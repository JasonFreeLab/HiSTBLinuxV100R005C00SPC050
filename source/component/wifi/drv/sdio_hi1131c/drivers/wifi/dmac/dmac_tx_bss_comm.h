/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_tx_bss_comm.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月15日
  最近修改   :
  功能描述   : dmac_tx_bss_comm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月15日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_TX_BSS_COMM_H__
#define __DMAC_TX_BSS_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "hal_ext_if.h"
#include "oal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "dmac_vap.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_alg.h"
#include "wlan_types.h"
#include "oal_net.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_BSS_COMM_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_MAX_FIFO_PUT       10  /* = FIFO DEHPTH + PREFETCH */
#define DMAC_MAX_PENDING_RETRY  6

typedef oal_uint32 (*p_dmac_tx_parse_mpdu_func)(oal_netbuf_stru *pst_netbuf, hal_tx_msdu_address_params *past_msdu);


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
extern oal_uint8 g_auc_default_mac_to_phy_protocol_mapping[WLAN_PROTOCOL_BUTT];
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
typedef struct
{
    hal_to_dmac_device_stru *pst_hal_device;
    mac_tx_ctl_stru         *pst_tx_cb;
    hal_tx_dscr_stru        *pst_tx_dscr;
    oal_netbuf_stru         *pst_netbuf;
    oal_uint8               *puc_mac_hdr_addr;
    oal_uint8               *puc_mac_payload_addr;
    oal_uint8                auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint16               us_mac_frame_len;      /* 帧头+帧体长度 */
    oal_uint8                uc_mac_hdr_len;
    oal_switch_enum_uint8    en_frame_switch;
    oal_switch_enum_uint8    en_cb_switch;
    oal_switch_enum_uint8    en_dscr_switch;
}dmac_tx_dump_param_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
extern oal_uint32  dmac_tx_data(
    dmac_vap_stru            *pst_dmac_vap,
    dmac_user_stru           *pst_dmac_user,
    mac_tx_ctl_stru          *pst_tx_ctl,
    oal_dlist_head_stru      *pst_tx_dscr_list_hdr,
    hal_tx_ppdu_feature_stru *pst_ppdu_feature,
    hal_tx_txop_alg_stru     *pst_txop_alg);
extern oal_uint32  dmac_tx_process_data_event(frw_event_mem_stru *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_tx_get_amsdu_params(
                                        oal_netbuf_stru  *pst_netbuf,
                                        mac_tx_ctl_stru  *pst_tx_ctl,
                                        hal_tx_mpdu_stru *pst_mpdu);
#endif
extern oal_uint32  dmac_tx_process_data(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_uint32  dmac_tx_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf_mgmt, oal_uint16 us_len);
extern oal_uint32  dmac_tid_tx_queue_remove(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, dmac_tid_stru *pst_tid_queue, oal_uint8 uc_dscr_num);
extern oal_uint32  dmac_tid_tx_queue_remove_ampdu(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_user, dmac_tid_stru *pst_tid_queue, oal_uint8 uc_mpdu_num);
extern oal_void  dmac_tx_excp_free_dscr(oal_dlist_head_stru *pst_tx_dscr_list_hdr, hal_to_dmac_device_stru *pst_hal_device);
extern oal_netbuf_stru* dmac_tx_dequeue_first_mpdu(oal_netbuf_head_stru  *pst_netbuf_head);
extern oal_uint32  dmac_tx_excp_free_netbuf(oal_netbuf_stru *pst_netbuf);
extern oal_uint32  dmac_flush_txq_to_tid_of_vo(hal_to_dmac_device_stru *pst_hal_device);
#if defined (_PRE_WLAN_FEATURE_UAPSD) || defined (_PRE_WLAN_FEATURE_STA_PM)
extern oal_uint32 dmac_send_qosnull(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_ac, oal_bool_enum_uint8 en_ps);
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32  dmac_tx_force(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint16 us_len, oal_uint8 uc_mgmt);
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_tx_set_htc_field
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_set_htc_field(
                                    hal_to_dmac_device_stru  *pst_hal_device,
                                    hal_tx_dscr_stru         *pst_tx_dscr,
                                    mac_tx_ctl_stru          *pst_tx_ctl,
                                    hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    mac_ieee80211_qos_htc_frame_addr4_stru  *pst_mac_ieee80211_qos_htc_frame_addr4;
    mac_ieee80211_qos_htc_frame_stru        *pst_mac_ieee80211_qos_htc_frame;
    oal_uint8                                uc_mac_header_length;

    if (OAL_TRUE == mac_get_cb_is_use_4_addr(pst_tx_ctl))
    {
        pst_mac_ieee80211_qos_htc_frame_addr4  = (mac_ieee80211_qos_htc_frame_addr4_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
        pst_mac_ieee80211_qos_htc_frame_addr4->ul_htc = (BIT22 | BIT23);
        pst_mac_ieee80211_qos_htc_frame_addr4->st_frame_control.bit_order = 1;
        uc_mac_header_length                   = OAL_SIZEOF(mac_ieee80211_qos_htc_frame_addr4_stru);
    }
    else
    {
        pst_mac_ieee80211_qos_htc_frame = (mac_ieee80211_qos_htc_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
        pst_mac_ieee80211_qos_htc_frame->auc_htc[2] = (oal_uint8)(BIT6 | BIT7);
        pst_mac_ieee80211_qos_htc_frame->st_frame_control.bit_order = 1;
        uc_mac_header_length                   = OAL_SIZEOF(mac_ieee80211_qos_htc_frame_stru);
    }

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = uc_mac_header_length;
    if (pst_ppdu_feature->uc_ampdu_enable == OAL_TRUE)
    {
        pst_ppdu_feature->ul_ampdu_length  += (OAL_SIZEOF(mac_ieee80211_qos_htc_frame_stru) - OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    }

    /* 修改描述符中mac 帧头长度 */
    hal_tx_set_dscr_modify_mac_header_length(pst_hal_device,pst_tx_dscr, uc_mac_header_length);

}

/*****************************************************************************
 函 数 名  : dmac_free_tx_dscr
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_free_tx_dscr(hal_tx_dscr_stru *pst_tx_dscr)
{
    oal_netbuf_stru   *pst_netbuf = OAL_PTR_NULL;

    pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
    pst_tx_dscr->pst_skb_start_addr = OAL_PTR_NULL;

    OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
    if (OAL_PTR_NULL != pst_netbuf)
    {
        dmac_tx_excp_free_netbuf(pst_netbuf);
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_free_tx_dscr::pst_netbuf null.}");
    }
}

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
/*****************************************************************************
 函 数 名  : dmac_tx_get_spec_mode_ucast_data_params
 功能描述  : 获取针对特定协议模式用户的单播数据帧发送参数
 输入参数  : pst_dmac_vap
             pst_dmac_user
             pst_tx_ctl
 输出参数  : ppst_txop_alg
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_get_spec_mode_ucast_data_params(
                                                   dmac_vap_stru         *pst_dmac_vap,
                                                   dmac_user_stru        *pst_dmac_user,
                                                   mac_tx_ctl_stru       *pst_tx_ctl,
                                                   hal_tx_txop_alg_stru  **ppst_txop_alg)
{
    wlan_phy_protocol_enum_uint8 en_phy_protocol = g_auc_default_mac_to_phy_protocol_mapping[pst_dmac_user->st_user_base_info.en_avail_protocol_mode];

    if (en_phy_protocol >= WLAN_PHY_PROTOCOL_BUTT)
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{dmac_tx_get_spec_mode_ucast_data_params::invalid en_phy_protocol(%u), caused by en_avail_protocol_mode(%u).}",
            en_phy_protocol, pst_dmac_user->st_user_base_info.en_avail_protocol_mode);
        return OAL_FAIL;
    }

    /* 若当前user采用的protocol所对应的配置参数valid, 则采用该协议下的ucast data发送参数 */
    if ((WLAN_VHT_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_vht_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_vht);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_vht;
    }
    else if ((WLAN_HT_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_ht_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_ht);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_ht;
    }
    else if ((WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11ag_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_11ag);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_11ag;
    }
    else if ((WLAN_11B_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11b_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_11b);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_11b;
    }
    /* 否则, 还是采用默认的ucast data发送参数 */
    else
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
    }

    return OAL_SUCC;
}
#endif


/*****************************************************************************
 函 数 名  : dmac_tx_get_txop_alg_params
 功能描述  : 获取发送参数
 输入参数  : 无
 输出参数  : ppst_txop_alg
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_txop_alg_params(
                                                   dmac_vap_stru         *pst_dmac_vap,
                                                   dmac_user_stru        *pst_dmac_user,
                                                   mac_tx_ctl_stru       *pst_tx_ctl,
                                                   hal_tx_txop_alg_stru  **ppst_txop_alg)
{
    if (OAL_TRUE == pst_tx_ctl->bit_is_vipframe)
    {
        *ppst_txop_alg = &pst_dmac_vap->ast_tx_mgmt_bmcast[pst_dmac_vap->st_vap_base_info.st_channel.en_band];
         return OAL_SUCC;
    }

    /* 从算法获取单播发送数据帧参数 */
    if (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
    {
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        /* 若vap下未配置针对特定协议的ucast data发送参数, 则采用默认的ucast data发送参数 */
        if (0 == pst_dmac_vap->un_mode_valid.uc_mode_param_valid)
        {
            dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
            *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
        }
        else
        {
            oal_uint32      ul_ret;
            ul_ret = dmac_tx_get_spec_mode_ucast_data_params(pst_dmac_vap, pst_dmac_user, pst_tx_ctl, ppst_txop_alg);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_get_txop_alg_params::dmac_tx_get_spec_mode_ucast_data_params fail, error code = %u}", ul_ret);
                return ul_ret;
            }
        }
    #else
        /* 从算法处获取单播数据帧速率等发送参数 */
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
    #endif
    }
    else /* 软件填写组播/广播数据帧发送参数 */
    {
        *ppst_txop_alg = &pst_dmac_vap->st_tx_data_mcast;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_get_ppdu_feature
 功能描述  : 填写ppdu feature 字段
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_init_ppdu_feature(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_mpdu_num, hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    hal_to_dmac_device_stru   *pst_hal_device_base;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_hal_device null.}");
        return;
    }
#endif

    if (OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_init_ppdu_feature::pst_hal_vap null.}");

        return;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if ((pst_dmac_vap->pst_hal_vap->uc_vap_id >= WLAN_PROXY_STA_START_ID) && (pst_dmac_vap->pst_hal_vap->uc_vap_id <= WLAN_PROXY_STA_END_ID))
    {
        /* 如果启用Repeater功能，Proxy STA的发送描述符中的TX VAP index需要填为4(和普通sta是一样的) */
        pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = WLAN_STA0_HAL_VAP_ID;
    }
    else
    {
        pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
    }
#else
    pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#endif

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index = 0;/* 用户结构体下的lut index */
    }
    else
    {
        /* addba req需要填写正确的ra lut index 以获取正确的ssn */
        pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index = pst_dmac_user->uc_lut_index; /* 用户结构体下的lut index */
        /* OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_init_ppdu_feature::uc_ra_lut_index=%d.}",
                      pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index); */
    }

    /* 单包/管理帧 发送这些字段无效初始化为0 */
    pst_ppdu_feature->uc_mpdu_num               = uc_mpdu_num;
    pst_ppdu_feature->uc_ampdu_enable           = 0;
    pst_ppdu_feature->uc_rifs_enable            = 0;
    pst_ppdu_feature->ul_ampdu_length           = 0;
    pst_ppdu_feature->us_min_mpdu_length        = 0;
    pst_ppdu_feature->en_addba_ssn_hw_bypass    = OAL_TRUE;
    pst_ppdu_feature->en_duration_hw_bypass     = OAL_FALSE;
    pst_ppdu_feature->en_retry_flag_hw_bypass   = OAL_FALSE;
    pst_ppdu_feature->en_seq_ctl_hw_bypass      = OAL_FALSE;
    pst_ppdu_feature->en_timestamp_hw_bypass    = OAL_FALSE;
    pst_ppdu_feature->en_tx_pn_hw_bypass        = OAL_FALSE;
    pst_ppdu_feature->en_long_nav_enable        = OAL_FALSE;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    if(OAL_SWITCH_ON == pst_hal_device_base->uc_al_tx_flag)
    {
        pst_ppdu_feature->en_seq_ctl_hw_bypass      = OAL_TRUE;
        pst_ppdu_feature->en_duration_hw_bypass     = OAL_TRUE;
        pst_ppdu_feature->en_retry_flag_hw_bypass   = OAL_TRUE;
    }
#endif
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_ppdu_feature
 功能描述  : 更新ppdu结构体的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_ppdu_feature(oal_netbuf_stru *pst_netbuf, hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    mac_tx_ctl_stru            *pst_cb;
    oal_uint8                   uc_frame_type = 0;           /* 802.11头 */

    pst_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    uc_frame_type = (oal_uint8)(((mac_ieee80211_frame_stru *)mac_get_cb_frame_hdr(pst_cb))->st_frame_control.bit_type);

    /* 更新非Qos帧的seq_ctl_hw_bypass 标志 */
    if ((OAL_TRUE!= mac_get_cb_is_qosdata(pst_cb)) && (2 == uc_frame_type))
    {
        pst_ppdu_feature->en_seq_ctl_hw_bypass = mac_get_cb_is_seq_ctrl_bypass(pst_cb);
    }
}

/*****************************************************************************
 函 数 名  : dmac_get_mgmt_mpdu_param
 功能描述  : 获取管理帧mpdu参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_get_mgmt_mpdu_param(oal_netbuf_stru *pst_netbuf_mgmt, mac_tx_ctl_stru *pst_tx_ctl,  oal_uint16 us_len, hal_tx_mpdu_stru *pst_mpdu)
{
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl) = 1;              /* 管理帧只有一个 */
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl) = FRW_EVENT_TYPE_WLAN_CTX;
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)   = 1;              /* 管理帧只有一个 */
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);         /* 管理帧不做amsdu聚合 */
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf_mgmt));

    /* 填写MPDU基本参数 */
    pst_mpdu->st_wmm.uc_tid_no = 0;
    pst_mpdu->st_wmm.uc_qos_enable = OAL_FALSE;
    if (WLAN_CONTROL == MAC_GET_CB_FRAME_TYPE(pst_tx_ctl))
    {
        pst_mpdu->st_wmm.uc_tid_no = mac_get_cb_tid(pst_tx_ctl);
        pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len = MAC_80211_CTL_HEADER_LEN;
    }
    else
    {
        pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len = MAC_80211_FRAME_LEN;
    }

    pst_mpdu->st_mpdu_mac_hdr.uc_num_sub_msdu = 1;

    pst_mpdu->st_mpdu_addr.ul_mac_hdr_start_addr = (oal_uint32)OAL_NETBUF_HEADER(pst_netbuf_mgmt);
    pst_mpdu->st_mpdu_addr.pst_skb_start_addr    = pst_netbuf_mgmt;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)((oal_uint8 *)OAL_NETBUF_DATA(pst_netbuf_mgmt));
#else
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)((oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf_mgmt) + pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len);
#endif

    pst_mpdu->ast_msdu_addr[0].us_msdu0_len  = us_len - pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len;

    pst_mpdu->ast_msdu_addr[0].us_msdu1_len  = 0;
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)  = pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl)             = us_len - MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl);
}

/*****************************************************************************
 函 数 名  : dmac_tx_get_txop_feature_params
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_txop_feature_params(
                dmac_vap_stru              *pst_dmac_vap,
                dmac_user_stru             *pst_dmac_user,
                hal_tx_txop_feature_stru   *pst_txop_feature)
{

    pst_txop_feature->pst_security  = &(pst_dmac_user->st_user_base_info.st_user_tx_info.st_security);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_get_mpdu_params
 功能描述  : 获取MPDU发送控制参数
 输入参数  : pst_hal_device:
             pst_dmac_vap  :
             pst_dmac_user :
             pst_netbuf    :
             pst_mpdu      :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_mpdu_params(
                oal_netbuf_stru           *pst_netbuf,
                mac_tx_ctl_stru           *pst_tx_ctl,
                hal_tx_mpdu_stru          *pst_mpdu)
{

    /* 获取MPDU相关参数 */
    pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len   = MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl);
    pst_mpdu->st_mpdu_mac_hdr.uc_num_sub_msdu  = MAC_GET_CB_NETBUF_NUM(pst_tx_ctl);

    pst_mpdu->st_wmm.en_ack_policy = mac_get_cb_ack_policy(pst_tx_ctl);
    pst_mpdu->st_wmm.uc_tid_no     = mac_get_cb_tid(pst_tx_ctl);
    pst_mpdu->st_wmm.uc_qos_enable = mac_get_cb_is_qosdata(pst_tx_ctl);

    pst_mpdu->st_mpdu_addr.ul_mac_hdr_start_addr = (oal_uint32)mac_get_cb_frame_hdr(pst_tx_ctl);
    pst_mpdu->st_mpdu_addr.pst_skb_start_addr    = pst_netbuf;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)oal_netbuf_payload(pst_netbuf);
    pst_mpdu->ast_msdu_addr[0].us_msdu0_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl);
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;
    pst_mpdu->ast_msdu_addr[0].us_msdu1_len = 0;
#else
    if (OAL_FALSE == mac_get_cb_is_amsdu(pst_tx_ctl))
    {
        pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)oal_netbuf_payload(pst_netbuf);
        pst_mpdu->ast_msdu_addr[0].us_msdu0_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl);
        pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;
        pst_mpdu->ast_msdu_addr[0].us_msdu1_len = 0;
    }
    else
    {
        return dmac_tx_get_amsdu_params(pst_netbuf, pst_tx_ctl, pst_mpdu);
    }
#endif
    return OAL_SUCC;
}



extern oal_void  dmac_proc_restore_tx_queue(hal_to_dmac_device_stru     *pst_hal_device,
                                                      hal_tx_dscr_queue_header_stru *pst_fake_queue);
extern oal_void dmac_proc_save_tx_queue(hal_to_dmac_device_stru       *pst_hal_device,
                                                  hal_tx_dscr_queue_header_stru *pst_fake_queue);

extern oal_uint32  dmac_tx_clear_tx_queue(hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32  dmac_tx_save_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_clear_fake_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_restore_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_switch_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id1, oal_uint8 uc_fake_q_id2);
extern oal_uint32  dmac_tx_fake_queue_empty_assert(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_fake_q,
                oal_uint32               ul_file_id);
#if 0
extern oal_uint32  dmac_flush_txq_to_tid(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_uint32  dmac_tx_update_protection_all_txop_alg(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_tx_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf_mgmt, oal_uint16 us_len);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_tx_bss_comm.h */
