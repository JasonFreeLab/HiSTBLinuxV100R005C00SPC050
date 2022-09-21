/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_cfg80211.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月8日
  最近修改   :
  功能描述   : wal_linux_cfg80211.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_LINUX_CFG80211_H__
#define __WAL_LINUX_CFG80211_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_types.h"
#include "wal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_ext_if.h"
#include "wal_linux_ioctl.h"
#include "wal_linux_scan.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_CFG80211_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     WAL_MAX_SCAN_TIME_PER_CHANNEL  400

#define     WAL_MAX_SCAN_TIME_PER_SCAN_REQ (5 * 1000)      /* wpa_s下发扫描请求，超时时间为5s，单位为ms */

/* channel index and frequence */
#define WAL_MIN_CHANNEL_2G      1
#define WAL_MAX_CHANNEL_2G      14

#define WAL_MIN_CHANNEL_5G      36
#define WAL_MAX_CHANNEL_5G      165

#define WAL_MIN_CHANNEL_4_9G    184
#define WAL_MAX_CHANNEL_4_9G    196

#define WAL_MIN_FREQ_2G    (2412 + 5*(WAL_MIN_CHANNEL_2G - 1))
#define WAL_MAX_FREQ_2G    (2484)
#define WAL_MIN_FREQ_5G    (5000 + 5*(WAL_MIN_CHANNEL_5G))
#define WAL_MAX_FREQ_5G    (5000 + 5*(WAL_MAX_CHANNEL_5G))

/* channel nums */
#define WAL_SCAN_CHANNEL_MAX_NUM ((WAL_MAX_CHANNEL_2G - WAL_MIN_CHANNEL_2G + 1) + (WAL_MAX_CHANNEL_4_9G - WAL_MIN_CHANNEL_5G + 1))

/* wiphy 结构体初始化变量 */
//#define WAL_MAX_PROBED_SSID_NUM     1
#define WAL_MAX_SCAN_IE_LEN        1000
/* 802.11n HT 能力掩码 */
#define IEEE80211_HT_CAP_LDPC_CODING        0x0001
#define IEEE80211_HT_CAP_SUP_WIDTH_20_40    0x0002
#define IEEE80211_HT_CAP_SM_PS          0x000C
#define IEEE80211_HT_CAP_SM_PS_SHIFT    2
#define IEEE80211_HT_CAP_GRN_FLD        0x0010
#define IEEE80211_HT_CAP_SGI_20         0x0020
#define IEEE80211_HT_CAP_SGI_40         0x0040
#define IEEE80211_HT_CAP_TX_STBC        0x0080
#define IEEE80211_HT_CAP_RX_STBC        0x0300
#define IEEE80211_HT_CAP_DELAY_BA       0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU      0x0800
#define IEEE80211_HT_CAP_DSSSCCK40      0x1000
#define IEEE80211_HT_CAP_RESERVED       0x2000
#define IEEE80211_HT_CAP_40MHZ_INTOLERANT   0x4000
#define IEEE80211_HT_CAP_LSIG_TXOP_PROT     0x8000

/* 802.11ac VHT Capabilities */
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895			0x00000000
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991			0x00000001
#define IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454			0x00000002
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ		0x00000004
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ	0x00000008
#define IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK			0x0000000C
#define IEEE80211_VHT_CAP_RXLDPC				0x00000010
#define IEEE80211_VHT_CAP_SHORT_GI_80				0x00000020
#define IEEE80211_VHT_CAP_SHORT_GI_160				0x00000040
#define IEEE80211_VHT_CAP_TXSTBC				0x00000080
#define IEEE80211_VHT_CAP_RXSTBC_1				0x00000100
#define IEEE80211_VHT_CAP_RXSTBC_2				0x00000200
#define IEEE80211_VHT_CAP_RXSTBC_3				0x00000300
#define IEEE80211_VHT_CAP_RXSTBC_4				0x00000400
#define IEEE80211_VHT_CAP_RXSTBC_MASK				0x00000700
#define IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE			0x00000800
#define IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE			0x00001000
#define IEEE80211_VHT_CAP_BEAMFORMER_ANTENNAS_MAX		0x00006000
#define IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MAX		0x00030000
#define IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE			0x00080000
#define IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE			0x00100000
#define IEEE80211_VHT_CAP_VHT_TXOP_PS				0x00200000
#define IEEE80211_VHT_CAP_HTC_VHT				0x00400000
#define IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT	23
#define IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK	\
		(7 << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT)
#define IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB	0x08000000
#define IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB	0x0c000000
#define IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN			0x10000000
#define IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN			0x20000000

/* management */
#define IEEE80211_STYPE_ASSOC_REQ       0x0000
#define IEEE80211_STYPE_ASSOC_RESP      0x0010
#define IEEE80211_STYPE_REASSOC_REQ     0x0020
#define IEEE80211_STYPE_REASSOC_RESP    0x0030
#define IEEE80211_STYPE_PROBE_REQ       0x0040
#define IEEE80211_STYPE_PROBE_RESP      0x0050
#define IEEE80211_STYPE_BEACON          0x0080
#define IEEE80211_STYPE_ATIM            0x0090
#define IEEE80211_STYPE_DISASSOC        0x00A0
#define IEEE80211_STYPE_AUTH            0x00B0
#define IEEE80211_STYPE_DEAUTH          0x00C0
#define IEEE80211_STYPE_ACTION          0x00D0

#define WAL_COOKIE_ARRAY_SIZE           8       /* 采用8bit 的map 作为保存cookie 的索引状态 */
#define WAL_MGMT_TX_TIMEOUT_MSEC        100     /* WAL 发送管理帧超时时间 */
#define WAL_MGMT_TX_RETRY_CNT           8       /* WAL 发送管理帧最大重传次数 */

#define IEEE80211_FCTL_FTYPE            0x000c
#define IEEE80211_FCTL_STYPE            0x00f0
#define IEEE80211_FTYPE_MGMT            0x0000

#define WAL_GET_STATION_THRESHOLD 1000 /* 固定时间内允许一次抛事件读DMAC RSSI */

typedef struct cookie_arry
{
    oal_uint64  ull_cookie;
    oal_uint32  ul_record_time;
}cookie_arry_stru;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#define RATETAB_ENT(_rate, _rateid, _flags)     \
{                                                               \
    .bitrate        = (_rate),                                  \
    .hw_value       = (_rateid),                                \
    .flags          = (_flags),                                 \
}

#define CHAN2G(_channel, _freq, _flags)  \
{                       \
    .band                   = IEEE80211_BAND_2GHZ,          \
    .center_freq            = (_freq),                      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#define CHAN5G(_channel, _flags) \
{                                              \
    .band                   = IEEE80211_BAND_5GHZ,          \
    .center_freq            = 5000 + (5 * (_channel)),      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#define CHAN4_9G(_channel, _flags) \
{                                              \
    .band                   = IEEE80211_BAND_5GHZ,          \
    .center_freq            = 4000 + (5 * (_channel)),      \
    .hw_value               = (_channel),                   \
    .flags                  = (_flags),                     \
    .max_antenna_gain       = 0,                            \
    .max_power              = 30,                           \
}

#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

#define RATETAB_ENT(_rate, _rateid, _flags)     \
{                                               \
    (_flags),                                   \
    (_rate),                  \
    (_rateid),                \
}

#define CHAN2G(_channel, _freq, _flags)  \
{                       \
    IEEE80211_BAND_2GHZ,          \
    (_freq),                      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}

#define CHAN5G(_channel, _flags)  \
{                                 \
    IEEE80211_BAND_5GHZ,          \
    5000 + (5 * (_channel)),      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}

#define CHAN4_9G(_channel, _flags) \
{                                 \
    IEEE80211_BAND_5GHZ,          \
    4000 + (5 * (_channel)),      \
    (_channel),                   \
    (_flags),                     \
    0,                            \
    30,                           \
}


#else
    error "WRONG OS VERSION"
#endif


#define WAL_MIN_RTS_THRESHOLD 256
#define WAL_MAX_RTS_THRESHOLD 0xFFFF

#define WAL_MAX_FRAG_THRESHOLD 7536
#define WAL_MIN_FRAG_THRESHOLD 256

#define WAL_MAX_WAIT_TIME 3000
/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_workqueue_stru  *g_pst_del_virtual_inf_workqueue;


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
        /* 此处02加载ko时出现，找不到符号的错误，待后续解决 TBD */
/*****************************************************************************
 函 数 名  : oal_ieee80211_is_probe_resp
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年1月7日
    作    者   :  
    修改内容   : 判断是否是probe response
    check if IEEE80211_FTYPE_MGMT && IEEE80211_STYPE_PROBE_RESP
    @fc: frame control bytes in little-endian byteorder

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_ieee80211_is_probe_resp(oal_uint16 fc)
{
	return (fc &  (IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE)) ==
	       (IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_PROBE_RESP);
}

extern oal_void  wal_cfg80211_exit(oal_void);

extern oal_uint32  wal_cfg80211_init(oal_void);

extern oal_uint32  wal_cfg80211_init_evt_handle(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_cfg80211_mgmt_tx_status(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32  wal_roam_comp_proc_sta(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
extern oal_uint32  wal_ft_event_proc_sta(frw_event_mem_stru *pst_event_mem);
#endif //_PRE_WLAN_FEATURE_11R

extern oal_void wal_cfg80211_unregister_netdev(oal_net_device_stru *pst_net_dev);

extern oal_uint32 wal_del_p2p_group(mac_device_stru *pst_mac_device);


extern oal_uint32 wal_cfg80211_add_vap(mac_cfg_add_vap_param_stru *pst_add_vap_param);

extern oal_void wal_cfg80211_reset_bands(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_cfg80211.h */
