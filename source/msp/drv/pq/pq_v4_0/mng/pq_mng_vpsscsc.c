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
#include "pq_mng_vpsscsc.h"
#include "pq_hal_comm.h"
#include "hi_math.h"

static HI_BOOL  sg_bVpssCscEn        = HI_FALSE;
static HI_BOOL  sg_bVpssCscDemoEn    = HI_FALSE;
static VPSSCSC_NODE_VPTYPE_S sg_enVpsVPCscType[HI_DRV_PQ_VP_TYPE_BUTT] =
{
    {0, HI_DRV_PQ_VP_TYPE_NORMAL} ,
    {0, HI_DRV_PQ_VP_TYPE_PREVIEW} ,
    {1, HI_DRV_PQ_VP_TYPE_REMOTE} ,
};

static VPSSCSC_DEMO_MODE_E sg_enVpssCscDemoMode = VPSSCSC_DEMO_ENABLE_L;

static HI_PQ_PICTURE_SETTING_S sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_BUTT] = /* normal & preview & remote */
{
    {128, 128, 128, 128},
    {128, 128, 128, 128},
    {128, 128, 128, 128},
};

static VPSSCSC_COLOR_TEMP sg_stVpssColorTemp = {50, 50, 50};

static HI_S32 g_VpssCscModeCfg[HI_DRV_PQ_VIDEOPHONE_MODE_BUTT][15] =
{
    {1024,   0,   0,     0,  1024,   0,   0,   0, 1024, -128, -128, -128, 128, 128, 128}, //Recommend
    {1024,   0,   0,     0,    0,    0,   0,   0,    0, -128, -128, -128, 128, 128, 128}, //BlackWhite
    {1600,   0,   0,     0,  1600,   0,   0,   0, 1600,  -80, -128, -128,  80, 128, 128}, //Colorful
    {2000,   0,   0,     0,  1024,   0,   0,   0, 1024,  -80, -128, -128,  80, 128, 128}, //Bright
    {1099,   0,  87,   -36,  1024, -43, 156,   0, 1203,    0, -128, -128,   0, 128, 128}, //Warm
    {1052,  59,   0,   111,  1250,   0, -25, -51, 1024,    0, -128, -128,   0, 128, 128}, //Cool
    {1195,    0,  194, -83,  1024, -96, 352,   0, 1425, -128, -128, -128, 128, 128, 128}, //Old
    {1195,    0,  194, -83,  1024, -96, 352,   0, 1425, -128, -128, -128, 128, 128, 128}  //user
    // {1024,   0,   0,   0, 1024,   0,   0,   0, 1024, -16, -128, -128, 16, 128, 128} //butt
};

const HI_S32 VPSS_SIN_TABLE[61] =
{
    -500, -485, -469, -454, -438, -422, -407, -391,
    -374, -358, -342, -325, -309, -292, -276, -259,
    -242, -225, -208, -191, -174, -156, -139, -122,
    -104,  -87,  -70,  -52,  -35,  -17,    0,   17,
    35,     52,   70,   87,  104,  122,  139,  156,
    174,   191,  208,  225,  242,  259,  276,  292,
    309,   325,  342,  358,  374,  391,  407,  422,
    438,   454,  469,  485,  500
};

const HI_U32 VPSS_COS_TABLE[61] =
{
    866, 875, 883, 891, 899,  906,  914,  921,
    927, 934, 940, 946, 951,  956,  961,  966,
    970, 974, 978, 982, 985,  988,  990,  993,
    995, 996, 998, 999, 999, 1000, 1000, 1000,
    999, 999, 998, 996, 995,  993,  990,  988,
    985, 982, 978, 974, 970,  966,  961,  956,
    951, 946, 940, 934, 927,  921,  914,  906,
    899, 891, 883, 875, 866
};

/* 计算色彩空间转换系数
   计算色温变换矩阵(for YCbCr->YCbCr 调节色温)
   */
static HI_VOID pq_mng_CalVpssCTemperatureMat(HI_U32 Kr, HI_U32 Kg, HI_U32 Kb,
        HI_PQ_CSC_COEF_S *pCSCTable, HI_PQ_CSC_COEF_S *pDstCSCTable)
{
    HI_S32 rGain;
    HI_S32 gGain;
    HI_S32 bGain;

    HI_PQ_CSC_COEF_S yuv_color_temp;

    /* 0-255 */
    rGain = Kr * 40 / 51;
    gGain = Kg * 40 / 51;
    bGain = Kb * 40 / 51;

    /* Kr系列精度100, 色温矩阵系数精度1000 */
    yuv_color_temp.csc_coef00 = (114  * bGain + 587 * gGain + 299 * rGain) / 100;
    yuv_color_temp.csc_coef01 = (232  * bGain - 232 * gGain) / 100;
    yuv_color_temp.csc_coef02 = -(341 * gGain - 341 * rGain) / 100;

    yuv_color_temp.csc_coef10 = -(289 * gGain - 436 * bGain + 147 * rGain) / 100;
    yuv_color_temp.csc_coef11 = (886  * bGain + 114 * gGain) / 100;
    yuv_color_temp.csc_coef12 = (168  * gGain - 168 * rGain) / 100;

    yuv_color_temp.csc_coef20 = -(100 * bGain + 515 * gGain - 615 * rGain) / 100;
    yuv_color_temp.csc_coef21 = -(203 * bGain - 203 * gGain) / 100;
    yuv_color_temp.csc_coef22 = (299  * gGain + 701 * rGain) / 100;

    pDstCSCTable->csc_coef00 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef20) / 1000;
    pDstCSCTable->csc_coef01 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef21) / 1000;
    pDstCSCTable->csc_coef02 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef22) / 1000;

    pDstCSCTable->csc_coef10 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef20) / 1000;
    pDstCSCTable->csc_coef11 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef21) / 1000;
    pDstCSCTable->csc_coef12 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef22) / 1000;

    pDstCSCTable->csc_coef20 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef20) / 1000;
    pDstCSCTable->csc_coef21 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef21) / 1000;
    pDstCSCTable->csc_coef22 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef22) / 1000;

    return;
}

/* 计算色彩空间转换系数 for YCbCr->YCbCr */
static HI_VOID pq_mng_CalVpssCscCoefTprtYCbCrtoYCbCr(HI_U32 Contrast, HI_U32 Saturation,
        HI_U32 Hue, HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, HI_PQ_CSC_COEF_S *pCSCTable, HI_PQ_CSC_COEF_S *pDstCSCTable)
{
    HI_S32     ChromaAdjust;
    HI_S32     SaturationAdjust;
    HI_PQ_CSC_COEF_S DstCSCTable2;

    ChromaAdjust     = Contrast   * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue              = Hue        * 60 / 255;

    pDstCSCTable->csc_coef00 = pCSCTable->csc_coef00 * ChromaAdjust / 100;
    pDstCSCTable->csc_coef01 = pCSCTable->csc_coef01 * ChromaAdjust / 100;
    pDstCSCTable->csc_coef02 = pCSCTable->csc_coef02 * ChromaAdjust / 100;

    pDstCSCTable->csc_coef10 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef10 * VPSS_COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef20 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef11 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef11 * VPSS_COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef21 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef12 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef12 * VPSS_COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef22 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;

    pDstCSCTable->csc_coef20 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef20 * VPSS_COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef10 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef21 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef21 * VPSS_COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef11 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef22 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef22 * VPSS_COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef12 * VPSS_SIN_TABLE[Hue]) / 1000) *
                                        ChromaAdjust * SaturationAdjust) / 10000;
    pq_mng_CalVpssCTemperatureMat(Kr, Kg, Kb, pDstCSCTable, &DstCSCTable2);

    pDstCSCTable->csc_coef00 = DstCSCTable2.csc_coef00;
    pDstCSCTable->csc_coef01 = DstCSCTable2.csc_coef01;
    pDstCSCTable->csc_coef02 = DstCSCTable2.csc_coef02;
    pDstCSCTable->csc_coef10 = DstCSCTable2.csc_coef10;
    pDstCSCTable->csc_coef11 = DstCSCTable2.csc_coef11;
    pDstCSCTable->csc_coef12 = DstCSCTable2.csc_coef12;
    pDstCSCTable->csc_coef20 = DstCSCTable2.csc_coef20;
    pDstCSCTable->csc_coef21 = DstCSCTable2.csc_coef21;
    pDstCSCTable->csc_coef22 = DstCSCTable2.csc_coef22;

    return;
}

/* 计算直流分量 */
/* Note: 这部分的计算, 精度还是按照原来的10bits配置, 可以在运算的最后乘上精度 */
static HI_VOID pq_mng_CalcVpssCscDcCoef(VPSSCSC_PARA_S *pstCSCParameter, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    HI_S32 s32Brightness = (HI_S32)pstCSCParameter->u16Brightness * 100 / 255 - 50;

    /* YCbCr -> YCbCr */
    pstCscDcCoef->csc_out_dc0 = s32Brightness + pstCscDcCoef->csc_out_dc0;

    return;
}

/* 10 bit precision */
static HI_S32 pq_mng_CalcVpssCscCoef(VPSSCSC_PARA_S *pstCSCParameter, HI_PQ_CSC_COEF_S *pstCscCoef)
{
    HI_PQ_CSC_COEF_S stCSCMatrix;

    PQ_CHECK_NULL_PTR(pstCSCParameter);
    PQ_CHECK_NULL_PTR(pstCscCoef);

    pq_mng_CalVpssCscCoefTprtYCbCrtoYCbCr(pstCSCParameter->u16Contrast,
                                          pstCSCParameter->u16Saturation,
                                          pstCSCParameter->u16Hue,
                                          pstCSCParameter->as16ColorTempGain[VPSSCOLORTEMP_R],
                                          pstCSCParameter->as16ColorTempGain[VPSSCOLORTEMP_G],
                                          pstCSCParameter->as16ColorTempGain[VPSSCOLORTEMP_B],
                                          pstCscCoef, &stCSCMatrix);

    pstCscCoef->csc_coef00 = stCSCMatrix.csc_coef00;
    pstCscCoef->csc_coef01 = stCSCMatrix.csc_coef01;
    pstCscCoef->csc_coef02 = stCSCMatrix.csc_coef02;

    pstCscCoef->csc_coef10 = stCSCMatrix.csc_coef10;
    pstCscCoef->csc_coef11 = stCSCMatrix.csc_coef11;
    pstCscCoef->csc_coef12 = stCSCMatrix.csc_coef12;

    pstCscCoef->csc_coef20 = stCSCMatrix.csc_coef20;
    pstCscCoef->csc_coef21 = stCSCMatrix.csc_coef21;
    pstCscCoef->csc_coef22 = stCSCMatrix.csc_coef22;

    pqprint(PQ_PRN_VPSSCSC, "pq_mng_CalcVpssCscCoef %d; %d; %d; %d; %d; %d; %d; %d; %d \n",
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

/* Set CSC Tran Mode:
   1. dc value order is right; but as the tran of Dobly, out dc is opposite to original data;
      we set right data in pq code, cbb tran it;
   2. we set precision at 10, with cbb;
   */
static HI_S32 pq_mng_GetVpssCscModeCoef(HI_DRV_PQ_VP_MODE_E enPqVPImageMode,
                                        HI_PQ_CSC_COEF_S *pstCscCoef,
                                        HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    PQ_CHECK_NULL_PTR(pstCscCoef);
    PQ_CHECK_NULL_PTR(pstCscDcCoef);

    pstCscCoef->csc_coef00 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][0]);
    pstCscCoef->csc_coef01 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][1]);
    pstCscCoef->csc_coef02 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][2]);

    pstCscCoef->csc_coef10 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][3]);
    pstCscCoef->csc_coef11 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][4]);
    pstCscCoef->csc_coef12 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][5]);

    pstCscCoef->csc_coef20 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][6]);
    pstCscCoef->csc_coef21 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][7]);
    pstCscCoef->csc_coef22 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][8]);

    pstCscDcCoef->csc_in_dc0  = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][9]);
    pstCscDcCoef->csc_in_dc1  = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][10]);
    pstCscDcCoef->csc_in_dc2  = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][11]);

    pstCscDcCoef->csc_out_dc0 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][12]);
    pstCscDcCoef->csc_out_dc1 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][13]);
    pstCscDcCoef->csc_out_dc2 = (HI_S32)(g_VpssCscModeCfg[enPqVPImageMode][14]);

    pqprint(PQ_PRN_VPSSCSC, "pq_mng_GetVpssCscModeCoef %d; %d; %d; %d; %d; %d; %d; %d; %d \n",
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

/* 设置CSC参数 */
static HI_S32 pq_mng_SetVpssCscPictureParam(HI_U32 u32VPNodeMatchType,
        HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode,
        HI_PQ_CSC_COEF_S *pstCscCoef,
        HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    VPSSCSC_PARA_S stVpssCscPara;

    PQ_CHECK_NULL_PTR(pstCscCoef);
    PQ_CHECK_NULL_PTR(pstCscDcCoef);

    pq_mng_GetVpssCscModeCoef(enDrvPqVPImageMode, pstCscCoef, pstCscDcCoef);

    if (HI_DRV_PQ_VIDEOPHONE_MODE_USER == enDrvPqVPImageMode)
    {
        stVpssCscPara.u16Brightness       = sg_stVPCscSetting[sg_enVpsVPCscType[u32VPNodeMatchType].enVpsVPCscType].u16Brightness;
        stVpssCscPara.u16Contrast         = sg_stVPCscSetting[sg_enVpsVPCscType[u32VPNodeMatchType].enVpsVPCscType].u16Contrast;
        stVpssCscPara.u16Saturation       = sg_stVPCscSetting[sg_enVpsVPCscType[u32VPNodeMatchType].enVpsVPCscType].u16Saturation;
        stVpssCscPara.u16Hue              = sg_stVPCscSetting[sg_enVpsVPCscType[u32VPNodeMatchType].enVpsVPCscType].u16Hue;
        stVpssCscPara.as16ColorTempGain[VPSSCOLORTEMP_R]   = LEVEL2NUM(sg_stVpssColorTemp.u32Red);
        stVpssCscPara.as16ColorTempGain[VPSSCOLORTEMP_G]   = LEVEL2NUM(sg_stVpssColorTemp.u32Green);
        stVpssCscPara.as16ColorTempGain[VPSSCOLORTEMP_B]   = LEVEL2NUM(sg_stVpssColorTemp.u32Blue);
        stVpssCscPara.as16ColorTempOffset[VPSSCOLORTEMP_R] = 128;
        stVpssCscPara.as16ColorTempOffset[VPSSCOLORTEMP_G] = 128;
        stVpssCscPara.as16ColorTempOffset[VPSSCOLORTEMP_B] = 128;
        pq_mng_CalcVpssCscCoef(&stVpssCscPara,   pstCscCoef);
        pq_mng_CalcVpssCscDcCoef(&stVpssCscPara, pstCscDcCoef);
    }

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVPCscSetting(HI_DRV_PQ_VP_TYPE_E enDrvPqVPType, HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    PQ_CHECK_NULL_PTR(pstPicSetting);

    if (HI_DRV_PQ_VP_TYPE_NORMAL == enDrvPqVPType)
    {
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Brightness = pstPicSetting->u16Brightness;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Contrast   = pstPicSetting->u16Contrast;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Saturation = pstPicSetting->u16Saturation;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Hue        = pstPicSetting->u16Hue;
    }
    else if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvPqVPType)
    {
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness = pstPicSetting->u16Brightness;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast   = pstPicSetting->u16Contrast;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation = pstPicSetting->u16Saturation;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue        = pstPicSetting->u16Hue;
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvPqVPType)
    {
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness = pstPicSetting->u16Brightness;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast   = pstPicSetting->u16Contrast;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation = pstPicSetting->u16Saturation;
        sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue        = pstPicSetting->u16Hue;
    }

    pqprint(PQ_PRN_VPSSCSC, "set MNG VPSS NORMAL Brightness=%d,Contrast=%d,Saturation=%d,Hue=%d\n",
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Brightness, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Contrast,
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Saturation, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Hue);
    pqprint(PQ_PRN_VPSSCSC, "set MNG VPSS PREVIEW Brightness=%d,Contrast=%d,Saturation=%d,Hue=%d\n",
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast,
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue);
    pqprint(PQ_PRN_VPSSCSC, "set MNG VPSS REMOTE Brightness=%d,Contrast=%d,Saturation=%d,Hue=%d\n",
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast,
            sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation, sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetVPCscSetting(HI_DRV_PQ_VP_TYPE_E enDrvPqVPType, HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    PQ_CHECK_NULL_PTR(pstPicSetting);

    if (HI_DRV_PQ_VP_TYPE_NORMAL == enDrvPqVPType)
    {
        pstPicSetting->u16Brightness = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Brightness;
        pstPicSetting->u16Contrast   = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Contrast;
        pstPicSetting->u16Hue        = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Hue;
        pstPicSetting->u16Saturation = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_NORMAL].u16Saturation;
    }
    else if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvPqVPType)
    {
        pstPicSetting->u16Brightness = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness;
        pstPicSetting->u16Contrast   = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast;
        pstPicSetting->u16Hue        = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue;
        pstPicSetting->u16Saturation = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation;
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvPqVPType)
    {
        pstPicSetting->u16Brightness = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness;
        pstPicSetting->u16Contrast   = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast;
        pstPicSetting->u16Hue        = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue;
        pstPicSetting->u16Saturation = sg_stVPCscSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation;
    }

    return HI_SUCCESS;
}

HI_S32 pq_mng_SetVpssCscEnable(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    PQ_STATUS_S stPqStatus = {0};
    HI_UNUSED(bEnable);

    PQ_COMM_GetPqStatus(&stPqStatus);
    if (PQ_IMAGE_MODE_VIDEOPHONE == stPqStatus.enImageMode)
    {
        sg_bVpssCscEn = HI_TRUE;
    }
    else
    {
        sg_bVpssCscEn = HI_FALSE;
    }


    if ((u32HandleNo == sg_enVpsVPCscType[1].u32HandleNo)
        && (HI_DRV_PQ_VP_TYPE_NORMAL == sg_enVpsVPCscType[1].enVpsVPCscType))
    {
        sg_bVpssCscEn = HI_FALSE;
    }

    if ((u32HandleNo == sg_enVpsVPCscType[2].u32HandleNo)
        && (HI_DRV_PQ_VP_TYPE_NORMAL == sg_enVpsVPCscType[2].enVpsVPCscType))
    {
        sg_bVpssCscEn = HI_FALSE;
    }

    PQ_HAL_SetVpssCscEnable(u32HandleNo, sg_bVpssCscEn);

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_UpdateVpssCscCoef(HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode)
{

    HI_PQ_CSC_COEF_S pstCscCoef       = {0};
    HI_PQ_CSC_DCCOEF_S pstCscDcCoef   = {0};
    HI_U32 u32VPNodeMatchType           = 0;
    if (u32HandleNo == sg_enVpsVPCscType[1].u32HandleNo)
    {
        u32VPNodeMatchType = 1;
    }
    else if (u32HandleNo == sg_enVpsVPCscType[2].u32HandleNo)
    {
        u32VPNodeMatchType = 2;
    }

    pq_mng_SetVpssCscPictureParam(u32VPNodeMatchType, enDrvPqVPImageMode, &pstCscCoef, &pstCscDcCoef);

    pstCscCoef.csc_coef00 = (HI_S32)(pstCscCoef.csc_coef00);
    pstCscCoef.csc_coef01 = (HI_S32)(pstCscCoef.csc_coef01);
    pstCscCoef.csc_coef02 = (HI_S32)(pstCscCoef.csc_coef02);
    pstCscCoef.csc_coef10 = (HI_S32)(pstCscCoef.csc_coef10);
    pstCscCoef.csc_coef11 = (HI_S32)(pstCscCoef.csc_coef11);
    pstCscCoef.csc_coef12 = (HI_S32)(pstCscCoef.csc_coef12);
    pstCscCoef.csc_coef20 = (HI_S32)(pstCscCoef.csc_coef20);
    pstCscCoef.csc_coef21 = (HI_S32)(pstCscCoef.csc_coef21);
    pstCscCoef.csc_coef22 = (HI_S32)(pstCscCoef.csc_coef22);

    pstCscDcCoef.csc_in_dc0  = (HI_S32)(pstCscDcCoef.csc_in_dc0);
    pstCscDcCoef.csc_in_dc1  = (HI_S32)(pstCscDcCoef.csc_in_dc1);
    pstCscDcCoef.csc_in_dc2  = (HI_S32)(pstCscDcCoef.csc_in_dc2);
    pstCscDcCoef.csc_out_dc0 = (HI_S32)(pstCscDcCoef.csc_out_dc0);
    pstCscDcCoef.csc_out_dc1 = (HI_S32)(pstCscDcCoef.csc_out_dc1);
    pstCscDcCoef.csc_out_dc2 = (HI_S32)(pstCscDcCoef.csc_out_dc2);

    pq_mng_SetVpssCscEnable(u32HandleNo, sg_bVpssCscEn);

    PQ_HAL_UpdateVpssCsc(u32HandleNo, &pstCscCoef, &pstCscDcCoef);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetVpssColorTemp(HI_U32 *pu32Red, HI_U32 *pu32Green, HI_U32 *pu32Blue)
{
    PQ_CHECK_NULL_PTR(pu32Red);
    PQ_CHECK_NULL_PTR(pu32Green);
    PQ_CHECK_NULL_PTR(pu32Blue);

    *pu32Red   = sg_stVpssColorTemp.u32Red;
    *pu32Green = sg_stVpssColorTemp.u32Green;
    *pu32Blue  = sg_stVpssColorTemp.u32Blue;

    return HI_SUCCESS;
}

HI_VOID  PQ_MNG_SetVpssColorTemp(HI_U32 u32Red, HI_U32 u32Green, HI_U32 u32Blue)
{
    sg_stVpssColorTemp.u32Red   = u32Red;
    sg_stVpssColorTemp.u32Green = u32Green;
    sg_stVpssColorTemp.u32Blue  = u32Blue;

    return;
}

/* Enable VpssCsc Demo En */
HI_S32 PQ_MNG_SetVpssCscDemoEn(HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    sg_bVpssCscDemoEn = bOnOff;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_TRUE == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetVpssCscDemoEnable(u32HandleNo, sg_bVpssCscDemoEn);
        }
    }

    return s32Ret;
}

HI_S32 PQ_MNG_GetVpssCscDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);
    *pbOnOff = sg_bVpssCscDemoEn;
    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetVpssCscDemoMode(PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;
    VPSSCSC_DEMO_MODE_E enVpssCscDemoMode = VPSSCSC_DEMO_ENABLE_L;

    sg_enVpssCscDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enVpssCscDemoMode = VPSSCSC_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enVpssCscDemoMode = VPSSCSC_DEMO_ENABLE_R;
    }

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_TRUE == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetVpssCscDemoMode(u32HandleNo, enVpssCscDemoMode);
        }
    }

    return s32Ret;
}

HI_S32 PQ_MNG_GetVpssCscDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR(penMode);
    *penMode = sg_enVpssCscDemoMode;
    return HI_SUCCESS;
}

/* Get VideoPhone Type */
HI_S32 PQ_MNG_SetVPType(HI_DRV_PQ_VP_TYPE_E enDrvPqVPType)
{
    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvPqVPType)
    {
        sg_enVpsVPCscType[1].u32HandleNo    = 0;
        sg_enVpsVPCscType[1].enVpsVPCscType = enDrvPqVPType;
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvPqVPType)
    {
        sg_enVpsVPCscType[2].u32HandleNo    = 1;
        sg_enVpsVPCscType[2].enVpsVPCscType = enDrvPqVPType;
    }

    return HI_SUCCESS;
}

static stPQAlgFuncs stVPSSCSCFuncs =
{
    .UpdateVpssCsc          = PQ_MNG_UpdateVpssCscCoef,
    .SetVPType              = PQ_MNG_SetVPType,
    .GetVPCscSetting        = PQ_MNG_GetVPCscSetting,
    .SetVPCscSetting        = PQ_MNG_SetVPCscSetting,
    .GetColorTemp           = PQ_MNG_GetVpssColorTemp,
    .SetColorTemp           = PQ_MNG_SetVpssColorTemp,
    .SetDemo                = PQ_MNG_SetVpssCscDemoEn,
    .GetDemo                = PQ_MNG_GetVpssCscDemoEn,
    .SetDemoMode            = PQ_MNG_SetVpssCscDemoMode,
    .GetDemoMode            = PQ_MNG_GetVpssCscDemoMode,
};

HI_S32 PQ_MNG_RegisterVPSSCSC(PQ_REG_TYPE_E enType)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_VPSSCSC, enType, PQ_BIN_ADAPT_MULTIPLE, "vpsscsc", HI_NULL, &stVPSSCSCFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterVPSSCSC()
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_VPSSCSC);

    return s32Ret;
}

