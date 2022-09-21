/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_config.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年1月8日
  最近修改   :
  功能描述   : dmac_config.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_CONFIG_H__
#define __DMAC_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "frw_ext_if.h"
#include "mac_vap.h"
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
#include "dmac_wow.h"
#endif

#include "dmac_alg_if.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_CONFIG_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_HIPRIV_CMD_NAME_MAX_LEN  16                             /* 字符串中每个单词的最大长度 */
#define DMAC_RX_LPF_GAIN  6                             /* 字符串中每个单词的最大长度 */
#define DMAC_DBM_CH  (-13)                             /* 字符串中每个单词的最大长度 */
#define DMAC_SINGLE_DOUBLE_SWITCH_GAIN  (3)                             /* 字符串中每个单词的最大长度 */
#define DMAC_RSSI_REF_DIFFERENCE  (20)                             /* 字符串中每个单词的最大长度 */
#define DMAC_RADAR_REF_DIFFERENCE  (24)                             /* 字符串中每个单词的最大长度 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    DMAC_MIPS_CYCLE_SWITCH_OFF,
    DMAC_MIPS_CYCLE_SWITCH_ON,

    DMAC_MIPS_CYCLE_SWITCH_BUTT
}dmac_mips_cycle_switch_enum;

typedef oal_uint8 dmac_mips_cycle_switch_enum_uint8;

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
extern oal_uint32  dmac_event_config_syn(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_config_set_qap_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_config_set_qap_cwmax(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_config_set_qap_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_config_set_qap_txop_limit(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_get_cmd_one_arg(oal_int8 *pc_cmd, oal_int8 *pc_arg, oal_uint32 *pul_cmd_offset);
extern oal_uint32  dmac_config_set_qap_msdu_lifetime(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#if 0
extern oal_void  dmac_config_set_wmm_open_cfg(hal_to_dmac_vap_stru *pst_hal_device, mac_wme_param_stru  *pst_wmm);
extern oal_void  dmac_config_set_wmm_close_cfg(hal_to_dmac_vap_stru *pst_hal_device, mac_wme_param_stru  *pst_wmm);
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_uint32 dmac_sta_set_ps_enable(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#ifdef _PRE_PSM_DEBUG_MODE
//extern oal_void dmac_pm_info(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32 dmac_show_ps_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif
extern oal_uint32 dmac_config_set_sta_pm_on(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#if ((_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION) ||(_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) )
extern oal_uint32  dmac_config_set_meta(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
extern  oal_uint32  dmac_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern  oal_uint32  dmac_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern  oal_uint32  dmac_config_enable_arp_offload(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern  oal_uint32  dmac_config_set_ip_addr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern  oal_uint32  dmac_config_show_arpoffload_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32  dmac_dpd_data_processed_recv(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_start_dpd_calibration(mac_vap_stru *pst_mac_vap);

#endif
extern oal_uint32  dmac_cali_hmac2dmac_recv(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_cali_to_hmac(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_uint32  dmac_config_set_monitor_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
oal_void  dmac_config_get_tx_rate_info(hal_tx_txop_alg_stru    *pst_tx_alg,
                                       mac_data_rate_stru      *pst_mac_rates_11g,
                                       oal_rate_info_stru      *pst_rate_info);
#endif
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
extern oal_uint32 dmac_pkt_mem_opt_stat_event_process(frw_event_mem_stru *pst_event_mem);
#endif /* */
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
extern oal_void dmac_config_update_rate_pow_table(oal_void);
extern oal_void dmac_config_update_scaling_reg(oal_void);
extern oal_void dmac_config_update_dsss_scaling_reg(dmac_alg_tpc_user_distance_enum_uint8 en_dmac_device_distance_enum);
#endif  /* _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_WLAN_FEATURE_WOW
extern oal_uint32 dmac_config_wow_sleep_wakeup_notify(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32 dmac_config_wow_set_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif /* _PRE_WLAN_FEATURE_WOW */

#if 0
/* 1131C-debug M3无此功能 */
OAL_INLINE oal_uint32 get_cycle_count(void)
{
    return 0;
}
OAL_INLINE void enable_cycle_counter(void)
{
    return;
}
OAL_INLINE void disable_cycle_counter(void)
{

}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_config */
