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

#ifndef __OAL_NET_H__
#define __OAL_NET_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "platform_spec.h"
#include "oal_types.h"
#include "oal_mm.h"
#include "oal_util.h"
#include "oal_schedule.h"
#include "oal_list.h"
#include "arch/oal_net.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAL_IF_NAME_SIZE   16
#define OAL_NETBUF_DEFAULT_DATA_OFFSET 48  /* 5115上实际测得data比head大48，用于netbuf data指针复位 */

#define OAL_ASSOC_REQ_IE_OFFSET        28    /* 上报内核关联请求帧偏移量 */
#define OAL_ASSOC_RSP_IE_OFFSET        30    /* 上报内核关联响应帧偏移量 */
#define OAL_AUTH_IE_OFFSET             30
#define OAL_FT_ACTION_IE_OFFSET        40
#define OAL_ASSOC_RSP_FIXED_OFFSET     6     /* 关联响应帧帧长FIXED PARAMETERS偏移量 */
#define OAL_MAC_ADDR_LEN               6
#define OAL_PMKID_LEN                  16
#define OAL_WPA_KEY_LEN                32
#define OAL_WPA_SEQ_LEN                16
#define OAL_WLAN_SA_QUERY_TR_ID_LEN    2

/*
 * Byte order/swapping support.
 */
#define OAL_LITTLE_ENDIAN    1234
#define OAL_BIG_ENDIAN       4321
#define OAL_BYTE_ORDER OAL_BIG_ENDIAN

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)) && defined (_PRE_WLAN_FEATURE_DFR)
/* hi1102  由于内核注册端口28 NETLINK_HISI_WIFI_MSG已被占用，所以此处使用未使用的27 NETLINK_HISI_WIFI_PMF */
#define NETLINK_DEV_ERROR 27
#endif
/*****************************************************************************
  2.10 IP宏定义
*****************************************************************************/

#define WLAN_DSCP_PRI_SHIFT         2
#define WLAN_IP_PRI_SHIFT           5
#define WLAN_IPV6_PRIORITY_MASK     0x0FF00000
#define WLAN_IPV6_PRIORITY_SHIFT    20

/*****************************************************************************
  2.11 VLAN宏定义
*****************************************************************************/


/*****************************************************************************
  2.12 LLC SNAP宏定义
*****************************************************************************/
#define LLC_UI                  0x3
#define SNAP_LLC_FRAME_LEN      8
#define SNAP_LLC_LSAP           0xaa
#define SNAP_RFC1042_ORGCODE_0  0x00
#define SNAP_RFC1042_ORGCODE_1  0x00
#define SNAP_RFC1042_ORGCODE_2  0x00
#define SNAP_BTEP_ORGCODE_0     0x00
#define SNAP_BTEP_ORGCODE_1     0x00
#define SNAP_BTEP_ORGCODE_2     0xf8

/*****************************************************************************
  2.13 ETHER宏定义
*****************************************************************************/
#define ETHER_ADDR_LEN  6   /* length of an Ethernet address */
#define ETHER_TYPE_LEN  2   /* length of the Ethernet type field */
#define ETHER_CRC_LEN   4   /* length of the Ethernet CRC */
#define ETHER_HDR_LEN   14
#define ETHER_MAX_LEN   1518
#define ETHER_MTU        (ETHER_MAX_LEN - ETHER_HDR_LEN - ETHER_CRC_LEN)

/* #ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY */
OAL_STATIC OAL_INLINE oal_uint8 a2x(const char c)
{
    if (c >= '0' && c <= '9')
    {
        return (oal_uint8)oal_atoi(&c);
    }
    if (c >= 'a' && c <= 'f')
    {
        return (oal_uint8)0xa + (oal_uint8)(c-'a');
    }
    if (c >= 'A' && c <= 'F')
    {
        return (oal_uint8)0xa + (oal_uint8)(c-'A');
    }
    return 0;
}

/*convert a string,which length is 18, to a macaddress data type.*/
#define MAC_STR_LEN 18
#define COPY_STR2MAC(mac,str)  \
    do { \
        oal_uint8 i; \
        for(i = 0; i < OAL_MAC_ADDR_LEN; i++) {\
            mac[i] = (oal_uint8)(a2x(str[i*3]) << 4) + a2x(str[i*3 + 1]);\
        }\
    } while(0)
/* #endif */

/* ip头到协议类型字段的偏移 */
#define IP_PROTOCOL_TYPE_OFFSET  9
#define IP_HDR_LEN               20

/* CCMP加密字节数 */
#define WLAN_CCMP_ENCRYP_LEN 16


/* is address mcast? */
#define ETHER_IS_MULTICAST(_a)   (*(_a) & 0x01)

/* is address bcast? */
#define ETHER_IS_BROADCAST(_a)   \
    ((_a)[0] == 0xff &&          \
     (_a)[1] == 0xff &&          \
     (_a)[2] == 0xff &&          \
     (_a)[3] == 0xff &&          \
     (_a)[4] == 0xff &&          \
     (_a)[5] == 0xff)

//#define ETHER_IS_IPV4_MULTICAST(_a)  (*(_a) == 0x01)      A公司的判断条件不合理
#define ETHER_IS_IPV4_MULTICAST(_a)  ((_a[0]) == 0x01 &&    \
                                      (_a[1]) == 0x00 &&    \
                                      (_a[2]) == 0x5e)

#define WLAN_DATA_VIP_TID              WLAN_TIDNO_BCAST

/* wiphy  */
#define IEEE80211_HT_MCS_MASK_LEN   10

/* ICMP codes for neighbour discovery messages */
#define OAL_NDISC_ROUTER_SOLICITATION       133
#define OAL_NDISC_ROUTER_ADVERTISEMENT      134
#define OAL_NDISC_NEIGHBOUR_SOLICITATION    135
#define OAL_NDISC_NEIGHBOUR_ADVERTISEMENT   136

#define OAL_ND_OPT_TARGET_LL_ADDR           2
#define OAL_ND_OPT_SOURCE_LL_ADDR           1
#define OAL_IPV6_ADDR_ANY                   0x0000U
#define OAL_IPV6_ADDR_MULTICAST             0x0002U
#define OAL_IPV6_MAC_ADDR_LEN               16

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
//WRAP SKB marks used by the hooks to optimize
#define OAL_PROXYSTA_MARK_DROPPED    0x1000    /*mark used to drop short circuited pkt*/
#define OAL_PROXYSTA_MARK_ACCEPT     0x1001    /*mark used to accecpt pkt, no check required*/
#define OAL_PROXYSTA_MARK_ROUTE      0x1002    /*mark used allow local deliver to the interface*/
#define OAL_WRAP_BR_MARK_FLOOD       0x8001    /*Special mark used to detect bridge flooded pkt*/
#endif

/*
 * support for ARP/ND offload. add by:  2015.6.12
 */
#define OAL_IPV4_ADDR_SIZE                    4
#define OAL_IPV6_ADDR_SIZE                    16
#define OAL_IP_ADDR_MAX_SIZE                  OAL_IPV6_ADDR_SIZE

/* IPv4受限广播: 255.255.255.255 , IPv4直接广播: 如192.168.10.255 */
#define OAL_IPV4_IS_BROADCAST(_a)             ((oal_uint8)((_a)[3]) == 0xff)

/* IPv4多播范围: 224.0.0.0--239.255.255.255 */
#define OAL_IPV4_IS_MULTICAST(_a)             ((oal_uint8)((_a)[0]) >= 224 && ((oal_uint8)((_a)[0]) <= 239))

/* IPv6组播地址: FFXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX(第一个字节全一) */
#define OAL_IPV6_IS_MULTICAST(_a)             ((oal_uint8)((_a)[0]) == 0xff)


/* IPv6未指定地址: ::/128 ,该地址仅用于接口还没有被分配IPv6地址时与其它节点
   通讯作为源地址,例如在重复地址检测DAD中会出现. */
#define OAL_IPV6_IS_UNSPECIFIED_ADDR(_a)   \
     ((_a)[0]  == 0x00 &&          \
      (_a)[1]  == 0x00 &&          \
      (_a)[2]  == 0x00 &&          \
      (_a)[3]  == 0x00 &&          \
      (_a)[4]  == 0x00 &&          \
      (_a)[5]  == 0x00 &&          \
      (_a)[6]  == 0x00 &&          \
      (_a)[7]  == 0x00 &&          \
      (_a)[8]  == 0x00 &&          \
      (_a)[9]  == 0x00 &&          \
      (_a)[10] == 0x00 &&          \
      (_a)[11] == 0x00 &&          \
      (_a)[12] == 0x00 &&          \
      (_a)[13] == 0x00 &&          \
      (_a)[14] == 0x00 &&          \
      (_a)[15] == 0x00)


/* IPv6链路本地地址: 最高10位值为1111111010, 例如:FE80:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX  */
#define OAL_IPV6_IS_LINK_LOCAL_ADDR(_a)       (((_a)[0] == 0xFE) && ((_a)[1] >> 6 == 2))




 /*****************************************************************************
   枚举名  : oal_mem_state_enum_uint8
   协议表格:
   枚举说明: 内存块状态
 *****************************************************************************/
typedef enum
{
    OAL_MEM_STATE_FREE  = 0,            /* 该内存空闲 */
    OAL_MEM_STATE_ALLOC,                /* 该内存已分配 */

    OAL_MEM_STATE_BUTT
}oal_mem_state_enum;
typedef oal_uint8 oal_mem_state_enum_uint8;

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 以下不区分操作系统 */
/* 内核下发的扫描类型 */
typedef enum
{
    OAL_PASSIVE_SCAN        = 0,
    OAL_ACTIVE_SCAN         = 1,

    OAL_SCAN_BUTT
}oal_scan_enum;
typedef oal_uint8 oal_scan_enum_uint8;

/* 内核下发的扫描频段 */
typedef enum
{
    OAL_SCAN_2G_BAND        = 1,
    OAL_SCAN_5G_BAND        = 2,
    OAL_SCAN_ALL_BAND       = 3,

    OAL_SCAN_BAND_BUTT
}oal_scan_band_enum;
typedef oal_uint8 oal_scan_band_enum_uint8;

/* hostapd 下发私有命令 */
enum HWIFI_IOCTL_CMD
{
    /*
     *IOCTL_CMD的起始值由0修改为0x8EE0，修改原因：51 WiFi模块和类似于dhdutil之类的其他模块共用同一个ioctl通道，
     *而51命令的枚举值从0开始，其他模块下发的ioctl命令也包含从0开始的这部分，这样就会同时“组播”到自己的模块和WiFi模块，
     *从而对WiFi模块的功能产生影响。所以将51 WiFi模块命令的枚举值调整到0x8EE0起，便规避了其他模块命令的影响。
     */
    HWIFI_IOCTL_CMD_GET_STA_ASSOC_REQ_IE = 0x8EE0,       /* get sta assocate request ie */
    HWIFI_IOCTL_CMD_SET_AP_AUTH_ALG,            /* set auth alg to driver */
    HWIFI_IOCTL_CMD_SET_COUNTRY,                /* 设置国家码 */
    HWIFI_IOCTL_CMD_SET_SSID,                   /* 设置ssid */
    HWIFI_IOCTL_CMD_SET_MAX_USER,               /* 设置最大用户数 */
    HWIFI_IOCTL_CMD_SET_FREQ,                   /* 设置频段 */
    HWIFI_IOCTL_CMD_SET_WPS_IE,                 /* 设置AP WPS 信息元素 */
    HWIFI_IOCTL_CMD_PRIV_CONNECT,               /* linux-2.6.30 sta发起connect */
    HWIFI_IOCTL_CMD_PRIV_DISCONNECT,            /* linux-2.6.30 sta发起disconnect */
    HWIFI_IOCTL_CMD_SET_FRAG,                   /* 设置分片门限值 */
    HWIFI_IOCTL_CMD_SET_RTS,                    /* 设置RTS 门限值 */

    HWIFI_IOCTL_CMD_NUM
};

enum APP_IE_TYPE
{
    OAL_APP_BEACON_IE       = 0,
    OAL_APP_PROBE_REQ_IE    = 1,
    OAL_APP_PROBE_RSP_IE    = 2,
    OAL_APP_ASSOC_REQ_IE    = 3,
    OAL_APP_ASSOC_RSP_IE    = 4,
    OAL_APP_FT_IE           = 5,
    OAL_APP_REASSOC_REQ_IE  = 6,
    OAL_APP_IE_NUM
};
typedef oal_uint8 en_app_ie_type_uint8;

typedef enum _wlan_net_queue_type_
{
    WLAN_HI_QUEUE = 0,
	WLAN_NORMAL_QUEUE,

    WLAN_TCP_DATA_QUEUE,
    WLAN_TCP_ACK_QUEUE,

    WLAN_UDP_BK_QUEUE,
    WLAN_UDP_BE_QUEUE,
    WLAN_UDP_VI_QUEUE,
    WLAN_UDP_VO_QUEUE,

    WLAN_NET_QUEUE_BUTT
} wlan_net_queue_type;

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

/* net_device ioctl结构体定义 */
/* hostapd/wpa_supplicant 下发的信息元素结构 */
/* 该结构为事件内存池大小，保存从hostapd/wpa_supplicant下发的ie 信息 */
/* 注意: 整个结构体长度为事件内存池大小，如果事件内存池有修改，则需要同步修改app 数据结构 */
struct oal_app_ie
{
    oal_uint32              ul_ie_len;
    en_app_ie_type_uint8    en_app_ie_type;
    oal_uint8               auc_rsv[3];
    /* auc_ie 中保存信息元素，长度 = (事件内存池大小 - 保留长度) */
    oal_uint8               auc_ie[WLAN_WPS_IE_MAX_SIZE];
};
typedef struct oal_app_ie oal_app_ie_stru;


/*
 * Structure of the IP frame
 */
struct oal_ip_header
{
/*  modifed proxyst begin */
//#if (_PRE_BIG_CPU_ENDIAN == _PRE_CPU_ENDIAN)            /* BIG_ENDIAN */
#if (_PRE_LITTLE_CPU_ENDIAN == _PRE_CPU_ENDIAN)            /* LITTLE_ENDIAN */
    oal_uint8    us_ihl:4,
                 uc_version_ihl:4;
#else
    oal_uint8    uc_version_ihl:4,
                 us_ihl:4;
#endif
/*  modifed proxyst end */

    oal_uint8    uc_tos;
    oal_uint16   us_tot_len;
    oal_uint16   us_id;
    oal_uint16   us_frag_off;
    oal_uint8    uc_ttl;
    oal_uint8    uc_protocol;
    oal_uint16   us_check;
    oal_uint32   ul_saddr;
    oal_uint32   ul_daddr;
    /*The options start here. */
}__OAL_DECLARE_PACKED;
typedef struct oal_ip_header oal_ip_header_stru;

typedef struct
{
    oal_uint16  us_sport;
    oal_uint16  us_dport;
    oal_uint32  ul_seqnum;
    oal_uint32  ul_acknum;
    oal_uint8   uc_offset;
    oal_uint8   uc_flags;
    oal_uint16  us_window;
    oal_uint16  us_check;
    oal_uint16  us_urgent;

}oal_tcp_header_stru;

typedef struct
{
    oal_uint16 source;
    oal_uint16 dest;
    oal_uint16 len;
    oal_uint16 check;
}oal_udp_header_stru;


/* WIN32和linux共用结构体  */
typedef struct
{
    oal_uint8 uc_type;
    oal_uint8 uc_len;
    oal_uint8 uc_addr[6];  /* hardware address */
}oal_eth_icmp6_lladdr_stru;

typedef struct
{
    oal_uint8           op;          /* packet opcode type */
    oal_uint8           htype;       /* hardware addr type */
    oal_uint8           hlen;        /* hardware addr length */
    oal_uint8           hops;        /* gateway hops */
    oal_uint32          xid;         /* transaction ID */
    oal_uint16          secs;        /* seconds since boot began */
    oal_uint16          flags;       /* flags */
    oal_uint32          ciaddr;      /* client IP address */
    oal_uint32          yiaddr;      /* 'your' IP address */
    oal_uint32          siaddr;      /* server IP address */
    oal_uint32          giaddr;      /* gateway IP address */
    oal_uint8           chaddr[16];  /* client hardware address */
    oal_uint8           sname[64];   /* server host name */
    oal_uint8           file[128];   /* boot file name */
    oal_uint8           options[4];  /* variable-length options field */
}oal_dhcp_packet_stru;

/* 不分平台通用结构体 */
typedef struct
{
    oal_uint8   auc_ssid[OAL_IEEE80211_MAX_SSID_LEN];       /* ssid array */
    oal_uint8   uc_ssid_len;                                /* length of the array */
    oal_uint8   auc_arry[3];
}oal_ssids_stru;

/* net_device ioctl结构体定义 */
typedef struct oal_net_dev_ioctl_data_tag
{
    oal_int32 l_cmd;                                  /* 命令号 */
    union
    {
        struct
        {
            oal_uint8    auc_mac[OAL_MAC_ADDR_LEN];
            oal_uint8    auc_rsv[2];
            oal_uint32   ul_buf_size;            /* 用户空间ie 缓冲大小 */
            oal_uint8   *puc_buf;               /* 用户空间ie 缓冲地址 */
        }assoc_req_ie;                          /* AP 模式，用于获取STA 关联请求ie 信息 */

        struct
        {
            oal_uint32    auth_alg;
        }auth_params;

        struct
        {
            oal_uint8    auc_country_code[4];
        }country_code;

		oal_uint8     ssid[OAL_IEEE80211_MAX_SSID_LEN+4];
        oal_uint32    ul_vap_max_user;

        struct
         {
             oal_int32    l_freq;
             oal_int32    l_channel;
             oal_int32    l_ht_enabled;
             oal_int32    l_sec_channel_offset;
             oal_int32    l_vht_enabled;
             oal_int32    l_center_freq1;
             oal_int32    l_center_freq2;
             oal_int32    l_bandwidth;
         }freq;

         oal_app_ie_stru  st_app_ie;          /* beacon ie,index 0; proberesp ie index 1; assocresp ie index 2 */

        struct
        {
            oal_int32                           l_freq;              /* ap所在频段，与linux-2.6.34内核中定义不同 */
            oal_uint32                          ssid_len;            /* SSID 长度 */
            oal_uint32                          ie_len;

            oal_uint8                          *puc_ie;
            OAL_CONST oal_uint8                *puc_ssid;               /* 期望关联的AP SSID  */
            OAL_CONST oal_uint8                *puc_bssid;              /* 期望关联的AP BSSID  */

            oal_uint8                           en_privacy;             /* 是否加密标志 */
            oal_nl80211_auth_type_enum_uint8    en_auth_type;           /* 认证类型，OPEN or SHARE-KEY */

            oal_uint8                           uc_wep_key_len;         /* WEP KEY长度 */
            oal_uint8                           uc_wep_key_index;       /* WEP KEY索引 */
            OAL_CONST oal_uint8                *puc_wep_key;            /* WEP KEY密钥 */

            oal_cfg80211_crypto_settings_stru   st_crypto;              /* 密钥套件信息 */
        }cfg80211_connect_params;
        struct
        {
            oal_uint8            auc_mac[OAL_MAC_ADDR_LEN];
            oal_uint16           us_reason_code;                        /* 去关联 reason code */
        }kick_user_params;

        oal_int32                l_frag;                                /* 分片门限值 */
        oal_int32                l_rts;                                 /* RTS 门限值 */
    }pri_data;
}oal_net_dev_ioctl_data_stru;
//#endif
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_bool_enum_uint8 oal_netbuf_is_dhcp_port(oal_udp_header_stru *pst_udp_hdr);
extern oal_bool_enum_uint8 oal_netbuf_is_nd(oal_ipv6hdr_stru  *pst_ipv6hdr);
extern oal_bool_enum_uint8 oal_netbuf_is_dhcp6(oal_ipv6hdr_stru  *pst_ether_hdr);

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
extern oal_void  oal_netbuf_get_txtid(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tos);
#endif

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
extern oal_bool_enum_uint8 oal_netbuf_is_tcp_ack6(oal_ipv6hdr_stru  *pst_ipv6hdr);
extern oal_uint16 oal_netbuf_select_queue(oal_netbuf_stru *pst_buf);
#endif
extern oal_bool_enum_uint8 oal_netbuf_is_tcp_ack(oal_ip_header_stru  *pst_ip_hdr);
extern oal_bool_enum_uint8 oal_netbuf_is_icmp(oal_ip_header_stru  *pst_ip_hdr);

//extern oal_int genKernel_init(oal_void);
//extern oal_void genKernel_exit(oal_void);
extern oal_int32 dev_netlink_send (oal_uint8 *data, oal_int data_len);
extern oal_int32 init_dev_excp_handler(oal_void);
extern oal_void deinit_dev_excp_handler(oal_void);
extern oal_int genl_msg_send_to_user(oal_void *data, oal_int i_len);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_net.h */
