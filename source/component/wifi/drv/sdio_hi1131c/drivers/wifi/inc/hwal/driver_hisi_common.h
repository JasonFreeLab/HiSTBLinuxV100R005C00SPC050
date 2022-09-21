/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : driver_hisi_common.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月16日
  最近修改   :
  功能描述   : driver与wpa_supplicant共用头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DRIVER_HISI_COMMON_H__
#define __DRIVER_HISI_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "stdio.h"

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef WIN32
#include "los_typedef.h"
#endif /* WIN32 */
/*****************************************************************************
  2 基本数据类型定义
*****************************************************************************/
#if ((_PRE_TEST_MODE_UT == _PRE_TEST_MODE) || (_PRE_TEST_MODE_ST == _PRE_TEST_MODE) || defined(_PRE_WIFI_DMT))
typedef char                    oal_int8;           /* 数据前缀:c */
#else
typedef signed char             oal_int8;           /* 数据前缀:c */
#endif

typedef signed short            oal_int16;          /* 数据前缀:s */
typedef signed int              oal_int32;          /* 数据前缀:l */
typedef signed long long        oal_int64;          /* 数据前缀:ll */
typedef unsigned char           oal_uint8;          /* 数据前缀:uc */
typedef unsigned short          oal_uint16;         /* 数据前缀:us */
typedef unsigned int            oal_uint32;         /* 数据前缀:ul */
typedef unsigned long long      oal_uint64;         /* 数据前缀:ull */
typedef void                    oal_void;
typedef unsigned long           oal_ulong;
#ifdef WIN32
typedef unsigned int            oal_size_t;
#else
typedef size_t                  oal_size_t;
#endif /* WIN32 */
/*****************************************************************************
  3 宏定义
*****************************************************************************/
#if ((_PRE_TEST_MODE_UT == _PRE_TEST_MODE) || (_PRE_TEST_MODE_ST == _PRE_TEST_MODE) || defined(_PRE_WIFI_DMT))

#ifdef INLINE_TO_FORCEINLINE
#define OAL_INLINE      __forceinline
#else
#define OAL_INLINE      __inline
#endif

#else
#ifdef INLINE_TO_FORCEINLINE
#define OAL_INLINE      __forceinline
#else
#define OAL_INLINE          inline
#endif
#define OAL_CONST           const
#endif


#if ((_PRE_TEST_MODE_UT == _PRE_TEST_MODE) || (_PRE_TEST_MODE_ST == _PRE_TEST_MODE) || defined(_PRE_WIFI_DMT))
#define OAL_STATIC
#else
#define OAL_STATIC          static
#endif

#define HISI_SUCC            0
#define HISI_EFAIL           1
#define HISI_EINVAL         22

#ifndef ETH_ADDR_LEN
#define ETH_ADDR_LEN        6
#endif

#define EAPOL_PKT_BUF_SIZE  800

#ifndef MAX_FREQS_NUM
#define MAX_FREQS_NUM        8
#endif

#ifndef MAX_SSID_LEN
#define MAX_SSID_LEN        32
#endif

#ifndef MAX_IE_LEN
#define MAX_IE_LEN          32
#endif

#ifndef HISI_MAX_NR_CIPHER_SUITES
#define HISI_MAX_NR_CIPHER_SUITES    5
#endif

#ifndef HISI_MAX_NR_AKM_SUITES
#define HISI_MAX_NR_AKM_SUITES       2
#endif

#ifndef HISI_WPAS_MAX_SCAN_SSIDS
#define HISI_WPAS_MAX_SCAN_SSIDS     16
#endif

#ifndef    HISI_PTR_NULL
#define    HISI_PTR_NULL  NULL
#endif

#ifndef    SCAN_AP_LIMIT
#define    SCAN_AP_LIMIT 64
#endif

#ifndef    HISI_PRINT
#ifdef     WIN32
#define    HISI_PRINT  printf
#else
#define    HISI_PRINT  oam_printf
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
#define HISI_REKEY_OFFLOAD_KCK_LEN              16
#define HISI_REKEY_OFFLOAD_KEK_LEN              16
#define HISI_REKEY_OFFLOAD_REPLAY_COUNTER_LEN   8
#endif
/*****************************************************************************
  4 枚举定义
*****************************************************************************/
typedef enum
{
    HISI_FALSE   = 0,
    HISI_TRUE    = 1,

    HISI_BUTT
}hisi_bool_enum;
typedef oal_uint8 hisi_bool_enum_uint8;

typedef enum
{
	HISI_IFTYPE_UNSPECIFIED,
	HISI_IFTYPE_ADHOC,
	HISI_IFTYPE_STATION,
	HISI_IFTYPE_AP,
	HISI_IFTYPE_AP_VLAN,
	HISI_IFTYPE_WDS,
	HISI_IFTYPE_MONITOR,
	HISI_IFTYPE_MESH_POINT,
	HISI_IFTYPE_P2P_CLIENT,
	HISI_IFTYPE_P2P_GO,
	HISI_IFTYPE_P2P_DEVICE,

	/* keep last */
	NUM_HISI_IFTYPES,
	HISI_IFTYPE_MAX = NUM_HISI_IFTYPES - 1
}hisi_iftype_enum;
typedef oal_uint8 hisi_iftype_enum_uint8;

typedef enum
{
    NO_SCAN, SCAN_REQUESTED, SCAN_STARTED, SCAN_COMPLETED,
    SCAN_ABORTED, SCHED_SCAN_STARTED, SCHED_SCAN_STOPPED,
    SCHED_SCAN_RESULTS
} hisi_scan_state_enum;
typedef oal_uint8 hisi_scan_state_enum_uint8;

typedef enum
{
    HISI_KEYTYPE_GROUP,
    HISI_KEYTYPE_PAIRWISE,
    HISI_KEYTYPE_PEERKEY,

    NUM_HISI_KEYTYPES
}hisi_key_type_enum;
typedef oal_uint8 hisi_key_type_enum_uint8;

typedef enum
{
    __HISI_KEY_DEFAULT_TYPE_INVALID,
    HISI_KEY_DEFAULT_TYPE_UNICAST,
    HISI_KEY_DEFAULT_TYPE_MULTICAST,

    NUM_HISI_KEY_DEFAULT_TYPES
}hisi_key_default_types_enum;
typedef oal_uint8 hisi_key_default_types_enum_uint8;

typedef enum
{
	HISI_NO_SSID_HIDING,
	HISI_HIDDEN_SSID_ZERO_LEN,
	HISI_HIDDEN_SSID_ZERO_CONTENTS
}hisi_hidden_ssid_enum;
typedef oal_uint8 hisi_hidden_ssid_enum_uint8;

typedef enum
{
    HISI_IOCTL_SET_AP = 0,
    HISI_IOCTL_NEW_KEY,
    HISI_IOCTL_DEL_KEY,
    HISI_IOCTL_SET_KEY,
    HISI_IOCTL_SEND_MLME,
    HISI_IOCTL_SEND_EAPOL,
    HISI_IOCTL_RECEIVE_EAPOL,
    HISI_IOCTL_ENALBE_EAPOL,
    HISI_IOCTL_DISABLE_EAPOL,
    HIIS_IOCTL_GET_ADDR,
    HISI_IOCTL_SET_POWER,
    HISI_IOCTL_SET_MODE,
    HIIS_IOCTL_GET_HW_FEATURE,
    HISI_IOCTL_STOP_AP,
    HISI_IOCTL_DEL_VIRTUAL_INTF,
    HISI_IOCTL_SCAN,
    HISI_IOCTL_DISCONNET,
    HISI_IOCTL_ASSOC,
    HISI_IOCTL_SET_NETDEV,
    HISI_IOCTL_SET_AP_WPS_P2P_IE,
    HISI_IOCTL_CHANGE_BEACON,
    HISI_IOCTL_DHCP_START,
    HISI_IOCTL_DHCP_STOP,
    HISI_IOCTL_DHCP_SUCC_CHECK,
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    HISI_IOCTL_SET_REKEY_INFO,
#endif
    HWAL_EVENT_BUTT
}hisi_event_enum;
typedef oal_uint8 hisi_event_enum_uint8;

typedef enum
{
    HISI_IOCTL_SET_CHANNEL,
#ifdef _PRE_WLAN_FEATURE_HILINK
    HISI_IOCTL_SET_MONITOR,
#endif
    HISI_IOCTL_SET_CHANNEL_40M,
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
    HISI_IOCTL_GET_TCP_PARAMS,
    HISI_IOCTL_SET_TCP_PARAMS,
#endif
    HISI_IOCTL_BUTT
}hisi_app_ioctl_enum;
typedef oal_uint8 hisi_app_ioctl_enum_uint8;

typedef enum
{
    HISI_ELOOP_EVENT_NEW_STA = 0,
    HISI_ELOOP_EVENT_DEL_STA,
    HISI_ELOOP_EVENT_RX_MGMT,
    HISI_ELOOP_EVENT_TX_STATUS,
    HISI_ELOOP_EVENT_SCAN_DONE,
    HISI_ELOOP_EVENT_SCAN_RESULT,
    HISI_ELOOP_EVENT_CONNECT_RESULT,
    HISI_ELOOP_EVENT_DISCONNECT,
    HISI_ELOOP_EVENT_DHCP_SUCC,

    HISI_ELOOP_EVENT_BUTT
}hisi_eloop_event_enum;
typedef oal_uint8 hisi_eloop_event_enum_uint8;

typedef enum
{
	HISI_CHAN_WIDTH_20_NOHT,
	HISI_CHAN_WIDTH_20,
	HISI_CHAN_WIDTH_40,

	HISI_CHAN_WIDTH_BUTT
}hisi_chan_width_enum;
typedef oal_uint8 hisi_chan_width_enum_uint8;

typedef enum
{
	HISI_SCAN_FLAG_LOW_PRIORITY			= 1<<0,
	HISI_SCAN_FLAG_FLUSH				= 1<<1,
	HISI_SCAN_FLAG_AP				    = 1<<2,
}hisi_scan_flags_enum;
typedef oal_uint8 hisi_scan_flags_enum_uint8;

typedef enum
{
	HISI_MFP_NO,
	HISI_MFP_REQUIRED,
}hisi_mfp_enum;
typedef oal_uint8 hisi_mfp_enum_uint8;

typedef enum
{
	HISI_WPA_VERSION_1 = 1 << 0,
	HISI_WPA_VERSION_2 = 1 << 1,
}hisi_wpa_versions_enum;
typedef oal_uint8 hisi_wpa_versions_enum_uint8;

typedef enum
{
    HISI_AUTHTYPE_OPEN_SYSTEM = 0,
    HISI_AUTHTYPE_SHARED_KEY,
    HISI_AUTHTYPE_FT,
    HISI_AUTHTYPE_NETWORK_EAP,
    HISI_AUTHTYPE_SAE,

    /* keep last */
    __HISI_AUTHTYPE_NUM,
    HISI_AUTHTYPE_MAX = __HISI_AUTHTYPE_NUM - 1,
    HISI_AUTHTYPE_AUTOMATIC,

    HISI_AUTHTYPE_BUTT
}hisi_auth_type_enum;
typedef oal_uint8 hisi_auth_type_enum_uint8;

typedef enum
{
	HISI_CHAN_DISABLED		= 1<<0,
	HISI_CHAN_PASSIVE_SCAN	= 1<<1,
	HISI_CHAN_NO_IBSS		= 1<<2,
	HISI_CHAN_RADAR		    = 1<<3,
	HISI_CHAN_NO_HT40PLUS	= 1<<4,
	HISI_CHAN_NO_HT40MINUS	= 1<<5,
	HISI_CHAN_NO_OFDM		= 1<<6,
	HISI_CHAN_NO_80MHZ		= 1<<7,
	HISI_CHAN_NO_160MHZ	    = 1<<8,
}hisi_channel_flags_enum;
typedef oal_uint8 hisi_channel_flags_enum_uint8;


typedef enum
{
	HISI_DISCONNECT		,
	HISI_CONNECT	    ,
}hisi_connect_status_enum;
typedef oal_uint8 hisi_connect_status_enum_uint8;

typedef enum
{
    HISI_BAND_WIDTH_40PLUS                 = 0,
    HISI_BAND_WIDTH_40MINUS                = 1,

    HISI_BAND_WIDTH_BUTT
}hilink_channel_bandwidth_enum;
typedef oal_uint8 hilink_channel_bandwidth_enum_uint8;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 消息头定义
*****************************************************************************/

/*****************************************************************************
  7 消息定义
*****************************************************************************/


/*****************************************************************************
  8 STRUCT定义
*****************************************************************************/

typedef struct _hisi_new_sta_info_stru
{
	oal_int32  l_reassoc;
	oal_size_t ul_ielen;
    oal_uint8 *puc_ie;
    oal_uint8  auc_macaddr[ETH_ADDR_LEN];
}hisi_new_sta_info_stru;

typedef struct _hisi_rx_mgmt_stru
{
    oal_uint8 *puc_buf;
    oal_uint32 ul_len;
    oal_int32  l_sig_mbm;
}hisi_rx_mgmt_stru;

typedef struct _hisi_tx_status_stru
{
    oal_uint8          *puc_buf;
    oal_uint32          ul_len;
    hisi_bool_enum_uint8 en_ack;
}hisi_tx_status_stru;

typedef struct _hisi_ethmac_header_stru
{
   oal_uint8   auc_mac_ra[ETH_ADDR_LEN];
   oal_uint8   auc_mac_ta[ETH_ADDR_LEN];
   oal_uint8   auc_mac_protocol[2];
}hisi_ethmac_header_stru;

typedef struct _hisi_mlme_data_stru
{
    oal_int32       l_noack;
    oal_uint32      ul_freq;
    oal_size_t      ul_data_len;
    oal_uint8      *puc_data;
    oal_uint64     *pull_send_action_cookie;
}hisi_mlme_data_stru;

typedef struct _hisi_beacon_data_stru
{
    oal_size_t      ul_head_len;
    oal_size_t      ul_tail_len;
    oal_uint8      *puc_head;
    oal_uint8      *puc_tail;
}hisi_beacon_data_stru;

typedef struct _hisi_freq_params_stru
{
    oal_int32 l_mode;
    oal_int32 l_freq;
    oal_int32 l_channel;

    /* for HT */
    oal_int32 l_ht_enabled;

    /* 0 = HT40 disabled, -1 = HT40 enabled,
     * secondary channel below primary, 1 = HT40
     * enabled, secondary channel above primary */
    oal_int32 l_sec_channel_offset;

    /* for VHT */
    oal_int32 l_vht_enabled;

    /* valid for both HT and VHT, center_freq2 is non-zero
     * only for bandwidth 80 and an 80+80 channel */
    oal_int32 l_center_freq1;
    oal_int32 l_center_freq2;
    oal_int32 l_bandwidth;
}hisi_freq_params_stru;

/* 密钥信息设置数据传递结构体*/
typedef struct _hisi_key_ext_stru
{
    oal_int32                           l_type;
    oal_uint32                          ul_key_idx;
    oal_uint32                          ul_key_len;
    oal_uint32                          ul_seq_len;
    oal_uint32                          ul_set_tx;
    oal_uint32                          ul_cipher;
    oal_uint8                          *puc_addr;
    oal_uint8                          *puc_key;
    oal_uint8                          *puc_seq;
    hisi_bool_enum_uint8                en_def;
    hisi_bool_enum_uint8                en_defmgmt;
    hisi_iftype_enum_uint8              en_nlmode;
    hisi_key_default_types_enum_uint8   en_default_types;
}hisi_key_ext_stru;

/* AP信息设置相关数据传递结构体*/
typedef struct _hisi_ap_settings_stru
{
    hisi_freq_params_stru        st_freq_params;
    hisi_beacon_data_stru        st_beacon_data;
    oal_size_t                   ul_ssid_len;
    oal_int32                    l_beacon_interval;
    oal_int32                    l_dtim_period;
    oal_uint8                   *puc_ssid;
    hisi_hidden_ssid_enum_uint8  en_hidden_ssid;
    hisi_auth_type_enum_uint8    en_auth_type;
}hisi_ap_settings_stru;

/* 设置模式结构体 */
typedef struct _hisi_set_mode_stru
{
    oal_uint8                   auc_bssid[ETH_ADDR_LEN];
    hisi_iftype_enum_uint8      en_iftype;
}hisi_set_mode_stru;

typedef struct _hisi_tx_eapol_stru
{
    oal_uint8           auc_src[ETH_ADDR_LEN];
    oal_uint8           auc_dst[ETH_ADDR_LEN];
    oal_uint8          *puc_buf;
    oal_uint32          ul_len;
}hisi_tx_eapol_stru;

typedef struct _hisi_rx_eapol_stru
{
    oal_uint8          *puc_buf;
    oal_uint32          ul_len;
}hisi_rx_eapol_stru;

typedef struct _hisi_enable_eapol_stru
{
    oal_void           *pfn_callback;
    oal_void           *p_contex;
}hisi_enable_eapol_stru;

typedef struct _hisi_ioctl_command_stru
{
    oal_uint32      ul_cmd;
    oal_void       *p_buf;
}hisi_ioctl_command_stru;

typedef struct _hisi_ieee80211_channel_stru
{
    oal_uint16  us_channel;
    oal_uint32  ul_freq;
    oal_uint32  ul_flags;
}hisi_ieee80211_channel_stru;

typedef struct _hisi_hw_feature_data_stru
{
    oal_int32                   l_channel_num;
    oal_uint16                  aus_bitrate[12];
    oal_uint16                  us_ht_capab;
    hisi_ieee80211_channel_stru ast_iee80211_channel[14];
}hisi_hw_feature_data_stru;

typedef struct hisi_driver_scan_ssid_stru
{
    oal_uint8                     auc_ssid[MAX_SSID_LEN];
    oal_size_t                    ul_ssid_len;
} hisi_driver_scan_ssid_stru;

typedef struct _hisi_scan_stru
{
	hisi_driver_scan_ssid_stru    ast_ssids[HISI_WPAS_MAX_SCAN_SSIDS];
	oal_int32                    *pl_freqs;
	oal_uint8                    *puc_extra_ies;
	oal_size_t                    ul_num_ssids;
	oal_size_t                    ul_num_freqs;
	oal_size_t                    ul_extra_ies_len;
}hisi_scan_stru;

typedef	struct _hisi_scan_filter_stru
{
	oal_uint8                    auc_ssid[MAX_SSID_LEN];
	oal_size_t                   ul_ssid_len;
} hisi_scan_filter_stru;

typedef	struct _hisi_bss_info_stru
{
	oal_uint32                   ul_flags;
	oal_uint8                    auc_bssid[ETH_ADDR_LEN];
	oal_int32                    l_freq;
	oal_uint16                   us_beacon_int;
	oal_uint16                   us_caps;
	oal_int32                    ul_qual;
	oal_int32                    ul_noise;
	oal_int32                    ul_level;
	oal_uint64                   ull_tsf;
	oal_uint32                   ul_age;
	oal_size_t                   ul_ie_len;
	oal_size_t                   ul_beacon_ie_len;

} hisi_bss_info_stru;
typedef struct  _hisi_crypto_settings_stru
{
    oal_uint32              ul_wpa_versions;
    oal_uint32              ul_cipher_group;
    oal_int32               l_n_ciphers_pairwise;
    oal_uint32              aul_ciphers_pairwise[HISI_MAX_NR_CIPHER_SUITES];
    oal_int32               l_n_akm_suites;
    oal_uint32              aul_akm_suites[HISI_MAX_NR_AKM_SUITES];
}hisi_crypto_settings_stru;


typedef	struct _hisi_associate_params_stru
{
    oal_uint8                          *puc_bssid;
    oal_uint8                          *puc_ssid;
    oal_uint8                          *puc_ie;
    oal_uint8                          *puc_key;
    oal_uint8                           uc_auth_type;
    oal_uint8                           uc_privacy;
    oal_uint8                           uc_key_len;
    oal_uint8                           uc_key_idx;
    oal_uint8                           uc_mfp;
    oal_uint32                          ul_freq;
    oal_uint32                          ul_ssid_len;
    oal_uint32                          ul_ie_len;
    hisi_crypto_settings_stru           st_crypto;
} hisi_associate_params_stru;


typedef	struct _hisi_connect_result_stru
{
    oal_uint8              *puc_req_ie;
    oal_size_t              ul_req_ie_len;
    oal_uint8              *puc_resp_ie;
    oal_size_t              ul_resp_ie_len;
    oal_uint8               auc_bssid[ETH_ADDR_LEN];
    oal_uint16              us_status;
    oal_uint8               auc_rsv[2];

} hisi_connect_result_stru;

typedef	struct _hisi_scan_result_stru
{
	oal_int32               l_flags;
	oal_uint8               auc_bssid[ETH_ADDR_LEN];
	oal_uint8               auc_rsv[2];
	oal_int32               l_freq;
	oal_int16               s_beacon_int;
	oal_int16               s_caps;
	oal_int32               l_qual;
	oal_int32               l_noise;
	oal_int32               l_level;
	oal_uint64              ull_tsf;
	oal_uint32              ul_age;
	oal_uint32              ul_ie_len;
	oal_uint32              ul_beacon_ie_len;
	oal_uint8              *puc_variable;

} hisi_scan_result_stru;

typedef struct _hisi_wpa_status_stru
{
    oal_uint8                  auc_ssid[MAX_SSID_LEN];
    oal_uint8                  auc_bssid[ETH_ADDR_LEN];
    oal_uint8                  auc_rsv[2];
    oal_uint32                 ul_status;

} hisi_wpa_status_stru;

typedef	struct _hisi_disconnect_stru
{
    oal_uint8                  *puc_ie;
    oal_uint16                  us_reason;
    oal_uint8                   auc_rsv[2];
    oal_uint32                  ul_ie_len;
} hisi_disconnect_stru;

typedef struct _hisi_app_ie_stru
{
    oal_uint32              ul_ie_len;
    oal_uint8               uc_app_ie_type;
    oal_uint8               auc_rsv[3];
    /* auc_ie 中保存信息元素 */
    oal_uint8              *puc_ie;
}hisi_app_ie_stru;
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
typedef struct _hisi_tcp_params_stru
{
    oal_uint32      ul_sess_id;
    oal_uint8       uc_dst_mac[6];  /* 目的MAC地址 */
    oal_uint8       auc_resv[2];
    oal_uint8       uc_src_ip[4];   /* 源IP地址 */
    oal_uint8       uc_dst_ip[4];   /* 目的IP地址 */
    oal_uint16      us_src_port;    /* 源端口号 */
    oal_uint16      us_dst_port;    /* 目的端口号 */
    oal_uint32      ul_seq_num;     /* 序列号 */
    oal_uint32      ul_ack_num;     /* 确认号 */
    oal_uint16      us_window;      /* TCP窗口大小 */
    oal_uint16      us_interval_timer;       /* 心跳包发送周期 */
    oal_uint16      us_retry_interval_timer; /* 重传时心跳包发送周期 */
    oal_uint16      us_retry_max_count;      /* 最大重传次数 */
    oal_uint32      ul_time_value;
    oal_uint32      ul_time_echo;
    oal_uint8      *puc_tcp_payload;
    oal_uint32      ul_payload_len;
}hisi_tcp_params_stru;
#endif
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
typedef struct _hisi_rekey_offload_stru
{
    oal_uint8   auc_kck[HISI_REKEY_OFFLOAD_KCK_LEN];
    oal_uint8   auc_kek[HISI_REKEY_OFFLOAD_KEK_LEN];
    oal_uint8   auc_replay_ctr[HISI_REKEY_OFFLOAD_REPLAY_COUNTER_LEN];
}hisi_rekey_offload_stru;
#endif

typedef oal_uint8 hisi_connect_status_enum_uint8;
typedef struct
{
    oal_uint8                               uc_channel_num;
    hilink_channel_bandwidth_enum_uint8     uc_channel_bandwidth;
}hilink_channel_stru;

/*****************************************************************************
  9 UNION定义
*****************************************************************************/

/*****************************************************************************
  10 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  11 函数声明
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of driver_hisi_common.h */
