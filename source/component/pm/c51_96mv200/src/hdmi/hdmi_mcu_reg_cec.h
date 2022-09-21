
/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_reg_cec.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2016/12/02
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __HDMI_MCU_REG_CEC_H__
#define __HDMI_MCU_REG_CEC_H__

#include "hi_type.h"

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit01_cec_reg_calib_cec_en            : 1  ; /* [16] */
        HI_U16     bit01_cec_reg_force_non_calib         : 1  ; /* [17] */
        HI_U16     bit01_cec_reg_i2c_cec_passthru        : 1  ; /* [18] */
        HI_U16     bit01_manual_cmd_set                  : 1  ; /* [19] */
        HI_U16     bit01_cec_reg_tx_auto_calc            : 1  ; /* [20] */
        HI_U16     bit01_cec_reg_tx_bfr_ac               : 1  ; /* [21] */
        HI_U16     bit04_cec_reg_tx_cmd_cnt              : 4  ; /* [25:22] */
        HI_U16     bit03_cec_reg_tx_retry_limit          : 3  ; /* [28:26] */
        HI_U16     bit01_cec_reg_rx_clr_cur_set          : 1  ; /* [29] */
        HI_U16     bit01_cec_reg_rx_clr_all              : 1  ; /* [30] */
        HI_U16     bit01_auto_clear_intrp_rx_fifo_nempty : 1  ; /* [31] */

        HI_U16     bit04_cec_bus_owner                   : 4  ; /* [3:0] */
        HI_U16     bit04_cec_snoop_initiator             : 4  ; /* [7:4] */
        HI_U16     bit01_cec_reg_snoop                   : 1  ; /* [8] */
        HI_U16     bit01_cec_reg_nack_hdr                : 1  ; /* [9] */
        HI_U16     bit01_cec_inv_ack_brcst               : 1  ; /* [10] */
        HI_U16     bit03_cec_ctl_retry_cnt               : 3  ; /* [13:11] */
        HI_U16     bit01_cec_reg_flush_tx_ff             : 1  ; /* [14] */
        HI_U16     bit01_cec_reg_calib_cec               : 1  ; /* [15] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_TX_CTRL_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_3                   : 16  ; /* [31:16] */

        HI_U16     bit04_cec_reg_rx_cmd_byte_cnt : 4  ; /* [3:0] */
        HI_U16     bit02_cec_reg_rx_ff_wr_sel    : 2  ; /* [5:4] */
        HI_U16     bit01_rsv_2                   : 1  ; /* [6] */
        HI_U16     bit01_cec_rx_error            : 1  ; /* [7] */
        HI_U16     bit04_cec_rx_dest_cmd_header  : 4  ; /* [11:8] */
        HI_U16     bit04_cec_rx_init_cmd_header  : 4  ; /* [15:12] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_RX_STATE_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_2               : 16  ; /* [31:16] */

        HI_U16     bit16_cec_auto_ping_start : 1  ; /* [0] */
        HI_U16     bit16_cec_auto_ping_clear : 1  ; /* [1] */
        HI_U16     bit16_cec_auto_ping_done  : 1  ; /* [2] */
        HI_U16     bit16_rsv_1               : 13  ; /* [15:3] */
    } bits;

    /* Define an unsigned member */
    HI_U32     u32;
}REG_CEC_AUTO_DISC_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_6           : 16  ; /* [31:16] */

        HI_U16     bit05_cec_cdc_arb_cnt : 5  ; /* [4:0] */
        HI_U16     bit01_cec_cdc_arb_en  : 1  ; /* [5] */
        HI_U16     bit02_rsv_5           : 2  ; /* [7:6] */
        HI_U16     bit08_cec_cdc_opcode  : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_CDC_CTRL_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_rsv_7             : 16  ; /* [31:16] */

        HI_U16     bit16_cec_auto_ping_map : 16  ; /* [15:0] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_AUTODISC_MAP_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16      bit16_reserved                      : 16 ; /* [31:16] */

        HI_U16      bit04_cec_tx_init_id                : 4  ; /* [03:00] */
        HI_U16      bit12_reserved                      : 12 ; /* [15:04] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_TX_INIT_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16      bit16_reserved                      : 16 ; /* [31:16] */

        HI_U16      bit04_cec_tx_dest_id                : 4  ; /* [03:00] */
        HI_U16      bit01_cec_reg_sd_poll_intern        : 1  ; /* [04] */
        HI_U16      bit11_reserved                      : 11 ; /* [15:05] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_TX_DEST_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit16_reserved                       : 16  ; /* [31:16] */

        HI_U16     bit16_cec_capture_id                 : 16  ; /* [15:0] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_CEC_CAPTUTR_ID_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_tx_cec_operand1                : 8  ; /* [23:16] */
        HI_U16     bit08_tx_cec_operand2                : 8  ; /* [31:24] */

        HI_U16     bit08_tx_cec_command                 : 8  ; /* [7:0] */
        HI_U16     bit08_tx_cec_operand0                : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_TX_CEC_CMD0_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_tx_cec_operand5            : 8  ; /* [23:16] */
        HI_U16     bit08_tx_cec_operand6            : 8  ; /* [31:24] */

        HI_U16     bit08_tx_cec_operand3            : 8  ; /* [7:0] */
        HI_U16     bit08_tx_cec_operand4            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_TX_CEC_CMD1_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_tx_cec_operand9            : 8  ; /* [23:16] */
        HI_U16     bit08_tx_cec_operand10            : 8  ; /* [31:24] */

        HI_U16     bit08_tx_cec_operand7            : 8  ; /* [7:0] */
        HI_U16     bit08_tx_cec_operand8            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_TX_CEC_CMD2_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_tx_cec_operand13            : 8  ; /* [23:16] */
        HI_U16     bit08_tx_cec_operand14            : 8  ; /* [31:24] */

        HI_U16     bit08_tx_cec_operand11            : 8  ; /* [7:0] */
        HI_U16     bit08_tx_cec_operand12            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_TX_CEC_CMD3_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_rx_cec_operand1                : 8  ; /* [23:16] */
        HI_U16     bit08_rx_cec_operand2                : 8  ; /* [31:24] */

        HI_U16     bit08_rx_cec_command                 : 8  ; /* [7:0] */
        HI_U16     bit08_rx_cec_operand0                : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_RX_CEC_CMD0_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_rx_cec_operand5            : 8  ; /* [23:16] */
        HI_U16     bit08_rx_cec_operand6            : 8  ; /* [31:24] */

        HI_U16     bit08_rx_cec_operand3            : 8  ; /* [7:0] */
        HI_U16     bit08_rx_cec_operand4            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_RX_CEC_CMD1_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_rx_cec_operand9            : 8  ; /* [23:16] */
        HI_U16     bit08_rx_cec_operand10            : 8  ; /* [31:24] */

        HI_U16     bit08_rx_cec_operand7            : 8  ; /* [7:0] */
        HI_U16     bit08_rx_cec_operand8            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_RX_CEC_CMD2_U;

typedef union
{
    /* order: u8[2]-u8[3]-u8[0]-u8[1] ; u16[1]-u16[0]*/
    struct
    {
        HI_U16     bit08_rx_cec_operand13            : 8  ; /* [23:16] */
        HI_U16     bit08_rx_cec_operand14            : 8  ; /* [31:24] */

        HI_U16     bit08_rx_cec_operand11            : 8  ; /* [7:0] */
        HI_U16     bit08_rx_cec_operand12            : 8  ; /* [15:8] */
    } bits;

    HI_U8      u8[4];
    HI_U32     u32;
} REG_RX_CEC_CMD3_U;

#define REG_CEC_BASE_ADDR    0xf8ce0000
#define REG_CEC_DEV_INFO     (REG_CEC_BASE_ADDR +  0x4800)
#define REG_CEC_START_PRIOD  (REG_CEC_BASE_ADDR +  0x4804)
#define REG_CEC_TX_CTRL      (REG_CEC_BASE_ADDR +  0x4808)
#define REG_CEC_RX_STATE     (REG_CEC_BASE_ADDR +  0x480C)
#define REG_CEC_AUTO_DISC    (REG_CEC_BASE_ADDR +  0x4810)
#define REG_CEC_CDC_CTRL     (REG_CEC_BASE_ADDR +  0x4814)
#define REG_CEC_AUTODISC_MAP (REG_CEC_BASE_ADDR +  0x4818)
#define REG_CEC_TX_INIT      (REG_CEC_BASE_ADDR +  0x481c)
#define REG_CEC_TX_DEST      (REG_CEC_BASE_ADDR +  0x4820)
#define REG_CEC_CAPTUTR_ID   (REG_CEC_BASE_ADDR +  0x4824)
#define REG_TX_CEC_CMD0      (REG_CEC_BASE_ADDR +  0x4828)
#define REG_TX_CEC_CMD1      (REG_CEC_BASE_ADDR +  0x482C)
#define REG_TX_CEC_CMD2      (REG_CEC_BASE_ADDR +  0x4830)
#define REG_TX_CEC_CMD3      (REG_CEC_BASE_ADDR +  0x4834)
#define REG_RX_CEC_CMD0      (REG_CEC_BASE_ADDR +  0x4838)
#define REG_RX_CEC_CMD1      (REG_CEC_BASE_ADDR +  0x483C)
#define REG_RX_CEC_CMD2      (REG_CEC_BASE_ADDR +  0x4840)
#define REG_RX_CEC_CMD3      (REG_CEC_BASE_ADDR +  0x4844)
#define REG_CEC_OP_ABORT_0   (REG_CEC_BASE_ADDR +  0x4848)
#define REG_CEC_OP_ABORT_1   (REG_CEC_BASE_ADDR +  0x484C)
#define REG_CEC_OP_ABORT_2   (REG_CEC_BASE_ADDR +  0x4850)
#define REG_CEC_OP_ABORT_3   (REG_CEC_BASE_ADDR +  0x4854)
#define REG_CEC_OP_ABORT_4   (REG_CEC_BASE_ADDR +  0x4858)
#define REG_CEC_OP_ABORT_5   (REG_CEC_BASE_ADDR +  0x485C)
#define REG_CEC_OP_ABORT_6   (REG_CEC_BASE_ADDR +  0x4860)
#define REG_CEC_OP_ABORT_7   (REG_CEC_BASE_ADDR +  0x4864)

#endif // __HDMI_MCU_REG_CEC_H__

