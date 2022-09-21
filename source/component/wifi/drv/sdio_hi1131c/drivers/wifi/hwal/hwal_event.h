/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_event.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月16日
  最近修改   :
  功能描述   : hwal_ioctl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HWAL_EVENT_H__
#define __HWAL_EVENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "driver_hisi_common.h"
#include "oam_ext_if.h"
#include "oal_net.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HWAL_EVENT_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
oal_void            cfg80211_new_sta(oal_net_device_stru *pst_dev, const oal_uint8 *puc_macaddr, oal_station_info_stru *pst_sinfo, oal_gfp_enum_uint8 en_gfp);
oal_void            cfg80211_del_sta(oal_net_device_stru *pst_dev, const oal_uint8 *puc_mac_addr, oal_gfp_enum_uint8 en_gfp);
oal_bool_enum_uint8 cfg80211_rx_mgmt(oal_wireless_dev_stru *pst_wdev, oal_int32 l_freq, oal_int32 l_sig_mbm, const oal_uint8 *puc_buf, size_t ul_len, oal_gfp_enum_uint8 en_gfp);
oal_bool_enum_uint8 cfg80211_mgmt_tx_status(struct wireless_dev *pst_wdev, oal_uint64 ull_cookie, const oal_uint8 *puc_buf, size_t ul_len, oal_bool_enum_uint8 en_ack, oal_gfp_enum_uint8 en_gfp);
oal_cfg80211_bss_stru *cfg80211_inform_bss_frame(oal_wiphy_stru *pst_wiphy,oal_ieee80211_channel_stru *pst_ieee80211_channel,oal_ieee80211_mgmt_stru     *pst_mgmt,
                                                  oal_uint32 ul_len,oal_int32 l_signal,oal_gfp_enum_uint8 en_ftp);
oal_void            cfg80211_connect_result(oal_net_device_stru*pst_dev, const oal_uint8 *puc_bssid,const oal_uint8 *puc_req_ie, oal_size_t ul_req_ie_len,const oal_uint8 *puc_resp_ie, oal_size_t ul_resp_ie_len,
			     							oal_uint16 us_status, oal_gfp_enum_uint8 en_gfp);
oal_uint32          cfg80211_disconnected(oal_net_device_stru *pst_net_device,oal_uint16 us_reason,oal_uint8 *puc_ie,oal_uint32 ul_ie_len,oal_gfp_enum_uint8 en_gfp);
oal_void            cfg80211_scan_done(oal_cfg80211_scan_request_stru *pst_request, oal_uint8 uc_aborted);

#ifdef _PRE_WLAN_FEATURE_HILINK
oal_uint32 hwal_send_others_bss_data(oal_netbuf_stru *pst_netbuf);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

