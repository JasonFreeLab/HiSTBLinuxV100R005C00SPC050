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

#ifndef __OAL_LINUX_SCHEDULE_H__
#define __OAL_LINUX_SCHEDULE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/*lint -e322*/

#include <linux/interrupt.h>
#include <asm/param.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <asm/uaccess.h>



#include "oal_mutex.h"
#include "oal_semaphore.h"
#include "oal_task.h"
#include "oal_rw_lock.h"
#include "oal_spinlock.h"
#include "oal_wakelock.h"
#include "oal_timer.h"
#include "oal_time.h"
#include "oal_atomic.h"
#include "oal_wait.h"
#include "oal_completion.h"
#include "oal_mm.h"

/*lint +e322*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/



/**
 * wait_event_interruptible_timeout - sleep until a condition gets true or a timeout elapses
 * @_wq: the waitqueue to wait on
 * @_condition: a C expression for the event to wait for
 * @_timeout: timeout, in jiffies
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a signal is received.
 * The @condition is checked each time the waitqueue @wq is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the wait condition.
 *
 * The function returns 0 if the @timeout elapsed, -ERESTARTSYS if it
 * was interrupted by a signal, and the remaining jiffies otherwise
 * if the condition evaluated to true before the timeout elapsed.
 */





#define oal_in_interrupt()  in_interrupt()

#define oal_in_atomic()     in_atomic()


typedef oal_uint32 (*oal_module_func_t)(oal_void);

/* 模块入口 */
#define oal_module_init(_module_name)   module_init(_module_name)

#define oal_module_license(_license_name) MODULE_LICENSE(_license_name)

#define oal_module_param    module_param

#define OAL_S_IRUGO         S_IRUGO

/* 模块出口 */
#define oal_module_exit(_module_name)   module_exit(_module_name)

/* 模块符号导出 */
#define oal_module_symbol(_symbol)      EXPORT_SYMBOL(_symbol)
#define OAL_MODULE_DEVICE_TABLE(_type, _name) MODULE_DEVICE_TABLE(_type, _name)

#ifdef HI1131C_SDIO_DETECT_SUPPORT/*sdio_detect.ko not need export symbol*/
    #define OAL_EXPORT_SYMBOL(_symbol)
#else
    #define OAL_EXPORT_SYMBOL(_symbol)      EXPORT_SYMBOL(_symbol)
#endif

#define oal_smp_call_function_single(core, task, info, wait) smp_call_function_single(core, task, info, wait)

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
typedef struct proc_dir_entry       oal_proc_dir_entry_stru;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



/*****************************************************************************
 函 数 名  : oal_copy_from_user
 功能描述  : 将用户态数据拷贝到内核态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_copy_from_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_from_user(p_to, p_from, (oal_uint)ul_size);
}

/*****************************************************************************
 函 数 名  : oal_copy_to_user
 功能描述  : 将内核态数据拷贝到用户态
 输入参数  : p_to: 目的地
             p_from : 源
             ul_size : 需要拷贝的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月27日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_copy_to_user(oal_void *p_to, const oal_void *p_from, oal_uint32 ul_size)
{
    return (oal_uint32)copy_to_user(p_to, p_from, (oal_uint)ul_size);
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
OAL_STATIC OAL_INLINE oal_proc_dir_entry_stru* oal_create_proc_entry(const oal_int8 *pc_name, oal_uint16 us_mode, oal_proc_dir_entry_stru *pst_parent)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    return NULL;
#else
    return create_proc_entry(pc_name, us_mode, pst_parent);
#endif
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
#else
    return remove_proc_entry(pc_name, pst_parent);
#endif
}



#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
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
extern oal_void _oal_smp_task_lock_(oal_task_lock_stru* pst_lock,oal_ulong  claim_addr);
#define oal_smp_task_lock(lock)    _oal_smp_task_lock_(lock, (oal_ulong)_THIS_IP_)

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
	oal_ulong flags;

	if(OAL_WARN_ON(in_interrupt() || in_atomic()))
	{
	    return;
	}

    if(OAL_UNLIKELY(!pst_lock->claimed))
    {
        OAL_WARN_ON(1);
        return;
    }

    oal_spin_lock_irq_save(&pst_lock->lock, &flags);
	if(--pst_lock->claim_cnt)
	{
	    oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
	}
	else
	{
		pst_lock->claimed = 0;
		pst_lock->claimer = NULL;
		oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
		wake_up(&pst_lock->wq);
	}
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
    oal_memset((oal_void*)pst_lock,0,sizeof(oal_task_lock_stru));

	oal_spin_lock_init(&pst_lock->lock);
	OAL_WAIT_QUEUE_INIT_HEAD(&pst_lock->wq);
	pst_lock->claimed = 0;
	pst_lock->claim_cnt = 0;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
