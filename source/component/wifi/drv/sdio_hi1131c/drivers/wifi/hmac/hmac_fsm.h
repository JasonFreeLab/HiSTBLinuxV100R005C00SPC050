/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_fsm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月18日
  最近修改   :
  功能描述   : hmac_fsm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_FSM_H__
#define __HMAC_FSM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "hmac_main.h"
#include "hmac_vap.h"
#include "hmac_rx_filter.h"
#include "hmac_config.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FSM_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef oal_uint32  (*hmac_fsm_func)(hmac_vap_stru *pst_hmac_vap, oal_void *p_param);

extern oal_uint32  hmac_config_sta_update_rates(mac_vap_stru *pst_mac_vap, mac_cfg_mode_param_stru *pst_cfg_mode, mac_bss_dscr_stru *pst_bss_dscr);

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 状态机输入类型枚举 */
typedef enum
{
    /* AP STA共有的输入类型 */
    HMAC_FSM_INPUT_RX_MGMT,
    HMAC_FSM_INPUT_RX_DATA,
    HMAC_FSM_INPUT_TX_DATA,
    HMAC_FSM_INPUT_TIMER0_OUT,
    HMAC_FSM_INPUT_MISC,        /* TBTT 异常 等其他输入类型 */

    /* AP 独有的输入类型 */
    HMAC_FSM_INPUT_START_REQ,

    /* STA独有的输入类型 */
    HMAC_FSM_INPUT_SCAN_REQ,
    HMAC_FSM_INPUT_JOIN_REQ,
    HMAC_FSM_INPUT_AUTH_REQ,
    HMAC_FSM_INPUT_ASOC_REQ,

    HMAC_FSM_INPUT_LISTEN_REQ,  /*  监听请求 */
    HMAC_FSM_INPUT_LISTEN_TIMEOUT,
    HMAC_FSM_INPUT_SCHED_SCAN_REQ,      /* PNO调度扫描请求 */

#ifdef _PRE_WLAN_FEATURE_ROAM
    HMAC_FSM_INPUT_ROAMING_START,
    HMAC_FSM_INPUT_ROAMING_STOP,
#endif //_PRE_WLAN_FEATURE_ROAM

    HMAC_FSM_INPUT_TYPE_BUTT
}hmac_fsm_input_type_enum;
typedef oal_uint8 hmac_fsm_input_type_enum_uint8;

#define HMAC_FSM_AP_INPUT_TYPE_BUTT     (HMAC_FSM_INPUT_MISC + 1)
#define HMAC_FSM_STA_INPUT_TYPE_BUTT    HMAC_FSM_INPUT_TYPE_BUTT
#define HMAC_SWITCH_STA_PSM_PERIOD      120000                  //staut打开低功耗超时的时间参考1101 120s

/* MISC输入类型的子类型定义 */
typedef enum
{
    HMAC_MISC_TBTT,
    HMAC_MISC_ERROR,
    HMAC_MISC_RADAR,

    HMAC_MISC_BUTT
}hmac_misc_input_enum;
typedef oal_uint8 hmac_misc_input_enum_uint8;

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
/* MISC输入类型，入参结构体定义 */
typedef struct
{
    hmac_misc_input_enum_uint8  en_type;
    oal_uint8                   auc_resv[3];
    oal_void                   *p_data;
}hmac_misc_input_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  hmac_fsm_init(oal_void);
extern oal_uint32  hmac_fsm_call_func_ap(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param);
extern oal_uint32  hmac_fsm_call_func_sta(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param);
extern oal_void  hmac_fsm_change_state(hmac_vap_stru *pst_hmac_vap, mac_vap_state_enum_uint8 en_vap_state);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
