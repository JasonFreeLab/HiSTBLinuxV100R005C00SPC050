/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : hmac对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_EXT_IF_H__
#define __HMAC_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_vap.h"
#include "mac_user.h"
#include "mac_frame.h"
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "oal_hcc_host_if.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_EXT_IF_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_RSP_MSG_MAX_LEN  64   /* get wid返回消息最大长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 返回值类型定义 */
typedef enum
{
    HMAC_TX_PASS = 0,     /* 继续往下 */
    HMAC_TX_BUFF = 1,     /* 已被缓存 */
    HMAC_TX_DONE = 2,     /* 组播转成单播已发送 */

    HMAC_TX_DROP_PROXY_ARP    = 3, /* PROXY ARP检查后丢弃*/
    HMAC_TX_DROP_USER_UNKNOWN,     /* 未知user*/
    HMAC_TX_DROP_USER_NULL,        /* user结构体为NULL*/
    HMAC_TX_DROP_USER_INACTIVE,    /* 目的user未关联*/
    HMAC_TX_DROP_SECURITY_FILTER,  /* 安全检查过滤掉*/
    HMAC_TX_DROP_BA_SETUP_FAIL,    /* BA会话创建失败*/
    HMAC_TX_DROP_AMSDU_ENCAP_FAIL, /* amsdu封装失败*/
    HMAC_TX_DROP_MUSER_NULL,       /*组播user为NULL */
    HMAC_TX_DROP_MTOU_FAIL,        /* 组播转单播失败*/
    HMAC_TX_DROP_80211_ENCAP_FAIL, /* 802.11 head封装失败*/

    HMAC_TX_BUTT
}hmac_tx_return_type_enum;
typedef oal_uint8 hmac_tx_return_type_enum_uint8;


/*****************************************************************************
  枚举名  : hmac_host_ctx_event_sub_type_enum_uint8
  协议表格:
  枚举说明: HOST CTX事件子类型定义
*****************************************************************************/
typedef enum
{
    HMAC_HOST_CTX_EVENT_SUB_TYPE_SCAN_COMP_STA= 0,      /* STA　扫描完成子类型 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_ASOC_COMP_STA,         /* STA 关联完成子类型 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_DISASOC_COMP_STA,      /* STA 上报去关联完成 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_CONNECT_AP,        /* AP 上报新加入BSS的STA情况 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_DISCONNECT_AP,      /* AP 上报离开BSS的STA情况 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_MIC_FAILURE,           /* 上报MIC攻击*/
    HMAC_HOST_CTX_EVENT_SUB_TYPE_ACS_RESPONSE,          /* 上报ACS命令执行结果 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_RX_MGMT,               /* 上报接收到的管理帧 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_LISTEN_EXPIRED,        /* 上报监听超时 */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    HMAC_HOST_CTX_EVENT_SUB_TYPE_ADD_PROXY_STA_VAP,     /* 上报WAL层，把Proxy STA添加到Device中，如果第一次创建的Proxy STA，添加网桥钩子函数 */
    HMAC_HOST_CTX_EVENT_SUB_TYPE_REMOVE_PROXY_STA_VAP,  /* 上报WAL层, 把Proxy STA从Device中移除，如果是移除最后一个Proxy STA，删除网桥钩子函数*/
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    HMAC_HOST_CTX_EVENT_SUB_TYPE_FLOWCTL_BACKP,         /* 上报流控反压消息 */
#endif
    HMAC_HOST_CTX_EVENT_SUB_TYPE_INIT,
    HMAC_HOST_CTX_EVENT_SUB_TYPE_MGMT_TX_STATUS,
#ifdef _PRE_WLAN_FEATURE_ROAM
    HMAC_HOST_CTX_EVENT_SUB_TYPE_ROAM_COMP_STA,         /* STA 漫游完成子类型 */
#endif  //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
    HMAC_HOST_CTX_EVENT_SUB_TYPE_FT_EVENT_STA,         /* STA 漫游完成子类型 */
#endif //_PRE_WLAN_FEATURE_11R

#ifdef _PRE_WLAN_FEATURE_DFR
    HMAC_HOST_CTX_EVENT_SUB_TYPE_DEV_ERROR,         /* device异常处理流程 */
#endif //_PRE_WLAN_FEATURE_DFR
#ifdef _PRE_WLAN_FEATURE_HILINK
    HMAC_HOST_CTX_EVENT_SUB_TYPE_OTHER_BSS_DATA,    /*上报接收到的其他BSS网络的数据帧*/
#endif

    HMAC_HOST_CTX_EVENT_SUB_TYPE_BUTT
}hmac_host_ctx_event_sub_type_enum;
typedef oal_uint8 hmac_host_ctx_event_sub_type_enum_uint8;


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
    oal_netbuf_head_stru            st_msdu_head;         /* msdu链表头 */
    frw_timeout_stru                st_amsdu_timer;
    oal_spin_lock_stru              st_amsdu_lock;        /* amsdu task lock */

    oal_uint8                       uc_msdu_num;          /* Number of sub-MSDUs accumulated */
    oal_uint8                       uc_last_pad_len;      /* 最后一个msdu的pad长度 */
    oal_uint8                       uc_amsdu_maxnum;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint8                       uc_short_pkt_num;     /* 短包计数   */
#else
    oal_uint8                       auc_reserve[1];
#endif

    oal_uint16                      us_amsdu_maxsize;
    oal_uint16                      us_amsdu_size;        /* Present size of the AMSDU */

    oal_uint8                       auc_eth_da[WLAN_MAC_ADDR_LEN];
    oal_uint8                       auc_eth_sa[WLAN_MAC_ADDR_LEN];
}hmac_amsdu_stru;

/* hmac配置私有结构 */
typedef struct
{
    oal_wait_queue_head_stru  st_wait_queue_for_sdt_reg;            /* 用于wal_config层线程等待(wal_config-->hmac),给SDT下发读寄存器命令时用 */
    oal_bool_enum_uint8       en_wait_ack_for_sdt_reg;
    oal_uint8                 auc_resv2[3];
    oal_int8                  ac_rsp_msg[HMAC_RSP_MSG_MAX_LEN];     /* get wid返回消息内存空间 */
    oal_uint32                dog_tag;

}hmac_vap_cfg_priv_stru;

/* WAL抛事件给HMAC时的事件PAYLOAD结构体 */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf链表一个元素 */
    mac_vap_stru           *pst_vap;
}hmac_tx_event_stru;

/* HMAC抛去关联完成事件结构体 */
typedef struct
{
    oal_uint8              *puc_msg;
}hmac_disasoc_comp_event_stru;

/* 扫描结果 */
typedef struct
{
    oal_uint8     uc_num_dscr;
    oal_uint8     uc_result_code;
    oal_uint8     auc_resv[2];
}hmac_scan_rsp_stru;

/* Status code for MLME operation confirm */
typedef enum
{
    HMAC_MGMT_SUCCESS             = 0,
    HMAC_MGMT_INVALID             = 1,
    HMAC_MGMT_TIMEOUT             = 2,
    HMAC_MGMT_REFUSED             = 3,
    HMAC_MGMT_TOMANY_REQ          = 4,
    HMAC_MGMT_ALREADY_BSS         = 5
}hmac_mgmt_status_enum;
typedef oal_uint8   hmac_mgmt_status_enum_uint8;

/* 关联结果 */
typedef struct
{
    hmac_mgmt_status_enum_uint8  en_result_code;         /* 关联成功,超时等 */
    oal_uint8                    auc_resv1[1];
    mac_status_code_enum_uint16  en_status_code;         /* ieee协议规定的16位状态码  */

    oal_uint8                    auc_addr_ap[WLAN_MAC_ADDR_LEN];
    oal_uint8                    auc_resv2[2];

    oal_uint32                   ul_asoc_req_ie_len;
    oal_uint32                   ul_asoc_rsp_ie_len;

    oal_uint8                    *puc_asoc_req_ie_buff;
    oal_uint8                    *puc_asoc_rsp_ie_buff;
}hmac_asoc_rsp_stru;
/* 漫游结果 */
typedef struct
{
    oal_uint8                    auc_bssid[WLAN_MAC_ADDR_LEN];
    oal_uint8                    auc_resv1[2];
    mac_channel_stru             st_channel;
    oal_uint32                   ul_asoc_req_ie_len;
    oal_uint32                   ul_asoc_rsp_ie_len;
    oal_uint8                   *puc_asoc_req_ie_buff;
    oal_uint8                   *puc_asoc_rsp_ie_buff;
}hmac_roam_rsp_stru;

#ifdef _PRE_WLAN_FEATURE_11R
typedef struct
{
    oal_uint8                    auc_bssid[WLAN_MAC_ADDR_LEN];
    oal_uint16                   us_ft_ie_len;
    oal_uint8                   *puc_ft_ie_buff;
}hmac_roam_ft_stru;

#endif //_PRE_WLAN_FEATURE_11R

/*mic攻击*/
typedef struct
{
    oal_uint8                  auc_user_mac[WLAN_MAC_ADDR_LEN];
    oal_uint8                  auc_reserve[2];
    oal_nl80211_key_type       en_key_type;
    oal_int32                  l_key_id;
}hmac_mic_event_stru;

/* 上报接收到管理帧事件的数据结构 */
typedef struct
{
    oal_uint8                  *puc_buf;
    oal_uint16                  us_len;
    oal_uint8                   uc_rsv[2];
    oal_int32                   l_freq;
    oal_int8                    ac_name[OAL_IF_NAME_SIZE];
}hmac_rx_mgmt_event_stru;

/* 上报监听超时数据结构 */
typedef struct
{
    oal_ieee80211_channel_stru  st_listen_channel;
    oal_uint64                  ull_cookie;
    oal_wireless_dev_stru      *pst_wdev;

}hmac_p2p_listen_expired_stru;

typedef enum
{
    HMAC_REPORT_DISASSOC = 0,   /* Disassociation帧 */
    HMAC_REPORT_DEAUTH   = 1,   /* Deauthentication帧 */
    HMAC_REPORT_ACTION   = 2,   /* ACTION帧(目前只有SA Query Action帧) */

    DEVICE_REPORT_PROTECTED_BUTT
}hmac_report_disasoc_reason;

typedef oal_uint16   hmac_report_disasoc_reason_uint16;

/* 上报接收到管理帧事件的数据结构 */
typedef struct
{
    oal_uint8                   uc_dev_mode;
    oal_uint8                   uc_vap_mode;
    oal_uint8                   uc_vap_status;
    oal_uint8                   uc_write_read;
    oal_uint32                  ul_val;
}hmac_cfg_rx_filter_stru;

/* 和device侧的mac_tx_ctl归一使用一份移到dmac_ext_if.h */
#if 1
struct  mac_tx_ctl_cut
{
    /* 该成员只在第一个netbuf中有效 */
    oal_uint8                               bit_mpdu_num                :7;          /* ampdu中包含的MPDU个数,实际描述符填写的值为此值-1 */
    /* 在每个MPDU的第一个NETBUF中有效 */
    oal_uint8                               bit_netbuf_num              :1;          /* 每个MPDU占用的netbuf数目 */

    oal_uint8                               bit_frame_header_length     :6;          //51四地址32 /* 该MPDU的802.11头长度 */
    oal_uint8                               en_is_first_msdu            :1;          /* 是否是第一个子帧，OAL_FALSE不是 OAL_TRUE是 */
    oal_uint8                               en_is_amsdu                 :1;          /* 是否AMSDU: OAL_FALSE不是，OAL_TRUE是 */

    frw_event_type_enum_uint8               bit_en_event_type           :6;          /* 取值:FRW_EVENT_TYPE_WLAN_DTX和FRW_EVENT_TYPE_HOST_DRX，作用:在释放时区分是内存池的netbuf还是原生态的 */
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               bit_is_vipframe             :1;          /* 该帧是否是EAPOL帧、DHCP帧 */


    oal_uint8                               bit_tx_user_idx             :4;          /* dmac tx 到 tx complete 传递的user结构体，目标用户地址 */
    oal_uint8          						en_is_probe_data            :3;          /* 是否探测帧 */
    oal_uint8                               en_ismcast                  :1;          /* 该MPDU是单播还是多播:OAL_FALSE单播，OAL_TRUE多播 */

    oal_uint8                               bit_retried_num             :4;
    oal_uint8                               bit_need_rsp                :1;           /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               en_is_eapol                 :1;           /* 该帧是否是EAPOL帧 1102可以去掉 */
    oal_uint8                               en_is_get_from_ps_queue     :1;           /* 节能特性用，标识一个MPDU是否从节能队列中取出来的 */
    oal_uint8                               bit_is_eapol_key_ptk        :1;           /* 4 次握手过程中设置单播密钥EAPOL KEY 帧标识 */

    oal_uint8                               bit_tx_vap_index            :3;
    oal_uint8                               bit_mgmt_frame_id           :4;            /* wpas 发送管理帧的frame id */
    oal_uint8                               bit_roam_data               :1;

    wlan_wme_ac_type_enum_uint8             bit_ac                      :3;            /* ac */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy               :3;            /* ACK 策略 */
    oal_uint8                               bit_reserved3               :2;

    oal_uint8                               uc_alg_pktno;                              /* 算法用到的字段，唯一标示该报文 */

    oal_uint8                               bit_tid                     :4;
    oal_uint8                               bit_tx_user_idx_bak         :4;

    //oal_time_us_stru                        st_timestamp_us;                           /* 维测使用入TID队列时的时间戳 */
	/*align to the dmac st_timestamp_us var,TBD by */
    oal_uint8                               reserved[8];
    oal_uint16                              us_mpdu_bytes;                             /* mpdu字节数，维测用，不包括头尾，不包括snap，不包括padding */

}__OAL_DECLARE_PACKED;
typedef struct mac_tx_ctl_cut  mac_tx_ctl_cut_stru;
#endif

struct mac_rx_ctl_cut
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_da_user_idx       :4;
    oal_uint8                   bit_ta_user_idx       :4;
    oal_uint8                   bit_mac_header_len    :6;   /* mac header帧头长度 */
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :1;
    /*word 1*/
    oal_uint16                  us_frame_len;               /* 帧头与帧体的总长度 */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4;   /* 每个MPDU占用的buf数 */
    oal_uint8                   uc_channel_number;          /* 接收帧的信道 */
}__OAL_DECLARE_PACKED;
typedef struct mac_rx_ctl_cut  mac_rx_ctl_cut_stru;

typedef struct
{
    oal_wait_queue_head_stru           st_wait_queue;
    oal_bool_enum_uint8                mgmt_tx_complete;
    oal_uint32                         mgmt_tx_status;
    oal_uint8                          mgmt_frame_id;
}oal_mgmt_tx_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  hmac_board_get_instance(mac_board_stru **ppst_hmac_board);
extern oal_int32  hmac_main_init(oal_void);
extern oal_void  hmac_main_exit(oal_void);
extern oal_uint32  hmac_tx_wlan_to_wlan_ap(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_TCP_OPT
extern oal_uint32  hmac_tx_lan_to_wlan_no_tcp_opt(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf);
#endif
extern oal_uint32  hmac_tx_lan_to_wlan(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_uint32  hmac_tx_proxysta_mat(oal_netbuf_stru *pst_buf, mac_vap_stru *pst_mac_vap);
#endif
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
extern oal_uint32 hmac_tx_post_event(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_tx_event_process(oal_mem_stru *pst_event_mem);
#endif
extern oal_uint16 hmac_free_netbuf_list(oal_netbuf_stru  *pst_buf);
extern oal_uint32  hmac_vap_get_priv_cfg(mac_vap_stru *pst_mac_vap, hmac_vap_cfg_priv_stru * * ppst_cfg_priv);
extern oal_net_device_stru  *hmac_vap_get_net_device(oal_uint8 uc_vap_id);
extern oal_int8*  hmac_vap_get_desired_country(oal_uint8 uc_vap_id);
#ifdef _PRE_WLAN_FEATURE_11D
extern oal_uint32  hmac_vap_get_updata_rd_by_ie_switch(oal_uint8 uc_vap_id,oal_bool_enum_uint8 *us_updata_rd_by_ie_switch);
#endif
extern oal_uint32  hmac_vap_set_asoc_req_ie_ptr_null(oal_uint8 uc_vap_id);
extern oal_uint32  hmac_config_add_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_del_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_start_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_down_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_PM
extern oal_uint32 hmac_config_wifi_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
//extern oal_uint32  hmac_config_update_mode(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_mac_addr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
extern oal_uint32  hmac_config_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
extern oal_uint32  hmac_config_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_ampdu(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_MONITOR
extern oal_uint32  hmac_config_set_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_get_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_max_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint32 ul_max_user);
extern oal_uint32  hmac_config_set_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_mpdu_num(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  hmac_config_ota_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32  hmac_config_start_dpd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_CHIP_TEST
extern oal_uint32  hmac_config_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_clear_all_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_ota_beacon_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_ota_rx_dscr_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_all_ota(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_oam_output(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_dhcp_arp_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_random_mac_addr_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_freq(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_freq(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_wmm_params(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_wmm_params(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_vap_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_event_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_eth_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_80211_ucast_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_80211_mcast_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_probe_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_rssi_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  hmac_config_report_vap_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_wfa_cfg_aifsn(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_wfa_cfg_cw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_lte_gpio_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32  hmac_config_log_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_user_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_ampdu_start(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_ampdu_end(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_auto_ba_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_profiling_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_addba_req(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_delba_req(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_dscr_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_rate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_mcs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_mcsac(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_nss(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_rfch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_bw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_always_tx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_always_tx_1102(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_always_rx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_DEBUG_MODE
extern oal_uint32  hmac_config_dync_txpower(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
#endif
extern oal_uint32  hmac_config_get_thruput(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_freq_skew(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_adjust_ppm(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_reg_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_dbb_scaling_amend(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
extern oal_uint32  hmac_config_sdio_flowctrl(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
extern oal_uint32  hmac_config_host_sleep_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_wow(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_wow_activate_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_wow_pattern(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif /* end of _PRE_WLAN_FEATURE_WOW */

#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_uint32  hmac_config_set_monitor_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_mips_cycle_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_amsdu_start(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_list_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_list_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_sta_list(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_list_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
extern oal_uint32  hmac_config_get_lauch_cap(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_sta_initiate_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_cfg80211_start_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_cfg80211_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_cfg80211_start_scan_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_sta_initiate_join(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr);
extern oal_void    hmac_mgmt_send_deauth_frame(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da, oal_uint16 us_err_code, oal_bool_enum_uint8 en_is_protected);
extern oal_uint32  hmac_config_send_deauth(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da);
extern oal_void    hmac_mgmt_send_disassoc_frame(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_da, oal_uint16 us_err_code, oal_bool_enum_uint8 en_is_protected);

extern oal_uint32 hmac_config_11i_add_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_11i_get_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_11i_remove_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_11i_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
//extern oal_uint32 hmac_config_11i_add_wep_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_kick_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_uint32 hmac_config_set_oma(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_proxysta_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32 hmac_config_pause_tid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_dump_timer(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_user_vip(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_vap_host(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_send_bar(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_reg_write(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_check_capability_mac_phy_supplicant(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr);
oal_uint32  hmac_config_dump_ba_bitmap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_dump_all_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_vap_pkt_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
//oal_uint32 hmac_config_11i_init_privacy(mac_vap_stru *pst_mac_vap,mac_cfg80211_connect_param_stru *pst_mac_connect_param);
extern oal_uint32 hmac_config_amsdu_ampdu_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_11i_add_wep_entry(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_sdt_recv_reg_cmd(mac_vap_stru  *pst_mac_vap, oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_uint32 hmac_init_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_config_dump_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_dump_tx_dscr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_alg(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32 hmac_config_report_thrput_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
oal_uint32  hmac_config_set_txop_ps_machw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
oal_uint32 hmac_config_print_btcoex_status(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
oal_uint32 hmac_config_ltecoex_mode_set(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint32  hmac_config_set_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
extern oal_uint32  hmac_config_set_uapsden(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_uapsden(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
#endif
extern oal_uint32 hmac_config_set_reset_state(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_reset_hw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_DFT_STAT
extern oal_uint32 hmac_config_set_phy_stat_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_dbb_env_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_usr_queue_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_report_vap_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_report_all_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
oal_uint32  hmac_config_get_hipkt_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_set_flowctl_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_get_flowctl_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_11D
extern oal_uint32 hmac_config_set_rd_by_ie_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_hide_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_amsdu_tx_on(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_ampdu_tx_on(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_DFS    //1131_debug
extern oal_uint32  hmac_config_set_country_for_dfs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_set_country(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_regdomain_pwr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_reduce_sar(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_country(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_connect(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_tid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_reset_hw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_reset_operate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

extern oal_uint32 hmac_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_beacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_get_assoc_req_ie(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_wps_p2p_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_wps_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_app_ie_to_vap(mac_vap_stru *pst_mac_vap,
                                            oal_app_ie_stru *pst_wps_ie,
                                            en_app_ie_type_uint8 en_type);

extern oal_uint32  hmac_config_alg_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_DFS
extern oal_uint32  hmac_config_dfs_radartool(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_SUPPORT_ACS
extern oal_uint32  hmac_config_acs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32 hmac_config_set_acs_cmd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_beacon_chain_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32 hmac_config_tdls_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_tdls_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_2040_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_FortyMHzIntolerant(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_2040_coext_support(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_PERFORM_STAT
extern oal_uint32  hmac_config_pfm_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_pfm_display(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32  hmac_config_set_edca_opt_switch_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_edca_opt_weight_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_edca_opt_switch_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_edca_opt_cycle_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_sync_cmd_common(mac_vap_stru *pst_mac_vap,wlan_cfgid_enum_uint16 en_cfg_id,oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_uint32  hmac_config_set_pm_by_module(mac_vap_stru *pst_mac_vap, mac_pm_ctrl_type_enum pm_ctrl_type, mac_pm_switch_enum pm_enable);
#endif

#ifdef _PRE_WLAN_CHIP_TEST

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
extern oal_uint32 hmac_enable_pmf(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param);
#endif
extern oal_uint32 hmac_test_send_action(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param);

extern oal_uint32  hmac_config_send_pspoll(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_send_nulldata(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_lpm_tx_data(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_set_rts_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_update_protection_tx_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_mib(mac_vap_stru *pst_mac_vap,wlan_cfgid_enum_uint16 en_cfg_id,oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_mib(mac_vap_stru *pst_mac_vap,wlan_cfgid_enum_uint16 en_cfg_id,oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_thruput_bypass(mac_vap_stru *pst_mac_vap,wlan_cfgid_enum_uint16 en_cfg_id,oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_coex(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_auto_protection(mac_vap_stru *pst_mac_vap, oal_uint8 uc_auto_protection_flag);
extern oal_uint32  hmac_config_set_dfx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_send_2040_coext(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_2040_coext_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_DEBUG_MODE
extern oal_uint32  hmac_config_get_all_reg_value(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
extern oal_uint32  hmac_config_data_acq(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_SMPS
#ifdef _PRE_DEBUG_MODE
extern oal_uint32 hmac_config_get_smps_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  hmac_config_resume_rx_intr_fifo(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32  hmac_tx_report_eth_frame(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf);

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32  hmac_config_set_opmode_notify(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_user_rssbw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
extern oal_uint32  hmac_config_set_blacklist_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_blacklist_add(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_blacklist_add_only(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_blacklist_del(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_show_blacklist(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_show_isolation(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_autoblacklist_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_autoblacklist_aging(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_autoblacklist_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_autoblacklist_reset_time(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_isolation_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_isolation_type(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_isolation_forword(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_isolation_clear(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
/*extern oal_void hmac_config_get_blacklist(mac_vap_stru *pst_mac_vap,oal_uint8 *pst_info_str,oal_int16 str_len);*/
/*extern oal_void hmac_config_get_isolation(mac_vap_stru *pst_mac_vap,oal_uint8 *pst_info_str,oal_int16 str_len);*/
#endif
extern oal_uint32  hmac_config_set_vap_nss(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_DEBUG_MODE
extern oal_uint32  hmac_config_rx_filter_val(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_rx_filter_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_rx_filter_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_report_ampdu_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_scan_test(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_bgscan_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_ampdu_aggr_num(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  hmac_config_set_ampdu_mmss(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  hmac_config_freq_adjust(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32  hmac_config_set_stbc_cap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_ldpc_cap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_uint16  hmac_rx_proxysta_update_checksum_addr(oal_uint16 us_osum,
                                                         oal_uint8  uc_omac[6],
                                                         oal_uint8  uc_nmac[6]);
#endif
extern oal_uint32  hmac_config_scan_abort(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_cancel_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_HS20
extern oal_uint32  hmac_config_set_qos_map(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_uint32  hmac_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_set_p2p_ps_stat(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_wpas_mgmt_tx(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_vap_classify_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_vap_classify_tid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_get_fem_pa_status(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
extern oal_uint32  hmac_config_query_station_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  hmac_config_vap_state_syn(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
extern oal_uint32  hmac_config_set_uapsd_para(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_PROFLING_MIPS
extern oal_uint32  hmac_config_set_mips(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_config_show_mips(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
oal_uint32 hmac_config_enable_arp_offload(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_ip_addr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_show_arpoffload_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32   hmac_config_cfg_vap_h2d(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_config_user_asoc_state_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32 hmac_config_user_cap_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32  hmac_config_user_rate_info_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32  hmac_config_user_info_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32  hmac_config_sta_vap_info_syn(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_init_user_security_port(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32 hmac_user_set_asoc_state(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, mac_user_asoc_state_enum_uint8 en_value);
#ifdef _PRE_WLAN_TCP_OPT
oal_uint32  hmac_config_get_tcp_ack_stream_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_tx_tcp_ack_opt_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_rx_tcp_ack_opt_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_tx_tcp_ack_limit(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32  hmac_config_rx_tcp_ack_limit(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 44))
#ifdef _PRE_WLAN_DFT_STAT
oal_uint32  hmac_config_set_performance_log_switch(mac_vap_stru *pst_mac_vap,wlan_cfgid_enum_uint16 en_cfg_id,oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#endif
extern oal_void hmac_config_del_p2p_ie(oal_uint8 *puc_ie, oal_uint32 *pul_ie_len);
extern oal_uint32  hmac_find_p2p_listen_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
oal_uint32  hmac_set_device_freq(oal_uint8 uc_device_freq_type);
extern oal_int32 hmac_set_auto_freq_process_func(oal_void);
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
extern oal_uint32  hmac_config_set_tx_classify_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_ext_if.h */
