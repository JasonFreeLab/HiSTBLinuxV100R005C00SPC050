
#ifndef __VENC_OSAL_H__
#define __VENC_OSAL_H__
#include <linux/wait.h>
#include <linux/sched.h>

#if defined(VENC_EXTRA_TYPE_DEFINE)
#include "hi_type.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
//Venc_Osal_Func_Ptr venc_Osal_Func_Ptr_S;

#if defined(VENC_EXTRA_TYPE_DEFINE)
    #define UINT64 HI_U64
    #define SINT64 HI_S64
    #define UINT32 HI_U32
    #define SINT32 HI_S32
    #define UINT16 HI_U16
    #define SINT16 HI_S16
    #define UINT8  HI_U8
    #define SINT8  HI_S8
    #define VOID   HI_VOID
    #define UADDR  HI_U32
    #define ULONG  HI_SIZE_T
    #define HANDLE HI_HANDLE
    #define VIRT_ADDR   HI_VOID*
    typedef const void CONSTVOID;
#else
    typedef  unsigned long long UINT64;
    typedef  long long          SINT64;
    typedef  unsigned int       UINT32;
    typedef  int                SINT32;
    typedef  unsigned short     UINT16;
    typedef  short              SINT16;
    typedef  char               SINT8;
    typedef  unsigned char      UINT8;
    typedef  unsigned int       UADDR;
    typedef  const void         CONSTVOID;
    typedef  unsigned long      ULONG;
    typedef  unsigned int       HANDLE;
#ifndef  VOID
    typedef  void               VOID;
#endif

#endif

typedef struct hiKERN_EVENT_S
{
    wait_queue_head_t   queue_head;
    HI_S32              flag;
} KERN_EVENT_S;

typedef struct
{
    UINT8* pu8StartVirAddr;    /*VirAddr*/
    UINT32 u32StartPhyAddr;    /*PhyAddr or SmmuAddr*/
    UINT32 u32Size;
} VENC_BUFFER_S;

typedef unsigned long VEDU_LOCK_FLAG;
typedef KERN_EVENT_S  VEDU_OSAL_EVENT;

VOID       VENC_DRV_OsalIrqFree(HI_U32 Irq);
SINT32        VENC_DRV_OsalIrqInit(HI_U32 Irq, HI_VOID (*ptrCallBack)(HI_VOID));
SINT32        VENC_DRV_OsalLockCreate (HI_VOID** phLock);
VOID       VENC_DRV_OsalLockDestroy(HI_VOID* hLock);
VOID       VENC_DRV_OsalLock(HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag);
VOID       VENC_DRV_OsalUnlock(HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag);
SINT32        VENC_DRV_OsalCreateTask(HI_VOID **phTask, HI_U8 TaskName[], HI_VOID* pTaskFunction);
SINT32        VENC_DRV_OsalDeleteTask(HI_VOID *hTask);

SINT32 VENC_DRV_OsalInitEvent( VEDU_OSAL_EVENT *pEvent, HI_S32 InitVal );
SINT32 VENC_DRV_OsalGiveEvent( VEDU_OSAL_EVENT *pEvent );
SINT32 VENC_DRV_OsalWaitEvent( VEDU_OSAL_EVENT *pEvent, HI_U32 msWaitTime );

struct file *VENC_DRV_OsalFopen(const char *filename, int flags, int mode);
VOID VENC_DRV_OsalFclose(struct file *filp);
SINT32 VENC_DRV_OsalFwrite(char *buf, int len, struct file *filp);

SINT32 HI_DRV_VENC_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, VENC_BUFFER_S *psMBuf);
VOID HI_DRV_VENC_UnmapAndRelease(VENC_BUFFER_S *psMBuf);
SINT32 HI_DRV_VENC_Map(VENC_BUFFER_S *psMBuf);
VOID HI_DRV_VENC_Unmap(VENC_BUFFER_S *psMBuf);

VOID InitVencInterface(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  // __VENC_OSAL_H__
