/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_ipc_msgqueue.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月16日
  最近修改   :
  功能描述   : frw_ipc_msgqueue.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FRW_IPC_MSGQUEUE_H__
#define __FRW_IPC_MSGQUEUE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_IPC_MSGQUEUE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM   (1 << 7)     /* 发送消息队列大小 必须为2的整数次方 */
#define FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM   (1 << 8)     /* 接受消息队列大小 必须为2的整数次方 */

/* 判断队列是否满 */
#define FRW_IPC_RING_FULL(_head, _tail, _length) (((_tail) + 1) % (_length) == (_head))

/* 判断队列是否为空 */
#define FRW_IPC_RING_EMPTY(_head, _tail)  ((_head) == (_tail))

/* 可翻转的队列头尾+1操作 */
#define FRW_IPC_RING_INCR(_val, _lim)       ((_val) = (((_val) + 1) & ((_lim) - 1)))

/* 发送消息队列入队尾+1操作 */
#define FRW_IPC_RING_TX_INCR(_val)          (FRW_IPC_RING_INCR((_val), (FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM)))

/* 接受消息队列入队头+1操作 */
#define FRW_IPC_RING_RX_INCR(_val)          (FRW_IPC_RING_INCR((_val), (FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM)))

/* 核间通信丢包告警打印 */
#define FRW_IPC_LOST_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_IPC_LOST_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)

/* 核间通信日志维测信息打印 */
#define FRW_IPC_LOG_INFO_PRINT1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_IPC_LOG_INFO_PRINT4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define MAX_LOG_RECORD              100         /* 日志记录最大条数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    FRW_IPC_TX_CTRL_ENABLED   = 0,       /* 目标核空闲可以发送核间通讯 */
    FRW_IPC_TX_CTRL_DISABLED  = 1,       /* 目标核忙不可启动间通讯中断 */

    FRW_IPC_TX_BUTT
}frw_ipc_tx_ctrl_enum;
typedef OAL_VOLATILE oal_uint8 frw_ipc_tx_ctrl_enum_uint8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/
typedef oal_mem_stru frw_ipc_msg_mem_stru;    /* 事件结构体内存块转定义 */


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    frw_ipc_msg_mem_stru     *pst_msg_mem;
}frw_ipc_msg_dscr_stru;

typedef struct
{
    OAL_VOLATILE oal_uint32         ul_tail;            /* 指向取出下一个消息位置 */
    OAL_VOLATILE oal_uint32         ul_head;            /* 指向要插入下一个消息位置 */
    oal_uint32                      ul_max_num;         /* 环形消息队列大小 */
    frw_ipc_msg_dscr_stru          *pst_dscr;           /* 环形消息描述符队列首地址 */
}frw_ipc_msg_queue_stru;

typedef struct
{
    oal_void        (*p_tx_complete_func)(frw_ipc_msg_mem_stru *);  /* 发送完成回调处理 */
    oal_void        (*p_rx_complete_func)(frw_ipc_msg_mem_stru *);  /* 接收回调处理 */
}frw_ipc_msg_callback_stru;

typedef struct
{
    oal_uint16          us_seq_num;             /* 接收消息的序列号 */
    oal_uint8           uc_target_cpuid;        /* 目标核cpuid */
    oal_uint8           uc_msg_type;            /* 消息类型 frw_ipc_msg_type_enum_uint8 */
    oal_int32           l_time_stamp;           /* 发送或接收消息的时间戳 */
}frw_ipc_log_record_stru;

typedef struct
{
    OAL_VOLATILE oal_uint32     ul_stats_recv_lost;                     /* 接收丢包统计 */
    OAL_VOLATILE oal_uint32     ul_stats_send_lost;                     /* 发送丢包统计 */
    OAL_VOLATILE oal_uint32     ul_stats_assert;                        /* 告警统计 */
    OAL_VOLATILE oal_uint32     ul_stats_send;                          /* 发送次数 */
    OAL_VOLATILE oal_uint32     ul_stats_recv;                          /* 接受次数 */
    OAL_VOLATILE oal_uint32     ul_tx_index;                            /* 发送日志结构体数组下标 */
    OAL_VOLATILE oal_uint32     ul_rx_index;                            /* 接收日志结构体数组下标 */
    frw_ipc_log_record_stru     st_tx_stats_record[MAX_LOG_RECORD];     /* 发送日志信息结构体数组 */
    frw_ipc_log_record_stru     st_rx_stats_record[MAX_LOG_RECORD];     /* 接收日志信息结构体数组 */
}frw_ipc_log_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  frw_ipc_msg_queue_init(frw_ipc_msg_queue_stru *pst_msg_queue, oal_uint32 ul_queue_len);
extern oal_uint32  frw_ipc_msg_queue_destroy(frw_ipc_msg_queue_stru *pst_msg_queue);
extern oal_uint32  frw_ipc_msg_queue_recv(oal_void *p_arg);
extern oal_uint32  frw_ipc_msg_queue_send(frw_ipc_msg_queue_stru *pst_ipc_tx_msg_queue, frw_ipc_msg_mem_stru *pst_msg_input, oal_uint8 uc_flags, oal_uint8 uc_cpuid);
extern oal_uint32  frw_ipc_msg_queue_register_callback(frw_ipc_msg_callback_stru *p_ipc_msg_handler);
extern oal_uint32  frw_ipc_log_exit(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_init(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_recv_alarm(frw_ipc_log_stru *pst_log, oal_uint32 ul_lost);
extern oal_uint32  frw_ipc_log_send_alarm(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_send(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type);
extern oal_uint32  frw_ipc_log_recv(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type);
extern oal_uint32  frw_ipc_log_tx_print(frw_ipc_log_stru *pst_log);
extern oal_uint32  frw_ipc_log_rx_print(frw_ipc_log_stru *pst_log);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_ipc_msgqueue.h */
