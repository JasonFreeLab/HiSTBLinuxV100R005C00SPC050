/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher_reg.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_PLCIPHER_REG_H__
#define __DRV_PLCIPHER_REG_H__

/* add include here */
//#include "hal_plcipher.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef union
{
    struct
    {
        HI_U32 reserved0                        : 3;    // [2:0]
        HI_U32 int_sta_timeout_err              : 1;    // [3]
        HI_U32 int_sta_logic_timeout            : 1;    // [4]
        HI_U32 reserved1                        : 4;    // [8:5]
        HI_U32 int_ista_desc_empty              : 1;    // [9]
        HI_U32 int_ista_desc_out                : 1;    // [10]
        HI_U32 reserved2                        : 6;    // [16:11]
        HI_U32 int_osta_desc_empty              : 1;   // [17]
        HI_U32 reserved3                        : 1;   // [18]
        HI_U32 int_osta_wrbuffer_done           : 1;   // [19]
        HI_U32 reserved4                        : 4;   // [23:20]
        HI_U32 int_ena_all                      : 1;   // [24]
        HI_U32 reserved5                        : 7;   // [31:25]
    } bits;
    HI_U32 u32;
} PLCIPHER_INT_STATUS_U;  //Offset:0x108

typedef PLCIPHER_INT_STATUS_U PLCIPHER_INT_ENABLE_U;
typedef PLCIPHER_INT_STATUS_U PLCIPHER_INT_ORG_STATUS_U;

typedef union
{
    struct
    {
        HI_U32  rsv1:8;
        HI_U32  sw_cw_odd_even: 1;
        HI_U32  sw_cw_channel_id: 4;
        HI_U32  rsv2:3;
        HI_U32  sw_cw_type: 8;
        HI_U32  sw_iv_sel: 1;
        HI_U32  rsv3:   3;
        HI_U32  case_sw_algo_type_ok:1;
        HI_U32  rsv4: 3;

    }bits;
    HI_U32 u32;
}PLCIPHER_CW_SET_U;

/* Define the union U_PL_CHN_PID_FLT_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sw_pid_mode           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PL_CHN_PID_FLT_EN;
//============================以下定义来自FPGA验证代码=========================
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_mmu_en            : 1   ; /* [0]  */
        unsigned int    chnl_pend_int_en      : 1   ; /* [1]  */
        unsigned int    obuf_pack_int_en      : 1   ; /* [2]  */
        unsigned int    obuf_nr_int_en        : 1   ; /* [3]  */
        unsigned int    dma_err_int_en        : 1   ; /* [4]  */
        unsigned int    reserved_0            : 4   ; /* [8..5]  */
        unsigned int    des_end_en            : 1   ; /* [9]  */
        unsigned int    reserved_1            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CTRL;

/* Define the union U_DMA_GLB_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_int_msk           : 1   ; /* [0]  */
        unsigned int    chnl_pend_status      : 1   ; /* [1]  */
        unsigned int    dma_pack_int          : 1   ; /* [2]  */
        unsigned int    dma_obuf_nr_full      : 1   ; /* [3]  */
        unsigned int    reserved_0            : 2   ; /* [5..4]  */
        unsigned int    des_end_status        : 1   ; /* [6]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    dma_bid_err_int       : 1   ; /* [16]  */
        unsigned int    reserved_2            : 1   ; /* [17]  */
        unsigned int    chk_code_err_int      : 1   ; /* [18]  */
        unsigned int    obuf_oflw_err_int     : 1   ; /* [19]  */
        unsigned int    des_type_err_int      : 1   ; /* [20]  */
        unsigned int    ichl_wptr_oflw_err_int : 1   ; /* [21]  */
        unsigned int    reserved_3            : 3   ; /* [24..22]  */
        unsigned int    dma_tlb_err_int       : 1   ; /* [25]  */
        unsigned int    dma_bus_err_int       : 1   ; /* [26]  */
        unsigned int    reserved_4            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_GLB_STAT;

/* Define the union U_DMA_TLB_BASE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    dma_tlb_base          : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_TLB_BASE;

/* Define the union U_DMA_DFX_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chk_code_en           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_DFX_CTRL;

/* Define the union U_CHNL_CHK_CODE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chnl_chk_code          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_CHNL_CHK_CODE;
/* Define the union U_DMA_DESC_END_INT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    des_end_int           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_DESC_END_INT;

/* Define the union U_DMA_CHNL_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_chanls_status     : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_STAT;

/* Define the union U_DMA_CHNL_ENB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_chanls_enb        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_ENB;

/* Define the union U_DMA_CHNL_DIS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_chanls_dis        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    dma_pi_mmu_dis        : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_DIS;

/* Define the union U_DMA_CHNL_PEND_INT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chnls_pending_int     : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_PEND_INT;

/* Define the union U_DMA_CHNL_BASE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    dqct_table_addr       : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_BASE;

/* Define the union U_DMA_CHNL_DEPTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_chnl_depth        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_CHNL_DEPTH;

/* Define the union U_DMA_SLOT_PI_R */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hw_pi_rptr            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    hw_pi_wptr            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 5   ; /* [30..26]  */
        unsigned int    pi_wptr_loopback      : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_SLOT_PI_R;

/* Define the union U_DMA_SLOT_PI_W */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sw_pi_wptr            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    sw_pi_w_bid           : 6   ; /* [21..16]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_SLOT_PI_W;

/* Define the union U_DMA_SLOT_PO_W */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hw_po_wptr            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 7   ; /* [30..24]  */
        unsigned int    po_wptr_loopback      : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_SLOT_PO_W;

/* Define the union U_DMA_SLOT_PO_R */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sw_po_rptr            : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_SLOT_PO_R;

/* Define the union U_DMA_OBUF_ADDR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    dma_obuf_base         : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_ADDR;

/* Define the union U_DMA_OBUF_LEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_length       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_LEN;

/* Define the union U_DMA_OBUF_THRED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_thresh       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_THRED;

/* Define the union U_DMA_OBUF_STAT_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_stat_l       : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_STAT_L;

/* Define the union U_DMA_OBUF_ENB_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_enb_l        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_ENB_L;

/* Define the union U_DMA_OBUF_DIS_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_dis_l        : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_DIS_L;

/* Define the union U_DMA_NR_FULL__L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_nr_full_l         : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_NR_FULL__L;

/* Define the union U_DMA_PACK_INT_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dma_pack_int_l         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DMA_PACK_INT_L;
/* Define the union U_DMA_COAL_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coal_time_cyc         : 16  ; /* [15..0]  */
        unsigned int    coal_cnt_nums         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_COAL_CFG;

/* Define the union U_DMA_OBUF_OVFLW_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    obuf_ovflw_err_int    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_OVFLW_L;

/* Define the union U_DMA_BID_ERR_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bid_err_int_l         : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_BID_ERR_L;

/* Define the union U_DMA_OBUF_MMU_DIS_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_obuf_mmu_dis_l    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_OBUF_MMU_DIS_L;

/* Define the union U_DMA_FSM_DFX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd_split_fsm          : 3   ; /* [2..0]  */
        unsigned int    chn_fet_fsm           : 2   ; /* [4..3]  */
        unsigned int    chn_pl_fsm            : 3   ; /* [7..5]  */
        unsigned int    chn_desc_fsm          : 2   ; /* [9..8]  */
        unsigned int    chn_po_fsm            : 4   ; /* [13..10]  */
        unsigned int    pak_cnt_en            : 1   ; /* [14]  */
        unsigned int    pak_dis_cnt_en        : 1   ; /* [15]  */
        unsigned int    discard_payload_cnt   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_FSM_DFX;

/* Define the union U_DMA_IPAK_DFX */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int in_payload_cnt         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DMA_IPAK_DFX;
/* Define the union U_DMA_OPAK_DFX */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out_payload_cnt        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DMA_OPAK_DFX;
/* Define the union U_DMA_MMU_DFX */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dma_tlb_err_page       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DMA_MMU_DFX;
/* Define the union U_DMA_S_MMU_DFX */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dma_s_tlb_err_page     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DMA_S_MMU_DFX;
/* Define the union U_DMA_AXI_DFX0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_rd_acc_clr        : 1   ; /* [0]  */
        unsigned int    cnt_rd_latency_clr    : 1   ; /* [1]  */
        unsigned int    cnt_wr_acc_clr        : 1   ; /* [2]  */
        unsigned int    cnt_wr_latency_clr    : 1   ; /* [3]  */
        unsigned int    cnt_rd0               : 1   ; /* [4]  */
        unsigned int    reserved_0            : 7   ; /* [11..5]  */
        unsigned int    cnt_wr0               : 1   ; /* [12]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX0;

/* Define the union U_DMA_AXI_DFX1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_rd_latency_max    : 16  ; /* [15..0]  */
        unsigned int    cnt_rd_latency_avg    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX1;

/* Define the union U_DMA_AXI_DFX2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_wr_latency_max    : 16  ; /* [15..0]  */
        unsigned int    cnt_wr_latency_avg    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX2;

/* Define the union U_DMA_AXI_DFX3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_wr_acc0           : 16  ; /* [15..0]  */
        unsigned int    cnt_wr_acc1           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX3;

/* Define the union U_DMA_AXI_DFX4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_rd_acc0           : 16  ; /* [15..0]  */
        unsigned int    cnt_rd_acc1           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX4;

/* Define the union U_DMA_AXI_DFX5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt_rd_otd0           : 8   ; /* [7..0]  */
        unsigned int    cnt_rd_otd1           : 8   ; /* [15..8]  */
        unsigned int    cnt_wr_otd0           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_AXI_DFX5;

/* Define the union U_DMA_BUF_DFX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    opl_pack_cnt_max      : 4   ; /* [3..0]  */
        unsigned int    opl_pack_cnt          : 4   ; /* [7..4]  */
        unsigned int    ipl_pack_cnt_max      : 4   ; /* [11..8]  */
        unsigned int    ipl_pack_cnt          : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_BUF_DFX;

/* Define the union U_DMA_S_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_s_mmu_en          : 1   ; /* [0]  */
        unsigned int    s_chnl_pend_int_en    : 1   ; /* [1]  */
        unsigned int    s_obuf_pack_int_en    : 1   ; /* [2]  */
        unsigned int    s_obuf_nr_int_en      : 1   ; /* [3]  */
        unsigned int    dma_s_err_int_en      : 1   ; /* [4]  */
        unsigned int    reserved_0            : 4   ; /* [8..5]  */
        unsigned int    s_des_end_en          : 1   ; /* [9]  */
        unsigned int    reserved_1            : 14  ; /* [23..10]  */
        unsigned int    dma_s_ci_sel          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_S_CTRL;

/* Define the union U_DMA_S_GLB_STAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dma_s_int_msk         : 1   ; /* [0]  */
        unsigned int    s_chnl_pend_status    : 1   ; /* [1]  */
        unsigned int    dma_s_pack_int        : 1   ; /* [2]  */
        unsigned int    dma_s_obuf_nr_full    : 1   ; /* [3]  */
        unsigned int    reserved_0            : 2   ; /* [5..4]  */
        unsigned int    s_des_end_status      : 1   ; /* [6]  */
        unsigned int    reserved_1            : 9   ; /* [15..7]  */
        unsigned int    dma_s_bid_err         : 1   ; /* [16]  */
        unsigned int    reserved_2            : 8   ; /* [24..17]  */
        unsigned int    dma_s_tlb_err         : 1   ; /* [25]  */
        unsigned int    dma_s_bus_err         : 1   ; /* [26]  */
        unsigned int    reserved_3            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_S_GLB_STAT;

/* Define the union U_DMA_S_TLB_BASE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    dma_s_tlb_base        : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_S_TLB_BASE;

/* Define the union U_DMA_S_COAL_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    s_coal_time_cyc       : 16  ; /* [15..0]  */
        unsigned int    s_coal_cnt_nums       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_S_COAL_CFG;

/* Define the union U_DMA_S_COAL_UNIT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    s_coal_pulse_cyc      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DMA_S_COAL_UNIT;

//==============================================================================

extern  HI_VOID * g_u32PLCipherRegBase;

#define PLCIPHER_REG_BASE_ADDR                   g_u32PLCipherRegBase //ioremap_nocache(0xF9A40000)

#define PL_GLB_CFG   ( 0x0000)
#define RAM_CKGT ( 0x0008)
#define PL_CHN_PID_FLT_EN ( 0x0010)

//====================================================
#define CW_SET ( 0x0200)

#define CW_WORD(WordNo)  (0x0204 + ((WordNo) << 2))

#define CA_INFO ( 0x0214)

#define DEBUG_REG ( 0x0400)
#define PID_CHN_CFG(ChanId,PIDNo)  (0x1000 + ((ChanId) << 8) + ((PIDNo) << 2)) /*0x1000 + 0x100*j + 4*i*/

//====================================================
#define DMA_CTRL (0x4000)
#define DMA_GLB_STAT (0x4004)
#define DMA_TLB_BASE (0x4010)
#define DMA_DFX_CTRL (0x4020)

#define DMA_CHNL_STAT (0x4030)
#define DMA_CHNL_ENB (0x4034)
#define DMA_CHNL_DIS (0x4038)
#define DMA_CHNL_BASE(ChanId) (0x4050 + ((ChanId) << 2))
#define DMA_CHNL_DEPTH(ChanId) (0x40C0 + ((ChanId) << 2))

#define DMA_SLOT_PI_R(ChanId) (0x4200 + ((ChanId) << 2))
#define DMA_SLOT_PI_W         (0x4280 )
#define DMA_SLOT_PO_W(ChanId) (0x4300 + ((ChanId) << 2))
#define DMA_SLOT_PO_R(ChanId) (0x4400 + ((ChanId) << 2))
#define DMA_OBUF_ADDR(ChanId) (0x4500 + ((ChanId) << 2))

#define DMA_OBUF_LEN(ChanId) (0x4600 + ((ChanId) << 2))
#define DMA_OBUF_STAT_L (0x4800)
#define DMA_OBUF_ENB_L (0x4808)
#define DMA_OBUF_DIS_L (0x4810)
#define DMA_PACK_INT_L (0x4820)


#define DMA_COAL_CFG        (0x4830)
#define DMA_OBUF_OVFLW_L    (0x4840)
#define DMA_BID_ERR_L       (0x4848)
#define DMA_OBUF_MMU_DIS_L  (0x4850)
#define DMA_IPAK_DFX        (0x48A8)
#define DMA_OPAK_DFX        (0x48Ac)
#define DMA_MMU_DFX         (0x48B0)

#define DMA_S_CTRL (0x4900)
#define DMA_S_GLB_STAT (0x4904)
#define DMA_S_TLB_BASE (0x4908)
#define DMA_S_COAL_CFG (0x490c)
#define DMA_S_COAL_UNIT (0x4910)

#ifdef __cplusplus
}
#endif
#endif /* end #ifndef __DRV_PLCIPHER_REG_H__ */

