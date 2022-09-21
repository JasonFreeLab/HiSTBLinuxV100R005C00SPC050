/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_timer.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年7月5日
  最近修改   :
  功能描述   : 定时器处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月5日
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
#include "frw_timer.h"
#include "frw_main.h"
#include "frw_task.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TIMER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oal_dlist_head_stru         g_ast_timer_list[WLAN_FRW_MAX_NUM_CORES];
oal_spin_lock_stru          g_ast_timer_list_spinlock[WLAN_FRW_MAX_NUM_CORES];
oal_timer_list_stru         g_st_timer;

#ifdef _PRE_DEBUG_MODE

oal_uint32                  g_ul_os_time = 0;
frw_timeout_track_stru      g_st_timeout_track[FRW_TIMEOUT_TRACK_NUM];
oal_uint8                   g_uc_timeout_track_idx = 0;
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
OAL_STATIC  oal_void __frw_timer_immediate_destroy_timer(oal_uint32 ul_file_id,
                                                                               oal_uint32 ul_line_num,
                                                                               frw_timeout_stru *pst_timeout);

/*****************************************************************************
 函 数 名  : frw_timer_init
 功能描述  : 初始化定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_init(oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
    oal_uint32 ul_core_id;

    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_dlist_init_head(&g_ast_timer_list[ul_core_id]);
        oal_spin_lock_init(&g_ast_timer_list_spinlock[ul_core_id]);
    }
    oal_timer_init(&g_st_timer, ul_delay, p_func, ui_arg);
#ifdef _PRE_FRW_TIMER_BIND_CPU
    oal_timer_start_on(&g_st_timer, FRW_TIMER_DEFAULT_TIME,0);
#else
    oal_timer_start(&g_st_timer, FRW_TIMER_DEFAULT_TIME);
#endif
#ifdef _PRE_DEBUG_MODE
    OAL_MEMZERO(g_st_timeout_track, OAL_SIZEOF(frw_timeout_track_stru) * FRW_TIMEOUT_TRACK_NUM);
#endif
}

/*****************************************************************************
 函 数 名  : frw_timer_exit
 功能描述  : 定时器退出函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_exit(oal_void)
{
    oal_timer_delete_sync(&g_st_timer);
}
/*****************************************************************************
 函 数 名  : frw_timer_dump
 功能描述  : 将所有定时器dump出来
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  frw_timer_dump(oal_uint32 ul_core_id)
{
    oal_dlist_head_stru   *pst_timeout_entry;
    frw_timeout_stru      *pst_timeout_element;

    pst_timeout_entry = g_ast_timer_list[ul_core_id].pst_next;
    while (pst_timeout_entry != &g_ast_timer_list[ul_core_id])
    {
        if(OAL_PTR_NULL == pst_timeout_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_dump:: time broken break}");
            break;
        }

        if(NULL == pst_timeout_entry->pst_next)
        {
            /*If next is null,
             the pst_timeout_entry stru maybe released or memset*/
            OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_dump:: pst_next is null,dump mem}");
            oal_print_hex_dump(((oal_uint8 *)pst_timeout_entry) - 64, 128, 32, "timer broken: ");
        }

        pst_timeout_element = OAL_DLIST_GET_ENTRY(pst_timeout_entry, frw_timeout_stru, st_entry);
        pst_timeout_entry = pst_timeout_entry->pst_next;
        OAM_ERROR_LOG4(0, OAM_SF_FRW, "{frw_timer_dump:: time_stamp[0x%x] timeout[%d] deleting[%d] enabled[%d]}"
                                      , pst_timeout_element->ul_time_stamp
                                      , pst_timeout_element->ul_timeout
                                      , pst_timeout_element->en_is_deleting
                                      , pst_timeout_element->en_is_enabled);
        OAM_ERROR_LOG3(0, OAM_SF_FRW, "{frw_timer_dump:: module_id[%d] file_id[%d] line_num[%d]}"
                                      , pst_timeout_element->en_module_id
                                      , pst_timeout_element->ul_file_id
                                      , pst_timeout_element->ul_line_num);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef CONFIG_PRINTK
        if(pst_timeout_element->p_func)
            printk(KERN_ERR"frw_timer_dump func : %pF\n",pst_timeout_element->p_func);
#endif
#endif
    }
}


#if 0
/*****************************************************************************
 函 数 名  : frw_timer_check_list
 功能描述  : 遍历定时器链表，是否已经断链
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月1日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_timer_check_list(oal_void)
{
    oal_dlist_head_stru   *pst_timeout_entry;

    pst_timeout_entry = g_st_timer_list.pst_next;
    while (pst_timeout_entry != &g_st_timer_list)
    {
       if (OAL_PTR_NULL == pst_timeout_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_check_list:: the timer list is broken! }");
            return OAL_FAIL;
        }

        pst_timeout_entry = pst_timeout_entry->pst_next;
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : oal_timer_timeout_proc
 功能描述  : 遍历timer链表执行到期超时函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_timer_timeout_proc(frw_event_mem_stru *pst_timeout_event)
{
    oal_dlist_head_stru *pst_timeout_entry;
    frw_timeout_stru    *pst_timeout_element;
    oal_uint32           ul_present_time;
    oal_uint32           ul_end_time;
    oal_uint32           ul_runtime;
    oal_uint32           ul_core_id;
    oal_uint32           ul_runtime_func_start  = 0;
    oal_uint32           ul_runtime_func_end  = 0;
    oal_uint32           ul_endtime_func  = 0;

#ifdef _PRE_DEBUG_MODE
    oal_uint32           ul_sum_time    = 0;
    oal_uint32           ul_start_time  = 0;

    if (OAL_TRUE == g_en_event_track_switch)
    {
        OAL_MEMZERO(&g_st_timeout_track[g_uc_timeout_track_idx], OAL_SIZEOF(frw_timeout_track_stru));
    }
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timeout_event))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_timeout_proc:: pst_timeout_event is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    ul_core_id = OAL_GET_CORE_ID();

    /* 执行超时定时器 */
    oal_spin_lock_bh(&g_ast_timer_list_spinlock[ul_core_id]);
    pst_timeout_entry = g_ast_timer_list[ul_core_id].pst_next;

    while (pst_timeout_entry != &g_ast_timer_list[ul_core_id])
    {

        if (OAL_PTR_NULL == pst_timeout_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_timeout_proc:: the timer list is broken! }");
            frw_timer_dump(ul_core_id);
            OAL_BUG_ON(1);
            break;
        }

        pst_timeout_element = OAL_DLIST_GET_ENTRY(pst_timeout_entry, frw_timeout_stru, st_entry);

        /* 如果该定时器没有使能或者待删除，则直接看下一个 */
        if ((OAL_TRUE == pst_timeout_element->en_is_deleting)
         || (OAL_FALSE == pst_timeout_element->en_is_enabled))
        {
            pst_timeout_entry = pst_timeout_entry->pst_next;
            continue;
        }

        pst_timeout_element->ul_curr_time_stamp = ul_present_time;
        ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_timeout_element->ul_time_stamp, ul_present_time);

        /* 一个定时器超时处理函数中创建新的定时器，新定时器的pst_timeout_element->ul_time_stamp可能大于ul_present_time
           导致ul_runtime异常大，增加ul_runtime最大值保护判断 */
        if (ul_runtime >= pst_timeout_element->ul_timeout && ul_runtime < FRW_TIMER_MAX_TIMEOUT)
        {
            if (OAL_TRUE != pst_timeout_element->en_is_periodic)
            {
                //__frw_timer_immediate_destroy_timer(THIS_FILE_ID, __LINE__, pst_timeout_element);
                pst_timeout_element->en_is_deleting = OAL_TRUE;
            }
            else
            {
                pst_timeout_element->ul_time_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            }

#ifdef _PRE_DEBUG_MODE
            ul_start_time = oal_5115timer_get_10ns();
#endif
            ul_runtime_func_start = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            //add for debug 
            pst_timeout_element->en_is_running = OAL_TRUE;

            oal_spin_unlock_bh(&g_ast_timer_list_spinlock[ul_core_id]);
            pst_timeout_element->p_func(pst_timeout_element->p_timeout_arg);
            oal_spin_lock_bh(&g_ast_timer_list_spinlock[ul_core_id]);

            pst_timeout_element->en_is_running = OAL_FALSE;

            ul_endtime_func = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            ul_runtime_func_end = (oal_uint32)OAL_TIME_GET_RUNTIME(ul_runtime_func_start, ul_endtime_func);
            if((oal_uint32)OAL_JIFFIES_TO_MSECS(2) <= ul_runtime_func_end)
            {
                OAM_WARNING_LOG4(0, OAM_SF_FRW, "{frw_timer_timeout_proc:: fileid=%u, linenum=%u, moduleid=%u, runtime=%u}",
                pst_timeout_element->ul_file_id,
                pst_timeout_element->ul_line_num,
                pst_timeout_element->en_module_id,
                ul_runtime_func_end);
            }

#ifdef _PRE_DEBUG_MODE

            if (OAL_TRUE == g_en_event_track_switch)
            {
                g_st_timeout_track[g_uc_timeout_track_idx].st_timer_track[g_st_timeout_track[g_uc_timeout_track_idx].uc_timer_cnt].ul_file_id = pst_timeout_element->ul_file_id;
                g_st_timeout_track[g_uc_timeout_track_idx].st_timer_track[g_st_timeout_track[g_uc_timeout_track_idx].uc_timer_cnt].ul_line_num = pst_timeout_element->ul_line_num;
                g_st_timeout_track[g_uc_timeout_track_idx].st_timer_track[g_st_timeout_track[g_uc_timeout_track_idx].uc_timer_cnt].ul_execute_time = ul_start_time - oal_5115timer_get_10ns();
                ul_sum_time += g_st_timeout_track[g_uc_timeout_track_idx].st_timer_track[g_st_timeout_track[g_uc_timeout_track_idx].uc_timer_cnt].ul_execute_time;
            }
#endif
        }
        else if((ul_runtime >= FRW_TIMER_MAX_TIMEOUT )&&(pst_timeout_element->ul_time_stamp < ul_present_time))
        {
            OAM_ERROR_LOG4(0, OAM_SF_FRW, "{timer running time abnormal: fileid=%u, linenum=%u, timestamp=%u, present timestamp=%u}",
                                                pst_timeout_element->ul_file_id,
                                                pst_timeout_element->ul_line_num,
                                                pst_timeout_element->ul_time_stamp,
                                                ul_present_time);

        }

#ifdef _PRE_DEBUG_MODE

        if (OAL_TRUE == g_en_event_track_switch)
        {
            OAL_INCR(g_st_timeout_track[g_uc_timeout_track_idx].uc_timer_cnt, FRW_TIMER_TRACK_NUM);
        }
#endif

        pst_timeout_entry = pst_timeout_entry->pst_next;

    }
    oal_spin_unlock_bh(&g_ast_timer_list_spinlock[ul_core_id]);

#ifdef _PRE_DEBUG_MODE
    if (OAL_TRUE == g_en_event_track_switch)
    {
        if ((ul_sum_time * 10) > 300000)
        {
            OAL_INCR(g_uc_timeout_track_idx, FRW_TIMEOUT_TRACK_NUM);
        }
    }
#endif

    /* 删除所有待删除定时器 */
    oal_spin_lock_bh(&g_ast_timer_list_spinlock[ul_core_id]);
    pst_timeout_entry = g_ast_timer_list[ul_core_id].pst_next;

    while (pst_timeout_entry != &g_ast_timer_list[ul_core_id])
    {

        if (OAL_PTR_NULL == pst_timeout_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_timeout_proc:: delete the timer list is broken! }");
            frw_timer_dump(ul_core_id);
            break;
        }

        pst_timeout_element = OAL_DLIST_GET_ENTRY(pst_timeout_entry, frw_timeout_stru, st_entry);

        pst_timeout_entry = pst_timeout_entry->pst_next;

        if (OAL_FALSE == pst_timeout_element->en_is_deleting)
        {
            continue;
        }

        __frw_timer_immediate_destroy_timer(pst_timeout_element->ul_file_id, pst_timeout_element->ul_line_num, pst_timeout_element);


    }
    oal_spin_unlock_bh(&g_ast_timer_list_spinlock[ul_core_id]);

    ul_end_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(ul_present_time, ul_end_time);
    /* 同device侧检测日志时限一致 */
    if (ul_runtime > (oal_uint32)OAL_JIFFIES_TO_MSECS(2))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_timer_timeout_proc:: timeout process exucte time too long time[%d]}", ul_runtime);
    }

    return OAL_SUCC;
}



/*****************************************************************************
 函 数 名  : frw_timer_add_timer
 功能描述  : 删除定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_add_timer(frw_timeout_stru *pst_timeout)
{
    if (OAL_PTR_NULL == pst_timeout)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_add_timer:: OAL_PTR_NULL == pst_timeout}");
        return;
    }

    oal_dlist_add_tail(&pst_timeout->st_entry, &g_ast_timer_list[pst_timeout->ul_core_id]);
}

/*****************************************************************************
 函 数 名  : frw_timer_create_timer
 功能描述  : 启动定时器
 输入参数  : en_is_periodic: 该定时器是否需要周期循环
             en_module_id: 模块 ID维测用
             p_timeout_arg :定时器超时处理函数需要的入参
             us_timeout: 超时时间
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_create_timer(
							oal_uint32 ul_file_id,
                            oal_uint32 ul_line_num,
                            frw_timeout_stru *pst_timeout,
                            frw_timeout_func  p_timeout_func,
                            oal_uint32 ul_timeout,
                            oal_void *p_timeout_arg,
                            oal_bool_enum_uint8  en_is_periodic,
                            oam_module_id_enum_uint16   en_module_id,
                            oal_uint32 ul_core_id)
{
    if (OAL_PTR_NULL == pst_timeout)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_create_timer:: OAL_PTR_NULL == pst_timeout}");
        return;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_timeout->ul_core_id     = 0;
#else
    pst_timeout->ul_core_id     = ul_core_id;
#endif

    oal_spin_lock_bh(&g_ast_timer_list_spinlock[pst_timeout->ul_core_id]);

    pst_timeout->p_func         = p_timeout_func;
    pst_timeout->p_timeout_arg  = p_timeout_arg;
    pst_timeout->ul_timeout     = ul_timeout;
    pst_timeout->ul_time_stamp  = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    pst_timeout->en_is_periodic = en_is_periodic;
    pst_timeout->en_module_id   = en_module_id;
    pst_timeout->ul_file_id     = ul_file_id;
    pst_timeout->ul_line_num    = ul_line_num;
    pst_timeout->en_is_enabled  = OAL_TRUE;       /* 默认使能 */
    pst_timeout->en_is_deleting = OAL_FALSE;


    if (OAL_TRUE != pst_timeout->en_is_registerd)
    {
        pst_timeout->en_is_running  = OAL_FALSE;
        pst_timeout->en_is_registerd= OAL_TRUE;       /* 默认使能 */
        frw_timer_add_timer(pst_timeout);
    }

    oal_spin_unlock_bh(&g_ast_timer_list_spinlock[pst_timeout->ul_core_id]);

    return;
}

/*****************************************************************************
 函 数 名  : frw_timer_destroy_timer
 功能描述  : 删除定时器(每15ms轮询删除)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_destroy_timer(oal_uint32 ul_file_id,
                                       oal_uint32 ul_line_num,
                                       frw_timeout_stru *pst_timeout)
{
    if (OAL_PTR_NULL == pst_timeout->st_entry.pst_prev || OAL_PTR_NULL == pst_timeout->st_entry.pst_next)
    {
        return;
    }

    if (OAL_FALSE == pst_timeout->en_is_registerd)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_timer_destroy_timer::This timer is not enabled it should not be deleted}");

        return;
    }

    pst_timeout->en_is_enabled   = OAL_FALSE;
    pst_timeout->en_is_deleting  = OAL_TRUE;

    // oam_report_timer_track(ul_file_id, ul_line_num, OAM_TIMER_TRACK_TYPE_DESTROY);
}

/*****************************************************************************
 函 数 名  : __frw_timer_immidate_destroy_timer
 功能描述  : 立即删除定时器，无锁
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  oal_void __frw_timer_immediate_destroy_timer(oal_uint32 ul_file_id,
                                                    oal_uint32 ul_line_num,
                                                    frw_timeout_stru *pst_timeout)
{
    if (OAL_PTR_NULL == pst_timeout->st_entry.pst_prev || OAL_PTR_NULL == pst_timeout->st_entry.pst_next)
    {
        return;
    }

    if (OAL_FALSE == pst_timeout->en_is_registerd)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_timer_immediate_destroy_timer::This timer is not enabled it should not be deleted}");

        return;
    }

    if(OAL_TRUE == pst_timeout->en_is_running)
    {
        OAM_WARNING_LOG2(0, OAM_SF_FRW, "{This timer is running when deleting,delay to delete it. file id[%d],line[%d]}",ul_file_id,ul_line_num);
        frw_timer_destroy_timer(ul_file_id,ul_line_num,pst_timeout);
        return;
    }

    pst_timeout->en_is_enabled   = OAL_FALSE;
    pst_timeout->en_is_registerd = OAL_FALSE;
    pst_timeout->en_is_deleting  = OAL_FALSE;

    oal_dlist_delete_entry(&pst_timeout->st_entry);
}


/*****************************************************************************
 函 数 名  : frw_timer_immidate_destroy_timer
 功能描述  : 立即删除定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月24日
    作    者   : 
    修改内容   : 加锁处理

*****************************************************************************/
oal_void  frw_timer_immediate_destroy_timer(oal_uint32 ul_file_id,
                                                    oal_uint32 ul_line_num,
                                                    frw_timeout_stru *pst_timeout)
{
    oal_spin_lock_bh(&g_ast_timer_list_spinlock[pst_timeout->ul_core_id]);
    __frw_timer_immediate_destroy_timer(ul_file_id, ul_line_num, pst_timeout);
    oal_spin_unlock_bh(&g_ast_timer_list_spinlock[pst_timeout->ul_core_id]);
}

/*****************************************************************************
 函 数 名  : frw_timer_restart_timer
 功能描述  : 重启定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_restart_timer(frw_timeout_stru *pst_timeout, oal_uint32 ul_timeout, oal_bool_enum_uint8  en_is_periodic)
{
    if (OAL_PTR_NULL == pst_timeout)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_restart_timer:: OAL_PTR_NULL == pst_timeout}");
        return;
    }


    pst_timeout->ul_time_stamp      = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    pst_timeout->ul_timeout         = ul_timeout;
    pst_timeout->en_is_periodic     = en_is_periodic;
    pst_timeout->en_is_enabled      = OAL_TRUE;
    pst_timeout->en_is_deleting     = OAL_FALSE;
}


/*****************************************************************************
 函 数 名  : frw_timer_stop_timer
 功能描述  : 停止定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_stop_timer(frw_timeout_stru *pst_timeout)
{
    if (OAL_PTR_NULL == pst_timeout)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_stop_timer:: OAL_PTR_NULL == pst_timeout}");
        return;
    }

    pst_timeout->en_is_enabled = OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_board_timer0_timeout_proc
 功能描述  : 15毫秒定时中断处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 g_uc_timer_pause = OAL_FALSE;
#if defined(_PRE_FRW_TIMER_BIND_CPU) && defined(CONFIG_NR_CPUS)
oal_uint32 g_ul_frw_timer_cpu_count[CONFIG_NR_CPUS] = {0};
#endif

oal_void  frw_timer_timeout_proc_event(oal_uint ui_arg)
{
    frw_event_mem_stru *pst_event_mem;
    frw_event_stru     *pst_event;
    oal_uint32          ul_core_id = 0;
    oal_uint8           uc_vap_id = 0;

#ifdef _PRE_DEBUG_MODE
    oal_uint32          ul_time = 0;

    if (OAL_TRUE == g_en_event_track_switch)
    {
        if (0 == g_ul_os_time)
        {
            g_ul_os_time = oal_5115timer_get_10ns();
        }
        else
        {
            ul_time = oal_5115timer_get_10ns();
            g_st_timeout_track[g_uc_timeout_track_idx].ul_os_timer_interval = g_ul_os_time - ul_time;
            g_ul_os_time = ul_time;
        }
    }
#endif

#if defined(_PRE_FRW_TIMER_BIND_CPU) && defined(CONFIG_NR_CPUS)
    do{
        oal_uint32 cpu_id = smp_processor_id();
        if(cpu_id < CONFIG_NR_CPUS)
        {
            g_ul_frw_timer_cpu_count[cpu_id]++;
        }
    }while(0);
#endif

    if(OAL_TRUE == g_uc_timer_pause)
    {
       return;
    }

/*lint -e539*//*lint -e830*/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if(frw_task_get_state(ul_core_id))
        {
#endif
            /* 如果定时器事件队列中，有未处理完的事件，不再抛；深度为2 */
            if(OAL_FALSE == frw_is_vap_event_queue_empty(ul_core_id, uc_vap_id, FRW_EVENT_TYPE_TIMEOUT))
            {
                /* 重启定时器 */
#ifdef _PRE_FRW_TIMER_BIND_CPU
                oal_timer_start_on(&g_st_timer, FRW_TIMER_DEFAULT_TIME, 0);
#else
                oal_timer_start(&g_st_timer, FRW_TIMER_DEFAULT_TIME);
#endif
                return ;
            }

            pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(frw_event_stru));
            /* 返回值检查 */
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
            {
                /* 重启定时器 */
#ifdef _PRE_FRW_TIMER_BIND_CPU
                oal_timer_start_on(&g_st_timer, FRW_TIMER_DEFAULT_TIME,0);
#else
                oal_timer_start(&g_st_timer, FRW_TIMER_DEFAULT_TIME);
#endif
                OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_timer_timeout_proc_event:: FRW_EVENT_ALLOC failed!}");
                return;
            }

            pst_event = (frw_event_stru *)pst_event_mem->puc_data;

            /* 填充事件头 */
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), en_type, (FRW_EVENT_TYPE_TIMEOUT));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), uc_sub_type, (FRW_TIMEOUT_TIMER_EVENT));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), us_length, (WLAN_MEM_EVENT_SIZE1));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), en_pipeline, (FRW_EVENT_PIPELINE_STAGE_0));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), uc_chip_id, (0));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), uc_device_id, (0));
            FRW_FIELD_SETUP((&pst_event->st_event_hdr), uc_vap_id, (0));

            /* 抛事件 */
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
            frw_event_post_event(pst_event_mem, ul_core_id);
#else
            frw_event_dispatch_event(pst_event_mem);
#endif
            FRW_EVENT_FREE(pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
        }
    }
#endif
/*lint +e539*//*lint +e830*/
    /* 重启定时器 */
#ifdef _PRE_FRW_TIMER_BIND_CPU
    oal_timer_start_on(&g_st_timer, FRW_TIMER_DEFAULT_TIME, 0);
#else
    oal_timer_start(&g_st_timer, FRW_TIMER_DEFAULT_TIME);
#endif
}


/*****************************************************************************
 函 数 名  : frw_timer_delete_all_timer
 功能描述  : 将定时器链表中的所有定时器删除，用于异常时外部模块清理定时器
             不能在定时器回调函数中调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void  frw_timer_delete_all_timer(oal_void)
{

    oal_dlist_head_stru *pst_timeout_entry;
    frw_timeout_stru    *pst_timeout_element;

    oal_uint32           ul_core_id;

    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_spin_lock_bh(&g_ast_timer_list_spinlock[ul_core_id]);
        /* 删除所有待删除定时器 */
        pst_timeout_entry = g_ast_timer_list[ul_core_id].pst_next;

        while (pst_timeout_entry != &g_ast_timer_list[ul_core_id])
        {
            pst_timeout_element = OAL_DLIST_GET_ENTRY(pst_timeout_entry, frw_timeout_stru, st_entry);

            pst_timeout_entry = pst_timeout_entry->pst_next;

            /* 删除定时器 */
            oal_dlist_delete_entry(&pst_timeout_element->st_entry);
#if 0
            if (oal_dlist_is_empty(&g_st_timer_list))
            {
                oal_timer_delete_sync(&g_st_timer);
            }
#endif
        }
        oal_spin_unlock_bh(&g_ast_timer_list_spinlock[ul_core_id]);
    }

}

/*****************************************************************************
 函 数 名  : frw_timer_dump_timer
 功能描述  : 打印所有timer的维测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_timer_dump_timer(oal_uint32 ul_core_id)
{
    oal_dlist_head_stru *pst_dlist_entry;
    frw_timeout_stru    *pst_timer;
    oal_uint32           ul_cnt = 0;

    OAM_WARNING_LOG0(0, OAM_SF_ANY, "frw_timer_dump_timer::timer dump start.");
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_entry, &g_ast_timer_list[ul_core_id])
    {
        pst_timer = OAL_DLIST_GET_ENTRY(pst_dlist_entry, frw_timeout_stru, st_entry);

        OAM_WARNING_LOG4(0, OAM_SF_ANY, "TIMER NO.%d, file id[%d], line num[%d], func addr[0x%08x]",
                        ul_cnt, pst_timer->ul_file_id, pst_timer->ul_line_num, pst_timer->p_func);
        OAM_WARNING_LOG4(0, OAM_SF_ANY, "tiemr enabled[%d], running[%d], registerd[%d], deleting[%d]",
                        pst_timer->en_is_enabled, pst_timer->en_is_running, pst_timer->en_is_registerd, pst_timer->en_is_deleting);
        OAM_WARNING_LOG4(0, OAM_SF_ANY, "timerout[%u], start timer stamp[%u], curr timer stamp[%u], period[%d]",
                        pst_timer->ul_timeout, pst_timer->ul_time_stamp, pst_timer->ul_curr_time_stamp, pst_timer->en_is_periodic);
        ul_cnt++;
    }
    OAM_WARNING_LOG0(0, OAM_SF_ANY, "frw_timer_dump_timer::timer dump end.");
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(frw_timer_restart_timer);
oal_module_symbol(frw_timer_destroy_timer);
oal_module_symbol(frw_timer_create_timer);
oal_module_symbol(frw_timer_dump_timer);
oal_module_symbol(frw_timer_stop_timer);
oal_module_symbol(frw_timer_add_timer);
oal_module_symbol(frw_timer_immediate_destroy_timer);
oal_module_symbol(frw_timer_delete_all_timer);
oal_module_symbol(frw_timer_exit);

oal_module_symbol(g_uc_timer_pause);

#ifdef _PRE_DEBUG_MODE
oal_module_symbol(g_st_timeout_track);
oal_module_symbol(g_uc_timeout_track_idx);
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

