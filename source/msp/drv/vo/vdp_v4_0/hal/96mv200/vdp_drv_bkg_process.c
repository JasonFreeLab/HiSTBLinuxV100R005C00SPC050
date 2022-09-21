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
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_2020_L; /* YCbCr L      -> YCbCr L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709;//VDP_CSC_YUV2RGB_2020_2020_L           ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_2020_L; /* YCbCr L      -> YCbCr L */
    }

    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_709_L ;
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_2020_709_L ;
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
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709_FULL    ; /* RGB          -> YCbCr_709 F */
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

    HI_U32 u32Yuv2RgbScale2p   = 11;
    HI_U32 u32Yuv2RgbClipMin = 16  * 16;
    HI_U32 u32Yuv2RgbClipMax = 235 * 16;

    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_HIHDR_SetVdmV0CscEn  (1);
        VDP_HIHDR_SetVdmY2rEn(1);
        VDP_HIHDR_SetVdm00Yuv2rgb( S16Yuv2Rgb[0][0]);
        VDP_HIHDR_SetVdm01Yuv2rgb( S16Yuv2Rgb[0][1]);
        VDP_HIHDR_SetVdm02Yuv2rgb( S16Yuv2Rgb[0][2]);
        VDP_HIHDR_SetVdm03Yuv2rgb( S16Yuv2Rgb[1][0]);
        VDP_HIHDR_SetVdm04Yuv2rgb( S16Yuv2Rgb[1][1]);
        VDP_HIHDR_SetVdm05Yuv2rgb( S16Yuv2Rgb[1][2]);
        VDP_HIHDR_SetVdm06Yuv2rgb( S16Yuv2Rgb[2][0]);
        VDP_HIHDR_SetVdm07Yuv2rgb( S16Yuv2Rgb[2][1]);
        VDP_HIHDR_SetVdm08Yuv2rgb( S16Yuv2Rgb[2][2]);
        VDP_HIHDR_SetVdmYuv2rgb00InDc( S32Yuv2RgbInDc[0]);
        VDP_HIHDR_SetVdmYuv2rgb01InDc( S32Yuv2RgbInDc[1]);
        VDP_HIHDR_SetVdmYuv2rgb02InDc( S32Yuv2RgbInDc[2]);
        VDP_HIHDR_SetVdmYuv2rgb00OutDc( S32Yuv2RgbOutDc[0]);
        VDP_HIHDR_SetVdmYuv2rgb01OutDc( S32Yuv2RgbOutDc[1]);
        VDP_HIHDR_SetVdmYuv2rgb02OutDc( S32Yuv2RgbOutDc[2]);

        VDP_HIHDR_SetVdmV0Yuv2rgbscale2p(u32Yuv2RgbScale2p);
        VDP_HIHDR_SetVdmV0Yuv2rgbClipMin(u32Yuv2RgbClipMin);
        VDP_HIHDR_SetVdmV0Yuv2rgbClipMax(u32Yuv2RgbClipMax);

    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        //VDP_HIHDR_SetVdmYuv2rgbEn(VDP_LAYER_VP0,1);
        VDP_HIHDR_SetVdmV1CscEn  (1);
        VDP_HIHDR_SetVdmV1CscEn  (1);
        VDP_HIHDR_SetVdm10Yuv2rgb( S16Yuv2Rgb[0][0]);
        VDP_HIHDR_SetVdm11Yuv2rgb( S16Yuv2Rgb[0][1]);
        VDP_HIHDR_SetVdm12Yuv2rgb( S16Yuv2Rgb[0][2]);
        VDP_HIHDR_SetVdm13Yuv2rgb( S16Yuv2Rgb[1][0]);
        VDP_HIHDR_SetVdm14Yuv2rgb( S16Yuv2Rgb[1][1]);
        VDP_HIHDR_SetVdm15Yuv2rgb( S16Yuv2Rgb[1][2]);
        VDP_HIHDR_SetVdm16Yuv2rgb( S16Yuv2Rgb[2][0]);
        VDP_HIHDR_SetVdm17Yuv2rgb( S16Yuv2Rgb[2][1]);
        VDP_HIHDR_SetVdm18Yuv2rgb( S16Yuv2Rgb[2][2]);

        VDP_HIHDR_SetVdmYuv2rgb10InDc( S32Yuv2RgbInDc[0]);
        VDP_HIHDR_SetVdmYuv2rgb11InDc( S32Yuv2RgbInDc[1]);
        VDP_HIHDR_SetVdmYuv2rgb12InDc( S32Yuv2RgbInDc[2]);
        VDP_HIHDR_SetVdmYuv2rgb10OutDc( S32Yuv2RgbOutDc[0]);
        VDP_HIHDR_SetVdmYuv2rgb11OutDc( S32Yuv2RgbOutDc[1]);
        VDP_HIHDR_SetVdmYuv2rgb12OutDc( S32Yuv2RgbOutDc[2]);

        VDP_HIHDR_SetVdmV1Yuv2rgbscale2p(u32Yuv2RgbScale2p);
        VDP_HIHDR_SetVdmV1Yuv2rgbClipMin(u32Yuv2RgbClipMin);
        VDP_HIHDR_SetVdmV1Yuv2rgbClipMax(u32Yuv2RgbClipMax);
    }

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetRgb2YuvCfg(HI_U32 u32LayerId, HI_S16  S16Rgb2Yuv[3][3],
                             HI_S32 S32Rgb2YuvOutDc[3], HI_S32 S32Rgb2YuvInDc[3])
{
    VDP_HIHDR_SetVdmRgb2yuvEn(HI_TRUE);
    VDP_HIHDR_SetVdmR2yPipEn( HI_FALSE);
    VDP_HIHDR_SetVdm00Rgb2yuv( S16Rgb2Yuv[0][0]);
    VDP_HIHDR_SetVdm01Rgb2yuv( S16Rgb2Yuv[0][1]);
    VDP_HIHDR_SetVdm02Rgb2yuv( S16Rgb2Yuv[0][2]);
    VDP_HIHDR_SetVdm10Rgb2yuv( S16Rgb2Yuv[1][0]);
    VDP_HIHDR_SetVdm11Rgb2yuv( S16Rgb2Yuv[1][1]);
    VDP_HIHDR_SetVdm12Rgb2yuv( S16Rgb2Yuv[1][2]);
    VDP_HIHDR_SetVdm20Rgb2yuv( S16Rgb2Yuv[2][0]);
    VDP_HIHDR_SetVdm21Rgb2yuv( S16Rgb2Yuv[2][1]);
    VDP_HIHDR_SetVdm22Rgb2yuv( S16Rgb2Yuv[2][2]);
    VDP_HIHDR_SetVdmRgb2yuvscale2p(14);
    VDP_HIHDR_SetVdmRgb2yuv0InDc( S32Rgb2YuvInDc[0]);
    VDP_HIHDR_SetVdmRgb2yuv1InDc( S32Rgb2YuvInDc[1]);
    VDP_HIHDR_SetVdmRgb2yuv2InDc( S32Rgb2YuvInDc[2]);
    VDP_HIHDR_SetVdmRgb2yuv0OutDc( S32Rgb2YuvOutDc[0]);
    VDP_HIHDR_SetVdmRgb2yuv1OutDc( S32Rgb2YuvOutDc[1]);
    VDP_HIHDR_SetVdmRgb2yuv2OutDc( S32Rgb2YuvOutDc[2]);

    VDP_HIHDR_SetVdmRgb2yuvClipUvMin( 64);
    VDP_HIHDR_SetVdmRgb2yuvClipUvMax( 960);
    VDP_HIHDR_SetVdmRgb2yuvClipYMin( 64);
    VDP_HIHDR_SetVdmRgb2yuvClipYMax( 960);

    return HI_SUCCESS;

}

HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_U32 u32LayerId,HI_BOOL bRgbColorSpace)
{
    VDP_BKG_S  stLetterBoxColor = {0};

    stLetterBoxColor.u32BkgA = 0xff;
    if (bRgbColorSpace)
    {
        stLetterBoxColor.u32BkgY = 0x0;
        stLetterBoxColor.u32BkgU = 0x0;
        stLetterBoxColor.u32BkgV = 0x0;
    }
    else
    {
        stLetterBoxColor.u32BkgY = 0x40;
        stLetterBoxColor.u32BkgU = 0x200;
        stLetterBoxColor.u32BkgV = 0x200;
    }
        VDP_VID_SetLayerBkg(u32LayerId, stLetterBoxColor);
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
    HI_S32 s32Red = 0, s32Y = 0;
    HI_S32 s32Green = 0, s32U = 0;
    HI_S32 s32Blue = 0, s32V = 0;

    s32Red = (HI_S32)pstMixvColor->u32BkgY;
    s32Green = (HI_S32)pstMixvColor->u32BkgU;
    s32Blue = (HI_S32)pstMixvColor->u32BkgV;

    if (bRgbColorSpace)
    {
        //8bit -> 10bit.
        pstMixvColor->u32BkgY = s32Red << 2;
        pstMixvColor->u32BkgU = s32Green << 2;
        pstMixvColor->u32BkgV = s32Blue << 2;
    }
    else
    {
        //change rgb to yuv.
        s32Y = (257 * s32Red  + 504 * s32Green  + 98 * s32Blue ) / 1000 + 16;
        s32U = (-148 * s32Red  - 291 * s32Green  + 439 * s32Blue ) / 1000 + 128;
        s32V = (439 * s32Red  - 368 * s32Green  - 71 * s32Blue ) / 1000 + 128;

        if (s32Y < 16)
        {
            s32Y = 16;
        }

        if (s32Y > 235)
        {
            s32Y = 235;
        }

        if (s32U < 16)
        {
            s32U = 16;
        }

        if (s32U > 240)
        {
            s32U = 240;
        }

        if (s32V < 16)
        {
            s32V = 16;
        }

        if (s32V > 240)
        {
            s32V = 240;
        }

        //8bit -> 10bit.
        pstMixvColor->u32BkgY = (HI_U32)s32Y << 2;
        pstMixvColor->u32BkgU = (HI_U32)s32U << 2;
        pstMixvColor->u32BkgV = (HI_U32)s32V << 2;
    }

    return ;
}
#endif
