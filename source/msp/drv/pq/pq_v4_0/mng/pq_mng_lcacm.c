#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mem.h"
#include "hi_drv_file.h"
#include "hi_drv_pq.h"

#include "pq_hal_comm.h"
#include "pq_hal_lcacm.h"
#include "pq_mng_lcacm.h"

static ALG_LCACM_S sg_stPQLCACMInfo = {0};

/* Init Color */
static HI_S32 PQ_MNG_LowCostACMParaInit(HI_VOID)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};

    memset(&stAcmPara, 0x0, sizeof(stAcmPara));

    PQ_HAL_SetLowCostAcmPara(VDP_LAYER_VP0, &stAcmPara);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLowCostACMEn(HI_BOOL bOnOff)
{
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    sg_stPQLCACMInfo.bEnable = bOnOff;

    if ((enSourceMode < SOURCE_MODE_ALL)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_COLOR, enSourceMode)))
    {
        sg_stPQLCACMInfo.bEnable = HI_FALSE;
    }

    PQ_HAL_EnableACM(VDP_LAYER_VP0, sg_stPQLCACMInfo.bEnable);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostACMEn(HI_U32 *pu32OnOff)
{
    PQ_CHECK_NULL_PTR(pu32OnOff);
    *pu32OnOff = sg_stPQLCACMInfo.bEnable;

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_InitLowCostACM(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_stPQLCACMInfo.bInit == HI_TRUE)
    {
        return HI_SUCCESS;
    }

    sg_stPQLCACMInfo.bEnable              = HI_TRUE;
    sg_stPQLCACMInfo.u32Strength          = 50;
    sg_stPQLCACMInfo.bDemoEnable          = HI_FALSE;
    sg_stPQLCACMInfo.eDemoMode            = PQ_DEMO_ENABLE_R;
    sg_stPQLCACMInfo.enLCACMFleshLevel          = LCACM_FLE_GAIN_MID;
    sg_stPQLCACMInfo.enLCAcmEnhance             = LCACM_ENHANCE_SPEC_COLOR_MODE;
    sg_stPQLCACMInfo.enLCACMColorSpecModeType   = LCACM_COLOR_MODE_RECOMMEND;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32RedOffset       = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32GreenOffset     = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32BlueOffset      = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32CyanOffset      = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32MagentaOffset   = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32YellowOffset    = 50;

    s32Ret = PQ_MNG_SetLowCostACMEn(HI_TRUE);
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_PQ("LowCost ACM Enable Init failure\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_LowCostACMParaInit();
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_PQ("LowCost ACM Para Init failure\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_TABLE_InitPhyList(PQ_VDP_LAYER_VID0, HI_PQ_MODULE_COLOR, SOURCE_MODE_NO, SOURCE_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Low Cost ACM InitPhyList error\n");
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitLowCostACM(HI_VOID)
{
    if (sg_stPQLCACMInfo.bInit == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    sg_stPQLCACMInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLowCostACMDemoEn(HI_BOOL bOnOff)
{
    /* lcacm demo off for only support 50% pos */
    PQ_HAL_EnableACMDemo(VDP_LAYER_VP0, HI_FALSE);

    sg_stPQLCACMInfo.bDemoEnable = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostACMDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);

    *pbOnOff = sg_stPQLCACMInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLowCostACMDemoMode(PQ_DEMO_MODE_E enMode)
{
    PQ_HAL_LAYER_VP_E   u32ChId   = VDP_LAYER_VP0;
    HAL_ACM_DEMO_MODE_E enAcmMode = HAL_ACM_DEMO_ENABLE_L;

    sg_stPQLCACMInfo.eDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enAcmMode = HAL_ACM_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enAcmMode = HAL_ACM_DEMO_ENABLE_R;
    }

    PQ_HAL_SetACMDemoMode(u32ChId, enAcmMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostACMDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR(penMode);

    *penMode = sg_stPQLCACMInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostColorEnhanceMode(HI_U32 *pu32ColorEnhanceMode)
{
    PQ_CHECK_NULL_PTR(pu32ColorEnhanceMode);

    *pu32ColorEnhanceMode = sg_stPQLCACMInfo.enLCACMColorSpecModeType;

    return HI_SUCCESS;
}



HI_S32 PQ_MNG_GetLowCostACMFleshToneLevel(HI_U32 *pu32FleshToneLevel)
{
    PQ_CHECK_NULL_PTR(pu32FleshToneLevel);

    *pu32FleshToneLevel = sg_stPQLCACMInfo.enLCACMFleshLevel;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLowCostACMFleshToneLevel(HI_PQ_FLESHTONE_E enGainLevel)
{

    LCACM_COLOR_SPEC_MODE_E enLCACMColorSpecMode = LCACM_COLOR_MODE_RECOMMEND;
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    if (HI_PQ_FLESHTONE_GAIN_BUTT <= enGainLevel)
    {
        HI_ERR_PQ("[%d]Switch : Color enGainLevel Mode Set error!\n", enGainLevel);
        return HI_FAILURE;
    }

    if (enGainLevel == HI_PQ_FLESHTONE_GAIN_OFF)
    {
        sg_stPQLCACMInfo.enLCAcmEnhance = LCACM_ENHANCE_SPEC_COLOR_MODE;
    }
    else
    {
        sg_stPQLCACMInfo.enLCAcmEnhance = LCACM_ENHANCE_FLESHTONE;
    }

    if (sg_stPQLCACMInfo.enLCAcmEnhance == LCACM_ENHANCE_FLESHTONE)
    {
        enLCACMColorSpecMode = LCACM_COLOR_MODE_PORTRAIT;
    }

    memset(&stAcmPara, 0x0, sizeof(stAcmPara));

    stAcmPara.acm0_sec_blk = 9;
    stAcmPara.acm0_fir_blk = 7;

    stAcmPara.acm0_d_u_off = 0;
    stAcmPara.acm0_c_u_off = 0;
    stAcmPara.acm0_b_u_off = -2;
    stAcmPara.acm0_a_u_off = -2;
    stAcmPara.acm0_d_v_off = 0;
    stAcmPara.acm0_c_v_off = 2;
    stAcmPara.acm0_b_v_off = 3;
    stAcmPara.acm0_a_v_off = 4;

    PQ_HAL_SetLowCostAcmPara(VDP_LAYER_VP0, &stAcmPara);

    sg_stPQLCACMInfo.enLCACMFleshLevel         = enGainLevel;
    sg_stPQLCACMInfo.enLCACMColorSpecModeType  = enLCACMColorSpecMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SwitchEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode, LCACM_COLOR_SPEC_MODE_E *pColorSpecMode)
{
    if (HI_PQ_COLOR_MODE_BUTT <= enColorSpecMode)
    {
        HI_ERR_PQ("[%d]Switch : Color Enhance Mode Set error!\n", enColorSpecMode);
        return HI_FAILURE;
    }

    switch (enColorSpecMode)
    {
        case HI_PQ_COLOR_MODE_RECOMMEND:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_RECOMMEND;
        }
        break;
        case HI_PQ_COLOR_MODE_BLUE:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_SKY;;
        }
        break;
        case HI_PQ_COLOR_MODE_GREEN:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_GRASS;
        }
        break;
        case HI_PQ_COLOR_MODE_BG:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_SCENERY;
        }
        break;
        case HI_PQ_COLOR_MODE_ORIGINAL:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_PORTRAIT;
        }
        break;
        default:
        {
            *pColorSpecMode = LCACM_COLOR_MODE_RECOMMEND;
        }
        break;
    }

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetLowCostColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    LCACM_COLOR_SPEC_MODE_E enLCACMColorSpecMode = LCACM_COLOR_MODE_RECOMMEND;
    PQ_HAL_ACM_PARA_S stAcmPara = {0};

    PQ_MNG_SwitchEnhanceMode(enColorSpecMode, &enLCACMColorSpecMode);

    switch (enLCACMColorSpecMode)
    {
        case LCACM_COLOR_MODE_RECOMMEND:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));
        }
        break;
        case LCACM_COLOR_MODE_PORTRAIT:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));

            stAcmPara.acm0_sec_blk = 9;
            stAcmPara.acm0_fir_blk = 7;

            stAcmPara.acm0_d_u_off = 0;
            stAcmPara.acm0_c_u_off = 0;
            stAcmPara.acm0_b_u_off = -2;
            stAcmPara.acm0_a_u_off = -2;
            stAcmPara.acm0_d_v_off = 0;
            stAcmPara.acm0_c_v_off = 2;
            stAcmPara.acm0_b_v_off = 3;
            stAcmPara.acm0_a_v_off = 4;
        }
        break;
        case LCACM_COLOR_MODE_SKY:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));

            stAcmPara.acm0_sec_blk = 7;
            stAcmPara.acm0_fir_blk = 9;

            stAcmPara.acm0_d_u_off = 5;
            stAcmPara.acm0_c_u_off = 2;
            stAcmPara.acm0_b_u_off = 0;
            stAcmPara.acm0_a_u_off = 3;
            stAcmPara.acm0_d_v_off = -5;
            stAcmPara.acm0_c_v_off = 0;
            stAcmPara.acm0_b_v_off = 0;
            stAcmPara.acm0_a_v_off = -3;
        }
        break;
        case LCACM_COLOR_MODE_GRASS:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));

            stAcmPara.acm0_sec_blk = 7;
            stAcmPara.acm0_fir_blk = 6;

            stAcmPara.acm0_d_u_off = -1;
            stAcmPara.acm0_c_u_off = -2;
            stAcmPara.acm0_b_u_off = -4;
            stAcmPara.acm0_a_u_off = -4;
            stAcmPara.acm0_d_v_off = -1;
            stAcmPara.acm0_c_v_off = -5;
            stAcmPara.acm0_b_v_off = -6;
            stAcmPara.acm0_a_v_off = -8;
        }
        break;
        case LCACM_COLOR_MODE_SCENERY:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));

            stAcmPara.acm0_sec_blk = 7;
            stAcmPara.acm0_fir_blk = 9;

            stAcmPara.acm0_d_u_off = 5;
            stAcmPara.acm0_c_u_off = 2;
            stAcmPara.acm0_b_u_off = 0;
            stAcmPara.acm0_a_u_off = 3;
            stAcmPara.acm0_d_v_off = -5;
            stAcmPara.acm0_c_v_off = 0;
            stAcmPara.acm0_b_v_off = 0;
            stAcmPara.acm0_a_v_off = -3;

            stAcmPara.acm1_sec_blk = 7;
            stAcmPara.acm1_fir_blk = 6;

            stAcmPara.acm1_d_u_off = -1;
            stAcmPara.acm1_c_u_off = -2;
            stAcmPara.acm1_b_u_off = -4;
            stAcmPara.acm1_a_u_off = -4;
            stAcmPara.acm1_d_v_off = -1;
            stAcmPara.acm1_c_v_off = -5;
            stAcmPara.acm1_b_v_off = -6;
            stAcmPara.acm1_a_v_off = -8;

            stAcmPara.acm2_sec_blk = 0;
            stAcmPara.acm2_fir_blk = 0;
        }
        break;
        default:
        {
            memset(&stAcmPara, 0x0, sizeof(stAcmPara));
        }
        break;
    }

    PQ_HAL_SetLowCostAcmPara(VDP_LAYER_VP0, &stAcmPara);

    sg_stPQLCACMInfo.enLCACMColorSpecModeType = enLCACMColorSpecMode;

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetLowCostACMGainLevel(HI_U32 u32GainLevel)
{
    if (u32GainLevel > 100)
    {
        HI_ERR_PQ("%d:PQ_MNG_SetLowCostACMGainLevel is over range!\n", u32GainLevel);
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.u32Strength = u32GainLevel;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostACMGainLevel(HI_U32 *pu32ColorLevel)
{
    PQ_CHECK_NULL_PTR(pu32ColorLevel);

    *pu32ColorLevel = sg_stPQLCACMInfo.u32Strength;

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetLowCostSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR(pstSixBaseColorOffset);

    if ((pstSixBaseColorOffset->u32Red > 100)
        || (pstSixBaseColorOffset->u32Green > 100)
        || (pstSixBaseColorOffset->u32Blue > 100)
        || (pstSixBaseColorOffset->u32Cyan > 100)
        || (pstSixBaseColorOffset->u32Magenta > 100)
        || (pstSixBaseColorOffset->u32Yellow > 100))
    {
        HI_ERR_PQ("out of range\n");
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32RedOffset     = pstSixBaseColorOffset->u32Red;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32GreenOffset   = pstSixBaseColorOffset->u32Green;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32BlueOffset    = pstSixBaseColorOffset->u32Blue;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32CyanOffset    = pstSixBaseColorOffset->u32Cyan;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32MagentaOffset = pstSixBaseColorOffset->u32Magenta;
    sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32YellowOffset  = pstSixBaseColorOffset->u32Yellow;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLowCostSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR(pstSixBaseColorOffset);

    pstSixBaseColorOffset->u32Red     = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32RedOffset;
    pstSixBaseColorOffset->u32Green   = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32GreenOffset;
    pstSixBaseColorOffset->u32Blue    = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32BlueOffset;
    pstSixBaseColorOffset->u32Cyan    = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32CyanOffset;
    pstSixBaseColorOffset->u32Magenta = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32MagentaOffset;
    pstSixBaseColorOffset->u32Yellow  = sg_stPQLCACMInfo.stLCACMSixbaseColorOffset.u32YellowOffset;

    return HI_SUCCESS;
}

static stPQAlgFuncs stLowCostACMFuncs =
{
    .Init                 = PQ_MNG_InitLowCostACM,
    .DeInit               = PQ_MNG_DeInitLowCostACM,
    .SetEnable            = PQ_MNG_SetLowCostACMEn,
    .GetEnable            = PQ_MNG_GetLowCostACMEn,
    .SetDemo              = PQ_MNG_SetLowCostACMDemoEn,
    .GetDemo              = PQ_MNG_GetLowCostACMDemoEn,
    .SetDemoMode          = PQ_MNG_SetLowCostACMDemoMode,
    .GetDemoMode          = PQ_MNG_GetLowCostACMDemoMode,
    .SetStrength          = PQ_MNG_SetLowCostACMGainLevel,
    .GetStrength          = PQ_MNG_GetLowCostACMGainLevel,
    .SetFleshToneLevel    = PQ_MNG_SetLowCostACMFleshToneLevel,
    .GetFleshToneLevel    = PQ_MNG_GetLowCostACMFleshToneLevel,
    .SetSixBaseColorLevel = PQ_MNG_SetLowCostSixBaseColorLevel,
    .GetSixBaseColorLevel = PQ_MNG_GetLowCostSixBaseColorLevel,
    .SetColorEnhanceMode  = PQ_MNG_SetLowCostColorEnhanceMode,
    .GetColorEnhanceMode  = PQ_MNG_GetLowCostColorEnhanceMode,
};

HI_S32 PQ_MNG_RegisterLowCostACM(PQ_REG_TYPE_E enType)
{
    return PQ_COMM_AlgRegister(HI_PQ_MODULE_COLOR, enType, PQ_BIN_ADAPT_SINGLE, "acm", HI_NULL, &stLowCostACMFuncs);
}

HI_S32 PQ_MNG_UnRegisterLowCostACM(HI_VOID)
{
    return PQ_COMM_AlgUnRegister(HI_PQ_MODULE_COLOR);
}

