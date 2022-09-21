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

#ifndef __PQ_HAL_VPSSCSC_H__
#define __PQ_HAL_VPSSCSC_H__

#include "hi_type.h"
#include "pq_hal_comm.h"
#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 色彩空间标准 */
typedef enum hiVPSSCOLOR_SPACE_TYPE_E
{
    VPSS_OPTM_CS_eItu_R_BT_709           = 0,
    VPSS_OPTM_CS_eUnknown,

    VPSS_OPTM_CS_BUTT
} VPSSCOLOR_SPACE_TYPE_E;

/* 色温通道 */
typedef enum hiVPSSCOLORTEMP_CHANNEL_E
{
    VPSSCOLORTEMP_R = 0  ,
    VPSSCOLORTEMP_G = 1  ,
    VPSSCOLORTEMP_B = 2  ,

    VPSSCOLORTEMP_ALL = 3
} VPSSCOLORTEMP_CHANNEL_E;

/* CSC 参数结构 */
typedef struct hiVPSSCSC_PARA_S
{
    HI_U32   u16Brightness;
    HI_U32   u16Contrast;
    HI_U32   u16Hue;
    HI_U32   u16Saturation;
    HI_U32   as16ColorTempGain[VPSSCOLORTEMP_ALL];
    HI_U32   as16ColorTempOffset[VPSSCOLORTEMP_ALL];
} VPSSCSC_PARA_S;

typedef enum hiVPSSCSC_DEMO_MODE_E
{
    VPSSCSC_DEMO_ENABLE_L = 0,
    VPSSCSC_DEMO_ENABLE_R    ,

    ACC_DEMO_ENABLE_BUTT
} VPSSCSC_DEMO_MODE_E;

HI_S32 PQ_HAL_SetVpssCscEnable(HI_U32 u32HandleNo, HI_BOOL bEnable);
HI_S32 PQ_HAL_SetVpssCscDemoEnable(HI_U32 u32HandleNo, HI_BOOL bVpssDemoEn);
HI_S32 PQ_HAL_SetVpssCscDemoMode(HI_U32 u32HandleNo, VPSSCSC_DEMO_MODE_E enVpssCscDemoMode);

HI_S32 PQ_HAL_UpdateVpssCsc(HI_U32 u32HandleNo, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

