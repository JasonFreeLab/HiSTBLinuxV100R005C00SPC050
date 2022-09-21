/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_xdr_adapter.c
Version       : Initial Draft
Author        : Hisilicon multimedia software  group
Created       : 2017/05/26
Last Modified :q00293180
Description   :
Function List :
History       :
******************************************************************************/
#include "drv_xdr_adapter.h"
#include "drv_pq_ext.h"
#include "drv_disp_xdr.h"
#include "drv_disp_bufcore.h"
#include "drv_disp_dolby.h"
#include "drv_disp_com.h"

#include "vdp_hal_chn.h"

#ifdef CFG_HI3798CV200
#include "vdp_drv_hihdr.h"
#include "vdp_drv_hdr.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


//==================extern function ================================
extern HI_BOOL  CheckFrameIs3D( HI_DRV_FRAME_TYPE_E  eFrmType);
extern HI_VOID GetSpecialLayerPriorty(HI_U32 u32layer_id, HI_U32 *pu32prio);

extern HI_VOID TransvertPixelFmt2CBB(HI_DRV_PIX_FORMAT_E *peInputPixelFmt, CBB_PIX_FORMAT_E  *peOutPixelFmt);
extern HI_S32  Internal_SelectTnrLocation(HI_PQ_ALGIP_SEL_E   enAlgIPSel);
extern HI_BOOL Internal_GetVidZmeOutFormatBasedOnP2IState(HI_U32 u32LayerNO, HI_BOOL bP2IOpen);


//=================transfer function for inner ==========================
HI_VOID JudgeCmpAndUvorderByPixFormat(HI_DRV_PIX_FORMAT_E ePixFormat,
                                      HI_BOOL  *pbUvorder,
                                      HI_BOOL  *pbCmpFmt,
                                      HI_BOOL  *pbLostCmp)
{
    /*since the cbb  has 3 params to describe:  cmp/uvorder/pixelfmt,  so we should
       * convert the enum value to the struct members.
       */
    if ((ePixFormat == HI_DRV_PIX_FMT_NV12)
        || (ePixFormat == HI_DRV_PIX_FMT_NV16_2X1)
        || (ePixFormat == HI_DRV_PIX_FMT_NV12_CMP))

    {
        *pbUvorder  = HI_TRUE;
    }
    else  if ((ePixFormat == HI_DRV_PIX_FMT_NV21)
              || (ePixFormat == HI_DRV_PIX_FMT_NV61_2X1)
              || (ePixFormat == HI_DRV_PIX_FMT_NV21_CMP)
              || (ePixFormat == HI_DRV_PIX_FMT_NV21_TILE)
              || (ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP))
    {
        *pbUvorder  = HI_FALSE;
    }
    else
    {
        *pbUvorder  = HI_FALSE;
    }


    /*since the cbb  has 3 params to describe:  cmp/uvorder/pixelfmt,  so we should
        *convert the enum value to the struct members.
        */

    if ((ePixFormat == HI_DRV_PIX_FMT_NV12_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV21_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV16_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV61_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV16_2X1_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV61_2X1_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
        || (ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP))
    {
        /*should open dcmp function in video layer.*/
        *pbCmpFmt   = HI_TRUE;
        *pbLostCmp  = HI_FALSE;
    }
    else
    {
        /*not compressed fmt.*/
        *pbCmpFmt   = HI_FALSE;
        *pbLostCmp  = HI_FALSE;
    }

    return;
}



HI_VOID ADAPTER_GetTnrDbDmInfo(WIN_INFO_S          *pstWinInfo,
                               HI_PQ_VDP_WBC_INFO_S *pstVdpLayerAlgInfor)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    switch (pstWinInfo->pCurrentFrame->enBitWidth)
    {
        case HI_DRV_PIXEL_BITWIDTH_8BIT:
            pstVdpLayerAlgInfor->u32BitDepth = 8;
            break;
        case HI_DRV_PIXEL_BITWIDTH_10BIT:
            pstVdpLayerAlgInfor->u32BitDepth = 10;
            break;
        case HI_DRV_PIXEL_BITWIDTH_12BIT:
            pstVdpLayerAlgInfor->u32BitDepth = 12;
            break;
        case HI_DRV_PIXEL_BITWIDTH_BUTT:
        default:
            break;
    }

    pstVdpLayerAlgInfor->stOriCoordinate  = pstWinInfo->pCurrentFrame->stDispRect;
    pstVdpLayerAlgInfor->stCropCoordinate = pstWinInfo->stIn;

    if (pstWinInfo->bTnrOnVdp)
    {
        pstVdpLayerAlgInfor->enAlgIPSel = HI_PQ_ALGIP_SEL_VDP;
    }
    else
    {
        pstVdpLayerAlgInfor->enAlgIPSel = HI_PQ_ALGIP_SEL_VPSS;
    }

    pstVdpLayerAlgInfor->bCropBeforeDB = HI_TRUE;
    pstVdpLayerAlgInfor->u32SingleModeFlag = 1;
    pstVdpLayerAlgInfor->u32ImageStruct = 0;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstWinInfo->pCurrentFrame->u32Priv;

    pstVdpLayerAlgInfor->u32ImageAvgQP = pstPriv->stDNRInfo.u32ImageAvgQP;
    pstVdpLayerAlgInfor->u32VdhInfoAddr = pstPriv->stDNRInfo.u32VdhInfoAddr;
    pstVdpLayerAlgInfor->u32VdhInfoStride = pstPriv->stDNRInfo.u32VdhInfoStride;

    pstVdpLayerAlgInfor->pstVdpWbcReg = (S_VPSSWB_REGS_TYPE *)pstWinInfo->stLayerAlgMmz.pu8StartVirAddr;
    pstVdpLayerAlgInfor->u32VdpWbcRegPhyAddr = pstWinInfo->stLayerAlgMmz.u32StartPhyAddr;

    pstVdpLayerAlgInfor->enVdecProtocol = HI_PQ_VDEC_PROTOCOL_H264;
    pstVdpLayerAlgInfor->enLayerId = pstWinInfo->u32LayerId;

    return;
}

HI_VOID ADAPTER_TransferAddrToHalAddr(HI_DRV_FRAME_TYPE_E eFrmType,
                                      HI_DRV_DISP_STEREO_E eDispMode,
                                      HI_BOOL       bRightEyeFirst,
                                      HI_BOOL       bDcmpEn,
                                      HI_DRV_VID_FRAME_ADDR_S *pstBufAddr,
                                      HI_DRV_VID_FRAME_ADDR_S *pstBufAddr_LB,
                                      VDP_ADDR_S          *pstAddr)
{
    HI_DRV_VID_FRAME_ADDR_S     stTmpBufAddr[HI_DRV_BUF_ADDR_MAX];
    HI_DRV_VID_FRAME_ADDR_S     stTmpBufAddr_LB[HI_DRV_BUF_ADDR_MAX];

    memset((HI_VOID *)&stTmpBufAddr[0], 0x0, sizeof(HI_DRV_VID_FRAME_ADDR_S) * HI_DRV_BUF_ADDR_MAX);
    memset((HI_VOID *)&stTmpBufAddr_LB[0], 0x0, sizeof(HI_DRV_VID_FRAME_ADDR_S) * HI_DRV_BUF_ADDR_MAX);

    if ( HI_TRUE == CheckFrameIs3D(eFrmType))
    {
        if (bRightEyeFirst)
        {
            stTmpBufAddr[0] = pstBufAddr[1];
            stTmpBufAddr_LB[0] = pstBufAddr_LB[1];
            stTmpBufAddr[1] = pstBufAddr[0];
            stTmpBufAddr_LB[1] = pstBufAddr_LB[0];
        }
        else
        {
            stTmpBufAddr[0] = pstBufAddr[0];
            stTmpBufAddr_LB[0] = pstBufAddr_LB[0];
            stTmpBufAddr[1] = pstBufAddr[1];
            stTmpBufAddr_LB[1] = pstBufAddr_LB[1];
        }
    }
    else
    {
        stTmpBufAddr[0] = pstBufAddr[0];
        stTmpBufAddr_LB[0] = pstBufAddr_LB[0];
    }

    pstAddr[VDP_ADDR_DATA].u32LumAddr = stTmpBufAddr[0].u32PhyAddr_Y;
    pstAddr[VDP_ADDR_DATA].u32ChmAddr = stTmpBufAddr[0].u32PhyAddr_C;
    pstAddr[VDP_ADDR_DATA].u32LumStr  = stTmpBufAddr[0].u32Stride_Y;
    pstAddr[VDP_ADDR_DATA].u32ChmStr  = stTmpBufAddr[0].u32Stride_C;

    if ( HI_TRUE == CheckFrameIs3D(eFrmType))
    {
        pstAddr[VDP_ADDR_3D].u32LumAddr = stTmpBufAddr[1].u32PhyAddr_Y;
        pstAddr[VDP_ADDR_3D].u32ChmAddr = stTmpBufAddr[1].u32PhyAddr_C;
        pstAddr[VDP_ADDR_3D].u32LumStr  = stTmpBufAddr[1].u32Stride_Y;
        pstAddr[VDP_ADDR_3D].u32ChmStr  = stTmpBufAddr[1].u32Stride_C;
    }
    else
    {
        if (DISP_STEREO_NONE == eDispMode)
        {
            pstAddr[VDP_ADDR_3D].u32LumAddr = 0;
            pstAddr[VDP_ADDR_3D].u32ChmAddr = 0;
            pstAddr[VDP_ADDR_3D].u32LumStr  = 0;
            pstAddr[VDP_ADDR_3D].u32ChmStr  = 0;
        }
        else
        {
            pstAddr[VDP_ADDR_3D].u32LumAddr = stTmpBufAddr[0].u32PhyAddr_Y;
            pstAddr[VDP_ADDR_3D].u32ChmAddr = stTmpBufAddr[0].u32PhyAddr_C;
            pstAddr[VDP_ADDR_3D].u32LumStr  = stTmpBufAddr[0].u32Stride_Y;
            pstAddr[VDP_ADDR_3D].u32ChmStr  = stTmpBufAddr[0].u32Stride_C;
        }
    }

    if (bDcmpEn)
    {
        pstAddr[VDP_ADDR_HEAD].u32LumAddr = stTmpBufAddr[0].u32PhyAddr_YHead;
        pstAddr[VDP_ADDR_HEAD].u32ChmAddr = stTmpBufAddr[0].u32PhyAddr_CHead;
        pstAddr[VDP_ADDR_HEAD].u32LumStr  = stTmpBufAddr[0].u32Head_Stride;
        pstAddr[VDP_ADDR_HEAD].u32DcmpHeadSize = stTmpBufAddr[0].u32Head_Size;
    }

    pstAddr[VDP_ADDR_TILE].u32LumAddr = stTmpBufAddr_LB[0].u32PhyAddr_Y;
    pstAddr[VDP_ADDR_TILE].u32ChmAddr = stTmpBufAddr_LB[0].u32PhyAddr_C;
    pstAddr[VDP_ADDR_TILE].u32LumStr  = stTmpBufAddr_LB[0].u32Stride_Y;
    pstAddr[VDP_ADDR_TILE].u32ChmStr  = stTmpBufAddr_LB[0].u32Stride_C;

    return;
}

#ifdef CFG_HI3798CV200
//*******************************function for hi3798cv200**************************

//******************************function for Hisi & Dolby****************************
HI_VOID ADAPTER_TransferBitWidth(HI_DRV_PIXEL_BITWIDTH_E enBitWidth,
                                 VDP_DATA_WTH      *penDataWidth)
{
    switch (enBitWidth)
    {
        case HI_DRV_PIXEL_BITWIDTH_8BIT :
        {
            *penDataWidth = VDP_DATA_WTH_8;
            break;
        }
        case HI_DRV_PIXEL_BITWIDTH_10BIT :
        {
            *penDataWidth = VDP_DATA_WTH_10;
            break;
        }
        default:
            DISP_ERROR("Invalid enBitWidth %d.\n", enBitWidth);
            *penDataWidth = VDP_DATA_WTH_10;
            break;
    }

    return;
}


HI_S32  ADAPTER_GetZmeStrategyFromPq(HI_U32 u32LayerId,
                                     HI_RECT_S stFrmInRect,
                                     HI_DRV_PIX_FORMAT_E enFrmPixFormat,
                                     HI_RECT_S stOutRect,
                                     HI_DISP_DISPLAY_INFO_S *pstDispInfo,
                                     HI_PQ_ZME_STRATEGY_OUT_U *punZmeOut)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_ZME_STRATEGY_IN_U  unZmeIn ;

    memset(&unZmeIn, 0x0, sizeof(HI_PQ_ZME_STRATEGY_IN_U));

    switch (enFrmPixFormat)
    {
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            // SP_420;
            unZmeIn.stLayerStrategy.u32FmtIn = 1;
            break;
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
            // SP_422;
            unZmeIn.stLayerStrategy.u32FmtIn = 0;
            break;
        default:
            unZmeIn.stLayerStrategy.u32FmtIn = 1;
            WIN_ERROR("Invalid pixel fmt %d.\n", enFrmPixFormat);
            break;
    }

    unZmeIn.stLayerStrategy.u32FrmWIn  = stFrmInRect.s32Width;
    unZmeIn.stLayerStrategy.u32FrmHIn  = stFrmInRect.s32Height;

    if (((pstDispInfo->bInterlace == 1)
         && (pstDispInfo->stFmtResolution.s32Width == 720 )
         && (pstDispInfo->stFmtResolution.s32Height == 576))
        || ((pstDispInfo->bInterlace == 1)
            && (pstDispInfo->stFmtResolution.s32Width == 720 )
            && (pstDispInfo->stFmtResolution.s32Height == 480)))
    {
        unZmeIn.stLayerStrategy.u32FrmWOut = stOutRect.s32Width * 2;
    }
    else
    {
        unZmeIn.stLayerStrategy.u32FrmWOut = stOutRect.s32Width;
    }

    unZmeIn.stLayerStrategy.u32FrmHOut = stOutRect.s32Height;

    if (HI_SUCCESS != (s32Ret = DRV_PQ_GetVdpZmeStrategy(u32LayerId, &unZmeIn, punZmeOut)))
    {
        HI_ERR_DISP("DRV_PQ_GetVdpZmeStrategy failed![Ret=%d]\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID ADAPTER_TransferZmeStrategy(HI_BOOL bMute,
                                    HI_PQ_ZME_STRATEGY_OUT_U *punPqZmeStrategy,
                                    VDP_VZME_DRV_PARA_S *pstCbbZmeStrategy,
                                    VDP_DRAW_MODE_E *penDrawMode,
                                    VDP_RECT_S      *pstZme2InRect)
{
    HI_BOOL bBtm = HI_FALSE;
    HI_U32  u32Vcnt = 0;

    if (bMute)
    {
        pstCbbZmeStrategy->bZmeFrmFmtIn  = HI_TRUE;
        pstCbbZmeStrategy->bZmeFrmFmtOut = HI_TRUE;
        pstCbbZmeStrategy->bZmeBFOut     = HI_FALSE;
        pstCbbZmeStrategy->bZmeBFIn      = HI_FALSE;
        pstZme2InRect->u32Wth = 0;
        pstZme2InRect->u32Hgt = 0;

        *penDrawMode = VDP_DRAW_MODE_1;
        return;
    }

    *penDrawMode = (HI_U32)punPqZmeStrategy->stStrategyLayerId.eVScalerMode;

    if (punPqZmeStrategy->stStrategyLayerId.u32ZmeNum == 2)
    {
        pstZme2InRect->u32Wth = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
        pstZme2InRect->u32Hgt = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else
    {
        pstZme2InRect->u32Wth = 0;
        pstZme2InRect->u32Hgt = 0;
    }

    pstCbbZmeStrategy->bZmeFirHL   = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL;
    pstCbbZmeStrategy->bZmeFirHC   = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC;
    pstCbbZmeStrategy->bZmeFirVL   = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL;
    pstCbbZmeStrategy->bZmeFirVC   = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC;
    pstCbbZmeStrategy->bZmeMedH    = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH;
    pstCbbZmeStrategy->bZmeMedV    = punPqZmeStrategy->stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV;
    pstCbbZmeStrategy->bZmeDefault = punPqZmeStrategy->stStrategyLayerId.bZmeDefault;

    pstCbbZmeStrategy->bZmeFrmFmtIn  = punPqZmeStrategy->stStrategyLayerId.bReadFmtIn;
    pstCbbZmeStrategy->bZmeFrmFmtOut = (VDP_DISP_GetDispMode(0) == 1) ? 1 : 0;

    /*get current t/b filed mode.*/
    VDP_DISP_GetVactState(0, &bBtm, &u32Vcnt);

    /*config next period's effective t/b field mode. */
    pstCbbZmeStrategy->bZmeBFOut = !bBtm;
    pstCbbZmeStrategy->bZmeBFIn  = !bBtm;

    return;
}



//****************************end function for Hisi & Dolby**************************

//generate hisi path hdr config.
HI_S32 ADAPTER_TransferWinInfoToHalCfg(WIN_INFO_S *pstWinInfo,
                                       VDP_LAYER_VID_INFO_S *pstVidInfo)
{
    VDP_DATA_RMODE_E eReadDataMode = VDP_RMODE_BUTT;
    HI_PQ_VDP_WBC_INFO_S stVdpLayerAlgInfor;
    CBB_PIX_FORMAT_E eOutPixelFmt = CBB_VID_IFMT_BUTT;

#ifdef  VDP_PQ_STRATEGY
    HI_PQ_ZME_STRATEGY_IN_U  stZmeIn ;
    HI_PQ_ZME_STRATEGY_OUT_U stZmeOut;

    HI_S32   s32Ret = HI_SUCCESS;
    HI_BOOL bBtm = HI_FALSE;
    HI_U32  u32Vcnt = 0;

    memset(&stZmeIn, 0x0, sizeof(HI_PQ_ZME_STRATEGY_IN_U));
    memset(&stZmeOut, 0x0, sizeof(HI_PQ_ZME_STRATEGY_OUT_U));
#endif

    memset(&stVdpLayerAlgInfor, 0x0, sizeof(HI_PQ_VDP_WBC_INFO_S));

    pstVidInfo->u32RegionNO    = pstWinInfo->u32RegionNo;
    GetSpecialLayerPriorty(pstWinInfo->u32LayerId, &pstVidInfo->u32LayerZorder);
    pstVidInfo->bRegionEn      = pstWinInfo->bRegionEnable;

    if ( ! pstWinInfo->u32Alpha)
    {
        pstVidInfo->u32Alpha = pstWinInfo->u32Alpha;
    }
    else
    {
        pstVidInfo->u32Alpha = (pstWinInfo->u32Alpha * LOGIC_MAX_ALPHA) / VDP_VIDEO_MAX_ALPHA;
    }

    if ( !pstWinInfo->u32AllAlpha)
    {
        pstVidInfo->u32AllAlpha = pstWinInfo->u32AllAlpha;
    }
    else
    {
        pstVidInfo->u32AllAlpha = (pstWinInfo->u32AllAlpha * LOGIC_MAX_ALPHA) / VDP_VIDEO_MAX_ALPHA;
    }


    if (VDP_LAYER_VID1 == pstWinInfo->u32LayerId)
    {
        pstVidInfo->bRegionModeEn = HI_TRUE;
    }
    else
    {
        pstVidInfo->bRegionModeEn = HI_FALSE;
    }


#ifdef  VDP_PQ_STRATEGY
    if (!pstWinInfo->bRegionMute && pstWinInfo->bRegionEnable)
    {
        DISP_ASSERT(HI_NULL != pstWinInfo->pCurrentFrame);

        TransvertPixelFmt2CBB(&pstWinInfo->pCurrentFrame->ePixFormat, &eOutPixelFmt);
        stZmeIn.stLayerStrategy.u32FmtIn   = eOutPixelFmt;
        stZmeIn.stLayerStrategy.u32FrmWIn  = pstWinInfo->stIn.s32Width;
        stZmeIn.stLayerStrategy.u32FrmHIn  = pstWinInfo->stIn.s32Height;

        if (((1 == pstWinInfo->pstDispInfo->bInterlace)
             && (720 == pstWinInfo->pstDispInfo->stFmtResolution.s32Width)
             && (576 == pstWinInfo->pstDispInfo->stFmtResolution.s32Height))
            || ((1 == pstWinInfo->pstDispInfo->bInterlace)
                && (720 == pstWinInfo->pstDispInfo->stFmtResolution.s32Width)
                && (480 == pstWinInfo->pstDispInfo->stFmtResolution.s32Height)))
        {
            stZmeIn.stLayerStrategy.u32FrmWOut = pstWinInfo->stVideo.s32Width * 2;
        }
        else
        {
            stZmeIn.stLayerStrategy.u32FrmWOut = pstWinInfo->stVideo.s32Width;
        }

        stZmeIn.stLayerStrategy.u32FrmHOut = pstWinInfo->stVideo.s32Height;

        if ((VDP_LAYER_VID0 == pstWinInfo->u32LayerId)
            || (VDP_LAYER_VID1 == pstWinInfo->u32LayerId))
        {
            if (HI_SUCCESS != (s32Ret = DRV_PQ_GetVdpZmeStrategy ((HI_PQ_ZME_LAYER_E)pstWinInfo->u32LayerId,
                                        &stZmeIn,
                                        &stZmeOut)))
            {
                DISP_ERROR("DRV_PQ_GetVdpZmeStrategy fail,Ret=[%d]\n", s32Ret);
                return s32Ret;
            }

            pstVidInfo->enDrawMode = (HI_U32)stZmeOut.stStrategyLayerId.eVScalerMode;

#if 0
            VDP_PRINT("---1 zme:%d,%d,%d,%d!\n", pstZmeOut.stStrategyLayerId.stZmeFmt[0].u32FrmInWidth,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[0].u32FrmInHeight,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[0].u32FrmOutWidth,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[0].u32FrmOutHeight);


            VDP_PRINT("---2 zme:%d,%d,%d,%d!\n", pstZmeOut.stStrategyLayerId.stZmeFmt[1].u32FrmInWidth,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[1].u32FrmInHeight,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[1].u32FrmOutWidth,
                      pstZmeOut.stStrategyLayerId.stZmeFmt[1].u32FrmOutHeight);
#endif
            /*only layer who has 2 scalers should set zme2. */
            if (stZmeOut.stStrategyLayerId.u32ZmeNum == 2)
            {
                pstVidInfo->stZme2InRect.u32Wth = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
                pstVidInfo->stZme2InRect.u32Hgt = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
            }
            else
            {
                pstVidInfo->stZme2InRect.u32Wth = 0;
                pstVidInfo->stZme2InRect.u32Hgt = 0;
            }

            ADAPTER_GetTnrDbDmInfo(pstWinInfo, &stVdpLayerAlgInfor);
            if (Internal_SelectTnrLocation(stVdpLayerAlgInfor.enAlgIPSel))
            {
                DISP_ERROR("Internal_SelectTnrLocation fail, Ret=[%d]\n", s32Ret);
                return HI_FAILURE;
            }

            DRV_PQ_SetVdpAlgCalcCfg(&stVdpLayerAlgInfor);

        }
        else
        {
            pstVidInfo->enDrawMode = VDP_DRAW_MODE_1;
            pstVidInfo->stZme2InRect.u32Wth = 0;
            pstVidInfo->stZme2InRect.u32Hgt = 0;
        }

        /*pass zme strategy to zme.*/
        pstVidInfo->stZmeDrvPara.bZmeFirHL   = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL;
        pstVidInfo->stZmeDrvPara.bZmeFirHC   = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC;
        pstVidInfo->stZmeDrvPara.bZmeFirVL   = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL;
        pstVidInfo->stZmeDrvPara.bZmeFirVC   = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC;
        pstVidInfo->stZmeDrvPara.bZmeMedH    = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH;
        pstVidInfo->stZmeDrvPara.bZmeMedV    = stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV;
        pstVidInfo->stZmeDrvPara.bZmeDefault = stZmeOut.stStrategyLayerId.bZmeDefault;

        pstVidInfo->stZmeDrvPara.bZmeFrmFmtIn  = stZmeOut.stStrategyLayerId.bReadFmtIn;
        pstVidInfo->stZmeDrvPara.bZmeFrmFmtOut = Internal_GetVidZmeOutFormatBasedOnP2IState(pstWinInfo->u32LayerId, HI_TRUE);

        /*set the layer's read  t/b mode, when dhd0 is progressive, the t/b config
         *is  useless. If dhd0 is interleave, the output mode is fixed to dhd0's opposite.
         * And the input mode forced to set to the output. since if input is p, the input mode is useless
         * and if input is interleave ,the input mode is the same to the output mode.
         */
        if ((VDP_LAYER_VID0 == pstWinInfo->u32LayerId)
            || (VDP_LAYER_VID1 == pstWinInfo->u32LayerId))
        {
            /*get current t/b filed mode.*/
            VDP_DISP_GetVactState(0, &bBtm, &u32Vcnt);

            /*config next period's effective t/b field mode. */
            pstVidInfo->stZmeDrvPara.bZmeBFOut = !bBtm;
            pstVidInfo->stZmeDrvPara.bZmeBFIn  = !bBtm;
        }
        else
        {
            pstVidInfo->stZmeDrvPara.bZmeBFOut = HI_FALSE;
            pstVidInfo->stZmeDrvPara.bZmeBFIn  = stZmeOut.stStrategyLayerId.bReadBFIn;
        }

        /* frame is interlace, this is for V3.*/
        if (HI_FALSE == pstWinInfo->pCurrentFrame->bProgressive)
        {
            if (HI_DRV_FIELD_TOP == pstWinInfo->pCurrentFrame->enFieldMode)
            {
                eReadDataMode = VDP_RMODE_TOP;
            }
            else
            {
                eReadDataMode = VDP_RMODE_BOTTOM;
            }
        }
        else
        {
            /*read frame.*/
            if (HI_TRUE == stZmeOut.stStrategyLayerId.bReadFmtIn)
            {
                eReadDataMode = VDP_RMODE_PROGRESSIVE;
            }
            else
            {
                eReadDataMode = VDP_RMODE_INTERFACE;
            }
        }
    }
    else
    {
        //frame is null or layer is disable.
        pstVidInfo->stZmeDrvPara.bZmeFrmFmtIn     = HI_TRUE;
        pstVidInfo->stZmeDrvPara.bZmeFrmFmtOut   = HI_TRUE;
        pstVidInfo->stZmeDrvPara.bZmeBFOut        = HI_FALSE;
        pstVidInfo->stZmeDrvPara.bZmeBFIn         = HI_FALSE;
        pstVidInfo->stZme2InRect.u32Wth  =    0;
        pstVidInfo->stZme2InRect.u32Hgt  =    0;

        pstVidInfo->enDrawMode = VDP_DRAW_MODE_1;

        if (1 == pstWinInfo->pstDispInfo->bInterlace)
        {
            eReadDataMode = VDP_RMODE_INTERLACE;
        }
        else
        {
            eReadDataMode = VDP_RMODE_PROGRESSIVE;
        }
        //  printk("mute-layer%d-r-%d---F--%d\n",pLayerCfgBasePara->u32LayerNO,pstZmeOut.stStrategyLayerId.bReadFmtIn,pLayerCfgBasePara->stFrame.bFrameInterlace);
    }
#else
    {
        // CBB  process  add by hyx
        pstVidInfo->stZmeDrvPara.bZmeFrmFmtIn  = HI_TRUE;
        pstVidInfo->stZmeDrvPara.bZmeFrmFmtOut = HI_TRUE;
        pstVidInfo->stZmeDrvPara.bZmeBFOut     = HI_FALSE;
        pstVidInfo->stZmeDrvPara.bZmeBFIn      = HI_FALSE;
        pstVidInfo->stZme2InRect.u32Wth = 0;
        pstVidInfo->stZme2InRect.u32Hgt = 0;

        pstVidInfo->enDrawMode = VDP_DRAW_MODE_1;

        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            if (HI_FALSE == pstWinInfo->pCurrentFrame->bProgressive)
            {
                if (HI_DRV_FIELD_TOP == pstWinInfo->pCurrentFrame->enFieldMode)
                {
                    eReadDataMode = VDP_RMODE_TOP;
                }
                else
                {
                    eReadDataMode = VDP_RMODE_BOTTOM;
                }
            }
            else
            {
                eReadDataMode  =  VDP_RMODE_PROGRESSIVE;
            }
        }
        else
        {
            eReadDataMode = VDP_RMODE_PROGRESSIVE;
        }
    }
#endif

    pstVidInfo->enReadMode = eReadDataMode;

    if (pstVidInfo->bRegionEn == HI_TRUE)
    {
        pstVidInfo->bFlipEn            = pstWinInfo->bFlipEn;

        pstVidInfo->stCropRect.u32X    = (HI_U32)(pstWinInfo->stIn.s32X);
        pstVidInfo->stCropRect.u32Y    = (HI_U32)(pstWinInfo->stIn.s32Y);
        pstVidInfo->stCropRect.u32Wth  = pstWinInfo->stIn.s32Width;
        pstVidInfo->stCropRect.u32Hgt  = pstWinInfo->stIn.s32Height;

        pstVidInfo->stVideoRect.u32X   = (HI_U32)(pstWinInfo->stVideo.s32X);
        pstVidInfo->stVideoRect.u32Y   = (HI_U32)(pstWinInfo->stVideo.s32Y);
        pstVidInfo->stVideoRect.u32Wth = pstWinInfo->stVideo.s32Width;
        pstVidInfo->stVideoRect.u32Hgt = pstWinInfo->stVideo.s32Height;

        pstVidInfo->stDispRect.u32X    = (HI_U32)(pstWinInfo->stDisp.s32X);
        pstVidInfo->stDispRect.u32Y    = (HI_U32)(pstWinInfo->stDisp.s32Y);
        pstVidInfo->stDispRect.u32Wth  = pstWinInfo->stDisp.s32Width;
        pstVidInfo->stDispRect.u32Hgt  = pstWinInfo->stDisp.s32Height;

        pstVidInfo->enInClrSpace       = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enInCsc);
        pstVidInfo->enOutClrSpace      = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enOutCsc);

        pstVidInfo->enDispMode         = XDR_DISPMODE_TRANSFER(pstWinInfo->pstDispInfo->eDispMode);
        pstVidInfo->stVdpDispInfo.enDispMode = pstVidInfo->enDispMode;

        pstVidInfo->stVdpDispInfo.bInterlace  = pstWinInfo->pstDispInfo->bInterlace;
        pstVidInfo->stVdpDispInfo.stFmtResolution.u32X   = pstWinInfo->pstDispInfo->stFmtResolution.s32X;
        pstVidInfo->stVdpDispInfo.stFmtResolution.u32Y   = pstWinInfo->pstDispInfo->stFmtResolution.s32Y;
        pstVidInfo->stVdpDispInfo.stFmtResolution.u32Wth = pstWinInfo->pstDispInfo->stFmtResolution.s32Width;
        pstVidInfo->stVdpDispInfo.stFmtResolution.u32Hgt = pstWinInfo->pstDispInfo->stFmtResolution.s32Height;
        pstVidInfo->stVdpDispInfo.stFmtResolution.u32SX  = 0;

        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            HI_BOOL bUvorder = HI_FALSE, bCmpFmt = HI_FALSE, bLostCmp = HI_FALSE;

            pstVidInfo->stSrcInfo.enSrc3dMode = XDR_FRM_TYPE_TRANSFER(pstWinInfo->pCurrentFrame->eFrmType);

            pstVidInfo->stSrcInfo.bSecureEn   = pstWinInfo->pCurrentFrame->bSecure;

#ifdef  CFG_VDP_MMU_SUPPORT
            pstVidInfo->stSrcInfo.bSmmuEn = HI_TRUE;
#else
            pstVidInfo->stSrcInfo.bSmmuEn = HI_FALSE;
#endif
            JudgeCmpAndUvorderByPixFormat(pstWinInfo->pCurrentFrame->ePixFormat,
                                          &bUvorder, &bCmpFmt, &bLostCmp);

            pstVidInfo->stSrcInfo.bUvOrder = bUvorder;
            pstVidInfo->stSrcInfo.bDcmpEn  = bCmpFmt;
            pstVidInfo->stSrcInfo.bDcmpLost = bLostCmp;
            pstVidInfo->stSrcInfo.enInFmt  = XDR_PIXEL_FMT_TRANSFER(pstWinInfo->pCurrentFrame->ePixFormat);

            ADAPTER_TransferBitWidth(pstWinInfo->pCurrentFrame->enBitWidth,
                                     &pstVidInfo->stSrcInfo.enDataWidth);

            pstVidInfo->stSrcInfo.bSrcIsInterlace = (HI_TRUE == pstWinInfo->pCurrentFrame->bProgressive) ? HI_FALSE : HI_TRUE;

            pstVidInfo->stSrcInfo.stSrcRect.u32X   = 0;
            pstVidInfo->stSrcInfo.stSrcRect.u32Y   = 0;
            pstVidInfo->stSrcInfo.stSrcRect.u32Wth = pstWinInfo->pCurrentFrame->u32Width;
            pstVidInfo->stSrcInfo.stSrcRect.u32Hgt = pstWinInfo->pCurrentFrame->u32Height;

            ADAPTER_TransferAddrToHalAddr(pstWinInfo->pCurrentFrame->eFrmType,
                                          pstWinInfo->pstDispInfo->eDispMode,
                                          pstWinInfo->pstDispInfo->bRightEyeFirst,
                                          bCmpFmt,
                                          &pstWinInfo->pCurrentFrame->stBufAddr[0],
                                          &pstWinInfo->pCurrentFrame->stBufAddr_LB[0],
                                          &pstVidInfo->stSrcInfo.stAddr[0]);

        }
        else
        {
            pstVidInfo->stSrcInfo.enSrc3dMode = VDP_DISP_MODE_2D;

        }

        pstVidInfo->u32DepthLevel = 0;

    }


    pstVidInfo->stSrcInfo.enSrcClrSpace = pstVidInfo->enInClrSpace;
    pstVidInfo->bMuteEn              = pstWinInfo->bRegionMute;
    pstVidInfo->stMuteColor.u32BkgY  = 0x40;
    pstVidInfo->stMuteColor.u32BkgU  = 0x200;
    pstVidInfo->stMuteColor.u32BkgV  = 0x200;
    pstVidInfo->stMuteColor.u32BkgA  = 0xff;
    pstVidInfo->stLetterBoxColor     = pstVidInfo->stMuteColor;

    pstVidInfo->stMixvColor.u32BkgA  = 0xff;
    pstVidInfo->stMixvColor.u32BkgY  = pstWinInfo->pstDispInfo->u32Kr;
    pstVidInfo->stMixvColor.u32BkgU  = pstWinInfo->pstDispInfo->u32Kg;
    pstVidInfo->stMixvColor.u32BkgV  = pstWinInfo->pstDispInfo->u32Kb;

    return HI_SUCCESS;
}

HI_VOID ADAPTER_CloseV0V1Layer(HI_VOID)
{
    HI_U32  u32Index = 0;
    VDP_LAYER_VID_INFO_S stVidInfo;

    memset(&stVidInfo, 0x0, sizeof(VDP_LAYER_VID_INFO_S));

    stVidInfo.bRegionModeEn = HI_FALSE;
    stVidInfo.u32RegionNO   = 0;
    stVidInfo.bRegionEn     = HI_FALSE;
    stVidInfo.bEnable       = HI_FALSE;
    stVidInfo.bMuteEn       = HI_TRUE;

    //close v0.
    VDP_DRV_SetVidLayer(VDP_LAYER_VID0, &stVidInfo);
    //close v1.
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER - 1; u32Index++)
    {
        stVidInfo.bRegionModeEn = HI_FALSE;
        stVidInfo.bRegionEn     = HI_FALSE;
        stVidInfo.bEnable       = HI_FALSE;
        stVidInfo.bMuteEn       = HI_TRUE;
        stVidInfo.u32RegionNO = u32Index;
        VDP_DRV_SetVidLayer(VDP_LAYER_VID1, &stVidInfo);
    }

    return;
}



HI_VOID ADAPTER_SetLayerCfg(HI_U32 u32LayerId,
                            WIN_INFO_S *pstWinInfo,
                            HI_BOOL *pbVdmArray,
                            HI_BOOL bConfigWholeLayer)
{
    VDP_LAYER_VID_INFO_S stVidInfo;

    if ((u32LayerId >= VDP_LAYER_VID4)
        || (pstWinInfo->u32RegionNo >= 16)
       )
    {
        return;
    }

    memset(&stVidInfo, 0x0, sizeof(VDP_LAYER_VID_INFO_S));

    if (HI_SUCCESS == ADAPTER_TransferWinInfoToHalCfg(pstWinInfo, &stVidInfo))
    {
        VDP_DRV_SetVidLayer(u32LayerId, &stVidInfo);
    }

    return;
}

//**************************Hisi Path*******************************************
//******************************************************************************
HI_VOID ADAPTER_TransferToHalReso(HI_RECT_S *pstDrvReso, VDP_RECT_S *pstHalReso)
{
    pstHalReso->u32X    = pstDrvReso->s32X;
    pstHalReso->u32Y    = pstDrvReso->s32Y;
    pstHalReso->u32Wth  = pstDrvReso->s32Width;
    pstHalReso->u32Hgt  = pstDrvReso->s32Height;
    return ;
}

HI_VOID ADAPTER_TransferToHalAddr(HI_DRV_VID_FRAME_ADDR_S *pstDrvAddr,
                                  VDP_ADDR_S              *pstCbbAddr,
                                  HI_BOOL                  bHeaderAddr,
                                  HI_BOOL                  bSecure,
                                  HI_BOOL                  bSmmu)
{
    if (HI_FALSE == bHeaderAddr)
    {
        pstCbbAddr->u32LumAddr = pstDrvAddr->u32PhyAddr_Y;
        pstCbbAddr->u32LumStr  = pstDrvAddr->u32Stride_Y;
        pstCbbAddr->u32ChmAddr = pstDrvAddr->u32PhyAddr_C;
        pstCbbAddr->u32ChmStr  = pstDrvAddr->u32Stride_C;
    }
    else
    {
        pstCbbAddr->u32LumAddr = pstDrvAddr->u32PhyAddr_YHead;
        pstCbbAddr->u32ChmAddr = pstDrvAddr->u32PhyAddr_CHead;
        pstCbbAddr->u32LumStr = pstDrvAddr->u32Head_Stride;
        pstCbbAddr->u32DcmpHeadSize = pstDrvAddr->u32Head_Size;

    }
    pstCbbAddr->bSecure        = bSecure;
    pstCbbAddr->bSmmu          = bSmmu;

    return ;
}


HI_VOID ADAPTER_GetHiHdrMode(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                             HI_DRV_DISP_OUT_TYPE_E enDispType,
                             VDP_HIHDR_CFG_MODE_E *penHdrMode)
{
    switch (enFrmType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            switch (enDispType)
            {
                case HI_DRV_DISP_TYPE_NORMAL:
                    *penHdrMode = VDP_HIHDR_HDR10_IN_SDR_OUT;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                    *penHdrMode = VDP_HIHDR_HDR10_IN_HDR10_OUT;
                    break;
                default:
                    DISP_ERROR("Unsupport mode.\n");
                    *penHdrMode = VDP_HIHDR_HDR10_IN_SDR_OUT;
                    break;
            }
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            switch (enDispType)
            {
                case HI_DRV_DISP_TYPE_NORMAL:
                    *penHdrMode = VDP_HIHDR_HLG_IN_SDR_OUT;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                    *penHdrMode = VDP_HIHDR_HLG_IN_HDR10_OUT;
                    break;
                default:
                    DISP_ERROR("Unsupport mode.\n");
                    *penHdrMode = VDP_HIHDR_HLG_IN_SDR_OUT;
                    break;
            }
            break;
        default:
            DISP_ERROR("Unsupport mode.\n");
            break;
    }

    return;
}

HI_VOID ADAPTER_TransferWinInfoToHiHdrCfg(WIN_INFO_S *pstWinInfo, VDP_HISI_HDR_CFG_S *pstHdrCfg)
{
    HI_BOOL  bUvorder = HI_FALSE, bCmpFmt = HI_FALSE, bLostCmp = HI_FALSE;
    pstHdrCfg->bGfxEn = HI_TRUE;
    pstHdrCfg->bMuteEn = pstWinInfo->bRegionMute;

#ifdef CFG_VDP_MMU_SUPPORT
    pstHdrCfg->bSmmuEn = HI_TRUE;
#else
    pstHdrCfg->bSmmuEn = HI_FALSE;
#endif

    pstHdrCfg->bPreMult = HI_FALSE;

    if ((pstWinInfo->pstDispInfo->eFmt >= HI_DRV_DISP_FMT_PAL)
        && (pstWinInfo->pstDispInfo->eFmt <= HI_DRV_DISP_FMT_1440x480i_60))
    {
        pstHdrCfg->bFlag480I576I = HI_TRUE;
    }
    else
    {
        pstHdrCfg->bFlag480I576I = HI_FALSE;
    }

    pstHdrCfg->bSecureEn = pstWinInfo->pCurrentFrame->bSecure;

    ADAPTER_GetHiHdrMode(pstWinInfo->pCurrentFrame->enSrcFrameType,
                         pstWinInfo->enOutType,
                         &pstHdrCfg->enHdrMode);

    ADAPTER_TransferBitWidth(pstWinInfo->pCurrentFrame->enBitWidth,
                             &pstHdrCfg->u32DataWidth);

    pstHdrCfg->enInClr  = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enInCsc);
    pstHdrCfg->enOutClr = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enOutCsc);
    pstHdrCfg->enVidIFmt = XDR_PIXEL_FMT_TRANSFER(pstWinInfo->pCurrentFrame->ePixFormat);
    ADAPTER_TransferToHalReso(&pstWinInfo->pCurrentFrame->stDispRect,
                              &pstHdrCfg->stVidInReso);
    ADAPTER_TransferToHalReso(&pstWinInfo->stDisp,
                              &pstHdrCfg->stVidOutReso);

    JudgeCmpAndUvorderByPixFormat(pstWinInfo->pCurrentFrame->ePixFormat,
                                  &bUvorder, &bCmpFmt, &bLostCmp);

    pstHdrCfg->bDcmpEn = bCmpFmt;

    ADAPTER_TransferToHalAddr(&pstWinInfo->pCurrentFrame->stBufAddr[0],
                              &pstHdrCfg->stVidAddr,
                              HI_FALSE,
                              pstWinInfo->pCurrentFrame->bSecure,
                              pstHdrCfg->bSmmuEn);

    ADAPTER_TransferToHalAddr(&pstWinInfo->pCurrentFrame->stBufAddr_LB[0],
                              &pstHdrCfg->stVidAddr_2LowBit,
                              HI_FALSE,
                              pstWinInfo->pCurrentFrame->bSecure,
                              pstHdrCfg->bSmmuEn);

    if (bCmpFmt)
    {
        ADAPTER_TransferToHalAddr(&pstWinInfo->pCurrentFrame->stBufAddr[0],
                                  &pstHdrCfg->stHeadAddr,
                                  HI_TRUE,
                                  pstWinInfo->pCurrentFrame->bSecure,
                                  pstHdrCfg->bSmmuEn);
    }

    return;
}

HI_VOID ADAPTER_SetHisiMode(HI_U32      u32LayerId,
                            WIN_INFO_S *pstWinInfo)
{
    HI_PQ_HDR_CFG   *pstPqHdrCfg = HI_NULL;
    DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;
    VDP_HISI_HDR_CFG_S stHdrCfg;

    memset(&stHdrCfg, 0x0, sizeof(VDP_HISI_HDR_CFG_S));

    //null frm
    if (HI_NULL == pstWinInfo->pCurrentFrame)
    {
        VDP_DRV_HiSiHdrMute(HI_TRUE);
    }
    else
    {
        pstDispBufNode = container_of((HI_U32 *)pstWinInfo->pCurrentFrame, DISP_BUF_NODE_S, u32Data[0]);
        pstPqHdrCfg = (HI_PQ_HDR_CFG *)pstDispBufNode->u8Metadata;

        ADAPTER_TransferWinInfoToHiHdrCfg(pstWinInfo, &stHdrCfg);

        VDP_DRV_SetHisiHdrMode(&stHdrCfg , pstPqHdrCfg);
    }

    return;
}


//=======================dolby process functions======================
#ifdef VDP_DOLBY_HDR_SUPPORT
HI_BOOL ADAPTER_IsLastDolbyFrame(HI_DRV_VIDEO_FRAME_S *pstCurrentFrm,
                                 HI_DRV_VIDEO_FRAME_S *pstNextFrm)
{
    HI_BOOL bLastFrm = HI_FALSE;
    HI_DRV_VIDEO_PRIVATE_S *pstPrivInfo = HI_NULL;
    DISP_BUF_NODE_S *pstDispBufNextNode = HI_NULL;

    if ((HI_NULL == pstCurrentFrm) || (HI_NULL == pstNextFrm))
    {
        return HI_FALSE;
    }

    pstPrivInfo = (HI_DRV_VIDEO_PRIVATE_S *)(pstCurrentFrm->u32Priv);
    pstDispBufNextNode = container_of((HI_U32 *)pstNextFrm, DISP_BUF_NODE_S, u32Data[0]);

    if ((HI_DRV_DISP_TYPE_DOLBY != pstDispBufNextNode->stHdrInfo.enDispOutType)
        || (pstPrivInfo->u32LastFlag))
    {
        bLastFrm = HI_TRUE;
    }
    else
    {
        bLastFrm = HI_FALSE;
    }

    return bLastFrm;

}

HI_VOID ADAPTER_SetUpdateMetadata(HI_DRV_DISP_OUT_TYPE_E enOutType,
                                  HI_DRV_VIDEO_FRAME_S   *pCurrentFrame,
                                  HI_DRV_VIDEO_FRAME_S   *pNextFrame,
                                  HI_U8                  *pu8MdBuf,
                                  HI_U32                  u32MdLen)
{
    DOLBY_MD_HEADER_S  stMdHeader;

    memset(&stMdHeader, 0x0, sizeof(DOLBY_MD_HEADER_S));

    /* Needn't update when output signal is not DolbyVision.*/
    if (HI_DRV_DISP_TYPE_DOLBY != enOutType)
    {
        return;
    }

    stMdHeader.u32MdId = pu8MdBuf[0];

    if (ADAPTER_IsLastDolbyFrame(pCurrentFrame, pNextFrame))
    {
        stMdHeader.bEos = HI_TRUE;
    }
    else
    {
        stMdHeader.bEos = HI_FALSE;
    }

    stMdHeader.bNoMd = HI_FALSE;
    stMdHeader.u8MdVer = HEADER_MD_VER;
    stMdHeader.u8MdType = HEADER_MD_TYPE;

    VDP_DRV_SetHdrHdmiMetadata((HI_U8 *)&stMdHeader, u32MdLen, pu8MdBuf);

    return;
}

HI_VOID ADAPTER_GetDolbyMode(HI_DRV_VIDEO_FRAME_S  *pstFrame,
                             HI_DRV_DISP_OUT_TYPE_E enDispType,
                             VDP_HDR_CFG_MODE_E *penHdrMode)
{
    HI_BOOL bCompatible = HI_FALSE;

    bCompatible = pstFrame->unHDRInfo.stDolbyInfo.bCompatible;

    switch (pstFrame->enSrcFrameType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_SDR:
            switch (enDispType)
            {
                    /*******NOT SUPPORT**********
                                case HI_DRV_DISP_TYPE_NORMAL:
                                    *penHdrMode = ;
                                    break;
                                case HI_DRV_DISP_TYPE_SDR_CERT:
                                    *penHdrMode = ;
                                    break;
                              *******************************/
                case HI_DRV_DISP_TYPE_HDR10:
                    *penHdrMode = VDP_HDR_V2P3_SDR_IN_HDR10_OUT;
                    break;
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                    *penHdrMode = VDP_HDR_V2P3_SDR_IN_HDR10_OUT_CERT;
                    break;
                case HI_DRV_DISP_TYPE_DOLBY:
                    *penHdrMode = VDP_HDR_V2P3_SDR_IN_DOLBY_OUT;
                    break;
                default:
                    DISP_ERROR("SDR Frm. Unsupport out mode.\n");
                    break;
            }
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            switch (enDispType)
            {
                case HI_DRV_DISP_TYPE_NORMAL:
                    *penHdrMode = VDP_HDR_V2P3_HDR10_IN_SDR_OUT;
                    break;
                case HI_DRV_DISP_TYPE_SDR_CERT:
                    *penHdrMode = VDP_HDR_V2P3_HDR10_IN_SDR_OUT_CERT;
                    break;
                case HI_DRV_DISP_TYPE_HDR10:
                    *penHdrMode = VDP_HDR_V2P3_HDR10_IN_HDR10_OUT;
                    break;
                case HI_DRV_DISP_TYPE_HDR10_CERT:
                    *penHdrMode = VDP_HDR_V2P3_HDR10_IN_HDR10_OUT_CERT;
                    break;
                case HI_DRV_DISP_TYPE_DOLBY:
                    *penHdrMode = VDP_HDR_V2P3_HDR10_IN_DOLBY_OUT;
                    break;
                default:
                    DISP_ERROR("HDR10 Frm. Unsupport out mode.\n");
                    break;
            }
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL:
            if (bCompatible)
            {
                switch (enDispType)
                {
                    case HI_DRV_DISP_TYPE_NORMAL:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_BC_IN_SDR_OUT;
                        break;
                    case HI_DRV_DISP_TYPE_SDR_CERT:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_BC_IN_SDR_OUT_CERT;
                        break;
                    case HI_DRV_DISP_TYPE_HDR10:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_BC_IN_HDR10_OUT;
                        break;
                    case HI_DRV_DISP_TYPE_HDR10_CERT:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_BC_IN_HDR10_OUT_CERT;
                        break;
                    case HI_DRV_DISP_TYPE_DOLBY:
                        //Dolby ONLY has IPT out.
                        *penHdrMode = VDP_HDR_V2P3_DOVI_BC_IN_DOVI_IPT_OUT;
                        break;
                    default:
                        DISP_ERROR("BC Dolby Frm. Unsupport out mode.\n");
                        break;
                }
            }
            else
            {
                switch (enDispType)
                {
                    case HI_DRV_DISP_TYPE_NORMAL:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_NBC_IN_SDR_OUT;
                        break;
                    case HI_DRV_DISP_TYPE_SDR_CERT:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_NBC_IN_SDR_OUT_CERT;
                        break;
                    case HI_DRV_DISP_TYPE_HDR10:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_NBC_IN_HDR10_OUT;
                        break;
                    case HI_DRV_DISP_TYPE_HDR10_CERT:
                        *penHdrMode = VDP_HDR_V2P3_DOVI_NBC_IN_HDR10_OUT_CERT;
                        break;
                    case HI_DRV_DISP_TYPE_DOLBY:
                        //Dolby ONLY has IPT out.
                        *penHdrMode = VDP_HDR_V2P3_DOVI_NBC_IN_DOVI_IPT_OUT;
                        break;
                    default:
                        DISP_ERROR("NBC Dolby Frm. Unsupport out mode.\n");
                        break;
                }
            }
            break;
        default:
            DISP_ERROR("Unknown frame type.Unsupport mode.\n");
            break;
    }

    return;
}

HI_VOID ADAPER_TransferWinInfoToDolbyCfg(WIN_INFO_S *pstWinInfo,
        VDP_HDR_CFG_S *pstHdrCfg)
{
    HI_DRV_VIDEO_FRAME_S  *pstBlFrm = HI_NULL;
    HI_DRV_VIDEO_FRAME_S  *pstElFrm = HI_NULL;
    DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;
    HI_BOOL  bUvorder = HI_FALSE, bCmpFmt = HI_FALSE, bLostCmp = HI_FALSE;

#ifdef  VDP_PQ_STRATEGY
    HI_PQ_ZME_STRATEGY_OUT_U stZmeOut;
    memset(&stZmeOut, 0x0, sizeof(HI_PQ_ZME_STRATEGY_OUT_U));
#endif

    pstBlFrm = pstWinInfo->pCurrentFrame;
    pstDispBufNode = container_of((HI_U32 *)pstBlFrm, DISP_BUF_NODE_S, u32Data[0]);

    //if frame is null.
    if (HI_NULL == pstBlFrm)
    {
        pstHdrCfg->bMuteEn = HI_TRUE;
    }
    else
    {
        pstHdrCfg->bGfxEn = HI_TRUE;
        pstHdrCfg->bMuteEn = pstWinInfo->bRegionMute;
#ifdef CFG_VDP_MMU_SUPPORT
        pstHdrCfg->bSmmuEn = HI_TRUE;
#else
        pstHdrCfg->bSmmuEn = HI_FALSE;
#endif
        pstHdrCfg->bPreMult = HI_FALSE;

        DISP_ASSERT(HI_NULL != pstWinInfo->pstDispInfo);

        if ((pstWinInfo->pstDispInfo->eFmt >= HI_DRV_DISP_FMT_PAL)
            && (pstWinInfo->pstDispInfo->eFmt <= HI_DRV_DISP_FMT_1440x480i_60))
        {
            pstHdrCfg->bFlag480I576I = HI_TRUE;
        }
        else
        {
            pstHdrCfg->bFlag480I576I = HI_FALSE;
        }

        pstHdrCfg->bSecureEn = pstBlFrm->bSecure;

        ADAPTER_GetDolbyMode(pstBlFrm,
                             pstWinInfo->enOutType,
                             &pstHdrCfg->enHdrMode);

        ADAPTER_TransferBitWidth(pstBlFrm->enBitWidth,
                                 &pstHdrCfg->u32DataWidth);

        if (pstDispBufNode->bValidData2)
        {
            pstElFrm = (HI_DRV_VIDEO_FRAME_S *)pstDispBufNode->u32Data2;
            pstHdrCfg->enVdpElVidIFmt = XDR_PIXEL_FMT_TRANSFER(pstElFrm->ePixFormat);

            ADAPTER_TransferToHalAddr(&pstElFrm->stBufAddr[0],
                                      &pstHdrCfg->stElAddr,
                                      HI_FALSE,
                                      pstElFrm->bSecure,
                                      pstHdrCfg->bSmmuEn);

            ADAPTER_TransferToHalReso(&pstElFrm->stDispRect, &pstHdrCfg->stElReso);

            /*****************************************************
                    |if EL reso is not equal to outRect,mute it
                    ******************************************************/
            if ((pstElFrm->stDispRect.s32Width != pstWinInfo->stDisp.s32Width)
                || (pstElFrm->stDispRect.s32Height != pstWinInfo->stDisp.s32Height))
            {

                if ((pstElFrm->stDispRect.s32Width == (pstWinInfo->stDisp.s32Width / 2) )
                    && (pstElFrm->stDispRect.s32Height == (pstWinInfo->stDisp.s32Height / 2) )
                   )
                {
                    pstHdrCfg->bMuteEn = HI_FALSE;
                }
                else
                {
                    pstHdrCfg->bMuteEn  = HI_TRUE;
                }
            }
        }

        pstHdrCfg->enVdpBlVidIFmt = XDR_PIXEL_FMT_TRANSFER(pstBlFrm->ePixFormat);

#ifdef  VDP_PQ_STRATEGY
        //zme strategy here.
        ADAPTER_GetZmeStrategyFromPq(pstWinInfo->u32LayerId,
                                     pstBlFrm->stDispRect,
                                     pstBlFrm->ePixFormat,
                                     pstWinInfo->stDisp,
                                     pstWinInfo->pstDispInfo,
                                     &stZmeOut);

        ADAPTER_TransferZmeStrategy(pstWinInfo->bRegionMute,
                                    &stZmeOut,
                                    &pstHdrCfg->stZmeDrvPara,
                                    &pstHdrCfg->enDrawMode,
                                    &pstHdrCfg->stZme2InRect);

#else
        // TODO:
#endif
        ADAPTER_TransferToHalReso(&pstBlFrm->stDispRect, &pstHdrCfg->stVidReso);
        ADAPTER_TransferToHalReso(&pstWinInfo->stDisp, &pstHdrCfg->stBlReso);
        ADAPTER_TransferToHalReso(&pstWinInfo->pstDispInfo->stFmtResolution,
                                  &pstHdrCfg->stFmtResolution);

        ADAPTER_TransferToHalAddr(&pstBlFrm->stBufAddr[0],
                                  &pstHdrCfg->stBlAddr,
                                  HI_FALSE,
                                  pstBlFrm->bSecure,
                                  pstHdrCfg->bSmmuEn);

        ADAPTER_TransferToHalAddr(&pstBlFrm->stBufAddr_LB[0],
                                  &pstHdrCfg->stBlAddr_2LowBit,
                                  HI_FALSE,
                                  pstBlFrm->bSecure,
                                  pstHdrCfg->bSmmuEn);

        JudgeCmpAndUvorderByPixFormat(pstBlFrm->ePixFormat,
                                      &bUvorder, &bCmpFmt, &bLostCmp);
        pstHdrCfg->bDcmpEn = bCmpFmt;
        if (bCmpFmt)
        {
            ADAPTER_TransferToHalAddr(&pstBlFrm->stBufAddr[0],
                                      &pstHdrCfg->stHeadAddr,
                                      HI_TRUE,
                                      pstBlFrm->bSecure,
                                      pstHdrCfg->bSmmuEn);
        }

    }

    return;
}

static VDP_HDR_CFG_S g_stHalHdrCfg = {0};
HI_VOID ADAPTER_SetDolbyCfg(WIN_INFO_S *pstWinInfo, DRV_DISP_DOLBY_PLAY_INFO_S *pstDolbyInfo)
{
    //step1. transfer to hal cfg. NOTE: null frame may carefully process.
    ADAPER_TransferWinInfoToDolbyCfg(pstWinInfo, &g_stHalHdrCfg);

    //step2. config logic path.
    VDP_DRV_SetHdrMode(&g_stHalHdrCfg,
                       &pstDolbyInfo->stDolbyCoeff.stCompCfg,
                       &pstDolbyInfo->stDolbyCoeff.stDmKs);

    //step3. process update metadata when output dolby signal.
    ADAPTER_SetUpdateMetadata(pstWinInfo->enOutType,
                              pstWinInfo->pCurrentFrame,
                              pstWinInfo->pNextFrame,
                              &pstDolbyInfo->stDolbyCoeff.u8MdBuf[0],
                              pstDolbyInfo->stDolbyCoeff.u32UpMdLen);

    return;
}



#endif

#else
//************************function for other chips except hi3798cv200*****************
HI_S32 ADAPTER_GetZmeCfgFromPq(WIN_INFO_S *pstWinInfo,
                               XDP_LAYER_VID_INFO_S *pstVidInfo)
{
#ifdef  VDP_PQ_STRATEGY

    HI_PQ_ZME_STRATEGY_IN_U  stZmeIn ;
    HI_PQ_ZME_STRATEGY_OUT_U stZmeOut;

    HI_S32   s32Ret = HI_SUCCESS;
    HI_BOOL bBtm = HI_FALSE;
    HI_U32  u32Vcnt = 0;
    HI_PQ_VDP_WBC_INFO_S stVdpLayerAlgInfor;

    memset(&stZmeIn, 0x0, sizeof(HI_PQ_ZME_STRATEGY_IN_U));
    memset(&stZmeOut, 0x0, sizeof(HI_PQ_ZME_STRATEGY_OUT_U));
    memset(&stVdpLayerAlgInfor, 0x0, sizeof(HI_PQ_VDP_WBC_INFO_S));

    if (!pstWinInfo->bRegionMute && pstWinInfo->bRegionEnable)
    {
        CBB_PIX_FORMAT_E eOutPixelFmt = CBB_VID_IFMT_BUTT;

        TransvertPixelFmt2CBB(&pstWinInfo->pCurrentFrame->ePixFormat, &eOutPixelFmt);
        stZmeIn.stLayerStrategy.u32FmtIn   = eOutPixelFmt;
        stZmeIn.stLayerStrategy.u32FrmWIn  = pstWinInfo->stIn.s32Width;
        stZmeIn.stLayerStrategy.u32FrmHIn  = pstWinInfo->stIn.s32Height;

        // TODO:
        switch (pstWinInfo->enLayerFrostMode)
        {
            case WINDOW_FROST_LOW:
                stZmeIn.stLayerStrategy.eFrostLevel = HI_PQ_FROST_LEVEL_LOW;
                break;

            case WINDOW_FROST_MIDDLE:
                stZmeIn.stLayerStrategy.eFrostLevel = HI_PQ_FROST_LEVEL_MIDDLE;
                break;

            case WINDOW_FROST_HIGH:
                stZmeIn.stLayerStrategy.eFrostLevel = HI_PQ_FROST_LEVEL_HIGH;
                break;
            case WINDOW_FROST_CLOSE:
            default:
                stZmeIn.stLayerStrategy.eFrostLevel = HI_PQ_FROST_LEVEL_CLOSE;
                break;
        }

        stZmeIn.stLayerStrategy.stHDCPAttestFactor.bHDCPScene = pstWinInfo->bHdcpDegradePQ;
        stZmeIn.stLayerStrategy.stHDCPAttestFactor.u32IntermedWidth = pstWinInfo->stHdcpIntermediateRect.s32Width;
        stZmeIn.stLayerStrategy.stHDCPAttestFactor.u32IntermedHeight = pstWinInfo->stHdcpIntermediateRect.s32Height;

        stZmeIn.stLayerStrategy.u32FrmWOut = pstWinInfo->stVideo.s32Width;
        stZmeIn.stLayerStrategy.u32FrmHOut = pstWinInfo->stVideo.s32Height;

        if ((VDP_LAYER_VID0 == pstWinInfo->u32LayerId)
            || (VDP_LAYER_VID1 == pstWinInfo->u32LayerId))
        {
            VDP_DISP_GetVactState(0, &bBtm, &u32Vcnt);
            stZmeIn.stLayerStrategy.bZmeFrmFmtOut   = (VDP_DISP_GetDispMode(0) == 1) ? 1 : 0;
            stZmeIn.stLayerStrategy.bZmeBFIn    = !bBtm;
            stZmeIn.stLayerStrategy.bZmeBFOut   = !bBtm;

            if (HI_SUCCESS != (s32Ret = DRV_PQ_GetVdpZmeStrategy ((HI_PQ_ZME_LAYER_E)pstWinInfo->u32LayerId, &stZmeIn, &stZmeOut)))
            {
                return s32Ret;
            }

            pstVidInfo->stXdpZmeCfg.bZmeFrmFmtOut = stZmeIn.stLayerStrategy.bZmeFrmFmtOut;
            pstVidInfo->stXdpZmeCfg.bZmeBFIn      = stZmeIn.stLayerStrategy.bZmeBFIn;
            pstVidInfo->stXdpZmeCfg.bZmeBFOut     = stZmeIn.stLayerStrategy.bZmeBFOut;

            pstVidInfo->stXdpZmeCfg.u32ZmeNum = stZmeOut.stStrategyLayerId.u32ZmeNum;

            pstVidInfo->stXdpFdrCfg.enDrawMode = (HI_U32)stZmeOut.stStrategyLayerId.eVScalerMode;

            pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Wth  =  stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
            pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Hgt  =  stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;

            ADAPTER_GetTnrDbDmInfo(pstWinInfo, &stVdpLayerAlgInfor);
            if (Internal_SelectTnrLocation(stVdpLayerAlgInfor.enAlgIPSel))
            {
                return HI_FAILURE;
            }

            //DRV_PQ_SetVdpAlgCalcCfg(&stVdpLayerAlgInfor);
        }
        else
        {
            memset((HI_VOID *)&stZmeOut, 0, sizeof(HI_PQ_ZME_STRATEGY_OUT_U));
            pstVidInfo->stXdpFdrCfg.enDrawMode = VDP_DRAW_MODE_1;
            pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Wth  =  pstWinInfo->stVideo.s32Width;;
            pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Hgt  =  pstWinInfo->stVideo.s32Height;;
        }

#ifndef VDP_ZME_COPY_MODE
        /*pass zme strategy to zme.*/
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable;

        /*pass zme strategy to zme.*/
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC;

        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV;
        //pstVidInfo->stXdpZmeCfg.bZmeDefault   = stZmeOut.stStrategyLayerId.bZmeDefault;

        /* set zme phase. */
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm = \
            stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm;

        if (2 == stZmeOut.stStrategyLayerId.u32ZmeNum)
        {
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable;

            /*pass zme strategy to zme.*/
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC;

            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH  = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV  = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV;
            //pstVidInfo->stXdpZmeCfg.bZmeDefault   = stZmeOut.stStrategyLayerId.bZmeDefault;

            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHL = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHL;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHC = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHC;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVL = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVL;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVC = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVC;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVLBtm = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVLBtm;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVCBtm = \
                stZmeOut.stStrategyLayerId.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVCBtm;
        }

#ifdef VDP_V1_ZME_COPY_MODE
        if (VDP_LAYER_VID1 == pstWinInfo->u32LayerId)
        {
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirHL   = HI_FALSE;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirHC   = HI_FALSE;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirVL   = HI_FALSE;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirVC   = HI_FALSE;

            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeMedH    = HI_FALSE;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeMedV    = HI_FALSE;
            pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeDefault = HI_FALSE;
        }
#endif

#else
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirHL = HI_FALSE;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirHC = HI_FALSE;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirVL = HI_FALSE;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFirVC = HI_FALSE;

        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeMedH  = HI_FALSE;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeMedV  = HI_FALSE;
        pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeDefault   = HI_FALSE;
#endif


        pstVidInfo->stXdpHZmeCfg.bHzmeEn  = stZmeOut.stStrategyLayerId.stPreZmeConfig.bPreZme;
        pstVidInfo->stXdpHZmeCfg.enHzmeMode = stZmeOut.stStrategyLayerId.stPreZmeConfig.bPreZmeFir ? VDP_HZME_MODE_FIR : VDP_HZME_MODE_COPY;

        switch (stZmeOut.stStrategyLayerId.eHScalerMode)
        {
            case HI_PQ_PREZME_HOR_2X:
                pstVidInfo->stXdpFdrCfg.enDrawPixelMode = VDP_DRAW_PIXEL_MODE_2;
                break;
            case HI_PQ_PREZME_HOR_4X:
                pstVidInfo->stXdpFdrCfg.enDrawPixelMode = VDP_DRAW_PIXEL_MODE_4;
                break;
            case HI_PQ_PREZME_HOR_8X:
                pstVidInfo->stXdpFdrCfg.enDrawPixelMode = VDP_DRAW_PIXEL_MODE_8;
                break;
            case HI_PQ_PREZME_HOR_DISABLE:
            default:
                pstVidInfo->stXdpFdrCfg.enDrawPixelMode = VDP_DRAW_PIXEL_MODE_1;
                break;
        }

        //pstVidInfo->stXdpZmeCfg.bZmeFrmFmtIn  = stZmeOut.stStrategyLayerId.bReadFmtIn;
        //pstVidInfo->stXdpZmeCfg.bZmeFrmFmtOut   = (VDP_DISP_GetDispMode(0)==1)? 1 : 0;

        /*set the layer's read  t/b mode, when dhd0 is progressive, the t/b config
         *is  useless. If dhd0 is interleave, the output mode is fixed to dhd0's opposite.
         * And the input mode forced to set to the output. since if input is p, the input mode is useless
         * and if input is interleave ,the input mode is the same to the output mode.
         */
        if ((VDP_LAYER_VID0 == pstWinInfo->u32LayerId)
            || (VDP_LAYER_VID1 == pstWinInfo->u32LayerId))
        {
            /*get current t/b filed mode.*/
            VDP_DISP_GetVactState(0, &bBtm, &u32Vcnt);

            /*config next period's effective t/b field mode. */
            //pstVidInfo->stXdpZmeCfg.bZmeBFOut         = !bBtm;
            //pstVidInfo->stXdpZmeCfg.bZmeBFIn      = !bBtm;
        }
        else
        {
            //pstVidInfo->stXdpZmeCfg.bZmeBFOut         = HI_FALSE;
            //pstVidInfo->stXdpZmeCfg.bZmeBFIn      = stZmeOut.stStrategyLayerId.bReadBFIn;
        }

        /* frame is interlace, this is for V3.*/
        if (HI_FALSE == pstWinInfo->pCurrentFrame->bProgressive)
        {
            if (HI_DRV_FIELD_TOP == pstWinInfo->pCurrentFrame->enFieldMode)
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_TOP;
            }
            else
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_BOTTOM;
            }
        }
        else
        {
            /*read frame.*/
            if (stZmeOut.stStrategyLayerId.bReadFmtIn == HI_TRUE)
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_PROGRESSIVE;
            }
            else
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_INTERFACE;
            }
        }
    }
    else
    {
        //pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFrmFmtIn   = HI_TRUE;
        //pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFrmFmtOut   = HI_TRUE;
        //pstVidInfo->stXdpZmeCfg.bZmeBFOut      = HI_FALSE;
        //pstVidInfo->stXdpZmeCfg.bZmeBFIn       = HI_FALSE;

        pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Wth = pstWinInfo->stVideo.s32Width;
        pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Hgt  =  pstWinInfo->stVideo.s32Height;

        pstVidInfo->stXdpFdrCfg.enDrawMode = VDP_DRAW_MODE_1;
        pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_INTERLACE;

#if 0
        if (pstWinInfo->pCurrentFrame->bProgressive == HI_FALSE)
        {
            if (HI_DRV_FIELD_TOP == pstWinInfo->pCurrentFrame->enFieldMode)
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_TOP;
            }
            else
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_BOTTOM;
            }
        }
        else
        {
            if (pstWinInfo->pstDispInfo->bInterlace == 1)
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_INTERLACE;
            }
            else
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_PROGRESSIVE;
            }
        }
#endif

    }
#else
    {
        // CBB  process  add by hyx
        //pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFrmFmtIn   = HI_TRUE;
        //pstVidInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZme2InRect.bZmeFrmFmtOut   = HI_TRUE;
        //pstVidInfo->stXdpZmeCfg.bZmeBFOut      = HI_FALSE;
        //pstVidInfo->stXdpZmeCfg.bZmeBFIn       = HI_FALSE;

        pstVidInfo->stXdpHZmeCfg.enHzmeMode = VDP_HZME_MODE_COPY;
        pstVidInfo->stXdpFdrCfg.enDrawPixelMode = VDP_DRAW_PIXEL_MODE_1;

        if (VDP_LAYER_VID0 == pstWinInfo->u32LayerId)
        {
            pstVidInfo->stXdpHZmeCfg.bHzmeEn = HI_TRUE;
        }
        else
        {
            pstVidInfo->stXdpHZmeCfg.bHzmeEn = HI_FALSE;
        }

        pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Wth  =  pstWinInfo->stVideo.s32Width;
        pstVidInfo->stXdpZmeCfg.stZme2InRect.u32Hgt  =  pstWinInfo->stVideo.s32Height;

        pstVidInfo->stXdpFdrCfg.enDrawMode = VDP_DRAW_MODE_1;

        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            if (pstWinInfo->pCurrentFrame->bProgressive == HI_FALSE)
            {
                if (HI_DRV_FIELD_TOP == pstWinInfo->pCurrentFrame->enFieldMode)
                {
                    pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_TOP;
                }
                else
                {
                    pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_BOTTOM;
                }
            }
            else
            {
                pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_PROGRESSIVE;
            }

        }
        else
        {
            pstVidInfo->stXdpFdrCfg.enReadMode = VDP_RMODE_INTERLACE;
        }
    }
#endif
    return HI_SUCCESS;
}


HI_VOID ADAPTER_TransferWinInfoToHalCfg(WIN_INFO_S *pstWinInfo,
                                        XDP_LAYER_VID_INFO_S *pstLayerInfo)
{
    if ((pstWinInfo->u32LayerId >= VDP_LAYER_VID4) || (pstWinInfo->u32RegionNo >= MAX_WINDOWS_NUM))
    {
        HI_ERR_DISP("Invalid LayerId %d or RegionNo %d.\n", pstWinInfo->u32LayerId, pstWinInfo->u32RegionNo);
        return ;
    }

    pstLayerInfo->stXdpSysCfg.u32RegionNO = pstWinInfo->u32RegionNo;
    GetSpecialLayerPriorty(pstWinInfo->u32LayerId, &pstLayerInfo->stXdpSysCfg.u32LayerZorder);

    if (VDP_LAYER_VID1 == pstWinInfo->u32LayerId)
    {
        pstLayerInfo->stXdpSysCfg.bRegionModeEn = HI_TRUE;
    }
    else
    {
        pstLayerInfo->stXdpSysCfg.bRegionModeEn = HI_FALSE;
    }
    pstLayerInfo->stXdpSysCfg.bRegionEn =  pstWinInfo->bRegionEnable;

    if ( ! pstWinInfo->u32Alpha)
    {
        pstLayerInfo->stXdpSysCfg.u32Alpha = pstWinInfo->u32Alpha;
    }
    else
    {
        pstLayerInfo->stXdpSysCfg.u32Alpha = (pstWinInfo->u32Alpha * LOGIC_MAX_ALPHA) / VDP_VIDEO_MAX_ALPHA;
    }

    if ( ! pstWinInfo->u32AllAlpha)
    {
        pstLayerInfo->stXdpSysCfg.u32AllAlpha = pstWinInfo->u32AllAlpha;
    }
    else
    {
        pstLayerInfo->stXdpSysCfg.u32AllAlpha = (pstWinInfo->u32AllAlpha * LOGIC_MAX_ALPHA) / VDP_VIDEO_MAX_ALPHA;
    }

    if (HI_TRUE == pstLayerInfo->stXdpSysCfg.bRegionEn)
    {
        ADAPTER_GetZmeCfgFromPq(pstWinInfo, pstLayerInfo);

        pstLayerInfo->stXdpFdrCfg.stCropRect.u32X      = (HI_U32)(pstWinInfo->stIn.s32X);
        pstLayerInfo->stXdpFdrCfg.stCropRect.u32Y      = (HI_U32)(pstWinInfo->stIn.s32Y);
        pstLayerInfo->stXdpFdrCfg.stCropRect.u32Wth    = pstWinInfo->stIn.s32Width;
        pstLayerInfo->stXdpFdrCfg.stCropRect.u32Hgt    = pstWinInfo->stIn.s32Height;

        pstLayerInfo->stXdpPositionCfg.stVideoRect.u32X     = (HI_U32)(pstWinInfo->stVideo.s32X);
        pstLayerInfo->stXdpPositionCfg.stVideoRect.u32Y     = (HI_U32)(pstWinInfo->stVideo.s32Y);
        pstLayerInfo->stXdpPositionCfg.stVideoRect.u32Wth   = pstWinInfo->stVideo.s32Width;
        pstLayerInfo->stXdpPositionCfg.stVideoRect.u32Hgt   = pstWinInfo->stVideo.s32Height;

        pstLayerInfo->stXdpPositionCfg.stDispRect.u32X      = (HI_U32)(pstWinInfo->stDisp.s32X);
        pstLayerInfo->stXdpPositionCfg.stDispRect.u32Y      = (HI_U32)(pstWinInfo->stDisp.s32Y);
        pstLayerInfo->stXdpPositionCfg.stDispRect.u32Wth    = pstWinInfo->stDisp.s32Width;
        pstLayerInfo->stXdpPositionCfg.stDispRect.u32Hgt    = pstWinInfo->stDisp.s32Height;

        pstLayerInfo->stXdpSrcCfg.enSrcClrSpace  = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enInCsc);
        pstLayerInfo->stXdpDispCfg.enOutClrSpace = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enOutCsc);
        pstLayerInfo->stXdpDispCfg.enDispMode    = XDR_DISPMODE_TRANSFER(pstWinInfo->pstDispInfo->eDispMode);

        pstLayerInfo->stXdpSysCfg.bMuteEn              = pstWinInfo->bRegionMute;
        pstLayerInfo->stXdpBkgCfg.stMuteColor.u32BkgY  = 0x40;
        pstLayerInfo->stXdpBkgCfg.stMuteColor.u32BkgU  = 0x200;
        pstLayerInfo->stXdpBkgCfg.stMuteColor.u32BkgV  = 0x200;
        pstLayerInfo->stXdpBkgCfg.stMuteColor.u32BkgA  = 0xff;

        pstLayerInfo->stXdpBkgCfg.stLetterBoxColor     = pstLayerInfo->stXdpBkgCfg.stMuteColor;

        /* set mixv color under RGB color space, cause Y2R always open. */
        pstLayerInfo->stXdpBkgCfg.stMixvColor.u32BkgA  = 0xff;
        pstLayerInfo->stXdpBkgCfg.stMixvColor.u32BkgY  = pstWinInfo->pstDispInfo->u32Kr;
        pstLayerInfo->stXdpBkgCfg.stMixvColor.u32BkgU  = pstWinInfo->pstDispInfo->u32Kg;
        pstLayerInfo->stXdpBkgCfg.stMixvColor.u32BkgV  = pstWinInfo->pstDispInfo->u32Kb;

        pstLayerInfo->stXdpDispCfg.bInterlace  = pstWinInfo->pstDispInfo->bInterlace;
        pstLayerInfo->stXdpDispCfg.stFmtReso.u32X  = pstWinInfo->pstDispInfo->stFmtResolution.s32X;
        pstLayerInfo->stXdpDispCfg.stFmtReso.u32Y  = pstWinInfo->pstDispInfo->stFmtResolution.s32Y;
        pstLayerInfo->stXdpDispCfg.stFmtReso.u32Wth  = pstWinInfo->pstDispInfo->stFmtResolution.s32Width;
        pstLayerInfo->stXdpDispCfg.stFmtReso.u32Hgt  = pstWinInfo->pstDispInfo->stFmtResolution.s32Height;
        pstLayerInfo->stXdpDispCfg.stFmtReso.u32SX = 0;


        //===============================src process=============================
        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            HI_BOOL bUvorder = HI_FALSE, bCmpFmt = HI_FALSE, bLostCmp = HI_FALSE;
            pstLayerInfo->stXdpSysCfg.bSecureEn = pstWinInfo->pCurrentFrame->bSecure;
#ifdef  CFG_VDP_MMU_SUPPORT
            pstLayerInfo->stXdpSrcCfg.bSmmuEn   = HI_TRUE;
#else
            pstLayerInfo->stXdpSrcCfg.bSmmuEn   = HI_FALSE;
#endif
            JudgeCmpAndUvorderByPixFormat(pstWinInfo->pCurrentFrame->ePixFormat,
                                          &bUvorder, &bCmpFmt, &bLostCmp);

            pstLayerInfo->stXdpSrcCfg.bDcmpEn   = bCmpFmt;
            pstLayerInfo->stXdpSrcCfg.bDcmpLost = bLostCmp;
            pstLayerInfo->stXdpSrcCfg.bUVOrder  = bUvorder;

            pstLayerInfo->stXdpSrcCfg.enInFmt = XDR_PIXEL_FMT_TRANSFER(pstWinInfo->pCurrentFrame->ePixFormat);

            //============================bitwidth===========================
            switch (pstWinInfo->pCurrentFrame->enBitWidth)
            {
                case HI_DRV_PIXEL_BITWIDTH_8BIT:
                    pstLayerInfo->stXdpSrcCfg.enDataWidth = VDP_DATA_WTH_8;
                    break;
                case HI_DRV_PIXEL_BITWIDTH_10BIT:
                    pstLayerInfo->stXdpSrcCfg.enDataWidth = VDP_DATA_WTH_10;
                    break;
                case HI_DRV_PIXEL_BITWIDTH_10BIT_CTS:
                    pstLayerInfo->stXdpSrcCfg.enDataWidth = VDP_DATA_WTH_10_CTS;
                    break;
                default:
                    HI_ERR_DISP("Invalid enBitWidth %d.\n", pstWinInfo->pCurrentFrame->enBitWidth);
                    pstLayerInfo->stXdpSrcCfg.enDataWidth = VDP_DATA_WTH_8;
                    break;
            }

            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32X   = 0;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Y   = 0;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Wth = pstWinInfo->pCurrentFrame->u32Width;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Hgt = pstWinInfo->pCurrentFrame->u32Height;

            //=============================addr ===========================
            ADAPTER_TransferAddrToHalAddr(pstWinInfo->pCurrentFrame->eFrmType,
                                          pstWinInfo->pstDispInfo->eDispMode,
                                          pstWinInfo->pstDispInfo->bRightEyeFirst,
                                          bCmpFmt,
                                          &pstWinInfo->pCurrentFrame->stBufAddr[0],
                                          &pstWinInfo->pCurrentFrame->stBufAddr_LB[0],
                                          &pstLayerInfo->stXdpSrcCfg.stAddr[0]);

        }
        else
        {
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32X   = 0;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Y   = 0;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Wth = pstWinInfo->stIn.s32Width;
            pstLayerInfo->stXdpSrcCfg.stSrcRect.u32Hgt = pstWinInfo->stIn.s32Height;
        }


    }

    return ;
}

HI_VOID ADAPTER_CloseV0V1Layer(HI_VOID)
{
    static  XDP_LAYER_VID_INFO_S stLayerInfoIn;
    HI_U32  u32Index = 0;

    memset(&stLayerInfoIn, 0x0, sizeof(XDP_LAYER_VID_INFO_S));

    stLayerInfoIn.stXdpSysCfg.bEnable = HI_FALSE;
    stLayerInfoIn.stXdpSysCfg.bRegionEn = HI_FALSE;

    //close v0.
    VDP_DRV_SetVidLayer(VDP_LAYER_VID0, &stLayerInfoIn, HI_NULL);
    //close v1.
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER - 1; u32Index++)
    {
        stLayerInfoIn.stXdpSysCfg.u32RegionNO = u32Index;
        VDP_DRV_SetVidLayer(VDP_LAYER_VID1, &stLayerInfoIn, HI_NULL);
    }

    return;
}

/*bConfigWholeLayer means whether to config whole layer or not.*/
HI_VOID ADAPTER_SetLayerCfg(HI_U32 u32LayerId,
                            WIN_INFO_S *pstWinInfo,
                            HI_BOOL *pbVdmArray,
                            HI_BOOL bConfigWholeLayer)
{
    static  XDP_LAYER_VID_INFO_S stLayerInfoIn;
    HI_PQ_HDR_CFG  *pstPqHdrCfg = HI_NULL;
    HI_U32 u32Index = 0;

    memset(&stLayerInfoIn, 0x0, sizeof(XDP_LAYER_VID_INFO_S));

    if (VDP_LAYER_VID_BUTT <= u32LayerId)
    {
        HI_ERR_DISP("Invalid layer id.\n");
        return;
    }

    ADAPTER_TransferWinInfoToHalCfg(pstWinInfo, &stLayerInfoIn);

    if ((VDP_LAYER_VID0 == u32LayerId)
        || (VDP_LAYER_VID1 == u32LayerId))
    {
        //vdm process.
        for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
        {
            stLayerInfoIn.stXdpSysCfg.bVdmProcess[u32Index] = pbVdmArray[u32Index];

            if ((1 == pbVdmArray[u32Index])
                && (u32Index == (pstWinInfo->hWinHandle & 0xFF)))
            {
                stLayerInfoIn.stXdpSysCfg.u32VdmOnLayerId = pstWinInfo->u32LayerId;
            }
        }

    }

    //pq para process.
    if (HI_NULL != pstWinInfo->pCurrentFrame)
    {
        DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;

        pstDispBufNode = container_of((HI_U32 *)pstWinInfo->pCurrentFrame, DISP_BUF_NODE_S, u32Data[0]);

        pstPqHdrCfg = (HI_PQ_HDR_CFG *)pstDispBufNode->u8Metadata;

        stLayerInfoIn.stXdpSrcCfg.enXdpViDeoFrameType = pstWinInfo->pCurrentFrame->enSrcFrameType;//modify it latter.
    }

    stLayerInfoIn.stXdpSrcCfg.enSrcClrSpace  = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enInCsc);
    stLayerInfoIn.stXdpDispCfg.enOutClrSpace = XDR_COLOR_SPACE_TRANSFER(pstWinInfo->enOutCsc);
    stLayerInfoIn.stXdpDispCfg.enDisPlayMode = XDR_OUT_TYPE_TRANSFER(pstWinInfo->enOutType);

    if (VDP_LAYER_VID3 == u32LayerId)
    {
        pstPqHdrCfg = HI_NULL;
    }

    stLayerInfoIn.stXdpLayerExtern.bConfigWholeLayer = bConfigWholeLayer;

    VDP_DRV_SetVidLayer(u32LayerId, &stLayerInfoIn, pstPqHdrCfg);

    return;
}

HI_VOID ADAPTER_SetDolbyCfg(WIN_INFO_S *pstWinInfo, DRV_DISP_DOLBY_PLAY_INFO_S *pstDolbyInfo)
{
    // TODO: for 98MV200/96MV200
    return;
}


#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
