/******************************************************************************
*
* Copyright (C) 2014-2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_csc.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/02/17
  Description   :

******************************************************************************/
#include <linux/string.h>      /* memcpy() */
#include "pq_mng_vpssgamma.h"
#include "pq_hal_comm.h"
#include "hi_math.h"

static HI_BOOL  sg_bVpssGmmEn        = HI_FALSE;
static HI_DRV_PQ_VP_TYPE_E sg_enVpsVPGmmType = HI_DRV_PQ_VP_TYPE_BUTT ;

static HI_S32 sg_VpssGammaClutY[HI_DRV_PQ_VIDEOPHONE_MODE_BUTT][HI_PQ_VPSSGAMA_LUT_SIZE] =
{
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*0*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*1*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*2*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*3*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*4*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*5*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*6*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    } /*7*/
};

static HI_S32 sg_VpssGammaClutU[HI_DRV_PQ_VIDEOPHONE_MODE_BUTT][HI_PQ_VPSSGAMA_LUT_SIZE] =
{
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*0*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*1*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*2*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*3*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*4*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*5*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*6*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    } /*7*/
};
static HI_S32 sg_VpssGammaClutV[HI_DRV_PQ_VIDEOPHONE_MODE_BUTT][HI_PQ_VPSSGAMA_LUT_SIZE] =
{
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*0*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*1*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*2*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*3*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*4*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*5*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    }, /*6*/
    {
        0,   8,   16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96,  104, 112, 120,
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255
    } /*7*/
};


/* Set CSC Tran Mode:
   1. dc value order is right; but as the tran of Dobly, out dc is opposite to original data;
      we set right data in pq code, cbb tran it;
   2. we set precision at 10, with cbb;
   */
static HI_S32 pq_mng_GetVpssGammaModeCoef(HI_DRV_PQ_VP_MODE_E enPqVPImageMode, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef)
{
    if (pstVpssGammaCoef == HI_NULL)
    {
        HI_ERR_PQ("pq_mng_GetVpssGammaModeCoef is NULL!\n");
        return HI_FAILURE;
    }

    memcpy(pstVpssGammaCoef->u32aGammaLutY, sg_VpssGammaClutY[enPqVPImageMode], HI_PQ_VPSSGAMA_LUT_SIZE * sizeof(pstVpssGammaCoef->u32aGammaLutY[0]));
    memcpy(pstVpssGammaCoef->u32aGammaLutU, sg_VpssGammaClutU[enPqVPImageMode], HI_PQ_VPSSGAMA_LUT_SIZE * sizeof(pstVpssGammaCoef->u32aGammaLutU[0]));
    memcpy(pstVpssGammaCoef->u32aGammaLutV, sg_VpssGammaClutV[enPqVPImageMode], HI_PQ_VPSSGAMA_LUT_SIZE * sizeof(pstVpssGammaCoef->u32aGammaLutV[0]));

    pqprint(PQ_PRN_VPSSGAMMA, "pq_mng_GetVpssGammaModeCoef Y Y U U V V enPqVPImageMode %d; %d; %d; %d; %d; %d; %d;\n",
            pstVpssGammaCoef->u32aGammaLutY[0],
            pstVpssGammaCoef->u32aGammaLutY[1],
            pstVpssGammaCoef->u32aGammaLutU[0],
            pstVpssGammaCoef->u32aGammaLutU[1],
            pstVpssGammaCoef->u32aGammaLutV[0],
            pstVpssGammaCoef->u32aGammaLutV[1],
            enPqVPImageMode);

    return HI_SUCCESS;
}

HI_S32 pq_mng_SetVpssGmmEnable(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    PQ_STATUS_S stPqStatus = {0};
    HI_UNUSED(bEnable);

    PQ_COMM_GetPqStatus(&stPqStatus);
    if ((PQ_IMAGE_MODE_VIDEOPHONE == stPqStatus.enImageMode) &&
        ((HI_DRV_PQ_VP_TYPE_PREVIEW == sg_enVpsVPGmmType) || (HI_DRV_PQ_VP_TYPE_REMOTE == sg_enVpsVPGmmType)))
    {
        sg_bVpssGmmEn = HI_TRUE;
    }
    else
    {
        sg_bVpssGmmEn = HI_FALSE;
    }

    PQ_HAL_SetVpssGmmEnable(u32HandleNo, sg_bVpssGmmEn);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_UpdateVpssGammaCoef(HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode)
{
    HAL_PQ_VPSSGAMMA_COEF_S stVpssGammaCoef ;
    memset(&stVpssGammaCoef, 0, sizeof(stVpssGammaCoef));

    pq_mng_SetVpssGmmEnable(u32HandleNo, sg_bVpssGmmEn);

    pq_mng_GetVpssGammaModeCoef(enDrvPqVPImageMode, &stVpssGammaCoef);

    PQ_HAL_UpdateVpssGamma(u32HandleNo, &stVpssGammaCoef);

    return HI_SUCCESS;
}

/* Get VideoPhone Type */
HI_S32 PQ_MNG_SetVPGammaType(HI_DRV_PQ_VP_TYPE_E enDrvPqVPType)
{

    sg_enVpsVPGmmType = enDrvPqVPType ;

    return HI_SUCCESS;
}


static stPQAlgFuncs stVPSSGAMMAFuncs =
{
    .UpdateVpssGammaCoef    = PQ_MNG_UpdateVpssGammaCoef,
    .SetVPType              = PQ_MNG_SetVPGammaType,
};

HI_S32 PQ_MNG_RegisterVPSSGAMMA(PQ_REG_TYPE_E enType)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_VPSSGAMMA, enType, PQ_BIN_ADAPT_SINGLE, "vpssgamma", HI_NULL, &stVPSSGAMMAFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterVPSSGAMMA()
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_VPSSGAMMA);

    return s32Ret;
}

