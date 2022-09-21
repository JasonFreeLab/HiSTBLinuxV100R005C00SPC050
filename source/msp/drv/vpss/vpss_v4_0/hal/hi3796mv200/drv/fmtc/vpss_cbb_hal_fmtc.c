

//#include "vpss_reg.h"
#include "vpss_cbb_common.h"


HI_VOID VPSS_Csc_SetVpssFmtcDemoOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_fmtc_demo_offset)
{
    U_VPSS_FMTC_GAMMA_CSC_CTRL VPSS_FMTC_GAMMA_CSC_CTRL;

    VPSS_FMTC_GAMMA_CSC_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32));
    VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_offset = vpss_fmtc_demo_offset;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32), VPSS_FMTC_GAMMA_CSC_CTRL.u32);

    return ;
}


HI_VOID VPSS_Csc_SetVpssFmtcDemoMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_fmtc_demo_mode)
{
    U_VPSS_FMTC_GAMMA_CSC_CTRL VPSS_FMTC_GAMMA_CSC_CTRL;

    VPSS_FMTC_GAMMA_CSC_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32));
    VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_mode = vpss_fmtc_demo_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32), VPSS_FMTC_GAMMA_CSC_CTRL.u32);

    return ;
}


HI_VOID VPSS_Csc_SetVpssFmtcDemoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_fmtc_demo_en)
{
    U_VPSS_FMTC_GAMMA_CSC_CTRL VPSS_FMTC_GAMMA_CSC_CTRL;

    VPSS_FMTC_GAMMA_CSC_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32));
    VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_en = vpss_fmtc_demo_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32), VPSS_FMTC_GAMMA_CSC_CTRL.u32);

    return ;
}


HI_VOID VPSS_Csc_SetVpssGammaEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_gamma_en)
{
    U_VPSS_FMTC_GAMMA_CSC_CTRL VPSS_FMTC_GAMMA_CSC_CTRL;

    VPSS_FMTC_GAMMA_CSC_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32));
    VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_gamma_en = vpss_gamma_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32), VPSS_FMTC_GAMMA_CSC_CTRL.u32);

    return ;
}


HI_VOID VPSS_Csc_SetVpssCscEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_csc_en)
{
    U_VPSS_FMTC_GAMMA_CSC_CTRL VPSS_FMTC_GAMMA_CSC_CTRL;

    VPSS_FMTC_GAMMA_CSC_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32));
    VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_csc_en = vpss_csc_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_CSC_CTRL.u32), VPSS_FMTC_GAMMA_CSC_CTRL.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_03)
{
    U_VPSS_FMTC_GAMMA_YLUT_0 VPSS_FMTC_GAMMA_YLUT_0;

    VPSS_FMTC_GAMMA_YLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32));
    VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_03 = gamma_y_lut_03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32), VPSS_FMTC_GAMMA_YLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_02)
{
    U_VPSS_FMTC_GAMMA_YLUT_0 VPSS_FMTC_GAMMA_YLUT_0;

    VPSS_FMTC_GAMMA_YLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32));
    VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_02 = gamma_y_lut_02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32), VPSS_FMTC_GAMMA_YLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_01)
{
    U_VPSS_FMTC_GAMMA_YLUT_0 VPSS_FMTC_GAMMA_YLUT_0;

    VPSS_FMTC_GAMMA_YLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32));
    VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_01 = gamma_y_lut_01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32), VPSS_FMTC_GAMMA_YLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_00)
{
    U_VPSS_FMTC_GAMMA_YLUT_0 VPSS_FMTC_GAMMA_YLUT_0;

    VPSS_FMTC_GAMMA_YLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32));
    VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_00 = gamma_y_lut_00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_0.u32), VPSS_FMTC_GAMMA_YLUT_0.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_07)
{
    U_VPSS_FMTC_GAMMA_YLUT_1 VPSS_FMTC_GAMMA_YLUT_1;

    VPSS_FMTC_GAMMA_YLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32));
    VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_07 = gamma_y_lut_07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32), VPSS_FMTC_GAMMA_YLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_06)
{
    U_VPSS_FMTC_GAMMA_YLUT_1 VPSS_FMTC_GAMMA_YLUT_1;

    VPSS_FMTC_GAMMA_YLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32));
    VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_06 = gamma_y_lut_06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32), VPSS_FMTC_GAMMA_YLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_05)
{
    U_VPSS_FMTC_GAMMA_YLUT_1 VPSS_FMTC_GAMMA_YLUT_1;

    VPSS_FMTC_GAMMA_YLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32));
    VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_05 = gamma_y_lut_05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32), VPSS_FMTC_GAMMA_YLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_04)
{
    U_VPSS_FMTC_GAMMA_YLUT_1 VPSS_FMTC_GAMMA_YLUT_1;

    VPSS_FMTC_GAMMA_YLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32));
    VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_04 = gamma_y_lut_04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_1.u32), VPSS_FMTC_GAMMA_YLUT_1.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_11)
{
    U_VPSS_FMTC_GAMMA_YLUT_2 VPSS_FMTC_GAMMA_YLUT_2;

    VPSS_FMTC_GAMMA_YLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32));
    VPSS_FMTC_GAMMA_YLUT_2.bits.gamma_y_lut_11 = gamma_y_lut_11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32), VPSS_FMTC_GAMMA_YLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_10)
{
    U_VPSS_FMTC_GAMMA_YLUT_2 VPSS_FMTC_GAMMA_YLUT_2;

    VPSS_FMTC_GAMMA_YLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32));
    VPSS_FMTC_GAMMA_YLUT_2.bits.gamma_y_lut_10 = gamma_y_lut_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32), VPSS_FMTC_GAMMA_YLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut09(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_09)
{
    U_VPSS_FMTC_GAMMA_YLUT_2 VPSS_FMTC_GAMMA_YLUT_2;

    VPSS_FMTC_GAMMA_YLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32));
    VPSS_FMTC_GAMMA_YLUT_2.bits.gamma_y_lut_09 = gamma_y_lut_09;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32), VPSS_FMTC_GAMMA_YLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_08)
{
    U_VPSS_FMTC_GAMMA_YLUT_2 VPSS_FMTC_GAMMA_YLUT_2;

    VPSS_FMTC_GAMMA_YLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32));
    VPSS_FMTC_GAMMA_YLUT_2.bits.gamma_y_lut_08 = gamma_y_lut_08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_2.u32), VPSS_FMTC_GAMMA_YLUT_2.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_15)
{
    U_VPSS_FMTC_GAMMA_YLUT_3 VPSS_FMTC_GAMMA_YLUT_3;

    VPSS_FMTC_GAMMA_YLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32));
    VPSS_FMTC_GAMMA_YLUT_3.bits.gamma_y_lut_15 = gamma_y_lut_15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32), VPSS_FMTC_GAMMA_YLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_14)
{
    U_VPSS_FMTC_GAMMA_YLUT_3 VPSS_FMTC_GAMMA_YLUT_3;

    VPSS_FMTC_GAMMA_YLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32));
    VPSS_FMTC_GAMMA_YLUT_3.bits.gamma_y_lut_14 = gamma_y_lut_14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32), VPSS_FMTC_GAMMA_YLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_13)
{
    U_VPSS_FMTC_GAMMA_YLUT_3 VPSS_FMTC_GAMMA_YLUT_3;

    VPSS_FMTC_GAMMA_YLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32));
    VPSS_FMTC_GAMMA_YLUT_3.bits.gamma_y_lut_13 = gamma_y_lut_13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32), VPSS_FMTC_GAMMA_YLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_12)
{
    U_VPSS_FMTC_GAMMA_YLUT_3 VPSS_FMTC_GAMMA_YLUT_3;

    VPSS_FMTC_GAMMA_YLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32));
    VPSS_FMTC_GAMMA_YLUT_3.bits.gamma_y_lut_12 = gamma_y_lut_12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_3.u32), VPSS_FMTC_GAMMA_YLUT_3.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_19)
{
    U_VPSS_FMTC_GAMMA_YLUT_4 VPSS_FMTC_GAMMA_YLUT_4;

    VPSS_FMTC_GAMMA_YLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32));
    VPSS_FMTC_GAMMA_YLUT_4.bits.gamma_y_lut_19 = gamma_y_lut_19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32), VPSS_FMTC_GAMMA_YLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_18)
{
    U_VPSS_FMTC_GAMMA_YLUT_4 VPSS_FMTC_GAMMA_YLUT_4;

    VPSS_FMTC_GAMMA_YLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32));
    VPSS_FMTC_GAMMA_YLUT_4.bits.gamma_y_lut_18 = gamma_y_lut_18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32), VPSS_FMTC_GAMMA_YLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_17)
{
    U_VPSS_FMTC_GAMMA_YLUT_4 VPSS_FMTC_GAMMA_YLUT_4;

    VPSS_FMTC_GAMMA_YLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32));
    VPSS_FMTC_GAMMA_YLUT_4.bits.gamma_y_lut_17 = gamma_y_lut_17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32), VPSS_FMTC_GAMMA_YLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_16)
{
    U_VPSS_FMTC_GAMMA_YLUT_4 VPSS_FMTC_GAMMA_YLUT_4;

    VPSS_FMTC_GAMMA_YLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32));
    VPSS_FMTC_GAMMA_YLUT_4.bits.gamma_y_lut_16 = gamma_y_lut_16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_4.u32), VPSS_FMTC_GAMMA_YLUT_4.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_23)
{
    U_VPSS_FMTC_GAMMA_YLUT_5 VPSS_FMTC_GAMMA_YLUT_5;

    VPSS_FMTC_GAMMA_YLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32));
    VPSS_FMTC_GAMMA_YLUT_5.bits.gamma_y_lut_23 = gamma_y_lut_23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32), VPSS_FMTC_GAMMA_YLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_22)
{
    U_VPSS_FMTC_GAMMA_YLUT_5 VPSS_FMTC_GAMMA_YLUT_5;

    VPSS_FMTC_GAMMA_YLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32));
    VPSS_FMTC_GAMMA_YLUT_5.bits.gamma_y_lut_22 = gamma_y_lut_22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32), VPSS_FMTC_GAMMA_YLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_21)
{
    U_VPSS_FMTC_GAMMA_YLUT_5 VPSS_FMTC_GAMMA_YLUT_5;

    VPSS_FMTC_GAMMA_YLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32));
    VPSS_FMTC_GAMMA_YLUT_5.bits.gamma_y_lut_21 = gamma_y_lut_21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32), VPSS_FMTC_GAMMA_YLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_20)
{
    U_VPSS_FMTC_GAMMA_YLUT_5 VPSS_FMTC_GAMMA_YLUT_5;

    VPSS_FMTC_GAMMA_YLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32));
    VPSS_FMTC_GAMMA_YLUT_5.bits.gamma_y_lut_20 = gamma_y_lut_20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_5.u32), VPSS_FMTC_GAMMA_YLUT_5.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_27)
{
    U_VPSS_FMTC_GAMMA_YLUT_6 VPSS_FMTC_GAMMA_YLUT_6;

    VPSS_FMTC_GAMMA_YLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32));
    VPSS_FMTC_GAMMA_YLUT_6.bits.gamma_y_lut_27 = gamma_y_lut_27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32), VPSS_FMTC_GAMMA_YLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_26)
{
    U_VPSS_FMTC_GAMMA_YLUT_6 VPSS_FMTC_GAMMA_YLUT_6;

    VPSS_FMTC_GAMMA_YLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32));
    VPSS_FMTC_GAMMA_YLUT_6.bits.gamma_y_lut_26 = gamma_y_lut_26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32), VPSS_FMTC_GAMMA_YLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_25)
{
    U_VPSS_FMTC_GAMMA_YLUT_6 VPSS_FMTC_GAMMA_YLUT_6;

    VPSS_FMTC_GAMMA_YLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32));
    VPSS_FMTC_GAMMA_YLUT_6.bits.gamma_y_lut_25 = gamma_y_lut_25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32), VPSS_FMTC_GAMMA_YLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_24)
{
    U_VPSS_FMTC_GAMMA_YLUT_6 VPSS_FMTC_GAMMA_YLUT_6;

    VPSS_FMTC_GAMMA_YLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32));
    VPSS_FMTC_GAMMA_YLUT_6.bits.gamma_y_lut_24 = gamma_y_lut_24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_6.u32), VPSS_FMTC_GAMMA_YLUT_6.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_31)
{
    U_VPSS_FMTC_GAMMA_YLUT_7 VPSS_FMTC_GAMMA_YLUT_7;

    VPSS_FMTC_GAMMA_YLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32));
    VPSS_FMTC_GAMMA_YLUT_7.bits.gamma_y_lut_31 = gamma_y_lut_31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32), VPSS_FMTC_GAMMA_YLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_30)
{
    U_VPSS_FMTC_GAMMA_YLUT_7 VPSS_FMTC_GAMMA_YLUT_7;

    VPSS_FMTC_GAMMA_YLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32));
    VPSS_FMTC_GAMMA_YLUT_7.bits.gamma_y_lut_30 = gamma_y_lut_30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32), VPSS_FMTC_GAMMA_YLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_29)
{
    U_VPSS_FMTC_GAMMA_YLUT_7 VPSS_FMTC_GAMMA_YLUT_7;

    VPSS_FMTC_GAMMA_YLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32));
    VPSS_FMTC_GAMMA_YLUT_7.bits.gamma_y_lut_29 = gamma_y_lut_29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32), VPSS_FMTC_GAMMA_YLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaYLut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_28)
{
    U_VPSS_FMTC_GAMMA_YLUT_7 VPSS_FMTC_GAMMA_YLUT_7;

    VPSS_FMTC_GAMMA_YLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32));
    VPSS_FMTC_GAMMA_YLUT_7.bits.gamma_y_lut_28 = gamma_y_lut_28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_7.u32), VPSS_FMTC_GAMMA_YLUT_7.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaYLut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_y_lut_32)
{
    U_VPSS_FMTC_GAMMA_YLUT_8 VPSS_FMTC_GAMMA_YLUT_8;

    VPSS_FMTC_GAMMA_YLUT_8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_8.u32));
    VPSS_FMTC_GAMMA_YLUT_8.bits.gamma_y_lut_32 = gamma_y_lut_32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_YLUT_8.u32), VPSS_FMTC_GAMMA_YLUT_8.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_03)
{
    U_VPSS_FMTC_GAMMA_ULUT_0 VPSS_FMTC_GAMMA_ULUT_0;

    VPSS_FMTC_GAMMA_ULUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32));
    VPSS_FMTC_GAMMA_ULUT_0.bits.gamma_u_lut_03 = gamma_u_lut_03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32), VPSS_FMTC_GAMMA_ULUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_02)
{
    U_VPSS_FMTC_GAMMA_ULUT_0 VPSS_FMTC_GAMMA_ULUT_0;

    VPSS_FMTC_GAMMA_ULUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32));
    VPSS_FMTC_GAMMA_ULUT_0.bits.gamma_u_lut_02 = gamma_u_lut_02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32), VPSS_FMTC_GAMMA_ULUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_01)
{
    U_VPSS_FMTC_GAMMA_ULUT_0 VPSS_FMTC_GAMMA_ULUT_0;

    VPSS_FMTC_GAMMA_ULUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32));
    VPSS_FMTC_GAMMA_ULUT_0.bits.gamma_u_lut_01 = gamma_u_lut_01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32), VPSS_FMTC_GAMMA_ULUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_00)
{
    U_VPSS_FMTC_GAMMA_ULUT_0 VPSS_FMTC_GAMMA_ULUT_0;

    VPSS_FMTC_GAMMA_ULUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32));
    VPSS_FMTC_GAMMA_ULUT_0.bits.gamma_u_lut_00 = gamma_u_lut_00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_0.u32), VPSS_FMTC_GAMMA_ULUT_0.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_07)
{
    U_VPSS_FMTC_GAMMA_ULUT_1 VPSS_FMTC_GAMMA_ULUT_1;

    VPSS_FMTC_GAMMA_ULUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32));
    VPSS_FMTC_GAMMA_ULUT_1.bits.gamma_u_lut_07 = gamma_u_lut_07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32), VPSS_FMTC_GAMMA_ULUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_06)
{
    U_VPSS_FMTC_GAMMA_ULUT_1 VPSS_FMTC_GAMMA_ULUT_1;

    VPSS_FMTC_GAMMA_ULUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32));
    VPSS_FMTC_GAMMA_ULUT_1.bits.gamma_u_lut_06 = gamma_u_lut_06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32), VPSS_FMTC_GAMMA_ULUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_05)
{
    U_VPSS_FMTC_GAMMA_ULUT_1 VPSS_FMTC_GAMMA_ULUT_1;

    VPSS_FMTC_GAMMA_ULUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32));
    VPSS_FMTC_GAMMA_ULUT_1.bits.gamma_u_lut_05 = gamma_u_lut_05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32), VPSS_FMTC_GAMMA_ULUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_04)
{
    U_VPSS_FMTC_GAMMA_ULUT_1 VPSS_FMTC_GAMMA_ULUT_1;

    VPSS_FMTC_GAMMA_ULUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32));
    VPSS_FMTC_GAMMA_ULUT_1.bits.gamma_u_lut_04 = gamma_u_lut_04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_1.u32), VPSS_FMTC_GAMMA_ULUT_1.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_11)
{
    U_VPSS_FMTC_GAMMA_ULUT_2 VPSS_FMTC_GAMMA_ULUT_2;

    VPSS_FMTC_GAMMA_ULUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32));
    VPSS_FMTC_GAMMA_ULUT_2.bits.gamma_u_lut_11 = gamma_u_lut_11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32), VPSS_FMTC_GAMMA_ULUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_10)
{
    U_VPSS_FMTC_GAMMA_ULUT_2 VPSS_FMTC_GAMMA_ULUT_2;

    VPSS_FMTC_GAMMA_ULUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32));
    VPSS_FMTC_GAMMA_ULUT_2.bits.gamma_u_lut_10 = gamma_u_lut_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32), VPSS_FMTC_GAMMA_ULUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut09(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_09)
{
    U_VPSS_FMTC_GAMMA_ULUT_2 VPSS_FMTC_GAMMA_ULUT_2;

    VPSS_FMTC_GAMMA_ULUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32));
    VPSS_FMTC_GAMMA_ULUT_2.bits.gamma_u_lut_09 = gamma_u_lut_09;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32), VPSS_FMTC_GAMMA_ULUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_08)
{
    U_VPSS_FMTC_GAMMA_ULUT_2 VPSS_FMTC_GAMMA_ULUT_2;

    VPSS_FMTC_GAMMA_ULUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32));
    VPSS_FMTC_GAMMA_ULUT_2.bits.gamma_u_lut_08 = gamma_u_lut_08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_2.u32), VPSS_FMTC_GAMMA_ULUT_2.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_15)
{
    U_VPSS_FMTC_GAMMA_ULUT_3 VPSS_FMTC_GAMMA_ULUT_3;

    VPSS_FMTC_GAMMA_ULUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32));
    VPSS_FMTC_GAMMA_ULUT_3.bits.gamma_u_lut_15 = gamma_u_lut_15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32), VPSS_FMTC_GAMMA_ULUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_14)
{
    U_VPSS_FMTC_GAMMA_ULUT_3 VPSS_FMTC_GAMMA_ULUT_3;

    VPSS_FMTC_GAMMA_ULUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32));
    VPSS_FMTC_GAMMA_ULUT_3.bits.gamma_u_lut_14 = gamma_u_lut_14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32), VPSS_FMTC_GAMMA_ULUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_13)
{
    U_VPSS_FMTC_GAMMA_ULUT_3 VPSS_FMTC_GAMMA_ULUT_3;

    VPSS_FMTC_GAMMA_ULUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32));
    VPSS_FMTC_GAMMA_ULUT_3.bits.gamma_u_lut_13 = gamma_u_lut_13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32), VPSS_FMTC_GAMMA_ULUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_12)
{
    U_VPSS_FMTC_GAMMA_ULUT_3 VPSS_FMTC_GAMMA_ULUT_3;

    VPSS_FMTC_GAMMA_ULUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32));
    VPSS_FMTC_GAMMA_ULUT_3.bits.gamma_u_lut_12 = gamma_u_lut_12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_3.u32), VPSS_FMTC_GAMMA_ULUT_3.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_19)
{
    U_VPSS_FMTC_GAMMA_ULUT_4 VPSS_FMTC_GAMMA_ULUT_4;

    VPSS_FMTC_GAMMA_ULUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32));
    VPSS_FMTC_GAMMA_ULUT_4.bits.gamma_u_lut_19 = gamma_u_lut_19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32), VPSS_FMTC_GAMMA_ULUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_18)
{
    U_VPSS_FMTC_GAMMA_ULUT_4 VPSS_FMTC_GAMMA_ULUT_4;

    VPSS_FMTC_GAMMA_ULUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32));
    VPSS_FMTC_GAMMA_ULUT_4.bits.gamma_u_lut_18 = gamma_u_lut_18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32), VPSS_FMTC_GAMMA_ULUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_17)
{
    U_VPSS_FMTC_GAMMA_ULUT_4 VPSS_FMTC_GAMMA_ULUT_4;

    VPSS_FMTC_GAMMA_ULUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32));
    VPSS_FMTC_GAMMA_ULUT_4.bits.gamma_u_lut_17 = gamma_u_lut_17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32), VPSS_FMTC_GAMMA_ULUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_16)
{
    U_VPSS_FMTC_GAMMA_ULUT_4 VPSS_FMTC_GAMMA_ULUT_4;

    VPSS_FMTC_GAMMA_ULUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32));
    VPSS_FMTC_GAMMA_ULUT_4.bits.gamma_u_lut_16 = gamma_u_lut_16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_4.u32), VPSS_FMTC_GAMMA_ULUT_4.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_23)
{
    U_VPSS_FMTC_GAMMA_ULUT_5 VPSS_FMTC_GAMMA_ULUT_5;

    VPSS_FMTC_GAMMA_ULUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32));
    VPSS_FMTC_GAMMA_ULUT_5.bits.gamma_u_lut_23 = gamma_u_lut_23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32), VPSS_FMTC_GAMMA_ULUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_22)
{
    U_VPSS_FMTC_GAMMA_ULUT_5 VPSS_FMTC_GAMMA_ULUT_5;

    VPSS_FMTC_GAMMA_ULUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32));
    VPSS_FMTC_GAMMA_ULUT_5.bits.gamma_u_lut_22 = gamma_u_lut_22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32), VPSS_FMTC_GAMMA_ULUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_21)
{
    U_VPSS_FMTC_GAMMA_ULUT_5 VPSS_FMTC_GAMMA_ULUT_5;

    VPSS_FMTC_GAMMA_ULUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32));
    VPSS_FMTC_GAMMA_ULUT_5.bits.gamma_u_lut_21 = gamma_u_lut_21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32), VPSS_FMTC_GAMMA_ULUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_20)
{
    U_VPSS_FMTC_GAMMA_ULUT_5 VPSS_FMTC_GAMMA_ULUT_5;

    VPSS_FMTC_GAMMA_ULUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32));
    VPSS_FMTC_GAMMA_ULUT_5.bits.gamma_u_lut_20 = gamma_u_lut_20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_5.u32), VPSS_FMTC_GAMMA_ULUT_5.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_27)
{
    U_VPSS_FMTC_GAMMA_ULUT_6 VPSS_FMTC_GAMMA_ULUT_6;

    VPSS_FMTC_GAMMA_ULUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32));
    VPSS_FMTC_GAMMA_ULUT_6.bits.gamma_u_lut_27 = gamma_u_lut_27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32), VPSS_FMTC_GAMMA_ULUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_26)
{
    U_VPSS_FMTC_GAMMA_ULUT_6 VPSS_FMTC_GAMMA_ULUT_6;

    VPSS_FMTC_GAMMA_ULUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32));
    VPSS_FMTC_GAMMA_ULUT_6.bits.gamma_u_lut_26 = gamma_u_lut_26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32), VPSS_FMTC_GAMMA_ULUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_25)
{
    U_VPSS_FMTC_GAMMA_ULUT_6 VPSS_FMTC_GAMMA_ULUT_6;

    VPSS_FMTC_GAMMA_ULUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32));
    VPSS_FMTC_GAMMA_ULUT_6.bits.gamma_u_lut_25 = gamma_u_lut_25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32), VPSS_FMTC_GAMMA_ULUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_24)
{
    U_VPSS_FMTC_GAMMA_ULUT_6 VPSS_FMTC_GAMMA_ULUT_6;

    VPSS_FMTC_GAMMA_ULUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32));
    VPSS_FMTC_GAMMA_ULUT_6.bits.gamma_u_lut_24 = gamma_u_lut_24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_6.u32), VPSS_FMTC_GAMMA_ULUT_6.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_31)
{
    U_VPSS_FMTC_GAMMA_ULUT_7 VPSS_FMTC_GAMMA_ULUT_7;

    VPSS_FMTC_GAMMA_ULUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32));
    VPSS_FMTC_GAMMA_ULUT_7.bits.gamma_u_lut_31 = gamma_u_lut_31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32), VPSS_FMTC_GAMMA_ULUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_30)
{
    U_VPSS_FMTC_GAMMA_ULUT_7 VPSS_FMTC_GAMMA_ULUT_7;

    VPSS_FMTC_GAMMA_ULUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32));
    VPSS_FMTC_GAMMA_ULUT_7.bits.gamma_u_lut_30 = gamma_u_lut_30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32), VPSS_FMTC_GAMMA_ULUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_29)
{
    U_VPSS_FMTC_GAMMA_ULUT_7 VPSS_FMTC_GAMMA_ULUT_7;

    VPSS_FMTC_GAMMA_ULUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32));
    VPSS_FMTC_GAMMA_ULUT_7.bits.gamma_u_lut_29 = gamma_u_lut_29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32), VPSS_FMTC_GAMMA_ULUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaULut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_28)
{
    U_VPSS_FMTC_GAMMA_ULUT_7 VPSS_FMTC_GAMMA_ULUT_7;

    VPSS_FMTC_GAMMA_ULUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32));
    VPSS_FMTC_GAMMA_ULUT_7.bits.gamma_u_lut_28 = gamma_u_lut_28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_7.u32), VPSS_FMTC_GAMMA_ULUT_7.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaULut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_u_lut_32)
{
    U_VPSS_FMTC_GAMMA_ULUT_8 VPSS_FMTC_GAMMA_ULUT_8;

    VPSS_FMTC_GAMMA_ULUT_8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_8.u32));
    VPSS_FMTC_GAMMA_ULUT_8.bits.gamma_u_lut_32 = gamma_u_lut_32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_ULUT_8.u32), VPSS_FMTC_GAMMA_ULUT_8.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_03)
{
    U_VPSS_FMTC_GAMMA_VLUT_0 VPSS_FMTC_GAMMA_VLUT_0;

    VPSS_FMTC_GAMMA_VLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32));
    VPSS_FMTC_GAMMA_VLUT_0.bits.gamma_v_lut_03 = gamma_v_lut_03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32), VPSS_FMTC_GAMMA_VLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_02)
{
    U_VPSS_FMTC_GAMMA_VLUT_0 VPSS_FMTC_GAMMA_VLUT_0;

    VPSS_FMTC_GAMMA_VLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32));
    VPSS_FMTC_GAMMA_VLUT_0.bits.gamma_v_lut_02 = gamma_v_lut_02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32), VPSS_FMTC_GAMMA_VLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_01)
{
    U_VPSS_FMTC_GAMMA_VLUT_0 VPSS_FMTC_GAMMA_VLUT_0;

    VPSS_FMTC_GAMMA_VLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32));
    VPSS_FMTC_GAMMA_VLUT_0.bits.gamma_v_lut_01 = gamma_v_lut_01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32), VPSS_FMTC_GAMMA_VLUT_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_00)
{
    U_VPSS_FMTC_GAMMA_VLUT_0 VPSS_FMTC_GAMMA_VLUT_0;

    VPSS_FMTC_GAMMA_VLUT_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32));
    VPSS_FMTC_GAMMA_VLUT_0.bits.gamma_v_lut_00 = gamma_v_lut_00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_0.u32), VPSS_FMTC_GAMMA_VLUT_0.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_07)
{
    U_VPSS_FMTC_GAMMA_VLUT_1 VPSS_FMTC_GAMMA_VLUT_1;

    VPSS_FMTC_GAMMA_VLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32));
    VPSS_FMTC_GAMMA_VLUT_1.bits.gamma_v_lut_07 = gamma_v_lut_07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32), VPSS_FMTC_GAMMA_VLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_06)
{
    U_VPSS_FMTC_GAMMA_VLUT_1 VPSS_FMTC_GAMMA_VLUT_1;

    VPSS_FMTC_GAMMA_VLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32));
    VPSS_FMTC_GAMMA_VLUT_1.bits.gamma_v_lut_06 = gamma_v_lut_06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32), VPSS_FMTC_GAMMA_VLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_05)
{
    U_VPSS_FMTC_GAMMA_VLUT_1 VPSS_FMTC_GAMMA_VLUT_1;

    VPSS_FMTC_GAMMA_VLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32));
    VPSS_FMTC_GAMMA_VLUT_1.bits.gamma_v_lut_05 = gamma_v_lut_05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32), VPSS_FMTC_GAMMA_VLUT_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_04)
{
    U_VPSS_FMTC_GAMMA_VLUT_1 VPSS_FMTC_GAMMA_VLUT_1;

    VPSS_FMTC_GAMMA_VLUT_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32));
    VPSS_FMTC_GAMMA_VLUT_1.bits.gamma_v_lut_04 = gamma_v_lut_04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_1.u32), VPSS_FMTC_GAMMA_VLUT_1.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_11)
{
    U_VPSS_FMTC_GAMMA_VLUT_2 VPSS_FMTC_GAMMA_VLUT_2;

    VPSS_FMTC_GAMMA_VLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32));
    VPSS_FMTC_GAMMA_VLUT_2.bits.gamma_v_lut_11 = gamma_v_lut_11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32), VPSS_FMTC_GAMMA_VLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_10)
{
    U_VPSS_FMTC_GAMMA_VLUT_2 VPSS_FMTC_GAMMA_VLUT_2;

    VPSS_FMTC_GAMMA_VLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32));
    VPSS_FMTC_GAMMA_VLUT_2.bits.gamma_v_lut_10 = gamma_v_lut_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32), VPSS_FMTC_GAMMA_VLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut09(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_09)
{
    U_VPSS_FMTC_GAMMA_VLUT_2 VPSS_FMTC_GAMMA_VLUT_2;

    VPSS_FMTC_GAMMA_VLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32));
    VPSS_FMTC_GAMMA_VLUT_2.bits.gamma_v_lut_09 = gamma_v_lut_09;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32), VPSS_FMTC_GAMMA_VLUT_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_08)
{
    U_VPSS_FMTC_GAMMA_VLUT_2 VPSS_FMTC_GAMMA_VLUT_2;

    VPSS_FMTC_GAMMA_VLUT_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32));
    VPSS_FMTC_GAMMA_VLUT_2.bits.gamma_v_lut_08 = gamma_v_lut_08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_2.u32), VPSS_FMTC_GAMMA_VLUT_2.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_15)
{
    U_VPSS_FMTC_GAMMA_VLUT_3 VPSS_FMTC_GAMMA_VLUT_3;

    VPSS_FMTC_GAMMA_VLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32));
    VPSS_FMTC_GAMMA_VLUT_3.bits.gamma_v_lut_15 = gamma_v_lut_15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32), VPSS_FMTC_GAMMA_VLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_14)
{
    U_VPSS_FMTC_GAMMA_VLUT_3 VPSS_FMTC_GAMMA_VLUT_3;

    VPSS_FMTC_GAMMA_VLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32));
    VPSS_FMTC_GAMMA_VLUT_3.bits.gamma_v_lut_14 = gamma_v_lut_14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32), VPSS_FMTC_GAMMA_VLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_13)
{
    U_VPSS_FMTC_GAMMA_VLUT_3 VPSS_FMTC_GAMMA_VLUT_3;

    VPSS_FMTC_GAMMA_VLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32));
    VPSS_FMTC_GAMMA_VLUT_3.bits.gamma_v_lut_13 = gamma_v_lut_13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32), VPSS_FMTC_GAMMA_VLUT_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_12)
{
    U_VPSS_FMTC_GAMMA_VLUT_3 VPSS_FMTC_GAMMA_VLUT_3;

    VPSS_FMTC_GAMMA_VLUT_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32));
    VPSS_FMTC_GAMMA_VLUT_3.bits.gamma_v_lut_12 = gamma_v_lut_12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_3.u32), VPSS_FMTC_GAMMA_VLUT_3.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_19)
{
    U_VPSS_FMTC_GAMMA_VLUT_4 VPSS_FMTC_GAMMA_VLUT_4;

    VPSS_FMTC_GAMMA_VLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32));
    VPSS_FMTC_GAMMA_VLUT_4.bits.gamma_v_lut_19 = gamma_v_lut_19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32), VPSS_FMTC_GAMMA_VLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_18)
{
    U_VPSS_FMTC_GAMMA_VLUT_4 VPSS_FMTC_GAMMA_VLUT_4;

    VPSS_FMTC_GAMMA_VLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32));
    VPSS_FMTC_GAMMA_VLUT_4.bits.gamma_v_lut_18 = gamma_v_lut_18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32), VPSS_FMTC_GAMMA_VLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_17)
{
    U_VPSS_FMTC_GAMMA_VLUT_4 VPSS_FMTC_GAMMA_VLUT_4;

    VPSS_FMTC_GAMMA_VLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32));
    VPSS_FMTC_GAMMA_VLUT_4.bits.gamma_v_lut_17 = gamma_v_lut_17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32), VPSS_FMTC_GAMMA_VLUT_4.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_16)
{
    U_VPSS_FMTC_GAMMA_VLUT_4 VPSS_FMTC_GAMMA_VLUT_4;

    VPSS_FMTC_GAMMA_VLUT_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32));
    VPSS_FMTC_GAMMA_VLUT_4.bits.gamma_v_lut_16 = gamma_v_lut_16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_4.u32), VPSS_FMTC_GAMMA_VLUT_4.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_23)
{
    U_VPSS_FMTC_GAMMA_VLUT_5 VPSS_FMTC_GAMMA_VLUT_5;

    VPSS_FMTC_GAMMA_VLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32));
    VPSS_FMTC_GAMMA_VLUT_5.bits.gamma_v_lut_23 = gamma_v_lut_23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32), VPSS_FMTC_GAMMA_VLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_22)
{
    U_VPSS_FMTC_GAMMA_VLUT_5 VPSS_FMTC_GAMMA_VLUT_5;

    VPSS_FMTC_GAMMA_VLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32));
    VPSS_FMTC_GAMMA_VLUT_5.bits.gamma_v_lut_22 = gamma_v_lut_22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32), VPSS_FMTC_GAMMA_VLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_21)
{
    U_VPSS_FMTC_GAMMA_VLUT_5 VPSS_FMTC_GAMMA_VLUT_5;

    VPSS_FMTC_GAMMA_VLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32));
    VPSS_FMTC_GAMMA_VLUT_5.bits.gamma_v_lut_21 = gamma_v_lut_21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32), VPSS_FMTC_GAMMA_VLUT_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_20)
{
    U_VPSS_FMTC_GAMMA_VLUT_5 VPSS_FMTC_GAMMA_VLUT_5;

    VPSS_FMTC_GAMMA_VLUT_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32));
    VPSS_FMTC_GAMMA_VLUT_5.bits.gamma_v_lut_20 = gamma_v_lut_20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_5.u32), VPSS_FMTC_GAMMA_VLUT_5.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_27)
{
    U_VPSS_FMTC_GAMMA_VLUT_6 VPSS_FMTC_GAMMA_VLUT_6;

    VPSS_FMTC_GAMMA_VLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32));
    VPSS_FMTC_GAMMA_VLUT_6.bits.gamma_v_lut_27 = gamma_v_lut_27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32), VPSS_FMTC_GAMMA_VLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_26)
{
    U_VPSS_FMTC_GAMMA_VLUT_6 VPSS_FMTC_GAMMA_VLUT_6;

    VPSS_FMTC_GAMMA_VLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32));
    VPSS_FMTC_GAMMA_VLUT_6.bits.gamma_v_lut_26 = gamma_v_lut_26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32), VPSS_FMTC_GAMMA_VLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_25)
{
    U_VPSS_FMTC_GAMMA_VLUT_6 VPSS_FMTC_GAMMA_VLUT_6;

    VPSS_FMTC_GAMMA_VLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32));
    VPSS_FMTC_GAMMA_VLUT_6.bits.gamma_v_lut_25 = gamma_v_lut_25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32), VPSS_FMTC_GAMMA_VLUT_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_24)
{
    U_VPSS_FMTC_GAMMA_VLUT_6 VPSS_FMTC_GAMMA_VLUT_6;

    VPSS_FMTC_GAMMA_VLUT_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32));
    VPSS_FMTC_GAMMA_VLUT_6.bits.gamma_v_lut_24 = gamma_v_lut_24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_6.u32), VPSS_FMTC_GAMMA_VLUT_6.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_31)
{
    U_VPSS_FMTC_GAMMA_VLUT_7 VPSS_FMTC_GAMMA_VLUT_7;

    VPSS_FMTC_GAMMA_VLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32));
    VPSS_FMTC_GAMMA_VLUT_7.bits.gamma_v_lut_31 = gamma_v_lut_31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32), VPSS_FMTC_GAMMA_VLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_30)
{
    U_VPSS_FMTC_GAMMA_VLUT_7 VPSS_FMTC_GAMMA_VLUT_7;

    VPSS_FMTC_GAMMA_VLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32));
    VPSS_FMTC_GAMMA_VLUT_7.bits.gamma_v_lut_30 = gamma_v_lut_30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32), VPSS_FMTC_GAMMA_VLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_29)
{
    U_VPSS_FMTC_GAMMA_VLUT_7 VPSS_FMTC_GAMMA_VLUT_7;

    VPSS_FMTC_GAMMA_VLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32));
    VPSS_FMTC_GAMMA_VLUT_7.bits.gamma_v_lut_29 = gamma_v_lut_29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32), VPSS_FMTC_GAMMA_VLUT_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetGammaVLut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_28)
{
    U_VPSS_FMTC_GAMMA_VLUT_7 VPSS_FMTC_GAMMA_VLUT_7;

    VPSS_FMTC_GAMMA_VLUT_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32));
    VPSS_FMTC_GAMMA_VLUT_7.bits.gamma_v_lut_28 = gamma_v_lut_28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_7.u32), VPSS_FMTC_GAMMA_VLUT_7.u32);

    return ;
}



HI_VOID VPSS_Csc_SetGammaVLut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gamma_v_lut_32)
{
    U_VPSS_FMTC_GAMMA_VLUT_8 VPSS_FMTC_GAMMA_VLUT_8;

    VPSS_FMTC_GAMMA_VLUT_8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_8.u32));
    VPSS_FMTC_GAMMA_VLUT_8.bits.gamma_v_lut_32 = gamma_v_lut_32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_GAMMA_VLUT_8.u32), VPSS_FMTC_GAMMA_VLUT_8.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscCoef01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_01)
{
    U_VPSS_FMTC_CSC_COEF_0 VPSS_FMTC_CSC_COEF_0;

    VPSS_FMTC_CSC_COEF_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_0.u32));
    VPSS_FMTC_CSC_COEF_0.bits.csc_coef_01 = csc_coef_01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_0.u32), VPSS_FMTC_CSC_COEF_0.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscCoef00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_00)
{
    U_VPSS_FMTC_CSC_COEF_0 VPSS_FMTC_CSC_COEF_0;

    VPSS_FMTC_CSC_COEF_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_0.u32));
    VPSS_FMTC_CSC_COEF_0.bits.csc_coef_00 = csc_coef_00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_0.u32), VPSS_FMTC_CSC_COEF_0.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscCoef10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_10)
{
    U_VPSS_FMTC_CSC_COEF_1 VPSS_FMTC_CSC_COEF_1;

    VPSS_FMTC_CSC_COEF_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_1.u32));
    VPSS_FMTC_CSC_COEF_1.bits.csc_coef_10 = csc_coef_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_1.u32), VPSS_FMTC_CSC_COEF_1.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscCoef02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_02)
{
    U_VPSS_FMTC_CSC_COEF_1 VPSS_FMTC_CSC_COEF_1;

    VPSS_FMTC_CSC_COEF_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_1.u32));
    VPSS_FMTC_CSC_COEF_1.bits.csc_coef_02 = csc_coef_02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_1.u32), VPSS_FMTC_CSC_COEF_1.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscCoef12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_12)
{
    U_VPSS_FMTC_CSC_COEF_2 VPSS_FMTC_CSC_COEF_2;

    VPSS_FMTC_CSC_COEF_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_2.u32));
    VPSS_FMTC_CSC_COEF_2.bits.csc_coef_12 = csc_coef_12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_2.u32), VPSS_FMTC_CSC_COEF_2.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscCoef11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_11)
{
    U_VPSS_FMTC_CSC_COEF_2 VPSS_FMTC_CSC_COEF_2;

    VPSS_FMTC_CSC_COEF_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_2.u32));
    VPSS_FMTC_CSC_COEF_2.bits.csc_coef_11 = csc_coef_11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_2.u32), VPSS_FMTC_CSC_COEF_2.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscCoef21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_21)
{
    U_VPSS_FMTC_CSC_COEF_3 VPSS_FMTC_CSC_COEF_3;

    VPSS_FMTC_CSC_COEF_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_3.u32));
    VPSS_FMTC_CSC_COEF_3.bits.csc_coef_21 = csc_coef_21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_3.u32), VPSS_FMTC_CSC_COEF_3.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscCoef20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_20)
{
    U_VPSS_FMTC_CSC_COEF_3 VPSS_FMTC_CSC_COEF_3;

    VPSS_FMTC_CSC_COEF_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_3.u32));
    VPSS_FMTC_CSC_COEF_3.bits.csc_coef_20 = csc_coef_20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_3.u32), VPSS_FMTC_CSC_COEF_3.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscCoef22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_coef_22)
{
    U_VPSS_FMTC_CSC_COEF_4 VPSS_FMTC_CSC_COEF_4;

    VPSS_FMTC_CSC_COEF_4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_4.u32));
    VPSS_FMTC_CSC_COEF_4.bits.csc_coef_22 = csc_coef_22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_4.u32), VPSS_FMTC_CSC_COEF_4.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscInDc1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_in_dc1)
{
    U_VPSS_FMTC_CSC_COEF_5 VPSS_FMTC_CSC_COEF_5;

    VPSS_FMTC_CSC_COEF_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_5.u32));
    VPSS_FMTC_CSC_COEF_5.bits.csc_in_dc1 = csc_in_dc1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_5.u32), VPSS_FMTC_CSC_COEF_5.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscInDc0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_in_dc0)
{
    U_VPSS_FMTC_CSC_COEF_5 VPSS_FMTC_CSC_COEF_5;

    VPSS_FMTC_CSC_COEF_5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_5.u32));
    VPSS_FMTC_CSC_COEF_5.bits.csc_in_dc0 = csc_in_dc0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_5.u32), VPSS_FMTC_CSC_COEF_5.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscOutDc0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_out_dc0)
{
    U_VPSS_FMTC_CSC_COEF_6 VPSS_FMTC_CSC_COEF_6;

    VPSS_FMTC_CSC_COEF_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_6.u32));
    VPSS_FMTC_CSC_COEF_6.bits.csc_out_dc0 = csc_out_dc0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_6.u32), VPSS_FMTC_CSC_COEF_6.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscInDc2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_in_dc2)
{
    U_VPSS_FMTC_CSC_COEF_6 VPSS_FMTC_CSC_COEF_6;

    VPSS_FMTC_CSC_COEF_6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_6.u32));
    VPSS_FMTC_CSC_COEF_6.bits.csc_in_dc2 = csc_in_dc2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_6.u32), VPSS_FMTC_CSC_COEF_6.u32);

    return ;
}



HI_VOID VPSS_Csc_SetCscOutDc2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_out_dc2)
{
    U_VPSS_FMTC_CSC_COEF_7 VPSS_FMTC_CSC_COEF_7;

    VPSS_FMTC_CSC_COEF_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_7.u32));
    VPSS_FMTC_CSC_COEF_7.bits.csc_out_dc2 = csc_out_dc2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_7.u32), VPSS_FMTC_CSC_COEF_7.u32);

    return ;
}


HI_VOID VPSS_Csc_SetCscOutDc1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csc_out_dc1)
{
    U_VPSS_FMTC_CSC_COEF_7 VPSS_FMTC_CSC_COEF_7;

    VPSS_FMTC_CSC_COEF_7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_7.u32));
    VPSS_FMTC_CSC_COEF_7.bits.csc_out_dc1 = csc_out_dc1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_FMTC_CSC_COEF_7.u32), VPSS_FMTC_CSC_COEF_7.u32);

    return ;
}


//module_name : CSC



