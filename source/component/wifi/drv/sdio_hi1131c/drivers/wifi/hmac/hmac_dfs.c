/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_dfs.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月16日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DFS

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_fsm.h"
#include "hmac_chan_mgmt.h"
#include "dmac_scan.h"
#include "hmac_dfs.h"
#include "hmac_scan.h"
#include "hmac_resource.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DFS_C


/*****************************************************************************
  2 结构体定义
*****************************************************************************/


/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define HMAC_DFS_IS_CHAN_WEATHER_RADAR(_us_freq) \
    ((5600 <= (_us_freq)) && ((_us_freq) <= 5650))


/*****************************************************************************
  4 全局变量定义
*****************************************************************************/


/*****************************************************************************
  5 内部静态函数声明
*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_nol_addchan(mac_device_stru *pst_mac_device, oal_uint8 uc_chan_idx);
OAL_STATIC oal_uint32  hmac_dfs_nol_delchan(mac_device_stru *pst_mac_device, mac_dfs_nol_node_stru *pst_nol_node);
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
OAL_STATIC oal_uint32  hmac_scan_switch_channel_back(mac_vap_stru *pst_mac_vap);
OAL_STATIC oal_uint32  hmac_scan_switch_channel_off(mac_vap_stru *pst_mac_vap);
#endif
OAL_STATIC oal_uint32  hmac_dfs_off_chan_cac_off_ch_dwell_timeout(oal_void *p_arg);
OAL_STATIC oal_uint32  hmac_dfs_off_chan_cac_opern_ch_dwell_timeout(oal_void *p_arg);


/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_dfs_init
 功能描述  : DFS特性初始化函数
 输入参数  : pst_mac_device: MAC DEVICE指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_dfs_init(mac_device_stru *pst_mac_device)
{
    mac_dfs_info_stru   *pst_dfs_info;

    /* 初始化Non-Occupancy List链表 */
    oal_dlist_init_head(&(pst_mac_device->st_dfs.st_dfs_nol));

    /* 软件雷达检测默认不使能 */
    mac_dfs_set_dfs_enable(pst_mac_device, OAL_FALSE);

    /* CAC检测默认不使能 */
    mac_dfs_set_cac_enable(pst_mac_device, OAL_FALSE);

    /* OFFCHAN-CAC检测默认不使能 */
    mac_dfs_set_offchan_cac_enable(pst_mac_device, OAL_FALSE);

    /* debug默认关闭 */
    mac_dfs_set_debug_level(pst_mac_device, 0);

    /* 设置CAC, Off-Channel CAC, etc... 超时时间 */
    pst_dfs_info = &(pst_mac_device->st_dfs.st_dfs_info);

    pst_dfs_info->ul_dfs_cac_outof_5600_to_5650_time_ms      = HMAC_DFS_CAC_OUTOF_5600_TO_5650_MHZ_TIME_MS;
    pst_dfs_info->ul_dfs_cac_in_5600_to_5650_time_ms         = HMAC_DFS_CAC_IN_5600_TO_5650_MHZ_TIME_MS;
    pst_dfs_info->ul_off_chan_cac_outof_5600_to_5650_time_ms = HMAC_DFS_OFF_CH_CAC_OUTOF_5600_TO_5650_MHZ_TIME_MS;
    pst_dfs_info->ul_off_chan_cac_in_5600_to_5650_time_ms    = HMAC_DFS_OFF_CH_CAC_IN_5600_TO_5650_MHZ_TIME_MS;
    pst_dfs_info->us_dfs_off_chan_cac_opern_chan_dwell_time  = HMAC_DFS_OFF_CHAN_CAC_PERIOD_TIME_MS;
    pst_dfs_info->us_dfs_off_chan_cac_off_chan_dwell_time    = HMAC_DFS_OFF_CHAN_CAC_DWELL_TIME_MS;

    /* 默认当前信道为home channel */
    pst_dfs_info->uc_offchan_flag = 0;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_channel_list_init
 功能描述  : DFS信道列表初始化
 输入参数  : pst_mac_device: MAC DEVICE指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_dfs_channel_list_init(mac_device_stru *pst_mac_device)
{
    mac_chan_status_enum_uint8    en_ch_status;
    oal_uint8                     uc_idx;
#ifdef _PRE_WLAN_FEATURE_5G
    oal_uint32                    ul_ret;
#endif /* _PRE_WLAN_FEATURE_5G */

#if 0
    if (WLAN_BAND_5G != pst_mac_device->en_max_band)
    {
        OAL_IO_PRINT("[DFS]hmac_dfs_channel_list_init::band is not 5G.\n.");
        return;
    }
#endif
    for (uc_idx = 0; uc_idx < MAC_MAX_SUPP_CHANNEL; uc_idx++)
    {
    #ifdef _PRE_WLAN_FEATURE_5G
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, uc_idx);
        if (OAL_SUCC == ul_ret)
        {
            if (OAL_TRUE == mac_is_ch_in_radar_band(MAC_RC_START_FREQ_5, uc_idx))
            {
                /* DFS信道 */
                en_ch_status = MAC_CHAN_DFS_REQUIRED;
            }
            else
            {
                en_ch_status = MAC_CHAN_AVAILABLE_ALWAYS;
            }
        }
        else
    #endif /* _PRE_WLAN_FEATURE_5G */
        {
            /* 管制域不支持 */
            en_ch_status = MAC_CHAN_NOT_SUPPORT;
        }

        pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status = en_ch_status;
    }
}

/*****************************************************************************
 函 数 名  : hmac_dfs_find_available_chan
 功能描述  : 从管制域支持的信道中，选择最低可用信道
 输入参数  : pst_mac_device: MAC DEVICE结构体指针
             pst_mac_vap   : MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 信道号
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint8  hmac_dfs_find_lowest_available_channel(mac_device_stru *pst_mac_device)
{
    oal_uint8     uc_channel_num = 36;
    oal_uint8     uc_chan_idx;
    oal_uint8     uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_device->en_max_band);
    oal_uint32    ul_ret;

    for (uc_chan_idx = 0; uc_chan_idx < uc_num_supp_chan; uc_chan_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(pst_mac_device->en_max_band, uc_chan_idx);
        if (OAL_SUCC != ul_ret)
        {
            continue;
        }

        if ((MAC_CHAN_NOT_SUPPORT        != pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status) &&
            (MAC_CHAN_BLOCK_DUE_TO_RADAR != pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status))
        {
            mac_get_channel_num_from_idx(pst_mac_device->en_max_band, uc_chan_idx, &uc_channel_num);

            return uc_channel_num;
        }
    }

    /* should not be here */
    return uc_channel_num;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_recalculate_channel
 功能描述  : 是否需要重新计算(更改)可用信道
 输入参数  : pst_mac_device: MAC DEVICE结构体指针
 输出参数  : puc_freq      : 信道号
 返 回 值  : OAL_TRUE : 需要
             OAL_FALSE: 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_recalculate_channel(
                    mac_device_stru                     *pst_mac_device,
                    oal_uint8                           *puc_freq,
                    wlan_channel_bandwidth_enum_uint8   *pen_bandwidth)
{
    hmac_channel_list_stru    st_chan_info;
    oal_uint8                 uc_chan_idx = 0;
    oal_uint8                 uc_loop;
    oal_uint32                ul_ret;
    oal_bool_enum_uint8       en_recalc = OAL_FALSE;

    ul_ret = mac_get_channel_idx_from_num(pst_mac_device->en_max_band, *puc_freq, &uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_mac_device->uc_device_id, OAM_SF_DFS, "{hmac_dfs_recalculate_channel::mac_get_channel_idx_from_num fail.max_band:%d  freq:%x}",pst_mac_device->en_max_band,puc_freq);
        return ul_ret;
    }

    hmac_chan_get_ext_chan_info(uc_chan_idx, *pen_bandwidth, &st_chan_info);

    for (uc_loop = 0; uc_loop < st_chan_info.ul_channels; uc_loop++)
    {
        uc_chan_idx = st_chan_info.ast_channels[uc_loop].uc_idx;

        if ((MAC_CHAN_NOT_SUPPORT        == pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status) ||
            (MAC_CHAN_BLOCK_DUE_TO_RADAR == pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status))
        {
            en_recalc = OAL_TRUE;
            break;
        }
    }

    if (OAL_FALSE == en_recalc)
    {
        return OAL_FALSE;
    }


    /* 如果由于雷达干扰导致当前信道不可用，则需要从管制域支持的信道中，选择最低可用信道，带宽20MHz */
    *puc_freq = hmac_dfs_find_lowest_available_channel(pst_mac_device);

    *pen_bandwidth = WLAN_BAND_WIDTH_20M;

    return OAL_TRUE;
}


/*****************************************************************************
 函 数 名  : hmac_dfs_radar_detect_event
 功能描述  : HMAC 雷达中断处理入口函数
 输入参数  : pst_event_mem: 事件内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_radar_detect_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru         *pst_event;
    hmac_vap_stru          *pst_hmac_vap;
    hmac_misc_input_stru    st_misc_input;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{hmac_dfs_radar_detect_event::pst_event_mem is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{hmac_dfs_radar_detect_event::pst_hmac_vap is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    st_misc_input.en_type = HMAC_MISC_RADAR;

    hmac_fsm_call_func_ap(pst_hmac_vap, HMAC_FSM_INPUT_MISC, &st_misc_input);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_update_channel_list
 功能描述  : 更新信道信息
 输入参数  : pst_mac_device   : MAC DEVICE指针
             uc_chan_idx      : 信道索引
             en_radar_detected: 是否检测到雷达
 输出参数  : pst_mac_device   : MAC DEVICE指针
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_update_available_channel_list(
                mac_device_stru       *pst_mac_device,
                oal_uint8              uc_chan_idx,
                oal_bool_enum_uint8    en_radar_detected)
{
    oal_uint32    ul_ret;

    ul_ret = mac_is_channel_idx_valid(pst_mac_device->en_max_band, uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "{hmac_dfs_update_available_channel_list::chan_idx(%d) invalid!}", uc_chan_idx);
        OAL_IO_PRINT("[DFS]hmac_dfs_update_available_channel_list::ch is not available.\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (MAC_CHAN_AVAILABLE_ALWAYS == pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status)
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "{hmac_dfs_update_available_channel_list::Radar detected in Non-Radar Channel(%d)!}", uc_chan_idx);
        OAL_IO_PRINT("[DFS]hmac_dfs_update_available_channel_list::ch status is always available.\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (OAL_TRUE == en_radar_detected)
    {
        pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status = MAC_CHAN_BLOCK_DUE_TO_RADAR;
        OAL_IO_PRINT("[DFS]ch status is changed to due to radar.\n");
    }
    else
    {
        pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status = MAC_CHAN_AVAILABLE_TO_OPERATE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_cac_timeout_fn
 功能描述  : Channel Availability Check(CAC) 超时函数
 输入参数  : p_arg: HMAC VAP的指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_cac_timeout_fn(oal_void *p_arg)
{
    mac_device_stru          *pst_mac_device;
    hmac_device_stru         *pst_hmac_device;
    hmac_vap_stru            *pst_hmac_vap;
    hmac_channel_list_stru    st_chan_info;
    oal_uint8                 uc_idx;
    mac_dfs_info_stru        *pst_dfs_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_timeout_fn::p_arg is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;

    OAL_IO_PRINT("[DFS]hmac_dfs_cac_timeout_fn, CAC expired, channel number:%d.\n",
                 pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number);

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device || OAL_PTR_NULL == pst_hmac_device->pst_device_base_info)
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_timeout_fn::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = pst_hmac_device->pst_device_base_info;

    pst_dfs_info = &pst_mac_device->st_dfs.st_dfs_info;

    pst_dfs_info->uc_timer_cnt++;

    if(pst_dfs_info->uc_timer_cnt != pst_dfs_info->uc_timer_end_cnt)
    {
        /* 启动 CAC 定时器 */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_cac_timer,
                               hmac_dfs_cac_timeout_fn,
                               HMAC_DFS_ONE_MIN_IN_MS,
                               pst_hmac_vap,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_hmac_vap->st_vap_base_info.ul_core_id);
        return OAL_SUCC;
    }

    hmac_chan_get_ext_chan_info(pst_hmac_vap->st_vap_base_info.st_channel.uc_idx,
                    pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth,
                    &st_chan_info);

    /* 将当前信道设置为工作信道 */
    for (uc_idx = 0; uc_idx < st_chan_info.ul_channels; uc_idx++)
    {
        hmac_dfs_update_available_channel_list(pst_mac_device, st_chan_info.ast_channels[uc_idx].uc_idx, OAL_FALSE);
    }

    if (MAC_VAP_STATE_AP_WAIT_START == pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
        pst_hmac_device->en_init_scan      = OAL_FALSE;
        pst_hmac_device->en_in_init_scan   = OAL_FALSE;
#endif
        /* 在该信道启动 BSS */
		hmac_start_all_bss_of_device(pst_hmac_device);

    } /*  TBD pause状态需要待定 */
    else if ((MAC_VAP_STATE_PAUSE == pst_hmac_vap->st_vap_base_info.en_vap_state) ||
             (MAC_VAP_STATE_UP    == pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        //hmac_vap_resume_tx_by_chl(pst_hmac_vap);

        hmac_chan_restart_network_after_switch(&(pst_hmac_vap->st_vap_base_info));
    }

    /* off-channel cac start */
    if(OAL_TRUE == mac_dfs_get_offchan_cac_enable(pst_mac_device))
    {
        hmac_dfs_off_chan_cac_start(pst_mac_device, pst_hmac_vap);
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_dfs_start_bss
 功能描述  : setchannel时判断是否需要cac检测，不需要则启动vap
 输入参数  : pst_hmac_vap: HMAC VAP的指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_start_bss(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru          *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_start_bss::pst_hmac_vap is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_timeout_fn::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 在该信道启动 BSS */
    return hmac_start_bss_in_available_channel(pst_hmac_vap);

}


/*****************************************************************************
 函 数 名  : hmac_chan_get_cac_time
 功能描述  : 获取Channel Availability Check(CAC)检测时间
 输入参数  : pst_mac_device: MAC DEVICE指针
             pst_mac_vap   : MAC VAP指针
 输出参数  : 无
 返 回 值  : CAC检测时间
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chan_get_cac_time(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_uint32 *ul_scan_time)
{
    mac_regdomain_info_stru   *pst_rd_info;
    hmac_channel_list_stru     st_chan_info;
    oal_uint8                  uc_idx = 0;
    oal_uint32                 ul_ret;

    mac_get_regdomain_info(&pst_rd_info);

    if (MAC_DFS_DOMAIN_ETSI == pst_rd_info->en_dfs_domain)
    {
        ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num, &uc_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG2(0, OAM_SF_DFS, "{hmac_chan_get_cac_time::mac_get_channel_idx_from_num fail. en_band:%d, offchan_num:%u}",pst_mac_vap->st_channel.en_band,pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num);
            return ul_ret;
        }
        hmac_chan_get_ext_chan_info(uc_idx,
                        pst_mac_vap->st_channel.en_bandwidth, &st_chan_info);

        for (uc_idx = 0; uc_idx < st_chan_info.ul_channels; uc_idx++)
        {
            if (HMAC_DFS_IS_CHAN_WEATHER_RADAR(st_chan_info.ast_channels[uc_idx].us_freq))
            {
                *ul_scan_time = pst_mac_device->st_dfs.st_dfs_info.ul_dfs_cac_in_5600_to_5650_time_ms;
                return OAL_SUCC;
            }
        }
    }
    *ul_scan_time = pst_mac_device->st_dfs.st_dfs_info.ul_dfs_cac_outof_5600_to_5650_time_ms;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_chan_get_off_chan_cac_time
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chan_get_off_chan_cac_time(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_uint32 *ul_scan_time)
{
    hmac_channel_list_stru     st_chan_info;
    oal_uint8                  uc_idx = 0;
    oal_uint32                 ul_ret;

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_DFS, "{hmac_chan_get_off_chan_cac_time::mac_get_channel_idx_from_num fail. en_band:%u, offchan_num:%u}",pst_mac_vap->st_channel.en_band,pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num);
        return ul_ret;
    }

    hmac_chan_get_ext_chan_info(uc_idx,
                    pst_mac_vap->st_channel.en_bandwidth, &st_chan_info);

    for (uc_idx = 0; uc_idx < st_chan_info.ul_channels; uc_idx++)
    {
        if (HMAC_DFS_IS_CHAN_WEATHER_RADAR(st_chan_info.ast_channels[uc_idx].us_freq))
        {
            *ul_scan_time = pst_mac_device->st_dfs.st_dfs_info.ul_off_chan_cac_in_5600_to_5650_time_ms;
            return OAL_SUCC;
        }
    }
    *ul_scan_time = pst_mac_device->st_dfs.st_dfs_info.ul_off_chan_cac_outof_5600_to_5650_time_ms;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_dfs_cac_stop
 功能描述  : Channel Availability Check(CAC)检测结束函数
 输入参数  : pst_mac_device: MAC DEVICE指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_dfs_cac_stop(mac_device_stru *pst_mac_device)
{
    if (OAL_TRUE == pst_mac_device->st_dfs.st_dfs_cac_timer.en_is_enabled)
    {
        /* 关闭CAC检测时长定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_dfs.st_dfs_cac_timer));

        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_stop::[DFS]CAC timer stopped.}");
    }
}

oal_void  hmac_dfs_off_cac_stop(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap)
{
    if (OAL_TRUE == pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer.en_is_enabled)
    {
        /* 关闭OFF CAC检测时长定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer));

        OAM_INFO_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_stop::[DFS]CAC big timer stopped.}");
    }
    if (OAL_TRUE == pst_mac_device->st_dfs.st_dfs_chan_dwell_timer.en_is_enabled)
    {
        /* 关闭OFFCAC信道驻留定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_dfs.st_dfs_chan_dwell_timer));

        OAM_INFO_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_stop::[DFS]CAC timer stopped.}");
    }
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    /* 若VAP在Off-Channel信道上则切回工作信道 */
    if (pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag & BIT0)
    {
        OAM_INFO_LOG0(0, OAM_SF_DFS, "{hmac_dfs_cac_stop::[DFS]switch back to home channel.}");
        hmac_scan_switch_channel_back(pst_mac_vap);
    }
#endif
    pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag = 0;
}


/*****************************************************************************
 函 数 名  : hmac_dfs_cac_start
 功能描述  : Channel Availability Check(CAC)检测开始函数
 输入参数  : pst_mac_device: MAC DEVICE指针
             pst_hmac_vap  : HMAC VAP指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_dfs_cac_start(mac_device_stru *pst_mac_device, hmac_vap_stru *pst_hmac_vap)
{
    oal_uint32   ul_scan_time = 0;
    oal_uint32   ul_ret;

    /* 如果已经启动 CAC 定时器，则直接返回 */
    if (OAL_TRUE == pst_mac_device->st_dfs.st_dfs_cac_timer.en_is_enabled)
    {
        return;
    }

    /* 设置 CAC 检测时间 */
    ul_ret = hmac_chan_get_cac_time(pst_mac_device, &(pst_hmac_vap->st_vap_base_info),&ul_scan_time);
    if (OAL_SUCC != ul_ret)
    {
        return;
    }
    OAL_IO_PRINT("start cac time=%d ms ch=%d\n", ul_scan_time, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number);

    if(HMAC_DFS_ONE_MIN_IN_MS > ul_scan_time)
    {
        pst_mac_device->st_dfs.st_dfs_info.uc_timer_cnt     = 0;
        pst_mac_device->st_dfs.st_dfs_info.uc_timer_end_cnt = 1;

        /* 启动 CAC 定时器 */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_cac_timer,
                               hmac_dfs_cac_timeout_fn,
                               ul_scan_time,
                               pst_hmac_vap,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_hmac_vap->st_vap_base_info.ul_core_id);
        return;
    }
    pst_mac_device->st_dfs.st_dfs_info.uc_timer_cnt     = 0;
    pst_mac_device->st_dfs.st_dfs_info.uc_timer_end_cnt = (oal_uint8)(ul_scan_time / HMAC_DFS_ONE_MIN_IN_MS);

    /* 启动 CAC 定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_cac_timer,
                           hmac_dfs_cac_timeout_fn,
                           HMAC_DFS_ONE_MIN_IN_MS,
                           pst_hmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_hmac_vap->st_vap_base_info.ul_core_id);

   OAM_WARNING_LOG2(0, OAM_SF_DFS, "{[DFS]hmac_dfs_cac_start, CAC start, channel number:%d, timer cnt:%d.}",
                 pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number, pst_mac_device->st_dfs.st_dfs_info.uc_timer_end_cnt);
}

/*****************************************************************************
 函 数 名  : hmac_dfs_radar_wait
 功能描述  :
 输入参数  : pst_mac_device: MAC DEVICE指针
             uc_chan_idx   : 信道索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_dfs_radar_wait(mac_device_stru *pst_mac_device, oal_uint8 uc_chan_idx)
{
    mac_vap_stru   *pst_mac_vap;
    oal_uint8       uc_vap_idx;

    /* 如果雷达使能没有开启 或者 当前信道不属于DFS信道，直接返回 */
    if ((OAL_FALSE == mac_dfs_get_dfs_enable(pst_mac_device)) ||
        (OAL_FALSE == mac_is_ch_in_radar_band(pst_mac_device->en_max_band, uc_chan_idx)))
    {
        return;
    }

    /* 遍历device下的所有vap，当所有vap都down后，将当前信道状态置为MAC_CHAN_DFS_REQUIRED */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFS, "{hmac_dfs_radar_wait::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);

            continue;
        }

        if (MAC_VAP_STATE_INIT != pst_mac_vap->en_vap_state)
        {
            return;
        }
    }

    if (MAC_CHAN_AVAILABLE_TO_OPERATE == pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status)
    {
        pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_status = MAC_CHAN_DFS_REQUIRED;
    }
}

/*****************************************************************************
 函 数 名  : hmac_dfs_nol_timeout_fn
 功能描述  : NOL超时函数，超时后将某一信道从NOL列表中剔除
 输入参数  : p_arg: NOL Node节点指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_nol_timeout_fn(oal_void *p_arg)
{
    mac_device_stru         *pst_mac_device;
    mac_dfs_nol_node_stru   *pst_nol_node;
    oal_uint8                uc_chan_num = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_nol_timeout_fn::p_arg is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_nol_node = (mac_dfs_nol_node_stru *)p_arg;

    pst_mac_device = mac_res_get_dev(pst_nol_node->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_nol_timeout_fn::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_get_channel_num_from_idx(pst_mac_device->en_max_band, pst_nol_node->uc_chan_idx, &uc_chan_num);

    OAM_INFO_LOG1(0, OAM_SF_DFS, "{[DFS]hmac_dfs_nol_timeout_fn, Non-Occupancy Period expired, remove channel %d from NOL.}", uc_chan_num);

    return hmac_dfs_nol_delchan(pst_mac_device, pst_nol_node);
}

/*****************************************************************************
 函 数 名  : hmac_dfs_nol_addchan
 功能描述  : 将指定信道加入NOL列表
 输入参数  : pst_mac_device: MAC DEVICE指针
             uc_chan_idx   : 信道索引
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_nol_addchan(mac_device_stru *pst_mac_device, oal_uint8 uc_chan_idx)
{
    mac_dfs_nol_node_stru   *pst_nol_node;
    oal_uint8                uc_chan_num = 0;

    pst_nol_node = (mac_dfs_nol_node_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_dfs_nol_node_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_nol_node))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{hmac_dfs_nol_addchan::memory not enough.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_nol_node->uc_chan_idx  = uc_chan_idx;
    pst_nol_node->uc_device_id = pst_mac_device->uc_device_id;

    oal_dlist_add_tail(&(pst_nol_node->st_entry), &(pst_mac_device->st_dfs.st_dfs_nol));

    mac_get_channel_num_from_idx(pst_mac_device->en_max_band, uc_chan_idx, &uc_chan_num);
    OAM_WARNING_LOG1(0, OAM_SF_DFS, "{[DFS]hmac_dfs_nol_addchan, add channel %d to NOL.}", uc_chan_num);

    /* 启动Non-Occupancy Peroid定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_nol_node->st_dfs_nol_timer,
                           hmac_dfs_nol_timeout_fn,
                           HMAC_DFS_NON_OCCUPANCY_PERIOD_TIME_MS,
                           pst_nol_node,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_mac_device->ul_core_id);

    /* 更新可用信道列列表 */
    return hmac_dfs_update_available_channel_list(pst_mac_device, uc_chan_idx, OAL_TRUE);
}

/*****************************************************************************
 函 数 名  : hmac_dfs_nol_delchan
 功能描述  : 将指定信道从NOL列表中剔除
 输入参数  : pst_mac_device: MAC DEVICE指针
             pst_nol_node  : NOL Node节点指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_nol_delchan(mac_device_stru *pst_mac_device, mac_dfs_nol_node_stru *pst_nol_node)
{
    /* 更新可用信道列列表 */
    pst_mac_device->st_ap_channel_list[pst_nol_node->uc_chan_idx].en_ch_status = MAC_CHAN_DFS_REQUIRED;

    oal_dlist_delete_entry(&pst_nol_node->st_entry);

    OAL_MEM_FREE(pst_nol_node, OAL_FALSE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_channel_mark_radar
 功能描述  : 将主、次信道标记为检测到雷达，并将主、次信道加入Non-Occupancy List(NOL)列表
 输入参数  : pst_mac_device: MAC DEVICE指针
             pst_mac_vap   : MAC VAP指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_dfs_channel_mark_radar(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap)
{
    hmac_channel_list_stru    st_chan_info;
    oal_uint8                 uc_idx = 0;
    oal_uint32                ul_ret;

    if(pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag == (BIT0|BIT1))
    {
        ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num, &uc_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_DFS, "{hmac_dfs_channel_mark_radar:: mac_get_channel_idx_from_num fail. en_band:%u, offchan_num:%u}",pst_mac_vap->st_channel.en_band,pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num);
            return;
        }
        hmac_chan_get_ext_chan_info(uc_idx,
                    pst_mac_vap->st_channel.en_bandwidth, &st_chan_info);
    }
    else
    {
        hmac_chan_get_ext_chan_info(pst_mac_vap->st_channel.uc_idx,
                    pst_mac_vap->st_channel.en_bandwidth, &st_chan_info);
    }

    for (uc_idx = 0; uc_idx < st_chan_info.ul_channels; uc_idx++)
    {
        hmac_dfs_nol_addchan(pst_mac_device, st_chan_info.ast_channels[uc_idx].uc_idx);
    }
}

/*****************************************************************************
 函 数 名  : hmac_dfs_select_random_channel
 功能描述  : 挑选一条信道(对)
 输入参数  : pst_mac_vap      : MAC VAP结构体指针
 输出参数  : puc_new_channel  : 挑选出来的主信道号
             pen_new_bandwidth: 挑选出来的带宽模式
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_dfs_select_random_channel(
                mac_vap_stru                        *pst_mac_vap,
                oal_uint8                           *puc_new_channel,
                wlan_channel_bandwidth_enum_uint8   *pen_new_bandwidth)
{
    mac_device_stru   *pst_mac_device;
    oal_uint8          uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_vap->st_channel.en_band);
    oal_uint32         ul_chan_bitmap = 0;
    oal_uint32         ul_window = 0;
    oal_uint8          uc_step = 0;
    oal_uint8          auc_available_chan_idx[MAC_CHANNEL_FREQ_5_BUTT];
    oal_uint8          uc_available_chan_cnt = 0;
    oal_uint8          uc_idx;
    oal_uint8          uc_cur_idx;
    oal_uint8          uc_sub;
    oal_uint8          uc_cur_sub;

#define HMAC_40MHZ_BITMAP_MASK     0xF7BFFFF
#define HMAC_80MHZ_BITMAP_MASK     0xFFFFFF

    OAL_MEMZERO(auc_available_chan_idx, OAL_SIZEOF(auc_available_chan_idx));

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_dfs_select_random_channel::pst_mac_device null, device_id = %d.}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取可用信道位图 */
    for (uc_idx = 0; uc_idx < uc_num_supp_chan; uc_idx++)
    {
        if (OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device))
        {
            if ((MAC_CHAN_NOT_SUPPORT        != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status) &&
                (MAC_CHAN_BLOCK_DUE_TO_RADAR != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status))
            {
                ul_chan_bitmap |= (0x1 << uc_idx);
            }
        }
        else
        {
            if (MAC_CHAN_NOT_SUPPORT != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status)
            {
                ul_chan_bitmap |= (0x1 << uc_idx);
            }
        }
    }

    /* 20MHz */
    if (WLAN_BAND_WIDTH_20M == pst_mac_vap->st_channel.en_bandwidth)
    {
        ul_window = 0x1;   /* 1b */
        uc_step = 1;

        for (uc_idx = 0; uc_idx < uc_num_supp_chan; uc_idx += uc_step)
        {
            if ((ul_window << uc_idx) == (ul_chan_bitmap & (ul_window << uc_idx)))
            {
                auc_available_chan_idx[uc_available_chan_cnt++] = uc_idx;
            }
        }
    }
    /* 40MHz */
    else if (pst_mac_vap->st_channel.en_bandwidth < WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        ul_window = 0x3;   /* 11b */
        uc_step = 2;
        ul_chan_bitmap &= HMAC_40MHZ_BITMAP_MASK;

        /* channel 36 ~ 136 */
        for (uc_idx = 0; uc_idx < MAC_CHANNEL140; uc_idx += uc_step)                /* skip channel 140 */
        {
            if ((ul_window << uc_idx) == (ul_chan_bitmap & (ul_window << uc_idx)))
            {
                auc_available_chan_idx[uc_available_chan_cnt++] = uc_idx;
            }
        }

        /* channel 149 ~ 161 */
        for (uc_idx = MAC_CHANNEL149; uc_idx < MAC_CHANNEL165; uc_idx += uc_step)   /* skip channel 165 */
        {
            if ((ul_window << uc_idx) == (ul_chan_bitmap & (ul_window << uc_idx)))
            {
                auc_available_chan_idx[uc_available_chan_cnt++] = uc_idx;
            }
        }

        /* channel 184 ~ 196 */
        for (uc_idx = MAC_CHANNEL184; uc_idx < uc_num_supp_chan; uc_idx += uc_step)
        {
            if ((ul_window << uc_idx) == (ul_chan_bitmap & (ul_window << uc_idx)))
            {
                auc_available_chan_idx[uc_available_chan_cnt++] = uc_idx;
            }
        }
    }
    /* 80MHz */
    else
    {
        ul_window = 0xF    /* 1111b */;
        uc_step = 4;
        ul_chan_bitmap &= HMAC_80MHZ_BITMAP_MASK;

        /* channel 36 ~ 161 */
        for (uc_idx = 0; uc_idx < MAC_CHANNEL165; uc_idx += uc_step)                /* JP channel 184, 188, 192, 196, */
        {                                                                           /* 4条信道组不了80MHz, 参考802.11 ac Annex E */
            if ((ul_window << uc_idx) == (ul_chan_bitmap & (ul_window << uc_idx)))
            {
                auc_available_chan_idx[uc_available_chan_cnt++] = uc_idx;
            }
        }
    }

    /* 如果找不到可用信道，从管制域支持的信道中，选择最低可用信道，带宽20MHz */
    if (0 == uc_available_chan_cnt)
    {
        *puc_new_channel = hmac_dfs_find_lowest_available_channel(pst_mac_device);
        *pen_new_bandwidth = WLAN_BAND_WIDTH_20M;

        return OAL_SUCC;
    }

    /* ,避免选择到邻近信道*/
    uc_sub = 0;
    for (ul_window = 0; ul_window < uc_available_chan_cnt; ul_window++)
    {
        uc_cur_idx = auc_available_chan_idx[ul_window];
        switch (pst_mac_vap->st_channel.en_bandwidth)
        {
            case WLAN_BAND_WIDTH_40MINUS:
            case WLAN_BAND_WIDTH_80MINUSPLUS:
               uc_cur_idx += 1;
               break;

            case WLAN_BAND_WIDTH_80PLUSMINUS:
                uc_cur_idx += 2;
                break;

            case WLAN_BAND_WIDTH_80MINUSMINUS:
                uc_cur_idx += 3;
                break;

            default:
                break;
        }

        mac_get_channel_num_from_idx(pst_mac_vap->st_channel.en_band, uc_cur_idx, puc_new_channel);
        uc_cur_sub = OAL_ABSOLUTE_SUB(pst_mac_vap->st_channel.uc_chan_number, *puc_new_channel);

        if(uc_cur_sub > uc_sub)
        {
            uc_sub = uc_cur_sub;
            uc_idx = uc_cur_idx;
        }
    }

    mac_get_channel_num_from_idx(pst_mac_vap->st_channel.en_band, uc_idx, puc_new_channel);

    *pen_new_bandwidth = pst_mac_vap->st_channel.en_bandwidth;

    OAL_IO_PRINT("[DFS]select_channel::bandwidth = %d, channelnum = %d.\n", *pen_new_bandwidth, *puc_new_channel);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_ap_wait_start_radar_handler
 功能描述  : AP在WAIT START状态下的雷达检测处理
 输入参数  : pst_hmac_vap: HMAC VAP指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_ap_wait_start_radar_handler(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru                     *pst_mac_device;
    mac_vap_stru                        *pst_mac_vap;
    oal_uint8                            uc_new_channel   = 0;
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth = WLAN_BAND_WIDTH_BUTT;
    oal_uint32                           ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{hmac_dfs_ap_wait_start_radar_handler::pst_hmac_vap is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_DFS,
                       "{hmac_dfs_ap_wait_start_radar_handler::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 关闭 CAC 检测 */
    hmac_dfs_cac_stop(pst_mac_device);

    /* 标记主、次信道检测到雷达 */
    hmac_dfs_channel_mark_radar(pst_mac_device, pst_mac_vap);

    /* 重新选择一条信道 */
    ul_ret = hmac_dfs_select_random_channel(pst_mac_vap, &uc_new_channel, &en_new_bandwidth);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    ul_ret = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, uc_new_channel);
    if ((OAL_SUCC != ul_ret) || (en_new_bandwidth >= WLAN_BAND_WIDTH_BUTT))
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_dfs_ap_wait_start_radar_handler::Could not start network using the selected channel[%d] or bandwidth[%d].}",
                         uc_new_channel, en_new_bandwidth);
        return ul_ret;
    }

    /*  TBD 只需要设置硬件寄存器一次，然后同步一下软件vap的配置即可 */
    hmac_chan_multi_select_channel_mac(pst_mac_vap, uc_new_channel, en_new_bandwidth);

    //hmac_chan_select_channel_mac(&(pst_hmac_vap->st_vap_base_info), uc_new_channel, en_new_bandwidth);

    /* 判断是否需要进行 */
    if (OAL_TRUE == hmac_dfs_need_for_cac(pst_mac_device, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number))
    {
        hmac_dfs_cac_start(pst_mac_device, pst_hmac_vap);

        return OAL_SUCC;
    }

    /* 否则，直接启动BSS */
    return hmac_start_bss_in_available_channel(pst_hmac_vap);
}

oal_uint32 hmac_dfs_switch_channel_for_radar(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap)
{
    oal_uint8                            uc_new_channel   = 0;
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth = WLAN_BAND_WIDTH_BUTT;
    oal_uint32                           ul_ret;

    /* 关闭 CAC 检测 */
    hmac_dfs_cac_stop(pst_mac_device);

    /* 标记主、次信道检测到雷达 */
    hmac_dfs_channel_mark_radar(pst_mac_device, pst_mac_vap);

    /* 如果AP已经准备进行信道切换，则直接返回，不做任何处理 */
    if (WLAN_CH_SWITCH_STATUS_1 == pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        return OAL_SUCC;
    }

    ul_ret = hmac_dfs_select_random_channel(pst_mac_vap, &uc_new_channel, &en_new_bandwidth);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt = WLAN_CHAN_SWITCH_DETECT_RADAR_CNT;
    hmac_chan_multi_switch_to_new_channel(pst_mac_vap, uc_new_channel, en_new_bandwidth);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_off_chan_cac_timeout_fn
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_off_chan_cac_timeout_fn(oal_void *p_arg)
{
    mac_device_stru     *pst_mac_device;
    hmac_vap_stru       *pst_hmac_vap;
    mac_dfs_info_stru   *pst_dfs_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_timeout_fn::p_arg is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_timeout_fn::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dfs_info = &pst_mac_device->st_dfs.st_dfs_info;

    pst_dfs_info->uc_timer_cnt++;

    if(pst_dfs_info->uc_timer_cnt != pst_dfs_info->uc_timer_end_cnt)
    {
        /* 启动OFF CHAN CAC 定时器 */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer,
                               hmac_dfs_off_chan_cac_timeout_fn,
                               HMAC_DFS_ONE_MIN_IN_MS,
                               pst_hmac_vap,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_hmac_vap->st_vap_base_info.ul_core_id);
        return OAL_SUCC;
    }


    OAL_IO_PRINT("[DFS]hmac_dfs_off_chan_cac_timeout_fn::off-channel cac end.\n");

    /* 关闭Off-channel CAC 信道驻留定时器 */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_dfs.st_dfs_chan_dwell_timer));
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    /* 若VAP在Off-Channel信道上则切回工作信道 */
    if (pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag & BIT0)
    {
        hmac_scan_switch_channel_back(&(pst_hmac_vap->st_vap_base_info));
    }
#endif
    pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag = 0;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_dfs_ap_up_radar_handler
 功能描述  : AP在UP状态下的雷达检测处理
 输入参数  : pst_hmac_vap: HMAC VAP指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_ap_up_radar_handler(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru                     *pst_mac_device;
    mac_vap_stru                        *pst_mac_vap;
    oal_uint8                            uc_offchan_flag;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "{hmac_dfs_ap_wait_start_radar_handler::pst_hmac_vap is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_DFS,
                       "{hmac_dfs_ap_wait_start_radar_handler::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_offchan_flag = pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag;
    /*off-chan cac 期间*/
    if(uc_offchan_flag & BIT1)
    {
        /* home channel检测到radar */
        if(!(uc_offchan_flag & BIT0))
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{[DFS]radar detected in channel %d.}", pst_mac_vap->st_channel.uc_chan_number);

            /* 关闭Off-channel CAC 定时器 */
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer));

            hmac_dfs_off_chan_cac_timeout_fn(pst_hmac_vap);

            return hmac_dfs_switch_channel_for_radar(pst_mac_device, pst_mac_vap);
        }
        /* off channel检测到radar */
        else
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{[DFS]radar detected in channel %d.}", pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num);
            /* 标记主、次信道检测到雷达 */
            hmac_dfs_channel_mark_radar(pst_mac_device, pst_mac_vap);
            return OAL_SUCC;
        }
    }
    /* in service monitor期间 */
    else
    {
        return hmac_dfs_switch_channel_for_radar(pst_mac_device, pst_mac_vap);
    }

}
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
/*****************************************************************************
 函 数 名  : hmac_scan_switch_channel_off
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_switch_channel_off(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_ret;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_switch_channel_off::pst_event_mem null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_scan_switch_channel_off::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_scan_switch_channel_back
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_switch_channel_back(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_ret;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_switch_channel_back::pst_event_mem null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_scan_switch_channel_back::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_dfs_off_chan_cac_opern_ch_dwell_timeout
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_off_chan_cac_opern_ch_dwell_timeout(oal_void *p_arg)
{
    mac_device_stru   *pst_mac_device;
    hmac_vap_stru     *pst_hmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_opern_ch_dwell_timeout::p_arg is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_opern_ch_dwell_timeout::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if 0
    pst_mac_device->st_scan_params.en_scan_mode = WLAN_SCAN_MODE_BACKGROUND_AP;
    pst_mac_device->st_scan_params.us_scan_time = pst_mac_device->st_dfs.st_dfs_info.us_dfs_off_chan_cac_off_chan_dwell_time;
    pst_mac_device->uc_scan_chan_idx = 0;
    /* pst_mac_device->st_scan_params.ast_channel_list[pst_mac_device->uc_scan_chan_idx] = st_channel;  TBD */
#endif

    /* 当前信道为offchan 标志 */
    pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag = (BIT0|BIT1);
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    /* 切换到Off-channel CAC检测信道 */
    hmac_scan_switch_channel_off(&pst_hmac_vap->st_vap_base_info);
#endif
    /* 将当前off-channel cac信道信息赋值给VAP */
    /* pst_hmac_vap->st_vap_base_info.st_channel = st_channel;  TBD*/

    /* 启动Off-channel信道上检测时长定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_chan_dwell_timer,
                          hmac_dfs_off_chan_cac_off_ch_dwell_timeout,
                          pst_mac_device->st_dfs.st_dfs_info.us_dfs_off_chan_cac_off_chan_dwell_time,
                          pst_hmac_vap,
                          OAL_FALSE,
                          OAM_MODULE_ID_HMAC,
                          pst_hmac_vap->st_vap_base_info.ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_off_chan_cac_off_ch_dwell_timeout
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_dfs_off_chan_cac_off_ch_dwell_timeout(oal_void *p_arg)
{
    mac_device_stru   *pst_mac_device;
    hmac_vap_stru     *pst_hmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_off_ch_dwell_timeout::p_arg is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_off_ch_dwell_timeout::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 当前信道为homechan标志 */
    pst_mac_device->st_dfs.st_dfs_info.uc_offchan_flag = BIT1;
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    /* 切换回工作信道 */
    hmac_scan_switch_channel_back(&(pst_hmac_vap->st_vap_base_info));
#endif
    /* 启动在工作信道上的工作时长定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_chan_dwell_timer,
                           hmac_dfs_off_chan_cac_opern_ch_dwell_timeout,
                           pst_mac_device->st_dfs.st_dfs_info.us_dfs_off_chan_cac_opern_chan_dwell_time,
                           pst_hmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_hmac_vap->st_vap_base_info.ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dfs_off_chan_cac_start
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : 
    修改内容   : 新生成函数

******************************************************************************/
oal_void  hmac_dfs_off_chan_cac_start(mac_device_stru *pst_mac_device, hmac_vap_stru *pst_hmac_vap)
{
    oal_uint32 ul_scan_time;
    oal_uint32 ul_ret;

    /* 如果已经启动OFF-CHAN-CAC 定时器, 直接返回 */
    if(OAL_TRUE == pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer.en_is_enabled)
    {
        OAM_INFO_LOG0(0, OAM_SF_DFS, "{hmac_dfs_off_chan_cac_start::off-chan-cac is already started by another vap.}");
        return;
    }

    /* 设置 Off-Channel CAC 检测时间 */
    ul_ret  = hmac_chan_get_off_chan_cac_time(pst_mac_device, &pst_hmac_vap->st_vap_base_info, &ul_scan_time);

    if(OAL_SUCC != ul_ret)
    {
        return;
    }

    pst_mac_device->st_dfs.st_dfs_info.uc_timer_cnt     = 0;
    pst_mac_device->st_dfs.st_dfs_info.uc_timer_end_cnt = (oal_uint8)(ul_scan_time / HMAC_DFS_ONE_MIN_IN_MS);

    /* 启动 CAC 定时器 */
    FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_off_chan_cac_timer,
                           hmac_dfs_off_chan_cac_timeout_fn,
                           HMAC_DFS_ONE_MIN_IN_MS,
                           pst_hmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_hmac_vap->st_vap_base_info.ul_core_id);

    OAM_INFO_LOG2(0, OAM_SF_DFS, "{[DFS]hmac_dfs_off_chan_cac_start, OFF-CHAN-CAC start, channel number:%d, scan time = %d.}",
                 pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num, ul_scan_time);


    hmac_dfs_off_chan_cac_opern_ch_dwell_timeout(pst_hmac_vap);
}
/*****************************************************************************
 函 数 名  : hmac_dfs_try_cac
 功能描述  : 尝试进行CAC
 输入参数  : mac_device_stru *pst_mac_device
             mac_vap_stru *pst_mac_vap
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_dfs_try_cac(hmac_device_stru *pst_hmac_device, mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru    *pst_hmac_vap;
#ifdef _PRE_SUPPORT_ACS
    mac_channel_stru *pst_channel;
#endif
    mac_device_stru  *pst_mac_device;
    oal_uint8         uc_cac_ch;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device || OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_dfs_try_cac::pst_device_base_info null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    
    pst_mac_device = pst_hmac_device->pst_device_base_info;
    
    

    /* 如果已经启动 CAC 定时器，则直接返回 */
    if (OAL_TRUE == pst_mac_device->st_dfs.st_dfs_cac_timer.en_is_enabled)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ACS, "cac started\n");
        return OAL_TRUE;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{hmac_dfs_try_cac::mac_res_get_hmac_vap fail.vap_id[%u]}",pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_SUPPORT_ACS
    pst_channel  = pst_hmac_device->ast_best_channel;

    uc_cac_ch = (MAC_ACS_SW_INIT == mac_get_acs_switch(pst_mac_device)
             || MAC_ACS_SW_BOTH == mac_get_acs_switch(pst_mac_device))
             && pst_channel[pst_hmac_vap->st_vap_base_info.st_channel.en_band].uc_chan_number
             ? pst_channel[pst_hmac_vap->st_vap_base_info.st_channel.en_band].uc_chan_number
             : pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number;
#else
    uc_cac_ch = pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number;
#endif

	OAM_WARNING_LOG1(0, OAM_SF_ACS, "cac ch=%d \n", uc_cac_ch);
    // if (IS_LEGACY_VAP(&(pst_hmac_vap->st_vap_base_info))&&(pst_mac_device->st_dfs.st_dfs_info.en_dfs_switch & BIT1))
    if (IS_LEGACY_VAP(&(pst_hmac_vap->st_vap_base_info)))
    {
        /* 如果需要进行 CAC 检测，这里启动定时器，直到CAC结束后才启动BSS(VAP UP) */
        if (OAL_TRUE == hmac_dfs_need_for_cac(pst_mac_device, uc_cac_ch))
        {
#ifdef _PRE_SUPPORT_ACS
            /* 若ACS使能，那么可能选取了一个不同于VAP配置信道的信道，强制同步 */
            if ((MAC_ACS_SW_INIT == mac_get_acs_switch(pst_mac_device)
             || MAC_ACS_SW_BOTH == mac_get_acs_switch(pst_mac_device))
             && 0 != pst_channel[pst_hmac_vap->st_vap_base_info.st_channel.en_band].uc_chan_number)
            {
                // FIXME:DBAC下需要更新DBAC的ONE PKT配置
                hmac_chan_sync(&pst_hmac_vap->st_vap_base_info,
                        pst_channel[pst_hmac_vap->st_vap_base_info.st_channel.en_band].uc_chan_number,
                        pst_channel[pst_hmac_vap->st_vap_base_info.st_channel.en_band].en_bandwidth,
                        OAL_TRUE);
            }
#endif
            /* 若ACS未使能或者未选出有效信道，则直接在已配置的信道上进行CAC */
            hmac_dfs_cac_start(pst_mac_device, pst_hmac_vap);
            pst_mac_device->st_dfs.st_dfs_info.en_dfs_switch &= ~BIT1;

            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : hmac_dfs_init_scan_hook
 功能描述  : 初始信道检查模块钩子函数，进行CAC检查
 输入参数  : hmac_scan_runtime_record_stru   *pst_scan_record
             mac_device_stru                 *pst_dev
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dfs_init_scan_hook(hmac_scan_record_stru   *pst_scan_record,
                                    hmac_device_stru        *pst_hmac_device)
{
    oal_uint8       uc_vap_id;
    mac_vap_stru   *pst_vap;

    OAM_WARNING_LOG0(0, OAM_SF_ACS, "dfs init scan hook run\n");

    for (uc_vap_id=0; uc_vap_id < WLAN_MAX_VAP_NUM; uc_vap_id++)
    {
        pst_vap = mac_res_get_mac_vap(uc_vap_id);
        if (pst_vap && WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode)
        {
            /* 只要当前device上已经开始进行CAC过程，那么同device的其他VAP不再进行 */
            /* CAC完成之后会统一设置信道并启动VAP */
            /* DBAC场景下依然可以满足 */
            if (OAL_TRUE == hmac_dfs_try_cac(pst_hmac_device, pst_vap))
            {
                OAM_WARNING_LOG0(0, OAM_SF_ACS, "cac started\n");
                return OAL_SUCC;
            }
        }
    }

    OAM_WARNING_LOG0(0, OAM_SF_ACS, "cac not need\n");
    return OAL_FAIL;
}

#ifdef _PRE_WLAN_CHIP_TEST

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_void test_dfs(oal_uint8 uc_vap_id)
{
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;
    mac_vap_stru        *pst_mac_vap;


    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "{test_dfs::mac_res_get_mac_vap fail. vap_id:%u.}",uc_vap_id);
        return;
    }

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{test_dfs::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru*)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST,
                       0,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
}

oal_void test_csa(oal_uint8 uc_vap_id, oal_uint8 uc_chan_id, oal_uint8 uc_sw_cnt)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    mac_vap_stru             *pst_mac_vap;
    oal_netbuf_stru          *pst_netbuf;
    oal_uint8                *puc_data;
    dmac_rx_ctl_stru         *pst_rx_ctrl;
    hcc_event_stru           *pst_hcc_event_payload;
    mac_ieee80211_frame_stru *pst_frame_hdr;
    oal_uint32                ul_ret = OAL_SUCC;


    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "{test_csa::mac_res_get_mac_vap fail vap_id:%u.}",uc_vap_id);
        return;
    }

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{test_csa::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru*)pst_event_mem->puc_data;
    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX,
                       0,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{test_csa::pst_netbuf null.}");
        return;
    }

    pst_rx_ctrl      = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr = (oal_uint32 *)oal_netbuf_data(pst_netbuf);
    pst_rx_ctrl->st_rx_info.uc_mac_header_len      = 24;
    pst_rx_ctrl->st_rx_info.us_frame_len           = 31;

    puc_data = oal_netbuf_data(pst_netbuf);
    puc_data[0]  = 0xd0;
    puc_data[24] = 0;
    puc_data[25] = 4;
    puc_data[26] = 37;
    puc_data[27] = 3;
    puc_data[28] = 1;
    puc_data[29] = uc_chan_id;
    puc_data[30] = uc_sw_cnt;
    oal_netbuf_put(pst_netbuf, 31);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)oal_netbuf_data(pst_netbuf);


    pst_hcc_event_payload = (hcc_event_stru *)pst_event->auc_event_data;
    pst_hcc_event_payload->en_nest_type     = FRW_EVENT_TYPE_WLAN_CRX;
    pst_hcc_event_payload->uc_nest_sub_type = DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX;
    pst_hcc_event_payload->pst_netbuf       = pst_netbuf;

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        /* 将netbuf归还内存池 */
        oal_netbuf_free(pst_netbuf);
    }

    FRW_EVENT_FREE(pst_event_mem);
}
#endif
#endif

#endif   /* end of _PRE_WLAN_FEATURE_DFS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

