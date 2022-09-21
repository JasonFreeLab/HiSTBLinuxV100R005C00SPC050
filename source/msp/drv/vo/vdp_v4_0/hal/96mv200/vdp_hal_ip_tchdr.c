
#include "vdp_hal_ip_tchdr.h"
#include "vdp_hal_comm.h"
#include "vdp_define.h"

extern S_VDP_REGS_TYPE *pVdpReg;


HI_VOID VDP_TCHDR_SetTchdrDemoPos(HI_U32 tchdr_demo_pos)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_demo_pos = tchdr_demo_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDemoMode(HI_U32 tchdr_demo_mode)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_demo_mode = tchdr_demo_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDemoEn(HI_U32 tchdr_demo_en)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_demo_en = tchdr_demo_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrCkGtEn(HI_U32 tchdr_ck_gt_en)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_ck_gt_en = tchdr_ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrCertEn(HI_U32 tchdr_cert_en)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_cert_en = tchdr_cert_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrEn(HI_U32 tchdr_en)
{
	U_TCHDR_CTRL TCHDR_CTRL;

	TCHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32));
	TCHDR_CTRL.bits.tchdr_en = tchdr_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_CTRL.u32),TCHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yClipEn(HI_U32 tchdr_r2y_clip_en)
{
	U_TCHDR_ALG_CTRL TCHDR_ALG_CTRL;

	TCHDR_ALG_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_ALG_CTRL.u32));
	TCHDR_ALG_CTRL.bits.tchdr_r2y_clip_en = tchdr_r2y_clip_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_ALG_CTRL.u32),TCHDR_ALG_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrYuvRange(HI_U32 tchdr_yuv_range)
{
	U_TCHDR_ALG_CTRL TCHDR_ALG_CTRL;

	TCHDR_ALG_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_ALG_CTRL.u32));
	TCHDR_ALG_CTRL.bits.tchdr_yuv_range = tchdr_yuv_range;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_ALG_CTRL.u32),TCHDR_ALG_CTRL.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrAlphaB(HI_U32 tchdr_alpha_b)
{
	U_TCHDR_ALPHA TCHDR_ALPHA;

	TCHDR_ALPHA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_ALPHA.u32));
	TCHDR_ALPHA.bits.tchdr_alpha_b = tchdr_alpha_b;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_ALPHA.u32),TCHDR_ALPHA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrAlphaA(HI_U32 tchdr_alpha_a)
{
	U_TCHDR_ALPHA TCHDR_ALPHA;

	TCHDR_ALPHA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_ALPHA.u32));
	TCHDR_ALPHA.bits.tchdr_alpha_a = tchdr_alpha_a;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_ALPHA.u32),TCHDR_ALPHA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct2(HI_U32 tchdr_oct2)
{
	U_TCHDR_OCT0 TCHDR_OCT0;

	TCHDR_OCT0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32));
	TCHDR_OCT0.bits.tchdr_oct2 = tchdr_oct2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32),TCHDR_OCT0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct1(HI_U32 tchdr_oct1)
{
	U_TCHDR_OCT0 TCHDR_OCT0;

	TCHDR_OCT0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32));
	TCHDR_OCT0.bits.tchdr_oct1 = tchdr_oct1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32),TCHDR_OCT0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct0(HI_U32 tchdr_oct0)
{
	U_TCHDR_OCT0 TCHDR_OCT0;

	TCHDR_OCT0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32));
	TCHDR_OCT0.bits.tchdr_oct0 = tchdr_oct0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT0.u32),TCHDR_OCT0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct5(HI_U32 tchdr_oct5)
{
	U_TCHDR_OCT1 TCHDR_OCT1;

	TCHDR_OCT1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32));
	TCHDR_OCT1.bits.tchdr_oct5 = tchdr_oct5;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32),TCHDR_OCT1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct4(HI_U32 tchdr_oct4)
{
	U_TCHDR_OCT1 TCHDR_OCT1;

	TCHDR_OCT1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32));
	TCHDR_OCT1.bits.tchdr_oct4 = tchdr_oct4;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32),TCHDR_OCT1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct3(HI_U32 tchdr_oct3)
{
	U_TCHDR_OCT1 TCHDR_OCT1;

	TCHDR_OCT1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32));
	TCHDR_OCT1.bits.tchdr_oct3 = tchdr_oct3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT1.u32),TCHDR_OCT1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrOct6(HI_U32 tchdr_oct6)
{
	U_TCHDR_OCT2 TCHDR_OCT2;

	TCHDR_OCT2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_OCT2.u32));
	TCHDR_OCT2.bits.tchdr_oct6 = tchdr_oct6;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_OCT2.u32),TCHDR_OCT2.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutStep3(HI_U32 tchdr_d_lut_step3)
{
	U_TCHDR_D_LUT_STEP TCHDR_D_LUT_STEP;

	TCHDR_D_LUT_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32));
	TCHDR_D_LUT_STEP.bits.tchdr_d_lut_step3 = tchdr_d_lut_step3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32),TCHDR_D_LUT_STEP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutStep2(HI_U32 tchdr_d_lut_step2)
{
	U_TCHDR_D_LUT_STEP TCHDR_D_LUT_STEP;

	TCHDR_D_LUT_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32));
	TCHDR_D_LUT_STEP.bits.tchdr_d_lut_step2 = tchdr_d_lut_step2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32),TCHDR_D_LUT_STEP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutStep1(HI_U32 tchdr_d_lut_step1)
{
	U_TCHDR_D_LUT_STEP TCHDR_D_LUT_STEP;

	TCHDR_D_LUT_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32));
	TCHDR_D_LUT_STEP.bits.tchdr_d_lut_step1 = tchdr_d_lut_step1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32),TCHDR_D_LUT_STEP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutStep0(HI_U32 tchdr_d_lut_step0)
{
	U_TCHDR_D_LUT_STEP TCHDR_D_LUT_STEP;

	TCHDR_D_LUT_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32));
	TCHDR_D_LUT_STEP.bits.tchdr_d_lut_step0 = tchdr_d_lut_step0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_STEP.u32),TCHDR_D_LUT_STEP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutThr1(HI_U32 tchdr_d_lut_thr1)
{
	U_TCHDR_D_LUT_THR0 TCHDR_D_LUT_THR0;

	TCHDR_D_LUT_THR0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR0.u32));
	TCHDR_D_LUT_THR0.bits.tchdr_d_lut_thr1 = tchdr_d_lut_thr1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR0.u32),TCHDR_D_LUT_THR0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutThr0(HI_U32 tchdr_d_lut_thr0)
{
	U_TCHDR_D_LUT_THR0 TCHDR_D_LUT_THR0;

	TCHDR_D_LUT_THR0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR0.u32));
	TCHDR_D_LUT_THR0.bits.tchdr_d_lut_thr0 = tchdr_d_lut_thr0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR0.u32),TCHDR_D_LUT_THR0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrDLutThr2(HI_U32 tchdr_d_lut_thr2)
{
	U_TCHDR_D_LUT_THR1 TCHDR_D_LUT_THR1;

	TCHDR_D_LUT_THR1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR1.u32));
	TCHDR_D_LUT_THR1.bits.tchdr_d_lut_thr2 = tchdr_d_lut_thr2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_D_LUT_THR1.u32),TCHDR_D_LUT_THR1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaCAddr(HI_U32 tchdr_para_c_addr)
{
	U_TCHDR_PARA_C_ADDR TCHDR_PARA_C_ADDR;

	TCHDR_PARA_C_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_C_ADDR.u32));
	TCHDR_PARA_C_ADDR.bits.tchdr_para_c_addr = tchdr_para_c_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_C_ADDR.u32),TCHDR_PARA_C_ADDR.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaPAddr(HI_U32 tchdr_para_p_addr)
{
	U_TCHDR_PARA_P_ADDR TCHDR_PARA_P_ADDR;

	TCHDR_PARA_P_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_P_ADDR.u32));
	TCHDR_PARA_P_ADDR.bits.tchdr_para_p_addr = tchdr_para_p_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_P_ADDR.u32),TCHDR_PARA_P_ADDR.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaSAddr(HI_U32 tchdr_para_s_addr)
{
	U_TCHDR_PARA_S_ADDR TCHDR_PARA_S_ADDR;

	TCHDR_PARA_S_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_S_ADDR.u32));
	TCHDR_PARA_S_ADDR.bits.tchdr_para_s_addr = tchdr_para_s_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_S_ADDR.u32),TCHDR_PARA_S_ADDR.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaIAddr(HI_U32 tchdr_para_i_addr)
{
	U_TCHDR_PARA_I_ADDR TCHDR_PARA_I_ADDR;

	TCHDR_PARA_I_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_I_ADDR.u32));
	TCHDR_PARA_I_ADDR.bits.tchdr_para_i_addr = tchdr_para_i_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_I_ADDR.u32),TCHDR_PARA_I_ADDR.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaDAddr(HI_U32 tchdr_para_d_addr)
{
	U_TCHDR_PARA_D_ADDR TCHDR_PARA_D_ADDR;

	TCHDR_PARA_D_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_D_ADDR.u32));
	TCHDR_PARA_D_ADDR.bits.tchdr_para_d_addr = tchdr_para_d_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_D_ADDR.u32),TCHDR_PARA_D_ADDR.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaDUpd(HI_U32 tchdr_para_d_upd)
{
	U_TCHDR_PARA_UP TCHDR_PARA_UP;

	TCHDR_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32));
	TCHDR_PARA_UP.bits.tchdr_para_d_upd = tchdr_para_d_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32),TCHDR_PARA_UP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaIUpd(HI_U32 tchdr_para_i_upd)
{
	U_TCHDR_PARA_UP TCHDR_PARA_UP;

	TCHDR_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32));
	TCHDR_PARA_UP.bits.tchdr_para_i_upd = tchdr_para_i_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32),TCHDR_PARA_UP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaSUpd(HI_U32 tchdr_para_s_upd)
{
	U_TCHDR_PARA_UP TCHDR_PARA_UP;

	TCHDR_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32));
	TCHDR_PARA_UP.bits.tchdr_para_s_upd = tchdr_para_s_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32),TCHDR_PARA_UP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaPUpd(HI_U32 tchdr_para_p_upd)
{
	U_TCHDR_PARA_UP TCHDR_PARA_UP;

	TCHDR_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32));
	TCHDR_PARA_UP.bits.tchdr_para_p_upd = tchdr_para_p_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32),TCHDR_PARA_UP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaCUpd(HI_U32 tchdr_para_c_upd)
{
	U_TCHDR_PARA_UP TCHDR_PARA_UP;

	TCHDR_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32));
	TCHDR_PARA_UP.bits.tchdr_para_c_upd = tchdr_para_c_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_UP.u32),TCHDR_PARA_UP.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaDRdEn(HI_U32 tchdr_para_d_rd_en)
{
	U_TCHDR_PARA_REN TCHDR_PARA_REN;

	TCHDR_PARA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32));
	TCHDR_PARA_REN.bits.tchdr_para_d_rd_en = tchdr_para_d_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32),TCHDR_PARA_REN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaIRdEn(HI_U32 tchdr_para_i_rd_en)
{
	U_TCHDR_PARA_REN TCHDR_PARA_REN;

	TCHDR_PARA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32));
	TCHDR_PARA_REN.bits.tchdr_para_i_rd_en = tchdr_para_i_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32),TCHDR_PARA_REN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaSRdEn(HI_U32 tchdr_para_s_rd_en)
{
	U_TCHDR_PARA_REN TCHDR_PARA_REN;

	TCHDR_PARA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32));
	TCHDR_PARA_REN.bits.tchdr_para_s_rd_en = tchdr_para_s_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32),TCHDR_PARA_REN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaPRdEn(HI_U32 tchdr_para_p_rd_en)
{
	U_TCHDR_PARA_REN TCHDR_PARA_REN;

	TCHDR_PARA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32));
	TCHDR_PARA_REN.bits.tchdr_para_p_rd_en = tchdr_para_p_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32),TCHDR_PARA_REN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaCRdEn(HI_U32 tchdr_para_c_rd_en)
{
	U_TCHDR_PARA_REN TCHDR_PARA_REN;

	TCHDR_PARA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32));
	TCHDR_PARA_REN.bits.tchdr_para_c_rd_en = tchdr_para_c_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_REN.u32),TCHDR_PARA_REN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaCData(HI_U32 tchdr_para_c_data)
{
	U_TCHDR_PARA_C_DATA TCHDR_PARA_C_DATA;

	TCHDR_PARA_C_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_C_DATA.u32));
	TCHDR_PARA_C_DATA.bits.tchdr_para_c_data = tchdr_para_c_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_C_DATA.u32),TCHDR_PARA_C_DATA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaPData(HI_U32 tchdr_para_p_data)
{
	U_TCHDR_PARA_P_DATA TCHDR_PARA_P_DATA;

	TCHDR_PARA_P_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_P_DATA.u32));
	TCHDR_PARA_P_DATA.bits.tchdr_para_p_data = tchdr_para_p_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_P_DATA.u32),TCHDR_PARA_P_DATA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaSData(HI_U32 tchdr_para_s_data)
{
	U_TCHDR_PARA_S_DATA TCHDR_PARA_S_DATA;

	TCHDR_PARA_S_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_S_DATA.u32));
	TCHDR_PARA_S_DATA.bits.tchdr_para_s_data = tchdr_para_s_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_S_DATA.u32),TCHDR_PARA_S_DATA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaIData(HI_U32 tchdr_para_i_data)
{
	U_TCHDR_PARA_I_DATA TCHDR_PARA_I_DATA;

	TCHDR_PARA_I_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_I_DATA.u32));
	TCHDR_PARA_I_DATA.bits.tchdr_para_i_data = tchdr_para_i_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_I_DATA.u32),TCHDR_PARA_I_DATA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrParaDData(HI_U32 tchdr_para_d_data)
{
	U_TCHDR_PARA_D_DATA TCHDR_PARA_D_DATA;

	TCHDR_PARA_D_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_PARA_D_DATA.u32));
	TCHDR_PARA_D_DATA.bits.tchdr_para_d_data = tchdr_para_d_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_PARA_D_DATA.u32),TCHDR_PARA_D_DATA.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef1(HI_U32 tchdr_r2y_coef1)
{
	U_TCHDR_R2Y_COEF0 TCHDR_R2Y_COEF0;

	TCHDR_R2Y_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF0.u32));
	TCHDR_R2Y_COEF0.bits.tchdr_r2y_coef1 = tchdr_r2y_coef1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF0.u32),TCHDR_R2Y_COEF0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef0(HI_U32 tchdr_r2y_coef0)
{
	U_TCHDR_R2Y_COEF0 TCHDR_R2Y_COEF0;

	TCHDR_R2Y_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF0.u32));
	TCHDR_R2Y_COEF0.bits.tchdr_r2y_coef0 = tchdr_r2y_coef0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF0.u32),TCHDR_R2Y_COEF0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef3(HI_U32 tchdr_r2y_coef3)
{
	U_TCHDR_R2Y_COEF1 TCHDR_R2Y_COEF1;

	TCHDR_R2Y_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF1.u32));
	TCHDR_R2Y_COEF1.bits.tchdr_r2y_coef3 = tchdr_r2y_coef3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF1.u32),TCHDR_R2Y_COEF1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef2(HI_U32 tchdr_r2y_coef2)
{
	U_TCHDR_R2Y_COEF1 TCHDR_R2Y_COEF1;

	TCHDR_R2Y_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF1.u32));
	TCHDR_R2Y_COEF1.bits.tchdr_r2y_coef2 = tchdr_r2y_coef2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF1.u32),TCHDR_R2Y_COEF1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef5(HI_U32 tchdr_r2y_coef5)
{
	U_TCHDR_R2Y_COEF2 TCHDR_R2Y_COEF2;

	TCHDR_R2Y_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF2.u32));
	TCHDR_R2Y_COEF2.bits.tchdr_r2y_coef5 = tchdr_r2y_coef5;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF2.u32),TCHDR_R2Y_COEF2.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef4(HI_U32 tchdr_r2y_coef4)
{
	U_TCHDR_R2Y_COEF2 TCHDR_R2Y_COEF2;

	TCHDR_R2Y_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF2.u32));
	TCHDR_R2Y_COEF2.bits.tchdr_r2y_coef4 = tchdr_r2y_coef4;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF2.u32),TCHDR_R2Y_COEF2.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef7(HI_U32 tchdr_r2y_coef7)
{
	U_TCHDR_R2Y_COEF3 TCHDR_R2Y_COEF3;

	TCHDR_R2Y_COEF3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF3.u32));
	TCHDR_R2Y_COEF3.bits.tchdr_r2y_coef7 = tchdr_r2y_coef7;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF3.u32),TCHDR_R2Y_COEF3.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef6(HI_U32 tchdr_r2y_coef6)
{
	U_TCHDR_R2Y_COEF3 TCHDR_R2Y_COEF3;

	TCHDR_R2Y_COEF3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF3.u32));
	TCHDR_R2Y_COEF3.bits.tchdr_r2y_coef6 = tchdr_r2y_coef6;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF3.u32),TCHDR_R2Y_COEF3.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yCoef8(HI_U32 tchdr_r2y_coef8)
{
	U_TCHDR_R2Y_COEF4 TCHDR_R2Y_COEF4;

	TCHDR_R2Y_COEF4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF4.u32));
	TCHDR_R2Y_COEF4.bits.tchdr_r2y_coef8 = tchdr_r2y_coef8;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_COEF4.u32),TCHDR_R2Y_COEF4.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yScale2p(HI_U32 tchdr_r2y_scale2p)
{
	U_TCHDR_R2Y_SCALE2P TCHDR_R2Y_SCALE2P;

	TCHDR_R2Y_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_SCALE2P.u32));
	TCHDR_R2Y_SCALE2P.bits.tchdr_r2y_scale2p = tchdr_r2y_scale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_SCALE2P.u32),TCHDR_R2Y_SCALE2P.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yOutDc0(HI_U32 tchdr_r2y_out_dc0)
{
	U_TCHDR_R2Y_OUT_DC0 TCHDR_R2Y_OUT_DC0;

	TCHDR_R2Y_OUT_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC0.u32));
	TCHDR_R2Y_OUT_DC0.bits.tchdr_r2y_out_dc0 = tchdr_r2y_out_dc0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC0.u32),TCHDR_R2Y_OUT_DC0.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yOutDc1(HI_U32 tchdr_r2y_out_dc1)
{
	U_TCHDR_R2Y_OUT_DC1 TCHDR_R2Y_OUT_DC1;

	TCHDR_R2Y_OUT_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC1.u32));
	TCHDR_R2Y_OUT_DC1.bits.tchdr_r2y_out_dc1 = tchdr_r2y_out_dc1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC1.u32),TCHDR_R2Y_OUT_DC1.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yOutDc2(HI_U32 tchdr_r2y_out_dc2)
{
	U_TCHDR_R2Y_OUT_DC2 TCHDR_R2Y_OUT_DC2;

	TCHDR_R2Y_OUT_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC2.u32));
	TCHDR_R2Y_OUT_DC2.bits.tchdr_r2y_out_dc2 = tchdr_r2y_out_dc2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_OUT_DC2.u32),TCHDR_R2Y_OUT_DC2.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yClipMin(HI_U32 tchdr_r2y_clip_min)
{
	U_TCHDR_R2Y_MIN TCHDR_R2Y_MIN;

	TCHDR_R2Y_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_MIN.u32));
	TCHDR_R2Y_MIN.bits.tchdr_r2y_clip_min = tchdr_r2y_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_MIN.u32),TCHDR_R2Y_MIN.u32);

	return ;
}


HI_VOID VDP_TCHDR_SetTchdrR2yClipMax(HI_U32 tchdr_r2y_clip_max)
{
	U_TCHDR_R2Y_MAX TCHDR_R2Y_MAX;

	TCHDR_R2Y_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->TCHDR_R2Y_MAX.u32));
	TCHDR_R2Y_MAX.bits.tchdr_r2y_clip_max = tchdr_r2y_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->TCHDR_R2Y_MAX.u32),TCHDR_R2Y_MAX.u32);

	return ;
}

//layer_name  : VDP
//module_name : tchdr





