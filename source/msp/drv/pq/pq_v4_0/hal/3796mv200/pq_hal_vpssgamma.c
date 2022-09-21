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
#include "drv_pq_comm.h"
#include "pq_hal_vpssgamma.h"


HI_S32 PQ_HAL_SetVpssGmmEnable(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_gamma_en = 0;//bEnable;
    pqprint(PQ_PRN_VPSSCSC, "PQ_HAL_SetVpssGmmEnable vpss_gamma_en == %d; ", pstVpssVirReg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_gamma_en);

    return HI_SUCCESS;
}

HI_S32 pq_hal_UpdateVpssGammaCoefY(HI_U32 u32HandleNo, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;
    HI_U32 i = 0;

    PQ_CHECK_NULL_PTR(pstVpssGammaCoef);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    /* VPSS_FMTC_GAMMA_YLUT_0-> VPSS_FMTC_GAMMA_YLUT_7 cfg set */
    for (i = 0; i < 8; i++)
    {
        *((&(pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_0.u32) + i * 1 )) =
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutY[i * 4 + 0]) << 0) & 0xff) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutY[i * 4 + 1]) << 8) & 0xff00) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutY[i * 4 + 2]) << 16) & 0xff0000) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutY[i * 4 + 3]) << 24) & 0xff000000) ;
    }

    pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_8.bits.gamma_y_lut_32    =  pstVpssGammaCoef->u32aGammaLutY[32];

    pqprint(PQ_PRN_VPSSCSC, " %d; %d; %d; %d; %d; %d; %d; %d; %d \n",
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_00,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_01,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_02,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_0.bits.gamma_y_lut_03,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_04,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_05,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_06,
            pstVpssVirReg->VPSS_FMTC_GAMMA_YLUT_1.bits.gamma_y_lut_07);


    return HI_SUCCESS;
}

HI_S32 pq_hal_UpdateVpssGammaCoefU(HI_U32 u32HandleNo, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;
    HI_U32 i = 0;

    PQ_CHECK_NULL_PTR(pstVpssGammaCoef);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    /* VPSS_FMTC_GAMMA_ULUT_0-> VPSS_FMTC_GAMMA_ULUT_7 cfg set */
    for (i = 0; i < 8; i++)
    {
        *((&(pstVpssVirReg->VPSS_FMTC_GAMMA_ULUT_0.u32) + i * 1 )) =
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutU[i * 4 + 0]) << 0) & 0xff) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutU[i * 4 + 1]) << 8) & 0xff00) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutU[i * 4 + 2]) << 16) & 0xff0000) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutU[i * 4 + 3]) << 24) & 0xff000000) ;
    }

    pstVpssVirReg->VPSS_FMTC_GAMMA_ULUT_8.bits.gamma_u_lut_32    =  pstVpssGammaCoef->u32aGammaLutU[32];

    return HI_SUCCESS;
}

HI_S32 pq_hal_UpdateVpssGammaCoefV(HI_U32 u32HandleNo, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef)
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;
    HI_U32 i = 0;

    PQ_CHECK_NULL_PTR(pstVpssGammaCoef);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    /* VPSS_FMTC_GAMMA_VLUT_0-> VPSS_FMTC_GAMMA_VLUT_7 cfg set */
    for (i = 0; i < 8; i++)
    {
        *((&(pstVpssVirReg->VPSS_FMTC_GAMMA_VLUT_0.u32) + i * 1 )) =
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutV[i * 4 + 0]) << 0) & 0xff) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutV[i * 4 + 1]) << 8) & 0xff00) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutV[i * 4 + 2]) << 16) & 0xff0000) |
            (((HI_U32)(pstVpssGammaCoef->u32aGammaLutV[i * 4 + 3]) << 24) & 0xff000000) ;
    }

    pstVpssVirReg->VPSS_FMTC_GAMMA_VLUT_8.bits.gamma_v_lut_32    =  pstVpssGammaCoef->u32aGammaLutV[32];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_UpdateVpssGamma(HI_U32 u32HandleNo, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef)
{
    HI_S32 s32Ret;
    /* gamma y lut */
    s32Ret = pq_hal_UpdateVpssGammaCoefY(u32HandleNo, pstVpssGammaCoef);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("ERR: pq_hal_UpdateVpssGammaCoefY failed!\n");
        return HI_FAILURE;
    }

    /* gamma u lut */
    s32Ret = pq_hal_UpdateVpssGammaCoefU(u32HandleNo, pstVpssGammaCoef);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("ERR: pq_hal_UpdateVpssGammaCoefU failed!\n");
        return HI_FAILURE;
    }

    /* gamma v lut */
    s32Ret = pq_hal_UpdateVpssGammaCoefV(u32HandleNo, pstVpssGammaCoef);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("ERR: pq_hal_UpdateVpssGammaCoefV failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

