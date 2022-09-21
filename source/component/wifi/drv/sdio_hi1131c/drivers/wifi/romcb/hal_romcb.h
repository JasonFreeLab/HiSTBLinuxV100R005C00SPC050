/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hal_romcb.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月9日
  最近修改   :
  功能描述   : wifi_rf.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HAL_ROMCB_H__
#define __HAL_ROMCB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HAL_ROMCB_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
//#include "hal_hi1102_rf.h"
#if 0
#include "wlan_types.h"
#include "frw_ext_if.h"
#include "dmac_vap.h"
#endif
//#include "hal_commom_ops.h"
#include "hal_device.h"

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)

/* g_pfa_wifi_rf_func对应枚举*/
typedef enum
{
#if (!defined(_PRE_PC_LINT) && !defined(WIN32))
    WIFI_RF_GET_PWR_COMP_VAL,   // hi1102_get_pwr_comp_val
#endif
    WIFI_SET_CHANNEL_INIFO,     // hi1102_rf_set_channel_info
    WIFI_PSM_RF_SLEEP,          // hi1102_psm_rf_sleep
    WIFI_PSM_RF_AWAKE,          // hi1102_psm_rf_awake
    WIFI_INITIALIZE_RF_SYS,     // hi1102_initialize_rf_sys
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    WIFI_DPD_CALI_FUNC,         // hi1102_dpd_cali_func
#endif
    WIFI_RF_GET_RFHW_STAT_INFO,

    WIFI_RF_FUNC_BUTT
}wifi_rf_func_enum;


typedef oal_void (*wifi_cb_func)(oal_void);
typedef oal_void (*get_pwr_comp_val)(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tx_ratio, oal_int16 * ps_pwr_comp_val);
typedef oal_uint32 (*get_scaling_addr)(oal_uint8 uc_offset_addr_a);

typedef oal_void (*set_channel_info)(hal_device_stru                    *pst_device,
                                        wlan_channel_band_enum_uint8        en_band,
                                        oal_uint8                           uc_channel_idx,
                                        wlan_channel_bandwidth_enum_uint8   en_bandwidth,
                                        oal_uint8                           uc_rf_channel_num);
typedef oal_void (*psm_rf_sleep)(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
typedef oal_void (*psm_rf_awake)(hal_to_dmac_device_stru  *pst_hal_device, oal_uint8 uc_restore_reg);
typedef oal_void (*initialize_rf_sys)(hal_to_dmac_device_stru *pst_hal_device);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
typedef oal_void (*dpd_cali_func)(oal_uint8 u_functype, oal_uint32* pul_status, oal_uint32* hi1102_dpd_cal_data_read, oal_uint32* hi1102_dpd_cal_data_write);
#endif
typedef oal_void (*rf_get_rfhw_stat_info)(hal_device_stru * pst_device,oal_uint16 *pus_rfhw_stat);



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern wifi_cb_func     g_pfa_wifi_rf_func[];



#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hal_romcb.h */

