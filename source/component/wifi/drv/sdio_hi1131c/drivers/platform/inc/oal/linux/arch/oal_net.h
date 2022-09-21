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

#ifndef __OAL_LINUX_NET_H__
#define __OAL_LINUX_NET_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <linux/version.h>
#include <net/iw_handler.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/hardirq.h>
#include <linux/bottom_half.h>
#include <linux/if.h>
#include <linux/etherdevice.h>
#include <linux/wireless.h>
#include <net/rtnetlink.h>
#include <net/netlink.h>
#include <linux/socket.h>
#include <linux/if.h>
#include <net/sch_generic.h>
#include <linux/if_vlan.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/rtnetlink.h>
#include <linux/netfilter_bridge.h>
#include <linux/if_arp.h>
#include <linux/in.h>
#if (defined(_PRE_BOARD_SD5610) || defined(_PRE_BOARD_SD5115))
#include <../net/bridge/br_private.h>
#endif
#include <linux/udp.h>
#include <linux/icmpv6.h>
#include <linux/ipv6.h>
#include <linux/inet.h>
#include <net/ip6_checksum.h>
#include <net/ipv6.h>
#include <net/arp.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
#include <net/cfg80211.h>
#if (defined(_PRE_BOARD_SD5610))
#include <mach/hi_drv_wdt.h>
#endif
#else
#include <net/wireless.h>
#endif
#include <linux/nl80211.h>
#include <linux/ieee80211.h>
#include <../net/wireless/nl80211.h>

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#include <linux/kobject.h>
#endif

#include <linux/kernel_stat.h>
#include <asm/cputime.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_BITFIELD_LITTLE_ENDIAN      0
#define OAL_BITFIELD_BIG_ENDIAN         1

#define OAL_WLAN_SA_QUERY_TR_ID_LEN    2
/* wiphy  */
#define IEEE80211_HT_MCS_MASK_LEN   10
#define OAL_IF_NAME_SIZE   16
#define ETHER_ADDR_LEN  6   /* length of an Ethernet address */

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
#define IPV6_ADDR_RESERVED  0x2000U /* reserved address space */

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

typedef iw_handler                                  oal_iw_handler;
#define oal_netif_running(_pst_net_dev)             netif_running(_pst_net_dev)
#define OAL_SMP_MB()                                smp_mb()
#define OAL_CONTAINER_OF(_member_ptr, _stru_type, _stru_member_name)  container_of(_member_ptr, _stru_type, _stru_member_name)

#define OAL_NETBUF_LIST_NUM(_pst_head)              ((_pst_head)->qlen)
#define OAL_NET_DEV_PRIV(_pst_dev)                  ((_pst_dev)->ml_priv)
#define OAL_NET_DEV_WIRELESS_PRIV(_pst_dev)         (netdev_priv(_pst_dev))
#define OAL_NET_DEV_WIRELESS_DEV(_pst_dev)          ((_pst_dev)->ieee80211_ptr)
#define OAL_NETBUF_NEXT(_pst_buf)                   ((_pst_buf)->next)
#define OAL_NETBUF_PREV(_pst_buf)                   ((_pst_buf)->prev)
#define OAL_NETBUF_HEAD_NEXT(_pst_buf_head)         ((_pst_buf_head)->next)
#define OAL_NETBUF_HEAD_PREV(_pst_buf_head)         ((_pst_buf_head)->prev)

#define OAL_NETBUF_PROTOCOL(_pst_buf)               ((_pst_buf)->protocol)
#define OAL_NETBUF_LAST_RX(_pst_buf)                ((_pst_buf)->last_rx)
#define OAL_NETBUF_DATA(_pst_buf)                   ((_pst_buf)->data)
#define OAL_NETBUF_HEADER(_pst_buf)                 ((_pst_buf)->data)
#define OAL_NETBUF_PAYLOAD(_pst_buf)                 ((_pst_buf)->data)

#define OAL_NETBUF_CB(_pst_buf)                     ((_pst_buf)->cb)
#define OAL_NETBUF_CB_SIZE()                        (OAL_SIZEOF(((oal_netbuf_stru*)0)->cb))
#define OAL_NETBUF_LEN(_pst_buf)                    ((_pst_buf)->len)
#define OAL_NETBUF_TAIL                              skb_tail_pointer
#define OAL_NETBUF_QUEUE_TAIL                        skb_queue_tail
#define OAL_NETBUF_QUEUE_HEAD_INIT                   skb_queue_head_init
#define OAL_NETBUF_DEQUEUE                           skb_dequeue
#define OAL_NETBUF_QUEUE_TAIL                        skb_queue_tail

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
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)
#define OAL_NETDEVICE_QDISC(_pst_dev, pst_val)              ((_pst_dev)->qdisc = pst_val)
#else
#define OAL_NETDEVICE_QDISC(_pst_dev, pst_val)
#endif
#define OAL_NETDEVICE_IFALIAS(_pst_dev)                     ((_pst_dev)->ifalias)
#define OAL_NETDEVICE_WDEV(_pst_dev)                        ((_pst_dev)->ieee80211_ptr)
#define OAL_NETDEVICE_HEADROOM(_pst_dev)                    ((_pst_dev)->needed_headroom)
#define OAL_NETDEVICE_TAILROOM(_pst_dev)                    ((_pst_dev)->needed_tailroom)
#define OAL_NETDEVICE_FLAGS(_pst_dev)                       ((_pst_dev)->flags)
#define OAL_NETDEVICE_ADDR_LEN(_pst_dev)                    ((_pst_dev)->addr_len)
#define OAL_NETDEVICE_WATCHDOG_TIMEO(_pst_dev)              ((_pst_dev)->watchdog_timeo)
#define OAL_NETDEVICE_HARD_HEADER_LEN(_pst_dev)             ((_pst_dev)->hard_header_len)

#define OAL_WIRELESS_DEV_NET_DEV(_pst_wireless_dev)         ((_pst_wireless_dev)->netdev)
#define OAL_WIRELESS_DEV_WIPHY(_pst_wireless_dev)           ((_pst_wireless_dev)->wiphy)
#define OAL_WIRELESS_DEV_IF_TYPE(_pst_wireless_dev)         ((_pst_wireless_dev)->iftype)


#define OAL_IFF_RUNNING         IFF_RUNNING
#define OAL_SIOCIWFIRSTPRIV     SIOCIWFIRSTPRIV

/* iw_priv参数类型OAL封装 */
#define OAL_IW_PRIV_TYPE_BYTE   IW_PRIV_TYPE_BYTE       /* Char as number */
#define OAL_IW_PRIV_TYPE_CHAR   IW_PRIV_TYPE_CHAR       /* Char as character */
#define OAL_IW_PRIV_TYPE_INT    IW_PRIV_TYPE_INT        /* 32 bits int */
#define OAL_IW_PRIV_TYPE_FLOAT  IW_PRIV_TYPE_FLOAT      /* struct iw_freq */
#define OAL_IW_PRIV_TYPE_ADDR   IW_PRIV_TYPE_ADDR       /* struct sockaddr */
#define OAL_IW_PRIV_SIZE_FIXED  IW_PRIV_SIZE_FIXED      /* Variable or fixed number of args */

/* iwconfig mode oal封装 */
#define OAL_IW_MODE_AUTO    IW_MODE_AUTO    /* Let the driver decides */
#define OAL_IW_MODE_ADHOC   IW_MODE_ADHOC   /* Single cell network */
#define OAL_IW_MODE_INFRA   IW_MODE_INFRA   /* Multi cell network, roaming, ... */
#define OAL_IW_MODE_MASTER  IW_MODE_MASTER  /* Synchronisation master or Access Point */
#define OAL_IW_MODE_REPEAT  IW_MODE_REPEAT  /* Wireless Repeater (forwarder) */
#define OAL_IW_MODE_SECOND  IW_MODE_SECOND  /* Secondary master/repeater (backup) */
#define OAL_IW_MODE_MONITOR IW_MODE_MONITOR /* Passive monitor (listen only) */
#define OAL_IW_MODE_MESH    IW_MODE_MESH    /* Mesh (IEEE 802.11s) network */

/* Transmit Power flags available */
#define OAL_IW_TXPOW_TYPE       IW_TXPOW_TYPE           /* Type of value */
#define OAL_IW_TXPOW_DBM        IW_TXPOW_DBM            /* Value is in dBm */
#define OAL_IW_TXPOW_MWATT      IW_TXPOW_MWATT          /* Value is in mW */
#define OAL_IW_TXPOW_RELATIVE   IW_TXPOW_RELATIVE       /* Value is in arbitrary units */
#define OAL_IW_TXPOW_RANGE      IW_TXPOW_RANGE          /* Range of value between min/max */

/* 主机与网络字节序转换 */
#define OAL_HOST2NET_SHORT(_x)  htons(_x)
#define OAL_NET2HOST_SHORT(_x)  ntohs(_x)
#define OAL_HOST2NET_LONG(_x)   htonl(_x)
#define OAL_NET2HOST_LONG(_x)   ntohl(_x)

#define OAL_INET_ECN_NOT_ECT    INET_ECN_NOT_ECT
#define OAL_INET_ECN_ECT_1      INET_ECN_ECT_1
#define OAL_INET_ECN_ECT_0      INET_ECN_ECT_0
#define OAL_INET_ECN_CE         INET_ECN_CE
#define OAL_INET_ECN_MASK       INET_ECN_MASK

/* 提取vlan信息 */
#define oal_vlan_tx_tag_present(_skb)   vlan_tx_tag_present(_skb)
#define oal_vlan_tx_tag_get(_skb)       vlan_tx_tag_get(_skb)

/* vlan宏定义 */
#define OAL_VLAN_VID_MASK       VLAN_VID_MASK       /* VLAN Identifier */
#define OAL_VLAN_PRIO_MASK      VLAN_PRIO_MASK      /* Priority Code Point */

#if  LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)
#define OAL_VLAN_PRIO_SHIFT     VLAN_PRIO_SHIFT
#else
#define OAL_VLAN_PRIO_SHIFT     13
#endif

/* ARP protocol opcodes. */
#define OAL_ARPOP_REQUEST      ARPOP_REQUEST         /* ARP request          */
#define OAL_ARPOP_REPLY        ARPOP_REPLY           /* ARP reply            */
#define OAL_ARPOP_RREQUEST     ARPOP_RREQUEST        /* RARP request         */
#define OAL_ARPOP_RREPLY       ARPOP_RREPLY          /* RARP reply           */
#define OAL_ARPOP_InREQUEST    ARPOP_InREQUEST       /* InARP request        */
#define OAL_ARPOP_InREPLY      ARPOP_InREPLY         /* InARP reply          */
#define OAL_ARPOP_NAK          ARPOP_NAK             /* (ATM)ARP NAK         */

#define  OAL_IPPROTO_UDP     IPPROTO_UDP         /* User Datagram Protocot */
#define  OAL_IPPROTO_ICMPV6  IPPROTO_ICMPV6      /* ICMPv6 */

#define OAL_IEEE80211_MAX_SSID_LEN          32  /* 最大SSID长度 */
#define OAL_INIT_NET            init_net
#define OAL_THIS_MODULE         THIS_MODULE
#define OAL_MSG_DONTWAIT        MSG_DONTWAIT

#if  LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)
#define OAL_NL80211_MAX_NR_CIPHER_SUITES    NL80211_MAX_NR_CIPHER_SUITES
#define OAL_NL80211_MAX_NR_AKM_SUITES       NL80211_MAX_NR_AKM_SUITES
#else
#define OAL_NL80211_MAX_NR_CIPHER_SUITES    5
#define OAL_NL80211_MAX_NR_AKM_SUITES       2
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef gfp_t        oal_gfp_enum_uint8;

#define OAL_NETDEV_TX_OK     NETDEV_TX_OK
#define OAL_NETDEV_TX_BUSY   NETDEV_TX_BUSY
#define OAL_NETDEV_TX_LOCKED NETDEV_TX_LOCKED

/**
 * oal_is_broadcast_ether_addr - Determine if the Ethernet address is broadcast
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Return true if the address is the broadcast address.
 */
#define oal_is_broadcast_ether_addr(addr) is_broadcast_ether_addr(addr)

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
typedef netdev_tx_t  oal_net_dev_tx_enum;
#else
typedef oal_int32    oal_net_dev_tx_enum;
#endif
/* 由于02 device是裸系统，需要使用uint8，所有02用uint8类型 51不改变*/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
typedef oal_uint8  oal_nl80211_auth_type_enum_uint8;
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
typedef enum nl80211_auth_type  oal_nl80211_auth_type_enum_uint8;
#endif
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
/* 加密类型linux-2.6.34内核和linux-2.6.30内核不同 */

struct oal_ether_header
{
    oal_uint8    auc_ether_dhost[ETHER_ADDR_LEN];
    oal_uint8    auc_ether_shost[ETHER_ADDR_LEN];
    oal_uint16   us_ether_type;
}__OAL_DECLARE_PACKED;
typedef struct oal_ether_header oal_ether_header_stru;

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

/* linux 结构体 */

typedef struct sk_buff                      oal_netbuf_stru;
typedef struct sk_buff_head                 oal_netbuf_head_stru;
typedef struct net_device                   oal_net_device_stru;
typedef struct net_device_ops               oal_net_device_ops_stru;
typedef struct ethtool_ops                  oal_ethtool_ops_stru;
typedef struct iw_priv_args                 oal_iw_priv_args_stru;
typedef struct iw_handler_def               oal_iw_handler_def_stru;
typedef struct iw_point                     oal_iw_point_stru;
typedef struct iw_param                     oal_iw_param_stru;
typedef struct iw_freq                      oal_iw_freq_stru;
typedef struct iw_request_info              oal_iw_request_info_stru;
typedef struct rtnl_link_ops                oal_rtnl_link_ops_stru;
typedef struct sockaddr                     oal_sockaddr_stru;
typedef struct net_device_stats             oal_net_device_stats_stru;
typedef struct ifreq                        oal_ifreq_stru;
typedef struct Qdisc                        oal_qdisc_stru;
typedef struct vlan_ethhdr                  oal_vlan_ethhdr_stru;
typedef struct wiphy                        oal_wiphy_stru;
typedef struct wireless_dev                 oal_wireless_dev_stru;
typedef struct cfg80211_ops                 oal_cfg80211_ops_stru;

typedef struct kobj_uevent_env              oal_kobj_uevent_env_stru;
typedef struct iw_quality                   oal_iw_quality_stru;
typedef union  iwreq_data                   oal_iwreq_data_union;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
typedef struct cfg80211_pmksa               oal_cfg80211_pmksa_stru;
#endif

typedef struct key_params                   oal_key_params_stru;

typedef struct cfg80211_scan_request        oal_cfg80211_scan_request_stru;
typedef struct cfg80211_ssid                oal_cfg80211_ssid_stru;
typedef struct cfg80211_sched_scan_request  oal_cfg80211_sched_scan_request_stru;
/*linux-2.6.34内核才有以下两个结构体，加密相关*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
typedef enum nl80211_mfp oal_nl80211_mfp_enum_uint8;
typedef struct cfg80211_connect_params      oal_cfg80211_connect_params_stru;
typedef struct cfg80211_crypto_settings     oal_cfg80211_crypto_settings_stru;
#else
/* linux-2.6.30内核没有这两个加密相关的结构体，命令下发上报也是内核透传，这里打桩 */
/*
typedef struct cfg80211_connect_params
{
    oal_int32                           l_freq;

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
}oal_cfg80211_connect_params_stru;
*/
typedef struct  cfg80211_crypto_settings
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

#endif

typedef struct work_struct                  oal_work_struct_stru;
typedef struct ieee80211_mgmt               oal_ieee80211_mgmt_stru;
typedef struct ieee80211_channel            oal_ieee80211_channel_stru;
typedef struct cfg80211_bss                 oal_cfg80211_bss_stru;
typedef struct rate_info                    oal_rate_info_stru;
typedef struct station_info                 oal_station_info_stru;
typedef struct station_parameters           oal_station_parameters_stru;
typedef enum station_info_flags             oal_station_info_flags;

typedef struct nlattr                       oal_nlattr_stru;
typedef struct genl_family                  oal_genl_family_stru;
typedef struct genl_multicast_group         oal_genl_multicast_group_stru;
typedef struct cfg80211_registered_device   oal_cfg80211_registered_device_stru;

typedef struct ieee80211_rate               oal_ieee80211_rate;
typedef struct ieee80211_channel            oal_ieee80211_channel;
typedef struct ieee80211_supported_band     oal_ieee80211_supported_band;
typedef enum cfg80211_signal_type           oal_cfg80211_signal_type;
typedef enum nl80211_channel_type           oal_nl80211_channel_type;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
typedef enum wiphy_params_flags             oal_wiphy_params_flags;
typedef enum wiphy_flags                    oal_wiphy_flags;
#else
/* linux-2.6.30内核打桩一份wiphy_flags枚举 */
typedef enum wiphy_flags
{
    WIPHY_FLAG_CUSTOM_REGULATORY    = BIT(0),
    WIPHY_FLAG_STRICT_REGULATORY    = BIT(1),
    WIPHY_FLAG_DISABLE_BEACON_HINTS = BIT(2),
    WIPHY_FLAG_NETNS_OK     = BIT(3),
    WIPHY_FLAG_PS_ON_BY_DEFAULT = BIT(4),
    WIPHY_FLAG_4ADDR_AP     = BIT(5),
    WIPHY_FLAG_4ADDR_STATION    = BIT(6),
    WIPHY_FLAG_HAVE_AP_SME          = BIT(17),
    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL	= BIT(21),
}oal_wiphy_flags;
#endif

typedef struct vif_params                   oal_vif_params_stru;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
typedef enum nl80211_key_type               oal_nl80211_key_type;
#else
enum nl80211_key_type {
    NL80211_KEYTYPE_GROUP,
    NL80211_KEYTYPE_PAIRWISE,
    NL80211_KEYTYPE_PEERKEY,
    NUM_NL80211_KEYTYPES
};
typedef enum nl80211_key_type oal_nl80211_key_type;
#endif

typedef struct ieee80211_sta_ht_cap         oal_ieee80211_sta_ht_cap;
typedef struct ieee80211_regdomain          oal_ieee80211_regdomain_stru;
typedef struct cfg80211_update_ft_ies_params    oal_cfg80211_update_ft_ies_stru;
typedef struct cfg80211_ft_event_params         oal_cfg80211_ft_event_stru;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
/*To be implement!*/
typedef struct cfg80211_beacon_data         oal_beacon_data_stru;
typedef struct cfg80211_ap_settings         oal_ap_settings_stru;
typedef struct bss_parameters               oal_bss_parameters;
struct beacon_parameters
{
    oal_uint8 *head, *tail;
    oal_int32 interval, dtim_period;
    oal_int32 head_len, tail_len;
};
typedef struct beacon_parameters            oal_beacon_parameters;
#else
typedef struct beacon_parameters            oal_beacon_parameters;
#endif
typedef struct ieee80211_channel_sw_ie      oal_ieee80211_channel_sw_ie;
typedef struct ieee80211_msrment_ie         oal_ieee80211_msrment_ie;
typedef struct ieee80211_mgmt               oal_ieee80211_mgmt;

typedef struct sock              oal_sock_stru;
typedef struct net               oal_net_stru;
typedef struct module            oal_module_stru;
typedef struct nlmsghdr          oal_nlmsghdr_stru;

typedef struct ethhdr            oal_ethhdr;
typedef struct nf_hook_ops       oal_nf_hook_ops_stru;
typedef struct net_bridge_port   oal_net_bridge_port;

typedef struct ipv6hdr          oal_ipv6hdr_stru;
typedef struct icmp6hdr         oal_icmp6hdr_stru;
typedef struct in6_addr         oal_in6_addr;
typedef struct nd_msg           oal_nd_msg_stru;
typedef struct nd_opt_hdr       oal_nd_opt_hdr;

#define OAL_LL_ALLOCATED_SPACE  LL_ALLOCATED_SPACE

/* netlink相关 */
#define OAL_NLMSG_ALIGNTO                NLMSG_ALIGNTO
#define OAL_NLMSG_ALIGN(_len)            NLMSG_ALIGN(_len)
#define OAL_NLMSG_HDRLEN                 NLMSG_HDRLEN
#define OAL_NLMSG_LENGTH(_len)           NLMSG_LENGTH(_len)
#define OAL_NLMSG_SPACE(_len)            NLMSG_SPACE(_len)
#define OAL_NLMSG_DATA(_nlh)             NLMSG_DATA(_nlh)
#define OAL_NLMSG_PAYLOAD(_nlh, _len)    NLMSG_PAYLOAD(_nlh, _len)
#define OAL_NETLINK_CB(_skb)             NETLINK_CB(_skb)

#define OAL_AF_BRIDGE   AF_BRIDGE   /* Multiprotocol bridge     */
#define OAL_PF_BRIDGE   OAL_AF_BRIDGE

/* Bridge Hooks */
/* After promisc drops, checksum checks. */
#define OAL_NF_BR_PRE_ROUTING   NF_BR_PRE_ROUTING
/* If the packet is destined for this box. */
#define OAL_NF_BR_LOCAL_IN      NF_BR_LOCAL_IN
/* If the packet is destined for another interface. */
#define OAL_NF_BR_FORWARD       NF_BR_FORWARD
/* Packets coming from a local process. */
#define OAL_NF_BR_LOCAL_OUT     NF_BR_LOCAL_OUT
/* Packets about to hit the wire. */
#define OAL_NF_BR_POST_ROUTING  NF_BR_POST_ROUTING
/* Not really a hook, but used for the ebtables broute table */
#define OAL_NF_BR_BROUTING      NF_BR_BROUTING
#define OAL_NF_BR_NUMHOOKS      NF_BR_NUMHOOKS

/* Responses from hook functions. */
#define OAL_NF_DROP             NF_DROP
#define OAL_NF_ACCEPT           NF_ACCEPT
#define OAL_NF_STOLEN           NF_STOLEN
#define OAL_NF_QUEUE            NF_QUEUE
#define OAL_NF_REPEAT           NF_REPEAT
#define OAL_NF_STOP             NF_STOP
#define OAL_NF_MAX_VERDICT      NF_STOP

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

typedef struct ieee80211_iface_limit        oal_ieee80211_iface_limit;
typedef struct ieee80211_iface_combination  oal_ieee80211_iface_combination;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_copy_queue_mapping(oal_netbuf_stru  *to, const oal_netbuf_stru *from)
{
    skb_copy_queue_mapping(to,from);
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
	return skb_put(pst_netbuf, ul_len);
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
    return skb_push(pst_netbuf, ul_len);
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

/*arm64 尾指针变成了偏移*/
#ifndef CONFIG_ARM64
/*tail指针操作请使用skb_put，避免使用该函数*/
OAL_STATIC OAL_INLINE oal_void oal_set_netbuf_tail(oal_netbuf_stru *pst_buf,  oal_uint8  *tail)
{
    pst_buf->tail = tail;
}
#endif

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

/*arm64 尾指针变成了偏移*/
#ifndef CONFIG_ARM64
/*tail指针操作请使用skb_put，避免使用该函数*/
OAL_STATIC OAL_INLINE oal_void oal_set_single_netbuf_tail(oal_netbuf_stru *pst_netbuf,oal_uint8 *puc_tail)
{
    pst_netbuf->tail = puc_tail;
}
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
#if (defined(_PRE_BOARD_SD5610) || defined(_PRE_BOARD_SD5115))
    oal_memcopy(pst_cpu_stat, &kstat_cpu(0).cpustat, OAL_SIZEOF(oal_cpu_usage_stat_stru));
#endif
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define oal_br_should_route_hook     br_should_route_hook

/*****************************************************************************
 函 数 名  : oal_nf_register_hooks
 功能描述  : 注册钩子函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_nf_register_hooks(oal_nf_hook_ops_stru *pst_nf_hook_ops, oal_uint32 ul_num)
{
    return nf_register_hooks(pst_nf_hook_ops, ul_num);
}

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
    nf_unregister_hooks(pst_nf_hook_ops, ul_num);
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
#if (defined(_PRE_BOARD_SD5610) || defined(_PRE_BOARD_SD5115))
    return br_get_port_type(pst_port);
#else
    return ~0;
#endif
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
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_ethhdr *oal_eth_hdr(OAL_CONST oal_netbuf_stru *pst_netbuf)
{
    return eth_hdr(pst_netbuf);
}

#define OAL_RCU_ASSIGN_POINTER(_p, _v)   rcu_assign_pointer(_p, _v)



#endif


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
    return ieee80211_get_channel(pst_wiphy,ul_freq);
}

/* BEGIN : Linux wiphy 结构相关的处理函数 */

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
OAL_STATIC OAL_INLINE oal_wiphy_stru * oal_wiphy_new(oal_cfg80211_ops_stru *ops, oal_int32 sizeof_priv)
{
    return wiphy_new(ops, sizeof_priv);
}

/*****************************************************************************
 函 数 名  : oal_wiphy_register
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
OAL_STATIC OAL_INLINE oal_int32 oal_wiphy_register(oal_wiphy_stru *pst_wiphy)
{
    return wiphy_register(pst_wiphy);
}

/*****************************************************************************
 函 数 名  : oal_wiphy_unregister
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_wiphy_unregister(oal_wiphy_stru *pst_wiphy)
{
    return wiphy_unregister(pst_wiphy);
}

/*****************************************************************************
 函 数 名  : oal_wiphy_free
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
OAL_STATIC OAL_INLINE void oal_wiphy_free(oal_wiphy_stru *pst_wiphy)
{
    wiphy_free(pst_wiphy);
}
/*****************************************************************************
 函 数 名  : oal_wiphy_priv
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
OAL_STATIC OAL_INLINE void *oal_wiphy_priv(oal_wiphy_stru *pst_wiphy)
{
    return wiphy_priv(pst_wiphy);
}

/*****************************************************************************
 函 数 名  : oal_wiphy_apply_custom_regulatory
 功能描述  :
 输入参数  : oal_wiphy_stru *pst_wiphy
             OAL_CONST oal_ieee80211_regdomain *regd
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE void *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE void oal_wiphy_apply_custom_regulatory(oal_wiphy_stru *pst_wiphy, OAL_CONST oal_ieee80211_regdomain_stru *regd)
{
    wiphy_apply_custom_regulatory(pst_wiphy, regd);
}

/* END : Linux wiphy 结构相关的处理函数 */

/* 添加wiphy结构体rts门限赋值 */
OAL_STATIC OAL_INLINE void oal_wiphy_set_rts(oal_wiphy_stru *pst_wiphy, oal_uint32 ul_rts_threshold)
{
    #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
        pst_wiphy->rts_threshold  =  ul_rts_threshold;
    #endif
    return;
}

/* 添加wiphy结构体分片门限赋值 */
OAL_STATIC OAL_INLINE void oal_wiphy_set_frag(oal_wiphy_stru *pst_wiphy, oal_uint32 ul_frag_threshold)
{
    #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
        pst_wiphy->frag_threshold  =  ul_frag_threshold;
    #endif
    return;
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
OAL_STATIC OAL_INLINE oal_uint16  oal_eth_type_trans(oal_netbuf_stru *pst_netbuf, oal_net_device_stru *pst_device)
{
    return eth_type_trans(pst_netbuf, pst_device);
}

/*****************************************************************************
 函 数 名  : oal_ether_setup
 功能描述  : 网络设备启动接口
 输入参数  : oal_net_device_stru:网络设备引用
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC OAL_INLINE oal_void oal_ether_setup(oal_net_device_stru *p_net_device)
{
    if (OAL_PTR_NULL == p_net_device)
    {
        return;
    }

    ether_setup(p_net_device);

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
OAL_STATIC OAL_INLINE oal_net_device_stru* oal_dev_get_by_name(const oal_int8 *pc_name)
{
    return dev_get_by_name(&init_net, pc_name);
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
#define oal_dev_put(_pst_dev) dev_put(_pst_dev)

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
OAL_STATIC OAL_INLINE oal_void  oal_net_close_dev(oal_net_device_stru *pst_netdev)
{
    rtnl_lock();
    dev_close(pst_netdev);
    rtnl_unlock();
}

/*****************************************************************************
 函 数 名  : oal_net_alloc_netdev
 功能描述  : 分配网络设备
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
OAL_STATIC OAL_INLINE oal_net_device_stru * oal_net_alloc_netdev(oal_uint32 ul_sizeof_priv, oal_int8 *puc_name,
                                                  oal_void *p_set_up)
{
    if ((OAL_PTR_NULL == puc_name) || (OAL_PTR_NULL == p_set_up))
    {
        return OAL_PTR_NULL;
    }
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 18, 0))
    return alloc_netdev(ul_sizeof_priv, puc_name, NET_NAME_UNKNOWN, p_set_up);
#else
    return alloc_netdev(ul_sizeof_priv, puc_name, p_set_up);
#endif
}

//#ifdef _PRE_WLAN_FEATURE_FLOWCTL
/*****************************************************************************
 函 数 名  : oal_net_alloc_netdev_mqs
 功能描述  : 分配网络设备,包含多个队列
 输入参数  : ul_sizeof_priv: 私有结构空间长度
           : puc_name 设备名称
           : p_set_up:启动函数指针
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_net_device_stru * oal_net_alloc_netdev_mqs(oal_uint32 ul_sizeof_priv, oal_int8 *puc_name,
                                                  oal_void *p_set_up, oal_uint32 ul_txqs, oal_uint32 ul_rxqs)
{
    if ((OAL_PTR_NULL == puc_name) || (OAL_PTR_NULL == p_set_up))
    {
        return OAL_PTR_NULL;
    }
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 18, 0))
    return alloc_netdev_mq(ul_sizeof_priv, puc_name, NET_NAME_UNKNOWN, p_set_up, ul_txqs);
#else
    return alloc_netdev_mq(ul_sizeof_priv, puc_name, p_set_up, ul_txqs);
#endif
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
    if (OAL_PTR_NULL == pst_dev)
    {
        return;
    }

    return netif_tx_wake_all_queues(pst_dev);
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
    if (OAL_PTR_NULL == pst_dev)
    {
        return;
    }

    return netif_tx_stop_all_queues(pst_dev);
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
    if (OAL_PTR_NULL == pst_dev)
    {
        return;
    }

    return netif_wake_subqueue(pst_dev, us_queue_idx);
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
    if (OAL_PTR_NULL == pst_dev)
    {
        return;
    }

    return netif_stop_subqueue(pst_dev, us_queue_idx);
}


//#endif

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

    free_netdev(pst_netdev);
}

/*****************************************************************************
 函 数 名  : oal_net_register_netdev
 功能描述  : 注册网络设备
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
OAL_STATIC OAL_INLINE oal_int32 oal_net_register_netdev(oal_net_device_stru *p_net_device)
{
    if (OAL_PTR_NULL == p_net_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*TBD,Just For HCC*/
    OAL_NETDEVICE_HEADROOM(p_net_device) = 64;
    OAL_NETDEVICE_TAILROOM(p_net_device) = 32;
#endif

    return register_netdev(p_net_device);

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
    if (OAL_PTR_NULL == p_net_device)
    {
        return ;
    }

    unregister_netdev(p_net_device);
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
OAL_STATIC OAL_INLINE oal_void* oal_net_device_priv(oal_net_device_stru *pst_net_dev)
{
    return netdev_priv(pst_net_dev);
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
OAL_STATIC OAL_INLINE oal_int32  oal_net_device_open(oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */
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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_close(oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */

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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_set_macaddr(oal_net_device_stru *pst_dev, oal_void *pst_addr)
{
    /* TBD netdevice相关接口函数后续统一优化 */

    oal_sockaddr_stru *pst_mac;

    pst_mac = (oal_sockaddr_stru *)pst_addr;

    oal_memcopy(pst_dev->dev_addr, pst_mac->sa_data, 6);

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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_init(oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */

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
OAL_STATIC OAL_INLINE oal_net_device_stats_stru *oal_net_device_get_stats(oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */

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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_ioctl(oal_net_device_stru *pst_dev, oal_ifreq_stru *pst_ifr, oal_int32 ul_cmd)
{
    /* TBD netdevice相关接口函数后续统一优化 */
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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_multicast_list(oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */

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
OAL_STATIC OAL_INLINE oal_int32 oal_net_device_change_mtu(oal_net_device_stru *pst_dev, oal_int32 ul_mtu)
{
    /* TBD 需要优化 */
    pst_dev->mtu = ul_mtu;
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

OAL_STATIC OAL_INLINE oal_int32 oal_net_device_hardstart(oal_netbuf_stru *pst_skb, oal_net_device_stru *pst_dev)
{
    /* TBD netdevice相关接口函数后续统一优化 */

    return OAL_SUCC;
}


/* 在dev.c中定义，用来在中断上下文或者非中断上下文中释放skb */
extern void dev_kfree_skb_any(struct sk_buff *skb);

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
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_reserve(oal_netbuf_stru *pst_netbuf, oal_int32 l_len)
{
    skb_reserve(pst_netbuf, l_len);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_alloc
 功能描述  : 为netbuf申请内存
 输入参数  : ul_size: 分配内存的大小
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
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_alloc(oal_uint32 ul_size, oal_int32 l_reserve, oal_int32 l_align)
{
    oal_netbuf_stru *pst_netbuf;
    oal_uint32       ul_offset;

    /* 保证data部分的size不会再字节对齐后小于预先想分配的大小 */
    if (l_align)
    {
        ul_size += (l_align - 1);
    }

    pst_netbuf = dev_alloc_skb(ul_size);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_PTR_NULL;
    }

    skb_reserve(pst_netbuf, l_reserve);

    if (l_align)
    {
        /* 计算为了能使4字节对齐的偏移量 */
        ul_offset = (oal_int32)(((oal_uint)pst_netbuf->data) % (oal_uint)l_align);

        if (ul_offset)
        {
            skb_reserve(pst_netbuf, l_align - ul_offset);
        }
    }

    return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_free
 功能描述  : 释放报文结构体内存空间, 非硬中断环境下使用
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
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_free(oal_netbuf_stru *pst_netbuf)
{
    dev_kfree_skb(pst_netbuf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_free_any
 功能描述  : 释放报文结构体内存空间，可用于中断环境
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
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_free_any(oal_netbuf_stru *pst_netbuf)
{
    dev_kfree_skb_any(pst_netbuf);
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
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_unshare(oal_netbuf_stru *pst_netbuf, oal_gfp_enum_uint8 en_pri)
{
    return skb_unshare(pst_netbuf, en_pri);
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
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_copy(oal_netbuf_stru *pst_netbuf, oal_gfp_enum_uint8 en_priority)
{
    return skb_copy(pst_netbuf, en_priority);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
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
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_data(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->data;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
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
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_header(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->data;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_data
 功能描述  : 获取skb数据头部
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
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_payload(oal_netbuf_stru *pst_netbuf)
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
    return skb_end_pointer(pst_netbuf);
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
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_get_len(oal_netbuf_stru *pst_netbuf)
{
    return pst_netbuf->len;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_headroom
 功能描述  :
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
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_headroom(const oal_netbuf_stru *pst_netbuf)
{
    return skb_headroom(pst_netbuf);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_tailroom
 功能描述  : 获取尾部空间大小
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
OAL_STATIC OAL_INLINE oal_uint32  oal_netbuf_tailroom(const oal_netbuf_stru *pst_netbuf)
{
    return skb_tailroom(pst_netbuf);
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
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_realloc_headroom(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_headroom)
{
    if(pskb_expand_head(pst_netbuf, ul_headroom, 0, GFP_ATOMIC))
    {
        dev_kfree_skb(pst_netbuf);
        pst_netbuf = OAL_PTR_NULL;
    }

    return pst_netbuf;
}

/*****************************************************************************
 函 数 名  : oal_netbuf_realloc_tailroom
 功能描述  : skb尾部空间扩充
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
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_realloc_tailroom(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_tailroom)
{
    if(OAL_LIKELY(!pskb_expand_head(pst_netbuf, 0, ul_tailroom, GFP_ATOMIC)))
    {
        return pst_netbuf;
    }

    /* unlikely path */
    dev_kfree_skb_any(pst_netbuf);

    return OAL_PTR_NULL;
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
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_cb(oal_netbuf_stru *pst_netbuf)
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
    skb_queue_tail(pst_head, pst_buf);
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
    return skb_queue_len(pst_head);
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
    skb_unlink(pst_buf, pst_list_head);
}

OAL_STATIC OAL_INLINE oal_void __netbuf_unlink(struct sk_buff *skb, struct sk_buff_head *list)
{
    struct sk_buff *next, *prev;

    list->qlen--;
    next       = skb->next;
    prev       = skb->prev;
    skb->next  = skb->prev = NULL;
    next->prev = prev;
    prev->next = next;
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
    return skb_dequeue(pst_list_head);
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
{
    return skb_queue_head(pst_list_head, netbuf);
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
  1.日    期   : 2012年12月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_netbuf_list_purge(oal_netbuf_head_stru *pst_list_head)
{
    skb_queue_purge(pst_list_head);
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
    return skb_queue_empty(pst_list_head);
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
#if 0
    oal_spin_lock_init(&pst_list_head->lock);
    pst_list_head->prev = pst_list_head->next = (oal_netbuf_stru *)pst_list_head;
    pst_list_head->qlen = 0;
#endif
    skb_queue_head_init(pst_list_head);
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
    skb_queue_tail(list, newsk);
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
    skb_queue_splice_init(list,head);
}
/*****************************************************************************
 函 数 名  : oal_netbuf_queue_splice_tail_init
 功能描述  :  join two skb lists and reinitialise the emptied list
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
    skb_queue_splice_tail_init(list,head);
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
    return skb_dequeue_tail(head);
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
    skb_queue_head_init(list);
}

/*****************************************************************************
 函 数 名  : oal_netbuf_peek
 输入参数  : pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  : 链表中第一个元素
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_netbuf_stru* oal_netbuf_peek(oal_netbuf_head_stru *pst_head)
{
    return skb_peek(pst_head);
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
    return skb_peek_tail(pst_head);
}
#if 0
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
  2.接口废弃，请使用oal_netbuf_trim

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8* oal_netbuf_depad(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len)
{
    pst_netbuf->tail -= ul_len;

    pst_netbuf->len -= ul_len;

    return pst_netbuf->tail;
}
#endif

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

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_netbuf) || (OAL_PTR_NULL == pst_expect_netbuf)))
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

        pst_netbuf = *pst_expect_netbuf;
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
    oal_int32   l_flags = GFP_KERNEL;

    if (in_interrupt() || irqs_disabled())
    {
        l_flags = GFP_ATOMIC;
    }

    return skb_clone(pst_buf, l_flags);
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

    oal_atomic_dec(&(pst_buf->users));

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

    oal_atomic_inc(&(pst_buf->users));

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
    return pst_netbuf_head->qlen;
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
    return skb_get(pst_netbuf);
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
OAL_STATIC OAL_INLINE oal_void  oal_netbuf_queue_purge(oal_netbuf_head_stru  *pst_netbuf_head)
{
    skb_queue_purge(pst_netbuf_head);
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
                                                 oal_netbuf_stru    *pst_netbuf,
                                                 oal_int32           ul_headroom,
                                                 oal_int32           ul_tailroom,
                                                 oal_gfp_enum_uint8  en_gfp_mask)
{
    return skb_copy_expand(pst_netbuf, ul_headroom, ul_tailroom, en_gfp_mask);
}

OAL_STATIC OAL_INLINE oal_int32  oal_netif_rx_hw(oal_netbuf_stru *pst_netbuf)
{
    if (!in_interrupt())
    {
        return netif_rx_ni(pst_netbuf);
    }
    else
    {
        return netif_rx(pst_netbuf);
    }
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
    return netif_rx(pst_netbuf);
}

/*****************************************************************************
 函 数 名  : oal_netif_rx_ni
 功能描述  : 将skb发给桥  !in_interrupt()
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
    return netif_rx_ni(pst_netbuf);
}


OAL_STATIC OAL_INLINE oal_void  oal_local_bh_disable(oal_void)
{
    local_bh_disable();
}

OAL_STATIC OAL_INLINE oal_void  oal_local_bh_enable(oal_void)
{
    local_bh_enable();
}

/*****************************************************************************
 函 数 名  : oal_cpu_clock
 功能描述  : 获取时间戳
 输入参数  :
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
    return cpu_clock(UINT_MAX);
}

OAL_STATIC OAL_INLINE oal_int32 oal_netbuf_expand_head(oal_netbuf_stru *netbuf,
                                                        oal_int32 nhead, oal_int32 ntail,
		                                                oal_int32 gfp_mask)
{
    return pskb_expand_head(netbuf, nhead, ntail, gfp_mask);
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    // host evn android 4.4 netlink_kernel_create API is changed
    struct netlink_kernel_cfg cfg;
    cfg.groups = 0;
    cfg.input = input;
    cfg.cb_mutex = NULL;

    return netlink_kernel_create(pst_net, l_unit, &cfg);
#else
    return netlink_kernel_create(pst_net, l_unit, ul_groups, input, pst_cb_mutex, pst_module);
#endif
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    netlink_kernel_release(pst_sock);
    return;
#else
    netlink_kernel_release(pst_sock);
#endif
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
    return nlmsg_put(pst_netbuf, ul_pid, ul_seq, l_type, l_payload, l_flags);
}

/*****************************************************************************
 函 数 名  : oal_nla_put_u32
 功能描述  : 给netlink数据中添加32位的信息
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
    return nla_put_u32(pst_skb, l_attrtype, ul_value);
}

/*****************************************************************************
 函 数 名  : oal_nla_put
 功能描述  : 给netlink消息中添加8位的信息
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
    return nla_put(pst_skb, l_attrtype, l_attrlen, p_data);
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_new
 功能描述  : 分配一个新的netlink消息
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
OAL_STATIC OAL_INLINE  oal_netbuf_stru *oal_nlmsg_new(oal_int32 payload, oal_gfp_enum_uint8 flags)
{
    return nlmsg_new(payload, flags);
}

/*****************************************************************************
 函 数 名  : oal_nlmsg_free
 功能描述  : 释放netlink消息
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
    return nlmsg_free(pst_skb);
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_multicast
 功能描述  : 调用netlink广播发送函数来发送netlink消息
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
OAL_STATIC OAL_INLINE oal_int32  oal_genlmsg_multicast(
                    oal_netbuf_stru *pst_skb, oal_uint32 ul_pid,
				    oal_uint32 ul_group, oal_gfp_enum_uint8 flags)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
    return genlmsg_multicast(pst_skb, ul_pid, ul_group, flags);
#else
    /* Linux 新版本已经提供其他接口上报信息，不需要通过genlmsg_multicast 上报 */
    return OAL_SUCC;
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(4, 1, 0)) */
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_put
 功能描述  : 给netlink消息中添加对应命令
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
OAL_STATIC OAL_INLINE oal_void *oal_genlmsg_put(
                oal_netbuf_stru *pst_skb, oal_uint32 ul_pid, oal_uint32 ul_seq,
				oal_genl_family_stru *pst_family, oal_int32 flags, oal_uint8 cmd)
{
    return genlmsg_put(pst_skb, ul_pid, ul_seq, pst_family, flags, cmd);
}

/*****************************************************************************
 函 数 名  : oal_nla_nest_start
 功能描述  : 开始处理netlink消息的起始位置
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
    return nla_nest_start(pst_skb, l_attrtype);
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_cancel
 功能描述  : 取消netlink消息封装
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
OAL_STATIC OAL_INLINE oal_void  oal_genlmsg_cancel(oal_netbuf_stru *pst_skb, oal_void *pst_hdr)
{
    return genlmsg_cancel(pst_skb, pst_hdr);
}

/*****************************************************************************
 函 数 名  : oal_nla_nest_end
 功能描述  : 完成netlink消息的所有填充
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
OAL_STATIC OAL_INLINE oal_int32  oal_nla_nest_end(oal_netbuf_stru *pst_skb, oal_nlattr_stru *pst_start)
{
    return nla_nest_end(pst_skb, pst_start);
}

/*****************************************************************************
 函 数 名  : oal_genlmsg_end
 功能描述  : netlink消息结束
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

OAL_STATIC OAL_INLINE oal_int32  oal_genlmsg_end(oal_netbuf_stru *pst_skb, oal_void *pst_hdr)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 1, 0))
    return genlmsg_end(pst_skb, pst_hdr);
#else
    genlmsg_end(pst_skb, pst_hdr);
    return OAL_SUCC;
#endif
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
#if (defined(_PRE_BOARD_SD5610) || defined(_PRE_BOARD_SD5115))
    struct skb_shared_info *shinfo;

    /* tail之前的成员初始化为0 */
    memset(pst_netbuf, 0, offsetof(struct sk_buff, tail));

    /* 初始化skb的share info */
    shinfo = skb_shinfo(pst_netbuf);
    shinfo->nr_frags  = 0;
    shinfo->gso_size = 0;
    shinfo->gso_segs = 0;
    shinfo->gso_type = 0;
    shinfo->ip6_frag_id = 0;
    shinfo->tx_flags.flags = 0;
    shinfo->frag_list = NULL;
    memset(&shinfo->hwtstamps, 0, sizeof(shinfo->hwtstamps));

    /* data tail指针复位 */
    pst_netbuf->data = pst_netbuf->head + ul_data_offset;
    pst_netbuf->tail = pst_netbuf->data;
    pst_netbuf->len  = 0;
#endif

}

/*****************************************************************************
 函 数 名  : oal_wiphy_to_dev
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
OAL_STATIC OAL_INLINE oal_cfg80211_registered_device_stru *oal_wiphy_to_dev(oal_wiphy_stru *pst_wiphy)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 18, 0))
    return wiphy_to_rdev(pst_wiphy);
#else
    return wiphy_to_dev(pst_wiphy);
#endif
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
    return netlink_unicast(pst_sock, pst_netbuf, ul_pid, l_nonblock);
}

/*****************************************************************************
 函 数 名  : oal_netlink_broadcast
 功能描述  : 封装内核netlink广播发送函数
 输入参数  :
             pst_sock:    Netlink接口的socket
             pst_netbuf:  数据消息内存
             ul_pid:      Pid值
             ul_group:    组播组
             en_gfp:      不可以睡眠的原子上下文分配内存
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_netlink_broadcast(
                oal_sock_stru *pst_sock, oal_netbuf_stru *pst_netbuf,
                oal_uint32 ul_pid, oal_int32 ul_group,oal_gfp_enum_uint8  en_gfp)
{
    return netlink_broadcast(pst_sock, pst_netbuf, ul_pid, ul_group, en_gfp);
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
    return skb_copy_bits(pst_netbuf_sc, ul_offset, p_dst, ul_len);
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
    return skb_trim(pst_netbuf, pst_netbuf->len - ul_len);
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
    if (skb_is_nonlinear(pst_netbuf_head))
    {
        OAL_IO_PRINT("oal_netbuf_concat:pst_netbuf_head not linear ");
    }

    if (skb_tailroom(pst_netbuf_head) < pst_netbuf->len)
    {
        OAL_IO_PRINT("not enough space for concat");
    }

    memcpy(skb_tail_pointer(pst_netbuf_head), pst_netbuf->data, pst_netbuf->len);

    skb_put(pst_netbuf_head, pst_netbuf->len);

    dev_kfree_skb(pst_netbuf);
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
        skb_trim(pst_netbuf, ul_len);
    }
    else
    {
        skb_put(pst_netbuf, (ul_len - pst_netbuf->len));
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
    pst_netbuf->protocol = ETH_P_CONTROL;
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
#if defined(_PRE_BOARD_SD5115)
        hi_kernel_wdt_clear();
#endif
#endif
}

/*****************************************************************************
 函 数 名  : oal_in_aton
 功能描述  : IP 地址转换（字符串 -> 数值）
  输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_in_aton(oal_uint8 *pul_str)
{
    return (in_aton(pul_str));
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
#else
    ipv6_addr_copy(pst_ipv6_dst, pst_ipv6_src);
#endif
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
    return dev_hard_header(pst_nb, pst_net_dev, us_type, puc_addr_d, puc_addr_s, ul_len);
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
    return csum_ipv6_magic(pst_ipv6_s, pst_ipv6_d, ul_len, us_proto, ul_sum);
}

/*****************************************************************************
 函 数 名  : oal_csum_partial
 功能描述  : 计算check sum
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
    return csum_partial(p_buff, l_len, ul_sum);
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
OAL_STATIC OAL_INLINE oal_int32  oal_ipv6_addr_type(oal_in6_addr *pst_ipv6)
{
#ifdef _PRE_WLAN_FEATURE_SUPPORT_IPV6
    return ipv6_addr_type(pst_ipv6);
#else  /* 不支持ipv6产品，相关函数无法获取，直接返回OAL_IPV6_ADDR_RESERVED 0x2000U */
    return (oal_int32)IPV6_ADDR_RESERVED;
#endif
}
/*****************************************************************************
 函 数 名  : oal_pskb_may_pull
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
OAL_STATIC OAL_INLINE oal_int32  oal_pskb_may_pull(oal_netbuf_stru *pst_nb, oal_uint32 ul_len)
{
    return pskb_may_pull(pst_nb, ul_len);
}

/*****************************************************************************
 函 数 名  : oal_arp_create
 功能描述  : 构造arp帧
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
    return arp_create(l_type, l_ptype, ul_dest_ip, pst_dev, ul_src_ip, puc_dest_hw, puc_src_hw, puc_target_hw);
}

/* get the queue index of the input skbuff */
OAL_STATIC OAL_INLINE oal_uint16 oal_skb_get_queue_mapping(oal_netbuf_stru  *pst_skb)
{
    return skb_get_queue_mapping(pst_skb);
}

OAL_STATIC OAL_INLINE oal_void oal_skb_set_queue_mapping(oal_netbuf_stru  *pst_skb, oal_uint16 queue_mapping)
{
    skb_set_queue_mapping(pst_skb, queue_mapping);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_net.h */
