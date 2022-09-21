/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_wow.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年05月05日
  最近修改   :
  功能描述   : WOW hmac功能
  函数列表   :
  修改历史   :
  1.日    期   : 2016年05月05日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifndef __HMAC_WOW_H__
#define __HMAC_WOW_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_vap.h"
#include "mac_device.h"
#include "hmac_device.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_WOW_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WOW_MAGIC_MAC_ADDR_LEN      (6)
#define WOW_MAGIC_TARGET_MAC_NUM    (16)
#define WOW_MAGIC_PAYLOAD_LEN       ((WOW_MAGIC_MAC_ADDR_LEN) + (WOW_MAGIC_MAC_ADDR_LEN)*(WOW_MAGIC_TARGET_MAC_NUM))
#define WOW_SAVE_EVENT_MAX_NUM      (8)
#define WOW_SAVE_NETBUF_MAX_NUM     (8)

#define WOW_SLEEP_REQ_WAIT_TIMEOUT  (3000)
/* 寄存器时间转换ms */
#define CALC_TIME_TEST_FUNC(time) ((0xffffffff - (time))*256/50000) 
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    HMAC_HOST_STATE_INVALID,
    HMAC_HOST_STATE_WAKEUP,
    HMAC_HOST_STATE_SLEEP_REQ,
    HMAC_HOST_STATE_DEV_READY_FOR_HOST_SLEEP,
    HMAC_HOST_STATE_HOST_READY,
    HMAC_HOST_STATE_SLEPT,
    HMAC_HOST_STATE_BUTT
}hmac_host_sleep_state_enum;
typedef oal_uint8 hmac_host_sleep_state_enum_uint8;

typedef enum
{
    MAC_WOW_PATTERN_PARAM_OPTION_NONE,
    MAC_WOW_PATTERN_PARAM_OPTION_CLR,
    MAC_WOW_PATTERN_PARAM_OPTION_ADD,
    MAC_WOW_PATTERN_PARAM_OPTION_DEL,
    MAC_WOW_PATTERN_PARAM_OPTION_BUTT
}mac_wow_pattern_param_option_enum;

typedef enum
{
    EVENT_TX_TYPE,
    EVENT_RX_TYPE,
    EVENT_DUAL_TYPE,
    EVENT_TYPE_BUTT
}mac_event_type_enum;
typedef oal_uint8 mac_event_type_enum_uint8;

typedef enum
{
    HMAC_WOW_MODULE_STATE_NOT_INIT  = 0,
    HMAC_WOW_MODULE_STATE_INIT      = 1,
    HMAC_WOW_MODULE_BUTT
}hmac_wow_init_state_enum;
typedef oal_uint8 hmac_wow_init_state_enum_uint8;

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
    oal_uint16      us_pattern_option;
    oal_uint16      us_pattern_index;
    oal_uint32      ul_pattern_len;
    oal_uint8       auc_pattern_value[WOW_NETPATTERN_MAX_LEN];
}hmac_cfg_wow_pattern_param_stru;

typedef struct
{
    oal_uint8   uc_tx_cnt;
    oal_uint8   uc_rx_cnt;
    oal_uint8   uc_dual_cnt;
    oal_uint8   uc_res;
}hmac_debug_param_stru;

typedef struct
{
    hmac_host_sleep_state_enum_uint8    uc_host_sleep_state;
    oal_uint8                           uc_is_wow_init;
    oal_uint8                           auc_res[2];
    hmac_debug_param_stru               st_event_info;
    mac_wow_cfg_stu                     st_wow_cfg;
    oal_completion                      st_sleep_req_done_event;
}hmac_wow_info_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern oal_void hmac_wow_set_host_state(oal_uint8 uc_sleep_state);

extern oal_uint8 hmac_wow_get_host_state(oal_void);

extern oal_void hmac_wow_init(oal_void);

extern oal_void* hmac_wow_get_cfg_vap(oal_void);

extern oal_uint32  hmac_wow_tx_check_filter_switch(
                        oal_void
                        );

extern oal_void hmac_wow_stop_scan_assoc(oal_void);

extern oal_void hmac_wow_stop_upper_layer_queue(oal_void);

extern oal_void hmac_wow_clear_data_channal(oal_void);

extern oal_void hmac_wow_clear_event_queue(oal_void);

extern oal_void hmac_wow_prepare_wakeup(oal_void);

extern oal_void hmac_wow_host_sleep_cmd(oal_uint32 ul_is_host_sleep);

extern oal_void hmac_wow_set_wow_cmd(oal_uint32 ul_wow_event);

extern oal_void hmac_wow_set_wow_en_cmd(oal_uint32 ul_wow_en);

extern oal_uint32 hmac_wow_add_pattern(oal_uint16 us_pattern_index, oal_uint32 ul_pattern_len, oal_uint8 *puc_pattern);

extern oal_uint32 hmac_wow_set_pattern_cmd(hmac_cfg_wow_pattern_param_stru * pst_pattern);

extern oal_uint32 hmac_wow_host_sleep_request(oal_void);

extern oal_uint32 hmac_wow_host_wakeup_notify(oal_void);

extern oal_void hmac_wow_create_lock(oal_void);

extern oal_void hmac_wow_obtain_lock(oal_void);

extern oal_void hmac_wow_release_lock(oal_void);

extern oal_void hmac_wow_trigger_host_state(oal_void);

extern oal_uint32  hmac_wow_proc_dev_ready_slp_event(frw_event_mem_stru *pst_event_mem);

extern oal_uint32  hmac_wow_proc_dev_sync_host_event(frw_event_mem_stru *pst_event_mem);

extern oal_uint32  hmac_wow_set_dmac_cfg(oal_void);

extern oal_uint32  hmac_wow_host_sleep_wakeup_notify(oal_uint8 uc_is_sleep_req);

extern oal_void wlan_suspend(oal_void);

extern oal_void wlan_resume(oal_void);

extern oal_void wlan_wifi_suspend(oal_void);

extern oal_void wlan_wifi_resume(oal_void);

extern oal_uint32  hmac_wow_proc_dev_ready_slp(oal_void);

extern oal_int32 hmac_wow_msg_handle(void *data);

extern oal_uint32  hmac_wow_check_event(
                frw_event_hdr_stru *pst_event_hrd,
                oal_uint8           uc_event_dir
                );

oal_void hmac_wow_enable_pm(oal_uint8 uc_pm_enable);

extern oal_uint32 hmac_wow_get_time(oal_void);

#endif //#ifdef _PRE_WLAN_FEATURE_WOW

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#endif