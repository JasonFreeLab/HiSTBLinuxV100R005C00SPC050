/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_user.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   : mac_user.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_USER_H__
#define __MAC_USER_H__

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
#include "wlan_spec.h"
#include "wlan_types.h"
#include "wlan_mib.h"
#include "mac_frame.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_USER_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MAC_ACTIVE_USER_IDX_BMAP_LEN        ((WLAN_ACTIVE_USER_MAX_NUM >> 3) + 1)   /* 活跃用户索引位图 */
#define MAC_INVALID_RA_LUT_IDX              WLAN_ACTIVE_USER_MAX_NUM                /* 不可用的RA LUT IDX */
#define MAC_USER_INIT_STREAM        1
#define MAC_INVALID_USER_ID         0xffff   /* 无效的user idx */

#define MAC_USER_FREED              0xff         /* USER资源未申请 */
#define MAC_USER_ALLOCED            0x5a         /* USER已被申请 */

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
/*****************************************************************************
  2.1 REKEY_OFFLOAD宏定义
*****************************************************************************/
#define MAC_REKEY_OFFLOAD_KCK_LEN              16
#define MAC_REKEY_OFFLOAD_KEK_LEN              16
#define MAC_REKEY_OFFLOAD_REPLAY_COUNTER_LEN   8
#endif

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
/* user tx参数，从架构分析文档获得成员 */
typedef struct
{
    wlan_security_txop_params_stru       st_security;
}mac_user_tx_param_stru;

typedef struct
{
    oal_uint8        uc_rs_nrates;                                 /* 个数 */
    oal_uint8        auc_rs_rates[WLAN_RATE_MAXSIZE];              /* 速率 */
}mac_rate_stru;


typedef struct
{
    oal_uint32  bit_spectrum_mgmt       : 1,        /* 频谱管理: 0=不支持, 1=支持 */
                bit_qos                 : 1,        /* QOS: 0=非QOS站点, 1=QOS站点 */
                bit_barker_preamble_mode: 1,        /* 供STA保存BSS中站点是否都支持short preamble， 0=支持， 1=不支持 */
                bit_apsd                : 1,        /* 自动节能: 0=不支持, 1=支持 *//* 目前bit_apsd只有写没有读，wifi联盟已自己定义了WMM节能IE代替cap apsd功能 ,此处预留为后续可能出的兼容性问题提供接口 */
                bit_pmf_active          : 1,        /* 管理帧加密使能开关*/
                bit_resv                : 27;
}mac_user_cap_info_stru;

/* user下ht相关信息 */
typedef struct
{
    /* ht cap */
    oal_bool_enum_uint8 en_ht_capable;                                /* HT capable              */
    oal_uint8           uc_max_rx_ampdu_factor;                       /* Max AMPDU Rx Factor     */
    oal_uint8           uc_min_mpdu_start_spacing;                    /* Min AMPDU Start Spacing */
    oal_uint8           uc_htc_support;                               /* HTC 域支持              */

    oal_uint16          bit_ldpc_coding_cap         : 1,              /* LDPC 编码 capability    */
                        bit_supported_channel_width : 1,              /* STA 支持的带宽   0: 20Mhz, 1: 20/40Mhz  */
                        bit_sm_power_save           : 2,              /* SM 省电模式             */
                        bit_ht_green_field          : 1,              /* 绿野模式                */
                        bit_short_gi_20mhz          : 1,              /* 20M下短保护间隔         */
                        bit_short_gi_40mhz          : 1,              /* 40M下短保护间隔         */
                        bit_tx_stbc                 : 1,              /* Indicates support for the transmission of PPDUs using STBC */
                        bit_rx_stbc                 : 2,              /* 支持 Rx STBC            */
                        bit_ht_delayed_block_ack    : 1,              /* Indicates support for HT-delayed Block Ack opera-tion. */
                        bit_max_amsdu_length        : 1,              /* Indicates maximum A-MSDU length. */
                        bit_dsss_cck_mode_40mhz     : 1,              /* 40M下 DSSS/CCK 模式     0:不使用 40M dsss/cck, 1: 使用 40M dsss/cck */
                        bit_resv                    : 1,
                        bit_forty_mhz_intolerant    : 1,              /* Indicates whether APs receiving this information or reports of this informa-tion are required to prohibit 40 MHz transmissions */
                        bit_lsig_txop_protection    : 1;              /* 支持 L-SIG TXOP 保护    */

    oal_uint8           uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN];   /* Rx MCS bitmask */

    /* ht operation, VAP是STA, user是AP独有 */
    oal_uint8           uc_primary_channel;

    oal_uint8           bit_secondary_chan_offset             : 2,
                        bit_sta_chan_width                    : 1,
                        bit_rifs_mode                         : 1,
                        bit_HT_protection                     : 2,
                        bit_nongf_sta_present                 : 1,
                        bit_obss_nonht_sta_present            : 1;

    oal_uint8           bit_dual_beacon                       : 1,
                        bit_dual_cts_protection               : 1,
                        bit_secondary_beacon                  : 1,
                        bit_lsig_txop_protection_full_support : 1,
                        bit_pco_active                        : 1,
                        bit_pco_phase                         : 1,
                        bit_resv6                             : 2;

    oal_uint8           auc_resv[1];

    oal_uint8           auc_basic_mcs_set[16];

	oal_uint32          bit_imbf_receive_cap                :   1,  /*隐式TxBf接收能力*/
                        bit_receive_staggered_sounding_cap  :   1,  /*接收交错探测帧的能力*/
                        bit_transmit_staggered_sounding_cap :   1,  /*发送交错探测帧的能力*/
                        bit_receive_ndp_cap                 :   1,  /*接收NDP能力*/
                        bit_transmit_ndp_cap                :   1,  /*发送NDP能力*/
                        bit_imbf_cap                        :   1,  /*隐式TxBf能力*/
                        bit_calibration                     :   2,  /*0=不支持，1=站点可以用CSI报告相应校准请求，但不能发起校准，2=保留，3=站点可以发起，也可以相应校准请求*/
                        bit_exp_csi_txbf_cap                :   1,  /*应用CSI反馈进行TxBf的能力*/
                        bit_exp_noncomp_txbf_cap            :   1,  /*应用非压缩矩阵进行TxBf的能力*/
                        bit_exp_comp_txbf_cap               :   1,  /*应用压缩矩阵进行TxBf的能力*/
                        bit_exp_csi_feedback                :   2,  /*0=不支持，1=延迟反馈，2=立即反馈，3=延迟和立即反馈*/
                        bit_exp_noncomp_feedback            :   2,  /*0=不支持，1=延迟反馈，2=立即反馈，3=延迟和立即反馈*/
                        bit_exp_comp_feedback               :   2,  /*0=不支持，1=延迟反馈，2=立即反馈，3=延迟和立即反馈*/
                        bit_min_grouping                    :   2,  /*0=不分组，1=1,2分组，2=1,4分组，3=1,2,4分组*/
                        bit_csi_bfer_ant_number             :   2,  /*CSI反馈时，bfee最多支持的beamformer天线数，0=1Tx天线探测，1=2Tx天线探测，2=3Tx天线探测，3=4Tx天线探测*/
                        bit_noncomp_bfer_ant_number         :   2,  /*非压缩矩阵反馈时，bfee最多支持的beamformer天线数，0=1Tx天线探测，1=2Tx天线探测，2=3Tx天线探测，3=4Tx天线探测*/
                        bit_comp_bfer_ant_number            :   2,  /*压缩矩阵反馈时，bfee最多支持的beamformer天线数，0=1Tx天线探测，1=2Tx天线探测，2=3Tx天线探测，3=4Tx天线探测*/
                        bit_csi_bfee_max_rows               :   2,  /*bfer支持的来自bfee的CSI显示反馈的最大行数*/
                        bit_channel_est_cap                 :   2,  /*信道估计的能力，0=1空时流，依次递增*/
                        bit_reserved                        :   3;
}mac_user_ht_hdl_stru;

typedef struct
{
oal_uint16              us_max_mcs_1ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_2ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_3ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_4ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_5ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_6ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_7ss : 2,                             /* 一个空间流的MCS最大支持MAP */
                        us_max_mcs_8ss : 2;                             /* 一个空间流的MCS最大支持MAP */
}mac_max_mcs_map_stru;

typedef mac_max_mcs_map_stru mac_tx_max_mcs_map_stru;
typedef mac_max_mcs_map_stru mac_rx_max_mcs_map_stru;

typedef struct
{
    oal_uint16  us_max_mpdu_length;
    oal_uint16  us_basic_mcs_set;

    oal_uint32  bit_max_mpdu_length         : 2,
                bit_supported_channel_width : 2,
                bit_rx_ldpc                 : 1,
                bit_short_gi_80mhz          : 1,
                bit_short_gi_160mhz         : 1,
                bit_tx_stbc                 : 1,
                bit_rx_stbc                 : 3,
                bit_su_beamformer_cap       : 1,                       /* SU bfer能力，要过AP认证，必须填1 */
                bit_su_beamformee_cap       : 1,                       /* SU bfee能力，要过STA认证，必须填1 */
                bit_num_bf_ant_supported    : 3,                       /* SU时，最大接收NDP的Nsts，最小是1 */
                bit_num_sounding_dim        : 3,                       /* SU时，表示Nsts最大值，最小是1 */
                bit_mu_beamformer_cap       : 1,                       /* 不支持，set to 0 */
                bit_mu_beamformee_cap       : 1,                       /* 不支持，set to 0 */
                bit_vht_txop_ps             : 1,
                bit_htc_vht_capable         : 1,
                bit_max_ampdu_len_exp       : 3,
                bit_vht_link_adaptation     : 2,
                bit_rx_ant_pattern          : 1,
                bit_tx_ant_pattern          : 1,
                bit_resv1                   : 2;                       /* 解析vht Capabilities IE: VHT Capabilities Info field */

    mac_tx_max_mcs_map_stru     st_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru     st_rx_max_mcs_map;

    oal_uint16  bit_rx_highest_rate : 13,
                bit_resv2           : 3;
    oal_uint16  bit_tx_highest_rate : 13,
                bit_resv3           : 3;                                /* 解析vht Capabilities IE: VHT Supported MCS Set field */

    oal_bool_enum_uint8 en_vht_capable;                                /* VHT capable */

    /* vht operation只有是ap的情况下有 */
    oal_uint8           uc_channel_width;                              /* 解析VHT Operation IE */
                                                                       /* uc_channel_width的取值，0 -- 20/40M, 1 -- 80M, 2 -- 160M */
    oal_uint8           uc_channel_center_freq_seg0;
    oal_uint8           uc_channel_center_freq_seg1;
} mac_vht_hdl_stru;

/* user结构体，对SA Query流程信息的保存结构 */
typedef struct
{
    oal_uint32          ul_sa_query_count;                          /* number of pending SA Query requests, 0 = no SA Query in progress */
    oal_uint32          ul_sa_query_start_time;                     /* sa_query 流程开始时间,单位ms */
    oal_uint16          us_sa_query_trans_id;                       /* trans id */
    oal_uint8           auc_resv[2];
    frw_timeout_stru    st_sa_query_interval_timer;                 /* SA Query 间隔定时器，相关dot11AssociationSAQueryRetryTimeout */
}mac_sa_query_stru;

typedef struct
{
    oal_uint8               uc_qos_info;                                /* 关联请求中的WMM IE的QOS info field */
    oal_uint8               uc_max_sp_len;                              /* 从qos info字段中提取翻译的最大服务长度*/
    oal_uint8               auc_resv[2];
    oal_uint8               uc_ac_trigger_ena[WLAN_WME_AC_BUTT];    /* 4个AC的trigger能力 */
    oal_uint8               uc_ac_delievy_ena[WLAN_WME_AC_BUTT];    /* 4个AC的delivery能力 */
}mac_user_uapsd_status_stru;

/* 用户与AP的关联状态枚举 */
typedef enum
{
    MAC_USER_STATE_AUTH_COMPLETE   = 1,
    MAC_USER_STATE_AUTH_KEY_SEQ1   = 2,
    MAC_USER_STATE_ASSOC           = 3,

    MAC_USER_STATE_BUTT            = 4
}hmac_user_asoc_state_enum;
typedef oal_uint8 mac_user_asoc_state_enum_uint8;

/* 802.1X-port 状态结构体*/
/* 1X端口状态说明:                                                  */
/* 1) portvalid && keydone 都是 TRUE: 表示端口处于合法状态          */
/* 2) portvalid == TRUE && keydone == FALSE:表示端口处于未知状态    */
/*                                     密钥还未生效                 */
/* 3) portValid == FALSE && keydone== TRUE:表示端口处于非法状态     */
/*                                      密钥获取失败                */
/* 4) portValid && keyDone are FALSE: 表示端口处于合法状态          */
/*                                          密钥还未生效            */

typedef struct
{
    oal_bool_enum_uint8             keydone;                      /*端口合法性是否允许测试*/
    oal_bool_enum_uint8             portvalid;                    /*端口合法性标识*/
    oal_uint8                       auc_resv0[2];
}mac_8021x_port_status_stru;


/*供AP查看STA是否被统计到对应项*/
typedef struct
{
    oal_uint8             bit_no_short_slot_stats_flag     :1;      /*指示user是否被统计到no short slot num中, 0表示未被统计， 1表示已被统计*/
    oal_uint8             bit_no_short_preamble_stats_flag :1;      /*指示user是否被统计到no short preamble num中*/
    oal_uint8             bit_no_erp_stats_flag            :1;      /*指示user是否被统计到no erp num中*/
    oal_uint8             bit_no_ht_stats_flag             :1;      /*指示user是否被统计到no ht num中*/
    oal_uint8             bit_no_gf_stats_flag             :1;      /*指示user是否被统计到no gf num中*/
    oal_uint8             bit_20M_only_stats_flag          :1;      /*指示user是否被统计到no 20M only num中*/
    oal_uint8             bit_no_40dsss_stats_flag         :1;      /*指示user是否被统计到no 40dsss num中*/
    oal_uint8             bit_no_lsig_txop_stats_flag      :1;      /*指示user是否被统计到no lsig txop num中*/

    oal_uint8             auc_resv0[3];
}mac_user_stats_flag_stru;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
typedef struct
{
    oal_bool_enum_uint8     en_tx_flg;
    oal_bool_enum_uint8     en_rx_flg;
    oal_uint8               uc_tx_protocol;
    oal_uint8               uc_rx_protocol;
}mac_user_track_txrx_protocol_stru;

typedef struct
{
    frw_timeout_stru        st_txrx_param_timer;/* 上报定时器 */
}mac_user_track_ctx_stru;
#endif
/* AP侧keepalive活动的控制结构体 */
typedef struct
{
    oal_uint8             uc_keepalive_count_ap;                  /* AP定时保活检测操作计数器 */
    oal_uint8             uc_timer_to_keepalive_count;            /* 复用aging timer/STA省电模式定时清醒策略，定时发送keepalive帧的计数器*/
    oal_uint8             uc_delay_flag;                          /* 标志用户进入睡眠状态或者其他不能马上收帧反馈的状态 */

    oal_uint8             auc_resv[1];
}mac_user_keepalive;
/*密钥管理结构体*/
typedef struct
{
    wlan_ciper_protocol_type_enum_uint8     en_cipher_type;
    oal_uint8                               uc_default_index;                       /* 默认索引 */
    oal_uint8                               uc_igtk_key_index;                      /* igtk索引 */
    oal_uint8                               bit_gtk       :1,                       /* 指示RX GTK的槽位，02使用 */
                                            bit_rsv       :7;
    wlan_priv_key_param_stru                ast_key[WLAN_NUM_TK + WLAN_NUM_IGTK];   /* key缓存 */
    oal_uint8                               uc_last_gtk_key_idx;                      /* igtk索引 */
    oal_uint8                               auc_reserved[1];
}mac_key_mgmt_stru;

/* histream属性 */
#ifdef _PRE_WLAN_FEATURE_HISTREAM
/* hidevice设备类型 */
typedef enum
{

    MAC_HIDEVICE_NONE     =  0,        /* 非hidevice设备 */
    MAC_HIDEVICE_HAC      =  1,        /* 家庭接入中心设备home access center */
    MAC_HIDEVICE_WMT      =  2,        /* 手持无线多媒体终端设备 */
    MAC_HIDEVICE_REPEATER =  3,        /* 无线中继 */
    MAC_HIDEVICE_CAMERA   =  4,        /* 无线摄像头设备 */
    MAC_HIDEVICE_MAX_TYPE_NUM
}mac_hidevice_type;
typedef oal_uint8 mac_hidevice_type_enum_uint8;

typedef struct
{
    mac_hidevice_type_enum_uint8     en_hidevice_type;        /* 设备类型 */
    oal_uint8                        auc_resv[3];
#if 0
    oal_uint8                        uc_udp_filter_num;       /* 开启udp过滤,0表示不过滤 */
    oal_uint16                       aus_udp_port[8];         /* 有效udp端口列表 */
    oal_uint8                        uc_tcp_filter_num;       /* 开启tcp过滤,0表示不过滤 */
    oal_uint16                       aus_tcp_port[8];         /* 有效tcp端口列表 */
#endif
}mac_histream_stru;
#endif //_PRE_WLAN_FEATURE_HISTREAM

/* 空间流信息结构体 */
typedef struct
{
    oal_uint16            us_user_idx;
    oal_uint8             uc_avail_num_spatial_stream;            /* Tx和Rx支持Nss的交集,供算法调用 */
    oal_uint8             uc_num_spatial_stream;                  /* 用户支持的空间流个数 */

}mac_user_nss_stru;

/* opmode信息结构体 */
typedef struct
{
    oal_uint16              us_user_idx;
    oal_uint8               uc_avail_num_spatial_stream;            /* Tx和Rx支持Nss的交集,供算法调用 */
    oal_uint8               uc_avail_bf_num_spatial_stream;         /* 用户支持的Beamforming空间流个数 */
    oal_uint8               uc_frame_type;
    wlan_bw_cap_enum_uint8  en_avail_bandwidth;                     /* 用户和VAP带宽能力交集,供算法调用 */
    wlan_bw_cap_enum_uint8  en_cur_bandwidth;                       /* 默认值与en_avail_bandwidth相同,供算法调用修改 */

    oal_uint8             auc_resv[1];
}mac_user_opmode_stru;

typedef struct mac_key_params_tag
{
    oal_uint8 auc_key[OAL_WPA_KEY_LEN];
    oal_uint8 auc_seq[OAL_WPA_SEQ_LEN];
    oal_int32  key_len;
    oal_int32  seq_len;
    oal_uint32 cipher;
}mac_key_params_stru;

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
typedef struct _mac_rekey_offload_stru
{
    oal_uint8   auc_kck[MAC_REKEY_OFFLOAD_KCK_LEN];
    oal_uint8   auc_kek[MAC_REKEY_OFFLOAD_KEK_LEN];
    oal_uint8   auc_replay_ctr[MAC_REKEY_OFFLOAD_REPLAY_COUNTER_LEN];
}mac_rekey_offload_stru;
#endif

/* mac user结构体, hmac_user_stru和dmac_user_stru公共部分 */
typedef struct
{
    /* 当前VAP工作在AP或STA模式，以下字段为user是STA或AP时公共字段，新添加字段请注意!!! */
    oal_dlist_head_stru                     st_user_dlist;                          /* 用于hash双向链中的双向链表 */
    oal_uint16                              us_user_hash_idx;                       /* 索引值(关联) */
    oal_uint8                               auc_user_mac_addr[WLAN_MAC_ADDR_LEN];   /* user对应的MAC地址 */
    oal_uint16                              us_assoc_id;                            /* user对应资源池索引值; user为STA时，表示填在管理帧中的AID，值为用户的资源池索引值1~32(协议规定范围为1~2007)*/
    oal_bool_enum_uint8                     en_is_multi_user;
    oal_uint8                               uc_vap_id;                              /* vap ID */
    oal_uint8                               uc_device_id;                           /* 设备ID */
    oal_uint8                               uc_chip_id;                             /* 芯片ID */
    wlan_protocol_enum_uint8                en_protocol_mode;                       /* 用户工作协议 */
    wlan_protocol_enum_uint8                en_avail_protocol_mode;                 /* 用户和VAP协议模式交集, 供算法调用 */
    wlan_protocol_enum_uint8                en_cur_protocol_mode;                   /* 默认值与en_avail_protocol_mode值相同, 供算法调用修改 */

    oal_uint8                               uc_avail_num_spatial_stream;            /* Tx和Rx支持Nss的交集,供算法调用 */
    oal_uint8                               uc_num_spatial_stream;                  /* 用户支持的空间流个数 */
    oal_uint8                               uc_avail_bf_num_spatial_stream;         /* 用户支持的Beamforming空间流个数 */
    oal_bool_enum_uint8                     en_port_valid;                          /* 802.1X端口合法性标识 */
    oal_uint8                               uc_is_user_alloced;                     /* 标志此user资源是否已经被申请 */

    mac_rate_stru                           st_avail_op_rates;                      /* 用户和VAP可用的11a/b/g速率交集，供算法调用 */
    mac_user_tx_param_stru                  st_user_tx_info;                        /* TX相关参数 */
    wlan_bw_cap_enum_uint8                  en_bandwidth_cap;                       /* 用户带宽能力信息 */
    wlan_bw_cap_enum_uint8                  en_avail_bandwidth;                     /* 用户和VAP带宽能力交集,供算法调用 */
    wlan_bw_cap_enum_uint8                  en_cur_bandwidth;                       /* 默认值与en_avail_bandwidth相同,供算法调用修改 */
    oal_uint8                               uc_drop_ncw;                            /* notify channel width action帧上报开关 */

    mac_user_asoc_state_enum_uint8          en_user_asoc_state;                     /* 用户关联状态 */

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    mac_histream_stru                       st_histream_info;                       /* HiStream信息 */
#endif //_PRE_WLAN_FEATURE_HISTREAM

    mac_user_cap_info_stru                  st_cap_info;                            /* user基本能力信息位 */
    mac_user_ht_hdl_stru                    st_ht_hdl;                              /* HT capability IE和 operation IE的解析信息 */
    mac_vht_hdl_stru                        st_vht_hdl;                             /* VHT capability IE和 operation IE的解析信息 */

    mac_key_mgmt_stru                       st_key_info;
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    mac_rekey_offload_stru                  st_rekey_offload; /* 上层下发的rekey info */
    oal_bool_enum_uint8                     en_rekey_info_exist;/* rekeyinfo是否已经被下发到DMAC */   
    oal_uint8                               auc_resv[3];
#endif

    /* 当前VAP工作在AP模式，以下字段为user是STA时独有字段，新添加字段请注意!!! */

    /* 当前VAP工作在STA模式，以下字段为user是AP时独有字段，新添加字段请注意!!! */
}mac_user_stru;

#ifdef _PRE_WLAN_FEATURE_UAPSD

#define MAC_USR_UAPSD_EN     0x01//U-APSD使能
#define MAC_USR_UAPSD_TRIG   0x02//U-APSD可以被trigger
#define MAC_USR_UAPSD_SP     0x04//u-APSD在一个Service Period处理中

/*AC是trigge_en的且用户当前处于trigger状态，can be trigger*/
#define MAC_USR_UAPSD_AC_CAN_TIGGER(_ac,_dmac_usr) \
    (((_dmac_usr)->st_uapsd_status.uc_ac_trigger_ena[_ac])&&((_dmac_usr)->uc_uapsd_flag & MAC_USR_UAPSD_TRIG))

/*AC是delivery_en的且用户当前处于trigger状态,can be delivery*/
#define MAC_USR_UAPSD_AC_CAN_DELIVERY(_ac,_dmac_usr) \
    (((_dmac_usr)->st_uapsd_status.uc_ac_delievy_ena[_ac])&&((_dmac_usr)->uc_uapsd_flag & MAC_USR_UAPSD_TRIG))

#define MAC_USR_UAPSD_USE_TIM(_dmac_usr) \
    (MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_BK, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_BE, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_VI, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_VO, _dmac_usr))
#endif

#define MAC_11I_ASSERT(_cond, _errcode) do{\
if(!(_cond))\
{\
    return _errcode;\
}\
}while(0);

#define MAC_11I_IS_PTK(en_macaddr_is_zero, en_pairwise)   ((OAL_TRUE != en_macaddr_is_zero) && (OAL_TRUE == en_pairwise))


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : mac_user_get_ra_lut_index
 功能描述  : 获取用户对应的ra lut index
 输入参数  : puc_index_table: 查找表数组
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_user_get_ra_lut_index(oal_uint8 *puc_index_table)
{
    return oal_get_lut_index(puc_index_table,
                             WLAN_ACTIVE_USER_IDX_BMAP_LEN,
                             WLAN_ACTIVE_USER_MAX_NUM);
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/*****************************************************************************
 函 数 名  : mac_user_get_ra_lut_index_proxysta
 功能描述  : 在开启Proxy STA特性的情况下，AP0关联的uer id只能为0~15(但只能关联15个)，所以从两个字节中取一个bit
 输入参数  : 第2个入参值为1，第3个入参为15
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_user_get_ra_lut_index_proxysta(oal_uint8 *puc_index_table)

{
    /* 获取的lut idx应该为0~15 */
    return oal_get_lut_index(puc_index_table,
                        (oal_uint8)WLAN_ASSOC_USER_IDX_BMAP_LEN,
                         (oal_uint16)WLAN_ASSOC_USER_MAX_NUM_SPEC);
}
#endif
/*****************************************************************************
 函 数 名  : mac_user_del_ra_lut_index
 功能描述  : 删除用户对应的ra lut index
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_user_del_ra_lut_index(oal_uint8 *puc_index_table, oal_uint8 uc_ra_lut_index)
{
    oal_del_lut_index(puc_index_table, uc_ra_lut_index);
}


/*****************************************************************************
  10 函数声明
*****************************************************************************/

oal_uint32 mac_user_add_wep_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);
oal_uint32 mac_user_add_rsn_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);
oal_uint32 mac_user_add_bip_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);

extern wlan_priv_key_param_stru *mac_user_get_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_id);

extern oal_uint32  mac_user_init(
                mac_user_stru  *pst_mac_user,
                oal_uint16      us_user_idx,
                oal_uint8      *puc_mac_addr,
                oal_uint8       uc_chip_id,
                oal_uint8       uc_device_id,
                oal_uint8       uc_vap_id);

extern oal_uint32 mac_user_set_port(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_port_valid);

extern oal_void mac_user_avail_bf_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_avail_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_bandwidth_cap(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bandwidth_value);
extern oal_void mac_user_set_bandwidth_info(mac_user_stru *pst_mac_user,
                                                    wlan_bw_cap_enum_uint8 en_avail_bandwidth,
                                                    wlan_bw_cap_enum_uint8 en_cur_bandwidth);
extern oal_void  mac_user_get_sta_cap_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap);
extern oal_void  mac_user_get_ap_opern_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap);
extern oal_uint32  mac_user_update_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bwcap);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  mac_user_change_info_event(
                                    oal_uint8  auc_user_macaddr[],
                                    oal_uint8  uc_vap_id,
                                    oal_uint32 ul_val_old,
                                    oal_uint32 ul_val_new,
                                    oam_module_id_enum_uint16 en_mod,
                                    oam_user_info_change_type_enum_uint8 en_type);
#endif
extern oal_void mac_user_set_assoc_id(mac_user_stru *pst_mac_user, oal_uint16 us_assoc_id);
extern oal_void mac_user_set_avail_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_avail_protocol_mode);
extern oal_void mac_user_set_cur_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_cur_protocol_mode);
extern oal_void mac_user_set_cur_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8  en_cur_bandwidth);
extern oal_void mac_user_set_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_protocol_mode);
extern oal_void mac_user_set_asoc_state(mac_user_stru *pst_mac_user, mac_user_asoc_state_enum_uint8 en_value);
extern oal_void mac_user_set_avail_op_rates(mac_user_stru *pst_mac_user, oal_uint8 uc_rs_nrates, oal_uint8 *puc_rs_rates);
extern oal_void mac_user_set_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl);
extern oal_void mac_user_get_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_set_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_get_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_set_ht_capable(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_ht_capable);
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_void mac_user_set_sm_power_save(mac_user_stru *pst_mac_user, oal_uint8 uc_sm_power_save);
#endif
extern oal_void mac_user_set_pmf_active(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_pmf_active);
extern oal_void mac_user_set_barker_preamble_mode(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_barker_preamble_mode);
extern oal_void mac_user_set_qos(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_qos_mode);
extern oal_void mac_user_set_spectrum_mgmt(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_spectrum_mgmt);
extern oal_void  mac_user_set_apsd(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_apsd);

extern oal_uint32 mac_user_init_key(mac_user_stru *pst_mac_user);
#ifdef _PRE_WLAN_FEATURE_HISTREAM
extern oal_uint32 mac_user_set_histream(mac_user_stru *pst_mac_user, mac_histream_stru *pst_histream_info);
#endif //_PRE_WLAN_FEATURE_HISTREAM
extern oal_uint32 mac_user_set_key(mac_user_stru *pst_multiuser,
                                            wlan_cipher_key_type_enum_uint8 en_keytype,
                                            wlan_ciper_protocol_type_enum_uint8 en_ciphertype,
                                            oal_uint8       uc_keyid);

extern oal_uint32 mac_user_update_wep_key(mac_user_stru *pst_mac_usr, oal_uint16 us_multi_user_idx);
extern oal_bool_enum_uint8 mac_addr_is_zero(oal_uint8 *puc_mac);
extern oal_void*  mac_res_get_mac_user(oal_uint16 us_idx);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_user.h */
