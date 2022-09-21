/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_chan_mgmt.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年2月22日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月22日
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
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_device.h"
#include "hmac_mgmt_sta.h"
#include "hmac_sme_sta.h"
#include "hmac_fsm.h"
#include "hmac_dfs.h"
#include "hmac_chan_mgmt.h"
#include "mac_device.h"
#include "hmac_scan.h"
#include "frw_ext_if.h"
#include "hmac_resource.h"
#include "hmac_encap_frame.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CHAN_MGMT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define HMAC_CENTER_FREQ_2G_40M_OFFSET    2   /* 中心频点相对于主信道idx的偏移量 */
#define HMAC_AFFECTED_CH_IDX_OFFSET       5   /* 2.4GHz下，40MHz带宽所影响的信道半径，中心频点 +/- 5个信道 */
/* 5G频段 信道与中心频率映射 */
OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_5g[MAC_CHANNEL_FREQ_5_BUTT] =
{
    { 5180, 36, 0},
    { 5200, 40, 1},
    { 5220, 44, 2},
    { 5240, 48, 3},
    { 5260, 52, 4},
    { 5280, 56, 5},
    { 5300, 60, 6},
    { 5320, 64, 7},
    { 5500, 100, 8},
    { 5520, 104, 9},
    { 5540, 108, 10},
    { 5560, 112, 11},
    { 5580, 116, 12},
    { 5600, 120, 13},
    { 5620, 124, 14},
    { 5640, 128, 15},
    { 5660, 132, 16},
    { 5680, 136, 17},
    { 5700, 140, 18},
    { 5720, 144, 19},
    { 5745, 149, 20},
    { 5765, 153, 21},
    { 5785, 157, 22},
    { 5805, 161, 23},
    { 5825, 165, 24},
    /* for JP 4.9G */
    { 4920, 184, 25},
    { 4940, 188, 26},
    { 4960, 192, 27},
    { 4980, 196, 28},
};

/* 2.4G频段 信道与中心频率映射 */
OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_2g[MAC_CHANNEL_FREQ_2_BUTT] =
{
    { 2412, 1, 0},
    { 2417, 2, 1},
    { 2422, 3, 2},
    { 2427, 4, 3},
    { 2432, 5, 4},
    { 2437, 6, 5},
    { 2442, 7, 6},
    { 2447, 8, 7},
    { 2452, 9, 8},
    { 2457, 10, 9},
    { 2462, 11, 10},
    { 2467, 12, 11},
    { 2472, 13, 12},
    { 2484, 14, 13},
};

/*****************************************************************************
  3 函数声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
OAL_STATIC oal_void hmac_chan_stop_40M_recovery_timer(mac_vap_stru *pst_mac_vap);
#endif
/*****************************************************************************
  4 函数实现
*****************************************************************************/

oal_uint32 hmac_dump_chan(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param)
{
    dmac_set_chan_stru *pst_chan;

    if ( (OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param) )
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_chan = (dmac_set_chan_stru*)puc_param;
    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "channel mgmt info\r\n");
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_chan_number=%d\r\n", pst_chan->st_channel.uc_chan_number);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_band=%d\r\n", pst_chan->st_channel.en_band);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bandwidth=%d\r\n", pst_chan->st_channel.en_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_idx=%d\r\n", pst_chan->st_channel.uc_idx);

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "c_announced_channel=%d\r\n", pst_chan->st_ch_switch_info.uc_announced_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_announced_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_announced_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_ch_switch_cnt=%d\r\n", pst_chan->st_ch_switch_info.uc_ch_switch_cnt);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_ch_switch_status=%d\r\n", pst_chan->st_ch_switch_info.en_ch_switch_status);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bw_switch_status=%d\r\n", pst_chan->st_ch_switch_info.en_bw_switch_status);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_csa_present_in_bcn=%d\r\n", pst_chan->st_ch_switch_info.en_csa_present_in_bcn);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_start_chan_idx=%d\r\n", pst_chan->st_ch_switch_info.uc_start_chan_idx);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_end_chan_idx=%d\r\n", pst_chan->st_ch_switch_info.uc_end_chan_idx);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_user_pref_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_user_pref_bandwidth);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_bw_change=%d\r\n", pst_chan->st_ch_switch_info.en_bw_change);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_new_channel=%d\r\n", pst_chan->st_ch_switch_info.uc_new_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_new_bandwidth=%d\r\n", pst_chan->st_ch_switch_info.en_new_bandwidth);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "uc_new_ch_swt_cnt=%d\r\n", pst_chan->st_ch_switch_info.uc_new_ch_swt_cnt);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_waiting_to_shift_channel=%d\r\n",
                pst_chan->st_ch_switch_info.en_waiting_to_shift_channel);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_waiting_for_ap=%d\r\n", pst_chan->st_ch_switch_info.en_waiting_for_ap);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_channel_swt_cnt_zero=%d\r\n", pst_chan->st_ch_switch_info.en_channel_swt_cnt_zero);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "en_te_b=%d\r\n",pst_chan->st_ch_switch_info.en_te_b);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "ul_chan_report_for_te_a=%d\r\n", pst_chan->st_ch_switch_info.ul_chan_report_for_te_a);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_send_ht_notify_chan_width
 功能描述  : 发送 ht  notify chan width帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_send_ht_notify_chan_width(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data)
{
    oal_uint16                    us_frame_len;
    oal_netbuf_stru              *pst_netbuf;
    mac_tx_ctl_stru              *pst_tx_ctl;
    oal_uint32                    ul_ret;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_data))
    {
        OAM_ERROR_LOG2(0, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::param null, %p %p.}", pst_mac_vap, puc_data);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 申请ht_notify_chan_width 帧空间 */
    pst_netbuf = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN, OAL_NETBUF_PRIORITY_MID);
    if(OAL_PTR_NULL == pst_netbuf)
    {
       OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::Alloc netbuf(size %d) null in normal_netbuf.}", MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN);
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 封装SA Query request帧*/
    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_NETBUF_CB_SIZE());
    us_frame_len = hmac_encap_notify_chan_width(pst_mac_vap, (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf), puc_data);

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf); /* 获取cb结构体 */
    pst_tx_ctl->us_mpdu_len     = us_frame_len;               /* dmac发送需要的mpdu长度 */
    pst_tx_ctl->us_tx_user_idx  = MAC_INVALID_USER_ID;        /* 发送完成需要获取user结构体 */
    oal_netbuf_put(pst_netbuf, us_frame_len);

    /* Buffer this frame in the Memory Queue for transmission */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_netbuf, us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_ht_notify_chan_width::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_chan_multi_switch_to_20MHz_ap
 功能描述  : 设置device下所有VAP信道参数，准备切换至20MHz运行
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_multi_switch_to_20MHz_ap(hmac_vap_stru *pst_hmac_vap)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    hmac_vap_stru     *pst_hmac_vap_iter;
#endif

    OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
            "{hmac_chan_multi_switch_to_20MHz_ap::bit_2040_channel_switch_prohibited=%d}",
            pst_hmac_vap->en_2040_switch_prohibited);

    /* 如果不允许切换带宽，则直接返回 */
    if (OAL_TRUE == pst_hmac_vap->en_2040_switch_prohibited)
    {
        return;
    }

    pst_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_switch_to_20MHz_ap::pst_device null,uc_device_id=%d.}",
                       pst_hmac_vap->st_vap_base_info.uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_switch_to_20MHz_ap::pst_device null,none vap.}");
        return;
    }

    if (mac_is_dbac_running(pst_device))
    {
        pst_mac_vap = &pst_hmac_vap->st_vap_base_info;
        pst_hmac_vap->en_40M_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
        hmac_chan_initiate_switch_to_20MHz_ap(&pst_hmac_vap->st_vap_base_info);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                       pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif
        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
        return;
    }

    /* 遍历device下所有vap，设置VAP信道参数，准备切换至20MHz运行 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                           "{hmac_chan_multi_switch_to_20MHz_ap::pst_mac_vap null,vap_idx=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        pst_hmac_vap_iter = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_vap_iter)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                           "{hmac_chan_multi_switch_to_20MHz_ap::pst_hmac_vap_iter null,vap_idx=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 40M切20M前记录40M带宽，40M恢复定时器将会使用这个信道进行恢复 */
        pst_hmac_vap_iter->en_40M_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
#endif

        hmac_chan_initiate_switch_to_20MHz_ap(pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                       pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif

        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
    }
}

/*****************************************************************************
 函 数 名  : hmac_chan_initiate_switch_to_new_channel
 功能描述  : 设置VAP信道参数，准备切换至新信道运行
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             uc_channel  : 新信道号(准备切换到的20MHz主信道号)
             en_bandwidth: 新带宽模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_chan_initiate_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    frw_event_mem_stru            *pst_event_mem;
    frw_event_stru                *pst_event;
    oal_uint32                     ul_ret;
    dmac_set_ch_switch_info_stru  *pst_ch_switch_info;
    mac_device_stru               *pst_mac_device;

    /* AP准备切换信道 */
    pst_mac_vap->st_ch_switch_info.en_ch_switch_status    = WLAN_CH_SWITCH_STATUS_1;
    pst_mac_vap->st_ch_switch_info.uc_announced_channel   = uc_channel;
    pst_mac_vap->st_ch_switch_info.en_announced_bandwidth = en_bandwidth;

    /* 在Beacon帧中添加Channel Switch Announcement IE */
    pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn  = OAL_TRUE;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_initiate_switch_to_new_channel::uc_announced_channel=%d,en_announced_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::pst_mac_device null.}");
        return;
    }
    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_set_ch_switch_info_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN,
                    OAL_SIZEOF(dmac_set_ch_switch_info_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 填写事件payload */
    pst_ch_switch_info = (dmac_set_ch_switch_info_stru *)pst_event->auc_event_data;
    pst_ch_switch_info->en_ch_switch_status    = WLAN_CH_SWITCH_STATUS_1;
    pst_ch_switch_info->uc_announced_channel   = uc_channel;
    pst_ch_switch_info->en_announced_bandwidth = en_bandwidth;
    pst_ch_switch_info->uc_ch_switch_cnt = pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt;
    pst_ch_switch_info->en_csa_present_in_bcn  = OAL_TRUE;
    pst_ch_switch_info->uc_csa_vap_cnt         = pst_mac_device->uc_csa_vap_cnt;


    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_initiate_switch_to_new_channel::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_chan_multi_switch_to_new_channel
 功能描述  : 遍历device下所有ap，设置VAP信道参数，准备切换至新信道运行
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             uc_channel  : 新信道号(准备切换到的20MHz主信道号)
             en_bandwidth: 新带宽模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFS
oal_void hmac_dfs_set_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_mac_device;
    mac_vap_stru      *pst_vap;
    oal_uint8          uc_chan_idx;
    oal_uint32         ul_ret;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::pst_device(%d) null.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::none vap.}");
        return;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_device->uc_csa_vap_cnt = 0;

    /* 遍历device下所有ap，设置ap信道参数，发送CSA帧，准备切换至新信道运行 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::pst_ap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 只有running AP需要发送CSA帧 */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP     == pst_vap->en_vap_state))
        {
            pst_mac_device->uc_csa_vap_cnt++;
            if(uc_channel == pst_vap->st_channel.uc_chan_number)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFS, "{hmac_dfs_set_channel::same channel num %d, no need to change.}", uc_channel);
                return;
            }
            hmac_chan_initiate_switch_to_new_channel(pst_vap, uc_channel, pst_vap->st_channel.en_bandwidth);
        }
    }
}
oal_void  hmac_chan_multi_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_mac_device;
    mac_vap_stru      *pst_vap;
    oal_uint8          uc_chan_idx;
    oal_uint32         ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_multi_switch_to_new_channel::uc_channel=%d,en_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::pst_device(%d) null.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::none vap.}");
        return;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, uc_channel, &uc_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_device->uc_csa_vap_cnt = 0;

    /* 遍历device下所有ap，设置ap信道参数，发送CSA帧，准备切换至新信道运行 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_switch_to_new_channel::pst_ap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 只有running AP需要发送CSA帧 */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP     == pst_vap->en_vap_state))
        {
            pst_mac_device->uc_csa_vap_cnt++;
            hmac_chan_initiate_switch_to_new_channel(pst_vap, uc_channel, en_bandwidth);
        }
        else  /* 其它站点只需要更新信道信息 */
        {
            /* 更新VAP下的主20MHz信道号、带宽模式、信道索引 */
            pst_vap->st_channel.uc_chan_number = uc_channel;
            pst_vap->st_channel.uc_idx         = uc_chan_idx;
            pst_vap->st_channel.en_bandwidth   = en_bandwidth;
        }
    }
}

#else

oal_void  hmac_chan_multi_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_ap;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_multi_switch_to_new_channel::uc_channel=%d,en_bandwidth=%d}",
        uc_channel, en_bandwidth);

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::pst_device null.}");
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::none vap.}");
        return;
    }

    /* 遍历device下所有ap，设置ap信道参数，准备切换至新信道运行 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_ap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_ap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_switch_to_new_channel::pst_ap null.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 只更新AP侧的信道切换信息 */
        if (WLAN_VAP_MODE_BSS_AP != pst_ap->en_vap_mode)
        {
            continue;
        }

        hmac_chan_initiate_switch_to_new_channel(pst_ap, uc_channel, en_bandwidth);
    }
}

#endif /* end of _PRE_WLAN_FEATURE_DFS */

oal_void  hmac_chan_sync_init(mac_vap_stru *pst_mac_vap, dmac_set_chan_stru *pst_set_chan)
{
    oal_memset(pst_set_chan, 0, OAL_SIZEOF(dmac_set_chan_stru));
    oal_memcopy(&pst_set_chan->st_channel, &pst_mac_vap->st_channel,
                    OAL_SIZEOF(mac_channel_stru));
    oal_memcopy(&pst_set_chan->st_ch_switch_info, &pst_mac_vap->st_ch_switch_info,
                    OAL_SIZEOF(mac_ch_switch_info_stru));
}

/*****************************************************************************
 函 数 名  : hmac_chan_do_sync
 功能描述  : HMAC模块抛事件到DMAC模块，设置SW/MAC/PHY/RF中的信道和带宽，
             使VAP工作在新信道上
 输入参数  : pst_mac_vap : mac_vap_stru
             pst_set_chan  : dmac_set_chan_stru
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_do_sync(mac_vap_stru *pst_mac_vap, dmac_set_chan_stru *pst_set_chan)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;
    oal_uint8                 uc_idx;

    hmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);
    /* 更新VAP下的主20MHz信道号、带宽模式、信道索引 */
    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_set_chan->st_channel.uc_chan_number, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_chan_sync::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return;
    }

    pst_mac_vap->st_channel.uc_chan_number = pst_set_chan->st_channel.uc_chan_number;
    pst_mac_vap->st_channel.en_bandwidth   = pst_set_chan->st_channel.en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;


    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_set_chan_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_sync::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN,
                    OAL_SIZEOF(dmac_set_chan_stru),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)pst_set_chan, OAL_SIZEOF(dmac_set_chan_stru));

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_sync::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_chan_sync
 功能描述  : HMAC将信道/带宽信息同步到DMAC
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             uc_channel  : 将要被设置的信道号
             en_bandwidth: 将要被设置的带宽模式
             en_switch_immediately: DMAC侧收到同步事件之后是否立即切换
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void hmac_chan_sync(mac_vap_stru *pst_mac_vap,
            oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth,
            oal_bool_enum_uint8 en_switch_immediately)
{
    dmac_set_chan_stru st_set_chan;

    hmac_chan_sync_init(pst_mac_vap, &st_set_chan);
    st_set_chan.st_channel.uc_chan_number = uc_channel;
    st_set_chan.st_channel.en_bandwidth = en_bandwidth;
    st_set_chan.en_switch_immediately = en_switch_immediately;
    hmac_chan_do_sync(pst_mac_vap, &st_set_chan);
}


/*****************************************************************************
 函 数 名  : hmac_chan_multi_select_channel_mac
 功能描述  : 遍历device下所有VAP，设置SW/MAC/PHY/RF中的信道和带宽，使VAP工作在新信道上
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             uc_channel  : 将要被设置的信道号
             en_bandwidth: 将要被设置的带宽模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_vap;

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_select_channel_mac::uc_channel=%d,en_bandwidth=%d}",
            uc_channel, en_bandwidth);

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_multi_select_channel_mac::pst_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_multi_select_channel_mac::none vap.}");
        return;
    }

    if (mac_is_dbac_running(pst_device))
    {
        hmac_chan_sync(pst_mac_vap, uc_channel, en_bandwidth, OAL_TRUE);
        return;
    }

    /* 遍历device下所有vap， */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                           "{hmac_chan_multi_select_channel_mac::pst_vap null,vap_id=%d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        hmac_chan_sync(pst_vap, uc_channel, en_bandwidth, OAL_TRUE);
    }
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 函 数 名  : hmac_chan_is_this_40MHz_set_possible
 功能描述  : 判断能否在给定的"主信道 + 次信道偏移量"上，建立起40MHz BSS
 输入参数  : pst_mac_device      : MAC DEVICE结构体指针
             pst_mac_vap         : MAC VAP结构体指针
             uc_pri_chan_idx     : 主信道索引
             en_sec_chan_offset  : 次信道偏移量
 输出参数  : pst_chan_scan_report: 信道评估结构体指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_this_40MHz_set_possible(
                mac_device_stru              *pst_mac_device,
                mac_vap_stru                 *pst_mac_vap,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_sec_chan_offset,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    mac_ap_ch_info_stru           *pst_ap_channel_list;
    wlan_channel_band_enum_uint8   en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                      uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8                      uc_affected_ch_idx_offset = mac_get_affected_ch_idx_offset(en_band);
    oal_uint8                      uc_sec_ch_idx_offset = mac_get_sec_ch_idx_offset(en_band);
    oal_uint8                      uc_ch_idx;
    oal_uint8                      uc_sec_chan_idx;
    oal_uint8                      uc_affected_chan_lo = 0, uc_affected_chan_hi = 0;
    hmac_network_type_enum_uint8   en_network_type;
    hmac_chan_op_enum_uint8        en_allowed_bit;
    oal_bool_enum_uint8            en_flag_2040_op_permitted = OAL_TRUE;
    oal_uint32                     ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_chan_is_this_40MHz_set_possible::uc_pri_chan_idx=%d,en_sec_chan_offset=%d}",
        uc_pri_chan_idx, en_sec_chan_offset);

    ul_ret = mac_is_channel_idx_valid(en_band, uc_pri_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    if (MAC_SCA == en_sec_chan_offset)
    {
        /* 计算次信道索引 */
        if (uc_num_supp_chan > uc_pri_chan_idx + uc_sec_ch_idx_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx + uc_sec_ch_idx_offset;
        }
        else
        {
            return OAL_FALSE;
        }

        en_network_type = HMAC_NETWORK_SCA;
        en_allowed_bit  = HMAC_SCA_ALLOWED;

        /* 计算受影响的信道下限索引 */
        uc_affected_chan_lo = (uc_pri_chan_idx >= uc_affected_ch_idx_offset) ?
                        (uc_pri_chan_idx - uc_affected_ch_idx_offset) : 0;

        /* 计算受影响的信道上限索引 */
        uc_affected_chan_hi = (uc_num_supp_chan > uc_sec_chan_idx + uc_affected_ch_idx_offset) ?
                        (uc_sec_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);
    }
    else if (MAC_SCB == en_sec_chan_offset)
    {
        /* 计算次信道索引 */
        if (uc_pri_chan_idx >= uc_sec_ch_idx_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx - uc_sec_ch_idx_offset;
        }
        else
        {
            return OAL_FALSE;
        }

        en_network_type = HMAC_NETWORK_SCB;
        en_allowed_bit  = HMAC_SCB_ALLOWED;

        /* 计算受影响的信道下限索引 */
        uc_affected_chan_lo = (uc_sec_chan_idx >= uc_affected_ch_idx_offset) ?
                        (uc_sec_chan_idx - uc_affected_ch_idx_offset) : 0;

        /* 计算受影响的信道上限索引 */
        uc_affected_chan_hi = (uc_num_supp_chan > uc_pri_chan_idx + uc_affected_ch_idx_offset) ?
                        (uc_pri_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);
    }
    else
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    /* 对于给定的"主信道 + 次信道偏移量"所波及的范围内(中心频点 +/- 5个信道)，判断能否建立40MHz BSS */
    for (uc_ch_idx = uc_affected_chan_lo; uc_ch_idx <= uc_affected_chan_hi; uc_ch_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, uc_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            continue;
        }

        pst_ap_channel_list = &(pst_mac_device->st_ap_channel_list[uc_ch_idx]);

        /* 如果这条信道上存在BSS */
        if (MAC_CH_TYPE_NONE != pst_ap_channel_list->en_ch_type)
        {
            /* 累加这条信道上扫描到的BSS个数 */
            pst_chan_scan_report[uc_pri_chan_idx].aus_num_networks[en_network_type] += pst_ap_channel_list->us_num_networks;

            /* 新BSS的主信道可以与已有的20/40MHz BSS的主信道重合 */
            if (uc_ch_idx == uc_pri_chan_idx)
            {
                if (MAC_CH_TYPE_PRIMARY == pst_ap_channel_list->en_ch_type)
                {
                    continue;
                }
            }

            /* 新BSS的次信道可以与已有的20/40MHz BSS的次信道重合 */
            if (uc_ch_idx == uc_sec_chan_idx)
            {
                if (MAC_CH_TYPE_SECONDARY == pst_ap_channel_list->en_ch_type)
                {
                    continue;
                }
            }

            en_flag_2040_op_permitted = OAL_FALSE;
        }
    }

    /* 如果20/40MHz共存没有使能，则认为可以建立40MHz BSS，除非用户设置了"40MHz不允许"位 */
    if ((OAL_FALSE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (OAL_FALSE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)))
    {
        en_flag_2040_op_permitted = OAL_TRUE;
    }
#ifdef _PRE_WLAN_FEATURE_5G
    /* 5GHz情况下不关心20/40M共存配置和40M不允许设置，一定建立40MHz BSS */
    else if (WLAN_BAND_5G == en_band)
    {
        en_flag_2040_op_permitted = OAL_TRUE;
    }
#endif /* _PRE_WLAN_FEATURE_5G */

    if (OAL_TRUE == en_flag_2040_op_permitted)
    {
        pst_chan_scan_report[uc_pri_chan_idx].en_chan_op |= en_allowed_bit;
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_chan_get_2040_op_chan_list
 功能描述  : 解析信道扫描结果，评估每条信道是否能够建立BSS
 输入参数  : pst_mac_vap         : MAC VAP结构体指针
 输出参数  : pst_chan_scan_report: 信道评估结构体指针
 返 回 值  : OAL_TRUE : 在某些信道上能够建立40MHz BSS
             OAL_FALSE: 在任何信道上都不能够建立40MHz BSS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_get_2040_op_chan_list(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    mac_device_stru       *pst_mac_device;
    oal_uint8              uc_chan_idx;
    oal_uint8              uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_vap->st_channel.en_band);
    oal_bool_enum_uint8    en_fortyMHz_poss = OAL_FALSE;
    oal_bool_enum_uint8    en_flag;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_get_2040_op_chan_list}");

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_get_2040_op_chan_list::pst_mac_device null.}");
        return OAL_FALSE;
    }

    for (uc_chan_idx = 0; uc_chan_idx < uc_num_supp_chan; uc_chan_idx++)
    {
        /* 判断能否建立SCA类型的40MHz BSS */
        en_flag = hmac_chan_is_this_40MHz_set_possible(pst_mac_device, pst_mac_vap, uc_chan_idx, MAC_SCA, pst_chan_scan_report);
        if (OAL_TRUE == en_flag)
        {
            en_fortyMHz_poss = OAL_TRUE;
        }

        /* 判断能否建立SCB类型的40MHz BSS */
        en_flag = hmac_chan_is_this_40MHz_set_possible(pst_mac_device, pst_mac_vap, uc_chan_idx, MAC_SCB, pst_chan_scan_report);
        if (OAL_TRUE == en_flag)
        {
            en_fortyMHz_poss = OAL_TRUE;
        }
    }

    /* 2.4GHz下，如果"40MHz不允许"位是否被设置，则不允许建立40MHz BSS */
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        if ((OAL_TRUE == pst_mac_device->en_40MHz_intol_bit_recd) ||
            (OAL_TRUE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)))
        {
            en_fortyMHz_poss = OAL_FALSE;
        }
    }

    return en_fortyMHz_poss;
}



/*****************************************************************************
 函 数 名  : hmac_chan_del_user
 功能描述  : 更新40M intolerant user bitmap信息
 输入参数  : hmac_vap_stru *pst_hmac_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_chan_update_40M_intol_user(mac_vap_stru *pst_mac_vap,
                                    mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_40M_intol_bit)
{
    hmac_vap_stru   *pst_hmac_vap;
    oal_uint16       us_user_id;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_update_40M_intol_user::pst_hmac_vap null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_user_id = pst_mac_user->us_assoc_id;
    if (us_user_id >= 32*MAC_DEV_MAX_40M_INTOL_USER_BITMAP_LEN)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_update_40M_intol_user:: user id exceed max user id %d}",
                       us_user_id);
        return OAL_ERR_CODE_BUTT;
    }

    if (OAL_TRUE == en_40M_intol_bit)
    {
        pst_hmac_vap->aul_40M_intol_user_bitmap[us_user_id/32] |= (1<<(us_user_id%32));
    }
    else
    {
        pst_hmac_vap->aul_40M_intol_user_bitmap[us_user_id/32] &= ~((oal_uint32)(1<<(us_user_id%32)));
    }

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                   "{hmac_chan_update_40M_intol_user:: bitmap 0x%x 0x%x 0x%x 0x%x}",
                   pst_hmac_vap->aul_40M_intol_user_bitmap[0], pst_hmac_vap->aul_40M_intol_user_bitmap[1],
                   pst_hmac_vap->aul_40M_intol_user_bitmap[2], pst_hmac_vap->aul_40M_intol_user_bitmap[3]);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_prepare_for_40M_recovery
 功能描述  : 在恢复40M之前，要清除obss扫描结果，40M禁止位，20M request位等信息
 输入参数  : hmac_vap_stru *pst_hmac_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_chan_prepare_for_40M_recovery(hmac_vap_stru *pst_hmac_vap,
                                            wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                       "{hmac_chan_prepare_for_40M_recovery::pst_device null,uc_device_id=%d.}",
                       pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device->en_40MHz_intol_bit_recd = OAL_FALSE;

    // TODO 此处要确认一下是否需要清除存放在pst_mac_device中的
    //st_ap_channel_list信道?????????????

    /* 设置VAP带宽模式为20MHz */
    pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth = en_bandwidth;

    /* 设置带宽切换状态变量，表明在下一个DTIM时刻切换至20MHz运行 */
    pst_hmac_vap->st_vap_base_info.st_ch_switch_info.en_bw_switch_status = WLAN_BW_SWITCH_20_TO_40;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_40M_recovery_timeout_fn
 功能描述  : 40M恢复定时器超时，恢复40M带宽
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chan_40M_recovery_timeout_fn(void *p_arg)
{
    hmac_vap_stru          *pst_hmac_vap;
    mac_vap_stru           *pst_mac_vap;

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_40M_recovery_timeout_fn::40M recovery timer time out.}");

    pst_hmac_vap = (hmac_vap_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_chan_40M_recovery_timeout_fn::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    /* 清除20M相关的信息 */
    if (pst_hmac_vap->en_40M_bandwidth == WLAN_BAND_WIDTH_20M) /* 如果ap初始带宽为20M, 则*/
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because init 20M.}");
        return OAL_SUCC;
    }

    if (pst_hmac_vap->aul_40M_intol_user_bitmap[0] | pst_hmac_vap->aul_40M_intol_user_bitmap[1]
        | pst_hmac_vap->aul_40M_intol_user_bitmap[2] | pst_hmac_vap->aul_40M_intol_user_bitmap[3])
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because 40M intol sta assoc}");
        return OAL_SUCC;
    }

    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;
    if (WLAN_BAND_WIDTH_20M != pst_mac_vap->st_channel.en_bandwidth)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "{hmac_chan_40M_recovery_timeout_fn::no need 40M recovery because already 20M}");
        hmac_chan_stop_40M_recovery_timer(pst_mac_vap);
        return OAL_SUCC;
    }

    hmac_chan_prepare_for_40M_recovery(pst_hmac_vap, pst_hmac_vap->en_40M_bandwidth);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                        pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_start_40M_recovery_timer
 功能描述  : 启动obss扫描定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_chan_start_40M_recovery_timer(mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru                 *pst_hmac_vap;
    oal_uint32                     ul_timeout;

    /* 根据发起扫描的vap id获取hmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_2040, "{hmac_chan_start_40M_recovery_timer:: pst_hmac_vap is NULL.}");
        return;
    }

    // TODO 去掉
#if 1
    ul_timeout = mac_mib_get_BSSWidthTriggerScanInterval(pst_mac_vap) * 2 * 1000;
#else
    ul_timeout = 10000;
#endif
    OAM_INFO_LOG1(0, OAM_SF_2040, "{hmac_chan_start_40M_recovery_timer::ul_timeout=%d}", ul_timeout);

    if (OAL_FALSE == pst_hmac_vap->st_40M_recovery_timer.en_is_registerd)
    {
        FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_40M_recovery_timer),
                               hmac_chan_40M_recovery_timeout_fn,
                               ul_timeout,
                               (void *)pst_hmac_vap,
                               OAL_TRUE,
                               OAM_MODULE_ID_HMAC,
                               pst_mac_vap->ul_core_id);
    }
    else
    {
        FRW_TIMER_RESTART_TIMER(&(pst_hmac_vap->st_40M_recovery_timer), ul_timeout, OAL_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : hmac_chan_stop_40M_recovery_timer
 功能描述  : 启动obss扫描定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_chan_stop_40M_recovery_timer(mac_vap_stru *pst_mac_vap)
{
    hmac_vap_stru                 *pst_hmac_vap;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_2040, "{hmac_chan_stop_40M_recovery_timer:: pst_hmac_vap is NULL.}");
        return;
    }

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_stop_40M_recovery_timer}");
    FRW_TIMER_STOP_TIMER(&(pst_hmac_vap->st_40M_recovery_timer));

    return;
}

#endif
/*****************************************************************************
 函 数 名  : hmac_chan_get_40MHz_possibility
 功能描述  : 判断在当前环境(扫描结果)下，能否建立40MHz BSS
 输入参数  : pst_mac_vap         : MAC VAP结构体指针
 输出参数  : pst_chan_scan_report: 信道评估结构体指针
 返 回 值  : OAL_TRUE : 能够建立
             OAL_FALSE: 不能建立
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_get_40MHz_possibility(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report)
{
    oal_bool_enum_uint8   en_fortyMHz_poss = OAL_FALSE;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_get_40MHz_possibility}");
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    if (OAL_TRUE ==  mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
    {
        en_fortyMHz_poss = hmac_chan_get_2040_op_chan_list(pst_mac_vap, pst_chan_scan_report);
    }
#endif

    return en_fortyMHz_poss;
}

/*****************************************************************************
 函 数 名  : hmac_chan_init_chan_scan_report
 功能描述  : 这函数看看到底要不要
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_chan_init_chan_scan_report(
                mac_device_stru              *pst_mac_device,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_num_supp_chan)
{
    oal_uint8    uc_idx;

    OAL_MEMZERO(pst_chan_scan_report, uc_num_supp_chan * OAL_SIZEOF(*pst_chan_scan_report));

    for (uc_idx = 0; uc_idx < uc_num_supp_chan; uc_idx++)
    {
    #ifdef _PRE_WLAN_FEATURE_DFS
        if (OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device))
        {
            if ((MAC_CHAN_NOT_SUPPORT        != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status) &&
                (MAC_CHAN_BLOCK_DUE_TO_RADAR != pst_mac_device->st_ap_channel_list[uc_idx].en_ch_status))
            {
                pst_chan_scan_report[uc_idx].en_chan_op |= HMAC_OP_ALLOWED;
            }
        }
        else
    #endif
        {
            pst_chan_scan_report[uc_idx].en_chan_op |= HMAC_OP_ALLOWED;
        }
    }
}

/*****************************************************************************
 函 数 名  : hmac_chan_is_40MHz_sca_allowed
 功能描述  : 对于给定的主信道，判断能否建立SCA类型的40MHz BSS
 输入参数  : pst_mac_vap         : MAC VAP结构体指针
             pst_chan_scan_report: 信道评估结构体指针
             uc_pri_chan_idx     : 主信道号索引
             en_user_chan_offset : 用户优先选择的次信道偏移量
 输出参数  : 无
 返 回 值  : OAL_TRUE : 能够建立40MHz BSS
             OAL_FALSE: 不能建立40MHz BSS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_40MHz_sca_allowed(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_user_chan_offset)
{
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8                       uc_sec_chan_idx = 0;
    oal_uint32                      ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
            "{hmac_chan_is_40MHz_sca_allowed::uc_pri_chan_idx=%d, en_user_chan_offset=%d}",
            uc_pri_chan_idx, en_user_chan_offset);

    if (MAC_SCB == en_user_chan_offset)
    {
        return OAL_FALSE;
    }

    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_2G == en_band))
    {
        if (!(pst_chan_scan_report[uc_pri_chan_idx].en_chan_op & HMAC_SCA_ALLOWED))
        {
            return OAL_FALSE;
        }
    }

    uc_sec_chan_idx = uc_pri_chan_idx + mac_get_sec_ch_idx_offset(en_band);
    if (uc_sec_chan_idx >= uc_num_supp_chan)
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
#else
    return OAL_FALSE;
#endif
}

/*****************************************************************************
 函 数 名  : hmac_chan_is_40MHz_scb_allowed
 功能描述  : 对于给定的主信道，判断能否建立SCB类型的40MHz BSS
 输入参数  : pst_mac_vap         : MAC VAP结构体指针
             pst_chan_scan_report: 信道评估结构体指针
             uc_pri_chan_idx     : 主信道号索引
             en_user_chan_offset : 用户优先选择的次信道偏移量
 输出参数  : 无
 返 回 值  : OAL_TRUE : 能够建立40MHz BSS
             OAL_FALSE: 不能建立40MHz BSS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_40MHz_scb_allowed(
                mac_vap_stru                 *pst_mac_vap,
                hmac_eval_scan_report_stru   *pst_chan_scan_report,
                oal_uint8                     uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8     en_user_chan_offset)
{
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_sec_ch_idx_offset = mac_get_sec_ch_idx_offset(en_band);
    oal_uint8                       uc_sec_chan_idx = 0;
    oal_uint32                      ul_ret;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
            "{hmac_chan_is_40MHz_sca_allowed::uc_pri_chan_idx=%d, en_user_chan_offset=%d}",
            uc_pri_chan_idx, en_user_chan_offset);

    if (MAC_SCA == en_user_chan_offset)
    {
        return OAL_FALSE;
    }

    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_2G == en_band))
    {
        if (!(pst_chan_scan_report[uc_pri_chan_idx].en_chan_op & HMAC_SCB_ALLOWED))
        {
            return OAL_FALSE;
        }
    }

    if (uc_pri_chan_idx >= uc_sec_ch_idx_offset)
    {
        uc_sec_chan_idx = uc_pri_chan_idx - uc_sec_ch_idx_offset;
    }
    else
    {
        return OAL_FALSE;
    }

    ul_ret = mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
#else
    return OAL_FALSE;
#endif
}

/*****************************************************************************
 函 数 名  : hmac_chan_get_cumulative_networks
 功能描述  : 获取当前信道邻近(+/- 3个信道)的BSS个数
 输入参数  : pst_mac_device : MAC DEVICE结构体指针
             en_band        : 频段
             uc_pri_chan_idx: 主信道号索引
 输出参数  : 无
 返 回 值  : 当前信道邻近的BSS个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint16  hmac_chan_get_cumulative_networks(
                mac_device_stru                     *pst_mac_device,
                wlan_channel_bandwidth_enum_uint8    en_band,
                oal_uint8                            uc_pri_chan_idx)
{
    oal_uint16   us_cumulative_networks = 0;
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8    uc_affected_ch_idx_offset = mac_get_affected_ch_idx_offset(en_band);
    oal_uint8    uc_affected_chan_lo, uc_affected_chan_hi;
    oal_uint8    uc_chan_idx;
    oal_uint32   ul_ret;

    uc_affected_chan_lo = (uc_pri_chan_idx >= uc_affected_ch_idx_offset) ?
                    (uc_pri_chan_idx - uc_affected_ch_idx_offset) : 0;

    uc_affected_chan_hi = (uc_num_supp_chan > uc_pri_chan_idx + uc_affected_ch_idx_offset) ?
                    (uc_pri_chan_idx + uc_affected_ch_idx_offset) : (uc_num_supp_chan - 1);

    for (uc_chan_idx = uc_affected_chan_lo; uc_chan_idx <= uc_affected_chan_hi; uc_chan_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            us_cumulative_networks += pst_mac_device->st_ap_channel_list[uc_pri_chan_idx].us_num_networks;
        }
    }

    return us_cumulative_networks;
}

/*****************************************************************************
 函 数 名  : hmac_chan_get_user_pref_primary_ch
 功能描述  : 获取用户优先设置的信道
 输入参数  : pst_mac_device: MAC DEVICE结构体指针
 输出参数  : 无
 返 回 值  : 用户优先设置的信道
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  hmac_chan_get_user_pref_primary_ch(mac_device_stru *pst_mac_device)
{
    return pst_mac_device->uc_max_channel;
}

/*****************************************************************************
 函 数 名  : hmac_get_user_pref_bandwidth
 功能描述  : 获取用户优先设置的带宽模式
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 用户优先设置的带宽模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_channel_bandwidth_enum_uint8  hmac_chan_get_user_pref_bandwidth(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->st_ch_switch_info.en_user_pref_bandwidth;
}

/*****************************************************************************
 函 数 名  : hmac_chan_select_channel_for_operation
 功能描述  : 挑选一条信道(对)
 输入参数  : pst_mac_vap      : MAC VAP结构体指针
 输出参数  : puc_new_channel  : 挑选出来的主信道号
             pen_new_bandwidth: 挑选出来的带宽模式
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_chan_select_channel_for_operation(
                mac_vap_stru                        *pst_mac_vap,
                oal_uint8                           *puc_new_channel,
                wlan_channel_bandwidth_enum_uint8   *pen_new_bandwidth)
{
    mac_device_stru                     *pst_mac_device;
    hmac_eval_scan_report_stru          *pst_chan_scan_report;
    oal_uint8                            uc_least_busy_chan_idx = 0xFF;
    oal_uint16                           us_least_networks = 0xFFFF;
    oal_uint16                           us_cumulative_networks = 0;
    oal_bool_enum_uint8                  en_fortyMHz_poss, en_rslt = OAL_FALSE;
    mac_sec_ch_off_enum_uint8            en_user_chan_offset = MAC_SEC_CH_BUTT, en_chan_offset = MAC_SCN;
    oal_uint8                            uc_user_chan_idx = 0xFF, uc_chan_idx = 0xFF;
    oal_uint8                            uc_num_supp_chan = mac_get_num_supp_channel(pst_mac_vap->st_channel.en_band);
    oal_uint8                            uc_max_supp_channle = MAC_MAX_SUPP_CHANNEL;
    oal_uint32                           ul_ret = OAL_FAIL;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040,"{hmac_chan_select_channel_for_operation}");

    pst_chan_scan_report = (hmac_eval_scan_report_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, uc_max_supp_channle * OAL_SIZEOF(*pst_chan_scan_report), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chan_scan_report))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_select_channel_for_operation::pst_chan_scan_report memory alloc failed, size[%d].}", (uc_max_supp_channle * OAL_SIZEOF(*pst_chan_scan_report)));
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                       "{hmac_chan_select_channel_for_operation::pst_mac_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_chan_init_chan_scan_report(pst_mac_device, pst_chan_scan_report, uc_num_supp_chan);

    /* 如自动信道选择没有开启，则获取用户选择的主信道号，以及带宽模式 */
    if (OAL_FALSE == mac_device_is_auto_chan_sel_enabled(pst_mac_device))
    {
#ifdef _PRE_WLAN_FEATURE_DBAC
        if(mac_is_dbac_enabled(pst_mac_device))
        {
            ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                            pst_mac_vap->st_channel.uc_chan_number, &uc_user_chan_idx) ;
        }
        else
#endif
        {
            ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                            hmac_chan_get_user_pref_primary_ch(pst_mac_device), &uc_user_chan_idx) ;
        }
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_select_channel_for_operation::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
            OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

            return ul_ret;
        }

        en_user_chan_offset = mac_get_sco_from_bandwidth(hmac_chan_get_user_pref_bandwidth(pst_mac_vap));

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                      "{hmac_chan_select_channel_for_operation::User Preferred Channel id=%d sco=%d.}",
                      uc_user_chan_idx, en_user_chan_offset);
    }

    /* 判断在当前环境下是否能够建立40MHz BSS */
    en_fortyMHz_poss = hmac_chan_get_40MHz_possibility(pst_mac_vap, pst_chan_scan_report);

    /* 用户选择了主信道 */
    if (uc_user_chan_idx != 0xFF)
    {
        /* 如果能够建立40MHz BSS，并且用户也希望建立40MHz */
        if ((OAL_TRUE == en_fortyMHz_poss) && (MAC_SCN != en_user_chan_offset))
        {
            if (MAC_SCA == en_user_chan_offset)
            {
                en_rslt = hmac_chan_is_40MHz_sca_allowed(pst_mac_vap, pst_chan_scan_report, uc_user_chan_idx, en_user_chan_offset);
            }
            else if (MAC_SCB == en_user_chan_offset)
            {
                en_rslt = hmac_chan_is_40MHz_scb_allowed(pst_mac_vap, pst_chan_scan_report, uc_user_chan_idx, en_user_chan_offset);
            }
        }

        if (OAL_TRUE == en_rslt)
        {
            en_chan_offset = en_user_chan_offset;
        }

        uc_least_busy_chan_idx = uc_user_chan_idx;
    }
    /* 用户没有选择信道，自动选择一条最不繁忙的信道(对) */
    else
    {
        for (uc_chan_idx = 0; uc_chan_idx < uc_num_supp_chan; uc_chan_idx++)
        {
            if (!(pst_chan_scan_report[uc_chan_idx].en_chan_op & HMAC_OP_ALLOWED))
            {
                continue;
            }

            /* 判断主信道索引号是否有效 */
            ul_ret = mac_is_channel_idx_valid(pst_mac_vap->st_channel.en_band, uc_chan_idx);
            if (OAL_SUCC != ul_ret)
            {
                continue;
            }

            /* 能够建立40MHz BSS */
            if ((OAL_TRUE == en_fortyMHz_poss))
            {
                /* 判断主信道上(右)面的信道是否可作为次信道 */
                en_rslt = hmac_chan_is_40MHz_sca_allowed(pst_mac_vap, pst_chan_scan_report, uc_chan_idx, en_user_chan_offset);
                if (OAL_TRUE == en_rslt)
                {
                    /* 如果这条信道最不繁忙，则选择这条信道作为"当前最不繁忙信道" */
                    if (pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCA] < us_least_networks)
                    {
                        us_least_networks      = pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCA];
                        uc_least_busy_chan_idx = uc_chan_idx;
                        en_chan_offset         = MAC_SCA;
                    }
                }

                /* 判断主信道下(左)面的信道是否可作为次信道 */
                en_rslt = hmac_chan_is_40MHz_scb_allowed(pst_mac_vap, pst_chan_scan_report, uc_chan_idx, en_user_chan_offset);
                if (OAL_TRUE == en_rslt)
                {
                    /* 如果这条信道最不繁忙，则选择这条信道作为"当前最不繁忙信道" */
                    if (pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCB] < us_least_networks)
                    {
                        us_least_networks      = pst_chan_scan_report[uc_chan_idx].aus_num_networks[HMAC_NETWORK_SCB];
                        uc_least_busy_chan_idx = uc_chan_idx;
                        en_chan_offset         = MAC_SCB;
                    }
                }
            }
            /* 不能够建立40MHz BSS */
            else
            {
                /* 获取当前信道邻近的BSS个数 */
                us_cumulative_networks = hmac_chan_get_cumulative_networks(pst_mac_device,
                                pst_mac_vap->st_channel.en_band, uc_chan_idx);

                /* 选择邻近BSS最少的一条信道作为"当前最不繁忙信道" */
                if (us_cumulative_networks < us_least_networks)
                {
                    us_least_networks      = us_cumulative_networks;
                    uc_least_busy_chan_idx = uc_chan_idx;
                }
            }
        }
    }

    mac_get_channel_num_from_idx(pst_mac_vap->st_channel.en_band, uc_least_busy_chan_idx, puc_new_channel);

    *pen_new_bandwidth = mac_get_bandwidth_from_sco(en_chan_offset);

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                  "{hmac_chan_select_channel_for_operation::Selected Channel=%d, Selected Bandwidth=%d.}",
                  (*puc_new_channel), (*pen_new_bandwidth));

    OAL_MEM_FREE((oal_void *)pst_chan_scan_report, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_reval_status
 功能描述  : 根据OBSS扫描结果，重新选择一条最合适的工作信道
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             puc_data   : 指向20/40 BSS Intolerant Channel Report element中
                          "Channel List"的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_reval_status(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap)
{
    oal_uint8                            uc_new_channel   = 0;
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth = WLAN_BAND_WIDTH_BUTT;
    oal_uint32                           ul_ret;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_reval_status}");

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_chan_reval_status::pst_mac_device or pst_mac_vap null.}", pst_mac_device, pst_mac_vap);
        return;
    }

    /* 如果AP已经准备进行信道切换，则直接返回，不做任何处理 */
    if (WLAN_CH_SWITCH_STATUS_1 == pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        return;
    }

    ul_ret = hmac_chan_select_channel_for_operation(pst_mac_vap, &uc_new_channel, &en_new_bandwidth);
    if (OAL_SUCC != ul_ret)
    {
        return;
    }

    ul_ret = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, uc_new_channel);
    if ((OAL_SUCC != ul_ret) || (en_new_bandwidth >= WLAN_BAND_WIDTH_BUTT))
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_chan_reval_status::Could not start network using the selected channel[%d] or bandwidth[%d].}",
                         uc_new_channel, en_new_bandwidth);
        return;
    }

    /* 主20MHz信道改变(按照目前的算法，主信道号应该不会改变，可能会改变的只是带宽模式) */
    if (uc_new_channel != pst_mac_vap->st_channel.uc_chan_number)
    {
        pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt = WLAN_CHAN_SWITCH_DEFAULT_CNT;
        hmac_chan_multi_switch_to_new_channel(pst_mac_vap, uc_new_channel, en_new_bandwidth);
    }
    /* 主20MHz信道不变，次20MHz or 40MHz信道改变 */
    else if (en_new_bandwidth != pst_mac_vap->st_channel.en_bandwidth)
    {
        hmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, en_new_bandwidth);
        hmac_send_ht_notify_chan_width(pst_mac_vap, BROADCAST_MACADDR);
    }
    else
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_reval_status::No Channel change after re-evaluation.}");
    }
}

/*****************************************************************************
 函 数 名  : hmac_chan_reval_bandwidth_sta
 功能描述  : 评估是否需要进行带宽切换，如需要，则通知硬件进行带宽切换
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_reval_bandwidth_sta(mac_vap_stru *pst_mac_vap, oal_uint32 ul_change)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_chan_reval_bandwidth_sta::pst_mac_vap null.}");
        return;
    }

    /* 需要进行带宽切换 */
    if (HMAC_BW_CHANGE & ul_change)
    {
        hmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);
    }
}

/*****************************************************************************
 函 数 名  : hmac_chan_update_csw_info
 功能描述  : STA侧处理Beacon帧中的(Extended) Channel Switch Announcement IE
 输入参数  : pst_mac_vap : MAC VAP结构体指针，指向STA
             puc_payload : Beacon帧体(不包含帧头)
             us_frame_len: Beacon帧长(不包含帧头)
             us_offset   : Beacon帧中第一个IE相对于帧体起始处的偏移
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_update_csw_info(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len, oal_uint16 us_offset)
{
    oal_bool_enum_uint8   en_csa_ie_present;

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        return;
    }

    en_csa_ie_present = hmac_ie_check_csa_ie(pst_mac_vap, puc_payload, us_frame_len, us_offset);

    if (OAL_FALSE == en_csa_ie_present)
    {
        if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_for_ap)
        {
            pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = OAL_FALSE;

            hmac_chan_enable_machw_tx(pst_mac_vap);
        }
    }
}


/*****************************************************************************
 函 数 名  : hmac_chan_ctrl_machw_tx
 功能描述  : 控制硬件是否发送(数据帧、ACK、RTS)
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             uc_sub_type: 事件子类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_chan_ctrl_machw_tx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_sub_type)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ctrl_machw_tx::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    uc_sub_type,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ctrl_machw_tx::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_chan_disable_machw_tx
 功能描述  : 禁止硬件发送(数据帧、ACK、RTS)
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_disable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    hmac_chan_ctrl_machw_tx(pst_mac_vap, DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX);
}

/*****************************************************************************
 函 数 名  : hmac_chan_enable_machw_tx
 功能描述  : 恢复硬件发送(数据帧、ACK、RTS)
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_enable_machw_tx(mac_vap_stru *pst_mac_vap)
{
    hmac_chan_ctrl_machw_tx(pst_mac_vap, DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX);
}

/*****************************************************************************
 函 数 名  : hmac_chan_check_chan_avail
 功能描述  : 自动信道选择有效性检查
 输入参数  : en_band         : 频段(0: 2.4GHz; 1: 5GHz)
 输出参数  : puc_start_ch_idx: 需要扫描的第一条信道索引
             puc_end_ch_idx  : 需要扫描的最后一条信道索引
 返 回 值  : OAL_TRUE : 成功
             OAL_FALSE: 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_check_channnel_avaible(
                wlan_channel_band_enum_uint8    en_band,
                oal_uint8                      *puc_start_ch_idx,
                oal_uint8                      *puc_end_ch_idx)
{
    oal_int32    l_ch_idx;
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint32   ul_ret;

    /* 取低有效信道 */
    for (l_ch_idx = *puc_start_ch_idx; l_ch_idx < uc_num_supp_chan; l_ch_idx++)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, (oal_uint8)l_ch_idx);
        if (OAL_SUCC == ul_ret)
        {
            *puc_start_ch_idx = (oal_uint8)l_ch_idx;
            break;
        }
    }

    if (l_ch_idx == uc_num_supp_chan)
    {
        return OAL_FALSE;
    }

    /* 取高有效信道 */
    for (l_ch_idx = *puc_end_ch_idx; l_ch_idx >= 0; l_ch_idx--)
    {
        ul_ret = mac_is_channel_idx_valid(en_band, (oal_uint8)l_ch_idx);
        if (OAL_SUCC == ul_ret)
        {
            *puc_end_ch_idx = (oal_uint8)l_ch_idx;
            break;
        }
    }

    if (l_ch_idx < 0)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : hmac_chan_get_affected_channels
 功能描述  : 计算需要扫描的信道范围，扫描的范围是想要建立40MHz BSS的中心频点 +/- 5个信道，
             比如想要建立主信道为5，次信道为9的40MHz BSS，则将扫描信道2~12
 输入参数  : en_band               : 频段(0: 2.4GHz; 1: 5GHz)
             uc_user_pri_ch_idx    : 用户选择的信道索引
             en_user_pref_bandwidth: 用户选择的带宽模式
 输出参数  : puc_start_ch_idx: 需要扫描的第一条信道索引
             puc_end_ch_idx  : 需要扫描的最后一条信道索引
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hmac_chan_get_affected_channels(
                wlan_channel_band_enum_uint8         en_band,
                oal_uint8                            uc_user_pri_ch_idx,
                wlan_channel_bandwidth_enum_uint8    en_user_pref_bandwidth,
                oal_uint8                           *puc_start_ch_idx,
                oal_uint8                           *puc_end_ch_idx)
{
    oal_uint8    uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_uint8    uc_pll_div_idx = 0;   /* 中心频点 */

    /* 计算中心频点 */
    if (WLAN_BAND_WIDTH_40PLUS == en_user_pref_bandwidth)
    {
        uc_pll_div_idx = uc_user_pri_ch_idx + HMAC_CENTER_FREQ_2G_40M_OFFSET;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == en_user_pref_bandwidth)
    {
        uc_pll_div_idx = uc_user_pri_ch_idx - HMAC_CENTER_FREQ_2G_40M_OFFSET;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_chan_get_affected_channels::invalid bandwidth[%d].}", en_user_pref_bandwidth);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 计算需要扫描的信道索引下限 */
    *puc_start_ch_idx = (uc_pll_div_idx >= HMAC_AFFECTED_CH_IDX_OFFSET) ?
                    (uc_pll_div_idx - HMAC_AFFECTED_CH_IDX_OFFSET) : 0;

    /* 计算需要扫描的信道索引上限 */
    *puc_end_ch_idx   = (uc_num_supp_chan > uc_pll_div_idx + HMAC_AFFECTED_CH_IDX_OFFSET) ?
                    (uc_pll_div_idx + HMAC_AFFECTED_CH_IDX_OFFSET) : (uc_num_supp_chan - 1);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_is_scan_needed_for_multi_vap
 功能描述  : 多VAP情况下，在BSS启动前，判断是否需要进行信道扫描
 输入参数  : pst_mac_device  : MAC DEVICE结构体指针
             pst_mac_vap     : MAC VAP结构体指针(AP)
 输出参数  : 无
 返 回 值  : OAL_TRUE : 需要进行扫描
             OAL_FALSE: 不需要进行扫描
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_scan_needed_for_multi_vap(
                mac_device_stru   *pst_mac_device,
                mac_vap_stru      *pst_mac_vap)
{
    mac_vap_stru   *pst_vap;
    oal_uint8       uc_vap_idx;

    /* 第一个VAP(AP)启动前，可能需要进行信道扫描，直接返回 */
    if (1 == pst_mac_device->uc_vap_num)
    {
        return OAL_TRUE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN,
                           "{hmac_chan_is_scan_needed_for_multi_vap::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 跳过本VAP */
        if (pst_vap->uc_vap_id == pst_mac_vap->uc_vap_id)
        {
            continue;
        }

        if (MAC_VAP_STATE_INIT != pst_vap->en_vap_state)
        {
            return OAL_FALSE;
        }
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : hmac_chan_is_chan_scan_needed
 功能描述  : 判断在BSS启动前，是否需要进行信道扫描
 输入参数  : pst_mac_device  : MAC DEVICE结构体指针
             pst_mac_vap     : MAC VAP结构体指针(AP)
 输出参数  : puc_start_ch_idx: 需要扫描的第一条信道索引
             puc_end_ch_idx  : 需要扫描的最后一条信道索引
 返 回 值  : OAL_TRUE : 需要进行扫描
             OAL_FALSE: 不需要进行扫描
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_chan_is_chan_scan_needed(
                mac_device_stru   *pst_mac_device,
                mac_vap_stru      *pst_mac_vap,
                oal_uint8         *puc_start_ch_idx,
                oal_uint8         *puc_end_ch_idx)
{
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    oal_bool_enum_uint8             en_rslt;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
	oal_uint8                       uc_user_ch_idx;
    oal_uint32                      ul_ret;
#endif

#ifdef _PRE_WLAN_FEATURE_5G
    /* 5g频段没有20/40共存,如果开启，BSS启动时直接配置信道，不需要进行扫描，避免出错 */
    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (WLAN_BAND_5G == en_band))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_is_chan_scan_needed::20/40 MHz BSS only in 2.4G.}");
        return OAL_FALSE;
    }
#endif /* _PRE_WLAN_FEATURE_5G */

    /* 如果开启自动信道选择，则BSS启动时需要进行扫描 */
    if (OAL_TRUE == mac_device_is_auto_chan_sel_enabled(pst_mac_device))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_is_chan_scan_needed::Auto Channel Selection in progress.}");
        *puc_start_ch_idx = 0;
        *puc_end_ch_idx   = uc_num_supp_chan - 1;

        if (OAL_FALSE == hmac_chan_check_channnel_avaible(en_band, puc_start_ch_idx, puc_end_ch_idx))
        {
            return OAL_FALSE;
        }

        return OAL_TRUE;
    }

    en_rslt = hmac_chan_is_scan_needed_for_multi_vap(pst_mac_device, pst_mac_vap);
    if (OAL_TRUE != en_rslt)
    {
    #ifdef _PRE_WLAN_FEATURE_DBAC
        if (OAL_FALSE == mac_is_dbac_enabled(pst_mac_device))
        {
            pst_mac_vap->st_channel.uc_chan_number = pst_mac_device->uc_max_channel;
        }
    #else
        pst_mac_vap->st_channel.uc_chan_number = pst_mac_device->uc_max_channel;
    #endif

        return OAL_FALSE;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* 进行信道扫描，当且仅当: */
    /* (1) 20/40MHz共存使能 */
    /* (2) 准备建立40MHz BSS */
    /* (3) 2.4GHz */
    if ((OAL_TRUE     == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (OAL_TRUE     == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))        &&
        (WLAN_BAND_2G == en_band))
    {
        ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                        hmac_chan_get_user_pref_primary_ch(pst_mac_device), &uc_user_ch_idx) ;
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_is_chan_scan_needed::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
            return OAL_FALSE;
        }

        // TODO 对于80M/160M, 要重新调整影响范围
        /* 获取需要扫描的信道范围 */
        ul_ret = hmac_chan_get_affected_channels(en_band, uc_user_ch_idx, hmac_chan_get_user_pref_bandwidth(pst_mac_vap), puc_start_ch_idx, puc_end_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_is_chan_scan_needed::hmac_chan_get_affected_channels failed[%d].}", ul_ret);
            return OAL_FALSE;
        }

        if (OAL_FALSE == hmac_chan_check_channnel_avaible(en_band, puc_start_ch_idx, puc_end_ch_idx))
        {
            return OAL_FALSE;
        }

        return OAL_TRUE;
    }
#endif

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_start_bss_in_available_channel
 功能描述  : 在指定(可用)信道上启动BSS
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
oal_uint32  hmac_start_bss_in_available_channel(hmac_vap_stru *pst_hmac_vap)
{
    hmac_ap_start_rsp_stru          st_ap_start_rsp;
    oal_uint32                      ul_ret;

    /* 调用hmac_config_start_vap_event，启动BSS */
    ul_ret = hmac_config_start_vap_event(&(pst_hmac_vap->st_vap_base_info), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                        "{hmac_start_bss_in_available_channel::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 设置bssid */
    mac_vap_set_bssid(&pst_hmac_vap->st_vap_base_info, pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 入网优化，不同频段下的能力不一样 */
    if (WLAN_BAND_2G == pst_hmac_vap->st_vap_base_info.st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(&(pst_hmac_vap->st_vap_base_info), WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&(pst_hmac_vap->st_vap_base_info), OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(&(pst_hmac_vap->st_vap_base_info), WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&(pst_hmac_vap->st_vap_base_info), OAL_TRUE);
    }

    /* 设置AP侧状态机为 UP */
    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_UP);

    /* 将结果上报至sme */
    st_ap_start_rsp.en_result_code = HMAC_MGMT_SUCCESS;
    hmac_send_rsp_to_sme_ap(pst_hmac_vap, HMAC_AP_SME_START_RSP, (oal_uint8 *)&st_ap_start_rsp);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_start_bss
 功能描述  : 挑选一条信道(对)，并启动BSS
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_chan_start_bss(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru                     *pst_mac_device;
    mac_vap_stru                        *pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    oal_uint8                            uc_channel   = 0;
    wlan_channel_bandwidth_enum_uint8    en_bandwidth = WLAN_BAND_WIDTH_BUTT;
    oal_uint32                           ul_ret;

    /* 设置bssid */
    mac_vap_set_bssid(pst_mac_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 初始化AP速率集 */
    mac_vap_init_rates(pst_mac_vap);

    /* 获取mac device指针 */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_start_bss::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 挑选一条信道(对) */
    ul_ret = hmac_chan_select_channel_for_operation(pst_mac_vap, &uc_channel, &en_bandwidth);
    if (OAL_SUCC != ul_ret)
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_chan_start_bss::hmac_chan_select_channel_for_operation failed[%d].}", ul_ret);
        return OAL_FAIL;
    }
#ifdef _PRE_SUPPORT_ACS
        /* acs,使用acs选择的信道和带宽 */
    if (MAC_ACS_SW_INIT == mac_get_acs_switch(pst_mac_device) || MAC_ACS_SW_BOTH == mac_get_acs_switch(pst_mac_device))
    {
        hmac_device_stru   *pst_hmac_device = hmac_res_get_mac_dev(pst_mac_device->uc_device_id);
        if (!pst_hmac_device || 0 == pst_hmac_device->ast_best_channel[pst_mac_vap->st_channel.en_band].uc_chan_number)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                             "{hmac_chan_start_bss::init acs enabled, but best channel of BAND%d is 0", pst_mac_vap->st_channel.en_band);
        }
        else
        {
            uc_channel   = pst_hmac_device->ast_best_channel[pst_mac_vap->st_channel.en_band].uc_chan_number;
            en_bandwidth = pst_hmac_device->ast_best_channel[pst_mac_vap->st_channel.en_band].en_bandwidth;
        }
    }
    else
#endif
    {
        /* 固定信道并且使能初始信道20/40共存，使用之前的共存判断结果的信道和带宽 */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        if (mac_get_2040bss_switch(pst_mac_device))
        {
            uc_channel   = pst_mac_vap->st_channel.uc_chan_number;
            en_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
        }
#endif
    }

    ul_ret = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, uc_channel);
    if (OAL_SUCC != ul_ret)
    {
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_INIT);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                         "{hmac_chan_start_bss::mac_is_channel_num_valid failed[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                  "{hmac_chan_start_bss::AP: Starting network in Channel: %d, bandwidth: %d.}",
                  uc_channel, en_bandwidth);

    /* 更新带宽模式 */
    pst_mac_vap->st_channel.en_bandwidth = en_bandwidth;

    /* 设置信道号 */
#ifdef _PRE_WLAN_FEATURE_DBAC
    /* 同时更改多个VAP的信道，此时需要强制清除记录 */
    /* 若启动了DBAC，则按照原始流程进行 */
    if (!mac_is_dbac_enabled(pst_mac_device))
#endif
    {
        pst_mac_device->uc_max_channel = 0;
    }
    ul_ret = hmac_config_set_freq(pst_mac_vap, OAL_SIZEOF(oal_uint32), &uc_channel);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                        "{hmac_chan_start_bss::hmac_config_set_freq failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 设置带宽模式，直接抛事件到DMAC配置寄存器 */
    ul_ret = hmac_set_mode_event(pst_mac_vap);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_chan_start_bss::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }
/* : CAC passed here */
#if 0
#ifdef _PRE_WLAN_FEATURE_DFS
    /* 判断是否进行 Channel Availability Check 检测 */
    if (OAL_TRUE == hmac_dfs_need_for_cac(pst_mac_device, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number))
    {
        hmac_dfs_cac_start(pst_mac_device, pst_hmac_vap);

        return OAL_SUCC;
    }
#endif
#endif
    /* 否则，直接启动BSS */
    return hmac_start_bss_in_available_channel(pst_hmac_vap);
}
/*****************************************************************************
 函 数 名  : hmac_chan_ch_av_chk_timeout_fn
 功能描述  : BSS上电扫描超时函数
 输入参数  : p_arg: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_chan_ch_av_chk_timeout_fn(void *p_arg)
{
    mac_device_stru              *pst_mac_device;
    hmac_vap_stru                *pst_hmac_vap;
    mac_vap_stru                 *pst_mac_vap;
    mac_chnl_av_chk_enum_uint8    en_status;

    pst_mac_vap   = (mac_vap_stru *)p_arg;
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ch_av_chk_timeout_fn::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_ch_av_chk_timeout_fn::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_CH_SWITCH_STATUS_1 == pst_mac_vap->st_ch_switch_info.en_ch_switch_status)
    {
        return OAL_SUCC;
    }

    /* 继续进行信道扫描 */
    en_status = hmac_chan_do_channel_availability_check(pst_mac_device, pst_mac_vap, OAL_FALSE);

    /* 如果信道扫描已完成，则选择一条信道(对)并启动BSS */
    if (MAC_CHNL_AV_CHK_COMPLETE == en_status)
    {
        hmac_chan_start_bss(pst_hmac_vap);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_chan_do_channel_availability_check
 功能描述  : BSS启动时，对所选择的信道列表进行被动扫描(或者选择不进行扫描)
 输入参数  : pst_mac_device: MAC DEVICE结构体指针
             pst_mac_vap   : MAC VAP结构体指针(AP)
             en_first_time : 是否是第一次进入这个函数(后续定时器超时还会调用这个函数，
                             那时就置为OAL_FALSE)
 输出参数  : 无
 返 回 值  : MAC_CHNL_AV_CHK_NOT_REQ : 不需要进行信道扫描
             MAC_CHNL_AV_CHK_IN_PROG : 正在进行信道扫描
             MAC_CHNL_AV_CHK_COMPLETE: 信道扫描已完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月31日
    作    者   : 
    修改内容   : 新生成函数

******************************************************************************/
mac_chnl_av_chk_enum_uint8  hmac_chan_do_channel_availability_check(
                mac_device_stru       *pst_mac_device,
                mac_vap_stru          *pst_mac_vap,
                oal_bool_enum_uint8    en_first_time)
{
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    oal_uint8                       uc_num_supp_chan = mac_get_num_supp_channel(en_band);
    mac_ch_switch_info_stru        *pst_csi = &(pst_mac_vap->st_ch_switch_info);
    oal_uint8                       uc_channel = 0;
    oal_bool_enum_uint8             en_need_for_scan = OAL_FALSE;
    oal_bool_enum_uint8             en_scan_itr_over = OAL_FALSE;

    for(;;)
    {
        if (en_first_time)
        {
            /* 判断是否需要进行信道扫描 */
	     en_need_for_scan = hmac_chan_is_chan_scan_needed(pst_mac_device, pst_mac_vap, &(pst_csi->uc_start_chan_idx), &(pst_csi->uc_end_chan_idx));
            if (OAL_FALSE == en_need_for_scan)
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Channel scanning not needed.}");
		 return MAC_CHNL_AV_CHK_NOT_REQ;
            }
            else
            {
                OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Channel scanning from %d to %d.}",
                              pst_csi->uc_start_chan_idx, pst_csi->uc_end_chan_idx);
            }

            /* 初始化信道扫描索引，从第一条需要扫描的信道开始 */
            pst_mac_device->uc_ap_chan_idx = pst_csi->uc_start_chan_idx;

            /* 清信道扫描结果列表 */
            OAL_MEMZERO(pst_mac_device->st_ap_channel_list, OAL_SIZEOF(pst_mac_device->st_ap_channel_list));

            /* 清'40MHz不允许位' */
            pst_mac_device->en_40MHz_intol_bit_recd = OAL_FALSE;

            /* 当前信道下扫描到的BSS个数清零 */
            pst_mac_device->st_bss_id_list.us_num_networks = 0;
        }
        else
        {
            /* 保存当前信道扫描到的BSS个数 */
            pst_mac_device->st_ap_channel_list[pst_mac_device->uc_ap_chan_idx].us_num_networks =
                            pst_mac_device->st_bss_id_list.us_num_networks;

            /* 清零，为扫描下一条信道做准备 */
            pst_mac_device->st_bss_id_list.us_num_networks = 0;

            /* 扫到最后一条信道，扫描结束 */
            if (pst_mac_device->uc_ap_chan_idx == pst_csi->uc_end_chan_idx)
            {
                en_scan_itr_over = OAL_TRUE;
            }

            /* 本次扫描完成，要扫描的信道索引+1 */
            pst_mac_device->uc_ap_chan_idx++;

            if (pst_mac_device->uc_ap_chan_idx >= uc_num_supp_chan)
            {
                pst_mac_device->uc_ap_chan_idx = 0;
            }

            if (pst_mac_device->uc_ap_chan_idx == pst_csi->uc_start_chan_idx)
            {
                en_scan_itr_over = OAL_TRUE;
            }

            if (OAL_TRUE == en_scan_itr_over)
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                              "{hmac_chan_do_channel_availability_check::Scan over.}");
                break;
            }
        }

        mac_get_channel_num_from_idx(en_band, pst_mac_device->uc_ap_chan_idx, &uc_channel);

        if (OAL_TRUE == hmac_chan_scan_availability(pst_mac_device,
                        &pst_mac_device->st_ap_channel_list[pst_mac_device->uc_ap_chan_idx]))
        {
            /* 切换至当前信道 */
            OAM_INFO_LOG0(0, OAM_SF_2040, "hmac_chan_do_channel_availability_check");
            hmac_chan_sync(pst_mac_vap, uc_channel, WLAN_BAND_WIDTH_20M, OAL_TRUE);

            /* 设置信道扫描超时时间 */
            pst_mac_device->st_scan_params.us_scan_time = WLAN_DEFAULT_PASSIVE_SCAN_TIME;

            /* 启动定时器 */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_scan_timer,
                                   hmac_chan_ch_av_chk_timeout_fn,
                                   pst_mac_device->st_scan_params.us_scan_time,
                                   pst_mac_vap,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_mac_device->ul_core_id);
            return MAC_CHNL_AV_CHK_IN_PROG;
        }

        en_first_time = OAL_FALSE;
    }

    return MAC_CHNL_AV_CHK_COMPLETE;
}
/*****************************************************************************
 函 数 名  : hmac_chan_get_ext_chan_info
 功能描述  : 获取指定VAP主、次(扩展)信道信息
 输入参数  : pst_mac_vap  : MAC VAP指针
 输出参数  : pst_chan_info: 主、次(扩展)信道信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_chan_get_ext_chan_info(
                oal_uint8                            uc_pri20_channel_idx,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth,
                hmac_channel_list_stru              *pst_chan_info)
{
    switch (en_bandwidth)
    {
        case WLAN_BAND_WIDTH_20M:
            pst_chan_info->ul_channels = 1;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        case WLAN_BAND_WIDTH_40PLUS:
            pst_chan_info->ul_channels = 2;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            break;

        case WLAN_BAND_WIDTH_40MINUS:
            pst_chan_info->ul_channels = 2;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        case WLAN_BAND_WIDTH_80PLUSPLUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx + 2];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 3];
            break;

        case WLAN_BAND_WIDTH_80PLUSMINUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 2];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            break;

        case WLAN_BAND_WIDTH_80MINUSPLUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx + 1];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx + 2];
            break;

        case WLAN_BAND_WIDTH_80MINUSMINUS:
            pst_chan_info->ul_channels = 4;
            pst_chan_info->ast_channels[0] = g_ast_freq_map_5g[uc_pri20_channel_idx - 3];
            pst_chan_info->ast_channels[1] = g_ast_freq_map_5g[uc_pri20_channel_idx - 2];
            pst_chan_info->ast_channels[2] = g_ast_freq_map_5g[uc_pri20_channel_idx - 1];
            pst_chan_info->ast_channels[3] = g_ast_freq_map_5g[uc_pri20_channel_idx];
            break;

        default:
            pst_chan_info->ul_channels = 0;
            OAM_ERROR_LOG1(0, OAM_SF_DFS, "{hmac_chan_get_ext_chan_info::Invalid bandwidth %d.}", en_bandwidth);
            break;
    }
}

/*****************************************************************************
 函 数 名  : hmac_chan_restart_network_after_switch
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_chan_restart_network_after_switch(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru   *pst_event_mem;
    frw_event_stru       *pst_event;
    oal_uint32            ul_ret;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_chan_restart_network_after_switch}");

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_restart_network_after_switch::pst_event_mem null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK,
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
                       "{hmac_chan_restart_network_after_switch::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
oal_module_symbol(g_ast_freq_map_5g);
oal_module_symbol(g_ast_freq_map_2g);

/*****************************************************************************
 函 数 名  : hmac_chan_switch_to_new_chan_complete
 功能描述  : 处理信道/带宽切换完成事件
 输入参数  : frw_event_mem_stru *pst_event_mem
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_chan_switch_to_new_chan_complete(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru     *pst_event;
    mac_device_stru    *pst_mac_device;
    hmac_vap_stru      *pst_hmac_vap;
    mac_vap_stru       *pst_mac_vap;
    dmac_set_chan_stru *pst_set_chan;
    oal_uint32          ul_ret;
    oal_uint8           uc_idx;

    OAM_INFO_LOG0(0, OAM_SF_2040, "{hmac_chan_restart_network_after_switch}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
	pst_set_chan = (dmac_set_chan_stru *)pst_event->auc_event_data;
    OAM_INFO_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "hmac_chan_switch_to_new_chan_complete\r\n");

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_hmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    OAM_INFO_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "hmac_chan_switch_to_new_chan_complete");
    hmac_dump_chan(pst_mac_vap, (oal_uint8*)pst_set_chan);

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040, "{hmac_switch_to_new_chan_complete::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band,
                pst_set_chan->st_channel.uc_chan_number, &uc_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                "{hmac_switch_to_new_chan_complete::mac_get_channel_idx_from_num failed[%d].}", ul_ret);

        return OAL_FAIL;
    }

    pst_mac_vap->st_channel.uc_chan_number = pst_set_chan->st_channel.uc_chan_number;
    pst_mac_vap->st_channel.en_bandwidth   = pst_set_chan->st_channel.en_bandwidth;
    pst_mac_vap->st_channel.uc_idx         = uc_idx;


    //pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = pst_set_chan->st_ch_switch_info.en_waiting_for_ap;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = pst_set_chan->st_ch_switch_info.en_waiting_to_shift_channel;

    pst_mac_vap->st_ch_switch_info.en_ch_switch_status = pst_set_chan->st_ch_switch_info.en_ch_switch_status;
    pst_mac_vap->st_ch_switch_info.en_bw_switch_status =
                                pst_set_chan->st_ch_switch_info.en_bw_switch_status;

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* 带宽已成功切换到40M, 停止40M恢复定时器 */
    if ((pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M) &&
         (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode))
    {
        hmac_chan_stop_40M_recovery_timer(&pst_hmac_vap->st_vap_base_info);
    }
#endif

    if (OAL_FALSE == pst_set_chan->en_check_cac)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    if (OAL_TRUE == hmac_dfs_need_for_cac(pst_mac_device, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number))
    {
        hmac_dfs_cac_start(pst_mac_device, pst_hmac_vap);
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                "{hmac_chan_switch_to_new_chan_complete::[DFS]CAC START!}");

        return OAL_SUCC;
    }

    hmac_chan_restart_network_after_switch(&(pst_hmac_vap->st_vap_base_info));
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_dbac_status_notify
 功能描述  : 处理dbac status event
 输入参数  : frw_event_mem_stru *pst_event_mem
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_dbac_status_notify(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru     *pst_event;
    mac_device_stru    *pst_mac_device;
    oal_bool_enum_uint8 *pen_dbac_enable;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_dbac_status_notify::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
	pen_dbac_enable = (oal_bool_enum_uint8 *)pst_event->auc_event_data;
    OAM_INFO_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040,
        "hmac_dbac_status_notify::dbac switch to enable=%d", *pen_dbac_enable);

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_2040,
            "{hmac_dbac_status_notify::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device->en_dbac_running = *pen_dbac_enable;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_ie_proc_ch_switch_ie
 功能描述  : 处理(Extended) Channel Switch Announcement IE
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             puc_payload: 指向(Extended) Channel Switch Announcement IE的指针
             en_eid_type: Element ID
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年1月20日
    作    者   : 
    修改内容   : 上移HMAC

*****************************************************************************/
oal_uint32  hmac_ie_proc_ch_switch_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_eid_enum_uint8 en_eid_type)
{
    oal_uint8    uc_ch_sw_mode = 0;
    oal_uint8    uc_new_chan   = 0;
    oal_uint8    uc_sw_cnt     = 0;
    oal_uint32   ul_check      = OAL_FAIL;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_ie_proc_ch_switch_ie::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*************************************************************************/
    /*                    Channel Switch Announcement element                */
    /* --------------------------------------------------------------------- */
    /* |Element ID|Length |Channel switch Mode|New Channel| Ch switch count| */
    /* --------------------------------------------------------------------- */
    /* |1         |1      |1                  |1          |1               | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*                Extended Channel Switch Announcement element           */
    /* --------------------------------------------------------------------- */
    /* |Elem ID|Length|Ch Switch Mode|New Reg Class|New Ch| Ch switch count| */
    /* --------------------------------------------------------------------- */
    /* |1      |1     |1             |1            |1     |1               | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    if (MAC_EID_CHANSWITCHANN == en_eid_type)
    {
        /* Channel Switch Announcement element */
        uc_ch_sw_mode = puc_payload[MAC_IE_HDR_LEN];
        uc_new_chan   = puc_payload[MAC_IE_HDR_LEN + 1];
        uc_sw_cnt     = puc_payload[MAC_IE_HDR_LEN + 2];
    }
    else if (MAC_EID_EXTCHANSWITCHANN == en_eid_type)
    {
        /* Extended Channel Switch Announcement element */
        uc_ch_sw_mode = puc_payload[MAC_IE_HDR_LEN];
        /* Skip New Operating Class = puc_payload[MAC_IE_HDR_LEN + 1]; */
        uc_new_chan   = puc_payload[MAC_IE_HDR_LEN + 2];
        uc_sw_cnt     = puc_payload[MAC_IE_HDR_LEN + 3];
    }
    else
    {
        return OAL_FAIL;
    }

    /* 如果STA已经准备进行信道切换，则不做任何事情，直接返回 */
    if ((OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel))
    {
        if (uc_sw_cnt < pst_mac_vap->st_ch_switch_info.uc_ch_swt_cnt)
        {
            return OAL_SUCC;
        }
    }
    else
    {
        /* STA在信道切换完成前应该停止传输 */
        if (1 == uc_ch_sw_mode)
        {
            hmac_chan_disable_machw_tx(pst_mac_vap);
        }
    }

    pst_mac_vap->st_ch_switch_info.uc_new_channel = uc_new_chan;

    /* 检查当前管制域是否支持该信道，如果不支持，则直接返回 */
    ul_check = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_ch_switch_info.uc_new_channel);
    if (OAL_SUCC != ul_check)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_ie_proc_ch_switch_ie::mac_is_channel_num_valid failed[%d], uc_new_chan=%d.}",
                         ul_check, uc_new_chan);
        return ul_check;
    }

    /* STA在信道切换完成前应该停止传输 */
    if (1 == uc_ch_sw_mode)
    {
        hmac_chan_disable_machw_tx(pst_mac_vap);
    }

    pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt = uc_sw_cnt;
    pst_mac_vap->st_ch_switch_info.uc_ch_swt_cnt     = uc_sw_cnt;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = OAL_TRUE;

    /* 如果"信道切换计数"等于0，则立即切换信道 */
    if (0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)
    {
        pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero = OAL_TRUE;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_chan_sync(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number,
                   pst_mac_vap->st_channel.en_bandwidth, OAL_FALSE);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_ie_proc_wide_bandwidth_ie
 功能描述  : 处理Wide Bandwidth Channel Switch IE
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             puc_payload: 指向Wide Bandwidth Channel Switch IE的指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月24日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年1月20日
    作    者   : 
    修改内容   : 上移HMAC
*****************************************************************************/
oal_uint32  hmac_ie_proc_wide_bandwidth_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload)
{
    oal_uint8     uc_new_channel;
    oal_uint8     uc_channel_width;
    oal_uint8     uc_channel_center_freq_seg0;
    oal_uint32    ul_check;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        MAC_ERR_LOG2(0, "hmac_ie_proc_wide_bandwidth_ie, pst_mac_vap or puc_payload is null.", pst_mac_vap, puc_payload);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_ie_proc_wide_bandwidth_ie::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_new_channel = pst_mac_vap->st_ch_switch_info.uc_new_channel;

    /* 检查当前管制域是否支持该信道，如果不支持，则直接返回 */
    ul_check = mac_is_channel_num_valid(pst_mac_vap->st_channel.en_band, uc_new_channel);
    if (OAL_SUCC != ul_check)
    {
        MAC_WARNING_VAR(pst_mac_vap->uc_vap_id, "hmac_ie_proc_wide_bandwidth_ie, New Channel No.%d \
                        not support by Reg Domain.", uc_new_channel);
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_wide_bandwidth_ie::mac_is_channel_num_valid failed[%d], uc_new_chan=%d.}",
                         ul_check, uc_new_channel);
        return ul_check;
    }

    /* IE长度检查 MAC_WIDE_BW_CH_SWITCH_IE_LEN:3*/
    if (puc_payload[1] < MAC_WIDE_BW_CH_SWITCH_IE_LEN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ie_proc_wide_bandwidth_ie::invalid wide bw ch switch ie len[%d]}", puc_payload[1]);
        return OAL_FAIL;
    }

    uc_channel_width            = puc_payload[MAC_IE_HDR_LEN];
    uc_channel_center_freq_seg0 = puc_payload[MAC_IE_HDR_LEN + 1];

    if (uc_channel_width >= 1)
    {
        //TODO 1. 要同步 2. 对于80M切换要区分fpga/asic
        pst_mac_vap->st_ch_switch_info.en_new_bandwidth = mac_get_bandwith_from_center_freq_seg0(uc_new_channel, uc_channel_center_freq_seg0);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_ie_check_csa_ie
 功能描述  : 解析Beacon帧中是否存在(Extended) Channel Switch Announcement IE
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             puc_payload : Beacon帧体
             us_frame_len: Beacon帧体长度(不包括帧头)
             us_offset   : 第一个IE在Beacon帧体中的偏移
 输出参数  : 无
 返 回 值  : OAL_TRUE : Beacon帧中存在(Extended) Channel Switch Announcement IE
             OAL_FALSE: 其它
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年1月20日
    作    者   : 
    修改内容   : 上移HMAC
*****************************************************************************/
oal_bool_enum_uint8  hmac_ie_check_csa_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len, oal_uint16 us_offset)
{
    oal_uint16   us_index = us_offset;
    oal_uint16   us_ch_index = 0xFFFF;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        MAC_ERR_LOG(0, "hmac_ie_check_csa_ie, pst_mac_vap is null.");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_ie_check_csa_ie::pst_mac_vap null.}");

        return OAL_FALSE;
    }

    /*************************************************************************/
    /*                    Channel Switch Announcement element                */
    /* --------------------------------------------------------------------- */
    /* |Element ID|Length |Channel switch Mode|New Channel| Ch switch count| */
    /* --------------------------------------------------------------------- */
    /* |1         |1      |1                  |1          |1               | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*                Extended Channel Switch Announcement element           */
    /* --------------------------------------------------------------------- */
    /* |Elem ID|Length|Ch Switch Mode|New Reg Class|New Ch| Ch switch count| */
    /* --------------------------------------------------------------------- */
    /* |1      |1     |1             |1            |1     |1               | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    while(us_index < us_frame_len)
    {
        if(MAC_EID_CHANSWITCHANN == puc_payload[us_index])
        {
            us_ch_index = us_index;
        }
        else if (MAC_EID_EXTCHANSWITCHANN == puc_payload[us_index])
        {
            us_ch_index = us_index;
            break;
        }

        us_index += (MAC_IE_HDR_LEN + puc_payload[us_index + 1]);

    }

    if (0xFFFF != us_ch_index)
    {
        hmac_ie_proc_ch_switch_ie(pst_mac_vap, &puc_payload[us_ch_index], (mac_eid_enum_uint8)puc_payload[us_ch_index]);

        return OAL_TRUE;
    }

    return OAL_FALSE;
}

oal_module_symbol(hmac_ie_proc_ch_switch_ie);
oal_module_symbol(hmac_ie_check_csa_ie);
oal_module_symbol(hmac_ie_proc_wide_bandwidth_ie);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

