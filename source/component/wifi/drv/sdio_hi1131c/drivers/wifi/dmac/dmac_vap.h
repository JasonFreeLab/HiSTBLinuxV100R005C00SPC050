/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_vap.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   : dmac_vap.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_VAP_H__
#define __DMAC_VAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "mac_vap.h"
#include "dmac_user.h"
#include "dmac_ext_if.h"
#include "dmac_ap_pm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_VAP_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_MAX_SW_RETRIES         10  /* 数据报文重传次数 */
#define DMAC_MGMT_MAX_SW_RETRIES    3   /* 管理报文重传次数 */
#define DMAC_MAX_AMPDU_LENGTH_PERFOMANCE_COUNT    32   /* 进行计数的最大的聚合长度*/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#define BTCOEX_LINKLOSS_OCCUPIED_NUMBER (8)
#endif
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

#define IS_OPEN_PMF_REG(_pst_dmac_vap)  (0 != ((_pst_dmac_vap)->ul_user_pmf_status))
#endif

#define DMAC_IS_LINKLOSS(_pst_dmac_vap) ((_pst_dmac_vap->st_linkloss_info.us_link_loss) > (_pst_dmac_vap->st_linkloss_info.us_linkloss_threshold))

#define DMAC_MAX_TX_SUCCESSIVE_FAIL_PRINT_THRESHOLD_BTCOEX    (40)   /* 连续发送失败的打印RF寄存器门限*/
#define DMAC_MAX_TX_SUCCESSIVE_FAIL_PRINT_THRESHOLD    (20)   /* 连续发送失败的打印RF寄存器门限*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* beacon帧索引枚举 */
typedef enum
{
    DMAC_VAP_BEACON_BUFFER1,
    DMAC_VAP_BEACON_BUFFER2,

    DMAC_VAP_BEACON_BUFFER_BUTT
}dmac_vap_beacon_buffer_enum;
/* 按照不同聚合长度分类的索引的枚举值*/
/*0:1~14 */
/*1:15~17 */
/*2:18~30 */
/*3:31~32 */
typedef enum
{
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_0,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_1,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_2,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_3,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT
}dmac_count_by_ampdu_length_enum;
/* 统计的AMPDU的门限值枚举值*/
typedef enum
{
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_1 = 1,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_14 = 14,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_15 = 15,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_17 = 17,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_18 = 18,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_30 = 30,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_31 = 31,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_32 = 32
}dmac_count_by_ampdu_length_level_enum;

typedef oal_uint8 dmac_vap_beacon_buffer_enum_uint8;
#ifdef _PRE_WLAN_DFT_STAT
#define   DMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)        ((_member) += (_cnt))
#define   DMAC_VAP_DFT_STATS_PKT_SET_ZERO(_member)        ((_member) = (0))
#else
#define   DMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)
#define   DMAC_VAP_DFT_STATS_PKT_SET_ZERO(_member)
#endif
#define   DMAC_VAP_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))


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
/* vap tx参数，从架构分析文档获得成员 */
typedef struct
{
    oal_uint16  us_rts_threshold;       /* rts阈值 */
    oal_uint8   uc_mcast_rate;          /* 广播速率 */
    oal_uint8   auc_resv[1];            /* 字节对齐 */
}dmac_vap_tx_param_stru;

#ifdef _PRE_WLAN_FEATURE_ROAM

#define ROAM_TRIGGER_COUNT_THRESHOLD           (5)
#define ROAM_TRIGGER_RSSI_NE80_DB              (-80)
#define ROAM_TRIGGER_RSSI_NE75_DB              (-75)
#define ROAM_TRIGGER_RSSI_NE70_DB              (-70)
#define ROAM_TRIGGER_INTERVAL_10S              (10 * 1000)
#define ROAM_TRIGGER_INTERVAL_15S              (15 * 1000)
#define ROAM_TRIGGER_INTERVAL_20S              (20 * 1000)
#define ROAM_WPA_CONNECT_INTERVAL_TIME         (5 * 1000)    /* 漫游与正常关联之间的时间间隔，WIFI+ 上层切换频繁 */

typedef struct
{
    oal_int8    c_trigger_2G;           /* 2G漫游触发门限   */
    oal_int8    c_trigger_5G;           /* 5G漫游触发门限   */
    oal_uint8   auc_recv[2];
    oal_uint32  ul_cnt;                 /* 漫游触发器计数       */
    oal_uint32  ul_time_stamp;          /* 漫游触发器时间戳     */
    oal_uint32  ul_ip_obtain_stamp;     /* 上层获取IP地址时间戳 */
    oal_uint32  ul_ip_addr_obtained;    /* IP地址是否已获取 */
}dmac_vap_roam_trigger_stru;
#endif //_PRE_WLAN_FEATURE_ROAM

/*修改此结构体需要同步通知SDT，否则上报无法解析*/
typedef struct
{
    oal_int32    ul_signal;

    oal_uint32   ul_drv_rx_pkts;     /* 驱动接收数据包数目 */
    oal_uint32   ul_hw_tx_pkts;      /* 发送完成中断上报发送成功的个数 */
    oal_uint32   ul_drv_rx_bytes;    /* 驱动接收字节数，不包括80211头尾 */
    oal_uint32   ul_hw_tx_bytes;     /* 发送完成中断上报发送成功字节数 */
    oal_uint32   ul_tx_retries;      /*发送重传次数*/
    oal_uint32   ul_rx_dropped_misc; /*接收失败次数*/
    oal_uint32   ul_tx_failed;     /* 发送失败次数，仅仅统计数据帧 */
//    oal_rate_info_stru st_txrate; /*vap当前速率*/

    oal_int16    s_free_power;  /*底噪*/
    /*维测需要增加较多的维测，使用维测预编译宏包着*/
#ifdef _PRE_WLAN_DFT_STAT
    /***************************************************************************
                                接收包统计
    ***************************************************************************/

    /* 接收流程遇到严重错误(描述符异常等)，释放所有MPDU的统计 */
    oal_uint32  ul_rx_ppdu_dropped;                             /* 硬件上报的vap_id错误，释放的MPDU个数 */

    /* 软件统计的接收到MPDU个数，正常情况下应该与MAC硬件统计值相同 */
    oal_uint32  ul_rx_mpdu_total_num;                           /* 接收流程上报到软件进行处理的MPDU总个数 */

    /* MPDU级别进行处理时发生错误释放MPDU个数统计 */
    oal_uint32  ul_rx_ta_check_dropped;                         /* 检查发送端地址异常，释放一个MPDU */
    oal_uint32  ul_rx_key_search_fail_dropped;                  /*  */
    oal_uint32  ul_rx_tkip_mic_fail_dropped;                    /* 接收描述符status为 tkip mic fail释放MPDU */
    oal_uint32  ul_rx_replay_fail_dropped;                      /* 重放攻击，释放一个MPDU */
    oal_uint32  ul_rx_security_check_fail_dropped;              /* 加密检测失败*/
    oal_uint32  ul_rx_alg_process_dropped;                      /* 算法处理返回失败 */
    oal_uint32  ul_rx_null_frame_dropped;                       /* 接收到空帧释放(之前节能特性已经对其进行处理) */
    oal_uint32  ul_rx_abnormal_dropped;                         /* 其它异常情况释放MPDU */
    oal_uint32  ul_rx_mgmt_mpdu_num_cnt;                         /* 接收到的管理帧和控制帧统计*/
    oal_uint32  ul_rx_mgmt_abnormal_dropped;                    /* 接收到管理帧出现异常，比如vap或者dev为空等 */

    /***************************************************************************
                                发送包统计
    ***************************************************************************/
    oal_uint32  ul_drv_tx_pkts;     /* 驱动发包数目，交给硬件的数目 */
    oal_uint32  ul_drv_tx_bytes;    /* 驱动发包字节数，不算80211头尾 */
    /* 发送流程发生异常导致释放的数据包统计，MSDU级别 */
    oal_uint32  ul_tx_abnormal_mpdu_dropped;                    /* 异常情况释放MPDU个数，指vap或者user为空等异常 */
    /* 发送完成中发送成功与失败的数据包统计，MPDU级别 */
    oal_uint32  ul_tx_mpdu_succ_num;                            /* 发送MPDU总个数 */
    oal_uint32  ul_tx_mpdu_fail_num;                            /* 发送MPDU失败个数 */
    oal_uint32  ul_tx_ampdu_succ_num;                           /* 发送成功的AMPDU总个数 */
    oal_uint32  ul_tx_mpdu_in_ampdu;                            /* 属于AMPDU的MPDU发送总个数 */
    oal_uint32  ul_tx_ampdu_fail_num;                           /* 发送AMPDU失败个数 */
    oal_uint32  ul_tx_mpdu_fail_in_ampdu;                       /* 属于AMPDU的MPDU发送失败个数 */
    oal_uint32  aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT];/*针对不同聚合长度的帧统计发送的个数*/
    oal_uint32  ul_tx_cts_fail;                                  /*发送rts失败的统计*/
    oal_uint8  uc_tx_successive_mpdu_fail_num;                  /*连续发送失败的统计*/
    oal_uint8  uc_reserve[3];                                   /*保留字节*/
#endif
}dmac_vap_query_stats_stru;

typedef oal_uint8 dmac_linkloss_status_enum_uint8;


typedef struct
{
    oal_uint32                        ul_old_dot11BeaconPeriod;     /* 记录beacon周期，防止周期改变linkloss计数不准确 */
    oal_uint16                        us_linkloss_threshold;       /*  LinkLoss门限  */
    oal_uint16                        us_link_loss;                /*  LinkLoss计数器 */
    oal_bool_enum_uint8               en_old_bt_on;                 /* 记录bt开关的旧状态，检测bt开关是否有变化 */
    oal_bool_enum_uint8               en_old_dbac_runing;         /* 记录dbac开关的旧状态，检测dbac开关是否有变化 */
    oal_bool_enum_uint8               en_old_far_distance;        /* 记录远近场的旧状态，远场为true*/
    oal_uint8                         uc_linkloss_times;            /* 记录linkloss当前门限值相对于正常的倍数，反映beacon的周期倍数 */
}dmac_vap_linkloss_stru;


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
#define DMAC_MAX_IPV4_ENTRIES         8
#define DMAC_MAX_IPV6_ENTRIES         8
typedef struct
{
    oal_uint8                         auc_ip_addr[OAL_IPV4_ADDR_SIZE];
}dmac_vap_ipv4_addr_stru;

typedef struct
{
    oal_uint8                         auc_ip_addr[OAL_IPV6_ADDR_SIZE];
}dmac_vap_ipv6_addr_stru;

typedef struct
{
    dmac_vap_ipv4_addr_stru           ast_ipv4_entry[DMAC_MAX_IPV4_ENTRIES];
    dmac_vap_ipv6_addr_stru           ast_ipv6_entry[DMAC_MAX_IPV6_ENTRIES];
}dmac_vap_ip_entries_stru;
#endif

/* dmac vap */
typedef struct dmac_vap_tag
{
    mac_vap_stru                     st_vap_base_info;                                  /* 基本VAP信息 */

    oal_uint32                       ul_active_id_bitmap;                               /* 活跃user的bitmap */

    oal_netbuf_stru                 *pauc_beacon_buffer[DMAC_VAP_BEACON_BUFFER_BUTT];   /* VAP下挂两个beacon帧 */
    oal_uint8                        uc_beacon_idx;                                     /* 当前放入硬件beacon帧索引值 */
    oal_uint8                        uc_tim_offset_in_beacon;
    oal_uint16                       us_beacon_len;                                     /* beacon帧的长度 */

    hal_to_dmac_vap_stru            *pst_hal_vap;                                       /* hal vap结构 */
    hal_to_dmac_device_stru         *pst_hal_device;                                    /* hal device结构体以免二次获取 */

    dmac_vap_linkloss_stru           st_linkloss_info;                                  /* linkloss机制相关信息 */
    oal_bool_enum_uint8              en_is_host_vap;                                    /* TRUE:主VAP，FALSE:从VAP */
    oal_uint8                        uc_default_ant_bitmap;                             /* 默认天线组合bitmap, 可以填写到描述符中 */

    oal_uint8                        uc_sw_retry_limit;
    oal_uint8                        en_multi_user_multi_ac_flag;			    /* 多用户多优先级时是否使能拥塞控制*/

    oal_traffic_type_enum_uint8      uc_traffic_type;                           /* 业务类型，是否有多用户多优先级 */

    oal_uint8                        uc_sta_pm_open_by_host;                /* sta 低功耗状态: HOST侧是否打开了低功耗 */
    oal_uint8                        uc_cfg_pm_mode;                            /* 手动挡保存的低功耗模式 */
    oal_uint8                        uc_sta_pm_close_status;                    /* sta 低功耗状态, 包含多个模块的低功耗控制信息 */

    /* 重传次数上限 */
    oal_uint8                        uc_vap_tx_chain;                                   /* 默认使用的发送通道，单播数据帧仅初始化使用，业务中有TXCS算法填写，其他数据管理帧均按初始化值填写 */
    oal_uint16                       us_del_timeout;                                    /* 多长时间超时删除ba会话 如果是0则不删除 */
    oal_uint8                        bit_bw_cmd:1;                                      /* 是否使能配置数据带宽的命令 0:No  1:Yes */
    oal_uint8                        bit_beacon_timeout_times:7;                           /* sta等待beacon超时计数 */
    hal_tx_txop_alg_stru             st_tx_alg;                                         /* 单播数据帧发送参数 */

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    hal_tx_txop_alg_stru             st_tx_alg_vht;                                     /* VHT单播数据帧发送参数 */
    hal_tx_txop_alg_stru             st_tx_alg_ht;                                      /* HT单播数据帧发送参数 */
    hal_tx_txop_alg_stru             st_tx_alg_11ag;                                    /* 11a/g单播数据帧发送参数 */
    hal_tx_txop_alg_stru             st_tx_alg_11b;                                     /* 11b单播数据帧发送参数 */

    union
    {
        oal_uint8                    uc_mode_param_valid;                               /* 是否有针对特定模式的单播数据帧参数配置生效(0=无, 大于0=有) */
        struct{
            oal_uint8                bit_vht_param_vaild  : 1;                          /* VHT单播数据帧参数配置是否生效(0=不生效, 1=生效) */
            oal_uint8                bit_ht_param_vaild   : 1;                          /* HT单播数据帧参数配置是否生效(0=不生效, 1=生效) */
            oal_uint8                bit_11ag_param_vaild : 1;                          /* 11a/g单播数据帧参数配置是否生效(0=不生效, 1=生效) */
            oal_uint8                bit_11b_param_vaild  : 1;                          /* 11b单播数据帧参数配置是否生效(0=不生效, 1=生效) */
            oal_uint8                bit_reserve          : 4;
        }st_spec_mode;
    }un_mode_valid;
    oal_uint8                        auc_resv1[3];
#endif

    hal_tx_txop_alg_stru             st_tx_data_mcast;                                  /* 组播数据帧参数 */
    hal_tx_txop_alg_stru             st_tx_data_bcast;                                  /* 广播数据帧参数*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_ucast[WLAN_BAND_BUTT];                  /* 单播管理帧参数*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_bmcast[WLAN_BAND_BUTT];                 /* 组播、广播管理帧参数*/

    oal_void                        *p_alg_priv;                                        /* VAP级别算法私有结构体 */

    oal_uint8                       *puc_tim_bitmap;                                    /* 本地保存的tim_bitmap，AP模式有效 */
    oal_uint8                        uc_tim_bitmap_len;
    oal_uint8                        uc_ps_user_num;                                    /* 处于节能模式的用户的数目，AP模式有效 */
    oal_uint8                        uc_dtim_count;
    oal_uint8                        uc_uapsd_max_depth;                                /* U-APSD节能队列的最大深度*/
    oal_bool_enum_uint8              en_beacon_chain_active;                            /* beacon是否双路轮流发送, 0-关闭, 1-开启 */
    oal_bool_enum_uint8              en_dtim_ctrl_bit0;                                 /* 用于表示DTIM Control字段的比特0是否置1了 */
#ifdef _PRE_WLAN_CHIP_TEST
    oal_netbuf_stru                  *pst_wow_probe_resp;                                /* wow使能时,准备的probe response帧*/
    oal_netbuf_stru                  *pst_wow_null_data;                                 /* wow使能时,准备的null data帧,STA模式时采用*/
    oal_uint16                       us_wow_probe_resp_len;
    oal_uint8                        auc_resv2[1];
#else
    oal_uint8                        auc_resv3[11];
#endif

    oal_uint32                       ul_obss_scan_timer_remain;                  /* 02最大定时器超时65s, OBSS扫描定时器可能为几分钟，通过计数器来实现大定时器*/
    oal_uint8                        uc_obss_scan_timer_started;
    oal_uint8                        uc_bcn_tout_max_cnt;                      /* beacon连续收不到最大睡眠次数 */

#ifdef _PRE_WLAN_FEATURE_STA_PM
    oal_uint8                       uc_null_frm_ofdm_succ_cnt;
    oal_uint8                       uc_null_frm_cnt;
#else
    oal_uint8                       uac_resv5[2];
#endif  /* _PRE_WLAN_FEATURE_STA_PM */

    oal_bool_enum_uint8              en_bfee_actived;
    oal_bool_enum_uint8              en_bfer_actived;
    oal_bool_enum_uint8              en_mu_bfee_actived;
    oal_bool_enum_uint8              en_txstbc_actived;
    oal_uint8                        uc_ps_poll_pending;
    #ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    oal_uint8                        uc_beacon_miss_cnt;                /* beacon miss 计数 */
    #else
    oal_uint8                        uac_resv4[1];
    #endif
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    oal_uint32                       ul_user_pmf_status;                 /* 记录此vap下user pmf使能的情况，供控制硬件vap是否打开加解密开关 */
#endif

#if defined (_PRE_WLAN_FEATURE_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
    oal_void*                        pst_pm_handler;  //ap和sta共用，用时再强转成所需结构体
#endif
    /*统计信息+信息上报新增字段，修改这个字段，必须修改SDT才能解析正确*/
    dmac_vap_query_stats_stru        st_query_stats;
    /* 常发测试使用 */
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    oal_uint8                        uc_protocol_rate_dscr;                          /* 发送描述符中协议与速率位组合值，用于常发模式下更改帧长 */
    oal_uint8                        uc_bw_flag;                                     /* 发送描述符中40M标志 */
    oal_uint8                        uc_short_gi;                                    /* short gi是否使能 */
#endif
    hal_to_dmac_vap_stru            *pst_p2p0_hal_vap;                               /* p2p0 hal vap结构 */
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_cfg_p2p_noa_param_stru         st_p2p_noa_param;
    mac_cfg_p2p_ops_param_stru         st_p2p_ops_param;
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    oal_switch_enum_uint8             en_arp_offload_switch;         /* ARP offload的开关 */
    oal_uint8                         auc_resv9[3];
    dmac_vap_ip_entries_stru         *pst_ip_addr_info;              /* Host侧IPv4和IPv6地址 */
#endif

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    oal_uint16                          us_sync_tsf_value;
    oal_uint64                          ul_old_beacon_timestamp;
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
    dmac_vap_roam_trigger_stru          st_roam_trigger;
#endif  //_PRE_WLAN_FEATURE_ROAM

    oal_uint16                       us_ext_tbtt_offset;            /* 外部tbtt offset配置值*/
    oal_uint16                       us_in_tbtt_offset;             /* 内部tbtt offset配置值*/
    oal_uint16                       us_beacon_timeout;             /* beacon timeout配置值*/
    oal_uint8                        uc_psm_dtim_period;            /* 实际采用的dtim period*/
    oal_uint8                        uc_psm_auto_dtim_cnt;          /* 自动dtim的计数器 */
    oal_uint16                       us_psm_listen_interval;        /* 实际采用的listen_interval*/

    oal_bool_enum_uint8              en_non_erp_exist;              /* sta模式下，是否有non_erp station */
}dmac_vap_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_vap_get_bss_type
 功能描述  : 获取VAP类型，指针是否为空，调用者判断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VAP类型
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_vap_mode_enum_uint8  dmac_vap_get_bss_type(mac_vap_stru *pst_vap)
{
    return pst_vap->en_vap_mode;
}

/*****************************************************************************
 函 数 名  : dmac_vap_linkloss_zero
 功能描述  :  对linkloss计数器清0
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_vap_linkloss_clean(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
#endif

    pst_dmac_vap->st_linkloss_info.us_link_loss = 0;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_btcoex_wifi_status = &(pst_dmac_vap->pst_hal_device->st_btcoex_wifi_status);
    pst_btcoex_wifi_status->uc_linkloss_index = 1;
    pst_btcoex_wifi_status->uc_linkloss_occupied_times = 0;
#endif

}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_vap_init(
                       dmac_vap_stru              *pst_vap,
                       oal_uint8                   uc_chip_id,
                       oal_uint8                   uc_device_id,
                       oal_uint8                   uc_vap_id,
                       mac_cfg_add_vap_param_stru *pst_param);
extern oal_uint32  dmac_vap_init_tx_frame_params(dmac_vap_stru *pst_dmac_vap, oal_bool_enum_uint8  en_mgmt_rate_init_flag);
extern oal_uint32  dmac_vap_init_tx_ucast_data_frame(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_vap_sta_reset(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  mac_vap_pause_tx(mac_vap_stru *pst_vap);
extern oal_uint32  mac_vap_resume_tx(mac_vap_stru *pst_vap);
extern oal_void  dmac_vap_pause_tx(mac_vap_stru *pst_mac_vap);

extern oal_void  dmac_vap_pause_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_src_chl);
extern oal_void  dmac_vap_resume_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_dst_channel);
extern oal_void  dmac_vap_update_bi_from_hw(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_vap_init_tx_data_ucast(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_protocol_mode, oal_uint8 uc_legacy_rate);
extern oal_uint32  dmac_vap_is_in_p2p_listen(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_vap_linkloss_init(dmac_vap_stru *pst_dmac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
extern oal_void  dmac_one_packet_send_null_data(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_ps);
#endif /* */
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_vap.h */
