/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_uapsd_sta.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年12月19日
  最近修改   :
  功能描述   : dmac_uapsd_sta.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_UAPSD_STA_H__
#define __DMAC_UAPSD_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "dmac_ext_if.h"
#include "dmac_sta_pm.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_UAPSD_STA_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* TAG-ITTIAM新增代码合入 */
#define DMAC_STA_EOSP_TIMEOUT_CNT   2      /* 2 TBTTS */


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
 函 数 名  : dmac_is_ap_uapsd_capable
 功能描述  : 检查对端ap是否开启UAPSD能力
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_ap_uapsd_capable(dmac_vap_stru *pst_dmac_vap)
{
    return pst_dmac_vap->st_vap_base_info.uc_uapsd_cap;
}

/*****************************************************************************
 函 数 名  : dmac_is_delivery_enabled
 功能描述  : 某个ac是否delivery enabled
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_delivery_enabled(dmac_vap_stru *pst_dmac_vap,  oal_uint8  uc_tid)
{
    oal_uint8                uc_ac;
    mac_cfg_uapsd_sta_stru   st_uapsd_cfg_sta;

    uc_ac = WLAN_WME_TID_TO_AC(uc_tid);
    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;
    return st_uapsd_cfg_sta.uc_delivery_enabled[uc_ac];
}
/*****************************************************************************
 函 数 名  : dmac_is_trigger_enabled
 功能描述  : 某个ac是否trigger enabled
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_trigger_enabled(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_tid)
{
    oal_uint8                uc_ac;
    mac_cfg_uapsd_sta_stru   st_uapsd_cfg_sta;

    uc_ac = WLAN_WME_TID_TO_AC(uc_tid);
    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;
    return st_uapsd_cfg_sta.uc_trigger_enabled[uc_ac];
}
/*****************************************************************************
 函 数 名  : dmac_is_trigger_frame
 功能描述  : 检查某个帧是否是 WMM PS trigger frame
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint8 dmac_is_trigger_frame(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8  uc_tid)
{
    mac_ieee80211_frame_stru            *pst_mac_header;
    oal_uint8                            uc_subtype;

    pst_mac_header = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);
    uc_subtype = mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);

    /* A trigger frame is a QoS Data or QoS Null frame from a WMM STA in     */
    /* power save mode associated with an AC the WMM STA has configured to   */
    /* be a trigger-enabled AC.                                              */
    if((uc_subtype == (WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA)) || (uc_subtype == (WLAN_FC0_SUBTYPE_QOS_NULL | WLAN_FC0_TYPE_DATA)))
    {
        if(dmac_is_trigger_enabled(pst_dmac_vap, uc_tid) == OAL_TRUE)
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : dmac_get_eosp
 功能描述  : 返回某个QOS帧里的EOSP BIT.
 输入参数  : pst_buf:netbuf结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  dmac_get_eosp(oal_netbuf_stru *pst_buf)
{
    mac_ieee80211_qos_frame_stru *pst_qos_frame_hdr;

    pst_qos_frame_hdr = (mac_ieee80211_qos_frame_stru *)OAL_NETBUF_HEADER(pst_buf);
    return pst_qos_frame_hdr->bit_qc_eosp;

}
/*****************************************************************************
 函 数 名  : dmac_get_eosp
 功能描述  : 检查uapsd service period 是否 in progress
 输入参数  : pst_mac_sta_pm_handle:STA PM结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_uapsd_sp_not_in_progress(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(DMAC_SP_NOT_IN_PROGRESS == pst_mac_sta_pm_handle->uc_uaspd_sp_status)
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}
/*****************************************************************************
 函 数 名  : dmac_get_eosp
 功能描述  : 检查uapsd service period 是否 WAIT START
 输入参数  : pst_mac_sta_pm_handle:STA PM结构体
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_uapsd_sp_wait_in_progress(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(pst_mac_sta_pm_handle->uc_uaspd_sp_status == DMAC_SP_WAIT_START)
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : dmac_wait_uapsd_sp_start
 功能描述  : This function waits for a UAPSD service period to start. Note that the
             service period will be started only after successful transmission of the
             trigger frame. In case the trigger frame is timed out the STA will try to
             retransmit a trigger frame. Also if it is already waiting for a service
             period to start or if a service period is in progress no wait is required
             and hence the flag is not set.
 输入参数  : pst_mac_sta_pm_handle:STA PM结构体
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_wait_uapsd_sp_start(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(DMAC_SP_NOT_IN_PROGRESS == pst_mac_sta_pm_handle->uc_uaspd_sp_status)
    {
       pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_WAIT_START;
    }

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_spsw);
}
/*****************************************************************************
函 数 名  : dmac_start_uapsd_sp
功能描述  : This function starts a UAPSD service period
输入参数  : pst_mac_sta_pm_handle:STA PM结构体
输出参数  : 无
返 回 值  : oal_void
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2014年12月20日
   作    者   : 
   修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_start_uapsd_sp(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_IN_PROGRESS;

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_sps);
}
/*****************************************************************************
函 数 名  : dmac_start_uapsd_sp
功能描述  : This function stops a UAPSD service period
输入参数  : pst_mac_sta_pm_handle:STA PM结构体
输出参数  : 无
返 回 值  : oal_void
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2014年12月20日
   作    者   : 
   修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_stop_uapsd_sp(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_NOT_IN_PROGRESS;

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_spe);
}

/*****************************************************************************
函 数 名  : dmac_start_uapsd_sp
功能描述  : returns the highest priority which is trigger enabled
输入参数  : pst_dmac_vap:dmac vap 结构体
输出参数  : 无
返 回 值  : oal_uint8
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2014年12月20日
   作    者   : 
   修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_get_highest_trigger_enabled_priority(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_FEATURE_WLAN_STA_UAPSD
    oal_uint8 uc_tid = WLAN_TID_MAX_NUM;

    /* Check for highest priority trigger enabled AC */
    if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_VOICE) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_VOICE;
    }
    else if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_VIDEO) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_VIDEO;
    }
    else if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_BEST_EFFORT) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_BEST_EFFORT;
    }
    else if (dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_BACKGROUND) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_BACKGROUND;
    }

    return uc_tid;
#else
    return WLAN_TIDNO_VOICE;
#endif /* _PRE_FEATURE_WLAN_STA_UAPSD */
}
/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  dmac_uapsd_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);

extern oal_uint8 dmac_uapsd_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);

extern oal_void  dmac_uapsd_process_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_dscr_status, oal_netbuf_stru *pst_netbuf);

extern oal_void dmac_uapsd_trigger_sp_sta(dmac_vap_stru *pst_dmac_vap);

#endif /* _RE_WLAN_FEATURE_STA_UAPSD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_uapsd_sta.h */
