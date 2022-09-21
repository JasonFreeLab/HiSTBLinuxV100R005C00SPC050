#include "vdp_drv_bkg_process.h"
#include "vdp_hal_comm.h"
#include "vdp_hal_ip_vdm.h"
#include "VdpHiHDR_cfg.h"
#include "vdp_drv_ip_vdm.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_func_pq_csc.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "drv_pq_ext.h"

HI_S32 VDP_DRV_GetCsc0Mode(VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    VDP_CSC_MODE_E enCsc2Mode = {0};
    static HI_PQ_HDR_CFG  pstPqHdrCfg;
    static DmCfg_t  pstDmCfg;

    memset((void *)&pstDmCfg, 0, sizeof(pstDmCfg));
    memset((void *)&pstPqHdrCfg, 0, sizeof(pstPqHdrCfg));


    if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709;//VDP_CSC_YUV2RGB_2020_2020_L           ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709; /* YCbCr L      -> YCbCr L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709;//VDP_CSC_YUV2RGB_2020_2020_L           ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709; /* YCbCr L      -> YCbCr L */
    }

    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709 ;
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709 ;
        enCsc2Mode  = VDP_CSC_RGB2RGB;
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_601 ;
    }

    else if (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = VDP_CSC_YUV2RGB_709 ;
    }
    else
    {
        VDP_PRINT("VDP Err csc0 mode in %d out %d!\n", enInClr, enOutClr);
    }

    return HI_SUCCESS;
}


HI_S32 VDP_DRV_GetCsc1Mode(VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    static HI_PQ_HDR_CFG  pstPqHdrCfg;
    static DmCfg_t  pstDmCfg;

    memset((void *)&pstDmCfg, 0, sizeof(pstDmCfg));
    memset((void *)&pstPqHdrCfg, 0, sizeof(pstPqHdrCfg));


   if ((enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020)
      || (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L))
   {
        *enCscMode = VDP_CSC_RGB2RGB             ; /* RGB          -> RGB */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB             ; /* RGB          -> RGB */
   }
    else if ((enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
        ||(enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_YUV_2020))
    {
        *enCscMode = VDP_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709    ; /* RGB          -> YCbCr_709 F */
    }
    else if ((enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
            ||  (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_601))
    {
        *enCscMode = VDP_CSC_RGB2YUV_601         ; /* RGB          -> YCbCr_709 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709         ; /* RGB          -> YCbCr_709 L */
    }
    else if ((enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_709_L)
            || (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_709))
    {
        *enCscMode = VDP_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }
    else
    {
        VDP_PRINT("VDP Err csc1 mode in %d out %d!\n", enInClr, enOutClr);
    }
    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetYuv2RgbCfg(HI_U32 u32LayerId, HI_S16  S16Yuv2Rgb[3][3],
                                       HI_S32 S32Yuv2RgbOutDc[3], HI_S32 S32Yuv2RgbInDc[3])
{
    VDP_VID_SetVdmVdmYuv2rgbscale2p(0, 13);
    VDP_VID_SetVdmVdmYuv2rgbClipMin(0, 0);
    VDP_VID_SetVdmVdmYuv2rgbClipMax(0, 1023);
    //VDP_VID_SetVdmVdmCscEn(VDP_LAYER_VID0, HI_TRUE);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdmV0CscEn  (VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdm00Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][0]);
        VDP_VID_SetVdmVdm01Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][1]);
        VDP_VID_SetVdmVdm02Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][2]);
        VDP_VID_SetVdmVdm03Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][0]);
        VDP_VID_SetVdmVdm04Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][1]);
        VDP_VID_SetVdmVdm05Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][2]);
        VDP_VID_SetVdmVdm06Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][0]);
        VDP_VID_SetVdmVdm07Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][1]);
        VDP_VID_SetVdmVdm08Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][2]);

        VDP_VID_SetVdmVdmYuv2rgb00InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[0]);
        VDP_VID_SetVdmVdmYuv2rgb01InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[1]);
        VDP_VID_SetVdmVdmYuv2rgb02InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[2]);
        VDP_VID_SetVdmVdmYuv2rgb00OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[0]);
        VDP_VID_SetVdmVdmYuv2rgb01OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[1]);
        VDP_VID_SetVdmVdmYuv2rgb02OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[2]);
    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_VID_SetVdmVdmYuv2rgbEn(VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdmV1CscEn  (VDP_LAYER_VP0, 1);
        VDP_VID_SetVdmVdm10Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][0]);
        VDP_VID_SetVdmVdm11Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][1]);
        VDP_VID_SetVdmVdm12Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[0][2]);
        VDP_VID_SetVdmVdm13Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][0]);
        VDP_VID_SetVdmVdm14Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][1]);
        VDP_VID_SetVdmVdm15Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[1][2]);
        VDP_VID_SetVdmVdm16Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][0]);
        VDP_VID_SetVdmVdm17Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][1]);
        VDP_VID_SetVdmVdm18Yuv2rgb(VDP_LAYER_VID0, S16Yuv2Rgb[2][2]);

        VDP_VID_SetVdmVdmYuv2rgb10InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[0]);
        VDP_VID_SetVdmVdmYuv2rgb11InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[1]);
        VDP_VID_SetVdmVdmYuv2rgb12InDc(VDP_LAYER_VID0, S32Yuv2RgbInDc[2]);
        VDP_VID_SetVdmVdmYuv2rgb10OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[0]);
        VDP_VID_SetVdmVdmYuv2rgb11OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[1]);
        VDP_VID_SetVdmVdmYuv2rgb12OutDc(VDP_LAYER_VID0, S32Yuv2RgbOutDc[2]);
    }

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetRgb2YuvCfg(HI_U32 u32LayerId, HI_S16  S16Rgb2Yuv[3][3],
                             HI_S32 S32Rgb2YuvOutDc[3], HI_S32 S32Rgb2YuvInDc[3])
{
    VDP_VID_SetVdmVdmRgb2yuvEn(VDP_LAYER_VID0, HI_TRUE);
    VDP_VID_SetVdmVdm00Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[0][0]);
    VDP_VID_SetVdmVdm01Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[0][1]);
    VDP_VID_SetVdmVdm02Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[0][2]);
    VDP_VID_SetVdmVdm10Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[1][0]);
    VDP_VID_SetVdmVdm11Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[1][1]);
    VDP_VID_SetVdmVdm12Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[1][2]);
    VDP_VID_SetVdmVdm20Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[2][0]);
    VDP_VID_SetVdmVdm21Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[2][1]);
    VDP_VID_SetVdmVdm22Rgb2yuv(VDP_LAYER_VID0, S16Rgb2Yuv[2][2]);
    VDP_VID_SetVdmVdmRgb2yuvscale2p(VDP_LAYER_VID0, 14);
    VDP_VID_SetVdmVdmRgb2yuv0InDc(VDP_LAYER_VID0, S32Rgb2YuvInDc[0]);
    VDP_VID_SetVdmVdmRgb2yuv1InDc(VDP_LAYER_VID0, S32Rgb2YuvInDc[1]);
    VDP_VID_SetVdmVdmRgb2yuv2InDc(VDP_LAYER_VID0, S32Rgb2YuvInDc[2]);
    VDP_VID_SetVdmVdmRgb2yuv0OutDc(VDP_LAYER_VID0, S32Rgb2YuvOutDc[0]);
    VDP_VID_SetVdmVdmRgb2yuv1OutDc(VDP_LAYER_VID0, S32Rgb2YuvOutDc[1]);
    VDP_VID_SetVdmVdmRgb2yuv2OutDc(VDP_LAYER_VID0, S32Rgb2YuvOutDc[2]);
    VDP_VID_SetVdmVdmRgb2yuvClipMin(VDP_LAYER_VID0, 0);
    VDP_VID_SetVdmVdmRgb2yuvClipMax(VDP_LAYER_VID0, 1023);

    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetVdpBkg(HI_U32 u32LayerId, VDP_COLOR_SPACE_INFO_S  *pstColorSpaceInfo)
{

    HI_PQ_CSC_CRTL_S stCscCtrl = {0};
    VDP_CSC_MODE_E enCscMode = {0};

    //VDP_CSC_MODE_E enCsc2Mode = {0};
    HI_PQ_CSC_MODE_E enPqCscMode = {0};

    VDP_CSC_COEF_S     stCscCoef = {0};
    VDP_CSC_DC_COEF_S  stCscDc = {0};
    HI_PQ_CSC_COEF_S   stPqCscCoef = {0};
    HI_PQ_CSC_DCCOEF_S stPqCscDc = {0};
    HI_S16             S16Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32             S32Yuv2RgbOutDc[3] = {0};
    HI_S32             S32Yuv2RgbInDc[3] = {0};
    VDP_CLR_SPACE_E enInClr;
    VDP_CLR_SPACE_E enOutClr;

    enInClr = pstColorSpaceInfo->enInClrSpace;
    enOutClr = pstColorSpaceInfo->enOutClrSpace;

    if (pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_RGB_2020_L
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_RGB_2020
       )
    {
        enInClr  = VDP_CLR_SPACE_YUV_709_L;
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }
    else
    {
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }

    //--------------------csc0 begin--------------------------------------//
    VDP_DRV_GetCsc0Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);

    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);

    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));

    S32Yuv2RgbOutDc[0] =  stPqCscDc.csc_out_dc0;
    S32Yuv2RgbOutDc[1] =  stPqCscDc.csc_out_dc1;
    S32Yuv2RgbOutDc[2] =  stPqCscDc.csc_out_dc2;

    S32Yuv2RgbInDc[0] =  stPqCscDc.csc_in_dc0;
    S32Yuv2RgbInDc[1] =  stPqCscDc.csc_in_dc1;
    S32Yuv2RgbInDc[2] =  stPqCscDc.csc_in_dc2;

    S16Yuv2Rgb[0][0]  = (HI_S16)stPqCscCoef.csc_coef00 * 8;
    S16Yuv2Rgb[0][1]  = (HI_S16)stPqCscCoef.csc_coef01 * 8;
    S16Yuv2Rgb[0][2]  = (HI_S16)stPqCscCoef.csc_coef02 * 8;
    S16Yuv2Rgb[1][0]  = (HI_S16)stPqCscCoef.csc_coef10 * 8;
    S16Yuv2Rgb[1][1]  = (HI_S16)stPqCscCoef.csc_coef11 * 8;
    S16Yuv2Rgb[1][2]  = (HI_S16)stPqCscCoef.csc_coef12 * 8;
    S16Yuv2Rgb[2][0]  = (HI_S16)stPqCscCoef.csc_coef20 * 8;
    S16Yuv2Rgb[2][1]  = (HI_S16)stPqCscCoef.csc_coef21 * 8;
    S16Yuv2Rgb[2][2]  = (HI_S16)stPqCscCoef.csc_coef22 * 8;

    VDP_DRV_SetYuv2RgbCfg(u32LayerId, S16Yuv2Rgb, S32Yuv2RgbOutDc, S32Yuv2RgbInDc);
    //--------------------csc0 end--------------------------------------//


    //--------------------csc1 begin--------------------------------------//
    enInClr  = enOutClr;

    if (pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020
       )
    {
        enOutClr = VDP_CLR_SPACE_YUV_709_L;
    }
    else if (pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
             || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020
            )
    {
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }
    else
    {
        enOutClr = pstColorSpaceInfo->enOutClrSpace;
    }

    VDP_DRV_GetCsc1Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);

    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);


    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));

    S32Yuv2RgbOutDc[0] =  stPqCscDc.csc_out_dc0;
    S32Yuv2RgbOutDc[1] =  stPqCscDc.csc_out_dc1;
    S32Yuv2RgbOutDc[2] =  stPqCscDc.csc_out_dc2;

    S32Yuv2RgbInDc[0] =  stPqCscDc.csc_in_dc0;
    S32Yuv2RgbInDc[1] =  stPqCscDc.csc_in_dc1;
    S32Yuv2RgbInDc[2] =  stPqCscDc.csc_in_dc2;

    S16Yuv2Rgb[0][0]  = (HI_S16)stPqCscCoef.csc_coef00 * 16;
    S16Yuv2Rgb[0][1]  = (HI_S16)stPqCscCoef.csc_coef01 * 16;
    S16Yuv2Rgb[0][2]  = (HI_S16)stPqCscCoef.csc_coef02 * 16;
    S16Yuv2Rgb[1][0]  = (HI_S16)stPqCscCoef.csc_coef10 * 16;
    S16Yuv2Rgb[1][1]  = (HI_S16)stPqCscCoef.csc_coef11 * 16;
    S16Yuv2Rgb[1][2]  = (HI_S16)stPqCscCoef.csc_coef12 * 16;
    S16Yuv2Rgb[2][0]  = (HI_S16)stPqCscCoef.csc_coef20 * 16;
    S16Yuv2Rgb[2][1]  = (HI_S16)stPqCscCoef.csc_coef21 * 16;
    S16Yuv2Rgb[2][2]  = (HI_S16)stPqCscCoef.csc_coef22 * 16;

    VDP_DRV_SetRgb2YuvCfg(u32LayerId, S16Yuv2Rgb, S32Yuv2RgbOutDc, S32Yuv2RgbInDc);
    //--------------------csc1 end--------------------------------------//

    return HI_SUCCESS;
}

HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_VOID)
{
    VDP_BKG_S  stLetterBoxColor = {0};

    stLetterBoxColor.u32BkgA = 0xff;

    stLetterBoxColor.u32BkgY = 0x0;
    stLetterBoxColor.u32BkgU = 0x0;
    stLetterBoxColor.u32BkgV = 0x0;

    VDP_VID_SetLayerBkg(VDP_LAYER_VID0, stLetterBoxColor);

    return;
}

HI_VOID XDP_DRV_JudgeRgbColorSpace(VDP_CLR_SPACE_E enOutClrSpace,HI_BOOL *pbRgbColorSpace)
{
    if (enOutClrSpace == VDP_CLR_SPACE_RGB_601
        || enOutClrSpace == VDP_CLR_SPACE_RGB_709
        || enOutClrSpace == VDP_CLR_SPACE_RGB_2020
        || enOutClrSpace == VDP_CLR_SPACE_RGB_601_L
        || enOutClrSpace == VDP_CLR_SPACE_RGB_709_L
        || enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
       )
    {
        *pbRgbColorSpace = HI_TRUE;
    }
    else
    {
        *pbRgbColorSpace = HI_FALSE;
    }

    return;
}

HI_VOID XDP_DRV_AdjustMixvColor(VDP_BKG_S *pstMixvColor, HI_BOOL bRgbColorSpace)
{
    /* 8bit->10bit */
    pstMixvColor->u32BkgY = pstMixvColor->u32BkgY << 2;
    pstMixvColor->u32BkgU = pstMixvColor->u32BkgU << 2;
    pstMixvColor->u32BkgV = pstMixvColor->u32BkgV << 2;

    return;
}

#endif
