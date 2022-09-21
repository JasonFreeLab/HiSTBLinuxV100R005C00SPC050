#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/rwlock.h>

#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>


#include "hi_kernel_adapt.h"
#include "hi_drv_mem.h"
#include "hi_drv_struct.h"
#include "drv_venc_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

static HI_VOID (*ptrVencCallBack)(HI_VOID);

static irqreturn_t VENC_DRV_OsalVencISR(HI_S32 Irq, HI_VOID* DevID)
{
    (*ptrVencCallBack)();
    return IRQ_HANDLED;
}

static HI_HANDLE hVencIRQ;

HI_S32 VENC_DRV_OsalIrqInit( HI_U32 Irq, HI_VOID (*ptrCallBack)(HI_VOID))
{
    HI_S32 ret = HI_FAILURE;

    if (Irq == VEDU_IRQ_ID)
    {
        ptrVencCallBack = ptrCallBack;
        ret = osal_request_irq(Irq, VENC_DRV_OsalVencISR, IRQF_SHARED, "venc", &hVencIRQ);
    }

    return ret;
}

HI_VOID VENC_DRV_OsalIrqFree( HI_U32 Irq )
{
    osal_free_irq(Irq, "venc", &hVencIRQ);
}

HI_S32 VENC_DRV_OsalLockCreate( HI_VOID**phLock )
{
    spinlock_t *pLock;

    pLock = (spinlock_t *)HI_KMALLOC(HI_ID_VENC, sizeof(spinlock_t), GFP_KERNEL);
    if (pLock == NULL)
    {
        return HI_FAILURE;
    }

    spin_lock_init( pLock );

    *phLock = pLock;

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_OsalLockDestroy( HI_VOID* hLock )
{
    HI_KFREE(HI_ID_VENC, hLock);
}

HI_VOID VENC_DRV_OsalLock( HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag )
{
    spin_lock_irqsave((spinlock_t *)hLock, *pFlag);
}

HI_VOID VENC_DRV_OsalUnlock( HI_VOID* hLock, VEDU_LOCK_FLAG *pFlag )
{
    spin_unlock_irqrestore((spinlock_t *)hLock, *pFlag);
}

HI_S32 VENC_DRV_OsalCreateTask(HI_VOID **phTask, HI_U8 TaskName[], HI_VOID *pTaskFunction )
{
    *phTask = (HI_VOID *)kthread_create(pTaskFunction, NULL, TaskName);
    if (IS_ERR(*phTask))    //(NULL == (*phTask))
    {
        return HI_FAILURE;
    }

    wake_up_process((struct task_struct*) (*phTask));
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_OsalDeleteTask(HI_VOID *hTask)
{
    //kthread_stop( (struct task_struct*) hTask );
    return HI_SUCCESS;
}

#if 1
/************************************************************************/
/* 初始化事件                                                           */
/************************************************************************/
HI_S32 VENC_DRV_OsalInitEvent( VEDU_OSAL_EVENT *pEvent, HI_S32 InitVal )
{
    pEvent->flag = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return HI_SUCCESS;
}

/************************************************************************/
/* 发出事件唤醒                                                             */
/************************************************************************/
HI_S32 VENC_DRV_OsalGiveEvent( VEDU_OSAL_EVENT *pEvent )
{
    pEvent->flag = 1;
    //wake_up_interruptible ( &(pEvent->queue_head) );
    wake_up( &(pEvent->queue_head) );
    return HI_SUCCESS;
}

/************************************************************************/
/* 等待事件                                                             */
/* 事件发生返回OSAL_OK，超时返回OSAL_ERR 若condition不满足就阻塞等待    */
/* 被唤醒返回 0 ，超时返回非-1                                          */
/************************************************************************/
HI_S32 VENC_DRV_OsalWaitEvent( VEDU_OSAL_EVENT *pEvent, HI_U32 msWaitTime )
{
    HI_S32 l_ret = 0;

    if ( msWaitTime != 0xffffffff)
    {
       //l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), ((msWaitTime*10+50)/(msWaitTime)) );
       l_ret = wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime)/*msWaitTime/10*/ );

       pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

       return (l_ret != 0)? HI_SUCCESS: HI_FAILURE;
    }
    else
    {
       l_ret = wait_event_interruptible( pEvent->queue_head, (pEvent->flag != 0));
       //wait_event(pEvent->queue_head, (pEvent->flag != 0));
       pEvent->flag = 0;
       return (l_ret == 0)? HI_SUCCESS: HI_FAILURE;
    }
}
#endif
/************************************************************************/
/* 文件tell position                                                    */
/************************************************************************/

struct file *VENC_DRV_OsalFopen(const char *filename, int flags, int mode)
{
        struct file *filp = filp_open(filename, flags, mode);
        return (IS_ERR(filp)) ? NULL : filp;
}

void VENC_DRV_OsalFclose(struct file *filp)
{
        if (filp)
    { filp_close(filp, NULL); }
}

int VENC_DRV_OsalFwrite(char *buf, int len, struct file *filp)
{
        int writelen;
        mm_segment_t oldfs;

        if (filp == NULL)
        { return -ENOENT; }
        if (filp->f_op->write == NULL)
        { return -ENOSYS; }
        if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
        { return -EACCES; }
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        writelen = filp->f_op->write(filp, buf, len, &filp->f_pos);
        set_fs(oldfs);

        return writelen;
}

/*********************************** for SMMU begain************************************/

HI_S32 HI_DRV_VENC_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, VENC_BUFFER_S *psMBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif

#ifndef HI_SMMU_SUPPORT
    s32Ret = HI_DRV_MMZ_AllocAndMap(bufname, zone_name, size, align, &stMMZBuf);
    psMBuf->pu8StartVirAddr  = stMMZBuf.pu8StartVirAddr;
    psMBuf->u32StartPhyAddr  = stMMZBuf.u32StartPhyAddr;
    psMBuf->u32Size          = stMMZBuf.u32Size;
#else
    s32Ret = HI_DRV_SMMU_AllocAndMap(bufname, size, align, &stSMMUBuf);
    psMBuf->pu8StartVirAddr  = stSMMUBuf.pu8StartVirAddr;
    psMBuf->u32StartPhyAddr  = stSMMUBuf.u32StartSmmuAddr;
    psMBuf->u32Size          = stSMMUBuf.u32Size;
#endif

    return s32Ret;
}

HI_VOID HI_DRV_VENC_UnmapAndRelease(VENC_BUFFER_S *psMBuf)
{
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif
    if(HI_NULL == psMBuf)
    {
        HI_ERR_VENC("invalid param!\n");
        return;
    }
#ifndef HI_SMMU_SUPPORT
    stMMZBuf.pu8StartVirAddr = psMBuf->pu8StartVirAddr;
    stMMZBuf.u32StartPhyAddr = psMBuf->u32StartPhyAddr;
    stMMZBuf.u32Size         = psMBuf->u32Size;
    HI_DRV_MMZ_UnmapAndRelease(&stMMZBuf);
#else
    stSMMUBuf.pu8StartVirAddr  = psMBuf->pu8StartVirAddr;
    stSMMUBuf.u32StartSmmuAddr = psMBuf->u32StartPhyAddr;
    stSMMUBuf.u32Size          = psMBuf->u32Size;
    HI_DRV_SMMU_UnmapAndRelease(&stSMMUBuf);
#endif
    return;
}

HI_S32 HI_DRV_VENC_Map(VENC_BUFFER_S *psMBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif

#ifndef HI_SMMU_SUPPORT
    stMMZBuf.u32StartPhyAddr = psMBuf->u32StartPhyAddr;
    stMMZBuf.u32Size         = psMBuf->u32Size;

    s32Ret = HI_DRV_MMZ_Map(&stMMZBuf);

    psMBuf->pu8StartVirAddr  = stMMZBuf.pu8StartVirAddr;
#else
    stSMMUBuf.u32StartSmmuAddr = psMBuf->u32StartPhyAddr;
    stSMMUBuf.u32Size          = psMBuf->u32Size;

    s32Ret = HI_DRV_SMMU_Map(&stSMMUBuf);

    psMBuf->pu8StartVirAddr  = stSMMUBuf.pu8StartVirAddr;
#endif
    return s32Ret;
}

HI_VOID HI_DRV_VENC_Unmap(VENC_BUFFER_S *psMBuf)
{
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif

#ifndef HI_SMMU_SUPPORT
    stMMZBuf.pu8StartVirAddr = psMBuf->pu8StartVirAddr;
    stMMZBuf.u32StartPhyAddr = psMBuf->u32StartPhyAddr;
    stMMZBuf.u32Size         = psMBuf->u32Size;
    HI_DRV_MMZ_Unmap(&stMMZBuf);
#else
    stSMMUBuf.pu8StartVirAddr  = psMBuf->pu8StartVirAddr;
    stSMMUBuf.u32StartSmmuAddr = psMBuf->u32StartPhyAddr;
    stSMMUBuf.u32Size          = psMBuf->u32Size;
    HI_DRV_SMMU_Unmap(&stSMMUBuf);
#endif
}
#if 0
HI_S32 HI_DRV_VENC_Alloc(const char *bufname, char *zone_name, HI_U32 size, int align, VENC_BUFFER_S *psMBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif

#ifndef HI_SMMU_SUPPORT
    s32Ret = HI_DRV_MMZ_Alloc(bufname, zone_name, size, align, &stMMZBuf);
    psMBuf->pu8StartVirAddr  = stMMZBuf.pu8StartVirAddr;
    psMBuf->u32StartPhyAddr  = stMMZBuf.u32StartPhyAddr;
    psMBuf->u32Size          = stMMZBuf.u32Size;
#else
    s32Ret = HI_DRV_SMMU_Alloc(bufname, size, align, &stSMMUBuf);
    psMBuf->pu8StartVirAddr  = stSMMUBuf.pu8StartVirAddr;
    psMBuf->u32StartPhyAddr  = stSMMUBuf.u32StartSmmuAddr;
    psMBuf->u32Size          = stSMMUBuf.u32Size;
#endif

    return s32Ret;
}

HI_VOID HI_DRV_VENC_Release(VENC_BUFFER_S *psMBuf)
{
#ifndef HI_SMMU_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    memset(&stMMZBuf, 0 , sizeof(MMZ_BUFFER_S));
#else
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0 , sizeof(SMMU_BUFFER_S));
#endif

#ifndef HI_SMMU_SUPPORT
    stMMZBuf.pu8StartVirAddr = psMBuf->pu8StartVirAddr;
    stMMZBuf.u32StartPhyAddr = psMBuf->u32StartPhyAddr;
    stMMZBuf.u32Size         = psMBuf->u32Size;
    HI_DRV_MMZ_Release(&stMMZBuf);
#else
    stSMMUBuf.pu8StartVirAddr  = psMBuf->pu8StartVirAddr;
    stSMMUBuf.u32StartSmmuAddr = psMBuf->u32StartPhyAddr;
    stSMMUBuf.u32Size          = psMBuf->u32Size;
    HI_DRV_SMMU_Release(&stSMMUBuf);
#endif
}
#endif
/*********************************** for SMMU end ************************************/








#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
