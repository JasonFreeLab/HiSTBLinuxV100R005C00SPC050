#include "vdp_drv_ip_vdm.h"
//#include <stdio.h>
#include "vdp_define.h"
#include "vdp_drv_func.h"

//#include "vdp_util.h"


//DmCfg_t g_DmCfg;

HI_VOID VDP_FUNC_SetVdmMode(HI_U32 enLayer, VDP_VID_VDM_MODE_E VdmMode, VDP_VDM_CFG_S * pstCfg)
{
    #if 0
    DmCfg_t * pstDmCfg;
//     HI_U32 ii;

	//filed declare
	HI_U32 vdm_ck_gt_en            = 0;
	HI_U32 vdm_tmap_in_bdp         = 0;
	HI_U32 vdm_csc_bind            = 0;
	HI_U32 vdm_gmm_en              = 0;
	HI_U32 vdm_tmap_en             = 0;
	HI_U32 vdm_degmm_en            = 0;
	HI_U32 vdm_en                  = 0;
	HI_U16 vdm_luma_coef0_tmap     = 0;
	HI_U16 vdm_luma_coef1_tmap     = 0;
	HI_U16 vdm_luma_coef2_tmap     = 0;
	HI_U16 vdm_tmap_luma_scale     = 0;
	HI_U16 vdm_tmap_coef_scale     = 0;
	HI_U32 vdm_tmap_out_clip_min   = 0;
	HI_U32 vdm_tmap_out_clip_max   = 0;
	//	HI_U32 vdm_para_degmm_addr  = 0;
	//	HI_U32 vdm_para_gmm_addr    = 0;
	//	HI_U32 vdm_para_tmap_addr   = 0;
	//	HI_U32 vdm_para_tmap_upd    = 0;
	//	HI_U32 vdm_para_gmm_upd     = 0;
	//	HI_U32 vdm_para_degmm_upd   = 0;
	HI_S32 vdm_tmap_out_dc0        = 0;
	HI_S32 vdm_tmap_out_dc1        = 0;
	HI_S32 vdm_tmap_out_dc2        = 0;
	HI_U32 vdm_degamma_rd_en       = 0;
	HI_U32 vdm_degamma_para_data   = 0;
	HI_U32 v_degmm_x1_step         = 0;
	HI_U32 v_degmm_x2_step         = 0;
	HI_U32 v_degmm_x3_step         = 0;
	HI_U32 v_degmm_x4_step         = 0;
	HI_U32 v_degmm_x5_step         = 0;
	HI_U32 v_degmm_x6_step         = 0;
	HI_U32 v_degmm_x7_step         = 0;
	HI_U32 v_degmm_x8_step         = 0;
	HI_U32 v_degmm_x1_pos          = 0;
	HI_U32 v_degmm_x2_pos          = 0;
	HI_U32 v_degmm_x3_pos          = 0;
	HI_U32 v_degmm_x4_pos          = 0;
	HI_U32 v_degmm_x5_pos          = 0;
	HI_U32 v_degmm_x6_pos          = 0;
	HI_U32 v_degmm_x7_pos          = 0;
	HI_U32 v_degmm_x8_pos          = 0;
	HI_U32 v_degmm_x1_num          = 0;
	HI_U32 v_degmm_x2_num          = 0;
	HI_U32 v_degmm_x3_num          = 0;
	HI_U32 v_degmm_x4_num          = 0;
	HI_U32 v_degmm_x5_num          = 0;
	HI_U32 v_degmm_x6_num          = 0;
	HI_U32 v_degmm_x7_num          = 0;
	HI_U32 v_degmm_x8_num          = 0;
	HI_U32 vdm_tmap_rd_en          = 0;
	HI_U32 vdm_sm_rd_en            = 0;
	HI_U32 vdm_tmap_para_data      = 0;
	HI_U32 vdm_sm_para_data        = 0;
	HI_U32 v_tmap_x4_step          = 0;
	HI_U32 v_tmap_x5_step          = 0;
	HI_U32 v_tmap_x6_step          = 0;
	HI_U32 v_tmap_x7_step          = 0;
	HI_U32 v_tmap_x8_step          = 0;
	HI_U32 v_tmap_x3_step          = 0;
	HI_U32 v_tmap_x2_step          = 0;
	HI_U32 v_tmap_x1_step          = 0;
	HI_U32 v_tmap_x1_pos           = 0;
	HI_U32 v_tmap_x2_pos           = 0;
	HI_U32 v_tmap_x4_num           = 0;
	HI_U32 v_tmap_x5_num           = 0;
	HI_U32 v_tmap_x6_num           = 0;
	HI_U32 v_tmap_x7_num           = 0;
	HI_U32 v_tmap_x8_num           = 0;
	HI_U32 v_tmap_x3_num           = 0;
	HI_U32 v_tmap_x2_num           = 0;
	HI_U32 v_tmap_x1_num           = 0;
	HI_U32 v_tmap_x3_pos           = 0;
	HI_U32 v_tmap_x4_pos           = 0;
	HI_U32 v_tmap_x5_pos           = 0;
	HI_U32 v_tmap_x6_pos           = 0;
	HI_U32 v_tmap_x7_pos           = 0;
	HI_U32 v_tmap_x8_pos           = 0;
	HI_U32 v_smap_x4_step          = 0;
	HI_U32 v_smap_x5_step          = 0;
	HI_U32 v_smap_x6_step          = 0;
	HI_U32 v_smap_x7_step          = 0;
	HI_U32 v_smap_x8_step          = 0;
	HI_U32 v_smap_x3_step          = 0;
	HI_U32 v_smap_x2_step          = 0;
	HI_U32 v_smap_x1_step          = 0;
	HI_U32 v_smap_x1_pos           = 0;
	HI_U32 v_smap_x2_pos           = 0;
	HI_U32 v_smap_x4_num           = 0;
	HI_U32 v_smap_x5_num           = 0;
	HI_U32 v_smap_x6_num           = 0;
	HI_U32 v_smap_x7_num           = 0;
	HI_U32 v_smap_x8_num           = 0;
	HI_U32 v_smap_x3_num           = 0;
	HI_U32 v_smap_x2_num           = 0;
	HI_U32 v_smap_x1_num           = 0;
	HI_U32 v_smap_x3_pos           = 0;
	HI_U32 v_smap_x4_pos           = 0;
	HI_U32 v_smap_x5_pos           = 0;
	HI_U32 v_smap_x6_pos           = 0;
	HI_U32 v_smap_x7_pos           = 0;
	HI_U32 v_smap_x8_pos           = 0;
	HI_U32 vdm_gamma_rd_en         = 0;
	HI_U32 vdm_gamma_para_data     = 0;
	HI_U32 v_gmm_x5_step           = 0;
	HI_U32 v_gmm_x6_step           = 0;
	HI_U32 v_gmm_x7_step           = 0;
	HI_U32 v_gmm_x8_step           = 0;
	HI_U32 v_gmm_x4_step           = 0;
	HI_U32 v_gmm_x3_step           = 0;
	HI_U32 v_gmm_x2_step           = 0;
	HI_U32 v_gmm_x1_step           = 0;
	HI_U32 v_gmm_x1_pos            = 0;
	HI_U32 v_gmm_x2_pos            = 0;
	HI_U32 v_gmm_x3_pos            = 0;
	HI_U32 v_gmm_x4_pos            = 0;
	HI_U32 v_gmm_x5_pos            = 0;
	HI_U32 v_gmm_x6_pos            = 0;
	HI_U32 v_gmm_x7_pos            = 0;
	HI_U32 v_gmm_x8_pos            = 0;
	HI_U32 v_gmm_x5_num            = 0;
	HI_U32 v_gmm_x6_num            = 0;
	HI_U32 v_gmm_x7_num            = 0;
	HI_U32 v_gmm_x8_num            = 0;
	HI_U32 v_gmm_x4_num            = 0;
	HI_U32 v_gmm_x3_num            = 0;
	HI_U32 v_gmm_x2_num            = 0;
	HI_U32 v_gmm_x1_num            = 0;
	HI_U32 vdm_csc_en              = 0;
	HI_S16 vdm_coef00_csc          = 0;
	HI_S16 vdm_coef01_csc          = 0;
	HI_S16 vdm_coef02_csc          = 0;
	HI_S16 vdm_coef10_csc          = 0;
	HI_S16 vdm_coef11_csc          = 0;
	HI_S16 vdm_coef12_csc          = 0;
	HI_S16 vdm_coef20_csc          = 0;
	HI_S16 vdm_coef21_csc          = 0;
	HI_S16 vdm_coef22_csc          = 0;
	HI_U16 vdm_csc_scale           = 0;
	HI_U32 vdm_csc_clip_min        = 0;
	HI_U32 vdm_csc_clip_max        = 0;
	HI_S32 vdm_csc_0_in_dc         = 0;
	HI_S32 vdm_csc_1_in_dc         = 0;
	HI_S32 vdm_csc_2_in_dc         = 0;
	HI_S32 vdm_csc_0_out_dc        = 0;
	HI_S32 vdm_csc_1_out_dc        = 0;
	HI_S32 vdm_csc_2_out_dc        = 0;
	HI_U32 vdm_v1_gamma_en         = 0;
	HI_U32 vdm_v0_gamma_en         = 0;
	HI_U32 vdm_v1_csc_en           = 0;
	HI_U32 vdm_v0_csc_en           = 0;
	HI_U32 vdm_yuv2rgb_en          = 0;
	HI_U32 vdm_v0_cl_en            = 0;
	HI_U32 vdm_v1_cl_en            = 0;
	HI_S16 vdm_00_yuv2rgb          = 0;
	HI_S16 vdm_01_yuv2rgb          = 0;
	HI_S16 vdm_02_yuv2rgb          = 0;
	HI_S16 vdm_03_yuv2rgb          = 0;
	HI_S16 vdm_04_yuv2rgb          = 0;
	HI_S16 vdm_05_yuv2rgb          = 0;
	HI_S16 vdm_06_yuv2rgb          = 0;
	HI_S16 vdm_07_yuv2rgb          = 0;
	HI_S16 vdm_08_yuv2rgb          = 0;
	HI_S16 vdm_10_yuv2rgb          = 0;
	HI_S16 vdm_11_yuv2rgb          = 0;
	HI_S16 vdm_12_yuv2rgb          = 0;
	HI_S16 vdm_13_yuv2rgb          = 0;
	HI_S16 vdm_14_yuv2rgb          = 0;
	HI_S16 vdm_15_yuv2rgb          = 0;
	HI_S16 vdm_16_yuv2rgb          = 0;
	HI_S16 vdm_17_yuv2rgb          = 0;
	HI_S16 vdm_18_yuv2rgb          = 0;
	HI_U16 vdm_v0_yuv2rgbscale2p   = 0;
	HI_U16 vdm_v1_yuv2rgbscale2p   = 0;
	HI_S32 vdm_yuv2rgb_00_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_01_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_02_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_00_out_dc   = 0;
	HI_S32 vdm_yuv2rgb_01_out_dc   = 0;
	HI_S32 vdm_yuv2rgb_02_out_dc   = 0;
	HI_S32 vdm_yuv2rgb_10_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_11_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_12_in_dc    = 0;
	HI_S32 vdm_yuv2rgb_10_out_dc   = 0;
	HI_S32 vdm_yuv2rgb_11_out_dc   = 0;
	HI_S32 vdm_yuv2rgb_12_out_dc   = 0;
	HI_U16 vdm_v0_yuv2rgb_clip_min = 0;
	HI_U16 vdm_v0_yuv2rgb_clip_max = 0;
	HI_U16 vdm_v1_yuv2rgb_clip_min = 0;
	HI_U16 vdm_v1_yuv2rgb_clip_max = 0;
	HI_U32 vdm_rgb2yuv_pip_en      = 0;
	HI_U32 vdm_rgb2yuv_en          = 0;
	HI_U32 vdm_cadj_en             = 0;
	HI_S16 vdm_00_rgb2yuv          = 0;
	HI_S16 vdm_01_rgb2yuv          = 0;
	HI_S16 vdm_02_rgb2yuv          = 0;
	HI_S16 vdm_10_rgb2yuv          = 0;
	HI_S16 vdm_11_rgb2yuv          = 0;
	HI_S16 vdm_12_rgb2yuv          = 0;
	HI_S16 vdm_20_rgb2yuv          = 0;
	HI_S16 vdm_21_rgb2yuv          = 0;
	HI_S16 vdm_22_rgb2yuv          = 0;
	HI_U16 vdm_rgb2yuvscale2p      = 0;
	HI_U16 vdm_cadj_scale2p        = 0;
	HI_S16 vdm_rgb2yuv_0_in_dc     = 0;
	HI_S16 vdm_rgb2yuv_1_in_dc     = 0;
	HI_S16 vdm_rgb2yuv_2_in_dc     = 0;
	HI_S16 vdm_rgb2yuv_0_out_dc    = 0;
	HI_S16 vdm_rgb2yuv_1_out_dc    = 0;
	HI_S16 vdm_rgb2yuv_2_out_dc    = 0;
	HI_U16 vdm_rgb2yuv_clip_y_min  = 0;
	HI_U16 vdm_rgb2yuv_clip_uv_min = 0;
	HI_U16 vdm_rgb2yuv_clip_y_max  = 0;
	HI_U16 vdm_rgb2yuv_clip_uv_max = 0;
	HI_U32 vdm_dither_round_unlim  = 0;
	HI_U32 vdm_dither_en           = 0;
	HI_U32 vdm_dither_round        = 0;
	HI_U32 vdm_dither_domain_mode  = 0;
	HI_U32 vdm_dither_tap_mode     = 0;
	HI_U32 vdm_dither_sed_y0       = 0;
	HI_U32 vdm_dither_sed_u0       = 0;
	HI_U32 vdm_dither_sed_v0       = 0;
	HI_U32 vdm_dither_sed_w0       = 0;
	HI_U32 vdm_dither_sed_y1       = 0;
	HI_U32 vdm_dither_sed_u1       = 0;
	HI_U32 vdm_dither_sed_v1       = 0;
	HI_U32 vdm_dither_sed_w1       = 0;
	HI_U32 vdm_dither_sed_y2       = 0;
	HI_U32 vdm_dither_sed_u2       = 0;
	HI_U32 vdm_dither_sed_v2       = 0;
	HI_U32 vdm_dither_sed_w2       = 0;
	HI_U32 vdm_dither_sed_y3       = 0;
	HI_U32 vdm_dither_sed_u3       = 0;
	HI_U32 vdm_dither_sed_v3       = 0;
	HI_U32 vdm_dither_sed_w3       = 0;
	HI_U32 vdm_dither_thr_max      = 0;
	HI_U32 vdm_dither_thr_min      = 0;

	HI_U32 degamm_num1             = 0;
	HI_U32 degamm_num2             = 0;
	HI_U32 degamm_num3             = 0;
	HI_U32 degamm_num4             = 0;
	HI_U32 degamm_num5             = 0;
	HI_U32 degamm_num6             = 0;
	HI_U32 degamm_num7             = 0;
	HI_U32 degamm_num8             = 0;
	HI_U32 degamm_step1            = 0;
	HI_U32 degamm_step2            = 0;
	HI_U32 degamm_step3            = 0;
	HI_U32 degamm_step4            = 0;
	HI_U32 degamm_step5            = 0;
	HI_U32 degamm_step6            = 0;
	HI_U32 degamm_step7            = 0;
	HI_U32 degamm_step8            = 0;
	HI_U32 degamm_pos1             = 0;
	HI_U32 degamm_pos2             = 0;
	HI_U32 degamm_pos3             = 0;
	HI_U32 degamm_pos4             = 0;
	HI_U32 degamm_pos5             = 0;
	HI_U32 degamm_pos6             = 0;
	HI_U32 degamm_pos7             = 0;
	HI_U32 degamm_pos8             = 0;

	HI_U32 tmap_num1               = 0;
	HI_U32 tmap_num2               = 0;
	HI_U32 tmap_num3               = 0;
	HI_U32 tmap_num4               = 0;
	HI_U32 tmap_num5               = 0;
	HI_U32 tmap_num6               = 0;
	HI_U32 tmap_num7               = 0;
	HI_U32 tmap_num8               = 0;
	HI_U32 tmap_step1              = 0;
	HI_U32 tmap_step2              = 0;
	HI_U32 tmap_step3              = 0;
	HI_U32 tmap_step4              = 0;
	HI_U32 tmap_step5              = 0;
	HI_U32 tmap_step6              = 0;
	HI_U32 tmap_step7              = 0;
	HI_U32 tmap_step8              = 0;
	HI_U32 tmap_pos1               = 0;
	HI_U32 tmap_pos2               = 0;
	HI_U32 tmap_pos3               = 0;
	HI_U32 tmap_pos4               = 0;
	HI_U32 tmap_pos5               = 0;
	HI_U32 tmap_pos6               = 0;
	HI_U32 tmap_pos7               = 0;
	HI_U32 tmap_pos8               = 0;
	HI_U32 smap_num1               = 0;
	HI_U32 smap_num2               = 0;
	HI_U32 smap_num3               = 0;
	HI_U32 smap_num4               = 0;
	HI_U32 smap_num5               = 0;
	HI_U32 smap_num6               = 0;
	HI_U32 smap_num7               = 0;
	HI_U32 smap_num8               = 0;
	HI_U32 smap_step1              = 0;
	HI_U32 smap_step2              = 0;
	HI_U32 smap_step3              = 0;
	HI_U32 smap_step4              = 0;
	HI_U32 smap_step5              = 0;
	HI_U32 smap_step6              = 0;
	HI_U32 smap_step7              = 0;
	HI_U32 smap_step8              = 0;
	HI_U32 smap_pos1               = 0;
	HI_U32 smap_pos2               = 0;
	HI_U32 smap_pos3               = 0;
	HI_U32 smap_pos4               = 0;
	HI_U32 smap_pos5               = 0;
	HI_U32 smap_pos6               = 0;
	HI_U32 smap_pos7               = 0;
	HI_U32 smap_pos8               = 0;

	HI_U32 gamm_num1               = 0;
	HI_U32 gamm_num2               = 0;
	HI_U32 gamm_num3               = 0;
	HI_U32 gamm_num4               = 0;
	HI_U32 gamm_num5               = 0;
	HI_U32 gamm_num6               = 0;
	HI_U32 gamm_num7               = 0;
	HI_U32 gamm_num8               = 0;
	HI_U32 gamm_step1              = 0;
	HI_U32 gamm_step2              = 0;
	HI_U32 gamm_step3              = 0;
	HI_U32 gamm_step4              = 0;
	HI_U32 gamm_step5              = 0;
	HI_U32 gamm_step6              = 0;
	HI_U32 gamm_step7              = 0;
	HI_U32 gamm_step8              = 0;
	HI_U32 gamm_pos1               = 0;
	HI_U32 gamm_pos2               = 0;
	HI_U32 gamm_pos3               = 0;
	HI_U32 gamm_pos4               = 0;
	HI_U32 gamm_pos5               = 0;
	HI_U32 gamm_pos6               = 0;
	HI_U32 gamm_pos7               = 0;
	HI_U32 gamm_pos8               = 0;
	HI_U32 degamma_num_sum7        = 0;
	HI_U32 tmap_num_sum7           = 0;
	HI_U32 smap_num_sum7           = 0;
	HI_U32 gamm_num_sum7           = 0;

	HI_U32 degamm_rand_cnt         = 0;
	HI_U32 tmap_rand_cnt           = 0;
	HI_U32 smap_rand_cnt           = 0;
	HI_U32 gamm_rand_cnt           = 0;

    pstDmCfg = (DmCfg_t *)malloc(sizeof(DmCfg_t));

    pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en   ;
    pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en   ;
    pstDmCfg->vdm_v0_cl_en                   = pstCfg->vdm_v0_cl_en  ;
    pstDmCfg->vdm_v1_cl_en                   = pstCfg->vdm_v1_cl_en  ;
    pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
    pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;
    pstDmCfg->vdm_csc_bind                   = pstCfg->vdm_csc_bind    ;

    pstDmCfg->stDitherCfg.u32_dither_round        = pstCfg->u32_dither_round       ;// 0:dither, 1:round
    pstDmCfg->stDitherCfg.u32_dither_domain_mode  = pstCfg->u32_dither_domain_mode ;// 1
    pstDmCfg->stDitherCfg.u32_dither_tap_mode     = pstCfg->u32_dither_tap_mode    ;
    pstDmCfg->stDitherCfg.u32_dither_round_unlim  = pstCfg->u32_dither_round_unlim ;

    pstDmCfg->vdm_yuv2rgb_en                 = pstCfg->vdm_yuv2rgb_en ;
    pstDmCfg->vdm_en                         = pstCfg->vdm_en         ;
    pstDmCfg->vdm_degmm_en                   = pstCfg->vdm_degmm_en   ;
    pstDmCfg->vdm_csc_en                     = pstCfg->vdm_csc_en     ;
    pstDmCfg->vdm_tmap_en                    = pstCfg->vdm_tmap_en    ;
    pstDmCfg->vdm_gmm_en                     = pstCfg->vdm_gmm_en     ;
    pstDmCfg->vdm_dither_en                  = pstCfg->vdm_dither_en  ;
    pstDmCfg->vdm_rgb2yuv_pip_en             = rand()%2;//pstCfg->vdm_rgb2yuv_pip_en ;default value in dut:1
    pstDmCfg->vdm_rgb2yuv_en                 = pstCfg->vdm_rgb2yuv_en ;
    pstDmCfg->vdm_cadj_en                    = pstCfg->vdm_cadj_en    ;
    pstDmCfg->vdm_ck_gt_en                   = pstCfg->vdm_ck_gt_en   ;

    pstDmCfg->VdmSceneMode                   = pstCfg->VdmSceneMode   ;

    pstDmCfg->vdm_tmap_in_bdp                = 1 ;//1:21bit for vdm , 0:16bit for gdm

#ifdef EDA_TEST
    pstDmCfg->vdm_v0_cl_en                   = rand()%2;
    pstDmCfg->vdm_v1_cl_en                   = rand()%2;
#endif

	if(VdmMode == VDP_VID_VDM_TYP)
  {
      if(pstDmCfg->VdmSceneMode == VDM_HDR10_IN_SDR_OUT)//96mv200 test ok!
      {
          //typ mode
          VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 1 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 7       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;//65535   ; //

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_HDR10_IN_SDR_PIP_OUT)//96mv200 test ok!
      {
          //typ mode
          VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 1 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 7       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;//65535   ; //

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_HDR10_IN_BBC_OUT)//96mv200 test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_BBC_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 10      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_HDR10_IN_BBC_PIP_OUT)//96mv200 test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_BBC_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 10      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_AVS_IN_SDR_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_AVS_IN_SDR_OUT\n");
          //typ mode

    			// enable signal
    			pstDmCfg->vdm_yuv2rgb_en				 = 1 ;
    			pstDmCfg->vdm_en						 = 1 ;
    			pstDmCfg->vdm_degmm_en					 = 1 ;
    			pstDmCfg->vdm_csc_en					 = 1 ; // 0 ;
    			pstDmCfg->vdm_tmap_en					 = 1 ;
    			pstDmCfg->vdm_gmm_en					 = 1 ;
    			pstDmCfg->vdm_dither_en 				 = 1 ;
    			pstDmCfg->vdm_rgb2yuv_en				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 1 ;

    			pstDmCfg->vdm_v0_csc_en 				 = 1 ;////use Y2R BT2020 0 ; //use Y2R BT709
    			pstDmCfg->vdm_v1_csc_en 				 = 0 ;//                            1 ;
    			pstDmCfg->vdm_v0_gamma_en				 = 1 ;//                            0 ;
    			pstDmCfg->vdm_v1_gamma_en				 = 0 ;//                            1 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217    ;
          pstDmCfg->u16M3LumaCal[2]                = 1943     ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 7       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_AVS_IN_SDR_PIP_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_AVS_IN_SDR_PIP_OUT\n");
          //typ mode

    			// enable signal
    			pstDmCfg->vdm_yuv2rgb_en				 = 1 ;
    			pstDmCfg->vdm_en						 = 1 ;
    			pstDmCfg->vdm_degmm_en					 = 1 ;
    			pstDmCfg->vdm_csc_en					 = 1 ; // 0 ;
    			pstDmCfg->vdm_tmap_en					 = 1 ;
    			pstDmCfg->vdm_gmm_en					 = 1 ;
    			pstDmCfg->vdm_dither_en 				 = 1 ;
    			pstDmCfg->vdm_rgb2yuv_en				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 1 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217    ;
          pstDmCfg->u16M3LumaCal[2]                = 1943     ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 7       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_AVS_IN_HDR10_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_AVS_IN_HDR10_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_AVS_IN_HDR10_PIP_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_AVS_IN_HDR10_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;
          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_BBC_IN_SDR_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BBC_IN_SDR_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en				 = 1 ;
          pstDmCfg->vdm_en						 = 1 ;
          pstDmCfg->vdm_degmm_en					 = 1 ;
          pstDmCfg->vdm_csc_en					 = 1 ; // 0 ;
          pstDmCfg->vdm_tmap_en					 = 1 ;
          pstDmCfg->vdm_gmm_en					 = 1 ;
          pstDmCfg->vdm_dither_en 				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_en				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en 				 = 1 ;////use Y2R BT2020 0 ; //use Y2R BT709
          pstDmCfg->vdm_v1_csc_en 				 = 0 ;//                            1 ;
          pstDmCfg->vdm_v0_gamma_en				 = 1 ;//                            0 ;
          pstDmCfg->vdm_v1_gamma_en				 = 0 ;//                            1 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217    ;
          pstDmCfg->u16M3LumaCal[2]                = 1943     ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 15      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 514     ;
          pstDmCfg->s32TMOff1                      = 514     ;
          pstDmCfg->s32TMOff2                      = 514     ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_BBC_IN_SDR_PIP_OUT)//98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BBC_IN_SDR_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en				 = 1 ;
          pstDmCfg->vdm_en						 = 1 ;
          pstDmCfg->vdm_degmm_en					 = 1 ;
          pstDmCfg->vdm_csc_en					 = 1 ; // 0 ;
          pstDmCfg->vdm_tmap_en					 = 1 ;
          pstDmCfg->vdm_gmm_en					 = 1 ;
          pstDmCfg->vdm_dither_en 				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_en				 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217    ;
          pstDmCfg->u16M3LumaCal[2]                = 1943     ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 15      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 514     ;
          pstDmCfg->s32TMOff1                      = 514     ;
          pstDmCfg->s32TMOff2                      = 514     ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;


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
      else if(pstDmCfg->VdmSceneMode == VDM_BBC_IN_HDR10_OUT) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0;// 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

           pstDmCfg->vdm_v0_csc_en                  = 1;//use BT2020
           pstDmCfg->vdm_v1_csc_en                  = 0;//
           pstDmCfg->vdm_v0_gamma_en                = 1;//
           pstDmCfg->vdm_v1_gamma_en                = 0;//

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 15      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

          //RGB2YUV
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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_BBC_IN_HDR10_PIP_OUT) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BBC_IN_HDR10_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 0;// 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 15      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

          //RGB2YUV
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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_BT2020_IN_709_OUT) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BT2020_IN_709_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_BT2020_IN_709_PIP_OUT) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_BT2020_IN_709_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_XVYCC) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_XVYCC\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ;
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 8       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 8       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 256     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 896     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 1536    ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 2176    ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 3520    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 3680    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 3840    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 4095    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 1       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 11      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 21      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 31      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 52      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 62      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = -393216 ;
          pstDmCfg->s32DcInSrc2Disp[1]             = -393216 ;
          pstDmCfg->s32DcInSrc2Disp[2]             = -393216 ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = 10279;//16384   ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = 5396; //0       ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 710;  //0       ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 1134; //0       ;
          pstDmCfg->s16M33Src2Disp[1][1]           = 15064;//16384   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = 187;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][0]           = 268;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 1442; //0       ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 14673;//16384   ;
          pstDmCfg->u16ScaleSrc2Disp               = 11      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
          pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
          pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
          pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 1536    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 1536    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 1536    ;
          pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
          pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
          pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
          pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
          pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
          pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 4095    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 4095    ;

          //RGB2YUV
          pstDmCfg->s16M33RGB2YUV[0][0]            = 3685 ;//2984    ; //BT709
          pstDmCfg->s16M33RGB2YUV[0][1]            = 9512 ;//10034   ;
          pstDmCfg->s16M33RGB2YUV[0][2]            = 832  ;//1013    ;
          pstDmCfg->s16M33RGB2YUV[1][0]            = -2004;//-1643   ;
          pstDmCfg->s16M33RGB2YUV[1][1]            = -5171;//-5531   ;
          pstDmCfg->s16M33RGB2YUV[1][2]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][0]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][1]            = -6598;//-6518   ;
          pstDmCfg->s16M33RGB2YUV[2][2]            = -577	;//-659    ;
          pstDmCfg->u16ScaleRGB2YUV                = 14      ;
          pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
          pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
          pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
          pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_XVYCC_PIP) //98mv200t test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_XVYCC_PIP\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 8       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 8       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 256     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 896     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 1536    ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 2176    ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 3520    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 3680    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 3840    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 4095    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 1       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 11      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 21      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 31      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 52      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 62      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = -393216 ;
          pstDmCfg->s32DcInSrc2Disp[1]             = -393216 ;
          pstDmCfg->s32DcInSrc2Disp[2]             = -393216 ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = 10279;//16384   ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = 5396; //0       ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 710;  //0       ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 1134; //0       ;
          pstDmCfg->s16M33Src2Disp[1][1]           = 15064;//16384   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = 187;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][0]           = 268;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 1442; //0       ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 14673;//16384   ;
          pstDmCfg->u16ScaleSrc2Disp               = 11      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ;//9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;//0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;//13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;//9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;//-1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;//-5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;//9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;//17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;//0       ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;

          pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
          pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
          pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 1536    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 1536    ;
          pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 1536    ;

          pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64     ;//-64     ;
          pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512    ;//-512    ;
          pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512    ;//-512    ;
          pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 1536    ;//0       ;
          pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 1536    ;//0       ;
          pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 1536    ;//0       ;

          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 4095    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 4095    ;

          //RGB2YUV
          pstDmCfg->s16M33RGB2YUV[0][0]            = 3685 ;//2984    ; //BT709
          pstDmCfg->s16M33RGB2YUV[0][1]            = 9512 ;//10034   ;
          pstDmCfg->s16M33RGB2YUV[0][2]            = 832  ;//1013    ;
          pstDmCfg->s16M33RGB2YUV[1][0]            = -2004;//-1643   ;
          pstDmCfg->s16M33RGB2YUV[1][1]            = -5171;//-5531   ;
          pstDmCfg->s16M33RGB2YUV[1][2]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][0]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][1]            = -6598;//-6518   ;
          pstDmCfg->s16M33RGB2YUV[2][2]            = -577	;//-659    ;
          pstDmCfg->u16ScaleRGB2YUV                = 14      ;
          pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
          pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
          pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
          pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT) //96mv200 test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 1 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ; //use BT2020
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = -14207  ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = -352    ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 30941   ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 27382   ;
          pstDmCfg->s16M33Src2Disp[1][1]           = -1761   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = -9238   ;
          pstDmCfg->s16M33Src2Disp[2][0]           = -2431   ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 18475   ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 342     ;
          pstDmCfg->u16ScaleSrc2Disp               = 14      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ; //use CL default coef
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_PIP_OUT) //96mv200 test ok!
      {
          VDP_PRINT("VdmSceneMode == VDM_SDR_BT2020CL_IN_BT709_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = pstCfg->vdm_v0_cl_en ;
          pstDmCfg->vdm_v1_cl_en                   = pstCfg->vdm_v1_cl_en ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = -14207  ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = -352    ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 30941   ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 27382   ;
          pstDmCfg->s16M33Src2Disp[1][1]           = -1761   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = -9238   ;
          pstDmCfg->s16M33Src2Disp[2][0]           = -2431   ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 18475   ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 342     ;
          pstDmCfg->u16ScaleSrc2Disp               = 14      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ; //use CL default coef
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;

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
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_SDR_IN_HDR10_OUT)
      {
          VDP_PRINT("VdmSceneMode == VDM_SDR_IN_HDR10_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ;
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 12      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0 ;//-393216 ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0 ;//-393216 ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0 ;//-393216 ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = 10279;//16384   ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = 5396; //0       ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 710;  //0       ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 1134; //0       ;
          pstDmCfg->s16M33Src2Disp[1][1]           = 15064;//16384   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = 187;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][0]           = 268;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 1442; //0       ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 14673;//16384   ;
          pstDmCfg->u16ScaleSrc2Disp               = 14      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 4095    ;

          //RGB2YUV
          pstDmCfg->s16M33RGB2YUV[0][0]            = 3685 ;//2984    ; //BT709
          pstDmCfg->s16M33RGB2YUV[0][1]            = 9512 ;//10034   ;
          pstDmCfg->s16M33RGB2YUV[0][2]            = 832  ;//1013    ;
          pstDmCfg->s16M33RGB2YUV[1][0]            = -2004;//-1643   ;
          pstDmCfg->s16M33RGB2YUV[1][1]            = -5171;//-5531   ;
          pstDmCfg->s16M33RGB2YUV[1][2]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][0]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][1]            = -6598;//-6518   ;
          pstDmCfg->s16M33RGB2YUV[2][2]            = -577	;//-659    ;
          pstDmCfg->u16ScaleRGB2YUV                = 14      ;
          pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
          pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
          pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
          pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_SDR_IN_HDR10_IN_HDR10_PIP_OUT)
      {
          VDP_PRINT("VdmSceneMode == VDM_SDR_IN_HDR10_IN_HDR10_PIP_OUT\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 1 ;
          pstDmCfg->vdm_degmm_en                   = 1 ;
          pstDmCfg->vdm_csc_en                     = 1 ;
          pstDmCfg->vdm_tmap_en                    = 1 ;
          pstDmCfg->vdm_gmm_en                     = 1 ;
          pstDmCfg->vdm_dither_en                  = 1 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = pstCfg->vdm_v0_csc_en ;
          pstDmCfg->vdm_v1_csc_en                  = pstCfg->vdm_v1_csc_en ;
          pstDmCfg->vdm_v0_gamma_en                = pstCfg->vdm_v0_gamma_en ;
          pstDmCfg->vdm_v1_gamma_en                = pstCfg->vdm_v1_gamma_en ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 0 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 8608    ;
          pstDmCfg->u16M3LumaCal[1]                = 22217   ;
          pstDmCfg->u16M3LumaCal[2]                = 1943    ;
          pstDmCfg->u16ScaleLumaCal                = 15      ;
          pstDmCfg->u16ScaleCoefTM                 = 12      ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0 ;//-393216 ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0 ;//-393216 ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0 ;//-393216 ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = 10279;//16384   ; //BT2020 to BT709
          pstDmCfg->s16M33Src2Disp[0][1]           = 5396; //0       ;
          pstDmCfg->s16M33Src2Disp[0][2]           = 710;  //0       ;
          pstDmCfg->s16M33Src2Disp[1][0]           = 1134; //0       ;
          pstDmCfg->s16M33Src2Disp[1][1]           = 15064;//16384   ;
          pstDmCfg->s16M33Src2Disp[1][2]           = 187;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][0]           = 268;  //0       ;
          pstDmCfg->s16M33Src2Disp[2][1]           = 1442; //0       ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 14673;//16384   ;
          pstDmCfg->u16ScaleSrc2Disp               = 14      ;
          pstDmCfg->u32ClipMinCSC                  = 0       ;
          pstDmCfg->u32ClipMaxCSC                  = 2097151 ;//0xFFFF0  1048575 ;

          //YUV2RGB
          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT709
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0       ;
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 14729   ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1752   ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -4379   ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17356   ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0       ;

          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567    ;//9567    ; //BT2020
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0       ;//0       ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729   ;//13792   ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567    ;//9567    ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752   ;//-1539   ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379   ;//-5344   ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567    ;//9567    ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356   ;//17597   ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0       ;//0       ;

          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023;//4095    ;

          //RGB2YUV
          pstDmCfg->s16M33RGB2YUV[0][0]            = 3685 ;//2984    ; //BT709
          pstDmCfg->s16M33RGB2YUV[0][1]            = 9512 ;//10034   ;
          pstDmCfg->s16M33RGB2YUV[0][2]            = 832  ;//1013    ;
          pstDmCfg->s16M33RGB2YUV[1][0]            = -2004;//-1643   ;
          pstDmCfg->s16M33RGB2YUV[1][1]            = -5171;//-5531   ;
          pstDmCfg->s16M33RGB2YUV[1][2]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][0]            = 7175 ;//7175    ;
          pstDmCfg->s16M33RGB2YUV[2][1]            = -6598;//-6518   ;
          pstDmCfg->s16M33RGB2YUV[2][2]            = -577	;//-659    ;
          pstDmCfg->u16ScaleRGB2YUV                = 14      ;
          pstDmCfg->s16InOffsetRGB2YUV[0]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[1]          = 0       ;
          pstDmCfg->s16InOffsetRGB2YUV[2]          = 0       ;
          pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
          pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
          pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 64      ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 64      ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 940     ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 960     ;

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
      else if(pstDmCfg->VdmSceneMode == VDM_BYPASS_MODE)
      {
          VDP_PRINT("VdmSceneMode == VDM_BYPASS_MODE\n");
          //typ mode

          // enable signal
          pstDmCfg->vdm_yuv2rgb_en                 = 1 ;
          pstDmCfg->vdm_en                         = 0 ;
          pstDmCfg->vdm_degmm_en                   = 0 ;
          pstDmCfg->vdm_csc_en                     = 0 ;
          pstDmCfg->vdm_tmap_en                    = 0 ;
          pstDmCfg->vdm_gmm_en                     = 0 ;
          pstDmCfg->vdm_dither_en                  = 0 ;
          pstDmCfg->vdm_rgb2yuv_en                 = 1 ;
          pstDmCfg->vdm_rgb2yuv_pip_en             = 1 ;

          pstDmCfg->vdm_v0_cl_en                   = 0 ;
          pstDmCfg->vdm_v1_cl_en                   = 0 ;
          pstDmCfg->vdm_cadj_en                    = 0 ;

          pstDmCfg->vdm_v0_csc_en                  = 1 ;
          pstDmCfg->vdm_v1_csc_en                  = 0 ;
          pstDmCfg->vdm_v0_gamma_en                = 1 ;
          pstDmCfg->vdm_v1_gamma_en                = 0 ;

          // ctrl signal
          pstDmCfg->vdm_csc_bind                        = 1 ;// 0:csc->tmap, 1:tmap->csc
          pstDmCfg->stDitherCfg.u32_dither_round        = 1 ;// 0:dither, 1:round
          pstDmCfg->stDitherCfg.u32_dither_domain_mode  = 0 ;// 1
          pstDmCfg->stDitherCfg.u32_dither_tap_mode     = 0 ;
          pstDmCfg->stDitherCfg.u32_dither_round_unlim  = 0 ;

          // cfg
          pstDmCfg->u16M3LumaCal[0]                = 1076    ;
          pstDmCfg->u16M3LumaCal[1]                = 2777    ;
          pstDmCfg->u16M3LumaCal[2]                = 243     ;
          pstDmCfg->u16ScaleLumaCal                = 12      ;
          pstDmCfg->u16ScaleCoefTM                 = 8       ;
          pstDmCfg->u16ScaleCoefSM                 = 8       ;
          pstDmCfg->u32ClipMinTM                   = 0       ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
          pstDmCfg->s32TMOff0                      = 0       ;
          pstDmCfg->s32TMOff1                      = 0       ;
          pstDmCfg->s32TMOff2                      = 0       ;

          pstDmCfg->DePQPara.gmm_x1_step           = 6       ;
          pstDmCfg->DePQPara.gmm_x2_step           = 5       ;
          pstDmCfg->DePQPara.gmm_x3_step           = 4       ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3       ;
          pstDmCfg->DePQPara.gmm_x5_step           = 2       ;
          pstDmCfg->DePQPara.gmm_x6_step           = 1       ;
          pstDmCfg->DePQPara.gmm_x7_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x8_step           = 0       ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 384     ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 704     ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 816     ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 944     ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 1016    ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 1020    ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 1023    ;
          pstDmCfg->DePQPara.gmm_x1_num            = 6       ;
          pstDmCfg->DePQPara.gmm_x2_num            = 16      ;
          pstDmCfg->DePQPara.gmm_x3_num            = 23      ;
          pstDmCfg->DePQPara.gmm_x4_num            = 39      ;
          pstDmCfg->DePQPara.gmm_x5_num            = 57      ;
          pstDmCfg->DePQPara.gmm_x6_num            = 59      ;
          pstDmCfg->DePQPara.gmm_x7_num            = 63      ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63      ;

          pstDmCfg->TMPara.gmm_x1_step             = 5       ;
          pstDmCfg->TMPara.gmm_x2_step             = 7       ;
          pstDmCfg->TMPara.gmm_x3_step             = 9       ;
          pstDmCfg->TMPara.gmm_x4_step             = 10      ;
          pstDmCfg->TMPara.gmm_x5_step             = 11      ;
          pstDmCfg->TMPara.gmm_x6_step             = 13      ;
          pstDmCfg->TMPara.gmm_x7_step             = 15      ;
          pstDmCfg->TMPara.gmm_x8_step             = 17      ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->TMPara.gmm_x1_num              = 4       ;
          pstDmCfg->TMPara.gmm_x2_num              = 11      ;
          pstDmCfg->TMPara.gmm_x3_num              = 13      ;
          pstDmCfg->TMPara.gmm_x4_num              = 17      ;
          pstDmCfg->TMPara.gmm_x5_num              = 22      ;
          pstDmCfg->TMPara.gmm_x6_num              = 36      ;
          pstDmCfg->TMPara.gmm_x7_num              = 52      ;
          pstDmCfg->TMPara.gmm_x8_num              = 63      ;

          pstDmCfg->SMPara.gmm_x1_step             = 5       ;
          pstDmCfg->SMPara.gmm_x2_step             = 7       ;
          pstDmCfg->SMPara.gmm_x3_step             = 9       ;
          pstDmCfg->SMPara.gmm_x4_step             = 10      ;
          pstDmCfg->SMPara.gmm_x5_step             = 11      ;
          pstDmCfg->SMPara.gmm_x6_step             = 13      ;
          pstDmCfg->SMPara.gmm_x7_step             = 15      ;
          pstDmCfg->SMPara.gmm_x8_step             = 17      ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128     ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024    ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048    ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144    ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384   ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072  ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360  ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151 ;
          pstDmCfg->SMPara.gmm_x1_num              = 4       ;
          pstDmCfg->SMPara.gmm_x2_num              = 11      ;
          pstDmCfg->SMPara.gmm_x3_num              = 13      ;
          pstDmCfg->SMPara.gmm_x4_num              = 17      ;
          pstDmCfg->SMPara.gmm_x5_num              = 22      ;
          pstDmCfg->SMPara.gmm_x6_num              = 36      ;
          pstDmCfg->SMPara.gmm_x7_num              = 52      ;
          pstDmCfg->SMPara.gmm_x8_num              = 63      ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5       ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7       ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9       ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10      ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11      ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13      ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15      ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17      ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128     ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024    ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048    ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144    ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384   ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072  ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360  ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151 ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4       ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11      ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13      ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17      ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22      ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36      ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52      ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63      ;

          pstDmCfg->s32DcInSrc2Disp[0]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[1]             = 0   ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = 0   ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = 0   ;
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
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13      ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13      ;
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
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023    ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0       ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023    ;
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
          pstDmCfg->u16ClipMinRGB2YUV_Y              = 0       ;
          pstDmCfg->u16ClipMinRGB2YUV_C              = 0       ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y              = 1023    ;
          pstDmCfg->u16ClipMaxRGB2YUV_C              = 1023    ;


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
      else
      {
          VDP_PRINT("VDP_FUNC_SetVdmMode enter into typ mode\n");

          pstDmCfg->u16M3LumaCal[0]                = 8608       ;
          pstDmCfg->u16M3LumaCal[1]                = 22217      ;
          pstDmCfg->u16M3LumaCal[2]                = 1943       ;
          pstDmCfg->u16ScaleLumaCal                = 15         ;
          pstDmCfg->u16ScaleCoefTM                 = 15         ;
          pstDmCfg->u16ScaleCoefSM                 = 10         ;
          pstDmCfg->u32ClipMinTM                   = 0          ;
          pstDmCfg->u32ClipMaxTM                   = (1<<21)-1  ;
          pstDmCfg->s32TMOff0                      = 514        ;
          pstDmCfg->s32TMOff1                      = 514        ;
          pstDmCfg->s32TMOff2                      = 514        ;

          pstDmCfg->DePQPara.gmm_x1_step           = 8          ;//6          ;
          pstDmCfg->DePQPara.gmm_x2_step           = 3          ;//4          ;
          pstDmCfg->DePQPara.gmm_x3_step           = 6          ;//2          ;
          pstDmCfg->DePQPara.gmm_x4_step           = 3          ;//0          ;
          pstDmCfg->DePQPara.gmm_x5_step           = 8          ;//0          ;
          pstDmCfg->DePQPara.gmm_x6_step           = 6          ;//0          ;
          pstDmCfg->DePQPara.gmm_x7_step           = 3          ;//0          ;
          pstDmCfg->DePQPara.gmm_x8_step           = 7          ;//0          ;
          pstDmCfg->DePQPara.gmm_x1_pos            = 1024       ;//512        ;
          pstDmCfg->DePQPara.gmm_x2_pos            = 1032       ;//928        ;
          pstDmCfg->DePQPara.gmm_x3_pos            = 1480       ;//1020       ;
          pstDmCfg->DePQPara.gmm_x4_pos            = 1528       ;//1023       ;
          pstDmCfg->DePQPara.gmm_x5_pos            = 2808       ;//1023       ;
          pstDmCfg->DePQPara.gmm_x6_pos            = 2936       ;//1023       ;
          pstDmCfg->DePQPara.gmm_x7_pos            = 3184       ;//1023       ;
          pstDmCfg->DePQPara.gmm_x8_pos            = 4080       ;//1023       ;
          pstDmCfg->DePQPara.gmm_x1_num            = 4          ;//8          ;
          pstDmCfg->DePQPara.gmm_x2_num            = 5          ;//34         ;
          pstDmCfg->DePQPara.gmm_x3_num            = 12         ;//57         ;
          pstDmCfg->DePQPara.gmm_x4_num            = 18         ;//61         ;
          pstDmCfg->DePQPara.gmm_x5_num            = 23         ;//61         ;
          pstDmCfg->DePQPara.gmm_x6_num            = 25         ;//61         ;
          pstDmCfg->DePQPara.gmm_x7_num            = 56         ;//61         ;
          pstDmCfg->DePQPara.gmm_x8_num            = 63         ;//61         ;

          pstDmCfg->TMPara.gmm_x1_step             = 5          ;
          pstDmCfg->TMPara.gmm_x2_step             = 7          ;
          pstDmCfg->TMPara.gmm_x3_step             = 9          ;
          pstDmCfg->TMPara.gmm_x4_step             = 10         ;
          pstDmCfg->TMPara.gmm_x5_step             = 11         ;
          pstDmCfg->TMPara.gmm_x6_step             = 13         ;
          pstDmCfg->TMPara.gmm_x7_step             = 15         ;
          pstDmCfg->TMPara.gmm_x8_step             = 17         ;
          pstDmCfg->TMPara.gmm_x1_pos              = 128        ;
          pstDmCfg->TMPara.gmm_x2_pos              = 1024       ;
          pstDmCfg->TMPara.gmm_x3_pos              = 2048       ;
          pstDmCfg->TMPara.gmm_x4_pos              = 6144       ;
          pstDmCfg->TMPara.gmm_x5_pos              = 16384      ;
          pstDmCfg->TMPara.gmm_x6_pos              = 131072     ;
          pstDmCfg->TMPara.gmm_x7_pos              = 655360     ;
          pstDmCfg->TMPara.gmm_x8_pos              = 2097151    ;
          pstDmCfg->TMPara.gmm_x1_num              = 4          ;
          pstDmCfg->TMPara.gmm_x2_num              = 11         ;
          pstDmCfg->TMPara.gmm_x3_num              = 13         ;
          pstDmCfg->TMPara.gmm_x4_num              = 17         ;
          pstDmCfg->TMPara.gmm_x5_num              = 22         ;
          pstDmCfg->TMPara.gmm_x6_num              = 36         ;
          pstDmCfg->TMPara.gmm_x7_num              = 52         ;
          pstDmCfg->TMPara.gmm_x8_num              = 63         ;

          pstDmCfg->SMPara.gmm_x1_step             = 5          ;
          pstDmCfg->SMPara.gmm_x2_step             = 7          ;
          pstDmCfg->SMPara.gmm_x3_step             = 9          ;
          pstDmCfg->SMPara.gmm_x4_step             = 10         ;
          pstDmCfg->SMPara.gmm_x5_step             = 11         ;
          pstDmCfg->SMPara.gmm_x6_step             = 13         ;
          pstDmCfg->SMPara.gmm_x7_step             = 15         ;
          pstDmCfg->SMPara.gmm_x8_step             = 17         ;
          pstDmCfg->SMPara.gmm_x1_pos              = 128        ;
          pstDmCfg->SMPara.gmm_x2_pos              = 1024       ;
          pstDmCfg->SMPara.gmm_x3_pos              = 2048       ;
          pstDmCfg->SMPara.gmm_x4_pos              = 6144       ;
          pstDmCfg->SMPara.gmm_x5_pos              = 16384      ;
          pstDmCfg->SMPara.gmm_x6_pos              = 131072     ;
          pstDmCfg->SMPara.gmm_x7_pos              = 655360     ;
          pstDmCfg->SMPara.gmm_x8_pos              = 2097151    ;
          pstDmCfg->SMPara.gmm_x1_num              = 4          ;
          pstDmCfg->SMPara.gmm_x2_num              = 11         ;
          pstDmCfg->SMPara.gmm_x3_num              = 13         ;
          pstDmCfg->SMPara.gmm_x4_num              = 17         ;
          pstDmCfg->SMPara.gmm_x5_num              = 22         ;
          pstDmCfg->SMPara.gmm_x6_num              = 36         ;
          pstDmCfg->SMPara.gmm_x7_num              = 52         ;
          pstDmCfg->SMPara.gmm_x8_num              = 63         ;

          pstDmCfg->GammaPara.gmm_x1_step          = 5          ;
          pstDmCfg->GammaPara.gmm_x2_step          = 7          ;
          pstDmCfg->GammaPara.gmm_x3_step          = 9          ;
          pstDmCfg->GammaPara.gmm_x4_step          = 10         ;
          pstDmCfg->GammaPara.gmm_x5_step          = 11         ;
          pstDmCfg->GammaPara.gmm_x6_step          = 13         ;
          pstDmCfg->GammaPara.gmm_x7_step          = 15         ;
          pstDmCfg->GammaPara.gmm_x8_step          = 17         ;
          pstDmCfg->GammaPara.gmm_x1_pos           = 128        ;
          pstDmCfg->GammaPara.gmm_x2_pos           = 1024       ;
          pstDmCfg->GammaPara.gmm_x3_pos           = 2048       ;
          pstDmCfg->GammaPara.gmm_x4_pos           = 6144       ;
          pstDmCfg->GammaPara.gmm_x5_pos           = 16384      ;
          pstDmCfg->GammaPara.gmm_x6_pos           = 131072     ;
          pstDmCfg->GammaPara.gmm_x7_pos           = 655360     ;
          pstDmCfg->GammaPara.gmm_x8_pos           = 2097151    ;
          pstDmCfg->GammaPara.gmm_x1_num           = 4          ;
          pstDmCfg->GammaPara.gmm_x2_num           = 11         ;
          pstDmCfg->GammaPara.gmm_x3_num           = 13         ;
          pstDmCfg->GammaPara.gmm_x4_num           = 17         ;
          pstDmCfg->GammaPara.gmm_x5_num           = 22         ;
          pstDmCfg->GammaPara.gmm_x6_num           = 36         ;
          pstDmCfg->GammaPara.gmm_x7_num           = 52         ;
          pstDmCfg->GammaPara.gmm_x8_num           = 63         ;

          pstDmCfg->s32DcInSrc2Disp[0]             = -512       ;
          pstDmCfg->s32DcInSrc2Disp[1]             = -512       ;
          pstDmCfg->s32DcInSrc2Disp[2]             = 512        ;
          pstDmCfg->s32DcOutSrc2Disp[0]            = 512        ;
          pstDmCfg->s32DcOutSrc2Disp[1]            = -512       ;
          pstDmCfg->s32DcOutSrc2Disp[2]            = -512       ;
          pstDmCfg->s16M33Src2Disp[0][0]           = 27209      ;
          pstDmCfg->s16M33Src2Disp[0][1]           = -9632      ;
          pstDmCfg->s16M33Src2Disp[0][2]           = -1194      ;
          pstDmCfg->s16M33Src2Disp[1][0]           = -2045      ;
          pstDmCfg->s16M33Src2Disp[1][1]           = 18565      ;
          pstDmCfg->s16M33Src2Disp[1][2]           = -138       ;
          pstDmCfg->s16M33Src2Disp[2][0]           = -297       ;
          pstDmCfg->s16M33Src2Disp[2][1]           = -1648      ;
          pstDmCfg->s16M33Src2Disp[2][2]           = 18330      ;
          pstDmCfg->u16ScaleSrc2Disp               = 14         ;
          pstDmCfg->u32ClipMinCSC                  = 0          ;
          pstDmCfg->u32ClipMaxCSC                  = (1<<21)-1  ;

          pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB0[0][1]           = 0          ;
          pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792      ;
          pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539      ;
          pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344      ;
          pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597      ;
          pstDmCfg->s16M33YUV2RGB0[2][2]           = 0          ;
          pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB1[0][1]           = 0          ;
          pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729      ;
          pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752      ;
          pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379      ;
          pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567       ;
          pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356      ;
          pstDmCfg->s16M33YUV2RGB1[2][2]           = 0          ;
          pstDmCfg->u16ScaleYUV2RGB_v0             = 13         ;
          pstDmCfg->u16ScaleYUV2RGB_v1             = 13         ;
          pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64        ;
          pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512       ;
          pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512       ;
          pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0          ;
          pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0          ;
          pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0          ;
          pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64        ;
          pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512       ;
          pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512       ;
          pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0          ;
          pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0          ;
          pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0          ;
          pstDmCfg->u16ClipMinYUV2RGB_v0           = 0          ;
          pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023       ;
          pstDmCfg->u16ClipMinYUV2RGB_v1           = 0          ;
          pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023       ;
          pstDmCfg->s16M33RGB2YUV[0][0]            = 2984       ;
          pstDmCfg->s16M33RGB2YUV[0][1]            = 10034      ;
          pstDmCfg->s16M33RGB2YUV[0][2]            = 1013       ;
          pstDmCfg->s16M33RGB2YUV[1][0]            = -1643      ;
          pstDmCfg->s16M33RGB2YUV[1][1]            = -5531      ;
          pstDmCfg->s16M33RGB2YUV[1][2]            = 7175       ;
          pstDmCfg->s16M33RGB2YUV[2][0]            = 7175       ;
          pstDmCfg->s16M33RGB2YUV[2][1]            = -6518      ;
          pstDmCfg->s16M33RGB2YUV[2][2]            = -659       ;
          pstDmCfg->u16ScaleRGB2YUV                = 14         ;
          pstDmCfg->s16InOffsetRGB2YUV[0]          = 0          ;
          pstDmCfg->s16InOffsetRGB2YUV[1]          = 0          ;
          pstDmCfg->s16InOffsetRGB2YUV[2]          = 0          ;
          pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64         ;
          pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512        ;
          pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512        ;
          pstDmCfg->u16ClipMinRGB2YUV_Y            = 0          ;
          pstDmCfg->u16ClipMinRGB2YUV_C            = 0          ;
          pstDmCfg->u16ClipMaxRGB2YUV_Y            = 1023       ;
          pstDmCfg->u16ClipMaxRGB2YUV_C            = 1023       ;


          pstDmCfg->stDitherCfg.u32_dither_thr_max = 32767      ;
          pstDmCfg->stDitherCfg.u32_dither_thr_min = 255        ;
          pstDmCfg->stDitherCfg.u32_dither_sed_y0  = 2140000000 ; //31'h7fffffff ;
          pstDmCfg->stDitherCfg.u32_dither_sed_u0  = 2140000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_v0  = 2140000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_w0  = 2140000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_y1  = 1500000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_u1  = 1500000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_v1  = 1500000000 ;
          pstDmCfg->stDitherCfg.u32_dither_sed_w1  = 1500000000 ;
      }
  }
    else if(VdmMode == VDP_VID_VDM_TYP1)
	{
		VDP_PRINT("VDP_FUNC_SetVdmMode enter into typ1 mode\n");

        pstDmCfg->u16M3LumaCal[0]                = 8608       ;
        pstDmCfg->u16M3LumaCal[1]                = 22217      ;
        pstDmCfg->u16M3LumaCal[2]                = 1943       ;
        pstDmCfg->u16ScaleLumaCal                = 15         ;
        pstDmCfg->u16ScaleCoefTM                 = 15         ;
        pstDmCfg->u32ClipMinTM                   = 0          ;
        pstDmCfg->u32ClipMaxTM                   = (1<<21)-1  ;
        pstDmCfg->s32TMOff0                      = 514        ;
        pstDmCfg->s32TMOff1                      = 514        ;
        pstDmCfg->s32TMOff2                      = 514        ;

        pstDmCfg->DePQPara.gmm_x1_step           = 8          ;
        pstDmCfg->DePQPara.gmm_x2_step           = 3          ;
        pstDmCfg->DePQPara.gmm_x3_step           = 6          ;
        pstDmCfg->DePQPara.gmm_x4_step           = 3          ;
        pstDmCfg->DePQPara.gmm_x5_step           = 8          ;
        pstDmCfg->DePQPara.gmm_x6_step           = 6          ;
        pstDmCfg->DePQPara.gmm_x7_step           = 3          ;
        pstDmCfg->DePQPara.gmm_x8_step           = 7          ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 1024       ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 1032       ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 1480       ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1528       ;
        pstDmCfg->DePQPara.gmm_x5_pos            = 2808       ;
        pstDmCfg->DePQPara.gmm_x6_pos            = 2936       ;
        pstDmCfg->DePQPara.gmm_x7_pos            = 3184       ;
        pstDmCfg->DePQPara.gmm_x8_pos            = 4080       ;
        pstDmCfg->DePQPara.gmm_x1_num            = 4          ;
        pstDmCfg->DePQPara.gmm_x2_num            = 5          ;
        pstDmCfg->DePQPara.gmm_x3_num            = 12         ;
        pstDmCfg->DePQPara.gmm_x4_num            = 18         ;
        pstDmCfg->DePQPara.gmm_x5_num            = 23         ;
        pstDmCfg->DePQPara.gmm_x6_num            = 25         ;
        pstDmCfg->DePQPara.gmm_x7_num            = 56         ;
        pstDmCfg->DePQPara.gmm_x8_num            = 63         ;

        pstDmCfg->TMPara.gmm_x1_step             = 5          ;
        pstDmCfg->TMPara.gmm_x2_step             = 7          ;
        pstDmCfg->TMPara.gmm_x3_step             = 9          ;
        pstDmCfg->TMPara.gmm_x4_step             = 10         ;
        pstDmCfg->TMPara.gmm_x5_step             = 11         ;
        pstDmCfg->TMPara.gmm_x6_step             = 13         ;
        pstDmCfg->TMPara.gmm_x7_step             = 15         ;
        pstDmCfg->TMPara.gmm_x8_step             = 17         ;
        pstDmCfg->TMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->TMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->TMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->TMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->TMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->TMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->TMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->TMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->TMPara.gmm_x1_num              = 4          ;
        pstDmCfg->TMPara.gmm_x2_num              = 11         ;
        pstDmCfg->TMPara.gmm_x3_num              = 13         ;
        pstDmCfg->TMPara.gmm_x4_num              = 17         ;
        pstDmCfg->TMPara.gmm_x5_num              = 22         ;
        pstDmCfg->TMPara.gmm_x6_num              = 36         ;
        pstDmCfg->TMPara.gmm_x7_num              = 52         ;
        pstDmCfg->TMPara.gmm_x8_num              = 63         ;

        pstDmCfg->SMPara.gmm_x1_step             = 5          ;
        pstDmCfg->SMPara.gmm_x2_step             = 7          ;
        pstDmCfg->SMPara.gmm_x3_step             = 9          ;
        pstDmCfg->SMPara.gmm_x4_step             = 10         ;
        pstDmCfg->SMPara.gmm_x5_step             = 11         ;
        pstDmCfg->SMPara.gmm_x6_step             = 13         ;
        pstDmCfg->SMPara.gmm_x7_step             = 15         ;
        pstDmCfg->SMPara.gmm_x8_step             = 17         ;
        pstDmCfg->SMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->SMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->SMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->SMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->SMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->SMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->SMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->SMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->SMPara.gmm_x1_num              = 4          ;
        pstDmCfg->SMPara.gmm_x2_num              = 11         ;
        pstDmCfg->SMPara.gmm_x3_num              = 13         ;
        pstDmCfg->SMPara.gmm_x4_num              = 17         ;
        pstDmCfg->SMPara.gmm_x5_num              = 22         ;
        pstDmCfg->SMPara.gmm_x6_num              = 36         ;
        pstDmCfg->SMPara.gmm_x7_num              = 52         ;
        pstDmCfg->SMPara.gmm_x8_num              = 63         ;

        pstDmCfg->GammaPara.gmm_x1_step          = 5          ;
        pstDmCfg->GammaPara.gmm_x2_step          = 7          ;
        pstDmCfg->GammaPara.gmm_x3_step          = 9          ;
        pstDmCfg->GammaPara.gmm_x4_step          = 10         ;
        pstDmCfg->GammaPara.gmm_x5_step          = 11         ;
        pstDmCfg->GammaPara.gmm_x6_step          = 13         ;
        pstDmCfg->GammaPara.gmm_x7_step          = 15         ;
        pstDmCfg->GammaPara.gmm_x8_step          = 17         ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 128        ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 1024       ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 2048       ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 6144       ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 16384      ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 131072     ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 655360     ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 2097151    ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4          ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11         ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13         ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17         ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22         ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36         ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52         ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63         ;

        pstDmCfg->s32DcInSrc2Disp[0]             = -512       ;
        pstDmCfg->s32DcInSrc2Disp[1]             = -512       ;
        pstDmCfg->s32DcInSrc2Disp[2]             = 512        ;
        pstDmCfg->s32DcOutSrc2Disp[0]            = 512        ;
        pstDmCfg->s32DcOutSrc2Disp[1]            = -512       ;
        pstDmCfg->s32DcOutSrc2Disp[2]            = -512       ;
        pstDmCfg->s16M33Src2Disp[0][0]           = 27209      ;
        pstDmCfg->s16M33Src2Disp[0][1]           = -9632      ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -1194      ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -2045      ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 18565      ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -138       ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -297       ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -1648      ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 18330      ;
        pstDmCfg->u16ScaleSrc2Disp               = 14         ;
        pstDmCfg->u32ClipMinCSC                  = 0          ;
        pstDmCfg->u32ClipMaxCSC                  = (1<<21)-1  ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0          ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 13792      ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -1539      ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -5344      ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 17597      ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0          ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0          ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 14729      ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -1752      ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -4379      ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 9567       ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 17356      ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0          ;
        pstDmCfg->u16ScaleYUV2RGB_v0             = 13         ;
        pstDmCfg->u16ScaleYUV2RGB_v1             = 13         ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -64        ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -512       ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -512       ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0          ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0          ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0          ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -64        ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -512       ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -512       ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0          ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0          ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0          ;
        pstDmCfg->u16ClipMinYUV2RGB_v0           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023       ;
        pstDmCfg->u16ClipMinYUV2RGB_v1           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023       ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 2984       ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = 10034      ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 1013       ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -1643      ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -5531      ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 7175       ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 7175       ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -6518      ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -659       ;
        pstDmCfg->u16ScaleRGB2YUV                = 14         ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0          ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0          ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0          ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 64         ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 512        ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 512        ;
        pstDmCfg->u16ClipMinRGB2YUV_Y            = 0          ;
        pstDmCfg->u16ClipMinRGB2YUV_C            = 0          ;
        pstDmCfg->u16ClipMaxRGB2YUV_Y            = 1023       ;
        pstDmCfg->u16ClipMaxRGB2YUV_C            = 1023       ;
        pstDmCfg->u16ScaleCoefSM                 = 10         ;


        pstDmCfg->stDitherCfg.u32_dither_thr_max = 32767      ;
        pstDmCfg->stDitherCfg.u32_dither_thr_min = 255        ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0  = 2140000000 ; //31'h7fffffff ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0  = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0  = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0  = 2140000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1  = 1500000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1  = 1500000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1  = 1500000000 ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1  = 1500000000 ;
    }
    else if(VdmMode == VDP_VID_VDM_RAND)
	{
		VDP_PRINT("VDP_FUNC_SetVdmMode enter into rand mode\n");
		//rand mode
        pstDmCfg->u16M3LumaCal[0]                = sGetRandEx( 0  , (1<<16)-1)    ;
        pstDmCfg->u16M3LumaCal[1]                = sGetRandEx( 0  , (1<<16)-1)    ;
        pstDmCfg->u16M3LumaCal[2]                = sGetRandEx( 0  , (1<<16)-1)    ;
        pstDmCfg->u16ScaleLumaCal                = sGetRandEx( 1  , 15  )    ;
        pstDmCfg->u16ScaleCoefTM                 = sGetRandEx( 1  , 15  )    ;
        pstDmCfg->u32ClipMinTM                   = sGetRandEx( 0  , (1<<9))   ;
        pstDmCfg->u32ClipMaxTM                   = sGetRandEx( (1<<18), (1<<21)-1)   ;
        pstDmCfg->s32TMOff0                      = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32TMOff1                      = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32TMOff2                      = sGetRandEx(-(1<<20),(1<<20)-1);

        degamm_pos8 = (1<<12)-1;//i_bdp
        tmap_pos8   = (1<<21)-1;
        smap_pos8   = (1<<21)-1;
        gamm_pos8   = (1<<21)-1;

        while(1)
        {
            degamma_num_sum7 = degamm_num1+degamm_num2+degamm_num3+degamm_num4+degamm_num5+degamm_num6+degamm_num7;
            if( (degamma_num_sum7>0) && (degamma_num_sum7<63) && (degamm_rand_cnt<=1000) )
            {
                degamm_rand_cnt++;
                degamm_num8=63-degamma_num_sum7;
                degamm_step1 = sGetRandEx( 0  , 9  );//12-3
                degamm_step2 = sGetRandEx( 0  , 9  );
                degamm_step3 = sGetRandEx( 0  , 9  );
                degamm_step4 = sGetRandEx( 0  , 9  );
                degamm_step5 = sGetRandEx( 0  , 9  );
                degamm_step6 = sGetRandEx( 0  , 9  );
                degamm_step7 = sGetRandEx( 0  , 9  );
                degamm_step8 = sGetRandEx( 0  , 9  );

                degamm_pos1 = degamm_num1*(1<<degamm_step1);
                degamm_pos2 = degamm_pos1+degamm_num2*(1<<degamm_step2);
                degamm_pos3 = degamm_pos2+degamm_num3*(1<<degamm_step3);
                degamm_pos4 = degamm_pos3+degamm_num4*(1<<degamm_step4);
                degamm_pos5 = degamm_pos4+degamm_num5*(1<<degamm_step5);
                degamm_pos6 = degamm_pos5+degamm_num6*(1<<degamm_step6);
                degamm_pos7 = degamm_pos6+degamm_num7*(1<<degamm_step7);
                degamm_pos8 = degamm_pos7+degamm_num8*(1<<degamm_step8);

                if(((1<<12)-degamm_pos8>0) && ((1<<12)-degamm_pos8 <= (1<<degamm_step8)))//degmm_in:12bit
                    break;
                if(degamm_rand_cnt == 1000)
                    VDP_PRINT("degamm random data not OK !\n");
            }
            else
            {
                degamm_rand_cnt = 0;
                degamm_num1 = sGetRandEx( 1  , 56  );//63-(8-1)
                degamm_num2 = sGetRandEx( 1  , 56  );
                degamm_num3 = sGetRandEx( 1  , 56  );
                degamm_num4 = sGetRandEx( 1  , 56  );
                degamm_num5 = sGetRandEx( 1  , 56  );
                degamm_num6 = sGetRandEx( 1  , 56  );
                degamm_num7 = sGetRandEx( 1  , 56  );
                continue;
            }

        }

        while(1)
        {
            tmap_num_sum7 = tmap_num1+tmap_num2+tmap_num3+tmap_num4+tmap_num5+tmap_num6+tmap_num7;
            if( (tmap_num_sum7>0) && (tmap_num_sum7<63) && (tmap_rand_cnt<=1000) )
            {
                tmap_rand_cnt++;
                tmap_num8=63-tmap_num_sum7;
                tmap_step1 = sGetRandEx( 0  , 18  );//21-3
                tmap_step2 = sGetRandEx( 0  , 18  );
                tmap_step3 = sGetRandEx( 0  , 18  );
                tmap_step4 = sGetRandEx( 0  , 18  );
                tmap_step5 = sGetRandEx( 0  , 18  );
                tmap_step6 = sGetRandEx( 0  , 18  );
                tmap_step7 = sGetRandEx( 0  , 18  );
                tmap_step8 = sGetRandEx( 0  , 18  );

                tmap_pos1 = tmap_num1*(1<<tmap_step1);
                tmap_pos2 = tmap_pos1+tmap_num2*(1<<tmap_step2);
                tmap_pos3 = tmap_pos2+tmap_num3*(1<<tmap_step3);
                tmap_pos4 = tmap_pos3+tmap_num4*(1<<tmap_step4);
                tmap_pos5 = tmap_pos4+tmap_num5*(1<<tmap_step5);
                tmap_pos6 = tmap_pos5+tmap_num6*(1<<tmap_step6);
                tmap_pos7 = tmap_pos6+tmap_num7*(1<<tmap_step7);
                tmap_pos8 = tmap_pos7+tmap_num8*(1<<tmap_step8);

                if(((1<<21)-tmap_pos8>0) && ((1<<21)-tmap_pos8 <= (1<<tmap_step8)))//tmap_in:21bit
                {
#if 0
                    VDP_PRINT("tmap_num1=%d,tmap_num2=%d,tmap_num3=%d,tmap_num4=%d\n",tmap_num1,tmap_num2,tmap_num3,tmap_num4);
                    VDP_PRINT("tmap_num5=%d,tmap_num6=%d,tmap_num7=%d,tmap_num8=%d\n",tmap_num5,tmap_num6,tmap_num7,tmap_num8);
                    VDP_PRINT("tmap_step1=%d,tmap_step2=%d,tmap_step3=%d,tmap_step4=%d\n",tmap_step1,tmap_step2,tmap_step3,tmap_step4);
                    VDP_PRINT("tmap_step5=%d,tmap_step6=%d,tmap_step7=%d,tmap_step8=%d\n\n",tmap_step5,tmap_step6,tmap_step7,tmap_step8);
#endif
                    break;
                }
                if(tmap_rand_cnt == 1000)
                    VDP_PRINT("tmap random data not OK !\n");
            }
            else
            {
                tmap_rand_cnt = 0;
                tmap_num1 = sGetRandEx( 1  , 56  );//63-(8-1)
                tmap_num2 = sGetRandEx( 1  , 56  );
                tmap_num3 = sGetRandEx( 1  , 56  );
                tmap_num4 = sGetRandEx( 1  , 56  );
                tmap_num5 = sGetRandEx( 1  , 56  );
                tmap_num6 = sGetRandEx( 1  , 56  );
                tmap_num7 = sGetRandEx( 1  , 56  );
                continue;
            }
        }

        while(1)
        {
            smap_num_sum7 = smap_num1+smap_num2+smap_num3+smap_num4+smap_num5+smap_num6+smap_num7;
            if( (smap_num_sum7>0) && (smap_num_sum7<63) && (smap_rand_cnt<=1000) )
            {
                smap_rand_cnt++;
                smap_num8=63-smap_num_sum7;
                smap_step1 = sGetRandEx( 0  , 18  );//21-3
                smap_step2 = sGetRandEx( 0  , 18  );
                smap_step3 = sGetRandEx( 0  , 18  );
                smap_step4 = sGetRandEx( 0  , 18  );
                smap_step5 = sGetRandEx( 0  , 18  );
                smap_step6 = sGetRandEx( 0  , 18  );
                smap_step7 = sGetRandEx( 0  , 18  );
                smap_step8 = sGetRandEx( 0  , 18  );

                smap_pos1 = smap_num1*(1<<smap_step1);
                smap_pos2 = smap_pos1+smap_num2*(1<<smap_step2);
                smap_pos3 = smap_pos2+smap_num3*(1<<smap_step3);
                smap_pos4 = smap_pos3+smap_num4*(1<<smap_step4);
                smap_pos5 = smap_pos4+smap_num5*(1<<smap_step5);
                smap_pos6 = smap_pos5+smap_num6*(1<<smap_step6);
                smap_pos7 = smap_pos6+smap_num7*(1<<smap_step7);
                smap_pos8 = smap_pos7+smap_num8*(1<<smap_step8);

                if(((1<<21)-smap_pos8>0) && ((1<<21)-smap_pos8 <= (1<<smap_step8)))//smap_in:21bit
                {
#if 0
                    VDP_PRINT("smap_num1=%d,smap_num2=%d,smap_num3=%d,smap_num4=%d\n",smap_num1,smap_num2,smap_num3,smap_num4);
                    VDP_PRINT("smap_num5=%d,smap_num6=%d,smap_num7=%d,smap_num8=%d\n",smap_num5,smap_num6,smap_num7,smap_num8);
                    VDP_PRINT("smap_step1=%d,smap_step2=%d,smap_step3=%d,smap_step4=%d\n",smap_step1,smap_step2,smap_step3,smap_step4);
                    VDP_PRINT("smap_step5=%d,smap_step6=%d,smap_step7=%d,smap_step8=%d\n\n",smap_step5,smap_step6,smap_step7,smap_step8);
#endif
                    break;
                }
                if(smap_rand_cnt == 1000)
                    VDP_PRINT("smap random data not OK !\n");
            }
            else
            {
                smap_rand_cnt = 0;
                smap_num1 = sGetRandEx( 1  , 56  );//63-(8-1)
                smap_num2 = sGetRandEx( 1  , 56  );
                smap_num3 = sGetRandEx( 1  , 56  );
                smap_num4 = sGetRandEx( 1  , 56  );
                smap_num5 = sGetRandEx( 1  , 56  );
                smap_num6 = sGetRandEx( 1  , 56  );
                smap_num7 = sGetRandEx( 1  , 56  );
                continue;
            }
        }


        while(1)
        {
            gamm_num_sum7 = gamm_num1+gamm_num2+gamm_num3+gamm_num4+gamm_num5+gamm_num6+gamm_num7;
            if( (gamm_num_sum7>0) && (gamm_num_sum7<63) && (gamm_rand_cnt<=1000) )
            {
                gamm_rand_cnt++;
                gamm_num8=63-gamm_num_sum7;
                gamm_step1 = sGetRandEx( 0  , 18  );//21-3
                gamm_step2 = sGetRandEx( 0  , 18  );
                gamm_step3 = sGetRandEx( 0  , 18  );
                gamm_step4 = sGetRandEx( 0  , 18  );
                gamm_step5 = sGetRandEx( 0  , 18  );
                gamm_step6 = sGetRandEx( 0  , 18  );
                gamm_step7 = sGetRandEx( 0  , 18  );
                gamm_step8 = sGetRandEx( 0  , 18  );

                gamm_pos1 = gamm_num1*(1<<gamm_step1);
                gamm_pos2 = gamm_pos1+gamm_num2*(1<<gamm_step2);
                gamm_pos3 = gamm_pos2+gamm_num3*(1<<gamm_step3);
                gamm_pos4 = gamm_pos3+gamm_num4*(1<<gamm_step4);
                gamm_pos5 = gamm_pos4+gamm_num5*(1<<gamm_step5);
                gamm_pos6 = gamm_pos5+gamm_num6*(1<<gamm_step6);
                gamm_pos7 = gamm_pos6+gamm_num7*(1<<gamm_step7);
                gamm_pos8 = gamm_pos7+gamm_num8*(1<<gamm_step8);

                if(((1<<21)-gamm_pos8 > 0) && ((1<<21)-gamm_pos8 <= (1<<gamm_step8)))//gmm_in:21bit
                {
#if 0
                    VDP_PRINT("gamm_num1=%d,gamm_num2=%d,gamm_num3=%d,gamm_num4=%d\n",gamm_num1,gamm_num2,gamm_num3,gamm_num4);
                    VDP_PRINT("gamm_num5=%d,gamm_num6=%d,gamm_num7=%d,gamm_num8=%d\n",gamm_num5,gamm_num6,gamm_num7,gamm_num8);
                    VDP_PRINT("gamm_step1=%d,gamm_step2=%d,gamm_step3=%d,gamm_step4=%d\n",gamm_step1,gamm_step2,gamm_step3,gamm_step4);
                    VDP_PRINT("gamm_step5=%d,gamm_step6=%d,gamm_step7=%d,gamm_step8=%d\n\n",gamm_step5,gamm_step6,gamm_step7,gamm_step8);
#endif
                    break;
                }
                if(gamm_rand_cnt == 1000)
                    VDP_PRINT("gamma random data not OK !\n");
            }
            else
            {
                gamm_rand_cnt = 0;
                gamm_num1 = sGetRandEx( 1  , 56  );//63-(8-1)
                gamm_num2 = sGetRandEx( 1  , 56  );
                gamm_num3 = sGetRandEx( 1  , 56  );
                gamm_num4 = sGetRandEx( 1  , 56  );
                gamm_num5 = sGetRandEx( 1  , 56  );
                gamm_num6 = sGetRandEx( 1  , 56  );
                gamm_num7 = sGetRandEx( 1  , 56  );
                continue;
            }
        }

        degamm_num1 = degamm_num1;
        degamm_num2 = degamm_num1+degamm_num2;
        degamm_num3 = degamm_num2+degamm_num3;
        degamm_num4 = degamm_num3+degamm_num4;
        degamm_num5 = degamm_num4+degamm_num5;
        degamm_num6 = degamm_num5+degamm_num6;
        degamm_num7 = degamm_num6+degamm_num7;
        degamm_num8 = degamm_num7+degamm_num8;

        tmap_num1 = tmap_num1;
        tmap_num2 = tmap_num1+tmap_num2;
        tmap_num3 = tmap_num2+tmap_num3;
        tmap_num4 = tmap_num3+tmap_num4;
        tmap_num5 = tmap_num4+tmap_num5;
        tmap_num6 = tmap_num5+tmap_num6;
        tmap_num7 = tmap_num6+tmap_num7;
        tmap_num8 = tmap_num7+tmap_num8;

        smap_num1 = smap_num1;
        smap_num2 = smap_num1+smap_num2;
        smap_num3 = smap_num2+smap_num3;
        smap_num4 = smap_num3+smap_num4;
        smap_num5 = smap_num4+smap_num5;
        smap_num6 = smap_num5+smap_num6;
        smap_num7 = smap_num6+smap_num7;
        smap_num8 = smap_num7+smap_num8;

        gamm_num1 = gamm_num1;
        gamm_num2 = gamm_num1+gamm_num2;
        gamm_num3 = gamm_num2+gamm_num3;
        gamm_num4 = gamm_num3+gamm_num4;
        gamm_num5 = gamm_num4+gamm_num5;
        gamm_num6 = gamm_num5+gamm_num6;
        gamm_num7 = gamm_num6+gamm_num7;
        gamm_num8 = gamm_num7+gamm_num8;

        pstDmCfg->DePQPara.gmm_x1_step           = degamm_step1 ;
        pstDmCfg->DePQPara.gmm_x2_step           = degamm_step2 ;
        pstDmCfg->DePQPara.gmm_x3_step           = degamm_step3 ;
        pstDmCfg->DePQPara.gmm_x4_step           = degamm_step4 ;
        pstDmCfg->DePQPara.gmm_x5_step           = degamm_step5 ;
        pstDmCfg->DePQPara.gmm_x6_step           = degamm_step6 ;
        pstDmCfg->DePQPara.gmm_x7_step           = degamm_step7 ;
        pstDmCfg->DePQPara.gmm_x8_step           = degamm_step8 ;
        pstDmCfg->DePQPara.gmm_x1_pos            = degamm_pos1  ;
        pstDmCfg->DePQPara.gmm_x2_pos            = degamm_pos2  ;
        pstDmCfg->DePQPara.gmm_x3_pos            = degamm_pos3  ;
        pstDmCfg->DePQPara.gmm_x4_pos            = degamm_pos4  ;
        pstDmCfg->DePQPara.gmm_x5_pos            = degamm_pos5  ;
        pstDmCfg->DePQPara.gmm_x6_pos            = degamm_pos6  ;
        pstDmCfg->DePQPara.gmm_x7_pos            = degamm_pos7  ;
        pstDmCfg->DePQPara.gmm_x8_pos            = degamm_pos8  ;
        pstDmCfg->DePQPara.gmm_x1_num            = degamm_num1  ;
        pstDmCfg->DePQPara.gmm_x2_num            = degamm_num2  ;
        pstDmCfg->DePQPara.gmm_x3_num            = degamm_num3  ;
        pstDmCfg->DePQPara.gmm_x4_num            = degamm_num4  ;
        pstDmCfg->DePQPara.gmm_x5_num            = degamm_num5  ;
        pstDmCfg->DePQPara.gmm_x6_num            = degamm_num6  ;
        pstDmCfg->DePQPara.gmm_x7_num            = degamm_num7  ;
        pstDmCfg->DePQPara.gmm_x8_num            = degamm_num8  ;

        pstDmCfg->TMPara.gmm_x1_step             = tmap_step1   ;
        pstDmCfg->TMPara.gmm_x2_step             = tmap_step2   ;
        pstDmCfg->TMPara.gmm_x3_step             = tmap_step3   ;
        pstDmCfg->TMPara.gmm_x4_step             = tmap_step4   ;
        pstDmCfg->TMPara.gmm_x5_step             = tmap_step5   ;
        pstDmCfg->TMPara.gmm_x6_step             = tmap_step6   ;
        pstDmCfg->TMPara.gmm_x7_step             = tmap_step7   ;
        pstDmCfg->TMPara.gmm_x8_step             = tmap_step8   ;
        pstDmCfg->TMPara.gmm_x1_pos              = tmap_pos1    ;
        pstDmCfg->TMPara.gmm_x2_pos              = tmap_pos2    ;
        pstDmCfg->TMPara.gmm_x3_pos              = tmap_pos3    ;
        pstDmCfg->TMPara.gmm_x4_pos              = tmap_pos4    ;
        pstDmCfg->TMPara.gmm_x5_pos              = tmap_pos5    ;
        pstDmCfg->TMPara.gmm_x6_pos              = tmap_pos6    ;
        pstDmCfg->TMPara.gmm_x7_pos              = tmap_pos7    ;
        pstDmCfg->TMPara.gmm_x8_pos              = tmap_pos8    ;
        pstDmCfg->TMPara.gmm_x1_num              = tmap_num1    ;
        pstDmCfg->TMPara.gmm_x2_num              = tmap_num2    ;
        pstDmCfg->TMPara.gmm_x3_num              = tmap_num3    ;
        pstDmCfg->TMPara.gmm_x4_num              = tmap_num4    ;
        pstDmCfg->TMPara.gmm_x5_num              = tmap_num5    ;
        pstDmCfg->TMPara.gmm_x6_num              = tmap_num6    ;
        pstDmCfg->TMPara.gmm_x7_num              = tmap_num7    ;
        pstDmCfg->TMPara.gmm_x8_num              = tmap_num8    ;

        pstDmCfg->SMPara.gmm_x1_step             = smap_step1   ;
        pstDmCfg->SMPara.gmm_x2_step             = smap_step2   ;
        pstDmCfg->SMPara.gmm_x3_step             = smap_step3   ;
        pstDmCfg->SMPara.gmm_x4_step             = smap_step4   ;
        pstDmCfg->SMPara.gmm_x5_step             = smap_step5   ;
        pstDmCfg->SMPara.gmm_x6_step             = smap_step6   ;
        pstDmCfg->SMPara.gmm_x7_step             = smap_step7   ;
        pstDmCfg->SMPara.gmm_x8_step             = smap_step8   ;
        pstDmCfg->SMPara.gmm_x1_pos              = smap_pos1    ;
        pstDmCfg->SMPara.gmm_x2_pos              = smap_pos2    ;
        pstDmCfg->SMPara.gmm_x3_pos              = smap_pos3    ;
        pstDmCfg->SMPara.gmm_x4_pos              = smap_pos4    ;
        pstDmCfg->SMPara.gmm_x5_pos              = smap_pos5    ;
        pstDmCfg->SMPara.gmm_x6_pos              = smap_pos6    ;
        pstDmCfg->SMPara.gmm_x7_pos              = smap_pos7    ;
        pstDmCfg->SMPara.gmm_x8_pos              = smap_pos8    ;
        pstDmCfg->SMPara.gmm_x1_num              = smap_num1    ;
        pstDmCfg->SMPara.gmm_x2_num              = smap_num2    ;
        pstDmCfg->SMPara.gmm_x3_num              = smap_num3    ;
        pstDmCfg->SMPara.gmm_x4_num              = smap_num4    ;
        pstDmCfg->SMPara.gmm_x5_num              = smap_num5    ;
        pstDmCfg->SMPara.gmm_x6_num              = smap_num6    ;
        pstDmCfg->SMPara.gmm_x7_num              = smap_num7    ;
        pstDmCfg->SMPara.gmm_x8_num              = smap_num8    ;

        pstDmCfg->GammaPara.gmm_x1_step          = gamm_step1   ;
        pstDmCfg->GammaPara.gmm_x2_step          = gamm_step2   ;
        pstDmCfg->GammaPara.gmm_x3_step          = gamm_step3   ;
        pstDmCfg->GammaPara.gmm_x4_step          = gamm_step4   ;
        pstDmCfg->GammaPara.gmm_x5_step          = gamm_step5   ;
        pstDmCfg->GammaPara.gmm_x6_step          = gamm_step6   ;
        pstDmCfg->GammaPara.gmm_x7_step          = gamm_step7   ;
        pstDmCfg->GammaPara.gmm_x8_step          = gamm_step8   ;
        pstDmCfg->GammaPara.gmm_x1_pos           = gamm_pos1    ;
        pstDmCfg->GammaPara.gmm_x2_pos           = gamm_pos2    ;
        pstDmCfg->GammaPara.gmm_x3_pos           = gamm_pos3    ;
        pstDmCfg->GammaPara.gmm_x4_pos           = gamm_pos4    ;
        pstDmCfg->GammaPara.gmm_x5_pos           = gamm_pos5    ;
        pstDmCfg->GammaPara.gmm_x6_pos           = gamm_pos6    ;
        pstDmCfg->GammaPara.gmm_x7_pos           = gamm_pos7    ;
        pstDmCfg->GammaPara.gmm_x8_pos           = gamm_pos8    ;
        pstDmCfg->GammaPara.gmm_x1_num           = gamm_num1    ;
        pstDmCfg->GammaPara.gmm_x2_num           = gamm_num2    ;
        pstDmCfg->GammaPara.gmm_x3_num           = gamm_num3    ;
        pstDmCfg->GammaPara.gmm_x4_num           = gamm_num4    ;
        pstDmCfg->GammaPara.gmm_x5_num           = gamm_num5    ;
        pstDmCfg->GammaPara.gmm_x6_num           = gamm_num6    ;
        pstDmCfg->GammaPara.gmm_x7_num           = gamm_num7    ;
        pstDmCfg->GammaPara.gmm_x8_num           = gamm_num8    ;

        pstDmCfg->s32DcInSrc2Disp[0]             = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32DcInSrc2Disp[1]             = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32DcInSrc2Disp[2]             = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32DcOutSrc2Disp[0]            = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32DcOutSrc2Disp[1]            = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s32DcOutSrc2Disp[2]            = sGetRandEx(-(1<<20),(1<<20)-1);
        pstDmCfg->s16M33Src2Disp[0][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[0][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[0][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[1][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[1][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[1][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[2][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[2][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33Src2Disp[2][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->u16ScaleSrc2Disp               = sGetRandEx( 1  , 15  )    ;
        pstDmCfg->u32ClipMinCSC                  = sGetRandEx( 0  , (1<<9) )    ;
        pstDmCfg->u32ClipMaxCSC                  = sGetRandEx( (1<<18), (1<<21)-1);

        pstDmCfg->s16M33YUV2RGB0[0][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[0][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[0][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[1][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[1][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[1][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[2][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[2][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB0[2][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[0][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[0][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[0][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[1][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[1][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[1][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[2][0]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[2][1]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33YUV2RGB1[2][2]           = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->u16ScaleYUV2RGB_v0             = sGetRandEx( 1  , 15  )    ;
        pstDmCfg->u16ScaleYUV2RGB_v1             = sGetRandEx( 1  , 15  )    ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = sGetRandEx(-(1<<12),(1<<12)-1);
        pstDmCfg->u16ClipMinYUV2RGB_v0           = sGetRandEx( 0  , 100)    ;
        pstDmCfg->u16ClipMaxYUV2RGB_v0           = sGetRandEx( 900, 1023);
        pstDmCfg->u16ClipMinYUV2RGB_v1           = sGetRandEx( 0  , 100)    ;
        pstDmCfg->u16ClipMaxYUV2RGB_v1           = sGetRandEx( 900, 1023);
        pstDmCfg->s16M33RGB2YUV[0][0]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[0][1]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[0][2]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[1][0]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[1][1]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[1][2]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[2][0]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[2][1]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->s16M33RGB2YUV[2][2]            = sGetRandEx(-(1<<15),(1<<15)-1);
        pstDmCfg->u16ScaleRGB2YUV                = sGetRandEx( 1, 15  )    ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s16InOffsetRGB2YUV[1]          = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s16InOffsetRGB2YUV[2]          = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = sGetRandEx(-(1<<10),(1<<10)-1);
        pstDmCfg->u16ClipMinRGB2YUV_Y            = sGetRandEx( 0  , 100  )    ;
        pstDmCfg->u16ClipMinRGB2YUV_C            = sGetRandEx( 0  , 100  )    ;
        pstDmCfg->u16ClipMaxRGB2YUV_Y            = sGetRandEx( 900,1023 );
        pstDmCfg->u16ClipMaxRGB2YUV_C            = sGetRandEx( 900,1023 );
        pstDmCfg->u16ScaleCoefSM                 = sGetRandEx( 1, 15  )      ;

        pstDmCfg->stDitherCfg.u32_dither_thr_min      = sGetRandEx( 0,65533 ) ;
        pstDmCfg->stDitherCfg.u32_dither_thr_max      = sGetRandEx( pstDmCfg->stDitherCfg.u32_dither_thr_min,65535 ) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y0       = sGetRandEx( 0,2147483647) ;//31'h7fffffff;
        pstDmCfg->stDitherCfg.u32_dither_sed_u0       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v0       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w0       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_y1       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_u1       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_v1       = sGetRandEx( 0,2147483647) ;
        pstDmCfg->stDitherCfg.u32_dither_sed_w1       = sGetRandEx( 0,2147483647) ;
    }
	else if(VdmMode == VDP_VID_VDM_MIN)
	{
		VDP_PRINT("VDP_FUNC_SetVdmMode enter into min mode\n");
		//min mode
        pstDmCfg->u16M3LumaCal[0]                = 0   ;
        pstDmCfg->u16M3LumaCal[1]                = 0   ;
        pstDmCfg->u16M3LumaCal[2]                = 0   ;
        pstDmCfg->u16ScaleLumaCal                = 1   ;
        pstDmCfg->u16ScaleCoefTM                 = 1   ;
        pstDmCfg->u32ClipMinTM                   = 0   ;
        pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
        pstDmCfg->s32TMOff0                      = -(1<<20)    ;
        pstDmCfg->s32TMOff1                      = -(1<<20)    ;
        pstDmCfg->s32TMOff2                      = -(1<<20)    ;

        pstDmCfg->DePQPara.gmm_x1_step           = 8          ;//6          ;
        pstDmCfg->DePQPara.gmm_x2_step           = 3          ;//4          ;
        pstDmCfg->DePQPara.gmm_x3_step           = 6          ;//2          ;
        pstDmCfg->DePQPara.gmm_x4_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x5_step           = 8          ;//0          ;
        pstDmCfg->DePQPara.gmm_x6_step           = 6          ;//0          ;
        pstDmCfg->DePQPara.gmm_x7_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x8_step           = 7          ;//0          ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 1024       ;//512        ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 1032       ;//928        ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 1480       ;//1020       ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1528       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x5_pos            = 2808       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x6_pos            = 2936       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x7_pos            = 3184       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x8_pos            = 4080       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x1_num            = 4          ;//8          ;
        pstDmCfg->DePQPara.gmm_x2_num            = 5          ;//34         ;
        pstDmCfg->DePQPara.gmm_x3_num            = 12         ;//57         ;
        pstDmCfg->DePQPara.gmm_x4_num            = 18         ;//61         ;
        pstDmCfg->DePQPara.gmm_x5_num            = 23         ;//61         ;
        pstDmCfg->DePQPara.gmm_x6_num            = 25         ;//61         ;
        pstDmCfg->DePQPara.gmm_x7_num            = 56         ;//61         ;
        pstDmCfg->DePQPara.gmm_x8_num            = 63         ;//61         ;

        pstDmCfg->TMPara.gmm_x1_step             = 5          ;
        pstDmCfg->TMPara.gmm_x2_step             = 7          ;
        pstDmCfg->TMPara.gmm_x3_step             = 9          ;
        pstDmCfg->TMPara.gmm_x4_step             = 10         ;
        pstDmCfg->TMPara.gmm_x5_step             = 11         ;
        pstDmCfg->TMPara.gmm_x6_step             = 13         ;
        pstDmCfg->TMPara.gmm_x7_step             = 15         ;
        pstDmCfg->TMPara.gmm_x8_step             = 17         ;
        pstDmCfg->TMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->TMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->TMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->TMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->TMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->TMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->TMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->TMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->TMPara.gmm_x1_num              = 4          ;
        pstDmCfg->TMPara.gmm_x2_num              = 11         ;
        pstDmCfg->TMPara.gmm_x3_num              = 13         ;
        pstDmCfg->TMPara.gmm_x4_num              = 17         ;
        pstDmCfg->TMPara.gmm_x5_num              = 22         ;
        pstDmCfg->TMPara.gmm_x6_num              = 36         ;
        pstDmCfg->TMPara.gmm_x7_num              = 52         ;
        pstDmCfg->TMPara.gmm_x8_num              = 63         ;

        pstDmCfg->SMPara.gmm_x1_step             = 5          ;
        pstDmCfg->SMPara.gmm_x2_step             = 7          ;
        pstDmCfg->SMPara.gmm_x3_step             = 9          ;
        pstDmCfg->SMPara.gmm_x4_step             = 10         ;
        pstDmCfg->SMPara.gmm_x5_step             = 11         ;
        pstDmCfg->SMPara.gmm_x6_step             = 13         ;
        pstDmCfg->SMPara.gmm_x7_step             = 15         ;
        pstDmCfg->SMPara.gmm_x8_step             = 17         ;
        pstDmCfg->SMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->SMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->SMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->SMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->SMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->SMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->SMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->SMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->SMPara.gmm_x1_num              = 4          ;
        pstDmCfg->SMPara.gmm_x2_num              = 11         ;
        pstDmCfg->SMPara.gmm_x3_num              = 13         ;
        pstDmCfg->SMPara.gmm_x4_num              = 17         ;
        pstDmCfg->SMPara.gmm_x5_num              = 22         ;
        pstDmCfg->SMPara.gmm_x6_num              = 36         ;
        pstDmCfg->SMPara.gmm_x7_num              = 52         ;
        pstDmCfg->SMPara.gmm_x8_num              = 63         ;

        pstDmCfg->GammaPara.gmm_x1_step          = 5          ;
        pstDmCfg->GammaPara.gmm_x2_step          = 7          ;
        pstDmCfg->GammaPara.gmm_x3_step          = 9          ;
        pstDmCfg->GammaPara.gmm_x4_step          = 10         ;
        pstDmCfg->GammaPara.gmm_x5_step          = 11         ;
        pstDmCfg->GammaPara.gmm_x6_step          = 13         ;
        pstDmCfg->GammaPara.gmm_x7_step          = 15         ;
        pstDmCfg->GammaPara.gmm_x8_step          = 17         ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 128        ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 1024       ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 2048       ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 6144       ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 16384      ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 131072     ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 655360     ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 2097151    ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4          ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11         ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13         ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17         ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22         ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36         ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52         ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63         ;

        pstDmCfg->s32DcInSrc2Disp[0]             = -(1<<20)   ;
        pstDmCfg->s32DcInSrc2Disp[1]             = -(1<<20)   ;
        pstDmCfg->s32DcInSrc2Disp[2]             = -(1<<20)   ;
        pstDmCfg->s32DcOutSrc2Disp[0]            = -(1<<20)   ;
        pstDmCfg->s32DcOutSrc2Disp[1]            = -(1<<20)   ;
        pstDmCfg->s32DcOutSrc2Disp[2]            = -(1<<20)   ;
        pstDmCfg->s16M33Src2Disp[0][0]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[0][1]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[0][2]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[1][0]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[1][1]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[1][2]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[2][0]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[2][1]           = -(1<<15)   ;
        pstDmCfg->s16M33Src2Disp[2][2]           = -(1<<15)   ;
        pstDmCfg->u16ScaleSrc2Disp               = 1          ;
        pstDmCfg->u32ClipMinCSC                  = 0          ;
        pstDmCfg->u32ClipMaxCSC                  = (1<<21)-1  ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = -(1<<15)   ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = -(1<<15)   ;
        pstDmCfg->u16ScaleYUV2RGB_v0             = 1     ;
        pstDmCfg->u16ScaleYUV2RGB_v1             = 1     ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = -(1<<10)   ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = -(1<<10)   ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = -(1<<10)   ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = -(1<<12)   ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = -(1<<12)   ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = -(1<<12)   ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = -(1<<10)   ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = -(1<<10)   ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = -(1<<10)   ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = -(1<<12)   ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = -(1<<12)   ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = -(1<<12)   ;
        pstDmCfg->u16ClipMinYUV2RGB_v0           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023;
        pstDmCfg->u16ClipMinYUV2RGB_v1           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023;
        pstDmCfg->s16M33RGB2YUV[0][0]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = -(1<<15)   ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = -(1<<15)   ;
        pstDmCfg->u16ScaleRGB2YUV                = 1          ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = -(1<<10)   ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = -(1<<10)   ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = -(1<<10)   ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = -(1<<10)   ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = -(1<<10)   ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = -(1<<10)   ;
        pstDmCfg->u16ClipMinRGB2YUV_Y            = 0          ;
        pstDmCfg->u16ClipMinRGB2YUV_C            = 0          ;
        pstDmCfg->u16ClipMaxRGB2YUV_Y            = 1023       ;
        pstDmCfg->u16ClipMaxRGB2YUV_C            = 1023       ;
        pstDmCfg->u16ScaleCoefSM                 = 1          ;

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
    }
	else if(VdmMode == VDP_VID_VDM_MAX)
	{
		VDP_PRINT("VDP_FUNC_SetVdmMode enter into max mode\n");
		//max mode
        pstDmCfg->u16M3LumaCal[0]                = (1<<16)-1   ;
        pstDmCfg->u16M3LumaCal[1]                = (1<<16)-1   ;
        pstDmCfg->u16M3LumaCal[2]                = (1<<16)-1   ;
        pstDmCfg->u16ScaleLumaCal                = 15          ;
        pstDmCfg->u16ScaleCoefTM                 = 15          ;
        pstDmCfg->u32ClipMinTM                   = 0           ;
        pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
        pstDmCfg->s32TMOff0                      = (1<<20)-1   ;
        pstDmCfg->s32TMOff1                      = (1<<20)-1   ;
        pstDmCfg->s32TMOff2                      = (1<<20)-1   ;

        pstDmCfg->DePQPara.gmm_x1_step           = 8          ;//6          ;
        pstDmCfg->DePQPara.gmm_x2_step           = 3          ;//4          ;
        pstDmCfg->DePQPara.gmm_x3_step           = 6          ;//2          ;
        pstDmCfg->DePQPara.gmm_x4_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x5_step           = 8          ;//0          ;
        pstDmCfg->DePQPara.gmm_x6_step           = 6          ;//0          ;
        pstDmCfg->DePQPara.gmm_x7_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x8_step           = 7          ;//0          ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 1024       ;//512        ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 1032       ;//928        ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 1480       ;//1020       ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1528       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x5_pos            = 2808       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x6_pos            = 2936       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x7_pos            = 3184       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x8_pos            = 4080       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x1_num            = 4          ;//8          ;
        pstDmCfg->DePQPara.gmm_x2_num            = 5          ;//34         ;
        pstDmCfg->DePQPara.gmm_x3_num            = 12         ;//57         ;
        pstDmCfg->DePQPara.gmm_x4_num            = 18         ;//61         ;
        pstDmCfg->DePQPara.gmm_x5_num            = 23         ;//61         ;
        pstDmCfg->DePQPara.gmm_x6_num            = 25         ;//61         ;
        pstDmCfg->DePQPara.gmm_x7_num            = 56         ;//61         ;
        pstDmCfg->DePQPara.gmm_x8_num            = 63         ;//61         ;

        pstDmCfg->TMPara.gmm_x1_step             = 5          ;
        pstDmCfg->TMPara.gmm_x2_step             = 7          ;
        pstDmCfg->TMPara.gmm_x3_step             = 9          ;
        pstDmCfg->TMPara.gmm_x4_step             = 10         ;
        pstDmCfg->TMPara.gmm_x5_step             = 11         ;
        pstDmCfg->TMPara.gmm_x6_step             = 13         ;
        pstDmCfg->TMPara.gmm_x7_step             = 15         ;
        pstDmCfg->TMPara.gmm_x8_step             = 17         ;
        pstDmCfg->TMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->TMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->TMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->TMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->TMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->TMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->TMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->TMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->TMPara.gmm_x1_num              = 4          ;
        pstDmCfg->TMPara.gmm_x2_num              = 11         ;
        pstDmCfg->TMPara.gmm_x3_num              = 13         ;
        pstDmCfg->TMPara.gmm_x4_num              = 17         ;
        pstDmCfg->TMPara.gmm_x5_num              = 22         ;
        pstDmCfg->TMPara.gmm_x6_num              = 36         ;
        pstDmCfg->TMPara.gmm_x7_num              = 52         ;
        pstDmCfg->TMPara.gmm_x8_num              = 63         ;

        pstDmCfg->SMPara.gmm_x1_step             = 5          ;
        pstDmCfg->SMPara.gmm_x2_step             = 7          ;
        pstDmCfg->SMPara.gmm_x3_step             = 9          ;
        pstDmCfg->SMPara.gmm_x4_step             = 10         ;
        pstDmCfg->SMPara.gmm_x5_step             = 11         ;
        pstDmCfg->SMPara.gmm_x6_step             = 13         ;
        pstDmCfg->SMPara.gmm_x7_step             = 15         ;
        pstDmCfg->SMPara.gmm_x8_step             = 17         ;
        pstDmCfg->SMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->SMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->SMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->SMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->SMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->SMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->SMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->SMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->SMPara.gmm_x1_num              = 4          ;
        pstDmCfg->SMPara.gmm_x2_num              = 11         ;
        pstDmCfg->SMPara.gmm_x3_num              = 13         ;
        pstDmCfg->SMPara.gmm_x4_num              = 17         ;
        pstDmCfg->SMPara.gmm_x5_num              = 22         ;
        pstDmCfg->SMPara.gmm_x6_num              = 36         ;
        pstDmCfg->SMPara.gmm_x7_num              = 52         ;
        pstDmCfg->SMPara.gmm_x8_num              = 63         ;

        pstDmCfg->GammaPara.gmm_x1_step          = 5          ;
        pstDmCfg->GammaPara.gmm_x2_step          = 7          ;
        pstDmCfg->GammaPara.gmm_x3_step          = 9          ;
        pstDmCfg->GammaPara.gmm_x4_step          = 10         ;
        pstDmCfg->GammaPara.gmm_x5_step          = 11         ;
        pstDmCfg->GammaPara.gmm_x6_step          = 13         ;
        pstDmCfg->GammaPara.gmm_x7_step          = 15         ;
        pstDmCfg->GammaPara.gmm_x8_step          = 17         ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 128        ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 1024       ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 2048       ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 6144       ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 16384      ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 131072     ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 655360     ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 2097151    ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4          ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11         ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13         ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17         ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22         ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36         ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52         ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63         ;

        pstDmCfg->s32DcInSrc2Disp[0]             = (1<<20)-1  ;
        pstDmCfg->s32DcInSrc2Disp[1]             = (1<<20)-1  ;
        pstDmCfg->s32DcInSrc2Disp[2]             = (1<<20)-1  ;
        pstDmCfg->s32DcOutSrc2Disp[0]            = (1<<20)-1  ;
        pstDmCfg->s32DcOutSrc2Disp[1]            = (1<<20)-1  ;
        pstDmCfg->s32DcOutSrc2Disp[2]            = (1<<20)-1  ;
        pstDmCfg->s16M33Src2Disp[0][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[0][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[0][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[1][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[1][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[1][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[2][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[2][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33Src2Disp[2][2]           = (1<<15)-1  ;
        pstDmCfg->u16ScaleSrc2Disp               = 15         ;
        pstDmCfg->u32ClipMinCSC                  = 0          ;
        pstDmCfg->u32ClipMaxCSC                  = (1<<21)-1  ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = (1<<15)-1  ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = (1<<15)-1  ;
        pstDmCfg->u16ScaleYUV2RGB_v0             = 15         ;
        pstDmCfg->u16ScaleYUV2RGB_v1             = 15         ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = (1<<10)-1  ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = (1<<10)-1  ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = (1<<10)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = (1<<12)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = (1<<12)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = (1<<12)-1  ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = (1<<10)-1  ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = (1<<10)-1  ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = (1<<10)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = (1<<12)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = (1<<12)-1  ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = (1<<12)-1  ;
        pstDmCfg->u16ClipMinYUV2RGB_v0           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023       ;
        pstDmCfg->u16ClipMinYUV2RGB_v1           = 0          ;
        pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023       ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = (1<<15)-1  ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = (1<<15)-1  ;
        pstDmCfg->u16ScaleRGB2YUV                = 15         ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = (1<<10)-1  ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = (1<<10)-1  ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = (1<<10)-1  ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = (1<<10)-1  ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = (1<<10)-1  ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = (1<<10)-1  ;
        pstDmCfg->u16ClipMinRGB2YUV_Y            = 0          ;
        pstDmCfg->u16ClipMinRGB2YUV_C            = 0          ;
        pstDmCfg->u16ClipMaxRGB2YUV_Y            = 1023       ;
        pstDmCfg->u16ClipMaxRGB2YUV_C            = 1023       ;
        pstDmCfg->u16ScaleCoefSM                 = 15         ;

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
    }
	else if(VdmMode == VDP_VID_VDM_ZERO)
	{
		VDP_PRINT("VDP_FUNC_SetVdmMode enter into zero mode\n");
		//zero mode
        pstDmCfg->u16M3LumaCal[0]                = 0   ;
        pstDmCfg->u16M3LumaCal[1]                = 0   ;
        pstDmCfg->u16M3LumaCal[2]                = 0   ;
        pstDmCfg->u16ScaleLumaCal                = 1   ;
        pstDmCfg->u16ScaleCoefTM                 = 1   ;
        pstDmCfg->u32ClipMinTM                   = 0   ;
        pstDmCfg->u32ClipMaxTM                   = (1<<21)-1   ;
        pstDmCfg->s32TMOff0                      = 0       ;
        pstDmCfg->s32TMOff1                      = 0       ;
        pstDmCfg->s32TMOff2                      = 0       ;

        pstDmCfg->DePQPara.gmm_x1_step           = 8          ;//6          ;
        pstDmCfg->DePQPara.gmm_x2_step           = 3          ;//4          ;
        pstDmCfg->DePQPara.gmm_x3_step           = 6          ;//2          ;
        pstDmCfg->DePQPara.gmm_x4_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x5_step           = 8          ;//0          ;
        pstDmCfg->DePQPara.gmm_x6_step           = 6          ;//0          ;
        pstDmCfg->DePQPara.gmm_x7_step           = 3          ;//0          ;
        pstDmCfg->DePQPara.gmm_x8_step           = 7          ;//0          ;
        pstDmCfg->DePQPara.gmm_x1_pos            = 1024       ;//512        ;
        pstDmCfg->DePQPara.gmm_x2_pos            = 1032       ;//928        ;
        pstDmCfg->DePQPara.gmm_x3_pos            = 1480       ;//1020       ;
        pstDmCfg->DePQPara.gmm_x4_pos            = 1528       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x5_pos            = 2808       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x6_pos            = 2936       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x7_pos            = 3184       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x8_pos            = 4080       ;//1023       ;
        pstDmCfg->DePQPara.gmm_x1_num            = 4          ;//8          ;
        pstDmCfg->DePQPara.gmm_x2_num            = 5          ;//34         ;
        pstDmCfg->DePQPara.gmm_x3_num            = 12         ;//57         ;
        pstDmCfg->DePQPara.gmm_x4_num            = 18         ;//61         ;
        pstDmCfg->DePQPara.gmm_x5_num            = 23         ;//61         ;
        pstDmCfg->DePQPara.gmm_x6_num            = 25         ;//61         ;
        pstDmCfg->DePQPara.gmm_x7_num            = 56         ;//61         ;
        pstDmCfg->DePQPara.gmm_x8_num            = 63         ;//61         ;

        pstDmCfg->TMPara.gmm_x1_step             = 5          ;
        pstDmCfg->TMPara.gmm_x2_step             = 7          ;
        pstDmCfg->TMPara.gmm_x3_step             = 9          ;
        pstDmCfg->TMPara.gmm_x4_step             = 10         ;
        pstDmCfg->TMPara.gmm_x5_step             = 11         ;
        pstDmCfg->TMPara.gmm_x6_step             = 13         ;
        pstDmCfg->TMPara.gmm_x7_step             = 15         ;
        pstDmCfg->TMPara.gmm_x8_step             = 17         ;
        pstDmCfg->TMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->TMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->TMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->TMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->TMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->TMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->TMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->TMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->TMPara.gmm_x1_num              = 4          ;
        pstDmCfg->TMPara.gmm_x2_num              = 11         ;
        pstDmCfg->TMPara.gmm_x3_num              = 13         ;
        pstDmCfg->TMPara.gmm_x4_num              = 17         ;
        pstDmCfg->TMPara.gmm_x5_num              = 22         ;
        pstDmCfg->TMPara.gmm_x6_num              = 36         ;
        pstDmCfg->TMPara.gmm_x7_num              = 52         ;
        pstDmCfg->TMPara.gmm_x8_num              = 63         ;

        pstDmCfg->SMPara.gmm_x1_step             = 5          ;
        pstDmCfg->SMPara.gmm_x2_step             = 7          ;
        pstDmCfg->SMPara.gmm_x3_step             = 9          ;
        pstDmCfg->SMPara.gmm_x4_step             = 10         ;
        pstDmCfg->SMPara.gmm_x5_step             = 11         ;
        pstDmCfg->SMPara.gmm_x6_step             = 13         ;
        pstDmCfg->SMPara.gmm_x7_step             = 15         ;
        pstDmCfg->SMPara.gmm_x8_step             = 17         ;
        pstDmCfg->SMPara.gmm_x1_pos              = 128        ;
        pstDmCfg->SMPara.gmm_x2_pos              = 1024       ;
        pstDmCfg->SMPara.gmm_x3_pos              = 2048       ;
        pstDmCfg->SMPara.gmm_x4_pos              = 6144       ;
        pstDmCfg->SMPara.gmm_x5_pos              = 16384      ;
        pstDmCfg->SMPara.gmm_x6_pos              = 131072     ;
        pstDmCfg->SMPara.gmm_x7_pos              = 655360     ;
        pstDmCfg->SMPara.gmm_x8_pos              = 2097151    ;
        pstDmCfg->SMPara.gmm_x1_num              = 4          ;
        pstDmCfg->SMPara.gmm_x2_num              = 11         ;
        pstDmCfg->SMPara.gmm_x3_num              = 13         ;
        pstDmCfg->SMPara.gmm_x4_num              = 17         ;
        pstDmCfg->SMPara.gmm_x5_num              = 22         ;
        pstDmCfg->SMPara.gmm_x6_num              = 36         ;
        pstDmCfg->SMPara.gmm_x7_num              = 52         ;
        pstDmCfg->SMPara.gmm_x8_num              = 63         ;

        pstDmCfg->GammaPara.gmm_x1_step          = 5          ;
        pstDmCfg->GammaPara.gmm_x2_step          = 7          ;
        pstDmCfg->GammaPara.gmm_x3_step          = 9          ;
        pstDmCfg->GammaPara.gmm_x4_step          = 10         ;
        pstDmCfg->GammaPara.gmm_x5_step          = 11         ;
        pstDmCfg->GammaPara.gmm_x6_step          = 13         ;
        pstDmCfg->GammaPara.gmm_x7_step          = 15         ;
        pstDmCfg->GammaPara.gmm_x8_step          = 17         ;
        pstDmCfg->GammaPara.gmm_x1_pos           = 128        ;
        pstDmCfg->GammaPara.gmm_x2_pos           = 1024       ;
        pstDmCfg->GammaPara.gmm_x3_pos           = 2048       ;
        pstDmCfg->GammaPara.gmm_x4_pos           = 6144       ;
        pstDmCfg->GammaPara.gmm_x5_pos           = 16384      ;
        pstDmCfg->GammaPara.gmm_x6_pos           = 131072     ;
        pstDmCfg->GammaPara.gmm_x7_pos           = 655360     ;
        pstDmCfg->GammaPara.gmm_x8_pos           = 2097151    ;
        pstDmCfg->GammaPara.gmm_x1_num           = 4          ;
        pstDmCfg->GammaPara.gmm_x2_num           = 11         ;
        pstDmCfg->GammaPara.gmm_x3_num           = 13         ;
        pstDmCfg->GammaPara.gmm_x4_num           = 17         ;
        pstDmCfg->GammaPara.gmm_x5_num           = 22         ;
        pstDmCfg->GammaPara.gmm_x6_num           = 36         ;
        pstDmCfg->GammaPara.gmm_x7_num           = 52         ;
        pstDmCfg->GammaPara.gmm_x8_num           = 63         ;

        pstDmCfg->s32DcInSrc2Disp[0]             = 0          ;
        pstDmCfg->s32DcInSrc2Disp[1]             = 0          ;
        pstDmCfg->s32DcInSrc2Disp[2]             = 0          ;
        pstDmCfg->s32DcOutSrc2Disp[0]            = 0          ;
        pstDmCfg->s32DcOutSrc2Disp[1]            = 0          ;
        pstDmCfg->s32DcOutSrc2Disp[2]            = 0          ;
        pstDmCfg->s16M33Src2Disp[0][0]           = 0          ;
        pstDmCfg->s16M33Src2Disp[0][1]           = 0          ;
        pstDmCfg->s16M33Src2Disp[0][2]           = 0          ;
        pstDmCfg->s16M33Src2Disp[1][0]           = 0          ;
        pstDmCfg->s16M33Src2Disp[1][1]           = 0          ;
        pstDmCfg->s16M33Src2Disp[1][2]           = 0          ;
        pstDmCfg->s16M33Src2Disp[2][0]           = 0          ;
        pstDmCfg->s16M33Src2Disp[2][1]           = 0          ;
        pstDmCfg->s16M33Src2Disp[2][2]           = 0          ;
        pstDmCfg->u16ScaleSrc2Disp               = 1          ;
        pstDmCfg->u32ClipMinCSC                  = 0          ;
        pstDmCfg->u32ClipMaxCSC                  = (1<<21)-1  ;

        pstDmCfg->s16M33YUV2RGB0[0][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[0][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[0][2]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[1][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[1][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[1][2]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[2][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[2][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB0[2][2]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[0][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[0][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[0][2]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[1][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[1][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[1][2]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[2][0]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[2][1]           = 0    ;
        pstDmCfg->s16M33YUV2RGB1[2][2]           = 0    ;
        pstDmCfg->u16ScaleYUV2RGB_v0             = 1    ;
        pstDmCfg->u16ScaleYUV2RGB_v1             = 1    ;
        pstDmCfg->s32InOffsetYUV2RGB0[0]         = 0    ;
        pstDmCfg->s32InOffsetYUV2RGB0[1]         = 0    ;
        pstDmCfg->s32InOffsetYUV2RGB0[2]         = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[0]        = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[1]        = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB0[2]        = 0    ;
        pstDmCfg->s32InOffsetYUV2RGB1[0]         = 0    ;
        pstDmCfg->s32InOffsetYUV2RGB1[1]         = 0    ;
        pstDmCfg->s32InOffsetYUV2RGB1[2]         = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[0]        = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[1]        = 0    ;
        pstDmCfg->s32OutOffsetYUV2RGB1[2]        = 0    ;
        pstDmCfg->u16ClipMinYUV2RGB_v0           = 0    ;
        pstDmCfg->u16ClipMaxYUV2RGB_v0           = 1023 ;
        pstDmCfg->u16ClipMinYUV2RGB_v1           = 0    ;
        pstDmCfg->u16ClipMaxYUV2RGB_v1           = 1023 ;
        pstDmCfg->s16M33RGB2YUV[0][0]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[0][1]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[0][2]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[1][0]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[1][1]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[1][2]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[2][0]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[2][1]            = 0    ;
        pstDmCfg->s16M33RGB2YUV[2][2]            = 0    ;
        pstDmCfg->u16ScaleRGB2YUV                = 1    ;
        pstDmCfg->s16InOffsetRGB2YUV[0]          = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[1]          = 0    ;
        pstDmCfg->s16InOffsetRGB2YUV[2]          = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[0]         = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[1]         = 0    ;
        pstDmCfg->s16OutOffsetRGB2YUV[2]         = 0    ;
        pstDmCfg->u16ClipMinRGB2YUV_Y            = 0    ;
        pstDmCfg->u16ClipMinRGB2YUV_C            = 0    ;
        pstDmCfg->u16ClipMaxRGB2YUV_Y            = 1023 ;
        pstDmCfg->u16ClipMaxRGB2YUV_C            = 1023 ;
        pstDmCfg->u16ScaleCoefSM                 = 1    ;

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
    }


    //------------------------
    // adapter
    //------------------------
//     memcpy(&g_DmCfg, pstDmCfg, sizeof(DmCfg_t));

    vdm_ck_gt_en            = pstDmCfg->vdm_ck_gt_en    ;
    vdm_tmap_in_bdp         = pstDmCfg->vdm_tmap_in_bdp ;
    vdm_csc_bind            = pstDmCfg->vdm_csc_bind    ;
    vdm_gmm_en              = pstDmCfg->vdm_gmm_en      ;
    vdm_tmap_en             = pstDmCfg->vdm_tmap_en     ;
    vdm_degmm_en            = pstDmCfg->vdm_degmm_en    ;
    vdm_en                  = pstDmCfg->vdm_en          ;
    vdm_v1_gamma_en         = pstDmCfg->vdm_v1_gamma_en ;
    vdm_v0_gamma_en         = pstDmCfg->vdm_v0_gamma_en ;
    vdm_v1_csc_en           = pstDmCfg->vdm_v1_csc_en   ;
    vdm_v0_csc_en           = pstDmCfg->vdm_v0_csc_en   ;
    vdm_yuv2rgb_en          = pstDmCfg->vdm_yuv2rgb_en  ;
    vdm_v0_cl_en            = pstDmCfg->vdm_v0_cl_en   ;
    vdm_v1_cl_en            = pstDmCfg->vdm_v1_cl_en   ;
    vdm_rgb2yuv_pip_en      = pstDmCfg->vdm_rgb2yuv_pip_en  ;
    vdm_rgb2yuv_en          = pstDmCfg->vdm_rgb2yuv_en  ;
    vdm_cadj_en             = pstDmCfg->vdm_cadj_en     ;
    vdm_csc_en              = pstDmCfg->vdm_csc_en      ;
    vdm_dither_en           = pstDmCfg->vdm_dither_en   ;

    vdm_luma_coef0_tmap     = pstDmCfg->u16M3LumaCal[0] ;
    vdm_luma_coef1_tmap     = pstDmCfg->u16M3LumaCal[1] ;
    vdm_luma_coef2_tmap     = pstDmCfg->u16M3LumaCal[2] ;
    vdm_tmap_luma_scale     = pstDmCfg->u16ScaleLumaCal ;
    vdm_tmap_coef_scale     = pstDmCfg->u16ScaleCoefTM  ;
    vdm_tmap_out_clip_min   = pstDmCfg->u32ClipMinTM    ;
    vdm_tmap_out_clip_max   = pstDmCfg->u32ClipMaxTM    ;
    vdm_tmap_out_dc0        = pstDmCfg->s32TMOff0       ;
    vdm_tmap_out_dc1        = pstDmCfg->s32TMOff1       ;
    vdm_tmap_out_dc2        = pstDmCfg->s32TMOff2       ;

    v_degmm_x1_step         = pstDmCfg->DePQPara.gmm_x1_step   ;
    v_degmm_x2_step         = pstDmCfg->DePQPara.gmm_x2_step   ;
    v_degmm_x3_step         = pstDmCfg->DePQPara.gmm_x3_step   ;
    v_degmm_x4_step         = pstDmCfg->DePQPara.gmm_x4_step   ;
    v_degmm_x5_step         = pstDmCfg->DePQPara.gmm_x5_step   ;
    v_degmm_x6_step         = pstDmCfg->DePQPara.gmm_x6_step   ;
    v_degmm_x7_step         = pstDmCfg->DePQPara.gmm_x7_step   ;
    v_degmm_x8_step         = pstDmCfg->DePQPara.gmm_x8_step   ;
    v_degmm_x1_pos          = pstDmCfg->DePQPara.gmm_x1_pos    ;
    v_degmm_x2_pos          = pstDmCfg->DePQPara.gmm_x2_pos    ;
    v_degmm_x3_pos          = pstDmCfg->DePQPara.gmm_x3_pos    ;
    v_degmm_x4_pos          = pstDmCfg->DePQPara.gmm_x4_pos    ;
    v_degmm_x5_pos          = pstDmCfg->DePQPara.gmm_x5_pos    ;
    v_degmm_x6_pos          = pstDmCfg->DePQPara.gmm_x6_pos    ;
    v_degmm_x7_pos          = pstDmCfg->DePQPara.gmm_x7_pos    ;
    v_degmm_x8_pos          = pstDmCfg->DePQPara.gmm_x8_pos    ;
    v_degmm_x1_num          = pstDmCfg->DePQPara.gmm_x1_num    ;
    v_degmm_x2_num          = pstDmCfg->DePQPara.gmm_x2_num    ;
    v_degmm_x3_num          = pstDmCfg->DePQPara.gmm_x3_num    ;
    v_degmm_x4_num          = pstDmCfg->DePQPara.gmm_x4_num    ;
    v_degmm_x5_num          = pstDmCfg->DePQPara.gmm_x5_num    ;
    v_degmm_x6_num          = pstDmCfg->DePQPara.gmm_x6_num    ;
    v_degmm_x7_num          = pstDmCfg->DePQPara.gmm_x7_num    ;
    v_degmm_x8_num          = pstDmCfg->DePQPara.gmm_x8_num    ;

    v_tmap_x1_step          = pstDmCfg->TMPara.gmm_x1_step ;
    v_tmap_x2_step          = pstDmCfg->TMPara.gmm_x2_step ;
    v_tmap_x3_step          = pstDmCfg->TMPara.gmm_x3_step ;
    v_tmap_x4_step          = pstDmCfg->TMPara.gmm_x4_step ;
    v_tmap_x5_step          = pstDmCfg->TMPara.gmm_x5_step ;
    v_tmap_x6_step          = pstDmCfg->TMPara.gmm_x6_step ;
    v_tmap_x7_step          = pstDmCfg->TMPara.gmm_x7_step ;
    v_tmap_x8_step          = pstDmCfg->TMPara.gmm_x8_step ;
    v_tmap_x1_pos           = pstDmCfg->TMPara.gmm_x1_pos  ;
    v_tmap_x2_pos           = pstDmCfg->TMPara.gmm_x2_pos  ;
    v_tmap_x3_pos           = pstDmCfg->TMPara.gmm_x3_pos  ;
    v_tmap_x4_pos           = pstDmCfg->TMPara.gmm_x4_pos  ;
    v_tmap_x5_pos           = pstDmCfg->TMPara.gmm_x5_pos  ;
    v_tmap_x6_pos           = pstDmCfg->TMPara.gmm_x6_pos  ;
    v_tmap_x7_pos           = pstDmCfg->TMPara.gmm_x7_pos  ;
    v_tmap_x8_pos           = pstDmCfg->TMPara.gmm_x8_pos  ;
    v_tmap_x1_num           = pstDmCfg->TMPara.gmm_x1_num  ;
    v_tmap_x2_num           = pstDmCfg->TMPara.gmm_x2_num  ;
    v_tmap_x3_num           = pstDmCfg->TMPara.gmm_x3_num  ;
    v_tmap_x4_num           = pstDmCfg->TMPara.gmm_x4_num  ;
    v_tmap_x5_num           = pstDmCfg->TMPara.gmm_x5_num  ;
    v_tmap_x6_num           = pstDmCfg->TMPara.gmm_x6_num  ;
    v_tmap_x7_num           = pstDmCfg->TMPara.gmm_x7_num  ;
    v_tmap_x8_num           = pstDmCfg->TMPara.gmm_x8_num  ;

    v_smap_x1_step          = pstDmCfg->SMPara.gmm_x1_step ;
    v_smap_x2_step          = pstDmCfg->SMPara.gmm_x2_step ;
    v_smap_x3_step          = pstDmCfg->SMPara.gmm_x3_step ;
    v_smap_x4_step          = pstDmCfg->SMPara.gmm_x4_step ;
    v_smap_x5_step          = pstDmCfg->SMPara.gmm_x5_step ;
    v_smap_x6_step          = pstDmCfg->SMPara.gmm_x6_step ;
    v_smap_x7_step          = pstDmCfg->SMPara.gmm_x7_step ;
    v_smap_x8_step          = pstDmCfg->SMPara.gmm_x8_step ;
    v_smap_x1_pos           = pstDmCfg->SMPara.gmm_x1_pos  ;
    v_smap_x2_pos           = pstDmCfg->SMPara.gmm_x2_pos  ;
    v_smap_x3_pos           = pstDmCfg->SMPara.gmm_x3_pos  ;
    v_smap_x4_pos           = pstDmCfg->SMPara.gmm_x4_pos  ;
    v_smap_x5_pos           = pstDmCfg->SMPara.gmm_x5_pos  ;
    v_smap_x6_pos           = pstDmCfg->SMPara.gmm_x6_pos  ;
    v_smap_x7_pos           = pstDmCfg->SMPara.gmm_x7_pos  ;
    v_smap_x8_pos           = pstDmCfg->SMPara.gmm_x8_pos  ;
    v_smap_x1_num           = pstDmCfg->SMPara.gmm_x1_num  ;
    v_smap_x2_num           = pstDmCfg->SMPara.gmm_x2_num  ;
    v_smap_x3_num           = pstDmCfg->SMPara.gmm_x3_num  ;
    v_smap_x4_num           = pstDmCfg->SMPara.gmm_x4_num  ;
    v_smap_x5_num           = pstDmCfg->SMPara.gmm_x5_num  ;
    v_smap_x6_num           = pstDmCfg->SMPara.gmm_x6_num  ;
    v_smap_x7_num           = pstDmCfg->SMPara.gmm_x7_num  ;
    v_smap_x8_num           = pstDmCfg->SMPara.gmm_x8_num  ;

    v_gmm_x1_step           = pstDmCfg->GammaPara.gmm_x1_step ;
    v_gmm_x2_step           = pstDmCfg->GammaPara.gmm_x2_step ;
    v_gmm_x3_step           = pstDmCfg->GammaPara.gmm_x3_step ;
    v_gmm_x4_step           = pstDmCfg->GammaPara.gmm_x4_step ;
    v_gmm_x5_step           = pstDmCfg->GammaPara.gmm_x5_step ;
    v_gmm_x6_step           = pstDmCfg->GammaPara.gmm_x6_step ;
    v_gmm_x7_step           = pstDmCfg->GammaPara.gmm_x7_step ;
    v_gmm_x8_step           = pstDmCfg->GammaPara.gmm_x8_step ;
    v_gmm_x1_pos            = pstDmCfg->GammaPara.gmm_x1_pos  ;
    v_gmm_x2_pos            = pstDmCfg->GammaPara.gmm_x2_pos  ;
    v_gmm_x3_pos            = pstDmCfg->GammaPara.gmm_x3_pos  ;
    v_gmm_x4_pos            = pstDmCfg->GammaPara.gmm_x4_pos  ;
    v_gmm_x5_pos            = pstDmCfg->GammaPara.gmm_x5_pos  ;
    v_gmm_x6_pos            = pstDmCfg->GammaPara.gmm_x6_pos  ;
    v_gmm_x7_pos            = pstDmCfg->GammaPara.gmm_x7_pos  ;
    v_gmm_x8_pos            = pstDmCfg->GammaPara.gmm_x8_pos  ;
    v_gmm_x1_num            = pstDmCfg->GammaPara.gmm_x1_num  ;
    v_gmm_x2_num            = pstDmCfg->GammaPara.gmm_x2_num  ;
    v_gmm_x3_num            = pstDmCfg->GammaPara.gmm_x3_num  ;
    v_gmm_x4_num            = pstDmCfg->GammaPara.gmm_x4_num  ;
    v_gmm_x5_num            = pstDmCfg->GammaPara.gmm_x5_num  ;
    v_gmm_x6_num            = pstDmCfg->GammaPara.gmm_x6_num  ;
    v_gmm_x7_num            = pstDmCfg->GammaPara.gmm_x7_num  ;
    v_gmm_x8_num            = pstDmCfg->GammaPara.gmm_x8_num  ;

    vdm_csc_0_in_dc         = pstDmCfg->s32DcInSrc2Disp[0]   ;
    vdm_csc_1_in_dc         = pstDmCfg->s32DcInSrc2Disp[1]   ;
    vdm_csc_2_in_dc         = pstDmCfg->s32DcInSrc2Disp[2]   ;
    vdm_csc_0_out_dc        = pstDmCfg->s32DcOutSrc2Disp[0]   ;
    vdm_csc_1_out_dc        = pstDmCfg->s32DcOutSrc2Disp[1]   ;
    vdm_csc_2_out_dc        = pstDmCfg->s32DcOutSrc2Disp[2]   ;
    vdm_coef00_csc          = pstDmCfg->s16M33Src2Disp[0][0] ;
    vdm_coef01_csc          = pstDmCfg->s16M33Src2Disp[0][1] ;
    vdm_coef02_csc          = pstDmCfg->s16M33Src2Disp[0][2] ;
    vdm_coef10_csc          = pstDmCfg->s16M33Src2Disp[1][0] ;
    vdm_coef11_csc          = pstDmCfg->s16M33Src2Disp[1][1] ;
    vdm_coef12_csc          = pstDmCfg->s16M33Src2Disp[1][2] ;
    vdm_coef20_csc          = pstDmCfg->s16M33Src2Disp[2][0] ;
    vdm_coef21_csc          = pstDmCfg->s16M33Src2Disp[2][1] ;
    vdm_coef22_csc          = pstDmCfg->s16M33Src2Disp[2][2] ;
    vdm_csc_scale           = pstDmCfg->u16ScaleSrc2Disp     ;
    vdm_csc_clip_min        = pstDmCfg->u32ClipMinCSC        ;
    vdm_csc_clip_max        = pstDmCfg->u32ClipMaxCSC        ;

    vdm_00_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[0][0] ;
    vdm_01_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[0][1] ;
    vdm_02_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[0][2] ;
    vdm_03_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[1][0] ;
    vdm_04_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[1][1] ;
    vdm_05_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[1][2] ;
    vdm_06_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[2][0] ;
    vdm_07_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[2][1] ;
    vdm_08_yuv2rgb          = pstDmCfg->s16M33YUV2RGB0[2][2] ;
    vdm_10_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[0][0] ;
    vdm_11_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[0][1] ;
    vdm_12_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[0][2] ;
    vdm_13_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[1][0] ;
    vdm_14_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[1][1] ;
    vdm_15_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[1][2] ;
    vdm_16_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[2][0] ;
    vdm_17_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[2][1] ;
    vdm_18_yuv2rgb          = pstDmCfg->s16M33YUV2RGB1[2][2] ;
    vdm_v0_yuv2rgbscale2p   = pstDmCfg->u16ScaleYUV2RGB_v0   ;
    vdm_v1_yuv2rgbscale2p   = pstDmCfg->u16ScaleYUV2RGB_v1   ;
    vdm_yuv2rgb_00_in_dc    = pstDmCfg->s32InOffsetYUV2RGB0[0]  ;
    vdm_yuv2rgb_01_in_dc    = pstDmCfg->s32InOffsetYUV2RGB0[1]  ;
    vdm_yuv2rgb_02_in_dc    = pstDmCfg->s32InOffsetYUV2RGB0[2]  ;
    vdm_yuv2rgb_00_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB0[0] ;
    vdm_yuv2rgb_01_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB0[1] ;
    vdm_yuv2rgb_02_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB0[2] ;
    vdm_yuv2rgb_10_in_dc    = pstDmCfg->s32InOffsetYUV2RGB1[0]  ;
    vdm_yuv2rgb_11_in_dc    = pstDmCfg->s32InOffsetYUV2RGB1[1]  ;
    vdm_yuv2rgb_12_in_dc    = pstDmCfg->s32InOffsetYUV2RGB1[2]  ;
    vdm_yuv2rgb_10_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB1[0] ;
    vdm_yuv2rgb_11_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB1[1] ;
    vdm_yuv2rgb_12_out_dc   = pstDmCfg->s32OutOffsetYUV2RGB1[2] ;
    vdm_v0_yuv2rgb_clip_min = pstDmCfg->u16ClipMinYUV2RGB_v0    ;
    vdm_v0_yuv2rgb_clip_max = pstDmCfg->u16ClipMaxYUV2RGB_v0    ;
    vdm_v1_yuv2rgb_clip_min = pstDmCfg->u16ClipMinYUV2RGB_v1    ;
    vdm_v1_yuv2rgb_clip_max = pstDmCfg->u16ClipMaxYUV2RGB_v1    ;
    vdm_00_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[0][0]     ;
    vdm_01_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[0][1]     ;
    vdm_02_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[0][2]     ;
    vdm_10_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[1][0]     ;
    vdm_11_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[1][1]     ;
    vdm_12_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[1][2]     ;
    vdm_20_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[2][0]     ;
    vdm_21_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[2][1]     ;
    vdm_22_rgb2yuv          = pstDmCfg->s16M33RGB2YUV[2][2]     ;
    vdm_rgb2yuvscale2p      = pstDmCfg->u16ScaleRGB2YUV         ;
    vdm_rgb2yuv_0_in_dc     = pstDmCfg->s16InOffsetRGB2YUV[0]   ;
    vdm_rgb2yuv_1_in_dc     = pstDmCfg->s16InOffsetRGB2YUV[1]   ;
    vdm_rgb2yuv_2_in_dc     = pstDmCfg->s16InOffsetRGB2YUV[2]   ;
    vdm_rgb2yuv_0_out_dc    = pstDmCfg->s16OutOffsetRGB2YUV[0]  ;
    vdm_rgb2yuv_1_out_dc    = pstDmCfg->s16OutOffsetRGB2YUV[1]  ;
    vdm_rgb2yuv_2_out_dc    = pstDmCfg->s16OutOffsetRGB2YUV[2]  ;
    vdm_rgb2yuv_clip_y_min  = pstDmCfg->u16ClipMinRGB2YUV_Y     ;
    vdm_rgb2yuv_clip_uv_min = pstDmCfg->u16ClipMinRGB2YUV_C     ;
    vdm_rgb2yuv_clip_y_max  = pstDmCfg->u16ClipMaxRGB2YUV_Y     ;
    vdm_rgb2yuv_clip_uv_max = pstDmCfg->u16ClipMaxRGB2YUV_C     ;
    vdm_cadj_scale2p        = pstDmCfg->u16ScaleCoefSM          ;

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


#if EDA_TEST
    //reg value print
    cout << "================ reg_value print begin ================" << endl ;
    cout << "vdm_ck_gt_en    = " << dec << vdm_ck_gt_en    << endl;
    cout << "vdm_tmap_in_bdp = " << dec << vdm_tmap_in_bdp << endl;
    cout << "vdm_csc_bind = " << dec << vdm_csc_bind << endl;
    cout << "vdm_gmm_en = " << dec << vdm_gmm_en << endl;
    cout << "vdm_tmap_en = " << dec << vdm_tmap_en << endl;
    cout << "vdm_degmm_en = " << dec << vdm_degmm_en << endl;
    cout << "vdm_en = " << dec << vdm_en << endl;
    cout << "vdm_luma_coef0_tmap = " << dec << vdm_luma_coef0_tmap << endl;
    cout << "vdm_luma_coef1_tmap = " << dec << vdm_luma_coef1_tmap << endl;
    cout << "vdm_luma_coef2_tmap = " << dec << vdm_luma_coef2_tmap << endl;
    cout << "vdm_tmap_luma_scale = " << dec << vdm_tmap_luma_scale << endl;
    cout << "vdm_tmap_coef_scale = " << dec << vdm_tmap_coef_scale << endl;
    cout << "vdm_tmap_out_clip_min = " << dec << vdm_tmap_out_clip_min << endl;
    cout << "vdm_tmap_out_clip_max = " << dec << vdm_tmap_out_clip_max << endl;
    cout << "vdm_tmap_out_dc0 = " << dec << vdm_tmap_out_dc0 << endl;
    cout << "vdm_tmap_out_dc1 = " << dec << vdm_tmap_out_dc1 << endl;
    cout << "vdm_tmap_out_dc2 = " << dec << vdm_tmap_out_dc2 << endl;
    cout << "vdm_degamma_rd_en = " << dec << vdm_degamma_rd_en << endl;
    cout << "vdm_degamma_para_data = " << dec << vdm_degamma_para_data << endl;
    cout << "v_degmm_x1_step = " << dec << v_degmm_x1_step << endl;
    cout << "v_degmm_x2_step = " << dec << v_degmm_x2_step << endl;
    cout << "v_degmm_x3_step = " << dec << v_degmm_x3_step << endl;
    cout << "v_degmm_x4_step = " << dec << v_degmm_x4_step << endl;
    cout << "v_degmm_x5_step = " << dec << v_degmm_x5_step << endl;
    cout << "v_degmm_x6_step = " << dec << v_degmm_x6_step << endl;
    cout << "v_degmm_x7_step = " << dec << v_degmm_x7_step << endl;
    cout << "v_degmm_x8_step = " << dec << v_degmm_x8_step << endl;
    cout << "v_degmm_x1_pos = " << dec << v_degmm_x1_pos << endl;
    cout << "v_degmm_x2_pos = " << dec << v_degmm_x2_pos << endl;
    cout << "v_degmm_x3_pos = " << dec << v_degmm_x3_pos << endl;
    cout << "v_degmm_x4_pos = " << dec << v_degmm_x4_pos << endl;
    cout << "v_degmm_x5_pos = " << dec << v_degmm_x5_pos << endl;
    cout << "v_degmm_x6_pos = " << dec << v_degmm_x6_pos << endl;
    cout << "v_degmm_x7_pos = " << dec << v_degmm_x7_pos << endl;
    cout << "v_degmm_x8_pos = " << dec << v_degmm_x8_pos << endl;
    cout << "v_degmm_x1_num = " << dec << v_degmm_x1_num << endl;
    cout << "v_degmm_x2_num = " << dec << v_degmm_x2_num << endl;
    cout << "v_degmm_x3_num = " << dec << v_degmm_x3_num << endl;
    cout << "v_degmm_x4_num = " << dec << v_degmm_x4_num << endl;
    cout << "v_degmm_x5_num = " << dec << v_degmm_x5_num << endl;
    cout << "v_degmm_x6_num = " << dec << v_degmm_x6_num << endl;
    cout << "v_degmm_x7_num = " << dec << v_degmm_x7_num << endl;
    cout << "v_degmm_x8_num = " << dec << v_degmm_x8_num << endl;
    cout << "vdm_tmap_rd_en = " << dec << vdm_tmap_rd_en << endl;
    cout << "vdm_sm_rd_en = " << dec << vdm_sm_rd_en << endl;
    cout << "vdm_tmap_para_data = " << dec << vdm_tmap_para_data << endl;
    cout << "v_tmap_x1_step = " << dec << v_tmap_x1_step << endl;
    cout << "v_tmap_x2_step = " << dec << v_tmap_x2_step << endl;
    cout << "v_tmap_x3_step = " << dec << v_tmap_x3_step << endl;
    cout << "v_tmap_x4_step = " << dec << v_tmap_x4_step << endl;
    cout << "v_tmap_x5_step = " << dec << v_tmap_x5_step << endl;
    cout << "v_tmap_x6_step = " << dec << v_tmap_x6_step << endl;
    cout << "v_tmap_x7_step = " << dec << v_tmap_x7_step << endl;
    cout << "v_tmap_x8_step = " << dec << v_tmap_x8_step << endl;
    cout << "v_tmap_x1_pos  = " << dec << v_tmap_x1_pos << endl;
    cout << "v_tmap_x2_pos  = " << dec << v_tmap_x2_pos << endl;
    cout << "v_tmap_x3_pos  = " << dec << v_tmap_x3_pos << endl;
    cout << "v_tmap_x4_pos  = " << dec << v_tmap_x4_pos << endl;
    cout << "v_tmap_x5_pos  = " << dec << v_tmap_x5_pos << endl;
    cout << "v_tmap_x6_pos  = " << dec << v_tmap_x6_pos << endl;
    cout << "v_tmap_x7_pos  = " << dec << v_tmap_x7_pos << endl;
    cout << "v_tmap_x8_pos  = " << dec << v_tmap_x8_pos << endl;
    cout << "v_tmap_x1_num  = " << dec << v_tmap_x1_num << endl;
    cout << "v_tmap_x2_num  = " << dec << v_tmap_x2_num << endl;
    cout << "v_tmap_x3_num  = " << dec << v_tmap_x3_num << endl;
    cout << "v_tmap_x4_num  = " << dec << v_tmap_x4_num << endl;
    cout << "v_tmap_x5_num  = " << dec << v_tmap_x5_num << endl;
    cout << "v_tmap_x6_num  = " << dec << v_tmap_x6_num << endl;
    cout << "v_tmap_x7_num  = " << dec << v_tmap_x7_num << endl;
    cout << "v_tmap_x8_num  = " << dec << v_tmap_x8_num << endl;
    cout << "v_smap_x1_step = " << dec << v_smap_x1_step << endl;
    cout << "v_smap_x2_step = " << dec << v_smap_x2_step << endl;
    cout << "v_smap_x3_step = " << dec << v_smap_x3_step << endl;
    cout << "v_smap_x4_step = " << dec << v_smap_x4_step << endl;
    cout << "v_smap_x5_step = " << dec << v_smap_x5_step << endl;
    cout << "v_smap_x6_step = " << dec << v_smap_x6_step << endl;
    cout << "v_smap_x7_step = " << dec << v_smap_x7_step << endl;
    cout << "v_smap_x8_step = " << dec << v_smap_x8_step << endl;
    cout << "v_smap_x1_pos  = " << dec << v_smap_x1_pos << endl;
    cout << "v_smap_x2_pos  = " << dec << v_smap_x2_pos << endl;
    cout << "v_smap_x3_pos  = " << dec << v_smap_x3_pos << endl;
    cout << "v_smap_x4_pos  = " << dec << v_smap_x4_pos << endl;
    cout << "v_smap_x5_pos  = " << dec << v_smap_x5_pos << endl;
    cout << "v_smap_x6_pos  = " << dec << v_smap_x6_pos << endl;
    cout << "v_smap_x7_pos  = " << dec << v_smap_x7_pos << endl;
    cout << "v_smap_x8_pos  = " << dec << v_smap_x8_pos << endl;
    cout << "v_smap_x1_num  = " << dec << v_smap_x1_num << endl;
    cout << "v_smap_x2_num  = " << dec << v_smap_x2_num << endl;
    cout << "v_smap_x3_num  = " << dec << v_smap_x3_num << endl;
    cout << "v_smap_x4_num  = " << dec << v_smap_x4_num << endl;
    cout << "v_smap_x5_num  = " << dec << v_smap_x5_num << endl;
    cout << "v_smap_x6_num  = " << dec << v_smap_x6_num << endl;
    cout << "v_smap_x7_num  = " << dec << v_smap_x7_num << endl;
    cout << "v_smap_x8_num  = " << dec << v_smap_x8_num << endl;
    cout << "vdm_gamma_rd_en = " << dec << vdm_gamma_rd_en << endl;
    cout << "vdm_gamma_para_data = " << dec << vdm_gamma_para_data << endl;
    cout << "v_gmm_x1_step = " << dec << v_gmm_x1_step << endl;
    cout << "v_gmm_x2_step = " << dec << v_gmm_x2_step << endl;
    cout << "v_gmm_x3_step = " << dec << v_gmm_x3_step << endl;
    cout << "v_gmm_x4_step = " << dec << v_gmm_x4_step << endl;
    cout << "v_gmm_x5_step = " << dec << v_gmm_x5_step << endl;
    cout << "v_gmm_x6_step = " << dec << v_gmm_x6_step << endl;
    cout << "v_gmm_x7_step = " << dec << v_gmm_x7_step << endl;
    cout << "v_gmm_x8_step = " << dec << v_gmm_x8_step << endl;
    cout << "v_gmm_x1_pos = " << dec << v_gmm_x1_pos << endl;
    cout << "v_gmm_x2_pos = " << dec << v_gmm_x2_pos << endl;
    cout << "v_gmm_x3_pos = " << dec << v_gmm_x3_pos << endl;
    cout << "v_gmm_x4_pos = " << dec << v_gmm_x4_pos << endl;
    cout << "v_gmm_x5_pos = " << dec << v_gmm_x5_pos << endl;
    cout << "v_gmm_x6_pos = " << dec << v_gmm_x6_pos << endl;
    cout << "v_gmm_x7_pos = " << dec << v_gmm_x7_pos << endl;
    cout << "v_gmm_x8_pos = " << dec << v_gmm_x8_pos << endl;
    cout << "v_gmm_x1_num = " << dec << v_gmm_x1_num << endl;
    cout << "v_gmm_x2_num = " << dec << v_gmm_x2_num << endl;
    cout << "v_gmm_x3_num = " << dec << v_gmm_x3_num << endl;
    cout << "v_gmm_x4_num = " << dec << v_gmm_x4_num << endl;
    cout << "v_gmm_x5_num = " << dec << v_gmm_x5_num << endl;
    cout << "v_gmm_x6_num = " << dec << v_gmm_x6_num << endl;
    cout << "v_gmm_x7_num = " << dec << v_gmm_x7_num << endl;
    cout << "v_gmm_x8_num = " << dec << v_gmm_x8_num << endl;
    cout << "vdm_csc_en = " << dec << vdm_csc_en << endl;
    cout << "vdm_coef00_csc = " << dec << vdm_coef00_csc << endl;
    cout << "vdm_coef01_csc = " << dec << vdm_coef01_csc << endl;
    cout << "vdm_coef02_csc = " << dec << vdm_coef02_csc << endl;
    cout << "vdm_coef10_csc = " << dec << vdm_coef10_csc << endl;
    cout << "vdm_coef11_csc = " << dec << vdm_coef11_csc << endl;
    cout << "vdm_coef12_csc = " << dec << vdm_coef12_csc << endl;
    cout << "vdm_coef20_csc = " << dec << vdm_coef20_csc << endl;
    cout << "vdm_coef21_csc = " << dec << vdm_coef21_csc << endl;
    cout << "vdm_coef22_csc = " << dec << vdm_coef22_csc << endl;
    cout << "vdm_csc_scale = " << dec << vdm_csc_scale << endl;
    cout << "vdm_csc_clip_min = " << dec << vdm_csc_clip_min << endl;
    cout << "vdm_csc_clip_max = " << dec << vdm_csc_clip_max << endl;
    cout << "vdm_csc_0_in_dc = " << dec << vdm_csc_0_in_dc << endl;
    cout << "vdm_csc_1_in_dc = " << dec << vdm_csc_1_in_dc << endl;
    cout << "vdm_csc_2_in_dc = " << dec << vdm_csc_2_in_dc << endl;
    cout << "vdm_csc_0_out_dc = " << dec << vdm_csc_0_out_dc << endl;
    cout << "vdm_csc_1_out_dc = " << dec << vdm_csc_1_out_dc << endl;
    cout << "vdm_csc_2_out_dc = " << dec << vdm_csc_2_out_dc << endl;
    cout << "vdm_v1_gamma_en = " << dec << vdm_v1_gamma_en << endl;
    cout << "vdm_v0_gamma_en = " << dec << vdm_v0_gamma_en << endl;
    cout << "vdm_v1_csc_en = " << dec << vdm_v1_csc_en << endl;
    cout << "vdm_v0_csc_en = " << dec << vdm_v0_csc_en << endl;
    cout << "vdm_yuv2rgb_en = " << dec << vdm_yuv2rgb_en << endl;
    cout << "vdm_v0_cl_en  = " << dec << vdm_v0_cl_en  << endl;
    cout << "vdm_v1_cl_en  = " << dec << vdm_v1_cl_en  << endl;
    cout << "vdm_00_yuv2rgb = " << dec << vdm_00_yuv2rgb << endl;
    cout << "vdm_01_yuv2rgb = " << dec << vdm_01_yuv2rgb << endl;
    cout << "vdm_02_yuv2rgb = " << dec << vdm_02_yuv2rgb << endl;
    cout << "vdm_03_yuv2rgb = " << dec << vdm_03_yuv2rgb << endl;
    cout << "vdm_04_yuv2rgb = " << dec << vdm_04_yuv2rgb << endl;
    cout << "vdm_05_yuv2rgb = " << dec << vdm_05_yuv2rgb << endl;
    cout << "vdm_06_yuv2rgb = " << dec << vdm_06_yuv2rgb << endl;
    cout << "vdm_07_yuv2rgb = " << dec << vdm_07_yuv2rgb << endl;
    cout << "vdm_08_yuv2rgb = " << dec << vdm_08_yuv2rgb << endl;
    cout << "vdm_10_yuv2rgb = " << dec << vdm_10_yuv2rgb << endl;
    cout << "vdm_11_yuv2rgb = " << dec << vdm_11_yuv2rgb << endl;
    cout << "vdm_12_yuv2rgb = " << dec << vdm_12_yuv2rgb << endl;
    cout << "vdm_13_yuv2rgb = " << dec << vdm_13_yuv2rgb << endl;
    cout << "vdm_14_yuv2rgb = " << dec << vdm_14_yuv2rgb << endl;
    cout << "vdm_15_yuv2rgb = " << dec << vdm_15_yuv2rgb << endl;
    cout << "vdm_16_yuv2rgb = " << dec << vdm_16_yuv2rgb << endl;
    cout << "vdm_17_yuv2rgb = " << dec << vdm_17_yuv2rgb << endl;
    cout << "vdm_18_yuv2rgb = " << dec << vdm_18_yuv2rgb << endl;
    cout << "vdm_v0_yuv2rgbscale2p = " << dec << vdm_v0_yuv2rgbscale2p << endl;
    cout << "vdm_v1_yuv2rgbscale2p = " << dec << vdm_v1_yuv2rgbscale2p << endl;
    cout << "vdm_yuv2rgb_00_in_dc = " << dec << vdm_yuv2rgb_00_in_dc << endl;
    cout << "vdm_yuv2rgb_01_in_dc = " << dec << vdm_yuv2rgb_01_in_dc << endl;
    cout << "vdm_yuv2rgb_02_in_dc = " << dec << vdm_yuv2rgb_02_in_dc << endl;
    cout << "vdm_yuv2rgb_00_out_dc = " << dec << vdm_yuv2rgb_00_out_dc << endl;
    cout << "vdm_yuv2rgb_01_out_dc = " << dec << vdm_yuv2rgb_01_out_dc << endl;
    cout << "vdm_yuv2rgb_02_out_dc = " << dec << vdm_yuv2rgb_02_out_dc << endl;
    cout << "vdm_yuv2rgb_10_in_dc = " << dec << vdm_yuv2rgb_10_in_dc << endl;
    cout << "vdm_yuv2rgb_11_in_dc = " << dec << vdm_yuv2rgb_11_in_dc << endl;
    cout << "vdm_yuv2rgb_12_in_dc = " << dec << vdm_yuv2rgb_12_in_dc << endl;
    cout << "vdm_yuv2rgb_10_out_dc = " << dec << vdm_yuv2rgb_10_out_dc << endl;
    cout << "vdm_yuv2rgb_11_out_dc = " << dec << vdm_yuv2rgb_11_out_dc << endl;
    cout << "vdm_yuv2rgb_12_out_dc = " << dec << vdm_yuv2rgb_12_out_dc << endl;
    cout << "vdm_v0_yuv2rgb_clip_min = " << dec << vdm_v0_yuv2rgb_clip_min << endl;
    cout << "vdm_v0_yuv2rgb_clip_max = " << dec << vdm_v0_yuv2rgb_clip_max << endl;
    cout << "vdm_v1_yuv2rgb_clip_min = " << dec << vdm_v1_yuv2rgb_clip_min << endl;
    cout << "vdm_v1_yuv2rgb_clip_max = " << dec << vdm_v1_yuv2rgb_clip_max << endl;
    cout << "vdm_rgb2yuv_en = " << dec << vdm_rgb2yuv_en << endl;
    cout << "vdm_rgb2yuv_pip_en = " << dec << vdm_rgb2yuv_pip_en << endl;
    cout << "vdm_cadj_en = " << dec << vdm_cadj_en << endl;
    cout << "vdm_00_rgb2yuv = " << dec << vdm_00_rgb2yuv << endl;
    cout << "vdm_01_rgb2yuv = " << dec << vdm_01_rgb2yuv << endl;
    cout << "vdm_02_rgb2yuv = " << dec << vdm_02_rgb2yuv << endl;
    cout << "vdm_10_rgb2yuv = " << dec << vdm_10_rgb2yuv << endl;
    cout << "vdm_11_rgb2yuv = " << dec << vdm_11_rgb2yuv << endl;
    cout << "vdm_12_rgb2yuv = " << dec << vdm_12_rgb2yuv << endl;
    cout << "vdm_20_rgb2yuv = " << dec << vdm_20_rgb2yuv << endl;
    cout << "vdm_21_rgb2yuv = " << dec << vdm_21_rgb2yuv << endl;
    cout << "vdm_22_rgb2yuv = " << dec << vdm_22_rgb2yuv << endl;
    cout << "vdm_rgb2yuvscale2p = " << dec << vdm_rgb2yuvscale2p << endl;
    cout << "vdm_cadj_scale2p   = " << dec << vdm_cadj_scale2p << endl;
    cout << "vdm_rgb2yuv_0_in_dc = " << dec << vdm_rgb2yuv_0_in_dc << endl;
    cout << "vdm_rgb2yuv_1_in_dc = " << dec << vdm_rgb2yuv_1_in_dc << endl;
    cout << "vdm_rgb2yuv_2_in_dc = " << dec << vdm_rgb2yuv_2_in_dc << endl;
    cout << "vdm_rgb2yuv_0_out_dc = " << dec << vdm_rgb2yuv_0_out_dc << endl;
    cout << "vdm_rgb2yuv_1_out_dc = " << dec << vdm_rgb2yuv_1_out_dc << endl;
    cout << "vdm_rgb2yuv_2_out_dc = " << dec << vdm_rgb2yuv_2_out_dc << endl;
    cout << "vdm_rgb2yuv_clip_y_min = " << dec << vdm_rgb2yuv_clip_y_min << endl;
    cout << "vdm_rgb2yuv_clip_uv_min = " << dec << vdm_rgb2yuv_clip_uv_min << endl;
    cout << "vdm_rgb2yuv_clip_y_max = " << dec << vdm_rgb2yuv_clip_y_max << endl;
    cout << "vdm_rgb2yuv_clip_uv_max = " << dec << vdm_rgb2yuv_clip_uv_max << endl;
    cout << "vdm_dither_round_unlim = " << dec << vdm_dither_round_unlim << endl;
    cout << "vdm_dither_en = " << dec << vdm_dither_en << endl;
    cout << "vdm_dither_round = " << dec << vdm_dither_round << endl;
    cout << "vdm_dither_domain_mode = " << dec << vdm_dither_domain_mode << endl;
    cout << "vdm_dither_tap_mode = " << dec << vdm_dither_tap_mode << endl;
    cout << "vdm_dither_sed_y0 = " << dec << vdm_dither_sed_y0 << endl;
    cout << "vdm_dither_sed_u0 = " << dec << vdm_dither_sed_u0 << endl;
    cout << "vdm_dither_sed_v0 = " << dec << vdm_dither_sed_v0 << endl;
    cout << "vdm_dither_sed_w0 = " << dec << vdm_dither_sed_w0 << endl;
    cout << "vdm_dither_sed_y1 = " << dec << vdm_dither_sed_y1 << endl;
    cout << "vdm_dither_sed_u1 = " << dec << vdm_dither_sed_u1 << endl;
    cout << "vdm_dither_sed_v1 = " << dec << vdm_dither_sed_v1 << endl;
    cout << "vdm_dither_sed_w1 = " << dec << vdm_dither_sed_w1 << endl;
    cout << "vdm_dither_sed_y2 = " << dec << vdm_dither_sed_y2 << endl;
    cout << "vdm_dither_sed_u2 = " << dec << vdm_dither_sed_u2 << endl;
    cout << "vdm_dither_sed_v2 = " << dec << vdm_dither_sed_v2 << endl;
    cout << "vdm_dither_sed_w2 = " << dec << vdm_dither_sed_w2 << endl;
    cout << "vdm_dither_sed_y3 = " << dec << vdm_dither_sed_y3 << endl;
    cout << "vdm_dither_sed_u3 = " << dec << vdm_dither_sed_u3 << endl;
    cout << "vdm_dither_sed_v3 = " << dec << vdm_dither_sed_v3 << endl;
    cout << "vdm_dither_sed_w3 = " << dec << vdm_dither_sed_w3 << endl;
    cout << "vdm_dither_thr_max = " << dec << vdm_dither_thr_max << endl;
    cout << "vdm_dither_thr_min = " << dec << vdm_dither_thr_min << endl;
    cout << "================ reg_value print end ================" << endl ;
#endif
	//drv transfer
    VDP_HIHDR_SetVdmCkGtEn( vdm_ck_gt_en);
	VDP_HIHDR_SetVdmTmapInBdp( vdm_tmap_in_bdp);
	VDP_HIHDR_SetVdmCscBind( vdm_csc_bind);
	VDP_HIHDR_SetVdmGmmEn( vdm_gmm_en);
	VDP_HIHDR_SetVdmTmapEn( vdm_tmap_en);
	VDP_HIHDR_SetVdmDegmmEn( vdm_degmm_en);
	VDP_HIHDR_SetVdmEn( vdm_en);
	VDP_HIHDR_SetVdmLumaCoef0Tmap( vdm_luma_coef0_tmap);
	VDP_HIHDR_SetVdmLumaCoef1Tmap( vdm_luma_coef1_tmap);
	VDP_HIHDR_SetVdmLumaCoef2Tmap( vdm_luma_coef2_tmap);
	VDP_HIHDR_SetVdmTmapLumaScale( vdm_tmap_luma_scale);
	VDP_HIHDR_SetVdmTmapCoefScale( vdm_tmap_coef_scale);
	VDP_HIHDR_SetVdmTmapOutClipMin( vdm_tmap_out_clip_min);
	VDP_HIHDR_SetVdmTmapOutClipMax( vdm_tmap_out_clip_max);
	VDP_HIHDR_SetVdmTmapOutDc0( vdm_tmap_out_dc0);
	VDP_HIHDR_SetVdmTmapOutDc1( vdm_tmap_out_dc1);
	VDP_HIHDR_SetVdmTmapOutDc2( vdm_tmap_out_dc2);
	VDP_HIHDR_SetVdmDegammaRdEn( vdm_degamma_rd_en);
	VDP_HIHDR_SetVdmDegammaParaData( vdm_degamma_para_data);
	VDP_HIHDR_SetVDegmmX4Step( v_degmm_x4_step);
	VDP_HIHDR_SetVDegmmX3Step( v_degmm_x3_step);
	VDP_HIHDR_SetVDegmmX2Step( v_degmm_x2_step);
	VDP_HIHDR_SetVDegmmX1Step( v_degmm_x1_step);
	VDP_HIHDR_SetVDegmmX8Step( v_degmm_x8_step);//add
	VDP_HIHDR_SetVDegmmX7Step( v_degmm_x7_step);//add
	VDP_HIHDR_SetVDegmmX6Step( v_degmm_x6_step);//add
	VDP_HIHDR_SetVDegmmX5Step( v_degmm_x5_step);//add
	VDP_HIHDR_SetVDegmmX2Pos( v_degmm_x2_pos);
	VDP_HIHDR_SetVDegmmX1Pos( v_degmm_x1_pos);
	VDP_HIHDR_SetVDegmmX4Pos( v_degmm_x4_pos);
	VDP_HIHDR_SetVDegmmX3Pos( v_degmm_x3_pos);
	VDP_HIHDR_SetVDegmmX6Pos( v_degmm_x6_pos);//add
	VDP_HIHDR_SetVDegmmX5Pos( v_degmm_x5_pos);//add
	VDP_HIHDR_SetVDegmmX8Pos( v_degmm_x8_pos);//add
	VDP_HIHDR_SetVDegmmX7Pos( v_degmm_x7_pos);//add
	VDP_HIHDR_SetVDegmmX4Num( v_degmm_x4_num);
	VDP_HIHDR_SetVDegmmX3Num( v_degmm_x3_num);
	VDP_HIHDR_SetVDegmmX2Num( v_degmm_x2_num);
	VDP_HIHDR_SetVDegmmX1Num( v_degmm_x1_num);
	VDP_HIHDR_SetVDegmmX8Num( v_degmm_x8_num);//add
	VDP_HIHDR_SetVDegmmX7Num( v_degmm_x7_num);//add
	VDP_HIHDR_SetVDegmmX6Num( v_degmm_x6_num);//add
	VDP_HIHDR_SetVDegmmX5Num( v_degmm_x5_num);//add
	VDP_HIHDR_SetVdmSmRdEn( vdm_sm_rd_en);//add
	VDP_HIHDR_SetVdmTmapRdEn( vdm_tmap_rd_en);
	VDP_HIHDR_SetVdmTmapParaData( vdm_tmap_para_data);
	VDP_HIHDR_SetVdmSmParaData( vdm_sm_para_data);//add
	VDP_HIHDR_SetVTmapX4Step( v_tmap_x4_step);
	VDP_HIHDR_SetVTmapX3Step( v_tmap_x3_step);
	VDP_HIHDR_SetVTmapX2Step( v_tmap_x2_step);
	VDP_HIHDR_SetVTmapX1Step( v_tmap_x1_step);
	VDP_HIHDR_SetVTmapX1Pos( v_tmap_x1_pos);
	VDP_HIHDR_SetVTmapX2Pos( v_tmap_x2_pos);
	VDP_HIHDR_SetVTmapX4Num( v_tmap_x4_num);
	VDP_HIHDR_SetVTmapX3Num( v_tmap_x3_num);
	VDP_HIHDR_SetVTmapX2Num( v_tmap_x2_num);
	VDP_HIHDR_SetVTmapX1Num( v_tmap_x1_num);
	VDP_HIHDR_SetVTmapX3Pos( v_tmap_x3_pos);
	VDP_HIHDR_SetVTmapX4Pos( v_tmap_x4_pos);
	VDP_HIHDR_SetVTmapX8Step( v_tmap_x8_step);
	VDP_HIHDR_SetVTmapX7Step( v_tmap_x7_step);
	VDP_HIHDR_SetVTmapX6Step( v_tmap_x6_step);
	VDP_HIHDR_SetVTmapX5Step( v_tmap_x5_step);
	VDP_HIHDR_SetVTmapX5Pos( v_tmap_x5_pos);
	VDP_HIHDR_SetVTmapX6Pos( v_tmap_x6_pos);
	VDP_HIHDR_SetVTmapX8Num( v_tmap_x8_num);
	VDP_HIHDR_SetVTmapX7Num( v_tmap_x7_num);
	VDP_HIHDR_SetVTmapX6Num( v_tmap_x6_num);
	VDP_HIHDR_SetVTmapX5Num( v_tmap_x5_num);
	VDP_HIHDR_SetVTmapX7Pos( v_tmap_x7_pos);
	VDP_HIHDR_SetVTmapX8Pos( v_tmap_x8_pos);
	VDP_HIHDR_SetVSmapX4Step( v_smap_x4_step);
	VDP_HIHDR_SetVSmapX3Step( v_smap_x3_step);
	VDP_HIHDR_SetVSmapX2Step( v_smap_x2_step);
	VDP_HIHDR_SetVSmapX1Step( v_smap_x1_step);
	VDP_HIHDR_SetVSmapX1Pos(  v_smap_x1_pos);
	VDP_HIHDR_SetVSmapX2Pos(  v_smap_x2_pos);
	VDP_HIHDR_SetVSmapX4Num(  v_smap_x4_num);
	VDP_HIHDR_SetVSmapX3Num(  v_smap_x3_num);
	VDP_HIHDR_SetVSmapX2Num(  v_smap_x2_num);
	VDP_HIHDR_SetVSmapX1Num(  v_smap_x1_num);
	VDP_HIHDR_SetVSmapX3Pos(  v_smap_x3_pos);
	VDP_HIHDR_SetVSmapX4Pos(  v_smap_x4_pos);
	VDP_HIHDR_SetVSmapX8Step( v_smap_x8_step);
	VDP_HIHDR_SetVSmapX7Step( v_smap_x7_step);
	VDP_HIHDR_SetVSmapX6Step( v_smap_x6_step);
	VDP_HIHDR_SetVSmapX5Step( v_smap_x5_step);
	VDP_HIHDR_SetVSmapX5Pos(  v_smap_x5_pos);
	VDP_HIHDR_SetVSmapX6Pos(  v_smap_x6_pos);
	VDP_HIHDR_SetVSmapX8Num(  v_smap_x8_num);
	VDP_HIHDR_SetVSmapX7Num(  v_smap_x7_num);
	VDP_HIHDR_SetVSmapX6Num(  v_smap_x6_num);
	VDP_HIHDR_SetVSmapX5Num(  v_smap_x5_num);
	VDP_HIHDR_SetVSmapX7Pos(  v_smap_x7_pos);
	VDP_HIHDR_SetVSmapX8Pos(  v_smap_x8_pos);
	VDP_HIHDR_SetVdmGammaRdEn( vdm_gamma_rd_en);
	VDP_HIHDR_SetVdmGammaParaData( vdm_gamma_para_data);
	VDP_HIHDR_SetVGmmX4Step( v_gmm_x4_step);
	VDP_HIHDR_SetVGmmX3Step( v_gmm_x3_step);
	VDP_HIHDR_SetVGmmX2Step( v_gmm_x2_step);
	VDP_HIHDR_SetVGmmX1Step( v_gmm_x1_step);
	VDP_HIHDR_SetVGmmX1Pos( v_gmm_x1_pos);
	VDP_HIHDR_SetVGmmX2Pos( v_gmm_x2_pos);
	VDP_HIHDR_SetVGmmX4Num( v_gmm_x4_num);
	VDP_HIHDR_SetVGmmX3Num( v_gmm_x3_num);
	VDP_HIHDR_SetVGmmX2Num( v_gmm_x2_num);
	VDP_HIHDR_SetVGmmX1Num( v_gmm_x1_num);
	VDP_HIHDR_SetVGmmX3Pos( v_gmm_x3_pos);
	VDP_HIHDR_SetVGmmX4Pos( v_gmm_x4_pos);
	VDP_HIHDR_SetVGmmX8Step( v_gmm_x8_step);
	VDP_HIHDR_SetVGmmX7Step( v_gmm_x7_step);
	VDP_HIHDR_SetVGmmX6Step( v_gmm_x6_step);
	VDP_HIHDR_SetVGmmX5Step( v_gmm_x5_step);
	VDP_HIHDR_SetVGmmX8Num( v_gmm_x8_num);
	VDP_HIHDR_SetVGmmX7Num( v_gmm_x7_num);
	VDP_HIHDR_SetVGmmX6Num( v_gmm_x6_num);
	VDP_HIHDR_SetVGmmX5Num( v_gmm_x5_num);
	VDP_HIHDR_SetVGmmX5Pos( v_gmm_x5_pos);
	VDP_HIHDR_SetVGmmX6Pos( v_gmm_x6_pos);
	VDP_HIHDR_SetVGmmX7Pos( v_gmm_x7_pos);
	VDP_HIHDR_SetVGmmX8Pos( v_gmm_x8_pos);
	VDP_HIHDR_SetVdmCscEn( vdm_csc_en);
	VDP_HIHDR_SetVdmCoef00Csc( vdm_coef00_csc);
	VDP_HIHDR_SetVdmCoef01Csc( vdm_coef01_csc);
	VDP_HIHDR_SetVdmCoef02Csc( vdm_coef02_csc);
	VDP_HIHDR_SetVdmCoef10Csc( vdm_coef10_csc);
	VDP_HIHDR_SetVdmCoef11Csc( vdm_coef11_csc);
	VDP_HIHDR_SetVdmCoef12Csc( vdm_coef12_csc);
	VDP_HIHDR_SetVdmCoef20Csc( vdm_coef20_csc);
	VDP_HIHDR_SetVdmCoef21Csc( vdm_coef21_csc);
	VDP_HIHDR_SetVdmCoef22Csc( vdm_coef22_csc);
	VDP_HIHDR_SetVdmCscScale( vdm_csc_scale);
	VDP_HIHDR_SetVdmCscClipMin( vdm_csc_clip_min);
	VDP_HIHDR_SetVdmCscClipMax( vdm_csc_clip_max);
	VDP_HIHDR_SetVdmCsc0InDc( vdm_csc_0_in_dc);//add
	VDP_HIHDR_SetVdmCsc1InDc( vdm_csc_1_in_dc);//add
	VDP_HIHDR_SetVdmCsc2InDc( vdm_csc_2_in_dc);//add
	VDP_HIHDR_SetVdmCsc0OutDc( vdm_csc_0_out_dc);//add
	VDP_HIHDR_SetVdmCsc1OutDc( vdm_csc_1_out_dc);//add
	VDP_HIHDR_SetVdmCsc2OutDc( vdm_csc_2_out_dc);//add
	VDP_HIHDR_SetVdmV1GammaEn( vdm_v1_gamma_en);
	VDP_HIHDR_SetVdmV0GammaEn( vdm_v0_gamma_en);
	VDP_HIHDR_SetVdmV1CscEn( vdm_v1_csc_en);
	VDP_HIHDR_SetVdmV0CscEn( vdm_v0_csc_en);
	VDP_HIHDR_SetVdmV0ClEn( vdm_v0_cl_en);//add
	VDP_HIHDR_SetVdmV1ClEn( vdm_v1_cl_en);//add
	VDP_HIHDR_SetVdmY2rEn( vdm_yuv2rgb_en);
	VDP_HIHDR_SetVdm00Yuv2rgb( vdm_00_yuv2rgb);
	VDP_HIHDR_SetVdm01Yuv2rgb( vdm_01_yuv2rgb);
	VDP_HIHDR_SetVdm02Yuv2rgb( vdm_02_yuv2rgb);
	VDP_HIHDR_SetVdm03Yuv2rgb( vdm_03_yuv2rgb);
	VDP_HIHDR_SetVdm04Yuv2rgb( vdm_04_yuv2rgb);
	VDP_HIHDR_SetVdm05Yuv2rgb( vdm_05_yuv2rgb);
	VDP_HIHDR_SetVdm06Yuv2rgb( vdm_06_yuv2rgb);
	VDP_HIHDR_SetVdm07Yuv2rgb( vdm_07_yuv2rgb);
	VDP_HIHDR_SetVdm08Yuv2rgb( vdm_08_yuv2rgb);
	VDP_HIHDR_SetVdm10Yuv2rgb( vdm_10_yuv2rgb);
	VDP_HIHDR_SetVdm11Yuv2rgb( vdm_11_yuv2rgb);
	VDP_HIHDR_SetVdm12Yuv2rgb( vdm_12_yuv2rgb);
	VDP_HIHDR_SetVdm13Yuv2rgb( vdm_13_yuv2rgb);
	VDP_HIHDR_SetVdm14Yuv2rgb( vdm_14_yuv2rgb);
	VDP_HIHDR_SetVdm15Yuv2rgb( vdm_15_yuv2rgb);
	VDP_HIHDR_SetVdm16Yuv2rgb( vdm_16_yuv2rgb);
	VDP_HIHDR_SetVdm17Yuv2rgb( vdm_17_yuv2rgb);
	VDP_HIHDR_SetVdm18Yuv2rgb( vdm_18_yuv2rgb);
	VDP_HIHDR_SetVdmV0Yuv2rgbscale2p( vdm_v0_yuv2rgbscale2p);
	VDP_HIHDR_SetVdmV1Yuv2rgbscale2p( vdm_v1_yuv2rgbscale2p);
	VDP_HIHDR_SetVdmYuv2rgb00InDc( vdm_yuv2rgb_00_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb01InDc( vdm_yuv2rgb_01_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb02InDc( vdm_yuv2rgb_02_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb00OutDc( vdm_yuv2rgb_00_out_dc);
	VDP_HIHDR_SetVdmYuv2rgb01OutDc( vdm_yuv2rgb_01_out_dc);
	VDP_HIHDR_SetVdmYuv2rgb02OutDc( vdm_yuv2rgb_02_out_dc);
	VDP_HIHDR_SetVdmYuv2rgb10InDc( vdm_yuv2rgb_10_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb11InDc( vdm_yuv2rgb_11_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb12InDc( vdm_yuv2rgb_12_in_dc);
	VDP_HIHDR_SetVdmYuv2rgb10OutDc( vdm_yuv2rgb_10_out_dc);
	VDP_HIHDR_SetVdmYuv2rgb11OutDc( vdm_yuv2rgb_11_out_dc);
	VDP_HIHDR_SetVdmYuv2rgb12OutDc( vdm_yuv2rgb_12_out_dc);
	VDP_HIHDR_SetVdmV0Yuv2rgbClipMin( vdm_v0_yuv2rgb_clip_min);
	VDP_HIHDR_SetVdmV0Yuv2rgbClipMax( vdm_v0_yuv2rgb_clip_max);
	VDP_HIHDR_SetVdmV1Yuv2rgbClipMin( vdm_v1_yuv2rgb_clip_min);
	VDP_HIHDR_SetVdmV1Yuv2rgbClipMax( vdm_v1_yuv2rgb_clip_max);
	VDP_HIHDR_SetVdmCadjEn( vdm_cadj_en);//add
	VDP_HIHDR_SetVdmRgb2yuvEn( vdm_rgb2yuv_en);
	VDP_HIHDR_SetVdmR2yPipEn( vdm_rgb2yuv_pip_en);
	VDP_HIHDR_SetVdm00Rgb2yuv( vdm_00_rgb2yuv);
	VDP_HIHDR_SetVdm01Rgb2yuv( vdm_01_rgb2yuv);
	VDP_HIHDR_SetVdm02Rgb2yuv( vdm_02_rgb2yuv);
	VDP_HIHDR_SetVdm10Rgb2yuv( vdm_10_rgb2yuv);
	VDP_HIHDR_SetVdm11Rgb2yuv( vdm_11_rgb2yuv);
	VDP_HIHDR_SetVdm12Rgb2yuv( vdm_12_rgb2yuv);
	VDP_HIHDR_SetVdm20Rgb2yuv( vdm_20_rgb2yuv);
	VDP_HIHDR_SetVdm21Rgb2yuv( vdm_21_rgb2yuv);
	VDP_HIHDR_SetVdm22Rgb2yuv( vdm_22_rgb2yuv);
	VDP_HIHDR_SetVdmCadjScale2p( vdm_cadj_scale2p);
	VDP_HIHDR_SetVdmRgb2yuvscale2p( vdm_rgb2yuvscale2p);
	VDP_HIHDR_SetVdmRgb2yuv0InDc( vdm_rgb2yuv_0_in_dc);
	VDP_HIHDR_SetVdmRgb2yuv1InDc( vdm_rgb2yuv_1_in_dc);
	VDP_HIHDR_SetVdmRgb2yuv2InDc( vdm_rgb2yuv_2_in_dc);
	VDP_HIHDR_SetVdmRgb2yuv0OutDc( vdm_rgb2yuv_0_out_dc);
	VDP_HIHDR_SetVdmRgb2yuv1OutDc( vdm_rgb2yuv_1_out_dc);
	VDP_HIHDR_SetVdmRgb2yuv2OutDc( vdm_rgb2yuv_2_out_dc);
	VDP_HIHDR_SetVdmRgb2yuvClipUvMin( vdm_rgb2yuv_clip_uv_min);//add
	VDP_HIHDR_SetVdmRgb2yuvClipYMin( vdm_rgb2yuv_clip_y_min);//add
	VDP_HIHDR_SetVdmRgb2yuvClipUvMax( vdm_rgb2yuv_clip_uv_max);//add
	VDP_HIHDR_SetVdmRgb2yuvClipYMax( vdm_rgb2yuv_clip_y_max);//add
	VDP_HIHDR_SetVdmDitherRoundUnlim( vdm_dither_round_unlim);
	VDP_HIHDR_SetVdmDitherEn( vdm_dither_en);
// 	VDP_HIHDR_SetVdmDitherMode( vdm_dither_mode);
	VDP_HIHDR_SetVdmDitherRound( vdm_dither_round);
	VDP_HIHDR_SetVdmDitherDomainMode( vdm_dither_domain_mode);
	VDP_HIHDR_SetVdmDitherTapMode( vdm_dither_tap_mode);
	VDP_HIHDR_SetVdmDitherSedY0( vdm_dither_sed_y0);
	VDP_HIHDR_SetVdmDitherSedU0( vdm_dither_sed_u0);
	VDP_HIHDR_SetVdmDitherSedV0( vdm_dither_sed_v0);
	VDP_HIHDR_SetVdmDitherSedW0( vdm_dither_sed_w0);
	VDP_HIHDR_SetVdmDitherSedY1( vdm_dither_sed_y1);
	VDP_HIHDR_SetVdmDitherSedU1( vdm_dither_sed_u1);
	VDP_HIHDR_SetVdmDitherSedV1( vdm_dither_sed_v1);
	VDP_HIHDR_SetVdmDitherSedW1( vdm_dither_sed_w1);
	VDP_HIHDR_SetVdmDitherSedY2( vdm_dither_sed_y2);
	VDP_HIHDR_SetVdmDitherSedU2( vdm_dither_sed_u2);
	VDP_HIHDR_SetVdmDitherSedV2( vdm_dither_sed_v2);
	VDP_HIHDR_SetVdmDitherSedW2( vdm_dither_sed_w2);
	VDP_HIHDR_SetVdmDitherSedY3( vdm_dither_sed_y3);
	VDP_HIHDR_SetVdmDitherSedU3( vdm_dither_sed_u3);
	VDP_HIHDR_SetVdmDitherSedV3( vdm_dither_sed_v3);
	VDP_HIHDR_SetVdmDitherSedW3( vdm_dither_sed_w3);
	VDP_HIHDR_SetVdmDitherThrMax( vdm_dither_thr_max);
	VDP_HIHDR_SetVdmDitherThrMin( vdm_dither_thr_min);
    free(pstDmCfg);
    #endif
}

HI_VOID VDP_DRV_SetYUV2RGB(HI_U32 enLayer, YUV2RGB_MODE_E Yuv2RgbMode, Y2RCfg_t* pY2RCfg)
{
    #if 0
    Y2RCfg_t * pstY2RCfg;

	HI_S16 vdm_00_yuv2rgb        = 0;
	HI_S16 vdm_01_yuv2rgb        = 0;
	HI_S16 vdm_02_yuv2rgb        = 0;
	HI_S16 vdm_03_yuv2rgb        = 0;
	HI_S16 vdm_04_yuv2rgb        = 0;
	HI_S16 vdm_05_yuv2rgb        = 0;
	HI_S16 vdm_06_yuv2rgb        = 0;
	HI_S16 vdm_07_yuv2rgb        = 0;
	HI_S16 vdm_08_yuv2rgb        = 0;
	HI_S16 vdm_10_yuv2rgb        = 0;
	HI_S16 vdm_11_yuv2rgb        = 0;
	HI_S16 vdm_12_yuv2rgb        = 0;
	HI_S16 vdm_13_yuv2rgb        = 0;
	HI_S16 vdm_14_yuv2rgb        = 0;
	HI_S16 vdm_15_yuv2rgb        = 0;
	HI_S16 vdm_16_yuv2rgb        = 0;
	HI_S16 vdm_17_yuv2rgb        = 0;
	HI_S16 vdm_18_yuv2rgb        = 0;
	HI_U16 vdm_v0_yuv2rgbscale2p   = 0;
	HI_U16 vdm_v1_yuv2rgbscale2p   = 0;
	HI_S32 vdm_yuv2rgb_00_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_01_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_02_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_00_out_dc = 0;
	HI_S32 vdm_yuv2rgb_01_out_dc = 0;
	HI_S32 vdm_yuv2rgb_02_out_dc = 0;
	HI_S32 vdm_yuv2rgb_10_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_11_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_12_in_dc  = 0;
	HI_S32 vdm_yuv2rgb_10_out_dc = 0;
	HI_S32 vdm_yuv2rgb_11_out_dc = 0;
	HI_S32 vdm_yuv2rgb_12_out_dc = 0;
	HI_U16 vdm_v0_yuv2rgb_clip_min = 0;
	HI_U16 vdm_v0_yuv2rgb_clip_max = 0;
	HI_U16 vdm_v1_yuv2rgb_clip_min = 0;
	HI_U16 vdm_v1_yuv2rgb_clip_max = 0;

    pstY2RCfg = (Y2RCfg_t *)malloc(sizeof(Y2RCfg_t));

    if(Yuv2RgbMode == YUV2RGB_601)
    {
        pstY2RCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstY2RCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstY2RCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstY2RCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstY2RCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstY2RCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstY2RCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstY2RCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstY2RCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstY2RCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstY2RCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstY2RCfg->u16ScaleYUV2RGB_V0             = 13      ;
        pstY2RCfg->u16ScaleYUV2RGB_V1             = 13      ;
        pstY2RCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstY2RCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstY2RCfg->u16ClipMinYUV2RGB_V0              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V0              = 1023    ;
        pstY2RCfg->u16ClipMinYUV2RGB_V1              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V1              = 1023    ;
    }
    else if(Yuv2RgbMode == YUV2RGB_709)
    {
        pstY2RCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstY2RCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstY2RCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstY2RCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstY2RCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstY2RCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstY2RCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstY2RCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstY2RCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstY2RCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstY2RCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstY2RCfg->u16ScaleYUV2RGB_V0             = 13      ;
        pstY2RCfg->u16ScaleYUV2RGB_V1             = 13      ;
        pstY2RCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstY2RCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstY2RCfg->u16ClipMinYUV2RGB_V0              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V0              = 1023    ;
        pstY2RCfg->u16ClipMinYUV2RGB_V1              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V1              = 1023    ;
    }
    else if(Yuv2RgbMode == YUV2RGB_2020)
    {
        pstY2RCfg->s16M33YUV2RGB0[0][0]           = 9567    ; //BT2020
        pstY2RCfg->s16M33YUV2RGB0[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB0[0][2]           = 13792   ;
        pstY2RCfg->s16M33YUV2RGB0[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[1][1]           = -1539   ;
        pstY2RCfg->s16M33YUV2RGB0[1][2]           = -5344   ;
        pstY2RCfg->s16M33YUV2RGB0[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB0[2][1]           = 17597   ;
        pstY2RCfg->s16M33YUV2RGB0[2][2]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][0]           = 9567    ; //BT709
        pstY2RCfg->s16M33YUV2RGB1[0][1]           = 0       ;
        pstY2RCfg->s16M33YUV2RGB1[0][2]           = 14729   ;
        pstY2RCfg->s16M33YUV2RGB1[1][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[1][1]           = -1752   ;
        pstY2RCfg->s16M33YUV2RGB1[1][2]           = -4379   ;
        pstY2RCfg->s16M33YUV2RGB1[2][0]           = 9567    ;
        pstY2RCfg->s16M33YUV2RGB1[2][1]           = 17356   ;
        pstY2RCfg->s16M33YUV2RGB1[2][2]           = 0       ;
        pstY2RCfg->u16ScaleYUV2RGB_V0             = 13      ;
        pstY2RCfg->u16ScaleYUV2RGB_V1             = 13      ;
        pstY2RCfg->s32InOffsetYUV2RGB0[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB0[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB0[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[2]        = 0       ;
        pstY2RCfg->s32InOffsetYUV2RGB1[0]         = -64     ;
        pstY2RCfg->s32InOffsetYUV2RGB1[1]         = -512    ;
        pstY2RCfg->s32InOffsetYUV2RGB1[2]         = -512    ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[0]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[1]        = 0       ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[2]        = 0       ;
        pstY2RCfg->u16ClipMinYUV2RGB_V0              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V0              = 1023    ;
        pstY2RCfg->u16ClipMinYUV2RGB_V1              = 0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V1              = 1023    ;
    }
    else if(Yuv2RgbMode == YUV2RGB_CFG)
    {
        pstY2RCfg->s16M33YUV2RGB0[0][0]           = pY2RCfg->s16M33YUV2RGB0[0][0]    ; //BT2020
        pstY2RCfg->s16M33YUV2RGB0[0][1]           = pY2RCfg->s16M33YUV2RGB0[0][1]    ;
        pstY2RCfg->s16M33YUV2RGB0[0][2]           = pY2RCfg->s16M33YUV2RGB0[0][2]    ;
        pstY2RCfg->s16M33YUV2RGB0[1][0]           = pY2RCfg->s16M33YUV2RGB0[1][0]    ;
        pstY2RCfg->s16M33YUV2RGB0[1][1]           = pY2RCfg->s16M33YUV2RGB0[1][1]    ;
        pstY2RCfg->s16M33YUV2RGB0[1][2]           = pY2RCfg->s16M33YUV2RGB0[1][2]    ;
        pstY2RCfg->s16M33YUV2RGB0[2][0]           = pY2RCfg->s16M33YUV2RGB0[2][0]    ;
        pstY2RCfg->s16M33YUV2RGB0[2][1]           = pY2RCfg->s16M33YUV2RGB0[2][1]    ;
        pstY2RCfg->s16M33YUV2RGB0[2][2]           = pY2RCfg->s16M33YUV2RGB0[2][2]    ;
        pstY2RCfg->s16M33YUV2RGB1[0][0]           = pY2RCfg->s16M33YUV2RGB1[0][0]    ; //BT709
        pstY2RCfg->s16M33YUV2RGB1[0][1]           = pY2RCfg->s16M33YUV2RGB1[0][1]    ;
        pstY2RCfg->s16M33YUV2RGB1[0][2]           = pY2RCfg->s16M33YUV2RGB1[0][2]    ;
        pstY2RCfg->s16M33YUV2RGB1[1][0]           = pY2RCfg->s16M33YUV2RGB1[1][0]    ;
        pstY2RCfg->s16M33YUV2RGB1[1][1]           = pY2RCfg->s16M33YUV2RGB1[1][1]    ;
        pstY2RCfg->s16M33YUV2RGB1[1][2]           = pY2RCfg->s16M33YUV2RGB1[1][2]    ;
        pstY2RCfg->s16M33YUV2RGB1[2][0]           = pY2RCfg->s16M33YUV2RGB1[2][0]    ;
        pstY2RCfg->s16M33YUV2RGB1[2][1]           = pY2RCfg->s16M33YUV2RGB1[2][1]    ;
        pstY2RCfg->s16M33YUV2RGB1[2][2]           = pY2RCfg->s16M33YUV2RGB1[2][2]    ;
        pstY2RCfg->u16ScaleYUV2RGB_V0             = pY2RCfg->u16ScaleYUV2RGB_V0        ;
        pstY2RCfg->u16ScaleYUV2RGB_V1             = pY2RCfg->u16ScaleYUV2RGB_V1         ;
        pstY2RCfg->s32InOffsetYUV2RGB0[0]         = pY2RCfg->s32InOffsetYUV2RGB0[0]  ;
        pstY2RCfg->s32InOffsetYUV2RGB0[1]         = pY2RCfg->s32InOffsetYUV2RGB0[1]  ;
        pstY2RCfg->s32InOffsetYUV2RGB0[2]         = pY2RCfg->s32InOffsetYUV2RGB0[2]  ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[0]        = pY2RCfg->s32OutOffsetYUV2RGB0[0] ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[1]        = pY2RCfg->s32OutOffsetYUV2RGB0[1] ;
        pstY2RCfg->s32OutOffsetYUV2RGB0[2]        = pY2RCfg->s32OutOffsetYUV2RGB0[2] ;
        pstY2RCfg->s32InOffsetYUV2RGB1[0]         = pY2RCfg->s32InOffsetYUV2RGB1[0]  ;
        pstY2RCfg->s32InOffsetYUV2RGB1[1]         = pY2RCfg->s32InOffsetYUV2RGB1[1]  ;
        pstY2RCfg->s32InOffsetYUV2RGB1[2]         = pY2RCfg->s32InOffsetYUV2RGB1[2]  ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[0]        = pY2RCfg->s32OutOffsetYUV2RGB1[0] ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[1]        = pY2RCfg->s32OutOffsetYUV2RGB1[1] ;
        pstY2RCfg->s32OutOffsetYUV2RGB1[2]        = pY2RCfg->s32OutOffsetYUV2RGB1[2] ;
        pstY2RCfg->u16ClipMinYUV2RGB_V0           = pY2RCfg->u16ClipMinYUV2RGB_V0       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V0           = pY2RCfg->u16ClipMaxYUV2RGB_V0       ;
        pstY2RCfg->u16ClipMinYUV2RGB_V1           = pY2RCfg->u16ClipMinYUV2RGB_V1       ;
        pstY2RCfg->u16ClipMaxYUV2RGB_V1           = pY2RCfg->u16ClipMaxYUV2RGB_V1       ;
    }
    else
    {
        VDP_PRINT("Error! Yuv2RgbMode : No this Mode!!! \n");
    }

    vdm_00_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[0][0] ;
    vdm_01_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[0][1] ;
    vdm_02_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[0][2] ;
    vdm_03_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[1][0] ;
    vdm_04_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[1][1] ;
    vdm_05_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[1][2] ;
    vdm_06_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[2][0] ;
    vdm_07_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[2][1] ;
    vdm_08_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB0[2][2] ;
    vdm_10_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[0][0] ;
    vdm_11_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[0][1] ;
    vdm_12_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[0][2] ;
    vdm_13_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[1][0] ;
    vdm_14_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[1][1] ;
    vdm_15_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[1][2] ;
    vdm_16_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[2][0] ;
    vdm_17_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[2][1] ;
    vdm_18_yuv2rgb     = pstY2RCfg->s16M33YUV2RGB1[2][2] ;
    vdm_v0_yuv2rgbscale2p   = pstY2RCfg->u16ScaleYUV2RGB_V0   ;
    vdm_v1_yuv2rgbscale2p   = pstY2RCfg->u16ScaleYUV2RGB_V1   ;
    vdm_yuv2rgb_00_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB0[0]  ;
    vdm_yuv2rgb_01_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB0[1]  ;
    vdm_yuv2rgb_02_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB0[2]  ;
    vdm_yuv2rgb_00_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB0[0] ;
    vdm_yuv2rgb_01_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB0[1] ;
    vdm_yuv2rgb_02_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB0[2] ;
    vdm_yuv2rgb_10_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB1[0]  ;
    vdm_yuv2rgb_11_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB1[1]  ;
    vdm_yuv2rgb_12_in_dc   = pstY2RCfg->s32InOffsetYUV2RGB1[2]  ;
    vdm_yuv2rgb_10_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB1[0] ;
    vdm_yuv2rgb_11_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB1[1] ;
    vdm_yuv2rgb_12_out_dc  = pstY2RCfg->s32OutOffsetYUV2RGB1[2] ;
    vdm_v0_yuv2rgb_clip_min = pstY2RCfg->u16ClipMinYUV2RGB_V0    ;
    vdm_v0_yuv2rgb_clip_max = pstY2RCfg->u16ClipMaxYUV2RGB_V0    ;
    vdm_v1_yuv2rgb_clip_min = pstY2RCfg->u16ClipMinYUV2RGB_V1    ;
    vdm_v1_yuv2rgb_clip_max = pstY2RCfg->u16ClipMaxYUV2RGB_V1    ;

    if(enLayer == VDP_LAYER_VID0)
    {
        VDP_HIHDR_SetVdm00Yuv2rgb(vdm_00_yuv2rgb);
        VDP_HIHDR_SetVdm01Yuv2rgb(vdm_01_yuv2rgb);
        VDP_HIHDR_SetVdm02Yuv2rgb(vdm_02_yuv2rgb);
        VDP_HIHDR_SetVdm03Yuv2rgb(vdm_03_yuv2rgb);
        VDP_HIHDR_SetVdm04Yuv2rgb(vdm_04_yuv2rgb);
        VDP_HIHDR_SetVdm05Yuv2rgb(vdm_05_yuv2rgb);
        VDP_HIHDR_SetVdm06Yuv2rgb(vdm_06_yuv2rgb);
        VDP_HIHDR_SetVdm07Yuv2rgb(vdm_07_yuv2rgb);
        VDP_HIHDR_SetVdm08Yuv2rgb(vdm_08_yuv2rgb);
        VDP_HIHDR_SetVdmYuv2rgb00InDc(vdm_yuv2rgb_00_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb01InDc(vdm_yuv2rgb_01_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb02InDc(vdm_yuv2rgb_02_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb00OutDc(vdm_yuv2rgb_00_out_dc);
        VDP_HIHDR_SetVdmYuv2rgb01OutDc(vdm_yuv2rgb_01_out_dc);
        VDP_HIHDR_SetVdmYuv2rgb02OutDc(vdm_yuv2rgb_02_out_dc);
        VDP_HIHDR_SetVdmV0Yuv2rgbscale2p( vdm_v0_yuv2rgbscale2p);
        VDP_HIHDR_SetVdmV0Yuv2rgbClipMin( vdm_v0_yuv2rgb_clip_min);
        VDP_HIHDR_SetVdmV0Yuv2rgbClipMax( vdm_v0_yuv2rgb_clip_max);
    }
    else if(enLayer == VDP_LAYER_VID1)
    {
        VDP_HIHDR_SetVdm10Yuv2rgb(vdm_10_yuv2rgb);
        VDP_HIHDR_SetVdm11Yuv2rgb(vdm_11_yuv2rgb);
        VDP_HIHDR_SetVdm12Yuv2rgb(vdm_12_yuv2rgb);
        VDP_HIHDR_SetVdm13Yuv2rgb(vdm_13_yuv2rgb);
        VDP_HIHDR_SetVdm14Yuv2rgb(vdm_14_yuv2rgb);
        VDP_HIHDR_SetVdm15Yuv2rgb(vdm_15_yuv2rgb);
        VDP_HIHDR_SetVdm16Yuv2rgb(vdm_16_yuv2rgb);
        VDP_HIHDR_SetVdm17Yuv2rgb(vdm_17_yuv2rgb);
        VDP_HIHDR_SetVdm18Yuv2rgb(vdm_18_yuv2rgb);
        VDP_HIHDR_SetVdmYuv2rgb10InDc(vdm_yuv2rgb_10_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb11InDc(vdm_yuv2rgb_11_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb12InDc(vdm_yuv2rgb_12_in_dc);
        VDP_HIHDR_SetVdmYuv2rgb10OutDc(vdm_yuv2rgb_10_out_dc);
        VDP_HIHDR_SetVdmYuv2rgb11OutDc(vdm_yuv2rgb_11_out_dc);
        VDP_HIHDR_SetVdmYuv2rgb12OutDc(vdm_yuv2rgb_12_out_dc);
        VDP_HIHDR_SetVdmV1Yuv2rgbscale2p( vdm_v1_yuv2rgbscale2p);
        VDP_HIHDR_SetVdmV1Yuv2rgbClipMin( vdm_v1_yuv2rgb_clip_min);
        VDP_HIHDR_SetVdmV1Yuv2rgbClipMax( vdm_v1_yuv2rgb_clip_max);
    }

    free(pstY2RCfg);
    #endif
}

HI_VOID VDP_DRV_SetRGB2YUV(HI_U32 enLayer, RGB2YUV_MODE_E Rgb2YuvMode, R2YCfg_t *pR2YCfg)
{
    #if 0
    R2YCfg_t * pstR2YCfg;

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

    pstR2YCfg = (R2YCfg_t *)malloc(sizeof(R2YCfg_t));

    if(Rgb2YuvMode == RGB2YUV_601)
    {
        pstR2YCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstR2YCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstR2YCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstR2YCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstR2YCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstR2YCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstR2YCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstR2YCfg->u16ScaleRGB2YUV                = 14      ;
        pstR2YCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstR2YCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstR2YCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstR2YCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstR2YCfg->u16ClipMinRGB2YUV              = 0       ;
        pstR2YCfg->u16ClipMaxRGB2YUV              = 1023    ;
    }
    else if(Rgb2YuvMode == RGB2YUV_709)
    {
        pstR2YCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstR2YCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstR2YCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstR2YCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstR2YCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstR2YCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstR2YCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstR2YCfg->u16ScaleRGB2YUV                = 14      ;
        pstR2YCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstR2YCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstR2YCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstR2YCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstR2YCfg->u16ClipMinRGB2YUV              = 0       ;
        pstR2YCfg->u16ClipMaxRGB2YUV              = 1023    ;
    }
    else if(Rgb2YuvMode == RGB2YUV_2020)
    {
        pstR2YCfg->s16M33RGB2YUV[0][0]            = 2984    ; //BT709
        pstR2YCfg->s16M33RGB2YUV[0][1]            = 10034   ;
        pstR2YCfg->s16M33RGB2YUV[0][2]            = 1013    ;
        pstR2YCfg->s16M33RGB2YUV[1][0]            = -1643   ;
        pstR2YCfg->s16M33RGB2YUV[1][1]            = -5531   ;
        pstR2YCfg->s16M33RGB2YUV[1][2]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][0]            = 7175    ;
        pstR2YCfg->s16M33RGB2YUV[2][1]            = -6518   ;
        pstR2YCfg->s16M33RGB2YUV[2][2]            = -659    ;
        pstR2YCfg->u16ScaleRGB2YUV                = 14      ;
        pstR2YCfg->s16InOffsetRGB2YUV[0]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[1]          = 0       ;
        pstR2YCfg->s16InOffsetRGB2YUV[2]          = 0       ;
        pstR2YCfg->s16OutOffsetRGB2YUV[0]         = 64      ;
        pstR2YCfg->s16OutOffsetRGB2YUV[1]         = 512     ;
        pstR2YCfg->s16OutOffsetRGB2YUV[2]         = 512     ;
        pstR2YCfg->u16ClipMinRGB2YUV              = 0       ;
        pstR2YCfg->u16ClipMaxRGB2YUV              = 1023    ;
    }
    else if(Rgb2YuvMode == RGB2YUV_CFG)
    {
        pstR2YCfg->s16M33RGB2YUV[0][0]            = pR2YCfg->s16M33RGB2YUV[0][0]    ; //BT709
        pstR2YCfg->s16M33RGB2YUV[0][1]            = pR2YCfg->s16M33RGB2YUV[0][1]    ;
        pstR2YCfg->s16M33RGB2YUV[0][2]            = pR2YCfg->s16M33RGB2YUV[0][2]    ;
        pstR2YCfg->s16M33RGB2YUV[1][0]            = pR2YCfg->s16M33RGB2YUV[1][0]    ;
        pstR2YCfg->s16M33RGB2YUV[1][1]            = pR2YCfg->s16M33RGB2YUV[1][1]    ;
        pstR2YCfg->s16M33RGB2YUV[1][2]            = pR2YCfg->s16M33RGB2YUV[1][2]    ;
        pstR2YCfg->s16M33RGB2YUV[2][0]            = pR2YCfg->s16M33RGB2YUV[2][0]    ;
        pstR2YCfg->s16M33RGB2YUV[2][1]            = pR2YCfg->s16M33RGB2YUV[2][1]    ;
        pstR2YCfg->s16M33RGB2YUV[2][2]            = pR2YCfg->s16M33RGB2YUV[2][2]    ;
        pstR2YCfg->u16ScaleRGB2YUV                = pR2YCfg->u16ScaleRGB2YUV        ;
        pstR2YCfg->s16InOffsetRGB2YUV[0]          = pR2YCfg->s16InOffsetRGB2YUV[0]  ;
        pstR2YCfg->s16InOffsetRGB2YUV[1]          = pR2YCfg->s16InOffsetRGB2YUV[1]  ;
        pstR2YCfg->s16InOffsetRGB2YUV[2]          = pR2YCfg->s16InOffsetRGB2YUV[2]  ;
        pstR2YCfg->s16OutOffsetRGB2YUV[0]         = pR2YCfg->s16OutOffsetRGB2YUV[0] ;
        pstR2YCfg->s16OutOffsetRGB2YUV[1]         = pR2YCfg->s16OutOffsetRGB2YUV[1] ;
        pstR2YCfg->s16OutOffsetRGB2YUV[2]         = pR2YCfg->s16OutOffsetRGB2YUV[2] ;
        pstR2YCfg->u16ClipMinRGB2YUV              = pR2YCfg->u16ClipMinRGB2YUV      ;
        pstR2YCfg->u16ClipMaxRGB2YUV              = pR2YCfg->u16ClipMaxRGB2YUV      ;
    }
    else
    {
        VDP_PRINT("Error! Rgb2YuvMode : No this Mode!!! \n");
    }

    vdm_00_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[0][0]     ;
    vdm_01_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[0][1]     ;
    vdm_02_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[0][2]     ;
    vdm_10_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[1][0]     ;
    vdm_11_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[1][1]     ;
    vdm_12_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[1][2]     ;
    vdm_20_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[2][0]     ;
    vdm_21_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[2][1]     ;
    vdm_22_rgb2yuv         = pstR2YCfg->s16M33RGB2YUV[2][2]     ;
    vdm_rgb2yuvscale2p     = pstR2YCfg->u16ScaleRGB2YUV         ;
    vdm_rgb2yuv_0_in_dc    = pstR2YCfg->s16InOffsetRGB2YUV[0]   ;
    vdm_rgb2yuv_1_in_dc    = pstR2YCfg->s16InOffsetRGB2YUV[1]   ;
    vdm_rgb2yuv_2_in_dc    = pstR2YCfg->s16InOffsetRGB2YUV[2]   ;
    vdm_rgb2yuv_0_out_dc   = pstR2YCfg->s16OutOffsetRGB2YUV[0]  ;
    vdm_rgb2yuv_1_out_dc   = pstR2YCfg->s16OutOffsetRGB2YUV[1]  ;
    vdm_rgb2yuv_2_out_dc   = pstR2YCfg->s16OutOffsetRGB2YUV[2]  ;
    vdm_rgb2yuv_clip_min   = pstR2YCfg->u16ClipMinRGB2YUV       ;
    vdm_rgb2yuv_clip_max   = pstR2YCfg->u16ClipMaxRGB2YUV       ;

    VDP_HIHDR_SetVdm00Rgb2yuv(vdm_00_rgb2yuv);
    VDP_HIHDR_SetVdm01Rgb2yuv(vdm_01_rgb2yuv);
    VDP_HIHDR_SetVdm02Rgb2yuv(vdm_02_rgb2yuv);
    VDP_HIHDR_SetVdm10Rgb2yuv(vdm_10_rgb2yuv);
    VDP_HIHDR_SetVdm11Rgb2yuv(vdm_11_rgb2yuv);
    VDP_HIHDR_SetVdm12Rgb2yuv(vdm_12_rgb2yuv);
    VDP_HIHDR_SetVdm20Rgb2yuv(vdm_20_rgb2yuv);
    VDP_HIHDR_SetVdm21Rgb2yuv(vdm_21_rgb2yuv);
    VDP_HIHDR_SetVdm22Rgb2yuv(vdm_22_rgb2yuv);
    VDP_HIHDR_SetVdmRgb2yuvscale2p(vdm_rgb2yuvscale2p);
    VDP_HIHDR_SetVdmRgb2yuv0InDc(vdm_rgb2yuv_0_in_dc);
    VDP_HIHDR_SetVdmRgb2yuv1InDc(vdm_rgb2yuv_1_in_dc);
    VDP_HIHDR_SetVdmRgb2yuv2InDc(vdm_rgb2yuv_2_in_dc);
    VDP_HIHDR_SetVdmRgb2yuv0OutDc(vdm_rgb2yuv_0_out_dc);
    VDP_HIHDR_SetVdmRgb2yuv1OutDc(vdm_rgb2yuv_1_out_dc);
    VDP_HIHDR_SetVdmRgb2yuv2OutDc(vdm_rgb2yuv_2_out_dc);
    VDP_HIHDR_SetVdmRgb2yuvClipUvMin(vdm_rgb2yuv_clip_min);
    VDP_HIHDR_SetVdmRgb2yuvClipUvMax(vdm_rgb2yuv_clip_max);

    free(pstR2YCfg);
    #endif
}

