/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_chan_mgmt.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年2月22日
  最近修改   :
  功能描述   : dmac_chan_mgmt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月22日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_CHAN_MGMT_H__
#define __DMAC_CHAN_MGMT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_CHAN_MGMT_H
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
extern oal_uint32  dmac_chan_initiate_switch_to_new_channel(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_chan_sync(frw_event_mem_stru *pst_event_mem);
extern oal_void  dmac_chan_attempt_new_chan(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
extern oal_void  dmac_chan_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
extern oal_uint32  dmac_chan_disable_machw_tx_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_chan_enable_machw_tx_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_void  dmac_chan_tx_complete_2040_coexist(mac_device_stru *pst_mac_device, hal_to_dmac_device_stru *pst_hal_device, oal_netbuf_stru *pst_netbuf);
extern oal_uint32  dmac_chan_restart_network_after_switch_event(frw_event_mem_stru *pst_event_mem);
extern oal_void  dmac_chan_tx_complete_suspend_tx(mac_device_stru      *pst_mac_device,
                                             mac_vap_stru              *pst_mac_vap,
                                             hal_to_dmac_device_stru   *pst_hal_device,
                                             oal_netbuf_stru           *pst_netbuf);
extern oal_void  dmac_chan_disable_machw_tx(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_chan_enable_machw_tx(mac_vap_stru *pst_mac_vap);
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
extern oal_uint32 dmac_dfs_radar_detect_event(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32  dmac_dfs_test(frw_event_mem_stru* pst_event_mem);
extern oal_void  dmac_switch_complete_notify(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_check_cac);
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
extern oal_uint32  dmac_dfs_switch_to_offchan_event_process(frw_event_mem_stru* pst_event_mem);
extern oal_uint32  dmac_dfs_switch_back_event_process(frw_event_mem_stru* pst_event_mem);
#endif
extern oal_void  dmac_chan_update_user_bandwidth(mac_vap_stru *pst_mac_vap);






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_chan_mgmt.h */
