#ifndef __VDP_ASYNC_H__
#define __VDP_ASYNC_H__

#include "hi_type.h"
#include "drv_async_define.h"
#define MAX_QUEUE_NUM 32


typedef HI_S32 (*MSG_PROCESS_CALLBACK)(const ASYNC_MSG_S *);

HI_VOID      VDP_ASYNC_Init(HI_VOID);
HI_S32       VDP_ASYNC_DeInit(HI_VOID);
HI_S32       VDP_ASYNC_ResetMsgQueue(HI_S32 s32QueueIdx);
HI_S32       VDP_ASYNC_DestroyMsgQueue(HI_S32 s32QueueIdx);
ASYNC_MSG_S *VDP_ASYNC_GetMsgPointer(HI_S32 s32QueueIdx);
HI_S32       VDP_ASYNC_PushMsg(ASYNC_MSG_S *async_msg, HI_S32 s32QueueIdx);
HI_VOID      VDP_ASYNC_DelMsg(const ASYNC_MSG_S *async_msg, HI_S32 s32QueueIdx);
HI_S32       VDP_ASYNC_ProcessMsgOnce(HI_S32 s32QueueIdx);
HI_S32       VDP_ASYNC_RegCallback(ASYNC_MSG_TYPE enAsyncType, const MSG_PROCESS_CALLBACK pCallbackFun);
HI_ULONG     VDP_ASYNC_GenExpectTime(HI_U32 u32Duration);
HI_ULONG     VDP_ASYNC_GenExpectTimeByCycle(HI_S32 s32CycleNum, HI_S32 s32CycleDuration);



#endif  /*__VDP_ASYNC_H__*/
