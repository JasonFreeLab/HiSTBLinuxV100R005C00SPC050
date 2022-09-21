/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_mgmt_bss_comm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年4月9日
  最近修改   :
  功能描述   : hmac_mgmt_bss_comm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_MGMT_BSS_COMM_H__
#define __HMAC_MGMT_BSS_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_BSS_COMM_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* HMAC_NCW_INHIBIT_THRED_TIME时间内连续HMAC_RECEIVE_NCW_MAX_CNT次接收到ncw,不上报 */
#define HMAC_NCW_INHIBIT_THRED_TIME   60000    /* 单位ms */
#define HMAC_RECEIVE_NCW_THRED_CNT    6


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint8 g_auc_avail_protocol_mode[WLAN_PROTOCOL_BUTT][WLAN_PROTOCOL_BUTT];
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint16 g_as_aggr_rx_encap;
extern oal_uint16 g_as_aggr_tx_encap;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  g_ul_print_wakeup_mgmt;
#endif

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint16  hmac_mgmt_encap_addba_req(
                       hmac_vap_stru          *pst_vap,
                       oal_uint8              *puc_data,
                       dmac_ba_tx_stru        *pst_tx_ba,
                       oal_uint8               uc_tid);
extern oal_uint16  hmac_mgmt_encap_addba_rsp(
                       hmac_vap_stru      *pst_vap,
                       oal_uint8          *puc_data,
                       hmac_ba_rx_stru    *pst_addba_rsp,
                       oal_uint8           uc_tid,
                       oal_uint8           uc_status);
extern oal_uint16  hmac_mgmt_encap_delba(
                       hmac_vap_stru                      *pst_vap,
                       oal_uint8                          *puc_data,
                       oal_uint8                          *puc_addr,
                       oal_uint8                           uc_tid,
                       mac_delba_initiator_enum_uint8      en_initiator,
                       oal_uint8                           reason);
extern oal_uint32  hmac_mgmt_rx_addba_req(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       oal_uint8                  *puc_payload);
extern oal_uint32  hmac_mgmt_rx_addba_rsp(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       oal_uint8                  *puc_payload);
extern oal_uint32  hmac_mgmt_rx_delba(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       oal_uint8                  *puc_payload);
extern oal_uint32  hmac_mgmt_tx_addba_req(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       mac_action_mgmt_args_stru  *pst_action_args);
extern oal_uint32  hmac_mgmt_tx_addba_rsp(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       hmac_ba_rx_stru            *pst_ba_rx_info,
                       oal_uint8                   uc_tid,
                       oal_uint8                   uc_status);
extern oal_uint32  hmac_mgmt_tx_delba(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       mac_action_mgmt_args_stru  *pst_action_args);
extern oal_uint32  hmac_mgmt_tx_addba_timeout(oal_void *p_arg);
extern oal_uint32  hmac_mgmt_tx_ampdu_start(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       mac_priv_req_args_stru     *pst_priv_req);
extern oal_uint32  hmac_mgmt_tx_ampdu_end(
                       hmac_vap_stru              *pst_hmac_vap,
                       hmac_user_stru             *pst_hmac_user,
                       mac_priv_req_args_stru     *pst_priv_req);


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
extern oal_uint32  hmac_sa_query_interval_timeout(oal_void *p_arg);
extern oal_void    hmac_send_sa_query_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 *pst_hdr, oal_bool_enum_uint8 en_is_protected);
extern oal_uint32  hmac_start_sa_query(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user, oal_bool_enum_uint8 en_is_protected);
extern oal_uint32  hmac_pmf_check_err_code(mac_user_stru *pst_user_base_info, oal_bool_enum_uint8 en_is_protected, oal_uint8 *puc_mac_hdr);

#endif
extern oal_uint32 hmac_tx_mgmt_send_event(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_mgmt_frame, oal_uint16 us_frame_len);
extern oal_uint32  hmac_ie_proc_vht_opern_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_user_stru *pst_mac_user);
extern oal_void hmac_mgmt_update_assoc_user_qos_table(
                oal_uint8                      *puc_payload,
                oal_uint16                      ul_msg_len,
                oal_uint16                      us_info_elem_offset,
                hmac_user_stru                 *pst_hmac_user);
extern  oal_uint32  hmac_check_bss_cap_info(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap);

#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hmac_mgmt_update_11ntxbf_cap(
                oal_uint8                      *puc_payload,
                hmac_user_stru                 *pst_hmac_user);
#endif

#ifdef _PRE_WLAN_FEATURE_HISTREAM
extern oal_void hmac_mgmt_update_histream_info(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user, oal_uint8 *puc_payload);
#endif //_PRE_WLAN_FEATURE_HISTREAM

extern  oal_void hmac_set_user_protocol_mode(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern oal_uint32  hmac_mgmt_reset_psm(mac_vap_stru *pst_vap, oal_uint16 us_user_id);
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32  hmac_ie_proc_opmode_field(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user,
                                                mac_opmode_notify_stru *pst_opmode_notify, oal_uint8 uc_mgmt_frm_type);
#endif
extern oal_uint32 hmac_keepalive_set_interval(mac_vap_stru *pst_mac_vap, oal_uint16 us_keepalive_interval);
extern oal_uint32 hmac_keepalive_set_limit(mac_vap_stru *pst_mac_vap, oal_uint32 us_keepalive_limit);

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
extern oal_void  hmac_rx_sa_query_req(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected);
extern oal_void  hmac_rx_sa_query_rsp(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected);
#endif
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32  hmac_mgmt_rx_opmode_notify_frame(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern oal_void  hmac_rx_notify_channel_width(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void  hmac_vap_add_proxysta_vap(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_msg);
#endif/*lint -e19*/

extern oal_void    hmac_send_mgmt_to_host(hmac_vap_stru  *pst_hmac_vap,
                                                oal_netbuf_stru *puc_buf,
                                                oal_uint16       us_len,
                                                oal_int          l_freq);

#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_P2P)
extern oal_void hmac_rx_mgmt_send_to_host(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);
#endif

extern oal_uint32  hmac_mgmt_tx_event_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_void hmac_user_init_rates(hmac_user_stru *pst_hmac_user, mac_vap_stru *pst_mac_vap);
extern oal_uint8 hmac_add_user_rates(hmac_user_stru *pst_hmac_user, oal_uint8 uc_rates_cnt, oal_uint8 *puc_rates);
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
extern oal_void  hmac_rx_ba_session_decr(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_tidno);
extern oal_void  hmac_tx_ba_session_decr(hmac_vap_stru *pst_hmac_vap, oal_uint8 uc_tidno);
#else
extern oal_void  hmac_rx_ba_session_decr(mac_device_stru *pst_mac_device, oal_uint8 uc_tidno);
extern oal_void  hmac_tx_ba_session_decr(mac_device_stru *pst_mac_device, oal_uint8 uc_tidno);
#endif
extern oal_void  hmac_vap_set_user_avail_rates(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern oal_uint32 hmac_proc_ht_cap_ie(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_ht_cap_ie);
extern oal_uint32 hmac_proc_vht_cap_ie(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user, oal_uint8 *puc_vht_cap_ie);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_mgmt_bss_comm.h */
