/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_schedule.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月29日
  最近修改   :
  功能描述   : 调度相关原语
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_schedule.h"

#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : oal_timer_init
 功能描述  : 初始化定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
}

/*****************************************************************************
 函 数 名  : oal_timer_delete
 功能描述  : 删除定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer)
{

    return 0;
}

/*****************************************************************************
 函 数 名  : oal_timer_delete_sync
 功能描述  : 同步删除定时器，用于多核
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer)
{

    return 0;
}

/*****************************************************************************
 函 数 名  : oal_timer_add
 功能描述  : 激活定时器
 输入参数  : pst_timer: 定时器结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_timer_add(oal_timer_list_stru *pst_timer)
{
}

/*****************************************************************************
 函 数 名  : oal_timer_start
 功能描述  : 重启定时器
 输入参数  : pst_timer: 结构体指针
             ui_expires: 重启的溢出事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_expires)
{

#ifdef  _PRE_WIFI_DMT
    DmtStub_StartTimer(MGMT_TIMER, ui_expires);  /*15ms 的定时任务，触发frw_timer_timeout_proc_event */
#endif

    return OAL_SUCC;
}

#endif

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
oal_void _oal_smp_task_lock_(oal_task_lock_stru* pst_lock,oal_ulong  claim_addr)
{
    DECLARE_WAITQUEUE(wait, current);

    oal_ulong flags;

    //might_sleep();/*called task must can sleep*/

    if(OAL_WARN_ON(in_interrupt() || in_atomic()))
    {
        DECLARE_DFT_TRACE_KEY_INFO("smp_task_lock_sched_warn", OAL_DFT_TRACE_EXCEP);
        return;
    }

    add_wait_queue(&pst_lock->wq, &wait);
    oal_spin_lock_irq_save(&pst_lock->lock, &flags);
    while (1) {
        set_current_state(TASK_UNINTERRUPTIBLE);
        if (!pst_lock->claimed || pst_lock->claimer == current)
            break;
        oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
        schedule();
        oal_spin_lock_irq_save(&pst_lock->lock, &flags);
    }
    set_current_state(TASK_RUNNING);

    pst_lock->claimed = 1;
    pst_lock->claimer = current;
    pst_lock->claim_cnt++;

    oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
    remove_wait_queue(&pst_lock->wq, &wait);
}
oal_module_symbol(_oal_smp_task_lock_);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

