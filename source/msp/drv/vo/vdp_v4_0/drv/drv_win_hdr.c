/******************************************************************************
  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_hdr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015-09-23
  Description   : Dolby HDR processing functions.
  History       :
  1.Date        : 2015-09-23
    Author      : sdk
    Modification: Created file
*******************************************************************************/

#include "drv_window.h"
#include "drv_virtual.h"
#include "drv_win_priv.h"
#include "hi_drv_stat.h"
#include "drv_win_buffer.h"

#include "drv_disp_debug.h"

#include "drv_win_hdr.h"
#include "drv_win_share.h"

#include "drv_win_frc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

extern HI_VOID  IncreaseFrameCntAccordingToFrame(HI_DRV_VIDEO_FRAME_S *pstFrame,WB_DEBUG_INFO_S *pstInfo);

//purpose of function below is to get EL and MD from a buf Node through BL frame.
#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
#endif

#ifndef container_of
#define container_of(ptr,type,member) ({  \
        const typeof(((type *)0)->member) *__mptr = (ptr);    \
        (type *)((char*)__mptr - offsetof( type , member)); } )
#endif

/* for debug. */
HI_S32 WIN_Dump2File(HI_CHAR *pBuf, int len, HI_CHAR *pfileName)
{
    int writeLen;
    struct file *pf;

    pf = vdp_k_fopen(pfileName, O_RDWR|O_CREAT|O_APPEND, 0);
    if (!pf)
    {
        DISP_ERROR("open file '%s' fail!\n", pfileName);
        return HI_FAILURE;
    }

    writeLen = vdp_k_fwrite(pBuf,len,pf);
    if(writeLen != len)
        return HI_FAILURE;

    vdp_k_fclose(pf);
    return HI_SUCCESS;
}




/******************************************************************************
    global object
*******************************************************************************/
extern volatile HI_S32 s_s32WindowGlobalFlag;

static WIN_DOLBY_LIB_INFO_S  s_DollbyLibInfo;


/******************************************************************************
    extern function
*******************************************************************************/
extern HI_S32 WinCheckFrame(HI_DRV_VIDEO_FRAME_S *pFrameInfo);
extern HI_VOID WinBuf_DebugAddInput(WB_DEBUG_INFO_S *pstInfo, HI_U32 u32FrameId);
extern HI_VOID WinBuf_DebugAddTryQF(WB_DEBUG_INFO_S *pstInfo);
extern HI_VOID WinBuf_DebugAddQFOK(WB_DEBUG_INFO_S *pstInfo);

extern HI_S32 DISP_GetDispOutput(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_OUT_TYPE_E * penDispType);
extern HI_S32 DISP_GetGfxState(HI_DRV_DISPLAY_E enDisp, HI_BOOL *pbNeedProcessGfx);
extern HI_S32 DISP_GenerateFrameOutColorSpace(HI_DRV_DISPLAY_E enDisp,
                                           HI_DRV_COLOR_SPACE_E enFrameInColorSpace,
                                           HI_DRV_COLOR_SPACE_E *penFrameOutColorSpace);


//Set window mode,note:Dolby mode will occupy two video layers.
HI_S32 WIN_SetMode(HI_HANDLE hWin, HI_DRV_WINDOW_MODE_E enWinMode)
{
    WINDOW_S    *pstWin  = HI_NULL;
    HI_BOOL     bVirtual = HI_TRUE;
    HI_U32      u32HdWinNum = 0;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        u32HdWinNum = WinGetHDWinNum();

        if(u32HdWinNum <= 0)
        {
            WIN_ERROR("No window exist!set window mode fail!\n");
            return HI_ERR_VO_WIN_NOT_EXIST;
        }
        else
        {
            if(pstWin->enWinMode == enWinMode)
            {
                WIN_INFO("The mode of window is the same as set.\n");
                return HI_SUCCESS;
            }

            if (HI_DRV_WINDOW_MODE_DOLBY == enWinMode)
            {
                if(u32HdWinNum > 1)
                {
                    WIN_ERROR("Too many windows,cannot set HDR mode!\n");
                    return HI_ERR_VO_WIN_UNSUPPORT;
                }
            }

            pstWin->enWinMode = enWinMode;
        }
    }

    return HI_SUCCESS;
}


HI_S32 WinBuf_PutNewDolbyFrame(WB_POOL_S    *pstWinBP,
                               HI_DRV_VIDEO_FRAME_S     *pstBLFrame,
                               HI_DRV_VIDEO_FRAME_S     *pstELFrame,
                               HI_BOOL                  bELValid,
                               HI_DRV_DOLBY_META_INFO_S *pstDolbyMdInfo,
                               HI_U32                    u32PlayCnt)
{
    HI_S32 nRet = HI_SUCCESS;
    DISP_BUF_NODE_S* pstNode = HI_NULL;
    DISP_MMZ_BUF_S   stMMZBuf;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstBLFrame);

    memset(&stMMZBuf,0x0,sizeof(DISP_MMZ_BUF_S));

#ifdef CFG_VDP_MMU_SUPPORT
    stMMZBuf.bSmmu = HI_TRUE;
#else
    stMMZBuf.bSmmu = HI_FALSE;
#endif

    WinBuf_DebugAddTryQF(pstWinBP->pstDebugInfo);
    nRet = DispBuf_GetEmptyNode(&pstWinBP->stBuffer, &pstNode);
    if (nRet != HI_SUCCESS)
    {
        return nRet;
    }

    /*set a barrier bettween DispBuf_GetEmptyNode and DispBuf_DelEmptyNode,
    * del oper will change the state of node in empty list, but get oper
    * will check it. so a barrier is neccessary. see DTS2014080502661.
    */
    barrier();

    memcpy(pstNode->u32Data, pstBLFrame, sizeof(HI_DRV_VIDEO_FRAME_S));
    if (bELValid)
    {
        pstNode->bValidData2 = HI_TRUE;//indicate Dolby dual source mode, both have BL & EL frames.
        memcpy(pstNode->u32Data2, pstELFrame, sizeof(HI_DRV_VIDEO_FRAME_S));
    }
    else
    {
        pstNode->bValidData2 = HI_FALSE;
    }

    pstNode->u32PlayCnt = u32PlayCnt;
    //copy metadata and store in buffer Node.
    pstNode->bHisiHdr = HI_FALSE;
    stMMZBuf.u32Size = pstDolbyMdInfo->u32TotalLen;
    stMMZBuf.u32StartPhyAddr = pstDolbyMdInfo->u32PhyAddr;
    nRet = DISP_OS_MMZ_Map(&stMMZBuf);
    if (nRet != HI_SUCCESS)
    {
        WIN_ERROR("MMZ Map fail.\n");
        return nRet;
    }

    memcpy(pstNode->u8Metadata,stMMZBuf.pu8StartVirAddr,DISP_BUF_METADATA_SIZE);


    //record Dolby metadata info in buffer Node.
    pstNode->stHdrInfo.enDispOutType = pstDolbyMdInfo->enDispOutType;
    pstNode->stHdrInfo.u32CompLen    = pstDolbyMdInfo->u32CompLen;
    pstNode->stHdrInfo.u32DmCfgLen   = pstDolbyMdInfo->u32DmCfgLen;
    pstNode->stHdrInfo.u32DmRegLen   = pstDolbyMdInfo->u32DmRegLen;
    pstNode->stHdrInfo.u32UpMdLen    = pstDolbyMdInfo->u32UpMdLen;
    pstNode->stHdrInfo.u32Hdr10InfoFrmLen= pstDolbyMdInfo->u32Hdr10InfoFrmLen;

    //according to description in dolbylib, output hdr10 is bt2020, others is bt709.
    if ((HI_DRV_DISP_TYPE_HDR10 == pstDolbyMdInfo->enDispOutType)
        || (HI_DRV_DISP_TYPE_HDR10_CERT == pstDolbyMdInfo->enDispOutType))
    {
        pstNode->enOutCs = HI_DRV_CS_BT2020_YUV_LIMITED;
    }
    else
    {
        pstNode->enOutCs = HI_DRV_CS_BT709_YUV_LIMITED;
    }

    DISP_OS_MMZ_UnMap(&stMMZBuf);

    nRet = DispBuf_DelEmptyNode(&pstWinBP->stBuffer, pstNode);
    if (nRet != HI_SUCCESS)
    {
        WIN_ERROR("DispBuf_DelEmptyNode failed, ID=0x%x\n", pstNode->u32ID);
        return HI_FAILURE;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S*)&(pstBLFrame->u32Priv[0]);

    if ((HI_TRUE != pstPriv->bForFenceUse)
      && (HI_DRV_FRAME_VDP_ALLOCATE_STILL != pstBLFrame->u32StillFrame))
    {
        IncreaseFrameCntAccordingToFrame(pstBLFrame,pstWinBP->pstDebugInfo);
        if (bELValid)
        {
            IncreaseFrameCntAccordingToFrame(pstELFrame,pstWinBP->pstDebugInfo);
        }
    }

    nRet = DispBuf_AddFullNode(&pstWinBP->stBuffer, pstNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    WinBuf_DebugAddInput(pstWinBP->pstDebugInfo, pstBLFrame->u32FrameIndex);
    WinBuf_DebugAddQFOK(pstWinBP->pstDebugInfo);

    return HI_SUCCESS;
}

#ifdef  CFG_HI3798CV200
static HI_VOID WinSpecificProcessOutTypeAndCs(HI_DRV_VIDEO_FRAME_TYPE_E   enSrcFrameType,
                                                        HI_DRV_COLOR_SPACE_E enInCs,
                                                        HI_DRV_DISP_OUT_TYPE_E  *penDispType,
                                                        HI_DRV_COLOR_SPACE_E *penOutCs)
{
    /* don't support sdr->hdr currently. */
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == enSrcFrameType)
    {
        *penDispType = HI_DRV_DISP_TYPE_NORMAL;
    }

    /* outCs follows inCs when output type is hdr. */
    if ((HI_DRV_DISP_TYPE_HDR10 == *penDispType)
        || (HI_DRV_DISP_TYPE_HDR10_CERT == *penDispType))
    {
        *penOutCs = enInCs;
    }

    /* don't support bt709/bt601 -> bt2020 currently. */
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == *penOutCs)
        || (HI_DRV_CS_BT2020_YUV_FULL == *penOutCs)
        || (HI_DRV_CS_BT2020_RGB_LIMITED == *penOutCs)
        || (HI_DRV_CS_BT2020_RGB_FULL == *penOutCs))
    {
        if ((HI_DRV_CS_BT2020_YUV_LIMITED != enInCs)
            && (HI_DRV_CS_BT2020_YUV_FULL != enInCs))
        {
            *penOutCs = enInCs;
        }
    }

    return;
}
#endif

/* put new Hdr10 frame into node with Hisi dm cfg.*/
HI_S32  WinBuf_HisiPutNewHdrFrame(WB_POOL_S                *pstWinBP,
                                    HI_DRV_VIDEO_FRAME_S     *pstFrame,
                                    HI_U32                    u32PlayCnt)
{
    HI_S32                  nRet = HI_SUCCESS;
    DISP_BUF_NODE_S         *pstNode = HI_NULL;
    HI_DRV_DISP_OUT_TYPE_E  enDispType = HI_DRV_DISP_TYPE_BUTT;
    HI_DRV_COLOR_SPACE_E    enOutCs = HI_DRV_CS_UNKNOWN;
    HI_PQ_HDR_CFG           *pstPqHdrCfg = HI_NULL;//Hisi-self hdr cfg.
    HI_PQ_WIN_HDR_INFO      stPqWinHdrMetaInfo; //the info that generate hdr cfg need.
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstFrame);

    pstPqHdrCfg = (HI_PQ_HDR_CFG *)DISP_MALLOC(sizeof(HI_PQ_HDR_CFG));
    if (HI_NULL == pstPqHdrCfg)
    {
        HI_ERR_WIN("Allocate HI_PQ_HDR_CFG fail.\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    DISP_MEMSET(&stPqWinHdrMetaInfo, 0x0, sizeof(HI_PQ_WIN_HDR_INFO));
    DISP_MEMSET(pstPqHdrCfg, 0x0, sizeof(HI_PQ_HDR_CFG));

    WinBuf_DebugAddTryQF(pstWinBP->pstDebugInfo);

    /* step1:get disp1's output type,hdr always on disp1 */
    nRet = DISP_GetDispOutput(HI_DRV_DISPLAY_1, &enDispType);
    if (nRet != HI_SUCCESS)
    {
        DISP_FREE(pstPqHdrCfg);
        HI_ERR_WIN("Get DISP1 output type fail.\n");
        return nRet;
    }

    switch (enDispType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
            stPqWinHdrMetaInfo.enDispType = HI_PQ_DISP_TYPE_NORMAL;
            break;
        case HI_DRV_DISP_TYPE_HDR10:
            stPqWinHdrMetaInfo.enDispType = HI_PQ_DISP_TYPE_HDR10;
            break;
        case HI_DRV_DISP_TYPE_HLG:
            stPqWinHdrMetaInfo.enDispType = HI_PQ_DISP_TYPE_HLG;
            break;
        default:
            HI_ERR_WIN("Unsupport DispOutType->[%d],Change to SDR out.\n",enDispType);
            enDispType = HI_DRV_DISP_TYPE_NORMAL;
            stPqWinHdrMetaInfo.enDispType = HI_PQ_DISP_TYPE_NORMAL;
            break;
    }

    /* step2:set the parameters that PQ needs. */
    stPqWinHdrMetaInfo.enSrcFrameType = pstFrame->enSrcFrameType;
    stPqWinHdrMetaInfo.enCodecType      = pstFrame->enCodecType;

    switch (stPqWinHdrMetaInfo.enSrcFrameType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_SDR:
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            stPqWinHdrMetaInfo.unHDRInfo.stHDR10Info = pstFrame->unHDRInfo.stHDR10Info;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            stPqWinHdrMetaInfo.unHDRInfo.stHLGInfo = pstFrame->unHDRInfo.stHLGInfo;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_SLF:
            stPqWinHdrMetaInfo.unHDRInfo.stSLFInfo = pstFrame->unHDRInfo.stSLFInfo;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_TECHNICOLOR:
            stPqWinHdrMetaInfo.unHDRInfo.stTechnicolorInfo = pstFrame->unHDRInfo.stTechnicolorInfo;
            break;
        default:
            HI_ERR_WIN("unknown enSrcFrameType.\n");
            stPqWinHdrMetaInfo.unHDRInfo.stHDR10Info = pstFrame->unHDRInfo.stHDR10Info;
            break;
    }

    /* get src color space and out color space. */
    WIN_SHARE_GetFrameColorSpace(pstFrame, &stPqWinHdrMetaInfo.enInCS);

    DISP_GenerateFrameOutColorSpace(HI_DRV_DISPLAY_1,
                                    stPqWinHdrMetaInfo.enInCS,
                                    &enOutCs);

    if ((HI_DRV_CS_UNKNOWN == enOutCs)
        || (HI_DRV_CS_BUTT <= enOutCs))
    {
        enOutCs = HI_DRV_CS_BT709_YUV_LIMITED;
    }

#ifdef  CFG_HI3798CV200
    WinSpecificProcessOutTypeAndCs(pstFrame->enSrcFrameType,
                                   stPqWinHdrMetaInfo.enInCS,
                                   &enDispType,
                                   &enOutCs);

    if (HI_DRV_VIDEO_FRAME_TYPE_SDR != pstFrame->enSrcFrameType)
#endif
    {
        stPqWinHdrMetaInfo.enOutCS = enOutCs;
        /* step3:call PQ's interface to generate DM config. */
        nRet = DRV_PQ_GetHdrCfg(&stPqWinHdrMetaInfo, pstPqHdrCfg);
        if (nRet != HI_SUCCESS)
        {
            DISP_FREE(pstPqHdrCfg);
            HI_ERR_WIN("Get Hdr config from PQ fail.\n");
            return nRet;
        }
    }

    /* step4:put frame and DM config into node buf */
    nRet = DispBuf_GetEmptyNode(&pstWinBP->stBuffer, &pstNode);
    if (nRet != HI_SUCCESS)
    {
        DISP_FREE(pstPqHdrCfg);
        return nRet;
    }

    /*set a barrier bettween DispBuf_GetEmptyNode and DispBuf_DelEmptyNode,
    * del oper will change the state of node in empty list, but get oper
    * will check it. so a barrier is neccessary. see DTS2014080502661.
    */
    barrier();

    memcpy(pstNode->u32Data, pstFrame, sizeof(HI_DRV_VIDEO_FRAME_S));
    /*here need to copy pq hdr cfg into data2 array of node.*/
    memcpy(pstNode->u8Metadata, pstPqHdrCfg, sizeof(HI_PQ_HDR_CFG));


    /* set disp type */
    pstNode->stHdrInfo.enDispOutType = enDispType;
    pstNode->enOutCs = enOutCs;
    /* set Hisi-self hdr10 path flag. */
    pstNode->bHisiHdr = HI_TRUE;
    pstNode->u32PlayCnt = u32PlayCnt;

    nRet = DispBuf_DelEmptyNode(&pstWinBP->stBuffer, pstNode);
    if (nRet != HI_SUCCESS)
    {
        DISP_FREE(pstPqHdrCfg);
        WIN_ERROR("DispBuf_DelEmptyNode failed, ID=0x%x\n", pstNode->u32ID);
        return nRet;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrame->u32Priv[0]);

    if ((HI_TRUE != pstPriv->bForFenceUse)
        && (HI_DRV_FRAME_VDP_ALLOCATE_STILL != pstFrame->u32StillFrame))
    {
        IncreaseFrameCntAccordingToFrame(pstFrame, pstWinBP->pstDebugInfo);
    }

    nRet = DispBuf_AddFullNode(&pstWinBP->stBuffer, pstNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    WinBuf_DebugAddInput(pstWinBP->pstDebugInfo, pstFrame->u32FrameIndex);
    WinBuf_DebugAddQFOK(pstWinBP->pstDebugInfo);
    DISP_FREE(pstPqHdrCfg);

    return HI_SUCCESS;
}

HI_S32 WinBuf_PutNewHdrFrame(WB_POOL_S                *pstWinBP,
                             HI_DRV_VIDEO_FRAME_S     *pstFrame,
                             HI_BOOL                   bDolbyProcess,
                             HI_DRV_DOLBY_META_INFO_S *pstDolbyMdInfo,
                               HI_U32                    u32PlayCnt)
{
    HI_S32  nRet = HI_SUCCESS;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstFrame);

    if(bDolbyProcess)
    {
        /* Dolby HDR10 process path.*/
        nRet = WinBuf_PutNewDolbyFrame(pstWinBP, pstFrame, HI_NULL, HI_FALSE, pstDolbyMdInfo, u32PlayCnt);
    }
    else
    {
        /* Hisi-self HDR process path. */
        nRet = WinBuf_HisiPutNewHdrFrame(pstWinBP, pstFrame, u32PlayCnt);
    }

    return nRet;
}


HI_DRV_VIDEO_FRAME_S* WinBuf_GetNextCfgFrm(WB_POOL_S *pstWinBP)
{
    DISP_BUF_NODE_S* pstNode;
    HI_DRV_VIDEO_FRAME_S* pstFrm;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    //get next frame that will be configurated in next interrupt.
    nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstNode);
    if (nRet != HI_SUCCESS)
    {
        return HI_NULL;
    }

    pstFrm = (HI_DRV_VIDEO_FRAME_S*)pstNode->u32Data;

    return pstFrm;
}


HI_S32 WinQueueDolbyFrame(HI_HANDLE                hWin,
                          HI_DRV_VIDEO_FRAME_S    *pBLFrmInfo,
                          HI_DRV_VIDEO_FRAME_S    *pELFrmInfo,
                          HI_BOOL                  bELValid,
                          HI_DRV_DOLBY_META_INFO_S *pstDolbyMdInfo)
{
	WINDOW_S *pstWin;
	HI_S32 nRet = HI_SUCCESS;
	HI_BOOL bVirtual = HI_FALSE;

	WinCheckDeviceOpen();
	WinCheckNullPointer(pBLFrmInfo);

	//ensure frame is Dolby frame.
	if (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL != pBLFrmInfo->enSrcFrameType)
	{
	    WIN_ERROR("Frame is NOT Dolby frame!\n");
	    return HI_ERR_VO_FRAME_INFO_ERROR;
	}

	// s2 get state
	nRet = WinCheckFrame(pBLFrmInfo);
	if (nRet)
	{
	    WIN_ERROR("win BL frame parameters invalid\n");
	    return HI_ERR_VO_FRAME_INFO_ERROR;
	}

	if (bELValid)
	{
	    nRet = WinCheckFrame(pELFrmInfo);
	    if (nRet)
	    {
	        WIN_ERROR("win EL frame parameters invalid\n");
	        return HI_ERR_VO_FRAME_INFO_ERROR;
	    }
	}

	bVirtual = WinCheckVirtual(hWin);
	if (!bVirtual)
	{
	    WinCheckWindow(hWin, pstWin);

	    if (HI_SUCCESS != WinStatisticLowdelayTimeInfor(hWin, pBLFrmInfo, EVENT_VO_FRM_IN))
	    {
	        WIN_ERROR("Update Window lowdelay time failed\n");
	    }

	    if (pstWin->bEnable == HI_TRUE)
	    {
	        HI_U32 u32PlayCnt = 0;
	        DRV_WIN_GetFramePlayCounts(pstWin->bQuickMode,
	                                   pstWin->hFrc,
	                                   pBLFrmInfo->u32FrameRate / 10,
	                                   pstWin->stDispInfo.u32RefreshRate,
	                                   &u32PlayCnt,
	                                   &pstWin->stWinDebugInfo.stFRC);

	        if (pBLFrmInfo->u32FrameRate / 10 != pstWin->stDispInfo.u32RefreshRate)
	        {
	            pBLFrmInfo->u32OriFrameRate = pBLFrmInfo->u32FrameRate;
	            pBLFrmInfo->u32FrameRate = pstWin->stDispInfo.u32RefreshRate * 10;
	        }

	        if (pELFrmInfo->u32FrameRate / 10 != pstWin->stDispInfo.u32RefreshRate)
	        {
	            pELFrmInfo->u32OriFrameRate = pELFrmInfo->u32FrameRate;
	            pELFrmInfo->u32FrameRate = pstWin->stDispInfo.u32RefreshRate * 10;
	        }

	        nRet = WinBuf_PutNewDolbyFrame(&pstWin->stBuffer.stWinBP,
	                                       pBLFrmInfo,
	                                       pELFrmInfo,
	                                       bELValid,
	                                       pstDolbyMdInfo,
	                                       u32PlayCnt);
	        if (HI_SUCCESS != nRet)
	        {
	            return HI_ERR_VO_BUFQUE_FULL;
	        }
	    }
	    else
	    {
	        WIN_WARN("Window is disabled\n");
	        return HI_ERR_VO_WIN_NOT_ENABLE;
	    }
	}
	else
	{
	    return HI_ERR_VO_WIN_UNSUPPORT;
	}

	return HI_SUCCESS;
}

HI_VOID WIN_HdrDolbyProcessPolicy(HI_DRV_VIDEO_FRAME_TYPE_E enFrameType,
                                  HI_DRV_DISP_OUT_TYPE_E    enDispType,
                                  HI_BOOL bHisiProcess,
                                  HI_BOOL *pbDolbyProcess)
{
    if (HI_TRUE == WIN_GetDolbyLibStatus()
        && (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enFrameType)
        && (HI_FALSE == bHisiProcess)
        && ((HI_DRV_DISP_TYPE_NORMAL == enDispType)
            || (HI_DRV_DISP_TYPE_SDR_CERT == enDispType)
            || (HI_DRV_DISP_TYPE_HDR10 == enDispType)
            || (HI_DRV_DISP_TYPE_HDR10_CERT == enDispType)
            || (HI_DRV_DISP_TYPE_DOLBY == enDispType)))
    {
        *pbDolbyProcess = HI_TRUE;
    }
    else if (HI_TRUE == WIN_GetDolbyLibStatus()
        && (HI_DRV_VIDEO_FRAME_TYPE_SDR == enFrameType)
        && (HI_FALSE == bHisiProcess)
        && ((HI_DRV_DISP_TYPE_HDR10 == enDispType)
            || (HI_DRV_DISP_TYPE_HDR10_CERT == enDispType)
            || (HI_DRV_DISP_TYPE_DOLBY == enDispType)))
    {
        *pbDolbyProcess = HI_TRUE;
    }
    else
    {
        *pbDolbyProcess = HI_FALSE;
    }

    return;
}

HI_S32 WIN_GetDispOutput(HI_HANDLE hWin, HI_DRV_DISP_OUT_TYPE_E *penDispType)
{
    HI_S32 s32Ret = HI_FAILURE;
    WINDOW_S *pstWin;

    if(HI_NULL == penDispType)
    {
        WIN_ERROR("para penDispType is null!\n");
        return HI_ERR_VO_NULL_PTR;
    }

    WinCheckWindow(hWin, pstWin);

    s32Ret = DISP_GetDispOutput(pstWin->enDisp,penDispType);
    return s32Ret;
}

HI_S32 WIN_GetDispOutputAndGfxState(HI_HANDLE hWin,
                                    HI_DRV_DISP_OUT_TYPE_E *penDispType,
                                    HI_BOOL  *pbNeedProcessGfx)
{
    HI_S32 s32Ret = HI_FAILURE;
    WINDOW_S *pstWin = HI_NULL;

    WinCheckWindow(hWin, pstWin);

    s32Ret = DISP_GetDispOutput(pstWin->enDisp,penDispType);
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = DISP_GetGfxState(pstWin->enDisp, pbNeedProcessGfx);
    return s32Ret;
}


HI_S32 WIN_CloseHdrPath(HI_HANDLE hWin, HI_BOOL bEnable)
{
    WINDOW_S*    pstWin;
    HI_BOOL     bVirtual = HI_TRUE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        pstWin->stCfg.stAttrBuf.bCloseHdrPath = bEnable;
        atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return HI_SUCCESS;

}

/* whether to take Hisi-self hdr path or not,true indicate not to take Hisi-self,
 * false->Hisi-self hdr path. */
HI_S32 WIN_SetHisiPath(HI_HANDLE hWin,HI_BOOL bEnable)
{
    WINDOW_S*    pstWin;
    HI_BOOL     bVirtual = HI_TRUE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        pstWin->stCfg.stAttrBuf.bHisiHdr = bEnable;
        atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return HI_SUCCESS;
}
HI_S32 WIN_SetDolbyLibInfo(WIN_DOLBY_LIB_INFO_S  *pstDolbyLibInfo )
{
    memcpy(&s_DollbyLibInfo, pstDolbyLibInfo, sizeof(WIN_DOLBY_LIB_INFO_S));
    return HI_SUCCESS;
}


HI_VOID WIN_ShowDolbyLibInfo(HI_VOID)
{
     WIN_ERROR("bValid    : %d\n",s_DollbyLibInfo.bValid);
     WIN_ERROR("Version   : %s\n",s_DollbyLibInfo.cVersion);
     WIN_ERROR("Buildtime : %s\n",s_DollbyLibInfo.cBuildtime);
     WIN_ERROR("UserName  : %s\n",s_DollbyLibInfo.cUserName);
     WIN_ERROR("UserID    : 0x%x,0x%x,0x%x,0x%x\n",s_DollbyLibInfo.u32UserID[0],s_DollbyLibInfo.u32UserID[1],s_DollbyLibInfo.u32UserID[2],s_DollbyLibInfo.u32UserID[3]);
     return ;
}

HI_BOOL WIN_GetDolbyLibStatus(HI_VOID)
{
    return s_DollbyLibInfo.bValid;
}

HI_VOID WIN_JudgeHdrFrame(HI_DRV_VIDEO_FRAME_TYPE_E  enFrameType,HI_BOOL *pbIsHdrFrame)
{
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == enFrameType)
    {
        *pbIsHdrFrame = HI_FALSE;
    }
    else
    {
        *pbIsHdrFrame = HI_TRUE;
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

