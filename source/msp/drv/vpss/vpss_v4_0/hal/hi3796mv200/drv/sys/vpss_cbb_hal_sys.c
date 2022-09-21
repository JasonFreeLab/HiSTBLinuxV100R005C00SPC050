//#include <linux/io.h>
//#include <unistd.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"



HI_S32 VPSS_DRV_SetTimeOut(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Data)
{
    HI_U32 VPSS_TIMEOUT;
    HI_S32 s32RetryCnt;

    VPSS_TIMEOUT = 0;
    s32RetryCnt = 0;

    while (VPSS_TIMEOUT != u32Data)
    {
        VPSS_TIMEOUT = u32Data;
        VPSS_REG_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_TIMEOUT.u32), VPSS_TIMEOUT);
        VPSS_TIMEOUT = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_TIMEOUT.u32));
        s32RetryCnt++;

        if (VPSS_TIMEOUT != u32Data)
        {
            VPSS_FATAL("retry:%d (exp %x  real %x)\n", s32RetryCnt, u32Data, VPSS_TIMEOUT);
        }
    }

    return HI_SUCCESS;
}


HI_VOID VPSS_DRV_SetCkgtEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Data)
{
    U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;

    VPSS_MISCELLANEOUS.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32));
    VPSS_MISCELLANEOUS.bits.ck_gt_en        = u32Data;
    VPSS_MISCELLANEOUS.bits.ck_gt_en_calc   = u32Data;
    VPSS_REG_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32), VPSS_MISCELLANEOUS.u32);
}


HI_S32 VPSS_DRV_GetRawIntStatus( S_VPSS_REGS_TYPE *pstVpssRegs )
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_RAWINT.u32));

    return VPSS_RAWINT.u32;
}

HI_S32 VPSS_DRV_GetIntStatus( S_VPSS_REGS_TYPE *pstVpssRegs )
{
    U_VPSS_RAWINT VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTSTATE.u32));

    return VPSS_INTSTATE.u32;
}


HI_VOID VPSS_DRV_ClrInt( S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32ClrInt )
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_REG_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTCLR.u32));
    VPSS_INTCLR.u32 = u32ClrInt;
    VPSS_REG_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTCLR.u32), VPSS_INTCLR.u32);
}

HI_VOID VPSS_DRV_SetIntMask( S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Mask )
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = u32Mask;

    VPSS_REG_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTMASK.u32), VPSS_INTMASK.u32);
}

HI_U32 VPSS_DRV_GetPfCnt(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    U_VPSS_PFCNT VPSS_PFCNT;

    VPSS_PFCNT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PFCNT.u32)));

    return VPSS_PFCNT.u32;

}
HI_U32 VPSS_DRV_GetEofCnt(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    U_VPSS_EOFCNT VPSS_EOFCNT;

    VPSS_EOFCNT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_EOFCNT.u32)));

    return VPSS_EOFCNT.u32;
}

HI_U32 VPSS_DRV_GetNodeId(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    U_VPSS_NODEID VPSS_NODEID;

    VPSS_NODEID.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_NODEID.u32)));

    return VPSS_NODEID.u32;
}

//addr=0x2f8
HI_VOID VPSS_Sys_SetVpssNodeId(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 nodeid )
{
    U_VPSS_NODEID VPSS_NODEID;

    VPSS_NODEID.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_NODEID.u32));
    VPSS_NODEID.bits.nodeid = nodeid ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_NODEID.u32), VPSS_NODEID.u32);

    return;
}

//addr=0x2fc
HI_VOID VPSS_DRV_Set_VPSS_PNEXT(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 *pu32PhyAddr)
#if 1
{
    U_VPSS_PNEXT VPSS_PNEXT;
    HI_S32 s32RetryCnt;

    s32RetryCnt = 0;
    VPSS_PNEXT.u32 = 0;

    while ((VPSS_PNEXT.u32 != (HI_U32)(long)pu32PhyAddr) && (s32RetryCnt < 10))
    {
        VPSS_PNEXT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PNEXT.u32)));
        VPSS_PNEXT.bits.p_next = (HI_U32)((unsigned long)pu32PhyAddr);
        VPSS_REG_RegWrite((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PNEXT.u32)), VPSS_PNEXT.u32);
        VPSS_PNEXT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PNEXT.u32)));
        s32RetryCnt++;

        if (VPSS_PNEXT.u32 != (HI_U32)(long)pu32PhyAddr)
        {
            VPSS_FATAL("retry:%d (exp %x  real %x)\n", s32RetryCnt, pu32PhyAddr, VPSS_PNEXT.u32);
        }
    }

    if (10 <= s32RetryCnt)
    {
        VPSS_FATAL("VPSS_DRV_Set_VPSS_PNEXT fail\n");
    }

    return;
}
#else
{
    U_VPSS_PNEXT VPSS_PNEXT;
    VPSS_PNEXT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PNEXT.u32)));
    VPSS_PNEXT.bits.p_next = (HI_U32)((unsigned long)pu32PhyAddr);
    VPSS_REG_RegWrite((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_PNEXT.u32)), VPSS_PNEXT.u32);

    return;
}
#endif
//addr=0x300
HI_VOID VPSS_DRV_Set_VPSS_START(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    U_VPSS_START VPSS_START;

    VPSS_START.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_START.u32));
    /* make sure all config data have been written to DDR before VPSS logic starts.
       Otherwise VPSS may get a accidental TIMEOUT crash.
    */
    mb();

    VPSS_START.bits.start = 0x1;
    VPSS_REG_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_START.u32), VPSS_START.u32);

    return;
}


//addr=0x314
HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_CLKGT(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ck_gt_en_calc , HI_U32 ck_gt_en)
{
    U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;

    VPSS_MISCELLANEOUS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32));
    VPSS_MISCELLANEOUS.bits.ck_gt_en_calc = ck_gt_en_calc ;
    VPSS_MISCELLANEOUS.bits.ck_gt_en      = ck_gt_en      ;
    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32), VPSS_MISCELLANEOUS.u32);

    return;
}

HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_OUTSTANDING(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 woutstanding , HI_U32 routstanding )
{
    U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;

    VPSS_MISCELLANEOUS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32));
    VPSS_MISCELLANEOUS.bits.woutstanding  = woutstanding  ;
    VPSS_MISCELLANEOUS.bits.routstanding  = routstanding  ;
    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32), VPSS_MISCELLANEOUS.u32);

    return;
}

HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_BUSLEN(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 bus_len )
{
    U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;

    VPSS_MISCELLANEOUS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32));

    VPSS_MISCELLANEOUS.bits.burst_len_cfg = bus_len  ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32), VPSS_MISCELLANEOUS.u32);

    return;
}

HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_INITTIMER(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 init_timer)
{
    U_VPSS_MISCELLANEOUS VPSS_MISCELLANEOUS;

    VPSS_MISCELLANEOUS.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32));

    VPSS_MISCELLANEOUS.bits.init_timer    = init_timer    ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MISCELLANEOUS.u32), VPSS_MISCELLANEOUS.u32);

    return;
}


//addr=0x318
HI_VOID VPSS_DRV_Set_VPSS_MACCFG(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 mac_ch_prio )
{
    U_VPSS_MACCFG VPSS_MACCFG;

    VPSS_MACCFG.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_MACCFG.u32));
    VPSS_MACCFG.bits.mac_ch_prio = mac_ch_prio ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MACCFG.u32), VPSS_MACCFG.u32);

    return;
}
//addr=0x320
HI_VOID VPSS_DRV_Set_VPSS_FTCONFIG(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 node_rst_en )
{
    U_VPSS_FTCONFIG VPSS_FTCONFIG;

    VPSS_FTCONFIG.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_FTCONFIG.u32));
    VPSS_FTCONFIG.bits.node_rst_en = node_rst_en ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_FTCONFIG.u32), VPSS_FTCONFIG.u32);

    return;
}
//addr=0x324
HI_VOID VPSS_DRV_Set_VPSS_INTMASK(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 bus_r_err_mask , HI_U32 dcmp_err_mask , HI_U32 vhd0_tunl_mask , HI_U32 eof_end_mask , HI_U32 bus_w_err_mask , HI_U32 timeout_mask , HI_U32 eof_mask )
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTMASK.u32));
    VPSS_INTMASK.bits.bus_r_err_mask = bus_r_err_mask ;
    //VPSS_INTMASK.bits.dcmp_err_mask  = dcmp_err_mask  ;
    //VPSS_INTMASK.bits.vhd0_tunl_mask = vhd0_tunl_mask ;
    VPSS_INTMASK.bits.eof_end_mask   = eof_end_mask   ;
    VPSS_INTMASK.bits.bus_w_err_mask = bus_w_err_mask ;
    VPSS_INTMASK.bits.timeout_mask   = timeout_mask   ;
    VPSS_INTMASK.bits.eof_mask       = eof_mask       ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTMASK.u32), VPSS_INTMASK.u32);

    return;
}
//addr=0x328
HI_VOID VPSS_DRV_SetMemCtrl(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ema, HI_U32 emaw, HI_U32 emasa, HI_U32 emaa, HI_U32 emab)
{
    U_VPSS_MEMCTRL VPSS_MEMCTRL;

    VPSS_MEMCTRL.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_INTMASK.u32));

    VPSS_MEMCTRL.bits.ema    = ema ;
    VPSS_MEMCTRL.bits.emaw   = emaw   ;
    VPSS_MEMCTRL.bits.emasa  = emasa ;
    VPSS_MEMCTRL.bits.emaa   = emaa   ;
    VPSS_MEMCTRL.bits.emab   = emab   ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_MEMCTRL.u32), VPSS_MEMCTRL.u32);

    return;
}

//addr=0x344
HI_VOID VPSS_DRV_Set_VPSS_BUS_CTRL(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 b128_split_en , HI_U32 b256_split_en )
{
    U_VPSS_BUS_CTRL VPSS_BUS_CTRL;

    VPSS_BUS_CTRL.u32 = VPSS_RegRead((volatile HI_U32 *) & (pstVpssRegs->VPSS_BUS_CTRL.u32));
    VPSS_BUS_CTRL.bits.b128_split_en = b128_split_en ;
    VPSS_BUS_CTRL.bits.b256_split_en = b256_split_en ;

    VPSS_RegWrite((volatile HI_U32 *) & (pstVpssRegs->VPSS_BUS_CTRL.u32), VPSS_BUS_CTRL.u32);

    return;
}

#if 1
HI_VOID VPSS_Sys_SetBfield(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.bfield = bfield;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBfieldMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield_mode)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.bfield_mode = bfield_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBfieldFirst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield_first)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.bfield_first = bfield_first;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetImgProMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 img_pro_mode)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.img_pro_mode = img_pro_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIgbmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 igbm_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.igbm_en = igbm_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIfmdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ifmd_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.ifmd_en = ifmd_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetProt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prot)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));

    //0: security; 2: not security
    if (prot)
    {
        VPSS_CTRL.bits.prot = 0;
    }
    else
    {
        VPSS_CTRL.bits.prot = 2;
    }

    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRotateEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rotate_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.rotate_en = rotate_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRotateAngle(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rotate_angle)
{
    U_VPSS_RTT_CFG VPSS_RTT_CFG;

    VPSS_RTT_CFG.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_RTT_CFG.u32));
    VPSS_RTT_CFG.bits.rotate_angle = rotate_angle;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_RTT_CFG.u32), VPSS_RTT_CFG.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRfrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.rfr_en = rfr_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 tnr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.tnr_en = tnr_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.snr_en = snr_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}
HI_VOID VPSS_Sys_SetFmtcEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fmtc_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.fmtc_en = fmtc_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRgmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgme_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.rgme_en = rgme_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBlkDetEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blk_det_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.blk_det_en = blk_det_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVc1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vc1_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.nx2_vc1_en = vc1_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMedsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 meds_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.meds_en = meds_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcdiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcdi_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.mcdi_en = mcdi_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDeiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dei_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.dei_en = dei_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetChkSumEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chk_sum_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.chk_sum_en = chk_sum_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetVhd0ZmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 zme_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32));
    VPSS_CTRL3.bits.zme_vhd0_en = zme_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32), VPSS_CTRL3.u32);

    return ;
}

HI_VOID VPSS_Sys_SetVhd0LbaEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lba_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32));
    VPSS_CTRL3.bits.vhd0_lba_en = lba_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32), VPSS_CTRL3.u32);

    return ;
}

HI_VOID VPSS_Sys_SetVhd0CropEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crop_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32));
    VPSS_CTRL3.bits.vhd0_crop_en = crop_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL3.u32), VPSS_CTRL3.u32);

    return ;
}

HI_VOID VPSS_Sys_SetVhd0En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.vhd0_en = vhd0_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRfrPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_pix_bitw)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.rfr_pix_bitw = rfr_pix_bitw;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRefPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_pix_bitw)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.ref_nxt_pix_bitw = ref_pix_bitw;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetCtsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cts_en)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.cts_en = cts_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}
HI_VOID VPSS_Sys_SetCtsBitSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bit_sel)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.cts_bit_sel = bit_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetInPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 in_pix_bitw)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.in_pix_bitw = in_pix_bitw;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetInFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 in_format)
{
    U_VPSS_IN_CTRL VPSS_IN_CTRL;

    VPSS_IN_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32));
    VPSS_IN_CTRL.bits.in_format = in_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_IN_CTRL.u32), VPSS_IN_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0Format(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_format)
{
    U_VPSS_VHD0CTRL VPSS_VHD0CTRL;

    VPSS_VHD0CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32));
    VPSS_VHD0CTRL.bits.vhd0_format = vhd0_format;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_VHD0CTRL.u32), VPSS_VHD0CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetFourPixEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 four_pix_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32));
    VPSS_CTRL.bits.four_pix_en = four_pix_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL.u32), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRamBank(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ram_bank)
{

    U_VPSS_CTRL2 VPSS_CTRL2;

    VPSS_CTRL2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32));
    VPSS_CTRL2.bits.ram_bank = ram_bank;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32), VPSS_CTRL2.u32);

    return ;
}

HI_VOID VPSS_Sys_SetRefDitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_dither_en)
{
    U_VPSS_CTRL2 VPSS_CTRL2;

    VPSS_CTRL2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32));
    VPSS_CTRL2.bits.ref_dither_en = ref_dither_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32), VPSS_CTRL2.u32);

    return ;
}
HI_VOID VPSS_Sys_SetRefDitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_dither_mode)
{
    U_VPSS_CTRL2 VPSS_CTRL2;

    VPSS_CTRL2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32));
    VPSS_CTRL2.bits.ref_dither_mode = ref_dither_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_CTRL2.u32), VPSS_CTRL2.u32);

    return ;
}

#endif
