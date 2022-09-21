// *****************************************************************************
//
// Copyright(c) 2015,Hisilicon Technologies Co., Ltd.
// All Rights Reserved
//
// Project name : VDP
// File Name    : coef.cpp
// Author       : sdk
// Email        : zhanglun1@hisilicon.com
// Date         : 2015/7/17
//
// Module Name  : COEF.CPP
// -----------------------------------------------------------------------------
// Abstract     :
//code_template.v*
//
// *****************************************************************************
// Called By    : TOP
// Modification History
// -----------------------------------------------------------------------------
// $Log :     $
//
//
// --=========================================================================--

#ifndef __VDM_COEF_H__
#define __VDM_COEF_H__


#include "hi_type.h"
#include "VdpHiHDR_cfg.h"



#ifndef  __DISP_PLATFORM_BOOT__
HI_VOID Vdp_Drv_SetHdrVdmCoef_gmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Degmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Tmapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Smapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetSdrVdmCoef_gmm(HIHDR_SCENE_MODE_E enHiHdrMode);
HI_VOID Vdp_Drv_SetSdrVdmCoef_Degmm(HIHDR_SCENE_MODE_E enHiHdrMode);

#endif

#endif
