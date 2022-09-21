/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_auto_adjust_freq.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年9月14日
  最近修改   :
  功能描述   : mac_auto_adjust_freq.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月14日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_AUTO_ADJUST_FREQ_H__
#define __MAC_AUTO_ADJUST_FREQ_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define  FREQ_LOCK_TIMEOUT_VAL  1000  /*锁定CPU主频的时间，单位ms*/

#define  SPEED_CALC_TRIG_VALUE              2000 /*2000个包计算一次包速率*/
#define  SPEED_CALC_TRIG_DURITION              100 /*最长的计算时间*/
/*
 * set cpu freq A53-0
 * this function used on K3V3+ platform
 */
#define CPU_MAX_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
#define CPU_MIN_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"

/*
 * set ddr freq
 * this function used on K3V3+ platform
 */
#define DDR_MAX_FREQ "/sys/class/devfreq/ddrfreq/max_freq"
#define DDR_MIN_FREQ "/sys/class/devfreq/ddrfreq/min_freq"

#define MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_3 (3)    /*连续3个周期都需要降频才降频*/
#define MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_2 (2)    /*连续2个周期都需要降频才降频*/
#define MAX_DEGRADE_FREQ_COUNT_THRESHOLD_SUCCESSIVE_10 (100)    /*有包时连续100个周期都需要降频才降频*/
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    AUTO_FREQ_DISABLE                        = 0,

    AUTO_FREQ_ENABLE                        = 1,
}oal_scaling_freq_enum;
typedef oal_uint8 oal_scaling_freq_enum_uint8;

enum
{
    /* indicate to set cpu/ddr max frequencies */
    SCALING_MAX_FREQ                        = 0,

    /* indicate to set cpu/ddr min frequencies */
    SCALING_MIN_FREQ                        = 1,
};

enum
{
    /* indicate to set cpu/ddr to a low level */
    FREQ_DOWNGRADE                          = 0,

    /* indicate to set cpu/ddr to a high level */
    FREQ_UPGRADE                            = 1,

    /* indicate to set cpu/ddr to original level */
    FREQ_ORIGINAL                           = 2,
};

enum
{
    /* frequency lock disable mode */
    FREQ_LOCK_DISABLE                       = 0,

    /* frequency lock enable mode */
    FREQ_LOCK_ENABLE                        = 1,
};
typedef oal_uint8 oal_freq_lock_enum_uint8;

typedef enum
{
    CMD_SET_AUTO_FREQ_ENDABLE,
    CMD_SET_CPU_FREQ_VALUE,
    CMD_SET_DDR_FREQ_VALUE,
    CMD_SET_DEVICE_FREQ_VALUE,
    CMD_SET_AUTO_FREQ_DEBUG_PRINT,
    CMD_SET_AUTO_BYPASS_DEVICE_AUTO_FREQ,
    CMD_AUTO_FREQ_BUTT,
}oal_auto_freq_cmd_enum;
typedef oal_uint8 oal_auto_freq_cmd_enum_uint8;


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
typedef struct {
    oal_uint8  uc_device_type;   /*device主频类型*/
    oal_uint8  uc_reserve[3];   /*保留字段*/
} device_speed_freq_level_stru;
typedef struct {
    oal_uint32  ul_speed_level;    /*吞吐量门限*/
    oal_uint32  ul_min_cpu_freq;  /*CPU主频下限*/
    oal_uint32  ul_min_ddr_freq;   /*DDR主频下限*/
} host_speed_freq_level_stru;

typedef struct {
    oal_uint8 uc_lock_mod;  /*使能开关*/

    oal_uint8  uc_curr_lock_level;  /*当前主频等级*/
    oal_uint8  uc_req_lock_level;   /*目标主频等级*/
    oal_bool_enum_uint8  en_debug_print;  /*打印开关*/
    oal_bool_enum_uint8  en_bypass_device_freq;  /*bypass device调频,devices主频设置为最高*/
    oal_uint8  uc_reserver[2];  /*预留字段*/
    oal_bool_enum_uint8  en_is_inited;
    oal_uint32 ul_total_sdio_rate;  /*吞吐速率*/
    oal_mutex_stru st_lock_freq_mtx;
} freq_lock_control_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#ifdef WIN32
extern oal_uint32 pre_jiffies;

extern oal_uint8                 g_freq_lock_num;
extern freq_lock_control_stru g_freq_lock_control;
extern oal_uint32 g_ul_wifi_rxtx_total;

extern  oal_uint32 g_ul_orig_cpu_min_freq;
extern  oal_uint32 g_ul_orig_cpu_max_freq;
extern  oal_uint32 g_ul_orig_ddr_min_freq;
extern  oal_uint32 g_ul_orig_ddr_max_freq;

#endif


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_bool_enum_uint8 hmac_set_auto_freq_mod(oal_freq_lock_enum_uint8 uc_freq_enable);
extern oal_bool_enum_uint8 hmac_set_auto_freq_debug_print(oal_bool_enum_uint8 en_debug_print);
extern oal_bool_enum_uint8 hmac_set_cpu_freq_raw(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value);
extern oal_bool_enum_uint8 hmac_set_ddr_freq_raw(oal_uint8 uc_freq_type, oal_uint32 ul_freq_value);
extern oal_void hmac_hcc_auto_freq_count(oal_uint32 ul_pkt_count);
extern oal_void hmac_adjust_freq(oal_void);
extern oal_uint32 hmac_wifi_tx_rx_counter(oal_uint32 ul_pkt_count);
extern oal_uint32 hmac_hcc_auto_freq_process(void);
extern oal_void hmac_adjust_freq_to_level(oal_void);
extern oal_void hmac_wifi_auto_freq_ctrl_init(void);
extern oal_void hmac_wifi_auto_freq_ctrl_deinit(void);
extern oal_bool_enum_uint8 hmac_set_auto_freq_bypass_device_auto_freq(oal_bool_enum_uint8 en_bypass_device);




#endif /* end of mac_auto_adjust_freq.h */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

