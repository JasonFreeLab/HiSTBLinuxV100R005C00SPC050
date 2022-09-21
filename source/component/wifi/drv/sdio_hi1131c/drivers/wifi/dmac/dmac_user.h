/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_user.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   : dmac_user.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_USER_H__
#define __DMAC_USER_H__

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
#include "mac_user.h"
#include "dmac_tid.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_USER_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_UAPSD_STATS_INCR(_member)    ((_member)++)
#define DMAC_PSM_STATS_INCR(_member)      ((_member)++)
#else
#define DMAC_UAPSD_STATS_INCR(_member)
#define DMAC_PSM_STATS_INCR(_member)
#endif
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
#define   DMAC_USER_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))
#else
#define   DMAC_USER_STATS_PKT_INCR(_member, _cnt)
#endif


#define DMAC_COMPATIBILITY_PKT_NUM_LIMIT 2000

#define DMAC_GET_USER_SUPPORT_VHT(_pst_user)    \
        ((1 == (_pst_user)->st_vht_hdl.en_vht_capable)? OAL_TRUE : OAL_FALSE)

#define DMAC_GET_USER_SUPPORT_HT(_pst_user)    \
        ((1 == (_pst_user)->st_ht_hdl.en_ht_capable)? OAL_TRUE : OAL_FALSE)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    DMAC_USER_PS_STATE_ACTIVE   = 0,
    DMAC_USER_PS_STATE_DOZE     = 1,

    DMAC_USER_PS_STATE_BUTT
}dmac_user_ps_state_enum;
typedef oal_uint8 dmac_user_ps_state_enum_uint8;

typedef enum
{
    DMAC_USER_STATE_PS,
    DMAC_USER_STATE_ACTIVE,

    DMAC_USER_STATE_BUTT
}dmac_user_state_enum;
typedef oal_uint8 dmac_user_state_enum_uint8;

typedef enum {
    PSM_QUEUE_TYPE_NORMAL,
    PSM_QUEUE_TYPE_IMPORTANT,

    PSM_QUEUE_TYPE_BUTT
}psm_queue_type_enum;
typedef oal_uint8 psm_queue_type_enum_uint8;

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

typedef struct
{
    oal_uint32  ul_uapsd_tx_enqueue_count;              /*dmac_uapsd_tx_enqueue调用次数*/
    oal_uint32  ul_uapsd_tx_dequeue_count;              /* 出队帧个数统计 */
    oal_uint32  ul_uapsd_tx_enqueue_free_count;         /*入队过程中MPDU被释放的次数，一次可能释放多个MPDU*/
    oal_uint32  ul_uapsd_rx_trigger_in_sp;              /*trigger检查发现处于SP中的次数*/
    oal_uint32  ul_uapsd_rx_trigger_state_trans;        /*trigger检查中发现需要状态转换的次数*/
    oal_uint32  ul_uapsd_rx_trigger_dup_seq;            /*trigger帧是重复帧的个数*/
    oal_uint32  ul_uapsd_send_qosnull;                  /*队列为空，发送qos null data的个数*/
    oal_uint32  ul_uapsd_send_extra_qosnull;            /*最后一个为管理帧，发送额外qosnull的个数*/
    oal_uint32  ul_uapsd_process_queue_error;           /*队列处理过程中出错的次数*/
    oal_uint32  ul_uapsd_flush_queue_error;             /*flush队列处理过程中出错的次数*/
    oal_uint32  ul_uapsd_send_qosnull_fail;             /* 发送qosnull失败次数 */
}dmac_usr_uapsd_statis_stru;

typedef struct
{
    oal_uint32  ul_psm_enqueue_succ_cnt;                  /* psm队列成功入队帧个数 */
    oal_uint32  ul_psm_enqueue_fail_cnt;                  /* psm队列入队失败被释放的帧个数 */
    oal_uint32  ul_psm_dequeue_fail_cnt;                  /* psm队列出队失败的帧个数 */
    oal_uint32  ul_psm_dequeue_succ_cnt;                  /* psm队列出队成功的帧个数 */
    oal_uint32  ul_psm_send_data_fail_cnt;                /* psm队列出队的数据帧发送失败个数 */
    oal_uint32  ul_psm_send_mgmt_fail_cnt;                /* psm队列出队的管理帧发送失败个数 */
    oal_uint32  ul_psm_send_null_fail_cnt;                /* AP发送null data失败的次数 */
    oal_uint32  ul_psm_resv_pspoll_send_null;             /* AP收到用户的pspoll，但是队列中没有缓存帧的次数 */
    oal_uint32  ul_psm_rsp_pspoll_succ_cnt;               /* AP收到用户的pspoll，发送缓存帧成功的次数 */
    oal_uint32  ul_psm_rsp_pspoll_fail_cnt;               /* AP收到用户的pspoll，发送缓存帧失败的次数 */
}dmac_user_psm_stats_stru;


typedef struct
{
    oal_spin_lock_stru          st_lock_uapsd;                      /*uapsd操作所*/
    oal_netbuf_head_stru        st_uapsd_queue_head;                /*uapsd节能队列头*/
    oal_atomic                  uc_mpdu_num;                        /*当前节能队列里的mpdu个数*/
    oal_uint16                  us_uapsd_trigseq[WLAN_WME_AC_BUTT]; /*最近一个trigger帧的sequence*/
    dmac_usr_uapsd_statis_stru *pst_uapsd_statis;                  /*运行中统计维测信息*/
}dmac_user_uapsd_stru;

typedef struct
{
    oal_spin_lock_stru          st_lock_ps;                   /* 对队列和ul_mpdu_num操作时需要加锁 */
    oal_netbuf_head_stru        st_ps_queue_head;             /* 用户节能缓存队列头 */
    oal_atomic                  uc_mpdu_num;                  /* 用户节能缓存队列中已存在的mpdu个数 */
    oal_bool_enum_uint8         en_is_pspoll_rsp_processing;  /* TURE:当前有pspoll正在处理，FALSE:当前没有pspoll正在处理*/
    oal_uint8                   auc_resv[3];
    dmac_user_psm_stats_stru   *pst_psm_stats;
}dmac_user_ps_stru;
typedef struct
{
    oal_int32    ul_signal;
    oal_uint32   ul_drv_rx_pkts;      /* 接收数据(硬件上报，包含rx描述符不成功的帧)数目，仅仅统计数据帧 */
    oal_uint32   ul_hw_tx_pkts;      /* 发送完成中断上报发送成功的个数 ，仅仅统计数据帧 */
    oal_uint32   ul_drv_rx_bytes;    /* 驱动接收字节数，不包括80211头尾 */
    oal_uint32   ul_hw_tx_bytes;     /* 发送完成中断上报发送成功字节数 */
    oal_uint32   ul_tx_retries;      /*发送重传次数*/
    oal_uint32   ul_rx_dropped_misc; /*接收失败(决定丢弃的帧)次数*/
    oal_uint32   ul_tx_failed;      /* 发送失败最终丢弃的次数，仅仅统计数据帧  */

    oal_uint32   ul_hw_tx_failed;   /* 发送完成中断上报发送失败的个数，仅仅统计数据帧 */
    oal_uint32   ul_tx_total;       /* 发送总计，仅仅统计数据帧  */

}dmac_user_query_stats_stru;

/* 软件平均rssi统计信息结构体 */
typedef struct
{
    oal_int32       l_tx_rssi;                  /* 记录ACK RSSI的累计值 */
    oal_int32       l_rx_rssi;                  /* 记录接收RSSI的累计值 */
    oal_uint16      us_tx_rssi_stat_count;      /* 发送平均rssi统计的发包数目 */
    oal_uint16      us_rx_rssi_stat_count;      /* 接收平均rssi统计的发包数目 */
}dmac_rssi_stat_info_stru;

/* 软件平均速率统计信息结构体 */
typedef struct
{
    oal_uint32      ul_tx_rate;                 /* 记录发送速率的累计值 */
    oal_uint32      ul_rx_rate;                 /* 记录接收速率的累计值 */
    oal_uint16      us_tx_rate_stat_count;      /* 发送平均rate统计的发包数目 */
    oal_uint16      us_rx_rate_stat_count;      /* 接收平均rate统计的发包数目 */
}dmac_rate_stat_info_stru;

typedef struct
{
    /* 用户基本信息 */
    wlan_protocol_enum_uint8 en_protocol;                        /* 协议模式 */
    hal_channel_assemble_enum_uint8 en_bandwidth;                       /* 工作带宽 */

    /* 算法用到的各个标志位 */
    oal_bool_enum_uint8 en_dmac_rssi_stat_flag;             /* 是否进行平均rssi统计 */
    oal_bool_enum_uint8 en_dmac_rate_stat_flag;             /* 是否进行平均速率统计 */

    dmac_rssi_stat_info_stru st_dmac_rssi_stat_info;             /* 软件平均rssi统计信息结构体指针 */
    dmac_rate_stat_info_stru st_dmac_rate_stat_info;             /* 软件平均速率统计信息结构体指针 */
}dmac_user_rate_info_stru;


typedef struct
{
    /* 此项变量仅能处于DMAC USER结构体内的第一项 */
    mac_user_stru                               st_user_base_info;                  /* hmac user与dmac user公共部分 */

    /* 当前VAP工作在AP或STA模式，以下字段为user是STA或AP时公共字段，新添加字段请注意!!! */
    oal_uint8                                   uc_lut_index;                       /* user对应的硬件索引，活跃用户id */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint8                                   auc_resv;
    oal_uint16                                  us_non_qos_seq_frag_num;                 /* 记录该用户非QOS帧的seq+frag num*/
#else
    oal_uint8                                   auc_res[3];
#endif
    oal_uint8                                   auc_txchain_mask[WLAN_NSS_BUTT];    /* 每种空间流下对应的TX CHAIN MASK */
    dmac_tid_stru                               ast_tx_tid_queue[WLAN_TID_MAX_NUM]; /* 发送tid缓存队列 */
    oal_void                                   *p_alg_priv;                         /* 用户级别算法私有结构体 */
    oal_uint16                                  us_partial_aid;
    oal_uint8                                   uc_groupid;
    oal_int8                                    c_rx_rssi;                              /* 用户接收RSSI统计量 */
    oal_uint16                                  aus_txseqs_frag[WLAN_TID_MAX_NUM];      /* 分片报文的seq num */
    oal_uint16                                  aus_txseqs[WLAN_TID_MAX_NUM];           /* 发送tid对应的seq num */

    /* 当前VAP工作在AP模式，以下字段为user是STA时独有字段，新添加字段请注意!!! */
    oal_uint8                                   bit_ps_mode     : 1,                /* ap保留的用户节能模式，PSM用 */
                                                bit_active_user : 1,                /* 是否活跃用户，用户管理用 */
                                                bit_forbid_rts  : 1,                /* 是否强制禁用RTS(在开启RTS存在兼容性问题时禁用RTS) */
                                                bit_resv        : 5;

    oal_bool_enum_uint8                         en_vip_flag;                        /* 只算法调度用，通过配置命令配置，TRUE: VIP用户, FALSE: 非VIP用户 */
    dmac_user_smartant_training_enum_uint8      en_smartant_training;               /* 智能天线训练状态  */
    oal_bool_enum_uint8                         en_delete_ba_flag;                  /* 删除ba标志，只算法通过接口修改，autorate降协议模式时置为true */

    dmac_tx_normal_rate_stats_stru              st_smartant_rate_stats;             /* 智能天线在发送完成中的统计信息 */
    dmac_user_ps_stru                           st_ps_structure;                    /* 用户的节能结构,单播用户与组播用户都会用*/

#ifdef _PRE_WLAN_FEATURE_UAPSD
    dmac_user_uapsd_stru                        st_uapsd_stru;                      /* 用户的U-APSD节能结构*/
#endif

    hal_tx_txop_alg_stru                        st_tx_data_mcast;                    /* 组播数据帧参数，预留11k使用 */
    hal_tx_txop_alg_stru                        st_tx_data_bcast;                    /* 广播数据帧参数, 预留11k使用 */
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
    /*添加信息上报字段*/
    dmac_user_query_stats_stru                  st_query_stats;
#endif
    mac_user_uapsd_status_stru                  st_uapsd_status;                        /* uapsd状态 */
    oal_uint8                                   uc_uapsd_flag;                          /* STA的U-APSD当前的处理状态 */
    oal_uint8                                   uc_max_key_index;                       /* 最大ptk index */
    oal_uint8                                   uc_resv2[2];
    oal_uint32                                  ul_last_active_timestamp;               /* user最后活跃时刻时间戳，user老化和活跃用户替换使用(使用OAL提供的时间戳函数赋值) */

    dmac_user_rate_info_stru                    st_user_rate_info;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    mac_user_track_txrx_protocol_stru           st_txrx_protocol;                       /* 保存上一个收发帧所使用的协议模式，如果本次变化了，则上报sdt */
    mac_user_track_ctx_stru                     st_user_track_ctx;
#endif
    /* 当前VAP工作在STA模式，以下字段为user是AP时独有字段，新添加字段请注意!!! */
}dmac_user_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE_USER_TRACK

extern oal_uint32  dmac_user_check_txrx_protocol_change(dmac_user_stru *pst_dmac_user,
                                                                      oal_uint8      uc_present_mode,
                                                                      oam_user_info_change_type_enum_uint8  en_type);
#endif
extern oal_uint32  dmac_user_del_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx);
extern oal_uint32  dmac_user_add(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_add_notify_alg(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_del(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_multi_user_idx);
extern oal_void    dmac_user_key_search_fail_handler(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_tx_inactive_user_handler(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_pause(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_resume(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_active(dmac_user_stru * pst_dmac_user);
extern oal_uint32  dmac_user_inactive(dmac_user_stru * pst_dmac_user);
extern oal_void dmac_user_init_slottime(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32  dmac_user_set_groupid_partial_aid(mac_vap_stru  *pst_mac_vap,
                                             dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_get_tid_by_num(mac_user_stru *pst_mac_user, oal_uint8 uc_tid_num, dmac_tid_stru **ppst_tid_queue);
#ifdef _PRE_WLAN_FEATURE_HISTREAM
extern oal_void dmac_user_set_histream_info(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, mac_histream_stru *pst_histream_info);
#endif //_PRE_WLAN_FEATURE_HISTREAM
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint8  dmac_user_get_smps_mode(mac_vap_stru  *pst_mac_vap, mac_user_stru *pst_mac_user);
#endif
oal_uint32  dmac_user_keepalive_timer(void *p_arg);
extern  oal_void dmac_ap_pause_all_user(mac_vap_stru *pst_mac_vap);
extern  oal_void dmac_ap_resume_all_user(mac_vap_stru *pst_mac_vap);
extern  oal_void dmac_rx_compatibility_identify(dmac_user_stru *pst_dmac_user, oal_uint32 ul_rate_kbps);
extern  oal_void dmac_rx_compatibility_show_stat(dmac_user_stru *pst_dmac_user);
extern oal_uint32 dmac_user_alloc(oal_uint16 us_user_idx);
extern oal_uint32 dmac_user_free(oal_uint16 us_user_idx);
extern void*  mac_res_get_dmac_user(oal_uint16 us_idx);
extern void*  mac_res_get_dmac_user_alloc(oal_uint16 us_idx);
oal_bool_enum_uint8 dmac_psm_is_psm_empty(dmac_user_stru *pst_dmac_user);
oal_bool_enum_uint8 dmac_psm_is_uapsd_empty(dmac_user_stru  *pst_dmac_user);
oal_bool_enum_uint8 dmac_psm_is_tid_empty(dmac_user_stru  *pst_dmac_user);
oal_uint32 dmac_psm_tid_mpdu_num(dmac_user_stru  *pst_dmac_user);
extern oal_void  dmac_tid_tx_queue_exit(dmac_user_stru *pst_dmac_user);
extern dmac_user_stru  *mac_vap_get_dmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_user.h */
