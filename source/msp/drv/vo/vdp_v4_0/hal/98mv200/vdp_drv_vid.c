#include "hi_type.h"
#include "vdp_drv_comm.h"
#include "vdp_drv_vid.h"
#include "vdp_hal_mmu.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_hal_comm.h"
#include "vdp_drv_ip_vdm.h"
#include "VdpHiHDR_cfg.h"
#include "vdp_drv_vdm_coef.h"
#include "vdp_fpga_define.h"

#include "vdp_drv_bkg_process.h"
#include "vdp_drv_gdm_coef.h"

#ifndef  __DISP_PLATFORM_BOOT__
#if (!EDA_TEST)
#include <linux/string.h>
#include <linux/kernel.h>
#else
#include <string.h>
#endif

extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;

HI_S32  XDP_DRV_HdrRegClean(XDP_LAYER_VID_INFO_S *pstInfo)
{
    HI_U32  i = 0;

    for (i = 0; i < MAX_WINDOWS_NUM; i++)
    {
        if (pstInfo->stXdpSysCfg.bVdmProcess[i] == HI_TRUE)
        {
            return HI_SUCCESS;
        }
    }
    VDP_VID_SetVdmVdmV1GammaEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmV0GammaEn(VDP_LAYER_VID0, HI_FALSE);

    VDP_VID_SetVdmVdmGmmEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmTmapEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmDegmmEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmEn(VDP_LAYER_VID0, HI_FALSE);

    //VDP_VID_SetVdmVdmV1CscEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmV0CscEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmRgb2yuvEn(VDP_LAYER_VID0, HI_FALSE);

    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, HI_FALSE);
    return HI_SUCCESS;
}

HI_VOID VDP_DRV_HdrRegClean(HI_VOID)
{
    VDP_VID_SetVdmVdmGmmEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmTmapEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmDegmmEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmV1GammaEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmV0GammaEn(VDP_LAYER_VID0, HI_FALSE);

    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, HI_FALSE);

    return;
}


HI_S32  XDP_DRV_GetLayerMuteInfo(XDP_LAYER_VID_INFO_S *pstInfo)
{
    if (pstInfo->stXdpSysCfg.bMuteEn == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    switch (pstInfo->stXdpDispCfg.enDisPlayMode)
    {
        case XDP_DISP_TYPE_NORMAL:
        case XDP_DISP_TYPE_SDR_CERT:
            pstInfo->stXdpSrcCfg.enXdpViDeoFrameType = XDP_VIDEO_FRAME_TYPE_SDR;
            break;
        case XDP_DISP_TYPE_HDR10:
        case XDP_DISP_TYPE_HDR10_CERT:
            pstInfo->stXdpSrcCfg.enXdpViDeoFrameType = XDP_VIDEO_FRAME_TYPE_HDR10;
            break;
        case XDP_DISP_TYPE_HLG:
            pstInfo->stXdpSrcCfg.enXdpViDeoFrameType = XDP_VIDEO_FRAME_TYPE_HLG;
            break;
        case XDP_DISP_TYPE_TECHNICOLOR:
            pstInfo->stXdpSrcCfg.enXdpViDeoFrameType = XDP_VIDEO_FRAME_TYPE_TECHNICOLOR;
            break;
        default:
            break;
    }

    pstInfo->stXdpSrcCfg.enSrcClrSpace = pstInfo->stXdpDispCfg.enOutClrSpace ;

    pstInfo->stXdpSysCfg.bSecureEn = HI_FALSE;
    pstInfo->stXdpSrcCfg.bSmmuEn = HI_FALSE;
    pstInfo->stXdpSrcCfg.bDcmpEn = HI_FALSE;
    pstInfo->stXdpSrcCfg.bDcmpLost = HI_FALSE;
    pstInfo->stXdpSrcCfg.enInFmt = VDP_VID_IFMT_SP_420;
    pstInfo->stXdpSrcCfg.enDataWidth   = VDP_DATA_WTH_8;

    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].bSecure = HI_FALSE;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].bSmmu = HI_FALSE;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr = gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_L];
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr = gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_C];
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr  = 0;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr  = 0;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].bSecure = HI_FALSE;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].bSmmu = HI_FALSE;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumAddr = gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_L];
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmAddr = gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_MUTE_V1_C];
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumStr  = 0;
    pstInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmStr  = 0;

    //to fix lowband issue.
    pstInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt = 0x1;
    pstInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = 0x0;

    /* v1 may cause v0 lowband. */
    pstInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = HI_TRUE;
    pstInfo->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 XDP_DRV_JudgeVidLayerEnable(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfo)
{
    if (((u32LayerId == VDP_LAYER_VID0) || (u32LayerId == VDP_LAYER_VID3))
        && (pstInfo->stXdpSysCfg.bRegionEn == HI_FALSE))
    {
        VDP_VID_SetLayerEnable (u32LayerId, HI_FALSE);
        VDP_VID_SetRegUp(u32LayerId);
        return HI_SUCCESS;
    }
    else if ((u32LayerId == VDP_LAYER_VID1) && (pstInfo->stXdpSysCfg.bRegionEn == HI_FALSE))
    {
        VDP_VID_SetRegionEnable(u32LayerId, pstInfo->stXdpSysCfg.u32RegionNO, pstInfo->stXdpSysCfg.bRegionEn);

        if (HI_FALSE == VDP_VID_CheckRegionState(u32LayerId))
        {
            VDP_VID_SetLayerEnable (u32LayerId, HI_FALSE);
            VDP_VID_SetAllRegionDisable(u32LayerId);
            VDP_VID_SetRegUp(u32LayerId);
            return HI_SUCCESS;
        }
        else
        {
            VDP_VID_SetLayerEnable (u32LayerId, HI_TRUE);
            VDP_VID_SetRegUp(u32LayerId);
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;

}


HI_S32 XDP_DRV_SetVidCBM(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstOutInfo)
{
    HI_U32  u32LayerZorder = pstOutInfo->stXdpSysCfg.u32LayerZorder;
    VDP_CBM_Clear_MixvPrio(u32LayerId);

    if ((u32LayerId == VDP_LAYER_VID0) || (u32LayerId == VDP_LAYER_VID1))
    {
        VDP_CBM_SetMixerPrio(VDP_CBM_MIXV0, u32LayerId, u32LayerZorder);
    }
    else if (u32LayerId == VDP_LAYER_VID3)
    {
        VDP_CBM_SetMixerPrio(VDP_CBM_MIXV1, u32LayerId, u32LayerZorder);
    }

    return HI_SUCCESS;
}


HI_S32 XDP_DRV_SetRegUp(HI_U32 u32LayerId)
{

    VDP_VID_SetRegUp(u32LayerId);
    VDP_VP_SetRegUp(VDP_LAYER_VP0);

    return HI_SUCCESS;
}




HI_S32 XDP_DRV_GetVidLayerFdr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    VDP_RECT_S stInRect      = {0};
    VDP_RECT_S stTileCrop    = {0}; //only use pos info
    VDP_RECT_S stCropOutRect = {0}; //linear hor crop
    HI_U32  u32CropX         = 0; //x pos
    HI_U32  u32CropY         = 0; //y pos

    u32CropX      = pstInfoIn->stXdpFdrCfg.stCropRect.u32X;
    u32CropY      = pstInfoIn->stXdpFdrCfg.stCropRect.u32Y;
    stCropOutRect = pstInfoIn->stXdpFdrCfg.stCropRect;

    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {

        stTileCrop.u32Y    = u32CropY;
        //----------------------------------------------------------------------
        //hardware crop
        //tile crop x_offset must 64 pixel aligned
        //do not support 3d mode in tile format
        //+----------+    +----------+    +----------+
        //|tile crop | -> |in rect   | -> |hor crop  |
        //+----------+    +----------+    +----------+
        //----------------------------------------------------------------------
        stCropOutRect.u32X = u32CropX % 64; //2 pixel aligned
        stTileCrop.u32X = u32CropX - stCropOutRect.u32X;
        stInRect.u32Wth = pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth + stCropOutRect.u32X;
        stInRect.u32Hgt = pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt;

    }
    else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE)
    {
        //----------------------------------------------------------------------
        //hardware & software crop
        //do not support 3d mode in tile format
        //----------------------------------------------------------------------

        //to do
    }
    else//linear
    {
        //+----------+    +----------+
        //|in rect   | -> |hor crop  |
        //+----------+    +----------+
        if (pstInfoIn->stXdpDispCfg.enDispMode == VDP_DISP_MODE_SBS) //sbs mode,position is single eye
        {
            stInRect.u32Wth      = pstInfoIn->stXdpSrcCfg.stSrcRect.u32Wth  / 1;//hareware
            stCropOutRect.u32X   = stCropOutRect.u32X   / 1;
            stCropOutRect.u32Wth = stCropOutRect.u32Wth / 1;

            stInRect.u32Hgt      = pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt ;
        }
        else if (pstInfoIn->stXdpDispCfg.enDispMode == VDP_DISP_MODE_TAB
                 || pstInfoIn->stXdpDispCfg.enDispMode == VDP_DISP_MODE_LBL)
        {
            stInRect.u32Wth      = pstInfoIn->stXdpSrcCfg.stSrcRect.u32Wth   ;
            stInRect.u32Hgt      = pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt / 1; //software
            stCropOutRect.u32Hgt = stCropOutRect.u32Hgt / 1;
            u32CropY             = u32CropY / 1;
        }
        else
        {
            stInRect.u32Wth      = pstInfoIn->stXdpSrcCfg.stSrcRect.u32Wth ;
            stInRect.u32Hgt      = stCropOutRect.u32Hgt;
        }

        //----------------------------------------------------------------------
        //software crop for ver
        //----------------------------------------------------------------------
        // draw to do...

    }

    //--------------draw mode setting-------------//
    if (pstInfoIn->stXdpFdrCfg.enDrawMode == VDP_DRAW_MODE_2)
    {
        stInRect.u32Hgt /= 2;
    }
    else if (pstInfoIn->stXdpFdrCfg.enDrawMode == VDP_DRAW_MODE_4)
    {
        stInRect.u32Hgt /= 4;
    }
    else if (pstInfoIn->stXdpFdrCfg.enDrawMode == VDP_DRAW_MODE_8)
    {
        stInRect.u32Hgt /= 8;
    }
    else //no draw
    {
        stInRect.u32Hgt /= 1;
    }


    if (pstInfoIn->stXdpFdrCfg.enDrawPixelMode == VDP_DRAW_PIXEL_MODE_2)
    {
        stCropOutRect.u32Wth /= 2;
    }
    else if (pstInfoIn->stXdpFdrCfg.enDrawPixelMode == VDP_DRAW_PIXEL_MODE_4)
    {
        stCropOutRect.u32Wth /= 4;
    }
    else if (pstInfoIn->stXdpFdrCfg.enDrawPixelMode == VDP_DRAW_PIXEL_MODE_8)
    {
        stCropOutRect.u32Wth /= 8;
    }
    else //no pixel draw
    {
        stCropOutRect.u32Wth /= 1;
    }

    pstInfoIn->stXdpSrcCfg.stSrcRect = stInRect;
    pstInfoIn->stXdpFdrCfg.stCropRect = stCropOutRect;

    pstInfoOut->stXdpSrcCfg.stSrcRect = pstInfoIn->stXdpSrcCfg.stSrcRect;
    pstInfoOut->stXdpFdrCfg.stCropRect = pstInfoIn->stXdpFdrCfg.stCropRect;
    pstInfoOut->stXdpFdrCfg.stTileCropRect = stTileCrop;

    return HI_SUCCESS;
}



HI_S32 XDP_DRV_SetVidLayerFdr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_U32 u32LeftEye  = (VDP_LAYER_VID0 == u32LayerId) ?  XDP_ADDR_3D_2LOWBIT_LEFT_EYE  : pstInfoOut->stXdpSysCfg.u32RegionNO;
    HI_U32 u32RightEye = (VDP_LAYER_VID0 == u32LayerId) ?  XDP_ADDR_3D_2LOWBIT_RIGHT_EYE : pstInfoOut->stXdpSysCfg.u32RegionNO;

    VDP_VID_SetLayerEnable (u32LayerId, HI_TRUE);

    if (u32LayerId == VDP_LAYER_VID1)
    {
        if (pstInfoOut->stXdpSysCfg.bRegionModeEn == 1)
        {
            VDP_VID_SetRegionEnable        (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpSysCfg.bRegionEn);
        }
    }

    VDP_VID_SetInDataFmt(u32LayerId, pstInfoOut->stXdpSrcCfg.enInFmt);

    VDP_VID_SetUvorder(u32LayerId, pstInfoOut->stXdpSrcCfg.bUVOrder);

    VDP_VID_SetReadMode                (u32LayerId, pstInfoOut->stXdpFdrCfg.enReadMode, pstInfoOut->stXdpFdrCfg.enReadMode);

    VDP_VID_Set16RegionSmmuLumBypass   (u32LayerId, u32LeftEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
    VDP_VID_Set16RegionSmmuChromBypass (u32LayerId, u32LeftEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
    VDP_VID_Set16RegionSmmuLumBypass   (u32LayerId, u32RightEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
    VDP_VID_Set16RegionSmmuChromBypass (u32LayerId, u32RightEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);


    VDP_VID_SetDataWidth               (u32LayerId, pstInfoOut->stXdpSrcCfg.enDataWidth);
    VDP_VID_SetNoSecFlag               (u32LayerId, !pstInfoOut->stXdpSysCfg.bSecureEn);

    VDP_VID_SetInReso                  (u32LayerId, pstInfoOut->stXdpSrcCfg.stSrcRect);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_VID_SetTileDcmpEnable          (u32LayerId, pstInfoOut->stXdpSrcCfg.bDcmpEn);
        VDP_VID_SetDrawPixelMode           (u32LayerId, pstInfoOut->stXdpFdrCfg.enDrawPixelMode);
        VDP_VID_SetDrawMode                (u32LayerId, pstInfoOut->stXdpFdrCfg.enDrawMode, pstInfoOut->stXdpFdrCfg.enDrawMode);

        VDP_VID_SetSrcCropReso             (u32LayerId, pstInfoOut->stXdpFdrCfg.stTileCropRect);
        VDP_VID_SetCropReso                (u32LayerId, pstInfoOut->stXdpFdrCfg.stCropRect);
    }


    return HI_SUCCESS;
}

HI_S32  XDP_DRV_GetVidAddrAfterCrop (HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    //HI_U32  u32CropX         = 0; //x pos
    HI_U32  u32CropY         = 0; //y pos
    HI_U32 u32LumAddr        = 0 ;
    HI_U32 u32ChmAddr        = 0 ;
    HI_U32 u32LumAddr3D      = 0 ;
    HI_U32 u32ChmAddr3D      = 0 ;
    HI_U32 u32LumAddrTile2bit = 0 ;
    HI_U32 u32ChmAddrTile2bit = 0 ;
    HI_U32 u32ChmRatio       = 1 ;

    //u32CropX       = pstInfoIn->stXdpFdrCfg.stCropRect.u32X;
    u32CropY       = pstInfoIn->stXdpFdrCfg.stCropRect.u32Y;

    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
        || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE
        || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        u32ChmRatio = 2;
    }
    else
    {
        u32ChmRatio = 1;
    }

    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        u32LumAddr         = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr;
        u32ChmAddr         = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr;
        u32LumAddrTile2bit = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumAddr;
        u32ChmAddrTile2bit = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32ChmAddr;
    }
    else
    {
        u32LumAddr   = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr + pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr * u32CropY;
        u32ChmAddr   = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr + pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr * u32CropY / u32ChmRatio;
        u32LumAddr3D = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumAddr   + pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr * u32CropY ;
        u32ChmAddr3D = pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmAddr   + pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr * u32CropY / u32ChmRatio ;
    }


    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr  = u32LumAddr   ;
    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr  = u32ChmAddr   ;
    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumAddr    = u32LumAddr3D ;
    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmAddr    = u32ChmAddr3D ;
    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumAddr  = u32LumAddrTile2bit;
    pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32ChmAddr  = u32ChmAddrTile2bit;


    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidReso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    VDP_RECT_S stVid1Reso;


    VDP_VID_SetOutReso(u32LayerId, pstInfoOut->stXdpZmeCfg.stZme2InRect);
    VDP_VID_SetSrOutReso (u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetVideoPos                (u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetDispPos                 (u32LayerId, pstInfoOut->stXdpPositionCfg.stDispRect);

    if (u32LayerId == VDP_LAYER_VID1)
    {
        if (pstInfoOut->stXdpSysCfg.bRegionModeEn == 1)
        {

            stVid1Reso = pstInfoOut->stXdpDispCfg.stFmtReso;

            VDP_VID_SetInReso                  (u32LayerId, stVid1Reso);
            VDP_VID_SetOutReso                 (u32LayerId, stVid1Reso);
            VDP_VID_SetVideoPos                (u32LayerId, stVid1Reso);
            VDP_VID_SetDispPos                 (u32LayerId, stVid1Reso);

            VDP_VID_SetRegionEnable        (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpSysCfg.bRegionEn);
            VDP_VID_SetRegionReso          (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpPositionCfg.stVideoRect);
        }


    }

    return HI_SUCCESS;

}
HI_S32 VDP_DRV_GetHiHdrGfxCfg(GdmCfg_t  *pstDmCfg)
{

    if(pstDmCfg->GdmSceneMode == GDM_SDR_IN_HDR10_OUT
    || pstDmCfg->GdmSceneMode == GDM_SDR_IN_HLG_OUT )
    {
        //VDP_PRINT("GdmSceneMode == GDM_SDR_IN_HDR10_OUT\n");
        //typ mode

        pstDmCfg->vdm_en                 = 1  ;
        pstDmCfg->vdm_degmm_en           = 1  ;
        pstDmCfg->vdm_csc_en             = 1  ;
        pstDmCfg->vdm_tmap_en            = 1  ;
        pstDmCfg->vdm_gmm_en             = 1  ;
        pstDmCfg->vdm_dither_en          = 1  ;
        pstDmCfg->vdm_rgb2yuv_en         = 1  ;
        pstDmCfg->gdm_r2y_premult_en     = 0  ;

        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 14     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]   = 10280 ; //BT709 to BT2020
        pstDmCfg->s16M33Src2Disp[0][1]   = 5396  ;
        pstDmCfg->s16M33Src2Disp[0][2]   = 709   ;
        pstDmCfg->s16M33Src2Disp[1][0]   = 1133  ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 15066 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = 185   ;
        pstDmCfg->s16M33Src2Disp[2][0]   = 269   ;
        pstDmCfg->s16M33Src2Disp[2][1]   = 1442  ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 14672 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 3685 ; //BT2020
        pstDmCfg->s16M33RGB2YUV[0][1]    = 9512 ;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 832  ;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -2004 * 1.3;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5171 * 1.3;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175 * 1.3;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175 * 1.3;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6598 * 1.3;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -577 * 1.3;
        pstDmCfg->u16ScaleRGB2YUV        = 14   ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64   ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512  ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512  ;
    }
    else if (pstDmCfg->GdmSceneMode == GDM_SDR_IN_BBC_OUT)
    {
        VDP_PRINT("GdmSceneMode == GDM_SDR_IN_BBC_OUT\n");
        //typ mode

        pstDmCfg->vdm_en                 = 1  ;
        pstDmCfg->vdm_degmm_en           = 1  ;
        pstDmCfg->vdm_csc_en             = 0  ;
        pstDmCfg->vdm_tmap_en            = 1  ;
        pstDmCfg->vdm_gmm_en             = 1  ;
        pstDmCfg->vdm_dither_en          = 1  ;
        pstDmCfg->vdm_rgb2yuv_en         = 1  ;
        pstDmCfg->gdm_r2y_premult_en     = 0  ;

        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 8     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]   = 27209 ;//709 to 709 bypass
        pstDmCfg->s16M33Src2Disp[0][1]   = -9632 ;
        pstDmCfg->s16M33Src2Disp[0][2]   = -1194 ;
        pstDmCfg->s16M33Src2Disp[1][0]   = -2045 ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 18565 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = -138  ;
        pstDmCfg->s16M33Src2Disp[2][0]   = -297  ;
        pstDmCfg->s16M33Src2Disp[2][1]   = -1648 ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 18330 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;
        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 2984; //BT2020
        pstDmCfg->s16M33RGB2YUV[0][1]    = 10034;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 1013;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -1643;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5531;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6518;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -659;
        pstDmCfg->u16ScaleRGB2YUV        = 14   ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64   ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512  ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512  ;
    }
    else if (pstDmCfg->GdmSceneMode == GDM_SDR_PREMULT)
    {
        VDP_PRINT("GdmSceneMode == GDM_SDR_PREMULT\n");
        //typ mode

        pstDmCfg->vdm_en                 = 0  ;
        pstDmCfg->vdm_degmm_en           = 0  ;
        pstDmCfg->vdm_csc_en             = 0  ;
        pstDmCfg->vdm_tmap_en            = 0  ;
        pstDmCfg->vdm_gmm_en             = 0  ;
        pstDmCfg->vdm_dither_en          = 0  ;
        pstDmCfg->vdm_rgb2yuv_en         = 1  ;
        pstDmCfg->gdm_r2y_premult_en     = 1  ;

        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 8     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]   = 10280 ; //BT709 to BT2020
        pstDmCfg->s16M33Src2Disp[0][1]   = 5396  ;
        pstDmCfg->s16M33Src2Disp[0][2]   = 709   ;
        pstDmCfg->s16M33Src2Disp[1][0]   = 1133  ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 15066 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = 185   ;
        pstDmCfg->s16M33Src2Disp[2][0]   = 269   ;
        pstDmCfg->s16M33Src2Disp[2][1]   = 1442  ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 14672 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 2984 ; //BT709
        pstDmCfg->s16M33RGB2YUV[0][1]    = 10034;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 1013 ;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -1643;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5531;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175 ;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175 ;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6518;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -659 ;
        pstDmCfg->u16ScaleRGB2YUV        = 14   ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64   ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512  ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512  ;
    }
    else if (pstDmCfg->GdmSceneMode == GDM_709_IN_BT2020_OUT)
    {
        VDP_PRINT("GdmSceneMode == GDM_709_IN_BT2020_OUT\n");
        //typ mode

        pstDmCfg->vdm_en                 = 1  ;
        pstDmCfg->vdm_degmm_en           = 1  ;
        pstDmCfg->vdm_csc_en             = 1  ;
        pstDmCfg->vdm_tmap_en            = 0  ;
        pstDmCfg->vdm_gmm_en             = 1  ;
        pstDmCfg->vdm_dither_en          = 1  ;
        pstDmCfg->vdm_rgb2yuv_en         = 1  ;
        pstDmCfg->gdm_r2y_premult_en     = 0  ;

        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 8     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]   = 27209 ;
        pstDmCfg->s16M33Src2Disp[0][1]   = -9632 ;
        pstDmCfg->s16M33Src2Disp[0][2]   = -1194 ;
        pstDmCfg->s16M33Src2Disp[1][0]   = -2045 ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 18565 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = -138  ;
        pstDmCfg->s16M33Src2Disp[2][0]   = -297  ;
        pstDmCfg->s16M33Src2Disp[2][1]   = -1648 ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 18330 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 2984  ;
        pstDmCfg->s16M33RGB2YUV[0][1]    = 10034 ;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 1013  ;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -1643 ;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5531 ;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6518 ;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -659  ;
        pstDmCfg->u16ScaleRGB2YUV        = 14    ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0     ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64    ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512   ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512   ;
    }
    else if (pstDmCfg->GdmSceneMode == GDM_BYPASS_MODE)
    {
        VDP_PRINT("GdmSceneMode == GDM_BYPASS_MODE\n");
        //typ mode

        pstDmCfg->vdm_en                 = 0  ;
        pstDmCfg->vdm_degmm_en           = 0  ;
        pstDmCfg->vdm_csc_en             = 0  ;
        pstDmCfg->vdm_tmap_en            = 0  ;
        pstDmCfg->vdm_gmm_en             = 0  ;
        pstDmCfg->vdm_dither_en          = 0  ;
        pstDmCfg->vdm_rgb2yuv_en         = 1  ;
        pstDmCfg->gdm_r2y_premult_en     = 0  ;

        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 8     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]   = 27209 ;
        pstDmCfg->s16M33Src2Disp[0][1]   = -9632 ;
        pstDmCfg->s16M33Src2Disp[0][2]   = -1194 ;
        pstDmCfg->s16M33Src2Disp[1][0]   = -2045 ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 18565 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = -138  ;
        pstDmCfg->s16M33Src2Disp[2][0]   = -297  ;
        pstDmCfg->s16M33Src2Disp[2][1]   = -1648 ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 18330 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 2984  ;
        pstDmCfg->s16M33RGB2YUV[0][1]    = 10034 ;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 1013  ;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -1643 ;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5531 ;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6518 ;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -659  ;
        pstDmCfg->u16ScaleRGB2YUV        = 14    ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0     ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64    ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512   ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512   ;
    }
    else
    {
        VDP_PRINT("VDP_FUNC_SetGdmMode enter into typ mode\n");
        //typ mode

        pstDmCfg->u16M3LumaCal[0]        = 1076  ;
        pstDmCfg->u16M3LumaCal[1]        = 2777  ;
        pstDmCfg->u16M3LumaCal[2]        = 243   ;
        pstDmCfg->u16ScaleLumaCal        = 12    ;
        pstDmCfg->u16ScaleCoefTM         = 8     ;

        pstDmCfg->DePQPara.gmm_x1_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x2_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x3_step   = 4     ;
        pstDmCfg->DePQPara.gmm_x4_step   = 5     ;
        pstDmCfg->DePQPara.gmm_x1_pos    = 672   ;
        pstDmCfg->DePQPara.gmm_x2_pos    = 832   ;
        pstDmCfg->DePQPara.gmm_x3_pos    = 992   ;
        pstDmCfg->DePQPara.gmm_x4_pos    = 1023  ;
        pstDmCfg->DePQPara.gmm_x1_num    = 42    ;
        pstDmCfg->DePQPara.gmm_x2_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x3_num    = 10    ;
        pstDmCfg->DePQPara.gmm_x4_num    = 1     ;

        pstDmCfg->TMPara.gmm_x1_step     = 9     ;
        pstDmCfg->TMPara.gmm_x2_step     = 10    ;
        pstDmCfg->TMPara.gmm_x3_step     = 12    ;
        pstDmCfg->TMPara.gmm_x4_step     = 13    ;
        pstDmCfg->TMPara.gmm_x1_pos      = 8192  ;
        pstDmCfg->TMPara.gmm_x2_pos      = 16384 ;
        pstDmCfg->TMPara.gmm_x3_pos      = 24576 ;
        pstDmCfg->TMPara.gmm_x4_pos      = 65535 ;
        pstDmCfg->TMPara.gmm_x1_num      = 16    ;
        pstDmCfg->TMPara.gmm_x2_num      = 8     ;
        pstDmCfg->TMPara.gmm_x3_num      = 2     ;
        pstDmCfg->TMPara.gmm_x4_num      = 5     ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]   = 27209 ;
        pstDmCfg->s16M33Src2Disp[0][1]   = -9632 ;
        pstDmCfg->s16M33Src2Disp[0][2]   = -1194 ;
        pstDmCfg->s16M33Src2Disp[1][0]   = -2045 ;
        pstDmCfg->s16M33Src2Disp[1][1]   = 18565 ;
        pstDmCfg->s16M33Src2Disp[1][2]   = -138  ;
        pstDmCfg->s16M33Src2Disp[2][0]   = -297  ;
        pstDmCfg->s16M33Src2Disp[2][1]   = -1648 ;
        pstDmCfg->s16M33Src2Disp[2][2]   = 18330 ;
        pstDmCfg->u16ScaleSrc2Disp       = 14    ;

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647 ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;

        pstDmCfg->s16M33RGB2YUV[0][0]    = 2984  ;
        pstDmCfg->s16M33RGB2YUV[0][1]    = 10034 ;
        pstDmCfg->s16M33RGB2YUV[0][2]    = 1013  ;
        pstDmCfg->s16M33RGB2YUV[1][0]    = -1643 ;
        pstDmCfg->s16M33RGB2YUV[1][1]    = -5531 ;
        pstDmCfg->s16M33RGB2YUV[1][2]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][0]    = 7175  ;
        pstDmCfg->s16M33RGB2YUV[2][1]    = -6518 ;
        pstDmCfg->s16M33RGB2YUV[2][2]    = -659  ;
        pstDmCfg->u16ScaleRGB2YUV        = 14    ;
        pstDmCfg->s16InOffsetRGB2YUV[0]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[1]  = 0     ;
        pstDmCfg->s16InOffsetRGB2YUV[2]  = 0     ;
        pstDmCfg->s16OutOffsetRGB2YUV[0] = 64    ;
        pstDmCfg->s16OutOffsetRGB2YUV[1] = 512   ;
        pstDmCfg->s16OutOffsetRGB2YUV[2] = 512   ;
    }

    return HI_SUCCESS;
}
HI_S32 VDP_DRV_SetHiHdrGfxCfg(GdmCfg_t  *pstDmCfg)
{

    //filed declare
    HI_U32 gdm_en    =  0;
    HI_U32 gdm_degmm_en    =  0;
    HI_U32 gdm_csc_en    =  0;
    HI_U32 gdm_tmap_en    =  0;
    HI_U32 gdm_gmm_en    =  0;
    HI_U32 gdm_dither_en    =  0;
    HI_U32 gdm_rgb2yuv_en    =  0;

    HI_U32 gdm_tmap_in_bdp    =  0;
    HI_U32 gdm_dither_mode    =  0;

    HI_U16 gdm_luma_coef0_tmap    =  0;
    HI_U16 gdm_luma_coef1_tmap    =  0;
    HI_U16 gdm_luma_coef2_tmap    =  0;
    HI_U16 gdm_tmap_luma_scale    =  0;
    HI_U16 gdm_tmap_coef_scale    =  0;
    HI_U16 gdm_tmap_out_clip_min    =  0;
    HI_U16 gdm_tmap_out_clip_max    =  0;
    //  HI_U32 gdm_para_gmm_addr    =  0;
    //  HI_U32 gdm_para_tmap_addr    =  0;
    //  HI_U32 gdm_para_tmap_upd    =  1;
    //  HI_U32 gdm_para_gmm_upd    =  1;
    HI_U32 g_degmm_x4_step    =  0;
    HI_U32 g_degmm_x3_step    =  0;
    HI_U32 g_degmm_x2_step    =  0;
    HI_U32 g_degmm_x1_step    =  0;
    HI_U32 g_degmm_x2_pos    =  0;
    HI_U32 g_degmm_x1_pos    =  0;
    HI_U32 g_degmm_x4_pos    =  0;
    HI_U32 g_degmm_x3_pos    =  0;
    HI_U32 g_degmm_x4_num    =  0;
    HI_U32 g_degmm_x3_num    =  0;
    HI_U32 g_degmm_x2_num    =  0;
    HI_U32 g_degmm_x1_num    =  0;
    HI_U32 gdm_tmap_rd_en    =  0;
    HI_U32 gdm_tmap_para_data    =  0;
    HI_U32 g_tmap_x4_step    =  0;
    HI_U32 g_tmap_x3_step    =  0;
    HI_U32 g_tmap_x2_step    =  0;
    HI_U32 g_tmap_x1_step    =  0;
    HI_U32 g_tmap_x1_pos    =  0;
    HI_U32 g_tmap_x2_pos    =  0;
    HI_U32 g_tmap_x4_num    =  0;
    HI_U32 g_tmap_x3_num    =  0;
    HI_U32 g_tmap_x2_num    =  0;
    HI_U32 g_tmap_x1_num    =  0;
    HI_U32 g_tmap_x3_pos    =  0;
    HI_U32 g_tmap_x4_pos    =  0;
    HI_U32 gdm_gamma_rd_en    =  0;
    HI_U32 gdm_gamma_para_data    =  0;

    //add_regs
    HI_U32 g_gmm_x8_step = 0;
    HI_U32 g_gmm_x7_step = 0;
    HI_U32 g_gmm_x6_step = 0;
    HI_U32 g_gmm_x5_step = 0;
    HI_U32 g_gmm_x6_pos = 0;
    HI_U32 g_gmm_x5_pos = 0;
    HI_U32 g_gmm_x8_pos = 0;
    HI_U32 g_gmm_x7_pos = 0;
    HI_U32 g_gmm_x8_num = 0;
    HI_U32 g_gmm_x7_num = 0;
    HI_U32 g_gmm_x6_num = 0;
    HI_U32 g_gmm_x5_num = 0;

    HI_U32 g_gmm_x4_step    =  0;
    HI_U32 g_gmm_x3_step    =  0;
    HI_U32 g_gmm_x2_step    =  0;
    HI_U32 g_gmm_x1_step    =  0;
    HI_U32 g_gmm_x2_pos    =  0;
    HI_U32 g_gmm_x1_pos    =  0;
    HI_U32 g_gmm_x4_pos    =  0;
    HI_U32 g_gmm_x3_pos    =  0;
    HI_U32 g_gmm_x4_num    =  0;
    HI_U32 g_gmm_x3_num    =  0;
    HI_U32 g_gmm_x2_num    =  0;
    HI_U32 g_gmm_x1_num    =  0;
    HI_S16 gdm_coef00_csc    =  0;
    HI_S16 gdm_coef01_csc    =  0;
    HI_S16 gdm_coef02_csc    =  0;
    HI_S16 gdm_coef10_csc    =  0;
    HI_S16 gdm_coef11_csc    =  0;
    HI_S16 gdm_coef12_csc    =  0;
    HI_S16 gdm_coef20_csc    =  0;
    HI_S16 gdm_coef21_csc    =  0;
    HI_S16 gdm_coef22_csc    =  0;
    HI_U16 gdm_csc_scale    =  0;
    HI_U32 gdm_csc_clip_min    =  0;
    HI_U32 gdm_csc_clip_max    =  0;
    HI_S16 gdm_00_rgb2yuv    =  0;
    HI_S16 gdm_01_rgb2yuv    =  0;
    HI_S16 gdm_02_rgb2yuv    =  0;
    HI_S16 gdm_10_rgb2yuv    =  0;
    HI_S16 gdm_11_rgb2yuv    =  0;
    HI_S16 gdm_12_rgb2yuv    =  0;
    HI_S16 gdm_20_rgb2yuv    =  0;
    HI_S16 gdm_21_rgb2yuv    =  0;
    HI_S16 gdm_22_rgb2yuv    =  0;
    HI_U16 gdm_rgb2yuvscale2p    =  0;
    HI_S16 gdm_rgb2yuv_0_in_dc    =  0;
    HI_S16 gdm_rgb2yuv_1_in_dc    =  0;
    HI_S16 gdm_rgb2yuv_2_in_dc    =  0;
    HI_S16 gdm_rgb2yuv_0_out_dc    =  0;
    HI_S16 gdm_rgb2yuv_1_out_dc    =  0;
    HI_S16 gdm_rgb2yuv_2_out_dc    =  0;
    HI_U16 gdm_rgb2yuv_clip_min    =  0;
    HI_U16 gdm_rgb2yuv_clip_max    =  0;
    HI_U32 gdm_dither_round_unlim    =  0;
    HI_U32 gdm_dither_round    =  0;
    HI_U32 gdm_dither_domain_mode    =  0;
    HI_U32 gdm_dither_tap_mode    =  0;
    HI_U32 gdm_dither_sed_y0    =  0;
    HI_U32 gdm_dither_sed_u0    =  0;
    HI_U32 gdm_dither_sed_v0    =  0;
    HI_U32 gdm_dither_sed_w0    =  0;
    HI_U32 gdm_dither_sed_y1    =  0;
    HI_U32 gdm_dither_sed_u1    =  0;
    HI_U32 gdm_dither_sed_v1    =  0;
    HI_U32 gdm_dither_sed_w1    =  0;
    HI_U32 gdm_dither_sed_y2    =  0;
    HI_U32 gdm_dither_sed_u2    =  0;
    HI_U32 gdm_dither_sed_v2    =  0;
    HI_U32 gdm_dither_sed_w2    =  0;
    HI_U32 gdm_dither_sed_y3    =  0;
    HI_U32 gdm_dither_sed_u3    =  0;
    HI_U32 gdm_dither_sed_v3    =  0;
    HI_U32 gdm_dither_sed_w3    =  0;
    HI_U32 gdm_dither_thr_max    =  0;
    HI_U32 gdm_dither_thr_min    =  0;
    gdm_tmap_in_bdp   = pstDmCfg->vdm_tmap_in_bdp ;
    gdm_gmm_en        = pstDmCfg->vdm_gmm_en      ;
    gdm_tmap_en       = pstDmCfg->vdm_tmap_en     ;
    gdm_degmm_en      = pstDmCfg->vdm_degmm_en    ;
    gdm_en            = pstDmCfg->vdm_en          ;
    gdm_rgb2yuv_en    = pstDmCfg->vdm_rgb2yuv_en  ;
    gdm_csc_en        = pstDmCfg->vdm_csc_en      ;
    gdm_dither_en     = pstDmCfg->vdm_dither_en   ;
    gdm_dither_mode   = pstDmCfg->vdm_dither_mode ;

    gdm_luma_coef0_tmap       = pstDmCfg->u16M3LumaCal[0] ;// ;
    gdm_luma_coef1_tmap       = pstDmCfg->u16M3LumaCal[1] ;// ;
    gdm_luma_coef2_tmap       = pstDmCfg->u16M3LumaCal[2] ;// ;
    gdm_tmap_luma_scale       = pstDmCfg->u16ScaleLumaCal ;// ;
    gdm_tmap_coef_scale       = pstDmCfg->u16ScaleCoefTM  ;// ;
    gdm_tmap_out_clip_min     = pstDmCfg->u16ClipMinTM    ;// ;
    gdm_tmap_out_clip_max     = pstDmCfg->u16ClipMaxTM    ;// ;

    g_degmm_x1_step   = pstDmCfg->DePQPara.gmm_x1_step   ;// ;
    g_degmm_x2_step   = pstDmCfg->DePQPara.gmm_x2_step   ;// ;
    g_degmm_x3_step   = pstDmCfg->DePQPara.gmm_x3_step   ;// ;
    g_degmm_x4_step   = pstDmCfg->DePQPara.gmm_x4_step   ;// ;
    g_degmm_x1_pos    = pstDmCfg->DePQPara.gmm_x1_pos    ;// ;
    g_degmm_x2_pos    = pstDmCfg->DePQPara.gmm_x2_pos    ;// ;
    g_degmm_x3_pos    = pstDmCfg->DePQPara.gmm_x3_pos    ;// ;
    g_degmm_x4_pos    = pstDmCfg->DePQPara.gmm_x4_pos    ;// ;
    g_degmm_x1_num    = pstDmCfg->DePQPara.gmm_x1_num    ;// ;
    g_degmm_x2_num    = pstDmCfg->DePQPara.gmm_x2_num    ;// ;
    g_degmm_x3_num    = pstDmCfg->DePQPara.gmm_x3_num    ;// ;
    g_degmm_x4_num    = pstDmCfg->DePQPara.gmm_x4_num    ;// ;


    g_tmap_x1_step     = pstDmCfg->TMPara.gmm_x1_step ;// ;
    g_tmap_x2_step     = pstDmCfg->TMPara.gmm_x2_step ;// ;
    g_tmap_x3_step     = pstDmCfg->TMPara.gmm_x3_step ;// ;
    g_tmap_x4_step     = pstDmCfg->TMPara.gmm_x4_step ;// ;
    g_tmap_x1_pos      = pstDmCfg->TMPara.gmm_x1_pos  ;// ;
    g_tmap_x2_pos      = pstDmCfg->TMPara.gmm_x2_pos  ;// ;
    g_tmap_x3_pos      = pstDmCfg->TMPara.gmm_x3_pos  ;// ;
    g_tmap_x4_pos      = pstDmCfg->TMPara.gmm_x4_pos  ;// ;
    g_tmap_x1_num      = pstDmCfg->TMPara.gmm_x1_num  ;// ;
    g_tmap_x2_num      = pstDmCfg->TMPara.gmm_x2_num  ;// ;
    g_tmap_x3_num      = pstDmCfg->TMPara.gmm_x3_num  ;// ;
    g_tmap_x4_num      = pstDmCfg->TMPara.gmm_x4_num  ;// ;

    g_gmm_x1_step     = pstDmCfg->GammaPara.gmm_x1_step ;// ;
    g_gmm_x2_step     = pstDmCfg->GammaPara.gmm_x2_step ;// ;
    g_gmm_x3_step     = pstDmCfg->GammaPara.gmm_x3_step ;// ;
    g_gmm_x4_step     = pstDmCfg->GammaPara.gmm_x4_step ;// ;
    g_gmm_x5_step     = pstDmCfg->GammaPara.gmm_x5_step ;// ;
    g_gmm_x6_step     = pstDmCfg->GammaPara.gmm_x6_step ;// ;
    g_gmm_x7_step     = pstDmCfg->GammaPara.gmm_x7_step ;// ;
    g_gmm_x8_step     = pstDmCfg->GammaPara.gmm_x8_step ;// ;
    g_gmm_x1_pos      = pstDmCfg->GammaPara.gmm_x1_pos  ;// ;
    g_gmm_x2_pos      = pstDmCfg->GammaPara.gmm_x2_pos  ;// ;
    g_gmm_x3_pos      = pstDmCfg->GammaPara.gmm_x3_pos  ;// ;
    g_gmm_x4_pos      = pstDmCfg->GammaPara.gmm_x4_pos  ;// ;
    g_gmm_x5_pos      = pstDmCfg->GammaPara.gmm_x5_pos  ;// ;
    g_gmm_x6_pos      = pstDmCfg->GammaPara.gmm_x6_pos  ;// ;
    g_gmm_x7_pos      = pstDmCfg->GammaPara.gmm_x7_pos  ;// ;
    g_gmm_x8_pos      = pstDmCfg->GammaPara.gmm_x8_pos  ;// ;
    g_gmm_x1_num      = pstDmCfg->GammaPara.gmm_x1_num  ;// ;
    g_gmm_x2_num      = pstDmCfg->GammaPara.gmm_x2_num  ;// ;
    g_gmm_x3_num      = pstDmCfg->GammaPara.gmm_x3_num  ;// ;
    g_gmm_x4_num      = pstDmCfg->GammaPara.gmm_x4_num  ;// ;
    g_gmm_x5_num      = pstDmCfg->GammaPara.gmm_x5_num  ;// ;
    g_gmm_x6_num      = pstDmCfg->GammaPara.gmm_x6_num  ;// ;
    g_gmm_x7_num      = pstDmCfg->GammaPara.gmm_x7_num  ;// ;
    g_gmm_x8_num      = pstDmCfg->GammaPara.gmm_x8_num  ;// ;

    gdm_coef00_csc       = pstDmCfg->s16M33Src2Disp[0][0] ;// ;
    gdm_coef01_csc       = pstDmCfg->s16M33Src2Disp[0][1] ;// ;
    gdm_coef02_csc       = pstDmCfg->s16M33Src2Disp[0][2] ;// ;
    gdm_coef10_csc       = pstDmCfg->s16M33Src2Disp[1][0] ;// ;
    gdm_coef11_csc       = pstDmCfg->s16M33Src2Disp[1][1] ;// ;
    gdm_coef12_csc       = pstDmCfg->s16M33Src2Disp[1][2] ;// ;
    gdm_coef20_csc       = pstDmCfg->s16M33Src2Disp[2][0] ;// ;
    gdm_coef21_csc       = pstDmCfg->s16M33Src2Disp[2][1] ;// ;
    gdm_coef22_csc       = pstDmCfg->s16M33Src2Disp[2][2] ;// ;
    gdm_csc_scale        = pstDmCfg->u16ScaleSrc2Disp     ;// ;
    gdm_csc_clip_min     = pstDmCfg->u32ClipMinCSC        ;// ;
    gdm_csc_clip_max     = pstDmCfg->u32ClipMaxCSC        ;// ;

    gdm_rgb2yuvscale2p     = pstDmCfg->u16ScaleRGB2YUV         ; // ;
    gdm_rgb2yuv_0_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[0]   ; // ;
    gdm_rgb2yuv_1_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[1]   ; // ;
    gdm_rgb2yuv_2_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[2]   ; // ;
    gdm_rgb2yuv_0_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[0]  ; // ;
    gdm_rgb2yuv_1_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[1]  ; // ;
    gdm_rgb2yuv_2_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[2]  ; // ;
    gdm_rgb2yuv_clip_min   = pstDmCfg->u16ClipMinRGB2YUV       ; // ;
    gdm_rgb2yuv_clip_max   = pstDmCfg->u16ClipMaxRGB2YUV       ; // ;

    gdm_00_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][0];
    gdm_01_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][1];
    gdm_02_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][2];
    gdm_10_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][0];
    gdm_11_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][1];
    gdm_12_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][2];
    gdm_20_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][0];
    gdm_21_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][1];
    gdm_22_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][2];

    gdm_dither_round       = pstDmCfg->stDitherCfg.u32_dither_round       ;
    gdm_dither_domain_mode = pstDmCfg->stDitherCfg.u32_dither_domain_mode ;
    gdm_dither_tap_mode    = pstDmCfg->stDitherCfg.u32_dither_tap_mode    ;
    gdm_dither_round_unlim = pstDmCfg->stDitherCfg.u32_dither_round_unlim ;
    gdm_dither_sed_y0      = pstDmCfg->stDitherCfg.u32_dither_sed_y0      ;
    gdm_dither_sed_u0      = pstDmCfg->stDitherCfg.u32_dither_sed_u0      ;
    gdm_dither_sed_v0      = pstDmCfg->stDitherCfg.u32_dither_sed_v0      ;
    gdm_dither_sed_w0      = pstDmCfg->stDitherCfg.u32_dither_sed_w0      ;
    gdm_dither_sed_y1      = pstDmCfg->stDitherCfg.u32_dither_sed_y1      ;
    gdm_dither_sed_u1      = pstDmCfg->stDitherCfg.u32_dither_sed_u1      ;
    gdm_dither_sed_v1      = pstDmCfg->stDitherCfg.u32_dither_sed_v1      ;
    gdm_dither_sed_w1      = pstDmCfg->stDitherCfg.u32_dither_sed_w1      ;
    gdm_dither_thr_max     = pstDmCfg->stDitherCfg.u32_dither_thr_max     ;
    gdm_dither_thr_min     = pstDmCfg->stDitherCfg.u32_dither_thr_min     ;



#if 0
    //reg value print
    VDP_PRINT("gdm_tmap_in_bdp = %d \n", gdm_tmap_in_bdp);
    VDP_PRINT("gdm_gmm_en = %d \n", gdm_gmm_en);
    VDP_PRINT("gdm_tmap_en = %d \n", gdm_tmap_en);
    VDP_PRINT("gdm_degmm_en = %d \n", gdm_degmm_en);
    VDP_PRINT("gdm_en = %d \n", gdm_en);
    VDP_PRINT("gdm_luma_coef0_tmap = %d \n", gdm_luma_coef0_tmap);
    VDP_PRINT("gdm_luma_coef1_tmap = %d \n", gdm_luma_coef1_tmap);
    VDP_PRINT("gdm_luma_coef2_tmap = %d \n", gdm_luma_coef2_tmap);
    VDP_PRINT("gdm_tmap_luma_scale = %d \n", gdm_tmap_luma_scale);
    VDP_PRINT("gdm_tmap_coef_scale = %d \n", gdm_tmap_coef_scale);
    VDP_PRINT("gdm_tmap_out_clip_min = %d \n", gdm_tmap_out_clip_min);
    VDP_PRINT("gdm_tmap_out_clip_max = %d \n", gdm_tmap_out_clip_max);
    VDP_PRINT("gdm_para_gmm_addr = %d \n", gdm_para_gmm_addr);
    VDP_PRINT("gdm_para_tmap_addr = %d \n", gdm_para_tmap_addr);
    VDP_PRINT("gdm_para_tmap_upd = %d \n", gdm_para_tmap_upd);
    VDP_PRINT("gdm_para_gmm_upd = %d \n", gdm_para_gmm_upd);
    VDP_PRINT("g_degmm_x4_step = %d \n", g_degmm_x4_step);
    VDP_PRINT("g_degmm_x3_step = %d \n", g_degmm_x3_step);
    VDP_PRINT("g_degmm_x2_step = %d \n", g_degmm_x2_step);
    VDP_PRINT("g_degmm_x1_step = %d \n", g_degmm_x1_step);
    VDP_PRINT("g_degmm_x2_pos = %d \n", g_degmm_x2_pos);
    VDP_PRINT("g_degmm_x1_pos = %d \n", g_degmm_x1_pos);
    VDP_PRINT("g_degmm_x4_pos = %d \n", g_degmm_x4_pos);
    VDP_PRINT("g_degmm_x3_pos = %d \n", g_degmm_x3_pos);
    VDP_PRINT("g_degmm_x4_num = %d \n", g_degmm_x4_num);
    VDP_PRINT("g_degmm_x3_num = %d \n", g_degmm_x3_num);
    VDP_PRINT("g_degmm_x2_num = %d \n", g_degmm_x2_num);
    VDP_PRINT("g_degmm_x1_num = %d \n", g_degmm_x1_num);
    VDP_PRINT("gdm_tmap_rd_en = %d \n", gdm_tmap_rd_en);
    VDP_PRINT("gdm_tmap_para_data = %d \n", gdm_tmap_para_data);
    VDP_PRINT("g_tmap_x4_step = %d \n", g_tmap_x4_step);
    VDP_PRINT("g_tmap_x3_step = %d \n", g_tmap_x3_step);
    VDP_PRINT("g_tmap_x2_step = %d \n", g_tmap_x2_step);
    VDP_PRINT("g_tmap_x1_step = %d \n", g_tmap_x1_step);
    VDP_PRINT("g_tmap_x1_pos = %d \n", g_tmap_x1_pos);
    VDP_PRINT("g_tmap_x2_pos = %d \n", g_tmap_x2_pos);
    VDP_PRINT("g_tmap_x4_num = %d \n", g_tmap_x4_num);
    VDP_PRINT("g_tmap_x3_num = %d \n", g_tmap_x3_num);
    VDP_PRINT("g_tmap_x2_num = %d \n", g_tmap_x2_num);
    VDP_PRINT("g_tmap_x1_num = %d \n", g_tmap_x1_num);
    VDP_PRINT("g_tmap_x3_pos = %d \n", g_tmap_x3_pos);
    VDP_PRINT("g_tmap_x4_pos = %d \n", g_tmap_x4_pos);
    VDP_PRINT("gdm_gamma_rd_en = %d \n", gdm_gamma_rd_en);
    VDP_PRINT("gdm_gamma_para_data = %d \n", gdm_gamma_para_data);
    VDP_PRINT("g_gmm_x4_step = %d \n", g_gmm_x4_step);
    VDP_PRINT("g_gmm_x3_step = %d \n", g_gmm_x3_step);
    VDP_PRINT("g_gmm_x2_step = %d \n", g_gmm_x2_step);
    VDP_PRINT("g_gmm_x1_step = %d \n", g_gmm_x1_step);
    VDP_PRINT("g_gmm_x2_pos = %d \n", g_gmm_x2_pos);
    VDP_PRINT("g_gmm_x1_pos = %d \n", g_gmm_x1_pos);
    VDP_PRINT("g_gmm_x4_pos = %d \n", g_gmm_x4_pos);
    VDP_PRINT("g_gmm_x3_pos = %d \n", g_gmm_x3_pos);
    VDP_PRINT("g_gmm_x4_num = %d \n", g_gmm_x4_num);
    VDP_PRINT("g_gmm_x3_num = %d \n", g_gmm_x3_num);
    VDP_PRINT("g_gmm_x2_num = %d \n", g_gmm_x2_num);
    VDP_PRINT("g_gmm_x1_num = %d \n", g_gmm_x1_num);
    VDP_PRINT("gdm_csc_en = %d \n", gdm_csc_en);
    VDP_PRINT("gdm_coef00_csc = %d \n", gdm_coef00_csc);
    VDP_PRINT("gdm_coef01_csc = %d \n", gdm_coef01_csc);
    VDP_PRINT("gdm_coef02_csc = %d \n", gdm_coef02_csc);
    VDP_PRINT("gdm_coef10_csc = %d \n", gdm_coef10_csc);
    VDP_PRINT("gdm_coef11_csc = %d \n", gdm_coef11_csc);
    VDP_PRINT("gdm_coef12_csc = %d \n", gdm_coef12_csc);
    VDP_PRINT("gdm_coef20_csc = %d \n", gdm_coef20_csc);
    VDP_PRINT("gdm_coef21_csc = %d \n", gdm_coef21_csc);
    VDP_PRINT("gdm_coef22_csc = %d \n", gdm_coef22_csc);
    VDP_PRINT("gdm_csc_scale = %d \n", gdm_csc_scale);
    VDP_PRINT("gdm_csc_clip_min = %d \n", gdm_csc_clip_min);
    VDP_PRINT("gdm_csc_clip_max = %d \n", gdm_csc_clip_max);
    VDP_PRINT("gdm_rgb2yuv_en = %d \n", gdm_rgb2yuv_en);
    VDP_PRINT("gdm_00_rgb2yuv = %d \n", gdm_00_rgb2yuv);
    VDP_PRINT("gdm_01_rgb2yuv = %d \n", gdm_01_rgb2yuv);
    VDP_PRINT("gdm_02_rgb2yuv = %d \n", gdm_02_rgb2yuv);
    VDP_PRINT("gdm_10_rgb2yuv = %d \n", gdm_10_rgb2yuv);
    VDP_PRINT("gdm_11_rgb2yuv = %d \n", gdm_11_rgb2yuv);
    VDP_PRINT("gdm_12_rgb2yuv = %d \n", gdm_12_rgb2yuv);
    VDP_PRINT("gdm_20_rgb2yuv = %d \n", gdm_20_rgb2yuv);
    VDP_PRINT("gdm_21_rgb2yuv = %d \n", gdm_21_rgb2yuv);
    VDP_PRINT("gdm_22_rgb2yuv = %d \n", gdm_22_rgb2yuv);
    VDP_PRINT("gdm_rgb2yuvscale2p = %d \n", gdm_rgb2yuvscale2p);
    VDP_PRINT("gdm_rgb2yuv_0_in_dc = %d \n", gdm_rgb2yuv_0_in_dc);
    VDP_PRINT("gdm_rgb2yuv_1_in_dc = %d \n", gdm_rgb2yuv_1_in_dc);
    VDP_PRINT("gdm_rgb2yuv_2_in_dc = %d \n", gdm_rgb2yuv_2_in_dc);
    VDP_PRINT("gdm_rgb2yuv_0_out_dc = %d \n", gdm_rgb2yuv_0_out_dc);
    VDP_PRINT("gdm_rgb2yuv_1_out_dc = %d \n", gdm_rgb2yuv_1_out_dc);
    VDP_PRINT("gdm_rgb2yuv_2_out_dc = %d \n", gdm_rgb2yuv_2_out_dc);
    VDP_PRINT("gdm_rgb2yuv_clip_min = %d \n", gdm_rgb2yuv_clip_min);
    VDP_PRINT("gdm_rgb2yuv_clip_max = %d \n", gdm_rgb2yuv_clip_max);
    VDP_PRINT("gdm_dither_round_unlim = %d \n", gdm_dither_round_unlim);
    VDP_PRINT("gdm_dither_en = %d \n", gdm_dither_en);
    VDP_PRINT("gdm_dither_mode = %d \n", gdm_dither_mode);
    VDP_PRINT("gdm_dither_round = %d \n", gdm_dither_round);
    VDP_PRINT("gdm_dither_domain_mode = %d \n", gdm_dither_domain_mode);
    VDP_PRINT("gdm_dither_tap_mode = %d \n", gdm_dither_tap_mode);
    VDP_PRINT("gdm_dither_sed_y0 = %d \n", gdm_dither_sed_y0);
    VDP_PRINT("gdm_dither_sed_u0 = %d \n", gdm_dither_sed_u0);
    VDP_PRINT("gdm_dither_sed_v0 = %d \n", gdm_dither_sed_v0);
    VDP_PRINT("gdm_dither_sed_w0 = %d \n", gdm_dither_sed_w0);
    VDP_PRINT("gdm_dither_sed_y1 = %d \n", gdm_dither_sed_y1);
    VDP_PRINT("gdm_dither_sed_u1 = %d \n", gdm_dither_sed_u1);
    VDP_PRINT("gdm_dither_sed_v1 = %d \n", gdm_dither_sed_v1);
    VDP_PRINT("gdm_dither_sed_w1 = %d \n", gdm_dither_sed_w1);
    VDP_PRINT("gdm_dither_sed_y2 = %d \n", gdm_dither_sed_y2);
    VDP_PRINT("gdm_dither_sed_u2 = %d \n", gdm_dither_sed_u2);
    VDP_PRINT("gdm_dither_sed_v2 = %d \n", gdm_dither_sed_v2);
    VDP_PRINT("gdm_dither_sed_w2 = %d \n", gdm_dither_sed_w2);
    VDP_PRINT("gdm_dither_sed_y3 = %d \n", gdm_dither_sed_y3);
    VDP_PRINT("gdm_dither_sed_u3 = %d \n", gdm_dither_sed_u3);
    VDP_PRINT("gdm_dither_sed_v3 = %d \n", gdm_dither_sed_v3);
    VDP_PRINT("gdm_dither_sed_w3 = %d \n", gdm_dither_sed_w3);
    VDP_PRINT("gdm_dither_thr_max = %d \n", gdm_dither_thr_max);
    VDP_PRINT("gdm_dither_thr_min = %d \n", gdm_dither_thr_min);
#endif
    //drv transfer
    VDP_GP_SetGdmGdmTmapInBdp(VDP_LAYER_GP0, gdm_tmap_in_bdp);
    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, gdm_gmm_en);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, gdm_tmap_en);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, gdm_degmm_en);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, gdm_en);
    VDP_GP_SetGdmGdmLumaCoef0Tmap(VDP_LAYER_GP0, gdm_luma_coef0_tmap);
    VDP_GP_SetGdmGdmLumaCoef1Tmap(VDP_LAYER_GP0, gdm_luma_coef1_tmap);
    VDP_GP_SetGdmGdmLumaCoef2Tmap(VDP_LAYER_GP0, gdm_luma_coef2_tmap);
    VDP_GP_SetGdmGdmTmapLumaScale(VDP_LAYER_GP0, gdm_tmap_luma_scale);
    VDP_GP_SetGdmGdmTmapCoefScale(VDP_LAYER_GP0, gdm_tmap_coef_scale);
    VDP_GP_SetGdmGdmTmapOutClipMin(VDP_LAYER_GP0, gdm_tmap_out_clip_min);
    VDP_GP_SetGdmGdmTmapOutClipMax(VDP_LAYER_GP0, gdm_tmap_out_clip_max);
    //VDP_GP_SetGdmGdmParaGmmAddr(VDP_LAYER_GP0, gdm_para_gmm_addr);
    //VDP_GP_SetGdmGdmParaTmapAddr(VDP_LAYER_GP0, gdm_para_tmap_addr);
    //VDP_GP_SetGdmGdmParaTmapUpd(VDP_LAYER_GP0, gdm_para_tmap_upd);
    //VDP_GP_SetGdmGdmParaGmmUpd(VDP_LAYER_GP0, gdm_para_gmm_upd);
    //add_regs
    VDP_GP_SetGdmGGmmX5Num(VDP_LAYER_GP0, g_gmm_x5_num);
    VDP_GP_SetGdmGGmmX6Num(VDP_LAYER_GP0, g_gmm_x6_num);
    VDP_GP_SetGdmGGmmX7Num(VDP_LAYER_GP0, g_gmm_x7_num);
    VDP_GP_SetGdmGGmmX8Num(VDP_LAYER_GP0, g_gmm_x8_num);
    VDP_GP_SetGdmGGmmX7Pos(VDP_LAYER_GP0, g_gmm_x7_pos);
    VDP_GP_SetGdmGGmmX8Pos(VDP_LAYER_GP0, g_gmm_x8_pos);
    VDP_GP_SetGdmGGmmX5Pos(VDP_LAYER_GP0, g_gmm_x5_pos);
    VDP_GP_SetGdmGGmmX6Pos(VDP_LAYER_GP0, g_gmm_x6_pos);
    VDP_GP_SetGdmGGmmX5Step(VDP_LAYER_GP0, g_gmm_x5_step);
    VDP_GP_SetGdmGGmmX6Step(VDP_LAYER_GP0, g_gmm_x6_step);
    VDP_GP_SetGdmGGmmX7Step(VDP_LAYER_GP0, g_gmm_x7_step);
    VDP_GP_SetGdmGGmmX8Step(VDP_LAYER_GP0, g_gmm_x8_step);

    VDP_GP_SetGdmGDegmmX4Step(VDP_LAYER_GP0, g_degmm_x4_step);
    VDP_GP_SetGdmGDegmmX3Step(VDP_LAYER_GP0, g_degmm_x3_step);
    VDP_GP_SetGdmGDegmmX2Step(VDP_LAYER_GP0, g_degmm_x2_step);
    VDP_GP_SetGdmGDegmmX1Step(VDP_LAYER_GP0, g_degmm_x1_step);
    VDP_GP_SetGdmGDegmmX2Pos(VDP_LAYER_GP0, g_degmm_x2_pos);
    VDP_GP_SetGdmGDegmmX1Pos(VDP_LAYER_GP0, g_degmm_x1_pos);
    VDP_GP_SetGdmGDegmmX4Pos(VDP_LAYER_GP0, g_degmm_x4_pos);
    VDP_GP_SetGdmGDegmmX3Pos(VDP_LAYER_GP0, g_degmm_x3_pos);
    VDP_GP_SetGdmGDegmmX4Num(VDP_LAYER_GP0, g_degmm_x4_num);
    VDP_GP_SetGdmGDegmmX3Num(VDP_LAYER_GP0, g_degmm_x3_num);
    VDP_GP_SetGdmGDegmmX2Num(VDP_LAYER_GP0, g_degmm_x2_num);
    VDP_GP_SetGdmGDegmmX1Num(VDP_LAYER_GP0, g_degmm_x1_num);
    VDP_GP_SetGdmGdmTmapRdEn(VDP_LAYER_GP0, gdm_tmap_rd_en);
    VDP_GP_SetGdmGdmTmapParaData(VDP_LAYER_GP0, gdm_tmap_para_data);
    VDP_GP_SetGdmGTmapX4Step(VDP_LAYER_GP0, g_tmap_x4_step);
    VDP_GP_SetGdmGTmapX3Step(VDP_LAYER_GP0, g_tmap_x3_step);
    VDP_GP_SetGdmGTmapX2Step(VDP_LAYER_GP0, g_tmap_x2_step);
    VDP_GP_SetGdmGTmapX1Step(VDP_LAYER_GP0, g_tmap_x1_step);
    VDP_GP_SetGdmGTmapX1Pos(VDP_LAYER_GP0, g_tmap_x1_pos);
    VDP_GP_SetGdmGTmapX2Pos(VDP_LAYER_GP0, g_tmap_x2_pos);
    VDP_GP_SetGdmGTmapX4Num(VDP_LAYER_GP0, g_tmap_x4_num);
    VDP_GP_SetGdmGTmapX3Num(VDP_LAYER_GP0, g_tmap_x3_num);
    VDP_GP_SetGdmGTmapX2Num(VDP_LAYER_GP0, g_tmap_x2_num);
    VDP_GP_SetGdmGTmapX1Num(VDP_LAYER_GP0, g_tmap_x1_num);
    VDP_GP_SetGdmGTmapX3Pos(VDP_LAYER_GP0, g_tmap_x3_pos);
    VDP_GP_SetGdmGTmapX4Pos(VDP_LAYER_GP0, g_tmap_x4_pos);
    VDP_GP_SetGdmGdmGammaRdEn(VDP_LAYER_GP0, gdm_gamma_rd_en);
    VDP_GP_SetGdmGdmGammaParaData(VDP_LAYER_GP0, gdm_gamma_para_data);
    VDP_GP_SetGdmGGmmX4Step(VDP_LAYER_GP0, g_gmm_x4_step);
    VDP_GP_SetGdmGGmmX3Step(VDP_LAYER_GP0, g_gmm_x3_step);
    VDP_GP_SetGdmGGmmX2Step(VDP_LAYER_GP0, g_gmm_x2_step);
    VDP_GP_SetGdmGGmmX1Step(VDP_LAYER_GP0, g_gmm_x1_step);
    VDP_GP_SetGdmGGmmX2Pos(VDP_LAYER_GP0, g_gmm_x2_pos);
    VDP_GP_SetGdmGGmmX1Pos(VDP_LAYER_GP0, g_gmm_x1_pos);
    VDP_GP_SetGdmGGmmX4Pos(VDP_LAYER_GP0, g_gmm_x4_pos);
    VDP_GP_SetGdmGGmmX3Pos(VDP_LAYER_GP0, g_gmm_x3_pos);
    VDP_GP_SetGdmGGmmX4Num(VDP_LAYER_GP0, g_gmm_x4_num);
    VDP_GP_SetGdmGGmmX3Num(VDP_LAYER_GP0, g_gmm_x3_num);
    VDP_GP_SetGdmGGmmX2Num(VDP_LAYER_GP0, g_gmm_x2_num);
    VDP_GP_SetGdmGGmmX1Num(VDP_LAYER_GP0, g_gmm_x1_num);
    VDP_GP_SetGdmGdmCscEn(VDP_LAYER_GP0, gdm_csc_en);
    VDP_GP_SetGdmGdmCoef00Csc(VDP_LAYER_GP0, gdm_coef00_csc);
    VDP_GP_SetGdmGdmCoef01Csc(VDP_LAYER_GP0, gdm_coef01_csc);
    VDP_GP_SetGdmGdmCoef02Csc(VDP_LAYER_GP0, gdm_coef02_csc);
    VDP_GP_SetGdmGdmCoef10Csc(VDP_LAYER_GP0, gdm_coef10_csc);
    VDP_GP_SetGdmGdmCoef11Csc(VDP_LAYER_GP0, gdm_coef11_csc);
    VDP_GP_SetGdmGdmCoef12Csc(VDP_LAYER_GP0, gdm_coef12_csc);
    VDP_GP_SetGdmGdmCoef20Csc(VDP_LAYER_GP0, gdm_coef20_csc);
    VDP_GP_SetGdmGdmCoef21Csc(VDP_LAYER_GP0, gdm_coef21_csc);
    VDP_GP_SetGdmGdmCoef22Csc(VDP_LAYER_GP0, gdm_coef22_csc);
    VDP_GP_SetGdmGdmCscScale(VDP_LAYER_GP0, gdm_csc_scale);
    VDP_GP_SetGdmGdmCscClipMin(VDP_LAYER_GP0, gdm_csc_clip_min);
    VDP_GP_SetGdmGdmCscClipMax(VDP_LAYER_GP0, gdm_csc_clip_max);
    VDP_GP_SetGdmGdmRgb2yuvEn(VDP_LAYER_GP0, gdm_rgb2yuv_en);
    VDP_GP_SetGdmGdm00Rgb2yuv(VDP_LAYER_GP0, gdm_00_rgb2yuv);
    VDP_GP_SetGdmGdm01Rgb2yuv(VDP_LAYER_GP0, gdm_01_rgb2yuv);
    VDP_GP_SetGdmGdm02Rgb2yuv(VDP_LAYER_GP0, gdm_02_rgb2yuv);
    VDP_GP_SetGdmGdm10Rgb2yuv(VDP_LAYER_GP0, gdm_10_rgb2yuv);
    VDP_GP_SetGdmGdm11Rgb2yuv(VDP_LAYER_GP0, gdm_11_rgb2yuv);
    VDP_GP_SetGdmGdm12Rgb2yuv(VDP_LAYER_GP0, gdm_12_rgb2yuv);
    VDP_GP_SetGdmGdm20Rgb2yuv(VDP_LAYER_GP0, gdm_20_rgb2yuv);
    VDP_GP_SetGdmGdm21Rgb2yuv(VDP_LAYER_GP0, gdm_21_rgb2yuv);
    VDP_GP_SetGdmGdm22Rgb2yuv(VDP_LAYER_GP0, gdm_22_rgb2yuv);
    VDP_GP_SetGdmGdmRgb2yuvscale2p(VDP_LAYER_GP0, gdm_rgb2yuvscale2p);
    VDP_GP_SetGdmGdmRgb2yuv0InDc(VDP_LAYER_GP0, gdm_rgb2yuv_0_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv1InDc(VDP_LAYER_GP0, gdm_rgb2yuv_1_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv2InDc(VDP_LAYER_GP0, gdm_rgb2yuv_2_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv0OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_0_out_dc);
    VDP_GP_SetGdmGdmRgb2yuv1OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_1_out_dc);
    VDP_GP_SetGdmGdmRgb2yuv2OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_2_out_dc);
    VDP_GP_SetGdmGdmRgb2yuvClipMin(VDP_LAYER_GP0, gdm_rgb2yuv_clip_min);
    VDP_GP_SetGdmGdmRgb2yuvClipMax(VDP_LAYER_GP0, gdm_rgb2yuv_clip_max);
    VDP_GP_SetGdmGdmDitherRoundUnlim(VDP_LAYER_GP0, gdm_dither_round_unlim);
    VDP_GP_SetGdmGdmDitherEn(VDP_LAYER_GP0, gdm_dither_en);
    VDP_GP_SetGdmGdmDitherMode(VDP_LAYER_GP0, gdm_dither_mode);
    VDP_GP_SetGdmGdmDitherRound(VDP_LAYER_GP0, gdm_dither_round);
    VDP_GP_SetGdmGdmDitherDomainMode(VDP_LAYER_GP0, gdm_dither_domain_mode);
    VDP_GP_SetGdmGdmDitherTapMode(VDP_LAYER_GP0, gdm_dither_tap_mode);
    VDP_GP_SetGdmGdmDitherSedY0(VDP_LAYER_GP0, gdm_dither_sed_y0);
    VDP_GP_SetGdmGdmDitherSedU0(VDP_LAYER_GP0, gdm_dither_sed_u0);
    VDP_GP_SetGdmGdmDitherSedV0(VDP_LAYER_GP0, gdm_dither_sed_v0);
    VDP_GP_SetGdmGdmDitherSedW0(VDP_LAYER_GP0, gdm_dither_sed_w0);
    VDP_GP_SetGdmGdmDitherSedY1(VDP_LAYER_GP0, gdm_dither_sed_y1);
    VDP_GP_SetGdmGdmDitherSedU1(VDP_LAYER_GP0, gdm_dither_sed_u1);
    VDP_GP_SetGdmGdmDitherSedV1(VDP_LAYER_GP0, gdm_dither_sed_v1);
    VDP_GP_SetGdmGdmDitherSedW1(VDP_LAYER_GP0, gdm_dither_sed_w1);
    VDP_GP_SetGdmGdmDitherSedY2(VDP_LAYER_GP0, gdm_dither_sed_y2);
    VDP_GP_SetGdmGdmDitherSedU2(VDP_LAYER_GP0, gdm_dither_sed_u2);
    VDP_GP_SetGdmGdmDitherSedV2(VDP_LAYER_GP0, gdm_dither_sed_v2);
    VDP_GP_SetGdmGdmDitherSedW2(VDP_LAYER_GP0, gdm_dither_sed_w2);
    VDP_GP_SetGdmGdmDitherSedY3(VDP_LAYER_GP0, gdm_dither_sed_y3);
    VDP_GP_SetGdmGdmDitherSedU3(VDP_LAYER_GP0, gdm_dither_sed_u3);
    VDP_GP_SetGdmGdmDitherSedV3(VDP_LAYER_GP0, gdm_dither_sed_v3);
    VDP_GP_SetGdmGdmDitherSedW3(VDP_LAYER_GP0, gdm_dither_sed_w3);
    VDP_GP_SetGdmGdmDitherThrMax(VDP_LAYER_GP0, gdm_dither_thr_max);
    VDP_GP_SetGdmGdmDitherThrMin(VDP_LAYER_GP0, gdm_dither_thr_min);

    return HI_SUCCESS;

}

HI_VOID VDP_DRV_SetGdmMode(HI_U32 u32LayerId, GDM_SCENE_MODE_E  enGdmSceneMode)
{
    GdmCfg_t  pstDmCfg;

    if (VDP_LAYER_VID3 == u32LayerId || (GDM_BYPASS_MODE == enGdmSceneMode))
    {
        return ;
    }

    memset((HI_VOID *)&pstDmCfg,0,sizeof(pstDmCfg));

    pstDmCfg.vdm_tmap_in_bdp        = 0 ;//1:20bit for vdm , 0:16bit for gdm
    pstDmCfg.u16ClipMinTM           = 0     ;
    pstDmCfg.u16ClipMaxTM           = 65535 ;
    pstDmCfg.u32ClipMinCSC          = 0     ;
    pstDmCfg.u32ClipMaxCSC          = 65535 ; //16bits
    pstDmCfg.u16ClipMinRGB2YUV      = 0     ;
    pstDmCfg.u16ClipMaxRGB2YUV      = 1023  ;


    pstDmCfg.GdmSceneMode                         = enGdmSceneMode ;

    Vdp_Drv_SetGdmCoef_Tmmp(enGdmSceneMode);
    Vdp_Drv_SetGdmCoef_Gmma(enGdmSceneMode);

    VDP_DRV_GetHiHdrGfxCfg(&pstDmCfg);
    VDP_DRV_SetHiHdrGfxCfg(&pstDmCfg);
    return;
}


HI_S32 XDP_DRV_GetGfxSceneMode(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, GDM_SCENE_MODE_E  *enGdmSceneMode)
{

    XDP_DISP_OUT_TYPE_E  enDisPlayMode = pstInfoOut->stXdpDispCfg.enDisPlayMode;

    if (VDP_LAYER_VID3 == u32LayerId)
    {
        return HI_SUCCESS;
    }

    switch (enDisPlayMode)
    {
        case XDP_DISP_TYPE_NORMAL:
            *enGdmSceneMode = GDM_BYPASS_MODE;

            break;
        case XDP_DISP_TYPE_HDR10:
            *enGdmSceneMode = GDM_SDR_IN_HDR10_OUT;

            break;
        case XDP_DISP_TYPE_HLG:
            *enGdmSceneMode = GDM_SDR_IN_HLG_OUT;
            break;
        case XDP_DISP_TYPE_TECHNICOLOR:
            VDP_PRINT("Unsupport play mode currently.\n");
            // TODO:
        default:
            *enGdmSceneMode = HIHDR_BYPASS_MODE;
            break;
    }


    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidSceneMode(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, HIHDR_SCENE_MODE_E *enSceneMode)
{

    XDP_VIDEO_FRAME_TYPE_E enFrmType   = pstInfoOut->stXdpSrcCfg.enXdpViDeoFrameType;
    XDP_DISP_OUT_TYPE_E  enDisPlayMode = pstInfoOut->stXdpDispCfg.enDisPlayMode;

    switch (enDisPlayMode)
    {
        case XDP_DISP_TYPE_NORMAL:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    if (((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                         || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                         || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpDispCfg.enOutClrSpace )))
                    {
                        *enSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else if (((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                              || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )) &&
                             ((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                              || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpDispCfg.enOutClrSpace )))
                    {
                        *enSceneMode = HIHDR_709_IN_BT2020_OUT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *enSceneMode = HIHDR_HDR10_IN_SDR_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    *enSceneMode = HIHDR_HLG_IN_SDR_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *enSceneMode = HIHDR_SLF_IN_SDR_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *enSceneMode = HIHDR_TECHNI_IN_SDR_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_HDR10:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *enSceneMode = HIHDR_SDR_IN_HDR10_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    if (((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                         || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpDispCfg.enOutClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                         || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *enSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else  if (((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                               || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpDispCfg.enOutClrSpace )) &&
                              ((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *enSceneMode = HIHDR_709_IN_BT2020_OUT;

                    }
                    else
                    {
                        *enSceneMode = HIHDR_BYPASS_MODE;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    *enSceneMode = HIHDR_HLG_IN_HDR10_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *enSceneMode = HIHDR_SLF_IN_HDR10_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *enSceneMode = HIHDR_TECHNI_IN_HDR10_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }

            break;
        case XDP_DISP_TYPE_HLG:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *enSceneMode = HIHDR_SDR_IN_HLG_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    if(((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                        || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpDispCfg.enOutClrSpace ))&&
                        ((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *enSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else  if(((VDP_CLR_SPACE_YUV_2020   == pstInfoOut->stXdpDispCfg.enOutClrSpace)
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoOut->stXdpDispCfg.enOutClrSpace ))&&
                        ((VDP_CLR_SPACE_YUV_709   == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_709_L == pstInfoOut->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *enSceneMode = HIHDR_709_IN_BT2020_OUT;

                    }
                    else
                    {
                        *enSceneMode = HIHDR_BYPASS_MODE;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *enSceneMode = HIHDR_HDR10_IN_HLG_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *enSceneMode = HIHDR_SLF_IN_HLG_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *enSceneMode = HIHDR_TECHNI_IN_HLG_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_TECHNICOLOR:
            VDP_PRINT("Unsupport mode currently.\n");
            // TODO:
            break;
        default:
            *enSceneMode = HIHDR_BYPASS_MODE;
            break;
    }

    /* vdm process according to the driver policy  */
    if(*enSceneMode != HIHDR_BYPASS_MODE)
    {
        if(pstInfoOut->stXdpSysCfg.u32VdmOnLayerId != u32LayerId)
        {
            *enSceneMode = HIHDR_BYPASS_MODE;
        }
    }

    return HI_SUCCESS;
}


HI_VOID VDP_DRV_SetHiHdrAjust(HI_PQ_HDR_CFG  *HiHdrCfg, DmCfg_t  *pstDmCfg)
{
    //接口转换

    pstDmCfg->vdm_csc_bind = HiHdrCfg->bGMapPosSel;
    //pstDmCfg->stDitherCfg.u32_dither_domain_mode = HiHdrCfg->bDITHER_MODE;//98mv200dither mode 不需要配置


    pstDmCfg->vdm_yuv2rgb_en                 = HiHdrCfg->bY2REn;
    pstDmCfg->vdm_degmm_en                   = HiHdrCfg->bDegammaEn;
    pstDmCfg->vdm_csc_en                     = HiHdrCfg->bGMapEn ;
    pstDmCfg->vdm_tmap_en                    = HiHdrCfg->bTMapEn;
    pstDmCfg->vdm_gmm_en                     = HiHdrCfg->bGammaEn;
    pstDmCfg->vdm_dither_en                  = HiHdrCfg->bDitherEn ;
    pstDmCfg->vdm_rgb2yuv_en                 = HiHdrCfg->bR2YEn ;
    pstDmCfg->vdm_v0_csc_en                  = HiHdrCfg->bY2REn ;
    pstDmCfg->vdm_v1_csc_en                  = 0 ;
    pstDmCfg->vdm_v0_gamma_en                = HiHdrCfg->bGammaEn ;
    pstDmCfg->vdm_v1_gamma_en                = 0;



    /********** YUV2RGB **********/


    pstDmCfg->s16M33YUV2RGB0[0][0]          = HiHdrCfg->stY2R.as16M33Y2R[0][0]  ; //BT2020
    pstDmCfg->s16M33YUV2RGB0[0][1]          = HiHdrCfg->stY2R.as16M33Y2R[0][1]  ;
    pstDmCfg->s16M33YUV2RGB0[0][2]          = HiHdrCfg->stY2R.as16M33Y2R[0][2]  ;
    pstDmCfg->s16M33YUV2RGB0[1][0]          = HiHdrCfg->stY2R.as16M33Y2R[1][0]  ;
    pstDmCfg->s16M33YUV2RGB0[1][1]          = HiHdrCfg->stY2R.as16M33Y2R[1][1]  ;
    pstDmCfg->s16M33YUV2RGB0[1][2]          = HiHdrCfg->stY2R.as16M33Y2R[1][2]  ;
    pstDmCfg->s16M33YUV2RGB0[2][0]          = HiHdrCfg->stY2R.as16M33Y2R[2][0]  ;
    pstDmCfg->s16M33YUV2RGB0[2][1]          = HiHdrCfg->stY2R.as16M33Y2R[2][1]  ;
    pstDmCfg->s16M33YUV2RGB0[2][2]          = HiHdrCfg->stY2R.as16M33Y2R[2][2]  ;

    pstDmCfg->s16M33YUV2RGB1[0][0]          = HiHdrCfg->stY2R.as16M33Y2R[0][0]  ; //BT709
    pstDmCfg->s16M33YUV2RGB1[0][1]          = HiHdrCfg->stY2R.as16M33Y2R[0][1]  ;
    pstDmCfg->s16M33YUV2RGB1[0][2]          = HiHdrCfg->stY2R.as16M33Y2R[0][2]  ;
    pstDmCfg->s16M33YUV2RGB1[1][0]          = HiHdrCfg->stY2R.as16M33Y2R[1][0]  ;
    pstDmCfg->s16M33YUV2RGB1[1][1]          = HiHdrCfg->stY2R.as16M33Y2R[1][1]  ;
    pstDmCfg->s16M33YUV2RGB1[1][2]          = HiHdrCfg->stY2R.as16M33Y2R[1][2]  ;
    pstDmCfg->s16M33YUV2RGB1[2][0]          = HiHdrCfg->stY2R.as16M33Y2R[2][0]  ;
    pstDmCfg->s16M33YUV2RGB1[2][1]          = HiHdrCfg->stY2R.as16M33Y2R[2][1]  ;
    pstDmCfg->s16M33YUV2RGB1[2][2]          = HiHdrCfg->stY2R.as16M33Y2R[2][2]  ;
    pstDmCfg->u16ScaleYUV2RGB               = HiHdrCfg->stY2R.u16ScaleY2R;


    pstDmCfg->s32InOffsetYUV2RGB0[0]        = HiHdrCfg->stY2R.as16DcInY2R[0];
    pstDmCfg->s32InOffsetYUV2RGB0[1]        = HiHdrCfg->stY2R.as16DcInY2R[1];
    pstDmCfg->s32InOffsetYUV2RGB0[2]        = HiHdrCfg->stY2R.as16DcInY2R[2];

    pstDmCfg->s32InOffsetYUV2RGB1[0]        = HiHdrCfg->stY2R.as16DcInY2R[0];
    pstDmCfg->s32InOffsetYUV2RGB1[1]        = HiHdrCfg->stY2R.as16DcInY2R[1];
    pstDmCfg->s32InOffsetYUV2RGB1[2]        = HiHdrCfg->stY2R.as16DcInY2R[2];

    pstDmCfg->s32OutOffsetYUV2RGB0[0]       = HiHdrCfg->stY2R.as16DcOutY2R[0];
    pstDmCfg->s32OutOffsetYUV2RGB0[1]       = HiHdrCfg->stY2R.as16DcOutY2R[1];
    pstDmCfg->s32OutOffsetYUV2RGB0[2]       = HiHdrCfg->stY2R.as16DcOutY2R[2];

    pstDmCfg->s32OutOffsetYUV2RGB1[0]       = HiHdrCfg->stY2R.as16DcOutY2R[0];
    pstDmCfg->s32OutOffsetYUV2RGB1[1]       = HiHdrCfg->stY2R.as16DcOutY2R[1];
    pstDmCfg->s32OutOffsetYUV2RGB1[2]       = HiHdrCfg->stY2R.as16DcOutY2R[2];

    pstDmCfg->u16ClipMinYUV2RGB             = HiHdrCfg->stY2R.u16ClipMinY2R;
    pstDmCfg->u16ClipMaxYUV2RGB             = HiHdrCfg->stY2R.u16ClipMaxY2R;



    /********** DeGamma ***********/

    pstDmCfg->DePQPara.gmm_x1_step          = HiHdrCfg->stDeGmm.au32Step[0];
    pstDmCfg->DePQPara.gmm_x2_step          = HiHdrCfg->stDeGmm.au32Step[1];
    pstDmCfg->DePQPara.gmm_x3_step          = HiHdrCfg->stDeGmm.au32Step[2];
    pstDmCfg->DePQPara.gmm_x4_step          = HiHdrCfg->stDeGmm.au32Step[3];
    pstDmCfg->DePQPara.gmm_x1_pos           = HiHdrCfg->stDeGmm.au32Pos[0]    ;
    pstDmCfg->DePQPara.gmm_x2_pos           = HiHdrCfg->stDeGmm.au32Pos[1]    ;
    pstDmCfg->DePQPara.gmm_x3_pos           = HiHdrCfg->stDeGmm.au32Pos[2]    ;
    pstDmCfg->DePQPara.gmm_x4_pos           = HiHdrCfg->stDeGmm.au32Pos[3]    ;
    pstDmCfg->DePQPara.gmm_x1_num           = HiHdrCfg->stDeGmm.au32Num[0];
    pstDmCfg->DePQPara.gmm_x2_num           = HiHdrCfg->stDeGmm.au32Num[1];
    pstDmCfg->DePQPara.gmm_x3_num           = HiHdrCfg->stDeGmm.au32Num[2];
    pstDmCfg->DePQPara.gmm_x4_num           = HiHdrCfg->stDeGmm.au32Num[3];


    //HiHdrCfg->stDeGmm.u32LUT;

    /********** ToneMapping **********/
    pstDmCfg->u16M3LumaCal[0]               = HiHdrCfg->stTMAP.au16M3LumaCal[0];
    pstDmCfg->u16M3LumaCal[1]               = HiHdrCfg->stTMAP.au16M3LumaCal[1];
    pstDmCfg->u16M3LumaCal[2]               = HiHdrCfg->stTMAP.au16M3LumaCal[2];
    pstDmCfg->u16ScaleLumaCal               = HiHdrCfg->stTMAP.u16ScaleLumaCal;
    pstDmCfg->u16ScaleCoefTM                = HiHdrCfg->stTMAP.u16ScaleCoefTM;
    pstDmCfg->u32ClipMinTM                  = HiHdrCfg->stTMAP.u32ClipMinTM;
    pstDmCfg->u32ClipMaxTM                  = HiHdrCfg->stTMAP.u32ClipMaxTM;
    pstDmCfg->s32TMOff0                     = HiHdrCfg->stTMAP.as32TMOff[0];
    pstDmCfg->s32TMOff1                     = HiHdrCfg->stTMAP.as32TMOff[1];
    pstDmCfg->s32TMOff2                     = HiHdrCfg->stTMAP.as32TMOff[2];


    //HiHdrCfg->stTMAP.u32LUTTM;

    pstDmCfg->TMPara.gmm_x1_step            = HiHdrCfg->stTMAP.au32StepTM[0];
    pstDmCfg->TMPara.gmm_x2_step            = HiHdrCfg->stTMAP.au32StepTM[1];
    pstDmCfg->TMPara.gmm_x3_step            = HiHdrCfg->stTMAP.au32StepTM[2];
    pstDmCfg->TMPara.gmm_x4_step            = HiHdrCfg->stTMAP.au32StepTM[3];
    pstDmCfg->TMPara.gmm_x5_step            = HiHdrCfg->stTMAP.au32StepTM[4];
    pstDmCfg->TMPara.gmm_x6_step            = HiHdrCfg->stTMAP.au32StepTM[5];
    pstDmCfg->TMPara.gmm_x7_step            = HiHdrCfg->stTMAP.au32StepTM[6];
    pstDmCfg->TMPara.gmm_x8_step            = HiHdrCfg->stTMAP.au32StepTM[7];
    pstDmCfg->TMPara.gmm_x1_pos             = HiHdrCfg->stTMAP.au32PosTM[0];
    pstDmCfg->TMPara.gmm_x2_pos             = HiHdrCfg->stTMAP.au32PosTM[1];
    pstDmCfg->TMPara.gmm_x3_pos             = HiHdrCfg->stTMAP.au32PosTM[2];
    pstDmCfg->TMPara.gmm_x4_pos             = HiHdrCfg->stTMAP.au32PosTM[3];
    pstDmCfg->TMPara.gmm_x5_pos             = HiHdrCfg->stTMAP.au32PosTM[4];
    pstDmCfg->TMPara.gmm_x6_pos             = HiHdrCfg->stTMAP.au32PosTM[5];
    pstDmCfg->TMPara.gmm_x7_pos             = HiHdrCfg->stTMAP.au32PosTM[6];
    pstDmCfg->TMPara.gmm_x8_pos             = HiHdrCfg->stTMAP.au32PosTM[7];
    pstDmCfg->TMPara.gmm_x1_num             = HiHdrCfg->stTMAP.au32NumTM[0];
    pstDmCfg->TMPara.gmm_x2_num             = HiHdrCfg->stTMAP.au32NumTM[1];
    pstDmCfg->TMPara.gmm_x3_num             = HiHdrCfg->stTMAP.au32NumTM[2];
    pstDmCfg->TMPara.gmm_x4_num             = HiHdrCfg->stTMAP.au32NumTM[3];
    pstDmCfg->TMPara.gmm_x5_num             = HiHdrCfg->stTMAP.au32NumTM[4];
    pstDmCfg->TMPara.gmm_x6_num             = HiHdrCfg->stTMAP.au32NumTM[5];
    pstDmCfg->TMPara.gmm_x7_num             = HiHdrCfg->stTMAP.au32NumTM[6];
    pstDmCfg->TMPara.gmm_x8_num             = HiHdrCfg->stTMAP.au32NumTM[7];




    /************ GamutMapping ***********/

    pstDmCfg->s16M33Src2Disp[0][0]          = HiHdrCfg->stGMAP.as16M33GMAP[0][0];
    pstDmCfg->s16M33Src2Disp[0][1]          = HiHdrCfg->stGMAP.as16M33GMAP[0][1];
    pstDmCfg->s16M33Src2Disp[0][2]          = HiHdrCfg->stGMAP.as16M33GMAP[0][2];
    pstDmCfg->s16M33Src2Disp[1][0]          = HiHdrCfg->stGMAP.as16M33GMAP[1][0];
    pstDmCfg->s16M33Src2Disp[1][1]          = HiHdrCfg->stGMAP.as16M33GMAP[1][1];
    pstDmCfg->s16M33Src2Disp[1][2]          = HiHdrCfg->stGMAP.as16M33GMAP[1][2];
    pstDmCfg->s16M33Src2Disp[2][0]          = HiHdrCfg->stGMAP.as16M33GMAP[2][0];
    pstDmCfg->s16M33Src2Disp[2][1]          = HiHdrCfg->stGMAP.as16M33GMAP[2][1];
    pstDmCfg->s16M33Src2Disp[2][2]          = HiHdrCfg->stGMAP.as16M33GMAP[2][2];
    pstDmCfg->u16ScaleSrc2Disp              = HiHdrCfg->stGMAP.u16ScaleGMAP;
    pstDmCfg->u32ClipMinCSC                 = HiHdrCfg->stGMAP.u32ClipMinGMAP;
    pstDmCfg->u32ClipMaxCSC                 = HiHdrCfg->stGMAP.u32ClipMaxGMAP;




    /************* Gamma ***********************/
    //HiHdrCfg->stGmm.u32LUT;

    pstDmCfg->GammaPara.gmm_x1_step         = HiHdrCfg->stGmm.au32Step[0];
    pstDmCfg->GammaPara.gmm_x2_step         = HiHdrCfg->stGmm.au32Step[1];
    pstDmCfg->GammaPara.gmm_x3_step         = HiHdrCfg->stGmm.au32Step[2];
    pstDmCfg->GammaPara.gmm_x4_step         = HiHdrCfg->stGmm.au32Step[3];
    pstDmCfg->GammaPara.gmm_x5_step         = HiHdrCfg->stGmm.au32Step[4];
    pstDmCfg->GammaPara.gmm_x6_step         = HiHdrCfg->stGmm.au32Step[5];
    pstDmCfg->GammaPara.gmm_x7_step         = HiHdrCfg->stGmm.au32Step[6];
    pstDmCfg->GammaPara.gmm_x8_step         = HiHdrCfg->stGmm.au32Step[7];
    pstDmCfg->GammaPara.gmm_x1_pos          = HiHdrCfg->stGmm.au32Pos[0];
    pstDmCfg->GammaPara.gmm_x2_pos          = HiHdrCfg->stGmm.au32Pos[1];
    pstDmCfg->GammaPara.gmm_x3_pos          = HiHdrCfg->stGmm.au32Pos[2];
    pstDmCfg->GammaPara.gmm_x4_pos          = HiHdrCfg->stGmm.au32Pos[3];
    pstDmCfg->GammaPara.gmm_x5_pos          = HiHdrCfg->stGmm.au32Pos[4];
    pstDmCfg->GammaPara.gmm_x6_pos          = HiHdrCfg->stGmm.au32Pos[5];
    pstDmCfg->GammaPara.gmm_x7_pos          = HiHdrCfg->stGmm.au32Pos[6];
    pstDmCfg->GammaPara.gmm_x8_pos          = HiHdrCfg->stGmm.au32Pos[7];
    pstDmCfg->GammaPara.gmm_x1_num          = HiHdrCfg->stGmm.au32Num[0];
    pstDmCfg->GammaPara.gmm_x2_num          = HiHdrCfg->stGmm.au32Num[1];
    pstDmCfg->GammaPara.gmm_x3_num          = HiHdrCfg->stGmm.au32Num[2];
    pstDmCfg->GammaPara.gmm_x4_num          = HiHdrCfg->stGmm.au32Num[3];
    pstDmCfg->GammaPara.gmm_x5_num          = HiHdrCfg->stGmm.au32Num[4];
    pstDmCfg->GammaPara.gmm_x6_num          = HiHdrCfg->stGmm.au32Num[5];
    pstDmCfg->GammaPara.gmm_x7_num          = HiHdrCfg->stGmm.au32Num[6];
    pstDmCfg->GammaPara.gmm_x8_num          = HiHdrCfg->stGmm.au32Num[7];



    /************** RGB2YUV ********************/

    pstDmCfg->s16M33RGB2YUV[0][0]           = HiHdrCfg->stR2Y.as16M33R2Y[0][0];
    pstDmCfg->s16M33RGB2YUV[0][1]           = HiHdrCfg->stR2Y.as16M33R2Y[0][1];
    pstDmCfg->s16M33RGB2YUV[0][2]           = HiHdrCfg->stR2Y.as16M33R2Y[0][2];
    pstDmCfg->s16M33RGB2YUV[1][0]           = HiHdrCfg->stR2Y.as16M33R2Y[1][0];
    pstDmCfg->s16M33RGB2YUV[1][1]           = HiHdrCfg->stR2Y.as16M33R2Y[1][1];
    pstDmCfg->s16M33RGB2YUV[1][2]           = HiHdrCfg->stR2Y.as16M33R2Y[1][2];
    pstDmCfg->s16M33RGB2YUV[2][0]           = HiHdrCfg->stR2Y.as16M33R2Y[2][0];
    pstDmCfg->s16M33RGB2YUV[2][1]           = HiHdrCfg->stR2Y.as16M33R2Y[2][1];
    pstDmCfg->s16M33RGB2YUV[2][2]           = HiHdrCfg->stR2Y.as16M33R2Y[2][2];
    pstDmCfg->u16ScaleRGB2YUV               = HiHdrCfg->stR2Y.u16ScaleR2Y;
    pstDmCfg->s16InOffsetRGB2YUV[0]         = HiHdrCfg->stR2Y.as16DcInR2Y[0];
    pstDmCfg->s16InOffsetRGB2YUV[1]         = HiHdrCfg->stR2Y.as16DcInR2Y[1];
    pstDmCfg->s16InOffsetRGB2YUV[2]         = HiHdrCfg->stR2Y.as16DcInR2Y[2];
    pstDmCfg->s16OutOffsetRGB2YUV[0]        = HiHdrCfg->stR2Y.as16DcOutR2Y[0];
    pstDmCfg->s16OutOffsetRGB2YUV[1]        = HiHdrCfg->stR2Y.as16DcOutR2Y[1];
    pstDmCfg->s16OutOffsetRGB2YUV[2]        = HiHdrCfg->stR2Y.as16DcOutR2Y[2];
    pstDmCfg->u16ClipMinRGB2YUV             = HiHdrCfg->stR2Y.u16ClipMinR2Y_Y;
    pstDmCfg->u16ClipMaxRGB2YUV             = HiHdrCfg->stR2Y.u16ClipMaxR2Y_Y;

    return;

}
HI_S32 VDP_DRV_GetHiHdrCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode, DmCfg_t  *pstDmCfg)
{

    //VDP_CLR_SPACE_E   enOutClr    = pstInfoOut->stXdpDispCfg.enOutClrSpace;
    if (HI_NULL == pstPqHdrCfg || u32LayerId == VDP_LAYER_VID3 )
    {
        return HI_FAILURE;
    }

#if CBB_CFG_FROM_PQ
    VDP_DRV_SetHiHdrAjust(pstPqHdrCfg, pstDmCfg);
#endif

    if (enSceneMode == HIHDR_HDR10_IN_SDR_OUT) //98mv200t test ok!
    {
        //typ mode
        VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217   ;
        pstDmCfg->u16M3LumaCal[2]                = 1943    ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 7       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 27209   ; //BT2020 to BT709
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;//0xFFFF0  1048575 ;//65535   ; //

        //YUV2RGB
        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;

        //RGB2YUV
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1315   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -4425   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 5740    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 5740    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -5214   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -527    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif
        //DITHER
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_HLG_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 0 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        pstDmCfg->vdm_v1_csc_en                  = 0 ;
        pstDmCfg->vdm_v0_gamma_en                = 1 ;
        pstDmCfg->vdm_v1_gamma_en                = 0 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217   ;
        pstDmCfg->u16M3LumaCal[2]                = 1943    ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 10      ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 349     ;
        pstDmCfg->s32TMOff1                      = 349     ;
        pstDmCfg->s32TMOff2                      = 349     ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 16384   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = 0       ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 0       ;
        pstDmCfg->s16M33Src2Disp[1][0]           = 0       ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 16384   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][0]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 16384   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 3685    ; //BT2020
        pstDmCfg->s16M33RGB2YUV[0][1]            = 9512    ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 832     ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -2004   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5171   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6598   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -577    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;

#endif
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_SDR_IN_HDR10_OUT) //not use
    {
        VDP_PRINT("VdmSceneMode == VDM_SDR_IN_HDR10_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217    ;
        pstDmCfg->u16M3LumaCal[2]                = 1943     ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;

        pstDmCfg->u16ScaleCoefTM                 = 15       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;


        pstDmCfg->DePQPara.gmm_x1_step           = 3       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 6       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 208     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 640     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 896     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 26      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 27      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 8      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 2       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6      ;
        pstDmCfg->TMPara.gmm_x3_step             = 8      ;
        pstDmCfg->TMPara.gmm_x4_step             = 9      ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;



        pstDmCfg->TMPara.gmm_x1_pos              = 64    ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512   ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024   ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072   ;

        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680   ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575   ;


        pstDmCfg->TMPara.gmm_x1_num              = 4      ;
        pstDmCfg->TMPara.gmm_x2_num              = 11       ;
        pstDmCfg->TMPara.gmm_x3_num              = 13       ;
        pstDmCfg->TMPara.gmm_x4_num              = 17       ;

        pstDmCfg->TMPara.gmm_x5_num              = 22       ;
        pstDmCfg->TMPara.gmm_x6_num              = 36       ;
        pstDmCfg->TMPara.gmm_x7_num              = 52       ;
        pstDmCfg->TMPara.gmm_x8_num              = 63       ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;

        pstDmCfg->GammaPara.gmm_x1_pos           = 64     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575 ;


        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 10279   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = 5396   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 710   ;

        pstDmCfg->s16M33Src2Disp[1][0]           = 1134   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 15064   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 187    ;

        pstDmCfg->s16M33Src2Disp[2][0]           = 268    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 1442   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 14673   ;


        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;


        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;


        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;

        pstDmCfg->s16M33RGB2YUV[0][0]            = 3685    ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = 9512   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 832    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -2605   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -6722   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 9328    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 9328    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -8577   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -750    ;

        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif

        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_SDR_IN_HLG_OUT) //not use
    {
        VDP_PRINT("VdmSceneMode == VDM_SDR_IN_BBC_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1 ;
        pstDmCfg->vdm_v1_csc_en                  = 0 ;
        pstDmCfg->vdm_v0_gamma_en                = 1 ;
        pstDmCfg->vdm_v1_gamma_en                = 0 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 1076    ;
        pstDmCfg->u16M3LumaCal[1]                = 2777    ;
        pstDmCfg->u16M3LumaCal[2]                = 243     ;
        pstDmCfg->u16ScaleLumaCal                = 12      ;
        pstDmCfg->u16ScaleCoefTM                 = 8       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 9       ;
        pstDmCfg->TMPara.gmm_x2_step             = 10      ;
        pstDmCfg->TMPara.gmm_x3_step             = 12      ;
        pstDmCfg->TMPara.gmm_x4_step             = 13      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x2_pos              = 16384   ;
        pstDmCfg->TMPara.gmm_x3_pos              = 24576   ;
        pstDmCfg->TMPara.gmm_x4_pos              = 65535   ;
        pstDmCfg->TMPara.gmm_x1_num              = 16      ;
        pstDmCfg->TMPara.gmm_x2_num              = 8       ;
        pstDmCfg->TMPara.gmm_x3_num              = 2       ;
        pstDmCfg->TMPara.gmm_x4_num              = 5       ;

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 27209   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984    ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif

        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_AVS_IN_SDR_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ; // 0 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1 ;////use Y2R BT2020 0 ; //use Y2R BT709
        pstDmCfg->vdm_v1_csc_en                  = 0 ;//                            1 ;
        pstDmCfg->vdm_v0_gamma_en                = 1 ;//                            0 ;
        pstDmCfg->vdm_v1_gamma_en                = 0 ;//                            1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217    ;
        pstDmCfg->u16M3LumaCal[2]                = 1943     ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 7       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 27209   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1315   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -4425   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 5740    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 5740    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -5214   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -527    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif

        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_AVS_IN_HDR10_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 0 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        pstDmCfg->vdm_v1_csc_en                  = 0 ;
        pstDmCfg->vdm_v0_gamma_en                = 1 ;
        pstDmCfg->vdm_v1_gamma_en                = 0 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217   ;
        pstDmCfg->u16M3LumaCal[2]                = 1943    ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 8       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 16384   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = 0       ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 0       ;
        pstDmCfg->s16M33Src2Disp[1][0]           = 0       ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 16384   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][0]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 0       ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 16384   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 3685    ; //BT2020
        pstDmCfg->s16M33RGB2YUV[0][1]            = 9512    ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 832     ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -2004   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5171   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6598   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -577    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;

#endif
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HLG_IN_SDR_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ; // 0 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1 ;////use Y2R BT2020 0 ; //use Y2R BT709
        pstDmCfg->vdm_v1_csc_en                  = 0 ;//                            1 ;
        pstDmCfg->vdm_v0_gamma_en                = 1 ;//                            0 ;
        pstDmCfg->vdm_v1_gamma_en                = 0 ;//                            1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217    ;
        pstDmCfg->u16M3LumaCal[2]                = 1943     ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 15      ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 349     ;
        pstDmCfg->s32TMOff1                      = 349     ;
        pstDmCfg->s32TMOff2                      = 349     ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 27209   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif

        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HLG_IN_HDR10_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 0;// 1 ;
        pstDmCfg->vdm_tmap_en                    = 1 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        pstDmCfg->vdm_v0_csc_en                  = 1;//use BT2020     0 ; //use BT709
        pstDmCfg->vdm_v1_csc_en                  = 0;//                      1 ;
        pstDmCfg->vdm_v0_gamma_en                = 1;//                      0 ;
        pstDmCfg->vdm_v1_gamma_en                = 0;//                      1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217   ;
        pstDmCfg->u16M3LumaCal[2]                = 1943    ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 15      ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4       ;
        pstDmCfg->TMPara.gmm_x2_step             = 6       ;
        pstDmCfg->TMPara.gmm_x3_step             = 8       ;
        pstDmCfg->TMPara.gmm_x4_step             = 9       ;
        pstDmCfg->TMPara.gmm_x5_step             = 10      ;
        pstDmCfg->TMPara.gmm_x6_step             = 12      ;
        pstDmCfg->TMPara.gmm_x7_step             = 14      ;
        pstDmCfg->TMPara.gmm_x8_step             = 16      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64      ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512     ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024    ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072    ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536   ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680  ;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575 ;
        pstDmCfg->TMPara.gmm_x1_num              = 4       ;
        pstDmCfg->TMPara.gmm_x2_num              = 11      ;
        pstDmCfg->TMPara.gmm_x3_num              = 13      ;
        pstDmCfg->TMPara.gmm_x4_num              = 17      ;
        pstDmCfg->TMPara.gmm_x5_num              = 22      ;
        pstDmCfg->TMPara.gmm_x6_num              = 36      ;
        pstDmCfg->TMPara.gmm_x7_num              = 52      ;
        pstDmCfg->TMPara.gmm_x8_num              = 63      ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 16384 ; //BT2020 to BT2020
        pstDmCfg->s16M33Src2Disp[0][1]           = 0     ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 0     ;
        pstDmCfg->s16M33Src2Disp[1][0]           = 0     ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 16384 ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 0     ;
        pstDmCfg->s16M33Src2Disp[2][0]           = 0     ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 0     ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 16384 ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        //YUV2RGB
        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;

        //RGB2YUV
        pstDmCfg->s16M33RGB2YUV[0][0]            = 3685   ; //BT2020
        pstDmCfg->s16M33RGB2YUV[0][1]            = 9512   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 832    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -2004  ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5171  ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175   ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175   ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6598  ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -577   ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif
        //DITHER
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_BT2020_IN_709_OUT) //98mv200t test ok!
    {
        VDP_PRINT("VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
        //typ mode


        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;


        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        // enable signal
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 0 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;

        //------------------//
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 0 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
        //-------------------------------//

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 8608    ;
        pstDmCfg->u16M3LumaCal[1]                = 22217   ;
        pstDmCfg->u16M3LumaCal[2]                = 1943    ;
        pstDmCfg->u16ScaleLumaCal                = 15      ;
        pstDmCfg->u16ScaleCoefTM                 = 8       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 5       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 672     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 832     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 992     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;
        pstDmCfg->DePQPara.gmm_x1_num            = 42      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 10      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 1       ;

        pstDmCfg->TMPara.gmm_x1_step             = 4     ;
        pstDmCfg->TMPara.gmm_x2_step             = 6     ;
        pstDmCfg->TMPara.gmm_x3_step             = 8     ;
        pstDmCfg->TMPara.gmm_x4_step             = 9     ;
        pstDmCfg->TMPara.gmm_x5_step             = 10    ;
        pstDmCfg->TMPara.gmm_x6_step             = 12    ;
        pstDmCfg->TMPara.gmm_x7_step             = 14    ;
        pstDmCfg->TMPara.gmm_x8_step             = 16    ;
        pstDmCfg->TMPara.gmm_x1_pos              = 64    ;
        pstDmCfg->TMPara.gmm_x2_pos              = 512   ;
        pstDmCfg->TMPara.gmm_x3_pos              = 1024  ;
        pstDmCfg->TMPara.gmm_x4_pos              = 3072  ;
        pstDmCfg->TMPara.gmm_x5_pos              = 8192  ;
        pstDmCfg->TMPara.gmm_x6_pos              = 65536 ;
        pstDmCfg->TMPara.gmm_x7_pos              = 327680;
        pstDmCfg->TMPara.gmm_x8_pos              = 1048575;
        pstDmCfg->TMPara.gmm_x1_num              = 4     ;
        pstDmCfg->TMPara.gmm_x2_num              = 11    ;
        pstDmCfg->TMPara.gmm_x3_num              = 13    ;
        pstDmCfg->TMPara.gmm_x4_num              = 17    ;
        pstDmCfg->TMPara.gmm_x5_num              = 22    ;
        pstDmCfg->TMPara.gmm_x6_num              = 36    ;
        pstDmCfg->TMPara.gmm_x7_num              = 52    ;
        pstDmCfg->TMPara.gmm_x8_num              = 63    ;

        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10    ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12    ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 64    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512   ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024  ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072  ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192  ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536 ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575;
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;

        pstDmCfg->s16M33Src2Disp[0][0]           = 27209   ; //BT2020 to BT709
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;//0xFFFF0  1048575 ;

        //YUV2RGB
        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;

        //RGB2YUV
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif
        //DITHER
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_709_IN_BT2020_OUT) //not use
    {
        VDP_PRINT("VdmSceneMode == VDM_709_IN_BT2020_OUT\n");
        //typ mode

        // enable signal

        // ctrl signal
        pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
        pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
        pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

        pstDmCfg->vdm_en                         = 1 ;
        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstDmCfg->vdm_v0_gamma_en                = 1 ;
            pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
        }
        else
        {
            pstDmCfg->vdm_v1_gamma_en                = 1 ;
            pstDmCfg->vdm_v1_csc_en                  = 1 ; //use BT2020
        }
#if !CBB_CFG_FROM_PQ
        pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
        pstDmCfg->vdm_en                         = 1 ;
        pstDmCfg->vdm_degmm_en                   = 1 ;
        pstDmCfg->vdm_csc_en                     = 1 ;
        pstDmCfg->vdm_tmap_en                    = 0 ;
        pstDmCfg->vdm_gmm_en                     = 1 ;
        pstDmCfg->vdm_dither_en                  = 1 ;
        pstDmCfg->vdm_rgb2yuv_en                 = 1 ;

        // cfg
        pstDmCfg->u16M3LumaCal[0]                = 1076    ;
        pstDmCfg->u16M3LumaCal[1]                = 2777    ;
        pstDmCfg->u16M3LumaCal[2]                = 243     ;
        pstDmCfg->u16ScaleLumaCal                = 12      ;
        pstDmCfg->u16ScaleCoefTM                 = 8       ;
        pstDmCfg->u32ClipMinTM                   = 0       ;
        pstDmCfg->u32ClipMaxTM                   = (1 << 20) - 1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
        pstDmCfg->DePQPara.gmm_x2_step           = 4       ;
        pstDmCfg->DePQPara.gmm_x3_step           = 2       ;
        pstDmCfg->DePQPara.gmm_x4_step           = 0       ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 512     ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 928     ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 1020     ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023    ;


        pstDmCfg->DePQPara.gmm_x1_num            = 8      ;
        pstDmCfg->DePQPara.gmm_x2_num            = 26      ;
        pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
        pstDmCfg->DePQPara.gmm_x4_num            = 4       ;

        pstDmCfg->TMPara.gmm_x1_step             = 9       ;
        pstDmCfg->TMPara.gmm_x2_step             = 10      ;
        pstDmCfg->TMPara.gmm_x3_step             = 12      ;
        pstDmCfg->TMPara.gmm_x4_step             = 13      ;
        pstDmCfg->TMPara.gmm_x1_pos              = 8192    ;
        pstDmCfg->TMPara.gmm_x2_pos              = 16384   ;
        pstDmCfg->TMPara.gmm_x3_pos              = 24576   ;
        pstDmCfg->TMPara.gmm_x4_pos              = 65535   ;
        pstDmCfg->TMPara.gmm_x1_num              = 16      ;
        pstDmCfg->TMPara.gmm_x2_num              = 8       ;
        pstDmCfg->TMPara.gmm_x3_num              = 2       ;
        pstDmCfg->TMPara.gmm_x4_num              = 5       ;



        pstDmCfg->GammaPara.gmm_x1_step          = 4     ;
        pstDmCfg->GammaPara.gmm_x2_step          = 6     ;
        pstDmCfg->GammaPara.gmm_x3_step          = 8     ;
        pstDmCfg->GammaPara.gmm_x4_step          = 9     ;
        pstDmCfg->GammaPara.gmm_x5_step          = 10     ;
        pstDmCfg->GammaPara.gmm_x6_step          = 12     ;
        pstDmCfg->GammaPara.gmm_x7_step          = 14    ;
        pstDmCfg->GammaPara.gmm_x8_step          = 16    ;

        pstDmCfg->GammaPara.gmm_x1_pos           = 64     ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 512     ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 1024     ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 3072     ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 8192     ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 65536     ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 327680    ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 1048575    ;

        pstDmCfg->GammaPara.gmm_x1_num           = 4     ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ;


        pstDmCfg->s16M33Src2Disp[0][0]           = 10279   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = 5396   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 710   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = 1134   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 15064   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 187    ;
        pstDmCfg->s16M33Src2Disp[2][0]           = 268    ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 1442   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 14673   ;
        pstDmCfg->u16ScaleSrc2Disp               = 14      ;
        pstDmCfg->u32ClipMinCSC                  = 0       ;
        pstDmCfg->u32ClipMaxCSC                  = 1048575 ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;

        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;

        pstDmCfg->u16ScaleYUV2RGB                = 13      ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstDmCfg->u16ClipMinYUV2RGB              = 0       ;
        pstDmCfg->u16ClipMaxYUV2RGB              = 1023    ;



        pstDmCfg->s16M33RGB2YUV[0][0]            = 3685    ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = 9512   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 832    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -2004   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5171   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6598   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -577    ;
        pstDmCfg->u16ScaleRGB2YUV                = 14      ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstDmCfg->u16ClipMinRGB2YUV              = 0       ;
        pstDmCfg->u16ClipMaxRGB2YUV              = 1023    ;
#endif

        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2140000000 ;
    }

    return HI_SUCCESS;




    return HI_SUCCESS;

}

HI_BOOL  XDP_DRV_SetVDMBypassProcess(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode)
{
    if (enSceneMode == HIHDR_BYPASS_MODE)
    {
        if (VDP_LAYER_VID0 == u32LayerId)
        {

            VDP_VID_SetVdmVdmV0GammaEn(VDP_LAYER_VID0, pstPqHdrCfg->vdm_v0_gamma_en);
        }
        else if (VDP_LAYER_VID1 == u32LayerId)
        {

            VDP_VID_SetVdmVdmV1GammaEn(VDP_LAYER_VID0, pstPqHdrCfg->vdm_v1_gamma_en);
        }
        return HI_FALSE;

    }

    return HI_TRUE;

}

HI_S32 XDP_DRV_SetVDMCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode)
{
    if (enSceneMode != HIHDR_HDR10_IN_HDR10_OUT
        && enSceneMode != HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT
        && enSceneMode != HIHDR_BT2020_IN_2020_OUT
        && enSceneMode != HIHDR_BYPASS_MODE
       )
    {

        Vdp_Drv_SetVdmCoef_gmm      (enSceneMode, pstPqHdrCfg);
        Vdp_Drv_SetVdmCoef_Degmm    (enSceneMode, pstPqHdrCfg);
        Vdp_Drv_SetVdmCoef_Tmapping (enSceneMode, pstPqHdrCfg);

    }

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetHiHdrCfg(HI_U32 u32LayerId, DmCfg_t  *pstDmCfg)
{
    //filed declare
    HI_U32 vdm_tmap_in_bdp    =  0;
    HI_U32 vdm_csc_bind    =  0;
    HI_U32 vdm_gmm_en    =  0;
    HI_U32 vdm_tmap_en    =  0;
    HI_U32 vdm_degmm_en    =  0;
    HI_U32 vdm_en    =  0;
    HI_U16 vdm_luma_coef0_tmap    =  0;
    HI_U16 vdm_luma_coef1_tmap    =  0;
    HI_U16 vdm_luma_coef2_tmap    =  0;
    HI_U16 vdm_tmap_luma_scale    =  0;
    HI_U16 vdm_tmap_coef_scale    =  0;
    HI_U32 vdm_tmap_out_clip_min    =  0;
    HI_U32 vdm_tmap_out_clip_max    =  0;
    HI_S32 vdm_tmap_out_dc0    =  0;
    HI_S32 vdm_tmap_out_dc1    =  0;
    HI_S32 vdm_tmap_out_dc2    =  0;
    HI_U32 vdm_degamma_rd_en    =  0;
    HI_U32 vdm_degamma_para_data    =  0;
    HI_U32 v_degmm_x4_step    =  0;
    HI_U32 v_degmm_x3_step    =  0;
    HI_U32 v_degmm_x2_step    =  0;
    HI_U32 v_degmm_x1_step    =  0;
    HI_U32 v_degmm_x2_pos    =  0;
    HI_U32 v_degmm_x1_pos    =  0;
    HI_U32 v_degmm_x4_pos    =  0;
    HI_U32 v_degmm_x3_pos    =  0;
    HI_U32 v_degmm_x4_num    =  0;
    HI_U32 v_degmm_x3_num    =  0;
    HI_U32 v_degmm_x2_num    =  0;
    HI_U32 v_degmm_x1_num    =  0;
    HI_U32 vdm_tmap_rd_en    =  0;
    HI_U32 vdm_tmap_para_data    =  0;
    HI_U32 v_tmap_x4_step    =  0;
    HI_U32 v_tmap_x5_step    =  0;
    HI_U32 v_tmap_x6_step    =  0;
    HI_U32 v_tmap_x7_step    =  0;
    HI_U32 v_tmap_x8_step    =  0;
    HI_U32 v_tmap_x3_step    =  0;
    HI_U32 v_tmap_x2_step    =  0;
    HI_U32 v_tmap_x1_step    =  0;
    HI_U32 v_tmap_x1_pos    =  0;
    HI_U32 v_tmap_x2_pos    =  0;
    HI_U32 v_tmap_x4_num    =  0;
    HI_U32 v_tmap_x5_num    =  0;
    HI_U32 v_tmap_x6_num    =  0;
    HI_U32 v_tmap_x7_num    =  0;
    HI_U32 v_tmap_x8_num    =  0;
    HI_U32 v_tmap_x3_num    =  0;
    HI_U32 v_tmap_x2_num    =  0;
    HI_U32 v_tmap_x1_num    =  0;
    HI_U32 v_tmap_x3_pos    =  0;
    HI_U32 v_tmap_x4_pos    =  0;
    HI_U32 v_tmap_x5_pos    =  0;
    HI_U32 v_tmap_x6_pos    =  0;
    HI_U32 v_tmap_x7_pos    =  0;
    HI_U32 v_tmap_x8_pos    =  0;
    HI_U32 vdm_gamma_rd_en    =  0;
    HI_U32 vdm_gamma_para_data    =  0;
    HI_U32 v_gmm_x5_step    =  0;
    HI_U32 v_gmm_x6_step    =  0;
    HI_U32 v_gmm_x7_step    =  0;
    HI_U32 v_gmm_x8_step    =  0;
    HI_U32 v_gmm_x4_step    =  0;
    HI_U32 v_gmm_x3_step    =  0;
    HI_U32 v_gmm_x2_step    =  0;
    HI_U32 v_gmm_x1_step    =  0;
    HI_U32 v_gmm_x1_pos    =  0;
    HI_U32 v_gmm_x2_pos    =  0;
    HI_U32 v_gmm_x3_pos    =  0;
    HI_U32 v_gmm_x4_pos    =  0;
    HI_U32 v_gmm_x5_pos    =  0;
    HI_U32 v_gmm_x6_pos    =  0;
    HI_U32 v_gmm_x7_pos    =  0;
    HI_U32 v_gmm_x8_pos    =  0;
    HI_U32 v_gmm_x5_num    =  0;
    HI_U32 v_gmm_x6_num    =  0;
    HI_U32 v_gmm_x7_num    =  0;
    HI_U32 v_gmm_x8_num    =  0;
    HI_U32 v_gmm_x4_num    =  0;
    HI_U32 v_gmm_x3_num    =  0;
    HI_U32 v_gmm_x2_num    =  0;
    HI_U32 v_gmm_x1_num    =  0;
    HI_U32 vdm_csc_en    =  0;
    HI_S16 vdm_coef00_csc    =  0;
    HI_S16 vdm_coef01_csc    =  0;
    HI_S16 vdm_coef02_csc    =  0;
    HI_S16 vdm_coef10_csc    =  0;
    HI_S16 vdm_coef11_csc    =  0;
    HI_S16 vdm_coef12_csc    =  0;
    HI_S16 vdm_coef20_csc    =  0;
    HI_S16 vdm_coef21_csc    =  0;
    HI_S16 vdm_coef22_csc    =  0;
    HI_U16 vdm_csc_scale    =  0;
    HI_U32 vdm_csc_clip_min    =  0;
    HI_U32 vdm_csc_clip_max    =  0;
    HI_U32 vdm_v1_gamma_en    =  0;
    HI_U32 vdm_v0_gamma_en    =  0;
    HI_U32 vdm_v1_csc_en    =  0;
    HI_U32 vdm_v0_csc_en    =  0;
    HI_U32 vdm_yuv2rgb_en    =  0;
    HI_S16 vdm_00_yuv2rgb    =  0;
    HI_S16 vdm_01_yuv2rgb    =  0;
    HI_S16 vdm_02_yuv2rgb    =  0;
    HI_S16 vdm_03_yuv2rgb    =  0;
    HI_S16 vdm_04_yuv2rgb    =  0;
    HI_S16 vdm_05_yuv2rgb    =  0;
    HI_S16 vdm_06_yuv2rgb    =  0;
    HI_S16 vdm_07_yuv2rgb    =  0;
    HI_S16 vdm_08_yuv2rgb    =  0;
    HI_S16 vdm_10_yuv2rgb    =  0;
    HI_S16 vdm_11_yuv2rgb    =  0;
    HI_S16 vdm_12_yuv2rgb    =  0;
    HI_S16 vdm_13_yuv2rgb    =  0;
    HI_S16 vdm_14_yuv2rgb    =  0;
    HI_S16 vdm_15_yuv2rgb    =  0;
    HI_S16 vdm_16_yuv2rgb    =  0;
    HI_S16 vdm_17_yuv2rgb    =  0;
    HI_S16 vdm_18_yuv2rgb    =  0;
    HI_U16 vdm_yuv2rgbscale2p    =  0;
    HI_S32 vdm_yuv2rgb_00_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_01_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_02_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_00_out_dc    =  0;
    HI_S32 vdm_yuv2rgb_01_out_dc    =  0;
    HI_S32 vdm_yuv2rgb_02_out_dc    =  0;
    HI_S32 vdm_yuv2rgb_10_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_11_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_12_in_dc    =  0;
    HI_S32 vdm_yuv2rgb_10_out_dc    =  0;
    HI_S32 vdm_yuv2rgb_11_out_dc    =  0;
    HI_S32 vdm_yuv2rgb_12_out_dc    =  0;
    HI_U16 vdm_yuv2rgb_clip_min    =  0;
    HI_U16 vdm_yuv2rgb_clip_max    =  0;
    HI_U32 vdm_rgb2yuv_en    =  0;
    HI_S16 vdm_00_rgb2yuv    =  0;
    HI_S16 vdm_01_rgb2yuv    =  0;
    HI_S16 vdm_02_rgb2yuv    =  0;
    HI_S16 vdm_10_rgb2yuv    =  0;
    HI_S16 vdm_11_rgb2yuv    =  0;
    HI_S16 vdm_12_rgb2yuv    =  0;
    HI_S16 vdm_20_rgb2yuv    =  0;
    HI_S16 vdm_21_rgb2yuv    =  0;
    HI_S16 vdm_22_rgb2yuv    =  0;
    HI_U16 vdm_rgb2yuvscale2p    =  0;
    HI_S16 vdm_rgb2yuv_0_in_dc    =  0;
    HI_S16 vdm_rgb2yuv_1_in_dc    =  0;
    HI_S16 vdm_rgb2yuv_2_in_dc    =  0;
    HI_S16 vdm_rgb2yuv_0_out_dc    =  0;
    HI_S16 vdm_rgb2yuv_1_out_dc    =  0;
    HI_S16 vdm_rgb2yuv_2_out_dc    =  0;
    HI_U16 vdm_rgb2yuv_clip_min    =  0;
    HI_U16 vdm_rgb2yuv_clip_max    =  0;
    HI_U32 vdm_dither_round_unlim    =  0;
    HI_U32 vdm_dither_en    =  0;
    HI_U32 vdm_dither_round    =  0;
    HI_U32 vdm_dither_domain_mode    =  0;
    HI_U32 vdm_dither_tap_mode    =  0;
    HI_U32 vdm_dither_sed_y0    =  0;
    HI_U32 vdm_dither_sed_u0    =  0;
    HI_U32 vdm_dither_sed_v0    =  0;
    HI_U32 vdm_dither_sed_w0    =  0;
    HI_U32 vdm_dither_sed_y1    =  0;
    HI_U32 vdm_dither_sed_u1    =  0;
    HI_U32 vdm_dither_sed_v1    =  0;
    HI_U32 vdm_dither_sed_w1    =  0;
    HI_U32 vdm_dither_sed_y2    =  0;
    HI_U32 vdm_dither_sed_u2    =  0;
    HI_U32 vdm_dither_sed_v2    =  0;
    HI_U32 vdm_dither_sed_w2    =  0;
    HI_U32 vdm_dither_sed_y3    =  0;
    HI_U32 vdm_dither_sed_u3    =  0;
    HI_U32 vdm_dither_sed_v3    =  0;
    HI_U32 vdm_dither_sed_w3    =  0;
    HI_U32 vdm_dither_thr_max    =  0;
    HI_U32 vdm_dither_thr_min    =  0;


    vdm_tmap_in_bdp   = pstDmCfg->vdm_tmap_in_bdp ;
    vdm_csc_bind      = pstDmCfg->vdm_csc_bind    ;
    vdm_gmm_en        = pstDmCfg->vdm_gmm_en      ;
    vdm_tmap_en       = pstDmCfg->vdm_tmap_en     ;
    vdm_degmm_en      = pstDmCfg->vdm_degmm_en    ;
    vdm_en            = pstDmCfg->vdm_en          ;
    vdm_v1_gamma_en   = pstDmCfg->vdm_v1_gamma_en ;
    vdm_v0_gamma_en   = pstDmCfg->vdm_v0_gamma_en ;
    vdm_v1_csc_en     = pstDmCfg->vdm_v1_csc_en   ;
    vdm_v0_csc_en     = pstDmCfg->vdm_v0_csc_en   ;
    vdm_yuv2rgb_en    = pstDmCfg->vdm_yuv2rgb_en  ;
    vdm_rgb2yuv_en    = pstDmCfg->vdm_rgb2yuv_en  ;
    vdm_csc_en        = pstDmCfg->vdm_csc_en      ;
    vdm_dither_en     = pstDmCfg->vdm_dither_en   ;

    vdm_luma_coef0_tmap       = pstDmCfg->u16M3LumaCal[0] ;// ;
    vdm_luma_coef1_tmap       = pstDmCfg->u16M3LumaCal[1] ;// ;
    vdm_luma_coef2_tmap       = pstDmCfg->u16M3LumaCal[2] ;// ;
    vdm_tmap_luma_scale       = pstDmCfg->u16ScaleLumaCal ;// ;
    vdm_tmap_coef_scale       = pstDmCfg->u16ScaleCoefTM  ;// ;
    vdm_tmap_out_clip_min     = pstDmCfg->u32ClipMinTM    ;// ;
    vdm_tmap_out_clip_max     = pstDmCfg->u32ClipMaxTM    ;// ;
    vdm_tmap_out_dc0          = pstDmCfg->s32TMOff0       ;// ;
    vdm_tmap_out_dc1          = pstDmCfg->s32TMOff1       ;// ;
    vdm_tmap_out_dc2          = pstDmCfg->s32TMOff2       ;// ;

    v_degmm_x1_step   = pstDmCfg->DePQPara.gmm_x1_step   ;// ;
    v_degmm_x2_step   = pstDmCfg->DePQPara.gmm_x2_step   ;// ;
    v_degmm_x3_step   = pstDmCfg->DePQPara.gmm_x3_step   ;// ;
    v_degmm_x4_step   = pstDmCfg->DePQPara.gmm_x4_step   ;// ;
    v_degmm_x1_pos    = pstDmCfg->DePQPara.gmm_x1_pos    ;// ;
    v_degmm_x2_pos    = pstDmCfg->DePQPara.gmm_x2_pos    ;// ;
    v_degmm_x3_pos    = pstDmCfg->DePQPara.gmm_x3_pos    ;// ;
    v_degmm_x4_pos    = pstDmCfg->DePQPara.gmm_x4_pos    ;// ;
    v_degmm_x1_num    = pstDmCfg->DePQPara.gmm_x1_num    ;// ;
    v_degmm_x2_num    = pstDmCfg->DePQPara.gmm_x2_num    ;// ;
    v_degmm_x3_num    = pstDmCfg->DePQPara.gmm_x3_num    ;// ;
    v_degmm_x4_num    = pstDmCfg->DePQPara.gmm_x4_num    ;// ;

    v_tmap_x1_step     = pstDmCfg->TMPara.gmm_x1_step ;// ;
    v_tmap_x2_step     = pstDmCfg->TMPara.gmm_x2_step ;// ;
    v_tmap_x3_step     = pstDmCfg->TMPara.gmm_x3_step ;// ;
    v_tmap_x4_step     = pstDmCfg->TMPara.gmm_x4_step ;// ;
    v_tmap_x5_step     = pstDmCfg->TMPara.gmm_x5_step ;// ;
    v_tmap_x6_step     = pstDmCfg->TMPara.gmm_x6_step ;// ;
    v_tmap_x7_step     = pstDmCfg->TMPara.gmm_x7_step ;// ;
    v_tmap_x8_step     = pstDmCfg->TMPara.gmm_x8_step ;// ;
    v_tmap_x1_pos      = pstDmCfg->TMPara.gmm_x1_pos  ;// ;
    v_tmap_x2_pos      = pstDmCfg->TMPara.gmm_x2_pos  ;// ;
    v_tmap_x3_pos      = pstDmCfg->TMPara.gmm_x3_pos  ;// ;
    v_tmap_x4_pos      = pstDmCfg->TMPara.gmm_x4_pos  ;// ;
    v_tmap_x5_pos      = pstDmCfg->TMPara.gmm_x5_pos  ;// ;
    v_tmap_x6_pos      = pstDmCfg->TMPara.gmm_x6_pos  ;// ;
    v_tmap_x7_pos      = pstDmCfg->TMPara.gmm_x7_pos  ;// ;
    v_tmap_x8_pos      = pstDmCfg->TMPara.gmm_x8_pos  ;// ;
    v_tmap_x1_num      = pstDmCfg->TMPara.gmm_x1_num  ;// ;
    v_tmap_x2_num      = pstDmCfg->TMPara.gmm_x2_num  ;// ;
    v_tmap_x3_num      = pstDmCfg->TMPara.gmm_x3_num  ;// ;
    v_tmap_x4_num      = pstDmCfg->TMPara.gmm_x4_num  ;// ;
    v_tmap_x5_num      = pstDmCfg->TMPara.gmm_x5_num  ;// ;
    v_tmap_x6_num      = pstDmCfg->TMPara.gmm_x6_num  ;// ;
    v_tmap_x7_num      = pstDmCfg->TMPara.gmm_x7_num  ;// ;
    v_tmap_x8_num      = pstDmCfg->TMPara.gmm_x8_num  ;// ;

    v_gmm_x1_step     = pstDmCfg->GammaPara.gmm_x1_step ;// ;
    v_gmm_x2_step     = pstDmCfg->GammaPara.gmm_x2_step ;// ;
    v_gmm_x3_step     = pstDmCfg->GammaPara.gmm_x3_step ;// ;
    v_gmm_x4_step     = pstDmCfg->GammaPara.gmm_x4_step ;// ;
    v_gmm_x5_step     = pstDmCfg->GammaPara.gmm_x5_step ;// ;
    v_gmm_x6_step     = pstDmCfg->GammaPara.gmm_x6_step ;// ;
    v_gmm_x7_step     = pstDmCfg->GammaPara.gmm_x7_step ;// ;
    v_gmm_x8_step     = pstDmCfg->GammaPara.gmm_x8_step ;// ;
    v_gmm_x1_pos      = pstDmCfg->GammaPara.gmm_x1_pos  ;// ;
    v_gmm_x2_pos      = pstDmCfg->GammaPara.gmm_x2_pos  ;// ;
    v_gmm_x3_pos      = pstDmCfg->GammaPara.gmm_x3_pos  ;// ;
    v_gmm_x4_pos      = pstDmCfg->GammaPara.gmm_x4_pos  ;// ;
    v_gmm_x5_pos      = pstDmCfg->GammaPara.gmm_x5_pos  ;// ;
    v_gmm_x6_pos      = pstDmCfg->GammaPara.gmm_x6_pos  ;// ;
    v_gmm_x7_pos      = pstDmCfg->GammaPara.gmm_x7_pos  ;// ;
    v_gmm_x8_pos      = pstDmCfg->GammaPara.gmm_x8_pos  ;// ;
    v_gmm_x1_num      = pstDmCfg->GammaPara.gmm_x1_num  ;// ;
    v_gmm_x2_num      = pstDmCfg->GammaPara.gmm_x2_num  ;// ;
    v_gmm_x3_num      = pstDmCfg->GammaPara.gmm_x3_num  ;// ;
    v_gmm_x4_num      = pstDmCfg->GammaPara.gmm_x4_num  ;// ;
    v_gmm_x5_num      = pstDmCfg->GammaPara.gmm_x5_num  ;// ;
    v_gmm_x6_num      = pstDmCfg->GammaPara.gmm_x6_num  ;// ;
    v_gmm_x7_num      = pstDmCfg->GammaPara.gmm_x7_num  ;// ;
    v_gmm_x8_num      = pstDmCfg->GammaPara.gmm_x8_num  ;// ;

    vdm_coef00_csc       = pstDmCfg->s16M33Src2Disp[0][0] ;// ;
    vdm_coef01_csc       = pstDmCfg->s16M33Src2Disp[0][1] ;// ;
    vdm_coef02_csc       = pstDmCfg->s16M33Src2Disp[0][2] ;// ;
    vdm_coef10_csc       = pstDmCfg->s16M33Src2Disp[1][0] ;// ;
    vdm_coef11_csc       = pstDmCfg->s16M33Src2Disp[1][1] ;// ;
    vdm_coef12_csc       = pstDmCfg->s16M33Src2Disp[1][2] ;// ;
    vdm_coef20_csc       = pstDmCfg->s16M33Src2Disp[2][0] ;// ;
    vdm_coef21_csc       = pstDmCfg->s16M33Src2Disp[2][1] ;// ;
    vdm_coef22_csc       = pstDmCfg->s16M33Src2Disp[2][2] ;// ;
    vdm_csc_scale        = pstDmCfg->u16ScaleSrc2Disp     ;// ;
    vdm_csc_clip_min     = pstDmCfg->u32ClipMinCSC        ;// ;
    vdm_csc_clip_max     = pstDmCfg->u32ClipMaxCSC        ;// ;

    vdm_00_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[0][0] ;// ;
    vdm_01_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[0][1] ;// ;
    vdm_02_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[0][2] ;// ;
    vdm_03_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[1][0] ;// ;
    vdm_04_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[1][1] ;// ;
    vdm_05_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[1][2] ;// ;
    vdm_06_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[2][0] ;// ;
    vdm_07_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[2][1] ;// ;
    vdm_08_yuv2rgb     = pstDmCfg->s16M33YUV2RGB0[2][2] ;// ;
    vdm_10_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[0][0] ;// ;
    vdm_11_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[0][1] ;// ;
    vdm_12_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[0][2] ;// ;
    vdm_13_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[1][0] ;// ;
    vdm_14_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[1][1] ;// ;
    vdm_15_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[1][2] ;// ;
    vdm_16_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[2][0] ;// ;
    vdm_17_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[2][1] ;// ;
    vdm_18_yuv2rgb     = pstDmCfg->s16M33YUV2RGB1[2][2] ;// ;
    vdm_yuv2rgbscale2p     = pstDmCfg->u16ScaleYUV2RGB      ;// ;
    vdm_yuv2rgb_00_in_dc   = pstDmCfg->s32InOffsetYUV2RGB0[0]  ; // ;
    vdm_yuv2rgb_01_in_dc   = pstDmCfg->s32InOffsetYUV2RGB0[1]  ; // ;
    vdm_yuv2rgb_02_in_dc   = pstDmCfg->s32InOffsetYUV2RGB0[2]  ; // ;
    vdm_yuv2rgb_00_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB0[0] ; // ;
    vdm_yuv2rgb_01_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB0[1] ; // ;
    vdm_yuv2rgb_02_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB0[2] ; // ;

    vdm_yuv2rgb_10_in_dc   = pstDmCfg->s32InOffsetYUV2RGB1[0]  ; // ;
    vdm_yuv2rgb_11_in_dc   = pstDmCfg->s32InOffsetYUV2RGB1[1]  ; // ;
    vdm_yuv2rgb_12_in_dc   = pstDmCfg->s32InOffsetYUV2RGB1[2]  ; // ;
    vdm_yuv2rgb_10_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB1[0] ; // ;
    vdm_yuv2rgb_11_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB1[1] ; // ;
    vdm_yuv2rgb_12_out_dc  = pstDmCfg->s32OutOffsetYUV2RGB1[2] ; // ;
    vdm_yuv2rgb_clip_min   = pstDmCfg->u16ClipMinYUV2RGB       ; // ;
    vdm_yuv2rgb_clip_max   = pstDmCfg->u16ClipMaxYUV2RGB       ; // ;
    vdm_00_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][0]     ; // ;
    vdm_01_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][1]     ; // ;
    vdm_02_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[0][2]     ; // ;
    vdm_10_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][0]     ; // ;
    vdm_11_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][1]     ; // ;
    vdm_12_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[1][2]     ; // ;
    vdm_20_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][0]     ; // ;
    vdm_21_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][1]     ; // ;
    vdm_22_rgb2yuv         = pstDmCfg->s16M33RGB2YUV[2][2]     ; // ;
    //printk("id = %d : %d \n",u32LayerId,vdm_00_rgb2yuv);
    vdm_rgb2yuvscale2p     = pstDmCfg->u16ScaleRGB2YUV         ; // ;
    vdm_rgb2yuv_0_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[0]   ; // ;
    vdm_rgb2yuv_1_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[1]   ; // ;
    vdm_rgb2yuv_2_in_dc    = pstDmCfg->s16InOffsetRGB2YUV[2]   ; // ;
    vdm_rgb2yuv_0_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[0]  ; // ;
    vdm_rgb2yuv_1_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[1]  ; // ;
    vdm_rgb2yuv_2_out_dc   = pstDmCfg->s16OutOffsetRGB2YUV[2]  ; // ;
    vdm_rgb2yuv_clip_min   = pstDmCfg->u16ClipMinRGB2YUV       ; // ;
    vdm_rgb2yuv_clip_max   = pstDmCfg->u16ClipMaxRGB2YUV       ; // ;

    vdm_dither_round        = pstDmCfg->stDitherCfg.u32_dither_round       ;
    vdm_dither_domain_mode  = pstDmCfg->stDitherCfg.u32_dither_domain_mode ;
    vdm_dither_tap_mode     = pstDmCfg->stDitherCfg.u32_dither_tap_mode    ;
    vdm_dither_round_unlim  = pstDmCfg->stDitherCfg.u32_dither_round_unlim ;
    vdm_dither_sed_y0       = pstDmCfg->stDitherCfg.u32_dither_sed_y0      ;
    vdm_dither_sed_u0       = pstDmCfg->stDitherCfg.u32_dither_sed_u0      ;
    vdm_dither_sed_v0       = pstDmCfg->stDitherCfg.u32_dither_sed_v0      ;
    vdm_dither_sed_w0       = pstDmCfg->stDitherCfg.u32_dither_sed_w0      ;
    vdm_dither_sed_y1       = pstDmCfg->stDitherCfg.u32_dither_sed_y1      ;
    vdm_dither_sed_u1       = pstDmCfg->stDitherCfg.u32_dither_sed_u1      ;
    vdm_dither_sed_v1       = pstDmCfg->stDitherCfg.u32_dither_sed_v1      ;
    vdm_dither_sed_w1       = pstDmCfg->stDitherCfg.u32_dither_sed_w1      ;
    vdm_dither_thr_max      = pstDmCfg->stDitherCfg.u32_dither_thr_max     ;
    vdm_dither_thr_min      = pstDmCfg->stDitherCfg.u32_dither_thr_min     ;


    //drv transfer
    VDP_VID_SetVdmVdmTmapInBdp(VDP_LAYER_VID0, vdm_tmap_in_bdp);
    VDP_VID_SetVdmVdmCscBind(VDP_LAYER_VID0, vdm_csc_bind);
    VDP_VID_SetVdmVdmGmmEn(VDP_LAYER_VID0, vdm_gmm_en);
    VDP_VID_SetVdmVdmTmapEn(VDP_LAYER_VID0, vdm_tmap_en);
    VDP_VID_SetVdmVdmDegmmEn(VDP_LAYER_VID0, vdm_degmm_en);
    VDP_VID_SetVdmVdmEn(VDP_LAYER_VID0, vdm_en);
    VDP_VID_SetVdmVdmLumaCoef0Tmap(VDP_LAYER_VID0, vdm_luma_coef0_tmap);
    VDP_VID_SetVdmVdmLumaCoef1Tmap(VDP_LAYER_VID0, vdm_luma_coef1_tmap);
    VDP_VID_SetVdmVdmLumaCoef2Tmap(VDP_LAYER_VID0, vdm_luma_coef2_tmap);
    VDP_VID_SetVdmVdmTmapLumaScale(VDP_LAYER_VID0, vdm_tmap_luma_scale);
    VDP_VID_SetVdmVdmTmapCoefScale(VDP_LAYER_VID0, vdm_tmap_coef_scale);
    VDP_VID_SetVdmVdmTmapOutClipMin(VDP_LAYER_VID0, vdm_tmap_out_clip_min);
    VDP_VID_SetVdmVdmTmapOutClipMax(VDP_LAYER_VID0, vdm_tmap_out_clip_max);
    //VDP_VID_SetVdmVdmParaDegmmAddr(VDP_LAYER_VID0, vdm_para_degmm_addr);
    //VDP_VID_SetVdmVdmParaGmmAddr(VDP_LAYER_VID0, vdm_para_gmm_addr);
    //VDP_VID_SetVdmVdmParaTmapAddr(VDP_LAYER_VID0, vdm_para_tmap_addr);
    //VDP_VID_SetVdmVdmParaTmapUpd(VDP_LAYER_VID0, vdm_para_tmap_upd);
    //VDP_VID_SetVdmVdmParaGmmUpd(VDP_LAYER_VID0, vdm_para_gmm_upd);
    //VDP_VID_SetVdmVdmParaDegmmUpd(VDP_LAYER_VID0, vdm_para_degmm_upd);
    VDP_VID_SetVdmTmapOutDc0(vdm_tmap_out_dc0);
    VDP_VID_SetVdmTmapOutDc1(vdm_tmap_out_dc1);
    VDP_VID_SetVdmTmapOutDc2(vdm_tmap_out_dc2);
    VDP_VID_SetVdmVdmDegammaRdEn(VDP_LAYER_VID0, vdm_degamma_rd_en);
    VDP_VID_SetVdmVdmDegammaParaData(VDP_LAYER_VID0, vdm_degamma_para_data);
    VDP_VID_SetVdmVDegmmX4Step(VDP_LAYER_VID0, v_degmm_x4_step);
    VDP_VID_SetVdmVDegmmX3Step(VDP_LAYER_VID0, v_degmm_x3_step);
    VDP_VID_SetVdmVDegmmX2Step(VDP_LAYER_VID0, v_degmm_x2_step);
    VDP_VID_SetVdmVDegmmX1Step(VDP_LAYER_VID0, v_degmm_x1_step);
    VDP_VID_SetVdmVDegmmX2Pos(VDP_LAYER_VID0, v_degmm_x2_pos);
    VDP_VID_SetVdmVDegmmX1Pos(VDP_LAYER_VID0, v_degmm_x1_pos);
    VDP_VID_SetVdmVDegmmX4Pos(VDP_LAYER_VID0, v_degmm_x4_pos);
    VDP_VID_SetVdmVDegmmX3Pos(VDP_LAYER_VID0, v_degmm_x3_pos);
    VDP_VID_SetVdmVDegmmX4Num(VDP_LAYER_VID0, v_degmm_x4_num);
    VDP_VID_SetVdmVDegmmX3Num(VDP_LAYER_VID0, v_degmm_x3_num);
    VDP_VID_SetVdmVDegmmX2Num(VDP_LAYER_VID0, v_degmm_x2_num);
    VDP_VID_SetVdmVDegmmX1Num(VDP_LAYER_VID0, v_degmm_x1_num);
    VDP_VID_SetVdmVdmTmapRdEn(VDP_LAYER_VID0, vdm_tmap_rd_en);
    VDP_VID_SetVdmVdmTmapParaData(VDP_LAYER_VID0, vdm_tmap_para_data);
    VDP_VID_SetVdmVTmapX4Step(VDP_LAYER_VID0, v_tmap_x4_step);
    VDP_VID_SetVTmapX5Step(v_tmap_x5_step);
    VDP_VID_SetVTmapX6Step(v_tmap_x6_step);
    VDP_VID_SetVTmapX7Step(v_tmap_x7_step);
    VDP_VID_SetVTmapX8Step(v_tmap_x8_step);
    VDP_VID_SetVdmVTmapX3Step(VDP_LAYER_VID0, v_tmap_x3_step);
    VDP_VID_SetVdmVTmapX2Step(VDP_LAYER_VID0, v_tmap_x2_step);
    VDP_VID_SetVdmVTmapX1Step(VDP_LAYER_VID0, v_tmap_x1_step);
    VDP_VID_SetVdmVTmapX1Pos(VDP_LAYER_VID0, v_tmap_x1_pos);
    VDP_VID_SetVdmVTmapX2Pos(VDP_LAYER_VID0, v_tmap_x2_pos);
    VDP_VID_SetVdmVTmapX3Num(VDP_LAYER_VID0, v_tmap_x3_num);
    VDP_VID_SetVdmVTmapX4Num(VDP_LAYER_VID0, v_tmap_x4_num);
    VDP_VID_SetVTmapX5Num(v_tmap_x5_num);
    VDP_VID_SetVTmapX6Num(v_tmap_x6_num);
    VDP_VID_SetVTmapX7Num(v_tmap_x7_num);
    VDP_VID_SetVTmapX8Num(v_tmap_x8_num);
    VDP_VID_SetVdmVTmapX2Num(VDP_LAYER_VID0, v_tmap_x2_num);
    VDP_VID_SetVdmVTmapX1Num(VDP_LAYER_VID0, v_tmap_x1_num);
    VDP_VID_SetVdmVTmapX3Pos(VDP_LAYER_VID0, v_tmap_x3_pos);
    VDP_VID_SetVdmVTmapX4Pos(VDP_LAYER_VID0, v_tmap_x4_pos);
    VDP_VID_SetVTmapX5Pos(v_tmap_x5_pos);
    VDP_VID_SetVTmapX6Pos(v_tmap_x6_pos);
    VDP_VID_SetVTmapX7Pos(v_tmap_x7_pos);
    VDP_VID_SetVTmapX8Pos(v_tmap_x8_pos);
    VDP_VID_SetVdmVdmGammaRdEn(VDP_LAYER_VID0, vdm_gamma_rd_en);
    VDP_VID_SetVdmVdmGammaParaData(VDP_LAYER_VID0, vdm_gamma_para_data);
    VDP_VID_SetVdmVGmmX4Step(VDP_LAYER_VID0, v_gmm_x4_step);
    VDP_VID_SetVdmVGmmX3Step(VDP_LAYER_VID0, v_gmm_x3_step);
    VDP_VID_SetVdmVGmmX2Step(VDP_LAYER_VID0, v_gmm_x2_step);
    VDP_VID_SetVdmVGmmX1Step(VDP_LAYER_VID0, v_gmm_x1_step);
    VDP_VID_SetVdmVGmmX2Pos(VDP_LAYER_VID0, v_gmm_x2_pos);
    VDP_VID_SetVdmVGmmX1Pos(VDP_LAYER_VID0, v_gmm_x1_pos);
    VDP_VID_SetVdmVGmmX4Pos(VDP_LAYER_VID0, v_gmm_x4_pos);
    VDP_VID_SetVdmVGmmX3Pos(VDP_LAYER_VID0, v_gmm_x3_pos);
    VDP_VID_SetVdmVGmmX4Num(VDP_LAYER_VID0, v_gmm_x4_num);
    VDP_VID_SetVdmVGmmX3Num(VDP_LAYER_VID0, v_gmm_x3_num);
    VDP_VID_SetVdmVGmmX2Num(VDP_LAYER_VID0, v_gmm_x2_num);
    VDP_VID_SetVdmVGmmX1Num(VDP_LAYER_VID0, v_gmm_x1_num);
    VDP_VID_SetVdmVGmmX6Pos(VDP_LAYER_VID0, v_gmm_x6_pos);
    VDP_VID_SetVdmVGmmX5Pos(VDP_LAYER_VID0, v_gmm_x5_pos);
    VDP_VID_SetVdmVGmmX8Pos(VDP_LAYER_VID0, v_gmm_x8_pos);
    VDP_VID_SetVdmVGmmX7Pos(VDP_LAYER_VID0, v_gmm_x7_pos);
    VDP_VID_SetVdmVGmmX8Step(VDP_LAYER_VID0, v_gmm_x8_step);
    VDP_VID_SetVdmVGmmX7Step(VDP_LAYER_VID0, v_gmm_x7_step);
    VDP_VID_SetVdmVGmmX6Step(VDP_LAYER_VID0, v_gmm_x6_step);
    VDP_VID_SetVdmVGmmX5Step(VDP_LAYER_VID0, v_gmm_x5_step);
    VDP_VID_SetVdmVGmmX8Num(VDP_LAYER_VID0, v_gmm_x8_num);
    VDP_VID_SetVdmVGmmX7Num(VDP_LAYER_VID0, v_gmm_x7_num);
    VDP_VID_SetVdmVGmmX6Num(VDP_LAYER_VID0, v_gmm_x6_num);
    VDP_VID_SetVdmVGmmX5Num(VDP_LAYER_VID0, v_gmm_x5_num);
    VDP_VID_SetVdmVdmCscEn(VDP_LAYER_VID0, vdm_csc_en);
    VDP_VID_SetVdmVdmCoef00Csc(VDP_LAYER_VID0, vdm_coef00_csc);
    VDP_VID_SetVdmVdmCoef01Csc(VDP_LAYER_VID0, vdm_coef01_csc);
    VDP_VID_SetVdmVdmCoef02Csc(VDP_LAYER_VID0, vdm_coef02_csc);
    VDP_VID_SetVdmVdmCoef10Csc(VDP_LAYER_VID0, vdm_coef10_csc);
    VDP_VID_SetVdmVdmCoef11Csc(VDP_LAYER_VID0, vdm_coef11_csc);
    VDP_VID_SetVdmVdmCoef12Csc(VDP_LAYER_VID0, vdm_coef12_csc);
    VDP_VID_SetVdmVdmCoef20Csc(VDP_LAYER_VID0, vdm_coef20_csc);
    VDP_VID_SetVdmVdmCoef21Csc(VDP_LAYER_VID0, vdm_coef21_csc);
    VDP_VID_SetVdmVdmCoef22Csc(VDP_LAYER_VID0, vdm_coef22_csc);
    VDP_VID_SetVdmVdmCscScale(VDP_LAYER_VID0, vdm_csc_scale);
    VDP_VID_SetVdmVdmCscClipMin(VDP_LAYER_VID0, vdm_csc_clip_min);
    VDP_VID_SetVdmVdmCscClipMax(VDP_LAYER_VID0, vdm_csc_clip_max);

    if (u32LayerId == VDP_LAYER_VID0)
    {

        VDP_VID_SetVdmVdmV0GammaEn(VDP_LAYER_VID0, vdm_v0_gamma_en);
        VDP_VID_SetVdmVdmV0CscEn(VDP_LAYER_VID0, vdm_v0_csc_en);
        VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VID0, vdm_yuv2rgb_en);
        VDP_VID_SetVdmVdm00Yuv2rgb(VDP_LAYER_VID0, vdm_00_yuv2rgb);
        VDP_VID_SetVdmVdm01Yuv2rgb(VDP_LAYER_VID0, vdm_01_yuv2rgb);
        VDP_VID_SetVdmVdm02Yuv2rgb(VDP_LAYER_VID0, vdm_02_yuv2rgb);
        VDP_VID_SetVdmVdm03Yuv2rgb(VDP_LAYER_VID0, vdm_03_yuv2rgb);
        VDP_VID_SetVdmVdm04Yuv2rgb(VDP_LAYER_VID0, vdm_04_yuv2rgb);
        VDP_VID_SetVdmVdm05Yuv2rgb(VDP_LAYER_VID0, vdm_05_yuv2rgb);
        VDP_VID_SetVdmVdm06Yuv2rgb(VDP_LAYER_VID0, vdm_06_yuv2rgb);
        VDP_VID_SetVdmVdm07Yuv2rgb(VDP_LAYER_VID0, vdm_07_yuv2rgb);
        VDP_VID_SetVdmVdm08Yuv2rgb(VDP_LAYER_VID0, vdm_08_yuv2rgb);
        VDP_VID_SetVdmVdmYuv2rgbscale2p(VDP_LAYER_VID0, vdm_yuv2rgbscale2p);
        VDP_VID_SetVdmVdmYuv2rgb00InDc(VDP_LAYER_VID0, vdm_yuv2rgb_00_in_dc);
        VDP_VID_SetVdmVdmYuv2rgb01InDc(VDP_LAYER_VID0, vdm_yuv2rgb_01_in_dc);
        VDP_VID_SetVdmVdmYuv2rgb02InDc(VDP_LAYER_VID0, vdm_yuv2rgb_02_in_dc);
        VDP_VID_SetVdmVdmYuv2rgb00OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_00_out_dc);
        VDP_VID_SetVdmVdmYuv2rgb01OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_01_out_dc);
        VDP_VID_SetVdmVdmYuv2rgb02OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_02_out_dc);
        VDP_VID_SetVdmVdmYuv2rgbClipMin(VDP_LAYER_VID0, vdm_yuv2rgb_clip_min);
        VDP_VID_SetVdmVdmYuv2rgbClipMax(VDP_LAYER_VID0, vdm_yuv2rgb_clip_max);

    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {

        VDP_VID_SetVdmVdmV1GammaEn(VDP_LAYER_VID0, vdm_v1_gamma_en);
        VDP_VID_SetVdmVdmV1CscEn(VDP_LAYER_VID0, vdm_v1_csc_en);

        VDP_VID_SetVdmVdm10Yuv2rgb(VDP_LAYER_VID0, vdm_10_yuv2rgb);
        VDP_VID_SetVdmVdm11Yuv2rgb(VDP_LAYER_VID0, vdm_11_yuv2rgb);
        VDP_VID_SetVdmVdm12Yuv2rgb(VDP_LAYER_VID0, vdm_12_yuv2rgb);
        VDP_VID_SetVdmVdm13Yuv2rgb(VDP_LAYER_VID0, vdm_13_yuv2rgb);
        VDP_VID_SetVdmVdm14Yuv2rgb(VDP_LAYER_VID0, vdm_14_yuv2rgb);
        VDP_VID_SetVdmVdm15Yuv2rgb(VDP_LAYER_VID0, vdm_15_yuv2rgb);
        VDP_VID_SetVdmVdm16Yuv2rgb(VDP_LAYER_VID0, vdm_16_yuv2rgb);
        VDP_VID_SetVdmVdm17Yuv2rgb(VDP_LAYER_VID0, vdm_17_yuv2rgb);
        VDP_VID_SetVdmVdm18Yuv2rgb(VDP_LAYER_VID0, vdm_18_yuv2rgb);
        VDP_VID_SetVdmVdmYuv2rgbscale2p(VDP_LAYER_VID0, vdm_yuv2rgbscale2p);
        VDP_VID_SetVdmVdmYuv2rgb10InDc(VDP_LAYER_VID0, vdm_yuv2rgb_10_in_dc);

        VDP_VID_SetVdmVdmYuv2rgb11InDc(VDP_LAYER_VID0, vdm_yuv2rgb_11_in_dc);
        VDP_VID_SetVdmVdmYuv2rgb12InDc(VDP_LAYER_VID0, vdm_yuv2rgb_12_in_dc);
        VDP_VID_SetVdmVdmYuv2rgb10OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_10_out_dc);
        VDP_VID_SetVdmVdmYuv2rgb11OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_11_out_dc);
        VDP_VID_SetVdmVdmYuv2rgb12OutDc(VDP_LAYER_VID0, vdm_yuv2rgb_12_out_dc);
        VDP_VID_SetVdmVdmYuv2rgbClipMin(VDP_LAYER_VID0, vdm_yuv2rgb_clip_min);
        VDP_VID_SetVdmVdmYuv2rgbClipMax(VDP_LAYER_VID0, vdm_yuv2rgb_clip_max);

    }


    VDP_VID_SetVdmVdmRgb2yuvEn(VDP_LAYER_VID0, vdm_rgb2yuv_en);
    VDP_VID_SetVdmVdm00Rgb2yuv(VDP_LAYER_VID0, vdm_00_rgb2yuv);
    VDP_VID_SetVdmVdm01Rgb2yuv(VDP_LAYER_VID0, vdm_01_rgb2yuv);
    VDP_VID_SetVdmVdm02Rgb2yuv(VDP_LAYER_VID0, vdm_02_rgb2yuv);
    VDP_VID_SetVdmVdm10Rgb2yuv(VDP_LAYER_VID0, vdm_10_rgb2yuv);
    VDP_VID_SetVdmVdm11Rgb2yuv(VDP_LAYER_VID0, vdm_11_rgb2yuv);
    VDP_VID_SetVdmVdm12Rgb2yuv(VDP_LAYER_VID0, vdm_12_rgb2yuv);
    VDP_VID_SetVdmVdm20Rgb2yuv(VDP_LAYER_VID0, vdm_20_rgb2yuv);
    VDP_VID_SetVdmVdm21Rgb2yuv(VDP_LAYER_VID0, vdm_21_rgb2yuv);
    VDP_VID_SetVdmVdm22Rgb2yuv(VDP_LAYER_VID0, vdm_22_rgb2yuv);
    VDP_VID_SetVdmVdmRgb2yuvscale2p(VDP_LAYER_VID0, vdm_rgb2yuvscale2p);
    VDP_VID_SetVdmVdmRgb2yuv0InDc(VDP_LAYER_VID0, vdm_rgb2yuv_0_in_dc);
    VDP_VID_SetVdmVdmRgb2yuv1InDc(VDP_LAYER_VID0, vdm_rgb2yuv_1_in_dc);
    VDP_VID_SetVdmVdmRgb2yuv2InDc(VDP_LAYER_VID0, vdm_rgb2yuv_2_in_dc);
    VDP_VID_SetVdmVdmRgb2yuv0OutDc(VDP_LAYER_VID0, vdm_rgb2yuv_0_out_dc);
    VDP_VID_SetVdmVdmRgb2yuv1OutDc(VDP_LAYER_VID0, vdm_rgb2yuv_1_out_dc);
    VDP_VID_SetVdmVdmRgb2yuv2OutDc(VDP_LAYER_VID0, vdm_rgb2yuv_2_out_dc);
    VDP_VID_SetVdmVdmRgb2yuvClipMin(VDP_LAYER_VID0, vdm_rgb2yuv_clip_min);
    VDP_VID_SetVdmVdmRgb2yuvClipMax(VDP_LAYER_VID0, vdm_rgb2yuv_clip_max);
    VDP_VID_SetVdmVdmDitherRoundUnlim(VDP_LAYER_VID0, vdm_dither_round_unlim);
    VDP_VID_SetVdmVdmDitherEn(VDP_LAYER_VID0, vdm_dither_en);
    VDP_VID_SetVdmVdmDitherRound(VDP_LAYER_VID0, vdm_dither_round);
    VDP_VID_SetVdmVdmDitherDomainMode(VDP_LAYER_VID0, vdm_dither_domain_mode);
    VDP_VID_SetVdmVdmDitherTapMode(VDP_LAYER_VID0, vdm_dither_tap_mode);
    VDP_VID_SetVdmVdmDitherSedY0(VDP_LAYER_VID0, vdm_dither_sed_y0);
    VDP_VID_SetVdmVdmDitherSedU0(VDP_LAYER_VID0, vdm_dither_sed_u0);
    VDP_VID_SetVdmVdmDitherSedV0(VDP_LAYER_VID0, vdm_dither_sed_v0);
    VDP_VID_SetVdmVdmDitherSedW0(VDP_LAYER_VID0, vdm_dither_sed_w0);
    VDP_VID_SetVdmVdmDitherSedY1(VDP_LAYER_VID0, vdm_dither_sed_y1);
    VDP_VID_SetVdmVdmDitherSedU1(VDP_LAYER_VID0, vdm_dither_sed_u1);
    VDP_VID_SetVdmVdmDitherSedV1(VDP_LAYER_VID0, vdm_dither_sed_v1);
    VDP_VID_SetVdmVdmDitherSedW1(VDP_LAYER_VID0, vdm_dither_sed_w1);
    VDP_VID_SetVdmVdmDitherSedY2(VDP_LAYER_VID0, vdm_dither_sed_y2);
    VDP_VID_SetVdmVdmDitherSedU2(VDP_LAYER_VID0, vdm_dither_sed_u2);
    VDP_VID_SetVdmVdmDitherSedV2(VDP_LAYER_VID0, vdm_dither_sed_v2);
    VDP_VID_SetVdmVdmDitherSedW2(VDP_LAYER_VID0, vdm_dither_sed_w2);
    VDP_VID_SetVdmVdmDitherSedY3(VDP_LAYER_VID0, vdm_dither_sed_y3);
    VDP_VID_SetVdmVdmDitherSedU3(VDP_LAYER_VID0, vdm_dither_sed_u3);
    VDP_VID_SetVdmVdmDitherSedV3(VDP_LAYER_VID0, vdm_dither_sed_v3);
    VDP_VID_SetVdmVdmDitherSedW3(VDP_LAYER_VID0, vdm_dither_sed_w3);
    VDP_VID_SetVdmVdmDitherThrMax(VDP_LAYER_VID0, vdm_dither_thr_max);
    VDP_VID_SetVdmVdmDitherThrMin(VDP_LAYER_VID0, vdm_dither_thr_min);

    return HI_SUCCESS;

}


HI_S32 XDP_DRV_SetVDMCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode, DmCfg_t  *pstDmCfg)
{
    if (HI_NULL == pstPqHdrCfg || VDP_LAYER_VID3 == u32LayerId)
    {
        return HI_FAILURE;
    }

    if (HI_FALSE == XDP_DRV_SetVDMBypassProcess(u32LayerId, pstInfoOut, pstPqHdrCfg, enSceneMode) )
    {
        return HI_SUCCESS;
    }


    XDP_DRV_SetVDMCoef(u32LayerId, pstInfoOut, pstPqHdrCfg, enSceneMode);
    VDP_DRV_SetHiHdrCfg(u32LayerId, pstDmCfg);

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVP0Reso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    if (u32LayerId != VDP_LAYER_VID3)
    {
        VDP_VP_SetVideoPos             (VDP_LAYER_VP0, pstInfoOut->stXdpDispCfg.stFmtReso);
        VDP_VP_SetDispPos              (VDP_LAYER_VP0, pstInfoOut->stXdpDispCfg.stFmtReso);
        VDP_VP_SetInReso               (VDP_LAYER_VP0, pstInfoOut->stXdpDispCfg.stFmtReso);
        VDP_VP_SetLayerGalpha          (VDP_LAYER_VP0, pstInfoOut->stXdpSysCfg.u32AllAlpha);
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidBkg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_BOOL bRgbColorSpace = HI_FALSE;
    VDP_COLOR_SPACE_INFO_S  stColorSpaceInfo = {0};

    VDP_VID_SetLayerGalpha(u32LayerId, pstInfoOut->stXdpSysCfg.u32Alpha);

    if (u32LayerId == VDP_LAYER_VID3)
    {
        return HI_SUCCESS;
    }

    stColorSpaceInfo.enInClrSpace  = pstInfoOut->stXdpSrcCfg.enSrcClrSpace;
    stColorSpaceInfo.enOutClrSpace = pstInfoOut->stXdpDispCfg.enOutClrSpace;

    XDP_DRV_AdjustMixvColor(&pstInfoOut->stXdpBkgCfg.stMixvColor, bRgbColorSpace);
    /* set the mixv background color under RGB colorspace.NOTE:mixv is immediate register. */
    VDP_CBM_SetMixerBkg(VDP_CBM_MIXV0, pstInfoOut->stXdpBkgCfg.stMixvColor);

    VDP_DRV_SetVdpBkg(u32LayerId, &stColorSpaceInfo);
    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_DRV_SetLayerLetterboxBkg();
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidMute(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_VID_SetRegionMuteEnable    (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, HI_FALSE);
        VDP_VID_SetMuteEnable              (u32LayerId, HI_FALSE);
        VDP_VID_SetMultiModeEnable     (u32LayerId, pstInfoOut->stXdpSysCfg.bRegionModeEn);
    }
    else
    {
        VDP_VID_SetMuteEnable          (u32LayerId, HI_FALSE);
        VDP_VID_SetMultiModeEnable     (u32LayerId, HI_FALSE);
    }


    return HI_SUCCESS;
}





HI_S32 XDP_DRV_SetVidAddr(HI_U32 u32LayerId, const XDP_LAYER_VID_INFO_S *pstOutInfo)
{

    HI_U32 u32LumAddr;
    HI_U32 u32ChmAddr;
    HI_U32 u32LumAddr3D;
    HI_U32 u32ChmAddr3D;
    HI_U32 u32LumAddrTile2bit;
    HI_U32 u32ChmAddrTile2bit;

    u32LumAddr   = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr;
    u32ChmAddr   = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr;
    u32LumAddr3D = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumAddr;
    u32ChmAddr3D = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmAddr;

    u32LumAddrTile2bit   = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumAddr;
    u32ChmAddrTile2bit   = pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32ChmAddr;

    if ((VDP_LAYER_VID1 == u32LayerId) && (pstOutInfo->stXdpSysCfg.bRegionModeEn == 1) )
    {
        VDP_VID_SetRegionAddr          (u32LayerId, pstOutInfo->stXdpSysCfg.u32RegionNO, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);
    }
    else
    {
        VDP_VID_SetLayerAddr           (u32LayerId, 0, u32LumAddr, u32ChmAddr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);

        if (pstOutInfo->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
        {
            VDP_VID_SetTileStride      (u32LayerId, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumStr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumStr);

            if (pstOutInfo->stXdpSrcCfg.bDcmpEn == HI_TRUE)
            {
                VDP_VID_SetHeadAddr        (u32LayerId, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32LumAddr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32ChmAddr);
                VDP_VID_SetHeadStride      (u32LayerId, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32LumStr);
                VDP_VID_SetHeadSize        (u32LayerId,  pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32DcmpHeadSize);
            }

            if (pstOutInfo->stXdpDispCfg.enDispMode != VDP_DISP_MODE_2D)
            {
                VDP_PRINT("VDP tile64 format do not support 3D!\n");
                return HI_FAILURE;
            }

            VDP_VID_SetLayerAddr           (u32LayerId, 1, u32LumAddrTile2bit, u32ChmAddrTile2bit, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);
        }

        if (pstOutInfo->stXdpDispCfg.enDispMode != VDP_DISP_MODE_2D)
        {
            VDP_VID_SetLayerAddr           (u32LayerId, 1, u32LumAddr3D, u32ChmAddr3D, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumStr, pstOutInfo->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmStr);
        }
    }
    return HI_SUCCESS;
}











HI_S32  XDP_DRV_GetOptimizePerformance(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    if ((u32LayerId == VDP_LAYER_VID0)
        && (pstInfoOut->stXdpSrcCfg.stSrcRect.u32Hgt * 10 / pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt > 25 )
        && ((pstInfoOut->stXdpDispCfg.stFmtReso.u32Wth == 3840)
            || (pstInfoOut->stXdpDispCfg.stFmtReso.u32Hgt == 2160)))
    {
        pstInfoOut->stXdpLayerExtern.bReduceDataWth = HI_TRUE;
    }

#if  0//98mv200 96mv200 no reducetap
    if ((3840 <= pstInfoOut->stXdpDispCfg.stFmtReso.u32Wth) && (2160 == pstInfoOut->stXdpDispCfg.stFmtReso.u32Hgt)
        && ((pstInfoOut->stXdpSrcCfg.stSrcRect.u32Wth > 1920) || (pstInfoOut->stXdpSrcCfg.stSrcRect.u32Hgt > 1080)))
    {

        pstInfoOut->stXdpLayerExtern.bVtapReduce = HI_TRUE;
    }
#endif
    return HI_SUCCESS;

}

HI_S32 VDP_DRV_GetVidZme2Strategy(XDP_LAYER_VID_INFO_S *pstInfoOut,
                                 HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio,
                                 HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefType)
{

    HI_S32 s32RatioHL = 100;
    HI_S32 s32RatioHC = 100;
    HI_S32 s32RatioVL = 100;
    //HI_S32 s32RatioVC=100;


    HI_S32 s32Ratio1d0 = 1 * 100;
    HI_S32 s32Ratio0d75 = 3 * 100 / 4;
    HI_S32 s32Ratio0d5 = 1 * 100 / 2;
    HI_S32 s32Ratio0d25 = 1 * 100 / 4;
    HI_S32 s32Ratio0d33 = 1 * 100 / 3;
    HI_S32 s32Ratio0d2 = 1 * 100 / 5;

    s32RatioHL  = (pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth * 100)/pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth   ;
    s32RatioHC  = (pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth * 100)/pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth  ;
    s32RatioVL  = (pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight* 100)/pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Hgt   ;

    switch (enPqZmeCoefType)
    {
        case HI_PQ_ZME_COEF_TYPE_LH:
            if (s32RatioHL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHL >= s32Ratio0d75) && (s32RatioHL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHL >= s32Ratio0d5) && (s32RatioHL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHL >= s32Ratio0d33) && (s32RatioHL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHL >= s32Ratio0d25) && (s32RatioHL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHL >= s32Ratio0d2) && (s32RatioHL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_CH:
            if (s32RatioHC == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHC >= s32Ratio0d75) && (s32RatioHC < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHC >= s32Ratio0d5) && (s32RatioHC < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHC >= s32Ratio0d33) && (s32RatioHC < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHC >= s32Ratio0d25) && (s32RatioHC < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHC >= s32Ratio0d2) && (s32RatioHC < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_LV:
        case HI_PQ_ZME_COEF_TYPE_CV:
            if (s32RatioVL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioVL >= s32Ratio0d75) && (s32RatioVL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioVL >= s32Ratio0d5) && (s32RatioVL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioVL >= s32Ratio0d33) && (s32RatioVL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioVL >= s32Ratio0d25) && (s32RatioVL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioVL >= s32Ratio0d2) && (s32RatioVL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;

        default:
            *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            break;
    }

    return  HI_SUCCESS;
}


HI_S32 VDP_DRV_GetVidZmeStrategy(XDP_LAYER_VID_INFO_S *pstInfoOut,
                                 HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio,
                                 HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefType)
{

    HI_S32 s32RatioHL = 100;
    HI_S32 s32RatioHC = 100;
    HI_S32 s32RatioVL = 100;
    //HI_S32 s32RatioVC=100;


    HI_S32 s32Ratio1d0 = 1 * 100;
    HI_S32 s32Ratio0d75 = 3 * 100 / 4;
    HI_S32 s32Ratio0d5 = 1 * 100 / 2;
    HI_S32 s32Ratio0d25 = 1 * 100 / 4;
    HI_S32 s32Ratio0d33 = 1 * 100 / 3;
    HI_S32 s32Ratio0d2 = 1 * 100 / 5;

    if (pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
        || pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE
        || pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        s32RatioHL  = (pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth * 100) / pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth;
        s32RatioHC  = (pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth * 100) / pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth;
        s32RatioVL  = pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Hgt * 100 / pstInfoOut->stXdpFdrCfg.stCropRect.u32Hgt;
    }
    else if (pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422)
    {
        s32RatioHL  = (pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth * 100) / pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth;
        s32RatioHC  = (pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth * 100) / pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth;
        s32RatioVL  = pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Hgt * 100 / pstInfoOut->stXdpFdrCfg.stCropRect.u32Hgt;
    }


    switch (enPqZmeCoefType)
    {
        case HI_PQ_ZME_COEF_TYPE_LH:
            if (s32RatioHL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHL >= s32Ratio0d75) && (s32RatioHL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHL >= s32Ratio0d5) && (s32RatioHL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHL >= s32Ratio0d33) && (s32RatioHL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHL >= s32Ratio0d25) && (s32RatioHL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHL >= s32Ratio0d2) && (s32RatioHL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_CH:
            if (s32RatioHC == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHC >= s32Ratio0d75) && (s32RatioHC < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHC >= s32Ratio0d5) && (s32RatioHC < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHC >= s32Ratio0d33) && (s32RatioHC < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHC >= s32Ratio0d25) && (s32RatioHC < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHC >= s32Ratio0d2) && (s32RatioHC < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_LV:
        case HI_PQ_ZME_COEF_TYPE_CV:
            if (s32RatioVL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioVL >= s32Ratio0d75) && (s32RatioVL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioVL >= s32Ratio0d5) && (s32RatioVL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioVL >= s32Ratio0d33) && (s32RatioVL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioVL >= s32Ratio0d25) && (s32RatioVL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioVL >= s32Ratio0d2) && (s32RatioVL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;

        default:
            *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            break;
    }

    return  HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZmeCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, XDP_THE_NUM_ZME_E enXdpTheNumZme)
{
    HI_PQ_ZME_COEF_RATIO_E enRationHL;
    HI_PQ_ZME_COEF_RATIO_E enRationHC;
    HI_PQ_ZME_COEF_RATIO_E enRationVL;
    HI_PQ_ZME_COEF_RATIO_E enRationVC;

    if (VDP_LAYER_VID3 == u32LayerId)
    {
        return HI_SUCCESS;
    }


    if ((VDP_LAYER_VID0 == u32LayerId || VDP_LAYER_VID1 == u32LayerId) && (XDP_THE_NUM_ZME1 == enXdpTheNumZme))
    {

        enRationHL =  pstInfoOut->stXdpLayerExtern.enRationHL ;
        enRationHC =  pstInfoOut->stXdpLayerExtern.enRationHC ;
        enRationVL =  pstInfoOut->stXdpLayerExtern.enRationVL ;
        enRationVC =  pstInfoOut->stXdpLayerExtern.enRationVC ;

        GetVdpZmeCoef(enRationHL, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);

        GetVdpZmeCoef(enRationHC, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));


        if (HI_TRUE == pstInfoOut->stXdpLayerExtern.bVtapReduce)
        {
            GetVdpZmeCoef(enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_5T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            GetVdpZmeCoef(enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_3T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        }
        else
        {
            GetVdpZmeCoef(enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            GetVdpZmeCoef(enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }


    }
    else if ((VDP_LAYER_VID0 == u32LayerId ) && (XDP_THE_NUM_ZME2 == enXdpTheNumZme))
    {

        enRationHL = HI_PQ_ZME_COEF_E1;// pstInfoOut->stXdpLayerExtern.enRationHL ;
        enRationHC = HI_PQ_ZME_COEF_E1;// pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].enRationHC ;
        enRationVL = HI_PQ_ZME_COEF_E1;// pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].enRationVL ;
        enRationVC = HI_PQ_ZME_COEF_E1;// pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].enRationVC ;

        GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);

        GetVdpZmeCoef(HI_PQ_ZME_COEF_1, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(HI_PQ_ZME_COEF_1, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(HI_PQ_ZME_COEF_1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

    }
    return HI_SUCCESS;

}

HI_VOID XDP_DRV_GetVidZmeRationCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_PQ_ZME_COEF_RATIO_E enRationHL = HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationHC= HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationVL= HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationVC= HI_PQ_ZME_COEF_E1;

    VDP_DRV_GetVidZmeStrategy(pstInfoOut, &enRationHL, HI_PQ_ZME_COEF_TYPE_LH);
    VDP_DRV_GetVidZmeStrategy(pstInfoOut, &enRationHC, HI_PQ_ZME_COEF_TYPE_CH);
    VDP_DRV_GetVidZmeStrategy(pstInfoOut, &enRationVL, HI_PQ_ZME_COEF_TYPE_LV);
    VDP_DRV_GetVidZmeStrategy(pstInfoOut, &enRationVC, HI_PQ_ZME_COEF_TYPE_CV);

    pstInfoOut->stXdpLayerExtern.enRationHL = enRationHL;
    pstInfoOut->stXdpLayerExtern.enRationHC = enRationHC;
    pstInfoOut->stXdpLayerExtern.enRationVL = enRationVL;
    pstInfoOut->stXdpLayerExtern.enRationVC = enRationVC;

    if((u32LayerId == VDP_LAYER_VID0) && ((HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable)
        || (HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable)))
    {

        VDP_DRV_GetVidZme2Strategy(pstInfoOut, &enRationHL, HI_PQ_ZME_COEF_TYPE_LH);
        VDP_DRV_GetVidZme2Strategy(pstInfoOut, &enRationHC, HI_PQ_ZME_COEF_TYPE_CH);
        VDP_DRV_GetVidZme2Strategy(pstInfoOut, &enRationVL, HI_PQ_ZME_COEF_TYPE_LV);
        VDP_DRV_GetVidZme2Strategy(pstInfoOut, &enRationVC, HI_PQ_ZME_COEF_TYPE_CV);

        pstInfoOut->stXdpLayerExtern.enZme2RationHL = enRationHL;
        pstInfoOut->stXdpLayerExtern.enZme2RationHC = enRationHC;
        pstInfoOut->stXdpLayerExtern.enZme2RationVL = enRationVL;
        pstInfoOut->stXdpLayerExtern.enZme2RationVC = enRationVC;
    }
    return ;
}

HI_S32 VDP_DRV_SetZmeCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut )
{

    HI_PQ_ZME_COEF_RATIO_E enRationHL;
    HI_PQ_ZME_COEF_RATIO_E enRationHC;
    HI_PQ_ZME_COEF_RATIO_E enRationVL;
    HI_PQ_ZME_COEF_RATIO_E enRationVC;

    VDP_COEF_BUF_E enVdpCoefBufZmeHTmp = VDP_COEF_BUF_ZMEH;
    VDP_COEF_BUF_E enVdpCoefBufZmeVTmp = VDP_COEF_BUF_ZMEV;

    if (u32LayerId == VDP_LAYER_VID3)
    {
        return HI_SUCCESS;
    }

    enVdpCoefBufZmeHTmp = (u32LayerId == VDP_LAYER_VID0) ? VDP_COEF_BUF_ZMEH : VDP_COEF_BUF_ZME_V1_H;
    enVdpCoefBufZmeVTmp = (u32LayerId == VDP_LAYER_VID0) ? VDP_COEF_BUF_ZMEV : VDP_COEF_BUF_ZME_V1_V;

    enRationHL  =  pstInfoOut->stXdpLayerExtern.enRationHL;
    enRationHC  =  pstInfoOut->stXdpLayerExtern.enRationHC;
    enRationVL  =  pstInfoOut->stXdpLayerExtern.enRationVL;
    enRationVC  =  pstInfoOut->stXdpLayerExtern.enRationVC;


    if ((VDP_LAYER_VID0 == u32LayerId) && (((HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable)|| (HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable))))
    {
        GetVdpZmeCoef(enRationHL, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeHTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(enRationHC, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CH, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeHTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));


        if (HI_TRUE == pstInfoOut->stXdpLayerExtern.bVtapReduce)
        {
            GetVdpZmeCoef(enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_5T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_5LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            GetVdpZmeCoef(enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_3T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_3CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }
        else
        {
            GetVdpZmeCoef(enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_6LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            GetVdpZmeCoef(enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }

        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeHTmp]));
        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeVTmp]));


        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_HOR);
        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_VER);

    }

    if ((VDP_LAYER_VID0 == u32LayerId )
        && (((HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable)|| (HI_TRUE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))))
    {
        enRationHL  =  pstInfoOut->stXdpLayerExtern.enZme2RationHL;
        enRationHC  =  pstInfoOut->stXdpLayerExtern.enZme2RationHC;
        enRationVL  =  pstInfoOut->stXdpLayerExtern.enZme2RationVL;
        enRationVC  =  pstInfoOut->stXdpLayerExtern.enZme2RationVC;

        GetVdpZmeCoef(enRationHL, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2H]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(enRationHC, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2H] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_6LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2V]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        GetVdpZmeCoef(enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2V] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        VDP_VID_SetZme2CoefAddr(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME2H]));
        VDP_VID_SetZme2CoefAddr(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME2V]));

        VDP_VID_SetParaUpd(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_HOR);
        VDP_VID_SetParaUpd(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_VER);
    }

    if( VDP_LAYER_VID1 == u32LayerId)
    {
        VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeHTmp]));
        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeVTmp]));
        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_HOR);
        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_VER);

    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidHZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    if (pstInfoOut->stXdpHZmeCfg.bHzmeEn == HI_TRUE)
    {
        pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth /= 2;
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZmeFmt(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    if (pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
        || pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE
        ||  pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_420;
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_422;
    }
    else if (pstInfoOut->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_444)
    {
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_444;
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_444;
    }
    else
    {
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt = VDP_PROC_FMT_SP_422;
        pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_422;
    }


    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZme3DCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_U32 u32HorRation = 1;
    HI_U32 u32VerRation = 1;

    if (pstInfoIn->stXdpDispCfg.enDispMode == VDP_DISP_MODE_SBS)
    {
        u32HorRation = 2;
        u32VerRation = 1;
    }
    else if ((pstInfoIn->stXdpDispCfg.enDispMode  == VDP_DISP_MODE_TAB)
             || (pstInfoIn->stXdpDispCfg.enDispMode  == VDP_DISP_MODE_LBL))
    {
        u32HorRation = 1;
        u32VerRation = 2;
    }
    else
    {
        u32HorRation = 1;
        u32VerRation = 1;
    }

    pstInfoOut->stXdpLayerExtern.u32HorRation = u32HorRation;
    pstInfoOut->stXdpLayerExtern.u32VerRation = u32VerRation;

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZmeCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    XDP_DRV_GetVidZmeFmt(u32LayerId,pstInfoOut);

    XDP_DRV_GetVidHZme(u32LayerId, pstInfoIn, pstInfoOut);

    XDP_DRV_GetVidZme3DCfg(u32LayerId, pstInfoIn, pstInfoOut);

    XDP_DRV_GetOptimizePerformance(u32LayerId, pstInfoOut);

    XDP_DRV_GetVidZmeRationCoef(u32LayerId, pstInfoOut);

    //XDP_DRV_GetVidZmeCoef(u32LayerId, pstInfoOut, XDP_THE_NUM_ZME1);
    //XDP_DRV_GetVidZmeCoef(u32LayerId, pstInfoOut, XDP_THE_NUM_ZME2);

    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetVidHPZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    if (HI_FALSE == pstInfoOut->stXdpHZmeCfg.bHzmeEn)
    {
        VDP_VID_SetHpzmeHpzmeEn(VDP_LAYER_VID0, pstInfoOut->stXdpHZmeCfg.bHzmeEn);
        return HI_SUCCESS;
    }

    if (VDP_LAYER_VID0 == u32LayerId)
    {
        VDP_VID_SetHpzmeHpzmeEn(VDP_LAYER_VID0, pstInfoOut->stXdpHZmeCfg.bHzmeEn);
        VDP_VID_SetHpzmeHpzmeMode(VDP_LAYER_VID0, pstInfoOut->stXdpHZmeCfg.enHzmeMode);

        VDP_VID_SetHpzmeCoef0(VDP_LAYER_VID0, 6);
        VDP_VID_SetHpzmeCoef1(VDP_LAYER_VID0, 52);
        VDP_VID_SetHpzmeCoef2(VDP_LAYER_VID0, 6);

    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidZme1(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_U32 u32RatioH = 1;
    HI_U32 u32RatioV = 1;

    VDP_RECT_S stZme1In  = {0};
    VDP_RECT_S stZme1Out = {0};

    if(( HI_FALSE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable )
      && (HI_FALSE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable) )
    {
        VDP_VID_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HOR, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable);
        VDP_VID_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VER, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable);
        return HI_SUCCESS;
    }

    stZme1In.u32Hgt = pstInfoOut->stXdpSrcCfg.stSrcRect.u32Hgt;
    stZme1In.u32Wth= pstInfoOut->stXdpFdrCfg.stCropRect.u32Wth;

    stZme1Out = (VDP_LAYER_VID0 == u32LayerId) ? pstInfoOut->stXdpZmeCfg.stZme2InRect : pstInfoOut->stXdpPositionCfg.stVideoRect;
    if (stZme1In.u32Hgt >= stZme1Out.u32Hgt)
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 0, 0);
    }
    else
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 1, 0);
    }

    if (stZme1In.u32Wth >= stZme1Out.u32Wth)
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 0, 0);
    }
    else
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 1, 0);
    }

    VDP_VID_SetZmeEnable  (u32LayerId, VDP_ZME_MODE_HOR, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable);
    VDP_VID_SetZmeEnable  (u32LayerId, VDP_ZME_MODE_VER, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable);

    u32RatioH  = (stZme1In.u32Wth / 2 * ZME_HPREC) / stZme1Out.u32Wth * 2 * pstInfoOut->stXdpLayerExtern.u32HorRation;
    u32RatioV  = (stZme1In.u32Hgt * ZME_VPREC) / stZme1Out.u32Hgt * pstInfoOut->stXdpLayerExtern.u32VerRation;
    VDP_VID_SetZmeHorRatio(u32LayerId, u32RatioH);
    VDP_VID_SetZmeVerRatio(u32LayerId, u32RatioV);

    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERL,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERC,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERBL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERBC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_HORL,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_HORC,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC);
    VDP_VID_SetZmeInFmt   (u32LayerId, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt );
    VDP_VID_SetZmeOutFmt  (u32LayerId, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt);


    VDP_VID_SetZmeHfirOrder(u32LayerId, VDP_ZME_ORDER_VH);

    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_HORL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_HORC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_VERL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_VERC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC);

    VDP_VID_SetZmeMidEnable(u32LayerId, VDP_ZME_MODE_VER, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV);
    VDP_VID_SetZmeMidEnable(u32LayerId, VDP_ZME_MODE_HOR, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH);

    return HI_SUCCESS;
}


HI_S32 VDP_DRV_SetVidZme2(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    if(( HI_FALSE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable )
      && (HI_FALSE == pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable) )
    {
         VDP_VID_SetZme2Enable              (VDP_LAYER_VID0, VDP_ZME_MODE_HOR, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable);
         VDP_VID_SetZme2Enable              (VDP_LAYER_VID0, VDP_ZME_MODE_VER, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable);
        return HI_SUCCESS;
    }

    if (VDP_LAYER_VID0 == u32LayerId)
    {
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printk("ZME2 In.W %d, H %d, Out.W %d, H %d \n", pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth,
               pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Hgt,
               pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth,
               pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt);
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        VDP_VID_SetZme2FirEnable           (VDP_LAYER_VID0, VDP_ZME_MODE_HORL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL);
        VDP_VID_SetZme2FirEnable           (VDP_LAYER_VID0, VDP_ZME_MODE_HORC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC);
        VDP_VID_SetZme2MidEnable           (VDP_LAYER_VID0, VDP_ZME_MODE_HOR,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH);

        VDP_VID_SetZme2Enable              (VDP_LAYER_VID0, VDP_ZME_MODE_HOR, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable);
        VDP_VID_SetZme2HorRatio            (VDP_LAYER_VID0, pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Wth * ZME_HPREC / pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth);

        VDP_VID_SetZme2Enable              (VDP_LAYER_VID0, VDP_ZME_MODE_VER, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable);
        VDP_VID_SetZme2FirEnable           (VDP_LAYER_VID0,  VDP_ZME_MODE_VERL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL);
        VDP_VID_SetZme2FirEnable           (VDP_LAYER_VID0,  VDP_ZME_MODE_VERC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC);
        VDP_VID_SetZme2MidEnable           (VDP_LAYER_VID0, VDP_ZME_MODE_VER,    pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV);

        //VDP_VID_SetZme2Phase      (VDP_LAYER_VID0, VDP_ZME_MODE_HOR, 0 * ZME_HPREC);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_VERL,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVL);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_VERC,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVC);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_VERBL, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVLBtm);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_VERBC, pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVCBtm);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_HORL,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHL);
        VDP_VID_SetZme2Phase      (u32LayerId, VDP_ZME_MODE_HORC,  pstInfoOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHC);

        VDP_VID_SetZme2VerRatio            (VDP_LAYER_VID0, pstInfoOut->stXdpZmeCfg.stZme2InRect.u32Hgt * ZME_VPREC / pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt);
    }
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidIfir(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_S32 s32V0IfirCoef[8] = {0, 0, 0, 0, 0, 0, -10, 42};
    HI_S32 s32V1IfirCoef[8] = {0, 0, 0, 0, 0, 0, -10, 42};
    HI_S32 s32V3IfirCoef[8] = { -7, 12, -17, 25, -38, 58, -105, 328};



    VDP_VID_SetIfirMode            (u32LayerId, VDP_IFIRMODE_6TAPFIR);

    switch (u32LayerId)
    {
        case VDP_LAYER_VID0 :
            VDP_VID_SetIfirCoef            (VDP_LAYER_VID0, s32V0IfirCoef);
            break;
        case VDP_LAYER_VID1 :
            VDP_VID_SetIfirCoef            (VDP_LAYER_VID1, s32V1IfirCoef);
            break;
        case VDP_LAYER_VID3 :
            VDP_VID_SetIfirCoef            (VDP_LAYER_VID3, s32V3IfirCoef);
            break;
        default :
            VDP_PRINT("VDP_DRV_SetVidIfir  Error !!! u32LayerId = %d\n",u32LayerId);
            break;
    }
    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetVidDataWidthForPerformance(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    if (VDP_LAYER_VID0 != u32LayerId)
    {
        return HI_SUCCESS;
    }

    if (pstInfoOut->stXdpLayerExtern.bReduceDataWth)
    {
        VDP_VID_SetDataWidth(u32LayerId, VDP_DATA_WTH_8);
    }
    else
    {
        VDP_VID_SetDataWidth(u32LayerId, pstInfoOut->stXdpSrcCfg.enDataWidth);
    }

    VDP_VID_SetVtapReduce(u32LayerId, (pstInfoOut->stXdpLayerExtern.bVtapReduce == HI_TRUE ) ? 1 : 0);

    return HI_SUCCESS;

}

HI_S32 XDP_DRV_SetVidZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    VDP_DRV_SetVidIfir(u32LayerId, pstInfoOut);

    if (u32LayerId == VDP_LAYER_VID3)
    {
        return HI_FAILURE;
    }

    VDP_DRV_SetVidHPZme(u32LayerId, pstInfoOut);
    VDP_DRV_SetVidZme1(u32LayerId, pstInfoOut);
    VDP_DRV_SetVidZme2(u32LayerId, pstInfoOut);
    VDP_DRV_SetVidDataWidthForPerformance(u32LayerId, pstInfoOut);

    VDP_DRV_SetZmeCoef(u32LayerId, pstInfoOut);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetV0V1CscReg(HI_U32 u32LayerId, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
#ifndef  __DISP_PLATFORM_BOOT__
    VDP_VID_SetVdmVdmYuv2rgbscale2p(0, 13);
    VDP_VID_SetVdmVdmYuv2rgbClipMin(0, 0);
    VDP_VID_SetVdmVdmYuv2rgbClipMax(0, 1023);


    //VDP_VID_SetVdmVdmGmmEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmTmapEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmDegmmEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmEn(VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetVdmVdmDitherEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmRgb2yuvEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VID0, HI_FALSE);
    //VDP_VID_SetVdmVdmCscEn(VDP_LAYER_VID0, HI_FALSE);
    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdmV0CscEn  (VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdm00Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef00);
        VDP_VID_SetVdmVdm01Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef01);
        VDP_VID_SetVdmVdm02Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef02);
        VDP_VID_SetVdmVdm03Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef10);
        VDP_VID_SetVdmVdm04Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef11);
        VDP_VID_SetVdmVdm05Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef12);
        VDP_VID_SetVdmVdm06Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef20);
        VDP_VID_SetVdmVdm07Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef21);
        VDP_VID_SetVdmVdm08Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef22);
        VDP_VID_SetVdmVdmYuv2rgb00InDc(VDP_LAYER_VID0,  stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_in_dc0 );
        VDP_VID_SetVdmVdmYuv2rgb01InDc(VDP_LAYER_VID0,  stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_in_dc1 );
        VDP_VID_SetVdmVdmYuv2rgb02InDc(VDP_LAYER_VID0,  stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_in_dc2 );
        VDP_VID_SetVdmVdmYuv2rgb00OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc0);
        VDP_VID_SetVdmVdmYuv2rgb01OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc1);
        VDP_VID_SetVdmVdmYuv2rgb02OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc2);


    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdmV1CscEn  (VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdmV1CscEn  (VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdm10Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef00);
        VDP_VID_SetVdmVdm11Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef01);
        VDP_VID_SetVdmVdm12Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef02);
        VDP_VID_SetVdmVdm13Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef10);
        VDP_VID_SetVdmVdm14Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef11);
        VDP_VID_SetVdmVdm15Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef12);
        VDP_VID_SetVdmVdm16Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef20);
        VDP_VID_SetVdmVdm17Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef21);
        VDP_VID_SetVdmVdm18Yuv2rgb(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef22);

        VDP_VID_SetVdmVdmYuv2rgb10InDc (VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_in_dc0 );
        VDP_VID_SetVdmVdmYuv2rgb11InDc (VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_in_dc1 );
        VDP_VID_SetVdmVdmYuv2rgb12InDc (VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_in_dc2 );
        VDP_VID_SetVdmVdmYuv2rgb10OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc0);
        VDP_VID_SetVdmVdmYuv2rgb11OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc1);
        VDP_VID_SetVdmVdmYuv2rgb12OutDc(VDP_LAYER_VID0, stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc2);



    }

#endif

    return HI_SUCCESS;

}

HI_S32 VDP_DRV_GetCscMode(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    VDP_CLR_SPACE_E enInClr  = pstInfoOut->stXdpSrcCfg.enSrcClrSpace;
    VDP_CLR_SPACE_E enOutClr = pstInfoOut->stXdpDispCfg.enOutClrSpace;

    if (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_RGB_601)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_601;/* YCbCr_601 L  -> RGB */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_601;/* YCbCr_601 L -> RGB */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709         ; /* YCbCr_709 L  -> RGB */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709         ; /* YCbCr_709 L  -> RGB */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_601 && enOutClr == VDP_CLR_SPACE_YUV_601_L)
    {
        *enCscMode = VDP_CSC_RGB2YUV_601         ; /* RGB          -> YCbCr_601 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_601         ; /* RGB          -> YCbCr_601 L */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_709 && enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        *enCscMode = VDP_CSC_RGB2YUV_709         ; /* RGB          -> YCbCr_709 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709         ; /* RGB          -> YCbCr_709 L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
    {
        *enCscMode = VDP_CSC_YUV2YUV_709_601     ; /* YCbCr_709 L  -> YCbCr_601 L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV_709_601     ; /* YCbCr_709 L  -> YCbCr_601 L */
    }
    else if ((enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
             || (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_YUV_709_L)
             || (enInClr == VDP_CLR_SPACE_YUV_709 && enOutClr == VDP_CLR_SPACE_YUV_709_L))
    {
        *enCscMode = VDP_CSC_YUV2YUV             ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV             ; /* YCbCr L      -> YCbCr L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        *enCscMode = VDP_CSC_YUV2YUV_601_709     ; /* YCbCr_601 L  -> YCbCr_709 L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV_601_709     ; /* YCbCr_601 L  -> YCbCr_709 L */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_709 && enOutClr == VDP_CLR_SPACE_RGB_2020)
    {
        *enCscMode = VDP_CSC_RGB2RGB_709_2020    ; /* RGB_709      -> RGB_2020 */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB_709_2020    ; /* RGB_709      -> RGB_2020 */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_2020 && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
    {
        *enCscMode = VDP_CSC_RGB2YUV_2020_2020_L  ; /* RGB_2020    -> YCbCr_2020 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_2020_2020_L  ; /* RGB_2020    -> YCbCr_2020 L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020)
    {
        *enCscMode = VDP_CSC_YUV2RGB_2020_2020_L  ; /* YCbCr_2020 L -> RGB_2020 */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_2020_L  ; /* YCbCr_2020 L -> RGB_2020 */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_2020 && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode = VDP_CSC_RGB2RGB_2020_709    ; /* RGB_2020     -> RGB_709 */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB_2020_709    ; /* RGB_2020     -> RGB_709 */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_601 && enOutClr == VDP_CLR_SPACE_RGB_2020)
    {
        *enCscMode = VDP_CSC_RGB2RGB_601_2020    ; /* RGB_601      -> RGB_2020 */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB_601_2020    ; /* RGB_601      -> RGB_2020 */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_2020 && enOutClr == VDP_CLR_SPACE_RGB_601)
    {
        *enCscMode = VDP_CSC_RGB2RGB_2020_601    ; /* RGB_2020     -> RGB_601 */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB_2020_601    ; /* RGB_2020     -> RGB_601 */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
    {
        *enCscMode = VDP_CSC_YUV2YUV_2020_601_L_L ; /* YCbCr_2020 L -> YCbCr_601 L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV_2020_601_L_L ; /* YCbCr_2020 L -> YCbCr_601 L */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_2020 && enOutClr == VDP_CLR_SPACE_YUV_601_L)
    {
        *enCscMode = VDP_CSC_RGB2YUV_2020_601_L  ; /* RGB_2020     -> YCbCr_601 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_2020_601_L  ; /* RGB_2020     -> YCbCr_601 L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_601 && enOutClr == VDP_CLR_SPACE_RGB_601)
    {
        *enCscMode = VDP_CSC_YUV2RGB_601_FULL    ; /* YCbCr_601 F  -> RGB */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_601_FULL    ; /* YCbCr_601 F  -> RGB */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_709 && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709_FULL    ; /* YCbCr_709 F  -> RGB */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709_FULL    ; /* YCbCr_709 F  -> RGB */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_601 && enOutClr == VDP_CLR_SPACE_YUV_601)
    {
        *enCscMode = VDP_CSC_RGB2YUV_601_FULL    ; /* RGB          -> YCbCr_601 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_601_FULL    ; /* RGB          -> YCbCr_601 F */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_709 && enOutClr == VDP_CLR_SPACE_YUV_709)
    {
        *enCscMode = VDP_CSC_RGB2YUV_709_FULL    ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709_FULL    ; /* RGB          -> YCbCr_709 F */
    }
    else if ((enInClr == VDP_CLR_SPACE_RGB_601 && enOutClr == VDP_CLR_SPACE_RGB_601)
             || (enInClr == VDP_CLR_SPACE_RGB_709 && enOutClr == VDP_CLR_SPACE_RGB_709)
             || (enInClr == VDP_CLR_SPACE_RGB_2020 && enOutClr == VDP_CLR_SPACE_RGB_2020))
    {
        *enCscMode = VDP_CSC_RGB2RGB             ; /* RGB          -> RGB */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB             ; /* RGB          -> RGB */
    }
    else if ((enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
             || (enInClr == VDP_CLR_SPACE_YUV_601 && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
             || (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
             || (enInClr == VDP_CLR_SPACE_YUV_709 && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
             || (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_YUV_2020_L)

            )
    {
        *enCscMode = VDP_CSC_YUV2YUV             ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV             ; /* YCbCr L      -> YCbCr L */


    }
    else if ((enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_709_L)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_709)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_YUV_601))
    {
        *enCscMode = VDP_CSC_YUV2YUV             ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2YUV_2020_709_L_L;

    }
    else if ((enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_709)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_601)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_601_L)
             || (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_709_L))
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_709_L ;

    }
    else if (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_601   ;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_601 ;
    }
    else
    {
        VDP_PRINT("VDP Err csc mode in %d out %d!\n", enInClr, enOutClr);
    }
    return HI_SUCCESS;

}

HI_S32 XDP_DRV_AdjustVidCscInfo(HI_U32 u32LayerId, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
    if (u32LayerId == VDP_LAYER_VID0)
    {
        //stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc0 *= 4;
        //stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc1 *= 4;
        //stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc.csc_out_dc2 *= 4;

        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef00 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef01 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef02 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef10 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef11 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef12 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef20 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef21 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef22 *= 8;
    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {

        //stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc0 *= 4;
        //stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc1 *= 4;
        // stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc.csc_out_dc2 *= 4;

        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef00 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef01 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef02 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef10 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef11 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef12 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef20 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef21 *= 8;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef22 *= 8;

    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidCscInfo(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
    HI_PQ_CSC_CRTL_S stCscCtrl = {0};
    VDP_CSC_MODE_E enCscMode = {0};
    HI_PQ_CSC_MODE_E enPqCscMode = {0};
    HI_PQ_CSC_COEF_S   stPqCscCoef = {0};
    HI_PQ_CSC_DCCOEF_S stPqCscDc = {0};
    HI_PQ_CSC_TYPE_E enHiPqCscType = HI_PQ_CSC_TUNING_V0;

    VDP_DRV_GetCscMode(u32LayerId, pstInfoOut, &enCscMode, &enPqCscMode);


    //printk("--in--%d-out %d---\n",enInClr,enOutClr);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        stCscCtrl.bCSCEn    = HI_TRUE;
        stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;
        enHiPqCscType =  HI_PQ_CSC_TUNING_V0;

        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].enCbbCscMode = enCscMode;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].enPqCscMode  = enPqCscMode;
    }
    else  if (u32LayerId == VDP_LAYER_VID1)
    {
        stCscCtrl.bCSCEn    = HI_TRUE;
        stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V1;
        enHiPqCscType =  HI_PQ_CSC_TUNING_V1;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].enCbbCscMode = enCscMode;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].enPqCscMode  = enPqCscMode;

    }

    else if (u32LayerId == VDP_LAYER_VID3)
    {
        stCscCtrl.bCSCEn    = HI_TRUE;
        stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V3;
        enHiPqCscType =  HI_PQ_CSC_TUNING_V3;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V3].enCbbCscMode = enCscMode;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V3].enPqCscMode  = enPqCscMode;

    }

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);
    memcpy(&stXdpCscCfg[enHiPqCscType].stPqCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stXdpCscCfg[enHiPqCscType].stPqCscDc,   &stPqCscDc,   sizeof(VDP_CSC_DC_COEF_S));

    XDP_DRV_AdjustVidCscInfo(u32LayerId, stXdpCscCfg);

    return HI_SUCCESS;

}

HI_S32 XDP_DRV_SetVidCsc(HI_U32 u32LayerId, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{

    VDP_CSC_COEF_S     stVdpCscCoef = {0};
    VDP_CSC_DC_COEF_S  stVdpDcCscCoef = {0};

    if (u32LayerId == VDP_LAYER_VID3)
    {
        memcpy(&stVdpCscCoef, &stXdpCscCfg[HI_PQ_CSC_TUNING_V3].stPqCscCoef, sizeof(VDP_CSC_COEF_S));
        memcpy(&stVdpDcCscCoef, &stXdpCscCfg[HI_PQ_CSC_TUNING_V3].stPqCscDc,   sizeof(VDP_CSC_DC_COEF_S));

        VDP_VID_SetCscEnable          (u32LayerId, HI_TRUE);
        VDP_VID_SetCscCoef            (u32LayerId, stVdpCscCoef);
        VDP_VID_SetCscDcCoef          (u32LayerId, stVdpDcCscCoef);
    }
    else
    {
        VDP_DRV_SetV0V1CscReg(u32LayerId, stXdpCscCfg);
    }

    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetVidLayerRegionAttr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    if ((VDP_LAYER_VID1 == u32LayerId)&& (pstInfoOut->stXdpSysCfg.bRegionModeEn == 1) )
    {
        VDP_VID_SetRegionEnable        (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpSysCfg.bRegionEn);
        VDP_VID_SetRegionReso          (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpPositionCfg.stVideoRect);
        VDP_VID_SetRegionAddr          (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr, pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr, pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr, pstInfoOut->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);

        VDP_VID_Set16RegionSmmuLumBypass   (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
        VDP_VID_Set16RegionSmmuChromBypass (u32LayerId, pstInfoOut->stXdpSysCfg.u32RegionNO, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
    }

    return HI_SUCCESS;
}


XDP_LAYER_VID_INFO_S stInfoTmp;
DmCfg_t  stDmCfg;

HI_S32 VDP_DRV_SetVidLayer(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstLayerInfoIn, HI_PQ_HDR_CFG  *pstPqHdrCfg)
{
    XDP_LAYER_VID_INFO_S *pstOutInfo = HI_NULL;
    HIHDR_SCENE_MODE_E    enSceneMode = HIHDR_BYPASS_MODE;
    GDM_SCENE_MODE_E      enGdmSceneMode = GDM_BYPASS_MODE;
    XDP_CSC_CFG_S         stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT];

    if (HI_SUCCESS == XDP_DRV_JudgeVidLayerEnable(u32LayerId, pstLayerInfoIn))
    {
        return HI_SUCCESS;
    }

    if ((HI_FALSE == pstLayerInfoIn->stXdpLayerExtern.bConfigWholeLayer) && (VDP_LAYER_VID1 == u32LayerId))
    {

        VDP_DRV_SetVidLayerRegionAttr(u32LayerId, pstLayerInfoIn);
        XDP_DRV_SetRegUp(u32LayerId);

        return HI_SUCCESS;
    }

    memset((HI_VOID *)&stInfoTmp, 0, sizeof(XDP_LAYER_VID_INFO_S));
    memset((HI_VOID *)&stDmCfg, 0, sizeof(DmCfg_t));
    memcpy((HI_VOID *)&stInfoTmp, pstLayerInfoIn, sizeof(XDP_LAYER_VID_INFO_S));
    pstOutInfo = &stInfoTmp;

    if ( VDP_LAYER_VID0 == u32LayerId
      || VDP_LAYER_VID1 == u32LayerId)
    {
        XDP_DRV_HdrRegClean(pstOutInfo);
    }

    XDP_DRV_GetLayerMuteInfo(pstOutInfo);

    XDP_DRV_SetVidMute(u32LayerId, pstOutInfo);

    XDP_DRV_GetVidLayerFdr(u32LayerId, pstLayerInfoIn, pstOutInfo);

    XDP_DRV_SetVidLayerFdr(u32LayerId, pstOutInfo);

    XDP_DRV_GetVidAddrAfterCrop(u32LayerId, pstLayerInfoIn, pstOutInfo);

    XDP_DRV_SetVidAddr(u32LayerId, pstOutInfo);

    XDP_DRV_GetVidZmeCfg(u32LayerId, pstLayerInfoIn, pstOutInfo);

    XDP_DRV_SetVidZme (u32LayerId, pstOutInfo);

    XDP_DRV_SetVidReso(u32LayerId, pstOutInfo);

    XDP_DRV_GetVidCscInfo(u32LayerId, pstOutInfo, stXdpCscCfg);

    XDP_DRV_SetVidCsc(u32LayerId, stXdpCscCfg);

    XDP_DRV_SetVidBkg(u32LayerId, pstOutInfo);

    XDP_DRV_SetVP0Reso(u32LayerId, pstOutInfo);

    XDP_DRV_GetVidSceneMode(u32LayerId, pstLayerInfoIn, &enSceneMode);

    VDP_DRV_GetHiHdrCfg(u32LayerId, pstOutInfo, pstPqHdrCfg, enSceneMode, &stDmCfg);

    XDP_DRV_SetVDMCfg(u32LayerId, pstOutInfo, pstPqHdrCfg, enSceneMode, &stDmCfg);

    XDP_DRV_GetGfxSceneMode(u32LayerId, pstOutInfo, &enGdmSceneMode);

    VDP_DRV_SetGdmMode(u32LayerId, enGdmSceneMode);

    XDP_DRV_SetVidCBM(u32LayerId, pstOutInfo);

    XDP_DRV_SetRegUp(u32LayerId);

    return HI_SUCCESS;
}
#endif

