/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_psm_ap.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月21日
  最近修改   :
  功能描述   : dmac_psm_ap.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月21日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_PSM_AP_H__
#define __DMAC_PSM_AP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "dmac_vap.h"
#include "dmac_user.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define MAX_MPDU_NUM_IN_PS_QUEUE    64

#define DMAC_PSM_CHANGE_USER_PS_STATE(_bit_ps, _en_val)  ((_bit_ps) = (_en_val))

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
extern oal_uint32  dmac_psm_resv_ps_poll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_void dmac_psm_set_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_bitmap_flg);
#if 0
extern oal_uint8 dmac_psm_get_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_uint8 dmac_psm_get_bitmap_offset(dmac_vap_stru *pst_dmac_vap);
extern oal_uint8 dmac_psm_get_bitmap_len(dmac_vap_stru *pst_dmac_vap);
#endif
extern oal_uint32 dmac_psm_send_null_data(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_bool_enum_uint8 en_ps);
extern oal_uint32 dmac_psm_user_ps_structure_init(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_psm_user_ps_structure_destroy(dmac_user_stru *pst_dmac_user);
extern oal_void dmac_psm_clear_ps_queue(dmac_user_stru *pst_dmac_user);
extern oal_void dmac_psm_queue_flush(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_uint32 dmac_psm_enqueue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_uint8 dmac_psm_pkt_need_buff(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_void dmac_psm_rx_process(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_uint32  dmac_psm_reset(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_psm_tx_set_more_data(dmac_user_stru *pst_dmac_user,
                                               mac_tx_ctl_stru *pst_tx_cb);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32  dmac_psm_enable_user_to_psm_back(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device, dmac_user_stru *pst_dmac_user);
oal_uint32  dmac_psm_disable_user_to_psm_back(mac_device_stru *pst_mac_device,dmac_user_stru *pst_dmac_user);
//oal_uint32  dmac_psm_flush_txq_to_psm(dmac_vap_stru  *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
#endif

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32 dmac_psm_opmode_notify_process(frw_event_mem_stru *pst_event_mem);
#endif

extern oal_void  dmac_change_null_data_rate(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 *uc_protocol_mode,oal_uint8 *uc_legacy_rate);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_psm_ap.h */
