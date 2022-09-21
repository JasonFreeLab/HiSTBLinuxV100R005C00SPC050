/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wlan_spec.h
  版 本 号   : 初稿
  作    者   : 张志明
  生成日期   : 2014年10月10日
  最近修改   :
  功能描述   : 1151 wlan产品规格宏定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月10日
    作    者   : 张志明
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WLAN_SPEC_1151_H__
#define __WLAN_SPEC_1151_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"

/*****************************************************************************
  0.0 定制化变量声明
*****************************************************************************/
extern oal_uint16   g_us_wlan_assoc_user_max_num;    /* 关联用户的最大个数 */
extern oal_uint32   g_ul_wlan_vap_max_num_per_device;

/*TBD，初始化放入Dmac_main中*/

/*****************************************************************************
  0.1.4 热点入网功能
*****************************************************************************/
/* 关联用户的最大个数 启动Proxy STA时，ap最大关联用户数为15，关闭时为32*/
#define WLAN_ASSOC_USER_MAX_NUM_SPEC        g_us_wlan_assoc_user_max_num

/* 作为P2P GO 允许关联最大用户数，在1151 中不使用，仅仅作为UT 编译使用 */
#define WLAN_P2P_GO_ASSOC_USER_MAX_NUM_SPEC 0

#ifdef _PRE_WIFI_DMT
#define WLAN_USER_AGING_TIME                    witp_dmt_get_user_aging_time()
#else
/* 单位ms */
#define WLAN_USER_AGING_TIME                    (300 * 1000)
#define WLAN_P2PGO_USER_AGING_TIME              (30 * 1000)     /* 30S */
#endif

/*****************************************************************************
  0.5.3 AMSDU功能
*****************************************************************************/
#ifdef _PRE_WIFI_DMT
#define WLAN_AMSDU_MAX_NUM                  witp_dmt_get_amsdu_aggr_num()
#else
/* 一个amsdu下允许拥有的msdu的最大个数 */
#define WLAN_AMSDU_MAX_NUM                  25
#endif

/*****************************************************************************
  0.8.8  多AP特性
*****************************************************************************/
#define WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC        g_ul_wlan_vap_max_num_per_device    /* 每个device支持vap的最大个数=最大业务VAP数目+配置VAP数量 */

/* 整个BOARD支持的最大的VAP数目 */
#define WLAN_VAP_SUPPOTR_MAX_NUM_SPEC       (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)   /* 5个或者18个 */

/* 整个BOARD支持的最大业务VAP的数目 */
#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_SPEC     (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * (WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC -1))

#define WLAN_MAX_MULTI_USER_NUM_SPEC              (WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_SPEC)

/*****************************************************************************
  1.0 WLAN芯片对应的spec
*****************************************************************************/
/* 每个board支持chip的最大个数放入平台 */
/* 每个chip支持device的最大个数放入平台 */
/* 最多支持的MAC硬件设备个数放入平台 */
/* 整个BOARD支持的最大的device数目放入平台 */

/*****************************************************************************
  1.3 oam相关的spec
*****************************************************************************/
/*oam 放入平台 */

/*****************************************************************************
  1.4 mem对应的spec
*****************************************************************************/
/*****************************************************************************
  1.4.1 内存池规格
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.2 共享描述符内存池配置信息
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.3 共享管理帧内存池配置信息
*****************************************************************************/
/*内存 spec 放入平台 */


/*****************************************************************************
  1.4.4 共享数据帧内存池配置信息
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.5 本地内存池配置信息
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.6 事件结构体内存池
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.7 用户内存池
*****************************************************************************/
/*****************************************************************************
  1.4.8 MIB内存池  TBD :最终个子池的空间大小及个数需要重新考虑
*****************************************************************************/
/*内存 spec 放入平台 */

/*****************************************************************************
  1.4.9 netbuf内存池  TBD :最终个子池的空间大小及个数需要重新考虑
*****************************************************************************/

/*内存 spec 放入平台 */


/*****************************************************************************
  1.4.9.1 sdt netbuf内存池
*****************************************************************************/
/*内存 spec 放入平台 */


/*****************************************************************************
  1.5 frw相关的spec
*****************************************************************************/
/*事件调度 spec 放入平台 */


/*****************************************************************************
  2 宏定义，分类和DR保持一致
*****************************************************************************/
/*****************************************************************************
  2.1 基础协议/定义物理层协议类别的spec
*****************************************************************************/
/*****************************************************************************
  2.1.1 扫描侧STA 功能
*****************************************************************************/
/* TBD 一次可以扫描的最大BSS个数，两个规格可以合并*/
#define WLAN_SCAN_REQ_MAX_BSSID                 2
#define WLAN_SCAN_REQ_MAX_SSID                  2

/* TBD 扫描延迟,us 未使用，可删除*/
#define WLAN_PROBE_DELAY_TIME                   10

/* 扫描时，最小的信道驻留时间，单位ms，变量命名有误*/
#define WLAN_DEFAULT_SCAN_MIN_TIME              110
/* 扫描时，最大的信道驻留时间，单位ms，变量命名有误*/
#define WLAN_DEFAULT_SCAN_MAX_TIME              500

/* 一个device所记录的扫描到的最大BSS个数*/
#define WLAN_MAX_SCAN_BSS_NUM                   32
/* 一个信道下记录扫描到的最大BSS个数 */
#define WLAN_MAX_SCAN_BSS_PER_CH                8
/* SSID最大长度, +1为\0预留空间 */
#define WLAN_SSID_MAX_LEN                   (32 + 1)

#define WLAN_DEFAULT_FG_SCAN_COUNT_PER_CHANNEL         2       /* 前景扫描每信道扫描次数 */
#define WLAN_DEFAULT_BG_SCAN_COUNT_PER_CHANNEL         1       /* 背景扫描每信道扫描次数 */
#define WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL  1       /* 每次信道扫描发送probe req帧的次数 */

#define WLAN_DEFAULT_MAX_TIME_PER_SCAN                 7000  /* 扫描的默认的最大执行时间，超过此时间，做超时处理 */

/* Beacon Interval参数 */
#define WLAN_BEACON_INTVAL_MAX              3500            /* max beacon interval, ms */
#define WLAN_BEACON_INTVAL_MIN              40              /* min beacon interval */
#define WLAN_BEACON_INTVAL_DEFAULT          100             /* min beacon interval */
/*AP IDLE状态下beacon interval值*/
#define WLAN_BEACON_INTVAL_IDLE             1000

/*TBD 扫描时，主被动扫描定时时间，单位ms，变量命名有误*/
#ifdef _PRE_WIFI_DMT
#define WLAN_DEFAULT_ACTIVE_SCAN_TIME           40
#define WLAN_DEFAULT_PASSIVE_SCAN_TIME          800
#else
#define WLAN_DEFAULT_ACTIVE_SCAN_TIME           20
#define WLAN_DEFAULT_PASSIVE_SCAN_TIME          360
#endif

/*****************************************************************************
  2.1.3 STA入网功能
*****************************************************************************/
/* STA可同时关联的最大AP个数*/
#define WLAN_ASSOC_AP_MAX_NUM               2

/* TBD，入网延迟，单位ms。变量需要修订*/
#ifdef _PRE_WIFI_DMT
#define WLAN_JOIN_START_TIMEOUT                 10000
#define WLAN_AUTH_TIMEOUT                       500
#define WLAN_ASSOC_TIMEOUT                      500
#else
#define WLAN_JOIN_START_TIMEOUT                 10000
#define WLAN_AUTH_TIMEOUT                       512
#define WLAN_ASSOC_TIMEOUT                      512
#endif


#define WLAN_LINKLOSS_OFFSET_11H                5  /* 切信道时的延迟 */
#define WLAN_LINKLOSS_MIN_THRESHOLD             10 /* linkloss门限最小最低值 */

/*****************************************************************************
  2.1.4 热点入网功能
*****************************************************************************/
/* 可配置的最大关联用户数 */
#define WLAN_MAX_ASSOC_USER_CFG             200
/* 关联用户的最大个数 */
#define WLAN_ASSOC_USER_MAX_NUM_LIMIT       32
//#define WLAN_ASSOC_USER_MAX_NUM             32                                      /* 关联用户的最大个数 */

/* 活跃用户的最大个数放入平台 */

/* 活跃用户索引位图 */
#define WLAN_ACTIVE_USER_IDX_BMAP_LEN       ((WLAN_ACTIVE_USER_MAX_NUM + 7)>> 3)
 /* 关联用户索引位图 */
#define WLAN_ASSOC_USER_IDX_BMAP_LEN       ((WLAN_ASSOC_USER_MAX_NUM_SPEC + 7)>> 3)
 /* 不可用的RA LUT IDX */
#define WLAN_INVALID_RA_LUT_IDX             WLAN_ACTIVE_USER_MAX_NUM

/*
 * The 802.11 spec says at most 2007 stations may be
 * associated at once.  For most AP's this is way more
 * than is feasible so we use a default of 128.  This
 * number may be overridden by the driver and/or by
 * user configuration.
 */
#define WLAN_AID_MAX                        2007
#define WLAN_AID_DEFAULT                    128


/* 用户管理超时参数*/
/* 活跃定时器触发周期 */
#define WLAN_USER_ACTIVE_TRIGGER_TIME           1000
/* 老化定时器触发周期 */
#define WLAN_USER_AGING_TRIGGER_TIME            5000
/* 单位ms */
#define WLAN_USER_ACTIVE_TO_INACTIVE_TIME       5000

#ifdef _PRE_WIFI_DMT
/* KeepAlive保活周期，单位ms */
#define WLAN_USER_KEEPALIVE_INTERVAL            (1000)
#define WLAN_USER_KEEPALIVE_WAIT_TIME           (WLAN_USER_AGING_TIME - (WLAN_USER_AGING_TIME >> 2))
#else
/* KeepAlive保活周期，单位ms */
#define WLAN_USER_KEEPALIVE_INTERVAL            (20 * 1000)
#define WLAN_USER_KEEPALIVE_WAIT_TIME           (WLAN_USER_AGING_TIME - (WLAN_USER_AGING_TIME >> 2))     /* KeepAlive保活操作在多久没有数据交互后开始启动 */
#endif

#define WLAN_USER_KEEPALIVE_TRIGGER_TIME        (30 * 1000)       /* keepalive定时器触发周期 单位ms*/
#define WLAN_USER_KEEPALIVE_SEND_NULL           (WLAN_USER_KEEPALIVE_TRIGGER_TIME * 4)   /* 单位ms*/
#define WLAN_GO_USER_KEEPALIVE_SEND_NULL        (15*1000)


#ifdef _PRE_WLAN_REALTIME_CALI
/* realtime calibration周期, 单位ms */
#define WLAN_REALTIME_CALI_INTERVAL             (1000)
#endif

/*****************************************************************************
  2.1.6 保护模式功能
*****************************************************************************/
/*TBD RTS开启门限，实际可删除*/
#define WLAN_RTS_DEFAULT                    512
#define WLAN_RTS_MIN                        1
#define WLAN_RTS_MAX                        2346

/*****************************************************************************
  2.1.7 分片功能
*****************************************************************************/
/* Fragmentation limits */
/* default frag threshold */
#define WLAN_FRAG_THRESHOLD_DEFAULT         1544
/* min frag threshold */
#define WLAN_FRAG_THRESHOLD_MIN             200 /* 为了保证分片数小于16,商用AP 默认500  */
/* max frag threshold */
#define WLAN_FRAG_THRESHOLD_MAX             2346


/*****************************************************************************
  2.1.17 数据速率功能
*****************************************************************************/
/* 速率相关参数 */
/* 一种协议，一种频宽下的最大速率个数 */
#define WLAN_RATE_MAXSIZE                   35

/* 记录支持的速率 */
#define WLAN_SUPP_RATES                         8
/* 用于记录扫描到的ap支持的速率最大个数 */
#define WLAN_MAX_SUPP_RATES                     12

/* 每个用户支持的最大速率集个数 */
#define HAL_TX_RATE_MAX_NUM               4
/*****************************************************************************
  2.2 其他协议/定义MAC 层协议类别的spec
*****************************************************************************/
/*****************************************************************************
  2.2.2 国家码STA功能
*****************************************************************************/
/* 管制类最大个数 */
#define WLAN_MAX_RC_NUM                         20
/* 管制类位图字数 */
#define WLAN_RC_BMAP_WORDS                      2
/* wifi 5G 2.4G全部信道个数 */
#define WLAN_MAX_CHANNEL_NUM                    (29 + 14)

/*****************************************************************************
  2.2.4 WMM功能
*****************************************************************************/
/*STA所用WLAN_EDCA_XXX参数同WLAN_QEDCA_XXX */
/* 清理UT工程后删除 */
#define WLAN_EDCA_TABLE_CWMIN_MIN           1
#define WLAN_EDCA_TABLE_CWMIN_MAX           10
#define WLAN_EDCA_TABLE_CWMAX_MIN           1
#define WLAN_EDCA_TABLE_CWMAX_MAX           10
#define WLAN_EDCA_TABLE_AIFSN_MIN           2
#define WLAN_EDCA_TABLE_AIFSN_MAX           15
#define WLAN_EDCA_TABLE_TXOP_LIMIT_MIN      1
#define WLAN_EDCA_TABLE_TXOP_LIMIT_MAX      65535
#define WLAN_EDCA_TABLE_MSDU_LIFETIME_MAX   500

/* EDCA参数 */
#define WLAN_QEDCA_TABLE_INDEX_MIN           1
#define WLAN_QEDCA_TABLE_INDEX_MAX           4
#define WLAN_QEDCA_TABLE_CWMIN_MIN           1
#define WLAN_QEDCA_TABLE_CWMIN_MAX           10
#define WLAN_QEDCA_TABLE_CWMAX_MIN           1
#define WLAN_QEDCA_TABLE_CWMAX_MAX           10
#define WLAN_QEDCA_TABLE_AIFSN_MIN           2
#define WLAN_QEDCA_TABLE_AIFSN_MAX           15
#define WLAN_QEDCA_TABLE_TXOP_LIMIT_MIN      1
#define WLAN_QEDCA_TABLE_TXOP_LIMIT_MAX      65535
#define WLAN_QEDCA_TABLE_MSDU_LIFETIME_MAX   500

/* TID个数方图平台SPEC */

/* 默认的数据类型业务的TID */
#define WLAN_TID_FOR_DATA                   0
/* 接收队列的个数 与HAL_RX_DSCR_QUEUE_ID_BUTT相等 */
#define HAL_RX_QUEUE_NUM                3
/* 发送队列的个数 */
#define HAL_TX_QUEUE_NUM                5
/* 存储硬件接收上报的描述符链表数目(ping pong使用) */
#define HAL_HW_RX_DSCR_LIST_NUM         2

/*****************************************************************************
  2.3 校准类别的spec
*****************************************************************************/
/* 支持手动设置分频系数的个数 */
#ifdef _PRE_WLAN_PHY_PLL_DIV
#define WITP_RF_SUPP_NUMS                  4
#endif

/*****************************************************************************
  2.4 安全协议类别的spec
*****************************************************************************/
#define WLAN_NUM_TK             4
#define WLAN_NUM_IGTK           2
#define WLAN_MAX_IGTK_KEY_INDEX 5
#define WLAN_MAX_WEP_KEY_COUNT  4
/*****************************************************************************
  2.4.1 WPA功能
*****************************************************************************/
/* 11i参数的WLAN_WPA_KEY_LEN 和 WLAN_WPA_SEQ_LEN作为平台结构体成员，放入平台*/

/* 加密相关的宏定义 */
/* 硬件MAC 最多等待32us， 软件等待40us */
#define HAL_CE_LUT_UPDATE_TIMEOUT          4


/*****************************************************************************
  2.4.4 PMF 功能
*****************************************************************************/
/* SA Query流程间隔时间,老化时间的三分之一*/
#define WLAN_SA_QUERY_RETRY_TIME                (WLAN_USER_AGING_TIME / 3)
/* SA Query流程超时时间,小于老化时间*/
#define WLAN_SA_QUERY_MAXIMUM_TIME              (WLAN_SA_QUERY_RETRY_TIME * 3)

/*****************************************************************************
  2.4.6 自定义安全
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define WLAN_BLACKLIST_MAX                  32
#endif

/*****************************************************************************
  2.5 性能类别的spec
*****************************************************************************/
/*****************************************************************************
  2.5.1 块确认功能
*****************************************************************************/
/* 支持的接收ba窗的最大个数 */
#define WLAN_MAX_RX_BA                      32

/* 支持的发送ba窗的最大个数 */
#define WLAN_MAX_TX_BA                      32

#ifdef _PRE_WIFI_DMT
/* 与RSP侧一致，考虑最差的场景下最大超时时间 */
#define WLAN_ADDBA_TIMEOUT                      10000
//#define WLAN_TX_PROT_TIMEOUT                    60000
#else
#define WLAN_ADDBA_TIMEOUT                      500
//#define WLAN_TX_PROT_TIMEOUT                    4000
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define HAL_PROXYSTA_MAX_BA_LUT_SIZE    16
#endif

/*****************************************************************************
  2.5.2 AMPDU功能
*****************************************************************************/
#define WLAN_AMPDU_RX_BUFFER_SIZE       64  /* AMPDU接收端接收缓冲区的buffer size的大小 */
#define WLAN_AMPDU_RX_BA_LUT_WSIZE      64  /* AMPDU接收端用于填写BA RX LUT表的win size,
                                               要求大于等于WLAN_AMPDU_RX_BUFFER_SIZE */
#define WLAN_AMPDU_TX_MAX_NUM           64  /* AMPDU发送端最大聚合子MPDU个数、发送端的buffer size */
#define WLAN_AMPDU_TX_MAX_BUF_SIZE      64  /* 发送端的buffer size */

#define WLAN_AMPDU_TX_SCHD_STRATEGY     1   /* 51 最大聚合个数等于最大窗口 */

#define HAL_MAX_BA_LUT_SIZE                32
#define HAL_MAX_AMPDU_LUT_SIZE             128
/*****************************************************************************
  2.5.3 AMSDU功能
*****************************************************************************/
#define AMSDU_ENABLE_ALL_TID                0xFF
/* amsdu下子msdu的最大长度 */
#define WLAN_MSDU_MAX_LEN                   1600
/* 1151 spec amsdu最大长度 */
#define WLAN_AMSDU_FRAME_MAX_LEN            7935

/* >= WLAN_AMSDU_MAX_NUM/2  */
#define WLAN_DSCR_SUBTABEL_MAX_NUM          13

/*****************************************************************************
  2.5.6 Memory限制
*****************************************************************************/
/*HAL 打头待修订为WLAN*/
/* 接收描述符个数的宏定义 */
/* 普通优先级接收描述符队列中描述符最大个数 32*2*3(amsdu占用buf的数目) */
#define HAL_NORMAL_RX_MAX_BUFFS           512
/* 高优先级接收描述符队列中描述符最大个数:取决于并发用户数(64) */
#define HAL_HIGH_RX_MAX_BUFFS             64
#define HAL_RX_MAX_BUFFS                 (HAL_NORMAL_RX_MAX_BUFFS + HAL_HIGH_RX_MAX_BUFFS)
/*接收描述符做ping pong处理*/
#define HAL_HW_MAX_RX_DSCR_LIST_IDX       1
/* 用于存储接收完成中断最大个数 */
#define HAL_HW_RX_ISR_INFO_MAX_NUMS       HAL_NORMAL_RX_MAX_BUFFS
#define HAL_DOWM_PART_RX_TRACK_MEM        200
#ifdef _PRE_DEBUG_MODE
/* 接收描述符第13行用于打时间戳，调试用 */
#define HAL_DEBUG_RX_DSCR_LINE            13
#endif


#ifdef _PRE_WLAN_PHY_PERFORMANCE
/* PHY性能测试使用帧长度 */
    #define HAL_RX_FRAME_LEN              5100
    #define HAL_RX_FRAME_MAX_LEN          8000
#else
/* 80211帧最大长度:软件最大为1600，流20字节的余量，防止硬件操作越界 */
    #define HAL_RX_FRAME_LEN              1580
    #define HAL_RX_FRAME_MAX_LEN          8000
#endif

#define HAL_AL_RX_FRAME_LEN               5100


/*****************************************************************************
  2.6 算法类别的spec
*****************************************************************************/

/*****************************************************************************
  2.6.6 TXBF功能
*****************************************************************************/
/* TXBF的beamformer的流个数*/
#define WLAN_TXBF_NSS_SPEC		2
#define WLAN_TXBF_SU_BFMER_DEFAULT_VALUE      1
#define WLAN_BFER_ACTIVED		OAL_TRUE
#define WLAN_TXSTBC_ACTIVED		OAL_TRUE
#define WLAN_MU_BFEE_ACTIVED	OAL_FALSE

/*****************************************************************************
  2.6.15 TPC功能
*****************************************************************************/
/* TPC相关参数 */
/* TPC步进DB数 */
#define WLAN_TPC_STEP                       3
/* 最大传输功率，单位dBm */
#define WLAN_MAX_TXPOWER                    30



/*****************************************************************************
  2.7 节能低功耗类别的spec
*****************************************************************************/
/*****************************************************************************
  2.7.1 芯片Sleep状态
*****************************************************************************/
/* default PCIE LO IDLETIME 1us */
#define WLAN_PCIE_L0_DEFAULT                1
/* default PCIE LO IDLETIME 1us */
#define WLAN_PCIE_L1_DEFAULT                32

/*****************************************************************************
  2.7.4 协议节能STA侧功能
*****************************************************************************/
/*PSM特性规格*/
/* default DTIM period */
#define WLAN_DTIM_DEFAULT                   3

/* DTIM Period参数 */
/* beacon interval的倍数 */
#define WLAN_DTIM_PERIOD_MAX                255
#define WLAN_DTIM_PERIOD_MIN                1

/*****************************************************************************
  2.7.5 协议节能AP侧功能
*****************************************************************************/



/*****************************************************************************
  2.8 架构形态类别的spec
*****************************************************************************/
/*****************************************************************************
  2.8.4  WiFi芯片抽象层
*****************************************************************************/
/* RF通道数规格*/
/* 通道0 */
#define WITP_RF_CHANNEL_ZERO        0
/* 通道1 */
#define WITP_RF_CHANNEL_ONE         1
/* 双通道 */
#define WITP_RF_CHANNEL_NUMS        2

/* 双通道掩码 */
#define WITP_TX_CHAIN_DOUBLE        3
/*  通道0 掩码*/
#define WITP_TX_CHAIN_ZERO          1
/*  通道1 掩码*/
#define WITP_TX_CHAIN_ONE           2

/*芯片版本已放入平台的定制化*/


/*****************************************************************************
  2.8.7  Proxy STA特性
*****************************************************************************/
/* 每个DEVICE支持的最大业务VAP数目: 场景一有4个AP VAP；场景二有1个AP VAP + 1个STA VAP */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MAX_PROXY_STA_NUM                  15
#define WLAN_STA0_HAL_VAP_ID                    4
#define WLAN_PROXY_STA_START_ID                 16
#define WLAN_PROXY_STA_END_ID                   31
#endif


/*****************************************************************************
  2.8.8  多AP特性
*****************************************************************************/
#if 0
#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     4
#endif
 /* AP VAP的规格、STA VAP的规格、STA P2P共存的规格放入平台*/

/* PROXY STA模式下VAP规格宏定义放入平台 */
//#define WLAN_VAP_MAX_NUM_PER_DEVICE          (WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + 1)

#define WLAN_HAL_OHTER_BSS_ID                   5     /* 其他BSS的ID */
#define WLAN_HAL_OTHER_BSS_UCAST_ID             7     /* 来自其他bss的单播管理帧和数据帧，维测用 */
#define WLAN_VAP_MAX_ID_PER_DEVICE_LIMIT        31    /* hal层，0-3 4个AP，4 1个STA 16-30 PROXY STA */


/* 整个BOARD支持的最大的VAP数目已放入平台 */

/* 整个BOARD支持的最大业务VAP的数目 已放入平台*/

/* MAC上报的tbtt中断类别最大值，4个ap的tbtt中断+1个sta的tbtt中断 */
#define WLAN_MAC_REPORT_TBTT_IRQ_MAX           5

/*****************************************************************************
  2.8.11  功能增减
*****************************************************************************/
/* 特性默认开启关闭定义*/
/*TBD Feature动态当前未使用，待清理。能力没有使用*/
#define WLAN_FEATURE_AMPDU_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_AMSDU_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_WME_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_DSSS_CCK_IS_OPEN           OAL_TRUE
#define WLAN_FEATURE_UAPSD_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_PSM_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_WPA_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_TXBF_IS_OPEN               OAL_TRUE
#define WLAN_FEATURE_MSDU_DEFRAG_IS_OPEN        OAL_TRUE

/*****************************************************************************
  2.8.20  DBAC
*****************************************************************************/
/*  虚假队列个数，用于切离一个信道时，将原信道上放到硬件队列里的帧保存起来
当前只有2个场景: DBAC 与 背景扫描 DBAC占用2个队列，编号0 1; 背景扫描占用一个，编号2 */
/*HAL 打头待修订为WLAN*/
#define HAL_TX_FAKE_QUEUE_NUM              3
#define HAL_TX_FAKE_QUEUE_BGSCAN_ID        2

#define HAL_FCS_PROT_MAX_FRAME_LEN         24

/*****************************************************************************
  2.9 WiFi应用类别的spec
*****************************************************************************/
/*****************************************************************************
  2.9.4 P2P特性
*****************************************************************************/
/* Hi1102 P2P特性中P2P vap设备的大小限制(PER_DEVICE) */
/* P2P只在1102下定义，此处定义是为了1151UT打桩 */
#ifdef _PRE_WLAN_FEATURE_P2P
#define WLAN_MAX_SERVICE_P2P_DEV_NUM          1
#define WLAN_MAX_SERVICE_P2P_GOCLIENT_NUM     1
#define WLAN_MAX_SERVICE_CFG_VAP_NUM          1
#endif
/*****************************************************************************
  2.10 MAC FRAME特性
*****************************************************************************/
/*****************************************************************************
  2.10.1 ht cap info
*****************************************************************************/
#define HT_GREEN_FILED_DEFAULT_VALUE            0
#define HT_TX_STBC_DEFAULT_VALUE                1
/*****************************************************************************
  2.10.2 vht cap info
*****************************************************************************/
#define VHT_TX_STBC_DEFAULT_VALUE               1

/*****************************************************************************
  2.10.3 RSSI
*****************************************************************************/
#define WLAN_NEAR_DISTANCE_RSSI        (-35)             /*默认近距离信号门限-35dBm*/
#define WLAN_CLOSE_DISTANCE_RSSI       (-25)             /*关联前距离判断门限-25dBm*/
#define WLAN_FAR_DISTANCE_RSSI         (-83)             /*默认远距离信号门限-83dBm*/
#define WLAN_NORMAL_DISTANCE_RSSI_UP   (-42)             /*信号强度小于-42dBm时，才认为非超近距离*/
#define WLAN_NORMAL_DISTANCE_RSSI_DOWN (-76)             /*信号强度大于-76dBm时，才认为是非超远距离*/


/*****************************************************************************

  2.11 描述符偏移
*****************************************************************************/
#define WLAN_RX_DSCR_SIZE                       (60)


#endif /* #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __WLAN_SPEC_1151_H__ */




