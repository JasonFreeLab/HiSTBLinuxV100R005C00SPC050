/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_main.c
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : HMAC模块初始化与卸载
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#include "oal_profiling.h"
#endif

#include "oam_ext_if.h"
#include "oam_trace.h"
#include "frw_ext_if.h"


#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "mac_board.h"

#include "dmac_ext_if.h"

#include "hmac_fsm.h"
#include "hmac_main.h"
#include "hmac_vap.h"
#include "hmac_tx_amsdu.h"
#include "hmac_rx_data.h"
#include "hmac_11i.h"
#include "hmac_mgmt_classifier.h"

#include "hmac_chan_mgmt.h"
#include "hmac_dfs.h"
#ifdef _PRE_WLAN_CHIP_TEST
#include "hmac_test_main.h"
#endif

#include "hmac_data_acq.h"
#include "hmac_rx_filter.h"

#include "hmac_hcc_adapt.h"

#include "hmac_dfs.h"
#include "hmac_config.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_hcc_adapt.h"
#include "hmac_dfx.h"
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#include "hmac_cali_mgmt.h"
#endif
#ifdef _PRE_SUPPORT_ACS
#include "dmac_acs.h"
#include "hmac_acs.h"
#endif
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
#include "oal_kernel_file.h"
#endif

#include "oal_hcc_host_if.h"
#include "oal_net.h"
#include "hmac_tcp_opt.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_resource.h"
#include "hmac_mgmt_classifier.h"
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "hmac_ext_if.h"
#include "hmac_auto_adjust_freq.h"
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
#include "plat_pm_wlan.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
#include "hmac_wow.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MAIN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/* hmac模块板子的全局控制变量 */
mac_board_stru g_st_hmac_board;

extern oal_uint8   g_auc_hmac_macaddr[WLAN_MAC_ADDR_LEN];
oal_wakelock_stru g_st_hmac_wakelock;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
hmac_rxdata_thread_stru     g_st_rxdata_thread;
#endif


OAL_STATIC oal_uint32  hmac_create_ba_event(frw_event_mem_stru  *pst_event_mem);
OAL_STATIC oal_uint32  hmac_del_ba_event(frw_event_mem_stru  *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32  hmac_syn_info_event(frw_event_mem_stru  *pst_event_mem);
OAL_STATIC oal_uint32  hmac_voice_aggr_event(frw_event_mem_stru  *pst_event_mem);
#endif

oal_uint32  hmac_init_scan_do(hmac_device_stru *pst_mac_dev, mac_vap_stru *pst_vap, mac_init_scan_req_stru *pst_cmd);

#ifdef _PRE_SUPPORT_ACS
oal_uint32  hmac_event_acs_response(frw_event_mem_stru  *pst_event_mem);
oal_uint32  hmac_config_set_acs_cmd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_acs_got_init_rank(hmac_device_stru *pst_hmac_dev, mac_vap_stru *pst_mac_vap, mac_acs_cmd_stru *pst_cmd);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
OAL_STATIC oal_uint32  hmac_flowctl_backp_event(frw_event_mem_stru  *pst_event_mem);
#endif

#if( (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)) && defined(_PRE_WLAN_CHIP_TEST_ALG)
extern  oal_uint32  hmac_alg_test_result_process(frw_event_mem_stru  *pst_event_mem);
extern  oal_int32   hmac_alg_test_main_common_init(oal_void);
extern  oal_int32   hmac_alg_test_main_common_exit(oal_void);
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_int32 hmac_hcc_adapt_init(oal_void);
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_board_get_instance
 功能描述  : 获取HMAC board对象
 输入参数  : 无
 输出参数  : HMAC board对象引用
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_board_get_instance(mac_board_stru **ppst_hmac_board)
{
    *ppst_hmac_board = &g_st_hmac_board;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hmac_init_event_process
 功能描述  : dmac 抛给hmac的初始化回复事件
 输入参数  : pst_event_mem: 事件结构体
 输出参数  :

 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
 oal_uint32 hmac_init_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    mac_data_rate_stru    *pst_data_rate;
    oal_uint8             *pst_data_mac_addr;
    dmac_tx_event_stru    *pst_ctx_event;
    mac_device_stru       *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_init_event_process::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_data_rate = (mac_data_rate_stru *)(oal_netbuf_data(pst_ctx_event->pst_netbuf));

    pst_data_mac_addr = (oal_uint8*)(oal_netbuf_data(pst_ctx_event->pst_netbuf)) + sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM;
    OAL_IO_PRINT("get rates from device\n");
    /* 同步mac支持的速率集信息 */
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_init_event_process::pst_mac_device null.}");
        oal_netbuf_free(pst_ctx_event->pst_netbuf);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    oal_memcopy((oal_uint8 *)(pst_mac_device->st_mac_rates_11g),
        (oal_uint8 *)pst_data_rate,
        sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM);
    oal_memcopy((oal_uint8 *)g_auc_hmac_macaddr,(oal_uint8 *)pst_data_mac_addr,WLAN_MAC_ADDR_LEN);

    /* 释放掉02同步消息所用的netbuf信息 */
    oal_netbuf_free(pst_ctx_event->pst_netbuf);

    return OAL_SUCC;
}
#else
/*****************************************************************************
 函 数 名  : hmac_init_event_process
 功能描述  : dmac 抛给hmac的初始化回复事件
 输入参数  : pst_event_mem: 事件结构体
 输出参数  :

 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
 oal_uint32 hmac_init_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    mac_chip_stru         *pst_chip;
    oal_uint32             ul_return;
    oal_uint32             ul_chip_max_num;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_init_event_process::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_chip = (mac_chip_stru *)(pst_event->auc_event_data);


    /* chip支持的最大数由PCIe总线处理提供; */
    ul_chip_max_num = oal_bus_get_chip_num();

    if (OAL_UNLIKELY(ul_chip_max_num > WLAN_CHIP_MAX_NUM_PER_BOARD))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_init_event_process::invalid ul_chip_max_num[%d].}", ul_chip_max_num);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    ul_return = hmac_board_init(ul_chip_max_num, pst_chip);
    if (OAL_SUCC != ul_return)
    {
         return OAL_FAIL;
    }

    return OAL_SUCC;
}


#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hmac_event_fsm_tx_adapt_subtable_register
 功能描述  : hmac模块事件发送适配子表的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_event_fsm_tx_adapt_subtable_register(oal_void)
{
    /* 注册WLAN_CTX事件处理函数表 */
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION].p_tx_adapt_func    = hmac_proc_tx_process_action_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER].p_tx_adapt_func  = hmac_proc_add_user_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER].p_tx_adapt_func  = hmac_proc_del_user_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT].p_tx_adapt_func      = hmac_proc_mgmt_ctx_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG].p_tx_adapt_func = hmac_proc_set_edca_param_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ].p_tx_adapt_func = hmac_scan_proc_scan_req_event_tx_adapt;
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
        g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DPD_DATA_PROCESSED].p_tx_adapt_func = hmac_dpd_data_processed_event_tx_adapt;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC].p_tx_adapt_func = hmac_send_cali_data_tx_adapt;

    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ].p_tx_adapt_func = hmac_scan_proc_sched_scan_req_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG].p_tx_adapt_func = hmac_mgmt_update_user_qos_table_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG].p_tx_adapt_func      = hmac_proc_join_set_reg_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG].p_tx_adapt_func    = hmac_proc_join_set_dtim_reg_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT].p_tx_adapt_func    = hmac_hcc_tx_convert_event_to_netbuf_uint32;
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_PSM_OPMODE_NOTIFY].p_tx_adapt_func  = hmac_hcc_tx_convert_event_to_netbuf_uint16;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER].p_tx_adapt_func  = hmac_hcc_tx_convert_event_to_netbuf_uint32;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER].p_tx_adapt_func  = hmac_user_add_notify_alg_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC].p_tx_adapt_func           = hmac_proc_rx_process_sync_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN].p_tx_adapt_func    = hmac_chan_select_channel_mac_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN].p_tx_adapt_func = hmac_chan_initiate_switch_to_new_channel_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT].p_tx_adapt_func  = hmac_edca_opt_stat_event_tx_adapt;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT].p_tx_adapt_func  = hmac_hcc_tx_convert_event_to_netbuf_uint8;

#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
#endif
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_TX_HOST_TCP_CRX].p_tx_adapt_func    = hmac_proc_tx_process_action_event_tx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_TX_HOST_UDP_CRX].p_tx_adapt_func    = hmac_proc_tx_process_action_event_tx_adapt;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    /* 注册HOST_DRX事件处理函数表 */
    g_ast_dmac_tx_host_drx[DMAC_TX_HOST_DRX].p_tx_adapt_func = hmac_proc_tx_host_tx_adapt;

    /* 注册HOST_CRX事件处理函数表 */
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_INIT].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_CREATE_CFG_VAP].p_tx_adapt_func = hmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_CFG].p_tx_adapt_func = hmac_proc_config_syn_tx_adapt;
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_ALG].p_tx_adapt_func = hmac_proc_config_syn_alg_tx_adapt;

    /*  add support keep alive code for 1102 */
    /* 注册WLAN_DTX事件处理函数表 */
}

/*****************************************************************************
 函 数 名  : hmac_event_fsm_rx_adapt_subtable_register
 功能描述  : hmac模块事件接收适配子表的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_void hmac_event_fsm_rx_adapt_subtable_register(oal_void)
{
    frw_event_sub_rx_adapt_table_init(g_ast_hmac_wlan_drx_event_sub_table,
                                        OAL_SIZEOF(g_ast_hmac_wlan_drx_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        hmac_hcc_rx_convert_netbuf_to_event_default);

    frw_event_sub_rx_adapt_table_init(g_ast_hmac_wlan_crx_event_sub_table,
                                        OAL_SIZEOF(g_ast_hmac_wlan_crx_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        hmac_hcc_rx_convert_netbuf_to_event_default);

    frw_event_sub_rx_adapt_table_init(g_ast_hmac_wlan_ctx_event_sub_table,
                                        OAL_SIZEOF(g_ast_hmac_wlan_ctx_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        hmac_hcc_rx_convert_netbuf_to_event_default);

    frw_event_sub_rx_adapt_table_init(g_ast_hmac_tbtt_event_sub_table,
                                        OAL_SIZEOF(g_ast_hmac_tbtt_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        hmac_hcc_rx_convert_netbuf_to_event_default);

    frw_event_sub_rx_adapt_table_init(g_ast_hmac_wlan_misc_event_sub_table,
                                        OAL_SIZEOF(g_ast_hmac_wlan_misc_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        hmac_hcc_rx_convert_netbuf_to_event_default);
#ifdef _PRE_WLAN_FEATURE_WOW
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_DEV_SYNC_HOST].p_rx_adapt_func = hmac_rx_convert_netbuf_to_netbuf_default;
#endif //_PRE_WLAN_FEATURE_WOW

    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA].p_rx_adapt_func = hmac_rx_process_data_sta_rx_adapt;
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP].p_rx_adapt_func  = hmac_rx_process_data_sta_rx_adapt;

    /* 注册HMAC模块WLAN_CRX事件子表 */
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT].p_rx_adapt_func = hmac_rx_convert_netbuf_to_netbuf_default;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX].p_rx_adapt_func = hmac_rx_process_mgmt_event_rx_adapt;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP].p_rx_adapt_func = hmac_alg_flowctl_backp_rx_adapt;
#endif

    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT].p_rx_adapt_func = hmac_rx_convert_netbuf_to_netbuf_default;
#ifdef  _PRE_WLAN_RF_110X_CALI_DPD
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND].p_rx_adapt_func = hmac_rx_convert_netbuf_to_netbuf_default;
#endif

    /* 注册MISC事件子表 */
	g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_CALI_TO_HMAC].p_rx_adapt_func  = hmac_cali2hmac_misc_event_rx_adapt;

}

#endif
/*****************************************************************************
 函 数 名  : hmac_event_fsm_action_subtable_register
 功能描述  : hmac模块事件执行子表的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_void hmac_event_fsm_action_subtable_register(oal_void)
{
    /* 将事件类型和调用函数的数组注册到事件调度模块 */
    /* 注册WLAN_DTX事件子表 */
    g_ast_hmac_wlan_dtx_event_sub_table[DMAC_TX_WLAN_DTX].p_func = hmac_tx_wlan_to_wlan_ap;

    /* AP模式，注册HMAC模块WLAN_DRX事件子表 */
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP].p_func = hmac_rx_process_data_ap;

    /* STA模式，注册HMAC模块WLAN_DRX事件子表 */
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA].p_func = hmac_rx_process_data_sta;

    /* AP 和STA 公共，注册HMAC模块WLAN_DRX事件子表 */
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE].p_func = hmac_rx_tkip_mic_failure_process;

    /* 注册HMAC模块WLAN_CRX事件子表 */
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT].p_func = hmac_init_event_process;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX].p_func = hmac_rx_process_mgmt_event;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA].p_func = hmac_mgmt_rx_delba_event;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT].p_func = hmac_scan_proc_scanned_bss;
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
      g_ast_hmac_wlan_crx_event_sub_table[DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND].p_func = hmac_dpd_cali_data_recv;
#endif
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP].p_func = hmac_scan_proc_scan_comp_event;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP].p_func = hmac_scan_proc_obss_scan_comp_event;
#endif
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT].p_func = hmac_scan_process_chan_result_event;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC].p_func = hmac_mgmt_send_disasoc_deauth_event;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH].p_func = hmac_mgmt_send_disasoc_deauth_event;

#ifdef _PRE_SUPPORT_ACS
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_ACS_RESP].p_func = hmac_event_acs_response;
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP].p_func = hmac_flowctl_backp_event;
#endif

    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE].p_func = hmac_chan_switch_to_new_chan_complete;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPR_DBAC].p_func = hmac_dbac_status_notify;

    /* 注册TBTT事件子表 */
    g_ast_hmac_tbtt_event_sub_table[DMAC_TBTT_EVENT_SUB_TYPE].p_func = hmac_mgmt_tbtt_event;

    /* 注册发向HOST侧的配置事件子表 */
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_SYN_UP_REG_VAL].p_func = hmac_sdt_up_reg_val;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_CREATE_BA].p_func      = hmac_create_ba_event;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_DEL_BA].p_func         = hmac_del_ba_event;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_SYN_CFG].p_func        = hmac_event_config_syn;
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)) && defined(_PRE_WLAN_CHIP_TEST_ALG)
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_ALG_TEST].p_func       = hmac_alg_test_result_process;
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_DEV_READY_FOR_HOST_SLP].p_func = hmac_wow_proc_dev_ready_slp_event;
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_DEV_SYNC_HOST].p_func = hmac_wow_proc_dev_sync_host_event;
#endif //_PRE_WLAN_FEATURE_WOW
#ifdef _PRE_WLAN_FEATURE_DFS
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_RADAR_DETECT].p_func          = hmac_dfs_radar_detect_event;
   // frw_event_table_register(FRW_EVENT_TYPE_DMAC_MISC, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_misc_event_sub_table);
#endif   /* end of _PRE_WLAN_FEATURE_DFS */
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_DISASOC].p_func               = hmac_proc_disasoc_misc_event;
#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_ROAM_TRIGGER].p_func          = hmac_proc_roam_trigger_event;
#endif //_PRE_WLAN_FEATURE_ROAM
//    frw_event_table_register(FRW_EVENT_TYPE_DMAC_MISC, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_misc_event_sub_table);

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    g_ast_hmac_host_drx_event_sub_table[HMAC_TX_HOST_DRX].p_func = hmac_tx_event_process;
    frw_event_table_register(FRW_EVENT_TYPE_HOST_DRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_hmac_host_drx_event_sub_table);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_ALG_INFO_SYN].p_func           = hmac_syn_info_event;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_VOICE_AGGR].p_func             = hmac_voice_aggr_event;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_CALI_TO_HMAC].p_func          = hmac_save_cali_event;
#endif
#endif
}

/*****************************************************************************
 函 数 名  : hmac_event_fsm_register
 功能描述  : hmac模块事件及其处理函数的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_event_fsm_register(oal_void)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    /*注册所有事件的tx adapt子表*/
    hmac_event_fsm_tx_adapt_subtable_register();

    /*注册所有事件的rx adapt子表*/
    hmac_event_fsm_rx_adapt_subtable_register();
#endif

    /*注册所有事件的执行函数子表*/
    hmac_event_fsm_action_subtable_register();

    event_fsm_table_register();

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_param_check
 功能描述  : Check the struct and var used in hmac
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC means ok, others failed!
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_param_check(oal_void)
{
    /*netbuf's cb size!*/
    oal_uint32 ul_netbuf_cb_size = (oal_uint32)OAL_NETBUF_CB_SIZE();
    if(ul_netbuf_cb_size < (oal_uint32)OAL_SIZEOF(mac_tx_ctl_stru))
    {
        OAL_IO_PRINT("mac_tx_ctl_stru size[%u] large then netbuf cb max size[%u]\n",
                        ul_netbuf_cb_size,(oal_uint32)OAL_SIZEOF(mac_tx_ctl_stru));
        return OAL_EFAIL;
    }

    if(ul_netbuf_cb_size < (oal_uint32)OAL_SIZEOF(mac_rx_ctl_stru))
    {
        OAL_IO_PRINT("mac_rx_ctl_stru size[%u] large then netbuf cb max size[%u]\n",
                        ul_netbuf_cb_size,(oal_uint32)OAL_SIZEOF(mac_rx_ctl_stru));
        return OAL_EFAIL;
    }
    return OAL_SUCC;
}

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
/*debug sysfs*/
extern oal_int32 hmac_tx_event_pkts_info_print(oal_void* data, char* buf, oal_int32 buf_len);
OAL_STATIC oal_kobject* g_conn_syfs_hmac_object = NULL;
OAL_STATIC oal_int32 hmac_print_vap_stat(oal_void* data, char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;
    oal_uint8               uc_vap_id;
    oal_net_device_stru    *pst_net_device = NULL;
    hmac_vap_stru          *pst_hmac_vap = NULL;
    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if(NULL == pst_hmac_vap)
        {
            continue;
        }
        ret +=  snprintf(buf + ret , buf_len - ret, "vap %2u info:\n",uc_vap_id);
        ret +=  snprintf(buf + ret , buf_len - ret, "vap_state %2u,protocol:%2u,user nums:%2u,init:%u\n",
                                                    pst_hmac_vap->st_vap_base_info.en_vap_state,
                                                    pst_hmac_vap->st_vap_base_info.en_protocol,
                                                    pst_hmac_vap->st_vap_base_info.us_user_nums,
                                                    pst_hmac_vap->st_vap_base_info.uc_init_flag);
        pst_net_device = pst_hmac_vap->pst_net_device;
        if(NULL != pst_net_device)
        {
        	oal_int32 i;
        	ret +=  snprintf(buf + ret , buf_len - ret, "net name:%s\n",netdev_name(pst_net_device));
            ret +=  snprintf(buf + ret , buf_len - ret, "tx [%d]queues info,state [bit0:DRV_OFF],[bit1:STACK_OFF],[bit2:FROZEN]\n",
                                                        pst_net_device->num_tx_queues);
        	for (i = 0; i < pst_net_device->num_tx_queues; i++) {
        		struct netdev_queue *txq = netdev_get_tx_queue(pst_net_device, i);
        		if(txq->state)
        		    ret +=  snprintf(buf + ret , buf_len - ret, "net queue[%2d]'s state:0x%lx\n",i,txq->state);
        	}
        }
        ret +=  snprintf(buf + ret , buf_len - ret, "\n");
    }
    return ret;
}

OAL_STATIC ssize_t  hmac_get_vap_stat(struct device *dev, struct device_attribute *attr, char* buf)
{
    int ret = 0;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);
    ret += hmac_print_vap_stat(NULL,buf,PAGE_SIZE - ret);
    return ret;
}
OAL_STATIC DEVICE_ATTR(vap_info, S_IRUGO, hmac_get_vap_stat, NULL);

OAL_STATIC ssize_t  hmac_get_adapt_info(struct device *dev, struct device_attribute *attr, char* buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret += hmac_tx_event_pkts_info_print(NULL, buf + ret,PAGE_SIZE - ret);
    return ret;
}

oal_int32 hmac_wakelock_info_print(char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;

#ifdef CONFIG_PRINTK
    if(g_st_hmac_wakelock.locked_addr)
    {
        ret +=  snprintf(buf + ret , buf_len - ret,"wakelocked by:%pf\n",
                    (oal_void*)g_st_hmac_wakelock.locked_addr);
    }
#endif

    ret +=  snprintf(buf + ret , buf_len - ret,"hold %lu locks\n", g_st_hmac_wakelock.lock_count);

    return ret;
}

OAL_STATIC ssize_t  hmac_get_wakelock_info(struct device *dev, struct device_attribute *attr, char*buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret += hmac_wakelock_info_print(buf,PAGE_SIZE - ret);

    return ret;
}

OAL_STATIC DEVICE_ATTR(adapt_info, S_IRUGO, hmac_get_adapt_info, NULL);
OAL_STATIC DEVICE_ATTR(wakelock, S_IRUGO, hmac_get_wakelock_info, NULL);

OAL_STATIC ssize_t  hmac_show_roam_status(struct device *dev, struct device_attribute *attr, char* buf)
{
    oal_int32               ret = 0;
    oal_uint8               uc_vap_id;
    oal_uint8               uc_roming_now  = 0;
    hmac_vap_stru          *pst_hmac_vap   = NULL;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru         *pst_hmac_user_multi;
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_device_stru    *pst_hmac_device;
    pst_hmac_device = hmac_res_get_mac_dev(0);
#endif

    if (OAL_PTR_NULL == buf)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{buf is NULL.}");
        return ret;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{device buff is NULL.}");
        return ret;
    }
#endif

    if ((OAL_PTR_NULL == dev) || (OAL_PTR_NULL == attr))
    {
        ret +=  snprintf(buf , PAGE_SIZE, "roam_status=0\n");
        return ret;
    }

    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);

        if(OAL_PTR_NULL == pst_hmac_vap)
        {
            continue;
        }

        if (WLAN_VAP_MODE_BSS_STA != pst_hmac_vap->st_vap_base_info.en_vap_mode)
        {
            continue;
        }
#ifdef _PRE_WLAN_FEATURE_ROAM
        if (MAC_VAP_STATE_ROAMING == pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            uc_roming_now = 1;
            break;
        }
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
        /* wapi下，将roam标志置为1，防止arp探测 */
        pst_hmac_user_multi = (hmac_user_stru *)mac_res_get_hmac_user(pst_hmac_vap->st_vap_base_info.us_multi_user_idx);
        if (OAL_PTR_NULL == pst_hmac_user_multi)
        {
            continue;
        }

        if (OAL_TRUE == pst_hmac_user_multi->st_wapi.uc_port_valid)
        {
            uc_roming_now = 1;
            break;
        }
#endif/* #ifdef _PRE_WLAN_FEATURE_WAPI */

    }
    /* 先出一个版本强制关闭arp探测，测试下效果 */
    //uc_roming_now = 1;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if ((WLAN_AMPDU_RX_BUFFER_SIZE > pst_hmac_device->st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size)
    && (0 < pst_hmac_device->st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size))
    {
        uc_roming_now = 1;
    }
#endif

    ret +=  snprintf(buf , PAGE_SIZE, "roam_status=%1d\n", uc_roming_now);
    return ret;
}

OAL_STATIC DEVICE_ATTR(roam_status, S_IRUGO, hmac_show_roam_status, NULL);


OAL_STATIC ssize_t hmac_set_rxthread_enable(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    oal_uint32 ul_val;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    if ((sscanf(buf, "%u", &ul_val) != 1))
    {
        OAL_IO_PRINT("set value one char!\n");
        return -OAL_EINVAL;
    }

    g_st_rxdata_thread.en_rxthread_enable = (oal_bool_enum_uint8)ul_val;

    return count;
}
OAL_STATIC ssize_t hmac_get_rxthread_info(struct device *dev, struct device_attribute *attr, char* buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret +=  snprintf(buf , PAGE_SIZE, "rxthread_enable=%d\nrxthread_queue_len=%d\nrxthread_pkt_loss=%d\n",
            g_st_rxdata_thread.en_rxthread_enable, oal_netbuf_list_len(&g_st_rxdata_thread.st_rxdata_netbuf_head), g_st_rxdata_thread.ul_pkt_loss_cnt);

    return ret;
}
OAL_STATIC DEVICE_ATTR(rxdata_info, S_IRUGO|S_IWUSR, hmac_get_rxthread_info, hmac_set_rxthread_enable);

OAL_STATIC struct attribute *hmac_sysfs_entries[] = {
        &dev_attr_vap_info.attr,
        &dev_attr_adapt_info.attr,
        &dev_attr_wakelock.attr,
        &dev_attr_roam_status.attr,
        &dev_attr_rxdata_info.attr,
        NULL
};

OAL_STATIC struct attribute_group hmac_attribute_group = {
        .name = "vap",
        .attrs = hmac_sysfs_entries,
};

OAL_STATIC oal_int32 hmac_sysfs_entry_init(oal_void)
{
    oal_int32       ret = OAL_SUCC;
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{hmac_sysfs_entry_init::get sysfs root object failed!}");
        return -OAL_EFAIL;
    }

    g_conn_syfs_hmac_object = kobject_create_and_add("hmac", pst_root_object);
    if(NULL == g_conn_syfs_hmac_object)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{hmac_sysfs_entry_init::create hmac object failed!}");
        return -OAL_EFAIL;
    }

    ret = sysfs_create_group(g_conn_syfs_hmac_object, &hmac_attribute_group);
    if (ret)
    {
        kobject_put(g_conn_syfs_hmac_object);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{hmac_sysfs_entry_init::sysfs create group failed!}");
        return ret;
    }
    return OAL_SUCC;
}

OAL_STATIC oal_int32 hmac_sysfs_entry_exit(oal_void)
{
    if(g_conn_syfs_hmac_object)
    {
        sysfs_remove_group(g_conn_syfs_hmac_object, &hmac_attribute_group);
        kobject_put(g_conn_syfs_hmac_object);
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
OAL_STATIC DECLARE_WIFI_PANIC_STRU(hmac_panic_vap_stat,hmac_print_vap_stat);
#endif

oal_uint32 hmac_get_pm_pause_func(oal_void)
{
    hmac_device_stru    *pst_hmac_device;

    /* 获取mac device结构体指针 */
    pst_hmac_device = hmac_res_get_mac_dev(0);

    if (OAL_PTR_NULL == pst_hmac_device)
    {
       OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_get_pm_pause_func::pst_device null.}");

       return OAL_FALSE;
    }

    if(OAL_TRUE == pst_hmac_device->st_scan_mgmt.en_is_scanning)
    {
        OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_get_pm_pause_func::in scanning}");
        return  OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }

}

oal_void hmac_register_pm_callback(oal_void)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))

    struct wifi_srv_callback_handler *pst_wifi_srv_handler;

    pst_wifi_srv_handler = wlan_pm_get_wifi_srv_handler();

    if(pst_wifi_srv_handler)
    {
        pst_wifi_srv_handler ->p_wifi_srv_get_pm_pause_func = hmac_get_pm_pause_func;
    }
    else
    {
        OAL_IO_PRINT("hmac_register_pm_callback:wlan_pm_get_wifi_srv_handler is null\n");
    }
#endif

}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_bool_enum_uint8 hmac_get_rxthread_enable(oal_void)
{
    return g_st_rxdata_thread.en_rxthread_enable;
}

oal_void hmac_rxdata_sched(oal_void)
{
    //OAL_IO_PRINT("[hcc]timestamp:%llu , netbuf_num:%d.", oal_cpu_clock(), oal_netbuf_list_len(&g_st_rxdata_netbuf_head));
    //OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&g_st_rxdata_wq);
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_up(&g_st_rxdata_thread.st_rxdata_sema);
#endif
    return;
}
oal_void hmac_rxdata_netbuf_enqueue(oal_netbuf_stru  *pst_netbuf)
{
    if(1000 < oal_netbuf_list_len(&g_st_rxdata_thread.st_rxdata_netbuf_head))
    {
        oal_netbuf_free(pst_netbuf);
        g_st_rxdata_thread.ul_pkt_loss_cnt++;
        return;
    }
    oal_netbuf_list_tail(&g_st_rxdata_thread.st_rxdata_netbuf_head, pst_netbuf);
    return;
}

OAL_STATIC oal_int32 hmac_rxdata_thread(oal_void* p_data)
{
    //oal_int32           l_ret = 20000;
    oal_netbuf_stru    *pst_netbuf = OAL_PTR_NULL;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_kthread_param_stru thread_param = {0};
    thread_param.l_prio    = HCC_TRANS_RXDATA_THERAD_PRIORITY;
    thread_param.l_nice    = HCC_TRANS_RXDATA_THERAD_NICE;
    thread_param.l_policy  = HCC_TRANS_RXDATA_THREAD_POLICY;
    oal_set_thread_property(OAL_CURRENT,&thread_param);

    allow_signal(SIGTERM);
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    while(OAL_LIKELY(!oal_down_interruptible(&g_st_rxdata_thread.st_rxdata_sema)))
#else
    for(;;)
#endif
    {
        if (oal_kthread_should_stop())
        {
            break;
        }

        //OAL_IO_PRINT("[rxd]timestamp:%llu , netbuf_num:%d.", oal_cpu_clock(), oal_netbuf_list_len(&g_st_rxdata_netbuf_head));
        pst_netbuf = oal_netbuf_delist(&g_st_rxdata_thread.st_rxdata_netbuf_head);
        if(pst_netbuf)
        {
            /* 将skb转发给桥 */
            oal_netif_rx_ni(pst_netbuf);

            //pst_netbuf = oal_netbuf_delist(&g_st_rxdata_netbuf_head);
        }
    }
    return OAL_SUCC;
}

OAL_STATIC oal_void hmac_hisi_thread_init(oal_void)
{
    oal_kthread_param_stru st_thread_param = {0};
#if defined(_PRE_WLAN_TCP_OPT) && !defined(WIN32)
    hmac_set_hmac_tcp_ack_process_func(hmac_tcp_ack_process);
    hmac_set_hmac_tcp_ack_need_schedule(hmac_tcp_ack_need_schedule);

    st_thread_param.l_cpuid       = NOT_BIND_CPU;
    st_thread_param.l_policy      = HCC_TRANS_THREAD_POLICY;
    st_thread_param.l_prio        = HCC_TRANS_THERAD_PRIORITY;
    st_thread_param.ul_stacksize  = HCC_TRANS_THERAD_STACKSIZE;
    hcc_get_default_handler()->hcc_transer_info.hcc_transfer_thread = oal_kthread_create("hisi_hcc",hcc_transfer_thread,
                                        (void*)hcc_get_default_handler(),
                                        &st_thread_param);
    if(!hcc_get_default_handler()->hcc_transer_info.hcc_transfer_thread)
    {
        OAL_IO_PRINT("hcc thread create failed!\n");
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        mutex_destroy(&hcc_get_default_handler()->tx_transfer_lock);
#endif
    }
#endif

    OAL_WAIT_QUEUE_INIT_HEAD(&g_st_rxdata_thread.st_rxdata_wq);

    oal_netbuf_list_head_init(&g_st_rxdata_thread.st_rxdata_netbuf_head);

    g_st_rxdata_thread.en_rxthread_enable = OAL_TRUE;
    g_st_rxdata_thread.ul_pkt_loss_cnt    = 0;


    oal_sema_init(&g_st_rxdata_thread.st_rxdata_sema,0);

    OAL_MEMZERO(&st_thread_param, OAL_SIZEOF(oal_kthread_param_stru));
    st_thread_param.l_cpuid      = NOT_BIND_CPU;
    st_thread_param.l_policy     = HCC_TRANS_RXDATA_THREAD_POLICY;
    st_thread_param.l_prio       = HCC_TRANS_RXDATA_THERAD_PRIORITY;
    st_thread_param.ul_stacksize = HCC_TRANS_RXDATA_THERAD_STACKSIZE;
    g_st_rxdata_thread.pst_rxdata_thread = oal_kthread_create("hisi_rxdata",hmac_rxdata_thread,NULL,&st_thread_param);
    if (OAL_PTR_NULL == g_st_rxdata_thread.pst_rxdata_thread)
    {
        OAL_IO_PRINT("hisi_rxdata thread create failed!\n");
    }
    return;
}

OAL_STATIC oal_void hmac_hisi_thread_exit(oal_void)
{
#if defined(_PRE_WLAN_TCP_OPT) && !defined(WIN32)
    oal_kthread_stop(hcc_get_default_handler()->hcc_transer_info.hcc_transfer_thread);
    hcc_get_default_handler()->hcc_transer_info.hcc_transfer_thread = NULL;
#endif

    oal_kthread_stop(g_st_rxdata_thread.pst_rxdata_thread);
    g_st_rxdata_thread.pst_rxdata_thread = NULL;
}
#endif
/*****************************************************************************
 函 数 名  : hmac_main_init
 功能描述  : HMAC模块初始化总入口，包含HMAC模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  hmac_main_init(oal_void)
{
    oal_uint32            ul_return;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#endif
    frw_init_enum_uint16  en_init_state;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
#endif

    oal_wake_lock_init(&g_st_hmac_wakelock, "wlan_hmac_wakelock");

    /* 为了解各模块的启动时间，增加时间戳打印 TBD */
    if(OAL_SUCC != hmac_param_check())
    {
        OAL_IO_PRINT("hmac_main_init:hmac_param_check failed!\n");
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_hcc_adapt_init();

#endif

    en_init_state = frw_get_init_state();

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_UNLIKELY((FRW_INIT_STATE_BUTT == en_init_state) || (en_init_state < FRW_INIT_STATE_FRW_SUCC)))
#else
    if (OAL_UNLIKELY((FRW_INIT_STATE_BUTT == en_init_state) || (en_init_state < FRW_INIT_STATE_DMAC_CONFIG_VAP_SUCC)))
#endif
    {
        OAL_IO_PRINT("hmac_main_init:en_init_state is error %d\n", en_init_state);
        frw_timer_delete_all_timer();
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    hmac_set_auto_freq_process_func();
    hmac_wifi_auto_freq_ctrl_init();
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_hisi_thread_init();

    ul_return = mac_res_init();
    if (OAL_SUCC != ul_return)
    {
        OAL_IO_PRINT("hmac_main_init: mac_res_init return err code %d\n", ul_return);
        frw_timer_delete_all_timer();
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }
#endif

    /* hmac资源初始化 */
    hmac_res_init();

    /* 如果初始化状态处于配置VAP成功前的状态，表明此次为HMAC第一次初始化，即重加载或启动初始化 */
    if (en_init_state < FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC)
    {
        /* 调用状态机初始化接口 */
        hmac_fsm_init();

        hmac_rx_filter_init();

        /* 事件注册 */
        hmac_event_fsm_register();

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* DMAC OFFLOAD下不需要抛事件到得device获取chip信息 */
        ul_return = hmac_board_init(&g_st_hmac_board);
        if (OAL_SUCC != ul_return)
        {
            frw_timer_delete_all_timer();
            event_fsm_unregister();
            mac_res_exit();
            hmac_res_exit(&g_st_hmac_board);  /* 释放hmac res资源 */
            OAL_BUG_ON(1);
            return OAL_FAIL;
        }
#else
    	/* 抛事件给dmac */
        pst_event_mem = FRW_EVENT_ALLOC(0);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
        {
            OAL_IO_PRINT("hmac_main_init: FRW_EVENT_ALLOC result = OAL_PTR_NULL.\n");
            frw_timer_delete_all_timer();
            OAL_BUG_ON(1);
            return -OAL_EFAIL;
        }

        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        /* 填写事件头 */
        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_CRX,
                        HMAC_TO_DMAC_SYN_INIT,
                        0,
                        FRW_EVENT_PIPELINE_STAGE_1,
                        0,0,0);
        ul_return = frw_event_dispatch_event(pst_event_mem);
        if (OAL_SUCC != ul_return)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_main_init::frw_event_dispatch_event failed[%d].}", ul_return);
        }

        /* 释放事件 */
        FRW_EVENT_FREE(pst_event_mem);
#endif

        frw_set_init_state(FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC);

        /* 启动成功后，输出打印 */
    }
    else
    {
        /* TBD 迭代10 康国昌修改 如果初始化状态为配置VAP成功后的状态，则表明本次为配置触发的初始化，
           需要遍历所有业务VAP，并检查其状态；如未初始化，则需要初始化其相关内容
           如支持特性接口挂接 */
    }

#ifdef _PRE_WLAN_CHIP_TEST
    hmac_test_init();
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
    hmac_data_acq_init();
#endif

    /* DFX 模块初始化 */
    hmac_dfx_init();

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)) && defined(_PRE_WLAN_CHIP_TEST_ALG)
    hmac_alg_test_main_common_init();
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
    oal_profiling_mips_init();
#endif

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    hmac_sysfs_entry_init();
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
    hwifi_panic_log_register(&hmac_panic_vap_stat,NULL);
#endif

    hmac_register_pm_callback();

#ifdef _PRE_SUPPORT_ACS
    hmac_acs_init();
#endif

#if 0 //#ifdef _PRE_WLAN_FEATURE_WOW
    hmac_wow_init();
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_main_exit
 功能描述  : HMAC模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_main_exit(oal_void)
{
    oal_uint32 ul_return;
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    hmac_sysfs_entry_exit();
#endif
    event_fsm_unregister();

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_hisi_thread_exit();
#endif

#if 0
    ul_return = mac_device_board_destroy(&g_st_hmac_board);
    if (OAL_UNLIKELY(OAL_SUCC != ul_return))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_main_exit::mac_device_board_destroy failed[%d].}", ul_return);
        return ;
    }
#else
    ul_return = hmac_board_exit(&g_st_hmac_board);
    if (OAL_UNLIKELY(OAL_SUCC != ul_return))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_main_exit::hmac_board_exit failed[%d].}", ul_return);
        return ;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
    hmac_data_acq_exit();
#endif
    /* DFX 模块初始化 */
    hmac_dfx_exit();

    hmac_rx_filter_exit();

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    hmac_wifi_auto_freq_ctrl_deinit();
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    frw_set_init_state(FRW_INIT_STATE_FRW_SUCC);
#else
    frw_set_init_state(FRW_INIT_STATE_DMAC_CONFIG_VAP_SUCC);
#endif
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)) && defined(_PRE_WLAN_CHIP_TEST_ALG)
    hmac_alg_test_main_common_exit();
#endif

    oal_wake_lock_exit(&g_st_hmac_wakelock);

#ifdef _PRE_SUPPORT_ACS
    hmac_acs_exit();
#endif

}

/*****************************************************************************
 函 数 名  : hmac_sdt_recv_reg_cmd
 功能描述  : SDT下发读写寄存器命令，在hmac层抛事件给dmac来处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sdt_recv_reg_cmd(
                            mac_vap_stru  *pst_mac_vap,
                            oal_uint8     *puc_buf,
                            oal_uint16     us_len)
{
    frw_event_mem_stru          *pst_event_mem;
    frw_event_stru              *pst_event;

    pst_event_mem = FRW_EVENT_ALLOC(us_len - OAL_IF_NAME_SIZE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_sdt_recv_reg_cmd::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CRX,
                       HMAC_TO_DMAC_SYN_REG,
                       (oal_uint16)(us_len - OAL_IF_NAME_SIZE),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    oal_memcopy(pst_event->auc_event_data, puc_buf + OAL_IF_NAME_SIZE, us_len - OAL_IF_NAME_SIZE);

    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sdt_up_reg_val
 功能描述  : hmac接收dmac抛回来的寄存器的值，然后交给wal，wal上报SDT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sdt_up_reg_val(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru      *pst_event;
    hmac_vap_stru       *pst_hmac_vap;
    oal_uint32          *pst_reg_val;

    pst_event = (frw_event_stru  *)pst_event_mem->puc_data;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{hmac_sdt_up_reg_val::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_reg_val = (oal_uint32 *)pst_hmac_vap->st_cfg_priv.ac_rsp_msg;
   *pst_reg_val = *((oal_uint32 *)pst_event->auc_event_data);

   /* 唤醒wal_sdt_recv_reg_cmd等待的进程 */
   pst_hmac_vap->st_cfg_priv.en_wait_ack_for_sdt_reg = OAL_TRUE;
   OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&(pst_hmac_vap->st_cfg_priv.st_wait_queue_for_sdt_reg));

   return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_create_ba_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_create_ba_event(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru      *pst_event;
    hmac_user_stru      *pst_hmac_user;
    hmac_vap_stru       *pst_hmac_vap;
    mac_tx_ctl_stru      st_cb;
    dmac_to_hmac_ctx_event_stru    *pst_create_ba_event;

    pst_event = (frw_event_stru  *)pst_event_mem->puc_data;

    pst_create_ba_event = (dmac_to_hmac_ctx_event_stru *)pst_event->auc_event_data;

    pst_hmac_user = mac_res_get_hmac_user(pst_create_ba_event->us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{hmac_create_ba_event::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap  = mac_res_get_hmac_vap(pst_create_ba_event->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{hmac_create_ba_event::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    st_cb.uc_tid  = pst_create_ba_event->uc_tid;

    hmac_tx_ba_setup(pst_hmac_vap, pst_hmac_user, st_cb.uc_tid);

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : hmac_del_ba_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_del_ba_event(frw_event_mem_stru  *pst_event_mem)
{
    oal_uint8           uc_tid;
    frw_event_stru     *pst_event;
    hmac_user_stru     *pst_hmac_user;
    hmac_vap_stru      *pst_hmac_vap;

    mac_action_mgmt_args_stru       st_action_args;   /* 用于填写ACTION帧的参数 */
    hmac_tid_stru                  *pst_hmac_tid;
    oal_uint32                      ul_ret;
    dmac_to_hmac_ctx_event_stru    *pst_del_ba_event;

    pst_event = (frw_event_stru  *)pst_event_mem->puc_data;

    pst_del_ba_event = (dmac_to_hmac_ctx_event_stru *)pst_event->auc_event_data;

    pst_hmac_user = mac_res_get_hmac_user(pst_del_ba_event->us_user_index);

    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_del_ba_event::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap  = mac_res_get_hmac_vap(pst_del_ba_event->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_del_ba_event::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_set_cur_protocol_mode(&pst_hmac_user->st_user_base_info, pst_del_ba_event->uc_cur_protocol);
    ul_ret = hmac_config_user_info_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
#endif

    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        pst_hmac_tid  = &pst_hmac_user->ast_tid_info[uc_tid];

        if (DMAC_BA_INIT == pst_hmac_tid->st_ba_tx_info.en_ba_status)
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_del_ba_event::the tx hdl is not exist.}");
            continue;
        }

        st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
        st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
        st_action_args.ul_arg1     = uc_tid;       /* 该数据帧对应的TID号 */
        st_action_args.ul_arg2     = MAC_ORIGINATOR_DELBA;           /* ADDBA_REQ中，buffer_size的默认大小 */
        st_action_args.ul_arg3     = MAC_UNSPEC_REASON;              /* BA会话的确认策略 */
        st_action_args.puc_arg5    = pst_hmac_user->st_user_base_info.auc_user_mac_addr;   /* ba会话对应的user */

        /* 删除BA会话 */
        ul_ret = hmac_mgmt_tx_action(pst_hmac_vap,  pst_hmac_user, &st_action_args);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_del_ba_event::hmac_mgmt_tx_action failed.}");
            continue;
        }
    }

    return OAL_SUCC;

}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hmac_syn_info_event
 功能描述  : 处理协议模式同步事件
 输入参数  : pst_event_mem
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_syn_info_event(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru      *pst_event;
    hmac_user_stru      *pst_hmac_user;
    mac_vap_stru        *pst_mac_vap;
    oal_uint32           ul_relt;

    dmac_to_hmac_syn_info_event_stru    *pst_syn_info_event;

    pst_event = (frw_event_stru  *)pst_event_mem->puc_data;
    pst_syn_info_event = (dmac_to_hmac_syn_info_event_stru *)pst_event->auc_event_data;
    pst_hmac_user = mac_res_get_hmac_user(pst_syn_info_event->us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_syn_info_event: pst_hmac_user null,user_idx=%d.}", pst_syn_info_event->us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap = mac_res_get_mac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_syn_info_event: pst_mac_vap null! vap_idx=%d, user_idx=%d.}",
                pst_hmac_user->st_user_base_info.uc_vap_id,
                pst_syn_info_event->us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_cur_protocol_mode(&pst_hmac_user->st_user_base_info, pst_syn_info_event->uc_cur_protocol);
    mac_user_set_cur_bandwidth(&pst_hmac_user->st_user_base_info, pst_syn_info_event->uc_cur_bandwidth);
    ul_relt = hmac_config_user_info_syn(pst_mac_vap, &pst_hmac_user->st_user_base_info);

    return ul_relt;

}

/*****************************************************************************
 函 数 名  : hmac_voice_aggr_event
 功能描述  : 处理Voice聚合同步事件
 输入参数  : pst_event_mem
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_voice_aggr_event(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru      *pst_event;
    mac_vap_stru        *pst_mac_vap;

    dmac_to_hmac_voice_aggr_event_stru    *pst_voice_aggr_event;

    pst_event = (frw_event_stru  *)pst_event_mem->puc_data;
    pst_voice_aggr_event = (dmac_to_hmac_voice_aggr_event_stru *)pst_event->auc_event_data;

    pst_mac_vap = mac_res_get_mac_vap(pst_voice_aggr_event->uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_voice_aggr_event: pst_mac_vap null! vap_idx=%d}",
                pst_voice_aggr_event->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap->bit_voice_aggr = pst_voice_aggr_event->en_voice_aggr;

    return OAL_SUCC;
}
#endif

#ifdef _PRE_SUPPORT_ACS

/*****************************************************************************
 函 数 名  : hmac_config_set_acs_cmd
 功能描述  : HMAC 层设置DMAC ACS的命令
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月16日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_config_set_acs_cmd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_mac_device;
    hmac_device_stru               *pst_hmac_device;
    oal_uint32                      ul_ret;
    mac_acs_cmd_stru               *pst_acs_cmd;

    /* 获取device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);

    if ((OAL_PTR_NULL == pst_hmac_device) || OAL_PTR_NULL == pst_hmac_device->pst_device_base_info || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_set_acs_cmd::null param,pst_hmac_device=%x puc_param=%x}",
                       pst_hmac_device, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = pst_hmac_device->pst_device_base_info;

    if (pst_mac_device == OAL_PTR_NULL || OAL_PTR_NULL == pst_mac_device->pst_acs)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_set_acs_cmd::pst_acs null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_acs_cmd = (mac_acs_cmd_stru *)puc_param;

    if (pst_acs_cmd->uc_cmd >=  DMAC_ACS_CMD_BUTT)
    {
        return OAL_SUCC;
    }

    if(pst_acs_cmd->uc_cmd == DMAC_ACS_CMD_DO_SCAN)
    {
        return hmac_init_scan_do(pst_hmac_device, pst_mac_vap, (mac_init_scan_req_stru *)pst_acs_cmd);
    }
    else if (pst_acs_cmd->uc_cmd == DMAC_ACS_CMD_SET_BEST_CHANNEL
             && pst_acs_cmd->auc_arg[0] == MAC_ACS_SET_CH_INIT)
    {
        return hmac_acs_got_init_rank(pst_hmac_device, pst_mac_vap, pst_acs_cmd);
    }

    /***************************************************************************
     抛事件到DMAC层, 同步DMAC数据
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_ACS_PARAM, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_set_acs_cmd::hmac_config_send_event failed[%d].}", ul_ret);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_handle_acs_response
 功能描述  : 将DMAC ACS的命令处理结果返回给WAL层
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_event_acs_response(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru                     *pst_event;

    /* 转发事件，只修改以下成员 */
    pst_event    = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event->st_event_hdr.en_type = FRW_EVENT_TYPE_HOST_CTX;
    pst_event->st_event_hdr.uc_sub_type = HMAC_HOST_CTX_EVENT_SUB_TYPE_ACS_RESPONSE;
    pst_event->st_event_hdr.en_pipeline = FRW_EVENT_PIPELINE_STAGE_0;

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_SUPPORT_ACS */

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
/*****************************************************************************
 函 数 名  : hmac_flowctl_backp_event
 功能描述  : 将dmac发送流控制反压信息传递给wal层
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_flowctl_backp_event(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru              *pst_hmac_to_wal_event;  /* 指向申请事件的payload指针 */
    mac_ioctl_queue_backp_stru  *pst_flowctl_backp_event;
    mac_vap_stru                *pst_mac_vap;
    oal_uint32                   ul_ret;
    hmac_user_stru              *pst_hmac_user;

    /* 获得事件指针 */
    pst_hmac_to_wal_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_flowctl_backp_event = (mac_ioctl_queue_backp_stru *)(pst_hmac_to_wal_event->auc_event_data);

    pst_mac_vap = (mac_vap_stru *) mac_res_get_mac_vap(pst_flowctl_backp_event->uc_vap_id);

    /* 对vap/user状态进行同步 */
    if (0xFFFF == pst_flowctl_backp_event->us_assoc_id)
    {
        pst_mac_vap->bit_vap_bw_limit = pst_flowctl_backp_event->uc_is_stop;
    }
    else if (WLAN_TID_MAX_NUM == pst_flowctl_backp_event->uc_tidno)
    {
        pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_flowctl_backp_event->us_assoc_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_edca_opt_rx_pkts_stat::null param,pst_hmac_user[%d].}",pst_flowctl_backp_event->us_assoc_id);
            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_hmac_user->en_user_bw_limit = (oal_bool_enum_uint8)(pst_flowctl_backp_event->uc_is_stop);
    }

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_wal_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_FLOWCTL_BACKP,
                       WLAN_MEM_EVENT_SIZE1,
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /* 分发 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_flowctl_backp_event::frw_event_dispatch_event null.}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}
#endif



/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(hmac_main_init);
oal_module_exit(hmac_main_exit);
#endif
oal_module_symbol(hmac_board_get_instance);
oal_module_symbol(hmac_sdt_recv_reg_cmd);
#ifdef _PRE_SUPPORT_ACS
oal_module_symbol(hmac_config_set_acs_cmd);
#endif

oal_module_license("GPL");
/*lint +e578*//*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
