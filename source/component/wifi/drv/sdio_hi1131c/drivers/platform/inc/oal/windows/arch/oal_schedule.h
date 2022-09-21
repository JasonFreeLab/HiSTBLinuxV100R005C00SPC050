/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_schedule.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月29日
  最近修改   :
  功能描述   : oal_types.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_WINDOWS_SCHEDULE_H__
#define __OAL_WINDOWS_SCHEDULE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <windows.h>
#include <time.h>
#include "oal_util.h"
#include "oal_types.h"
#include "oal_mm.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* typedef CRITICAL_SECTION    oal_spin_lock_stru; zouhongliang 保持windows下与linux下大小一致 */
typedef struct
{
    oal_uint8       auc_resv[4];
}oal_spin_lock_stru;

typedef LONG volatile       oal_atomic;

typedef oal_uint32          (*oal_irqlocked_func)(oal_void *);

typedef CRITICAL_SECTION    oal_rwlock_stru;

typedef oal_void            (*oal_defer_func)(oal_uint);

typedef oal_void         oal_wait_queue_stru;

typedef struct
{
    oal_uint32      resv1[4];
    oal_uint32      resv2[4];
}oal_wait_queue_head_stru;


typedef struct semaphore          oal_semaphore_stru;
typedef struct _oal_wakelock_stru_
{
#ifdef CONFIG_HAS_WAKELOCK
    struct wake_lock        st_wakelock;        //wakelock锁
    oal_spin_lock_stru      lock;    //wakelock锁操作spinlock锁
#endif
    oal_ulong               lock_count;         //持有wakelock锁的次数
    oal_ulong               locked_addr;/*the locked address*/
}oal_wakelock_stru;


/* Tasklet is scheduled for execution */
#define TASKLET_STATE_SCHED     (0)

/* tasklet声明 */
#define OAL_DECLARE_TASK(_name, _func, _p_data) \
    struct oal_tasklet_stru _name = {NULL, 0, _func, _p_data, 0, NULL, THREAD_PRIORITY_ABOVE_NORMAL}

/*****************************************************************************
 函 数 名  : oal_wait_event_interruptible_timeout
 功能描述  : win32封装
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_wait_event_interruptible_timeout(oal_wait_queue_head_stru st_wq, oal_uint8 uc_bool, oal_int i_time)
{
    return 50;
}

OAL_STATIC OAL_INLINE oal_int32  oal_wait_event_interruptible(oal_wait_queue_head_stru st_wq, oal_uint8 uc_bool)
{
    return 10;
}

OAL_STATIC OAL_INLINE oal_int32  oal_wait_event_timeout(oal_wait_queue_head_stru st_wq, oal_uint8 uc_bool, oal_int i_time)
{
    return 50;
}


#define OAL_WAIT_EVENT_INTERRUPTIBLE_TIMEOUT(_st_wq, _condition, _timeout)      oal_wait_event_interruptible_timeout(_st_wq, _condition, _timeout)

#define OAL_WAIT_EVENT_TIMEOUT(_st_wq, _condition, _timeout)      oal_wait_event_timeout(_st_wq, _condition, _timeout)

#define OAL_WAIT_EVENT_INTERRUPTIBLE(_st_wq, _condition)      oal_wait_event_interruptible(_st_wq, _condition)


#define OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(_pst_wq)   OAL_REFERENCE(_pst_wq)

#define OAL_WAIT_QUEUE_WAKE_UP(_pst_wq)

#define OAL_INTERRUPTIBLE_SLEEP_ON(_pst_wq)

#define OAL_WAIT_QUEUE_INIT_HEAD(_pst_wq)


#if (_PRE_CHIP_BITS_MIPS32 == _PRE_CHIP_BITS)
/* 32位寄存器最大长度 */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFF - 1)

#elif (_PRE_CHIP_BITS_MIPS64 == _PRE_CHIP_BITS)
/* 64位寄存器最大长度 */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFFFFFFFFFF - 1)

#endif

/* 获取毫秒级时间戳 */
#define OAL_TIME_GET_STAMP_MS() clock()
#define OAL_TIME_GET_HIGH_PRECISION_MS() clock()

#define OAL_ENABLE_CYCLE_COUNT()
#define OAL_DISABLE_CYCLE_COUNT()
#define OAL_GET_CYCLE_COUNT()

/* 寄存器反转模块运行时间计算 */
#define OAL_TIME_CALC_RUNTIME(_ul_start, _ul_end)   ((OAL_TIME_US_MAX_LEN) - (_ul_start) + (_ul_end))

#define OAL_TIME_JIFFY  15

#define OAL_TIME_HZ     (1000)


#define OAL_MSECS_TO_JIFFIES(_msecs)    (_msecs)

#define OAL_JIFFIES_TO_MSECS(_jiffies)  (_jiffies)

#define OAL_INIT_COMPLETION(_my_completion) {}

#define OAL_COMPLETE(_my_completion)        {}

/* 获取从_ul_start到_ul_end的时间差 */
#define OAL_TIME_GET_RUNTIME(_ul_start, _ul_end) \
    (((_ul_start) > (_ul_end))?(OAL_TIME_CALC_RUNTIME((_ul_start), (_ul_end))):((_ul_end) - (_ul_start)))


OAL_STATIC OAL_INLINE oal_int32  oal_in_interrupt()
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_int32 oal_in_atomic()
{
    return 0;
}


typedef void (*oal_timer_func)(oal_uint);

typedef struct
{
    oal_uint32                  ul_delay;
    oal_timer_func              p_timer_func;
    oal_uint                    ui_arg;
    oal_uint32                  ul_timer_id;
}oal_timer_list_stru;

/* 模块入口 */
#define oal_module_init(_module_name)

#define oal_module_license(_license_name)

/* 模块出口 */
#define oal_module_exit(_module_name)

#define oal_module_param(_symbol, _type, _name)

/* 模块符号导出 */
#define oal_module_symbol(_symbol)
#define OAL_MODULE_DEVICE_TABLE(_type, _name)

#define oal_smp_call_function_single(core, task, info, wait)
#define IS_ERR(x) (0)
#define IS_ERR_OR_NULL(x) (0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef int (read_proc_t)(oal_int8 *, oal_int8 **, oal_int,
                                       oal_int32, oal_int32 *, oal_void *);
typedef int (write_proc_t)(oal_file_stru *, const oal_int8 *,
                                       oal_uint32, oal_void *);
typedef struct
{
    oal_uint32               ul_done; //标志是否已经做完，未做完就是负值，代表等待个数，完成为0

    oal_wait_queue_head_stru st_wait;

}oal_completion;

#define DECLARE_COMPLETION(work) oal_completion work

typedef struct
{
    oal_int i_sec;
    oal_int i_usec;
}oal_time_us_stru;

typedef union{
    oal_int i_sec;
    oal_int i_usec;
}oal_time_t_stru;

/* 线程结构体 */
typedef struct
{
    LPSECURITY_ATTRIBUTES       lp_thread_attributes;       /* 指向SECURITY_ATTRIBUTES的指针，设定线程的安全性 */
    oal_uint32                  ul_stack_size;              /* 设置线程初始栈的大小 */
    oal_defer_func              p_startaddress_func;        /* 线程所要执行的的函数的初始地址 */
    oal_uint                    ui_parameter;               /* 给新线程所要传递的参数 */
    oal_uint32                  ul_creationflags;           /* 设置控制线程创建的附加标记 */
    HANDLE                      threadhead;                 /* 线程操作对象 */
    oal_int32                   l_npriority;                /* 线程优先级 */
    oal_int                     i_state;                    /* 线程调度状态 */
}oal_tasklet_stru;

typedef struct
{
    oal_void            *data;
    oal_uint16           nlink;
    oal_uint8            resv[2];

    read_proc_t         *read_proc;
    write_proc_t        *write_proc;

}oal_proc_dir_entry_stru;

typedef struct
{
    oal_atomic            count;
    oal_spin_lock_stru    wait_lock;
}oal_mutex_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#define SIGHUP       1
#define SIGINT       2
#define SIGQUIT      3
#define SIGILL       4
#define SIGTRAP      5
#define SIGABRT      6
#define SIGIOT       6
#define SIGBUS       7
#define SIGFPE       8
#define SIGKILL      9
#define SIGUSR1     10
#define SIGSEGV     11
#define SIGUSR2     12
#define SIGPIPE     13
#define SIGALRM     14
#define SIGTERM     15
#define SIGSTKFLT   16
#define SIGCHLD     17
#define SIGCONT     18
#define SIGSTOP     19
#define SIGTSTP     20
#define SIGTTIN     21
#define SIGTTOU     22
#define SIGURG      23
#define SIGXCPU     24
#define SIGXFSZ     25
#define SIGVTALRM   26
#define SIGPROF     27
#define SIGWINCH    28
#define SIGIO       29
#define SIGPOLL     SIGIO

#define ERESTARTSYS 512

#define SCHED_NORMAL        0
#define SCHED_FIFO      1
#define SCHED_RR        2
#define SCHED_BATCH     3
/* SCHED_ISO: reserved but not implemented yet */
#define SCHED_IDLE      5
struct task_struct {
    volatile long state;    /* -1 unrunnable, 0 runnable, >0 stopped */
    void *stack;/*add if you use*/
};

struct semaphore {
    unsigned int        count;
};

struct sched_param {
    int sched_priority;
};

typedef struct _oal_task_lock_stru_
{
    oal_wait_queue_head_stru    wq;
    struct task_struct  *claimer;   /* task that has host claimed */
    oal_ulong            claim_addr;
    oal_uint32           claimed;
    oal_int32            claim_cnt;
}oal_task_lock_stru;

OAL_STATIC OAL_INLINE static char* oal_get_current_task_name()
{
    return "win32";
}

/*****************************************************************************
 函 数 名  : allow_signal
 功能描述  : kernel function
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE int allow_signal(int sig)
{
        return 0;
}


/*****************************************************************************
 函 数 名  : oal_atomic_read
 功能描述  : 读取原子变量的值
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32  oal_atomic_read(oal_atomic *p_vector)
{
    return (oal_int32)(*p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_set
 功能描述  : 原子地设置原子变量p_vector值为ul_val
 输入参数  : p_vector: 需要进行原子操作的原子变量地址
             l_val  : 需要被设置成的值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_atomic_set(oal_atomic *p_vector, oal_int32 l_val)
{
    *p_vector = (LONG)l_val;
}

/*****************************************************************************
 函 数 名  : oal_atomic_dec
 功能描述  : 原子的给入参减1，
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void oal_atomic_dec(oal_atomic *p_vector)
{
    InterlockedDecrement(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_inc
 功能描述  : 原子的给如参加一
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_atomic_inc(oal_atomic *p_vector)
{
    InterlockedIncrement(p_vector);
}

/*****************************************************************************
 函 数 名  : oal_atomic_inc_and_test
 功能描述  : 原子递增后检查结果是否为0
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_atomic_inc_and_test(oal_atomic *p_vector)
{
    /*InterlockedIncrementtest(p_vector);*/
}

/*****************************************************************************
 函 数 名  : oal_atomic_dec_and_test
 功能描述  : 原子递减后检查结果是否为0
 输入参数  : *p_vector: 需要进行原子操作的原子变量地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_atomic_dec_and_test(oal_atomic *p_vector)
{
    /*InterlockedDecrementandtest(p_vector);*/
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_init
 功能描述  : 自旋锁初始化,windows下现在没有用，为了与linux下锁的结构大小一致，
             此函数暂时什么都不做，直接返回。zouhongliang
 输入参数  : *pst_lock: 自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_spin_lock_init(oal_spin_lock_stru *pst_lock)
{
    /* InitializeCriticalSection(pst_lock);*/
}

/*****************************************************************************
 函 数 名  : oal_spin_lock
 功能描述  : 获得自旋锁,windows下现在没有用，为了与linux下锁的结构大小一致，
             此函数暂时什么都不做，直接返回。zouhongliang
 输入参数  : *pst_lock: 自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_spin_lock(oal_spin_lock_stru *pst_lock)
{
    /* EnterCriticalSection(pst_lock);*/
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock
 功能描述  : 释放自旋锁,windows下现在没有用，为了与linux下锁的结构大小一致，
             此函数暂时什么都不做，直接返回。zouhongliang
 输入参数  : *pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_spin_unlock(oal_spin_lock_stru *pst_lock)
{
    /* LeaveCriticalSection(pst_lock); */
}

/***************************************************************************
函 数 名 : oal_spin_lock_bh

功能描述 : 自旋锁在软中断以及内核线程等核心态上下文环境下的加锁操作。
           如果能够立即获得锁，它就马上返回，否则，它将自旋在那里，直到
           该自旋锁的保持者释放，这时，它就获得锁并返回。windows下现在
           没有用，为了与linux下锁的结构大小一致,此函数暂时什么都不做，
           直接返回。zouhongliang
输入参数 : pst_lock:自旋锁地址
输出参数 : 无
返 回 值 :
调用函数 :
被调函数 :

修改历史 :
 1.日    期 : 2012年9月25日
   作    者 : 
   修改内容 : 新生成函数

****************************************************************************/
OAL_INLINE oal_void oal_spin_lock_bh(oal_spin_lock_stru *pst_lock)
{
    /* EnterCriticalSection(pst_lock); */
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_bh
 功能描述  : Spinlock在软中断以及内核线程等核心态上下文环境下的解锁操作
             windows下现在没有用，为了与linux下锁的结构大小一致,此函数暂时什么都不做，
             直接返回。zouhongliang
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void oal_spin_unlock_bh(oal_spin_lock_stru *pst_lock)
{
    /* LeaveCriticalSection(pst_lock); */
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_save
 功能描述  : 获得自旋锁的同时把保存标志寄存器的值，并且失效本地中断。
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_spin_lock_irq_save(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_irq_save(pui_flags, OAL_5115IRQ_OSLIS);

    oal_spin_lock(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_irq_restore
 功能描述  : 释放自旋锁的同时，恢复标志寄存器的值，恢复本地中断。它与oal_sp-
             in_lock_irq配对使用。
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_spin_unlock_irq_restore(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_unlock(pst_lock);

    oal_irq_restore(pui_flags, OAL_5115IRQ_OSLIS);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_exec
 功能描述  : 获取自旋锁，关闭中断，执行某个函数，完了之后再打开中断，释放自
             旋锁。
 输入参数  : *pst_lock:自旋锁地址
             func：函数指针地址
             *p_arg：函数参数
             pui_flags:中断标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_spin_lock_irq_exec(oal_spin_lock_stru *pst_lock, oal_irqlocked_func p_irq_locked_func, oal_void *p_arg, oal_uint *pui_flags)
{
    oal_uint32  ul_Rslt;

    oal_spin_lock_irq_save(pst_lock, pui_flags);

    ul_Rslt = p_irq_locked_func(p_arg);

    oal_spin_unlock_irq_restore(pst_lock, pui_flags);

    return ul_Rslt;
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_init
 功能描述  : 读写锁初始化，把读写锁设置为1（未锁状态）。
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_rw_lock_init(oal_rwlock_stru *pst_lock)
{
    /* InitializeCriticalSection(pst_lock); */
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_read_lock
 功能描述  : 获得指定的读锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_rw_lock_read_lock(oal_rwlock_stru *pst_lock)
{
    /* EnterCriticalSection(pst_lock); */
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_read_unlock
 功能描述  : 释放指定的读锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_rw_lock_read_unlock(oal_rwlock_stru *pst_lock)
{
    /*LeaveCriticalSection(pst_lock);*/
}

/*****************************************************************************
 函 数 名  : oal_write_lock
 功能描述  : 获得指定的写锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_rw_lock_write_lock(oal_rwlock_stru *pst_lock)
{
    /*EnterCriticalSection(pst_lock);*/
}

/*****************************************************************************
 函 数 名  : oal_rw_lock_write_unlock
 功能描述  : 释放指定的写锁
 输入参数  : pst_lock: 读写锁结构体地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_rw_lock_write_unlock(oal_rwlock_stru *pst_lock)
{
    /*LeaveCriticalSection(pst_lock);*/
}

/*****************************************************************************
 函 数 名  : oal_thread_process
 功能描述  : tasklet执行的函数入口，只为内部接口提供不对外
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

#if 0
OAL_STATIC DWORD WINAPI  oal_thread_process(LPVOID p_parameter)
{
    oal_tasklet_stru   *pst_task;
    oal_defer_func      p_func;
    oal_uint            ui_args;

    pst_task    = (oal_tasklet_stru *)p_parameter;
    p_func      = pst_task->p_startaddress_func;
    ui_args     = pst_task->ui_parameter;

    p_func(ui_args);

    oal_bit_atomic_clear(TASKLET_STATE_SCHED, &(pst_task->i_state));

    return 0;
}
#endif


/*****************************************************************************
 函 数 名  : oal_task_init
 功能描述  : 任务初始化。初始化完成后，任务处于挂起状态。*pst_task有调用者负责分配内存空间
 输入参数  : pst_task: 任务结构体指针
             func: 任务处理函数入口地址
             p_args: 需进行处理的函数的入参地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_task_init(oal_tasklet_stru *pst_task, oal_defer_func p_func, oal_uint ui_args)
{
    pst_task->lp_thread_attributes      = NULL;                                 /* 该线程使用默认安全性 */
    pst_task->ul_stack_size             = 0;                                    /* 适用于调用该函数的线程相同大小的栈空间大小 */
    pst_task->p_startaddress_func       = p_func;                               /* 传递线程须执行的函数首地址 */
    pst_task->ui_parameter              = ui_args;                              /* 传递线程参数 */
    pst_task->ul_creationflags          = 0;                                    /* 设置为线程创建立即执行 */
    pst_task->l_npriority               = THREAD_PRIORITY_ABOVE_NORMAL;         /* 优先级为高于标准 */
}

/*****************************************************************************
 函 数 名  : oal_task_kill
 功能描述  : 退出task运行
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月29日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_task_kill(oal_tasklet_stru *pst_task)
{
}

/*****************************************************************************
 函 数 名  : oal_task_sched
 功能描述  : 任务调度，令任务处于准备就绪状态；当任务执行完后，又回到挂起状
             态。
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_task_sched(oal_tasklet_stru *pst_task)
{

}

/*****************************************************************************
 函 数 名  : oal_task_is_scheduled
 功能描述  : 检测tasklet是否等待执行
 输入参数  : pst_task: 任务结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint oal_task_is_scheduled(oal_tasklet_stru *pst_task)
{
    return (pst_task->i_state & (1 << (TASKLET_STATE_SCHED + 1)));
}

/*****************************************************************************
 函 数 名  : oal_time_get_stamp_us
 功能描述  : 获取微妙精度级的时间戳
 输入参数  : pst_usec: 时间结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_time_get_stamp_us(oal_time_us_stru *pst_usec)
{
    pst_usec->i_sec     = 0;

    pst_usec->i_usec    = 0;
}

/*****************************************************************************
 函 数 名  : oal_ktime_get
 功能描述  : 获取当前时间戳
 输入参数  : oal_void
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_get(oal_void)
{
    oal_time_t_stru st_time = {0};
    return st_time;
}

/*****************************************************************************
 函 数 名  : oal_ktime_sub
 功能描述  : 获取时间差值
 输入参数  : const oal_time_t_stru lhs,
             const oal_time_t_stru rhs
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_sub(const oal_time_t_stru lhs, const oal_time_t_stru rhs)
{
    oal_time_t_stru st_time = {0};
    return st_time;
}

extern oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg);
extern oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer);
extern oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer);
extern oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_expires);
extern oal_void  oal_timer_add(oal_timer_list_stru *pst_timer);

/*****************************************************************************
 函 数 名  : oal_timer_start_on
 功能描述  : 指定cpu,重启定时器,调用时timer要处于非激活状态否者会死机
 输入参数  : pst_timer: 结构体指针
             ui_expires: 重启的溢出事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_timer_start_on(oal_timer_list_stru *pst_timer, oal_uint ui_delay, oal_int32 cpu)
{
    OAL_REFERENCE(pst_timer);
    OAL_REFERENCE(ui_delay);
    OAL_REFERENCE(cpu);
}

/*****************************************************************************
 函 数 名  : oal_copy_from_user
 功能描述  : 将用户态数据拷贝到内核态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  : 拷贝的字符串长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_copy_from_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    oal_memcopy(p_to, p_from, ul_size);

    return 0;
}

/*****************************************************************************
 函 数 名  : oal_copy_to_user
 功能描述  : 将内核态数据拷贝到用户态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  : 拷贝的字符串长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月27日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_copy_to_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    oal_memcopy(p_to, p_from, ul_size);

    return 0;
}

/*****************************************************************************
 函 数 名  : oal_create_proc_entry
 功能描述  : 创建proc_entry结构体
 输入参数  : pc_name: 创建的proc_entry的名字
             us_mode: 创建模式
             pst_parent: 母proc_entry结构体，继承属性
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_proc_dir_entry_stru* oal_create_proc_entry(const oal_int8 *pc_name, oal_uint16 us_mode, oal_proc_dir_entry_stru *pst_parent)
{
    oal_proc_dir_entry_stru     *pst_proc_entry;

    pst_proc_entry = (oal_proc_dir_entry_stru *)oal_memalloc(sizeof(oal_proc_dir_entry_stru));

    return pst_proc_entry;
}

/*****************************************************************************
 函 数 名  : oal_remove_proc_entry
 功能描述  : 创建proc_entry结构体
 输入参数  : pc_name: 创建的proc_entry的名字
             pst_parent: 母proc_entry结构体，继承属性
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE void oal_remove_proc_entry(const oal_int8 *pc_name, oal_proc_dir_entry_stru *pst_parent)
{
    oal_free(pst_parent);
    return;
}

/*****************************************************************************
 函 数 名  : oal_time_is_before
 功能描述  : 判断ul_time是否比当前时间早
             若早，表示超时时间已过；若不早，表明还未超时
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_is_before(oal_uint ui_time)
{
    return 1;
}

/*****************************************************************************
 函 数 名  : oal_time_after
 功能描述  : 判断时间戳ul_time_a是否在ul_time_b之后:
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : Return: 1 ul_time_a在ul_time_b之后; 否则 Return: 0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_after(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return 1;
}

/*****************************************************************************
 函 数 名  : oal_wait_for_completion_timeout
 功能描述  : 同步：等待超时检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_wait_for_completion_timeout(oal_completion *pst_completion, oal_uint32 ul_timeout)
{
    return 1;
}

/*****************************************************************************
 函 数 名  : oal_smp_task_lock
 功能描述  : lock the task, the lock can be double locked by the same process
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_smp_task_lock(oal_task_lock_stru* pst_lock)
{
    OAL_REFERENCE(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_smp_task_unlock
 功能描述  : unlock the task
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_smp_task_unlock(oal_task_lock_stru* pst_lock)
{
    OAL_REFERENCE(pst_lock);
}

/*****************************************************************************
 函 数 名  : oal_smp_task_lock_init
 功能描述  : task struct init
 输入参数  : 
             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_smp_task_lock_init(oal_task_lock_stru* pst_lock)
{
    OAL_REFERENCE(pst_lock);
}


OAL_STATIC OAL_INLINE oal_void oal_wake_lock_init(oal_wakelock_stru *pst_wakelock,char* name)
{

}

OAL_STATIC OAL_INLINE oal_void oal_wake_lock_exit(oal_wakelock_stru *pst_wakelock)
{

}

OAL_STATIC OAL_INLINE void oal_wake_lock(oal_wakelock_stru *pst_wakelock)
{

}

OAL_STATIC OAL_INLINE  void oal_wake_unlock(oal_wakelock_stru *pst_wakelock)
{

}

OAL_STATIC OAL_INLINE oal_uint oal_wakelock_active(oal_wakelock_stru *pst_wakelock)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_void oal_sema_init(oal_semaphore_stru *sem, oal_int32 val)
{
}


OAL_STATIC OAL_INLINE oal_void oal_up(oal_semaphore_stru *sem)
{
}

OAL_STATIC OAL_INLINE oal_void oal_down(oal_semaphore_stru *sem)
{
}

OAL_STATIC OAL_INLINE oal_int32 oal_down_timeout(oal_semaphore_stru *sem,oal_int32 jiffies)
{
    return 0;
}
OAL_STATIC OAL_INLINE oal_int32 oal_down_interruptible(oal_semaphore_stru *sem)
{
    return 0;
}

 OAL_STATIC OAL_INLINE oal_int32 oal_down_trylock(oal_semaphore_stru *sem)
{
    return 0;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
