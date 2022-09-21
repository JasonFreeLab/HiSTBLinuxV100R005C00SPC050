//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"

#if 1
//addr=0xf000
HI_VOID VPSS_DRV_Set_SMMU_SCR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ptw_pf , HI_U32 int_en , HI_U32 glb_bypass )
{
    U_VPSS_SMMU_SCR VPSS_SMMU_SCR;

    VPSS_SMMU_SCR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_SCR.u32));
    VPSS_SMMU_SCR.bits.ptw_pf     = ptw_pf     ;
    VPSS_SMMU_SCR.bits.int_en     = int_en     ;
    VPSS_SMMU_SCR.bits.glb_bypass = glb_bypass ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_SCR.u32), VPSS_SMMU_SCR.u32);

    return;
}
//addr=0xf008
HI_VOID VPSS_DRV_Set_SMMU_LP_CTRL(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 auto_clk_gt_en )
{
    U_VPSS_SMMU_LP_CTRL VPSS_SMMU_LP_CTRL;

    VPSS_SMMU_LP_CTRL.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_LP_CTRL.u32));
    VPSS_SMMU_LP_CTRL.bits.auto_clk_gt_en = auto_clk_gt_en ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_LP_CTRL.u32), VPSS_SMMU_LP_CTRL.u32);

    return;
}
//addr=0xf010
HI_VOID VPSS_DRV_Set_SMMU_INTMASK_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_msk , HI_U32
                                    ints_tlbinvalid_rd_msk , HI_U32 ints_ptw_trans_msk , HI_U32 ints_tlbmiss_msk )
{
    U_VPSS_SMMU_INTMASK_S VPSS_SMMU_INTMASK_S;

    VPSS_SMMU_INTMASK_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTMASK_S.u32));
    VPSS_SMMU_INTMASK_S.bits.ints_tlbinvalid_wr_msk    = ints_tlbinvalid_wr_msk ;
    VPSS_SMMU_INTMASK_S.bits.ints_tlbinvalid_rd_msk    = ints_tlbinvalid_rd_msk ;
    VPSS_SMMU_INTMASK_S.bits.ints_ptw_trans_msk     = ints_ptw_trans_msk     ;
    VPSS_SMMU_INTMASK_S.bits.ints_tlbmiss_msk       = ints_tlbmiss_msk       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTMASK_S.u32), VPSS_SMMU_INTMASK_S.u32);

    return;
}
//addr=0xf014
HI_VOID VPSS_DRV_Set_SMMU_INTRAW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_raw , HI_U32
                                   ints_tlbinvalid_rd_raw , HI_U32 ints_ptw_trans_raw , HI_U32 ints_tlbmiss_raw )
{
    U_VPSS_SMMU_INTRAW_S VPSS_SMMU_INTRAW_S;

    VPSS_SMMU_INTRAW_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTRAW_S.u32));
    VPSS_SMMU_INTRAW_S.bits.ints_tlbinvalid_wr_raw = ints_tlbinvalid_wr_raw ;
    VPSS_SMMU_INTRAW_S.bits.ints_tlbinvalid_rd_raw = ints_tlbinvalid_rd_raw ;
    VPSS_SMMU_INTRAW_S.bits.ints_ptw_trans_raw     = ints_ptw_trans_raw     ;
    VPSS_SMMU_INTRAW_S.bits.ints_tlbmiss_raw       = ints_tlbmiss_raw       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTRAW_S.u32), VPSS_SMMU_INTRAW_S.u32);

    return;
}
//addr=0xf018
HI_VOID VPSS_DRV_Set_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_stat , HI_U32
                                    ints_tlbinvalid_rd_stat , HI_U32 ints_ptw_trans_stat , HI_U32 ints_tlbmiss_stat )
{
    U_VPSS_SMMU_INTSTAT_S VPSS_SMMU_INTSTAT_S;

    VPSS_SMMU_INTSTAT_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_S.u32));
    VPSS_SMMU_INTSTAT_S.bits.ints_tlbinvalid_wr_stat = ints_tlbinvalid_wr_stat ;
    VPSS_SMMU_INTSTAT_S.bits.ints_tlbinvalid_rd_stat = ints_tlbinvalid_rd_stat ;
    VPSS_SMMU_INTSTAT_S.bits.ints_ptw_trans_stat     = ints_ptw_trans_stat     ;
    VPSS_SMMU_INTSTAT_S.bits.ints_tlbmiss_stat       = ints_tlbmiss_stat       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_S.u32), VPSS_SMMU_INTSTAT_S.u32);

    return;
}

HI_S32 VPSS_DRV_Get_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 *pu32SecureState, HI_U32 *pu32NoSecureState)
{
    U_VPSS_SMMU_INTSTAT_S VPSS_SMMU_INTSTAT_S;
    U_VPSS_SMMU_INTSTAT_NS VPSS_SMMU_INTSTAT_NS;

    VPSS_SMMU_INTSTAT_S.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_S.u32));

    *pu32SecureState = VPSS_SMMU_INTSTAT_S.u32;

    VPSS_SMMU_INTSTAT_NS.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_NS.u32));

    *pu32NoSecureState = VPSS_SMMU_INTSTAT_NS.u32;

#if 1
    if (0 != VPSS_SMMU_INTSTAT_NS.u32)
    {
        HI_U32 SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM;
        HI_U32 SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS;
        HI_U32 SMMU_FAULT_ADDR_WR_NS, SMMU_FAULT_TLB_WR_NS, SMMU_FAULT_ID_WR_NS;

        VPSS_FATAL("SMMU, S-int:%u, NS-int:%u\n", VPSS_SMMU_INTSTAT_S.u32, VPSS_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_NS  = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_NS.u32));
        SMMU_FAULT_ID_PTW_NS    = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_NS.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_NS   = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_NS.u32));
        SMMU_FAULT_TLB_RD_NS    = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_NS.u32));
        SMMU_FAULT_ID_RD_NS     = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_NS.u32));

        VPSS_FATAL("SMMU_FAULT_ADDR_PTW_NS:%x (%u) \nSMMU_FAULT_ID_PTW_NS:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                   SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM);
        VPSS_FATAL("SMMU_FAULT_ADDR_RD_NS:%x (%u) \nSMMU_FAULT_TLB_RD_NS:%u \nSMMU_FAULT_ID_RD_NS:%u\n",
                   SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS);
        SMMU_FAULT_ADDR_WR_NS = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_NS.u32));
        SMMU_FAULT_TLB_WR_NS = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_NS.u32));
        SMMU_FAULT_ID_WR_NS = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_NS.u32));
        VPSS_FATAL("SMMU_FAULT_ADDR_WR_NS:%x (%u)\nSMMU_FAULT_TLB_WR_NS:%u\nSMMU_FAULT_ID_WR_NS:%u\n",
                   SMMU_FAULT_ADDR_WR_NS, SMMU_FAULT_ADDR_WR_NS,
                   SMMU_FAULT_TLB_WR_NS,
                   SMMU_FAULT_ID_WR_NS);
    }

    if (0 != VPSS_SMMU_INTSTAT_S.u32)
    {
        HI_U32 SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ID_PTW_S, SMMU_FAULT_PTW_NUM;
        HI_U32 SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_TLB_RD_S, SMMU_FAULT_ID_RD_S;
        HI_U32 SMMU_FAULT_ADDR_WR_S, SMMU_FAULT_TLB_WR_S,   SMMU_FAULT_ID_WR_S;
        HI_U32 SMMU_SCB_TTBR;

        VPSS_FATAL("SMMU, S-int:%u, NS-int:%u\n", VPSS_SMMU_INTSTAT_S.u32, VPSS_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_S   = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_S.u32));
        SMMU_FAULT_ID_PTW_S     = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_S.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_S    = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_S.u32));
        SMMU_FAULT_TLB_RD_S     = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_S.u32));
        SMMU_FAULT_ID_RD_S      = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_S.u32));
        SMMU_SCB_TTBR           = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_SCB_TTBR.u32));


        VPSS_FATAL("SMMU_FAULT_ADDR_PTW_S:%x (%u) \nSMMU_FAULT_ID_PTW_S:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                   SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ID_PTW_S, SMMU_FAULT_PTW_NUM);
        VPSS_FATAL("SMMU_FAULT_ADDR_RD_S:%x (%u) \nSMMU_FAULT_TLB_RD_S:%u \nSMMU_FAULT_ID_RD_S:%u\n",
                   SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_TLB_RD_S, SMMU_FAULT_ID_RD_S);
        SMMU_FAULT_ADDR_WR_S = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_S.u32));
        SMMU_FAULT_TLB_WR_S = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_S.u32));
        SMMU_FAULT_ID_WR_S = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_S.u32));
        VPSS_FATAL("SMMU_FAULT_ADDR_WR_S:%x (%u)\nSMMU_FAULT_TLB_WR_S:%u\nSMMU_FAULT_ID_WR_S:%u\nSMMU_SCB_TTBR:%x\n",
                   SMMU_FAULT_ADDR_WR_S, SMMU_FAULT_ADDR_WR_S,
                   SMMU_FAULT_TLB_WR_S,
                   SMMU_FAULT_ID_WR_S,
                   SMMU_SCB_TTBR);
    }
#endif

    return HI_SUCCESS;
}

//addr=0xf01c
HI_VOID VPSS_DRV_Set_SMMU_INTCLR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ints_tlbinvalid_wr_clr , HI_U32
                                   ints_tlbinvalid_rd_clr , HI_U32 ints_ptw_trans_clr , HI_U32 ints_tlbmiss_clr )
{
    U_VPSS_SMMU_INTCLR_S VPSS_SMMU_INTCLR_S;

    VPSS_SMMU_INTCLR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTCLR_S.u32));
    VPSS_SMMU_INTCLR_S.bits.ints_tlbinvalid_wr_clr = ints_tlbinvalid_wr_clr ;
    VPSS_SMMU_INTCLR_S.bits.ints_tlbinvalid_rd_clr = ints_tlbinvalid_rd_clr ;
    VPSS_SMMU_INTCLR_S.bits.ints_ptw_trans_clr     = ints_ptw_trans_clr     ;
    VPSS_SMMU_INTCLR_S.bits.ints_tlbmiss_clr       = ints_tlbmiss_clr       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTCLR_S.u32), VPSS_SMMU_INTCLR_S.u32);

    return;
}
//addr=0xf020
HI_VOID VPSS_DRV_Set_SMMU_INTMASK_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_msk , HI_U32
                                     intns_tlbinvalid_rd_msk , HI_U32 intns_ptw_trans_msk , HI_U32 intns_tlbmiss_msk )
{
    U_VPSS_SMMU_INTMASK_NS VPSS_SMMU_INTMASK_NS;

    VPSS_SMMU_INTMASK_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTMASK_NS.u32));
    VPSS_SMMU_INTMASK_NS.bits.intns_tlbinvalid_wr_msk = intns_tlbinvalid_wr_msk ;
    VPSS_SMMU_INTMASK_NS.bits.intns_tlbinvalid_rd_msk = intns_tlbinvalid_rd_msk ;
    VPSS_SMMU_INTMASK_NS.bits.intns_ptw_trans_msk     = intns_ptw_trans_msk     ;
    VPSS_SMMU_INTMASK_NS.bits.intns_tlbmiss_msk       = intns_tlbmiss_msk       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTMASK_NS.u32), VPSS_SMMU_INTMASK_NS.u32);

    return;
}
//addr=0xf024
HI_VOID VPSS_DRV_Set_SMMU_INTRAW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_raw , HI_U32
                                    intns_tlbinvalid_rd_raw , HI_U32 intns_ptw_trans_raw , HI_U32 intns_tlbmiss_raw )
{
    U_VPSS_SMMU_INTRAW_NS VPSS_SMMU_INTRAW_NS;

    VPSS_SMMU_INTRAW_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTRAW_NS.u32));
    VPSS_SMMU_INTRAW_NS.bits.intns_tlbinvalid_wr_raw = intns_tlbinvalid_wr_raw ;
    VPSS_SMMU_INTRAW_NS.bits.intns_tlbinvalid_rd_raw = intns_tlbinvalid_rd_raw ;
    VPSS_SMMU_INTRAW_NS.bits.intns_ptw_trans_raw     = intns_ptw_trans_raw     ;
    VPSS_SMMU_INTRAW_NS.bits.intns_tlbmiss_raw       = intns_tlbmiss_raw       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTRAW_NS.u32), VPSS_SMMU_INTRAW_NS.u32);

    return;
}
//addr=0xf028
HI_VOID VPSS_DRV_Set_SMMU_INTSTAT_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_stat , HI_U32
                                     intns_tlbinvalid_rd_stat , HI_U32 intns_ptw_trans_stat , HI_U32 intns_tlbmiss_stat )
{
    U_VPSS_SMMU_INTSTAT_NS VPSS_SMMU_INTSTAT_NS;

    VPSS_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_NS.u32));
    VPSS_SMMU_INTSTAT_NS.bits.intns_tlbinvalid_wr_stat = intns_tlbinvalid_wr_stat ;
    VPSS_SMMU_INTSTAT_NS.bits.intns_tlbinvalid_rd_stat = intns_tlbinvalid_rd_stat ;
    VPSS_SMMU_INTSTAT_NS.bits.intns_ptw_trans_stat     = intns_ptw_trans_stat     ;
    VPSS_SMMU_INTSTAT_NS.bits.intns_tlbmiss_stat       = intns_tlbmiss_stat       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTSTAT_NS.u32), VPSS_SMMU_INTSTAT_NS.u32);

    return;
}
//addr=0xf02c
HI_VOID VPSS_DRV_Set_SMMU_INTCLR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 intns_tlbinvalid_wr_clr , HI_U32
                                    intns_tlbinvalid_rd_clr , HI_U32 intns_ptw_trans_clr , HI_U32 intns_tlbmiss_clr )
{
    U_VPSS_SMMU_INTCLR_NS VPSS_SMMU_INTCLR_NS;

    VPSS_SMMU_INTCLR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTCLR_NS.u32));
    VPSS_SMMU_INTCLR_NS.bits.intns_tlbinvalid_wr_clr = intns_tlbinvalid_wr_clr ;
    VPSS_SMMU_INTCLR_NS.bits.intns_tlbinvalid_rd_clr = intns_tlbinvalid_rd_clr ;
    VPSS_SMMU_INTCLR_NS.bits.intns_ptw_trans_clr     = intns_ptw_trans_clr     ;
    VPSS_SMMU_INTCLR_NS.bits.intns_tlbmiss_clr       = intns_tlbmiss_clr       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_INTCLR_NS.u32), VPSS_SMMU_INTCLR_NS.u32);

    return;
}
//addr=0xf208
HI_VOID VPSS_DRV_Set_SMMU_SCB_TTBR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scb_ttbr )
{
    U_VPSS_SMMU_SCB_TTBR VPSS_SMMU_SCB_TTBR;

    VPSS_SMMU_SCB_TTBR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_SCB_TTBR.u32));
    VPSS_SMMU_SCB_TTBR.bits.scb_ttbr = scb_ttbr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_SCB_TTBR.u32), VPSS_SMMU_SCB_TTBR.u32);

    return;
}
//addr=0xf20c
HI_VOID VPSS_DRV_Set_SMMU_CB_TTBR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cb_ttbr )
{
    U_VPSS_SMMU_CB_TTBR VPSS_SMMU_CB_TTBR;

    VPSS_SMMU_CB_TTBR.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_CB_TTBR.u32));
    VPSS_SMMU_CB_TTBR.bits.cb_ttbr = cb_ttbr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_CB_TTBR.u32), VPSS_SMMU_CB_TTBR.u32);

    return;
}
//addr=0xf2f0
HI_VOID VPSS_DRV_Set_SMMU_ERR_RDADDR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_s_rd_addr )
{
    U_VPSS_SMMU_ERR_RDADDR_S VPSS_SMMU_ERR_RDADDR_S;

    VPSS_SMMU_ERR_RDADDR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_RDADDR_S.u32));
    VPSS_SMMU_ERR_RDADDR_S.bits.err_s_rd_addr = err_s_rd_addr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_RDADDR_S.u32), VPSS_SMMU_ERR_RDADDR_S.u32);

    return;
}
//addr=0xf2f4
HI_VOID VPSS_DRV_Set_SMMU_ERR_WRADDR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_s_wr_addr )
{
    U_VPSS_SMMU_ERR_WRADDR_S VPSS_SMMU_ERR_WRADDR_S;

    VPSS_SMMU_ERR_WRADDR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_WRADDR_S.u32));
    VPSS_SMMU_ERR_WRADDR_S.bits.err_s_wr_addr = err_s_wr_addr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_WRADDR_S.u32), VPSS_SMMU_ERR_WRADDR_S.u32);

    return;
}
//addr=0xf304
HI_VOID VPSS_DRV_Set_SMMU_ERR_RDADDR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_ns_rd_addr )
{
    U_VPSS_SMMU_ERR_RDADDR_NS VPSS_SMMU_ERR_RDADDR_NS;

    VPSS_SMMU_ERR_RDADDR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_RDADDR_NS.u32));
    VPSS_SMMU_ERR_RDADDR_NS.bits.err_ns_rd_addr = err_ns_rd_addr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_RDADDR_NS.u32), VPSS_SMMU_ERR_RDADDR_NS.u32);

    return;
}
//addr=0xf308
HI_VOID VPSS_DRV_Set_SMMU_ERR_WRADDR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 err_ns_wr_addr )
{
    U_VPSS_SMMU_ERR_WRADDR_NS VPSS_SMMU_ERR_WRADDR_NS;

    VPSS_SMMU_ERR_WRADDR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_WRADDR_NS.u32));
    VPSS_SMMU_ERR_WRADDR_NS.bits.err_ns_wr_addr = err_ns_wr_addr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_ERR_WRADDR_NS.u32), VPSS_SMMU_ERR_WRADDR_NS.u32);

    return;
}
//addr=0xf310
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_PTW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_ptw_s )
{
    U_VPSS_SMMU_FAULT_ADDR_PTW_S VPSS_SMMU_FAULT_ADDR_PTW_S;

    VPSS_SMMU_FAULT_ADDR_PTW_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_S.u32));
    VPSS_SMMU_FAULT_ADDR_PTW_S.bits.fault_addr_ptw_s = fault_addr_ptw_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_S.u32), VPSS_SMMU_FAULT_ADDR_PTW_S.u32);

    return;
}
//addr=0xf314
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_PTW_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_strm_id_s , HI_U32
        fault_index_id_s )
{
    U_VPSS_SMMU_FAULT_ID_PTW_S VPSS_SMMU_FAULT_ID_PTW_S;

    VPSS_SMMU_FAULT_ID_PTW_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_S.u32));
    VPSS_SMMU_FAULT_ID_PTW_S.bits.fault_strm_id_s  = fault_strm_id_s  ;
    VPSS_SMMU_FAULT_ID_PTW_S.bits.fault_index_id_s = fault_index_id_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_S.u32), VPSS_SMMU_FAULT_ID_PTW_S.u32);

    return;
}
//addr=0xf320
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_PTW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_ptw_ns )
{
    U_VPSS_SMMU_FAULT_ADDR_PTW_NS VPSS_SMMU_FAULT_ADDR_PTW_NS;

    VPSS_SMMU_FAULT_ADDR_PTW_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_NS.u32));
    VPSS_SMMU_FAULT_ADDR_PTW_NS.bits.fault_addr_ptw_ns = fault_addr_ptw_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_PTW_NS.u32), VPSS_SMMU_FAULT_ADDR_PTW_NS.u32);

    return;
}
//addr=0xf324
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_PTW_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_strm_id_ns , HI_U32
        fault_index_id_ns )
{
    U_VPSS_SMMU_FAULT_ID_PTW_NS VPSS_SMMU_FAULT_ID_PTW_NS;

    VPSS_SMMU_FAULT_ID_PTW_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_NS.u32));
    VPSS_SMMU_FAULT_ID_PTW_NS.bits.fault_strm_id_ns  = fault_strm_id_ns  ;
    VPSS_SMMU_FAULT_ID_PTW_NS.bits.fault_index_id_ns = fault_index_id_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_PTW_NS.u32), VPSS_SMMU_FAULT_ID_PTW_NS.u32);

    return;
}
//addr=0xf328
HI_VOID VPSS_DRV_Set_SMMU_FAULT_PTW_NUM(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_ns_ptw_num , HI_U32
                                        fault_s_ptw_num )
{
    U_VPSS_SMMU_FAULT_PTW_NUM VPSS_SMMU_FAULT_PTW_NUM;

    VPSS_SMMU_FAULT_PTW_NUM.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_PTW_NUM.u32));
    VPSS_SMMU_FAULT_PTW_NUM.bits.fault_ns_ptw_num = fault_ns_ptw_num ;
    VPSS_SMMU_FAULT_PTW_NUM.bits.fault_s_ptw_num  = fault_s_ptw_num  ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_PTW_NUM.u32), VPSS_SMMU_FAULT_PTW_NUM.u32);

    return;
}
//addr=0xf330
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_wr_s )
{
    U_VPSS_SMMU_FAULT_ADDR_WR_S VPSS_SMMU_FAULT_ADDR_WR_S;

    VPSS_SMMU_FAULT_ADDR_WR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_S.u32));
    VPSS_SMMU_FAULT_ADDR_WR_S.bits.fault_addr_wr_s = fault_addr_wr_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_S.u32), VPSS_SMMU_FAULT_ADDR_WR_S.u32);

    return;
}
//addr=0xf334
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_wr_s )
{
    U_VPSS_SMMU_FAULT_TLB_WR_S VPSS_SMMU_FAULT_TLB_WR_S;

    VPSS_SMMU_FAULT_TLB_WR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_S.u32));
    VPSS_SMMU_FAULT_TLB_WR_S.bits.fault_tlb_wr_s = fault_tlb_wr_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_S.u32), VPSS_SMMU_FAULT_TLB_WR_S.u32);

    return;
}
//addr=0xf338
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_WR_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_wr_s , HI_U32
                                        fault_index_id_wr_s )
{
    U_VPSS_SMMU_FAULT_ID_WR_S VPSS_SMMU_FAULT_ID_WR_S;

    VPSS_SMMU_FAULT_ID_WR_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_S.u32));
    VPSS_SMMU_FAULT_ID_WR_S.bits.fault_str_id_wr_s   = fault_str_id_wr_s   ;
    VPSS_SMMU_FAULT_ID_WR_S.bits.fault_index_id_wr_s = fault_index_id_wr_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_S.u32), VPSS_SMMU_FAULT_ID_WR_S.u32);

    return;
}
//addr=0xf340
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_wr_ns )
{
    U_VPSS_SMMU_FAULT_ADDR_WR_NS VPSS_SMMU_FAULT_ADDR_WR_NS;

    VPSS_SMMU_FAULT_ADDR_WR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_NS.u32));
    VPSS_SMMU_FAULT_ADDR_WR_NS.bits.fault_addr_wr_ns = fault_addr_wr_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_WR_NS.u32), VPSS_SMMU_FAULT_ADDR_WR_NS.u32);

    return;
}
//addr=0xf344
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_wr_ns )
{
    U_VPSS_SMMU_FAULT_TLB_WR_NS VPSS_SMMU_FAULT_TLB_WR_NS;

    VPSS_SMMU_FAULT_TLB_WR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_NS.u32));
    VPSS_SMMU_FAULT_TLB_WR_NS.bits.fault_tlb_wr_ns = fault_tlb_wr_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_WR_NS.u32), VPSS_SMMU_FAULT_TLB_WR_NS.u32);

    return;
}
//addr=0xf348
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_WR_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_wr_ns , HI_U32
        fault_index_id_wr_ns )
{
    U_VPSS_SMMU_FAULT_ID_WR_NS VPSS_SMMU_FAULT_ID_WR_NS;

    VPSS_SMMU_FAULT_ID_WR_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_NS.u32));
    VPSS_SMMU_FAULT_ID_WR_NS.bits.fault_str_id_wr_ns   = fault_str_id_wr_ns   ;
    VPSS_SMMU_FAULT_ID_WR_NS.bits.fault_index_id_wr_ns = fault_index_id_wr_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_WR_NS.u32), VPSS_SMMU_FAULT_ID_WR_NS.u32);

    return;
}
//addr=0xf350
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_rd_s )
{
    U_VPSS_SMMU_FAULT_ADDR_RD_S VPSS_SMMU_FAULT_ADDR_RD_S;

    VPSS_SMMU_FAULT_ADDR_RD_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_S.u32));
    VPSS_SMMU_FAULT_ADDR_RD_S.bits.fault_addr_rd_s = fault_addr_rd_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_S.u32), VPSS_SMMU_FAULT_ADDR_RD_S.u32);

    return;
}
//addr=0xf354
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_rd_s )
{
    U_VPSS_SMMU_FAULT_TLB_RD_S VPSS_SMMU_FAULT_TLB_RD_S;

    VPSS_SMMU_FAULT_TLB_RD_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_S.u32));
    VPSS_SMMU_FAULT_TLB_RD_S.bits.fault_tlb_rd_s = fault_tlb_rd_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_S.u32), VPSS_SMMU_FAULT_TLB_RD_S.u32);

    return;
}
//addr=0xf358
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_RD_S(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_rd_s , HI_U32
                                        fault_index_id_rd_s )
{
    U_VPSS_SMMU_FAULT_ID_RD_S VPSS_SMMU_FAULT_ID_RD_S;

    VPSS_SMMU_FAULT_ID_RD_S.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_S.u32));
    VPSS_SMMU_FAULT_ID_RD_S.bits.fault_str_id_rd_s   = fault_str_id_rd_s   ;
    VPSS_SMMU_FAULT_ID_RD_S.bits.fault_index_id_rd_s = fault_index_id_rd_s ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_S.u32), VPSS_SMMU_FAULT_ID_RD_S.u32);

    return;
}
//addr=0xf360
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ADDR_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_addr_rd_ns )
{
    U_VPSS_SMMU_FAULT_ADDR_RD_NS VPSS_SMMU_FAULT_ADDR_RD_NS;

    VPSS_SMMU_FAULT_ADDR_RD_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_NS.u32));
    VPSS_SMMU_FAULT_ADDR_RD_NS.bits.fault_addr_rd_ns = fault_addr_rd_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ADDR_RD_NS.u32), VPSS_SMMU_FAULT_ADDR_RD_NS.u32);

    return;
}
//addr=0xf364
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TLB_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tlb_rd_ns )
{
    U_VPSS_SMMU_FAULT_TLB_RD_NS VPSS_SMMU_FAULT_TLB_RD_NS;

    VPSS_SMMU_FAULT_TLB_RD_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_NS.u32));
    VPSS_SMMU_FAULT_TLB_RD_NS.bits.fault_tlb_rd_ns = fault_tlb_rd_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TLB_RD_NS.u32), VPSS_SMMU_FAULT_TLB_RD_NS.u32);

    return;
}
//addr=0xf368
HI_VOID VPSS_DRV_Set_SMMU_FAULT_ID_RD_NS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_str_id_rd_ns , HI_U32
        fault_index_id_rd_ns )
{
    U_VPSS_SMMU_FAULT_ID_RD_NS VPSS_SMMU_FAULT_ID_RD_NS;

    VPSS_SMMU_FAULT_ID_RD_NS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_NS.u32));
    VPSS_SMMU_FAULT_ID_RD_NS.bits.fault_str_id_rd_ns   = fault_str_id_rd_ns   ;
    VPSS_SMMU_FAULT_ID_RD_NS.bits.fault_index_id_rd_ns = fault_index_id_rd_ns ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_ID_RD_NS.u32), VPSS_SMMU_FAULT_ID_RD_NS.u32);

    return;
}
//addr=0xf36c
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TBU_INFO(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 fault_tbu_num , HI_U32
        fault_tlbinvalid_err_ns , HI_U32 fault_tlbmiss_err_ns , HI_U32 fault_tlbinvalid_err_s , HI_U32 fault_tlbmiss_err_s )
{
    U_VPSS_SMMU_FAULT_TBU_INFO VPSS_SMMU_FAULT_TBU_INFO;

    VPSS_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TBU_INFO.u32));
    VPSS_SMMU_FAULT_TBU_INFO.bits.fault_tbu_num           = fault_tbu_num           ;
    VPSS_SMMU_FAULT_TBU_INFO.bits.fault_tlbinvalid_err_ns = fault_tlbinvalid_err_ns ;
    VPSS_SMMU_FAULT_TBU_INFO.bits.fault_tlbmiss_err_ns    = fault_tlbmiss_err_ns    ;
    VPSS_SMMU_FAULT_TBU_INFO.bits.fault_tlbinvalid_err_s  = fault_tlbinvalid_err_s  ;
    VPSS_SMMU_FAULT_TBU_INFO.bits.fault_tlbmiss_err_s     = fault_tlbmiss_err_s     ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TBU_INFO.u32), VPSS_SMMU_FAULT_TBU_INFO.u32);

    return;
}
//addr=0xf370
HI_VOID VPSS_DRV_Set_SMMU_FAULT_TBU_DBG(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 read_command_counter , HI_U32
                                        arch_stall_n , HI_U32 tbu_arreadym , HI_U32 ar_readys , HI_U32 ar_valids , HI_U32 write_command_counter , HI_U32
                                        awch_stall_n , HI_U32 tbu_awreadym , HI_U32 aw_readys , HI_U32 aw_valids )
{
    U_VPSS_SMMU_FAULT_TBU_DBG VPSS_SMMU_FAULT_TBU_DBG;

    VPSS_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TBU_DBG.u32));
    VPSS_SMMU_FAULT_TBU_DBG.bits.read_command_counter  = read_command_counter  ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.arch_stall_n          = arch_stall_n          ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.tbu_arreadym          = tbu_arreadym          ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.ar_readys             = ar_readys             ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.ar_valids             = ar_valids             ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.write_command_counter = write_command_counter ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.awch_stall_n          = awch_stall_n          ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.tbu_awreadym          = tbu_awreadym          ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.aw_readys             = aw_readys             ;
    VPSS_SMMU_FAULT_TBU_DBG.bits.aw_valids             = aw_valids             ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_FAULT_TBU_DBG.u32), VPSS_SMMU_FAULT_TBU_DBG.u32);

    return;
}
//addr=0xf374
HI_VOID VPSS_DRV_Set_SMMU_PREF_BUFFER_EMPTY(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 pref_buffer_empty )
{
    U_VPSS_SMMU_PREF_BUFFER_EMPTY VPSS_SMMU_PREF_BUFFER_EMPTY;

    VPSS_SMMU_PREF_BUFFER_EMPTY.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_PREF_BUFFER_EMPTY.u32));
    VPSS_SMMU_PREF_BUFFER_EMPTY.bits.pref_buffer_empty = pref_buffer_empty ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_PREF_BUFFER_EMPTY.u32), VPSS_SMMU_PREF_BUFFER_EMPTY.u32);

    return;
}
//addr=0xf378
HI_VOID VPSS_DRV_Set_SMMU_PTWQ_IDLE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ptwq15_idle_state , HI_U32 ptwq14_idle_state
                                    , HI_U32 ptwq13_idle_state , HI_U32 ptwq12_idle_state , HI_U32 ptwq11_idle_state , HI_U32 ptwq10_idle_state , HI_U32
                                    ptwq9_idle_state , HI_U32 ptwq8_idle_state , HI_U32 ptwq7_idle_state , HI_U32 ptwq6_idle_state , HI_U32 ptwq5_idle_state ,
                                    HI_U32 ptwq4_idle_state , HI_U32 ptwq3_idle_state , HI_U32 ptwq2_idle_state , HI_U32 ptwq1_idle_state , HI_U32
                                    ptwq0_idle_state )
{
    U_VPSS_SMMU_PTWQ_IDLE VPSS_SMMU_PTWQ_IDLE;

    VPSS_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_PTWQ_IDLE.u32));
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq15_idle_state = ptwq15_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq14_idle_state = ptwq14_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq13_idle_state = ptwq13_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq12_idle_state = ptwq12_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq11_idle_state = ptwq11_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq10_idle_state = ptwq10_idle_state ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq9_idle_state  = ptwq9_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq8_idle_state  = ptwq8_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq7_idle_state  = ptwq7_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq6_idle_state  = ptwq6_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq5_idle_state  = ptwq5_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq4_idle_state  = ptwq4_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq3_idle_state  = ptwq3_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq2_idle_state  = ptwq2_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq1_idle_state  = ptwq1_idle_state  ;
    VPSS_SMMU_PTWQ_IDLE.bits.ptwq0_idle_state  = ptwq0_idle_state  ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_PTWQ_IDLE.u32), VPSS_SMMU_PTWQ_IDLE.u32);

    return;
}
//addr=0xf37c
HI_VOID VPSS_DRV_Set_SMMU_RESET_STATE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 smmu_rst_state )
{
    U_VPSS_SMMU_RESET_STATE VPSS_SMMU_RESET_STATE;

    VPSS_SMMU_RESET_STATE.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_RESET_STATE.u32));
    VPSS_SMMU_RESET_STATE.bits.smmu_rst_state = smmu_rst_state ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_RESET_STATE.u32), VPSS_SMMU_RESET_STATE.u32);

    return;
}
//addr=0xf380
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG0(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 in_out_cmd_cnt_rd , HI_U32 rdy_debug_rd ,
                                      HI_U32 vld_debug_rd , HI_U32 cur_miss_cnt_rd , HI_U32 last_miss_cnt_rd )
{
    U_VPSS_SMMU_MASTER_DBG0 VPSS_SMMU_MASTER_DBG0;

    VPSS_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG0.u32));
    VPSS_SMMU_MASTER_DBG0.bits.in_out_cmd_cnt_rd = in_out_cmd_cnt_rd ;
    VPSS_SMMU_MASTER_DBG0.bits.rdy_debug_rd      = rdy_debug_rd      ;
    VPSS_SMMU_MASTER_DBG0.bits.vld_debug_rd      = vld_debug_rd      ;
    VPSS_SMMU_MASTER_DBG0.bits.cur_miss_cnt_rd   = cur_miss_cnt_rd   ;
    VPSS_SMMU_MASTER_DBG0.bits.last_miss_cnt_rd  = last_miss_cnt_rd  ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG0.u32), VPSS_SMMU_MASTER_DBG0.u32);

    return;
}
//addr=0xf384
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG1(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 in_out_cmd_cnt_wr , HI_U32 rdy_debug_wr ,
                                      HI_U32 vld_debug_wr , HI_U32 cur_miss_cnt_wr , HI_U32 last_miss_cnt_wr )
{
    U_VPSS_SMMU_MASTER_DBG1 VPSS_SMMU_MASTER_DBG1;

    VPSS_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG1.u32));
    VPSS_SMMU_MASTER_DBG1.bits.in_out_cmd_cnt_wr = in_out_cmd_cnt_wr ;
    VPSS_SMMU_MASTER_DBG1.bits.rdy_debug_wr      = rdy_debug_wr      ;
    VPSS_SMMU_MASTER_DBG1.bits.vld_debug_wr      = vld_debug_wr      ;
    VPSS_SMMU_MASTER_DBG1.bits.cur_miss_cnt_wr   = cur_miss_cnt_wr   ;
    VPSS_SMMU_MASTER_DBG1.bits.last_miss_cnt_wr  = last_miss_cnt_wr  ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG1.u32), VPSS_SMMU_MASTER_DBG1.u32);

    return;
}
//addr=0xf388
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG2(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_double_upd_cnt_rd , HI_U32
                                      last_double_upd_cnt_rd , HI_U32 cur_double_miss_cnt_rd , HI_U32 last_double_miss_cnt_rd )
{
    U_VPSS_SMMU_MASTER_DBG2 VPSS_SMMU_MASTER_DBG2;

    VPSS_SMMU_MASTER_DBG2.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG2.u32));
    VPSS_SMMU_MASTER_DBG2.bits.cur_double_upd_cnt_rd   = cur_double_upd_cnt_rd   ;
    VPSS_SMMU_MASTER_DBG2.bits.last_double_upd_cnt_rd  = last_double_upd_cnt_rd  ;
    VPSS_SMMU_MASTER_DBG2.bits.cur_double_miss_cnt_rd  = cur_double_miss_cnt_rd  ;
    VPSS_SMMU_MASTER_DBG2.bits.last_double_miss_cnt_rd = last_double_miss_cnt_rd ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG2.u32), VPSS_SMMU_MASTER_DBG2.u32);

    return;
}
//addr=0xf38c
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG3(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 mst_fsm_cur , HI_U32 cur_double_upd_cnt_wr
                                      , HI_U32 last_double_upd_cnt_wr , HI_U32 cur_double_miss_cnt_wr , HI_U32 last_double_miss_cnt_wr )
{
    U_VPSS_SMMU_MASTER_DBG3 VPSS_SMMU_MASTER_DBG3;

    VPSS_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG3.u32));
    VPSS_SMMU_MASTER_DBG3.bits.mst_fsm_cur             = mst_fsm_cur             ;
    VPSS_SMMU_MASTER_DBG3.bits.cur_double_upd_cnt_wr   = cur_double_upd_cnt_wr   ;
    VPSS_SMMU_MASTER_DBG3.bits.last_double_upd_cnt_wr  = last_double_upd_cnt_wr  ;
    VPSS_SMMU_MASTER_DBG3.bits.cur_double_miss_cnt_wr  = cur_double_miss_cnt_wr  ;
    VPSS_SMMU_MASTER_DBG3.bits.last_double_miss_cnt_wr = last_double_miss_cnt_wr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG3.u32), VPSS_SMMU_MASTER_DBG3.u32);

    return;
}
//addr=0xf520
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG4(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel1_chn_miss_cnt_rd , HI_U32
                                      last_sel1_chn_miss_cnt_rd )
{
    U_VPSS_SMMU_MASTER_DBG4 VPSS_SMMU_MASTER_DBG4;

    VPSS_SMMU_MASTER_DBG4.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG4.u32));
    VPSS_SMMU_MASTER_DBG4.bits.cur_sel1_chn_miss_cnt_rd  = cur_sel1_chn_miss_cnt_rd  ;
    VPSS_SMMU_MASTER_DBG4.bits.last_sel1_chn_miss_cnt_rd = last_sel1_chn_miss_cnt_rd ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG4.u32), VPSS_SMMU_MASTER_DBG4.u32);

    return;
}
//addr=0xf524
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG5(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel2_chn_miss_cnt_rd , HI_U32
                                      last_sel2_chn_miss_cnt_rd )
{
    U_VPSS_SMMU_MASTER_DBG5 VPSS_SMMU_MASTER_DBG5;

    VPSS_SMMU_MASTER_DBG5.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG5.u32));
    VPSS_SMMU_MASTER_DBG5.bits.cur_sel2_chn_miss_cnt_rd  = cur_sel2_chn_miss_cnt_rd  ;
    VPSS_SMMU_MASTER_DBG5.bits.last_sel2_chn_miss_cnt_rd = last_sel2_chn_miss_cnt_rd ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG5.u32), VPSS_SMMU_MASTER_DBG5.u32);

    return;
}
//addr=0xf528
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG6(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel1_chn_miss_cnt_wr , HI_U32
                                      last_sel1_chn_miss_cnt_wr )
{
    U_VPSS_SMMU_MASTER_DBG6 VPSS_SMMU_MASTER_DBG6;

    VPSS_SMMU_MASTER_DBG6.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG6.u32));
    VPSS_SMMU_MASTER_DBG6.bits.cur_sel1_chn_miss_cnt_wr  = cur_sel1_chn_miss_cnt_wr  ;
    VPSS_SMMU_MASTER_DBG6.bits.last_sel1_chn_miss_cnt_wr = last_sel1_chn_miss_cnt_wr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG6.u32), VPSS_SMMU_MASTER_DBG6.u32);

    return;
}
//addr=0xf52c
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG7(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 cur_sel2_chn_miss_cnt_wr , HI_U32
                                      last_sel2_chn_miss_cnt_wr )
{
    U_VPSS_SMMU_MASTER_DBG7 VPSS_SMMU_MASTER_DBG7;

    VPSS_SMMU_MASTER_DBG7.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG7.u32));
    VPSS_SMMU_MASTER_DBG7.bits.cur_sel2_chn_miss_cnt_wr  = cur_sel2_chn_miss_cnt_wr  ;
    VPSS_SMMU_MASTER_DBG7.bits.last_sel2_chn_miss_cnt_wr = last_sel2_chn_miss_cnt_wr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG7.u32), VPSS_SMMU_MASTER_DBG7.u32);

    return;
}
//addr=0xf530
HI_VOID VPSS_DRV_Set_SMMU_MASTER_DBG8(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 sel1_chn_rd , HI_U32 sel2_chn_rd , HI_U32
                                      sel1_chn_wr , HI_U32 sel2_chn_wr )
{
    U_VPSS_SMMU_MASTER_DBG8 VPSS_SMMU_MASTER_DBG8;

    VPSS_SMMU_MASTER_DBG8.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG8.u32));
    VPSS_SMMU_MASTER_DBG8.bits.sel1_chn_rd = sel1_chn_rd ;
    VPSS_SMMU_MASTER_DBG8.bits.sel2_chn_rd = sel2_chn_rd ;
    VPSS_SMMU_MASTER_DBG8.bits.sel1_chn_wr = sel1_chn_wr ;
    VPSS_SMMU_MASTER_DBG8.bits.sel2_chn_wr = sel2_chn_wr ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_SMMU_MASTER_DBG8.u32), VPSS_SMMU_MASTER_DBG8.u32);

    return;
}
#endif

HI_VOID VPSS_Mmu_SetWchBypassFlag(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 u32Flag)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32));
    VPSS_WCH_BYPASS.u32 = u32Flag         ;
    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_WCH_BYPASS.u32);

    return;
}

HI_VOID VPSS_Mmu_SetRchBypassFlag(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 u32Flag)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_RCH_BYPASS.u32));
    VPSS_RCH_BYPASS.u32 = u32Flag         ;
    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_WCH_BYPASS.u32), VPSS_RCH_BYPASS.u32);

    return;
}


