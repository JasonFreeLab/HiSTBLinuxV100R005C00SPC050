/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_scan.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2015年06月04日
  最近修改   :
  功能描述   : 扫描模块 hmac功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年06月04日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

#ifdef _PRE_SUPPORT_ACS

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_mgmt_sta.h"
#include "frw_ext_if.h"
#include "dmac_acs.h"
#include "hmac_acs.h"
#include "hmac_chan_mgmt.h"
#ifdef _PRE_WLAN_FEATURE_DFS
#include "hmac_dfs.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ACS_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_SUPPORT_ACS
#define ACS_DIV(a, b) ((b)==0 ? 0 : (a)/(b))
/*****************************************************************************
 功能描述  : 根据扫描运行结果，获取acs需要的简单的bss统计信息
 输入参数  : mac_scan_bss_stats_simple_stru   *pst_simple_bss_stats,
             hmac_scan_record_stru            *pst_scan_record
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_acs_get_simple_bss_stats_info(mac_scan_bss_stats_simple_stru  *pst_simple_bss_stats,
                                                       hmac_scan_record_stru           *pst_scan_record)
{
    hmac_bss_mgmt_stru              *pst_bss_mgmt;
    mac_bss_dscr_stru               *pst_bss_dscr;
    hmac_scanned_bss_info           *pst_scanned_bss;
    oal_dlist_head_stru             *pst_entry;
    oal_uint32                       ul_idx = 0;

    /* 根据扫描运行结果获取简单的bss统计信息 */

    /* 获取扫描结果的管理结构地址 */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    /* 获取锁 */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* 遍历扫描到的bss信息 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if ((OAL_PTR_NULL == pst_bss_dscr) || (OAL_PTR_NULL == pst_bss_dscr->auc_mgmt_buff))
        {
            continue;
        }

        pst_simple_bss_stats[ul_idx].c_rssi               = pst_bss_dscr->c_rssi;
        pst_simple_bss_stats[ul_idx].uc_channel_number    = pst_bss_dscr->st_channel.uc_chan_number;
        pst_simple_bss_stats[ul_idx].en_ht_capable        = pst_bss_dscr->en_ht_capable;
        pst_simple_bss_stats[ul_idx].en_vht_capable       = pst_bss_dscr->en_vht_capable;
        pst_simple_bss_stats[ul_idx].en_bw_cap            = pst_bss_dscr->en_bw_cap;
        pst_simple_bss_stats[ul_idx].en_channel_bandwidth = pst_bss_dscr->en_channel_bandwidth;

        ul_idx++;
    }

    /* 解除锁 */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return;
}

/*****************************************************************************
 函 数 名  : hmac_acs_get_simple_channel_stats_info
 功能描述  : 根据扫描运行结果，获取acs需要的简单信道统计信息
 输入参数  : mac_scan_bss_stats_simple_stru   *pst_simple_bss_stats,
             hmac_scan_record_stru            *pst_scan_record
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 由调用者保证入参的合法性
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_acs_get_simple_channel_stats_info(mac_scan_chan_stats_simple_stru  *pst_simple_channel_stats,
                                                           hmac_scan_record_stru            *pst_scan_record)
{
    oal_uint32      ul_idx = 0;
    oal_uint32      ul_chan_numbers = pst_scan_record->uc_chan_numbers;

    /* 获取信道测量结果 */
    for (ul_idx = 0; ul_idx < ul_chan_numbers; ul_idx++)
    {
        pst_simple_channel_stats[ul_idx].us_total_stats_time_ms = pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us / 1000;
        pst_simple_channel_stats[ul_idx].uc_bandwidth_mode      = pst_scan_record->ast_chan_results[ul_idx].uc_bandwidth_mode;
        pst_simple_channel_stats[ul_idx].uc_radar_detected      = pst_scan_record->ast_chan_results[ul_idx].uc_radar_detected;
        pst_simple_channel_stats[ul_idx].uc_radar_bw            = pst_scan_record->ast_chan_results[ul_idx].uc_radar_bw;
        pst_simple_channel_stats[ul_idx].uc_radar_type          = pst_scan_record->ast_chan_results[ul_idx].uc_radar_type;
        pst_simple_channel_stats[ul_idx].uc_radar_freq_offset   = pst_scan_record->ast_chan_results[ul_idx].uc_radar_freq_offset;
        pst_simple_channel_stats[ul_idx].uc_channel_number      = pst_scan_record->ast_chan_results[ul_idx].uc_channel_number;

        pst_simple_channel_stats[ul_idx].s_free_power_20M  = (oal_int8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].s_free_power_stats_20M,
                                                                       pst_scan_record->ast_chan_results[ul_idx].uc_free_power_cnt);
        pst_simple_channel_stats[ul_idx].s_free_power_40M  = (oal_int8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].s_free_power_stats_40M,
                                                                       pst_scan_record->ast_chan_results[ul_idx].uc_free_power_cnt);
        pst_simple_channel_stats[ul_idx].s_free_power_80M  = (oal_int8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].s_free_power_stats_80M,
                                                                       pst_scan_record->ast_chan_results[ul_idx].uc_free_power_cnt);

        pst_simple_channel_stats[ul_idx].uc_free_time_20M_rate  = (oal_uint8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].ul_total_free_time_20M_us << 8,
                                                                       pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us);
        pst_simple_channel_stats[ul_idx].uc_free_time_40M_rate  = (oal_uint8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].ul_total_free_time_40M_us << 8,
                                                                       pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us);
        pst_simple_channel_stats[ul_idx].uc_free_time_80M_rate  = (oal_uint8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].ul_total_free_time_80M_us << 8,
                                                                       pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us);
        pst_simple_channel_stats[ul_idx].uc_total_send_time_rate  = (oal_uint8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].ul_total_send_time_us << 8,
                                                                       pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us);
        pst_simple_channel_stats[ul_idx].uc_total_recv_time_rate  = (oal_uint8)ACS_DIV(pst_scan_record->ast_chan_results[ul_idx].ul_total_recv_time_us << 8,
                                                                   pst_scan_record->ast_chan_results[ul_idx].ul_total_stats_time_us);
    }

    return;
}

/*****************************************************************************
 函 数 名  : hmac_acs_setup_scan_result
 功能描述  : 构造扫描结果
 输入参数  : hmac_scan_runtime_record_stru *pst_scan_record
             oal_bool_enum_uint8            en_need_rank
 输出参数  : 无
 返 回 值  : frw_event_mem_stru *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru *hmac_acs_setup_scan_result(hmac_scan_record_stru   *pst_scan_record,
                                               oal_bool_enum_uint8      en_need_rank)
{
    mac_scan_event_stru                 *pst_scan_event;
    mac_scan_chan_stats_simple_stru     *pst_chan_results;
    mac_scan_bss_stats_simple_stru      *pst_bss_results;
    oal_uint8                           *puc_result;
    mac_acs_response_hdr_stru           *pst_msg_hdr;
    frw_event_mem_stru                  *pst_event_mem;
    frw_event_stru                      *pst_event;
    oal_uint32                           ul_size;
    oal_uint32                           ul_cmd_id = 0;
    oal_uint32                           ul_bss_num = pst_scan_record->st_bss_mgmt.ul_bss_num;
    oal_uint8                            uc_chip_id   = pst_scan_record->uc_chip_id;
    oal_uint8                            uc_device_id = pst_scan_record->uc_device_id;
    mac_device_stru                      *pst_mac_devce = OAL_PTR_NULL;

    pst_mac_devce = mac_res_get_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_mac_devce)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_acs_setup_scan_result:invalid device id=%d}", uc_device_id);
        return OAL_PTR_NULL;
    }

    ul_size = OAL_SIZEOF(mac_acs_response_hdr_stru)
            + OAL_SIZEOF(mac_scan_event_stru)
            + pst_scan_record->uc_chan_numbers * OAL_SIZEOF(mac_scan_chan_stats_simple_stru)
            + ul_bss_num * OAL_SIZEOF(mac_scan_bss_stats_simple_stru);

    /* 由于太大，payload中包含一个acs_response和一个指针 */
    /* 数据中会重复包含一个acs_response, 仅仅为编码方便 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_acs_response_hdr_stru)+ 4);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_acs_scan_cb:alloc failed, size=%d}", ul_size);
        return OAL_PTR_NULL;
    }

    puc_result = (oal_uint8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)ul_size, OAL_TRUE);
    if (OAL_PTR_NULL == puc_result)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_acs_scan_cb:alloc failed, size=%d}", ul_size);
        OAL_IO_PRINT("alloc failed in hmac_acs_setup_scan_result size=%d bss=%d ch=%d\n",
                ul_size, ul_bss_num, pst_scan_record->uc_chan_numbers);
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                     FRW_EVENT_TYPE_HOST_CTX,
                     HMAC_HOST_CTX_EVENT_SUB_TYPE_ACS_RESPONSE,
                     (oal_uint16)ul_size,
                     FRW_EVENT_PIPELINE_STAGE_0,
                     uc_chip_id,
                     uc_device_id,
                     0);
    /* payload中首先是一个response结构，用以判断CMD */
    pst_msg_hdr = (mac_acs_response_hdr_stru *)pst_event->auc_event_data;

    pst_msg_hdr->uc_cmd       = DMAC_ACS_CMD_DO_SCAN;
    pst_msg_hdr->uc_chip_id   = uc_chip_id;
    pst_msg_hdr->uc_device_id = uc_device_id;
    pst_msg_hdr->ul_len       = ul_size;
    pst_msg_hdr->ul_cmd_cnt   = ul_cmd_id;

    /* 而后是一个指针，指向结果包 */
    *(oal_uint32 *)(pst_msg_hdr + 1) = (oal_uint32)puc_result;

    /* 结果包首先是一个重复的response */
    oal_memcopy(puc_result, pst_msg_hdr, OAL_SIZEOF(mac_acs_response_hdr_stru));
    pst_scan_event    = (mac_scan_event_stru *)(puc_result + OAL_SIZEOF(mac_acs_response_hdr_stru));
    pst_chan_results  = (mac_scan_chan_stats_simple_stru *)(pst_scan_event + 1);
    pst_bss_results   = (mac_scan_bss_stats_simple_stru *)(pst_chan_results + pst_scan_record->uc_chan_numbers);

    oal_memset(pst_scan_event, 0, OAL_SIZEOF(mac_scan_event_stru));
    pst_scan_event->uc_chip_id   = uc_chip_id;
    pst_scan_event->uc_device_id = uc_device_id;
    pst_scan_event->uc_need_rank = en_need_rank;
#ifdef _PRE_WLAN_FEATURE_DFS
    pst_scan_event->uc_dfs_on    = mac_dfs_get_dfs_enable(pst_mac_devce);
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    pst_scan_event->uc_obss_on   = mac_get_2040bss_switch(pst_mac_devce);
#endif
    pst_scan_event->uc_nchans    = pst_scan_record->uc_chan_numbers;
    pst_scan_event->uc_nbss      = (oal_uint8)pst_scan_record->st_bss_mgmt.ul_bss_num;

    /* 获取acs需要的信道统计信息 */
    hmac_acs_get_simple_channel_stats_info(pst_chan_results, pst_scan_record);

    /* 获取acs需要的简单的bss统计信息，*/
    hmac_acs_get_simple_bss_stats_info(pst_bss_results, pst_scan_record);

    return pst_event_mem;
}
/*****************************************************************************
 函 数 名  : hmac_acs_got_init_rank
 功能描述  : 处理来自APP的初始信道选择结果
 输入参数  : mac_device_stru *pst_mac_dev
             mac_vap_stru *pst_mac_vap
             mac_acs_cmd_stru *pst_cmd
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_acs_got_init_rank(hmac_device_stru *pst_hmac_device, mac_vap_stru *pst_mac_vap, mac_acs_cmd_stru *pst_cmd)
{
    mac_channel_stru    *pst_ch = pst_hmac_device->ast_best_channel;
    oal_uint8            uc_chip_id;
    oal_uint8            uc_device_id;

    if (pst_hmac_device == OAL_PTR_NULL || pst_hmac_device->pst_device_base_info == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }

    uc_device_id   = (pst_cmd->auc_arg[1] >> 4) & 0x0F;
    uc_chip_id= (pst_cmd->auc_arg[1]) & 0xF;

    if (uc_chip_id != pst_hmac_device->pst_device_base_info->uc_chip_id
     || uc_device_id != pst_hmac_device->pst_device_base_info->uc_device_id)
    {
        return OAL_SUCC;
    }

    hmac_init_scan_cancel_timer(pst_hmac_device);

    pst_ch->en_band = pst_cmd->auc_data[0] & 0x0F;
    pst_ch->en_bandwidth = (pst_cmd->auc_data[0] >> 4) & 0x0F;
    pst_ch->uc_chan_number = pst_cmd->auc_data[1];
    if(OAL_SUCC != mac_get_channel_idx_from_num(pst_ch->en_band,
                                                pst_ch->uc_chan_number,
                                               &pst_ch->uc_idx))
    {
        OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{hmac_acs_got_init_rank::invalid 2G channel band=%d bw=%d ch=%d",
                         pst_ch->en_band, pst_ch->en_bandwidth, pst_ch->uc_chan_number);
        oal_memset(pst_ch, 0, OAL_SIZEOF(mac_channel_stru));
    }

    pst_ch++;
    pst_ch->en_band = pst_cmd->auc_data[2] & 0x0F;
    pst_ch->en_bandwidth = (pst_cmd->auc_data[2] >> 4) & 0x0F;
    pst_ch->uc_chan_number = pst_cmd->auc_data[3];
    if(OAL_SUCC != mac_get_channel_idx_from_num(pst_ch->en_band,
                                                pst_ch->uc_chan_number,
                                               &pst_ch->uc_idx))
    {
        OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{hmac_acs_got_init_rank::invalid 5G channel band=%d bw=%d ch=%d",
                         pst_ch->en_band, pst_ch->en_bandwidth, pst_ch->uc_chan_number);
        oal_memset(pst_ch, 0, OAL_SIZEOF(mac_channel_stru));
    }

    OAL_IO_PRINT("got init rank result [%d %d %d] -  [%d %d %d] init=%d for %d:%d\n",
            pst_ch[-1].en_band, pst_ch[-1].en_bandwidth, pst_ch[-1].uc_chan_number,
            pst_ch[0].en_band,  pst_ch[0].en_bandwidth,  pst_ch[0].uc_chan_number, pst_hmac_device->en_init_scan,
            uc_chip_id, uc_device_id);

    if (pst_hmac_device->en_init_scan == OAL_TRUE)
    {
        pst_hmac_device->en_init_scan = OAL_FALSE;
        pst_hmac_device->en_in_init_scan = OAL_FALSE;

        /* ACS信道选择中已经考虑OBSS共存性要求，只需执行CAC检测 */
#ifdef _PRE_WLAN_FEATURE_DFS
        if (mac_dfs_get_dfs_enable(pst_hmac_device->pst_device_base_info))
        {
            if(OAL_SUCC != hmac_dfs_init_scan_hook(&pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt, pst_hmac_device))
            {
                OAL_IO_PRINT("cac not need, start bss\n");
                hmac_start_all_bss_of_device(pst_hmac_device);
            }
            else
            {
                OAL_IO_PRINT("doing cac, wait to start\n");
            }
        }
        else
#endif
        {
            hmac_start_all_bss_of_device(pst_hmac_device);
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_acs_init_scan_hook
 功能描述  :
 输入参数  : hmac_scan_record_stru   *pst_scan_record
             hmac_device_stru        *pst_dev
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_acs_init_scan_hook(hmac_scan_record_stru   *pst_scan_record,
                                    hmac_device_stru        *pst_dev)
{
    frw_event_mem_stru              *pst_event_mem;
    pst_event_mem = hmac_acs_setup_scan_result(pst_scan_record, pst_dev->en_init_scan ? OAL_TRUE : OAL_FALSE);

    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_FAIL;
    }

    OAL_IO_PRINT("<<< rsp=5:scan report ch=%d bss=%d init=%d\n", pst_scan_record->uc_chan_numbers,
                    pst_scan_record->st_bss_mgmt.ul_bss_num, pst_dev->en_init_scan);

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_acs_idle_device
 功能描述  : 判断是否是空闲的device可用于重新ACS
 输入参数  : mac_device_stru *pst_mac_dev
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_acs_idle_device(mac_device_stru *pst_mac_dev)
{
    oal_uint8       uc_vap_idx;
    mac_vap_stru   *pst_mac_vap;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_dev->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_dev->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL != pst_mac_vap)
        {
            if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
            {
                return OAL_FALSE;
            }

            if (pst_mac_vap->us_user_nums)
            {
                return OAL_FALSE;
            }
        }
    }

    return OAL_TRUE;
}
/*****************************************************************************
 函 数 名  : hmac_acs_rescan_handler
 功能描述  : ACS运行时重新扫描对应钩子函数
 输入参数  : void *p_arg
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_acs_rescan_handler(void *p_arg)
{
    hmac_device_stru    *pst_dev = hmac_res_get_mac_dev((oal_uint32)p_arg);
    mac_vap_stru        *pst_mac_vap;

    oal_uint8            uc_vap_idx;

    if (!pst_dev || !pst_dev->pst_device_base_info || MAC_ACS_SW_NONE == mac_get_acs_switch(pst_dev->pst_device_base_info) || pst_dev->en_init_scan)
    {
        return OAL_SUCC;
    }

    if(!pst_dev->en_rescan_idle)
    {
        return OAL_SUCC;
    }

    // not support when dbac running
    if (mac_is_dbac_running(pst_dev->pst_device_base_info))
    {
        return OAL_SUCC;
    }

    if (!hmac_acs_idle_device(pst_dev->pst_device_base_info))
    {
        return OAL_SUCC;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_dev->pst_device_base_info->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_dev->pst_device_base_info->auc_vap_id[uc_vap_idx]);
        if ((OAL_PTR_NULL != pst_mac_vap)                      &&
            (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) &&
            (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state))
        {

            OAM_WARNING_LOG1(0, OAM_SF_ACS, "{rescan for dev=%d}", pst_dev->pst_device_base_info->uc_device_id);
            hmac_init_scan_try(pst_dev->pst_device_base_info, pst_mac_vap, MAC_TRY_INIT_SCAN_RESCAN);
            break;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_acs_init
 功能描述  : 初始化动态扫描定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_acs_init(oal_void)
{
    oal_uint32           ul_dev_id;
    hmac_device_stru    *pst_dev;

    for (ul_dev_id = 0; ul_dev_id < MAC_RES_MAX_DEV_NUM; ul_dev_id++)
    {
        pst_dev = hmac_res_get_mac_dev(ul_dev_id);
        if (pst_dev)
        {
            FRW_TIMER_CREATE_TIMER(&pst_dev->st_rescan_timer,
                                   hmac_acs_rescan_handler,
                                   HMAC_ACS_RECHECK_INTERVAL,
                                   (oal_void*)ul_dev_id,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_dev->pst_device_base_info->ul_core_id);
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_acs_init
 功能描述  : 销毁动态扫描定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_acs_exit(oal_void)
{
    oal_uint32           ul_dev_id;
    hmac_device_stru    *pst_dev;

    for (ul_dev_id = 0; ul_dev_id < MAC_RES_MAX_DEV_NUM; ul_dev_id++)
    {
        pst_dev = hmac_res_get_mac_dev(ul_dev_id);
        if (pst_dev && pst_dev->st_rescan_timer.en_is_enabled)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_dev->st_rescan_timer);
        }
    }

    return OAL_SUCC;
}

oal_module_symbol(hmac_acs_init_scan_hook);
oal_module_symbol(hmac_acs_got_init_rank);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

