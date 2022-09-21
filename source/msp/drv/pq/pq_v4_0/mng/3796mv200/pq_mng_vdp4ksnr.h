/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_vdp4ksnr.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/04/14
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_VDP4KSNR_H__
#define __PQ_MNG_VDP4KSNR_H__

#include "drv_pq_comm.h"
#include "pq_hal_vdp4ksnr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct hiALG_VDP4KSNR_S
{
    HI_BOOL     bInit;
    HI_BOOL     bEnable;
    HI_U32      u32Strength;
    HI_BOOL     bDemoEnable;
    PQ_DEMO_MODE_E eDemoMode;
} ALG_VDP4KSNR_S;


HI_S32 PQ_MNG_RegisterVDP4KSNR(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterVDP4KSNR(HI_VOID);

HI_S32 PQ_MNG_SetVdp4KSnrMeanRatio(HI_PQ_SNR_MEAN_RATIO_S* pstMeanRatio);

HI_S32 PQ_MNG_GetVdp4KSnrMeanRatio(HI_PQ_SNR_MEAN_RATIO_S* pstMeanRatio);

HI_S32 PQ_MNG_SetVdp4KSnrEdgeStr(HI_PQ_SNR_EDGE_STR_S* pstEdgeStr);

HI_S32 PQ_MNG_GetVdp4KSnrEdgeStr(HI_PQ_SNR_EDGE_STR_S* pstEdgeStr);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_VDP4KSNR_H__ */



