/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_table_default.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/10/30
  Description   :

******************************************************************************/

#include "hi_drv_pq.h"
#include "pq_hal_table_default.h"

static PQ_PHY_REG_S sg_stPhyRegDefault[PHY_REG_MAX] =
{

    /*Addr         Lsb       Msb  SourceMode  OutputMode   Module     Value        Description*/

    /***********************************************DEI***********************************************/
    /*VPSS_DIECTRL*/
    {0x1000,        29,     29,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_out_sel_l
    {0x1000,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_out_sel_c
    {0x1000,        26,     27,     0,      0,      HI_PQ_MODULE_DEI,       1},     //die_l_mode
    {0x1000,        24,     25,     0,      0,      HI_PQ_MODULE_DEI,       1},     //die_c_mode
    {0x1000,        22,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_only
    {0x1000,        21,     21,     0,      0,      HI_PQ_MODULE_DEI,       0},     //ma_only
    {0x1000,        20,     20,     0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_smooth_en
    {0x1000,        19,     19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mchdir_l
    {0x1000,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mchdir_c
    {0x1000,        17,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_rst
    {0x1000,        16,     16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //stinfo_stop
    {0x1000,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //edge_smooth_ratio
    /*VPSS_DIELMA2*/
    {0x1004,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       8},     //chroma_mf_offset
    {0x1004,        8,      23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dei_st_rst_value
    {0x1004,        7,      7,      0,      0,      HI_PQ_MODULE_DEI,       1},     //rec_mode_en
    {0x1004,        6,      6,      0,      0,      HI_PQ_MODULE_DEI,       0},     //chroma_mf_max
    {0x1004,        5,      5,      0,      0,      HI_PQ_MODULE_DEI,       0},     //luma_mf_max
    {0x1004,        4,      4,      0,      0,      HI_PQ_MODULE_DEI,       1},     //motion_iir_en
    {0x1004,        2,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //luma_scesdf_max
    {0x1004,        1,      1,      0,      0,      HI_PQ_MODULE_DEI,       1},     //frame_motion_smooth_en
    {0x1004,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //recmode_frmfld_blend_mode
    /*VPSS_DIEINTEN*/
    {0x1008,        16,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //min_north_strength
    {0x1008,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //dir_ratio_north
    /*VPSS_DIESCALE*/
    {0x100c,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       2},     //range_scale
    /*VPSS_DIECHECK1*/
    {0x1010,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bc1_gain
    {0x1010,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //bc1_autodz_gain
    {0x1010,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       30},    //bc1_max_dz
    /*VPSS_DIECHECK2*/
    {0x1014,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bc2_gain
    {0x1014,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //bc2_autodz_gain
    {0x1014,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       30},    //bc2_max_dz
    /*VPSS_DIEDIR0_3*/
    /*VPSS_DIEDIR12_14*/
    {0x1024,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir14_scale
    {0x1024,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir13_scale
    {0x1024,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir12_scale
    /*VPSS_DIEDIR8_11*/
    {0x1020,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir11_scale
    {0x1020,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir10_scale
    {0x1020,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir9_scale
    {0x1020,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir8_scale
    /*VPSS_DIEDIR4_7*/
    {0x101c,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir7_scale
    {0x101c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir6_scale
    {0x101c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir5_scale
    {0x101c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir4_scale
    {0x1018,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir3_scale
    {0x1018,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir2_scale
    {0x1018,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir1_scale
    {0x1018,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir0_scale  /*VPSS_DIESTA*/
    {0x1028,        20,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //c_height_cnt
    {0x1028,        8,      19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //l_height_cnt
    {0x1028,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //cur_cstate
    {0x1028,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       0},     //cur_state
    /*VPSS_DIEINTPSCL0*/
    {0x102c,        28,     31,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_8
    {0x102c,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_7
    {0x102c,        20,     23,     0,      0,      HI_PQ_MODULE_DEI,       7},     //intp_scale_ratio_6
    {0x102c,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_5
    {0x102c,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_4
    {0x102c,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_3
    {0x102c,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       7},     //intp_scale_ratio_2
    {0x102c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       5},     //intp_scale_ratio_1
    /*VPSS_DIEINTPSCL1*/
    {0x1030,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_15
    {0x1030,        20,     23,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_14
    {0x1030,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_13
    {0x1030,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_12
    {0x1030,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_11
    {0x1030,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_10
    {0x1030,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_9
    /*VPSS_DIEDIRTHD*/
    {0x1034,        16,     31,     0,      0,      HI_PQ_MODULE_DEI,       16383}, //strength_thd
    {0x1034,        13,     13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //hor_edge_en
    {0x1034,        12,     12,     0,      0,      HI_PQ_MODULE_DEI,       1},     //edge_mode
    {0x1034,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dir_thd
    {0x1034,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       64},    //bc_gain
    /*VPSS_DIEJITMTN*/
    {0x1038,        12,     19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //fld_motion_coring
    {0x1038,        4,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //jitter_coring
    {0x1038,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //jitter_gain
    /*VPSS_DIEJITMTN*/
    {0x103c,        29,     29,     0,      0,      HI_PQ_MODULE_DEI,       0},     //long_motion_shf
    {0x103c,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //fld_motion_wnd_mode
    {0x103c,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //fld_motion_gain
    {0x103c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       -2},    //fld_motion_curve_slope
    {0x103c,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //fld_motion_thd_high
    {0x103c,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //fld_motion_thd_low
    /*VPSS_DIEMTNDIFFTHD0*/
    {0x1040,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_3
    {0x1040,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       208},   //motion_diff_thd_2
    {0x1040,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       144},   //motion_diff_thd_1
    {0x1040,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       16},    //motion_diff_thd_0
    /*VPSS_DIEMTNDIFFTHD1*/
    {0x1044,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //max_motion_iir_ratio
    {0x1044,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       32},    //min_motion_iir_ratio
    {0x1044,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_5
    {0x1044,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_4
    /*VPSS_DIEMTNIIRSLP*/
    /*VPSS_DIEMTNIIRRAT*/
    {0x104c,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_4
    {0x104c,       16,     22,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_3
    {0x104c,       8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_2
    {0x104c,       0,      6,      0,      0,      HI_PQ_MODULE_DEI,       48},    //motion_iir_curve_ratio_1
    {0x1048,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       32},    //motion_iir_curve_ratio_0
    {0x1048,       18,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_iir_curve_slope_3
    {0x1048,       12,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_iir_curve_slope_2
    {0x1048,       6,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //motion_iir_curve_slope_1
    {0x1048,       0,      5,      0,      0,      HI_PQ_MODULE_DEI,       1},     //motion_iir_curve_slope_0
    /*VPSS_DIEHISMODE*/
    {0x1050,       21,     21,     0,      0,      HI_PQ_MODULE_DEI,       0},     //his_motion_info_write_mode
    {0x1050,       20,     20,     0,      0,      HI_PQ_MODULE_DEI,       0},     //his_motion_write_mode
    {0x1050,       19,     19,     0,      0,      HI_PQ_MODULE_DEI,       1},     //his_motion_using_mode
    {0x1050,       18,     18,     0,      0,      HI_PQ_MODULE_DEI,       1},     //his_motion_en
    {0x1050,       17,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //pre_info_en
    {0x1050,       16,     16,     0,      0,      HI_PQ_MODULE_DEI,       1},     //ppre_info_en
    {0x1050,       12,     13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_frm_motion_step_1
    {0x1050,       8,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_frm_motion_step_0
    {0x1050,       4,      6,      0,      0,      HI_PQ_MODULE_DEI,       2},     //rec_mode_fld_motion_step_1
    {0x1050,       0,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //rec_mode_fld_motion_step_0
    /*VPSS_DIEMORFLT*/
    {0x1054,       26,     26,     0,      0,      HI_PQ_MODULE_DEI,       0},     //med_blend_en
    {0x1054,       24,     24,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mor_flt_en
    {0x1054,       8,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mor_flt_size
    {0x1054,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mor_flt_thd
    /*VPSS_DIECOMBCHK0*/
    {0x1058,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       160},   //comb_chk_upper_limit
    {0x1058,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       10},    //comb_chk_lower_limit
    {0x1058,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       15},    //comb_chk_min_vthd
    {0x1058,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //comb_chk_min_hthd
    /*VPSS_DIECOMBCHK1*/
    {0x105c,       16,     16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //comb_chk_en
    {0x105c,       8,      12,     0,      0,      HI_PQ_MODULE_DEI,       20},    //comb_chk_md_thd
    {0x105c,       0,      6,      0,      0,      HI_PQ_MODULE_DEI,       16},    //comb_chk_edge_thd
    /*VPSS_DIEFRMMTNSMTHTHD0*/
    {0x1060,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd3
    {0x1060,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd2
    {0x1060,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       72},    //frame_motion_smooth_thd1
    {0x1060,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_motion_smooth_thd0
    /*VPSS_DIEFRMMTNSMTHTHD1*/
    {0x1064,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio_max
    {0x1064,       16,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_ratio_min
    {0x1064,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd5
    {0x1064,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd4
    /*VPSS_DIEFRMMTNSMTHSLP*/
    {0x1068,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_ratio0
    {0x1068,       18,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope3
    {0x1068,       12,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope2
    {0x1068,       6,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope1
    {0x1068,       0,      5,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_motion_smooth_slope0
    /*VPSS_DIEFRMMTNSMTHRAT*/
    /*VPSS_DIEFRMFLDBLENDTHD0*/
    {0x1070,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_field_blend_thd3
    {0x1070,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_field_blend_thd2
    {0x1070,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       72},    //frame_field_blend_thd1
    {0x1070,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_field_blend_thd0
    /*VPSS_DIEFRMFLDBLENDTHD1*/
    {0x1074,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_field_blend_ratio_max
    {0x1074,       16,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_field_blend_ratio_min
    {0x1074,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_field_blend_thd5
    {0x1074,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_field_blend_thd4
    /*VPSS_DIEFRMFLDBLENDSLP*/
    {0x1078,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_field_blend_ratio0
    {0x1078,       18,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_field_blend_slope3
    {0x1078,       12,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_field_blend_slope2
    {0x1078,       6,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_field_blend_slope1
    {0x1078,       0,      5,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_field_blend_slope0
    /*VPSS_DIEFRMFLDBLENDRAT*/
    {0x107c,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_field_blend_ratio4
    {0x107c,       16,     22,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_field_blend_ratio3
    {0x107c,       8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_field_blend_ratio2
    {0x107c,       0,      6,      0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_field_blend_ratio1
    /*VPSS_DIEMTNADJ*/
    {0x1080,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_adjust_gain_chr
    {0x1080,       8,      13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_adjust_coring
    {0x1080,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_adjust_gain
    /*VPSS_DIEEDGENORM0*/
    {0x1084,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       341},   //edge_norm_1
    {0x1084,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_norm_0
    /*VPSS_DIEEDGENORM1*/
    {0x1088,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       195},   //edge_norm_3
    {0x1088,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       273},   //edge_norm_2
    /*VPSS_DIEEDGENORM2*/
    {0x108c,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_strength_k3
    {0x108c,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       124},   //edge_norm_5
    {0x108c,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       151},   //edge_norm_4
    /*VPSS_DIEEDGENORM3*/
    {0x1090,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       64},    //mc_strength_g3
    {0x1090,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       91},    //edge_norm_7
    {0x1090,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       105},   //edge_norm_6
    /*VPSS_DIEEDGENORM4*/
    {0x1094,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       32},    //inter_diff_thd0
    {0x1094,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       71},    //edge_norm_9
    {0x1094,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       80},    //edge_norm_8
    /*VPSS_DIEEDGENORM5*/
    {0x1098,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       64},    //inter_diff_thd1
    {0x1098,       12,     23,     0,      0,      HI_PQ_MODULE_DEI,       50},    //edge_norm_11
    {0x1098,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       59},    //edge_norm_10
    /*VPSS_DIEEDGEFORMC*/
    {0x109c,       20,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //inter_diff_thd2
    {0x109c,       10,     19,     0,      0,      HI_PQ_MODULE_DEI,       32},    //edge_scale
    {0x109c,       0,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_coring
    /*VPSS_DIEMCSTRENGTH0*/
    {0x10a0,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       16},    //mc_strength_g0
    {0x10a0,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_strength_k2
    {0x10a0,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       6},     //mc_strength_k1
    {0x10a0,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_strength_k0
    /*VPSS_DIEMCSTRENGTH1*/
    {0x10a4,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       16},    //mc_strength_maxg
    {0x10a4,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       16},    //mc_strength_ming
    {0x10a4,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //mc_strength_g2
    {0x10a4,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       16},    //mc_strength_g1
    /*VPSS_DIEFUSION0*/
    {0x10a8,       24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k_c_mcbld
    {0x10a8,       16,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_c_mcw
    {0x10a8,       8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k_y_mcbld
    {0x10a8,       0,      6,      0,      0,      HI_PQ_MODULE_DEI,       16},    //k_y_mcw
    /*VPSS_DIEFUSION1*/
    {0x10ac,       16,     27,     0,      0,      HI_PQ_MODULE_DEI,       1023},  //g0_mcw_adj
    {0x10ac,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_mcw_adj
    {0x10ac,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       64},    //x0_mcw_adj
    /*VPSS_DIEFUSION2*/
    {0x10b0,       24,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //k1_mcbld
    {0x10b0,       16,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //k0_mcbld
    {0x10b0,       8,      15,     0,      0,      HI_PQ_MODULE_DEI,       0},     //x0_mcbld
    {0x10b0,       0,      7,      0,      0,      HI_PQ_MODULE_DEI,       128},   //k1_mcw_adj
    /*VPSS_DIEFUSION3*/
    {0x10b4,       20,     20,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mc_lai_bldmode
    {0x10b4,       12,     16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //k_curw_mcbld
    {0x10b4,       0,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //g0_mcbld
    /*VPSS_DIEMAGBMTHD0*/
    {0x10b8,       16,     25,     0,      0,      HI_PQ_MODULE_DEI,       16},    //ma_gbm_thd0
    {0x10b8,       0,      9,      0,      0,      HI_PQ_MODULE_DEI,       48},    //ma_gbm_thd1
    /*VPSS_DIEMAGBMTHD1*/
    {0x10bc,       16,     25,     0,      0,      HI_PQ_MODULE_DEI,       80},    //ma_gbm_thd2
    {0x10bc,       0,      9,      0,      0,      HI_PQ_MODULE_DEI,       112},   //ma_gbm_thd3
    /*VPSS_DIEMCGBMCOEF0*/
    {0x10c0,       28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mtfilten_gmd
    {0x10c0,       20,     25,     0,      0,      HI_PQ_MODULE_DEI,       28},    //mtth3_gmd
    {0x10c0,       12,     17,     0,      0,      HI_PQ_MODULE_DEI,       20},    //mtth2_gmd
    {0x10c0,       4,      8,      0,      0,      HI_PQ_MODULE_DEI,       12},    //mtth1_gmd
    {0x10c0,       0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //mtth0_gmd
    /*VPSS_DIEMCGBMCOEF1*/
    {0x10c4,       12,     19,     0,      0,      HI_PQ_MODULE_DEI,       96},    //k_mag_gmd
    {0x10c4,       4,      10,     0,      0,      HI_PQ_MODULE_DEI,       22},    //k_difh_gmd
    {0x10c4,       0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_maxmag_gmd
    /*VPSS_DIEKMAG1*/
    {0x10c8,       24,     28,     0,      0,      HI_PQ_MODULE_DEI,       31},    //khoredge
    {0x10c8,       19,     23,     0,      0,      HI_PQ_MODULE_DEI,       2},     //kmagv_2
    {0x10c8,       14,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //kmagv_1
    {0x10c8,       7,      13,     0,      0,      HI_PQ_MODULE_DEI,       31},    //kmagh_2
    {0x10c8,       0,      6,      0,      0,      HI_PQ_MODULE_DEI,       31},    //kmagh_1
    /*VPSS_DIEKMAG2*/
    {0x10cc,       20,     22,     0,      0,      HI_PQ_MODULE_DEI,       4},     //scaler_framemotion
    {0x10cc,       12,     19,     0,      0,      HI_PQ_MODULE_DEI,       60},    //motion_limt_2
    {0x10cc,       4,      11,     0,      0,      HI_PQ_MODULE_DEI,       60},    //motion_limt_1
    {0x10cc,       3,      3,      0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_mag_en
    {0x10cc,       0,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //scaler_horedge


    /***********************************************LCDI***********************************************/
    /*VPSS_DIE_S3ADD*/
    {0x10d0,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_str_coring_c
    {0x10d0,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //dir_ratio_c
    /*VPSS_MCDI_RGDIFY*/
    {0x1108,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       3},     //k_rgdifycore
    {0x1108,        14,     23,     0,      0,      HI_PQ_MODULE_DEI,       1023},  //g_rgdifycore
    {0x1108,        10,     13,     0,      0,      HI_PQ_MODULE_DEI,       5},     //core_rgdify
    {0x1108,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       511},   //lmt_rgdify
    /*VPSS_MCDI_RGSAD*/
    {0x110c,        23,     25,     0,      0,      HI_PQ_MODULE_DEI,       1},     //coef_sadlpf
    {0x110c,        15,     21,     0,      0,      HI_PQ_MODULE_DEI,       15},    //kmv_rgsad
    {0x110c,        9,      14,     0,      0,      HI_PQ_MODULE_DEI,       63},    //k_tpdif_rgsad
    {0x110c,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       255},   //g_tpdif_rgsad
    /*VPSS_MCDI_RGMV*/
    {0x1110,        19,     26,     0,      0,      HI_PQ_MODULE_DEI,       0},     //thmag_rgmv
    {0x1110,        10,     18,     0,      0,      HI_PQ_MODULE_DEI,       128},   //th_saddif_rgmv
    {0x1110,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       256},   //th_0mvsad_rgmv
    /*VPSS_MCDI_RGMAG0*/
    {0x1114,        10,     13,     0,      0,      HI_PQ_MODULE_DEI,       3},     //core_mag_rg
    {0x1114,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       255},   //lmt_mag_rg
    /*VPSS_MCDI_RGMAG1*/
    {0x1118,        21,     25,     0,      0,      HI_PQ_MODULE_DEI,       2},     //core_mv_rgmvls
    {0x1118,        16,     20,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k_mv_rgmvls
    {0x1118,        9,      15,     0,      0,      HI_PQ_MODULE_DEI,       -64},   //core_mag_rgmvls
    {0x1118,        5,      8,      0,      0,      HI_PQ_MODULE_DEI,       12},    //k_mag_rgmvls
    {0x1118,        1,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //th_mvadj_rgmvls
    {0x1118,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       1},     //en_mvadj_rgmvls
    /*VPSS_MCDI_RGLS*/
    {0x111c,        15,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_sad_rgls
    {0x111c,        9,      14,     0,      0,      HI_PQ_MODULE_DEI,       40},    //th_mag_rgls
    {0x111c,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       8},     //th_sad_rgls
    {0x111c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_sadcore_rgmv
    /*VPSS_MCDI_SEL*/
    {0x1120,        8,      8,      0,      0,      HI_PQ_MODULE_DEI,       0},     //force_mven
    {0x1120,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //force_mvx
    /*VPSS_MCDI_DLT0*/
    {0x1124,        16,     18,     0,      0,      HI_PQ_MODULE_DEI,       6},     //th_blkmvx_mvdlt
    {0x1124,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       4},     //th_rgmvx_mvdlt
    {0x1124,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       8},     //th_ls_mvdlt
    {0x1124,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       1},     //th_vblkdist_mvdlt
    {0x1124,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //th_hblkdist_mvdlt
    /*VPSS_MCDI_DLT1*/
    {0x1128,        23,     25,     0,      0,      HI_PQ_MODULE_DEI,       2},     //k_sadcore_mvdlt
    {0x1128,        18,     22,     0,      0,      HI_PQ_MODULE_DEI,       12},    //th_mag_mvdlt
    {0x1128,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       16},    //g_mag_mvdlt
    {0x1128,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       96},    //thl_sad_mvdlt
    {0x1128,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //thh_sad_mvdlt
    /*VPSS_MCDI_RGMCW0*/
    {0x112c,        20,     24,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k_rglsw
    {0x112c,        14,     19,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k_simimvw
    {0x112c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       15},    //gh_core_simimv
    {0x112c,        5,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //gl_core_simimv
    {0x112c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_core_simimv
    /*VPSS_MCDI_RGMCW1*/
    {0x1130,        23,     27,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k_core_vsaddif
    {0x1130,        19,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_rgsadadj_mcw
    {0x1130,        10,     18,     0,      0,      HI_PQ_MODULE_DEI,       64},    //core_rgsadadj_mcw
    {0x1130,        4,      9,      0,      0,      HI_PQ_MODULE_DEI,       20},    //k_mvy_mcw
    {0x1130,        1,      3,      0,      0,      HI_PQ_MODULE_DEI,       3},     //core_mvy_mcw
    {0x1130,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       1},     //rgtb_en_mcw
    /*VPSS_MCDI_RGMCW2*/
    {0x1134,        19,     26,     0,      0,      HI_PQ_MODULE_DEI,       24},    //core_rgmag_mcw
    {0x1134,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mode_rgysad_mcw
    {0x1134,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       10},    //k_vsaddifw
    {0x1134,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       64},    //gh_core_vsad_dif
    {0x1134,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       5},     //gl_core_vsaddif
    /*VPSS_MCDI_RGMCW3*/
    {0x1138,        18,     25,     0,      0,      HI_PQ_MODULE_DEI,       64},    //g0_rgmag_mcw
    {0x1138,        9,      17,     0,      0,      HI_PQ_MODULE_DEI,       256},   //k0_rgmag_mcw
    {0x1138,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       64},    //x0_rgmag_mcw
    /*VPSS_MCDI_RGMCW4*/
    {0x113c,        17,     26,     0,      0,      HI_PQ_MODULE_DEI,       512},   //x0_rgsad_mcw
    {0x113c,        9,      16,     0,      0,      HI_PQ_MODULE_DEI,       96},    //core_rgsad_mcw
    {0x113c,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       320},   //k1_rgmag_mcw
    /*VPSS_MCDI_RGMCW5*/
    {0x1140,        17,     25,     0,      0,      HI_PQ_MODULE_DEI,       128},   //k1_rgsad_mcw
    {0x1140,        9,      16,     0,      0,      HI_PQ_MODULE_DEI,       255},   //g0_rgsad_mcw
    {0x1140,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       160},   //k0_rgsad_mcw
    /*VPSS_MCDI_RGMCW6*/
    {0x1144,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       24},    //k_rgsad_mcw
    {0x1144,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       112},   //x_rgsad_mcw
    {0x1144,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_smrg_mcw
    {0x1144,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       16},    //x0_smrg_mcw
    /*VPSS_MCDI_TPMCW0*/
    {0x1148,        23,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k1_tpmvdist_mcw
    {0x1148,        15,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //g0_tpmvdist_mcw
    {0x1148,        8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_tpmvdist_mcw
    {0x1148,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //x0_tpmvdist_mcw
    /*VPSS_MCDI_TPMCW1*/
    {0x114c,        11,     13,     0,      0,      HI_PQ_MODULE_DEI,       2},     //k_core_tpmvdist_mcw
    {0x114c,        8,      10,     0,      0,      HI_PQ_MODULE_DEI,       2},     //b_core_tpmvdist_mcw
    {0x114c,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_avgmvdist_mcw
    {0x114c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_minmvdist_mcw
    /*VPSS_MCDI_WNDMCW0*/
    {0x1150,        27,     30,     0,      0,      HI_PQ_MODULE_DEI,       15},    //k_tbdif_mcw
    {0x1150,        23,     26,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k0_max_mag_mcw
    {0x1150,        19,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k1_max_mag_mcw
    {0x1150,        15,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_max_dif_mcw
    {0x1150,        11,     14,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_max_core_mcw
    {0x1150,        5,      10,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k_difvcore_mcw
    {0x1150,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       18},    //k_difhcore_mcw
    /*VPSS_MCDI_WNDMCW1*/
    {0x1154,        21,     24,     0,      0,      HI_PQ_MODULE_DEI,       6},     //k1_mag_wnd_mcw
    {0x1154,        15,     20,     0,      0,      HI_PQ_MODULE_DEI,       24},    //g0_mag_wnd_mcw
    {0x1154,        11,     14,     0,      0,      HI_PQ_MODULE_DEI,       6},     //k0_mag_wnd_mcw
    {0x1154,        4,      10,     0,      0,      HI_PQ_MODULE_DEI,       32},    //x0_mag_wnd_mcw
    {0x1154,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       0},     //k_tbmag_mcw
    /*VPSS_MCDI_WNDMCW2*/
    {0x1158,        21,     28,     0,      0,      HI_PQ_MODULE_DEI,       16},    //g0_sad_wnd_mcw
    {0x1158,        16,     20,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k0_sad_wnd_mcw
    {0x1158,        9,      15,     0,      0,      HI_PQ_MODULE_DEI,       8},     //x0_sad_wnd_mcw
    {0x1158,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       288},   //g1_mag_wnd_mcw
    /*VPSS_MCDI_WNDMCW3*/
    {0x115c,        5,      13,     0,      0,      HI_PQ_MODULE_DEI,       288},   //g1_sad_wnd_mcw
    {0x115c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //k1_sad_wnd_mcw
    /*VPSS_MCDI_VERTWEIGHT0*/
    {0x1160,        24,     26,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_hvdif_dw
    {0x1160,        20,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_bhvdif_dw
    {0x1160,        12,     18,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k_bhvdif_dw
    {0x1160,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       5},     //core_bhvdif_dw
    {0x1160,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       15},    //gain_lpf_dw
    {0x1160,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       12},    //k_max_hvdif_dw
    /*VPSS_MCDI_VERTWEIGHT1*/
    {0x1164,        20,     25,     0,      0,      HI_PQ_MODULE_DEI,       56},    //b_mv_dw
    {0x1164,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       -2},    //core_mv_dw
    {0x1164,        8,      12,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k_difv_dw
    {0x1164,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //core_hvdif_dw
    /*VPSS_MCDI_VERTWEIGHT2*/
    {0x1168,        25,     30,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k1_hvdif_dw
    {0x1168,        16,     24,     0,      0,      HI_PQ_MODULE_DEI,       128},   //g0_hvdif_dw
    {0x1168,        9,      12,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k0_hvdif_dw
    {0x1168,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       256},   //x0_hvdif_dw
    /*VPSS_MCDI_VERTWEIGHT3*/
    {0x116c,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k1_mv_dw
    {0x116c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       32},    //g0_mv_dw
    {0x116c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k0_mv_dw
    {0x116c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //x0_mv_dw
    /*VPSS_MCDI_VERTWEIGHT4*/
    {0x1170,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k1_mt_dw
    {0x1170,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       64},    //g0_mt_dw
    {0x1170,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k0_mt_dw
    {0x1170,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       32},    //x0_mt_dw
    /*VPSS_MCDI_VERTWEIGHT5*/
    {0x1174,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_mt_dw
    {0x1174,        12,     16,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k1_mv_mt
    {0x1174,        8,      9,      0,      0,      HI_PQ_MODULE_DEI,       1},     //x0_mv_mt
    {0x1174,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       31},    //g0_mv_mt
    /*VPSS_MCDI_MC0*/
    {0x1178,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mclpf_mode
    {0x1178,        20,     26,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_pxlmag_mcw
    {0x1178,        16,     18,     0,      0,      HI_PQ_MODULE_DEI,       2},     //x_pxlmag_mcw
    {0x1178,        15,     15,     0,      0,      HI_PQ_MODULE_DEI,       0},     //rs_pxlmag_mcw
    {0x1178,        10,     14,     0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_mclpfh
    {0x1178,        5,      9,      0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_dn_mclpfv
    {0x1178,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_up_mclpfv
    /*VPSS_MCDI_MC1*/
    {0x117c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       0},     //g_pxlmag_mcw
    /*VPSS_MCDI_MC2*/
    {0x1180,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       15},    //k_c_vertw
    {0x1180,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_y_vertw
    /*VPSS_MCDI_MC3*/
    {0x1184,        25,     29,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_fstmt_mc
    {0x1184,        20,     24,     0,      0,      HI_PQ_MODULE_DEI,       16},    //x_fstmt_mc
    {0x1184,        14,     19,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k1_mv_mc
    {0x1184,        11,     13,     0,      0,      HI_PQ_MODULE_DEI,       2},     //x0_mv_mc
    {0x1184,        8,      10,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bdv_mcpos
    {0x1184,        5,      7,      0,      0,      HI_PQ_MODULE_DEI,       4},     //bdh_mcpos
    {0x1184,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_delta
    /*VPSS_MCDI_MC4*/
    {0x1188,        26,     30,     0,      0,      HI_PQ_MODULE_DEI,       31},    //k_hfcore_mc
    {0x1188,        21,     25,     0,      0,      HI_PQ_MODULE_DEI,       0},     //x_hfcore_mc
    {0x1188,        15,     20,     0,      0,      HI_PQ_MODULE_DEI,       12},    //g_slmt_mc
    {0x1188,        10,     14,     0,      0,      HI_PQ_MODULE_DEI,       31},    //k_slmt_mc
    {0x1188,        5,      9,      0,      0,      HI_PQ_MODULE_DEI,       8},     //x_slmt_mc
    {0x1188,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       31},    //g_fstmt_mc
    /*VPSS_MCDI_MC5*/
    {0x118c,        18,     29,     0,      0,      HI_PQ_MODULE_DEI,       0},     //r0_mc
    {0x118c,        6,      17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //c0_mc
    {0x118c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       63},    //g_hfcore_mc
    /*VPSS_MCDI_MC6*/
    {0x1190,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //mcmvrange
    {0x1190,        12,     23,     0,      0,      HI_PQ_MODULE_DEI,       4095},  //r1_mc
    {0x1190,        0,      11,     0,      0,      HI_PQ_MODULE_DEI,       4095},  //c1_mc
    /*VPSS_MCDI_MC7*/
    {0x1194,        6,      12,     0,      0,      HI_PQ_MODULE_DEI,       48},   //k_frcount_mc
    {0x1194,        1,      5,      0,      0,      HI_PQ_MODULE_DEI,       8},     //x_frcount_mc
    {0x1194,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //scenechange_mc
    /*VPSS_MCDI_LCDINEW0*/
    {0x1198,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mcendc
    {0x1198,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mcendr
    {0x1198,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mcstartc
    {0x1198,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mcstartr
    /*VPSS_MCDI_LCDINEW1*/
    {0x119c,        18,     23,     0,      0,      HI_PQ_MODULE_DEI,       2},     //movegain
    {0x119c,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       4},     //movecorig
    {0x119c,        6,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //movethdl
    {0x119c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       12},    //movethdh
    /*VPSS_MCDI_NUMT*/
    {0x11a0,        15,     15,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mc_numt_blden
    {0x11a0,        7,      14,     0,      0,      HI_PQ_MODULE_DEI,       32},    //numt_gain
    {0x11a0,        1,      6,      0,      0,      HI_PQ_MODULE_DEI,       0},     //numt_coring
    {0x11a0,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //numt_lpf_en
    /*VPSS_MCDI_S3ADD0*/
    {0x11a4,        21,     26,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k1_hw
    {0x11a4,        15,     20,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k0_hw
    {0x11a4,        9,      14,     0,      0,      HI_PQ_MODULE_DEI,       15},    //core_hfvline
    {0x11a4,        6,      8,      0,      0,      HI_PQ_MODULE_DEI,       2},     //k1_hfvline
    {0x11a4,        3,      5,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k0_hfvline
    {0x11a4,        0,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //core_rglsw
    /*VPSS_MCDI_S3ADD1*/
    {0x11a8,        20,     28,     0,      0,      HI_PQ_MODULE_DEI,       208},   //g_difcore_mcw
    {0x11a8,        19,     19,     0,      0,      HI_PQ_MODULE_DEI,       1},     //subpix_mc_en
    {0x11a8,        15,     18,     0,      0,      HI_PQ_MODULE_DEI,       3},     //core1_hw
    {0x11a8,        11,     14,     0,      0,      HI_PQ_MODULE_DEI,       4},     //k_core0_hw
    {0x11a8,        7,      10,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_core0_hw
    {0x11a8,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       80},    //g_hw
    /*VPSS_MCDI_S3ADD2*/
    {0x11ac,        20,     27,     0,      0,      HI_PQ_MODULE_DEI,       4},     //g0_sadr_wnd_mcw
    {0x11ac,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       4},     //k0_sadr_wnd_mcw
    {0x11ac,        9,      15,     0,      0,      HI_PQ_MODULE_DEI,       8},     //x0_sadr_wnd_mcw
    {0x11ac,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       10},    //rp_k1_sad_wnd_mcw
    {0x11ac,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       10},    //rp_k1_mag_wnd_mcw
    /*VPSS_MCDI_S3ADD3*/
    {0x11b0,        21,     29,     0,      0,      HI_PQ_MODULE_DEI,       128},   //th_cur_blksad
    {0x11b0,        17,     20,     0,      0,      HI_PQ_MODULE_DEI,       12},    //k_mcdifv_mcw
    {0x11b0,        13,     16,     0,      0,      HI_PQ_MODULE_DEI,       6},     //k_p1cfdifh_mcw
    {0x11b0,        4,      12,     0,      0,      HI_PQ_MODULE_DEI,       288},   //g1_sadr_wnd_mcw
    {0x11b0,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k1_sadr_wnd_mcw
    /*VPSS_MCDI_S3ADD4*/
    {0x11b4,        18,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //th_cur_blkmotion
    {0x11b4,        9,      17,     0,      0,      HI_PQ_MODULE_DEI,       128},   //thl_neigh_blksad
    {0x11b4,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       256},   //thh_neigh_blksad
    /*VPSS_MCDI_S3ADD5*/
    {0x11b8,        20,     23,     0,      0,      HI_PQ_MODULE_DEI,       5},     //rp_difmvxth_rgmv
    {0x11b8,        17,     19,     0,      0,      HI_PQ_MODULE_DEI,       3},     //rp_mvxth_rgmv
    {0x11b8,        14,     16,     0,      0,      HI_PQ_MODULE_DEI,       2},     //rpcounterth
    {0x11b8,        11,     13,     0,      0,      HI_PQ_MODULE_DEI,       4},     //k_rpcounter
    {0x11b8,        10,     10,     0,      0,      HI_PQ_MODULE_DEI,       1},     //blkmv_update_en
    {0x11b8,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       512},   //th_rgmv_mag
    /*VPSS_MCDI_S3ADD6*/
    {0x11bc,        17,     26,     0,      0,      HI_PQ_MODULE_DEI,       600},   //rp_magth_rgmv
    {0x11bc,        8,      16,     0,      0,      HI_PQ_MODULE_DEI,       125},   //rp_sadth_rgmv
    {0x11bc,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       32},    //rp_difsadth_rgmv
    /*VPSS_MCDI_S3ADD7*/
    {0x11c0,        20,     20,     0,      0,      HI_PQ_MODULE_DEI,       0},     //difvt_mode
    {0x11c0,        19,     19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //rp_en
    {0x11c0,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       1},     //submv_sadchk_en
    {0x11c0,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       80},    //k1_tpdif_rgsad
    {0x11c0,        3,      11,     0,      0,      HI_PQ_MODULE_DEI,       428},   //rp_difsadth_tb
    {0x11c0,        0,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //rp_difmvxth_sp
    /*VPSS_MCDI_DEMO*/
    {0x11cc,        5,      16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_border
    {0x11cc,        3,      4,      0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_mode_r
    {0x11cc,        1,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_mode_l
    {0x11cc,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_en



    /***********************************************FMD***********************************************/
    /*FMD_CTRL*/
    {0x1000,        20,     20,     0,      0,      HI_PQ_MODULE_FMD,       0},     //edge_smooth_en
    {0x1000,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //edge_smooth_ratio
    {0x10dc,        0,      2,      0,      0,      HI_PQ_MODULE_FMD,       6},     //
    /*FMD_CTRL_ReadOnly*/
    {0x1000,        19,     19,     0,      0,      HI_PQ_MODULE_FMD,       0},     //mchdir_l
    {0x1000,        18,     18,     0,      0,      HI_PQ_MODULE_FMD,       0},     //mchdir_c
    /*VPSS_PDPCCMOV*/
    {0x10d8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       20},    //mov_coring_norm
    {0x10d8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       50},    //mov_coring_tkr
    {0x10d8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       20},    //mov_coring_blk
    /*VPSS_PDPHISTTHD*/
    {0x10d4,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       32},    //hist_thd3
    {0x10d4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       32},    //hist_thd2
    {0x10d4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       16},    //hist_thd1
    {0x10d4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       8},     //hist_thd0
    /*VPSS_PDCTRL*/
    {0x10dc,        19,     19,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_mode
    {0x10e0,        20,     27,     0,      0,      HI_PQ_MODULE_FMD,       30},    //diff_movblk_thd
    /*VPSS_PDUMTHD*/
    {0x10e4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       64},    //um_thd2
    {0x10e4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //um_thd1
    {0x10e4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       8},     //um_thd0
    /*VPSS_PDPCCCORING*/
    {0x10e8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       16},    //coring_blk
    {0x10e8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       16},    //coring_norm
    {0x10e8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       90},    //coring_tkr
    /*VPSS_PDPCCHVTHD*/
    {0x10ec,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       16},    //pcc_hthd
    {0x10f0,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       128},   //pcc_vthd3
    {0x10f0,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       64},    //pcc_vthd2
    {0x10f0,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //pcc_vthd1
    {0x10f0,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       16},    //pcc_vthd0
    /*VPSS_PDITDIFFVTHD*/
    {0x10f4,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       32},    //itdiff_vthd3
    {0x10f4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       16},    //itdiff_vthd2
    {0x10f4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       8},     //itdiff_vthd1
    {0x10f4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       4},     //itdiff_vthd0
    /*VPSS_PDLASITHD*/
    {0x10f8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       32},    //lasi_mov_thd
    {0x10f8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       15},    //lasi_edge_thd
    {0x10f8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       20},    //lasi_coring_thd
    /*PDLASIMODE0COEF*/
    {0x10fc,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_coring
    {0x10fc,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,      32},     //lasi_txt_alpha
    {0x1100,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd3
    {0x1100,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd2
    {0x1100,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd1
    {0x1100,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd0
    /*PDLASIMODE0COEF*/
    {0x1104,        12,     23,     0,      0,      HI_PQ_MODULE_FMD,       0},     //region1_y_stt
    {0x1104,        0,      11,     0,      0,      HI_PQ_MODULE_FMD,       0},     //region1_y_end

    /***********************************************DB SD*********************************************/
    /*VPSS_SNR_CTRL*/
    {0x2100,       16,     18,     1,      0,      HI_PQ_MODULE_DB,        6},     //dbm_out_mode
    {0x2100,       13,     13,     1,      0,      HI_PQ_MODULE_DB,        1},     //det_hy_en
    {0x2100,       3,      3,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_en
    {0x2100,       0,      0,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_en
    /*VPSS_DB_DIR*/
    {0x2108,       8,      12,     1,      0,      HI_PQ_MODULE_DB,        2},     //db_ctrst_thresh
    {0x2108,       0,      4,      1,      0,      HI_PQ_MODULE_DB,        24},    //db_grad_sub_ratio
    /*VPSS_DB_BLK*/
    {0x210c,       0,      6,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_h_blk_size
    /*VPSS_DB_RATIO*/
    {0x2110,       20,     21,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_txt_win_size
    {0x2110,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_global_db_strenth_lum
    {0x2110,       8,      9,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_filter_sel
    {0x2110,       0,      1,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_scale_ratio
    /*VPSS_DB_LHHF*/
    {0x2114,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_hf_var_gain2
    {0x2114,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_hf_var_gain1
    {0x2114,       16,     22,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_var_core
    {0x2114,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain2
    {0x2114,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain1
    {0x2114,       0,      6,      1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_core
    /*VPSS_DB_LVHF*/
    {0x2118,       21,     23,     1,      0,      HI_PQ_MODULE_DB,        7},     //db_lum_hor_bord_adj_gain
    {0x2118,       16,     20,     1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_adj_gain
    /*VPSS_DB_CTRS*/
    {0x211c,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        4},     //db_max_lum_hor_db_dist
    {0x211c,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_ctrst_adj_gain2
    {0x211c,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_gain1
    {0x211c,       5,      6,      1,      0,      HI_PQ_MODULE_DB,        2},     //db_dir_smooth_mode
    {0x211c,       0,      4,      1,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_core
    /*VPSS_DB_LUT0*/
    {0x2120,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p7
    {0x2120,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p6
    {0x2120,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p5
    {0x2120,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p4
    {0x2120,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p3
    {0x2120,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p2
    {0x2120,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p1
    {0x2120,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p0
    /*VPSS_DB_LUT1*/
    {0x2124,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p15
    {0x2124,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p14
    {0x2124,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        2},     //db_lum_hor_delta_lut_p13
    {0x2124,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p12
    {0x2124,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        6},     //db_lum_hor_delta_lut_p11
    {0x2124,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p10
    {0x2124,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p9
    {0x2124,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p8
    /*VPSS_DB_LUT2*/
    {0x2128,       27,     29,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p9
    {0x2128,       24,     26,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p8
    {0x2128,       21,     23,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p7
    {0x2128,       18,     20,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p6
    {0x2128,       15,     17,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p5
    {0x2128,       12,     14,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p4
    {0x2128,       9,      11,     1,      0,      HI_PQ_MODULE_DB,        3},     //db_lum_h_str_fade_lut_p3
    {0x2128,       6,      8,      1,      0,      HI_PQ_MODULE_DB,        3},     //db_lum_h_str_fade_lut_p2
    {0x2128,       3,      5,      1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_h_str_fade_lut_p1
    {0x2128,       0,      2,      1,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_h_str_fade_lut_p0
    /*VPSS_DB_LUT3*/
    {0x212c,       3,      5,      1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p11
    {0x212c,       0,      2,      1,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p10
    /*VPSS_DB_LUT4*/
    {0x2130,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p7
    {0x2130,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p6
    {0x2130,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p5
    {0x2130,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p4
    {0x2130,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_gain_lut_p3
    {0x2130,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        3},     //db_dir_str_gain_lut_p2
    {0x2130,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        5},     //db_dir_str_gain_lut_p1
    {0x2130,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_gain_lut_p0
    /*VPSS_DB_LUT5*/
    {0x2134,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        6},     //db_dir_str_lut_p7
    {0x2134,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p6
    {0x2134,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p5
    {0x2134,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p4
    {0x2134,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p3
    {0x2134,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p2
    {0x2134,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p1
    {0x2134,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p0
    /*VPSS_DB_LUT6*/
    {0x2138,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p15
    {0x2138,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p14
    {0x2138,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p13
    {0x2138,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p12
    {0x2138,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p11
    {0x2138,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p10
    {0x2138,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p9
    {0x2138,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p8
    /*VPSS_DB_ADPT*/
    {0x213c,        12,     28,     1,      0,      HI_PQ_MODULE_DB,        15},    //db_adpt_delta_scl
    {0x213c,        2,      6,      1,      0,      HI_PQ_MODULE_DB,        3},     //db_adpt_delta_adj0
    {0x213c,        0,      1,      1,      0,      HI_PQ_MODULE_DB,        0},     //db_adpt_flt_mode
    /*VPSS_DBD_THDEDGE*/
    {0x2150,       0,      5,      1,      0,      HI_PQ_MODULE_DB,        32},    //dbd_hy_thd_edge
    /*VPSS_DBD_THDTXT*/
    {0x2154,       0,      5,      1,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_thd_txt
    /*VPSS_DBD_LUTWGT0*/
    {0x2158,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt7
    {0x2158,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        10},    //dbd_det_lut_wgt6
    {0x2158,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        7},     //dbd_det_lut_wgt5
    {0x2158,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        5},     //dbd_det_lut_wgt4
    {0x2158,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        2},     //dbd_det_lut_wgt3
    {0x2158,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        1},     //dbd_det_lut_wgt2
    {0x2158,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt1
    {0x2158,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt0
    /*VPSS_DBD_LUTWGT1*/
    {0x215c,       28,     31,     1,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt15
    {0x215c,       24,     27,     1,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt14
    {0x215c,       20,     23,     1,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt13
    {0x215c,       16,     19,     1,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt12
    {0x215c,       12,     15,     1,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt11
    {0x215c,       8,      11,     1,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt10
    {0x215c,       4,      7,      1,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt9
    {0x215c,       0,      3,      1,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt8
    /*VPSS_DBD_RTNBDTXT*/
    {0x2160,       0,      4,      1,      0,      HI_PQ_MODULE_DB,        20},    //dbd_hy_rtn_bd_txt
    /*VPSS_DBD_TSTBLKNUM*/
    {0x2164,       0,      9,      1,      0,      HI_PQ_MODULE_DB,        90},    //dbd_hy_tst_blk_num
    /*VPSS_DBD_HYRDX8BINLUT0*/
    {0x2168,       12,     22,     1,      0,      HI_PQ_MODULE_DB,        48},    //dbd_hy_rdx8bin_lut1
    {0x2168,       0,      10,     1,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_rdx8bin_lut0
    /*VPSS_DBD_HYRDX8BINLUT1*/
    {0x216c,       12,     22,     1,      0,      HI_PQ_MODULE_DB,        112},   //dbd_hy_rdx8bin_lut3
    {0x216c,       0,      10,     1,      0,      HI_PQ_MODULE_DB,        80},    //dbd_hy_rdx8bin_lut2
    /*VPSS_DBD_HYRDX8BINLUT2*/
    {0x2170,       12,     22,     1,      0,      HI_PQ_MODULE_DB,        176},   //dbd_hy_rdx8bin_lut5
    {0x2170,       0,      10,     1,      0,      HI_PQ_MODULE_DB,        144},   //dbd_hy_rdx8bin_lut4
    /*VPSS_DBD_HYRDX8BINLUT3*/
    {0x2174,       0,      10,     1,      0,      HI_PQ_MODULE_DB,        208},   //dbd_hy_rdx8bin_lut6
    /*VPSS_DBD_BLKSIZE*/
    {0x2178,       8,      14,     1,      0,      HI_PQ_MODULE_DB,        64},    //dbd_hy_max_blk_size
    {0x2178,       0,      5,      1,      0,      HI_PQ_MODULE_DB,        4},     //dbd_min_blk_size
    /*VPSS_DBD_FLAT*/
    {0x217c,       0,      4,      1,      0,      HI_PQ_MODULE_DB,        16},    //dbd_thr_flat

    /***********************************************DB FHD*********************************************/
    /*VPSS_SNR_CTRL*/
    {0x2100,       16,     18,     2,      0,      HI_PQ_MODULE_DB,        6},     //dbm_out_mode
    {0x2100,       13,     13,     2,      0,      HI_PQ_MODULE_DB,        1},     //det_hy_en
    {0x2100,       3,      3,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_en
    {0x2100,       0,      0,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_en
    /*VPSS_DB_DIR*/
    {0x2108,       8,      12,     2,      0,      HI_PQ_MODULE_DB,        2},     //db_ctrst_thresh
    {0x2108,       0,      4,      2,      0,      HI_PQ_MODULE_DB,        24},    //db_grad_sub_ratio
    /*VPSS_DB_BLK*/
    {0x210c,       0,      6,      2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_h_blk_size
    /*VPSS_DB_RATIO*/
    {0x2110,       20,     21,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_txt_win_size
    {0x2110,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_global_db_strenth_lum
    {0x2110,       8,      9,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_filter_sel
    {0x2110,       0,      1,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_scale_ratio
    /*VPSS_DB_LHHF*/
    {0x2114,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_hf_var_gain2
    {0x2114,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_hf_var_gain1
    {0x2114,       16,     22,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_var_core
    {0x2114,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain2
    {0x2114,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain1
    {0x2114,       0,      6,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_core
    /*VPSS_DB_LVHF*/
    {0x2118,       21,     23,     2,      0,      HI_PQ_MODULE_DB,        7},     //db_lum_hor_bord_adj_gain
    {0x2118,       16,     20,     2,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_adj_gain
    /*VPSS_DB_CTRS*/
    {0x211c,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        4},     //db_max_lum_hor_db_dist
    {0x211c,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_ctrst_adj_gain2
    {0x211c,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_gain1
    {0x211c,       5,      6,      2,      0,      HI_PQ_MODULE_DB,        2},     //db_dir_smooth_mode
    {0x211c,       0,      4,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_core
    /*VPSS_DB_LUT0*/
    {0x2120,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p7
    {0x2120,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p6
    {0x2120,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p5
    {0x2120,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p4
    {0x2120,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p3
    {0x2120,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p2
    {0x2120,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        6},     //db_lum_hor_delta_lut_p1
    {0x2120,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p0
    /*VPSS_DB_LUT1*/
    {0x2124,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p15
    {0x2124,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p14
    {0x2124,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        2},     //db_lum_hor_delta_lut_p13
    {0x2124,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        3},     //db_lum_hor_delta_lut_p12
    {0x2124,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p11
    {0x2124,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        5},     //db_lum_hor_delta_lut_p10
    {0x2124,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        6},     //db_lum_hor_delta_lut_p9
    {0x2124,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        7},     //db_lum_hor_delta_lut_p8
    /*VPSS_DB_LUT2*/
    {0x2128,       27,     29,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p9
    {0x2128,       24,     26,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p8
    {0x2128,       21,     23,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p7
    {0x2128,       18,     20,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p6
    {0x2128,       15,     17,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p5
    {0x2128,       12,     14,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p4
    {0x2128,       9,      11,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p3
    {0x2128,       6,      8,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p2
    {0x2128,       3,      5,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_h_str_fade_lut_p1
    {0x2128,       0,      2,      2,      0,      HI_PQ_MODULE_DB,        2},     //db_lum_h_str_fade_lut_p0
    /*VPSS_DB_LUT3*/
    {0x212c,       3,      5,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p11
    {0x212c,       0,      2,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p10
    /*VPSS_DB_LUT4*/
    {0x2130,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p7
    {0x2130,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p6
    {0x2130,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p5
    {0x2130,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p4
    {0x2130,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_gain_lut_p3
    {0x2130,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        3},     //db_dir_str_gain_lut_p2
    {0x2130,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        5},     //db_dir_str_gain_lut_p1
    {0x2130,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_gain_lut_p0
    /*VPSS_DB_LUT5*/
    {0x2134,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        6},     //db_dir_str_lut_p7
    {0x2134,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p6
    {0x2134,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p5
    {0x2134,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p4
    {0x2134,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p3
    {0x2134,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p2
    {0x2134,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p1
    {0x2134,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p0
    /*VPSS_DB_LUT6*/
    {0x2138,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p15
    {0x2138,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p14
    {0x2138,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p13
    {0x2138,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p12
    {0x2138,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p11
    {0x2138,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p10
    {0x2138,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p9
    {0x2138,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p8
    /*VPSS_DB_ADPT*/
    {0x213c,       12,     28,     2,      0,      HI_PQ_MODULE_DB,        15},    //db_adpt_delta_scl
    {0x213c,       2,      6,      2,      0,      HI_PQ_MODULE_DB,        3},     //db_adpt_delta_adj0
    {0x213c,       0,      1,      2,      0,      HI_PQ_MODULE_DB,        0},     //db_adpt_flt_mode
    /*VPSS_DBD_THDEDGE*/
    {0x2150,       0,      5,      2,      0,      HI_PQ_MODULE_DB,        32},    //dbd_hy_thd_edge
    /*VPSS_DBD_THDTXT*/
    {0x2154,       0,      5,      2,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_thd_txt
    /*VPSS_DBD_LUTWGT0*/
    {0x2158,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt7
    {0x2158,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        10},    //dbd_det_lut_wgt6
    {0x2158,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        7},     //dbd_det_lut_wgt5
    {0x2158,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        5},     //dbd_det_lut_wgt4
    {0x2158,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        2},     //dbd_det_lut_wgt3
    {0x2158,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        1},     //dbd_det_lut_wgt2
    {0x2158,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt1
    {0x2158,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt0
    /*VPSS_DBD_LUTWGT1*/
    {0x215c,       28,     31,     2,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt15
    {0x215c,       24,     27,     2,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt14
    {0x215c,       20,     23,     2,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt13
    {0x215c,       16,     19,     2,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt12
    {0x215c,       12,     15,     2,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt11
    {0x215c,       8,      11,     2,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt10
    {0x215c,       4,      7,      2,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt9
    {0x215c,       0,      3,      2,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt8
    /*VPSS_DBD_RTNBDTXT*/
    {0x2160,       0,      4,      2,      0,      HI_PQ_MODULE_DB,        20},    //dbd_hy_rtn_bd_txt
    /*VPSS_DBD_TSTBLKNUM*/
    {0x2164,       0,      9,      2,      0,      HI_PQ_MODULE_DB,        90},    //dbd_hy_tst_blk_num
    /*VPSS_DBD_HYRDX8BINLUT0*/
    {0x2168,       12,     22,     2,      0,      HI_PQ_MODULE_DB,        48},    //dbd_hy_rdx8bin_lut1
    {0x2168,       0,      10,     2,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_rdx8bin_lut0
    /*VPSS_DBD_HYRDX8BINLUT1*/
    {0x216c,       12,     22,     2,      0,      HI_PQ_MODULE_DB,        112},   //dbd_hy_rdx8bin_lut3
    {0x216c,       0,      10,     2,      0,      HI_PQ_MODULE_DB,        80},    //dbd_hy_rdx8bin_lut2
    /*VPSS_DBD_HYRDX8BINLUT2*/
    {0x2170,       12,     22,     2,      0,      HI_PQ_MODULE_DB,        176},   //dbd_hy_rdx8bin_lut5
    {0x2170,       0,      10,     2,      0,      HI_PQ_MODULE_DB,        144},   //dbd_hy_rdx8bin_lut4
    /*VPSS_DBD_HYRDX8BINLUT3*/
    {0x2174,       0,      10,     2,      0,      HI_PQ_MODULE_DB,        208},   //dbd_hy_rdx8bin_lut6
    /*VPSS_DBD_BLKSIZE*/
    {0x2178,       8,      14,     2,      0,      HI_PQ_MODULE_DB,        64},    //dbd_hy_max_blk_size
    {0x2178,       0,      5,      2,      0,      HI_PQ_MODULE_DB,        4},     //dbd_min_blk_size
    /*VPSS_DBD_FLAT*/
    {0x217c,       0,      4,      2,      0,      HI_PQ_MODULE_DB,        16},    //dbd_thr_flat


    /*********************************************DM SD/FHD the same **************************************/
    /*VPSS_SNR_CTRL*/
    {0x2100,       1,      1,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_en
    /*VPSS_DM_DIR*/
    {0x2190,       16,     17,     0,      0,      HI_PQ_MODULE_DM,        2},     //dm_opp_ang_ctrst_div
    {0x2190,       8,      15,     0,      0,      HI_PQ_MODULE_DM,        18},    //dm_opp_ang_ctrst_t
    {0x2190,       6,      7,      0,      0,      HI_PQ_MODULE_DM,        2},     //dm_ctrst_thresh
    {0x2190,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        24},    //dm_grad_sub_ratio
    /*VPSS_DM_EDGE*/
    {0x2194,       22,     25,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_global_str
    {0x2194,       1,      2,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_init_val_step
    {0x2194,       0,      0,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_set
    /*VPSS_DM_LUT0*/
    {0x2198,       24,     30,     0,      0,      HI_PQ_MODULE_DM,        32},    //dm_sw_wht_lut_p3
    {0x2198,       16,     22,     0,      0,      HI_PQ_MODULE_DM,        16},    //dm_sw_wht_lut_p2
    {0x2198,       8,      14,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_sw_wht_lut_p1
    {0x2198,       0,      6,      0,      0,      HI_PQ_MODULE_DM,        4},     //dm_sw_wht_lut_p0
    /*VPSS_DM_LUT1*/
    {0x219c,       16,     25,     0,      0,      HI_PQ_MODULE_DM,        72},    //dm_limit_t_10
    {0x219c,       8,      15,     0,      0,      HI_PQ_MODULE_DM,        18},    //dm_limit_t
    {0x219c,       0,      6,      0,      0,      HI_PQ_MODULE_DM,        64},    //dm_sw_wht_lut_p4
    /*VPSS_DM_LUT2*/
    {0x21a0,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        11},    //dm_dir_str_gain_lut_p7
    {0x21a0,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        13},    //dm_dir_str_gain_lut_p6
    {0x21a0,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p5
    {0x21a0,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p4
    {0x21a0,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p3
    {0x21a0,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p2
    {0x21a0,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p1
    {0x21a0,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_gain_lut_p0
    /*VPSS_DM_LUT3*/
    {0x21a4,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        14},    //dm_dir_str_lut_p7
    {0x21a4,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_dir_str_lut_p6
    {0x21a4,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        10},    //dm_dir_str_lut_p5
    {0x21a4,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p4
    {0x21a4,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_dir_str_lut_p3
    {0x21a4,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_dir_str_lut_p2
    {0x21a4,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        2},     //dm_dir_str_lut_p1
    {0x21a4,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_dir_str_lut_p0
    /*VPSS_DM_LUT4*/
    {0x21a8,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p15
    {0x21a8,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p14
    {0x21a8,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p13
    {0x21a8,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p12
    {0x21a8,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p11
    {0x21a8,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p10
    {0x21a8,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p9
    {0x21a8,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p8
    /*VPSS_DM_DIRC*/
    {0x21ac,       31,     31,     0,      0,      HI_PQ_MODULE_DM,        1},     //dm_mmf_limit_en
    /*VPSS_DM_DIRO*/
    {0x21b0,       22,     31,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_csw_trsnt_st_10
    /*VPSS_DM_LSW*/
    {0x21b4,       27,     29,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_lsw_ratio
    {0x21b4,       18,     25,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_csw_trsnt_st
    {0x21b4,       8,      17,     0,      0,      HI_PQ_MODULE_DM,        120},   //dm_lw_ctrst_t_10
    {0x21b4,       0,      7,      0,      0,      HI_PQ_MODULE_DM,        30},    //dm_lw_ctrst_t
    /*VPSS_DM_MMFLR*/
    {0x21b8,       20,     27,     0,      0,      HI_PQ_MODULE_DM,        40},    //dm_csw_trsnt_lt
    {0x21b8,       9,      19,     0,      0,      HI_PQ_MODULE_DM,        200},   //dm_mmf_lr_10
    {0x21b8,       0,      8,      0,      0,      HI_PQ_MODULE_DM,        50},    //dm_mmf_lr
    /*VPSS_DM_MMFSR*/
    {0x21bc,       20,     29,     0,      0,      HI_PQ_MODULE_DM,        160},   //dm_csw_trsnt_lt_10
    {0x21bc,       9,      19,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_sr_10
    {0x21bc,       0,      8,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_sr
    /*VPSS_DM_THR0*/
    {0x21c0,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_dir_blend_str
    {0x21c0,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_lim_res_blend_str2
    {0x21c0,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        7},     //dm_lim_res_blend_str1
    {0x21c0,       0,      2,      0,      0,      HI_PQ_MODULE_DM,        4},     //dm_limit_lsw_ratio
    /*VPSS_DM_LUT5*/
    {0x21c4,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_trans_band_lut_p4
    {0x21c4,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_trans_band_lut_p3
    {0x21c4,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_trans_band_lut_p2
    {0x21c4,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        2},     //dm_trans_band_lut_p1
    {0x21c4,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_trans_band_lut_p0
    /*VPSS_DM_LUT6*/
    {0x21c8,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p9
    {0x21c8,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p8
    {0x21c8,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p7
    {0x21c8,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p6
    {0x21c8,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p5
    /*VPSS_DM_LUT7*/
    {0x21cc,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_trans_band_lut_p14
    {0x21cc,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_trans_band_lut_p13
    {0x21cc,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_trans_band_lut_p12
    {0x21cc,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_trans_band_lut_p11
    {0x21cc,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p10
    /*VPSS_DM_LUT8*/
    {0x21d0,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p19
    {0x21d0,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p18
    {0x21d0,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p17
    {0x21d0,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p16
    {0x21d0,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p15
    /*VPSS_DM_LUT9*/
    {0x21d4,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p24
    {0x21d4,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p23
    {0x21d4,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p22
    {0x21d4,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        10},    //dm_trans_band_lut_p21
    {0x21d4,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        10},    //dm_trans_band_lut_p20
    /*VPSS_DM_LUT10*/
    {0x21d8,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p29
    {0x21d8,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p28
    {0x21d8,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p27
    {0x21d8,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p26
    {0x21d8,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p25
    /*VPSS_DM_LUT11*/
    {0x21dc,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p30
    /*VPSS_DM_LUT12*/
    {0x21e0,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p20
    {0x21e0,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p19
    {0x21e0,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p18
    {0x21e0,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p17
    {0x21e0,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_dir_str_lut_p16
    /*VPSS_DM_LUT13*/
    {0x21e4,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        3},     //dm_ang_ctrst_pun_lutp5
    {0x21e4,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        2},     //dm_ang_ctrst_pun_lutp4
    {0x21e4,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        1},     //dm_ang_ctrst_pun_lutp3
    {0x21e4,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        1},     //dm_ang_ctrst_pun_lutp2
    {0x21e4,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_ang_ctrst_pun_lutp1
    {0x21e4,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_ang_ctrst_pun_lutp0
    /*VPSS_DM_LUT14*/
    {0x21e8,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_ang_ctrst_pun_lutp11
    {0x21e8,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        5},     //dm_ang_ctrst_pun_lutp10
    {0x21e8,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        5},     //dm_ang_ctrst_pun_lutp9
    {0x21e8,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_ang_ctrst_pun_lutp8
    {0x21e8,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        4},     //dm_ang_ctrst_pun_lutp7
    {0x21e8,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        3},     //dm_ang_ctrst_pun_lutp6
    /*VPSS_DM_LUT15*/
    {0x21ec,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        9},     //dm_ang_ctrst_pun_lutp17
    {0x21ec,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_ang_ctrst_pun_lutp16
    {0x21ec,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_ang_ctrst_pun_lutp15
    {0x21ec,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_ang_ctrst_pun_lutp14
    {0x21ec,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        7},     //dm_ang_ctrst_pun_lutp13
    {0x21ec,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        6},     //dm_ang_ctrst_pun_lutp12
    /*VPSS_DM_LUT16*/
    {0x21f0,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        23},    //dm_ang_ctrst_pun_lutp23
    {0x21f0,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        22},    //dm_ang_ctrst_pun_lutp22
    {0x21f0,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        21},    //dm_ang_ctrst_pun_lutp21
    {0x21f0,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        18},    //dm_ang_ctrst_pun_lutp20
    {0x21f0,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_ang_ctrst_pun_lutp19
    {0x21f0,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        12},    //dm_ang_ctrst_pun_lutp18
    /*VPSS_DM_LUT17*/
    {0x21f4,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        25},    //dm_ang_ctrst_pun_lutp25
    {0x21f4,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        24},    //dm_ang_ctrst_pun_lutp24
    /*VPSS_DM_TRANS_WID*/
    {0x21f8,       8,      17,     0,      0,      HI_PQ_MODULE_DM,        120},   //dm_trans_wid_10
    {0x21f8,       0,      7,      0,      0,      HI_PQ_MODULE_DM,        30},    //dm_trans_wid
    /*VPSS_DM_DR_CTRL*/
    {0x2500,       7,      7,      0,      0,      HI_PQ_MODULE_DM,        0},     //clipmode
    {0x2500,       6,      6,      0,      0,      HI_PQ_MODULE_DM,        1},     //enangadjstbylm
    {0x2500,       5,      5,      0,      0,      HI_PQ_MODULE_DM,        1},     //enstradjstbylm
    //{0x2500,        0,      0,      0,      0,      HI_PQ_MODULE_DM,        0},     //enep
    {0x2500,       0,      0,      0,      0,      HI_PQ_MODULE_DM,        1},     //enep
    /*VPSS_DR_THR*/
    {0x2504,       18,     28,     0,      0,      HI_PQ_MODULE_DM,        12},    //lradjpixrange_10
    {0x2504,       9,      17,     0,      0,      HI_PQ_MODULE_DM,        3},     //lradjpixrange
    {0x2504,       4,      8,      0,      0,      HI_PQ_MODULE_DM,        8},     //regdrstrenth
    {0x2504,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        7},     //regthrmdfangctrst
    /*VPSS_DRLSWSTRLUT0*/
    {0x2508,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut50
    {0x2508,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut40
    {0x2508,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        10},    //lswstrlut30
    {0x2508,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        10},    //lswstrlut20
    {0x2508,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        8},     //lswstrlut10
    {0x2508,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut00
    /*VPSS_DRLSWSTRLUT1*/
    {0x250c,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        16},    //lswstrlut51
    {0x250c,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        16},    //lswstrlut41
    {0x250c,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        16},    //lswstrlut31
    {0x250c,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        14},    //lswstrlut21
    {0x250c,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut11
    {0x250c,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut01
    /*VPSS_DRLSWSTRLUT2*/
    {0x2510,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        16},    //lswstrlut52
    {0x2510,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        16},    //lswstrlut42
    {0x2510,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut32
    {0x2510,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        10},    //lswstrlut22
    {0x2510,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        6},     //lswstrlut12
    {0x2510,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut02
    /*VPSS_DRLSWSTRLUT3*/
    {0x2514,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut53
    {0x2514,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        12},    //lswstrlut43
    {0x2514,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //lswstrlut33
    {0x2514,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        4},     //lswstrlut23
    {0x2514,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut13
    {0x2514,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut03
    /*VPSS_DRLSWSTRLUT4*/
    {0x2518,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        10},    //lswstrlut54
    {0x2518,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        10},    //lswstrlut44
    {0x2518,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        4},     //lswstrlut34
    {0x2518,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut24
    {0x2518,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut14
    {0x2518,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut04
    /*VPSS_DRLSWSTRLUT5*/
    {0x251c,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        6},     //lswstrlut55
    {0x251c,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        6},     //lswstrlut45
    {0x251c,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut35
    {0x251c,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut25
    {0x251c,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut15
    {0x251c,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut05
    /*VPSS_DRLSWSTRLUT6*/
    {0x2520,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut56
    {0x2520,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        2},     //lswstrlut46
    {0x2520,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut36
    {0x2520,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut26
    {0x2520,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut16
    {0x2520,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut06
    /*VPSS_DRLSWSTRLUT7*/
    {0x2524,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut57
    {0x2524,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut47
    {0x2524,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut37
    {0x2524,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut27
    {0x2524,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut17
    {0x2524,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut07
    /*VPSS_DRLSWSTRLUT8*/
    {0x2528,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut58
    {0x2528,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut48
    {0x2528,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut38
    {0x2528,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut28
    {0x2528,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut18
    {0x2528,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lswstrlut08
    /*VPSS_DRLRWSTRLUT0*/
    {0x252c,       25,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut50
    {0x252c,       20,     24,     0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut40
    {0x252c,       15,     19,     0,      0,      HI_PQ_MODULE_DM,        10},    //lrwstrlut30
    {0x252c,       10,     14,     0,      0,      HI_PQ_MODULE_DM,        10},    //lrwstrlut20
    {0x252c,       5,      9,      0,      0,      HI_PQ_MODULE_DM,        8},     //lrwstrlut10
    {0x252c,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut00
    /*VPSS_DRLRWSTRLUT1*/
    {0x2530,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        16},    //lrwstrlut51
    {0x2530,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        16},    //lrwstrlut41
    {0x2530,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        16},    //lrwstrlut31
    {0x2530,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        14},    //lrwstrlut21
    {0x2530,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut11
    {0x2530,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut01
    /*VPSS_DRLRWSTRLUT2*/
    {0x2534,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        16},    //lrwstrlut52
    {0x2534,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        16},    //lrwstrlut42
    {0x2534,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut32
    {0x2534,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        10},    //lrwstrlut22
    {0x2534,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        6},     //lrwstrlut12
    {0x2534,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut02
    /*VPSS_DRLRWSTRLUT3*/
    {0x2538,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut53
    {0x2538,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        12},    //lrwstrlut43
    {0x2538,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //lrwstrlut33
    {0x2538,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        4},     //lrwstrlut23
    {0x2538,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut13
    {0x2538,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut03
    /*VPSS_DRLRWSTRLUT4*/
    {0x253c,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        10},    //lrwstrlut54
    {0x253c,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        10},    //lrwstrlut44
    {0x253c,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        4},     //lrwstrlut34
    {0x253c,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut24
    {0x253c,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut14
    {0x253c,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut04
    /*VPSS_DRLRWSTRLUT5*/
    {0x2540,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        6},     //lrwstrlut55
    {0x2540,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        6},     //lrwstrlut45
    {0x2540,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut35
    {0x2540,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut25
    {0x2540,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut15
    {0x2540,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut05
    /*VPSS_DRLRWSTRLUT6*/
    {0x2544,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut56
    {0x2544,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        2},     //lrwstrlut46
    {0x2544,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut36
    {0x2544,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut26
    {0x2544,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut16
    {0x2544,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut06
    /*VPSS_DRLRWSTRLUT7*/
    {0x2548,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut57
    {0x2548,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut47
    {0x2548,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut37
    {0x2548,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut27
    {0x2548,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut17
    {0x2548,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut07
    /*VPSS_DRLRWSTRLUT8*/
    {0x254c,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut58
    {0x254c,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut48
    {0x254c,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut38
    {0x254c,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut28
    {0x254c,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut18
    {0x254c,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //lrwstrlut08
    /*VPSS_DRLSWSTRADJUSTLUT0*/
    {0x2550,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lswadjlut2
    {0x2550,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lswadjlut1
    {0x2550,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lswadjlut0
    /*VPSS_DRLSWSTRADJUSTLUT1*/
    {0x2554,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        8},     //dr_lswadjlut5
    {0x2554,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        6},     //dr_lswadjlut4
    {0x2554,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lswadjlut3
    /*VPSS_DRLSWSTRADJUSTLUT2*/
    {0x2558,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        8},     //dr_lswadjlut8
    {0x2558,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        8},     //dr_lswadjlut7
    {0x2558,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        8},     //dr_lswadjlut6
    /*VPSS_DRLRWSTRADJUSTLUT0*/
    {0x255c,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut2
    {0x255c,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut1
    {0x255c,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut0
    /*VPSS_DRLRWSTRADJUSTLUT1*/
    {0x2560,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut5
    {0x2560,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut4
    {0x2560,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut3
    /*VPSS_DRLRWSTRADJUSTLUT2*/
    {0x2564,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut8
    {0x2564,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut7
    {0x2564,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_lrwadjlut6
    /*VPSS_DRANGADJSUTLUT0*/
    {0x2568,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        6},     //dr_angadjlut2
    {0x2568,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        8},     //dr_angadjlut1
    {0x2568,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        12},    //dr_angadjlut0
    /*VPSS_DRANGADJSUTLUT1*/
    {0x256c,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut5
    {0x256c,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut4
    {0x256c,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut3
    /*VPSS_DRANGADJSUTLUT2*/
    {0x2570,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut8
    {0x2570,        4,      7,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut7
    {0x2570,        0,      3,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angadjlut6
    /*VPSS_DRANGLESTRLUT1_0*/
    {0x2574,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        2},     //dr_angdifflut5
    {0x2574,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        1},     //dr_angdifflut4
    {0x2574,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        1},     //dr_angdifflut3
    {0x2574,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angdifflut2
    {0x2574,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angdifflut1
    {0x2574,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angdifflut0
    /*VPSS_DRANGLESTRLUT1_1*/
    {0x2578,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        8},     //dr_angdifflut11
    {0x2578,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        7},     //dr_angdifflut10
    {0x2578,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        6},     //dr_angdifflut9
    {0x2578,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        5},     //dr_angdifflut8
    {0x2578,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        4},     //dr_angdifflut7
    {0x2578,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        3},     //dr_angdifflut6
    /*VPSS_DRANGLESTRLUT1_2*/
    {0x257c,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        16},    //dr_angdifflut16
    {0x257c,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        15},    //dr_angdifflut15
    {0x257c,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        14},    //dr_angdifflut14
    {0x257c,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        13},    //dr_angdifflut13
    {0x257c,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        12},    //dr_angdifflut12
    /*VPSS_DRANGLESTRLUT2_0*/
    {0x2580,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        2},     //dr_angminlut5
    {0x2580,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        6},     //dr_angminlut4
    {0x2580,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        12},    //dr_angminlut3
    {0x2580,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        14},    //dr_angminlut2
    {0x2580,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        16},    //dr_angminlut1
    {0x2580,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        16},    //dr_angminlut0
    /*VPSS_DRANGLESTRLUT2_1*/
    {0x2584,        25,     29,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut11
    {0x2584,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut10
    {0x2584,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut9
    {0x2584,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut8
    {0x2584,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut7
    {0x2584,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut6
    /*VPSS_DRANGLESTRLUT2_2*/
    {0x2588,        20,     24,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut16
    {0x2588,        15,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut15
    {0x2588,        10,     14,     0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut14
    {0x2588,        5,      9,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut13
    {0x2588,        0,      4,      0,      0,      HI_PQ_MODULE_DM,        0},     //dr_angminlut12
    /*VPSS_DMDR_MERGE*/
    {0x258c,        8,      11,     0,      0,      HI_PQ_MODULE_DM,        7},     //drdir_blend_str
    {0x258c,        7,      7,      0,      0,      HI_PQ_MODULE_DM,        1},     //dmcond_app_dren
    {0x258c,        3,      6,      0,      0,      HI_PQ_MODULE_DM,        8},     //u8drdm_blend_str
    {0x258c,        0,      2,      0,      0,      HI_PQ_MODULE_DM,        7},     //u8drdm_merge_mode
    /*VPSS_DMDR_MERGE_DELTA0*/
    {0x2590,        11,     25,     0,      0,      HI_PQ_MODULE_DM,        4800},  //alpha_acthvrange
    {0x2590,        0,      10,     0,      0,      HI_PQ_MODULE_DM,        109},   //alpha_acthvratio
    /*VPSS_DMDR_MERGE_DELTA1*/
    {0x2594,        16,     31,     0,      0,      HI_PQ_MODULE_DM,        3200},  //winact_limit
    {0x2594,        0,      15,     0,      0,      HI_PQ_MODULE_DM,        6400},  //winact_cliplimit
    /*VPSS_DMDR_MERGE_DELTA2*/
    {0x2598,        11,     23,     0,      0,      HI_PQ_MODULE_DM,        16},    //angstr1_minusfac
    {0x2598,        0,      10,     0,      0,      HI_PQ_MODULE_DM,        82},    //winact_ratio



    /***********************************************SNR SD*********************************************/
    /*VPSS_SNR_CTRL*/
    {0x2100,        16,     18,     1,      0,      HI_PQ_MODULE_SNR,       6},     //dbm_out_mode
    {0x2100,        14,     15,     1,      0,      HI_PQ_MODULE_SNR,       0},     //mad_mode
    {0x2100,        2,      2,      1,      0,      HI_PQ_MODULE_SNR,       1},     //snr_en
    /*VPSS_SNR_ENABLE*/
    {0x2300,        7,      7,      1,      0,      HI_PQ_MODULE_SNR,       0},     //test_en
    {0x2300,        5,      5,      1,      0,      HI_PQ_MODULE_SNR,       1},     //edgeprefilteren
    {0x2300,        4,      4,      1,      0,      HI_PQ_MODULE_SNR,       0},     //colorweighten
    {0x2300,        3,      3,      1,      0,      HI_PQ_MODULE_SNR,       1},     //motionedgeweighten
    {0x2300,        2,      2,      1,      0,      HI_PQ_MODULE_SNR,       1},     //cnr2den
    {0x2300,        1,      1,      1,      0,      HI_PQ_MODULE_SNR,       1},     //ynr2den
    {0x2304,        8,      11,     1,      0,      HI_PQ_MODULE_SNR,       15},     //edgeoriratio
    {0x2304,        4,      7,      1,      0,      HI_PQ_MODULE_SNR,       1},     //edgeminratio
    {0x2304,        0,      3,      1,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxratio
    {0x2308,        8,      11,     1,      0,      HI_PQ_MODULE_SNR,       0},     //edgeoristrength
    {0x2308,        4,      7,      1,      0,      HI_PQ_MODULE_SNR,       0},     //edgeminstrength
    {0x2308,        0,      3,      1,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxstrength
    {0x230c,        20,     29,     1,      0,      HI_PQ_MODULE_SNR,       24},    //edgestrth3
    {0x230c,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       16},    //edgestrth2
    {0x230c,        0,      9,      1,      0,      HI_PQ_MODULE_SNR,       12},     //edgestrth1
    {0x2310,        12,     17,     1,      0,      HI_PQ_MODULE_SNR,       32},    //edgestrk3
    {0x2310,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       36},    //edgestrk2
    {0x2310,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       32},    //edgestrk1
    {0x2314,        20,     29,     1,      0,      HI_PQ_MODULE_SNR,       128 / 16}, //edgemeanth3
    {0x2314,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       90 / 16}, //edgemeanth2
    {0x2314,        0,      9,      1,      0,      HI_PQ_MODULE_SNR,       64 / 16}, //edgemeanth1
    {0x2318,        20,     29,     1,      0,      HI_PQ_MODULE_SNR,       300 / 16}, //edgemeanth6
    {0x2318,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       196 / 16}, //edgemeanth5
    {0x2318,        0,      9,      1,      0,      HI_PQ_MODULE_SNR,       164 / 16}, //edgemeanth4
    {0x231c,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       768 / 16}, //edgemeanth8
    {0x231c,        0,      9,      1,      0,      HI_PQ_MODULE_SNR,       512 / 16}, //edgemeanth7
    {0x2320,        18,     23,     1,      0,      HI_PQ_MODULE_SNR,       10},    //edgemeank4
    {0x2320,        12,     17,     1,      0,      HI_PQ_MODULE_SNR,       20},    //edgemeank3
    {0x2320,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       32},    //edgemeank2
    {0x2320,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       0},     //edgemeank1
    {0x2324,        18,     23,     1,      0,      HI_PQ_MODULE_SNR,       1},     //edgemeank8
    {0x2324,        12,     17,     1,      0,      HI_PQ_MODULE_SNR,       2},     //edgemeank7
    {0x2324,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       4},     //edgemeank6
    {0x2324,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       6},     //edgemeank5
    {0x2328,        13,     14,     1,      0,      HI_PQ_MODULE_SNR,       3},     //c2dwinheight
    {0x2328,        9,      12,     1,      0,      HI_PQ_MODULE_SNR,       5},     //c2dwinwidth
    {0x2328,        5,      8,      1,      0,      HI_PQ_MODULE_SNR,       5},     //y2dwinheight
    {0x2328,        0,      4,      1,      0,      HI_PQ_MODULE_SNR,       9},     //y2dwinwidth
    {0x232c,        8,      15,     1,      0,      HI_PQ_MODULE_SNR,       32},    //csnrstr
    {0x232c,        0,      7,      1,      0,      HI_PQ_MODULE_SNR,       32},    //ysnrstr
    {0x2330,        6,      7,      1,      0,      HI_PQ_MODULE_SNR,       3},     //stroffset3
    {0x2330,        4,      5,      1,      0,      HI_PQ_MODULE_SNR,       2},     //stroffset2
    {0x2330,        2,      3,      1,      0,      HI_PQ_MODULE_SNR,       1},     //stroffset1
    {0x2330,        0,      1,      1,      0,      HI_PQ_MODULE_SNR,       0},     //stroffset0
    {0x2334,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       16},    //cstradjust
    {0x2334,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       16},    //ystradjust
    {0x2338,        0,      3,      1,      0,      HI_PQ_MODULE_SNR,       3},     //scenechangeth
    {0x234c,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       128},   //test_color_cr
    {0x234c,        0,      9,      1,      0,      HI_PQ_MODULE_SNR,       128},   //test_color_cb
    {0x2350,        30,     30,     1,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode2_en
    {0x2350,        20,     29,     1,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_bldcore
    {0x2350,        10,     19,     1,      0,      HI_PQ_MODULE_SNR,       96},    //scenechange_bldk
    {0x2350,        9,       9,     1,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode1_en
    {0x2350,        8,       8,     1,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_en
    {0x2350,        0,      7,      1,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_info
    {0x2354,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       32},    //motionalpha
    {0x2358,        24,     27,     1,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight1
    {0x2358,        18,     23,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end1
    {0x2358,        12,     17,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end1
    {0x2358,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin1
    {0x2358,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin1
    {0x235c,        24,     27,     1,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight2
    {0x235c,        18,     23,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end2
    {0x235c,        12,     17,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end2
    {0x235c,        6,      11,     1,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin2
    {0x235c,        0,      5,      1,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin2
    /***********************************************SNR FHD********************************************/
    {0x2100,        16,     18,     2,      0,      HI_PQ_MODULE_SNR,       6},     //dbm_out_mode
    {0x2100,        14,     15,     2,      0,      HI_PQ_MODULE_SNR,       2},     //mad_mode
    {0x2100,        2,      2,      2,      0,      HI_PQ_MODULE_SNR,       1},     //snr_en
    {0x2300,        7,      7,      2,      0,      HI_PQ_MODULE_SNR,       0},     //test_en
    {0x2300,        5,      5,      2,      0,      HI_PQ_MODULE_SNR,       1},     //edgeprefilteren
    {0x2300,        4,      4,      2,      0,      HI_PQ_MODULE_SNR,       0},     //colorweighten
    {0x2300,        3,      3,      2,      0,      HI_PQ_MODULE_SNR,       1},     //motionedgeweighten
    {0x2300,        2,      2,      2,      0,      HI_PQ_MODULE_SNR,       1},     //cnr2den
    {0x2300,        1,      1,      2,      0,      HI_PQ_MODULE_SNR,       1},     //ynr2den
    {0x2304,        8,      11,     2,      0,      HI_PQ_MODULE_SNR,       15},     //edgeoriratio
    {0x2304,        4,      7,      2,      0,      HI_PQ_MODULE_SNR,       1},     //edgeminratio
    {0x2304,        0,      3,      2,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxratio
    {0x2308,        8,      11,     2,      0,      HI_PQ_MODULE_SNR,       0},     //edgeoristrength
    {0x2308,        4,      7,      2,      0,      HI_PQ_MODULE_SNR,       0},     //edgeminstrength
    {0x2308,        0,      3,      2,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxstrength
    /*VPSS_SNR_EDGE_STRTH*/
    {0x230c,        20,     29,     2,      0,      HI_PQ_MODULE_SNR,       24},    //edgestrth3
    {0x230c,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       16},    //edgestrth2
    {0x230c,        0,      9,      2,      0,      HI_PQ_MODULE_SNR,       8},     //edgestrth1
    /*VPSS_SNR_EDGE_STRK*/
    {0x2310,        12,     17,     2,      0,      HI_PQ_MODULE_SNR,       32},    //edgestrk3
    {0x2310,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       36},    //edgestrk2
    {0x2310,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       32},    //edgestrk1
    /*VPSS_SNR_EDGE_MEANTH1*/
    {0x2314,        20,     29,     2,      0,      HI_PQ_MODULE_SNR,       128 / 16}, //edgemeanth3
    {0x2314,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       90 / 16}, //edgemeanth2
    {0x2314,        0,      9,      2,      0,      HI_PQ_MODULE_SNR,       64 / 16}, //edgemeanth1
    /*VPSS_SNR_EDGE_MEANTH2*/
    {0x2318,        20,     29,     2,      0,      HI_PQ_MODULE_SNR,       300 / 16}, //edgemeanth6
    {0x2318,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       196 / 16}, //edgemeanth5
    {0x2318,        0,      9,      2,      0,      HI_PQ_MODULE_SNR,       164 / 16}, //edgemeanth4
    /*VPSS_SNR_EDGE_MEANTH3*/
    {0x231c,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       768 / 16}, //edgemeanth8
    {0x231c,        0,      9,      2,      0,      HI_PQ_MODULE_SNR,       512 / 16}, //edgemeanth7
    /*VPSS_SNR_EDGE_MEANK1*/
    {0x2320,        18,     23,     2,      0,      HI_PQ_MODULE_SNR,       10},    //edgemeank4
    {0x2320,        12,     17,     2,      0,      HI_PQ_MODULE_SNR,       20},    //edgemeank3
    {0x2320,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       32},    //edgemeank2
    {0x2320,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       0},     //edgemeank1
    /*VPSS_SNR_EDGE_MEANK2*/
    {0x2324,        18,     23,     2,      0,      HI_PQ_MODULE_SNR,       1},     //edgemeank8
    {0x2324,        12,     17,     2,      0,      HI_PQ_MODULE_SNR,       2},     //edgemeank7
    {0x2324,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       4},     //edgemeank6
    {0x2324,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       6},     //edgemeank5
    /*VPSS_SNR_WIN*/
    {0x2328,        13,     14,     2,      0,      HI_PQ_MODULE_SNR,       3},     //c2dwinheight
    {0x2328,        9,      12,     2,      0,      HI_PQ_MODULE_SNR,       5},     //c2dwinwidth
    {0x2328,        5,      8,      2,      0,      HI_PQ_MODULE_SNR,       5},     //y2dwinheight
    {0x2328,        0,      4,      2,      0,      HI_PQ_MODULE_SNR,       9},     //y2dwinwidth
    /*VPSS_SNR_STR*/
    {0x232c,        8,      15,     2,      0,      HI_PQ_MODULE_SNR,       32},    //csnrstr
    {0x232c,        0,      7,      2,      0,      HI_PQ_MODULE_SNR,       32},    //ysnrstr
    /*VPSS_SNR_STR_OFFSET*/
    {0x2330,        6,      7,      2,      0,      HI_PQ_MODULE_SNR,       3},     //stroffset3
    {0x2330,        4,      5,      2,      0,      HI_PQ_MODULE_SNR,       2},     //stroffset2
    {0x2330,        2,      3,      2,      0,      HI_PQ_MODULE_SNR,       1},     //stroffset1
    {0x2330,        0,      1,      2,      0,      HI_PQ_MODULE_SNR,       0},     //stroffset0
    /*VPSS_SNR_STR_ADJUST*/
    {0x2334,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       16},    //cstradjust
    {0x2334,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       16},    //ystradjust
    /*VPSS_SNR_SCHANGE_TH*/
    {0x2338,        0,      3,      2,      0,      HI_PQ_MODULE_SNR,       3},     //scenechangeth
    /*VPSS_SNR_EDGE_RATIO_1*/
    /*VPSS_SNR_EDGE_RATIO_2*/
    /*VPSS_SNR_EDGE_RATIO_3*/
    /*VPSS_SNR_EDGE_STR*/
    /*VPSS_SNR_TEST_COLOR*/
    {0x234c,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       128},   //test_color_cr
    {0x234c,        0,      9,      2,      0,      HI_PQ_MODULE_SNR,       128},   //test_color_cb
    /*VPSS_SNR_SCHANGE*/
    {0x2350,        30,     30,     2,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode2_en
    {0x2350,        20,     29,     2,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_bldcore
    {0x2350,        10,     19,     2,      0,      HI_PQ_MODULE_SNR,       96},    //scenechange_bldk
    {0x2350,        9,       9,     2,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode1_en
    {0x2350,        8,       8,     2,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_en
    {0x2350,        0,      7,      2,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_info
    /*VPSS_SNR_MT*/
    {0x2354,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       32},    //motionalpha
    /*VPSS_SNR_CBCR_W1*/
    {0x2358,        24,     27,     2,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight1
    {0x2358,        18,     23,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end1
    {0x2358,        12,     17,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end1
    {0x2358,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin1
    {0x2358,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin1
    /*VPSS_SNR_CBCR_W2*/
    {0x235c,        24,     27,     2,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight2
    {0x235c,        18,     23,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end2
    {0x235c,        12,     17,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end2
    {0x235c,        6,      11,     2,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin2
    {0x235c,        0,      5,      2,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin2

    /*******************************************VDP4KSNR_UHD******************************************/
    /*SNR_ENABLE*/
    {0xe000,        23,     27,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       16},    //snrstrength
    {0xe000,        22,     22,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //snrfiltermode
    {0xe000,        21,     21,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratioen
    {0xe000,        19,     20,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //edgelpfmode
    {0xe000,        12,     13,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       1},     //debugmode
    {0xe000,        11,     11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //debugmodeen
    {0xe000,        10,     10,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //demomodelr
    {0xe000,        9,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //demomodeen
    {0xe000,        7,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //blendingmode
    {0xe000,        6,      6,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       1},     //edgeonlyen
    {0xe000,        3,      3,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //edgeprelpfen
    {0xe000,        1,      1,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       1},     //lumasnren
    /*SNR_EDGE_RATIO*/
    {0xe004,        0,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       8},     //meanedgeratiox0
    {0xe004,        10,     19,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       40},    //meanedgeratiox1
    {0xe004,        20,     29,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratiox2
    {0xe008,        0,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       128},   //meanedgeratiox3
    {0xe008,        10,     19,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       255},   //meanedgeratiox4
    {0xe008,        20,     29,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       1023},  //meanedgeratiox5
    {0xe00c,        0,      6,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratioy0
    {0xe00c,        7,      13,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratioy1
    {0xe00c,        14,     20,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratioy2
    {0xe010,        0,      6,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratioy3
    {0xe010,        7,      13,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //meanedgeratioy4
    {0xe014,        0,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratiok0
    {0xe014,        8,      15,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratiok1
    {0xe018,        0,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratiok2
    {0xe018,        8,      15,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratiok3
    {0xe01c,        7,      13,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //meanedgeratiomin
    {0xe01c,        0,      6,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       127},   //meanedgeratiomax
    /*SNR_EDGE_STR*/
    {0xe020,        0,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       7},     //edgestrmappingx0
    {0xe020,        10,     19,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       15},    //edgestrmappingx1
    {0xe020,        20,     29,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       31},    //edgestrmappingx2
    {0xe024,        0,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       63},    //edgestrmappingx3
    {0xe024,        10,     19,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       127},   //edgestrmappingx4
    {0xe024,        20,     29,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       255},   //edgestrmappingx5
    {0xe028,        0,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       511},   //edgestrmappingx6
    {0xe028,        10,     19,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       1023},  //edgestrmappingx7
    {0xe02c,        0,      5,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //edgestrmappingy0
    {0xe02c,        6,      11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       4},     //edgestrmappingy1
    {0xe02c,        12,     17,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       10},    //edgestrmappingy2
    {0xe02c,        18,     23,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       18},    //edgestrmappingy3
    {0xe030,        0,      5,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       30},    //edgestrmappingy4
    {0xe030,        6,      11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       46},    //edgestrmappingy5
    {0xe030,        12,     17,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       63},    //edgestrmappingy6
    {0xe034,        0,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       128},   //edgestrmappingk0
    {0xe034,        8,      15,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       96},    //edgestrmappingk1
    {0xe034,        16,     23,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       64},    //edgestrmappingk2
    {0xe038,        0,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       48},    //edgestrmappingk3
    {0xe038,        8,      15,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       32},    //edgestrmappingk4
    {0xe038,        16,     23,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       17},    //edgestrmappingk5
    {0xe03c,        6,      11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       63},    //edgestrmappingmax
    {0xe03c,        0,      5,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //edgestrmappingmin
    /*SNR_FYMAX_VALTH*/
    {0xe040,        0,      4,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       4},     //sfymaxedgevalthd1
    {0xe040,        5,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       7},     //sfymaxedgevalthd2
    {0xe040,        10,     14,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       11},    //sfymaxedgevalthd3
    {0xe044,        0,      3,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //sfymaxedgeidxthd1
    {0xe044,        4,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //sfymaxedgeidxthd2
    {0xe044,        8,      11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //sfymaxedgeidxthd3
    {0xe048,        0,      4,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       2},     //sfymeanedgevalthd1
    {0xe048,        5,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       4},     //sfymeanedgevalthd2
    {0xe048,        10,     14,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       6},     //sfymeanedgevalthd3
    {0xe04c,        0,      4,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       27},    //wfymaxedgevalthd1
    {0xe04c,        5,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       24},    //wfymaxedgevalthd2
    {0xe04c,        10,     14,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       21},    //wfymaxedgevalthd3
    {0xe050,        0,      3,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       1},     //wfymaxedgeidxthd1
    {0xe050,        4,      7,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       2},     //wfymaxedgeidxthd2
    {0xe050,        8,      11,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       4},     //wfymaxedgeidxthd3
    {0xe054,        0,      4,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       24},    //wfymeanedgevalthd1
    {0xe054,        5,      9,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       21},    //wfymeanedgevalthd2
    {0xe054,        10,     14,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       18},    //wfymeanedgevalthd3
    /*SNR_FILTER_TYPE*/
    {0xe070,        0,      2,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       3},     //ydefaultfiltertype
    /*SNR_NOISE_CORE*/
    {0xe074,        5,      10,     3,      0,      HI_PQ_MODULE_VDP4KSNR,       32},    //nonoisegain
    {0xe074,        0,      4,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       0},     //noisecore
    {0xe078,        1,      5,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       3},     //randyinnoiselevel
    {0xe078,        0,      0,      3,      0,      HI_PQ_MODULE_VDP4KSNR,       1},     //addrandyinnoiseen


    /***********************************************MCNR_SD***********************************************/
    /*VPSS_TNR_CONTRL*/
    {0x3800,        22,     23,     1,      0,      HI_PQ_MODULE_TNR,       2},     //mcnr_rgme_mode
    {0x3800,        20,     21,     1,      0,      HI_PQ_MODULE_TNR,       0},     //motion_mode
    {0x3800,        7,      19,     1,      0,      HI_PQ_MODULE_TNR,       0},     //marketcoor
    {0x3800,        6,      6,      1,      0,      HI_PQ_MODULE_TNR,       0},     //marketmode
    {0x3800,        5,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //marketmodeen
    {0x3800,        4,      4,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mcnr_meds_en
    {0x3800,        3,      3,      1,      0,      HI_PQ_MODULE_TNR,       1},     //mcnr_en
    {0x3800,        2,      2,      1,      0,      HI_PQ_MODULE_TNR,       1},     //cnren
    {0x3800,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ynren
    {0x3800,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //nren
    /*VPSS_TNR_MAMD_CTRL*/
    {0x3804,        20,     22,     1,      0,      HI_PQ_MODULE_TNR,       0},     //alpha2
    {0x3804,        17,     19,     1,      0,      HI_PQ_MODULE_TNR,       0},     //alpha1
    {0x3804,        15,     16,     1,      0,      HI_PQ_MODULE_TNR,       2},     //cmotionlpfmode
    {0x3804,        13,     14,     1,      0,      HI_PQ_MODULE_TNR,       2},     //ymotionlpfmode
    {0x3804,        11,     12,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncalcmode
    {0x3804,        9,      10,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncalcmode
    {0x3804,        6,      8,      1,      0,      HI_PQ_MODULE_TNR,       4},     //meancadjshift
    {0x3804,        3,      5,      1,      0,      HI_PQ_MODULE_TNR,       4},     //meanyadjshift
    {0x3804,        2,      2,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mean_cmotion_adj_en
    {0x3804,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mean_ymotion_adj_en
    {0x3804,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //mdprelpfen
    /*VPSS_TNR_MAMD_GAIN*/
    {0x3808,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmdcore
    {0x3808,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       15},    //cmdgain
    {0x3808,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymdcore
    {0x3808,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       15},    //ymdgain
    /*VPSS_TNR_MAND_CTRL*/
    {0x380c,        9,      10,     1,      0,      HI_PQ_MODULE_TNR,       3},     //randomctrlmode
    {0x380c,        1,      8,      1,      0,      HI_PQ_MODULE_TNR,       32},    //blkdiffthd
    {0x380c,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //noisedetecten
    /*VPSS_TNR_MAND_THD*/
    {0x3810,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       32},    //flatthdmax
    {0x3810,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       20},    //flatthdmed
    {0x3810,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       12},    //flatthdmin
    /*VPSS_TNR_MAME_CTRL*/
    {0x3814,        13,     15,     1,      0,      HI_PQ_MODULE_TNR,       4},     //smvythd
    {0x3814,        10,     12,     1,      0,      HI_PQ_MODULE_TNR,       4},     //smvxthd
    {0x3814,        9,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvyen
    {0x3814,        8,      8,      1,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvxen
    {0x3814,        5,      7,      1,      0,      HI_PQ_MODULE_TNR,       0},     //gm_adj
    {0x3814,        3,      4,      1,      0,      HI_PQ_MODULE_TNR,       2},     //mvlpfmode
    {0x3814,        1,      2,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mvrefmode
    {0x3814,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //motionestimateen
    /*VPSS_TNR_MAME_GAIN*/
    {0x3818,        24,     31,     1,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_xmv
    {0x3818,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_xmv
    {0x3818,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_0mv
    {0x3818,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_0mv
    /*VPSS_TNR_MAME_STD_CORE*/
    {0x381c,        25,     29,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_xmv
    {0x381c,        20,     24,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_xmv
    {0x381c,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_0mv
    {0x381c,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_0mv
    {0x381c,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //std_core_xmv
    {0x381c,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       28},    //std_core_0mv
    /*VPSS_TNR_MAME_STD_GAIN*/
    {0x3820,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //std_pnl_core
    {0x3820,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       31},    //std_pnl_gain
    /*VPSS_TNR_MAME_MV_THD*/
    {0x3824,        25,     29,     1,      0,      HI_PQ_MODULE_TNR,       16},    //adj_xmv_max
    {0x3824,        20,     24,     1,      0,      HI_PQ_MODULE_TNR,       16},    //adj_0mv_max
    {0x3824,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       4},     //adj_xmv_min
    {0x3824,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       4},     //adj_0mv_min
    {0x3824,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       10},    //adj_mv_min
    {0x3824,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       24},    //adj_mv_max
    /*VPSS_TNR_MAMC_CBCR_UPEN*/
    {0x3828,        5,      8,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight2
    {0x3828,        1,      4,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight1
    {0x3828,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbcrupdateen
    /*VPSS_TNR_MAMC_CBCR_UPTHD1*/
    {0x382c,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crend1
    {0x382c,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cbend1
    {0x382c,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin1
    {0x382c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin1
    /*VPSS_TNR_MAMC_CBCR_UPTHD2*/
    {0x3830,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crend2
    {0x3830,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cbend2
    {0x3830,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin2
    {0x3830,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin2
    /*VPSS_TNR_MAMC_PRE_MAD*/
    {0x3834,        6,      10,     1,      0,      HI_PQ_MODULE_TNR,       16},    //motionmergeratio
    {0x3834,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       18},    //premotionalpha
    {0x3834,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //premotionmergemode
    /*VPSS_TNR_MAMC_MAP*/
    {0x3838,        17,     22,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncore
    {0x3838,        12,     16,     1,      0,      HI_PQ_MODULE_TNR,       24},    //cmotiongain
    {0x3838,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncore
    {0x3838,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       24},    //ymotiongain
    {0x3838,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       0},     //motionmappingen
    /*VPSS_TNR_MAMC_SALTUS*/
    {0x383c,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //saltuslevel
    {0x383c,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //saltusdecten
    /*VPSS_TNR_MAMC_MCADJ*/
    {0x3840,        4,      5,      1,      0,      HI_PQ_MODULE_TNR,       3},     //cmclpfmode
    {0x3840,        2,      3,      1,      0,      HI_PQ_MODULE_TNR,       3},     //ymclpfmode
    {0x3840,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       1},     //cmcadjen
    {0x3840,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ymcadjen
    /*VPSS_TNR_FILR_MODE*/
    {0x3844,        7,      11,     1,      0,      HI_PQ_MODULE_TNR,       2},     //cnonrrange
    {0x3844,        2,      6,      1,      0,      HI_PQ_MODULE_TNR,       2},     //ynonrrange
    {0x3844,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotionmode
    {0x3844,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ymotionmode
    /*VPSS_TNR_SCENE_CHANGE*/
    {0x3848,        1,      8,      1,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeinfo
    {0x3848,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //scenechangeen
    /*VPSS_TNR_CFG*/
    {0x384c,        17,     21,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_cmdcore
    {0x384c,        11,     16,     1,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_cmdgain
    {0x384c,        6,      10,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_ymdcore
    {0x384c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_ymdgain
    /*VPSS_TNR_FLAT_INFO*/
    {0x3850,        24,     31,     1,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymax
    {0x3850,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       56},    //flatinfoxmax
    {0x3850,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymin
    {0x3850,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       64},    //flatinfoxmin
    /*VPSS_TNR_YBLEND*/
    {0x385c,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //yblendingymax
    {0x385c,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       12},    //yblendingxmax
    {0x385c,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       16},    //yblendingymin
    {0x385c,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       0},     //yblendingxmin
    /*VPSS_TNR_CBLEND*/
    {0x3858,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //cblendingymax
    {0x3858,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       12},    //cblendingxmax
    {0x3858,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       16},    //cblendingymin
    {0x3858,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cblendingxmin
    /*VPSS_TNR_DTBLEND*/
    {0x385c,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //dtblendingymax
    {0x385c,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       15},    //dtblendingxmax
    {0x385c,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       12},    //dtblendingymin
    {0x385c,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       1},     //dtblendingxmin
    /*VPSS_TNR_MEAN_MOTION_LUT0*/
    {0x3900,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio3
    {0x3900,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio2
    {0x3900,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio1
    {0x3900,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio0
    /*VPSS_TNR_MEAN_MOTION_LUT1*/
    {0x3904,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio7
    {0x3904,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio6
    {0x3904,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio5
    {0x3904,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio4
    /*VPSS_TNR_MEAN_MOTION_LUT2*/
    {0x3908,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio11
    {0x3908,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio10
    {0x3908,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio9
    {0x3908,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio8
    /*VPSS_TNR_MEAN_MOTION_LUT3*/
    {0x390c,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio15
    {0x390c,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio14
    {0x390c,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio13
    {0x390c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio12


    /***********************************************MCNR_FHD***********************************************/
    /*VPSS_TNR_CONTRL*/
    {0x3800,        22,     23,     2,      0,      HI_PQ_MODULE_TNR,       2},     //mcnr_rgme_mode
    {0x3800,        20,     21,     2,      0,      HI_PQ_MODULE_TNR,       2},     //motion_mode
    {0x3800,        7,      19,     2,      0,      HI_PQ_MODULE_TNR,       0},     //marketcoor
    {0x3800,        6,      6,      2,      0,      HI_PQ_MODULE_TNR,       0},     //marketmode
    {0x3800,        5,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //marketmodeen
    {0x3800,        4,      4,      2,      0,      HI_PQ_MODULE_TNR,       1},     //mcnr_meds_en
    {0x3800,        3,      3,      2,      0,      HI_PQ_MODULE_TNR,       1},     //mcnr_en
    {0x3800,        2,      2,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cnren
    {0x3800,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       1},     //ynren
    {0x3800,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //nren
    /*VPSS_TNR_MAMD_CTRL*/
    {0x3804,        20,     22,     2,      0,      HI_PQ_MODULE_TNR,       0},     //alpha2
    {0x3804,        17,     19,     2,      0,      HI_PQ_MODULE_TNR,       0},     //alpha1
    {0x3804,        15,     16,     2,      0,      HI_PQ_MODULE_TNR,       2},     //cmotionlpfmode
    {0x3804,        13,     14,     2,      0,      HI_PQ_MODULE_TNR,       2},     //ymotionlpfmode
    {0x3804,        11,     12,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncalcmode
    {0x3804,        9,      10,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncalcmode
    {0x3804,        6,      8,      2,      0,      HI_PQ_MODULE_TNR,       4},     //meancadjshift
    {0x3804,        3,      5,      2,      0,      HI_PQ_MODULE_TNR,       4},     //meanyadjshift
    {0x3804,        2,      2,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mean_cmotion_adj_en
    {0x3804,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mean_ymotion_adj_en
    {0x3804,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mdprelpfen
    /*VPSS_TNR_MAMD_GAIN*/
    {0x3808,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmdcore
    {0x3808,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       15},    //cmdgain
    {0x3808,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymdcore
    {0x3808,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       15},    //ymdgain
    /*VPSS_TNR_MAND_CTRL*/
    {0x380c,        9,      10,     2,      0,      HI_PQ_MODULE_TNR,       3},     //randomctrlmode
    {0x380c,        1,      8,      2,      0,      HI_PQ_MODULE_TNR,       64},    //blkdiffthd
    {0x380c,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //noisedetecten
    /*VPSS_TNR_MAND_THD*/
    {0x3810,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       32},    //flatthdmax
    {0x3810,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       20},    //flatthdmed
    {0x3810,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       12},    //flatthdmin
    /*VPSS_TNR_MAME_CTRL*/
    {0x3814,        13,     15,     2,      0,      HI_PQ_MODULE_TNR,       4},     //smvythd
    {0x3814,        10,     12,     2,      0,      HI_PQ_MODULE_TNR,       4},     //smvxthd
    {0x3814,        9,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvyen
    {0x3814,        8,      8,      2,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvxen
    {0x3814,        5,      7,      2,      0,      HI_PQ_MODULE_TNR,       0},     //gm_adj
    {0x3814,        3,      4,      2,      0,      HI_PQ_MODULE_TNR,       2},     //mvlpfmode
    {0x3814,        1,      2,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mvrefmode
    {0x3814,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //motionestimateen
    /*VPSS_TNR_MAME_GAIN*/
    {0x3818,        24,     31,     2,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_xmv
    {0x3818,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_xmv
    {0x3818,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_0mv
    {0x3818,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_0mv
    /*VPSS_TNR_MAME_STD_CORE*/
    {0x381c,        25,     29,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_xmv
    {0x381c,        20,     24,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_xmv
    {0x381c,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_0mv
    {0x381c,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_0mv
    {0x381c,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //std_core_xmv
    {0x381c,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       28},    //std_core_0mv
    /*VPSS_TNR_MAME_STD_GAIN*/
    {0x3820,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //std_pnl_core
    {0x3820,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       31},    //std_pnl_gain
    /*VPSS_TNR_MAME_MV_THD*/
    {0x3824,        25,     29,     2,      0,      HI_PQ_MODULE_TNR,       16},    //adj_xmv_max
    {0x3824,        20,     24,     2,      0,      HI_PQ_MODULE_TNR,       16},    //adj_0mv_max
    {0x3824,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       4},     //adj_xmv_min
    {0x3824,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       4},     //adj_0mv_min
    {0x3824,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       10},    //adj_mv_min
    {0x3824,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       31},    //adj_mv_max
    /*VPSS_TNR_MAMC_CBCR_UPEN*/
    {0x3828,        5,      8,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight2
    {0x3828,        1,      4,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight1
    {0x3828,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbcrupdateen
    /*VPSS_TNR_MAMC_CBCR_UPTHD1*/
    {0x382c,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crend1
    {0x382c,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cbend1
    {0x382c,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin1
    {0x382c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin1
    /*VPSS_TNR_MAMC_CBCR_UPTHD2*/
    {0x3830,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crend2
    {0x3830,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cbend2
    {0x3830,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin2
    {0x3830,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin2
    /*VPSS_TNR_MAMC_PRE_MAD*/
    {0x3834,        6,      10,     2,      0,      HI_PQ_MODULE_TNR,       16},    //motionmergeratio
    {0x3834,        1,      5,      2,      0,      HI_PQ_MODULE_TNR,       18},    //premotionalpha
    {0x3834,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //premotionmergemode
    /*VPSS_TNR_MAMC_MAP*/
    {0x3838,        17,     22,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncore
    {0x3838,        12,     16,     2,      0,      HI_PQ_MODULE_TNR,       24},    //cmotiongain
    {0x3838,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncore
    {0x3838,        1,      5,      2,      0,      HI_PQ_MODULE_TNR,       24},    //ymotiongain
    {0x3838,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //motionmappingen
    /*VPSS_TNR_MAMC_SALTUS*/
    {0x383c,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //saltusdecten
    {0x383c,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //saltusdecten
    /*VPSS_TNR_MAMC_MCADJ*/
    {0x3840,        4,      5,      2,      0,      HI_PQ_MODULE_TNR,       3},     //cmclpfmode
    {0x3840,        2,      3,      2,      0,      HI_PQ_MODULE_TNR,       3},     //ymclpfmode
    {0x3840,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       1},     //cmcadjen
    {0x3840,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //ymcadjen
    /*VPSS_TNR_FILR_MODE*/
    {0x3844,        7,      11,     2,      0,      HI_PQ_MODULE_TNR,       2},     //cnonrrange
    {0x3844,        2,      6,      2,      0,      HI_PQ_MODULE_TNR,       2},     //ynonrrange
    {0x3844,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotionmode
    {0x3844,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //ymotionmode
    /*VPSS_TNR_SCENE_CHANGE*/
    {0x3848,        1,      8,      2,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeinfo
    {0x3848,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //scenechangeen
    /*VPSS_TNR_CFG*/
    {0x384c,        17,     21,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_cmdcore
    {0x384c,        11,     16,     2,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_cmdgain
    {0x384c,        6,      10,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_ymdcore
    {0x384c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_ymdgain
    /*VPSS_TNR_FLAT_INFO*/
    {0x3850,        24,     31,     2,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymax
    {0x3850,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       56},    //flatinfoxmax
    {0x3850,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymin
    {0x3850,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       64},    //flatinfoxmin
    /*VPSS_TNR_YBLEND*/
    {0x385c,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //yblendingymax
    {0x385c,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       12},    //yblendingxmax
    {0x385c,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       16},    //yblendingymin
    {0x385c,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       0},     //yblendingxmin
    /*VPSS_TNR_CBLEND*/
    {0x3858,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //cblendingymax
    {0x3858,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       12},    //cblendingxmax
    {0x3858,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       16},    //cblendingymin
    {0x3858,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cblendingxmin
    /*VPSS_TNR_DTBLEND*/
    {0x385c,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //dtblendingymax
    {0x385c,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       15},    //dtblendingxmax
    {0x385c,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       12},    //dtblendingymin
    {0x385c,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       1},     //dtblendingxmin
    /*VPSS_TNR_MEAN_MOTION_LUT0*/
    {0x3900,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio3
    {0x3900,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio2
    {0x3900,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio1
    {0x3900,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio0
    /*VPSS_TNR_MEAN_MOTION_LUT1*/
    {0x3904,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio7
    {0x3904,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio6
    {0x3904,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio5
    {0x3904,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio4
    /*VPSS_TNR_MEAN_MOTION_LUT2*/
    {0x3908,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio11
    {0x3908,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio10
    {0x3908,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio9
    {0x3908,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio8
    /*VPSS_TNR_MEAN_MOTION_LUT3*/
    {0x390c,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio15
    {0x390c,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio14
    {0x390c,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio13
    {0x390c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio12

    /***********************************************ACC***********************************************/
    /*VHDACCTHD1*/
    {0x6700,       31,     31,     0,      0,      HI_PQ_MODULE_DCI,       1},     //acc_en
    {0x6700,       30,     30,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_mode
    {0x6700,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       280},   //thd_med_low
    {0x6700,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       620},   //thd_high
    {0x6700,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       400},   //thd_low
    /*VHDACCTHD2*/
    {0x6704,       20,     20,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_dbg_en
    {0x6704,       19,     19,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_dbg_mode
    {0x6704,       18,     18,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_rst
    {0x6704,       10,     17,     0,      0,      HI_PQ_MODULE_DCI,       14},    //acc_multiple
    {0x6704,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       740},   //thd_med_high
    /*VHDACCLOWN*/
    {0x6710,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       286},   //table_data31
    {0x6710,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       146},   //table_data21
    {0x6710,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //table_data11
    /*VHDACCLOWN*/
    {0x6714,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //table_data32
    {0x6714,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       550},   //table_data22
    {0x6714,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       426},   //table_data12
    /*VHDACCLOWN*/
    {0x6718,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //table_data32
    {0x6718,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       896},   //table_data23
    {0x6718,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       768},   //table_data13
    /*VHDACCMEDN*/
    {0x6720,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //table_data31
    {0x6720,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       110},    //table_data21
    {0x6720,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //table_data11
    /*VHDACCMEDN*/
    {0x6724,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //table_data32
    {0x6724,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       540},   //table_data22
    {0x6724,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       384},   //table_data12
    /*VHDACCMEDN*/
    {0x6728,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //table_data33
    {0x6728,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       880},   //table_data23
    {0x6728,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       800},   //table_data13
    /*VHDACCHIGHN*/
    {0x6730,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //table_data31
    {0x6730,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       100},   //table_data21
    {0x6730,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //table_data11
    /*VHDACCHIGHN*/
    {0x6734,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       620},   //table_data32
    {0x6734,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       496},   //table_data22
    {0x6734,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       360},   //table_data12
    /*VHDACCHIGHN*/
    {0x6738,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //table_data33
    {0x6738,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       864},   //table_data23
    {0x6738,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       764},   //table_data13
    /*VHDACCMLN*/
    {0x6740,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //table_data31
    {0x6740,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       110},    //table_data21
    {0x6740,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //table_data11
    /*VHDACCMLN*/
    {0x6744,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //table_data32
    {0x6744,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       540},   //table_data22
    {0x6744,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       384},   //table_data12
    /*VHDACCMLN*/
    {0x6748,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //table_data33
    {0x6748,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       880},   //table_data23
    {0x6748,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       800},   //table_data13
    /*VHDACCMHN*/
    {0x6750,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //table_data31
    {0x6750,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       110},    //table_data21
    {0x6750,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //table_data11
    /*VHDACCMHN*/
    {0x6754,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //table_data32
    {0x6754,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       540},   //table_data22
    {0x6754,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       384},   //table_data12
    /*VHDACCMHN*/
    {0x6758,       20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //table_data33
    {0x6758,       10,     19,     0,      0,      HI_PQ_MODULE_DCI,       880},   //table_data23
    {0x6758,       0,      9,      0,      0,      HI_PQ_MODULE_DCI,       800},   //table_data13

    /***********************************************ACM_CTRL***********************************************/
    /*VHDACM0*/
    {0x6450,       31,     31,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm3_en
    {0x6450,       30,     30,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm2_en
    {0x6450,       29,     29,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm1_en
    {0x6450,       28,     28,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm0_en
    {0x6450,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0x6450,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0x6450,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0x6450,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0x6450,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},   //acm_b_u_off
    {0x6450,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_u_off
    /*VHDACM1*/
    {0x6454,       22,     22,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //bw_pro_mode
    {0x6454,       21,     21,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_dbg_mode
    {0x6454,       20,     20,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_test_en
    {0x6454,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_v_off
    {0x6454,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0x6454,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_v_off
    {0x6454,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_v_off
    /*VHDACM2*/
    {0x6458,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0x6458,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0x6458,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_u_off
    {0x6458,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_u_off
    {0x6458,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_u_off
    {0x6458,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_u_off
    /*VHDACM3*/
    {0x645c,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0x645c,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0x645c,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_v_off
    {0x645c,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_v_off
    /*VHDACM4*/
    {0x6460,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0x6460,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0x6460,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0x6460,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0x6460,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_u_off
    {0x6460,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_u_off
    /*VHDACM5*/
    {0x6464,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0x6464,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0x6464,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_v_off
    {0x6464,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_v_off
    /*VHDACM6*/
    {0x6468,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0x6468,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0x6468,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0x6468,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0x6468,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_u_off
    {0x6468,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_u_off
    /*VHDACM7*/
    {0x646c,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0x646c,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0x646c,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_v_off
    {0x646c,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_v_off
    /***********************************************SHARPEN***********************************************/
    /*SD source*/
    /*SPCTRL*/
    {0x6200,    17,      17,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //ensctrl
    {0x6200,     4,      16,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_pos
    {0x6200,     2,       3,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_mode
    {0x6200,     1,       1,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //sharpen_en
    {0x6200,     0,       0,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //debug_en
    /*SPENABLE*/
    {0x6204,     4,       4,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_d
    {0x6204,     3,       3,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_v
    {0x6204,     2,       2,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_h
    {0x6204,     1,       1,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //detec_en
    {0x6204,     0,       0,        1,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //peak_en
    /*SPWINSIZEHVD*/
    {0x6208,     6,       8,        1,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_d
    {0x6208,     3,       5,        1,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_v
    {0x6208,     0,       2,        1,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_h
    /*SPTMPH1*/
    {0x620c,    16,      24,        1,      0,      HI_PQ_MODULE_SHARPNESS,  78},     //tmp2_h1
    {0x620c,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  61},     //tmp1_h1
    {0x620c,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  28},     //tmp0_h1
    /*SPTMPH2*/
    {0x6210,    16,      24,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //tmp2_h2
    {0x6210,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //tmp1_h2
    {0x6210,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS, -64},     //tmp0_h2
    /*SPTMPV1*/
    {0x6214,    16,      24,        1,      0,      HI_PQ_MODULE_SHARPNESS,  78},     //tmp2_v1
    {0x6214,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  61},     //tmp1_v1
    {0x6214,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  28},     //tmp0_v1
    /*SPTMPV2*/
    {0x6218,    16,      24,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //tmp2_v2
    {0x6218,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //tmp1_v2
    {0x6218,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS, -64},     //tmp0_v2
    /*SPGAIN*/
    {0x621c,    20,      27,        1,      0,      HI_PQ_MODULE_SHARPNESS,   8},     //dir_gain
    {0x621c,    10,      19,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //edge_gain
    {0x621c,     0,       9,        1,      0,      HI_PQ_MODULE_SHARPNESS, 256},     //peak_gain
    {0x6220,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  20},     //peak_coring
    /*SPPEAKSHOOTCTL*/
    {0x6224,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //peak_mixratio
    {0x6224,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //peak_under_thr
    {0x6224,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //peak_over_thr
    /*SPGAINPOS*/
    {0x6228,    18,      26,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_d
    {0x6228,     9,      17,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_v
    {0x6228,     0,       8,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_h
    /*SPGAINNEG*/
    {0x622c,    18,      26,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_d
    {0x622c,     9,      17,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_v
    {0x622c,     0,       8,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_h
    /*SPOVERTHR*/
    {0x6230,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_d
    {0x6230,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_v
    {0x6230,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_h
    /*SPUNDERTHR*/
    {0x6234,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_d
    {0x6234,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_v
    {0x6234,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_h
    /*SPMIXRATIO*/
    {0x6238,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_d
    {0x6238,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_v
    {0x6238,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_h
    /*SPCORINGZERO*/
    {0x623c,     6,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //coringzero_d
    {0x623c,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,   3},     //coringzero_v
    {0x623c,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,   3},     //coringzero_h
    /*SPCORINGRATIO*/
    {0x6240,    10,      14,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_d
    {0x6240,     5,       9,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_v
    {0x6240,     0,       4,        1,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_h
    /*SPCORINGTHR*/
    {0x6244,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_d
    {0x6244,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_v
    {0x6244,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_h
    /*SPLMTRATIO*/
    {0x6248,     6,       8,        1,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_d
    {0x6248,     3,       5,        1,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_v
    {0x6248,     0,       2,        1,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_h
    /*SPLMTPOS0*/
    {0x624c,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_d
    {0x624c,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_v
    {0x624c,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_h
    /*SPLMTPOS1*/
    {0x6250,    16,      23,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_d
    {0x6250,     8,      15,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_v
    {0x6250,     0,       7,        1,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_h
    /*SPBOUNDPOS*/
    {0x6254,    16,      23,        1,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_d
    {0x6254,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_v
    {0x6254,     0,       7,        1,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_h
    /*SPLMTNEG0*/
    {0x6258,    18,      26,        1,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_d
    {0x6258,     9,      17,        1,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_v
    {0x6258,     0,       8,        1,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_h
    /*SPLMTNEG1*/
    {0x625c,    18,      26,        1,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_d
    {0x625c,     9,      17,        1,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_v
    {0x625c,     0,       8,        1,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_h
    /*SPBOUNDNEG*/
    {0x6260,    18,      26,        1,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_d
    {0x6260,     9,      17,        1,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_v
    {0x6260,     0,       8,        1,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_h
    /*SPEDGESHOOTCTL*/
    {0x6264,    16,      23,        1,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //edge_mixratio
    {0x6264,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,   10},    //edge_under_thr
    {0x6264,     0,       7,        1,        0,    HI_PQ_MODULE_SHARPNESS,   10},    //edge_over_thr
    /*SPEDGETMPH*/
    {0x6268,    16,      24,        1,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //tmp2_sx
    {0x6268,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,    0},    //tmp1_sx
    {0x6268,     0,       7,        1,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //tmp0_sx
    /*SPEDGETMPV*/
    {0x626c,    16,      24,        1,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //tmp2_sy
    {0x626c,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,    0},    //tmp1_sy
    {0x626c,     0,       7,        1,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //tmp0_sy
    /*SPEDGEEI*/
    {0x6270,    16,      23,        1,        0,    HI_PQ_MODULE_SHARPNESS,    4},    //edge_eiratio
    {0x6270,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,  100},    //edge_ei1
    {0x6270,     0,       7,        1,        0,    HI_PQ_MODULE_SHARPNESS,   68},    //edge_ei0
    /*SPGRADMIN*/
    {0x6274,    20,      26,        1,        0,    HI_PQ_MODULE_SHARPNESS,    4},    //gradminslop
    {0x6274,    10,      19,        1,        0,    HI_PQ_MODULE_SHARPNESS,   40},    //gradminthrh
    {0x6274,     0,       9,        1,        0,    HI_PQ_MODULE_SHARPNESS,    8},    //gradminthrl
    /*SPGRADCTR*/
    {0x6278,    10,      25,        1,        0,    HI_PQ_MODULE_SHARPNESS, 1600},    //chessboardthr
    {0x6278,     0,       9,        1,        0,    HI_PQ_MODULE_SHARPNESS,   16},    //gradminthr
    /*SPSHOOTRATIO*/
    {0x627c,    21,      27,        1,        0,    HI_PQ_MODULE_SHARPNESS,  127},    //oshootratiot
    {0x627c,    14,      20,        1,        0,    HI_PQ_MODULE_SHARPNESS,  127},    //oshootratioe
    {0x627c,     7,      13,        1,        0,    HI_PQ_MODULE_SHARPNESS,  16},     //ushootratiot
    {0x627c,     0,       6,        1,        0,    HI_PQ_MODULE_SHARPNESS,  16},     //ushootratioe
    /*SPGRADCONTRAST*/
    {0x6280,     8,      15,        1,        0,    HI_PQ_MODULE_SHARPNESS,  64},     //gradcontrastthr
    {0x6280,     0,      7,         1,        0,    HI_PQ_MODULE_SHARPNESS,   4},     //gradcontrastslop

    /*HD source*/
    /*SPCTRL*/
    {0x6200,    17,      17,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //ensctrl
    {0x6200,     4,      16,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_pos
    {0x6200,     2,       3,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_mode
    {0x6200,     1,       1,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //sharpen_en
    {0x6200,     0,       0,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //debug_en
    /*SPENABLE*/
    {0x6204,     4,       4,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_d
    {0x6204,     3,       3,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_v
    {0x6204,     2,       2,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //hfreq_en_h
    {0x6204,     1,       1,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //detec_en
    {0x6204,     0,       0,        2,      0,      HI_PQ_MODULE_SHARPNESS,   1},     //peak_en
    /*SPWINSIZEHVD*/
    {0x6208,     6,       8,        2,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_d
    {0x6208,     3,       5,        2,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_v
    {0x6208,     0,       2,        2,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //winsize_h
    /*SPTMPH1*/
    {0x620c,    16,      24,        2,      0,      HI_PQ_MODULE_SHARPNESS,  78},     //tmp2_h1
    {0x620c,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  61},     //tmp1_h1
    {0x620c,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  28},     //tmp0_h1
    /*SPTMPH2*/
    {0x6210,    16,      24,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //tmp2_h2
    {0x6210,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //tmp1_h2
    {0x6210,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS, -64},     //tmp0_h2
    /*SPTMPV1*/
    {0x6214,    16,      24,        2,      0,      HI_PQ_MODULE_SHARPNESS,  78},     //tmp2_v1
    {0x6214,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  61},     //tmp1_v1
    {0x6214,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  28},     //tmp0_v1
    /*SPTMPV2*/
    {0x6218,    16,      24,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //tmp2_v2
    {0x6218,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //tmp1_v2
    {0x6218,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS, -64},     //tmp0_v2
    /*SPGAIN*/
    {0x621c,    20,      27,        2,      0,      HI_PQ_MODULE_SHARPNESS,   8},     //dir_gain
    {0x621c,    10,      19,        2,      0,      HI_PQ_MODULE_SHARPNESS,  128},     //edge_gain
    {0x621c,     0,       9,        2,      0,      HI_PQ_MODULE_SHARPNESS,  256},     //peak_gain
    {0x6220,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  20},     //peak_coring
    /*SPPEAKSHOOTCTL*/
    {0x6224,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //peak_mixratio
    {0x6224,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //peak_under_thr
    {0x6224,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //peak_over_thr
    /*SPGAINPOS*/
    {0x6228,    18,      26,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_d
    {0x6228,     9,      17,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_v
    {0x6228,     0,       8,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_pos_h
    /*SPGAINNEG*/
    {0x622c,    18,      26,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_d
    {0x622c,     9,      17,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_v
    {0x622c,     0,       8,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //gain_neg_h
    /*SPOVERTHR*/
    {0x6230,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_d
    {0x6230,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_v
    {0x6230,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //over_thr_h
    /*SPUNDERTHR*/
    {0x6234,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_d
    {0x6234,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_v
    {0x6234,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //under_thr_h
    /*SPMIXRATIO*/
    {0x6238,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_d
    {0x6238,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_v
    {0x6238,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  96},     //mixratio_h
    /*SPCORINGZERO*/
    {0x623c,     6,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,   2},     //coringzero_d
    {0x623c,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,   3},     //coringzero_v
    {0x623c,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,   3},     //coringzero_h
    /*SPCORINGRATIO*/
    {0x6240,    10,      14,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_d
    {0x6240,     5,       9,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_v
    {0x6240,     0,       4,        2,      0,      HI_PQ_MODULE_SHARPNESS,  15},     //coringratio_h
    /*SPCORINGTHR*/
    {0x6244,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_d
    {0x6244,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_v
    {0x6244,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,   7},     //coringthr_h
    /*SPLMTRATIO*/
    {0x6248,     6,       8,        2,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_d
    {0x6248,     3,       5,        2,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_v
    {0x6248,     0,       2,        2,      0,      HI_PQ_MODULE_SHARPNESS,   6},     //limit_ratio_h
    /*SPLMTPOS0*/
    {0x624c,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_d
    {0x624c,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_v
    {0x624c,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS,  64},     //limitpos0_h
    /*SPLMTPOS1*/
    {0x6250,    16,      23,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_d
    {0x6250,     8,      15,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_v
    {0x6250,     0,       7,        2,      0,      HI_PQ_MODULE_SHARPNESS, 128},     //limitpos1_h
    /*SPBOUNDPOS*/
    {0x6254,    16,      23,        2,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_d
    {0x6254,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_v
    {0x6254,     0,       7,        2,        0,    HI_PQ_MODULE_SHARPNESS,  112},    //boundpos_h
    /*SPLMTNEG0*/
    {0x6258,    18,      26,        2,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_d
    {0x6258,     9,      17,        2,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_v
    {0x6258,     0,       8,        2,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //limitneg0_h
    /*SPLMTNEG1*/
    {0x625c,    18,      26,        2,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_d
    {0x625c,     9,      17,        2,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_v
    {0x625c,     0,       8,        2,        0,    HI_PQ_MODULE_SHARPNESS, -128},    //limitneg1_h
    /*SPBOUNDNEG*/
    {0x6260,    18,      26,        2,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_d
    {0x6260,     9,      17,        2,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_v
    {0x6260,     0,       8,        2,        0,    HI_PQ_MODULE_SHARPNESS, -112},    //boundneg_h
    /*SPEDGESHOOTCTL*/
    {0x6264,    16,      23,        2,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //edge_mixratio
    {0x6264,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,   10},    //edge_under_thr
    {0x6264,     0,       7,        2,        0,    HI_PQ_MODULE_SHARPNESS,   10},    //edge_over_thr
    /*SPEDGETMPH*/
    {0x6268,    16,      24,        2,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //tmp2_sx
    {0x6268,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,    0},    //tmp1_sx
    {0x6268,     0,       7,        2,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //tmp0_sx
    /*SPEDGETMPV*/
    {0x626c,    16,      24,        2,        0,    HI_PQ_MODULE_SHARPNESS,  128},    //tmp2_sy
    {0x626c,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,    0},    //tmp1_sy
    {0x626c,     0,       7,        2,        0,    HI_PQ_MODULE_SHARPNESS,  -64},    //tmp0_sy
    /*SPEDGEEI*/
    {0x6270,    16,      23,        2,        0,    HI_PQ_MODULE_SHARPNESS,    4},    //edge_eiratio
    {0x6270,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,  100},    //edge_ei1
    {0x6270,     0,       7,        2,        0,    HI_PQ_MODULE_SHARPNESS,   68},    //edge_ei0
    /*SPGRADMIN*/
    {0x6274,    20,      26,        2,        0,    HI_PQ_MODULE_SHARPNESS,    4},    //gradminslop
    {0x6274,    10,      19,        2,        0,    HI_PQ_MODULE_SHARPNESS,   40},    //gradminthrh
    {0x6274,     0,       9,        2,        0,    HI_PQ_MODULE_SHARPNESS,    8},    //gradminthrl
    /*SPGRADCTR*/
    {0x6278,    10,      25,        2,        0,    HI_PQ_MODULE_SHARPNESS, 1600},    //chessboardthr
    {0x6278,     0,       9,        2,        0,    HI_PQ_MODULE_SHARPNESS,   16},    //gradminthr
    /*SPSHOOTRATIO*/
    {0x627c,    21,      27,        2,        0,    HI_PQ_MODULE_SHARPNESS,  127},    //oshootratiot
    {0x627c,    14,      20,        2,        0,    HI_PQ_MODULE_SHARPNESS,  127},    //oshootratioe
    {0x627c,     7,      13,        2,        0,    HI_PQ_MODULE_SHARPNESS,  16},     //ushootratiot
    {0x627c,     0,       6,        2,        0,    HI_PQ_MODULE_SHARPNESS,  16},     //ushootratioe
    /*SPGRADCONTRAST*/
    {0x6280,     8,      15,        2,        0,    HI_PQ_MODULE_SHARPNESS,  64},     //gradcontrastthr
    {0x6280,     0,      7,         2,        0,    HI_PQ_MODULE_SHARPNESS,   4},     //gradcontrastslop

    {0x621c,    10,      19,        0,      4,      HI_PQ_MODULE_SHARPNESS, 256},     //edge_gain
    {0x621c,     0,       9,        0,      4,      HI_PQ_MODULE_SHARPNESS, 400},     //peak_gain
    {0x621c,    10,      19,        0,      5,      HI_PQ_MODULE_SHARPNESS, 256},     //edge_gain
    {0x621c,     0,       9,        0,      5,      HI_PQ_MODULE_SHARPNESS, 400},     //peak_gain
    {0x621c,    10,      19,        1,      2,      HI_PQ_MODULE_SHARPNESS, 176},     //edge_gain
    {0x621c,     0,       9,        1,      2,      HI_PQ_MODULE_SHARPNESS, 352},     //peak_gain
    {0x621c,    10,      19,        1,      3,      HI_PQ_MODULE_SHARPNESS, 256},     //edge_gain
    {0x621c,     0,       9,        1,      3,      HI_PQ_MODULE_SHARPNESS, 512},     //peak_gain
    /************************************* ZME DS *****************************************/
    /* SHOOTCTRL_HL */
    {0x08f8,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_shootctrl_en
    {0x08f8,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //hl_shootctrl_mode
    {0x08f8,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_flatdect_mode
    {0x08f8,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_coringadj_en
    {0x08f8,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_gain
    {0x08f8,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_coring
    /* SHOOTCTRL_VL */
    {0x0900,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_shootctrl_en
    {0x0900,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //vl_shootctrl_mode
    {0x0900,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_flatdect_mode
    {0x0900,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_coringadj_en
    {0x0900,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_gain
    {0x0900,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_coring

    /* ZME2 DS */
    /* SHOOTCTRL_HL */
    {0xbaf8,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_shootctrl_en
    {0xbaf8,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //hl_shootctrl_mode
    {0xbaf8,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_flatdect_mode
    {0xbaf8,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_coringadj_en
    {0xbaf8,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_gain
    {0xbaf8,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_coring
    /* SHOOTCTRL_VL */
    {0xbb00,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_shootctrl_en
    {0xbb00,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //vl_shootctrl_mode
    {0xbb00,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_flatdect_mode
    {0xbb00,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_coringadj_en
    {0xbb00,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_gain
    {0xbb00,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_coring

};

static PQ_PHY_REG_S sg_stPQSoftReg[SOFT_REG_MAX] =
{
    /***************************************************************************
      * Special Register
     ***************************************************************************/

    /*Addr                                   Lsb       Msb    SourceMode  OutputMode   Module     Value        Description*/
    /***********************************************FMD_CTRL***********************************************/
    /*IP_DETECT*/
    {PQ_SOFT_IP_DETECT,         0,       1,        0,        0,     HI_PQ_MODULE_FMD,       0},       //ip_detect_choice
    {PQ_SOFT_FRMRATETHR_L,      0,      15,        0,        0,     HI_PQ_MODULE_FMD,   23800},       //g_u32FrmRateThr_L
    {PQ_SOFT_FRMRATETHR_H,      0,      15,        0,        0,     HI_PQ_MODULE_FMD,   24200},       //g_u32FrmRateThr_H

    /*HDR_SATU*/
    {PQ_SOFT_HDR_SATU,          0,       0,        0,        0,     HI_PQ_MODULE_HDR,      50},       //hdr_saturation

    /*COLOR_TEMP*/
    {PQ_SOFT_COLOR_TEMP_R,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp red
    {PQ_SOFT_COLOR_TEMP_G,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp green
    {PQ_SOFT_COLOR_TEMP_B,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp blue

    /*MODULE_ON_OR_OFF*/
    {PQ_SOFT_MODULE_FMD_SD,     0,       0,        0,        0,     HI_PQ_MODULE_FMD,       1},       //fmd sd on/off
    {PQ_SOFT_MODULE_FMD_HD,     0,       0,        0,        0,     HI_PQ_MODULE_FMD,       1},       //fmd hd on/off
    {PQ_SOFT_MODULE_FMD_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_FMD,       1},       //fmd uhd on/off
    {PQ_SOFT_MODULE_TNR_SD,     0,       0,        0,        0,     HI_PQ_MODULE_TNR,       1},       //tnr sd on/off
    {PQ_SOFT_MODULE_TNR_HD,     0,       0,        0,        0,     HI_PQ_MODULE_TNR,       1},       //tnr hd on/off
    {PQ_SOFT_MODULE_TNR_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_TNR,       0},       //tnr uhd on/off
    {PQ_SOFT_MODULE_SNR_SD,     0,       0,        0,        0,     HI_PQ_MODULE_SNR,       1},       //snr sd on/off
    {PQ_SOFT_MODULE_SNR_HD,     0,       0,        0,        0,     HI_PQ_MODULE_SNR,       1},       //snr hd on/off
    {PQ_SOFT_MODULE_SNR_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_SNR,       0},       //snr uhd on/off
    {PQ_SOFT_MODULE_VDP4KSNR_SD,         0,        0,        0,        0,     HI_PQ_MODULE_VDP4KSNR,     0},       //vdp4ksnr sd on/off
    {PQ_SOFT_MODULE_VDP4KSNR_FHD,        0,        0,        0,        0,     HI_PQ_MODULE_VDP4KSNR,     0},       //vdp4ksnr hd on/off
    {PQ_SOFT_MODULE_VDP4KSNR_UHD,        0,        0,        0,        0,     HI_PQ_MODULE_VDP4KSNR,     1},       //vdp4ksnr uhd on/off
    {PQ_SOFT_MODULE_DB_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DB,        1},       //db sd on/off
    {PQ_SOFT_MODULE_DB_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DB,        1},       //db hd on/off
    {PQ_SOFT_MODULE_DB_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DB,        0},       //db uhd on/off
    {PQ_SOFT_MODULE_DR_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DR,        1},       //dr sd on/off
    {PQ_SOFT_MODULE_DR_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DR,        1},       //dr hd on/off
    {PQ_SOFT_MODULE_DR_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DR,        1},       //dr uhd on/off
    {PQ_SOFT_MODULE_DM_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DM,        1},       //dm sd on/off
    {PQ_SOFT_MODULE_DM_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DM,        1},       //dm hd on/off
    {PQ_SOFT_MODULE_DM_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DM,        0},       //dm uhd on/off
    {PQ_SOFT_MODULE_SHARPN_SD,  0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 1},       //sharp sd on/off
    {PQ_SOFT_MODULE_SHARPN_HD,  0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 1},       //sharphd on/off
    {PQ_SOFT_MODULE_SHARPN_UHD, 0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 0},       //sharp uhd on/off
    {PQ_SOFT_MODULE_DCI_SD,     0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci sd on/off
    {PQ_SOFT_MODULE_DCI_HD,     0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci hd on/off
    {PQ_SOFT_MODULE_DCI_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci uhd on/off
    {PQ_SOFT_MODULE_ACM_SD,     0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm sd on/off
    {PQ_SOFT_MODULE_ACM_HD,     0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm hd on/off
    {PQ_SOFT_MODULE_ACM_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm uhd on/off
    {PQ_SOFT_MODULE_CSC_SD,     0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc sd on/off
    {PQ_SOFT_MODULE_CSC_HD,     0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc hd on/off
    {PQ_SOFT_MODULE_CSC_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc uhd on/off
    {PQ_SOFT_MODULE_DS_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd sd on/off
    {PQ_SOFT_MODULE_DS_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd hd on/off
    {PQ_SOFT_MODULE_DS_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd uhd on/off
};


PQ_PHY_REG_S *PQ_TABLE_GetPhyRegDefault(HI_VOID)
{
    return sg_stPhyRegDefault;
}

PQ_PHY_REG_S *PQ_TABLE_GetSoftRegDefault(HI_VOID)
{
    return sg_stPQSoftReg;
}

