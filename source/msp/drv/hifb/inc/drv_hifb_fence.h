/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : drv_hifb_fence.h
Version         : Initial Draft
Author          :
Created         : 2016/02/02
Description     :
Function List   :


History         :
Date                Author                Modification
2016/02/02            sdk              Created file
******************************************************************************/
#ifndef __DRV_HIFB_FENCE_H__
#define __DRV_HIFB_FENCE_H__


/*********************************add include here******************************/
#include <sw_sync.h>

#include "drv_hifb_osr.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/
#define HIFB_SYNC_NAME                 "hifb_fence"
#define HIFB_DISP_BUFFER_NUM_MAX       (CFG_HIFB_FENCE_TIMELINE_NUM)

/*************************** Structure Definition ****************************/
typedef struct
{
    HI_BOOL bFrameHit;
    HI_U8   RegUpdateCnt[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32  FenceValue[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32  TimeLine[HIFB_DISP_BUFFER_NUM_MAX];
    HI_S32  ReleaseFenceFd[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32  FrameEndFlag;
    spinlock_t lock;
    wait_queue_head_t FrameEndEvent;
    struct sw_sync_timeline *pstTimeline[HIFB_DISP_BUFFER_NUM_MAX];
}HIFB_SYNC_INFO_S;

/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/

HI_S32  DRV_HIFB_FenceInit(HIFB_PAR_S *par);
HI_VOID DRV_HIFB_FenceDInit(HIFB_PAR_S *par);
HI_VOID DRV_HIFB_FENCE_FrameEndCallBack(HI_VOID *pParaml, HI_VOID *pParamr);
HI_BOOL DRV_HIFB_FENCE_IsRefresh(HI_VOID);
HI_S32  DRV_HIFB_FENCE_Create(HI_U32 BufferId);
HI_VOID DRV_HIFB_IncRefreshTime(HI_BOOL bLayerEnable, HI_U32 BufferId);
HI_VOID DRV_HIFB_ReleaseFence(HI_U32 BufferId, HI_U8 *pFenceRefreshCount);
HI_BOOL DRV_HIFB_GetBufState(HI_U32 BufferId);
HI_VOID DRV_HIFB_WaiteRefreshEnd(HI_BOOL ShouldWaite);
HI_S32  DRV_HIFB_FENCE_Waite(struct sync_fence *fence, long timeout);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
