/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_mgmt_bss_comm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年4月9日
  最近修改   :
  功能描述   : dmac_mgmt_bss_comm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_MGMT_BSS_COMM_H__
#define __DMAC_MGMT_BSS_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_BSS_COMM_H
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
extern oal_uint16  dmac_ba_encap_blockack_req(
                       dmac_vap_stru     *pst_dmac_vap,
                       oal_netbuf_stru   *pst_netbuf,
                       dmac_ba_tx_stru   *pst_ba_tx_hdl,
                       oal_uint8          uc_tid);
extern oal_uint32  dmac_mgmt_delba(
                       dmac_vap_stru          *pst_dmac_vap,
                       dmac_user_stru         *pst_dmac_user,
                       oal_uint8               uc_tid,
                       oal_uint8               uc_initiator,
                       oal_uint8               uc_reason);
extern oal_uint32  dmac_mgmt_rx_addba_rsp(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_crx_action_event);
extern oal_uint32  dmac_mgmt_rx_delba(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_crx_action_event);
extern oal_uint32  dmac_mgmt_tx_addba_req(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_tx_addba_rsp(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_tx_delba(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_rx_ampdu_start(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       mac_priv_req_args_stru         *pst_crx_req_args);
extern oal_uint32  dmac_mgmt_rx_ampdu_end(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       mac_priv_req_args_stru         *pst_crx_req_args);
extern oal_uint32  dmac_mgmt_scan_timeout(dmac_vap_stru *pst_dmac_vap, oal_void *p_param);

extern oal_uint32  dmac_mgmt_switch_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_channel, oal_uint8 en_clear_fifo);

/* Channel Switch 相关封装函数 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#else
extern oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  dmac_mgmt_encap_ext_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_opert_class, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#endif
extern oal_uint32  dmac_mgmt_send_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);

extern oal_uint32  dmac_mgmt_scan_vap_down(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_set_cap_info_field(oal_void *pst_vap, oal_uint8 *puc_buffer);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_mgmt_bss_comm.h */
