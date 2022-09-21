/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_profiling.h
  版 本 号   : 初稿
  作    者   : wangtd
  生成日期   : 2015年3月4日
  最近修改   :
  功能描述   : oal_profiling.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月4日
    作    者   : Wlan_mib_temp
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_PROFILING_H__
#define __OAL_PROFILING_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_util.h"
//#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
//#include "core_cr4.h"
//#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PROFILING_H



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW != _PRE_OS_VERSION)
#define PACKETMEM
#else
#define PACKETMEM __attribute__((section("shared_mem_section"))) __attribute__((zero_init))
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
#define OAL_MIPS_TX_STATISTIC(_uc_func_idx) oal_profiling_tx_save_data(_uc_func_idx)
#define OAL_MIPS_RX_STATISTIC(_uc_func_idx) oal_profiling_rx_save_data(_uc_func_idx)
#else
#define OAL_MIPS_TX_STATISTIC(_uc_func_idx)
#define OAL_MIPS_RX_STATISTIC(_uc_func_idx)
#endif

#define OAL_MIPS_TX_PACKET_MAX_COUNT             1       /* DMAC统计发包的最大次数 */
#define OAL_MIPS_RX_PACKET_MAX_COUNT             1       /* DMAC统计收包的最大次数 */

#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION) || defined(_PRE_WIFI_DMT))&&(!defined(_PRE_PC_LINT))
#define OAL_GET_THRUPUT_BYPASS_ENABLE(_uc_type) (0)
#define OAL_SET_THRUPUT_BYPASS_ENABLE(_uc_type, _uc_value)
#else
#define OAL_GET_THRUPUT_BYPASS_ENABLE(_uc_type) oal_get_thruput_bypass_enable(_uc_type)
#define OAL_SET_THRUPUT_BYPASS_ENABLE(_uc_type, _uc_value) oal_set_thruput_bypass_enable(_uc_type, _uc_value)
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 报文发送统计函数列表 */
typedef enum
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    /* wal and hmac, Time0 */
    HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT,
    HMAC_PROFILING_FUNC_CB_INIT,
    HMAC_PROFILING_FUNC_TRAFFIC_CLASSIFY,
    HMAC_PROFILING_FUNC_SETUP_BA,
    HMAC_PROFILING_FUNC_AMSDU,
    HMAC_PROFILING_FUNC_ENCAP_HEAD,

    /* hcc */
    HOST_PROFILING_FUNC_HCC_TX_ADAPT,
    HOST_PROFILING_FUNC_HCC_TX_DATA,
    HOST_PROFILING_FUNC_HCC_TX,

    HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC,

#else
    /* SDIO Write, Time0 */
    DMAC_SDIO_H2D_WRITE_START,
    DMAC_SDIO_H2D_WRITE_CALLBACK,
    DMAC_SDIO_H2D_TRANSFER_BEGIN,
    DMAC_SDIO_H2D_TRANSFER_END,
    DMAC_SDIO_H2D_BUILD_ADMA_DESCR_END,
    DMAC_SDIO_H2D_WRITE_END,

    /* SDIO Write Over, Time1 */
    DMAC_SDIO_H2D_WROVER_START,
    DMAC_SDIO_H2D_ASSEM_INFO_BEGIN,
    DMAC_SDIO_H2D_WROVER_END,

    /* 发送开始 Time2 */
    DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START,
    DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_END,

    DMAC_PROFILING_FUNC_TX_DMAC_START,
    DMAC_PROFILING_FUNC_TX_DMAC_DATA,
    DMAC_PROFILING_FUNC_TX_DMAC_INACTIVE_USER_HDL,
    DMAC_PROFILING_FUNC_TX_DMAC_FLOWCTRL,
    DMAC_PROFILING_FUNC_TX_DMAC_FILL_DSCR,
    DMAC_PROFILING_FUNC_TX_DMAC_TID_ENQUEUE,
    DMAC_PROFILING_FUNC_TX_DMAC_END,

    /* 调度开始  Time3 */
    DMAC_PROFILING_FUNC_SCHEDULE_START,
    DMAC_PROFILING_FUNC_SCHEDULE,
    DMAC_PROFILING_FUNC_SCHEDULE_GET_TID,

    /* 发送MPDU */
    DMAC_PROFILING_FUNC_MPDU_REMOVE_QUEUE,

    /* 发送AMPDU */
    DMAC_PROFILING_FUNC_AMPDU_GET_INFO,
    DMAC_PROFILING_FUNC_AMPDU_AGGR_PREPARE,
    DMAC_PROFILING_FUNC_AMPDU_CALCULATE_MINLEN,
    DMAC_PROFILING_FUNC_AMPDU_LINK_MPDUS,
    DMAC_PROFILING_FUNC_AMPDU_REMOVE_QUEUE,

    DMAC_PROFILING_FUNC_TX_GET_TSF,
    DMAC_PROFILING_FUNC_TX_SET_DSCR,
    DMAC_PROFILING_FUNC_TX_PUT_DSCR,
    DMAC_PROFILING_FUNC_SCHEDULE_END,

    /* 发送完成处理 Time4 */
    DMAC_PROFILING_FUNC_TX_COMP_IRQ_START,
    DMAC_PROFILING_FUNC_TX_COMP_IRQ_GET_TSF,
    DMAC_PROFILING_FUNC_TX_COMP_IRQ_END,
    DMAC_PROFILING_FUNC_TX_COMP_DMAC_START,

    /* normal buff */
    DMAC_PROFILING_FUNC_TX_COMP_GET_DSCR_STAT,
    DMAC_PROFILING_FUNC_TX_COMP_PROCESS_FEATURE,
    DMAC_PROFILING_FUNC_TX_COMP_MGMT_NOTIFY,
    /* ampdu buff */
    DMAC_PROFILING_FUNC_AMPDU_AMPDU_PREPARE,
    DMAC_PROFILING_FUNC_AMPDU_UPDATE_MIB,
    DMAC_PROFILING_FUNC_AMPDU_TX_COMP_CHECK,
    DMAC_PROFILING_FUNC_AMPDU_EXTRACT_BA,
    DMAC_PROFILING_FUNC_AMPDU_COMP_ACK,
    DMAC_PROFILING_FUNC_AMPDU_COMP_ALG_NOTIFY,
    DMAC_PROFILING_FUNC_AMPDU_COMP_ENQUEUE_RETRY,

    DMAC_PROFILING_FUNC_TX_COMP_DMAC_END,
#endif
    DMAC_PROFILING_TX_FUNC_BUTT
} oal_profiling_tx_func_enum;
typedef oal_uint8 oal_profiling_tx_func_enum_uint8;

/* 报文接收统计函数列表 */
typedef enum
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    DMAC_PROFILING_FUNC_RX_COMP_IRQ_START                           , /* 接收的基准时间，接收完成中断上半部起始点 */
    DMAC_PROFILING_FUNC_RX_COMP_GET_DSCR                            , /* 获取描述符地址与个数 */
    DMAC_PROFILING_FUNC_RX_COMP_INTR_INFO_TO_LIST                   , /* 将中断信息存入链表 */
    DMAC_PROFILING_FUNC_RX_COMP_ADD_DSCR                            , /* 补充描述符 */
    DMAC_PROFILING_FUNC_RX_COMP_ALLOC_EVENT                         , /* 申请事件内存 */
    DMAC_PROFILING_FUNC_RX_COMP_IRQ_END                             , /* 事件抛出，上半部结束 */

    DMAC_PROFILING_FUNC_RX_DMAC_START                               ,  /* 函数起点:dmac_rx_process_data_event */
    DMAC_PROFILING_FUNC_RX_DMAC_GET_INTR_INFO_FROM_LIST             ,  /* 从中断信息链表中取节点*/
    DMAC_PROFILING_FUNC_RX_DMAC_GET_DSCR_AND_RET_BACK               ,  /* 取描述符各属性并将描述符还回资源池(02)或硬件队列(51) */
    DMAC_PROFILING_FUNC_RX_DMAC_INTR_LIST_OVER                      ,  /* 中断信息链表各节点获取完毕 */

    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_START               ,  /* 循环处理每个mpdu的起始点 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_FRAME_RXQ    ,  /* 针对帧类型与接收队列类型是否匹配做过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CB_CHECK     ,  /* AMSDU场景及buff个数异常场景过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_GET_VAP_ID          ,  /* 获取VAP ID */

    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ADDR_VAP     ,  /* 地址匹配过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_DSCR_SEC     ,  /* 描述符状态为加密异常的过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CIPHER_AMPDU ,  /* 加密类型匹配与AMPDU属性过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ALG_PSM_NULL ,  /* 算法、低功耗及Null帧过滤 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_OVER         ,  /* 过滤结束 */

    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_MAKE_NETBUF_LIST    ,  /* 将netbuf串成链 */
    DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PREPARE_EVENT                ,  /* 抛事件参数准备 */
    DMAC_PROFILING_FUNC_RX_DMAC_END                                 ,  /* 抛出事件完毕 */

    DMAC_SDIO_D2H_READ_START,
    DMAC_SDIO_D2H_READ_CALLBACK,
    DMAC_SDIO_D2H_BUILD_ADMA_DESCR_END,
    DMAC_SDIO_D2H_READ_END,

    DMAC_SDIO_D2H_RDOVER_START,
    DMAC_SDIO_D2H_RDOVER_END,
#else
    HMAC_PROFILING_FUNC_RX_DATA_ADAPT,
    HMAC_PROFILING_FUNC_RX_DATA_START,               /* 接收的基准时间 函数:hal_irq_rx_complete_isr */
    HMAC_PROFILING_FUNC_RX_GET_NETBUF_LIST,
    HMAC_PROFILING_FUNC_RX_REORDER_FILTER,
    HMAC_PROFILING_FUNC_RX_NON_REORDER_BACK,
    HMAC_PROFILING_FUNC_RX_TCP_ACK_OPT,
    HMAC_PROFILING_FUNC_RX_PREPARE_MSDU_INFO,
    HMAC_PROFILING_FUNC_RX_NETBUF_FOR_KERNEL,
    HMAC_PROFILING_FUNC_RX_HMAC_END,                 /* 申请事件内存 */
#endif
    DMAC_PROFILING_RX_FUNC_BUTT
} oal_profiling_rx_func_enum;
typedef oal_uint8 oal_profiling_rx_func_enum_uint8;

typedef enum
{
    OAL_MIPS_TX,
    OAL_MIPS_RX,

    OAL_MIPS_PARAM_BUTT
}oal_mips_param_enum;
typedef oal_uint8 oal_mips_param_enum_uint8;

typedef enum
{
    OAL_TX_LINUX_BYPASS,
    OAL_TX_SDIO_HOST_BYPASS,
    OAL_TX_SDIO_SLAVE_BYPASS,
    OAL_TX_HAL_HARDWARE_BYPASS,

    OAL_THRUPUT_BYPASS_BUTT,
}oal_thruput_bypass_enum;
typedef oal_uint8 oal_thruput_bypass_enum_uint8;


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
/* tx性能统计结构体 */
typedef struct
{
    oal_switch_enum_uint8 en_switch;         /* 统计开关 */
    oal_uint8             uc_index;          /* 当前包的计数 */
    oal_uint8             uc_flag;
    oal_uint8             auc_resv[1];

    oal_uint64            ast_tx_pass_cycles[OAL_MIPS_TX_PACKET_MAX_COUNT][DMAC_PROFILING_TX_FUNC_BUTT];  /* 经过时的CYCLES */
}oal_profiling_tx_statistic_stru;

/* rx性能统计结构体 */
typedef struct
{
    oal_switch_enum_uint8 en_switch;         /* 统计开关 */
    oal_uint8             uc_index;          /* 当前包的计数 */
    oal_uint8             auc_reserve[2];

    oal_uint64            ast_rx_pass_cycles[OAL_MIPS_RX_PACKET_MAX_COUNT][DMAC_PROFILING_RX_FUNC_BUTT];  /* 经过时的CYCLES */
}oal_profiling_rx_statistic_stru;

/* 维测，设置某一种具体mips开关的参数结构体 */
typedef struct
{
    oal_int32                           l_mips_type;
    oal_int32                           l_switch;
}oal_mips_type_param_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/* 保存tx profiling测试的所有数据 */
extern oal_profiling_tx_statistic_stru g_mips_tx_statistic;

/* 保存rx profiling测试的所有数据 */
extern oal_profiling_rx_statistic_stru g_mips_rx_statistic;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef _PRE_WLAN_PROFLING_SOC
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
extern oal_void oal_profiling_check_soc(oal_void);
#endif
#endif


#ifdef _PRE_WLAN_PROFLING_MIPS
extern oal_uint32  oal_profiling_mips_tx_init(oal_void);

extern oal_void  oal_profiling_tx_dump(
                    oal_uint32                          ul_packet_idx,
                    oal_uint32                          ul_loop,
                    oal_profiling_tx_func_enum_uint8    uc_func_idx);
extern oal_void oal_profiling_tx_mips_show(oal_void);
extern oal_uint32  oal_profiling_mips_rx_init(oal_void);
extern oal_void oal_profiling_rx_mips_show(oal_void);
extern oal_uint32 oal_profiling_mips_init(oal_void);
extern oal_void oal_profiling_enable_cycles(oal_void);
extern oal_void oal_profiling_disable_cycles(oal_void);
extern oal_void oal_profiling_tx_save_data(oal_profiling_tx_func_enum_uint8 en_func_index);
extern oal_void oal_profiling_rx_save_data(oal_profiling_rx_func_enum_uint8 en_func_index);
extern oal_void oal_profiling_stop_rx_save(oal_void);
extern oal_void oal_profiling_stop_tx_save(oal_void);

#endif

extern oal_uint32 oal_get_thruput_bypass_enable(oal_thruput_bypass_enum_uint8 uc_bypass_type);
extern oal_void oal_set_thruput_bypass_enable(oal_thruput_bypass_enum_uint8 uc_bypass_type, oal_uint8 uc_value);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_profiling.h */
