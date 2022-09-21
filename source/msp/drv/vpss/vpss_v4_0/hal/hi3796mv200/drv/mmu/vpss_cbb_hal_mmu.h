/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_cfgreg.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/25
  Last Modified :
  Description   : vpss_cfgreg.c header file
  Function List :
  History       :
  1.Date        : 2016/1/25
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __VPSS_CBB_HAL_MMU_H__
#define __VPSS_CBB_HAL_MMU_H__
#include "hi_type.h"
//#include "vpss_reg.h"
#include "vpss_cbb_common.h"


/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if 1
extern HI_VOID VPSS_DRV_Set_SMMU_CB_TTBR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cb_ttbr );
extern HI_VOID VPSS_DRV_Set_SMMU_ERR_RDADDR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_ns_rd_addr );
extern HI_VOID VPSS_DRV_Set_SMMU_ERR_RDADDR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_s_rd_addr );
extern HI_VOID VPSS_DRV_Set_SMMU_ERR_WRADDR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_ns_wr_addr );
extern HI_VOID VPSS_DRV_Set_SMMU_ERR_WRADDR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_s_wr_addr );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_PTW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_ptw_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_PTW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_ptw_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_rd_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_rd_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_wr_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_wr_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_PTW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_strm_id_ns , HI_U32
        fault_index_id_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_PTW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_strm_id_s , HI_U32
        fault_index_id_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_rd_ns , HI_U32
        fault_index_id_rd_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_rd_s , HI_U32
        fault_index_id_rd_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_wr_ns , HI_U32
        fault_index_id_wr_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_wr_s , HI_U32
        fault_index_id_wr_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_PTW_NUM(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_ns_ptw_num , HI_U32
        fault_s_ptw_num );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TBU_DBG(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 read_command_counter , HI_U32
        arch_stall_n , HI_U32 tbu_arreadym , HI_U32 ar_readys , HI_U32 ar_valids , HI_U32 write_command_counter , HI_U32
        awch_stall_n , HI_U32 tbu_awreadym , HI_U32 aw_readys , HI_U32 aw_valids );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TBU_INFO(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tbu_num , HI_U32
        fault_tlbinvalid_err_ns , HI_U32 fault_tlbmiss_err_ns , HI_U32 fault_tlbinvalid_err_s , HI_U32 fault_tlbmiss_err_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_rd_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_rd_s );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_wr_ns );
extern HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_wr_s );
extern HI_VOID VPSS_DRV_Set_SMMU_INTCLR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_clr , HI_U32
        intns_tlbinvalid_rd_clr , HI_U32 intns_ptw_trans_clr , HI_U32 intns_tlbmiss_clr );
extern HI_VOID VPSS_DRV_Set_SMMU_INTCLR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_clr , HI_U32
        ints_tlbinvalid_rd_clr , HI_U32 ints_ptw_trans_clr , HI_U32 ints_tlbmiss_clr );
extern HI_VOID VPSS_DRV_Set_SMMU_INTMASK_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_msk , HI_U32
        intns_tlbinvalid_rd_msk , HI_U32 intns_ptw_trans_msk , HI_U32 intns_tlbmiss_msk );
extern HI_VOID VPSS_DRV_Set_SMMU_INTMASK_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_msk , HI_U32
        ints_tlbinvalid_rd_msk , HI_U32 ints_ptw_trans_msk , HI_U32 ints_tlbmiss_msk );
extern HI_VOID VPSS_DRV_Set_SMMU_INTRAW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_raw , HI_U32
        intns_tlbinvalid_rd_raw , HI_U32 intns_ptw_trans_raw , HI_U32 intns_tlbmiss_raw );
extern HI_VOID VPSS_DRV_Set_SMMU_INTRAW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_raw , HI_U32
        ints_tlbinvalid_rd_raw , HI_U32 ints_ptw_trans_raw , HI_U32 ints_tlbmiss_raw );
extern HI_VOID VPSS_DRV_Set_SMMU_INTSTAT_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_stat , HI_U32
        intns_tlbinvalid_rd_stat , HI_U32 intns_ptw_trans_stat , HI_U32 intns_tlbmiss_stat );
extern HI_VOID VPSS_DRV_Set_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_stat , HI_U32
        ints_tlbinvalid_rd_stat , HI_U32 ints_ptw_trans_stat , HI_U32 ints_tlbmiss_stat );
extern HI_VOID VPSS_DRV_Set_SMMU_LP_CTRL(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 auto_clk_gt_en );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG0(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 in_out_cmd_cnt_rd , HI_U32 rdy_debug_rd ,
        HI_U32 vld_debug_rd , HI_U32 cur_miss_cnt_rd , HI_U32 last_miss_cnt_rd );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG1(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 in_out_cmd_cnt_wr , HI_U32 rdy_debug_wr ,
        HI_U32 vld_debug_wr , HI_U32 cur_miss_cnt_wr , HI_U32 last_miss_cnt_wr );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG2(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_double_upd_cnt_rd , HI_U32
        last_double_upd_cnt_rd , HI_U32 cur_double_miss_cnt_rd , HI_U32 last_double_miss_cnt_rd );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG3(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 mst_fsm_cur , HI_U32 cur_double_upd_cnt_wr
        , HI_U32 last_double_upd_cnt_wr , HI_U32 cur_double_miss_cnt_wr , HI_U32 last_double_miss_cnt_wr );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG4(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel1_chn_miss_cnt_rd , HI_U32
        last_sel1_chn_miss_cnt_rd );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG5(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel2_chn_miss_cnt_rd , HI_U32
        last_sel2_chn_miss_cnt_rd );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG6(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel1_chn_miss_cnt_wr , HI_U32
        last_sel1_chn_miss_cnt_wr );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG7(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel2_chn_miss_cnt_wr , HI_U32
        last_sel2_chn_miss_cnt_wr );
extern HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG8(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 sel1_chn_rd , HI_U32 sel2_chn_rd , HI_U32
        sel1_chn_wr , HI_U32 sel2_chn_wr );
extern HI_VOID VPSS_DRV_Set_SMMU_PREF_BUFFER_EMPTY(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 pref_buffer_empty );
extern HI_VOID VPSS_DRV_Set_SMMU_PTWQ_IDLE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ptwq15_idle_state , HI_U32 ptwq14_idle_state
        , HI_U32 ptwq13_idle_state , HI_U32 ptwq12_idle_state , HI_U32 ptwq11_idle_state , HI_U32 ptwq10_idle_state , HI_U32
        ptwq9_idle_state , HI_U32 ptwq8_idle_state , HI_U32 ptwq7_idle_state , HI_U32 ptwq6_idle_state , HI_U32 ptwq5_idle_state ,
        HI_U32 ptwq4_idle_state , HI_U32 ptwq3_idle_state , HI_U32 ptwq2_idle_state , HI_U32 ptwq1_idle_state , HI_U32
        ptwq0_idle_state );
extern HI_VOID VPSS_DRV_Set_SMMU_RESET_STATE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 smmu_rst_state );
extern HI_VOID VPSS_DRV_Set_SMMU_SCB_TTBR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scb_ttbr );
extern HI_VOID VPSS_DRV_Set_SMMU_SCR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ptw_pf , HI_U32 int_en , HI_U32 glb_bypass );
#endif

HI_VOID VPSS_Mmu_SetWchBypassFlag(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 u32Flag);
HI_VOID VPSS_Mmu_SetRchBypassFlag(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 u32Flag);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

