/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_thread.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年1月29日
  最近修改   :
  功能描述   : oal_thread.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月13日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LITEOS_THREAD_H__
#define __OAL_LITEOS_THREAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <los_task.h>

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/

typedef  LOS_TASK_CB oal_kthread_stru; 

typedef struct _kthread_param_{
    oal_uint32         ul_stacksize;
    oal_int32           l_prio;
    oal_int32           l_policy;
    oal_int32           l_cpuid;
    oal_int32           l_nice;
}oal_kthread_param_stru;

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#define OAL_CURRENT     oal_get_current()

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 宏定义
*****************************************************************************/
#define OAL_SCHED_FIFO      (1)
#define OAL_SCHED_RR        (2)

#define NOT_BIND_CPU        (-1)

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
typedef int (*oal_thread_func)(void *);

/*****************************************************************************
  10 函数声明
*****************************************************************************/

OAL_STATIC OAL_INLINE oal_kthread_stru* oal_kthread_create(char                   *pc_thread_name,
                                                           oal_thread_func        pf_threadfn,
                                                           void                   *p_data,
                                                           oal_kthread_param_stru *pst_thread_param)
{
    oal_int32 uwRet;
    TSK_INIT_PARAM_S stSdTask;
    oal_uint32 ul_taskid;
    oal_kthread_stru *pst_kthread=NULL;

    memset(&stSdTask, 0, sizeof(TSK_INIT_PARAM_S));
    stSdTask.pfnTaskEntry  = (TSK_ENTRY_FUNC)pf_threadfn;
    stSdTask.auwArgs[0]    = (oal_int32)p_data;
    stSdTask.uwStackSize   = pst_thread_param->ul_stacksize;
    stSdTask.pcName        = pc_thread_name;    
    stSdTask.usTaskPrio    = (oal_uint16)pst_thread_param->l_prio;
    stSdTask.uwResved      = LOS_TASK_STATUS_DETACHED;
    
    uwRet = LOS_TaskCreate(&ul_taskid, &stSdTask);
    if (LOS_OK != uwRet)
    {
        dprintf("Failed to create %s thread\n",pc_thread_name);
        return NULL;
    }

    pst_kthread = (oal_kthread_stru *)&g_pstTaskCBArray[ul_taskid];
    return pst_kthread;
}


OAL_STATIC OAL_INLINE oal_void oal_kthread_stop(oal_kthread_stru *pst_kthread)
{
    if (OAL_UNLIKELY(pst_kthread == NULL))
    {
        dprintf("thread can't stop\n");
        return;
    }
    dprintf(">>>>>>>>>%s thread stop\n",pst_kthread->pcTaskName);
    LOS_TaskDelete(pst_kthread->uwTaskPID);
}

OAL_STATIC OAL_INLINE  oal_int32 oal_kthread_should_stop(oal_void)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_uint32 oal_set_thread_property(oal_kthread_stru        *pst_thread,
                                                         oal_kthread_param_stru  *pst_thread_param)
{
    return LOS_TaskPriSet(pst_thread->uwTaskPID,pst_thread_param->l_prio);
}

OAL_STATIC OAL_INLINE oal_kthread_stru *oal_get_current(oal_void)
{
    return g_stLosTask.pstRunTask;
}

OAL_INLINE static char* oal_get_current_task_name(oal_void)
{
      return g_stLosTask.pstRunTask->pcTaskName;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
