#include "vdp_drv_bkg_process.h"
#include "vdp_hal_comm.h"
//#include "vdp_hal_ip_vdm.h"
//#include "VdpHiHDR_cfg.h"
//#include "vdp_drv_ip_vdm.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_func_pq_csc.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "drv_pq_ext.h"

static HI_BOOL gb_v1_enable = HI_FALSE;

HI_S32 VDP_DRV_GetCsc0Mode(VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    VDP_CSC_MODE_E enCsc2Mode = {0};
    static HI_PQ_HDR_CFG  pstPqHdrCfg;

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

    VDP_HDR_SetVDmEn               (HI_TRUE);
    VDP_HDR_SetVDmYuv2rgbEn        (HI_TRUE);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_HDR_SetVDmYuv2rgbV0En      (HI_TRUE);
        VDP_HDR_SetVDmImap0Yuv2rgb     (S16Yuv2Rgb);
        VDP_HDR_SetVDmImapYuv2rgbInDc0  (S32Yuv2RgbInDc);
        VDP_HDR_SetVDmImapYuv2rgbOutDc0  (S32Yuv2RgbOutDc);
    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_HDR_SetVDmYuv2rgbV1En      (HI_TRUE);
        VDP_HDR_SetVDmImap1Yuv2rgb     (S16Yuv2Rgb);
        VDP_HDR_SetVDmImapYuv2rgbOutDc1  (S32Yuv2RgbOutDc);
        VDP_HDR_SetVDmImapYuv2rgbInDc1   (S32Yuv2RgbInDc);
    }

    VDP_HDR_SetVDmImapYuv2rgbscale2p (13);


    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetRgb2YuvCfg(HI_U32 u32LayerId, HI_S16  S16Rgb2Yuv[3][3],
                             HI_S32 S32Rgb2YuvOutDc[3], HI_S32 S32Rgb2YuvInDc[3])
{
#if 1

        VDP_HDR_SetVCvmImapLms2iptscale2p(15 | (1<<5) );
        VDP_HDR_SetVCvmImapLms2ipt       (S16Rgb2Yuv         );
        VDP_HDR_SetVCvmImapLms2iptOutDc  (S32Rgb2YuvOutDc );
        VDP_HDR_SetVDmImapLms2iptmin     (0);
        VDP_HDR_SetVDmImapLms2iptmax     (0x7FFF);
        VDP_HDR_SetVCvmLms2iptEn         ( 1 );
#endif

    return HI_SUCCESS;

}

HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_U32 u32LayerId,HI_BOOL bLayerEnable)
{
    VDP_BKG_S  stLetterBoxColor = {0};

    stLetterBoxColor.u32BkgA = 0xff;

    if (VDP_LAYER_VID0 == u32LayerId)
    {
        if (gb_v1_enable)
        {
            stLetterBoxColor.u32BkgY = 0x40;
            stLetterBoxColor.u32BkgU = 0x200;
            stLetterBoxColor.u32BkgV = 0x200;
        }
        else
        {
            stLetterBoxColor.u32BkgY = 0x0;
            stLetterBoxColor.u32BkgU = 0x0;
            stLetterBoxColor.u32BkgV = 0x0;
        }

        VDP_VID_SetLayerBkg(VDP_LAYER_VID0, stLetterBoxColor);
    }

    if (VDP_LAYER_VID1 == u32LayerId)
    {
        if (bLayerEnable)
        {
            stLetterBoxColor.u32BkgY = 0x40;
            stLetterBoxColor.u32BkgU = 0x200;
            stLetterBoxColor.u32BkgV = 0x200;

            VDP_VID_SetLayerBkg(VDP_LAYER_VID0, stLetterBoxColor);
            gb_v1_enable = HI_TRUE;
        }
        else
        {
            stLetterBoxColor.u32BkgY = 0x0;
            stLetterBoxColor.u32BkgU = 0x0;
            stLetterBoxColor.u32BkgV = 0x0;

            VDP_VID_SetLayerBkg(VDP_LAYER_VID0, stLetterBoxColor);
            gb_v1_enable = HI_FALSE;
        }
    }

    return;
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

    if ((pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020) &&
         ((pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L) ||
        (pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020)))
    {
        enInClr  = VDP_CLR_SPACE_YUV_2020_L;
        enOutClr = VDP_CLR_SPACE_RGB_2020_L;
    }
    else  if ((pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_709_L
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_709
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_709_L
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_709) &&
              ((pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L)||
              (pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020)))
    {
        return HI_SUCCESS;
    }
    else  if ((pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
               || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020) &&
              ((pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_709_L) ||
               (pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_601_L) ))
    {
        //up change can not supported !!!
        return HI_SUCCESS;
    }
    else
    {
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }

    //--------------------csc0 begin--------------------------------------//
    VDP_DRV_GetCsc0Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);

    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.u32CscPre = 12;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;


    if ((pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L
        ||pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L))
    {
        VDP_FUNC_GetCSCCoef(&stCscCtrl, enCscMode, &stPqCscCoef, &stPqCscDc);
    }
    else
    {
        VDP_PQ_SetCSCCoef(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);
    }

    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));


    S16Yuv2Rgb[0][0]  = (HI_S16)stPqCscCoef.csc_coef00 * 8;
    S16Yuv2Rgb[0][1]  = (HI_S16)stPqCscCoef.csc_coef01 * 8;
    S16Yuv2Rgb[0][2]  = (HI_S16)stPqCscCoef.csc_coef02 * 8;
    S16Yuv2Rgb[1][0]  = (HI_S16)stPqCscCoef.csc_coef10 * 8;
    S16Yuv2Rgb[1][1]  = (HI_S16)stPqCscCoef.csc_coef11 * 8;
    S16Yuv2Rgb[1][2]  = (HI_S16)stPqCscCoef.csc_coef12 * 8;
    S16Yuv2Rgb[2][0]  = (HI_S16)stPqCscCoef.csc_coef20 * 8;
    S16Yuv2Rgb[2][1]  = (HI_S16)stPqCscCoef.csc_coef21 * 8;
    S16Yuv2Rgb[2][2]  = (HI_S16)stPqCscCoef.csc_coef22 * 8;


    S32Yuv2RgbOutDc[0] =  -stPqCscDc.csc_out_dc0 * 16 * 1024;
    S32Yuv2RgbOutDc[1] =  -stPqCscDc.csc_out_dc1 * 16 * 1024;
    S32Yuv2RgbOutDc[2] =  -stPqCscDc.csc_out_dc2 * 16 * 1024;

    S32Yuv2RgbInDc[0] =  stPqCscDc.csc_in_dc0 * 16;
    S32Yuv2RgbInDc[1] =  stPqCscDc.csc_in_dc1 * 16;
    S32Yuv2RgbInDc[2] =  stPqCscDc.csc_in_dc2 * 16;


    VDP_DRV_SetYuv2RgbCfg(u32LayerId, S16Yuv2Rgb, S32Yuv2RgbOutDc, S32Yuv2RgbInDc);
    //--------------------csc0 end--------------------------------------//


    //--------------------csc1 begin--------------------------------------//
    enInClr  = enOutClr;
    enOutClr = pstColorSpaceInfo->enOutClrSpace;

    if( enOutClr == VDP_CLR_SPACE_RGB_709_L
        || enOutClr == VDP_CLR_SPACE_RGB_709)
    {
    return HI_SUCCESS;
    }
    VDP_DRV_GetCsc1Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);


    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;

    if ( pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L
         || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L
         || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020)
    {
        VDP_FUNC_GetCSCCoef(&stCscCtrl, enCscMode, &stPqCscCoef, &stPqCscDc);
    }
    else
    {
        VDP_PQ_SetCSCCoef(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);
    }


    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));

    S32Yuv2RgbOutDc[0] =  stPqCscDc.csc_out_dc0* 32;
    S32Yuv2RgbOutDc[1] =  stPqCscDc.csc_out_dc1* 32;
    S32Yuv2RgbOutDc[2] =  stPqCscDc.csc_out_dc2* 32;

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
#endif
