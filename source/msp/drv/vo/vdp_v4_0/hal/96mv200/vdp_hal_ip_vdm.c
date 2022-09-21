
#include "vdp_hal_ip_vdm.h"
#include "vdp_hal_comm.h"
#include "vdp_define.h"


extern S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_HIHDR_SetVdmCkGtEn(HI_U32 vdm_ck_gt_en)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_ck_gt_en = vdm_ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapInBdp(HI_U32 vdm_tmap_in_bdp)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_tmap_in_bdp = vdm_tmap_in_bdp;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCscBind(HI_U32 vdm_csc_bind)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_csc_bind = vdm_csc_bind;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmGmmEn(HI_U32 vdm_gmm_en)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_gmm_en = vdm_gmm_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapEn(HI_U32 vdm_tmap_en)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_tmap_en = vdm_tmap_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDegmmEn(HI_U32 vdm_degmm_en)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_degmm_en = vdm_degmm_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmEn(HI_U32 vdm_en)
{
	U_VDM_CTRL VDM_CTRL;

	VDM_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CTRL.u32));
	VDM_CTRL.bits.vdm_en = vdm_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CTRL.u32),VDM_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmLumaCoef0Tmap(HI_U32 vdm_luma_coef0_tmap)
{
	U_VDM_TMAP_LUMA_COEF0 VDM_TMAP_LUMA_COEF0;

	VDM_TMAP_LUMA_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF0.u32));
	VDM_TMAP_LUMA_COEF0.bits.vdm_luma_coef0_tmap = vdm_luma_coef0_tmap;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF0.u32),VDM_TMAP_LUMA_COEF0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmLumaCoef1Tmap(HI_U32 vdm_luma_coef1_tmap)
{
	U_VDM_TMAP_LUMA_COEF1 VDM_TMAP_LUMA_COEF1;

	VDM_TMAP_LUMA_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF1.u32));
	VDM_TMAP_LUMA_COEF1.bits.vdm_luma_coef1_tmap = vdm_luma_coef1_tmap;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF1.u32),VDM_TMAP_LUMA_COEF1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmLumaCoef2Tmap(HI_U32 vdm_luma_coef2_tmap)
{
	U_VDM_TMAP_LUMA_COEF2 VDM_TMAP_LUMA_COEF2;

	VDM_TMAP_LUMA_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF2.u32));
	VDM_TMAP_LUMA_COEF2.bits.vdm_luma_coef2_tmap = vdm_luma_coef2_tmap;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_COEF2.u32),VDM_TMAP_LUMA_COEF2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapLumaScale(HI_U32 vdm_tmap_luma_scale)
{
	U_VDM_TMAP_LUMA_SCALE VDM_TMAP_LUMA_SCALE;

	VDM_TMAP_LUMA_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_SCALE.u32));
	VDM_TMAP_LUMA_SCALE.bits.vdm_tmap_luma_scale = vdm_tmap_luma_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_LUMA_SCALE.u32),VDM_TMAP_LUMA_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapCoefScale(HI_U32 vdm_tmap_coef_scale)
{
	U_VDM_TMAP_COEF_SCALE VDM_TMAP_COEF_SCALE;

	VDM_TMAP_COEF_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_COEF_SCALE.u32));
	VDM_TMAP_COEF_SCALE.bits.vdm_tmap_coef_scale = vdm_tmap_coef_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_COEF_SCALE.u32),VDM_TMAP_COEF_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapOutClipMin(HI_U32 vdm_tmap_out_clip_min)
{
	U_VDM_TMAP_OUT_CLIP_MIN VDM_TMAP_OUT_CLIP_MIN;

	VDM_TMAP_OUT_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_CLIP_MIN.u32));
	VDM_TMAP_OUT_CLIP_MIN.bits.vdm_tmap_out_clip_min = vdm_tmap_out_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_CLIP_MIN.u32),VDM_TMAP_OUT_CLIP_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapOutClipMax(HI_U32 vdm_tmap_out_clip_max)
{
	U_VDM_TMAP_OUT_CLIP_MAX VDM_TMAP_OUT_CLIP_MAX;

	VDM_TMAP_OUT_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_CLIP_MAX.u32));
	VDM_TMAP_OUT_CLIP_MAX.bits.vdm_tmap_out_clip_max = vdm_tmap_out_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_CLIP_MAX.u32),VDM_TMAP_OUT_CLIP_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaDegmmAddr(HI_U32 vdm_para_degmm_addr)
{
	U_VDM_PARA_DEGMM_ADDR VDM_PARA_DEGMM_ADDR;

	VDM_PARA_DEGMM_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_DEGMM_ADDR.u32));
	VDM_PARA_DEGMM_ADDR.bits.vdm_para_degmm_addr = vdm_para_degmm_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_DEGMM_ADDR.u32),VDM_PARA_DEGMM_ADDR.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaGmmAddr(HI_U32 vdm_para_gmm_addr)
{
	U_VDM_PARA_GMM_ADDR VDM_PARA_GMM_ADDR;

	VDM_PARA_GMM_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_GMM_ADDR.u32));
	VDM_PARA_GMM_ADDR.bits.vdm_para_gmm_addr = vdm_para_gmm_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_GMM_ADDR.u32),VDM_PARA_GMM_ADDR.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaTmapAddr(HI_U32 vdm_para_tmap_addr)
{
	U_VDM_PARA_TMAP_ADDR VDM_PARA_TMAP_ADDR;

	VDM_PARA_TMAP_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_TMAP_ADDR.u32));
	VDM_PARA_TMAP_ADDR.bits.vdm_para_tmap_addr = vdm_para_tmap_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_TMAP_ADDR.u32),VDM_PARA_TMAP_ADDR.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaSmAddr(HI_U32 vdm_para_sm_addr)
{
	U_VDM_PARA_SM_ADDR VDM_PARA_SM_ADDR;

	VDM_PARA_SM_ADDR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_SM_ADDR.u32));
	VDM_PARA_SM_ADDR.bits.vdm_para_sm_addr = vdm_para_sm_addr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_SM_ADDR.u32),VDM_PARA_SM_ADDR.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaSmUpd(HI_U32 vdm_para_sm_upd)
{
	U_VDM_PARA_UP VDM_PARA_UP;

	VDM_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32));
	VDM_PARA_UP.bits.vdm_para_sm_upd = vdm_para_sm_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32),VDM_PARA_UP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaTmapUpd(HI_U32 vdm_para_tmap_upd)
{
	U_VDM_PARA_UP VDM_PARA_UP;

	VDM_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32));
	VDM_PARA_UP.bits.vdm_para_tmap_upd = vdm_para_tmap_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32),VDM_PARA_UP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaGmmUpd(HI_U32 vdm_para_gmm_upd)
{
	U_VDM_PARA_UP VDM_PARA_UP;

	VDM_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32));
	VDM_PARA_UP.bits.vdm_para_gmm_upd = vdm_para_gmm_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32),VDM_PARA_UP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmParaDegmmUpd(HI_U32 vdm_para_degmm_upd)
{
	U_VDM_PARA_UP VDM_PARA_UP;

	VDM_PARA_UP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32));
	VDM_PARA_UP.bits.vdm_para_degmm_upd = vdm_para_degmm_upd;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_PARA_UP.u32),VDM_PARA_UP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapOutDc0(HI_U32 vdm_tmap_out_dc0)
{
	U_VDM_TMAP_OUT_DC0 VDM_TMAP_OUT_DC0;

	VDM_TMAP_OUT_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC0.u32));
	VDM_TMAP_OUT_DC0.bits.vdm_tmap_out_dc0 = vdm_tmap_out_dc0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC0.u32),VDM_TMAP_OUT_DC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapOutDc1(HI_U32 vdm_tmap_out_dc1)
{
	U_VDM_TMAP_OUT_DC1 VDM_TMAP_OUT_DC1;

	VDM_TMAP_OUT_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC1.u32));
	VDM_TMAP_OUT_DC1.bits.vdm_tmap_out_dc1 = vdm_tmap_out_dc1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC1.u32),VDM_TMAP_OUT_DC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapOutDc2(HI_U32 vdm_tmap_out_dc2)
{
	U_VDM_TMAP_OUT_DC2 VDM_TMAP_OUT_DC2;

	VDM_TMAP_OUT_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC2.u32));
	VDM_TMAP_OUT_DC2.bits.vdm_tmap_out_dc2 = vdm_tmap_out_dc2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TMAP_OUT_DC2.u32),VDM_TMAP_OUT_DC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDegammaRdEn(HI_U32 vdm_degamma_rd_en)
{
	U_VDM_DEGMM_REN VDM_DEGMM_REN;

	VDM_DEGMM_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGMM_REN.u32));
	VDM_DEGMM_REN.bits.vdm_degamma_rd_en = vdm_degamma_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGMM_REN.u32),VDM_DEGMM_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDegammaParaData(HI_U32 vdm_degamma_para_data)
{
	U_VDM_DEGMM_DATA VDM_DEGMM_DATA;

	VDM_DEGMM_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGMM_DATA.u32));
	VDM_DEGMM_DATA.bits.vdm_degamma_para_data = vdm_degamma_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGMM_DATA.u32),VDM_DEGMM_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX4Step(HI_U32 v_degmm_x4_step)
{
	U_VDM_DEGAMMA_STEP VDM_DEGAMMA_STEP;

	VDM_DEGAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32));
	VDM_DEGAMMA_STEP.bits.v_degmm_x4_step = v_degmm_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32),VDM_DEGAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX3Step(HI_U32 v_degmm_x3_step)
{
	U_VDM_DEGAMMA_STEP VDM_DEGAMMA_STEP;

	VDM_DEGAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32));
	VDM_DEGAMMA_STEP.bits.v_degmm_x3_step = v_degmm_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32),VDM_DEGAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX2Step(HI_U32 v_degmm_x2_step)
{
	U_VDM_DEGAMMA_STEP VDM_DEGAMMA_STEP;

	VDM_DEGAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32));
	VDM_DEGAMMA_STEP.bits.v_degmm_x2_step = v_degmm_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32),VDM_DEGAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX1Step(HI_U32 v_degmm_x1_step)
{
	U_VDM_DEGAMMA_STEP VDM_DEGAMMA_STEP;

	VDM_DEGAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32));
	VDM_DEGAMMA_STEP.bits.v_degmm_x1_step = v_degmm_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP.u32),VDM_DEGAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX8Step(HI_U32 v_degmm_x8_step)
{
	U_VDM_DEGAMMA_STEP2 VDM_DEGAMMA_STEP2;

	VDM_DEGAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32));
	VDM_DEGAMMA_STEP2.bits.v_degmm_x8_step = v_degmm_x8_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32),VDM_DEGAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX7Step(HI_U32 v_degmm_x7_step)
{
	U_VDM_DEGAMMA_STEP2 VDM_DEGAMMA_STEP2;

	VDM_DEGAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32));
	VDM_DEGAMMA_STEP2.bits.v_degmm_x7_step = v_degmm_x7_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32),VDM_DEGAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX6Step(HI_U32 v_degmm_x6_step)
{
	U_VDM_DEGAMMA_STEP2 VDM_DEGAMMA_STEP2;

	VDM_DEGAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32));
	VDM_DEGAMMA_STEP2.bits.v_degmm_x6_step = v_degmm_x6_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32),VDM_DEGAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX5Step(HI_U32 v_degmm_x5_step)
{
	U_VDM_DEGAMMA_STEP2 VDM_DEGAMMA_STEP2;

	VDM_DEGAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32));
	VDM_DEGAMMA_STEP2.bits.v_degmm_x5_step = v_degmm_x5_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_STEP2.u32),VDM_DEGAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX2Pos(HI_U32 v_degmm_x2_pos)
{
	U_VDM_DEGAMMA_POS0 VDM_DEGAMMA_POS0;

	VDM_DEGAMMA_POS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS0.u32));
	VDM_DEGAMMA_POS0.bits.v_degmm_x2_pos = v_degmm_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS0.u32),VDM_DEGAMMA_POS0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX1Pos(HI_U32 v_degmm_x1_pos)
{
	U_VDM_DEGAMMA_POS0 VDM_DEGAMMA_POS0;

	VDM_DEGAMMA_POS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS0.u32));
	VDM_DEGAMMA_POS0.bits.v_degmm_x1_pos = v_degmm_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS0.u32),VDM_DEGAMMA_POS0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX4Pos(HI_U32 v_degmm_x4_pos)
{
	U_VDM_DEGAMMA_POS1 VDM_DEGAMMA_POS1;

	VDM_DEGAMMA_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS1.u32));
	VDM_DEGAMMA_POS1.bits.v_degmm_x4_pos = v_degmm_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS1.u32),VDM_DEGAMMA_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX3Pos(HI_U32 v_degmm_x3_pos)
{
	U_VDM_DEGAMMA_POS1 VDM_DEGAMMA_POS1;

	VDM_DEGAMMA_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS1.u32));
	VDM_DEGAMMA_POS1.bits.v_degmm_x3_pos = v_degmm_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS1.u32),VDM_DEGAMMA_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX6Pos(HI_U32 v_degmm_x6_pos)
{
	U_VDM_DEGAMMA_POS2 VDM_DEGAMMA_POS2;

	VDM_DEGAMMA_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS2.u32));
	VDM_DEGAMMA_POS2.bits.v_degmm_x6_pos = v_degmm_x6_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS2.u32),VDM_DEGAMMA_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX5Pos(HI_U32 v_degmm_x5_pos)
{
	U_VDM_DEGAMMA_POS2 VDM_DEGAMMA_POS2;

	VDM_DEGAMMA_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS2.u32));
	VDM_DEGAMMA_POS2.bits.v_degmm_x5_pos = v_degmm_x5_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS2.u32),VDM_DEGAMMA_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX8Pos(HI_U32 v_degmm_x8_pos)
{
	U_VDM_DEGAMMA_POS3 VDM_DEGAMMA_POS3;

	VDM_DEGAMMA_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS3.u32));
	VDM_DEGAMMA_POS3.bits.v_degmm_x8_pos = v_degmm_x8_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS3.u32),VDM_DEGAMMA_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX7Pos(HI_U32 v_degmm_x7_pos)
{
	U_VDM_DEGAMMA_POS3 VDM_DEGAMMA_POS3;

	VDM_DEGAMMA_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS3.u32));
	VDM_DEGAMMA_POS3.bits.v_degmm_x7_pos = v_degmm_x7_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_POS3.u32),VDM_DEGAMMA_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX4Num(HI_U32 v_degmm_x4_num)
{
	U_VDM_DEGAMMA_NUM VDM_DEGAMMA_NUM;

	VDM_DEGAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32));
	VDM_DEGAMMA_NUM.bits.v_degmm_x4_num = v_degmm_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32),VDM_DEGAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX3Num(HI_U32 v_degmm_x3_num)
{
	U_VDM_DEGAMMA_NUM VDM_DEGAMMA_NUM;

	VDM_DEGAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32));
	VDM_DEGAMMA_NUM.bits.v_degmm_x3_num = v_degmm_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32),VDM_DEGAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX2Num(HI_U32 v_degmm_x2_num)
{
	U_VDM_DEGAMMA_NUM VDM_DEGAMMA_NUM;

	VDM_DEGAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32));
	VDM_DEGAMMA_NUM.bits.v_degmm_x2_num = v_degmm_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32),VDM_DEGAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX1Num(HI_U32 v_degmm_x1_num)
{
	U_VDM_DEGAMMA_NUM VDM_DEGAMMA_NUM;

	VDM_DEGAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32));
	VDM_DEGAMMA_NUM.bits.v_degmm_x1_num = v_degmm_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM.u32),VDM_DEGAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX8Num(HI_U32 v_degmm_x8_num)
{
	U_VDM_DEGAMMA_NUM2 VDM_DEGAMMA_NUM2;

	VDM_DEGAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32));
	VDM_DEGAMMA_NUM2.bits.v_degmm_x8_num = v_degmm_x8_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32),VDM_DEGAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX7Num(HI_U32 v_degmm_x7_num)
{
	U_VDM_DEGAMMA_NUM2 VDM_DEGAMMA_NUM2;

	VDM_DEGAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32));
	VDM_DEGAMMA_NUM2.bits.v_degmm_x7_num = v_degmm_x7_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32),VDM_DEGAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX6Num(HI_U32 v_degmm_x6_num)
{
	U_VDM_DEGAMMA_NUM2 VDM_DEGAMMA_NUM2;

	VDM_DEGAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32));
	VDM_DEGAMMA_NUM2.bits.v_degmm_x6_num = v_degmm_x6_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32),VDM_DEGAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVDegmmX5Num(HI_U32 v_degmm_x5_num)
{
	U_VDM_DEGAMMA_NUM2 VDM_DEGAMMA_NUM2;

	VDM_DEGAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32));
	VDM_DEGAMMA_NUM2.bits.v_degmm_x5_num = v_degmm_x5_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DEGAMMA_NUM2.u32),VDM_DEGAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmSmRdEn(HI_U32 vdm_sm_rd_en)
{
	U_VDM_TONEMAP_REN VDM_TONEMAP_REN;

	VDM_TONEMAP_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_REN.u32));
	VDM_TONEMAP_REN.bits.vdm_sm_rd_en = vdm_sm_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_REN.u32),VDM_TONEMAP_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapRdEn(HI_U32 vdm_tmap_rd_en)
{
	U_VDM_TONEMAP_REN VDM_TONEMAP_REN;

	VDM_TONEMAP_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_REN.u32));
	VDM_TONEMAP_REN.bits.vdm_tmap_rd_en = vdm_tmap_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_REN.u32),VDM_TONEMAP_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmTmapParaData(HI_U32 vdm_tmap_para_data)
{
	U_VDM_TONEMAP_DATA VDM_TONEMAP_DATA;

	VDM_TONEMAP_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_DATA.u32));
	VDM_TONEMAP_DATA.bits.vdm_tmap_para_data = vdm_tmap_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_DATA.u32),VDM_TONEMAP_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmSmParaData(HI_U32 vdm_sm_para_data)
{
	U_VDM_TONEMAP_SM_DATA VDM_TONEMAP_SM_DATA;

	VDM_TONEMAP_SM_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_SM_DATA.u32));
	VDM_TONEMAP_SM_DATA.bits.vdm_sm_para_data = vdm_sm_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_SM_DATA.u32),VDM_TONEMAP_SM_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX4Step(HI_U32 v_tmap_x4_step)
{
	U_VDM_TONEMAP_STEP VDM_TONEMAP_STEP;

	VDM_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32));
	VDM_TONEMAP_STEP.bits.v_tmap_x4_step = v_tmap_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32),VDM_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX3Step(HI_U32 v_tmap_x3_step)
{
	U_VDM_TONEMAP_STEP VDM_TONEMAP_STEP;

	VDM_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32));
	VDM_TONEMAP_STEP.bits.v_tmap_x3_step = v_tmap_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32),VDM_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX2Step(HI_U32 v_tmap_x2_step)
{
	U_VDM_TONEMAP_STEP VDM_TONEMAP_STEP;

	VDM_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32));
	VDM_TONEMAP_STEP.bits.v_tmap_x2_step = v_tmap_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32),VDM_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX1Step(HI_U32 v_tmap_x1_step)
{
	U_VDM_TONEMAP_STEP VDM_TONEMAP_STEP;

	VDM_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32));
	VDM_TONEMAP_STEP.bits.v_tmap_x1_step = v_tmap_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP.u32),VDM_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX1Pos(HI_U32 v_tmap_x1_pos)
{
	U_VDM_TONEMAP_POS0 VDM_TONEMAP_POS0;

	VDM_TONEMAP_POS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS0.u32));
	VDM_TONEMAP_POS0.bits.v_tmap_x1_pos = v_tmap_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS0.u32),VDM_TONEMAP_POS0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX2Pos(HI_U32 v_tmap_x2_pos)
{
	U_VDM_TONEMAP_POS1 VDM_TONEMAP_POS1;

	VDM_TONEMAP_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS1.u32));
	VDM_TONEMAP_POS1.bits.v_tmap_x2_pos = v_tmap_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS1.u32),VDM_TONEMAP_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX4Num(HI_U32 v_tmap_x4_num)
{
	U_VDM_TONEMAP_NUM VDM_TONEMAP_NUM;

	VDM_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32));
	VDM_TONEMAP_NUM.bits.v_tmap_x4_num = v_tmap_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32),VDM_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX3Num(HI_U32 v_tmap_x3_num)
{
	U_VDM_TONEMAP_NUM VDM_TONEMAP_NUM;

	VDM_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32));
	VDM_TONEMAP_NUM.bits.v_tmap_x3_num = v_tmap_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32),VDM_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX2Num(HI_U32 v_tmap_x2_num)
{
	U_VDM_TONEMAP_NUM VDM_TONEMAP_NUM;

	VDM_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32));
	VDM_TONEMAP_NUM.bits.v_tmap_x2_num = v_tmap_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32),VDM_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX1Num(HI_U32 v_tmap_x1_num)
{
	U_VDM_TONEMAP_NUM VDM_TONEMAP_NUM;

	VDM_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32));
	VDM_TONEMAP_NUM.bits.v_tmap_x1_num = v_tmap_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM.u32),VDM_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX3Pos(HI_U32 v_tmap_x3_pos)
{
	U_VDM_TONEMAP_POS2 VDM_TONEMAP_POS2;

	VDM_TONEMAP_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS2.u32));
	VDM_TONEMAP_POS2.bits.v_tmap_x3_pos = v_tmap_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS2.u32),VDM_TONEMAP_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX4Pos(HI_U32 v_tmap_x4_pos)
{
	U_VDM_TONEMAP_POS3 VDM_TONEMAP_POS3;

	VDM_TONEMAP_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS3.u32));
	VDM_TONEMAP_POS3.bits.v_tmap_x4_pos = v_tmap_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS3.u32),VDM_TONEMAP_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX8Step(HI_U32 v_tmap_x8_step)
{
	U_VDM_TONEMAP_STEP2 VDM_TONEMAP_STEP2;

	VDM_TONEMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32));
	VDM_TONEMAP_STEP2.bits.v_tmap_x8_step = v_tmap_x8_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32),VDM_TONEMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX7Step(HI_U32 v_tmap_x7_step)
{
	U_VDM_TONEMAP_STEP2 VDM_TONEMAP_STEP2;

	VDM_TONEMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32));
	VDM_TONEMAP_STEP2.bits.v_tmap_x7_step = v_tmap_x7_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32),VDM_TONEMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX6Step(HI_U32 v_tmap_x6_step)
{
	U_VDM_TONEMAP_STEP2 VDM_TONEMAP_STEP2;

	VDM_TONEMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32));
	VDM_TONEMAP_STEP2.bits.v_tmap_x6_step = v_tmap_x6_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32),VDM_TONEMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX5Step(HI_U32 v_tmap_x5_step)
{
	U_VDM_TONEMAP_STEP2 VDM_TONEMAP_STEP2;

	VDM_TONEMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32));
	VDM_TONEMAP_STEP2.bits.v_tmap_x5_step = v_tmap_x5_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_STEP2.u32),VDM_TONEMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX5Pos(HI_U32 v_tmap_x5_pos)
{
	U_VDM_TONEMAP_POS4 VDM_TONEMAP_POS4;

	VDM_TONEMAP_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS4.u32));
	VDM_TONEMAP_POS4.bits.v_tmap_x5_pos = v_tmap_x5_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS4.u32),VDM_TONEMAP_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX6Pos(HI_U32 v_tmap_x6_pos)
{
	U_VDM_TONEMAP_POS5 VDM_TONEMAP_POS5;

	VDM_TONEMAP_POS5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS5.u32));
	VDM_TONEMAP_POS5.bits.v_tmap_x6_pos = v_tmap_x6_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS5.u32),VDM_TONEMAP_POS5.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX8Num(HI_U32 v_tmap_x8_num)
{
	U_VDM_TONEMAP_NUM2 VDM_TONEMAP_NUM2;

	VDM_TONEMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32));
	VDM_TONEMAP_NUM2.bits.v_tmap_x8_num = v_tmap_x8_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32),VDM_TONEMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX7Num(HI_U32 v_tmap_x7_num)
{
	U_VDM_TONEMAP_NUM2 VDM_TONEMAP_NUM2;

	VDM_TONEMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32));
	VDM_TONEMAP_NUM2.bits.v_tmap_x7_num = v_tmap_x7_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32),VDM_TONEMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX6Num(HI_U32 v_tmap_x6_num)
{
	U_VDM_TONEMAP_NUM2 VDM_TONEMAP_NUM2;

	VDM_TONEMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32));
	VDM_TONEMAP_NUM2.bits.v_tmap_x6_num = v_tmap_x6_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32),VDM_TONEMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX5Num(HI_U32 v_tmap_x5_num)
{
	U_VDM_TONEMAP_NUM2 VDM_TONEMAP_NUM2;

	VDM_TONEMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32));
	VDM_TONEMAP_NUM2.bits.v_tmap_x5_num = v_tmap_x5_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_NUM2.u32),VDM_TONEMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX7Pos(HI_U32 v_tmap_x7_pos)
{
	U_VDM_TONEMAP_POS6 VDM_TONEMAP_POS6;

	VDM_TONEMAP_POS6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS6.u32));
	VDM_TONEMAP_POS6.bits.v_tmap_x7_pos = v_tmap_x7_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS6.u32),VDM_TONEMAP_POS6.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVTmapX8Pos(HI_U32 v_tmap_x8_pos)
{
	U_VDM_TONEMAP_POS7 VDM_TONEMAP_POS7;

	VDM_TONEMAP_POS7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS7.u32));
	VDM_TONEMAP_POS7.bits.v_tmap_x8_pos = v_tmap_x8_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_TONEMAP_POS7.u32),VDM_TONEMAP_POS7.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX4Step(HI_U32 v_smap_x4_step)
{
	U_VDM_SMAP_STEP VDM_SMAP_STEP;

	VDM_SMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32));
	VDM_SMAP_STEP.bits.v_smap_x4_step = v_smap_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32),VDM_SMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX3Step(HI_U32 v_smap_x3_step)
{
	U_VDM_SMAP_STEP VDM_SMAP_STEP;

	VDM_SMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32));
	VDM_SMAP_STEP.bits.v_smap_x3_step = v_smap_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32),VDM_SMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX2Step(HI_U32 v_smap_x2_step)
{
	U_VDM_SMAP_STEP VDM_SMAP_STEP;

	VDM_SMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32));
	VDM_SMAP_STEP.bits.v_smap_x2_step = v_smap_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32),VDM_SMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX1Step(HI_U32 v_smap_x1_step)
{
	U_VDM_SMAP_STEP VDM_SMAP_STEP;

	VDM_SMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32));
	VDM_SMAP_STEP.bits.v_smap_x1_step = v_smap_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP.u32),VDM_SMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX1Pos(HI_U32 v_smap_x1_pos)
{
	U_VDM_SMAP_POS0 VDM_SMAP_POS0;

	VDM_SMAP_POS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS0.u32));
	VDM_SMAP_POS0.bits.v_smap_x1_pos = v_smap_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS0.u32),VDM_SMAP_POS0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX2Pos(HI_U32 v_smap_x2_pos)
{
	U_VDM_SMAP_POS1 VDM_SMAP_POS1;

	VDM_SMAP_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS1.u32));
	VDM_SMAP_POS1.bits.v_smap_x2_pos = v_smap_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS1.u32),VDM_SMAP_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX4Num(HI_U32 v_smap_x4_num)
{
	U_VDM_SMAP_NUM VDM_SMAP_NUM;

	VDM_SMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32));
	VDM_SMAP_NUM.bits.v_smap_x4_num = v_smap_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32),VDM_SMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX3Num(HI_U32 v_smap_x3_num)
{
	U_VDM_SMAP_NUM VDM_SMAP_NUM;

	VDM_SMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32));
	VDM_SMAP_NUM.bits.v_smap_x3_num = v_smap_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32),VDM_SMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX2Num(HI_U32 v_smap_x2_num)
{
	U_VDM_SMAP_NUM VDM_SMAP_NUM;

	VDM_SMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32));
	VDM_SMAP_NUM.bits.v_smap_x2_num = v_smap_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32),VDM_SMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX1Num(HI_U32 v_smap_x1_num)
{
	U_VDM_SMAP_NUM VDM_SMAP_NUM;

	VDM_SMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32));
	VDM_SMAP_NUM.bits.v_smap_x1_num = v_smap_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM.u32),VDM_SMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX3Pos(HI_U32 v_smap_x3_pos)
{
	U_VDM_SMAP_POS2 VDM_SMAP_POS2;

	VDM_SMAP_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS2.u32));
	VDM_SMAP_POS2.bits.v_smap_x3_pos = v_smap_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS2.u32),VDM_SMAP_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX4Pos(HI_U32 v_smap_x4_pos)
{
	U_VDM_SMAP_POS3 VDM_SMAP_POS3;

	VDM_SMAP_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS3.u32));
	VDM_SMAP_POS3.bits.v_smap_x4_pos = v_smap_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS3.u32),VDM_SMAP_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX8Step(HI_U32 v_smap_x8_step)
{
	U_VDM_SMAP_STEP2 VDM_SMAP_STEP2;

	VDM_SMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32));
	VDM_SMAP_STEP2.bits.v_smap_x8_step = v_smap_x8_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32),VDM_SMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX7Step(HI_U32 v_smap_x7_step)
{
	U_VDM_SMAP_STEP2 VDM_SMAP_STEP2;

	VDM_SMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32));
	VDM_SMAP_STEP2.bits.v_smap_x7_step = v_smap_x7_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32),VDM_SMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX6Step(HI_U32 v_smap_x6_step)
{
	U_VDM_SMAP_STEP2 VDM_SMAP_STEP2;

	VDM_SMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32));
	VDM_SMAP_STEP2.bits.v_smap_x6_step = v_smap_x6_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32),VDM_SMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX5Step(HI_U32 v_smap_x5_step)
{
	U_VDM_SMAP_STEP2 VDM_SMAP_STEP2;

	VDM_SMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32));
	VDM_SMAP_STEP2.bits.v_smap_x5_step = v_smap_x5_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_STEP2.u32),VDM_SMAP_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX5Pos(HI_U32 v_smap_x5_pos)
{
	U_VDM_SMAP_POS4 VDM_SMAP_POS4;

	VDM_SMAP_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS4.u32));
	VDM_SMAP_POS4.bits.v_smap_x5_pos = v_smap_x5_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS4.u32),VDM_SMAP_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX6Pos(HI_U32 v_smap_x6_pos)
{
	U_VDM_SMAP_POS5 VDM_SMAP_POS5;

	VDM_SMAP_POS5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS5.u32));
	VDM_SMAP_POS5.bits.v_smap_x6_pos = v_smap_x6_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS5.u32),VDM_SMAP_POS5.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX8Num(HI_U32 v_smap_x8_num)
{
	U_VDM_SMAP_NUM2 VDM_SMAP_NUM2;

	VDM_SMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32));
	VDM_SMAP_NUM2.bits.v_smap_x8_num = v_smap_x8_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32),VDM_SMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX7Num(HI_U32 v_smap_x7_num)
{
	U_VDM_SMAP_NUM2 VDM_SMAP_NUM2;

	VDM_SMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32));
	VDM_SMAP_NUM2.bits.v_smap_x7_num = v_smap_x7_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32),VDM_SMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX6Num(HI_U32 v_smap_x6_num)
{
	U_VDM_SMAP_NUM2 VDM_SMAP_NUM2;

	VDM_SMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32));
	VDM_SMAP_NUM2.bits.v_smap_x6_num = v_smap_x6_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32),VDM_SMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX5Num(HI_U32 v_smap_x5_num)
{
	U_VDM_SMAP_NUM2 VDM_SMAP_NUM2;

	VDM_SMAP_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32));
	VDM_SMAP_NUM2.bits.v_smap_x5_num = v_smap_x5_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_NUM2.u32),VDM_SMAP_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX7Pos(HI_U32 v_smap_x7_pos)
{
	U_VDM_SMAP_POS6 VDM_SMAP_POS6;

	VDM_SMAP_POS6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS6.u32));
	VDM_SMAP_POS6.bits.v_smap_x7_pos = v_smap_x7_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS6.u32),VDM_SMAP_POS6.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVSmapX8Pos(HI_U32 v_smap_x8_pos)
{
	U_VDM_SMAP_POS7 VDM_SMAP_POS7;

	VDM_SMAP_POS7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_SMAP_POS7.u32));
	VDM_SMAP_POS7.bits.v_smap_x8_pos = v_smap_x8_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_SMAP_POS7.u32),VDM_SMAP_POS7.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmGammaRdEn(HI_U32 vdm_gamma_rd_en)
{
	U_VDM_GAMMA_REN VDM_GAMMA_REN;

	VDM_GAMMA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_REN.u32));
	VDM_GAMMA_REN.bits.vdm_gamma_rd_en = vdm_gamma_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_REN.u32),VDM_GAMMA_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmGammaParaData(HI_U32 vdm_gamma_para_data)
{
	U_VDM_GAMMMA_DATA VDM_GAMMMA_DATA;

	VDM_GAMMMA_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMMA_DATA.u32));
	VDM_GAMMMA_DATA.bits.vdm_gamma_para_data = vdm_gamma_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMMA_DATA.u32),VDM_GAMMMA_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX4Step(HI_U32 v_gmm_x4_step)
{
	U_VDM_GAMMA_STEP VDM_GAMMA_STEP;

	VDM_GAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32));
	VDM_GAMMA_STEP.bits.v_gmm_x4_step = v_gmm_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32),VDM_GAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX3Step(HI_U32 v_gmm_x3_step)
{
	U_VDM_GAMMA_STEP VDM_GAMMA_STEP;

	VDM_GAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32));
	VDM_GAMMA_STEP.bits.v_gmm_x3_step = v_gmm_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32),VDM_GAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX2Step(HI_U32 v_gmm_x2_step)
{
	U_VDM_GAMMA_STEP VDM_GAMMA_STEP;

	VDM_GAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32));
	VDM_GAMMA_STEP.bits.v_gmm_x2_step = v_gmm_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32),VDM_GAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX1Step(HI_U32 v_gmm_x1_step)
{
	U_VDM_GAMMA_STEP VDM_GAMMA_STEP;

	VDM_GAMMA_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32));
	VDM_GAMMA_STEP.bits.v_gmm_x1_step = v_gmm_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP.u32),VDM_GAMMA_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX1Pos(HI_U32 v_gmm_x1_pos)
{
	U_VDM_GAMMA_POS0 VDM_GAMMA_POS0;

	VDM_GAMMA_POS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS0.u32));
	VDM_GAMMA_POS0.bits.v_gmm_x1_pos = v_gmm_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS0.u32),VDM_GAMMA_POS0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX2Pos(HI_U32 v_gmm_x2_pos)
{
	U_VDM_GAMMA_POS1 VDM_GAMMA_POS1;

	VDM_GAMMA_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS1.u32));
	VDM_GAMMA_POS1.bits.v_gmm_x2_pos = v_gmm_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS1.u32),VDM_GAMMA_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX4Num(HI_U32 v_gmm_x4_num)
{
	U_VDM_GAMMA_NUM VDM_GAMMA_NUM;

	VDM_GAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32));
	VDM_GAMMA_NUM.bits.v_gmm_x4_num = v_gmm_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32),VDM_GAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX3Num(HI_U32 v_gmm_x3_num)
{
	U_VDM_GAMMA_NUM VDM_GAMMA_NUM;

	VDM_GAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32));
	VDM_GAMMA_NUM.bits.v_gmm_x3_num = v_gmm_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32),VDM_GAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX2Num(HI_U32 v_gmm_x2_num)
{
	U_VDM_GAMMA_NUM VDM_GAMMA_NUM;

	VDM_GAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32));
	VDM_GAMMA_NUM.bits.v_gmm_x2_num = v_gmm_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32),VDM_GAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX1Num(HI_U32 v_gmm_x1_num)
{
	U_VDM_GAMMA_NUM VDM_GAMMA_NUM;

	VDM_GAMMA_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32));
	VDM_GAMMA_NUM.bits.v_gmm_x1_num = v_gmm_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM.u32),VDM_GAMMA_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX3Pos(HI_U32 v_gmm_x3_pos)
{
	U_VDM_GAMMA_POS2 VDM_GAMMA_POS2;

	VDM_GAMMA_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS2.u32));
	VDM_GAMMA_POS2.bits.v_gmm_x3_pos = v_gmm_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS2.u32),VDM_GAMMA_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX4Pos(HI_U32 v_gmm_x4_pos)
{
	U_VDM_GAMMA_POS3 VDM_GAMMA_POS3;

	VDM_GAMMA_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS3.u32));
	VDM_GAMMA_POS3.bits.v_gmm_x4_pos = v_gmm_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS3.u32),VDM_GAMMA_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX8Step(HI_U32 v_gmm_x8_step)
{
	U_VDM_GAMMA_STEP2 VDM_GAMMA_STEP2;

	VDM_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32));
	VDM_GAMMA_STEP2.bits.v_gmm_x8_step = v_gmm_x8_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32),VDM_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX7Step(HI_U32 v_gmm_x7_step)
{
	U_VDM_GAMMA_STEP2 VDM_GAMMA_STEP2;

	VDM_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32));
	VDM_GAMMA_STEP2.bits.v_gmm_x7_step = v_gmm_x7_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32),VDM_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX6Step(HI_U32 v_gmm_x6_step)
{
	U_VDM_GAMMA_STEP2 VDM_GAMMA_STEP2;

	VDM_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32));
	VDM_GAMMA_STEP2.bits.v_gmm_x6_step = v_gmm_x6_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32),VDM_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX5Step(HI_U32 v_gmm_x5_step)
{
	U_VDM_GAMMA_STEP2 VDM_GAMMA_STEP2;

	VDM_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32));
	VDM_GAMMA_STEP2.bits.v_gmm_x5_step = v_gmm_x5_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_STEP2.u32),VDM_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX8Num(HI_U32 v_gmm_x8_num)
{
	U_VDM_GAMMA_NUM2 VDM_GAMMA_NUM2;

	VDM_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32));
	VDM_GAMMA_NUM2.bits.v_gmm_x8_num = v_gmm_x8_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32),VDM_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX7Num(HI_U32 v_gmm_x7_num)
{
	U_VDM_GAMMA_NUM2 VDM_GAMMA_NUM2;

	VDM_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32));
	VDM_GAMMA_NUM2.bits.v_gmm_x7_num = v_gmm_x7_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32),VDM_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX6Num(HI_U32 v_gmm_x6_num)
{
	U_VDM_GAMMA_NUM2 VDM_GAMMA_NUM2;

	VDM_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32));
	VDM_GAMMA_NUM2.bits.v_gmm_x6_num = v_gmm_x6_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32),VDM_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX5Num(HI_U32 v_gmm_x5_num)
{
	U_VDM_GAMMA_NUM2 VDM_GAMMA_NUM2;

	VDM_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32));
	VDM_GAMMA_NUM2.bits.v_gmm_x5_num = v_gmm_x5_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_NUM2.u32),VDM_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX5Pos(HI_U32 v_gmm_x5_pos)
{
	U_VDM_GAMMA_POS4 VDM_GAMMA_POS4;

	VDM_GAMMA_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS4.u32));
	VDM_GAMMA_POS4.bits.v_gmm_x5_pos = v_gmm_x5_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS4.u32),VDM_GAMMA_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX6Pos(HI_U32 v_gmm_x6_pos)
{
	U_VDM_GAMMA_POS5 VDM_GAMMA_POS5;

	VDM_GAMMA_POS5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS5.u32));
	VDM_GAMMA_POS5.bits.v_gmm_x6_pos = v_gmm_x6_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS5.u32),VDM_GAMMA_POS5.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX7Pos(HI_U32 v_gmm_x7_pos)
{
	U_VDM_GAMMA_POS6 VDM_GAMMA_POS6;

	VDM_GAMMA_POS6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS6.u32));
	VDM_GAMMA_POS6.bits.v_gmm_x7_pos = v_gmm_x7_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS6.u32),VDM_GAMMA_POS6.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVGmmX8Pos(HI_U32 v_gmm_x8_pos)
{
	U_VDM_GAMMA_POS7 VDM_GAMMA_POS7;

	VDM_GAMMA_POS7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS7.u32));
	VDM_GAMMA_POS7.bits.v_gmm_x8_pos = v_gmm_x8_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_GAMMA_POS7.u32),VDM_GAMMA_POS7.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCscEn(HI_U32 vdm_csc_en)
{
	U_VDM_CSC_CTRL VDM_CSC_CTRL;

	VDM_CSC_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_CTRL.u32));
	VDM_CSC_CTRL.bits.vdm_csc_en = vdm_csc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_CTRL.u32),VDM_CSC_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef00Csc(HI_U32 vdm_coef00_csc)
{
	U_VDM_CSC_COEF00 VDM_CSC_COEF00;

	VDM_CSC_COEF00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF00.u32));
	VDM_CSC_COEF00.bits.vdm_coef00_csc = vdm_coef00_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF00.u32),VDM_CSC_COEF00.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef01Csc(HI_U32 vdm_coef01_csc)
{
	U_VDM_CSC_COEF01 VDM_CSC_COEF01;

	VDM_CSC_COEF01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF01.u32));
	VDM_CSC_COEF01.bits.vdm_coef01_csc = vdm_coef01_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF01.u32),VDM_CSC_COEF01.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef02Csc(HI_U32 vdm_coef02_csc)
{
	U_VDM_CSC_COEF02 VDM_CSC_COEF02;

	VDM_CSC_COEF02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF02.u32));
	VDM_CSC_COEF02.bits.vdm_coef02_csc = vdm_coef02_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF02.u32),VDM_CSC_COEF02.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef10Csc(HI_U32 vdm_coef10_csc)
{
	U_VDM_CSC_COEF10 VDM_CSC_COEF10;

	VDM_CSC_COEF10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF10.u32));
	VDM_CSC_COEF10.bits.vdm_coef10_csc = vdm_coef10_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF10.u32),VDM_CSC_COEF10.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef11Csc(HI_U32 vdm_coef11_csc)
{
	U_VDM_CSC_COEF11 VDM_CSC_COEF11;

	VDM_CSC_COEF11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF11.u32));
	VDM_CSC_COEF11.bits.vdm_coef11_csc = vdm_coef11_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF11.u32),VDM_CSC_COEF11.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef12Csc(HI_U32 vdm_coef12_csc)
{
	U_VDM_CSC_COEF12 VDM_CSC_COEF12;

	VDM_CSC_COEF12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF12.u32));
	VDM_CSC_COEF12.bits.vdm_coef12_csc = vdm_coef12_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF12.u32),VDM_CSC_COEF12.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef20Csc(HI_U32 vdm_coef20_csc)
{
	U_VDM_CSC_COEF20 VDM_CSC_COEF20;

	VDM_CSC_COEF20.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF20.u32));
	VDM_CSC_COEF20.bits.vdm_coef20_csc = vdm_coef20_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF20.u32),VDM_CSC_COEF20.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef21Csc(HI_U32 vdm_coef21_csc)
{
	U_VDM_CSC_COEF21 VDM_CSC_COEF21;

	VDM_CSC_COEF21.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF21.u32));
	VDM_CSC_COEF21.bits.vdm_coef21_csc = vdm_coef21_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF21.u32),VDM_CSC_COEF21.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCoef22Csc(HI_U32 vdm_coef22_csc)
{
	U_VDM_CSC_COEF22 VDM_CSC_COEF22;

	VDM_CSC_COEF22.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_COEF22.u32));
	VDM_CSC_COEF22.bits.vdm_coef22_csc = vdm_coef22_csc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_COEF22.u32),VDM_CSC_COEF22.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCscScale(HI_U32 vdm_csc_scale)
{
	U_VDM_CSC_SCALE VDM_CSC_SCALE;

	VDM_CSC_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_SCALE.u32));
	VDM_CSC_SCALE.bits.vdm_csc_scale = vdm_csc_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_SCALE.u32),VDM_CSC_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCscClipMin(HI_U32 vdm_csc_clip_min)
{
	U_VDM_CSC_CLIP_MIN VDM_CSC_CLIP_MIN;

	VDM_CSC_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_CLIP_MIN.u32));
	VDM_CSC_CLIP_MIN.bits.vdm_csc_clip_min = vdm_csc_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_CLIP_MIN.u32),VDM_CSC_CLIP_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCscClipMax(HI_U32 vdm_csc_clip_max)
{
	U_VDM_CSC_CLIP_MAX VDM_CSC_CLIP_MAX;

	VDM_CSC_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_CLIP_MAX.u32));
	VDM_CSC_CLIP_MAX.bits.vdm_csc_clip_max = vdm_csc_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_CLIP_MAX.u32),VDM_CSC_CLIP_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc0InDc(HI_U32 vdm_csc_0_in_dc)
{
	U_VDM_CSC_IN_DC0 VDM_CSC_IN_DC0;

	VDM_CSC_IN_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC0.u32));
	VDM_CSC_IN_DC0.bits.vdm_csc_0_in_dc = vdm_csc_0_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC0.u32),VDM_CSC_IN_DC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc1InDc(HI_U32 vdm_csc_1_in_dc)
{
	U_VDM_CSC_IN_DC1 VDM_CSC_IN_DC1;

	VDM_CSC_IN_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC1.u32));
	VDM_CSC_IN_DC1.bits.vdm_csc_1_in_dc = vdm_csc_1_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC1.u32),VDM_CSC_IN_DC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc2InDc(HI_U32 vdm_csc_2_in_dc)
{
	U_VDM_CSC_IN_DC2 VDM_CSC_IN_DC2;

	VDM_CSC_IN_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC2.u32));
	VDM_CSC_IN_DC2.bits.vdm_csc_2_in_dc = vdm_csc_2_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_IN_DC2.u32),VDM_CSC_IN_DC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc0OutDc(HI_U32 vdm_csc_0_out_dc)
{
	U_VDM_CSC_OUT_DC0 VDM_CSC_OUT_DC0;

	VDM_CSC_OUT_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC0.u32));
	VDM_CSC_OUT_DC0.bits.vdm_csc_0_out_dc = vdm_csc_0_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC0.u32),VDM_CSC_OUT_DC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc1OutDc(HI_U32 vdm_csc_1_out_dc)
{
	U_VDM_CSC_OUT_DC1 VDM_CSC_OUT_DC1;

	VDM_CSC_OUT_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC1.u32));
	VDM_CSC_OUT_DC1.bits.vdm_csc_1_out_dc = vdm_csc_1_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC1.u32),VDM_CSC_OUT_DC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCsc2OutDc(HI_U32 vdm_csc_2_out_dc)
{
	U_VDM_CSC_OUT_DC2 VDM_CSC_OUT_DC2;

	VDM_CSC_OUT_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC2.u32));
	VDM_CSC_OUT_DC2.bits.vdm_csc_2_out_dc = vdm_csc_2_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_CSC_OUT_DC2.u32),VDM_CSC_OUT_DC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1GammaEn(HI_U32 vdm_v1_gamma_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v1_gamma_en = vdm_v1_gamma_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0GammaEn(HI_U32 vdm_v0_gamma_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v0_gamma_en = vdm_v0_gamma_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1CscEn(HI_U32 vdm_v1_csc_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v1_csc_en = vdm_v1_csc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0CscEn(HI_U32 vdm_v0_csc_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v0_csc_en = vdm_v0_csc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0ClEn(HI_U32 vdm_v0_cl_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v0_cl_en = vdm_v0_cl_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1ClEn(HI_U32 vdm_v1_cl_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_v1_cl_en = vdm_v1_cl_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmY2rEn(HI_U32 vdm_y2r_en)
{
	U_VDM_YUV2RGB_CTRL VDM_YUV2RGB_CTRL;

	VDM_YUV2RGB_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32));
	VDM_YUV2RGB_CTRL.bits.vdm_y2r_en = vdm_y2r_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_CTRL.u32),VDM_YUV2RGB_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm00Yuv2rgb(HI_U32 vdm_00_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF00 VDM_YUV2RGB_COEF00;

	VDM_YUV2RGB_COEF00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF00.u32));
	VDM_YUV2RGB_COEF00.bits.vdm_00_yuv2rgb = vdm_00_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF00.u32),VDM_YUV2RGB_COEF00.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm01Yuv2rgb(HI_U32 vdm_01_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF01 VDM_YUV2RGB_COEF01;

	VDM_YUV2RGB_COEF01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF01.u32));
	VDM_YUV2RGB_COEF01.bits.vdm_01_yuv2rgb = vdm_01_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF01.u32),VDM_YUV2RGB_COEF01.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm02Yuv2rgb(HI_U32 vdm_02_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF02 VDM_YUV2RGB_COEF02;

	VDM_YUV2RGB_COEF02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF02.u32));
	VDM_YUV2RGB_COEF02.bits.vdm_02_yuv2rgb = vdm_02_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF02.u32),VDM_YUV2RGB_COEF02.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm03Yuv2rgb(HI_U32 vdm_03_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF03 VDM_YUV2RGB_COEF03;

	VDM_YUV2RGB_COEF03.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF03.u32));
	VDM_YUV2RGB_COEF03.bits.vdm_03_yuv2rgb = vdm_03_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF03.u32),VDM_YUV2RGB_COEF03.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm04Yuv2rgb(HI_U32 vdm_04_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF04 VDM_YUV2RGB_COEF04;

	VDM_YUV2RGB_COEF04.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF04.u32));
	VDM_YUV2RGB_COEF04.bits.vdm_04_yuv2rgb = vdm_04_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF04.u32),VDM_YUV2RGB_COEF04.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm05Yuv2rgb(HI_U32 vdm_05_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF05 VDM_YUV2RGB_COEF05;

	VDM_YUV2RGB_COEF05.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF05.u32));
	VDM_YUV2RGB_COEF05.bits.vdm_05_yuv2rgb = vdm_05_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF05.u32),VDM_YUV2RGB_COEF05.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm06Yuv2rgb(HI_U32 vdm_06_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF06 VDM_YUV2RGB_COEF06;

	VDM_YUV2RGB_COEF06.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF06.u32));
	VDM_YUV2RGB_COEF06.bits.vdm_06_yuv2rgb = vdm_06_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF06.u32),VDM_YUV2RGB_COEF06.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm07Yuv2rgb(HI_U32 vdm_07_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF07 VDM_YUV2RGB_COEF07;

	VDM_YUV2RGB_COEF07.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF07.u32));
	VDM_YUV2RGB_COEF07.bits.vdm_07_yuv2rgb = vdm_07_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF07.u32),VDM_YUV2RGB_COEF07.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm08Yuv2rgb(HI_U32 vdm_08_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF08 VDM_YUV2RGB_COEF08;

	VDM_YUV2RGB_COEF08.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF08.u32));
	VDM_YUV2RGB_COEF08.bits.vdm_08_yuv2rgb = vdm_08_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF08.u32),VDM_YUV2RGB_COEF08.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm10Yuv2rgb(HI_U32 vdm_10_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF10 VDM_YUV2RGB_COEF10;

	VDM_YUV2RGB_COEF10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF10.u32));
	VDM_YUV2RGB_COEF10.bits.vdm_10_yuv2rgb = vdm_10_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF10.u32),VDM_YUV2RGB_COEF10.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm11Yuv2rgb(HI_U32 vdm_11_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF11 VDM_YUV2RGB_COEF11;

	VDM_YUV2RGB_COEF11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF11.u32));
	VDM_YUV2RGB_COEF11.bits.vdm_11_yuv2rgb = vdm_11_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF11.u32),VDM_YUV2RGB_COEF11.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm12Yuv2rgb(HI_U32 vdm_12_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF12 VDM_YUV2RGB_COEF12;

	VDM_YUV2RGB_COEF12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF12.u32));
	VDM_YUV2RGB_COEF12.bits.vdm_12_yuv2rgb = vdm_12_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF12.u32),VDM_YUV2RGB_COEF12.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm13Yuv2rgb(HI_U32 vdm_13_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF13 VDM_YUV2RGB_COEF13;

	VDM_YUV2RGB_COEF13.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF13.u32));
	VDM_YUV2RGB_COEF13.bits.vdm_13_yuv2rgb = vdm_13_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF13.u32),VDM_YUV2RGB_COEF13.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm14Yuv2rgb(HI_U32 vdm_14_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF14 VDM_YUV2RGB_COEF14;

	VDM_YUV2RGB_COEF14.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF14.u32));
	VDM_YUV2RGB_COEF14.bits.vdm_14_yuv2rgb = vdm_14_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF14.u32),VDM_YUV2RGB_COEF14.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm15Yuv2rgb(HI_U32 vdm_15_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF15 VDM_YUV2RGB_COEF15;

	VDM_YUV2RGB_COEF15.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF15.u32));
	VDM_YUV2RGB_COEF15.bits.vdm_15_yuv2rgb = vdm_15_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF15.u32),VDM_YUV2RGB_COEF15.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm16Yuv2rgb(HI_U32 vdm_16_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF16 VDM_YUV2RGB_COEF16;

	VDM_YUV2RGB_COEF16.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF16.u32));
	VDM_YUV2RGB_COEF16.bits.vdm_16_yuv2rgb = vdm_16_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF16.u32),VDM_YUV2RGB_COEF16.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm17Yuv2rgb(HI_U32 vdm_17_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF17 VDM_YUV2RGB_COEF17;

	VDM_YUV2RGB_COEF17.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF17.u32));
	VDM_YUV2RGB_COEF17.bits.vdm_17_yuv2rgb = vdm_17_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF17.u32),VDM_YUV2RGB_COEF17.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm18Yuv2rgb(HI_U32 vdm_18_yuv2rgb)
{
	U_VDM_YUV2RGB_COEF18 VDM_YUV2RGB_COEF18;

	VDM_YUV2RGB_COEF18.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF18.u32));
	VDM_YUV2RGB_COEF18.bits.vdm_18_yuv2rgb = vdm_18_yuv2rgb;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_COEF18.u32),VDM_YUV2RGB_COEF18.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1Yuv2rgbscale2p(HI_U32 vdm_v1_yuv2rgbscale2p)
{
	U_VDM_YUV2RGB_SCALE2P VDM_YUV2RGB_SCALE2P;

	VDM_YUV2RGB_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_SCALE2P.u32));
	VDM_YUV2RGB_SCALE2P.bits.vdm_v1_yuv2rgbscale2p = vdm_v1_yuv2rgbscale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_SCALE2P.u32),VDM_YUV2RGB_SCALE2P.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0Yuv2rgbscale2p(HI_U32 vdm_v0_yuv2rgbscale2p)
{
	U_VDM_YUV2RGB_SCALE2P VDM_YUV2RGB_SCALE2P;

	VDM_YUV2RGB_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_SCALE2P.u32));
	VDM_YUV2RGB_SCALE2P.bits.vdm_v0_yuv2rgbscale2p = vdm_v0_yuv2rgbscale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_SCALE2P.u32),VDM_YUV2RGB_SCALE2P.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb00InDc(HI_U32 vdm_yuv2rgb_00_in_dc)
{
	U_VDM_YUV2RGB_IN_DC00 VDM_YUV2RGB_IN_DC00;

	VDM_YUV2RGB_IN_DC00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC00.u32));
	VDM_YUV2RGB_IN_DC00.bits.vdm_yuv2rgb_00_in_dc = vdm_yuv2rgb_00_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC00.u32),VDM_YUV2RGB_IN_DC00.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb01InDc(HI_U32 vdm_yuv2rgb_01_in_dc)
{
	U_VDM_YUV2RGB_IN_DC01 VDM_YUV2RGB_IN_DC01;

	VDM_YUV2RGB_IN_DC01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC01.u32));
	VDM_YUV2RGB_IN_DC01.bits.vdm_yuv2rgb_01_in_dc = vdm_yuv2rgb_01_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC01.u32),VDM_YUV2RGB_IN_DC01.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb02InDc(HI_U32 vdm_yuv2rgb_02_in_dc)
{
	U_VDM_YUV2RGB_IN_DC02 VDM_YUV2RGB_IN_DC02;

	VDM_YUV2RGB_IN_DC02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC02.u32));
	VDM_YUV2RGB_IN_DC02.bits.vdm_yuv2rgb_02_in_dc = vdm_yuv2rgb_02_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC02.u32),VDM_YUV2RGB_IN_DC02.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb00OutDc(HI_U32 vdm_yuv2rgb_00_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC00 VDM_YUV2RGB_OUT_DC00;

	VDM_YUV2RGB_OUT_DC00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC00.u32));
	VDM_YUV2RGB_OUT_DC00.bits.vdm_yuv2rgb_00_out_dc = vdm_yuv2rgb_00_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC00.u32),VDM_YUV2RGB_OUT_DC00.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb01OutDc(HI_U32 vdm_yuv2rgb_01_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC01 VDM_YUV2RGB_OUT_DC01;

	VDM_YUV2RGB_OUT_DC01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC01.u32));
	VDM_YUV2RGB_OUT_DC01.bits.vdm_yuv2rgb_01_out_dc = vdm_yuv2rgb_01_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC01.u32),VDM_YUV2RGB_OUT_DC01.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb02OutDc(HI_U32 vdm_yuv2rgb_02_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC02 VDM_YUV2RGB_OUT_DC02;

	VDM_YUV2RGB_OUT_DC02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC02.u32));
	VDM_YUV2RGB_OUT_DC02.bits.vdm_yuv2rgb_02_out_dc = vdm_yuv2rgb_02_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC02.u32),VDM_YUV2RGB_OUT_DC02.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb10InDc(HI_U32 vdm_yuv2rgb_10_in_dc)
{
	U_VDM_YUV2RGB_IN_DC10 VDM_YUV2RGB_IN_DC10;

	VDM_YUV2RGB_IN_DC10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC10.u32));
	VDM_YUV2RGB_IN_DC10.bits.vdm_yuv2rgb_10_in_dc = vdm_yuv2rgb_10_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC10.u32),VDM_YUV2RGB_IN_DC10.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb11InDc(HI_U32 vdm_yuv2rgb_11_in_dc)
{
	U_VDM_YUV2RGB_IN_DC11 VDM_YUV2RGB_IN_DC11;

	VDM_YUV2RGB_IN_DC11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC11.u32));
	VDM_YUV2RGB_IN_DC11.bits.vdm_yuv2rgb_11_in_dc = vdm_yuv2rgb_11_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC11.u32),VDM_YUV2RGB_IN_DC11.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb12InDc(HI_U32 vdm_yuv2rgb_12_in_dc)
{
	U_VDM_YUV2RGB_IN_DC12 VDM_YUV2RGB_IN_DC12;

	VDM_YUV2RGB_IN_DC12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC12.u32));
	VDM_YUV2RGB_IN_DC12.bits.vdm_yuv2rgb_12_in_dc = vdm_yuv2rgb_12_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_IN_DC12.u32),VDM_YUV2RGB_IN_DC12.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb10OutDc(HI_U32 vdm_yuv2rgb_10_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC10 VDM_YUV2RGB_OUT_DC10;

	VDM_YUV2RGB_OUT_DC10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC10.u32));
	VDM_YUV2RGB_OUT_DC10.bits.vdm_yuv2rgb_10_out_dc = vdm_yuv2rgb_10_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC10.u32),VDM_YUV2RGB_OUT_DC10.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb11OutDc(HI_U32 vdm_yuv2rgb_11_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC11 VDM_YUV2RGB_OUT_DC11;

	VDM_YUV2RGB_OUT_DC11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC11.u32));
	VDM_YUV2RGB_OUT_DC11.bits.vdm_yuv2rgb_11_out_dc = vdm_yuv2rgb_11_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC11.u32),VDM_YUV2RGB_OUT_DC11.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmYuv2rgb12OutDc(HI_U32 vdm_yuv2rgb_12_out_dc)
{
	U_VDM_YUV2RGB_OUT_DC12 VDM_YUV2RGB_OUT_DC12;

	VDM_YUV2RGB_OUT_DC12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC12.u32));
	VDM_YUV2RGB_OUT_DC12.bits.vdm_yuv2rgb_12_out_dc = vdm_yuv2rgb_12_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_OUT_DC12.u32),VDM_YUV2RGB_OUT_DC12.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1Yuv2rgbClipMin(HI_U32 vdm_v1_yuv2rgb_clip_min)
{
	U_VDM_YUV2RGB_MIN VDM_YUV2RGB_MIN;

	VDM_YUV2RGB_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MIN.u32));
	VDM_YUV2RGB_MIN.bits.vdm_v1_yuv2rgb_clip_min = vdm_v1_yuv2rgb_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MIN.u32),VDM_YUV2RGB_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0Yuv2rgbClipMin(HI_U32 vdm_v0_yuv2rgb_clip_min)
{
	U_VDM_YUV2RGB_MIN VDM_YUV2RGB_MIN;

	VDM_YUV2RGB_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MIN.u32));
	VDM_YUV2RGB_MIN.bits.vdm_v0_yuv2rgb_clip_min = vdm_v0_yuv2rgb_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MIN.u32),VDM_YUV2RGB_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV1Yuv2rgbClipMax(HI_U32 vdm_v1_yuv2rgb_clip_max)
{
	U_VDM_YUV2RGB_MAX VDM_YUV2RGB_MAX;

	VDM_YUV2RGB_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MAX.u32));
	VDM_YUV2RGB_MAX.bits.vdm_v1_yuv2rgb_clip_max = vdm_v1_yuv2rgb_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MAX.u32),VDM_YUV2RGB_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmV0Yuv2rgbClipMax(HI_U32 vdm_v0_yuv2rgb_clip_max)
{
	U_VDM_YUV2RGB_MAX VDM_YUV2RGB_MAX;

	VDM_YUV2RGB_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MAX.u32));
	VDM_YUV2RGB_MAX.bits.vdm_v0_yuv2rgb_clip_max = vdm_v0_yuv2rgb_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_YUV2RGB_MAX.u32),VDM_YUV2RGB_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmR2yPipEn(HI_U32 vdm_r2y_pip_en)
{
	U_VDM_RGB2YUV_CTRL VDM_RGB2YUV_CTRL;

	VDM_RGB2YUV_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32));
	VDM_RGB2YUV_CTRL.bits.vdm_r2y_pip_en = vdm_r2y_pip_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32),VDM_RGB2YUV_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCadjEn(HI_U32 vdm_cadj_en)
{
	U_VDM_RGB2YUV_CTRL VDM_RGB2YUV_CTRL;

	VDM_RGB2YUV_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32));
	VDM_RGB2YUV_CTRL.bits.vdm_cadj_en = vdm_cadj_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32),VDM_RGB2YUV_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvEn(HI_U32 vdm_rgb2yuv_en)
{
	U_VDM_RGB2YUV_CTRL VDM_RGB2YUV_CTRL;

	VDM_RGB2YUV_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32));
	VDM_RGB2YUV_CTRL.bits.vdm_rgb2yuv_en = vdm_rgb2yuv_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_CTRL.u32),VDM_RGB2YUV_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm00Rgb2yuv(HI_U32 vdm_00_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF0 VDM_RGB2YUV_COEF0;

	VDM_RGB2YUV_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF0.u32));
	VDM_RGB2YUV_COEF0.bits.vdm_00_rgb2yuv = vdm_00_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF0.u32),VDM_RGB2YUV_COEF0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm01Rgb2yuv(HI_U32 vdm_01_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF1 VDM_RGB2YUV_COEF1;

	VDM_RGB2YUV_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF1.u32));
	VDM_RGB2YUV_COEF1.bits.vdm_01_rgb2yuv = vdm_01_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF1.u32),VDM_RGB2YUV_COEF1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm02Rgb2yuv(HI_U32 vdm_02_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF2 VDM_RGB2YUV_COEF2;

	VDM_RGB2YUV_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF2.u32));
	VDM_RGB2YUV_COEF2.bits.vdm_02_rgb2yuv = vdm_02_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF2.u32),VDM_RGB2YUV_COEF2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm10Rgb2yuv(HI_U32 vdm_10_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF3 VDM_RGB2YUV_COEF3;

	VDM_RGB2YUV_COEF3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF3.u32));
	VDM_RGB2YUV_COEF3.bits.vdm_10_rgb2yuv = vdm_10_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF3.u32),VDM_RGB2YUV_COEF3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm11Rgb2yuv(HI_U32 vdm_11_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF4 VDM_RGB2YUV_COEF4;

	VDM_RGB2YUV_COEF4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF4.u32));
	VDM_RGB2YUV_COEF4.bits.vdm_11_rgb2yuv = vdm_11_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF4.u32),VDM_RGB2YUV_COEF4.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm12Rgb2yuv(HI_U32 vdm_12_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF5 VDM_RGB2YUV_COEF5;

	VDM_RGB2YUV_COEF5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF5.u32));
	VDM_RGB2YUV_COEF5.bits.vdm_12_rgb2yuv = vdm_12_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF5.u32),VDM_RGB2YUV_COEF5.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm20Rgb2yuv(HI_U32 vdm_20_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF6 VDM_RGB2YUV_COEF6;

	VDM_RGB2YUV_COEF6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF6.u32));
	VDM_RGB2YUV_COEF6.bits.vdm_20_rgb2yuv = vdm_20_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF6.u32),VDM_RGB2YUV_COEF6.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm21Rgb2yuv(HI_U32 vdm_21_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF7 VDM_RGB2YUV_COEF7;

	VDM_RGB2YUV_COEF7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF7.u32));
	VDM_RGB2YUV_COEF7.bits.vdm_21_rgb2yuv = vdm_21_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF7.u32),VDM_RGB2YUV_COEF7.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdm22Rgb2yuv(HI_U32 vdm_22_rgb2yuv)
{
	U_VDM_RGB2YUV_COEF8 VDM_RGB2YUV_COEF8;

	VDM_RGB2YUV_COEF8.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF8.u32));
	VDM_RGB2YUV_COEF8.bits.vdm_22_rgb2yuv = vdm_22_rgb2yuv;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_COEF8.u32),VDM_RGB2YUV_COEF8.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmCadjScale2p(HI_U32 vdm_cadj_scale2p)
{
	U_VDM_RGB2YUV_SCALE2P VDM_RGB2YUV_SCALE2P;

	VDM_RGB2YUV_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_SCALE2P.u32));
	VDM_RGB2YUV_SCALE2P.bits.vdm_cadj_scale2p = vdm_cadj_scale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_SCALE2P.u32),VDM_RGB2YUV_SCALE2P.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvscale2p(HI_U32 vdm_rgb2yuvscale2p)
{
	U_VDM_RGB2YUV_SCALE2P VDM_RGB2YUV_SCALE2P;

	VDM_RGB2YUV_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_SCALE2P.u32));
	VDM_RGB2YUV_SCALE2P.bits.vdm_rgb2yuvscale2p = vdm_rgb2yuvscale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_SCALE2P.u32),VDM_RGB2YUV_SCALE2P.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv0InDc(HI_U32 vdm_rgb2yuv_0_in_dc)
{
	U_VDM_RGB2YUV_IN_DC0 VDM_RGB2YUV_IN_DC0;

	VDM_RGB2YUV_IN_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC0.u32));
	VDM_RGB2YUV_IN_DC0.bits.vdm_rgb2yuv_0_in_dc = vdm_rgb2yuv_0_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC0.u32),VDM_RGB2YUV_IN_DC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv1InDc(HI_U32 vdm_rgb2yuv_1_in_dc)
{
	U_VDM_RGB2YUV_IN_DC1 VDM_RGB2YUV_IN_DC1;

	VDM_RGB2YUV_IN_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC1.u32));
	VDM_RGB2YUV_IN_DC1.bits.vdm_rgb2yuv_1_in_dc = vdm_rgb2yuv_1_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC1.u32),VDM_RGB2YUV_IN_DC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv2InDc(HI_U32 vdm_rgb2yuv_2_in_dc)
{
	U_VDM_RGB2YUV_IN_DC2 VDM_RGB2YUV_IN_DC2;

	VDM_RGB2YUV_IN_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC2.u32));
	VDM_RGB2YUV_IN_DC2.bits.vdm_rgb2yuv_2_in_dc = vdm_rgb2yuv_2_in_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_IN_DC2.u32),VDM_RGB2YUV_IN_DC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv0OutDc(HI_U32 vdm_rgb2yuv_0_out_dc)
{
	U_VDM_RGB2YUV_OUT_DC0 VDM_RGB2YUV_OUT_DC0;

	VDM_RGB2YUV_OUT_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC0.u32));
	VDM_RGB2YUV_OUT_DC0.bits.vdm_rgb2yuv_0_out_dc = vdm_rgb2yuv_0_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC0.u32),VDM_RGB2YUV_OUT_DC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv1OutDc(HI_U32 vdm_rgb2yuv_1_out_dc)
{
	U_VDM_RGB2YUV_OUT_DC1 VDM_RGB2YUV_OUT_DC1;

	VDM_RGB2YUV_OUT_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC1.u32));
	VDM_RGB2YUV_OUT_DC1.bits.vdm_rgb2yuv_1_out_dc = vdm_rgb2yuv_1_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC1.u32),VDM_RGB2YUV_OUT_DC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuv2OutDc(HI_U32 vdm_rgb2yuv_2_out_dc)
{
	U_VDM_RGB2YUV_OUT_DC2 VDM_RGB2YUV_OUT_DC2;

	VDM_RGB2YUV_OUT_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC2.u32));
	VDM_RGB2YUV_OUT_DC2.bits.vdm_rgb2yuv_2_out_dc = vdm_rgb2yuv_2_out_dc;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_OUT_DC2.u32),VDM_RGB2YUV_OUT_DC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvClipUvMin(HI_U32 vdm_rgb2yuv_clip_uv_min)
{
	U_VDM_RGB2YUV_MIN VDM_RGB2YUV_MIN;

	VDM_RGB2YUV_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MIN.u32));
	VDM_RGB2YUV_MIN.bits.vdm_rgb2yuv_clip_uv_min = vdm_rgb2yuv_clip_uv_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MIN.u32),VDM_RGB2YUV_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvClipYMin(HI_U32 vdm_rgb2yuv_clip_y_min)
{
	U_VDM_RGB2YUV_MIN VDM_RGB2YUV_MIN;

	VDM_RGB2YUV_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MIN.u32));
	VDM_RGB2YUV_MIN.bits.vdm_rgb2yuv_clip_y_min = vdm_rgb2yuv_clip_y_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MIN.u32),VDM_RGB2YUV_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvClipUvMax(HI_U32 vdm_rgb2yuv_clip_uv_max)
{
	U_VDM_RGB2YUV_MAX VDM_RGB2YUV_MAX;

	VDM_RGB2YUV_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MAX.u32));
	VDM_RGB2YUV_MAX.bits.vdm_rgb2yuv_clip_uv_max = vdm_rgb2yuv_clip_uv_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MAX.u32),VDM_RGB2YUV_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmRgb2yuvClipYMax(HI_U32 vdm_rgb2yuv_clip_y_max)
{
	U_VDM_RGB2YUV_MAX VDM_RGB2YUV_MAX;

	VDM_RGB2YUV_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MAX.u32));
	VDM_RGB2YUV_MAX.bits.vdm_rgb2yuv_clip_y_max = vdm_rgb2yuv_clip_y_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_RGB2YUV_MAX.u32),VDM_RGB2YUV_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherRoundUnlim(HI_U32 vdm_dither_round_unlim)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_round_unlim = vdm_dither_round_unlim;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherEn(HI_U32 vdm_dither_en)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_en = vdm_dither_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherMode(HI_U32 vdm_dither_mode)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_mode = vdm_dither_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherRound(HI_U32 vdm_dither_round)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_round = vdm_dither_round;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherDomainMode(HI_U32 vdm_dither_domain_mode)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_domain_mode = vdm_dither_domain_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherTapMode(HI_U32 vdm_dither_tap_mode)
{
	U_VDM_DITHER_CTRL VDM_DITHER_CTRL;

	VDM_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32));
	VDM_DITHER_CTRL.bits.vdm_dither_tap_mode = vdm_dither_tap_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_CTRL.u32),VDM_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedY0(HI_U32 vdm_dither_sed_y0)
{
	U_VDM_DITHER_SED_Y0 VDM_DITHER_SED_Y0;

	VDM_DITHER_SED_Y0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y0.u32));
	VDM_DITHER_SED_Y0.bits.vdm_dither_sed_y0 = vdm_dither_sed_y0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y0.u32),VDM_DITHER_SED_Y0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedU0(HI_U32 vdm_dither_sed_u0)
{
	U_VDM_DITHER_SED_U0 VDM_DITHER_SED_U0;

	VDM_DITHER_SED_U0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U0.u32));
	VDM_DITHER_SED_U0.bits.vdm_dither_sed_u0 = vdm_dither_sed_u0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U0.u32),VDM_DITHER_SED_U0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedV0(HI_U32 vdm_dither_sed_v0)
{
	U_VDM_DITHER_SED_V0 VDM_DITHER_SED_V0;

	VDM_DITHER_SED_V0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V0.u32));
	VDM_DITHER_SED_V0.bits.vdm_dither_sed_v0 = vdm_dither_sed_v0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V0.u32),VDM_DITHER_SED_V0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedW0(HI_U32 vdm_dither_sed_w0)
{
	U_VDM_DITHER_SED_W0 VDM_DITHER_SED_W0;

	VDM_DITHER_SED_W0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W0.u32));
	VDM_DITHER_SED_W0.bits.vdm_dither_sed_w0 = vdm_dither_sed_w0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W0.u32),VDM_DITHER_SED_W0.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedY1(HI_U32 vdm_dither_sed_y1)
{
	U_VDM_DITHER_SED_Y1 VDM_DITHER_SED_Y1;

	VDM_DITHER_SED_Y1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y1.u32));
	VDM_DITHER_SED_Y1.bits.vdm_dither_sed_y1 = vdm_dither_sed_y1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y1.u32),VDM_DITHER_SED_Y1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedU1(HI_U32 vdm_dither_sed_u1)
{
	U_VDM_DITHER_SED_U1 VDM_DITHER_SED_U1;

	VDM_DITHER_SED_U1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U1.u32));
	VDM_DITHER_SED_U1.bits.vdm_dither_sed_u1 = vdm_dither_sed_u1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U1.u32),VDM_DITHER_SED_U1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedV1(HI_U32 vdm_dither_sed_v1)
{
	U_VDM_DITHER_SED_V1 VDM_DITHER_SED_V1;

	VDM_DITHER_SED_V1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V1.u32));
	VDM_DITHER_SED_V1.bits.vdm_dither_sed_v1 = vdm_dither_sed_v1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V1.u32),VDM_DITHER_SED_V1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedW1(HI_U32 vdm_dither_sed_w1)
{
	U_VDM_DITHER_SED_W1 VDM_DITHER_SED_W1;

	VDM_DITHER_SED_W1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W1.u32));
	VDM_DITHER_SED_W1.bits.vdm_dither_sed_w1 = vdm_dither_sed_w1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W1.u32),VDM_DITHER_SED_W1.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedY2(HI_U32 vdm_dither_sed_y2)
{
	U_VDM_DITHER_SED_Y2 VDM_DITHER_SED_Y2;

	VDM_DITHER_SED_Y2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y2.u32));
	VDM_DITHER_SED_Y2.bits.vdm_dither_sed_y2 = vdm_dither_sed_y2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y2.u32),VDM_DITHER_SED_Y2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedU2(HI_U32 vdm_dither_sed_u2)
{
	U_VDM_DITHER_SED_U2 VDM_DITHER_SED_U2;

	VDM_DITHER_SED_U2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U2.u32));
	VDM_DITHER_SED_U2.bits.vdm_dither_sed_u2 = vdm_dither_sed_u2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U2.u32),VDM_DITHER_SED_U2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedV2(HI_U32 vdm_dither_sed_v2)
{
	U_VDM_DITHER_SED_V2 VDM_DITHER_SED_V2;

	VDM_DITHER_SED_V2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V2.u32));
	VDM_DITHER_SED_V2.bits.vdm_dither_sed_v2 = vdm_dither_sed_v2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V2.u32),VDM_DITHER_SED_V2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedW2(HI_U32 vdm_dither_sed_w2)
{
	U_VDM_DITHER_SED_W2 VDM_DITHER_SED_W2;

	VDM_DITHER_SED_W2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W2.u32));
	VDM_DITHER_SED_W2.bits.vdm_dither_sed_w2 = vdm_dither_sed_w2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W2.u32),VDM_DITHER_SED_W2.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedY3(HI_U32 vdm_dither_sed_y3)
{
	U_VDM_DITHER_SED_Y3 VDM_DITHER_SED_Y3;

	VDM_DITHER_SED_Y3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y3.u32));
	VDM_DITHER_SED_Y3.bits.vdm_dither_sed_y3 = vdm_dither_sed_y3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_Y3.u32),VDM_DITHER_SED_Y3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedU3(HI_U32 vdm_dither_sed_u3)
{
	U_VDM_DITHER_SED_U3 VDM_DITHER_SED_U3;

	VDM_DITHER_SED_U3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U3.u32));
	VDM_DITHER_SED_U3.bits.vdm_dither_sed_u3 = vdm_dither_sed_u3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_U3.u32),VDM_DITHER_SED_U3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedV3(HI_U32 vdm_dither_sed_v3)
{
	U_VDM_DITHER_SED_V3 VDM_DITHER_SED_V3;

	VDM_DITHER_SED_V3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V3.u32));
	VDM_DITHER_SED_V3.bits.vdm_dither_sed_v3 = vdm_dither_sed_v3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_V3.u32),VDM_DITHER_SED_V3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherSedW3(HI_U32 vdm_dither_sed_w3)
{
	U_VDM_DITHER_SED_W3 VDM_DITHER_SED_W3;

	VDM_DITHER_SED_W3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W3.u32));
	VDM_DITHER_SED_W3.bits.vdm_dither_sed_w3 = vdm_dither_sed_w3;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_SED_W3.u32),VDM_DITHER_SED_W3.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherThrMax(HI_U32 vdm_dither_thr_max)
{
	U_VDM_DITHER_THR VDM_DITHER_THR;

	VDM_DITHER_THR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_THR.u32));
	VDM_DITHER_THR.bits.vdm_dither_thr_max = vdm_dither_thr_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_THR.u32),VDM_DITHER_THR.u32);

	return ;
}


HI_VOID VDP_HIHDR_SetVdmDitherThrMin(HI_U32 vdm_dither_thr_min)
{
	U_VDM_DITHER_THR VDM_DITHER_THR;

	VDM_DITHER_THR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VDM_DITHER_THR.u32));
	VDM_DITHER_THR.bits.vdm_dither_thr_min = vdm_dither_thr_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VDM_DITHER_THR.u32),VDM_DITHER_THR.u32);

	return ;
}

HI_VOID VDP_VP0_SetCsc0Mode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
	VDP_CSC_COEF_S    st_csc_coef;
	VDP_CSC_DC_COEF_S st_csc_dc_coef;
	HI_U32 u32Pre   = 1 << 13;
	HI_U32 u32InDcPre = 4;//1:8bit; 4:10bit
	HI_U32 u32OutDcPre = 16;//1:8bit; 4:10bit;16:12bit

	HI_U32 yuv2rgb0scale2p   = 11;
	HI_U32 yuv2rgb0_clip_min = 16  * u32OutDcPre;//0;//
	HI_U32 yuv2rgb0_clip_max = 235 * u32OutDcPre;//4095;//

  if(enCscMode == VDP_CSC_RGB2YUV_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)(0.257  * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(0.504  * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)(0.098  * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.148 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.291 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439  * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439  * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.368 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.071 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.002 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.596 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.391 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.813 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-2.018  * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.001  * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_RGB2YUV_709)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 0.183 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.614 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.062 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.101 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.338 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.399 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.040 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 16  * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_709)//limit range inverse to rgb2yuv
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0     * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.793 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.213 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.534 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 2.115 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0     * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_709_601)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.100 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.191 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 0.990 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.110 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.072 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0.984 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_601_709)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.116 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.208 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 1.018 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.114 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 0.074 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 1.025 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
	else if(enCscMode == VDP_CSC_YUV2YUV_MIN)
	{
  		st_csc_coef.csc_coef00     = 0;
  		st_csc_coef.csc_coef01     = 0;
  		st_csc_coef.csc_coef02     = 0;
  		st_csc_coef.csc_coef10     = 0;
  		st_csc_coef.csc_coef11     = 0;
  		st_csc_coef.csc_coef12     = 0;
  		st_csc_coef.csc_coef20     = 0;
  		st_csc_coef.csc_coef21     = 0;
  		st_csc_coef.csc_coef22     = 0;
  		st_csc_dc_coef.csc_in_dc0  = 0;
  		st_csc_dc_coef.csc_in_dc1  = 0;
  		st_csc_dc_coef.csc_in_dc2  = 0;
  		st_csc_dc_coef.csc_out_dc0 = 0;
  		st_csc_dc_coef.csc_out_dc1 = 0;
  		st_csc_dc_coef.csc_out_dc2 =  0;
	}
	else
	{
  	  VDP_PRINT("CSC MODE IS NOT INCLUDED !!!!!!!!!!!!!!!!!!!!!!\n");
  		st_csc_coef.csc_coef00     = 1 * u32Pre;
  		st_csc_coef.csc_coef01     = 0 * u32Pre;
  		st_csc_coef.csc_coef02     = 0 * u32Pre;
  		st_csc_coef.csc_coef10     = 0 * u32Pre;
  		st_csc_coef.csc_coef11     = 1 * u32Pre;
  		st_csc_coef.csc_coef12     = 0 * u32Pre;
  		st_csc_coef.csc_coef20     = 0 * u32Pre;
  		st_csc_coef.csc_coef21     = 0 * u32Pre;
  		st_csc_coef.csc_coef22     = 1 * u32Pre;
  		st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
	}

	VDP_HIHDR_SetVdmV0Yuv2rgbscale2p(yuv2rgb0scale2p);
  VDP_HIHDR_SetVdmV0Yuv2rgbClipMin(yuv2rgb0_clip_min);
  VDP_HIHDR_SetVdmV0Yuv2rgbClipMax(yuv2rgb0_clip_max);

	VDP_HIHDR_SetVdm00Yuv2rgb( st_csc_coef.csc_coef00);
	VDP_HIHDR_SetVdm01Yuv2rgb( st_csc_coef.csc_coef01);
	VDP_HIHDR_SetVdm02Yuv2rgb( st_csc_coef.csc_coef02);
	VDP_HIHDR_SetVdm03Yuv2rgb( st_csc_coef.csc_coef10);
	VDP_HIHDR_SetVdm04Yuv2rgb( st_csc_coef.csc_coef11);
	VDP_HIHDR_SetVdm05Yuv2rgb( st_csc_coef.csc_coef12);
	VDP_HIHDR_SetVdm06Yuv2rgb( st_csc_coef.csc_coef20);
	VDP_HIHDR_SetVdm07Yuv2rgb( st_csc_coef.csc_coef21);
	VDP_HIHDR_SetVdm08Yuv2rgb( st_csc_coef.csc_coef22);

	VDP_HIHDR_SetVdmYuv2rgb00InDc( st_csc_dc_coef.csc_in_dc0);
	VDP_HIHDR_SetVdmYuv2rgb01InDc( st_csc_dc_coef.csc_in_dc1);
	VDP_HIHDR_SetVdmYuv2rgb02InDc( st_csc_dc_coef.csc_in_dc2);
	VDP_HIHDR_SetVdmYuv2rgb00OutDc( st_csc_dc_coef.csc_out_dc0);
	VDP_HIHDR_SetVdmYuv2rgb01OutDc( st_csc_dc_coef.csc_out_dc1);
	VDP_HIHDR_SetVdmYuv2rgb02OutDc( st_csc_dc_coef.csc_out_dc2);

	return ;
}

HI_VOID VDP_VP0_SetCsc1Mode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
	VDP_CSC_COEF_S    st_csc_coef;
	VDP_CSC_DC_COEF_S st_csc_dc_coef;
	HI_U32 u32Pre   = 1 << 13;
	HI_U32 u32InDcPre = 4;//1:8bit; 4:10bit
	HI_U32 u32OutDcPre = 16;//1:8bit; 4:10bit;16:12bit

	HI_U32 yuv2rgb1scale2p   = 11;
	HI_U32 yuv2rgb1_clip_min = 16  * u32OutDcPre;//0;//
	HI_U32 yuv2rgb1_clip_max = 235 * u32OutDcPre;//4095;//

  if(enCscMode == VDP_CSC_RGB2YUV_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)(0.257  * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(0.504  * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)(0.098  * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.148 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.291 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439  * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439  * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.368 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.071 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.002 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.596 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.391 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.813 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-2.018  * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.001  * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_RGB2YUV_709)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 0.183 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.614 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.062 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.101 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.338 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.399 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.040 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 16  * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_709)//limit range inverse to rgb2yuv
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0     * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.793 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.213 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.534 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 2.115 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0     * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_709_601)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.100 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.191 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 0.990 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.110 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.072 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0.984 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_601_709)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.116 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.208 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 1.018 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.114 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 0.074 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 1.025 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
	else if(enCscMode == VDP_CSC_YUV2YUV_MIN)
	{
  		st_csc_coef.csc_coef00     = 0;
  		st_csc_coef.csc_coef01     = 0;
  		st_csc_coef.csc_coef02     = 0;
  		st_csc_coef.csc_coef10     = 0;
  		st_csc_coef.csc_coef11     = 0;
  		st_csc_coef.csc_coef12     = 0;
  		st_csc_coef.csc_coef20     = 0;
  		st_csc_coef.csc_coef21     = 0;
  		st_csc_coef.csc_coef22     = 0;
  		st_csc_dc_coef.csc_in_dc0  = 0;
  		st_csc_dc_coef.csc_in_dc1  = 0;
  		st_csc_dc_coef.csc_in_dc2  = 0;
  		st_csc_dc_coef.csc_out_dc0 = 0;
  		st_csc_dc_coef.csc_out_dc1 = 0;
  		st_csc_dc_coef.csc_out_dc2 =  0;
	}
	else
	{
  	  VDP_PRINT("CSC MODE IS NOT INCLUDED !!!!!!!!!!!!!!!!!!!!!!\n");
  		st_csc_coef.csc_coef00     = 1 * u32Pre;
  		st_csc_coef.csc_coef01     = 0 * u32Pre;
  		st_csc_coef.csc_coef02     = 0 * u32Pre;
  		st_csc_coef.csc_coef10     = 0 * u32Pre;
  		st_csc_coef.csc_coef11     = 1 * u32Pre;
  		st_csc_coef.csc_coef12     = 0 * u32Pre;
  		st_csc_coef.csc_coef20     = 0 * u32Pre;
  		st_csc_coef.csc_coef21     = 0 * u32Pre;
  		st_csc_coef.csc_coef22     = 1 * u32Pre;
  		st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
	}

	VDP_HIHDR_SetVdmV1Yuv2rgbscale2p(yuv2rgb1scale2p);
  VDP_HIHDR_SetVdmV1Yuv2rgbClipMin(yuv2rgb1_clip_min);
  VDP_HIHDR_SetVdmV1Yuv2rgbClipMax(yuv2rgb1_clip_max);

	VDP_HIHDR_SetVdm10Yuv2rgb(st_csc_coef.csc_coef00);
	VDP_HIHDR_SetVdm11Yuv2rgb(st_csc_coef.csc_coef01);
	VDP_HIHDR_SetVdm12Yuv2rgb(st_csc_coef.csc_coef02);
	VDP_HIHDR_SetVdm13Yuv2rgb(st_csc_coef.csc_coef10);
	VDP_HIHDR_SetVdm14Yuv2rgb(st_csc_coef.csc_coef11);
	VDP_HIHDR_SetVdm15Yuv2rgb(st_csc_coef.csc_coef12);
	VDP_HIHDR_SetVdm16Yuv2rgb(st_csc_coef.csc_coef20);
	VDP_HIHDR_SetVdm17Yuv2rgb(st_csc_coef.csc_coef21);
	VDP_HIHDR_SetVdm18Yuv2rgb(st_csc_coef.csc_coef22);

	VDP_HIHDR_SetVdmYuv2rgb10InDc( st_csc_dc_coef.csc_in_dc0);
	VDP_HIHDR_SetVdmYuv2rgb11InDc( st_csc_dc_coef.csc_in_dc1);
	VDP_HIHDR_SetVdmYuv2rgb12InDc( st_csc_dc_coef.csc_in_dc2);
	VDP_HIHDR_SetVdmYuv2rgb10OutDc( st_csc_dc_coef.csc_out_dc0);
	VDP_HIHDR_SetVdmYuv2rgb11OutDc( st_csc_dc_coef.csc_out_dc1);
	VDP_HIHDR_SetVdmYuv2rgb12OutDc( st_csc_dc_coef.csc_out_dc2);

	return ;
}


HI_VOID VDP_VP0_SetCsc0Csc1Mode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
	VDP_CSC_COEF_S    st_csc_coef;
	VDP_CSC_DC_COEF_S st_csc_dc_coef;
	HI_U32 u32Pre   = 1 << 13;
	HI_U32 u32InDcPre = 4;//1:8bit; 4:10bit
	HI_U32 u32OutDcPre = 16;//1:8bit; 4:10bit;16:12bit

	HI_U32 yuv2rgb0scale2p   = 11;
	HI_U32 yuv2rgb0_clip_min = 16  * u32OutDcPre;//0;//
	HI_U32 yuv2rgb0_clip_max = 235 * u32OutDcPre;//4095;//

	HI_U32 yuv2rgb1scale2p   = 11;
	HI_U32 yuv2rgb1_clip_min = 16  * u32OutDcPre;//0;//
	HI_U32 yuv2rgb1_clip_max = 235 * u32OutDcPre;//4095;//

  if(enCscMode == VDP_CSC_RGB2YUV_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)(0.257  * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(0.504  * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)(0.098  * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.148 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.291 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439  * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439  * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.368 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.071 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_601)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.002 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.596 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.391 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.813 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-2.018  * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.001  * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_RGB2YUV_709)//limit range
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 0.183 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.614 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.062 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(-0.101 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.338 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.439 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 0.439 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.399 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)(-0.040 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = 0 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = 0 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 16  * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2RGB_709)//limit range inverse to rgb2yuv
  {
      st_csc_coef.csc_coef00     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0     * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 1.793 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)(-0.213 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.534 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)( 1.164 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 2.115 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0     * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 = 0 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 = 0 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_709_601)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)( 0.100 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.191 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 0.990 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)(-0.110 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)(-0.072 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 0.984 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
  else if(enCscMode == VDP_CSC_YUV2YUV_601_709)
  {
      st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
      st_csc_coef.csc_coef01     = (HI_S32)(-0.116 * u32Pre);
      st_csc_coef.csc_coef02     = (HI_S32)( 0.208 * u32Pre);

      st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef11     = (HI_S32)( 1.018 * u32Pre);
      st_csc_coef.csc_coef12     = (HI_S32)( 0.114 * u32Pre);

      st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
      st_csc_coef.csc_coef21     = (HI_S32)( 0.074 * u32Pre);
      st_csc_coef.csc_coef22     = (HI_S32)( 1.025 * u32Pre);

      st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
      st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
      st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;

      st_csc_dc_coef.csc_out_dc0 =   16 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc1 =  128 * u32OutDcPre;
      st_csc_dc_coef.csc_out_dc2 =  128 * u32OutDcPre;
  }
	else if(enCscMode == VDP_CSC_YUV2YUV_MIN)
	{
  		st_csc_coef.csc_coef00     = 0;
  		st_csc_coef.csc_coef01     = 0;
  		st_csc_coef.csc_coef02     = 0;
  		st_csc_coef.csc_coef10     = 0;
  		st_csc_coef.csc_coef11     = 0;
  		st_csc_coef.csc_coef12     = 0;
  		st_csc_coef.csc_coef20     = 0;
  		st_csc_coef.csc_coef21     = 0;
  		st_csc_coef.csc_coef22     = 0;
  		st_csc_dc_coef.csc_in_dc0  = 0;
  		st_csc_dc_coef.csc_in_dc1  = 0;
  		st_csc_dc_coef.csc_in_dc2  = 0;
  		st_csc_dc_coef.csc_out_dc0 = 0;
  		st_csc_dc_coef.csc_out_dc1 = 0;
  		st_csc_dc_coef.csc_out_dc2 =  0;
	}
	else
	{
  	  VDP_PRINT("CSC MODE IS NOT INCLUDED !!!!!!!!!!!!!!!!!!!!!!\n");
  		st_csc_coef.csc_coef00     = 1 * u32Pre;
  		st_csc_coef.csc_coef01     = 0 * u32Pre;
  		st_csc_coef.csc_coef02     = 0 * u32Pre;
  		st_csc_coef.csc_coef10     = 0 * u32Pre;
  		st_csc_coef.csc_coef11     = 1 * u32Pre;
  		st_csc_coef.csc_coef12     = 0 * u32Pre;
  		st_csc_coef.csc_coef20     = 0 * u32Pre;
  		st_csc_coef.csc_coef21     = 0 * u32Pre;
  		st_csc_coef.csc_coef22     = 1 * u32Pre;
  		st_csc_dc_coef.csc_in_dc0  = -16  * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc1  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_in_dc2  = -128 * u32InDcPre;
  		st_csc_dc_coef.csc_out_dc0 =  16 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc1 = 128 * u32OutDcPre;
  		st_csc_dc_coef.csc_out_dc2 = 128 * u32OutDcPre;
	}

	VDP_HIHDR_SetVdmV0Yuv2rgbscale2p(yuv2rgb0scale2p);
  VDP_HIHDR_SetVdmV0Yuv2rgbClipMin(yuv2rgb0_clip_min);
  VDP_HIHDR_SetVdmV0Yuv2rgbClipMax(yuv2rgb0_clip_max);

	VDP_HIHDR_SetVdmV1Yuv2rgbscale2p(yuv2rgb1scale2p);
  VDP_HIHDR_SetVdmV1Yuv2rgbClipMin(yuv2rgb1_clip_min);
  VDP_HIHDR_SetVdmV1Yuv2rgbClipMax(yuv2rgb1_clip_max);

	if(u32Data==0)
	{
		VDP_HIHDR_SetVdm00Yuv2rgb( st_csc_coef.csc_coef00);
		VDP_HIHDR_SetVdm01Yuv2rgb( st_csc_coef.csc_coef01);
		VDP_HIHDR_SetVdm02Yuv2rgb( st_csc_coef.csc_coef02);
		VDP_HIHDR_SetVdm03Yuv2rgb( st_csc_coef.csc_coef10);
		VDP_HIHDR_SetVdm04Yuv2rgb( st_csc_coef.csc_coef11);
		VDP_HIHDR_SetVdm05Yuv2rgb( st_csc_coef.csc_coef12);
		VDP_HIHDR_SetVdm06Yuv2rgb( st_csc_coef.csc_coef20);
		VDP_HIHDR_SetVdm07Yuv2rgb( st_csc_coef.csc_coef21);
		VDP_HIHDR_SetVdm08Yuv2rgb( st_csc_coef.csc_coef22);

		VDP_HIHDR_SetVdmYuv2rgb00InDc( st_csc_dc_coef.csc_in_dc0);
		VDP_HIHDR_SetVdmYuv2rgb01InDc( st_csc_dc_coef.csc_in_dc1);
		VDP_HIHDR_SetVdmYuv2rgb02InDc( st_csc_dc_coef.csc_in_dc2);
		VDP_HIHDR_SetVdmYuv2rgb00OutDc( st_csc_dc_coef.csc_out_dc0);
		VDP_HIHDR_SetVdmYuv2rgb01OutDc( st_csc_dc_coef.csc_out_dc1);
		VDP_HIHDR_SetVdmYuv2rgb02OutDc( st_csc_dc_coef.csc_out_dc2);
	}
	else if(u32Data==1)
	{
		VDP_HIHDR_SetVdm10Yuv2rgb(st_csc_coef.csc_coef00);
		VDP_HIHDR_SetVdm11Yuv2rgb(st_csc_coef.csc_coef01);
		VDP_HIHDR_SetVdm12Yuv2rgb(st_csc_coef.csc_coef02);
		VDP_HIHDR_SetVdm13Yuv2rgb(st_csc_coef.csc_coef10);
		VDP_HIHDR_SetVdm14Yuv2rgb(st_csc_coef.csc_coef11);
		VDP_HIHDR_SetVdm15Yuv2rgb(st_csc_coef.csc_coef12);
		VDP_HIHDR_SetVdm16Yuv2rgb(st_csc_coef.csc_coef20);
		VDP_HIHDR_SetVdm17Yuv2rgb(st_csc_coef.csc_coef21);
		VDP_HIHDR_SetVdm18Yuv2rgb(st_csc_coef.csc_coef22);

		VDP_HIHDR_SetVdmYuv2rgb10InDc( st_csc_dc_coef.csc_in_dc0);
		VDP_HIHDR_SetVdmYuv2rgb11InDc( st_csc_dc_coef.csc_in_dc1);
		VDP_HIHDR_SetVdmYuv2rgb12InDc( st_csc_dc_coef.csc_in_dc2);
		VDP_HIHDR_SetVdmYuv2rgb10OutDc( st_csc_dc_coef.csc_out_dc0);
		VDP_HIHDR_SetVdmYuv2rgb11OutDc( st_csc_dc_coef.csc_out_dc1);
		VDP_HIHDR_SetVdmYuv2rgb12OutDc( st_csc_dc_coef.csc_out_dc2);
	}
	return ;
}

