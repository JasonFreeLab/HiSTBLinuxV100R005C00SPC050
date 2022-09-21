/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : dmac对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_EXT_IF_H__
#define __DMAC_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "oal_mm.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "wal_ext_if.h"
#include "wlan_types.h"
#include "mac_frame.h"
#include "mac_device.h"
#include "mac_user.h"
#include "mac_vap.h"


#ifdef _PRE_WLAN_RF_110X_CALI_DPD
//#include "hmac_cali_dpd.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_EXT_IF_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_UCAST_FRAME_TX_COMP_TIMES      5           /* 建立BA会话前，需要产生单播帧的发送完成中断 */

#define DMAC_BA_SEQNO_MASK                  0x0FFF      /* max sequece number */
#define DMAC_BA_MAX_SEQNO_BY_TWO            2048
#define DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO   64
#define DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO   4032

#define DMAC_BA_GREATER_THAN_SEQHI          1
#define DMAC_BA_BETWEEN_SEQLO_SEQHI         2
#define DMAC_BA_AMSDU_BACK_SUPPORTED_FLAG   1           /* BA会话对AMSDU的支持标识 */

#define DMAC_BA_DELBA_TIMEOUT               0
#define DMAC_BATX_WIN_STALL_THRESHOLD       6

#define MAC_TX_CTL_SIZE                     OAL_NETBUF_CB_SIZE()

#define DMAC_BA_SEQ_ADD(_seq1, _seq2)       (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQ_SUB(_seq1, _seq2)       (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_ADD(_seq1, _seq2)     (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_SUB(_seq1, _seq2)     (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)

#define DMAC_BA_BMP_SIZE                    64

#define DMAC_IS_BA_INFO_PRESENT(_flags)     (_flags & BIT0)

#define DMAC_INVALID_SIGNAL_DELTA      (30)
#define DMAC_RSSI_SIGNAL_MIN           (-103)    /*信号强度极小值 */
#define DMAC_RSSI_SIGNAL_MAX           (5)       /*信号强度极大值 */
#define DMAC_INVALID_SIGNAL_INITIAL    (100)     /*非法初始信号极大值*/

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define DMAC_Non_Proxysta_BA_LUT_IDX_BMAP_LEN   ((HAL_MAX_BA_LUT_SIZE + 7) >> 4) /* 非Proxy STA LUT表需要两个字节 0~15 */
#define DMAC_Proxysta_BA_LUT_IDX_BMAP_LEN       ((HAL_MAX_BA_LUT_SIZE + 7) >> 4) /* Proxy STA LUT表需要两个字节 16~31 */
#endif

#define DMAC_INVALID_BA_LUT_INDEX           HAL_MAX_BA_LUT_SIZE

#define DMAC_AMPDU_LUT_IDX_BMAP_LEN         ((HAL_MAX_AMPDU_LUT_SIZE >> 3) + 1) /* 255 / 8 + 1 */
#define DMAC_INVALID_AMPDU_LUT_INDEX        (0)

/* 发送BA窗口记录seq number的最大个数，必须是2的整数次幂 */
#define DMAC_TID_MAX_BUFS       128
/* 发送BA窗口记录seq number的bitmap所使用的类型长度 */
#define DMAC_TX_BUF_BITMAP_WORD_SIZE        32
/* 发送BA窗口记录seq number的bit map的长度 */
#define DMAC_TX_BUF_BITMAP_WORDS \
    ((DMAC_TID_MAX_BUFS+DMAC_TX_BUF_BITMAP_WORD_SIZE-1) / DMAC_TX_BUF_BITMAP_WORD_SIZE)

/* 安全加密 :  bss_info 中记录AP 能力标识， WPA or WPA2*/
#define DMAC_WPA_802_11I    BIT0
#define DMAC_RSNA_802_11I   BIT1

#define DMAC_TX_MAX_RISF_NUM    6
#define DMAC_TX_QUEUE_AGGR_DEPTH     2
#define DMAX_TX_QUEUE_SINGLE_DEPTH   2
#define DMAC_TX_QEUEU_MAX_PPDU_NUM   2
#define DMAC_TX_QUEUE_UAPSD_DEPTH    5
#define DMAC_TX_QUEUE_FAIL_CHECK_NUM    1000
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_TID_STATS_INCR(_member, _cnt)      ((_member) += (_cnt))
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_DEV)
#define MAX_TX_USER_IDX 0XFFFF
#else
#define MAX_TX_USER_IDX 0x000F
#endif

#define DMAC_PA_ERROR_OFFSET 3

#if (defined(_PRE_DEBUG_MODE) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE))
extern oal_uint32 g_ul_desc_addr[HAL_TX_QUEUE_BUTT];
#endif

extern mac_board_stru g_st_dmac_board;
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名  : dmac_tx_host_drx_subtype_enum_uint8
  协议表格:
  枚举说明: HOST DRX事件子类型定义
*****************************************************************************/
/* WLAN_CRX子类型定义 */
typedef enum
{
    DMAC_TX_HOST_DRX = 0,
    HMAC_TX_HOST_DRX = 1,

    DMAC_TX_HOST_DRX_BUTT
}dmac_tx_host_drx_subtype_enum;
typedef oal_uint8 dmac_tx_host_drx_subtype_enum_uint8;

/*****************************************************************************
  枚举名  : dmac_tx_wlan_dtx_subtype_enum_uint8
  协议表格:
  枚举说明: WLAN DTX事件子类型定义
*****************************************************************************/
typedef enum
{
    DMAC_TX_WLAN_DTX = 0,

    DMAC_TX_WLAN_DTX_BUTT
}dmac_tx_wlan_dtx_subtype_enum;
typedef oal_uint8 dmac_tx_wlan_dtx_subtype_enum_uint8;

/*****************************************************************************
  枚举名  : dmac_wlan_ctx_event_sub_type_enum_uint8
  协议表格:
  枚举说明: WLAN CTX事件子类型定义
*****************************************************************************/
typedef enum
{
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION = 0,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC,      /* 收到wlan的Delba和addba rsp用于到dmac的同步 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ,  /* 11N自定义的请求的事件类型 */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ,              /* 扫描请求 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ,        /* PNO调度扫描请求 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT,      /* 管理帧处理 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM, /* 收到认证请求 关联请求，复位用户的节能状态 */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT,       /* 关联结果 */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG, /* AP侧处理关联时，修改SEQNUM_DUPDET_CTRL寄存器*/

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG,  /* STA收到beacon和assoc rsp时，更新EDCA寄存器 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_DEFAULT_VO_REG,/* 如果AP不是WMM的，则STA会去使能EDCA寄存器，并设置VO寄存器 */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN,          /* 切换至新信道事件 */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN,                 /* 设置信道事件 */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX,                  /* 禁止硬件发送 */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX,                   /* 恢复硬件发送 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK,             /* 切换信道后，恢复BSS的运行 */
#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN,          /* 切换到offchan做off-chan cac检测 */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN,         /* 切回home chan */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST,
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_SMPS,
#endif

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_PSM_OPMODE_NOTIFY,       /* AP侧opmode notify帧时判断节能信息 */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT,                /* edca优化中业务识别通知事件 */
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DPD_DATA_PROCESSED,
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
    DMAC_TX_HOST_TCP_CRX,
    DMAC_TX_HOST_UDP_CRX,
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_ctx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_ctx_event_sub_type_enum_uint8;

/* DMAC模块 WLAN_DRX子类型定义 */
typedef enum
{
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP,     /* AP模式: DMAC WLAN DRX 流程 */
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA,    /* STA模式: DMAC WLAN DRX 流程 */
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE,/* DMAC tkip mic faile 上报给HMAC */

    DMAC_WLAN_DRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_drx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_drx_event_sub_type_enum_uint8;

/* DMAC模块 WLAN_CRX子类型定义 */
typedef enum
{
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT,      /* DMAC 给 HMAC的初始化参数 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX,        /* DMAC WLAN CRX 流程 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA,     /* DMAC自身产生的DELBA帧 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT,  /* 扫描到一个bss信息，上报结果 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP,          /* DMAC扫描完成上报给HMAC */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP,     /* DMAC OBSS扫描完成上报给HMAC */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT,        /* 上报一个信道的扫描结果 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_ACS_RESP,           /* DMAC ACS 回复应用层命令执行结果给HMAC */

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP,     /* dmac向hmac发送流控制反压信息 */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC,  /* DMAC上报去关联事件到HMAC, HMAC会删除用户 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH,    /* DMAC上报去认证事件到HMAC */

    DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE,   /* 信道切换完成事件 */
    DMAC_WLAN_CRX_EVENT_SUB_TYPR_DBAC,                 /* DBAC enable/disable事件 */
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND,
#endif

    DMAC_WLAN_CRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_crx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_crx_event_sub_type_enum_uint8;

/* TBTT事件子类型定义 */
typedef enum
{
    DMAC_TBTT_EVENT_SUB_TYPE,

    DMAC_TBTT_EVENT_SUB_TYPE_BUTT
}dmac_tbtt_event_sub_type_enum;
typedef oal_uint8 dmac_tbtt_event_sub_type_enum_uint8;

/* 发向HOST侧的配置事件 */
typedef enum
{
    DMAC_TO_HMAC_SYN_UP_REG_VAL = 1,//FRW_SDT_REG_EVENT_LOG_SYN_SUB_TYPE = 0
    DMAC_TO_HMAC_CREATE_BA,
    DMAC_TO_HMAC_DEL_BA,
    DMAC_TO_HMAC_SYN_CFG,
#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_TO_HMAC_ALG_TEST,
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    DMAC_TO_HMAC_ALG_INFO_SYN,
    DMAC_TO_HMAC_VOICE_AGGR,
#endif

    DMAC_TO_HMAC_SYN_BUTT
}dmac_to_hmac_syn_type_enum;

/* MISC杂散事件 */
typedef enum
{
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
    DMAC_MISC_SUB_TYPE_RADAR_DETECT,
#endif
    DMAC_MISC_SUB_TYPE_DISASOC,
    DMAC_MISC_SUB_TYPE_CALI_TO_HMAC,
    DMAC_MISC_SUB_TYPE_HMAC_TO_CALI,


#ifdef _PRE_WLAN_FEATURE_ROAM
    DMAC_MISC_SUB_TYPE_ROAM_TRIGGER,
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_WOW
    DMAC_MISC_SUB_TYPE_DEV_READY_FOR_HOST_SLP,
    DMAC_MISC_SUB_TYPE_DEV_SYNC_HOST,
#endif //_PRE_WLAN_FEATURE_WOW

    DMAC_MISC_SUB_TYPE_BUTT
}dmac_misc_sub_type_enum;

typedef enum{
    DMAC_DISASOC_MISC_LINKLOSS = 0,
    DMAC_DISASOC_MISC_KEEPALIVE = 1,
    DMAC_DISASOC_MISC_CHANNEL_MISMATCH = 2,
    DMAC_DISASOC_MISC_BUTT
}dmac_disasoc_misc_reason_enum;
typedef oal_uint16 dmac_disasoc_misc_reason_enum_uint16;


/* HMAC to DMAC同步类型 */
typedef enum
{
    HMAC_TO_DMAC_SYN_INIT,
    HMAC_TO_DMAC_SYN_CREATE_CFG_VAP,
    HMAC_TO_DMAC_SYN_CFG,
    HMAC_TO_DMAC_SYN_ALG,
    HMAC_TO_DMAC_SYN_REG,

    HMAC_TO_DMAC_SYN_BUTT
}hmac_to_dmac_syn_type_enum;
typedef oal_uint8 hmac_to_dmac_syn_type_enum_uint8;

/* TXRX函数回调出参定义 */
typedef enum
{
    DMAC_TXRX_PASS = 0,     /* 继续往下 */
    DMAC_TXRX_DROP = 1,     /* 需要丢包 */
    DMAC_TXRX_SENT = 2,     /* 已被发送 */
    DMAC_TXRX_BUFF = 3,     /* 已被缓存 */

    DMAC_TXRX_BUTT
}dmac_txrx_output_type_enum;
typedef oal_uint8 dmac_txrx_output_type_enum_uint8;


/* 天线训练状态 */
typedef enum
{
    DMAC_USER_SMARTANT_NON_TRAINING        = 0,
    DMAC_USER_SMARTANT_NULLDATA_TRAINING   = 1,
    DMAC_USER_SMARTANT_DATA_TRAINING       = 2,

    DMAC_USER_SMARTANT_TRAINING_BUTT
}dmac_user_smartant_training_enum;
typedef oal_uint8 dmac_user_smartant_training_enum_uint8;

/* 算法的报文探测标志 (注:对于1102该枚举只允许使用3bit空间, 因此有效枚举值最大为7) */
typedef enum
{
    DMAC_USER_ALG_NON_PROBE                     = 0,    /* 非探测报文 */
    DMAC_USER_ALG_TXBF_SOUNDING                 = 1,    /* TxBf sounding报文 */
    DMAC_USER_ALG_AUOTRATE_PROBE                = 2,    /* Autorate探测报文 */
    DMAC_USER_ALG_AGGR_PROBE                    = 3,    /* 聚合探测报文 */
    DMAC_USER_ALG_TPC_PROBE                     = 4,    /* TPC探测报文 */
    DMAC_USER_ALG_TX_MODE_PROBE                 = 5,    /* 发送模式探测报文(TxBf, STBC, Chain) */
    DMAC_USER_ALG_SMARTANT_NULLDATA_PROBE       = 6,    /* 智能天线NullData训练报文 */
    DMAC_USER_ALG_SMARTANT_DATA_PROBE           = 7,    /* 智能天线Data训练报文 */

    DMAC_USER_ALG_PROBE_BUTT
}dmac_user_alg_probe_enum;
typedef oal_uint8 dmac_user_alg_probe_enum_uint8;

/* BA会话的状态枚举 */
typedef enum
{
    DMAC_BA_INIT        = 0,    /* BA会话未建立 */
    DMAC_BA_INPROGRESS,         /* BA会话建立过程中 */
    DMAC_BA_COMPLETE,           /* BA会话建立完成 */
    DMAC_BA_HALTED,             /* BA会话节能暂停 */
    DMAC_BA_FAILED,             /* BA会话建立失败 */

    DMAC_BA_BUTT
}dmac_ba_conn_status_enum;
typedef oal_uint8 dmac_ba_conn_status_enum_uint8;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,                /*无效*/
      DMAC_TX_SUCC,                         /*成功*/
      DMAC_TX_FAIL,                         /*发送失败（超过重传限制：接收响应帧超时）*/
      DMAC_TX_TIMEOUT,                      /*lifetime超时（没法送出去）*/
      DMAC_TX_RTS_FAIL,                     /*RTS 发送失败（超出重传限制：接收cts超时）*/
      DMAC_TX_NOT_COMPRASS_BA,              /*收到的BA是非压缩块确认*/
      DMAC_TX_TID_MISMATCH,                 /*收到的BA中TID与发送时填写在描述符中的TID不一致*/
      DMAC_TX_KEY_SEARCH_FAIL,              /* Key search failed*/
      DMAC_TX_AMPDU_MISMATCH,               /*描述符异常*/
      DMAC_TX_PENDING,                      /*tx pending：mac发送过该帧，但是没有成功，等待重传*/
      DMAC_TX_FAIL_ACK_ERROR,               /*发送失败（超过重传限制：接收到的响应帧错误）*/
      DMAC_TX_RTS_FAIL_CTS_ERROR,           /*RTS发送失败（超出重传限制：接收到的CTS错误）*/
      DMAC_TX_FAIL_ABORT,                   /*发送失败（因为abort）*/
      DMAC_TX_FAIL_STATEMACHINE_PHY_ERROR,  /*MAC发送该帧异常结束（状态机超时、phy提前结束等原因）*/
      DMAC_TX_SOFT_PSM_BACK,                /*软件节能回退*/
      DMAC_TX_SOFT_RESERVE,              /*reserved*/
} dmac_tx_dscr_status_enum;
#else
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,
      DMAC_TX_SUCC,
      DMAC_TX_FAIL,
      DMAC_TX_TIMEOUT,
      DMAC_TX_RTS_FAIL,
      DMAC_TX_NOT_COMPRASS_BA,
      DMAC_TX_TID_MISMATCH,
      DMAC_TX_KEY_SEARCH_FAIL,
      DMAC_TX_AMPDU_MISMATCH,
      DMAC_TX_PENDING,
      DMAC_TX_SOFT_PSM_BACK,    /*软件节能回退*/
      DMAC_TX_SOFT_RESET_BACK,  /*软件RESET回退*/
} dmac_tx_dscr_status_enum;
#endif
typedef oal_uint8 dmac_tx_dscr_status_enum_uint8;

typedef enum
{
    DMAC_TX_MODE_NORMAL  = 0,
    DMAC_TX_MODE_RIFS    = 1,
    DMAC_TX_MODE_AGGR    = 2,
    DMAC_TX_MODE_BUTT
}dmac_tx_mode_enum;
typedef oal_uint8 dmac_tx_mode_enum_uint8;

/* mib index定义 */
typedef enum
{
    WLAN_MIB_INDEX_LSIG_TXOP_PROTECTION_OPTION_IMPLEMENTED,
    WLAN_MIB_INDEX_HT_GREENFIELD_OPTION_IMPLEMENTED,
    WLAN_MIB_INDEX_SPEC_MGMT_IMPLEMENT,
    WLAN_MIB_INDEX_FORTY_MHZ_OPERN_IMPLEMENT,
    WLAN_MIB_INDEX_2040_COEXT_MGMT_SUPPORT,
    WLAN_MIB_INDEX_FORTY_MHZ_INTOL,
    WLAN_MIB_INDEX_VHT_CHAN_WIDTH_OPTION_IMPLEMENT,
    WLAN_MIB_INDEX_MINIMUM_MPDU_STARTING_SPACING,

    WLAN_MIB_INDEX_OBSSSCAN_TRIGGER_INTERVAL, /*8*/
    WLAN_MIB_INDEX_OBSSSCAN_TRANSITION_DELAY_FACTOR,
    WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_DWELL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_DWELL,
    WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_TOTAL_PER_CHANNEL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_TOTAL_PER_CHANNEL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVITY_THRESHOLD,/*14*/

    WLAN_MIB_INDEX_BUTT
}wlan_mib_index_enum;
typedef oal_uint16 wlan_mib_index_enum_uint16;

typedef enum
{
    DMAC_TID_PAUSE_RESUME_TYPE_BA   = 0,
    DMAC_TID_PAUSE_RESUME_TYPE_PS   = 1,
    DMAC_TID_PAUSE_RESUME_TYPE_BUTT
}dmac_tid_pause_type_enum;
typedef oal_uint8 dmac_tid_pause_type_enum_uint8;

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
/* DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP */
typedef struct
{
    dmac_disasoc_misc_reason_enum_uint16     en_disasoc_reason;
    oal_uint16                               us_user_idx;
}dmac_disasoc_misc_stru;

/* 接收帧的统计信息 */
typedef struct
{
    oal_uint32  ul_total_num;           /* 总数 */
    oal_uint32  ul_self_fcs_correct;    /* 发给自己的FCS正确的单播帧 */
    oal_uint32  ul_other_fcs_correct;   /* 不是发给自己的FCS正确的单播帧 */
    oal_uint32  ul_total_fcs_error;     /* FCS错误的所有帧 */
}dmac_rx_fcs_statistic;
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_DEV)
/* 声明接收帧的FCS的统计信息 */
extern dmac_rx_fcs_statistic g_ast_rx_fcs_statistic[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
#endif

typedef struct
{
    oal_uint8               uc_tid_num;                         /* 需要发送的tid队列号 */
    dmac_tx_mode_enum_uint8 en_tx_mode;                         /* 调度tid的发送模式 */
    oal_uint8               uc_mpdu_num[DMAC_TX_QUEUE_AGGR_DEPTH];   /* 调度得到的需要发送的mpdu个数 */
    oal_uint16              us_user_idx;                        /* 要发送的tid队列隶属的user */
    oal_uint8               uc_resv[2];
}mac_tid_schedule_output_stru;

/* DMAC与HMAC模块共用的WLAN DRX事件结构体 */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf链表一个元素 */
    oal_uint16              us_netbuf_num;      /* netbuf链表的个数 */
    oal_uint8               auc_resv[2];        /* 字节对齐 */
}dmac_wlan_drx_event_stru;

/* DMAC与HMAC模块共用的WLAN CRX事件结构体 */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* 指向管理帧对应的netbuf */
    oal_uint8              *puc_chtxt;          /* Shared Key认证用的challenge text */
}dmac_wlan_crx_event_stru;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct
{
    oal_uint8 uc_need_delba;
    oal_uint8 uc_ba_size;
    oal_uint8 auc_reserve[2];
}dmac_to_hmac_btcoex_rx_delba_trigger_event_stru;
#endif

typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_tid;
    oal_uint8       uc_vap_id;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       uc_cur_protocol;
    oal_uint8       auc_reserve[3];
#endif
}dmac_to_hmac_ctx_event_stru;


typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_cur_bandwidth;
    oal_uint8       uc_cur_protocol;
}dmac_to_hmac_syn_info_event_stru;

typedef struct
{
    oal_uint8       uc_vap_id;
    oal_uint8       en_voice_aggr;              /* 是否支持Voice聚合 */
    oal_uint8       auc_resv[2];
}dmac_to_hmac_voice_aggr_event_stru;

/*mic攻击*/
typedef struct
{
    oal_uint8                  auc_user_mac[WLAN_MAC_ADDR_LEN];
    oal_uint8                  auc_reserve[2];
    oal_nl80211_key_type       en_key_type;
    oal_int32                  l_key_id;
}dmac_to_hmac_mic_event_stru;

/*DMAC与HMAC模块共用的DTX事件结构体 */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf链表一个元素 */
    oal_uint16              us_frame_len;
    oal_uint8               auc_reserve[2];
}dmac_tx_event_stru;

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
typedef struct
{
    oal_uint32        us_dpd_data[128]; /*dpd calibration data*/
    oal_uint16        us_data_len;       /*data length*/
}dpd_cali_data_stru;

#endif

typedef struct
{
    mac_channel_stru                     st_channel;
    mac_ch_switch_info_stru              st_ch_switch_info;

    oal_bool_enum_uint8                  en_switch_immediately; /* 1 - 马上切换  0 - 暂不切换, 推迟到tbtt中切换*/
    oal_bool_enum_uint8                  en_check_cac;
    oal_uint8                            auc_resv[2];
}dmac_set_chan_stru;

typedef struct
{
    wlan_ch_switch_status_enum_uint8     en_ch_switch_status;      /* 信道切换状态 */
    oal_uint8                            uc_announced_channel;     /* 新信道号 */
    wlan_channel_bandwidth_enum_uint8    en_announced_bandwidth;   /* 新带宽模式 */
    oal_uint8                            uc_ch_switch_cnt;         /* 信道切换计数 */
    oal_bool_enum_uint8                  en_csa_present_in_bcn;    /* Beacon帧中是否包含CSA IE */
    oal_uint8                            uc_csa_vap_cnt;           /* 需要发送csa的vap个数 */
    oal_uint8                            auc_reserve[2];
}dmac_set_ch_switch_info_stru;

/*
    (1)DMAC与HMAC模块共用的CTX子类型ACTION对应的事件的结构体
    (2)当DMAC自身产生DELBA帧时，使用该结构体向HMAC模块抛事件
*/
 typedef struct
 {
    mac_category_enum_uint8     en_action_category;     /* ACTION帧的类型 */
    oal_uint8                   uc_action;              /* 不同ACTION类下的子帧类型 */
    oal_uint16                  us_user_idx;
    oal_uint16                  us_frame_len;           /* 帧长度 */
    oal_uint8                   uc_hdr_len;             /* 帧头长度 */
    oal_uint8                   uc_tidno;               /* tidno，部分action帧使用 */
    oal_uint8                   uc_initiator;           /* 触发端方向 */

    /* 以下为接收到req帧，发送rsp帧后，需要同步到dmac的内容 */
    oal_uint8                       uc_stauts;              /* rsp帧中的状态 */
    oal_uint16                      us_baw_start;           /* 窗口开始序列号 */
    oal_uint16                      us_baw_size;            /* 窗口大小 */
    oal_uint8                       uc_ampdu_max_num;       /* BA会话下的最多聚合的AMPDU的个数 */
    oal_bool_enum_uint8             en_amsdu_supp;          /* 是否支持AMSDU */
    oal_uint16                      us_ba_timeout;          /* BA会话交互超时时间 */
    mac_back_variant_enum_uint8     en_back_var;            /* BA会话的变体 */
    oal_uint8                       uc_dialog_token;        /* ADDBA交互帧的dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;           /* LUT索引 */
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* 用于DELBA查找HMAC用户 */
 }dmac_ctx_action_event_stru;

/* 添加用户事件payload结构体 */
typedef struct
{
    oal_uint16  us_user_idx;     /* 用户index */
    oal_uint8   auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint16  us_sta_aid;
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN];

    mac_vht_hdl_stru          st_vht_hdl;
    mac_user_ht_hdl_stru      st_ht_hdl;
    mac_ap_type_enum_uint8    en_ap_type;

//    oal_uint8   bit_transmit_staggered_sounding_cap : 1,
//                bit_exp_comp_feedback               : 2,
//                bit_su_beamformer_cap               : 1,                       /* SU bfer能力，要过AP认证，必须填1 */
//                bit_su_beamformee_cap               : 1,                       /* SU bfee能力，要过STA认证，必须填1 */
//                bit_resv                            : 3;

 //   oal_uint8   bit_num_bf_ant_supported            : 3,                       /* SU时，最大接收NDP的Nsts，最小是1 */
 //               bit_num_sounding_dim                : 3,                       /* SU时，表示Nsts最大值，最小是1 */
 //               bit_mu_beamformer_cap               : 1,                       /* 不支持，set to 0 */
//                bit_mu_beamformee_cap               : 1;                       /* 不支持，set to 0 */
}dmac_ctx_add_user_stru;

/* 删除用户事件结构体 */
typedef dmac_ctx_add_user_stru dmac_ctx_del_user_stru;

/* 扫描请求事件payload结构体 */
typedef struct
{
    mac_scan_req_stru   *pst_scan_params;   /* 将扫描参数传下去 */
}dmac_ctx_scan_req_stru;

typedef struct
{
    oal_uint8                   uc_scan_idx;
    oal_uint8                   auc_resv[3];
    mac_scan_chan_stats_stru    st_chan_result;
}dmac_crx_chan_result_stru;


/* Update join req 参数写寄存器的结构体定义 */
typedef struct
{
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];           /* 加入的AP的BSSID  */
    oal_uint16              us_beacon_period;
    mac_channel_stru        st_current_channel;                     /* 要切换的信道信息 */
    oal_uint32              ul_beacon_filter;                       /* 过滤beacon帧的滤波器开启标识位 */
    oal_uint32              ul_non_frame_filter;                    /* 过滤no_frame帧的滤波器开启标识位 */
    oal_uint8               auc_ssid[WLAN_SSID_MAX_LEN];            /* 加入的AP的SSID  */
    oal_uint8               uc_dtim_period;                         /* dtim period */
    oal_bool_enum_uint8     en_dot11FortyMHzOperationImplemented;
    oal_uint8               auc_resv;
}dmac_ctx_join_req_set_reg_stru;

/* wait join写寄存器参数的结构体定义 */
typedef struct
{
    oal_uint32              ul_dtim_period;                  /* dtim period */
    oal_uint32              ul_dtim_cnt;                     /* dtim count  */
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];    /* 加入的AP的BSSID  */
    oal_uint16              us_tsf_bit0;                     /* tsf bit0  */
}dmac_ctx_set_dtim_tsf_reg_stru;

/* wait join misc写寄存器参数的结构体定义 */
typedef struct
{
    oal_uint32              ul_beacon_filter;                /* 过滤beacon帧的滤波器开启标识位 */
}dmac_ctx_join_misc_set_reg_stru;

/* wait join写寄存器参数的结构体定义 */
typedef struct
{
    oal_uint16             uc_user_index;                    /* user index */
    oal_uint8              auc_resv[2];
}dmac_ctx_asoc_set_reg_stru;

/* sta更新edca参数寄存器的结构体定义 */
typedef struct
{
    oal_uint8                            uc_vap_id;
    mac_wmm_set_param_type_enum_uint8    en_set_param_type;
    oal_uint8                            auc_resv[2];
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    wlan_mib_Dot11QAPEDCAEntry_stru      ast_wlan_mib_qap_edac[WLAN_WME_AC_BUTT];
#endif
}dmac_ctx_sta_asoc_set_edca_reg_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
/* 裸系统下DMAC模块与HMAC模块共用的接收流程控制信息数据结构定义, 与hal_rx_ctl_stru结构体保持一致*/
#pragma pack(push,1)
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
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :1;
    /*word 1*/
    oal_uint16                  us_frame_len;               /* 帧头与帧体的总长度 */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4; /* 每个MPDU占用的buf数 */
    oal_uint8                   uc_channel_number;          /* 接收帧的信道 */
    /*word 2*/
}mac_rx_ctl_stru;
#pragma pack(pop)

#else
/* DMAC模块与HMAC模块共用的接收流程控制信息数据结构定义, 与hal_rx_ctl_stru结构体保持一致*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_buff_nums         :4;   /* 每个MPDU占用的buf数目 */
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :3;
    oal_uint8                   uc_mac_header_len;          /* mac header帧头长度 */
    /*word 1*/
    oal_uint16                  us_frame_len;               /* 帧头与帧体的总长度 */
    oal_uint16                  us_da_user_idx;             /* 目的地址用户索引 */
    /*word 2*/
    oal_uint32                 *pul_mac_hdr_start_addr;     /* 对应的帧的帧头地址,虚拟地址 */
    /*word 3*/
    oal_uint16                  us_ta_user_idx;             /* 发送端地址用户索引 */
    oal_uint8                   uc_mac_vap_id;
    oal_uint8                   uc_channel_number;          /* 接收帧的信道 */
}mac_rx_ctl_stru;
#endif
/* hmac to dmac配置同步消息结构 */
typedef struct
{
    wlan_cfgid_enum_uint16              en_syn_id;      /* 同步事件ID*/
    oal_uint16                          us_len;         /* 事件payload长度 */
    oal_uint8                           auc_msg_body[4];/* 事件payload */
}hmac_to_dmac_cfg_msg_stru;

typedef hmac_to_dmac_cfg_msg_stru dmac_to_hmac_cfg_msg_stru;

/* HMAC到DMAC配置同步操作 */
typedef struct
{
    wlan_cfgid_enum_uint16      en_cfgid;
    oal_uint8                   auc_resv[2];
    oal_uint32                  (*p_set_func)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
}dmac_config_syn_stru;

typedef dmac_config_syn_stru hmac_config_syn_stru;

#if 0
/* DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP */
typedef struct
{
    oal_uint32      ul_bss_num;
    oal_void       *p_bss_list;
}dmac_wlan_crx_scan_comp_stru;
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
#pragma pack(push,1)
/* 裸系统cb字段 只有20字节可用，可以将resv字段修改为可用字段，不允许再增加字节!!!!!!!!!!!!!!!!!!!!!!!!! */
struct  mac_tx_ctl
{
    /* 该成员只在第一个netbuf中有效 */
    oal_uint8                               bit_mpdu_num                :7;          /* ampdu中包含的MPDU个数,实际描述符填写的值为此值-1 */
    /* 在每个MPDU的第一个NETBUF中有效 */
    oal_uint8                               bit_netbuf_num              :1;          /* 每个MPDU占用的netbuf数目 */

    oal_uint8                               bit_frame_header_length     :6;          //51四地址32 /* 该MPDU的802.11头长度 */
    oal_uint8                               en_is_first_msdu            :1;          /* 是否是第一个子帧，OAL_FALSE不是 OAL_TRUE是 */
    oal_uint8                               en_is_amsdu                 :1;          /* 是否AMSDU: OAL_FALSE不是，OAL_TRUE是 */

    frw_event_type_enum_uint8               bit_en_event_type           :6;          /* 取值:FRW_EVENT_TYPE_WLAN_DTX和FRW_EVENT_TYPE_HOST_DRX，作用:在释放时区分是内存池的netbuf还是原生态的 */
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               bit_is_vipframe             :1;          /* 该帧是否是EAPOL帧、DHCP帧 */


    oal_uint8                               bit_tx_user_idx             :4;          /* dmac tx 到 tx complete 传递的user结构体，目标用户地址 */
    dmac_user_alg_probe_enum_uint8          en_is_probe_data            :3;          /* 是否探测帧 */
    oal_uint8                               en_ismcast                  :1;          /* 该MPDU是单播还是多播:OAL_FALSE单播，OAL_TRUE多播 */

    oal_uint8                               bit_retried_num             :4;
    oal_uint8                               bit_need_rsp                :1;           /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               en_is_eapol                 :1;           /* 该帧是否是EAPOL帧 1102可以去掉 */
    oal_uint8                               en_is_get_from_ps_queue     :1;           /* 节能特性用，标识一个MPDU是否从节能队列中取出来的 */
    oal_uint8                               bit_is_eapol_key_ptk        :1;           /* 4 次握手过程中设置单播密钥EAPOL KEY 帧标识 */

    oal_uint8                               bit_tx_vap_index            :3;
    oal_uint8                               bit_mgmt_frame_id           :4;            /* wpas 发送管理帧的frame id */
    oal_uint8                               bit_roam_data               :1;

    wlan_wme_ac_type_enum_uint8             bit_ac                      :3;            /* ac */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy               :3;            /* ACK 策略 */
    oal_uint8                               bit_reserved3               :2;

    oal_uint8                               uc_alg_pktno;                              /* 算法用到的字段，唯一标示该报文 */

    oal_uint8                               bit_tid                     :4;
    oal_uint8                               bit_tx_user_idx_bak         :4;

    oal_time_us_stru                        st_timestamp_us;                           /* 维测使用入TID队列时的时间戳 */
    oal_uint16                              us_mpdu_bytes;                             /* mpdu字节数，维测用，不包括头尾，不包括snap，不包括padding */

}__OAL_DECLARE_PACKED;
typedef struct mac_tx_ctl  mac_tx_ctl_stru;
/* DMAC模块接收流程控制信息结构，存放于对应的netbuf的CB字段中，最大值为48字节,
   如果修改，一定要通知sdt同步修改，否则解析会有错误!!!!!!!!!!!!!!!!!!!!!!!!!*/
typedef struct
{
    mac_rx_ctl_stru             st_rx_info;         /* hmac需要传给dmac的数据信息 */
    hal_rx_status_stru          st_rx_status;       /* 保存加密类型及帧长信息 */
    hal_rx_statistic_stru       st_rx_statistic;    /* 保存接收描述符的统计信息 */
}dmac_rx_ctl_stru;

#pragma pack(pop)
#else
/* netbuf控制字段(CB)，总长度为48字节 (目前已用42字节),如果修改，一定要通知sdt
   同步修改，否则解析会有错误!!!!!!!!!!!!!!!!!!!!!!!!! */
typedef struct
{
    /* 该成员只在第一个netbuf中有效 */
    oal_uint8                               uc_mpdu_num;                /* ampdu中包含的MPDU个数,实际描述符填写的值为此值-1 */

    /* 在每个MPDU的第一个NETBUF中有效 */
    oal_uint8                               uc_netbuf_num;                              /* 每个MPDU占用的netbuf数目 */
    oal_uint16                              us_mpdu_len;                                /* 每个MPDU的长度不包括mac header length */
    oal_uint8                               en_is_amsdu                 :1;             /* 是否AMSDU: OAL_FALSE不是，OAL_TRUE是 */
    oal_uint8                               en_ismcast                  :1;             /* 该MPDU是单播还是多播:OAL_FALSE单播，OAL_TRUE多播 */
    oal_uint8                               en_is_eapol                 :1;             /* 该帧是否是EAPOL帧 */
    oal_uint8                               en_use_4_addr               :1;             /* 是否使用4地址，由WDS特性决定 */
    oal_uint8                               en_is_get_from_ps_queue     :1;             /* 节能特性用，标识一个MPDU是否从节能队列中取出来的 */
    oal_uint8                               uc_is_first_msdu            :1;             /* 是否是第一个子帧，OAL_FALSE不是 OAL_TRUE是 */
	oal_uint8                               en_need_pause_tid           :1;
    oal_uint8                               en_is_bar                   :1;
    oal_uint8                               uc_frame_header_length;                     /* 该MPDU的802.11头长度 */
    oal_uint8                               en_is_qosdata               :1;             /* 指示该帧是否是qos data */
    oal_uint8                               bit_80211_mac_head_type     :1;             /* 0: 802.11 mac头不在skb中，另外申请了内存存放； 1: 802.11 mac头在skb中*/
    oal_uint8                               bit_is_vipframe             :1;             /* 该帧是否是EAPOL帧、DHCP帧 */
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               en_seq_ctrl_bypass          :1;             /* 该帧的SN号由软件维护，硬件禁止维护(目前仅用于非QOS分片帧 ) */
    oal_uint8                               bit_need_rsp                :1;             /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               bit_is_eapol_key_ptk        :1;             /* 4 次握手过程中设置单播密钥EAPOL KEY 帧标识 */
    oal_uint8                               bit_roam_data               :1;

    wlan_frame_type_enum_uint8              en_frame_type;                              /* 帧类型：数据帧，管理帧... */
    mac_ieee80211_frame_stru               *pst_frame_header;                           /* 该MPDU的帧头指针 */


    wlan_wme_ac_type_enum_uint8             uc_ac;                                      /* ac */
    oal_uint8                               uc_tid;                                     /* tid */
    frw_event_type_enum_uint8               en_event_type;                              /* 取值:FRW_EVENT_TYPE_WLAN_DTX和FRW_EVENT_TYPE_HOST_DRX，作用:在释放时区分是内存池的netbuf还是原生态的 */
    oal_uint8                               uc_event_sub_type;                          /* amsdu抛事件用的 */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy;                              /* ACK 策略 */
    oal_uint8                               uc_tx_vap_index;
    oal_uint16                              us_tx_user_idx;                             /* dmac tx 到 tx complete 传递的user结构体，目标用户地址 */
    oal_uint32                              ul_alg_pktno;                               /* 算法用到的字段，唯一标示该报文 */
    oal_uint8                               uc_retried_num;
    dmac_user_alg_probe_enum_uint8          en_is_probe_data;                           /* 是否是探测帧 */
    oal_uint16                              us_seqnum;                                  /* 记录软件分配的seqnum*/
    hal_tx_dscr_stru                       *pst_bar_dscr;
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_HOST)
    /*1102 host 不用此变量，占空间太大,ARM64时CB超过大小!*/
    oal_time_us_stru                        st_timestamp_us;                            /* 入TID队列时的时间戳 */
#endif
    oal_uint16                              us_eapol_ts;                                /* eapol帧时间戳 */
    oal_uint16                              us_mpdu_bytes;                              /* mpdu字节数，维测用，不包括头尾，不包括snap，不包括padding */
    oal_uint8                               bit_mgmt_frame_id           :4;             /* wpas 发送管理帧的frame id */
    oal_uint8                               bit_reserved2               :4;
}mac_tx_ctl_stru;

/* DMAC模块接收流程控制信息结构，存放于对应的netbuf的CB字段中，最大值为48字节,
   如果修改，一定要通知sdt同步修改，否则解析会有错误!!!!!!!!!!!!!!!!!!!!!!!!!*/
typedef struct
{
    mac_rx_ctl_stru             st_rx_info;         /* hmac需要传给dmac的数据信息 */
    hal_rx_status_stru          st_rx_status;       /* 保存加密类型及帧长信息 */
    hal_rx_statistic_stru       st_rx_statistic;    /* 保存接收描述符的统计信息 */
}dmac_rx_ctl_stru;

#endif


typedef struct
{
    oal_uint32      ul_best_rate_goodput_kbps;
    oal_uint32      ul_rate_kbps;           /* 速率大小(单位:kbps) */
    oal_uint8       uc_aggr_subfrm_size;    /* 聚合子帧数门限值 */
    oal_uint8       uc_per;                 /* 该速率的PER(单位:%) */
    oal_uint8       uc_resv[2];
}dmac_tx_normal_rate_stats_stru;

typedef struct
{
    oal_bool_enum_uint8                     in_use;                     /* 缓存BUF是否被使用 */
    oal_uint8                               uc_num_buf;                 /* MPDU对应的描述符的个数 */
    oal_uint16                              us_seq_num;                 /* MPDU对应的序列号 */
    oal_netbuf_head_stru                    st_netbuf_head;             /* MPDU对应的描述符首地址 */
    oal_uint32                              ul_rx_time;                 /* 报文被缓存的时间戳 */
} dmac_rx_buf_stru;


typedef struct
{
    oal_void                               *pst_ba;
    oal_uint8                               uc_tid;
    mac_delba_initiator_enum_uint8          en_direction;
    oal_uint16                              us_mac_user_idx;
    oal_uint8                               uc_vap_id;
    oal_uint16                              us_timeout_times;
    oal_uint8                               uc_resv[1];
}dmac_ba_alarm_stru;


/* 一个站点下的每一个TID下的聚合接收的状态信息 */
typedef struct
{
    oal_uint16                      us_baw_start;         /* 第一个未收到的MPDU的序列号 */
    oal_bool_enum_uint8             en_is_ba;             /* Session Valid Flag */
    oal_uint8                       auc_resv[1];

    /* 建立BA会话相关的信息 */
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;    /* BA会话的状态 */
    mac_back_variant_enum_uint8     en_back_var;          /* BA会话的变体 */
    oal_uint8                       uc_ba_policy;         /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;         /* 接收端Session H/w LUT Index */
    oal_uint8                      *puc_transmit_addr;    /* BA会话发送端地址 */
}dmac_ba_rx_stru;

typedef struct
{
    oal_uint8   uc_in_use;
    oal_uint8   uc_resv[1];
    oal_uint16  us_seq_num;
    oal_void*   p_tx_dscr;
}dmac_retry_queue_stru;

typedef struct
{
    oal_uint16                      us_baw_start;           /* 第一个未确认的MPDU的序列号 */
    oal_uint16                      us_last_seq_num;        /* 最后一个发送的MPDU的序列号 */
    oal_uint16                      us_baw_size;            /* Block_Ack会话的buffer size大小 */
    oal_uint16                      us_baw_head;            /* bitmap中记录的第一个未确认的包的位置 */
    oal_uint16                      us_baw_tail;            /* bitmap中下一个未使用的位置 */
    oal_bool_enum_uint8             en_is_ba;               /* Session Valid Flag */
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;      /* BA会话的状态 */
    mac_back_variant_enum_uint8     en_back_var;            /* BA会话的变体 */
    oal_uint8                       uc_dialog_token;        /* ADDBA交互帧的dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_bool_enum_uint8             en_amsdu_supp;          /* BLOCK ACK支持AMSDU的标识 */
    oal_uint8                      *puc_dst_addr;           /* BA会话接收端地址 */
    oal_uint16                      us_ba_timeout;          /* BA会话交互超时时间 */
    oal_uint8                       uc_ampdu_max_num;       /* BA会话下，能够聚合的最大的mpdu的个数 */
    oal_uint8                       uc_tx_ba_lut;
    oal_uint16                      us_mac_user_idx;
    oal_uint8                       auc_resv[2];
    oal_uint32                      aul_tx_buf_bitmap[DMAC_TX_BUF_BITMAP_WORDS];
}dmac_ba_tx_stru;

/* 11n下的参数，需要在关联时进行设置 */
typedef struct
{
    oal_uint8               uc_ampdu_max_num;
    oal_uint8               auc_reserve[1];
    oal_uint16              us_ampdu_max_size;
    oal_uint32              ul_ampdu_max_size_vht;
}dmac_ht_handle_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    /* 入队统计 */
    oal_uint32              ul_tid_enqueue_total_cnt;            /* 入队总数目统计 */
    oal_uint32              ul_tid_enqueue_ptr_null_cnt;         /* 入队函数空指针流程导致丢包统计 */
    oal_uint32              ul_tid_enqueue_full_cnt;             /* 入队时队列满导致丢包统计 */
    oal_uint32              ul_tid_enqueue_head_ptr_null_cnt;    /* 发送完成中入队，空指针流程丢包 */
    oal_uint32              ul_tid_enqueue_head_full_cnt;        /* 发送完成中入队，队列满丢包统计 */

    /* 出队统计 */
    oal_uint32              ul_tid_dequeue_total_cnt;            /* 出队总数目统计 */
    oal_uint32              ul_tid_dequeue_normal_cnt;           /* 非AMPDU时出队个数 */
    oal_uint32              ul_tid_dequeue_ampdu_cnt;            /* AMPDU出队个数 */

    /* 丢包统计 */
    oal_uint32              ul_tid_video_dropped_cnt;            /* 视频丢包个数，从tid拿出来直接删除 */
    oal_uint32              ul_tid_traffic_ctl_dropped_cnt;      /* 流控丢包个数，从tid拿出来直接删除 */
    oal_uint32              ul_tid_txbuf_overflow_dropped_cnt;   /* 发送时buf溢出丢包 */
    oal_uint32              ul_tid_dbac_reset_dropped_cnt;             /* dbac复位case信息丢包 */

    /* 重传统计 */
    oal_uint32              ul_tid_retry_enqueue_cnt;            /* 重传包入队数目统计 */
    oal_uint32              ul_tid_retry_dequeue_cnt;            /* 重传包出队数目统计 */
}dmac_tid_stats_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef oam_stats_ampdu_stat_stru dmac_tid_ampdu_stat_stru;
#endif


typedef struct
{
    oal_uint8               uc_tid;                 /* 通信标识符 */
    oal_uint8               uc_is_paused;           /* TID被暂停调度 */
    oal_uint8               uc_num_dq;              /* 可以加到ba窗的包的个数 */
    oal_uint8               uc_retry_num;           /* tid队列中重传报文的个数 */
    oal_uint16              us_mpdu_num;            /* MPDU个数 */
    oal_uint16              us_user_idx;            /* 无效值为MAC_RES_MAC_USER_NUM */

    oal_uint32              ul_mpdu_avg_len;        /* mpdu滑动平均长度 */
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_dlist_head_stru     st_retry_q;             /* 重传队列链表 */
    oal_netbuf_head_stru    st_buff_head;           /* 发送缓存队列链表 */
#else
    oal_dlist_head_stru     st_hdr;                 /* tid缓存队列头 */
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    oal_void               *p_alg_priv;             /* TID级别算法私有结构体 */
    dmac_tx_normal_rate_stats_stru st_rate_stats;   /* 速率算法在发送完成中统计出的信息 */
    dmac_ba_tx_stru        *pst_ba_tx_hdl;
    dmac_ba_rx_stru        *pst_ba_rx_hdl;
    dmac_ht_handle_stru     st_ht_tx_hdl;
    oal_uint8               uc_num_tx_ba;
    oal_uint8               uc_num_rx_ba;
    oal_uint8               uc_vap_id;
    dmac_tx_mode_enum_uint8 en_tx_mode;             /* 发送模式: rifs,aggr,normal发送 */
    oal_bool_enum_uint8     en_is_delba_ing;        /* 该tid是否正在发delba */
    oal_uint8               uc_rx_wrong_ampdu_num;  /* 该tid未建立BA会话时收到的聚合子帧数(一般是DELBA失败) */
    oal_uint8               uc_resv[2];
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru    *pst_tid_stats;           /* 该TID下入队、出队包数，丢包数统计 */
#endif
#endif
#ifdef _PRE_DEBUG_MODE
    dmac_tid_ampdu_stat_stru *pst_tid_ampdu_stat;    /* ampdu业务流程统计信息 */
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint16             us_last_seq_frag_num;          /* 保存的前一个QoS帧的seq + frag num */
    oal_uint8              auc_resv2[2];
#endif
}dmac_tid_stru;

/* 处理MPDU的MSDU的处理状态的结构体的定义 */
typedef struct
{
    oal_netbuf_stru        *pst_curr_netbuf;              /* 当前处理的netbuf指针 */
    oal_uint8              *puc_curr_netbuf_data;         /* 当前处理的netbuf的data指针 */
    oal_uint16              us_submsdu_offset;            /* 当前处理的submsdu的偏移量,   */
    oal_uint8               uc_msdu_nums_in_netbuf;       /* 当前netbuf包含的总的msdu数目 */
    oal_uint8               uc_procd_msdu_in_netbuf;      /* 当前netbuf中已处理的msdu数目 */
    oal_uint8               uc_netbuf_nums_in_mpdu;       /* 当前MPDU的中的总的netbuf的数目 */
    oal_uint8               uc_procd_netbuf_nums;         /* 当前MPDU中已处理的netbuf的数目 */
    oal_uint8               uc_procd_msdu_nums_in_mpdu;   /* 当前MPDU中已处理的MSDU数目 */

    oal_uint8               uc_flag;
}dmac_msdu_proc_state_stru;

/* 每一个MSDU包含的内容的结构体的定义 */
typedef struct
{
    oal_uint8               auc_sa[WLAN_MAC_ADDR_LEN];      /* MSDU发送的源地址 */
    oal_uint8               auc_da[WLAN_MAC_ADDR_LEN];      /* MSDU接收的目的地址 */
    oal_uint8               auc_ta[WLAN_MAC_ADDR_LEN];      /* MSDU接收的发送地址 */
    oal_uint8               uc_priority;
    oal_uint8               auc_resv[1];

    oal_netbuf_stru        *pst_netbuf;                     /* MSDU对应的netbuf指针(可以使clone的netbuf) */
}dmac_msdu_stru;

/* 复位原因定义 */
typedef enum
{
    DMAC_RESET_REASON_SW_ERR = 0,
    DMAC_RESET_REASON_HW_ERR,
    DMAC_RESET_REASON_CONFIG,
    DMAC_RETST_REASON_OVER_TEMP,

    DMAC_RESET_REASON_BUTT
}dmac_reset_mac_submod_enum;
typedef oal_uint8 dmac_reset_mac_submod_enum_uint8;

typedef struct
{
    hal_reset_hw_type_enum_uint8     uc_reset_type;        /*命令类型0|1|2|3(all|phy|mac|debug)*/
    hal_reset_mac_submod_enum_uint8  uc_reset_mac_mod;
    dmac_reset_mac_submod_enum_uint8 en_reason;
    oal_uint8 uc_reset_phy_reg;
    oal_uint8 uc_reset_mac_reg;
    oal_uint8 uc_debug_type;                              /*debug时，参数2复用为类型，0|1|2(mac reg|phy reg|lut)*/
    oal_uint8 uc_reset_rf_reg;
    oal_uint8 auc_resv[1];
}dmac_reset_para_stru;

typedef struct
{
    oal_uint8 uc_reason;
    oal_uint8 uc_event;
    oal_uint8 auc_des_addr[WLAN_MAC_ADDR_LEN];
}dmac_diasoc_deauth_event;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* 软件最优速率统计信息结构体 */
typedef struct
{
    oal_uint32      ul_best_rate_kbps;          /* 统计周期内的最优速率 */
    oal_uint16      us_best_rate_per;           /* 统计周期内最优速率下的平均per */
    oal_uint8       uc_best_rate_aggr_num;      /* 统计周期内最优速率的aggr */
    oal_uint8       uc_resv;
}dmac_best_rate_traffic_stat_info_stru;

typedef struct
{
    dmac_best_rate_traffic_stat_info_stru    ast_best_rate_stat[WLAN_WME_AC_BUTT];
}dmac_best_rate_stat_info_stru;
#endif

#define DMAC_QUERY_EVENT_LEN  (48)   /*消息内容的长度 */
typedef enum
{
    OAL_QUERY_STATION_INFO_EVENT      = 1,
    OAL_ATCMDSRV_DBB_NUM_INFO_EVENT   = 2,
    OAL_ATCMDSRV_FEM_PA_INFO_EVENT    = 3,
    OAL_ATCMDSRV_GET_RX_PKCG          = 4,
    OAL_ATCMDSRV_LTE_GPIO_CHECK       = 5,
    OAL_QUERY_EVNET_BUTT
}oal_query_event_id_enum;

typedef struct
{
    oal_uint8        query_event;
    oal_uint8        auc_query_sta_addr[WLAN_MAC_ADDR_LEN];
}dmac_query_request_event;
typedef struct
{
    oal_uint8        query_event;
    oal_int8        reserve[DMAC_QUERY_EVENT_LEN];
}dmac_query_response_event;
typedef struct
{
    oal_uint32   ul_event_para;       /*消息传输的数据*/
    oal_int16    s_always_rx_rssi;
    oal_uint8    uc_event_id;         /*消息号*/
    oal_uint8    uc_reserved;
}dmac_atcmdsrv_atcmd_response_event;


typedef struct
{
    oal_uint8        query_event;
    oal_uint8 auc_query_sta_addr[WLAN_MAC_ADDR_LEN];/*sta mac地址*/
}dmac_query_station_info_request_event;
typedef struct
{
    oal_uint8    query_event; /*消息号*/
    oal_uint16   asoc_id;     /* Association ID of the STA*/
    oal_int32    ul_signal;             /*信号强度*/
    oal_uint32   ul_rx_packets;     /* total packets received   */
    oal_uint32   ul_tx_packets;     /* total packets transmitted    */
    oal_uint32   ul_rx_bytes;       /* total bytes received     */
    oal_uint32   ul_tx_bytes;       /* total bytes transmitted  */
    oal_uint32   ul_tx_retries;      /*发送重传次数*/
    oal_uint32   ul_rx_dropped_misc;     /*接收失败次数*/
    oal_uint32   ul_tx_failed;     /* 发送失败次数  */
    oal_int16    s_free_power;  /*底噪*/
    oal_rate_info_stru st_txrate; /*vap当前速率*/
}dmac_query_station_info_response_event;

typedef struct
{
    oal_uint8   uc_p2p0_hal_vap_id;
    oal_uint8   uc_p2p_gocl_hal_vap_id;
    oal_uint8   uc_rsv[2];
}mac_add_vap_sync_data_stru;

typedef struct
{
    oal_uint32  ul_cycles;              /* 统计间隔时钟周期数 */
    oal_uint32  ul_sw_tx_succ_num;     /* 软件统计发送成功ppdu个数 */
    oal_uint32  ul_sw_tx_fail_num;     /* 软件统计发送失败ppdu个数 */
    oal_uint32  ul_sw_rx_ampdu_succ_num;     /* 软件统计接收成功的ampdu个数 */
    oal_uint32  ul_sw_rx_mpdu_succ_num;      /* 软件统计接收成功的mpdu个数 */
    oal_uint32  ul_sw_rx_ppdu_fail_num;      /* 软件统计接收失败的ppdu个数 */
    oal_uint32  ul_hw_rx_ampdu_fcs_fail_num;   /* 硬件统计接收ampdu fcs校验失败个数 */
    oal_uint32  ul_hw_rx_mpdu_fcs_fail_num;    /* 硬件统计接收mpdu fcs校验失败个数 */
}dmac_thruput_info_sync_stru;

typedef struct
{
    oal_uint32                   uc_dscr_status;
    oal_uint8                   mgmt_frame_id;
    oal_uint8                   uc_user_idx; //
}dmac_crx_mgmt_tx_status_stru;

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
typedef struct
{
    oal_uint32           ul_chan_report_for_te_a;  /* Channel Bit Map to register TE-A */
    oal_bool_enum_uint8  en_te_b;                  /* 20/40M intolerant for TE-B */
}dmac_obss_te_a_b_stru;
#endif


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
typedef enum
{
    DMAC_CONFIG_IPV4 = 0,                /* 配置IPv4地址 */
    DMAC_CONFIG_IPV6,                    /* 配置IPv6地址 */
    DMAC_CONFIG_BUTT
}dmac_ip_type;
typedef oal_uint8 dmac_ip_type_enum_uint8;

typedef enum
{
    DMAC_IP_ADDR_ADD = 0,                /* 增加IP地址 */
    DMAC_IP_ADDR_DEL,                    /* 删除IP地址 */
    DMAC_IP_OPER_BUTT
}dmac_ip_oper;
typedef oal_uint8 dmac_ip_oper_enum_uint8;

typedef struct
{
    dmac_ip_type_enum_uint8           en_type;
    dmac_ip_oper_enum_uint8           en_oper;

    oal_uint8                         auc_resv[2];

    oal_uint8                         auc_ip_addr[OAL_IP_ADDR_MAX_SIZE];
}dmac_ip_addr_config_stru;
#endif


/* 函数执行控制枚举 */
typedef enum
{
    DMAC_RX_FRAME_CTRL_GOON,        /* 本数据帧需要继续处理 */
    DMAC_RX_FRAME_CTRL_DROP,        /* 本数据帧需要丢弃 */
    DMAC_RX_FRAME_CTRL_BA_BUF,      /* 本数据帧被BA会话缓存 */

    DMAC_RX_FRAME_CTRL_BUTT
}dmac_rx_frame_ctrl_enum;
typedef oal_uint8 dmac_rx_frame_ctrl_enum_uint8;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#define HMAC_TO_DMAC_CFG_MSG_HDR_LEN  (OAL_SIZEOF(hmac_to_dmac_cfg_msg_stru) - 4)   /* 只取头的长度，去掉4字节auc_msg_body长度 */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
/* 裸系统cb字段信息获取 */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->bit_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)                 ((_pst_tx_ctrl)->bit_netbuf_num)
/* 从hcc头里面解析mpdu len */
/*lint -e778*/
#define MAC_GET_CB_MPDU_LEN(_pst_tx_ctrl)                (((hcc_header_stru *)((oal_uint8 *)(_pst_tx_ctrl) - (OAL_SIZEOF(hcc_header_stru) + OAL_PAD_HDR_LEN)))->pay_len)
#define MAC_GET_CB_IS_MCAST(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_ismcast)
#define MAC_GET_CB_IS_EAPOL(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_is_eapol)
#define MAC_GET_CB_IS_FROM_PS_QUEUE(_pst_tx_ctrl)        ((_pst_tx_ctrl)->en_is_get_from_ps_queue)
#define MAC_GET_CB_IS_FIRST_MSDU(_pst_tx_ctrl)           ((_pst_tx_ctrl)->en_is_first_msdu)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)     ((_pst_tx_ctrl)->bit_frame_header_length)
#define MAC_GET_CB_IS_VIPFRAME(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_is_vipframe)
#define MAC_GET_CB_IS_NEEDRETRY(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_is_needretry)

#define MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)   \
    (((mac_ieee80211_frame_stru *)((oal_uint8 *)_pst_tx_ctrl + OAL_MAX_CB_LEN))->st_frame_control.bit_type)
#define MAC_GET_CB_EN_FRAME_SUBTYPE(_pst_tx_ctrl)   \
    (((mac_ieee80211_qos_htc_frame_stru *)(_pst_tx_ctrl + 1))->st_frame_control.bit_sub_type)

#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)              ((_pst_tx_ctrl)->bit_en_event_type)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_tx_user_idx)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)               ((_pst_tx_ctrl)->uc_alg_pktno)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_retried_num)
#define MAC_GET_CB_IS_PROBE_DATA(_pst_tx_ctrl)           ((_pst_tx_ctrl)->en_is_probe_data)

#define MAC_GET_CB_TIMESTAMP(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->st_timestamp_us)
#define MAC_GET_CB_MPDU_BYTES(_pst_tx_ctrl)                 ((_pst_tx_ctrl)->us_mpdu_bytes)

/* DMAC模块接收流程控制信息结构体的信息元素获取 */

/* 02 51 mac_rx_ctl_stru 不同元素封装成宏 */
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_da_user_idx)
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_ta_user_idx)
#define MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl)               ((_pst_rx_ctl)->bit_mac_header_len)
#define MAC_GET_RX_CB_FRAME_LEN(_pst_rx_ctl)                    ((_pst_rx_ctl)->us_frame_len)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl,_pst_buf)           (OAL_NETBUF_PAYLOAD(_pst_buf))
#define MAC_GET_RX_CB_HAL_VAP_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_vap_id)

#else

/* 发送控制字段获取 */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->uc_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->uc_netbuf_num)
#define MAC_GET_CB_MPDU_LEN(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->us_mpdu_len)
#define MAC_GET_CB_IS_MCAST(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->en_ismcast)
#define MAC_GET_CB_IS_EAPOL(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->en_is_eapol)
#define MAC_GET_CB_IS_FROM_PS_QUEUE(_pst_tx_ctrl)               ((_pst_tx_ctrl)->en_is_get_from_ps_queue)
#define MAC_GET_CB_IS_FIRST_MSDU(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->uc_is_first_msdu)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)            ((_pst_tx_ctrl)->uc_frame_header_length)
#define MAC_GET_CB_IS_VIPFRAME(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->bit_is_vipframe)
#define MAC_GET_CB_IS_NEEDRETRY(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->bit_is_needretry)

#define MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_frame_type)

#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_event_type)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->uc_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->us_tx_user_idx)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)                      ((_pst_tx_ctrl)->ul_alg_pktno)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->uc_retried_num)
#define MAC_GET_CB_IS_PROBE_DATA(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->en_is_probe_data)
#define MAC_GET_CB_TIMESTAMP(_pst_tx_ctrl)                      ((_pst_tx_ctrl)->st_timestamp_us)
#define MAC_GET_CB_MPDU_BYTES(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->us_mpdu_bytes)

/* DMAC模块接收流程控制信息结构体的信息元素获取 */

/* 02有，51没有的字段 */
#define MAC_GET_RX_CB_BIT_PROTOCOL_MODE(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_NSS_MCS_RATE(_pst_cb_ctrl)
#define MAC_GET_RX_CB_RSSI(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_RESPONSE_FLAG(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_VAP_INDEX(_pst_cb_ctrl)
#define MAC_GET_RX_ITRUP_SEQ_NUM(_pst_cb_ctrl)
#define MAC_GET_RX_CB_MAC_HDR_LEN(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_NUM_RX_BUFFERS(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_RECV_FLAGSS(_pst_cb_ctrl)
#define MAC_GET_RX_CB_NUM_MSDUS_IN_CUR_RX_BUFFER(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_CODE_BOOK(_pst_cb_ctrl)

/* 02 51 mac_rx_ctl_stru 不同元素封装成宏 */
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_da_user_idx)
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_ta_user_idx)
#define MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl)               ((_pst_rx_ctl)->uc_mac_header_len)
#define MAC_GET_RX_CB_FRAME_LEN(_pst_rx_ctl)                    ((_pst_rx_ctl)->us_frame_len)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl, _pst_buf) \
((oal_uint8 *)(mac_get_rx_cb_mac_hdr(_pst_rx_ctl)) + MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl))
#define MAC_GET_RX_CB_HAL_VAP_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_vap_id)

#endif

/*****************************************************************************
 函 数 名  : dmac_board_get_instance
 功能描述  : 获取DMAC board对象
 输入参数  : 无
 输出参数  : DMAC board对象引用
 返 回 值  : 物
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_board_get_instance(mac_board_stru **ppst_dmac_board)
{
    *ppst_dmac_board = &g_st_dmac_board;
}

/*****************************************************************************
 函 数 名  : dmac_rx_free_netbuf_list
 功能描述  : 从当前的netbuf指针开始，释放后续n个netbuf元素
 输入参数  : (1)指向netbuf链表头的指针
             (2)释放的个数
 输出参数  : 返回下一个要处理的netbuf指针
 返 回 值  : 期望的netbuf的指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_free_netbuf_list(
                oal_netbuf_head_stru       *pst_netbuf_hdr,
                oal_netbuf_stru           **pst_netbuf,
                oal_uint16                  us_nums)
{
    oal_netbuf_stru    *pst_netbuf_temp;
    oal_uint16          us_netbuf_num;
#ifdef _PRE_MEM_DEBUG_MODE
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        oal_uint32 ul_return_addr      = __return_address();
#endif
#endif

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_netbuf_hdr) || (OAL_PTR_NULL == pst_netbuf)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (us_netbuf_num = 0; us_netbuf_num < us_nums; us_netbuf_num++)
    {
        pst_netbuf_temp = oal_get_netbuf_next(*pst_netbuf);

        oal_netbuf_delete(*pst_netbuf, pst_netbuf_hdr);

        if(OAL_ERR_CODE_OAL_MEM_ALREADY_FREE==oal_netbuf_free(*pst_netbuf))
        {
           #ifdef _PRE_MEM_DEBUG_MODE
           #if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
            OAL_IO_PRINT("double free caller[%x]!\r\n",ul_return_addr);
           #endif
           #endif
        }

        *pst_netbuf = pst_netbuf_temp;
        if (pst_netbuf_hdr ==  (oal_netbuf_head_stru*)(*pst_netbuf))
        {
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_bar
 功能描述  : 判断某个帧是否是bar
 输入参数  : pst_tx_ctrl CB
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    mac_ieee80211_qos_htc_frame_stru   *pst_mac_naked_frame;

    pst_mac_naked_frame = (mac_ieee80211_qos_htc_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);

    if ((WLAN_CONTROL      == pst_mac_naked_frame->st_frame_control.bit_type) &&
        (WLAN_BLOCKACK_REQ == pst_mac_naked_frame ->st_frame_control.bit_sub_type))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
#else
    return pst_tx_ctrl->en_is_bar;

#endif
}

/*****************************************************************************
 函 数 名  : mac_set_cb_is_bar
 功能描述  : 设置bar帧
 输入参数  : pst_tx_ctrl CB
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_bar)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
   return;                                      //裸系统不操作
#else
   pst_tx_ctrl->en_is_bar = uc_bar;
#endif
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_qosdata
 功能描述  : 判断某个帧是否是bar
 输入参数  : pst_tx_ctrl CB
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    mac_ieee80211_qos_htc_frame_stru   *pst_mac_qos_htc_frame;
    oal_uint8                           ul_ret = OAL_FALSE;

    pst_mac_qos_htc_frame = (mac_ieee80211_qos_htc_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);

    if (WLAN_DATA_BASICTYPE == pst_mac_qos_htc_frame->st_frame_control.bit_type)
    {
        if ((WLAN_QOS_DATA       == pst_mac_qos_htc_frame->st_frame_control.bit_sub_type) ||
            (WLAN_QOS_NULL_FRAME == pst_mac_qos_htc_frame->st_frame_control.bit_sub_type))
        {
            ul_ret = OAL_TRUE;
        }
    }

    return ul_ret;
#else
    return pst_tx_ctrl->en_is_qosdata;

#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_qosdata
 功能描述  : 判断某个帧是否是bar
 输入参数  : pst_tx_ctrl CB
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_is_qosdata)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->en_is_qosdata = uc_en_is_qosdata;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_rx_cb_mac_hdr
 功能描述  : 设置mac头的值
 输入参数  : dmac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_cb_ctrl->pul_mac_hdr_start_addr = pul_mac_hdr_start_addr;

#endif
}
/*****************************************************************************
 函 数 名  : mac_get_rx_cb_mac_hdr
 功能描述  : 获取mac头的值
 输入参数  : dmac_rx_ctl_stru *pst_cb_ctrl
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return (oal_uint32 *)((oal_uint8 *)pst_cb_ctrl + OAL_MAX_CB_LEN);
#else
    return pst_cb_ctrl->pul_mac_hdr_start_addr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_tid
 功能描述  : 获取tid的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return pst_tx_ctrl->bit_tid;
#else
    return pst_tx_ctrl->uc_tid;
#endif
}

/*****************************************************************************
 函 数 名  : mac_set_cb_tid
 功能描述  : 设置tid的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年1月21日
    作    者   : 
    修改内容   : 修改偏移地址到netbuf->data

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_tid)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    pst_tx_ctrl->bit_tid = (uc_tid & 0x0F);
#else
    pst_tx_ctrl->uc_tid = uc_tid;

#endif
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_amsdu
 功能描述  : 获取amsdu的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_amsdu(mac_tx_ctl_stru *pst_tx_ctrl)
{
    return pst_tx_ctrl->en_is_amsdu;
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_amsdu
 功能描述  : 设置amsdu的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_amsdu(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_amsdu)
{
    pst_tx_ctrl->en_is_amsdu = uc_amsdu;
}
/*****************************************************************************
 函 数 名  : mac_get_cb_ack_policy
 功能描述  : 获取ack_policy的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_ack_policy(mac_tx_ctl_stru *pst_tx_ctrl)
{
    return pst_tx_ctrl->en_ack_policy;
}
/*****************************************************************************
 函 数 名  : mac_set_cb_ack_policy
 功能描述  : 设置ack_policy的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_ack_policy(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_qc_ack_polocy)
{
    pst_tx_ctrl->en_ack_policy = uc_qc_ack_polocy;
}
/*****************************************************************************
 函 数 名  : mac_get_cb_seqnum
 功能描述  : 获取seqnum的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint16 mac_get_cb_seqnum(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return ((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->bit_seq_num;
#else
    return pst_tx_ctrl->us_seqnum;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_ack_policy
 功能描述  : 设置ack_policy的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_seqnum(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint16 us_sc_seq_num)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
   ((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->bit_seq_num = us_sc_seq_num;
#else
    pst_tx_ctrl->us_seqnum = us_sc_seq_num;
#endif
}

/*****************************************************************************
 函 数 名  : mac_set_cb_sub_type
 功能描述  : 设置subtype的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_subtype
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_sub_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_subtype)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    (((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->st_frame_control.bit_sub_type) = uc_subtype;

#else
    return;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_ac
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_wme_ac_type_enum_uint8 mac_get_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    //oal_uint8   uc_tid = mac_get_cb_tid(pst_tx_ctrl);
    //return (WLAN_WME_TID_TO_AC(uc_tid));
    return pst_tx_ctrl->bit_ac;
#else
    return pst_tx_ctrl->uc_ac;

#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_ac
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_wme_ac_type)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    pst_tx_ctrl->bit_ac = uc_wme_ac_type;
#else
    pst_tx_ctrl->uc_ac = uc_wme_ac_type;

#endif
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_wme_ac_type_enum_uint8 mac_get_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return OAL_FALSE;
#else
    return pst_tx_ctrl->en_need_pause_tid;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_en_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_need_pause_tid)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->en_need_pause_tid = uc_en_need_pause_tid;
#endif
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_ieee80211_frame_stru *mac_get_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    mac_ieee80211_frame_stru *pst_frame_header;
    pst_frame_header = (mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);
    return pst_frame_header;
#else
    return pst_tx_ctrl->pst_frame_header;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl, mac_ieee80211_frame_stru *pst_mac_hdr_addr)
{
#if (_PRE_PRODUCT_ID_HI1131C_DEV == _PRE_PRODUCT_ID)
    return;
#else
    pst_tx_ctrl->pst_frame_header = pst_mac_hdr_addr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_use_4_addr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return OAL_FALSE;
#else
    return pst_tx_ctrl->en_use_4_addr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_use_4_addr(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_is_use_4_addr)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->en_use_4_addr = uc_en_is_use_4_addr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_bar_dscr
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE hal_tx_dscr_stru *mac_get_cb_bar_dscr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return OAL_PTR_NULL;
#else
    return pst_tx_ctrl->pst_bar_dscr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_need_pause_tid
 功能描述  : 设置ac的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_bar_dscr(mac_tx_ctl_stru *pst_tx_ctrl, hal_tx_dscr_stru *pst_bar_dscr)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->pst_bar_dscr = pst_bar_dscr;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_80211_mac_head_type
 功能描述  : 设置bit_80211_mac_head_type的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_80211_mac_head_type(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return 1; //02是要return 0 还是 1?
#else
    return pst_tx_ctrl->bit_80211_mac_head_type;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_80211_mac_head_type
 功能描述  : 设置bit_80211_mac_head_type的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_80211_mac_head_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_80211_mac_head_type)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->bit_80211_mac_head_type = uc_80211_mac_head_type;
#endif
}

/*****************************************************************************
 函 数 名  : mac_get_cb_is_seq_ctrl_bypass
 功能描述  : 获取en_seq_ctrl_bypass的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_seq_ctrl_bypass(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return mac_get_cb_is_qosdata(pst_tx_ctrl);
#else
    return pst_tx_ctrl->en_seq_ctrl_bypass;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_seq_ctrl_bypass
 功能描述  : 设置bit_80211_mac_head_type的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_seq_ctrl_bypass(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_seq_ctrl_bypass)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->en_seq_ctrl_bypass = uc_en_seq_ctrl_bypass;
#endif
}
/*****************************************************************************
 函 数 名  : mac_get_cb_event_sub_type
 功能描述  : 获取uc_event_sub_type的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_event_sub_type(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return 0;
#else
    return pst_tx_ctrl->uc_event_sub_type;
#endif
}
/*****************************************************************************
 函 数 名  : mac_set_cb_is_seq_ctrl_bypass
 功能描述  : 设置bit_80211_mac_head_type的值
 输入参数  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_event_sub_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_event_sub_type)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    return;
#else
    pst_tx_ctrl->uc_event_sub_type = uc_en_event_sub_type;

#endif
}


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32  dmac_main_init(oal_void);
extern oal_void  dmac_main_exit(oal_void);
extern oal_void  dmac_alg_config_event_register(oal_uint32 p_func(frw_event_mem_stru *));
extern oal_void  dmac_alg_config_event_unregister(oal_void);
extern oal_uint32  dmac_tx_dump_get_switch(
                                    oam_user_track_frame_type_enum_uint8     en_frame_type,
                                    oal_uint8                               *pen_frame_switch,
                                    oal_uint8                               *pen_cb_switch,
                                    oal_uint8                               *pen_dscr_switch,
                                    mac_tx_ctl_stru                         *pst_tx_cb);
extern oal_uint32  dmac_tx_dump_get_user_macaddr(mac_tx_ctl_stru *pst_tx_cb,
                                             oal_uint8        auc_user_macaddr[]);

#ifdef _PRE_WLAN_PERFORM_STAT

/* 性能统计模块对外接口 */

typedef enum
{
    DMAC_STAT_TX      = 0,      /* 与DMAC_STAT_PER_MAC_TOTAL对应 */
    DMAC_STAT_RX      = 1,      /* 与DMAC_STAT_PER_BUFF_OVERFLOW对应 */
    DMAC_STAT_BOTH    = 2,      /* 与DMAC_STAT_PER_BUFF_BE_SEIZED对应 */

    DMAC_STAT_BUTT
}dmac_stat_direct;
typedef oal_uint8 dmac_stat_direct_enum_uint8;

typedef enum
{
    DMAC_STAT_PER_MAC_TOTAL             = 0,

    DMAC_STAT_PER_BUFF_OVERFLOW         = 1,
    DMAC_STAT_PER_BUFF_BE_SEIZED        = 2,
    DMAC_STAT_PER_DELAY_OVERTIME        = 3,
    DMAC_STAT_PER_SW_RETRY_AMPDU        = 4,
    DMAC_STAT_PER_SW_RETRY_SUB_AMPDU    = 5,
    DMAC_STAT_PER_SW_RETRY_MPDU         = 6,
    DMAC_STAT_PER_SW_RETRY_OVERFLOW     = 7,

    DMAC_STAT_PER_RTS_FAIL              = 8,
    DMAC_STAT_PER_HW_SW_FAIL            = 9,

    DMAC_STAT_PER_BUTT
}dmac_stat_per_reason;
typedef oal_uint8 dmac_stat_per_reason_enum_uint8;

typedef struct
{
    oam_module_id_enum_uint16      en_module_id;                    /* 对应的模块id */
    mac_stat_type_enum_uint8       en_stat_type;                    /* 统计类型 */
    oal_uint8                      uc_resv[1];

    oal_void                      *p_void;                          /* tid,user或者vap指针 */
    oal_uint32                     aul_stat_avg[DMAC_STAT_PER_BUTT];    /* 某个周期的统计结果 */
}dmac_stat_param_stru;

/* 供内部模块调用的统计定时器到期处理函数指针 */
typedef oal_uint32  (*dmac_stat_timeout_func)(dmac_stat_param_stru *);

extern oal_uint32  dmac_stat_register(oam_module_id_enum_uint16         en_module_id,
                                        mac_stat_type_enum_uint8        en_stat_type,
                                        oal_void                       *p_void,
                                        dmac_stat_param_stru           *p_output_param,
                                        dmac_stat_timeout_func          p_func,
										oal_uint32						ul_core_id);

extern oal_uint32	dmac_stat_start(oam_module_id_enum_uint16      en_module_id,
                                     mac_stat_type_enum_uint8      en_stat_type,
                                     oal_uint16                    us_stat_period,
                                     oal_uint16                    us_stat_num,
                                     oal_void                      *p_void);

extern oal_uint32	dmac_stat_stop(oam_module_id_enum_uint16      en_module_id,
                                     mac_stat_type_enum_uint8     en_stat_type,
                                     oal_void                    *p_void);

extern oal_uint32	dmac_stat_unregister(oam_module_id_enum_uint16      en_module_id,
                                         mac_stat_type_enum_uint8       en_stat_type,
                                         oal_void                      *p_void);

#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  mac_user_check_txrx_protocol_change(
                                  mac_user_stru *pst_mac_user,
                                  oal_uint8      uc_present_mode,
                                  oam_user_info_change_type_enum_uint8  en_type);
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
extern oal_uint32 dmac_stat_tid_per(mac_user_stru *pst_dmac_user,
                                    oal_uint8 uc_tidno,
                                    oal_uint16 us_mpdu_num,
                                    oal_uint16 us_err_mpdu_num,
                                    dmac_stat_per_reason_enum_uint8 en_per_reason);
#endif
extern oal_uint32  dmac_tid_pause(dmac_tid_stru *pst_tid, oal_uint8 uc_type);
extern oal_uint32  dmac_tid_resume(hal_to_dmac_device_stru *pst_hal_device, dmac_tid_stru *pst_tid, oal_uint8 uc_type);
extern oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr);
extern oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl);
extern oal_uint8 mac_get_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_bar);
extern oal_uint8 mac_get_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_qosdata(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8  uc_qos);
extern oal_void mac_set_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_need_pause_tid);
extern oal_uint8 mac_get_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_tid);
extern wlan_wme_ac_type_enum_uint8 mac_get_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_wme_ac_type);
extern wlan_wme_ac_type_enum_uint8 mac_get_cb_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl);
extern mac_ieee80211_frame_stru *mac_get_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl, mac_ieee80211_frame_stru *pul_mac_hdr_addr);
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32  dmac_config_set_qap_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#if (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
extern oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#if 0
extern oal_uint32 dmac_init_event_create_cfg_vap(frw_event_mem_stru *pst_event_mem);
#else
extern oal_uint32 dmac_cfg_vap_init_event(frw_event_mem_stru *pst_event_mem);
#endif

#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*TBD，待修订为同步，删除该逻辑*/
extern oal_uint32  dmac_custom_sync(mac_vap_stru *pst_mac_vap);
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_ext_if.h */
