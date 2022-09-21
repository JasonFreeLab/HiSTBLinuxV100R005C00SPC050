/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_wow.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2016年4月5日
  最近修改   :
  功能描述   : dmac_wow.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月5日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_WOW_H__
#define __DMAC_WOW_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_WOW

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "mac_vap.h"
#include "dmac_vap.h"
#include "dmac_user.h"
#include "dmac_ext_if.h"
#include "dmac_ap_pm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_WOW_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WOW_MAGIC_MAC_ADDR_LEN      (6)
#define WOW_MAGIC_TARGET_MAC_NUM    (16)
#define WOW_MAGIC_PAYLOAD_LEN       ((WOW_MAGIC_MAC_ADDR_LEN) + (WOW_MAGIC_MAC_ADDR_LEN)*(WOW_MAGIC_TARGET_MAC_NUM))
#define WOW_SAVE_EVENT_MAX_NUM      (8)
#define WOW_SAVE_NETBUF_MAX_NUM     (8)
#define WOW_DEV_SYNC_HOST_DATA_MAX_LEN  (WLAN_LARGE_NETBUF_SIZE)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    WOW_SAVE_TYPE_INIT,     /* 初始类型 */
    WOW_SAVE_TYPE_EVENT,    /* 保存事件 */
    WOW_SAVE_TYPE_NETBUF,   /* 保存netbuf */
    WOW_SAVE_TYPE_BUT
}dmac_wow_save_type_enum;
typedef oal_uint8 dmac_wow_save_type_enum_uint8;

typedef enum
{
    WOW_SAVE_EVENT_INIT,     /* 初始类型 */
    WOW_SAVE_EVENT_DISASSOC,
    WOW_SAVE_EVENT_TYPE_BUT
}dmac_wow_save_event_type_enum;
typedef oal_uint8 dmac_wow_save_event_type_enum_uint8;

typedef enum
{
    DMAC_HOST_STATE_INVALID,
    DMAC_HOST_STATE_DEV_WAKE_HOST_WAITING,
    DMAC_HOST_STATE_WAKEUP,
    DMAC_HOST_STATE_SLEEP_REQ_RECEIVED,
    DMAC_HOST_STATE_DEV_READY_FOR_HOST_SLEEP,
    DMAC_HOST_STATE_SLEPT, //callback
    DMAC_HOST_STATE_BUTT
}dmac_host_sleep_state_enum;
typedef oal_uint8 dmac_host_sleep_state_enum_uint8;

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
    oal_uint32                       ul_event_type;
    mac_vap_stru                    *pst_vap;
    frw_event_mem_stru              *pst_event_mem;
}wow_save_event_sub_stru;

typedef struct
{
    oal_netbuf_stru                 *pst_netbuf;
    mac_vap_stru                    *pst_vap;
    oal_uint8                        uc_mgmt_type;
    oal_uint8                        uc_has_disassoc;
    oal_uint8                        auc_resv[2];
}wow_save_rx_mgmt_sub_stru;

/* WOW 备份参数 */
typedef struct
{
    wow_save_rx_mgmt_sub_stru   st_rx_mgmt[WOW_SAVE_NETBUF_MAX_NUM];
    oal_uint16                  us_save_map;
    oal_uint16                  us_save_num;
}wow_save_rx_mgmt_stru;

typedef struct
{
    wow_save_event_sub_stru     st_event[WOW_SAVE_EVENT_MAX_NUM];
    oal_uint16                  us_save_map;
    oal_uint16                  us_save_num;
}wow_save_event_stru;

typedef struct
{
    oal_uint8               uc_wow_sleep_state;
    oal_uint8               auc_res[3];
    oal_uint32              ul_wakeup_reason;
    mac_wow_cfg_stu         st_wow_cfg;
    wow_save_event_stru     st_save_event;
    wow_save_rx_mgmt_stru   st_save_rx_mgmt;
}dmac_wow_info_stu;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern dmac_wow_info_stu   g_st_wow_info;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
//#ifdef WIFI_ALL_ROM
extern oal_void dmac_wow_dev_wake_up_host_ram(oal_uint32 ul_wakeup_reason);

extern oal_void dmac_wow_set_host_state(oal_uint8 uc_sleep_state);

extern oal_uint8 dmac_wow_get_host_state(oal_void);

extern oal_void dmac_wow_init_ram(oal_void);

extern oal_uint32 dmac_wow_sleep_wakeup_notify_ram(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_uint32 dmac_wow_set_param_ram(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_uint32 dmac_wow_allow_host_slp_condition(oal_void);

extern oal_void  dmac_wow_main_process_ram(oal_void);
                
extern oal_uint32  dmac_wow_rx_check_filter_switch_ram(oal_void);

extern oal_void dmac_wow_host_sleep_callback_ram(oal_void);

extern oal_uint32 dmac_wow_ready_for_host_sleep(oal_void);

extern oal_uint32 dmac_wow_dev_sync_host(oal_void);

extern oal_uint32 dmac_wow_alloc_mgmt_event(
                        mac_vap_stru          *pst_vap,
                        oal_netbuf_stru       *pst_netbuf,
                        frw_event_mem_stru   **ppst_event_mem
                        );

extern oal_void dmac_wow_dispatch_saved_disassoc(
                    oal_void
                    );
extern oal_void dmac_wow_dispatch_saved_auth(
                    oal_void
                    );

extern oal_void dmac_wow_dispatch_saved_event(
                    oal_void
                    );

extern oal_void dmac_wow_check_clear_saved_data(
                    oal_void
                    );
            
extern oal_void dmac_wow_dispatch_saved_data(
                    oal_void
                    );

extern oal_uint32 dmac_wow_rx_process_magic_packet(
                        mac_vap_stru          *pst_vap,
                        oal_netbuf_stru       *pst_netbuf
                        );

extern oal_uint32 dmac_wow_rx_process_netpattern_tcp(
                    mac_vap_stru          *pst_vap,
                    oal_netbuf_stru       *pst_netbuf
                    );

extern oal_uint32 dmac_wow_rx_process_netpattern_udp(
                        mac_vap_stru          *pst_vap,
                        oal_netbuf_stru       *pst_netbuf
                        );

extern oal_uint32 dmac_wow_rx_process_tcp_udp_keep_alive(
                        mac_vap_stru          *pst_vap,
                        oal_netbuf_stru       *pst_netbuf
                        );

extern oal_uint32 dmac_wow_rx_process_data_ram(
                        oal_netbuf_head_stru     *pst_netbuf_header_in,
                        oal_netbuf_head_stru     *pst_netbuf_header_out,
                        mac_vap_stru             *pst_vap,
                        oal_netbuf_stru          *pst_netbuf
                        );

extern oal_uint32 dmac_wow_rx_process_data_list(
                        oal_netbuf_head_stru     *pst_netbuf_header_in,
                        oal_netbuf_head_stru     *pst_netbuf_header_out,
                        mac_vap_stru             *pst_vap,
                        oal_netbuf_stru          *pst_netbuf
                        );

extern oal_uint32 dmac_wow_rx_process_control_ram(
                        dmac_vap_stru       *pst_dmac_vap,
                        oal_netbuf_stru     *pst_netbuf,
                        oal_uint8           *pen_go_on
                        );

extern oal_uint32  dmac_wow_rx_save_disassoc(
                        mac_vap_stru       *pst_vap,
                        oal_netbuf_stru    *pst_netbuf
                        );

extern oal_uint32  dmac_wow_rx_save_auth(
                        mac_vap_stru       *pst_vap,
                        oal_netbuf_stru    *pst_netbuf
                        );

extern oal_uint32  dmac_wow_rx_check_mgmt_frame_exist(
                        mac_vap_stru       *pst_vap,
                        oal_uint8          *puc_ta_addr,
                        oal_uint8           uc_mgmt_type
                        );

extern oal_uint32  dmac_wow_check_event_exist(
                        mac_vap_stru        *pst_vap, 
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );

extern oal_uint32  dmac_wow_process_and_save_event_ram(
                        mac_vap_stru        *pst_vap, 
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );

extern oal_uint32 dmac_wow_disassoc_end_notify_ram(
                        mac_vap_stru        *pst_vap,
                        oal_uint8           *puc_mac_addr
                        );
                        
extern oal_uint32  dmac_wow_save_event(
                        mac_vap_stru        *pst_vap, 
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );

extern oal_uint32  dmac_wow_rx_process_mgmt_ram(
                        dmac_vap_stru      *pst_dmac_vap,
                        oal_netbuf_stru    *pst_netbuf,
                        frw_event_mem_stru *pst_event_mem,
                        oal_uint8          *pen_go_on
                        );

//#endif

extern oal_void dmac_wow_dev_wake_up_host(oal_uint32 ul_wakeup_reason);

extern oal_void dmac_wow_init(oal_void);

extern oal_uint32 dmac_wow_sleep_wakeup_notify(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_uint32 dmac_wow_set_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_void  dmac_wow_main_process(oal_void);
                
extern oal_uint32  dmac_wow_rx_check_filter_switch(oal_void);

extern oal_void dmac_wow_host_sleep_callback(oal_void);

extern oal_uint32  dmac_wow_process_and_save_event(
                        mac_vap_stru        *pst_vap, 
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );

extern oal_uint32 dmac_wow_disassoc_end_notify(
                        mac_vap_stru        *pst_vap,
                        oal_uint8           *puc_mac_addr
                        );

extern oal_uint32 dmac_wow_rx_process_data(
                        oal_netbuf_head_stru    *pst_netbuf_header_in,
                        oal_netbuf_head_stru  *pst_netbuf_header_out,
                        mac_vap_stru          *pst_vap,
                        oal_netbuf_stru       *pst_netbuf
                        );
                                        
extern oal_uint32 dmac_wow_process_control(
                        dmac_vap_stru       *pst_dmac_vap,
                        oal_netbuf_stru     *pst_netbuf,
                        oal_uint8           *pen_go_on
                        );
                                                            
extern oal_uint32  dmac_wow_rx_process_mgmt(
                        dmac_vap_stru      *pst_dmac_vap,
                        oal_netbuf_stru    *pst_netbuf,
                        frw_event_mem_stru *pst_event_mem,
                        oal_uint8          *pen_go_on
                        );

extern oal_void dmac_wow_enable_pm(oal_uint8 uc_pm_enable);

extern oal_void dmac_wow_msg_handle(oal_uint8 uc_sleep_wakeup_notify);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_wow.h */

