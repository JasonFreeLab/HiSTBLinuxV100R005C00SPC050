/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_vap.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   : mac_vap.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_VAP_H__
#define __MAC_VAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_mib.h"
#include "mac_user.h"
#include "oam_ext_if.h"
#include "mac_regdomain.h"
#include "hal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_VAP_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MAC_NUM_DR_802_11A              8    /* 11A 5g模式时的数据速率(DR)个数 */
#define MAC_NUM_BR_802_11A              3    /* 11A 5g模式时的基本速率(BR)个数 */
#define MAC_NUM_NBR_802_11A             5    /* 11A 5g模式时的非基本速率(NBR)个数 */

#define MAC_NUM_DR_802_11B              4    /* 11B 2.4G模式时的数据速率(DR)个数 */
#define MAC_NUM_BR_802_11B              2    /* 11B 2.4G模式时的数据速率(BR)个数 */
#define MAC_NUM_NBR_802_11B             2    /* 11B 2.4G模式时的数据速率(NBR)个数 */

#define MAC_NUM_DR_802_11G              8    /* 11G 2.4G模式时的数据速率(DR)个数 */
#define MAC_NUM_BR_802_11G              3    /* 11G 2.4G模式时的基本速率(BR)个数 */
#define MAC_NUM_NBR_802_11G             5    /* 11G 2.4G模式时的非基本速率(NBR)个数 */

#define MAC_NUM_DR_802_11G_MIXED        12   /* 11G 混合模式时的数据速率(DR)个数 */
#define MAC_NUM_BR_802_11G_MIXED_ONE    4    /* 11G 混合1模式时的基本速率(BR)个数 */
#define MAC_NUM_NBR_802_11G_MIXED_ONE   8    /* 11G 混合1模式时的非基本速率(NBR)个数 */

#define MAC_NUM_BR_802_11G_MIXED_TWO    7    /* 11G 混合2模式时的基本速率(BR)个数 */
#define MAC_NUM_NBR_802_11G_MIXED_TWO   5    /* 11G 混合2模式时的非基本速率(NBR)个数 */

/* 11N MCS相关的内容 */
#if 0
#define MAC_MAX_RATE_SINGLE_NSS_20M_11N 72  /* 1个空间流20MHz的最大速率*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11N 150 /* 1个空间流40MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11N 144 /* 1个空间流80MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11N 300 /* 2个空间流20MHz的最大速率*/
#endif

#define MAC_MAX_RATE_SINGLE_NSS_20M_11N 0  /* 1个空间流20MHz的最大速率*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11N 0 /* 1个空间流40MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11N 0 /* 1个空间流80MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11N 0 /* 2个空间流20MHz的最大速率*/

/* 11AC MCS相关的内容 */
#define MAC_MAX_SUP_MCS7_11AC_EACH_NSS   0   /* 11AC各空间流支持的最大MCS序号，支持0-7*/
#define MAC_MAX_SUP_MCS8_11AC_EACH_NSS   1   /* 11AC各空间流支持的最大MCS序号，支持0-8*/
#define MAC_MAX_SUP_MCS9_11AC_EACH_NSS   2   /* 11AC各空间流支持的最大MCS序号，支持0-9*/
#define MAC_MAX_UNSUP_MCS_11AC_EACH_NSS  3   /* 11AC各空间流支持的最大MCS序号，不支持n个空间流*/

#define MAC_MAX_RATE_SINGLE_NSS_20M_11AC 86  /* 1个空间流20MHz的最大速率*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11AC 200 /* 1个空间流40MHz的最大速率*/
#define MAC_MAX_RATE_SINGLE_NSS_80M_11AC 433 /* 1个空间流80MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11AC 173 /* 2个空间流20MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11AC 400 /* 2个空间流40MHz的最大速率*/
#define MAC_MAX_RATE_DOUBLE_NSS_80M_11AC 866 /* 2个空间流80MHz的最大速率*/


#define MAC_VAP_USER_HASH_INVALID_VALUE      0xFFFFFFFF                         /* HSAH非法值 */
#define MAC_VAP_USER_HASH_MAX_VALUE         (WLAN_ASSOC_USER_MAX_NUM_LIMIT * 2)       /* 2为扩展因子 */

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define MAC_VAP_PROXY_STA_HASH_MAX_VALUE     16       /* 硬件索引为16~31，最多16个,其实最多创建15个proxy sta */
#endif

#define MAC_VAP_CAP_ENABLE                   1
#define MAC_VAP_CAP_DISABLE                  0

#define MAC_VAP_FEATURE_ENABLE               1
#define MAC_VAP_FEATRUE_DISABLE              0

#define MAC_CALCULATE_HASH_VALUE(_puc_mac_addr)     \
    ((_puc_mac_addr[0] + _puc_mac_addr[1]           \
    + _puc_mac_addr[2] + _puc_mac_addr[3]           \
    + _puc_mac_addr[4] + _puc_mac_addr[5])          \
    & (MAC_VAP_USER_HASH_MAX_VALUE - 1))

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define MAC_PROXYSTA_CALCULATE_HASH_VALUE(_puc_mac_addr)     \
    ((_puc_mac_addr[0] + _puc_mac_addr[1]           \
    + _puc_mac_addr[2] + _puc_mac_addr[3]           \
    + _puc_mac_addr[4] + _puc_mac_addr[5])          \
    & (MAC_VAP_PROXY_STA_HASH_MAX_VALUE - 1))
#endif

#define IS_AP(_pst_mac_vap)  (WLAN_VAP_MODE_BSS_AP  == (_pst_mac_vap)->en_vap_mode)
#define IS_STA(_pst_mac_vap) (WLAN_VAP_MODE_BSS_STA == (_pst_mac_vap)->en_vap_mode)

#define IS_P2P_DEV(_pst_mac_vap)    (WLAN_P2P_DEV_MODE    == (_pst_mac_vap)->en_p2p_mode)
#define IS_P2P_GO(_pst_mac_vap)     (WLAN_P2P_GO_MODE     == (_pst_mac_vap)->en_p2p_mode)
#define IS_P2P_CL(_pst_mac_vap)     (WLAN_P2P_CL_MODE     == (_pst_mac_vap)->en_p2p_mode)
#define IS_LEGACY_VAP(_pst_mac_vap) (WLAN_LEGACY_VAP_MODE == (_pst_mac_vap)->en_p2p_mode)

#define CIPHER_IS_WEP(cipher) ((WLAN_CIPHER_SUITE_WEP40 == cipher)||(WLAN_CIPHER_SUITE_WEP104 == cipher))

#ifdef _PRE_WLAN_DFT_STAT
#define   MAC_VAP_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))
#define   MAC_VAP_STATS_BYTE_INCR(_member, _cnt)           ((_member) += (_cnt))
#endif

#define MAC_DATA_CONTAINER_HEADER_LEN 4
#define MAC_DATA_CONTAINER_MAX_LEN    512
#define MAC_DATA_CONTAINER_MIN_LEN    8  /*至少要包含1个事件*/
#define MAC_DATA_HEADER_LEN           4

#define MAC_SEND_TWO_DEAUTH_FLAG    0xf000

#define MAC_DBB_SCALING_2G_RATE_NUM 12                /*2G rate速率的个数*/
#define MAC_DBB_SCALING_5G_RATE_NUM 8                /*2G rate速率的个数*/
#define MAC_DBB_SCALING_2G_RATE_OFFSET 0                /*2G Rate dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_2G_HT20_MCS_OFFSET 12                /*2G HT20 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_2G_HT40_MCS_OFFSET 20                /*2G HT40 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_2G_HT40_MCS32_OFFSET 61                /*2G HT40 mcs32 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_RATE_OFFSET 28                /*5G Rate dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT20_MCS_OFFSET 40                /*5G HT20 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT20_MCS8_OFFSET 36                /*5G HT20 mcs8 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT40_MCS_OFFSET 48                /*5G HT40 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT40_MCS32_OFFSET 60                /*5G HT40 mcs32 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT80_MCS_OFFSET 66                /*5G HT80 dbb scaling 索引偏移值*/
#define MAC_DBB_SCALING_5G_HT80_MCS0_DELTA_OFFSET 2                /*5G HT80 mcs0/1 dbb scaling 索引偏移值回退值*/
#define MAC_DBB_SCALING_CFG_BITS 8                /*dbb scaling配置寄存器位数*/
#define MAC_DBB_SCALING_FIX_POINT_BITS 8                /*dbb scaling 定点化放大倍数 256 (8 bits)*/
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#define MAC_NUM_2G_BAND 3   /*2g band个数*/
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* VAP状态机，AP STA共用一个状态枚举 */
typedef enum
{
    /* ap sta公共状态 */
    MAC_VAP_STATE_INIT               = 0,
    MAC_VAP_STATE_UP                 = 1,       /* VAP UP */
    MAC_VAP_STATE_PAUSE              = 2,       /* pause , for ap &sta */

    /* ap 独有状态 */
    MAC_VAP_STATE_AP_WAIT_START      = 3,

    /* sta独有状态 */
    MAC_VAP_STATE_STA_FAKE_UP        = 4,
    MAC_VAP_STATE_STA_WAIT_SCAN      = 5,
    MAC_VAP_STATE_STA_SCAN_COMP      = 6,
    MAC_VAP_STATE_STA_JOIN_COMP      = 7,
    MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 = 8,
    MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 = 9,
    MAC_VAP_STATE_STA_AUTH_COMP      = 10,
    MAC_VAP_STATE_STA_WAIT_ASOC      = 11,
    MAC_VAP_STATE_STA_OBSS_SCAN      = 12,
    MAC_VAP_STATE_STA_BG_SCAN        = 13,
    MAC_VAP_STATE_STA_LISTEN         = 14,/* p2p0 监听 */
#ifdef _PRE_WLAN_FEATURE_ROAM
    MAC_VAP_STATE_ROAMING            = 15,/* 漫游 */
#endif //_PRE_WLAN_FEATURE_ROAM
    MAC_VAP_STATE_BUTT,
}mac_vap_state_enum;
typedef oal_uint8  mac_vap_state_enum_uint8;

/* 芯片验证，控制帧/管理帧类型 */
typedef enum
{

    MAC_TEST_MGMT_BCST   =  0,/* 非beacon广播管理帧 */
    MAC_TEST_MGMT_MCST  =   1,/* 非beacon组播管理帧 */
    MAC_TEST_ATIM_UCST =    2,/* 单播ATIM帧 */
    MAC_TEST_UCST =         3,/* 单播管理帧 */
    MAC_TEST_CTL_BCST =     4,/* 广播控制帧 */
    MAC_TEST_CTL_MCST =     5,/* 组播控制帧 */
    MAC_TEST_CTL_UCST =     6,/* 单播控制帧 */
    MAC_TEST_ACK_UCST =     7,/* ACK控制帧 */
    MAC_TEST_CTS_UCST =     8,/* CTS控制帧 */
    MAC_TEST_RTS_UCST =     9,/* RTS控制帧 */
    MAC_TEST_BA_UCST =      10,/* BA控制帧 */
    MAC_TEST_CF_END_UCST =  11,/* CF-End控制帧 */
    MAC_TEST_TA_RA_EUQAL =  12,/* RA,TA相同帧 */
    MAC_TEST_MAX_TYPE_NUM
}mac_test_frame_type;
typedef oal_uint8 mac_test_frame_type_enum_uint8;



typedef enum
{
    MAC_VAP_CONFIG_UCAST_DATA  = 0,
    MAC_VAP_CONFIG_MCAST_DATA,
    MAC_VAP_CONFIG_BCAST_DATA,
    MAC_VAP_CONFIG_UCAST_MGMT_2G,
    MAC_VAP_CONFIG_UCAST_MGMT_5G,
    MAC_VAP_CONFIG_MBCAST_MGMT_2G,
    MAC_VAP_CONFIG_MBCAST_MGMT_5G,

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    MAC_VAP_CONFIG_MODE_UCAST_DATA,                                 /* 区分协议设置单播数据帧参数的起始枚举 */
    MAC_VAP_CONFIG_VHT_UCAST_DATA = MAC_VAP_CONFIG_MODE_UCAST_DATA, /* 针对11ac用户设置单播数据帧参数 */
    MAC_VAP_CONFIG_HT_UCAST_DATA,                                   /* 针对11n用户设置单播数据帧参数 */
    MAC_VAP_CONFIG_11AG_UCAST_DATA,                                 /* 针对11a/11g用户设置单播数据帧参数 */
    MAC_VAP_CONFIG_11B_UCAST_DATA,                                  /* 针对11b用户设置单播数据帧参数 */
#endif

    MAC_VAP_CONFIG_BUTT,
} mac_vap_config_dscr_frame_type_enum;
typedef oal_uint8 mac_vap_config_dscr_frame_type_uint8;



typedef enum
{
    /* 业务调度算法配置参数,请添加到对应的START和END之间 */
    MAC_ALG_CFG_SCHEDULE_START,

    MAC_ALG_CFG_SCHEDULE_VI_CTRL_ENA,
    MAC_ALG_CFG_SCHEDULE_BEBK_MIN_BW_ENA,
    MAC_ALG_CFG_SCHEDULE_MVAP_SCH_ENA,
    MAC_ALG_CFG_FLOWCTRL_ENABLE_FLAG,
    MAC_ALG_CFG_SCHEDULE_VI_SCH_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VO_SCH_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VI_DROP_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VI_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_VO_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_BE_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_BK_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_VI_LOW_DELAY_MS,
    MAC_ALG_CFG_SCHEDULE_VI_HIGH_DELAY_MS,
    MAC_ALG_CFG_SCHEDULE_VI_CTRL_MS,
    MAC_ALG_CFG_SCHEDULE_SCH_CYCLE_MS,
    MAC_ALG_CFG_SCHEDULE_TRAFFIC_CTRL_CYCLE,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS_BE,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS_BK,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS_BE,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS_BK,
    MAC_ALG_CFG_SCHEDULE_CIR_VAP_KBPS,
    MAC_ALG_CFG_SCHEDULE_SM_TRAIN_DELAY,
    MAC_ALG_CFG_VIDEO_DROP_PKT_LIMIT,
    MAC_ALG_CFG_SCHEDULE_LOG_START,
    MAC_ALG_CFG_SCHEDULE_VAP_SCH_PRIO,

    MAC_ALG_CFG_SCHEDULE_LOG_END,

    MAC_ALG_CFG_SCHEDULE_END,

    /* AUTORATE算法配置参数，请添加到对应的START和END之间*/
    MAC_ALG_CFG_AUTORATE_START,

    MAC_ALG_CFG_AUTORATE_ENABLE,
    MAC_ALG_CFG_AUTORATE_USE_LOWEST_RATE,
    MAC_ALG_CFG_AUTORATE_SHORT_STAT_NUM,
    MAC_ALG_CFG_AUTORATE_SHORT_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_LONG_STAT_NUM,
    MAC_ALG_CFG_AUTORATE_LONG_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_MIN_PROBE_INTVL_PKTNUM,
    MAC_ALG_CFG_AUTORATE_MAX_PROBE_INTVL_PKTNUM,
    MAC_ALG_CFG_AUTORATE_PROBE_INTVL_KEEP_TIMES,
    MAC_ALG_CFG_AUTORATE_DELTA_GOODPUT_RATIO,
    MAC_ALG_CFG_AUTORATE_VI_PROBE_PER_LIMIT,
    MAC_ALG_CFG_AUTORATE_VO_PROBE_PER_LIMIT,
    MAC_ALG_CFG_AUTORATE_AMPDU_DURATION,
    MAC_ALG_CFG_AUTORATE_MCS0_CONT_LOSS_NUM,
    MAC_ALG_CFG_AUTORATE_UP_PROTOCOL_DIFF_RSSI,
    MAC_ALG_CFG_AUTORATE_RTS_MODE,
    MAC_ALG_CFG_AUTORATE_LEGACY_1ST_LOSS_RATIO_TH,
    MAC_ALG_CFG_AUTORATE_HT_VHT_1ST_LOSS_RATIO_TH,
    MAC_ALG_CFG_AUTORATE_LOG_ENABLE,
    MAC_ALG_CFG_AUTORATE_VO_RATE_LIMIT,
    MAC_ALG_CFG_AUTORATE_JUDGE_FADING_PER_TH,
    MAC_ALG_CFG_AUTORATE_AGGR_OPT,
    MAC_ALG_CFG_AUTORATE_AGGR_PROBE_INTVL_NUM,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_DBAC_AGGR_TIME,
    MAC_ALG_CFG_AUTORATE_DBG_VI_STATUS,
    MAC_ALG_CFG_AUTORATE_DBG_AGGR_LOG,
    MAC_ALG_CFG_AUTORATE_AGGR_NON_PROBE_PCK_NUM,
    MAC_ALG_CFG_AUTORATE_AGGR_MIN_AGGR_TIME_IDX,
    MAC_ALG_CFG_AUTORATE_MAX_AGGR_NUM,
    MAC_ALG_CFG_AUTORATE_LIMIT_1MPDU_PER_TH,
    MAC_ALG_CFG_AUTORATE_BTCOEX_PROBE_ENABLE,
    MAC_ALG_CFG_AUTORATE_BTCOEX_AGGR_ENABLE,
    MAC_ALG_CFG_AUTORATE_COEX_STAT_INTVL,
    MAC_ALG_CFG_AUTORATE_COEX_LOW_ABORT_TH,
    MAC_ALG_CFG_AUTORATE_COEX_HIGH_ABORT_TH,
    MAC_ALG_CFG_AUTORATE_COEX_AGRR_NUM_ONE_TH,
    MAC_ALG_CFG_AUTORATE_DYNAMIC_BW_ENABLE,
    MAC_ALG_CFG_AUTORATE_THRPT_WAVE_OPT,
    MAC_ALG_CFG_AUTORATE_GOODPUT_DIFF_TH,
    MAC_ALG_CFG_AUTORATE_PER_WORSE_TH,
    MAC_ALG_CFG_AUTORATE_RX_CTS_NO_BA_NUM,
    MAL_ALG_CFG_AUTORATE_VOICE_AGGR,
    MAC_ALG_CFG_AUTORATE_FAST_SMOOTH_SHIFT,
    MAC_ALG_CFG_AUTORATE_FAST_SMOOTH_AGGR_NUM,
    MAC_ALG_CFG_AUTORATE_SGI_PUNISH_PER,
    MAC_ALG_CFG_AUTORATE_SGI_PUNISH_NUM,

    MAC_ALG_CFG_AUTORATE_END,

    /*AUTORATE算法日志配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_AUTORATE_LOG_START,

    MAC_ALG_CFG_AUTORATE_STAT_LOG_START,
    MAC_ALG_CFG_AUTORATE_SELECTION_LOG_START,
    MAC_ALG_CFG_AUTORATE_FIX_RATE_LOG_START,
    MAC_ALG_CFG_AUTORATE_STAT_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_SELECTION_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_FIX_RATE_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_LOG_START,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_LOG_WRITE,

    MAC_ALG_CFG_AUTORATE_LOG_END,

    /*AUTORATE算法系统测试命令，请添加到对应的START和END之间 */
    MAC_ALG_CFG_AUTORATE_TEST_START,

    MAC_ALG_CFG_AUTORATE_DISPLAY_RATE_SET,
    MAC_ALG_CFG_AUTORATE_CONFIG_FIX_RATE,
    MAC_ALG_CFG_AUTORATE_CYCLE_RATE,
    MAC_ALG_CFG_AUTORATE_DISPLAY_RX_RATE,

    MAC_ALG_CFG_AUTORATE_TEST_END,

    /* SMARTANT算法配置参数， 请添加到对应的START和END之间*/
    MAC_ALG_CFG_SMARTANT_START,

    MAC_ALG_CFG_SMARTANT_TRAINING_PACKET_NUMBER,

    MAC_ALG_CFG_SMARTANT_END,
    /* TXBF算法配置参数，请添加到对应的START和END之间*/
    MAC_ALG_CFG_TXBF_START,
    MAC_ALG_CFG_TXBF_MASTER_SWITCH,
    MAC_ALG_CFG_TXBF_TXMODE_ENABLE,
    MAC_ALG_CFG_TXBF_TXBFER_ENABLE,
    MAC_ALG_CFG_TXBF_TXBFEE_ENABLE,
    MAC_ALG_CFG_TXBF_11N_BFEE_ENABLE,
    MAC_ALG_CFG_TXBF_TXSTBC_ENABLE,
    MAC_ALG_CFG_TXBF_RXSTBC_ENABLE,
    MAC_ALG_CFG_TXBF_2G_BFER_ENABLE,
    MAC_ALG_CFG_TXBF_2NSS_BFER_ENABLE,
    MAC_ALG_CFG_TXBF_FIX_MODE,
    MAC_ALG_CFG_TXBF_FIX_SOUNDING,
    MAC_ALG_CFG_TXBF_LOG_ENABLE,
    MAC_ALG_CFG_TXBF_END,
    /* TXBF LOG配置参数，请添加到对应的START和END之间*/
    MAC_ALG_CFG_TXBF_LOG_START,
    MAC_ALG_CFG_TXBF_RECORD_LOG_START,
    MAC_ALG_CFG_TXBF_LOG_OUTPUT,
    MAC_ALG_CFG_TXBF_LOG_END,

    /* 抗干扰算法配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_ANTI_INTF_START,

    MAC_ALG_CFG_ANTI_INTF_IMM_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_RSSI_STAT_CYCLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_CYCLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_DUR_TIME,
    MAC_ALG_CFG_ANTI_INTF_NAV_IMM_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_GOODPUT_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_KEEP_CYC_MAX_NUM,
    MAC_ALG_CFG_ANTI_INTF_KEEP_CYC_MIN_NUM,
    MAC_ALG_CFG_ANTI_INTF_TX_TIME_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_PER_PROBE_EN,
    MAC_ALG_CFG_ANTI_INTF_PER_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_GOODPUT_JITTER_TH,
    MAC_ALG_CFG_ANTI_INTF_DEBUG_MODE,

    MAC_ALG_CFG_ANTI_INTF_END,

    /* EDCA优化算法配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_EDCA_OPT_START,

    MAC_ALG_CFG_EDCA_OPT_CO_CH_DET_CYCLE,
    MAC_ALG_CFG_EDCA_OPT_AP_EN_MODE,
    MAC_ALG_CFG_EDCA_OPT_STA_EN,
    MAC_ALG_CFG_EDCA_OPT_STA_WEIGHT,
    MAC_ALG_CFG_EDCA_OPT_NONDIR_TH,
    MAC_ALG_CFG_EDCA_OPT_TH_UDP,
    MAC_ALG_CFG_EDCA_OPT_TH_TCP,
    MAC_ALG_CFG_EDCA_OPT_DEBUG_MODE,

    MAC_ALG_CFG_EDCA_OPT_END,

    /* CCA优化算法配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_CCA_OPT_START,

    MAC_ALG_CFG_CCA_OPT_ALG_EN_MODE,
    MAC_ALG_CFG_CCA_OPT_DEBUG_MODE,
    MAC_ALG_CFG_CCA_OPT_SET_T1_COUNTER_TIME,
    MAC_ALG_CFG_CCA_OPT_SET_T2_COUNTER_TIME,
    MAC_ALG_CFG_CCA_OPT_SET_ILDE_CNT_TH,
    MAC_ALG_CFG_CCA_OPT_SET_DUTY_CYC_TH,
    MAC_ALG_CFG_CCA_OPT_SET_AVEG_RSSI_TH,
    MAC_ALG_CFG_CCA_OPT_SET_CHN_SCAN_CYC,
    MAC_ALG_CFG_CCA_OPT_SET_SYNC_ERR_TH,
    MAC_ALG_CFG_CCA_OPT_SET_CCA_TH_DEBUG,
    MAC_ALG_CFG_CCA_OPT_LOG,
    MAC_ALG_CFG_CCA_OPT_SET_COLLISION_RATIO_TH,
    MAC_ALG_CFG_CCA_OPT_SET_GOODPUT_LOSS_TH,
    MAC_ALG_CFG_CCA_OPT_SET_MAX_INTVL_NUM,
    MAC_ALG_CFG_CCA_OPT_NON_INTF_CYCLE_NUM_TH,
    MAC_ALG_CFG_CCA_OPT_NON_INTF_DUTY_CYC_TH,
    MAC_ALG_CFG_CCA_OPT_END,

    /*CCA OPT算法日志配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_CCA_OPT_LOG_START,
    MAC_ALG_CFG_CCA_OPT_STAT_LOG_START,
    MAC_ALG_CFG_CCA_OPT_STAT_LOG_WRITE,
    MAC_ALG_CFG_CCA_OPT_LOG_END,

    /* TPC算法配置参数, 请添加到对应的START和END之间*/
    MAC_ALG_CFG_TPC_START,

    MAC_ALG_CFG_TPC_MODE,
    MAC_ALG_CFG_TPC_DEBUG,
    MAC_ALG_CFG_TPC_POWER_LEVEL,
    MAC_ALG_CFG_TPC_LOG,
    MAC_ALG_CFG_TPC_MANAGEMENT_MCAST_FRM_POWER_LEVEL,
    MAC_ALG_CFG_TPC_CONTROL_FRM_POWER_LEVEL,
    MAC_ALG_CFG_TPC_OVER_TMP_TH,
    MAC_ALG_CFG_TPC_DPD_ENABLE_RATE,
    MAC_ALG_CFG_TPC_TARGET_RATE_11B,
    MAC_ALG_CFG_TPC_TARGET_RATE_11AG,
    MAC_ALG_CFG_TPC_TARGET_RATE_HT20,
    MAC_ALG_CFG_TPC_TARGET_RATE_HT40,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT20,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT40,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT80,
    MAC_ALG_CFG_TPC_SHOW_LOG_INFO,
    MAC_ALG_CFG_TPC_NO_MARGIN_POW,
    MAC_ALG_CFG_TPC_POWER_AMEND,

    MAC_ALG_CFG_TPC_END,

    /*TPC算法日志配置参数，请添加到对应的START和END之间 */
    MAC_ALG_CFG_TPC_LOG_START,

    MAC_ALG_CFG_TPC_STAT_LOG_START,
    MAC_ALG_CFG_TPC_STAT_LOG_WRITE,
    MAC_ALG_CFG_TPC_PER_PKT_LOG_START,
    MAC_ALG_CFG_TPC_PER_PKT_LOG_WRITE,
    MAC_ALG_CFG_TPC_GET_FRAME_POW,
    MAC_ALG_CFG_TPC_RESET_STAT,
    MAC_ALG_CFG_TPC_RESET_PKT,

    MAC_ALG_CFG_TPC_LOG_END,

    MAC_ALG_CFG_BUTT
}mac_alg_cfg_enum;
typedef oal_uint8 mac_alg_cfg_enum_uint8;

typedef enum            /* hi1102-cb */
{
    SHORTGI_20_CFG_ENUM,
    SHORTGI_40_CFG_ENUM,
    SHORTGI_80_CFG_ENUM,
    SHORTGI_BUTT_CFG
}short_gi_cfg_type;

typedef enum
{
    MAC_SET_BEACON  = 0,
    MAC_ADD_BEACON  = 1,

    MAC_BEACON_OPERATION_BUTT
}mac_beacon_operation_type ;
typedef oal_uint8 mac_beacon_operation_type_uint8;

typedef enum
{
    MAC_WMM_SET_PARAM_TYPE_DEFAULT,
    MAC_WMM_SET_PARAM_TYPE_UPDATE_EDCA,

    MAC_WMM_SET_PARAM_TYPE_BUTT
}mac_wmm_set_param_type_enum;
typedef oal_uint8 mac_wmm_set_param_type_enum_uint8;


#define MAC_VAP_AP_STATE_BUTT       (MAC_VAP_STATE_AP_WAIT_START + 1)
#define MAC_VAP_STA_STATE_BUTT      MAC_VAP_STATE_BUTT

#define H2D_SYNC_MASK_BARK_PREAMBLE (1<<1)
#define H2D_SYNC_MASK_MIB           (1<<2)
#define H2D_SYNC_MASK_PROT          (1<<3)
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
enum
{
    FREQ_IDLE                          = 0,

    FREQ_MIDIUM                            = 1,

    FREQ_HIGHER                            = 2,

    FREQ_HIGHEST                           = 3,

    FREQ_HIGHEST_DBG_480MHZ                           = 4,

    FREQ_BUTT                           = 5
};
typedef oal_uint8 oal_device_freq_type_enum_uint8;
#endif

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
/* channel结构体 */
typedef struct
{
    oal_uint8                           uc_chan_number;     /* 主20MHz信道号 */
    wlan_channel_band_enum_uint8        en_band;            /* 频段 */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;       /* 带宽模式 */
    oal_uint8                           uc_idx;             /* 信道索引号 */
}mac_channel_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
typedef struct                          /* hi1102-cb */
{
    oal_uint8                           uc_shortgi_type;    /* shortgi 20/40/80     */
    oal_uint8                           uc_enable;          /* 1:enable; 0:disable  */
    oal_uint8                           auc_resv[2];
}shortgi_cfg_stru;
#endif
#define SHORTGI_CFG_STRU_LEN            4

typedef struct
{
    oal_uint8                            uc_announced_channel;     /* 新信道号 */
    wlan_channel_bandwidth_enum_uint8    en_announced_bandwidth;   /* 新带宽模式 */
    oal_uint8                            uc_ch_switch_cnt;         /* 信道切换计数 */
    wlan_ch_switch_status_enum_uint8     en_ch_switch_status;      /* 信道切换状态 */
    wlan_bw_switch_status_enum_uint8     en_bw_switch_status;      /* 带宽切换状态 */
    oal_bool_enum_uint8                  en_csa_present_in_bcn;    /* Beacon帧中是否包含CSA IE */

    oal_uint8                            uc_start_chan_idx;
    oal_uint8                            uc_end_chan_idx;
    wlan_channel_bandwidth_enum_uint8    en_user_pref_bandwidth;

    /* VAP为STA时，特有成员
     *
     *  ---|--------|--------------------|-----------------|-----------
     *     0        3                    0                 0
     *     X        A                    B                 C
     *
     *  sta的信道切换可通过上图帮助理解, 数字为切换计数器，
     *  X->A A之前为未发生任务信道切换时,切换计数器为0
     *  从A->B时间段为sta等待切换状态: en_waiting_to_shift_channel为true
     *  从B->C为sta信道切换中,即等待ap加beacon状态: en_waiting_for_ap为true
     *  C-> 为sta收到了ap的beacon，标准信道切换结束
     *
     *  A点通常中收到csa ie(beacon/action...), B点通常为tbtt中断中切换计数器变为
     *  0或者csa ie中计数器为0，C点则为收到beacon
     *
     *  从A->C的过程中，会过滤重复收到的csa ie或者信道切换动作
     *
     */
   // oal_bool_enum_uint8                  en_bw_change;             /* STA是否需要进行带宽切换 */
    oal_uint8                            uc_new_channel;           /* 可以考虑跟上面合并 */
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth;         /* 可以考虑跟上面合并 */
    oal_uint8                            uc_new_ch_swt_cnt;        /* 可以考虑跟上面合并 */
    oal_bool_enum_uint8                  en_waiting_to_shift_channel;
    oal_bool_enum_uint8                  en_waiting_for_ap;
    oal_bool_enum_uint8                  en_channel_swt_cnt_zero;

    oal_bool_enum_uint8                  en_te_b;
    oal_uint8                            uc_ch_swt_cnt;
    oal_uint8                            uc_csa_rsv_cnt;
    oal_uint8                            auc_resv[1];
    oal_uint32                           ul_chan_report_for_te_a;
}mac_ch_switch_info_stru;

typedef struct
{
    oal_uint8   uc_mac_rate; /* MAC对应速率 */
    oal_uint8   uc_phy_rate; /* PHY对应速率 */
    oal_uint8   uc_mbps;     /* 速率 */
    oal_uint8   auc_resv[1];
}mac_data_rate_stru;

#if 0
/* add by  2014.6.13 增加工作模式通知信息结构体,待张炜整理配置命令使用场景后再继续开发改代码，暂时保留 */
typedef struct
{
    oal_bool_enum_uint8  en_include_opmode_notify_ie;     /* Beacon、关联请求帧中是否包含opmode_notify IE */
    oal_bool_enum_uint8  en_bf_rx_nss_change;             /* Beamforming的Rx Nss改变 */
    oal_uint8            uc_include_ie_count;             /* Beacon、关联请求帧中包含opmode_notify IE次数 */
    oal_uint8            auc_resv[1];
}mac_opmode_notify_info_stru;

#endif

typedef struct
{
    oal_uint8           uc_rs_nrates;   /* 速率个数 */
    oal_uint8           auc_resv[3];
    mac_data_rate_stru  ast_rs_rates[WLAN_RATE_MAXSIZE];
}mac_rateset_stru;

typedef struct
{
    oal_uint8         uc_br_rate_num;   /* 基本速率个数 */
    oal_uint8         uc_nbr_rate_num;  /* 非基本速率个数 */
    oal_uint8         uc_max_rate;      /* 最大基本速率 */
    oal_uint8         uc_min_rate;      /* 最小基本速率 */
    mac_rateset_stru  st_rate;
}mac_curr_rateset_stru;

/* wme参数 */
typedef struct
{
    oal_uint32    ul_aifsn;          /* AIFSN parameters */
    oal_uint32    ul_logcwmin;       /* cwmin in exponential form, 单位2^n -1 slot */
    oal_uint32    ul_logcwmax;       /* cwmax in exponential form, 单位2^n -1 slot */
    oal_uint32    ul_txop_limit;     /* txopLimit, us */
}mac_wme_param_stru;

/* MAC vap能力特性标识 */
typedef struct
{
    oal_uint32  bit_uapsd                          : 1,
                bit_txop_ps                        : 1,
                bit_wpa                            : 1,
                bit_wpa2                           : 1,
                bit_dsss_cck_mode_40mhz            : 1,                 /* 是否允许在40M上使用DSSS/CCK, 1-允许, 0-不允许 */
                bit_rifs_tx_on                     : 1,
                bit_tdls_prohibited                : 1,                 /* tdls全局禁用开关， 0-不关闭, 1-关闭 */
                bit_tdls_channel_switch_prohibited : 1,                 /* tdls信道切换全局禁用开关， 0-不关闭, 1-关闭 */
                bit_hide_ssid                      : 1,                 /* AP开启隐藏ssid,  0-关闭, 1-开启*/
                bit_wps                            : 1,                 /* AP WPS功能:0-关闭, 1-开启 */
                bit_11ac2g                         : 1,                 /* 2.4G下的11ac:0-关闭, 1-开启 */
                bit_keepalive                      : 1,                 /* vap KeepAlive功能开关: 0-关闭, 1-开启*/
                bit_smps                           : 2,                 /* vap 当前SMPS能力 */
                bit_dpd_enbale                     : 1,                 /* dpd是否开启 */
                bit_dpd_done                       : 1,                 /* dpd是否完成 */
                bit_11ntxbf                        : 1,                 /* 11n txbf能力 */
                bit_disable_2ght40                 : 1,                 /* 2ght40禁止位，1-禁止，0-不禁止 */
                bit_auto_dtim_enbale               : 1,                 /* 动态DTIM能力 */
                bit_resv                           : 13;
}mac_cap_flag_stru;

/* VAP收发包统计 */
typedef struct
{
    /* net_device用统计信息, net_device统计经过以太网的报文 */
    oal_uint32  ul_rx_packets_to_lan;               /* 接收流程到LAN的包数 */
    oal_uint32  ul_rx_bytes_to_lan;                 /* 接收流程到LAN的字节数 */
    oal_uint32  ul_rx_dropped_packets;              /* 接收流程中丢弃的包数 */
    oal_uint32  ul_rx_vap_non_up_dropped;           /* vap没有up丢弃的包的个数 */
    oal_uint32  ul_rx_dscr_error_dropped;           /* 描述符出错丢弃的包的个数 */
    oal_uint32  ul_rx_first_dscr_excp_dropped;      /* 描述符首包异常丢弃的包的个数 */
    oal_uint32  ul_rx_alg_filter_dropped;           /* 算法过滤丢弃的包的个数 */
    oal_uint32  ul_rx_feature_ap_dropped;           /* AP特性帧过滤丢包个数 */
    oal_uint32  ul_rx_null_frame_dropped;           /* 收到NULL帧的数目 */
    oal_uint32  ul_rx_transmit_addr_checked_dropped;/* 发送端地址过滤失败丢弃 */
    oal_uint32  ul_rx_dest_addr_checked_dropped;    /* 目的地址过滤失败丢弃 */
    oal_uint32  ul_rx_multicast_dropped;            /* 组播帧失败(netbuf copy失败)丢弃 */

    oal_uint32  ul_tx_packets_from_lan;             /* 发送流程LAN过来的包数 */
    oal_uint32  ul_tx_bytes_from_lan;               /* 发送流程LAN过来的字节数 */
    oal_uint32  ul_tx_dropped_packets;              /* 发送流程中丢弃的包数 */

    /* 其它报文统计信息 */

}mac_vap_stats_stru;
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
/* 黑名单 */
typedef struct
{
    oal_uint8                       auc_mac_addr[OAL_MAC_ADDR_LEN];       /* mac地址          */
    oal_uint8                       auc_reserved[2];                      /* 字节对齐         */
    oal_uint32                      ul_cfg_time;                          /* 加入黑名单的时间 */
    oal_uint32                      ul_aging_time;                        /* 老化时间         */
    oal_uint32                      ul_drop_counter;                      /* 报文丢弃统计     */
} mac_blacklist_stru;

/* 自动黑名单 */
typedef struct
{
    oal_uint8                       auc_mac_addr[OAL_MAC_ADDR_LEN];       /* mac地址  */
    oal_uint8                       auc_reserved[2];                      /* 字节对齐 */
    oal_uint32                      ul_cfg_time;                          /* 初始时间 */
    oal_uint32                      ul_asso_counter;                      /* 关联计数 */
} mac_autoblacklist_stru;

/* 自动黑名单信息 */
typedef struct
{
    oal_uint8                       uc_enabled;                             /* 使能标志 0:未使能  1:使能 */
    oal_uint8                       list_num;                               /* 有多少个自动黑名单        */
    oal_uint8                       auc_reserved[2];                        /* 字节对齐                  */
    oal_uint32                      ul_threshold;                           /* 门限                      */
    oal_uint32                      ul_reset_time;                          /* 重置时间                  */
    oal_uint32                      ul_aging_time;                          /* 老化时间                  */
    mac_autoblacklist_stru          ast_autoblack_list[WLAN_BLACKLIST_MAX]; /* 自动黑名单表              */
} mac_autoblacklist_info_stru;


/* 黑白名单信息 */
typedef struct
{
    oal_uint8                          uc_mode;                                  /* 黑白名单模式   */
    oal_uint8                          uc_list_num;                              /* 名单数         */
    oal_uint8                          auc_reserved[2];                          /* 字节对齐       */
    mac_autoblacklist_info_stru        st_autoblacklist_info;                    /* 自动黑名单信息 */
    mac_blacklist_stru                 ast_black_list[WLAN_BLACKLIST_MAX];       /* 有效黑白名单表 */
} mac_blacklist_info_stru;

/* 隔离信息 */
typedef struct
{
    oal_uint8                           uc_type;                                  /* 隔离类型   */
    oal_uint8                           uc_mode;                                  /* 隔离模式bit0：广播隔离 bit1：组播隔离 bit2：单播隔离   */
    oal_uint8                           uc_forward;                               /* forwarding方式 */
    oal_uint8                           auc_reserved[1];                          /* 字节对齐       */
    oal_uint32                          ul_counter_bcast;                         /* 广播隔离计数器 */
    oal_uint32                          ul_counter_mcast;                         /* 组播隔离计数器 */
    oal_uint32                          ul_counter_ucast;                         /* 单播隔离计数器 */
} mac_isolation_info_stru;
#endif  /* _PRE_WLAN_FEATURE_CUSTOM_SECURITY */
typedef struct
{
    oal_uint16                          us_user_idx;
    wlan_protocol_enum_uint8            en_avail_protocol_mode; /* 用户协议模式 */
    wlan_protocol_enum_uint8            en_cur_protocol_mode;
    wlan_protocol_enum_uint8            en_protocol_mode;
    oal_uint8                           auc_resv[3];
}mac_h2d_user_protocol_stru;

typedef struct
{
    oal_uint16                          us_user_idx;
    oal_uint8                           uc_arg1;
    oal_uint8                           uc_arg2;

    /* 协议模式信息 */
    wlan_protocol_enum_uint8            en_cur_protocol_mode;
    wlan_protocol_enum_uint8            en_protocol_mode;
    oal_uint8                           en_avail_protocol_mode; /* 用户和VAP协议模式交集, 供算法调用 */

    wlan_bw_cap_enum_uint8              en_bandwidth_cap;       /* 用户带宽能力信息 */
    wlan_bw_cap_enum_uint8              en_avail_bandwidth;     /* 用户和VAP带宽能力交集,供算法调用 */
    wlan_bw_cap_enum_uint8              en_cur_bandwidth;       /* 默认值与en_avail_bandwidth相同,供算法调用修改 */

    oal_bool_enum_uint8                 en_user_pmf;
    mac_user_asoc_state_enum_uint8      en_user_asoc_state;     /* 用户关联状态 */
    oal_uint8                           uc_drop_ncw;            /* notify channel width action帧上报开关 */
#ifdef _PRE_WLAN_FEATURE_HISTREAM
    mac_histream_stru                   st_histream_info;
#endif //_PRE_WLAN_FEATURE_HISTREAM
}mac_h2d_usr_info_stru;


typedef struct
{
    mac_user_cap_info_stru              st_user_cap_info;                   /* 用户能力信息 */
    oal_uint16                          us_user_idx;
    oal_uint8                           auc_resv[2];
}mac_h2d_usr_cap_stru;


/* 问题单: hamc向dmac同步速率集合信息时，
   使用的结构体大小超出了事件内存的大小，导致事件同步有可能失败。
   单独定义结构体mac_h2d_user_rate_info_stru,保证mac_h2d_usr_info_stru不超过限制 */
typedef struct
{
    oal_uint16                          us_user_idx;

    /* vht速率集信息 */
    mac_vht_hdl_stru                    st_vht_hdl;

    /* ht速率集信息 */
    mac_user_ht_hdl_stru                 st_ht_hdl;

    /* legacy速率集信息 */
    oal_uint8                           uc_avail_rs_nrates;
    oal_uint8                           auc_avail_rs_rates[WLAN_RATE_MAXSIZE];

    wlan_protocol_enum_uint8            en_protocol_mode;                            /* 用户协议模式 */
}mac_h2d_usr_rate_info_stru;


typedef struct
{
    oal_uint16                         us_sta_aid;
    oal_uint8                          uc_uapsd_cap;
    oal_uint8                          auc_resv[1];
}mac_h2d_vap_info_stru;

typedef struct
{
    oal_uint16                          us_user_idx;
    wlan_protocol_enum_uint8            en_avail_protocol_mode; /* 用户协议模式 */
    wlan_bw_cap_enum_uint8              en_bandwidth_cap;       /* 用户带宽能力信息 */
    wlan_bw_cap_enum_uint8              en_avail_bandwidth;     /* 用户和VAP带宽能力交集,供算法调用 */
    wlan_bw_cap_enum_uint8              en_cur_bandwidth;       /* 默认值与en_avail_bandwidth相同,供算法调用修改 */
    oal_uint8                           auc_rsv[2];
}mac_h2d_user_bandwidth_stru;


typedef struct
{
    oal_uint16                          us_user_idx;
    mac_user_asoc_state_enum_uint8      en_asoc_state;
    oal_uint8                           uc_rsv[1];
}mac_h2d_user_asoc_state_stru;


typedef struct
{
    oal_uint8 auc_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8 auc_pmkid[WLAN_PMKID_LEN];
    oal_uint8 auc_resv0[2];
} mac_pmkid_info_stu;

typedef struct
{
    oal_uint8       uc_num_elems;
    oal_uint8       auc_resv0[3];
    mac_pmkid_info_stu ast_elem[WLAN_PMKID_CACHE_SIZE];
} mac_pmkid_cache_stru;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
typedef struct
{
    oal_device_freq_type_enum_uint8                         uc_device_freq_type;
    oal_uint8                          uc_rsv[3];
}config_device_freq_h2d_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
typedef struct
{
    oal_uint8   bit_imbf_receive_cap            :   1,  /*隐式TxBf接收能力*/
                bit_exp_comp_txbf_cap           :   1, /*应用压缩矩阵进行TxBf的能力*/
                bit_min_grouping                :   2,  /*0=不分组，1=1,2分组，2=1,4分组，3=1,2,4分组*/
                bit_csi_bfee_max_rows           :   2,  /*bfer支持的来自bfee的CSI显示反馈的最大行数*/
                bit_channel_est_cap             :   2;  /*信道估计的能力，0=1空时流，依次递增*/
    oal_uint8   auc_resv0[3];
}mac_vap_txbf_add_stru;
#endif

typedef struct
{
    /*word 0*/
    wlan_prot_mode_enum_uint8           en_protection_mode;                              /* 保护模式 */
    oal_uint8                           uc_obss_non_erp_aging_cnt;                       /*指示OBSS中non erp 站点的老化时间*/
    oal_uint8                           uc_obss_non_ht_aging_cnt;                        /*指示OBSS中non ht 站点的老化时间*/
    oal_uint8                           bit_auto_protection        : 1;                  /*指示保护策略是否开启，OAL_SWITCH_ON 打开， OAL_SWITCH_OFF 关闭*/
    oal_uint8                           bit_obss_non_erp_present   : 1;                  /*指示obss中是否存在non ERP的站点*/
    oal_uint8                           bit_obss_non_ht_present    : 1;                  /*指示obss中是否存在non HT的站点*/
    oal_uint8                           bit_rts_cts_protect_mode   : 1;                  /*指rts_cts 保护机制是否打开, OAL_SWITCH_ON 打开， OAL_SWITCH_OFF 关闭*/
    oal_uint8                           bit_lsig_txop_protect_mode : 1;                  /*指示L-SIG protect是否打开, OAL_SWITCH_ON 打开， OAL_SWITCH_OFF 关闭*/
    oal_uint8                           bit_reserved               : 3;

    /*word 1*/
    oal_uint8                           uc_sta_no_short_slot_num;                       /* 不支持short slot的STA个数*/
    oal_uint8                           uc_sta_no_short_preamble_num;                   /* 不支持short preamble的STA个数*/
    oal_uint8                           uc_sta_non_erp_num;                             /* 不支持ERP的STA个数*/
    oal_uint8                           uc_sta_non_ht_num;                              /* 不支持HT的STA个数 */
    /*word 2*/
    oal_uint8                           uc_sta_non_gf_num;                              /* 支持ERP/HT,不支持GF的STA个数 */
    oal_uint8                           uc_sta_20M_only_num;                            /* 只支持20M 频段的STA个数*/
    oal_uint8                           uc_sta_no_40dsss_cck_num;                       /* 不用40M DSSS-CCK STA个数  */
    oal_uint8                           uc_sta_no_lsig_txop_num;                        /* 不支持L-SIG TXOP Protection STA个数 */
} mac_protection_stru;

/*用于同步保护相关的参数*/
typedef struct
{
    oal_uint32             ul_sync_mask;

    mac_user_cap_info_stru st_user_cap_info;
    oal_uint16             us_user_idx;
    oal_uint8              auc_resv[2];

    wlan_mib_ht_protection_enum_uint8   en_dot11HTProtection;
    oal_bool_enum_uint8 en_dot11RIFSMode;
    oal_bool_enum_uint8 en_dot11LSIGTXOPFullProtectionActivated;
    oal_bool_enum_uint8 en_dot11NonGFEntitiesPresent;

    mac_protection_stru st_protection;
}mac_h2d_protection_stru;

typedef struct
{
    oal_uint8                          *puc_ie;                                         /* APP 信息元素 */
    oal_uint32                          ul_ie_len;                                      /* APP 信息元素长度 */
    oal_uint32                          ul_ie_max_len;                                  /* APP 信息元素最大长度 */
} mac_app_ie_stru;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
typedef struct
{
    oal_uint8                 auc_oma[WLAN_MAC_ADDR_LEN];                            /* proxysta的 OMA地址 */
    oal_bool_enum_uint8       en_is_proxysta;                                        /* 在Proxy STA特性下，只要是sta，均为true */
    oal_bool_enum_uint8       en_is_main_proxysta;                                   /* 是否为普通的sta0，如果是的，则为true，vap_id为4，不是则为16~31 */
    oal_uint8                 uc_lut_idx;                                            /* 如果为Proxy STA，则lut_idx为16~31,add vap的时候从这里获取 */
    oal_uint8                 auc_res[3];
}mac_vap_proxysta_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    mac_ether_header_stru               st_eth_hdr;
    oal_uint8                           auc_rsv[2];
    oal_uint16                          us_proxy_num; /* 记录处理过帧的条数 */
    oal_uint16                          us_type;
    oal_err_code_enum_uint32            en_rst;
}mac_vap_proxyarp_debug_stru;
#endif

typedef struct
{
    oal_dlist_head_stru                 ast_ipv4_head[MAC_VAP_USER_HASH_MAX_VALUE];
    oal_dlist_head_stru                 ast_ipv6_head[MAC_VAP_USER_HASH_MAX_VALUE];
    oal_bool_enum_uint8                 en_is_proxyarp;
    oal_uint8                           uc_ipv4_num;        /* 记录ipv4的条数 */
    oal_uint8                           uc_ipv6_num;        /* 记录ipv6的条数 */
    oal_bool_enum_uint8                 en_2wlan;

#ifdef _PRE_DEBUG_MODE
    /* 调试使用,最多记录MAC_VAP_USER_HASH_MAX_VALUE条记录 */
    oal_uint16                          us_idx_cur; /* 循环指向当前记录的位置 */
    oal_uint8                           auc_rsv[2];
    mac_vap_proxyarp_debug_stru         ast_vap_proxyarp_dbg[MAC_VAP_USER_HASH_MAX_VALUE];
#endif
}mac_vap_proxyarp_stru;
#endif


/* 协议参数 对应cfgid: WLAN_CFGID_MODE */
typedef struct
{
    wlan_protocol_enum_uint8            en_protocol;    /* 协议 */
    wlan_channel_band_enum_uint8        en_band;        /* 频带 */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* 带宽 */
    oal_uint8                           en_channel_idx; /* 主20M信道号 */
}mac_cfg_mode_param_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef oam_stats_vap_stat_stru mac_vap_dft_stats_stru;

typedef struct
{
    mac_vap_dft_stats_stru             *pst_vap_dft_stats;
    frw_timeout_stru                    st_vap_dft_timer;
    oal_uint32                          ul_flg;             /* 开始统计标志 */


}mac_vap_dft_stru;
#endif


#ifdef _PRE_WLAN_FEATURE_STA_PM
/* STA UAPSD 配置命令 */
typedef  struct
{
    oal_uint8       uc_max_sp_len;
    oal_uint8       uc_delivery_enabled[WLAN_WME_AC_BUTT];
    oal_uint8       uc_trigger_enabled[WLAN_WME_AC_BUTT];
}mac_cfg_uapsd_sta_stru;

/* Power save modes specified by the user */
typedef enum
{
    NO_POWERSAVE     = 0,
    MIN_FAST_PS      = 1,
    MAX_FAST_PS      = 2,
    MIN_PSPOLL_PS    = 3,
    MAX_PSPOLL_PS    = 4,
    NUM_PS_MODE      = 5
} ps_user_mode_enum;

#endif

#ifdef _PRE_WLAN_FEATURE_TXOPPS
/* STA txopps aid同步 */
typedef  struct
{
    oal_uint16                           us_partial_aid;
    oal_uint8                            en_protocol;
    oal_uint8                            uc_resv;
}mac_cfg_txop_sta_stru;
#endif

#define MAC_VAP_INVAILD    (0x0) /*0为vap无效*/
#define MAC_VAP_VAILD      (0x2b)

/* VAP的数据结构 */
typedef struct
{
    /* VAP为AP或者STA均有成员 */
    /* word0~word1 */
    oal_uint8                           uc_vap_id;                                      /* vap ID   *//* 即资源池索引值 */
    oal_uint8                           uc_device_id;                                   /* 设备ID   */
    oal_uint8                           uc_chip_id;                                     /* chip ID  */
    wlan_vap_mode_enum_uint8            en_vap_mode;                                    /* vap模式  */
    oal_uint32                          ul_core_id;

    /* word2~word3 */
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];                   /* BSSID，非MAC地址，MAC地址是mib中的auc_dot11StationID  */
    mac_vap_state_enum_uint8            en_vap_state;                                   /* VAP状态 */
    wlan_protocol_enum_uint8            en_protocol;                                    /* 工作的协议模式 */

    /* word4~word5 */
    mac_channel_stru                    st_channel;                                     /* vap所在的信道 */
    mac_ch_switch_info_stru             st_ch_switch_info;

    /* word6 */
    oal_uint8                           bit_has_user_bw_limit   :   1;                  /* 该vap是否存在user限速 */
    oal_uint8                           bit_vap_bw_limit        :   1;                  /* 该vap是否已限速 */
    oal_uint8                           bit_voice_aggr          :   1;                  /* 该vap是否针对VO业务支持聚合 */
    oal_uint8                           bit_resv                :   5;

    oal_uint8                           uc_tx_power;                                    /* 传输功率, 单位dBm */
    oal_uint8                           uc_channel_utilization;                         /* 当前信道利用率 */
    oal_uint8                           uc_wmm_params_update_count;                     /* 初始为0，AP模式下，每跟新一次wmm参数这个变量加1,在beacon帧和assoc rsp中会填写，4bit，不能超过15；STA模式下解析帧并更新这个值 */

    /* word7 */
    oal_uint16                          us_user_nums;                                   /* VAP下已挂接的用户个数 */
    oal_uint16                          us_multi_user_idx;                              /* 组播用户ID */
    oal_uint8                           auc_cache_user_mac_addr[WLAN_MAC_ADDR_LEN];     /* cache user对应的MAC地址 */
    oal_uint16                          us_cache_user_id;                               /* cache user对应的userID*/
    oal_dlist_head_stru                 ast_user_hash[MAC_VAP_USER_HASH_MAX_VALUE];     /* hash数组,使用HASH结构内的DLIST */
    oal_dlist_head_stru                 st_mac_user_list_head;                          /* 关联用户节点双向链表,使用USER结构内的DLIST */

    /* word8 */
    /* add by   */
    wlan_nss_enum_uint8                 en_vap_rx_nss;                                  /* vap的接收空间流个数 */

    /*vap为静态资源，标记VAP有没有被申请。,
      DMAC OFFLOAD模式VAP被删除后过滤缓冲的帧*/
    oal_uint8                           uc_init_flag;
    oal_uint8                           auc_resv1[2];
#ifdef _PRE_WLAN_FEATURE_HISTREAM
    mac_histream_stru                   st_histream_info;
#endif //_PRE_WLAN_FEATURE_HISTREAM

    /* 加密相关 */
    /*结构体需要保证4字节对齐*/
    //mac_key_mgmt_stru                   st_key_mgmt;                                    /*用于保存自身ptk gtk等密钥信息，在AP/STA模式下均需要使用*/

    mac_cap_flag_stru                   st_cap_flag;                                    /* vap能力特性标识 */
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_vap_stats_stru                  st_vap_stats;                                   /* VAP收发包统计 */
#endif
    wlan_mib_ieee802dot11_stru         *pst_mib_info;                                   /* mib信息(当时配置vap时，可以直接将指针值为NULL，节省空间)  */

    mac_curr_rateset_stru               st_curr_sup_rates;                              /* 当前支持的速率集 */
    mac_curr_rateset_stru               ast_sta_sup_rates_ie[WLAN_BAND_BUTT];           /* 只在sta全信道扫描时使用，用于填写支持的速率集ie，分2.4和5G */


#ifdef _PRE_WLAN_DFT_STAT
    /* user 链表维测 */
    oal_uint32          ul_dlist_cnt;     /* dlsit统计 */
    oal_uint32          ul_hash_cnt;     /* hash个数统计 */
#if 0
    mac_vap_dft_stru                    st_vap_dft;                                     /* vap吞吐统计信息，维测用 */
#endif

#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_vap_txbf_add_stru               st_txbf_add_cap;
#endif

    /* VAP为AP或者STA均有成员 定义结束*/


    /* VAP为AP特有成员， 定义开始*/
    mac_protection_stru                 st_protection;                                   /*与保护相关变量*/
    mac_app_ie_stru                     ast_app_ie[OAL_APP_IE_NUM];
    /* VAP为AP特定成员， 定义结束*/

    /* VAP为STA特有成员， 定义开始*/

    oal_uint16                          us_sta_aid;                                     /* VAP为STA模式时保存AP分配给STA的AID(从响应帧获取),取值范围1~2007; VAP为AP模式时，不用此成员变量 */
    oal_uint8                           uc_assoc_vap_id;                                /* VAP为STA模式时保存user(ap)的资源池索引；VAP为AP模式时，不用此成员变量 */
    oal_uint8                           uc_wmm_cap;                                     /* 保存与STA关联的AP是否支持wmm能力信息 */

    oal_uint8                           uc_uapsd_cap;                                   /* 保存与STA关联的AP是否支持uapsd能力信息 */
    oal_uint16                          us_assoc_user_cap_info;                         /* sta要关联的用户的能力信息 */
    oal_uint8                           bit_ap_11ntxbf : 1,                             /* sta要关联的用户的11n txbf能力信息 */
                                        bit_resv4      : 7;


#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_proxysta_stru               st_vap_proxysta;                                /* Proxy STA 特性相关结构体 */
    oal_dlist_head_stru                 st_entry;                                       /* 相同hash值的vap链表 */
    oal_uint16                          us_non_qos_seq_num;                             /* 记录该Proxy STA保存的接收来自Root Ap的前一个非QOS帧的seq num */
    oal_uint8                           auc_resv4[2];
    oal_uint16                          aus_last_qos_seq_num[WLAN_TID_MAX_NUM];         /* 记录该Proxy STA保存的接收来自Root Ap的前一个QoS帧的seq num */
#endif
    /* VAP为STA特定成员， 定义结束*/

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    mac_vap_proxyarp_stru              *pst_vap_proxyarp;
#endif

//#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* 常发测试使用 */
    oal_uint8                           bit_al_tx_flag  :1;                             /* 常发标志 */
    oal_uint8                           bit_payload_flag:2;                             /* payload内容:0:全0  1:全1  2:random */
    oal_uint8                           bit_first_run:1;                                /* 常发关闭再次打开标志 */
    oal_uint8                           bit_reserved:4;
    //oal_uint8                           auc_resv5[3];
//#endif

//#ifdef _PRE_WLAN_FEATURE_P2P
    wlan_p2p_mode_enum_uint8            en_p2p_mode;                                    /* 0:非P2P设备; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
    oal_uint8                           uc_p2p_gocl_hal_vap_id;                         /* p2p go / cl的hal vap id */
    oal_uint8                           uc_p2p_listen_channel;                          /* P2P Listen channel */
    //oal_uint8                           auc_resv6[1];
//#endif    /* _PRE_WLAN_FEATURE_P2P */

#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_cfg_uapsd_sta_stru              st_sta_uapsd_cfg;     /* UAPSD的配置信息 */
#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    oal_bool_enum_uint8                 en_user_pmf_cap;      /* STA侧在未创建user前，存储目标user的pmf使能信息 */
#endif

    oal_spin_lock_stru                  st_cache_user_lock;                        /* cache_user lock */
}mac_vap_stru;

/* cfg id对应的get set函数 */
typedef struct
{
    wlan_cfgid_enum_uint16          en_cfgid;
    oal_uint8                       auc_resv[2];    /* 字节对齐 */
    oal_uint32                      (*p_get_func)(mac_vap_stru *pst_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
    oal_uint32                      (*p_set_func)(mac_vap_stru *pst_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
}mac_cfgid_stru;


/* cfg id对应的参数结构体 */
/* 创建VAP参数结构体, 对应cfgid: WLAN_CFGID_ADD_VAP */
typedef struct
{
    wlan_vap_mode_enum_uint8  en_vap_mode;
    oal_uint8                 uc_cfg_vap_indx;
    oal_uint16                us_muti_user_id;          /* 添加vap 对应的muti user index */

    oal_uint8                 uc_vap_id;                /* 需要添加的vap id */
    wlan_p2p_mode_enum_uint8  en_p2p_mode;              /* 0:非P2P设备; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_bool_enum_uint8       en_is_proxysta;
    oal_bool_enum_uint8       en_is_main_proxysta;
#else
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    oal_uint8                 bit_11ac2g_enable         :1;
    oal_uint8                 bit_disable_capab_2ght40  :1;
    oal_uint8                 bit_reserve               :6;
    oal_uint8                 auc_resv0[1];
#else
    oal_uint8                 auc_resv0[2];
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_UAPSD
    oal_uint8                 bit_uapsd_enable    :1;
    oal_uint8                 bit_reserve1        :7;
    oal_uint8                 auc_resv1[3];
#endif
    oal_net_device_stru      *pst_net_dev;
}mac_cfg_add_vap_param_stru;
typedef mac_cfg_add_vap_param_stru mac_cfg_del_vap_param_stru;


/* 启用VAP参数结构体 对应cfgid: WLAN_CFGID_START_VAP */
typedef struct
{
    oal_bool_enum_uint8         en_mgmt_rate_init_flag;              /* start vap时候，管理帧速率是否需要初始化 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8            uc_protocol;
    oal_uint8            uc_band;
    oal_uint8            uc_bandwidth;
#else
    oal_uint8            auc_resv1[3];
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
    wlan_p2p_mode_enum_uint8   en_p2p_mode;
    oal_uint8                  auc_resv2[3];
#endif
    oal_net_device_stru       *pst_net_dev;     /* 此成员仅供Host(WAL&HMAC)使用，Device侧(DMAC&ALG&HAL层)不使用 */
}mac_cfg_start_vap_param_stru;
typedef mac_cfg_start_vap_param_stru mac_cfg_down_vap_param_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* CFG VAP h2d */
typedef struct
{
    oal_net_device_stru        *pst_net_dev;
}mac_cfg_vap_h2d_stru;
#endif


/* 设置mac地址参数 对应cfgid: WLAN_CFGID_STATION_ID */
typedef struct
{
    oal_uint8                   auc_station_id[WLAN_MAC_ADDR_LEN];
    wlan_p2p_mode_enum_uint8    en_p2p_mode;
    oal_uint8                   auc_resv[1];
}mac_cfg_staion_id_param_stru;

/* SSID参数 对应cfgid: WLAN_CFGID_SSID */
typedef struct
{
    oal_uint8   uc_ssid_len;
    oal_uint8   auc_resv[2];
    oal_int8    ac_ssid[WLAN_SSID_MAX_LEN];
}mac_cfg_ssid_param_stru;

/* HOSTAPD 设置工作频段，信道和带宽参数 */
typedef struct
{
    wlan_channel_band_enum_uint8        en_band;        /* 频带 */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* 带宽 */
    oal_uint8                           uc_channel;     /* 信道编号 */
    oal_uint8                           uc_hilink_flag;    /* hilink标志 */
}mac_cfg_channel_param_stru;

/* HOSTAPD 设置wiphy 物理设备信息，包括RTS 门限值，分片报文门限值 */
typedef struct
{
    oal_uint8  uc_frag_threshold_changed;
    oal_uint8  uc_rts_threshold_changed;
    oal_uint8  uc_rsv[2];
    oal_uint32 ul_frag_threshold;
    oal_uint32 ul_rts_threshold;
}mac_cfg_wiphy_param_stru;

/* HOSTAPD 设置 Beacon 信息 */
typedef struct
{
    oal_int32                l_interval;                            /* beacon interval */
    oal_int32                l_dtim_period;                         /* DTIM period     */
    oal_bool_enum_uint8      en_privacy;
    oal_uint8                uc_crypto_mode;                              /* WPA/WPA2 */
    oal_uint8                uc_group_crypto;                             /* 组播密钥类型 */
    oal_bool_enum_uint8      uc_hidden_ssid;
    oal_uint8                auc_auth_type[MAC_AUTHENTICATION_SUITE_NUM];  /* akm 类型 */
    oal_uint8                auc_pairwise_crypto_wpa[MAC_PAIRWISE_CIPHER_SUITES_NUM];
    oal_uint8                auc_pairwise_crypto_wpa2[MAC_PAIRWISE_CIPHER_SUITES_NUM];
    oal_uint16               us_rsn_capability;
    oal_bool_enum_uint8      en_shortgi_20;
    oal_bool_enum_uint8      en_shortgi_40;
    oal_bool_enum_uint8      en_shortgi_80;
    wlan_protocol_enum_uint8 en_protocol;

    oal_uint8                       uc_smps_mode;
    mac_beacon_operation_type_uint8 en_operation_type;
    oal_uint8                auc_resv1[2];
}mac_beacon_param_stru;


/* 设置log模块开关的配置命令参数 */
typedef struct
{
    oam_module_id_enum_uint16           en_mod_id;      /* 对应的模块id */
    oal_bool_enum_uint8                 en_switch;      /* 对应的开关设置 */
    oal_uint8                           auc_resv[1];
}mac_cfg_log_module_param_stru;

/* 用户相关的配置命令参数 */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_bool_enum_uint8     en_ht_cap;                          /* ht能力 */
    oal_uint8               auc_resv[3];
    oal_uint16              us_user_idx;                        /* 用户索引 */
}mac_cfg_add_user_param_stru;

typedef mac_cfg_add_user_param_stru mac_cfg_del_user_param_stru;

/* 接收帧的FCS统计信息 */
typedef struct
{
    oal_uint32  ul_data_op;         /* 数据操作模式:<0>保留,<1>清除 */
    oal_uint32  ul_print_info;      /* 打印数据内容:<0>所有数据 <1>总帧数 <2>self fcs correct, <3>other fcs correct, <4>fcs error  */
}mac_cfg_rx_fcs_info_stru;

/* 剔除用户配置命令参数 */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint16              us_reason_code;                     /* 去关联 reason code */
}mac_cfg_kick_user_param_stru;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/* 设置Proxy STA OMA配置命令参数 */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* Proxy STA OMA地址 */
    oal_uint8               auc_resv[2];
}mac_cfg_set_oma_param_stru;

#endif

/* 暂停tid配置命令参数 */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               uc_tid;
    oal_uint8               uc_is_paused;
}mac_cfg_pause_tid_param_stru;

/* 配置用户是否为vip */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               uc_vip_flag;
}mac_cfg_user_vip_param_stru;

/* 暂停tid配置命令参数 */
typedef struct
{
    oal_uint8               uc_aggr_tx_on;
    oal_uint8               uc_tid;
    oal_uint16              us_packet_len;
}mac_cfg_ampdu_tx_on_param_stru;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/* 设置host某个队列的每次调度报文个数，low_waterline, high_waterline */
typedef struct
{
    oal_uint8               uc_queue_type;
    oal_uint8               auc_resv[1];
    oal_uint16              us_burst_limit;
    oal_uint16              us_low_waterline;
    oal_uint16              us_high_waterline;
}mac_cfg_flowctl_param_stru;
#endif

/* 使能qempty命令 */
typedef struct
{
    oal_uint8   uc_is_on;
    oal_uint8   auc_resv[3];
}mac_cfg_resume_qempty_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/* 使能rx intr fifo命令 */
typedef struct
{
    oal_uint8   uc_is_on;
    oal_uint8   auc_resv[3];
}mac_cfg_resume_rx_intr_fifo_stru;
#endif

/* 发送mpdu/ampdu命令参数  */
typedef struct
{
    oal_uint8               uc_tid;
    oal_uint8               uc_packet_num;
    oal_uint16              us_packet_len;
    oal_uint8               auc_ra_mac[OAL_MAC_ADDR_LEN];
}mac_cfg_mpdu_ampdu_tx_param_stru;
/* AMPDU相关的配置命令参数 */
typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* 用户的MAC ADDR */
    oal_uint8                       uc_tidno;                           /* 对应的tid号 */
    oal_uint8                       auc_reserve[1];                      /* 确认策略 */
}mac_cfg_ampdu_start_param_stru;

typedef mac_cfg_ampdu_start_param_stru mac_cfg_ampdu_end_param_stru;

/* BA会话相关的配置命令参数 */
typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* 用户的MAC ADDR */
    oal_uint8                       uc_tidno;                           /* 对应的tid号 */
    mac_ba_policy_enum_uint8        en_ba_policy;                       /* BA确认策略 */
    oal_uint16                      us_buff_size;                       /* BA窗口的大小 */
    oal_uint16                      us_timeout;                         /* BA会话的超时时间 */
}mac_cfg_addba_req_param_stru;

typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* 用户的MAC ADDR */
    oal_uint8                       uc_tidno;                           /* 对应的tid号 */
    mac_delba_initiator_enum_uint8  en_direction;                       /* 删除ba会话的发起端 */
    oal_uint8                       auc_reserve[1];                     /* 删除原因 */
}mac_cfg_delba_req_param_stru;

typedef struct
{
    oal_uint8                           auc_mac_addr[6];
    oal_uint8                           uc_amsdu_max_num;   /* amsdu最大个数 */
    oal_uint8                           auc_reserve[3];
    oal_uint16                          us_amsdu_max_size;  /* amsdu最大长度 */

}mac_cfg_amsdu_start_param_stru;

/* 设置用户配置参数 */
typedef struct
{
    oal_uint8                               uc_function_index;
    oal_uint8                               auc_reserve[2];
    mac_vap_config_dscr_frame_type_uint8    en_type;       /* 配置的帧类型 */
    oal_int32                               l_value;
}mac_cfg_set_dscr_param_stru;

typedef struct
{
    mac_vap_stru                *pst_mac_vap;
    oal_int8                     pc_param[4];      /* 查询或配置信息 */
}mac_cfg_event_stru;

/* non-HT协议模式下速率配置结构体 */
typedef struct
{
    wlan_legacy_rate_value_enum_uint8       en_rate;            /* 速率值 */
    wlan_phy_protocol_enum_uint8            en_protocol_mode;   /* 对应的协议 */
    oal_uint8                               auc_reserve[2];     /* 保留 */
}mac_cfg_non_ht_rate_stru;

/* 配置发送描述符内部元素结构体 */
typedef enum
{
    RF_PAYLOAD_ALL_ZERO = 0,
    RF_PAYLOAD_ALL_ONE,
    RF_PAYLOAD_RAND,
    RF_PAYLOAD_BUTT
}mac_rf_payload_enum;
typedef oal_uint8 mac_rf_payload_enum_uint8;

typedef struct
{
    oal_uint8                        uc_param;      /* 查询或配置信息 */
    wlan_phy_protocol_enum_uint8     en_protocol_mode;
    mac_rf_payload_enum_uint8        en_payload_flag;
    wlan_tx_ack_policy_enum_uint8    en_ack_policy;
    oal_uint32                       ul_payload_len;
}mac_cfg_tx_comp_stru;

typedef struct
{
    oal_uint8                   uc_offset_addr_a;
    oal_uint8                   uc_offset_addr_b;
    oal_uint16                  us_delta_gain;
}mac_cfg_dbb_scaling_stru;


/* 频偏较正命令格式 */
typedef struct
{
    oal_uint16                  us_idx;             /* 全局数组索引值 */
    oal_uint16                  us_chn;             /* 配置信道 */
    oal_int16                   as_corr_data[8];     /* 校正数据 */
}mac_cfg_freq_skew_stru;

/* wfa edca参数配置 */
typedef struct
{
    oal_bool_enum_uint8             en_switch;      /* 开关 */
    wlan_wme_ac_type_enum_uint8     en_ac;          /* AC */
    oal_uint16                      us_val;         /* 数据 */
}mac_edca_cfg_stru;

/* PPM调整命令格式 */
typedef struct
{
    oal_int8                     c_ppm_val;         /* PPM差值 */
    oal_uint8                    uc_clock_freq;     /* 时钟频率 */
    oal_uint8                    uc_resv[1];
}mac_cfg_adjust_ppm_stru;

/* 用户信息相关的配置命令参数 */
typedef struct
{
    oal_uint16              us_user_idx;                        /* 用户索引 */
    oal_uint8               auc_reserve[2];

}mac_cfg_user_info_param_stru;

/* 管制域配置命令结构体 */
typedef struct
{
    oal_void *p_mac_regdom;

}mac_cfg_country_stru;

/* 管制域最大发送功率配置 */
typedef struct
{
    oal_uint8 uc_pwr;
    oal_uint8 en_exceed_reg;
    oal_uint8 auc_resv[2];
}mac_cfg_regdomain_max_pwr_stru;


/* 获取当前管制域国家码字符配置命令结构体 */
typedef struct
{
    oal_int8    ac_country[3];
    oal_uint8   auc_resv[1];
}mac_cfg_get_country_stru;

/* query消息格式:2字节WID x N */
typedef struct
{
    wlan_tidno_enum_uint8  en_tid;
    oal_uint8              uc_resv[3];
}mac_cfg_get_tid_stru;


/* 以下为解析内核配置参数转化为驱动内部参数下发的结构体*/

/* 解析内核配置的扫描参数后，下发给驱动的扫描参数 */
typedef struct
{
    oal_ssids_stru              st_ssids[WLAN_SCAN_REQ_MAX_SSID];
    oal_int32                   l_ssid_num;

    const oal_uint8            *puc_ie;
    oal_uint32                  ul_ie_len;

    oal_scan_enum_uint8         en_scan_type;
    oal_uint8                   uc_num_channels_2G;
    oal_uint8                   uc_num_channels_5G;
    oal_uint8                   auc_arry[1];

    oal_uint32                  *pul_channels_2G;
    oal_uint32                  *pul_channels_5G;

    /* WLAN/P2P 特性情况下，p2p0 和p2p-p2p0 cl 扫描时候，需要使用不同设备，增加bit_is_p2p0_scan来区分 */
    oal_uint8                    bit_is_p2p0_scan : 1;   /* 是否为p2p0 发起扫描 */
    oal_uint8                    bit_rsv          : 7;   /* 保留位 */
    oal_uint8                    auc_rsv[3];             /* 保留位 */
}mac_cfg80211_scan_param_stru;


typedef struct
{
    mac_cfg80211_scan_param_stru  *pst_mac_cfg80211_scan_param;
}mac_cfg80211_scan_param_pst_stru;

/* 解析内核配置的connect参数后，下发给驱动的connect参数 */
typedef struct
{
    oal_uint8               wpa_versions;
    oal_uint8               cipher_group;
    oal_uint8               n_ciphers_pairwise;
    oal_uint8               ciphers_pairwise[OAL_NL80211_MAX_NR_CIPHER_SUITES];
    oal_uint8               n_akm_suites;
    oal_uint8               akm_suites[OAL_NL80211_MAX_NR_AKM_SUITES];

    oal_bool_enum_uint8     control_port;
}mac_cfg80211_crypto_settings_stru;

/**
 * enum nl80211_mfp - Management frame protection state
 * @NL80211_MFP_NO: Management frame protection not used
 * @NL80211_MFP_REQUIRED: Management frame protection required
 */

typedef enum
{
    MAC_NL80211_MFP_NO,
    MAC_NL80211_MFP_REQUIRED,

    MAC_NL80211_MFP_BUTT
}mac_nl80211_mfp_enum;
typedef oal_uint8 mac_nl80211_mfp_enum_uint8;



typedef struct
{
    oal_uint8                           uc_channel;              /* ap所在信道编号，eg 1,2,11,36,40... */
    oal_uint8                           uc_ssid_len;            /* SSID 长度 */
    mac_nl80211_mfp_enum_uint8          en_mfp;
    oal_uint8                           uc_wapi;

    oal_uint8                          *puc_ie;
    oal_uint8                          *puc_ssid;               /* 期望关联的AP SSID  */
    oal_uint8                          *puc_bssid;              /* 期望关联的AP BSSID  */

    oal_bool_enum_uint8                 en_privacy;             /* 是否加密标志 */
    oal_nl80211_auth_type_enum_uint8    en_auth_type;           /* 认证类型，OPEN or SHARE-KEY */

    oal_uint8                           uc_wep_key_len;         /* WEP KEY长度 */
    oal_uint8                           uc_wep_key_index;       /* WEP KEY索引 */
    OAL_CONST oal_uint8                *puc_wep_key;            /* WEP KEY密钥 */

    mac_cfg80211_crypto_settings_stru   st_crypto;              /* 密钥套件信息 */
    oal_uint32                          ul_ie_len;
}mac_cfg80211_connect_param_stru;

typedef struct
{
    oal_bool_enum_uint8                 en_privacy;             /* 是否加密标志 */
    oal_nl80211_auth_type_enum_uint8    en_auth_type;           /* 认证类型，OPEN or SHARE-KEY */
    oal_uint8                           uc_wep_key_len;         /* WEP KEY长度 */
    oal_uint8                           uc_wep_key_index;       /* WEP KEY索引 */
    oal_uint8                           auc_wep_key[WLAN_WEP104_KEY_LEN];            /* WEP KEY密钥 */
    mac_nl80211_mfp_enum_uint8          en_mgmt_proteced;       /* 此条链接pmf是否使能 */
    wlan_pmf_cap_status_uint8           en_pmf_cap;             /* 设备pmf能力 */
    oal_bool_enum_uint8                 en_wps_enable;

    mac_cfg80211_crypto_settings_stru   st_crypto;              /* 密钥套件信息 */
#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint8                           auc_mde[8];             /* MD IE信息 */
#endif //_PRE_WLAN_FEATURE_11R
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_int8                            c_rssi;                 /* 关联AP的RSSI信息 */
    oal_uint8                           auc_rsv[3];
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
}mac_cfg80211_connect_security_stru;


#ifdef _PRE_WLAN_FEATURE_11R
#define MAC_MAX_FTE_LEN              257

typedef struct
{
    oal_uint16            us_mdid;                   /* Mobile Domain ID */
    oal_uint16            us_len;                    /* FTE 的长度 */
    oal_uint8             auc_ie[MAC_MAX_FTE_LEN];
}mac_cfg80211_ft_ies_stru;

typedef struct
{
    oal_cfg80211_bss_stru            *pst_bss;
    const oal_uint8                  *puc_ie;
    oal_uint8                         uc_ie_len;
    oal_nl80211_auth_type_enum_uint8  en_auth_type;
    const oal_uint8                  *puc_key;
    oal_uint8                         uc_key_len;
    oal_uint8                         uc_key_idx;
}mac_cfg80211_auth_req_stru;

#endif //_PRE_WLAN_FEATURE_11R

typedef struct
{

    oal_uint8       auc_mac_addr[OAL_MAC_ADDR_LEN];
    oal_uint8       auc_rsv[2];
}mac_cfg80211_init_port_stru;

/* 解析内核配置的disconnect参数后，下发给驱动的disconnect参数 */
typedef struct mac_cfg80211_disconnect_param_tag
{
    oal_uint16              us_reason_code; /* disconnect reason code */
    oal_uint16              us_aid;

    oal_uint8               uc_type;
    oal_uint8               auc_arry[3];
}mac_cfg80211_disconnect_param_stru;



#ifdef _PRE_WLAN_CHIP_TEST


typedef enum
{
   MAC_LPM_SOC_BUS_GATING       = 0,
   MAC_LPM_SOC_PCIE_RD_BYPASS   = 1,
   MAC_LPM_SOC_MEM_PRECHARGE    = 2,
   MAC_LPM_SOC_PCIE_L0_S        = 3,
   MAC_LPM_SOC_PCIE_L1_0        = 4,

   MAC_LPM_SOC_SET_BUTT
}mac_lpm_soc_set_enum;
typedef oal_uint8   mac_lpm_soc_set_enum_uint8;


typedef struct mac_cfg_lpm_soc_set_tag
{
    mac_lpm_soc_set_enum_uint8      en_mode;
    oal_uint8                       uc_on_off;
    oal_uint8                       uc_pcie_idle;
    oal_uint8                       auc_rsv[1];
}mac_cfg_lpm_soc_set_stru;


typedef enum
{
   MAC_LPM_STATE_SOFT_SLEEP  = 0,
   MAC_LPM_STATE_GPIO_SLEEP  = 1,
   MAC_LPM_STATE_WORK        = 2,

   MAC_LPM_STATE_BUTT
}mac_lpm_state_enum;
typedef oal_uint8   mac_lpm_state_enum_uint8;

typedef struct mac_cfg_lpm_sleep_para_tag
{
    mac_lpm_state_enum_uint8         uc_pm_switch;  /*睡眠唤醒开关*/
    oal_uint8                        uc_rsv;
    oal_uint16                       us_sleep_ms;   /*睡眠时间，毫秒*/

}mac_cfg_lpm_sleep_para_stru;




typedef struct mac_cfg_lpm_psm_param_tag
{
    oal_uint8   uc_psm_on;
    oal_uint8   uc_psm_wakeup_mode;
    oal_uint8   auc_rsv[2];
    oal_uint16  us_psm_listen_interval;
    oal_uint16  us_psm_tbtt_offset;

}mac_cfg_lpm_psm_param_stru;

typedef struct mac_cfg_lpm_smps_stub
{
    oal_uint8                       uc_stub_type;   /*0:off, 1:单流，2:双流*/
    oal_uint8                       uc_rts_en;    /*是否发RTS*/
}mac_cfg_lpm_smps_stub_stru;


typedef struct mac_cfg_lpm_txopps_set_tag
{
    oal_uint8                       uc_txop_ps_on;
    oal_uint8                       uc_conditon1;
    oal_uint8                       uc_conditon2;
    oal_uint8                       auc_rsv[1];
}mac_cfg_lpm_txopps_set_stru;

typedef struct mac_cfg_lpm_txopps_tx_stub
{
    oal_uint8                       uc_stub_on;   /*0:off, 1:on*/
    oal_uint8                       auc_rsv[1];
    oal_uint16                      us_begin_num;  /* 第n个报文打桩 */
}mac_cfg_lpm_txopps_tx_stub_stru;

typedef struct mac_cfg_lpm_wow_en
{
    oal_uint8                       uc_en;              /*0:off, 1:on*/
    oal_uint8                       uc_null_wake;       /*1:null data wakeup*/
}mac_cfg_lpm_wow_en_stru;

typedef struct mac_cfg_lpm_tx_data_tag
{
    oal_uint16  us_num;
    oal_uint16  us_len;
    oal_uint8   uc_ac;
    oal_uint8   uc_positive;                          /*0:被动probe request，1:主动 */
    oal_uint8   uc_psm;                               /*0:psm=0,1:psm=1*/
    oal_uint8   uc_rsv[1];
    oal_uint8   auc_da[WLAN_MAC_ADDR_LEN];            /*发送probe request时，复用为指定BSSID*/
    //oal_uint8   auc_sa[WLAN_MAC_ADDR_LEN];
}mac_cfg_lpm_tx_data_stru;

typedef struct
{
    oal_uint16  us_user_idx;
    oal_uint8   uc_is_remove;
    oal_uint8   auc_resv[1];
}mac_cfg_remove_lut_stru;


typedef struct
{
    oal_uint8                               auc_mac_ra[WLAN_MAC_ADDR_LEN];
    oal_uint8                               uc_pkt_num;
    mac_test_frame_type_enum_uint8          en_frame_type;
}mac_cfg_send_frame_param_stru;

typedef struct
{
    oal_uint32                               ul_mac_ctrl;
    oal_uint32                               ul_rf_ctrl;
}mac_cfg_coex_ctrl_param_stru;

#endif
typedef struct
{
    oal_uint8                               auc_mac_da[WLAN_MAC_ADDR_LEN];
    oal_uint8                               uc_category;
    oal_uint8                               auc_resv[1];
}mac_cfg_send_action_param_stru;

#ifdef _PRE_WLAN_FEATURE_SMPS
typedef struct
{
    oal_uint8    uc_smps_mode;
    oal_uint8    auc_rsv[1];
    oal_uint16   us_user_idx;
}mac_cfg_smps_mode_stru;
#endif

typedef struct
{
    oal_int32   l_is_psm;                           /* 是否进入节能 */
    oal_int32   l_is_qos;                           /* 是否发qosnull */
    oal_int32   l_tidno;                            /* tid号 */
}mac_cfg_tx_nulldata_stru;

/* 设置以太网开关需要的参数 */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oal_switch_enum_uint8   en_switch;
    oal_uint8               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
}mac_cfg_eth_switch_param_stru;

/* 设置80211单播帧开关需要的参数 */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oam_user_track_frame_type_enum_uint8    en_frame_type;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
    oal_uint8                               auc_resv[1];
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
}mac_cfg_80211_ucast_switch_stru;
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* 获取用户收发参数开关需要的参数结构 */
typedef struct
{
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oam_user_txrx_param_type_enum_uint8     en_type;
    oal_switch_enum_uint8                   en_switch;
    oal_uint32                              ul_period;
}mac_cfg_report_txrx_param_stru;
#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
/* 软件配置mac txopps使能寄存器需要的三个参数 */
typedef struct
{
    oal_switch_enum_uint8 en_machw_txopps_en;               /* sta是否使能txopps */
    oal_switch_enum_uint8 en_machw_txopps_condition1;       /* txopps条件1 */
    oal_switch_enum_uint8 en_machw_txopps_condition2;       /* txopps条件2 */
    oal_uint8             auc_resv[1];
}mac_txopps_machw_param_stru;
#endif
/* 设置80211组播\广播帧开关需要的参数 */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oam_user_track_frame_type_enum_uint8    en_frame_type;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
    oal_uint8                               auc_resv[3];
}mac_cfg_80211_mcast_switch_stru;

/* 设置probe request和probe response开关需要的参数 */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
}mac_cfg_probe_switch_stru;

/* 获取mpdu数目需要的参数 */
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   auc_resv[2];
}mac_cfg_get_mpdu_num_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_resv;
}mac_cfg_usr_queue_param_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_tid_no;
}mac_cfg_ampdu_stat_stru;
#endif

typedef struct
{
    oal_uint8                   uc_aggr_num_switch; /* 控制聚合个数开关 */
    oal_uint8                   uc_aggr_num;        /* 聚合个数 */
    oal_uint8                   auc_resv[2];
}mac_cfg_aggr_num_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint8                   uc_mmss_val;        /* 最小帧间距 */
    oal_uint8                   auc_resv[3];
}mac_cfg_ampdu_mmss_stru;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint16                  us_pll_int;         /* 整数分频系数 */
    oal_uint16                  us_pll_frac;        /* 小数分频系数 */
}mac_cfg_freq_adjust_stru;
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_resv;
}mac_cfg_usr_thrput_stru;

#endif

typedef struct
{
    oal_uint32  ul_coext_info;
    oal_uint32  ul_channel_report;
}mac_cfg_set_2040_coexist_stru;

typedef struct
{
    oal_uint32   ul_mib_idx;
    oal_uint32   ul_mib_value;
}mac_cfg_set_mib_stru;

typedef struct
{
    oal_uint8  uc_bypass_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_thruput_bypass_stru;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
typedef struct
{
    oal_uint8  uc_cmd_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_auto_freq_stru;
#endif
typedef struct
{
    oal_uint8  uc_performance_log_switch_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_performance_log_switch_stru;

typedef struct
{
    oal_uint32   ul_timeout;
    oal_uint8    uc_is_period;
    oal_uint8    uc_stop_start;
    oal_uint8    auc_resv[2];
}mac_cfg_test_timer_stru;

typedef struct
{
    oal_uint16   us_user_idx;
    oal_uint16   us_rx_pn;
}mac_cfg_set_rx_pn_stru;

typedef struct
{
    oal_uint32   ul_frag_threshold;
}mac_cfg_frag_threshold_stru;

typedef struct
{
    oal_uint32   ul_rts_threshold;
}mac_cfg_rts_threshold_stru;

typedef struct
{
    /* software_retry值 */
    oal_uint8   uc_software_retry;
    /* 是否取test设置的值，为0则为正常流程所设 */
    oal_uint8   uc_retry_test;

    oal_uint8   uc_pad[2];
}mac_cfg_set_soft_retry_stru;


typedef struct
{
    oal_bool_enum_uint8 en_default_key;
    oal_uint8           uc_key_index;
    oal_uint8           uc_key_len;
    oal_uint8           auc_wep_key[WLAN_WEP104_KEY_LEN];
} mac_wep_key_param_stru;



typedef struct mac_pmksa_tag
{
    oal_uint8 auc_bssid[OAL_MAC_ADDR_LEN];
    oal_uint8 auc_pmkid[OAL_PMKID_LEN];

}mac_pmksa_stru;

typedef struct
{
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_uint8                auc_mac_addr[OAL_MAC_ADDR_LEN];
    mac_key_params_stru      st_key;
}mac_addkey_param_stru;


typedef struct
{
    oal_int32  key_len;
    oal_uint8 auc_key[OAL_WPA_KEY_LEN];
}mac_key_stru;

typedef struct
{
    oal_int32  seq_len;
    oal_uint8 auc_seq[OAL_WPA_SEQ_LEN];
}mac_seq_stru;


typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                  uc_key_index;
    oal_bool_enum_uint8        en_pairwise;
    //oal_uint8                auc_resv1[2];
    oal_uint8                  auc_mac_addr[OAL_MAC_ADDR_LEN];
    //oal_uint8                  uc_usridx;       /*  */
    oal_uint8                  cipher;
    //oal_uint8                  uc_type;        /* 1-key 2-seq */
    oal_uint8                  auc_rsv[3];
    mac_key_stru               st_key;
    mac_seq_stru               st_seq;
}mac_addkey_hmac2dmac_param_stru;

typedef struct
{
    oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_uint8                auc_resv1[2];
    oal_uint8               *puc_mac_addr;
    oal_void                *cookie;
    oal_void               (*callback)(oal_void *cookie, oal_key_params_stru *key_param);
}mac_getkey_param_stru;

typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    //oal_uint8                auc_resv1[2];
    oal_uint8                auc_mac_addr[OAL_MAC_ADDR_LEN];
}mac_removekey_param_stru;

typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_unicast;
    oal_bool_enum_uint8      en_multicast;
    oal_uint8                auc_resv1[1];
}mac_setdefaultkey_param_stru;

typedef struct
{
    oal_uint32  ul_dfs_mode;
    oal_int32   al_para[3];
}mac_cfg_dfs_param_stru;

typedef struct
{
    oal_uint8  uc_total_channel_num;
    oal_uint8  auc_channel_number[15];
}mac_cfg_dfs_auth_channel_stru;


typedef struct
{
    oal_uint    ul_addr;
    oal_uint32  ul_len;
}mac_cfg_dump_memory_stru;

#ifdef _PRE_WLAN_PERFORM_STAT
/* 统计量类型 */
typedef enum
{
    MAC_STAT_TYPE_TID_DELAY,
    MAC_STAT_TYPE_TID_PER,
    MAC_STAT_TYPE_TID_THRPT,
    MAC_STAT_TYPE_USER_THRPT,
    MAC_STAT_TYPE_VAP_THRPT,

    MAC_STAT_TYPE_BUTT
}mac_stat_type_enum;
typedef oal_uint8    mac_stat_type_enum_uint8;

typedef struct
{
    mac_stat_type_enum_uint8    en_stat_type;                       /* 统计类型 */
    oal_uint8                   uc_vap_id;                          /* vap id */
    oal_uint8                   auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8                   uc_tidno;                           /* tidno */
    oal_uint16                  us_stat_period;                     /* 统计周期 */
    oal_uint16                  us_stat_num;                        /* 统计次数 */
}mac_cfg_stat_param_stru;

typedef struct
{
    mac_stat_type_enum_uint8    en_stat_type;                       /* 统计类型 */
    oal_uint8                   uc_vap_id;                          /* vap id */
    oal_uint8                   auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8                   uc_tidno;                           /* tidno */
}mac_cfg_display_param_stru;

/* 统计tid */
typedef struct
{
    oal_uint8               uc_vap_id;                          /* vap id */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               uc_tidno;                           /* tidno */
    oal_uint16              us_stat_period;                     /* 统计周期 */
    oal_uint32              ul_stat_num;                        /* 统计次数 */
}mac_ioctl_stat_param_stru;

#endif


#ifdef _PRE_WLAN_FEATURE_FLOWCTL

typedef enum
{
    MAC_LINUX_SUBQ_BE = 0,    /* best effort */
    MAC_LINUX_SUBQ_BK = 1,    /* background */
    MAC_LINUX_SUBQ_VI = 2,    /* video */
    MAC_LINUX_SUBQ_VO = 3,    /* voice */

    MAC_LINUX_SUBQ_BUTT
}MAC_linux_subq_type_enum;
typedef oal_uint8 mac_linux_subq_type_enum;

#define MAC_TOS_TO_SUBQ(_tos) (      \
        (((_tos) == 0) || ((_tos) == 3)) ? MAC_LINUX_SUBQ_BE : \
        (((_tos) == 1) || ((_tos) == 2)) ? MAC_LINUX_SUBQ_BK : \
        (((_tos) == 4) || ((_tos) == 5)) ? MAC_LINUX_SUBQ_VI : \
        MAC_LINUX_SUBQ_VO)

typedef struct
{
    oal_uint16                      us_assoc_id;
    oal_uint8                       uc_vap_id;
    oal_uint8                       uc_tidno;
    oal_uint8                       uc_is_stop;
    oal_uint8                       uc_resv[3];
}mac_ioctl_queue_backp_stru;

#endif


/* 算法参数枚举，参数值 */
typedef struct
{
    mac_alg_cfg_enum_uint8              en_alg_cfg;     /* 配置命令枚举 */
    oal_uint8                           uc_resv[3];     /* 字节对齐 */
    oal_uint32                          ul_value;       /* 配置参数值 */
}mac_ioctl_alg_param_stru;

/* AUTORATE LOG 算法参数枚举，参数值 */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;     /* 配置命令枚举 */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               uc_ac_no;                           /* AC类型 */
    oal_uint8               auc_resv[2];
    oal_uint16              us_value;                           /*配置参数值 */
}mac_ioctl_alg_ar_log_param_stru;

/* AUTORATE 测试相关的命令参数 */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* 配置命令枚举 */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               auc_resv[1];
    oal_uint16              us_value;                           /* 命令参数 */
}mac_ioctl_alg_ar_test_param_stru;

/* TXMODE LOG 算法参数枚举，参数值 */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;     /* 配置命令枚举 */
    oal_uint8               uc_ac_no;                           /* AC类型 */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               auc_resv1[2];
    oal_uint16              us_value;                           /*配置参数值 */
}mac_ioctl_alg_txbf_log_param_stru;
/* 算法配置命令接口 */
typedef struct
{
    oal_uint8       uc_argc;
    oal_uint8       auc_argv_offset[DMAC_ALG_CONFIG_MAX_ARG];
}mac_ioctl_alg_config_stru;

/* TPC LOG 算法参数枚举，参数值 */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* 配置命令枚举 */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC地址 */
    oal_uint8               uc_ac_no;                           /* AC类型 */
    oal_uint16              us_value;                           /* 配置参数值 */
    oal_int8               *pc_frame_name;                      /* 获取特定帧功率使用该变量 */
}mac_ioctl_alg_tpc_log_param_stru;

/* cca opt LOG 算法参数枚举，参数值 */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* 配置命令枚举 */
    oal_uint16              us_value;                           /* 统计总时间 */
    oal_uint8               auc_resv;
}mac_ioctl_alg_cca_opt_log_param_stru;

#ifdef _PRE_DEBUG_MODE
/* 扫描测试命令 */
typedef struct
{
    oal_int8                            ac_scan_type[15];
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;
}mac_ioctl_scan_test_config_stru;
#endif

/*RTS 发送参数*/
typedef struct
{
    wlan_legacy_rate_value_enum_uint8   auc_rate[HAL_TX_RATE_MAX_NUM];           /*发送速率，单位mpbs*/
    wlan_phy_protocol_enum_uint8        auc_protocol_mode[HAL_TX_RATE_MAX_NUM] ; /*协议模式, 取值参见wlan_phy_protocol_enum_uint8*/
    wlan_channel_band_enum_uint8        en_band;
    oal_uint8                           auc_recv[3];
}mac_cfg_rts_tx_param_stru;

/* 组播转单播 发送参数 */
typedef struct
{
    oal_uint8 uc_m2u_mcast_mode;
    oal_uint8 uc_m2u_snoop_on;
}mac_cfg_m2u_snoop_on_param_stru;


/* 加组播转单播黑名单 */
typedef struct
{
    oal_uint32 ul_deny_group_addr;
}mac_add_m2u_deny_table_stru;

/* 清空组播转单播黑名单 */
typedef struct
{
    oal_uint8 uc_m2u_clear_deny_table;
    oal_uint8 uc_m2u_show_deny_table;
}mac_clg_m2u_deny_table_stru;


/* print snoop table*/
typedef struct
{
    oal_uint8 uc_m2u_show_snoop_table;
}mac_show_m2u_snoop_table_stru;

/* add snoop table*/
typedef struct
{
    oal_uint8 uc_m2u_add_snoop_table;
}mac_add_m2u_snoop_table_stru;

typedef struct
{
    oal_bool_enum_uint8 en_proxyarp;
    oal_uint8           auc_rsv[3];
}mac_proxyarp_en_stru;


typedef struct
{
    oal_uint64                          ull_cookie;
    oal_uint32                          ul_listen_duration;         /* 监听时间   */
    oal_uint8                           uc_listen_channel;          /* 监听的信道 */
    wlan_channel_bandwidth_enum_uint8   en_listen_channel_type;     /* 监听信道类型 */
    oal_uint8                           uc_home_channel;            /* 监听结束返回的信道 */
    wlan_channel_bandwidth_enum_uint8   en_home_channel_type;       /* 监听结束，返回主信道类型 */
    mac_vap_state_enum_uint8            en_last_vap_state;          /* P2P0和P2P_CL 公用VAP 结构，保存进入监听前VAP 的状态，便于监听结束时恢复该状态 */
    wlan_channel_band_enum_uint8        en_band;
    oal_ieee80211_channel_stru          st_listen_channel;

}mac_remain_on_channel_param_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint8    uc_pool_id;
}mac_device_pool_id_stru;
#endif

/* WPAS 管理帧发送结构 */
typedef struct
{
    oal_int32               channel;
    oal_uint8               mgmt_frame_id;
    oal_uint8               uc_rsv;
    oal_uint16              us_len;
    OAL_CONST oal_uint8    *puc_frame;
} mac_mgmt_frame_stru;

/* STA PS 发送参数 */
#ifdef _PRE_WLAN_FEATURE_STA_PM
typedef struct
{
    oal_uint8   uc_vap_ps_mode;

}mac_cfg_ps_mode_param_stru;

typedef struct
{
    oal_uint16   us_beacon_timeout;
    oal_uint16   us_tbtt_offset;
    oal_uint16   us_ext_tbtt_offset;
    oal_uint16   us_dtim3_on;
}mac_cfg_ps_param_stru;

#ifdef _PRE_PSM_DEBUG_MODE
typedef struct
{
    oal_uint8   uc_psm_info_enable      :2;  //开启psm的统计维测输出
    oal_uint8   uc_psm_debug_mode       :2;  //开启psm的debug打印模式
    oal_uint8   uc_psm_resd             :4;
}mac_cfg_ps_info_stru;
#endif

#endif
typedef struct
{
    oal_uint8   uc_show_ip_addr                 :4;  //show ip addr
    oal_uint8   uc_show_arpoffload_info         :4;  //show arpoffload 维测
}mac_cfg_arpoffload_info_stru;

typedef struct
{
    oal_uint8   uc_in_suspend; //亮暗屏
    oal_uint8   uc_arpoffload_switch; // arpoffload开关
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    oal_uint8   uc_rekeyoffload_switch;// rekeyoffload开关
    oal_uint8   auc_resv[1];
#endif
}mac_cfg_suspend_stru;

typedef enum {
    MAC_STA_PM_SWITCH_OFF         = 0,        /* 关闭低功耗 */
    MAC_STA_PM_SWITCH_ON          = 1,        /* 打开低功耗 */
    MAC_STA_PM_MANUAL_MODE_ON     = 2,        /* 开启手动sta pm mode */
    MAC_STA_PM_MANUAL_MODE_OFF    = 3,        /* 关闭手动sta pm mode */
    MAC_STA_PM_SWITCH_BUTT,                   /* 最大类型 */
}mac_pm_switch_enum;
typedef oal_uint8 mac_pm_switch_enum_uint8;

typedef enum {
    MAC_STA_PM_CTRL_TYPE_HOST   = 0,        /* 低功耗控制类型 HOST  */
    MAC_STA_PM_CTRL_TYPE_DBAC   = 1,        /* 低功耗控制类型 DBAC  */
    MAC_STA_PM_CTRL_TYPE_ROAM   = 2,        /* 低功耗控制类型 ROAM  */
    MAC_STA_PM_CTRL_TYPE_CMD    = 3,        /* 低功耗控制类型 CMD   */
    MAC_STA_PM_CTRL_TYPE_BUTT,              /* 最大类型，应小于 8  */
}mac_pm_ctrl_type_enum;
typedef oal_uint8 mac_pm_ctrl_type_enum_uint8;

typedef struct
{
    mac_pm_ctrl_type_enum_uint8     uc_pm_ctrl_type;       /*mac_pm_ctrl_type_enum*/
    mac_pm_switch_enum_uint8        uc_pm_enable;          /*mac_pm_switch_enum*/
}mac_cfg_ps_open_stru;

typedef enum {
    HISTREAM_SWITCH_OFF   = 0,        /* Histream 功能使能关闭  */
    HISTREAM_SWITCH_ON    = 1,        /* Histream 功能使能打开  */
    HISTREAM_SWITCH_ON_BUTT,          /* 最大类型，应小于 8  */
}mac_histream_switch_enum;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct mac_btcoex_syn_param
{
    oal_uint16 us_occupied;
}mac_btcoex_syn_param_stru;
#endif

/* P2P OPS 节能配置参数 */
typedef struct
{
    oal_uint8       en_ops_ctrl;
    oal_uint8       uc_ct_window;
    oal_uint8       en_pause_ops;
    oal_uint8       auc_rsv[1];
}mac_cfg_p2p_ops_param_stru;

/* P2P NOA节能配置参数 */
typedef struct
{
    oal_uint32      ul_start_time;
    oal_uint32      ul_duration;
    oal_uint32      ul_interval;
    oal_uint8       uc_count;
    oal_uint8       auc_rsv[3];
}mac_cfg_p2p_noa_param_stru;

/* P2P 节能控制命令 */
typedef struct
{
    oal_uint8       uc_p2p_statistics_ctrl;/* 0:清除P2P 统计值； 1:打印输出统计值 */
    oal_uint8       auc_rsv[3];

}mac_cfg_p2p_stat_param_stru;

#ifdef _PRE_WLAN_FEATURE_WOW

#define WOW_NETPATTERN_MAX_NUM      (4)
#define WOW_NETPATTERN_MAX_LEN      (64)

typedef enum
{
    MAC_WOW_DISABLE,
    MAC_WOW_ENABLE,
    MAC_WOW_EN_BUTT
}mac_wow_en_enum;

typedef enum
{
    MAC_WOW_WAKEUP_NOTIFY,
    MAC_WOW_SLEEP_REQUEST,
    MAC_WOW_NOTIFY_TYPE_BUTT
}mac_wow_notify_type_enum;

typedef enum
{
    MAC_WOW_FIELD_ALL_CLEAR          = 0,          /* Clear all events */
    MAC_WOW_FIELD_MAGIC_PACKET       = BIT0,       /* Wakeup on Magic Packet */
    MAC_WOW_FIELD_NETPATTERN_TCP     = BIT1,       /* Wakeup on TCP NetPattern */
    MAC_WOW_FIELD_NETPATTERN_UDP     = BIT2,       /* Wakeup on UDP NetPattern */
    MAC_WOW_FIELD_DISASSOC_RX        = BIT3,       /* 对端去关联，Wakeup on loss-of-link due to Disassociation/Deauth */
    MAC_WOW_FIELD_DISASSOC_TX        = BIT4,       /* 本端主动去关联，Wakeup on loss of beacon */
    MAC_WOW_FIELD_AUTH_RX            = BIT5,       /* 对端关联请求，Wakeup on auth */
    MAC_WOW_FIELD_TCP_UDP_KEEP_ALIVE = BIT6,       /* Wakeup on TCP/UDP keep alive timeout */
    MAC_WOW_FIELD_HOST_WAKEUP        = BIT7,       /* Host wakeup */
}mac_wow_field_enum;

/* WOW netpattern 参数配置,单个配置 */
typedef struct
{
    oal_uint8   auc_pattern_data[WOW_NETPATTERN_MAX_LEN];
    oal_uint32  ul_pattern_len;
}wow_pattern_stru;

/* WOW netpattern 参数配置，所有配置 */
typedef struct
{
    wow_pattern_stru   ast_pattern[WOW_NETPATTERN_MAX_NUM];
    oal_uint16         us_pattern_map;
    oal_uint16         us_pattern_num;
}wow_pattern_cfg_stru;

typedef struct
{
    oal_uint8                   uc_wow_en;
    oal_uint8                   auc_res[3];
    oal_uint32                  ul_wow_event;
    wow_pattern_cfg_stru        st_wow_pattern;
}mac_wow_cfg_stu;


#endif //#ifdef _PRE_WLAN_FEATURE_WOW

#ifdef _PRE_WLAN_FEATURE_ROAM
typedef enum
{
    WPAS_CONNECT_STATE_INIT            = 0,
    WPAS_CONNECT_STATE_START           = 1,
    WPAS_CONNECT_STATE_ASSOCIATED      = 2,
    WPAS_CONNECT_STATE_HANDSHAKED      = 3,
    WPAS_CONNECT_STATE_IPADDR_OBTAINED   = 4,
    WPAS_CONNECT_STATE_IPADDR_REMOVED    = 5,
    WPAS_CONNECT_STATE_BUTT
}wpas_connect_state_enum;
typedef oal_uint32 wpas_connect_state_enum_uint32;
/* roam trigger 数据结构体 */
typedef struct
{
    oal_int8                      c_trigger_2G;
    oal_int8                      c_trigger_5G;
    oal_uint8                     auc_resv[2];
}mac_roam_trigger_stru;

/* roam hmac 同步 dmac数据结构体 */
typedef struct
{
    oal_uint16                      us_sta_aid;
    oal_uint16                      us_pad;
    mac_channel_stru                st_channel;
    mac_user_cap_info_stru          st_cap_info;
    mac_key_mgmt_stru               st_key_info;
    mac_user_tx_param_stru          st_user_tx_info;
    oal_uint32                      ul_back_to_old;
}mac_h2d_roam_sync_stru;
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/* 定制化 linkloss门限配置参数 */
typedef struct
{
    oal_uint8                   uc_linkloss_threshold_wlan_near;
    oal_uint8                   uc_linkloss_threshold_wlan_far;
    oal_uint8                   uc_linkloss_threshold_p2p;
    oal_uint8                   auc_resv[1];
}mac_cfg_linkloss_threshold;
/* 定制化 power ref 2g 5g配置参数 */
typedef struct
{
    oal_uint32                  ul_power_ref_2g;
}mac_cfg_power_ref;
/* customize rf cfg struct */
typedef struct
{
    oal_int8                    c_rf_gain_db_2g_mult4;      /*外部PA/LNA bypass时的增益(0.25dB)*/
    oal_int8                    c_rf_gain_db_2g_mult10;     /*外部PA/LNA bypass时的增益(0.1dB)*/
}mac_cfg_gain_db_2g_band;
typedef struct
{
    /* 2g */
    mac_cfg_gain_db_2g_band     ac_gain_db_2g[MAC_NUM_2G_BAND];
    /* 5g */
    oal_uint16                  us_lna_on2off_time_ns_5g;           /* LNA开到LNA关的时间(ns) */
    oal_uint16                  us_lna_off2on_time_ns_5g;           /* LNA关到LNA开的时间(ns) */
    oal_int8                    c_rf_line_rx_gain_db_5g;            /* 外部LNA bypass时的增益(dB) */
    oal_int8                    c_lna_gain_db_5g;                   /* 外部LNA增益(dB) */
    oal_int8                    c_rf_line_tx_gain_db_5g;            /* 外部LNA bypass时的增益(dB) */
    oal_uint8                   uc_ext_switch_isexist_5g;           /* 是否使用外部switch */
    oal_uint8                   uc_ext_pa_isexist_5g;               /* 是否使用外部pa */
    oal_uint8                   uc_ext_lna_isexist_5g;              /* 是否使用外部lna */
    oal_uint8                   auc_resv_5g[2];
}mac_cfg_customize_rf;
typedef struct
{
    oal_uint16                  us_tx_ratio;                        /* tx占空比 */
    oal_uint16                  us_tx_pwr_comp_val;                 /* 发射功率补偿值 */
}mac_tx_ratio_vs_pwr_stru;

/* 定制化TX占空比&温度补偿发射功率的参数 */
typedef struct
{
    mac_tx_ratio_vs_pwr_stru    ast_txratio2pwr[3];                 /* 3档占空比分别对应功率补偿值 */
    oal_uint32                  ul_more_pwr;                        /* 根据温度额外补偿的发射功率 */
}mac_cfg_customize_tx_pwr_comp_stru;
/* 定制化 时钟配置参数 */
typedef struct
{
    oal_uint32                  ul_rtc_clk_freq;
    oal_uint8                   uc_clk_type;
    oal_uint8                   auc_resv[3];
}st_pm_cfg_param;
/* RF寄存器定制化结构体 */
typedef struct
{
    oal_uint16                 us_rf_reg117;
    oal_uint16                 us_rf_reg123;
    oal_uint16                 us_rf_reg124;
    oal_uint16                 us_rf_reg125;
    oal_uint16                 us_rf_reg126;
    oal_uint8                  auc_resv[2];
}mac_cus_dts_rf_reg;
/* FCC认证 参数结构体 */
typedef struct
{
    oal_uint8       uc_index;           /* 下标表示偏移 */
    oal_uint8       uc_max_txpower;     /* 最大发送功率 */
    oal_uint8       uc_dbb_scale;       /* dbb scale */
    oal_uint8       uc_resv;
}mac_cus_band_edge_limit_stru;
/* 定制化 校准配置参数 */
typedef struct
{
    /* dts */
    oal_int16                  aus_cali_txpwr_pa_dc_ref_2g_val[13];        /* txpwr分信道ref值 */
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band1;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band2;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band3;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band4;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band5;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band6;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band7;
    oal_int8                   uc_band_5g_enable;
    oal_uint8                  uc_tone_amp_grade;
    oal_int8                   auc_resv_wifi_cali[2];
    /* bt tmp */
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band1;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band2;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band3;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band4;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band5;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band6;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band7;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band8;
    oal_uint16                  us_cali_bt_txpwr_numb;
    oal_uint16                  us_cali_bt_txpwr_pa_fre1;
    oal_uint16                  us_cali_bt_txpwr_pa_fre2;
    oal_uint16                  us_cali_bt_txpwr_pa_fre3;
    oal_uint16                  us_cali_bt_txpwr_pa_fre4;
    oal_uint16                  us_cali_bt_txpwr_pa_fre5;
    oal_uint16                  us_cali_bt_txpwr_pa_fre6;
    oal_uint16                  us_cali_bt_txpwr_pa_fre7;
    oal_uint16                  us_cali_bt_txpwr_pa_fre8;
    oal_uint8                   uc_bt_tone_amp_grade;
    oal_uint8                   auc_resv_bt_cali[1];
}mac_cus_dts_cali_stru;
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
typedef struct
{
    oal_uint32      ul_sess_id;
    oal_uint8       uc_dst_mac[6];  /*目的MAC地址*/
    oal_uint8       auc_resv[2];
    oal_uint8       uc_src_ip[4];   /*源IP地址*/
    oal_uint8       uc_dst_ip[4];   /*目的IP地址*/
    oal_uint16      us_src_port;    /*源端口号*/
    oal_uint16      us_dst_port;    /*目的端口号*/
    oal_uint32      ul_seq_num;     /*序列号*/
    oal_uint32      ul_ack_num;     /*确认号*/
    oal_uint16      us_window;      /*TCP窗口大小*/
    oal_uint16      us_interval_timer;       /*心跳包发送周期*/
    oal_uint16      us_retry_interval_timer; /*重传时心跳包发送周期*/
    oal_uint16      us_retry_max_count;      /*最大重传次数*/
    oal_uint32      ul_time_value;
    oal_uint32      ul_time_echo;
}mac_tcp_params_stru;

typedef struct
{
    oal_uint32     ul_sess_id;
    oal_uint8      uc_dst_mac[6];    /*目的MAC地址*/
    oal_uint8      auc_resv[2];
    oal_uint8      uc_src_ip[4];     /*源IP地址*/
    oal_uint8      uc_dst_ip[4];     /*目的IP地址*/
    oal_uint16     us_src_port;      /*源端口号*/
    oal_uint16     us_dst_port;      /*目的端口号*/
    oal_uint16     us_interval_timer;       /*心跳包发送周期*/
    oal_uint16     us_retry_interval_timer; /*重传时心跳包发送周期*/
    oal_uint16     us_retry_max_count;      /*最大重传次数*/
    oal_uint32     ul_time_value;
    oal_uint32     ul_time_echo;
}mac_udp_params_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
extern oal_uint8 g_uc_uapsd_cap;
#endif

#ifdef _PRE_WLAN_FEATURE_HISTREAM
extern oal_uint8 g_uc_histream_switch;
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
//extern oal_void mac_vap_set_p2p_channel(mac_vap_stru *pst_mac_vap, mac_channel_stru * pst_p2p_home_channel);

/*****************************************************************************
 函 数 名  : mac_get_excludeunencrypted
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_get_excludeunencrypted(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11ExcludeUnencrypted;
}

/*****************************************************************************
 函 数 名  : mac_get_PrivacyInvoked
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_rsnacfggroupcipher(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;
}

OAL_STATIC OAL_INLINE oal_void mac_mib_set_rsnacfggroupcipher(mac_vap_stru *pst_mac_vap, oal_uint8 uc_group_cipher)
{
  pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = uc_group_cipher;
}
OAL_STATIC OAL_INLINE oal_void mac_mib_set_RSNAGroupCipherSelected(mac_vap_stru *pst_mac_vap, oal_uint8 uc_group_cipher_selected)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherSelected = uc_group_cipher_selected;
}

OAL_STATIC OAL_INLINE oal_void mac_mib_set_RSNAConfigGroupCipherSize(oal_uint32 ul_group_cipher_size,mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = ul_group_cipher_size;
}

OAL_STATIC OAL_INLINE oal_uint32 mac_get_RSNAConfigGroupCipherSize(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize;
}

void mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_inp, oal_uint8 uc_idx);
void mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value);
void mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value);

/*****************************************************************************
 函 数 名  : mac_mib_get_PrivacyInvoked
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_privacyinvoked(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_PrivacyInvoked
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_privacyinvoked(mac_vap_stru *pst_mac_vap,oal_bool_enum_uint8 en_privacyinvoked)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked = en_privacyinvoked;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_rsnaactivated
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_rsnaactivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_rsnaactivated
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_rsnaactivated(mac_vap_stru *pst_mac_vap,oal_bool_enum_uint8 en_rsnaactivated)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated = en_rsnaactivated;
}

/*****************************************************************************
 函 数 名  : mac_is_wep_enabled
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_is_wep_enabled(mac_vap_stru *pst_mac_vap)
{
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_FALSE;
    }

    if ((mac_mib_get_privacyinvoked(pst_mac_vap) == OAL_FALSE)||(mac_mib_get_rsnaactivated(pst_mac_vap) == OAL_TRUE))
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : mac_is_wep_allowed
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_is_wep_allowed(mac_vap_stru *pst_mac_vap)
{
    oal_uint8 uc_grp_policy ;

    if (mac_mib_get_rsnaactivated(pst_mac_vap) == OAL_TRUE)
    {
        uc_grp_policy = mac_get_rsnacfggroupcipher(pst_mac_vap);
        if ((WLAN_80211_CIPHER_SUITE_WEP_40 == uc_grp_policy)||(WLAN_80211_CIPHER_SUITE_WEP_104 == uc_grp_policy))
        {
            return OAL_TRUE;
        }

        return OAL_FALSE;
    }
    else
    {
        return mac_is_wep_enabled(pst_mac_vap);
    }
}

/*****************************************************************************
 函 数 名  : mac_set_WEPDefaultKeyID
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_set_wep_default_keyid(mac_vap_stru *pst_mac_vap,oal_uint8 uc_default_key_id)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID = uc_default_key_id;
}

/*****************************************************************************
 函 数 名  : mac_get_WEPDefaultKeyID
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_default_keyid(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID);
}

/*****************************************************************************
 函 数 名  : mac_get_WEPDefaultKeySize
 功能描述  : 获取默认密钥的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_default_keysize(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[mac_get_wep_default_keyid(pst_mac_vap)].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET]);
}

/*****************************************************************************
 函 数 名  : mac_get_wep_keysize
 功能描述  : 获取指定序列号的wep key的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_keysize(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx)
{
    return (pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET]);
}

/*****************************************************************************
 函 数 名  : mac_get_wep_default_keyvalue
 功能描述  : 获取默认wep key的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8*  mac_get_wep_default_keyvalue(mac_vap_stru *pst_mac_vap)
{
    return (&pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[mac_get_wep_default_keyid(pst_mac_vap)].auc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET]);
}

/*****************************************************************************
 函 数 名  : mset_wep_key_value
 功能描述  : 将一个密钥写进mib项中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_set_wep_key_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx, OAL_CONST oal_uint8 *puc_key, oal_uint8 uc_size)
{
    oal_uint8 *puc_dot11WEPDefaultKeyValue;

    puc_dot11WEPDefaultKeyValue = pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue;
    puc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = uc_size;

    switch(uc_size)
    {
        case 40:
            uc_size = 5;
            break;
        case 104:
            uc_size = 13;
            break;
        default:
            uc_size = 5;
            break;
    }

    oal_memcopy(&puc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET], puc_key, uc_size);
}

/*****************************************************************************
 函 数 名  : mac_get_wep_key_value
 功能描述  : 获取wep key的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8*  mac_get_wep_key_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx)
{
    return (&pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET]);
}

/*****************************************************************************
 函 数 名  : mac_get_wep_type
 功能描述  : 获取wep type的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_ciper_protocol_type_enum_uint8 mac_get_wep_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id)
{
    wlan_ciper_protocol_type_enum_uint8 en_cipher_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    switch(mac_get_wep_keysize(pst_mac_vap,uc_key_id))
    {
        case 40:
            en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
            break;
        case 104:
            en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_104;
            break;
        default:
            en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
            break;
    }
    return en_cipher_type;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_DeauthenticateReason
 功能描述  : 记录去认证原因
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DeauthenticateReason(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DeauthenticateReason = (oal_uint32)us_err_code;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_DeauthenticateStation
 功能描述  : 记录去认证站点地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DeauthenticateStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DeauthenticateStation, puc_da, 6);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_DeauthenticateStation
 功能描述  : 记录认证失败的STA地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_AuthenticateFailStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11AuthenticateFailStation, puc_da, 6);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_DeauthenticateReason
 功能描述  : 记录认证失败原因
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_AuthenticateFailStatus(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticateFailStatus = (oal_uint32)us_err_code;
}


/*****************************************************************************
 函 数 名  : mac_mib_set_DisassocStation
 功能描述  : 记录去关联地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DisassocStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DisassociateStation, puc_da, 6);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_DisassocReason
 功能描述  : 记录去关联原因
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DisassocReason(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DisassociateReason = (oal_uint32)us_err_code;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_StationID
 功能描述  : 获取MIB项 dot11StationID 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : MAC地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 *mac_mib_get_StationID(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_StationID
 功能描述  : 设置MIB项 dot11StationID 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             puc_sta_id : MAC地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_StationID(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_sta_id)
{
    oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, puc_sta_id);
}

/*****************************************************************************
 函 数 名  : mac_mib_get_OBSSScanPassiveDwell
 功能描述  : 获取MIB项 dot11OBSSScanPassiveDwell 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OBSSScanPassiveDwell
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanPassiveDwell(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_OBSSScanPassiveDwell
 功能描述  : 设置MIB项 dot11OBSSScanPassiveDwell 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanPassiveDwell(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_OBSSScanActiveDwell
 功能描述  : 获取MIB项 dot11OBSSScanActiveDwell 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OBSSScanActiveDwell
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActiveDwell(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_OBSSScanActiveDwell
 功能描述  : 设置MIB项 dot11OBSSScanActiveDwell 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActiveDwell(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_BSSWidthTriggerScanInterval
 功能描述  : 获取MIB项 dot11BSSWidthTriggerScanInterval 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11BSSWidthTriggerScanInterval
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_BSSWidthTriggerScanInterval(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_BSSWidthTriggerScanInterval
 功能描述  : 设置MIB项 dot11BSSWidthTriggerScanInterval 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_BSSWidthTriggerScanInterval(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_OBSSScanPassiveTotalPerChannel
 功能描述  : 获取MIB项 dot11OBSSScanPassiveTotalPerChannel 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OBSSScanPassiveTotalPerChannel
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanPassiveTotalPerChannel(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_OBSSScanPassiveTotalPerChannel
 功能描述  : 设置MIB项 dot11OBSSScanPassiveTotalPerChannel 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanPassiveTotalPerChannel(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_OBSSScanActiveTotalPerChannel
 功能描述  : 获取MIB项 dot11OBSSScanActiveTotalPerChannel 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OBSSScanActiveTotalPerChannel
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActiveTotalPerChannel(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_OBSSScanActiveTotalPerChannel
 功能描述  : 设置MIB项 dot11OBSSScanActiveTotalPerChannel 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActiveTotalPerChannel(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_BSSWidthChannelTransitionDelayFactor
 功能描述  : 获取MIB项 dot11BSSWidthChannelTransitionDelayFactor 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11BSSWidthChannelTransitionDelayFactor
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_BSSWidthChannelTransitionDelayFactor(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_BSSWidthChannelTransitionDelayFactor
 功能描述  : 设置MIB项 dot11BSSWidthChannelTransitionDelayFactor 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_BSSWidthChannelTransitionDelayFactor(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_OBSSScanActivityThreshold
 功能描述  : 获取MIB项 dot11OBSSScanActivityThreshold 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OBSSScanActivityThreshold
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActivityThreshold(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_OBSSScanActivityThreshold
 功能描述  : 设置MIB项 dot11OBSSScanActivityThreshold 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActivityThreshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_HighThroughputOptionImplemented
 功能描述  : 获取MIB项 dot11HighThroughputOptionImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11HighThroughputOptionImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_HighThroughputOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_HighThroughputOptionImplemented
 功能描述  : 设置MIB项 dot11HighThroughputOptionImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_HighThroughputOptionImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = en_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_VHTOptionImplemented
 功能描述  : 获取MIB项 dot11VHTOptionImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11VHTOptionImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_VHTOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_VHTChannelWidthOptionImplemented
 功能描述  : 获取MIB项 dot11VHTChannelWidthOptionImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11VHTChannelWidthOptionImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_mib_get_VHTChannelWidthOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.uc_dot11VHTChannelWidthOptionImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_dot11FortyMHzOperationImplemented
 功能描述  : 获取MIB项 dot11FortyMHzOperationImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11FortyMHzOperationImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_FortyMHzOperationImplemented(mac_vap_stru *pst_mac_vap)
{
    return (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band) ?
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented :
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_dot11FortyMHzOperationImplemented
 功能描述  : 设置MIB项 dot11FortyMHzOperationImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_FortyMHzOperationImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented = en_val;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented = en_val;
    }
}

/*****************************************************************************
 函 数 名  : mac_mib_get_SpectrumManagementImplemented
 功能描述  : 获取MIB项 dot11SpectrumManagementImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11SpectrumManagementImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_SpectrumManagementImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_SpectrumManagementImplemented
 功能描述  : 设置MIB项 dot11SpectrumManagementImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_SpectrumManagementImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented = en_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_FortyMHzIntolerant
 功能描述  : 获取MIB项 dot11FortyMHzIntolerant 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11FortyMHzIntolerant
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_FortyMHzIntolerant(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant;
}



/*****************************************************************************
 函 数 名  : mac_mib_set_FortyMHzIntolerant
 功能描述  : 设置MIB项 dot11FortyMHzIntolerant 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_FortyMHzIntolerant(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant = en_val;
}


/*****************************************************************************
 函 数 名  : mac_mib_get_2040BSSCoexistenceManagementSupport
 功能描述  : 获取MIB项 dot112040BSSCoexistenceManagementSupport 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot112040BSSCoexistenceManagementSupport
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_2040BSSCoexistenceManagementSupport(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot112040BSSCoexistenceManagementSupport;
}
 /*****************************************************************************
 函 数 名  : mac_mib_get_dot11RSNAActivated
 功能描述  : 获取MIB项 dot11RSNAActivated 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11RSNAActivated
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAActivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_dot11RSNAProtectedManagementFramesActivated
 功能描述  : 获取MIB项 dot11RSNAProtectedManagementFramesActivated 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11RSNAProtectedManagementFramesActivated
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAProtectedManagementFramesActivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAProtectedManagementFramesActivated;
}
/*****************************************************************************
 函 数 名  : mac_mib_get_dot11RSNAMFPC
 功能描述  : 获取MIB项 dot11RSNAMFPC 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11RSNAMFPC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAMFPC(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC;
}
/*****************************************************************************
 函 数 名  : mac_mib_get_dot11RSNAMFPR
 功能描述  : 获取MIB项 dot11RSNAMFPR 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11RSNAMFPR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAMFPR(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_dot11RSNAActivated
 功能描述  : 设置MIB项 dot11RSNAActivated 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated = ul_val;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_dot11RSNAProtectedManagementFramesActivated
 功能描述  : 设置MIB项 dot11RSNAProtectedManagementFramesActivated 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAProtectedManagementFramesActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAProtectedManagementFramesActivated = ul_val;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_dot11RSNAMFPC
 功能描述  : 设置MIB项 dot11RSNAMFPC 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAMFPC(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
   pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = ul_val;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_dot11RSNAMFPR
 功能描述  : 设置MIB项 dot11RSNAMFPR的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAMFPR(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = ul_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_dot11AssociationSAQueryMaximumTimeout
 功能描述  : 获取MIB项 dot11AssociationSAQueryMaximumTimeout 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11AssociationSAQueryMaximumTimeout
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11AssociationSAQueryMaximumTimeout(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout;
}
/*****************************************************************************
 函 数 名  : mac_mib_get_dot11AssociationSAQueryRetryTimeout
 功能描述  : 获取MIB项 dot11AssociationSAQueryRetryTimeout 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11AssociationSAQueryRetryTimeout
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11AssociationSAQueryRetryTimeout(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_dot11AssociationSAQueryMaximumTimeout
 功能描述  : 设置MIB项 dot11AssociationSAQueryMaximumTimeout 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11AssociationSAQueryMaximumTimeout(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout = ul_val;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_dot11AssociationSAQueryRetryTimeout
功能描述  : 设置MIB项 dot11AssociationSAQueryRetryTimeout 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11AssociationSAQueryRetryTimeout(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout = ul_val;
#endif
}
/*****************************************************************************
 函 数 名  : mac_mib_set_2040BSSCoexistenceManagementSupport
 功能描述  : 设置MIB项 dot112040BSSCoexistenceManagementSupport 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_2040BSSCoexistenceManagementSupport(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot112040BSSCoexistenceManagementSupport = en_val;
}
/*****************************************************************************
 函 数 名  : mac_mib_get_dot11dtimperiod
 功能描述  : 获取MIB项 ul_dot11DTIMPeriod 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11dtimperiod(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;
}

/*****************************************************************************
 函 数 名  : mac_mib_init_2040
 功能描述  : 初始化支持2040共存
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11FortyMHzIntolerant
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : zhangzhiming
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_init_2040(mac_vap_stru *pst_mac_vap)
{
    mac_mib_set_FortyMHzIntolerant(pst_mac_vap, OAL_FALSE);
    mac_mib_set_SpectrumManagementImplemented(pst_mac_vap, OAL_TRUE);
    mac_mib_set_2040BSSCoexistenceManagementSupport(pst_mac_vap, OAL_TRUE);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_dot11dtimperiod
 功能描述  : 设置MIB项 ul_dot11DTIMPeriod 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_dot11dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    if (ul_val != 0)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = ul_val;
    }
}

/*****************************************************************************
 函 数 名  : mac_mib_get_powermanagementmode
 功能描述  : 获取MIB项 ul_dot11DTIMPeriod 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_powermanagementmode(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_powermanagementmode
 功能描述  : 设置MIB项 ul_dot11DTIMPeriod 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             ul_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_powermanagementmode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_val)
{
    if (uc_val != 0)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode = uc_val;
    }
}

#if defined _PRE_WLAN_FEATURE_OPMODE_NOTIFY || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : mac_mib_get_OperatingModeNotificationImplemented
 功能描述  : 获取MIB项 dot11OperatingModeNotificationImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : dot11OperatingModeNotificationImplemented
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_OperatingModeNotificationImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_OperatingModeNotificationImplemented
 功能描述  : 设置MIB项 dot11OperatingModeNotificationImplemented 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
             en_val     : 需要设置的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OperatingModeNotificationImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented = en_val;
}
#endif


/*****************************************************************************
 函 数 名  : mac_mib_get_LsigTxopFullProtectionActivated
 功能描述  : 获取LsigTxopFullProtectionActivated值
 输入参数  : pst_mac_vap  :  mac vap结构体
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_LsigTxopFullProtectionActivated(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11LSIGTXOPFullProtectionActivated);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_LsigTxopFullProtectionActivated
 功能描述  : 设置LsigTxopFullProtectionActivated值
 输入参数  : pst_mac_vap                            :  mac vap结构体
             en_lsig_txop_full_protection_activated :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_LsigTxopFullProtectionActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_lsig_txop_full_protection_activated)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11LSIGTXOPFullProtectionActivated = en_lsig_txop_full_protection_activated;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_NonGFEntitiesPresent
 功能描述  : 获取NonGFEntitiesPresent值
 输入参数  : pst_mac_vap  :  mac vap结构体
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_NonGFEntitiesPresent(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11NonGFEntitiesPresent);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_NonGFEntitiesPresent
 功能描述  : 设置NonGFEntitiesPresent值
 输入参数  : pst_mac_vap                :  mac vap结构体
             en_non_gf_entities_present :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_NonGFEntitiesPresent(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_non_gf_entities_present)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11NonGFEntitiesPresent = en_non_gf_entities_present;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_RifsMode
 功能描述  : 获取RIFSMode值
 输入参数  : pst_mac_vap  :  mac vap结构体
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_RifsMode(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11RIFSMode);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_RifsMode
 功能描述  : 设置RIFSMode值
 输入参数  : pst_mac_vap             :  mac vap结构体
             en_rifs_mode            :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_RifsMode(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_rifs_mode)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11RIFSMode = en_rifs_mode;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_HtProtection
 功能描述  : 获取htProtection值
 输入参数  : pst_mac_vap  :  mac vap结构体
 输出参数  : 无
 返 回 值  : wlan_mib_ht_protection_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_mib_ht_protection_enum_uint8 mac_mib_get_HtProtection(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11HTProtection);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_HtProtection
 功能描述  : 设置htProtection值
 输入参数  : pst_mac_vap                 :  mac vap结构体
             en_ht_protection            :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_HtProtection(mac_vap_stru *pst_mac_vap, wlan_mib_ht_protection_enum_uint8 en_ht_protection)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11HTProtection = en_ht_protection;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_ShortPreambleOptionImplemented
 功能描述  : 获取ShortPreambleOptionImplemented值
 输入参数  : pst_mac_vap  :  mac vap结构体
 输出参数  : 无
 返 回 值  : wlan_11b_preamble_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_11b_mib_preamble_enum_uint8 mac_mib_get_ShortPreambleOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ShortPreambleOptionImplemented);
}

/*****************************************************************************
 函 数 名  : mac_mib_set_ShortPreambleOptionImplemented
 功能描述  : 设置ShortPreambleOptionImplemented值
 输入参数  : pst_mac_vap                 :  mac vap结构体
             en_preamble                 :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_ShortPreambleOptionImplemented(mac_vap_stru *pst_mac_vap, wlan_11b_mib_preamble_enum_uint8 en_preamble)
{
    pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ShortPreambleOptionImplemented = en_preamble;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_SpectrumManagementRequired
 功能描述  : 设置en_dot11SpectrumManagementRequired值
 输入参数  : pst_mac_vap            :  mac vap结构体
             en_val                 :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_SpectrumManagementRequired(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementRequired = en_val;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_ShortGIOptionInFortyImplemented
 功能描述  : 获取en_dot11ShortGIOptionInFortyImplemented值
 输入参数  : pst_mac_vap            :  mac vap结构体
             en_val                 :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_ShortGIOptionInFortyImplemented(mac_vap_stru *pst_mac_vap)
{
    return (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band) ?
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented :
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_ShortGIOptionInFortyImplemented
 功能描述  : 设置en_dot11ShortGIOptionInFortyImplemented值
 输入参数  : pst_mac_vap            :  mac vap结构体
             en_val                 :  需要设置值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_ShortGIOptionInFortyImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented = en_val;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented = en_val;
    }
}

/*****************************************************************************
 函 数 名  : mac_mib_set_frag_threshold
 功能描述  : 设置分片门限值
 输入参数  : pst_mac_vap                 :  mac vap结构体
             ul_frag_threshold           :  分片门限值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_frag_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_frag_threshold)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold = ul_frag_threshold;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_rts_threshold
 功能描述  : 设置RTS门限值
 输入参数  : pst_mac_vap                 :  mac vap结构体
             ul_rts_threshold            :  RTS 门限值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_rts_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_rts_threshold)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11RTSThreshold = ul_rts_threshold;
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32 mac_vap_init(
                    mac_vap_stru               *pst_vap,
                    oal_uint8                   uc_chip_id,
                    oal_uint8                   uc_device_id,
                    oal_uint8                   uc_vap_id,
                    mac_cfg_add_vap_param_stru *pst_param);
extern oal_void mac_vap_init_rates(mac_vap_stru *pst_vap);
extern oal_void mac_sta_init_bss_rates(mac_vap_stru *pst_vap, oal_void *pst_bss_dscr);
extern oal_void mac_vap_init_rates_by_protocol(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru *pst_rates);
extern oal_uint32 mac_vap_exit(mac_vap_stru *pst_vap);
extern oal_uint32  mac_vap_del_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx);
extern oal_uint32  mac_vap_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx);

extern oal_uint32  mac_device_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx);

#if 0
extern oal_uint32  mac_vap_update_user(mac_vap_stru *pst_vap, oal_uint32   ul_user_dix);
#endif
extern oal_uint32  mac_vap_add_assoc_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx);


/*****************************************************************************
    mib操作函数
*****************************************************************************/
extern oal_uint32  mac_mib_get_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_get_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_get_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_group_count);
#endif
extern oal_uint32  mac_mib_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_get_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  mac_mib_set_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_set_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_group_count);
#endif
extern oal_uint32  mac_mib_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
oal_void  mac_mib_clear_rsna_auth_suite(mac_vap_stru *pst_mac_vap);
oal_void  mac_mib_set_rsna_auth_suite(mac_vap_stru *pst_mac_vap, oal_uint8 uc_auth_value);
oal_void  mac_mib_get_authentication_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value);
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value);


#if 0
extern oal_uint32  mac_vap_get_user_wme_info(
                       mac_vap_stru               *pst_vap,
                       wlan_wme_ac_type_enum_uint8 en_wme_type,
                       mac_wme_param_stru         *pst_wme_info);
extern oal_uint32  mac_vap_set_user_wme_info(
                       mac_vap_stru               *pst_vap,
                       wlan_wme_ac_type_enum_uint8 en_wme_type,
                       mac_wme_param_stru         *pst_wme_info);
#endif
extern oal_uint32  mac_mib_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32 mac_vap_set_bssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid);
extern oal_uint32 mac_vap_set_current_channel(mac_vap_stru *pst_vap,wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel);
extern oal_uint8  mac_vap_get_curr_baserate(mac_vap_stru *pst_mac_ap,oal_uint8 uc_br_idx);
extern oal_void  mac_vap_init_rsna_status(mac_vap_stru *pst_vap, oal_uint32 ul_idx);
extern void mibset_RSNAStatsSTAAddress(oal_uint8 *puckey, mac_vap_stru *pst_vap, oal_uint16 us_idx);
extern void mibset_RSNAStatsSelectedPairwiseCipher(oal_uint8 inp, mac_vap_stru *pst_vap, oal_uint16 us_idx);
extern void mac_mib_set_RSNAAuthenticationSuiteSelected(mac_vap_stru *pst_vap, oal_uint8 inp);
extern void mac_mib_set_RSNAPairwiseCipherSelected(mac_vap_stru *pst_vap, oal_uint8 inp);
extern void mibset_RSNAClearWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap);
extern void mibset_RSNAClearWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap);
extern oal_void  mac_vap_state_change(mac_vap_stru *pst_mac_vap, mac_vap_state_enum_uint8 en_vap_state);
extern oal_uint32 mac_vap_config_vht_ht_mib_by_protocol(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_init_wme_param(mac_vap_stru *pst_mac_vap);

#ifdef _PRE_WLAN_FEATURE_SMPS
extern wlan_mib_mimo_power_save_enum_uint8 mac_mib_get_smps(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32 mac_vap_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_void mac_vap_set_smps(mac_vap_stru *pst_vap, oal_uint8 uc_value);
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
extern oal_uint32  mac_vap_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_value);
extern oal_uint8  mac_vap_get_uapsd_en(mac_vap_stru *pst_mac_vap);
#endif
extern oal_uint32  mac_vap_init_by_protocol(mac_vap_stru *pst_mac_vap, wlan_protocol_enum_uint8 en_protocol);

extern  oal_bool_enum_uint8 mac_vap_check_bss_cap_info_phy_ap(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap);
extern  mac_wme_param_stru  *mac_get_wmm_cfg(wlan_vap_mode_enum_uint8 en_vap_mode);
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
extern  mac_wme_param_stru  *mac_get_wmm_cfg_multi_user_multi_ac(oal_traffic_type_enum_uint8 en_vap_mode);
#endif
extern oal_void  mac_vap_get_bandwidth_cap(mac_vap_stru *pst_mac_vap, wlan_bw_cap_enum_uint8 *pen_cap);
extern oal_void  mac_vap_change_mib_by_bandwidth(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 en_bandwidth);

extern oal_void  mac_vap_init_rx_nss_by_protocol(mac_vap_stru *pst_mac_vap);
#if 0
#ifdef _PRE_WLAN_DFT_STAT
extern oal_uint32  mac_vap_dft_stat_clear(mac_vap_stru *pst_vap);
#endif
#endif
extern oal_void mac_dec_p2p_num(mac_vap_stru *pst_vap);
extern oal_void mac_inc_p2p_num(mac_vap_stru *pst_vap);
extern oal_void mac_vap_set_p2p_mode(mac_vap_stru *pst_vap, wlan_p2p_mode_enum_uint8 en_p2p_mode);
extern wlan_p2p_mode_enum_uint8 mac_get_p2p_mode(mac_vap_stru *pst_vap);
extern oal_void mac_vap_set_aid(mac_vap_stru *pst_vap, oal_uint16 us_aid);
extern oal_void mac_vap_set_uapsd_cap(mac_vap_stru *pst_vap, oal_uint8 uc_uapsd_cap);
extern oal_void mac_vap_set_assoc_id(mac_vap_stru *pst_vap, oal_uint8 uc_assoc_vap_id);
extern oal_void mac_vap_set_tx_power(mac_vap_stru *pst_vap, oal_uint8 uc_tx_power);
extern oal_void mac_vap_set_al_tx_flag(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag);
extern oal_void mac_vap_set_al_tx_first_run(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag);
extern oal_void mac_vap_set_al_tx_payload_flag(mac_vap_stru *pst_vap, oal_uint8 uc_paylod);
extern oal_uint32 mac_dump_protection(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param);
extern oal_void mac_vap_set_multi_user_idx(mac_vap_stru *pst_vap, oal_uint16 us_multi_user_idx);
#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_void mac_vap_set_uapsd_para(mac_vap_stru *pst_mac_vap, mac_cfg_uapsd_sta_stru *pst_uapsd_info);
#endif
extern oal_void mac_vap_set_wmm_params_update_count(mac_vap_stru *pst_vap, oal_uint8 uc_update_count);
#if 0
extern oal_void mac_vap_set_rifs_tx_on(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_void mac_vap_set_tdls_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_void mac_vap_set_tdls_channel_switch_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value);
#endif
extern oal_void mac_vap_set_11ac2g(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_void mac_vap_set_hide_ssid(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_uint32 mac_vap_clear_app_ie(mac_vap_stru *pst_mac_vap, en_app_ie_type_uint8 en_type);
extern oal_uint32 mac_vap_save_app_ie(mac_vap_stru *pst_mac_vap, oal_app_ie_stru *pst_app_ie, en_app_ie_type_uint8 en_type);
extern oal_void mac_vap_set_rx_nss(mac_vap_stru *pst_vap, oal_uint8 uc_rx_nss);

extern oal_uint32 mac_vap_init_privacy(mac_vap_stru                        *pst_mac_vap,
                                                mac_cfg80211_connect_security_stru     *pst_mac_security_param);

extern oal_uint32 mac_mib_set_wep(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id);
extern oal_bool_enum_uint8 mac_check_auth_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                            oal_uint8 uc_policy);
extern mac_user_stru  *mac_vap_get_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);
extern oal_uint32 mac_vap_add_beacon(mac_vap_stru * pst_mac_vap, mac_beacon_param_stru * pst_beacon_param);
extern oal_uint32 mac_vap_add_key(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_key_id, mac_key_params_stru *pst_key);
extern oal_uint8 mac_vap_get_default_key_id(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8  uc_key_index);
extern oal_uint32 mac_vap_set_default_mgmt_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index);
extern void mac_vap_init_user_security_port(mac_vap_stru  *pst_mac_vap,
                                        mac_user_stru *pst_mac_user);
extern oal_uint32 mac_vap_set_beacon(mac_vap_stru * pst_mac_vap, mac_beacon_param_stru * pst_beacon_param);
extern oal_uint8* mac_vap_get_mac_addr(mac_vap_stru *pst_mac_vap);
#ifdef _PRE_WLAN_FEATURE_11R
extern oal_uint32 mac_mib_init_ft_cfg(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mde);
extern oal_uint32 mac_mib_get_md_id(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_mdid);
#if 0
extern oal_uint32 mac_vap_set_pmksa(mac_vap_stru *pst_mac_vap, mac_pmksa_stru *pst_mac_pmksa);
extern oal_uint32 mac_vap_del_pmksa(mac_vap_stru *pst_mac_vap, mac_pmksa_stru *pst_mac_pmksa);
extern oal_uint32 mac_vap_flush_pmksa(mac_vap_stru *pst_mac_vap);
extern mac_pmkid_info_stu *mac_vap_get_pmksa(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid);
#endif
#endif //_PRE_WLAN_FEATURE_11R
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_vap.h */
