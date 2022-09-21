/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_user.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   : hmac_user.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_USER_H__
#define __HMAC_USER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mac_user.h"
#include "mac_resource.h"
#include "hmac_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_edca_opt.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_USER_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_ADDBA_EXCHANGE_ATTEMPTS        10  /* 试图建立ADDBA会话的最大允许次数 */

#define HMAC_USER_IS_AMSDU_SUPPORT(_user, _tid)         (((_user)->uc_amsdu_supported) & (0x01 << ((_tid) & 0x07)))

#define HMAC_USER_SET_AMSDU_SUPPORT(_user, _tid)        (((_user)->uc_amsdu_supported) |= (0x01 << ((_tid) & 0x07)))

#define HMAC_USER_SET_AMSDU_NOT_SUPPORT(_user, _tid)    (((_user)->uc_amsdu_supported) &= (oal_uint8)(~(0x01 << ((_tid) & 0x07))))

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#define MAX_JUDGE_CACHE_LENGTH      20  /* 业务识别-用户待识别队列长度 */
#define MAX_CONFIRMED_FLOW_NUM      2   /* 业务识别-用户已识别业务总数 */
#endif

#define   HMAC_USER_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))

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
/* TID对应的发送BA会话的状态 */
typedef struct
{
    dmac_ba_conn_status_enum_uint8  en_ba_status;       /* 该TID对应的BA会话的状态 */
    oal_uint8                       uc_addba_attemps;   /* 启动建立BA会话的次数 */
    oal_uint8                       uc_dialog_token;    /* 随机标记数 */
    oal_bool_enum_uint8             en_ba_switch;
    frw_timeout_stru                st_addba_timer;
    dmac_ba_alarm_stru              st_alarm_data;
}hmac_ba_tx_stru;

typedef struct
{
    oal_bool_enum_uint8                     in_use;                     /* 缓存BUF是否被使用 */
    oal_uint8                               uc_num_buf;                 /* MPDU占用的netbuf(接收描述符)个数 */
    oal_uint16                              us_seq_num;                 /* MPDU对应的序列号 */
    oal_netbuf_head_stru                    st_netbuf_head;             /* MPDU对应的描述符首地址 */
    oal_uint32                              ul_rx_time;                 /* 报文被缓存的时间戳 */
} hmac_rx_buf_stru;

typedef struct
{
    oal_void                               *pst_ba;
    oal_uint8                               uc_tid;
    mac_delba_initiator_enum_uint8          en_direction;
    oal_uint8                               uc_resv[1];
    oal_uint8                               uc_vap_id;
    oal_uint16                              us_mac_user_idx;
    oal_uint16                              us_timeout_times;

}hmac_ba_alarm_stru;

/*Hmac侧接收侧BA会话句柄 */
typedef struct
{
    oal_uint16                      us_baw_start;               /* 第一个未收到的MPDU的序列号 */
    oal_uint16                      us_baw_end;                 /* 最后一个可以接收的MPDU的序列号 */
    oal_uint16                      us_baw_tail;                /* 目前Re-Order队列中，最大的序列号 */
    oal_uint16                      us_baw_size;                /* Block_Ack会话的buffer size大小 */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock_stru              st_ba_lock;                 /* 02用于hcc线程和事件线程并发 */
#endif

    oal_bool_enum_uint8             en_timer_triggered;         /* 上一次上报是否为定时器上报 */
    oal_bool_enum_uint8             en_is_ba;                   /* Session Valid Flag */
    dmac_ba_conn_status_enum_uint8  en_ba_status;               /* 该TID对应的BA会话的状态 */
    oal_uint8                       uc_mpdu_cnt;                /* 当前Re-Order队列中，MPDU的数目 */

    hmac_rx_buf_stru                ast_re_order_list[WLAN_AMPDU_RX_BUFFER_SIZE];  /* Re-Order队列 */
    hmac_ba_alarm_stru              st_alarm_data;
    /* frw_timeout_stru                st_ba_timer; */

    /*以下action帧相关*/
    mac_back_variant_enum_uint8     en_back_var;        /* BA会话的变体 */
    oal_uint8                       uc_dialog_token;    /* ADDBA交互帧的dialog token */
    oal_uint8                       uc_ba_policy;       /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;       /* 接收端Session H/w LUT Index */
    oal_uint16                      us_status_code;     /* 返回状态码 */
    oal_uint16                      us_ba_timeout;      /* BA会话交互超时时间 */
    oal_uint8                      *puc_transmit_addr;  /* BA会话发送端地址 */
    oal_bool_enum_uint8             en_amsdu_supp;      /* BLOCK ACK支持AMSDU的标识 */
    oal_uint8                       auc_resv1[1];
    oal_uint16                      us_baw_head;        /* bitmap的起始序列号 */
    oal_uint32                      aul_rx_buf_bitmap[2];
}hmac_ba_rx_stru;

/* user结构中，TID对应的BA信息的保存结构 */
typedef struct
{
    oal_uint8               uc_tid_no;
    oal_bool_enum_uint8     en_ampdu_start;             /* 标识该tid下的AMPDU是否已经被设置 */
    oal_uint16              us_hmac_user_idx;
    hmac_ba_tx_stru         st_ba_tx_info;
    hmac_ba_rx_stru        *pst_ba_rx_info;             /* 由于部分处理上移，这部分内存到LocalMem中申请 */
    frw_timeout_stru        st_ba_timer;                /* 接收重排序缓冲超时 */
}hmac_tid_stru;
typedef struct
{
    oal_uint32  bit_short_preamble      : 1,        /* 是否支持802.11b短前导码 0=不支持， 1=支持*/
                bit_erp                 : 1,        /* AP保存STA能力使用,指示user是否有ERP能力， 0=不支持，1=支持*/
                bit_erp_use_protect     : 1,        /* 供STA保存AP是否启用了ERP保护 */
                bit_short_slot_time     : 1,        /* 短时隙: 0=不支持, 1=支持 */
                bit_11ac2g              : 1,
                bit_11ntxbf             : 1,
                bit_resv                : 26;
}hmac_user_cap_info_stru;

#ifdef _PRE_WLAN_FEATURE_WAPI
#define WAPI_KEY_LEN                    16
#define WAPI_PN_LEN                     16
#define HMAC_WAPI_MAX_KEYID             2


typedef struct
{
    oal_uint32 ulrx_mic_calc_fail;           /* 由于参数错误导致mic计算错误 */
    oal_uint32 ultx_ucast_drop;              /* 由于协议没有完成，将帧drop掉 */
    oal_uint32 ultx_wai;
    oal_uint32 ultx_port_valid;             /* 协商完成的情况下，发送的帧个数 */
    oal_uint32 ulrx_port_valid;             /* 协商完成的情况下，接收的帧个数 */
    oal_uint32 ulrx_idx_err;                /* 接收idx错误错误 */
    oal_uint32 ulrx_netbuff_len_err;        /* 接收netbuff长度错误 */
    oal_uint32 ulrx_idx_update_err;         /* 密钥更新错误 */
    oal_uint32 ulrx_key_en_err;             /* 密钥没有使能 */
    oal_uint32 ulrx_pn_odd_err;             /* PN奇偶校验出错 */
    oal_uint32 ulrx_pn_replay_err;          /* PN重放 */
    oal_uint32 ulrx_memalloc_err;           /* rx内存申请失败 */
    oal_uint32 ulrx_decrypt_ok;             /* 解密成功的次数 */

    oal_uint32 ultx_memalloc_err;            /* 内存分配失败 */
    oal_uint32 ultx_mic_calc_fail;           /* 由于参数错误导致mic计算错误 */
    //oal_uint32 ultx_drop_wai;              /* wai帧drop的次数 */
    oal_uint32 ultx_encrypt_ok;              /* 加密成功的次数 */
    oal_uint8  aucrx_pn[WAPI_PN_LEN];       /* 问题发生时，记录接收方向帧的PN,此pn会随时被刷新 */

}hmac_wapi_debug;

typedef struct
{
    oal_uint8   auc_wpi_ek[WAPI_KEY_LEN];
    oal_uint8   auc_wpi_ck[WAPI_KEY_LEN];
    oal_uint8   auc_pn_rx[WAPI_PN_LEN];
    oal_uint8   auc_pn_tx[WAPI_PN_LEN];
    oal_uint8   uc_key_en;
    oal_uint8   auc_rsv[3];
}hmac_wapi_key_stru;

typedef struct tag_hmac_wapi_stru
{
    oal_uint8              uc_port_valid;                       /* wapi控制端口 */
    oal_uint8              uc_keyidx;
    oal_uint8              uc_keyupdate_flg;                    /* key更新标志 */
    oal_uint8              uc_pn_inc;                           /* pn步进值 */

    hmac_wapi_key_stru     ast_wapi_key[HMAC_WAPI_MAX_KEYID];   /*keyed: 0~1 */

#ifdef _PRE_WAPI_DEBUG
    hmac_wapi_debug        st_debug;                            /* 维侧 */
#endif

    oal_uint8               (*wapi_filter_frame)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru *pst_netbuff);
    oal_bool_enum_uint8     (*wapi_is_pn_odd)(oal_uint8 *puc_pn);     /* 判断pn是否为奇数 */
    oal_uint32              (*wapi_decrypt)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru *pst_netbuff);
    oal_uint32              (*wapi_encrypt)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
    oal_netbuf_stru        *(*wapi_netbuff_txhandle)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
    oal_netbuf_stru        *(*wapi_netbuff_rxhandle)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
}hmac_wapi_stru;

#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
/* 业务识别-五元组结构体: 用于唯一地标识业务流 */
typedef struct
{
    oal_uint32                          ul_sip;                         /* ip */
    oal_uint32                          ul_dip;

    oal_uint16                          us_sport;                       /* 端口 */
    oal_uint16                          us_dport;

    oal_uint32                          ul_proto;                       /* 协议 */

}hmac_tx_flow_info_stru;

/* 业务识别-待识别队列结构体: */
typedef struct
{
    hmac_tx_flow_info_stru              st_flow_info;

    oal_uint32                          ul_len;                        /* 来包长度 */
    oal_uint8                           uc_flag;                       /* 有效位，用于计数 */

    oal_uint8                           uc_udp_flag;                   /* udp flag为1即为UDP帧 */
    oal_uint8                           uc_tcp_flag;                   /* tcp flag为1即为TCP帧 */

    oal_uint8                           uc_rtpver;                     /* RTP version */
    oal_uint32                          ul_rtpssrc;                    /* RTP SSRC */
    oal_uint32                          ul_payload_type;               /* RTP:标记1bit、有效载荷类型(PT)7bit */

}hmac_tx_judge_info_stru;

/* 业务识别-待识别队列主要业务结构体: */
typedef struct
{
    hmac_tx_flow_info_stru              st_flow_info;

    oal_uint32                          ul_average_len;                /* 业务来包平均长度 */
    oal_uint8                           uc_flag;                       /* 有效位 */

    oal_uint8                           uc_udp_flag;                   /* udp flag为1即为UDP帧 */
    oal_uint8                           uc_tcp_flag;                   /* tcp flag为1即为TCP帧 */

    oal_uint8                           uc_rtpver;                     /* RTP version */
    oal_uint32                          ul_rtpssrc;                    /* RTP SSRC */
    oal_uint32                          ul_payload_type;               /* 标记1bit、有效载荷类型(PT)7bit */

    oal_uint32                          ul_wait_check_num;             /* 待检测列表中此业务包个数 */

}hmac_tx_major_flow_stru;

/* 业务识别-用户已识别结构体: */
typedef struct
{
    hmac_tx_flow_info_stru              st_cfm_flow_info;               /* 已识别业务的五元组信息 */

    oal_uint32                          ul_last_jiffies;                /* 记录已识别业务的最新来包时间 */
    oal_uint16                          us_cfm_tid;                     /* 已识别业务tid */

    oal_uint16                          us_cfm_flag;                        /* 有效位 */

}hmac_tx_cfm_flow_stru;


/* 业务识别-用户待识别业务队列: */
typedef struct
{
    oal_uint32                          ul_jiffies_st;                                  /* 记录待识别业务队列的起始时间与最新来包时间 */
    oal_uint32                          ul_jiffies_end;
    oal_uint32                          ul_to_judge_num;                                /* 用户待识别业务队列长度 */

    hmac_tx_judge_info_stru             ast_judge_cache[MAX_JUDGE_CACHE_LENGTH];     /* 待识别流队列 */

}hmac_tx_judge_list_stru;
#endif

/* 声明该结构体变量后请一定要调用oal_memzero */
typedef struct
{
    /* 当前VAP工作在AP或STA模式，以下字段为user是STA或AP时公共字段，新添加字段请注意!!! */
    oal_uint8                       uc_is_wds;                                  /* 是否是wds用户 */
    oal_uint8                       uc_amsdu_supported;                     /* 每个位代表某个TID是否支持AMSDU */
    oal_uint16                      us_amsdu_maxsize;                           /* amsdu最大长度 */
    hmac_amsdu_stru                 ast_hmac_amsdu[WLAN_WME_MAX_TID_NUM];       /* asmdu数组 */
    hmac_tid_stru                   ast_tid_info[WLAN_TID_MAX_NUM];             /* 保存与TID相关的信息 */
    oal_uint32                      aul_last_timestamp[WLAN_TID_MAX_NUM];       /* 时间戳用于实现5个连续报文建立BA */
    oal_uint8                       auc_ch_text[WLAN_CHTXT_SIZE];               /* WEP用的挑战明文 */
    frw_timeout_stru                st_mgmt_timer;                              /* 认证关联用定时器 */
    frw_timeout_stru                st_defrag_timer;                            /* 去分片超时定时器 */
    oal_netbuf_stru                *pst_defrag_netbuf;
    oal_uint8                       auc_ba_flag[WLAN_TID_MAX_NUM];          /* 该标志表示该TID是否可以建立BA会话，大于等于5时可以建立BA会话。该标志在用户初始化、删除BA会话时清零 */
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    mac_sa_query_stru               st_sa_query_info;                       /* sa query流程的控制信息 */
#endif
    mac_rate_stru                   st_op_rates;                            /* user可选速率 AP侧保存STA速率；STA侧保存AP速率 */
    hmac_user_cap_info_stru         st_hmac_cap_info;                       /* hmac侧用户能力标志位 */
    oal_uint32                      ul_rssi_last_timestamp;                 /* 获取user rssi所用时间戳, 1s最多更新一次rssi */

    /* 当前VAP工作在AP模式，以下字段为user是STA时独有字段，新添加字段请注意!!! */
    oal_uint32                      ul_assoc_req_ie_len;
    oal_uint8                      *puc_assoc_req_ie_buff;
    oal_bool_enum_uint8             en_user_bw_limit;                       /* 该用是否有限速 */
    oal_uint8                       auc_resv1[3];

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_uint32                      aaul_txrx_data_stat[WLAN_WME_AC_BUTT][WLAN_TXRX_DATA_BUTT];       /* 发送/接收 tcp/udp be,bk,vi,vo报文 */
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_stru                  st_wapi;
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
    oal_uint8                       uc_cfm_num;                                         /* 用户已被识别业务个数 */
    oal_uint8                       auc_resv2[3];
    hmac_tx_cfm_flow_stru           ast_cfm_flow_list[MAX_CONFIRMED_FLOW_NUM];          /* 已识别业务 */
    hmac_tx_judge_list_stru         st_judge_list;                                      /* 待识别流队列 */

    //oal_spin_lock_stru          st_lock;

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    oal_uint32                      ul_receive_ncw_cnt;                        /* host侧接收到notify_channel_width计数 */
    oal_uint32                      ul_ncw_start_time;                         /* sta带宽切换起始时间戳 */
#endif

    /* 当前VAP工作在STA模式，以下字段为user是AP时独有字段，新添加字段请注意!!! */
    mac_user_stats_flag_stru        st_user_stats_flag;                      /*当user是sta时候，指示user是否被统计到对应项*/
    oal_uint32                      ul_rx_pkt_drop;                      /* 接收数据包host侧被drop的计数 */


    /* 此项变量仅能处于HMAC USER结构体内的最后一项 */
    mac_user_stru                   st_user_base_info;                          /* hmac user与dmac user公共部分 */

}hmac_user_stru;

/*SA Query 超时定时器 和 间隔定时器 的超时函数入参结构*/
typedef struct
{
    mac_vap_stru     *pst_mac_vap;                  /* 发送SA Query request的mac vap信息 */
    hmac_user_stru   *pst_hmac_user;                /* 目标user */
}hmac_maxtimeout_timer_stru;
typedef struct
{
    mac_vap_stru       *pst_mac_vap;                  /* 发送SA Query request的mac vap信息 */
    hmac_user_stru     *pst_hmac_user;                /* 目标user */
    oal_bool_enum_uint8 en_is_protected;              /* SA Query管理帧加密的使能开关 */
    oal_uint16          us_trans_id;                  /* SA Query request帧的trans id */
}hmac_interval_timer_stru;

/* 存储AP关联请求帧的ie信息，用于上报内核 */
typedef struct
{
    oal_uint32                      ul_assoc_req_ie_len;
    oal_uint8                      *puc_assoc_req_ie_buff;
    oal_uint8                       auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
}hmac_asoc_user_req_ie_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_user_ht_support
 功能描述  : 是否为HT用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_TRUE是，OAL_FALSE不是
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_ht_support(hmac_user_stru *pst_hmac_user)
{
    if (OAL_TRUE == pst_hmac_user->st_user_base_info.st_ht_hdl.en_ht_capable)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_user_vht_support
 功能描述  : 是否为VHT用户
 输入参数  : hmac_user_stru *pst_hmac_user
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月12日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_vht_support(hmac_user_stru *pst_hmac_user)
{
    if (OAL_TRUE == pst_hmac_user->st_user_base_info.st_vht_hdl.en_vht_capable)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_user_xht_support
 功能描述  : 是否支持ht/vht聚合
 输入参数  : hmac_user_stru *pst_hmac_user
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月12日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_xht_support(hmac_user_stru *pst_hmac_user)
{
    if ((pst_hmac_user->st_user_base_info.en_cur_protocol_mode >= WLAN_HT_MODE)
        && (pst_hmac_user->st_user_base_info.en_cur_protocol_mode < WLAN_PROTOCOL_BUTT))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  hmac_user_alloc(oal_uint16 *pus_user_idx, oal_uint8 ul_is_multi_user);
extern oal_uint32  hmac_user_free(oal_uint16 us_idx);
extern oal_uint32  hmac_user_init(hmac_user_stru *pst_hmac_user);
extern oal_uint32  hmac_user_set_avail_num_space_stream(mac_user_stru *pst_mac_user, wlan_nss_enum_uint8 en_vap_nss);
extern oal_uint32  hmac_user_del(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern oal_uint32  hmac_user_add(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint16 *pus_user_index);
extern oal_uint32  hmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 *us_user_index);
extern oal_uint32  hmac_user_del_multi_user(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_user_add_notify_alg(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx);
extern oal_uint32 hmac_update_user_last_active_time(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_void hmac_tid_clear(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern hmac_user_stru*  mac_res_get_hmac_user_alloc(oal_uint16 us_idx);
extern hmac_user_stru*  mac_res_get_hmac_user(oal_uint16 us_idx);
extern hmac_user_stru  *mac_vap_get_hmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);


#ifdef _PRE_WLAN_FEATURE_WAPI
extern hmac_wapi_stru *hmac_user_get_wapi_ptr(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_pairwise, oal_uint16 us_pairwise_idx);
extern oal_uint8  hmac_user_is_wapi_connected(oal_uint8 uc_device_id);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_user.h */
