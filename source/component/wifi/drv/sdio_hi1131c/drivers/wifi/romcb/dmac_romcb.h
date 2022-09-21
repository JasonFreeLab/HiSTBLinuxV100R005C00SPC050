/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_romcb.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月9日
  最近修改   :
  功能描述   : dmac_romcb.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ROMCB_H__
#define __DMAC_ROMCB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ROMCB_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
//#include "hal_hi1102_rf.h"
#include "wlan_types.h"
#include "frw_ext_if.h"
#include "dmac_vap.h"
#if 0
#include "hal_commom_ops.h"
#include "hal_device.h"
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)

/*****************************************************************************
  2 宏定义
*****************************************************************************/



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    WOW_RX_PROCESS_DATA,        //dmac_wow_rx_process_data
    WOW_RX_PROCESS_CONTROL,     //dmac_wow_rx_process_control
    WOW_RX_PROCESS_MGMT,        //dmac_wow_rx_process_mgmt
    WOW_DEV_WAKEUP_HOST,        //dmac_wow_dev_wake_up_host
    WOW_INIT,                   //dmac_wow_init
    WOW_SLEEP_WAKE_NOTIFY,      //dmac_wow_sleep_wakeup_notify
    WOW_SET_PARAM,              //dmac_wow_set_param
    WOW_MAIN_PROCESS,           //dmac_wow_main_process
    WOW_RX_CHECK_FILTER,        //dmac_wow_rx_check_filter_switch
    WOW_SLEEP_CALLBACK,         //dmac_wow_host_sleep_callback
    WOW_PROC_SAVE_EVENT,        //dmac_wow_process_and_save_event
    WOW_DISASSOC_END_NOTIFY,    //dmac_wow_disassoc_end_notify
    WIFI_FTR_FUNC_BUTT
}wifi_ftr_func_enum;
                    
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
typedef oal_void (*wifi_cb_func)(oal_void);

#ifdef _PRE_WLAN_FEATURE_WOW
typedef oal_uint32   (*wow_rx_process_data)(oal_netbuf_head_stru    *pst_netbuf_header_in, oal_netbuf_head_stru    *pst_netbuf_header_out,mac_vap_stru *pst_vap, oal_netbuf_stru *pst_netbuf);
typedef oal_uint32   (*wow_rx_process_control)(dmac_vap_stru *pst_dmac_vap,oal_netbuf_stru     *pst_netbuf, oal_uint8 *pen_go_on);
typedef oal_uint32   (*wow_rx_process_mgmt)(dmac_vap_stru      *pst_dmac_vap,
                                          oal_netbuf_stru    *pst_netbuf,
                                          frw_event_mem_stru *pst_event_mem,
                                          oal_uint8          *pen_go_on);

typedef oal_void    (*wow_dev_wake_up_host)(oal_uint32 ul_wakeup_reason);

typedef oal_void    (*wow_init)(oal_void);

typedef oal_uint32  (*wow_sleep_wakeup_notify)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

typedef oal_uint32  (*wow_set_param)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

typedef oal_void    (*wow_main_process)(oal_void);
                
typedef oal_uint32  (*wow_rx_check_filter_switch)(oal_void);

typedef oal_void    (*wow_host_sleep_callback)(oal_void);

typedef oal_uint32  (*wow_process_and_save_event)(
                        mac_vap_stru        *pst_vap, 
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );
typedef oal_uint32  (*wow_disassoc_end_notify)(
                        mac_vap_stru        *pst_vap,
                        oal_uint8           *puc_mac_addr
                        );
#endif

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_WOW
extern wifi_cb_func     g_pfa_wifi_ftr_func[];
#endif
/*****************************************************************************
  10 函数声明
*****************************************************************************/


#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_romcb.h */

