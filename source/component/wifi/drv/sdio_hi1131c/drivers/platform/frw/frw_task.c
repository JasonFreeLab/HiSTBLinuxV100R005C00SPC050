/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_task.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2012年10月22日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月22日
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
#include "platform_spec.h"
#include "frw_main.h"
#include "frw_event_main.h"
#include "frw_task.h"
#include "hal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TASK_C

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#define FRW_TASK_PRIO       (1)
#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#define FRW_TASK_PRIO       (10)
#endif
#define FRW_TASK_SIZE        (0x2000)

#define FRW_THREAD_NAME_MAX_SIZE    (20)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oal_int8 g_frw_thread_name[WLAN_FRW_MAX_NUM_CORES][FRW_THREAD_NAME_MAX_SIZE]={"0"};
/******************************************************************************
    事件处理全局变量
*******************************************************************************/
frw_task_stru g_ast_event_task[WLAN_FRW_MAX_NUM_CORES];

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)

/*****************************************************************************
 函 数 名  : frw_task_thread
 功能描述  : frw 内核线程主程序
 输入参数  : 核id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32 frw_task_thread(oal_void* ul_bind_cpu)
{
    oal_int32       ret = 0;
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
    oal_uint32 ul_empty_count = 0;
#endif
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    allow_signal(SIGTERM);
#endif
    for (;;)
    {
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        oal_uint32 ul_event_count;
#endif
        if (oal_kthread_should_stop())
        {
            break;
        }

        /*state为TASK_INTERRUPTIBLE，condition不成立则线程阻塞，直到被唤醒进入waitqueue*/
        /*lint -e730*/
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, (oal_uint32)(oal_ulong)ul_bind_cpu);
#endif
        ret = OAL_WAIT_EVENT_INTERRUPTIBLE(g_ast_event_task[(oal_uint)ul_bind_cpu].frw_wq,  OAL_TRUE == frw_task_thread_condition_check((oal_uint)ul_bind_cpu));
        /*lint +e730*/
        if(OAL_UNLIKELY(-ERESTARTSYS == ret))
        {
            OAL_IO_PRINT("wifi task %s was interrupted by a signal\n", oal_get_current_task_name());
            break;
        }
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_loop_cnt++;

        ul_event_count = g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_event_cnt;
#endif
        frw_event_process_all_event((oal_uint)ul_bind_cpu);
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        if(ul_event_count == g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_event_cnt)
        {
            /*空转*/
            ul_empty_count++;
            if(ul_empty_count == 10000)
            {
                DECLARE_DFT_TRACE_KEY_INFO("frw_sched_too_much", OAL_DFT_TRACE_EXCEP);
            }
        }
        else
        {
            if(ul_empty_count > g_ast_event_task[(oal_uint)ul_bind_cpu].ul_max_empty_count)
            {
                g_ast_event_task[(oal_uint)ul_bind_cpu].ul_max_empty_count = ul_empty_count;
            }
            ul_empty_count = 0;
        }
#endif
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, (oal_uint32)(oal_ulong)ul_bind_cpu);
#endif
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : frw_task_init_kthread
 功能描述  : kthread初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_task_init(oal_void)
{
    oal_uint       ul_core_id;
    oal_kthread_stru   *pst_kthread;
    oal_kthread_param_stru st_thread_param = {0};
    
    OAL_MEMZERO(g_ast_event_task, OAL_SIZEOF(g_ast_event_task));
    
    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        OAL_WAIT_QUEUE_INIT_HEAD(&g_ast_event_task[ul_core_id].frw_wq);

        OAL_MEMZERO(&st_thread_param, OAL_SIZEOF(oal_kthread_param_stru));
        st_thread_param.l_cpuid      = ul_core_id;
        st_thread_param.l_policy     = OAL_SCHED_FIFO;
        st_thread_param.l_prio       = FRW_TASK_PRIO;
        st_thread_param.ul_stacksize = FRW_TASK_SIZE;

        OAL_MEMZERO(g_frw_thread_name[ul_core_id], FRW_THREAD_NAME_MAX_SIZE);
        OAL_SPRINTF(g_frw_thread_name[ul_core_id], FRW_THREAD_NAME_MAX_SIZE, "hisi_frw%lu", ul_core_id);
        pst_kthread = oal_kthread_create(g_frw_thread_name[ul_core_id], frw_task_thread, (oal_void*)ul_core_id,&st_thread_param);
        if (IS_ERR_OR_NULL(pst_kthread)) {
            return OAL_FAIL;
        }
        
        g_ast_event_task[ul_core_id].pst_event_kthread = pst_kthread;
        g_ast_event_task[ul_core_id].uc_task_state     = FRW_TASK_STATE_IRQ_UNBIND;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_thread_exit
 功能描述  : 线程退出函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_exit(oal_void)
{
    oal_uint32       ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if (g_ast_event_task[ul_core_id].pst_event_kthread)
        {
            oal_kthread_stop(g_ast_event_task[ul_core_id].pst_event_kthread);
            g_ast_event_task[ul_core_id].pst_event_kthread = OAL_PTR_NULL;
        }
    }
}

/*****************************************************************************
 函 数 名  : frw_task_event_handler_register
 功能描述  : 供外部模块注册tasklet处理函数中执行的函数
 输入参数  : p_func: 需要被执行的函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint))
{

}

/*****************************************************************************
 函 数 名  : frw_task_sched
 功能描述  : 唤醒event时间处理线程，与wake_event_interruptible对应
 输入参数  : ul_core_id: 核id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_sched(oal_uint32 ul_core_id)
{
    OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&g_ast_event_task[ul_core_id].frw_wq);
}

/*****************************************************************************
 函 数 名  : frw_task_set_state
 功能描述  : 设置内核线程的绑定状态
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state)
{
    g_ast_event_task[ul_core_id].uc_task_state = uc_task_state;
}
/*****************************************************************************
 函 数 名  : frw_task_get_state
 功能描述  : 获取内核线程的绑定状态
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 frw_task_get_state(oal_uint32 ul_core_id)
{
    return g_ast_event_task[ul_core_id].uc_task_state;
}

#elif (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_TASKLET)

/*****************************************************************************
 函 数 名  : frw_task_init
 功能描述  : tasklet初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_task_init(oal_void)
{
    oal_uint32 ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_task_init(&g_ast_event_task[ul_core_id].st_event_tasklet, g_ast_event_task[ul_core_id].p_event_handler_func, 0);
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_task_exit
 功能描述  : task 退出函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月29日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_exit(oal_void)
{
    oal_uint32       ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_task_kill(&g_ast_event_task[ul_core_id].st_event_tasklet);
    }
}

/*****************************************************************************
 函 数 名  : frw_task_event_handler_register
 功能描述  : 供外部模块注册tasklet处理函数中执行的函数
 输入参数  : p_func: 需要被执行的函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint))
{
    oal_uint32 ul_core_id;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_task_event_handler_register:: p_func is null ptr}");
        return;
    }

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        g_ast_event_task[ul_core_id].p_event_handler_func = p_func;
    }
}

/*****************************************************************************
 函 数 名  : frw_remote_task_receive
 功能描述  : 将tasklet调度执行，被IPI中断调度执行
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void frw_remote_task_receive(void *info)
{
    oal_tasklet_stru *pst_task = (oal_tasklet_stru *)info;
    oal_task_sched(pst_task);
}

/*****************************************************************************
 函 数 名  : frw_task_sched_on_cpu
 功能描述  : 使用IPI中断，调度目标core上的tasklet执行处理事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void frw_task_sched_on_cpu(oal_tasklet_stru *pst_task, oal_uint32 ul_core_id)
{
    oal_smp_call_function_single(ul_core_id, frw_remote_task_receive, (void *)pst_task, 0);
}

/*****************************************************************************
 函 数 名  : frw_task_sched
 功能描述  : task调度接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_sched(oal_uint32 ul_core_id)
{
    oal_uint32 ul_this_cpu = OAL_GET_CORE_ID();

    if (oal_task_is_scheduled(&g_ast_event_task[ul_core_id].st_event_tasklet))
    {
        return;
    }

    if (ul_this_cpu == ul_core_id)
    {
        oal_task_sched(&g_ast_event_task[ul_core_id].st_event_tasklet);
    }
    else
    {
        frw_task_sched_on_cpu(&g_ast_event_task[ul_core_id].st_event_tasklet, ul_core_id);
    }
}

/*****************************************************************************
 函 数 名  : frw_task_set_state
 功能描述  : 设置tasklet的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state)
{
}

/*****************************************************************************
 函 数 名  : frw_task_get_state
 功能描述  : 获取tasklet的状态，tasklet一直与核绑定
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 frw_task_get_state(oal_uint32 ul_core_id)
{
    return FRW_TASK_STATE_IRQ_BIND;
}

#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(frw_task_set_state);
oal_module_symbol(frw_task_get_state);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

