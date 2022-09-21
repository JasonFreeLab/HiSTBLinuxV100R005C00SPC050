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


#ifndef __PQ_MNG_VPSSCSC_H__
#define __PQ_MNG_VPSSCSC_H__

#include "pq_hal_vpsscsc.h"
#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/* 亮度/对比度/色调/饱和度设定 */
typedef struct hiVPSSPICTURE_SETTING_S
{
    HI_U16 u16Brightness;
    HI_U16 u16Contrast;
    HI_U16 u16Hue;
    HI_U16 u16Saturation;
} VPSSPICTURE_SETTING_S;

/* 色温设定 */
typedef struct hiVPSSCOLOR_TEMPERATURE_S
{
    HI_S16 s16RedGain;
    HI_S16 s16GreenGain;
    HI_S16 s16BlueGain;
    HI_S16 s16RedOffset;
    HI_S16 s16GreenOffset;
    HI_S16 s16BlueOffset;
} VPSSCOLOR_TEMPERATURE_S;

/* 色彩空间设定 */
typedef struct hiVPSSCOLOR_SPACE_S
{
    VPSSCOLOR_SPACE_TYPE_E u16InputColorSpace;    /* 输入色彩空间 */
    VPSSCOLOR_SPACE_TYPE_E u16OutputColorSpace;   /* 输出色彩空间 */
    HI_BOOL            bFullRange;            /* 0:limit,1:full range */
} VPSSCOLOR_SPACE_S;

typedef struct hiVPSSCSC_COLOR_TEMP
{
    HI_U32 u32Red;
    HI_U32 u32Green;
    HI_U32 u32Blue;
} VPSSCSC_COLOR_TEMP;

typedef struct hiVPSSCSC_NODE_VPTYPE_S
{
    HI_U32 u32HandleNo;
    HI_DRV_PQ_VP_TYPE_E enVpsVPCscType;
} VPSSCSC_NODE_VPTYPE_S;

HI_S32 PQ_MNG_RegisterVPSSCSC(PQ_REG_TYPE_E enType);

HI_S32 PQ_MNG_UnRegisterVPSSCSC(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
