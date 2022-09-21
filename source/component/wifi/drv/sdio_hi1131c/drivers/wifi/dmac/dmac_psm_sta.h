/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_psm_sta.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年11月25日
  最近修改   :
  功能描述   : dmac_psm_sta.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月25日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_PSM_STA_H__
#define __DMAC_PSM_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
#include "dmac_uapsd_sta.h"
#else
#include "dmac_sta_pm.h"
#include "dmac_ext_if.h"
#include "dmac_tx_bss_comm.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PSM_STA_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_DEFAULT_DTIM_LISTEN_DIFF 4        // DTIM LISTEN INTERVAL 比较中间量
#define DMAC_DEFAULT_LISTEN_INTERVAL  2        // 默认listen interval

/* 第一档超时TIMEOUT * CNT 必须大于100ms，否则丢包率高,体验差 */
#define DMAC_PSM_TIMER_IDLE_TIMEOUT     50
#define DMAC_PSM_TIMER_MIDIUM_TIMEOUT   100
#define DMAC_PSM_TIMER_BUSY_TIMEOUT     200
#define DMAC_PSM_TIMER_IDLE_CNT         4
#define DMAC_PSM_TIMER_MIDIUM_CNT       2
#define DMAC_PSM_TIMER_BUSY_CNT         2


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint32 g_device_wlan_pm_timeout;
extern oal_uint32 g_pm_timer_restart_cnt;
extern oal_uint8  g_uc_max_powersave;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
struct dmac_tim_ie {
    oal_uint8 uc_tim_ie;               /* MAC_EID_TIM */
    oal_uint8 uc_tim_len;
    oal_uint8 uc_dtim_count;           /* DTIM count */
    oal_uint8 uc_dtim_period;          /* DTIM period */
    oal_uint8 uc_tim_bitctl;           /* bitmap control */
    oal_uint8 auc_tim_bitmap[1];        /* variable-length bitmap */
}__OAL_DECLARE_PACKED;
typedef struct dmac_tim_ie dmac_tim_ie_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_psm_sta_incr_activity_cnt
 功能描述  : activity_cnt++
 输入参数  : pst_sta_pm_handle:状态机结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_sta_incr_activity_cnt(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    pst_sta_pm_handle->ul_tx_rx_activity_cnt++;
}
/*****************************************************************************
 函 数 名  : dmac_psm_get_more_data_sta
 功能描述  : 检查是否有moredata
 输入参数  : pst_sta_pm_handle:状态机结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_get_more_data_sta(mac_ieee80211_frame_stru *pst_frame_hdr)
{
    return (oal_uint8)(pst_frame_hdr->st_frame_control.bit_more_data);

}
/*****************************************************************************
 函 数 名  : dmac_psm_sta_reset_activity_cnt
 功能描述  : reset activity cnt
 输入参数  : pst_sta_pm_handle:状态机结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_sta_reset_activity_cnt(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    pst_sta_pm_handle->ul_tx_rx_activity_cnt = 0;
}
/*****************************************************************************
 函 数 名  : dmac_psm_sta_is_activity_cnt_zero
 功能描述  : 判断 activity cnt 是否为0
 输入参数  : pst_sta_pm_handle:状态机结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_sta_is_activity_cnt_zero(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    if (0 == pst_sta_pm_handle->ul_tx_rx_activity_cnt)
    {
      return OAL_TRUE;
    }
    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : dmac_is_ac_legacy
 功能描述  : sta下判断当前ac是是否是传统ac
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_netbuf:netbuf结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_ac_legacy(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint8    uc_ac;
    mac_cfg_uapsd_sta_stru  st_uapsd_cfg_sta;

    uc_ac = mac_get_cb_ac(pst_tx_ctl);
    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;

    if(uc_ac < WLAN_WME_AC_BUTT)
    {
        if((st_uapsd_cfg_sta.uc_trigger_enabled[uc_ac] == 0) &&
        (st_uapsd_cfg_sta.uc_delivery_enabled[uc_ac] == 0))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : dmac_is_legacy_ac_present
 功能描述  : sta下判断四种是否有传统的ac
 输入参数  : pst_dmac_vap:dmac_vap 结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_legacy_ac_present(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8               uc_ac;
    mac_cfg_uapsd_sta_stru  st_uapsd_cfg_sta;

    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;

    for(uc_ac = 0; uc_ac < WLAN_WME_AC_BUTT; uc_ac++)
    {
        if((st_uapsd_cfg_sta.uc_trigger_enabled[uc_ac] == 0) &&
           (st_uapsd_cfg_sta.uc_delivery_enabled[uc_ac] == 0))
           return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_is_legacy_ac
 功能描述  : sta下判断当前ac是是否是传统ac
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_netbuf:netbuf结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_legacy_ac(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru   *pst_tx_ctl)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        return dmac_is_ac_legacy(pst_dmac_vap, pst_tx_ctl);
    }
#endif /* WLAN_FEATURE_STA_UAPSD */

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : dmac_is_any_legacy_ac_present
 功能描述  : checks if any legacy AC is present for the STA
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_netbuf:netbuf结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_any_legacy_ac_present(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        return dmac_is_legacy_ac_present(pst_dmac_vap);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

    return OAL_TRUE;
}

/* This function checks if a PS Poll Response is pending */
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_ps_poll_rsp_pending(dmac_vap_stru *pst_dmac_vap)
{
    return pst_dmac_vap->uc_ps_poll_pending;
}

/* This function sets the PS Poll Response pending flag */
OAL_STATIC OAL_INLINE oal_void dmac_set_ps_poll_rsp_pending(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_val)
{
    pst_dmac_vap->uc_ps_poll_pending = uc_val;
}

/*****************************************************************************
 函 数 名  : dmac_process_rx_process_data_sta_prot
 功能描述  : 基于其他协议处理接收帧(uapsd p2p节能等)
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_netbuf:netbuf结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_process_rx_process_data_sta_prot(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buf)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if (OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_rx_process_data_sta(pst_dmac_vap, pst_buf);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

#ifdef _PRE_WLAN_FEATURE_P2P
    dmac_set_ps_poll_rsp_pending(pst_dmac_vap, OAL_FALSE);
#endif

}
/*****************************************************************************
 函 数 名  : dmac_psm_process_tx_process_data_sta_prot
 功能描述  : 基于其他协议处理发送帧(uapsd p2p节能等)
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_tx_ctl:tx cb结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_process_tx_process_data_sta_prot(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if (OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        return dmac_uapsd_tx_process_data_sta(pst_dmac_vap, pst_tx_ctl);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

    return STA_PWR_SAVE_STATE_ACTIVE;
}
/*****************************************************************************
 函 数 名  : dmac_psm_process_tx_complete_sta_prot
 功能描述  : 基于其他协议处理发送完成中断(uapsd p2p节能等)
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_tx_ctl:tx cb结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_process_tx_complete_sta_prot(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_dscr_status, oal_netbuf_stru *pst_netbuf)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_process_tx_complete_sta(pst_dmac_vap, uc_dscr_status, pst_netbuf);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
}
/*****************************************************************************
 函 数 名  : dmac_psm_process_tx_complete_sta_prot
 功能描述  : handles TIM set event for STA mode based on the protocol
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_tx_ctl:tx cb结构体
 输出参数  : OAL_TRUE/OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_process_tim_set_sta_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_trigger_sp_sta(pst_dmac_vap);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
}
/*****************************************************************************
 函 数 名  : dmac_is_sta_fast_ps_enabled
 功能描述  : 是否开启fast ps 节能模式
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_sta_fast_ps_enabled(mac_sta_pm_handler_stru  *pst_sta_pm_handle)
{
    if((oal_uint8)(pst_sta_pm_handle->uc_vap_ps_mode)  >= (oal_uint8)MIN_PSPOLL_PS)
    {
        return OAL_FALSE;
    }
    else
    {
        return OAL_TRUE;
    }
}
/*****************************************************************************
 函 数 名  : dmac_can_sta_doze_prot
 功能描述  : This function checks if the STA can doze based on the protocol defined
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint8 dmac_can_sta_doze_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    /* If the AP is UAPSD capable and UAPSD service period is in progress    */
    /* or STA is waiting for UAPSD service period to start the STA cannot go */
    /* to doze mode.                                                         */
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        if (OAL_FALSE == dmac_is_uapsd_sp_not_in_progress(pst_mac_sta_pm_handle))
        {
            return OAL_FALSE;
        }
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
    return OAL_TRUE;
}
/*****************************************************************************
 函 数 名  : dmac_send_ps_poll_to_AP_prot
 功能描述  : Set the P2P PS Poll pending flag whenever a PS-Poll frame is sent to AP
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_send_ps_poll_to_ap_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_P2P
    dmac_set_ps_poll_rsp_pending(pst_dmac_vap, OAL_TRUE);
#endif /* #if  defined(_PRE_WLAN_FEATURE_P2P)*/
}


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void dmac_psm_tx_set_power_mgmt_bit(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);

extern oal_void dmac_psm_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, hal_tx_dscr_stru  *pst_dscr, oal_netbuf_stru *pst_netbuf);

extern oal_void dmac_psm_process_tbtt_sta(dmac_vap_stru *pst_dmac_vap,mac_device_stru  *pst_mac_device);

extern oal_void  dmac_psm_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buf);

extern oal_uint8 dmac_psm_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);
extern oal_void dmac_psm_max_powersave_enable(mac_device_stru *pst_mac_device);
extern oal_void dmac_psm_update_dtime_period(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_mib_dtim_period,oal_uint32 ul_beacon_period);
extern oal_void dmac_psm_update_keepalive(dmac_vap_stru *pst_dmac_vap);

extern oal_uint32 dmac_send_null_frame_to_ap(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_psm, oal_bool_enum_uint8 en_qos);
extern oal_uint32 dmac_send_pspoll_to_ap(dmac_vap_stru *pst_dmac_vap);

extern oal_void dmac_psm_start_activity_timer(dmac_vap_stru *pst_dmac_vap, mac_sta_pm_handler_stru *pst_sta_pm_handle);
extern oal_uint32 dmac_psm_is_tim_dtim_set(dmac_vap_stru *pst_dmac_vap, oal_uint8* puc_tim_elm);
extern oal_void dmac_psm_process_tim_elm(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_void  dmac_psm_recover_ps_abb_state(oal_void);
extern oal_uint32 dmac_psm_alarm_callback(void *p_arg);
extern oal_uint8  dmac_psm_get_state(dmac_vap_stru* pst_dmac_vap);
extern oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap);
extern oal_uint32 dmac_psm_process_fast_ps_state_change(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_psm);
extern oal_void dmac_psm_init_null_frm_cnt(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_inc_null_frm_ofdm_succ(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_dec_null_frm_ofdm_succ(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_inc_null_frm(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_dec_null_frm(dmac_vap_stru *pst_dmac_vap);

#endif/*_PRE_WLAN_FEATURE_STA_PM*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_psm_sta.h */
