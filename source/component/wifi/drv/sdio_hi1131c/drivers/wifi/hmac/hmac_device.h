/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_device.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年1月31日
  最近修改   :
  功能描述   : hmac_device.c 的头文件，包括hmac device结构的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_DEVICE_H__
#define __HMAC_DEVICE_H__

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
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "mac_vap.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt_struc.h"
#include "oal_hcc_host_if.h"
#endif
#include "plat_pm.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DEVICE_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef _PRE_WLAN_TCP_OPT
#define HCC_TRANS_THREAD_POLICY         OAL_SCHED_FIFO

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
#define HCC_TRANS_THERAD_PRIORITY       (10)
#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#define HCC_TRANS_THERAD_PRIORITY       (10)
#endif

#define HCC_TRANS_THERAD_NICE           (-10)
#define HCC_TRANS_THERAD_STACKSIZE      (0x2000)

#define HCC_TRANS_RXDATA_THREAD_POLICY              OAL_SCHED_FIFO

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
#define HCC_TRANS_RXDATA_THERAD_PRIORITY            (97)
#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#define HCC_TRANS_RXDATA_THERAD_PRIORITY            (10)
#endif

#define HCC_TRANS_RXDATA_THERAD_NICE                (-10)
#define HCC_TRANS_RXDATA_THERAD_STACKSIZE           (0x2000)
#endif
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

/* 存储每个扫描到的bss信息 */
typedef struct
{
    oal_dlist_head_stru    st_dlist_head;	    /* 链表指针 */
    //oal_spin_lock_stru     st_lock;             /* 锁 */
    mac_bss_dscr_stru      st_bss_dscr_info;	/* bss描述信息，包括上报的管理帧 */
}hmac_scanned_bss_info;

/* 存储在hmac device下的扫描结果维护的结构体 */
typedef struct
{
    oal_spin_lock_stru  st_lock;
    oal_dlist_head_stru st_bss_list_head;
    oal_uint32          ul_bss_num;
}hmac_bss_mgmt_stru;


/* 扫描运行结果记录 */
typedef struct
{
    hmac_bss_mgmt_stru           st_bss_mgmt;                              /* 存储扫描BSS结果的管理结构 */
    mac_scan_chan_stats_stru     ast_chan_results[WLAN_MAX_CHANNEL_NUM];   /* 信道统计/测量结果 */
    oal_uint8                    uc_chan_numbers;                          /* 此次扫描总共需要扫描的信道个数 */
    oal_uint8                    uc_device_id : 4;
    oal_uint8                    uc_chip_id   : 4;
    oal_uint8                    uc_vap_id;                                /* 本次执行扫描的vap id */
    mac_scan_status_enum_uint8   en_scan_rsp_status;                       /* 本次扫描完成返回的状态码，是成功还是被拒绝 */

    oal_time_us_stru             st_scan_start_timestamp;                  /* 扫描维测使用 */
    mac_scan_cb_fn               p_fn_cb;                                  /* 此次扫描结束的回调函数指针 */

    oal_uint64                   ull_cookie;                               /* 保存P2P 监听结束上报的cookie 值 */
    mac_vap_state_enum_uint8     en_vap_last_state;                        /* 保存VAP进入扫描前的状态,AP/P2P GO模式下20/40M扫描专用 */
    oal_time_t_stru              st_scan_start_time;                       /* 扫描起始时间戳 */
}hmac_scan_record_stru;


/* 扫描相关相关控制信息 */
typedef struct
{
    /* scan 相关控制信息 */
    oal_bool_enum_uint8                    en_is_scanning;               /* host侧的扫描请求是否正在执行 */
    oal_bool_enum_uint8                    en_is_random_mac_addr_scan;   /* 是否为随机mac addr扫描，默认关闭(定制化宏开启下废弃) */
    oal_bool_enum_uint8                    en_complete;                   /* 内核普通扫描请求是否完成标志 */
    oal_bool_enum_uint8                    en_sched_scan_complete;        /* 调度扫描是否正在运行标记 */

    oal_cfg80211_scan_request_stru        *pst_request;               /* 内核下发的扫描请求结构体 */
    oal_cfg80211_sched_scan_request_stru  *pst_sched_scan_req;        /* 内核下发的调度扫描请求结构体 */

    oal_wait_queue_head_stru               st_wait_queue;
    oal_spin_lock_stru                     st_scan_request_spinlock;            /* 内核下发的request资源锁 */

    frw_timeout_stru                       st_scan_timeout;            /* 扫描模块host侧的超时保护所使用的定时器 */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    frw_timeout_stru                       st_init_scan_timeout;
#endif
    hmac_scan_record_stru                  st_scan_record_mgmt;        /* 扫描运行记录管理信息，包括扫描结果和发起扫描者的相关信息 */
    mac_channel_stru                       st_p2p_listen_channel;      /* 记录下发的listen channel，供上报给app用   */
}hmac_scan_stru;

typedef struct
{

    frw_timeout_stru    st_rx_dscr_opt_timer;     /* rx_dscr调整定时器 */
    oal_uint32          ul_rx_pkt_num;
    oal_uint32          ul_rx_pkt_opt_limit;
    oal_uint32          ul_rx_pkt_reset_limit;
    oal_bool_enum_uint8 en_dscr_opt_state;        /* TRUE表示已调整 */
    oal_bool_enum_uint8 en_dscr_opt_enable;
}hmac_rx_dscr_opt_stru;

/* hmac device结构体，记录只保存在hmac的device公共信息 */
typedef struct
{
    hmac_scan_stru                      st_scan_mgmt;                           /* 扫描管理结构体 */
#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    oal_uint8                           uc_desired_bss_num;                         /* 扫描到的期望的bss个数 */
    oal_uint8                           auc_resv[3];
    oal_uint8                           auc_desired_bss_idx[WLAN_MAX_SCAN_BSS_NUM]; /* 期望加入的bss在bss list中的位置 */
#endif
    oal_uint32                          ul_p2p_intf_status;
    oal_wait_queue_head_stru            st_netif_change_event;
    mac_device_stru                    *pst_device_base_info;                   /* 指向公共部分mac device */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    oal_bool_enum_uint8                 en_init_scan      : 1;
    oal_bool_enum_uint8                 en_start_via_priv : 1;
    oal_bool_enum_uint8                 en_in_init_scan   : 1;
    oal_bool_enum_uint8                 en_rescan_idle    : 1;
	oal_uint8							uc_resv_bit		  : 4;
    oal_uint8                           auc_resvx[3];
    mac_channel_stru                    ast_best_channel[WLAN_BAND_BUTT];
#endif
#if defined(_PRE_SUPPORT_ACS)
    frw_timeout_stru                    st_rescan_timer;
#endif
#ifdef _PRE_WLAN_TCP_OPT
    oal_bool_enum_uint8        sys_tcp_rx_ack_opt_enable;
    oal_bool_enum_uint8        sys_tcp_tx_ack_opt_enable;
    oal_bool_enum_uint8        en_need_notify;
#endif
    hmac_rx_dscr_opt_stru      st_rx_dscr_opt;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_to_hmac_btcoex_rx_delba_trigger_event_stru      st_dmac_to_hmac_btcoex_rx_delba;
#endif
#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
#ifdef CONFIG_HAS_EARLYSUSPEND
        struct early_suspend            early_suspend;      //early_suspend支持
#else
        struct notifier_block           pm_notifier;         //普通内核节能支持
#endif
        oal_spin_lock_stru              st_suspend_lock;
#endif
}hmac_device_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern oal_uint32  hmac_board_exit(mac_board_stru *pst_board);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 hmac_config_host_dev_init(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_host_dev_exit(mac_vap_stru *pst_mac_vap);
extern oal_uint32  hmac_board_init(mac_board_stru *pst_board);
#else
extern oal_uint32  hmac_board_init(oal_uint32 ul_chip_max_num, mac_chip_stru *pst_chip);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_device.h */
