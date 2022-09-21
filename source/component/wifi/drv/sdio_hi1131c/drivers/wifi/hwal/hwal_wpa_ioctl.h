/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_ioctl.h
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

#ifndef __HWAL_IOCTL_H__
#define __HWAL_IOCTL_H__

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
#include "wal_main.h"
#include "mac_user.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HWAL_IOCTL_H
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
typedef oal_int32 (*hwal_ioctl_handler)(oal_int8 *puc_ifname, oal_void *p_buf);

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
oal_int32   hwal_ioctl_set_key(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_new_key(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_del_key(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_set_ap(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_change_beacon(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_send_mlme(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_send_eapol(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_set_mode(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_set_power(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_receive_eapol(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_enable_eapol(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_disable_eapol(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_get_addr(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_get_hw_feature(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_stop_ap(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_del_virtual_intf(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_set_ap_wps_p2p_ie(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_wpa_ioctl(oal_int8 *puc_ifname, hisi_ioctl_command_stru *pst_cmd);
oal_int32   hwal_ioctl_scan(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_disconnect(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_assoc(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_set_netdev(oal_int8 *puc_ifname, oal_void *p_buf);
oal_uint8   hwal_is_valid_ie_attr(oal_uint8 *puc_ie, oal_uint32 ul_ie_len);
oal_int32   hwal_ioctl_dhcp_start(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_dhcp_stop(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32   hwal_ioctl_dhcp_succ_check(oal_int8 *puc_ifname, oal_void *p_buf);

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
oal_int32           hwal_ioctl_set_rekey_info(oal_int8 *puc_ifname, oal_void *p_buf);
extern oal_int32    wal_cfg80211_set_rekey_info(oal_net_device_stru *pst_net_dev, mac_rekey_offload_stru *pst_rekey_offload);
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hwal_ioctl.h */

