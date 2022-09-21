//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_common.h"
//#include "vpss_reg.h"
#if 1

HI_VOID VPSS_Tnr_SetMcnrRgmeMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mcnr_rgme_mode)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.mcnr_rgme_mode = mcnr_rgme_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}

HI_VOID VPSS_Tnr_SetMcnrMotionMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mcnr_motion_mode)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.motion_mode = mcnr_motion_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMarketcoor(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  marketcoor)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.marketcoor = marketcoor;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMarketmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  marketmode)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.marketmode = marketmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMarketmodeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  marketmodeen)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.marketmodeen = marketmodeen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMcnrMedsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mcnr_meds_en)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.mcnr_meds_en = mcnr_meds_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMcnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mcnr_en)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.mcnr_en = mcnr_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cnren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.cnren = cnren;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ynren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.ynren = ynren;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetNren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  nren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32));
    VPSS_TNR_CONTRL.bits.nren = nren;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CONTRL.u32), VPSS_TNR_CONTRL.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetAlpha2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  alpha2)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.alpha2 = alpha2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAlpha1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  alpha1)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.alpha1 = alpha1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionlpfmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.cmotionlpfmode = cmotionlpfmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionlpfmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.ymotionlpfmode = ymotionlpfmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotioncalcmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.cmotioncalcmode = cmotioncalcmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotioncalcmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.ymotioncalcmode = ymotioncalcmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeancadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  meancadjshift)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.meancadjshift = meancadjshift;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanyadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  meanyadjshift)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.meanyadjshift = meanyadjshift;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanCmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_cmotion_adj_en)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.mean_cmotion_adj_en = mean_cmotion_adj_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanYmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_ymotion_adj_en)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.mean_ymotion_adj_en = mean_ymotion_adj_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMdprelpfen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mdprelpfen)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32));
    VPSS_TNR_MAMD_CTRL.bits.mdprelpfen = mdprelpfen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmdcore)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32));
    VPSS_TNR_MAMD_GAIN.bits.cmdcore = cmdcore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmdgain)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32));
    VPSS_TNR_MAMD_GAIN.bits.cmdgain = cmdgain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymdcore)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32));
    VPSS_TNR_MAMD_GAIN.bits.ymdcore = ymdcore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymdgain)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32));
    VPSS_TNR_MAMD_GAIN.bits.ymdgain = ymdgain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetRandomctrlmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  randomctrlmode)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32));
    VPSS_TNR_MAND_CTRL.bits.randomctrlmode = randomctrlmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32), VPSS_TNR_MAND_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetBlkdiffthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  blkdiffthd)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32));
    VPSS_TNR_MAND_CTRL.bits.blkdiffthd = blkdiffthd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32), VPSS_TNR_MAND_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetNoisedetecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  noisedetecten)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32));
    VPSS_TNR_MAND_CTRL.bits.noisedetecten = noisedetecten;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_CTRL.u32), VPSS_TNR_MAND_CTRL.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetFlatthdmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatthdmax)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32));
    VPSS_TNR_MAND_THD.bits.flatthdmax = flatthdmax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32), VPSS_TNR_MAND_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetFlatthdmed(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatthdmed)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32));
    VPSS_TNR_MAND_THD.bits.flatthdmed = flatthdmed;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32), VPSS_TNR_MAND_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetFlatthdmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatthdmin)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32));
    VPSS_TNR_MAND_THD.bits.flatthdmin = flatthdmin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAND_THD.u32), VPSS_TNR_MAND_THD.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetSmvythd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  smvythd)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.smvythd = smvythd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetSmvxthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  smvxthd)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.smvxthd = smvxthd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetDiscardsmvyen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  discardsmvyen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.discardsmvyen = discardsmvyen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetDiscardsmvxen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  discardsmvxen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.discardsmvxen = discardsmvxen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetGmAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  gm_adj)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.gm_adj = gm_adj;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMvlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mvlpfmode)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.mvlpfmode = mvlpfmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMvrefmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mvrefmode)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.mvrefmode = mvrefmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMotionestimateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  motionestimateen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32));
    VPSS_TNR_MAME_CTRL.bits.motionestimateen = motionestimateen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_CTRL.u32), VPSS_TNR_MAME_CTRL.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetMagPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mag_pnl_core_xmv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_core_xmv = mag_pnl_core_xmv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMagPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mag_pnl_gain_xmv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_gain_xmv = mag_pnl_gain_xmv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMagPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mag_pnl_core_0mv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_core_0mv = mag_pnl_core_0mv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMagPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mag_pnl_gain_0mv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_gain_0mv = mag_pnl_gain_0mv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_GAIN.u32), VPSS_TNR_MAME_GAIN.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetStdPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_core_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_core_xmv = std_pnl_core_xmv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_gain_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_gain_xmv = std_pnl_gain_xmv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_core_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_core_0mv = std_pnl_core_0mv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_gain_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_gain_0mv = std_pnl_gain_0mv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_core_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_core_xmv = std_core_xmv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_core_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32));
    VPSS_TNR_MAME_STD_CORE.bits.std_core_0mv = std_core_0mv;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetStdPnlCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_core)
{
    U_VPSS_TNR_MAME_STD_GAIN VPSS_TNR_MAME_STD_GAIN;

    VPSS_TNR_MAME_STD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32));
    VPSS_TNR_MAME_STD_GAIN.bits.std_pnl_core = std_pnl_core;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32), VPSS_TNR_MAME_STD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetStdPnlGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  std_pnl_gain)
{
    U_VPSS_TNR_MAME_STD_GAIN VPSS_TNR_MAME_STD_GAIN;

    VPSS_TNR_MAME_STD_GAIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32));
    VPSS_TNR_MAME_STD_GAIN.bits.std_pnl_gain = std_pnl_gain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32), VPSS_TNR_MAME_STD_GAIN.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetAdjXmvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_xmv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_xmv_max = adj_xmv_max;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAdj0mvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_0mv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_0mv_max = adj_0mv_max;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAdjXmvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_xmv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_xmv_min = adj_xmv_min;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAdj0mvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_0mv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_0mv_min = adj_0mv_min;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAdjMvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_mv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_mv_min = adj_mv_min;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetAdjMvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  adj_mv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32));
    VPSS_TNR_MAME_MV_THD.bits.adj_mv_max = adj_mv_max;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCbcrweight2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbcrweight2)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrweight2 = cbcrweight2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbcrweight1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbcrweight1)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrweight1 = cbcrweight1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbcrupdateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbcrupdateen)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrupdateen = cbcrupdateen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCrend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  crend1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crend1 = crend1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbend1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbend1 = cbend1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCrbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  crbegin1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crbegin1 = crbegin1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbbegin1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbbegin1 = cbbegin1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCrend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  crend2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crend2 = crend2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbend2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbend2 = cbend2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCrbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  crbegin2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crbegin2 = crbegin2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCbbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cbbegin2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbbegin2 = cbbegin2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetMotionmergeratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  motionmergeratio)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32));
    VPSS_TNR_MAMC_PRE_MAD.bits.motionmergeratio = motionmergeratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetPremotionalpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  premotionalpha)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32));
    VPSS_TNR_MAMC_PRE_MAD.bits.premotionalpha = premotionalpha;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetPremotionmergemode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  premotionmergemode)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32));
    VPSS_TNR_MAMC_PRE_MAD.bits.premotionmergemode = premotionmergemode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotioncore)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32));
    VPSS_TNR_MAMC_MAP.bits.cmotioncore = cmotioncore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotiongain)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32));
    VPSS_TNR_MAMC_MAP.bits.cmotiongain = cmotiongain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotioncore)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32));
    VPSS_TNR_MAMC_MAP.bits.ymotioncore = ymotioncore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotiongain)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32));
    VPSS_TNR_MAMC_MAP.bits.ymotiongain = ymotiongain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMotionmappingen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  motionmappingen)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32));
    VPSS_TNR_MAMC_MAP.bits.motionmappingen = motionmappingen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MAP.u32), VPSS_TNR_MAMC_MAP.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetSaltuslevel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  saltuslevel)
{
    U_VPSS_TNR_MAMC_SALTUS VPSS_TNR_MAMC_SALTUS;

    VPSS_TNR_MAMC_SALTUS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32));
    VPSS_TNR_MAMC_SALTUS.bits.saltuslevel = saltuslevel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32), VPSS_TNR_MAMC_SALTUS.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetSaltusdecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  saltusdecten)
{
    U_VPSS_TNR_MAMC_SALTUS VPSS_TNR_MAMC_SALTUS;

    VPSS_TNR_MAMC_SALTUS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32));
    VPSS_TNR_MAMC_SALTUS.bits.saltusdecten = saltusdecten;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32), VPSS_TNR_MAMC_SALTUS.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmclpfmode)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32));
    VPSS_TNR_MAMC_MCADJ.bits.cmclpfmode = cmclpfmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymclpfmode)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32));
    VPSS_TNR_MAMC_MCADJ.bits.ymclpfmode = ymclpfmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmcadjen)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32));
    VPSS_TNR_MAMC_MCADJ.bits.cmcadjen = cmcadjen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymcadjen)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32));
    VPSS_TNR_MAMC_MCADJ.bits.ymcadjen = ymcadjen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cnonrrange)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32));
    VPSS_TNR_FILR_MODE.bits.cnonrrange = cnonrrange;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ynonrrange)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32));
    VPSS_TNR_FILR_MODE.bits.ynonrrange = ynonrrange;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionmode)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32));
    VPSS_TNR_FILR_MODE.bits.cmotionmode = cmotionmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionmode)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32));
    VPSS_TNR_FILR_MODE.bits.ymotionmode = ymotionmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FILR_MODE.u32), VPSS_TNR_FILR_MODE.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetScenechangeinfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  scenechangeinfo)
{
    U_VPSS_TNR_SCENE_CHANGE VPSS_TNR_SCENE_CHANGE;

    VPSS_TNR_SCENE_CHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32));
    VPSS_TNR_SCENE_CHANGE.bits.scenechangeinfo = scenechangeinfo;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32), VPSS_TNR_SCENE_CHANGE.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetScenechangeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  scenechangeen)
{
    U_VPSS_TNR_SCENE_CHANGE VPSS_TNR_SCENE_CHANGE;

    VPSS_TNR_SCENE_CHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32));
    VPSS_TNR_SCENE_CHANGE.bits.scenechangeen = scenechangeen;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32), VPSS_TNR_SCENE_CHANGE.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCfgCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cfg_cmdcore)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32));
    VPSS_TNR_CFG.bits.cfg_cmdcore = cfg_cmdcore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCfgCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cfg_cmdgain)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32));
    VPSS_TNR_CFG.bits.cfg_cmdgain = cfg_cmdgain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCfgYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cfg_ymdcore)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32));
    VPSS_TNR_CFG.bits.cfg_ymdcore = cfg_ymdcore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCfgYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cfg_ymdgain)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32));
    VPSS_TNR_CFG.bits.cfg_ymdgain = cfg_ymdgain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CFG.u32), VPSS_TNR_CFG.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetFlatinfoymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatinfoymax)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32));
    VPSS_TNR_FLAT_INFO.bits.flatinfoymax = flatinfoymax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetFlatinfoxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatinfoxmax)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32));
    VPSS_TNR_FLAT_INFO.bits.flatinfoxmax = flatinfoxmax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetFlatinfoymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatinfoymin)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32));
    VPSS_TNR_FLAT_INFO.bits.flatinfoymin = flatinfoymin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetFlatinfoxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  flatinfoxmin)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32));
    VPSS_TNR_FLAT_INFO.bits.flatinfoxmin = flatinfoxmin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_FLAT_INFO.u32), VPSS_TNR_FLAT_INFO.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingymax)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32));
    VPSS_TNR_YBLEND.bits.yblendingymax = yblendingymax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingxmax)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32));
    VPSS_TNR_YBLEND.bits.yblendingxmax = yblendingxmax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingymin)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32));
    VPSS_TNR_YBLEND.bits.yblendingymin = yblendingymin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingxmin)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32));
    VPSS_TNR_YBLEND.bits.yblendingxmin = yblendingxmin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLEND.u32), VPSS_TNR_YBLEND.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingymax)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32));
    VPSS_TNR_CBLEND.bits.cblendingymax = cblendingymax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingxmax)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32));
    VPSS_TNR_CBLEND.bits.cblendingxmax = cblendingxmax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingymin)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32));
    VPSS_TNR_CBLEND.bits.cblendingymin = cblendingymin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingxmin)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32));
    VPSS_TNR_CBLEND.bits.cblendingxmin = cblendingxmin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLEND.u32), VPSS_TNR_CBLEND.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetDtblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  dtblendingymax)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32));
    VPSS_TNR_DTBLEND.bits.dtblendingymax = dtblendingymax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetDtblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  dtblendingxmax)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32));
    VPSS_TNR_DTBLEND.bits.dtblendingxmax = dtblendingxmax;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetDtblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  dtblendingymin)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32));
    VPSS_TNR_DTBLEND.bits.dtblendingymin = dtblendingymin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetDtblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  dtblendingxmin)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32));
    VPSS_TNR_DTBLEND.bits.dtblendingxmin = dtblendingxmin;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_DTBLEND.u32), VPSS_TNR_DTBLEND.u32);

    return ;
}

HI_VOID VPSS_Tnr_SetMeanMotionRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio3)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio3 = mean_motion_ratio3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio2)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio2 = mean_motion_ratio2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio1)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio1 = mean_motion_ratio1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio0)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio0 = mean_motion_ratio0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetMeanMotionRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio7)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio7 = mean_motion_ratio7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio6)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio6 = mean_motion_ratio6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio5)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio5 = mean_motion_ratio5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio4)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio4 = mean_motion_ratio4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetMeanMotionRatio11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio11)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio11 = mean_motion_ratio11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio10)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio10 = mean_motion_ratio10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio9)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio9 = mean_motion_ratio9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio8)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio8 = mean_motion_ratio8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetMeanMotionRatio15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio15)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio15 = mean_motion_ratio15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio14)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio14 = mean_motion_ratio14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio13)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio13 = mean_motion_ratio13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetMeanMotionRatio12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  mean_motion_ratio12)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio12 = mean_motion_ratio12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut3)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut3 = yblendingalphalut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut2)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut2 = yblendingalphalut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut1)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut1 = yblendingalphalut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut0)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut0 = yblendingalphalut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut7)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut7 = yblendingalphalut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut6)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut6 = yblendingalphalut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut5)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut5 = yblendingalphalut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut4)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut4 = yblendingalphalut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut11)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut11 = yblendingalphalut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut10)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut10 = yblendingalphalut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut9)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut9 = yblendingalphalut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut8)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut8 = yblendingalphalut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut15)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut15 = yblendingalphalut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut14)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut14 = yblendingalphalut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut13)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut13 = yblendingalphalut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut12)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut12 = yblendingalphalut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut19)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut19 = yblendingalphalut19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut18)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut18 = yblendingalphalut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut17)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut17 = yblendingalphalut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut16)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut16 = yblendingalphalut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut23)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut23 = yblendingalphalut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut22)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut22 = yblendingalphalut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut21)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut21 = yblendingalphalut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut20)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut20 = yblendingalphalut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut27)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut27 = yblendingalphalut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut26)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut26 = yblendingalphalut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut25)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut25 = yblendingalphalut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut24)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut24 = yblendingalphalut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut31)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut31 = yblendingalphalut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut30)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut30 = yblendingalphalut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut29)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut29 = yblendingalphalut29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  yblendingalphalut28)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut28 = yblendingalphalut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut3)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut3 = cblendingalphalut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut2)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut2 = cblendingalphalut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut1)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut1 = cblendingalphalut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut0)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut0 = cblendingalphalut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut7)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut7 = cblendingalphalut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut6)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut6 = cblendingalphalut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut5)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut5 = cblendingalphalut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut4)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut4 = cblendingalphalut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut11)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut11 = cblendingalphalut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut10)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut10 = cblendingalphalut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut9)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut9 = cblendingalphalut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut8)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut8 = cblendingalphalut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut15)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut15 = cblendingalphalut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut14)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut14 = cblendingalphalut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut13)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut13 = cblendingalphalut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut12)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut12 = cblendingalphalut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut19)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut19 = cblendingalphalut19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut18)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut18 = cblendingalphalut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut17)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut17 = cblendingalphalut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut16)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut16 = cblendingalphalut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut23)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut23 = cblendingalphalut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut22)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut22 = cblendingalphalut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut21)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut21 = cblendingalphalut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut20)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut20 = cblendingalphalut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut27)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut27 = cblendingalphalut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut26)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut26 = cblendingalphalut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut25)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut25 = cblendingalphalut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut24)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut24 = cblendingalphalut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut31)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut31 = cblendingalphalut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut30)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut30 = cblendingalphalut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut29)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut29 = cblendingalphalut29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cblendingalphalut28)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut28 = cblendingalphalut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut3)
{
    U_VPSS_TNR_YMOTIONSTR_LUT0 VPSS_TNR_YMOTIONSTR_LUT0;

    VPSS_TNR_YMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32));
    VPSS_TNR_YMOTIONSTR_LUT0.bits.ymotionstrlut3 = ymotionstrlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32), VPSS_TNR_YMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut2)
{
    U_VPSS_TNR_YMOTIONSTR_LUT0 VPSS_TNR_YMOTIONSTR_LUT0;

    VPSS_TNR_YMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32));
    VPSS_TNR_YMOTIONSTR_LUT0.bits.ymotionstrlut2 = ymotionstrlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32), VPSS_TNR_YMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut1)
{
    U_VPSS_TNR_YMOTIONSTR_LUT0 VPSS_TNR_YMOTIONSTR_LUT0;

    VPSS_TNR_YMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32));
    VPSS_TNR_YMOTIONSTR_LUT0.bits.ymotionstrlut1 = ymotionstrlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32), VPSS_TNR_YMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut0)
{
    U_VPSS_TNR_YMOTIONSTR_LUT0 VPSS_TNR_YMOTIONSTR_LUT0;

    VPSS_TNR_YMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32));
    VPSS_TNR_YMOTIONSTR_LUT0.bits.ymotionstrlut0 = ymotionstrlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT0.u32), VPSS_TNR_YMOTIONSTR_LUT0.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut7)
{
    U_VPSS_TNR_YMOTIONSTR_LUT1 VPSS_TNR_YMOTIONSTR_LUT1;

    VPSS_TNR_YMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32));
    VPSS_TNR_YMOTIONSTR_LUT1.bits.ymotionstrlut7 = ymotionstrlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32), VPSS_TNR_YMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut6)
{
    U_VPSS_TNR_YMOTIONSTR_LUT1 VPSS_TNR_YMOTIONSTR_LUT1;

    VPSS_TNR_YMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32));
    VPSS_TNR_YMOTIONSTR_LUT1.bits.ymotionstrlut6 = ymotionstrlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32), VPSS_TNR_YMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut5)
{
    U_VPSS_TNR_YMOTIONSTR_LUT1 VPSS_TNR_YMOTIONSTR_LUT1;

    VPSS_TNR_YMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32));
    VPSS_TNR_YMOTIONSTR_LUT1.bits.ymotionstrlut5 = ymotionstrlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32), VPSS_TNR_YMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut4)
{
    U_VPSS_TNR_YMOTIONSTR_LUT1 VPSS_TNR_YMOTIONSTR_LUT1;

    VPSS_TNR_YMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32));
    VPSS_TNR_YMOTIONSTR_LUT1.bits.ymotionstrlut4 = ymotionstrlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT1.u32), VPSS_TNR_YMOTIONSTR_LUT1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut11)
{
    U_VPSS_TNR_YMOTIONSTR_LUT2 VPSS_TNR_YMOTIONSTR_LUT2;

    VPSS_TNR_YMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32));
    VPSS_TNR_YMOTIONSTR_LUT2.bits.ymotionstrlut11 = ymotionstrlut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32), VPSS_TNR_YMOTIONSTR_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut10)
{
    U_VPSS_TNR_YMOTIONSTR_LUT2 VPSS_TNR_YMOTIONSTR_LUT2;

    VPSS_TNR_YMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32));
    VPSS_TNR_YMOTIONSTR_LUT2.bits.ymotionstrlut10 = ymotionstrlut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32), VPSS_TNR_YMOTIONSTR_LUT2.u32);

    return ;
}

HI_VOID VPSS_Tnr_SetYmotionstrlut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut9)
{
    U_VPSS_TNR_YMOTIONSTR_LUT2 VPSS_TNR_YMOTIONSTR_LUT2;

    VPSS_TNR_YMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32));
    VPSS_TNR_YMOTIONSTR_LUT2.bits.ymotionstrlut9 = ymotionstrlut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32), VPSS_TNR_YMOTIONSTR_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut8)
{
    U_VPSS_TNR_YMOTIONSTR_LUT2 VPSS_TNR_YMOTIONSTR_LUT2;

    VPSS_TNR_YMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32));
    VPSS_TNR_YMOTIONSTR_LUT2.bits.ymotionstrlut8 = ymotionstrlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT2.u32), VPSS_TNR_YMOTIONSTR_LUT2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut15)
{
    U_VPSS_TNR_YMOTIONSTR_LUT3 VPSS_TNR_YMOTIONSTR_LUT3;

    VPSS_TNR_YMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32));
    VPSS_TNR_YMOTIONSTR_LUT3.bits.ymotionstrlut15 = ymotionstrlut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32), VPSS_TNR_YMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut14)
{
    U_VPSS_TNR_YMOTIONSTR_LUT3 VPSS_TNR_YMOTIONSTR_LUT3;

    VPSS_TNR_YMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32));
    VPSS_TNR_YMOTIONSTR_LUT3.bits.ymotionstrlut14 = ymotionstrlut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32), VPSS_TNR_YMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut13)
{
    U_VPSS_TNR_YMOTIONSTR_LUT3 VPSS_TNR_YMOTIONSTR_LUT3;

    VPSS_TNR_YMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32));
    VPSS_TNR_YMOTIONSTR_LUT3.bits.ymotionstrlut13 = ymotionstrlut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32), VPSS_TNR_YMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut12)
{
    U_VPSS_TNR_YMOTIONSTR_LUT3 VPSS_TNR_YMOTIONSTR_LUT3;

    VPSS_TNR_YMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32));
    VPSS_TNR_YMOTIONSTR_LUT3.bits.ymotionstrlut12 = ymotionstrlut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT3.u32), VPSS_TNR_YMOTIONSTR_LUT3.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut19)
{
    U_VPSS_TNR_YMOTIONSTR_LUT4 VPSS_TNR_YMOTIONSTR_LUT4;

    VPSS_TNR_YMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32));
    VPSS_TNR_YMOTIONSTR_LUT4.bits.ymotionstrlut19 = ymotionstrlut19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32), VPSS_TNR_YMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut18)
{
    U_VPSS_TNR_YMOTIONSTR_LUT4 VPSS_TNR_YMOTIONSTR_LUT4;

    VPSS_TNR_YMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32));
    VPSS_TNR_YMOTIONSTR_LUT4.bits.ymotionstrlut18 = ymotionstrlut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32), VPSS_TNR_YMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut17)
{
    U_VPSS_TNR_YMOTIONSTR_LUT4 VPSS_TNR_YMOTIONSTR_LUT4;

    VPSS_TNR_YMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32));
    VPSS_TNR_YMOTIONSTR_LUT4.bits.ymotionstrlut17 = ymotionstrlut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32), VPSS_TNR_YMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut16)
{
    U_VPSS_TNR_YMOTIONSTR_LUT4 VPSS_TNR_YMOTIONSTR_LUT4;

    VPSS_TNR_YMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32));
    VPSS_TNR_YMOTIONSTR_LUT4.bits.ymotionstrlut16 = ymotionstrlut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT4.u32), VPSS_TNR_YMOTIONSTR_LUT4.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut23)
{
    U_VPSS_TNR_YMOTIONSTR_LUT5 VPSS_TNR_YMOTIONSTR_LUT5;

    VPSS_TNR_YMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32));
    VPSS_TNR_YMOTIONSTR_LUT5.bits.ymotionstrlut23 = ymotionstrlut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32), VPSS_TNR_YMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut22)
{
    U_VPSS_TNR_YMOTIONSTR_LUT5 VPSS_TNR_YMOTIONSTR_LUT5;

    VPSS_TNR_YMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32));
    VPSS_TNR_YMOTIONSTR_LUT5.bits.ymotionstrlut22 = ymotionstrlut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32), VPSS_TNR_YMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut21)
{
    U_VPSS_TNR_YMOTIONSTR_LUT5 VPSS_TNR_YMOTIONSTR_LUT5;

    VPSS_TNR_YMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32));
    VPSS_TNR_YMOTIONSTR_LUT5.bits.ymotionstrlut21 = ymotionstrlut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32), VPSS_TNR_YMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut20)
{
    U_VPSS_TNR_YMOTIONSTR_LUT5 VPSS_TNR_YMOTIONSTR_LUT5;

    VPSS_TNR_YMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32));
    VPSS_TNR_YMOTIONSTR_LUT5.bits.ymotionstrlut20 = ymotionstrlut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT5.u32), VPSS_TNR_YMOTIONSTR_LUT5.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut27)
{
    U_VPSS_TNR_YMOTIONSTR_LUT6 VPSS_TNR_YMOTIONSTR_LUT6;

    VPSS_TNR_YMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32));
    VPSS_TNR_YMOTIONSTR_LUT6.bits.ymotionstrlut27 = ymotionstrlut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32), VPSS_TNR_YMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut26)
{
    U_VPSS_TNR_YMOTIONSTR_LUT6 VPSS_TNR_YMOTIONSTR_LUT6;

    VPSS_TNR_YMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32));
    VPSS_TNR_YMOTIONSTR_LUT6.bits.ymotionstrlut26 = ymotionstrlut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32), VPSS_TNR_YMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut25)
{
    U_VPSS_TNR_YMOTIONSTR_LUT6 VPSS_TNR_YMOTIONSTR_LUT6;

    VPSS_TNR_YMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32));
    VPSS_TNR_YMOTIONSTR_LUT6.bits.ymotionstrlut25 = ymotionstrlut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32), VPSS_TNR_YMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut24)
{
    U_VPSS_TNR_YMOTIONSTR_LUT6 VPSS_TNR_YMOTIONSTR_LUT6;

    VPSS_TNR_YMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32));
    VPSS_TNR_YMOTIONSTR_LUT6.bits.ymotionstrlut24 = ymotionstrlut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT6.u32), VPSS_TNR_YMOTIONSTR_LUT6.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut31)
{
    U_VPSS_TNR_YMOTIONSTR_LUT7 VPSS_TNR_YMOTIONSTR_LUT7;

    VPSS_TNR_YMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32));
    VPSS_TNR_YMOTIONSTR_LUT7.bits.ymotionstrlut31 = ymotionstrlut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32), VPSS_TNR_YMOTIONSTR_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut30)
{
    U_VPSS_TNR_YMOTIONSTR_LUT7 VPSS_TNR_YMOTIONSTR_LUT7;

    VPSS_TNR_YMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32));
    VPSS_TNR_YMOTIONSTR_LUT7.bits.ymotionstrlut30 = ymotionstrlut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32), VPSS_TNR_YMOTIONSTR_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut29)
{
    U_VPSS_TNR_YMOTIONSTR_LUT7 VPSS_TNR_YMOTIONSTR_LUT7;

    VPSS_TNR_YMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32));
    VPSS_TNR_YMOTIONSTR_LUT7.bits.ymotionstrlut29 = ymotionstrlut29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32), VPSS_TNR_YMOTIONSTR_LUT7.u32);

    return ;
}

HI_VOID VPSS_Tnr_SetYmotionstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut28)
{
    U_VPSS_TNR_YMOTIONSTR_LUT7 VPSS_TNR_YMOTIONSTR_LUT7;

    VPSS_TNR_YMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32));
    VPSS_TNR_YMOTIONSTR_LUT7.bits.ymotionstrlut28 = ymotionstrlut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT7.u32), VPSS_TNR_YMOTIONSTR_LUT7.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut35)
{
    U_VPSS_TNR_YMOTIONSTR_LUT8 VPSS_TNR_YMOTIONSTR_LUT8;

    VPSS_TNR_YMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32));
    VPSS_TNR_YMOTIONSTR_LUT8.bits.ymotionstrlut35 = ymotionstrlut35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32), VPSS_TNR_YMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut34)
{
    U_VPSS_TNR_YMOTIONSTR_LUT8 VPSS_TNR_YMOTIONSTR_LUT8;

    VPSS_TNR_YMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32));
    VPSS_TNR_YMOTIONSTR_LUT8.bits.ymotionstrlut34 = ymotionstrlut34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32), VPSS_TNR_YMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut33)
{
    U_VPSS_TNR_YMOTIONSTR_LUT8 VPSS_TNR_YMOTIONSTR_LUT8;

    VPSS_TNR_YMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32));
    VPSS_TNR_YMOTIONSTR_LUT8.bits.ymotionstrlut33 = ymotionstrlut33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32), VPSS_TNR_YMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut32)
{
    U_VPSS_TNR_YMOTIONSTR_LUT8 VPSS_TNR_YMOTIONSTR_LUT8;

    VPSS_TNR_YMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32));
    VPSS_TNR_YMOTIONSTR_LUT8.bits.ymotionstrlut32 = ymotionstrlut32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT8.u32), VPSS_TNR_YMOTIONSTR_LUT8.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut39)
{
    U_VPSS_TNR_YMOTIONSTR_LUT9 VPSS_TNR_YMOTIONSTR_LUT9;

    VPSS_TNR_YMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32));
    VPSS_TNR_YMOTIONSTR_LUT9.bits.ymotionstrlut39 = ymotionstrlut39;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32), VPSS_TNR_YMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut38)
{
    U_VPSS_TNR_YMOTIONSTR_LUT9 VPSS_TNR_YMOTIONSTR_LUT9;

    VPSS_TNR_YMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32));
    VPSS_TNR_YMOTIONSTR_LUT9.bits.ymotionstrlut38 = ymotionstrlut38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32), VPSS_TNR_YMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut37)
{
    U_VPSS_TNR_YMOTIONSTR_LUT9 VPSS_TNR_YMOTIONSTR_LUT9;

    VPSS_TNR_YMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32));
    VPSS_TNR_YMOTIONSTR_LUT9.bits.ymotionstrlut37 = ymotionstrlut37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32), VPSS_TNR_YMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut36)
{
    U_VPSS_TNR_YMOTIONSTR_LUT9 VPSS_TNR_YMOTIONSTR_LUT9;

    VPSS_TNR_YMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32));
    VPSS_TNR_YMOTIONSTR_LUT9.bits.ymotionstrlut36 = ymotionstrlut36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT9.u32), VPSS_TNR_YMOTIONSTR_LUT9.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut43)
{
    U_VPSS_TNR_YMOTIONSTR_LUT10 VPSS_TNR_YMOTIONSTR_LUT10;

    VPSS_TNR_YMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32));
    VPSS_TNR_YMOTIONSTR_LUT10.bits.ymotionstrlut43 = ymotionstrlut43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32), VPSS_TNR_YMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut42)
{
    U_VPSS_TNR_YMOTIONSTR_LUT10 VPSS_TNR_YMOTIONSTR_LUT10;

    VPSS_TNR_YMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32));
    VPSS_TNR_YMOTIONSTR_LUT10.bits.ymotionstrlut42 = ymotionstrlut42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32), VPSS_TNR_YMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut41)
{
    U_VPSS_TNR_YMOTIONSTR_LUT10 VPSS_TNR_YMOTIONSTR_LUT10;

    VPSS_TNR_YMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32));
    VPSS_TNR_YMOTIONSTR_LUT10.bits.ymotionstrlut41 = ymotionstrlut41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32), VPSS_TNR_YMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut40)
{
    U_VPSS_TNR_YMOTIONSTR_LUT10 VPSS_TNR_YMOTIONSTR_LUT10;

    VPSS_TNR_YMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32));
    VPSS_TNR_YMOTIONSTR_LUT10.bits.ymotionstrlut40 = ymotionstrlut40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT10.u32), VPSS_TNR_YMOTIONSTR_LUT10.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut47)
{
    U_VPSS_TNR_YMOTIONSTR_LUT11 VPSS_TNR_YMOTIONSTR_LUT11;

    VPSS_TNR_YMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32));
    VPSS_TNR_YMOTIONSTR_LUT11.bits.ymotionstrlut47 = ymotionstrlut47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32), VPSS_TNR_YMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut46)
{
    U_VPSS_TNR_YMOTIONSTR_LUT11 VPSS_TNR_YMOTIONSTR_LUT11;

    VPSS_TNR_YMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32));
    VPSS_TNR_YMOTIONSTR_LUT11.bits.ymotionstrlut46 = ymotionstrlut46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32), VPSS_TNR_YMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut45)
{
    U_VPSS_TNR_YMOTIONSTR_LUT11 VPSS_TNR_YMOTIONSTR_LUT11;

    VPSS_TNR_YMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32));
    VPSS_TNR_YMOTIONSTR_LUT11.bits.ymotionstrlut45 = ymotionstrlut45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32), VPSS_TNR_YMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut44)
{
    U_VPSS_TNR_YMOTIONSTR_LUT11 VPSS_TNR_YMOTIONSTR_LUT11;

    VPSS_TNR_YMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32));
    VPSS_TNR_YMOTIONSTR_LUT11.bits.ymotionstrlut44 = ymotionstrlut44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT11.u32), VPSS_TNR_YMOTIONSTR_LUT11.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut51)
{
    U_VPSS_TNR_YMOTIONSTR_LUT12 VPSS_TNR_YMOTIONSTR_LUT12;

    VPSS_TNR_YMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32));
    VPSS_TNR_YMOTIONSTR_LUT12.bits.ymotionstrlut51 = ymotionstrlut51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32), VPSS_TNR_YMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut50)
{
    U_VPSS_TNR_YMOTIONSTR_LUT12 VPSS_TNR_YMOTIONSTR_LUT12;

    VPSS_TNR_YMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32));
    VPSS_TNR_YMOTIONSTR_LUT12.bits.ymotionstrlut50 = ymotionstrlut50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32), VPSS_TNR_YMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut49)
{
    U_VPSS_TNR_YMOTIONSTR_LUT12 VPSS_TNR_YMOTIONSTR_LUT12;

    VPSS_TNR_YMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32));
    VPSS_TNR_YMOTIONSTR_LUT12.bits.ymotionstrlut49 = ymotionstrlut49;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32), VPSS_TNR_YMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut48)
{
    U_VPSS_TNR_YMOTIONSTR_LUT12 VPSS_TNR_YMOTIONSTR_LUT12;

    VPSS_TNR_YMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32));
    VPSS_TNR_YMOTIONSTR_LUT12.bits.ymotionstrlut48 = ymotionstrlut48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT12.u32), VPSS_TNR_YMOTIONSTR_LUT12.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut55)
{
    U_VPSS_TNR_YMOTIONSTR_LUT13 VPSS_TNR_YMOTIONSTR_LUT13;

    VPSS_TNR_YMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32));
    VPSS_TNR_YMOTIONSTR_LUT13.bits.ymotionstrlut55 = ymotionstrlut55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32), VPSS_TNR_YMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut54)
{
    U_VPSS_TNR_YMOTIONSTR_LUT13 VPSS_TNR_YMOTIONSTR_LUT13;

    VPSS_TNR_YMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32));
    VPSS_TNR_YMOTIONSTR_LUT13.bits.ymotionstrlut54 = ymotionstrlut54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32), VPSS_TNR_YMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut53)
{
    U_VPSS_TNR_YMOTIONSTR_LUT13 VPSS_TNR_YMOTIONSTR_LUT13;

    VPSS_TNR_YMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32));
    VPSS_TNR_YMOTIONSTR_LUT13.bits.ymotionstrlut53 = ymotionstrlut53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32), VPSS_TNR_YMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut52)
{
    U_VPSS_TNR_YMOTIONSTR_LUT13 VPSS_TNR_YMOTIONSTR_LUT13;

    VPSS_TNR_YMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32));
    VPSS_TNR_YMOTIONSTR_LUT13.bits.ymotionstrlut52 = ymotionstrlut52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT13.u32), VPSS_TNR_YMOTIONSTR_LUT13.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut59)
{
    U_VPSS_TNR_YMOTIONSTR_LUT14 VPSS_TNR_YMOTIONSTR_LUT14;

    VPSS_TNR_YMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32));
    VPSS_TNR_YMOTIONSTR_LUT14.bits.ymotionstrlut59 = ymotionstrlut59;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32), VPSS_TNR_YMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut58)
{
    U_VPSS_TNR_YMOTIONSTR_LUT14 VPSS_TNR_YMOTIONSTR_LUT14;

    VPSS_TNR_YMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32));
    VPSS_TNR_YMOTIONSTR_LUT14.bits.ymotionstrlut58 = ymotionstrlut58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32), VPSS_TNR_YMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut57)
{
    U_VPSS_TNR_YMOTIONSTR_LUT14 VPSS_TNR_YMOTIONSTR_LUT14;

    VPSS_TNR_YMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32));
    VPSS_TNR_YMOTIONSTR_LUT14.bits.ymotionstrlut57 = ymotionstrlut57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32), VPSS_TNR_YMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut56)
{
    U_VPSS_TNR_YMOTIONSTR_LUT14 VPSS_TNR_YMOTIONSTR_LUT14;

    VPSS_TNR_YMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32));
    VPSS_TNR_YMOTIONSTR_LUT14.bits.ymotionstrlut56 = ymotionstrlut56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT14.u32), VPSS_TNR_YMOTIONSTR_LUT14.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut63)
{
    U_VPSS_TNR_YMOTIONSTR_LUT15 VPSS_TNR_YMOTIONSTR_LUT15;

    VPSS_TNR_YMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32));
    VPSS_TNR_YMOTIONSTR_LUT15.bits.ymotionstrlut63 = ymotionstrlut63;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32), VPSS_TNR_YMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut62)
{
    U_VPSS_TNR_YMOTIONSTR_LUT15 VPSS_TNR_YMOTIONSTR_LUT15;

    VPSS_TNR_YMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32));
    VPSS_TNR_YMOTIONSTR_LUT15.bits.ymotionstrlut62 = ymotionstrlut62;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32), VPSS_TNR_YMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut61)
{
    U_VPSS_TNR_YMOTIONSTR_LUT15 VPSS_TNR_YMOTIONSTR_LUT15;

    VPSS_TNR_YMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32));
    VPSS_TNR_YMOTIONSTR_LUT15.bits.ymotionstrlut61 = ymotionstrlut61;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32), VPSS_TNR_YMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut60)
{
    U_VPSS_TNR_YMOTIONSTR_LUT15 VPSS_TNR_YMOTIONSTR_LUT15;

    VPSS_TNR_YMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32));
    VPSS_TNR_YMOTIONSTR_LUT15.bits.ymotionstrlut60 = ymotionstrlut60;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT15.u32), VPSS_TNR_YMOTIONSTR_LUT15.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut67)
{
    U_VPSS_TNR_YMOTIONSTR_LUT16 VPSS_TNR_YMOTIONSTR_LUT16;

    VPSS_TNR_YMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32));
    VPSS_TNR_YMOTIONSTR_LUT16.bits.ymotionstrlut67 = ymotionstrlut67;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32), VPSS_TNR_YMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut66)
{
    U_VPSS_TNR_YMOTIONSTR_LUT16 VPSS_TNR_YMOTIONSTR_LUT16;

    VPSS_TNR_YMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32));
    VPSS_TNR_YMOTIONSTR_LUT16.bits.ymotionstrlut66 = ymotionstrlut66;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32), VPSS_TNR_YMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut65)
{
    U_VPSS_TNR_YMOTIONSTR_LUT16 VPSS_TNR_YMOTIONSTR_LUT16;

    VPSS_TNR_YMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32));
    VPSS_TNR_YMOTIONSTR_LUT16.bits.ymotionstrlut65 = ymotionstrlut65;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32), VPSS_TNR_YMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut64)
{
    U_VPSS_TNR_YMOTIONSTR_LUT16 VPSS_TNR_YMOTIONSTR_LUT16;

    VPSS_TNR_YMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32));
    VPSS_TNR_YMOTIONSTR_LUT16.bits.ymotionstrlut64 = ymotionstrlut64;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT16.u32), VPSS_TNR_YMOTIONSTR_LUT16.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut71)
{
    U_VPSS_TNR_YMOTIONSTR_LUT17 VPSS_TNR_YMOTIONSTR_LUT17;

    VPSS_TNR_YMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32));
    VPSS_TNR_YMOTIONSTR_LUT17.bits.ymotionstrlut71 = ymotionstrlut71;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32), VPSS_TNR_YMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut70)
{
    U_VPSS_TNR_YMOTIONSTR_LUT17 VPSS_TNR_YMOTIONSTR_LUT17;

    VPSS_TNR_YMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32));
    VPSS_TNR_YMOTIONSTR_LUT17.bits.ymotionstrlut70 = ymotionstrlut70;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32), VPSS_TNR_YMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut69)
{
    U_VPSS_TNR_YMOTIONSTR_LUT17 VPSS_TNR_YMOTIONSTR_LUT17;

    VPSS_TNR_YMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32));
    VPSS_TNR_YMOTIONSTR_LUT17.bits.ymotionstrlut69 = ymotionstrlut69;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32), VPSS_TNR_YMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut68)
{
    U_VPSS_TNR_YMOTIONSTR_LUT17 VPSS_TNR_YMOTIONSTR_LUT17;

    VPSS_TNR_YMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32));
    VPSS_TNR_YMOTIONSTR_LUT17.bits.ymotionstrlut68 = ymotionstrlut68;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT17.u32), VPSS_TNR_YMOTIONSTR_LUT17.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut75)
{
    U_VPSS_TNR_YMOTIONSTR_LUT18 VPSS_TNR_YMOTIONSTR_LUT18;

    VPSS_TNR_YMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32));
    VPSS_TNR_YMOTIONSTR_LUT18.bits.ymotionstrlut75 = ymotionstrlut75;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32), VPSS_TNR_YMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut74)
{
    U_VPSS_TNR_YMOTIONSTR_LUT18 VPSS_TNR_YMOTIONSTR_LUT18;

    VPSS_TNR_YMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32));
    VPSS_TNR_YMOTIONSTR_LUT18.bits.ymotionstrlut74 = ymotionstrlut74;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32), VPSS_TNR_YMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut73)
{
    U_VPSS_TNR_YMOTIONSTR_LUT18 VPSS_TNR_YMOTIONSTR_LUT18;

    VPSS_TNR_YMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32));
    VPSS_TNR_YMOTIONSTR_LUT18.bits.ymotionstrlut73 = ymotionstrlut73;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32), VPSS_TNR_YMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut72)
{
    U_VPSS_TNR_YMOTIONSTR_LUT18 VPSS_TNR_YMOTIONSTR_LUT18;

    VPSS_TNR_YMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32));
    VPSS_TNR_YMOTIONSTR_LUT18.bits.ymotionstrlut72 = ymotionstrlut72;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT18.u32), VPSS_TNR_YMOTIONSTR_LUT18.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut79)
{
    U_VPSS_TNR_YMOTIONSTR_LUT19 VPSS_TNR_YMOTIONSTR_LUT19;

    VPSS_TNR_YMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32));
    VPSS_TNR_YMOTIONSTR_LUT19.bits.ymotionstrlut79 = ymotionstrlut79;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32), VPSS_TNR_YMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut78)
{
    U_VPSS_TNR_YMOTIONSTR_LUT19 VPSS_TNR_YMOTIONSTR_LUT19;

    VPSS_TNR_YMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32));
    VPSS_TNR_YMOTIONSTR_LUT19.bits.ymotionstrlut78 = ymotionstrlut78;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32), VPSS_TNR_YMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut77)
{
    U_VPSS_TNR_YMOTIONSTR_LUT19 VPSS_TNR_YMOTIONSTR_LUT19;

    VPSS_TNR_YMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32));
    VPSS_TNR_YMOTIONSTR_LUT19.bits.ymotionstrlut77 = ymotionstrlut77;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32), VPSS_TNR_YMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut76)
{
    U_VPSS_TNR_YMOTIONSTR_LUT19 VPSS_TNR_YMOTIONSTR_LUT19;

    VPSS_TNR_YMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32));
    VPSS_TNR_YMOTIONSTR_LUT19.bits.ymotionstrlut76 = ymotionstrlut76;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT19.u32), VPSS_TNR_YMOTIONSTR_LUT19.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut83)
{
    U_VPSS_TNR_YMOTIONSTR_LUT20 VPSS_TNR_YMOTIONSTR_LUT20;

    VPSS_TNR_YMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32));
    VPSS_TNR_YMOTIONSTR_LUT20.bits.ymotionstrlut83 = ymotionstrlut83;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32), VPSS_TNR_YMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut82)
{
    U_VPSS_TNR_YMOTIONSTR_LUT20 VPSS_TNR_YMOTIONSTR_LUT20;

    VPSS_TNR_YMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32));
    VPSS_TNR_YMOTIONSTR_LUT20.bits.ymotionstrlut82 = ymotionstrlut82;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32), VPSS_TNR_YMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut81)
{
    U_VPSS_TNR_YMOTIONSTR_LUT20 VPSS_TNR_YMOTIONSTR_LUT20;

    VPSS_TNR_YMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32));
    VPSS_TNR_YMOTIONSTR_LUT20.bits.ymotionstrlut81 = ymotionstrlut81;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32), VPSS_TNR_YMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut80)
{
    U_VPSS_TNR_YMOTIONSTR_LUT20 VPSS_TNR_YMOTIONSTR_LUT20;

    VPSS_TNR_YMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32));
    VPSS_TNR_YMOTIONSTR_LUT20.bits.ymotionstrlut80 = ymotionstrlut80;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT20.u32), VPSS_TNR_YMOTIONSTR_LUT20.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut87)
{
    U_VPSS_TNR_YMOTIONSTR_LUT21 VPSS_TNR_YMOTIONSTR_LUT21;

    VPSS_TNR_YMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32));
    VPSS_TNR_YMOTIONSTR_LUT21.bits.ymotionstrlut87 = ymotionstrlut87;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32), VPSS_TNR_YMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut86)
{
    U_VPSS_TNR_YMOTIONSTR_LUT21 VPSS_TNR_YMOTIONSTR_LUT21;

    VPSS_TNR_YMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32));
    VPSS_TNR_YMOTIONSTR_LUT21.bits.ymotionstrlut86 = ymotionstrlut86;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32), VPSS_TNR_YMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut85)
{
    U_VPSS_TNR_YMOTIONSTR_LUT21 VPSS_TNR_YMOTIONSTR_LUT21;

    VPSS_TNR_YMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32));
    VPSS_TNR_YMOTIONSTR_LUT21.bits.ymotionstrlut85 = ymotionstrlut85;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32), VPSS_TNR_YMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut84)
{
    U_VPSS_TNR_YMOTIONSTR_LUT21 VPSS_TNR_YMOTIONSTR_LUT21;

    VPSS_TNR_YMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32));
    VPSS_TNR_YMOTIONSTR_LUT21.bits.ymotionstrlut84 = ymotionstrlut84;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT21.u32), VPSS_TNR_YMOTIONSTR_LUT21.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut91)
{
    U_VPSS_TNR_YMOTIONSTR_LUT22 VPSS_TNR_YMOTIONSTR_LUT22;

    VPSS_TNR_YMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32));
    VPSS_TNR_YMOTIONSTR_LUT22.bits.ymotionstrlut91 = ymotionstrlut91;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32), VPSS_TNR_YMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut90)
{
    U_VPSS_TNR_YMOTIONSTR_LUT22 VPSS_TNR_YMOTIONSTR_LUT22;

    VPSS_TNR_YMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32));
    VPSS_TNR_YMOTIONSTR_LUT22.bits.ymotionstrlut90 = ymotionstrlut90;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32), VPSS_TNR_YMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut89)
{
    U_VPSS_TNR_YMOTIONSTR_LUT22 VPSS_TNR_YMOTIONSTR_LUT22;

    VPSS_TNR_YMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32));
    VPSS_TNR_YMOTIONSTR_LUT22.bits.ymotionstrlut89 = ymotionstrlut89;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32), VPSS_TNR_YMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut88)
{
    U_VPSS_TNR_YMOTIONSTR_LUT22 VPSS_TNR_YMOTIONSTR_LUT22;

    VPSS_TNR_YMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32));
    VPSS_TNR_YMOTIONSTR_LUT22.bits.ymotionstrlut88 = ymotionstrlut88;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT22.u32), VPSS_TNR_YMOTIONSTR_LUT22.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut95)
{
    U_VPSS_TNR_YMOTIONSTR_LUT23 VPSS_TNR_YMOTIONSTR_LUT23;

    VPSS_TNR_YMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32));
    VPSS_TNR_YMOTIONSTR_LUT23.bits.ymotionstrlut95 = ymotionstrlut95;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32), VPSS_TNR_YMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut94)
{
    U_VPSS_TNR_YMOTIONSTR_LUT23 VPSS_TNR_YMOTIONSTR_LUT23;

    VPSS_TNR_YMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32));
    VPSS_TNR_YMOTIONSTR_LUT23.bits.ymotionstrlut94 = ymotionstrlut94;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32), VPSS_TNR_YMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut93)
{
    U_VPSS_TNR_YMOTIONSTR_LUT23 VPSS_TNR_YMOTIONSTR_LUT23;

    VPSS_TNR_YMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32));
    VPSS_TNR_YMOTIONSTR_LUT23.bits.ymotionstrlut93 = ymotionstrlut93;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32), VPSS_TNR_YMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut92)
{
    U_VPSS_TNR_YMOTIONSTR_LUT23 VPSS_TNR_YMOTIONSTR_LUT23;

    VPSS_TNR_YMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32));
    VPSS_TNR_YMOTIONSTR_LUT23.bits.ymotionstrlut92 = ymotionstrlut92;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT23.u32), VPSS_TNR_YMOTIONSTR_LUT23.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut99)
{
    U_VPSS_TNR_YMOTIONSTR_LUT24 VPSS_TNR_YMOTIONSTR_LUT24;

    VPSS_TNR_YMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32));
    VPSS_TNR_YMOTIONSTR_LUT24.bits.ymotionstrlut99 = ymotionstrlut99;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32), VPSS_TNR_YMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut98)
{
    U_VPSS_TNR_YMOTIONSTR_LUT24 VPSS_TNR_YMOTIONSTR_LUT24;

    VPSS_TNR_YMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32));
    VPSS_TNR_YMOTIONSTR_LUT24.bits.ymotionstrlut98 = ymotionstrlut98;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32), VPSS_TNR_YMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut97)
{
    U_VPSS_TNR_YMOTIONSTR_LUT24 VPSS_TNR_YMOTIONSTR_LUT24;

    VPSS_TNR_YMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32));
    VPSS_TNR_YMOTIONSTR_LUT24.bits.ymotionstrlut97 = ymotionstrlut97;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32), VPSS_TNR_YMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut96)
{
    U_VPSS_TNR_YMOTIONSTR_LUT24 VPSS_TNR_YMOTIONSTR_LUT24;

    VPSS_TNR_YMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32));
    VPSS_TNR_YMOTIONSTR_LUT24.bits.ymotionstrlut96 = ymotionstrlut96;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT24.u32), VPSS_TNR_YMOTIONSTR_LUT24.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut103(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut103)
{
    U_VPSS_TNR_YMOTIONSTR_LUT25 VPSS_TNR_YMOTIONSTR_LUT25;

    VPSS_TNR_YMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32));
    VPSS_TNR_YMOTIONSTR_LUT25.bits.ymotionstrlut103 = ymotionstrlut103;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32), VPSS_TNR_YMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut102(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut102)
{
    U_VPSS_TNR_YMOTIONSTR_LUT25 VPSS_TNR_YMOTIONSTR_LUT25;

    VPSS_TNR_YMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32));
    VPSS_TNR_YMOTIONSTR_LUT25.bits.ymotionstrlut102 = ymotionstrlut102;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32), VPSS_TNR_YMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut101(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut101)
{
    U_VPSS_TNR_YMOTIONSTR_LUT25 VPSS_TNR_YMOTIONSTR_LUT25;

    VPSS_TNR_YMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32));
    VPSS_TNR_YMOTIONSTR_LUT25.bits.ymotionstrlut101 = ymotionstrlut101;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32), VPSS_TNR_YMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut100(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut100)
{
    U_VPSS_TNR_YMOTIONSTR_LUT25 VPSS_TNR_YMOTIONSTR_LUT25;

    VPSS_TNR_YMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32));
    VPSS_TNR_YMOTIONSTR_LUT25.bits.ymotionstrlut100 = ymotionstrlut100;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT25.u32), VPSS_TNR_YMOTIONSTR_LUT25.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut107(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut107)
{
    U_VPSS_TNR_YMOTIONSTR_LUT26 VPSS_TNR_YMOTIONSTR_LUT26;

    VPSS_TNR_YMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32));
    VPSS_TNR_YMOTIONSTR_LUT26.bits.ymotionstrlut107 = ymotionstrlut107;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32), VPSS_TNR_YMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut106(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut106)
{
    U_VPSS_TNR_YMOTIONSTR_LUT26 VPSS_TNR_YMOTIONSTR_LUT26;

    VPSS_TNR_YMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32));
    VPSS_TNR_YMOTIONSTR_LUT26.bits.ymotionstrlut106 = ymotionstrlut106;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32), VPSS_TNR_YMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut105(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut105)
{
    U_VPSS_TNR_YMOTIONSTR_LUT26 VPSS_TNR_YMOTIONSTR_LUT26;

    VPSS_TNR_YMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32));
    VPSS_TNR_YMOTIONSTR_LUT26.bits.ymotionstrlut105 = ymotionstrlut105;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32), VPSS_TNR_YMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut104(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut104)
{
    U_VPSS_TNR_YMOTIONSTR_LUT26 VPSS_TNR_YMOTIONSTR_LUT26;

    VPSS_TNR_YMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32));
    VPSS_TNR_YMOTIONSTR_LUT26.bits.ymotionstrlut104 = ymotionstrlut104;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT26.u32), VPSS_TNR_YMOTIONSTR_LUT26.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut111(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut111)
{
    U_VPSS_TNR_YMOTIONSTR_LUT27 VPSS_TNR_YMOTIONSTR_LUT27;

    VPSS_TNR_YMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32));
    VPSS_TNR_YMOTIONSTR_LUT27.bits.ymotionstrlut111 = ymotionstrlut111;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32), VPSS_TNR_YMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut110(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut110)
{
    U_VPSS_TNR_YMOTIONSTR_LUT27 VPSS_TNR_YMOTIONSTR_LUT27;

    VPSS_TNR_YMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32));
    VPSS_TNR_YMOTIONSTR_LUT27.bits.ymotionstrlut110 = ymotionstrlut110;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32), VPSS_TNR_YMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut109(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut109)
{
    U_VPSS_TNR_YMOTIONSTR_LUT27 VPSS_TNR_YMOTIONSTR_LUT27;

    VPSS_TNR_YMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32));
    VPSS_TNR_YMOTIONSTR_LUT27.bits.ymotionstrlut109 = ymotionstrlut109;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32), VPSS_TNR_YMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut108(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut108)
{
    U_VPSS_TNR_YMOTIONSTR_LUT27 VPSS_TNR_YMOTIONSTR_LUT27;

    VPSS_TNR_YMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32));
    VPSS_TNR_YMOTIONSTR_LUT27.bits.ymotionstrlut108 = ymotionstrlut108;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT27.u32), VPSS_TNR_YMOTIONSTR_LUT27.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut115(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut115)
{
    U_VPSS_TNR_YMOTIONSTR_LUT28 VPSS_TNR_YMOTIONSTR_LUT28;

    VPSS_TNR_YMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32));
    VPSS_TNR_YMOTIONSTR_LUT28.bits.ymotionstrlut115 = ymotionstrlut115;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32), VPSS_TNR_YMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut114(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut114)
{
    U_VPSS_TNR_YMOTIONSTR_LUT28 VPSS_TNR_YMOTIONSTR_LUT28;

    VPSS_TNR_YMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32));
    VPSS_TNR_YMOTIONSTR_LUT28.bits.ymotionstrlut114 = ymotionstrlut114;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32), VPSS_TNR_YMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut113(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut113)
{
    U_VPSS_TNR_YMOTIONSTR_LUT28 VPSS_TNR_YMOTIONSTR_LUT28;

    VPSS_TNR_YMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32));
    VPSS_TNR_YMOTIONSTR_LUT28.bits.ymotionstrlut113 = ymotionstrlut113;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32), VPSS_TNR_YMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut112(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut112)
{
    U_VPSS_TNR_YMOTIONSTR_LUT28 VPSS_TNR_YMOTIONSTR_LUT28;

    VPSS_TNR_YMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32));
    VPSS_TNR_YMOTIONSTR_LUT28.bits.ymotionstrlut112 = ymotionstrlut112;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT28.u32), VPSS_TNR_YMOTIONSTR_LUT28.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut119(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut119)
{
    U_VPSS_TNR_YMOTIONSTR_LUT29 VPSS_TNR_YMOTIONSTR_LUT29;

    VPSS_TNR_YMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32));
    VPSS_TNR_YMOTIONSTR_LUT29.bits.ymotionstrlut119 = ymotionstrlut119;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32), VPSS_TNR_YMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut118(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut118)
{
    U_VPSS_TNR_YMOTIONSTR_LUT29 VPSS_TNR_YMOTIONSTR_LUT29;

    VPSS_TNR_YMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32));
    VPSS_TNR_YMOTIONSTR_LUT29.bits.ymotionstrlut118 = ymotionstrlut118;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32), VPSS_TNR_YMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut117(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut117)
{
    U_VPSS_TNR_YMOTIONSTR_LUT29 VPSS_TNR_YMOTIONSTR_LUT29;

    VPSS_TNR_YMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32));
    VPSS_TNR_YMOTIONSTR_LUT29.bits.ymotionstrlut117 = ymotionstrlut117;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32), VPSS_TNR_YMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut116(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut116)
{
    U_VPSS_TNR_YMOTIONSTR_LUT29 VPSS_TNR_YMOTIONSTR_LUT29;

    VPSS_TNR_YMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32));
    VPSS_TNR_YMOTIONSTR_LUT29.bits.ymotionstrlut116 = ymotionstrlut116;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT29.u32), VPSS_TNR_YMOTIONSTR_LUT29.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut123(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut123)
{
    U_VPSS_TNR_YMOTIONSTR_LUT30 VPSS_TNR_YMOTIONSTR_LUT30;

    VPSS_TNR_YMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32));
    VPSS_TNR_YMOTIONSTR_LUT30.bits.ymotionstrlut123 = ymotionstrlut123;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32), VPSS_TNR_YMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut122(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut122)
{
    U_VPSS_TNR_YMOTIONSTR_LUT30 VPSS_TNR_YMOTIONSTR_LUT30;

    VPSS_TNR_YMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32));
    VPSS_TNR_YMOTIONSTR_LUT30.bits.ymotionstrlut122 = ymotionstrlut122;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32), VPSS_TNR_YMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut121(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut121)
{
    U_VPSS_TNR_YMOTIONSTR_LUT30 VPSS_TNR_YMOTIONSTR_LUT30;

    VPSS_TNR_YMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32));
    VPSS_TNR_YMOTIONSTR_LUT30.bits.ymotionstrlut121 = ymotionstrlut121;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32), VPSS_TNR_YMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut120(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut120)
{
    U_VPSS_TNR_YMOTIONSTR_LUT30 VPSS_TNR_YMOTIONSTR_LUT30;

    VPSS_TNR_YMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32));
    VPSS_TNR_YMOTIONSTR_LUT30.bits.ymotionstrlut120 = ymotionstrlut120;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT30.u32), VPSS_TNR_YMOTIONSTR_LUT30.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetYmotionstrlut127(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut127)
{
    U_VPSS_TNR_YMOTIONSTR_LUT31 VPSS_TNR_YMOTIONSTR_LUT31;

    VPSS_TNR_YMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32));
    VPSS_TNR_YMOTIONSTR_LUT31.bits.ymotionstrlut127 = ymotionstrlut127;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32), VPSS_TNR_YMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut126(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut126)
{
    U_VPSS_TNR_YMOTIONSTR_LUT31 VPSS_TNR_YMOTIONSTR_LUT31;

    VPSS_TNR_YMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32));
    VPSS_TNR_YMOTIONSTR_LUT31.bits.ymotionstrlut126 = ymotionstrlut126;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32), VPSS_TNR_YMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut125(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut125)
{
    U_VPSS_TNR_YMOTIONSTR_LUT31 VPSS_TNR_YMOTIONSTR_LUT31;

    VPSS_TNR_YMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32));
    VPSS_TNR_YMOTIONSTR_LUT31.bits.ymotionstrlut125 = ymotionstrlut125;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32), VPSS_TNR_YMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetYmotionstrlut124(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  ymotionstrlut124)
{
    U_VPSS_TNR_YMOTIONSTR_LUT31 VPSS_TNR_YMOTIONSTR_LUT31;

    VPSS_TNR_YMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32));
    VPSS_TNR_YMOTIONSTR_LUT31.bits.ymotionstrlut124 = ymotionstrlut124;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_YMOTIONSTR_LUT31.u32), VPSS_TNR_YMOTIONSTR_LUT31.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut3)
{
    U_VPSS_TNR_CMOTIONSTR_LUT0 VPSS_TNR_CMOTIONSTR_LUT0;

    VPSS_TNR_CMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32));
    VPSS_TNR_CMOTIONSTR_LUT0.bits.cmotionstrlut3 = cmotionstrlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32), VPSS_TNR_CMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut2)
{
    U_VPSS_TNR_CMOTIONSTR_LUT0 VPSS_TNR_CMOTIONSTR_LUT0;

    VPSS_TNR_CMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32));
    VPSS_TNR_CMOTIONSTR_LUT0.bits.cmotionstrlut2 = cmotionstrlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32), VPSS_TNR_CMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut1)
{
    U_VPSS_TNR_CMOTIONSTR_LUT0 VPSS_TNR_CMOTIONSTR_LUT0;

    VPSS_TNR_CMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32));
    VPSS_TNR_CMOTIONSTR_LUT0.bits.cmotionstrlut1 = cmotionstrlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32), VPSS_TNR_CMOTIONSTR_LUT0.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut0)
{
    U_VPSS_TNR_CMOTIONSTR_LUT0 VPSS_TNR_CMOTIONSTR_LUT0;

    VPSS_TNR_CMOTIONSTR_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32));
    VPSS_TNR_CMOTIONSTR_LUT0.bits.cmotionstrlut0 = cmotionstrlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT0.u32), VPSS_TNR_CMOTIONSTR_LUT0.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut7)
{
    U_VPSS_TNR_CMOTIONSTR_LUT1 VPSS_TNR_CMOTIONSTR_LUT1;

    VPSS_TNR_CMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32));
    VPSS_TNR_CMOTIONSTR_LUT1.bits.cmotionstrlut7 = cmotionstrlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32), VPSS_TNR_CMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut6)
{
    U_VPSS_TNR_CMOTIONSTR_LUT1 VPSS_TNR_CMOTIONSTR_LUT1;

    VPSS_TNR_CMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32));
    VPSS_TNR_CMOTIONSTR_LUT1.bits.cmotionstrlut6 = cmotionstrlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32), VPSS_TNR_CMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut5)
{
    U_VPSS_TNR_CMOTIONSTR_LUT1 VPSS_TNR_CMOTIONSTR_LUT1;

    VPSS_TNR_CMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32));
    VPSS_TNR_CMOTIONSTR_LUT1.bits.cmotionstrlut5 = cmotionstrlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32), VPSS_TNR_CMOTIONSTR_LUT1.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut4)
{
    U_VPSS_TNR_CMOTIONSTR_LUT1 VPSS_TNR_CMOTIONSTR_LUT1;

    VPSS_TNR_CMOTIONSTR_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32));
    VPSS_TNR_CMOTIONSTR_LUT1.bits.cmotionstrlut4 = cmotionstrlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT1.u32), VPSS_TNR_CMOTIONSTR_LUT1.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut11)
{
    U_VPSS_TNR_CMOTIONSTR_LUT2 VPSS_TNR_CMOTIONSTR_LUT2;

    VPSS_TNR_CMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32));
    VPSS_TNR_CMOTIONSTR_LUT2.bits.cmotionstrlut11 = cmotionstrlut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32), VPSS_TNR_CMOTIONSTR_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut10)
{
    U_VPSS_TNR_CMOTIONSTR_LUT2 VPSS_TNR_CMOTIONSTR_LUT2;

    VPSS_TNR_CMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32));
    VPSS_TNR_CMOTIONSTR_LUT2.bits.cmotionstrlut10 = cmotionstrlut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32), VPSS_TNR_CMOTIONSTR_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut9)
{
    U_VPSS_TNR_CMOTIONSTR_LUT2 VPSS_TNR_CMOTIONSTR_LUT2;

    VPSS_TNR_CMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32));
    VPSS_TNR_CMOTIONSTR_LUT2.bits.cmotionstrlut9 = cmotionstrlut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32), VPSS_TNR_CMOTIONSTR_LUT2.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut8)
{
    U_VPSS_TNR_CMOTIONSTR_LUT2 VPSS_TNR_CMOTIONSTR_LUT2;

    VPSS_TNR_CMOTIONSTR_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32));
    VPSS_TNR_CMOTIONSTR_LUT2.bits.cmotionstrlut8 = cmotionstrlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT2.u32), VPSS_TNR_CMOTIONSTR_LUT2.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut15)
{
    U_VPSS_TNR_CMOTIONSTR_LUT3 VPSS_TNR_CMOTIONSTR_LUT3;

    VPSS_TNR_CMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32));
    VPSS_TNR_CMOTIONSTR_LUT3.bits.cmotionstrlut15 = cmotionstrlut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32), VPSS_TNR_CMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut14)
{
    U_VPSS_TNR_CMOTIONSTR_LUT3 VPSS_TNR_CMOTIONSTR_LUT3;

    VPSS_TNR_CMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32));
    VPSS_TNR_CMOTIONSTR_LUT3.bits.cmotionstrlut14 = cmotionstrlut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32), VPSS_TNR_CMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut13)
{
    U_VPSS_TNR_CMOTIONSTR_LUT3 VPSS_TNR_CMOTIONSTR_LUT3;

    VPSS_TNR_CMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32));
    VPSS_TNR_CMOTIONSTR_LUT3.bits.cmotionstrlut13 = cmotionstrlut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32), VPSS_TNR_CMOTIONSTR_LUT3.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut12)
{
    U_VPSS_TNR_CMOTIONSTR_LUT3 VPSS_TNR_CMOTIONSTR_LUT3;

    VPSS_TNR_CMOTIONSTR_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32));
    VPSS_TNR_CMOTIONSTR_LUT3.bits.cmotionstrlut12 = cmotionstrlut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT3.u32), VPSS_TNR_CMOTIONSTR_LUT3.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut19)
{
    U_VPSS_TNR_CMOTIONSTR_LUT4 VPSS_TNR_CMOTIONSTR_LUT4;

    VPSS_TNR_CMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32));
    VPSS_TNR_CMOTIONSTR_LUT4.bits.cmotionstrlut19 = cmotionstrlut19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32), VPSS_TNR_CMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut18)
{
    U_VPSS_TNR_CMOTIONSTR_LUT4 VPSS_TNR_CMOTIONSTR_LUT4;

    VPSS_TNR_CMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32));
    VPSS_TNR_CMOTIONSTR_LUT4.bits.cmotionstrlut18 = cmotionstrlut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32), VPSS_TNR_CMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut17)
{
    U_VPSS_TNR_CMOTIONSTR_LUT4 VPSS_TNR_CMOTIONSTR_LUT4;

    VPSS_TNR_CMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32));
    VPSS_TNR_CMOTIONSTR_LUT4.bits.cmotionstrlut17 = cmotionstrlut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32), VPSS_TNR_CMOTIONSTR_LUT4.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut16)
{
    U_VPSS_TNR_CMOTIONSTR_LUT4 VPSS_TNR_CMOTIONSTR_LUT4;

    VPSS_TNR_CMOTIONSTR_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32));
    VPSS_TNR_CMOTIONSTR_LUT4.bits.cmotionstrlut16 = cmotionstrlut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT4.u32), VPSS_TNR_CMOTIONSTR_LUT4.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut23)
{
    U_VPSS_TNR_CMOTIONSTR_LUT5 VPSS_TNR_CMOTIONSTR_LUT5;

    VPSS_TNR_CMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32));
    VPSS_TNR_CMOTIONSTR_LUT5.bits.cmotionstrlut23 = cmotionstrlut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32), VPSS_TNR_CMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut22)
{
    U_VPSS_TNR_CMOTIONSTR_LUT5 VPSS_TNR_CMOTIONSTR_LUT5;

    VPSS_TNR_CMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32));
    VPSS_TNR_CMOTIONSTR_LUT5.bits.cmotionstrlut22 = cmotionstrlut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32), VPSS_TNR_CMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut21)
{
    U_VPSS_TNR_CMOTIONSTR_LUT5 VPSS_TNR_CMOTIONSTR_LUT5;

    VPSS_TNR_CMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32));
    VPSS_TNR_CMOTIONSTR_LUT5.bits.cmotionstrlut21 = cmotionstrlut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32), VPSS_TNR_CMOTIONSTR_LUT5.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut20)
{
    U_VPSS_TNR_CMOTIONSTR_LUT5 VPSS_TNR_CMOTIONSTR_LUT5;

    VPSS_TNR_CMOTIONSTR_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32));
    VPSS_TNR_CMOTIONSTR_LUT5.bits.cmotionstrlut20 = cmotionstrlut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT5.u32), VPSS_TNR_CMOTIONSTR_LUT5.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut27)
{
    U_VPSS_TNR_CMOTIONSTR_LUT6 VPSS_TNR_CMOTIONSTR_LUT6;

    VPSS_TNR_CMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32));
    VPSS_TNR_CMOTIONSTR_LUT6.bits.cmotionstrlut27 = cmotionstrlut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32), VPSS_TNR_CMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut26)
{
    U_VPSS_TNR_CMOTIONSTR_LUT6 VPSS_TNR_CMOTIONSTR_LUT6;

    VPSS_TNR_CMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32));
    VPSS_TNR_CMOTIONSTR_LUT6.bits.cmotionstrlut26 = cmotionstrlut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32), VPSS_TNR_CMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut25)
{
    U_VPSS_TNR_CMOTIONSTR_LUT6 VPSS_TNR_CMOTIONSTR_LUT6;

    VPSS_TNR_CMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32));
    VPSS_TNR_CMOTIONSTR_LUT6.bits.cmotionstrlut25 = cmotionstrlut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32), VPSS_TNR_CMOTIONSTR_LUT6.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut24)
{
    U_VPSS_TNR_CMOTIONSTR_LUT6 VPSS_TNR_CMOTIONSTR_LUT6;

    VPSS_TNR_CMOTIONSTR_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32));
    VPSS_TNR_CMOTIONSTR_LUT6.bits.cmotionstrlut24 = cmotionstrlut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT6.u32), VPSS_TNR_CMOTIONSTR_LUT6.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut31)
{
    U_VPSS_TNR_CMOTIONSTR_LUT7 VPSS_TNR_CMOTIONSTR_LUT7;

    VPSS_TNR_CMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32));
    VPSS_TNR_CMOTIONSTR_LUT7.bits.cmotionstrlut31 = cmotionstrlut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32), VPSS_TNR_CMOTIONSTR_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut30)
{
    U_VPSS_TNR_CMOTIONSTR_LUT7 VPSS_TNR_CMOTIONSTR_LUT7;

    VPSS_TNR_CMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32));
    VPSS_TNR_CMOTIONSTR_LUT7.bits.cmotionstrlut30 = cmotionstrlut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32), VPSS_TNR_CMOTIONSTR_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut29)
{
    U_VPSS_TNR_CMOTIONSTR_LUT7 VPSS_TNR_CMOTIONSTR_LUT7;

    VPSS_TNR_CMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32));
    VPSS_TNR_CMOTIONSTR_LUT7.bits.cmotionstrlut29 = cmotionstrlut29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32), VPSS_TNR_CMOTIONSTR_LUT7.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut28)
{
    U_VPSS_TNR_CMOTIONSTR_LUT7 VPSS_TNR_CMOTIONSTR_LUT7;

    VPSS_TNR_CMOTIONSTR_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32));
    VPSS_TNR_CMOTIONSTR_LUT7.bits.cmotionstrlut28 = cmotionstrlut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT7.u32), VPSS_TNR_CMOTIONSTR_LUT7.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut35)
{
    U_VPSS_TNR_CMOTIONSTR_LUT8 VPSS_TNR_CMOTIONSTR_LUT8;

    VPSS_TNR_CMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32));
    VPSS_TNR_CMOTIONSTR_LUT8.bits.cmotionstrlut35 = cmotionstrlut35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32), VPSS_TNR_CMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut34)
{
    U_VPSS_TNR_CMOTIONSTR_LUT8 VPSS_TNR_CMOTIONSTR_LUT8;

    VPSS_TNR_CMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32));
    VPSS_TNR_CMOTIONSTR_LUT8.bits.cmotionstrlut34 = cmotionstrlut34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32), VPSS_TNR_CMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut33)
{
    U_VPSS_TNR_CMOTIONSTR_LUT8 VPSS_TNR_CMOTIONSTR_LUT8;

    VPSS_TNR_CMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32));
    VPSS_TNR_CMOTIONSTR_LUT8.bits.cmotionstrlut33 = cmotionstrlut33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32), VPSS_TNR_CMOTIONSTR_LUT8.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut32)
{
    U_VPSS_TNR_CMOTIONSTR_LUT8 VPSS_TNR_CMOTIONSTR_LUT8;

    VPSS_TNR_CMOTIONSTR_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32));
    VPSS_TNR_CMOTIONSTR_LUT8.bits.cmotionstrlut32 = cmotionstrlut32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT8.u32), VPSS_TNR_CMOTIONSTR_LUT8.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut39)
{
    U_VPSS_TNR_CMOTIONSTR_LUT9 VPSS_TNR_CMOTIONSTR_LUT9;

    VPSS_TNR_CMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32));
    VPSS_TNR_CMOTIONSTR_LUT9.bits.cmotionstrlut39 = cmotionstrlut39;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32), VPSS_TNR_CMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut38)
{
    U_VPSS_TNR_CMOTIONSTR_LUT9 VPSS_TNR_CMOTIONSTR_LUT9;

    VPSS_TNR_CMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32));
    VPSS_TNR_CMOTIONSTR_LUT9.bits.cmotionstrlut38 = cmotionstrlut38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32), VPSS_TNR_CMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut37)
{
    U_VPSS_TNR_CMOTIONSTR_LUT9 VPSS_TNR_CMOTIONSTR_LUT9;

    VPSS_TNR_CMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32));
    VPSS_TNR_CMOTIONSTR_LUT9.bits.cmotionstrlut37 = cmotionstrlut37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32), VPSS_TNR_CMOTIONSTR_LUT9.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut36)
{
    U_VPSS_TNR_CMOTIONSTR_LUT9 VPSS_TNR_CMOTIONSTR_LUT9;

    VPSS_TNR_CMOTIONSTR_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32));
    VPSS_TNR_CMOTIONSTR_LUT9.bits.cmotionstrlut36 = cmotionstrlut36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT9.u32), VPSS_TNR_CMOTIONSTR_LUT9.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut43)
{
    U_VPSS_TNR_CMOTIONSTR_LUT10 VPSS_TNR_CMOTIONSTR_LUT10;

    VPSS_TNR_CMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32));
    VPSS_TNR_CMOTIONSTR_LUT10.bits.cmotionstrlut43 = cmotionstrlut43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32), VPSS_TNR_CMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut42)
{
    U_VPSS_TNR_CMOTIONSTR_LUT10 VPSS_TNR_CMOTIONSTR_LUT10;

    VPSS_TNR_CMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32));
    VPSS_TNR_CMOTIONSTR_LUT10.bits.cmotionstrlut42 = cmotionstrlut42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32), VPSS_TNR_CMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut41)
{
    U_VPSS_TNR_CMOTIONSTR_LUT10 VPSS_TNR_CMOTIONSTR_LUT10;

    VPSS_TNR_CMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32));
    VPSS_TNR_CMOTIONSTR_LUT10.bits.cmotionstrlut41 = cmotionstrlut41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32), VPSS_TNR_CMOTIONSTR_LUT10.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut40)
{
    U_VPSS_TNR_CMOTIONSTR_LUT10 VPSS_TNR_CMOTIONSTR_LUT10;

    VPSS_TNR_CMOTIONSTR_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32));
    VPSS_TNR_CMOTIONSTR_LUT10.bits.cmotionstrlut40 = cmotionstrlut40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT10.u32), VPSS_TNR_CMOTIONSTR_LUT10.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut47)
{
    U_VPSS_TNR_CMOTIONSTR_LUT11 VPSS_TNR_CMOTIONSTR_LUT11;

    VPSS_TNR_CMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32));
    VPSS_TNR_CMOTIONSTR_LUT11.bits.cmotionstrlut47 = cmotionstrlut47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32), VPSS_TNR_CMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut46)
{
    U_VPSS_TNR_CMOTIONSTR_LUT11 VPSS_TNR_CMOTIONSTR_LUT11;

    VPSS_TNR_CMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32));
    VPSS_TNR_CMOTIONSTR_LUT11.bits.cmotionstrlut46 = cmotionstrlut46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32), VPSS_TNR_CMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut45)
{
    U_VPSS_TNR_CMOTIONSTR_LUT11 VPSS_TNR_CMOTIONSTR_LUT11;

    VPSS_TNR_CMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32));
    VPSS_TNR_CMOTIONSTR_LUT11.bits.cmotionstrlut45 = cmotionstrlut45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32), VPSS_TNR_CMOTIONSTR_LUT11.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut44)
{
    U_VPSS_TNR_CMOTIONSTR_LUT11 VPSS_TNR_CMOTIONSTR_LUT11;

    VPSS_TNR_CMOTIONSTR_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32));
    VPSS_TNR_CMOTIONSTR_LUT11.bits.cmotionstrlut44 = cmotionstrlut44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT11.u32), VPSS_TNR_CMOTIONSTR_LUT11.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut51)
{
    U_VPSS_TNR_CMOTIONSTR_LUT12 VPSS_TNR_CMOTIONSTR_LUT12;

    VPSS_TNR_CMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32));
    VPSS_TNR_CMOTIONSTR_LUT12.bits.cmotionstrlut51 = cmotionstrlut51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32), VPSS_TNR_CMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut50)
{
    U_VPSS_TNR_CMOTIONSTR_LUT12 VPSS_TNR_CMOTIONSTR_LUT12;

    VPSS_TNR_CMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32));
    VPSS_TNR_CMOTIONSTR_LUT12.bits.cmotionstrlut50 = cmotionstrlut50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32), VPSS_TNR_CMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut49)
{
    U_VPSS_TNR_CMOTIONSTR_LUT12 VPSS_TNR_CMOTIONSTR_LUT12;

    VPSS_TNR_CMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32));
    VPSS_TNR_CMOTIONSTR_LUT12.bits.cmotionstrlut49 = cmotionstrlut49;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32), VPSS_TNR_CMOTIONSTR_LUT12.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut48)
{
    U_VPSS_TNR_CMOTIONSTR_LUT12 VPSS_TNR_CMOTIONSTR_LUT12;

    VPSS_TNR_CMOTIONSTR_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32));
    VPSS_TNR_CMOTIONSTR_LUT12.bits.cmotionstrlut48 = cmotionstrlut48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT12.u32), VPSS_TNR_CMOTIONSTR_LUT12.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut55)
{
    U_VPSS_TNR_CMOTIONSTR_LUT13 VPSS_TNR_CMOTIONSTR_LUT13;

    VPSS_TNR_CMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32));
    VPSS_TNR_CMOTIONSTR_LUT13.bits.cmotionstrlut55 = cmotionstrlut55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32), VPSS_TNR_CMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut54)
{
    U_VPSS_TNR_CMOTIONSTR_LUT13 VPSS_TNR_CMOTIONSTR_LUT13;

    VPSS_TNR_CMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32));
    VPSS_TNR_CMOTIONSTR_LUT13.bits.cmotionstrlut54 = cmotionstrlut54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32), VPSS_TNR_CMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut53)
{
    U_VPSS_TNR_CMOTIONSTR_LUT13 VPSS_TNR_CMOTIONSTR_LUT13;

    VPSS_TNR_CMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32));
    VPSS_TNR_CMOTIONSTR_LUT13.bits.cmotionstrlut53 = cmotionstrlut53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32), VPSS_TNR_CMOTIONSTR_LUT13.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut52)
{
    U_VPSS_TNR_CMOTIONSTR_LUT13 VPSS_TNR_CMOTIONSTR_LUT13;

    VPSS_TNR_CMOTIONSTR_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32));
    VPSS_TNR_CMOTIONSTR_LUT13.bits.cmotionstrlut52 = cmotionstrlut52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT13.u32), VPSS_TNR_CMOTIONSTR_LUT13.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut59)
{
    U_VPSS_TNR_CMOTIONSTR_LUT14 VPSS_TNR_CMOTIONSTR_LUT14;

    VPSS_TNR_CMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32));
    VPSS_TNR_CMOTIONSTR_LUT14.bits.cmotionstrlut59 = cmotionstrlut59;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32), VPSS_TNR_CMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut58)
{
    U_VPSS_TNR_CMOTIONSTR_LUT14 VPSS_TNR_CMOTIONSTR_LUT14;

    VPSS_TNR_CMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32));
    VPSS_TNR_CMOTIONSTR_LUT14.bits.cmotionstrlut58 = cmotionstrlut58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32), VPSS_TNR_CMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut57)
{
    U_VPSS_TNR_CMOTIONSTR_LUT14 VPSS_TNR_CMOTIONSTR_LUT14;

    VPSS_TNR_CMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32));
    VPSS_TNR_CMOTIONSTR_LUT14.bits.cmotionstrlut57 = cmotionstrlut57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32), VPSS_TNR_CMOTIONSTR_LUT14.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut56)
{
    U_VPSS_TNR_CMOTIONSTR_LUT14 VPSS_TNR_CMOTIONSTR_LUT14;

    VPSS_TNR_CMOTIONSTR_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32));
    VPSS_TNR_CMOTIONSTR_LUT14.bits.cmotionstrlut56 = cmotionstrlut56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT14.u32), VPSS_TNR_CMOTIONSTR_LUT14.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut63)
{
    U_VPSS_TNR_CMOTIONSTR_LUT15 VPSS_TNR_CMOTIONSTR_LUT15;

    VPSS_TNR_CMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32));
    VPSS_TNR_CMOTIONSTR_LUT15.bits.cmotionstrlut63 = cmotionstrlut63;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32), VPSS_TNR_CMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut62)
{
    U_VPSS_TNR_CMOTIONSTR_LUT15 VPSS_TNR_CMOTIONSTR_LUT15;

    VPSS_TNR_CMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32));
    VPSS_TNR_CMOTIONSTR_LUT15.bits.cmotionstrlut62 = cmotionstrlut62;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32), VPSS_TNR_CMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut61)
{
    U_VPSS_TNR_CMOTIONSTR_LUT15 VPSS_TNR_CMOTIONSTR_LUT15;

    VPSS_TNR_CMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32));
    VPSS_TNR_CMOTIONSTR_LUT15.bits.cmotionstrlut61 = cmotionstrlut61;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32), VPSS_TNR_CMOTIONSTR_LUT15.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut60)
{
    U_VPSS_TNR_CMOTIONSTR_LUT15 VPSS_TNR_CMOTIONSTR_LUT15;

    VPSS_TNR_CMOTIONSTR_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32));
    VPSS_TNR_CMOTIONSTR_LUT15.bits.cmotionstrlut60 = cmotionstrlut60;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT15.u32), VPSS_TNR_CMOTIONSTR_LUT15.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut67)
{
    U_VPSS_TNR_CMOTIONSTR_LUT16 VPSS_TNR_CMOTIONSTR_LUT16;

    VPSS_TNR_CMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32));
    VPSS_TNR_CMOTIONSTR_LUT16.bits.cmotionstrlut67 = cmotionstrlut67;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32), VPSS_TNR_CMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut66)
{
    U_VPSS_TNR_CMOTIONSTR_LUT16 VPSS_TNR_CMOTIONSTR_LUT16;

    VPSS_TNR_CMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32));
    VPSS_TNR_CMOTIONSTR_LUT16.bits.cmotionstrlut66 = cmotionstrlut66;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32), VPSS_TNR_CMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut65)
{
    U_VPSS_TNR_CMOTIONSTR_LUT16 VPSS_TNR_CMOTIONSTR_LUT16;

    VPSS_TNR_CMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32));
    VPSS_TNR_CMOTIONSTR_LUT16.bits.cmotionstrlut65 = cmotionstrlut65;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32), VPSS_TNR_CMOTIONSTR_LUT16.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut64)
{
    U_VPSS_TNR_CMOTIONSTR_LUT16 VPSS_TNR_CMOTIONSTR_LUT16;

    VPSS_TNR_CMOTIONSTR_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32));
    VPSS_TNR_CMOTIONSTR_LUT16.bits.cmotionstrlut64 = cmotionstrlut64;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT16.u32), VPSS_TNR_CMOTIONSTR_LUT16.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut71)
{
    U_VPSS_TNR_CMOTIONSTR_LUT17 VPSS_TNR_CMOTIONSTR_LUT17;

    VPSS_TNR_CMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32));
    VPSS_TNR_CMOTIONSTR_LUT17.bits.cmotionstrlut71 = cmotionstrlut71;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32), VPSS_TNR_CMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut70)
{
    U_VPSS_TNR_CMOTIONSTR_LUT17 VPSS_TNR_CMOTIONSTR_LUT17;

    VPSS_TNR_CMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32));
    VPSS_TNR_CMOTIONSTR_LUT17.bits.cmotionstrlut70 = cmotionstrlut70;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32), VPSS_TNR_CMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut69)
{
    U_VPSS_TNR_CMOTIONSTR_LUT17 VPSS_TNR_CMOTIONSTR_LUT17;

    VPSS_TNR_CMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32));
    VPSS_TNR_CMOTIONSTR_LUT17.bits.cmotionstrlut69 = cmotionstrlut69;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32), VPSS_TNR_CMOTIONSTR_LUT17.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut68)
{
    U_VPSS_TNR_CMOTIONSTR_LUT17 VPSS_TNR_CMOTIONSTR_LUT17;

    VPSS_TNR_CMOTIONSTR_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32));
    VPSS_TNR_CMOTIONSTR_LUT17.bits.cmotionstrlut68 = cmotionstrlut68;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT17.u32), VPSS_TNR_CMOTIONSTR_LUT17.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut75)
{
    U_VPSS_TNR_CMOTIONSTR_LUT18 VPSS_TNR_CMOTIONSTR_LUT18;

    VPSS_TNR_CMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32));
    VPSS_TNR_CMOTIONSTR_LUT18.bits.cmotionstrlut75 = cmotionstrlut75;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32), VPSS_TNR_CMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut74)
{
    U_VPSS_TNR_CMOTIONSTR_LUT18 VPSS_TNR_CMOTIONSTR_LUT18;

    VPSS_TNR_CMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32));
    VPSS_TNR_CMOTIONSTR_LUT18.bits.cmotionstrlut74 = cmotionstrlut74;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32), VPSS_TNR_CMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut73)
{
    U_VPSS_TNR_CMOTIONSTR_LUT18 VPSS_TNR_CMOTIONSTR_LUT18;

    VPSS_TNR_CMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32));
    VPSS_TNR_CMOTIONSTR_LUT18.bits.cmotionstrlut73 = cmotionstrlut73;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32), VPSS_TNR_CMOTIONSTR_LUT18.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut72)
{
    U_VPSS_TNR_CMOTIONSTR_LUT18 VPSS_TNR_CMOTIONSTR_LUT18;

    VPSS_TNR_CMOTIONSTR_LUT18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32));
    VPSS_TNR_CMOTIONSTR_LUT18.bits.cmotionstrlut72 = cmotionstrlut72;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT18.u32), VPSS_TNR_CMOTIONSTR_LUT18.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut79)
{
    U_VPSS_TNR_CMOTIONSTR_LUT19 VPSS_TNR_CMOTIONSTR_LUT19;

    VPSS_TNR_CMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32));
    VPSS_TNR_CMOTIONSTR_LUT19.bits.cmotionstrlut79 = cmotionstrlut79;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32), VPSS_TNR_CMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut78)
{
    U_VPSS_TNR_CMOTIONSTR_LUT19 VPSS_TNR_CMOTIONSTR_LUT19;

    VPSS_TNR_CMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32));
    VPSS_TNR_CMOTIONSTR_LUT19.bits.cmotionstrlut78 = cmotionstrlut78;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32), VPSS_TNR_CMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut77)
{
    U_VPSS_TNR_CMOTIONSTR_LUT19 VPSS_TNR_CMOTIONSTR_LUT19;

    VPSS_TNR_CMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32));
    VPSS_TNR_CMOTIONSTR_LUT19.bits.cmotionstrlut77 = cmotionstrlut77;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32), VPSS_TNR_CMOTIONSTR_LUT19.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut76)
{
    U_VPSS_TNR_CMOTIONSTR_LUT19 VPSS_TNR_CMOTIONSTR_LUT19;

    VPSS_TNR_CMOTIONSTR_LUT19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32));
    VPSS_TNR_CMOTIONSTR_LUT19.bits.cmotionstrlut76 = cmotionstrlut76;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT19.u32), VPSS_TNR_CMOTIONSTR_LUT19.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut83)
{
    U_VPSS_TNR_CMOTIONSTR_LUT20 VPSS_TNR_CMOTIONSTR_LUT20;

    VPSS_TNR_CMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32));
    VPSS_TNR_CMOTIONSTR_LUT20.bits.cmotionstrlut83 = cmotionstrlut83;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32), VPSS_TNR_CMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut82)
{
    U_VPSS_TNR_CMOTIONSTR_LUT20 VPSS_TNR_CMOTIONSTR_LUT20;

    VPSS_TNR_CMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32));
    VPSS_TNR_CMOTIONSTR_LUT20.bits.cmotionstrlut82 = cmotionstrlut82;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32), VPSS_TNR_CMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut81)
{
    U_VPSS_TNR_CMOTIONSTR_LUT20 VPSS_TNR_CMOTIONSTR_LUT20;

    VPSS_TNR_CMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32));
    VPSS_TNR_CMOTIONSTR_LUT20.bits.cmotionstrlut81 = cmotionstrlut81;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32), VPSS_TNR_CMOTIONSTR_LUT20.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut80)
{
    U_VPSS_TNR_CMOTIONSTR_LUT20 VPSS_TNR_CMOTIONSTR_LUT20;

    VPSS_TNR_CMOTIONSTR_LUT20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32));
    VPSS_TNR_CMOTIONSTR_LUT20.bits.cmotionstrlut80 = cmotionstrlut80;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT20.u32), VPSS_TNR_CMOTIONSTR_LUT20.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut87)
{
    U_VPSS_TNR_CMOTIONSTR_LUT21 VPSS_TNR_CMOTIONSTR_LUT21;

    VPSS_TNR_CMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32));
    VPSS_TNR_CMOTIONSTR_LUT21.bits.cmotionstrlut87 = cmotionstrlut87;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32), VPSS_TNR_CMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut86)
{
    U_VPSS_TNR_CMOTIONSTR_LUT21 VPSS_TNR_CMOTIONSTR_LUT21;

    VPSS_TNR_CMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32));
    VPSS_TNR_CMOTIONSTR_LUT21.bits.cmotionstrlut86 = cmotionstrlut86;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32), VPSS_TNR_CMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut85)
{
    U_VPSS_TNR_CMOTIONSTR_LUT21 VPSS_TNR_CMOTIONSTR_LUT21;

    VPSS_TNR_CMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32));
    VPSS_TNR_CMOTIONSTR_LUT21.bits.cmotionstrlut85 = cmotionstrlut85;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32), VPSS_TNR_CMOTIONSTR_LUT21.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut84)
{
    U_VPSS_TNR_CMOTIONSTR_LUT21 VPSS_TNR_CMOTIONSTR_LUT21;

    VPSS_TNR_CMOTIONSTR_LUT21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32));
    VPSS_TNR_CMOTIONSTR_LUT21.bits.cmotionstrlut84 = cmotionstrlut84;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT21.u32), VPSS_TNR_CMOTIONSTR_LUT21.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut91)
{
    U_VPSS_TNR_CMOTIONSTR_LUT22 VPSS_TNR_CMOTIONSTR_LUT22;

    VPSS_TNR_CMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32));
    VPSS_TNR_CMOTIONSTR_LUT22.bits.cmotionstrlut91 = cmotionstrlut91;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32), VPSS_TNR_CMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut90)
{
    U_VPSS_TNR_CMOTIONSTR_LUT22 VPSS_TNR_CMOTIONSTR_LUT22;

    VPSS_TNR_CMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32));
    VPSS_TNR_CMOTIONSTR_LUT22.bits.cmotionstrlut90 = cmotionstrlut90;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32), VPSS_TNR_CMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut89)
{
    U_VPSS_TNR_CMOTIONSTR_LUT22 VPSS_TNR_CMOTIONSTR_LUT22;

    VPSS_TNR_CMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32));
    VPSS_TNR_CMOTIONSTR_LUT22.bits.cmotionstrlut89 = cmotionstrlut89;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32), VPSS_TNR_CMOTIONSTR_LUT22.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut88)
{
    U_VPSS_TNR_CMOTIONSTR_LUT22 VPSS_TNR_CMOTIONSTR_LUT22;

    VPSS_TNR_CMOTIONSTR_LUT22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32));
    VPSS_TNR_CMOTIONSTR_LUT22.bits.cmotionstrlut88 = cmotionstrlut88;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT22.u32), VPSS_TNR_CMOTIONSTR_LUT22.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut95)
{
    U_VPSS_TNR_CMOTIONSTR_LUT23 VPSS_TNR_CMOTIONSTR_LUT23;

    VPSS_TNR_CMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32));
    VPSS_TNR_CMOTIONSTR_LUT23.bits.cmotionstrlut95 = cmotionstrlut95;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32), VPSS_TNR_CMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut94)
{
    U_VPSS_TNR_CMOTIONSTR_LUT23 VPSS_TNR_CMOTIONSTR_LUT23;

    VPSS_TNR_CMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32));
    VPSS_TNR_CMOTIONSTR_LUT23.bits.cmotionstrlut94 = cmotionstrlut94;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32), VPSS_TNR_CMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut93)
{
    U_VPSS_TNR_CMOTIONSTR_LUT23 VPSS_TNR_CMOTIONSTR_LUT23;

    VPSS_TNR_CMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32));
    VPSS_TNR_CMOTIONSTR_LUT23.bits.cmotionstrlut93 = cmotionstrlut93;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32), VPSS_TNR_CMOTIONSTR_LUT23.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut92)
{
    U_VPSS_TNR_CMOTIONSTR_LUT23 VPSS_TNR_CMOTIONSTR_LUT23;

    VPSS_TNR_CMOTIONSTR_LUT23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32));
    VPSS_TNR_CMOTIONSTR_LUT23.bits.cmotionstrlut92 = cmotionstrlut92;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT23.u32), VPSS_TNR_CMOTIONSTR_LUT23.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut99)
{
    U_VPSS_TNR_CMOTIONSTR_LUT24 VPSS_TNR_CMOTIONSTR_LUT24;

    VPSS_TNR_CMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32));
    VPSS_TNR_CMOTIONSTR_LUT24.bits.cmotionstrlut99 = cmotionstrlut99;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32), VPSS_TNR_CMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut98)
{
    U_VPSS_TNR_CMOTIONSTR_LUT24 VPSS_TNR_CMOTIONSTR_LUT24;

    VPSS_TNR_CMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32));
    VPSS_TNR_CMOTIONSTR_LUT24.bits.cmotionstrlut98 = cmotionstrlut98;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32), VPSS_TNR_CMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut97)
{
    U_VPSS_TNR_CMOTIONSTR_LUT24 VPSS_TNR_CMOTIONSTR_LUT24;

    VPSS_TNR_CMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32));
    VPSS_TNR_CMOTIONSTR_LUT24.bits.cmotionstrlut97 = cmotionstrlut97;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32), VPSS_TNR_CMOTIONSTR_LUT24.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut96)
{
    U_VPSS_TNR_CMOTIONSTR_LUT24 VPSS_TNR_CMOTIONSTR_LUT24;

    VPSS_TNR_CMOTIONSTR_LUT24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32));
    VPSS_TNR_CMOTIONSTR_LUT24.bits.cmotionstrlut96 = cmotionstrlut96;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT24.u32), VPSS_TNR_CMOTIONSTR_LUT24.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut103(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut103)
{
    U_VPSS_TNR_CMOTIONSTR_LUT25 VPSS_TNR_CMOTIONSTR_LUT25;

    VPSS_TNR_CMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32));
    VPSS_TNR_CMOTIONSTR_LUT25.bits.cmotionstrlut103 = cmotionstrlut103;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32), VPSS_TNR_CMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut102(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut102)
{
    U_VPSS_TNR_CMOTIONSTR_LUT25 VPSS_TNR_CMOTIONSTR_LUT25;

    VPSS_TNR_CMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32));
    VPSS_TNR_CMOTIONSTR_LUT25.bits.cmotionstrlut102 = cmotionstrlut102;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32), VPSS_TNR_CMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut101(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut101)
{
    U_VPSS_TNR_CMOTIONSTR_LUT25 VPSS_TNR_CMOTIONSTR_LUT25;

    VPSS_TNR_CMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32));
    VPSS_TNR_CMOTIONSTR_LUT25.bits.cmotionstrlut101 = cmotionstrlut101;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32), VPSS_TNR_CMOTIONSTR_LUT25.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut100(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut100)
{
    U_VPSS_TNR_CMOTIONSTR_LUT25 VPSS_TNR_CMOTIONSTR_LUT25;

    VPSS_TNR_CMOTIONSTR_LUT25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32));
    VPSS_TNR_CMOTIONSTR_LUT25.bits.cmotionstrlut100 = cmotionstrlut100;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT25.u32), VPSS_TNR_CMOTIONSTR_LUT25.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut107(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut107)
{
    U_VPSS_TNR_CMOTIONSTR_LUT26 VPSS_TNR_CMOTIONSTR_LUT26;

    VPSS_TNR_CMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32));
    VPSS_TNR_CMOTIONSTR_LUT26.bits.cmotionstrlut107 = cmotionstrlut107;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32), VPSS_TNR_CMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut106(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut106)
{
    U_VPSS_TNR_CMOTIONSTR_LUT26 VPSS_TNR_CMOTIONSTR_LUT26;

    VPSS_TNR_CMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32));
    VPSS_TNR_CMOTIONSTR_LUT26.bits.cmotionstrlut106 = cmotionstrlut106;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32), VPSS_TNR_CMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut105(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut105)
{
    U_VPSS_TNR_CMOTIONSTR_LUT26 VPSS_TNR_CMOTIONSTR_LUT26;

    VPSS_TNR_CMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32));
    VPSS_TNR_CMOTIONSTR_LUT26.bits.cmotionstrlut105 = cmotionstrlut105;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32), VPSS_TNR_CMOTIONSTR_LUT26.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut104(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut104)
{
    U_VPSS_TNR_CMOTIONSTR_LUT26 VPSS_TNR_CMOTIONSTR_LUT26;

    VPSS_TNR_CMOTIONSTR_LUT26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32));
    VPSS_TNR_CMOTIONSTR_LUT26.bits.cmotionstrlut104 = cmotionstrlut104;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT26.u32), VPSS_TNR_CMOTIONSTR_LUT26.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut111(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut111)
{
    U_VPSS_TNR_CMOTIONSTR_LUT27 VPSS_TNR_CMOTIONSTR_LUT27;

    VPSS_TNR_CMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32));
    VPSS_TNR_CMOTIONSTR_LUT27.bits.cmotionstrlut111 = cmotionstrlut111;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32), VPSS_TNR_CMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut110(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut110)
{
    U_VPSS_TNR_CMOTIONSTR_LUT27 VPSS_TNR_CMOTIONSTR_LUT27;

    VPSS_TNR_CMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32));
    VPSS_TNR_CMOTIONSTR_LUT27.bits.cmotionstrlut110 = cmotionstrlut110;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32), VPSS_TNR_CMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut109(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut109)
{
    U_VPSS_TNR_CMOTIONSTR_LUT27 VPSS_TNR_CMOTIONSTR_LUT27;

    VPSS_TNR_CMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32));
    VPSS_TNR_CMOTIONSTR_LUT27.bits.cmotionstrlut109 = cmotionstrlut109;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32), VPSS_TNR_CMOTIONSTR_LUT27.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut108(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut108)
{
    U_VPSS_TNR_CMOTIONSTR_LUT27 VPSS_TNR_CMOTIONSTR_LUT27;

    VPSS_TNR_CMOTIONSTR_LUT27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32));
    VPSS_TNR_CMOTIONSTR_LUT27.bits.cmotionstrlut108 = cmotionstrlut108;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT27.u32), VPSS_TNR_CMOTIONSTR_LUT27.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut115(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut115)
{
    U_VPSS_TNR_CMOTIONSTR_LUT28 VPSS_TNR_CMOTIONSTR_LUT28;

    VPSS_TNR_CMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32));
    VPSS_TNR_CMOTIONSTR_LUT28.bits.cmotionstrlut115 = cmotionstrlut115;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32), VPSS_TNR_CMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut114(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut114)
{
    U_VPSS_TNR_CMOTIONSTR_LUT28 VPSS_TNR_CMOTIONSTR_LUT28;

    VPSS_TNR_CMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32));
    VPSS_TNR_CMOTIONSTR_LUT28.bits.cmotionstrlut114 = cmotionstrlut114;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32), VPSS_TNR_CMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut113(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut113)
{
    U_VPSS_TNR_CMOTIONSTR_LUT28 VPSS_TNR_CMOTIONSTR_LUT28;

    VPSS_TNR_CMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32));
    VPSS_TNR_CMOTIONSTR_LUT28.bits.cmotionstrlut113 = cmotionstrlut113;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32), VPSS_TNR_CMOTIONSTR_LUT28.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut112(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut112)
{
    U_VPSS_TNR_CMOTIONSTR_LUT28 VPSS_TNR_CMOTIONSTR_LUT28;

    VPSS_TNR_CMOTIONSTR_LUT28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32));
    VPSS_TNR_CMOTIONSTR_LUT28.bits.cmotionstrlut112 = cmotionstrlut112;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT28.u32), VPSS_TNR_CMOTIONSTR_LUT28.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut119(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut119)
{
    U_VPSS_TNR_CMOTIONSTR_LUT29 VPSS_TNR_CMOTIONSTR_LUT29;

    VPSS_TNR_CMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32));
    VPSS_TNR_CMOTIONSTR_LUT29.bits.cmotionstrlut119 = cmotionstrlut119;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32), VPSS_TNR_CMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut118(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut118)
{
    U_VPSS_TNR_CMOTIONSTR_LUT29 VPSS_TNR_CMOTIONSTR_LUT29;

    VPSS_TNR_CMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32));
    VPSS_TNR_CMOTIONSTR_LUT29.bits.cmotionstrlut118 = cmotionstrlut118;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32), VPSS_TNR_CMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut117(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut117)
{
    U_VPSS_TNR_CMOTIONSTR_LUT29 VPSS_TNR_CMOTIONSTR_LUT29;

    VPSS_TNR_CMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32));
    VPSS_TNR_CMOTIONSTR_LUT29.bits.cmotionstrlut117 = cmotionstrlut117;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32), VPSS_TNR_CMOTIONSTR_LUT29.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut116(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut116)
{
    U_VPSS_TNR_CMOTIONSTR_LUT29 VPSS_TNR_CMOTIONSTR_LUT29;

    VPSS_TNR_CMOTIONSTR_LUT29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32));
    VPSS_TNR_CMOTIONSTR_LUT29.bits.cmotionstrlut116 = cmotionstrlut116;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT29.u32), VPSS_TNR_CMOTIONSTR_LUT29.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut123(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut123)
{
    U_VPSS_TNR_CMOTIONSTR_LUT30 VPSS_TNR_CMOTIONSTR_LUT30;

    VPSS_TNR_CMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32));
    VPSS_TNR_CMOTIONSTR_LUT30.bits.cmotionstrlut123 = cmotionstrlut123;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32), VPSS_TNR_CMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut122(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut122)
{
    U_VPSS_TNR_CMOTIONSTR_LUT30 VPSS_TNR_CMOTIONSTR_LUT30;

    VPSS_TNR_CMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32));
    VPSS_TNR_CMOTIONSTR_LUT30.bits.cmotionstrlut122 = cmotionstrlut122;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32), VPSS_TNR_CMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut121(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut121)
{
    U_VPSS_TNR_CMOTIONSTR_LUT30 VPSS_TNR_CMOTIONSTR_LUT30;

    VPSS_TNR_CMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32));
    VPSS_TNR_CMOTIONSTR_LUT30.bits.cmotionstrlut121 = cmotionstrlut121;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32), VPSS_TNR_CMOTIONSTR_LUT30.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut120(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut120)
{
    U_VPSS_TNR_CMOTIONSTR_LUT30 VPSS_TNR_CMOTIONSTR_LUT30;

    VPSS_TNR_CMOTIONSTR_LUT30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32));
    VPSS_TNR_CMOTIONSTR_LUT30.bits.cmotionstrlut120 = cmotionstrlut120;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT30.u32), VPSS_TNR_CMOTIONSTR_LUT30.u32);

    return ;
}



HI_VOID VPSS_Tnr_SetCmotionstrlut127(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut127)
{
    U_VPSS_TNR_CMOTIONSTR_LUT31 VPSS_TNR_CMOTIONSTR_LUT31;

    VPSS_TNR_CMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32));
    VPSS_TNR_CMOTIONSTR_LUT31.bits.cmotionstrlut127 = cmotionstrlut127;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32), VPSS_TNR_CMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut126(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut126)
{
    U_VPSS_TNR_CMOTIONSTR_LUT31 VPSS_TNR_CMOTIONSTR_LUT31;

    VPSS_TNR_CMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32));
    VPSS_TNR_CMOTIONSTR_LUT31.bits.cmotionstrlut126 = cmotionstrlut126;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32), VPSS_TNR_CMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut125(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut125)
{
    U_VPSS_TNR_CMOTIONSTR_LUT31 VPSS_TNR_CMOTIONSTR_LUT31;

    VPSS_TNR_CMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32));
    VPSS_TNR_CMOTIONSTR_LUT31.bits.cmotionstrlut125 = cmotionstrlut125;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32), VPSS_TNR_CMOTIONSTR_LUT31.u32);

    return ;
}


HI_VOID VPSS_Tnr_SetCmotionstrlut124(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32  cmotionstrlut124)
{
    U_VPSS_TNR_CMOTIONSTR_LUT31 VPSS_TNR_CMOTIONSTR_LUT31;

    VPSS_TNR_CMOTIONSTR_LUT31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32));
    VPSS_TNR_CMOTIONSTR_LUT31.bits.cmotionstrlut124 = cmotionstrlut124;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_TNR_CMOTIONSTR_LUT31.u32), VPSS_TNR_CMOTIONSTR_LUT31.u32);

    return ;
}
#endif
