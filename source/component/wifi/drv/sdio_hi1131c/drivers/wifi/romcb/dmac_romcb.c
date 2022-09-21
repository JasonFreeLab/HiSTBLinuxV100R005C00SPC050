/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_romcb.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月8日
  最近修改   :
  功能描述   : DMAC接口映射
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ROMCB_C

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_romcb.h"

/*****************************************************************************
  2 函数定义
*****************************************************************************/

/*WOW外部调用函数*/
extern oal_int32 dmac_wow_rx_process_data_ram(oal_netbuf_head_stru    *pst_netbuf_header, mac_vap_stru *pst_vap, oal_netbuf_stru *pst_netbuf);

extern oal_int32 dmac_wow_rx_process_control_ram(dmac_vap_stru *pst_dmac_vap,oal_netbuf_stru     *pst_netbuf, oal_uint8 *pen_go_on);

extern oal_uint32  dmac_wow_rx_process_mgmt_ram(dmac_vap_stru      *pst_dmac_vap,
                                           oal_netbuf_stru    *pst_netbuf,
                                           frw_event_mem_stru *pst_event_mem,
                                           oal_uint8          *pen_go_on);

extern oal_void dmac_wow_dev_wake_up_host_ram(oal_uint32 ul_wakeup_reason);

extern oal_void dmac_wow_init_ram(oal_void);

extern oal_uint32 dmac_wow_sleep_wakeup_notify_ram(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_uint32 dmac_wow_set_param_ram(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

extern oal_void  dmac_wow_main_process_ram(oal_void);

extern oal_uint32  dmac_wow_rx_check_filter_switch_ram(oal_void);

extern oal_void dmac_wow_host_sleep_callback_ram(oal_void);

extern oal_uint32  dmac_wow_process_and_save_event_ram(
                        mac_vap_stru        *pst_vap,
                        frw_event_mem_stru  *pst_event_mem,
                        oal_uint32           ul_event_type
                        );

extern oal_uint32  dmac_wow_disassoc_end_notify_ram(
                        mac_vap_stru        *pst_vap,
                        oal_uint8           *puc_mac_addr
                        );
                        
/*****************************************************************************
  3 全局变量定义
*****************************************************************************/


#ifdef _PRE_WLAN_FEATURE_WOW
/*新特性回调函数数组*/
wifi_cb_func ROM_CALLBACK g_pfa_wifi_ftr_func[WIFI_FTR_FUNC_BUTT] =
{
                    (wifi_cb_func)(dmac_wow_rx_process_data_ram),           //dmac_wow_rx_process_data
                    (wifi_cb_func)(dmac_wow_rx_process_control_ram),        //dmac_wow_rx_process_control
                    (wifi_cb_func)(dmac_wow_rx_process_mgmt_ram),           //dmac_wow_rx_process_mgmt
                    (wifi_cb_func)(dmac_wow_dev_wake_up_host_ram),          //dmac_wow_dev_wake_up_host
                    (wifi_cb_func)(dmac_wow_init_ram),                      //dmac_wow_init
                    (wifi_cb_func)(dmac_wow_sleep_wakeup_notify_ram),       //dmac_wow_sleep_wakeup_notify
                    (wifi_cb_func)(dmac_wow_set_param_ram),                 //dmac_wow_set_param
                    (wifi_cb_func)(dmac_wow_main_process_ram),              //dmac_wow_main_process
                    (wifi_cb_func)(dmac_wow_rx_check_filter_switch_ram),    //dmac_wow_rx_check_filter_switch
                    (wifi_cb_func)(dmac_wow_host_sleep_callback_ram),       //dmac_wow_host_sleep_callback
                    (wifi_cb_func)(dmac_wow_process_and_save_event_ram),    //dmac_wow_process_and_save_event
                    (wifi_cb_func)(dmac_wow_disassoc_end_notify_ram)        //dmac_wow_disassoc_end_notify
};
#endif

/*****************************************************************************
  4 函数实现
*****************************************************************************/
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


