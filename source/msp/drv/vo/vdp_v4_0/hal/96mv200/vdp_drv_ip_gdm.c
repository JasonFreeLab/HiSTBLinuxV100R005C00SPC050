#include "vdp_drv_ip_gdm.h"
//#include <string.h>
#include "vdp_define.h"
#include "vdp_drv_func.h"
#if EDA_TEST
#include <stdio.h>
#endif

GdmCfg_t g_GdmCfg;

HI_VOID VDP_FUNC_SetGdmMode(HI_U32 enLayer, VDP_GP_GDM_MODE_E GdmMode, VDP_GDM_CFG_S * pstCfg)
{
    #if 0
    GdmCfg_t * pstDmCfg;

#if EDA_TEST
    pstCfg->GdmSceneMode                        =  GDM_BUTT;
#endif

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
// 	HI_U32 gdm_para_gmm_addr    =  0;	
// 	HI_U32 gdm_para_tmap_addr    =  0;	
// 	HI_U32 gdm_para_tmap_upd    =  1;	
// 	HI_U32 gdm_para_gmm_upd    =  1;	
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

    pstDmCfg = (GdmCfg_t *)malloc(sizeof(GdmCfg_t));

    pstDmCfg->vdm_en                 = pstCfg->gdm_en          ;
    pstDmCfg->vdm_degmm_en           = pstCfg->gdm_degmm_en    ;   
    pstDmCfg->vdm_csc_en             = pstCfg->gdm_csc_en      ;
    pstDmCfg->vdm_tmap_en            = pstCfg->gdm_tmap_en     ;   
    pstDmCfg->vdm_gmm_en             = pstCfg->gdm_gmm_en      ;   
    pstDmCfg->vdm_dither_en          = pstCfg->gdm_dither_en   ;
    pstDmCfg->vdm_rgb2yuv_en         = pstCfg->gdm_rgb2yuv_en  ;
    //pstDmCfg->gdm_r2y_premult_en     = pstCfg->gdm_r2y_premult_en  ;

    pstDmCfg->stDitherCfg.u32_dither_round        = pstCfg->u32_dither_round       ;// 0:dither, 1:round
    pstDmCfg->stDitherCfg.u32_dither_domain_mode  = pstCfg->u32_dither_domain_mode ;// 1 
    pstDmCfg->stDitherCfg.u32_dither_tap_mode     = pstCfg->u32_dither_tap_mode    ; 
    pstDmCfg->stDitherCfg.u32_dither_round_unlim  = pstCfg->u32_dither_round_unlim ; 
  
    //pstDmCfg->vdm_dither_mode        = 0 ;//12bit->10bit ;
    pstDmCfg->vdm_tmap_in_bdp        = 0 ;//1:20bit for vdm , 0:16bit for gdm

    pstDmCfg->u16ClipMinTM           = 0     ; 
    pstDmCfg->u16ClipMaxTM           = 65535 ; 
    pstDmCfg->u32ClipMinCSC          = 0     ; 
    pstDmCfg->u32ClipMaxCSC          = 65535 ; //16bits
    pstDmCfg->u16ClipMinRGB2YUV      = 0     ; 
    pstDmCfg->u16ClipMaxRGB2YUV      = 1023  ; 

    if(GdmMode == VDP_GP_GDM_TYP)
    {
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;
        
        if(pstCfg->GdmSceneMode == GDM_SDR_IN_HDR10_OUT)
        {
            VDP_PRINT("GdmSceneMode == GDM_SDR_IN_HDR10_OUT\n");
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

            pstDmCfg->s16M33RGB2YUV[0][0]    = 3685 ; //BT2020
            pstDmCfg->s16M33RGB2YUV[0][1]    = 9512 ; 
            pstDmCfg->s16M33RGB2YUV[0][2]    = 832  ; 
            pstDmCfg->s16M33RGB2YUV[1][0]    = -2004; 
            pstDmCfg->s16M33RGB2YUV[1][1]    = -5171; 
            pstDmCfg->s16M33RGB2YUV[1][2]    = 7175 ; 
            pstDmCfg->s16M33RGB2YUV[2][0]    = 7175 ; 
            pstDmCfg->s16M33RGB2YUV[2][1]    = -6598; 
            pstDmCfg->s16M33RGB2YUV[2][2]    = -577 ; 
            pstDmCfg->u16ScaleRGB2YUV        = 14   ; 
            pstDmCfg->s16InOffsetRGB2YUV[0]  = 0    ; 
            pstDmCfg->s16InOffsetRGB2YUV[1]  = 0    ; 
            pstDmCfg->s16InOffsetRGB2YUV[2]  = 0    ; 
            pstDmCfg->s16OutOffsetRGB2YUV[0] = 64   ; 
            pstDmCfg->s16OutOffsetRGB2YUV[1] = 512  ; 
            pstDmCfg->s16OutOffsetRGB2YUV[2] = 512  ; 
        }
        else if(pstCfg->GdmSceneMode == GDM_SDR_IN_BBC_OUT)
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
        else if(pstCfg->GdmSceneMode == GDM_SDR_PREMULT)
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
        else if(pstCfg->GdmSceneMode == GDM_709_IN_BT2020_OUT)
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
        else if(pstCfg->GdmSceneMode == GDM_BYPASS_MODE)
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
    }
    else if(GdmMode == VDP_GP_GDM_TYP1)
    {
        VDP_PRINT("VDP_FUNC_SetGdmMode enter into typ1 mode\n");
        //typ1 mode
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;

        pstDmCfg->u16M3LumaCal[0]        = 1076  ; 
        pstDmCfg->u16M3LumaCal[1]        = 2777  ; 
        pstDmCfg->u16M3LumaCal[2]        = 243   ; 
        pstDmCfg->u16ScaleLumaCal        = 12    ; 
        pstDmCfg->u16ScaleCoefTM         = 8     ; 
        pstDmCfg->u16ClipMinTM           = 1024  ; //2^(16-6)
        pstDmCfg->u16ClipMaxTM           = 4096  ; //2^(16-4)

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
        pstDmCfg->u32ClipMinCSC          = 1024  ; //2^(16-6)
        pstDmCfg->u32ClipMaxCSC          = 4096  ; //2^(16-4)

        // dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 32767 ; 
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 255 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2140000000;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2140000000 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2140000000 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2140000000 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 1500000000;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 1500000000 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 1500000000 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 1500000000 ; 

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
        pstDmCfg->u16ClipMinRGB2YUV      = 16    ; //2^(10-6)
        pstDmCfg->u16ClipMaxRGB2YUV      = 256   ; //2^(10-2) 

    }
	else if(GdmMode == VDP_GP_GDM_ZERO)
    {
		VDP_PRINT("VDP_FUNC_SetGdmMode enter into zero mode\n");
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;
		//zero mode
        pstDmCfg->u16M3LumaCal[0]                = 0    ; 
        pstDmCfg->u16M3LumaCal[1]                = 0    ; 
        pstDmCfg->u16M3LumaCal[2]                = 0    ; 
        pstDmCfg->u16ScaleLumaCal                = 1    ; 
        pstDmCfg->u16ScaleCoefTM                 = 1    ; 
//         pstDmCfg->u16ClipMinTM                   = sGetRandEx( 0  , 65534)   ; 
//         pstDmCfg->u16ClipMaxTM                   = sGetRandEx( pstDmCfg->u16ClipMinTM+1, 65535)   ; 

        pstDmCfg->DePQPara.gmm_x1_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x2_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x3_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x4_step           = 5   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x1_pos            = 672 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x2_pos            = 832 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x3_pos            = 992 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x1_num            = 42  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x2_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x3_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x4_num            = 1   ;//sGetRandEx( 0  , 63  )    ; 

        pstDmCfg->TMPara.gmm_x1_step             = 9    ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x2_step             = 10   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x3_step             = 12   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x4_step             = 13   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x1_pos              = 8192 ;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x2_pos              = 16384;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x3_pos              = 24576;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x4_pos              = 65535;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x1_num              = 16   ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x2_num              = 8    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x3_num              = 2    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x4_num              = 5    ;//sGetRandEx( 0  , 31  )    ; 

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ; //sGetRandEx( 0  , 15  )    ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ; 
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ; 
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ; 
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ; 
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ; 
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ; 
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ; 
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ; //sGetRandEx( 0  , 65535 )  ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ; 
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ; 
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ; 
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ; 
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ; 
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ; 
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ; 
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ; //sGetRandEx( 0  , 63  )    ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ; 
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ; 
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ; 
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ; 
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ; 
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ; 
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ; 


        pstDmCfg->s16M33Src2Disp[0][0]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[0][1]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[0][2]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[1][0]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[1][1]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[1][2]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[2][0]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[2][1]           = 0    ; 
        pstDmCfg->s16M33Src2Disp[2][2]           = 0    ; 
        pstDmCfg->u16ScaleSrc2Disp               = 1    ; 
//         pstDmCfg->u32ClipMinCSC                  = sGetRandEx( 0  , 65534 )    ; 
//         pstDmCfg->u32ClipMaxCSC                  = sGetRandEx( pstDmCfg->u32ClipMinCSC+1, 65535)    ; //16bits

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 0;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 0;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 0 ; 

        pstDmCfg->s16M33RGB2YUV[0][0]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[0][1]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[0][2]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[1][0]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[1][1]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[1][2]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[2][0]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[2][1]            = 0    ; 
        pstDmCfg->s16M33RGB2YUV[2][2]            = 0    ; 
        pstDmCfg->u16ScaleRGB2YUV                = 8    ; 
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0    ; 
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0    ; 
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 0    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 0    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 0    ; 
//         pstDmCfg->u16ClipMinRGB2YUV              = sGetRandEx( 0  , 1022 )    ; 
//         pstDmCfg->u16ClipMaxRGB2YUV              = sGetRandEx( pstDmCfg->u16ClipMinRGB2YUV+1,1023 ); 
    }
	else if(GdmMode == VDP_GP_GDM_RAND)
    {
		VDP_PRINT("VDP_FUNC_SetGdmMode enter into rand mode\n");
        //rand mode
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;
        pstDmCfg->u16M3LumaCal[0]                = sGetRandEx( 0  , 4095)    ; 
        pstDmCfg->u16M3LumaCal[1]                = sGetRandEx( 0  , 4095)    ; 
        pstDmCfg->u16M3LumaCal[2]                = sGetRandEx( 0  , 4095)    ; 
        pstDmCfg->u16ScaleLumaCal                = sGetRandEx( 1  , 15  )    ; 
        pstDmCfg->u16ScaleCoefTM                 = sGetRandEx( 1  , 15  )    ; 
//         pstDmCfg->u16ClipMinTM                   = sGetRandEx( 0  , 65533)   ; 
//         pstDmCfg->u16ClipMaxTM                   = sGetRandEx( pstDmCfg->u16ClipMinTM+1, 65535)   ; 

        pstDmCfg->DePQPara.gmm_x1_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x2_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x3_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x4_step           = 5   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x1_pos            = 672 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x2_pos            = 832 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x3_pos            = 992 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x1_num            = 42  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x2_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x3_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x4_num            = 1   ;//sGetRandEx( 0  , 63  )    ; 

        pstDmCfg->TMPara.gmm_x1_step             = 9    ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x2_step             = 10   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x3_step             = 12   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x4_step             = 13   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x1_pos              = 8192 ;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x2_pos              = 16384;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x3_pos              = 24576;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x4_pos              = 65535;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x1_num              = 16   ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x2_num              = 8    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x3_num              = 2    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x4_num              = 5    ;//sGetRandEx( 0  , 31  )    ; 

        pstDmCfg->GammaPara.gmm_x1_step          = 0     ; //sGetRandEx( 0  , 15  )    ;
        pstDmCfg->GammaPara.gmm_x2_step          = 2     ; 
        pstDmCfg->GammaPara.gmm_x3_step          = 4     ; 
        pstDmCfg->GammaPara.gmm_x4_step          = 5     ; 
        pstDmCfg->GammaPara.gmm_x5_step          = 6     ; 
        pstDmCfg->GammaPara.gmm_x6_step          = 8     ; 
        pstDmCfg->GammaPara.gmm_x7_step          = 10    ; 
        pstDmCfg->GammaPara.gmm_x8_step          = 12    ; 
        pstDmCfg->GammaPara.gmm_x1_pos           = 4     ; //sGetRandEx( 0  , 65535 )  ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 32    ; 
        pstDmCfg->GammaPara.gmm_x3_pos           = 64    ; 
        pstDmCfg->GammaPara.gmm_x4_pos           = 192   ; 
        pstDmCfg->GammaPara.gmm_x5_pos           = 512   ; 
        pstDmCfg->GammaPara.gmm_x6_pos           = 4096  ; 
        pstDmCfg->GammaPara.gmm_x7_pos           = 20480 ; 
        pstDmCfg->GammaPara.gmm_x8_pos           = 65535 ; 
        pstDmCfg->GammaPara.gmm_x1_num           = 4     ; //sGetRandEx( 0  , 63  )    ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11    ; 
        pstDmCfg->GammaPara.gmm_x3_num           = 13    ; 
        pstDmCfg->GammaPara.gmm_x4_num           = 17    ; 
        pstDmCfg->GammaPara.gmm_x5_num           = 22    ; 
        pstDmCfg->GammaPara.gmm_x6_num           = 36    ; 
        pstDmCfg->GammaPara.gmm_x7_num           = 52    ; 
        pstDmCfg->GammaPara.gmm_x8_num           = 63    ; 


        pstDmCfg->s16M33Src2Disp[0][0]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[0][1]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[0][2]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[1][0]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[1][1]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[1][2]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[2][0]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[2][1]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33Src2Disp[2][2]           = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->u16ScaleSrc2Disp               = sGetRandEx( 1  , 15  )    ; 
//         pstDmCfg->u32ClipMinCSC                  = sGetRandEx( 0  , 65533 )    ; 
//         pstDmCfg->u32ClipMaxCSC                  = sGetRandEx( pstDmCfg->u32ClipMinCSC+1, 65535)    ; //16bits

        // dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = sGetRandEx( 0,65533 ) ; 
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = sGetRandEx( pstDmCfg->stDitherCfg.u32_dither_thr_min,65535 ) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = sGetRandEx( 0,2147483647) ;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = sGetRandEx( 0,2147483647) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = sGetRandEx( 0,2147483647) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = sGetRandEx( 0,2147483647) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = sGetRandEx( 0,2147483647) ;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = sGetRandEx( 0,2147483647) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = sGetRandEx( 0,2147483647) ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = sGetRandEx( 0,2147483647) ; 

        pstDmCfg->s16M33RGB2YUV[0][0]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[0][1]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[0][2]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[1][0]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[1][1]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[1][2]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[2][0]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[2][1]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->s16M33RGB2YUV[2][2]            = sGetRandEx( -32768, 32767)    ; 
        pstDmCfg->u16ScaleRGB2YUV                = sGetRandEx( 8, 15  )    ; 
        pstDmCfg->s16InOffsetRGB2YUV[0]          = sGetRandEx( -1024, 1023 )    ; 
        pstDmCfg->s16InOffsetRGB2YUV[1]          = sGetRandEx( -1024, 1023 )    ; 
        pstDmCfg->s16InOffsetRGB2YUV[2]          = sGetRandEx( -1024, 1023 )    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = sGetRandEx( -1024, 1023 )    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = sGetRandEx( -1024, 1023 )    ; 
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = sGetRandEx( -1024, 1023 )    ; 
//         pstDmCfg->u16ClipMinRGB2YUV              = sGetRandEx( 0  , 1022 )    ; 
//         pstDmCfg->u16ClipMaxRGB2YUV              = sGetRandEx( pstDmCfg->u16ClipMinRGB2YUV+1,1023 ); 
    }
	else if(GdmMode == VDP_GP_GDM_MIN)
    {
		VDP_PRINT("VDP_FUNC_SetGdmMode enter into min mode\n");
		//min mode
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;
        pstDmCfg->u16M3LumaCal[0]                = 0    ; 
        pstDmCfg->u16M3LumaCal[1]                = 0    ; 
        pstDmCfg->u16M3LumaCal[2]                = 0    ; 
        pstDmCfg->u16ScaleLumaCal                = 1    ; 
        pstDmCfg->u16ScaleCoefTM                 = 1    ; 
//         pstDmCfg->u16ClipMinTM                   = sGetRandEx( 0  , 65533)   ; 
//         pstDmCfg->u16ClipMaxTM                   = sGetRandEx( pstDmCfg->u16ClipMinTM+1, 65535)   ; 

        pstDmCfg->DePQPara.gmm_x1_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x2_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x3_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x4_step           = 5   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x1_pos            = 672 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x2_pos            = 832 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x3_pos            = 992 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x1_num            = 42  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x2_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x3_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x4_num            = 1   ;//sGetRandEx( 0  , 63  )    ; 

        pstDmCfg->TMPara.gmm_x1_step             = 9    ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x2_step             = 10   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x3_step             = 12   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x4_step             = 13   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x1_pos              = 8192 ;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x2_pos              = 16384;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x3_pos              = 24576;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x4_pos              = 65535;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x1_num              = 16   ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x2_num              = 8    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x3_num              = 2    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x4_num              = 5    ;//sGetRandEx( 0  , 31  )    ; 

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


        pstDmCfg->s16M33Src2Disp[0][0]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[0][1]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[0][2]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[1][0]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[1][1]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[1][2]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[2][0]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[2][1]           = -32768   ; 
        pstDmCfg->s16M33Src2Disp[2][2]           = -32768   ; 
        pstDmCfg->u16ScaleSrc2Disp               = 1        ; 
//         pstDmCfg->u32ClipMinCSC                  = sGetRandEx( 0  , 65533 )    ; 
//         pstDmCfg->u32ClipMaxCSC                  = sGetRandEx( pstDmCfg->u32ClipMinCSC+1, 65535)    ; //16bits

        // dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 1 ; 
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 0 ;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 0 ;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 0 ; 

        pstDmCfg->s16M33RGB2YUV[0][0]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[0][1]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[0][2]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[1][0]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[1][1]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[1][2]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[2][0]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[2][1]            = -32768    ; 
        pstDmCfg->s16M33RGB2YUV[2][2]            = -32768    ; 
        pstDmCfg->u16ScaleRGB2YUV                = 8         ; 
        pstDmCfg->s16InOffsetRGB2YUV[0]          = -1024     ; 
        pstDmCfg->s16InOffsetRGB2YUV[1]          = -1024     ; 
        pstDmCfg->s16InOffsetRGB2YUV[2]          = -1024     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = -1024     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = -1024     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = -1024     ; 
//         pstDmCfg->u16ClipMinRGB2YUV              = sGetRandEx( 0  , 1021 )    ; 
//         pstDmCfg->u16ClipMaxRGB2YUV              = sGetRandEx( pstDmCfg->u16ClipMinRGB2YUV+1,1023 ); 
    }
	else if(GdmMode == VDP_GP_GDM_MAX)
    {
		VDP_PRINT("VDP_FUNC_SetGdmMode enter into max mode\n");
		//max mode
        pstDmCfg->GdmSceneMode                        = pstCfg->GdmSceneMode ;
        pstDmCfg->u16M3LumaCal[0]                = 4095    ; 
        pstDmCfg->u16M3LumaCal[1]                = 4095    ; 
        pstDmCfg->u16M3LumaCal[2]                = 4095    ; 
        pstDmCfg->u16ScaleLumaCal                = 15      ; 
        pstDmCfg->u16ScaleCoefTM                 = 15      ; 
//         pstDmCfg->u16ClipMinTM                   = sGetRandEx( 0  , 65533)   ; 
//         pstDmCfg->u16ClipMaxTM                   = sGetRandEx( pstDmCfg->u16ClipMinTM+1, 65535)   ; 

        pstDmCfg->DePQPara.gmm_x1_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x2_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x3_step           = 4   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x4_step           = 5   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->DePQPara.gmm_x1_pos            = 672 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x2_pos            = 832 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x3_pos            = 992 ;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x4_pos            = 1023;//sGetRandEx( 0  , 1023)    ; 
        pstDmCfg->DePQPara.gmm_x1_num            = 42  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x2_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x3_num            = 10  ;//sGetRandEx( 0  , 63  )    ; 
        pstDmCfg->DePQPara.gmm_x4_num            = 1   ;//sGetRandEx( 0  , 63  )    ; 

        pstDmCfg->TMPara.gmm_x1_step             = 9    ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x2_step             = 10   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x3_step             = 12   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x4_step             = 13   ;//sGetRandEx( 0  , 15  )    ; 
        pstDmCfg->TMPara.gmm_x1_pos              = 8192 ;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x2_pos              = 16384;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x3_pos              = 24576;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x4_pos              = 65535;//sGetRandEx( 0  , 65535)   ; 
        pstDmCfg->TMPara.gmm_x1_num              = 16   ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x2_num              = 8    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x3_num              = 2    ;//sGetRandEx( 0  , 31  )    ; 
        pstDmCfg->TMPara.gmm_x4_num              = 5    ;//sGetRandEx( 0  , 31  )    ; 

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


        pstDmCfg->s16M33Src2Disp[0][0]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[0][1]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[0][2]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[1][0]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[1][1]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[1][2]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[2][0]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[2][1]           = 32767    ; 
        pstDmCfg->s16M33Src2Disp[2][2]           = 32767    ; 
        pstDmCfg->u16ScaleSrc2Disp               = 15       ; 
//         pstDmCfg->u32ClipMinCSC                  = sGetRandEx( 0  , 65533 )    ; 
//         pstDmCfg->u32ClipMaxCSC                  = sGetRandEx( pstDmCfg->u32ClipMinCSC+1, 65535)    ; //16bits

        //dither cfg
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = 65535 ; 
        pstDmCfg->stDitherCfg.u32_dither_thr_min      = 0 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = 2147483647;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = 2147483647 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = 2147483647 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = 2147483647 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = 2147483647;//31'h7fffffff; 
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = 2147483647 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = 2147483647 ; 
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = 2147483647 ; 

        pstDmCfg->s16M33RGB2YUV[0][0]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[0][1]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[0][2]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[1][0]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[1][1]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[1][2]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[2][0]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[2][1]            = 32767    ; 
        pstDmCfg->s16M33RGB2YUV[2][2]            = 32767    ; 
        pstDmCfg->u16ScaleRGB2YUV                = 15       ; 
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 1023     ; 
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 1023     ; 
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 1023     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 1023     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 1023     ; 
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 1023     ; 
//         pstDmCfg->u16ClipMinRGB2YUV              = sGetRandEx( 0  , 1021 )    ; 
//         pstDmCfg->u16ClipMaxRGB2YUV              = sGetRandEx( pstDmCfg->u16ClipMinRGB2YUV+1,1023 ); 
    }
   
//     pstDmCfg->stDitherCfg.u32_dither_sed_y1       = pstDmCfg->stDitherCfg.u32_dither_sed_y0 ; 
//     pstDmCfg->stDitherCfg.u32_dither_sed_u1       = pstDmCfg->stDitherCfg.u32_dither_sed_u0 ; 
//     pstDmCfg->stDitherCfg.u32_dither_sed_v1       = pstDmCfg->stDitherCfg.u32_dither_sed_v0 ; 
//     pstDmCfg->stDitherCfg.u32_dither_sed_w1       = pstDmCfg->stDitherCfg.u32_dither_sed_w0 ; 

    //------------------------
    // adapter
    //------------------------

#ifdef VDP_LP_MODE
    pstDmCfg->stDitherCfg.u32_dither_round  = 1; 
#endif

    memcpy(&g_GdmCfg, pstDmCfg, sizeof(GdmCfg_t));

    g_GdmCfg.DePQPara.gmm_lut = (HI_U32 *)malloc(sizeof(HI_U32)*64);
    g_GdmCfg.TMPara.gmm_lut = (HI_U32 *)malloc(sizeof(HI_U32)*32);
    g_GdmCfg.GammaPara.gmm_lut = (HI_U32 *)malloc(sizeof(HI_U32)*64);

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
		cout << "================ reg_value print begin ================" << endl ;
		cout << "gdm_tmap_in_bdp = "                 << dec    << gdm_tmap_in_bdp        << endl;
		cout << "gdm_gmm_en = "                      << dec    << gdm_gmm_en             << endl;
		cout << "gdm_tmap_en = "                     << dec    << gdm_tmap_en            << endl;
		cout << "gdm_degmm_en = "                    << dec    << gdm_degmm_en           << endl;
		cout << "gdm_en = "                          << dec    << gdm_en                 << endl;
		cout << "gdm_luma_coef0_tmap = "             << dec    << gdm_luma_coef0_tmap    << endl;
		cout << "gdm_luma_coef1_tmap = "             << dec    << gdm_luma_coef1_tmap    << endl;
		cout << "gdm_luma_coef2_tmap = "             << dec    << gdm_luma_coef2_tmap    << endl;
		cout << "gdm_tmap_luma_scale = "             << dec    << gdm_tmap_luma_scale    << endl;
		cout << "gdm_tmap_coef_scale = "             << dec    << gdm_tmap_coef_scale    << endl;
		cout << "gdm_tmap_out_clip_min = "           << dec    << gdm_tmap_out_clip_min  << endl;
		cout << "gdm_tmap_out_clip_max = "           << dec    << gdm_tmap_out_clip_max  << endl;
		cout << "g_degmm_x4_step = "                 << dec    << g_degmm_x4_step        << endl;
		cout << "g_degmm_x3_step = "                 << dec    << g_degmm_x3_step        << endl;
		cout << "g_degmm_x2_step = "                 << dec    << g_degmm_x2_step        << endl;
		cout << "g_degmm_x1_step = "                 << dec    << g_degmm_x1_step        << endl;
		cout << "g_degmm_x2_pos = "                  << dec    << g_degmm_x2_pos         << endl;
		cout << "g_degmm_x1_pos = "                  << dec    << g_degmm_x1_pos         << endl;
		cout << "g_degmm_x4_pos = "                  << dec    << g_degmm_x4_pos         << endl;
		cout << "g_degmm_x3_pos = "                  << dec    << g_degmm_x3_pos         << endl;
		cout << "g_degmm_x4_num = "                  << dec    << g_degmm_x4_num         << endl;
		cout << "g_degmm_x3_num = "                  << dec    << g_degmm_x3_num         << endl;
		cout << "g_degmm_x2_num = "                  << dec    << g_degmm_x2_num         << endl;
		cout << "g_degmm_x1_num = "                  << dec    << g_degmm_x1_num         << endl;
		cout << "g_tmap_x4_step = "                  << dec    << g_tmap_x4_step         << endl;
		cout << "g_tmap_x3_step = "                  << dec    << g_tmap_x3_step         << endl;
		cout << "g_tmap_x2_step = "                  << dec    << g_tmap_x2_step         << endl;
		cout << "g_tmap_x1_step = "                  << dec    << g_tmap_x1_step         << endl;
		cout << "g_tmap_x1_pos = "                   << dec    << g_tmap_x1_pos          << endl;
		cout << "g_tmap_x2_pos = "                   << dec    << g_tmap_x2_pos          << endl;
		cout << "g_tmap_x4_num = "                   << dec    << g_tmap_x4_num          << endl;
		cout << "g_tmap_x3_num = "                   << dec    << g_tmap_x3_num          << endl;
		cout << "g_tmap_x2_num = "                   << dec    << g_tmap_x2_num          << endl;
		cout << "g_tmap_x1_num = "                   << dec    << g_tmap_x1_num          << endl;
		cout << "g_tmap_x3_pos = "                   << dec    << g_tmap_x3_pos          << endl;
		cout << "g_tmap_x4_pos = "                   << dec    << g_tmap_x4_pos          << endl;
		cout << "g_gmm_x1_step = "                   << dec    << g_gmm_x1_step          << endl;
		cout << "g_gmm_x2_step = "                   << dec    << g_gmm_x2_step          << endl;
		cout << "g_gmm_x3_step = "                   << dec    << g_gmm_x3_step          << endl;
		cout << "g_gmm_x4_step = "                   << dec    << g_gmm_x4_step          << endl;
		cout << "g_gmm_x5_step = "                   << dec    << g_gmm_x5_step          << endl;
		cout << "g_gmm_x6_step = "                   << dec    << g_gmm_x6_step          << endl;
		cout << "g_gmm_x7_step = "                   << dec    << g_gmm_x7_step          << endl;
		cout << "g_gmm_x8_step = "                   << dec    << g_gmm_x8_step          << endl;
		cout << "g_gmm_x1_pos = "                    << dec    << g_gmm_x1_pos           << endl;
		cout << "g_gmm_x2_pos = "                    << dec    << g_gmm_x2_pos           << endl;
		cout << "g_gmm_x3_pos = "                    << dec    << g_gmm_x3_pos           << endl;
		cout << "g_gmm_x4_pos = "                    << dec    << g_gmm_x4_pos           << endl;
		cout << "g_gmm_x5_pos = "                    << dec    << g_gmm_x5_pos           << endl;
		cout << "g_gmm_x6_pos = "                    << dec    << g_gmm_x6_pos           << endl;
		cout << "g_gmm_x7_pos = "                    << dec    << g_gmm_x7_pos           << endl;
		cout << "g_gmm_x8_pos = "                    << dec    << g_gmm_x8_pos           << endl;
		cout << "g_gmm_x1_num = "                    << dec    << g_gmm_x1_num           << endl;
		cout << "g_gmm_x2_num = "                    << dec    << g_gmm_x2_num           << endl;
		cout << "g_gmm_x3_num = "                    << dec    << g_gmm_x3_num           << endl;
		cout << "g_gmm_x4_num = "                    << dec    << g_gmm_x4_num           << endl;
		cout << "g_gmm_x5_num = "                    << dec    << g_gmm_x5_num           << endl;
		cout << "g_gmm_x6_num = "                    << dec    << g_gmm_x6_num           << endl;
		cout << "g_gmm_x7_num = "                    << dec    << g_gmm_x7_num           << endl;
		cout << "g_gmm_x8_num = "                    << dec    << g_gmm_x8_num           << endl;
		cout << "gdm_csc_en = "                      << dec    << gdm_csc_en             << endl;
		cout << "gdm_coef00_csc = "                  << dec    << gdm_coef00_csc         << endl;
		cout << "gdm_coef01_csc = "                  << dec    << gdm_coef01_csc         << endl;
		cout << "gdm_coef02_csc = "                  << dec    << gdm_coef02_csc         << endl;
		cout << "gdm_coef10_csc = "                  << dec    << gdm_coef10_csc         << endl;
		cout << "gdm_coef11_csc = "                  << dec    << gdm_coef11_csc         << endl;
		cout << "gdm_coef12_csc = "                  << dec    << gdm_coef12_csc         << endl;
		cout << "gdm_coef20_csc = "                  << dec    << gdm_coef20_csc         << endl;
		cout << "gdm_coef21_csc = "                  << dec    << gdm_coef21_csc         << endl;
		cout << "gdm_coef22_csc = "                  << dec    << gdm_coef22_csc         << endl;
		cout << "gdm_csc_scale = "                   << dec    << gdm_csc_scale          << endl;
		cout << "gdm_csc_clip_min = "                << dec    << gdm_csc_clip_min       << endl;
		cout << "gdm_csc_clip_max = "                << dec    << gdm_csc_clip_max       << endl;
		cout << "gdm_rgb2yuv_en = "                  << dec    << gdm_rgb2yuv_en         << endl;
		cout << "gdm_00_rgb2yuv = "                  << dec    << gdm_00_rgb2yuv         << endl;
		cout << "gdm_01_rgb2yuv = "                  << dec    << gdm_01_rgb2yuv         << endl;
		cout << "gdm_02_rgb2yuv = "                  << dec    << gdm_02_rgb2yuv         << endl;
		cout << "gdm_10_rgb2yuv = "                  << dec    << gdm_10_rgb2yuv         << endl;
		cout << "gdm_11_rgb2yuv = "                  << dec    << gdm_11_rgb2yuv         << endl;
		cout << "gdm_12_rgb2yuv = "                  << dec    << gdm_12_rgb2yuv         << endl;
		cout << "gdm_20_rgb2yuv = "                  << dec    << gdm_20_rgb2yuv         << endl;
		cout << "gdm_21_rgb2yuv = "                  << dec    << gdm_21_rgb2yuv         << endl;
		cout << "gdm_22_rgb2yuv = "                  << dec    << gdm_22_rgb2yuv         << endl;
		cout << "gdm_rgb2yuvscale2p = "              << dec    << gdm_rgb2yuvscale2p     << endl;
		cout << "gdm_rgb2yuv_0_in_dc = "             << dec    << gdm_rgb2yuv_0_in_dc    << endl;
		cout << "gdm_rgb2yuv_1_in_dc = "             << dec    << gdm_rgb2yuv_1_in_dc    << endl;
		cout << "gdm_rgb2yuv_2_in_dc = "             << dec    << gdm_rgb2yuv_2_in_dc    << endl;
		cout << "gdm_rgb2yuv_0_out_dc = "            << dec    << gdm_rgb2yuv_0_out_dc   << endl;
		cout << "gdm_rgb2yuv_1_out_dc = "            << dec    << gdm_rgb2yuv_1_out_dc   << endl;
		cout << "gdm_rgb2yuv_2_out_dc = "            << dec    << gdm_rgb2yuv_2_out_dc   << endl;
		cout << "gdm_rgb2yuv_clip_min = "            << dec    << gdm_rgb2yuv_clip_min   << endl;
		cout << "gdm_rgb2yuv_clip_max = "            << dec    << gdm_rgb2yuv_clip_max   << endl;
		cout << "gdm_dither_round_unlim = "          << dec    << gdm_dither_round_unlim << endl;
		cout << "gdm_dither_en = "                   << dec    << gdm_dither_en          << endl;
		cout << "gdm_dither_mode = "                 << dec    << gdm_dither_mode        << endl;
		cout << "gdm_dither_round = "                << dec    << gdm_dither_round       << endl;
		cout << "gdm_dither_domain_mode = "          << dec    << gdm_dither_domain_mode << endl;
		cout << "gdm_dither_tap_mode = "             << dec    << gdm_dither_tap_mode    << endl;
		cout << "gdm_dither_sed_y0 = "               << dec    << gdm_dither_sed_y0      << endl;
		cout << "gdm_dither_sed_u0 = "               << dec    << gdm_dither_sed_u0      << endl;
		cout << "gdm_dither_sed_v0 = "               << dec    << gdm_dither_sed_v0      << endl;
		cout << "gdm_dither_sed_w0 = "               << dec    << gdm_dither_sed_w0      << endl;
		cout << "gdm_dither_sed_y1 = "               << dec    << gdm_dither_sed_y1      << endl;
		cout << "gdm_dither_sed_u1 = "               << dec    << gdm_dither_sed_u1      << endl;
		cout << "gdm_dither_sed_v1 = "               << dec    << gdm_dither_sed_v1      << endl;
		cout << "gdm_dither_sed_w1 = "               << dec    << gdm_dither_sed_w1      << endl;
		cout << "gdm_dither_sed_y2 = "               << dec    << gdm_dither_sed_y2      << endl;
		cout << "gdm_dither_sed_u2 = "               << dec    << gdm_dither_sed_u2      << endl;
		cout << "gdm_dither_sed_v2 = "               << dec    << gdm_dither_sed_v2      << endl;
		cout << "gdm_dither_sed_w2 = "               << dec    << gdm_dither_sed_w2      << endl;
		cout << "gdm_dither_sed_y3 = "               << dec    << gdm_dither_sed_y3      << endl;
		cout << "gdm_dither_sed_u3 = "               << dec    << gdm_dither_sed_u3      << endl;
		cout << "gdm_dither_sed_v3 = "               << dec    << gdm_dither_sed_v3      << endl;
		cout << "gdm_dither_sed_w3 = "               << dec    << gdm_dither_sed_w3      << endl;
		cout << "gdm_dither_thr_max = "              << dec    << gdm_dither_thr_max     << endl;
		cout << "gdm_dither_thr_min = "              << dec    << gdm_dither_thr_min     << endl;
		cout << "================ reg_value print end ================"   << endl ;
#endif


#if 0	
    //reg value print
    VDP_PRINT("gdm_tmap_in_bdp = %d \n",gdm_tmap_in_bdp);	
    VDP_PRINT("gdm_gmm_en = %d \n",gdm_gmm_en);	
    VDP_PRINT("gdm_tmap_en = %d \n",gdm_tmap_en);	
    VDP_PRINT("gdm_degmm_en = %d \n",gdm_degmm_en);	
    VDP_PRINT("gdm_en = %d \n",gdm_en);	
    VDP_PRINT("gdm_luma_coef0_tmap = %d \n",gdm_luma_coef0_tmap);	
    VDP_PRINT("gdm_luma_coef1_tmap = %d \n",gdm_luma_coef1_tmap);	
    VDP_PRINT("gdm_luma_coef2_tmap = %d \n",gdm_luma_coef2_tmap);	
    VDP_PRINT("gdm_tmap_luma_scale = %d \n",gdm_tmap_luma_scale);	
    VDP_PRINT("gdm_tmap_coef_scale = %d \n",gdm_tmap_coef_scale);	
    VDP_PRINT("gdm_tmap_out_clip_min = %d \n",gdm_tmap_out_clip_min);	
    VDP_PRINT("gdm_tmap_out_clip_max = %d \n",gdm_tmap_out_clip_max);	
    VDP_PRINT("gdm_para_gmm_addr = %d \n",gdm_para_gmm_addr);	
    VDP_PRINT("gdm_para_tmap_addr = %d \n",gdm_para_tmap_addr);	
    VDP_PRINT("gdm_para_tmap_upd = %d \n",gdm_para_tmap_upd);	
    VDP_PRINT("gdm_para_gmm_upd = %d \n",gdm_para_gmm_upd);	
    VDP_PRINT("g_degmm_x4_step = %d \n",g_degmm_x4_step);	
    VDP_PRINT("g_degmm_x3_step = %d \n",g_degmm_x3_step);	
    VDP_PRINT("g_degmm_x2_step = %d \n",g_degmm_x2_step);	
    VDP_PRINT("g_degmm_x1_step = %d \n",g_degmm_x1_step);	
    VDP_PRINT("g_degmm_x2_pos = %d \n",g_degmm_x2_pos);	
    VDP_PRINT("g_degmm_x1_pos = %d \n",g_degmm_x1_pos);	
    VDP_PRINT("g_degmm_x4_pos = %d \n",g_degmm_x4_pos);	
    VDP_PRINT("g_degmm_x3_pos = %d \n",g_degmm_x3_pos);	
    VDP_PRINT("g_degmm_x4_num = %d \n",g_degmm_x4_num);	
    VDP_PRINT("g_degmm_x3_num = %d \n",g_degmm_x3_num);	
    VDP_PRINT("g_degmm_x2_num = %d \n",g_degmm_x2_num);	
    VDP_PRINT("g_degmm_x1_num = %d \n",g_degmm_x1_num);	
    VDP_PRINT("gdm_tmap_rd_en = %d \n",gdm_tmap_rd_en);	
    VDP_PRINT("gdm_tmap_para_data = %d \n",gdm_tmap_para_data);	
    VDP_PRINT("g_tmap_x4_step = %d \n",g_tmap_x4_step);	
    VDP_PRINT("g_tmap_x3_step = %d \n",g_tmap_x3_step);	
    VDP_PRINT("g_tmap_x2_step = %d \n",g_tmap_x2_step);	
    VDP_PRINT("g_tmap_x1_step = %d \n",g_tmap_x1_step);	
    VDP_PRINT("g_tmap_x1_pos = %d \n",g_tmap_x1_pos);	
    VDP_PRINT("g_tmap_x2_pos = %d \n",g_tmap_x2_pos);	
    VDP_PRINT("g_tmap_x4_num = %d \n",g_tmap_x4_num);	
    VDP_PRINT("g_tmap_x3_num = %d \n",g_tmap_x3_num);	
    VDP_PRINT("g_tmap_x2_num = %d \n",g_tmap_x2_num);	
    VDP_PRINT("g_tmap_x1_num = %d \n",g_tmap_x1_num);	
    VDP_PRINT("g_tmap_x3_pos = %d \n",g_tmap_x3_pos);	
    VDP_PRINT("g_tmap_x4_pos = %d \n",g_tmap_x4_pos);	
    VDP_PRINT("gdm_gamma_rd_en = %d \n",gdm_gamma_rd_en);	
    VDP_PRINT("gdm_gamma_para_data = %d \n",gdm_gamma_para_data);	
    VDP_PRINT("g_gmm_x4_step = %d \n",g_gmm_x4_step);	
    VDP_PRINT("g_gmm_x3_step = %d \n",g_gmm_x3_step);	
    VDP_PRINT("g_gmm_x2_step = %d \n",g_gmm_x2_step);	
    VDP_PRINT("g_gmm_x1_step = %d \n",g_gmm_x1_step);	
    VDP_PRINT("g_gmm_x2_pos = %d \n",g_gmm_x2_pos);	
    VDP_PRINT("g_gmm_x1_pos = %d \n",g_gmm_x1_pos);	
    VDP_PRINT("g_gmm_x4_pos = %d \n",g_gmm_x4_pos);	
    VDP_PRINT("g_gmm_x3_pos = %d \n",g_gmm_x3_pos);	
    VDP_PRINT("g_gmm_x4_num = %d \n",g_gmm_x4_num);	
    VDP_PRINT("g_gmm_x3_num = %d \n",g_gmm_x3_num);	
    VDP_PRINT("g_gmm_x2_num = %d \n",g_gmm_x2_num);	
    VDP_PRINT("g_gmm_x1_num = %d \n",g_gmm_x1_num);	
    VDP_PRINT("gdm_csc_en = %d \n",gdm_csc_en);	
    VDP_PRINT("gdm_coef00_csc = %d \n",gdm_coef00_csc);	
    VDP_PRINT("gdm_coef01_csc = %d \n",gdm_coef01_csc);	
    VDP_PRINT("gdm_coef02_csc = %d \n",gdm_coef02_csc);	
    VDP_PRINT("gdm_coef10_csc = %d \n",gdm_coef10_csc);	
    VDP_PRINT("gdm_coef11_csc = %d \n",gdm_coef11_csc);	
    VDP_PRINT("gdm_coef12_csc = %d \n",gdm_coef12_csc);	
    VDP_PRINT("gdm_coef20_csc = %d \n",gdm_coef20_csc);	
    VDP_PRINT("gdm_coef21_csc = %d \n",gdm_coef21_csc);	
    VDP_PRINT("gdm_coef22_csc = %d \n",gdm_coef22_csc);	
    VDP_PRINT("gdm_csc_scale = %d \n",gdm_csc_scale);	
    VDP_PRINT("gdm_csc_clip_min = %d \n",gdm_csc_clip_min);	
    VDP_PRINT("gdm_csc_clip_max = %d \n",gdm_csc_clip_max);	
    VDP_PRINT("gdm_rgb2yuv_en = %d \n",gdm_rgb2yuv_en);	
    VDP_PRINT("gdm_00_rgb2yuv = %d \n",gdm_00_rgb2yuv);	
    VDP_PRINT("gdm_01_rgb2yuv = %d \n",gdm_01_rgb2yuv);	
    VDP_PRINT("gdm_02_rgb2yuv = %d \n",gdm_02_rgb2yuv);	
    VDP_PRINT("gdm_10_rgb2yuv = %d \n",gdm_10_rgb2yuv);	
    VDP_PRINT("gdm_11_rgb2yuv = %d \n",gdm_11_rgb2yuv);	
    VDP_PRINT("gdm_12_rgb2yuv = %d \n",gdm_12_rgb2yuv);	
    VDP_PRINT("gdm_20_rgb2yuv = %d \n",gdm_20_rgb2yuv);	
    VDP_PRINT("gdm_21_rgb2yuv = %d \n",gdm_21_rgb2yuv);	
    VDP_PRINT("gdm_22_rgb2yuv = %d \n",gdm_22_rgb2yuv);	
    VDP_PRINT("gdm_rgb2yuvscale2p = %d \n",gdm_rgb2yuvscale2p);	
    VDP_PRINT("gdm_rgb2yuv_0_in_dc = %d \n",gdm_rgb2yuv_0_in_dc);	
    VDP_PRINT("gdm_rgb2yuv_1_in_dc = %d \n",gdm_rgb2yuv_1_in_dc);	
    VDP_PRINT("gdm_rgb2yuv_2_in_dc = %d \n",gdm_rgb2yuv_2_in_dc);	
    VDP_PRINT("gdm_rgb2yuv_0_out_dc = %d \n",gdm_rgb2yuv_0_out_dc);	
    VDP_PRINT("gdm_rgb2yuv_1_out_dc = %d \n",gdm_rgb2yuv_1_out_dc);	
    VDP_PRINT("gdm_rgb2yuv_2_out_dc = %d \n",gdm_rgb2yuv_2_out_dc);	
    VDP_PRINT("gdm_rgb2yuv_clip_min = %d \n",gdm_rgb2yuv_clip_min);	
    VDP_PRINT("gdm_rgb2yuv_clip_max = %d \n",gdm_rgb2yuv_clip_max);	
    VDP_PRINT("gdm_dither_round_unlim = %d \n",gdm_dither_round_unlim);	
    VDP_PRINT("gdm_dither_en = %d \n",gdm_dither_en);	
    VDP_PRINT("gdm_dither_mode = %d \n",gdm_dither_mode);	
    VDP_PRINT("gdm_dither_round = %d \n",gdm_dither_round);	
    VDP_PRINT("gdm_dither_domain_mode = %d \n",gdm_dither_domain_mode);	
    VDP_PRINT("gdm_dither_tap_mode = %d \n",gdm_dither_tap_mode);	
    VDP_PRINT("gdm_dither_sed_y0 = %d \n",gdm_dither_sed_y0);	
    VDP_PRINT("gdm_dither_sed_u0 = %d \n",gdm_dither_sed_u0);	
    VDP_PRINT("gdm_dither_sed_v0 = %d \n",gdm_dither_sed_v0);	
    VDP_PRINT("gdm_dither_sed_w0 = %d \n",gdm_dither_sed_w0);	
    VDP_PRINT("gdm_dither_sed_y1 = %d \n",gdm_dither_sed_y1);	
    VDP_PRINT("gdm_dither_sed_u1 = %d \n",gdm_dither_sed_u1);	
    VDP_PRINT("gdm_dither_sed_v1 = %d \n",gdm_dither_sed_v1);	
    VDP_PRINT("gdm_dither_sed_w1 = %d \n",gdm_dither_sed_w1);	
    VDP_PRINT("gdm_dither_sed_y2 = %d \n",gdm_dither_sed_y2);	
    VDP_PRINT("gdm_dither_sed_u2 = %d \n",gdm_dither_sed_u2);	
    VDP_PRINT("gdm_dither_sed_v2 = %d \n",gdm_dither_sed_v2);	
    VDP_PRINT("gdm_dither_sed_w2 = %d \n",gdm_dither_sed_w2);	
    VDP_PRINT("gdm_dither_sed_y3 = %d \n",gdm_dither_sed_y3);	
    VDP_PRINT("gdm_dither_sed_u3 = %d \n",gdm_dither_sed_u3);	
    VDP_PRINT("gdm_dither_sed_v3 = %d \n",gdm_dither_sed_v3);	
    VDP_PRINT("gdm_dither_sed_w3 = %d \n",gdm_dither_sed_w3);	
    VDP_PRINT("gdm_dither_thr_max = %d \n",gdm_dither_thr_max);	
    VDP_PRINT("gdm_dither_thr_min = %d \n",gdm_dither_thr_min);	
#endif
	//drv transfer	
	VDP_GP_SetGdmGdmTmapInBdp(enLayer, gdm_tmap_in_bdp);
	VDP_GP_SetGdmGdmGmmEn(enLayer, gdm_gmm_en);
	VDP_GP_SetGdmGdmTmapEn(enLayer, gdm_tmap_en);
	VDP_GP_SetGdmGdmDegmmEn(enLayer, gdm_degmm_en);
	VDP_GP_SetGdmGdmEn(enLayer, gdm_en);
	VDP_GP_SetGdmGdmLumaCoef0Tmap(enLayer, gdm_luma_coef0_tmap);
	VDP_GP_SetGdmGdmLumaCoef1Tmap(enLayer, gdm_luma_coef1_tmap);
	VDP_GP_SetGdmGdmLumaCoef2Tmap(enLayer, gdm_luma_coef2_tmap);
	VDP_GP_SetGdmGdmTmapLumaScale(enLayer, gdm_tmap_luma_scale);
	VDP_GP_SetGdmGdmTmapCoefScale(enLayer, gdm_tmap_coef_scale);
	VDP_GP_SetGdmGdmTmapOutClipMin(enLayer, gdm_tmap_out_clip_min);
	VDP_GP_SetGdmGdmTmapOutClipMax(enLayer, gdm_tmap_out_clip_max);
	//VDP_GP_SetGdmGdmParaGmmAddr(enLayer, gdm_para_gmm_addr);
	//VDP_GP_SetGdmGdmParaTmapAddr(enLayer, gdm_para_tmap_addr);
	//VDP_GP_SetGdmGdmParaTmapUpd(enLayer, gdm_para_tmap_upd);
	//VDP_GP_SetGdmGdmParaGmmUpd(enLayer, gdm_para_gmm_upd);
    //add_regs 
	VDP_GP_SetGdmGGmmX5Num(enLayer,g_gmm_x5_num);
	VDP_GP_SetGdmGGmmX6Num(enLayer,g_gmm_x6_num);
	VDP_GP_SetGdmGGmmX7Num(enLayer,g_gmm_x7_num);
	VDP_GP_SetGdmGGmmX8Num(enLayer,g_gmm_x8_num);
	VDP_GP_SetGdmGGmmX7Pos(enLayer,g_gmm_x7_pos);
	VDP_GP_SetGdmGGmmX8Pos(enLayer,g_gmm_x8_pos);
	VDP_GP_SetGdmGGmmX5Pos(enLayer,g_gmm_x5_pos);
	VDP_GP_SetGdmGGmmX6Pos(enLayer,g_gmm_x6_pos);
	VDP_GP_SetGdmGGmmX5Step(enLayer,g_gmm_x5_step);
	VDP_GP_SetGdmGGmmX6Step(enLayer,g_gmm_x6_step);
	VDP_GP_SetGdmGGmmX7Step(enLayer,g_gmm_x7_step);
	VDP_GP_SetGdmGGmmX8Step(enLayer,g_gmm_x8_step);

	VDP_GP_SetGdmGDegmmX4Step(enLayer, g_degmm_x4_step);
	VDP_GP_SetGdmGDegmmX3Step(enLayer, g_degmm_x3_step);
	VDP_GP_SetGdmGDegmmX2Step(enLayer, g_degmm_x2_step);
	VDP_GP_SetGdmGDegmmX1Step(enLayer, g_degmm_x1_step);
	VDP_GP_SetGdmGDegmmX2Pos(enLayer, g_degmm_x2_pos);
	VDP_GP_SetGdmGDegmmX1Pos(enLayer, g_degmm_x1_pos);
	VDP_GP_SetGdmGDegmmX4Pos(enLayer, g_degmm_x4_pos);
	VDP_GP_SetGdmGDegmmX3Pos(enLayer, g_degmm_x3_pos);
	VDP_GP_SetGdmGDegmmX4Num(enLayer, g_degmm_x4_num);
	VDP_GP_SetGdmGDegmmX3Num(enLayer, g_degmm_x3_num);
	VDP_GP_SetGdmGDegmmX2Num(enLayer, g_degmm_x2_num);
	VDP_GP_SetGdmGDegmmX1Num(enLayer, g_degmm_x1_num);
	VDP_GP_SetGdmGdmTmapRdEn(enLayer, gdm_tmap_rd_en);
	VDP_GP_SetGdmGdmTmapParaData(enLayer, gdm_tmap_para_data);
	VDP_GP_SetGdmGTmapX4Step(enLayer, g_tmap_x4_step);
	VDP_GP_SetGdmGTmapX3Step(enLayer, g_tmap_x3_step);
	VDP_GP_SetGdmGTmapX2Step(enLayer, g_tmap_x2_step);
	VDP_GP_SetGdmGTmapX1Step(enLayer, g_tmap_x1_step);
	VDP_GP_SetGdmGTmapX1Pos(enLayer, g_tmap_x1_pos);
	VDP_GP_SetGdmGTmapX2Pos(enLayer, g_tmap_x2_pos);
	VDP_GP_SetGdmGTmapX4Num(enLayer, g_tmap_x4_num);
	VDP_GP_SetGdmGTmapX3Num(enLayer, g_tmap_x3_num);
	VDP_GP_SetGdmGTmapX2Num(enLayer, g_tmap_x2_num);
	VDP_GP_SetGdmGTmapX1Num(enLayer, g_tmap_x1_num);
	VDP_GP_SetGdmGTmapX3Pos(enLayer, g_tmap_x3_pos);
	VDP_GP_SetGdmGTmapX4Pos(enLayer, g_tmap_x4_pos);
	VDP_GP_SetGdmGdmGammaRdEn(enLayer, gdm_gamma_rd_en);
	VDP_GP_SetGdmGdmGammaParaData(enLayer, gdm_gamma_para_data);
	VDP_GP_SetGdmGGmmX4Step(enLayer, g_gmm_x4_step);
	VDP_GP_SetGdmGGmmX3Step(enLayer, g_gmm_x3_step);
	VDP_GP_SetGdmGGmmX2Step(enLayer, g_gmm_x2_step);
	VDP_GP_SetGdmGGmmX1Step(enLayer, g_gmm_x1_step);
	VDP_GP_SetGdmGGmmX2Pos(enLayer, g_gmm_x2_pos);
	VDP_GP_SetGdmGGmmX1Pos(enLayer, g_gmm_x1_pos);
	VDP_GP_SetGdmGGmmX4Pos(enLayer, g_gmm_x4_pos);
	VDP_GP_SetGdmGGmmX3Pos(enLayer, g_gmm_x3_pos);
	VDP_GP_SetGdmGGmmX4Num(enLayer, g_gmm_x4_num);
	VDP_GP_SetGdmGGmmX3Num(enLayer, g_gmm_x3_num);
	VDP_GP_SetGdmGGmmX2Num(enLayer, g_gmm_x2_num);
	VDP_GP_SetGdmGGmmX1Num(enLayer, g_gmm_x1_num);
	VDP_GP_SetGdmGdmCscEn(enLayer, gdm_csc_en);
	VDP_GP_SetGdmGdmCoef00Csc(enLayer, gdm_coef00_csc);
	VDP_GP_SetGdmGdmCoef01Csc(enLayer, gdm_coef01_csc);
	VDP_GP_SetGdmGdmCoef02Csc(enLayer, gdm_coef02_csc);
	VDP_GP_SetGdmGdmCoef10Csc(enLayer, gdm_coef10_csc);
	VDP_GP_SetGdmGdmCoef11Csc(enLayer, gdm_coef11_csc);
	VDP_GP_SetGdmGdmCoef12Csc(enLayer, gdm_coef12_csc);
	VDP_GP_SetGdmGdmCoef20Csc(enLayer, gdm_coef20_csc);
	VDP_GP_SetGdmGdmCoef21Csc(enLayer, gdm_coef21_csc);
	VDP_GP_SetGdmGdmCoef22Csc(enLayer, gdm_coef22_csc);
	VDP_GP_SetGdmGdmCscScale(enLayer, gdm_csc_scale);
	VDP_GP_SetGdmGdmCscClipMin(enLayer, gdm_csc_clip_min);
	VDP_GP_SetGdmGdmCscClipMax(enLayer, gdm_csc_clip_max);
	VDP_GP_SetGdmGdmRgb2yuvEn(enLayer, gdm_rgb2yuv_en);
	VDP_GP_SetGdmGdm00Rgb2yuv(enLayer, gdm_00_rgb2yuv);
	VDP_GP_SetGdmGdm01Rgb2yuv(enLayer, gdm_01_rgb2yuv);
	VDP_GP_SetGdmGdm02Rgb2yuv(enLayer, gdm_02_rgb2yuv);
	VDP_GP_SetGdmGdm10Rgb2yuv(enLayer, gdm_10_rgb2yuv);
	VDP_GP_SetGdmGdm11Rgb2yuv(enLayer, gdm_11_rgb2yuv);
	VDP_GP_SetGdmGdm12Rgb2yuv(enLayer, gdm_12_rgb2yuv);
	VDP_GP_SetGdmGdm20Rgb2yuv(enLayer, gdm_20_rgb2yuv);
	VDP_GP_SetGdmGdm21Rgb2yuv(enLayer, gdm_21_rgb2yuv);
	VDP_GP_SetGdmGdm22Rgb2yuv(enLayer, gdm_22_rgb2yuv);
	VDP_GP_SetGdmGdmRgb2yuvscale2p(enLayer, gdm_rgb2yuvscale2p);
	VDP_GP_SetGdmGdmRgb2yuv0InDc(enLayer, gdm_rgb2yuv_0_in_dc);
	VDP_GP_SetGdmGdmRgb2yuv1InDc(enLayer, gdm_rgb2yuv_1_in_dc);
	VDP_GP_SetGdmGdmRgb2yuv2InDc(enLayer, gdm_rgb2yuv_2_in_dc);
	VDP_GP_SetGdmGdmRgb2yuv0OutDc(enLayer, gdm_rgb2yuv_0_out_dc);
	VDP_GP_SetGdmGdmRgb2yuv1OutDc(enLayer, gdm_rgb2yuv_1_out_dc);
	VDP_GP_SetGdmGdmRgb2yuv2OutDc(enLayer, gdm_rgb2yuv_2_out_dc);
	VDP_GP_SetGdmGdmRgb2yuvClipMin(enLayer, gdm_rgb2yuv_clip_min);
	VDP_GP_SetGdmGdmRgb2yuvClipMax(enLayer, gdm_rgb2yuv_clip_max);
	VDP_GP_SetGdmGdmDitherRoundUnlim(enLayer, gdm_dither_round_unlim);
	VDP_GP_SetGdmGdmDitherEn(enLayer, gdm_dither_en);
	VDP_GP_SetGdmGdmDitherMode(enLayer, gdm_dither_mode);
	VDP_GP_SetGdmGdmDitherRound(enLayer, gdm_dither_round);
	VDP_GP_SetGdmGdmDitherDomainMode(enLayer, gdm_dither_domain_mode);
	VDP_GP_SetGdmGdmDitherTapMode(enLayer, gdm_dither_tap_mode);
	VDP_GP_SetGdmGdmDitherSedY0(enLayer, gdm_dither_sed_y0);
	VDP_GP_SetGdmGdmDitherSedU0(enLayer, gdm_dither_sed_u0);
	VDP_GP_SetGdmGdmDitherSedV0(enLayer, gdm_dither_sed_v0);
	VDP_GP_SetGdmGdmDitherSedW0(enLayer, gdm_dither_sed_w0);
	VDP_GP_SetGdmGdmDitherSedY1(enLayer, gdm_dither_sed_y1);
	VDP_GP_SetGdmGdmDitherSedU1(enLayer, gdm_dither_sed_u1);
	VDP_GP_SetGdmGdmDitherSedV1(enLayer, gdm_dither_sed_v1);
	VDP_GP_SetGdmGdmDitherSedW1(enLayer, gdm_dither_sed_w1);
	VDP_GP_SetGdmGdmDitherSedY2(enLayer, gdm_dither_sed_y2);
	VDP_GP_SetGdmGdmDitherSedU2(enLayer, gdm_dither_sed_u2);
	VDP_GP_SetGdmGdmDitherSedV2(enLayer, gdm_dither_sed_v2);
	VDP_GP_SetGdmGdmDitherSedW2(enLayer, gdm_dither_sed_w2);
	VDP_GP_SetGdmGdmDitherSedY3(enLayer, gdm_dither_sed_y3);
	VDP_GP_SetGdmGdmDitherSedU3(enLayer, gdm_dither_sed_u3);
	VDP_GP_SetGdmGdmDitherSedV3(enLayer, gdm_dither_sed_v3);
	VDP_GP_SetGdmGdmDitherSedW3(enLayer, gdm_dither_sed_w3);
	VDP_GP_SetGdmGdmDitherThrMax(enLayer, gdm_dither_thr_max);
	VDP_GP_SetGdmGdmDitherThrMin(enLayer, gdm_dither_thr_min);

    free(pstDmCfg);
#if EDA_TEST
	cout << "__LINE__" <<__LINE__<< endl;
#endif
	#endif
}

