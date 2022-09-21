#ifndef  __DRV_VENC_OSAL_H__
#define  __DRV_VENC_OSAL_H__

#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include "hi_type.h"

#include "drv_venc_osal_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct hiKERN_EVENT_S
{
    wait_queue_head_t   queue_head;
    HI_S32              flag;
} KERN_EVENT_S;


typedef KERN_EVENT_S    VEDU_OSAL_EVENT;

HI_S32 VENC_DRV_OsalInitEvent( VEDU_OSAL_EVENT* pEvent, HI_S32 InitVal );
HI_S32 VENC_DRV_OsalGiveEvent( VEDU_OSAL_EVENT* pEvent );
HI_S32 VENC_DRV_OsalWaitEvent( VEDU_OSAL_EVENT* pEvent, HI_U32 msWaitTime );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif //__DRV_VENC_OSAL_H__
