/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_trace.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月18日
  最近修改   :
  功能描述   : oam_trace.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAM_TRACE_H__
#define __OAM_TRACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_TRACE_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*****************************************************************************
    2.1 profiling相关宏定义
*****************************************************************************/
#define OAM_PROFILING_TX_PACKET_MAX_COUNT       2      /* 统计发包的最大次数 */
#define OAM_PROFILING_RX_PACKET_MAX_COUNT       20      /* 统计收包的最大次数 */
#define OAM_PROFILING_ALG_PACKET_MAX_COUNT       2      /* 统计ALG的最大次数 */

#define OAM_PROFILING_PACKET_INVALID_VALUE      1010    /* 不合理的skb id，初始化默认值为1010 */
#define OAM_PROFILING_PACKET_ABNORMAL_GAP       2000

#define OAM_PROFILING_STATISTIC_RX_DEBUG        0x01    /* RX流程配置位:1为enbale，0为disable */
#define OAM_PROFILING_STATISTIC_TX_DEBUG        0x02    /* RX流程配置位:1为enbale，0为disable */
#define OAM_PROFILING_STATISTIC_ALG_DEBUG       0x04    /* ALG流程配置位:1为enbale，0为disable */


/*****************************************************************************
    2.2 trace相关宏定义
*****************************************************************************/
#define OAM_TRACE_PRINT_DATA_LENGTH     128     /* TRACE打印的最大长度 */
#define OAM_TRACE_PRINT_FORMAT_LENGTH   128     /* TRACE输出格式的最大长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
    3.1 profiling相关枚举定义
*****************************************************************************/
/* 用于对应配置命令输入的配置类型 */
typedef enum
{
    OAM_PROFILING_SWITCH_DEBUG_CONFIG = 1,

    OAM_PROFILING_SWITCH_CONFIG_BUTT
}oam_profiling_switch_config_enum;
typedef oal_uint8  oam_profiling_switch_config_enum_uint8;



/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
    7.1 profiling相关STRUCT定义
*****************************************************************************/
/* tx性能统计结构体 */
typedef struct
{
    oal_spin_lock_stru  st_spin_lock;           /* 读写锁 */
    oal_uint16          us_abnormal_index;      /* 非正常索引统计 */
    oal_uint8           uc_idx_for_array;       /* 在发送流程入口函数处赋值 */
    oal_uint8           uc_skb_id_idx;          /* 在发送流程入口函数处赋值 */

    oal_uint16          aus_tx_skb_id_list[OAM_PROFILING_TX_PACKET_MAX_COUNT];                                  /* 用于将第几个发送的包，保存到对应次数的数组元素中 */
    oal_uint16          aus_tx_pass_count[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT];       /* 经过函数次数统计 */
    oal_uint32          ast_tx_func_stand_time[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT];  /* 经过函数基准时间 */
    oal_uint32          ast_tx_func_time_offset[OAM_PROFILING_TX_PACKET_MAX_COUNT][OAM_PROFILING_TX_FUNC_BUTT]; /* 函数间的时间差 */
}oam_profiling_tx_statistic_stru;

/* rx性能统计结构体 */
typedef struct
{
    oal_spin_lock_stru  st_spin_lock;           /* 读写锁 */
    oal_uint16          us_abnormal_index;      /* 非正常索引统计 */
    oal_uint8           uc_idx_for_array;       /* 在接收流程入口函数处赋值 */
    oal_uint8           uc_skb_id_idx;          /* 在接收流程入口函数处赋值 */

    oal_uint16          aus_rx_skb_id_list[OAM_PROFILING_RX_PACKET_MAX_COUNT];                                  /* 用于将第几个接收的包，保存到对应次数的数组元素中 */
    oal_uint16          aus_rx_pass_count[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT];       /* 经过函数次数统计 */
    oal_uint32          ast_rx_func_stand_time[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT];  /* 经过函数基准时间 */
    oal_uint32          ast_rx_func_time_offset[OAM_PROFILING_RX_PACKET_MAX_COUNT][OAM_PROFILING_RX_FUNC_BUTT]; /* 函数间的时间差 */
}oam_profiling_rx_statistic_stru;

/* alg性能统计结构体 */
typedef struct
{
    oal_spin_lock_stru  st_spin_lock;           /* 读写锁 */
    oal_uint16          us_abnormal_index;      /* 非正常索引统计 */
    oal_uint8           uc_idx_for_array;       /* 在发送流程入口函数处赋值 */
    oal_uint8           uc_skb_id_idx;          /* 在发送流程入口函数处赋值 */

    oal_uint16          aus_alg_skb_id_list[OAM_PROFILING_ALG_PACKET_MAX_COUNT];                                  /* 用于将第几个发送的包，保存到对应次数的数组元素中 */
    oal_uint16          aus_alg_pass_count[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT];       /* 经过函数次数统计 */
    oal_uint32          ast_alg_func_stand_time[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT];  /* 经过函数基准时间 */
    oal_uint32          ast_alg_func_time_offset[OAM_PROFILING_ALG_PACKET_MAX_COUNT][OAM_PROFILING_ALG_FUNC_BUTT]; /* 函数间的时间差 */
}oam_profiling_alg_statistic_stru;

/* 芯片启动时间统计结构体 */
typedef struct
{
    oal_uint32          aul_timestamp[OAM_PROFILING_STARTTIME_FUNC_BUTT];
}oam_profiling_starttime_statistic_stru;

/* 信道切换时间统计 */
typedef struct
{
    oal_uint32          aul_timestamp[OAM_PROFILING_CHSWITCH_FUNC_BUTT];
}oam_profiling_chswitch_statistic_stru;


/* OAM PROFILING的控制结构 */
typedef struct
{
    oal_int     i_profiling_tx_debuging_enable;
    oal_int     i_profiling_rx_debuging_enable;
    oal_int     i_profiling_alg_debuging_enable;
}oam_profiling_statistic_debug_stru;

/* 自定义skb cb对应的结构体，用于设置测试信息 */
typedef struct
{
    oal_uint8   auc_resv[44];       /* 对ping过程统计无意义，对应于dmac_rx_ctrl_stru */

    oal_uint16  us_skb_id;          /* skb id号 */
    oal_uint8   uc_is_broad_cast;   /* 数据包是否为广播包 */
    oal_uint8   uc_is_used;
}oam_profiling_skb_cb_stru;

/*****************************************************************************
    7.2 trace相关STRUCT定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/*****************************************************************************
    4.1 profiling全局变量声明
*****************************************************************************/

/*****************************************************************************
    4.3 trace全局变量声明
*****************************************************************************/

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
    trace对应函数声明
*****************************************************************************/
extern oal_uint32  oam_trace_init(oal_void);
extern oal_uint32  oam_trace_set_switch(oal_switch_enum_uint8 en_switch);

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_trace.h */
