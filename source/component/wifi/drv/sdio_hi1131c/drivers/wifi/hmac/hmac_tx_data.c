/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_tx_data.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月12日
  最近修改   :
  功能描述   : HMAC BSS AP TX 主文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月12日
    作    者   : 
    修改内容   : 创建文件
  2.日    期   : 2013年1月8日
    作    者   :  52447
    修改内容   : 文件名修改为hmac_tx_data.c
******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_profiling.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "hmac_tx_data.h"
#include "hmac_tx_amsdu.h"
#include "mac_frame.h"
#include "mac_data.h"
#include "hmac_frag.h"
#include "hmac_11i.h"
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "hmac_ext_if.h"
#endif
#ifdef _PRE_WLAN_FEATURE_MCAST /* 组播转单播 */
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#include "hmac_traffic_classify.h"
#endif

#include "hmac_crypto_tkip.h"
#include "hmac_device.h"
#include "hmac_resource.h"

#include "hmac_tcp_opt.h"

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TX_DATA_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
static oal_uint16 us_noqos_frag_seqnum= 0; /*保存非qos分片帧seqnum*/
#endif


/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_uint32 hmac_tx_data(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);
#endif


/*****************************************************************************
 函 数 名  : hmac_tx_is_dhcp
 功能描述  : 判断是否是dhcp帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_tx_is_dhcp(mac_ether_header_stru  *pst_ether_hdr)
{
    mac_ip_header_stru     *puc_ip_hdr;

    puc_ip_hdr = (mac_ip_header_stru *)(pst_ether_hdr + 1);

    return mac_is_dhcp_port(puc_ip_hdr);

}


/*****************************************************************************
 函 数 名  : hmac_tx_report_dhcp_and_arp
 功能描述  : 上报dhcp和arp request
 输入参数  : pst_ether_hdr :以太网帧头指针
             us_ether_len  :以太网帧长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_tx_report_dhcp_and_arp(
                                            mac_vap_stru  *pst_mac_vap,
                                            mac_ether_header_stru  *pst_ether_hdr,
                                            oal_uint16   us_ether_len)
{
    oal_bool_enum_uint8     en_flg = OAL_FALSE;

    switch (OAL_HOST2NET_SHORT(pst_ether_hdr->us_ether_type))
    {
        case ETHER_TYPE_ARP:
            en_flg = OAL_TRUE;
        break;

        case ETHER_TYPE_IP:
            en_flg = hmac_tx_is_dhcp(pst_ether_hdr);
        break;

        default:
            en_flg = OAL_FALSE;
        break;
    }

    if (en_flg && oam_report_dhcp_arp_get_switch())
    {
        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            oam_report_eth_frame(pst_ether_hdr->auc_ether_dhost, (oal_uint8 *)pst_ether_hdr, us_ether_len, OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        }
        else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            oam_report_eth_frame(pst_mac_vap->auc_bssid, (oal_uint8 *)pst_ether_hdr, us_ether_len, OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        }
        else
        {
        }
    }

}

/*****************************************************************************
 函 数 名  : hmac_tx_report_eth_frame
 功能描述  : 将以太网过来的帧上报SDT
 输入参数  : pst_mac_vap:mac_vap结构
             pst_netbuf :以太网过来的数据帧
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_report_eth_frame(mac_vap_stru   *pst_mac_vap,
                                           oal_netbuf_stru *pst_netbuf)
{
    oal_uint16              us_user_idx = 0;
    mac_ether_header_stru  *pst_ether_hdr = OAL_PTR_NULL;
    oal_uint32              ul_ret;
    oal_uint8               auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0};
    oal_switch_enum_uint8   en_eth_switch = 0;
#ifdef _PRE_WLAN_DFT_STAT
    hmac_vap_stru           *pst_hmac_vap;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::input null %x %x}", pst_mac_vap, pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_DFT_STAT
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::mac_res_get_hmac_vap fail. vap_id = %u}", pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

#endif

    /* 统计以太网下来的数据包统计 */
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_pkt_to_lan,1);
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_bytes_to_lan,OAL_NETBUF_LEN(pst_netbuf));
    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, tx_pkt_num_from_lan, 1);
    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, tx_bytes_from_lan, OAL_NETBUF_LEN(pst_netbuf));

    /* 获取目的用户资源池id和用户MAC地址，用于过滤 */
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::ether_hdr is null!\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_ether_hdr->auc_ether_dhost, &us_user_idx);
        if (OAL_ERR_CODE_PTR_NULL == ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::find user return ptr null!!\r\n", ul_ret);
            return ul_ret;
        }

        if (OAL_FAIL == ul_ret)
        {
            /* 如果找不到用户，该帧可能是dhcp或者arp request，需要上报 */
            hmac_tx_report_dhcp_and_arp(pst_mac_vap, pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf));
            return OAL_SUCC;
        }

        oal_set_mac_addr(auc_user_macaddr, pst_ether_hdr->auc_ether_dhost);
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        if (0 == pst_mac_vap->us_user_nums)
        {
            return OAL_SUCC;
        }
#if 1
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::ether_hdr is null!\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }
        /* 如果找不到用户，该帧可能是dhcp或者arp request，需要上报 */
        hmac_tx_report_dhcp_and_arp(pst_mac_vap, pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf));

#endif
        us_user_idx = pst_mac_vap->uc_assoc_vap_id;
        oal_set_mac_addr(auc_user_macaddr, pst_mac_vap->auc_bssid);
    }

    /* 检查打印以太网帧的开关 */
    ul_ret = oam_report_eth_frame_get_switch(us_user_idx, OAM_OTA_FRAME_DIRECTION_TYPE_TX, &en_eth_switch);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::get tx eth frame switch fail!\r\n");
        return ul_ret;
    }

    if (OAL_SWITCH_ON == en_eth_switch)
    {
        /* 将以太网下来的帧上报 */
        ul_ret = oam_report_eth_frame(auc_user_macaddr,
                             oal_netbuf_data(pst_netbuf),
                             (oal_uint16)OAL_NETBUF_LEN(pst_netbuf),
                             OAM_OTA_FRAME_DIRECTION_TYPE_TX);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{hmac_tx_report_eth_frame::oam_report_eth_frame return err: 0x%x.}\r\n", ul_ret);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_free_netbuf_list
 功能描述  : 释放一个netbuf链，此链中的skb或者都来自lan，或者都来自wlan
 输入参数  : pst_buf－SKB结构体单向链表，最后一个next指针务必为NULL，否则会出异常
 输出参数  :
 返 回 值  : 释放的buf数目
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_free_netbuf_list(oal_netbuf_stru  *pst_buf)
{
    oal_netbuf_stru     *pst_buf_tmp;
    mac_tx_ctl_stru     *pst_tx_cb;
    oal_uint16           us_buf_num = 0;

    if(OAL_PTR_NULL != pst_buf)
    {
        pst_tx_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);

        while (OAL_PTR_NULL != pst_buf)
        {
            pst_buf_tmp = oal_netbuf_list_next(pst_buf);
            us_buf_num++;

            pst_tx_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
            /*
                释放内存增加判断oal_netbuf_headroom(pst_buf) <  MAC_80211_QOS_HTC_4ADDR_FRAME_LEN
               如果frame_header部分是内存池申请的才从内存池释放，采用skb内部自身的，就不需要再释放
            */
            if ((oal_netbuf_headroom(pst_buf) <  MAC_80211_QOS_HTC_4ADDR_FRAME_LEN) && (OAL_PTR_NULL != pst_tx_cb->pst_frame_header))
            {
                OAL_MEM_FREE(pst_tx_cb->pst_frame_header, OAL_TRUE);
                pst_tx_cb->pst_frame_header = OAL_PTR_NULL;
            }

            oal_netbuf_free(pst_buf);

            pst_buf = pst_buf_tmp;
        }
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_free_netbuf_list::pst_buf is null}");
    }

    return us_buf_num;
}

#if 0
/*****************************************************************************
 函 数 名  : hmac_tx_classify_wlan_to_wlan
 功能描述  : 从wlan过来报文的业务识别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_tx_classify_wlan_to_wlan(mac_tx_ctl_stru *pst_tx_ctl, oal_uint8 *puc_tid)
{
    mac_ieee80211_frame_stru            *pst_frame_header;
    mac_ieee80211_qos_frame_stru        *pst_qos_header;
    mac_ieee80211_qos_frame_addr4_stru  *pst_qos_addr4_headder;
    oal_uint8                            uc_tid = 0;


    OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_wlan_to_wlan::enter func.}");
    pst_frame_header = pst_tx_ctl->pst_frame_header;

    /* 由帧头判断是否是QoS data帧，如果是则从Qos字段取出tid值 */
    if (WLAN_DATA_BASICTYPE == pst_frame_header->st_frame_control.bit_type
        && WLAN_QOS_DATA == pst_frame_header->st_frame_control.bit_sub_type)
    {
        if (OAL_TRUE == pst_tx_ctl->en_use_4_addr)                /* 使用4地址 */
        {
            pst_qos_addr4_headder = (mac_ieee80211_qos_frame_addr4_stru *)pst_frame_header;

            uc_tid = pst_qos_addr4_headder->bit_qc_tid;
        }
        else
        {
            pst_qos_header = (mac_ieee80211_qos_frame_stru *)pst_frame_header;

            uc_tid = pst_qos_header->bit_qc_tid;
        }
    }

    /* 出参赋值 */
    *puc_tid = uc_tid;

}
#endif

#ifdef _PRE_WLAN_FEATURE_HS20
/*****************************************************************************
 函 数 名  : hmac_tx_set_qos_map
 功能描述  : 根据对端发送的QoS_Map项更新TID
 输入参数  : oal_netbuf_stru *pst_buf, oal_uint8 *puc_tid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_tx_set_qos_map(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tid)
{
    mac_ether_header_stru  *pst_ether_header;
    mac_ip_header_stru     *pst_ip;
    oal_uint8               uc_dscp = 0;
    mac_tx_ctl_stru        *pst_tx_ctl;
    hmac_vap_stru          *pst_hmac_vap     = OAL_PTR_NULL;
    oal_uint8               uc_idx;

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    pst_hmac_vap     = (hmac_vap_stru *)mac_res_get_hmac_vap(MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));

    /* 获取以太网头 */
    pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_ether_header))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HS20,
                       "{hmac_tx_set_qos_map::The input parameter of QoS_Map_Configure_frame_with_QoSMap_Set_element is OAL_PTR_NULL.}");
        return;
    }

    /* 从IP TOS字段寻找DSCP优先级 */
    /*---------------------------------
      tos位定义
      ---------------------------------
    |    bit7~bit2      | bit1~bit0 |
    |    DSCP优先级     | 保留      |
    ---------------------------------*/

    /* 偏移一个以太网头，取ip头 */
    pst_ip = (mac_ip_header_stru *)(pst_ether_header + 1);
    uc_dscp = pst_ip->uc_tos >> WLAN_DSCP_PRI_SHIFT;
    OAM_INFO_LOG2(0, OAM_SF_HS20, "{hmac_tx_set_qos_map::tos = %d, uc_dscp=%d.}", pst_ip->uc_tos, uc_dscp);

    if ((pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except > 0)
        &&(pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except <= MAX_DSCP_EXCEPT)
        && (pst_hmac_vap->st_cfg_qos_map_param.uc_valid))
    {
        for (uc_idx = 0; uc_idx < pst_hmac_vap->st_cfg_qos_map_param.uc_num_dscp_except; uc_idx++)
        {
            if (uc_dscp == pst_hmac_vap->st_cfg_qos_map_param.auc_dscp_exception[uc_idx])
            {
               *puc_tid  = pst_hmac_vap->st_cfg_qos_map_param.auc_dscp_exception_up[uc_idx];
                pst_tx_ctl->bit_is_vipframe              = OAL_TRUE;
                pst_tx_ctl->bit_is_needretry             = OAL_TRUE;
                pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
                return;
            }
        }
    }

    for (uc_idx = 0; uc_idx < MAX_QOS_UP_RANGE; uc_idx++)
    {
        if ((uc_dscp < pst_hmac_vap->st_cfg_qos_map_param.auc_up_high[uc_idx])
            && (uc_dscp > pst_hmac_vap->st_cfg_qos_map_param.auc_up_low[uc_idx]))
        {
           *puc_tid  = uc_idx;
            pst_tx_ctl->bit_is_vipframe              = OAL_TRUE;
            pst_tx_ctl->bit_is_needretry             = OAL_TRUE;
            pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
            return;
        }
        else
        {
            *puc_tid = 0;
        }
    }
    pst_hmac_vap->st_cfg_qos_map_param.uc_valid = 0;
    return;
}
#endif //_PRE_WLAN_FEATURE_HS20

#ifdef _PRE_WLAN_FEATURE_CLASSIFY
/*****************************************************************************
 函 数 名  : hmac_tx_classify_lan_to_wlan
 功能描述  : 从lan过来报文的业务识别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年11月23日
    作    者   : ()
    修改内容   : 函数算法增量

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_tx_classify_lan_to_wlan(oal_netbuf_stru *pst_buf, oal_uint8 *puc_tid)
{
    mac_ether_header_stru  *pst_ether_header;
    mac_ip_header_stru     *pst_ip;
    oal_vlan_ethhdr_stru   *pst_vlan_ethhdr;
    oal_uint32              ul_ipv6_hdr;
    oal_uint32              ul_pri;
    oal_uint16              us_vlan_tci;
    oal_uint8               uc_tid = 0;
    mac_tx_ctl_stru        *pst_tx_ctl;
#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_EDCA_OPT_AP) || defined(_PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN)
    hmac_vap_stru          *pst_hmac_vap     = OAL_PTR_NULL;
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    hmac_user_stru         *pst_hmac_user    = OAL_PTR_NULL;
#endif
#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    mac_tcp_header_stru    *pst_tcp;
#endif

    pst_tx_ctl     = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_EDCA_OPT_AP) || defined(_PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN)
    pst_hmac_vap   = (hmac_vap_stru *)mac_res_get_hmac_vap(MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));
    if  (OAL_PTR_NULL == pst_hmac_vap)
    {
    	OAM_WARNING_LOG1(0,OAM_SF_TX,"{hmac_tx_classify_lan_to_wlan::mac_res_get_hmac_vap fail.vap_index[%u]}",MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl));
	    return;
    }
#endif
    /* 获取以太网头 */
    pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    switch (pst_ether_header->us_ether_type)
    {
        /*lint -e778*//* 屏蔽Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_IP.}");

        #ifdef _PRE_WLAN_FEATURE_HS20
            if (pst_hmac_vap->st_cfg_qos_map_param.uc_valid)
            {
                hmac_tx_set_qos_map(pst_buf, &uc_tid);
               *puc_tid = uc_tid;
                return;
            }
        #endif //_PRE_WLAN_FEATURE_HS20

            /* 从IP TOS字段寻找优先级 */
            /*----------------------------------------------------------------------
                tos位定义
             ----------------------------------------------------------------------
            | bit7~bit5 | bit4 |  bit3  |  bit2  |   bit1   | bit0 |
            | 包优先级  | 时延 | 吞吐量 | 可靠性 | 传输成本 | 保留 |
             ----------------------------------------------------------------------*/
            pst_ip = (mac_ip_header_stru *)(pst_ether_header + 1);      /* 偏移一个以太网头，取ip头 */

            uc_tid = pst_ip->uc_tos >> WLAN_IP_PRI_SHIFT;

        #ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
            if (OAL_SWITCH_ON == pst_hmac_vap->uc_tx_traffic_classify_flag)
            {
                if (0 != uc_tid)
                {
                    break;
                }
                hmac_tx_traffic_classify(pst_tx_ctl, pst_ip, &uc_tid);
            }
        #endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

            OAM_INFO_LOG2(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::tos = %d, uc_tid=%d.}", pst_ip->uc_tos, uc_tid);
            /* 如果是DHCP帧，则进入VO队列发送 */
            if (OAL_TRUE == mac_is_dhcp_port(pst_ip))
            {
                uc_tid = WLAN_DATA_VIP_TID;
                pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
                pst_tx_ctl->bit_is_needretry = OAL_TRUE;
            }
#ifdef _PRE_WLAN_FEATURE_SCHEDULE
            /* 对于chariot信令报文进行特殊处理，防止断流 */
            else if (MAC_TCP_PROTOCAL == pst_ip->uc_protocol)
            {
                pst_tcp = (mac_tcp_header_stru *)(pst_ip + 1);

                if ((OAL_NTOH_16(pst_tcp->us_dport) == MAC_CHARIOT_NETIF_PORT)
                        || (OAL_NTOH_16(pst_tcp->us_sport) == MAC_CHARIOT_NETIF_PORT))
                {
                    OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::chariot netif tcp pkt.}");
                    uc_tid = WLAN_DATA_VIP_TID;
                    pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
                    pst_tx_ctl->bit_is_needretry = OAL_TRUE;
                }
            }
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_user    = (hmac_user_stru *)mac_res_get_hmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
            {
                OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_edca_opt_rx_pkts_stat::null param,pst_hmac_user[%d].}",MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
                break;
            }

            if ((OAL_TRUE == pst_hmac_vap->uc_edca_opt_flag_ap) && (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode))
            {
                /* mips优化:解决开启业务统计性能差10M问题 */
                if (((MAC_UDP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tid)][WLAN_TX_UDP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10)))
                    || ((MAC_TCP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user->aaul_txrx_data_stat[WLAN_WME_TID_TO_AC(uc_tid)][WLAN_TX_TCP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10))))
                {
                    hmac_edca_opt_tx_pkts_stat(pst_tx_ctl, uc_tid, pst_ip);
                }
            }
#endif
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_IPV6.}");
            /* 从IPv6 traffic class字段获取优先级 */
            /*----------------------------------------------------------------------
                IPv6包头 前32为定义
             -----------------------------------------------------------------------
            | 版本号 | traffic class   | 流量标识 |
            | 4bit   | 8bit(同ipv4 tos)|  20bit   |
            -----------------------------------------------------------------------*/
            ul_ipv6_hdr = *((oal_uint32 *)(pst_ether_header + 1));  /* 偏移一个以太网头，取ip头 */

            ul_pri = (OAL_NET2HOST_LONG(ul_ipv6_hdr) & WLAN_IPV6_PRIORITY_MASK) >> WLAN_IPV6_PRIORITY_SHIFT;

            uc_tid = (oal_uint8)(ul_pri >> WLAN_IP_PRI_SHIFT);
            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);

            /* 如果是ND帧，则进入VO队列发送 */
            if (OAL_TRUE == mac_is_nd((oal_ipv6hdr_stru *)(pst_ether_header + 1)))
            {
                uc_tid = WLAN_DATA_VIP_TID;
                pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
                pst_tx_ctl->bit_is_needretry = OAL_TRUE;
            }

            /* 如果是DHCPV6帧，则进入VO队列发送 */
            else if (OAL_TRUE == mac_is_dhcp6((oal_ipv6hdr_stru *)(pst_ether_header + 1)))
            {
                OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_DHCP6.}");
                uc_tid = WLAN_DATA_VIP_TID;
                pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
                pst_tx_ctl->bit_is_needretry = OAL_TRUE;
            }

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_PAE):
            /* 如果是EAPOL帧，则进入VO队列发送 */
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_PAE.}");
            uc_tid = WLAN_DATA_VIP_TID;
            pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
            pst_tx_ctl->bit_is_needretry = OAL_TRUE;

#ifdef _PRE_DEBUG_MODE
            pst_tx_ctl->en_is_eapol      = OAL_TRUE;
            pst_tx_ctl->us_eapol_ts = (oal_uint16)OAL_TIME_GET_STAMP_MS();
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::tx EAPOL.}");
#endif

            /* 如果是4 次握手设置单播密钥，则设置tx cb 中bit_is_eapol_key_ptk 置一，dmac 发送不加密 */
            if (OAL_TRUE == mac_is_eapol_key_ptk((mac_eapol_header_stru *)(pst_ether_header + 1)))
            {
                pst_tx_ctl->bit_is_eapol_key_ptk = OAL_TRUE;
            }

            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

        /* TDLS帧处理，建链保护，入高优先级TID队列 */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_TDLS):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_TDLS.}");
            uc_tid = WLAN_DATA_VIP_TID;
            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

		/* PPPOE帧处理，建链保护(发现阶段, 会话阶段)，入高优先级TID队列 */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC):
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_PPP_DISC, ETHER_TYPE_PPP_SES.}");
            uc_tid = WLAN_DATA_VIP_TID;
            pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
            pst_tx_ctl->bit_is_needretry = OAL_TRUE;

            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

#ifdef _PRE_WLAN_FEATURE_WAPI
        case OAL_HOST2NET_SHORT(ETHER_TYPE_WAI):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_WAI.}");
            uc_tid = WLAN_DATA_VIP_TID;
            pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
            pst_tx_ctl->bit_is_needretry = OAL_TRUE;
            break;
#endif

        case OAL_HOST2NET_SHORT(ETHER_TYPE_VLAN):
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_VLAN.}");
            /* 获取vlan tag的优先级 */
            pst_vlan_ethhdr = (oal_vlan_ethhdr_stru *)oal_netbuf_data(pst_buf);

            /*------------------------------------------------------------------
                802.1Q(VLAN) TCI(tag control information)位定义
             -------------------------------------------------------------------
            |Priority | DEI  | Vlan Identifier |
            | 3bit    | 1bit |      12bit      |
             ------------------------------------------------------------------*/
            us_vlan_tci = OAL_NET2HOST_SHORT(pst_vlan_ethhdr->h_vlan_TCI);

            uc_tid = us_vlan_tci >> OAL_VLAN_PRIO_SHIFT;    /* 右移13位，提取高3位优先级 */
            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
            /* 如果是ARP帧，则进入VO队列发送 */
            OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::ETHER_TYPE_ARP.}");
            uc_tid = WLAN_DATA_VIP_TID;
            pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::uc_tid=%d.}", uc_tid);
            break;

        /*lint +e778*/
        default:
            OAM_INFO_LOG1(0, OAM_SF_TX, "{hmac_tx_classify_lan_to_wlan::default us_ether_type[%d].}", pst_ether_header->us_ether_type);
            break;
    }

    /* 出参赋值 */
    *puc_tid = uc_tid;
}

/*****************************************************************************
 函 数 名  : hmac_tx_update_tid
 功能描述  : 根据算法需求，tid = 1, 3, 5, 7的，分别更新为0, 2, 4, 6
             如果WMM功能关闭，直接填为DMAC_WMM_SWITCH_TID
 输入参数  : puc_tid 注意，此参数为入出参
 输出参数  : puc_tid
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_tx_update_tid(oal_bool_enum_uint8  en_wmm, oal_uint8 *puc_tid)
{

    if (OAL_LIKELY(OAL_TRUE == en_wmm)) /*wmm使能*/
    {
        *puc_tid = (*puc_tid < WLAN_TIDNO_BUTT) ? WLAN_TOS_TO_TID(*puc_tid): WLAN_TIDNO_BCAST;
    }
    else   /*wmm不使能*/
    {
        *puc_tid = MAC_WMM_SWITCH_TID;
    }
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : hmac_tx_wmm_acm
 功能描述  : 根据热点配置ACM，重新选择队列
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint8 hmac_tx_wmm_acm(oal_bool_enum_uint8  en_wmm, hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_tid)
{
    oal_uint8                   uc_ac;
    oal_uint8                   uc_ac_new;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_tid))
    {
        return OAL_FALSE;
    }

    if (OAL_FALSE == en_wmm)
    {
        return OAL_FALSE;
    }

    uc_ac = WLAN_WME_TID_TO_AC(*puc_tid);
    uc_ac_new = uc_ac;
    while ((uc_ac_new != WLAN_WME_AC_BK) && (OAL_TRUE == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_ac_new].en_dot11QAPEDCATableMandatory))
    {
        switch (uc_ac_new)
        {
            case WLAN_WME_AC_VO:
                uc_ac_new = WLAN_WME_AC_VI;
                break;

            case WLAN_WME_AC_VI:
                uc_ac_new = WLAN_WME_AC_BE;
                break;

            default:
                uc_ac_new = WLAN_WME_AC_BK;
                break;
        }
    }

    if (uc_ac_new != uc_ac)
    {
        *puc_tid = WLAN_WME_AC_TO_TID(uc_ac_new);
    }

    return OAL_TRUE;
}
#endif /* (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST) */

/*****************************************************************************
 函 数 名  : hmac_tx_classify
 功能描述  : 以太网包 业务识别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月2日
    作    者   : 
    修改内容   : 新生成函数

  2.日    期   : 2013年10月10日
    作    者   : 
    修改内容   : 增加wlan to wlan分支处理

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_tx_classify(
                hmac_vap_stru   *pst_hmac_vap,
                mac_user_stru   *pst_user,
                oal_netbuf_stru *pst_buf)
{
    oal_uint8               uc_tid = 0;
    mac_tx_ctl_stru        *pst_tx_ctl;
    mac_device_stru        *pst_mac_dev = OAL_PTR_NULL;

    hmac_tx_classify_lan_to_wlan(pst_buf, &uc_tid);

    /* 非QoS站点，直接返回 */
    if (OAL_UNLIKELY(OAL_TRUE != pst_user->st_cap_info.bit_qos))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify::user is a none QoS station.}");
        return;
    }

    pst_mac_dev = mac_res_get_dev(pst_user->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify::pst_mac_dev null.}");
        return;
    }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    hmac_tx_wmm_acm(pst_mac_dev->en_wmm, pst_hmac_vap, &uc_tid);
#endif /* */

    /* : 由于1151支持VO聚合, VIP报文和VO报文都放在tid 6聚合传输, 导致VIP报文无法以基本速率发送。
       因此, 将VIP报文放在tid 7, 与实际VO业务区分, 保证VIP报文的传输可靠性。 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    if ((OAL_TRUE != pst_tx_ctl->bit_is_vipframe) || (OAL_FALSE == pst_mac_dev->en_wmm))
    {
        hmac_tx_update_tid(pst_mac_dev->en_wmm, &uc_tid);
    }

    /* 如果使能了vap流等级，则采用设置的vap流等级 */
    if (OAL_TRUE == pst_mac_dev->en_vap_classify)
    {
        uc_tid = pst_hmac_vap->uc_classify_tid;
    }

    /* 设置ac和tid到cb字段 */
    pst_tx_ctl->uc_tid  = uc_tid;
    pst_tx_ctl->uc_ac   = WLAN_WME_TID_TO_AC(uc_tid);

    OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_classify::uc_ac=%d uc_tid=%d.}", pst_tx_ctl->uc_ac, pst_tx_ctl->uc_tid);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_tx_filter_security
 功能描述  : 针对来自以太网的数据帧做安全过滤
 输入参数  : hmac_vap_stru     *pst_hmac_vap
             oal_netbuf_stru  *pst_buf
             hmac_user_stru   *pst_hmac_user
             mac_tx_ctl_stru  *pst_tx_ctl
 输出参数  : OAL_TRUE
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月12日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 hmac_tx_filter_security(hmac_vap_stru     *pst_hmac_vap,
                                        oal_netbuf_stru  *pst_buf,
                                        hmac_user_stru   *pst_hmac_user)
{
    mac_ether_header_stru   *pst_ether_header = OAL_PTR_NULL;
    mac_user_stru           *pst_mac_user     = OAL_PTR_NULL;
    mac_vap_stru            *pst_mac_vap      = OAL_PTR_NULL;
    oal_uint32               ul_ret           = OAL_SUCC;
    oal_uint16               us_ether_type;

    pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user = &(pst_hmac_user->st_user_base_info);

    if (OAL_TRUE == pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated)/* 判断是否使能WPA/WPA2 */
    {
        if (pst_mac_user->en_port_valid != OAL_TRUE)/* 判断端口是否打开 */
        {
            /* 获取以太网头 */
            pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
            /* 发送数据时，针对非EAPOL 的数据帧做过滤 */

            if (oal_byteorder_host_to_net_uint16(ETHER_TYPE_PAE) != pst_ether_header->us_ether_type)
            {
                us_ether_type = oal_byteorder_host_to_net_uint16(pst_ether_header->us_ether_type);
                OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_filter_security::TYPE 0x%04x, 0x%04x.}",
                               us_ether_type, ETHER_TYPE_PAE);
                ul_ret = OAL_FAIL;
            }
        }
    }


    return ul_ret;

}

/*****************************************************************************
 函 数 名  : hmac_tx_ba_setup
 功能描述  : 自动触发BA会话的建立
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_tx_ba_setup(
                hmac_vap_stru    *pst_hmac_vap,
                hmac_user_stru   *pst_user,
                oal_uint8         uc_tidno)
{
    mac_action_mgmt_args_stru   st_action_args;   /* 用于填写ACTION帧的参数 */
    oal_bool_enum_uint8         en_ampdu_support = OAL_FALSE;

    /* 建立BA会话，是否需要判断VAP的AMPDU的支持情况，因为需要实现建立BA会话时，一定发AMPDU */
    en_ampdu_support = hmac_user_xht_support(pst_user);

    if (en_ampdu_support)
    {
        /*
        建立BA会话时，st_action_args结构各个成员意义如下
        (1)uc_category:action的类别
        (2)uc_action:BA action下的类别
        (3)ul_arg1:BA会话对应的TID
        (4)ul_arg2:BUFFER SIZE大小
        (5)ul_arg3:BA会话的确认策略
        (6)ul_arg4:TIMEOUT时间
        */
        st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
        st_action_args.uc_action   = MAC_BA_ACTION_ADDBA_REQ;
        st_action_args.ul_arg1     = uc_tidno;                     /* 该数据帧对应的TID号 */
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
        st_action_args.ul_arg2     = (oal_uint32)g_st_wlan_customize.ul_ampdu_tx_max_num;       /* ADDBA_REQ中，buffer_size的默认大小 */
        OAM_WARNING_LOG1(0, OAM_SF_TX, "hisi_customize_wifi::[ba buffer size:%d]", st_action_args.ul_arg2);
#else
        st_action_args.ul_arg2     = WLAN_AMPDU_TX_MAX_BUF_SIZE;       /* ADDBA_REQ中，buffer_size的默认大小 */
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

        st_action_args.ul_arg3     = MAC_BA_POLICY_IMMEDIATE;     /* BA会话的确认策略 */
        st_action_args.ul_arg4     = 0;                            /* BA会话的超时时间设置为0 */

        /* 建立BA会话 */
        hmac_mgmt_tx_action(pst_hmac_vap, pst_user, &st_action_args);
    }
    else
    {
        if (DMAC_BA_INIT != pst_user->ast_tid_info[uc_tidno].st_ba_tx_info.en_ba_status)
        {
            st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
            st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
            st_action_args.ul_arg1     = uc_tidno;                                         /* 该数据帧对应的TID号 */
            st_action_args.ul_arg2     = MAC_ORIGINATOR_DELBA;                             /* 发送端删除ba */
            st_action_args.ul_arg3     = MAC_UNSPEC_REASON;                                /* BA会话删除原因 */
            st_action_args.puc_arg5     = pst_user->st_user_base_info.auc_user_mac_addr;   /* 用户mac地址 */

            /* 删除BA会话 */
            hmac_mgmt_tx_action(pst_hmac_vap, pst_user, &st_action_args);
        }
    }

}

/*****************************************************************************
 函 数 名  : hmac_tx_ucast_process
 功能描述  : 单播处理
 输入参数  : pst_vap VAP结构体; pst_buf netbuf结构体;pst_user 用户结构体
 输出参数  :
 返 回 值  :
 调用函数  : hmac_tx_mpdu_process_ap
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2013年09月12日
    作    者   : 
    修改内容   : 修改函数，增加安全过滤

*****************************************************************************/
oal_uint32 hmac_tx_ucast_process(
                hmac_vap_stru     *pst_hmac_vap,
                oal_netbuf_stru   *pst_buf,
                hmac_user_stru    *pst_user,
                mac_tx_ctl_stru   *pst_tx_ctl)
{
    oal_uint32         ul_ret = HMAC_TX_PASS;

   /*安全过滤*/
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    if (OAL_UNLIKELY(OAL_SUCC != hmac_tx_filter_security(pst_hmac_vap, pst_buf, pst_user)))
    {
        OAM_STAT_VAP_INCR(pst_hmac_vap->st_vap_base_info.uc_vap_id, tx_security_check_faild, 1);
        return HMAC_TX_DROP_SECURITY_FILTER;
    }
#endif

    /*以太网业务识别*/
#ifdef _PRE_WLAN_FEATURE_CLASSIFY
    hmac_tx_classify(pst_hmac_vap, &(pst_user->st_user_base_info), pst_buf);
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    /* TBD */
#endif

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_TRAFFIC_CLASSIFY);
    /* 如果是EAPOL、DHCP帧，则不允许主动建立BA会话 */
    if (OAL_FALSE == pst_tx_ctl->bit_is_vipframe)
    {
#ifdef _PRE_WLAN_FEATURE_AMPDU
        if (OAL_TRUE == hmac_tid_need_ba_session(pst_hmac_vap, pst_user, pst_tx_ctl->uc_tid, pst_buf))
        {
            /* 自动触发建立BA会话，设置AMPDU聚合参数信息在DMAC模块的处理addba rsp帧的时刻后面 */
            hmac_tx_ba_setup(pst_hmac_vap, pst_user, pst_tx_ctl->uc_tid);
        }
#endif

        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_SETUP_BA);
#ifdef _PRE_WLAN_FEATURE_AMSDU
        ul_ret = hmac_amsdu_notify(pst_hmac_vap, pst_user, pst_buf);
        if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
        {
            return ul_ret;
        }
#endif
        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_AMSDU);
    }

    return ul_ret;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hmac_nonqos_frame_set_sn
 功能描述  : 对非Qos帧进行SN号的维护(目前只针对非qos帧分片场景下使用)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_nonqos_frame_set_sn(hmac_vap_stru *pst_hmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
    pst_tx_ctl->pst_frame_header->bit_seq_num = (us_noqos_frag_seqnum++) & 0x0fff;
    pst_tx_ctl->en_seq_ctrl_bypass = OAL_TRUE;
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_tx_is_need_frag
 功能描述  : 检查该报文是否需要分片
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_tx_is_need_frag(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint32        ul_threshold;
	oal_uint32        uc_last_frag;
    /* 判断报文是否需要进行分片 */
    /* 1、长度大于门限          */
    /* 2、是legac协议模式       */
    /* 3、不是广播帧            */
    /* 4、不是聚合帧            */
    /* 6、DHCP帧不进行分片      */

    if (OAL_TRUE == pst_tx_ctl->bit_is_vipframe)
    {
        return OAL_FALSE;
    }

    ul_threshold = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold;
    ul_threshold = (ul_threshold & (~(BIT0|BIT1))) + 2;
	/* 规避1151硬件bug,调整分片门限：TKIP加密时，当最后一个分片的payload长度小于等于8时，无法进行加密 */
	if (WLAN_80211_CIPHER_SUITE_TKIP == pst_hmac_user->st_user_base_info.st_key_info.en_cipher_type)
	{
		uc_last_frag = (OAL_NETBUF_LEN(pst_netbuf) + 8) % (ul_threshold - pst_tx_ctl->uc_frame_header_length - (WEP_IV_FIELD_SIZE + EXT_IV_FIELD_SIZE));
		if ((uc_last_frag > 0) && (uc_last_frag <= 8))
		{
			ul_threshold = ul_threshold + 8;
		}
	}

    return (((OAL_NETBUF_LEN(pst_netbuf) + pst_tx_ctl->uc_frame_header_length) > ul_threshold)
                     && (!pst_tx_ctl->en_ismcast)
                     && (!pst_tx_ctl->en_is_amsdu)
                     && (pst_hmac_user->st_user_base_info.en_cur_protocol_mode < WLAN_HT_MODE || pst_hmac_vap->st_vap_base_info.en_protocol < WLAN_HT_MODE)
                     &&(OAL_FALSE == hmac_vap_ba_is_setup(pst_hmac_user, pst_tx_ctl->uc_tid)));

}


#else

/*****************************************************************************
 函 数 名  : hmac_tx_is_need_frag
 功能描述  : 检查该报文是否需要分片
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_tx_is_need_frag(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint32        ul_threshold;
    /* 判断报文是否需要进行分片 */
    /* 1、长度大于门限          */
    /* 2、是legac协议模式       */
    /* 3、不是广播帧            */
    /* 4、不是聚合帧            */
    /* 6、DHCP帧不进行分片      */

    if (OAL_TRUE == pst_tx_ctl->bit_is_vipframe)
    {
        return OAL_FALSE;
    }
    ul_threshold = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold;
    ul_threshold = (ul_threshold & (~(BIT0|BIT1))) + 2;

    return ((OAL_NETBUF_LEN(pst_netbuf) > ul_threshold)
                     && (!pst_tx_ctl->en_ismcast)
                     && (!pst_tx_ctl->en_is_amsdu)
                     && (pst_hmac_user->st_user_base_info.en_avail_protocol_mode < WLAN_HT_MODE || pst_hmac_vap->st_vap_base_info.en_protocol < WLAN_HT_MODE)
                     &&(OAL_FALSE == hmac_vap_ba_is_setup(pst_hmac_user, pst_tx_ctl->uc_tid)));

}

#endif

/*****************************************************************************
 函 数 名  : hmac_tx_encap
 功能描述  : 802.11帧头封装 AP模式
 输入参数  : pst_vap－vap结构体
             pst_user－用户结构体
             pst_buf－BUF结构体
 输出参数  : pst_ret_hdr－返回的头部
 返 回 值  : OAL_PTR_NULL 或者 802.11帧头指针
 调用函数  : AMSDU模块以及本文件
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_encap(
                hmac_vap_stru    *pst_vap,
                hmac_user_stru   *pst_user,
                oal_netbuf_stru  *pst_buf)
{
    mac_ieee80211_qos_htc_frame_addr4_stru   *pst_hdr;           /* 802.11头 */
    mac_ether_header_stru                    *pst_ether_hdr;
    oal_uint32                                ul_qos = HMAC_TX_BSS_NOQOS;
    mac_tx_ctl_stru                          *pst_tx_ctl;
    oal_uint16                                us_ether_type = 0;
    oal_uint8                                 auc_saddr[ETHER_ADDR_LEN];   /* 原地址指针 */
    oal_uint8                                 auc_daddr[ETHER_ADDR_LEN];   /* 目的地址指针 */
    oal_uint32                                ul_ret;
    mac_llc_snap_stru                        *pst_snap_hdr;

#ifdef _PRE_DEBUG_MODE
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{hmac_tx_encap::param null,%d %d.}", pst_vap, pst_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* 获取CB */
    pst_tx_ctl = (mac_tx_ctl_stru *)(oal_netbuf_cb(pst_buf));

    /*如果skb中data指针前预留的空间大于802.11 mac head len，则不需要格外申请内存存放802.11头*/
    if (oal_netbuf_headroom(pst_buf) >=  MAC_80211_QOS_HTC_4ADDR_FRAME_LEN)
    {
        pst_hdr = (mac_ieee80211_qos_htc_frame_addr4_stru *)(OAL_NETBUF_HEADER(pst_buf)- MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
        pst_tx_ctl->bit_80211_mac_head_type = 1;  /*指示mac头部在skb中*/
    }
    else
    {

#ifdef _PRE_LWIP_ZERO_COPY_DEBUG
        OAM_ERROR_LOG0(0, 0, "[hmac_tx_encap] headroom not enough");
#endif

        /* 申请最大的80211头 */
        pst_hdr = (mac_ieee80211_qos_htc_frame_addr4_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DATA_PKT,
                                                                          MAC_80211_QOS_HTC_4ADDR_FRAME_LEN,
                                                                          OAL_FALSE);

        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hdr))
        {
            OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_encap::pst_hdr null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_tx_ctl->bit_80211_mac_head_type = 0;  /*指示mac头部不在skb中，申请了额外内存存放的*/
    }

    /* 获取以太网头, 原地址，目的地址, 以太网类型 */
    pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    oal_set_mac_addr((oal_uint8 *)auc_daddr, pst_ether_hdr->auc_ether_dhost);
    oal_set_mac_addr((oal_uint8 *)auc_saddr, pst_ether_hdr->auc_ether_shost);

    /*非amsdu帧*/
    if (OAL_FALSE == pst_tx_ctl->en_is_amsdu)
    {
        us_ether_type = pst_ether_hdr->us_ether_type;
    }
    else
    {
       /* 如果是AMSDU的第一个子帧，需要从snap头中获取以太网类型，如果是以太网帧，可以
          直接从以太网头中获取*/
        pst_snap_hdr  = (mac_llc_snap_stru *)((oal_uint8 *)pst_ether_hdr + ETHER_HDR_LEN);
        us_ether_type = pst_snap_hdr->us_ether_type;
    }

    /* 非组播帧，获取用户的QOS能力位信息 */
    if (OAL_FALSE == pst_tx_ctl->en_ismcast)
    {
        /* 根据用户结构体的cap_info，判断是否是QOS站点 */
        ul_qos                      = pst_user->st_user_base_info.st_cap_info.bit_qos;
        pst_tx_ctl->en_is_qosdata   = pst_user->st_user_base_info.st_cap_info.bit_qos;
    }

    /* 设置帧控制 */
    hmac_tx_set_frame_ctrl(ul_qos, pst_tx_ctl, pst_hdr);

    /* 设置地址 */
    ul_ret = hmac_tx_set_addresses(pst_vap, pst_user, pst_tx_ctl, auc_saddr, auc_daddr, pst_hdr, us_ether_type);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        if (0 == pst_tx_ctl->bit_80211_mac_head_type)
        {
            OAL_MEM_FREE(pst_hdr, OAL_TRUE);
        }
        OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_encap::hmac_tx_set_addresses failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 对于LAN to WLAN的非AMSDU聚合帧，填充LLC SNAP头 */
    if (OAL_FALSE == pst_tx_ctl->en_is_amsdu)
    {
#ifdef _PRE_WLAN_CHIP_TEST
        /* al tx */
        if(OAL_SWITCH_ON != pst_vap->st_vap_base_info.bit_al_tx_flag)
        {
#endif
           mac_set_snap(pst_buf, us_ether_type, (ETHER_HDR_LEN - SNAP_LLC_FRAME_LEN));
#ifdef _PRE_WLAN_CHIP_TEST
        }
#endif
        /* 更新frame长度 */
        pst_tx_ctl->us_mpdu_len = (oal_uint16) oal_netbuf_get_len(pst_buf);

        /* 非amsdu聚合帧，记录mpdu字节数，不包括snap */
        pst_tx_ctl->us_mpdu_bytes = pst_tx_ctl->us_mpdu_len - SNAP_LLC_FRAME_LEN;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* mac头部在skb中时，netbuf的data指针指向mac头。但是mac_set_snap函数中已经将data指针指向了llc头。因此这里要重新push到mac头。  */
    if (pst_tx_ctl->bit_80211_mac_head_type == 1)
    {
        oal_netbuf_push(pst_buf, MAC_80211_QOS_HTC_4ADDR_FRAME_LEN);
    }
#endif

    /* 挂接802.11头 */
    pst_tx_ctl->pst_frame_header = (mac_ieee80211_frame_stru *)pst_hdr;

    /* 对非Qos 帧进行 软件seq num的维护， */
    /* 分片处理 */
    if (OAL_TRUE == hmac_tx_is_need_frag(pst_vap, pst_user, pst_buf, pst_tx_ctl))
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        hmac_nonqos_frame_set_sn(pst_vap, pst_tx_ctl);
#endif
        ul_ret = hmac_frag_process_proc(pst_vap, pst_user, pst_buf, pst_tx_ctl);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_tx_mpdu_process
 功能描述  : 单个MPDU处理函数
 输入参数  : pst_event－事件结构体
             pst_vap－vap结构体
             pst_buf－BUF结构体
             pst_tx_ctl－CB结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_tx_lan_mpdu_process_sta(
                hmac_vap_stru      *pst_vap,
                oal_netbuf_stru    *pst_buf,
                mac_tx_ctl_stru    *pst_tx_ctl)
{
    hmac_user_stru          *pst_user;      /* 目标STA结构体 */
    mac_ether_header_stru   *pst_ether_hdr; /* 以太网头 */
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx;
    oal_uint8               *puc_ether_payload;

    pst_ether_hdr  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    pst_tx_ctl->uc_tx_vap_index = pst_vap->st_vap_base_info.uc_vap_id;

    us_user_idx = pst_vap->st_vap_base_info.uc_assoc_vap_id;

    pst_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_USER_NULL;
    }

    if (oal_byteorder_host_to_net_uint16(ETHER_TYPE_ARP) == pst_ether_hdr->us_ether_type)
    {
        pst_ether_hdr++;
        puc_ether_payload = (oal_uint8 *)pst_ether_hdr;
        /* The source MAC address is modified only if the packet is an   */
        /* ARP Request or a Response. The appropriate bytes are checked. */
        /* Type field (2 bytes): ARP Request (1) or an ARP Response (2)  */
        if((puc_ether_payload[6] == 0x00) &&
          (puc_ether_payload[7] == 0x02 || puc_ether_payload[7] == 0x01))
        {
            /* Set Address2 field in the WLAN Header with source address */
            oal_set_mac_addr(puc_ether_payload + 8, pst_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
        }
    }

    pst_tx_ctl->us_tx_user_idx = us_user_idx;

    ul_ret = hmac_tx_ucast_process(pst_vap, pst_buf, pst_user, pst_tx_ctl);
    if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
    {
        return ul_ret;
    }

    /* 封装802.11头 */
    ul_ret = hmac_tx_encap(pst_vap, pst_user, pst_buf);
    if (OAL_UNLIKELY((OAL_SUCC != ul_ret) ))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_mpdu_process_sta::hmac_tx_encap failed[%d].}", ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_80211_ENCAP_FAIL;
    }

    OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_ENCAP_HEAD);
    return HMAC_TX_PASS;
}

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
/*****************************************************************************
 函 数 名  : hmac_tx_proxyarp_is_en
 功能描述  : 检查proxyarp功能是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_tx_proxyarp_is_en(hmac_vap_stru *pst_vap)
{

   return (OAL_PTR_NULL != pst_vap->st_vap_base_info.pst_vap_proxyarp)
           && (OAL_TRUE == pst_vap->st_vap_base_info.pst_vap_proxyarp->en_is_proxyarp);

}
#endif

/*****************************************************************************
 函 数 名  : hmac_tx_mpdu_process
 功能描述  : 单个MPDU处理函数
 输入参数  : pst_event－事件结构体
             pst_vap－vap结构体
             pst_buf－BUF结构体
             pst_tx_ctl－CB结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hmac_tx_lan_mpdu_process_ap(
                hmac_vap_stru      *pst_vap,
                oal_netbuf_stru    *pst_buf,
                mac_tx_ctl_stru    *pst_tx_ctl)
{
    hmac_user_stru          *pst_user;      /* 目标STA结构体 */
    mac_ether_header_stru   *pst_ether_hdr; /* 以太网头 */
    oal_uint8               *puc_addr;      /* 目的地址 */
    oal_uint32               ul_ret;
    oal_uint16               us_user_idx;

    /* 判断是组播或单播,对于lan to wlan的单播帧，返回以太网地址 */
    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    puc_addr        = pst_ether_hdr->auc_ether_dhost;

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    /*确认proxy arp 是否使能*/
    if (OAL_TRUE == hmac_tx_proxyarp_is_en(pst_vap))
    {
        if(OAL_TRUE == hmac_proxy_arp_proc(pst_vap, pst_buf))
        {
            return HMAC_TX_DROP_PROXY_ARP;
        }
    }
#endif

    /*单播数据帧*/
#ifdef _PRE_WLAN_CHIP_TEST
    if (OAL_LIKELY(!ETHER_IS_MULTICAST(puc_addr)) && pst_vap->st_vap_base_info.bit_al_tx_flag != OAL_SWITCH_ON)
#else
    if (OAL_LIKELY(!ETHER_IS_MULTICAST(puc_addr)))
#endif
    {
        ul_ret = mac_vap_find_user_by_macaddr(&(pst_vap->st_vap_base_info), puc_addr, &us_user_idx);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{hmac_tx_lan_mpdu_process_ap::hmac_tx_find_user failed %2x:%2x:%2x:%2x}", puc_addr[2], puc_addr[3], puc_addr[4], puc_addr[5]);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_USER_UNKNOWN;
        }

        /* 转成HMAC的USER结构体 */
        pst_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_USER_NULL;
        }

        /* 用户状态判断 */
        if (OAL_UNLIKELY(MAC_USER_STATE_ASSOC != pst_user->st_user_base_info.en_user_asoc_state))
        {
             OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
             return HMAC_TX_DROP_USER_INACTIVE;
        }

        /* 目标user指针 */
        pst_tx_ctl->us_tx_user_idx = us_user_idx;

        ul_ret = hmac_tx_ucast_process(pst_vap, pst_buf, pst_user, pst_tx_ctl);
        if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
        {
            return ul_ret;
        }
    }
    else /* 组播 or 广播 */
    {
        /* 设置组播标识位 */
        pst_tx_ctl->en_ismcast = OAL_TRUE;

        /* 更新ACK策略 */
        pst_tx_ctl->en_ack_policy = WLAN_TX_NO_ACK;

        /* 获取组播用户 */
        pst_user = mac_res_get_hmac_user(pst_vap->st_vap_base_info.us_multi_user_idx);

        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                                 "{hmac_tx_lan_mpdu_process_ap::get multi user failed[%d].}", pst_vap->st_vap_base_info.us_multi_user_idx);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
            return HMAC_TX_DROP_MUSER_NULL;
        }

        pst_tx_ctl->us_tx_user_idx = pst_vap->st_vap_base_info.us_multi_user_idx;
        pst_tx_ctl->uc_tid  = WLAN_TIDNO_BCAST;

        pst_tx_ctl->uc_ac   = WLAN_WME_TID_TO_AC(pst_tx_ctl->uc_tid);

        #ifdef _PRE_WLAN_FEATURE_MCAST /* 组播转单播 */
            if ((ETHER_IS_IPV4_MULTICAST(puc_addr)) && (!ETHER_IS_BROADCAST(puc_addr)) && (OAL_PTR_NULL != pst_vap->pst_m2u))
            {
                ul_ret = hmac_m2u_snoop_convert(pst_vap, pst_buf);
                if (ul_ret != HMAC_TX_PASS)
                {
                    return ul_ret;
                }
            }
        #endif
    }

    /* 封装802.11头 */
    ul_ret = hmac_tx_encap(pst_vap, pst_user, pst_buf);
    if (OAL_UNLIKELY((OAL_SUCC != ul_ret) ))
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{hmac_tx_lan_mpdu_process_ap::hmac_tx_encap failed[%d].}", ul_ret);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return HMAC_TX_DROP_80211_ENCAP_FAIL;
    }

    return HMAC_TX_PASS;
}
/*****************************************************************************
 函 数 名  : hmac_tx_lan_to_wlan_no_tcp_opt
 功能描述  : hmac AP模式 处理HOST DRX事件，注册到事件管理模块中
             PAYLOAD是一个NETBUF
 输入参数  : pst_vap: vap指针
             pst_buf: netbuf指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_lan_to_wlan_no_tcp_opt(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    frw_event_stru        *pst_event;        /* 事件结构体 */
    frw_event_mem_stru    *pst_event_mem;
    hmac_vap_stru         *pst_hmac_vap;     /* VAP结构体 */
    mac_tx_ctl_stru       *pst_tx_ctl;       /* SKB CB */
    oal_uint32             ul_ret = HMAC_TX_PASS;
    dmac_tx_event_stru    *pst_dtx_stru;
    oal_uint8              uc_data_type;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru              *pst_user;
    hmac_wapi_stru              *pst_wapi;
    mac_ieee80211_frame_stru    *pst_mac_hdr;
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::pst_hmac_vap null.}");
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* VAP模式判断 */
    if (OAL_UNLIKELY(WLAN_VAP_MODE_BSS_AP != pst_vap->en_vap_mode && WLAN_VAP_MODE_BSS_STA != pst_vap->en_vap_mode))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::en_vap_mode=%d.}", pst_vap->en_vap_mode);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    /* 如果关联用户数量为0，则丢弃报文 */
    if (OAL_UNLIKELY(0 == pst_hmac_vap->st_vap_base_info.us_user_nums))
    {
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        return OAL_FAIL;
    }
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* 发数据，只发一次，避免反复申请tx描述符地址 */
    if (OAL_SWITCH_ON == pst_vap->bit_al_tx_flag)
    {
        if (OAL_FALSE != pst_vap->bit_first_run)
        {
            return OAL_SUCC;
        }
        mac_vap_set_al_tx_first_run(pst_vap, OAL_TRUE);
    }
#endif

    /* 初始化CB tx rx字段 , CB字段在前面已经被清零， 在这里不需要重复对某些字段赋零值*/
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
    pst_tx_ctl->uc_mpdu_num               = 1;
    pst_tx_ctl->uc_netbuf_num             = 1;
    pst_tx_ctl->en_frame_type             = WLAN_DATA_BASICTYPE;
    pst_tx_ctl->en_is_probe_data          = DMAC_USER_ALG_NON_PROBE;
    pst_tx_ctl->en_ack_policy             = WLAN_TX_NORMAL_ACK;
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_tx_ctl->en_ack_policy             = pst_hmac_vap->bit_ack_policy;
#endif
    pst_tx_ctl->uc_tx_vap_index           = pst_vap->uc_vap_id;
    pst_tx_ctl->us_tx_user_idx            = 0xffff;
    pst_tx_ctl->uc_ac                     = WLAN_WME_AC_BE;                  /* 初始化入BE队列 */

    /* 由于LAN TO WLAN和WLAN TO WLAN的netbuf都走这个函数，为了区分，需要先判断
       到底是哪里来的netbuf然后再对CB的事件类型字段赋值
    */
    if (FRW_EVENT_TYPE_WLAN_DTX != pst_tx_ctl->en_event_type)
    {
        pst_tx_ctl->en_event_type             = FRW_EVENT_TYPE_HOST_DRX;
        pst_tx_ctl->uc_event_sub_type         = DMAC_TX_HOST_DRX;
    }


    /* 此处数据可能从内核而来，也有可能由dev报上来再通过空口转出去，注意一下 */
    uc_data_type =  mac_get_data_type_from_8023((oal_uint8 *)oal_netbuf_data(pst_buf), MAC_NETBUFF_PAYLOAD_ETH);
    /* 维测，输出一个关键帧打印 */
    if((MAC_DATA_DHCP == uc_data_type) ||
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_HMAC == _PRE_MULTI_CORE_MODE)
    (MAC_DATA_ARP_REQ == uc_data_type)||
    (MAC_DATA_ARP_RSP == uc_data_type) ||
#endif
    (MAC_DATA_EAPOL == uc_data_type))
    {
        pst_tx_ctl->bit_is_vipframe  = OAL_TRUE;
        OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_WPA, "{hmac_tx_lan_to_wlan_no_tcp_opt::send datatype==%u, len==%u}[0:dhcp 1:arp_req 2:arp_rsp 3:eapol]", uc_data_type, OAL_NETBUF_LEN(pst_buf));
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        /*  处理当前 MPDU */
        if( OAL_FALSE == pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented )
        {
            pst_tx_ctl->uc_ac                     = WLAN_WME_AC_VO;            /*AP模式 关WMM 入VO队列 */
            pst_tx_ctl->uc_tid =  WLAN_WME_AC_TO_TID(pst_tx_ctl->uc_ac);
        }

        ul_ret = hmac_tx_lan_mpdu_process_ap(pst_hmac_vap, pst_buf, pst_tx_ctl);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* 处理当前MPDU */
        /*  */
        pst_tx_ctl->uc_ac                     = WLAN_WME_AC_VO;                  /* STA模式 非qos帧入VO队列 */
        /* , AC和tid队列要保持一致 */
        pst_tx_ctl->uc_tid =  WLAN_WME_AC_TO_TID(pst_tx_ctl->uc_ac);

        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_CB_INIT);
        ul_ret = hmac_tx_lan_mpdu_process_sta(pst_hmac_vap, pst_buf, pst_tx_ctl);

#ifdef _PRE_WLAN_FEATURE_WAPI
        if(HMAC_TX_PASS == ul_ret)
            //&& OAL_UNLIKELY(WAPI_IS_WORK(pst_hmac_vap)))
        {
            pst_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_vap->uc_assoc_vap_id);
            if (OAL_PTR_NULL == pst_user)
            {
                OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "hmac_tx_lan_to_wlan_no_tcp_opt::usrid==%u no usr!}", pst_vap->uc_assoc_vap_id);
                return HMAC_TX_DROP_USER_NULL;
            }

            /* 获取wapi对象 组播/单播 */
            pst_mac_hdr = ((mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf))->pst_frame_header;
/*lint -e730*/
            pst_wapi = hmac_user_get_wapi_ptr(pst_vap,
                                                !ETHER_IS_MULTICAST(pst_mac_hdr->auc_address1),
                                                        pst_user->st_user_base_info.us_assoc_id);
/*lint +e730*/

            if ( (OAL_TRUE == WAPI_IS_PORT_VALID(pst_wapi))
                    && (OAL_PTR_NULL != pst_wapi->wapi_netbuff_txhandle))
            {
                pst_buf = pst_wapi->wapi_netbuff_txhandle(pst_wapi, pst_buf);
                /*  由于wapi可能修改netbuff，此处需要重新获取一下cb */
                pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
            }
        }

#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */

    }

    if (OAL_LIKELY(HMAC_TX_PASS == ul_ret))
    {
        /* 抛事件，传给DMAC */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
        {
            OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::FRW_EVENT_ALLOC failed.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_vap->st_vap_stats.ul_tx_dropped_packets++;
#endif
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        /* 填写事件头 */
        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_HOST_DRX,
                            DMAC_TX_HOST_DRX,
                            OAL_SIZEOF(dmac_tx_event_stru),
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_vap->uc_chip_id,
                            pst_vap->uc_device_id,
                            pst_vap->uc_vap_id);

        pst_dtx_stru             = (dmac_tx_event_stru *)pst_event->auc_event_data;
        pst_dtx_stru->pst_netbuf = pst_buf;
        //pst_dtx_stru->us_frame_len = (oal_uint16)oal_netbuf_get_len(pst_buf);
        pst_dtx_stru->us_frame_len = pst_tx_ctl->us_mpdu_len;

        /* 调度事件 */
        ul_ret = frw_event_dispatch_event(pst_event_mem);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::frw_event_dispatch_event failed[%d].}", ul_ret);
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);
        }

         /* 释放事件 */
        FRW_EVENT_FREE(pst_event_mem);

        OAL_MIPS_TX_STATISTIC(HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC);
#ifdef _PRE_WLAN_PROFLING_MIPS
        oal_profiling_stop_tx_save();
#endif
    }
    else if (OAL_UNLIKELY(HMAC_TX_BUFF == ul_ret))
    {
        ul_ret = OAL_SUCC;
    }
    else if ((HMAC_TX_DONE == ul_ret))
    {
        ul_ret = OAL_SUCC;
    }
    else if ((HMAC_TX_DROP_MTOU_FAIL == ul_ret))
    {
        /* 组播报文没有对应的STA可以转成单播，所以丢弃，属正常行为 */
        OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }
    else
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_no_tcp_opt::HMAC_TX_DROP.reason[%d]!}", ul_ret);
    }

    return ul_ret;
}

#ifdef _PRE_WLAN_TCP_OPT
OAL_STATIC  oal_uint32 hmac_transfer_tx_handler(hmac_device_stru * hmac_device,hmac_vap_stru * hmac_vap,oal_netbuf_stru* netbuf)
{
    oal_uint32              ul_ret = OAL_SUCC;
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    if(WLAN_TCP_ACK_QUEUE == oal_netbuf_select_queue(netbuf))
    {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG0(0, OAM_SF_TX,
                             "{hmac_transfer_tx_handler::netbuf is tcp ack.}\r\n");
#endif
        oal_spin_lock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
        oal_netbuf_list_tail(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue[HMAC_TCP_ACK_QUEUE],
                        netbuf);
        ul_ret = OAL_SUCC;
        /* 单纯TCP ACK等待调度, 特殊报文马上发送 */
        if(hmac_judge_tx_netbuf_is_tcp_ack((oal_ether_header_stru *)oal_netbuf_data(netbuf)))
        {
            hmac_device->en_need_notify = OAL_TRUE;
            oal_spin_unlock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            hmac_sched_transfer();
        }
        else
        {
            oal_spin_unlock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_TX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            hmac_tcp_ack_process();
        }
    }
    else
    {
        ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt(&(hmac_vap->st_vap_base_info),netbuf);
    }
#endif
    return ul_ret;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_tx_wlan_to_wlan_ap
 功能描述  : (1)WLAN TO WLAN流程tx入口函数，接收rx流程抛过来的netbuf或者netbuf链，
             其中每一个netbuf里面有一个MSDU，每一个MSDU的内容是一个以太网格式的
             帧。如果是netbuf链，第一个netbuf的prev指针为空，最后一个netbuf的
             next指针为空。
             (2)函数循环调用LAN TO WLAN的入口函数来处理每一个MSDU，这样就把
             WLAN TO WLAN流程统一到了LAN TO WLAN流程
 输入参数  : pst_event_mem－事件内存块
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_wlan_to_wlan_ap(oal_mem_stru *pst_event_mem)
{
    frw_event_stru         *pst_event;        /* 事件结构体 */
    mac_vap_stru           *pst_mac_vap;
    oal_netbuf_stru        *pst_buf;          /* 从netbuf链上取下来的指向netbuf的指针 */
    oal_netbuf_stru        *pst_buf_tmp;      /* 暂存netbuf指针，用于while循环 */
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret;
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_DEBUG_MODE
    oal_uint16              us_buf_num = 0;
#endif
#endif
    /* 入参判断 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap::pst_event null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取PAYLOAD中的netbuf链 */
    pst_buf = (oal_netbuf_stru *)(*((oal_uint *)(pst_event->auc_event_data)));

    ul_ret = hmac_tx_get_mac_vap(pst_event->st_event_hdr.uc_vap_id, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_TX, "{hmac_tx_wlan_to_wlan_ap::hmac_tx_get_mac_vap failed[%d].}", ul_ret);
    #ifdef _PRE_DEBUG_MODE
    #if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        us_buf_num = hmac_free_netbuf_list(pst_buf);
        OAM_STAT_VAP_INCR(pst_event->st_event_hdr.uc_vap_id, tx_abnormal_msdu_dropped, us_buf_num);
    #else
        hmac_free_netbuf_list(pst_buf);
    #endif
    #else
        hmac_free_netbuf_list(pst_buf);
    #endif
        return ul_ret;
    }

    /* 循环处理每一个netbuf，按照以太网帧的方式处理 */
    while (OAL_PTR_NULL != pst_buf)
    {
        pst_buf_tmp = OAL_NETBUF_NEXT(pst_buf);

        OAL_NETBUF_NEXT(pst_buf) = OAL_PTR_NULL;
        OAL_NETBUF_PREV(pst_buf) = OAL_PTR_NULL;

        /* 由于此netbuf来自接收流程，是从内存池申请的，而以太网过来的netbuf是从
           操作系统申请的，二者的释放方式不一样，后续要通过事件类型字段来选择正确
           的释放方式
        */
        pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
        OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));

        pst_tx_ctl->en_event_type = FRW_EVENT_TYPE_WLAN_DTX;
        pst_tx_ctl->uc_event_sub_type = DMAC_TX_WLAN_DTX;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /*set the queue map id when wlan to wlan*/
        oal_skb_set_queue_mapping(pst_buf, WLAN_NORMAL_QUEUE);
#endif

        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_buf);

        /* 调用失败，自己调用自己释放netbuff内存 */
        if(OAL_SUCC != ul_ret)
        {
            hmac_free_netbuf_list(pst_buf);
        }

        pst_buf = pst_buf_tmp;
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 函 数 名  : hmac_delba_send_timeout
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_delba_send_timeout(oal_void *p_arg)
{
    hmac_vap_stru *pst_hmac_vap;
    mac_vap_stru  *pst_vap;
    oal_uint32 ui_val;

    pst_hmac_vap = (hmac_vap_stru *)p_arg;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{hmac_delba_send_timeout::p_arg is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap = &(pst_hmac_vap->st_vap_base_info);
    ui_val = oal_atomic_read(&pst_hmac_vap->ul_rx_unicast_pkt_to_lan);
    if(ui_val < 2)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_COEX, "{hmac_delba_send_timeout:delba send rx_pkt_below.this rx_pkt:%d}",ui_val);
        hmac_btcoex_delba_foreach_user(pst_vap);
    }

    oal_atomic_set(&pst_hmac_vap->ul_rx_unicast_pkt_to_lan,0);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_base_arp_delba
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void hmac_btcoex_arp_fail_delba(oal_netbuf_stru *pst_netbuf, hmac_vap_stru *pst_hmac_vap)
{

   oal_uint8              uc_data_type;

   /***************************************************************************/
   /*                      ARP Frame Format                                   */
   /* ----------------------------------------------------------------------- */
   /* |以太网目的地址|以太网源地址|帧类型|硬件类型|协议类型|硬件地址长度|     */
   /* ----------------------------------------------------------------------- */
   /* | 6            |6(待替换)   |2     |2       |2       |1           |     */
   /* ----------------------------------------------------------------------- */
   /* |协议地址长度|op|发送端以太网地址|发送端IP地址|目的以太网地址|目的IP地址*/
   /* ----------------------------------------------------------------------- */
   /* | 1          |2 |6(待替换)       |4           |6             |4         */
   /* ----------------------------------------------------------------------- */
   /*                                                                         */
   /***************************************************************************/

    /* 参数外面已经做检查，里面没必要再做检查了 */
    uc_data_type =  mac_get_data_type_from_8023((oal_uint8 *)oal_netbuf_data(pst_netbuf), MAC_NETBUFF_PAYLOAD_ETH);

    /* 发送方向创建定时器 */
    if((MAC_DATA_ARP_REQ == uc_data_type) && (OAL_FALSE == pst_hmac_vap->st_delba_opt_timer.en_is_registerd))
    {
        /* 每次重启定时器之前清零,保证统计的时间 */
        oal_atomic_set(&pst_hmac_vap->ul_rx_unicast_pkt_to_lan,0);

        FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_delba_opt_timer),
                   hmac_delba_send_timeout,
                   5000,
                   pst_hmac_vap,
                   OAL_FALSE,
                   OAM_MODULE_ID_HMAC,
                   pst_hmac_vap->st_vap_base_info.ul_core_id);


    }
}
#endif
#ifdef _PRE_WLAN_FEATURE_PROXYSTA

/*****************************************************************************
 函 数 名  : hmac_tx_proxysta_checksum
 功能描述  : 计算报文的校验和
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint16  hmac_tx_proxysta_checksum(oal_uint16   us_protocol,
                                                 oal_uint16   us_len,
                                                 oal_uint8    auc_src_addr[],
                                                 oal_uint8    auc_dest_addr[],
                                                 oal_uint16   us_addrleninbytes,
                                                 oal_uint8   *puc_buff)
{
    oal_uint16 us_pad = 0;
    oal_uint16 us_word16;
    oal_uint32 ul_sum = 0;
    oal_int    l_loop;

    if (us_len & 1)
    {
        us_len -= 1;
        us_pad  = 1;
    }

    for (l_loop = 0; l_loop < us_len; l_loop = l_loop + 2)
    {
        us_word16 = puc_buff[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + puc_buff[l_loop+1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    if (us_pad)
    {
        us_word16 = puc_buff[us_len];
        us_word16 <<= 8;
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_src_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_src_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }


    for (l_loop = 0; l_loop < us_addrleninbytes; l_loop = l_loop + 2)
    {
        us_word16 = auc_dest_addr[l_loop];
        us_word16 = (oal_uint16)((us_word16 << 8) + auc_dest_addr[l_loop + 1]);
        ul_sum = ul_sum + (oal_uint32)us_word16;
    }

    ul_sum = ul_sum + (oal_uint32)us_protocol + (oal_uint32)(us_len+us_pad);

    while (ul_sum >> 16)
    {
        ul_sum = (ul_sum & 0xFFFF) + (ul_sum >> 16);
    }

    ul_sum = ~ul_sum;

    return ((oal_uint16) ul_sum);
}

/*****************************************************************************
 函 数 名  : hmac_tx_proxysta_arp_mat
 功能描述  : arp包地址转换
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_tx_proxysta_arp_mat(mac_vap_stru *pst_mac_vap,
                                                      oal_uint8 *puc_eth_body,
                                                      oal_uint32 ul_pkt_len,
                                                      oal_uint32 ul_contig_len)
{
    oal_eth_arphdr_stru *pst_arp      = OAL_PTR_NULL;
    oal_uint8           *puc_arp_smac = OAL_PTR_NULL;

   /***************************************************************************/
   /*                      ARP Frame Format                                   */
   /* ----------------------------------------------------------------------- */
   /* |以太网目的地址|以太网源地址|帧类型|硬件类型|协议类型|硬件地址长度|     */
   /* ----------------------------------------------------------------------- */
   /* | 6            |6(待替换)   |2     |2       |2       |1           |     */
   /* ----------------------------------------------------------------------- */
   /* |协议地址长度|op|发送端以太网地址|发送端IP地址|目的以太网地址|目的IP地址*/
   /* ----------------------------------------------------------------------- */
   /* | 1          |2 |6(待替换)       |4           |6             |4         */
   /* ----------------------------------------------------------------------- */
   /*                                                                         */
   /***************************************************************************/

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_arp_mat::The input parameter of hmac_tx_proxysta_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += (oal_int32)OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_arp_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_eth_arphdr_stru.}");
        return OAL_FAIL;
    }

    /*lint -e778*/
    if ((ETHER_ADDR_LEN == pst_arp->uc_ar_hln) && (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_arp->us_ar_pro))
    {
        puc_arp_smac = pst_arp->auc_ar_sha;
    }
    /*lint +e778*/
    else
    {
        pst_arp = OAL_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_arp)
    {
        switch (OAL_NET2HOST_SHORT(pst_arp->us_ar_op))
        {
            case OAL_ARPOP_REQUEST:
            case OAL_ARPOP_REPLY:

            // 替换mac地址为out vap的mac地址
            oal_set_mac_addr(puc_arp_smac,  mac_mib_get_StationID(pst_mac_vap));
            break;
            default:
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                             "{hmac_tx_proxysta_arp_mat::do not replace arp addr.}");
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_tx_proxysta_ip_mat
 功能描述  : ip包地址转换
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_tx_proxysta_ip_mat(mac_vap_stru           *pst_mac_vap,
                                                     mac_ether_header_stru  *pst_ether_header,
                                                     oal_uint8              *puc_eth_body,
                                                     oal_uint32             ul_pkt_len,
                                                     oal_uint32             ul_contig_len)
{
    oal_ip_header_stru   *pst_ip_header   = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header  = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet = OAL_PTR_NULL;
    oal_uint8            *puc_scr_mac     = OAL_PTR_NULL;
    oal_uint16            us_ip_header_len;

    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |以太网头        |   IP头         | UDP头           |DHCP报文       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | 不定          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_ip_mat::The input parameter of hmac_tx_proxysta_dhcp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_ip_header =  (oal_ip_header_stru *)puc_eth_body;

    /*************************************************************************/
    /*                    IP头格式 (oal_ip_header_stru)                      */
    /* --------------------------------------------------------------------- */
    /* | 版本 | 报头长度 | 服务类型 | 总长度  |标识  |标志  |段偏移量
|      */
    /* --------------------------------------------------------------------- */
    /* | 4bits|  4bits   | 1        | 2       | 2    |3bits | 13bits  |      */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | 生存期 | 协议        | 头部校验和| 源地址（SrcIp）|目的地址（DstIp）*/
    /* --------------------------------------------------------------------- */
    /* | 1      |  1 (17为UDP)| 2         | 4              | 4               */
    /* --------------------------------------------------------------------- */
    /*************************************************************************/

    ul_contig_len += OAL_SIZEOF(oal_ip_header_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_ip_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ip_header_stru.}");
        return OAL_FAIL;
    }

    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* 如果是UDP */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);

        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_ip_mat::The length of buf is invalid.}");
            return OAL_FAIL;
        }

        /*************************************************************************/
        /*                      UDP 头 (oal_udp_header_stru)                     */
        /* --------------------------------------------------------------------- */
        /* |源端口号（SrcPort）|目的端口号（DstPort）| UDP长度    | UDP检验和  | */
        /* --------------------------------------------------------------------- */
        /* | 2                 | 2                   |2           | 2          | */
        /* --------------------------------------------------------------------- */
        /*                                                                       */
        /*************************************************************************/

        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */

/*lint -e778*/
/*lint -e572*/

        if (OAL_HOST2NET_SHORT(67)== pst_udp_header->dest)
        {
/*lint +e778*/
/*lint +e572*/

            /*************************************************************************/
            /*                    DHCP 报文格式 (oal_dhcp_packet_stru)               */
            /* --------------------------------------------------------------------- */
            /* | op | htpe | hlen | hops  |xid(事务IP)  |secs(秒数)   |flags(标志)|  */
            /* --------------------------------------------------------------------- */
            /* | 1  | 1    | 1    | 1     | 4           | 2           | 2          | */
            /* --------------------------------------------------------------------- */
            /* --------------------------------------------------------------------- */
            /* | ciaddr(4)客户ip地址 | yiaddr（4）你的IP地址 |siaddr(4)服务器IP地址| */
            /* --------------------------------------------------------------------- */
            /* | giaddr（4）中继代理IP地址      | chaddr（16）客户机硬件地址(待替换)|*/
            /* --------------------------------------------------------------------- */
            /* |sname（64）服务器的主机名|file（128）启动文件名|option（不定长）选项|*/
            /* --------------------------------------------------------------------- */
            /*************************************************************************/

            pst_dhcp_packet = (oal_dhcp_packet_stru *)(((oal_uint8 *)pst_udp_header) + OAL_SIZEOF(oal_udp_header_stru));

            ul_contig_len += OAL_SIZEOF(oal_dhcp_packet_stru);
            if (ul_pkt_len < ul_contig_len)
            {
                OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_ip_mat::The length of buf is invalid.}");
                return OAL_FAIL;
            }

            puc_scr_mac = pst_ether_header->auc_ether_shost;

            if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, pst_ether_header->auc_ether_shost))
            {
                /* 把UDP包中的地址替换为自己的地址 */
                oal_set_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap));

                /* 由于包内容已经被改写，所以要重新写UDP 帧的checksum */
                pst_udp_header->check = hmac_rx_proxysta_update_checksum_addr(pst_udp_header->check,
                                                                              puc_scr_mac,
                                                                              mac_mib_get_StationID(pst_mac_vap));
            }

        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_tx_proxysta_icmpv6_mat
 功能描述  : icmpv6包地址转换
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_tx_proxysta_icmpv6_mat(mac_vap_stru *pst_mac_vap,
                                                           oal_uint8 *puc_eth_body,
                                                           oal_uint32 ul_pkt_len,
                                                           oal_uint32 ul_contig_len)
{
    oal_ipv6hdr_stru          *pst_ipv6hdr          = OAL_PTR_NULL;
    oal_icmp6hdr_stru         *pst_icmp6hdr         = OAL_PTR_NULL;
    oal_eth_icmp6_lladdr_stru *pst_eth_icmp6_lladdr = OAL_PTR_NULL;
    oal_uint16                 us_icmp6len;
    oal_bool_enum_uint8        en_packet_changed = OAL_TRUE;
    oal_uint16                 us_check_sum = 0;

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_eth_body))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_icmpv6_mat::The input parameter of hmac_tx_proxysta_icmpv6_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    pst_ipv6hdr = (oal_ipv6hdr_stru *)puc_eth_body;

    ul_contig_len += OAL_SIZEOF(oal_ipv6hdr_stru);
    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_icmpv6_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ipv6hdr_stru.  ul_pkt_len[%d], ul_contig_len[%d]}", ul_pkt_len, ul_contig_len);
        return OAL_FAIL;
    }

    if (OAL_IPPROTO_ICMPV6 == pst_ipv6hdr->nexthdr)
    {
        pst_icmp6hdr = (oal_icmp6hdr_stru *)(pst_ipv6hdr + 1);
        us_icmp6len  = pst_ipv6hdr->payload_len;

        ul_contig_len += OAL_SIZEOF(oal_icmp6hdr_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_icmpv6_mat::The length of buf is invalid.}");
            return OAL_FAIL;
        }

        /*
         * It seems that we only have to modify IPv6 packets being
         * sent by a Proxy STA. Both the solicitation and advertisement
         * packets have the STA's OMA. Flip that to the VMA.
        */
        switch (pst_icmp6hdr->icmp6_type)
        {
            case OAL_NDISC_NEIGHBOUR_SOLICITATION:
            case OAL_NDISC_NEIGHBOUR_ADVERTISEMENT:
            {
                ul_contig_len += OAL_IPV6_MAC_ADDR_LEN;
                /* 不存在IcmpV6 option,源地址不存在，不需要转换 */
                if (ul_pkt_len == ul_contig_len)
                {
                    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                          "{hmac_tx_proxysta_icmpv6_mat::No source addr.}");
                    return OAL_SUCC;
                }

                /* 存在源地址，进行转换 */
                ul_contig_len += OAL_SIZEOF(oal_eth_icmp6_lladdr_stru);
                if (ul_pkt_len < ul_contig_len)
                {
                    OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_icmpv6_mat ABNORMAL::The length of buf is invalid ul_pkt_len[%d], ul_contig_len[%d] icmp6_type[%d].}", ul_pkt_len, ul_contig_len, pst_icmp6hdr->icmp6_type);
                    return OAL_FAIL;
                }

                pst_eth_icmp6_lladdr = (oal_eth_icmp6_lladdr_stru *)((oal_uint8 *)(pst_icmp6hdr + 1) + 16);

                /* 替换地址 */
                oal_set_mac_addr(pst_eth_icmp6_lladdr->uc_addr, mac_mib_get_StationID(pst_mac_vap));

                us_check_sum = hmac_tx_proxysta_checksum((oal_uint16)OAL_IPPROTO_ICMPV6,us_icmp6len,
                                   pst_ipv6hdr->saddr.s6_addr, pst_ipv6hdr->daddr.s6_addr,16,(oal_uint8 *)pst_icmp6hdr);

                pst_icmp6hdr->icmp6_cksum = OAL_HOST2NET_SHORT(us_check_sum);
                break;
            }
            case OAL_NDISC_ROUTER_SOLICITATION:
            {
                ul_contig_len += OAL_SIZEOF(oal_eth_icmp6_lladdr_stru);
                if (ul_pkt_len < ul_contig_len)
                {
                    OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_tx_proxysta_icmpv6_mat::The length of buf is invalid.}");
                    return OAL_FAIL;
                }

                /* replace the HW address with the VMA */
                pst_eth_icmp6_lladdr =(oal_eth_icmp6_lladdr_stru *)((oal_uint8 *)(pst_icmp6hdr + 1));
                break;
            }
            default:
                en_packet_changed = OAL_FALSE;
                break;
        }

        if ((OAL_TRUE == en_packet_changed) && (OAL_PTR_NULL != pst_eth_icmp6_lladdr))
        {
            oal_set_mac_addr(pst_eth_icmp6_lladdr->uc_addr, pst_mac_vap->auc_bssid);
            us_check_sum = hmac_tx_proxysta_checksum((oal_uint16)OAL_IPPROTO_ICMPV6, us_icmp6len,
                               pst_ipv6hdr->saddr.s6_addr, pst_ipv6hdr->daddr.s6_addr,16,(oal_uint8 *)pst_icmp6hdr);

            pst_icmp6hdr->icmp6_cksum = OAL_HOST2NET_SHORT(us_check_sum);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_tx_proxysta_mat
 功能描述  : ARP、DHCP、ICMPv6等包的地址转换 发送前地址转换函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_proxysta_mat(oal_netbuf_stru *pst_buf, mac_vap_stru *pst_mac_vap)
{
    mac_ether_header_stru  *pst_ether_header;
    oal_uint8              *puc_eth_body;
    oal_uint16              us_ether_type;
    oal_uint8              *puc_scr_mac;
    oal_uint32              ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    oal_uint32              ul_pkt_len;
    oal_uint32              ul_ret = OAL_SUCC;

    /* 参数合法性检查 */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_buf) || (OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_mat::The input parameter of hmac_tx_proxysta_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    /* 参数合法性检查后，获取pst_buf的长度 */
    ul_pkt_len = OAL_NETBUF_LEN(pst_buf);

    /* 如果不是sta，不需要地址转换 */
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        return OAL_SUCC;
    }

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_tx_proxysta_mat::The length of buf is invalid.}");
        return OAL_FAIL;
    }

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    us_ether_type = pst_ether_header->us_ether_type;
    puc_scr_mac   = pst_ether_header->auc_ether_shost;

    if (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == us_ether_type)
    {
        return OAL_SUCC;
    }

    /* ARP包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP)  == us_ether_type)
    {
        ul_ret = hmac_tx_proxysta_arp_mat(pst_mac_vap, puc_eth_body, ul_pkt_len, ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_mat::hmac_tx_proxysta_arp_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

/*lint -e778*/
    /*DHCP 包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
    {
/*lint +e778*/
        ul_ret = hmac_tx_proxysta_ip_mat(pst_mac_vap,
                                         pst_ether_header,
                                         puc_eth_body,
                                         ul_pkt_len,
                                         ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_mat::hmac_tx_proxysta_dhcp_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

    /*icmpv6 包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
    {
        ul_ret = hmac_tx_proxysta_icmpv6_mat(pst_mac_vap, puc_eth_body, ul_pkt_len, ul_contig_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_tx_proxysta_mat::hmac_tx_proxysta_icmpv6_mat return value is %d.}", ul_ret);
            return ul_ret;
        }
    }

    oal_set_mac_addr(puc_scr_mac, mac_mib_get_StationID(pst_mac_vap));

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : hmac_tx_lan_to_wlan_tcp_opt
 功能描述  : hmac AP模式 处理HOST DRX事件，注册到事件管理模块中
             PAYLOAD是一个NETBUF
 输入参数  : pst_vap: vap指针
             pst_buf: netbuf指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_tx_lan_to_wlan(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    oal_uint32             ul_ret = HMAC_TX_PASS;
#ifdef _PRE_WLAN_TCP_OPT
    hmac_device_stru    *pst_hmac_device;
    hmac_vap_stru         *pst_hmac_vap;     /* VAP结构体 */

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_lan_to_wlan_tcp_opt::pst_dmac_vap null.}\r\n");
        return OAL_FAIL;
    }
    pst_hmac_device = hmac_res_get_mac_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan_tcp_opt::pst_hmac_device null.}\r\n");
        return OAL_FAIL;
    }
    if(OAL_TRUE == pst_hmac_device->sys_tcp_tx_ack_opt_enable)
    {
        ul_ret = hmac_transfer_tx_handler(pst_hmac_device,pst_hmac_vap,pst_buf);
    }
    else
 #endif
    {
        ul_ret = hmac_tx_lan_to_wlan_no_tcp_opt(pst_vap, pst_buf);
    }
    return ul_ret;
}

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_uint8 g_tx_debug = 0;

oal_uint32 hmac_tx_data(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru        *pst_vap = &(pst_hmac_vap->st_vap_base_info);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru     *pst_mac_device;
#endif
    oal_uint32           ul_ret;

    if(g_tx_debug)
    {
       OAL_IO_PRINT("hmac_tx_data start\n");
    }

#ifdef _PRE_WLAN_CHIP_TEST
    if (OAL_SWITCH_ON == pst_vap->bit_al_tx_flag)
    {
        OAM_INFO_LOG0(0, OAM_SF_TX, "{hmac_tx_data::the vap alway tx!}\r\n");
        oal_netbuf_free(pst_netbuf);
        return OAL_NETDEV_TX_OK;
    }
#endif

    /* 将以太网过来的帧上报SDT */
    hmac_tx_report_eth_frame(pst_vap, pst_netbuf);
#if 0
#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_TRUE == pst_vap->st_vap_dft.ul_flg && OAL_PTR_NULL != pst_vap->st_vap_dft.pst_vap_dft_stats)
    {
        MAC_VAP_STATS_PKT_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_pkts, 1);
        MAC_VAP_STATS_BYTE_INCR(pst_vap->st_vap_dft.pst_vap_dft_stats->ul_lan_tx_bytes,
                                OAL_NETBUF_LEN(pst_netbuf) - ETHER_HDR_LEN);
    }
#endif
#endif
    /* 考虑VAP状态与控制面互斥，需要加锁保护 */
    //oal_spin_lock(&pst_vap->st_lock_state);

     /* 判断VAP的状态，如果没有UP，则丢弃报文 */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_vap->en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state))))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_data::vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n", pst_vap->en_vap_state);

        oal_netbuf_free(pst_netbuf);

        //oal_spin_unlock(&pst_vap->st_lock_state);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, tx_abnormal_msdu_dropped, 1);

        return OAL_NETDEV_TX_OK;
    }

    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;
    OAL_NETBUF_PREV(pst_netbuf) = OAL_PTR_NULL;

    OAL_MEMZERO(OAL_NETBUF_CB(pst_netbuf), OAL_NETBUF_CB_SIZE());

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_tx_data::mac_res_get_dev is null!}");
        oal_netbuf_free(pst_netbuf);
        //oal_spin_unlock(&pst_vap->st_lock_state);

        return OAL_NETDEV_TX_OK;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* ARP、DHCP、ICMPv6等数据包的地址转换 (只有proxy STA的发送的包才需要地址转换)*/
        if ((OAL_TRUE == pst_vap->st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            ul_ret = hmac_tx_proxysta_mat(pst_netbuf, pst_vap);

            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_tx_data::hmac_tx_proxysta_mat fail.}");
                oal_netbuf_free(pst_netbuf);
                //oal_spin_unlock(&pst_vap->st_lock_state);

                return OAL_NETDEV_TX_OK;
            }
        }
    }

#endif

    ul_ret = hmac_tx_lan_to_wlan(pst_vap, pst_netbuf);

    /* 调用失败，要释放内核申请的netbuff内存池 */
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        hmac_free_netbuf_list(pst_netbuf);
    }

    //oal_spin_unlock(&pst_vap->st_lock_state);

    return OAL_NETDEV_TX_OK;
}

oal_uint32 hmac_tx_post_event(mac_vap_stru *pst_mac_vap)
{
    oal_uint32              ul_ret;
    frw_event_stru          *pst_event;
    frw_event_mem_stru      *pst_event_mem;
    hmac_vap_stru           *pst_hmac_vap;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    /* tx_event_num减1后等于0表示eth to wlan数据事件为空，可以申请事件。同时这个方案能确保每次只有一个事件入队并处理，防止存在两个以上事件申请入队 */
    if(oal_atomic_dec_and_test(&(pst_hmac_vap->ul_tx_event_num)))
    {
        /* 申请事件内存 */
        pst_event_mem = FRW_EVENT_ALLOC(0);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
        {
            oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num)); /* 事件申请失败，tx_event_num要加回去，恢复成默认值1 */
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::pst_event_mem null.}");
            OAL_IO_PRINT("Hmac_tx_post_event fail to alloc event mem\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        /* 填写事件 */
        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                           FRW_EVENT_TYPE_HOST_DRX,
                           HMAC_TX_HOST_DRX,
                           0,
                           FRW_EVENT_PIPELINE_STAGE_0,
                           pst_mac_vap->uc_chip_id,
                           pst_mac_vap->uc_device_id,
                           pst_mac_vap->uc_vap_id);


        /* 抛事入队列 */
        ul_ret = frw_event_post_event(pst_event_mem,pst_mac_vap->ul_core_id);
        if (OAL_SUCC != ul_ret)
        {
            oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num)); /* 事件入队失败，tx_event_num要加回去，恢复成默认值1 */
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::frw_event_dispatch_event failed[%d].}", ul_ret);
            OAL_IO_PRINT("{hmac_tx_post_event::frw_event_dispatch_event failed}\n");
        }

        /* 释放事件内存 */
        FRW_EVENT_FREE(pst_event_mem);
    }
    else
    {
        /* 事件队列中已经有事件要处理(tx_event_num值为0)，这个时候预先减去的值要加回去，tx_event_num要恢复成0 */
        oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num));

        if(g_tx_debug)
        {
            /* 增加维测信息，把tx_event_num的值打印出来，如果此时的值不为0，就属于异常(不申请事件，但是值又不为0) */
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_post_event::tx_event_num value is [%d].}", (oal_int32)oal_atomic_read(&(pst_hmac_vap->ul_tx_event_num)));
            OAL_IO_PRINT("do not post tx event, data in queue len %d,out queue len %d\n",
                            OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_in_queue_id]),
                            OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]));
        }
    }

    return OAL_SUCC;
}

OAL_STATIC oal_uint8 hmac_vap_user_is_bw_limit(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_ether_header_stru   *pst_ether_hdr; /* 以太网头 */
    oal_uint16               us_user_idx;
    hmac_user_stru          *pst_hmac_user;
    oal_uint32               ul_ret;

    pst_ether_hdr   = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
    ul_ret = mac_vap_find_user_by_macaddr(pst_vap, pst_ether_hdr->auc_ether_dhost, &us_user_idx);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return OAL_FALSE;
    }
    pst_hmac_user    = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return (pst_vap->bit_vap_bw_limit || pst_hmac_user->en_user_bw_limit);
}

oal_uint32  hmac_tx_event_process(oal_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hmac_vap_stru           *pst_hmac_vap;
    oal_uint32               ul_work = 0;
    oal_uint32               ul_reschedule = OAL_TRUE;
	oal_netbuf_stru         *pst_netbuf;

    /* 入参判断 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_event_mem null.}");
        OAL_BUG_ON(1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_event null.}");
        OAL_BUG_ON(1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if(OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{hmac_tx_event_process::pst_hmac_vap null.}");
        OAL_BUG_ON(1);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if(g_tx_debug)
        OAL_IO_PRINT("hmac_tx_event_process start\n");

    /* 事件申请时在hmac_tx_post_event处理时已经减为了0，这里要加回去，恢复成1 */
    oal_atomic_inc(&(pst_hmac_vap->ul_tx_event_num));

    if(g_tx_debug)
        OAL_IO_PRINT("oal_atomic_dec OK\n");

    oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
    if(0 == OAL_NETBUF_LIST_NUM(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]))
    {
        /*如果当前out queue空了, 才切换out_queue_id*/
        pst_hmac_vap->uc_in_queue_id = pst_hmac_vap->uc_out_queue_id;
        pst_hmac_vap->uc_out_queue_id = (pst_hmac_vap->uc_out_queue_id + 1) & 1;

    }
    oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);

	do
	{
        oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
        pst_netbuf = OAL_NETBUF_DEQUEUE(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id]);
        oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);

		if (!pst_netbuf)
		{
    		if(g_tx_debug)
                OAL_IO_PRINT("OAL_NETBUF_DEQUEUE OK\n");
            ul_reschedule = OAL_FALSE;
			break;
	    }

        if(OAL_TRUE == hmac_vap_user_is_bw_limit(&(pst_hmac_vap->st_vap_base_info), pst_netbuf))
        {
            /* 增加维测信息，出现用户和vap限速之后，也会造成用户关连不上，ping不通问题 */
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_event_process::vap id[%d] hmac_vap_user_is_bw_limit.}", pst_hmac_vap->st_vap_base_info.uc_vap_id);
            oal_spin_lock_bh(&pst_hmac_vap->st_smp_lock);
            OAL_NETBUF_QUEUE_TAIL(&pst_hmac_vap->st_tx_queue_head[pst_hmac_vap->uc_out_queue_id], pst_netbuf);
            oal_spin_unlock_bh(&pst_hmac_vap->st_smp_lock);
            continue;
        }

        hmac_tx_data(pst_hmac_vap,pst_netbuf);

	} while(++ul_work < pst_hmac_vap->ul_tx_quata); // && jiffies == ul_start_time

	if(OAL_TRUE == ul_reschedule)
	{
        hmac_tx_post_event(&(pst_hmac_vap->st_vap_base_info));
	}

	return OAL_SUCC;


}
#endif

/*****************************************************************************
 函 数 名  : hmac_tx_ba_cnt_vary
 功能描述  : 发5个包建立聚合 改为 发5个"连续"的大包建立聚合 51暂时不变
             因考虑不连续的包即使建立BA,发的也是单包聚合,意义并不大。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_void hmac_tx_ba_cnt_vary(
                       hmac_vap_stru   *pst_hmac_vap,
                       hmac_user_stru  *pst_hmac_user,
                       oal_uint8        uc_tidno,
                       oal_netbuf_stru *pst_buf)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32             ul_current_timestamp;
    oal_uint32             ul_runtime;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(OAL_TRUE == oal_netbuf_is_tcp_ack((oal_ip_header_stru *)(oal_netbuf_data(pst_buf) + ETHER_HDR_LEN)))
    {
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
        return ;
    }
#endif

    if (0 == pst_hmac_user->auc_ba_flag[uc_tidno])
    {
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
        pst_hmac_user->aul_last_timestamp[uc_tidno] = (oal_uint32)OAL_TIME_GET_STAMP_MS();

        return ;
    }

    ul_current_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(ul_current_timestamp, pst_hmac_user->aul_last_timestamp[uc_tidno]);

    if ((oal_netbuf_get_len(pst_buf) <= WLAN_MSDU_MAX_LEN && WLAN_BA_CNT_INTERVAL < ul_runtime)||
         (oal_netbuf_get_len(pst_buf) > WLAN_MSDU_MAX_LEN && WLAN_BA_CNT_INTERVAL > ul_runtime))
    {
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
    }
    else
    {
        pst_hmac_user->auc_ba_flag[uc_tidno] = 0;
    }

    pst_hmac_user->aul_last_timestamp[uc_tidno] = (oal_uint32)OAL_TIME_GET_STAMP_MS();
#else
    pst_hmac_user->auc_ba_flag[uc_tidno]++;
#endif
}


/*lint -e19*/
oal_module_symbol(hmac_tx_wlan_to_wlan_ap);
oal_module_symbol(hmac_tx_lan_to_wlan);
oal_module_symbol(hmac_free_netbuf_list);

oal_module_symbol(hmac_tx_report_eth_frame);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
oal_module_symbol(hmac_tx_proxysta_mat);
#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(g_tx_debug);
oal_module_symbol(hmac_tx_post_event);
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

