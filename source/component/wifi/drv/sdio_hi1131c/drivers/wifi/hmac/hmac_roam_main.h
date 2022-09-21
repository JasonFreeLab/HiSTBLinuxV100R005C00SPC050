/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_roam_main.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2015年3月18日
  最近修改   :
  功能描述   : hmac_roam_main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月18日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_ROAM_MAIN_H__
#define __HMAC_ROAM_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_MAIN_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define ROAM_SCAN_TIME_MAX        (5 * 1000)       /* 扫描超时时间 单位ms*/
#define ROAM_CONNECT_TIME_MAX     (8 * 1000)       /* 关联超时时间 单位ms*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 漫游主状态机状态 */
typedef enum
{
    ROAM_MAIN_STATE_INIT               = 0,
    ROAM_MAIN_STATE_FAIL               = ROAM_MAIN_STATE_INIT,
    ROAM_MAIN_STATE_SCANING            = 1,
    ROAM_MAIN_STATE_CONNECTING         = 2,
    ROAM_MAIN_STATE_UP                 = 3,

    ROAM_MAIN_STATE_BUTT
}roam_main_state_enum;
typedef oal_uint8  roam_main_state_enum_uint8;

/* 漫游主状态机事件类型 */
typedef enum
{
    ROAM_MAIN_FSM_EVENT_START          = 0,
    ROAM_MAIN_FSM_EVENT_SCAN_RESULT    = 1,
    ROAM_MAIN_FSM_EVENT_START_CONNECT  = 2,
    ROAM_MAIN_FSM_EVENT_CONNECT_FAIL   = 3,
    ROAM_MAIN_FSM_EVENT_HANDSHAKE_FAIL = 4,
    ROAM_MAIN_FSM_EVENT_CONNECT_SUCC   = 5,
    ROAM_MAIN_FSM_EVENT_TIMEOUT        = 6,
    ROAM_MAIN_FSM_EVENT_TYPE_BUTT
}roam_main_fsm_event_type_enum;

#define ROAM_BAND_2G_BIT BIT0

#ifdef _PRE_WLAN_FEATURE_5G
#define ROAM_BAND_5G_BIT BIT1
#endif /* _PRE_WLAN_FEATURE_5G */

/* 漫游扫描信道正交属性参数,命令行传入*/
typedef enum
{
    ROAM_SCAN_CHANNEL_ORG_1       = 1, //2.4G channel 1\6\11
    ROAM_SCAN_CHANNEL_ORG_3       = 3, //2.4G channel 1\5\7\11
    ROAM_SCAN_CHANNEL_ORG_BUTT
}roam_channel_org_enum;
typedef oal_uint8  roam_channel_org_enum_uint8;
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
/* 漫游配置结构体 */
typedef struct
{
    oal_uint8                       uc_scan_band;                /* 扫描频段 */
    roam_channel_org_enum_uint8     uc_scan_orthogonal;          /* 扫描信道正交属性 */
    oal_int8                        c_trigger_rssi_2G;           /* 2G时的触发门限 */
    oal_int8                        c_trigger_rssi_5G;           /* 5G时的触发门限 */
    oal_uint8                       uc_delta_rssi_2G;            /* 2G时的增益门限 */
    oal_uint8                       uc_delta_rssi_5G;            /* 5G时的增益门限 */
    oal_uint8                       auc_recv[2];
    oal_uint32                      ul_blacklist_expire_sec;     /* not used for now */
    oal_uint32                      ul_buffer_max;               /* not used for now */
}hmac_roam_config_stru;

/* 漫游统计结构体 */
typedef struct
{
    oal_uint32                 ul_trigger_rssi_cnt;             /* rssi触发漫游扫描计数 */
    oal_uint32                 ul_trigger_linkloss_cnt;         /* linkloss触发漫游扫描计数 */
    oal_uint32                 ul_scan_cnt;                     /* 漫游扫描次数 */
    oal_uint32                 ul_scan_result_cnt;              /* 漫游扫描返回次数 */
    oal_uint32                 ul_connect_cnt;                  /* 漫游连接计数 */
    oal_uint32                 ul_roam_old_cnt;                 /* 漫游失败计数 */
    oal_uint32                 ul_roam_new_cnt;                 /* 漫游成功计数 */
}hmac_roam_static_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
oal_uint32 hmac_roam_enable(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_enable);
oal_uint32 hmac_roam_band(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_scan_band);
oal_uint32 hmac_roam_org(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_scan_orthogonal);
oal_uint32 hmac_roam_start(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_show(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_init(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_info_init(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_exit(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_test(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_resume_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param);
oal_uint32 hmac_roam_pause_user(hmac_vap_stru *pst_hmac_vap, oal_void *p_param);
oal_uint32 hmac_sta_roam_rx_mgmt(hmac_vap_stru *pst_hmac_vap, oal_void *p_param);
oal_uint32 hmac_roam_trigger_handle(hmac_vap_stru *pst_hmac_vap, oal_int8 c_rssi);
oal_void hmac_roam_tbtt_handle(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_scan_complete(hmac_vap_stru *pst_hmac_vap);
oal_void hmac_roam_connect_complete(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_result);
oal_void  hmac_roam_add_key_done(hmac_vap_stru *pst_hmac_vap);
oal_void  hmac_roam_wpas_connect_state_notify(hmac_vap_stru *pst_hmac_vap, wpas_connect_state_enum_uint32 conn_state);
oal_uint32 hmac_roam_ignore_rssi_trigger(hmac_vap_stru *pst_hmac_vap, oal_bool_enum_uint8 en_val);
oal_uint32 hmac_roam_check_bkscan_result(hmac_vap_stru *pst_hmac_vap, void *p_scan_record);
#ifdef _PRE_WLAN_FEATURE_11R
oal_uint32 hmac_roam_reassoc(hmac_vap_stru *pst_hmac_vap);
oal_uint32 hmac_roam_rx_ft_action(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);
#endif //_PRE_WLAN_FEATURE_11R
oal_void hmac_roam_timeout_test(hmac_vap_stru *pst_hmac_vap);

#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_roam_main.h */
