/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_btcoex.h

  最近修改   :
  功能描述   : dmac_btcoex.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月02日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_BTCOEX_H__
#define __DMAC_BTCOEX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif





/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "hal_ext_if.h"
#include "hal_hi1102_coex_reg.h"
#include "dmac_alg_if.h"
#include "dmac_rx_data.h"
#include "mac_resource.h"
#include "mac_board.h"
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BTCOEX_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*命名不规范，待整改*/
typedef enum
{
    WIFIAWAKE = 0,
    WIFISLEEP = 1,
    COEX_ALL_STATUS
}COEX_STATUS;


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
typedef struct mac_ieee80211_qoscoex_frame
{
    mac_header_frame_control_stru   st_frame_control;
    oal_uint16                      bit_duration_value      : 15,           /* duration/id */
                                    bit_duration_flag       : 1;
    oal_uint8                       auc_address1[WLAN_MAC_ADDR_LEN];
    oal_uint8                       auc_address2[WLAN_MAC_ADDR_LEN];
    oal_uint8                       auc_address3[WLAN_MAC_ADDR_LEN];
    oal_uint16                      bit_sc_frag_num     : 4,                /* sequence control */
                                    bit_sc_seq_num      : 12;
    oal_uint8                       bit_qc_tid          : 4,
                                    bit_qc_eosp         : 1,
                                    bit_qc_ack_polocy   : 2,
                                    bit_qc_amsdu        : 1;

}dmac_btcoex_qosnull_frame_stru;


typedef struct dmac_btcoex_param
{
    oal_uint32 ul_self_cts_duration;
    oal_uint32 ul_abort_null_duration;
}dmac_btcoex_param_stru;


typedef struct dmac_btcoex
{
    oal_uint8 auc_null_qosnull_frame[BTCOEX_MAC_HDR];
    dmac_btcoex_param_stru st_dmac_btcoex_param;
}dmac_btcoex_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint32 dmac_btcoex_init(oal_void);
extern oal_uint32 dmac_btcoex_exit(oal_void);
extern oal_void dmac_btcoex_init_preempt(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, coex_preempt_frame_enum_uint8 en_preempt_type);
extern oal_void dmac_btcoex_wlan_priority_set(mac_device_stru *pst_mac_device, oal_uint8 uc_value, oal_uint8 uc_timeout_ms);
extern oal_uint32 dmac_btcoex_wlan_priority_timeout_callback(oal_void *p_arg);
extern oal_void dmac_btcoex_change_state_syn(mac_vap_stru *pst_mac_vap);
extern oal_void dmac_btcoex_vap_up_handle(mac_vap_stru *pst_mac_vap);
extern oal_void dmac_btcoex_vap_down_handle(mac_vap_stru *pst_mac_vap);
extern oal_uint32 dmac_config_btcoex_assoc_state_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_void dmac_btcoex_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_bt_on,oal_uint8 uc_ba_size);
extern oal_void dmac_btcoex_bt_low_rate_process (mac_vap_stru *pst_vap, hal_to_dmac_device_stru *pst_hal_device);
extern oal_void dmac_btcoex_release_rx_prot(mac_device_stru *pst_mac_device, oal_uint8 uc_data_type);
#endif /* #ifdef _PRE_WLAN_FEATURE_COEXIST_BT */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_data_acq.h */
