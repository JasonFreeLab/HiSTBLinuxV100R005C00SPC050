/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_pm_sta.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年1月14日
  最近修改   :
  功能描述   : dmac_pm_sta.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月14日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_PM_STA_H__
#define __DMAC_PM_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PM_STA_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WLAN_SAVE_USE_DMA 1

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
extern oal_uint8 dmac_psm_check_hw_txq_state(oal_void);
extern oal_uint8 dmac_psm_check_txrx_state(oal_void);
extern oal_void  dmac_psm_recover_start_dma(oal_uint8 *puc_ch0,oal_uint8 *puc_ch1,oal_uint8 *puc_ch2);
extern oal_uint8 dmac_psm_clean_state (oal_void);
extern oal_void dmac_psm_save_start_dma (oal_uint8* puc_ch0,oal_uint8* puc_ch1,oal_uint8* puc_ch2);
extern oal_uint8 dmac_psm_save_ps_state (oal_void);
extern oal_uint8 dmac_psm_recover_powerdown(oal_uint8 uc_dmach0,oal_uint8 uc_dmach1,oal_uint8 uc_dmach2);
extern oal_uint8 dmac_psm_recover_no_powerdown (oal_void);
extern oal_uint8 dmac_psm_cbb_stopwork (oal_void);
extern oal_void dmac_psm_rf_sleep(oal_uint8 uc_restore_reg);
extern oal_void dmac_psm_rf_awake (oal_uint8 uc_restore_reg);
//extern oal_void dmac_psm_sync_tsf_to_sta(oal_void);
//extern oal_void dmac_psm_sync_tsf_to_ap(oal_void);
extern oal_uint8 dmac_psm_is_fake_queues_empty(oal_void);
extern void pm_wlan_deepsleep_save_state(void);
extern void pm_wlan_deepsleep_load_state(void);
extern oal_void dmac_psm_save_register(oal_void);
extern oal_void dmac_psm_restore_register(oal_void);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_pm_sta.h */
