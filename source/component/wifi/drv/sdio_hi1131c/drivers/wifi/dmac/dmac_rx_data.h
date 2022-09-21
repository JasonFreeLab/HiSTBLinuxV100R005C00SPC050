/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_rx_data.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : dmac_rx_data.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_RX_DATA_H__
#define __DMAC_RX_DATA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "dmac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_uapsd.h"
#include "dmac_alg.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_11i.h"
#include "dmac_arp_offload.h"
#include "oam_ext_if.h"
#include "mac_device.h"

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#endif

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
#include "dmac_rekey/dmac_rekey_offload.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RX_DATA_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_EVALUATED_AVG_PADDING_LEN   2
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_int32 g_l_proxysta_feature;
#endif

#define DMAC_STAT_RX_PKT_COUNT (2048)
#define DMAC_STAT_RX_PKT_COUNT_OFFSET (11)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_uint8 g_uc_hilink_switch;
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
/* MAC ERROR函数处理结构体 */
typedef struct
{
    oal_void      (* p_func)(mac_device_stru *pst_dev, oal_uint32 ul_para);
    oal_uint32    ul_param;
}dmac_error_proc_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern oal_uint32  dmac_rx_filter_frame_ap(
                mac_vap_stru               *pst_vap,
                dmac_rx_ctl_stru           *pst_cb_ctrl);
extern oal_uint32  dmac_rx_filter_frame_sta(
                mac_vap_stru               *pst_vap,
                dmac_rx_ctl_stru           *pst_cb_ctrl,
                dmac_user_stru             *pst_dmac_user);
extern oal_bool_enum_uint8  dmac_rx_check_mgmt_replay_failure(dmac_rx_ctl_stru  *pst_cb_ctrl);

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1131C_DEV)
/*****************************************************************************
 函 数 名  : dmac_rx_fcs_statistic_info
 功能描述  : 统计接收到的帧的FCS的正确性
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_rx_fcs_statistic_info(
                mac_ieee80211_frame_stru    *pst_frame_hdr,
                mac_vap_stru                *pst_vap,
                dmac_rx_ctl_stru            *pst_cb_ctrl)
{
    oal_uint8   *puc_destination_addr;  /* 目的地址 */
    oal_uint32   ul_mac_addr_cmp;       /* MAC ADDR比较，相等为0 */

    /* 获取目的地址 */
    mac_rx_get_da(pst_frame_hdr, &puc_destination_addr);

    g_ast_rx_fcs_statistic[pst_vap->uc_vap_id].ul_total_num++;

    if (HAL_RX_SUCCESS == pst_cb_ctrl->st_rx_status.bit_dscr_status)            /* FCS正确 */
    {
        /* 发给自己的帧的数目统计 */
        ul_mac_addr_cmp = oal_compare_mac_addr(pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, puc_destination_addr);
        if (0 == ul_mac_addr_cmp)   /* 地址相同 */
        {
            g_ast_rx_fcs_statistic[pst_vap->uc_vap_id].ul_self_fcs_correct++;
        }
        else
        {
            g_ast_rx_fcs_statistic[pst_vap->uc_vap_id].ul_other_fcs_correct++;
        }
    }
    else if (HAL_RX_FCS_ERROR == pst_cb_ctrl->st_rx_status.bit_dscr_status)     /* FCS错误 */
    {
        /* 数目统计，该帧是否发给自己未作统计 */
        g_ast_rx_fcs_statistic[pst_vap->uc_vap_id].ul_total_fcs_error++;
    }
}
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_get_dscr_info
 功能描述  : 设置描述符信息，并且将信息存储到对应的netbuf的cb字段中
 输入参数  : pul_dscr为软件可见的描述符首地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_rx_get_dscr_info(
                hal_to_dmac_device_stru    *pst_device,
                oal_uint32                 *pul_dscr,
                dmac_rx_ctl_stru           *pst_cb_ctrl)
{
    hal_rx_ctl_stru *pst_hal_rx_ctl;
    oal_uint32       ul_rx_dscr_len;

    pst_hal_rx_ctl = (hal_rx_ctl_stru *)pst_cb_ctrl;

    /* 获取接收描述符信息 */
    hal_rx_get_info_dscr(pst_device,
                         pul_dscr,
                         pst_hal_rx_ctl,
                         &pst_cb_ctrl->st_rx_status,
                         &pst_cb_ctrl->st_rx_statistic);

    if (OAL_UNLIKELY(MAC_GET_RX_CB_MAC_HEADER_LEN(&(pst_cb_ctrl->st_rx_info)) > pst_cb_ctrl->st_rx_info.us_frame_len))
    {
        hal_rx_get_size_dscr(pst_device, &ul_rx_dscr_len);
        oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    mac_set_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info), pst_hal_rx_ctl->pul_mac_hdr_start_addr);
#endif
   // pst_cb_ctrl->st_rx_info.pul_mac_hdr_start_addr   = st_hal_rx_ctl.pul_mac_hdr_start_addr;
}

/*****************************************************************************
 函 数 名  : dmac_rx_data_ps_process
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_data_ps_process(
                dmac_vap_stru          *pst_dmac_vap,
                dmac_user_stru         *pst_dmac_user,
                oal_netbuf_stru        *pst_netbuf)
{
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    dmac_rx_ctrl_enum_uint8           en_ret;
#endif

    if (WLAN_VAP_MODE_BSS_STA == dmac_vap_get_bss_type(&(pst_dmac_vap->st_vap_base_info)))
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        /* 节能特性处理 */
        dmac_psm_rx_process_data_sta(pst_dmac_vap, pst_netbuf);
#endif
    }
    else if (WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* psm节能处理 */
        dmac_psm_rx_process(pst_dmac_vap, pst_dmac_user, pst_netbuf);

#ifdef _PRE_WLAN_FEATURE_UAPSD
        /* uapsd节能特性 */
        dmac_uapsd_rx_trigger_check( pst_dmac_vap, pst_dmac_user, pst_netbuf);
#endif
    }

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    en_ret = dmac_is_wpa_group_msg(pst_dmac_user, pst_dmac_vap, pst_netbuf);
    switch (en_ret)
    {
        case DMAC_RX_CTRL_REKEY_GOON:
            if (DMAC_RX_CTRL_JUST_DROP == dmac_rx_wpa_group_msg_process(pst_dmac_user, pst_dmac_vap, pst_netbuf))
            {
                /* 已经在DMAC侧成功回复rekey报文，报告Fail，以丢弃报文 */
                return OAL_FAIL;
            }
            break;
        case DMAC_RX_CTRL_OTHERS_GOON:
            break;
        case DMAC_RX_CTRL_JUST_DROP:
            return OAL_FAIL;
        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_rx_data_ps_process::dmac_is_wpa_group_msg unexpected return[%x]!}", en_ret);
            break;
    }
#endif

#ifndef _PRE_WLAN_PROFLING_MIPS
     /* arp offload 过滤代码需要在低功耗处理后 */
#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    if (DMAC_RX_FRAME_CTRL_DROP == dmac_ao_process_arp_and_mcast(pst_dmac_vap, pst_dmac_user, pst_netbuf))
    {
        g_ul_arpoffload_drop_frame++;
        return OAL_FAIL;
    }
#endif
#endif /* _PRE_WLAN_PROFLING_MIPS */
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_rx_rssi_rate_stat
 功能描述  : 接收帧处理接口
 输入参数  : pst_user : User指针
             pst_rx_stats : 接收统计量
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_rx_rssi_rate_stat(dmac_user_stru *pst_dmac_user, hal_rx_statistic_stru *pst_rx_stats, mac_device_stru *pst_mac_device)
{
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32 ul_rate_kbps = 0;

    pst_hal_device = pst_mac_device->pst_device_stru;

    pst_hal_device->l_rx_rssi = pst_rx_stats->c_rssi_dbm;

    /* 获取速率大小 */
    dmac_alg_get_rate_by_table(&pst_dmac_user->st_user_base_info, pst_rx_stats, &ul_rate_kbps);

    pst_hal_device->ul_rx_rate = ul_rate_kbps;
}

/*****************************************************************************
 函 数 名  : dmac_rx_record_tid
 功能描述  : 记录最新数据帧的tid,方便wmm动态开关的自动化测试
 输入参数  :
             mac_ieee80211_frame_stru:     帖头指针
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_rx_record_tid(mac_vap_stru  *pst_vap, mac_ieee80211_frame_stru  *pst_frame)
{
    mac_device_stru          *pst_mac_dev;
    oal_uint8                *pucTid = OAL_PTR_NULL;
    oal_uint8                ucTid = 0;

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_frame || OAL_PTR_NULL == pst_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 不是Qos Data */
    if((WLAN_DATA_BASICTYPE != pst_frame->st_frame_control.bit_type)
    || (WLAN_QOS_DATA != pst_frame->st_frame_control.bit_sub_type))
    {
        return OAL_FAIL;
    }

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_dev)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pucTid = (oal_uint8 *)pst_frame + MAC_80211_FRAME_LEN;
    ucTid  = (*pucTid & 0xf); /* tid对应QOS Ctl 字段的低4位 */
    pst_mac_dev->en_tid = ucTid;
    return OAL_SUCC;


}


/*****************************************************************************
 函 数 名  : dmac_rx_update_aggr_mib
 功能描述  : 更新接收到的mpdu的数目
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_rx_update_aggr_mib(mac_vap_stru *pst_vap, oal_uint16 us_mpdu_num)
{
    if ((0 == us_mpdu_num) || (0 == pst_vap->uc_vap_id))
    {
        return;
    }

    pst_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11MPDUInReceivedAMPDUCount += us_mpdu_num;
}

/*****************************************************************************
 函 数 名  : dmac_rx_update_mib_11n
 功能描述  : 更新接收流程中与11n相关的MIB值
 输入参数  : (1)要操作的vap的指针
             (2)接收帧对应的控制信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_rx_update_mib_11n(mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_cb_ctrl)
{
    /* 更新ul_dot11ReceivedAMSDUCount值 */
    if (pst_cb_ctrl->st_rx_info.bit_amsdu_enable)
    {
        /* 更新receive amsdu nums值*/
        pst_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11ReceivedAMSDUCount++;

        /* 更新receive amsdu nums值*/
        pst_vap->pst_mib_info->st_wlan_mib_counters.ull_dot11dot11ReceivedOctetsInAMSDUCount += pst_cb_ctrl->st_rx_info.us_frame_len;
    }
}

OAL_STATIC OAL_INLINE oal_void dmac_rx_pingpong_list_lock(hal_to_dmac_device_stru  *pst_device)
{
    /*AMP系统锁住CPU中断消耗MIPS较少，而SMP必须锁住MAC RX中断!*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_irq_disable();
#else
    /*TBD:lock the mac rx irq,对应的偏移是0*/
    oal_irq_disable();
    #if (_PRE_TEST_MODE_UT != _PRE_TEST_MODE)
    hal_mask_interrupt(pst_device, 0);
    #endif
#endif
}

OAL_STATIC OAL_INLINE oal_void dmac_rx_pingpong_list_unlock(hal_to_dmac_device_stru  *pst_device)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_irq_enable();
#else
    /*TBD:unlock the mac rx irq,对应的偏移是0*/
    #if (_PRE_TEST_MODE_UT != _PRE_TEST_MODE)
    hal_unmask_interrupt(pst_device, 0);
    #endif
    oal_irq_enable();
#endif
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_rx_process_data_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_mac_error_process_event(frw_event_mem_stru *pst_event_mem);
oal_uint32  dmac_rx_process_data_frame(mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_cb_ctrl, oal_netbuf_stru *pst_netbuf);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  dmac_soc_error_process_event(frw_event_mem_stru *pst_event_mem);
#endif
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_filter_mpdu(dmac_rx_ctl_stru *pst_cb_ctrl, oal_uint16 us_dscr_num)
{
    /* 描述符异常:接收到的为A-MSDU帧，同时该描述符非该MPDU的第一个描述符 */
    if (OAL_UNLIKELY((OAL_TRUE == pst_cb_ctrl->st_rx_info.bit_amsdu_enable) && (OAL_FALSE == pst_cb_ctrl->st_rx_info.bit_is_first_buffer)))
    {
        //OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_filter_mpdu::the control netbuf is not the first netbuf of a amsdu.}");
        return OAL_ERR_CODE_RX_DSCR_AMSDU_DISORDER;
    }

    /* 描述符异常:获取的buffer数目大于剩余的描述符的个数 */
    if (OAL_UNLIKELY(pst_cb_ctrl->st_rx_info.bit_buff_nums > us_dscr_num))
    {
        //OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_filter_mpdu::the numbers of netbuf exceeds the remianing netbufs.}");
        return OAL_ERR_CODE_RX_DSCR_LOSE;
    }

    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_filter_frame(
                                    mac_vap_stru           *pst_vap,
                                    dmac_rx_ctl_stru       *pst_cb_ctrl,
                                    dmac_user_stru             *pst_dmac_user)
{
    if (WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(pst_vap))
    {
        return dmac_rx_filter_frame_ap(pst_vap, pst_cb_ctrl);
    }
    else if (WLAN_VAP_MODE_BSS_STA == dmac_vap_get_bss_type(pst_vap))
    {
        return dmac_rx_filter_frame_sta(pst_vap, pst_cb_ctrl, pst_dmac_user);
    }

    return OAL_FAIL;
}

extern dmac_rx_frame_ctrl_enum_uint8  dmac_rx_process_frame(
                mac_vap_stru                   *pst_vap,
                dmac_rx_ctl_stru               *pst_cb_ctrl,
                oal_netbuf_stru                *pst_netbuf,
                oal_netbuf_head_stru           *pst_netbuf_header);

#if 0
extern oal_uint32 dmac_start_stat_rssi(dmac_user_stru *pst_dmac_user);
extern oal_uint32 dmac_get_stat_rssi(dmac_user_stru *pst_dmac_user, oal_int8 *pc_tx_rssi, oal_int8 *pc_rx_rssi);
extern oal_uint32 dmac_stop_stat_rssi(dmac_user_stru *pst_dmac_user);
#endif
extern oal_uint32 dmac_get_stat_rate(dmac_user_stru *pst_dmac_user, oal_uint32 *pul_tx_rate, oal_uint32 *pul_rx_rate);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_rx_data.h */
