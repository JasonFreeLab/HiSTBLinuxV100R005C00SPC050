/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hal_common_ops.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月23日
  最近修改   :
  功能描述   : hal层规格定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月23日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifndef __HAL_COMMOM_OPS_H__
#define __HAL_COMMOM_OPS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "wlan_spec.h"

/*****************************************************************************/
/*****************************************************************************/
/*                        HI1102 产品宏定义、枚举                            */
/*****************************************************************************/
/*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HAL_PUBLIC_HOOK_FUNC(_func) do {                                                                  \
         hi1102##_func();                                                                                 \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC1(_func, param) do {                                                          \
         hi1102##_func(param );                                                                           \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC2(_func, _param1, _param2) do {                                               \
         hi1102##_func(_param1, _param2);                                                                 \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC3(_func, _param1, _param2, _param3)                                       \
         hi1102##_func(_param1, _param2, _param3)

#define HAL_PUBLIC_HOOK_FUNC4(_func, _param1, _param2, _param3, _param4) do {                             \
         hi1102##_func(_param1, _param2, _param3, _param4);                                               \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC5(_func, _param1, _param2, _param3, _param4, _param5) do {                    \
         hi1102##_func(_param1, _param2, _param3, _param4, _param5);                                      \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC6(_func, _param1, _param2, _param3, _param4, _param5, _param6) do {           \
         hi1102##_func(_param1, _param2, _param3, _param4, _param5, _param6);                             \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC7(_func, _param1, _param2, _param3, _param4, _param5, _param6, _param7) do {  \
         hi1102##_func(_param1, _param2, _param3, _param4, _param5, _param6, _param7);                    \
} while(0);



#define HAL_RX_DSCR_GET_SW_ADDR(_addr)     hal_rx_dscr_get_sw_addr(_addr)   /* 一个字节中包含的bit数目 */
#define HAL_RX_DSCR_GET_REAL_ADDR(_addr)   hal_rx_dscr_get_real_addr(_addr)   /* 一个字节中包含的bit数目 */

#define HAL_MAX_AP_NUM                     2      /* HAL AP个数 */
#define HAL_MAX_STA_NUM                    3      /* HAL STA个数 */
#define HAL_MAX_VAP_NUM                    (HAL_MAX_AP_NUM + HAL_MAX_STA_NUM)  /* HAL VAP???? */

#define HAL_VAP_ID_IS_VALID(_vap_id)      ((_vap_id == 0) || (_vap_id == 1) || (_vap_id == 4) || (_vap_id == 5) || (_vap_id == 6))

/*****************************************************************************
  3 枚举
*****************************************************************************/
typedef enum
{
    HAL_TX_QUEUE_BE        = 0,        /* 尽力而为业务 */
    HAL_TX_QUEUE_BK        = 1,        /* 背景业务 */
    HAL_TX_QUEUE_VI        = 2,        /* 视频业务 */
    HAL_TX_QUEUE_VO        = 3,        /* 语音业务 */
    HAL_TX_QUEUE_HI        = 4,        /* 高优先级队列(管理帧/控制帧用此队列) */
    HAL_TX_QUEUE_BUTT
}hal_tx_queue_type_enum;
typedef oal_uint8 hal_tx_queue_type_enum_uint8;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef enum
{
    BTCOEX_NOFRAME = 0,
    BTCOEX_SELFCTS = 1,
    BTCOEX_NULLDATA = 2,
    BTCOEX_QOSNULL = 3,
    BTCOEX_FRAME_NUTT
}coex_preempt_frame_enum;
typedef oal_uint8 coex_preempt_frame_enum_uint8;
#endif


/*****************************************************************************
  4 函数实现
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32*  hal_rx_dscr_get_real_addr(oal_uint32 *pul_rx_dscr)
{
    /* 注意数字2代表hi1102_rx_buffer_addr_stru结构体中的prev指针，移动到next指针位置 */
    if (OAL_PTR_NULL == pul_rx_dscr)
    {
        //OAL_IO_PRINT("[file = %s, line = %d], hal_rx_dscr_get_real_addr, dscr is NULL!\r\n",
        //             __FILE__, __LINE__);
        return pul_rx_dscr;
    }
    return pul_rx_dscr + 2;
}

OAL_STATIC OAL_INLINE oal_uint32*  hal_rx_dscr_get_sw_addr(oal_uint32 *pul_rx_dscr)
{
    /* 注意数字2代表hi1102_rx_buffer_addr_stru结构体中的prev指针，移动到next指针位置 */
    if (OAL_PTR_NULL == pul_rx_dscr)
    {
        OAL_IO_PRINT("[file = %s, line = %d], hal_rx_dscr_get_sw_addr, dscr is NULL!\r\n",
                     __FILE__, __LINE__);
        return pul_rx_dscr;
    }
    return pul_rx_dscr - 2;
}

#endif /* end of #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)*/

/*****************************************************************************/
/*****************************************************************************/
/*                        HI1151 产品宏定义、枚举                            */
/*****************************************************************************/
/*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HAL_PUBLIC_HOOK_FUNC(_func) do {                                                                  \
         hi1151##_func();                                                                                   \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC1(_func, param) do {                                                          \
         hi1151##_func(param );                                                                             \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC2(_func, _param1, _param2) do {                                               \
         hi1151##_func(_param1, _param2);                                                                   \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC3(_func, _param1, _param2, _param3) \
         hi1151##_func(_param1, _param2, _param3)

#define HAL_PUBLIC_HOOK_FUNC4(_func, _param1, _param2, _param3, _param4) do {                             \
         hi1151##_func(_param1, _param2, _param3, _param4);                                                 \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC5(_func, _param1, _param2, _param3, _param4, _param5) do {                    \
         hi1151##_func(_param1, _param2, _param3, _param4, _param5);                                        \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC6(_func, _param1, _param2, _param3, _param4, _param5, _param6) do {           \
         hi1151##_func(_param1, _param2, _param3, _param4, _param5, _param6);                               \
} while(0);

#define HAL_PUBLIC_HOOK_FUNC7(_func, _param1, _param2, _param3, _param4, _param5, _param6, _param7) do {  \
         hi1151##_func(_param1, _param2, _param3, _param4, _param5, _param6, _param7);                      \
} while(0);

#define HAL_RX_DSCR_GET_SW_ADDR(_addr)    (_addr)
#define HAL_RX_DSCR_GET_REAL_ADDR(_addr)  (_addr)
#define HAL_TX_DSCR_GET_SW_ADDR(_addr)    (_addr)
#define HAL_TX_DSCR_GET_REAL_ADDR(_addr)  (_addr)

#define HAL_MAX_AP_NUM                     4       /* 支持多BSSID特性的规格，最大为4 AP*/
#define HAL_MAX_STA_NUM                    1      /* HAL STA个数 */
#define HAL_MAX_VAP_NUM                    (HAL_MAX_AP_NUM + HAL_MAX_STA_NUM)  /* HAL VAP???? */
#define HAL_VAP_ID_IS_VALID(_vap_id)      ((_vap_id == 0) || (_vap_id == 1)|| (_vap_id == 2) || (_vap_id == 3) || (_vap_id == 4))

/*****************************************************************************
  3 枚举
*****************************************************************************/
typedef enum
{
    HAL_TX_QUEUE_BK        = 0,        /* 背景业务 */
    HAL_TX_QUEUE_BE        = 1,        /* 尽力而为业务 */
    HAL_TX_QUEUE_VI        = 2,        /* 视频业务 */
    HAL_TX_QUEUE_VO        = 3,        /* 语音业务 */
    HAL_TX_QUEUE_HI        = 4,        /* 高优先级队列(管理帧/控制帧用此队列) */
    HAL_TX_QUEUE_BUTT
}hal_tx_queue_type_enum;
typedef oal_uint8 hal_tx_queue_type_enum_uint8;

#endif  /* end of #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)*/

/*****************************************************************************/
/*****************************************************************************/
/*                        公共宏定义、枚举、结构体                           */
/*****************************************************************************/
/*****************************************************************************/

/* 获取当前帧所使用的协议模式 */
#define HAL_GET_DATA_PROTOCOL_MODE(_val)      ((_val) >> 6)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 2.4GHz频段: 信道号对应的信道索引值 */
typedef enum
{
    HAL_2G_CHANNEL1  = 0,
    HAL_2G_CHANNEL2  = 1,
    HAL_2G_CHANNEL3  = 2,
    HAL_2G_CHANNEL4  = 3,
    HAL_2G_CHANNEL5  = 4,
    HAL_2G_CHANNEL6  = 5,
    HAL_2G_CHANNEL7  = 6,
    HAL_2G_CHANNEL8  = 7,
    HAL_2G_CHANNEL9  = 8,
    HAL_2G_CHANNEL10 = 9,
    HAL_2G_CHANNEL11 = 10,
    HAL_2G_CHANNEL12 = 11,
    HAL_2G_CHANNEL13 = 12,
    HAL_2G_CHANNEL14 = 13,

    HAL_CHANNEL_FREQ_2G_BUTT = 14
}hal_channel_freq_2g_enum;
typedef oal_uint8 hal_channel_freq_2g_enum_uint8;

typedef enum
{
    HAL_FCS_PROTECT_TYPE_NONE      = 0,    /* NONE        */
    HAL_FCS_PROTECT_TYPE_SELF_CTS,         /* SELF CTS    */
    HAL_FCS_PROTECT_TYPE_NULL_DATA,        /* NULL DATA   */

    HAL_FCS_PROTECT_TYPE_BUTT
}hal_fcs_protect_type_enum;
typedef oal_uint8 hal_fcs_protect_type_enum_uint8;

typedef enum
{
    HAL_FCS_PROTECT_CNT_1 = 1,    /* 1 */
    HAL_FCS_PROTECT_CNT_2 = 2,    /* 2 */
    HAL_FCS_PROTECT_CNT_3 = 3,    /* 3 */

    HAL_FCS_PROTECT_CNT_BUTT
}hal_fcs_protect_cnt_enum;
typedef oal_uint8 hal_fcs_protect_cnt_enum_uint8;

typedef enum
{
    HAL_OPER_MODE_NORMAL,
    HAL_OPER_MODE_HUT,

    HAL_OPER_MODE_BUTT
}hal_oper_mode_enum;
typedef oal_uint8 hal_oper_mode_enum_uint8;

/**** RF测试用，用于指示配置TX描述符字段 ****/
typedef enum
{
    HAL_RF_TEST_DATA_RATE_ZERO,
    HAL_RF_TEST_BAND_WIDTH,
    HAL_RF_TEST_CHAN_CODE,
    HAL_RF_TEST_BUTT
}hal_rf_test_sect_enum;
typedef oal_uint8 hal_rf_test_sect_enum_uint8;
/*****************************************************************************
  3.1 队列相关枚举定义
*****************************************************************************/
#define HAL_AC_TO_Q_NUM(_ac) (       \
        ((_ac) == WLAN_WME_AC_VO) ? HAL_TX_QUEUE_VO : \
        ((_ac) == WLAN_WME_AC_VI) ? HAL_TX_QUEUE_VI : \
        ((_ac) == WLAN_WME_AC_BK) ? HAL_TX_QUEUE_BK : \
        ((_ac) == WLAN_WME_AC_BE) ? HAL_TX_QUEUE_BE : \
        ((_ac) == WLAN_WME_AC_MGMT) ? HAL_TX_QUEUE_HI : \
        HAL_TX_QUEUE_BK)

#define HAL_Q_NUM_TO_AC(_q) (       \
        ((_q) == HAL_TX_QUEUE_VO) ? WLAN_WME_AC_VO : \
        ((_q) == HAL_TX_QUEUE_VI) ? WLAN_WME_AC_VI : \
        ((_q) == HAL_TX_QUEUE_BK) ? WLAN_WME_AC_BK : \
        ((_q) == HAL_TX_QUEUE_BE) ? WLAN_WME_AC_BE : \
        ((_q) == HAL_TX_QUEUE_HI) ? WLAN_WME_AC_MGMT : \
        WLAN_WME_AC_BE)

#define HAL_TX_QUEUE_MGMT               HAL_TX_QUEUE_HI     /* 0~3代表AC发送队列，4代表管理帧、控制帧发送队列 */

/*****************************************************************************
  3.3 描述符相关枚举定义
*****************************************************************************/
typedef enum
{
    HAL_TX_RATE_RANK_0 = 0,
    HAL_TX_RATE_RANK_1,
    HAL_TX_RATE_RANK_2,
    HAL_TX_RATE_RANK_3,

    HAL_TX_RATE_RANK_BUTT
}hal_tx_rate_rank_enum;
typedef oal_uint8 hal_tx_rate_rank_enum_uint8;
typedef enum
{
    HAL_DFS_RADAR_TYPE_NULL  = 0,
    HAL_DFS_RADAR_TYPE_FCC   = 1,
    HAL_DFS_RADAR_TYPE_ETSI  = 2,
    HAL_DFS_RADAR_TYPE_MKK   = 3,
    HAL_DFS_RADAR_TYPE_KOREA = 4,

    HAL_DFS_RADAR_TYPE_BUTT
}hal_dfs_radar_type_enum;
typedef oal_uint8 hal_dfs_radar_type_enum_uint8;

typedef enum
{
    HAL_RX_NEW                    = 0x0,
    HAL_RX_SUCCESS                = 0x1,
    HAL_RX_DUP_DETECTED           = 0x2,
    HAL_RX_FCS_ERROR              = 0x3,
    HAL_RX_KEY_SEARCH_FAILURE     = 0x4,
    HAL_RX_CCMP_MIC_FAILURE       = 0x5,
    HAL_RX_ICV_FAILURE            = 0x6,
    HAL_RX_TKIP_REPLAY_FAILURE    = 0x7,
    HAL_RX_CCMP_REPLAY_FAILURE    = 0x8,
    HAL_RX_TKIP_MIC_FAILURE       = 0x9,
    HAL_RX_BIP_MIC_FAILURE        = 0xA,
    HAL_RX_BIP_REPLAY_FAILURE     = 0xB,
    HAL_RX_MUTI_KEY_SEARCH_FAILURE= 0xC     /*组播广播*/
} hal_rx_status_enum;
typedef oal_uint8 hal_rx_status_enum_uint8;

/* 接收描述符队列状态 */
typedef enum
{
    HAL_DSCR_QUEUE_INVALID  = 0,
    HAL_DSCR_QUEUE_VALID,
    HAL_DSCR_QUEUE_SUSPENDED,

    HAL_DSCR_QUEUE_STATUS_BUTT
}hal_dscr_queue_status_enum;
typedef oal_uint8 hal_dscr_queue_status_enum_uint8;

/* 接收描述符队列号 */
typedef enum
{
    HAL_RX_DSCR_NORMAL_PRI_QUEUE = 0,
    HAL_RX_DSCR_HIGH_PRI_QUEUE,
    HAL_RX_DSCR_SMALL_QUEUE,

    HAL_RX_DSCR_QUEUE_ID_BUTT
}hal_rx_dscr_queue_id_enum;
typedef oal_uint8 hal_rx_dscr_queue_id_enum_uint8;

/* TX 描述符 12行 b23:b22 phy工作模式 */
typedef enum
{
    WLAN_11B_PHY_PROTOCOL_MODE              = 0,   /* 11b CCK */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE      = 1,   /* 11g/a OFDM */
    WLAN_HT_PHY_PROTOCOL_MODE               = 2,   /* 11n HT */
    WLAN_VHT_PHY_PROTOCOL_MODE              = 3,   /* 11ac VHT */

    WLAN_PHY_PROTOCOL_BUTT
}wlan_phy_protocol_enum;
typedef oal_uint8 wlan_phy_protocol_enum_uint8;

/* HAL模块需要抛出的WLAN_DRX事件子类型的定义
 说明:该枚举需要和dmac_wlan_drx_event_sub_type_enum_uint8枚举一一对应 */
typedef enum
{
    HAL_WLAN_DRX_EVENT_SUB_TYPE_RX,     /* WLAN DRX 流程 */

    HAL_WLAN_DRX_EVENT_SUB_TYPE_BUTT
}hal_wlan_drx_event_sub_type_enum;
typedef oal_uint8 hal_wlan_drx_event_sub_type_enum_uint8;

/* HAL模块需要抛出的WLAN_CRX事件子类型的定义
   说明:该枚举需要和dmac_wlan_crx_event_sub_type_enum_uint8枚举一一对应 */
typedef enum
{
    HAL_WLAN_CRX_EVENT_SUB_TYPE_RX,    /* WLAN CRX 流程 */

    HAL_WLAN_CRX_EVENT_SUB_TYPE_BUTT
}hal_wlan_crx_event_sub_type_enum;
typedef oal_uint8 hal_wlan_crx_event_sub_type_enum_uint8;

typedef enum
{
    HAL_TX_COMP_SUB_TYPE_TX,

    HAL_TX_COMP_SUB_TYPE_BUTT
}hal_tx_comp_sub_type_enum;
typedef oal_uint8 hal_tx_comp_sub_type_enum_uint8;

typedef enum
{
    HAL_EVENT_TBTT_SUB_TYPE,

    HAL_EVENT_TBTT_SUB_TYPE_BUTT
}hal_event_tbtt_sub_type_enum;
typedef oal_uint8 hal_event_tbtt_sub_type_enum_uint8;


/*****************************************************************************
  3.4 中断相关枚举定义
*****************************************************************************/
/****3.4.1  芯片错误中断类型 ************************************************/
typedef enum
{
    HAL_EVENT_ERROR_IRQ_MAC_ERROR,      /* MAC错误中断时间*/
    HAL_EVENT_ERROR_IRQ_SOC_ERROR,      /* SOC错误中断事件*/

    HAL_EVENT_ERROR_IRQ_SUB_TYPE_BUTT
}hal_event_error_irq_sub_type_enum;
typedef oal_uint8 hal_event_error_irq_sub_type_enum_uint8;

/****3.4.2  MAC错误中断类型 (枚举值与错误中断状态寄存器的位一一对应!)********/
typedef enum
{
    HAL_MAC_ERROR_PARA_CFG_ERR                  = 0,        /*描述符参数配置异常,包括AMPDU长度配置不匹配,AMPDU中MPDU长度超长,sub msdu num错误*/
    HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL          = 1,        /*接收非AMSDU帧长大于RxBuff大小异常*/
    HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND            = 2,        /*未找到BA会话表项异常0*/
    HAL_MAC_ERROR_PHY_TRLR_TIME_OUT             = 3,        /*PHY_RX_TRAILER超时*/
    HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN           = 4,        /*PHY_RX_FIFO满写异常*/
    HAL_MAC_ERROR_TX_DATAFLOW_BREAK             = 5,        /*发送帧数据断流*/
    HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT             = 6,        /*RX_FSM状态机超时*/
    HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT             = 7,        /*TX_FSM状态机超时*/
    HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT         = 8,        /*RX_HANDLER状态机超时*/
    HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT         = 9,        /*TX_HANDLER状态机超时*/
    HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN          = 10,       /*TX 中断FIFO满写*/
    HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN          = 11,       /*RX中断 FIFO满写*/
    HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN        = 12,       /*HIRX中断FIFO满写*/
    HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY         = 13,       /*接收到普通优先级帧但此时RX BUFFER指针为空*/
    HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY       = 14,       /*接收到高优先级帧但此时HI RX BUFFER指针为空*/
    HAL_MAC_ERROR_BUS_RLEN_ERR                  = 15,       /*总线读请求长度为0异常*/
    HAL_MAC_ERROR_BUS_RADDR_ERR                 = 16,       /*总线读请求地址无效异常*/
    HAL_MAC_ERROR_BUS_WLEN_ERR                  = 17,       /*总线写请求长度为0异常*/
    HAL_MAC_ERROR_BUS_WADDR_ERR                 = 18,       /*总线写请求地址无效异常*/
    HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN             = 19,       /*tx acbk队列fifo满写*/
    HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN             = 20,       /*tx acbe队列fifo满写*/
    HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN             = 21,       /*tx acvi队列fifo满写*/
    HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN             = 22,       /*tx acv0队列fifo满写*/
    HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN            = 23,       /*tx hipri队列fifo满写*/
    HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT           = 24,       /*matrix计算超时*/
    HAL_MAC_ERROR_CCA_TIME_OUT                  = 25,       /*cca超时*/
    HAL_MAC_ERROR_DCOL_DATA_OVERLAP             = 26,       /*数采overlap告警*/
    HAL_MAC_ERROR_BEACON_MISS                   = 27,       /*连续发送beacon失败*/
    HAL_MAC_ERROR_INTR_FIFO_UNEXPECTED_READ     = 28,       /*interrupt fifo空读异常*/
    HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR       = 29,       /*rx desc地址错误异常*/
    HAL_MAC_ERROR_RX_OVERLAP_ERR                = 30,       /*mac没有处理完前一帧,phy又上报了一帧异常*/
    HAL_MAC_ERROR_RESERVED_31                   = 31,
    HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT       = 32,       /*发送BE队列退避超时*/
    HAL_MAC_ERROR_TX_ACBK_BACKOFF_TIMEOUT       = 33,       /*发送BK队列退避超时*/
    HAL_MAC_ERROR_TX_ACVI_BACKOFF_TIMEOUT       = 34,       /*发送VI队列退避超时*/
    HAL_MAC_ERROR_TX_ACVO_BACKOFF_TIMEOUT       = 35,       /*发送VO队列退避超时*/
    HAL_MAC_ERROR_TX_HIPRI_BACKOFF_TIMEOUT      = 36,       /*发送高优先级队列退避超时*/
    HAL_MAC_ERROR_RX_SMALL_Q_EMPTY              = 37,       /*接收普通队列的小包，但是小包队列指针为空*/
    HAL_MAC_ERROR_PARA_CFG_2ERR                 = 38,       /*发送描述符中AMPDU中MPDU长度过长*/
    HAL_MAC_ERROR_PARA_CFG_3ERR                 = 39,       /*发送描述符中11a，11b，11g发送时，mpdu配置长度超过4095*/
    HAL_MAC_ERROR_EDCA_ST_TIMEOUT               = 40,       /*CH_ACC_EDCA_CTRL状态机超时*/

    HAL_MAC_ERROR_TYPE_BUTT
}hal_mac_error_type_enum;
typedef oal_uint8 hal_mac_error_type_enum_uint8;

/****3.4.3 SOC错误中断类型 (需要在DMAC模块进行处理的error irq的类型定义)*****/
typedef enum
{
    /* SOC错误中断 */
    HAL_SOC_ERROR_BUCK_OCP,                                                 /* PMU BUCK过流中断 */
    HAL_SOC_ERROR_BUCK_SCP,                                                 /* PMU BUCK短路中断 */
    HAL_SOC_ERROR_OCP_RFLDO1,                                               /* PMU RFLDO1过流中断 */
    HAL_SOC_ERROR_OCP_RFLDO2,                                               /* PMU RFLDO2过流中断 */
    HAL_SOC_ERROR_OCP_CLDO,                                                 /* PMU CLDO过流中断 */
    HAL_SOC_ERROR_RF_OVER_TEMP,                                             /* RF过热中断 */
    HAL_SOC_ERROR_CMU_UNLOCK,                                               /* CMU PLL失锁中断 */
    HAL_SOC_ERROR_PCIE_SLV_ERR,                                             /* PCIE总线错误中断 */

    HAL_SOC_ERROR_TYPE_BUTT
}hal_soc_error_type_enum;
typedef oal_uint8 hal_soc_error_type_enum_uint8;


/* DMAC MISC 子事件枚举定义 */
typedef enum
{
    HAL_EVENT_DMAC_MISC_CH_STATICS_COMP,    /* 信道统计/测量完成中断 */
    HAL_EVENT_DMAC_MISC_RADAR_DETECTED,     /* 检测到雷达信号 */
    HAL_EVENT_DMAC_MISC_DFS_AUTH_CAC,       /* DFS认证CAC测试 */
    HAL_EVENT_DMAC_MISC_DBAC,               /* DBAC */
    HAL_EVENT_DMAC_MISC_MWO_DET,            /* 微波炉识别中断 */
#ifdef _PRE_WLAN_DFT_REG
    HAL_EVENT_DMAC_REG_REPORT,
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    HAL_EVENT_DMAC_PS_BTCOEX,
    HAL_EVENT_DMAC_BT_TRANSFER,
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
    HAL_EVENT_DMAC_P2P_NOA_ABSENT_START,
    HAL_EVENT_DMAC_P2P_NOA_ABSENT_END,
    HAL_EVENT_DMAC_P2P_CTWINDOW_END,
#endif
    HAL_EVENT_DMAC_BEACON_TIMEOUT,          /* 等待beacon帧超时 */
    HAL_EVENT_DMAC_CALI_TO_HMAC,            /* 校准数据从dmac抛到hmac */

    HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT
}hal_dmac_misc_sub_type_enum;
typedef oal_uint8  hal_dmac_misc_sub_type_enum_uint8;

/*****************************************************************************
  3.5 复位相关枚举定义
*****************************************************************************/
/****3.5.1  复位事件子类型定义 **********************************************/
typedef enum
{
    HAL_RESET_HW_TYPE_ALL = 0,
    HAL_RESET_HW_TYPE_PHY,
    HAL_RESET_HW_TYPE_MAC,
    HAL_RESET_HW_TYPE_RF,
    HAL_RESET_HW_TYPE_MAC_PHY,
    HAL_RESET_HW_TYPE_TCM,
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    HAL_RESET_HW_TYPE_MAC_TSF,
    HAL_RESET_HW_TYPE_MAC_CRIPTO,
    HAL_RESET_HW_TYPE_MAC_NON_CRIPTO,
    HAL_RESET_HW_TYPE_PHY_RADAR,
#endif
    HAL_RESET_HW_NORMAL_TYPE_PHY,
    HAL_RESET_HW_NORMAL_TYPE_MAC,
    HAL_RESET_HW_TYPE_DUMP_MAC,
    HAL_RESET_HW_TYPE_DUMP_PHY,

    HAL_RESET_HW_TYPE_BUTT
}hal_reset_hw_type_enum;
typedef oal_uint8 hal_reset_hw_type_enum_uint8;

/****3.5.1  复位MAC子模块定义 **********************************************/
typedef enum
{
    HAL_RESET_MAC_ALL = 0,
    HAL_RESET_MAC_PA ,
    HAL_RESET_MAC_CE,
    HAL_RESET_MAC_TSF,
    HAL_RESET_MAC_DUP,
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    HAL_RESET_MAC_LOGIC,
#endif
    HAL_RESET_MAC_BUTT
}hal_reset_mac_submod_enum;
typedef oal_uint8 hal_reset_mac_submod_enum_uint8;

typedef enum
{
   HAL_LPM_SOC_BUS_GATING       = 0,
   HAL_LPM_SOC_PCIE_RD_BYPASS   = 1,
   HAL_LPM_SOC_MEM_PRECHARGE    = 2,
   HAL_LPM_SOC_PCIE_L0          = 3,
   HAL_LPM_SOC_PCIE_L1_PM       = 4,

   HAL_LPM_SOC_SET_BUTT
}hal_lpm_soc_set_enum;
typedef oal_uint8   hal_lpm_soc_set_enum_uint8;

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
typedef enum
{
    HAL_SMPS_MODE_DISABLE = 0,
    HAL_SMPS_MODE_STATIC ,
    HAL_SMPS_MODE_DYNAMIC,

    HAL_SMPS_MODE_BUTT
}hal_smps_mode_enum;
typedef oal_uint8 hal_smps_mode_enum_uint8;

#endif
typedef enum
{
    HAL_ALG_ISR_NOTIFY_DBAC,
    HAL_ALG_ISR_NOTIFY_MWO_DET,
    HAL_ALG_ISR_NOTIFY_ANTI_INTF,

    HAL_ALG_ISR_NOTIFY_BUTT,
}hal_alg_noify_enum;
typedef oal_uint8 hal_alg_noify_enum_uint8;

typedef enum
{
    HAL_ISR_TYPE_TBTT,
    HAL_ISR_TYPE_ONE_PKT,
    HAL_ISR_TYPE_MWO_DET,
    HAL_ISR_TYPE_NOA_START,
    HAL_ISR_TYPE_NOA_END,

    HAL_ISR_TYPE_BUTT,
}hal_isr_type_enum;
typedef oal_uint8 hal_isr_type_enum_uint8;



/*性能测试相关*/
typedef enum {
    HAL_ALWAYS_TX_DISABLE,         /* 禁用常发 */
    HAL_ALWAYS_TX_RF,              /* 保留给RF测试广播报文*/
    HAL_ALWAYS_TX_AMPDU_ENABLE,    /* 使能AMPDU聚合包常发 */
    HAL_ALWAYS_TX_MPDU,            /* 使能非聚合包常发 */
    HAL_ALWAYS_TX_BUTT
}hal_device_always_tx_state_enum;
typedef oal_uint8 hal_device_always_tx_enum_uint8;


typedef enum {
    HAL_ALWAYS_RX_DISABLE,         /* 禁用常收 */
    HAL_ALWAYS_RX_RESERVED,        /* 保留给RF测试广播报文*/
    HAL_ALWAYS_RX_AMPDU_ENABLE,    /* 使能AMPDU聚合包常收 */
    HAL_ALWAYS_RX_ENABLE,          /* 使能非聚合包常收 */
    HAL_ALWAYS_RX_BUTT
}hal_device_always_rx_state_enum;
typedef oal_uint8 hal_device_always_rx_enum_uint8;

typedef enum
{
    WLAN_PHY_RATE_1M                = 0,    /* 0000 */
    WLAN_PHY_RATE_2M                = 1,    /* 0001 */
    WLAN_PHY_RATE_5HALF_M           = 2,    /* 0010 */
    WLAN_PHY_RATE_11M               = 3,    /* 0011 */

    WLAN_PHY_RATE_48M               = 8,    /* 1000 */
    WLAN_PHY_RATE_24M               = 9,    /* 1001 */
    WLAN_PHY_RATE_12M               = 10,   /* 1010 */
    WLAN_PHY_RATE_6M                = 11,   /* 1011 */

    WLAN_PHY_RATE_54M               = 12,   /* 1100 */
    WLAN_PHY_RATE_36M               = 13,   /* 1101 */
    WLAN_PHY_RATE_18M               = 14,   /* 1110 */
    WLAN_PHY_RATE_9M                = 15,   /* 1111 */

    WLAN_PHY_RATE_BUTT
}wlan_phy_rate_enum;

#ifdef _PRE_WLAN_FEATURE_DFS
typedef enum
{
    HAL_RADAR_NOT_REPORT = 0,
    HAL_RADAR_REPORT,
}hal_radar_filter_enum;
typedef oal_uint8 hal_radar_filter_enum_uint8;
#endif
/*****************************************************************************
  3.6 加密相关枚举定义
*****************************************************************************/
/****3.6.1  芯片密钥类型定义 ************************************************/

typedef enum
{
    HAL_KEY_TYPE_TX_GTK              = 0,       /*Hi1102:HAL_KEY_TYPE_TX_IGTK */
    HAL_KEY_TYPE_PTK                 = 1,
    HAL_KEY_TYPE_RX_GTK              = 2,
    HAL_KEY_TYPE_RX_GTK2             = 3,       /* 02使用 */
    HAL_KEY_TYPE_BUTT
} hal_cipher_key_type_enum;
typedef oal_uint8 hal_cipher_key_type_enum_uint8;

/****3.6.2  芯片加密算法类型对应芯片中的值 **********************************/
typedef enum
{
    HAL_WEP40                      = 0,
    HAL_TKIP                       = 1,
    HAL_CCMP                       = 2,
    HAL_NO_ENCRYP                  = 3,
    HAL_WEP104                     = 4,
    HAL_BIP                        = 5,
    HAL_CIPER_PROTOCOL_TYPE_BUTT
} hal_cipher_protocol_type_enum;
typedef oal_uint8 hal_cipher_protocol_type_enum_uint8;

/****3.6.3  芯片填写加密寄存器CE_LUT_CONFIG AP/STA **************************/
typedef enum
{
    HAL_AUTH_KEY = 0,      /* 表明该设备为认证者 */
    HAL_SUPP_KEY = 1,      /* 表明该设备为申请者 */

    HAL_KEY_ORIGIN_BUTT,
} hal_key_origin_enum;
typedef oal_uint8 hal_key_origin_enum_uint8;

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
typedef struct
{
    hal_fcs_protect_type_enum_uint8     en_protect_type;
    hal_fcs_protect_cnt_enum_uint8      en_protect_cnt;
    oal_uint8                           auc_resv[2];
    oal_uint32                          ul_tx_mode;
    oal_uint32                          ul_tx_data_rate;
    oal_uint16                          us_duration;    /* 单位 us */
    oal_uint16                          us_timeout;
    oal_uint8                           auc_protect_frame[HAL_FCS_PROT_MAX_FRAME_LEN];
}hal_one_packet_cfg_stru;

typedef struct
{
    oal_bool_enum_uint8     en_mac_in_one_pkt_mode  : 1;
    oal_bool_enum_uint8     en_self_cts_success     : 1;
    oal_bool_enum_uint8     en_null_data_success    : 1;
    oal_uint32              ul_resv                 : 5;
}hal_one_packet_status_stru;

typedef struct
{
    oal_uint8     uc_pn_tid;          /* tid,0~7, 对rx pn lut有效 */
    oal_uint8     uc_pn_peer_idx;     /* 对端peer索引,0~31 */
    oal_uint8     uc_pn_key_type;     /* 1151 0:multicast,1:unicast */
                                      /* 1102 tx pn: 0x0：GTK(multicast) 0x1：PTK(unicast) 0x2：IGTK others：reserved*/
                                      /* 1102 rx pn: 0x0：组播/广播数据帧 0x1：单播qos数据帧 0x2：单播非qos数据帧
                                         0x3：单播管理帧  0x4：组播/广播管理帧 others：保留 */
    oal_uint8     uc_all_tid;         /* 0:仅配置TID,1:所有TID 对rx pn lut有效*/
    oal_uint32    ul_pn_msb;          /* pn值的高32位,写操作时做入参，读操作时做返回值 */
    oal_uint32    ul_pn_lsb;          /* pn值的低32位，写操作时做入参，读操作时做返回值 */
}hal_pn_lut_cfg_stru;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct {
    oal_uint16  bit_bt_on            : 1,
               bit_bt_cali          : 1,
               bit_bt_ps            : 1,
               bit_bt_inquiry       : 1,
               bit_bt_page          : 1,
               bit_bt_acl           : 1,
               bit_bt_a2dp          : 1,
               bit_bt_sco           : 1,
               bit_bt_data_trans    : 1,
               bit_bt_acl_num       : 3,
               bit_bt_link_role     : 4;
} bt_status_stru;

typedef union {
    oal_uint16 us_bt_status_reg;
    bt_status_stru st_bt_status;
} btcoex_bt_status_union;

typedef struct {
    oal_uint16  bit_ble_on           : 1,
               bit_ble_scan         : 1,
               bit_ble_con          : 1,
               bit_ble_adv          : 1,
               bit_bt_transfer      : 1,
               bit_bt_ba            : 1,
               bit_resv             : 10;
} ble_status_stru;

typedef union {
    oal_uint16 us_ble_status_reg;
    ble_status_stru st_ble_status;
} btcoex_ble_status_union;

typedef struct hal_btcoex_btble_status {
    btcoex_bt_status_union un_bt_status;
    btcoex_ble_status_union un_ble_status;
} hal_btcoex_btble_status_stru;

typedef struct
{
    oal_uint32 ul_abort_start_cnt;
    oal_uint32 ul_abort_done_cnt;
    oal_uint32 ul_abort_end_cnt;
    oal_uint32 ul_preempt_cnt;
    oal_uint32 ul_post_preempt_cnt;
    oal_uint32 ul_post_premmpt_fail_cnt;
    oal_uint32 ul_abort_duration_on;
    oal_uint32 ul_abort_duration_start_us;
    oal_uint32 ul_abort_duration_us;
    oal_uint32 ul_abort_duration_s;
} hal_btcoex_statistics_stru;

typedef struct hal_btcoex_wifi_rx_info {
    oal_uint16      us_rx_rssi_stat_count;
    oal_uint16      us_rx_rate_stat_count;
    oal_int32       l_rx_rssi;
    oal_uint32      ul_rx_rate_mbps;
} hal_btcoex_wifi_rx_info_stru;

typedef struct hal_btcoex_wifi_status {
    oal_uint32 ul_ap_beacon_count;
    oal_uint8 uc_ap_beacon_miss;
    coex_preempt_frame_enum_uint8  en_all_abort_preempt_type;
    oal_uint8 uc_occupied_times;
    oal_uint8 uc_rx_rate_statistics_flag;

    oal_uint8 uc_prio_occupied_state;
    oal_uint8 auc_resv[3];

    oal_uint32 ul_timestamp;

    oal_uint8 uc_get_addba_req_flag;
    oal_uint8 uc_ba_size_index;
    oal_uint8 uc_rx_rate_statistics_timeout;
    oal_uint8 uc_ba_size_addba_rsp_index;

    oal_uint8 uc_ba_size;
    oal_uint8 uc_ba_size_tendence;
    oal_uint8 uc_linkloss_occupied_times;
    oal_uint8 uc_linkloss_index;

    oal_uint32 ul_rx_rate_threshold_min;
    oal_uint32 ul_rx_rate_threshold_max;
    hal_btcoex_wifi_rx_info_stru st_btcoex_rx_info;
    hal_btcoex_statistics_stru st_btcoex_statistics;
} hal_btcoex_wifi_status_stru;
#endif

typedef struct hal_wifi_channel_status {
    oal_uint8 uc_chan_number;     /* 主20MHz信道号 */
    oal_uint8 uc_band;            /* 频段 */
    oal_uint8 uc_bandwidth;       /* 带宽模式 */
    oal_uint8 uc_idx;             /* 信道索引号 */
} hal_wifi_channel_status_stru;

/*****************************************************************************
  7.0 寄存器配置结构
*****************************************************************************/
/*lint -e958*/
#if (_PRE_WLAN_CHIP_VERSION == _PRE_WLAN_CHIP_FPGA_HI1101RF)
struct witp_reg_cfg
{
    oal_uint16    us_soft_index;
    oal_uint8     uc_addr;
    oal_uint32    ul_val;
}__OAL_DECLARE_PACKED;
#elif(_PRE_WLAN_CHIP_VERSION == _PRE_WLAN_CHIP_FPGA_HI1151RF) /* End of _PRE_WLAN_CHIP_FPGA_HI1101RF*/
struct witp_reg16_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
typedef struct witp_reg16_cfg witp_reg16_cfg_stru;

struct witp_reg_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
#elif(_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)    /* End of _PRE_WLAN_CHIP_FPGA_HI1151RF*/
struct witp_reg16_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
typedef struct witp_reg16_cfg witp_reg16_cfg_stru;

struct witp_reg_cfg
{
    oal_uint16   us_addr;
    oal_uint16   us_val;
}__OAL_DECLARE_PACKED;
#endif /* End of _PRE_WLAN_CHIP_ASIC */

typedef struct witp_reg_cfg witp_reg_cfg_stru;

struct witp_single_tune_reg_cfg
{
    oal_uint16    us_addr;
    oal_uint16     ul_val;//oal_int32     ul_val;
}__OAL_DECLARE_PACKED;

typedef struct witp_single_tune_reg_cfg witp_single_tune_reg_cfg_stru;

/*lint +e958*/
/*****************************************************************************
  7.1 基准发送描述符定义
*****************************************************************************/
typedef struct tag_hal_tx_dscr_stru
{
    oal_dlist_head_stru                 st_entry;
    oal_netbuf_stru                    *pst_skb_start_addr;         /* Sub MSDU 0 Skb Address */
    oal_uint16                          us_original_mpdu_len;       /* mpdu长度 含帧头 */
    hal_tx_queue_type_enum_uint8        uc_q_num;                   /* 发送队列队列号 */
    oal_uint8                           bit_is_retried          :1; /* 是不是重传包 */
    oal_uint8                           bit_is_ampdu            :1; /* 是不是ampdu */
    oal_uint8                           bit_is_rifs             :1; /* 是不是rifs发送 */
    oal_uint8                           bit_is_first            :1; /* 标志是否是第一个描述符 */
    oal_uint8                           bit_tx_hal_vap_id       :4; /* Proxy STA的tx hal_vap_id */
    oal_uint8                           data[4];
}hal_tx_dscr_stru;

/*****************************************************************************
  7.2 基准接收描述符定义
*****************************************************************************/
typedef struct tag_hal_rx_dscr_stru
{
    oal_uint32                 *pul_prev_rx_dscr;           /* 前一个描述符的地址           */
    oal_uint32                  ul_skb_start_addr;          /* 描述符中保存的netbuf的首地址 */
    oal_uint32                 *pul_next_rx_dscr;           /* 前一个描述符的地址(物理地址) */
}hal_rx_dscr_stru;

/*****************************************************************************
  7.3 对外部发送提供接口所用数据结构
*****************************************************************************/

/*****************************************************************************
  结构名  : hal_channel_matrix_dsc_stru
  结构说明: 矩阵信息结构体
*****************************************************************************/
typedef struct
{
    /*(第10 23行) */
    oal_uint8                            bit_codebook              : 2;
    oal_uint8                            bit_grouping              : 2;
    oal_uint8                            bit_row_num               : 4;

    oal_uint8                            bit_column_num            : 4;
    oal_uint8                            bit_response_flag         : 1;     /* 在Tx 描述符中不用填写该字段;发送完成中断后，将有无信道矩阵信息存储在此 */
    oal_uint8                            bit_reserve1              : 3;

    oal_uint16                           us_channel_matrix_length;          /*信道矩阵的总字节(Byte)数 */
    oal_uint32                           ul_steering_matrix;                /* txbf需要使用的矩阵地址,填写发送描述符时候使用 */
}hal_channel_matrix_dsc_stru;

typedef struct
{
    /* PHY TX MODE 1(第13行) */
    /* (1) 速率自适应填写 */
    oal_uint8                               uc_extend_spatial_streams;      /* 扩展空间流个数 */
    wlan_channel_code_enum_uint8            en_channel_code;                /* 信道编码(BCC或LDPC) */

    /* (2) ACS填写 */
    hal_channel_assemble_enum_uint8         uc_channel_bandwidth;           /* 工作带宽 */

    oal_uint8                               bit_lsig_txop       : 1;        /* L-SIG TXOP保护 0:不开启保护，1: 开启保护*/
    oal_uint8                               bit_reserved        : 7;

    oal_uint8                               dyn_bandwidth_in_non_ht;        /* 如果是本设备或者对端设备不是VHT设备，或者寄存器设置的速率为non-HT速率，那么该字段无意义（可填0)*/
    oal_uint8                               dyn_bandwidth_in_non_ht_exist;  /* 如果本设备和对端设备都为VHT设备，并且寄存器设置的速率为non-HT速率，那么该字段填1 */
    oal_uint8                               ch_bandwidth_in_non_ht_exist;   /* 如果本设备和对端设备都为VHT设备，并且寄存器设置的速率为non-HT速率，那么该字段填1 */


#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    oal_uint8                               bit_lpf_gain_level             : 2;
    oal_uint8                               bit_upc_gain_level             : 4;
    oal_uint8                               bit_pa_gain_level              : 2;

    oal_uint8                               bit_dpd_enable                 : 1;
    oal_uint8                               auc_reserve1                   : 7;

    /* 02芯片测试添加抗干扰变量，为tx描述符赋值 */
    oal_uint8                               bit_anti_intf_1thr              : 2;
    oal_uint8                               bit_anti_intf_0thr              : 2;
    oal_uint8                               bit_anti_intf_en                : 1;
    oal_uint8                               bit_reserve                     : 3;
#else
    oal_uint8                               bit_upc_gain_level             : 1;  /*UPC增益级别*/
    oal_uint8                               bit_pa_gain_level              : 1;  /*PA增益级别*/
    oal_uint8                               bit_micro_tx_power_gain_level  : 4;  /*Micro Tx power增益级别*/
    oal_uint8                               bit_dac_gain_level             : 2;  /*DAC增益级别*/

    oal_uint8                               auc_reserve1[2];
#endif

    oal_uint8                               uc_smoothing;                   /* 通知接收端是否对信道矩阵做平滑 */

    wlan_sounding_enum_uint8                en_sounding_mode;               /* sounding模式 */
}hal_tx_txop_rate_params_stru;

typedef union
{
    oal_uint32  ul_value;
    /* (第14 19 20 21行) */
    struct
    {
    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        oal_uint8   bit_tx_count              : 2;                      /* 传输次数 */
        oal_uint8   bit_stbc_mode             : 2;                      /* 空时分组编码 */
    #else
        oal_uint8   bit_tx_count              : 4;                      /* 传输次数 */
    #endif
        oal_uint8   bit_tx_chain_selection    : 4;                      /* 发送通道选择 (单通道:0x1, 双通道:0x3, 三通道:0x7, 四通道:0xf) */
        oal_uint8   uc_tx_data_antenna;                                 /* 发送数据使用的天线组合 */

        union
        {
            struct
            {
                oal_uint8   bit_vht_mcs       : 4;
                oal_uint8   bit_nss_mode      : 2;                       /* 该速率对应的空间流枚举值 */
                oal_uint8   bit_protocol_mode : 2;                       /* 协议模式 */
            } st_vht_nss_mcs;
            struct
            {
                oal_uint8   bit_ht_mcs        : 6;
                oal_uint8   bit_protocol_mode : 2;                       /* 协议模式 */
            } st_ht_rate;
            struct
            {
                oal_uint8   bit_legacy_rate   : 4;
                oal_uint8   bit_reserved1     : 2;
                oal_uint8   bit_protocol_mode : 2;                       /* 协议模式 */
            } st_legacy_rate;
        } un_nss_rate;

        oal_uint8   bit_rts_cts_enable        : 1;                      /* 是否使能RTS */
        oal_uint8   bit_txbf_mode             : 2;                      /* txbf模式 */
        oal_uint8   bit_preamble_mode         : 1;                      /* 前导码 */
        oal_uint8   bit_short_gi_enable       : 1;                      /* 短保护间隔 */
        oal_uint8   bit_reserve               : 3;
    }rate_bit_stru;
}hal_tx_txop_per_rate_params_union;

typedef struct
{
    /* PHY TX MODE 2 (第15行) */
    oal_uint8                               uc_tx_rts_antenna;          /* 发送RTS使用的天线组合 */
    oal_uint8                               uc_rx_ctrl_antenna;         /* 接收CTS/ACK/BA使用的天线组合 */
    oal_uint8                               auc_reserve1[1];            /* TX VAP index 不是算法填写，故在此也填0 */
    oal_uint8                               bit_txop_ps_not_allowed: 1; /* 0代表允许TXOP POWER save，1代表不允许TXOP POWER save */
    oal_uint8                               bit_long_nav_enable:     1; /* NAV保护enable字段，1代表Long nav保护，0代表non long nav保护 */
    oal_uint8                               bit_group_id:            6; /* 这个字段暂时由软件填写，最终可能由算法填写，故先列出 */

}hal_tx_txop_antenna_params_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
typedef struct
{
    /* TX POWER (第22行) */
    oal_uint8                               bit_lpf_gain_level0           : 1;
    oal_uint8                               bit_pa_gain_level0            : 1;
    oal_uint8                               bit_upc_gain_level0           : 4;
    oal_uint8                               bit_dac_gain_level0           : 2;

    oal_uint8                               bit_lpf_gain_level1           : 1;
    oal_uint8                               bit_pa_gain_level1            : 1;
    oal_uint8                               bit_upc_gain_level1           : 4;
    oal_uint8                               bit_dac_gain_level1           : 2;

    oal_uint8                               bit_lpf_gain_level2           : 1;
    oal_uint8                               bit_pa_gain_level2            : 1;
    oal_uint8                               bit_upc_gain_level2           : 4;
    oal_uint8                               bit_dac_gain_level2           : 2;

    oal_uint8                               bit_lpf_gain_level3           : 1;
    oal_uint8                               bit_pa_gain_level3            : 1;
    oal_uint8                               bit_upc_gain_level3           : 4;
    oal_uint8                               bit_dac_gain_level3           : 2;

}hal_tx_txop_tx_power_stru;
#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_TEST_MODE != _PRE_TEST_MODE_OFF) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
typedef struct
{
    /* TX POWER (第14行) */
    oal_uint8                               bit_lpf_gain_level0           : 2;
    oal_uint8                               bit_upc_gain_level0           : 4;
    oal_uint8                               bit_pa_gain_level0            : 2;

    oal_uint8                               bit_lpf_gain_level1           : 2;
    oal_uint8                               bit_upc_gain_level1           : 4;
    oal_uint8                               bit_pa_gain_level1            : 2;

    oal_uint8                               bit_lpf_gain_level2           : 2;
    oal_uint8                               bit_upc_gain_level2           : 4;
    oal_uint8                               bit_pa_gain_level2            : 2;

    oal_uint8                               bit_lpf_gain_level3           : 2;
    oal_uint8                               bit_upc_gain_level3           : 4;
    oal_uint8                               bit_pa_gain_level3            : 2;
}hal_tx_txop_tx_power_stru;
#endif

typedef struct
{
    wlan_tx_ack_policy_enum_uint8           en_ack_policy;     /* ACK 策略 */
    oal_uint8                               uc_tid_no;        /* 通信标识符 */
    oal_uint8                               uc_qos_enable;    /* 是否开启QoS */
    oal_uint8                               auc_resv[1];
}hal_wmm_txop_params_stru;

/* 第12 17行 */
typedef struct
{
    oal_uint16                              us_tsf_timestamp;
    oal_uint8                               uc_mac_hdr_len;
    oal_uint8                               uc_num_sub_msdu;
}hal_tx_mpdu_mac_hdr_params_stru;

typedef struct
{
    oal_uint32                              ul_mac_hdr_start_addr;
    oal_netbuf_stru                        *pst_skb_start_addr;
}hal_tx_mpdu_address_params_stru;

typedef struct
{
    oal_uint8                               uc_ra_lut_index;
    oal_uint8                               uc_tx_vap_index;
    oal_uint8                               auc_resv[2];
}hal_tx_ppdu_addr_index_params_stru;


typedef struct
{
    oal_uint32                              ul_msdu_addr0;
    oal_uint16                              us_msdu0_len;
    oal_uint16                              us_msdu1_len;
    oal_uint32                              ul_msdu_addr1;
}hal_tx_msdu_address_params;


typedef struct
{
    oal_uint8                            uc_long_retry;
    oal_uint8                            uc_short_retry;
    oal_uint8                            uc_rts_succ;
    oal_uint8                            uc_cts_failure;
    oal_int8                             c_last_ack_rssi;
    oal_uint8                            uc_mpdu_num;
    oal_uint8                            uc_error_mpdu_num;
    oal_uint8                            uc_last_rate_rank;
    oal_uint8                            uc_tid;
    hal_tx_queue_type_enum_uint8         uc_ac;
    oal_uint16                           us_mpdu_len;
    oal_uint8                            uc_is_retried;
    oal_uint8                            uc_bandwidth;
    oal_uint8			                 uc_sounding_mode;           /* 表示该帧sounding类型 */
    oal_uint8                            uc_status;                  /* 该帧的发送结果 */
    oal_uint64                           ull_ampdu_result;
    hal_channel_matrix_dsc_stru          st_tx_dsc_chnl_matrix;      /*发送描述符中的信道矩阵信息*/
    hal_tx_txop_per_rate_params_union    ast_per_rate[HAL_TX_RATE_MAX_NUM];
    oal_uint32                           ul_ampdu_length;
    hal_tx_txop_tx_power_stru            st_tx_power;

}hal_tx_dscr_ctrl_one_param;

typedef struct
{
    /* 由安全特性更新 */
    wlan_security_txop_params_stru           *pst_security;         /* 第16行 MAC TX MODE 2 */

    /* groupid和partial_aid */
    wlan_groupid_partial_aid_stru            st_groupid_partial_aid;  /* 第12和15行部分 */

}hal_tx_txop_feature_stru;
/*****************************************************************************
  结构名  : hal_tx_txop_alg_stru
  结构说明: DMAC模块TXOP发送控制结构
*****************************************************************************/
typedef struct
{
    /*tx dscr中算法填写的参数 */
    hal_channel_matrix_dsc_stru          st_txbf_matrix;                     /* 第10 23行  */
    hal_tx_txop_rate_params_stru         st_rate;                            /* 第13行(HY TX MODE 1)*/
    hal_tx_txop_per_rate_params_union    ast_per_rate[HAL_TX_RATE_MAX_NUM];  /* 第14(PHY TX RATA 1) 19 20 21 行*/
    hal_tx_txop_antenna_params_stru      st_antenna_params;                  /* 第15行(PHY TX MODE 2) */
    hal_tx_txop_tx_power_stru            st_tx_power;                        /* 第22行(TX POWER)*/

}hal_tx_txop_alg_stru;

/*****************************************************************************
  结构名  : hal_tx_ppdu_feature_stru
  结构说明: DMAC模块PPDU发送控制结构
*****************************************************************************/
typedef struct
{
    /* 第15 16行 TX VAP index 和 RA LUT Index */
    hal_tx_ppdu_addr_index_params_stru  st_ppdu_addr_index;

    /* 第16 17行 */
    oal_uint32                          ul_ampdu_length;         /* 不包括null data的ampdu总长度 */
    oal_uint16                          us_min_mpdu_length;      /* 根据速率查表得到的ampdu最小mpdu的长度 */

    /* 第13行 */
    oal_uint8                           uc_ampdu_enable;         /* 是否使能AMPDU */

    oal_uint8                           uc_rifs_enable;          /* rifs模式下发送时，MPDU链最后是否挂一个BAR帧 */
    /* 第12行  MAC TX MODE 1 */
    oal_uint16                          us_tsf;
    oal_uint8                           en_retry_flag_hw_bypass;
    oal_uint8                           en_duration_hw_bypass;
    oal_uint8                           en_seq_ctl_hw_bypass;
    oal_uint8                           en_timestamp_hw_bypass;
    oal_uint8                           en_addba_ssn_hw_bypass;
    oal_uint8                           en_tx_pn_hw_bypass;
    oal_uint8                           en_long_nav_enable;
    oal_uint8                           uc_mpdu_num;             /* ampdu中mpdu的个数 */
    oal_uint8                           auc_resv[2];
}hal_tx_ppdu_feature_stru;

/*****************************************************************************
  结构名  : hal_tx_mpdu_stru
  结构说明: DMAC模块MPDU发送控制结构
*****************************************************************************/
typedef struct
{
    /* 从11MAC帧头中获取 针对MPDU*/
    hal_wmm_txop_params_stru              st_wmm;
    hal_tx_mpdu_mac_hdr_params_stru       st_mpdu_mac_hdr;                          /* 第12 17行(PHY TX MODE 2) */
    hal_tx_mpdu_address_params_stru       st_mpdu_addr;                             /* 第18行(MAC TX MODE 2)*/
    hal_tx_msdu_address_params            ast_msdu_addr[WLAN_DSCR_SUBTABEL_MAX_NUM];/* 第24,25...行*/
}hal_tx_mpdu_stru;

/* Beacon帧发送参数 */
typedef struct
{
    oal_uint32              ul_pkt_ptr;
    oal_uint32              us_pkt_len;
    hal_tx_txop_alg_stru   *pst_tx_param;
    oal_uint32              ul_tx_chain_mask;

    //dmac看不到描述符，这两个寄存器赋值放到hal
    //oal_uint32  ul_phy_tx_mode;     /* 同tx描述符 phy tx mode 1 */
    //oal_uint32  ul_tx_data_rate;    /* 同tx描述符 data rate 0 */

}hal_beacon_tx_params_stru;

/*****************************************************************************
  结构名  : hal_security_key_stru
  结构说明: DMAC模块安全密钥配置结构体
*****************************************************************************/
typedef struct
{
    oal_uint8                           uc_key_id;
    wlan_cipher_key_type_enum_uint8     en_key_type;
    oal_uint8                           uc_lut_idx;
    wlan_ciper_protocol_type_enum_uint8 en_cipher_type;
    oal_bool_enum_uint8                 en_update_key;
    wlan_key_origin_enum_uint8          en_key_origin;
    oal_uint8                           auc_reserve[2];
    oal_uint8                           *puc_cipher_key;
    oal_uint8                           *puc_mic_key;
}hal_security_key_stru;

/*****************************************************************************
  7.4 基准VAP和Device结构
*****************************************************************************/
typedef struct tag_hal_to_dmac_vap_stru
{
    oal_uint8                            uc_chip_id;                                 /* 芯片ID */
    oal_uint8                            uc_device_id;                               /* 设备ID */
    oal_uint8                            uc_vap_id;                                  /* VAP ID */
    wlan_vap_mode_enum_uint8             en_vap_mode;                                /* VAP工作模式 */
    oal_uint8                            uc_mac_vap_id;                              /* 保存mac vap id */
    oal_uint8                            uc_dtim_cnt;                                /* dtim count */
    oal_uint8                            uc_service_id;
    oal_uint8                            uc_resv[1];
}hal_to_dmac_vap_stru;


/*****************************************************************************
  7.5 对外部接收提供接口所用数据结构
*****************************************************************************/
typedef struct
{
    oal_int8            c_rssi_dbm;
    union
    {
        struct
        {
            oal_uint8   bit_vht_mcs       : 4;
            oal_uint8   bit_nss_mode      : 2;
            oal_uint8   bit_protocol_mode : 2;
        } st_vht_nss_mcs;                                   /* 11ac的速率集定义 */
        struct
        {
            oal_uint8   bit_ht_mcs        : 6;
            oal_uint8   bit_protocol_mode : 2;
        } st_ht_rate;                                       /* 11n的速率集定义 */
        struct
        {
            oal_uint8   bit_legacy_rate   : 4;
            oal_uint8   bit_reserved1     : 2;
            oal_uint8   bit_protocol_mode : 2;
        } st_legacy_rate;                                   /* 11a/b/g的速率集定义 */
    } un_nss_rate;

    oal_uint8           uc_short_gi;
    oal_uint8           uc_bandwidth;
}hal_rx_statistic_stru;



#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
/* 裸系统下，后续需要传输给HMAC模块的信息，与mac_rx_ctl_stru结构体保持一致*/
/*hal_rx_ctl_stru结构的修改要考虑hi1102_rx_get_info_dscr函数中的优化
并且结构修改要和文件dmac_ext_if.h和hmac_ext_if.h 中的修改一致*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_da_user_idx       :4;
    oal_uint8                   bit_ta_user_idx       :4;
    oal_uint8                   bit_mac_header_len    :6;   /* mac header帧头长度 */
    oal_uint8                   bit_reserved1         :2;
    /*word 1*/
    oal_uint16                  us_frame_len;               /* 帧头与帧体的总长度 */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4;   /* 每个MPDU占用的buf数 */
}hal_rx_ctl_stru;
#else
/* 后续需要传输给HMAC模块的信息，与mac_rx_ctl_stru结构体保持一致*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;   /* 对应hal vap id */
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_buff_nums         :4;   /* 每个MPDU占用的buf数目 */
    oal_uint8                   bit_reserved1         :4;
    oal_uint8                   uc_mac_header_len;          /* mac header帧头长度 */
    /*word 1*/
    oal_uint16                  us_frame_len;               /* 帧头与帧体的总长度 */
    oal_uint16                  us_da_user_idx;             /* 目的地址用户索引 */
    /*word 2*/
    oal_uint32                 *pul_mac_hdr_start_addr;     /* 对应的帧的帧头地址,虚拟地址 */
}hal_rx_ctl_stru;

#endif

/* 对DMAC SCAN 模块提供的硬件MAC/PHY信道测量结果结构体 */
typedef struct
{
    /* 信道统计 */
    oal_uint32  ul_ch_stats_time_us;
    oal_uint32  ul_pri20_free_time_us;
    oal_uint32  ul_pri40_free_time_us;
    oal_uint32  ul_pri80_free_time_us;
    oal_uint32  ul_ch_rx_time_us;
    oal_uint32  ul_ch_tx_time_us;

    /* 信道测量 */
    oal_uint8  uc_ch_estimate_time_ms;
    oal_int8   c_pri20_idle_power;
    oal_int8   c_pri40_idle_power;
    oal_int8   c_pri80_idle_power;

    oal_uint32 ul_stats_cnt;
    oal_uint32 ul_meas_cnt;
    oal_uint32 ul_test_cnt;
}hal_ch_statics_irq_event_stru;

/* 对DMAC SCAN模块提供的硬件雷达检测信息结构体 */
typedef struct
{
    oal_uint8   uc_radar_type;
    oal_uint8   uc_radar_freq_offset;
    oal_uint8   uc_radar_bw;
    oal_uint8   uc_band;
    oal_uint8   uc_channel_num;
    oal_uint8   uc_working_bw;
    oal_uint8   auc_resv[2];
}hal_radar_det_event_stru;

typedef struct
{
    oal_uint32      ul_reg_band_info;
    oal_uint32      ul_reg_bw_info;
    oal_uint32      ul_reg_ch_info;
}hal_radar_irq_reg_list_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
/*
 *裸系统下针对接收，提供读取接口
 * frame_len长度
 * 802.11帧头长度(uc_mac_hdr_len)
*/
#pragma pack(push,1)

typedef struct
{
    /*word 0*/


    oal_uint8   bit_cipher_protocol_type  : 4;      /* ?????? */
    oal_uint8   bit_dscr_status           : 4;      /* ??????? */
    /*word 1*/


    oal_uint8   bit_channel_code          : 1;
    oal_uint8   bit_STBC                  : 2;
    oal_uint8   bit_GI                    : 1;
    oal_uint8   bit_rsvd                  : 1;
    oal_uint8   bit_AMPDU                 : 1;
    oal_uint8   bit_sounding_mode         : 2;
    /*word 2*/


    oal_uint8   bit_ext_spatial_streams   : 2;
    oal_uint8   bit_smoothing             : 1;
    oal_uint8   bit_freq_bandwidth_mode   : 4;
    oal_uint8   bit_preabmle              : 1;
    //oal_uint16  us_rx_frame_length;     /* ??hcc?? */
    /*word 3*/
    //oal_uint8   bit_amsdu_flag            : 1;              /* AMSDU?? */
    //oal_uint8   bit_buffer_start_flag     : 1;              /* AMSDU?,??MSDU?? */
    //oal_uint8   bit_frag_flag             : 1;              /* MSDU???? */
    oal_uint8   bit_reserved2             : 3;
    oal_uint8   bit_rsp_flag              : 1;


    oal_uint8   bit_column_number         : 4;

    /*word 4?5*/
    oal_uint16  us_channel_matrix_len;

    /* word 6 */

    oal_uint8   bit_code_book             : 2;   /* ???????? */
    oal_uint8   bit_grouping              : 2;
    oal_uint8   bit_row_number            : 4;
}hal_rx_status_stru;
#pragma pack(pop)

#else
/*
 *针对接收，提供读取接口
 * frame_len长度
 * 802.11帧头长度(uc_mac_hdr_len)
*/
typedef struct
{
    /*word 0*/
    oal_uint8   bit_dscr_status           : 4;     /* 描述符接收状态 */
    oal_uint8   bit_cipher_protocol_type  : 4;  /* 帧的加密类型*/
    oal_uint8   bit_ext_spatial_streams   : 2;
    oal_uint8   bit_smoothing             : 1;
    oal_uint8   bit_freq_bandwidth_mode   : 4;
    oal_uint8   bit_preabmle              : 1;
    oal_uint8   bit_channel_code          : 1;
    oal_uint8   bit_STBC                  : 2;
    oal_uint8   bit_GI                    : 1;
    oal_uint8   bit_reserved1             : 1;
    oal_uint8   bit_AMPDU                 : 1;
    oal_uint8   bit_sounding_mode         : 2;
    oal_uint8   uc_reserved1;
    /*word 1*/
    oal_uint8   bit_code_book             : 2;              /* 信道矩阵相关信息 */
    oal_uint8   bit_grouping              : 2;
    oal_uint8   bit_row_number            : 4;
    oal_uint8   bit_column_number         : 4;
    oal_uint8   bit_rsp_flag              : 3;
    oal_uint8   bit_reserved2             : 1;
    oal_uint16  us_channel_matrix_len;                   /* 信道矩阵长度 */
    /*word 2*/
    oal_uint32  ul_tsf_timestamp;                        /* TSF时间戳 */
    /*word 3*/

}hal_rx_status_stru;
#endif
/*
 * 针对接收，提供读取接口
 *
*/
typedef struct
{
    oal_uint32                    ul_skb_start_addr;
}hal_rx_addr_stru;

/*针对发送，提供设置接口*/
typedef struct
{
    oal_uint32                    ul_mac_hdr_start_addr;
    oal_uint32                    ul_skb_start_addr;
}hal_rx_ctrl_stru;

/*****************************************************************************
  7.6 对外部保留的VAP级接口列表，建议外部不做直接调用，而是调用对应的内联函数
*****************************************************************************/
typedef struct
{
    hal_to_dmac_vap_stru    st_vap_base;
    oal_uint32              ul_vap_base_addr;
}hal_vap_stru;

/*****************************************************************************
  结构名  : hal_rx_dscr_queue_header_stru
  结构说明: 接收描述符队列头的结构体
*****************************************************************************/
typedef struct
{
    oal_uint32                             *pul_element_head;   /* 指向接收描述符链表的第一个元素 */
    oal_uint32                             *pul_element_tail;   /* 指向接收描述符链表的最后一个元素 */
    oal_uint16                              us_element_cnt;     /* 接收描述符队列中元素的个数 */
    hal_dscr_queue_status_enum_uint8        uc_queue_status;    /* 接收描述符队列的状态 */
    oal_uint8                               auc_resv[1];
}hal_rx_dscr_queue_header_stru;
/*****************************************************************************
  结构名  : dmac_tx_dscr_queue_header_stru
  结构说明: 发送描述符队列头的结构体
*****************************************************************************/
typedef struct
{
    oal_dlist_head_stru                     st_header;          /* 发送描述符队列头结点 */
    hal_dscr_queue_status_enum_uint8        en_queue_status;    /* 发送描述符队列状态 */
    oal_uint8                               uc_ppdu_cnt;     /* 发送描述符队列中元素的个数 */
    oal_uint8                               auc_resv[2];
}hal_tx_dscr_queue_header_stru;

/*****************************************************************************
  结构名  : dmac_tx_dscr_queue_header_stru
  结构说明: 发送描述符队列头的结构体
*****************************************************************************/
typedef struct
{
    oal_uint8         uc_nulldata_awake;              /* AP时收到节能位为0的null data是否唤醒*/
    oal_uint8         uc_nulldata_phy_mode;           /* STA时发送null data的phy mode */
    oal_uint8         uc_nulldata_rate;               /* STA时发送null data的速率*/
    oal_uint8         uc_rsv[1];
    oal_uint32        ul_nulldata_interval;           /* STA时发送null data的间隔*/
    oal_uint32        ul_nulldata_address;            /* STA时发送null data的速率*/
    oal_uint32        ul_ap0_probe_resp_address;      /* AP0的probe response内存地址*/
    oal_uint32        ul_ap0_probe_resp_len;          /* AP0的probe response长度*/
    oal_uint32        ul_ap1_probe_resp_address;      /* AP1的probe response内存地址*/
    oal_uint32        ul_ap1_probe_resp_len;          /* AP1的probe response长度*/
    oal_uint8         uc_ap0_probe_resp_phy;          /* AP0的probe response发送phy模式*/
    oal_uint8         uc_ap0_probe_resp_rate;         /* AP0的probe response发送reate*/
    oal_uint8         uc_ap1_probe_resp_phy;          /* AP1的probe response发送phy模式*/
    oal_uint8         uc_ap1_probe_resp_rate;         /* AP1的probe response发送reate*/
}hal_wow_param_stru;

typedef enum
{
    HAL_WOW_PARA_EN                    = BIT0,
    HAL_WOW_PARA_NULLDATA              = BIT1,
    HAL_WOW_PARA_NULLDATA_INTERVAL     = BIT2,
    HAL_WOW_PARA_NULLDATA_AWAKE        = BIT3,
    HAL_WOW_PARA_AP0_PROBE_RESP        = BIT4,
    HAL_WOW_PARA_AP1_PROBE_RESP        = BIT5,

    HAL_WOW_PARA_BUTT
} hal_wow_para_set_enum;
typedef oal_uint32 hal_tx_status_enum_uint32;

/*****************************************************************************
  结构名  : hal_lpm_chip_state
  结构说明: 芯片低功耗状态枚举
*****************************************************************************/
typedef enum
{
    HAL_LPM_STATE_POWER_DOWN,
    HAL_LPM_STATE_IDLE,
    HAL_LPM_STATE_LIGHT_SLEEP,
    HAL_LPM_STATE_DEEP_SLEEP,
    HAL_LPM_STATE_NORMAL_WORK,
    HAL_LPM_STATE_WOW,

    HAL_LPM_STATE_BUTT
}hal_lpm_state_enum;
typedef oal_uint8 hal_lpm_state_enum_uint8;

/*****************************************************************************
  结构名  : hal_lpm_state_para
  结构说明: 芯片低功耗状态设置参数
*****************************************************************************/
typedef struct
{
    oal_uint8         uc_dtim_count;              /* 当前的DTIM count值，STA节能时设置相位*/
    oal_uint8         uc_dtim_period;
    oal_uint8         bit_gpio_sleep_en:1,        /* soc睡眠唤醒的方式,GPIO管脚方式使能*/
                      bit_soft_sleep_en:1,        /* soc睡眠睡眠的方式,软睡眠方式使能*/
                      bit_set_bcn_interval:1,     /* 是否调整beacon inter*/
                      bit_rsv          :6;
    oal_uint8         uc_rx_chain;               /* 接收通道值*/
    oal_uint32        ul_idle_bcn_interval;      /* idle状态下beaon inter*/
    oal_uint32        ul_sleep_time;             /* 软定时睡眠时间，单位ms*/
}hal_lpm_state_param_stru;


/*****************************************************************************
  结构名  : hal_cfg_rts_tx_param_stru
  结构说明: RTS设置发送参数
*****************************************************************************/
typedef struct
{
    wlan_legacy_rate_value_enum_uint8   auc_rate[HAL_TX_RATE_MAX_NUM];           /*发送速率，单位mpbs*/
    wlan_phy_protocol_enum_uint8        auc_protocol_mode[HAL_TX_RATE_MAX_NUM] ; /*协议模式, 取值参见wlan_phy_protocol_enum_uint8*/
    wlan_channel_band_enum_uint8        en_band;
    oal_uint8                           auc_recv[3];
}hal_cfg_rts_tx_param_stru;


/*****************************************************************************
  7.7 对外部保留的设备级接口列表，建议外部不做直接调用，而是调用对应的内联函数
*****************************************************************************/
typedef oal_void (* p_hal_alg_isr_func)(oal_uint8 uc_vap_id, oal_void *p_hal_to_dmac_device);

typedef struct
{

    oal_uint32      ul_phy_addr;
    oal_uint8       uc_status;
    oal_uint8       uc_q;
    oal_uint8       auc_resv[2];
    oal_uint32      ul_timestamp;

    oal_uint32      ul_arrive_time;     /* 下半部到来时间 */
    oal_uint32      ul_handle_time;     /* 下半部处理时间 */
    oal_uint32      ul_irq_cnt;
    oal_cpu_usage_stat_stru st_cpu_state;
}hal_rx_dpart_track_stru;

/* 保存硬件上报接收中断信息结构 */
typedef struct
{
    oal_dlist_head_stru         st_dlist_head;
    oal_uint32                 *pul_base_dscr;      /* 本次中断描述符地址 */
    oal_uint16                  us_dscr_num;        /* 接收到的描述符的个数 */
    //oal_bool_enum_uint8         en_used;
    oal_uint8                   uc_channel_num;     /* 本次中断时，所在的信道号 */
    oal_uint8                   uc_queue_id;
}hal_hw_rx_dscr_info_stru;
typedef struct tag_hal_to_dmac_chip_stru
{
    oal_uint8   uc_chip_id;
}hal_to_dmac_chip_stru;

typedef enum
{
    HAL_DFR_TIMER_STEP_1 = 0,
    HAL_DFR_TIMER_STEP_2 = 1,

}hal_dfr_timer_step_enum;
typedef oal_uint8 hal_dfr_timer_step_enum_uint8;

typedef struct
{
    frw_timeout_stru                 st_tx_prot_timer;        /* 检测无发送完成中断定时器 */
    hal_dfr_timer_step_enum_uint8    en_tx_prot_timer_step;   /* 超时标志，表明第几次超时 */
    oal_uint16                       us_tx_prot_time;         /* 超时时间 */
    oal_uint8                        auc_resv[1];
}hal_dfr_tx_prot_stru;

typedef struct
{
    oal_uint16    us_tbtt_cnt;   /* TBTT中断计数，每10次TBTT中断，将us_err_cnt清零 */
    oal_uint16    us_err_cnt;    /* 每10次TBTT中断，产生的MAC错误中断个数 */
}hal_dfr_err_opern_stru;

typedef struct
{
    oal_uint32                      ul_error1_val; /* 错误1中断状态 */
    oal_uint32                      ul_error2_val; /* 错误2中断状态 */
}hal_error_state_stru;

typedef struct
{
    oal_dlist_head_stru   st_entry;
    oal_uint32            ul_phy_addr;    /* 接收描述符物理地址 */
}witp_rx_dscr_recd_stru;


/*****************************************************************************
  结构名  : hal_phy_tpc_param_stru
  结构说明: PHY TPC寄存器参数, 在2.4G/5G频点切换时使用
*****************************************************************************/
typedef struct
{
    oal_uint32                      ul_pa_bias_addr;                             /* PA_BIAS地址 */
    oal_uint32                      aul_pa_bias_gain_code[WLAN_BAND_BUTT];       /* 2G/5G PA_BIAS CODE */
    oal_uint32                      ul_pa_addr;                             /* PA地址 */
    oal_uint32                      aul_pa_gain_code[WLAN_BAND_BUTT];       /* 2G/5G PAIN CODE */
    oal_uint32                      aul_2g_upc_addr[WLAN_2G_SUB_BAND_NUM];  /* 2G UPC地址 */
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint32                      aul_5g_upc_addr[WLAN_5G_SUB_BAND_NUM];  /* 5G UPC地址 */
#endif /* _PRE_WLAN_FEATURE_5G */

    oal_uint32                      aul_2g_upc1_data[WLAN_2G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 2G 通道1 UPC DATA */
    oal_uint32                      aul_2g_upc2_data[WLAN_2G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 2G 通道2 UPC DATA */
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint32                      aul_5g_upc1_data[WLAN_5G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 5G 通道1 UPC DATA */
    oal_uint32                      aul_5g_upc2_data[WLAN_5G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 5G 通道2 UPC DATA */
#endif /* _PRE_WLAN_FEATURE_5G */

    oal_uint32                      ul_dac_addr;                            /* DAC地址 */
    oal_uint32                      aul_dac_data[WLAN_BAND_BUTT];           /* 2G/5G DAC DATA */
    oal_uint32                      ul_lpf_addr;                            /* DAC地址 */
    oal_uint32                      aul_lpf_data[WLAN_BAND_BUTT];           /* 2G/5G LPF DATA */
    oal_uint8                       auc_2g_cali_upc_code[2][WLAN_2G_SUB_BAND_NUM];/* 2G校准的UPC Code */
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint8                       auc_5g_cali_upc_code[2][WLAN_5G_CALI_SUB_BAND_NUM];  /* 5G校准的UPC Code(区分20M和80M) */
#endif /* _PRE_WLAN_FEATURE_5G */
    oal_uint8                       auc_reserve_addr[2];

    /*不同帧的tpc code*/
    oal_uint32                      aul_2g_ofdm_ack_cts_tpc_code[WLAN_2G_SUB_BAND_NUM];
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint32                      aul_5g_ack_cts_tpc_code[WLAN_5G_SUB_BAND_NUM];
#endif /* _PRE_WLAN_FEATURE_5G */

    oal_uint8                       auc_2g_dsss_ack_cts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_rts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_one_pkt_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_selfcts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_cfend_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_null_data_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_cfend_tpc_code[WLAN_2G_SUB_BAND_NUM];
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint8                       auc_5g_rts_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_one_pkt_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_abort_cfend_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_cfend_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_ndp_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_vht_report_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_abort_null_data_tpc_code[WLAN_5G_SUB_BAND_NUM];
#else
    oal_uint8                       auc_reserve[1];
#endif /* _PRE_WLAN_FEATURE_5G */
    /*读取不同帧格式的速率*/
    oal_uint32                      ul_rate_ofdm_ack_cts;
    oal_uint8                       uc_rate_rts;
    oal_uint8                       uc_rate_one_pkt;
    oal_uint8                       uc_rate_abort_selfcts;
    oal_uint8                       uc_rate_abort_cfend;
    oal_uint8                       uc_rate_cfend;
    oal_uint8                       uc_rate_ndp;
    oal_uint8                       uc_rate_vht_report;
    oal_uint8                       uc_rate_abort_null_data;
}hal_phy_tpc_param_stru;

#ifdef _PRE_WLAN_FEATURE_DFS
typedef struct
{
    oal_bool_enum_uint8  en_chirp_enable;
    oal_uint8            auc_resv[3];
    oal_uint32           ul_chirp_time_threshold;
    oal_uint32           ul_chirp_cnt_threshold;
    oal_uint32           ul_time_threshold;
    oal_uint32           ul_last_burst_timestamp;
    oal_uint32           ul_last_burst_timestamp_for_chirp;
}hal_dfs_radar_filter_stru;
#endif

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
typedef struct
{
    oal_uint16     us_max_offset_tsf;     /* 最长耗时的时间 */
    oal_uint16     us_mpdu_len;           /* 最长耗时的mpdu长度 */
    oal_uint16     us_tx_excp_cnt;        /* 发送完成耗时异常统计 */
    oal_uint8      uc_q_num;              /* 最长耗时的q_num*/
    oal_uint8      auc_resv;
}hal_tx_excp_info_stru;
#endif

typedef struct
{
    oal_uint32          ul_tkipccmp_rep_fail_cnt;    /* 重放攻击检测计数TKIP + CCMP */
    oal_uint32          ul_tx_mpdu_cnt;              /* 发送计数非ampdu高优先级 + 普通优先级 + ampdu中mpdu */
    oal_uint32          ul_rx_passed_mpdu_cnt;       /* 属于AMPDU MPDU的FCS正确的MPDU数量 */
    oal_uint32          ul_rx_failed_mpdu_cnt;       /* 属于AMPDU MPDU的FCS错误的MPDU数量 */
    oal_uint32          ul_rx_tkipccmp_mic_fail_cnt; /* kip mic + ccmp mic fail的帧数 */
    oal_uint32          ul_key_search_fail_cnt;      /* 接收key serach fail的帧数 */
}hal_mac_key_statis_info_stru;
typedef struct tag_hal_to_dmac_device_stru
{
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_mac_device_id;                           /* 保存mac device id */
    hal_lpm_state_enum_uint8        uc_curr_state;                              /*当前芯片的低功耗状态*/
    oal_uint32                      ul_core_id;

#if ((_PRE_PRODUCT_ID !=_PRE_PRODUCT_ID_HI1131C_DEV) && (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_HOST))
    oal_dlist_head_stru             ast_rx_dscr_hash[HAL_RX_MAX_BUFFS];   /*  */
#endif

    hal_dfr_tx_prot_stru            st_dfr_tx_prot;                             /* 用于无法送完成中断检测及恢复 */
    hal_dfr_err_opern_stru          st_dfr_err_opern[HAL_MAC_ERROR_TYPE_BUTT];  /* 用于MAC异常中断恢复 */

    hal_rx_dscr_queue_header_stru   ast_rx_dscr_queue[HAL_RX_QUEUE_NUM];
    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue[HAL_TX_QUEUE_NUM];

#ifdef _PRE_DEBUG_MODE
    /* 记录接收描述符队列中，各个描述符的地址 */
    witp_rx_dscr_recd_stru          st_nor_rx_dscr_recd[HAL_NORMAL_RX_MAX_BUFFS];
    witp_rx_dscr_recd_stru          st_hi_rx_dscr_recd[HAL_HIGH_RX_MAX_BUFFS];
#endif

    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue_fake[HAL_TX_FAKE_QUEUE_NUM][HAL_TX_QUEUE_NUM];

    oal_uint32                      ul_rx_normal_dscr_cnt;

    oal_uint32                      ul_track_stop_flag;
    oal_uint8                       uc_al_tx_flag;
    oal_uint8                       uc_fcc_country;            /* 0:表示非FCC认证国家，1:表示FCC认证国家 */
    oal_uint8                       uc_full_phy_freq_user_cnt; //device下需要满频的vap(ap)/sta(user) 个数
    oal_uint8                       uc_over_temp;
    oal_uint32                      bit_al_tx_flag        :3;  /*0: 关闭常发; 1:保留给RF测试; 2: ampdu聚合帧常发; 3:非聚合帧常发*/
    oal_uint32                      bit_al_rx_flag        :3;  /*0: 关闭常收; 1:保留给RF测试；2: ampdu聚合帧常收; 3:非聚合帧常收*/
    oal_uint32                      bit_one_packet_st     :1;  /* 0表示DBC结束 1表示DBAC正在执行 */
    oal_uint32                      bit_clear_fifo_st     :1;  /* 0表示无clear fifo状态，1表示clear fifo状态 */
    oal_uint32                      bit_al_txrx_ampdu_num :8;  /*指示用于常发常收的聚合帧数目*/
    oal_uint32                      bit_track_cnt         :8;  /* 遇到qempty 剩余记录条目数 */
    oal_uint32                      bit_track_cnt_down    :8;  /* 剩余记录条目减少标志 */
    oal_netbuf_stru *               pst_alrx_netbuf;           /* 记录常收时，描述符所共用的内存 */
    oal_uint32                      ul_rx_normal_mdpu_succ_num;
    oal_uint32                      ul_rx_ampdu_succ_num;
    oal_uint32                      ul_tx_ppdu_succ_num;
    oal_uint32                      ul_rx_ppdu_fail_num;
    oal_uint32                      ul_tx_ppdu_fail_num;
#ifdef _PRE_DEBUG_MODE
    oal_uint32                      ul_dync_txpower_flag;
#endif

    oal_dlist_head_stru             ast_rx_isr_info_list[HAL_HW_RX_DSCR_LIST_NUM];

    hal_hw_rx_dscr_info_stru        ast_rx_isr_info_member[HAL_HW_RX_ISR_INFO_MAX_NUMS];

    oal_dlist_head_stru             st_rx_isr_info_res_list;  /* 接收中断信息存储资源链表 */
    oal_uint8                       uc_current_rx_list_index;
    oal_uint8                       uc_current_chan_number;
    wlan_p2p_mode_enum_uint8        en_p2p_mode;               /* 指示当前创建的P2P 是处于CL/GO 模式。由于P2P 中断产生后只能通过创建的P2P 设备是CL 还是GO 来获取对应的hal_vap_id，所以增加该变量 */
    oal_bool_enum_uint8             en_rx_intr_fifo_resume_flag;    /* RX INTR FIFO OVERRUN是否恢复标识 */

#ifdef _PRE_DEBUG_MODE
    /* 原始描述符物理地址 */
    oal_uint32                      aul_nor_rx_dscr[HAL_NORMAL_RX_MAX_BUFFS];
    oal_uint32                      aul_hi_rx_dscr[HAL_HIGH_RX_MAX_BUFFS];

    oal_uint32                      ul_dpart_save_idx;
    oal_uint32                      ul_rx_irq_loss_cnt;
    hal_rx_dpart_track_stru         ast_dpart_track[HAL_DOWM_PART_RX_TRACK_MEM];

    /* 描述符异常还回统计 */
    oal_uint32                      ul_exception_free;
    oal_uint32                      ul_irq_cnt;

#endif
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    oam_user_track_rx_ampdu_stat    st_user_track_rx_ampdu_stat;
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
    hal_dfs_radar_filter_stru       st_dfs_radar_filter;
#endif

    /* TPC相关PHY参数*/
    hal_phy_tpc_param_stru          st_phy_tpc_param;

    /* RTS速率相关参数 */
    wlan_legacy_rate_value_enum_uint8   auc_rts_rate[WLAN_BAND_BUTT][HAL_TX_RATE_MAX_NUM];      /* 两个频段的RTS发送速率 */
    wlan_phy_protocol_enum_uint8        auc_rts_protocol[WLAN_BAND_BUTT][HAL_TX_RATE_MAX_NUM] ; /* 两个频段的RTS协议模式 */

    /* 字节对齐 */
    p_hal_alg_isr_func  pa_hal_alg_isr_func_table[HAL_ISR_TYPE_BUTT][HAL_ALG_ISR_NOTIFY_BUTT];

    oal_uint8                       *puc_mac_reset_reg;
    oal_uint8                       *puc_phy_reset_reg;
    oal_uint16                      uc_cali_check_hw_status;    /*FEM&PA失效检测*/
    oal_int16                       s_always_rx_rssi;

    hal_wifi_channel_status_stru   st_wifi_channel_status;
    oal_uint32                          ul_rx_rate;
    oal_int32                           l_rx_rssi;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_btble_status_stru   st_btcoex_btble_status;
    hal_btcoex_wifi_status_stru    st_btcoex_wifi_status;
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
    oal_uint32                     ul_lte_coex_status;
#endif
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
    hal_tx_excp_info_stru          st_tx_excp_info;
#endif

} hal_to_dmac_device_stru;




/* HAL模块和DMAC模块共用的WLAN RX结构体 */
typedef struct
{
    oal_uint32                 *pul_base_dscr;      /* 描述符基地址 */
    oal_bool_enum_uint8         en_sync_req;        /* 队列同步标识 */
    oal_uint16                  us_dscr_num;        /* 接收到的描述符的个数 */
    oal_uint8                   uc_queue_id;        /* 接收队列号 */
    hal_to_dmac_device_stru    *pst_hal_device;
    oal_uint8                   uc_channel_num;
    oal_uint8                   auc_resv[3];
}hal_wlan_rx_event_stru;

typedef struct
{
    hal_tx_dscr_stru        *pst_base_dscr;/* 发送完成中断硬件所上报的描述符指针 */
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint8                uc_dscr_num; /* 硬件一次发送所发出的描述符个数 */

    oal_uint8                auc_resv[3];
}hal_tx_complete_event_stru;

typedef struct
{
    hal_error_state_stru            st_error_state;
    hal_to_dmac_device_stru        *pst_hal_device;
}hal_error_irq_event_stru;

typedef struct
{
    oal_uint8                       p2p_noa_status; /* 0: 表示noa 定时器停止，1: 表示noa 定时器正在工作 */
    oal_uint8                       auc_resv[3];
}hal_p2p_pm_event_stru;


/*****************************************************************************
  10.2 对外暴露的配置接口
*****************************************************************************/
/************************  1151  ********************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define HAL_CHIP_LEVEL_FUNC_EXTERN
extern oal_uint32 hal_chip_get_device_num_impl(oal_bus_dev_stru * pst_bus_stru, oal_uint8 * puc_device_nums);
#define HAL_DEVICE_LEVEL_FUNC_EXTERN
extern oal_uint32 hal_chip_get_device_impl(oal_bus_dev_stru * pst_bus_stru, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_device_stru);
extern oal_void hi1151_get_chip_version(hal_to_dmac_chip_stru *pst_hal_chip, oal_uint32 *pul_chip_ver);
extern oal_void hi1151_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_hal_device,oal_uint8 uc_set_hw);
extern oal_void  hi1151_rx_dscr_add_netbuf(hal_to_dmac_device_stru *pst_device, oal_uint32  *pul_ret);
extern oal_void  hi1151_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_buff);
extern oal_void hi1151_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device,oal_uint8 uc_destroy_netbuf);
extern oal_void hi1151_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1151_al_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_device);

extern oal_void hi1151_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_tx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1151_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_free_rx_isr_list(oal_dlist_head_stru  *pst_rx_isr_list);
extern oal_void hi1151_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_get_tx_dscr_queue_total_ppdu_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 *pus_ppdu_cnt);
extern oal_void hi1151_tx_fill_basic_ctrl_dscr(hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu);
extern oal_void hi1151_tx_ctrl_dscr_link(hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1151_get_tx_dscr_next(hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next);
extern oal_void hi1151_tx_ctrl_dscr_unlink(hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1151_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1151_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1151_tx_set_dscr_modify_mac_header_length(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length);
extern oal_void hi1151_tx_set_dscr_seqno_sw_generate(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate);
extern oal_void hi1151_tx_get_size_dscr(oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size);
extern oal_void hi1151_tx_get_vap_id(hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id, oal_int32 l_proxysta_feature);
extern oal_void hi1151_tx_get_dscr_ctrl_one_param(hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param);
extern oal_void hi1151_tx_get_dscr_seq_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num);
extern oal_void  hi1151_tx_get_dscr_tx_cnt(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count);
extern oal_void hi1151_tx_get_dscr_mpdu_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_mpdu_num);
extern oal_void hi1151_tx_set_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status);
extern oal_void hi1151_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id);
extern oal_void hi1151_tx_get_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status);
extern oal_void  hi1151_tx_get_dscr_send_rate_rank(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank);
extern oal_void hi1151_tx_get_dscr_ba_ssn(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn);
extern oal_void hi1151_tx_get_dscr_ba_bitmap(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap);
extern oal_void hi1151_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr);
extern oal_void hi1151_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum);
extern oal_void hi1151_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_void hi1151_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode);
#endif
extern oal_void hi1151_rx_get_size_dscr(oal_uint32 * pul_dscr_size);
extern oal_void hi1151_rx_get_info_dscr(oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics);
extern oal_void hi1151_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap);
extern oal_void hi1151_rx_get_netbuffer_addr_dscr(oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr);
extern oal_void hi1151_rx_get_mac_hdr_addr_dscr(oal_uint32 *pul_rx_dscr, oal_uint32 ** ppul_mac_hdr_address_dscr);
extern oal_void hi1151_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type);
extern oal_void hi1151_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num);
extern oal_void hi1151_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr);
extern oal_void hi1151_dump_rx_dscr(oal_uint32 *pul_rx_dscr);
extern oal_void hi1151_dump_tx_dscr(oal_uint32 *pul_tx_dscr);
extern oal_void hi1151_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val);
extern oal_void hi1151_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void hi1151_resume_mac_rx_dscr_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_uint32 hi1151_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device,
                                                        oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void hi1151_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                     oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg);
extern oal_void hi1151_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_initialize_machw(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth);

#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1151_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1151_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num);
#endif
extern oal_void hi1151_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1151_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_HW_TEST
extern oal_void hi1151_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_void hi1151_freq_adjust(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_pll_int, oal_uint16 us_pll_frac);
#endif

extern oal_void hi1151_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain);
extern oal_void hi1151_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size);
extern oal_void hi1151_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1151_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
										 oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para);
extern oal_void hi1151_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                             oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para);
extern oal_void hi1151_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag);
extern oal_void hi1151_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write);
extern oal_void hi1151_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read);
extern oal_void hi1151_reset_init(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_reset_destroy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1151_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1151_reset_reg_dma_save(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1151_reset_reg_dma_restore(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1151_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_initialize_phy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain);
extern oal_void hi1151_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device);
#ifdef _PRE_WLAN_REALTIME_CALI
extern oal_void hi1151_rf_cali_realtime(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_freq, oal_uint8 uc_chn_idx, oal_uint8 uc_bandwidth, oal_uint8 uc_protocol);
#endif
extern oal_void  hi1151_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status);

extern oal_void hi1151_initialize_soc(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status);
extern oal_void hi1151_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1151_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state);
extern oal_void hi1151_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1151_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1151_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1151_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param);
extern oal_void hi1151_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_irq_stat(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 *puc_param, oal_uint32 ul_len, oal_uint8 uc_type);
extern oal_void hi1151_get_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1151_add_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1151_del_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id);

extern oal_void hi1151_set_proxysta_enable(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void hi1151_set_proxysta_vap_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 vap_id, oal_uint8 *puc_mac_addr);
#endif
extern oal_void hi1151_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol);
extern oal_void hi1151_register_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                           hal_alg_noify_enum_uint8 en_alg_notify,p_hal_alg_isr_func p_func);
extern oal_void hi1151_unregister_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                             hal_alg_noify_enum_uint8 en_alg_notify);
extern oal_void hi1151_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg);
extern oal_void hi1151_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status);
extern oal_void hi1151_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1151_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1151_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1151_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val);
extern oal_void hi1151_get_all_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_val);
extern oal_void hi1151_get_ampdu_bytes(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes);
extern oal_void hi1151_get_rx_err_count(hal_to_dmac_device_stru* pst_hal_device,
                                        oal_uint32* pul_cnt1,
                                        oal_uint32* pul_cnt2,
                                        oal_uint32* pul_cnt3,
                                        oal_uint32* pul_cnt4,
                                        oal_uint32* pul_cnt5,
                                        oal_uint32* pul_cnt6);
extern oal_void hi1151_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type);
extern oal_void hi1151_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr);
extern oal_void hi1151_disable_ce(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
extern oal_void hi1151_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr);
extern oal_void hi1151_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx);
extern oal_void hi1151_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
extern oal_void hi1151_tx_get_dscr_phy_mode_one(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_phy_mode_one);
extern oal_void hi1151_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index);
extern oal_void hi1151_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
#endif
extern oal_void hi1151_get_rate_80211g_table(oal_void **pst_rate);
extern oal_void hi1151_get_rate_80211g_num(oal_uint32 *pst_data_num);
extern oal_void hi1151_get_hw_addr(oal_uint8 *puc_addr);
extern oal_void hi1151_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period);
extern oal_void hi1151_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period);
extern oal_void hi1151_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1151_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1151_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void hi1151_set_improve_ce_threshold(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void hi1151_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info);
extern oal_void hi1151_update_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param);
extern oal_void hi1151_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1151_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp);
extern oal_void hi1151_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode);
extern oal_void  hi1151_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code, oal_int8 *pac_tpc_level_table,
        oal_uint8 uc_tpc_level_num, oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table, oal_int16 *pas_other_gain_table,wlan_channel_band_enum_uint8 en_freq_band);
extern oal_void  hi1151_get_bcn_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint8 *puc_data_rate);
extern oal_void hi1151_set_bcn_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_tpc_code, oal_uint8 uc_vap_id);
extern oal_void  hi1151_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1151_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param);
extern oal_void hi1151_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2);
extern oal_void hi1151_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2);
extern oal_void hi1151_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void hi1151_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void  hi1151_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1151_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx);
extern oal_void  hi1151_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate,
       oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx);
#ifdef _PRE_WLAN_REALTIME_CALI
extern oal_void  hi1151_get_tpc_cali_upc_gain_in_rf_list(oal_int8* pac_upc_gain_in_rf_list);
#endif
#endif
extern oal_void hi1151_irq_affinity_init(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_core_id);
#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hi1151_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix);
extern oal_void hi1151_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix);
extern oal_void hi1151_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1151_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1151_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1151_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1151_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time);
extern oal_void hi1151_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration);
extern oal_void hi1151_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_group_id);
extern oal_void hi1151_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1151_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1151_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1151_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);
extern oal_void hi1151_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_val);
extern oal_void hi1151_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_mac_addr,oal_uint8 uc_lut_index);
extern oal_void hi1151_set_mu_aid_matrix_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint16 us_aid, oal_uint8 *p_matrix);
extern oal_void hi1151_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1151_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);

#endif

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
extern oal_void hi1151_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_device, oal_int32 l_reg_val);
extern oal_void hi1151_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val);
extern oal_void hi1151_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint16 us_obss_dur);
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
extern oal_void hi1151_set_counter1_clear(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_txrx_frame_time(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_reg_val);
extern oal_void hi1151_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable);
#endif
extern oal_void hi1151_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis);
#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_void hi1151_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *pl_ed_high_reg_val);
extern oal_void hi1151_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val);
extern oal_void hi1151_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val);
extern oal_void hi1151_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val);
extern oal_void hi1151_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val);

#endif
extern oal_void hi1151_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle);
extern oal_void hi1151_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void  hi1151_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count);
extern oal_void  hi1151_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval);
extern oal_void  hi1151_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1151_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1151_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void hi1151_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
#endif
#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1151_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_partial_aid);
#endif
extern oal_void hi1151_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para);
extern oal_void hi1151_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para);
extern oal_void hi1151_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en);
extern oal_void hi1151_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl);
extern oal_void hi1151_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num);

#ifdef _PRE_DEBUG_MODE
extern oal_void hi1151_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device);
#endif

extern oal_void hi1151_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect);
extern oal_void hi1151_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
#ifdef _PRE_WLAN_PHY_PLL_DIV
extern oal_void hi1151_rf_set_freq_skew(oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[]);
#endif
extern oal_void hi1151_rf_adjust_ppm(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_ppm, wlan_channel_bandwidth_enum_uint8  en_bandwidth, oal_uint8 uc_clock);
extern oal_void hi1151_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth);
extern oal_void hi1151_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value);
extern oal_void hi1151_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value);
#ifdef _PRE_WLAN_HW_TEST
extern oal_void hi1151_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
#endif
extern oal_void hi1151_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val);
extern oal_void hi1151_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
extern oal_void  hi1151_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value);
extern oal_void  hi1151_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period);
extern oal_void  hi1151_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val);
extern oal_void  hi1151_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device);

#define HAL_VAP_LEVEL_FUNC_EXTERN
extern oal_void hi1151_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo);
extern oal_void hi1151_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo);
extern oal_void hi1151_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo);
extern oal_void hi1151_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo);
extern oal_void hi1151_vap_send_beacon_pkt(hal_to_dmac_vap_stru *pst_hal_vap, hal_beacon_tx_params_stru *pst_params);
extern oal_void hi1151_vap_set_beacon_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_rate);
extern oal_void hi1151_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate);
extern oal_void hi1151_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr);
extern oal_void hi1151_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);

extern oal_void hi1151_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);
extern oal_void hi1151_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo);
extern oal_void hi1151_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                            wlan_wme_ac_type_enum_uint8   en_ac,
                                            oal_uint8                     uc_aifs);
extern oal_void hi1151_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ac_type);
extern oal_void hi1151_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ac_type);
#if 0
extern oal_void hi1151_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
#endif
extern oal_void hi1151_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1151_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1151_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1151_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1151_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1151_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1151_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1151_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1151_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable);
extern oal_void hi1151_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value);
extern oal_void hi1151_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value);
extern oal_void hi1151_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1151_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1151_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period);
extern oal_void  hi1151_sta_tsf_save(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_need_restore);
extern oal_void  hi1151_sta_tsf_restore(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void  hi1151_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void  hi1151_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window);
extern oal_void hi1151_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru * pst_hal_vap,
                oal_bool_enum_uint8 en_suspend_enable);
#endif
extern oal_void hi1151_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte);
extern oal_void  hi1151_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim);
extern oal_void hi1151_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period);
extern oal_void hi1151_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period);

extern oal_void  hi1151_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *uc_dtim_count);
extern oal_void  hi1151_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count);
extern oal_void hi1151_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count);
extern oal_void  hi1151_pm_wlan_servid_register(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint32 *pul_ret);
extern oal_void hi1151_pm_wlan_servid_unregister(hal_to_dmac_vap_stru  *pst_hal_vap);
extern oal_void hi1151_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_keyid);
extern oal_void hi1151_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val);
extern oal_void  hi1151_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void  hi1151_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void  hi1151_get_beacon_miss_status(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1151_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type);
extern oal_void hi1151_psm_rf_sleep (hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
extern oal_void hi1151_psm_rf_awake (hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg);
extern oal_void hi1151_rx_dscr_opt_reset_normal(hal_to_dmac_device_stru * pst_device);
#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))

/************************  1102  CHIP********************************************/
#define HAL_CHIP_LEVEL_FUNC_EXTERN
extern oal_void hi1102_get_chip_version(hal_to_dmac_chip_stru *pst_hal_chip, oal_uint32 *pul_chip_ver);
/************************  1102  DEVICE********************************************/
#define HAL_DEVICE_LEVEL_FUNC_EXTERN
extern oal_void hi1102_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_set_hw);
extern oal_void hi1102_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device,oal_uint8 uc_destroy_netbuf);
extern oal_void hi1102_al_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_device);

extern oal_void hi1102_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1102_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_tx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1102_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_free_rx_isr_list(oal_dlist_head_stru  *pst_rx_isr_list);
extern oal_void hi1102_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);

extern oal_void hi1102_tx_fill_basic_ctrl_dscr(hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu);
extern oal_void hi1102_tx_ctrl_dscr_link(hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1102_get_tx_dscr_next(hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next);
extern oal_void hi1102_tx_ctrl_dscr_unlink(hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1102_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1102_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1102_tx_set_dscr_modify_mac_header_length(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length);
extern oal_void hi1102_tx_set_dscr_seqno_sw_generate(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate);
extern oal_void hi1102_tx_get_size_dscr(oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size);
extern oal_void hi1102_tx_get_vap_id(hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id, oal_int32 l_proxysta_feature);
extern oal_void hi1102_tx_get_dscr_ctrl_one_param(hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param);
extern oal_void hi1102_tx_get_dscr_seq_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num);
extern oal_void hi1102_tx_get_dscr_tx_cnt(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count);
extern oal_void hi1102_tx_set_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status);
extern oal_void hi1102_tx_get_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status);
extern oal_void  hi1102_tx_get_dscr_send_rate_rank(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank);
extern oal_void hi1102_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id);
extern oal_void hi1102_tx_get_dscr_ba_ssn(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn);
extern oal_void hi1102_tx_get_dscr_ba_bitmap(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap);
extern oal_void hi1102_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr);
extern oal_void hi1102_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum);
extern oal_void hi1102_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len);
#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_void hi1102_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode);
#endif
extern oal_void hi1102_rx_get_info_dscr(oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics);
extern oal_void hi1102_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap);
extern oal_void hi1102_rx_get_netbuffer_addr_dscr(oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr);
extern oal_void hi1102_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type);
extern oal_void hi1102_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num);
extern oal_void hi1102_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr);
extern oal_void hi1102_dump_tx_dscr(oal_uint32 *pul_tx_dscr);
extern oal_void hi1102_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val);
extern oal_void hi1102_reg_write16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 us_val);
extern oal_void hi1102_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_uint32 hi1102_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void  hi1102_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_dscr_num);
extern oal_void hi1102_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                     oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg);
extern oal_void hi1102_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1102_initialize_machw(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1102_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1102_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num);
#endif
extern oal_void hi1102_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1102_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_PHY_PERFORMANCE
extern oal_void hi1102_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac);
#endif

extern oal_void hi1102_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain);
extern oal_void hi1102_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size);
extern oal_void hi1102_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                        oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para);
extern oal_void hi1102_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                             oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para);
extern oal_void hi1102_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag);
extern oal_void hi1102_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write);
extern oal_void hi1102_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read);
extern oal_void hi1102_reset_init(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_reset_destroy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1102_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1102_reset_reg_dma_save(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1102_reset_reg_dma_restore(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1102_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_initialize_phy(hal_to_dmac_device_stru * pst_hal_device);
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
extern oal_void hi1102_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain);
#endif
extern oal_void hi1102_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device);
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
extern oal_void hi1102_set_rf_custom_reg(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_void hi1102_cali_send_func(oal_uint8* puc_cali_data);
extern oal_void hi1102_psm_rf_sleep (hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
extern oal_void hi1102_psm_rf_awake (hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg);
extern oal_void hi1102_initialize_soc(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status);
extern oal_void hi1102_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1102_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state);
extern oal_void hi1102_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1102_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1102_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1102_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param);
extern oal_void hi1102_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device);

extern oal_void hi1102_get_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1102_add_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1102_del_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id);

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_void hi1102_dpd_cali_func(oal_uint8 u_functype, oal_uint32* pul_status, oal_uint32* hi1102_dpd_cal_data_read, oal_uint32* hi1102_dpd_cal_data_write);
#endif

extern oal_void hi1102_set_proxysta_enable(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void hi1102_set_proxysta_vap_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 vap_id, oal_uint8 *puc_mac_addr);
#endif
extern oal_void hi1102_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol);
extern oal_void hi1102_register_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                           hal_alg_noify_enum_uint8 en_alg_notify,p_hal_alg_isr_func p_func);
extern oal_void hi1102_unregister_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                             hal_alg_noify_enum_uint8 en_alg_notify);
extern oal_void hi1102_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg);
extern oal_void hi1102_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status);
extern oal_void hi1102_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1102_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1102_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val);
extern oal_void hi1102_reg_info16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 *pus_val);
extern oal_void hi1102_get_all_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_val);
extern oal_void hi1102_get_ampdu_bytes(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes);
extern oal_void hi1102_get_rx_err_count(hal_to_dmac_device_stru* pst_hal_device,
                                        oal_uint32* pul_cnt1,
                                        oal_uint32* pul_cnt2,
                                        oal_uint32* pul_cnt3,
                                        oal_uint32* pul_cnt4,
                                        oal_uint32* pul_cnt5,
                                        oal_uint32* pul_cnt6);
extern oal_void hi1102_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type);
extern oal_void hi1102_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_pmf_crypto(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_crypto);
extern oal_void hi1102_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr);
extern oal_void hi1102_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
extern oal_void hi1102_disable_ce(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr);
extern oal_void hi1102_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx);
extern oal_void hi1102_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
extern oal_void hi1102_tx_get_dscr_phy_mode_one(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_phy_mode_one);
extern oal_void hi1102_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index);
extern oal_void hi1102_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
#endif
extern oal_void hi1102_get_rate_80211g_table(oal_void **pst_rate);
extern oal_void hi1102_get_rate_80211g_num(oal_uint32 *pst_data_num);
extern oal_void hi1102_get_hw_addr(oal_uint8 *puc_addr);
extern oal_void hi1102_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period);
extern oal_void hi1102_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period);
extern oal_void hi1102_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1102_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
extern oal_void hi1102_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
#endif
extern oal_void hi1102_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void  hi1102_set_improve_ce_threshold(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_val);
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
extern oal_void hi1102_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info);
#endif
extern oal_void hi1102_update_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param);
extern oal_void hi1102_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void  hi1102_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp);
extern oal_void  hi1102_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode);
extern oal_void  hi1102_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code,
            oal_int8  *pac_tpc_level_table, oal_uint8 uc_tpc_level_num,
            oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table,
            oal_int16 *pas_other_gain_table,wlan_channel_band_enum_uint8 en_freq_band);

extern oal_void  hi1102_get_bcn_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint8 *puc_data_rate);
extern oal_void  hi1102_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_bcn_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_tpc_code, oal_uint8 uc_vap_id);
extern oal_void hi1102_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1102_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param);
extern oal_void hi1102_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2);
extern oal_void hi1102_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2);
extern oal_void hi1102_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void hi1102_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
      oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
      oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void  hi1102_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1102_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx);
extern oal_void  hi1102_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate,
       oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx);

#endif
extern oal_void hi1102_irq_affinity_init(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_core_id);

#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hi1102_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix);
extern oal_void hi1102_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix);
extern oal_void hi1102_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1102_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1102_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1102_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1102_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time);
extern oal_void hi1102_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration);
extern oal_void hi1102_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_group_id);
extern oal_void hi1102_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1102_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1102_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);
extern oal_void hi1102_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_mac_addr,oal_uint8 uc_lut_index);
extern oal_void hi1102_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1102_set_mu_aid_matrix_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint16 us_aid, oal_uint8 *p_matrix);
extern oal_void hi1102_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1102_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);

#endif

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
extern oal_void hi1102_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_device, oal_int32 l_reg_val);
extern oal_void hi1102_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val);
extern oal_void hi1102_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint32 us_obss_dur);
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
extern oal_void hi1102_set_counter1_clear(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_get_txrx_frame_time(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * ul_reg_val);
extern oal_void hi1102_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable);
#endif
extern oal_void hi1102_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis);
#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_void hi1102_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *l_ed_high_reg_val);
extern oal_void hi1102_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val);
extern oal_void hi1102_set_cca_opt_stat(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 debug_mode);
extern oal_void hi1102_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val);
extern oal_void hi1102_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val);
extern oal_void hi1102_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val);
#endif
extern oal_void  hi1102_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle);
extern oal_void hi1102_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void  hi1102_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval);
extern oal_void  hi1102_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count);
extern oal_void hi1102_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1102_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1102_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period);
extern oal_void hi1102_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val);
#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1102_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void hi1102_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
#endif
#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1102_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_partial_aid);
#endif
extern oal_void hi1102_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para);
extern oal_void hi1102_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para);
extern oal_void hi1102_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en);
extern oal_void hi1102_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl);
extern oal_void hi1102_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num);

#ifdef _PRE_DEBUG_MODE
extern oal_void hi1102_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_void hi1102_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect);
extern oal_void hi1102_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
#ifdef _PRE_WLAN_PHY_PLL_DIV
extern oal_void hi1102_rf_set_freq_skew(oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[]);
#endif
extern oal_void hi1102_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth);
extern oal_void hi1102_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value);
extern oal_void hi1102_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value);

#ifdef _PRE_WLAN_ASIC_RF_TEST
extern oal_void hi1102_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
#endif

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void hi1102_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
extern oal_void hi1102_get_pwr_comp_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tx_ratio, oal_int16 * ps_pwr_comp_val);
extern oal_void hi1102_over_temp_handler(hal_to_dmac_device_stru *pst_hal_device);

#endif

extern oal_void hi1102_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val);
extern oal_void hi1102_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
extern oal_void  hi1102_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value);
extern oal_void  hi1102_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device);

#define HAL_VAP_LEVEL_FUNC_EXTERN
extern oal_void hi1102_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo);
extern oal_void hi1102_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo);
extern oal_void hi1102_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo);
extern oal_void hi1102_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo);
extern oal_void hi1102_vap_send_beacon_pkt(hal_to_dmac_vap_stru *pst_hal_vap, hal_beacon_tx_params_stru *pst_params);
extern oal_void hi1102_vap_set_beacon_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_rate);
extern oal_void hi1102_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate);


extern oal_void hi1102_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr);
extern oal_void hi1102_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);

extern oal_void hi1102_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);
extern oal_void hi1102_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo);
extern oal_void hi1102_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                            wlan_wme_ac_type_enum_uint8   en_ac,
                                            oal_uint8                     uc_aifs);
extern oal_void  hi1102_vap_set_machw_aifsn_ac_wfa(hal_to_dmac_vap_stru         *pst_hal_vap,
                                      wlan_wme_ac_type_enum_uint8   en_ac,
                                      oal_uint8                     uc_aifs,
                                      wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1102_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ac_type);
extern oal_void  hi1102_vap_set_edca_machw_cw_wfa(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmaxmin, oal_uint8 uc_ac_type, wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1102_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ac_type);
#if 0
extern oal_void hi1102_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
#endif
extern oal_void hi1102_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);


extern oal_void hi1102_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1102_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1102_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1102_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1102_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1102_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1102_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1102_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable);
extern oal_void hi1102_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value);
extern oal_void hi1102_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value);
extern oal_void hi1102_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1102_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void  hi1102_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period);
extern oal_void  hi1102_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);

extern oal_void  hi1102_sta_tsf_restore(hal_to_dmac_vap_stru   *pst_hal_vap);
extern oal_void  hi1102_sta_tsf_save(hal_to_dmac_vap_stru   *pst_hal_vap, oal_bool_enum_uint8 en_need_restore);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void  hi1102_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window);
extern oal_void  hi1102_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_bool_enum_uint8     en_suspend_enable);
#endif
extern oal_void hi1102_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte);
extern oal_void hi1102_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period);
extern oal_void hi1102_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period);
extern oal_void hi1102_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count);
extern oal_void  hi1102_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *uc_dtim_count);
extern oal_void  hi1102_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count);
extern oal_void  hi1102_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim);
extern oal_void hi1102_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val);
extern oal_void hi1102_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type);
#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void  hi1102_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status);

extern oal_void hi1102_pm_wlan_servid_register(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint32 *pul_ret);

extern oal_void hi1102_pm_wlan_servid_unregister(hal_to_dmac_vap_stru  *pst_hal_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_void hi1102_coex_irq_en_set(oal_uint8 uc_intr_en);
extern oal_void hi1102_coex_sw_irq_clr_set(oal_uint8 uc_irq_clr);
extern oal_void hi1102_coex_sw_irq_set(oal_uint8 uc_irq_en);
extern oal_void hi1102_coex_sw_irq_status_get(oal_uint8 *uc_irq_status);
extern oal_void hi1102_get_btcoex_abort_qos_null_seq_num(oal_uint32 *ul_qosnull_seq_num);
extern oal_void hi1102_get_btcoex_occupied_period(oal_uint16 *ul_occupied_period);
extern oal_void hi1102_get_btcoex_pa_status(oal_uint32 *ul_pa_status);
extern oal_void hi1102_update_btcoex_btble_status(hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32 hi1102_btcoex_init(oal_void *p_arg);
extern oal_void hi1102_get_btcoex_statistic(oal_bool_enum_uint8 en_enable_abort_stat);
extern oal_uint32 hi1102_mpw_soc_write_reg(oal_uint32 ulQuryRegAddrTemp, oal_uint16 usQuryRegValueTemp);
extern oal_void hi1102_btcoex_update_ap_beacon_count(oal_uint32 *pul_beacon_count);
extern oal_void hi1102_btcoex_post_event(hal_to_dmac_device_stru *pst_hal_device, hal_dmac_misc_sub_type_enum_uint8 uc_sub_type);
extern oal_void hi1102_btcoex_have_small_ampdu(hal_to_dmac_device_stru *pst_hal_base_device, oal_uint32 *pul_have_ampdu);
extern oal_void hi1102_btcoex_process_bt_status(hal_to_dmac_device_stru *pst_hal_device);
#ifdef _PRE_WLAN_FEATURE_LTECOEX
extern oal_void  hi1102_ltecoex_req_mask_ctrl(oal_uint16 req_mask_ctrl);
#endif
extern oal_void hi1102_set_btcoex_abort_null_buff_addr(oal_uint32 ul_abort_null_buff_addr);
extern oal_void hi1102_set_btcoex_abort_qos_null_seq_num(oal_uint32 ul_qosnull_seq_num);
extern oal_void hi1102_set_btcoex_hw_rx_priority_dis(oal_uint8 uc_hw_rx_prio_dis);
extern oal_void hi1102_set_btcoex_hw_priority_en(oal_uint8 uc_hw_prio_en);
extern oal_void hi1102_set_btcoex_occupied_period(oal_uint16 ul_occupied_period);
extern oal_void hi1102_btcoex_get_rf_control(oal_uint16 ul_occupied_period, oal_uint32 *pul_wlbt_mode_sel, oal_uint16 us_wait_cnt);
extern oal_void hi1102_set_btcoex_sw_all_abort_ctrl(oal_uint8 uc_sw_abort_ctrl);
extern oal_void hi1102_set_btcoex_sw_priority_flag(oal_uint8 uc_sw_prio_flag);
extern oal_void hi1102_set_btcoex_soc_gpreg0(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
extern oal_void hi1102_set_btcoex_soc_gpreg1(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
#endif

extern oal_void hi1102_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_keyid);
extern oal_void hi1102_rx_dscr_opt_reset_normal(hal_to_dmac_device_stru * pst_device);
#ifdef _PRE_WLAN_DFT_STAT
extern oal_void  hi1102_dft_get_machw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_machw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_set_phy_stat_node(hal_to_dmac_device_stru * pst_hal_device,oam_stats_phy_node_idx_stru *pst_phy_node_idx);
extern oal_void  hi1102_dft_get_phyhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_phyhw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_get_rfhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_rfhw_stat, oal_uint32 *pul_len);
extern oal_void hi1102_dft_get_sochw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint16 *pst_sochw_stat, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_print_machw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_print_phyhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_print_rfhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_report_all_reg_state(hal_to_dmac_device_stru   *pst_hal_device);

#endif
extern oal_void hi1102_set_lte_gpio_mode(oal_uint32 ul_mode_value);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

