/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_alg_if.h
  版 本 号   : 初稿
  作    者   : 陈艳
  生成日期   : 2013年3月21日
  最近修改   :
  功能描述   : DMAC to ALG的API接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月21日
    作    者   : 陈艳
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ALG_IF_H__
#define __DMAC_ALG_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "oal_net.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ALG_IF_H
#define  ALG_TXRX_DATA_MAXNUM    4			/*与ALG_TXRX_DATA_BUTT相同*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

typedef enum
{
    CH_BW_CHG_TYPE_MOVE_WORK,
    CH_BW_CHG_TYPE_SCAN,

    CH_BW_CHG_TYPE_BUTT
}dmac_alg_channel_bw_chg_type;
typedef oal_uint8 dmac_alg_channel_bw_chg_type_uint8;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef enum
{
    BT_TRANSFER_OFF,
    BT_TRANSFER_ON,

    BT_STATE_TYPE_BUTT
}dmac_alg_bt_state_type;
typedef oal_uint8 dmac_alg_bt_state_type_uint8;
#endif

/* 常用代码简化 */
#define DMAC_ALG_IS_DEV_INIT_DONE(_ul_chip_num, _ul_dev_num, _pst_mac_board)     \
        (OAL_TRUE == _pst_mac_board->ast_chip[_ul_chip_num].ast_device[_ul_dev_num].en_device_state)

#define DMAC_ALG_SET_DEV_PRIV(_ul_chip_num, _ul_dev_num, _pst_mac_board, _p_alg_stru)     \
        MAC_DEV_ALG_PRIV(&_pst_mac_board->ast_chip[_ul_chip_num].ast_device[_ul_dev_num]) = (oal_void *)_p_alg_stru

/* 控制面回调函数类型定义 */
typedef oal_uint32 (*p_alg_create_vap_notify_func)(mac_vap_stru *pst_vap);
typedef oal_uint32 (*p_alg_delete_vap_notify_func)(mac_vap_stru *pst_vap);
typedef oal_uint32 (*p_alg_cfg_channel_notify_func)(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
typedef oal_uint32 (*p_alg_cfg_start_connect_notify_func)(mac_vap_stru *pst_vap, oal_int c_rssi);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef oal_void (*p_alg_cfg_btcoex_state_notify_func)(mac_device_stru *pst_device, dmac_alg_bt_state_type_uint8 en_type);
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
typedef oal_uint32 (*p_alg_cfg_bandwidth_notify_func)(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type);
typedef oal_uint32 (*p_alg_cfg_user_bandwidth_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
typedef oal_uint32 (*p_alg_cfg_user_protocol_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
typedef oal_uint32 (*p_alg_add_assoc_user_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
typedef oal_uint32 (*p_alg_delete_assoc_user_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
#ifdef _PRE_WLAN_FEATURE_CCA_OPT
typedef oal_uint32 (*p_alg_cfg_cca_intf_mode_notify_func)(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80);
#endif
#ifdef  _PRE_WLAN_FEATURE_SMPS
typedef oal_uint32 (*p_alg_cfg_smps_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
#endif
typedef oal_uint32 (*p_alg_cfg_user_spatial_stream_notify_func)(mac_user_stru *pst_user);

/* 收发流程相关回调 */
typedef oal_uint32 (*p_alg_rx_notify_func)(mac_vap_stru *pst_vap,
                                               mac_user_stru *pst_user,
                                               oal_netbuf_stru *pst_buf,
                                               hal_rx_statistic_stru *pst_rx_stats);
typedef oal_uint32 (*p_alg_enqueue_tid_notify_func)(mac_vap_stru *pst_vap,
                                                    dmac_tid_stru *pst_tid,
                                                    oal_uint8 uc_mpdu_num);
typedef oal_uint32 (*p_alg_vap_up_notify_func)(mac_vap_stru *pst_vap);
typedef oal_uint32 (*p_alg_vap_down_notify_func)(mac_vap_stru *pst_vap);
typedef oal_uint32 (*p_alg_tx_notify_func)(mac_user_stru *pst_user,
                                               mac_tx_ctl_stru *pst_cb,
                                               hal_tx_txop_alg_stru *pst_txop_param);
typedef oal_uint32 (*p_alg_tx_complete_notify_func)(mac_user_stru *pst_user,
                                               oal_netbuf_stru *pst_buf,
                                               hal_tx_dscr_ctrl_one_param *pst_tx_dscr_param);
typedef oal_void   (*p_alg_probe_req_rx_notify_func)(dmac_vap_stru *pst_vap, oal_netbuf_stru *pst_net_buf);

#ifdef _PRE_WLAN_CHIP_TEST_ALG
typedef oal_uint32 (*p_alg_rx_event_notify_func)(oal_uint8 uc_vap_id,
                                                oal_netbuf_stru *pst_buf,
                                                dmac_rx_ctl_stru *pst_cb_ctrl);
#endif
/* 调度相关回调 */
typedef oal_uint32 (*p_alg_tx_schedule_func)(mac_device_stru *pst_device, oal_uint8 uc_ac_num, mac_tid_schedule_output_stru *pst_sch_output);
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
typedef oal_uint32 (*p_alg_tx_schedule_stat_event_notify_func)(oal_uint8 uc_device_id, oal_uint8 uc_vap_id, oal_uint8 (*ppuc_traffic_num)[ALG_TXRX_DATA_MAXNUM]);
#endif
typedef oal_uint32 (*p_alg_update_tid_notify_func)(dmac_tid_stru *pst_tid);
typedef oal_uint32 (*p_alg_downlink_flowctl_notify_func)(mac_vap_stru *pst_vap,
                                                                mac_user_stru *pst_user,
                                                                oal_netbuf_stru *pst_buf,
                                                                dmac_txrx_output_type_enum_uint8 *pen_output);

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
typedef oal_uint32 (*p_alg_flowctl_backp_notify_func)(mac_vap_stru *pst_vap, oal_uint16 us_total_mpdu_num, oal_uint16 *pus_total_mpdu_num);
#endif

/* 定时器回调 */
typedef oal_uint32 (*p_alg_timer_notify_func)(oal_void *p_args);

/* 事件回调 */
typedef oal_uint32 (*p_alg_host_crx_event_notify_func)(frw_event_stru *pst_event);

/*txbf/抗干扰处理接收管理帧回调*/
typedef oal_uint32  (*p_alg_rx_mgmt_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user, oal_netbuf_stru *pst_buf);

/*txbf处理接收控制帧回调*/
typedef oal_uint32  (*p_alg_txbf_rx_cntl_notify_func)(mac_vap_stru *pst_vap, mac_user_stru *pst_user, oal_netbuf_stru *pst_buf);

typedef oal_uint32 (*p_alg_config_func)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_argc, oal_int8 *pac_argv[]);

/* 单用户跟踪获取参数回调 */
#ifdef _PRE_DEBUG_MODE_USER_TRACK
typedef oal_uint32 (*p_alg_start_stat_rssi_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_get_rssi_func)(mac_user_stru *pst_mac_user, oal_int8 *pc_tx_rssi, oal_int8 *pc_rx_rssi);
typedef oal_uint32 (*p_alg_stop_stat_rssi_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_start_stat_rate_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_get_rate_func)(mac_user_stru *pst_mac_user, oal_uint32 *pul_tx_rate, oal_uint32 *pul_rx_rate);
typedef oal_uint32 (*p_alg_stop_stat_rate_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_start_stat_best_rate_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_get_best_rate_func)(mac_user_stru *pst_mac_user, dmac_best_rate_stat_info_stru *pst_best_rate_info);
typedef oal_uint32 (*p_alg_stop_stat_best_rate_func)(mac_user_stru *pst_mac_user);
#endif
typedef oal_uint32 (*p_alg_get_rate_by_table_func)(mac_user_stru *pst_mac_user, hal_rx_statistic_stru *pst_rx_stats, oal_uint32 *pul_rate_kbps);
typedef oal_uint32 (*p_alg_get_tx_best_rate_func)(mac_user_stru *pst_mac_user, wlan_wme_ac_type_enum_uint8 en_traffic_type, oal_uint32 *pul_rate_kbps);
typedef oal_uint32 (*p_alg_delete_ba_fail_notify_func)(mac_user_stru *pst_mac_user);
typedef oal_uint32 (*p_alg_dbac_pause_func)(mac_device_stru *pst_device);
typedef oal_bool_enum_uint8 (*p_alg_dbac_is_pause)(mac_device_stru *pst_device);

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
#ifdef _PRE_WLAN_FEATURE_DBAC
    DMAC_ALG_CONFIG_ID_DBAC,
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    DMAC_ALG_CONFIG_ID_SCH,
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    DMAC_ALG_CONFIG_ID_TRAFF_CTL,
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_CONFIG_ID_TXBF,
    DMAC_ALG_CONFIG_ID_TEST_MAIN,
    DMAC_ALG_CONFIG_ID_DBAC_TEST,
    DMAC_ALG_CONFIG_ID_AUTORATE_TEST,
    DMAC_ALG_CONFIG_ID_SMARTANT_TEST,
    DMAC_ALG_CONFIG_ID_RSSI_TEST,
    DMAC_ALG_CONFIG_ID_TPC_TEST,
    DMAC_ALG_CONFIG_ID_CCA_OPT_TEST,
//#error "error!!!"
#endif
    DMAC_ALG_CONFIG_ID_COMMON,
    DMAC_ALG_CONFIG_ID_ERROR,   /* 占位，不要删除*/

    DMAC_ALG_CONFIG_ID_BUTT
}dmac_alg_config_id_enum;
typedef oal_uint8    dmac_alg_config_id_enum_uint8;

typedef struct
{
    oal_int8                       *puc_alg_name;
    dmac_alg_config_id_enum_uint8   en_alg_config_id;
    oal_uint8                       auc_resv[3];
}dmac_alg_config_table_stru;

/* 定义事件HOST_CRX事件的子类型，HMAC接收到算法APP的CRX事件后，使用这些子类型 */
typedef enum
{
    DMAC_ALG_HOST_CRX_SUBTYPE_CFG,

    DMAC_ALG_HOST_CRX_SUBTYPE_BUTT
}dmac_alg_host_crx_subtype_enum;
typedef oal_uint8 dmac_alg_host_crx_subtype_enum_uint8;

/* HOST CRX EVENT回调函数枚举ID */
typedef enum
{
    DMAC_ALG_HOST_CRX_EVENT_NOTIFY_ACS,

    ALG_HOST_CRX_EVENT_NOTIFY_BUTT,
}dmac_alg_host_crx_event_notify_enum;
typedef oal_uint8 dmac_alg_host_crx_event_notify_enum_uint8;

/* 算法ID，唯一识别某个算法，ID=2的整数值 */
typedef enum
{
    DMAC_ALG_ID_SCHEDULE     = 0x00000001,
    DMAC_ALG_ID_AUTORATE     = 0x00000002,
    DMAC_ALG_ID_SMARTANT     = 0x00000004,
    DMAC_ALG_ID_ACS          = 0x00000008,
    DMAC_ALG_ID_TPC          = 0x00000010,
    DMAC_ALG_ID_TRAFFIC_CTL  = 0x00000020,
    DMAC_ALG_ID_TXBF         = 0x00000040,
    DMAC_ALG_ID_DBAC         = 0x00000080,
    DMAC_ALG_ID_ANTI_INTF    = 0x00000100,
    DMAC_ALG_ID_MWO_DET      = 0x00000200,
    DMAC_ALG_ID_EDCA_OPT     = 0x00000400,
    DMAC_ALG_ID_CCA_OPT      = 0x00000800,
#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_ID_TPC_TEST     = 0x20000000,
    DMAC_ALG_ID_RSSI_TEST    = 0x40000000,
#endif

    DMAC_ALG_ID_BUTT
}dmac_alg_id_enum;
typedef oal_uint32 dmac_alg_id_enum_uint32;

/* 数据结构类型枚举定义 */
typedef enum
{
    DMAC_ALG_DEVICE_STRU_ID_SCHEDULE,
    DMAC_ALG_DEVICE_STRU_ID_AUTORATE,
    DMAC_ALG_DEVICE_STRU_ID_SMARTANT,
    DMAC_ALG_DEVICE_STRU_ID_DBAC,
    DMAC_ALG_DEVICE_STRU_ID_TXBF,
    DMAC_ALG_DEVICE_STRU_ID_ANTI_INTF,
    DMAC_ALG_DEVICE_STRU_ID_MWO_DET,
    DMAC_ALG_DEVICE_STRU_ID_TPC,        //TPC结构体
    DMAC_ALG_DEVICE_STRU_ID_EDCA_OPT,
    DMAC_ALG_DEVICE_STRU_ID_CCA_OPT,

    DMAC_ALG_DEVICE_STRU_ID_BUTT
}dmac_alg_device_stru_id_enum;
typedef oal_uint8 dmac_alg_device_stru_id_enum_uint8;

typedef enum
{
    DMAC_ALG_VAP_STRU_ID_SCHEDULE,
    DMAC_ALG_VAP_STRU_ID_TPC,
    DMAC_ALG_VAP_STRU_ID_MWO_DET,

    DMAC_ALG_VAP_STRU_ID_BUTT
}dmac_alg_vap_stru_id_enum;
typedef oal_uint8 dmac_alg_vap_stru_id_enum_uint8;

typedef enum
{
    DMAC_ALG_USER_STRU_ID_SCHEDULE,
    DMAC_ALG_USER_STRU_ID_AUTORATE,
    DMAC_ALG_USER_STRU_ID_SMARTANT,
    DMAC_ALG_USER_STRU_ID_TXBF,
    DMAC_ALG_USER_STRU_ID_ANTI_INTF,
    DMAC_ALG_USER_STRU_ID_MWO_DET,
	DMAC_ALG_USER_STRU_ID_TPC_POW,      //功率信息结构体
    DMAC_ALG_USER_STRU_ID_TPC_DIS,      //距离信息结构体
    DMAC_ALG_USER_STRU_ID_TPC_RSSI,     //rssi信息结构体
    DMAC_ALG_USER_STRU_ID_CCA_OPT,

    DMAC_ALG_USER_STRU_ID_BUTT
}dmac_alg_user_stru_id_enum;
typedef oal_uint8 dmac_alg_user_stru_id_enum_uint8;

typedef enum
{
    DMAC_ALG_TID_STRU_ID_SCHEDULE,
    DMAC_ALG_TID_STRU_ID_DBAC,

    DMAC_ALG_TID_STRU_ID_BUTT
}dmac_alg_tid_stru_id_enum;
typedef oal_uint8 dmac_alg_tid_stru_id_enum_uint8;

typedef enum
{
    DMAC_ALG_ENQUEUE_TID_START  = 0,
    DMAC_ALG_ENQUEUE_TID_DBAC   = DMAC_ALG_ENQUEUE_TID_START,

    DMAC_ALG_ENQUEUE_TID_BUTT
}dmac_alg_enqueue_tid_notify_enum;
typedef oal_uint8 dmac_alg_enqueue_tid_notify_enum_uint8;

typedef enum
{
    DMAC_ALG_VAP_UP_DBAC,
    DMAC_ALG_VAP_UP_TPC,

    DMAC_ALG_VAP_UP_BUTT
}dmac_alg_vap_up_notify_enum;
typedef oal_uint8 dmac_alg_vap_up_notify_enum_uint8;

typedef enum
{
    DMAC_ALG_VAP_DOWN_DBAC,

    DMAC_ALG_VAP_DOWN_BUTT
}dmac_alg_vap_down_notify_enum;
typedef oal_uint8 dmac_alg_vap_down_notify_enum_uint8;

typedef enum
{
    DMAC_ALG_PROBE_REQ_RX_DBAC,

    DMAC_ALG_PROBE_REQ_RX_BUTT
}dmac_alg_probe_req_rx_notify_enum;
typedef oal_uint8 dmac_alg_probe_req_rx_notify_enum_uint8;

typedef enum
{
    DMAC_ALG_OFDM_NULL_FRM_SUCC_TH = 6,
    DMAC_ALG_NULL_FRM_INC_CNT = 8,
    DMAC_ALG_NULL_FRM_INIT_CNT = 10,

    DMAC_ALG_NULL_FRM_BUTT
}dmac_alg_ar_null_frm_notify_enum;
typedef oal_uint8 dmac_alg_ar_null_frm_notify_enum_uint8;

/* 发送流程上获取发送参数的回调函数 */
typedef enum
{
    DMAC_ALG_TX_START = 0,

#ifdef _PRE_WLAN_FEATURE_TXBF
    DMAC_ALG_TX_TXBF_SOUNDING = DMAC_ALG_TX_START,
    DMAC_ALG_TX_AUTORATE,
#else
    DMAC_ALG_TX_AUTORATE = DMAC_ALG_TX_START,
#endif
    DMAC_ALG_TX_TPC,
    DMAC_ALG_TX_TXBF,
    DMAC_ALG_TX_DBAC,
    DMAC_ALG_TX_SMARTANT,
    DMAC_ALG_TX_EDCA_OPT,
#ifdef _PRE_WLAN_CHIP_TEST
    DMAC_ALG_TEST_TX_TXBF,
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_TEST_TX_AUTORATE,
    DMAC_ALG_TEST_TX_SMARTANT,
    DMAC_ALG_TEST_TX_TPC,
#endif
    DMAC_ALG_TX_NOTIFY_BUTT
}dmac_alg_tx_notify_enum;
typedef oal_uint8 dmac_alg_tx_notify_enum_uint8;

/* 发送完成流程上获取统计信息的回调函数 */
typedef enum
{
    DMAC_ALG_TX_COMPLETE_START = 0,
    DMAC_ALG_TX_COMPLETE_AUTORATE = DMAC_ALG_TX_COMPLETE_START,
    DMAC_ALG_TX_COMPLETE_SCHEDULE,
    DMAC_ALG_TX_COMPLETE_TPC,
    DMAC_ALG_TX_COMPLETE_TXBF,
    DMAC_ALG_TX_COMPLETE_DBAC,
    DMAC_ALG_TX_COMPLETE_ACS,
    DMAC_ALG_TX_COMPLETE_SMARTANT,
    DMAC_ALG_TX_COMPLETE_ANTI_INTF,
    DMAC_ALG_TX_COMPLETE_EDCA_OPT,
    DMAC_ALG_TX_COMPLETE_CCA_OPT,

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_TX_COMPLETE_DBAC_TEST,
    DMAC_ALG_TX_COMPLETE_TXBF_TEST,
    DMAC_ALG_TEST_TX_COMPLETE_AUTORATE,
    DMAC_ALG_TEST_TX_COMPLETE_SMARTANT,
    DMAC_ALG_TEST_TX_COMPLETE_TPC,
#endif

    DMAC_ALG_TX_COMPLETE_COMMON,

    DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT
}dmac_alg_tx_complete_notify_enum;
typedef oal_uint8 dmac_alg_tx_complete_notify_enum_uint8;

/* 接收流程上的回调函数 */
typedef enum
{
    DMAC_ALG_RX_START = 0,
    DMAC_ALG_RX_AUTORATE = DMAC_ALG_RX_START,
    DMAC_ALG_RX_DBAC,
    DMAC_ALG_RX_ACS,
    DMAC_ALG_RX_ANTI_INTF,
    DMAC_ALG_RX_TPC,
#ifdef _PRE_WLAN_FEATURE_TXBF
    DMAC_ALG_RX_TXBF,
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_RX_TXBF_TEST,
    DMAC_ALG_RX_DBAC_TEST,
    DMAC_ALG_RX_RSSI_TEST,
#endif

    DMAC_ALG_RX_NOTIFY_BUTT
}dmac_alg_rx_notify_enum;
typedef oal_uint8 dmac_alg_rx_notify_enum_uint8;

/* 添加关联用户回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_ADD_USER_NOTIFY_SCHEDULE,
    DMAC_ALG_ADD_USER_NOTIFY_AUTROATE,
    DMAC_ALG_ADD_USER_NOTIFY_SMARTANT,
    DMAC_ALG_ADD_USER_NOTIFY_DBAC,
    DMAC_ALG_ADD_USER_NOTIFY_ACS,
    DMAC_ALG_ADD_USER_NOTIFY_ANTI_INTF,
#ifdef _PRE_WLAN_FEATURE_TXBF
    DMAC_ALG_ADD_USER_NOTIFY_TXBF,
#endif
    DMAC_ALG_ADD_USER_NOTIFY_TPC,

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_ALG_TEST_USER_NOTIFY_SMARTANT,
#endif
    DMAC_ALG_ADD_USER_NOTIFY_CCA_OPT,

    DMAC_ALG_ADD_USER_NOTIFY_BUTT,
}dmac_alg_add_user_notify_enum;
typedef oal_uint8 dmac_alg_add_user_notify_enum_uint8;

/* 删除关联用户回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_DEL_USER_NOTIFY_SCHEDULE,
    DMAC_ALG_DEL_USER_NOTIFY_AUTORATE,
    DMAC_ALG_DEL_USER_NOTIFY_SMARTANT,
    DMAC_ALG_DEL_USER_NOTIFY_DBAC,
    DMAC_ALG_DEL_USER_NOTIFY_ACS,
    DMAC_ALG_DEL_USER_NOTIFY_ANTI_INTF,
#ifdef _PRE_WLAN_FEATURE_TXBF
    DMAC_ALG_DEL_USER_NOTIFY_TXBF,
#endif
    DMAC_ALG_DEL_USER_NOTIFY_TPC,
    DMAC_ALG_DEL_USER_NOTIFY_CCA_OPT,

    DMAC_ALG_DEL_USER_NOTIFY_BUTT,
}dmac_alg_del_user_notify_enum;
typedef oal_uint8 dmac_alg_del_user_notify_enum_uint8;

/* 创建VAP回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_ADD_VAP_NOTIFY_SCHEDULE,
    DMAC_ALG_ADD_VAP_NOTIFY_AUTORATE,
    DMAC_ALG_ADD_VAP_NOTIFY_ACS,
    DMAC_ALG_ADD_VAP_NOTIFY_TPC,
//    DMAC_ALG_ADD_VAP_NOTIFY_MWO_DET,

    DMAC_ALG_ADD_VAP_NOTIFY_BUTT,
}dmac_alg_add_vap_notify_enum;
typedef oal_uint8 dmac_alg_add_vap_notify_enum_uint8;

/* 删除VAP回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_DEL_VAP_NOTIFY_SCHEDULE,
    DMAC_ALG_DEL_VAP_NOTIFY_ACS,
    DMAC_ALG_DEL_VAP_NOTIFY_TPC,
//    DMAC_ALG_DEL_VAP_NOTIFY_MWO_DET,

    DMAC_ALG_DEL_VAP_NOTIFY_BUTT,
}dmac_alg_del_vap_notify_enum;
typedef oal_uint8 dmac_alg_del_vap_notify_enum_uint8;

/* 设置信道回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_CFG_CHANNEL_NOTIFY_ACS,
    DMAC_ALG_CFG_CHANNEL_NOTIFY_TPC,
    DMAC_ALG_CFG_CHANNEL_NOTIFY_TXBF,

    DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT,
}dmac_alg_cfg_channel_notify_enum;
typedef oal_uint8 dmac_alg_cfg_channel_notify_enum_uint8;

/* 设置信道回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_CFG_START_CONNECT_NOTIFY_TPC,

    DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT,
}dmac_alg_cfg_start_connect_notify_enum;
typedef oal_uint8 dmac_alg_cfg_start_connect_notify_enum_uint8;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
/* 设置信道回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_AUTO,

    DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_BUTT,
}dmac_alg_cfg_btcoex_state_notify_enum;
typedef oal_uint8 dmac_alg_cfg_btcoex_state_notify_enum_uint8;
#endif

/* 设置带宽回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_CFG_BANDWIDTH_NOTIFY_ACS,

    DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT,
}dmac_alg_cfg_bandwidth_notify_enum;
typedef oal_uint8 dmac_alg_cfg_bandwidth_notify_enum_uint8;

typedef enum
{
    DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_AUTORATE,
    DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_TPC,
    DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_TXBF,

    DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT,
}dmac_alg_cfg_user_bandwidth_notify_enum;
typedef oal_uint8 dmac_alg_cfg_user_bandwidth_notify_enum_uint8;

/* 改变协议模式回调函数枚举定义 */
typedef enum
{
    DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_TPC,
    DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_TXBF,

    DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT,
}dmac_alg_cfg_user_protocol_notify_enum;
typedef oal_uint8 dmac_alg_cfg_user_protocol_notify_enum_uint8;

/*CCA检测到的干扰模式改变时回调函数枚举定义*/
/*CCA mode*/
typedef enum
{
    DMAC_ALG_CCA_OPT_NO_INTF        = 0,    /* 无干扰 */
    DMAC_ALG_CCA_OPT_MEDIUM_INTF    = 1,    /* 中等强度干扰 */
    DMAC_ALG_CCA_OPT_STRONG_INTF    = 2,    /* 强干扰 */
    DMAC_ALG_CCA_OPT_INTF_MODE_BUTT
}dmac_alg_cca_opt_intf_enum;
typedef oal_uint8 dmac_alg_cca_opt_intf_mode_enum_uint8;

typedef enum
{
    DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_TPC,
    DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_DMAC_MODULE,

    DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT,
}dmac_alg_cfg_cca_intf_mode_notify_enum;
typedef oal_uint8 dmac_alg_cfg_cca_intf_mode_notify_enum_uint8;

#ifdef  _PRE_WLAN_FEATURE_SMPS
typedef enum
{
    DMAC_ALG_CFG_SMPS_NOTIFY_TXBF,

    DMAC_ALG_CFG_SMPS_NOTIFY_BUTT,
}dmac_alg_cfg_smps_notify_enum;
typedef oal_uint8 dmac_alg_cfg_smps_notify_enum_uint8;
#endif

typedef enum
{
    DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_AUTORATE,

    DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT,
}dmac_alg_cfg_user_spatial_stream_notify_enum;
typedef oal_uint8 dmac_alg_cfg_user_spatial_stream_notify_enum_uint8;

/* 接收管理帧的回调函数 */
typedef enum
{
    DMAC_ALG_RX_MGMT_TXBF,
    DMAC_ALG_RX_MGMT_ANTI_INTF,
    DMAC_ALG_RX_MGMT_EDCA_OPT,
    DMAC_ALG_RX_MGMT_TPC,

    DMAC_ALG_RX_MGMT_NOTIFY_BUTT
}dmac_alg_rx_mgmt_notify_enum;
typedef oal_uint8 dmac_alg_rx_mgmt_notify_enum_uint8;

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/* 发送/接收数据类型 */
typedef enum
{
    ALG_TX_TCP_DATA = 0,    /* 发送TCP data */
    ALG_RX_TCP_DATA = 1,    /* 接收TCP data */
    ALG_TX_UDP_DATA = 2,    /* 发送UDP data */
    ALG_RX_UDP_DATA = 3,    /* 接收UDP data */

    ALG_TXRX_DATA_BUTT = 4,
}alg_txrx_data_type_enum;
typedef oal_uint8 alg_txrx_data_type_enum_uint8;
#endif


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern  dmac_alg_config_table_stru g_ast_dmac_alg_config_table[];

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* 算法定时器结构体 */
typedef frw_timeout_stru  dmac_alg_timer_stru;


/* 挂在各个device上的数据结构 */
typedef struct
{
    oal_void       *p_alg_info[DMAC_ALG_DEVICE_STRU_ID_BUTT];
}dmac_alg_device_stru;

/* 挂在各个vap上的数据结构 */
typedef struct
{
   oal_void        *p_alg_info[DMAC_ALG_VAP_STRU_ID_BUTT];
}dmac_alg_vap_stru;

/* 挂在各个user上的数据结构 */
typedef struct
{
   oal_void        *p_alg_info[DMAC_ALG_USER_STRU_ID_BUTT];
}dmac_alg_user_stru;

/* 挂在各个tid上的数据结构 */
typedef struct
{
   oal_void        *p_alg_info[DMAC_ALG_TID_STRU_ID_BUTT];
}dmac_alg_tid_stru;

/* 用户距离状态 */
typedef enum
{
    DMAC_ALG_TPC_NEAR_DISTANCE       = 0,
    DMAC_ALG_TPC_NORMAL_DISTANCE     = 1,
    DMAC_ALG_TPC_FAR_DISTANCE        = 2,

    DMAC_ALG_TPC_BUTT_DISTANCE
}dmac_alg_tpc_user_distance_enum;
typedef oal_uint8 dmac_alg_tpc_user_distance_enum_uint8;


/* 用户距离通知信息结构体 */
typedef struct
{
    dmac_alg_tpc_user_distance_enum_uint8  en_old_distance;    /* 变化前的距离状态信息 */
    dmac_alg_tpc_user_distance_enum_uint8  en_new_distance;    /* 变化后的距离状态信息 */
}dmac_alg_distance_notify_info_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/***************** 子算法注册注销接口 ************** */
extern oal_uint32  dmac_alg_register(dmac_alg_id_enum_uint32 en_alg_id);
extern oal_uint32  dmac_alg_unregister(dmac_alg_id_enum_uint32 en_alg_id);
extern oal_uint32  dmac_alg_is_registered(dmac_alg_id_enum_uint32 en_alg_id, oal_bool_enum_uint8 *pen_is_registered);

/***************** 定时器接口 *********************** */
extern oal_uint32  dmac_alg_register_timer(oal_uint32  ul_file_id,
                                          oal_uint32  ul_line_num,
                                          oam_module_id_enum_uint16 en_module_id,
                                          oal_uint32 ul_core_id,
                                          p_alg_timer_notify_func p_timer_notify_func,
                                          oal_void *p_arg,
                                          oal_bool_enum_uint8 en_is_periodic,
                                          dmac_alg_timer_stru **ppst_timer);
extern oal_uint32  dmac_alg_unregister_timer(dmac_alg_timer_stru *pst_timer);
extern oal_uint32  dmac_alg_start_timer(dmac_alg_timer_stru *pst_timer, oal_uint16 us_timeout_ms);
extern oal_uint32  dmac_alg_stop_timer(dmac_alg_timer_stru *pst_timer);


/***************** 回调函数注册接口 ******************* */
extern oal_uint32  dmac_alg_register_tx_notify_func(dmac_alg_tx_notify_enum_uint8    en_notify_sub_type,
                                                            p_alg_tx_notify_func             p_func);
extern oal_uint32  dmac_alg_register_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8    en_notify_sub_type,
                                                                          p_alg_tx_complete_notify_func             p_func);
extern oal_uint32  dmac_alg_register_rx_notify_func(dmac_alg_rx_notify_enum_uint8    en_notify_sub_type,
                                                            p_alg_rx_notify_func             p_func);
extern oal_uint32  dmac_alg_register_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8  en_notify_sub_type,
                                                                 p_alg_create_vap_notify_func      p_func);
extern oal_uint32  dmac_alg_register_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8  en_notify_sub_type,
                                                                 p_alg_delete_vap_notify_func      p_func);
extern oal_uint32  dmac_alg_register_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8  en_notify_sub_type,
                                                                   p_alg_cfg_channel_notify_func      p_func);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_alg_register_cfg_start_connect_notify_func(dmac_alg_cfg_start_connect_notify_enum_uint8  en_notify_sub_type,
                                                                   p_alg_cfg_start_connect_notify_func     p_func);
extern oal_uint32  dmac_alg_unregister_cfg_start_connect_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type);
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
extern oal_uint32  dmac_alg_register_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8  en_notify_sub_type,
                                                                      p_alg_cfg_bandwidth_notify_func      p_func);
extern oal_uint32  dmac_alg_register_cfg_user_bandwidth_notify_func(
                dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type,
                p_alg_cfg_user_bandwidth_notify_func          p_func);
extern oal_uint32  dmac_alg_register_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8  en_notify_sub_type,
                                                                      p_alg_cfg_user_protocol_notify_func      p_func);
extern oal_uint32  dmac_alg_register_cfg_user_spatial_stream_notify_func(
                dmac_alg_cfg_user_spatial_stream_notify_enum_uint8  en_notify_sub_type,
                p_alg_cfg_user_spatial_stream_notify_func          p_func);
extern oal_uint32  dmac_alg_register_add_user_notify_func(dmac_alg_add_user_notify_enum_uint8 en_notify_sub_type,
                                                                        p_alg_add_assoc_user_notify_func     p_func);
extern oal_uint32  dmac_alg_register_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8 en_notify_sub_type,
                                                                           p_alg_delete_assoc_user_notify_func     p_func);
extern oal_uint32  dmac_alg_register_tx_schedule_func(p_alg_tx_schedule_func  p_func);

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
extern oal_uint32  dmac_alg_register_tx_schedule_stat_event_notify_func(p_alg_tx_schedule_stat_event_notify_func  p_func);
extern oal_uint32  dmac_alg_unregister_tx_schedule_stat_event_notify_func(oal_void);
#endif

extern oal_uint32  dmac_alg_register_tid_update_notify_func(p_alg_update_tid_notify_func p_func);
extern oal_uint32  dmac_alg_register_downlink_flowctl_notify_func(p_alg_downlink_flowctl_notify_func p_func);
#ifdef _PRE_WLAN_FEATURE_DBAC
extern oal_uint32  dmac_alg_register_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_enqueue_tid_notify_func p_func);
extern oal_uint32  dmac_alg_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *));
#endif

extern oal_uint32  dmac_alg_register_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_up_notify_func p_func);
extern oal_uint32  dmac_alg_register_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_down_notify_func p_func);
#ifdef _PRE_WLAN_CHIP_TEST_ALG
extern oal_void    dmac_alg_register_rx_event_notify(p_alg_rx_event_notify_func p_func);
#endif

extern oal_uint32  dmac_alg_register_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type, p_alg_rx_mgmt_notify_func p_func);
extern oal_uint32  dmac_alg_register_txbf_rx_cntl_notify_func(p_alg_txbf_rx_cntl_notify_func p_func);


/***************** 回调函数注销接口 ******************* */
extern oal_uint32  dmac_alg_unregister_tx_notify_func(dmac_alg_tx_notify_enum_uint8    en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8    en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_rx_notify_func(dmac_alg_rx_notify_enum_uint8    en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_cfg_user_spatial_stream_notify_func(dmac_alg_cfg_user_spatial_stream_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_cfg_user_bandwidth_notify_func(dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_add_user_notify_func(dmac_alg_add_user_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_tx_schedule_func(oal_void);
extern oal_uint32  dmac_alg_unregister_tid_update_notify_func(oal_void);
extern oal_uint32  dmac_alg_unregister_downlink_flowctl_notify_func(oal_void);
extern oal_uint32  dmac_alg_register_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type, p_alg_config_func p_func);
extern oal_uint32  dmac_alg_unregister_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type);
#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_uint32  dmac_alg_register_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type,
                                                               p_alg_cfg_cca_intf_mode_notify_func        p_func);
extern oal_uint32  dmac_alg_unregister_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_cfg_cca_intf_mode_notify(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80);
#endif
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint32  dmac_alg_register_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type,
                                                   p_alg_cfg_smps_notify_func        p_func);
extern oal_uint32  dmac_alg_unregister_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type);
extern oal_uint32  dmac_alg_cfg_smps_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
#endif

#ifdef _PRE_WLAN_FEATURE_DBAC
extern oal_uint32  dmac_alg_unregister_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type);
extern oal_uint32  dmac_alg_register_probe_req_rx_notify_func(dmac_alg_probe_req_rx_notify_enum_uint8 en_notify_sub_type,
                                                          p_alg_probe_req_rx_notify_func p_func);
#endif
extern oal_uint32  dmac_alg_unregister_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type);

#ifdef _PRE_WLAN_CHIP_TEST_ALG
extern oal_void   dmac_alg_unregister_rx_event_notify(oal_void);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
extern oal_uint32  dmac_alg_register_flowctl_backp_notify_func(p_alg_flowctl_backp_notify_func p_func);
extern oal_uint32  dmac_alg_unregister_flowctl_backp_notify_func(oal_void);
extern oal_uint32  dmac_alg_flowctl_backp(mac_vap_stru *pst_mac_vap, oal_uint16 us_assoc_id, oal_uint8 uc_tidno, oal_uint8 uc_is_stop);
#endif

extern oal_uint32  dmac_alg_unregister_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type);
extern oal_uint32  dmac_alg_unregister_txbf_rx_cntl_notify_func(oal_void);


/***************** 注册数据结构接口 ******************** */
extern oal_uint32  dmac_alg_register_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                   dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type,
                                                   oal_void                        *p_dev_stru);
extern oal_uint32  dmac_alg_register_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                                dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                                oal_void                     *p_vap_stru);
extern oal_uint32  dmac_alg_register_user_priv_stru(mac_user_stru               *pst_user,
                                                dmac_alg_user_stru_id_enum_uint8  en_user_stru_type,
                                                oal_void                     *p_user_stru);
extern oal_uint32  dmac_alg_register_tid_priv_stru(mac_user_stru              *pst_user,
                                             oal_uint8                    uc_tid_no,
                                             dmac_alg_tid_stru_id_enum_uint8   en_tid_stru_type,
                                             oal_void                    *p_tid_stru);

/***************** 注销数据结构接口 ****************** */
extern oal_uint32  dmac_alg_unregister_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                            dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type);
extern oal_uint32  dmac_alg_unregister_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                                        dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type);
extern oal_uint32  dmac_alg_unregister_user_priv_stru(mac_user_stru               *pst_user,
                                                         dmac_alg_user_stru_id_enum_uint8  en_user_stru_type);
extern oal_uint32  dmac_alg_unregister_tid_priv_stru(mac_user_stru              *pst_user,
                                                       oal_uint8                    uc_tid_no,
                                                       dmac_alg_tid_stru_id_enum_uint8   en_tid_stru_type);

/***************** 获取数据结构接口 ****************** */
extern oal_uint32  dmac_alg_get_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                             dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type,
                                             oal_void                        **pp_dev_stru);
extern oal_uint32  dmac_alg_get_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                         dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                         oal_void                     **pp_vap_stru);
extern oal_uint32  dmac_alg_get_user_priv_stru(mac_user_stru               *pst_user,
                                          dmac_alg_user_stru_id_enum_uint8   en_user_stru_type,
                                          oal_void                     **pp_user_stru);
extern oal_uint32  dmac_alg_get_tid_priv_stru(mac_user_stru               *pst_user,
                                       oal_uint8                    uc_tid_no,
                                       dmac_alg_tid_stru_id_enum_uint8   en_tid_stru_type,
                                       oal_void                    **pp_tid_stru);
extern oal_uint32   dmac_alg_get_hal_queue_ppdu_num(oal_uint16 us_assoc_id,
                                            oal_uint8 uc_ac_num,
                                            oal_uint8 *puc_ppdu_num);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32   dmac_alg_set_hal_queue_ppdu_num(oal_uint16 us_assoc_id,
                                            oal_uint8 uc_ac_num,
                                            oal_uint8 puc_ppdu_num);
#endif

/******************DMAC其他API接口*********************/
extern oal_bool_enum_uint8  dmac_vap_is_host(mac_vap_stru *pst_vap);
#if 0
extern oal_uint8  dmac_vap_get_default_ant(mac_vap_stru *pst_vap);
#endif
extern oal_uint32  dmac_user_get_tid_by_num(mac_user_stru *pst_mac_user, oal_uint8 uc_tid_num, dmac_tid_stru **ppst_tid_queue);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
extern oal_uint32  dmac_user_set_smartant_training_state(mac_user_stru *pst_user,
                                                                      dmac_user_smartant_training_enum_uint8 en_training_state);
#endif
extern oal_uint32  dmac_user_get_smartant_training_state(mac_user_stru *pst_user,
                                                                      dmac_user_smartant_training_enum_uint8 *en_training_state);
extern oal_uint32  dmac_user_get_smartant_normal_rate_stats(
                       mac_user_stru                   *pst_mac_user,
                       dmac_tx_normal_rate_stats_stru  **ppst_rate_stats_info);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
extern oal_uint32  dmac_user_set_smartant_normal_rate_stats(
                       mac_user_stru *pst_mac_user,
                       dmac_tx_normal_rate_stats_stru *pst_rate_stats_info);
#endif
#if 0
extern oal_uint32  dmac_user_get_txchain_mask(mac_user_stru *pst_user,
                                                          wlan_nss_enum_uint8 en_nss,
                                                          oal_uint8 *puc_chainmask);
extern oal_uint32  dmac_user_set_txchain_mask(mac_user_stru *pst_user,
                                                         wlan_nss_enum_uint8 en_nss,
                                                         oal_uint8 puc_chainmask);
#endif
extern oal_bool_enum_uint8  dmac_user_get_vip_flag(mac_user_stru  *pst_user);
extern oal_bool_enum_uint8  dmac_user_get_ps_mode(mac_user_stru *pst_user);
extern oal_uint32  dmac_user_set_vip_flag(
                mac_user_stru               *pst_user,
                oal_bool_enum_uint8          en_vip_flag);
extern oal_uint32  dmac_tid_get_util_ratio(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint8 *puc_ratio);
extern oal_uint32  dmac_tid_get_mpdu_by_index(
                                                          dmac_tid_stru *pst_tid_queue,
                                                          oal_uint16 us_mpdu_index,
                                                          oal_netbuf_stru **ppst_netbuf_stru);
extern oal_uint32  dmac_tid_get_min_max_mpdu_length(
                                        mac_user_stru *pst_mac_user,
                                        oal_uint8 uc_tid_num,
                                        oal_uint16      us_head_mpdu_num,
                                        oal_uint16     *pus_min_mpdu_len,
                                        oal_uint16     *pus_max_mpdu_len);
extern oal_uint32  dmac_tid_delete_mpdu_tail(dmac_tid_stru *pst_tid_queue, oal_uint16 us_mpdu_num);
extern oal_uint32  dmac_tid_delete_mpdu_head(dmac_tid_stru *pst_tid_queue, oal_uint16 us_mpdu_num);
extern oal_uint32  dmac_tid_get_normal_rate_stats(
                mac_user_stru      *pst_mac_user,
                oal_uint8           uc_tid_id,
                dmac_tx_normal_rate_stats_stru **ppst_rate_stats_info);
extern oal_uint32  dmac_tid_set_normal_rate_stats(
                mac_user_stru      *pst_mac_user,
                oal_uint8           uc_tid_id,
                dmac_tx_normal_rate_stats_stru *pst_rate_stats_info);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
extern oal_uint32 dmac_tx_training_data(mac_user_stru *pst_user, oal_uint8 uc_tid_num, oal_netbuf_stru *pst_netbuf, oal_uint16 us_msdu_len);
#endif
//#if ALG_SCHEUDLE_EDCA_FEATURE
extern oal_uint32  dmac_alg_set_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info);
//#endif

extern oal_uint32  dmac_alg_get_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info);

extern oal_uint32  dmac_alg_set_qap_msdu_lifetime(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                oal_uint32                  ul_msdu_lifetime);

#ifdef _PRE_WLAN_FEATURE_SMARTANT
extern oal_uint32  dmac_alg_create_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_dmac_user, oal_uint8 uc_tid);
#endif
extern oal_uint32  dmac_alg_del_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_tid);

extern oal_uint32  dmac_tx_complete_schedule(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ac_num);
extern hal_to_dmac_vap_stru *dmac_alg_get_hal_to_dmac_vap(oal_uint8 uc_mac_vap_id);

extern oal_uint32  dmac_mgmt_switch_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_channel, oal_uint8 en_clear_fifo);
extern oal_void    dmac_timestamp_get(oal_time_us_stru *pst_usec);

extern oal_uint32  dmac_alg_cfg_user_protocol_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user);

extern oal_uint32  dmac_alg_cfg_user_bandwidth_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_alg_syn_info(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_voice_aggr(mac_vap_stru *pst_mac_vap);
#endif
#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  dmac_alg_register_start_stat_rssi_notify(p_alg_start_stat_rssi_func   p_func);
extern oal_uint32  dmac_alg_unregister_start_stat_rssi_notify(oal_void);
extern oal_uint32  dmac_alg_register_get_rssi_notify(p_alg_get_rssi_func p_func);
extern oal_uint32  dmac_alg_unregister_get_rssi_notify(oal_void);
extern oal_uint32  dmac_alg_register_stop_stat_rssi_notify(p_alg_stop_stat_rssi_func   p_func);
extern oal_uint32  dmac_alg_unregister_stop_stat_rssi_notify(oal_void);
extern oal_uint32  dmac_alg_register_start_stat_rate_notify(p_alg_start_stat_rate_func   p_func);
extern oal_uint32  dmac_alg_unregister_start_stat_rate_notify(oal_void);
extern oal_uint32  dmac_alg_register_get_rate_notify(p_alg_get_rate_func p_func);
extern oal_uint32  dmac_alg_unregister_get_rate_notify(oal_void);
extern oal_uint32  dmac_alg_register_stop_stat_rate_notify(p_alg_stop_stat_rate_func   p_func);
extern oal_uint32  dmac_alg_unregister_stop_stat_rate_notify(oal_void);
extern oal_uint32  dmac_alg_stop_stat_rssi(mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_stop_stat_rate(mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_get_rssi(mac_user_stru *pst_mac_user,
                                  oal_int8      *pc_tx_rssi,
                                  oal_int8      *pc_rx_rssi);
extern oal_uint32  dmac_alg_get_rate(mac_user_stru *pst_mac_user,
                                  oal_uint32     *pul_tx_rate,
                                  oal_uint32     *pul_rx_rate);
extern oal_uint32  dmac_alg_start_stat_rssi(mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_start_stat_rate(mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_register_start_stat_best_rate_notify(
                                        p_alg_start_stat_best_rate_func   p_func);
extern oal_uint32  dmac_alg_unregister_start_stat_best_rate_notify(oal_void);
extern oal_uint32  dmac_alg_register_get_best_rate_notify(p_alg_get_best_rate_func p_func);
extern oal_uint32  dmac_alg_unregister_get_best_rate_notify(oal_void);
extern oal_uint32  dmac_alg_register_stop_stat_best_rate_notify(
                                        p_alg_stop_stat_best_rate_func   p_func);
extern oal_uint32  dmac_alg_unregister_stop_stat_best_rate_notify(oal_void);
extern oal_uint32  dmac_alg_start_stat_best_rate(mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_alg_get_best_rate(
                                  mac_user_stru   *pst_mac_user,
                                  dmac_best_rate_stat_info_stru *pst_best_rate_info);
extern oal_uint32  dmac_alg_stop_stat_best_rate(mac_user_stru *pst_mac_user);

#endif

extern oal_uint32  dmac_alg_register_get_rate_by_table_notify(p_alg_get_rate_by_table_func p_func);
extern oal_uint32  dmac_alg_unregister_get_rate_by_table_notify(oal_void);
extern oal_uint32  dmac_alg_get_rate_by_table(mac_user_stru *pst_mac_user,
                                  hal_rx_statistic_stru *pst_rx_stats,
                                  oal_uint32 *pul_rate_kbps);

extern oal_uint32  dmac_alg_register_get_tx_best_rate_notify(p_alg_get_tx_best_rate_func p_func);
extern oal_uint32  dmac_alg_unregister_get_tx_best_rate_notify(oal_void);
extern oal_uint32  dmac_alg_get_tx_best_rate(mac_user_stru *pst_mac_user,
                                  wlan_wme_ac_type_enum_uint8 en_traffic_type,
                                  oal_uint32 *pul_rate_kbps);

extern oal_uint32  dmac_alg_register_delete_ba_fail_notify(p_alg_delete_ba_fail_notify_func p_func);
extern oal_uint32  dmac_alg_unregister_delete_ba_fail_notify(oal_void);
extern oal_uint32  dmac_alg_delete_ba_fail_notify(mac_user_stru *pst_mac_user);


#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/* 抗干扰:EDCA优化统计信息事件回调函数 */
typedef oal_uint32  (*p_alg_edca_stat_event_notify_func)(oal_uint8 uc_device_id, oal_uint8 uc_vap_id, oal_uint8 (*ppuc_traffic_num)[ALG_TXRX_DATA_BUTT]);
extern oal_uint32  dmac_alg_register_edca_stat_event_notify(p_alg_edca_stat_event_notify_func p_func);
extern oal_uint32  dmac_alg_unregister_edca_stat_event_notify(oal_void);
#endif

extern oal_uint32  dmac_alg_register_dbac_pause_notify(
                p_alg_dbac_pause_func   p_func);
extern oal_uint32  dmac_alg_register_dbac_resume_notify(
                p_alg_dbac_pause_func   p_func);
extern oal_uint32  dmac_alg_register_dbac_is_pause(
                p_alg_dbac_is_pause   p_func);
extern oal_uint32  dmac_alg_dbac_pause(mac_device_stru *pst_mac_device);
extern oal_uint32  dmac_alg_dbac_resume(mac_device_stru *pst_mac_device);
extern oal_bool_enum_uint8  dmac_alg_dbac_is_pause(mac_device_stru *pst_mac_device);

extern oal_uint32 dmac_alg_distance_notify_hook(mac_user_stru *pst_user, dmac_alg_distance_notify_info_stru *pst_distance_info);
extern oal_uint32 dmac_alg_co_intf_notify_hook(mac_device_stru *pst_device, oal_bool_enum_uint8 en_intf_state_cur, oal_bool_enum_uint8 en_intf_state_old);
extern oal_uint32 dmac_alg_cca_intf_notify_hook(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80);
#if _PRE_TEST_MODE == _PRE_TEST_MODE_UT
#define ALG_ASSERT_RET(_expr, _ret) \
    do  \
    {   \
        if(!(_expr))    \
        {               \
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "ALG_ASSERT_RET fail"); \
            return _ret;    \
        }                   \
    }while(0)
#else
#define ALG_ASSERT_RET(_expr, _ret)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_alg_if.h */
