/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_drv_demux_reg.h
* Description:  Define hw regs.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DRV_DEMUX_REG_H__
#define __TEE_DRV_DEMUX_REG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define DMX_READ_REG(base, offset)  readl(base + offset)
#define DMX_WRITE_REG(base, offset, value)   writel(value, (base + offset))

#if defined(DMX_MMU_VERSION_1)
#define SMMU_SCB_TTBR_OFFSET    (0x0208)
#elif defined(DMX_MMU_VERSION_2)
#define MMU_TAB_SEC_OFFSET      (0xCF44)
#endif

#define DMX_VERSION   (0x0a00)
#define DMX_RST_OVER  (0x0a10)

#define DMX_PID_VALUE(ChanId)           (0x3400 + ((ChanId) << 2))  /* PID value set */
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    pid_value             : 13  ; // [12..0]
        unsigned int    pid_extra             : 1   ; // [13]
        unsigned int    Reserved_0            : 18  ; // [31..14]
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DMX_PID_VALUE;

#define DMX_PID_CTRL(ChanId)            (0x3000 + ((ChanId) << 2))  /* PID channel set */
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    data_type             : 2   ; // [1..0]
        unsigned int    cw_index              : 5   ; // [6..2]
        unsigned int    do_scram              : 1   ; // [7]
        unsigned int    af_mode               : 2   ; // [9..8]
        unsigned int    crc_mode              : 3   ; // [12..10]
        unsigned int    cc_discon_ctrl        : 1   ; // [13]
        unsigned int    pusi_disable          : 1   ; // [14]
        unsigned int    cc_equ_rve            : 1   ; // [15]
        unsigned int    ts_post_mode          : 1   ; // [16]
        unsigned int    ts_post_threshold     : 6   ; // [22..17]
        unsigned int    ch_attri              : 3   ; // [25..23]
        unsigned int    Reserved_0            : 6   ; // [31..26]
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_DMX_PID_CTRL;

#ifdef DMX_SECURE_CHANNEL_SUPPORT
#define DMX_SECURE_OQ(offset)   (0x3E20 + ((offset) << 2))
#endif

#ifdef DMX_SECURE_KEY_SUPPORT
#define CW_SECURE_FLAG          (0x3e10)  /* secure CW set flag */
#define CW_SECURE_LOCK          (0x3e14) /* secure CW lock */
#define CW_SET_SECURE           (0x3E00)    /* secure CW configuration control register */
#define DMX_CW_DATA_SECURE      (0x3E04)    /* secure CW configuration register */
#endif
#define CW_SET_NONSECURE        (0x3B80)    /* none secure CW configuration control register */
#define DMX_CW_DATA_NONSECURE   (0x3B84)    /* none secure CW configuration register */

//DEMUX config regs
#define DMX_CRG_REGS_IOBASE      (0xF8A22000)
#define DMX_CRG_REGS63_OFFSET    (0xFC)
#define DMX_CRG_REGS64_OFFSET    (0x100)

typedef union
{
    struct
    {
        HI_U32  cw_word_id      : 2;    // [1:0]
        HI_U32  reserved0       : 6;    // [7:2]
        HI_U32  cw_odd_even     : 1;    // [8]
        HI_U32  cw_group_id     : 5;    // [13:9]
        HI_U32  reserved1       : 2;    // [15:14]
        HI_U32  cw_type         : 8;    // [23:16]
        HI_U32  cw_iv_sel       : 1;    // [24]
        HI_U32  reserved2       : 7;    // [31:25]
    } bits;

    HI_U32  value;
} U_CW_SET1;

#ifdef DMX_SECURE_ENCRYPT_KEY_SUPPORT
#define DMX_ACTIVE_ENCRYPT_KEY_SET   (0x3E08)
#define DMX_SECURE_ENCRYPT_KEY_SET   (0x3E0C)

typedef union
{
    struct
    {
        HI_U32 sec_rec_scr_index      : 5;   // [4 : 0]
        HI_U32 reserved_0             : 3;   // [7 : 5]
        HI_U32 sec_scr_flag           : 1;   // [8]
        HI_U32 reserved_1             : 23;  // [31 : 9]
    }bits;

    HI_U32 u32;
}U_CW_ENCRYPT_SET;

#define DMX_CW_SET(DmxId)               (0x3BC0 + ((DmxId) << 2))
typedef union
{
    struct
    {
        HI_U32    dmx_cw_index            : 5   ; // [4..0]
        HI_U32    Reserved_1              : 1   ; // [5]
        HI_U32    dmx_cw_tabid            : 2   ; // [7..6]
        HI_U32    dmx_cw_open             : 1   ; // [8]
        HI_U32    dmx_cw_nocare_syntax    : 1   ; // [9]
        HI_U32    dmx_cw_dsc_chg_flag     : 1   ; // [10]
        HI_U32    cw_iv_en                : 1   ; // [11]
        HI_U32    dmx_cw_scr_chg_flag     : 1   ; // [12]
        HI_U32    Reserved_0              : 18  ; // [31..13]
    } bits;

    HI_U32 u32;

} U_DMX_CW_SET;
#endif

#ifdef DMX_SECURE_RAM_PORT_SUPPORT
#define DMX_SECURE_RAM_PORT_SET (0x3E1C)
#endif

#define CA_INFO0                        (0x3B90)    /* hardware OTP CA set [31:0] */
typedef union
{
    struct
    {
        HI_U32  hardonly_csa2       : 1;    // [0]
        HI_U32  hardonly_spe        : 1;    // [1]
        HI_U32  hardonly_des        : 1;    // [2]
        HI_U32  hardonly_novel      : 1;    // [3]
        HI_U32  hardonly_csa3       : 1;    // [4]
        HI_U32  hardonly_others     : 1;    // [5]
        HI_U32  hardonly_aes_cbc    : 1;    // [6]
        HI_U32  hardonly_ctr_clr    : 1;    // [7]
        HI_U32  dis_csa2            : 1;    // [8]
        HI_U32  dis_spe             : 1;    // [9]
        HI_U32  dis_des             : 1;    // [10]
        HI_U32  dis_novel           : 1;    // [11]
        HI_U32  dis_csa3            : 1;    // [12]
        HI_U32  dis_others          : 1;    // [13]
        HI_U32  dis_tdes            : 1;    // [14]
        HI_U32  reserved1           : 1;    // [15]
        HI_U32  dis_asa             : 1;    // [16]
        HI_U32  reserved2           : 13;   // [29:17]
        HI_U32  ca_tsout_dis        : 1;    // [30]
        HI_U32  cainfo_dbg_dis      : 1;    // [31]
    } bits;

    HI_U32 value;
} U_CA_INFO0;

#define CA_ENTROPY                      (0x3BA8)    /* reserved register. Entropy decrease register */

#define CHAN_CW_TAB_ID(ChanId)          (0x3BE0 + (ChanId) / 16 * 4)    /* Set channel's CW table id, 2bit for each channel */


#define TS_CNT0_5_L(RecId)               (0xC1B0 + ((RecId) << 3))   /* TS packet counter 0-5 of joining on someone record buffer low 32bit */
#define TS_CNT0_5_H(RecId)               (0xC1B4 + ((RecId) << 3))   /* TS packet counter 0-5 of joining on someone record buffer high 8 bits */
#define TS_CNT6_31_L(RecId)              (0xC500 + ((RecId) << 3))   /* TS packet counter 6-31 of joining on someone record buffer low 32bit */
#define TS_CNT6_31_H(RecId)              (0xC504 + ((RecId) << 3))   /* TS packet counter 6-31 of joining on someone record buffer high 8 bits */


#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
/* Define the union U_PERI_CRG63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_bus_cken          : 1   ; /* [0]  */
        unsigned int    pvr_dmx_cken          : 1   ; /* [1]  */
        unsigned int    pvr_27m_cken          : 1   ; /* [2]  */
        unsigned int    pvr_tsi1_cken         : 1   ; /* [3]  */
        unsigned int    pvr_tsi2_cken         : 1   ; /* [4]  */
        unsigned int    pvr_tsi3_cken         : 1   ; /* [5]  */
        unsigned int    pvr_tsi4_cken         : 1   ; /* [6]  */
        unsigned int    reserved_0            : 3   ; /* [9..7]  */
        unsigned int    pvr_ts0_cken          : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    pvr_tsout0_cken       : 1   ; /* [12]  */
        unsigned int    reserved_2            : 2   ; /* [14..13]  */
        unsigned int    pvr_tsi1_pctrl        : 1   ; /* [15]  */
        unsigned int    pvr_tsi2_pctrl        : 1   ; /* [16]  */
        unsigned int    pvr_tsi3_pctrl        : 1   ; /* [17]  */
        unsigned int    pvr_tsi4_pctrl        : 1   ; /* [18]  */
        unsigned int    reserved_3            : 5   ; /* [23..19]  */
        unsigned int    pvr_srst_req          : 1   ; /* [24]  */
        unsigned int    reserved_4            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG63;

/* Define the union U_PERI_CRG64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_tsout0_pctrl      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    pvr_dmx_clk_sel       : 1   ; /* [2]  */
        unsigned int    reserved_1            : 1   ; /* [3]  */
        unsigned int    sw_dmx_clk_div        : 5   ; /* [8..4]  */
        unsigned int    sw_dmxclk_loaden      : 1   ; /* [9]  */
        unsigned int    pvr_dmx_clkdiv_cfg    : 1   ; /* [10]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    pvr_ts0_clk_sel       : 2   ; /* [13..12]  */
        unsigned int    reserved_3            : 2   ; /* [15..14]  */
        unsigned int    pvr_ts0_clk_div       : 4   ; /* [19..16]  */
        unsigned int    reserved_4            : 4   ; /* [23..20]  */
        unsigned int    pvr_tsi_sel           : 1   ; /* [24]  */
        unsigned int    reserved_5            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG64;
#elif defined(CHIP_TYPE_hi3798cv200)

/* Define the union U_PERI_CRG63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_bus_cken          : 1   ; /* [0]  */
        unsigned int    pvr_dmx_cken          : 1   ; /* [1]  */
        unsigned int    pvr_27m_cken          : 1   ; /* [2]  */
        unsigned int    pvr_tsi1_cken         : 1   ; /* [3]  */
        unsigned int    pvr_tsi2_cken         : 1   ; /* [4]  */
        unsigned int    pvr_tsi3_cken         : 1   ; /* [5]  */
        unsigned int    pvr_tsi4_cken         : 1   ; /* [6]  */
        unsigned int    pvr_tsi5_cken         : 1   ; /* [7]  */
        unsigned int    pvr_tsi6_cken         : 1   ; /* [8]  */
        unsigned int    reserved_0            : 1   ; /* [9]  */
        unsigned int    pvr_ts0_cken          : 1   ; /* [10]  */
        unsigned int    pvr_ts1_cken          : 1   ; /* [11]  */
        unsigned int    pvr_tsout0_cken       : 1   ; /* [12]  */
        unsigned int    pvr_tsout1_cken       : 1   ; /* [13]  */
        unsigned int    reserved_1            : 1   ; /* [14]  */
        unsigned int    pvr_tsi1_pctrl        : 1   ; /* [15]  */
        unsigned int    pvr_tsi2_pctrl        : 1   ; /* [16]  */
        unsigned int    pvr_tsi3_pctrl        : 1   ; /* [17]  */
        unsigned int    pvr_tsi4_pctrl        : 1   ; /* [18]  */
        unsigned int    pvr_tsi5_pctrl        : 1   ; /* [19]  */
        unsigned int    pvr_tsi6_pctrl        : 1   ; /* [20]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    pvr_srst_req          : 1   ; /* [24]  */
        unsigned int    reserved_3            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG63;

/* Define the union U_PERI_CRG64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_tsout0_pctrl      : 1   ; /* [0]  */
        unsigned int    pvr_tsout1_pctrl      : 1   ; /* [1]  */
        unsigned int    pvr_dmx_clk_sel       : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    sw_dmx_clk_div        : 5   ; /* [8..4]  */
        unsigned int    sw_dmxclk_loaden      : 1   ; /* [9]  */
        unsigned int    pvr_dmx_clkdiv_cfg    : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    pvr_ts0_clk_sel       : 2   ; /* [13..12]  */
        unsigned int    pvr_ts1_clk_sel       : 2   ; /* [15..14]  */
        unsigned int    pvr_ts0_clk_div       : 4   ; /* [19..16]  */
        unsigned int    pvr_ts1_clk_div       : 4   ; /* [23..20]  */
        unsigned int    clk_tsi03_com_sel     : 3   ; /* [26..24]  */
        unsigned int    reserved_2            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG64;

#elif defined(CHIP_TYPE_hi3796mv200)
/* Define the union U_PERI_CRG63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_bus_cken          : 1   ; /* [0]  */
        unsigned int    pvr_dmx_cken          : 1   ; /* [1]  */
        unsigned int    pvr_27m_cken          : 1   ; /* [2]  */
        unsigned int    pvr_tsi1_cken         : 1   ; /* [3]  */
        unsigned int    pvr_tsi2_cken         : 1   ; /* [4]  */
        unsigned int    pvr_tsi3_cken         : 1   ; /* [5]  */
        unsigned int    pvr_tsi4_cken         : 1   ; /* [6]  */
        unsigned int    pvr_tsi5_cken         : 1   ; /* [7]  */
        unsigned int    pvr_tsi6_cken         : 1   ; /* [8]  */
        unsigned int    pvr_tsi7_cken         : 1   ; /* [9]  */
        unsigned int    pvr_ts0_cken          : 1   ; /* [10]  */
        unsigned int    pvr_ts1_cken          : 1   ; /* [11]  */
        unsigned int    pvr_tsout0_cken       : 1   ; /* [12]  */
        unsigned int    pvr_tsout1_cken       : 1   ; /* [13]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    pvr_tsi2_pctrl        : 1   ; /* [16]  */
        unsigned int    pvr_tsi3_pctrl        : 1   ; /* [17]  */
        unsigned int    pvr_tsi4_pctrl        : 1   ; /* [18]  */
        unsigned int    pvr_tsi5_pctrl        : 1   ; /* [19]  */
        unsigned int    pvr_tsi6_pctrl        : 1   ; /* [20]  */
        unsigned int    pvr_tsi7_pctrl        : 1   ; /* [21]  */
        unsigned int    pvr_tsi8_pctrl        : 1   ; /* [22]  */
        unsigned int    reserved_1            : 1   ; /* [23]  */
        unsigned int    pvr_srst_req          : 1   ; /* [24]  */
        unsigned int    pvr_tsi8_cken         : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG63;

/* Define the union U_PERI_CRG64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_tsout0_pctrl      : 1   ; /* [0]  */
        unsigned int    pvr_tsout1_pctrl      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 10  ; /* [11..2]  */
        unsigned int    pvr_ts0_clk_sel       : 2   ; /* [13..12]  */
        unsigned int    pvr_ts1_clk_sel       : 2   ; /* [15..14]  */
        unsigned int    pvr_ts0_clk_div       : 4   ; /* [19..16]  */
        unsigned int    pvr_ts1_clk_div       : 4   ; /* [23..20]  */
        unsigned int    pvr_tsi_sel           : 1   ; /* [24]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG64;

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DRV_DEMUX_REG_H__ */
