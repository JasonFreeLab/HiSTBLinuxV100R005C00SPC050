/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_event_deploy.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月16日
  最近修改   :
  功能描述   : 事件部署以及核间通信主模块，包括对外接口
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
#include "frw_event_deploy.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* ipc全局结构体:每个核一个,AMP情况下当前只考虑双核场景 */
OAL_STATIC frw_ipc_node_stru         g_st_ipc_node[FRW_IPC_CORE_TYPE_BUTT];

/* 主核发送给从核的消息队列 */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_master_to_slave;

/* 从核发送给主核的消息队列 */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_slave_to_master;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* IPC接口 */
OAL_STATIC oal_uint32  frw_ipc_init(oal_void);
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void);
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8 uc_msg_type, oal_uint8 *puc_data, oal_uint8 us_len);
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg);
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void);
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void);

/* 事件部署接口 */
OAL_STATIC oal_uint32  frw_event_deploy_pipeline(oal_mem_stru *pst_mem_event, frw_event_deploy_enum_uint8 *en_deploy_result);

/*****************************************************************************
 函 数 名  : frw_ipc_recv
 功能描述  : 消息接收处理，运行在中断上下文环境，不能加锁
 输入参数  : pst_ipc_mem_msg: 消息结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC: 成功; 其他: 失败
 调用函数  : 由接收中断处理回调
 被调函数  : IPC模块内部其他函数

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    frw_ipc_msg_header_stru     *pst_header;    /* 消息头部结构体 */
    frw_ipc_core_type_enum_uint8 en_type;       /* CPU类型: 主核或从核 */

    /* 入参检查 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_recv::OAL_PTR_NULL == pst_ipc_mem_msg}\r\n");
        return;
    }

    /* 获取信息头部, 在IPC发送时已经挪了puc_data指针，此处该指针已指向IPC头 */
    pst_header = (frw_ipc_msg_header_stru *)(pst_ipc_mem_msg->puc_data);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_header
        || pst_header->uc_target_cpuid > FRW_IPC_CORE_NUM_BUTT
        || pst_header->uc_msg_type > FRW_IPC_MSG_TYPE_BUTT))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{pst_header is incorrect.}");
        return;
    }

    /* 获取当前内核信息 */
    en_type = frw_ipc_get_core_type();

    /* 判断seq number是否正确 */
    if (OAL_LIKELY(g_st_ipc_node[en_type].us_seq_num_rx_expect == pst_header->us_seq_number))
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect++;  /* 该变量只有在这里读写 */
    }
    else if(g_st_ipc_node[en_type].us_seq_num_rx_expect < pst_header->us_seq_number)
    {
        /* 期望下次收到是匹配的 */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;

    #ifdef _PRE_DEBUG_MODE
        /* 日志，告警 */
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number - g_st_ipc_node[en_type].us_seq_num_rx_expect));
    #endif
    }
    else
    {
        /* 说明溢出且丢包了 */
        /* 期望下次收到是匹配的 */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;
    #ifdef _PRE_DEBUG_MODE
        /* 日志，告警，丢包计算公式: 当前序列号+序列号最大值-序列号期望值+1 */
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number + FRW_IPC_MAX_SEQ_NUMBER - g_st_ipc_node[en_type].us_seq_num_rx_expect + 1));
    #endif
    }

#ifdef _PRE_DEBUG_MODE
    /* 接收日志 */
    frw_ipc_log_recv(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    switch (pst_header->uc_msg_type)
    {
        case FRW_IPC_MSG_TYPE_EVENT:

            /* 在IPC发送时被偏移到IPC头部位置，所以这里需要再偏移到事件结构体位置 */
            pst_ipc_mem_msg->puc_data += FRW_IPC_MSG_HEADER_LENGTH;

            /* 事件直接入队操作 */
            frw_event_post_event(pst_ipc_mem_msg,OAL_GET_CORE_ID());

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_ENABLE:
            /* 修改发送状态控制标识，原子操作 */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_ENABLED;

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_DISENABLE:
            /* 修改发送状态控制标识，原子操作 */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_DISABLED;

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_REQUEST:
            /* 发送连接响应 */
            frw_ipc_send_connect_response();

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_RESPONSE:
            /* 修改状态，原子操作 */
            g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_CONNECTED;

            break;

        case FRW_IPC_MSG_TYPE_CONFIG_REQUEST:
        case FRW_IPC_MSG_TYPE_CONFIG_RESPONSE:
        case FRW_IPC_MSG_TYPE_ERROR_NOTICE:
        case FRW_IPC_MSG_TYPE_RESET_REQUEST:
        case FRW_IPC_MSG_TYPE_RESET_RESPONSE:
        case FRW_IPC_MSG_TYPE_OPEN_OAM:
        case FRW_IPC_MSG_TYPE_CLOSE_OAM:
        case FRW_IPC_MSG_TYPE_EXIT_REQUEST:
        case FRW_IPC_MSG_TYPE_EXIT_RESPONSE:
        default:

            break;
    }

    /* 释放消息 */
    FRW_EVENT_FREE(pst_ipc_mem_msg);
}

/*****************************************************************************
 函 数 名  : frw_ipc_send
 功能描述  : 对外接口, 发送核间消息, 消息内容为事件, 调用该函数后可以释放内存
 输入参数  : pst_ipc_mem_msg: 消息结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC: 成功; 其他: 失败
 调用函数  : 外部模块用来发送事件
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_header_stru     *pst_header;        /* 消息头部结构体 */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* 消息队列 */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU类型: 主核或从核 */

    /* 入参检查 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_send::OAL_PTR_NULL == pst_ipc_mem_msg}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取当前内核信息 */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* 检查当前IPC模块状态*/
    if (FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states)
    {
        OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_send::FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states. en_type:%d, en_states:%d}\r\n", en_type, g_st_ipc_node[en_type].en_states);
        return OAL_FAIL;
    }

    /* 获取IPC头部 */
    pst_header = (frw_ipc_msg_header_stru *)frw_ipc_get_header(pst_ipc_mem_msg);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_header))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_send:: pst_header is null ptr}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 核间消息头部填充 */
    pst_header->us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_header->uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_header->uc_msg_type     = FRW_IPC_MSG_TYPE_EVENT;

    /* 发送核间消息 */
    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_ipc_mem_msg,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_ERR_CODE_IPC_QUEUE_FULL == ul_ret))
    {
    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_send_alarm(&g_st_ipc_node[en_type].st_log);
    #endif
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code: %d}", OAL_ERR_CODE_IPC_QUEUE_FULL);
        return ul_ret;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* 更新序列号 */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    /* 更新事件结构体引用计数 */
    pst_ipc_mem_msg->uc_user_cnt++;

#ifdef _PRE_DEBUG_MODE
    /* 发送日志 */
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_tx_complete_handler
 功能描述  : 发送完成中断处理，非OFFLOAD情况下不用，OFFLOAD情况下需要用
 输入参数  : pst_msg:消息结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC: 成功; 其他: 失败
 调用函数  : 由发送完成中断处理回调
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg)
{
    /* TBD */
}

/*****************************************************************************
 函 数 名  : frw_ipc_init
 功能描述  : 对外接口，IPC模块初始化，OFFLOAD情况下主CPU侧由主核调用该函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : 外部负责初始化的模块
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init(oal_void)
{
    oal_uint32   ul_ret;

    if(FRW_IPC_CORE_TYPE_MASTER == frw_ipc_get_core_type())
    {
        ul_ret = frw_ipc_init_master(&g_st_ipc_node[FRW_IPC_CORE_TYPE_MASTER]);
    }
    else
    {
        ul_ret = frw_ipc_init_slave(&g_st_ipc_node[FRW_IPC_CORE_TYPE_SLAVE]);
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc init fail.}");
        return ul_ret;
    }

    /* 启动连接 */
    ul_ret = frw_ipc_send_connect_request();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc connect fail.}");
        return ul_ret;
    }

    /* 将以下函数注册到事件管理模块中 */
    frw_event_ipc_event_queue_full_register(frw_ipc_event_queue_full);
    frw_event_ipc_event_queue_empty_register(frw_ipc_event_queue_empty);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_init_master
 功能描述  : 主核IPC模块初始化，OFFLOAD情况下主CPU和WIFI都调用该函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : IPC初始化
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* 全局结构体初始化 */
    pst_ipc_node->en_cpuid             = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_SLAVE;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_MASTER;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* 主核完成消息队列初始化 */
    /* 发送队列初始化 */
    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_master_to_slave,
                                    FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_init g_st_queue_master_to_slave return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* 接收队列初始化 */
    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_slave_to_master,
                                    FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW,  "{frw_ipc_init_master:: frw_ipc_msg_queue_init g_st_queue_slave_to_master return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* 中断注册 */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_slave_to_master;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq:: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* 回调函数注册 */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* 日志初始化 */
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : frw_ipc_init_slave
 功能描述  : 从核IPC模块初始化: OFFLOAD情况下不需要用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : IPC初始化
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* 全局结构体初始化 */
    pst_ipc_node->en_cpuid             = (oal_uint8)OAL_GET_CORE_ID();
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_SLAVE;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* 中断注册 */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_master_to_slave;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* 回调函数注册 */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave:: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* 日志初始化 */
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : frw_ipc_exit
 功能描述  : 真正的释放资源
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－退出响应处理成功；其他－退出响应处理失败
 调用函数  : IPC内部函数
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void)
{
    oal_uint32 ul_ret;
    frw_ipc_core_type_enum_uint8  en_type;       /* CPU类型: 主核或从核 */

    /* 获取当前内核信息 */
    en_type = frw_ipc_get_core_type();

    /* 修改IPC模块状态 */
    g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_EXIT;

    /* 注销核间中断 */
    oal_irq_free(&g_st_ipc_node[en_type].st_irq_dev);

    /* 释放消息队列 */
    if (FRW_IPC_CORE_ID_MASTER == en_type) /* 主核 */
    {
        /* 发送队列注销 */
        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_master_to_slave);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_exit: frw_ipc_msg_queue_destroy g_st_queue_master_to_slave return err code:%d}", ul_ret);
            return ul_ret;
        }

        /* 接收队列注销 */
        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_slave_to_master);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "frw_ipc_exit:: frw_ipc_msg_queue_destroy g_st_queue_slave_to_master return err code:%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_DEBUG_MODE
    /* 打印日志信息 */
    frw_ipc_log_tx_print(&g_st_ipc_node[en_type].st_log);
    frw_ipc_log_rx_print(&g_st_ipc_node[en_type].st_log);

    /* 退出日志模块 */
    ul_ret = frw_ipc_log_exit(&g_st_ipc_node[en_type].st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_send_connect_request
 功能描述  : 采用异步方式进行连接，该函数只发送连接请求，
             在中断服务例程中接收处理连接响应，并改变IPC状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－发送连接请求成功；其他－发送连接请求失败
 调用函数  : IPC内部函数
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_REQUEST,
                                    OAL_PTR_NULL,
                                    0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_request: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_send_connect_response
 功能描述  : 运行在中断上下文，采用异步方式进行连接，该函数只发送连接响应，
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－发送连接请求成功；其他－发送连接请求失败
 调用函数  : IPC内部函数
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_RESPONSE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_response: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_inter_msg_send
 功能描述  : 发送核间通信内部消息
 输入参数  : uc_msg_type: 内部消息类型
             puc_data: 需要发送的数据
             us_len: 数据长度
 输出参数  : 无
 返 回 值  : OAL_SUCC－发送成功；OAL_FAIL－发送失败
 调用函数  : IPC内部函数
 被调函数  : 调用事件创建接口

 修改历史      :
  1.日    期   : 2012年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8  uc_msg_type,
                                                       oal_uint8 *puc_data,
                                                       oal_uint8  us_len)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_mem_stru        *pst_msg_mem_stru;  /* 消息内存块 */
    frw_ipc_inter_msg_stru      *pst_ipc_msg;       /* 消息结构体 */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* 消息队列 */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU类型: 主核或从核 */
    oal_uint8                    ul_length;

    /* 获取当前内核信息 */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* 申请核间内部消息内存 */
    ul_length = OAL_SIZEOF(frw_ipc_inter_msg_stru) - 4 + us_len;
    pst_msg_mem_stru = FRW_EVENT_ALLOC(ul_length);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_mem_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_send_inter_msg: FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 获取消息地址 */
    pst_ipc_msg = (frw_ipc_inter_msg_stru *)frw_ipc_get_header(pst_msg_mem_stru);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_msg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_send_inter_msg: pst_ipc_msg is null ptr.}");
        FRW_EVENT_FREE(pst_msg_mem_stru);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填充消息头 */
    pst_ipc_msg->st_ipc_hdr.us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_ipc_msg->st_ipc_hdr.uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_ipc_msg->st_ipc_hdr.uc_msg_type     = uc_msg_type;
    pst_ipc_msg->ul_length                  = us_len;

    /* 填充数据 */
    if (us_len > 0)
    {
        oal_memcopy((oal_void *)pst_ipc_msg->auc_data, (oal_void *)puc_data, us_len);
    }

    /* 发送内部消息 */
    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_msg_mem_stru,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{send inter msg fail.}");
        FRW_EVENT_FREE(pst_msg_mem_stru);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* 发送日志 */
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                      g_st_ipc_node[en_type].us_seq_num_tx_expect,
                      g_st_ipc_node[en_type].en_target_cpuid,
                      uc_msg_type);
#endif

    /* 更新序列号 */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_reset
 功能描述  : IPC模块复位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 

*****************************************************************************/
oal_uint32  frw_ipc_reset(oal_void)
{
    /* TBD */
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_pkt_dispatch
 功能描述  : 多核报文分发保序入口
 输入参数  : buf-网络帧结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : 注册挂接在报文接收入口处
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_smp_dispatch(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_pkt_ordering
 功能描述  : 报文保序处理
 输入参数  : buf-网络帧结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : 注册挂接在报文发送出口处
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_ipc_smp_ordering(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_event_queue_full
 功能描述  : 当事件调度模块发现队列高于某个阀值时，调用该接口通知对方内核
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : 事件调度模块
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_DISENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_full: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_ipc_event_queue_empty
 功能描述  : 当事件调度模块发现队列低于某个阀值时，调用该接口通知对方内核
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC－成功；其他－失败
 调用函数  : 事件调度模块
 被调函数  : 内部函数

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_ENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_empty: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_event_deploy_init
 功能描述  : 对外接口，事件部署模块初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_init(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_init();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy init fail.}");
        return ul_ret;
    }

    /* TBD */

    /* 事件部署模块数据结构初始化 */

    /* 各种级别的事件部署按照均衡部署方式进行初始化 */

    /* 引入宏, 如果是HMAC DMAC PIPELINE方式，则注册frw_event_deploy_pipeline */

    /* 引入宏, 如果是按照CHIP,DEVICE,VAP方式，则注册frw_event_deploy_owner */

    frw_event_deploy_register(frw_event_deploy_pipeline);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : frw_event_deploy_exit
 功能描述  : 对外接口，事件部署模块退出接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_exit(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_exit();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy exit fail.}");
        return ul_ret;
    }

    /* TBD */

    /* 事件部署模块数据结构卸载 */

    /* 调用事件管理模块接口，注销事件部署接口函数 */

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : frw_event_deploy_pipeline
 功能描述  : 内部函数，事件部署接口，挂接到事件管理模块中，按照PIPELINE部署
 输入参数  : pst_mem_event: 事件内存块指针
 输出参数  : en_deploy: FRW_EVENT_DEPLOY_IPC-该事件需要IPC
                        FRW_EVENT_DEPLOY_POST-该事件需要入队列
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  : 事件分发函数
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  frw_event_deploy_pipeline(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                              frw_event_deploy_enum_uint8 *en_deploy_result)
{
    frw_event_hdr_stru *pst_event_hdr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_deploy_pipeline: pst_ipc_mem_msg/en_deploy_result null ptr err:%d, %d}", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_hdr = (frw_event_hdr_stru *)pst_ipc_mem_msg->puc_data;

    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hdr->en_pipeline)
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_NON_IPC;
    }
    else
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

        frw_ipc_send(pst_ipc_mem_msg);
    }

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : frw_event_deploy_owner
 功能描述  : 内部函数，事件部署接口，挂接到事件管理模块中，按照CHIP, DEVICE, VAP部署
 输入参数  : pst_mem_event: 事件内存块指针
 输出参数  : en_deploy: FRW_EVENT_DEPLOY_IPC-该事件需要IPC
                        FRW_EVENT_DEPLOY_POST-该事件需要入队列
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  : 事件分发函数
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_owner(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                            frw_event_deploy_enum_uint8 *en_deploy_result)
{
    if ((OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        FRW_ERR_LOG2(0, "frw_event_deploy_owner: pst_ipc_mem_msg/en_deploy_result null ptr err:", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD */

    /* 1. 获取事件payload中的chip id, device id和vap id */

    /* 2. 获取当前VAP的事件部署策略，并根据策略进行部署 */

    /* 3. 更新统计量，区分CHIP, DEVICE, VAP分别进行统计 */

    (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_event_deploy_set_affinity_device
 功能描述  : 对外接口，chip亲和力绑定
 输入参数  : uc_device_id-设备ID
             ul_core_mask-CPU掩码
 输出参数  : 无
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  : device创建时调用
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_device(oal_uint8 uc_device_id,
                                                            oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. 检查当前该device期望部署方式与它所属的chip的部署方式是否冲突: */
    /* 如果chip的部署不存在，则表示不冲突,跳到第2步; */
    /* 如果chip的coremask包含device期望的coremask，就不冲突,跳到第2步; 否则冲突，返回失败 */

    /* 2. 检查当前该device期望部署方式与它所带的vap的部署方式是否冲突:*/
    /* 如果各个vap的部署不存在，则表示不冲突,跳到第3步; */
    /* 如果device期望的coremask不包含它底下某个vap的coremask，就冲突，返回失败;否则，跳到第3步; */

    /* 3. 不冲突，按照当前期望的部署方式部署 */
    /* 如果该device底下还存在没有部署的VAP，则统一按照device期望的部署方式进行部署 */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_event_deploy_set_affinity_vap
 功能描述  : 对外接口，chip亲和力绑定
 输入参数  : uc_vap_id-vap ID
             ul_core_mask-CPU掩码
 输出参数  : 无
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  : VAP创建时调用
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_vap(oal_uint8 uc_vap_id,
                                                        oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. 检查当前该vap期望部署方式与它所属的device的部署方式是否冲突: */
    /* 如果device的部署不存在，则表示不冲突，跳到第2步; */
    /* 如果device的coremask包含vap期望的coremask，就不冲突，跳到第3步; 否则冲突，返回失败 */

    /* 2. 检查当前该vap期望部署方式与它所属的chip的部署方式是否冲突: */
    /* 如果chip的部署不存在，则表示不冲突，跳到第3步; */
    /* 如果chip的coremask包含vap期望的coremask，就不冲突，跳到第3步; 否则冲突，返回失败 */

    /* 3. 不冲突，按照当前期望的部署方式部署 */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_event_deploy_set_affinity_chip
 功能描述  : 对外接口，chip亲和力绑定
 输入参数  : uc_chip_id-chip id
             ul_core_mask-CPU掩码
 输出参数  : 无
 返 回 值  : OAL_SUCC-成功; 其他-失败
 调用函数  : CHIP创建时调用
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_chip(oal_uint8 uc_chip_id,
                                                         oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. 检查当前该chip期望部署方式与它所带的device的部署方式是否冲突:*/
    /* 如果各个device的部署不存在，则表示不冲突，跳到第2步; */
    /* 如果chip期望的coremask不包含它底下某个device的coremask，就冲突，返回失败; 否则，跳到第3步 */

    /* 2. 检查当前该chip期望部署方式与它所带的vap的部署方式是否冲突:*/
    /* 如果各个vap的部署不存在，则表示不冲突，跳到第3步; */
    /* 如果chip期望的coremask不包含它底下某个vap的coremask，就冲突，返回失败；否则，执行第3步 */

    /* 3. 不冲突，按照当前期望的部署方式部署: */
    /* 如果该CHIP底下还存在没有部署的DEVICE和VAP，则统一按照CHIP期望的部署方式进行部署 */

    return OAL_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

