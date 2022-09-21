/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_sta_pm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年11月25日
  最近修改   :
  功能描述   : dmac_sta_pm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月25日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_STS_PM_H__
#define __DMAC_STS_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_device.h"
#include "mac_frame.h"
#include "mac_pm.h"
#include "dmac_vap.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STA_PM_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WLAN_NBBY      8
//#define WLAN_TIM_ISSET(a,i) ((a)[(i)/WLAN_NBBY] & (1<<((i)%WLAN_NBBY)))
#define WLAN_TIM_ISSET(a,i) ((a)[(i)>>3] & (1<<((i)&0x7)))
#define LISTEN_INTERVAL_TO_DITM_TIMES   4
#define MIN_ACTIVITY_TIME_OUT 20000   /* 500 ms */
#define MAX_ACTIVITY_TIME_OUT 20000 /* 10 sec */
#define WLAN_PS_KEEPALIVE_MAX_NUM   300 /* 300 DTIM1 interval*/
#define WLAN_MAX_NULL_SENT_NUM      10  /* NULL帧最大重传次数 */
#define STA_GET_PM_STATE(_pst_handler)    ((_pst_handler)->p_mac_fsm->uc_cur_state)/* 获取当前状态机的状态 */
#define DMAC_TIMER_DOZE_TRANS_FAIL_NUM        10
#define DMAC_STATE_DOZE_TRANS_FAIL_NUM        2          //连续N次切doze失败输出维测
#define DMAC_BEACON_DOZE_TRANS_FAIL_NUM       2
#define DMAC_BEACON_TIMEOUT_MAX_TIME          1000 //收不到beacon最大睡眠时间,单位ms

#if defined(_PRE_DEBUG_MODE)
#define DMAC_STA_UAPSD_STATS_INCR(_member)    ((_member)++)
#define DMAC_STA_PSM_STATS_INCR(_member)      ((_member)++)
#elif defined(_PRE_PSM_DEBUG_MODE)
#define DMAC_STA_PSM_STATS_INCR(_member)    ((_member)++)
#define DMAC_STA_UAPSD_STATS_INCR(_member)
#else
#define DMAC_STA_UAPSD_STATS_INCR(_member)
#define DMAC_STA_PSM_STATS_INCR(_member)
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* TIM processing result */
typedef enum
{
    DMAC_TIM_IS_SET  = 1,
    DMAC_DTIM_IS_SET = 2,

    DMAC_TIM_PROC_BUTT
} dmac_tim_proc_enum;

typedef enum {
    STA_PWR_SAVE_STATE_ACTIVE = 0,         /* active状态 */
    STA_PWR_SAVE_STATE_DOZE,               /* doze状态 */
    STA_PWR_SAVE_STATE_AWAKE,              /* wake状态*/

    STA_PWR_SAVE_STATE_BUTT                /*最大状态*/
} sta_pwr_save_state_info;

typedef enum {
    STA_PWR_EVENT_TX_DATA = 0,              /* DOZE状态下的发送事件 */
    STA_PWR_EVENT_TBTT,                     /* DOZE状态下的TBTT事件 */
    STA_PWR_EVENT_FORCE_AWAKE,              /* DOZE状态下后tbtt唤醒还没上来,手动强制唤醒 */
    STA_PWR_EVENT_RX_UCAST,                 /* AWAKE状态下接收单播  */
    STA_PWR_EVENT_LAST_MCAST = 4,           /* AWAKE状态下最后一个组播/广播 */
    STA_PWR_EVENT_TIM,                      /* AWAKE状态下的TIM事件 */
    STA_PWR_EVENT_DTIM,                     /* AWAKE状态下的DTIM事件 */
    STA_PWR_EVENT_NORMAL_SLEEP,
    STA_PWR_EVENT_BEACON_TIMEOUT  = 8,      /* AWAKE状态下睡眠事件 */
    STA_PWR_EVENT_SEND_NULL_SUCCESS,        /* 三种状态下都有NULL帧发送成功事件 */
    STA_PWR_EVENT_TIMEOUT,                  /* ACTIVE/AWAKE状态下超时事件 */
    STA_PWR_EVENT_KEEPALIVE,                /* ACTIVE状态下非节能模式下keepalive事件 */
    STA_PWR_EVENT_NO_POWERSAVE = 12,        /* DOZE/AWAKE状态下非节能模式 */
    STA_PWR_EVENT_P2P_SLEEP,                /* P2P SLEEP */
    STA_PWR_EVENT_P2P_AWAKE,                /* P2P AWAKE */
    STA_PWR_EVENT_DETATCH,                  /* 销毁低功耗状态机事件 */
    STA_PWR_EVENT_DEASSOCIATE,              /* 去关联*/
    STA_PWR_EVENT_TX_MGMT,                  /* 发送管理帧开启前端 */
    STA_PWR_EVENT_BUTT
}sta_pwr_save_event;


typedef enum _PM_DEBUG_MSG_TYPE_{
    PM_MSG_WAKE_TO_ACTIVE = 0,
    PM_MSG_WAKE_TO_DOZE,
    PM_MSG_ACTIVE_TO_DOZE,
    PM_MSG_TBTT_CNT, /* tbtt count */
    PM_MSG_PSM_BEACON_CNT,
    PM_MSG_BEACON_TIMEOUT_CNT,
    PM_MSG_PROCESS_DOZE_CNT,
    PM_MSG_BCN_TOUT_SLEEP,
    PM_MSG_DEEP_DOZE_CNT = 8,
    PM_MSG_LIGHT_DOZE_CNT,
    PM_MSG_LAST_DTIM_SLEEP,
    PM_MSG_SCAN_DIS_ALLOW_SLEEP,
    PM_MSG_DBAC_DIS_ALLOW_SLEEP,
    PM_MSG_FREQ_DIS_ALLOW_SLEEP,
    PM_MSG_BCNTIMOUT_DIS_ALLOW_SLEEP,
    PM_MSG_HOST_AWAKE,
    PM_MSG_DTIM_AWAKE,
    PM_MSG_TIM_AWAKE,
    /* 超时定时器处理 */
    PM_MSG_PSM_TIMEOUT_PM_OFF  = 18,
    PM_MSG_PSM_TIMEOUT_QUEUE_NO_EMPTY,
    PM_MSG_PSM_RESTART_A,
    PM_MSG_PSM_RESTART_B,
    PM_MSG_PSM_RESTART_C,
    PM_MSG_PSM_TIMEOUT_PKT_CNT  =23,
    PM_MSG_PSM_RESTART_P2P_PAUSE,
    PM_MSG_PSM_P2P_SLEEP,
    PM_MSG_PSM_P2P_AWAKE,
    PM_MSG_PSM_P2P_PS,
    PM_MSG_NULL_NOT_SLEEP,
    PM_MSG_COUNT = 29
}PM_DEBUG_MSG_TYPE;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern    oal_uint32   g_lightsleep_fe_awake_cnt;
extern    oal_uint32   g_deepsleep_fe_awake_cnt;
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
    oal_uint8    en_active_null_wait : 1; /* STA发送NULL帧给AP提示进入ACTIVE 状态 */
    oal_uint8    en_doze_null_wait  :1;   /* STA发送NULL帧给AP提示进入doze状态*/
} dmac_vap_null_wait_stru;

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint32 ul_wmmpssta_tacdl;       /* Trigger enabled Downlink traffic exception.          */
    oal_uint32 ul_wmmpssta_dacul;        /* Delivery enabled Uplink traffic exception.             */
    oal_uint32 ul_wmmpssta_spsw;        /* Wait for service period start.                       */
    oal_uint32 ul_wmmpssta_sps;         /* Service period start                                 */
    oal_uint32 ul_wmmpssta_spe;         /* Service period end                                   */
    oal_uint32 ul_wmmpssta_trigsp;      /* Trigger service period                               */
    oal_uint32 ul_wmmpssta_trspnr;      /* Trigger service period is not required               */
}dmac_wmmps_info_stru;

#elif defined(_PRE_PSM_DEBUG_MODE)

#endif

typedef enum
{
    STA_PS_DEEP_SLEEP   = 0,
    STA_PS_LIGHT_SLEEP  = 1
}ps_mode_state_enum;

typedef  enum
{
    DMAC_SP_NOT_IN_PROGRESS         = 0,
    DMAC_SP_WAIT_START              = 1,
    DMAC_SP_IN_PROGRESS             = 2,
    DMAC_SP_UAPSD_STAT_BUTT
}dmac_uapsd_sp_stat_sta_enum;

/* STA 侧pm管理结构定义*/
typedef struct _mac_sta_pm_handler
{
    mac_fsm_stru                    *p_mac_fsm;                                 /*节能状态机*/
    frw_timeout_stru                st_inactive_timer;                          /* 定时器 */

    oal_uint32                      ul_tx_rx_activity_cnt;                      /* ACTIVE统计值，由超时进入DOZE复位 */
    oal_uint32                      ul_activity_timeout;                        /* 定时器超时时间 */
    oal_uint32                      ul_ps_keepalive_cnt;                        /* STA侧节能状态下keepalive机制统计接收beacon数*/
    oal_uint32                      ul_ps_keepalive_max_num;                    /* STA侧节能状态下keepalive机制最大接收beacon数 */

    oal_uint8                       uc_vap_ps_mode;                             /*  sta当前省电模式 */

    oal_uint8                       en_beacon_frame_wait            :1;         /* 提示接收beacon帧 */
    oal_uint8                       en_more_data_expected           :1;         /* 提示AP中有更多的缓存帧 */
    oal_uint8                       en_send_null_delay              :1;         /* 延迟发送NULL帧开关 */
    oal_uint8                       en_ps_deep_sleep                :1;         /* 是否是doze下的深睡 */
    oal_uint8                       en_send_active_null_frame_to_ap :1;         /* FAST模式下发送NULL进入ACTIVE */
    oal_uint8                       en_hw_ps_enable                 :1;         /* 开启全系统低功耗/协议栈低功耗 */
    oal_uint8                       en_ps_back_active_pause         :1;         /* ps back 延迟发送唤醒null帧 */
    oal_uint8                       en_ps_back_doze_pause           :1;         /* ps back 延迟发送睡眠null帧 */

    oal_uint8                       uc_timer_fail_doze_trans_cnt;               /* 超时函数内发null切doze失败次数 */
    oal_uint8                       uc_state_fail_doze_trans_cnt;               /* 切doze时,由于条件不满足失败计数 */

    oal_uint8                       uc_beacon_fail_doze_trans_cnt;              /* 收beacon 投票睡眠却却无法睡下去的计数 */
    oal_uint8                       uc_doze_event;                              /* 记录切状态的事件类型 */
    oal_uint8                       uc_awake_event;
    oal_uint8                       uc_active_event;

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    oal_uint8                       uc_eosp_timeout_cnt;                        /* uapsd省电中TBTT计数器 */
    oal_uint8                       uc_uaspd_sp_status;                         /* UAPSD的状态 */
#endif
    oal_uint8                       uc_doze_null_retran_cnt;
    oal_uint8                       uc_active_null_retran_cnt;

    dmac_vap_null_wait_stru         st_null_wait;                               /* STA发送NULL帧切换状态时，各状态NULL帧等待状态的结构体*/
#ifdef _PRE_DEBUG_MODE
    dmac_wmmps_info_stru            st_wmmps_info;                              /* STA侧uapsd的维测信息 */
#endif
    oal_uint32                      aul_pmDebugCount[PM_MSG_COUNT];
    oal_uint32                      ul_psm_pkt_cnt;
    oal_uint8                       uc_psm_timer_restart_cnt;                   /* 重启睡眠定时器的count */
    oal_uint8                       uc_can_sta_sleep;                           /* 协议允许切到doze,是否能投票睡眠 */
    oal_uint8                       uc_resrv[2];
} mac_sta_pm_handler_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event);
extern oal_uint32 dmac_pm_sta_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data);
extern mac_sta_pm_handler_stru * dmac_pm_sta_attach(oal_void* pst_oshandler);
extern oal_void dmac_pm_sta_detach(oal_void* pst_oshandler);
extern oal_void dmac_sta_initialize_psm_globals(mac_sta_pm_handler_stru *p_handler);
extern oal_void dmac_pm_enable_front_end(mac_device_stru   *pst_mac_device, oal_uint8 uc_enable_paldo);
extern oal_void dmac_pm_key_info_dump(dmac_vap_stru  *pst_dmac_vap);
extern oal_void dmac_pm_enable_front_end_ram(mac_device_stru *pst_mac_device, oal_uint8 uc_enable_paldo);


#endif /* _PRE_WLAN_FEATURE_STA_PM*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_sts_pm.h */
