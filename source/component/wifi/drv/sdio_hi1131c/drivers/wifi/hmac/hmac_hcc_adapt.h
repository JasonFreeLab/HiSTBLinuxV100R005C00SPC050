/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_hcc_adapt
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月8日
  最近修改   :
  功能描述   : hmac_hcc_adapt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 侯寅
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_HCC_ADAPT_H__
#define __HMAC_HCC_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "hmac_ext_if.h"
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_HCC_ADAPT_H

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

/*Hcc 事件处理*/
extern oal_uint32 hmac_hcc_rx_event_comm_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_hcc_test_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);


/*Rx适配部分*/
extern frw_event_mem_stru * hmac_rx_process_data_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru *  hmac_rx_process_mgmt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru *pst_hcc_event_mem);
/*Tx适配部分*/

extern oal_uint32 hmac_proc_add_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_del_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_host_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_test_hcc_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_mgmt_ctx_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_set_edca_param_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_process_action_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32   hmac_dpd_data_processed_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32   hmac_send_cali_data_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_sched_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_update_user_qos_table_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_join_set_dtim_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint32(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint8(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru * hmac_rx_convert_netbuf_to_netbuf_default(frw_event_mem_stru * pst_hcc_event_mem);
extern oal_uint32 hmac_proc_join_set_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_user_add_notify_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_proc_rx_process_sync_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_select_channel_mac_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_initiate_switch_to_new_channel_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern frw_event_mem_stru * hmac_cali2hmac_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

#ifdef _PRE_WLAN_FEATRUE_FLOWCTL
extern frw_event_mem_stru* hmac_alg_flowctl_backp_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32 hmac_edca_opt_stat_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_main */

