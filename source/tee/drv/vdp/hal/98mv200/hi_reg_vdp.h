//******************************************************************************
// Copyright     :  Copyright (C) 2016, Hisilicon Technologies Co., Ltd.
// File name     :  c_union_define.h
// Author        :  xxx
// Version       :  1.0
// Date          :  2016-05-06
// Description   :  Define all registers/tables for vdp
// Others        :  Generated automatically by nManager V4.0
// History       :  xxx 2016-05-06 Create file
//******************************************************************************

#ifndef __C_UNION_DEFINE_H__
#define __C_UNION_DEFINE_H__

/* Define the union U_VOCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m0_arb_mode           : 4   ; /* [3..0]  */
        unsigned int    m1_arb_mode           : 4   ; /* [7..4]  */
        unsigned int    m2_arb_mode           : 4   ; /* [11..8]  */
        unsigned int    m3_arb_mode           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 6   ; /* [21..16]  */
        unsigned int    grc_arb_mode          : 2   ; /* [23..22]  */
        unsigned int    twochn_en             : 1   ; /* [24]  */
        unsigned int    twochn_mode           : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    g3_sel                : 1   ; /* [29]  */
        unsigned int    chk_sum_en            : 1   ; /* [30]  */
        unsigned int    vo_ck_gt_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOCTRL;

/* Define the union U_VOMIDORDER */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_mode             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    mid_enable            : 1   ; /* [3]  */
        unsigned int    reserved_1            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMIDORDER;


typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m0_outstd_rid0        : 4   ; /* [3..0]  */
        unsigned int    m0_outstd_rid1        : 4   ; /* [7..4]  */
        unsigned int    m0_wr_ostd            : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 3   ; /* [14..12]  */
        unsigned int    m0_mutli_id_o         : 1   ; /* [15]  */
        unsigned int    m1_outstd_rid0        : 4   ; /* [19..16]  */
        unsigned int    m1_outstd_rid1        : 4   ; /* [23..20]  */
        unsigned int    m1_wr_ostd            : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    m1_mutli_id_o         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOAXICTRL;

/* Define the union U_VOAXICTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    m2_outstd_rid0        : 4   ; /* [3..0]  */
        unsigned int    m2_outstd_rid1        : 4   ; /* [7..4]  */
        unsigned int    m2_wr_ostd            : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    m3_outstd_rid0        : 4   ; /* [19..16]  */
        unsigned int    m3_outstd_rid1        : 4   ; /* [23..20]  */
        unsigned int    m3_wr_ostd            : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOAXICTRL1;

/* Define the union U_VOMASTERSEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_master_sel         : 1   ; /* [0]  */
        unsigned int    v1_master_sel         : 1   ; /* [1]  */
        unsigned int    v2_master_sel         : 1   ; /* [2]  */
        unsigned int    v3_master_sel         : 1   ; /* [3]  */
        unsigned int    v4_master_sel         : 1   ; /* [4]  */
        unsigned int    v5_master_sel         : 1   ; /* [5]  */
        unsigned int    v6_master_sel         : 1   ; /* [6]  */
        unsigned int    v7_master_sel         : 1   ; /* [7]  */
        unsigned int    v8_master_sel         : 1   ; /* [8]  */
        unsigned int    v9_master_sel         : 1   ; /* [9]  */
        unsigned int    vhd_str_master_sel    : 1   ; /* [10]  */
        unsigned int    vhd_stw_master_sel    : 1   ; /* [11]  */
        unsigned int    vad_str_master_sel    : 1   ; /* [12]  */
        unsigned int    vad_stw_master_sel    : 1   ; /* [13]  */
        unsigned int    g0_master_sel         : 1   ; /* [14]  */
        unsigned int    g1_master_sel         : 1   ; /* [15]  */
        unsigned int    g2_master_sel         : 1   ; /* [16]  */
        unsigned int    g3_master_sel         : 1   ; /* [17]  */
        unsigned int    g4_master_sel         : 1   ; /* [18]  */
        unsigned int    g5_master_sel         : 1   ; /* [19]  */
        unsigned int    g6_master_sel         : 1   ; /* [20]  */
        unsigned int    g7_master_sel         : 1   ; /* [21]  */
        unsigned int    wbc0_master_sel       : 1   ; /* [22]  */
        unsigned int    wbc1_master_sel       : 1   ; /* [23]  */
        unsigned int    wbc2_master_sel       : 1   ; /* [24]  */
        unsigned int    wbc3_master_sel       : 1   ; /* [25]  */
        unsigned int    wbc4_master_sel       : 1   ; /* [26]  */
        unsigned int    wbc5_master_sel       : 1   ; /* [27]  */
        unsigned int    wbc6_master_sel       : 1   ; /* [28]  */
        unsigned int    wbc7_master_sel       : 1   ; /* [29]  */
        unsigned int    para_master_sel       : 1   ; /* [30]  */
        unsigned int    sddate_master_sel     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMASTERSEL;

/* Define the union U_VOMASTERSEL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_master_sel         : 1   ; /* [0]  */
        unsigned int    v1_master_sel         : 1   ; /* [1]  */
        unsigned int    v2_master_sel         : 1   ; /* [2]  */
        unsigned int    v3_master_sel         : 1   ; /* [3]  */
        unsigned int    v4_master_sel         : 1   ; /* [4]  */
        unsigned int    v5_master_sel         : 1   ; /* [5]  */
        unsigned int    v6_master_sel         : 1   ; /* [6]  */
        unsigned int    v7_master_sel         : 1   ; /* [7]  */
        unsigned int    v8_master_sel         : 1   ; /* [8]  */
        unsigned int    v9_master_sel         : 1   ; /* [9]  */
        unsigned int    vhd_str_master_sel    : 1   ; /* [10]  */
        unsigned int    vhd_stw_master_sel    : 1   ; /* [11]  */
        unsigned int    vad_str_master_sel    : 1   ; /* [12]  */
        unsigned int    vad_stw_master_sel    : 1   ; /* [13]  */
        unsigned int    g0_master_sel         : 1   ; /* [14]  */
        unsigned int    g1_master_sel         : 1   ; /* [15]  */
        unsigned int    g2_master_sel         : 1   ; /* [16]  */
        unsigned int    g3_master_sel         : 1   ; /* [17]  */
        unsigned int    g4_master_sel         : 1   ; /* [18]  */
        unsigned int    g5_master_sel         : 1   ; /* [19]  */
        unsigned int    g6_master_sel         : 1   ; /* [20]  */
        unsigned int    g7_master_sel         : 1   ; /* [21]  */
        unsigned int    wbc0_master_sel       : 1   ; /* [22]  */
        unsigned int    wbc1_master_sel       : 1   ; /* [23]  */
        unsigned int    wbc2_master_sel       : 1   ; /* [24]  */
        unsigned int    wbc3_master_sel       : 1   ; /* [25]  */
        unsigned int    wbc4_master_sel       : 1   ; /* [26]  */
        unsigned int    wbc5_master_sel       : 1   ; /* [27]  */
        unsigned int    wbc6_master_sel       : 1   ; /* [28]  */
        unsigned int    wbc7_master_sel       : 1   ; /* [29]  */
        unsigned int    para_master_sel       : 1   ; /* [30]  */
        unsigned int    sddate_master_sel     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMASTERSEL1;

/* Define the union U_V0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ifmt                  : 4   ; /* [3..0]  */
        unsigned int    vicap_abnm_en         : 1   ; /* [4]  */
        unsigned int    req_ctrl              : 3   ; /* [7..5]  */
        unsigned int    dcmp_en               : 1   ; /* [8]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    nosec_flag            : 1   ; /* [10]  */
        unsigned int    uv_order              : 1   ; /* [11]  */
        unsigned int    chm_rmode             : 2   ; /* [13..12]  */
        unsigned int    lm_rmode              : 2   ; /* [15..14]  */
        unsigned int    reserved_1            : 1   ; /* [16]  */
        unsigned int    vup_mode              : 1   ; /* [17]  */
        unsigned int    ifir_mode             : 2   ; /* [19..18]  */
        unsigned int    ofl_master            : 1   ; /* [20]  */
        unsigned int    es_en                 : 1   ; /* [21]  */
        unsigned int    fi_vscale             : 1   ; /* [22]  */
        unsigned int    chroma_copy           : 1   ; /* [23]  */
        unsigned int    twodt3d_en            : 1   ; /* [24]  */
        unsigned int    test_pattern_en       : 1   ; /* [25]  */
        unsigned int    flip_en               : 1   ; /* [26]  */
        unsigned int    mute_en               : 1   ; /* [27]  */
        unsigned int    data_width            : 2   ; /* [29..28]  */
        unsigned int    surface_c_en          : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CTRL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VFPOS;

/* Define the union U_V0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VLPOS;

/* Define the union U_V0_P0VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0VFPOS;

/* Define the union U_V0_P0VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_P0VLPOS;

/* Define the union U_DB_HDR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 30  ; /* [29..0]  */
        unsigned int    edr_en                : 1   ; /* [30]  */
        unsigned int    hdr_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DB_HDR_CTRL;


typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 12  ; /* [11..0]  */
        unsigned int    ih                    : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_IRESO;

/* Define the union U_MIXV0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_BKG;

/* Define the union U_MIXV0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_MIX;

/* Define the union U_MIXG0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKG;

/* Define the union U_MIXG0_BKALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_alpha           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKALPHA;

/* Define the union U_MIXG0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    mixer_prio2           : 4   ; /* [11..8]  */
        unsigned int    mixer_prio3           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_MIX;

/* Define the union U_MIXG0_MIX_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    layer0_premulti       : 1   ; /* [0]  */
        unsigned int    layer0_bypass_en      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 13  ; /* [14..2]  */
        unsigned int    mix1_bypass_mode      : 1   ; /* [15]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_MIX_BYPASS;

/* Define the union U_CBM_BKG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr1            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb1            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy1             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG1;

/* Define the union U_CBM_MIX1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX1;

/* Define the union U_WBC_BMP_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_bmp_thd           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_BMP_THD;

/* Define the union U_CBM_BKG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr2            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb2            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy2             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG2;

/* Define the union U_CBM_MIX2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX2;

/* Define the union U_HC_BMP_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_bmp_thd            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HC_BMP_THD;

/* Define the union U_CBM_BKG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr3            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb3            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy3             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG3;

/* Define the union U_CBM_MIX3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    mixer_prio2           : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX3;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 28  ; /* [27..0]  */
        unsigned int    para_clr              : 1   ; /* [28]  */
        unsigned int    nosec_flag            : 1   ; /* [29]  */
        unsigned int    bg_embd_en            : 1   ; /* [30]  */
        unsigned int    dwm_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_CTRL;

/* Define the union U_V0_DWM_SYB_SCL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scale                 : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_SCL;

/* Define the union U_V0_DWM_SYB_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    width                 : 12  ; /* [11..0]  */
        unsigned int    height                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_ORESO;

/* Define the union U_V0_DWM_SYB_FPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    syb_xfpos             : 12  ; /* [11..0]  */
        unsigned int    syb_yfpos             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_FPOS;

/* Define the union U_V0_DWM_SYB_LPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    syb_xlpos             : 12  ; /* [11..0]  */
        unsigned int    syb_ylpos             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_LPOS;

/* Define the union U_V0_DWM_SYB_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    syb_hor_num           : 4   ; /* [3..0]  */
        unsigned int    syb_ver_num           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_NUM;

/* Define the union U_V0_DWM_SYB_SPAC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    syb_hor_spac          : 12  ; /* [11..0]  */
        unsigned int    syb_ver_spac          : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_SPAC;

/* Define the union U_V0_DWM_LFRE_DISTANCE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dirction_0            : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dirction_1            : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    dirction_2            : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_LFRE_DISTANCE;

/* Define the union U_V0_DWM_RFRE_DISTANCE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dirction_0            : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dirction_1            : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    dirction_2            : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_RFRE_DISTANCE;

/* Define the union U_V0_DWM_TFRE_DISTANCE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dirction_0            : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dirction_1            : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    dirction_2            : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_TFRE_DISTANCE;

/* Define the union U_V0_DWM_FRE_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frequency_pix         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    frequency_line        : 6   ; /* [17..12]  */
        unsigned int    reserved_1            : 2   ; /* [19..18]  */
        unsigned int    frequency_spac        : 8   ; /* [27..20]  */
        unsigned int    reserved_2            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_FRE_NUM;

/* Define the union U_V0_DWM_SYB_PARA_RD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_rdata_0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DWM_SYB_PARA_RD;
/* Define the union U_V0_DWM_STRENGH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    direction_max         : 12  ; /* [11..0]  */
        unsigned int    strengh_multiply      : 8   ; /* [19..12]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_STRENGH;

/* Define the union U_V0_DWM_SYB_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sub_stride            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_STRIDE;

/* Define the union U_V0_DWM_SYB_PARA_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_DWM_SYB_PARA_ADDR;
/* Define the union U_V0_DWM_SYB_PARAUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_up               : 1   ; /* [0]  */
        unsigned int    reserved_0            : 7   ; /* [7..1]  */
        unsigned int    para_rdata_1          : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_SYB_PARAUP;

/* Define the union U_V0_DWM_STR_THD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    strengh_0             : 16  ; /* [15..0]  */
        unsigned int    strengh_1             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_STR_THD0;


/* Define the union U_V0_DWM_BGSTR_THD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    strengh_0             : 16  ; /* [15..0]  */
        unsigned int    strengh_1             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DWM_BGSTR_THD0;


typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    disp_mode             : 3   ; /* [3..1]  */
        unsigned int    iop                   : 1   ; /* [4]  */
        unsigned int    intf_ivs              : 1   ; /* [5]  */
        unsigned int    intf_ihs              : 1   ; /* [6]  */
        unsigned int    intf_idv              : 1   ; /* [7]  */
        unsigned int    reserved_0            : 1   ; /* [8]  */
        unsigned int    hdmi420c_sel          : 1   ; /* [9]  */
        unsigned int    hdmi420_en            : 1   ; /* [10]  */
        unsigned int    uf_offline_en         : 1   ; /* [11]  */
        unsigned int    gmm_mode              : 1   ; /* [12]  */
        unsigned int    gmm_en                : 1   ; /* [13]  */
        unsigned int    hdmi_mode             : 1   ; /* [14]  */
        unsigned int    twochn_debug          : 1   ; /* [15]  */
        unsigned int    reserved_1            : 1   ; /* [16]  */
        unsigned int    mirror_en             : 1   ; /* [17]  */
        unsigned int    sin_en                : 1   ; /* [18]  */
        unsigned int    trigger_en            : 1   ; /* [19]  */
        unsigned int    fpga_lmt_width        : 7   ; /* [26..20]  */
        unsigned int    fpga_lmt_en           : 1   ; /* [27]  */
        unsigned int    p2i_en                : 1   ; /* [28]  */
        unsigned int    cbar_sel              : 1   ; /* [29]  */
        unsigned int    cbar_en               : 1   ; /* [30]  */
        unsigned int    intf_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CTRL;

/* Define the union U_DHD0_VSYNC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vact                  : 12  ; /* [11..0]  */
        unsigned int    vbb                   : 10  ; /* [21..12]  */
        unsigned int    vfb                   : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VSYNC;

/* Define the union U_DHD0_HSYNC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hact                  : 16  ; /* [15..0]  */
        unsigned int    hbb                   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HSYNC1;
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sr_sel                : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_SRSEL;

/* Define the union U_HDATE_VBI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgmsb_add_en          : 1   ; /* [0]  */
        unsigned int    cgmsa_add_en          : 1   ; /* [1]  */
        unsigned int    mv_en                 : 1   ; /* [2]  */
        unsigned int    vbi_lpf_en            : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_VBI_CTRL;

/* Define the union U_HDATE_CGMSA_DATA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cgmsa_data            : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CGMSA_DATA;

/* Define the union U_HDATE_CGMSB_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdate_cgmsb_h         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDATE_CGMSB_H;

/* Define the union U_HDATE_CGMSB_DATA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA1;
/* Define the union U_HDATE_CGMSB_DATA2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data2            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA2;
/* Define the union U_HDATE_CGMSB_DATA3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data3            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA3;
/* Define the union U_HDATE_CGMSB_DATA4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cgmsb_data4            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HDATE_CGMSB_DATA4;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_seq                : 1   ; /* [0]  */
        unsigned int    chgain_en             : 1   ; /* [1]  */
        unsigned int    sylp_en               : 1   ; /* [2]  */
        unsigned int    chlp_en               : 1   ; /* [3]  */
        unsigned int    oversam2_en           : 1   ; /* [4]  */
        unsigned int    lunt_en               : 1   ; /* [5]  */
        unsigned int    oversam_en            : 2   ; /* [7..6]  */
        unsigned int    reserved_0            : 1   ; /* [8]  */
        unsigned int    luma_dl               : 4   ; /* [12..9]  */
        unsigned int    agc_amp_sel           : 1   ; /* [13]  */
        unsigned int    length_sel            : 1   ; /* [14]  */
        unsigned int    sync_mode_scart       : 1   ; /* [15]  */
        unsigned int    sync_mode_sel         : 2   ; /* [17..16]  */
        unsigned int    style_sel             : 4   ; /* [21..18]  */
        unsigned int    fm_sel                : 1   ; /* [22]  */
        unsigned int    vbi_lpf_en            : 1   ; /* [23]  */
        unsigned int    rgb_en                : 1   ; /* [24]  */
        unsigned int    scanline              : 1   ; /* [25]  */
        unsigned int    pbpr_lpf_en           : 1   ; /* [26]  */
        unsigned int    pal_half_en           : 1   ; /* [27]  */
        unsigned int    reserved_1            : 1   ; /* [28]  */
        unsigned int    dis_ire               : 1   ; /* [29]  */
        unsigned int    clpf_sel              : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF0;

/* Define the union U_DATE_COEFF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac_test              : 10  ; /* [9..0]  */
        unsigned int    date_test_mode        : 2   ; /* [11..10]  */
        unsigned int    date_test_en          : 1   ; /* [12]  */
        unsigned int    amp_outside           : 10  ; /* [22..13]  */
        unsigned int    c_limit_en            : 1   ; /* [23]  */
        unsigned int    cc_seq                : 1   ; /* [24]  */
        unsigned int    cgms_seq              : 1   ; /* [25]  */
        unsigned int    vps_seq               : 1   ; /* [26]  */
        unsigned int    wss_seq               : 1   ; /* [27]  */
        unsigned int    cvbs_limit_en         : 1   ; /* [28]  */
        unsigned int    c_gain                : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF1;

/* Define the union U_DATE_COEFF2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef02                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF2;
/* Define the union U_DATE_COEFF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef03                : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF3;

/* Define the union U_DATE_COEFF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef04                : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF4;

/* Define the union U_DATE_COEFF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef05                : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF5;

/* Define the union U_DATE_COEFF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef06_1              : 23  ; /* [22..0]  */
        unsigned int    reserved_0            : 8   ; /* [30..23]  */
        unsigned int    coef06_0              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF6;

/* Define the union U_DATE_COEFF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt07_enf2             : 1   ; /* [0]  */
        unsigned int    tt08_enf2             : 1   ; /* [1]  */
        unsigned int    tt09_enf2             : 1   ; /* [2]  */
        unsigned int    tt10_enf2             : 1   ; /* [3]  */
        unsigned int    tt11_enf2             : 1   ; /* [4]  */
        unsigned int    tt12_enf2             : 1   ; /* [5]  */
        unsigned int    tt13_enf2             : 1   ; /* [6]  */
        unsigned int    tt14_enf2             : 1   ; /* [7]  */
        unsigned int    tt15_enf2             : 1   ; /* [8]  */
        unsigned int    tt16_enf2             : 1   ; /* [9]  */
        unsigned int    tt17_enf2             : 1   ; /* [10]  */
        unsigned int    tt18_enf2             : 1   ; /* [11]  */
        unsigned int    tt19_enf2             : 1   ; /* [12]  */
        unsigned int    tt20_enf2             : 1   ; /* [13]  */
        unsigned int    tt21_enf2             : 1   ; /* [14]  */
        unsigned int    tt22_enf2             : 1   ; /* [15]  */
        unsigned int    tt07_enf1             : 1   ; /* [16]  */
        unsigned int    tt08_enf1             : 1   ; /* [17]  */
        unsigned int    tt09_enf1             : 1   ; /* [18]  */
        unsigned int    tt10_enf1             : 1   ; /* [19]  */
        unsigned int    tt11_enf1             : 1   ; /* [20]  */
        unsigned int    tt12_enf1             : 1   ; /* [21]  */
        unsigned int    tt13_enf1             : 1   ; /* [22]  */
        unsigned int    tt14_enf1             : 1   ; /* [23]  */
        unsigned int    tt15_enf1             : 1   ; /* [24]  */
        unsigned int    tt16_enf1             : 1   ; /* [25]  */
        unsigned int    tt17_enf1             : 1   ; /* [26]  */
        unsigned int    tt18_enf1             : 1   ; /* [27]  */
        unsigned int    tt19_enf1             : 1   ; /* [28]  */
        unsigned int    tt20_enf1             : 1   ; /* [29]  */
        unsigned int    tt21_enf1             : 1   ; /* [30]  */
        unsigned int    tt22_enf1             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF7;

/* Define the union U_DATE_COEFF8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_staddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF8;
/* Define the union U_DATE_COEFF9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_edaddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF9;
/* Define the union U_DATE_COEFF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_pktoff             : 8   ; /* [7..0]  */
        unsigned int    tt_mode               : 2   ; /* [9..8]  */
        unsigned int    tt_highest            : 1   ; /* [10]  */
        unsigned int    full_page             : 1   ; /* [11]  */
        unsigned int    nabts_100ire          : 1   ; /* [12]  */
        unsigned int    reserved_0            : 18  ; /* [30..13]  */
        unsigned int    tt_ready              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF10;

/* Define the union U_DATE_COEFF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    date_clf2             : 10  ; /* [9..0]  */
        unsigned int    date_clf1             : 10  ; /* [19..10]  */
        unsigned int    cc_enf2               : 1   ; /* [20]  */
        unsigned int    cc_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF11;

/* Define the union U_DATE_COEFF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cc_f2data             : 16  ; /* [15..0]  */
        unsigned int    cc_f1data             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF12;

/* Define the union U_DATE_COEFF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f1data             : 20  ; /* [19..0]  */
        unsigned int    cg_enf2               : 1   ; /* [20]  */
        unsigned int    cg_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF13;

/* Define the union U_DATE_COEFF14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f2data             : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF14;

/* Define the union U_DATE_COEFF15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wss_data              : 14  ; /* [13..0]  */
        unsigned int    wss_en                : 1   ; /* [14]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF15;

/* Define the union U_DATE_COEFF16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 24  ; /* [23..0]  */
        unsigned int    vps_en                : 1   ; /* [24]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF16;

/* Define the union U_DATE_COEFF17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF17;
/* Define the union U_DATE_COEFF18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF18;
/* Define the union U_DATE_COEFF19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF19;

/* Define the union U_DATE_COEFF20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt05_enf2             : 1   ; /* [0]  */
        unsigned int    tt06_enf2             : 1   ; /* [1]  */
        unsigned int    tt06_enf1             : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF20;

/* Define the union U_DATE_COEFF21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_in_sel           : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_in_sel           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_in_sel           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_in_sel           : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_in_sel           : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_in_sel           : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF21;

/* Define the union U_DATE_COEFF22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_phase_delta     : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF22;

/* Define the union U_DATE_COEFF23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_out_dly          : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_out_dly          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_out_dly          : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_out_dly          : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_out_dly          : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_out_dly          : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF23;

/* Define the union U_DATE_COEFF24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int burst_start            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF24;
/* Define the union U_DATE_COEFF25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_coef              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    x_n_1_coef            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF25;

/* Define the union U_DATE_COEFF26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_1_coef            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF26;

/* Define the union U_DATE_COEFF27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_n_coef              : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    y_n_1_coef            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF27;

/* Define the union U_DATE_COEFF28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_begin1          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    pixel_begin2          : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF28;

/* Define the union U_DATE_COEFF29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_end             : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF29;

/* Define the union U_DATE_COEFF30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_secam               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF30;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd1_lcd_trustzone_ctrl     : 1   ; /* [0]  */
        unsigned int    dhd1_hdmi_trustzone_ctrl    : 1   ; /* [1]  */
        unsigned int    dhd1_vga_trustzone_ctrl     : 1   ; /* [2]  */
        unsigned int    dhd1_ypbpr_trustzone_ctrl   : 1   ; /* [3]  */
        unsigned int    dhd1_cvbs_trustzone_ctrl    : 1   ; /* [4]  */
        unsigned int    dhd0_lcd_trustzone_ctrl     : 1   ; /* [5]  */
        unsigned int    dhd0_hdmi_trustzone_ctrl    : 1   ; /* [6]  */
        unsigned int    dhd0_vga_trustzone_ctrl     : 1   ; /* [7]  */
        unsigned int    dhd0_ypbpr_trustzone_ctrl   : 1   ; /* [8]  */
        unsigned int    dhd0_cvbs_trustzone_ctrl    : 1   ; /* [9]  */
        unsigned int    gb0_trustzone_ctrl          : 1   ; /* [10]  */
        unsigned int    ga3_trustzone_ctrl          : 1   ; /* [11]  */
        unsigned int    ga2_trustzone_ctrl          : 1   ; /* [12]  */
        unsigned int    ga1_trustzone_ctrl          : 1   ; /* [13]  */
        unsigned int    ga0_trustzone_ctrl          : 1   ; /* [14]  */
        unsigned int    v4_trustzone_ctrl           : 1   ; /* [15]  */
        unsigned int    v3_trustzone_ctrl           : 1   ; /* [16]  */
        unsigned int    v1_trustzone_ctrl           : 1   ; /* [17]  */
        unsigned int    v0_trustzone_ctrl           : 1   ; /* [18]  */
        unsigned int    reserved                    : 13  ; /* [19..31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} U_SEC_OUTPUT_CTRL;


typedef struct
{
    U_SEC_OUTPUT_CTRL   SEC_OUTPUT_CTRL;
}S_VDP_SEC_OUTPUT_CTRL;

/* Define the union U_V0_NXG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_rate            : 8   ; /* [7..0]  */
        unsigned int    frame_type            : 2   ; /* [9..8]  */
        unsigned int    reserved_0            : 17  ; /* [26..10]  */
        unsigned int    rgb_fmt               : 1   ; /* [27]  */
        unsigned int    wm_3d_eye             : 1   ; /* [28]  */
        unsigned int    wm_3d_en              : 1   ; /* [29]  */
        unsigned int    debug_en              : 1   ; /* [30]  */
        unsigned int    dwm_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_NXG_CTRL;

/* Define the union U_V0_NXG_KEYIN */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int keyin                  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_KEYIN;
/* Define the union U_V0_NXG_PAYLOAD0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int payload_0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_PAYLOAD0;
/* Define the union U_V0_NXG_PAYLOAD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    payload_1             : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_NXG_PAYLOAD1;

/* Define the union U_V0_NXG_SETTING0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int setting_0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_SETTING0;
/* Define the union U_V0_NXG_SETTING1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int setting_1              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_SETTING1;
/* Define the union U_V0_NXG_SETTING2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int setting_2              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_SETTING2;
/* Define the union U_V0_NXG_SETTING3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int setting_3              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_SETTING3;
/* Define the union U_V0_NXG_SETTING4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int setting_4              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_NXG_SETTING4;
/* Define the union U_V0_NXG_SETTING5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    setting_5             : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_NXG_SETTING5;

/* Define the union U_V0_NXG_FPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 12  ; /* [11..0]  */
        unsigned int    video_yfpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_NXG_FPOS;

/* Define the union U_V0_NXG_LPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 12  ; /* [11..0]  */
        unsigned int    video_ylpos           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_NXG_LPOS;


//==============================================================================
/* Define the global struct */
typedef struct
{
    U_VOCTRL               VOCTRL                            ; /* 0x0 */
    unsigned int           reserved_10[9]                  ; /* 0x4~0x24 */
    U_VOMIDORDER           VOMIDORDER                        ; /* 0x28 */
    unsigned int           reserved_10_0                       ; /* 0x2c */
    U_VOAXICTRL            VOAXICTRL                         ; /* 0x30 */
    U_VOAXICTRL1           VOAXICTRL1                        ; /* 0x34 */
    U_VOMASTERSEL          VOMASTERSEL                       ; /* 0x38 */
    U_VOMASTERSEL1         VOMASTERSEL1                      ; /* 0x3c */
    unsigned int           reserved_13[496]                     ; /* 0x40~0x7fc */
    U_V0_CTRL              V0_CTRL                           ; /* 0x800 */
    unsigned int           reserved_13_1[25]                     ; /* 0x804~0x864 */
    U_V0_VFPOS             V0_VFPOS                          ; /* 0x868 */
    U_V0_VLPOS             V0_VLPOS                          ; /* 0x86c */
    unsigned int           reserved_74_0[104]                 ; /* 0x870~0xa0c */
    U_V0_P0VFPOS           V0_P0VFPOS                        ; /* 0xa10 */
    U_V0_P0VLPOS           V0_P0VLPOS                        ; /* 0xa14 */
    unsigned int           reserved_74[4442]                     ; /* 0xa18~0x4f7c */
    U_DB_HDR_CTRL          DB_HDR_CTRL                       ; /* 0x4f80 */
    unsigned int           reserved_81_0[1057]                   ; /* 0x4f84 ~0x6004 */
    U_VP0_IRESO            VP0_IRESO                         ; /* 0x6008 */
    unsigned int           reserved_81[5117]                 ; /* 0x600c ~0xaffc */
    U_MIXV0_BKG            MIXV0_BKG                         ; /* 0xb000 */
    unsigned int           reserved_162                     ; /* 0xb004 */
    U_MIXV0_MIX            MIXV0_MIX                         ; /* 0xb008 */
    unsigned int           reserved_163[125]                     ; /* 0xb00c~0xb1fc */
    U_MIXG0_BKG            MIXG0_BKG                         ; /* 0xb200 */
    U_MIXG0_BKALPHA        MIXG0_BKALPHA                     ; /* 0xb204 */
    U_MIXG0_MIX            MIXG0_MIX                         ; /* 0xb208 */
    U_MIXG0_MIX_BYPASS     MIXG0_MIX_BYPASS                  ; /* 0xb20c */
    unsigned int           reserved_164[124]                     ; /* 0xb210~0xb3fc */
    U_CBM_BKG1             CBM_BKG1                          ; /* 0xb400 */
    unsigned int           reserved_165                     ; /* 0xb404 */
    U_CBM_MIX1             CBM_MIX1                          ; /* 0xb408 */
    unsigned int           reserved_166[14]                     ; /* 0xb40c~0xb440 */
    U_WBC_BMP_THD          WBC_BMP_THD                       ; /* 0xb444 */
    unsigned int           reserved_167[46]                     ; /* 0xb448~0xb4fc */
    U_CBM_BKG2             CBM_BKG2                          ; /* 0xb500 */
    unsigned int           reserved_168                     ; /* 0xb504 */
    U_CBM_MIX2             CBM_MIX2                          ; /* 0xb508 */
    unsigned int           reserved_169[14]                     ; /* 0xb50c~0xb540 */
    U_HC_BMP_THD           HC_BMP_THD                        ; /* 0xb544 */
    unsigned int           reserved_170[46]                     ; /* 0xb548~0xb5fc */
    U_CBM_BKG3             CBM_BKG3                          ; /* 0xb600 */
    unsigned int           reserved_171                     ; /* 0xb604 */
    U_CBM_MIX3             CBM_MIX3                          ; /* 0xb608 */
    unsigned int           reserved_172[381]                     ; /* 0xb60c~0xbbfc */
    U_V0_DWM_CTRL          V0_DWM_CTRL                       ; /* 0xbc00 */
    U_V0_DWM_SYB_SCL       V0_DWM_SYB_SCL                    ; /* 0xbc04 */
    U_V0_DWM_SYB_ORESO     V0_DWM_SYB_ORESO                  ; /* 0xbc08 */
    U_V0_DWM_SYB_FPOS      V0_DWM_SYB_FPOS                   ; /* 0xbc0c */
    U_V0_DWM_SYB_LPOS      V0_DWM_SYB_LPOS                   ; /* 0xbc10 */
    U_V0_DWM_SYB_NUM       V0_DWM_SYB_NUM                    ; /* 0xbc14 */
    U_V0_DWM_SYB_SPAC      V0_DWM_SYB_SPAC                   ; /* 0xbc18 */
    U_V0_DWM_LFRE_DISTANCE   V0_DWM_LFRE_DISTANCE            ; /* 0xbc1c */
    U_V0_DWM_RFRE_DISTANCE   V0_DWM_RFRE_DISTANCE            ; /* 0xbc20 */
    U_V0_DWM_TFRE_DISTANCE   V0_DWM_TFRE_DISTANCE            ; /* 0xbc24 */
    U_V0_DWM_FRE_NUM       V0_DWM_FRE_NUM                    ; /* 0xbc28 */
    U_V0_DWM_SYB_PARA_RD   V0_DWM_SYB_PARA_RD                ; /* 0xbc2c */
    U_V0_DWM_STRENGH       V0_DWM_STRENGH                    ; /* 0xbc30 */
    U_V0_DWM_SYB_STRIDE    V0_DWM_SYB_STRIDE                 ; /* 0xbc34 */
    U_V0_DWM_SYB_PARA_ADDR   V0_DWM_SYB_PARA_ADDR            ; /* 0xbc38 */
    U_V0_DWM_SYB_PARAUP    V0_DWM_SYB_PARAUP                 ; /* 0xbc3c */
    U_V0_DWM_STR_THD0      V0_DWM_STR_THD0                   ; /* 0xbc40 */
    unsigned int           reserved_181[23]                  ; /*0xbc44~0xbc9c */
    U_V0_DWM_BGSTR_THD0    V0_DWM_BGSTR_THD0                 ; /* 0xbca0 */
    unsigned int           reserved_181_0[215]               ; /* 0xbca4~0xbffc */
    U_DHD0_CTRL            DHD0_CTRL                         ; /* 0xc000 */
    U_DHD0_VSYNC           DHD0_VSYNC                        ; /* 0xc004 */
    U_DHD0_HSYNC1          DHD0_HSYNC1                       ; /* 0xc008 */
    unsigned int           reserved_181_1[7]                  ; /* 0xc004~0xc024 */
    U_DHD0_SRSEL           DHD0_SRSEL                        ; /* 0xc028 */
    unsigned int           reserved_182[213]                 ; /* 0xc02c~0xcdfc */
	
    U_V0_NXG_CTRL          V0_NXG_CTRL                       ; /* 0xc380 */
    U_V0_NXG_KEYIN         V0_NXG_KEYIN                      ; /* 0xc384 */
    U_V0_NXG_PAYLOAD0      V0_NXG_PAYLOAD0                   ; /* 0xc388 */
    U_V0_NXG_PAYLOAD1      V0_NXG_PAYLOAD1                   ; /* 0xc38c */
    U_V0_NXG_SETTING0      V0_NXG_SETTING0                   ; /* 0xc390 */
    U_V0_NXG_SETTING1      V0_NXG_SETTING1                   ; /* 0xc394 */
    U_V0_NXG_SETTING2      V0_NXG_SETTING2                   ; /* 0xc398 */
    U_V0_NXG_SETTING3      V0_NXG_SETTING3                   ; /* 0xc39c */
    U_V0_NXG_SETTING4      V0_NXG_SETTING4                   ; /* 0xc3a0 */
    U_V0_NXG_SETTING5      V0_NXG_SETTING5                   ; /* 0xc3a4 */
    U_V0_NXG_FPOS          V0_NXG_FPOS                       ; /* 0xc3a8 */
    U_V0_NXG_LPOS          V0_NXG_LPOS                       ; /* 0xc3ac */
	
	unsigned int           reserved_182_1[573]               ;
	U_HDATE_VBI_CTRL       HDATE_VBI_CTRL                    ; /* 0xcca4 */
    U_HDATE_CGMSA_DATA     HDATE_CGMSA_DATA                  ; /* 0xcca8 */
    U_HDATE_CGMSB_H        HDATE_CGMSB_H                     ; /* 0xccac */
    U_HDATE_CGMSB_DATA1    HDATE_CGMSB_DATA1                 ; /* 0xccb0 */
    U_HDATE_CGMSB_DATA2    HDATE_CGMSB_DATA2                 ; /* 0xccb4 */
    U_HDATE_CGMSB_DATA3    HDATE_CGMSB_DATA3                 ; /* 0xccb8 */
    U_HDATE_CGMSB_DATA4    HDATE_CGMSB_DATA4                 ; /* 0xccbc */
	
    unsigned int           reserved_183[80]                 ; /* 0xc3b0~0xcdfc */
    U_DATE_COEFF0          DATE_COEFF0                       ; /* 0xce00 */
    U_DATE_COEFF1          DATE_COEFF1                       ; /* 0xce04 */
    U_DATE_COEFF2          DATE_COEFF2                       ; /* 0xce08 */
    U_DATE_COEFF3          DATE_COEFF3                       ; /* 0xce0c */
    U_DATE_COEFF4          DATE_COEFF4                       ; /* 0xce10 */
    U_DATE_COEFF5          DATE_COEFF5                       ; /* 0xce14 */
    U_DATE_COEFF6          DATE_COEFF6                       ; /* 0xce18 */
    U_DATE_COEFF7          DATE_COEFF7                       ; /* 0xce1c */
    U_DATE_COEFF8          DATE_COEFF8                       ; /* 0xce20 */
    U_DATE_COEFF9          DATE_COEFF9                       ; /* 0xce24 */
    U_DATE_COEFF10         DATE_COEFF10                      ; /* 0xce28 */
    U_DATE_COEFF11         DATE_COEFF11                      ; /* 0xce2c */
    U_DATE_COEFF12         DATE_COEFF12                      ; /* 0xce30 */
    U_DATE_COEFF13         DATE_COEFF13                      ; /* 0xce34 */
    U_DATE_COEFF14         DATE_COEFF14                      ; /* 0xce38 */
    U_DATE_COEFF15         DATE_COEFF15                      ; /* 0xce3c */
    U_DATE_COEFF16         DATE_COEFF16                      ; /* 0xce40 */
    U_DATE_COEFF17         DATE_COEFF17                      ; /* 0xce44 */
    U_DATE_COEFF18         DATE_COEFF18                      ; /* 0xce48 */
    U_DATE_COEFF19         DATE_COEFF19                      ; /* 0xce4c */
    U_DATE_COEFF20         DATE_COEFF20                      ; /* 0xce50 */
    U_DATE_COEFF21         DATE_COEFF21                      ; /* 0xce54 */
    U_DATE_COEFF22         DATE_COEFF22                      ; /* 0xce58 */
    U_DATE_COEFF23         DATE_COEFF23                      ; /* 0xce5c */
    U_DATE_COEFF24         DATE_COEFF24                      ; /* 0xce60 */
    U_DATE_COEFF25         DATE_COEFF25                      ; /* 0xce64 */
    U_DATE_COEFF26         DATE_COEFF26                      ; /* 0xce68 */
    U_DATE_COEFF27         DATE_COEFF27                      ; /* 0xce6c */
    U_DATE_COEFF28         DATE_COEFF28                      ; /* 0xce70 */
    U_DATE_COEFF29         DATE_COEFF29                      ; /* 0xce74 */
    U_DATE_COEFF30         DATE_COEFF30                      ; /* 0xce78 */
    unsigned int           reserved_197[2478]                ; /* 0xce04~0xf530 */

} S_VDP_REGS_TYPE;

/* Declare the struct pointor of the module VDP */
extern S_VDP_REGS_TYPE *gopVDPAllReg;


#endif /* __C_UNION_DEFINE_H__ */
