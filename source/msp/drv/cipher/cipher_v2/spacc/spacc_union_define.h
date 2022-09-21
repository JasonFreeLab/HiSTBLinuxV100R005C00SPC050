/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : spacc_union_define.h
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/

#ifndef __SPACC_UNION_DEFINE_H__
#define __SPACC_UNION_DEFINE_H__

/* Define the union U_HDCP_MODE_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdcp_mode_en          : 1   ; /* [0]  */
        unsigned int    hdcp_rootkey_sel      : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    hdmi_tx_hdcp14_wr_en  : 1   ; /* [4]  */
        unsigned int    hdmi_rx_hdcp14_wr_en  : 1   ; /* [5]  */
        unsigned int    hdmi_rx_hdcp22_wr_en  : 1   ; /* [6]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    hdcp_wr_sel           : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HDCP_MODE_CTRL;

/* Define the union U_SEC_CHN_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cipher_sec_chn_cfg    : 8   ; /* [7..0]  */
        unsigned int    cipher_sec_chn_cfg_lock : 1   ; /* [8]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    hash_sec_chn_cfg      : 8   ; /* [23..16]  */
        unsigned int    hash_sec_chn_cfg_lock : 1   ; /* [24]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SEC_CHN_CFG;

/* Define the union U_MEM_EMA_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_ema               : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    rfs_emaw              : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    rft_emaa              : 3   ; /* [10..8]  */
        unsigned int    rft_emab              : 3   ; /* [13..11]  */
        unsigned int    rft_emasa             : 1   ; /* [14]  */
        unsigned int    rft_colldisn          : 1   ; /* [15]  */
        unsigned int    reserved_2            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MEM_EMA_CFG;

/* Define the union U_KEY_ST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_req_cur_st        : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_KEY_ST;

/* Define the union U_CALC_ST0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cipher_calc_cur_st    : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    hash_calc_cur_st      : 4   ; /* [11..8]  */
        unsigned int    hdcp_key_ksv_crc4     : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CALC_ST0;

/* Define the union U_CALC_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    klad_key_use_err      : 1   ; /* [0]  */
        unsigned int    alg_len_err           : 1   ; /* [1]  */
        unsigned int    smmu_page_unvlid      : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CALC_ERR;

/* Define the union U_CHANN_HASH_STATE_VAL_ADDR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hash_state_val_addr   : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_HASH_STATE_VAL_ADDR;

/* Define the union U_CHAN0_CIPHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sym_ch0_start         : 1   ; /* [0]  */
        unsigned int    sym_ch0_alg_mode      : 3   ; /* [3..1]  */
        unsigned int    sym_ch0_alg_sel       : 3   ; /* [6..4]  */
        unsigned int    sym_ch0_decrypt       : 1   ; /* [7]  */
        unsigned int    sym_ch0_dat_width     : 2   ; /* [9..8]  */
        unsigned int    sym_ch0_key_length    : 2   ; /* [11..10]  */
        unsigned int    sym_ch0_ccm_gcm_input_flag : 2   ; /* [13..12]  */
        unsigned int    sym_ch0_key_sel       : 1   ; /* [14]  */
        unsigned int    sym_ch0_ivin_sel      : 1   ; /* [15]  */
        unsigned int    reserved_0            : 2   ; /* [17..16]  */
        unsigned int    sym_ch0_sm1_round_num : 2   ; /* [19..18]  */
        unsigned int    sym_ch0_gcm_iv_len    : 4   ; /* [23..20]  */
        unsigned int    sym_ch0_ccm_gcm_pc_last : 1   ; /* [24]  */
        unsigned int    sym_ccm_gcm_last_block  : 4   ;/* [28..25]  */
        unsigned int    reserved_1            : 3   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHAN0_CIPHER_CTRL;

/* Define the union U_CIPHER_INT_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    cipher_chn_ibuf_int   : 7   ; /* [7..1]  */
        unsigned int    cipher_chn_obuf_int   : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CIPHER_INT_STATUS;

/* Define the union U_CIPHER_INT_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    cipher_chn_ibuf_en    : 7   ; /* [7..1]  */
        unsigned int    cipher_chn_obuf_en    : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 14  ; /* [29..16]  */
        unsigned int    cipher_sec_int_en     : 1   ; /* [30]  */
        unsigned int    cipher_nsec_int_en    : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CIPHER_INT_EN;

/* Define the union U_CIPHER_INT_RAW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    cipher_chn_ibuf_raw   : 7   ; /* [7..1]  */
        unsigned int    cipher_chn_obuf_raw   : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CIPHER_INT_RAW;

/* Define the union U_CIPHER_IN_SMMU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cipher_in_chan_rd_dat_smmu_en : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    cipher_in_chan_rd_node_smmu_en : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CIPHER_IN_SMMU_EN;

/* Define the union U_OUT_SMMU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_chan_wr_dat_smmu_en : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    out_chan_rd_node_smmu_en : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_OUT_SMMU_EN;

/* Define the union U_IN_ST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hash_in_ctrl_cur_st   : 5   ; /* [4..0]  */
        unsigned int    sym_in_ctrl_cur_st    : 3   ; /* [7..5]  */
        unsigned int    sym_hash_req_cur_st   : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_IN_ST;

/* Define the union U_OUT_ST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_cur_st            : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_OUT_ST;

/* Define the union U_CHANN_CIPHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    sym_chn_alg_mode      : 3   ; /* [3..1]  */
        unsigned int    sym_chn_alg_sel       : 3   ; /* [6..4]  */
        unsigned int    sym_chn_decrypt       : 1   ; /* [7]  */
        unsigned int    sym_chn_dat_width     : 2   ; /* [9..8]  */
        unsigned int    sym_chn_key_length    : 2   ; /* [11..10]  */
        unsigned int    reserved_1            : 2   ; /* [13..12]  */
        unsigned int    sym_chn_key_sel       : 1   ; /* [14]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    sym_chn_dout_byte_swap_en : 1   ; /* [16]  */
        unsigned int    sym_chn_din_byte_swap_en : 1   ; /* [17]  */
        unsigned int    sym_chn_sm1_round_num : 2   ; /* [19..18]  */
        unsigned int    reserved_3            : 2   ; /* [21..20]  */
        unsigned int    weight                : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_CIPHER_CTRL;

/* Define the union U_CHANN_CIPHER_IN_NODE_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cipher_in_node_mpackage_int_level : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    cipher_in_node_rptr   : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    cipher_in_node_wptr   : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    cipher_in_node_total_num : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_CIPHER_IN_NODE_CFG;

/* Define the union U_CHANN_CIPHER_IN_LEFT_BYTE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    in_left_byte0         : 24  ; /* [23..0]  */
        unsigned int    in_byte_cnt           : 2   ; /* [25..24]  */
        unsigned int    in_word_cnt           : 2   ; /* [27..26]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_CIPHER_IN_LEFT_BYTE;

/* Define the union U_CHANN_CIPHER_OUT_NODE_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cipher_out_node_mpackage_int_level : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    cipher_out_node_rptr  : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    cipher_out_node_wptr  : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    cipher_out_node_total_num : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_CIPHER_OUT_NODE_CFG;

/* Define the union U_CHANN_CIPHER_OUT_LEFT_BYTE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_left_byte0        : 24  ; /* [23..0]  */
        unsigned int    out_byte_cnt          : 2   ; /* [25..24]  */
        unsigned int    out_word_cnt          : 2   ; /* [27..26]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_CIPHER_OUT_LEFT_BYTE;

/* Define the union U_CHAN0_HASH_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hash_ch0_start        : 1   ; /* [0]  */
        unsigned int    hash_ch0_agl_sel      : 3   ; /* [3..1]  */
        unsigned int    hash_ch0_hmac_calc_step : 1   ; /* [4]  */
        unsigned int    hash_ch0_mode         : 1   ; /* [5]  */
        unsigned int    hash_ch0_key_sel      : 1   ; /* [6]  */
        unsigned int    reserved_0            : 2   ; /* [8..7]  */
        unsigned int    hash_ch0_auto_padding_en : 1   ; /* [9]  */
        unsigned int    hash_ch0_hmac_key_addr : 3   ; /* [12..10]  */
        unsigned int    hash_ch0_used          : 1   ; /* [13]  */
        unsigned int    hash_ch0_sec_alarm     : 1   ; /* [13]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHAN0_HASH_CTRL;

/* Define the union U_HASH_INT_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    hash_ch0_oram_int     : 1   ; /* [18]  */
        unsigned int    hash_ch1_oram_int     : 1   ; /* [19]  */
        unsigned int    hash_ch2_oram_int     : 1   ; /* [20]  */
        unsigned int    hash_ch3_oram_int     : 1   ; /* [21]  */
        unsigned int    hash_ch4_oram_int     : 1   ; /* [22]  */
        unsigned int    hash_ch5_oram_int     : 1   ; /* [23]  */
        unsigned int    hash_ch6_oram_int     : 1   ; /* [24]  */
        unsigned int    hash_ch7_oram_int     : 1   ; /* [25]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HASH_INT_STATUS;

/* Define the union U_HASH_INT_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    hash_chn_oram_en      : 8   ; /* [25..18]  */
        unsigned int    reserved_1            : 4   ; /* [29..26]  */
        unsigned int    hash_sec_int_en       : 1   ; /* [30]  */
        unsigned int    hash_int_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HASH_INT_EN;

/* Define the union U_HASH_INT_RAW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    hash_chn_oram_raw     : 8   ; /* [25..18]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HASH_INT_RAW;

/* Define the union U_HASH_IN_SMMU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hash_in_chan_rd_dat_smmu_en : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 9   ; /* [15..7]  */
        unsigned int    hash_in_chan_rd_node_smmu_en : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HASH_IN_SMMU_EN;

/* Define the union U_CHANN_HASH_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    hash_chn_agl_sel      : 3   ; /* [3..1]  */
        unsigned int    reserved_1            : 1   ; /* [4]  */
        unsigned int    hash_chn_mode         : 1   ; /* [5]  */
        unsigned int    hash_chn_key_sel      : 1   ; /* [6]  */
        unsigned int    hash_chn_dat_in_byte_swap_en : 1   ; /* [7]  */
        unsigned int    hash_chn_dat_in_bit_swap_en : 1   ; /* [8]  */
        unsigned int    hash_chn_auto_padding_en : 1   ; /* [9]  */
        unsigned int    hash_chn_hmac_key_addr : 3   ; /* [12..10]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_HASH_CTRL;

/* Define the union U_CHANN_HASH_IN_NODE_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hash_in_node_mpackage_int_level : 8   ; /* [7..0]  */
        unsigned int    hash_in_node_rptr     : 8   ; /* [15..8]  */
        unsigned int    hash_in_node_wptr     : 8   ; /* [23..16]  */
        unsigned int    hash_in_node_total_num : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHANN_HASH_IN_NODE_CFG;

#endif /* __C_UNION_DEFINE_H__ */
