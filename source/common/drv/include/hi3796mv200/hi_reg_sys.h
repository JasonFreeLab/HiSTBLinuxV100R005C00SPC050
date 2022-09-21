//******************************************************************************
// Copyright     :  Copyright (C) 2016, Hisilicon Technologies Co., Ltd.
// File name     :  hi_reg_sys.h
// Author        :  fangqiubin 00179307
// Version       :  1.0
// Date          :  2017/03/08
// Description   :
// Others        :  Generated automatically by nManager V4.1
//******************************************************************************

#ifndef __HI_REG_SYS_H__
#define __HI_REG_SYS_H__

/* Define the union U_SC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mcu_bus_clk_sel       : 2   ; /* [1..0]  */
        unsigned int    mcu_bus_clk_sele_stat : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CTRL;

/* Define the union U_SC_SYSRES */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int softresreq             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_SYSRES;

/* Define the union U_SC_POWER_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    power_state           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_POWER_STAT;

/* Define the union U_SC_BUS_CORE_PD_COUNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int bus_core_pd_count      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_BUS_CORE_PD_COUNT;

/* Define the union U_SC_CORE_PD_RST_COUNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int core_pd_rst_count      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CORE_PD_RST_COUNT;

/* Define the union U_SC_CORE_PWRUP_COUNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int core_pwrup_count       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CORE_PWRUP_COUNT;

/* Define the union U_SC_CORE_PWRUP_RST_COUNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int core_pwrup_rst_count   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CORE_PWRUP_RST_COUNT;

/* Define the union U_SC_LOW_POWER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bus_discon_timeout_clr : 1   ; /* [0]  */
        unsigned int    reserved_0            : 2   ; /* [2..1]  */
        unsigned int    mcu_lp_subsys_iso     : 1   ; /* [3]  */
        unsigned int    sys_power_status      : 4   ; /* [7..4]  */
        unsigned int    reserved_1            : 8   ; /* [15..8]  */
        unsigned int    cpu_standbywfi        : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_LOW_POWER_CTRL;

/* Define the union U_SC_IO_REUSE_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    uart_rx_sel           : 3   ; /* [2..0]  */
        unsigned int    uart_tx_sel           : 3   ; /* [5..3]  */
        unsigned int    clk_gpio_sel          : 1   ; /* [6]  */
        unsigned int    data_gpio_sel         : 2   ; /* [8..7]  */
        unsigned int    key_gpio_sel          : 2   ; /* [10..9]  */
        unsigned int    ir_gpio_sel           : 1   ; /* [11]  */
        unsigned int    stb_gpio_sel          : 1   ; /* [12]  */
        unsigned int    dq4_gpio_sel          : 1   ; /* [13]  */
        unsigned int    reserved_0            : 1   ; /* [14]  */
        unsigned int    i2c_sda_sel           : 2   ; /* [16..15]  */
        unsigned int    i2c_scl_sel           : 2   ; /* [18..17]  */
        unsigned int    dq3_gpio_sel          : 2   ; /* [20..19]  */
        unsigned int    hdmitx_hotplug_sel    : 1   ; /* [21]  */
        unsigned int    hdmitx_sda_sel        : 1   ; /* [22]  */
        unsigned int    hdmitx_scl_sel        : 1   ; /* [23]  */
        unsigned int    hdmitx_cec_sel        : 1   ; /* [24]  */
        unsigned int    lsadc1_sel            : 2   ; /* [26..25]  */
        unsigned int    lsadc0_sel            : 1   ; /* [27]  */
        unsigned int    led_data_DS           : 3   ; /* [30..28]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_IO_REUSE_SEL;

/* Define the union U_SC_CLKGATE_SRST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mce_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ir_cken               : 1   ; /* [4]  */
        unsigned int    ir_srst_req           : 1   ; /* [5]  */
        unsigned int    timer01_cken          : 1   ; /* [6]  */
        unsigned int    timer01_srst_req      : 1   ; /* [7]  */
        unsigned int    led_cken              : 1   ; /* [8]  */
        unsigned int    led_srst_req          : 1   ; /* [9]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    uart_cken             : 1   ; /* [12]  */
        unsigned int    uart_srst_req         : 1   ; /* [13]  */
        unsigned int    reserved_2            : 2   ; /* [15..14]  */
        unsigned int    wifi_cken             : 1   ; /* [16]  */
        unsigned int    wificlk_sel           : 2   ; /* [18..17]  */
        unsigned int    hdmi_cec_cken         : 1   ; /* [19]  */
        unsigned int    hdmi_cec_srst_req     : 1   ; /* [20]  */
        unsigned int    hdmi_osc_cken         : 1   ; /* [21]  */
        unsigned int    hdmi_apb_cken         : 1   ; /* [22]  */
        unsigned int    hdmi_bus_srst_req     : 1   ; /* [23]  */
        unsigned int    hdmi_srst_req         : 1   ; /* [24]  */
        unsigned int    reserved_3            : 4   ; /* [28..25]  */
        unsigned int    uart_sel              : 1   ; /* [29]  */
        unsigned int    lsadc_cken            : 1   ; /* [30]  */
        unsigned int    lsadc_srst_req        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_CLKGATE_SRST_CTRL;

/* Define the union U_SC_WDG_RST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdg_rst_ctrl          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_WDG_RST_CTRL;

/* Define the union U_SC_DDRPHY_LP_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddrphy0_lp_en         : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_DDRPHY_LP_EN;

/* Define the union U_SC_IO_REUSE2_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    led_clk_DS            : 3   ; /* [2..0]  */
        unsigned int    led_key_DS            : 2   ; /* [4..3]  */
        unsigned int    led_key_SR            : 1   ; /* [5]  */
        unsigned int    led_key_PU            : 1   ; /* [6]  */
        unsigned int    led_key_PD            : 1   ; /* [7]  */
        unsigned int    gpio5_4_DS            : 3   ; /* [10..8]  */
        unsigned int    lsadc1_DS             : 2   ; /* [12..11]  */
        unsigned int    i2c3_sda_DS           : 2   ; /* [14..13]  */
        unsigned int    i2c3_sda_SR           : 1   ; /* [15]  */
        unsigned int    i2c3_sda_PU           : 1   ; /* [16]  */
        unsigned int    i2c3_sda_PD           : 1   ; /* [17]  */
        unsigned int    i2c3_scl_DS           : 2   ; /* [19..18]  */
        unsigned int    i2c3_scl_SR           : 1   ; /* [20]  */
        unsigned int    i2c3_scl_PU           : 1   ; /* [21]  */
        unsigned int    i2c3_scl_PD           : 1   ; /* [22]  */
        unsigned int    gpio5_6_DS            : 3   ; /* [25..23]  */
        unsigned int    ioctrl_htp_DS         : 2   ; /* [27..26]  */
        unsigned int    ioctrl_htp_SR         : 1   ; /* [28]  */
        unsigned int    ioctrl_htp_PU         : 1   ; /* [29]  */
        unsigned int    ioctrl_htp_PD         : 1   ; /* [30]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_IO_REUSE2_SEL;

/* Define the union U_SC_MCU_LDO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mcu_ldo_vset          : 4   ; /* [3..0]  */
        unsigned int    mcu_ldo_fuse          : 4   ; /* [7..4]  */
        unsigned int    mcu_ldo_enz           : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_MCU_LDO_CTRL;

/* Define the union U_SC_LSADC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsadc_en_a            : 1   ; /* [0]  */
        unsigned int    lsadc_en_b            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    lsadc_reg             : 4   ; /* [7..4]  */
        unsigned int    lsadc_pd_ctrl         : 1   ; /* [8]  */
        unsigned int    lsadc_reset           : 1   ; /* [9]  */
        unsigned int    reserved_1            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_LSADC_CTRL;

/* Define the union U_SC_LSADC_DATA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lsadc_rdata_a         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lsadc_rdata_b         : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_LSADC_DATA;

/* Define the union U_MEM_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_ema               : 3   ; /* [2..0]  */
        unsigned int    rfs_emaw              : 2   ; /* [4..3]  */
        unsigned int    rft_emaa              : 3   ; /* [7..5]  */
        unsigned int    rft_emab              : 3   ; /* [10..8]  */
        unsigned int    rft_emasa             : 1   ; /* [11]  */
        unsigned int    rft_colldisn          : 1   ; /* [12]  */
        unsigned int    ras_ema               : 3   ; /* [15..13]  */
        unsigned int    ras_emaw              : 2   ; /* [17..16]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MEM_CTRL;

/* Define the union U_SC_IO_REUSE3_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioctrl_sda_DS         : 2   ; /* [1..0]  */
        unsigned int    ioctrl_sda_SR         : 1   ; /* [2]  */
        unsigned int    ioctrl_sda_PU         : 1   ; /* [3]  */
        unsigned int    ioctrl_sda_PD         : 1   ; /* [4]  */
        unsigned int    ioctrl_scl_DS         : 2   ; /* [6..5]  */
        unsigned int    ioctrl_scl_SR         : 1   ; /* [7]  */
        unsigned int    ioctrl_scl_PU         : 1   ; /* [8]  */
        unsigned int    ioctrl_scl_PD         : 1   ; /* [9]  */
        unsigned int    ioctrl_cec_DS         : 2   ; /* [11..10]  */
        unsigned int    ioctrl_cec_SW         : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_IO_REUSE3_SEL;

/* Define the union U_SC_LOCKEN */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int sc_locken              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SC_LOCKEN;

/* Define the union U_CPU_CEC_INFO_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_cec_info_0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_CEC_INFO_0;

/* Define the union U_CPU_CEC_INFO_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_cec_info_1         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_CEC_INFO_1;

/* Define the union U_CPU_MCU_SWITCH_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_mcu_switch_info    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_MCU_SWITCH_INFO;

/* Define the union U_CPU_HDMITX_RESERVED_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_hdmitx_reserved_0  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_HDMITX_RESERVED_0;

/* Define the union U_CPU_HDMITX_RESERVED_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_hdmitx_reserved_1  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_HDMITX_RESERVED_1;

/* Define the union U_CPU_HDMITX_RESERVED_2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_hdmitx_reserved_2  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_HDMITX_RESERVED_2;

/* Define the union U_CPU_HDMITX_RESERVED_3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_hdmitx_reserved_3  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_HDMITX_RESERVED_3;

/* Define the union U_CPU_HDMITX_RESERVED_4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cpu_hdmitx_reserved_4  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CPU_HDMITX_RESERVED_4;

/* Define the union U_MCU_CEC_INFO_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_cec_info_0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_CEC_INFO_0;

/* Define the union U_MCU_CEC_INFO_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_cec_info_1         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_CEC_INFO_1;

/* Define the union U_MCU_CPU_SWITCH_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_cpu_switch_info    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_CPU_SWITCH_INFO;

/* Define the union U_MCU_HDMITX_RESERVED_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_hdmitx_reserved_0  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_HDMITX_RESERVED_0;

/* Define the union U_MCU_HDMITX_RESERVED_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_hdmitx_reserved_1  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_HDMITX_RESERVED_1;

/* Define the union U_MCU_HDMITX_RESERVED_2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_hdmitx_reserved_2  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_HDMITX_RESERVED_2;

/* Define the union U_MCU_HDMITX_RESERVED_3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_hdmitx_reserved_3  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_HDMITX_RESERVED_3;

/* Define the union U_MCU_HDMITX_RESERVED_4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mcu_hdmitx_reserved_4  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MCU_HDMITX_RESERVED_4;

/* Define the union U_DDR_PHY_PARAa */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ddr_phy_para           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDR_PHY_PARAa;

/* Define the union U_LPDS_OPER_DATAb */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int lpds_oper_data         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LPDS_OPER_DATAb;

/* Define the union U_SMCU_FW_ADDRESS_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_fw_address_0      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_FW_ADDRESS_0;

/* Define the union U_SMCU_FW_LENGTH_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_fw_length_0       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_FW_LENGTH_0;

/* Define the union U_LP_START */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int lp_start               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LP_START;

/* Define the union U_SMCU_FW_ADDRESS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_fw_address        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_FW_ADDRESS;

/* Define the union U_SMCU_FW_LENGTH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_fw_length         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_FW_LENGTH;

/* Define the union U_SMCU_GEN0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_gen0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_GEN0;

/* Define the union U_SMCU_GEN1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int smcu_gen1              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_GEN1;

/* Define the union U_SMCU_FW_ADDRESS_LOCK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smcu_fw_address_lock  : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMCU_FW_ADDRESS_LOCK;

/* Define the union U_DDR_PHY_PARA_LOCK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_phy_para_lock     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDR_PHY_PARA_LOCK;

/* Define the union U_CAS_FW_LOADER_ADDR_LOCK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cas_fw_loader_addr_lock : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_LOADER_ADDR_LOCK;

/* Define the union U_CAS_FW_ADDRESS_LOCK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cas_fw_address_lock   : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_ADDRESS_LOCK;

/* Define the union U_PCIE_BAK_REG_LOCK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcie_bak_reg_lock     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PCIE_BAK_REG_LOCK;

/* Define the union U_CAS_FW_LOADER_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cas_fw_loader_addr     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_LOADER_ADDR;

/* Define the union U_CAS_FW_LOADER_LEN */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cas_fw_loader_len      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_LOADER_LEN;

/* Define the union U_SCPU_GEN2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scpu_gen2              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCPU_GEN2;

/* Define the union U_SCPU_GEN3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scpu_gen3              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCPU_GEN3;

/* Define the union U_CAS_FW_ADDRESS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cas_fw_address         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_ADDRESS;

/* Define the union U_CAS_FW_LENGTH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cas_fw_length          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CAS_FW_LENGTH;

/* Define the union U_SCPU_GEN6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scpu_gen6              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCPU_GEN6;

/* Define the union U_SCPU_GEN7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scpu_gen7              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCPU_GEN7;

/* Define the union U_PCIE_SYS_STATE_SHW7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int pcie_sys_state_shw7    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PCIE_SYS_STATE_SHW7;

/* Define the union U_PCIE_SYS_STATE_SHW8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int pcie_sys_state_shw8    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PCIE_SYS_STATE_SHW8;

/* Define the union U_PCIE_SYS_STATE_SHW9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int pcie_sys_state_shw9    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PCIE_SYS_STATE_SHW9;

/* Define the union U_NONCE_0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nonce_0                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NONCE_0;

/* Define the union U_NONCE_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nonce_1                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NONCE_1;

/* Define the union U_NONCE_2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nonce_2                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NONCE_2;

/* Define the union U_NONCE_3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nonce_3                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_NONCE_3;

/* Define the union U_DDRCA_RANDOM0_DDRC */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ddrca_random0_ddrc     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDRCA_RANDOM0_DDRC;

/* Define the union U_DDRCA_RANDOM1_DDRC */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ddrca_random1_ddrc     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DDRCA_RANDOM1_DDRC;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_SC_CTRL                  SC_CTRL                         ; /* 0x0 */
    volatile U_SC_SYSRES                SC_SYSRES                       ; /* 0x4 */
    volatile U_SC_POWER_STAT            SC_POWER_STAT                   ; /* 0x8 */
    volatile unsigned int               reserved_0[9]                   ; /* 0xc~0x2c */
    volatile U_SC_BUS_CORE_PD_COUNT     SC_BUS_CORE_PD_COUNT            ; /* 0x30 */
    volatile U_SC_CORE_PD_RST_COUNT     SC_CORE_PD_RST_COUNT            ; /* 0x34 */
    volatile U_SC_CORE_PWRUP_COUNT      SC_CORE_PWRUP_COUNT             ; /* 0x38 */
    volatile U_SC_CORE_PWRUP_RST_COUNT  SC_CORE_PWRUP_RST_COUNT         ; /* 0x3c */
    volatile U_SC_LOW_POWER_CTRL        SC_LOW_POWER_CTRL               ; /* 0x40 */
    volatile U_SC_IO_REUSE_SEL          SC_IO_REUSE_SEL                 ; /* 0x44 */
    volatile U_SC_CLKGATE_SRST_CTRL     SC_CLKGATE_SRST_CTRL            ; /* 0x48 */
    volatile unsigned int               reserved_1                      ; /* 0x4c */
    volatile U_SC_WDG_RST_CTRL          SC_WDG_RST_CTRL                 ; /* 0x50 */
    volatile unsigned int               reserved_2                      ; /* 0x54 */
    volatile U_SC_DDRPHY_LP_EN          SC_DDRPHY_LP_EN                 ; /* 0x58 */
    volatile U_SC_IO_REUSE2_SEL         SC_IO_REUSE2_SEL                ; /* 0x5c */
    volatile unsigned int               reserved_3[2]                   ; /* 0x60~0x64 */
    volatile U_SC_MCU_LDO_CTRL          SC_MCU_LDO_CTRL                 ; /* 0x68 */
    volatile U_SC_LSADC_CTRL            SC_LSADC_CTRL                   ; /* 0x6c */
    volatile U_SC_LSADC_DATA            SC_LSADC_DATA                   ; /* 0x70 */
    volatile unsigned int               reserved_4[3]                   ; /* 0x74~0x7c */
    volatile unsigned int               SC_GENm[24]                     ; /* 0x80~0xdc */
    volatile unsigned int               SC_GENx[8]                      ; /* 0xe0~0xfc */
    volatile U_MEM_CTRL                 MEM_CTRL                        ; /* 0x100 */
    volatile U_SC_IO_REUSE3_SEL         SC_IO_REUSE3_SEL                ; /* 0x104 */
    volatile unsigned int               reserved_5[65]                  ; /* 0x108~0x208 */
    volatile U_SC_LOCKEN                SC_LOCKEN                       ; /* 0x20c */
    volatile U_CPU_CEC_INFO_0           CPU_CEC_INFO_0                  ; /* 0x210 */
    volatile U_CPU_CEC_INFO_1           CPU_CEC_INFO_1                  ; /* 0x214 */
    volatile U_CPU_MCU_SWITCH_INFO      CPU_MCU_SWITCH_INFO             ; /* 0x218 */
    volatile U_CPU_HDMITX_RESERVED_0    CPU_HDMITX_RESERVED_0           ; /* 0x21c */
    volatile U_CPU_HDMITX_RESERVED_1    CPU_HDMITX_RESERVED_1           ; /* 0x220 */
    volatile U_CPU_HDMITX_RESERVED_2    CPU_HDMITX_RESERVED_2           ; /* 0x224 */
    volatile U_CPU_HDMITX_RESERVED_3    CPU_HDMITX_RESERVED_3           ; /* 0x228 */
    volatile U_CPU_HDMITX_RESERVED_4    CPU_HDMITX_RESERVED_4           ; /* 0x22c */
    volatile U_MCU_CEC_INFO_0           MCU_CEC_INFO_0                  ; /* 0x230 */
    volatile U_MCU_CEC_INFO_1           MCU_CEC_INFO_1                  ; /* 0x234 */
    volatile U_MCU_CPU_SWITCH_INFO      MCU_CPU_SWITCH_INFO             ; /* 0x238 */
    volatile U_MCU_HDMITX_RESERVED_0    MCU_HDMITX_RESERVED_0           ; /* 0x23c */
    volatile U_MCU_HDMITX_RESERVED_1    MCU_HDMITX_RESERVED_1           ; /* 0x240 */
    volatile U_MCU_HDMITX_RESERVED_2    MCU_HDMITX_RESERVED_2           ; /* 0x244 */
    volatile U_MCU_HDMITX_RESERVED_3    MCU_HDMITX_RESERVED_3           ; /* 0x248 */
    volatile U_MCU_HDMITX_RESERVED_4    MCU_HDMITX_RESERVED_4           ; /* 0x24c */
    volatile unsigned int               reserved_6[108]                 ; /* 0x250~0x3fc */
    volatile U_DDR_PHY_PARAa            DDR_PHY_PARAa[128]              ; /* 0x400~0x5fc */
    volatile unsigned int               reserved_7[128]                 ; /* 0x600~0x7fc */
    volatile U_LPDS_OPER_DATAb          LPDS_OPER_DATAb[64]             ; /* 0x800~0x8fc */
    volatile unsigned int               reserved_8[64]                  ; /* 0x900~0x9fc */
    volatile U_SMCU_FW_ADDRESS_0        SMCU_FW_ADDRESS_0               ; /* 0xa00 */
    volatile U_SMCU_FW_LENGTH_0         SMCU_FW_LENGTH_0                ; /* 0xa04 */
    volatile U_LP_START                 LP_START                        ; /* 0xa08 */
    volatile unsigned int               reserved_9[61]                  ; /* 0xa0c~0xafc */
    volatile U_SMCU_FW_ADDRESS          SMCU_FW_ADDRESS                 ; /* 0xb00 */
    volatile U_SMCU_FW_LENGTH           SMCU_FW_LENGTH                  ; /* 0xb04 */
    volatile U_SMCU_GEN0                SMCU_GEN0                       ; /* 0xb08 */
    volatile U_SMCU_GEN1                SMCU_GEN1                       ; /* 0xb0c */
    volatile unsigned int               reserved_10[4]                  ; /* 0xb10~0xb1c */
    volatile U_SMCU_FW_ADDRESS_LOCK     SMCU_FW_ADDRESS_LOCK            ; /* 0xb20 */
    volatile unsigned int               reserved_11[3]                  ; /* 0xb24~0xb2c */
    volatile U_DDR_PHY_PARA_LOCK        DDR_PHY_PARA_LOCK               ; /* 0xb30 */
    volatile unsigned int               reserved_12[3]                  ; /* 0xb34~0xb3c */
    volatile U_CAS_FW_LOADER_ADDR_LOCK  CAS_FW_LOADER_ADDR_LOCK         ; /* 0xb40 */
    volatile U_CAS_FW_ADDRESS_LOCK      CAS_FW_ADDRESS_LOCK             ; /* 0xb44 */
    volatile unsigned int               reserved_13[2]                  ; /* 0xb48~0xb4c */
    volatile U_PCIE_BAK_REG_LOCK        PCIE_BAK_REG_LOCK               ; /* 0xb50 */
    volatile unsigned int               reserved_14[11]                 ; /* 0xb54~0xb7c */
    volatile U_CAS_FW_LOADER_ADDR       CAS_FW_LOADER_ADDR              ; /* 0xb80 */
    volatile U_CAS_FW_LOADER_LEN        CAS_FW_LOADER_LEN               ; /* 0xb84 */
    volatile U_SCPU_GEN2                SCPU_GEN2                       ; /* 0xb88 */
    volatile U_SCPU_GEN3                SCPU_GEN3                       ; /* 0xb8c */
    volatile U_CAS_FW_ADDRESS           CAS_FW_ADDRESS                  ; /* 0xb90 */
    volatile U_CAS_FW_LENGTH            CAS_FW_LENGTH                   ; /* 0xb94 */
    volatile U_SCPU_GEN6                SCPU_GEN6                       ; /* 0xb98 */
    volatile U_SCPU_GEN7                SCPU_GEN7                       ; /* 0xb9c */
    volatile unsigned int               reserved_15[8]                  ; /* 0xba0~0xbbc */
    volatile U_PCIE_SYS_STATE_SHW7      PCIE_SYS_STATE_SHW7             ; /* 0xbc0 */
    volatile U_PCIE_SYS_STATE_SHW8      PCIE_SYS_STATE_SHW8             ; /* 0xbc4 */
    volatile U_PCIE_SYS_STATE_SHW9      PCIE_SYS_STATE_SHW9             ; /* 0xbc8 */
    volatile unsigned int               reserved_16[13]                 ; /* 0xbcc~0xbfc */
    volatile U_NONCE_0                  NONCE_0                         ; /* 0xc00 */
    volatile U_NONCE_1                  NONCE_1                         ; /* 0xc04 */
    volatile U_NONCE_2                  NONCE_2                         ; /* 0xc08 */
    volatile U_NONCE_3                  NONCE_3                         ; /* 0xc0c */
    volatile unsigned int               reserved_17[177]                ; /* 0xc10~0xed0 */
    volatile U_DDRCA_RANDOM0_DDRC       DDRCA_RANDOM0_DDRC              ; /* 0xed4 */
    volatile U_DDRCA_RANDOM1_DDRC       DDRCA_RANDOM1_DDRC              ; /* 0xed8 */
    volatile unsigned int               reserved_18                     ; /* 0xedc */
    volatile unsigned int               SC_SYSID                        ; /* 0xee0 */
    volatile unsigned int               reserved_19[7]                  ; /* 0xee4~0xefc */
    volatile unsigned int               SC_GENy[32]                     ; /* 0xf00~0xf7c */
} S_SYSCTRL_REGS_TYPE;

#endif /* __HI_REG_SYS_H__ */
