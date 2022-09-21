/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_reg_aon.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/06/28
  Description   :
  History       :
  Date          : 20161202
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __HDMI_MCU_REG_AON_H__
#define __HDMI_MCU_REG_AON_H__

#include "hi_type.h"

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_tx_hw_year  : 16  ; /* [31:16] */

        HI_U16     bit08_tx_hw_day   : 8  ; /* [7:0] */
        HI_U16     bit08_tx_hw_month : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_HW_INFO;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     tx_rtl_version : 8  ; /* [23:16] */
        HI_U16     rsv_0          : 8  ; /* [31:24] */

        HI_U16     tx_reg_version : 8  ; /* [7:0] */
        HI_U16     tx_drv_version : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_HW_VERSION;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     rsv_0 : 16  ; /* [15:0] */

        HI_U16     rsv_1 : 16  ; /* [31:16] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_HW_FEATURE;

/* Define the union REG_TX_AON_RST_CTRL */
/* Define the union REG_TX_AON_RST_CTRL,ATTR:,ADDR:401C,INIT:00000000,MASK:1,CMMNT:±£Áô¼Ä´æÆ÷*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_2                : 16  ; /* [31:16] */

        HI_U16     bit01_tx_aon_soft_arst_req : 1  ; /* [0] */
        HI_U16     bit15_rsv_1                : 15  ; /* [15:1] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_AON_RST_CTRL;

/* Define the union REG_HOTPLUG_ST_CFG */
/* Define the union REG_HOTPLUG_ST_CFG,ATTR:,ADDR:4020,INIT:00007CF1,MASK:ffff,CMMNT:HOTPLUG ×´Ì¬ÅäÖÃ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_3            : 16  ; /* [31:16] */

        HI_U16     bit01_hpd_fillter_en   : 1  ; /* [0] */
        HI_U16     bit01_hpd_override_en  : 1  ; /* [1] */
        HI_U16     bit01_hpd_polarity_ctl : 1  ; /* [2] */
        HI_U16     bit01_hpd_soft_value   : 1  ; /* [3] */
        HI_U16     bit12_osc_div_cnt      : 12  ; /* [15:4] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_HOTPLUG_ST_CFG;

/* Define the union REG_HOTPLUG_FILLTER_CFG */
/* Define the union REG_HOTPLUG_FILLTER_CFG,ATTR:,ADDR:4024,INIT:00090063,MASK:ffffffff,CMMNT:HOTPLUG Ã«´Ì¹ýÂËÅäÖÃ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_hpd_low_reshold  : 16  ; /* [31:16] */

        HI_U16     bit16_hpd_high_reshold : 16  ; /* [15:0] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_HOTPLUG_FILLTER_CFG;

/* Define the union REG_TX_AON_STATE */
/* Define the union REG_TX_AON_STATE,ATTR:,ADDR:4028,INIT:00000000,MASK:3,CMMNT:TX AON Ä£¿é×´Ì¬Ö¸Ê¾¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_2         : 16  ; /* [31:2] */

        HI_U16     bit01_hotplug_state : 1  ; /* [0] */
        HI_U16     bit01_phy_rx_sense  : 1  ; /* [1] */
        HI_U16     bit12_rsv_0         : 14  ; /* [15:2] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_AON_STATE;

/* Define the union REG_TX_AON_INTR_MASK */
/* Define the union REG_TX_AON_INTR_MASK,ATTR:,ADDR:4030,INIT:00000000,MASK:3ff3,CMMNT:TX AON Ä£¿éÖÐ¶ÏÆÁ±Î¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_1           : 16  ; /* [31:16] */

        HI_U16     bit01_aon_intr_mask0  : 1  ; /* [0] */
        HI_U16     bit01_aon_intr_mask1  : 1  ; /* [1] */
        HI_U16     bit01_rsv_5           : 1  ; /* [2] */
        HI_U16     bit01_rsv_6           : 1  ; /* [3] */
        HI_U16     bit01_aon_intr_mask4  : 1  ; /* [4] */
        HI_U16     bit01_aon_intr_mask5  : 1  ; /* [5] */
        HI_U16     bit01_aon_intr_mask6  : 1  ; /* [6] */
        HI_U16     bit01_aon_intr_mask7  : 1  ; /* [7] */
        HI_U16     bit01_aon_intr_mask8  : 1  ; /* [8] */
        HI_U16     bit01_aon_intr_mask9  : 1  ; /* [9] */
        HI_U16     bit01_aon_intr_mask10 : 1  ; /* [10] */
        HI_U16     bit01_aon_intr_mask11 : 1  ; /* [11] */
        HI_U16     bit01_aon_intr_mask12 : 1  ; /* [12] */
        HI_U16     bit01_aon_intr_mask13 : 1  ; /* [13] */
        HI_U16     bit02_rsv_7           : 2  ; /* [15:14] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_AON_INTR_MASK;

/* Define the union REG_TX_AON_INTR_STATE */
/* Define the union REG_TX_AON_INTR_STATE,ATTR:,ADDR:4034,INIT:00000000,MASK:3ff3,CMMNT:TX AON Ä£¿éÖÐ¶Ï×´Ì¬¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_01          : 16  ; /* [31:16] */

        HI_U16     bit01_aon_intr_stat0  : 1  ; /* [0] */
        HI_U16     bit01_aon_intr_stat1  : 1  ; /* [1] */
        HI_U16     bit01_rsv_8           : 1  ; /* [2] */
        HI_U16     bit01_rsv_9           : 1  ; /* [3] */
        HI_U16     bit01_aon_intr_stat4  : 1  ; /* [4] */
        HI_U16     bit01_aon_intr_stat5  : 1  ; /* [5] */
        HI_U16     bit01_aon_intr_stat6  : 1  ; /* [6] */
        HI_U16     bit01_aon_intr_stat7  : 1  ; /* [7] */
        HI_U16     bit01_aon_intr_stat8  : 1  ; /* [8] */
        HI_U16     bit01_aon_intr_stat9  : 1  ; /* [9] */
        HI_U16     bit01_aon_intr_stat10 : 1  ; /* [10] */
        HI_U16     bit01_aon_intr_stat11 : 1  ; /* [11] */
        HI_U16     bit01_aon_intr_stat12 : 1  ; /* [12] */
        HI_U16     bit01_aon_intr_stat13 : 1  ; /* [13] */
        HI_U16     bit02_rsv_00          : 2  ; /* [15:14] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_TX_AON_INTR_STATE;

/* Define the union REG_DDC_MST_CTRL */
/* Define the union REG_DDC_MST_CTRL,ATTR:,ADDR:4040,INIT:000004A0,MASK:1ff3,CMMNT:DDC MasterÄ£¿éÅäÖÃ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_12         : 16  ; /* [31:16] */

        HI_U16     bit01_ddc_aon_access : 1  ; /* [0] */
        HI_U16     bit01_dcc_man_en     : 1  ; /* [1] */
        HI_U16     bit02_rsv_11         : 2  ; /* [3:2] */
        HI_U16     bit09_ddc_speed_cnt  : 9  ; /* [12:4] */
        HI_U16     bit03_rsv_12         : 3  ; /* [15:13] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_MST_CTRL;

/* Define the union REG_DDC_FIFO_RDATA */
/* Define the union REG_DDC_FIFO_RDATA,ATTR:,ADDR:4044,INIT:00000000,MASK:ff,CMMNT:DDC Master FIFO ¶ÁÊý¾Ý¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_13            : 16  ; /* [31:16] */

        HI_U16     bit08_ddc_fifo_data_out : 8  ; /* [7:0] */
        HI_U16     bit08_rsv_13            : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_FIFO_RDATA;

/* Define the union REG_DDC_FIFO_WDATA */
/* Define the union REG_DDC_FIFO_WDATA,ATTR:,ADDR:4048,INIT:00000000,MASK:ff,CMMNT:DDC Master FIFO Ð´Êý¾Ý¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_14           : 16  ; /* [31:8] */

        HI_U16     bit08_ddc_fifo_data_in : 8  ; /* [7:0] */
        HI_U16     bit08_rsv_14           : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_FIFO_WDATA;

/* Define the union REG_DDC_DATA_CNT */
/* Define the union REG_DDC_DATA_CNT,ATTR:,ADDR:404C,INIT:00000000,MASK:3ff1f,CMMNT:DDC Master FIFOÊý¾Ý¼ÆÊý¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit02_H_ddc_data_out_cnt  : 2  ; /* [17:16] */   //note that 10bit total,it must combime to use
        HI_U16     bit14_rsv_16            : 14  ; /* [31:18] */

        HI_U16     bit05_ddc_fifo_data_cnt : 5  ; /* [4:0] */
        HI_U16     bit03_rsv_15            : 3  ; /* [7:5] */
        HI_U16     bit08_L_ddc_data_out_cnt  : 8  ; /* [15:8] */    //note that 10bit total,it must combime to use
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_DATA_CNT;

/* Define the union REG_DDC_SLAVE_CFG */
/* Define the union REG_DDC_SLAVE_CFG,ATTR:,ADDR:4050,INIT:00000000,MASK:ffffff,CMMNT:DDC ·ÃÎÊSlaveÅäÖÃ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_ddc_slave_seg    : 8  ; /* [23:16] */
        HI_U16     bit08_rsv_17           : 8  ; /* [31:24] */

        HI_U16     bit08_ddc_slave_addr   : 8  ; /* [7:0] */
        HI_U16     bit08_ddc_slave_offset : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_SLAVE_CFG;

/* Define the union REG_DDC_MST_STATE */
/* Define the union REG_DDC_MST_STATE,ATTR:,ADDR:4054,INIT:00000020,MASK:ff,CMMNT:DDC Master ×´Ì¬Ö¸Ê¾¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_18             : 16  ; /* [31:16] */

        HI_U16     bit01_ddc_i2c_no_ack     : 1  ; /* [0] */
        HI_U16     bit01_ddc_i2c_bus_low    : 1  ; /* [1] */
        HI_U16     bit01_ddc_i2c_in_prog    : 1  ; /* [2] */
        HI_U16     bit01_ddc_fifo_wr_in_use : 1  ; /* [3] */
        HI_U16     bit01_ddc_fifo_rd_in_use : 1  ; /* [4] */
        HI_U16     bit01_ddc_fifo_empty     : 1  ; /* [5] */
        HI_U16     bit01_ddc_fifo_half_full : 1  ; /* [6] */
        HI_U16     bit01_ddc_fifo_full      : 1  ; /* [7] */
        HI_U16     bit08_rsv_18             : 8  ; /* [15:8] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_MST_STATE;

/* Define the union REG_DDC_MST_CMD */
/* Define the union REG_DDC_MST_CMD,ATTR:,ADDR:4058,INIT:00000000,MASK:f,CMMNT:DDC Master Ö¸ÁîÅäÖÃ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_19      : 16  ; /* [31:4] */

        HI_U16     bit04_ddc_mst_cmd : 4  ; /* [3:0] */
        HI_U16     bit12_rsv_19      : 12  ; /* [31:4] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_MST_CMD;

/* Define the union REG_DDC_MAN_CTRL */
/* Define the union REG_DDC_MAN_CTRL,ATTR:,ADDR:405C,INIT:0000000C,MASK:f,CMMNT:DDC Í¨µÀÈí¼þÄ£Äâ¿ØÖÆ¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_20      : 16  ; /* [31:16] */

        HI_U16     bit01_ddc_scl_st  : 1  ; /* [0] */
        HI_U16     bit01_ddc_sda_st  : 1  ; /* [1] */
        HI_U16     bit01_ddc_scl_oen : 1  ; /* [2] */
        HI_U16     bit01_ddc_sda_oen : 1  ; /* [3] */
        HI_U16     bit12_rsv_20      : 12  ; /* [15:4] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_MAN_CTRL;

/* Define the union REG_DDC_STATE_CLR */
/* Define the union REG_DDC_STATE_CLR,ATTR:,ADDR:4060,INIT:00000000,MASK:3,CMMNT:DDC Master ×´Ì¬Çå³ý¼Ä´æÆ÷¡£*/
typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_21          : 16  ; /* [31:16] */

        HI_U16     bit01_ddc_clr_bus_low : 1  ; /* [0] */
        HI_U16     bit01_ddc_clr_no_ack  : 1  ; /* [1] */
        HI_U16     bit14_rsv_21          : 14  ; /* [15:2] */
    } bits;

    HI_U8       u8[4];
    HI_U32      u32;
} REG_DDC_STATE_CLR;

#define MCU_AON_BASE_ADDR            0xf8ce0000

#define REG_AON_TX_HW_INFO          (MCU_AON_BASE_ADDR + 0x4000)
#define REG_AON_TX_HW_VERSION       (MCU_AON_BASE_ADDR + 0x4004)
#define REG_AON_TX_HW_FEATURE       (MCU_AON_BASE_ADDR + 0x4008)
/*    Reserved_0[4];	400C-4018*/
#define REG_AON_TX_AON_RST_CTRL     (MCU_AON_BASE_ADDR + 0x401C)
#define REG_AON_HOTPLUG_ST_CFG      (MCU_AON_BASE_ADDR + 0x4020)
#define REG_AON_HOTPLUG_FILLTER_CFG (MCU_AON_BASE_ADDR + 0x4024)
#define REG_AON_TX_AON_STATE        (MCU_AON_BASE_ADDR + 0x4028)
/*    Reserved_2[1];	(MCU_AON_BASE_ADDR + 0x402C */
#define REG_AON_TX_AON_INTR_MASK    (MCU_AON_BASE_ADDR + 0x4030)
#define REG_AON_TX_AON_INTR_STATE   (MCU_AON_BASE_ADDR + 0x4034)
/*    Reserved_3[2];	(MCU_AON_BASE_ADDR + 0x4038-403C*/
#define REG_AON_DDC_MST_CTRL        (MCU_AON_BASE_ADDR + 0x4040)
#define REG_AON_DDC_FIFO_RDATA      (MCU_AON_BASE_ADDR + 0x4044)
#define REG_AON_DDC_FIFO_WDATA      (MCU_AON_BASE_ADDR + 0x4048)
#define REG_AON_DDC_DATA_CNT        (MCU_AON_BASE_ADDR + 0x404C)
#define REG_AON_DDC_SLAVE_CFG       (MCU_AON_BASE_ADDR + 0x4050)
#define REG_AON_DDC_MST_STATE       (MCU_AON_BASE_ADDR + 0x4054)
#define REG_AON_DDC_MST_CMD         (MCU_AON_BASE_ADDR + 0x4058)
#define REG_AON_DDC_MAN_CTRL        (MCU_AON_BASE_ADDR + 0x405C)
#define REG_AON_DDC_STATE_CLR       (MCU_AON_BASE_ADDR + 0x4060)

#endif // __HDMI_MCU_REG_AON_H__

