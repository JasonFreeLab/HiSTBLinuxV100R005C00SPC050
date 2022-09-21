/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_cfg80211.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2014年5月9日
  最近修改   :
  功能描述   : oal_cfg80211.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月9日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_CFG80211_H__
#define __OAL_CFG80211_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"

#include "arch/oal_cfg80211.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define    KEY_DEL_MAXNUM            6
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 用于hostapd和supplicant事件上报的属性填写，和hostapd和supplicant侧对应起来，30内核属性很少 */
enum PRIV_NL80211_ATTRs {
/* don't change the order or add anything inbetween, this is ABI! */
    PRIV_NL80211_ATTR_UNSPEC,

    PRIV_NL80211_ATTR_WIPHY,
    PRIV_NL80211_ATTR_WIPHY_NAME,

    PRIV_NL80211_ATTR_IFINDEX,
    PRIV_NL80211_ATTR_IFNAME,
    PRIV_NL80211_ATTR_IFTYPE,

    PRIV_NL80211_ATTR_MAC,

    PRIV_NL80211_ATTR_KEY_DATA,
    PRIV_NL80211_ATTR_KEY_IDX,
    PRIV_NL80211_ATTR_KEY_CIPHER,
    PRIV_NL80211_ATTR_KEY_SEQ,
    PRIV_NL80211_ATTR_KEY_DEFAULT,

    PRIV_NL80211_ATTR_BEACON_INTERVAL,
    PRIV_NL80211_ATTR_DTIM_PERIOD,
    PRIV_NL80211_ATTR_BEACON_HEAD,
    PRIV_NL80211_ATTR_BEACON_TAIL,

    PRIV_NL80211_ATTR_STA_AID,
    PRIV_NL80211_ATTR_STA_FLAGS,
    PRIV_NL80211_ATTR_STA_LISTEN_INTERVAL,
    PRIV_NL80211_ATTR_STA_SUPPORTED_RATES,
    PRIV_NL80211_ATTR_STA_VLAN,
    PRIV_NL80211_ATTR_STA_INFO,

    PRIV_NL80211_ATTR_WIPHY_BANDS,

    PRIV_NL80211_ATTR_MNTR_FLAGS,

    PRIV_NL80211_ATTR_MESH_ID,
    PRIV_NL80211_ATTR_STA_PLINK_ACTION,
    PRIV_NL80211_ATTR_MPATH_NEXT_HOP,
    PRIV_NL80211_ATTR_MPATH_INFO,

    PRIV_NL80211_ATTR_BSS_CTS_PROT,
    PRIV_NL80211_ATTR_BSS_SHORT_PREAMBLE,
    PRIV_NL80211_ATTR_BSS_SHORT_SLOT_TIME,

    PRIV_NL80211_ATTR_HT_CAPABILITY,

    PRIV_NL80211_ATTR_SUPPORTED_IFTYPES,

    PRIV_NL80211_ATTR_REG_ALPHA2,
    PRIV_NL80211_ATTR_REG_RULES,

    PRIV_NL80211_ATTR_MESH_PARAMS,

    PRIV_NL80211_ATTR_BSS_BASIC_RATES,

    PRIV_NL80211_ATTR_WIPHY_TXQ_PARAMS,
    PRIV_NL80211_ATTR_WIPHY_FREQ,
    PRIV_NL80211_ATTR_WIPHY_CHANNEL_TYPE,

    PRIV_NL80211_ATTR_KEY_DEFAULT_MGMT,

    PRIV_NL80211_ATTR_MGMT_SUBTYPE,
    PRIV_NL80211_ATTR_IE,

    PRIV_NL80211_ATTR_MAX_NUM_SCAN_SSIDS,

    PRIV_NL80211_ATTR_SCAN_FREQUENCIES,
    PRIV_NL80211_ATTR_SCAN_SSIDS,
    PRIV_NL80211_ATTR_GENERATION, /* replaces old SCAN_GENERATION */
    PRIV_NL80211_ATTR_BSS,

    PRIV_NL80211_ATTR_REG_INITIATOR,
    PRIV_NL80211_ATTR_REG_TYPE,

    PRIV_NL80211_ATTR_SUPPORTED_COMMANDS,

    PRIV_NL80211_ATTR_FRAME,
    PRIV_NL80211_ATTR_SSID,
    PRIV_NL80211_ATTR_AUTH_TYPE,
    PRIV_NL80211_ATTR_REASON_CODE,

    PRIV_NL80211_ATTR_KEY_TYPE,

    PRIV_NL80211_ATTR_MAX_SCAN_IE_LEN,
    PRIV_NL80211_ATTR_CIPHER_SUITES,

    PRIV_NL80211_ATTR_FREQ_BEFORE,
    PRIV_NL80211_ATTR_FREQ_AFTER,

    PRIV_NL80211_ATTR_FREQ_FIXED,


    PRIV_NL80211_ATTR_WIPHY_RETRY_SHORT,
    PRIV_NL80211_ATTR_WIPHY_RETRY_LONG,
    PRIV_NL80211_ATTR_WIPHY_FRAG_THRESHOLD,
    PRIV_NL80211_ATTR_WIPHY_RTS_THRESHOLD,

    PRIV_NL80211_ATTR_TIMED_OUT,

    PRIV_NL80211_ATTR_USE_MFP,

    PRIV_NL80211_ATTR_STA_FLAGS2,

    PRIV_NL80211_ATTR_CONTROL_PORT,

    PRIV_NL80211_ATTR_TESTDATA,

    PRIV_NL80211_ATTR_PRIVACY,

    PRIV_NL80211_ATTR_DISCONNECTED_BY_AP,
    PRIV_NL80211_ATTR_STATUS_CODE,

    PRIV_NL80211_ATTR_CIPHER_SUITES_PAIRWISE,
    PRIV_NL80211_ATTR_CIPHER_SUITE_GROUP,
    PRIV_NL80211_ATTR_WPA_VERSIONS,
    PRIV_NL80211_ATTR_AKM_SUITES,

    PRIV_NL80211_ATTR_REQ_IE,
    PRIV_NL80211_ATTR_RESP_IE,

    PRIV_NL80211_ATTR_PREV_BSSID,

    PRIV_NL80211_ATTR_KEY,
    PRIV_NL80211_ATTR_KEYS,

    PRIV_NL80211_ATTR_PID,

    PRIV_NL80211_ATTR_4ADDR,

    PRIV_NL80211_ATTR_SURVEY_INFO,

    PRIV_NL80211_ATTR_PMKID,
    PRIV_NL80211_ATTR_MAX_NUM_PMKIDS,

    PRIV_NL80211_ATTR_DURATION,

    PRIV_NL80211_ATTR_COOKIE,

    PRIV_NL80211_ATTR_WIPHY_COVERAGE_CLASS,

    PRIV_NL80211_ATTR_TX_RATES,

    PRIV_NL80211_ATTR_FRAME_MATCH,

    PRIV_NL80211_ATTR_ACK,

    PRIV_NL80211_ATTR_PS_STATE,

    /* add attributes here, update the policy in nl80211.c */

    __PRIV_NL80211_ATTR_AFTER_LAST,
    PRIV_NL80211_ATTR_MAX = __PRIV_NL80211_ATTR_AFTER_LAST - 1
};

enum PRIV_NL80211_STA_info {
	__PRIV_NL80211_STA_INFO_INVALID,
	PRIV_NL80211_STA_INFO_INACTIVE_TIME,
	PRIV_NL80211_STA_INFO_RX_BYTES,
	PRIV_NL80211_STA_INFO_TX_BYTES,
	PRIV_NL80211_STA_INFO_LLID,
	PRIV_NL80211_STA_INFO_PLID,
	PRIV_NL80211_STA_INFO_PLINK_STATE,
	PRIV_NL80211_STA_INFO_SIGNAL,
	PRIV_NL80211_STA_INFO_TX_BITRATE,
	PRIV_NL80211_STA_INFO_RX_PACKETS,
	PRIV_NL80211_STA_INFO_TX_PACKETS,
	PRIV_NL80211_STA_INFO_TX_RETRIES,
	PRIV_NL80211_STA_INFO_TX_FAILED,
	PRIV_NL80211_STA_INFO_SIGNAL_AVG,
	PRIV_NL80211_STA_INFO_RX_BITRATE,
	PRIV_NL80211_STA_INFO_BSS_PARAM,
	PRIV_NL80211_STA_INFO_CONNECTED_TIME,
	PRIV_NL80211_STA_INFO_STA_FLAGS,
	PRIV_NL80211_STA_INFO_BEACON_LOSS,
	PRIV_NL80211_STA_INFO_T_OFFSET,

	/* keep last */
	__PRIV_NL80211_STA_INFO_AFTER_LAST,
	PRIV_NL80211_STA_INFO_MAX = __PRIV_NL80211_STA_INFO_AFTER_LAST - 1
};

enum priv_nl80211_commands {
/* don't change the order or add anything between, this is ABI! */
	PRIV_NL80211_CMD_UNSPEC,

	PRIV_NL80211_CMD_GET_WIPHY,		/* can dump */
	PRIV_NL80211_CMD_SET_WIPHY,
	PRIV_NL80211_CMD_NEW_WIPHY,
	PRIV_NL80211_CMD_DEL_WIPHY,

	PRIV_NL80211_CMD_GET_INTERFACE,	/* can dump */
	PRIV_NL80211_CMD_SET_INTERFACE,
	PRIV_NL80211_CMD_NEW_INTERFACE,
	PRIV_NL80211_CMD_DEL_INTERFACE,

	PRIV_NL80211_CMD_GET_KEY,
	PRIV_NL80211_CMD_SET_KEY,
	PRIV_NL80211_CMD_NEW_KEY,
	PRIV_NL80211_CMD_DEL_KEY,

	PRIV_NL80211_CMD_GET_BEACON,
	PRIV_NL80211_CMD_SET_BEACON,
	PRIV_NL80211_CMD_START_AP,
	PRIV_NL80211_CMD_NEW_BEACON = PRIV_NL80211_CMD_START_AP,
	PRIV_NL80211_CMD_STOP_AP,
	PRIV_NL80211_CMD_DEL_BEACON = PRIV_NL80211_CMD_STOP_AP,

	PRIV_NL80211_CMD_GET_STATION,
	PRIV_NL80211_CMD_SET_STATION,
	PRIV_NL80211_CMD_NEW_STATION,
	PRIV_NL80211_CMD_DEL_STATION,

	PRIV_NL80211_CMD_GET_MPATH,
	PRIV_NL80211_CMD_SET_MPATH,
	PRIV_NL80211_CMD_NEW_MPATH,
	PRIV_NL80211_CMD_DEL_MPATH,

	PRIV_NL80211_CMD_SET_BSS,

	PRIV_NL80211_CMD_SET_REG,
	PRIV_NL80211_CMD_REQ_SET_REG,

	PRIV_NL80211_CMD_GET_MESH_CONFIG,
	PRIV_NL80211_CMD_SET_MESH_CONFIG,

	PRIV_NL80211_CMD_SET_MGMT_EXTRA_IE /* reserved; not used */,

	PRIV_NL80211_CMD_GET_REG,

	PRIV_NL80211_CMD_GET_SCAN,
	PRIV_NL80211_CMD_TRIGGER_SCAN,
	PRIV_NL80211_CMD_NEW_SCAN_RESULTS,
	PRIV_NL80211_CMD_SCAN_ABORTED,

	PRIV_NL80211_CMD_REG_CHANGE,

	PRIV_NL80211_CMD_AUTHENTICATE,
	PRIV_NL80211_CMD_ASSOCIATE,
	PRIV_NL80211_CMD_DEAUTHENTICATE,
	PRIV_NL80211_CMD_DISASSOCIATE,

	PRIV_NL80211_CMD_MICHAEL_MIC_FAILURE,

	PRIV_NL80211_CMD_REG_BEACON_HINT,

	PRIV_NL80211_CMD_JOIN_IBSS,
	PRIV_NL80211_CMD_LEAVE_IBSS,

	PRIV_NL80211_CMD_TESTMODE,

	PRIV_NL80211_CMD_CONNECT,
	PRIV_NL80211_CMD_ROAM,
	PRIV_NL80211_CMD_DISCONNECT,

	PRIV_NL80211_CMD_SET_WIPHY_NETNS,

	PRIV_NL80211_CMD_GET_SURVEY,
	PRIV_NL80211_CMD_NEW_SURVEY_RESULTS,

	PRIV_NL80211_CMD_SET_PMKSA,
	PRIV_NL80211_CMD_DEL_PMKSA,
	PRIV_NL80211_CMD_FLUSH_PMKSA,

	PRIV_NL80211_CMD_REMAIN_ON_CHANNEL,
	PRIV_NL80211_CMD_CANCEL_REMAIN_ON_CHANNEL,

	PRIV_NL80211_CMD_SET_TX_BITRATE_MASK,

	PRIV_NL80211_CMD_REGISTER_FRAME,
	PRIV_NL80211_CMD_REGISTER_ACTION = PRIV_NL80211_CMD_REGISTER_FRAME,
	PRIV_NL80211_CMD_FRAME,
	PRIV_NL80211_CMD_ACTION = PRIV_NL80211_CMD_FRAME,
	PRIV_NL80211_CMD_FRAME_TX_STATUS,
	PRIV_NL80211_CMD_ACTION_TX_STATUS = PRIV_NL80211_CMD_FRAME_TX_STATUS,

	PRIV_NL80211_CMD_SET_POWER_SAVE,
	PRIV_NL80211_CMD_GET_POWER_SAVE,

	PRIV_NL80211_CMD_SET_CQM,
	PRIV_NL80211_CMD_NOTIFY_CQM,

	PRIV_NL80211_CMD_SET_CHANNEL,
	PRIV_NL80211_CMD_SET_WDS_PEER,

	PRIV_NL80211_CMD_FRAME_WAIT_CANCEL,

	PRIV_NL80211_CMD_JOIN_MESH,
	PRIV_NL80211_CMD_LEAVE_MESH,

	PRIV_NL80211_CMD_UNPROT_DEAUTHENTICATE,
	PRIV_NL80211_CMD_UNPROT_DISASSOCIATE,

	PRIV_NL80211_CMD_NEW_PEER_CANDIDATE,

	PRIV_NL80211_CMD_GET_WOWLAN,
	PRIV_NL80211_CMD_SET_WOWLAN,

	PRIV_NL80211_CMD_START_SCHED_SCAN,
	PRIV_NL80211_CMD_STOP_SCHED_SCAN,
	PRIV_NL80211_CMD_SCHED_SCAN_RESULTS,
	PRIV_NL80211_CMD_SCHED_SCAN_STOPPED,

	PRIV_NL80211_CMD_SET_REKEY_OFFLOAD,

	PRIV_NL80211_CMD_PMKSA_CANDIDATE,

	PRIV_NL80211_CMD_TDLS_OPER,
	PRIV_NL80211_CMD_TDLS_MGMT,

	PRIV_NL80211_CMD_UNEXPECTED_FRAME,

	PRIV_NL80211_CMD_PROBE_CLIENT,

	PRIV_NL80211_CMD_REGISTER_BEACONS,

	PRIV_NL80211_CMD_UNEXPECTED_4ADDR_FRAME,

	PRIV_NL80211_CMD_SET_NOACK_MAP,

	PRIV_NL80211_CMD_CH_SWITCH_NOTIFY,

	PRIV_NL80211_CMD_START_P2P_DEVICE,
	PRIV_NL80211_CMD_STOP_P2P_DEVICE,

	PRIV_NL80211_CMD_CONN_FAILED,

	PRIV_NL80211_CMD_SET_MCAST_RATE,

	/* add new commands above here */

	/* used to define PRIV_NL80211_CMD_MAX below */
	__PRIV_NL80211_CMD_AFTER_LAST,
	PRIV_NL80211_CMD_MAX = __PRIV_NL80211_CMD_AFTER_LAST - 1
};

enum PRIV_NL80211_RATE_info {
	__PRIV_NL80211_RATE_INFO_INVALID,
	PRIV_NL80211_RATE_INFO_BITRATE,
	PRIV_NL80211_RATE_INFO_MCS,
	PRIV_NL80211_RATE_INFO_40_MHZ_WIDTH,
	PRIV_NL80211_RATE_INFO_SHORT_GI,
	PRIV_NL80211_RATE_INFO_BITRATE32,

	/* keep last */
	__PRIV_NL80211_RATE_INFO_AFTER_LAST,
	PRIV_NL80211_RATE_INFO_MAX = __PRIV_NL80211_RATE_INFO_AFTER_LAST - 1
};

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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  oal_cfg80211_put_bss(oal_cfg80211_bss_stru *pst_cfg80211_bss);
extern oal_cfg80211_bss_stru *oal_cfg80211_inform_bss_frame(
                                oal_wiphy_stru              *pst_wiphy,
                                oal_ieee80211_channel_stru  *pst_ieee80211_channel,
                                oal_ieee80211_mgmt_stru     *pst_mgmt,
                                oal_uint32                   ul_len,
                                oal_int32                    l_signal,
                                oal_gfp_enum_uint8           en_ftp);
extern oal_void  oal_cfg80211_scan_done(
                oal_cfg80211_scan_request_stru *pst_cfg80211_scan_request,oal_int8 c_aborted);
extern oal_void  oal_cfg80211_sched_scan_result(oal_wiphy_stru *pst_wiphy);
extern oal_uint32  oal_cfg80211_connect_result(
                        oal_net_device_stru         *pst_net_device,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                              oal_uint16             us_status,
                              oal_gfp_enum_uint8     en_gfp);
extern  oal_uint32  oal_cfg80211_disconnected(
                    oal_net_device_stru        *pst_net_device,
                    oal_uint16                  us_reason,
                    oal_uint8                   *puc_ie,
                    oal_uint32                  ul_ie_len,
                    oal_gfp_enum_uint8          en_gfp);
extern  oal_uint32  oal_cfg80211_new_sta(
                        oal_net_device_stru     *pst_net_device,
                        const oal_uint8         *puc_mac_addr,
                        oal_station_info_stru   *pst_station_info,
                        oal_gfp_enum_uint8      en_gfp);
extern oal_void  oal_cfg80211_mic_failure(
                        oal_net_device_stru     *pst_net_device,
                        const oal_uint8         *puc_mac_addr,
                        enum nl80211_key_type    key_type,
                        oal_int32                key_id,
                        const oal_uint8         *tsc,
                        oal_gfp_enum_uint8       en_gfp);
extern oal_uint32  oal_cfg80211_del_sta(
                                   oal_net_device_stru  *pst_net_device,
                                   const oal_uint8      *puc_mac_addr,
                                   oal_gfp_enum_uint8    en_gfp);
extern oal_uint32 oal_cfg80211_rx_mgmt(
                                   oal_net_device_stru  *pst_dev,
                                   oal_int32             l_freq,
                                   const oal_uint8      *puc_buf,
                                   oal_uint32            ul_len,
                                   oal_gfp_enum_uint8    en_gfp);
extern oal_void oal_cfg80211_ready_on_channel(oal_wireless_dev_stru       *pst_wdev,
                                        oal_uint64                  ull_cookie,
			                            oal_ieee80211_channel_stru *pst_chan,
                                        oal_uint32                  ul_duration,
                                        oal_gfp_enum_uint8          en_gfp);
extern oal_void oal_cfg80211_remain_on_channel_expired(oal_wireless_dev_stru        *pst_wdev,
                                        oal_uint64                   ull_cookie,
					                    oal_ieee80211_channel_stru  *pst_listen_channel,
					                    oal_gfp_enum_uint8           en_gfp);

extern oal_void oal_cfg80211_mgmt_tx_status(struct wireless_dev *wdev, oal_uint64 cookie,
			     OAL_CONST oal_uint8 *buf, size_t len, oal_bool_enum_uint8 ack, oal_gfp_enum_uint8 gfp);
extern oal_uint32  oal_cfg80211_roamed(
                        oal_net_device_stru         *pst_net_device,
                        struct ieee80211_channel    *pst_channel,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                        oal_gfp_enum_uint8           en_gfp);
extern oal_uint32  oal_cfg80211_ft_event(oal_net_device_stru *pst_net_device, oal_cfg80211_ft_event_stru  *pst_ft_event);
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
extern oal_void oal_kobject_uevent_env_sta_join(oal_net_device_stru *pst_net_device, const oal_uint8 *puc_mac_addr);
extern oal_void oal_kobject_uevent_env_sta_leave(oal_net_device_stru *pst_net_device, const oal_uint8 *puc_mac_addr);
#endif
#endif

extern oal_uint32  oal_cfg80211_rx_exception(oal_net_device_stru *pst_netdev,
                                               oal_uint8          *puc_data,
                                               oal_uint32          ul_data_len);


extern oal_uint32  oal_cfg80211_init(oal_void);
extern oal_void  oal_cfg80211_exit(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_cfg80211.h */
