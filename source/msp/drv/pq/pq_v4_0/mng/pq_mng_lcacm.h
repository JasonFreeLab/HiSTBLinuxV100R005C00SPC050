/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_lcacm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/07/18
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_LCACM_H__
#define __PQ_MNG_LCACM_H__


#include "drv_pq_table.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*ACM 增强类型*/
typedef enum hiLCACM_ENHANCE_E
{
    LCACM_ENHANCE_FLESHTONE       = 0,    /* 肤色增强 */
    LCACM_ENHANCE_SIX_BASE        = 1,    /* 六基色增强,自定义颜色的增强 */
    LCACM_ENHANCE_SPEC_COLOR_MODE = 2,    /* 固定模式的颜色增强模式 */
    LCACM_ENHANCE_BUTT
} LCACM_ENHANCE_E;

/* color enhance mode */
typedef enum hiLCACM_COLOR_SPEC_MODE_E
{
    LCACM_COLOR_MODE_RECOMMEND = 0  , /* color enhance recommend mode  */
    LCACM_COLOR_MODE_SKY       = 1  , /* color enhance sky mode        */
    LCACM_COLOR_MODE_GRASS     = 2  , /* color enhance grass mode      */
    LCACM_COLOR_MODE_SCENERY   = 3  , /* color enhance scenery mode    */
    LCACM_COLOR_MODE_PORTRAIT  = 4  , /* color enhance portrait mode   */

    LCACM_COLOR_MODE_BUTT
} LCACM_COLOR_SPEC_MODE_E;

/* 六基色偏移值 */
typedef struct hiLCACM_SIX_BASE_COLOR_OFFSET_S
{
    HI_U32  u32RedOffset;
    HI_U32  u32GreenOffset;
    HI_U32  u32BlueOffset;
    HI_U32  u32CyanOffset;
    HI_U32  u32MagentaOffset;
    HI_U32  u32YellowOffset;
} LCACM_SIX_BASE_COLOR_OFFSET_S;

/* 肤色增益类型 */
typedef enum hiLAACM_FLESHTONE_LEVEL_E
{
    LCACM_FLE_GAIN_OFF = 0 ,
    LCACM_FLE_GAIN_LOW     ,
    LCACM_FLE_GAIN_MID     ,
    LCACM_FLE_GAIN_HIGH    ,

    LCACM_FLE_GAIN_BUTT
} LAACM_FLESHTONE_LEVEL_E;

typedef struct hiALG_LCACM_S
{
    HI_BOOL         bInit;
    HI_BOOL         bEnable;
    HI_U32          u32Strength;
    HI_BOOL         bDemoEnable;
    PQ_DEMO_MODE_E  eDemoMode;
    LAACM_FLESHTONE_LEVEL_E         enLCACMFleshLevel;
    LCACM_ENHANCE_E                 enLCAcmEnhance;
    LCACM_COLOR_SPEC_MODE_E         enLCACMColorSpecModeType;
    LCACM_SIX_BASE_COLOR_OFFSET_S   stLCACMSixbaseColorOffset;
} ALG_LCACM_S;

HI_S32 PQ_MNG_RegisterLowCostACM(PQ_REG_TYPE_E enType);
HI_S32 PQ_MNG_UnRegisterLowCostACM(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


