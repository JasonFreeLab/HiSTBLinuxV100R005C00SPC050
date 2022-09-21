/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_dft.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年8月13日
  最近修改   :
  功能描述   : dmac_dft.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月13日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_DFT_H__
#define __DMAC_DFT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "mac_user.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_user.h"
#include "dmac_vap.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DFT_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#define  DMAC_DFT_PHY_STAT_NODE_0_BASE           0   /* phy统计节点0的基准bit，寄存器PHY_STA_01_EN的bit0 */
#define  DMAC_DFT_PHY_STAT_NODE_1_BASE           16  /* phy统计节点1的基准bit，寄存器PHY_STA_01_EN的bit16 */
#define  DMAC_DFT_PHY_STAT_NODE_2_BASE           0   /* phy统计节点2的基准bit，寄存器PHY_STA_23_EN的bit0 */
#define  DMAC_DFT_PHY_STAT_NODE_3_BASE           16  /* phy统计节点3的基准bit，寄存器PHY_STA_23_EN的bit16 */
#define  DMAC_DFT_REPORT_TO_COLLECT_TIMES        100 /* 空口环境类参数上报周期(2s)与采集周期(20ms)的比值 */
#define  DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT  20  /* 空口环境类参数采集周期，20ms */
#define  DMAC_DFT_REPORT_VAP_STAT_TIMEOUT        2000/* 上报vap吞吐相关统计信息周期 */
#define  DMAC_DFT_PHY_INTLAN_GAIN_NUM            8   /* 内置LNA增益数目 */
#define  DMAC_DFT_PHY_VGA_GAIN_NUM               32  /* VGA增益数目 */
#define  DMAC_DFT_VAP_STAT_RATE_TO_KBPS          250 /* 速率单位是kbps，应该是字节数除以周期(2s)再除以1000在乘以8(B/b) */
#define  DMAC_DFT_MAC_CHAN_STAT_PERIOD           20000 /* MAC进行信道空闲时间统计周期，20000us(20ms) */
#define  DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD    10  /* PHY进行信道空闲功率测量的周期，10ms */

#define  DMAC_DFT_MGMT_STAT_INCR(_member)     ((_member)++)
#define  DMAC_DFT_AP_BEACON_MISS_MAX_NUM(_idx, _val, _pul_val)  do {   \
         *_pul_val = ((0xFF << ((_idx) << 3)) & (_val)) >> ((_idx) << 3);  \
         }while(0)

#define  DMAC_DFT_REG_OTA_LEN              1024 /* 寄存器OTA上报的最大限制 */
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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* OTA上报的信息结构体定义(包括内存池，vap，user，队列等等)，将结构体统一定义在此处的目的是便于维护 */

/*****************************************************************************
  结构名  : mem_subpool_dft_stru
  结构说明: ota上报的子内存池结构体
*****************************************************************************/
typedef struct
{
    oal_uint8             uc_sub_pool_id;     /* 子内存池的id */
    oal_uint8             auc_resv[3];
    oal_uint16            us_free_cnt;        /* 本子内存池可用内存块数 */
    oal_uint16            us_total_cnt;       /* 本子内存池内存块总数 */
} mem_subpool_dft_stru;

/* OTA上报的内存池使用情况的结构体，此结构体的修改需要通知SDT相关人员进行同步修改，否则会解析错误 */
typedef struct
{
    oal_uint8                  uc_pool_id;             /* 本内存池的pool id */
    oal_uint8                  uc_subpool_cnt;         /* 本内存池一共有多少子内存池 */
    oal_uint16                 us_max_byte_len;        /* 本内存池可分配内存块最大长度 */
    oal_uint16                 us_mem_used_cnt;        /* 本内存池已用内存块 */
    oal_uint16                 us_mem_total_cnt;       /* 本内存池一共有多少内存块 */

    /* 子内存池的信息 */
    mem_subpool_dft_stru       ast_subpool_table[WLAN_MEM_MAX_SUBPOOL_NUM];
}mem_pool_dft_stru;

/* OTA上报的硬件信息结构体，此结构体的修改需要通知SDT相关人员进行同步修改，否则会解析错误 */
typedef struct
{
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_mac_device_id;                           /* 保存mac device id */
    hal_lpm_state_enum_uint8        uc_curr_state;                              /*当前芯片的低功耗状态*/
    oal_uint32                      ul_core_id;

    hal_rx_dscr_queue_header_stru   ast_rx_dscr_queue[HAL_RX_QUEUE_NUM];
    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue[HAL_TX_QUEUE_NUM];

    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue_fake[HAL_TX_FAKE_QUEUE_NUM][HAL_TX_QUEUE_NUM];
} hal_device_dft_stru;

/* OTA上报的用户队列的结构体，此结构体的修改需要通知SDT相关人员进行同步修改，否则会解析错误 */
typedef struct
{
    dmac_tid_stru                      ast_tx_tid_queue[WLAN_TID_MAX_NUM]; /* 发送tid缓存队列 */

#ifdef _PRE_WLAN_FEATURE_UAPSD
    dmac_user_uapsd_stru               st_uapsd_stru;                      /* 用户的U-APSD节能结构*/
#endif
}dmac_user_queue_info_dft_stru;

/* OTA上报的dmac vap结构体，此结构体的修改需要通知SDT相关人员进行同步修改，否则会解析错误 */
typedef struct
{
    /* 以下元素对应于mac_vap_stru结构中元素 */
    oal_uint8                        uc_vap_id;                                      /* vap ID   *//* 即资源池索引值 */
    oal_uint8                        uc_device_id;                                   /* 设备ID   */
    oal_uint8                        uc_chip_id;                                     /* chip ID  */
    wlan_vap_mode_enum_uint8         en_vap_mode;                                    /* vap模式  */
    oal_uint32                       ul_core_id;
    oal_uint8                        auc_bssid[WLAN_MAC_ADDR_LEN];                   /* BSSID，非MAC地址，MAC地址是mib中的auc_dot11StationID  */
    mac_vap_state_enum_uint8         en_vap_state;                                   /* VAP状态 */
    wlan_protocol_enum_uint8         en_protocol;                                    /* 工作的协议模式 */
    mac_channel_stru                 st_channel;                                     /* vap所在的信道 */
    oal_uint8                        bit_has_user_bw_limit   :   1;                  /* 该vap是否存在user限速 */
    oal_uint8                        bit_vap_bw_limit        :   1;                  /* 该vap是否已限速 */
    oal_uint8                        bit_resv                :   6;
    oal_uint8                        uc_tx_power;                                    /* 传输功率, 单位dBm */
    wlan_p2p_mode_enum_uint8         en_p2p_mode;                                    /* 0:非P2P设备; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
    oal_uint8                        uc_p2p_gocl_hal_vap_id;                         /* p2p go / cl的hal vap id */
    oal_uint16                       us_user_nums;                                   /* VAP下已挂接的用户个数 */
    oal_uint16                       us_multi_user_idx;                              /* 组播用户ID */
    mac_cap_flag_stru                st_cap_flag;
    mac_protection_stru              st_protection;                                  /* 与保护相关变量 */

    /* 以下元素对应于dmac_vap_stru结构中元素 */
    dmac_vap_linkloss_stru           st_linkloss_info;                                  /* linkloss机制相关信息 */
    hal_tx_txop_alg_stru             st_tx_alg;                                         /* 单播数据帧发送参数 */
    hal_tx_txop_alg_stru             st_tx_data_mcast;                                  /* 组播数据帧参数 */
    hal_tx_txop_alg_stru             st_tx_data_bcast;                                  /* 广播数据帧参数*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_ucast[WLAN_BAND_BUTT];                 /* 单播管理帧参数*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_bmcast[WLAN_BAND_BUTT];                /* 组播、广播管理帧参数*/

    oal_uint8                        uc_ps_user_num;                                    /* 处于节能模式的用户的数目，AP模式有效 */
    oal_uint8                        uc_dtim_count;
    oal_uint8                        uc_uapsd_max_depth;                                /* U-APSD节能队列的最大深度*/
    oal_uint8                        uc_resv;
}dmac_vap_dft_stru;

/* OTA上报的dmac user结构体，此结构体的修改需要通知SDT相关人员进行同步修改，否则会解析错误 */
typedef struct
{
    /* 以下元素对应于mac_user_stru结构中元素 */
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

    mac_rate_stru                           st_avail_op_rates;                      /* 用户和VAP可用的11a/b/g速率交集，供算法调用 */
    mac_user_tx_param_stru                  st_user_tx_info;                        /* TX相关参数 */

    wlan_bw_cap_enum_uint8                  en_bandwidth_cap;                       /* 用户带宽能力信息 */
    wlan_bw_cap_enum_uint8                  en_avail_bandwidth;                     /* 用户和VAP带宽能力交集,供算法调用 */
    wlan_bw_cap_enum_uint8                  en_cur_bandwidth;                       /* 默认值与en_avail_bandwidth相同,供算法调用修改 */
    mac_user_asoc_state_enum_uint8          en_user_asoc_state;                     /* 用户关联状态 */

    mac_user_cap_info_stru                  st_cap_info;                            /* user基本能力信息位 */
    mac_user_ht_hdl_stru                    st_ht_hdl;                              /* HT capability IE和 operation IE的解析信息 */
    mac_vht_hdl_stru                        st_vht_hdl;                             /* VHT capability IE和 operation IE的解析信息 */

    mac_key_mgmt_stru                       st_key_info;

    /* 以下元素对应于dmac_user_stru结构中元素 */
    hal_tx_txop_alg_stru                    st_tx_data_mcast;                   /* 组播数据帧参数，预留11k使用 */
    hal_tx_txop_alg_stru                    st_tx_data_bcast;                   /* 广播数据帧参数, 预留11k使用 */

    mac_user_uapsd_status_stru              st_uapsd_status;                    /* uapsd状态 */
    oal_uint8                               uc_lut_index;                       /* user对应的硬件索引，活跃用户id */
    oal_uint8                               uc_uapsd_flag;                      /* STA的U-APSD当前的处理状态 */
    oal_uint8                               uc_max_key_index;                   /* 最大ptk index */
    oal_uint8                               uc_resv;

    dmac_user_rate_info_stru                st_user_rate_info;
}dmac_user_dft_stru;

#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void dmac_dft_report_dmac_vap_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_user_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_event_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_memory_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_mac_hardware_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_queue_info(mac_vap_stru  *pst_mac_vap);

#endif

extern oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx);
extern oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap);
extern oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap);

extern oal_uint32  dmac_dft_start_report_vap_stat(mac_vap_stru *pst_mac_vap);
extern oal_uint32  dmac_dft_stop_report_vap_stat(mac_vap_stru *pst_mac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  dmac_dft_clear_usr_queue_stat(dmac_user_stru  *pst_dmac_user);
extern oal_uint32  dmac_dft_report_usr_queue_stat(dmac_user_stru  *pst_dmac_user);
#endif
extern oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev);
extern oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type);
extern oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat);
extern oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch);
extern oal_void dmac_dft_print_mac_phy_rf(mac_device_stru *pst_mac_dev);

extern oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta);

#endif

#ifdef _PRE_DEBUG_MODE

extern oal_uint32  dmac_dft_report_all_ampdu_stat(dmac_user_stru  *pst_dmac_user,
                                                   oal_uint8        uc_param);



extern oal_uint32  dmac_dft_report_ampdu_stat(dmac_tid_stru  *pst_tid,
                                                      oal_uint8      auc_macaddr[],
                                                      oal_uint8       uc_param);
#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_dft.h */
