/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_vpsscsc.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/02/17
  Description   :

******************************************************************************/
#include "pq_hal_vpsscsc.h"

HI_S32 pq_hal_UpdateVpssCscCoef(HI_U32 u32HandleNo, HI_PQ_CSC_COEF_S *pstCscCoef)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_FMTC_CSC_COEF_0.bits.csc_coef_00 = pstCscCoef->csc_coef00;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_0.bits.csc_coef_01 = pstCscCoef->csc_coef01;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_1.bits.csc_coef_02 = pstCscCoef->csc_coef02;

    pstVpssVirReg->VPSS_FMTC_CSC_COEF_1.bits.csc_coef_10 = pstCscCoef->csc_coef10;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_2.bits.csc_coef_11 = pstCscCoef->csc_coef11;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_2.bits.csc_coef_12 = pstCscCoef->csc_coef12;

    pstVpssVirReg->VPSS_FMTC_CSC_COEF_3.bits.csc_coef_20 = pstCscCoef->csc_coef20;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_3.bits.csc_coef_21 = pstCscCoef->csc_coef21;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_4.bits.csc_coef_22 = pstCscCoef->csc_coef22;

    pqprint(PQ_PRN_VPSSCSC, " %d; %d; %d; %d; %d; %d; %d; %d; %d \n",
            pstCscCoef->csc_coef00,
            pstCscCoef->csc_coef01,
            pstCscCoef->csc_coef02,
            pstCscCoef->csc_coef10,
            pstCscCoef->csc_coef11,
            pstCscCoef->csc_coef12,
            pstCscCoef->csc_coef20,
            pstCscCoef->csc_coef21,
            pstCscCoef->csc_coef22);

    return HI_SUCCESS;
}

HI_S32 pq_hal_UpdateVpssCscDcCoef(HI_U32 u32HandleNo, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    PQ_CHECK_NULL_PTR(pstCscDcCoef);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_FMTC_CSC_COEF_5.bits.csc_in_dc0  = pstCscDcCoef->csc_in_dc0;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_5.bits.csc_in_dc1  = pstCscDcCoef->csc_in_dc1;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_6.bits.csc_in_dc2  = pstCscDcCoef->csc_in_dc2;

    pstVpssVirReg->VPSS_FMTC_CSC_COEF_6.bits.csc_out_dc0 = pstCscDcCoef->csc_out_dc0;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_7.bits.csc_out_dc1 = pstCscDcCoef->csc_out_dc1;
    pstVpssVirReg->VPSS_FMTC_CSC_COEF_7.bits.csc_out_dc2 = pstCscDcCoef->csc_out_dc2;

    pqprint(PQ_PRN_VPSSCSC, " %d; %d; %d; %d; %d; %d; %d; %d; %d \n",
            pstCscDcCoef->csc_in_dc0,
            pstCscDcCoef->csc_in_dc1,
            pstCscDcCoef->csc_in_dc2,
            pstCscDcCoef->csc_out_dc0,
            pstCscDcCoef->csc_out_dc1,
            pstCscDcCoef->csc_out_dc2);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVpssCscEnable(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_csc_en = bEnable;
    pqprint(PQ_PRN_VPSSCSC, "PQ_HAL_UpdateVpssCscCoef vpss_csc_en == %d; ", pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_csc_en);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVpssCscDemoEnable(HI_U32 u32HandleNo, HI_BOOL bVpssDemoEn)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);
    pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_en = bVpssDemoEn;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVpssCscDemoMode(HI_U32 u32HandleNo, VPSSCSC_DEMO_MODE_E enVpssCscDemoMode)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);
    pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_mode = enVpssCscDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_UpdateVpssCsc(HI_U32 u32HandleNo, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    HI_S32 s32Ret;

    s32Ret = pq_hal_UpdateVpssCscCoef(u32HandleNo, pstCscCoef);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("ERR: PQ_HAL_UpdateVpssCscCoef failed!\n");
        return HI_FAILURE;
    }

    s32Ret = pq_hal_UpdateVpssCscDcCoef(u32HandleNo, pstCscDcCoef);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("ERR: PQ_HAL_UpdateVpssCscDcCoef failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


