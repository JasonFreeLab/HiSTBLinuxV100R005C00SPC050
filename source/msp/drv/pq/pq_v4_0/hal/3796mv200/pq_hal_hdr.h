/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_hdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/06/15
  Description  :

******************************************************************************/

#ifndef _PQ_HAL_HDR_H_
#define _PQ_HAL_HDR_H_

#include "hi_type.h"
#include "pq_mng_hdr_ext.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32 PQ_HAL_GetHDRCfg(HI_PQ_WIN_HDR_INFO *pstWinHdrInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);

HI_S32 PQ_HAL_InitHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault);

HI_S32 PQ_HAL_SetHDRTmLut(HI_PQ_HDR_TM_LUT_S *pstTMSetLut);

HI_S32 PQ_HAL_GetHDRTmLut(HI_PQ_HDR_TM_LUT_S *pstTMSetLut);

HI_S32 PQ_HAL_SetHDRTmXpos(HI_U8 *pstTMSetLut);

HI_S32 PQ_HAL_GetHDRTmXpos(HI_U8 *pstTMSetLut);

HI_S32 PQ_HAL_GetHDRSrcLum(HI_PQ_HDR_SRC_LUM_S *pstTMSrcLum);

HI_S32 PQ_HAL_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstSetParaMode);

HI_S32 PQ_HAL_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstGetParaMode);

HI_S32 PQ_HAL_SetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstSetSoftpara);

HI_S32 PQ_HAL_GetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstGetsoftpara);

HI_S32 PQ_HAL_SetHDRToneMap(HI_U8 *pstToneMap);

HI_S32 PQ_HAL_GetHDRToneMap(HI_U8 *pstToneMap);

HI_S32 PQ_HAL_SetHDRTYMap(HI_U8 *pstTYSetLut);

HI_S32 PQ_HAL_GetHDRTYMap(HI_U8 *pstTYSetLut);

HI_S32 PQ_HAL_SetHDRSatMap(HI_U8 *pstSatMap);

HI_S32 PQ_HAL_GetHDRSatMap(HI_U8 *pstSatMap);

HI_S32 PQ_HAL_SetHDRDefaultCfg(HI_BOOL bDefault);

HI_S32 PQ_HAL_SetHdrCscSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
