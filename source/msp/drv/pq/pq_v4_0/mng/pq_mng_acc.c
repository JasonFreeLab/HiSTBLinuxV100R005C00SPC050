/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_acc.c
  Version       : Initial Draft
  Author        :
  Created       : 2016/09/23
  Description   :

******************************************************************************/
#include "hi_math.h"
#include "pq_mng_acc.h"
#include "pq_hal_acc.h"

#define  PQ_ACC_TABLE_SIZE 45

static ALG_ACC_S sg_stPQACCInfo;
static PQ_PARAM_S *sg_pstPqParam  = HI_NULL;

static HI_S32 sg_u32AccTable[PQ_ACC_TABLE_SIZE] =
{
    0, 130, 270, 406, 530, 640, 768, 896, 1023, /* LowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidTable */
    0, 100, 240, 360, 496, 620, 764, 864, 1023, /* HighTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidLowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidHighTable */
};

static HI_S32 sg_u32AccTableBasic[PQ_ACC_TABLE_SIZE] =
{
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023
};

HI_S32 PQ_MNG_SetAccLevel(HI_U32 u32ACCLevel);

static HI_S32 PQ_MNG_ACCParaInit(HI_BOOL bDefault)
{
    PQ_HAL_ACC_PARA_S stAccPara;

    stAccPara.stAccCfg.acc_en       = HI_TRUE;
    stAccPara.stAccCfg.acc_mode     = HI_FALSE;
    stAccPara.stAccCfg.acc_dbg_mode = HI_TRUE;
    stAccPara.stAccCfg.acc_dbg_en   = HI_FALSE;
    stAccPara.stAccCfg.acc_rst      = HI_FALSE;

    stAccPara.thd_med_low   = 280;
    stAccPara.thd_high      = 620;
    stAccPara.thd_low       = 400;
    stAccPara.acc_multiple  = 14;
    stAccPara.thd_med_high  = 740;
    stAccPara.cnt3_low      = 0;
    stAccPara.cnt3_med      = 0;
    stAccPara.cnt3_high     = 0;
    stAccPara.cnt8_med_low  = 0;
    stAccPara.cnt8_med_high = 0;
    stAccPara.acc_pix_total = 0;

    return PQ_HAL_SetAccPara(PQ_HAL_LAYER_VID0, stAccPara);
}

static HI_VOID PQ_MNG_ACCLutInit(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    if (HI_NULL == pstPqParam)
    {
        return;
    }

    sg_pstPqParam = pstPqParam;

    if (HI_TRUE == bDefault)
    {
        memcpy((HI_VOID *)(pstPqParam->stPQCoef.stACCCoef.as32AccLut), (HI_VOID *)sg_u32AccTable,
               sizeof(sg_u32AccTable));
    }
    else
    {
        memcpy((HI_VOID *)sg_u32AccTable, (HI_VOID *)(pstPqParam->stPQCoef.stACCCoef.as32AccLut),
               sizeof(sg_u32AccTable));
    }

    return ;
}

HI_S32 PQ_MNG_GetACCHistgram(HI_PQ_ACC_HISTGRAM_S* pstACCHist)
{
    PQ_CHECK_NULL_PTR(pstACCHist);
    return PQ_HAL_GetACCHistgram((ACC_HISTGRAM_S*)pstACCHist);
}

HI_S32 PQ_MNG_InitACC(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_TRUE == sg_stPQACCInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQACCInfo.bEnable              = HI_TRUE;
    sg_stPQACCInfo.u32Strength          = 50;
    sg_stPQACCInfo.bDemoEnable          = HI_FALSE;
    sg_stPQACCInfo.eDemoMode            = PQ_DEMO_ENABLE_R;

    s32Ret = PQ_MNG_ACCParaInit(bDefault);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_ACCParaInit error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_TABLE_InitPhyList(PQ_VDP_LAYER_VID0, HI_PQ_MODULE_DCI, SOURCE_MODE_NO, OUTPUT_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("DCI InitPhyList error\n");
        return HI_FAILURE;
    }

    PQ_MNG_ACCLutInit(pstPqParam, bDefault);

    PQ_MNG_SetAccLevel(50);

    sg_stPQACCInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitACC(HI_VOID)
{
    if (HI_FALSE == sg_stPQACCInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQACCInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCEn(HI_U32 *pu32OnOff)
{
    PQ_CHECK_NULL_PTR(pu32OnOff);

    *pu32OnOff = sg_stPQACCInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCEn(HI_BOOL bOnOff)
{
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutputMode = PQ_COMM_GetOutputMode();
    PQ_STATUS_S stPqStatus = {0};

    sg_stPQACCInfo.bEnable = bOnOff;

    if ((OUTPUT_MODE_PREVIEW == enOutputMode)
        || (OUTPUT_MODE_REMOTE == enOutputMode))
    {
        sg_stPQACCInfo.bEnable = HI_FALSE;
    }

    if ((enSourceMode < SOURCE_MODE_ALL)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DCI, enSourceMode)))
    {
        sg_stPQACCInfo.bEnable = HI_FALSE;
    }
    PQ_COMM_GetPqStatus(&stPqStatus);
    if (PQ_IMAGE_MODE_VIDEOPHONE == stPqStatus.enImageMode)
    {
        sg_stPQACCInfo.bEnable = HI_FALSE;
    }

    PQ_HAL_SetAccAccEn(PQ_HAL_LAYER_VID0, sg_stPQACCInfo.bEnable);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCDemoEn(HI_BOOL bOnOff)
{
    /* acc demo off for only support 50% pos */
    PQ_HAL_SetAccDbgEn(PQ_HAL_LAYER_VID0, HI_FALSE);

    sg_stPQACCInfo.bDemoEnable = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);

    *pbOnOff = sg_stPQACCInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCDemoMode(PQ_DEMO_MODE_E enMode)
{
    PQ_HAL_LAYER_VID_E u32ChId   = PQ_HAL_LAYER_VID0;
    ACC_DEMO_MODE_E    enAccMode = ACC_DEMO_ENABLE_R;

    sg_stPQACCInfo.eDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enAccMode = ACC_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enAccMode = ACC_DEMO_ENABLE_R;
    }

    PQ_HAL_SetAccDbgMode(u32ChId, enAccMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR(penMode);

    *penMode = sg_stPQACCInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetAccLevel(HI_U32 *pu32ACCLevel)
{
    PQ_CHECK_NULL_PTR(pu32ACCLevel);

    *pu32ACCLevel = sg_stPQACCInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetAccLevel(HI_U32 u32ACCLevel)
{
    HI_S32 i;
    HI_U32 au32AccTable[PQ_ACC_TABLE_SIZE] = {0};
    HI_S32 s32TmpTableDate = 0;

    if (u32ACCLevel > 100)
    {
        HI_ERR_PQ("%d:ACC Level is over range!\n", u32ACCLevel);
        return HI_FAILURE;
    }

    sg_stPQACCInfo.u32Strength = u32ACCLevel;

    for (i = 0; i < PQ_ACC_TABLE_SIZE; i++)
    {
        if ( u32ACCLevel < 50)
        {
            s32TmpTableDate = sg_u32AccTableBasic[i] + \
                (sg_u32AccTable[i] - sg_u32AccTableBasic[i]) * (HI_S32)u32ACCLevel / 50;
            au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);

        }
        else
        {
            s32TmpTableDate = (sg_u32AccTable[i] + \
                (sg_u32AccTable[i] - sg_u32AccTableBasic[i]) * ((HI_S32)u32ACCLevel - 50) / 50);
            au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
        }
    }

    return PQ_HAL_SetAccTab(PQ_HAL_LAYER_VID0,  au32AccTable);
}

HI_S32 PQ_MNG_SetACCLut(PQ_ACC_LUT_S *pstACCLut)
{
    PQ_CHECK_NULL_PTR(pstACCLut);
    PQ_CHECK_NULL_PTR(sg_pstPqParam);

    memcpy((HI_VOID *)(sg_pstPqParam->stPQCoef.stACCCoef.as32AccLut), (HI_VOID *)pstACCLut,
           sizeof(PQ_ACC_LUT_S));

    memcpy((HI_VOID *)sg_u32AccTable, (HI_VOID *)pstACCLut, sizeof(PQ_ACC_LUT_S));

    return PQ_MNG_SetAccLevel(sg_stPQACCInfo.u32Strength);
}

HI_S32 PQ_MNG_GetACCLut(PQ_ACC_LUT_S *pstACCLut)
{
    PQ_CHECK_NULL_PTR(pstACCLut);
    PQ_CHECK_NULL_PTR(sg_pstPqParam);

    memcpy((HI_VOID *)pstACCLut, (HI_VOID *)sg_u32AccTable, sizeof(PQ_ACC_LUT_S));

    return HI_SUCCESS;
}

static stPQAlgFuncs stACCFuncs =
{
    .Init               = PQ_MNG_InitACC,
    .DeInit             = PQ_MNG_DeInitACC,
    .SetEnable          = PQ_MNG_SetACCEn,
    .GetEnable          = PQ_MNG_GetACCEn,
    .SetDemo            = PQ_MNG_SetACCDemoEn,
    .GetDemo            = PQ_MNG_GetACCDemoEn,
    .SetDemoMode        = PQ_MNG_SetACCDemoMode,
    .GetDemoMode        = PQ_MNG_GetACCDemoMode,
    .SetStrength        = PQ_MNG_SetAccLevel,
    .GetStrength        = PQ_MNG_GetAccLevel,
    .GetACCHistGram     = PQ_MNG_GetACCHistgram,
};

HI_S32 PQ_MNG_RegisterACC(PQ_REG_TYPE_E enType)
{
    return PQ_COMM_AlgRegister(HI_PQ_MODULE_DCI, enType, PQ_BIN_ADAPT_SINGLE, "acc", HI_NULL, &stACCFuncs);
}

HI_S32 PQ_MNG_UnRegisterACC(HI_VOID)
{
    return PQ_COMM_AlgUnRegister(HI_PQ_MODULE_DCI);
}

