/******************************************************************************
*
* Copyright (C) 2014-2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_csc.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/02/17
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_VPSSGAMMA_H__
#define __PQ_HAL_VPSSGAMMA_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HI_PQ_VPSSGAMA_LUT_SIZE 33

typedef enum hiHAL_PQ_VP_VPSSGAMMA_MODE_E
{
    HAL_PQ_VP_VPSSGAMMA_MODE_RECOMMEND = 0, /**<Optimization Model */ /**<CNcomment:最优模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_BLACK     = 1, /**<Blue Model */ /**<CNcomment:蓝色增强模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_COLORFUL  = 2, /**<Green Model */ /**<CNcomment:绿色增强模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_BRIGHT    = 3, /**<Cyan Model */ /**<CNcomment:蓝绿增强模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_WARM      = 4, /**<Original Model */ /**<CNcomment:原始颜色模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_COOL      = 5, /**<Original Model */ /**<CNcomment:原始颜色模式 CNend*/
    HAL_PQ_VP_VPSSGAMMA_MODE_USER      = 6,

    HAL_PQ_VP_VPSSGAMMA_MODE_BUTT
} HAL_PQ_VP_VPSSGAMMA_MODE_E;

/* CSC Tuning Or No Tuning */
typedef enum hiHAL_PQ_VPSSGAMMA_SCENE_MODE_VP_E
{
    HAL_PQ_VPSSGAMMA_SCENE_MODE_VP_PREVIEW = 0  ,
    HAL_PQ_VPSSGAMMA_SCENE_MODE_VP_REMOTE       ,

    HAL_PQ_VPSSGAMMA_SCENE_MODE_VP_BUUT
} HAL_PQ_VPSSGAMMA_MODE_VP_E;

typedef struct HiHAL_PQ_VPSSGAMMA_COEF_S
{
    /*Gamma Coef*/
    HI_U32 u32aGammaLutY[HI_PQ_VPSSGAMA_LUT_SIZE];
    HI_U32 u32aGammaLutU[HI_PQ_VPSSGAMA_LUT_SIZE];
    HI_U32 u32aGammaLutV[HI_PQ_VPSSGAMA_LUT_SIZE];
} HAL_PQ_VPSSGAMMA_COEF_S;

typedef struct  hiVPSSGAMMA_CFG_S
{
    HI_BOOL     bVpssGammaEn;
    HAL_PQ_VPSSGAMMA_MODE_VP_E  enVpssGammaVpMode;
} VPSSGAMMA_CFG_S;

HI_S32 PQ_HAL_SetVpssGmmEnable(HI_U32 u32HandleNo, HI_BOOL bEnable);
HI_S32 PQ_HAL_UpdateVpssGamma(HI_U32 u32HandleNo, HAL_PQ_VPSSGAMMA_COEF_S *pstVpssGammaCoef);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

