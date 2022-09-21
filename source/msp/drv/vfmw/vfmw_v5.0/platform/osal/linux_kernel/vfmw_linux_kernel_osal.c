#include "hi_kernel_adapt.h"
#include "vfmw_linux_kernel_osal.h"
#include "public.h"
#include "vfmw_osal_ext.h"

#include "vfmw_proc.h"

//#include "drv_vfmw_ext.h"

extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;

/* Wang Yun */
/* SpinLock */
OSAL_IRQ_SPIN_LOCK g_TaskLock;
OSAL_IRQ_SPIN_LOCK g_RecordLock;
OSAL_IRQ_SPIN_LOCK g_SpinLock;
OSAL_IRQ_SPIN_LOCK g_SpinLock_fsp;
OSAL_IRQ_SPIN_LOCK g_SpinLockIrq_Destroy;
OSAL_IRQ_SPIN_LOCK g_ActivateLock;
OSAL_IRQ_SPIN_LOCK g_SpinLockIsr_MsgQueue;
OSAL_IRQ_SPIN_LOCK g_SpinLockIsr_Image2D;
OSAL_IRQ_SPIN_LOCK g_FrameBuf_SpinLock;

/* Mutext */
OSAL_TASK_MUTEX g_IntEvent;
OSAL_TASK_MUTEX g_WaitScdStopWorking;

OSAL_SEMA g_stSem;
OSAL_SEMA g_VfmwChanRlsStreamSem[MAX_CHAN_NUM];
OSAL_SEMA g_saveYUVSem[MAX_CHAN_NUM];

UINT64 OSAL_Do_Div(UINT64 Dividend, UINT32 Divison)
{
    do_div(Dividend, Divison);

    return Dividend;
}

UINT32 OSAL_GetTimeInMs(VOID)
{
    UINT64   SysTime;

    SysTime = sched_clock();
    do_div(SysTime, 1000000);
    return (UINT32)SysTime;
}

UINT32 OSAL_GetTimeInUs(VOID)
{
    UINT32 CurrUs = 0;

    struct timeval CurrentTime;
    do_gettimeofday(&CurrentTime);
    CurrUs = (UINT32)(CurrentTime.tv_sec * 1000000 + CurrentTime.tv_usec);

    return CurrUs;
}

SINT32 OSAL_CreateTask( VOID *pParam, SINT8 TaskName[], VOID *pTaskFunction )
{
    OSAL_TASK *pTask = (OSAL_TASK *)pParam;

    *pTask = kthread_create(pTaskFunction, (VOID *)NULL, TaskName);

    if (IS_ERR(*pTask))
    {
        dprint(PRN_FATAL, "can not create thread!\n");
        return ( VF_ERR_SYS );
    }

    wake_up_process(*pTask);
    return OSAL_OK;
}

SINT32 OSAL_RequestIrq(UINT32 irq, vfmw_irq_handler_t handler, unsigned long flags, const char *name, void *dev)
{
    if (0 != osal_request_irq(irq, (irq_handler_t)handler, flags, name, dev))
    {
        dprint(PRN_FATAL, "can not request irq!\n");
        return OSAL_ERR;
    }
#ifdef HI_FPGA_SUPPORT
    if (0 != HI_DRV_SYS_SetIrqAffinity(HI_ID_VFMW, irq, name))
    {
        dprint(PRN_ERROR, "HI_DRV_SYS_SetIrqAffinity error.\n");
    }
#endif

    return OSAL_OK;
}

VOID OSAL_Freeirq(UINT32 irq, const char *name, void *dev)
{
    osal_free_irq(irq, name, dev);

    return;
}


/************************************************************************/
/* 激活任务                                                             */
/************************************************************************/
SINT32 OSAL_WakeupTask( OSAL_TASK *pTask )
{
    return OSAL_OK;
}

/************************************************************************/
/* 销毁任务                                                             */
/************************************************************************/
SINT32 OSAL_DeleteTask(OSAL_TASK *pTask)
{
    return OSAL_OK;
}

/************************************************************************/
/* 初始化事件                                                           */
/************************************************************************/
VOID  OSAL_InitWaitQueue(OSAL_EVENT* pEvent)
{
    init_waitqueue_head(&(pEvent->queue_head));

    return ;
}

SINT32 OSAL_InitEvent( OSAL_EVENT* pEvent, SINT32 InitVal )
{
    pEvent->flag = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return OSAL_OK;
}

SINT32 OSAL_InitEvent_l( KERN_EVENT_S_L *pEvent, UINT32 InitVal )
{
    pEvent->flag_0 = InitVal;
    pEvent->flag_1 = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return OSAL_OK;
}

SINT32 OSAL_InitEvent_s( OSAL_EVENT *pEvent, SINT32 InitVal )
{
    pEvent->flag = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return OSAL_OK;
}

/************************************************************************/
/* 发出事件                                                             */
/************************************************************************/
VOID OSAL_WakeUp(OSAL_EVENT* pEvent)
{
    wake_up(&(pEvent->queue_head));

    return ;
}

SINT32 OSAL_GiveEvent( OSAL_EVENT* pEvent )
{
    pEvent->flag = 1;
    wake_up_interruptible ( &(pEvent->queue_head) );

    return OSAL_ERR;
}

VOID OSAL_GiveEvent_l( OSAL_EVENT_L *pEvent, UINT32 type )
{
    pEvent->flag_0 |= 1<<type;

    wake_up_interruptible ( &(pEvent->queue_head) );

    return;
}

VOID OSAL_GiveEvent_s( OSAL_EVENT *pEvent )
{
    pEvent->flag = 1;
    wake_up_interruptible ( &(pEvent->queue_head) );

    return;
}

/************************************************************************/
/* 等待事件                                                             */
/* 事件发生返回OSAL_OK，超时返回OSAL_ERR 若condition不满足就阻塞等待    */
/************************************************************************/
SINT32 OSAL_WaitQueueTimeout(OSAL_EVENT* pEvent, SINT32 condition, SINT32 msWaitTime)
{
    SINT32 l_ret;

    l_ret = wait_event_timeout(pEvent->queue_head, condition, msecs_to_jiffies(msWaitTime));

    return (l_ret == 0) ? OSAL_OK : OSAL_ERR;
}

SINT32 OSAL_WaitEvent(OSAL_EVENT* pEvent, SINT32 msWaitTime)
{
    SINT32 l_ret;

    l_ret = wait_event_interruptible_timeout(pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime));

    pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

    return (l_ret == 0) ? OSAL_OK : OSAL_ERR;
}

UINT32 OSAL_WaitEvent_l(OSAL_EVENT_L *pEvent, SINT32 msWaitTime)
{
    SINT32 l_ret;
    UINT32 ret;

    l_ret = wait_event_interruptible_timeout(pEvent->queue_head, (pEvent->flag_0 != 0 || pEvent->flag_1 != 0), msecs_to_jiffies(msWaitTime));

    if (pEvent->flag_0 == 0 && pEvent->flag_1 == 0)
    {
        l_ret = -1;
        ret = 0;
    }
    else
    {
        ret = 0;
        if (pEvent->flag_0 != 0)
        {
            ret |= pEvent->flag_0;
            pEvent->flag_0 = 0;
        }

        if (pEvent->flag_1 != 0)
        {
            ret |= pEvent->flag_1;
            pEvent->flag_1 = 0;
        }
    }

    return ret;
}

SINT32 OSAL_WaitEvent_s(OSAL_EVENT *pEvent, SINT32 msWaitTime)
{
    SINT32 l_ret;

    l_ret = wait_event_interruptible_timeout(pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime));

    pEvent->flag = 0;

    return (l_ret == 0) ? OSAL_OK : OSAL_ERR;
}

SINT8 *KernelRegisterMap(UADDR  PhyAddr)
{
    return (SINT8 *)ioremap_nocache( PhyAddr, 0x10000 );
}

VOID KernelRegisterUnMap(UINT8 *VirAddr)
{
    iounmap(VirAddr);
    return;
}

VOID *klib_fopen(const char *filename, int flags, int mode)
{
    struct file *filp = filp_open(filename, flags, mode);

    return (IS_ERR(filp)) ? NULL : (VOID *)filp;
}

VOID klib_fclose(VOID *fp)
{
    mm_segment_t oldfs;
    struct file *filp = (struct file *)fp;
    if (filp)
    {
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        vfs_fsync(filp, 0);
        set_fs(oldfs);
        filp_close(filp, NULL);
    }
}

SINT32 klib_fread(char *buf, UINT32 len, VOID *fp)
{
    int readlen;
    mm_segment_t oldfs;
    struct file *filp = (struct file *)fp;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = vfs_read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

SINT32 klib_fwrite(char *buf, UINT32 len, VOID *fp)
{
    int writelen;
    mm_segment_t oldfs;
    struct file *filp = (struct file *)fp;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = vfs_write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return writelen;
}

OSAL_SEMA *GetSemByEnum(SemType semType,int ChanID)
{
    OSAL_SEMA *pOsalSem = NULL;

    switch (semType)
    {
        case G_INIT_DEINIT_SEM:
            pOsalSem = &g_stSem;
            break;

        case G_RLSSTREAM_SEM:
            pOsalSem = &g_VfmwChanRlsStreamSem[ChanID];
            break;

        case G_SAVEYUV_SEM:
            pOsalSem = &g_saveYUVSem[ChanID];
            break;

        default:
            break;
    }
    return pOsalSem;
}

VOID OSAL_SEMA_INTIT(SemType semType,int chanID)
{
    OSAL_SEMA *pOsalSem = NULL;
    pOsalSem = GetSemByEnum(semType,chanID);
    sema_init(pOsalSem, 1);
}

SINT32 OSAL_DOWN_INTERRUPTIBLE(SemType semType,int chanID)
{
    HI_S32 s32Ret;
    OSAL_SEMA *pOsalSem = NULL;
    pOsalSem = GetSemByEnum(semType,chanID);
    s32Ret = down_interruptible(pOsalSem);
    return s32Ret;
}
VOID OSAL_UP(SemType semType,int chanID)
{
    OSAL_SEMA *pOsalSem = NULL;
    pOsalSem = GetSemByEnum(semType,chanID);
    up(pOsalSem);
}

/************************************************************************/
/* 锁初始化                                                             */
/************************************************************************/
inline VOID OSAL_SpinLockIRQInit(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_lock_init(&pIntrMutex->irq_lock);
    pIntrMutex->isInit = 1;

    return;
}

inline VOID OSAL_RWLockIRQInit(OSAL_RW_LOCK *pIntrMutex)
{
    rwlock_init(&pIntrMutex->rw_lock);
    pIntrMutex->isInit = 1;

    return;
}


/************************************************************************/
/* 中断互斥加锁(关中断且加锁)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if(pIntrMutex->isInit == 0)
    {
        spin_lock_init(&pIntrMutex->irq_lock);
        pIntrMutex->isInit = 1;
    }
    spin_lock_irqsave(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}

inline SINT32 OSAL_ReadLockIRQ(OSAL_RW_LOCK *pIntrMutex)
{
    if(pIntrMutex->isInit == 0)
    {
        rwlock_init(&pIntrMutex->rw_lock);
        pIntrMutex->isInit = 1;
    }
    read_lock_irqsave(&pIntrMutex->rw_lock, pIntrMutex->read_lockflags);

    return OSAL_OK;
}

inline SINT32 OSAL_WriteLockIRQ(OSAL_RW_LOCK *pIntrMutex)
{
    if(pIntrMutex->isInit == 0)
    {
        rwlock_init(&pIntrMutex->rw_lock);
        pIntrMutex->isInit = 1;
    }
    write_lock_irqsave(&pIntrMutex->rw_lock, pIntrMutex->write_lockflags);

    return OSAL_OK;
}

/************************************************************************/
/* 中断互斥解锁(开中断且去锁)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinUnLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    spin_unlock_irqrestore(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);

    return OSAL_OK;
}

inline SINT32 OSAL_ReadUnLockIRQ(OSAL_RW_LOCK *pIntrMutex)
{
    read_unlock_irqrestore(&pIntrMutex->rw_lock, pIntrMutex->read_lockflags);

    return OSAL_OK;
}

inline SINT32 OSAL_WriteUnLockIRQ(OSAL_RW_LOCK *pIntrMutex)
{
    write_unlock_irqrestore(&pIntrMutex->rw_lock, pIntrMutex->write_lockflags);

    return OSAL_OK;
}

/******************************************************************************
                       这里开始是产品差异化代码
******************************************************************************/

/************************************************************************/
/* 申请虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID *OSAL_AllocVirMem(SINT32 Size)
{
    return HI_VMALLOC(HI_ID_VFMW, Size);
}

/************************************************************************/
/* 释放虚拟内存（可能非物理连续）                                       */
/************************************************************************/
VOID OSAL_FreeVirMem(VOID *p)
{
    if (p)
    {
        HI_VFREE(HI_ID_VFMW, p);
    }
}

SINT32 KernelMemMalloc(UINT8 *MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
#ifdef HI_SMMU_SUPPORT
    SMMU_BUFFER_S stSMMUBuffer;
    memset(&stSMMUBuffer, 0, sizeof(SMMU_BUFFER_S));
    if(HI_SUCCESS != HI_DRV_SMMU_Alloc(MemName, len, align, &stSMMUBuffer))
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    if( 0 != stSMMUBuffer.u32StartSmmuAddr )
    {
        if(IsCached == 1)
        {
            if(HI_SUCCESS != HI_DRV_SMMU_MapCache(&stSMMUBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
        else
        {
            if(HI_SUCCESS != HI_DRV_SMMU_Map(&stSMMUBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
    }
    else
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    pMemDesc->MmuAddr = (SINT32)stSMMUBuffer.u32StartSmmuAddr;
    pMemDesc->VirAddr = PTR_UINT64(stSMMUBuffer.pu8StartVirAddr);
    pMemDesc->Length  = (SINT32)stSMMUBuffer.u32Size;
#else
    MMZ_BUFFER_S stMmzBuffer;
    memset(&stMmzBuffer, 0, sizeof(MMZ_BUFFER_S));
    if(HI_SUCCESS != HI_DRV_MMZ_Alloc(MemName, NULL, len, align, &stMmzBuffer))
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    if( 0 != stMmzBuffer.u32StartPhyAddr )
    {
        if(IsCached == 1)
        {
            if(HI_SUCCESS != HI_DRV_MMZ_MapCache(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
        else
        {
            if(HI_SUCCESS != HI_DRV_MMZ_Map(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
    }
    else
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    pMemDesc->PhyAddr = (SINT32)stMmzBuffer.u32StartPhyAddr;
    pMemDesc->VirAddr = PTR_UINT64(stMmzBuffer.pu8StartVirAddr);
    pMemDesc->Length  = (SINT32)stMmzBuffer.u32Size;
#endif

    return 0;
}

SINT32 KernelMemFree(MEM_DESC_S *pMemDesc)
{
#ifdef HI_SMMU_SUPPORT
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));
    stSMMUBuf.u32StartSmmuAddr = (UINT32)pMemDesc->PhyAddr;
    stSMMUBuf.pu8StartVirAddr  = UINT64_PTR(pMemDesc->VirAddr);
    stSMMUBuf.u32Size          = (UINT32)pMemDesc->Length;
    HI_DRV_SMMU_Unmap(&stSMMUBuf);
    HI_DRV_SMMU_Release(&stSMMUBuf);
#else
    MMZ_BUFFER_S stMBuf;
    memset(&stMBuf, 0, sizeof(MMZ_BUFFER_S));
    stMBuf.u32StartPhyAddr  = (UINT32)pMemDesc->PhyAddr;
    stMBuf.pu8StartVirAddr  = UINT64_PTR(pMemDesc->VirAddr);
    stMBuf.u32Size          = (UINT32)pMemDesc->Length;
    HI_DRV_MMZ_Unmap(&stMBuf);
    HI_DRV_MMZ_Release(&stMBuf);
#endif

    return 0;
}

UINT8 *KernelMmap(MEM_RECORD_S *pMemRec)
{
    SINT32 s32Ret = 0;
    MMZ_BUFFER_S stMemBuf;
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

#ifdef HI_SMMU_SUPPORT
    stSMMUBuf.u32StartSmmuAddr = pMemRec->PhyAddr;
    s32Ret = HI_DRV_SMMU_Map(&stSMMUBuf);
    if(s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_SMMU_Map ERR\n", __LINE__);
    }
    return stSMMUBuf.pu8StartVirAddr;
#else
    stMemBuf.u32StartPhyAddr = pMemRec->PhyAddr;
    s32Ret = HI_DRV_MMZ_Map(&stMemBuf);
    if(s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_MMZ_Map ERR\n", __LINE__);
    }
    return stMemBuf.pu8StartVirAddr;
#endif
}

UINT8 *KernelMmapMMZ(MEM_RECORD_S *pMemRec)
{
    SINT32 s32Ret = 0;
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));

    stMemBuf.u32StartPhyAddr = pMemRec->PhyAddr;
    s32Ret = HI_DRV_MMZ_Map(&stMemBuf);
    if(s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_MMZ_Map ERR\n", __LINE__);
    }
    return stMemBuf.pu8StartVirAddr;
}

UINT8 *KernelMmapCache(MEM_RECORD_S *pMemRec)
{
    SINT32 s32Ret = 0;
    MMZ_BUFFER_S stMemBuf;
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

#ifdef HI_SMMU_SUPPORT
    stSMMUBuf.u32StartSmmuAddr = pMemRec->PhyAddr;
    s32Ret = HI_DRV_SMMU_MapCache(&stSMMUBuf);
    if(s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_SMMU_MapCache ERR\n", __LINE__);
    }
    return stSMMUBuf.pu8StartVirAddr;
#else
    stMemBuf.u32StartPhyAddr = pMemRec->PhyAddr;
    s32Ret = HI_DRV_MMZ_MapCache(&stMemBuf);
    if(s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_MMZ_Map ERR\n", __LINE__);
    }
    return stMemBuf.pu8StartVirAddr;
#endif
}


VOID KernelMunmap(UINT8 *p )
{
    MMZ_BUFFER_S stMemBuf;
    SMMU_BUFFER_S stSMMUBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));
 #ifdef HI_SMMU_SUPPORT
    stSMMUBuf.pu8StartVirAddr = p;
    HI_DRV_SMMU_Unmap(&stSMMUBuf);
 #else
     stMemBuf.pu8StartVirAddr = p;
     HI_DRV_MMZ_Unmap(&stMemBuf);
 #endif
}


VOID KernelMunmapMMZ(UINT8 *p )
{
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));

    stMemBuf.pu8StartVirAddr = p;
    HI_DRV_MMZ_Unmap(&stMemBuf);
}


VOID KernelFlushCache(VOID *ptr, UADDR phy_addr, UINT32 len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);

    spin_lock_irqsave(&cache_lock, flags);
#ifdef HI_VFMW_32BIT //64bit
    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr + len); // flush l2cache
#else
    __flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache 64bit
    flush_icache_range(phy_addr, phy_addr+len); // 64bit
#endif

    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

VOID KernelGetPageTableAddr(UINT32 *pu32ptaddr, UINT32 *pu32err_rdaddr, UINT32 *pu32err_wraddr)
{
 #ifdef HI_SMMU_SUPPORT
    HI_DRV_SMMU_GetPageTableAddr(pu32ptaddr, pu32err_rdaddr, pu32err_wraddr);
 #endif
}

SINT32 HI_GetVp9_Support(UINT32 *pVp9Support)
{
#ifdef VFMW_STB_PRODUCT
    *pVp9Support= 1;
    return HI_SUCCESS;
#else
    return HI_DRV_SYS_GetVP9Support(pVp9Support);
#endif
}

void klib_flush_cache(void *ptr, UADDR phy_addr, unsigned int len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);

    spin_lock_irqsave(&cache_lock, flags);
#ifdef HI_VFMW_32BIT //64bit
    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr + len); // flush l2cache
#else
    __flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache 64bit
    flush_icache_range(phy_addr, phy_addr+len); //64bit
#endif

    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

VOID Sema_Init_with_Option(OSAL_SEMA *stSem)
{
    sema_init(stSem, 1);
}

SINT32 Down_Interruptible_with_Option(OSAL_SEMA *stSem)
{
    SINT32 s32Ret;
    s32Ret = down_interruptible(stSem);
    return s32Ret;
}

VOID Up_Interruptible_with_Option(OSAL_SEMA *stSem)
{
    up(stSem);
}

/* Wang Yun */
OSAL_IRQ_SPIN_LOCK *GetSpinLockByEnum(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    switch (spinLockType)
    {
        case G_TASKLOCK:
            pOsalSpinLock = &g_TaskLock;
            break;

        case G_RECORDLOCK:
            pOsalSpinLock = &g_RecordLock;
            break;

        case G_SPINLOCK:
            pOsalSpinLock = &g_SpinLock;
            break;

        case G_SPINLOCK_FSP:
            pOsalSpinLock = &g_SpinLock_fsp;
            break;

        case G_SPINLOCKIRQ_DESTROY:
            pOsalSpinLock = &g_SpinLockIrq_Destroy;
            break;

        case G_ACTIVATELOCK:
            pOsalSpinLock = &g_ActivateLock;
            break;

        case G_SPINLOCKISR_MSGQUE:
            pOsalSpinLock = &g_SpinLockIsr_MsgQueue;
            break;

        case G_SPINLOCKISR_IMAGE2D:
            pOsalSpinLock = &g_SpinLockIsr_Image2D;
            break;

        case G_FRAMEBUF:
            pOsalSpinLock = &g_FrameBuf_SpinLock;
            break;

        default:
            break;
    }

    return pOsalSpinLock;
}

VOID Osal_SpinLockInit(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    OSAL_SpinLockIRQInit(pOsalSpinLock);
}

SINT32 Osal_SpinLock(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    return OSAL_SpinLockIRQ(pOsalSpinLock);
}


SINT32 Osal_SpinUnLock(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    return OSAL_SpinUnLockIRQ(pOsalSpinLock);
}

SINT32 Osal_InitWaitQue(MutexType mutextType, SINT32 initVal)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutextType)
    {
        case G_INTEVENT:
            retVal = OSAL_InitEvent(&g_IntEvent, initVal);
            break;

        case G_INTWAITQUEUE:
            retVal = OSAL_OK;
            OSAL_InitWaitQueue(&g_WaitScdStopWorking);
            break;

        default:
            break;
    }

    return retVal;
}

SINT32 Osal_WakeupWaitQue(MutexType mutexType)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_GiveEvent(&g_IntEvent);
            break;

        case G_INTWAITQUEUE:
            retVal = OSAL_OK;
            OSAL_WakeUp(&g_WaitScdStopWorking);
            break;

        default:
            break;
    }

    return retVal;
}

SINT32 Osal_WaitWaitQue(MutexType mutexType, SINT32 condition, SINT32 waitTimeInMs)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_WaitEvent(&g_IntEvent, waitTimeInMs);
            break;

        case G_INTWAITQUEUE:
            retVal = OSAL_WaitQueueTimeout(&g_WaitScdStopWorking, condition, waitTimeInMs);
            break;

        default:
            break;
    }

    return retVal;
}

UINT32 strlcpy_command_line(char *dest, UINT32 size)
{
    return strlcpy(dest, saved_command_line, size);
}

VOID Osal_mb(VOID)
{
    mb();
}

VOID Osal_udelay(unsigned long usecs)
{
    udelay(usecs);
}

VOID OSAL_InitVfmwInterface(VOID)
{
    memset(&vfmw_Osal_Func_Ptr_S, 0, sizeof(Vfmw_Osal_Func_Ptr));

    vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInMs = OSAL_GetTimeInMs;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInUs = OSAL_GetTimeInUs;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit = Osal_SpinLockInit;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLock     = Osal_SpinLock;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinUnlock   = Osal_SpinUnLock;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaInit = OSAL_SEMA_INTIT;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown = OSAL_DOWN_INTERRUPTIBLE;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp   = OSAL_UP;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileOpen  = klib_fopen;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileClose = klib_fclose;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileRead  = klib_fread;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite = klib_fwrite;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet = (FN_OSAL_MemSet)memset;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCpy = (FN_OSAL_MemCpy)memcpy;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemMov = (FN_OSAL_MemMov)memmove;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCmp = (FN_OSAL_MemCmp)memcmp;

#ifndef HI_ADVCA_FUNCTION_RELEASE
    vfmw_Osal_Func_Ptr_S.pfun_Osal_printk = printk;
#else
    vfmw_Osal_Func_Ptr_S.pfun_Osal_printk = NULL;
#endif

    vfmw_Osal_Func_Ptr_S.pfun_Osal_snprintf = (FN_OSAL_snprintf)snprintf;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_sscanf   = sscanf;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strncmp  = (FN_OSAL_strncmp)strncmp;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy_command_line = strlcpy_command_line;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy       = (FN_OSAL_strlcpy)strlcpy;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strsep        = (FN_OSAL_strsep)strsep;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_simple_strtol = (FN_OSAL_simple_strtol)simple_strtol;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strstr        = (FN_OSAL_strstr)strstr;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlen        = (FN_OSAL_strlen)strlen;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_msleep = msleep;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_mb     = Osal_mb;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay = Osal_udelay;


    vfmw_Osal_Func_Ptr_S.pfun_Osal_InitEvent = Osal_InitWaitQue;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_GiveEvent = Osal_WakeupWaitQue;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_WaitEvent = Osal_WaitWaitQue;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_FlushCache       = klib_flush_cache;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelFlushCache = KernelFlushCache;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemAlloc = KernelMemMalloc;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemFree  = KernelMemFree;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterMap   = KernelRegisterMap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterUnMap = KernelRegisterUnMap;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmap      = KernelMmap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMap    = KernelMunmap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapCache = KernelMmapCache;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapMMZ      = KernelMmapMMZ;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMapMMZ    = KernelMunmapMMZ;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelGetPageTableAddr = KernelGetPageTableAddr;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_CreateTask = OSAL_CreateTask;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_phys_to_virt = (FN_OSAL_phys_to_virt)phys_to_virt;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_AllocVirMem = OSAL_AllocVirMem;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FreeVirMem  = OSAL_FreeVirMem;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_request_irq = OSAL_RequestIrq;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_free_irq    = OSAL_Freeirq;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_init    = (FN_OSAL_vfmw_proc_init)vfmw_proc_init;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_exit    = (FN_OSAL_vfmw_proc_exit)vfmw_proc_exit;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_create  = (FN_OSAL_vfmw_proc_create)vfmw_proc_create;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_destroy = (FN_OSAL_vfmw_proc_destroy)vfmw_proc_destroy;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_GetVp9Support = HI_GetVp9_Support;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_DoDiv = OSAL_Do_Div;
}
