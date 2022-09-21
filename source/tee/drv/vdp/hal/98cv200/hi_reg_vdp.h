//******************************************************************************
// Copyright     :  Copyright (C) 2015, Hisilicon Technologies Co., Ltd.
// File name     :  hi_reg_vdp.h
// Author        :  xxx
// Version       :  1.0
// Date          :  2015-08-14
// Description   :  Define all registers/tables for vdp
// Others        :  Generated automatically by nManager V4.0
// History       :  xxx 2015-08-14 Create file
//******************************************************************************

#ifndef __HI_REG_VDP_H__
#define __HI_REG_VDP_H__

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

typedef struct
{
    unsigned int    u32;
}S_VDP_SEC_OUTPUT_CTRL;

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
        unsigned int    reserved_2            : 1   ; /* [25]  */
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

/* Define the union U_HDR_CTRL */
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

} U_HDR_CTRL;

/* Define the union U_VP0_IRESO */
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
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
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


/* Define the union U_DHD0_CTRL */
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


/* Define the union U_DHD0_SRSEL */
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


/* Define the union U_DATE_COEFF0 */
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

/* Define the union U_DATE_DACDET2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_pixel_sta         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 4   ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_DACDET2;


//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_VOCTRL               VOCTRL                   ; /* 0x0 */
    volatile unsigned int           reserved_a[9]           ; /* 0x4~0x24 */
    volatile U_VOMIDORDER           VOMIDORDER               ; /* 0x28 */
    volatile unsigned int           reserved_b               ; /* 0x2c */
    volatile U_VOAXICTRL            VOAXICTRL                ; /* 0x30 */
    volatile U_VOAXICTRL1           VOAXICTRL1               ; /* 0x34 */
    volatile U_VOMASTERSEL          VOMASTERSEL              ; /* 0x38 */
    volatile U_VOMASTERSEL1         VOMASTERSEL1             ; /* 0x3c */
    volatile unsigned int           reserved_13[496]                     ; /* 0x40~0x7fc */
    volatile U_V0_CTRL              V0_CTRL                           ; /* 0x800 */
    volatile unsigned int           reserved_14[25]                  ; /* 0x804~0x864 */
    volatile U_V0_VFPOS             V0_VFPOS                          ; /* 0x868 */
    volatile U_V0_VLPOS             V0_VLPOS                          ; /* 0x86c */
    volatile unsigned int           reserved_62[104]                 ; /* 0x86c~0xa0c */
    volatile U_V0_P0VFPOS           V0_P0VFPOS                        ; /* 0xa10 */
    volatile U_V0_P0VLPOS           V0_P0VLPOS                        ; /* 0xa14 */
    volatile unsigned int           reserved_62_1[3418]                 ; /* 0xa18~0x3f7c */
    volatile U_HDR_CTRL             HDR_CTRL                          ; /* 0x3f80 */
    volatile unsigned int           reserved_62_2[2081]               ; /* 0x3f84~0x6004 */
    volatile U_VP0_IRESO            VP0_IRESO                         ; /* 0x6008 */
    volatile unsigned int           reserved_134[5117]                 ; /* 0xa8f8~0xaffc */
    volatile U_MIXV0_BKG            MIXV0_BKG                         ; /* 0xb000 */
    volatile unsigned int           reserved_135                     ; /* 0xb004 */
    volatile U_MIXV0_MIX            MIXV0_MIX                         ; /* 0xb008 */
    volatile unsigned int           reserved_136[125]                     ; /* 0xb00c~0xb1fc */
    volatile U_MIXG0_BKG            MIXG0_BKG                         ; /* 0xb200 */
    volatile U_MIXG0_BKALPHA        MIXG0_BKALPHA                     ; /* 0xb204 */
    volatile U_MIXG0_MIX            MIXG0_MIX                         ; /* 0xb208 */
    volatile unsigned int           reserved_137[125]                 ; /* 0xb20c~0xb3fc */
    volatile U_CBM_BKG1             CBM_BKG1                          ; /* 0xb400 */
    volatile unsigned int           reserved_138_0                     ; /* 0xb404 */
    volatile U_CBM_MIX1             CBM_MIX1                          ; /* 0xb408 */
    volatile unsigned int           reserved_139[61]                  ; /* 0xb40c~0xb4fc */
    volatile U_CBM_BKG2             CBM_BKG2                          ; /* 0xb500 */
    volatile unsigned int           reserved_141                     ; /* 0xb504 */
    volatile U_CBM_MIX2             CBM_MIX2                          ; /* 0xb508 */
    volatile unsigned int           reserved_143_0[61]                  ; /* 0xb50c~0xb5fc */
    volatile U_CBM_BKG3             CBM_BKG3                          ; /* 0xb600 */
    volatile unsigned int           reserved_144_0                      ; /* 0xb604 */
    volatile U_CBM_MIX3             CBM_MIX3                          ; /* 0xb608 */
    volatile unsigned int           reserved_143[381]                 ;/* 0xb60c ~0xbbfc*/
    volatile U_V0_DWM_CTRL          V0_DWM_CTRL                       ; /* 0xbc00 */
    volatile U_V0_DWM_SYB_SCL       V0_DWM_SYB_SCL                    ; /* 0xbc04 */
    volatile U_V0_DWM_SYB_ORESO     V0_DWM_SYB_ORESO                  ; /* 0xbc08 */
    volatile U_V0_DWM_SYB_FPOS      V0_DWM_SYB_FPOS                   ; /* 0xbc0c */
    volatile U_V0_DWM_SYB_LPOS      V0_DWM_SYB_LPOS                   ; /* 0xbc10 */
    volatile U_V0_DWM_SYB_NUM       V0_DWM_SYB_NUM                    ; /* 0xbc14 */
    volatile U_V0_DWM_SYB_SPAC      V0_DWM_SYB_SPAC                   ; /* 0xbc18 */
    volatile U_V0_DWM_LFRE_DISTANCE   V0_DWM_LFRE_DISTANCE            ; /* 0xbc1c */
    volatile U_V0_DWM_RFRE_DISTANCE   V0_DWM_RFRE_DISTANCE            ; /* 0xbc20 */
    volatile U_V0_DWM_TFRE_DISTANCE   V0_DWM_TFRE_DISTANCE            ; /* 0xbc24 */
    volatile U_V0_DWM_FRE_NUM       V0_DWM_FRE_NUM                    ; /* 0xbc28 */
    volatile unsigned int           reserved_138                      ; /* 0xbc2c */
    volatile U_V0_DWM_STRENGH       V0_DWM_STRENGH                    ; /* 0xbc30 */
    volatile U_V0_DWM_SYB_STRIDE    V0_DWM_SYB_STRIDE                 ; /* 0xbc34 */
    volatile U_V0_DWM_SYB_PARA_ADDR   V0_DWM_SYB_PARA_ADDR            ; /* 0xbc38 */
    volatile U_V0_DWM_SYB_PARAUP    V0_DWM_SYB_PARAUP                 ; /* 0xbc3c */
    volatile U_V0_DWM_STR_THD0      V0_DWM_STR_THD0                   ; /* 0xbc40 */
    volatile unsigned int           reserved_144[23]                  ; /* 0xbc3c ~0xbc9c*/
    volatile U_V0_DWM_BGSTR_THD0    V0_DWM_BGSTR_THD0                 ; /* 0xbca0 */
    volatile unsigned int           reserved_153[215]                 ; /* 0xbca4~0xbffc */
    volatile U_DHD0_CTRL            DHD0_CTRL                         ; /* 0xc000 */
    volatile unsigned int           reserved_154[9]                    ; /* 0xc004~0xc024 */
    volatile U_DHD0_SRSEL           DHD0_SRSEL                        ; /* 0xc028 */
    volatile unsigned int           reserved_170_0[885]                  ; /* 0xccc0~0xcdfc */
    volatile U_DATE_COEFF0          DATE_COEFF0                       ; /* 0xce00 */
    volatile unsigned int           reserved_170[2508]                  ; /* 0xccc0~0xcdfc */
} S_VDP_REGS_TYPE;
//extern S_VDP_REGS_TYPE *pVdpReg;

#endif /* __HI_REG_VDP_H__ */
