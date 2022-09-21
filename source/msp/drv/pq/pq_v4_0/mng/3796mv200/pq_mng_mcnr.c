/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_mcnr.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/07/18
  Description   :

******************************************************************************/
#include "hi_math.h"
#include "drv_pq_table.h"
#include "drv_pq_comm.h"
#include "pq_hal_mcnr.h"
#include "pq_mng_mcnr.h"

#define PQ_NOUSE_INLINE 0

#define MIN(x, y) (((x) > (y)) ? (y) : (x))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#if PQ_NOUSE_INLINE
#define NR_CLIP3(low,high,x)   (MAX(MIN((high),(x)),(low)))
#define NR_CLIP2(high,x)  (MIN((high),(x)))
#define NR_CLIP(x) (((x) < 0) ? 0 : (x))
#define NR_CLIP255(x)  (MAX( MIN((x), 255), 0))
#define NR_CLIP1023(x) (MAX( MIN((x), 1023), 0))
#else
inline HI_S32 NR_CLIP3(HI_S32 low, HI_S32 high, HI_S32 x)
{
    HI_S32 low_value = low;
    HI_S32 high_value = high;
    HI_S32 x_value = x;
    HI_S32 temp;

    temp = MIN((high_value), (x_value));
    return MAX(temp, (low_value));
}

inline HI_S32 NR_CLIP2(HI_S32 high, HI_S32 x)
{
    HI_S32 high_value = high;
    HI_S32 x_value = x;

    return MIN((high_value), (x_value));
}

inline HI_S32 NR_CLIP(HI_S32 x)
{
    HI_S32 x_value = x;
    return (((x_value) < 0) ? 0 : (x_value));
}

inline HI_S32 NR_CLIP255(HI_S32 x)
{
    HI_S32 x_value = x;
    HI_S32 temp;
    temp = MIN((x_value), 255);
    return (MAX(temp , 0));
}

inline HI_S32 NR_CLIP1023(HI_S32 x)
{
    HI_S32 x_value = x;
    HI_S32 temp;

    temp = MIN((x_value), 1023);
    return (MAX(temp , 0));
}
#endif

#define MCNR_Y_MAX_WIDTH  (1920)
#define MCNR_Y_MIN_WIDTH  (128)

static MCNR_TIMING_INFO g_McnrTimingInfo;
static HI_BOOL sg_bMCNREn = HI_TRUE;
static HI_S32 sg_u32MCNRStr = 50;

static HI_S32 LUT256[256] =
{
    10000, 9999, 9997, 9994, 9989, 9983, 9975, 9966, 9956, 9944, 9931, 9917, 9901, 9884, 9865, 9845,
    9824, 9802, 9778, 9753, 9727, 9699, 9671, 9641, 9609, 9577, 9543, 9508, 9472, 9435, 9396, 9357,
    9316, 9274, 9231, 9187, 9142, 9096, 9049, 9001, 8952, 8902, 8851, 8799, 8746, 8692, 8638, 8582,
    8526, 8469, 8411, 8353, 8293, 8233, 8173, 8111, 8049, 7986, 7923, 7859, 7795, 7730, 7664, 7598,
    7532, 7465, 7397, 7330, 7261, 7193, 7124, 7055, 6985, 6916, 6846, 6775, 6705, 6634, 6564, 6493,
    6422, 6351, 6279, 6208, 6137, 6065, 5994, 5923, 5851, 5780, 5709, 5638, 5567, 5496, 5425, 5355,
    5285, 5215, 5145, 5075, 5006, 4936, 4868, 4799, 4731, 4663, 4595, 4528, 4461, 4395, 4328, 4263,
    4197, 4133, 4068, 4004, 3941, 3878, 3815, 3753, 3692, 3630, 3570, 3510, 3450, 3391, 3333, 3275,
    3218, 3161, 3105, 3049, 2994, 2940, 2886, 2833, 2780, 2728, 2677, 2626, 2576, 2526, 2477, 2429,
    2381, 2334, 2287, 2242, 2196, 2152, 2107, 2064, 2021, 1979, 1937, 1896, 1856, 1816, 1777, 1739,
    1701, 1663, 1626, 1590, 1555, 1520, 1485, 1451, 1418, 1385, 1353, 1322, 1291, 1260, 1230, 1201,
    1172, 1144, 1116, 1089, 1062, 1036, 1010,  985,  960,  936,  912,  889,  866,  844,  822,  801,
    780,   759,  739,  720,  700,  682,  663,  645,  628,  611,  594,  577,  561,  546,  530,  515,
    501,   487,  473,  459,  446,  433,  420,  408,  396,  384,  373,  362,  351,  340,  330,  320,
    310,   301,  292,  283,  274,  265,  257,  249,  241,  234,  226,  219,  212,  205,  198,  192,
    186,   180,  174,  168,  162,  157,  152,  147,  142,  137,  132,  128,  123,  119,  115,  111
};

static int Noise_Noise_LUT_FHD[32] = { 0,  1,  2,  3,  4,  5,  5,  6,  6,  7,  7,  6,  6,  5,  5,  4,  4,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3};
static int Noise_Noise_LUT_SD[32]  = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  8,  7,  6,  5,  5,  6,  7,  8,  8,  9,  9,  9,  8,  8,  7,  7,  6,  5,  4,  3,  2,  2,  2};
static int Noise_Noise_LUT_HD[32]  = { 0,  1,  2,  3,  4,  5,  6,  6,  7,  7,  7,  8,  8,  8,  8,  7,  7,  7,  6,  6,  5,  4,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2};

static int Alpha_LUT[20][32] =    /* adjust for MCNR when demo on , when noise is very large in 98mv200*/
{
    ////        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    /*  0 */ {12, 15, 19, 23, 27, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 0
    /*  1 */ {11, 14, 17, 21, 24, 27, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 1
    /*  2 */ {10, 12, 15, 17, 22, 25, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 2
    /*  3 */ { 9, 11, 13, 16, 19, 22, 25, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 3
    /*  4 */ { 8,  9, 11, 13, 16, 19, 20, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 4
    /*  5 */ { 8,  9, 10, 11, 13, 16, 18, 21, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 5
    /*  6 */ { 8,  8,  9, 10, 12, 14, 17, 20, 22, 25, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 6
    /*  7 */ { 8,  8,  8,  9, 10, 12, 14, 17, 20, 22, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 7
    /*  8 */ { 8,  8,  8,  8,  9, 10, 12, 15, 18, 20, 22, 24, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 8
    /*  9 */ { 8,  8,  7,  7,  8,  9, 10, 12, 15, 18, 21, 23, 25, 26, 27, 28, 29, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 9
    /* 10 */ {13, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 10
    /* 11 */ {12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 11
    /* 12 */ {11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 12
    /* 13 */ {11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 13
    /* 14 */ {10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 14
    /* 15 */ {10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 15
    /* 16 */ { 9, 10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 16
    /* 17 */ { 9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 17
    /* 18 */ { 8,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31}, // 18
    /* 19 */ { 8,  8,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 19, 21, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31}  // 19
};

static int Strong_Alpha_LUT[32] = { 4,  4,  4,  4,  5,  5,  5,  6,  6,  7,  8,  9, 10, 11, 12, 13, 15, 17, 20, 23, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31};
int miniAlpha[32] = {24, 15, 10,  8,  6,  5,  4,  4,  3,  3,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};


static MCNR_INPUT_INFO     stInputInf;
static MCNR_INPUT_REG      stInputReg;
static SNR_OUTPUT_REG      stOutputSnrReg;
static MCNR_TIMING_PARAM   stParam;
/*--------------------------------------------------------------------------------*
Function        :   HI_S32 pq_mng_MCNR_InitCfg(MCNR_OUTPUT_REG *pReg, MCNR_INPUT_INFO *pInf)
Description     :   初始化MCNR参数
Calls           :
Data Accessed   :
Data Updated    :
Input           :       pReg.CNcomment:输出逻辑寄存器值 CNend;
                pInf.CNcomment:输出中间变量 CNend;
Output          :   NA
Return          :       HI_SUCCESS     success.  CNcomment:成功 CNend
Others          :       NA
*--------------------------------------------------------------------------------*/
static HI_S32 pq_mng_MCNR_InitCfg(MCNR_INPUT_INFO *pInf)
{
    pInf->Cfg_InputPort = 0;

    /* info */
    pInf->Cfg_ND_NoiseDetectEn = 1;
    pInf->Cfg_ND_FlatInfoXMin   = 0;    // ND_FlatInfoXMin
    pInf->Cfg_ND_FlatInfoXMax   = 56;   // ND_FlatInfoXMax
    pInf->Cfg_ND_FlatInfoYMin   = 0;    // ND_FlatInfoYMin
    pInf->Cfg_ND_FlatInfoYMax   = 64;   // ND_FlatInfoYMax


    pInf->Cfg_ME_Adj_MV_Max          = 24;
    pInf->Cfg_ME_Adj_MV_Min = 12;   // atv:12,  av:12,  sd;12,  fhd:10
    pInf->Cfg_MD_YMotionGain = 15;
    pInf->Cfg_MD_YMotionCore = -6;
    pInf->Cfg_MD_CMotionGain = 15;
    pInf->Cfg_MD_CMotionCore = -6;
    pInf->Cfg_ME_MotionEstimationEn  = 1;    // ME_MotionEstimateEn

    pInf->wRGNum = 0;
    pInf->hRGNum = 0;
    pInf->pRGMV_mag = 0;

    pInf->Cfg_MC_AutoMotionMappingEn = 0;    // MC_AutoMotionMappingEn

    /* inf */
    pInf->Cfg_MC_YMotionGain = 15; //16
    pInf->Cfg_MC_YMotionCore = 5;   // atv:0,       otherwise:5

    pInf->Cfg_MC_CMotionGain = 15;
    pInf->Cfg_MC_CMotionCore = 5;

    pInf->Cfg_TF_AutoMotionAlphaEn = 0;

    return HI_SUCCESS;
}

/*--------------------------------------------------------------------------------*
Function        :   HI_S32 pq_mng_MCNR_GetMCTFBlendingAlpha(HI_S32 Index, HI_S32 X_Min, HI_S32 X_Max, HI_S32 Y_Min, HI_S32 Y_Max)
Description     :   获取Alhpa-blend 的结果
Calls           :
Data Accessed   :
Data Updated    :
Input           : Index.CNcomment:索引 CNend;
                  X_Min.CNcomment:最小X CNend;
                  X_Max.CNcomment:最大X CNend;
                  Y_Min.CNcomment:最小Y CNend;
                  Y_Max.CNcomment:最大Y CNend;
Output          :   NA
Return          :   result     .  CNcomment:结果 CNend
Others          :   NA
*--------------------------------------------------------------------------------*/







HI_S32 pq_mng_CopyU32ByBitWithSignal(HI_U32 u32Src, HI_U32 u32SrcStartBit, HI_S32 *pu32Dst, HI_U32 u32DstStartBit, HI_U32 u32Num)
{
    HI_U32 u32SrcTmp = 0;

    PQ_CHECK_NULL_PTR(pu32Dst);
    if (((u32SrcStartBit + u32Num) > 32) || (u32DstStartBit + u32Num) > 32)
    {
        return HI_FAILURE;
    }

    /* 保存src需要拷贝的u32Num个bits，并移动到dst指定的位置; 将高位清0 */
    u32SrcTmp = u32Src << (32 - u32SrcStartBit - u32Num);

    /* 将指定的u32Num位移到低bit位上 */
    u32SrcTmp = u32SrcTmp >> (32 - u32Num);

    if (((u32SrcTmp >> ( u32Num - 1)) & 0x1) == 1)
    {
        //*pu32Dst = ((u32SrcTmp&((1<<u32Num) -1)) - (1<<u32Num));
        *pu32Dst = 0 - ((u32SrcTmp ^ ((1 << u32Num) - 1)) + 1);
    }
    else
    {
        *pu32Dst = u32SrcTmp & ((1 << u32Num) - 1);
    }

    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetHRGNum(HI_BOOL bInterlace, HI_S32 YHeight, HI_S32 *pHRGNum)
{
    *pHRGNum = YHeight / 16; //不使用四舍五?


    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetWRGNum(HI_S32 YWidth, HI_S32 *pWRGNum)
{
    if (YWidth > 1920)
    {
        *pWRGNum = YWidth / (2 * 64);
    }
    else
    {
        *pWRGNum = YWidth / 64;
    }

    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetMEHistMV20(HI_S32 MV_y, HI_S32 *pME_HistMV22, HI_S32 *pME_HistMV23, HI_S32 *pME_HistMV24)
{
    if ((-2 < MV_y) && (MV_y < 0))
    {
        *pME_HistMV22 = *pME_HistMV22 + 1;
    }
    else if ((0 < MV_y) && (MV_y < 2))
    {
        *pME_HistMV23 = *pME_HistMV23 + 1;
    }
    else
    {
        *pME_HistMV24 = *pME_HistMV24 + 1;
    }

    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetMEHistMv21(HI_S32 MV_x, HI_S32 *pME_HistMV20, HI_S32 *pME_HistMV21, HI_S32 *pME_HistMV24)
{
    if ((-2 < MV_x) && (MV_x < 0))
    {
        *pME_HistMV20 = *pME_HistMV20 + 1;
    }
    else if ((0 < MV_x) && (MV_x < 2))
    {
        *pME_HistMV21 = *pME_HistMV21 + 1;
    }
    else
    {
        *pME_HistMV24 = *pME_HistMV24 + 1;
    }

    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetMEHistMv1(HI_S32 tmpMV, HI_S32 *pME_HistMV10, HI_S32 *pME_HistMV11,
                                       HI_S32 *pME_HistMV12, HI_S32 *pME_HistMV13, HI_S32 *pME_HistMV14)
{
    if (0 >= tmpMV)
    {
        *pME_HistMV10 = *pME_HistMV10 + 1;
    }
    else if (1 >= tmpMV)
    {
        *pME_HistMV11 = *pME_HistMV11 + 1;
    }
    else if (8 >= tmpMV)
    {
        *pME_HistMV12 = *pME_HistMV12 + 1;
    }
    else if (16 >= tmpMV)
    {
        *pME_HistMV13 = *pME_HistMV13 + 1;
    }
    else
    {
        *pME_HistMV14 = *pME_HistMV14 + 1;
    }

    return HI_SUCCESS;
}

inline HI_S32 pq_mng_MCNR_GetMEHistMag2(HI_S32 MV_mag, HI_S32 *pME_HistMag0, HI_S32 *pME_HistMag1,
                                        HI_S32 *pME_HistMag2, HI_S32 *pME_HistMag3, HI_S32 *pME_HistMag4)
{
    if (0 >= MV_mag)
    {
        *pME_HistMag0 = *pME_HistMag0 + 1;
    }
    else if (2 >= MV_mag)
    {
        *pME_HistMag1 = *pME_HistMag1 + 1;
    }
    else if (4 >= MV_mag)
    {
        *pME_HistMag2 = *pME_HistMag2 + 1;
    }
    else if (8 >= MV_mag)
    {
        *pME_HistMag3 = *pME_HistMag3 + 1;
    }
    else
    {
        *pME_HistMag4 = *pME_HistMag4 + 1;
    }

    return HI_SUCCESS;
}

static HI_S32 pq_mng_MCNR_EstimationGlobalMotionMCME(MCNR_INPUT_INFO *pInfIn, HI_VOID *pRGMV, HI_U32 u32Stride)
{
    HI_S32 i;
    HI_S32 wRGNum, hRGNum;
    HI_S32 MV_x = 0;
    HI_S32 MV_y = 0;
    HI_S32 tmpMV;
    HI_S32 MV_mag = 0;
    //    HI_S32 ME_HistMV00 = 0;
    HI_S32 ME_HistMV01 = 0;
    HI_S32 ME_HistMV02 = 0;
    HI_S32 ME_HistMV03 = 0;
    HI_S32 ME_HistMV04 = 0;
    HI_S32 ME_HistMV10 = 0;
    HI_S32 ME_HistMV11 = 0;
    HI_S32 ME_HistMV12 = 0;
    HI_S32 ME_HistMV13 = 0;
    HI_S32 ME_HistMV14 = 0;
    HI_S32 ME_HistMV20 = 0;
    HI_S32 ME_HistMV21 = 0;
    HI_S32 ME_HistMV22 = 0;
    HI_S32 ME_HistMV23 = 0;
    HI_S32 ME_HistMV24 = 0;
    HI_S32 ME_HistMag0 = 0;
    HI_S32 ME_HistMag1 = 0;
    HI_S32 ME_HistMag2 = 0;
    HI_S32 ME_HistMag3 = 0;
    HI_S32 ME_HistMag4 = 0;
    HI_S32 MVNum;
    MCMVSTRUCT RGMV;
    //HI_U32 *tmp = NULL;
    HI_U32 TmpGM;
    HI_S32 nCol, nRow;
    HI_S32 GlobalMotion;
    HI_S32 saltusVal;
    HI_S32 SaltusLevel = 0;
    HI_S32 meanPreGM;
    HI_S32 NonrgmeLevel;
    HI_S32 HMVCnt1 = 0;
    HI_S32 VMVCnt1 = 0;

    HI_S32 HMVCnt2 = 0;
    HI_S32 VMVCnt2 = 0;

    HI_S32 Inf_ME_HMVCntTmp[40];
    HI_S32 Inf_ME_VMVCntTmp[40];

    RGMV.x = 0;
    RGMV.mvy = 0;
    RGMV.mag = 0;

    pq_mng_MCNR_GetHRGNum(pInfIn->bInterlace, pInfIn->YHeight, &hRGNum);
    pq_mng_MCNR_GetWRGNum(pInfIn->YWidth, &wRGNum);

    for (nRow = 0; nRow < hRGNum; nRow++)
    {
        for (nCol = 0; nCol < wRGNum; nCol++)
        {
            /*解析RGMV的参数*/
            /* 96mv200:
            |63     |62     |61 55|54 51|50 44|43 36|35 29|28 19|18 9|8 0|
            ----------------------------------------------------------------------------
            |1'b0 |3'b0 | 3~0 |    9~0   |   7~0  |    9~0   |    9~0   |    9~0   |    8~0  |
            ----------------------------------------------------------------------------
            |1'b0 |repeatflag|meanmvx|ls|vsad|mvy|vstillsad|mag|sad|   x   |
            */
            pq_mng_CopyU32ByBitWithSignal(*(HI_U32 *)((HI_U32 *)pRGMV + (nRow * u32Stride / 4 + nCol * 2)), 0, &(RGMV.x), 0, 9); //x[8:0]
            pq_mng_CopyU32ByBitWithSignal(*(HI_U32 *)((HI_U32 *)pRGMV + (nRow * u32Stride / 4 + nCol * 2) + 1), 5, &(RGMV.mvy), 0, 8); //mvy[43:36]
            pq_mng_CopyU32ByBitWithSignal(*(HI_U32 *)((HI_U32 *)pRGMV + (nRow * u32Stride / 4 + nCol * 2)), 19, &(RGMV.mag), 0, 10); //mag[28:19]

            MV_x = RGMV.x;
            MV_y = RGMV.mvy;
            MV_mag = RGMV.mag;
            tmpMV = ABS(MV_x) + ABS(MV_y);

            pq_mng_MCNR_GetMEHistMv1(tmpMV, &ME_HistMV10, &ME_HistMV11, &ME_HistMV12, &ME_HistMV13, &ME_HistMV14);
            pq_mng_MCNR_GetMEHistMv21(MV_x, &ME_HistMV20, &ME_HistMV21, &ME_HistMV24);
            pq_mng_MCNR_GetMEHistMV20(MV_y, &ME_HistMV22, &ME_HistMV23, &ME_HistMV24);
            pq_mng_MCNR_GetMEHistMag2(MV_mag, &ME_HistMag0, &ME_HistMag1, &ME_HistMag2, &ME_HistMag3, &ME_HistMag4);
        }
    }

    MVNum = hRGNum * wRGNum;

    if (pInfIn->YWidth < 1920)
    {
        GlobalMotion = NR_CLIP2( 320000, 640000 * (ME_HistMV01 + ME_HistMV02 + 2 * ME_HistMV03 + 2 * ME_HistMV04) / 7 / MVNum);
        TmpGM = 1600 * (ME_HistMV11 + ME_HistMV12 + ME_HistMV13 + ME_HistMV14) / MVNum;
        GlobalMotion = 100 * NR_CLIP2( 3200, TmpGM);
        TmpGM = 400 * (8 * ME_HistMag0 + 4 * ME_HistMag1 + 2 * ME_HistMag2 + ME_HistMag3 + ME_HistMag4) / MVNum;
        NonrgmeLevel = 100 * NR_CLIP2( 2400, TmpGM);

        memcpy(Inf_ME_HMVCntTmp, g_McnrTimingInfo.Inf_ME_HMVCnt + 1, sizeof(HI_S32) * 39);
        memcpy(Inf_ME_VMVCntTmp, g_McnrTimingInfo.Inf_ME_VMVCnt + 1, sizeof(HI_S32) * 39);

        Inf_ME_HMVCntTmp[39] = (ME_HistMV20 - ME_HistMV21);
        Inf_ME_VMVCntTmp[39] = (ME_HistMV22 - ME_HistMV23);

        memcpy(g_McnrTimingInfo.Inf_ME_HMVCnt, Inf_ME_HMVCntTmp, sizeof(HI_S32) * 40);
        memcpy(g_McnrTimingInfo.Inf_ME_VMVCnt, Inf_ME_VMVCntTmp, sizeof(HI_S32) * 40);

        for (i = 0; i < 40; i++)
        {
            HMVCnt1 += Inf_ME_HMVCntTmp[i];
            VMVCnt1 += Inf_ME_VMVCntTmp[i];
        }

        for (i = 20; i < 40; i++)
        {
            HMVCnt2 += Inf_ME_HMVCntTmp[i];
            VMVCnt2 += Inf_ME_VMVCntTmp[i];
        }

        HMVCnt1 /= 40;
        VMVCnt1 /= 40;
        HMVCnt2 /= 20;
        VMVCnt2 /= 20;
        g_McnrTimingInfo.Inf_ME_AsistGlobalMotion1 = NR_CLIP3(0, 16, 16 * (ABS(HMVCnt1) / 3 + ABS(VMVCnt1)) / MVNum - NR_CLIP(g_McnrTimingInfo.Inf_SCD_DarknessLevel - 18));
        g_McnrTimingInfo.Inf_ME_AsistGlobalMotion2 = NR_CLIP3(0, 16, 16 * (ABS(HMVCnt2)   + ABS(VMVCnt2)) / MVNum - NR_CLIP(g_McnrTimingInfo.Inf_SCD_DarknessLevel - 18));
    }
    else
    {
        TmpGM = 1600 * (ME_HistMV11 + 2 * ME_HistMV12 + 2 * ME_HistMV13 + 2 * ME_HistMV14) / MVNum;
        GlobalMotion = 100 * NR_CLIP2( 3200, TmpGM);
        TmpGM = 400 * (5 * ME_HistMag0 + 4 * ME_HistMag1 + 4 * ME_HistMag2 + 2 * ME_HistMag3 + ME_HistMag4) / MVNum;
        NonrgmeLevel = 100 * NR_CLIP2( 2400, TmpGM);
        g_McnrTimingInfo.Inf_ME_AsistGlobalMotion1 = 0;
        g_McnrTimingInfo.Inf_ME_AsistGlobalMotion2 = 0;
    }

    meanPreGM = MAX(10000, (g_McnrTimingInfo.Inf_ME_preGlobalMotion[1]
                            + g_McnrTimingInfo.Inf_ME_preGlobalMotion[2]
                            + g_McnrTimingInfo.Inf_ME_preGlobalMotion[3]) / 3);

    if (GlobalMotion <= 30000)
    {
        saltusVal = 0;
    }
    else
    {
        if (GlobalMotion - meanPreGM < 20000)
        {
            saltusVal = 0;
        }
        else
        {
            saltusVal = NR_CLIP(10000 * GlobalMotion / meanPreGM - 10000);
        }
    }

/*
    SaltusLevel = 0;//NR_CLIP2( 310000,saltusVal*10+5);

    if (SaltusLevel >= 100000)
    {
        g_McnrTimingInfo.Inf_ME_SaltusFlag = 1;
    }
*/
    g_McnrTimingInfo.Inf_ME_SaltusFlag = g_McnrTimingInfo.Inf_ME_SaltusFlag - 1;

    if (g_McnrTimingInfo.Inf_ME_SaltusFlag < -2)
    {
        g_McnrTimingInfo.Inf_ME_SaltusFlag = -2;
    }

    if (SaltusLevel >= g_McnrTimingInfo.Inf_ME_preSaltusLevel[2]
        || SaltusLevel >= g_McnrTimingInfo.Inf_ME_preSaltusLevel[1])
    {
        SaltusLevel = (g_McnrTimingInfo.Inf_ME_preSaltusLevel[1]
                       + g_McnrTimingInfo.Inf_ME_preSaltusLevel[2]
                       + 6 * SaltusLevel) / 8;
    }
    else if ((g_McnrTimingInfo.Inf_ME_SaltusFlag < 0) && (g_McnrTimingInfo.Inf_ME_SaltusFlag > -4))
    {
        SaltusLevel = (g_McnrTimingInfo.Inf_ME_preSaltusLevel[2] + SaltusLevel) / 2;
    }
    else
    {
        SaltusLevel = (g_McnrTimingInfo.Inf_ME_preSaltusLevel[0]
                       + g_McnrTimingInfo.Inf_ME_preSaltusLevel[1]
                       + 2 * g_McnrTimingInfo.Inf_ME_preSaltusLevel[2]
                       + 4 * SaltusLevel) / 8;
    }

    if (SaltusLevel >= 20000)
    {
        GlobalMotion = (g_McnrTimingInfo.Inf_ME_preGlobalMotion[2]
                        + g_McnrTimingInfo.Inf_ME_preGlobalMotion[3]
                        + 6 * GlobalMotion) / 8;
    }
    else
    {
        GlobalMotion = (g_McnrTimingInfo.Inf_ME_preGlobalMotion[0]
                        + g_McnrTimingInfo.Inf_ME_preGlobalMotion[1]
                        + g_McnrTimingInfo.Inf_ME_preGlobalMotion[2]
                        + g_McnrTimingInfo.Inf_ME_preGlobalMotion[3]
                        + GlobalMotion) / 5;
    }

    NonrgmeLevel = (g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[0]
                    + g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[1]
                    + g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[2]
                    + g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[3]
                    + NonrgmeLevel) / 5;

    for (i = 0; i < 2; i++)
    {
        g_McnrTimingInfo.Inf_ME_preSaltusLevel[i]  = g_McnrTimingInfo.Inf_ME_preSaltusLevel[i + 1];
    }

    g_McnrTimingInfo.Inf_ME_preSaltusLevel[i] = SaltusLevel;

    for (i = 0; i < 3; i++)
    {
        g_McnrTimingInfo.Inf_ME_preGlobalMotion[i] = g_McnrTimingInfo.Inf_ME_preGlobalMotion[i + 1];
        g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[i] = g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[i + 1];
    }

    g_McnrTimingInfo.Inf_ME_preGlobalMotion[i] = GlobalMotion;
    g_McnrTimingInfo.Inf_ME_preNonrgmeLevel[i] = NonrgmeLevel;

    g_McnrTimingInfo.Inf_ME_SaltusLevel = (int)NR_CLIP2( 31, (SaltusLevel + 5000) / 10000);

    g_McnrTimingInfo.Inf_ME_GlobalMotion = (int)NR_CLIP2( 31, (GlobalMotion + 5000) / 10000);

    g_McnrTimingInfo.Inf_ME_NonrgmeLevel = (int)NR_CLIP2( 24, (NonrgmeLevel + 5000) / 10000);

    if (g_McnrTimingInfo.Inf_ME_GlobalMotion == 0)
    {
        /*解析RGMV的参数*/
        /* 98mv200:
        |63 61|60 57|56      47|46    39|38      29|28      19|18       9|8       0|
        ----------------------------------------------------------------------------
        |3'b0 | 3~0 |    9~0   |   7~0  |    9~0   |    9~0   |    9~0   |    8~0  |
        ----------------------------------------------------------------------------
        | Rs  |  ls |   vsad   |   mvy  | vstiilsad|    mag   |    sad   |     x   |
        */
        g_McnrTimingInfo.Inf_ME_NonrgmeLevel = (int)NR_CLIP2( 21, g_McnrTimingInfo.Inf_ME_NonrgmeLevel);
    }
    else
    {
        g_McnrTimingInfo.Inf_ME_NonrgmeLevel = (int)NR_CLIP3(0, 24, g_McnrTimingInfo.Inf_ME_NonrgmeLevel - NR_CLIP(1 - g_McnrTimingInfo.Inf_ME_GlobalMotion));
    }

    return HI_SUCCESS;
}

HI_S32 pq_mng_MCND_getFlatInfo(HI_S32 Index, HI_S32 X_Min, HI_S32 X_Max, HI_S32 Y_Min, HI_S32 Y_Max)
{
    HI_S32 x;
    HI_S32 B;
    HI_S32 ThreeSigma;
    HI_S32 result;

    ThreeSigma = ((X_Max > X_Min) ? (X_Max - X_Min) : 255);

    if (Index < X_Min)
    {
        x = 0; /* 0.0 */
    }
    else if (Index > X_Max)
    {
        x = 255; /* 1.0 */
    }
    else
    {
        x = NR_CLIP255(255 * (Index - X_Min) / ThreeSigma);
    }

    B = LUT256[x];
    result = ((Y_Max - Y_Min) * (10000 - B) + 5000) / 10000 + Y_Min;

    return  NR_CLIP3(Y_Min, Y_Max, result);
}

HI_S32 pq_mng_MCNR_GetNoiseRatio(HI_BOOL bInterlace, HI_S32 *pNoiseRatio)
{
    if (HI_TRUE == bInterlace)
    {
        *pNoiseRatio = 10000;
    }
    else
    {
        *pNoiseRatio = 13000; //1.3;
    }

    return HI_SUCCESS;
}

HI_S32 pq_mng_MCND_getNoiseLevel(MCNR_INPUT_REG *pReg, MCNR_INPUT_INFO *pInfIn)
{
    HI_S32 i;
    HI_S32 rawNoise;
    HI_S32 noiseInfo;
    HI_S32 flatRatio;
    HI_S32 reliability;
    HI_S32 noiseLevel;
    HI_U32 tmp1 = 1;
    HI_U32 tmp2 = 1;

    HI_S32 maxGM = 0;
    HI_S32 globalMotion;
    HI_S32 noiseRatio;

    HI_S32 flatStr;

    for (i = 0; i < 9; i++)
    {
        g_McnrTimingInfo.Inf_ND_preGM[i] = g_McnrTimingInfo.Inf_ND_preGM[i + 1];
        if (maxGM <= g_McnrTimingInfo.Inf_ND_preGM[i])
        {
            maxGM = g_McnrTimingInfo.Inf_ND_preGM[i];
        }
    }

    g_McnrTimingInfo.Inf_ND_preGM[i] = NR_CLIP2( 21, g_McnrTimingInfo.Inf_ME_GlobalMotion);
    globalMotion = MAX(maxGM, g_McnrTimingInfo.Inf_ND_preGM[i]);

    if ((g_McnrTimingInfo.Inf_ME_NonrgmeLevel >= 14) && (globalMotion <= 6))
    {
        globalMotion = NR_CLIP3(globalMotion, 7, globalMotion * NR_CLIP3(0, 2, g_McnrTimingInfo.Inf_ME_NonrgmeLevel / 2 - 7));
    }

    pq_mng_MCNR_GetNoiseRatio(pInfIn->bInterlace, &noiseRatio);

    tmp1 = (pReg->Reg_ND_SumNoiseInfoMax + 2 * pReg->Reg_ND_SumNoiseInfoMed + 3 * pReg->Reg_ND_SumNoiseInfoMin);

    if (pInfIn->YWidth < 1920)
    {
        tmp2 = (pReg->Reg_ND_NoisePointCntMed + 2 * pReg->Reg_ND_NoisePointCntMed + 3 * pReg->Reg_ND_NoisePointCntMin);
    }
    else
    {
        tmp2 = (pReg->Reg_ND_NoisePointCntMax + 2 * pReg->Reg_ND_NoisePointCntMed + 3 * pReg->Reg_ND_NoisePointCntMin);
    }

    if (tmp2 > 0)
    {
        tmp1 = noiseRatio * (tmp1 / tmp2);
    }
    else
    {
        tmp1 = 0;
    }

    rawNoise    = NR_CLIP2( 1270000, tmp1);

    if (pInfIn->bInterlace == 1)
    {
        flatRatio = (64 * (pReg->Reg_ND_NoisePointCntMax +  3 * pReg->Reg_ND_NoisePointCntMed + 4 * pReg->Reg_ND_NoisePointCntMin + 4)) / pInfIn->YWidth / pInfIn->YHeight;
        flatStr = (512 * pReg->Reg_ND_NoisePointNum) / pInfIn->YWidth / pInfIn->YHeight;
    }
    else
    {
        flatRatio = (32 * (pReg->Reg_ND_NoisePointCntMax +  3 * pReg->Reg_ND_NoisePointCntMed + 4 * pReg->Reg_ND_NoisePointCntMin + 4)) / pInfIn->YWidth / pInfIn->YHeight;
        flatStr = (256 * pReg->Reg_ND_NoisePointNum) / pInfIn->YWidth / pInfIn->YHeight;
    }

    reliability = pq_mng_MCND_getFlatInfo(flatRatio, pInfIn->Cfg_ND_FlatInfoXMin, pInfIn->Cfg_ND_FlatInfoXMax, pInfIn->Cfg_ND_FlatInfoYMin, pInfIn->Cfg_ND_FlatInfoYMax);
    reliability = NR_CLIP3(0, 54, reliability);
    noiseInfo = rawNoise * reliability / 54;

    if (pInfIn->YWidth > 960)
    {
        noiseLevel = NR_CLIP3(40000, 320000, noiseInfo);
    }
    else
    {
        noiseLevel = NR_CLIP2( 320000, noiseInfo);
    }

    if (pInfIn->YWidth < 1920)
    {
        globalMotion = (int)NR_CLIP3(0, 15, NR_CLIP(globalMotion - NR_CLIP(noiseLevel / 10000 - 9)));
        noiseLevel = NR_CLIP3((6 + NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ME_AsistGlobalMotion1 - 2)) * noiseLevel / 16, 320000, noiseLevel * NR_CLIP(6 - NR_CLIP(globalMotion - 6)) / 6);
    }
    else
    {
        globalMotion = (int)NR_CLIP3(0, 15, NR_CLIP(globalMotion - NR_CLIP(noiseLevel / 10000 - 9)));
        noiseLevel = NR_CLIP3(2 * noiseLevel / 5, 320000, noiseLevel * NR_CLIP(6 - NR_CLIP(globalMotion - 7)) / 6);
    }

    if ((g_McnrTimingInfo.Inf_ME_SaltusLevel >= 8) && (pInfIn->YWidth >= 1920))
    {
        noiseLevel = NR_CLIP3(0, noiseLevel, NR_CLIP(5 - g_McnrTimingInfo.Inf_ND_NoiseLevel));
    }

    noiseLevel = (g_McnrTimingInfo.Inf_ND_preNoiseLevel[0] + g_McnrTimingInfo.Inf_ND_preNoiseLevel[1] + 2 * g_McnrTimingInfo.Inf_ND_preNoiseLevel[2] + 3 * noiseLevel) / 7;

    g_McnrTimingInfo.Inf_ND_preNoiseLevel[0] = g_McnrTimingInfo.Inf_ND_preNoiseLevel[1];
    g_McnrTimingInfo.Inf_ND_preNoiseLevel[1] = g_McnrTimingInfo.Inf_ND_preNoiseLevel[2];
    g_McnrTimingInfo.Inf_ND_preNoiseLevel[2] = noiseLevel;
    g_McnrTimingInfo.Inf_ND_rawNoiseLevel       = (int)NR_CLIP2( 31, (noiseInfo + 5000) / 10000);
    g_McnrTimingInfo.Inf_ND_TextureDenseLevel   = (int)NR_CLIP3(0, 16, 16 - flatStr);

    if ((g_McnrTimingInfo.Inf_SCD_DarknessLevel >= 15) && (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 5))
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel  = (int)NR_CLIP3(0, 8 - NR_CLIP3(0, 3, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 21),
                                              (noiseLevel - 10000 * NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 21) + 5000) / 10000);
    }
    else if (g_McnrTimingInfo.Inf_SCD_DarknessLevel >= 20)
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel  = (int)NR_CLIP3(0, 8 - NR_CLIP3(0, 3, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 21),
                                              (noiseLevel - 10000 * NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 21) + 5000) / 10000);
    }
    else if ((g_McnrTimingInfo.Inf_SCD_DarknessLevel <= 12) && (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 1))
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel = (int)NR_CLIP3(0, 31, (noiseLevel + 5000 + 10000 * NR_CLIP(2 - g_McnrTimingInfo.Inf_ME_GlobalMotion)) / 10000);
    }
    else
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel = (int)NR_CLIP3(0, 31, (noiseLevel + 5000) / 10000);
    }

    if ((g_McnrTimingInfo.Inf_SCD_DarknessLevel <= 8) && (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 1)
        && (reliability <= 20) && (g_McnrTimingInfo.Inf_ND_TextureDenseLevel == 0) && (g_McnrTimingInfo.Inf_ND_NoiseLevel <= 7))
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel += 1;
    }

    if ((g_McnrTimingInfo.Inf_SCD_DarknessLevel <= 8) && (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 1)
        && (reliability <= 15) && (g_McnrTimingInfo.Inf_ND_TextureDenseLevel == 0) && (g_McnrTimingInfo.Inf_ND_NoiseLevel <= 7))
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel += 1;
    }

    return HI_SUCCESS;
}

static HI_S32 pq_mng_MCNR_UpdateSNRRegisters(HI_U32 u32SceneChange, SNR_OUTPUT_REG *pRegOut)
{
    HI_S32 SNR_Motion_Ratio;

    if ((g_McnrTimingInfo.Inf_bTnterlace == 0) && (g_McnrTimingInfo.Inf_Width == 1920))
    {
        SNR_Motion_Ratio = NR_CLIP3(0, 24, 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_rawNoiseLevel - 2) / 2 + 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel));
    }
    else
    {
        if (g_McnrTimingInfo.Inf_ME_NonrgmeLevel == 24)
        {
            SNR_Motion_Ratio = NR_CLIP3(0, 24, 12 + 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_rawNoiseLevel - 2) / 2 + 2 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 1));
        }
        else
        {
            SNR_Motion_Ratio = NR_CLIP3(0, 8, NR_CLIP(g_McnrTimingInfo.Inf_ND_rawNoiseLevel - 2) / 2 + NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 1));
        }
    }
    pRegOut->MotionAlpha = NR_CLIP3(0, 32, SNR_Motion_Ratio);
    pRegOut->SceneChange = u32SceneChange;

    return HI_SUCCESS;
}

HI_S32 pq_mng_MCNR_UpdateTimingParam( MCNR_INPUT_INFO *pInf, MCNR_TIMING_PARAM *tParam)
{
    int i;
    int NoiseLevel;
    int TextureDenseLevel;
    int YBlendingMin;
    int CBlendingMin;
    int alphaCnt;
    int gm_adj1[7] = {6, 5, 4, 3, 2, 1, 0};
    int GM_Gain[16] = { 0,  0,  0,  1,  1,  2,  3,  4,  5,  5,  6,  6,  6,  6,  6,  6};
    int NL_Gain[24] = { 0,  0,  0,  0,  0,  0, -1, -2, -3, -4, -5, -6, -7, -8, -8, -9, -9, -9, -10, -10, -10, -11, -11, -11};
    int ref_mv_level;
    /*** Motion Detection ***/

    tParam->Reg_MD_Alpha1   = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_NoiseLevel - 3);
    tParam->Reg_MD_Alpha2   = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_NoiseLevel - 9);
    if (g_McnrTimingInfo.Inf_ND_TextureDenseLevel >= 5)
    {
        tParam->Reg_MD_Alpha1   = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_TextureDenseLevel - 6);
        tParam->Reg_MD_Alpha2   = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_TextureDenseLevel - 10);
    }

    tParam->Reg_MD_YMDGain  = NR_CLIP3(0, 63, tParam->Reg_MD_YMDGain);
    tParam->Reg_MD_YMDCore  = NR_CLIP3(-16, 15, tParam->Reg_MD_YMDCore + NR_CLIP3(0, 9, NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 9) / 2));
    tParam->Reg_MD_CMDGain  = NR_CLIP3(0, 63, tParam->Reg_MD_CMDGain);
    tParam->Reg_MD_CMDCore  = NR_CLIP3(-16, 15, tParam->Reg_MD_CMDCore + NR_CLIP3(0, 9, NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 9) / 2));
    if (sg_u32MCNRStr > 50)
    {
        tParam->Reg_MC_YMotionGain  = NR_CLIP3(0, 63, tParam->Reg_MC_YMotionGain + 63 * (50 - sg_u32MCNRStr) / 50);
        tParam->Reg_MC_CMotionGain  = NR_CLIP3(0, 63, tParam->Reg_MC_CMotionGain + 63 * (50 - sg_u32MCNRStr) / 50);
    }
    if ((g_McnrTimingInfo.Inf_ME_AsistGlobalMotion1 == 2)
        && (g_McnrTimingInfo.Inf_ME_AsistGlobalMotion2 > 2)
        && (g_McnrTimingInfo.Inf_ME_GlobalMotion > 10))
    {
        ref_mv_level = 0;
    }
    else if ((g_McnrTimingInfo.Inf_ME_AsistGlobalMotion1 == 2)
             && (g_McnrTimingInfo.Inf_ME_AsistGlobalMotion2 == 2)
             && (g_McnrTimingInfo.Inf_ME_GlobalMotion > 10))
    {
        ref_mv_level = 1;
    }
    else
    {
        ref_mv_level = 2;
    }

    /***  Motion Detection  ***/
    /*** Motion Vector Estimation ***/
    if (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 3)
    {
        tParam->Reg_ME_DiscardSMVXEn = 1;
        tParam->Reg_ME_DiscardSMVYEn = 1;

        tParam->Reg_ME_SMVXThd = 3;
        tParam->Reg_ME_SMVYThd = 5;
    }
    else if (g_McnrTimingInfo.Inf_ME_GlobalMotion <= 5)
    {
        tParam->Reg_ME_DiscardSMVXEn = 1;
        tParam->Reg_ME_DiscardSMVYEn = 1;
        tParam->Reg_ME_SMVXThd = 2;
        tParam->Reg_ME_SMVYThd = 4;
    }
    else
    {
        tParam->Reg_ME_DiscardSMVXEn = 0;
        tParam->Reg_ME_DiscardSMVYEn = 0;
        tParam->Reg_ME_SMVXThd = 0;
        tParam->Reg_ME_SMVYThd = 0;
    }

    tParam->Reg_ME_Mag_Pnl_Gain_0MV = NR_CLIP3(0, 256, 127 - g_McnrTimingInfo.Inf_ME_GlobalMotion);
    tParam->Reg_ME_Mag_Pnl_Core_0MV = NR_CLIP1023(63 - 8 * g_McnrTimingInfo.Inf_ME_GlobalMotion);

    tParam->Reg_ME_Mag_Pnl_Gain_XMV = NR_CLIP2( 256, 127 + 10 * g_McnrTimingInfo.Inf_ME_GlobalMotion);
    tParam->Reg_ME_Mag_Pnl_Core_XMV = NR_CLIP1023(63 - 14 * NR_CLIP(NR_CLIP3(0, 8, g_McnrTimingInfo.Inf_ME_GlobalMotion) - NR_CLIP(g_McnrTimingInfo.Inf_ND_rawNoiseLevel - 7)));
    tParam->Reg_ME_Std_Pnl_Gain_0MV = 16;
    tParam->Reg_ME_Std_Pnl_Core_0MV = NR_CLIP3(10, 16, 16 - gm_adj1[CLIP3(0, 6, g_McnrTimingInfo.Inf_ME_GlobalMotion)] - 2 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 7)); //htxiang
    tParam->Reg_ME_Std_Pnl_Gain_XMV = NR_CLIP3(10, 16, 16 - 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 8) / 2);
    tParam->Reg_ME_Std_Pnl_Core_XMV = 16;

    tParam->Reg_ME_Std_Core_0MV     = 28;
    tParam->Reg_ME_Std_Core_XMV     = NR_CLIP3(0, 16, 5 * (g_McnrTimingInfo.Inf_ND_NoiseLevel - 7) / 2);
    tParam->Reg_ME_Std_Pnl_Gain     = 31;
    tParam->Reg_ME_Std_Pnl_Core     = NR_CLIP3(0, 16, 2 * (g_McnrTimingInfo.Inf_ND_NoiseLevel - 7));

    tParam->Reg_ME_Adj_0MV_Min      = 4;
    tParam->Reg_ME_Adj_0MV_Max      = 16;
    tParam->Reg_ME_Adj_XMV_Min      = 4;
    tParam->Reg_ME_Adj_XMV_Max      = 16;//htxiang

    if (g_McnrTimingInfo.Inf_ND_TextureDenseLevel <= 0)
    {
        if (pInf->YWidth <= 960)
        {
            tParam->Reg_ME_Adj_MV_Max = NR_CLIP3(16, 31, pInf->Cfg_ME_Adj_MV_Max - 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 8) / 2
                                                 - ref_mv_level * 3 * NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 7) / 2 - 3 * NR_CLIP(3 - g_McnrTimingInfo.Inf_ME_GlobalMotion)
                                                 * NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_NoiseLevel - 3) * NR_CLIP3(0, 2, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 17));
            tParam->Reg_ME_Adj_MV_Min = NR_CLIP3(0, 16, pInf->Cfg_ME_Adj_MV_Min + 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 8) / 2
                                                 + ref_mv_level * NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 6) + 2 * NR_CLIP(3 - g_McnrTimingInfo.Inf_ME_GlobalMotion)
                                                 * NR_CLIP3(0, 3, g_McnrTimingInfo.Inf_ND_NoiseLevel - 4) * NR_CLIP3(0, 2, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 17));
        }
        else
        {
            tParam->Reg_ME_Adj_MV_Max = NR_CLIP3(16, 31, pInf->Cfg_ME_Adj_MV_Max - 3 * NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 8) / 2
                                                 - 3 * NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 7) - 3 * NR_CLIP(3 - g_McnrTimingInfo.Inf_ME_GlobalMotion)
                                                 * NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ND_NoiseLevel - 3) * NR_CLIP3(0, 2, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 17));
            tParam->Reg_ME_Adj_MV_Min = NR_CLIP3(0, 16, pInf->Cfg_ME_Adj_MV_Min + NR_CLIP(g_McnrTimingInfo.Inf_ND_NoiseLevel - 8)
                                                 + NR_CLIP(g_McnrTimingInfo.Inf_ME_GlobalMotion - 7) + 2 * NR_CLIP(3 - g_McnrTimingInfo.Inf_ME_GlobalMotion)
                                                 * NR_CLIP3(0, 3, g_McnrTimingInfo.Inf_ND_NoiseLevel - 4) * NR_CLIP3(0, 2, g_McnrTimingInfo.Inf_SCD_DarknessLevel - 17));
        }
    }
    else
    {
        tParam->Reg_ME_Adj_MV_Max = NR_CLIP3(16, 31, pInf->Cfg_ME_Adj_MV_Max);
        tParam->Reg_ME_Adj_MV_Min = NR_CLIP2(  16, pInf->Cfg_ME_Adj_MV_Min);
    }

    if (pInf->YWidth <= 960)
    {
        tParam->Reg_ME_GM_Adj = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ME_GlobalMotion - 2);
    }
    else
    {
        tParam->Reg_ME_GM_Adj = NR_CLIP3(0, 4, g_McnrTimingInfo.Inf_ME_GlobalMotion - 3);
    }

    /*** Motion Vector Estimation ***/
    /*** Motion Calculation ***/
    tParam->Reg_MC_NoiseLevel           = g_McnrTimingInfo.Inf_ND_NoiseLevel;
    tParam->Reg_MC_Scenechange          = g_McnrTimingInfo.Inf_SCD_SCLevel;
    tParam->Reg_MC_GlobalMotion         = g_McnrTimingInfo.Inf_ME_GlobalMotion;
    tParam->Reg_MC_SaltusLevel          = NR_CLIP3(0, 15, g_McnrTimingInfo.Inf_ME_SaltusLevel - 1);

    tParam->Reg_MC_YMotionGain          = NR_CLIP3(0, 31, pInf->Cfg_MC_YMotionGain + GM_Gain[NR_CLIP3(0, 15,
                                          g_McnrTimingInfo.Inf_ME_GlobalMotion)] + NL_Gain[NR_CLIP3(0, 23, g_McnrTimingInfo.Inf_ND_NoiseLevel - 6)]);
    tParam->Reg_MC_YMotionCore          = NR_CLIP3(0, 31, pInf->Cfg_MC_YMotionCore);
    tParam->Reg_MC_CMotionGain          = NR_CLIP3(0, 31, pInf->Cfg_MC_CMotionGain + GM_Gain[NR_CLIP3(0, 15,
                                          g_McnrTimingInfo.Inf_ME_GlobalMotion)] + NL_Gain[NR_CLIP3(0, 23, g_McnrTimingInfo.Inf_ND_NoiseLevel - 6)]);
    tParam->Reg_MC_CMotionCore          = NR_CLIP3(0, 31, pInf->Cfg_MC_CMotionCore);

    if (pInf->CurFNum < 32)
    {
        alphaCnt = pInf->CurFNum;
        YBlendingMin = miniAlpha[alphaCnt];
        CBlendingMin = miniAlpha[alphaCnt];
    }
    else
        /*** Motion Calculation ***/
        /*** Temporal Filtering ***/
    {
        YBlendingMin = 0;
        CBlendingMin = 0;
    }
    NoiseLevel = NR_CLIP3(0, 15, g_McnrTimingInfo.Inf_ND_NoiseLevel * (32 - NR_CLIP(g_McnrTimingInfo.Inf_ME_SaltusLevel - 3)) / 32);
    if (pInf->YWidth == 1920)
    {
        NoiseLevel = Noise_Noise_LUT_FHD[NoiseLevel];
    }
    else if (pInf->YWidth > 960)
    {
        NoiseLevel = Noise_Noise_LUT_HD[NoiseLevel];
    }
    else
    {
        NoiseLevel = Noise_Noise_LUT_SD[NoiseLevel];
    }

    if (pInf->Cfg_InputPort == 2)
    {
        TextureDenseLevel = 0;
    }
    else
    {
        TextureDenseLevel = g_McnrTimingInfo.Inf_ND_TextureDenseLevel;
    }

    for (i = 0; i < 32; i++)
    {
        tParam->Reg_TF_YBlendingAlphaLUT[i] = NR_CLIP3(YBlendingMin, 31, (Alpha_LUT[NoiseLevel][i] * (16 - TextureDenseLevel) + Strong_Alpha_LUT[i] * TextureDenseLevel + 8) / 16);
        tParam->Reg_TF_CBlendingAlphaLUT[i] = NR_CLIP3(CBlendingMin, 31, (Alpha_LUT[NoiseLevel][i] * (16 - TextureDenseLevel) + Strong_Alpha_LUT[i] * TextureDenseLevel + 8) / 16);
        if (sg_u32MCNRStr < 50)
        {
            tParam->Reg_TF_YBlendingAlphaLUT[i] = NR_CLIP3(0, 31, tParam->Reg_TF_YBlendingAlphaLUT[i] + 31 * (50 - sg_u32MCNRStr) / 50);
            tParam->Reg_TF_CBlendingAlphaLUT[i] = NR_CLIP3(0, 31, tParam->Reg_TF_CBlendingAlphaLUT[i] + 31 * (50 - sg_u32MCNRStr) / 50);
        }
    }
    /*** Temporal Filtering ***/
    return HI_SUCCESS;
}

/* 获取统计信息 */
static HI_S32 pq_mng_MCNR_GetSttParam(S_STT_REGS_TYPE *pVpssSWBReg, MCNR_INPUT_REG *pinputReg)
{
    pinputReg->Reg_ND_NoisePointCntMax = pVpssSWBReg->TNR_NOISEPOINTCNT_MAX.bits.noisepointcntmax;
    pinputReg->Reg_ND_NoisePointCntMed = pVpssSWBReg->TNR_NOISEPOINTCNT_MED.bits.noisepointcntmed;
    pinputReg->Reg_ND_NoisePointCntMin = pVpssSWBReg->TNR_NOISEPOINTCNT_MIN.bits.noisepointcntmin;
    pinputReg->Reg_ND_NoisePointNum   = pVpssSWBReg->TNR_NOISEPOINTNUM.bits.noisepointnum;
    pinputReg->Reg_ND_SumNoiseInfoMax = pVpssSWBReg->TNR_SUMNOISEINFO_MAX.bits.sumnoiseinfomax;
    pinputReg->Reg_ND_SumNoiseInfoMed = pVpssSWBReg->TNR_SUMNOISEINFO_MED.bits.sumnoiseinfomed;
    pinputReg->Reg_ND_SumNoiseInfoMin = pVpssSWBReg->TNR_SUMNOISEINFO_MIN.bits.sumnoiseinfomin;

    /* depend on vpss w*h set mcnr open  */
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_NoisePointCntMax, 3924481);/* w*h,1920x2044 */
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_NoisePointCntMed, 3924481);/* w*h,1920x2044 */
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_NoisePointCntMin, 3924481);/* w*h,1920x2044 */
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_NoisePointNum,    3924481);/* w*h,1920x2044 */
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_SumNoiseInfoMax, 0x80000000);
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_SumNoiseInfoMed, 0x80000000);
    PQ_CHECK_OVER_RANGE(pinputReg->Reg_ND_SumNoiseInfoMin, 0x80000000);

    return HI_SUCCESS;
}

static HI_S32 pq_mng_MCNR_UpdateTimingInfo(MCNR_INPUT_REG *pRegIn, MCNR_INPUT_INFO *pInfIn, HI_VOID *pRGMV, HI_U32 u32stride)
{
    /*** Motion Vector Estimation ***/
    if (pInfIn->Cfg_ME_MotionEstimationEn)
    {
        pq_mng_MCNR_EstimationGlobalMotionMCME(pInfIn, pRGMV, u32stride);
    }
    else
    {
        g_McnrTimingInfo.Inf_ME_SaltusLevel     = 0;
        g_McnrTimingInfo.Inf_ME_NonrgmeLevel = 31;
        g_McnrTimingInfo.Inf_ME_GlobalMotion    = 0;
    }

    g_McnrTimingInfo.Inf_ME_NonrgmeLevel = NR_CLIP3(0, 24,  g_McnrTimingInfo.Inf_ME_NonrgmeLevel - NR_CLIP3(0, 4, 20 - g_McnrTimingInfo.Inf_SCD_DarknessLevel));
    /*** Noise Level Estimation ***/
    if (pInfIn->Cfg_ND_NoiseDetectEn)
    {
        pq_mng_MCND_getNoiseLevel(pRegIn, pInfIn);
    }
    else
    {
        g_McnrTimingInfo.Inf_ND_NoiseLevel = 2;
    }

    return HI_SUCCESS;
}

static HI_S32 pq_mng_MCNR_UpdateSoftWareCfg(HI_U32 u32HandleNo,
        HI_VOID *pRGMV,
        HI_U32 u32Stride,
        S_STT_REGS_TYPE *pVpssSWBReg,
        HI_U32 u32Width,
        HI_U32 u32Height,
        HI_BOOL bInterlace,
        HI_U32 u32SceneChange)
{

    stInputInf.YWidth      = u32Width;
    stInputInf.YHeight     = u32Height;
    stInputInf.SceneChange = u32SceneChange;
    stInputInf.bInterlace = bInterlace;
    stInputInf.Cfg_InputPort = 0;

    pq_mng_MCNR_InitCfg(&stInputInf);

    if (u32SceneChange >= 224)
    {
        g_McnrTimingInfo.Inf_FrameNum_after_Scenechange = 0;
    }
    else
    {
        g_McnrTimingInfo.Inf_FrameNum_after_Scenechange++;
    }

    if (g_McnrTimingInfo.Inf_FrameNum_after_Scenechange >= 32)
    {
        g_McnrTimingInfo.Inf_FrameNum_after_Scenechange = 32;
    }

    stInputInf.CurFNum = g_McnrTimingInfo.Inf_FrameNum_after_Scenechange;

    g_McnrTimingInfo.Inf_SCD_DarknessLevel = 0;
    g_McnrTimingInfo.Inf_SCD_SCLevel = 0;

    stParam.Reg_MD_CMDCore = -3;
    stParam.Reg_MD_CMDGain = 16;
    stParam.Reg_MD_YMDCore = -3;
    stParam.Reg_MD_YMDGain = 16;

    stParam.Reg_ND_NoiseDetectEn         = 1;
    stParam.Reg_MD_MDPreLPFEn            = 1;
    stParam.Reg_ME_MotionEstimationEn    = 1;
    stParam.Reg_MC_YMCAdjEn              = 1;
    stParam.Reg_MC_CMCAdjEn              = 1;
    stParam.Reg_MC_SaltusDetectEn        = 1;

    stInputInf.Cfg_TF_AutoMotionAlphaEn   = 1;
    stInputInf.Cfg_ND_NoiseDetectEn       = 1;
    stInputInf.Cfg_ME_MotionEstimationEn  = 1;

    pq_mng_MCNR_GetSttParam(pVpssSWBReg, &stInputReg);
    pq_mng_MCNR_UpdateTimingInfo(&stInputReg, &stInputInf, pRGMV, u32Stride);
    pq_mng_MCNR_UpdateTimingParam(&stInputInf, &stParam);
    pq_mng_MCNR_UpdateSNRRegisters(u32SceneChange, &stOutputSnrReg);

    PQ_HAL_UpdateTnrSoftReg(u32HandleNo, &stParam);
    PQ_HAL_UpdateSnrSoftReg(u32HandleNo, &stOutputSnrReg);

    return HI_SUCCESS;
}

HI_U32 idex;

HI_S32 PQ_MNG_UpdateMCNRCfg(HI_PQ_WBC_INFO_S *pstVpssWbcInfo)
{
    HI_S32 s32Ret         = HI_FAILURE;
    HI_BOOL bTNROnOff     = HI_FALSE;
    HI_U32 u32MCNRStr     = 50;

    HI_U32 u32HandleNo    = pstVpssWbcInfo->u32HandleNo;
    HI_U32 u32Stride      = pstVpssWbcInfo->stride;
    HI_U32 u32Width       = pstVpssWbcInfo->u32Width;
    HI_U32 u32Height      = pstVpssWbcInfo->u32Height;
    HI_U32 u32SceneChange = 0;
    HI_BOOL bInterlace    = pstVpssWbcInfo->u32DeiEnFlag;
    HI_VOID *pRGMV        = pstVpssWbcInfo->pRGMV;
    S_STT_REGS_TYPE *pVpssSWBReg =  pstVpssWbcInfo->pstVPSSWbcReg;

    if (HI_FALSE == pstVpssWbcInfo->bMcnrEnableFlag)
    {
        return HI_SUCCESS;
    }

    if ((u32Width > MCNR_Y_MAX_WIDTH) || (u32Width < MCNR_Y_MIN_WIDTH))
    {
        return HI_SUCCESS;
    }

    PQ_CHECK_NULL_PTR(pRGMV);
    PQ_CHECK_NULL_PTR(pVpssSWBReg);
    PQ_CHECK_OVER_RANGE(u32Stride, 200);
    PQ_CHECK_OVER_RANGE(u32Width, (MCNR_Y_MAX_WIDTH + 1));

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, GetEnable))
    {
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->GetEnable(&bTNROnOff);
    }

    if (HI_TRUE != bTNROnOff)
    {
        return HI_FAILURE;
    }

    if (HI_TRUE != sg_bMCNREn)
    {
        return HI_FAILURE;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, GetStrength))
    {
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->GetStrength(&u32MCNRStr);
    }

    sg_u32MCNRStr = u32MCNRStr;

    s32Ret = pq_mng_MCNR_UpdateSoftWareCfg(u32HandleNo, pRGMV, u32Stride, \
                                           pVpssSWBReg, u32Width, u32Height, \
                                           bInterlace, u32SceneChange);

    return s32Ret;
}

HI_S32 PQ_MNG_SetMCNREn(HI_BOOL bOnOff)
{
    sg_bMCNREn = bOnOff;
    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetMCNREn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR(pbOnOff);
    *pbOnOff = sg_bMCNREn;
    return HI_SUCCESS;
}

