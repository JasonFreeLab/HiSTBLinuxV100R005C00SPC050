/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_vdp4ksnr.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/04/14
  Description   :

******************************************************************************/
#include "hi_drv_mem.h"
#include "drv_pq_table.h"
#include "pq_hal_comm.h"
#include "pq_mng_vdp4ksnr.h"
#include "pq_hal_vdp4ksnr.h"

static ALG_VDP4KSNR_S sg_stPQVdp4KSNRInfo;

static HI_U32  sg_u32PQVdp4KSnrYStr = 16;


HI_S32 PQ_MNG_DeInitVdp4KSnr(HI_VOID)
{
    if (HI_FALSE == sg_stPQVdp4KSNRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQVdp4KSNRInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVdp4KSnrEnable(HI_BOOL bOnOff)
{
    HI_U32 u32Vid = PQ_VDP_LAYER_VID0;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    if ((enSourceMode < SOURCE_MODE_UHD)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_VDP4KSNR, enSourceMode)))
    {
        bOnOff = HI_FALSE;
    }

    sg_stPQVdp4KSNRInfo.bEnable = bOnOff;

    PQ_HAL_SetVdp4KSnrEnable(u32Vid, sg_stPQVdp4KSNRInfo.bEnable);

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_GetVdp4KSnrEnable(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);

    *pbOnOff = sg_stPQVdp4KSNRInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVdp4KSnrDemoEn(HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Vid = PQ_VDP_LAYER_VID0;

    sg_stPQVdp4KSNRInfo.bDemoEnable = bOnOff;

    s32Ret = PQ_HAL_SetVdp4KSnrDemomodeen(u32Vid, sg_stPQVdp4KSNRInfo.bDemoEnable);

    return s32Ret;
}

HI_S32 PQ_MNG_GetVdp4KSnrDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);

    *pbOnOff = sg_stPQVdp4KSNRInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVdp4KSnrDemoMode(PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Vid = PQ_VDP_LAYER_VID0;

    sg_stPQVdp4KSNRInfo.eDemoMode = enMode;

    s32Ret = PQ_HAL_SetVdp4KSnrDemomodelr(u32Vid, (VDP4KSNR_DEMO_MODE_E)enMode);

    return s32Ret;
}

HI_S32 PQ_MNG_GetVdp4KSnrDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR(penMode);

    *penMode = sg_stPQVdp4KSNRInfo.eDemoMode;

    return HI_SUCCESS;
}

/* Set Snr Strengh; s32SnrStr  Snr Strengh[0,100] */
HI_S32 PQ_MNG_SetVdp4KSnrStrength(HI_U32 u32SnrStr)
{
    HI_S32 s32Ret      = HI_FAILURE;
    HI_U32 u32Vid      = PQ_VDP_LAYER_VID0;
    HI_U32 u32Strength = 50;

    if (u32SnrStr > 100)
    {
        HI_ERR_PQ("the value[%d] of setting SNR strength is out of range!\n", u32SnrStr);
        return HI_FAILURE;
    }

    sg_stPQVdp4KSNRInfo.u32Strength = u32SnrStr;

    u32Strength = (sg_stPQVdp4KSNRInfo.u32Strength * sg_u32PQVdp4KSnrYStr * 2) / 100;

    s32Ret = PQ_HAL_SetVdp4KSnrstrength(u32Vid, u32Strength);

    return s32Ret;
}

/* Get Snr Strengh ; s32SnrStr Strengh[0,100] */
HI_S32 PQ_MNG_GetVdp4KSnrStrength(HI_U32 *pu32SnrStr)
{
    PQ_CHECK_NULL_PTR(pu32SnrStr);

    *pu32SnrStr = sg_stPQVdp4KSNRInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVdp4KSnrDemoModeCoor (HI_U32 u32XPos)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Vid = PQ_VDP_LAYER_VID0;

    s32Ret = PQ_HAL_SetVdp4KSnrDemoModeCoor(u32Vid, u32XPos);

    return s32Ret;
}

HI_S32 PQ_MNG_SetVdp4KSNRCbCrLut (HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVdp4KSNRMotionEdgeLut (HI_U32 u32Width)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Vid = PQ_VDP_LAYER_VID0;

    s32Ret = PQ_HAL_SetVdp4KSnrMotionEdgeLut(u32Vid, u32Width);

    return s32Ret;
}

HI_S32 PQ_MNG_InitVdp4KSnr(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32HandleNo = 0;

    sg_stPQVdp4KSNRInfo.bEnable      = HI_FALSE;
    sg_stPQVdp4KSNRInfo.u32Strength  = 50;
    sg_stPQVdp4KSNRInfo.bDemoEnable  = HI_FALSE;
    sg_stPQVdp4KSNRInfo.eDemoMode    = PQ_DEMO_ENABLE_R;

    if (HI_TRUE == sg_stPQVdp4KSNRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    PQ_TABLE_InitPhyList(u32HandleNo, HI_PQ_MODULE_VDP4KSNR, SOURCE_MODE_UHD, OUTPUT_MODE_NO);

    s32Ret = PQ_MNG_SetVdp4KSNRMotionEdgeLut(3840);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_SetVdp4KSNRMotionEdgeLut error!\n");
        return HI_FAILURE;
    }

    PQ_MNG_SetVdp4KSnrStrength(sg_stPQVdp4KSNRInfo.u32Strength);

    sg_stPQVdp4KSNRInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}


static stPQAlgFuncs stVDP4KSNRFuncs =
{
    .Init                = PQ_MNG_InitVdp4KSnr,
    .DeInit              = PQ_MNG_DeInitVdp4KSnr,
    .SetEnable           = PQ_MNG_SetVdp4KSnrEnable,
    .GetEnable           = PQ_MNG_GetVdp4KSnrEnable,
    .SetDemo             = PQ_MNG_SetVdp4KSnrDemoEn,
    .GetDemo             = PQ_MNG_GetVdp4KSnrDemoEn,
    .SetDemoMode         = PQ_MNG_SetVdp4KSnrDemoMode,
    .GetDemoMode         = PQ_MNG_GetVdp4KSnrDemoMode,
    .SetStrength         = PQ_MNG_SetVdp4KSnrStrength,
    .GetStrength         = PQ_MNG_GetVdp4KSnrStrength,
    .SetDemoModeCoor     = PQ_MNG_SetVdp4KSnrDemoModeCoor,
    .SetSNRCbCrLut       = PQ_MNG_SetVdp4KSNRCbCrLut,
    .SetSNRMotionEdgeLut = PQ_MNG_SetVdp4KSNRMotionEdgeLut,

};

HI_S32 PQ_MNG_RegisterVDP4KSNR(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_VDP4KSNR, enType, PQ_BIN_ADAPT_SINGLE, "vdp4ksnr", HI_NULL, &stVDP4KSNRFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterVDP4KSNR()
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_VDP4KSNR);

    return s32Ret;
}

