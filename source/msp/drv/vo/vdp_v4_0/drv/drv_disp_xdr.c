/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_xdr.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-05-12
  Description   : process sdr/hdr source.
  History       :
  1.Date        : 2017-05-12
    Author      : q00293180
    Modification: Created file
*******************************************************************************/
#ifndef __DISP_PLATFORM_BOOT__
#include "hi_drv_hdmi.h"
#include "drv_hdmi_ext.h"
#endif
#include "drv_disp_priv.h"
#include "drv_disp_bufcore.h"
#include "drv_disp_xdr.h"
#include "drv_win_share.h"

#ifdef VDP_DOLBY_HDR_SUPPORT
#include "drv_disp_dolby.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

//========================static variable============================
static WIN_SHARE_INFO_S   g_stWinShareInfo = {0};


//=======================extern functions.==========================
#ifndef __DISP_PLATFORM_BOOT__
extern HI_S32 DispGetHdmiExportFuncPtr(HDMI_EXPORT_FUNC_S ** pstHdmiFunc);
#else
#define DispGetHdmiExportFuncPtr(a) HI_SUCCESS
#endif

extern HI_VOID XDR_DOLBY_Process(DISP_S                *pstDisp,
                                  WIN_INFO_S            *pstWinInfo,
                                  HI_DRV_COLOR_SPACE_E   *penOutCs,
                                  HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr);

//=======================end extern functions========================

HI_VOID DISP_XDR_UpdateDispInfo(HI_DRV_DISPLAY_E enDisp, HI_DISP_DISPLAY_INFO_S *pstDispInfo)
{
#ifndef __DISP_PLATFORM_BOOT__
    (HI_VOID)DISP_ISR_SetDispInfo(enDisp, pstDispInfo);
#endif
    return;
}

HI_VOID XDR_Debug_SetDispXdrProcInfo(DISP_S *pstDisp,
                                               WIN_SHARE_INFO_S *pstWinShareInfo,
                                               DISP_XDR_WORK_MODE_E enXdrWorkMode)
{
    HI_U32 u32Index = 0;

    pstDisp->stXdrProcInfo.enWorkMode = enXdrWorkMode;
    pstDisp->stXdrProcInfo.u32HdWinNum = pstWinShareInfo->u32HdWinNum;

    for(u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pstDisp->stXdrProcInfo.stWinInfo[u32Index] = pstWinShareInfo->stWinInfo[u32Index];
    }
    return;
}

HI_VOID XDR_Policy_MaskDisplayChannel(HI_DRV_DISPLAY_E enDisp, HI_BOOL bMask)
{
#ifndef __DISP_PLATFORM_BOOT__
    DISP_INTF_OPERATION_S stDispHalFunc = {0};
    memset(&stDispHalFunc, 0x0, sizeof(DISP_INTF_OPERATION_S));

    (HI_VOID)DISP_HAL_GetOperation(&stDispHalFunc);

    if ((HI_NULL == stDispHalFunc.PF_DispMask)
        || (HI_NULL == stDispHalFunc.PF_DispUnMask))
    {
        return;
    }

    if (bMask)
    {
        stDispHalFunc.PF_DispMask(enDisp);
    }
    else
    {
        stDispHalFunc.PF_DispUnMask(enDisp);
    }
#endif
    return;
}

HI_S32 XDR_Policy_FindValidWindow(WIN_SHARE_INFO_S *pstWinShareInfo, HI_U32 *pu32Index)
{
    HI_U32 u32Index = 0;
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if (WIN_SHARE_HandleValid(pstWinShareInfo->stWinInfo[u32Index].hWinHandle))
        {
            *pu32Index = u32Index;
            return HI_SUCCESS;
        }
    }

    HI_ERR_DISP("Can not find the valid window!\n");
    return HI_FAILURE;
}


/**********************functions below belong to POLICY MODULE,  func definitions need to be discussed.*********************************/
DISP_XDR_WORK_MODE_E XDR_Policy_WorkModePolicy(WIN_SHARE_INFO_S *pstWinShareInfo, DISP_XDR_WORK_MODE_E enLastWorkMode)
{
    DISP_XDR_WORK_MODE_E   enWorkMode = XDR_WORK_MODE_BUTT;
    HI_DRV_VIDEO_FRAME_S  *pCurrentFrm   = HI_NULL;
    DISP_BUF_NODE_S       *pstDispBufNode = HI_NULL;
    HI_U32                 u32Index = 0;

    if (1 != pstWinShareInfo->u32HdWinNum)
    {
        return  XDR_WORK_MODE_HISI;
    }

    if (HI_FAILURE == XDR_Policy_FindValidWindow(pstWinShareInfo, &u32Index))
    {
        return XDR_WORK_MODE_HISI;
    }

    /*
        * when close hdr function. go through hisi mode.
        */
    if (pstWinShareInfo->stWinInfo[u32Index].bCloseHdr)
    {
        return XDR_WORK_MODE_HISI;
    }

    pCurrentFrm = pstWinShareInfo->stWinInfo[u32Index].pCurrentFrame;
    if (HI_NULL == pCurrentFrm)
    {
        enWorkMode = enLastWorkMode;
    }
    else
    {
        pstDispBufNode = container_of((HI_U32 *)pCurrentFrm, DISP_BUF_NODE_S, u32Data[0]);
        if (pstDispBufNode->bHisiHdr)
        {
            enWorkMode = XDR_WORK_MODE_HISI;
        }
        else
        {
            enWorkMode = XDR_WORK_MODE_DOLBY;
        }

    }

    return enWorkMode;
}

//get the index of max valid&enable win out of the share array.
HI_VOID XDR_Policy_GetMaxWinIndex(WIN_SHARE_INFO_S *pstWinShareInfo, HI_U32 *pu32MaxWinIndex)
{
    HI_U32 u32Index = 0, u32MaxWinIndex = INVALID_WIN_INDEX;
    HI_U64 u64Size = 0, u64MaxSize = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if ((WIN_SHARE_HandleValid(pstWinShareInfo->stWinInfo[u32Index].hWinHandle))
            && (pstWinShareInfo->stWinInfo[u32Index].bWinEnable))
        {
            u64Size = (HI_U64)(pstWinShareInfo->stWinInfo[u32Index].stDisp.s32Width *
                      pstWinShareInfo->stWinInfo[u32Index].stDisp.s32Height);

            if (u64MaxSize < u64Size)
            {
                u64MaxSize = u64Size;
                u32MaxWinIndex = u32Index;
            }
        }
    }

    *pu32MaxWinIndex = u32MaxWinIndex;
    return;
}


HI_BOOL XDR_Policy_VdmProcessByInAndOutColorSpace(HI_DRV_COLOR_SPACE_E enInCs,
                                                                 HI_DRV_COLOR_SPACE_E enOutCs)
{
    if (enInCs == enOutCs)
    {
        return HI_FALSE;
    }

    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCs)
        || (HI_DRV_CS_BT2020_YUV_LIMITED == enOutCs))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}


HI_BOOL XDR_Policy_VdmProcessBySrcAndOutSignal(HI_DRV_VIDEO_FRAME_TYPE_E enSrcType,
                                                             HI_DRV_DISP_OUT_TYPE_E enOutType)
{
    HI_BOOL bVdmProcess = HI_FALSE;

    switch(enSrcType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_SDR:
            switch (enOutType)
            {
                case HI_DRV_DISP_TYPE_SDR_CERT:
                case HI_DRV_DISP_TYPE_NORMAL:
                    bVdmProcess = HI_FALSE;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                    bVdmProcess = HI_TRUE;
                    break;
                case HI_DRV_DISP_TYPE_HLG:
                    bVdmProcess = HI_TRUE;
                    break;
                default:
                    bVdmProcess = HI_FALSE;
                    break;
            }
            break;

        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            switch (enOutType)
            {
                case HI_DRV_DISP_TYPE_SDR_CERT:
                case HI_DRV_DISP_TYPE_NORMAL:
                    bVdmProcess = HI_TRUE;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                    bVdmProcess = HI_FALSE;
                    break;
                case HI_DRV_DISP_TYPE_HLG:
                    bVdmProcess = HI_TRUE;
                    break;
                default:
                    bVdmProcess = HI_FALSE;
                    break;
            }
            break;

        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            switch (enOutType)
            {
                case HI_DRV_DISP_TYPE_SDR_CERT:
                case HI_DRV_DISP_TYPE_NORMAL:
                    bVdmProcess = HI_TRUE;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                    bVdmProcess = HI_TRUE;
                    break;
                case HI_DRV_DISP_TYPE_HLG:
                    bVdmProcess = HI_FALSE;
                    break;
                default:
                    bVdmProcess = HI_FALSE;
                    break;
            }
            break;

        case HI_DRV_VIDEO_FRAME_TYPE_SLF:
            switch (enOutType)
            {
                case HI_DRV_DISP_TYPE_SDR_CERT:
                case HI_DRV_DISP_TYPE_NORMAL:
                case HI_DRV_DISP_TYPE_HDR10:
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                case HI_DRV_DISP_TYPE_HLG:
                    bVdmProcess = HI_TRUE;
                    break;
                default:
                    bVdmProcess = HI_FALSE;
                    break;
            }
            break;
        default:
            bVdmProcess = HI_FALSE;
            break;
    }
    return bVdmProcess;
}

HI_VOID XDR_Process_Vdm_GenerateVdmConfig(WIN_SHARE_INFO_S  *pstWinShareInfo,
                                                       HI_BOOL            *pbVdmProcessArray)
{
    HI_U32 u32Index = 0;
    WIN_INFO_S *pstWinInfo = HI_NULL;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pstWinInfo = &pstWinShareInfo->stWinInfo[u32Index];
        if ((WIN_SHARE_HandleValid(pstWinInfo->hWinHandle))
            && (pstWinInfo->bWinEnable)
            && (HI_NULL != pstWinInfo->pCurrentFrame))
        {
            if ((XDR_Policy_VdmProcessBySrcAndOutSignal(pstWinInfo->pCurrentFrame->enSrcFrameType, \
                                                        pstWinInfo->enOutType))
                 || (XDR_Policy_VdmProcessByInAndOutColorSpace(pstWinInfo->enInCsc, \
                                                        pstWinInfo->enOutCsc)))
            {
                pbVdmProcessArray[u32Index] = HI_TRUE;
            }
        }
    }

    return;
}

static HI_VOID XDR_InfoFrame_SetHdrModeAndEotfType(HI_DRV_DISP_OUT_TYPE_E enOutType,
                                                  HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    switch (enOutType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
            pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
            break;
        case HI_DRV_DISP_TYPE_HDR10:
            pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3;
            pstHdmiHdrAttr->enEotfType = HI_DRV_HDMI_EOTF_SMPTE_ST_2084;
            break;
        case HI_DRV_DISP_TYPE_HLG:
            pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3;
            pstHdmiHdrAttr->enEotfType = HI_DRV_HDMI_EOTF_HLG;
            break;
        default:
            pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
            break;
    }

    return;
}


static HI_VOID XDR_InfoFrame_SetColorimetry(HI_DRV_COLOR_SPACE_E enOutCs,
                                                   HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    switch (enOutCs)
    {
        case HI_DRV_CS_BT601_YUV_FULL:
        case HI_DRV_CS_BT601_YUV_LIMITED:
            pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_ITU601;
            break;
        case HI_DRV_CS_BT709_YUV_FULL:
        case HI_DRV_CS_BT709_YUV_LIMITED:
            pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_ITU709;
            break;
        case HI_DRV_CS_BT2020_YUV_FULL:
        case HI_DRV_CS_BT2020_YUV_LIMITED:
            pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_2020_NON_CONST_LUMINOUS;
            break;
        default:
            pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_ITU709;
            break;
    }

    return;
}

static HI_VOID XDR_InfoFrame_SetDescriptor(WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut,
                                           HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    if(pstMdInfoOut->bMasteringAvailable)
    {
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_X = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_x[0];
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_Y = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_y[0];
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_X = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_x[1];
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_Y = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_y[1];
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_X = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_x[2];
        pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_Y = pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_y[2];
        pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_X = pstMdInfoOut->stMasteringInfo.u16WhitePoint_x;
        pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_Y = pstMdInfoOut->stMasteringInfo.u16WhitePoint_y;

        /* !NOTICE!
             * conflict between protocol of hevc and CEA861.3-2015,
             * hevc define max and min disp master luminance as unsigned 32-bit value
             * in units of 0.0001 nits; while CEA861.3-2015 define max as unsigned 16-bit
             * value in units of 1 nits,min as unsigned 16-bit value in units of 0.0001 nits.
             */
        pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLuminance = (HI_U16)(pstMdInfoOut->stMasteringInfo.u32MaxDisplayMasteringLuminance / 10000);
        pstHdmiHdrAttr->unDescriptor.stType1.u16MinLuminance = (HI_U16)pstMdInfoOut->stMasteringInfo.u32MinDisplayMasteringLuminance;

    }
    else
    {
        memset(&pstHdmiHdrAttr->unDescriptor.stType1,0x0,sizeof(HI_DRV_HDMI_META_DESCIRPER_1ST));
    }

    if (pstMdInfoOut->bContentAvailable)
    {
        pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLightLevel    = (HI_U16)pstMdInfoOut->stContentInfo.u32MaxContentLightLevel;
        pstHdmiHdrAttr->unDescriptor.stType1.u16AverageLightLevel= (HI_U16)pstMdInfoOut->stContentInfo.u32MaxPicAverageLightLevel;
    }
    else
    {   /*
             * max conten light level & average light level are useless in frame info.set 0 currently.
             */
        pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLightLevel    = 0;      //zero currently
        pstHdmiHdrAttr->unDescriptor.stType1.u16AverageLightLevel= 0;     //zero currently
    }

    return;
}

static HI_VOID XDR_InfoFrame_FillByUnifiedMd(WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut,
                                            HI_DRV_COLOR_SPACE_E enOutCs,
                                            HI_DRV_DISP_OUT_TYPE_E enOutType,
                                            HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    XDR_InfoFrame_SetHdrModeAndEotfType(enOutType, pstHdmiHdrAttr);

    pstHdmiHdrAttr->enMetadataId = HI_DRV_HDMI_HDR_METADATA_ID_0;

    XDR_InfoFrame_SetDescriptor(pstMdInfoOut, pstHdmiHdrAttr);

    XDR_InfoFrame_SetColorimetry(enOutCs, pstHdmiHdrAttr);

    return;
}

HI_VOID XDR_InfoFrame_FillByDefault(HI_DRV_COLOR_SPACE_E enOutCs,
                                                        HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    memset(pstHdmiHdrAttr,0x0,sizeof(HI_DRV_HDMI_HDR_ATTR_S));

    pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;

    XDR_InfoFrame_SetColorimetry(enOutCs, pstHdmiHdrAttr);

    return;
}

static HI_VOID XDR_InfoFrame_GetUnifiedMd(HI_DRV_VIDEO_FRAME_S *pstFrame,
                                                   WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    WIN_SHARE_UNIFIED_METADATA_IN_S stMdInfoIn;

    memset(&stMdInfoIn,0x0,sizeof(WIN_SHARE_UNIFIED_METADATA_IN_S));

    stMdInfoIn.enSrcFrameType = pstFrame->enSrcFrameType;
    switch(stMdInfoIn.enSrcFrameType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            stMdInfoIn.stColorDescriptionInfo = pstFrame->stColourInfo;
            stMdInfoIn.u8TransferCharacteristics = pstFrame->unHDRInfo.stHDR10Info.u8TransferCharacteristics;
            stMdInfoIn.bMasteringAvailable = pstFrame->unHDRInfo.stHDR10Info.u8MasteringAvailable;
            stMdInfoIn.stMasteringInfo = pstFrame->unHDRInfo.stHDR10Info.stMasteringInfo;
            stMdInfoIn.bContentAvailable = pstFrame->unHDRInfo.stHDR10Info.u8ContentAvailable;
            stMdInfoIn.stContentInfo  = pstFrame->unHDRInfo.stHDR10Info.stContentInfo;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            stMdInfoIn.stColorDescriptionInfo = pstFrame->stColourInfo;
            stMdInfoIn.u8TransferCharacteristics = pstFrame->unHDRInfo.stHLGInfo.u8TransferCharacteristics;
            stMdInfoIn.bMasteringAvailable = pstFrame->unHDRInfo.stHLGInfo.u8MasteringAvailable;
            stMdInfoIn.stMasteringInfo = pstFrame->unHDRInfo.stHLGInfo.stMasteringInfo;
            stMdInfoIn.bContentAvailable = pstFrame->unHDRInfo.stHLGInfo.u8ContentAvailable;
            stMdInfoIn.stContentInfo  = pstFrame->unHDRInfo.stHLGInfo.stContentInfo;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_SLF:
            stMdInfoIn.stColorDescriptionInfo = pstFrame->stColourInfo;
            stMdInfoIn.u8TransferCharacteristics = pstFrame->unHDRInfo.stSLFInfo.u8TransferCharacteristics;
            stMdInfoIn.bMasteringAvailable = pstFrame->unHDRInfo.stSLFInfo.u8MasteringAvailable;
            stMdInfoIn.stMasteringInfo = pstFrame->unHDRInfo.stSLFInfo.stMasteringInfo;
            stMdInfoIn.bContentAvailable = pstFrame->unHDRInfo.stSLFInfo.u8ContentAvailable;
            stMdInfoIn.stContentInfo  = pstFrame->unHDRInfo.stSLFInfo.stContentInfo;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_TECHNICOLOR:
            DISP_ERROR("Unsupport frame type.\n");
            return;
        default:
            break;

    }

    WIN_SHARE_GetUnifiedMetadata(&stMdInfoIn, pstFrame->enCodecType, pstMdInfoOut);

    return;
}

HI_VOID XDR_InfoFrame_Fill(DISP_S       *pstDisp,
                           WIN_INFO_S   *pstWinInfo,
                           HI_DRV_COLOR_SPACE_E   enOutCs,
                           HI_DRV_DISP_OUT_TYPE_E enOutType,
                           HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    WIN_SHARE_UNIFIED_METADATA_OUT_S stMdInfoOut;

    memset(&stMdInfoOut,0x0,sizeof(WIN_SHARE_UNIFIED_METADATA_OUT_S));

    //max win is invalid or disable.
    if ((HI_FALSE == WIN_SHARE_HandleValid(pstWinInfo->hWinHandle))
        || (!pstWinInfo->bWinEnable))
    {
        XDR_InfoFrame_FillByDefault(enOutCs,pstHdmiHdrAttr);
        return;
    }

    //max win is valid, and receive null frame.use last info frame.
    if (HI_NULL == pstWinInfo->pCurrentFrame)
    {
        *pstHdmiHdrAttr = pstDisp->stXdrPlayInfo.stPreHdmiHdrAttr;
        return;
    }

    //unifiy metadata.
    XDR_InfoFrame_GetUnifiedMd(pstWinInfo->pCurrentFrame, &stMdInfoOut);

    //valid frame.
    XDR_InfoFrame_FillByUnifiedMd(&stMdInfoOut,
                                  enOutCs,
                                  enOutType,
                                  pstHdmiHdrAttr);

    return;
}

HI_VOID XDR_Process_WorkModeChange(DISP_S *pstDisp,
                                             HI_DRV_DISP_PROCESS_MODE_E enCurDispMode,
                                             HI_DRV_DISP_PROCESS_MODE_E enPreDispMode)
{
#ifndef __DISP_PLATFORM_BOOT__
    HI_BOOL bWorkModeChange = HI_FALSE;
    HI_BOOL bCurSdrWorkMode = HI_TRUE;

    if (((HI_DRV_DISP_PROCESS_MODE_SDR == enCurDispMode)
        && (HI_DRV_DISP_PROCESS_MODE_SDR != enPreDispMode))
        || ((HI_DRV_DISP_PROCESS_MODE_SDR != enCurDispMode)
        && (HI_DRV_DISP_PROCESS_MODE_SDR == enPreDispMode)))
    {
        bWorkModeChange = HI_TRUE;
    }

    bCurSdrWorkMode = (HI_DRV_DISP_PROCESS_MODE_SDR == enCurDispMode)? HI_TRUE : HI_FALSE;

    pstDisp->pstIntfOpt->PF_WorkModeChangeProcess(bWorkModeChange,bCurSdrWorkMode);
#endif
    return;

}


/*****************************************************************************
para[in]:   pstDisp
               pstWinShareInfo
para[out]: pstHdmiHdrAttr
               penDispProcessMode
               penOutCs
*******************************************************************************/
HI_VOID XDR_Process_HisiProcess(DISP_S                *pstDisp,
                                       WIN_SHARE_INFO_S       *pstWinShareInfo,
                                       HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr,
                                       HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                                       HI_DRV_COLOR_SPACE_E   *penOutCs)
{
#ifndef __DISP_PLATFORM_BOOT__
    HI_U32 u32MaxWinIndex = 0;
    HI_BOOL bVdmProcess[WINDOW_MAX_NUMBER] = {0};
    HI_DRV_COLOR_SPACE_E enOutCs = HI_DRV_CS_BUTT;
    HI_DRV_DISP_OUT_TYPE_E enOutType = HI_DRV_DISP_TYPE_BUTT;
    *penDispProcessMode = HI_DRV_DISP_PROCESS_MODE_SDR;

    XDR_Policy_GetMaxWinIndex(pstWinShareInfo, &u32MaxWinIndex);

    //generate vdm process array.
    XDR_Process_Vdm_GenerateVdmConfig(pstWinShareInfo, &bVdmProcess[0]);

    if (INVALID_WIN_INDEX != u32MaxWinIndex)
    {
        //adjust config policy (different chip set may have different policy.)
        pstDisp->pstIntfOpt->PF_AdjustConfig(pstWinShareInfo,
                                            u32MaxWinIndex,
                                            &bVdmProcess[0],
                                            pstDisp->stDispInfo.enDispProcessMode,
                                            penDispProcessMode,
                                            &enOutCs,
                                            &enOutType);

        //get hdmi metadata.
        XDR_InfoFrame_Fill(pstDisp,
                           &pstWinShareInfo->stWinInfo[u32MaxWinIndex],
                           enOutCs,
                           enOutType,
                           pstHdmiHdrAttr);

        *penOutCs = enOutCs;
    }
    else
    {
        enOutCs = pstDisp->stSetting.enOutputColorSpace;
        XDR_InfoFrame_FillByDefault(enOutCs,pstHdmiHdrAttr);
        *penOutCs = enOutCs;
    }

    //need to clean and fix gfx issue before config register.
    XDR_Process_WorkModeChange(pstDisp, *penDispProcessMode, pstDisp->stDispInfo.enDispProcessMode);

    //config all win.
    pstDisp->pstIntfOpt->PF_SetHdLayer(pstWinShareInfo,
                                       &bVdmProcess[0],
                                       *penDispProcessMode);

    //record proc.
#endif
    return;
}



/*****************************************************************************
para[in]:   pstDisp
               pstWinShareInfo
para[out]: pstHdmiHdrAttr
               penDispProcessMode
               penOutCs
*******************************************************************************/
HI_VOID XDR_Process_DolbyProcess(DISP_S                *pstDisp,
                                       WIN_SHARE_INFO_S       *pstWinShareInfo,
                                       HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr,
                                       HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                                       HI_DRV_COLOR_SPACE_E   *penOutCs)
{
#ifndef __DISP_PLATFORM_BOOT__
    HI_U32 u32WinIndex = INVALID_WIN_INDEX;

    if (HI_FAILURE == XDR_Policy_FindValidWindow(pstWinShareInfo, &u32WinIndex))
    {
        DISP_ERROR("Invalid window!\n");
        *penDispProcessMode = HI_DRV_DISP_PROCESS_MODE_SDR;
        *penOutCs = pstDisp->stDispInfo.eColorSpace;
        return ;
    }

    *penDispProcessMode = HI_DRV_DISP_PROCESS_MODE_HDR;

    //need to clean and fix gfx issue before config register.
    XDR_Process_WorkModeChange(pstDisp, *penDispProcessMode, pstDisp->stDispInfo.enDispProcessMode);

    //dolby process.
    XDR_DOLBY_Process(pstDisp, &pstWinShareInfo->stWinInfo[u32WinIndex], penOutCs, pstHdmiHdrAttr);

    //NOTE:outCs is decided by dolbylib. SDR/Dolby outType is 709 while HDR10 is 2020.
    pstWinShareInfo->stWinInfo[u32WinIndex].enOutCsc = *penOutCs;
#endif
    return;
}


HI_VOID XDR_Process_SendHdmiInfoFrame(HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
#ifndef __DISP_PLATFORM_BOOT__
    HDMI_EXPORT_FUNC_S *pstHdmiFunc = HI_NULL;

    if (HI_SUCCESS != DispGetHdmiExportFuncPtr(&pstHdmiFunc))
    {
        DISP_ERROR("DISP_get HDMI func failed!");
        return ;
    }

    if (pstHdmiFunc->pfnHdmiSetHdrAttr)
    {
        if (pstHdmiFunc->pfnHdmiSetHdrAttr(HI_UNF_HDMI_ID_0, pstHdmiHdrAttr))
        {
            DISP_ERROR("HDMI setHdrAttr Fail.\n");
        }
    }
    else
    {
        DISP_ERROR("pfnHdmiSetHdrAttr of HDMI is NULL!\n");
    }
#endif
    return;
}

HI_VOID XDR_ResetV0V1Layer(DISP_S *pstDisp)
{
#ifndef __DISP_PLATFORM_BOOT__
    //disable v0/v1 layer and regions.
    pstDisp->pstIntfOpt->PF_ResetV0V1Layer();
#endif
    return;
}

HI_VOID XDR_Process(DISP_S                *pstDisp,
                    DISP_XDR_WORK_MODE_E enXdrWorkMode,
                    WIN_SHARE_INFO_S       *pstWinShareInfo,
                    HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr,
                    HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                    HI_DRV_COLOR_SPACE_E   *penOutCs)
{
#ifndef __DISP_PLATFORM_BOOT__

    if (XDR_WORK_MODE_DOLBY == enXdrWorkMode)
    {
        // TODO:
        XDR_Process_DolbyProcess(pstDisp,
                                 pstWinShareInfo,
                                 pstHdmiHdrAttr,
                                 penDispProcessMode,
                                 penOutCs);
    }
    else
    {
        XDR_Process_HisiProcess(pstDisp,
                                pstWinShareInfo,
                                pstHdmiHdrAttr,
                                penDispProcessMode,
                                penOutCs);
    }

#endif
    return;
}


HI_VOID DISP_XDR_IsrProcess(HI_VOID *hHandle, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    DISP_S                      *pstDisp = HI_NULL;
    DISP_XDR_WORK_MODE_E         enXdrWorkMode = XDR_WORK_MODE_BUTT;
    HI_DRV_HDMI_HDR_ATTR_S       stHdmiHdrAttr;
    HI_DISP_DISPLAY_INFO_S       stDispInfo;
    WIN_SHARE_INFO_S            *pstWinShareInfo = HI_NULL;
    HI_BOOL                      bMaskSdChannel = HI_FALSE;

    pstDisp = (DISP_S *)hHandle;

    memset(&stHdmiHdrAttr, 0x0, sizeof(HI_DRV_HDMI_HDR_ATTR_S));
    memset(&stDispInfo, 0x0, sizeof(HI_DISP_DISPLAY_INFO_S));

    if ( ( DISP_PRIV_STATE_WILL_ENABLE == pstDisp->eState )
         || ( DISP_PRIV_STATE_WILL_DISABLE == pstDisp->eState )
         || ( HI_DRV_DISP_C_PREPARE_CLOSE == pstInfo->eEventType )
         || ( HI_DRV_DISP_C_PREPARE_TO_PEND == pstInfo->eEventType ))
    {
        return ;
    }

    stDispInfo = pstInfo->stDispInfo;

    pstWinShareInfo = &g_stWinShareInfo;
    WIN_SHARE_GetShareInfo(pstWinShareInfo);

    enXdrWorkMode = XDR_Policy_WorkModePolicy(pstWinShareInfo, pstDisp->stXdrPlayInfo.enPreWorkMode);

    XDR_ResetV0V1Layer(pstDisp);

    XDR_Process(pstDisp,
                enXdrWorkMode,
                pstWinShareInfo,
                &stHdmiHdrAttr,
                &stDispInfo.enDispProcessMode,
                &stDispInfo.eColorSpace);

    bMaskSdChannel = (HI_DRV_DISP_PROCESS_MODE_HDR == stDispInfo.enDispProcessMode) ? HI_TRUE : HI_FALSE;

    XDR_Policy_MaskDisplayChannel(HI_DRV_DISPLAY_0, bMaskSdChannel);

    if (pstDisp->stSetting.enOutputColorSpace != stDispInfo.eColorSpace)
    {
        pstDisp->bDispSettingChange = HI_FALSE;
        pstDisp->stSetting.enOutputColorSpace = stDispInfo.eColorSpace;
        pstDisp->bDispSettingChange = HI_TRUE;
    }

    /* update out_color_space and info GFX the disp mode(sdr or hdr) */
    DISP_XDR_UpdateDispInfo(pstDisp->enDisp, &stDispInfo);

    /* config hdmi info frame. */
    XDR_Process_SendHdmiInfoFrame(&stHdmiHdrAttr);

    pstDisp->stXdrPlayInfo.enPreWorkMode = enXdrWorkMode;
    pstDisp->stXdrPlayInfo.stPreHdmiHdrAttr = stHdmiHdrAttr;

    XDR_Debug_SetDispXdrProcInfo(pstDisp, pstWinShareInfo, enXdrWorkMode);

    WIN_SHARE_ResetShareInfo();

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
