// ******************************************************************************
// Copyright     :  Copyright (C) 2017, Hisilicon Technologies Co. Ltd.
// File name     :  hi_reg_peri.h
// Project line  :  ý���Ʒ��
// Department    :  STB��Ʒ��
// Author        :  fangqiubin 00179307
// Version       :  1.0
// Date          :  2014/1/17
// Description   :  ��Ŀ������Ϣ
// Others        :  Generated automatically by nManager V4.1
// History       :  fangqiubin 00179307 2017/06/01 11:17:20 Create file
// ******************************************************************************

#ifndef __HI_REG_PERI_H__
#define __HI_REG_PERI_H__

/* Define the union U_START_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 9   ; /* [8..0]  */
        unsigned int    boot_sel              : 3   ; /* [11..9]  */
        unsigned int    reserved_1            : 8   ; /* [19..12]  */
        unsigned int    romboot_sel           : 1   ; /* [20]  */
        unsigned int    reserved_2            : 1   ; /* [21]  */
        unsigned int    por_sel               : 1   ; /* [22]  */
        unsigned int    jtag_sel_in           : 1   ; /* [23]  */
        unsigned int    usb_boot              : 1   ; /* [24]  */
        unsigned int    sdio_pu_en_in_lock    : 1   ; /* [25]  */
        unsigned int    reserved_3            : 2   ; /* [27..26]  */
        unsigned int    caboot_en_in_to_ca    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_START_MODE;

/* Define the union U_PERI_REMAP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    remapstat             : 4   ; /* [3..0]  */
        unsigned int    bootram_exe_enable    : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_REMAP;

/* Define the union U_PERI_CTRL */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    sdio1_card_det_mode   : 1   ; /* [0]  */
        unsigned int    sdio0_card_det_mode   : 1   ; /* [1]  */
        unsigned int    sdio0_card_detect     : 1   ; /* [2]  */
        unsigned int    sdio1_card_detect     : 1   ; /* [3]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    sdio0_cwpr_mode       : 1   ; /* [5]  */
        unsigned int    sdio1_cwpr_mode       : 1   ; /* [6]  */
        unsigned int    reserved_1            : 3   ; /* [9..7]  */
        unsigned int    sata0_pwren           : 1   ; /* [10]  */
        unsigned int    pcie_usb3_sata3_sel_combphy1 : 2   ; /* [12..11]  */
        unsigned int    sdio0_power_en_mode   : 1   ; /* [13]  */
        unsigned int    sdio1_power_en_mode   : 1   ; /* [14]  */
        unsigned int    rgmii_rst_od_sel      : 1   ; /* [15]  */
        unsigned int    reserved_2            : 13  ; /* [28..16]  */
        unsigned int    peri_jtag_sel         : 3   ; /* [31..29]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    sdio1_card_det_mode   : 1   ; /* [0]  */
        unsigned int    sdio0_card_det_mode   : 1   ; /* [1]  */
        unsigned int    sdio0_card_detect     : 1   ; /* [2]  */
        unsigned int    sdio1_card_detect     : 1   ; /* [3]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    sdio0_cwpr_mode       : 1   ; /* [5]  */
        unsigned int    sdio1_cwpr_mode       : 1   ; /* [6]  */
        unsigned int    reserved_1            : 3   ; /* [9..7]  */
        unsigned int    sata0_pwren           : 1   ; /* [10]  */
        unsigned int    pcie_usb3_sata3_sel_combphy1 : 2   ; /* [12..11]  */
        unsigned int    sdio0_power_en_mode   : 1   ; /* [13]  */
        unsigned int    sdio1_power_en_mode   : 1   ; /* [14]  */
        unsigned int    rgmii_rst_od_sel      : 1   ; /* [15]  */
        unsigned int    reserved_2            : 8   ; /* [23..16]  */
        unsigned int    test_out_sel          : 3   ; /* [26..24]  */
        unsigned int    reserved_3            : 2   ; /* [28..27]  */
        unsigned int    peri_jtag_sel         : 3   ; /* [31..29]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CTRL;

/* Define the union U_PERI_QOS_CFG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aiao_arqos            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    aiao_awqos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    cpu_arqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 1   ; /* [19]  */
        unsigned int    cpu_awqos             : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 1   ; /* [23]  */
        unsigned int    ddrt_arqos            : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    ddrt_awqos            : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG0;

/* Define the union U_PERI_QOS_CFG1 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    gzip_arqos            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    gzip_awqos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    gpu_arqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 1   ; /* [19]  */
        unsigned int    gpu_awqos             : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 9   ; /* [31..23]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    reserved_0            : 3   ; /* [2..0]  */
        unsigned int    reserved_1            : 1   ; /* [3]  */
        unsigned int    reserved_2            : 3   ; /* [6..4]  */
        unsigned int    reserved_3            : 9   ; /* [15..7]  */
        unsigned int    gpu_arqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    gpu_awqos             : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG1;

/* Define the union U_PERI_QOS_CFG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jpgd_arqos            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    jpgd_awqos            : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    jpge_arqos            : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 1   ; /* [19]  */
        unsigned int    jpge_awqos            : 3   ; /* [22..20]  */
        unsigned int    reserved_3            : 1   ; /* [23]  */
        unsigned int    pgd_arqos             : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    pgd_awqos             : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG2;

/* Define the union U_PERI_QOS_CFG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    sata3_arqos           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    sata3_awqos           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    tde_arqos             : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    tde_awqos             : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    usb3_arqos            : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    usb3_awqos            : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 1   ; /* [27]  */
        unsigned int    vdh_arqos             : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG3;

/* Define the union U_PERI_QOS_CFG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh_awqos             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vdp_arqos             : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    vdp_awqos             : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    vedu_arqos            : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    vedu_awqos            : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 5   ; /* [23..19]  */
        unsigned int    vpss_arqos            : 3   ; /* [26..24]  */
        unsigned int    reserved_5            : 1   ; /* [27]  */
        unsigned int    vpss_awqos            : 3   ; /* [30..28]  */
        unsigned int    reserved_6            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG4;

/* Define the union U_PERI_QOS_CFG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    mcipher_qos           : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    emmc_qos              : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    dmac_qos              : 3   ; /* [18..16]  */
        unsigned int    reserved_3            : 9   ; /* [27..19]  */
        unsigned int    pvr_qos               : 3   ; /* [30..28]  */
        unsigned int    reserved_4            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG5;

/* Define the union U_PERI_QOS_CFG6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    sdio_qos              : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 5   ; /* [11..7]  */
        unsigned int    gsf_qos               : 3   ; /* [14..12]  */
        unsigned int    reserved_2            : 9   ; /* [23..15]  */
        unsigned int    sha_qos               : 3   ; /* [26..24]  */
        unsigned int    reserved_3            : 1   ; /* [27]  */
        unsigned int    usb2_qos              : 3   ; /* [30..28]  */
        unsigned int    reserved_4            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG6;

/* Define the union U_PERI_QOS_CFG7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    mce_qos               : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    pcie0_arqos           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    pcie0_awqos           : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 5   ; /* [19..15]  */
        unsigned int    fmc_qos               : 3   ; /* [22..20]  */
        unsigned int    reserved_4            : 1   ; /* [23]  */
        unsigned int    pastc_arqos           : 3   ; /* [26..24]  */
        unsigned int    reserved_5            : 1   ; /* [27]  */
        unsigned int    pastc_awqos           : 3   ; /* [30..28]  */
        unsigned int    reserved_6            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG7;

/* Define the union U_PERI_USB_RESUME_INT_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_suspend0_int_mask : 1   ; /* [0]  */
        unsigned int    usb_suspend1_int_mask : 1   ; /* [1]  */
        unsigned int    usb_suspend2_int_mask : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_MASK;

/* Define the union U_PERI_USB_RESUME_INT_RAWSTAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_suspend0_int_rawstat : 1   ; /* [0]  */
        unsigned int    usb_suspend1_int_rawstat : 1   ; /* [1]  */
        unsigned int    usb_suspend2_int_rawstat : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_RAWSTAT;

/* Define the union U_PERI_USB_RESUME_INT_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb_suspend0_int_stat : 1   ; /* [0]  */
        unsigned int    usb_suspend1_int_stat : 1   ; /* [1]  */
        unsigned int    usb_suspend2_int_stat : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB_RESUME_INT_STAT;

/* Define the union U_PERI_INT_A9TOMCE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_cputomce          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_A9TOMCE;

/* Define the union U_PERI_INT_SWI0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi0              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI0;

/* Define the union U_PERI_INT_SWI1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi1              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI1;

/* Define the union U_PERI_INT_SWI2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi2              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI2;

/* Define the union U_PERI_INT_SWI0_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi0_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI0_MASK;

/* Define the union U_PERI_INT_SWI1_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi1_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI1_MASK;

/* Define the union U_PERI_INT_SWI2_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    int_swi2_mask_a9      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_INT_SWI2_MASK;

/* Define the union U_PERI_TIANLA_ADAC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adac_dig_dacr_vol     : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    adac_dig_dacl_vol     : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 3   ; /* [17..15]  */
        unsigned int    adac_dig_deemphasis_fs : 2   ; /* [19..18]  */
        unsigned int    adac_dig_dacr_deemph  : 1   ; /* [20]  */
        unsigned int    adac_dig_dacl_deemph  : 1   ; /* [21]  */
        unsigned int    adac_dig_dacr_path    : 1   ; /* [22]  */
        unsigned int    adac_dig_dacl_path    : 1   ; /* [23]  */
        unsigned int    reserved_2            : 4   ; /* [27..24]  */
        unsigned int    adac_dig_mute_dacr    : 1   ; /* [28]  */
        unsigned int    adac_dig_mute_dacl    : 1   ; /* [29]  */
        unsigned int    adac_dig_pd_dacr      : 1   ; /* [30]  */
        unsigned int    adac_dig_pd_dacl      : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC0;

/* Define the union U_PERI_TIANLA_ADAC1 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    pop_direct_r          : 1   ; /* [0]  */
        unsigned int    pop_adj_res           : 2   ; /* [2..1]  */
        unsigned int    pop_direct_l          : 1   ; /* [3]  */
        unsigned int    pop_adj_clk           : 2   ; /* [5..4]  */
        unsigned int    reserved_0            : 1   ; /* [6]  */
        unsigned int    verf_extmod           : 1   ; /* [7]  */
        unsigned int    reserved_1            : 11  ; /* [18..8]  */
        unsigned int    clksel                : 3   ; /* [21..19]  */
        unsigned int    data_bits             : 2   ; /* [23..22]  */
        unsigned int    reserved_2            : 8   ; /* [31..24]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    adac_adj_refbf        : 3   ; /* [2..0]  */
        unsigned int    adac_adj_ctcm         : 2   ; /* [4..3]  */
        unsigned int    adac_adj_dac          : 3   ; /* [7..5]  */
        unsigned int    reserved_0            : 11  ; /* [18..8]  */
        unsigned int    adac_clk_sel_sam      : 3   ; /* [21..19]  */
        unsigned int    adac_data_bits        : 2   ; /* [23..22]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC1;

/* Define the union U_PERI_FEPHY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fephy_phy_addr        : 5   ; /* [4..0]  */
        unsigned int    mask_fephy_wol        : 1   ; /* [5]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    soft_fephy_test_en    : 1   ; /* [8]  */
        unsigned int    reserved_1            : 1   ; /* [9]  */
        unsigned int    soft_fephy_patch_en   : 1   ; /* [10]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    soft_fephy_mdio_mdc   : 1   ; /* [12]  */
        unsigned int    reserved_3            : 1   ; /* [13]  */
        unsigned int    soft_fephy_mdio_i     : 1   ; /* [14]  */
        unsigned int    reserved_4            : 1   ; /* [15]  */
        unsigned int    soft_fephy_gp_i       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_FEPHY;

/* Define the union U_PERI_SD_LDO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio0_ldo_fuse        : 4   ; /* [3..0]  */
        unsigned int    sdio0_ldo_vset        : 1   ; /* [4]  */
        unsigned int    sdio0_ldo_en          : 1   ; /* [5]  */
        unsigned int    sdio0_ldo_bypass      : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SD_LDO;

/* Define the union U_PERI_USB3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb2_2p_ss_word_if_i  : 1   ; /* [0]  */
        unsigned int    usb2_2p_ohci_susp_lgcy_i : 1   ; /* [1]  */
        unsigned int    usb2_2p_app_start_clk_i : 1   ; /* [2]  */
        unsigned int    reserved_0            : 2   ; /* [4..3]  */
        unsigned int    usb2_2p_ss_autoppd_on_overcur_en_i : 1   ; /* [5]  */
        unsigned int    usb2_2p_ss_ena_incr_align_i : 1   ; /* [6]  */
        unsigned int    usb2_2p_ss_ena_incr4_i : 1   ; /* [7]  */
        unsigned int    usb2_2p_ss_ena_incr8_i : 1   ; /* [8]  */
        unsigned int    usb2_2p_ss_ena_incr16_i : 1   ; /* [9]  */
        unsigned int    reserved_1            : 12  ; /* [21..10]  */
        unsigned int    usb2_2p_ss_hubsetup_min_i : 1   ; /* [22]  */
        unsigned int    reserved_2            : 5   ; /* [27..23]  */
        unsigned int    usb2_2p_chipid        : 1   ; /* [28]  */
        unsigned int    usb2_2p_ss_scaledown_mode : 2   ; /* [30..29]  */
        unsigned int    usb2_2p_ohci_0_cntsel_i_n : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB3;

/* Define the union U_PERI_USB5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    usb3_phy0_hub_port_perm_attach : 2   ; /* [3..2]  */
        unsigned int    usb3_phy0_host_u2_port_disable : 1   ; /* [4]  */
        unsigned int    usb3_phy0_host_u3_port_disable : 1   ; /* [5]  */
        unsigned int    usb3_phy0_host_port_power_control_present : 1   ; /* [6]  */
        unsigned int    usb3_phy0_host_msi_enable : 1   ; /* [7]  */
        unsigned int    usb3_phy0_fladj_30mhz_reg : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    usb3_phy0_bus_filter_bypass : 4   ; /* [19..16]  */
        unsigned int    usb3_phy0_host_current_belt : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB5;

/* Define the union U_PERI_USB6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb3_phy0_pwr_ctrl    : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB6;

/* Define the union U_PERI_USB2PHY_TEST0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    soft_usb2_phy0_bist_en : 1   ; /* [0]  */
        unsigned int    soft_usb2_phy0_utmi_biston : 1   ; /* [1]  */
        unsigned int    soft_usb2_phy0_utmi_testcontrol : 2   ; /* [3..2]  */
        unsigned int    soft_usb2_phy0_utmi_xcvrselect : 2   ; /* [5..4]  */
        unsigned int    soft_usb2_phy0_utmi_opmode : 2   ; /* [7..6]  */
        unsigned int    soft_usb2_phy0_utmi_termselect : 1   ; /* [8]  */
        unsigned int    soft_usb2_phy0_utmi_suspend_n : 1   ; /* [9]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    usb2_phy0_utmi_bistdone : 1   ; /* [12]  */
        unsigned int    usb2_phy0_utmi_hostdisc : 1   ; /* [13]  */
        unsigned int    usb2_phy0_utmi_status : 2   ; /* [15..14]  */
        unsigned int    soft_usb2_phy1_bist_en : 1   ; /* [16]  */
        unsigned int    soft_usb2_phy1_utmi_biston : 1   ; /* [17]  */
        unsigned int    soft_usb2_phy1_utmi_testcontrol : 2   ; /* [19..18]  */
        unsigned int    soft_usb2_phy1_utmi_xcvrselect : 2   ; /* [21..20]  */
        unsigned int    soft_usb2_phy1_utmi_opmode : 2   ; /* [23..22]  */
        unsigned int    soft_usb2_phy1_utmi_termselect : 1   ; /* [24]  */
        unsigned int    soft_usb2_phy1_utmi_suspend_n : 1   ; /* [25]  */
        unsigned int    reserved_1            : 2   ; /* [27..26]  */
        unsigned int    usb2_phy1_utmi_bistdone : 1   ; /* [28]  */
        unsigned int    usb2_phy1_utmi_hostdisc : 1   ; /* [29]  */
        unsigned int    usb2_phy1_utmi_status : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB2PHY_TEST0;

/* Define the union U_PERI_USB2PHY_TEST1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    soft_usb2_phy2_bist_en : 1   ; /* [0]  */
        unsigned int    soft_usb2_phy2_utmi_biston : 1   ; /* [1]  */
        unsigned int    soft_usb2_phy2_utmi_testcontrol : 2   ; /* [3..2]  */
        unsigned int    soft_usb2_phy2_utmi_xcvrselect : 2   ; /* [5..4]  */
        unsigned int    soft_usb2_phy2_utmi_opmode : 2   ; /* [7..6]  */
        unsigned int    soft_usb2_phy2_utmi_termselect : 1   ; /* [8]  */
        unsigned int    soft_usb2_phy2_utmi_suspend_n : 1   ; /* [9]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    usb2_phy2_utmi_bistdone : 1   ; /* [12]  */
        unsigned int    usb2_phy2_utmi_hostdisc : 1   ; /* [13]  */
        unsigned int    usb2_phy2_utmi_status : 2   ; /* [15..14]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_USB2PHY_TEST1;

/* Define the union U_PERI_COMBPHY_TEST0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    soft_combphy0_bist_en : 1   ; /* [0]  */
        unsigned int    soft_combphy0_bypass_codec : 1   ; /* [1]  */
        unsigned int    soft_combphy0_rx_eq_training : 1   ; /* [2]  */
        unsigned int    soft_combphy0_rx_polarity : 1   ; /* [3]  */
        unsigned int    soft_combphy0_rx_standby : 1   ; /* [4]  */
        unsigned int    soft_combphy0_rx_termination : 1   ; /* [5]  */
        unsigned int    soft_combphy0_tx_compliance : 1   ; /* [6]  */
        unsigned int    soft_combphy0_tx_detect_rx : 1   ; /* [7]  */
        unsigned int    soft_combphy0_tx_elecidle : 1   ; /* [8]  */
        unsigned int    soft_combphy0_tx_oneszeros : 1   ; /* [9]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY_TEST0;

/* Define the union U_PERI_TIANLA_ADAC2 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    adac_pd_dffr          : 1   ; /* [0]  */
        unsigned int    adac_pd_dffl          : 1   ; /* [1]  */
        unsigned int    adac_pd_vref          : 1   ; /* [2]  */
        unsigned int    adac_pd_ctcm_ibias    : 1   ; /* [3]  */
        unsigned int    adac_pd_ibias         : 1   ; /* [4]  */
        unsigned int    adac_pd_dacr          : 1   ; /* [5]  */
        unsigned int    adac_pd_dacl          : 1   ; /* [6]  */
        unsigned int    adac_pd_ctcm          : 1   ; /* [7]  */
        unsigned int    adac_adj_refbf        : 2   ; /* [9..8]  */
        unsigned int    adac_adj_dac          : 2   ; /* [11..10]  */
        unsigned int    adac_adj_ctcm         : 1   ; /* [12]  */
        unsigned int    stb_dac_ana_rst       : 1   ; /* [13]  */
        unsigned int    adac_mute_dacr        : 1   ; /* [14]  */
        unsigned int    adac_mute_dacl        : 1   ; /* [15]  */
        unsigned int    adac_td_sel           : 5   ; /* [20..16]  */
        unsigned int    adac_fs               : 1   ; /* [21]  */
        unsigned int    adac_popfreer         : 1   ; /* [22]  */
        unsigned int    adac_popfreel         : 1   ; /* [23]  */
        unsigned int    adac_clkdgesel        : 1   ; /* [24]  */
        unsigned int    adac_clk_sel          : 1   ; /* [25]  */
        unsigned int    adac_chop_dacvref_sel : 2   ; /* [27..26]  */
        unsigned int    adac_chop_ctcm_sel    : 2   ; /* [29..28]  */
        unsigned int    adac_chop_bps_dacvref : 1   ; /* [30]  */
        unsigned int    adac_chop_bps_ctcm    : 1   ; /* [31]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    adac_fs               : 1   ; /* [0]  */
        unsigned int    adac_pd_vref          : 1   ; /* [1]  */
        unsigned int    adac_pdb_ctcm_ibias   : 1   ; /* [2]  */
        unsigned int    adac_pd_ctcm          : 1   ; /* [3]  */
        unsigned int    adac_pd_ibias         : 1   ; /* [4]  */
        unsigned int    adac_mute_lineout     : 1   ; /* [5]  */
        unsigned int    adac_pd_dacr          : 1   ; /* [6]  */
        unsigned int    adac_pd_dacl          : 1   ; /* [7]  */
        unsigned int    adac_pop_pu_pullb     : 1   ; /* [8]  */
        unsigned int    adac_pop_pullout_en   : 1   ; /* [9]  */
        unsigned int    adac_adj_dac_low_bias : 1   ; /* [10]  */
        unsigned int    adac_adj_cp           : 2   ; /* [12..11]  */
        unsigned int    adac_gain             : 3   ; /* [15..13]  */
        unsigned int    reserved_0            : 1   ; /* [16]  */
        unsigned int    adac_mute_sp_lineout  : 1   ; /* [17]  */
        unsigned int    adac_vref_extmod      : 1   ; /* [18]  */
        unsigned int    adac_td_sel           : 5   ; /* [23..19]  */
        unsigned int    adac_dac_lineout_chop_sel : 2   ; /* [25..24]  */
        unsigned int    adac_dac_vref_chop_sel : 2   ; /* [27..26]  */
        unsigned int    adac_ctcm_chop_sel    : 2   ; /* [29..28]  */
        unsigned int    adac_chop_bps_dacvref : 1   ; /* [30]  */
        unsigned int    adac_chop_bps_ctcm    : 1   ; /* [31]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC2;

/* Define the union U_PERI_TIANLA_ADAC3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adac_chop_bps_lineout : 1   ; /* [0]  */
        unsigned int    adac_pop_spd_cfg      : 2   ; /* [2..1]  */
        unsigned int    adac_pop_pdm_delay_cfg : 2   ; /* [4..3]  */
        unsigned int    adac_rst_pop          : 1   ; /* [5]  */
        unsigned int    adac_pop_dis          : 1   ; /* [6]  */
        unsigned int    adac_pd_clkramp       : 1   ; /* [7]  */
        unsigned int    adac_pop_clk_sel      : 2   ; /* [9..8]  */
        unsigned int    adac_cp_dt_ctrl       : 2   ; /* [11..10]  */
        unsigned int    adac_cp_clk_sel       : 2   ; /* [13..12]  */
        unsigned int    adac_cp_en_soft       : 1   ; /* [14]  */
        unsigned int    adac_cp_pd            : 1   ; /* [15]  */
        unsigned int    adac_cp_buffer_pd     : 1   ; /* [16]  */
        unsigned int    adac_pd_lineout       : 1   ; /* [17]  */
        unsigned int    adac_msel             : 1   ; /* [18]  */
        unsigned int    reserved_0            : 2   ; /* [20..19]  */
        unsigned int    adac_rst              : 1   ; /* [21]  */
        unsigned int    adac_clkdgesel        : 1   ; /* [22]  */
        unsigned int    adac_clksel           : 1   ; /* [23]  */
        unsigned int    adac_ctrl7            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC3;

/* Define the union U_PERI_TIANLA_ADAC4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adac_ctrl8            : 8   ; /* [7..0]  */
        unsigned int    adac_ctrl9            : 8   ; /* [15..8]  */
        unsigned int    adac_ctrl10           : 8   ; /* [23..16]  */
        unsigned int    adac_ctrl11           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC4;

/* Define the union U_PERI_TIANLA_ADAC5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adac_ctrl12           : 8   ; /* [7..0]  */
        unsigned int    adac_ctrl13           : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_TIANLA_ADAC5;

/* Define the union U_PERI_DDRPHY_TEST0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddrphy0_iotst_iotest  : 12  ; /* [11..0]  */
        unsigned int    ddrphy0_hs_dbgmux_sel : 15  ; /* [26..12]  */
        unsigned int    ddrphy0_ls_dbgmux_sel : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_DDRPHY_TEST0;

/* Define the union U_CHIPSET_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dolby_flag            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    dts_flag              : 1   ; /* [2]  */
        unsigned int    peri_chipset_info     : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CHIPSET_INFO;

/* Define the union U_PERI_SOC_FUSE_0 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    otp_control_cpu       : 1   ; /* [0]  */
        unsigned int    soc_fuse_11_1         : 11  ; /* [11..1]  */
        unsigned int    otp_ctrl_vdac         : 1   ; /* [12]  */
        unsigned int    soc_fuse_15_13        : 3   ; /* [15..13]  */
        unsigned int    chip_id               : 5   ; /* [20..16]  */
        unsigned int    soc_fuse_21           : 1   ; /* [21]  */
        unsigned int    otp_ngd_soft_en       : 1   ; /* [22]  */
        unsigned int    otp_ngd_en            : 1   ; /* [23]  */
        unsigned int    mven                  : 1   ; /* [24]  */
        unsigned int    vedu_chip_id          : 2   ; /* [26..25]  */
        unsigned int    otp_hdr_ctrl          : 2   ; /* [28..27]  */
        unsigned int    soc_fuse_31_29        : 3   ; /* [31..29]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    reserved_0            : 12  ; /* [11..0]  */
        unsigned int    otp_ctrl_vdac         : 1   ; /* [12]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    chip_id               : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 1   ; /* [21]  */
        unsigned int    otp_ngd_soft_en       : 1   ; /* [22]  */
        unsigned int    otp_ngd_en            : 1   ; /* [23]  */
        unsigned int    mven                  : 1   ; /* [24]  */
        unsigned int    reserved_3            : 2   ; /* [26..25]  */
        unsigned int    otp_hdr_ctrl          : 2   ; /* [28..27]  */
        unsigned int    reserved_4            : 3   ; /* [31..29]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_0;

/* Define the union U_PERI_FEPHY_LDO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    fephy_ldo_en          : 1   ; /* [4]  */
        unsigned int    fephy_ldo_enz         : 1   ; /* [5]  */
        unsigned int    fephy_ldo_rstn        : 1   ; /* [6]  */
        unsigned int    fephy_iddq_mode       : 1   ; /* [7]  */
        unsigned int    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_FEPHY_LDO_CTRL;

/* Define the union U_PERI_COMBPHY0_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    combphy0_clkref_oe    : 1   ; /* [0]  */
        unsigned int    combphy0_clkref_ie    : 1   ; /* [1]  */
        unsigned int    combphy0_tx_pattern   : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    combphy0_txdeemph_2   : 1   ; /* [5]  */
        unsigned int    reserved_1            : 5   ; /* [10..6]  */
        unsigned int    combphy0_rx_standby   : 1   ; /* [11]  */
        unsigned int    combphy0_test_addr    : 5   ; /* [16..12]  */
        unsigned int    reserved_2            : 3   ; /* [19..17]  */
        unsigned int    combphy0_test_data    : 4   ; /* [23..20]  */
        unsigned int    combphy0_test_write   : 1   ; /* [24]  */
        unsigned int    reserved_3            : 3   ; /* [27..25]  */
        unsigned int    combphy0_buffer_mode  : 1   ; /* [28]  */
        unsigned int    reserved_4            : 2   ; /* [30..29]  */
        unsigned int    combphy0_bypass_codec : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY0_CFG;

/* Define the union U_PERI_COMBPHY0_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    combphy0_align_detect : 1   ; /* [0]  */
        unsigned int    combphy0_rx_standby_status : 1   ; /* [1]  */
        unsigned int    combphy0_rx_data_valid : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    combphy0_data_bus_width : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    combphy0_test_o       : 4   ; /* [11..8]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_COMBPHY0_STATE;

/* Define the union U_PERI_SOC_FUSE_1 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    otp_control_pcie0     : 1   ; /* [0]  */
        unsigned int    otp_control_sata0     : 1   ; /* [1]  */
        unsigned int    otp_ctrl_usb3_0       : 1   ; /* [2]  */
        unsigned int    otp_ctrl_gsf          : 1   ; /* [3]  */
        unsigned int    otp_ctrl_uart_core    : 1   ; /* [4]  */
        unsigned int    otp_ctrl_uart_mcu     : 1   ; /* [5]  */
        unsigned int    otp_ctrl_fephy        : 1   ; /* [6]  */
        unsigned int    otp_ctrl_usb2_2p      : 1   ; /* [7]  */
        unsigned int    romboot_sel_lock      : 1   ; /* [8]  */
        unsigned int    otp_vdh_real          : 1   ; /* [9]  */
        unsigned int    otp_vdh_divx3         : 1   ; /* [10]  */
        unsigned int    otp_vdh_vc1           : 1   ; /* [11]  */
        unsigned int    otp_vdh_vp6           : 1   ; /* [12]  */
        unsigned int    otp_vdh_vp8           : 1   ; /* [13]  */
        unsigned int    otp_vdh_h264          : 1   ; /* [14]  */
        unsigned int    otp_vdh_mpeg4         : 1   ; /* [15]  */
        unsigned int    otp_vdh_avs           : 1   ; /* [16]  */
        unsigned int    soc_fuse_51_49        : 3   ; /* [19..17]  */
        unsigned int    otp_ctrl_tsi          : 1   ; /* [20]  */
        unsigned int    otp_ctrl_tsi1         : 1   ; /* [21]  */
        unsigned int    otp_ctrl_tsi2         : 1   ; /* [22]  */
        unsigned int    otp_ctrl_tsi3         : 1   ; /* [23]  */
        unsigned int    soc_fuse_63_56        : 8   ; /* [31..24]  */
    } bits;

    /* Define the struct bits  for Hi3798MV310*/
    struct
    {
        unsigned int    otp_control_pcie0     : 1   ; /* [0]  */
        unsigned int    otp_control_sata0     : 1   ; /* [1]  */
        unsigned int    otp_ctrl_usb3_0       : 1   ; /* [2]  */
        unsigned int    otp_ctrl_gsf          : 1   ; /* [3]  */
        unsigned int    otp_ctrl_uart_core    : 1   ; /* [4]  */
        unsigned int    otp_ctrl_uart_mcu     : 1   ; /* [5]  */
        unsigned int    otp_ctrl_fephy        : 1   ; /* [6]  */
        unsigned int    otp_ctrl_usb2_2p      : 1   ; /* [7]  */
        unsigned int    romboot_sel_lock      : 1   ; /* [8]  */
        unsigned int    otp_vdh_real          : 1   ; /* [9]  */
        unsigned int    otp_vdh_divx3         : 1   ; /* [10]  */
        unsigned int    reserved_0            : 9   ; /* [19..11]  */
        unsigned int    otp_ctrl_tsi0         : 1   ; /* [20]  */
        unsigned int    otp_ctrl_tsi1         : 1   ; /* [21]  */
        unsigned int    otp_ctrl_tsi2         : 1   ; /* [22]  */
        unsigned int    otp_ctrl_tsi3         : 1   ; /* [23]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_1;

/* Define the union U_PERI_SOC_FUSE_2 */
typedef union
{
    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    otp_vdh_mpg2          : 1   ; /* [0]  */
        unsigned int    otp_vdh_h265          : 1   ; /* [1]  */
        unsigned int    otp_vdh_4k_2k         : 1   ; /* [2]  */
        unsigned int    otp_vdh_vp9           : 1   ; /* [3]  */
        unsigned int    soc_fuse_73_68        : 6   ; /* [9..4]  */
        unsigned int    otp_ctrl_sdio0        : 1   ; /* [10]  */
        unsigned int    otp_ctrl_sdio1        : 1   ; /* [11]  */
        unsigned int    otp_vdh_h265_10bit    : 1   ; /* [12]  */
        unsigned int    otp_vdh_vp9_10bit     : 1   ; /* [13]  */
        unsigned int    soc_fuse_95_76        : 18  ; /* [31..14]  */
    } bits;

    /* Define the struct bits for Hi3798MV310*/
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    otp_vdh_4k_2k         : 1   ; /* [2]  */
        unsigned int    reserved_1            : 7   ; /* [9..3]  */
        unsigned int    otp_ctrl_sdio0        : 1   ; /* [10]  */
        unsigned int    otp_ctrl_sdio1        : 1   ; /* [11]  */
        unsigned int    reserved_2            : 2   ; /* [13..12]  */
        unsigned int    otp_test_out_oen      : 1   ; /* [14]  */
        unsigned int    reserved_3            : 14  ; /* [28..15]  */
        unsigned int    otp_ctrl_spi_nand_wrap : 1   ; /* [29]  */
        unsigned int    reserved_4            : 2   ; /* [31..30]  */
    } bits_mv300;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_SOC_FUSE_2;

/* Define the union U_PERI_QOS_CFG8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mmu_vdp_pref_qos      : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    mmu_vedu_pref_qos     : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    mmu_jpgd_pref_qos     : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    mmu_pgd_pref_qos      : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    mmu_vdh_pref_qos      : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    mmu_vpss_pref_qos     : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    mmu_tde_pref_qos      : 3   ; /* [26..24]  */
        unsigned int    reserved_6            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG8;

/* Define the union U_PERI_QOS_CFG9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    mmu_mcipher_pref_qos  : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_CFG9;

/* Define the union U_PERI_QOS_MEDIA3AXI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpss_priority_media3  : 2   ; /* [1..0]  */
        unsigned int    tde_priority_media3   : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 2   ; /* [5..4]  */
        unsigned int    media1_priority_media3 : 2   ; /* [7..6]  */
        unsigned int    vedu_mst_priority     : 2   ; /* [9..8]  */
        unsigned int    pgd_mst_priority      : 2   ; /* [11..10]  */
        unsigned int    jpgd_mst_priority     : 2   ; /* [13..12]  */
        unsigned int    jpge_mst_priority     : 2   ; /* [15..14]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_QOS_MEDIA3AXI;

/* Define the union U_PERI_CPU_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_smpen             : 4   ; /* [3..0]  */
        unsigned int    cactive_adb_m         : 1   ; /* [4]  */
        unsigned int    cactive_adb_s         : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CPU_STATE;

/* Define the union U_PERI_RAM_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_ema               : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    rfs_emaw              : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ras_ema               : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    ras_emaw              : 2   ; /* [13..12]  */
        unsigned int    reserved_3            : 2   ; /* [15..14]  */
        unsigned int    rft_emaa              : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    rft_emab              : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 1   ; /* [23]  */
        unsigned int    rft_emasa             : 1   ; /* [24]  */
        unsigned int    rft_colldisn          : 1   ; /* [25]  */
        unsigned int    reserved_6            : 2   ; /* [27..26]  */
        unsigned int    ros_ema               : 3   ; /* [30..28]  */
        unsigned int    reserved_7            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_RAM_CFG;

/* Define the union U_PERI_PM_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pm31_0_en             : 1   ; /* [0]  */
        unsigned int    pm35_0_en             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    pm31_1_en             : 1   ; /* [3]  */
        unsigned int    pm35_1_en             : 1   ; /* [4]  */
        unsigned int    reserved_1            : 1   ; /* [5]  */
        unsigned int    pm31_2_en             : 1   ; /* [6]  */
        unsigned int    pm35_2_en             : 1   ; /* [7]  */
        unsigned int    reserved_2            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PM_EN;

/* Define the union U_PATH_STS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    secure_chip           : 4   ; /* [3..0]  */
        unsigned int    key_area              : 4   ; /* [7..4]  */
        unsigned int    para_area             : 4   ; /* [11..8]  */
        unsigned int    aux_area_ca_vry       : 4   ; /* [15..12]  */
        unsigned int    aux_area_hisi_vry     : 4   ; /* [19..16]  */
        unsigned int    bootram_exe_dot0      : 4   ; /* [23..20]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PATH_STS;

/* Define the union U_AUX_DEC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aux_dec               : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_AUX_DEC;

/* Define the union U_RAM_EXE_DISABLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ram_exe_disable       : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_RAM_EXE_DISABLE;

/* Define the union U_REMAP_CLR_DOT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    remap_clr_dot         : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_REMAP_CLR_DOT;

/* Define the union U_BOOT_DEC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    boot_dec              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_BOOT_DEC;

/* Define the union U_BOOT_VRY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    boot_vry              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_BOOT_VRY;

/* Define the union U_DDR_WKUP_DOT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_wkup_dot          : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDR_WKUP_DOT;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_START_MODE           START_MODE               ; /* 0x0 */
    volatile U_PERI_REMAP           PERI_REMAP               ; /* 0x4 */
    volatile U_PERI_CTRL            PERI_CTRL                ; /* 0x8 */
    volatile unsigned int           reserved_0[14]                     ; /* 0xc~0x40 */
    volatile U_PERI_QOS_CFG0        PERI_QOS_CFG0            ; /* 0x44 */
    volatile U_PERI_QOS_CFG1        PERI_QOS_CFG1            ; /* 0x48 */
    volatile U_PERI_QOS_CFG2        PERI_QOS_CFG2            ; /* 0x4c */
    volatile U_PERI_QOS_CFG3        PERI_QOS_CFG3            ; /* 0x50 */
    volatile U_PERI_QOS_CFG4        PERI_QOS_CFG4            ; /* 0x54 */
    volatile U_PERI_QOS_CFG5        PERI_QOS_CFG5            ; /* 0x58 */
    volatile U_PERI_QOS_CFG6        PERI_QOS_CFG6            ; /* 0x5c */
    volatile U_PERI_QOS_CFG7        PERI_QOS_CFG7            ; /* 0x60 */
    volatile unsigned int           reserved_1[20]                     ; /* 0x64~0xb0 */
    volatile U_PERI_USB_RESUME_INT_MASK   PERI_USB_RESUME_INT_MASK ; /* 0xb4 */
    volatile U_PERI_USB_RESUME_INT_RAWSTAT   PERI_USB_RESUME_INT_RAWSTAT ; /* 0xb8 */
    volatile U_PERI_USB_RESUME_INT_STAT   PERI_USB_RESUME_INT_STAT ; /* 0xbc */
    volatile U_PERI_INT_A9TOMCE     PERI_INT_A9TOMCE         ; /* 0xc0 */
    volatile unsigned int           reserved_2[8]                     ; /* 0xc4~0xe0 */
    volatile U_PERI_INT_SWI0        PERI_INT_SWI0            ; /* 0xe4 */
    volatile U_PERI_INT_SWI1        PERI_INT_SWI1            ; /* 0xe8 */
    volatile U_PERI_INT_SWI2        PERI_INT_SWI2            ; /* 0xec */
    volatile U_PERI_INT_SWI0_MASK   PERI_INT_SWI0_MASK       ; /* 0xf0 */
    volatile U_PERI_INT_SWI1_MASK   PERI_INT_SWI1_MASK       ; /* 0xf4 */
    volatile U_PERI_INT_SWI2_MASK   PERI_INT_SWI2_MASK       ; /* 0xf8 */
    volatile unsigned int           reserved_3[5]                     ; /* 0xfc~0x10c */
    volatile U_PERI_TIANLA_ADAC0    PERI_TIANLA_ADAC0        ; /* 0x110 */
    volatile U_PERI_TIANLA_ADAC1    PERI_TIANLA_ADAC1        ; /* 0x114 */
    volatile U_PERI_FEPHY           PERI_FEPHY               ; /* 0x118 */
    volatile U_PERI_SD_LDO          PERI_SD_LDO              ; /* 0x11c */
    volatile unsigned int           reserved_4[3]                     ; /* 0x120~0x128 */
    volatile U_PERI_USB3            PERI_USB3                ; /* 0x12c */
    volatile unsigned int           reserved_5                     ; /* 0x130 */
    volatile U_PERI_USB5            PERI_USB5                ; /* 0x134 */
    volatile U_PERI_USB6            PERI_USB6                ; /* 0x138 */
    volatile unsigned int           reserved_6[5]                     ; /* 0x13c~0x14c */
    volatile U_PERI_USB2PHY_TEST0   PERI_USB2PHY_TEST0       ; /* 0x150 */
    volatile U_PERI_USB2PHY_TEST1   PERI_USB2PHY_TEST1       ; /* 0x154 */
    volatile U_PERI_COMBPHY_TEST0   PERI_COMBPHY_TEST0       ; /* 0x158 */
    volatile unsigned int           reserved_7                     ; /* 0x15c */
    volatile U_PERI_TIANLA_ADAC2    PERI_TIANLA_ADAC2        ; /* 0x160 */
    volatile U_PERI_TIANLA_ADAC3    PERI_TIANLA_ADAC3        ; /* 0x164 */
    volatile U_PERI_TIANLA_ADAC4    PERI_TIANLA_ADAC4        ; /* 0x168 */
    volatile U_PERI_TIANLA_ADAC5    PERI_TIANLA_ADAC5        ; /* 0x16c */
    volatile unsigned int           reserved_8[17]                     ; /* 0x170~0x1b0 */
    volatile U_PERI_DDRPHY_TEST0    PERI_DDRPHY_TEST0        ; /* 0x1b4 */
    volatile unsigned int           reserved_9[10]                     ; /* 0x1b8~0x1dc */
    volatile U_CHIPSET_INFO         CHIPSET_INFO             ; /* 0x1e0 */
    volatile unsigned int           reserved_10[3]                     ; /* 0x1e4~0x1ec */
    volatile unsigned int           PERI_SW_SET              ; /* 0x1f0 */
    volatile unsigned int           reserved_11[403]                     ; /* 0x1f4~0x83c */
    volatile U_PERI_SOC_FUSE_0      PERI_SOC_FUSE_0          ; /* 0x840 */
    volatile U_PERI_FEPHY_LDO_CTRL   PERI_FEPHY_LDO_CTRL     ; /* 0x844 */
    volatile unsigned int           reserved_12[2]                     ; /* 0x848~0x84c */
    volatile U_PERI_COMBPHY0_CFG    PERI_COMBPHY0_CFG        ; /* 0x850 */
    volatile U_PERI_COMBPHY0_STATE   PERI_COMBPHY0_STATE     ; /* 0x854 */
    volatile unsigned int           reserved_13[6]                     ; /* 0x858~0x86c */
    volatile U_PERI_SOC_FUSE_1      PERI_SOC_FUSE_1          ; /* 0x870 */
    volatile U_PERI_SOC_FUSE_2      PERI_SOC_FUSE_2          ; /* 0x874 */
    volatile unsigned int           reserved_14[18]                     ; /* 0x878~0x8bc */
    volatile U_PERI_QOS_CFG8        PERI_QOS_CFG8            ; /* 0x8c0 */
    volatile U_PERI_QOS_CFG9        PERI_QOS_CFG9            ; /* 0x8c4 */
    volatile unsigned int           reserved_15                     ; /* 0x8c8 */
    volatile U_PERI_QOS_MEDIA3AXI   PERI_QOS_MEDIA3AXI       ; /* 0x8cc */
    volatile unsigned int           reserved_16[12]                     ; /* 0x8d0~0x8fc */
    volatile U_PERI_CPU_STATE       PERI_CPU_STATE           ; /* 0x900 */
    volatile unsigned int           reserved_17[7]                     ; /* 0x904~0x91c */
    volatile unsigned int           PERI_ECO_VERSION         ; /* 0x920 */
    volatile unsigned int           reserved_18[2]                     ; /* 0x924~0x928 */
    volatile U_PERI_RAM_CFG         PERI_RAM_CFG             ; /* 0x92c */
    volatile unsigned int           PERI_PM_SYS_CFG_L        ; /* 0x930 */
    volatile unsigned int           PERI_PM_SYS_CFG_H        ; /* 0x934 */
    volatile U_PERI_PM_EN           PERI_PM_EN               ; /* 0x938 */
    volatile unsigned int           PERI_PM31_0_DATA_RPT     ; /* 0x93c */
    volatile unsigned int           PERI_PM31_1_DATA_RPT     ; /* 0x940 */
    volatile unsigned int           PERI_PM31_2_DATA_RPT     ; /* 0x944 */
    volatile unsigned int           PERI_PM35_0_DATA_RPT     ; /* 0x948 */
    volatile unsigned int           PERI_PM35_1_DATA_RPT     ; /* 0x94c */
    volatile unsigned int           PERI_PM35_2_DATA_RPT     ; /* 0x950 */
    volatile unsigned int           reserved_19[7]                     ; /* 0x954~0x96c */
    volatile U_PATH_STS             PATH_STS                 ; /* 0x970 */
    volatile U_AUX_DEC              AUX_DEC                  ; /* 0x974 */
    volatile U_RAM_EXE_DISABLE      RAM_EXE_DISABLE          ; /* 0x978 */
    volatile U_REMAP_CLR_DOT        REMAP_CLR_DOT            ; /* 0x97c */
    volatile U_BOOT_DEC             BOOT_DEC                 ; /* 0x980 */
    volatile U_BOOT_VRY             BOOT_VRY                 ; /* 0x984 */
    volatile unsigned int           reserved_20                     ; /* 0x988 */
    volatile U_DDR_WKUP_DOT         DDR_WKUP_DOT             ; /* 0x98c */
    volatile unsigned int           DDR_WKUP_FLAG            ; /* 0x990 */

} S_PERICTRL_REGS_TYPE;



#endif /* __HI_REG_PERI_H__ */
