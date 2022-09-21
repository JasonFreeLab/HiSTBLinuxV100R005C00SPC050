/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_customer.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/30
  Description  :
  History       :
  1.Date        : 2017/06/26
    Author      :
    Modification: Created file

*******************************************************************************/

#include "hi_type.h"

#ifndef  __ENGINE_CUSTOMER_H__
#define  __ENGINE_CUSTOMER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
    PTSMUTE_MUTE_NONE,
    PTSMUTE_MUTE_START,
    PTSMUTE_MUTE_STOP,
}PTSMUTEQUEUE_POLICY;

HI_S32 PTSMUTEQUEUE_Create(HI_VOID** phHandle);

HI_VOID PTSMUTEQUEUE_Destroy(HI_VOID* pHandle);

HI_S32 PTSMUTEQUEUE_Add(HI_VOID* pHandle, HI_U32 u32StartPts, HI_U32 u32StopPts);

PTSMUTEQUEUE_POLICY PTSMUTEQUEUE_Find(HI_VOID* handle, HI_U32 u32Pts);

HI_S32 PTSMUTEQUEUE_Reset(HI_VOID* pHandle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

