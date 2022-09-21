/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_hdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/03/19
  Description  :

******************************************************************************/


#ifndef __PQ_MNG_HDR_H__
#define __PQ_MNG_HDR_H__

#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern HI_U32 sg_u32HdrParaMode;
HI_S32 PQ_MNG_RegisterHDR(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterHDR(HI_VOID);

HI_S32 PQ_MNG_SetHDRTmLut(HI_PQ_HDR_TM_LUT_S* pstTMLut);

HI_S32 PQ_MNG_GetHDRTmLut(HI_PQ_HDR_TM_LUT_S* pstTMLut);

HI_S32 PQ_MNG_SetHDRTmXpos(HI_U8* pstTMXpos);

HI_S32 PQ_MNG_GetHDRTmXpos(HI_U8* pstTMXpos);

HI_S32 PQ_MNG_SetHDRTYMap(HI_U8* pstTYMap);

HI_S32 PQ_MNG_GetHDRTYMap(HI_U8* pstTYMap);

HI_S32 PQ_MNG_SetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstSetSoftPara);

HI_S32 PQ_MNG_GetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstSetSoftPara);

HI_S32 PQ_MNG_GetHDRSrcLum(HI_PQ_HDR_SRC_LUM_S *pstGetSrclum);

HI_S32 PQ_MNG_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pParaMode);

HI_S32 PQ_MNG_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pParaMode);

HI_S32 PQ_MNG_SetHDRToneMap(HI_U8* pstTMLut);

HI_S32 PQ_MNG_GetHDRToneMap(HI_U8* pstTMLut);

HI_S32 PQ_MNG_SetHDRSatMap(HI_U8* pstTMLut);

HI_S32 PQ_MNG_GetHDRSatMap(HI_U8* pstTMLut);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


