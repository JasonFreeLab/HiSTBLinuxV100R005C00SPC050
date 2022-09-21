/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_net.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月7日
  最近修改   :
  功能描述   : oal_net.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月7日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_WINDOWS_NET_H__
#define __OAL_WINDOWS_NET_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "platform_spec_1131c.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_BITFIELD_LITTLE_ENDIAN      0
#define OAL_BITFIELD_BIG_ENDIAN         1
#define OAL_WIN32_NETBUF_CB_SIZE    (48)
#define OAL_WLAN_SA_QUERY_TR_ID_LEN    2
/* wiphy  */
#define IEEE80211_HT_MCS_MASK_LEN   10
#define OAL_IF_NAME_SIZE   16
#define ETHER_ADDR_LEN  6   /* length of an Ethernet address */
#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

/*****************************************************************************
  2.10 IP宏定义
*****************************************************************************/
#define IPV6_ADDR_MULTICAST    	0x0002U
#define IPV6_ADDR_UNICAST      	0x0001U
#define IPV6_ADDR_SCOPE_TYPE(scope)	((scope) << 16)
#define IPV6_ADDR_SCOPE_NODELOCAL	0x01
#define IPV6_ADDR_SCOPE_LINKLOCAL	0x02
#define IPV6_ADDR_SCOPE_SITELOCAL	0x05
#define IPV6_ADDR_SCOPE_ORGLOCAL	0x08
#define IPV6_ADDR_SCOPE_GLOBAL		0x0e
#define IPV6_ADDR_LOOPBACK	0x0010U
#define IPV6_ADDR_LINKLOCAL	0x0020U
#define IPV6_ADDR_SITELOCAL	0x0040U

#define IPV6_ADDR_MC_SCOPE(a)	\
    ((a)->s6_addr[1] & 0x0f)    /* nonstandard */

/*****************************************************************************
  2.11 VLAN宏定义
*****************************************************************************/


/*****************************************************************************
  2.12 LLC SNAP宏定义
*****************************************************************************/


/*****************************************************************************
  2.13 ETHER宏定义
*****************************************************************************/
/* ether type */
#define ETHER_TYPE_PAE   0x888e  /* EAPOL PAE/802.1x */
#define ETHER_TYPE_IP    0x0800  /* IP protocol */
#define ETHER_TYPE_AARP  0x80f3  /* Appletalk AARP protocol */
#define ETHER_TYPE_IPX   0x8137  /* IPX over DIX protocol */
#define ETHER_TYPE_ARP   0x0806  /* ARP protocol */
#define ETHER_TYPE_RARP  0x8035
#define ETHER_TYPE_IPV6  0x86dd  /* IPv6 */
#define ETHER_TYPE_TDLS  0x890d  /* TDLS */
#define ETHER_TYPE_VLAN  0x8100  /* VLAN TAG protocol */
#define ETHER_TYPE_WAI   0x88b4  /* WAI/WAPI */
#define ETHER_LLTD_TYPE  0x88D9  /* LLTD */
#define ETHER_ONE_X_TYPE 0x888E  /* 802.1x Authentication */
#define ETHER_TUNNEL_TYPE 0x88bd  /* 自定义tunnel协议 */
#define ETHER_TYPE_PPP_DISC	0x8863		/* PPPoE discovery messages */
#define ETHER_TYPE_PPP_SES	0x8864		/* PPPoE session messages */

#define ETH_SENDER_IP_ADDR_LEN       4  /* length of an Ethernet send ip address */
#define ETH_TARGET_IP_ADDR_LEN       4  /* length of an Ethernet target ip address */

/*lint -e773*/
/* 通过结构体成员找结构体指针 第一个参数为结构体指针； 第二个参数为结构体类型名； 第三个参数为数据结构体中成员名字 */
#define OAL_CONTAINER_OF(_member_ptr, _stru_type, _stru_member_name) \
/*lint -e(413)*/        ((_stru_type *)((oal_int8 *)(_member_ptr)-(oal_uint)(&((_stru_type *)0)->_stru_member_name)))

#undef  offsetof
#define offsetof(type, member) ((long) &((type *) 0)->member)

#define OAL_SMP_MB()                                    /* 为空 */
#define OAL_ERR_CODE_NETBUF_PANIC  OAL_PTR_NULL;
#define OAL_NETBUF_LIST_NUM(_pst_head)              ((_pst_head)->ul_num)
#define OAL_NET_DEV_PRIV(_pst_dev)                  ((_pst_dev)->ml_priv)
#define OAL_NET_DEV_WIRELESS_PRIV(_pst_dev)         ((_pst_dev)->priv)
#define OAL_NET_DEV_WIRELESS_DEV(_pst_dev)          ((_pst_dev)->ieee80211_ptr)
#define OAL_NETBUF_NEXT(_pst_buf)                   ((_pst_buf)->next)
#define OAL_NETBUF_PREV(_pst_buf)                   ((_pst_buf)->prev)
#define OAL_NETBUF_HEAD_NEXT(_pst_buf_head)         ((_pst_buf_head)->pst_next)
#define OAL_NETBUF_HEAD_PREV(_pst_buf_head)         ((_pst_buf_head)->pst_prev)

#define OAL_NETBUF_DATA(_pst_buf)                   ((_pst_buf)->data)
#define OAL_NETBUF_HEADER(_pst_buf)                 ((_pst_buf)->data)
#define OAL_NETBUF_PAYLOAD(_pst_buf)                 ((_pst_buf)->data)

#define OAL_NETBUF_CB(_pst_buf)                     ((_pst_buf)->cb)
#define OAL_NETBUF_CB_SIZE()                        (OAL_WIN32_NETBUF_CB_SIZE)
#define OAL_NETBUF_LEN(_pst_buf)                    ((_pst_buf)->len)
#define OAL_NETBUF_TAIL(_pst_buf)                   ((_pst_buf)->tail)
#define OAL_NETBUF_PROTOCOL(_pst_buf)               ((_pst_buf)->protocol)

#define OAL_NETDEVICE_OPS(_pst_dev)                         ((_pst_dev)->netdev_ops)
#define OAL_NETDEVICE_OPS_OPEN(_pst_netdev_ops)             ((_pst_netdev_ops)->ndo_open)
#define OAL_NETDEVICE_OPS_STOP(_pst_netdev_ops)             ((_pst_netdev_ops)->ndo_stop)
#define OAL_NETDEVICE_OPS_START_XMIT(_pst_netdev_ops)       ((_pst_netdev_ops)->ndo_start_xmit)
#define OAL_NETDEVICE_OPS_SET_MAC_ADDR(_pst_netdev_ops)     ((_pst_netdev_ops)->ndo_set_mac_address)
#define OAL_NETDEVICE_OPS_TX_TIMEOUT(_pst_netdev_ops)       ((_pst_netdev_ops)->ndo_tx_timeout)
#define OAL_NETDEVICE_OPS_SET_MC_LIST(_pst_netdev_ops)      ((_pst_netdev_ops)->ndo_set_multicast_list)
#define OAL_NETDEVICE_OPS_GET_STATS(_pst_netdev_ops)        ((_pst_netdev_ops)->ndo_get_stats)
#define OAL_NETDEVICE_OPS_DO_IOCTL(_pst_netdev_ops)         ((_pst_netdev_ops)->ndo_do_ioctl)
#define OAL_NETDEVICE_OPS_CHANGE_MTU(_pst_netdev_ops)       ((_pst_netdev_ops)->ndo_change_mtu)
#define OAL_NETDEVICE_LAST_RX(_pst_dev)                     ((_pst_dev)->last_rx)
#define OAL_NETDEVICE_WIRELESS_HANDLERS(_pst_dev)           ((_pst_dev)->wireless_handlers)
#define OAL_NETDEVICE_RTNL_LINK_OPS(_pst_dev)               ((_pst_dev)->rtnl_link_ops)
#define OAL_NETDEVICE_RTNL_LINK_STATE(_pst_dev)             ((_pst_dev)->rtnl_link_state)
#define OAL_NETDEVICE_MAC_ADDR(_pst_dev)                    ((_pst_dev)->dev_addr)
#define OAL_NETDEVICE_TX_QUEUE_LEN(_pst_dev)                ((_pst_dev)->tx_queue_len)
#define OAL_NETDEVICE_TX_QUEUE_NUM(_pst_dev)                ((_pst_dev)->num_tx_queues)
#define OAL_NETDEVICE_TX_QUEUE(_pst_dev, _index)            ((_pst_dev)->_tx[_index])
#define OAL_NETDEVICE_DESTRUCTOR(_pst_dev)                  ((_pst_dev)->destructor)
#define OAL_NETDEVICE_TYPE(_pst_dev)                        ((_pst_dev)->type)
#define OAL_NETDEVICE_NAME(_pst_dev)                        ((_pst_dev)->name)
#define OAL_NETDEVICE_MASTER(_pst_dev)                      ((_pst_dev)->master)
#define OAL_NETDEVICE_QDISC(_pst_dev, pst_val)              ((_pst_dev)->qdisc = pst_val)
#define OAL_NETDEVICE_IFALIAS(_pst_dev)                     ((_pst_dev)->ifalias)
#define OAL_NETDEVICE_FLAGS(_pst_dev)                       ((_pst_dev)->flags)
#define OAL_NETDEVICE_WDEV(_pst_dev)                        ((_pst_dev)->ieee80211_ptr)
#define OAL_NETDEVICE_HEADROOM(_pst_dev)                    ((_pst_dev)->needed_headroom)
#define OAL_NETDEVICE_TAILROOM(_pst_dev)                    ((_pst_dev)->needed_tailroom)

#define OAL_NETDEVICE_ADDR_LEN(_pst_dev)                    ((_pst_dev)->addr_len)
#define OAL_NETDEVICE_WATCHDOG_TIMEO(_pst_dev)              ((_pst_dev)->watchdog_timeo)
#define OAL_NETDEVICE_HARD_HEADER_LEN(_pst_dev)             ((_pst_dev)->hard_header_len)

#define OAL_WIRELESS_DEV_NET_DEV(_pst_wireless_dev)         ((_pst_wireless_dev)->netdev)
#define OAL_WIRELESS_DEV_WIPHY(_pst_wireless_dev)           ((_pst_wireless_dev)->wiphy)
#define OAL_WIRELESS_DEV_IF_TYPE(_pst_wireless_dev)         ((_pst_wireless_dev)->iftype)

#define OAL_IFF_RUNNING         0x40    /* linux net_device flag宏定义，表示设备在运行 */
#define OAL_SIOCIWFIRSTPRIV     0x8BE0

/* iw_priv参数类型OAL封装 */
#define OAL_IW_PRIV_TYPE_BYTE   0x1000  /* Char as number */
#define OAL_IW_PRIV_TYPE_CHAR   0x2000  /* Char as character */
#define OAL_IW_PRIV_TYPE_INT    0x4000  /* 32 bits int */
#define OAL_IW_PRIV_TYPE_FLOAT  0x5000  /* struct iw_freq */
#define OAL_IW_PRIV_TYPE_ADDR   0x6000  /* struct sockaddr */
#define OAL_IW_PRIV_SIZE_FIXED  0x0800  /* Variable or fixed number of args */

/* Modes of operation */
#define OAL_IW_MODE_AUTO    0   /* Let the driver decides */
#define OAL_IW_MODE_ADHOC   1   /* Single cell network */
#define OAL_IW_MODE_INFRA   2   /* Multi cell network, roaming, ... */
#define OAL_IW_MODE_MASTER  3   /* Synchronisation master or Access Point */
#define OAL_IW_MODE_REPEAT  4   /* Wireless Repeater (forwarder) */
#define OAL_IW_MODE_SECOND  5   /* Secondary master/repeater (backup) */
#define OAL_IW_MODE_MONITOR 6   /* Passive monitor (listen only) */
#define OAL_IW_MODE_MESH    7   /* Mesh (IEEE 802.11s) network */

/* Transmit Power flags available */
#define OAL_IW_TXPOW_TYPE       0x00FF  /* Type of value */
#define OAL_IW_TXPOW_DBM        0x0000  /* Value is in dBm */
#define OAL_IW_TXPOW_MWATT      0x0001  /* Value is in mW */
#define OAL_IW_TXPOW_RELATIVE   0x0002  /* Value is in arbitrary units */
#define OAL_IW_TXPOW_RANGE      0x1000  /* Range of value between min/max */
#define OAL_IEEE80211_MAX_SSID_LEN          (32) /* 最大SSID长度 */
#define IEEE80211_MAX_SSID_LEN		        OAL_IEEE80211_MAX_SSID_LEN
#define OAL_NL80211_MAX_NR_CIPHER_SUITES    5
#define OAL_NL80211_MAX_NR_AKM_SUITES       2
#define OAL_MAX_SCAN_CHANNELS               40  /* 内核下发的最大扫描信道个数 */

#define OAL_ETH_SENDER_IP_ADDR_LEN       4  /* length of an Ethernet send ip address */
#define OAL_ETH_TARGET_IP_ADDR_LEN       4  /* length of an Ethernet target ip address */

/* ARP protocol opcodes. */
#define OAL_ARPOP_REQUEST   1       /* ARP request          */
#define OAL_ARPOP_REPLY     2       /* ARP reply            */
#define OAL_ARPOP_RREQUEST  3       /* RARP request         */
#define OAL_ARPOP_RREPLY    4       /* RARP reply           */
#define OAL_ARPOP_InREQUEST 8       /* InARP request        */
#define OAL_ARPOP_InREPLY   9       /* InARP reply          */
#define OAL_ARPOP_NAK       10      /* (ATM)ARP NAK         */

#define  OAL_IPPROTO_UDP     17         /* User Datagram Protocot */

#define  OAL_IPPROTO_ICMPV6  58         /* ICMPv6 */

struct oal_ether_header
{
    oal_uint8    auc_ether_dhost[ETHER_ADDR_LEN];
    oal_uint8    auc_ether_shost[ETHER_ADDR_LEN];
    oal_uint16   us_ether_type;
}__OAL_DECLARE_PACKED;
typedef struct oal_ether_header oal_ether_header_stru;

typedef struct oal_net_notify
{
    oal_uint32 ul_ip_addr;
    oal_uint32 ul_notify_type;
}oal_net_notify_stru;
typedef struct cfg80211_chan_def oal_cfg80211_chan_def;


/*****************************************************************************
 函 数 名  : oal_netif_running
 功能描述  : win32封装
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint32  oal_netif_running_func()
{
    return 0;
}

#define oal_netif_running(_pst_net_dev)             oal_netif_running_func()

/* 主机与网络字节序转换 */
#define OAL_HOST2NET_SHORT(_x)  OAL_SWAP_BYTEORDER_16(_x)
#define OAL_NET2HOST_SHORT(_x)  OAL_SWAP_BYTEORDER_16(_x)
#define OAL_HOST2NET_LONG(_x)   OAL_SWAP_BYTEORDER_32(_x)
#define OAL_NET2HOST_LONG(_x)   OAL_SWAP_BYTEORDER_32(_x)

#define oal_vlan_tx_tag_present(_skb)   ((_skb)->vlan_tci & 0x1000)
#define oal_vlan_tx_tag_get(_skb)       ((_skb)->vlan_tci & ~0x1000)

/* vlan宏定义 */
#define OAL_VLAN_VID_MASK           0x0fff      /* VLAN Identifier */
#define OAL_VLAN_PRIO_MASK          0xe000      /* Priority Code Point */
#define OAL_VLAN_PRIO_SHIFT         13

#define OAL_THIS_MODULE         OAL_PTR_NULL
#define OAL_MSG_DONTWAIT        0

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

#define NETDEV_UP               0x0001                      /* veto a device up/down */
#define NETDEV_DOWN             0x0002                      /* veto a device up/down */


typedef enum
{
    GFP_KERNEL,
    GFP_ATOMIC,

    OAL_GFP_BUTT
}oal_gfp_enum;
typedef oal_uint8 oal_gfp_enum_uint8;

typedef enum
{
    OAL_NETDEV_TX_OK     = 0x00,
    OAL_NETDEV_TX_BUSY   = 0x10,
    OAL_NETDEV_TX_LOCKED = 0x20,
}oal_net_dev_tx_enum;

enum {
    OAL_INET_ECN_NOT_ECT    = 0,
    OAL_INET_ECN_ECT_1      = 1,
    OAL_INET_ECN_ECT_0      = 2,
    OAL_INET_ECN_CE         = 3,
    OAL_INET_ECN_MASK       = 3,
};

typedef enum
{
    OAL_IEEE80211_BAND_2GHZ   = 0,
    OAL_IEEE80211_BAND_5GHZ   = 1,

    OAL_IEEE80211_BAND_BUTT
}oal_ieee80211_band_enum;
typedef oal_uint8 oal_ieee80211_band_enum_uint8;

typedef enum
{
    NL80211_AUTHTYPE_OPEN_SYSTEM = 0,
    NL80211_AUTHTYPE_SHARED_KEY,
    NL80211_AUTHTYPE_FT,
    NL80211_AUTHTYPE_NETWORK_EAP,
    NL80211_AUTHTYPE_SAE,

    /* keep last */
    __NL80211_AUTHTYPE_NUM,
    NL80211_AUTHTYPE_MAX = __NL80211_AUTHTYPE_NUM - 1,
    NL80211_AUTHTYPE_AUTOMATIC,

    NL80211_AUTHTYPE_BUTT
}oal_nl80211_auth_type_enum;
typedef oal_uint8 oal_nl80211_auth_type_enum_uint8;

enum cfg80211_signal_type {
    CFG80211_SIGNAL_TYPE_NONE,
    CFG80211_SIGNAL_TYPE_MBM,
    CFG80211_SIGNAL_TYPE_UNSPEC,
};

typedef oal_uint8 en_cfg80211_signal_type_uint8;

typedef struct oal_cpu_usage_stat
{
    oal_uint64 ull_user;
    oal_uint64 ull_nice;
    oal_uint64 ull_system;
    oal_uint64 ull_softirq;
    oal_uint64 ull_irq;
    oal_uint64 ull_idle;
    oal_uint64 ull_iowait;
    oal_uint64 ull_steal;
    oal_uint64 ull_guest;
}oal_cpu_usage_stat_stru;

typedef enum {
    NETIF_FLOW_CTRL_OFF,      // stop flow_ctrl, continue to transfer data to driver
    NETIF_FLOW_CTRL_ON,       // start flow_ctrl, stop transferring data to driver

    NETIF_FLOW_CTRL_BUTT
}netif_flow_ctrl_enum;
typedef oal_uint8 netif_flow_ctrl_enum_uint8;

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
#define LL_ALLOCATED_SPACE(dev) \
	((((dev)->hard_header_len+(dev)->needed_headroom+(dev)->needed_tailroom)&~(15)) + 16)

#define LL_RESERVED_SPACE(dev) \
        ((((dev)->hard_header_len+(dev)->needed_headroom)&~(15)) + 16)

#define OAL_LL_ALLOCATED_SPACE  LL_ALLOCATED_SPACE
typedef oal_uint32              oal_ip_addr_t;

typedef struct
{
  union {
            oal_uint8        u6_addr8[16];
            oal_uint16       u6_addr16[8];
            oal_uint32       u6_addr32[4];
        } in6_u;
#define s6_addr         in6_u.u6_addr8
#define s6_addr16       in6_u.u6_addr16
#define s6_addr32       in6_u.u6_addr32
}oal_in6_addr;


typedef struct
{
    oal_uint8           version:4,
                        priority:4;
    oal_uint8          flow_lbl[3];
    oal_uint16         payload_len;

    oal_uint8           nexthdr;
    oal_uint8           hop_limit;

    oal_in6_addr       saddr;
    oal_in6_addr       daddr;
}oal_ipv6hdr_stru;

#if 0
typedef struct
{
    oal_uint8          icmp6_type;
    oal_uint8          icmp6_code;
    oal_uint16         icmp6_cksum;
}oal_icmp6hdr_stru;
#endif

typedef struct
{
    oal_uint32		reserved:5,
    override:1,
    solicited:1,
    router:1,
    reserved2:24;
}icmpv6_nd_advt;


typedef struct
{
    oal_uint8          icmp6_type;
    oal_uint8          icmp6_code;
    oal_uint16         icmp6_cksum;
    union
    {
        oal_uint32			un_data32[1];
		oal_uint16			un_data16[2];
		oal_uint8			un_data8[4];
        icmpv6_nd_advt      u_nd_advt;
    }icmp6_dataun;

#define icmp6_solicited		icmp6_dataun.u_nd_advt.solicited
#define icmp6_override		icmp6_dataun.u_nd_advt.override
}oal_icmp6hdr_stru;

/* 多了4字节，记得减去4 */
typedef struct
{
    oal_icmp6hdr_stru	icmph;
    oal_in6_addr	    target;
    oal_uint8		    opt[1];
    oal_uint8		    rsv[3];
}oal_nd_msg_stru;

typedef struct
{
	oal_uint8		nd_opt_type;
	oal_uint8		nd_opt_len;
}oal_nd_opt_hdr;

typedef struct ieee80211_rate {
    oal_uint32 flags;
    oal_uint16 bitrate;
    oal_uint16 hw_value;
    oal_uint16 hw_value_short;
    oal_uint8  uc_rsv[2];
}oal_ieee80211_rate;

typedef struct ieee80211_channel_sw_ie {
    oal_uint8 mode;
    oal_uint8 new_ch_num;
    oal_uint8 count;
    oal_uint8 uc_rsv[1];
} oal_ieee80211_channel_sw_ie;

typedef struct ieee80211_msrment_ie {
    oal_uint8 token;
    oal_uint8 mode;
    oal_uint8 type;
    oal_uint8 request[1];
} oal_ieee80211_msrment_ie;


typedef struct ieee80211_mgmt {
    oal_uint16 frame_control;
    oal_uint16 duration;
    oal_uint8 da[6];
    oal_uint8 sa[6];
    oal_uint8 bssid[6];
    oal_uint16 seq_ctrl;
    union {
        struct {
            oal_uint16 auth_alg;
            oal_uint16 auth_transaction;
            oal_uint16 status_code;
            /* possibly followed by Challenge text */
            oal_uint8 variable[1];
            oal_uint8 uc_rsv[1];
        } auth;
        struct {
            oal_uint16 reason_code;
        }  deauth;
        struct {
            oal_uint16 capab_info;
            oal_uint16 listen_interval;
            /* followed by SSID and Supported rates */
            oal_uint8 variable[1];
            oal_uint8 uc_rsv[1];
        } assoc_req;
        struct {
            oal_uint16 capab_info;
            oal_uint16 status_code;
            oal_uint16 aid;
            /* followed by Supported rates */
            oal_uint8 variable[1];
            oal_uint8 uc_rsv[1];
        } assoc_resp, reassoc_resp;
        struct {
            oal_uint16 capab_info;
            oal_uint16 listen_interval;
            oal_uint8 current_ap[6];
            /* followed by SSID and Supported rates */
            oal_uint8 variable[1];
            oal_uint8 uc_rsv[1];
        } reassoc_req;
        struct {
            oal_uint16 reason_code;
        } disassoc;
        struct {
            oal_uint64 timestamp;
            oal_uint16 beacon_int;
            oal_uint16 capab_info;
            oal_uint8 uc_rsv[3];
            /* followed by some of SSID, Supported rates,
             * FH Params, DS Params, CF Params, IBSS Params, TIM */
            oal_uint8 variable[1];
        } beacon;

        struct {
            oal_uint64 timestamp;
            oal_uint16 beacon_int;
            oal_uint16 capab_info;
            oal_uint8 uc_rsv[3];
            /* followed by some of SSID, Supported rates,
             * FH Params, DS Params, CF Params, IBSS Params */
            oal_uint8 variable[1];
        } probe_resp;
        struct {
            oal_uint8 category;
            oal_uint8 uc_rsv[1];
            union {
                struct {
                    oal_uint8 action_code;
                    oal_uint8 dialog_token;
                    oal_uint8 status_code;
                    oal_uint8 variable[1];
                } wme_action;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 element_id;
                    oal_uint8 length;
                    oal_ieee80211_channel_sw_ie sw_elem;
                } chan_switch;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 dialog_token;
                    oal_uint8 element_id;
                    oal_uint8 length;
                    oal_ieee80211_msrment_ie msr_elem;
                } measurement;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 dialog_token;
                    oal_uint16 capab;
                    oal_uint16 timeout;
                    oal_uint16 start_seq_num;
                } addba_req;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 dialog_token;
                    oal_uint16 status;
                    oal_uint16 capab;
                    oal_uint16 timeout;
                } addba_resp;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 uc_rsv[1];
                    oal_uint16 params;
                    oal_uint16 reason_code;
                } delba;
                struct{
                    oal_uint8 action_code;
                    /* Followed in plink_confirm by status
                     * code, AID and supported rates,
                     * and directly by supported rates in
                     * plink_open and plink_close
                     */
                    oal_uint8 variable[1];

                    /* capab_info for open and confirm,
                     * reason for close
                     */
                    oal_uint16 aux;


                } plink_action;
                struct{
                    oal_uint8 action_code;
                    oal_uint8 variable[1];
                } mesh_action;
                struct {
                    oal_uint8 action;
                    oal_uint8 uc_rsv[1];
                    oal_uint8 trans_id[OAL_WLAN_SA_QUERY_TR_ID_LEN];
                } sa_query;
                struct {
                    oal_uint8 action;
                    oal_uint8 smps_control;
                    oal_uint8 uc_rsv[2];
                } ht_smps;
            } u;
        } action;
    } u;
} oal_ieee80211_mgmt;


enum nl80211_band {
    NL80211_BAND_2GHZ,
    NL80211_BAND_5GHZ,
};

enum ieee80211_band {
    IEEE80211_BAND_2GHZ = NL80211_BAND_2GHZ,
    IEEE80211_BAND_5GHZ = NL80211_BAND_5GHZ,

    /* keep last */
    IEEE80211_NUM_BANDS
};

enum nl80211_channel_type {
    NL80211_CHAN_NO_HT,
    NL80211_CHAN_HT20,
    NL80211_CHAN_HT40MINUS,
    NL80211_CHAN_HT40PLUS
};
typedef enum nl80211_channel_type oal_nl80211_channel_type;

enum nl80211_key_type {
    NL80211_KEYTYPE_GROUP,
    NL80211_KEYTYPE_PAIRWISE,
    NL80211_KEYTYPE_PEERKEY,
    NUM_NL80211_KEYTYPES
};
typedef enum nl80211_key_type oal_nl80211_key_type;

/* 表示wiphy 结构中对应的参数是否被修改 */
enum wiphy_params_flags {
    WIPHY_PARAM_RETRY_SHORT     = 1 << 0,
    WIPHY_PARAM_RETRY_LONG      = 1 << 1,
    WIPHY_PARAM_FRAG_THRESHOLD  = 1 << 2,
    WIPHY_PARAM_RTS_THRESHOLD   = 1 << 3,
    WIPHY_PARAM_COVERAGE_CLASS  = 1 << 4,
};
typedef enum wiphy_params_flags             oal_wiphy_params_flags;

struct vif_params {
       oal_uint8    *mesh_id;
       oal_int32     mesh_id_len;
       oal_int32     use_4addr;
       oal_uint8    *macaddr;
};
typedef struct vif_params                   oal_vif_params_stru;
enum station_info_flags {
    STATION_INFO_INACTIVE_TIME = 1<<0,
    STATION_INFO_RX_BYTES      = 1<<1,
    STATION_INFO_TX_BYTES      = 1<<2,
    STATION_INFO_LLID          = 1<<3,
    STATION_INFO_PLID          = 1<<4,
    STATION_INFO_PLINK_STATE   = 1<<5,
    STATION_INFO_SIGNAL        = 1<<6,
    STATION_INFO_TX_BITRATE    = 1<<7,
    STATION_INFO_RX_PACKETS    = 1<<8,
    STATION_INFO_TX_PACKETS    = 1<<9,
	STATION_INFO_TX_RETRIES		= 1<<10,
	STATION_INFO_TX_FAILED		= 1<<11,
	STATION_INFO_RX_DROP_MISC	= 1<<12,
	STATION_INFO_SIGNAL_AVG		= 1<<13,
	STATION_INFO_RX_BITRATE		= 1<<14,
	STATION_INFO_BSS_PARAM          = 1<<15,
	STATION_INFO_CONNECTED_TIME	= 1<<16,
	STATION_INFO_ASSOC_REQ_IES	= 1<<17,
	STATION_INFO_STA_FLAGS		= 1<<18,
	STATION_INFO_BEACON_LOSS_COUNT	= 1<<19,
	STATION_INFO_T_OFFSET		= 1<<20,
	STATION_INFO_LOCAL_PM		= 1<<21,
	STATION_INFO_PEER_PM		= 1<<22,
	STATION_INFO_NONPEER_PM		= 1<<23,
	STATION_INFO_RX_BYTES64		= 1<<24,
	STATION_INFO_TX_BYTES64		= 1<<25,

};
typedef struct ieee80211_channel {
    enum ieee80211_band band;
    oal_uint16          center_freq;
    oal_uint16          hw_value;
    oal_uint32          flags;
    oal_int32           max_antenna_gain;
    oal_int32           max_power;
    oal_bool_enum       beacon_found;
    oal_uint32          orig_flags;
    oal_int32           orig_mag;
    oal_int32           orig_mpwr;
}oal_ieee80211_channel;

struct ieee80211_mcs_info {
    oal_uint8   rx_mask[IEEE80211_HT_MCS_MASK_LEN];
    oal_uint16  rx_highest;
    oal_uint8   tx_params;
    oal_uint8   reserved[3];
};

typedef struct ieee80211_sta_ht_cap {
    oal_uint16          cap; /* use IEEE80211_HT_CAP_ */
    oal_bool_enum_uint8 ht_supported;
    oal_uint8           ampdu_factor;
    oal_uint8           ampdu_density;
    oal_uint8           auc_rsv[3];
    struct ieee80211_mcs_info mcs;
}oal_ieee80211_sta_ht_cap;

typedef struct ieee80211_supported_band {
    oal_ieee80211_channel   *channels;
    oal_ieee80211_rate      *bitrates;
    enum ieee80211_band      band;
    oal_int32                n_channels;
    oal_int32                n_bitrates;
    oal_ieee80211_sta_ht_cap ht_cap;
}oal_ieee80211_supported_band;

struct beacon_parameters {
    oal_uint8 *head, *tail;
    oal_int32 interval, dtim_period;
    oal_int32 head_len, tail_len;
};
typedef struct beacon_parameters    oal_beacon_parameters;

/* lm add new code begin */
/* 3.10内核中下发的修改beacon帧参数的结构体 */
struct cfg80211_beacon_data
{
	oal_uint8  *head, *tail;
	oal_uint8  *beacon_ies;
	oal_uint8  *proberesp_ies;
	oal_uint8  *assocresp_ies;
	oal_uint8  *probe_resp;
	oal_uint32  head_len, tail_len;
	oal_uint32  beacon_ies_len;
	oal_uint32  proberesp_ies_len;
	oal_uint32  assocresp_ies_len;
	oal_uint32  probe_resp_len;
};
typedef struct cfg80211_beacon_data oal_beacon_data_stru;

/* 3.10内核中下发的修改bss信息的结构体 */
struct bss_parameters
{
	oal_int32    use_cts_prot;
	oal_int32    use_short_preamble;
	oal_int32    use_short_slot_time;
	oal_uint8 *basic_rates;
	oal_uint8  basic_rates_len;
	oal_int32    ap_isolate;
	oal_int32    ht_opmode;
	oal_int8   p2p_ctwindow;
	oal_int8   p2p_opp_ps;
};
typedef struct bss_parameters oal_bss_parameters;

struct cfg80211_chan_def
{
	oal_ieee80211_channel   *chan;
	oal_nl80211_channel_type width;
	oal_int32                center_freq1;
	oal_int32                center_freq2;
};
typedef struct cfg80211_chan_def oal_cfg80211_chan_def;

struct  cfg80211_crypto_settings
{
    oal_uint32              wpa_versions;
    oal_uint32              cipher_group;
    oal_int32               n_ciphers_pairwise;
    oal_uint32              ciphers_pairwise[OAL_NL80211_MAX_NR_CIPHER_SUITES];
    oal_int32               n_akm_suites;
    oal_uint32              akm_suites[OAL_NL80211_MAX_NR_AKM_SUITES];
    oal_bool_enum_uint8     control_port;
    oal_uint8               auc_arry[3];
};
typedef struct cfg80211_crypto_settings oal_cfg80211_crypto_settings;

struct mac_address
{
	oal_uint8 addr[6];
};

struct cfg80211_acl_data
{
	oal_uint32 acl_policy;
	oal_int32 n_acl_entries;
	struct mac_address mac_addrs[1];
};

/* 3.10新内核下发的配置ap的信息 */
struct cfg80211_ap_settings {
	oal_cfg80211_chan_def            chandef;
	oal_beacon_data_stru             beacon;
	oal_int32                        beacon_interval;
	oal_int32                        dtim_period;
	oal_uint8                       *ssid;
	oal_int32                        ssid_len;
	oal_int32                        hidden_ssid;
	oal_cfg80211_crypto_settings     crypto;
	oal_uint32                       privacy;
	oal_nl80211_auth_type_enum_uint8 auth_type;
	oal_int32                        inactivity_timeout;
	oal_uint8                        p2p_ctwindow;
	oal_uint32                       p2p_opp_ps;
	const struct cfg80211_acl_data  *acl;
	oal_uint32                       radar_required;
};
typedef struct cfg80211_ap_settings oal_ap_settings_stru;
/* lm add new code end */

struct cfg80211_update_ft_ies_params {
    oal_uint16                   md;
	const oal_uint8             *ie;
	oal_uint32                   ie_len;
};
typedef struct cfg80211_update_ft_ies_params oal_cfg80211_update_ft_ies_stru;

struct cfg80211_ft_event_params {
	const oal_uint8            *ies;
	oal_uint32                  ies_len;
	const oal_uint8            *target_ap;
	const oal_uint8            *ric_ies;
	oal_uint32                  ric_ies_len;
};

typedef struct cfg80211_ft_event_params oal_cfg80211_ft_event_stru;

enum wiphy_flags {
    WIPHY_FLAG_CUSTOM_REGULATORY    = BIT(0),
    WIPHY_FLAG_STRICT_REGULATORY    = BIT(1),
    WIPHY_FLAG_DISABLE_BEACON_HINTS = BIT(2),
    WIPHY_FLAG_NETNS_OK             = BIT(3),
    WIPHY_FLAG_PS_ON_BY_DEFAULT     = BIT(4),
    WIPHY_FLAG_4ADDR_AP             = BIT(5),
    WIPHY_FLAG_4ADDR_STATION        = BIT(6),
    WIPHY_FLAG_SUPPORTS_SCHED_SCAN  = BIT(11),
    WIPHY_FLAG_HAVE_AP_SME          = BIT(17),
    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL= BIT(21),
};

enum nl80211_iftype {
    NL80211_IFTYPE_UNSPECIFIED,
    NL80211_IFTYPE_ADHOC,
    NL80211_IFTYPE_STATION,
    NL80211_IFTYPE_AP,
    NL80211_IFTYPE_AP_VLAN,
    NL80211_IFTYPE_WDS,
    NL80211_IFTYPE_MONITOR,
    NL80211_IFTYPE_MESH_POINT,
    NL80211_IFTYPE_P2P_CLIENT,
    NL80211_IFTYPE_P2P_GO,
    NL80211_IFTYPE_P2P_DEVICE,

    /* keep last */
    __NL80211_IFTYPE_AFTER_LAST,
    NL80211_IFTYPE_MAX = __NL80211_IFTYPE_AFTER_LAST - 1
};

typedef struct ieee80211_txrx_stypes {
    oal_uint16 tx;
    oal_uint16 rx;
}oal_ieee80211_txrx_stypes;


/* 管制域相关结构体定义 */
#define MHZ_TO_KHZ(freq) ((freq) * 1000)
#define KHZ_TO_MHZ(freq) ((freq) / 1000)
#define DBI_TO_MBI(gain) ((gain) * 100)
#define MBI_TO_DBI(gain) ((gain) / 100)
#define DBM_TO_MBM(gain) ((gain) * 100)
#define MBM_TO_DBM(gain) ((gain) / 100)

#define REG_RULE(start, end, bw, gain, eirp, reg_flags) \
{                                                       \
    {MHZ_TO_KHZ(start), MHZ_TO_KHZ(end), MHZ_TO_KHZ(bw)},  \
    {DBI_TO_MBI(gain), DBM_TO_MBM(eirp)},  \
    (reg_flags),        \
}

struct ieee80211_freq_range {
    oal_uint32 start_freq_khz;
    oal_uint32 end_freq_khz;
    oal_uint32 max_bandwidth_khz;
};

struct ieee80211_power_rule {
    oal_uint32 max_antenna_gain;
    oal_uint32 max_eirp;
};

struct ieee80211_reg_rule {
    struct ieee80211_freq_range freq_range;
    struct ieee80211_power_rule power_rule;
    oal_uint32 flags;
};

typedef struct{
    oal_uint32      n_reg_rules;
    oal_int8        alpha2[2];
    oal_uint8       auc_rsv[2];
    struct ieee80211_reg_rule reg_rules[10];
}oal_ieee80211_regdomain_stru;


/* 此结构体成员命名是为了保持跟linux一致 */
typedef struct oal_wiphy_tag
{
    oal_uint8   perm_addr[6];
    oal_uint8   addr_mask[6];
    oal_uint32  flags;
    en_cfg80211_signal_type_uint8        signal_type;
    oal_uint8                            max_scan_ssids;
    oal_uint16                           interface_modes;
    oal_uint16                           max_scan_ie_len;
    oal_uint8                            auc_rsv[2];
    oal_int32                            n_cipher_suites;

    OAL_CONST oal_uint32                *cipher_suites;
    oal_uint32                           frag_threshold;
    oal_uint32                           rts_threshold;
    oal_ieee80211_supported_band        *bands[IEEE80211_NUM_BANDS];
    oal_uint8                            priv[4];

}oal_wiphy_stru;

typedef struct oal_cfg80211_pmksa_tag
{
    oal_uint8 *bssid;
    oal_uint8 *pmkid;

}oal_cfg80211_pmksa_stru;

typedef struct oal_key_params_tag
{
    oal_uint8 *key;
    oal_uint8 *seq;
    oal_int32  key_len;
    oal_int32  seq_len;
    oal_uint32 cipher;
}oal_key_params_stru;


typedef oal_uint32       oal_work_struct_stru;
typedef oal_ieee80211_mgmt       oal_ieee80211_mgmt_stru;
typedef oal_uint32       oal_cfg80211_bss_stru;
/*typedef oal_uint32       oal_station_info_stru;*/


/**
 * enum nl80211_reg_rule_flags - regulatory rule flags
 *
 * @NL80211_RRF_NO_OFDM: OFDM modulation not allowed
 * @NL80211_RRF_NO_CCK: CCK modulation not allowed
 * @NL80211_RRF_NO_INDOOR: indoor operation not allowed
 * @NL80211_RRF_NO_OUTDOOR: outdoor operation not allowed
 * @NL80211_RRF_DFS: DFS support is required to be used
 * @NL80211_RRF_PTP_ONLY: this is only for Point To Point links
 * @NL80211_RRF_PTMP_ONLY: this is only for Point To Multi Point links
 * @NL80211_RRF_PASSIVE_SCAN: passive scan is required
 * @NL80211_RRF_NO_IBSS: no IBSS is allowed
 */
 #define NL80211_RRF_NO_OFDM         (1<<0)
 #define NL80211_RRF_NO_CCK          (1<<1)
 #define NL80211_RRF_NO_INDOOR       (1<<2)
 #define NL80211_RRF_NO_OUTDOOR      (1<<3)
 #define NL80211_RRF_DFS             (1<<4)
 #define NL80211_RRF_PTP_ONLY        (1<<5)
 #define NL80211_RRF_PTMP_ONLY       (1<<6)
 #define NL80211_RRF_PASSIVE_SCAN    (1<<7)
 #define NL80211_RRF_NO_IBSS         (1<<8)


typedef struct oal_netbuf_tag
{
    struct oal_netbuf_tag       *next;
    struct oal_netbuf_tag       *prev;

    struct oal_net_device       *dev;
	unsigned short		queue_mapping;

    oal_uint8       cb[OAL_WIN32_NETBUF_CB_SIZE];
    oal_uint32      len;
    oal_uint32      cloned;
    oal_uint16      protocol;
    oal_uint16      vlan_tci;
    oal_uint8      *transport_header;
    oal_uint8      *network_header;
    oal_uint8      *mac_header;
    oal_uint8      *tail;
    oal_uint8      *end;
    oal_uint8      *head;
    oal_uint8      *data;
    oal_uint32      truesize;
    oal_atomic      users;
	oal_uint8      *p_mem_head;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    union {
        oal_uint32  mark;
        oal_uint32  dropcount;
    };
#endif
}oal_netbuf_stru;

/* net device统计信息结构体 */
typedef struct
{
    oal_uint32   rx_packets;     /* total packets received   */
    oal_uint32   tx_packets;     /* total packets transmitted    */
    oal_uint32   rx_bytes;       /* total bytes received     */
    oal_uint32   tx_bytes;       /* total bytes transmitted  */
    oal_uint32   rx_errors;      /* bad packets received     */
    oal_uint32   tx_errors;      /* packet transmit problems */
    oal_uint32   rx_dropped;     /* no space in linux buffers    */
    oal_uint32   tx_dropped;     /* no space available in linux  */
    oal_uint32   multicast;      /* multicast packets received   */
    oal_uint32   collisions;

    /* detailed rx_errors: */
    oal_uint32   rx_length_errors;
    oal_uint32   rx_over_errors;     /* receiver ring buff overflow  */
    oal_uint32   rx_crc_errors;      /* recved pkt with crc error    */
    oal_uint32   rx_frame_errors;    /* recv'd frame alignment error */
    oal_uint32   rx_fifo_errors;     /* recv'r fifo overrun      */
    oal_uint32   rx_missed_errors;   /* receiver missed packet   */

    /* detailed tx_errors */
    oal_uint32   tx_aborted_errors;
    oal_uint32   tx_carrier_errors;
    oal_uint32   tx_fifo_errors;
    oal_uint32   tx_heartbeat_errors;
    oal_uint32   tx_window_errors;

    /* for cslip etc */
    oal_uint32   rx_compressed;
    oal_uint32   tx_compressed;
}oal_net_device_stats_stru;

typedef struct
{
    oal_netbuf_stru *pst_next;
    oal_netbuf_stru *pst_prev;
    oal_uint32       ul_num;
    oal_uint8        auc_resv[4]; /* ,此处添加4个保留字节是为了让整个结构体与linux下大小一致 */
}oal_netbuf_head_stru;

typedef struct
{
    oal_uint32   ul_fake;
    oal_uint8   *ifr_data;
}oal_ifreq_stru;

typedef struct
{
    oal_uint32  ul_handle;
}oal_qdisc_stru;

/* iw_handler_def结构体win32封装 */
typedef struct
{
    oal_uint16       cmd;        /* Wireless Extension command */
    oal_uint16       flags;      /* More to come ;-) */
}oal_iw_request_info_stru;

typedef struct
{
  void       *pointer;    /* Pointer to the data  (in user space) */
  oal_uint16  length;     /* number of fields or size in bytes */
  oal_uint16  flags;      /* Optional params */
}oal_iw_point_stru;

typedef struct
{
    oal_int32      value;      /* The value of the parameter itself */
    oal_uint8      fixed;      /* Hardware should not use auto select */
    oal_uint8      disabled;   /* Disable the feature */
    oal_uint16     flags;      /* Various specifc flags (if any) */
}oal_iw_param_stru;

typedef struct
{
    oal_int32        m;      /* Mantissa */
    oal_int16        e;      /* Exponent */
    oal_uint8        i;      /* List index (when in range struct) */
    oal_uint8        flags;  /* Flags (fixed/auto) */
}oal_iw_freq_stru;

typedef struct
{
    oal_uint8        qual;       /* link quality (%retries, SNR, %missed beacons or better...) */
    oal_uint8        level;      /* signal level (dBm) */
    oal_uint8        noise;      /* noise level (dBm) */
    oal_uint8        updated;    /* Flags to know if updated */
}oal_iw_quality_stru;

typedef struct
{
    oal_uint16      sa_family;      /* address family, AF_xxx   */
    oal_int8        sa_data[14];    /* 14 bytes of protocol address */
}oal_sockaddr_stru;

typedef union
{
    /* Config - generic */
    char                name[OAL_IF_NAME_SIZE];
    oal_iw_point_stru   essid;      /* Extended network name */
    oal_iw_param_stru   nwid;       /* network id (or domain - the cell) */
    oal_iw_freq_stru    freq;       /* frequency or channel : * 0-1000 = channel * > 1000 = frequency in Hz */
    oal_iw_param_stru   sens;       /* signal level threshold */
    oal_iw_param_stru   bitrate;    /* default bit rate */
    oal_iw_param_stru   txpower;    /* default transmit power */
    oal_iw_param_stru   rts;        /* RTS threshold threshold */
    oal_iw_param_stru   frag;       /* Fragmentation threshold */
    oal_uint32          mode;       /* Operation mode */
    oal_iw_param_stru   retry;      /* Retry limits & lifetime */
    oal_iw_point_stru   encoding;   /* Encoding stuff : tokens */
    oal_iw_param_stru   power;      /* PM duration/timeout */
    oal_iw_quality_stru qual;       /* Quality part of statistics */
    oal_sockaddr_stru   ap_addr;    /* Access point address */
    oal_sockaddr_stru   addr;       /* Destination address (hw/mac) */
    oal_iw_param_stru   param;      /* Other small parameters */
    oal_iw_point_stru   data;       /* Other large parameters */
}oal_iwreq_data_union;

typedef oal_int32 (*oal_iw_handler)(struct oal_net_device *dev, oal_iw_request_info_stru *info, oal_iwreq_data_union *wrqu, char *extra);

/* 私有IOCTL接口信息 */
typedef struct
{
    oal_uint32       cmd;                       /* ioctl命令号 */
    oal_uint16       set_args;                  /* 类型和参数字符个数 */
    oal_uint16       get_args;                  /* 类型和参数字符个数 */
    oal_int8         name[OAL_IF_NAME_SIZE];    /* 私有命令名 */
}oal_iw_priv_args_stru;

typedef struct
{
    oal_uint32  ul_fake;
}oal_iw_statistics_stru;

typedef struct
{
    OAL_CONST oal_iw_handler    *standard;
    oal_uint16                   num_standard;
    oal_uint16                   num_private;

    oal_uint8                    auc_resv[2];
    oal_uint16                   num_private_args;

    OAL_CONST oal_iw_handler    *private_win32;

    const oal_iw_priv_args_stru *private_args;
    oal_iw_statistics_stru*    (*get_wireless_stats)(struct oal_net_device *dev);
}oal_iw_handler_def_stru;

struct oal_net_device;
struct wireless_dev;

typedef struct
{
    oal_uint32    type;
}oal_net_bridge_port;

typedef enum {
  PBUF_TRANSPORT,
  PBUF_IP,
  PBUF_LINK,
  PBUF_RAW
} pbuf_layer;

typedef enum {
  PBUF_RAM, /* pbuf data is stored in RAM */
  PBUF_ROM, /* pbuf data is stored in ROM */
  PBUF_REF, /* pbuf comes from the pbuf pool */
  PBUF_POOL /* pbuf payload refers to RAM */
} pbuf_type;
#define WIFI_DRIVER_IF                  6
#define  ETHARP_HWADDR_LEN              6

/* Function pointer of driver send function */
typedef void (*drv_send_fn)(struct netif *netif, struct pbuf *p);
typedef void (*drv_notify_fn)(struct netif *netif, oal_uint32 notify_type);

struct netif
{
  /** pointer to next in linked list */
  struct netif *next;
  oal_ip_addr_t ip_addr;

  void *state;

  drv_send_fn drv_send;
  drv_notify_fn drv_notify;

  /** maximum transfer unit (in bytes) */
  oal_uint16 mtu;
  /** number of bytes used in hwaddr */
  oal_uint8 hwaddr_len;
  /** link level hardware address of this interface */
  oal_uint8 hwaddr[6];

  oal_uint16 link_layer_type;
  /** flags (see NETIF_FLAG_ above) */
  oal_uint8 flags;
};
typedef struct netif            oal_lwip_netif;
struct pbuf
{
  /** next pbuf in singly linked pbuf chain */
  struct pbuf *next;

  /** pointer to the actual data in the buffer */
  oal_uint8 *payload;

  /**
   * total length of this buffer and all next buffers in chain
   * belonging to the same packet.
   *
   * For non-queue packet chains this is the invariant:
   * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
   */
  oal_uint16 tot_len;

  /** length of this buffer */
  oal_uint16 len;

  /** pbuf_type as u8_t instead of enum to save space */
  oal_uint8 /*pbuf_type*/ type;

  /** misc flags */
  oal_uint8 flags;

  /**
   * the reference count always equals the number of pointers
   * that refer to this pbuf. This can be pointers from an application,
   * the stack itself, or pbuf->next pointers from a chain.
   */
  oal_uint16 ref;
};
typedef struct pbuf             oal_lwip_buf;
#define ETH_PAD_SIZE    2


#if BYTE_ORDER == BIG_ENDIAN
/** Set an IP address given by the four byte-parts */
#define IP4_ADDR(ipaddr, a,b,c,d) \
        *(oal_uint32 *)ipaddr = ((oal_uint32)((a) & 0xff) << 24) | \
                         ((oal_uint32)((b) & 0xff) << 16) | \
                         ((oal_uint32)((c) & 0xff) << 8)  | \
                          (oal_uint32)((d) & 0xff)
#else
/** Set an IP address given by the four byte-parts.
    Little-endian version that prevents the use of htonl. */
#define IP4_ADDR(ipaddr, a,b,c,d) \
        *(oal_uint32 *)ipaddr = ((oal_uint32)((d) & 0xff) << 24) | \
                         ((oal_uint32)((c) & 0xff) << 16) | \
                         ((oal_uint32)((b) & 0xff) << 8)  | \
                          (oal_uint32)((a) & 0xff)
#endif
#define OAL_IP4_ADDR                        IP4_ADDR

typedef struct _oal_hisi_eapol_stru
{
    oal_bool_enum    en_register;
    oal_uint8        auc_reserve[3];
    void            *context;
    void           (*notify_callback)(void *, void *context);
    oal_netbuf_head_stru     st_eapol_skb_head;
}oal_hisi_eapol_stru;

typedef struct oal_net_device
{
    oal_int8                    name[OAL_IF_NAME_SIZE];
    oal_void                   *ml_priv;
    struct oal_net_device_ops  *netdev_ops;
    oal_uint                    last_rx;
    oal_uint                    flags;
    oal_iw_handler_def_stru    *wireless_handlers;
    oal_int8                    dev_addr[6];
    oal_uint8                   auc_resv[2];
    oal_int32                   tx_queue_len;
    oal_int16                   hard_header_len;
    oal_int16                   type;
    oal_int16		            needed_headroom;
	oal_int16		            needed_tailroom;
    struct oal_net_device      *master;
    struct wireless_dev        *ieee80211_ptr;
    oal_qdisc_stru             *qdisc;
    oal_uint8                  *ifalias;
    oal_uint8                   addr_len;
    oal_uint8                   auc_resv2[3];
    oal_int                     watchdog_timeo;
    oal_net_device_stats_stru   stats;
    oal_uint32                  mtu;
    oal_void                  (*destructor)(struct oal_net_device *);
    oal_void                    *priv;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_net_bridge_port        *br_port;
#endif
    oal_hisi_eapol_stru         st_hisi_eapol;  /* EAPOL报文收发数据结构 */
    oal_lwip_netif             *pst_lwip_netif; /* LWIP协议栈数据结构 */
}oal_net_device_stru;

typedef struct wireless_dev
{
    struct oal_net_device       *netdev;
    oal_wiphy_stru              *wiphy;
    enum nl80211_iftype          iftype;
    /* 1102新内核新增字段 add by lm */
    oal_cfg80211_chan_def        preset_chandef;
}oal_wireless_dev_stru;


typedef struct oal_net_device_ops
{
    oal_int32                   (*ndo_init)(oal_net_device_stru *);
    oal_int32                   (*ndo_open)(struct oal_net_device*);
    oal_int32                   (*ndo_stop)(struct oal_net_device*);
    oal_net_dev_tx_enum         (*ndo_start_xmit) (oal_netbuf_stru*, struct oal_net_device*);
    oal_void                    (*ndo_set_multicast_list)(struct oal_net_device*);
    oal_net_device_stats_stru*  (*ndo_get_stats)(oal_net_device_stru *);
    oal_int32                   (*ndo_do_ioctl)(struct oal_net_device*,oal_ifreq_stru *, oal_int32);
    oal_int32                   (*ndo_change_mtu)(struct oal_net_device*, oal_int32);
    oal_int32                   (*ndo_set_mac_address)(struct oal_net_device *, oal_void *);
    oal_int32                   (*ndo_select_queue)(struct oal_net_device *pst_dev, oal_netbuf_stru *);
    oal_int32                   (*ndo_netif_notify)(struct oal_net_device *, oal_net_notify_stru *);
}oal_net_device_ops_stru;

/* VLAN以太网头 win32封装 */
typedef struct
{
    oal_uint8       h_dest[6];
    oal_uint8       h_source[6];
    oal_uint16      h_vlan_proto;
    oal_uint16      h_vlan_TCI;
    oal_uint16      h_vlan_encapsulated_proto;
}oal_vlan_ethhdr_stru;

/* scan相关参数 */
typedef struct oal_ieee80211_channel_tag
{
    oal_ieee80211_band_enum_uint8   band;
    oal_bool_enum_uint8             beacon_found;
    oal_uint8                       auc_arry[2];

    oal_uint16                      center_freq;
    oal_uint16                      hw_value;

    oal_uint32                      flags;
    oal_int32                       max_antenna_gain;
    oal_int32                       max_power;
    oal_uint32                      orig_flags;
    oal_int32                       orig_mag;
    oal_int32                       orig_mpwr;
}oal_ieee80211_channel_stru;

typedef struct oal_station_parameters_tag
{
    oal_uint8 *supported_rates;
    struct net_device *vlan;
    oal_uint32 sta_flags_mask, sta_flags_set;
    oal_int32 listen_interval;
    oal_uint16 aid;
    oal_uint8 supported_rates_len;
    oal_uint8 plink_action;
    struct ieee80211_ht_cap *ht_capa;
}oal_station_parameters_stru;

typedef struct rate_info
{
    oal_uint8    flags;
    oal_uint8    mcs;
    oal_uint16   legacy;
    oal_uint8    nss;
}oal_rate_info_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
typedef struct oal_station_info_tag
{
    oal_uint32 filled;
    oal_uint32 inactive_time;
    oal_uint32 rx_bytes;
    oal_uint32 tx_bytes;
	oal_uint32 tx_retries;
	oal_uint32 tx_failed;
	oal_uint32 rx_dropped_misc;
    oal_uint16 llid;
    oal_uint16 plid;
    oal_uint8 plink_state;
    oal_int8 signal;
    oal_uint8 auc_resv[2];
    oal_rate_info_stru txrate;
    oal_uint32 rx_packets;
    oal_uint32 tx_packets;

    oal_int32 generation;
}oal_station_info_stru;
#else
struct sta_bss_parameters {
	oal_uint8  flags;
	oal_uint8  dtim_period;
	oal_uint16 beacon_interval;
};

struct nl80211_sta_flag_update {
	oal_uint32 mask;
	oal_uint32 set;
};

enum nl80211_mesh_power_mode {
	NL80211_MESH_POWER_UNKNOWN,
	NL80211_MESH_POWER_ACTIVE,
	NL80211_MESH_POWER_LIGHT_SLEEP,
	NL80211_MESH_POWER_DEEP_SLEEP,

	__NL80211_MESH_POWER_AFTER_LAST,
	NL80211_MESH_POWER_MAX = __NL80211_MESH_POWER_AFTER_LAST - 1
};

typedef struct oal_station_info_tag
{
	oal_uint32 filled;
	oal_uint32 connected_time;
	oal_uint32 inactive_time;
	oal_uint64 rx_bytes;
	oal_uint64 tx_bytes;
	oal_uint16 llid;
	oal_uint16 plid;
	oal_uint8  plink_state;
	oal_int8   signal;
	oal_int8   signal_avg;
	oal_rate_info_stru txrate;
	oal_rate_info_stru rxrate;
	oal_uint32 rx_packets;
	oal_uint32 tx_packets;
	oal_uint32 tx_retries;
	oal_uint32 tx_failed;
	oal_uint32 rx_dropped_misc;
	struct sta_bss_parameters      bss_param;
	struct nl80211_sta_flag_update sta_flags;

	oal_int32 generation;

    oal_uint8   *assoc_req_ies;
    oal_uint32   assoc_req_ies_len;

	oal_uint32 beacon_loss_count;
	oal_int64  t_offset;
	enum nl80211_mesh_power_mode local_pm;
	enum nl80211_mesh_power_mode peer_pm;
	enum nl80211_mesh_power_mode nonpeer_pm;
}oal_station_info_stru;
#endif

typedef struct nlattr
{
    oal_uint16    nla_len;
	oal_uint16    nla_type;
}oal_nlattr_stru;

typedef struct oal_genl_family
{
    oal_uint32		id;
	oal_uint32		hdrsize;
	oal_uint8		name[16];
	oal_uint32		version;
	oal_uint32		maxattr;
	oal_nlattr_stru **	attrbuf;	/* private */
	oal_list_head_stru	ops_list;	/* private */
	oal_list_head_stru	family_list;	/* private */
	oal_list_head_stru	mcast_groups;	/* private */
}oal_genl_family_stru;

typedef struct oal_cfg80211_ssid_tag
{
    oal_uint8   ssid[OAL_IEEE80211_MAX_SSID_LEN];
    oal_uint8   ssid_len;
    oal_uint8   auc_arry[3];

}oal_cfg80211_ssid_stru;

/* 打桩内核下发扫描请求命令参数 */
typedef struct oal_cfg80211_scan_request_tag
{
    oal_cfg80211_ssid_stru *ssids;
    oal_int32               n_ssids;
    oal_uint32              n_channels;
    oal_uint32              ie_len;

    /* internal */
    oal_wiphy_stru         *wiphy;
    oal_net_device_stru    *dev;

    struct wireless_dev    *wdev;

    oal_bool_enum_uint8     aborted;
    oal_uint8               auc_arry[3];

    const oal_uint8        *ie;

    /* keep last */
    oal_ieee80211_channel_stru  *channels[OAL_MAX_SCAN_CHANNELS];
}oal_cfg80211_scan_request_stru;

typedef struct cfg80211_match_set {
	oal_cfg80211_ssid_stru ssid;
}oal_cfg80211_match_set;

/* 打桩内核下发调度扫描请求命令参数 */
typedef struct oal_cfg80211_sched_scan_request_tag
{
    oal_cfg80211_ssid_stru *ssids;
	oal_int32               n_ssids;
	oal_uint32              n_channels;
	oal_uint32              interval;
	const oal_uint8        *ie;
	oal_uint32              ie_len;
	oal_uint32              flags;
	oal_cfg80211_match_set *match_sets;
	oal_int32               n_match_sets;
	oal_int32               rssi_thold;

	/* internal */
	oal_wiphy_stru         *wiphy;
	oal_net_device_stru    *dev;
	oal_uint64              scan_start;

	/* keep last */
	oal_ieee80211_channel_stru *channels[0];
}oal_cfg80211_sched_scan_request_stru;


typedef struct  oal_cfg80211_crypto_settings_tag
{
    oal_uint32              wpa_versions;
    oal_uint32              cipher_group;
    oal_int32               n_ciphers_pairwise;
    oal_uint32              ciphers_pairwise[OAL_NL80211_MAX_NR_CIPHER_SUITES];
    oal_int32               n_akm_suites;
    oal_uint32              akm_suites[OAL_NL80211_MAX_NR_AKM_SUITES];

    oal_bool_enum_uint8     control_port;
    oal_uint8               auc_arry[3];
}oal_cfg80211_crypto_settings_stru;

/**
 * enum nl80211_mfp - Management frame protection state
 * @NL80211_MFP_NO: Management frame protection not used
 * @NL80211_MFP_REQUIRED: Management frame protection required
 */

typedef enum
{
	NL80211_MFP_NO,
	NL80211_MFP_REQUIRED,

    NL80211_MFP_BUTT
}oal_nl80211_mfp_enum;
typedef oal_uint8 oal_nl80211_mfp_enum_uint8;

/* 打桩内核下发关联请求命令参数 */
typedef struct oal_cfg80211_connect_params_tag
{
    oal_ieee80211_channel_stru          *channel;

    oal_uint8                           *bssid;
    oal_uint8                           *ssid;
    oal_uint8                           *ie;

    oal_uint32                          ssid_len;
    oal_uint32                          ie_len;
    oal_cfg80211_crypto_settings_stru   crypto;
    const oal_uint8                     *key;

    oal_nl80211_auth_type_enum_uint8    auth_type;
    oal_bool_enum_uint8                 privacy;
    oal_uint8                           key_len;
    oal_uint8                           key_idx;
    oal_nl80211_mfp_enum_uint8          mfp;
    oal_uint8                           auc_resv[3];

}oal_cfg80211_connect_params_stru;

/* 内核下发cfg的接口函数 */
typedef struct oal_cfg80211_ops_tag
{
    oal_int32 (*add_key)(oal_wiphy_stru *wiphy, oal_net_device_stru *netdev,
                    oal_uint8 key_index,
                    oal_bool_enum            en_pairwise,
                    OAL_CONST oal_uint8 *mac_addr, oal_key_params_stru *params);
    oal_int32 (*get_key)(oal_wiphy_stru *wiphy, oal_net_device_stru *netdev,
                    oal_uint8 key_index,
                    oal_bool_enum            en_pairwise,
                    OAL_CONST oal_uint8 *mac_addr, void *cookie,
                    oal_void (*callback)(oal_void *cookie, oal_key_params_stru *key));
    oal_int32 (*del_key)(oal_wiphy_stru *wiphy, oal_net_device_stru *netdev,
                    oal_uint8 key_index,
                    oal_bool_enum            en_pairwise,
                    OAL_CONST oal_uint8 *mac_addr);
    oal_int32 (*set_default_key)(oal_wiphy_stru *wiphy,oal_net_device_stru *netdev, oal_uint8 key_index,
                    oal_bool_enum            en_unicast,
                    oal_bool_enum            en_multicast
                    );
    oal_int32 (*set_default_mgmt_key)(oal_wiphy_stru *wiphy,oal_net_device_stru *netdev, oal_uint8 key_index,
                    oal_bool_enum            en_unicast,
                    oal_bool_enum            en_multicast
                    );
    //oal_int32 (*set_pmksa)(oal_wiphy_stru *wiphy, oal_net_device_stru *netdev,oal_cfg80211_pmksa_stru *pst_pmksa);
    oal_int32 (*scan)(oal_wiphy_stru *pst_wiphy,  oal_net_device_stru *pst_dev,
            oal_cfg80211_scan_request_stru *pst_request);
    oal_int32 (*connect)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev,oal_cfg80211_connect_params_stru *pst_sme);
    oal_int32 (*disconnect)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev,oal_uint16 us_reason_code);
    oal_int32 (*set_channel)(oal_wiphy_stru *pst_wiphy, oal_ieee80211_channel *pst_chan, oal_nl80211_channel_type en_channel_type);
    oal_int32 (*set_wiphy_params)(oal_wiphy_stru *pst_wiphy, oal_uint32 ul_changed);
    oal_int32 (*add_beacon)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev, oal_beacon_parameters *pst_info);
    oal_int32 (*change_virtual_intf)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev,
            enum nl80211_iftype en_type, oal_uint32 *pul_flags, oal_vif_params_stru *pst_params);
    oal_int32 (*add_station)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev, oal_uint8 *puc_mac, oal_station_parameters_stru *pst_sta_parms);
    oal_int32 (*del_station)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev, oal_uint8 *puc_mac);
    oal_int32 (*change_station)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev, oal_uint8 *puc_mac, oal_station_parameters_stru *pst_sta_parms);
    oal_int32 (*get_station)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_dev, oal_uint8 *puc_mac, oal_station_info_stru *pst_sta_info);
    oal_int32 (*dump_station)(oal_wiphy_stru *wiphy, oal_net_device_stru *dev, oal_int32 idx, oal_uint8 *mac, oal_station_info_stru *pst_sta_info);
    /* lm add new code begin */
    oal_int32 (*change_beacon)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev, oal_beacon_data_stru *pst_beacon_info);
    oal_int32 (*start_ap)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev, oal_ap_settings_stru *pst_ap_settings);
    oal_int32 (*stop_ap)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev);
    oal_int32 (*change_bss)(oal_wiphy_stru *pst_wiphy, oal_net_device_stru *pst_netdev, oal_bss_parameters *pst_bss_params);
    oal_int32 (*set_power_mgmt)(oal_wiphy_stru  *pst_wiphy,oal_net_device_stru *pst_ndev, oal_bool_enum  enabled,oal_int32 ul_timeout);
    /* lm add new code end */
}oal_cfg80211_ops_stru;

typedef struct
{
    oal_uint32      nlmsg_len;      /* 消息长度，包括首部在内 */
    oal_uint16      nlmsg_type;     /* 消息内容的类型 */
    oal_uint16      nlmsg_flags;    /* 附加的标志 */
    oal_uint32      nlmsg_seq;      /* 序列号 */
    oal_uint32      nlmsg_pid;      /* 发送进程的端口ID */
}oal_nlmsghdr_stru;

typedef struct
{
    oal_uint32   pid;
    oal_uint32   uid;
    oal_uint32   gid;
}oal_ucred_stru;

typedef struct
{
    oal_uint32   cap[2];
}oal_kernel_capt_stru;

typedef struct
{
    oal_uint32   num_syms;
}oal_module_stru;

struct ethhdr
{
    oal_uint8    h_dest[ETHER_ADDR_LEN];     /* destination eth addr */
    oal_uint8    h_source[ETHER_ADDR_LEN];   /* source ether addr    */
    oal_uint16   h_proto;                    /* packet type ID field */
}__OAL_DECLARE_PACKED;
typedef struct ethhdr oal_ethhdr;

typedef oal_uint32 nf_hookfn(oal_uint32 hooknum,
                   oal_netbuf_stru *skb,
                   const oal_net_device_stru *in,
                   const oal_net_device_stru *out,
                   int (*okfn)(oal_netbuf_stru *));

typedef struct
{
    /* oal_dlist_head_stru    list; */

    /* User fills in from here down. */
    nf_hookfn             *hook;
    oal_module_stru       *owner;
    oal_uint8              pf;
    oal_uint8              auc_resv[3];
    oal_uint32             hooknum;
    /* Hooks are ordered in ascending priority. */
    oal_int32              priority;
}oal_nf_hook_ops_stru;

typedef struct
{
    oal_ucred_stru          creds;
    oal_uint32              pid;
    oal_uint32              dst_group;
    oal_kernel_capt_stru    eff_cap;
    oal_uint32              loginuid;
    oal_uint32              sessionid;
    oal_uint32              sid;
}oal_netlink_skb_parms_stru;

typedef struct genl_multicast_group
{
	oal_genl_family_stru	*family;	/* private */
	oal_list_head_stru	list;		/* private */
	oal_int8			name[16];
	oal_uint32			id;
}oal_genl_multicast_group_stru;

typedef struct cfg80211_registered_device
{
	oal_cfg80211_ops_stru *ops;
	oal_list_head_stru list;
	oal_wiphy_stru     wiphy;

}oal_cfg80211_registered_device_stru;

/* netlink相关 */
#define OAL_NLMSG_ALIGNTO               4
#define OAL_NLMSG_ALIGN(_len)           ( ((_len)+OAL_NLMSG_ALIGNTO-1) & ~(OAL_NLMSG_ALIGNTO-1) )
#define OAL_NLMSG_HDRLEN                ((oal_int32) OAL_NLMSG_ALIGN(OAL_SIZEOF(oal_nlmsghdr_stru)))
#define OAL_NLMSG_LENGTH(_len)          ((_len)+OAL_NLMSG_ALIGN(OAL_NLMSG_HDRLEN))
#define OAL_NLMSG_SPACE(_len)           OAL_NLMSG_ALIGN(OAL_NLMSG_LENGTH(_len))
#define OAL_NLMSG_DATA(_nlh)            ((oal_void*)(((char*)_nlh) + OAL_NLMSG_LENGTH(0)))
#define OAL_NLMSG_PAYLOAD(_nlh, _len)   ((_nlh)->nlmsg_len - OAL_NLMSG_SPACE((_len)))

/*lint -e545*/
#define OAL_NETLINK_CB(_skb)            (*(oal_netlink_skb_parms_stru*)&((_skb)->cb))

#define OAL_AF_BRIDGE   7   /* Multiprotocol bridge     */
#define OAL_PF_BRIDGE   OAL_AF_BRIDGE

/* Bridge Hooks */
/* After promisc drops, checksum checks. */
#define OAL_NF_BR_PRE_ROUTING   0
/* If the packet is destined for this box. */
#define OAL_NF_BR_LOCAL_IN      1
/* If the packet is destined for another interface. */
#define OAL_NF_BR_FORWARD       2
/* Packets coming from a local process. */
#define OAL_NF_BR_LOCAL_OUT     3
/* Packets about to hit the wire. */
#define OAL_NF_BR_POST_ROUTING  4
/* Not really a hook, but used for the ebtables broute table */
#define OAL_NF_BR_BROUTING      5
#define OAL_NF_BR_NUMHOOKS      6

/* Responses from hook functions. */
#define OAL_NF_DROP             0
#define OAL_NF_ACCEPT           1
#define OAL_NF_STOLEN           2
#define OAL_NF_QUEUE            3
#define OAL_NF_REPEAT           4
#define OAL_NF_STOP             5
#define OAL_NF_MAX_VERDICT      OAL_NF_STOP

enum nf_br_hook_priorities {
    NF_BR_PRI_FIRST = INT_MIN,
    NF_BR_PRI_NAT_DST_BRIDGED = -300,
    NF_BR_PRI_FILTER_BRIDGED = -200,
    NF_BR_PRI_BRNF = 0,
    NF_BR_PRI_NAT_DST_OTHER = 100,
    NF_BR_PRI_FILTER_OTHER = 200,
    NF_BR_PRI_NAT_SRC = 300,
    NF_BR_PRI_LAST = INT_MAX,
};

typedef struct
{
    int         sk_wmem_queued;
}oal_sock_stru;
extern oal_sock_stru g_st_sock;

typedef struct
{
    oal_proc_dir_entry_stru   *proc_net;
}oal_net_stru;

extern oal_net_stru  g_st_init_net;
#define OAL_INIT_NET   g_st_init_net

typedef struct
{
    oal_uint16 us_ar_hrd;   /* format of hardware address */
    oal_uint16 us_ar_pro;   /* format of protocol address */

    oal_uint8  uc_ar_hln;   /* length of hardware address */
    oal_uint8  uc_ar_pln;   /* length of protocol address */
    oal_uint16 us_ar_op;    /* ARP opcode (command) */

    oal_uint8  auc_ar_sha[ETHER_ADDR_LEN];           /* sender hardware address */
    oal_uint8  auc_ar_sip[ETH_SENDER_IP_ADDR_LEN];   /* sender IP address */
    oal_uint8  auc_ar_tha[ETHER_ADDR_LEN];           /* target hardware address */
    oal_uint8  auc_ar_tip[ETH_TARGET_IP_ADDR_LEN];   /* target IP address */
}oal_eth_arphdr_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_delist(oal_netbuf_head_stru *pst_list_head);
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_free(oal_netbuf_stru *pst_netbuf);
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_peek_tail(oal_netbuf_head_stru *pst_head);
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_delete(oal_netbuf_stru *pst_buf, oal_netbuf_head_stru *pst_list_head);
OAL_STATIC OAL_INLINE oal_void oal_netbuf_copy_queue_mapping(oal_netbuf_stru  *to, const oal_netbuf_stru *from)
{
    //to->queue_mapping = from->queue_mapping;
}


OAL_STATIC OAL_INLINE oal_void oal_netif_set_up(struct netif *netif)
{

}

OAL_STATIC OAL_INLINE oal_int32 oal_dhcp_start(struct netif *netif)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_void oal_dhcp_stop(struct netif *netif)
{

}

OAL_STATIC OAL_INLINE oal_void oal_netif_set_down(struct netif *netif)
{
}

OAL_STATIC OAL_INLINE void skb_reset_tail_pointer(struct netif *skb)
{
}

OAL_STATIC OAL_INLINE oal_int32 oal_dhcp_succ_check(struct netif *netif)
{
    return 0;
}

/**
 * is_broadcast_ether_addr - Determine if the Ethernet address is broadcast
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Return true if the address is the broadcast address.
 */
OAL_STATIC OAL_INLINE  oal_bool_enum_uint8 oal_is_broadcast_ether_addr(const oal_uint8 *addr)
{
	return (addr[0] & addr[1] & addr[2] & addr[3] & addr[4] & addr[5]) == 0xff;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_put
 功能描述  : 在缓冲区尾部增加数据
 输入参数  : pst_netbuf: 缓冲区结构体指针
             ul_len: 需要增加数据的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_put(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    oal_uint8 *puc_temp;

    puc_temp = pst_netbuf->tail;

    pst_netbuf->tail += ul_len;
    pst_netbuf->len  += ul_len;

    if (OAL_UNLIKELY(pst_netbuf->tail > pst_netbuf->end))
    {
        OAL_IO_PRINT("oal_netbuf_put, pst_netbuf->tail > pst_netbuf->end");
    }

    return puc_temp;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_push
 功能描述  : 在缓冲区开头增加数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  *oal_netbuf_push(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    pst_netbuf->data -= ul_len;
    pst_netbuf->len  += ul_len;

    if (OAL_UNLIKELY(pst_netbuf->data < pst_netbuf->head))
    {
        OAL_IO_PRINT("oal_netbuf_push, pst_netbuf->data < pst_netbuf->head");
    }

    return pst_netbuf->data;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_pull
 功能描述  : 从skb头部取出数据
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_pull(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    if (ul_len > pst_netbuf->len)
    {
        return OAL_PTR_NULL;
    }

    pst_netbuf->len -= ul_len;

    return (pst_netbuf->data += ul_len);
}
/*****************************************************************************
 函 数 名  : oal_ieee80211_channel_to_frequency
 功能描述  : 将信道转换成频率
 输入参数  : oal_int32 l_channel      :信道号
             enum ieee80211_band band :频段
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 oal_ieee80211_channel_to_frequency(oal_int32 l_channel, enum ieee80211_band band)
{
    /* see 802.11 17.3.8.3.2 and Annex J
        * there are overlapping channel numbers in 5GHz and 2GHz bands */
    if (l_channel <= 0)
    {
        return 0; /* not supported */
    }

    switch (band)
    {
        case IEEE80211_BAND_2GHZ:
        {
            if (14 == l_channel)
            {
                return 2484;
            }
            else if (l_channel < 14)
            {
                return 2407 + l_channel * 5;
            }
            break;
        }

        case IEEE80211_BAND_5GHZ:
        {
            if (l_channel >= 182 && l_channel <= 196)
            {
                return 4000 + l_channel * 5;
            }
            else
            {
                return 5000 + l_channel * 5;
            }
        }
        default:
            /* not supported other BAND*/
            return 0;
    }

    /* not supported */
    return 0;
}
/*****************************************************************************
 函 数 名  : oal_ieee80211_frequency_to_channel
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2013年11月1日
    作    者   :  
    修改内容   : 修改函数，将4.9G 频段正常转换

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_ieee80211_frequency_to_channel(oal_int32 l_center_freq)
{
    oal_int32 l_channel;

    /* see 802.11 17.3.8.3.2 and Annex J */
    if (2484 == l_center_freq)
    {
        l_channel = 14;
    }
    else if (l_center_freq < 2484)
    {
        l_channel = (l_center_freq - 2407) / 5;
    }
    else if (l_center_freq >= 4910 && l_center_freq <= 4980)
    {
        l_channel = (l_center_freq - 4000) / 5;
    }
    else if (l_center_freq <= 45000) /* DMG band lower limit */
    {
        l_channel = (l_center_freq - 5000) / 5;
    }
    else if (l_center_freq >= 58320 && l_center_freq <= 64800)
    {
        l_channel = (l_center_freq - 56160) / 2160;
    }
    else
    {
        l_channel = 0;
    }
    return l_channel;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_get_bitfield
 功能描述  : 识别IP报文的大小端
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月9日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 oal_netbuf_get_bitfield(oal_void)
{
    union bitfield
    {
        oal_uint8 uc_byte;
        struct  {
            oal_uint8 high:4,
                      low :4;
                } bits;
    } un_bitfield;

    un_bitfield.uc_byte = 0x12;
    if (0x2 == un_bitfield.bits.low)
    {
        return OAL_BITFIELD_LITTLE_ENDIAN;
    }
    else
    {
        return OAL_BITFIELD_BIG_ENDIAN;
    }
}

OAL_STATIC OAL_INLINE oal_void oal_set_netbuf_prev(oal_netbuf_stru *pst_buf, oal_netbuf_stru *pst_prev)
{
   pst_buf->prev = pst_prev;
}

OAL_STATIC OAL_INLINE oal_netbuf_stru *oal_get_netbuf_prev(oal_netbuf_stru *pst_buf)
{
    return pst_buf->prev;
}

OAL_STATIC OAL_INLINE oal_void oal_set_netbuf_tail(oal_netbuf_stru *pst_buf,  oal_uint8  *tail)
{
    pst_buf->tail = tail;
}
OAL_STATIC OAL_INLINE oal_void oal_set_netbuf_next(oal_netbuf_stru *pst_buf,  oal_netbuf_stru  *next)
{
    if (OAL_PTR_NULL == pst_buf)
    {
        return;
    }
    else
    {
        pst_buf->next = next;
    }
}

OAL_STATIC OAL_INLINE oal_netbuf_stru *oal_get_netbuf_next(oal_netbuf_stru *pst_buf)
{
    return pst_buf->next;
}

OAL_STATIC OAL_INLINE oal_void oal_set_single_netbuf_tail(oal_netbuf_stru *pst_netbuf,oal_uint8 *puc_tail)
{
    pst_netbuf->tail = puc_tail;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_addlist
 功能描述  : skb链表从头部入队
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_addlist(oal_netbuf_head_stru *pst_list_head,
                                                              oal_netbuf_stru* netbuf)
{   /*stub function, to be implement*/
    return;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_tail
 功能描述  : add a netbuf to skb list
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_list_tail(oal_netbuf_head_stru *list, oal_netbuf_stru *newsk)
{
    /*stub function, to be implement*/
    return;
}

OAL_STATIC OAL_INLINE oal_int32 oal_netbuf_expand_head(oal_netbuf_stru *skb,
                                                        oal_int32 nhead, oal_int32 ntail,
		                                                oal_int32 gfp_mask)
{
    /*stub function, to be implement*/
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_delist_tail
 功能描述  : remove skb from list tail
 输入参数  : @head: the place to add it in the first list
 输出参数  : The list at @list is reinitialised
 返 回 值  : the netbuf removed from the list
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_delist_tail( oal_netbuf_head_stru *head)
{
	oal_netbuf_stru *pst_netbuf = oal_netbuf_peek_tail(head);
	if (pst_netbuf)
		oal_netbuf_delete(pst_netbuf, head);
	return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_splice_sync
 功能描述  : move head buffs to list
 输入参数  : @list: the new list to add
             @head: the place to add it in the first list
 输出参数  : The list at @list is reinitialised
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_splice_sync(oal_netbuf_head_stru *list, oal_netbuf_head_stru *head)
{
    oal_netbuf_stru* netbuf;
    for(;;)
    {
        netbuf = oal_netbuf_delist_tail(head);
        if(NULL == netbuf)
        {
            break;
        }
        oal_netbuf_addlist(list, netbuf);
    }
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_purge
 功能描述  : skb链表清空
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_list_purge(oal_netbuf_head_stru *pst_list_head)
{
    oal_netbuf_stru* netbuf = NULL;
    for(;;)
    {
        netbuf = oal_netbuf_delist(pst_list_head);
        if(netbuf)
            oal_netbuf_free(netbuf);
    }
    return;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_tail
 功能描述  : join two skb lists and reinitialise the emptied list
 输入参数  : @list: the new list to add
             @head: the place to add it in the first list
 输出参数  : The list at @list is reinitialised
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_splice_init(oal_netbuf_head_stru *list, oal_netbuf_head_stru *head)
{
    /*stub function, to be implement*/
    return;
}
/*****************************************************************************
 函 数 名  : oal_netbuf_queue_splice_tail_init
 功能描述  : join two skb lists and reinitialise the emptied list
 输入参数  : @list: the new list to add
             @head: the place to add it in the first list
 输出参数  : The list at @list is reinitialised
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_queue_splice_tail_init(oal_netbuf_head_stru *list, oal_netbuf_head_stru *head)
{
    /*stub function, to be implement*/
    return;
}



/*****************************************************************************
 函 数 名  : oal_netbuf_head_init
 功能描述  : init netbuf list
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_head_init(oal_netbuf_head_stru *list)
{
    return;
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define oal_br_should_route_hook

/*****************************************************************************
 函 数 名  : oal_nf_unregister_hooks
 功能描述  : 注销网桥钩子函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_nf_unregister_hooks(oal_nf_hook_ops_stru *pst_nf_hook_ops, oal_uint32 ul_num)
{

}

/*****************************************************************************
 函 数 名  : oal_nf_register_hooks
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nf_register_hooks(oal_nf_hook_ops_stru *pst_nf_hook_ops, oal_uint32 ul_num)
{
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oal_br_get_port_type
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_br_get_port_type(oal_net_bridge_port *pst_port)
{
    return (pst_port->type);
}

/*****************************************************************************
 函 数 名  : oal_eth_hdr
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014??月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_ethhdr *oal_eth_hdr(oal_netbuf_stru *pst_netbuf)
{
    return (oal_ethhdr *)pst_netbuf->mac_header;
}

#define OAL_RCU_ASSIGN_POINTER(_p, _v)

#endif

/*****************************************************************************
 函 数 名  : oal_get_cpu_stat
 功能描述  : get cpu stat
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_get_cpu_stat(oal_cpu_usage_stat_stru *pst_cpu_stat)
{

}


extern oal_net_device_stru  *g_past_net_device[];

/*****************************************************************************
 函 数 名  : oal_ieee80211_get_channel
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_ieee80211_channel_stru *oal_ieee80211_get_channel(oal_wiphy_stru *pst_wiphy,oal_int32 ul_freq)
{
    oal_ieee80211_channel_stru *pst_ieee80211_channel;

    pst_ieee80211_channel = OAL_PTR_NULL;

    return pst_ieee80211_channel;
}

/*****************************************************************************
 函 数 名  : oal_eth_type_trans
 功能描述  : 获取协议模式
 输入参数  : pst_netbuf: skb指针
             pst_device: net device结构体指针
 输出参数  : 无
 返 回 值  : 协议模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint16 oal_eth_type_trans(oal_netbuf_stru *pst_netbuf, oal_net_device_stru *pst_device)
{
    oal_netbuf_pull(pst_netbuf, OAL_SIZEOF(oal_ether_header_stru));

    return 0;
}
/*****************************************************************************
 函 数 名  : oal_ether_setup
 功能描述  : ether dev建立
 输入参数  : net device引用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void oal_ether_setup(oal_net_device_stru *p_net_device)
{
    return;
}

/*****************************************************************************
 函 数 名  : oal_dev_get_by_name
 功能描述  : 根据名字寻找netdevice
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_net_device_stru* oal_dev_get_by_name(const oal_int8 *pc_name)
{
    oal_uint32   u_i;

    for (u_i = 0; u_i < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; u_i++)
    {
        if (OAL_PTR_NULL != g_past_net_device[u_i])
        {
            if ( !(oal_strcmp(g_past_net_device[u_i]->name, pc_name)))
            {
                return g_past_net_device[u_i];
            }
        }
    }

    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : oal_dev_put
 功能描述  : 调用oal_dev_get_by_name后需要调用dev_put,是net_dev的引用计数减1
 输入参数  : _pst_dev: 指向net_dev的指针
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#define oal_dev_put(_pst_dev)

//#ifdef _PRE_WLAN_FEATURE_FLOWCTL
/*****************************************************************************
 函 数 名  : oal_net_alloc_netdev_mqs
 功能描述  : 分配net device
 输入参数  : net device引用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_net_device_stru * oal_net_alloc_netdev_mqs(oal_uint32 ul_sizeof_priv, oal_int8 *puc_name,
                                                  oal_void *p_set_up, oal_uint32 ul_txqs, oal_uint32 ul_rxqs)
{
    oal_net_device_stru *pst_net_dev;
    oal_uint32           ul_size;

    ul_size = OAL_STRLEN(puc_name) + 1; /* 包括'\0' */

    pst_net_dev = (oal_net_device_stru *)oal_memalloc(OAL_SIZEOF(oal_net_device_stru));

    OAL_MEMZERO(pst_net_dev, OAL_SIZEOF(oal_net_device_stru));

    /* 将name保存到netdeivce */
    oal_memcopy(pst_net_dev->name, puc_name, ul_size);

    return pst_net_dev;
}

/*****************************************************************************
 函 数 名  : oal_net_tx_wake_all_queues
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_tx_wake_all_queues(oal_net_device_stru *pst_dev)
{
    return;
}


/*****************************************************************************
 函 数 名  : oal_net_tx_stop_all_queues
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_tx_stop_all_queues(oal_net_device_stru *pst_dev)
{
    return;
}

/*****************************************************************************
 函 数 名  : oal_net_wake_subqueue
 功能描述  : wake网络设备的某个subqueue
 输入参数  :
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_wake_subqueue(oal_net_device_stru *pst_dev, oal_uint16 us_queue_idx)
{
    return;
}


/*****************************************************************************
 函 数 名  : oal_net_stop_subqueue
 功能描述  : 暂停网络设备的某个subqueue
 输入参数  :
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_stop_subqueue(oal_net_device_stru *pst_dev, oal_uint16 us_queue_idx)
{
    return;
}

//#endif

/*****************************************************************************
 函 数 名  : oal_net_alloc_netdev
 功能描述  : 分配net device
 输入参数  : net device引用
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_net_device_stru * oal_net_alloc_netdev(oal_uint32 ul_sizeof_priv, oal_int8 *puc_name,
                                                  oal_void *p_set_up)
{
    oal_net_device_stru *pst_net_dev;
    oal_uint32           ul_size;

    ul_size = OAL_STRLEN(puc_name) + 1; /* 包括'\0' */

    pst_net_dev = (oal_net_device_stru *)oal_memalloc(OAL_SIZEOF(oal_net_device_stru));

    OAL_MEMZERO(pst_net_dev, OAL_SIZEOF(oal_net_device_stru));

    /* 将name保存到netdeivce */
    oal_memcopy(pst_net_dev->name, puc_name, ul_size);

    return pst_net_dev;
}

/*****************************************************************************
 函 数 名  : oal_net_close_dev
 功能描述  : down调 netdev
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_net_close_dev(oal_net_device_stru *pst_netdev)
{
    return;
}


/*****************************************************************************
 函 数 名  : oal_net_free_netdev
 功能描述  : 释放网络设备
 输入参数  : ul_sizeof_priv: 私有结构空间长度
           : puc_name 设备名称
           : p_set_up:启动函数指针
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_free_netdev(oal_net_device_stru *pst_netdev)
{
    if (OAL_PTR_NULL == pst_netdev)
    {
        return ;
    }

    if (OAL_PTR_NULL != pst_netdev->priv)
    {
        oal_free((oal_void *)pst_netdev->priv);
    }

    oal_free((oal_void *)pst_netdev);
}

/*****************************************************************************
 函 数 名  : oal_net_device_priv
 功能描述  : 返回netdev的私有成员
 输入参数  : pst_net_dev: net device 结构体指针
 输出参数  : 无
 返 回 值  : priv成员
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void* oal_net_device_priv(oal_net_device_stru *pst_net_dev)
{
    return pst_net_dev->ml_priv;
}

/*****************************************************************************
 函 数 名  : oal_net_device_open
 功能描述  : net device的open函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32  oal_net_device_open(oal_net_device_stru *pst_dev)
{
    pst_dev->flags |= OAL_IFF_RUNNING;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_close
 功能描述  : net device的close函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_close(oal_net_device_stru *pst_dev)
{

    pst_dev->flags &= ~OAL_IFF_RUNNING;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_set_macaddr
 功能描述  : net device的设置mac地址函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_set_macaddr(oal_net_device_stru *pst_dev, oal_void *pst_addr)
{

    oal_sockaddr_stru *pst_mac;

    pst_mac = (oal_sockaddr_stru *)pst_addr;

    oal_memcopy((oal_void *)pst_dev->dev_addr, (oal_void *)pst_mac->sa_data, 6);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_init
 功能描述  : net device的初始化函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_init(oal_net_device_stru *pst_dev)
{

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_get_stats
 功能描述  : net device的统计函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 统计结果指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_net_device_stats_stru *oal_net_device_get_stats(oal_net_device_stru *pst_dev)
{
    oal_net_device_stats_stru *pst_stats;

    pst_stats = &pst_dev->stats;
    pst_stats->tx_errors     = 0;
    pst_stats->tx_dropped    = 0;
    pst_stats->tx_packets    = 0;
    pst_stats->rx_packets    = 0;
    pst_stats->rx_errors     = 0;
    pst_stats->rx_dropped    = 0;
    pst_stats->rx_crc_errors = 0;

    return pst_stats;
}

/*****************************************************************************
 函 数 名  : oal_net_device_ioctl
 功能描述  : net device的ioctl函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 统计结果指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_ioctl(oal_net_device_stru *pst_dev, oal_ifreq_stru *pst_ifr, oal_int32 ul_cmd)
{
    return -OAL_EINVAL;
}

/*****************************************************************************
 函 数 名  : oal_net_device_multicast_list
 功能描述  : net device的multicast函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 统计结果指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_multicast_list(oal_net_device_stru *pst_dev)
{

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_change_mtu
 功能描述  : net device的change_mtu函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 统计结果指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32 oal_net_device_change_mtu(oal_net_device_stru *pst_dev, oal_int32 l_mtu)
{

    pst_dev->mtu = (oal_uint32)l_mtu;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_net_device_hardstart
 功能描述  : net device的hardstart函数
 输入参数  : net device指针
 输出参数  : 无
 返 回 值  : 统计结果指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_INLINE oal_int32 oal_net_device_hardstart(oal_netbuf_stru *pst_skb, oal_net_device_stru *pst_dev)
{

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oal_net_register_netdev
 功能描述  : 注册网络设备
 输入参数  : pst_net_dev: net device 结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_int32  oal_net_register_netdev(oal_net_device_stru *pst_net_dev)
{
    oal_int32    u_i;

    if (OAL_PTR_NULL == pst_net_dev)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (u_i = 0; u_i < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; u_i++)
    {
        if (OAL_PTR_NULL == g_past_net_device[u_i])
        {
            g_past_net_device[u_i] = pst_net_dev;

            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}



/*****************************************************************************
 函 数 名  : oal_net_unregister_netdev
 功能描述  : 去注册网络设备
 输入参数  : p_net_device: net device 结构体指针
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_net_unregister_netdev(oal_net_device_stru *p_net_device)
{
    oal_uint32    u_i;

    if (OAL_PTR_NULL == p_net_device)
    {
        return;
    }

    for (u_i = 0; u_i < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; u_i++)
    {
        if (g_past_net_device[u_i] == p_net_device)
        {
            g_past_net_device[u_i] = OAL_PTR_NULL;
            /*linux下操作系统会释放netdev，windows下需自己释放*/
            oal_net_free_netdev(p_net_device);
            return;
        }
    }

}

/*****************************************************************************
 函 数 名  : oal_netbuf_reserve
 功能描述  : 将报文结构体的data指针和tail指针同时下移
 输入参数  : pst_netbuf报文结构体指针
             len: 预留长度
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_netbuf_reserve(oal_netbuf_stru *pst_netbuf, oal_int32 l_len)
{
    pst_netbuf->data += l_len;
    pst_netbuf->tail += l_len;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_alloc
 功能描述  : 为netbuf申请内存
 输入参数  : pst_netbuf: 报文结构体指针
             ul_size: 分配内存的大小
             l_reserve: data跟指针头之间要预留的长度
             ul_align: 需要几字节对齐
 输出参数  : 无
 返 回 值  : 成功返回结构体指针；失败返回OAL_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_netbuf_stru  *oal_netbuf_alloc(oal_uint32 ul_size, oal_int32 l_reserve, oal_int32 l_align)
{
    oal_int32        l_offset;
    oal_netbuf_stru *pst_netbuf;

    /* 防止字节对齐造成分配大小比预期的小 */
    if (l_align)
    {
        ul_size += (oal_uint32)(l_align - 1);
    }

    /* 分配结构体空间 */
    pst_netbuf = (oal_netbuf_stru *)oal_memalloc(OAL_SIZEOF(oal_netbuf_stru));

    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_PTR_NULL;
    }
    OAL_MEMZERO(pst_netbuf, OAL_SIZEOF(oal_netbuf_stru));

    /* 分配数据空间 */
    pst_netbuf->head = (oal_uint8 *)oal_memalloc(ul_size);

    if (OAL_PTR_NULL == pst_netbuf->head)
    {
        oal_free(pst_netbuf);

        return OAL_PTR_NULL;
    }

    /* 结构体初始化 */
    OAL_MEMZERO(pst_netbuf->head, ul_size);

    pst_netbuf->data                = pst_netbuf->head;
    pst_netbuf->tail                = pst_netbuf->head;
    pst_netbuf->len                 = 0;

    if (ul_size >= 2400)
    {
        pst_netbuf->truesize        = 2636;     /* = WLAN_MEM_NETBUF_TRUE_SIZE3 */
    }
    else if (ul_size >= 1514)            /* WLAN_MEM_NETBUF_SIZE2 */
    {
        pst_netbuf->truesize        = 1736;     /* = WLAN_MEM_NETBUF_TRUE_SIZE2 */
    }
    else if (ul_size >= 1024)            /* WLAN_MEM_NETBUF_SIZE2 */
    {
        pst_netbuf->truesize        = 1037;     /* = WLAN_MEM_NETBUF_TRUE_SIZE2 */
    }
    else
    {
        pst_netbuf->truesize        = 232;      /* = WLAN_MEM_NETBUF_TRUE_SIZE1 */
    }

    pst_netbuf->users               = 1;
    pst_netbuf->end                 = pst_netbuf->head + ul_size;
    pst_netbuf->cloned              = 0;
    pst_netbuf->transport_header    = pst_netbuf->head;
    pst_netbuf->network_header      = pst_netbuf->head;
    pst_netbuf->mac_header          = pst_netbuf->head;

    /* note: alloc doesn't take responsibility if reserve unaligns the data pointer */
    oal_netbuf_reserve(pst_netbuf, l_reserve);

    /* 字节对齐 */
    if(l_align)
    {
        l_offset = (oal_int32)(((oal_uint) pst_netbuf->data) % (oal_uint)l_align);

        if(l_offset)
        {
            oal_netbuf_reserve(pst_netbuf, l_align - l_offset);
        }
    }

    return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_free
 功能描述  : 释放报文结构体内存空间
 输入参数  : pst_netbuf: 报文结构体指针
 输出参数  : 无
 返 回 值  : 成功返回OAL_SUCC；失败返回OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_netbuf_free(oal_netbuf_stru *pst_netbuf)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (oal_atomic_read(&pst_netbuf->users) > 1)
    {
        oal_atomic_dec(&pst_netbuf->users);

        return OAL_SUCC;
    }

    if (0 == oal_atomic_read(&pst_netbuf->users))
    {
        return OAL_SUCC;
    }

    if (1 != pst_netbuf->cloned)
    {
        oal_free(pst_netbuf->head);
    }

    oal_free(pst_netbuf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_free_any
 功能描述  : 释放报文结构体内存空间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  oal_netbuf_free_any(oal_netbuf_stru *pst_netbuf)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return;
    }

    if (oal_atomic_read(&pst_netbuf->users) > 1)
    {
        oal_atomic_dec(&pst_netbuf->users);

        return;
    }

    if (0 == oal_atomic_read(&pst_netbuf->users))
    {
        return;
    }

    if (1 != pst_netbuf->cloned)
    {
        oal_free(pst_netbuf->head);
    }

    oal_free(pst_netbuf);

    return;
}


/*****************************************************************************
 函 数 名  : oal_netbuf_cloned
 功能描述  : 判断一个skb是否是克隆的
 输入参数  : pst_netbuf: skb结构体指针
             en_pri: 内存分配的优先级
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_cloned(const oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->cloned;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_copy_header
 功能描述  : 将skb非数据部分拷贝
 输入参数  : pst_newbuf: 拷贝目的skb
             pst_oldbuf: 拷贝源skb
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_copy_header(oal_netbuf_stru *pst_newbuf, oal_netbuf_stru *pst_oldbuf)
{
    oal_uint32 l_offset;

    pst_newbuf->cloned              = pst_oldbuf->cloned;
    pst_newbuf->mac_header          = pst_oldbuf->mac_header;
    pst_newbuf->transport_header    = pst_oldbuf->transport_header;
    pst_newbuf->network_header      = pst_oldbuf->network_header;

    if (pst_newbuf->data > pst_oldbuf->data)
    {
        l_offset = (oal_uint32)(pst_newbuf->data - pst_oldbuf->data);
        pst_newbuf->mac_header += l_offset;
        pst_newbuf->transport_header += l_offset;
        pst_newbuf->network_header += l_offset;
    }
    else
    {
        l_offset = (oal_uint32)(pst_oldbuf->data - pst_newbuf->data);
        pst_newbuf->mac_header -= l_offset;
        pst_newbuf->transport_header -= l_offset;
        pst_newbuf->network_header -= l_offset;
    }

    oal_memcopy((oal_void *)pst_newbuf->cb, (oal_void *)pst_oldbuf->cb, sizeof(pst_oldbuf->cb));

}

/*****************************************************************************
 函 数 名  : oal_netbuf_copy
 功能描述  : 拷贝一份新的skb
 输入参数  : pst_netbuf: skb结构体指针
             en_pri: 内存分配的优先级
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_netbuf_stru  *oal_netbuf_copy(oal_netbuf_stru *pst_netbuf, oal_gfp_enum_uint8 en_priority)
{
    oal_uint32       ul_size;
    oal_int32        l_reserve;
    oal_netbuf_stru *pst_newbuf;

    ul_size    = (oal_uint32)(pst_netbuf->end - pst_netbuf->head);
    l_reserve  = pst_netbuf->data - pst_netbuf->head;
    pst_newbuf = oal_netbuf_alloc(ul_size, l_reserve, 0);

    if (OAL_PTR_NULL == pst_newbuf)
    {
        return OAL_PTR_NULL;
    }

    oal_netbuf_put(pst_newbuf, pst_netbuf->len);

    /* 数据拷贝 */
    oal_memcopy((oal_void *)pst_newbuf->head, (oal_void *)pst_netbuf->head, ul_size);

    /* 结构体拷贝 */
    oal_netbuf_copy_header(pst_newbuf, pst_netbuf);

    return pst_newbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_unshare
 功能描述  : 判断一个skb是否为克隆的，是则copy一份新的skb，否则直接返回传入的skb
 输入参数  : pst_netbuf: skb结构体指针
             en_pri: 内存分配的优先级
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_netbuf_stru  *oal_netbuf_unshare(oal_netbuf_stru *pst_netbuf, oal_gfp_enum_uint8 en_priority)
{
    oal_netbuf_stru *pst_newbuf;

    if (oal_netbuf_cloned(pst_netbuf))
    {
        pst_newbuf = oal_netbuf_copy(pst_netbuf, en_priority);
        oal_netbuf_free(pst_netbuf);
        pst_netbuf = pst_newbuf;
    }

    return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint8* oal_netbuf_data(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->data;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint8* oal_netbuf_header(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->data;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint8* oal_netbuf_payload(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->data;
}


/*****************************************************************************
 函 数 名  : oal_netbuf_end
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 *oal_netbuf_end(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->end;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_get_len
 功能描述  : 获取skb数据长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_netbuf_get_len(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->len;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_headroom
 功能描述  : 获取头部空间大小
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  : 头部空间大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_netbuf_headroom(const oal_netbuf_stru *pst_netbuf)
{
    return (oal_uint32)(pst_netbuf->data - pst_netbuf->head);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_tailroom
 功能描述  : 获取尾部空间大小
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  : 尾部空间大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  oal_netbuf_tailroom(const oal_netbuf_stru *pst_netbuf)
{
    return (oal_uint32)(pst_netbuf->end - pst_netbuf->tail);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_realloc
 功能描述  : skb头部内存空间扩充
 输入参数  : pst_netbuf: skb结构体指针
             ul_headroom: 想要扩展的头部空间大小
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_netbuf_stru* oal_netbuf_realloc_headroom(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_headroom)
{
    oal_uint32          ul_headlen;
    oal_netbuf_stru*    pst_nbuf;

    ul_headlen = ul_headroom + oal_netbuf_headroom(pst_netbuf);
    pst_nbuf   = oal_netbuf_alloc((pst_netbuf->truesize - OAL_SIZEOF(oal_netbuf_stru) + ul_headroom), (oal_int32)ul_headlen, 4);

    oal_netbuf_copy_header(pst_nbuf, pst_netbuf);

    oal_netbuf_put(pst_nbuf, pst_netbuf->len);

    oal_memcopy(pst_nbuf->data, pst_netbuf->data, pst_netbuf->len);

    oal_netbuf_free(pst_netbuf);

    return pst_nbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_realloc_tailroom
 功能描述  : skb尾部空间扩充
 输入参数  : pst_netbuf: skb结构体指针
             ul_tailroom: 想要扩展的尾部空间大小
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_netbuf_stru* oal_netbuf_realloc_tailroom(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_tailroom)
{
    oal_uint32          ul_headlen;
    oal_netbuf_stru*    pst_nbuf;

    ul_headlen = oal_netbuf_headroom(pst_netbuf);
    pst_nbuf   = oal_netbuf_alloc((pst_netbuf->truesize - OAL_SIZEOF(oal_netbuf_stru) + ul_tailroom), (oal_int32)ul_headlen, 4);

    oal_netbuf_copy_header(pst_nbuf, pst_netbuf);

    oal_netbuf_put(pst_nbuf, pst_netbuf->len);

    oal_memcopy(pst_nbuf->data, pst_netbuf->data, pst_netbuf->len);

    oal_netbuf_free(pst_netbuf);

    return pst_nbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_cb
 功能描述  : 返回skb中的cb字段
 输入参数  : pst_netbuf: skb结构体指针
 输出参数  : 无
 返 回 值  : cb
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint8* oal_netbuf_cb(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->cb;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_add_to_list
 功能描述  : 将skb加入skb链表中
 输入参数  : pst_new: 要插入的新skb指针
             pst_prev: 尾节点
             pst_head: skb链表头指针

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_add_to_list(oal_netbuf_stru *pst_buf, oal_netbuf_stru *pst_prev, oal_netbuf_stru *pst_next)
{
    pst_buf->next   = pst_next;
    pst_buf->prev   = pst_prev;
    pst_next->prev  = pst_buf;
    pst_prev->next  = pst_buf;
}

/*****************************************************************************
 函 数 名  : hmac_msdu_add_to_amsdu_tail
 功能描述  : 将skb加入skb链表中的尾部
 输入参数  : pst_new: 要插入的新skb指针
             pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_add_to_list_tail(oal_netbuf_stru *pst_buf, oal_netbuf_head_stru *pst_head)
{
    oal_netbuf_add_to_list(pst_buf, pst_head->pst_prev, (oal_netbuf_stru *)pst_head);

    pst_head->ul_num++;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_len
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_list_len(oal_netbuf_head_stru *pst_head)
{
    return pst_head->ul_num;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_empty
 功能描述  : 判断skb list是否为空
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_netbuf_list_empty(const oal_netbuf_head_stru *pst_list_head)
{
    return (pst_list_head == (oal_netbuf_head_stru *)pst_list_head->pst_next);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_head_init
 功能描述  : 初始化skb队列头
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_list_head_init(oal_netbuf_head_stru *pst_list_head)
{
    pst_list_head->pst_next = (oal_netbuf_stru *)pst_list_head;
    pst_list_head->pst_prev = (oal_netbuf_stru *)pst_list_head;

    pst_list_head->ul_num = 0;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_list_next
 功能描述  : 返回链表中指定节点的下一个节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_list_next(const oal_netbuf_stru *pst_buf)
{
    return pst_buf->next;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_delete
 功能描述  : 删除链表中的skb
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_delete(oal_netbuf_stru *pst_buf, oal_netbuf_head_stru *pst_list_head)
{
    oal_netbuf_stru *pst_next;
    oal_netbuf_stru *pst_prev;

    pst_next       = pst_buf->next;
    pst_prev       = pst_buf->prev;
    pst_buf->prev  = NULL;
    pst_buf->next  = NULL;
    pst_next->prev = pst_prev;
    pst_prev->next = pst_next;

    pst_list_head->ul_num--;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_delist
 功能描述  : skb链表出队
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_delist(oal_netbuf_head_stru *pst_list_head)
{
    oal_netbuf_stru *pst_buf_peek;

    pst_buf_peek = pst_list_head->pst_next;

    if (pst_buf_peek == (oal_netbuf_stru *)pst_list_head)
    {
        return OAL_PTR_NULL;
    }

    oal_netbuf_delete(pst_buf_peek, pst_list_head);

    return pst_buf_peek;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_peek
 功能描述  : 返回skb链表中的第一个元素
 输入参数  : pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  : 链表中第一个元素
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_peek(oal_netbuf_head_stru *pst_head)
{
    oal_netbuf_stru *pst_peek;

    pst_peek = ((oal_netbuf_stru *)pst_head)->next;

    if (pst_peek == (oal_netbuf_stru *)pst_head)
    {
        pst_peek = OAL_PTR_NULL;
    }

    return pst_peek;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_peek_tail
 功能描述  : 返回skb链表中的最后一个元素
 输入参数  : pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  : 链表中第一个元素
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_peek_tail(oal_netbuf_head_stru *pst_head)
{

	oal_netbuf_stru *pst_netbuf = pst_head->pst_prev;

	if (pst_netbuf == (oal_netbuf_stru *)pst_head)
		pst_netbuf = NULL;
	return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_tail
 功能描述  : 返回skb链表中的最后一个元素
 输入参数  : pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  : 链表中最后一个元素
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_tail(oal_netbuf_head_stru *pst_head)
{
    oal_netbuf_stru *pst_tail;

    pst_tail = ((oal_netbuf_stru *)pst_head)->prev;

    if (pst_tail == (oal_netbuf_stru *)pst_head)
    {
        pst_tail = OAL_PTR_NULL;
    }

    return pst_tail;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_depad
 功能描述  : 去掉尾部的pad
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_depad(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    pst_netbuf->tail -= ul_len;
    pst_netbuf->len  -= ul_len;

    return pst_netbuf->tail;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_free_list
 功能描述  : 从链表中释放制定个数的skb
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_free_list(oal_netbuf_head_stru *pst_head, oal_uint32 ul_num)
{
    oal_uint32 ul_index;
    oal_uint32 ul_ret;

    for (ul_index = 0; ul_index < ul_num; ul_index++)
    {
        ul_ret = oal_netbuf_free(oal_netbuf_delist(pst_head));

        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_get_appointed_netbuf
 功能描述  : 获取当前netbuf元素后的第n个元素
 输入参数  : (1)起始查找节点
             (2)向后查找的个数
 输出参数  : 指向期望的netbuf的指针
 返 回 值  : 期望的betbuf元素的指针或空指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_get_appointed_netbuf(oal_netbuf_stru *pst_netbuf, oal_uint8 uc_num, oal_netbuf_stru **pst_expect_netbuf)
{
    oal_uint8   uc_buf_num;

    if ((OAL_PTR_NULL == pst_netbuf) || (OAL_PTR_NULL == pst_expect_netbuf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pst_expect_netbuf = OAL_PTR_NULL;

    for (uc_buf_num = 0; uc_buf_num < uc_num; uc_buf_num++)
    {
       *pst_expect_netbuf = oal_get_netbuf_next(pst_netbuf);

        if (OAL_PTR_NULL == *pst_expect_netbuf)
        {
            break;
        }

        pst_netbuf          = *pst_expect_netbuf;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_clone
 功能描述  : skb克隆，复制头部 ，data指向同一块区域
 输入参数  : pst_buf: skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_clone(oal_netbuf_stru *pst_buf)
{
    oal_netbuf_stru *pst_nbuf;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        return OAL_PTR_NULL;
    }

    pst_nbuf = (oal_netbuf_stru *)oal_memalloc(sizeof(oal_netbuf_stru));

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_nbuf))
    {
        return OAL_PTR_NULL;
    }

    pst_nbuf->mac_header          = pst_buf->mac_header;
    pst_nbuf->transport_header    = pst_buf->transport_header;
    pst_nbuf->network_header      = pst_buf->network_header;

    pst_nbuf->len       = pst_buf->len;
    pst_nbuf->cloned    = 1;
    pst_nbuf->data      = pst_buf->data;
    pst_nbuf->head      = pst_buf->head;
    pst_nbuf->tail      = pst_buf->tail;
    pst_nbuf->end       = pst_buf->end;
    pst_nbuf->truesize  = pst_buf->truesize;
    pst_nbuf->users     = 1;

    pst_buf->cloned     = 1;

    oal_memcopy((oal_void *)pst_nbuf->cb, (oal_void *)pst_buf->cb, sizeof(pst_buf->cb));

    return pst_nbuf;
}
/*****************************************************************************
 函 数 名  : oal_netbuf_decrease_user
 功能描述  : 将skb的引用计数减一
 输入参数  : pst_buf: skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_decrease_user(oal_netbuf_stru *pst_buf)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_buf->users--;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_increase_user
 功能描述  : 将skb的引用计数+1
 输入参数  : pst_buf: skb指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_increase_user(oal_netbuf_stru *pst_buf)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_buf->users++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_get_buf_num
 功能描述  : 获取netbuf双向链表中buf的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_get_buf_num(oal_netbuf_head_stru *pst_netbuf_head)
{
    return pst_netbuf_head->ul_num;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_get
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_get(oal_netbuf_stru *pst_netbuf)
{
    oal_atomic_inc(&pst_netbuf->users);
    return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_queue_purge
 功能描述  : 释放skb链中的所有skb
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_queue_purge(
                                            oal_netbuf_head_stru  *pst_netbuf_head)
{
    oal_netbuf_free_list(pst_netbuf_head, oal_netbuf_list_len(pst_netbuf_head));
}

/*****************************************************************************
 函 数 名  : oal_netbuf_copy_expand
 功能描述  : 复制skb以及数据，并扩充头部和尾部空间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru*  oal_netbuf_copy_expand(
                                                 oal_netbuf_stru *pst_netbuf,
                                                 oal_int32        ul_headroom,
                                                 oal_int32        ul_tailroom,
                                                 oal_gfp_enum     en_gfp_mask)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_int32  oal_netif_rx_hw(oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_free(pst_netbuf);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oal_netif_rx
 功能描述  : 将skb发给桥
 输入参数  : pst_netbuf: skb指针
 输出参数  : 无
 返 回 值  : 1，drop；0，succ
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_netif_rx(oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_free(pst_netbuf);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : oal_netif_rx_ni
 功能描述  : 将skb发给桥 !in_interrupt()
 输入参数  : pst_netbuf: skb指针
 输出参数  : 无
 返 回 值  : 1，drop；0，succ
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_netif_rx_ni(oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_free(pst_netbuf);

    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_void  oal_local_bh_disable(oal_void)
{
    return;
}

OAL_STATIC OAL_INLINE oal_void  oal_local_bh_enable(oal_void)
{
    return;
}


/*****************************************************************************
 函 数 名  : oal_cpu_clock
 功能描述  : 获取cpu时间戳
 输入参数  : pst_netbuf: skb指针
 输出参数  : 无
 返 回 值  : 1，drop；0，succ
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint64  oal_cpu_clock(oal_void)
{
    return OAL_SUCC;
}

/* BEGIN : Windows 实现 Linux wiphy 结构相关的处理函数 */

/*****************************************************************************
 函 数 名  : oal_wiphy_new
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_wiphy_stru * oal_wiphy_new(oal_cfg80211_ops_stru *ops, oal_uint32 sizeof_priv)
{
    return (oal_wiphy_stru *)oal_memalloc(sizeof_priv + OAL_SIZEOF(oal_wiphy_stru));// 由于在Windows 中，需要申请空间才能继续执行，故将 oal_wiphy_new 返回值为真。
}

OAL_STATIC OAL_INLINE oal_int32 oal_wiphy_register(oal_wiphy_stru *pst_wiphy)
{
    return 0;//在Linxu 中， 注册设备成功返回 0.
}

OAL_STATIC OAL_INLINE oal_void oal_wiphy_unregister(oal_wiphy_stru *pst_wiphy)
{

}

OAL_STATIC OAL_INLINE void oal_wiphy_free(oal_wiphy_stru *pst_wiphy)
{
    oal_free(pst_wiphy);
}
OAL_STATIC OAL_INLINE void *oal_wiphy_priv(oal_wiphy_stru *pst_wiphy)
{
    //return OAL_PTR_NULL;
    return pst_wiphy->priv;
}


OAL_STATIC OAL_INLINE void oal_wiphy_apply_custom_regulatory(oal_wiphy_stru *pst_wiphy, OAL_CONST oal_ieee80211_regdomain_stru *regd)
{
    return;
}

/* 添加wiphy结构体rts门限赋值 */
OAL_STATIC OAL_INLINE void oal_wiphy_set_rts(oal_wiphy_stru *pst_wiphy, oal_uint32 ul_rts_threshold)
{
        pst_wiphy->rts_threshold  =  ul_rts_threshold;
}

/* 添加wiphy结构体分片门限赋值 */
OAL_STATIC OAL_INLINE void oal_wiphy_set_frag(oal_wiphy_stru *pst_wiphy, oal_uint32 ul_frag_threshold)
{
        pst_wiphy->frag_threshold  =  ul_frag_threshold;
}

/*****************************************************************************
 函 数 名  : oal_netlink_kernel_create
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_sock_stru* oal_netlink_kernel_create(
                oal_net_stru *pst_net, oal_int32 l_unit, oal_uint32 ul_groups,
                oal_void (*input)(oal_netbuf_stru *pst_netbuf),
                oal_mutex_stru *pst_cb_mutex, oal_module_stru *pst_module)
{
    return &g_st_sock;
}

/*****************************************************************************
 函 数 名  : oal_netlink_kernel_release
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netlink_kernel_release(oal_sock_stru *pst_sock)
{

}

/*****************************************************************************
 函 数 名  : oal_nlmsg_hdr
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_nlmsghdr_stru* oal_nlmsg_hdr(OAL_CONST oal_netbuf_stru *pst_netbuf)
{
    return (oal_nlmsghdr_stru *)OAL_NETBUF_HEADER(pst_netbuf);
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_msg_size
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nlmsg_msg_size(oal_int32 l_payload)
{
    return OAL_NLMSG_HDRLEN + l_payload;
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_total_size
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nlmsg_total_size(oal_int32 l_payload)
{
    return OAL_NLMSG_ALIGN(oal_nlmsg_msg_size(l_payload));
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_put
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_nlmsghdr_stru* oal_nlmsg_put(
                oal_netbuf_stru *pst_netbuf, oal_uint32 ul_pid,
                oal_uint32 ul_seq, oal_int32 l_type, oal_int32 l_payload, oal_int32 l_flags)

{
    oal_nlmsghdr_stru   *pst_nlmsghdr;
    oal_int32            l_size;

    if (OAL_UNLIKELY((oal_int32)oal_netbuf_tailroom(pst_netbuf) < oal_nlmsg_total_size(l_payload)))
    {
        return OAL_PTR_NULL;
    }

    l_size = OAL_NLMSG_LENGTH(l_payload);

    pst_nlmsghdr = (oal_nlmsghdr_stru *)oal_netbuf_put(pst_netbuf, OAL_NLMSG_ALIGN(l_size));
    pst_nlmsghdr->nlmsg_type = (oal_uint16)l_type;
    pst_nlmsghdr->nlmsg_len = (oal_uint32)l_size;
    pst_nlmsghdr->nlmsg_flags = (oal_uint16)l_flags;
    pst_nlmsghdr->nlmsg_pid = ul_pid;
    pst_nlmsghdr->nlmsg_seq = ul_seq;
    if (OAL_NLMSG_ALIGN(l_size) - l_size != 0)
    {
        oal_memset((oal_uint8 *)OAL_NLMSG_DATA(pst_nlmsghdr) + l_payload, 0, OAL_NLMSG_ALIGN(l_size) - l_size);
    }

    return pst_nlmsghdr;
}

/*****************************************************************************
 函 数 名  : oal_nla_put_u32
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月23日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 oal_nla_put_u32(oal_netbuf_stru *pst_skb, oal_int32 l_attrtype, oal_uint32 ul_value)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_nla_put
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月23日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nla_put(oal_netbuf_stru *pst_skb, oal_int32 l_attrtype, oal_int32 l_attrlen, const oal_void *p_data)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_new
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru *oal_nlmsg_new(oal_int32 payload, oal_gfp_enum_uint8 flags)
{
    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_free
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_nlmsg_free(oal_netbuf_stru *pst_skb)
{
    return ;
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_multicast
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 18, 0))
OAL_STATIC OAL_INLINE oal_int32  oal_genlmsg_multicast(oal_genl_family_stru *pst_family,
                                     oal_netbuf_stru *pst_skb, oal_uint32 ul_pid,
                                     oal_uint32 ul_group, oal_gfp_enum_uint8 flags)
#else
OAL_STATIC OAL_INLINE oal_int32  oal_genlmsg_multicast(oal_netbuf_stru *pst_skb, oal_uint32 ul_pid,
                                     oal_uint32 ul_group, oal_gfp_enum_uint8 flags)
#endif
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_put
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void *oal_genlmsg_put(
                oal_netbuf_stru *pst_skb, oal_uint32 ul_pid, oal_uint32 ul_seq,
				oal_genl_family_stru *pst_family, oal_int32 flags, oal_uint8 cmd)
{
    return (oal_void *)OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : oal_nla_nest_start
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_nlattr_stru *oal_nla_nest_start(oal_netbuf_stru *pst_skb, oal_int32 l_attrtype)
{
    oal_nlattr_stru *pst_nla_nest_start = OAL_PTR_NULL;

    return pst_nla_nest_start;
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_cancel
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_genlmsg_cancel(oal_netbuf_stru *pst_skb, oal_void *pst_hdr)
{
    return ;
}

/*****************************************************************************
 函 数 名  : oal_nla_nest_end
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nla_nest_end(oal_netbuf_stru *pst_skb, oal_nlattr_stru *pst_start)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_end
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_genlmsg_end(oal_netbuf_stru *pst_skb, oal_void *pst_hdr)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_wiphy_to_dev
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月23日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_cfg80211_registered_device_stru *oal_wiphy_to_dev(oal_wiphy_stru *pst_wiphy)
{
    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : oal_netlink_unicast
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_netlink_unicast(
                oal_sock_stru *pst_sock, oal_netbuf_stru *pst_netbuf,
                oal_uint32 ul_pid, oal_int32 l_nonblock)
{
    oal_netbuf_free(pst_netbuf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_copydata
 功能描述  : 将skb中的内容先偏移ul_offset后 按指定长度拷贝到指定内从中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_copydata(oal_netbuf_stru *pst_netbuf_sc, oal_uint32 ul_offset, oal_void *p_dst, oal_uint32 ul_len)
{
    oal_void *p_scr;
    p_scr = OAL_NETBUF_DATA(pst_netbuf_sc) + ul_offset;

    oal_memcopy(p_dst, p_scr, ul_len);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_trim
 功能描述  : 剥去skb中尾部的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_trim(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    oal_uint32  ul_size;

    ul_size = pst_netbuf->len - ul_len;

    if (pst_netbuf->len > ul_size)
    {

        pst_netbuf->len = ul_size;
        pst_netbuf->tail = pst_netbuf->data;
        pst_netbuf->tail += ul_size;
    }

    return;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_concat
 功能描述  : 向netbu_head的尾部串接netbuf
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_concat(oal_netbuf_stru *pst_netbuf_head, oal_netbuf_stru *pst_netbuf)
{
    memcpy(pst_netbuf_head->tail, pst_netbuf->data, pst_netbuf->len);

    oal_netbuf_put(pst_netbuf_head, pst_netbuf->len);

    oal_netbuf_free(pst_netbuf);
}



/*****************************************************************************
 函 数 名  : oal_netbuf_set_len
 功能描述  : 将skb的数据内容长度设置为指定长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_set_len(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    if (pst_netbuf->len > ul_len)
    {
        oal_netbuf_trim(pst_netbuf, pst_netbuf->len - ul_len);
    }
    else
    {
        oal_netbuf_put(pst_netbuf, (ul_len - pst_netbuf->len));
    }
}

/*****************************************************************************
 函 数 名  : oal_netbuf_init
 功能描述  : 初始化netbuf
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_init(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    oal_netbuf_set_len(pst_netbuf, ul_len);
    pst_netbuf->protocol = 0;
}


/*****************************************************************************
 函 数 名  : oal_netbuf_reset
 功能描述  : netbuf初始复位
 输入参数  : pst_netbuf    : netbuf指针
             ul_data_offset: data相对head的偏移
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_reset(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_data_offset)
{
    /* data tail指针复位 */
    pst_netbuf->data = pst_netbuf->head + ul_data_offset;
    pst_netbuf->tail = pst_netbuf->data;
    pst_netbuf->len  = 0;
}

/*****************************************************************************
 函 数 名  : oal_hi_kernel_wdt_clear
 功能描述  : 狗复位
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_hi_kernel_wdt_clear(oal_void)
{
    return;
}

/*****************************************************************************
 函 数 名  : oal_ipv6_addr_copy
 功能描述  : 拷贝ipv6地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_ipv6_addr_copy(oal_in6_addr *pst_ipv6_dst, oal_in6_addr *pst_ipv6_src)
{
    oal_memcopy(pst_ipv6_dst, pst_ipv6_src, OAL_SIZEOF(oal_in6_addr));
}

/*****************************************************************************
 函 数 名  : oal_arp_create
 功能描述  : 保证skb->data包含ul_len指指示的空间，如果没有，则从 skb_shinfo(skb)->frags[]中
             拷贝一份数据。
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  eth_header(oal_netbuf_stru *skb, oal_net_device_stru *dev,
           oal_uint16 type,
           void *daddr, void *saddr, oal_uint32 len)
{
     oal_ether_header_stru *eth = ( oal_ether_header_stru *)oal_netbuf_push(skb, 14);

    if (type != 0x0001 && type != 0x0004)
    {
        eth->us_ether_type = OAL_HOST2NET_SHORT(type);
    }
    else
    {
        eth->us_ether_type = OAL_HOST2NET_SHORT(len);
    }

    if (!saddr)
    {
        saddr = dev->dev_addr;
    }

    memcpy(eth->auc_ether_shost, saddr, 6);

    if (daddr)
    {
        memcpy(eth->auc_ether_dhost, daddr, 6);
        return 14;
    }

    return -14;
}


/*****************************************************************************
 函 数 名  : oal_dev_hard_header
 功能描述  : 构造以太头
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_dev_hard_header(oal_netbuf_stru *pst_nb,
                                                            oal_net_device_stru *pst_net_dev,
                                                            oal_uint16 us_type,
                                                            oal_uint8 *puc_addr_d,
                                                            oal_uint8 *puc_addr_s,
                                                            oal_uint32 ul_len)
{
    return eth_header(pst_nb, pst_net_dev, us_type, puc_addr_d, puc_addr_s, ul_len);
}

/*****************************************************************************
 函 数 名  : oal_dev_hard_header
 功能描述  : 生成ipv6的magic
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint16  oal_csum_ipv6_magic(oal_in6_addr *pst_ipv6_s,
                                                            oal_in6_addr *pst_ipv6_d,
                                                            oal_uint32 ul_len,
                                                            oal_uint16 us_proto,
                                                            oal_uint32 ul_sum)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : oal_csum_partial
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_csum_partial(const void *p_buff,
                                                            oal_int32  l_len,
                                                            oal_uint32 ul_sum)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : oal_ipv6_addr_type
 功能描述  : 获取ipv6地址的类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 ipv6_addr_scope2type(oal_uint32 ul_scope)
{
    switch(ul_scope) {
    case IPV6_ADDR_SCOPE_NODELOCAL:
        return (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_NODELOCAL) |
            IPV6_ADDR_LOOPBACK);
    case IPV6_ADDR_SCOPE_LINKLOCAL:
        return (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL) |
            IPV6_ADDR_LINKLOCAL);
    case IPV6_ADDR_SCOPE_SITELOCAL:
        return (IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_SITELOCAL) |
            IPV6_ADDR_SITELOCAL);
    default:
        break;
    }
    return IPV6_ADDR_SCOPE_TYPE(ul_scope);
}

/*****************************************************************************
 函 数 名  : __ipv6_addr_type
 功能描述  :获取ipv6地址类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

/*lint -e778*/ /*lint -e572*/ /*lint -e778*/ /*lint -e713*/
OAL_STATIC OAL_INLINE oal_int32 __ipv6_addr_type(oal_in6_addr *pst_addr6)
{
    oal_uint32 ul_st;

    ul_st = pst_addr6->s6_addr32[0];

    /* Consider all addresses with the first three bits different of
       000 and 111 as unicasts.
     */


    if ((ul_st & OAL_HOST2NET_LONG(0xE0000000)) != OAL_HOST2NET_LONG(0x00000000) &&
        (ul_st & OAL_HOST2NET_LONG(0xE0000000)) != OAL_HOST2NET_LONG(0xE0000000))
    {
        return (IPV6_ADDR_UNICAST | IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));
    }

    if ((ul_st & OAL_HOST2NET_LONG(0xFF000000)) == OAL_HOST2NET_LONG(0xFF000000))
    {
        /* multicast */
        /* addr-select 3.1 */
        return (IPV6_ADDR_MULTICAST | ipv6_addr_scope2type(IPV6_ADDR_MC_SCOPE(pst_addr6)));
    }

    if ((ul_st & oal_byteorder_host_to_net_uint32(0xFFC00000)) == oal_byteorder_host_to_net_uint32(0xFE800000))
    {
        return (IPV6_ADDR_LINKLOCAL | IPV6_ADDR_UNICAST |
    		IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL));		/* addr-select 3.1 */
    }

    if ((ul_st & oal_byteorder_host_to_net_uint32(0xFFC00000)) == oal_byteorder_host_to_net_uint32(0xFEC00000))
    {
    	return (IPV6_ADDR_SITELOCAL | IPV6_ADDR_UNICAST |
    		IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_SITELOCAL));		/* addr-select 3.1 */
    }

    if ((ul_st & oal_byteorder_host_to_net_uint32(0xFE000000)) == oal_byteorder_host_to_net_uint32(0xFC000000))
    {
    	return (IPV6_ADDR_UNICAST |
    		IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));			/* RFC 4193 */
    }

    if ((pst_addr6->s6_addr32[0] | pst_addr6->s6_addr32[1]) == 0)
    {
    	if (pst_addr6->s6_addr32[2] == 0)
    	{
    		if (pst_addr6->s6_addr32[3] == 0)
    		{
    		    return 0;
    		}

    		if (pst_addr6->s6_addr32[3] == OAL_HOST2NET_LONG(0x00000001))
    		{
    			return (IPV6_ADDR_LOOPBACK | IPV6_ADDR_UNICAST |
    				IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_LINKLOCAL));	/* addr-select 3.4 */
    		}

    		return (0x0080U | IPV6_ADDR_UNICAST |
    			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));	/* addr-select 3.3 */
    	}

    	if (pst_addr6->s6_addr32[2] == OAL_HOST2NET_LONG((oal_uint32)0x0000ffff))
    	{
    		return (0x1000U |
    			IPV6_ADDR_SCOPE_TYPE(IPV6_ADDR_SCOPE_GLOBAL));	/* addr-select 3.3 */
    	}
    }
    return 0;
}

/*lint +e778*/ /*lint +e572*/ /*lint +e778*/ /*lint +e713*/
/*****************************************************************************
 函 数 名  : ipv6_addr_type
 功能描述  :获取地址类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 ipv6_addr_type(oal_in6_addr *pst_addr6)
{
    return __ipv6_addr_type(pst_addr6) & 0xffff;
}

/*****************************************************************************
 函 数 名  : oal_ipv6_addr_type
 功能描述  :获取地址类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_ipv6_addr_type(oal_in6_addr *pst_ipv6)
{
    return ipv6_addr_type(pst_ipv6);
}

/*****************************************************************************
 函 数 名  : oal_pskb_may_pull
 功能描述  : 保证skb->data包含ul_len指示的空间，如果没有，则从 skb_shinfo(skb)->frags[]中
             拷贝一份数据。
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_pskb_may_pull(oal_netbuf_stru *pst_nb, oal_uint32 ul_len)
{
   return 1;
}

/*****************************************************************************
 函 数 名  : arp_hdr_len
 功能描述  : 获取arp头的长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 arp_hdr_len(oal_net_device_stru *pst_dev)
{
    /* ARP header, plus 2 device addresses, plus 2 IP addresses. */
    return sizeof(oal_eth_arphdr_stru) + (pst_dev->addr_len + sizeof(oal_uint32)) * 2;
}


/*****************************************************************************
 函 数 名  : arp_hdr_len
 功能描述  : skb的data和len指针一起往下移动len
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void skb_reserve(oal_netbuf_stru *pst_skb, int l_len)
{
	pst_skb->data += l_len;
	pst_skb->tail += l_len;
}

/*****************************************************************************
 函 数 名  : oal_arp_create
 功能描述  : 创建一个arp包
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC OAL_INLINE oal_netbuf_stru  *oal_arp_create(oal_int32 l_type, oal_int32 l_ptype, oal_uint32 ul_dest_ip,
                                    			    oal_net_device_stru *pst_dev, oal_uint32 ul_src_ip,
                                    			   oal_uint8 *puc_dest_hw,
                                    			   oal_uint8 *puc_src_hw,
                                    			   oal_uint8 *puc_target_hw)
{
    oal_netbuf_stru             *pst_skb;
    oal_eth_arphdr_stru         *pst_arp;
    oal_uint8                   *pst_arp_ptr;
    oal_int8                    ac_bcast[6] = {0x33,0x33,0x33,0x33,0x33,0x33};
    /*
     *  Allocate a buffer
     */

    pst_skb = oal_netbuf_alloc(arp_hdr_len(pst_dev) + LL_ALLOCATED_SPACE(pst_dev), 0, 4);
    //skb = alloc_skb(arp_hdr_len(dev) + LL_ALLOCATED_SPACE(dev), GFP_ATOMIC);
    if (pst_skb == NULL)
    {
        return NULL;
    }


    skb_reserve(pst_skb, LL_RESERVED_SPACE(pst_dev)); /* reserve 16 */
    //skb_reset_network_header(skb);
    pst_skb->network_header = pst_skb->data;
    pst_arp = (oal_eth_arphdr_stru *) oal_netbuf_put(pst_skb, (oal_uint32)arp_hdr_len(pst_dev));
    pst_skb->dev = pst_dev;
    pst_skb->protocol = OAL_HOST2NET_SHORT(ETHER_TYPE_ARP);
    if (puc_src_hw == NULL)
    {
        oal_memcopy(puc_src_hw, pst_dev->dev_addr, 6);
    }

    if (puc_dest_hw == NULL)
    {
        oal_memcopy(puc_dest_hw, ac_bcast, 6);
    }

    /*
     *  Fill the device header for the ARP frame
     */

    /*lint -e734*/
    if (eth_header(pst_skb, pst_dev, l_ptype, puc_dest_hw, puc_src_hw, pst_skb->len) < 0)
    {
        oal_netbuf_free(pst_skb);
        return NULL;
    }
    /*lint +e734*/


    /*lint -e778*/
    pst_arp->us_ar_hrd = OAL_HOST2NET_SHORT(pst_dev->type);
    pst_arp->us_ar_pro = OAL_HOST2NET_SHORT(ETHER_TYPE_IP);
    /*lint +e778*/

    pst_arp->uc_ar_hln = 6;
    pst_arp->uc_ar_pln = 4;
    pst_arp->us_ar_op = OAL_HOST2NET_SHORT(l_type);

    pst_arp_ptr=(oal_uint8 *)pst_arp + 8 ;

    oal_memcopy(pst_arp_ptr, puc_src_hw, 6);
    pst_arp_ptr += 6;
    oal_memcopy(pst_arp_ptr, &ul_src_ip, 4);
    pst_arp_ptr += 4;
    if (puc_target_hw != NULL)
    {
        oal_memcopy(pst_arp_ptr, puc_target_hw, 6);
    }
    else
    {
        oal_memset(pst_arp_ptr, 0, 6);
    }

    pst_arp_ptr += 6;
    oal_memcopy(pst_arp_ptr, &ul_dest_ip, 4);

    return pst_skb;

}

/*
 * Convert an ASCII string to binary IP.
 * This is outside of net/ipv4/ because various code that uses IP addresses
 * is otherwise not dependent on the TCP/IP stack.
 */

OAL_STATIC OAL_INLINE oal_uint32 oal_in_aton(oal_uint8 *pul_str)
{
    oal_uint32 ul_l;
    oal_uint32 ul_val;
    oal_uint8  uc_i;

    ul_l = 0;

    for (uc_i = 0; uc_i < 4; uc_i++)
    {
        ul_l <<= 8;
        if (*pul_str != '\0')
        {
            ul_val = 0;
            while (*pul_str != '\0' && *pul_str != '.' && *pul_str != '\n')
            {

                ul_val *= 10;
                ul_val += *pul_str - '0';
                pul_str++;
            }

            ul_l |= ul_val;

            if (*pul_str != '\0')
            {
                pul_str++;
            }
        }
    }

    return(oal_byteorder_host_to_net_uint32(ul_l));
}

/* get the queue index of the input skbuff */
OAL_STATIC OAL_INLINE oal_uint16 oal_skb_get_queue_mapping(oal_netbuf_stru  *pst_skb)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_void oal_skb_set_queue_mapping(oal_netbuf_stru  *pst_skb, oal_uint16 queue_mapping)
{
    return;
}


OAL_INLINE oal_lwip_buf* pbuf_alloc(pbuf_layer layer, oal_uint16 length, pbuf_type type)
{
    oal_lwip_buf        *pst_pbuf;

    /* 分配结构体空间 */
    pst_pbuf = (oal_lwip_buf *)oal_memalloc(OAL_SIZEOF(oal_lwip_buf));

    if (OAL_PTR_NULL == pst_pbuf)
    {
        return OAL_PTR_NULL;
    }
    OAL_MEMZERO(pst_pbuf, OAL_SIZEOF(oal_lwip_buf));

    /* 分配数据空间 */
    pst_pbuf->payload = (oal_uint8 *)oal_memalloc(length);
    if (OAL_PTR_NULL == pst_pbuf->payload)
    {
        oal_free(pst_pbuf);

        return OAL_PTR_NULL;
    }

    /* 结构体初始化 */
    OAL_MEMZERO(pst_pbuf->payload, length);

    return pst_pbuf;
}
OAL_INLINE oal_int32 pbuf_free(oal_lwip_buf *pst_pbuf)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_pbuf))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_pbuf->ref > 1)
    {
        pst_pbuf->ref--;
        return OAL_SUCC;
    }

    oal_free(pst_pbuf->payload);
    oal_free(pst_pbuf);

    return OAL_SUCC;
}

OAL_INLINE oal_void pbuf_header(oal_lwip_buf *pst_pbuf, oal_int32 l_offset)
{
    pst_pbuf->payload += l_offset;
}

OAL_INLINE oal_void driverif_input(oal_lwip_netif *pst_netif, oal_lwip_buf *pst_pbuf)
{

}

OAL_INLINE oal_lwip_netif* netif_add(oal_lwip_netif *netif, const oal_ip_addr_t *ipaddr, const oal_ip_addr_t *netmask, const oal_ip_addr_t *gw)
{
    return netif;
}

OAL_INLINE oal_void tcpip_init(oal_void *pst_p1, oal_void *pst_p2)
{

}

OAL_STATIC OAL_INLINE oal_wiphy_stru *oal_wiphy_get(void)
{
    return OAL_PTR_NULL;
}

OAL_STATIC OAL_INLINE oal_int32 wal_cfg80211_del_virtual_intf(oal_wiphy_stru           *pst_wiphy,
                                                   oal_wireless_dev_stru    *pst_wdev)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_int32 hisi_driver_send_event(oal_int32 l_cmd, oal_uint8 *puc_buf, oal_uint32 ul_length)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_void hilink_add_tail(oal_uint8 *puc_data, oal_uint16 us_len)
{

}

OAL_STATIC OAL_INLINE void notify_callback(void *ctx, void *context)
{

}

OAL_STATIC OAL_INLINE oal_int32  wal_netdev_select_queue_fun(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_net_dev_tx_enum  wal_bridge_vap_xmit_fun(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    return OAL_NETDEV_TX_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_net.h */
