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
  Created       : 2013/09/18
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_CSC_H__
#define __PQ_HAL_CSC_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/* 色彩空间标准 */
typedef enum hiCOLOR_SPACE_TYPE_E
{
    OPTM_CS_eUnknown           = 0,
    OPTM_CS_eItu_R_BT_709      = 1,
    OPTM_CS_eFCC               = 4,
    OPTM_CS_eItu_R_BT_470_2_BG = 5,
    OPTM_CS_eSmpte_170M        = 6,
    OPTM_CS_eSmpte_240M        = 7,
    OPTM_CS_eXvYCC_709         = OPTM_CS_eItu_R_BT_709,
    OPTM_CS_eXvYCC_601         = 8,
    OPTM_CS_eRGB               = 9,
    /*
    OPTM_CS_eItu_BT_2020       = 10,
    OPTM_CS_eRGB_601           = 11,
    OPTM_CS_eRGB_709           = 12,
    OPTM_CS_eRGB_2020          = 13,
    */

    OPTM_CS_BUTT
} COLOR_SPACE_TYPE_E;

/* 色温通道 */
typedef enum hiCOLORTEMP_CHANNEL_E
{
    COLORTEMP_R = 0  ,
    COLORTEMP_G = 1  ,
    COLORTEMP_B = 2  ,

    COLORTEMP_ALL = 3
} COLORTEMP_CHANNEL_E;

/* CSC 参数结构 */
typedef struct hiCSC_PARA_S
{
    HI_U32   u16Brightness;
    HI_U32   u16Contrast;
    HI_U32   u16Hue;
    HI_U32   u16Saturation;
    HI_U32   as16ColorTempGain[COLORTEMP_ALL];
    HI_U32   as16ColorTempOffset[COLORTEMP_ALL];
    HI_U16   u16InputColorSpace;
    HI_U16   u16OutputColorSpace;
    HI_BOOL  bFullRange;
} CSC_PARA_S;

typedef enum  hiWBC_POINT_SEL_E
{
    WBC_POINT_AFTER_CSC  = 0,   /* 00：回写点在VP CSC后，数据格式为YUV444 */
    WBC_POINT_AFTER_ZME     ,   /* 01：回写点在V0 ZME后，数据格式为YUV422 */
    WBC_POINT_BEFORE_ZME    ,   /* 10：回写点在V0 ZME前，数据格式为YUV420或YUV422 */

    WBC_POINT_BUTT
} WBC_POINT_SEL_E;

HI_U32 PQ_HAL_GetWbcPointSel(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
