/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_acs.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年12月10日
  最近修改   :
  功能描述   : dmac_acs.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月10日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ACS_H__
#define __DMAC_ACS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_SUPPORT_ACS

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "mac_user.h"
#include "mac_device.h"
#include "dmac_tid.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ACS_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_ACS_REPLY_HDR_LEN                      12

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    DMAC_ACS_SCAN_TYPE_BACKGROUND = 0,  /* 背景扫描，每个信道扫描时间较短 */
    DMAC_ACS_SCAN_TYPE_FOREGROUND,      /* 初始扫描，每个信道扫描时间较长 */
    DMAC_ACS_SCAN_TYPE_BUTT
}dmac_acs_scan_type_enum;
typedef oal_uint8 dmac_acs_scan_type_enum_uint8;

typedef enum
{
    DMAC_ACS_CMD_SET_BEST_CHANNEL = 0,
    DMAC_ACS_CMD_GET_VAP_PERF_INFO,
    DMAC_ACS_CMD_GET_AVAIL_CHANNEL,
    DMAC_ACS_CMD_GET_NET_INFO,
    DMAC_ACS_CMD_DO_OFFCHAN_CAC,
    DMAC_ACS_CMD_DO_SCAN,
    DMAC_ACS_CMD_DO_CSA,
    DMAC_ACS_CMD_DO_DURATION_STATS,
    DMAC_ACS_CMD_BUTT,  // used as DMAC_ACS_RANK in app

    /* 以下为DMAC向APP主动发送的消息 */
    DMAC_ACS_NOTIFY_CREATE_VAP,
    DMAC_ACS_NOTIFY_DELETE_VAP,
    DMAC_ACS_NOTIFY_ADD_USER,
    DMAC_ACS_NOTIFY_DEL_USER,
    DMAC_ACS_NOTIFY_CFG_CHANNEL,
    DMAC_ACS_NOTIFY_CFG_BANDWIDTH,
    DMAC_ACS_NOTIFY_RADAR_DETECTED,
    DMAC_ACS_NOTIFY_BUTT
}mac_acs_cmd_enum;
typedef oal_uint8 dmac_acs_cmd_enum_uint8;
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

/* ACS中最优信道的描述结构 */
typedef struct
{
    oal_bool_enum_uint8               en_valid      : 1;
    wlan_channel_bandwidth_enum_uint8 en_bandwidth  : 7;
    oal_uint8                         uc_channel_number;
}dmac_acs_channel_stru;

/* VAP创建/删除主动发送信息结构，对应命令                   */
/* DMAC_ACS_NOTIFY_CREATE_VAP 和 DMAC_ACS_NOTIFY_DELETE_VAP */
typedef struct
{
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];
    wlan_vap_mode_enum_uint8            en_vap_mode; /* vap模式  */
    oal_uint8                           uc_vap_id;

    wlan_protocol_enum_uint8            en_protocol;                                    /* 工作的协议模式 */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;     /* VAP创建时的初始带宽 */
    oal_uint8                           uc_channel;       /* VAP的信道号 */
    wlan_bw_cap_enum_uint8              en_bandwidth_cap;
}dmac_acs_vap_info_stru;

/* USER关联/去关联主动发送信息结构，对应命令            */
/* DMAC_ACS_NOTIFY_ADD_USER 和 DMAC_ACS_NOTIFY_DEL_USER */
typedef struct
{
    oal_uint8                           auc_user_mac_addr[WLAN_MAC_ADDR_LEN];   /* user对应的MAC地址 */
    oal_uint16                          us_assoc_id;

    oal_uint8                           uc_assoc_vap_id;
    wlan_bw_cap_enum_uint8              en_cur_bandwidth      : 4;
    wlan_protocol_enum_uint8            en_cur_protocol_mode  : 4; /* USER关联时协商的初始带宽 */
    oal_uint8                           bit_bandwidth_cap:4,  /* USER的最大带宽能力 */
                                        bit_spectrum_mgmt:1,  /* 是否支持频谱管理(CSA) */
                                        bit_resv:3;
    oal_int8                            c_rx_rssi;         /* RSSI */
}dmac_acs_user_info_stru;

/* DMAC_ACS_CMD_GET_NET_INFO */
typedef struct
{
    oal_uint8   uc_vap_cnt;
    oal_uint8   auc_resv[1];
    oal_uint16  us_user_cnt;
    // vap_info1  vap_info2 ..
    // user_info1 user_info2...
}dmac_acs_net_info_stru;

/* 配置信道/带宽主动发送信息结构，对应命令                      */
/* DMAC_ACS_NOTIFY_CFG_CHANNEL 和 DMAC_ACS_NOTIFY_CFG_BANDWIDTH */
typedef struct
{
    dmac_acs_vap_info_stru      st_vap_info;
}dmac_acs_vap_channel_info_stru;

/* ACS内部维护的USER信息结构 */
typedef struct
{
    oal_dlist_head_stru           st_dlist_head;

    oal_uint8       auc_user_addr[WLAN_MAC_ADDR_LEN];
    oal_uint16      us_assoc_id;

    oal_int8        c_rx_rssi;
    oal_uint8       auc_resv[3];

    oal_uint32      ul_tx_duration_us;
    oal_uint32      ul_rx_duration_us;
    oal_uint32      ul_tx_pkt_cnt;
    oal_uint32      ul_tx_pkt_bytes;
    oal_uint32      ul_rx_pkt_cnt;
    oal_uint32      ul_rx_pkt_bytes;
}dmac_acs_user_internal_stru;

/* ACS内部维护的VAP信息结构 */
typedef struct
{
    oal_dlist_head_stru     st_dlist_head; /* VAP dlist 表头 */
    oal_uint8               uc_vap_id;
    oal_uint8               uc_resv;
    oal_uint16              us_sta_num;

    /* VAP最优备选信道结构 2G & 5G */
    dmac_acs_channel_stru   ast_best_channel_per_band[WLAN_BAND_BUTT];
    /* TBTT 切换计数 */
    oal_uint8               auc_tbtt_cnt[WLAN_BAND_BUTT];

    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];
    oal_bool_enum_uint8     en_dfs_wait_for_csa_sent;
    oal_bool_enum_uint8     en_in_csa_phase;

    oal_dlist_head_stru     st_user_dlist_head;
}dmac_acs_vap_internal_stru;

/* 发现雷达主动发送信息结构，对应命令 */
/* DMAC_ACS_NOTIFY_RADAR_DETECTED */
typedef struct
{
    oal_uint8                           uc_channel_number;
    wlan_channel_bandwidth_enum_uint8   en_bandwidth_mode; /* 检测到雷达时的工作带宽 */
    oal_uint8                           uc_radar_bw;
    oal_uint8                           uc_freq_offset;
}dmac_acs_radar_info_stru;

/* 可用信道信息结构，对应命令 */
/* DMAC_ACS_CMD_GET_AVAIL_CHANNEL */
typedef struct
{
    oal_uint8 uc_avail_channel_num;
    oal_uint8 uc_device_id;
    oal_uint8 uc_chip_id;
    oal_uint8 uc_2g_channel_cnt;
}dmac_acs_avail_channel_reply_stru;
//dmac_acs_channel_stru ast_channels[WLAN_MAX_CHANNEL_NUM]; /* 2G + 5G total channels */

typedef struct acs_vap_perf_stat
{
    oal_uint8                     auc_user_addr[WLAN_MAC_ADDR_LEN];
    oal_uint16                    us_assoc_id;
    oal_int8                      c_rx_rssi;
    oal_uint8                     auc_resv[1];
    oal_uint8                     uc_tx_duration_rate;
    oal_uint8                     uc_rx_duration_rate;

    oal_uint32                    ul_tx_pkt_cnt;
    oal_uint32                    ul_tx_pkt_bytes;
    oal_uint32                    ul_rx_pkt_cnt;
    oal_uint32                    ul_rx_pkt_bytes;
}acs_vap_perf_user_stat_stru;

/* AP的性能参数回复结构， 对应命令 */
/* DMAC_ACS_CMD_GET_VAP_PERF_INFO */
typedef struct
{
    oal_uint8       uc_vap_id;
    oal_uint8       uc_csa_sta_num;
    oal_uint16      us_sta_nums;
    oal_uint32      ul_mpdu_num;
    oal_uint16      aus_max_delay[WLAN_TID_MAX_NUM]; // ms

    oal_uint16      us_mac_stats_time_ms;
    oal_uint8       uc_mac_free_time_rate;
    oal_uint8       c_phy_free_power;
}dmac_acs_vap_perf_reply_stru;
// acs_vap_perf_user_stat_stru  ast_user_stat[N];

/* 来自APP的CSA命令结构 */
typedef struct
{
    oal_uint8           uc_band;
    oal_uint8           uc_bandwidth;
    oal_uint8           uc_channel_num;
    oal_uint8           uc_tbtt_cnt;
    oal_uint8           uc_vap_id;
    oal_bool_enum_uint8 en_global;
    oal_uint8           auc_resv[2];
}dmac_acs_csa_stru;
typedef oal_void (*dmac_acs_cmd_handler_fn)(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd);

// 信道更新和sta带宽改变二者不会同时使用
typedef struct
{
    oal_uint8           uc_2g_cnt;      // 2g 信道个数
    oal_uint8           uc_5g_cnt;      // 5g 信道个数
    oal_uint8           uc_bw_chg_sta_cnt;  // 带宽发送改变的sta个数
    oal_uint8           uc_chip_id  : 4;
    oal_uint8           uc_device_id : 4;
}dmac_acs_selected_info_stru;
typedef struct
{
    oal_uint16  us_assoc_id;
    oal_uint8   uc_assoc_vap_id;
    wlan_channel_bandwidth_enum_uint8 en_new_bandwidth;
}dmac_acs_sta_bw_info_stru;
// dmac_acs_channel_stru * uc_2g_cnt
// dmac_acs_channel_stru * uc_5g_cnt
// dmac_acs_sta_bw_info_stru * uc_bw_chg_sta_cn

typedef struct
{
    oal_uint8               uc_chip_id;
    oal_uint8               uc_device_id;
    oal_bool_enum_uint8     en_in_scan;
    oal_bool_enum_uint8     en_in_stats;

    /* ACS最优信道结构 2G & 5G */
    dmac_acs_channel_stru             ast_best_channel_per_band[WLAN_BAND_BUTT];

    /* 信道信息 相关数据 */
    oal_uint8                         uc_csa_vap_cnt;        /* 有VAP处于CSA状态 */
    oal_uint8                         auc_resv[3];

    /* ACS 运行统计数据 */
    oal_uint32                        ul_mac_stats_time_us;
    oal_uint32                        ul_mac_free_time_us;
    oal_uint32                        ul_phy_free_power;

    /* ACS 内部维护VAP链表 */
    oal_dlist_head_stru               st_vap_dlist_head;

    /* ACS 命令处理列表 */
    dmac_acs_cmd_handler_fn           apfn_cmd_handler[DMAC_ACS_CMD_BUTT];
}dmac_acs_stru;

/* 该表由ALG_AUTORATE定义，但DMAC不能直接引用，这里重新复制一个 */
typedef struct
{
    oal_bool_enum_uint8                 en_short_gi;
    wlan_nss_enum_uint8                 en_nss;
    hal_channel_assemble_enum_uint8     en_bandwidth;
    union
    {
        wlan_vht_mcs_enum_uint8             en_vht_mcs;
        wlan_ht_mcs_enum_uint8              en_ht_mcs;
        wlan_legacy_rate_value_enum_uint8   en_legacy_rate;
    }un_nss_rate;
    oal_uint32                          ul_rate_kbps;
    oal_uint32                          ul_theory_rate;
    oal_uint32                          ul_aggr_bytes_limit;
    wlan_protocol_enum_uint8            en_protocol;
    oal_uint8                           uc_20m_rate_code;
    oal_uint8                           uc_40m_rate_code;
    oal_uint8                           uc_80m_rate_code;
}dmac_acs_rate_table_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_acs_init(mac_device_stru *pst_device);
extern oal_uint32  dmac_acs_exit(mac_device_stru *pst_device);
extern oal_uint32  dmac_acs_recv_msg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  dmac_acs_radar_detected_handler(mac_device_stru *pst_mac_device, hal_radar_det_event_stru *pst_radar_det_info);
#endif
extern oal_void    dmac_acs_channel_meas_comp_handler(mac_device_stru *pst_mac_dev, hal_ch_statics_irq_event_stru *pst_mac_stats_result);
extern oal_uint32  dmac_acs_tx_update(mac_user_stru *pst_mac_user, oal_netbuf_stru *pst_buf, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one);
extern oal_uint32  dmac_acs_rx_update(mac_vap_stru *pst_mac_vap,
                        mac_user_stru                       *pst_mac_user,
                        oal_netbuf_stru                     *pst_buf,
                        hal_rx_statistic_stru               *pst_rx_stats);
extern oal_uint32  dmac_config_acs(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param);
extern oal_void    dmac_acs_report_support_chan(mac_vap_stru *pst_mac_vap);
#endif /* #ifdef _PRE_SUPPORT_ACS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_acs.h */
