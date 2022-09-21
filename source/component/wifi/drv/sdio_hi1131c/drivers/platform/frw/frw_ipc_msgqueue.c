/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_ipc_msgqueue.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月16日
  最近修改   :
  功能描述   : IPC模块消息队列相关处理，依赖
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月16日
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
#include "frw_main.h"
#include "frw_ipc_msgqueue.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_IPC_MSGQUEUE_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OAL_STATIC frw_ipc_msg_callback_stru gst_ipc_msg_callback;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : frw_ipc_msg_queue_init
 功能描述  : 消息队列初始化，内存分配
 输入参数  : pst_msg_queue: 消息队列结构体指针
             ul_queue_len: 消息队列长度
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；
             入参检测为空指针: OAL_ERR_CODE_PTR_NULL
             内存分配失败: OAL_ERR_CODE_ALLOC_MEM_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_init(frw_ipc_msg_queue_stru *pst_msg_queue, oal_uint32 ul_queue_len)
{
    oal_uint16 us_queue_size = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_init:: pst_msg_queue is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 为发送消息队列分配内存 */
    us_queue_size               = (oal_uint16)(OAL_SIZEOF(frw_ipc_msg_dscr_stru) * ul_queue_len);
    pst_msg_queue->pst_dscr     = (frw_ipc_msg_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, us_queue_size, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_queue->pst_dscr))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_init:: pst_msg_queue->pst_dscr is null ptr!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 结构体变量初始化 */
    pst_msg_queue->ul_head      = 0;
    pst_msg_queue->ul_tail      = 0;
    pst_msg_queue->ul_max_num  = ul_queue_len;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_msg_queue_destroy
 功能描述  : 释放消息队列内存空间
 输入参数  : pst_msg_queue: 消息队列结构体指针
 输出参数  : 无
 返 回 值  : 成功OAL_SUCC
             入参检测为空指针: OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_destroy(frw_ipc_msg_queue_stru *pst_msg_queue)
{
    /* 入参检查 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_queue))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_msg_queue->pst_dscr)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_destroy:: pst_msg_queue->pst_dscr is null ptr}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_FREE(pst_msg_queue->pst_dscr, OAL_TRUE);

    pst_msg_queue->pst_dscr = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_msg_queue_recv
 功能描述  : 消息接收函数。当核间发生接收中断时，会调用核间中断处理函数进行
             中断处理，中断处理函数则会调用ipc_msg_queue_recv接收消息。该函
             数工作在中断上下文。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功OAL_SUCC
             失败返回回调函数的错误信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_recv(oal_void *p_arg)
{
    frw_ipc_msg_queue_stru  *pst_ipc_rx_msg_queue;
    oal_uint32              ul_head             = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_recv:: p_arg is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ipc_rx_msg_queue = (frw_ipc_msg_queue_stru *)(((oal_irq_dev_stru *)p_arg)->p_drv_arg);
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_ipc_msg_callback.p_rx_complete_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_recv:: gst_ipc_msg_callback.p_rx_complete_func is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 队列操作 */
    do
    {
        ul_head = (pst_ipc_rx_msg_queue->ul_head);
        FRW_IPC_RING_RX_INCR(pst_ipc_rx_msg_queue->ul_head);

        /* 回调ipc_recv() */
        gst_ipc_msg_callback.p_rx_complete_func(pst_ipc_rx_msg_queue->pst_dscr[ul_head].pst_msg_mem);

    }while (!FRW_IPC_RING_EMPTY(pst_ipc_rx_msg_queue->ul_head, pst_ipc_rx_msg_queue->ul_tail));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_msg_queue_send(ipc_node *node, oal_netbuf_t *buf);
 功能描述  : 核间消息发送操作。
 输入参数  : pst_ipc_tx_msg_queue: 发送消息队列结构体指针
             pst_msg_input: 核间通讯消息地址
             uc_flags: 是否可以起中断的标志
             uc_cpuid: 发送目标核ID
 输出参数  : 队列满: OAL_FAIL
             成功: OAL_SUCC
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_send(frw_ipc_msg_queue_stru *pst_ipc_tx_msg_queue, frw_ipc_msg_mem_stru *pst_msg_input, oal_uint8 uc_flags, oal_uint8 uc_cpuid)
{
    oal_uint32  ul_tail = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_ipc_tx_msg_queue) || OAL_PTR_NULL == pst_msg_input))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_ipc_msg_queue_send: pst_ipc_tx_msg_queue/pst_msg_input is null ptr: %d %d}", pst_ipc_tx_msg_queue, pst_msg_input);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD 锁 */

    /* 判断队列是否满 */
    if (OAL_UNLIKELY(FRW_IPC_RING_FULL(pst_ipc_tx_msg_queue->ul_head,
                      pst_ipc_tx_msg_queue->ul_tail,
                      pst_ipc_tx_msg_queue->ul_max_num)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_send:: FRW_IPC_RING_FULL OAL_ERR_CODE_IPC_QUEUE_FULL.}");
        return OAL_ERR_CODE_IPC_QUEUE_FULL;
    }

    ul_tail = pst_ipc_tx_msg_queue->ul_tail;
    FRW_IPC_RING_TX_INCR(pst_ipc_tx_msg_queue->ul_tail);

    pst_ipc_tx_msg_queue->pst_dscr[ul_tail].pst_msg_mem = pst_msg_input;

    /* 目标核如果为空闲则启动目标核硬件中断 */
    if (FRW_IPC_TX_CTRL_ENABLED == uc_flags)
    {
        oal_irq_trigger(uc_cpuid);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_msg_handler_register
 功能描述  : 函数钩子注册
 输入参数  : p_ipc_msg_handler: 函数钩子结构体指针
 输出参数  : 无
 返 回 值  : 成功OAL_SUCC
             入参检测为空指针: OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_register_callback(frw_ipc_msg_callback_stru *p_ipc_msg_handler)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_ipc_msg_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_register_callback:: p_ipc_msg_handler is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    gst_ipc_msg_callback.p_rx_complete_func = p_ipc_msg_handler->p_rx_complete_func;
    gst_ipc_msg_callback.p_tx_complete_func = p_ipc_msg_handler->p_tx_complete_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_exit
 功能描述  : 维测模块退出
 输入参数  : pst_log: 维测信息结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_exit(frw_ipc_log_stru *pst_log)
{
    /* TBD */
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_init
 功能描述  : 维测模块初始化
 输入参数  : pst_log: 维测信息结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_init(frw_ipc_log_stru *pst_log)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_init:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD */
    pst_log->ul_stats_assert        = 0;
    pst_log->ul_stats_send_lost     = 0;
    pst_log->ul_stats_recv_lost     = 0;
    pst_log->ul_stats_recv          = 0;
    pst_log->ul_stats_send          = 0;
    pst_log->ul_tx_index            = 0;
    pst_log->ul_rx_index            = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_alarm
 功能描述  : 核间通信接收丢包告警
 输入参数  : pst_log: 维测信息结构体指针
             ul_lost: 丢包次数
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_recv_alarm(frw_ipc_log_stru *pst_log, oal_uint32 ul_lost)
{
    oal_int32 l_lost, l_assert = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_recv_alarm:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_log->ul_stats_recv_lost += ul_lost;    /* 丢包数更新 */
    pst_log->ul_stats_assert++;              /* 告警次数更新 */

    l_lost      = (oal_int32)pst_log->ul_stats_recv_lost;
    l_assert    = (oal_int32)pst_log->ul_stats_assert;

    FRW_IPC_LOST_WARNING_LOG2(0, "The number of rx lost package respectively are ", l_lost, l_assert);
    OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_log_recv_alarm::The number of rx lost package respectively are  %d %d}", l_lost, l_assert);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_send_alarm
 功能描述  : 核间通信发送丢包告警
 输入参数  : pst_log: 维测信息结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_send_alarm(frw_ipc_log_stru *pst_log)
{
    oal_int32 l_lost;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_send_alarm:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_log->ul_stats_send_lost++;
    pst_log->ul_stats_assert++;         /* 告警次数更新 */

    l_lost = (oal_int32)pst_log->ul_stats_send_lost;

    FRW_IPC_LOST_WARNING_LOG1(0, "The number of tx lost package respectively are ", l_lost);
    OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_log_send_alarm::the number of tx lost packets are %d. }\r\n", l_lost);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_send
 功能描述  : 统计发送信息
 输入参数  : pst_log: 维测信息结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_send(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_send:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAX_LOG_RECORD != pst_log->ul_tx_index)
    {
        pst_log->ul_stats_send++;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].us_seq_num      = us_seq_num;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].uc_target_cpuid = uc_target_cpuid;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].uc_msg_type     = uc_msg_type;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].l_time_stamp    = OAL_TIME_GET_STAMP_MS();
        pst_log->ul_tx_index++;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_recv
 功能描述  : 统计接收信息
 输入参数  : pst_log: 维测信息结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_recv(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_recv:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAX_LOG_RECORD != pst_log->ul_rx_index)
    {
        pst_log->ul_stats_recv++;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].us_seq_num      = us_seq_num;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].uc_target_cpuid = uc_target_cpuid;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].uc_msg_type     = uc_msg_type;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].l_time_stamp    = OAL_TIME_GET_STAMP_MS();
        pst_log->ul_rx_index++;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_print
 功能描述  : 将记录在发送日志数组中的日志打印
 输入参数  : pst_log: 日志信息结构体
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_tx_print(frw_ipc_log_stru *pst_log)
{
    oal_uint16 us_log_index = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_tx_print:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (us_log_index = 0; us_log_index < pst_log->ul_tx_index; us_log_index++)
    {
        FRW_IPC_LOG_INFO_PRINT4(0, "SEND SEQUENCE NUMBER:  TARGET CPUID:  MESSAGE TYPE: TIME STAMP: ",
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].us_seq_num,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].uc_target_cpuid,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].uc_msg_type,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].l_time_stamp);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_log_rx_print
 功能描述  : 将记录在接收日志数组中的日志信息打印
 输入参数  : pst_log: 日志信息结构体
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_log_rx_print(frw_ipc_log_stru *pst_log)
{
    oal_uint16 us_log_index = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_rx_print:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    FRW_IPC_LOG_INFO_PRINT1(0, "times of recieve:", (oal_int32)pst_log->ul_stats_recv);

    for (us_log_index = 0; us_log_index < pst_log->ul_rx_index; us_log_index++)
    {
        FRW_IPC_LOG_INFO_PRINT4(0, "RECEIVE SEQUENCE NUMBER: TARGET CPUID: MESSAGE TYPE:  TIME STAMP:",
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].us_seq_num,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].uc_target_cpuid,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].uc_msg_type,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].l_time_stamp);
    }

    return OAL_SUCC;
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

