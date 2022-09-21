/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_hcc_adapt.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月8日
  最近修改   :
  功能描述   : HMAC模块HCC层适配
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月8日
    作    者   : 侯寅
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_profiling.h"
#include "hmac_hcc_adapt.h"
#include "mac_resource.h"
#include "oal_hcc_host_if.h"
#include "frw_event_main.h"
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_HCC_ADAPT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OAL_STATIC oal_uint8  g_hcc_sched_stat[FRW_EVENT_TYPE_BUTT];
OAL_STATIC oal_uint8  g_hcc_flowctrl_stat[FRW_EVENT_TYPE_BUTT];
OAL_STATIC oal_uint32  g_hcc_sched_event_pkts[FRW_EVENT_TYPE_BUTT]={0};
OAL_STATIC oal_uint8  g_wlan_queue_to_dmac_queue[WLAN_NET_QUEUE_BUTT];

extern oal_uint32 g_ul_pm_wakeup_event;
oal_uint32  g_ul_print_wakeup_mgmt = OAL_FALSE;
extern oal_uint32 hmac_hcc_tx_netbuf(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len,
                                    oal_uint32 fc_type,
                                    oal_uint32 queue_id);
oal_uint32 hmac_hcc_tx_netbuf_auto(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len);
extern oal_uint32 hmac_hcc_tx_data(frw_event_mem_stru * pst_hcc_event_mem, oal_netbuf_stru *pst_netbuf);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
oal_void hmac_tx_net_queue_map_init(oal_void)
{
    oal_memset(g_wlan_queue_to_dmac_queue,DATA_LO_QUEUE,OAL_SIZEOF(g_wlan_queue_to_dmac_queue));
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    g_wlan_queue_to_dmac_queue[WLAN_HI_QUEUE] = DATA_HI_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_NORMAL_QUEUE] = DATA_LO_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_TCP_DATA_QUEUE] = DATA_TCP_DATA_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_TCP_ACK_QUEUE] = DATA_TCP_ACK_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_BK_QUEUE] = DATA_UDP_BK_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_BE_QUEUE] = DATA_UDP_BE_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_VI_QUEUE] = DATA_UDP_VI_QUEUE;
    g_wlan_queue_to_dmac_queue[WLAN_UDP_VO_QUEUE] = DATA_UDP_VO_QUEUE;


    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_HI_QUEUE,WLAN_HI_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_LO_QUEUE,WLAN_NORMAL_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_TCP_DATA_QUEUE,WLAN_TCP_DATA_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_TCP_ACK_QUEUE,WLAN_TCP_ACK_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_BK_QUEUE,WLAN_UDP_BK_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_BE_QUEUE,WLAN_UDP_BE_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_VI_QUEUE,WLAN_UDP_VI_QUEUE);
    hcc_tx_wlan_queue_map_set(hcc_get_default_handler(),DATA_UDP_VO_QUEUE,WLAN_UDP_VO_QUEUE);
#endif

}

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
oal_int32 hmac_tx_event_pkts_info_print(oal_void* data, char* buf, oal_int32 buf_len)
{
    int i;
    oal_int32 ret = 0;
    oal_uint64 total = 0;
    struct hcc_handler* hcc = hcc_get_default_handler();
    if(NULL == hcc)
        return ret;

    ret +=  snprintf(buf + ret , buf_len - ret,"tx_event_pkts_info_show\n");
    for(i = 0; i < FRW_EVENT_TYPE_BUTT; i++)
    {
        if(g_hcc_sched_event_pkts[i])
            ret +=  snprintf(buf + ret , buf_len - ret,"event:%d, pkts:%10u\n", i,g_hcc_sched_event_pkts[i]);
        total += g_hcc_sched_event_pkts[i];
    }

    if(total)
        ret +=  snprintf(buf + ret , buf_len - ret,"total:%llu\n",total);
    return ret;
}
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
OAL_STATIC DECLARE_WIFI_PANIC_STRU(hmac_panic_hcc_adapt,hmac_tx_event_pkts_info_print);
#endif

oal_void hmac_tx_sched_info_init(oal_void)
{
    oal_memset(g_hcc_sched_stat,DATA_LO_QUEUE,OAL_SIZEOF(g_hcc_sched_stat));

    /*set the event sched PRI, TBD*/
    g_hcc_sched_stat[FRW_EVENT_TYPE_HIGH_PRIO] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_CRX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_DRX] = DATA_LO_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_CTX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_HOST_SDT_REG] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_CRX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_DRX] = DATA_LO_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_CTX] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_WLAN_TX_COMP] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_TBTT] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_TIMEOUT] = DATA_HI_QUEUE;
    g_hcc_sched_stat[FRW_EVENT_TYPE_DMAC_MISC] = DATA_HI_QUEUE;

    oal_memset(g_hcc_flowctrl_stat,HCC_FC_NONE,OAL_SIZEOF(g_hcc_flowctrl_stat));
#if 0
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HIGH_PRIO] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_CRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_CTX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_SDT_REG] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_CRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_DRX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_CTX] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_TX_COMP] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_TBTT] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_TIMEOUT] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HMAC_MISC] = HCC_FC_NONE;
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_DMAC_MISC] = HCC_FC_NONE;
#endif
    /*来自HOST的事件，如果从Kernel Net过来选择网络层流控+丢包的方式，
    如果是Wlan To Wlan 的方式，直接丢包!*/
    g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_DROP|HCC_FC_NET;
    //g_hcc_flowctrl_stat[FRW_EVENT_TYPE_HOST_DRX] = HCC_FC_DROP;

    //g_hcc_flowctrl_stat[FRW_EVENT_TYPE_WLAN_DTX] = HCC_FC_NET;
}

OAL_STATIC OAL_INLINE oal_void hmac_hcc_adapt_extend_hdr_init(frw_event_mem_stru *pst_hcc_event_mem,oal_netbuf_stru *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr;
    frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hdr = (struct frw_hcc_extend_hdr*)OAL_NETBUF_DATA(pst_netbuf);
    pst_hdr->en_nest_type = pst_event_hdr->en_type;
    pst_hdr->uc_nest_sub_type = pst_event_hdr->uc_sub_type;
    pst_hdr->device_id = pst_event_hdr->uc_device_id;
    pst_hdr->chip_id = pst_event_hdr->uc_chip_id;
    pst_hdr->vap_id = pst_event_hdr->uc_vap_id;
}

oal_void get_simple_mac_tx_ctl(mac_tx_ctl_cut_stru  *pst_simple_mac_tx_ctl, mac_tx_ctl_stru  *pst_tx_ctrl)
{
    pst_simple_mac_tx_ctl->uc_alg_pktno = (oal_uint8)pst_tx_ctrl->ul_alg_pktno;
    pst_simple_mac_tx_ctl->bit_en_event_type  = pst_tx_ctrl->en_event_type;
    pst_simple_mac_tx_ctl->bit_frame_header_length = pst_tx_ctrl->uc_frame_header_length;
    pst_simple_mac_tx_ctl->bit_is_needretry = pst_tx_ctrl->bit_is_needretry;
    pst_simple_mac_tx_ctl->bit_is_vipframe  = pst_tx_ctrl->bit_is_vipframe;
    pst_simple_mac_tx_ctl->bit_mpdu_num = pst_tx_ctrl->uc_mpdu_num;
    pst_simple_mac_tx_ctl->bit_netbuf_num = pst_tx_ctrl->uc_netbuf_num;
    pst_simple_mac_tx_ctl->bit_retried_num = pst_tx_ctrl->uc_retried_num;
    pst_simple_mac_tx_ctl->bit_tx_user_idx = (oal_uint8)pst_tx_ctrl->us_tx_user_idx;
    pst_simple_mac_tx_ctl->bit_tx_vap_index = pst_tx_ctrl->uc_tx_vap_index;
    pst_simple_mac_tx_ctl->en_ismcast = pst_tx_ctrl->en_ismcast;
    pst_simple_mac_tx_ctl->en_is_eapol = pst_tx_ctrl->en_is_eapol;
    pst_simple_mac_tx_ctl->en_is_first_msdu = pst_tx_ctrl->uc_is_first_msdu;
    pst_simple_mac_tx_ctl->en_is_get_from_ps_queue = pst_tx_ctrl->en_is_get_from_ps_queue;
    pst_simple_mac_tx_ctl->en_is_probe_data = pst_tx_ctrl->en_is_probe_data;
    /*useless struct member*/
    //pst_simple_mac_tx_ctl->st_timestamp_us = pst_tx_ctrl->st_timestamp_us;
    pst_simple_mac_tx_ctl->us_mpdu_bytes = pst_tx_ctrl->us_mpdu_bytes;
    pst_simple_mac_tx_ctl->bit_mgmt_frame_id = pst_tx_ctrl->bit_mgmt_frame_id;
    pst_simple_mac_tx_ctl->bit_is_eapol_key_ptk = pst_tx_ctrl->bit_is_eapol_key_ptk;
    pst_simple_mac_tx_ctl->bit_need_rsp      = pst_tx_ctrl->bit_need_rsp;
    pst_simple_mac_tx_ctl->bit_ac            = pst_tx_ctrl->uc_ac;
    pst_simple_mac_tx_ctl->en_is_amsdu       = pst_tx_ctrl->en_is_amsdu;
    pst_simple_mac_tx_ctl->en_ack_policy     = pst_tx_ctrl->en_ack_policy;
    pst_simple_mac_tx_ctl->bit_tid           = (pst_tx_ctrl->uc_tid & 0x0F);
    /*  TBD 解决STA user idx等于0的问题，此处用bit_reserved4作为user idx的备份 */
    pst_simple_mac_tx_ctl->bit_tx_user_idx_bak = (oal_uint8)pst_tx_ctrl->us_tx_user_idx;
}

/*****************************************************************************
 函 数 名  : get_mac_rx_ctl
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void get_mac_rx_ctl(mac_rx_ctl_stru  *pst_mac_rx_ctl, mac_rx_ctl_cut_stru  *pst_mac_rx_cut_ctl)
{
    pst_mac_rx_ctl->bit_amsdu_enable    = pst_mac_rx_cut_ctl->bit_amsdu_enable;
    pst_mac_rx_ctl->bit_buff_nums       = pst_mac_rx_cut_ctl->bit_buff_nums;
    pst_mac_rx_ctl->us_da_user_idx      = pst_mac_rx_cut_ctl->bit_da_user_idx;
    pst_mac_rx_ctl->bit_is_first_buffer = pst_mac_rx_cut_ctl->bit_is_first_buffer;
    pst_mac_rx_ctl->bit_is_fragmented   = pst_mac_rx_cut_ctl->bit_is_fragmented;
    pst_mac_rx_ctl->uc_mac_header_len   = pst_mac_rx_cut_ctl->bit_mac_header_len;
    pst_mac_rx_ctl->us_ta_user_idx      = pst_mac_rx_cut_ctl->bit_ta_user_idx;
    pst_mac_rx_ctl->bit_vap_id          = pst_mac_rx_cut_ctl->bit_vap_id;
    pst_mac_rx_ctl->uc_msdu_in_buffer   = pst_mac_rx_cut_ctl->uc_msdu_in_buffer;
    pst_mac_rx_ctl->us_frame_len        = pst_mac_rx_cut_ctl->us_frame_len;
    pst_mac_rx_ctl->uc_mac_vap_id       = pst_mac_rx_cut_ctl->uc_mac_vap_id;
    pst_mac_rx_ctl->uc_channel_number   = pst_mac_rx_cut_ctl->uc_channel_number;
    pst_mac_rx_ctl->bit_is_beacon       = pst_mac_rx_cut_ctl->bit_is_beacon;
}

/*****************************************************************************
 函 数 名  : check_headroom_add_length
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 check_headroom_add_length(mac_tx_ctl_stru *pst_tx_ctrl, frw_event_type_enum_uint8  en_nest_type, oal_uint8  uc_nest_sub_type)
{
    oal_uint32 ul_headroom_add;

    if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
    {
        /*case 1: data from net, mac head is maintence in netbuff*/
         /*lint -e778*/
        ul_headroom_add = OAL_SIZEOF(mac_tx_ctl_cut_stru) - (MAC_80211_QOS_HTC_4ADDR_FRAME_LEN - MAX_MAC_HEAD_LEN);//结构体肯定大于4
         /*lint +e778*/
    }
    else if ((FRW_EVENT_TYPE_WLAN_CTX == en_nest_type) &&
            ((DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT == uc_nest_sub_type) || (DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION == uc_nest_sub_type)))
    {
        /*case 2: mgmt frame, mac header is maintence in payload part*/
        ul_headroom_add = OAL_SIZEOF(mac_tx_ctl_cut_stru)+(MAX_MAC_HEAD_LEN - MAC_80211_FRAME_LEN);
    }
    else
    {
        /*case 3: data from net, mac head not maintence in netbuff*/
        /*case 4: netbuff alloced in adapt layer */
        ul_headroom_add = MAX_MAC_HEAD_LEN + OAL_SIZEOF(mac_tx_ctl_cut_stru);
    }

    return ul_headroom_add;
}

/*****************************************************************************
 函 数 名  : hmac_adjust_netbuf_data
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_adjust_netbuf_data(oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctrl, frw_event_type_enum_uint8  en_nest_type, oal_uint8  uc_nest_sub_type)
{
    oal_uint8                       *puc_data_hdr;
    mac_tx_ctl_cut_stru             st_simple_mac_tx_ctl;

    /*在进入HCC之前，将CB字段和Mac头连续存放至payload之前*/
    puc_data_hdr      = OAL_NETBUF_DATA(pst_netbuf);

    oal_memset(&st_simple_mac_tx_ctl,0,OAL_SIZEOF(mac_tx_ctl_cut_stru));
    get_simple_mac_tx_ctl(&st_simple_mac_tx_ctl, pst_tx_ctrl);

    if ((FRW_EVENT_TYPE_WLAN_CTX == en_nest_type) &&
       ((DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT == uc_nest_sub_type) || (DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION == uc_nest_sub_type)))
    {

        /*case 1: mgmt frame, mac header is maintence in payload part*/
        oal_memcopy(puc_data_hdr, (oal_uint8 *)&st_simple_mac_tx_ctl, OAL_SIZEOF(mac_tx_ctl_cut_stru));
        /*copy mac hdr*/
        oal_memmove(puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru),
                    puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru)+(MAX_MAC_HEAD_LEN - MAC_80211_FRAME_LEN),
                    MAC_80211_FRAME_LEN);
    }
    else if (OAL_PTR_NULL != pst_tx_ctrl->pst_frame_header)
    {
        /*case 2: data from net, mac head not maintence in netbuff*/
        /*case 3: netbuff alloced in adapt layer */
        oal_memmove(puc_data_hdr + OAL_SIZEOF(mac_tx_ctl_cut_stru), (oal_uint8 *)pst_tx_ctrl->pst_frame_header, MAX_MAC_HEAD_LEN);
        oal_memcopy(puc_data_hdr, (oal_uint8 *)&st_simple_mac_tx_ctl, OAL_SIZEOF(mac_tx_ctl_cut_stru));

        /* 帧头和帧体不连续，帧头重新申请了事件内存，此处需要释放 */
        if (0 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            OAL_MEM_FREE((oal_uint8 *)pst_tx_ctrl->pst_frame_header, OAL_TRUE);
        }
    }
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_netbuf_auto
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_hcc_tx_netbuf_auto(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len)
{
    oal_uint32      fc_type,queue_id;
    frw_event_hdr_stru              *pst_event_hdr;
    frw_event_type_enum_uint8        en_type;
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);
    en_type                 = pst_event_hdr->en_type;

    if(OAL_WARN_ON(en_type >= FRW_EVENT_TYPE_BUTT))
    {
        oal_netbuf_free(pst_netbuf);
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_hcc_tx_netbuf_auto::FRW_EVENT_TYPE[%d] over limit!}",en_type);
        return OAL_FAIL;
    }

    queue_id = g_hcc_sched_stat[en_type];
    fc_type = g_hcc_flowctrl_stat[en_type];

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    /* 对于从以太网报文获取其队列号 */
    if (FRW_EVENT_TYPE_HOST_DRX == en_type)
    {
        queue_id = oal_skb_get_queue_mapping(pst_netbuf);
        if(OAL_WARN_ON(queue_id >= WLAN_NET_QUEUE_BUTT))
        {
            queue_id = DATA_LO_QUEUE;
        }
        else
        {
            queue_id = g_wlan_queue_to_dmac_queue[queue_id];
        }
    }
#endif
    return hmac_hcc_tx_netbuf(pst_hcc_event_mem,pst_netbuf,ul_hdr_len,fc_type,queue_id);
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_netbuf
 功能描述  : 发送普通netbuf,将netbuf->data开始的长度为ul_hdr_len的空间放入TCM
             正常核间通信建议调用此函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/4/10
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_hcc_tx_netbuf(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf,oal_uint32 ul_hdr_len,
                                    oal_uint32 fc_type,
                                    oal_uint32 queue_id)
{
    frw_event_hdr_stru             *pst_event_hdr = OAL_PTR_NULL;
    oal_int32                       ul_headroom_add = 0;
    oal_uint32                       ret = OAL_SUCC;

    DECLARE_HCC_TX_PARAM_INITIALIZER(st_hcc_transfer_param,
                                     HCC_ACTION_TYPE_WIFI,
                                     0,
                                     ul_hdr_len + OAL_SIZEOF(struct frw_hcc_extend_hdr),
                                     fc_type,
                                     queue_id);

    OAL_BUG_ON(NULL == pst_netbuf);

    if(OAL_UNLIKELY(oal_netbuf_headroom(pst_netbuf) < OAL_SIZEOF(struct frw_hcc_extend_hdr)))
    {
        ul_headroom_add =  (oal_int32)OAL_SIZEOF(struct frw_hcc_extend_hdr) - (oal_int32)oal_netbuf_headroom(pst_netbuf);
    }

    if(ul_headroom_add > 0)
    {
#ifdef _PRE_LWIP_ZERO_COPY_DEBUG
        OAM_ERROR_LOG0(0, 0, "[hmac_hcc_tx_netbuf] headroom not enough");
#endif
        oal_int32 ul_head_room = (oal_int32)oal_netbuf_headroom(pst_netbuf);
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_hcc_tx_netbuf expand head done![%d]}",ul_head_room);
        ret = (oal_uint32)oal_netbuf_expand_head(pst_netbuf, (oal_int32) ul_headroom_add, 0, GFP_ATOMIC);
        if(OAL_WARN_ON(OAL_SUCC != ret))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: alloc head room failed.}");
            oal_netbuf_free(pst_netbuf);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    }

    /*add frw hcc extend area*/
    oal_netbuf_push(pst_netbuf, OAL_SIZEOF(struct frw_hcc_extend_hdr));
    hmac_hcc_adapt_extend_hdr_init(pst_hcc_event_mem,pst_netbuf);

    /* 2015.08.12 START 用于同步事件打印，确认是否丢事件 */
    pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);

    if(HMAC_TO_DMAC_SYN_CFG == pst_event_hdr->uc_sub_type)
    {
        hmac_to_dmac_cfg_msg_stru  *pst_syn_msg = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_hcc_event_mem);
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
        if (WLAN_CFGID_SET_DEVICE_FREQ != pst_syn_msg->en_syn_id)
#endif
        {
            OAM_INFO_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{hmac_hcc_tx_netbuf::host send event type[%d],subtype[%d],cfgid[%d]}",
                       pst_event_hdr->en_type, pst_event_hdr->uc_sub_type, pst_syn_msg->en_syn_id);
        }
    }
    /* 2015.08.12 END*/

    //expand 14B后性能下降40%,待确认!
    //oal_netbuf_expand_head(pst_netbuf, 4, 0, GFP_ATOMIC);
#ifdef CONFIG_PRINTK
    ret = (oal_uint32)hcc_tx(hcc_get_default_handler(), pst_netbuf, &st_hcc_transfer_param);
    if(OAL_UNLIKELY(OAL_SUCC != ret))
    {
        /*hcc 关闭时下发了命令,报警需要清理*/
        if(OAL_WARN_ON(-OAL_EBUSY == ret))
        {
            OAL_IO_PRINT("[E]hmac_tx event[%u:%u] drop!\n", pst_event_hdr->en_type, pst_event_hdr->uc_sub_type);
            ret = OAL_SUCC;
            DECLARE_DFT_TRACE_KEY_INFO("hcc_is_busy",OAL_DFT_TRACE_OTHER);
        }

        if(-OAL_EIO == ret)
        {
            /*hcc exception, drop the pkts*/
            ret = OAL_SUCC;
        }

        oal_netbuf_free(pst_netbuf);
    }
    else
    {
        //frw_event_hdr_stru              *pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);
        if(OAL_LIKELY(pst_event_hdr->en_type < FRW_EVENT_TYPE_BUTT))
            g_hcc_sched_event_pkts[pst_event_hdr->en_type]++;
    }
    OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX);

    return ret;
#else
    /*UT Failed! Should remove this macro when DMT!*/
    return ret;
#endif
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_data
 功能描述  : hmac tx data adapt function,处理网络层过来的数据包
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/4/9
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_hcc_tx_data(frw_event_mem_stru * pst_hcc_event_mem, oal_netbuf_stru *pst_netbuf)
{
    frw_event_hdr_stru              *pst_event_hdr;

    frw_event_type_enum_uint8        en_type;
    oal_uint8                        uc_sub_type;

    mac_tx_ctl_stru                *pst_tx_ctrl;
    oal_uint32                      ul_headroom_add;

    oal_int32                       ret = OAL_SUCC;

    oal_uint                        ul_netbuf_old_addr;
    oal_uint                        ul_netbuf_new_addr;
    oal_uint                        ul_addr_offset;
    oal_uint8                       auc_macheader[MAC_80211_QOS_HTC_4ADDR_FRAME_LEN] = {0};

    /*提取嵌套的业务事件类型*/
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);

    en_type                 = pst_event_hdr->en_type;
    uc_sub_type             = pst_event_hdr->uc_sub_type;

    OAL_BUG_ON(NULL == pst_netbuf);

    pst_tx_ctrl  = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    if (OAL_WARN_ON(pst_tx_ctrl->en_use_4_addr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: use 4 address.}");
        oal_netbuf_free(pst_netbuf);
        return OAL_FAIL;
    }

    ul_headroom_add = check_headroom_add_length(pst_tx_ctrl, en_type, uc_sub_type);

    if(ul_headroom_add > oal_netbuf_headroom(pst_netbuf))
    {
#ifdef _PRE_LWIP_ZERO_COPY_DEBUG
        OAM_ERROR_LOG0(0, 0, "[hmac_hcc_tx_data] headroom not enough");
#endif
        if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            oal_memcopy(auc_macheader, (oal_uint8 *)pst_tx_ctrl->pst_frame_header, MAX_MAC_HEAD_LEN);
        }

        ret = oal_netbuf_expand_head(pst_netbuf,
                                    (oal_int32)ul_headroom_add - (oal_int32)oal_netbuf_headroom(pst_netbuf),
                                    0, GFP_ATOMIC);
        if(OAL_WARN_ON(OAL_SUCC != ret))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_tx_data:: alloc head room failed.}");
            oal_netbuf_free(pst_netbuf);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        if (1 == pst_tx_ctrl->bit_80211_mac_head_type)
        {
            oal_memcopy(OAL_NETBUF_DATA(pst_netbuf), auc_macheader, MAX_MAC_HEAD_LEN);
            pst_tx_ctrl->pst_frame_header = (mac_ieee80211_frame_stru *)OAL_NETBUF_DATA(pst_netbuf);
        }
    }

    /*修改netbuff的data指针和len*/
    oal_netbuf_push(pst_netbuf, ul_headroom_add);
    hmac_adjust_netbuf_data(pst_netbuf, pst_tx_ctrl,en_type, uc_sub_type);

    /* 使netbuf四字节对齐 */
    ul_netbuf_old_addr = (oal_uint)(OAL_NETBUF_DATA(pst_netbuf) + OAL_SIZEOF(mac_tx_ctl_cut_stru) + MAX_MAC_HEAD_LEN);
    ul_netbuf_new_addr = OAL_ROUND_DOWN(ul_netbuf_old_addr, 4);
    ul_addr_offset = ul_netbuf_old_addr - ul_netbuf_new_addr;

    /* 未对齐时在host侧做数据搬移，此处牺牲host，解放device */
    if (ul_addr_offset)
    {
        if(ul_addr_offset < oal_netbuf_headroom(pst_netbuf))
        {
            oal_memmove((oal_uint8*)OAL_NETBUF_DATA(pst_netbuf) - ul_addr_offset, (oal_uint8*)OAL_NETBUF_DATA(pst_netbuf), OAL_NETBUF_LEN(pst_netbuf));
            oal_netbuf_push(pst_netbuf, ul_addr_offset);
            oal_netbuf_trim(pst_netbuf, ul_addr_offset);
        }
    }

#ifdef _PRE_LWIP_ZERO_COPY_DEBUG
    OAM_WARNING_LOG4(0, 0, "[hmac_hcc_tx_data] need_rom = %d, head_room = %d, old/new_offset = %d, tailroom = %d", ul_headroom_add, ul_headroom, ul_addr_offset, oal_netbuf_tailroom(pst_netbuf));
#endif
    OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX_DATA);
    /*netbuf不管成功与否都由发送函数释放!*/
    hmac_hcc_tx_netbuf_auto(pst_hcc_event_mem,pst_netbuf,
                        OAL_SIZEOF(mac_tx_ctl_cut_stru) + MAX_MAC_HEAD_LEN);
    return OAL_SUCC;
}

oal_uint32 hmac_hcc_tx_netbuf_adapt(frw_event_mem_stru * pst_hcc_event_mem,
                                    oal_netbuf_stru *pst_netbuf)
{
    return hmac_hcc_tx_netbuf_auto(pst_hcc_event_mem,pst_netbuf,0);
}

oal_uint32 hmac_hcc_tx_event_buf_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                                         oal_uint8 *           pst_buf,
                                                         oal_uint32            payload_size)
{
    oal_netbuf_stru                 *pst_netbuf;
    /*申请netbuf存放事件payload*/
    pst_netbuf = hcc_netbuf_alloc(payload_size);
    if (OAL_WARN_ON(NULL == pst_netbuf))
    {
       OAL_IO_PRINT("hmac_hcc_tx_event_buf_to_netbuf alloc netbuf failed!\n");
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /*将结构体拷贝到netbuff数据区*/
    //OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
    oal_netbuf_put(pst_netbuf, payload_size);
    oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf)), (oal_uint8 *)pst_buf, payload_size);

    return hmac_hcc_tx_netbuf_adapt(pst_event_mem,pst_netbuf);
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_event_payload_to_netbuf
 功能描述  :

 输入参数  : frw_event_mem_stru *pst_event_mem，输入事件
             oal_uint32          payload_size   有效长度
 输出参数  : 无
 返 回 值  : OAL_SUCC， event转换成netbuf发送到对端成功，失败会在发送函数中释放。
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/4/9
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_hcc_tx_event_payload_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                                         oal_uint32            payload_size)
{
    oal_uint8          *pst_event_payload;

    if(OAL_WARN_ON(NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_hcc_tx_event_payload_to_netbuf:pst_event_mem null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*取业务事件信息*/
    pst_event_payload    = frw_get_event_payload(pst_event_mem);
    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem,pst_event_payload,payload_size);
}

/*****************************************************************************
 函 数 名  : hmac_hcc_rx_event_comm_adapt
 功能描述  : Hmac rx 业务事件适配函数，主要用于wlan数据适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_hcc_rx_event_comm_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    oal_uint8                       bit_mac_header_len;
    frw_event_hdr_stru              *pst_event_hdr;
    hcc_event_stru                  *pst_hcc_event_payload;

    mac_rx_ctl_stru                 *pst_rx_ctrl;
    oal_uint8                       *puc_hcc_extend_hdr;

    /*step1 提取嵌套的业务事件类型*/
    pst_event_hdr           = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru*)frw_get_event_payload(pst_hcc_event_mem);


    /*完成从51Mac rx ctl 到02 Mac rx ctl的拷贝,
    传到此处,pad_payload已经是0*/

    /* hcc protocol header
    |-------hcc total(64B)-----|-----------package mem--------------|
    |hcc hdr|pad hdr|hcc extend|pad_payload|--------payload---------|*/

    if(OAL_WARN_ON(NULL == pst_hcc_event_payload->pst_netbuf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_hcc_rx_event_comm_adapt:did't found netbuf!");
        return OAL_FAIL;
    }

    puc_hcc_extend_hdr  = OAL_NETBUF_DATA((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf);
    bit_mac_header_len = ((mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr)->bit_mac_header_len;
    if (bit_mac_header_len)
    {
        if(bit_mac_header_len > MAX_MAC_HEAD_LEN)
        {
            OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "invaild mac header len:%d,main:%d,sub:%d",
                            bit_mac_header_len,pst_event_hdr->en_type, pst_event_hdr->uc_sub_type);
            oal_print_hex_dump(puc_hcc_extend_hdr, (oal_int32)OAL_NETBUF_LEN((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf), 32, "invaild mac header len");
            return OAL_FAIL;
        }

        pst_rx_ctrl  = (mac_rx_ctl_stru *)OAL_NETBUF_CB((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf);
        get_mac_rx_ctl(pst_rx_ctrl, (mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr) ;

        /*需要修改pst_rx_ctrl中所有指针*/
        pst_rx_ctrl->pul_mac_hdr_start_addr = (oal_uint32 *)(puc_hcc_extend_hdr + OAL_MAX_CB_LEN + MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len);

        /* 将mac header的内容向高地址偏移8个字节拷贝，使得mac header和payload的内容连续 */
        oal_memmove((oal_uint8 *)pst_rx_ctrl->pul_mac_hdr_start_addr,
                    (oal_uint8 *)((oal_uint8 *)pst_rx_ctrl->pul_mac_hdr_start_addr - (MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len)),
                    pst_rx_ctrl->uc_mac_header_len);

        /*将netbuff data指针移到payload位置*/
        oal_netbuf_pull(pst_hcc_event_payload->pst_netbuf, OAL_MAX_CB_LEN + (MAX_MAC_HEAD_LEN - pst_rx_ctrl->uc_mac_header_len));

        //OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_rx_event_handler::cut short}");
    }
    else
    {
        oal_netbuf_pull(pst_hcc_event_payload->pst_netbuf, (OAL_MAX_CB_LEN + MAX_MAC_HEAD_LEN));

        //OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_hcc_rx_event_handler::cut short}");
    }


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_hcc_expand_rx_adpat_event
 功能描述  : hmac event 扩展函数，复制一个rx event事件,事件申请失败则释放原事件中的netbuf!
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_expand_rx_adpat_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 event_size)
{
    frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    frw_event_type_enum_uint8       en_type;
    oal_uint8                       uc_sub_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_vap_id;
    frw_event_mem_stru             *pst_event_mem;              /* 业务事件相关信息 */

   /* 提取HCC事件信息 */
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    en_type                 = pst_hcc_event_hdr->en_type;
    uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /* 申请业务事件 */
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)event_size);
    if (OAL_WARN_ON(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_WARNING_LOG1(0,OAM_SF_ANY,"hmac_hcc_rx_netbuf_convert_to_event  alloc event failed,event len:%d",event_size);
        /* 释放hcc事件中申请的netbuf内存 */
        oal_netbuf_free(pst_hcc_netbuf);
        return OAL_PTR_NULL;
    }

    /* 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       (oal_uint16)event_size,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    return pst_event_mem;
}

/*****************************************************************************
 函 数 名  : hmac_hcc_rx_netbuf_convert_to_event
 功能描述  : Dmac模块将netbuf中的事件内容还原到事件内存中
 输入参数  : frw_event_mem_stru *pst_hcc_event_mem
             oal_uint32 revert_size
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_rx_netbuf_convert_to_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 revert_size)
{
    //frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    //frw_event_type_enum_uint8       en_type;
    //oal_uint8                       uc_sub_type;
    frw_event_mem_stru             *pst_event_mem;              /* 业务事件相关信息 */

    if(OAL_WARN_ON(NULL == pst_hcc_event_mem))
    {
        return NULL;
    }

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    //pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    //en_type                 = pst_hcc_event_hdr->en_type;
    //uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;

    if(OAL_WARN_ON(NULL == pst_hcc_netbuf))
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"Fatal Error,payload did't contain any netbuf!");
        return OAL_PTR_NULL;
    }

    if(revert_size > OAL_NETBUF_LEN(pst_hcc_netbuf))
    {
        revert_size = OAL_NETBUF_LEN(pst_hcc_netbuf);
    }

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,revert_size);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_PTR_NULL;
    }

    if(revert_size)
        oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem),
                (oal_uint8 *)OAL_NETBUF_DATA(pst_hcc_netbuf), revert_size);

    /* 释放hcc事件中申请的netbuf内存 */
    oal_netbuf_free(pst_hcc_netbuf);

    return pst_event_mem;
}

/*****************************************************************************
 函 数 名  : hmac_hcc_rx_convert_netbuf_to_event_default
 功能描述  : Dmac模块将netbuf中的事件内容还原到事件内存中,
             netbuf 的申请的 event长度一致!
 输入参数  : frw_event_mem_stru *pst_hcc_event_mem

 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru *pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    if(OAL_WARN_ON(OAL_PTR_NULL == pst_hcc_event_mem))
    {
        return OAL_PTR_NULL;
    }

    pst_hcc_event_payload = (hcc_event_stru*)frw_get_event_payload(pst_hcc_event_mem);
    return hmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,pst_hcc_event_payload->ul_buf_len);
}

/*****************************************************************************
 函 数 名  : hmac_common_rx_adapt
 功能描述  : hmac处理不懈怠payload事件的公共接收适配接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_hcc_test_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    hcc_event_stru                  *pst_hcc_rx_event;

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*填业务事件信息*/
    pst_hcc_rx_event                 = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_hcc_rx_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_rx_event->ul_buf_len     = (oal_uint32)OAL_NETBUF_LEN((oal_netbuf_stru*)pst_hcc_event_payload->pst_netbuf);

    return pst_event_mem;
}

frw_event_mem_stru * hmac_rx_convert_netbuf_to_netbuf_default(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;

    dmac_tx_event_stru              *pst_ctx_event;

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_tx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    pst_ctx_event               = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);

    pst_ctx_event->pst_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_ctx_event->us_frame_len = (oal_uint16)OAL_NETBUF_LEN((oal_netbuf_stru*)pst_hcc_event_payload->pst_netbuf);

    OAM_INFO_LOG2(0, OAM_SF_ANY, "{hmac_rx_convert_netbuf_to_netbuf_default::netbuf = %p, frame len = %d.}",
                  pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len);

    return pst_event_mem;
}

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_sta_rx_adapt
 功能描述  : rx_process_data_sta接收适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_rx_process_data_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    dmac_wlan_drx_event_stru        *pst_wlan_rx_event;

    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_DATA_ADAPT);

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_wlan_drx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*填业务事件信息*/
    pst_wlan_rx_event                 = (dmac_wlan_drx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_wlan_rx_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_wlan_rx_event->us_netbuf_num  = 1;//目前不支持通过SDIO后组链，默认都是单帧

    return pst_event_mem;
}

frw_event_mem_stru *  hmac_rx_process_mgmt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    dmac_wlan_crx_event_stru        *pst_crx_event;

    /*取HCC事件信息*/
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*filter the extend buf*/
    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_wlan_crx_event_stru));
    if (NULL == pst_event_mem)
    {
        return NULL;
    }

    /*填业务事件信息*/
    pst_crx_event                     = (dmac_wlan_crx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_crx_event->pst_netbuf         = pst_hcc_event_payload->pst_netbuf;

    return pst_event_mem;

}

#ifdef _PRE_WLAN_FEATRUE_FLOWCTL

/*****************************************************************************
 函 数 名  : hmac_alg_flowctl_backp_rx_adapt
 功能描述  : hmac反压函数适配函数
 输入参数  : frw_event_mem_stru *
 输出参数  : 无
 返 回 值  : frw_event_mem_stru*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月07日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru* hmac_alg_flowctl_backp_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    frw_event_stru                  *pst_hcc_event;
    hcc_event_stru                  *pst_hcc_event_payload;
    frw_event_hdr_stru              *pst_hcc_event_hdr;

    oal_uint8                        uc_chip_id;
    oal_uint8                        uc_device_id;
    oal_uint8                        uc_vap_id;

    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;

    if (OAL_PTR_NULL == pst_hcc_event_mem)
    {
        return OAL_PTR_NULL;
    }

    /*step1 取HCC事件头*/
    pst_hcc_event           = (frw_event_stru *)pst_hcc_event_mem->puc_data;
    pst_hcc_event_hdr       = &(pst_hcc_event->st_event_hdr);
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /*step2 取HCC事件信息*/
    pst_hcc_event_payload   = (hcc_event_stru *)pst_hcc_event->auc_event_data;


    /*step3 申请业务事件*/
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)pst_hcc_event_payload->ul_buf_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        oal_netbuf_free(pst_hcc_event_payload->pst_netbuf);
        return OAL_PTR_NULL;
    }

    pst_event =  (frw_event_stru *)pst_event_mem->puc_data;

    /*step4 填业务事件头*/
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                   pst_hcc_event_payload->en_nest_type,
                   pst_hcc_event_payload->uc_nest_sub_type,
                   (oal_uint16)pst_hcc_event_payload->ul_buf_len,
                   FRW_EVENT_PIPELINE_STAGE_1,
                   uc_chip_id,
                   uc_device_id,
                   uc_vap_id);

    /*step5 填HCC事件信息*/
    oal_memcopy(pst_event->auc_event_data, (oal_uint8 *)(OAL_NETBUF_DATA((oal_netbuf_stru *)pst_hcc_event_payload->pst_netbuf)), pst_hcc_event_payload->ul_buf_len);

    oal_netbuf_free(pst_hcc_event_payload->pst_netbuf);

    return pst_event_mem;
}


#endif

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_sta_rx_adapt
 功能描述  : rx_process_data_sta接收适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru * hmac_cali2hmac_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;

    frw_event_mem_stru              *pst_event_mem;
    hal_cali_hal2hmac_event_stru    *pst_cali_save_event;

    //OAL_IO_PRINT("hmac_cali2hmac_misc_event_rx_adapt start\r\n");

    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_DATA_ADAPT);

    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    hmac_hcc_rx_event_comm_adapt(pst_hcc_event_mem);

    pst_event_mem = hmac_hcc_expand_rx_adpat_event(pst_hcc_event_mem,OAL_SIZEOF(hal_cali_hal2hmac_event_stru));
    if (NULL == pst_event_mem)
    {
        OAL_IO_PRINT("cali_hmac_rx_adapt_fail\r\n");
        return NULL;
    }

    /*填业务事件信息*/
    pst_cali_save_event                 = (hal_cali_hal2hmac_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_cali_save_event->pst_netbuf     = pst_hcc_event_payload->pst_netbuf;
    pst_cali_save_event->us_netbuf_num  = 1;//目前不支持通过SDIO后组链，默认都是单帧

    return pst_event_mem;
}

/*****************************************************************************
 函 数 名  : hmac_proc_add_user_tx_adapt
 功能描述  : add_user模块发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_proc_add_user_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_add_user_stru));
}


/*****************************************************************************
 函 数 名  : hmac_proc_del_user_tx_adapt
 功能描述  : del_user模块发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32 hmac_proc_del_user_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_del_user_stru));
}

/*****************************************************************************
 函 数 名  : hmac_proc_config_syn_tx_adapt
 功能描述  : config_syn模块发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/4/9
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e413*/
oal_uint32 hmac_proc_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    hmac_to_dmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_syn_cfg_payload    = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem,
                                              (pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body)));
}
/*lint +e413*/


/*****************************************************************************
 函 数 名  : hmac_proc_config_syn_alg_tx_adapt
 功能描述  : config_alg_syn模块发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e413*/
oal_uint32 hmac_proc_config_syn_alg_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    hmac_to_dmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_syn_cfg_payload    = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem,
                                              (pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body)));
}
/*lint +e413*/

/*****************************************************************************
 函 数 名  : hmac_proc_tx_host_tx_adapt
 功能描述  : tx_host_event发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改

*****************************************************************************/

oal_uint32 hmac_proc_tx_host_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_netbuf_stru                 *pst_current_netbuf;
    oal_netbuf_stru                 *pst_current_netbuf_tmp = NULL;
    dmac_tx_event_stru              *pst_dmac_tx_event_payload;

    /*取业务事件信息*/
    pst_dmac_tx_event_payload = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_current_netbuf        = pst_dmac_tx_event_payload->pst_netbuf;

    while(OAL_PTR_NULL != pst_current_netbuf)
    {
        /*必须在netbuf抛出之前指向下一个netbuf，防止frw_event_dispatch_event 中重置 netbuf->next */
        pst_current_netbuf_tmp = pst_current_netbuf;
        pst_current_netbuf = OAL_NETBUF_NEXT(pst_current_netbuf);

        /*netbuf 失败由被调函数释放!*/
        OAL_MIPS_TX_STATISTIC(HOST_PROFILING_FUNC_HCC_TX_ADAPT);
        hmac_hcc_tx_data(pst_event_mem, pst_current_netbuf_tmp);

    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_proc_mgmt_ctx_tx_adapt
 功能描述  : mgmt_ctx发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32 hmac_proc_mgmt_ctx_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_proc_tx_host_tx_adapt(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_proc_tx_process_action_event_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_proc_tx_process_action_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_proc_tx_host_tx_adapt(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_proc_set_edca_param_tx_adapt
 功能描述  : set_edca_param发送适配
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月7日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月29日
    作    者   : 
    修改内容   : 修改edca适配传递所传参数
*****************************************************************************/
oal_uint32 hmac_proc_set_edca_param_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));
}

/*****************************************************************************
 函 数 名  : hmac_scan_proc_scan_req_event_tx_adapt
 功能描述  : 通过SDIO下发扫描配置前的适配函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_scan_proc_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    mac_scan_req_stru          *pst_h2d_scan_req_params;        /* 下发的扫描参数 */

	if(OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
	{
	    return OAL_ERR_CODE_PTR_NULL;
	}

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_scan_proc_scan_req_event_tx_adapt:: scan req, enter into tx adapt.}");
    pst_h2d_scan_req_params = (mac_scan_req_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)pst_h2d_scan_req_params, OAL_SIZEOF(mac_scan_req_stru));
}
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
oal_uint32   hmac_dpd_data_processed_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_tx_event_stru          *pst_dmac_tx_event;

    if(OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: dpd data, enter into tx adapt.}");
    pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)OAL_NETBUF_DATA(pst_dmac_tx_event->pst_netbuf), pst_dmac_tx_event->us_frame_len);
}

#endif

oal_uint32   hmac_send_cali_data_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_tx_event_stru          *pst_dmac_tx_event;

    if(OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    //OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{hmac_dpd_data_processed_event_tx_adapt:: dpd data, enter into tx adapt.}");
    pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    //OAL_IO_PRINT("hmac_send_cali_data_tx_adapt : pst_dmac_tx_event->us_frame_len %d\r\n", pst_dmac_tx_event->us_frame_len);
    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8*)OAL_NETBUF_DATA(pst_dmac_tx_event->pst_netbuf), pst_dmac_tx_event->us_frame_len);
}

/*****************************************************************************
 函 数 名  : hmac_scan_proc_sched_scan_req_event_tx_adapt
 功能描述  : 通过SDIO下发PNO调度扫描配置前的适配函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_scan_proc_sched_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    mac_pno_scan_stru   *pst_h2d_pno_scan_req_params;     /* 下发PNO调度扫描请求 */

	if(OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
	{
	    return OAL_ERR_CODE_PTR_NULL;
	}

    pst_h2d_pno_scan_req_params = (mac_pno_scan_stru *)(*(oal_uint *)frw_get_event_payload(pst_event_mem));

    return hmac_hcc_tx_event_buf_to_netbuf(pst_event_mem, (oal_uint8 *)pst_h2d_pno_scan_req_params, OAL_SIZEOF(mac_pno_scan_stru));
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_update_user_qos_table_tx_adapt
 功能描述  : 通过SDIO下发更新关联user配置前的适配函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改

*****************************************************************************/
oal_uint32 hmac_mgmt_update_user_qos_table_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));
}

/*****************************************************************************
 函 数 名  : hmac_join_set_reg_event_tx_adapt
 功能描述  : 通过SDIO下发join配置前得适配函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改

*****************************************************************************/
oal_uint32 hmac_proc_join_set_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_proc_join_set_reg_event_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
}


/*****************************************************************************
 函 数 名  : hmac_join_set_dtim_reg_event_tx_adapt
 功能描述  : 通过SDIO下发配置dtim寄存器前的发送适配函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改

*****************************************************************************/
oal_uint32 hmac_proc_join_set_dtim_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_proc_join_set_dtim_reg_event_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_convert_event_to_netbuf_uint32
 功能描述  : hmac 将event 转换为 netbuf,在dmac 将netbuf还原为event,event的payload长度为4B
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改
  3.日    期   : 2016年1月23日
    作    者   : 
    修改内容   : 核间通信函数精简

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint32(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint32));
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_convert_event_to_netbuf_uint16
 功能描述  : hmac 将event 转换为 netbuf,在dmac 将netbuf还原为event,event的payload长度为2B
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月23日
    作    者   : 
    修改内容   : 核间通信函数精简

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint16));
}

/*****************************************************************************
 函 数 名  : hmac_hcc_tx_convert_event_to_netbuf_uint8
 功能描述  : hmac 将event 转换为 netbuf,在dmac 将netbuf还原为event,event的payload长度为1B
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月23日
    作    者   : 
    修改内容   : 核间通信函数精简

*****************************************************************************/
oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint8(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint8));
}

/*****************************************************************************
 函 数 名  : hmac_user_add_notify_alg_tx_adapt
 功能描述  : 通过SDIO下发数据，通知dmac挂算法钩子函数
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : 
    修改内容   : 核间通信函数整改

*****************************************************************************/
oal_uint32 hmac_user_add_notify_alg_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_user_add_notify_alg_tx_adapt::tx adapt.}");
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_add_user_stru));
}

/*****************************************************************************
 函 数 名  : hmac_proc_rx_process_sync_event_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_proc_rx_process_sync_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_ctx_action_event_stru));
}

oal_uint32 hmac_chan_select_channel_mac_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_set_chan_stru));
}

/*****************************************************************************
 函 数 名  : hmac_chan_initiate_switch_to_new_channel_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_chan_initiate_switch_to_new_channel_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(dmac_set_ch_switch_info_stru));
}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 函 数 名  : hmac_edca_opt_stat_event_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_edca_opt_stat_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return hmac_hcc_tx_event_payload_to_netbuf(pst_event_mem, OAL_SIZEOF(oal_uint8) * 16);
}

#endif

oal_int32 hmac_rx_extend_hdr_vaild_check(struct frw_hcc_extend_hdr* pst_extend_hdr)
{
    if(OAL_UNLIKELY(pst_extend_hdr->en_nest_type >= FRW_EVENT_TYPE_BUTT))
    {
        return OAL_FALSE;
    }
#if 0
    if(OAL_UNLIKELY(pst_extend_hdr->vap_id > WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}

/*
oal_int32 dmac_rx_wifi_pre_action_function(oal_uint8 stype, hcc_netbuf_stru* pst_hcc_netbuf,
                                                  oal_uint8  **pre_do_context)
{
    return OAL_SUCC;
}
*/

oal_int32 hmac_rx_wifi_post_action_function(oal_uint8 stype,
                                             hcc_netbuf_stru* pst_hcc_netbuf, oal_uint8 *pst_context)
{
    oal_int32 ret = OAL_SUCC;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_vap_stru             *pst_hmac_vap;
#endif
    struct frw_hcc_extend_hdr* pst_extend_hdr;

    frw_event_mem_stru   *pst_event_mem;      /*event mem */
    frw_event_stru       *pst_event;
    hcc_event_stru       *pst_event_payload;
    mac_rx_ctl_cut_stru  *pst_rx_ctl;
    oal_uint8            *puc_hcc_extend_hdr;

    pst_extend_hdr = (struct frw_hcc_extend_hdr*)OAL_NETBUF_DATA(pst_hcc_netbuf->pst_netbuf);
    if(OAL_TRUE != hmac_rx_extend_hdr_vaild_check(pst_extend_hdr))
    {
        oal_print_hex_dump(OAL_NETBUF_DATA(pst_hcc_netbuf->pst_netbuf), (oal_int32)OAL_NETBUF_LEN(pst_hcc_netbuf->pst_netbuf),
                           32, "invaild frw extend hdr: ");
        return -OAL_EINVAL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_extend_hdr->vap_id);

    frw_event_task_lock();
    if(OAL_UNLIKELY(NULL == pst_hmac_vap))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "hmac rx adapt ignored,pst vap is null, vap id:%u", pst_extend_hdr->vap_id);
        frw_event_task_unlock();
        oal_netbuf_free(pst_hcc_netbuf->pst_netbuf);
        return -OAL_EINVAL;
    }

    if(OAL_UNLIKELY(MAC_VAP_VAILD != pst_hmac_vap->st_vap_base_info.uc_init_flag))
    {
        if(0 == pst_extend_hdr->vap_id)
        {
            /*配置VAP不过滤*/
        }
        else
        {
            OAM_WARNING_LOG2(pst_extend_hdr->vap_id, OAM_SF_ANY, "hmac rx adapt ignored,main:%u,sub:%u", pst_extend_hdr->en_nest_type,pst_extend_hdr->uc_nest_sub_type);
            frw_event_task_unlock();
            oal_netbuf_free(pst_hcc_netbuf->pst_netbuf);
            return -OAL_ENOMEM;
        }
    }
    frw_event_task_unlock();
#endif

    if(OAL_TRUE == g_ul_pm_wakeup_event)
    {
        g_ul_pm_wakeup_event = OAL_FALSE;
        if(FRW_EVENT_TYPE_WLAN_CRX == pst_extend_hdr->en_nest_type)
        {
          g_ul_print_wakeup_mgmt = OAL_TRUE;
        }
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        OAL_IO_PRINT("[WARN]event mem alloc failed\n");
        return -OAL_ENOMEM;
    }

    /*trim the frw hcc extend header*/
    oal_netbuf_pull(pst_hcc_netbuf->pst_netbuf, OAL_SIZEOF(struct frw_hcc_extend_hdr));

    /*event hdr point*/
    pst_event = frw_get_event_stru(pst_event_mem);

    /*fill event hdr*/
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       pst_extend_hdr->en_nest_type,
                       pst_extend_hdr->uc_nest_sub_type,
                       OAL_SIZEOF(hcc_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_extend_hdr->chip_id,
                       pst_extend_hdr->device_id,
                       pst_extend_hdr->vap_id);


    pst_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_event_payload->pst_netbuf = pst_hcc_netbuf->pst_netbuf;
    pst_event_payload->ul_buf_len = OAL_NETBUF_LEN(pst_hcc_netbuf->pst_netbuf);
    //pst_event_payload->ul_buf_len = pst_hcc_netbuf->len;

    puc_hcc_extend_hdr  = OAL_NETBUF_DATA((oal_netbuf_stru *)pst_event_payload->pst_netbuf);
    pst_rx_ctl    = (mac_rx_ctl_cut_stru *)puc_hcc_extend_hdr;


    if(!(pst_rx_ctl->bit_is_beacon))
    {
        #ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
        if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_count_func)
        {
            g_pst_alg_process_func.p_auto_freq_count_func(1);
        }
        #endif

        //wlan_pm_feed_wdg();
    }

    frw_event_task_lock();
    ret = (oal_int32)frw_event_dispatch_event(pst_event_mem);
    frw_event_task_unlock();
    if(OAL_WARN_ON(OAL_SUCC != ret))
    {
        /*如果事件入队失败，内存失败由该函数释放，直接调用的由rx adapt函数释放!*/
        OAL_IO_PRINT("[WARN]hcc rx post event failed!!!ret=%u,main:%d,sub:%d\n",
                    ret,
                    pst_extend_hdr->en_nest_type,
                    pst_extend_hdr->uc_nest_sub_type);
    }
    FRW_EVENT_FREE(pst_event_mem);

    return ret;
}

oal_int32 hmac_hcc_adapt_init(oal_void)
{
    hmac_tx_net_queue_map_init();
    hmac_tx_sched_info_init();
    hcc_rx_register(hcc_get_default_handler(), HCC_ACTION_TYPE_WIFI, hmac_rx_wifi_post_action_function, NULL);
#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
    hwifi_panic_log_register(&hmac_panic_hcc_adapt,NULL);
#endif
    return OAL_SUCC;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


