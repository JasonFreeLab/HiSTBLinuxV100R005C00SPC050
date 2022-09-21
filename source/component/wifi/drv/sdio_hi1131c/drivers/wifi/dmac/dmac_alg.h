/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_alg.h
  版 本 号   : 初稿
  作    者   : 陈艳
  生成日期   : 2013年3月21日
  最近修改   :
  功能描述   : dmac_alg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月21日
    作    者   : 陈艳
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ALG_H__
#define __DMAC_ALG_H__

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
#include "frw_ext_if.h"
#include "dmac_alg_if.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ALG_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
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
/* 算法主结构体,挂在DEVICE上 */
typedef struct
{
    oal_uint32                              ul_alg_bitmap;    /* 算法位图，每位表示一个算法是否注册 */
    p_alg_tx_notify_func                    pa_tx_notify_func[DMAC_ALG_TX_NOTIFY_BUTT];
    p_alg_tx_complete_notify_func           pa_tx_complete_notify_func[DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT];
    p_alg_rx_notify_func                    pa_rx_notify_func[DMAC_ALG_RX_NOTIFY_BUTT];
    p_alg_update_tid_notify_func            p_tid_update_func;
    p_alg_tx_schedule_func                  p_tx_schedule_func;
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
    p_alg_tx_schedule_stat_event_notify_func                  p_tx_schedule_stat_event_notify_func;
#endif
    p_alg_downlink_flowctl_notify_func      p_downlink_flowctl_func;
    p_alg_add_assoc_user_notify_func        pa_add_assoc_user_notify_func[DMAC_ALG_ADD_USER_NOTIFY_BUTT];
    p_alg_delete_assoc_user_notify_func     pa_delete_assoc_user_notify_func[DMAC_ALG_DEL_USER_NOTIFY_BUTT];
    p_alg_create_vap_notify_func            pa_create_vap_notify_func[DMAC_ALG_ADD_VAP_NOTIFY_BUTT];
    p_alg_delete_vap_notify_func            pa_delete_vap_notify_func[DMAC_ALG_DEL_VAP_NOTIFY_BUTT];
    p_alg_cfg_channel_notify_func           pa_cfg_channel_notify_func[DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT];
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    p_alg_cfg_start_connect_notify_func     pa_cfg_start_connect_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT];
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    p_alg_cfg_btcoex_state_notify_func     pa_cfg_btcoex_state_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT];
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
    p_alg_cfg_bandwidth_notify_func         pa_cfg_bandwidth_notify_func[DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT];
    p_alg_cfg_user_bandwidth_notify_func    pa_cfg_user_bandwidth_notify_func[DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT];
    p_alg_cfg_user_protocol_notify_func     pa_cfg_user_protocol_notify_func[DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT];
#ifdef _PRE_WLAN_FEATURE_CCA_OPT
    p_alg_cfg_cca_intf_mode_notify_func     pa_cfg_cca_intf_mode_notify_func[DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT];
#endif
#ifdef _PRE_WLAN_FEATURE_SMPS
    p_alg_cfg_smps_notify_func              pa_cfg_smps_notify_func[DMAC_ALG_CFG_SMPS_NOTIFY_BUTT];
#endif
    p_alg_cfg_user_spatial_stream_notify_func  pa_cfg_user_spatial_stream_notify_func[DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT];

    p_alg_rx_mgmt_notify_func           p_rx_mgmt_func[DMAC_ALG_RX_MGMT_NOTIFY_BUTT];
    p_alg_txbf_rx_cntl_notify_func          p_txbf_rx_cntl_func;
    p_alg_config_func                       pa_alg_config_notify_func[DMAC_ALG_CONFIG_ID_BUTT];
    p_alg_enqueue_tid_notify_func           pa_alg_enqueue_tid_notify_func[DMAC_ALG_ENQUEUE_TID_BUTT];
    p_alg_vap_up_notify_func                pa_alg_vap_up_notify_func[DMAC_ALG_VAP_UP_BUTT];
    p_alg_vap_down_notify_func              pa_alg_vap_down_notify_func[DMAC_ALG_VAP_DOWN_BUTT];

#ifdef _PRE_WLAN_FEATURE_DBAC
    p_alg_probe_req_rx_notify_func          pa_alg_probe_req_rx_notify_func[DMAC_ALG_PROBE_REQ_RX_BUTT];
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    p_alg_flowctl_backp_notify_func         p_alg_flowctl_backp_func;
#endif

    oal_dlist_head_stru                     st_timer_list;   /* 10ms定时列表 */

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    p_alg_rx_event_notify_func              p_rx_event_notify_func;
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    p_alg_start_stat_rssi_func              p_start_stat_rssi_func;
    p_alg_get_rssi_func                     p_get_rssi_func;
    p_alg_stop_stat_rssi_func               p_stop_stat_rssi_func;
    p_alg_start_stat_rate_func              p_start_stat_rate_func;
    p_alg_get_rate_func                     p_get_rate_func;
    p_alg_stop_stat_rate_func               p_stop_stat_rate_func;
    p_alg_start_stat_best_rate_func         p_start_stat_best_rate_func;
    p_alg_get_best_rate_func                p_get_best_rate_func;
    p_alg_stop_stat_best_rate_func          p_stop_stat_best_rate_func;
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    p_alg_edca_stat_event_notify_func       p_edca_stat_event_notify_func;
#endif
    p_alg_dbac_pause_func                   p_dbac_pause_func;
    p_alg_dbac_pause_func                   p_dbac_resume_func;
    p_alg_dbac_is_pause                     p_dbac_is_pause_func;

    p_alg_get_rate_by_table_func            p_get_rate_by_table_func;	
    p_alg_get_tx_best_rate_func             p_get_tx_best_rate_func;
    p_alg_delete_ba_fail_notify_func        p_delete_ba_fail_notify_func;

}dmac_alg_stru;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern dmac_alg_stru  gst_alg_main;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32 gul_dmac_alg_pktno;
#else
extern oal_uint8     guc_dmac_alg_pktno;
#endif
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_alg_tx_complete_notify
 功能描述  : 调用挂接到TX COMPLETE流程上的算法钩子
 输入参数  : pst_mac_vap: VAP结构体;
            pst_user: 用户结构体;
            pst_buf 数据BUF;
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_tx_complete_notify(
                mac_user_stru                  *pst_user,
                oal_netbuf_stru                *pst_buf,
                hal_tx_dscr_ctrl_one_param     *pst_tx_dscr_param)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;
#ifdef _PRE_WLAN_FEATURE_ROAM
    mac_vap_stru   *pst_mac_vap;
    mac_tx_ctl_stru                    *pst_tx_ctl;
#endif //_PRE_WLAN_FEATURE_ROAM

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* 漫游状态下由于强制使用最低速率发送，不需要在发送完成中处理算法钩子 */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_user->uc_vap_id);
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_alg_tx_complete_notify::pst_mac_vap null.}");
        return OAL_SUCC;
    }
    if (OAL_TRUE == pst_tx_ctl->bit_roam_data)
    {
        pst_tx_ctl->bit_roam_data = OAL_FALSE;
        return OAL_SUCC;
    }
#endif //_PRE_WLAN_FEATURE_ROAM

    /* 获取算法所需参数 */
    hal_tx_complete_update_rate(pst_tx_dscr_param);

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_TX_COMPLETE_START; ul_index < DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_tx_complete_notify_func[ul_index])
        {
            pst_alg_stru->pa_tx_complete_notify_func[ul_index](pst_user, pst_buf, pst_tx_dscr_param);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_tx_schedule_notify
 功能描述  : 调用挂接到TX COMPLETE流程上的算法钩子
 输入参数  : pst_device: 设备结构体
 输出参数  : pst_sch_output
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_alg_tx_schedule_notify(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ac_num, mac_tid_schedule_output_stru *pst_sch_output)
{
    mac_device_stru                 *pst_alg_device;

    /* 调调度的钩子 */
    pst_alg_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_device))
    {
        //OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_alg_tx_schedule_notify::pst_alg_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_tx_schedule_func))
    {
        //OAM_WARNING_LOG0(0, OAM_SF_TX, "{dmac_alg_tx_schedule_notify::p_tx_schedule_func null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_tx_schedule_func(pst_alg_device, uc_ac_num, pst_sch_output);
}

/*****************************************************************************
 函 数 名  : dmac_alg_tid_update_notify
 功能描述  : 更新TID队列时回调算法
 输入参数  : pst_tid: TID结构体
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_alg_tid_update_notify(dmac_tid_stru *pst_tid)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_tid_update_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_tid_update_func(pst_tid);
}

/*****************************************************************************
 函 数 名  : dmac_alg_update_bandwidth_mode
 功能描述  : 更新发送描述符中的"freq bandwidth mode"
 输入参数  : pst_mac_user: USER结构体指针
             en_algexist : 是否存在auto rate算法
 输出参数  : pst_txop_alg: 算法结构体指针，其中包含"freq bandwidth mode"，用于
                           发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_alg_update_bandwidth_mode(
                mac_user_stru        *pst_mac_user,
                hal_tx_txop_alg_stru *pst_txop_alg,
                oal_bool_enum_uint8   en_algexist)
{
    oal_uint8   uc_channel_bandwidth = 0;

    if (WLAN_BW_CAP_20M == pst_mac_user->en_avail_bandwidth)
    {
        uc_channel_bandwidth = 0;        /* BW20 */
    }
    else if (WLAN_BW_CAP_40M == pst_mac_user->en_avail_bandwidth)
    {
        uc_channel_bandwidth = BIT2;     /* BW40 */
    }
    else if (WLAN_BW_CAP_80M == pst_mac_user->en_avail_bandwidth)
    {
        uc_channel_bandwidth = BIT3;     /* BW80 */
    }

    if (OAL_TRUE == en_algexist)
    {
        pst_txop_alg->st_rate.uc_channel_bandwidth = OAL_MIN(pst_txop_alg->st_rate.uc_channel_bandwidth, uc_channel_bandwidth);
    }
    else
    {
        pst_txop_alg->st_rate.uc_channel_bandwidth = uc_channel_bandwidth;
    }
}
#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : dmac_tx_check_mimo_rate
 功能描述  : 更新发送描述符中的"phy tx mode 1"
 输入参数  : pst_dmac_vap : VAP结构体指针
             pst_dmac_user: USER结构体指针
 输出参数  : pst_txop_alg : 算法结构体指针，其中包含"phy tx mode 1"，用于
                            发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_tx_check_mimo_rate(oal_uint8 uc_smps, oal_uint8 uc_protocol_mode, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_data_idx)
{
    oal_bool_enum_uint8  en_mimo_rate = OAL_FALSE;
    oal_uint8            uc_daterate  = WLAN_HT_MCS_BUTT;
    if (WLAN_HT_PHY_PROTOCOL_MODE == uc_protocol_mode)
    {
        uc_daterate = pst_txop_alg->ast_per_rate[uc_data_idx].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs;
        if ((WLAN_HT_MCS8 <= uc_daterate) && (WLAN_HT_MCS_BUTT > uc_daterate))
        {
            en_mimo_rate = OAL_TRUE;
        }
    }

    else if (WLAN_VHT_PHY_PROTOCOL_MODE == uc_protocol_mode)
    {
        uc_daterate = pst_txop_alg->ast_per_rate[uc_data_idx].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode;
        if (WLAN_SINGLE_NSS < uc_daterate)
        {
            en_mimo_rate = OAL_TRUE;
        }
    }
    else
    {
       /* 暂时不做处理 */
    }

    return en_mimo_rate;
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_smps_txop_alg
 功能描述  : 更新发送描述符中的"phy tx mode 1"
 输入参数  : pst_dmac_vap : VAP结构体指针
             pst_dmac_user: USER结构体指针
 输出参数  : pst_txop_alg : 算法结构体指针，其中包含"phy tx mode 1"，用于
                            发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_smps_txop_alg(dmac_vap_stru *pst_dmac_vap, mac_user_stru *pst_mac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    oal_uint8                    uc_smps             =  0;
    oal_uint8                    uc_protocol_mode    =  0;
    oal_uint8                    uc_mimo_rate        =  0;
    oal_uint8                    uc_index            =  0;
    mac_device_stru             *pst_device          =  OAL_PTR_NULL;
    hal_cfg_rts_tx_param_stru    st_hal_rts_tx_param;

    uc_smps = dmac_user_get_smps_mode(&pst_dmac_vap->st_vap_base_info, pst_mac_user);

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO <= uc_smps)
    {
        return;
    }

    pst_device= mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
       //OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{dmac_tx_update_smps_txop_alg::pst_device null.}");

        return;
    }

    if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return;
    }

    for (uc_index = 0; uc_index < HAL_TX_RATE_MAX_NUM; uc_index++)
    {
        uc_protocol_mode = pst_txop_alg->ast_per_rate[uc_index].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
        uc_mimo_rate     = dmac_tx_check_mimo_rate(uc_smps, uc_protocol_mode, pst_txop_alg, uc_index);

        if (OAL_FALSE == uc_mimo_rate)
        {
            continue;
        }

        if (WLAN_MIB_MIMO_POWER_SAVE_DYNAMIC == uc_smps)
        {
            pst_txop_alg->ast_per_rate[uc_index].rate_bit_stru.bit_rts_cts_enable = OAL_TRUE;

            /* 设置RTS速率对应的频带 */
            st_hal_rts_tx_param.en_band = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

            /* RTS[0~2]设为24Mbps */
            st_hal_rts_tx_param.auc_protocol_mode[0]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            st_hal_rts_tx_param.auc_rate[0]             = WLAN_LEGACY_OFDM_24M_BPS;
            st_hal_rts_tx_param.auc_protocol_mode[1]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            st_hal_rts_tx_param.auc_rate[1]             = WLAN_LEGACY_OFDM_24M_BPS;
            st_hal_rts_tx_param.auc_protocol_mode[2]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            st_hal_rts_tx_param.auc_rate[2]             = WLAN_LEGACY_OFDM_24M_BPS;

            /* 2G的RTS[3]设为1Mbps */
            if (WLAN_BAND_2G == st_hal_rts_tx_param.en_band)
            {
                st_hal_rts_tx_param.auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
                st_hal_rts_tx_param.auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
            }
            /* 5G的RTS[3]设为24Mbps */
            else
            {
            #ifdef _PRE_WLAN_FEATURE_5G
                st_hal_rts_tx_param.auc_protocol_mode[3]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                st_hal_rts_tx_param.auc_rate[3]             = WLAN_LEGACY_OFDM_24M_BPS;
            #endif /* _PRE_WLAN_FEATURE_5G */
            }

            hal_set_rts_rate_params(pst_device->pst_device_stru, &st_hal_rts_tx_param);
        }
        else if (WLAN_MIB_MIMO_POWER_SAVE_STATIC == uc_smps)
        {
            pst_txop_alg->ast_per_rate[uc_index].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = WLAN_HT_MCS0;
        }
    }
}
#endif
/*****************************************************************************
 函 数 名  : alg_data_tx_notify
 功能描述  : 调用挂接到TX流程上的算法钩子
 输入参数  : pst_mac_user: 用户结构体; pst_cb CB字段;
 输出参数  : pst_txop_param 出参
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_tx_notify(
                dmac_vap_stru           *pst_dmac_vap,
                mac_user_stru           *pst_user,
                mac_tx_ctl_stru         *pst_cb,
                hal_tx_txop_alg_stru    *pst_txop_alg)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;
    //oal_uint32      ul_ret;

    pst_alg_stru = &gst_alg_main;

    if (0 == pst_dmac_vap->bit_bw_cmd)
    {
        dmac_alg_update_bandwidth_mode(pst_user, pst_txop_alg, OAL_FALSE);
    }

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
#ifdef _PRE_WLAN_FEATURE_SMPS
        /* 如果算法不存在就直接调用该函数，如果算法存在继续执行算法函数 */
        dmac_tx_update_smps_txop_alg(pst_dmac_vap, pst_user, pst_txop_alg);
#endif
        return OAL_SUCC;
    }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    MAC_GET_CB_ALG_PKTNO(pst_cb) = (++gul_dmac_alg_pktno);
#else
    MAC_GET_CB_ALG_PKTNO(pst_cb) = (++guc_dmac_alg_pktno);
#endif

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_TX_START; ul_index < DMAC_ALG_TX_NOTIFY_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_tx_notify_func[ul_index])
        {
            pst_alg_stru->pa_tx_notify_func[ul_index](pst_user, pst_cb, pst_txop_alg);
            #if 0
            ul_ret = pst_alg_stru->pa_tx_notify_func[ul_index](pst_user, pst_cb, pst_txop_alg);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_alg_tx_notify::pa_tx_notify_func failed[%d].}", ul_ret);
            }
            #endif
        }
    }

    if ((OAL_PTR_NULL != pst_alg_stru->pa_tx_notify_func[DMAC_ALG_TX_AUTORATE])
    #ifdef _PRE_WLAN_CHIP_TEST_ALG
        || (OAL_PTR_NULL != pst_alg_stru->pa_tx_notify_func[DMAC_ALG_TEST_TX_AUTORATE])
    #endif
       )
    {
        if (0 == pst_dmac_vap->bit_bw_cmd)
        {
            dmac_alg_update_bandwidth_mode(pst_user, pst_txop_alg, OAL_TRUE);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_rx_notify
 功能描述  : 调用挂接到RX流程上的算法钩子
 输入参数  : pst_mac_vap: VAP结构体; pst_mac_user: 用户结构体; pst_buf 数据BUF;
 输出参数  : ul_output 出参
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_alg_rx_notify(
                mac_vap_stru                       *pst_mac_vap,
                mac_user_stru                      *pst_mac_user,
                oal_netbuf_stru                    *pst_buf,
                hal_rx_statistic_stru              *pst_rx_stats)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;
    //oal_uint32      ul_ret;

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (OAL_UNLIKELY(0 == pst_alg_stru->ul_alg_bitmap))
    {
        return;
    }

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_RX_START; ul_index < DMAC_ALG_RX_NOTIFY_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_rx_notify_func[ul_index])
        {
            pst_alg_stru->pa_rx_notify_func[ul_index](pst_mac_vap, pst_mac_user, pst_buf, pst_rx_stats);
            #if 0
            ul_ret = pst_alg_stru->pa_rx_notify_func[ul_index](pst_mac_vap, pst_mac_user, pst_buf, pst_rx_stats);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_alg_rx_notify::pa_rx_notify_func failed[%d].}", ul_ret);
            }
            #endif
        }
    }

    return;
}

#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 函 数 名  : dmac_alg_enqueue_tid_notify
 功能描述  : 调用挂接到报文入TID队列流程上的算法钩子
 输入参数  : pst_mac_vap
             pst_tid
             uc_mpdu_num
 输出参数  : ul_output 出参
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_enqueue_tid_notify(
                                        mac_vap_stru   *pst_mac_vap,
                                        dmac_tid_stru  *pst_tid,
                                        oal_uint8 uc_mpdu_num)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;
    //oal_uint32      ul_ret;

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
		//OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_alg_enqueue_tid_notify::ul_alg_bitmap=0.}");
        return OAL_SUCC;
    }

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_ENQUEUE_TID_START; ul_index < DMAC_ALG_ENQUEUE_TID_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_alg_enqueue_tid_notify_func[ul_index])

        {
            pst_alg_stru->pa_alg_enqueue_tid_notify_func[ul_index](pst_mac_vap, pst_tid, uc_mpdu_num);
            #if 0
            ul_ret = pst_alg_stru->pa_alg_enqueue_tid_notify_func[ul_index](pst_mac_vap, pst_tid, uc_mpdu_num);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_alg_enqueue_tid_notify::pa_alg_enqueue_tid_notify_func failed[%d].}", ul_ret);
            }
            #endif
        }
    }

    return OAL_SUCC;

}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_vap_up_notify
 功能描述  : vap up时调用算法钩子
 输入参数  : pst_mac_vap
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_vap_up_notify(mac_vap_stru *pst_mac_vap)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
		//OAM_WARNING_LOG0(0, OAM_SF_RX, "{ul_alg_bitmap=0.}");
        return OAL_SUCC;
    }

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_VAP_UP_DBAC; ul_index < DMAC_ALG_VAP_UP_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_alg_vap_up_notify_func[ul_index])
        {
            pst_alg_stru->pa_alg_vap_up_notify_func[ul_index](pst_mac_vap);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_vap_down_notify
 功能描述  : vap down时调用算法钩子
 输入参数  : pst_mac_vap
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_vap_down_notify(mac_vap_stru *pst_mac_vap)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
		//OAM_WARNING_LOG0(0, OAM_SF_RX, "{ul_alg_bitmap=0.}");
        return OAL_SUCC;
    }

    /* 调用钩子函数 */
    for (ul_index = DMAC_ALG_VAP_DOWN_DBAC; ul_index < DMAC_ALG_VAP_DOWN_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_alg_vap_down_notify_func[ul_index])
        {
            pst_alg_stru->pa_alg_vap_down_notify_func[ul_index](pst_mac_vap);
        }
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 函 数 名  : dmac_alg_probe_req_rx_notify
 功能描述  : 收到probe req时的钩子函数
 输入参数  : pst_dmac_vap、pst_probe_req
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_alg_probe_req_rx_notify(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_net_buf)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_index;

    pst_alg_stru = &gst_alg_main;

    /* 检查是否有算法注册 */
    if (0 == pst_alg_stru->ul_alg_bitmap)
    {
		//OAM_WARNING_LOG0(0, OAM_SF_RX, "{ul_alg_bitmap=0.}");
        return OAL_SUCC;
    }

    /* 调用钩子函数 */
    for (ul_index = 0; ul_index < DMAC_ALG_PROBE_REQ_RX_BUTT; ul_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_alg_probe_req_rx_notify_func[ul_index])
        {
            pst_alg_stru->pa_alg_probe_req_rx_notify_func[ul_index](pst_dmac_vap, pst_net_buf);
        }
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG

/*****************************************************************************
 函 数 名  : dmac_alg_rx_event_notify
 功能描述  : 调用接收报文事件通知的钩子
 输入参数  : uc_vap_id
             pst_netbuf
             pst_cb_ctrl
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月19日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_alg_rx_event_notify(oal_uint8 uc_vap_id,
                                    oal_netbuf_stru *pst_netbuf, dmac_rx_ctl_stru *pst_cb_ctrl)
{
    oal_uint32      ul_ret;

    if (OAL_PTR_NULL != gst_alg_main.p_rx_event_notify_func)
    {
        ul_ret = gst_alg_main.p_rx_event_notify_func(uc_vap_id, pst_netbuf, pst_cb_ctrl);
        if (OAL_SUCC != ul_ret)
        {
            //OAM_WARNING_LOG1(0, OAM_SF_RX, "{dmac_alg_rx_event_notify::p_rx_event_notify_func failed[%d].}", ul_ret);
            return;
        }
    }
}
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

/*****************************************************************************
 函 数 名  : dmac_alg_flowctl_backp_notify
 功能描述  : flowctrl的反压机制
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_alg_flowctl_backp_notify(mac_vap_stru *pst_vap,
                                                                oal_uint16 us_total_mpdu_num,
                                                                oal_uint16 aus_ac_mpdu_num[])
{
    oal_uint32  ul_ret = OAL_SUCC;

    if (OAL_PTR_NULL == gst_alg_main.p_alg_flowctl_backp_func)
    {
        return OAL_SUCC;
    }

    if (OAL_PTR_NULL == pst_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 调用流控制反压钩子函数 */
    ul_ret = gst_alg_main.p_alg_flowctl_backp_func(pst_vap, us_total_mpdu_num, aus_ac_mpdu_num);
    if (OAL_SUCC != ul_ret)
    {
        //OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_alg_flowctl_backp_notify::p_alg_flowctl_backp_func failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32 dmac_alg_downlink_flowctl_notify(mac_vap_stru *pst_vap,
                                                                mac_user_stru *pst_user,
                                                                oal_netbuf_stru *pst_buf);
extern oal_uint32 dmac_alg_cfg_channel_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 dmac_alg_cfg_start_connect_notify(mac_vap_stru *pst_vap, oal_int8 c_rssi);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint32  dmac_alg_cfg_btcoex_state_notify(mac_device_stru *pst_device, dmac_alg_bt_state_type_uint8 en_type);
extern oal_uint32  dmac_alg_register_cfg_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8  en_notify_sub_type, p_alg_cfg_btcoex_state_notify_func  p_func);
extern oal_uint32  dmac_alg_unregister_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8 en_notify_sub_type);

#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
extern oal_uint32 dmac_alg_cfg_bandwidth_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type);
extern oal_uint32 dmac_alg_add_assoc_user_notify(dmac_vap_stru *pst_vap, dmac_user_stru *pst_user);
extern oal_uint32 dmac_alg_del_assoc_user_notify(dmac_vap_stru * pst_vap, dmac_user_stru * pst_user);
extern oal_uint32  dmac_alg_rx_mgmt_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_user, oal_netbuf_stru *pst_buf);
extern oal_uint32  dmac_alg_txbf_rx_cntl_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_user, oal_netbuf_stru *pst_buf);
extern oal_uint32 dmac_alg_create_vap_notify(dmac_vap_stru *pst_vap);
extern oal_uint32 dmac_alg_delete_vap_notify(dmac_vap_stru *pst_vap);
extern oal_uint32  dmac_alg_init(mac_device_stru  *pst_device);
extern oal_uint32  dmac_alg_exit(mac_device_stru  *pst_device);
extern oal_uint32  dmac_alg_get_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info);
extern oal_uint32  dmac_alg_cfg_user_spatial_stream_notify(mac_user_stru *pst_mac_user);

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32 dmac_edca_opt_stat_event_process(frw_event_mem_stru *pst_event_mem);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_alg.h */
