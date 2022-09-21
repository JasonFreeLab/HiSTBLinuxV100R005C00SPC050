/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_scan.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年8月26日
  最近修改   :
  功能描述   : 与内核接口相关的scan功能函数
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "oal_cfg80211.h"
#include "wlan_spec.h"
#include "wal_linux_event.h"
#include "wal_linux_scan.h"
#include "wal_linux_cfg80211.h"
#include "wal_main.h"
#include "wal_linux_rx_rsp.h"
#include "hmac_vap.h"
#include "hmac_device.h"
#include "mac_device.h"
#include "hmac_resource.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
#include "plat_pm_wlan.h"
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <net/cfg80211.h>
#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#ifndef u64
 #define u64    UINT64
#endif
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)

#endif

#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    /* UT模式下调用frw_event_process_all_event */
    extern oal_void  frw_event_process_all_event(oal_uint ui_data);
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_SCAN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : wal_inform_bss_frame
 功能描述  : 逐个上报ssid消息给内核
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  wal_inform_bss_frame(wal_scanned_bss_info_stru *pst_scanned_bss_info, oal_void *p_data)
{
    oal_cfg80211_bss_stru        *pst_cfg80211_bss;
    oal_wiphy_stru               *pst_wiphy;
    oal_ieee80211_channel_stru   *pst_ieee80211_channel;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 39))
    struct timespec ts;
#else
    struct timeval tv;
#endif
#endif

    if ((OAL_PTR_NULL == pst_scanned_bss_info) || (OAL_PTR_NULL == p_data))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{wal_inform_bss_frame::input param pointer is null, pst_scanned_bss_info[%p], p_data[%p]!}",
                       pst_scanned_bss_info, p_data);
        return;
    }

    pst_wiphy = (oal_wiphy_stru *)p_data;

    pst_ieee80211_channel = oal_ieee80211_get_channel(pst_wiphy, (oal_int32)pst_scanned_bss_info->s_freq);

    if(NULL == pst_ieee80211_channel)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_inform_bss_frame::get channel failed, wrong s_freq[%d]}",
                       (oal_int32)pst_scanned_bss_info->s_freq);
        return;
    }

    pst_scanned_bss_info->l_signal = pst_scanned_bss_info->l_signal * 100;

/*  2015/11/23 begin*/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/* 由于驱动缓存扫描结果，导致cts认证2次扫描的bss的timestamp时间一致(后一次没有扫描到) */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 39))
    get_monotonic_boottime(&ts);
    pst_scanned_bss_info->pst_mgmt->u.probe_resp.timestamp = ((u64)ts.tv_sec*1000000)
        + ts.tv_nsec / 1000;
#else
    do_gettimeofday(&tv);
    pst_scanned_bss_info->pst_mgmt->u.probe_resp.timestamp = ((u64)tv.tv_sec*1000000)
        + tv.tv_usec;
#endif
#endif
/*  2015/11/23 end*/

    /* 逐个上报内核bss 信息 */
    pst_cfg80211_bss = oal_cfg80211_inform_bss_frame(pst_wiphy, pst_ieee80211_channel, pst_scanned_bss_info->pst_mgmt, pst_scanned_bss_info->ul_mgmt_len, pst_scanned_bss_info->l_signal, GFP_ATOMIC);
    if (pst_cfg80211_bss != NULL)
    {
        oal_cfg80211_put_bss(pst_cfg80211_bss);
    }

    return;
}

/*****************************************************************************
 函 数 名  : wal_inform_all_bss
 功能描述  : 上报所有的bss到内核
 输入参数  : oal_wiphy_stru  *pst_wiphy,
             hmac_bss_mgmt_stru  *pst_bss_mgmt,
             oal_uint8   uc_vap_id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  wal_inform_all_bss(oal_wiphy_stru  *pst_wiphy, hmac_bss_mgmt_stru  *pst_bss_mgmt, oal_uint8   uc_vap_id)
{
    mac_bss_dscr_stru              *pst_bss_dscr;
    hmac_scanned_bss_info          *pst_scanned_bss;
    oal_dlist_head_stru            *pst_entry;
    mac_ieee80211_frame_stru       *pst_frame_hdr;
    wal_scanned_bss_info_stru       st_scanned_bss_info;
    oal_uint32                      ul_ret;
    oal_uint32                      ul_bss_num_not_in_regdomain = 0;
    oal_uint8                       uc_chan_number;
    enum ieee80211_band             en_band;

    /* 获取锁 */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* 遍历扫描到的bss信息 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if (OAL_PTR_NULL == pst_bss_dscr)
        {
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_SCAN,
                "{wal_inform_all_bss::scan result in bss list is invalid. bss_dscr:0x%p}",pst_bss_dscr);
            continue;
        }

        uc_chan_number = pst_bss_dscr->st_channel.uc_chan_number;
        en_band        = (enum ieee80211_band)pst_bss_dscr->st_channel.en_band;

        /* 判断信道是不是在管制域内，如果不在，则不上报内核 */
        ul_ret = mac_is_channel_num_valid(en_band, uc_chan_number);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(uc_vap_id, OAM_SF_SCAN,
                             "{wal_inform_all_bss::curr channel[%d] and band[%d] is not in regdomain.}",
                             uc_chan_number, en_band);
            ul_bss_num_not_in_regdomain++;
            continue;
        }

        /* 初始化 */
        oal_memset(&st_scanned_bss_info, 0, OAL_SIZEOF(wal_scanned_bss_info_stru));

        st_scanned_bss_info.l_signal    = pst_bss_dscr->c_rssi;

        /*填bss所在信道的中心频率*/
        st_scanned_bss_info.s_freq      = (oal_int16)oal_ieee80211_channel_to_frequency(uc_chan_number, en_band);

        /* 填管理帧指针和长度 */
        st_scanned_bss_info.pst_mgmt    = (oal_ieee80211_mgmt_stru *)(pst_bss_dscr->auc_mgmt_buff);
        st_scanned_bss_info.ul_mgmt_len = pst_bss_dscr->ul_mgmt_len;

        /* 获取上报的扫描结果的管理帧的帧头 */
        pst_frame_hdr  = (mac_ieee80211_frame_stru *)pst_bss_dscr->auc_mgmt_buff;

        /* 如果扫描请求接收到的帧类型有beacon类型，统一修改为probe rsp类型上报，
           为了解决上报内核的扫描结果beacon帧不够敏感的问题，此问题，在01出现过 */
    	if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
    	{
    	    /* 修改beacon帧类型为probe rsp */
    		pst_frame_hdr->st_frame_control.bit_sub_type = WLAN_PROBE_RSP;
    	}

        /* 上报扫描结果给内核 */
        wal_inform_bss_frame(&st_scanned_bss_info, pst_wiphy);
    }

    /* 解除锁 */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    OAM_WARNING_LOG2(uc_vap_id, OAM_SF_SCAN,
                     "{wal_inform_all_bss::there are %d bss not in regdomain, so inform kernal bss num is [%d]!}",
                     ul_bss_num_not_in_regdomain, (pst_bss_mgmt->ul_bss_num - ul_bss_num_not_in_regdomain));

    return;
}

/*****************************************************************************
 函 数 名  : free_scan_param_resource
 功能描述  : 释放申请的信道信息资源
 输入参数  : mac_cfg80211_scan_param_stru *
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void free_scan_param_resource(mac_cfg80211_scan_param_stru *pst_scan_param)
{
    if (pst_scan_param->pul_channels_2G != OAL_PTR_NULL)
    {
        oal_free(pst_scan_param->pul_channels_2G);
        pst_scan_param->pul_channels_2G = OAL_PTR_NULL;
    }
    if (pst_scan_param->pul_channels_5G != OAL_PTR_NULL)
    {
        oal_free(pst_scan_param->pul_channels_5G);
        pst_scan_param->pul_channels_5G = OAL_PTR_NULL;
    }
}

/*****************************************************************************
 函 数 名  : wal_set_scan_channel
 功能描述  : 提取内核下发扫描信道相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  wal_set_scan_channel(
                    oal_cfg80211_scan_request_stru    *pst_request,
                    mac_cfg80211_scan_param_stru      *pst_scan_param)

{
    oal_uint32  ul_loop;
    oal_uint32  ul_num_chan_2G;
    oal_uint32  ul_num_chan_5G;

    if (OAL_PTR_NULL == pst_request || OAL_PTR_NULL == pst_scan_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_get_scan_channel_num::set scan channel from scan request failed, pst_request[%p] null ptr or pst_scan_param[%p] null ptr.}",
            pst_request, pst_scan_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_request->n_channels)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_get_scan_channel_num::channels in scan requst is zero.}");
        return OAL_FAIL;
    }

    pst_scan_param->pul_channels_2G = oal_memalloc(pst_request->n_channels * OAL_SIZEOF(oal_uint32));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_scan_param->pul_channels_2G))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{wal_scan_work_func::2.4G channel alloc mem return null ptr!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_scan_param->pul_channels_5G = oal_memalloc(pst_request->n_channels * OAL_SIZEOF(oal_uint32));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_scan_param->pul_channels_5G))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{wal_scan_work_func::5G channel alloc mem return null ptr!}");
        free_scan_param_resource(pst_scan_param);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    ul_num_chan_2G = 0;
    ul_num_chan_5G = 0;

    for (ul_loop = 0; ul_loop < pst_request->n_channels; ul_loop++)
    {
        oal_uint16  us_center_freq;
        oal_uint32  ul_chan;

        us_center_freq = pst_request->channels[ul_loop]->center_freq;

        /* 根据中心频率，计算信道号 */
        ul_chan = (oal_uint32)oal_ieee80211_frequency_to_channel((oal_int32)us_center_freq);

        if (us_center_freq <= WAL_MAX_FREQ_2G)
        {
            pst_scan_param->pul_channels_2G[ul_num_chan_2G++] = ul_chan;
        }
        else
        {
            pst_scan_param->pul_channels_5G[ul_num_chan_5G++] = ul_chan;
        }
    }

    pst_scan_param->uc_num_channels_2G = (oal_uint8)ul_num_chan_2G;
    pst_scan_param->uc_num_channels_5G = (oal_uint8)ul_num_chan_5G;

    if (0 == ul_num_chan_2G)
    {
        oal_free(pst_scan_param->pul_channels_2G);
        pst_scan_param->pul_channels_2G = OAL_PTR_NULL;
    }
    if (0 == ul_num_chan_5G)
    {
        oal_free(pst_scan_param->pul_channels_5G);
        pst_scan_param->pul_channels_5G = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_set_scan_ssid
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void wal_set_scan_ssid(oal_cfg80211_scan_request_stru *pst_request, mac_cfg80211_scan_param_stru *pst_scan_param)
{
    oal_int32   l_loop;
    oal_int32   l_ssid_num;

    if ((OAL_PTR_NULL == pst_request) || (OAL_PTR_NULL == pst_scan_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_set_scan_ssid::scan failed, null ptr, pst_request[%p], pst_scan_param[%p].}",
          pst_request, pst_scan_param);

        return;
    }

    pst_scan_param->en_scan_type = OAL_ACTIVE_SCAN; /* active scan */
    pst_scan_param->l_ssid_num   = 0;

    /* 取内核下发的ssid的个数 */
    l_ssid_num = pst_request->n_ssids;
    if (l_ssid_num > WLAN_SCAN_REQ_MAX_SSID)
    {
        /* 如果用户下发的指定ssid的个数大于驱动支持的最大个数，则取驱动支持的指定ssid的最大个数 */
        l_ssid_num = WLAN_SCAN_REQ_MAX_SSID;
    }

    /* 将用户下发的ssid信息拷贝到对应的结构体中 */
    if ((l_ssid_num > 0) && (OAL_PTR_NULL != pst_request->ssids))
    {
        pst_scan_param->l_ssid_num = l_ssid_num;

        for (l_loop = 0; l_loop < l_ssid_num; l_loop++)
        {
            pst_scan_param->st_ssids[l_loop].uc_ssid_len = pst_request->ssids[l_loop].ssid_len;
            if (pst_scan_param->st_ssids[l_loop].uc_ssid_len > OAL_IEEE80211_MAX_SSID_LEN)
            {
                OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_set_scan_ssid::ssid scan set failed, ssid_len[%d] is exceed, max[%d].}",
                  pst_scan_param->st_ssids[l_loop].uc_ssid_len, OAL_IEEE80211_MAX_SSID_LEN);

                pst_scan_param->st_ssids[l_loop].uc_ssid_len = OAL_IEEE80211_MAX_SSID_LEN;
            }

            oal_memcopy(pst_scan_param->st_ssids[l_loop].auc_ssid, pst_request->ssids[l_loop].ssid,
              pst_scan_param->st_ssids[l_loop].uc_ssid_len);
        }
	}
}

/*****************************************************************************
 函 数 名  : wal_wait_for_scan_complete_time_out
 功能描述  : 等待扫描完成超时处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  wal_wait_for_scan_timeout_fn(void *p_arg)
{
    hmac_vap_stru                  *pst_hmac_vap = (hmac_vap_stru *)p_arg;
    mac_vap_stru                   *pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
    hmac_device_stru               *pst_hmac_device;
    hmac_bss_mgmt_stru             *pst_bss_mgmt;
    hmac_scan_stru                 *pst_scan_mgmt;
    oal_wiphy_stru                 *pst_wiphy;

    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{wal_wait_for_scan_timeout_fn:: 5 seconds scan timeout proc.}");

    /* 根据当前扫描的类型和当前vap的状态，决定切换vap的状态，扫描异常保护中，上报内核扫描状态为扫描完成 */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) &&
        (MAC_VAP_STATE_STA_WAIT_SCAN == pst_mac_vap->en_vap_state))
    {
        /* 改变vap状态到SCAN_COMP */
        mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
    }

    /* 获取hmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_wait_for_scan_complete_time_out::pst_hmac_device[%d] is null.}",
                        pst_mac_vap->uc_device_id);
        return OAL_FAIL;
    }

    pst_scan_mgmt = &(pst_hmac_device->st_scan_mgmt);
    pst_wiphy      = pst_hmac_device->pst_device_base_info->pst_wiphy;

    /* 获取扫描结果的管理结构地址 */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    /* 对于内核下发的扫描request资源加锁 */
    oal_spin_lock(&(pst_scan_mgmt->st_scan_request_spinlock));

    if (OAL_PTR_NULL != pst_scan_mgmt->pst_request)
    {
        /* 上报扫描到的所有的bss */
        wal_inform_all_bss(pst_wiphy, pst_bss_mgmt, pst_mac_vap->uc_vap_id);

        /* 通知 kernel scan 已经结束 */
        oal_cfg80211_scan_done(pst_scan_mgmt->pst_request, 0);

        pst_scan_mgmt->pst_request = OAL_PTR_NULL;
        pst_scan_mgmt->en_complete = OAL_TRUE;

        /* 让编译器优化时保证OAL_WAIT_QUEUE_WAKE_UP在最后执行 */
        OAL_SMP_MB();
        OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&pst_scan_mgmt->st_wait_queue);
    }

    /* 通知完内核，释放资源后解锁 */
    oal_spin_unlock(&(pst_scan_mgmt->st_scan_request_spinlock));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_start_timer_for_scan_timeout
 功能描述  : 启动扫描定时器做扫描超时保护处理
 输入参数  : oal_uint8   uc_vap_id, 发起扫描的vap id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  wal_start_timer_for_scan_timeout(oal_uint8   uc_vap_id)
{
    hmac_vap_stru               *pst_hmac_vap = OAL_PTR_NULL;
    mac_device_stru             *pst_mac_device = OAL_PTR_NULL;
    oal_uint32                   ul_timeout;

    /* 超时时间为5秒 */
    ul_timeout = WAL_MAX_SCAN_TIME_PER_SCAN_REQ;

    /* 获取hmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{wal_start_timer_for_scan_timeout::pst_hmac_vap is null!}");
        return;
    }

    /* 获取mac device */
    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{wal_start_timer_for_scan_timeout::pst_mac_device is null!}");
        return;
    }

    /* 启动扫描保护定时器，在指定时间没有上报扫描结果，主动上报扫描完成 */
    FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_scan_timeout),
                           wal_wait_for_scan_timeout_fn,
                           ul_timeout,
                           pst_hmac_vap,
                           OAL_FALSE,
                           OAM_MODULE_ID_WAL,
                           pst_mac_device->ul_core_id);

    return;
}

/*****************************************************************************
 函 数 名  : wal_scan_work_func
 功能描述  : 解析内核下发扫描命令相关参数，启动扫描
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wal_scan_work_func(hmac_scan_stru                     *pst_scan_mgmt,
                                  oal_net_device_stru                   *pst_netdev,
                                  oal_cfg80211_scan_request_stru        *pst_request)
{
    mac_cfg80211_scan_param_stru st_scan_param;
    oal_uint32                   ul_ret;
    mac_vap_stru                *pst_mac_vap = OAL_NET_DEV_PRIV(pst_netdev);
    oal_uint8                    uc_vap_id = pst_mac_vap->uc_vap_id;

    oal_memset(&st_scan_param, 0, sizeof(mac_cfg80211_scan_param_stru));

    /* 解析内核下发的扫描信道列表 */
    ul_ret = wal_set_scan_channel(pst_request, &st_scan_param);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_scan_work_func::wal_set_scan_channel proc failed, err_code[%d]!}", ul_ret);
        return OAL_FAIL;
    }

    /* 解析内核下发的ssid */
    wal_set_scan_ssid(pst_request, &st_scan_param);

    /* 解析内核下发的ie */
    st_scan_param.puc_ie    = pst_request->ie;
    st_scan_param.ul_ie_len = pst_request->ie_len;

    /* P2P WLAN/P2P 特性情况下，根据扫描的ssid 判断是否为p2p device 发起的扫描，
        ssid 为"DIRECT-"则认为是p2p device 发起的扫描 */
    /* 解析下发扫描的device 是否为p2p device(p2p0) */
    st_scan_param.bit_is_p2p0_scan      = OAL_FALSE;


    if (IS_P2P_SCAN_REQ(pst_request))
    {
        st_scan_param.bit_is_p2p0_scan = OAL_TRUE;
    }

    /* 在事件前防止异步调度完成扫描后,发生同步问题 */
    pst_scan_mgmt->en_complete = OAL_FALSE;

    /* 抛事件，通知驱动启动扫描 */
    ul_ret = wal_cfg80211_start_scan(pst_netdev, &st_scan_param);
    if( OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_scan_work_func::wal_cfg80211_start_scan proc failed, err_code[%d]!}", ul_ret);
        /* 正常情况下，在hmac释放 */
        free_scan_param_resource(&st_scan_param);

        pst_scan_mgmt->en_complete = OAL_TRUE;
        return OAL_FAIL;
    }

    /* win32 UT模式，触发一次事件调度 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    frw_event_process_all_event(0);
#endif

    /* 启动定时器，进行扫描超时处理 */
    wal_start_timer_for_scan_timeout(uc_vap_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_send_scan_abort_msg
 功能描述  : 终止扫描
 输入参数  : oal_net_device_stru   *pst_net_dev
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wal_send_scan_abort_msg(oal_net_device_stru   *pst_net_dev)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_pedding_data = 0;       /* 填充数据，不使用，只是为了复用接口 */
    oal_int32                       l_ret = 0;
    wal_msg_stru                    *pst_rsp_msg = OAL_PTR_NULL;

    /* 拋事件通知device侧终止扫描 */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SCAN_ABORT, OAL_SIZEOF(ul_pedding_data));

    oal_memcopy(st_write_msg.auc_value, (oal_int8 *)&ul_pedding_data, OAL_SIZEOF(ul_pedding_data));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(ul_pedding_data),
                               (oal_uint8 *)&st_write_msg,
                               OAL_TRUE,
                               &pst_rsp_msg);
    if (OAL_SUCC != wal_check_and_release_msg_resp(pst_rsp_msg))
    {
        OAM_WARNING_LOG0(0,OAM_SF_SCAN,"{wal_send_scan_abort_msg::wal_check_and_release_msg_resp fail.}");
    }
    
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_send_scan_abort_msg::fail to stop scan, error[%d]}", l_ret);
    }



    return l_ret;
}

/*************** **************************************************************
 函 数 名  : wal_force_scan_complete
 功能描述  : 通知扫描完成
 输入参数  : oal_net_device_stru   *pst_net_dev,
             oal_bool_enum          en_is_aborted
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wal_force_scan_complete(oal_net_device_stru   *pst_net_dev,
                                         oal_bool_enum          en_is_aborted)
{
    mac_vap_stru            *pst_mac_vap;
    hmac_vap_stru           *pst_hmac_vap;
    hmac_device_stru        *pst_hmac_device;
    hmac_scan_stru           *pst_scan_mgmt;

    pst_mac_vap  = OAL_NET_DEV_PRIV(pst_net_dev);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_force_scan_complete::Cannot find mac_vap by net_dev!}");
        return -OAL_EINVAL;
    }

    /* 获取hmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_force_scan_complete::pst_hmac_device[%d] is null!}",
                         pst_mac_vap->uc_device_id);
        return -OAL_EINVAL;
    }

    /* stop的vap和正在扫描的vap不相同则直接返回 */
    if (pst_mac_vap->uc_vap_id != pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_force_scan_complete::stop_vap[%d] is different scan_vap[%d]!}",
                         pst_mac_vap->uc_vap_id,
                         pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id);
        return OAL_SUCC;
    }

    pst_scan_mgmt = &(pst_hmac_device->st_scan_mgmt);

    /* 如果是来自内部的扫描 */
    if (OAL_PTR_NULL == pst_scan_mgmt->pst_request)
    {
        /* 判断是否存在内部扫描，如果存在，也需要停止 */
        if ((OAL_TRUE == pst_hmac_device->st_scan_mgmt.en_is_scanning) &&
            (pst_mac_vap->uc_vap_id == pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id))
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{wal_force_scan_complete::may be internal scan, stop scan!}");
            /* 终止扫描 */
            wal_send_scan_abort_msg(pst_net_dev);
        }

        return OAL_SUCC;
    }

    /* 获取hmac vap */
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_force_scan_complete::hmac_vap is null, vap_id[%d]!}", pst_mac_vap->uc_vap_id);
        return -OAL_EINVAL;
    }

    /* 删除等待扫描超时定时器 */
    if (OAL_TRUE == pst_hmac_vap->st_scan_timeout.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_vap->st_scan_timeout));
    }

    /* 对于内核下发的扫描request资源加锁 */
    oal_spin_lock(&(pst_scan_mgmt->st_scan_request_spinlock));

    /* 如果是上层下发的扫描请求，则通知内核扫描结束，内部扫描不需通知 */
    if (OAL_PTR_NULL != pst_scan_mgmt->pst_request)
    {
        /* 上报内核扫描结果 */
        wal_inform_all_bss(pst_hmac_device->pst_device_base_info->pst_wiphy,
                           &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt),
                           pst_mac_vap->uc_vap_id);

        /* 通知内核扫描终止 */
        oal_cfg80211_scan_done(pst_scan_mgmt->pst_request, en_is_aborted);

        pst_scan_mgmt->pst_request = OAL_PTR_NULL;
        pst_scan_mgmt->en_complete = OAL_TRUE;
        /* 通知完内核，释放资源后解锁 */
        oal_spin_unlock(&(pst_scan_mgmt->st_scan_request_spinlock));
        /* 下发device终止扫描 */
        wal_send_scan_abort_msg(pst_net_dev);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{wal_force_scan_complete::vap_id[%d] notify kernel scan abort!}",
                         pst_mac_vap->uc_vap_id);

        /* 让编译器优化时保证OAL_WAIT_QUEUE_WAKE_UP在最后执行 */
        OAL_SMP_MB();
        OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&pst_scan_mgmt->st_wait_queue);
    }
    else
    {
        /* 通知完内核，释放资源后解锁 */
        oal_spin_unlock(&(pst_scan_mgmt->st_scan_request_spinlock));
    }

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

