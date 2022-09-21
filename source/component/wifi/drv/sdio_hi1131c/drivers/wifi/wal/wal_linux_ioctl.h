/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_ioctl.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月10日
  最近修改   :
  功能描述   : wal_linux_ioctl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月10日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_LINUX_IOCTL_H__
#define __WAL_LINUX_IOCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_types.h"
#include "wlan_spec.h"
#include "mac_vap.h"
#include "hmac_ext_if.h"
#include "wal_ext_if.h"
#include "wal_config.h"
#include "dmac_alg_if.h"
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
#include "hmac_tcp_udp_keepalive.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_IOCTL_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WAL_HIPRIV_CMD_MAX_LEN       (WLAN_MEM_LOCAL_SIZE2 - 4)     /* 私有配置命令字符串最大长度，对应本地内存池一级大小 */

#define WAL_HIPRIV_CMD_NAME_MAX_LEN  80                             /* 字符串中每个单词的最大长度(原20) */

#define WAL_HIPRIV_PROC_ENTRY_NAME   "hipriv"

#define WAL_SIOCDEVPRIVATE              0x89F0  /* SIOCDEVPRIVATE */

#define WAL_HIPRIV_HT_MCS_MIN           0
#define WAL_HIPRIV_HT_MCS_MAX           32
#define WAL_HIPRIV_VHT_MCS_MIN          0
#define WAL_HIPRIV_VHT_MCS_MAX          9
#define WAL_HIPRIV_NSS_MIN              1
#define WAL_HIPRIV_NSS_MAX              4
#define WAL_HIPRIV_CH_NUM               4

#define WAL_HIPRIV_BOOL_NIM             0
#define WAL_HIPRIV_BOOL_MAX             1
#define WAL_HIPRIV_FREQ_SKEW_ARG_NUM    8

#define WAL_HIPRIV_MS_TO_S                   1000   /* ms和s之间倍数差 */
#define WAL_HIPRIV_KEEPALIVE_INTERVAL_MIN    5000   /* 受默认老化计数器出发时间所限制 */
#define WAL_HIPRIV_KEEPALIVE_INTERVAL_MAX    0xffff /* timer间隔时间限制所致(oal_uin16) */


/* IOCTL私有配置命令宏定义 */
#define WAL_IOCTL_PRIV_SETPARAM          (OAL_SIOCIWFIRSTPRIV + 0)
#define WAL_IOCTL_PRIV_GETPARAM          (OAL_SIOCIWFIRSTPRIV + 1)
#define WAL_IOCTL_PRIV_SET_WMM_PARAM     (OAL_SIOCIWFIRSTPRIV + 3)
#define WAL_IOCTL_PRIV_GET_WMM_PARAM     (OAL_SIOCIWFIRSTPRIV + 5)
#define WAL_IOCTL_PRIV_SET_COUNTRY       (OAL_SIOCIWFIRSTPRIV + 8)
#define WAL_IOCTL_PRIV_GET_COUNTRY       (OAL_SIOCIWFIRSTPRIV + 9)

#define WAL_IOCTL_PRIV_GET_MODE     (OAL_SIOCIWFIRSTPRIV + 17)      /* 读取模式 */
#define WAL_IOCTL_PRIV_SET_MODE     (OAL_SIOCIWFIRSTPRIV + 18)      /* 设置模式 包括协议 频段 带宽 */

#define WAL_IOCTL_PRIV_AP_GET_STA_LIST               (OAL_SIOCIWFIRSTPRIV + 21)
#define WAL_IOCTL_PRIV_AP_MAC_FLTR	                 (OAL_SIOCIWFIRSTPRIV + 22)
/* netd将此配置命令作为GET方式下发，get方式命令用奇数，set用偶数 */
#define WAL_IOCTL_PRIV_SET_AP_CFG                    (OAL_SIOCIWFIRSTPRIV + 23)
#define WAL_IOCTL_PRIV_AP_STA_DISASSOC		         (OAL_SIOCIWFIRSTPRIV + 24)

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define WAL_IOCTL_PRIV_GET_BLACKLIST        (OAL_SIOCIWFIRSTPRIV + 27)
#define WAL_IOCTL_PRIV_SET_ISOLATION        (OAL_SIOCIWFIRSTPRIV + 28)
#endif
#define WAL_IOCTL_PRIV_SUBCMD_MAX_LEN          20
typedef oal_uint32  (*wal_hipriv_cmd_func)(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    WAL_DSCR_PARAM_FREQ_BANDWIDTH_MODE = 0,      /* 频带模式 */
    WAL_DSCR_PARAM_PA_GAIN_LEVEL,      /* pa增益等级 */
    WAL_DSCR_PARAM_MICRO_TX_POWER_GAIN_LEVEL,
    WAL_DSCR_PARAM_SMART_ANTENNA_ENABLE,
    WAL_DSCR_PARAM_TXRTS_ANTENNA,
    WAL_DSCR_PARAM_RXCTRL_ANTENNA,
    WAL_DSCR_PARAM_CHANNAL_CODE,
    WAL_DSCR_PARAM_DATA_RATE0,
    WAL_DSCR_PARAM_DATA_RATE1,
    WAL_DSCR_PARAM_DATA_RATE2,
    WAL_DSCR_PARAM_DATA_RATE3,
    WAL_DSCR_PARAM_POWER,
    WAL_DSCR_PARAM_SHORTGI,
    WAL_DSCR_PARAM_PREAMBLE_MODE,
    WAL_DSCR_PARAM_RTSCTS,
    WAL_DSCR_PARAM_LSIGTXOP,
    WAL_DSCR_PARAM_SMOOTH,
    WAL_DSCR_PARAM_SOUNDING,
    WAL_DSCR_PARAM_TXBF,
    WAL_DSCR_PARAM_STBC,
    WAL_DSCR_PARAM_GET_ESS,
    WAL_DSCR_PARAM_DYN_BW,
    WAL_DSCR_PARAM_DYN_BW_EXIST,
    WAL_DSCR_PARAM_CH_BW_EXIST,

    WAL_DSCR_PARAM_BUTT
}wal_dscr_param_enum;
typedef oal_uint8 wal_dscr_param_enum_uint8;
#ifdef _PRE_WLAN_FEATURE_HILINK
typedef enum
{
  WAL_HILINK_OTHER_BSS_CAST_DATA_CLOSE,/*其他BSS网络组播数据帧上报关闭*/
  WAL_HILINK_OTHER_BSS_CAST_DATA_OPEN, /*其他BSS网络组播数据帧上报打开*/
  WAL_HILINK_MONITOR_CLOSE,            /*monitor模式关闭*/
  WAL_HILINK_MONITOR_OPEN,             /*monitor模式打开*/
  WAL_HILINK_BUTT
}wal_hilink_enum;
typedef oal_uint8 wal_hilink_enum_uint8;
#endif


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_iw_handler_def_stru g_st_iw_handler_def;
extern oal_net_device_ops_stru g_st_wal_net_dev_ops;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern oal_ethtool_ops_stru g_st_wal_ethtool_ops;
#endif
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
extern hmac_tcp_udp_conn_stru g_st_tcp_udp_conn;
#endif

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* 私有命令入口结构定义 */
typedef struct
{
    oal_int8           *pc_cmd_name;    /* 命令字符串 */
    wal_hipriv_cmd_func p_func;         /* 命令对应处理函数 */
}wal_hipriv_cmd_entry_stru;

/* 协议模式与字符串映射 */
typedef struct
{
    oal_int8                           *pc_name;        /* 模式名字符串 */
    wlan_protocol_enum_uint8            en_mode;        /* 协议模式 */
    wlan_channel_band_enum_uint8        en_band;        /* 频段 */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* 带宽 */
    oal_uint8                           auc_resv[1];
}wal_ioctl_mode_map_stru;

/* 算法参数配置结构体 */
typedef struct
{
    oal_int8                           *pc_name;        /* 配置命令字符串 */
    mac_alg_cfg_enum_uint8              en_alg_cfg;     /* 配置命令对应的枚举值 */
    oal_uint8                           auc_resv[3];    /* 字节对齐 */
}wal_ioctl_alg_cfg_stru;

/* 1102 使用wpa_supplicant 下发命令 */
typedef struct wal_android_wifi_priv_cmd {
    oal_int32    l_total_len;
    oal_int32    l_used_len;
    oal_uint8   *puc_buf;
}wal_android_wifi_priv_cmd_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  wal_hipriv_set_rate(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32  wal_hipriv_set_mcs(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32  wal_hipriv_set_mcsac(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32  wal_hipriv_vap_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);

extern oal_uint32  wal_hipriv_create_proc(oal_void *p_proc_arg);
extern oal_int32   wal_netdev_stop(oal_net_device_stru *pst_net_dev);
extern oal_int32   wal_netdev_open(oal_net_device_stru *pst_net_dev);
extern oal_uint32  wal_hipriv_del_vap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32  wal_hipriv_remove_proc(oal_void);
extern oal_uint32  wal_alloc_cfg_event(oal_net_device_stru *pst_net_dev,frw_event_mem_stru **ppst_event_mem,
                 oal_void*     pst_resp_addr, wal_msg_stru  **ppst_cfg_msg, oal_uint16 us_len);
extern oal_int32   wal_send_cfg_event(
                                   oal_net_device_stru      *pst_net_dev,
                                   wal_msg_type_enum_uint8   en_msg_type,
                                   oal_uint16                us_len,
                                   oal_uint8                *puc_param,
                                   oal_bool_enum_uint8       en_need_rsp,
                                   wal_msg_stru            **ppst_rsp_msg);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
extern oal_int32 wal_start_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32  wal_stop_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_init_wlan_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_deinit_wlan_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_init_wlan_netdev(oal_wiphy_stru *pst_wiphy, char *dev_name);
extern oal_int32  wal_setup_ap(oal_net_device_stru *pst_net_dev);
extern oal_int32  wal_host_dev_init(oal_net_device_stru *pst_net_dev);
#endif

#ifdef _PRE_WLAN_FEATURE_11D
extern oal_uint32  wal_regdomain_update_sta(oal_uint8 uc_vap_id);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_int32  wal_set_random_mac_to_mib(oal_net_device_stru *pst_net_dev);
#endif

wlan_p2p_mode_enum_uint8 wal_wireless_iftype_to_mac_p2p_mode(enum nl80211_iftype en_iftype);

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern oal_uint32 wal_hipriv_arp_offload_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
oal_uint32 wal_hipriv_show_arpoffload_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
#endif
extern oal_int32  wal_cfg_vap_h2d_event(oal_net_device_stru *pst_net_dev);
#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 wal_hipriv_roam_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_band(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_org(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_HOST)
/* 1131只采用ini文件方式,不采用dts或nv方式进行定制化参数配置 */
extern oal_void hwifi_config_init_nvram_main(oal_net_device_stru * pst_cfg_net_dev);
extern oal_uint32 hwifi_config_init_dts_main(oal_net_device_stru *pst_cfg_net_dev);
#endif
extern oal_int32 wal_set_custom_process_func(oal_void);
extern oal_uint32 wal_custom_cali(oal_void);
extern oal_void hwifi_config_init_force(oal_void);
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_ioctl.h */

