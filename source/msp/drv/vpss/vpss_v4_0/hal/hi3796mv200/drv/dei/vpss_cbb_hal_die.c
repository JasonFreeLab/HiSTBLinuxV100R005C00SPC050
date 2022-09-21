
//vpss_hal_ip_die.cpp begin

#include "vpss_cbb_common.h"
//#include "vpss_reg.h"


HI_VOID VPSS_Die_SetDieOutSelL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 die_out_sel_l)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.die_out_sel_l = die_out_sel_l;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetDieOutSelC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 die_out_sel_c)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.die_out_sel_c = die_out_sel_c;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetDieLMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 die_l_mode)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.die_l_mode = die_l_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);


    return ;
}


HI_VOID VPSS_Die_SetDieCMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 die_c_mode)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.die_c_mode = die_c_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetTwoFourPxlShare(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 two_four_pxl_share)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.two_four_pxl_share = two_four_pxl_share;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcOnly(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_only)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.mc_only = mc_only;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetMaOnly(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ma_only)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.ma_only = ma_only;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeSmoothEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_smooth_en)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.edge_smooth_en = edge_smooth_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetMchdirL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mchdir_l)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.mchdir_l = mchdir_l;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetMchdirC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mchdir_c)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.mchdir_c = mchdir_c;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetDieRst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 die_rst)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.die_rst = die_rst;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetStinfoStop(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stinfo_stop)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.stinfo_stop = stinfo_stop;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeSmoothRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_smooth_ratio)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECTRL.u32));
    VPSS_DIECTRL.bits.edge_smooth_ratio = edge_smooth_ratio;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECTRL.u32), VPSS_DIECTRL.u32);

    return ;
}



HI_VOID VPSS_Die_SetChromaMfOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chroma_mf_offset)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.chroma_mf_offset = chroma_mf_offset;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetDeiStRstValue(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dei_st_rst_value)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.dei_st_rst_value = dei_st_rst_value;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecModeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rec_mode_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.rec_mode_en = rec_mode_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetChromaMfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chroma_mf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.chroma_mf_max = chroma_mf_max;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetLumaMfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 luma_mf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.luma_mf_max = luma_mf_max;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.motion_iir_en = motion_iir_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetLumaScesdfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 luma_scesdf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.luma_scesdf_max = luma_scesdf_max;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.frame_motion_smooth_en = frame_motion_smooth_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecmodeFrmfldBlendMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 recmode_frmfld_blend_mode)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIELMA2.u32));
    VPSS_DIELMA2.bits.recmode_frmfld_blend_mode = recmode_frmfld_blend_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIELMA2.u32), VPSS_DIELMA2.u32);

    return ;
}



HI_VOID VPSS_Die_SetMinNorthStrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 min_north_strength)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTEN.u32));
    VPSS_DIEINTEN.bits.min_north_strength = min_north_strength;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTEN.u32), VPSS_DIEINTEN.u32);

    return ;
}


HI_VOID VPSS_Die_SetDirRatioNorth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_ratio_north)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTEN.u32));
    VPSS_DIEINTEN.bits.dir_ratio_north = dir_ratio_north;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTEN.u32), VPSS_DIEINTEN.u32);

    return ;
}



HI_VOID VPSS_Die_SetRangeScale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 range_scale)
{
    U_VPSS_DIESCALE VPSS_DIESCALE;

    VPSS_DIESCALE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIESCALE.u32));
    VPSS_DIESCALE.bits.range_scale = range_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIESCALE.u32), VPSS_DIESCALE.u32);

    return ;
}



HI_VOID VPSS_Die_SetBc1Gain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc1_gain)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK1.u32));
    VPSS_DIECHECK1.bits.bc1_gain = bc1_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK1.u32), VPSS_DIECHECK1.u32);

    return ;
}


HI_VOID VPSS_Die_SetBc1AutodzGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc1_autodz_gain)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK1.u32));
    VPSS_DIECHECK1.bits.bc1_autodz_gain = bc1_autodz_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK1.u32), VPSS_DIECHECK1.u32);

    return ;
}


HI_VOID VPSS_Die_SetBc1MaxDz(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc1_max_dz)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK1.u32));
    VPSS_DIECHECK1.bits.bc1_max_dz = bc1_max_dz;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK1.u32), VPSS_DIECHECK1.u32);

    return ;
}



HI_VOID VPSS_Die_SetBc2Gain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc2_gain)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK2.u32));
    VPSS_DIECHECK2.bits.bc2_gain = bc2_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK2.u32), VPSS_DIECHECK2.u32);

    return ;
}


HI_VOID VPSS_Die_SetBc2AutodzGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc2_autodz_gain)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK2.u32));
    VPSS_DIECHECK2.bits.bc2_autodz_gain = bc2_autodz_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK2.u32), VPSS_DIECHECK2.u32);

    return ;
}


HI_VOID VPSS_Die_SetBc2MaxDz(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc2_max_dz)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECHECK2.u32));
    VPSS_DIECHECK2.bits.bc2_max_dz = bc2_max_dz;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECHECK2.u32), VPSS_DIECHECK2.u32);

    return ;
}



HI_VOID VPSS_Die_SetDir3Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir3_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR0_3.u32));
    VPSS_DIEDIR0_3.bits.dir3_scale = dir3_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR0_3.u32), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir2Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir2_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR0_3.u32));
    VPSS_DIEDIR0_3.bits.dir2_scale = dir2_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR0_3.u32), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir1Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir1_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR0_3.u32));
    VPSS_DIEDIR0_3.bits.dir1_scale = dir1_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR0_3.u32), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir0Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir0_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR0_3.u32));
    VPSS_DIEDIR0_3.bits.dir0_scale = dir0_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR0_3.u32), VPSS_DIEDIR0_3.u32);

    return ;
}



HI_VOID VPSS_Die_SetDir7Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir7_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR4_7.u32));
    VPSS_DIEDIR4_7.bits.dir7_scale = dir7_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR4_7.u32), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir6Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir6_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR4_7.u32));
    VPSS_DIEDIR4_7.bits.dir6_scale = dir6_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR4_7.u32), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir5Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir5_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR4_7.u32));
    VPSS_DIEDIR4_7.bits.dir5_scale = dir5_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR4_7.u32), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir4Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir4_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR4_7.u32));
    VPSS_DIEDIR4_7.bits.dir4_scale = dir4_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR4_7.u32), VPSS_DIEDIR4_7.u32);

    return ;
}



HI_VOID VPSS_Die_SetDir11Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir11_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR8_11.u32));
    VPSS_DIEDIR8_11.bits.dir11_scale = dir11_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR8_11.u32), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir10Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir10_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR8_11.u32));
    VPSS_DIEDIR8_11.bits.dir10_scale = dir10_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR8_11.u32), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir9Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir9_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR8_11.u32));
    VPSS_DIEDIR8_11.bits.dir9_scale = dir9_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR8_11.u32), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir8Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir8_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR8_11.u32));
    VPSS_DIEDIR8_11.bits.dir8_scale = dir8_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR8_11.u32), VPSS_DIEDIR8_11.u32);

    return ;
}



HI_VOID VPSS_Die_SetDir14Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir14_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR12_14.u32));
    VPSS_DIEDIR12_14.bits.dir14_scale = dir14_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR12_14.u32), VPSS_DIEDIR12_14.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir13Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir13_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR12_14.u32));
    VPSS_DIEDIR12_14.bits.dir13_scale = dir13_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR12_14.u32), VPSS_DIEDIR12_14.u32);

    return ;
}


HI_VOID VPSS_Die_SetDir12Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir12_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIR12_14.u32));
    VPSS_DIEDIR12_14.bits.dir12_scale = dir12_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIR12_14.u32), VPSS_DIEDIR12_14.u32);

    return ;
}



HI_VOID VPSS_Die_SetCHeightCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 c_height_cnt)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIESTA.u32));
    VPSS_DIESTA.bits.c_height_cnt = c_height_cnt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIESTA.u32), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Die_SetLHeightCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 l_height_cnt)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIESTA.u32));
    VPSS_DIESTA.bits.l_height_cnt = l_height_cnt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIESTA.u32), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Die_SetCurCstate(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_cstate)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIESTA.u32));
    VPSS_DIESTA.bits.cur_cstate = cur_cstate;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIESTA.u32), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Die_SetCurState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_state)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIESTA.u32));
    VPSS_DIESTA.bits.cur_state = cur_state;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIESTA.u32), VPSS_DIESTA.u32);

    return ;
}



HI_VOID VPSS_Die_SetIntpScaleRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_8)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_8 = intp_scale_ratio_8;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_7)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_7 = intp_scale_ratio_7;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_6)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_6 = intp_scale_ratio_6;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_5)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_5 = intp_scale_ratio_5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_4)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_4 = intp_scale_ratio_4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_3)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_3 = intp_scale_ratio_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_2)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_2 = intp_scale_ratio_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_1)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_1 = intp_scale_ratio_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL0.u32), VPSS_DIEINTPSCL0.u32);

    return ;
}



HI_VOID VPSS_Die_SetIntpScaleRatio15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_15)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_15 = intp_scale_ratio_15;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_14)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_14 = intp_scale_ratio_14;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_13)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_13 = intp_scale_ratio_13;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_12)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_12 = intp_scale_ratio_12;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_11)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_11 = intp_scale_ratio_11;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_10)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_10 = intp_scale_ratio_10;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Die_SetIntpScaleRatio9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 intp_scale_ratio_9)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_9 = intp_scale_ratio_9;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEINTPSCL1.u32), VPSS_DIEINTPSCL1.u32);

    return ;
}



HI_VOID VPSS_Die_SetStrengthThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 strength_thd)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIRTHD.u32));
    VPSS_DIEDIRTHD.bits.strength_thd = strength_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIRTHD.u32), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetHorEdgeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 hor_edge_en)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIRTHD.u32));
    VPSS_DIEDIRTHD.bits.hor_edge_en = hor_edge_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIRTHD.u32), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_mode)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIRTHD.u32));
    VPSS_DIEDIRTHD.bits.edge_mode = edge_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIRTHD.u32), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetDirThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_thd)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIRTHD.u32));
    VPSS_DIEDIRTHD.bits.dir_thd = dir_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIRTHD.u32), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetBcGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bc_gain)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEDIRTHD.u32));
    VPSS_DIEDIRTHD.bits.bc_gain = bc_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEDIRTHD.u32), VPSS_DIEDIRTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetFldMotionCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_coring)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEJITMTN.u32));
    VPSS_DIEJITMTN.bits.fld_motion_coring = fld_motion_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEJITMTN.u32), VPSS_DIEJITMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetJitterCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 jitter_coring)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEJITMTN.u32));
    VPSS_DIEJITMTN.bits.jitter_coring = jitter_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEJITMTN.u32), VPSS_DIEJITMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetJitterGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 jitter_gain)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEJITMTN.u32));
    VPSS_DIEJITMTN.bits.jitter_gain = jitter_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEJITMTN.u32), VPSS_DIEJITMTN.u32);

    return ;
}



HI_VOID VPSS_Die_SetLongMotionShf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 long_motion_shf)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.long_motion_shf = long_motion_shf;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetFldMotionWndMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_wnd_mode)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.fld_motion_wnd_mode = fld_motion_wnd_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetFldMotionGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_gain)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.fld_motion_gain = fld_motion_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetFldMotionCurveSlope(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_curve_slope)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.fld_motion_curve_slope = fld_motion_curve_slope;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetFldMotionThdHigh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_thd_high)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.fld_motion_thd_high = fld_motion_thd_high;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Die_SetFldMotionThdLow(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fld_motion_thd_low)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFLDMTN.u32));
    VPSS_DIEFLDMTN.bits.fld_motion_thd_low = fld_motion_thd_low;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFLDMTN.u32), VPSS_DIEFLDMTN.u32);

    return ;
}



HI_VOID VPSS_Die_SetMotionDiffThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_3)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_3 = motion_diff_thd_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionDiffThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_2)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_2 = motion_diff_thd_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionDiffThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_1)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_1 = motion_diff_thd_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionDiffThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_0)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_0 = motion_diff_thd_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}



HI_VOID VPSS_Die_SetMaxMotionIirRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 max_motion_iir_ratio)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32));
    VPSS_DIEMTNDIFFTHD1.bits.max_motion_iir_ratio = max_motion_iir_ratio;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMinMotionIirRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 min_motion_iir_ratio)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32));
    VPSS_DIEMTNDIFFTHD1.bits.min_motion_iir_ratio = min_motion_iir_ratio;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionDiffThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_5)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32));
    VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_5 = motion_diff_thd_5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionDiffThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_diff_thd_4)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32));
    VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_4 = motion_diff_thd_4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetMotionIirCurveRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_ratio_0)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_ratio_0 = motion_iir_curve_ratio_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_slope_3)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_3 = motion_iir_curve_slope_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_slope_2)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_2 = motion_iir_curve_slope_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_slope_1)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_1 = motion_iir_curve_slope_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_slope_0)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_0 = motion_iir_curve_slope_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32), VPSS_DIEMTNIIRSLP.u32);

    return ;
}



HI_VOID VPSS_Die_SetMotionIirCurveRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_ratio_4)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_4 = motion_iir_curve_ratio_4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_ratio_3)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_3 = motion_iir_curve_ratio_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_ratio_2)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_2 = motion_iir_curve_ratio_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionIirCurveRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_iir_curve_ratio_1)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_1 = motion_iir_curve_ratio_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32), VPSS_DIEMTNIIRRAT.u32);

    return ;
}



HI_VOID VPSS_Die_SetHisMotionInfoWriteMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 his_motion_info_write_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.his_motion_info_write_mode = his_motion_info_write_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetHisMotionWriteMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 his_motion_write_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.his_motion_write_mode = his_motion_write_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetHisMotionUsingMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 his_motion_using_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.his_motion_using_mode = his_motion_using_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetHisMotionEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 his_motion_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.his_motion_en = his_motion_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetPreInfoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pre_info_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.pre_info_en = pre_info_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetPpreInfoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ppre_info_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.ppre_info_en = ppre_info_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecModeFrmMotionStep1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rec_mode_frm_motion_step_1)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.rec_mode_frm_motion_step_1 = rec_mode_frm_motion_step_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecModeFrmMotionStep0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rec_mode_frm_motion_step_0)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.rec_mode_frm_motion_step_0 = rec_mode_frm_motion_step_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecModeFldMotionStep1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rec_mode_fld_motion_step_1)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.rec_mode_fld_motion_step_1 = rec_mode_fld_motion_step_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Die_SetRecModeFldMotionStep0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rec_mode_fld_motion_step_0)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEHISMODE.u32));
    VPSS_DIEHISMODE.bits.rec_mode_fld_motion_step_0 = rec_mode_fld_motion_step_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEHISMODE.u32), VPSS_DIEHISMODE.u32);

    return ;
}



HI_VOID VPSS_Die_SetMedBlendEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 med_blend_en)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMORFLT.u32));
    VPSS_DIEMORFLT.bits.med_blend_en = med_blend_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMORFLT.u32), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMorFltEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mor_flt_en)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMORFLT.u32));
    VPSS_DIEMORFLT.bits.mor_flt_en = mor_flt_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMORFLT.u32), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMorFltSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mor_flt_size)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMORFLT.u32));
    VPSS_DIEMORFLT.bits.mor_flt_size = mor_flt_size;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMORFLT.u32), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Die_SetMorFltThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mor_flt_thd)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMORFLT.u32));
    VPSS_DIEMORFLT.bits.mor_flt_thd = mor_flt_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMORFLT.u32), VPSS_DIEMORFLT.u32);

    return ;
}



HI_VOID VPSS_Die_SetCombChkUpperLimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_upper_limit)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32));
    VPSS_DIECOMBCHK0.bits.comb_chk_upper_limit = comb_chk_upper_limit;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCombChkLowerLimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_lower_limit)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32));
    VPSS_DIECOMBCHK0.bits.comb_chk_lower_limit = comb_chk_lower_limit;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCombChkMinVthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_min_vthd)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32));
    VPSS_DIECOMBCHK0.bits.comb_chk_min_vthd = comb_chk_min_vthd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCombChkMinHthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_min_hthd)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32));
    VPSS_DIECOMBCHK0.bits.comb_chk_min_hthd = comb_chk_min_hthd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK0.u32), VPSS_DIECOMBCHK0.u32);

    return ;
}



HI_VOID VPSS_Die_SetCombChkEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_en)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32));
    VPSS_DIECOMBCHK1.bits.comb_chk_en = comb_chk_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32), VPSS_DIECOMBCHK1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCombChkMdThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_md_thd)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32));
    VPSS_DIECOMBCHK1.bits.comb_chk_md_thd = comb_chk_md_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32), VPSS_DIECOMBCHK1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCombChkEdgeThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 comb_chk_edge_thd)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32));
    VPSS_DIECOMBCHK1.bits.comb_chk_edge_thd = comb_chk_edge_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIECOMBCHK1.u32), VPSS_DIECOMBCHK1.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameMotionSmoothThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd3)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd3 = frame_motion_smooth_thd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd2)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd2 = frame_motion_smooth_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd1)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd1 = frame_motion_smooth_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd0)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd0 = frame_motion_smooth_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameMotionSmoothRatioMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio_max)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_max = frame_motion_smooth_ratio_max;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothRatioMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio_min)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_min = frame_motion_smooth_ratio_min;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd5)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd5 = frame_motion_smooth_thd5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_thd4)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd4 = frame_motion_smooth_thd4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameMotionSmoothRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio0)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_ratio0 = frame_motion_smooth_ratio0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_slope3)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope3 = frame_motion_smooth_slope3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_slope2)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope2 = frame_motion_smooth_slope2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_slope1)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope1 = frame_motion_smooth_slope1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_slope0)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope0 = frame_motion_smooth_slope0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameMotionSmoothRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio4)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio4 = frame_motion_smooth_ratio4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio3)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio3 = frame_motion_smooth_ratio3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio2)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio2 = frame_motion_smooth_ratio2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMotionSmoothRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_motion_smooth_ratio1)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio1 = frame_motion_smooth_ratio1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameFieldBlendThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd3)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd3 = frame_field_blend_thd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd2)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd2 = frame_field_blend_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd1)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd1 = frame_field_blend_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd0)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd0 = frame_field_blend_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameFieldBlendRatioMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio_max)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_max = frame_field_blend_ratio_max;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendRatioMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio_min)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_min = frame_field_blend_ratio_min;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd5)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd5 = frame_field_blend_thd5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_thd4)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd4 = frame_field_blend_thd4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameFieldBlendRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio0)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_ratio0 = frame_field_blend_ratio0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_slope3)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope3 = frame_field_blend_slope3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_slope2)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope2 = frame_field_blend_slope2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_slope1)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope1 = frame_field_blend_slope1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_slope0)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope0 = frame_field_blend_slope0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}



HI_VOID VPSS_Die_SetFrameFieldBlendRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio4)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio4 = frame_field_blend_ratio4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio3)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio3 = frame_field_blend_ratio3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio2)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio2 = frame_field_blend_ratio2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameFieldBlendRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_field_blend_ratio1)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio1 = frame_field_blend_ratio1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}



HI_VOID VPSS_Die_SetMotionAdjustGainChr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_adjust_gain_chr)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNADJ.u32));
    VPSS_DIEMTNADJ.bits.motion_adjust_gain_chr = motion_adjust_gain_chr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNADJ.u32), VPSS_DIEMTNADJ.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionAdjustCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_adjust_coring)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNADJ.u32));
    VPSS_DIEMTNADJ.bits.motion_adjust_coring = motion_adjust_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNADJ.u32), VPSS_DIEMTNADJ.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionAdjustGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_adjust_gain)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMTNADJ.u32));
    VPSS_DIEMTNADJ.bits.motion_adjust_gain = motion_adjust_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMTNADJ.u32), VPSS_DIEMTNADJ.u32);

    return ;
}



HI_VOID VPSS_Die_SetEdgeNorm1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_1)
{
    U_VPSS_DIEEDGENORM0 VPSS_DIEEDGENORM0;

    VPSS_DIEEDGENORM0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM0.u32));
    VPSS_DIEEDGENORM0.bits.edge_norm_1 = edge_norm_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM0.u32), VPSS_DIEEDGENORM0.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_0)
{
    U_VPSS_DIEEDGENORM0 VPSS_DIEEDGENORM0;

    VPSS_DIEEDGENORM0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM0.u32));
    VPSS_DIEEDGENORM0.bits.edge_norm_0 = edge_norm_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM0.u32), VPSS_DIEEDGENORM0.u32);

    return ;
}



HI_VOID VPSS_Die_SetEdgeNorm3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_3)
{
    U_VPSS_DIEEDGENORM1 VPSS_DIEEDGENORM1;

    VPSS_DIEEDGENORM1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM1.u32));
    VPSS_DIEEDGENORM1.bits.edge_norm_3 = edge_norm_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM1.u32), VPSS_DIEEDGENORM1.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_2)
{
    U_VPSS_DIEEDGENORM1 VPSS_DIEEDGENORM1;

    VPSS_DIEEDGENORM1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM1.u32));
    VPSS_DIEEDGENORM1.bits.edge_norm_2 = edge_norm_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM1.u32), VPSS_DIEEDGENORM1.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcStrengthK3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_k3)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32));
    VPSS_DIEEDGENORM2.bits.mc_strength_k3 = mc_strength_k3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32), VPSS_DIEEDGENORM2.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_5)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32));
    VPSS_DIEEDGENORM2.bits.edge_norm_5 = edge_norm_5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32), VPSS_DIEEDGENORM2.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_4)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32));
    VPSS_DIEEDGENORM2.bits.edge_norm_4 = edge_norm_4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM2.u32), VPSS_DIEEDGENORM2.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcStrengthG3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_g3)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32));
    VPSS_DIEEDGENORM3.bits.mc_strength_g3 = mc_strength_g3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32), VPSS_DIEEDGENORM3.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_7)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32));
    VPSS_DIEEDGENORM3.bits.edge_norm_7 = edge_norm_7;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32), VPSS_DIEEDGENORM3.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_6)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32));
    VPSS_DIEEDGENORM3.bits.edge_norm_6 = edge_norm_6;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM3.u32), VPSS_DIEEDGENORM3.u32);

    return ;
}



HI_VOID VPSS_Die_SetInterDiffThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 inter_diff_thd0)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32));
    VPSS_DIEEDGENORM4.bits.inter_diff_thd0 = inter_diff_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32), VPSS_DIEEDGENORM4.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_9)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32));
    VPSS_DIEEDGENORM4.bits.edge_norm_9 = edge_norm_9;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32), VPSS_DIEEDGENORM4.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_8)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32));
    VPSS_DIEEDGENORM4.bits.edge_norm_8 = edge_norm_8;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM4.u32), VPSS_DIEEDGENORM4.u32);

    return ;
}



HI_VOID VPSS_Die_SetInterDiffThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 inter_diff_thd1)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32));
    VPSS_DIEEDGENORM5.bits.inter_diff_thd1 = inter_diff_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32), VPSS_DIEEDGENORM5.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_11)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32));
    VPSS_DIEEDGENORM5.bits.edge_norm_11 = edge_norm_11;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32), VPSS_DIEEDGENORM5.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeNorm10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_norm_10)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32));
    VPSS_DIEEDGENORM5.bits.edge_norm_10 = edge_norm_10;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGENORM5.u32), VPSS_DIEEDGENORM5.u32);

    return ;
}



HI_VOID VPSS_Die_SetInterDiffThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 inter_diff_thd2)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32));
    VPSS_DIEEDGEFORMC.bits.inter_diff_thd2 = inter_diff_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32), VPSS_DIEEDGEFORMC.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeScale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_scale)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32));
    VPSS_DIEEDGEFORMC.bits.edge_scale = edge_scale;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32), VPSS_DIEEDGEFORMC.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_coring)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32));
    VPSS_DIEEDGEFORMC.bits.edge_coring = edge_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32), VPSS_DIEEDGEFORMC.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcStrengthG0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_g0)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_g0 = mc_strength_g0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthK2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_k2)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k2 = mc_strength_k2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthK1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_k1)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k1 = mc_strength_k1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthK0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_k0)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k0 = mc_strength_k0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcStrengthMaxg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_maxg)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_maxg = mc_strength_maxg;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthMing(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_ming)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_ming = mc_strength_ming;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthG2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_g2)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_g2 = mc_strength_g2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcStrengthG1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_strength_g1)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_g1 = mc_strength_g1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKCMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_c_mcbld)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION0.u32));
    VPSS_DIEFUSION0.bits.k_c_mcbld = k_c_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION0.u32), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKCMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_c_mcw)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION0.u32));
    VPSS_DIEFUSION0.bits.k_c_mcw = k_c_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION0.u32), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKYMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_y_mcbld)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION0.u32));
    VPSS_DIEFUSION0.bits.k_y_mcbld = k_y_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION0.u32), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKYMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_y_mcw)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION0.u32));
    VPSS_DIEFUSION0.bits.k_y_mcw = k_y_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION0.u32), VPSS_DIEFUSION0.u32);

    return ;
}



HI_VOID VPSS_Die_SetG0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION1.u32));
    VPSS_DIEFUSION1.bits.g0_mcw_adj = g0_mcw_adj;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION1.u32), VPSS_DIEFUSION1.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION1.u32));
    VPSS_DIEFUSION1.bits.k0_mcw_adj = k0_mcw_adj;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION1.u32), VPSS_DIEFUSION1.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION1.u32));
    VPSS_DIEFUSION1.bits.x0_mcw_adj = x0_mcw_adj;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION1.u32), VPSS_DIEFUSION1.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION2.u32));
    VPSS_DIEFUSION2.bits.k1_mcbld = k1_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION2.u32), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION2.u32));
    VPSS_DIEFUSION2.bits.k0_mcbld = k0_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION2.u32), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION2.u32));
    VPSS_DIEFUSION2.bits.x0_mcbld = x0_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION2.u32), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mcw_adj)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION2.u32));
    VPSS_DIEFUSION2.bits.k1_mcw_adj = k1_mcw_adj;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION2.u32), VPSS_DIEFUSION2.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcLaiBldmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_lai_bldmode)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION3.u32));
    VPSS_DIEFUSION3.bits.mc_lai_bldmode = mc_lai_bldmode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION3.u32), VPSS_DIEFUSION3.u32);

    return ;
}


HI_VOID VPSS_Die_SetKCurwMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_curw_mcbld)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION3.u32));
    VPSS_DIEFUSION3.bits.k_curw_mcbld = k_curw_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION3.u32), VPSS_DIEFUSION3.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mcbld)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEFUSION3.u32));
    VPSS_DIEFUSION3.bits.g0_mcbld = g0_mcbld;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEFUSION3.u32), VPSS_DIEFUSION3.u32);

    return ;
}



HI_VOID VPSS_Die_SetMaGbmThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ma_gbm_thd0)
{
    U_VPSS_DIEMAGBMTHD0 VPSS_DIEMAGBMTHD0;

    VPSS_DIEMAGBMTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32));
    VPSS_DIEMAGBMTHD0.bits.ma_gbm_thd0 = ma_gbm_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32), VPSS_DIEMAGBMTHD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMaGbmThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ma_gbm_thd1)
{
    U_VPSS_DIEMAGBMTHD0 VPSS_DIEMAGBMTHD0;

    VPSS_DIEMAGBMTHD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32));
    VPSS_DIEMAGBMTHD0.bits.ma_gbm_thd1 = ma_gbm_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32), VPSS_DIEMAGBMTHD0.u32);

    return ;
}



HI_VOID VPSS_Die_SetMaGbmThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ma_gbm_thd2)
{
    U_VPSS_DIEMAGBMTHD1 VPSS_DIEMAGBMTHD1;

    VPSS_DIEMAGBMTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32));
    VPSS_DIEMAGBMTHD1.bits.ma_gbm_thd2 = ma_gbm_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32), VPSS_DIEMAGBMTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMaGbmThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ma_gbm_thd3)
{
    U_VPSS_DIEMAGBMTHD1 VPSS_DIEMAGBMTHD1;

    VPSS_DIEMAGBMTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32));
    VPSS_DIEMAGBMTHD1.bits.ma_gbm_thd3 = ma_gbm_thd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32), VPSS_DIEMAGBMTHD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetMtfiltenGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mtfilten_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32));
    VPSS_DIEMCGBMCOEF0.bits.mtfilten_gmd = mtfilten_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMtth3Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mtth3_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32));
    VPSS_DIEMCGBMCOEF0.bits.mtth3_gmd = mtth3_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMtth2Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mtth2_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32));
    VPSS_DIEMCGBMCOEF0.bits.mtth2_gmd = mtth2_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMtth1Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mtth1_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32));
    VPSS_DIEMCGBMCOEF0.bits.mtth1_gmd = mtth1_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMtth0Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mtth0_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32));
    VPSS_DIEMCGBMCOEF0.bits.mtth0_gmd = mtth0_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}



HI_VOID VPSS_Die_SetKMagGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mag_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32));
    VPSS_DIEMCGBMCOEF1.bits.k_mag_gmd = k_mag_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKDifhGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_difh_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32));
    VPSS_DIEMCGBMCOEF1.bits.k_difh_gmd = k_difh_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMaxmagGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_maxmag_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32));
    VPSS_DIEMCGBMCOEF1.bits.k_maxmag_gmd = k_maxmag_gmd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKhoredge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 khoredge)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG1.u32));
    VPSS_DIEKMAG1.bits.khoredge = khoredge;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG1.u32), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKmagv2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmagv_2)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG1.u32));
    VPSS_DIEKMAG1.bits.kmagv_2 = kmagv_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG1.u32), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKmagv1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmagv_1)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG1.u32));
    VPSS_DIEKMAG1.bits.kmagv_1 = kmagv_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG1.u32), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKmagh2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmagh_2)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG1.u32));
    VPSS_DIEKMAG1.bits.kmagh_2 = kmagh_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG1.u32), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKmagh1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmagh_1)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG1.u32));
    VPSS_DIEKMAG1.bits.kmagh_1 = kmagh_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG1.u32), VPSS_DIEKMAG1.u32);

    return ;
}



HI_VOID VPSS_Die_SetScalerFramemotion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scaler_framemotion)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG2.u32));
    VPSS_DIEKMAG2.bits.scaler_framemotion = scaler_framemotion;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG2.u32), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionLimt2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_limt_2)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG2.u32));
    VPSS_DIEKMAG2.bits.motion_limt_2 = motion_limt_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG2.u32), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Die_SetMotionLimt1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_limt_1)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG2.u32));
    VPSS_DIEKMAG2.bits.motion_limt_1 = motion_limt_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG2.u32), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Die_SetFrameMagEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 frame_mag_en)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG2.u32));
    VPSS_DIEKMAG2.bits.frame_mag_en = frame_mag_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG2.u32), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Die_SetScalerHoredge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scaler_horedge)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIEKMAG2.u32));
    VPSS_DIEKMAG2.bits.scaler_horedge = scaler_horedge;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIEKMAG2.u32), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Die_SetEdgeStrCoringC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge_str_coring_c)
{
    U_VPSS_DIE_S3ADD VPSS_DIE_S3ADD;

    VPSS_DIE_S3ADD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIE_S3ADD.u32));
    VPSS_DIE_S3ADD.bits.edge_str_coring_c = edge_str_coring_c;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIE_S3ADD.u32), VPSS_DIE_S3ADD.u32);

    return ;
}


HI_VOID VPSS_Die_SetDirRatioC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_ratio_c)
{
    U_VPSS_DIE_S3ADD VPSS_DIE_S3ADD;

    VPSS_DIE_S3ADD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_DIE_S3ADD.u32));
    VPSS_DIE_S3ADD.bits.dir_ratio_c = dir_ratio_c;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_DIE_S3ADD.u32), VPSS_DIE_S3ADD.u32);

    return ;
}


HI_VOID VPSS_Die_SetHistThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 hist_thd3)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32));
    VPSS_PDPHISTTHD1.bits.hist_thd3 = hist_thd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetHistThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 hist_thd2)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32));
    VPSS_PDPHISTTHD1.bits.hist_thd2 = hist_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetHistThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 hist_thd1)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32));
    VPSS_PDPHISTTHD1.bits.hist_thd1 = hist_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetHistThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 hist_thd0)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32));
    VPSS_PDPHISTTHD1.bits.hist_thd0 = hist_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPHISTTHD1.u32), VPSS_PDPHISTTHD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetMovCoringNorm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mov_coring_norm)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCMOV.u32));
    VPSS_PDPCCMOV.bits.mov_coring_norm = mov_coring_norm;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCMOV.u32), VPSS_PDPCCMOV.u32);

    return ;
}


HI_VOID VPSS_Die_SetMovCoringTkr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mov_coring_tkr)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCMOV.u32));
    VPSS_PDPCCMOV.bits.mov_coring_tkr = mov_coring_tkr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCMOV.u32), VPSS_PDPCCMOV.u32);

    return ;
}


HI_VOID VPSS_Die_SetMovCoringBlk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mov_coring_blk)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCMOV.u32));
    VPSS_PDPCCMOV.bits.mov_coring_blk = mov_coring_blk;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCMOV.u32), VPSS_PDPCCMOV.u32);

    return ;
}



HI_VOID VPSS_Die_SetLasiMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_mode)
{
    U_VPSS_PDCTRL VPSS_PDCTRL;

    VPSS_PDCTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDCTRL.u32));
    VPSS_PDCTRL.bits.lasi_mode = lasi_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDCTRL.u32), VPSS_PDCTRL.u32);

    return ;
}


HI_VOID VPSS_Die_SetBitsmov2r(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bitsmov2r)
{
    U_VPSS_PDCTRL VPSS_PDCTRL;

    VPSS_PDCTRL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDCTRL.u32));
    VPSS_PDCTRL.bits.bitsmov2r = bitsmov2r;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDCTRL.u32), VPSS_PDCTRL.u32);

    return ;
}



HI_VOID VPSS_Die_SetDiffMovblkThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 diff_movblk_thd)
{
    U_VPSS_PDBLKTHD VPSS_PDBLKTHD;

    VPSS_PDBLKTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDBLKTHD.u32));
    VPSS_PDBLKTHD.bits.diff_movblk_thd = diff_movblk_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDBLKTHD.u32), VPSS_PDBLKTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetUmThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 um_thd2)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDUMTHD.u32));
    VPSS_PDUMTHD.bits.um_thd2 = um_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDUMTHD.u32), VPSS_PDUMTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetUmThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 um_thd1)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDUMTHD.u32));
    VPSS_PDUMTHD.bits.um_thd1 = um_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDUMTHD.u32), VPSS_PDUMTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetUmThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 um_thd0)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDUMTHD.u32));
    VPSS_PDUMTHD.bits.um_thd0 = um_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDUMTHD.u32), VPSS_PDUMTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetCoringBlk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 coring_blk)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCCORING.u32));
    VPSS_PDPCCCORING.bits.coring_blk = coring_blk;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCCORING.u32), VPSS_PDPCCCORING.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoringNorm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 coring_norm)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCCORING.u32));
    VPSS_PDPCCCORING.bits.coring_norm = coring_norm;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCCORING.u32), VPSS_PDPCCCORING.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoringTkr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 coring_tkr)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCCORING.u32));
    VPSS_PDPCCCORING.bits.coring_tkr = coring_tkr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCCORING.u32), VPSS_PDPCCCORING.u32);

    return ;
}



HI_VOID VPSS_Die_SetPccHthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pcc_hthd)
{
    U_VPSS_PDPCCHTHD VPSS_PDPCCHTHD;

    VPSS_PDPCCHTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCHTHD.u32));
    VPSS_PDPCCHTHD.bits.pcc_hthd = pcc_hthd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCHTHD.u32), VPSS_PDPCCHTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetPccVthd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pcc_vthd3)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCVTHD.u32));
    VPSS_PDPCCVTHD.bits.pcc_vthd3 = pcc_vthd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCVTHD.u32), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetPccVthd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pcc_vthd2)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCVTHD.u32));
    VPSS_PDPCCVTHD.bits.pcc_vthd2 = pcc_vthd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCVTHD.u32), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetPccVthd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pcc_vthd1)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCVTHD.u32));
    VPSS_PDPCCVTHD.bits.pcc_vthd1 = pcc_vthd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCVTHD.u32), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetPccVthd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pcc_vthd0)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDPCCVTHD.u32));
    VPSS_PDPCCVTHD.bits.pcc_vthd0 = pcc_vthd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDPCCVTHD.u32), VPSS_PDPCCVTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetItdiffVthd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 itdiff_vthd3)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd3 = itdiff_vthd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetItdiffVthd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 itdiff_vthd2)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd2 = itdiff_vthd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetItdiffVthd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 itdiff_vthd1)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd1 = itdiff_vthd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetItdiffVthd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 itdiff_vthd0)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd0 = itdiff_vthd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32), VPSS_PDITDIFFVTHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetLasiMovThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_mov_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASITHD.u32));
    VPSS_PDLASITHD.bits.lasi_mov_thd = lasi_mov_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASITHD.u32), VPSS_PDLASITHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiEdgeThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_edge_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASITHD.u32));
    VPSS_PDLASITHD.bits.lasi_edge_thd = lasi_edge_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASITHD.u32), VPSS_PDLASITHD.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiCoringThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_coring_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASITHD.u32));
    VPSS_PDLASITHD.bits.lasi_coring_thd = lasi_coring_thd;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASITHD.u32), VPSS_PDLASITHD.u32);

    return ;
}



HI_VOID VPSS_Die_SetLasiTxtCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_coring)
{
    U_VPSS_PDLASIMODE0COEF VPSS_PDLASIMODE0COEF;

    VPSS_PDLASIMODE0COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32));
    VPSS_PDLASIMODE0COEF.bits.lasi_txt_coring = lasi_txt_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32), VPSS_PDLASIMODE0COEF.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiTxtAlpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_alpha)
{
    U_VPSS_PDLASIMODE0COEF VPSS_PDLASIMODE0COEF;

    VPSS_PDLASIMODE0COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32));
    VPSS_PDLASIMODE0COEF.bits.lasi_txt_alpha = lasi_txt_alpha;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32), VPSS_PDLASIMODE0COEF.u32);

    return ;
}



HI_VOID VPSS_Die_SetLasiTxtThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_thd3)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd3 = lasi_txt_thd3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiTxtThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_thd2)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd2 = lasi_txt_thd2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiTxtThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_thd1)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd1 = lasi_txt_thd1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Die_SetLasiTxtThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lasi_txt_thd0)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd0 = lasi_txt_thd0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32), VPSS_PDLASIMODE1COEF.u32);

    return ;
}



HI_VOID VPSS_Die_SetRegion1YStt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 region1_y_stt)
{
    U_VPSS_PDREGION VPSS_PDREGION;

    VPSS_PDREGION.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDREGION.u32));
    VPSS_PDREGION.bits.region1_y_stt = region1_y_stt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDREGION.u32), VPSS_PDREGION.u32);

    return ;
}


HI_VOID VPSS_Die_SetRegion1YEnd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 region1_y_end)
{
    U_VPSS_PDREGION VPSS_PDREGION;

    VPSS_PDREGION.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_PDREGION.u32));
    VPSS_PDREGION.bits.region1_y_end = region1_y_end;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_PDREGION.u32), VPSS_PDREGION.u32);

    return ;
}



HI_VOID VPSS_Die_SetKRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rgdifycore)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32));
    VPSS_MCDI_RGDIFY.bits.k_rgdifycore = k_rgdifycore;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Die_SetGRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_rgdifycore)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32));
    VPSS_MCDI_RGDIFY.bits.g_rgdifycore = g_rgdifycore;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rgdify)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32));
    VPSS_MCDI_RGDIFY.bits.core_rgdify = core_rgdify;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Die_SetLmtRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lmt_rgdify)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32));
    VPSS_MCDI_RGDIFY.bits.lmt_rgdify = lmt_rgdify;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32), VPSS_MCDI_RGDIFY.u32);

    return ;
}



HI_VOID VPSS_Die_SetCoefSadlpf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 coef_sadlpf)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32));
    VPSS_MCDI_RGSAD.bits.coef_sadlpf = coef_sadlpf;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Die_SetKmvRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmv_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32));
    VPSS_MCDI_RGSAD.bits.kmv_rgsad = kmv_rgsad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Die_SetKTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_tpdif_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32));
    VPSS_MCDI_RGSAD.bits.k_tpdif_rgsad = k_tpdif_rgsad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Die_SetGTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_tpdif_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32));
    VPSS_MCDI_RGSAD.bits.g_tpdif_rgsad = g_tpdif_rgsad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGSAD.u32), VPSS_MCDI_RGSAD.u32);

    return ;
}



HI_VOID VPSS_Die_SetThmagRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thmag_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMV.u32));
    VPSS_MCDI_RGMV.bits.thmag_rgmv = thmag_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMV.u32), VPSS_MCDI_RGMV.u32);

    return ;
}


HI_VOID VPSS_Die_SetThSaddifRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_saddif_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMV.u32));
    VPSS_MCDI_RGMV.bits.th_saddif_rgmv = th_saddif_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMV.u32), VPSS_MCDI_RGMV.u32);

    return ;
}


HI_VOID VPSS_Die_SetTh0mvsadRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_0mvsad_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMV.u32));
    VPSS_MCDI_RGMV.bits.th_0mvsad_rgmv = th_0mvsad_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMV.u32), VPSS_MCDI_RGMV.u32);

    return ;
}



HI_VOID VPSS_Die_SetCoreMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mag_rg)
{
    U_VPSS_MCDI_RGMAG0 VPSS_MCDI_RGMAG0;

    VPSS_MCDI_RGMAG0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32));
    VPSS_MCDI_RGMAG0.bits.core_mag_rg = core_mag_rg;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32), VPSS_MCDI_RGMAG0.u32);

    return ;
}


HI_VOID VPSS_Die_SetLmtMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lmt_mag_rg)
{
    U_VPSS_MCDI_RGMAG0 VPSS_MCDI_RGMAG0;

    VPSS_MCDI_RGMAG0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32));
    VPSS_MCDI_RGMAG0.bits.lmt_mag_rg = lmt_mag_rg;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32), VPSS_MCDI_RGMAG0.u32);

    return ;
}



HI_VOID VPSS_Die_SetCoreMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mv_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.core_mv_rgmvls = core_mv_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mv_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.k_mv_rgmvls = k_mv_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mag_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.core_mag_rgmvls = core_mag_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mag_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.k_mag_rgmvls = k_mag_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetThMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_mvadj_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.th_mvadj_rgmvls = th_mvadj_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Die_SetEnMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 en_mvadj_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32));
    VPSS_MCDI_RGMAG1.bits.en_mvadj_rgmvls = en_mvadj_rgmvls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32), VPSS_MCDI_RGMAG1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_sad_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGLS.u32));
    VPSS_MCDI_RGLS.bits.k_sad_rgls = k_sad_rgls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGLS.u32), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Die_SetThMagRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_mag_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGLS.u32));
    VPSS_MCDI_RGLS.bits.th_mag_rgls = th_mag_rgls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGLS.u32), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Die_SetThSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_sad_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGLS.u32));
    VPSS_MCDI_RGLS.bits.th_sad_rgls = th_sad_rgls;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGLS.u32), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Die_SetKSadcoreRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_sadcore_rgmv)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGLS.u32));
    VPSS_MCDI_RGLS.bits.k_sadcore_rgmv = k_sadcore_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGLS.u32), VPSS_MCDI_RGLS.u32);

    return ;
}



HI_VOID VPSS_Die_SetForceMven(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 force_mven)
{
    U_VPSS_MCDI_SEL VPSS_MCDI_SEL;

    VPSS_MCDI_SEL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_SEL.u32));
    VPSS_MCDI_SEL.bits.force_mven = force_mven;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_SEL.u32), VPSS_MCDI_SEL.u32);

    return ;
}


HI_VOID VPSS_Die_SetForceMvx(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 force_mvx)
{
    U_VPSS_MCDI_SEL VPSS_MCDI_SEL;

    VPSS_MCDI_SEL.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_SEL.u32));
    VPSS_MCDI_SEL.bits.force_mvx = force_mvx;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_SEL.u32), VPSS_MCDI_SEL.u32);

    return ;
}



HI_VOID VPSS_Die_SetThBlkmvxMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_blkmvx_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT0.u32));
    VPSS_MCDI_DLT0.bits.th_blkmvx_mvdlt = th_blkmvx_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT0.u32), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetThRgmvxMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_rgmvx_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT0.u32));
    VPSS_MCDI_DLT0.bits.th_rgmvx_mvdlt = th_rgmvx_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT0.u32), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetThLsMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_ls_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT0.u32));
    VPSS_MCDI_DLT0.bits.th_ls_mvdlt = th_ls_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT0.u32), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetThVblkdistMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_vblkdist_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT0.u32));
    VPSS_MCDI_DLT0.bits.th_vblkdist_mvdlt = th_vblkdist_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT0.u32), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetThHblkdistMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_hblkdist_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT0.u32));
    VPSS_MCDI_DLT0.bits.th_hblkdist_mvdlt = th_hblkdist_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT0.u32), VPSS_MCDI_DLT0.u32);

    return ;
}



HI_VOID VPSS_Die_SetKSadcoreMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_sadcore_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT1.u32));
    VPSS_MCDI_DLT1.bits.k_sadcore_mvdlt = k_sadcore_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT1.u32), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetThMagMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_mag_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT1.u32));
    VPSS_MCDI_DLT1.bits.th_mag_mvdlt = th_mag_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT1.u32), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetGMagMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_mag_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT1.u32));
    VPSS_MCDI_DLT1.bits.g_mag_mvdlt = g_mag_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT1.u32), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetThlSadMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thl_sad_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT1.u32));
    VPSS_MCDI_DLT1.bits.thl_sad_mvdlt = thl_sad_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT1.u32), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetThhSadMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thh_sad_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DLT1.u32));
    VPSS_MCDI_DLT1.bits.thh_sad_mvdlt = thh_sad_mvdlt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DLT1.u32), VPSS_MCDI_DLT1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKRglsw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rglsw)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32));
    VPSS_MCDI_RGMCW0.bits.k_rglsw = k_rglsw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKSimimvw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_simimvw)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32));
    VPSS_MCDI_RGMCW0.bits.k_simimvw = k_simimvw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGhCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gh_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32));
    VPSS_MCDI_RGMCW0.bits.gh_core_simimv = gh_core_simimv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGlCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gl_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32));
    VPSS_MCDI_RGMCW0.bits.gl_core_simimv = gl_core_simimv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32));
    VPSS_MCDI_RGMCW0.bits.k_core_simimv = k_core_simimv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32), VPSS_MCDI_RGMCW0.u32);

    return ;
}



HI_VOID VPSS_Die_SetKCoreVsaddif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_core_vsaddif)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.k_core_vsaddif = k_core_vsaddif;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKRgsadadjMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rgsadadj_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.k_rgsadadj_mcw = k_rgsadadj_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreRgsadadjMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rgsadadj_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.core_rgsadadj_mcw = core_rgsadadj_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMvyMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mvy_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.k_mvy_mcw = k_mvy_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreMvyMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mvy_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.core_mvy_mcw = core_mvy_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetRgtbEnMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgtb_en_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32));
    VPSS_MCDI_RGMCW1.bits.rgtb_en_mcw = rgtb_en_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32), VPSS_MCDI_RGMCW1.u32);

    return ;
}



HI_VOID VPSS_Die_SetCoreRgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32));
    VPSS_MCDI_RGMCW2.bits.core_rgmag_mcw = core_rgmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetModeRgysadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mode_rgysad_mcw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32));
    VPSS_MCDI_RGMCW2.bits.mode_rgysad_mcw = mode_rgysad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetKVsaddifw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_vsaddifw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32));
    VPSS_MCDI_RGMCW2.bits.k_vsaddifw = k_vsaddifw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetGhCoreVsadDif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gh_core_vsad_dif)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32));
    VPSS_MCDI_RGMCW2.bits.gh_core_vsad_dif = gh_core_vsad_dif;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetGlCoreVsaddif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gl_core_vsaddif)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32));
    VPSS_MCDI_RGMCW2.bits.gl_core_vsaddif = gl_core_vsaddif;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32), VPSS_MCDI_RGMCW2.u32);

    return ;
}



HI_VOID VPSS_Die_SetG0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32));
    VPSS_MCDI_RGMCW3.bits.g0_rgmag_mcw = g0_rgmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32), VPSS_MCDI_RGMCW3.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32));
    VPSS_MCDI_RGMCW3.bits.k0_rgmag_mcw = k0_rgmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32), VPSS_MCDI_RGMCW3.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32));
    VPSS_MCDI_RGMCW3.bits.x0_rgmag_mcw = x0_rgmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32), VPSS_MCDI_RGMCW3.u32);

    return ;
}



HI_VOID VPSS_Die_SetX0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32));
    VPSS_MCDI_RGMCW4.bits.x0_rgsad_mcw = x0_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32), VPSS_MCDI_RGMCW4.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32));
    VPSS_MCDI_RGMCW4.bits.core_rgsad_mcw = core_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32), VPSS_MCDI_RGMCW4.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32));
    VPSS_MCDI_RGMCW4.bits.k1_rgmag_mcw = k1_rgmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32), VPSS_MCDI_RGMCW4.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32));
    VPSS_MCDI_RGMCW5.bits.k1_rgsad_mcw = k1_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32), VPSS_MCDI_RGMCW5.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32));
    VPSS_MCDI_RGMCW5.bits.g0_rgsad_mcw = g0_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32), VPSS_MCDI_RGMCW5.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32));
    VPSS_MCDI_RGMCW5.bits.k0_rgsad_mcw = k0_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32), VPSS_MCDI_RGMCW5.u32);

    return ;
}



HI_VOID VPSS_Die_SetKRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32));
    VPSS_MCDI_RGMCW6.bits.k_rgsad_mcw = k_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Die_SetXRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32));
    VPSS_MCDI_RGMCW6.bits.x_rgsad_mcw = x_rgsad_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0SmrgMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_smrg_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32));
    VPSS_MCDI_RGMCW6.bits.k0_smrg_mcw = k0_smrg_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0SmrgMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_smrg_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32));
    VPSS_MCDI_RGMCW6.bits.x0_smrg_mcw = x0_smrg_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32), VPSS_MCDI_RGMCW6.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32));
    VPSS_MCDI_TPMCW0.bits.k1_tpmvdist_mcw = k1_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32));
    VPSS_MCDI_TPMCW0.bits.g0_tpmvdist_mcw = g0_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32));
    VPSS_MCDI_TPMCW0.bits.k0_tpmvdist_mcw = k0_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32));
    VPSS_MCDI_TPMCW0.bits.x0_tpmvdist_mcw = x0_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32), VPSS_MCDI_TPMCW0.u32);

    return ;
}



HI_VOID VPSS_Die_SetKCoreTpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_core_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32));
    VPSS_MCDI_TPMCW1.bits.k_core_tpmvdist_mcw = k_core_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetBCoreTpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_core_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32));
    VPSS_MCDI_TPMCW1.bits.b_core_tpmvdist_mcw = b_core_tpmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKAvgmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_avgmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32));
    VPSS_MCDI_TPMCW1.bits.k_avgmvdist_mcw = k_avgmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMinmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_minmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32));
    VPSS_MCDI_TPMCW1.bits.k_minmvdist_mcw = k_minmvdist_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32), VPSS_MCDI_TPMCW1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKTbdifMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_tbdif_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k_tbdif_mcw = k_tbdif_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0MaxMagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_max_mag_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k0_max_mag_mcw = k0_max_mag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1MaxMagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_max_mag_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k1_max_mag_mcw = k1_max_mag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMaxDifMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_max_dif_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k_max_dif_mcw = k_max_dif_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMaxCoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_max_core_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k_max_core_mcw = k_max_core_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKDifvcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_difvcore_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k_difvcore_mcw = k_difvcore_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKDifhcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_difhcore_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32));
    VPSS_MCDI_WNDMCW0.bits.k_difhcore_mcw = k_difhcore_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32), VPSS_MCDI_WNDMCW0.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32));
    VPSS_MCDI_WNDMCW1.bits.k1_mag_wnd_mcw = k1_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32));
    VPSS_MCDI_WNDMCW1.bits.g0_mag_wnd_mcw = g0_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32));
    VPSS_MCDI_WNDMCW1.bits.k0_mag_wnd_mcw = k0_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32));
    VPSS_MCDI_WNDMCW1.bits.x0_mag_wnd_mcw = x0_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKTbmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_tbmag_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32));
    VPSS_MCDI_WNDMCW1.bits.k_tbmag_mcw = k_tbmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32), VPSS_MCDI_WNDMCW1.u32);

    return ;
}



HI_VOID VPSS_Die_SetG0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32));
    VPSS_MCDI_WNDMCW2.bits.g0_sad_wnd_mcw = g0_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32));
    VPSS_MCDI_WNDMCW2.bits.k0_sad_wnd_mcw = k0_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32));
    VPSS_MCDI_WNDMCW2.bits.x0_sad_wnd_mcw = x0_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Die_SetG1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g1_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32));
    VPSS_MCDI_WNDMCW2.bits.g1_mag_wnd_mcw = g1_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32), VPSS_MCDI_WNDMCW2.u32);

    return ;
}



HI_VOID VPSS_Die_SetG1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g1_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW3 VPSS_MCDI_WNDMCW3;

    VPSS_MCDI_WNDMCW3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32));
    VPSS_MCDI_WNDMCW3.bits.g1_sad_wnd_mcw = g1_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32), VPSS_MCDI_WNDMCW3.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW3 VPSS_MCDI_WNDMCW3;

    VPSS_MCDI_WNDMCW3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32));
    VPSS_MCDI_WNDMCW3.bits.k1_sad_wnd_mcw = k1_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32), VPSS_MCDI_WNDMCW3.u32);

    return ;
}



HI_VOID VPSS_Die_SetBHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.b_hvdif_dw = b_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetBBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.b_bhvdif_dw = b_bhvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.k_bhvdif_dw = k_bhvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.core_bhvdif_dw = core_bhvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGainLpfDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gain_lpf_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.gain_lpf_dw = gain_lpf_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMaxHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_max_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32));
    VPSS_MCDI_VERTWEIGHT0.bits.k_max_hvdif_dw = k_max_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}



HI_VOID VPSS_Die_SetBMvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32));
    VPSS_MCDI_VERTWEIGHT1.bits.b_mv_dw = b_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreMvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32));
    VPSS_MCDI_VERTWEIGHT1.bits.core_mv_dw = core_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKDifvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_difv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32));
    VPSS_MCDI_VERTWEIGHT1.bits.k_difv_dw = k_difv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32));
    VPSS_MCDI_VERTWEIGHT1.bits.core_hvdif_dw = core_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32));
    VPSS_MCDI_VERTWEIGHT2.bits.k1_hvdif_dw = k1_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32));
    VPSS_MCDI_VERTWEIGHT2.bits.g0_hvdif_dw = g0_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32));
    VPSS_MCDI_VERTWEIGHT2.bits.k0_hvdif_dw = k0_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32));
    VPSS_MCDI_VERTWEIGHT2.bits.x0_hvdif_dw = x0_hvdif_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32));
    VPSS_MCDI_VERTWEIGHT3.bits.k1_mv_dw = k1_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32));
    VPSS_MCDI_VERTWEIGHT3.bits.g0_mv_dw = g0_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32));
    VPSS_MCDI_VERTWEIGHT3.bits.k0_mv_dw = k0_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32));
    VPSS_MCDI_VERTWEIGHT3.bits.x0_mv_dw = x0_mv_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32));
    VPSS_MCDI_VERTWEIGHT4.bits.k1_mt_dw = k1_mt_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32));
    VPSS_MCDI_VERTWEIGHT4.bits.g0_mt_dw = g0_mt_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32));
    VPSS_MCDI_VERTWEIGHT4.bits.k0_mt_dw = k0_mt_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32));
    VPSS_MCDI_VERTWEIGHT4.bits.x0_mt_dw = x0_mt_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}



HI_VOID VPSS_Die_SetBMtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32));
    VPSS_MCDI_VERTWEIGHT5.bits.b_mt_dw = b_mt_dw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32));
    VPSS_MCDI_VERTWEIGHT5.bits.k1_mv_mt = k1_mv_mt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32));
    VPSS_MCDI_VERTWEIGHT5.bits.x0_mv_mt = x0_mv_mt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Die_SetG0MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32));
    VPSS_MCDI_VERTWEIGHT5.bits.g0_mv_mt = g0_mv_mt;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}



HI_VOID VPSS_Die_SetMclpfMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mclpf_mode)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.mclpf_mode = mclpf_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetKPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.k_pxlmag_mcw = k_pxlmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetXPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.x_pxlmag_mcw = x_pxlmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetRsPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rs_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.rs_pxlmag_mcw = rs_pxlmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGainMclpfh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gain_mclpfh)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.gain_mclpfh = gain_mclpfh;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGainDnMclpfv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gain_dn_mclpfv)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.gain_dn_mclpfv = gain_dn_mclpfv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Die_SetGainUpMclpfv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gain_up_mclpfv)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC0.u32));
    VPSS_MCDI_MC0.bits.gain_up_mclpfv = gain_up_mclpfv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC0.u32), VPSS_MCDI_MC0.u32);

    return ;
}



HI_VOID VPSS_Die_SetGPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_pxlmag_mcw)
{
    U_VPSS_MCDI_MC1 VPSS_MCDI_MC1;

    VPSS_MCDI_MC1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC1.u32));
    VPSS_MCDI_MC1.bits.g_pxlmag_mcw = g_pxlmag_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC1.u32), VPSS_MCDI_MC1.u32);

    return ;
}



HI_VOID VPSS_Die_SetKCVertw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_c_vertw)
{
    U_VPSS_MCDI_MC2 VPSS_MCDI_MC2;

    VPSS_MCDI_MC2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC2.u32));
    VPSS_MCDI_MC2.bits.k_c_vertw = k_c_vertw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC2.u32), VPSS_MCDI_MC2.u32);

    return ;
}


HI_VOID VPSS_Die_SetKYVertw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_y_vertw)
{
    U_VPSS_MCDI_MC2 VPSS_MCDI_MC2;

    VPSS_MCDI_MC2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC2.u32));
    VPSS_MCDI_MC2.bits.k_y_vertw = k_y_vertw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC2.u32), VPSS_MCDI_MC2.u32);

    return ;
}



HI_VOID VPSS_Die_SetKFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_fstmt_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.k_fstmt_mc = k_fstmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetXFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_fstmt_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.x_fstmt_mc = x_fstmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1MvMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_mv_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.k1_mv_mc = k1_mv_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0MvMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_mv_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.x0_mv_mc = x0_mv_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetBdvMcpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bdv_mcpos)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.bdv_mcpos = bdv_mcpos;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetBdhMcpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bdh_mcpos)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.bdh_mcpos = bdh_mcpos;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Die_SetKDelta(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_delta)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC3.u32));
    VPSS_MCDI_MC3.bits.k_delta = k_delta;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC3.u32), VPSS_MCDI_MC3.u32);

    return ;
}



HI_VOID VPSS_Die_SetKHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_hfcore_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.k_hfcore_mc = k_hfcore_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Die_SetXHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_hfcore_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.x_hfcore_mc = x_hfcore_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Die_SetGSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.g_slmt_mc = g_slmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Die_SetKSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.k_slmt_mc = k_slmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Die_SetXSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.x_slmt_mc = x_slmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Die_SetGFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_fstmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC4.u32));
    VPSS_MCDI_MC4.bits.g_fstmt_mc = g_fstmt_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC4.u32), VPSS_MCDI_MC4.u32);

    return ;
}



HI_VOID VPSS_Die_SetR0Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 r0_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC5.u32));
    VPSS_MCDI_MC5.bits.r0_mc = r0_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC5.u32), VPSS_MCDI_MC5.u32);

    return ;
}


HI_VOID VPSS_Die_SetC0Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 c0_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC5.u32));
    VPSS_MCDI_MC5.bits.c0_mc = c0_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC5.u32), VPSS_MCDI_MC5.u32);

    return ;
}


HI_VOID VPSS_Die_SetGHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_hfcore_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC5.u32));
    VPSS_MCDI_MC5.bits.g_hfcore_mc = g_hfcore_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC5.u32), VPSS_MCDI_MC5.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcmvrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcmvrange)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC6.u32));
    VPSS_MCDI_MC6.bits.mcmvrange = mcmvrange;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC6.u32), VPSS_MCDI_MC6.u32);

    return ;
}


HI_VOID VPSS_Die_SetR1Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 r1_mc)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC6.u32));
    VPSS_MCDI_MC6.bits.r1_mc = r1_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC6.u32), VPSS_MCDI_MC6.u32);

    return ;
}


HI_VOID VPSS_Die_SetC1Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 c1_mc)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC6.u32));
    VPSS_MCDI_MC6.bits.c1_mc = c1_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC6.u32), VPSS_MCDI_MC6.u32);

    return ;
}



HI_VOID VPSS_Die_SetKFrcountMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_frcount_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC7.u32));
    VPSS_MCDI_MC7.bits.k_frcount_mc = k_frcount_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC7.u32), VPSS_MCDI_MC7.u32);

    return ;
}


HI_VOID VPSS_Die_SetXFrcountMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x_frcount_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC7.u32));
    VPSS_MCDI_MC7.bits.x_frcount_mc = x_frcount_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC7.u32), VPSS_MCDI_MC7.u32);

    return ;
}


HI_VOID VPSS_Die_SetScenechangeMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_MC7.u32));
    VPSS_MCDI_MC7.bits.scenechange_mc = scenechange_mc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_MC7.u32), VPSS_MCDI_MC7.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcendc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcendc)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32));
    VPSS_MCDI_LCDINEW0.bits.mcendc = mcendc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcendr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcendr)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32));
    VPSS_MCDI_LCDINEW0.bits.mcendr = mcendr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcstartc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcstartc)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32));
    VPSS_MCDI_LCDINEW0.bits.mcstartc = mcstartc;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Die_SetMcstartr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcstartr)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32));
    VPSS_MCDI_LCDINEW0.bits.mcstartr = mcstartr;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32), VPSS_MCDI_LCDINEW0.u32);

    return ;
}



HI_VOID VPSS_Die_SetMovegain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 movegain)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32));
    VPSS_MCDI_LCDINEW1.bits.movegain = movegain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMovecorig(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 movecorig)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32));
    VPSS_MCDI_LCDINEW1.bits.movecorig = movecorig;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMovethdl(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 movethdl)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32));
    VPSS_MCDI_LCDINEW1.bits.movethdl = movethdl;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Die_SetMovethdh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 movethdh)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32));
    VPSS_MCDI_LCDINEW1.bits.movethdh = movethdh;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32), VPSS_MCDI_LCDINEW1.u32);

    return ;
}



HI_VOID VPSS_Die_SetMcNumtBlden(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_numt_blden)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_NUMT.u32));
    VPSS_MCDI_NUMT.bits.mc_numt_blden = mc_numt_blden;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_NUMT.u32), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Die_SetNumtGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 numt_gain)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_NUMT.u32));
    VPSS_MCDI_NUMT.bits.numt_gain = numt_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_NUMT.u32), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Die_SetNumtCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 numt_coring)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_NUMT.u32));
    VPSS_MCDI_NUMT.bits.numt_coring = numt_coring;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_NUMT.u32), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Die_SetNumtLpfEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 numt_lpf_en)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_NUMT.u32));
    VPSS_MCDI_NUMT.bits.numt_lpf_en = numt_lpf_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_NUMT.u32), VPSS_MCDI_NUMT.u32);

    return ;
}



HI_VOID VPSS_Die_SetK1Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_hw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.k1_hw = k1_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_hw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.k0_hw = k0_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreHfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.core_hfvline = core_hfvline;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1Hfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.k1_hfvline = k1_hfvline;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0Hfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.k0_hfvline = k0_hfvline;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Die_SetCoreRglsw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rglsw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32));
    VPSS_MCDI_S3ADD0.bits.core_rglsw = core_rglsw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32), VPSS_MCDI_S3ADD0.u32);

    return ;
}



HI_VOID VPSS_Die_SetGDifcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_difcore_mcw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.g_difcore_mcw = g_difcore_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetSubpixMcEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 subpix_mc_en)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.subpix_mc_en = subpix_mc_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetCore1Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core1_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.core1_hw = core1_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetKCore0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_core0_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.k_core0_hw = k_core0_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetBCore0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 b_core0_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.b_core0_hw = b_core0_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Die_SetGHw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32));
    VPSS_MCDI_S3ADD1.bits.g_hw = g_hw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32), VPSS_MCDI_S3ADD1.u32);

    return ;
}



HI_VOID VPSS_Die_SetG0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32));
    VPSS_MCDI_S3ADD2.bits.g0_sadr_wnd_mcw = g0_sadr_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Die_SetK0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32));
    VPSS_MCDI_S3ADD2.bits.k0_sadr_wnd_mcw = k0_sadr_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Die_SetX0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 x0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32));
    VPSS_MCDI_S3ADD2.bits.x0_sadr_wnd_mcw = x0_sadr_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpK1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_k1_sad_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32));
    VPSS_MCDI_S3ADD2.bits.rp_k1_sad_wnd_mcw = rp_k1_sad_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpK1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_k1_mag_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32));
    VPSS_MCDI_S3ADD2.bits.rp_k1_mag_wnd_mcw = rp_k1_mag_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32), VPSS_MCDI_S3ADD2.u32);

    return ;
}



HI_VOID VPSS_Die_SetThCurBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_cur_blksad)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32));
    VPSS_MCDI_S3ADD3.bits.th_cur_blksad = th_cur_blksad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Die_SetKMcdifvMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mcdifv_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32));
    VPSS_MCDI_S3ADD3.bits.k_mcdifv_mcw = k_mcdifv_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Die_SetKP1cfdifhMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_p1cfdifh_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32));
    VPSS_MCDI_S3ADD3.bits.k_p1cfdifh_mcw = k_p1cfdifh_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Die_SetG1SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g1_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32));
    VPSS_MCDI_S3ADD3.bits.g1_sadr_wnd_mcw = g1_sadr_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32));
    VPSS_MCDI_S3ADD3.bits.k1_sadr_wnd_mcw = k1_sadr_wnd_mcw;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32), VPSS_MCDI_S3ADD3.u32);

    return ;
}



HI_VOID VPSS_Die_SetThCurBlkmotion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_cur_blkmotion)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32));
    VPSS_MCDI_S3ADD4.bits.th_cur_blkmotion = th_cur_blkmotion;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32), VPSS_MCDI_S3ADD4.u32);

    return ;
}


HI_VOID VPSS_Die_SetThlNeighBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thl_neigh_blksad)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32));
    VPSS_MCDI_S3ADD4.bits.thl_neigh_blksad = thl_neigh_blksad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32), VPSS_MCDI_S3ADD4.u32);

    return ;
}


HI_VOID VPSS_Die_SetThhNeighBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thh_neigh_blksad)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32));
    VPSS_MCDI_S3ADD4.bits.thh_neigh_blksad = thh_neigh_blksad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32), VPSS_MCDI_S3ADD4.u32);

    return ;
}



HI_VOID VPSS_Die_SetRpDifmvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difmvxth_rgmv)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.rp_difmvxth_rgmv = rp_difmvxth_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpMvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_mvxth_rgmv)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.rp_mvxth_rgmv = rp_mvxth_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpcounterth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rpcounterth)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.rpcounterth = rpcounterth;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Die_SetKRpcounter(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rpcounter)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.k_rpcounter = k_rpcounter;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Die_SetBlkmvUpdateEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_update_en)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.blkmv_update_en = blkmv_update_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Die_SetThRgmvMag(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_rgmv_mag)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32));
    VPSS_MCDI_S3ADD5.bits.th_rgmv_mag = th_rgmv_mag;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32), VPSS_MCDI_S3ADD5.u32);

    return ;
}



HI_VOID VPSS_Die_SetRpMagthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_magth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32));
    VPSS_MCDI_S3ADD6.bits.rp_magth_rgmv = rp_magth_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32), VPSS_MCDI_S3ADD6.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpSadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_sadth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32));
    VPSS_MCDI_S3ADD6.bits.rp_sadth_rgmv = rp_sadth_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32), VPSS_MCDI_S3ADD6.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpDifsadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difsadth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32));
    VPSS_MCDI_S3ADD6.bits.rp_difsadth_rgmv = rp_difsadth_rgmv;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32), VPSS_MCDI_S3ADD6.u32);

    return ;
}


HI_VOID VPSS_Die_SetSubmvSadchkEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 submv_sadchk_en)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.submv_sadchk_en = submv_sadchk_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}



HI_VOID VPSS_Die_SetRpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_en)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.rp_en = rp_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Die_SetDifvtMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 difvt_mode)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.difvt_mode = difvt_mode;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Die_SetK1TpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_tpdif_rgsad)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.k1_tpdif_rgsad = k1_tpdif_rgsad;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpDifsadthTb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difsadth_tb)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.rp_difsadth_tb = rp_difsadth_tb;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Die_SetRpDifmvxthSp(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difmvxth_sp)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32));
    VPSS_MCDI_S3ADD7.bits.rp_difmvxth_sp = rp_difmvxth_sp;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32), VPSS_MCDI_S3ADD7.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_5)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_5 = cntlut_5;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_4)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_4 = cntlut_4;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_3)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_3 = cntlut_3;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_2)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_2 = cntlut_2;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_1)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_1 = cntlut_1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_0)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32));
    VPSS_MCDI_STILLCNT0.bits.cntlut_0 = cntlut_0;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT0.u32);

    return ;
}

HI_VOID VPSS_Die_SetMcwScntGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcw_scnt_gain)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.mcw_scnt_gain = mcw_scnt_gain;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetMcwScntEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcw_scnt_en)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.mcw_scnt_en = mcw_scnt_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetMcMtshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mc_mtshift)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.mc_mtshift = mc_mtshift;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_8)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.cntlut_8 = cntlut_8;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_7)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.cntlut_7 = cntlut_7;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetCntlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cntlut_6)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32));
    VPSS_MCDI_STILLCNT1.bits.cntlut_6 = cntlut_6;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32), VPSS_MCDI_STILLCNT1.u32);

    return ;
}

HI_VOID VPSS_Die_SetDemoBorder(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 demo_border)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DEMO.u32));
    VPSS_MCDI_DEMO.bits.demo_border = demo_border;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DEMO.u32), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Die_SetDemoModeR(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 demo_mode_r)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DEMO.u32));
    VPSS_MCDI_DEMO.bits.demo_mode_r = demo_mode_r;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DEMO.u32), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Die_SetDemoModeL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 demo_mode_l)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DEMO.u32));
    VPSS_MCDI_DEMO.bits.demo_mode_l = demo_mode_l;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DEMO.u32), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Die_SetDemoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 demo_en)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_MCDI_DEMO.u32));
    VPSS_MCDI_DEMO.bits.demo_en = demo_en;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_MCDI_DEMO.u32), VPSS_MCDI_DEMO.u32);

    return ;
}

//module_name : DIE



