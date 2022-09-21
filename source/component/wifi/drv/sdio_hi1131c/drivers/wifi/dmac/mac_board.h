/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_board.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月17日
  最近修改   :
  功能描述   : mac_board.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月17日
    作    者   : 侯寅
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_BOARD_H__
#define __MAC_BOARD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_BOARD_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*****************************************************************************
  DFX 宏定义
*****************************************************************************/
#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION) || defined(_PRE_WIFI_DMT))&&(!defined(_PRE_PC_LINT))
#define DFX_GET_PERFORMANCE_LOG_SWITCH_ENABLE(_uc_type) (0)
#define DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(_uc_type, _uc_value)
#else
#define DFX_GET_PERFORMANCE_LOG_SWITCH_ENABLE(_uc_type) dfx_get_performance_log_switch_enable(_uc_type)
#define DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(_uc_type, _uc_value) dfx_set_performance_log_switch_enable(_uc_type, _uc_value)
#endif
    

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
  DFX公用枚举定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
typedef enum
{
    DFX_PERFORMANCE_TX_LOG,
    DFX_PERFORMANCE_DUMP,
    DFX_PERFORMANCE_LOG_BUTT,
}dfx_performance_log_switch_enum;
typedef oal_uint8 dfx_performance_log_switch_enum_uint8;
#endif

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* HOST CRX子表 */
extern frw_event_sub_table_item_stru g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_BUTT];

/* DMAC模块，HOST_DRX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_tx_host_drx[DMAC_TX_HOST_DRX_BUTT];

/* DMAC模块，WLAN_DTX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_tx_wlan_dtx[DMAC_TX_WLAN_DTX_BUTT];

/* DMAC模块，WLAN_CTX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块,WLAN_DRX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_wlan_drx_event_sub_table[HAL_WLAN_DRX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块，高优先级事件处理函数注册结构体定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_high_prio_event_sub_table[HAL_EVENT_ERROR_IRQ_SUB_TYPE_BUTT];

/* DMAC模块,WLAN_CRX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_wlan_crx_event_sub_table[HAL_WLAN_CRX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块，TX_COMP事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_tx_comp_event_sub_table[HAL_TX_COMP_SUB_TYPE_BUTT];

/* DMAC模块, TBTT事件处理函数表定义 */
extern frw_event_sub_table_item_stru g_ast_dmac_tbtt_event_sub_table[HAL_EVENT_TBTT_SUB_TYPE_BUTT];

/*DMAC模块, MISC事件处理函数表定义 */
extern  frw_event_sub_table_item_stru g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT];

/* WLAN_DTX 事件子类型表 */
extern frw_event_sub_table_item_stru g_ast_hmac_wlan_dtx_event_sub_table[DMAC_TX_WLAN_DTX_BUTT];

/* HMAC模块 WLAN_DRX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 WLAN_CRX事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 TBTT事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_tbtt_event_sub_table[DMAC_TBTT_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 发向HOST侧的配置事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_SYN_BUTT];

/* HMAC模块 MISC杂散事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_BUTT];

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
/* HMAC模块 IPC事件处理函数注册结构定义 */
extern frw_event_sub_table_item_stru g_ast_hmac_host_drx_event_sub_table[DMAC_TX_HOST_DRX_BUTT];
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern frw_event_sub_table_item_stru g_ast_hmac_hcc_rx_event_sub_table[DMAC_HCC_RX_EVENT_SUB_TYPE_BUTT];
#endif
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
    
/*****************************************************************************
  DFX公用函数声明
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
extern oal_uint32 dfx_get_performance_log_switch_enable(dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type);
extern oal_void dfx_set_performance_log_switch_enable(dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type, oal_uint8 uc_value);
#endif    
    

extern oal_void  event_fsm_unregister(oal_void);

extern oal_void  event_fsm_table_register(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_board */



