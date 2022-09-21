/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_hcc_adapt
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月8日
  最近修改   :
  功能描述   : dmac_hcc_adapt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月8日
    作    者   : 侯寅
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_HCC_ADAPT_H__
#define __DMAC_HCC_ADAPT_H__

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
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_HCC_ADAPT_H

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

/*Rx适配部分*/
extern frw_event_mem_stru* dmac_process_rx_data_event_adapt_default(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_event_config_syn_alg_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru* dmac_scan_proc_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern  frw_event_mem_stru* dmac_dpd_data_processed_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);
#endif
extern frw_event_mem_stru*   dmac_cali_hmac2dmac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

extern frw_event_mem_stru* dmac_scan_proc_sched_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem);

/*Tx适配部分*/
extern oal_uint32 dmac_proc_wlan_drx_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_tkip_mic_fail_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_crx_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_scan_report_scanned_bss_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32 dmac_dpd_data_cali_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32 dmac_scan_proc_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_chan_result_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_init_event_process_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_proc_event_del_ba_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_event_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_alg_ct_result_tx_adapt(frw_event_mem_stru *pst_event_mem);
//extern oal_uint32 dmac_proc_event_log_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_mgmt_rx_delba_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_send_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_switch_to_new_chan_complete_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_dbac_status_notify_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_proc_disasoc_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_cali2hmac_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 dmac_proc_roam_trigger_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_WOW
oal_uint32 dmac_proc_wow_dev_ready_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
oal_uint32 dmac_proc_wow_dev_sync_host_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_WOW

extern oal_uint32  dmac_alg_syn_info_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_alg_voice_aggr_adapt(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern oal_uint32 dmac_scan_proc_obss_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
extern oal_uint32  dmac_alg_flow_tx_adapt_tx_adapt(frw_event_mem_stru * pst_event_mem);
#endif

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_main */


