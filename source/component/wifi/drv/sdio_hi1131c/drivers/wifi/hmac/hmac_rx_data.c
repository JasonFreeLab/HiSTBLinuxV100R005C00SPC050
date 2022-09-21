/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_rx_data.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : DMAC模块接收帧的公共操作函数以及数据帧的操作函数定义的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月20日
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
#include "oal_profiling.h"
#include "mac_frame.h"
#include "mac_data.h"
#include "hmac_rx_data.h"
#include "dmac_ext_if.h"
#include "hmac_vap.h"
#include "hmac_ext_if.h"
#include "oam_ext_if.h"
#include "oal_ext_if.h"
#include "oal_net.h"
#include "hmac_frag.h"
#include "hmac_11i.h"
#include "mac_vap.h"
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#include "hmac_custom_security.h"
#endif
#ifdef _PRE_WLAN_FEATURE_MCAST
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif
#include "hmac_blockack.h"
#include "hmac_tcp_opt.h"

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RX_DATA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT) || (_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT))

/*5610适配， 快速转发功能*/
typedef oal_void (*p_hisi_fp_func)(oal_netbuf_stru *skb, oal_net_device_stru *dev);

OAL_STATIC p_hisi_fp_func g_p_hisi_fp_func = NULL;

oal_void hisi_wifi_dev_recv_reg(p_hisi_fp_func p_func)
{
    g_p_hisi_fp_func = p_func;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(hisi_wifi_dev_recv_reg);
/*lint +e578*//*lint +e19*/

#elif (_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT)  //暂时复用EVB的，后面再咨询产品一起调试
/*5610适配， 快速转发功能*/
typedef oal_void (*p_hisi_fp_func)(oal_netbuf_stru *skb, oal_net_device_stru *dev);

OAL_STATIC p_hisi_fp_func g_p_hisi_fp_func = NULL;

oal_void hisi_wifi_dev_recv_reg(p_hisi_fp_func p_func)
{
    g_p_hisi_fp_func = p_func;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(hisi_wifi_dev_recv_reg);
/*lint +e578*//*lint +e19*/
#elif (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)

extern void (*g_pv_wifi_callback)(struct sk_buff *skb, struct net_device *dev);

#endif
#endif

/*****************************************************************************
 函 数 名  : hmac_rx_report_eth_frame
 功能描述  : 将要送往以太网的帧上报给SDT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
oal_void  hmac_rx_report_eth_frame(mac_vap_stru   *pst_mac_vap,
                                                      oal_netbuf_stru *pst_netbuf)
{
    oal_uint16              us_user_idx = 0;
    mac_ether_header_stru  *pst_ether_hdr = OAL_PTR_NULL;
    oal_uint32              ul_ret;
    oal_uint8               auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0};
    oal_switch_enum_uint8   en_eth_switch = 0;
#if 0 //def _PRE_WLAN_DFT_STAT
    hmac_vap_stru           *pst_hmac_vap;
#endif

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return;
    }

    /* 将skb的data指针指向以太网的帧头 */
    oal_netbuf_push(pst_netbuf, ETHER_HDR_LEN);
#if 0 //def _PRE_WLAN_DFT_STAT
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
#endif
    /* 增加统计信息 */
    //HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_pkt_to_lan,1);
    //HMAC_VAP_DFT_STATS_PKT_INCR(pst_hmac_vap->st_query_stats.ul_rx_bytes_to_lan,OAL_NETBUF_LEN(pst_netbuf));
    //OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, rx_pkt_to_lan, 1);                           /* 增加发往LAN的帧的数目 */
    //OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, rx_bytes_to_lan, OAL_NETBUF_LEN(pst_netbuf));/* 增加发送LAN的字节数 */

    /* 获取目的用户资源池id */
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{hmac_rx_report_eth_frame::pst_ether_hdr null.}");
            oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);
            return;
        }

        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_ether_hdr->auc_ether_shost, &us_user_idx);
        if (OAL_ERR_CODE_PTR_NULL == ul_ret)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{hmac_rx_report_eth_frame::ul_ret null.}");
            oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);
            return;
        }

        if (OAL_FAIL == ul_ret)
        {
            oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);
            return;
        }

        oal_set_mac_addr(auc_user_macaddr, pst_ether_hdr->auc_ether_shost);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        if (0 == pst_mac_vap->us_user_nums)
        {
            oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);
            /* SUCC , return */
            return;
        }

        us_user_idx = pst_mac_vap->uc_assoc_vap_id;
        oal_set_mac_addr(auc_user_macaddr, pst_mac_vap->auc_bssid);
    }

    ul_ret = oam_report_eth_frame_get_switch(us_user_idx, OAM_OTA_FRAME_DIRECTION_TYPE_RX, &en_eth_switch);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{hmac_rx_report_eth_frame::oam_report_eth_frame_get_switch failed[%d].}", ul_ret);
        oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);
        return;
    }

    if (OAL_SWITCH_ON == en_eth_switch)
    {
        /* 将要送往以太网的帧上报 */
        ul_ret = oam_report_eth_frame(auc_user_macaddr,
                             oal_netbuf_data(pst_netbuf),
                             (oal_uint16)OAL_NETBUF_LEN(pst_netbuf),
                             OAM_OTA_FRAME_DIRECTION_TYPE_RX);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{hmac_rx_report_eth_frame::oam_report_eth_frame return err: 0x%x.}\r\n", ul_ret);
        }
    }

    oal_netbuf_pull(pst_netbuf, ETHER_HDR_LEN);

}
#endif

/*****************************************************************************
 函 数 名  : hmac_rx_frame_80211_to_eth
 功能描述  : 将MSDU转化为以太网格式的帧
 输入参数  : pst_netbuf : 指向含有MSDU的netbuf的指针
             puc_da     : 目的地址
             puc_sa     : 源地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_rx_frame_80211_to_eth(
                                    oal_netbuf_stru     *pst_netbuf,
                                    oal_uint8           *puc_da,
                                    oal_uint8           *puc_sa)
{
    mac_ether_header_stru              *pst_ether_hdr;
    mac_llc_snap_stru                  *pst_snap;
    oal_uint16                          us_ether_type;

    pst_snap = (mac_llc_snap_stru *)oal_netbuf_data(pst_netbuf);
    us_ether_type = pst_snap->us_ether_type;

    /* 将payload向前扩充6个字节，加上后面8个字节的snap头空间，构成以太网头的14字节空间 */
    oal_netbuf_push(pst_netbuf, HMAC_RX_DATA_ETHER_OFFSET_LENGTH);
    pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);

    pst_ether_hdr->us_ether_type = us_ether_type;
    oal_set_mac_addr(pst_ether_hdr->auc_ether_shost, puc_sa);
    oal_set_mac_addr(pst_ether_hdr->auc_ether_dhost, puc_da);
}

/*****************************************************************************
 函 数 名  : hmac_rx_free_netbuf_list
 功能描述  : 释放指定个数的netbuf
 输入参数  : (1)期望删除的netbuf的起始指针
             (2)需要删除的netbuf的个数
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_free_netbuf(oal_netbuf_stru *pst_netbuf, oal_uint16 us_nums)
{
    oal_netbuf_stru    *pst_netbuf_temp;
    oal_uint16           us_netbuf_num;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_free_netbuf::pst_netbuf null.}\r\n");
        return;
    }

    for (us_netbuf_num = us_nums; us_netbuf_num > 0; us_netbuf_num--)
    {
        pst_netbuf_temp = OAL_NETBUF_NEXT(pst_netbuf);

        /* 减少netbuf对应的user引用计数 */
        oal_netbuf_free(pst_netbuf);

        pst_netbuf = pst_netbuf_temp;

        if (OAL_PTR_NULL == pst_netbuf)
        {
            if (OAL_UNLIKELY(us_netbuf_num != 1))
            {
                OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_rx_free_netbuf::pst_netbuf list broken, us_netbuf_num[%d]us_nums[%d].}", us_netbuf_num, us_nums);
                return;
            }

            break;
        }
    }

}

/*****************************************************************************
 函 数 名  : hmac_rx_free_netbuf_list
 功能描述  : for list
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
oal_void  hmac_rx_free_netbuf_list(oal_netbuf_head_stru *pst_netbuf_hdr, oal_uint16 uc_num_buf)
{
    oal_netbuf_stru   *pst_netbuf;
    oal_uint16         us_idx;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf_hdr))
    {
        OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_rx_free_netbuf_list::pst_netbuf null.}");
        return;
    }

    OAM_INFO_LOG1(0, OAM_SF_RX, "{hmac_rx_free_netbuf_list::free [%d].}", uc_num_buf);

    for (us_idx = uc_num_buf; us_idx > 0; us_idx--)
    {
        pst_netbuf = oal_netbuf_delist(pst_netbuf_hdr);
        if (OAL_PTR_NULL != pst_netbuf)
        {
            OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_rx_free_netbuf_list::pst_netbuf null.}");
            oal_netbuf_free(pst_netbuf);
        }
    }

}

/*****************************************************************************
 函 数 名  : hmac_rx_transmit_to_wlan
 功能描述  : 将数据帧发送到WLAN侧的接口函数，将一个netbuf链抛给发送流程，每个
             netbuf的内容都是一个以太网格式的MSDU
 输入参数  : (1)指向事件头的指针
             (2)指向需要发送的netbuf的第一个元素的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2016年06月20日
    作    者   :  
    修改内容   : :修改wlan to wlan 数据转发为直接发送，不需要抛事件

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_rx_transmit_to_wlan(
                frw_event_hdr_stru   *pst_event_hdr,
                oal_netbuf_head_stru *pst_netbuf_head)
{
    oal_netbuf_stru            *pst_netbuf;         /* 从netbuf链上取下来的指向netbuf的指针 */
    oal_uint32                  ul_netbuf_num;
    oal_uint32                  ul_ret;
    oal_netbuf_stru            *pst_buf_tmp;        /* 暂存netbuf指针，用于while循环 */
    mac_tx_ctl_stru            *pst_tx_ctl;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_event_hdr) || (OAL_PTR_NULL == pst_netbuf_head)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_rx_transmit_to_wlan::param null, %d %d.}", pst_event_hdr, pst_netbuf_head);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取链头的net buffer */
    pst_netbuf = oal_netbuf_peek(pst_netbuf_head);

    /* 获取mac vap 结构 */
    ul_ret = hmac_tx_get_mac_vap(pst_event_hdr->uc_vap_id, &pst_mac_vap);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        ul_netbuf_num = oal_netbuf_list_len(pst_netbuf_head);
        hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)ul_netbuf_num);
        OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{hmac_rx_transmit_to_wlan::find vap [%d] failed[%d], free [%d] netbuffer.}",
                        pst_event_hdr->uc_vap_id, ul_ret, ul_netbuf_num);
        return ul_ret;
    }

    /* 循环处理每一个netbuf，按照以太网帧的方式处理 */
    while (OAL_PTR_NULL != pst_netbuf)
    {
        pst_buf_tmp = OAL_NETBUF_NEXT(pst_netbuf);

        OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;
        OAL_NETBUF_PREV(pst_netbuf) = OAL_PTR_NULL;

        pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
        OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));

        pst_tx_ctl->en_event_type = FRW_EVENT_TYPE_WLAN_DTX;
        pst_tx_ctl->uc_event_sub_type = DMAC_TX_WLAN_DTX;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /*set the queue map id when wlan to wlan*/
        oal_skb_set_queue_mapping(pst_netbuf, WLAN_NORMAL_QUEUE);
#endif

        ul_ret = hmac_tx_lan_to_wlan(pst_mac_vap, pst_netbuf);

        /* 调用失败，自己调用自己释放netbuff内存 */
        if(OAL_SUCC != ul_ret)
        {
            hmac_free_netbuf_list(pst_netbuf);
        }

        pst_netbuf = pst_buf_tmp;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_parse_amsdu
 功能描述  : 解析出每一个AMSDU中的MSDU
 输入参数  : 指向MPDU的第一个netbuf的指针
 输出参数  : (1)指向当前要转发的MSDU的指针
             (2)用于记录处理当前的MPDU中MSDU的信息
             (3)当前MPDU的处理状态:标识该MPDU是否处理完成
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_rx_parse_amsdu(
                oal_netbuf_stru                    *pst_netbuf,
                dmac_msdu_stru                     *pst_msdu,
                dmac_msdu_proc_state_stru          *pst_msdu_state,
                mac_msdu_proc_status_enum_uint8    *pen_proc_state)
{
    hmac_rx_ctl_stru       *pst_rx_ctrl;                            /* MPDU的控制信息 */
    oal_uint8              *puc_buffer_data_addr    = OAL_PTR_NULL; /* 指向netbuf数据域的指针 */
    oal_uint16              us_offset               = 0;            /* submsdu相对于data指针的偏移 */
    oal_uint16              us_submsdu_len          = 0;            /* submsdu的长度 */
    oal_uint8               uc_submsdu_pad_len      = 0;            /* submsdu的填充长度 */
    oal_uint8              *puc_submsdu_hdr         = OAL_PTR_NULL; /* 指向submsdu头部的指针 */
    oal_netbuf_stru        *pst_netbuf_prev;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_parse_amsdu::pst_netbuf null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 首次进入该函数解析AMSDU */
    if ((0 == pst_msdu_state->uc_procd_netbuf_nums)
     && (0 == pst_msdu_state->uc_procd_msdu_in_netbuf))
    {
        pst_msdu_state->pst_curr_netbuf      = pst_netbuf;

        /* AMSDU时，首个netbuf的中包含802.11头，对应的payload需要偏移 */
        pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_msdu_state->pst_curr_netbuf);

        pst_msdu_state->puc_curr_netbuf_data   = (oal_uint8*)(pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr) + pst_rx_ctrl->st_rx_info.uc_mac_header_len;
        pst_msdu_state->uc_netbuf_nums_in_mpdu = pst_rx_ctrl->st_rx_info.bit_buff_nums;
        pst_msdu_state->uc_msdu_nums_in_netbuf = pst_rx_ctrl->st_rx_info.uc_msdu_in_buffer;
        pst_msdu_state->us_submsdu_offset      = 0;
    }

    /* 获取submsdu的头指针 */
    puc_buffer_data_addr = pst_msdu_state->puc_curr_netbuf_data;
    us_offset            = pst_msdu_state->us_submsdu_offset;
    puc_submsdu_hdr      = puc_buffer_data_addr + us_offset;

    /* 获取submsdu的相关信息 */
    mac_get_submsdu_len(puc_submsdu_hdr, &us_submsdu_len);
    mac_get_submsdu_pad_len(MAC_SUBMSDU_HEADER_LEN + us_submsdu_len, &uc_submsdu_pad_len);
    oal_set_mac_addr(pst_msdu->auc_sa, (puc_submsdu_hdr + MAC_SUBMSDU_SA_OFFSET));
    oal_set_mac_addr(pst_msdu->auc_da, (puc_submsdu_hdr + MAC_SUBMSDU_DA_OFFSET));

    /* 针对当前的netbuf，申请新的subnetbuf，并设置对应的netbuf的信息，赋值给对应的msdu */
    pst_msdu->pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (MAC_SUBMSDU_HEADER_LEN + us_submsdu_len + uc_submsdu_pad_len), OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_msdu->pst_netbuf)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_parse_amsdu::pst_netbuf null.}");
        OAM_STAT_VAP_INCR(0, rx_no_buff_dropped, 1);
        return OAL_FAIL;
    }

    OAL_MEM_NETBUF_TRACE(pst_msdu->pst_netbuf, OAL_TRUE);

    /* 针对每一个子msdu，修改netbuf的end、data、tail、len指针 */
    oal_netbuf_put(pst_msdu->pst_netbuf, us_submsdu_len + HMAC_RX_DATA_ETHER_OFFSET_LENGTH);
    oal_netbuf_pull(pst_msdu->pst_netbuf, HMAC_RX_DATA_ETHER_OFFSET_LENGTH);
    oal_memcopy(pst_msdu->pst_netbuf->data, (puc_submsdu_hdr + MAC_SUBMSDU_HEADER_LEN), us_submsdu_len);

    /* 增加当前已处理的msdu的个数 */
    pst_msdu_state->uc_procd_msdu_in_netbuf++;

    /* 获取当前的netbuf中的下一个msdu进行处理 */
    if (pst_msdu_state->uc_procd_msdu_in_netbuf < pst_msdu_state->uc_msdu_nums_in_netbuf)
    {
        pst_msdu_state->us_submsdu_offset += us_submsdu_len + uc_submsdu_pad_len + MAC_SUBMSDU_HEADER_LEN;
    }
    else if (pst_msdu_state->uc_procd_msdu_in_netbuf == pst_msdu_state->uc_msdu_nums_in_netbuf)
    {
        pst_msdu_state->uc_procd_netbuf_nums++;

        pst_netbuf_prev = pst_msdu_state->pst_curr_netbuf;

        /* 获取该MPDU对应的下一个netbuf的内容 */
        if (pst_msdu_state->uc_procd_netbuf_nums < pst_msdu_state->uc_netbuf_nums_in_mpdu)
        {
            pst_msdu_state->pst_curr_netbuf      = OAL_NETBUF_NEXT(pst_msdu_state->pst_curr_netbuf);
            pst_msdu_state->puc_curr_netbuf_data = oal_netbuf_data(pst_msdu_state->pst_curr_netbuf);

            pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_msdu_state->pst_curr_netbuf);

            pst_msdu_state->uc_msdu_nums_in_netbuf  = pst_rx_ctrl->st_rx_info.uc_msdu_in_buffer;
            pst_msdu_state->us_submsdu_offset       = 0;
            pst_msdu_state->uc_procd_msdu_in_netbuf = 0;
        }
        else if (pst_msdu_state->uc_procd_netbuf_nums == pst_msdu_state->uc_netbuf_nums_in_mpdu)
        {
           *pen_proc_state = MAC_PROC_LAST_MSDU;

            oal_netbuf_free(pst_netbuf_prev);

            return OAL_SUCC;
        }
        else
        {
           *pen_proc_state = MAC_PROC_ERROR;

           OAM_WARNING_LOG0(0, OAM_SF_RX, "{hmac_rx_parse_amsdu::pen_proc_state is err for uc_procd_netbuf_nums > uc_netbuf_nums_in_mpdul.}");
           oal_netbuf_free(pst_netbuf_prev);

           return OAL_FAIL;
        }
        oal_netbuf_free(pst_netbuf_prev);
    }
    else
    {
        *pen_proc_state = MAC_PROC_ERROR;
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{hmac_rx_parse_amsdu::pen_proc_state is err for uc_procd_netbuf_nums > uc_netbuf_nums_in_mpdul.}");
        oal_netbuf_free(pst_msdu_state->pst_curr_netbuf);
        return OAL_FAIL;
    }

    *pen_proc_state = MAC_PROC_MORE_MSDU;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_prepare_msdu_list_to_wlan
 功能描述  : 解析MPDU，如果是非AMSDU，则将MSDU还原为以太网格式的帧，并加入到
             netbuf链的最后，如果该MPDU是AMSDU，则解析出每一个MSDU，并且每一
             个MSDU占用一个netbuf
 输入参数  : pst_netbuf_header: 要交给发送流程的netbuf链表头
             pst_netbuf       : 当前要处理的MPDU的第一个netbuf
             pst_frame_hdr    : 当前要处理的MPDU的MAC头
 输出参数  : 无
 返 回 值  : 成功或者错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_rx_prepare_msdu_list_to_wlan(
                hmac_vap_stru                *pst_vap,
                oal_netbuf_head_stru         *pst_netbuf_header,
                oal_netbuf_stru              *pst_netbuf,
                mac_ieee80211_frame_stru     *pst_frame_hdr)
{
    hmac_rx_ctl_stru                   *pst_rx_ctrl;                        /* 指向MPDU控制块信息的指针 */
    dmac_msdu_stru                      st_msdu;                            /* 保存解析出来的每一个MSDU */
    mac_msdu_proc_status_enum_uint8     en_process_state = MAC_PROC_BUTT;   /* 解析AMSDU的状态 */
    dmac_msdu_proc_state_stru           st_msdu_state    = {0};             /* 记录MPDU的处理信息 */
    oal_uint8                          *puc_addr         = OAL_PTR_NULL;
    oal_uint32                          ul_ret;
    oal_uint8                           auc_sa[WLAN_MAC_ADDR_LEN];
    oal_uint8                           auc_da[WLAN_MAC_ADDR_LEN];
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    mac_ether_header_stru              *pst_ether_hdr;
#endif
    hmac_user_stru                     *pst_hmac_user = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_prepare_msdu_list_to_wlan::pst_netbuf null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 解析MPDU-->MSDU *//* 将MSDU组成netbuf链 */
    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);

    /* 获取该MPDU的控制信息 */
    pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(&st_msdu, OAL_SIZEOF(dmac_msdu_stru));

    /* 情况一:不是AMSDU聚合，则该MPDU对应一个MSDU，同时对应一个NETBUF,将MSDU还原
       成以太网格式帧以后直接加入到netbuf链表最后
    */
    if (OAL_FALSE == pst_rx_ctrl->st_rx_info.bit_amsdu_enable)
    {
        pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_rx_ctrl->st_rx_info.us_ta_user_idx);

        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
        {

            /* 打印此net buf相关信息 */
            mac_rx_report_80211_frame((oal_uint8 *)&(pst_vap->st_vap_base_info),
                                      (oal_uint8 *)&(pst_rx_ctrl->st_rx_info),
                                      pst_netbuf,
                                      OAM_OTA_TYPE_RX_HMAC_CB);
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_netbuf = hmac_defrag_process(pst_hmac_user, pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_header_len);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            return OAL_SUCC;
        }

        pst_rx_ctrl     = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
        pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

        /* 从MAC头中获取源地址和目的地址 */
        mac_rx_get_sa(pst_frame_hdr, &puc_addr);
        oal_set_mac_addr(auc_sa, puc_addr);

        mac_rx_get_da(pst_frame_hdr, &puc_addr);
        oal_set_mac_addr(auc_da, puc_addr);

        /* 将netbuf的data指针指向mac frame的payload处，也就是指向了8字节的snap头 */
        oal_netbuf_pull(pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_header_len);

        /* 将MSDU转化为以太网格式的帧 */
        hmac_rx_frame_80211_to_eth(pst_netbuf, auc_da, auc_sa);

        OAL_MEMZERO(OAL_NETBUF_CB(pst_netbuf), OAL_NETBUF_CB_SIZE());


#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
        pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);

        if (OAL_SUCC != hmac_11i_ether_type_filter(pst_vap, pst_ether_hdr->auc_ether_shost, pst_ether_hdr->us_ether_type))
        {/* 接收安全数据过滤 */

            /* ,us_ether_type为0导致企业级加密失败,添加维测信息看是否报文解析异常 */
            oam_report_eth_frame(auc_da, (oal_uint8*)pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf), OAM_OTA_FRAME_DIRECTION_TYPE_RX);

            oal_netbuf_free(pst_netbuf);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_portvalid_check_fail_dropped, 1);
            return OAL_FAIL;
        }
        else
#endif
        {
            /* 将MSDU加入到netbuf链的最后 */
            oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);
        }
    }

    else /* 情况二:AMSDU聚合 */
    {
        st_msdu_state.uc_procd_netbuf_nums    = 0;
        st_msdu_state.uc_procd_msdu_in_netbuf = 0;

        do
        {
            /* 获取下一个要转发的msdu */
            ul_ret = hmac_rx_parse_amsdu(pst_netbuf, &st_msdu, &st_msdu_state, &en_process_state);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_rx_prepare_msdu_list_to_wlan::hmac_rx_parse_amsdu failed[%d].}", ul_ret);
                return ul_ret;
            }

            /* 将MSDU转化为以太网格式的帧 */
            hmac_rx_frame_80211_to_eth(st_msdu.pst_netbuf, st_msdu.auc_da, st_msdu.auc_sa);

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
            pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(st_msdu.pst_netbuf);

            if (OAL_SUCC != hmac_11i_ether_type_filter(pst_vap, pst_ether_hdr->auc_ether_shost, pst_ether_hdr->us_ether_type))
            {
                /* 接收安全数据过滤 */
                /* ,us_ether_type为0导致企业级加密失败,添加维测信息看是否报文解析异常 */
                oam_report_eth_frame(st_msdu.auc_da, (oal_uint8*)pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf), OAM_OTA_FRAME_DIRECTION_TYPE_RX);

                oal_netbuf_free(st_msdu.pst_netbuf);
                OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_portvalid_check_fail_dropped, 1);
                continue;
            }
            else
#endif
            {
                /* 将MSDU加入到netbuf链的最后 */
                oal_netbuf_add_to_list_tail(st_msdu.pst_netbuf, pst_netbuf_header);
            }
        }while (MAC_PROC_LAST_MSDU != en_process_state);
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/*****************************************************************************
 函 数 名  : hmac_rx_proxysta_update_checksum_addr
 功能描述  : 更新checksum
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
oal_uint16  hmac_rx_proxysta_update_checksum_addr(oal_uint16 us_osum,
                                                         oal_uint8  uc_omac[6],
                                                         oal_uint8  uc_nmac[6])

{
    oal_uint16 us_nsum = us_osum;
    oal_uint32 ul_sum;
    oal_uint32 ul_loop;

    if (0 == us_osum)
    {
        return us_nsum;
    }

    for (ul_loop = 0;ul_loop < 3; ul_loop++)
    {
        ul_sum = us_nsum;
        ul_sum += *(oal_uint16 *)&uc_omac[ul_loop * 2] + (~(*(oal_uint16 *)&uc_nmac[ul_loop * 2]) & 0XFFFF);
        ul_sum  = (ul_sum >> 16) + (ul_sum & 0XFFFF);
        us_nsum = (oal_uint16)((ul_sum >> 16) + ul_sum);
    }

    return us_nsum;
}

/*****************************************************************************
 函 数 名  : hmac_rx_proxysta_arp_mat
 功能描述  : arp包地址转换
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_rx_proxysta_arp_mat(mac_vap_stru            *pst_mac_vap,
                                                      mac_ether_header_stru   *pst_ether_header,
                                                      mac_device_stru         *pst_mac_device,
                                                      oal_uint32               ul_pkt_len)
{
    oal_eth_arphdr_stru *pst_arp          = OAL_PTR_NULL;
    oal_uint8           *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8           *puc_arp_dmac     = OAL_PTR_NULL;
    mac_vap_stru        *pst_mac_temp_vap = OAL_PTR_NULL;
    oal_uint8           *puc_des_mac      = OAL_PTR_NULL;
    oal_uint8           uc_vap_idx;
    oal_bool_enum_uint8 en_is_mcast;
    oal_uint32          ul_contig_len;
    oal_bool_enum_uint8 en_is_arp_mac_changed = OAL_FALSE;

    /***************************************************************************/
    /*                      ARP Frame Format                                   */
    /* ----------------------------------------------------------------------- */
    /* |以太网目的地址|以太网源地址|帧类型|硬件类型|协议类型|硬件地址长度|     */
    /* ----------------------------------------------------------------------- */
    /* | 6 (待替换)   |6           |2     |2       |2       |1           |     */
    /* ----------------------------------------------------------------------- */
    /* |协议地址长度|op|发送端以太网地址|发送端IP地址|目的以太网地址|目的IP地址*/
    /* ----------------------------------------------------------------------- */
    /* | 1          |2 |6               |4           |6 (待替换)    |4         */
    /* ----------------------------------------------------------------------- */
    /*                                                                         */
    /***************************************************************************/

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_rx_proxysta_arp_mat::The input parameter of hmac_rx_proxysta_arp_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);

    /* 获取以太网目的mac和数据段 */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* 获取以太网帧目的地址是否为多播地址 */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);

    /* ARP 包地址转换 */
    pst_arp = (oal_eth_arphdr_stru *)puc_eth_body;
    ul_contig_len += OAL_SIZEOF(oal_eth_arphdr_stru);

    if (ul_pkt_len < ul_contig_len)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_rx_proxysta_arp_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_eth_arphdr_stru.}");
        return OAL_FAIL;
    }

    /*lint -e778*/
    if ((ETHER_ADDR_LEN == pst_arp->uc_ar_hln) && (OAL_NET2HOST_SHORT(ETHER_TYPE_IP) == pst_arp->us_ar_pro))
    {
        puc_arp_dmac = pst_arp->auc_ar_tha;
    }
    else
    {
        pst_arp = OAL_PTR_NULL;
    }
    /*lint +e778*/

    if (OAL_PTR_NULL != pst_arp)
    {
        if (OAL_TRUE != en_is_mcast)
        {
            switch (OAL_NET2HOST_SHORT(pst_arp->us_ar_op))
            {
                case OAL_ARPOP_REQUEST:
                case OAL_ARPOP_REPLY:
                    /* 替换mac地址为out vap的mac地址 */
                    oal_set_mac_addr(puc_arp_dmac, pst_mac_vap->st_vap_proxysta.auc_oma);

                    break;
                default:
                    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{hmac_rx_proxysta_arp_mat::do not replace arp addr.}");
            }
        }
        else
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_rx_proxysta_arp_mat::received arp broadcast packet, start process.}");

            /* root ap发过来的下行广播包，只有sta0可以收到，但arp包的arp_dmac为stax‘的地址，找到stax’,替换为其代理的oma地址 */
            if (OAL_FALSE != oal_compare_mac_addr(puc_arp_dmac, pst_mac_vap->st_vap_proxysta.auc_oma))
            {
                OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_rx_proxysta_arp_mat::start into if.}");

               /* 遍历Device下的vap(STA模式)，当目的地址为与vap自己的地址相同时，用其oma地址替换帧的目的地址 */
               for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
               {
                   pst_mac_temp_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                   if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_temp_vap))
                   {
                       OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_PROXYSTA, "{hmac_rx_proxysta_arp_mat::pst_mac_vap is null ptr!}");
                       return OAL_SUCC;
                   }

                   if (OAL_FALSE == oal_compare_mac_addr(puc_arp_dmac, mac_mib_get_StationID(pst_mac_temp_vap)))
                   {
                       /* 替换mac地址为out vap的mac地址 */
                       oal_set_mac_addr(puc_arp_dmac,pst_mac_temp_vap->st_vap_proxysta.auc_oma);

                       OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                     "{hmac_rx_proxysta_arp_mat::changed multi arp des mac with proxysta's oma mac.}");

                       en_is_arp_mac_changed = OAL_TRUE;
                       break;
                   }
               }

               /* 如果arm mac没有改变，如果是下行arp广播包，无需换地址，直接返回 */
               if (OAL_FALSE == en_is_arp_mac_changed)
               {
                    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                                   "{hmac_rx_proxysta_arp_mat::do not changed multi arp des mac, return succ.}");
                    return OAL_SUCC;
                }
            }
        }
    }

    oal_set_mac_addr(puc_des_mac, pst_mac_vap->st_vap_proxysta.auc_oma);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_proxysta_ip_mat
 功能描述  : ip包地址转换，主要包括以下两种报文的处理:
             1.DHCP报文的处理；
             2.其他IP类型报文的处理
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_rx_proxysta_ip_mat(mac_vap_stru           *pst_mac_vap,
                                                     mac_ether_header_stru  *pst_ether_header,
                                                     mac_device_stru        *pst_mac_device,
                                                     oal_uint32              ul_pkt_len)
{
    oal_ip_header_stru   *pst_ip_header    = OAL_PTR_NULL;
    oal_udp_header_stru  *pst_udp_header   = OAL_PTR_NULL;
    oal_dhcp_packet_stru *pst_dhcp_packet  = OAL_PTR_NULL;
    mac_vap_stru         *pst_mac_temp_vap = OAL_PTR_NULL;
    oal_uint8            *puc_eth_body     = OAL_PTR_NULL;
    oal_uint8            *puc_des_mac      = OAL_PTR_NULL;
    oal_uint16           us_ip_header_len;
    oal_uint8            uc_vap_idx;
    oal_bool_enum_uint8  en_is_mcast;
    oal_uint32           ul_contig_len;

    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_ether_header) || (OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{hmac_rx_proxysta_ip_mat::The input parameter of hmac_rx_proxysta_ip_mat is OAL_PTR_NULL.}");
        return OAL_FAIL;
    }

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                  "{hmac_rx_proxysta_ip_mat::start into hmac_rx_proxysta_ip_mat.}");

    ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);

    /* 获取以太网目的mac和数据段 */
    puc_des_mac = pst_ether_header->auc_ether_dhost;
    puc_eth_body = (oal_uint8 *)(pst_ether_header + 1);

    /* 获取以太网帧目的地址是否为多播地址 */
    en_is_mcast = ETHER_IS_MULTICAST(puc_des_mac);

    /*************************************************************************/
    /*                      DHCP Frame Format                                */
    /* --------------------------------------------------------------------- */
    /* |以太网头        |   IP头         | UDP头           |DHCP报文       | */
    /* --------------------------------------------------------------------- */
    /* | 14             |20              |8                | 不定          | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    pst_ip_header = (oal_ip_header_stru *)puc_eth_body;

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
                       "{hmac_rx_proxysta_ip_mat::The length of buf is less than the sum of mac_ether_header_stru and oal_ip_header_stru.}");
        return OAL_FAIL;
    }

    us_ip_header_len = pst_ip_header->us_ihl * 4;

    /* 如果是UDP包，并且是DHCP协议的报文地址转换 */
    if (OAL_IPPROTO_UDP == pst_ip_header->uc_protocol)
    {
        pst_udp_header  = (oal_udp_header_stru *)((oal_uint8 *)pst_ip_header + us_ip_header_len);

        ul_contig_len += OAL_SIZEOF(oal_udp_header_stru);
        if (ul_pkt_len < ul_contig_len)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_rx_proxysta_ip_mat::The length of buf is invalid.}");
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

/*lint -e778*/
/*lint -e572*/

        /* DHCP request UDP Client SP = 68 (bootpc), DP = 67 (bootps) */
        if (OAL_NET2HOST_SHORT(67) == pst_udp_header->source)
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
                return OAL_FAIL;
            }

            if (OAL_FALSE == en_is_mcast)
            {
                /* 单播包 */
                if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap)))
                {
                    /* 把UDP包中的地址替换为自己的地址 */
                    oal_set_mac_addr(pst_dhcp_packet->chaddr, pst_mac_vap->st_vap_proxysta.auc_oma);

                    /* 重新计算udp checksum */
                    pst_udp_header->check = hmac_rx_proxysta_update_checksum_addr(pst_udp_header->check,
                                                                                  mac_mib_get_StationID(pst_mac_vap),
                                                                                  pst_mac_vap->st_vap_proxysta.auc_oma);

                    /* 如果DHCP offer、ack回应帧是单播帧，为了防止单播帧被聚合将其目的地址转换为广播地址 */
                    oal_set_mac_addr(puc_des_mac, BROADCAST_MACADDR);
                }
                else
                {
                    return OAL_SUCC;
                }
            }
            else
            {
                /* main sta收到广播DHCP数据帧，dhcp报文中客户端mac地址和接收端口的地址不同，则遍历所有的vap(即proxysta)，
                   找到和dhcp报文中的客户端mac地址相同的vap mac(即proxysta)地址，并客户端mac地址替换为proxysta的oma地址，
                   并更新udp check */
                if (OAL_FALSE != oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_vap)))
                {
                   /* 遍历Device下的vap(STA模式)，当目的地址为与vap自己的地址相同时，用其oma地址替换帧的目的地址 */
                   for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
                   {
                       pst_mac_temp_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                       if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_temp_vap))
                       {
                           OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_PROXYSTA,
                                            "{hmac_rx_proxysta_ip_mat::pst_mac_vap is null ptr!}");
                           return OAL_SUCC;
                       }

                       if (OAL_FALSE == oal_compare_mac_addr(pst_dhcp_packet->chaddr, mac_mib_get_StationID(pst_mac_temp_vap)))
                       {
                           /* 替换mac地址为out vap的mac地址 */
                           oal_set_mac_addr(pst_dhcp_packet->chaddr, pst_mac_temp_vap->st_vap_proxysta.auc_oma);

                           /* 重新计算udp checksum */
                           pst_udp_header->check = hmac_rx_proxysta_update_checksum_addr(pst_udp_header->check,
                                                                                         mac_mib_get_StationID(pst_mac_temp_vap),
                                                                                         pst_mac_temp_vap->st_vap_proxysta.auc_oma);

                           break;
                       }
                   }
                }
            }
        }
        else
        {
            /* 不是DHCP的其它UDP包，也需要更新以太网目的地址为proxysta的vma */
            oal_set_mac_addr(puc_des_mac, pst_mac_vap->st_vap_proxysta.auc_oma);
        }
    }
    /* 其它类型IP报文的地址转换处理 */
    else
    {
        /* 更新以太网目的地址为proxysta的vma */
        oal_set_mac_addr(puc_des_mac, pst_mac_vap->st_vap_proxysta.auc_oma);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_proxysta_mat
 功能描述  : ARP、DHCP、ICMPv6等包，上报网桥前地址转换函数
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
oal_uint32  hmac_rx_proxysta_mat(oal_netbuf_stru *pst_buf, oal_net_device_stru *pst_dev)
{
    mac_vap_stru            *pst_mac_vap;
    mac_ether_header_stru   *pst_ether_header;
    oal_uint16               us_ether_type;
    oal_uint8               *puc_scr_mac;
    oal_uint8               *puc_des_mac;
    oal_bool_enum_uint8      en_is_mcast;
    oal_uint32               ul_contig_len = OAL_SIZEOF(mac_ether_header_stru);
    oal_uint32               ul_pkt_len;

    oal_uint8                uc_vap_idx;
    mac_device_stru          *pst_mac_device;
    mac_vap_stru             *pst_mac_temp_vap;
    oal_uint32               ul_ret;

    ul_pkt_len = OAL_NETBUF_LEN(pst_buf) + ETHER_HDR_LEN;

    /* 获取VAP结构体 */
    pst_mac_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_dev);

    /* 如果不是sta，不需要地址转换 */
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        return OAL_SUCC;
    }

    /* 获取device指针结构体 */
    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA,
                       "{hmac_rx_proxysta_mat::get pst_mac_device is a null ptr!}");
        return OAL_FAIL ;
    }

    if (ul_pkt_len < ul_contig_len)
    {
        return OAL_FAIL;
    }

    /* 将skb的data指针指向以太网的帧头 */
    oal_netbuf_push(pst_buf, ETHER_HDR_LEN);

    pst_ether_header = (mac_ether_header_stru *)OAL_NETBUF_HEADER(pst_buf);

    /* 还原skb的data指针 */
    oal_netbuf_pull(pst_buf, ETHER_HDR_LEN);

    us_ether_type = pst_ether_header->us_ether_type;
    puc_scr_mac   = pst_ether_header->auc_ether_shost;
    puc_des_mac   = pst_ether_header->auc_ether_dhost;

    en_is_mcast   = ETHER_IS_MULTICAST(puc_des_mac);

    if (OAL_HOST2NET_SHORT(ETHER_TYPE_PAE) == us_ether_type)
    {
        /* 标注包处理类型 在网桥钩子函数中处理 */
        pst_buf->mark   = OAL_PROXYSTA_MARK_ROUTE;
        return OAL_SUCC;
    }

    /* main sta和proxysta向root ap发送广播包，root ap会将收到的广播包向与其关联的所有用户转发此包，
       因此，main sta会收到root ap所发送的广播包，当收到这些广播包后，main sta会判断是否为本device上的
       sta发送的广播包，如果是将其标记为丢弃，上网桥后将其丢弃；否则不做任何处理 */
    if ((OAL_TRUE == en_is_mcast) && (OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta))
    {
        /* 遍历device下的vap,做标记，以备网桥处理 */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_temp_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
            {
                OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_PROXYSTA,
                                 "{hmac_rx_proxysta_mat::get pst_mac_vap is null ptr!}");
                return OAL_FAIL;
            }

            if (OAL_FALSE == oal_compare_mac_addr(puc_scr_mac, mac_mib_get_StationID(pst_mac_temp_vap)))
            {
                pst_buf->mark = OAL_PROXYSTA_MARK_DROPPED;
                return OAL_SUCC;
            }
        }
    }

    /* ARP 包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_ARP) == us_ether_type)
    {
        ul_ret = hmac_rx_proxysta_arp_mat(pst_mac_vap,
                                          pst_ether_header,
                                          pst_mac_device,
                                          ul_pkt_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_rx_proxysta_mat::hmac_rx_proxysta_arp_mat returns %d.}", ul_ret);
        }
        return ul_ret;
    }

/*lint -e778*/
    /* IP包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == us_ether_type)
    {
/*lint +e778*/
        ul_ret = hmac_rx_proxysta_ip_mat(pst_mac_vap,
                                         pst_ether_header,
                                         pst_mac_device,
                                         ul_pkt_len);
        if (OAL_SUCC != ul_ret)
        {
           OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,
                           "{hmac_rx_proxysta_mat::hmac_rx_proxysta_ip_mat returns %d.}", ul_ret);
        }
        return ul_ret;
    }

    /*icmpv6 包地址转换 */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == us_ether_type)
    {
        /*TBD A公司代码中是todo */
    }

    oal_set_mac_addr(puc_des_mac, pst_mac_vap->st_vap_proxysta.auc_oma);

    return OAL_SUCC;
}

#endif
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
OAL_STATIC oal_void hmac_pkt_mem_opt_stat_reset(hmac_device_stru *pst_hmac_device, oal_bool_enum_uint8 en_dscr_opt_state)
{
    frw_event_mem_stru    *pst_event_mem;
    frw_event_stru        *pst_event;
    hmac_rx_dscr_opt_stru *pst_dscr_opt = &pst_hmac_device->st_rx_dscr_opt;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device->pst_device_base_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_pkt_mem_opt_stat_reset::pst_device_base_info null!}");
        return;
    }


    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_stat_reset::new_state[%d], pkt_num[%d]}", en_dscr_opt_state, pst_dscr_opt->ul_rx_pkt_num);
    pst_dscr_opt->en_dscr_opt_state = en_dscr_opt_state;
    pst_dscr_opt->ul_rx_pkt_num     = 0;

    /***************************************************************************
        抛事件到dmac模块,将统计信息报给dmac
    ***************************************************************************/
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_timeout_fn::pst_event_mem null.}");
        return;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT,
                    0,
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_hmac_device->pst_device_base_info->uc_chip_id,
                    pst_hmac_device->pst_device_base_info->uc_device_id,
                    0);

    /* 拷贝参数 */
    pst_event->auc_event_data[0] = pst_dscr_opt->en_dscr_opt_state;

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : hmac_pkt_mem_opt_cfg
 功能描述  : 配置hmac_pkt_mem_opt_cfg参数
 输入参数  : ul_cfg_type:0 enable使能开关
                         1 opt_limit
                         2 reset_limit
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_pkt_mem_opt_cfg(oal_uint32 ul_cfg_tpye, oal_uint32 ul_cfg_value)
{
    hmac_device_stru      *pst_hmac_device = (hmac_device_stru*)hmac_res_get_mac_dev(0);
    hmac_rx_dscr_opt_stru *pst_dscr_opt;

    if(ul_cfg_tpye > 2)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_cfg::invalid cfg tpye.}");
        return;
    }
    if(OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_cfg::hmac device is null.}");
        return;
    }

    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_cfg::cfg type[%d], cfg value[%d].}", ul_cfg_tpye, ul_cfg_value);
    pst_dscr_opt = &pst_hmac_device->st_rx_dscr_opt;
    if(0 == ul_cfg_tpye)
    {
        pst_dscr_opt->en_dscr_opt_enable = (oal_uint8)ul_cfg_value;
        if(OAL_FALSE == pst_dscr_opt->en_dscr_opt_enable && OAL_TRUE == pst_dscr_opt->en_dscr_opt_state)
        {
            hmac_pkt_mem_opt_stat_reset(pst_hmac_device, OAL_FALSE);
        }
    }
    if(1 == ul_cfg_tpye)
    {
        pst_dscr_opt->ul_rx_pkt_opt_limit = ul_cfg_value;
    }
    if(2 == ul_cfg_tpye)
    {
        pst_dscr_opt->ul_rx_pkt_reset_limit = ul_cfg_value;
    }
}

oal_uint32  hmac_pkt_mem_opt_timeout_fn(oal_void *p_arg)
{
    hmac_device_stru      *pst_hmac_device;
    hmac_rx_dscr_opt_stru *pst_dscr_opt;


    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_timeout_fn::p_arg is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_device = (hmac_device_stru *)p_arg;
    pst_dscr_opt    = &pst_hmac_device->st_rx_dscr_opt;

    if(OAL_TRUE != pst_dscr_opt->en_dscr_opt_enable)
    {
        return OAL_SUCC;
    }

    OAM_INFO_LOG2(0, OAM_SF_ANY, "{hmac_rx_dscr_opt_timeout_fn::state[%d], pkt_num[%d]}", pst_dscr_opt->en_dscr_opt_state, pst_dscr_opt->ul_rx_pkt_num);

    /* rx_dscr未调整状态时, 检测到RX业务,调整描述符 */
    if(OAL_FALSE == pst_dscr_opt->en_dscr_opt_state && pst_dscr_opt->ul_rx_pkt_num > pst_dscr_opt->ul_rx_pkt_opt_limit)
    {
        hmac_pkt_mem_opt_stat_reset(pst_hmac_device, OAL_TRUE);
    }
    /* rx_dscr已调整状态时, 未检测到RX业务,调整回描述符,保证TX性能 */
    else if(OAL_TRUE == pst_dscr_opt->en_dscr_opt_state && pst_dscr_opt->ul_rx_pkt_num < pst_dscr_opt->ul_rx_pkt_reset_limit)
    {
        hmac_pkt_mem_opt_stat_reset(pst_hmac_device, OAL_FALSE);
    }
    else
    {
        pst_dscr_opt->ul_rx_pkt_num  = 0;
    }

    return OAL_SUCC;
}

oal_void hmac_pkt_mem_opt_init(hmac_device_stru *pst_hmac_device)
{
    pst_hmac_device->st_rx_dscr_opt.en_dscr_opt_state     = OAL_FALSE;
    pst_hmac_device->st_rx_dscr_opt.ul_rx_pkt_num         = 0;
    pst_hmac_device->st_rx_dscr_opt.ul_rx_pkt_opt_limit   = WLAN_PKT_MEM_PKT_OPT_LIMIT;
    pst_hmac_device->st_rx_dscr_opt.ul_rx_pkt_reset_limit = WLAN_PKT_MEM_PKT_RESET_LIMIT;
    pst_hmac_device->st_rx_dscr_opt.en_dscr_opt_enable    = OAL_TRUE;

    FRW_TIMER_CREATE_TIMER(&(pst_hmac_device->st_rx_dscr_opt.st_rx_dscr_opt_timer), hmac_pkt_mem_opt_timeout_fn, WLAN_PKT_MEM_OPT_TIME_MS, pst_hmac_device, OAL_TRUE, OAM_MODULE_ID_HMAC,0);
}

oal_void hmac_pkt_mem_opt_exit(hmac_device_stru *pst_hmac_device)
{
    if (OAL_TRUE == pst_hmac_device->st_rx_dscr_opt.st_rx_dscr_opt_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_device->st_rx_dscr_opt.st_rx_dscr_opt_timer));
    }
}


OAL_STATIC oal_void  hmac_pkt_mem_opt_rx_pkts_stat(hmac_vap_stru *pst_vap, oal_ip_header_stru *pst_ip)
{
    hmac_device_stru *pst_hmac_device = (hmac_device_stru*)hmac_res_get_mac_dev(pst_vap->st_vap_base_info.uc_device_id);

    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_pkt_mem_opt_rx_pkts_stat::hmac_res_get_mac_dev fail.device_id :%d}",pst_vap->st_vap_base_info.uc_device_id);
        return;
    }
    /* 过滤IP_LEN 小于 HMAC_RX_DSCR_OPT_MIN_PKT_LEN的报文 */
    if (OAL_NET2HOST_SHORT(pst_ip->us_tot_len) < WLAN_PKT_MEM_OPT_MIN_PKT_LEN)
    {
        return;
    }

    if ((MAC_UDP_PROTOCAL == pst_ip->uc_protocol) || (MAC_TCP_PROTOCAL == pst_ip->uc_protocol))
    {
        pst_hmac_device->st_rx_dscr_opt.ul_rx_pkt_num++;
    }
    else
    {
        OAM_INFO_LOG0(0, OAM_SF_RX, "{hmac_rx_dscr_opt_rx_pkts_stat: neither UDP nor TCP ");
    }
}
#endif
/*****************************************************************************
 函 数 名  : hmac_rx_transmit_msdu_to_lan
 功能描述  : 将MSDU转发到LAN的接口，包括地址转换等信息的设置
             说明:本函数接收到的netbuf数据域是从snap头开始
 输入参数  : (1)指向vap的指针
             (2)指向需要发送的msdu的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_rx_transmit_msdu_to_lan(hmac_vap_stru *pst_vap, dmac_msdu_stru *pst_msdu)
{
    oal_net_device_stru    *pst_device;
    oal_netbuf_stru        *pst_netbuf;
    mac_ether_header_stru  *pst_ether_hdr;
#ifdef _PRE_WLAN_FEATURE_MCAST
    hmac_user_stru         *pst_hmac_user;
    oal_uint16              us_user_idx = 0xffff;
#endif

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    oal_uint8              *puc_mac_addr;
#endif
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_uint32              ul_proxymat_ret;
    mac_device_stru        *pst_mac_device;
    mac_vap_stru           *pst_mac_vap_proxysta = &(pst_vap->st_vap_base_info);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    mac_vap_stru           *pst_mac_vap       = &(pst_vap->st_vap_base_info);
    hmac_user_stru         *pst_hmac_user_st  = OAL_PTR_NULL;
    mac_ip_header_stru     *pst_ip            = OAL_PTR_NULL;
    oal_uint16              us_assoc_id       = 0xffff;
#endif

    /* 获取netbuf，该netbuf的data指针已经指向payload处 */
    pst_netbuf = pst_msdu->pst_netbuf;

    OAL_NETBUF_PREV(pst_netbuf) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;

    hmac_rx_frame_80211_to_eth(pst_netbuf, pst_msdu->auc_da, pst_msdu->auc_sa);

    pst_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ether_hdr))
    {
        oal_netbuf_free(pst_netbuf);
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_rx_transmit_msdu_to_lan::pst_ether_hdr null.}");
        return;
    }

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    puc_mac_addr = pst_msdu->auc_ta;

    if (OAL_SUCC != hmac_11i_ether_type_filter(pst_vap, puc_mac_addr, pst_ether_hdr->us_ether_type))
    {
        /* 接收安全数据过滤 */
        /* ,us_ether_type为0导致企业级加密失败,添加维测信息看是否报文解析异常 */
        oam_report_eth_frame(puc_mac_addr, (oal_uint8*)pst_ether_hdr, (oal_uint16)OAL_NETBUF_LEN(pst_netbuf), OAM_OTA_FRAME_DIRECTION_TYPE_RX);

        oal_netbuf_free(pst_netbuf);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_portvalid_check_fail_dropped, 1);
        return;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
    if (OAL_PTR_NULL != pst_vap->pst_m2u)
    {
        if (WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode)
        {
            if (OAL_SUCC != mac_vap_find_user_by_macaddr(&(pst_vap->st_vap_base_info), pst_ether_hdr->auc_ether_shost, &us_user_idx))
            {
                OAM_ERROR_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_rx_transmit_msdu_to_lan::mac_vap_find_user_by_macaddr [%x].[%x].[%x].[%x]failed}",
                                                        (oal_uint32)(pst_ether_hdr->auc_ether_shost[2]),
                                                        (oal_uint32)(pst_ether_hdr->auc_ether_shost[3]),
                                                        (oal_uint32)(pst_ether_hdr->auc_ether_shost[4]),
                                                        (oal_uint32)(pst_ether_hdr->auc_ether_shost[5]));
                oal_netbuf_free(pst_netbuf);
                return;
            }
        }
        else if (WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
        {
            us_user_idx = pst_vap->st_vap_base_info.uc_assoc_vap_id;
        }
        pst_hmac_user = mac_res_get_hmac_user(us_user_idx);
        hmac_m2u_snoop_inspecting(pst_vap, pst_hmac_user, pst_netbuf);
    }
#endif

    /* 获取net device hmac创建的时候，需要记录netdevice指针 */
    pst_device      = pst_vap->pst_net_device;

    /* 对protocol模式赋值 */
    /*此处linux有复杂操作，liteos做了简化，protocol为0，先pull 14字节，后面会用到，最后交给系统之前push回去。*/
    OAL_NETBUF_PROTOCOL(pst_netbuf) = oal_eth_type_trans(pst_netbuf, pst_device);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_vap->st_vap_base_info.uc_device_id);
    if ( OAL_PTR_NULL == pst_mac_device)
    {
        oal_netbuf_free(pst_netbuf);
        OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_rx_transmit_msdu_to_lan::mac_res_get_dev is null!}");
        return;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if (OAL_TRUE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_proxysta)
        {
            /* 接收包地址转换 */
            ul_proxymat_ret = hmac_rx_proxysta_mat(pst_netbuf, pst_device);
            if (OAL_SUCC != ul_proxymat_ret)
            {
                oal_netbuf_free(pst_netbuf);
                OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_PROXYSTA,
                       "{hmac_rx_transmit_msdu_to_lan::hmac_rx_proxysta_mat fail, return value is %d.}", ul_proxymat_ret);
                return;
            }
        }
    }
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(OAL_FALSE == ETHER_IS_MULTICAST(pst_msdu->auc_da))
    {
        oal_atomic_inc(&(pst_vap->ul_rx_unicast_pkt_to_lan));
    }
#endif

    /* 信息统计与帧上报分离 */
    /* 增加统计信息 */
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_vap->st_query_stats.ul_rx_pkt_to_lan,1);
    HMAC_VAP_DFT_STATS_PKT_INCR(pst_vap->st_query_stats.ul_rx_bytes_to_lan,OAL_NETBUF_LEN(pst_netbuf));
    OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_pkt_to_lan, 1); /* 增加发往LAN的帧的数目 */
    OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_bytes_to_lan, OAL_NETBUF_LEN(pst_netbuf)); /* 增加发送LAN的字节数 */

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    hmac_rx_report_eth_frame(&pst_vap->st_vap_base_info, pst_netbuf);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) && (OAL_TRUE == pst_vap->uc_edca_opt_flag_ap))
    {
        /*lint -e778*/
        if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_ether_hdr->us_ether_type)
        {
            if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, pst_ether_hdr->auc_ether_shost, &us_assoc_id))
            {
                OAM_WARNING_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_rx_transmit_msdu_to_lan::find_user_by_macaddr[%02x:XX:XX:%02x:%02x:%02x]failed}",
                               (oal_uint32)(pst_ether_hdr->auc_ether_shost[0]),
                               (oal_uint32)(pst_ether_hdr->auc_ether_shost[3]),
                               (oal_uint32)(pst_ether_hdr->auc_ether_shost[4]),
                               (oal_uint32)(pst_ether_hdr->auc_ether_shost[5]));
                oal_netbuf_free(pst_netbuf);
                return;
            }
            pst_hmac_user_st = (hmac_user_stru *)mac_res_get_hmac_user(us_assoc_id);
            if (OAL_PTR_NULL == pst_hmac_user_st)
            {
                oal_netbuf_free(pst_netbuf);
                OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_rx_transmit_msdu_to_lan::mac_res_get_hmac_user fail. assoc_id: %u}", us_assoc_id);
                return;
            }

            pst_ip = (mac_ip_header_stru *)(pst_ether_hdr + 1);

            /* mips优化:解决开启业务统计性能差10M问题 */
            if (((MAC_UDP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user_st->aaul_txrx_data_stat[WLAN_WME_AC_BE][WLAN_RX_UDP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10)))
                || ((MAC_TCP_PROTOCAL == pst_ip->uc_protocol) && (pst_hmac_user_st->aaul_txrx_data_stat[WLAN_WME_AC_BE][WLAN_RX_TCP_DATA] < (HMAC_EDCA_OPT_PKT_NUM + 10))))
            {
                hmac_edca_opt_rx_pkts_stat(us_assoc_id, WLAN_TIDNO_BEST_EFFORT, pst_ip);
            }
        }
        /*lint +e778*/
    }
#endif

    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
    OAL_MEMZERO(OAL_NETBUF_CB(pst_netbuf), OAL_NETBUF_CB_SIZE());
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT) || (_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT))
    if ( NULL != g_p_hisi_fp_func ) /*5610适配， 快速转发功能*/
    {
        /* 将skb的data指针指向以太网的帧头 */
        oal_netbuf_push(pst_netbuf, ETHER_HDR_LEN);
        g_p_hisi_fp_func(pst_netbuf, pst_device);
    }
    else
#elif (_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT)//暂时复用EVB的
    if ( NULL != g_p_hisi_fp_func ) /*5610适配， 快速转发功能*/
    {
        /* 将skb的data指针指向以太网的帧头 */
        oal_netbuf_push(pst_netbuf, ETHER_HDR_LEN);
        g_p_hisi_fp_func(pst_netbuf, pst_device);
    }
    else
#elif (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)
    if (NULL != g_pv_wifi_callback)
    {
        oal_netbuf_push(pst_netbuf, ETHER_HDR_LEN);
        g_pv_wifi_callback(pst_netbuf, pst_device);
    }
    else
#endif
    {
        /* 将skb转发给桥 */
        oal_netif_rx_hw(pst_netbuf);
    }
#else
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_pkt_mem_opt_rx_pkts_stat(pst_vap, (oal_ip_header_stru*)(pst_ether_hdr + 1));
#endif
    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_NETBUF_FOR_KERNEL);

    /* 将skb转发给桥 */
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    pst_netbuf->dev = pst_device;

    /* 将skb的data指针指向以太网的帧头 */
    //由于前面pull了14字节，这个地方要push回去。
    oal_netbuf_push(pst_netbuf, ETHER_HDR_LEN);
#endif /* */
    if(OAL_TRUE == hmac_get_rxthread_enable())
    {
        hmac_rxdata_netbuf_enqueue(pst_netbuf);

        hmac_rxdata_sched();
    }
    else
    {
        oal_netif_rx_ni(pst_netbuf);
    }
#endif

    /* 置位net_dev->jiffies变量 */
    OAL_NETDEVICE_LAST_RX(pst_device) = OAL_TIME_JIFFY;

}

/*****************************************************************************
 函 数 名  : hmac_rx_lan_frame_classify
 功能描述  : HMAC接收模块，WLAN到LAN的转发接口
 输入参数  : (1)对应MPDU的第一个netbuf的指针
             (2)对应的MPDU占用的netbuf的数目
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_lan_frame_classify(
                hmac_vap_stru              *pst_vap,
                oal_netbuf_stru            *pst_netbuf,
                mac_ieee80211_frame_stru   *pst_frame_hdr)
{
    hmac_rx_ctl_stru                   *pst_rx_ctrl;                        /* 指向MPDU控制块信息的指针 */
    dmac_msdu_stru                      st_msdu;                            /* 保存解析出来的每一个MSDU */
    mac_msdu_proc_status_enum_uint8     en_process_state = MAC_PROC_BUTT;   /* 解析AMSDU的状态 */
    dmac_msdu_proc_state_stru           st_msdu_state    = {0};             /* 记录MPDU的处理信息 */
    oal_uint8                          *puc_addr         = OAL_PTR_NULL;
    oal_uint32                          ul_ret;
    hmac_user_stru                     *pst_hmac_user;
    oal_uint8                           uc_datatype = MAC_DATA_BUTT;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_stru                     *pst_wapi;
#endif
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_netbuf) || (OAL_PTR_NULL == pst_frame_hdr)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_lan_frame_classify::params null.}");
        return;
    }
    /* 获取该MPDU的控制信息 */
    pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(&st_msdu, OAL_SIZEOF(dmac_msdu_stru));

    mac_get_transmit_addr(pst_frame_hdr, &puc_addr);

    oal_set_mac_addr(st_msdu.auc_ta, puc_addr);

    pst_hmac_user = (hmac_user_stru*)mac_res_get_hmac_user(pst_rx_ctrl->st_rx_info.us_ta_user_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                      "{hmac_rx_lan_frame_classify::pst_hmac_user null, user_idx=%d.}",
                       pst_rx_ctrl->st_rx_info.us_ta_user_idx);

        /* 打印此net buf相关信息 */
        OAM_ERROR_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                      "{hmac_rx_lan_frame_classify::info in cb, vap id=%d mac_hdr_len=%d, us_frame_len=%d mac_hdr_start_addr=0x%08x.}",
                       pst_rx_ctrl->st_rx_info.bit_vap_id,
                       pst_rx_ctrl->st_rx_info.uc_mac_header_len,
                       pst_rx_ctrl->st_rx_info.us_frame_len,
                       (oal_uint)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr);
        OAM_ERROR_LOG2(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{hmac_rx_lan_frame_classify::net_buf ptr addr=0x%08x, cb ptr addr=0x%08x.}",
                       (oal_uint)pst_netbuf, (oal_uint)pst_rx_ctrl);
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
         mac_rx_report_80211_frame((oal_uint8 *)&(pst_vap->st_vap_base_info),
                                   (oal_uint8 *)&(pst_rx_ctrl->st_rx_info),
                                    pst_netbuf,
                                    OAM_OTA_TYPE_RX_HMAC_CB);
#endif

         return;
    }

    hmac_ba_update_rx_bitmap(pst_hmac_user, pst_frame_hdr);

    /* 情况一:不是AMSDU聚合，则该MPDU对应一个MSDU，同时对应一个NETBUF */
    if (OAL_FALSE == pst_rx_ctrl->st_rx_info.bit_amsdu_enable)
    {
#ifdef _PRE_WLAN_FEATURE_WAPI
/*lint -e730*/
        pst_wapi = hmac_user_get_wapi_ptr(&pst_vap->st_vap_base_info,
                                                        !ETHER_IS_MULTICAST(pst_frame_hdr->auc_address1),
                                                        pst_hmac_user->st_user_base_info.us_assoc_id);
/*lint +e730*/
        if (OAL_PTR_NULL == pst_wapi)
        {
            OAM_WARNING_LOG0(0, OAM_SF_WPA, "{hmac_rx_lan_frame_classify:: get pst_wapi Err!.}");
            HMAC_USER_STATS_PKT_INCR(pst_hmac_user->ul_rx_pkt_drop, 1);
            return ;
        }

        if ((OAL_TRUE == WAPI_IS_PORT_VALID(pst_wapi))
            && (OAL_PTR_NULL != pst_wapi->wapi_netbuff_rxhandle))
        {
            pst_netbuf = pst_wapi->wapi_netbuff_rxhandle(pst_wapi, pst_netbuf);
            if (OAL_PTR_NULL == pst_netbuf)
            {
                OAM_WARNING_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify:: wapi decrypt FAIL!}");
                HMAC_USER_STATS_PKT_INCR(pst_hmac_user->ul_rx_pkt_drop, 1);
                return ;
            }

            /* 重新获取该MPDU的控制信息 */
            pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
        }
#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */

        pst_netbuf = hmac_defrag_process(pst_hmac_user, pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_header_len);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            return;
        }

        /* 打印出关键帧(dhcp)信息 */
        uc_datatype = mac_get_data_type_from_80211(pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_header_len);
        if ((uc_datatype <= MAC_DATA_VIP) && (uc_datatype != MAC_DATA_ARP_REQ))
        {
            OAM_WARNING_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify::user[%d], datatype==%u, len==%u, rx_drop_cnt==%u}[0:dhcp 1:arp_req 2:arp_rsp 3:eapol]",
                             pst_rx_ctrl->st_rx_info.us_ta_user_idx,
                             uc_datatype,
                             pst_rx_ctrl->st_rx_info.us_frame_len,
                             pst_hmac_user->ul_rx_pkt_drop);

        }

        /* 对当前的msdu进行赋值 */
        st_msdu.pst_netbuf    = pst_netbuf;

        /* 将netbuf的data指针指向mac frame的payload处 */
        oal_netbuf_pull(pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_header_len);

        /* 获取源地址和目的地址 */
        mac_rx_get_sa(pst_frame_hdr, &puc_addr);
        oal_set_mac_addr(st_msdu.auc_sa, puc_addr);

        mac_rx_get_da(pst_frame_hdr, &puc_addr);
        oal_set_mac_addr(st_msdu.auc_da, puc_addr);

        OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_PREPARE_MSDU_INFO);

        /* 将MSDU转发到LAN */
        hmac_rx_transmit_msdu_to_lan(pst_vap, &st_msdu);
    }
    /* 情况二:AMSDU聚合 */
    else
    {
        st_msdu_state.uc_procd_netbuf_nums    = 0;
        st_msdu_state.uc_procd_msdu_in_netbuf = 0;

        do
        {
            /* 获取下一个要转发的msdu */
            ul_ret = hmac_rx_parse_amsdu(pst_netbuf, &st_msdu, &st_msdu_state, &en_process_state);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                                 "{hmac_rx_lan_frame_classify::hmac_rx_parse_amsdu failed[%d].}", ul_ret);
                return;
            }

            OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_PREPARE_MSDU_INFO);

            /* 将每一个MSDU转发到LAN */
            hmac_rx_transmit_msdu_to_lan(pst_vap, &st_msdu);
        }while (MAC_PROC_LAST_MSDU != en_process_state);
    }

}

/*****************************************************************************
 函 数 名  : hmac_rx_copy_netbuff
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
oal_uint32  hmac_rx_copy_netbuff(oal_netbuf_stru  **ppst_dest_netbuf, oal_netbuf_stru  *pst_src_netbuf, oal_uint8 uc_vap_id, mac_ieee80211_frame_stru **ppul_mac_hdr_start_addr)
{
    hmac_rx_ctl_stru  *pst_rx_ctrl;

    if (OAL_PTR_NULL == pst_src_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_dest_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == *ppst_dest_netbuf))
    {
        OAM_WARNING_LOG0(uc_vap_id, OAM_SF_RX, "{hmac_rx_copy_netbuff::pst_netbuf_copy null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 信息复制 */
    oal_memcopy(oal_netbuf_cb(*ppst_dest_netbuf), oal_netbuf_cb(pst_src_netbuf), OAL_SIZEOF(hmac_rx_ctl_stru)); //modify src bug
    oal_memcopy(oal_netbuf_data(*ppst_dest_netbuf), oal_netbuf_data(pst_src_netbuf), OAL_NETBUF_LEN(pst_src_netbuf));

    /* 设置netbuf长度、TAIL指针 */
    oal_netbuf_put(*ppst_dest_netbuf, oal_netbuf_get_len(pst_src_netbuf));

    /* 调整MAC帧头的指针copy后，对应的mac header的头已经发生变化) */
    pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(*ppst_dest_netbuf);
    pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr = (oal_uint32 *)oal_netbuf_data(*ppst_dest_netbuf);
    *ppul_mac_hdr_start_addr = (mac_ieee80211_frame_stru *)oal_netbuf_data(*ppst_dest_netbuf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_filter
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
oal_void  hmac_rx_process_data_filter(oal_netbuf_head_stru *pst_netbuf_header, oal_netbuf_stru *pst_temp_netbuf, oal_uint16 us_netbuf_num)
{
    oal_netbuf_stru                    *pst_netbuf;
    hmac_rx_ctl_stru                   *pst_rx_ctrl;
#ifdef _PRE_WLAN_FEATURE_AMPDU
    hmac_user_stru                     *pst_hmac_user;
    mac_ieee80211_frame_stru           *pst_frame_hdr;
#endif
    oal_uint8                           uc_buf_nums;
    mac_vap_stru                       *pst_vap;
    oal_uint32                          ul_ret = OAL_SUCC;
    oal_bool_enum_uint8                 en_is_ba_buf;
    oal_uint8                           uc_netbuf_num;

    while (0 != us_netbuf_num)
    {
        en_is_ba_buf = OAL_FALSE;
        pst_netbuf  = pst_temp_netbuf;
        if (OAL_PTR_NULL == pst_netbuf)
        {
            OAM_WARNING_LOG1(0, OAM_SF_RX, "{hmac_rx_process_data_filter::us_netbuf_num = %d}",us_netbuf_num);
            break;
        }

        pst_rx_ctrl   = (hmac_rx_ctl_stru*)oal_netbuf_cb(pst_netbuf);
#ifdef _PRE_WLAN_FEATURE_AMPDU
        pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctrl->st_rx_info))); //make sure ta user idx is exist
        pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
#endif
        uc_buf_nums   = pst_rx_ctrl->st_rx_info.bit_buff_nums;

        /* 获取下一个要处理的MPDU */
        oal_netbuf_get_appointed_netbuf(pst_netbuf, uc_buf_nums, &pst_temp_netbuf);
        us_netbuf_num = OAL_SUB(us_netbuf_num, uc_buf_nums);

        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_rx_ctrl->st_rx_info.uc_mac_vap_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
        {
            hmac_rx_free_netbuf_list(pst_netbuf_header, uc_buf_nums);
            OAM_WARNING_LOG0(pst_rx_ctrl->st_rx_info.bit_vap_id, OAM_SF_RX, "{hmac_rx_process_data_filter::pst_vap null.}");
            continue;
        }

        /*  start, modified: 2015/04/08 */
        if (0 == pst_vap->uc_vap_id || WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT < pst_vap->uc_vap_id)
        {
            OAM_ERROR_LOG1(0, OAM_SF_RX, "{hmac_rx_process_data_filter::Invalid vap_id.vap_id[%u]}",pst_vap->uc_vap_id);
            hmac_rx_free_netbuf_list(pst_netbuf_header, uc_buf_nums);
            continue;
        }
        /*  end */


#ifdef _PRE_WLAN_FEATURE_AMPDU
        if(OAL_FALSE == pst_rx_ctrl->st_rx_info.bit_amsdu_enable)
        {
            ul_ret = hmac_ba_filter_serv(pst_vap, pst_hmac_user, pst_rx_ctrl, pst_frame_hdr, pst_netbuf_header, &en_is_ba_buf);
            OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_REORDER_FILTER);
        }
        else
        {
            ul_ret = OAL_SUCC;
        }
#endif

        if (OAL_SUCC != ul_ret)
        {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            //OAM_WARNING_LOG0(pst_rx_ctrl->st_rx_info.bit_vap_id, OAM_SF_RX, "{hmac_rx_process_data_filter::hmac_ba_filter_serv proc error.}");
#endif /* 1151暂时注释掉不打印 */
            hmac_rx_free_netbuf_list(pst_netbuf_header, uc_buf_nums);
            continue;
        }

        if (OAL_TRUE == en_is_ba_buf)
        {
            continue;
        }

        /*如果不buff进reorder队列，则重新挂到链表尾，保序*/
        for (uc_netbuf_num = 0; uc_netbuf_num < uc_buf_nums; uc_netbuf_num++)
        {
            pst_netbuf = oal_netbuf_delist(pst_netbuf_header);

            if (OAL_LIKELY(OAL_PTR_NULL != pst_netbuf))
            {
                oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);
            }
            else
            {
                OAM_WARNING_LOG0(pst_rx_ctrl->st_rx_info.bit_vap_id, OAM_SF_RX, "{hmac_rx_process_data_filter::no buff error.}");
            }
        }
        OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_NON_REORDER_BACK);
    }

}

#ifdef _PRE_WLAN_TCP_OPT
OAL_STATIC  oal_bool_enum_uint8 hmac_transfer_rx_handler(hmac_device_stru* pst_hmac_device,hmac_vap_stru * hmac_vap,oal_netbuf_stru* netbuf)
{
#ifndef WIN32
    hmac_rx_ctl_stru                   *pst_rx_ctrl;                        /* 指向MPDU控制块信息的指针 */
    oal_netbuf_stru* pst_mac_llc_snap_netbuf;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    if(OAL_TRUE == pst_hmac_device->sys_tcp_rx_ack_opt_enable)
    {
        pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(netbuf);
        pst_mac_llc_snap_netbuf = (oal_netbuf_stru*)(netbuf->data + pst_rx_ctrl->st_rx_info.uc_mac_header_len);
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
        OAM_WARNING_LOG1(0, OAM_SF_TX,
                             "{hmac_transfer_rx_handler::uc_mac_header_len = %d}\r\n",pst_rx_ctrl->st_rx_info.uc_mac_header_len);
#endif
        if(OAL_TRUE == hmac_judge_rx_netbuf_classify(pst_mac_llc_snap_netbuf))
        {
#ifdef _PRE_WLAN_TCP_OPT_DEBUG
            OAM_WARNING_LOG0(0, OAM_SF_TX,
                                 "{hmac_transfer_rx_handler::netbuf is tcp ack.}\r\n");
#endif
            oal_spin_lock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_RX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            oal_netbuf_list_tail(&hmac_vap->st_hamc_tcp_ack[HCC_RX].data_queue[HMAC_TCP_ACK_QUEUE],
                            netbuf);
            pst_hmac_device->en_need_notify = OAL_TRUE;
            oal_spin_unlock_bh(&hmac_vap->st_hamc_tcp_ack[HCC_RX].data_queue_lock[HMAC_TCP_ACK_QUEUE]);
            hmac_sched_transfer();
            return OAL_TRUE;
        }
    }
#endif
#endif
    return OAL_FALSE;
}

#endif

/*****************************************************************************
 函 数 名  : hmac_rx_lan_frame
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
oal_uint32  hmac_rx_lan_frame(oal_netbuf_head_stru *pst_netbuf_header)
{
    oal_uint32                 ul_netbuf_num;
    oal_netbuf_stru           *pst_temp_netbuf;
    oal_netbuf_stru           *pst_netbuf;
    oal_uint8                  uc_buf_nums;
    hmac_rx_ctl_stru          *pst_rx_ctrl;
    mac_ieee80211_frame_stru  *pst_frame_hdr;
    hmac_vap_stru             *pst_vap;

    ul_netbuf_num   = oal_netbuf_get_buf_num(pst_netbuf_header);
    pst_temp_netbuf = oal_netbuf_peek(pst_netbuf_header);

    //OAM_INFO_LOG1(0, OAM_SF_RX, "{hmac_rx_lan_frame::prepare %d netbuf up to netdevice.}", ul_netbuf_num);

    while (0 != ul_netbuf_num)
    {
        pst_netbuf = pst_temp_netbuf;
        if(NULL == pst_netbuf)
        {
            break;
        }

        pst_rx_ctrl   = (hmac_rx_ctl_stru*)oal_netbuf_cb(pst_netbuf);
        pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
        uc_buf_nums = pst_rx_ctrl->st_rx_info.bit_buff_nums;

        ul_netbuf_num = OAL_SUB(ul_netbuf_num, uc_buf_nums);
        oal_netbuf_get_appointed_netbuf(pst_netbuf, uc_buf_nums, &pst_temp_netbuf);

        pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_rx_ctrl->st_rx_info.uc_mac_vap_id);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_RX, "{hmac_rx_lan_frame::mac_res_get_hmac_vap null. vap_id:%u}",pst_rx_ctrl->st_rx_info.uc_mac_vap_id);
            continue;
        }
        pst_rx_ctrl->st_rx_info.us_da_user_idx = pst_vap->st_vap_base_info.uc_assoc_vap_id;

        hmac_rx_lan_frame_classify(pst_vap, pst_netbuf, pst_frame_hdr);
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_HILINK
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
extern oal_uint32 hwal_send_others_bss_data(oal_netbuf_stru *pst_netbuf);
#endif
/*****************************************************************************
 函 数 名  : hmac_rx_process_others_bss_data
 功能描述  : HMAC模块接收到其他BSS网络数据帧的处理函数
 输入参数  : 事件结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月25日
    作    者   : 任磊
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_rx_process_others_bss_data(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event          = OAL_PTR_NULL;
    frw_event_hdr_stru         *pst_event_hdr      = OAL_PTR_NULL;
    oal_netbuf_stru            *pst_netbuf         = OAL_PTR_NULL;
    oal_netbuf_stru            *pst_temp_netbuf    = OAL_PTR_NULL;
    dmac_wlan_drx_event_stru   *pst_wlan_rx_event  = OAL_PTR_NULL;
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_uint32                  ul_ret;
#endif
    oal_uint16                  us_netbuf_num;
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_wlan_rx_event   = (dmac_wlan_drx_event_stru *)(pst_event->auc_event_data);
    us_netbuf_num       = pst_wlan_rx_event->us_netbuf_num;
    pst_netbuf          = pst_wlan_rx_event->pst_netbuf;
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    while(0 != us_netbuf_num)
    {
        pst_temp_netbuf = pst_netbuf;
        if (OAL_PTR_NULL == pst_temp_netbuf)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }
        pst_netbuf = OAL_NETBUF_NEXT(pst_temp_netbuf);
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
        /* 抛事件到wal层会出现由于事件队列满导致抛事件失败,直接调用可以提高效率 */
        ul_ret = hwal_send_others_bss_data(pst_temp_netbuf);
        if (OAL_SUCC != ul_ret)
        {
            hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
            return OAL_FAIL;
        }
        us_netbuf_num--;
#else
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_FAIL;
#endif
    }
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_ap
 功能描述  : AP模式下，HMAC模块接收WLAN_DRX事件(数据帧)的处理函数
 输入参数  : 事件结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_rx_process_data_ap(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    dmac_wlan_drx_event_stru           *pst_wlan_rx_event;
    oal_netbuf_stru                    *pst_netbuf;                     /* 用于保存当前处理的MPDU的第一个netbuf指针 */
    oal_netbuf_stru                    *pst_temp_netbuf;                /* 用于临时保存下一个需要处理的netbuf指针 */
    oal_uint16                          us_netbuf_num;                  /* netbuf链表的个数 */
    oal_netbuf_head_stru                st_netbuf_header;               /* 存储上报给网络层的数据 */
    hmac_vap_stru                      *pst_hmac_vap;
#ifdef _PRE_WLAN_TCP_OPT
    oal_netbuf_head_stru                st_temp_header;
    hmac_device_stru                   *pst_hmac_device;
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
    dmac_rx_ctl_stru                   *pst_cb_ctrl = OAL_PTR_NULL;
    oal_uint32                          ul_ret;
#endif


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_process_data_ap::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_START);

    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_wlan_rx_event   = (dmac_wlan_drx_event_stru *)(pst_event->auc_event_data);
    pst_temp_netbuf     = pst_wlan_rx_event->pst_netbuf;
    us_netbuf_num       = pst_wlan_rx_event->us_netbuf_num;
#ifdef _PRE_WLAN_FEATURE_HILINK
    pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_temp_netbuf);
    if (WLAN_HAL_OHTER_BSS_CAST_DATA_ID == pst_cb_ctrl->st_rx_info.bit_vap_id)
    {
        /*处理上报的其他BSS组播数据包*/
       ul_ret = hmac_rx_process_others_bss_data(pst_event_mem);
       if(OAL_SUCC != ul_ret)
       {
            OAM_ERROR_LOG1(0, OAM_SF_RX, "hmac_rx_process_data_ap::process other bss data is failed! ul_ret=%d",ul_ret);
            hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
            return ul_ret;
       }
       return OAL_SUCC;
    }
#endif

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_BASE_INFO);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_temp_netbuf))
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{hmac_rx_process_data_ap::us_netbuf_num = %d.}",us_netbuf_num);
        return OAL_SUCC; /* 这个是事件处理函数，为了防止51的UT挂掉 返回 true */
    }
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_device = hmac_res_get_mac_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_process_data_ap::pst_hmac_device null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_process_data_ap::pst_hmac_vap null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*暂时规避mib_info 指针为空的问题，
      If mib info is null ptr,release the netbuf*/
    if(OAL_PTR_NULL == pst_hmac_vap->st_vap_base_info.pst_mib_info)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_process_data_ap::pst_mib_info null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_SUCC;
    }
#endif

    /*将所有netbuff全部入链表*/
    oal_netbuf_list_head_init(&st_netbuf_header);
    while (0 != us_netbuf_num)
    {
        pst_netbuf = pst_temp_netbuf;
        if (OAL_PTR_NULL == pst_netbuf)
        {
            break;
        }

        pst_temp_netbuf = OAL_NETBUF_NEXT(pst_netbuf);
        oal_netbuf_add_to_list_tail(pst_netbuf, &st_netbuf_header);
        us_netbuf_num--;

    }

    if(0 != us_netbuf_num)
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_rx_process_data_ap::us_netbuf_num[%d], event_buf_num[%d].}",
                        us_netbuf_num, pst_wlan_rx_event->us_netbuf_num);
    }

    /*将Dmac上报的帧进入reorder队列过滤一下*/
    hmac_rx_process_data_filter(&st_netbuf_header, pst_wlan_rx_event->pst_netbuf, pst_wlan_rx_event->us_netbuf_num);

#ifdef _PRE_WLAN_TCP_OPT
    oal_netbuf_head_init(&st_temp_header);

    while(!!(pst_temp_netbuf = oal_netbuf_delist(&st_netbuf_header)))
    {
        if(OAL_FALSE == hmac_transfer_rx_handler(pst_hmac_device,pst_hmac_vap,pst_temp_netbuf))
        {
            oal_netbuf_list_tail(&st_temp_header,pst_temp_netbuf);
        }
    }
    /*lint -e522*/
    OAL_WARN_ON(!oal_netbuf_list_empty(&st_netbuf_header));
    /*lint +e522*/
    oal_netbuf_splice_init(&st_temp_header, &st_netbuf_header);
#endif

    hmac_rx_process_data_ap_tcp_ack_opt(pst_hmac_vap,&st_netbuf_header);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_rx_process_data_ap_tcp_ack_opt
 功能描述  : AP模式下，HMAC模块接收WLAN_DRX事件(数据帧)的处理函数
 输入参数  : 事件结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_process_data_ap_tcp_ack_opt(hmac_vap_stru *pst_vap,oal_netbuf_head_stru* pst_netbuf_header)
{
    frw_event_hdr_stru                 st_event_hdr;
    mac_ieee80211_frame_stru           *pst_frame_hdr;                  /* 保存mac帧的指针 */
    mac_ieee80211_frame_stru           *pst_copy_frame_hdr;             /* 保存mac帧的指针 */
    oal_uint8                          *puc_da;                         /* 保存用户目的地址的指针 */
    hmac_user_stru                     *pst_hmac_da_user;
    oal_uint32                          ul_rslt;
    oal_uint16                          us_user_dix;
    hmac_rx_ctl_stru                   *pst_rx_ctrl;                    /* 每一个MPDU的控制信息 */
    oal_uint16                          us_netbuf_num;                  /* netbuf链表的个数 */
    oal_uint8                           uc_buf_nums;                    /* 每个mpdu占有buf的个数 */
    oal_netbuf_stru                    *pst_netbuf;                     /* 用于保存当前处理的MPDU的第一个netbuf指针 */
    oal_netbuf_stru                    *pst_temp_netbuf;                /* 用于临时保存下一个需要处理的netbuf指针 */
    oal_netbuf_stru                    *pst_netbuf_copy;                /* 用于保存组播帧copy */
    oal_netbuf_head_stru                st_w2w_netbuf_hdr;              /* 保存wlan to wlan的netbuf链表的头 */
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
        cs_isolation_forward_enum           en_forward;
#endif

    /* 循环收到的每一个MPDU，处情况如下:
        1、组播帧时，调用WLAN TO WLAN和WLAN TO LAN接口
        2、其他，根据实际情况，调用WLAN TO LAN接口或者WLAN TO WLAN接口 */
    oal_netbuf_list_head_init(&st_w2w_netbuf_hdr);
    pst_temp_netbuf = oal_netbuf_peek(pst_netbuf_header);
    us_netbuf_num = (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header);
    st_event_hdr.uc_chip_id = pst_vap->st_vap_base_info.uc_chip_id;
    st_event_hdr.uc_device_id = pst_vap->st_vap_base_info.uc_device_id;
    st_event_hdr.uc_vap_id = pst_vap->st_vap_base_info.uc_vap_id;

    while (0 != us_netbuf_num)
    {
        pst_netbuf  = pst_temp_netbuf;
        if (OAL_PTR_NULL == pst_netbuf)
        {
            break;
        }

        pst_rx_ctrl   = (hmac_rx_ctl_stru*)oal_netbuf_cb(pst_netbuf);

        /* 获取帧头信息 */
        pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

        /* 获取当前MPDU占用的netbuf数目 */
        uc_buf_nums   = pst_rx_ctrl->st_rx_info.bit_buff_nums;

        /* 获取下一个要处理的MPDU */
        oal_netbuf_get_appointed_netbuf(pst_netbuf, uc_buf_nums, &pst_temp_netbuf);
        us_netbuf_num = OAL_SUB(us_netbuf_num, uc_buf_nums);

        pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_rx_ctrl->st_rx_info.uc_mac_vap_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
        {
            OAM_WARNING_LOG0(pst_rx_ctrl->st_rx_info.bit_vap_id, OAM_SF_RX, "{hmac_rx_process_data_ap::pst_vap null.}");
            hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)uc_buf_nums);
            continue;
        }

        /* 获取接收端地址  */
        mac_rx_get_da(pst_frame_hdr, &puc_da);

        /* 目的地址为组播地址时，进行WLAN_TO_WLAN和WLAN_TO_LAN的转发 */
        if (ETHER_IS_MULTICAST(puc_da))
        {
            OAM_INFO_LOG0(st_event_hdr.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify::the frame is a group frame.}");
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_mcast_cnt, 1);

            if (OAL_SUCC != hmac_rx_copy_netbuff(&pst_netbuf_copy, pst_netbuf, pst_rx_ctrl->st_rx_info.uc_mac_vap_id, &pst_copy_frame_hdr))
            {
                OAM_WARNING_LOG0(st_event_hdr.uc_vap_id, OAM_SF_RX, "{hmac_rx_process_data_ap::send mcast pkt to air fail.}");

                OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_no_buff_dropped, 1);
                continue;
            }

            hmac_rx_lan_frame_classify(pst_vap, pst_netbuf, pst_frame_hdr); //上报网络层

        #ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
            pst_rx_ctrl   = (hmac_rx_ctl_stru*)oal_netbuf_cb(pst_netbuf_copy);

            /* 获取帧头信息 */
            pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
            mac_rx_get_da(pst_frame_hdr, &puc_da);

            en_forward = hmac_isolation_filter(&pst_vap->st_vap_base_info, puc_da);
            if (CS_ISOLATION_FORWORD_DROP == en_forward)
            {
                /* 释放当前处理的MPDU占用的netbuf. 2014.7.29 cause memory leak bug fixed */
                /* OAL_IO_PRINT("isolation drop %d-%d\n",uc_netbuf_num,uc_buf_nums);1-1 */
                hmac_rx_free_netbuf(pst_netbuf_copy, (oal_uint16)uc_buf_nums);
                continue;
            }
        #endif

            /* 将MPDU解析成单个MSDU，把所有的MSDU组成一个netbuf链 */
            hmac_rx_prepare_msdu_list_to_wlan(pst_vap, &st_w2w_netbuf_hdr, pst_netbuf_copy, pst_copy_frame_hdr);
            continue;
        }

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
        en_forward = hmac_isolation_filter(&pst_vap->st_vap_base_info, puc_da);
        if (CS_ISOLATION_FORWORD_DROP == en_forward)
        {
            /* 释放当前处理的MPDU占用的netbuf. 2014.7.29 cause memory leak bug fixed */
            /* OAL_IO_PRINT("isolation drop %d-%d\n",uc_netbuf_num,uc_buf_nums);1-1 */
            hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)uc_buf_nums);
            /*return OAL_SUCC; bug fixed */
            continue;
        }
#endif

        /* 获取目的地址对应的用户指针 */
        ul_rslt = mac_vap_find_user_by_macaddr(&pst_vap->st_vap_base_info, puc_da, &us_user_dix);
        if (OAL_ERR_CODE_PTR_NULL == ul_rslt )  /* 查找用户失败 */
        {
            /* 释放当前处理的MPDU占用的netbuf */
            hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)uc_buf_nums);

            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_da_check_dropped, 1);
            continue;
        }

        /* 没有找到对应的用户 */
        if (OAL_SUCC != ul_rslt)
        {
            OAM_INFO_LOG0(st_event_hdr.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify::the frame is a unique frame.}");
            /* 目的用户不在AP的用户表中，调用wlan_to_lan转发接口 */
            hmac_rx_lan_frame_classify(pst_vap, pst_netbuf, pst_frame_hdr);
            continue;
        }

        /* 目的用户已在AP的用户表中，进行WLAN_TO_WLAN转发 */
        pst_hmac_da_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_dix);

        if (OAL_PTR_NULL == pst_hmac_da_user)
        {
            OAM_WARNING_LOG0(st_event_hdr.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify::pst_hmac_da_user null.}");
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_da_check_dropped, 1);

            hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)uc_buf_nums);
            continue;
        }

        if (MAC_USER_STATE_ASSOC != pst_hmac_da_user->st_user_base_info.en_user_asoc_state)
        {
            OAM_WARNING_LOG0(st_event_hdr.uc_vap_id, OAM_SF_RX, "{hmac_rx_lan_frame_classify::the station is not associated with ap.}");
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, rx_da_check_dropped, 1);

            hmac_rx_free_netbuf(pst_netbuf, (oal_uint16)uc_buf_nums);
            hmac_mgmt_send_deauth_frame(&pst_vap->st_vap_base_info, puc_da, MAC_NOT_AUTHED, OAL_FALSE);

            continue;
        }

        /* 将目的地址的资源池索引值放到cb字段中，user的asoc id会在关联的时候被赋值 */
        pst_rx_ctrl->st_rx_info.us_da_user_idx = pst_hmac_da_user->st_user_base_info.us_assoc_id;

        /* 将MPDU解析成单个MSDU，把所有的MSDU组成一个netbuf链 */
        hmac_rx_prepare_msdu_list_to_wlan(pst_vap, &st_w2w_netbuf_hdr, pst_netbuf, pst_frame_hdr);
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_TO_LAN);

    /*  将MSDU链表交给发送流程处理 */
    if (OAL_FALSE == oal_netbuf_list_empty(&st_w2w_netbuf_hdr) && OAL_PTR_NULL != oal_netbuf_tail(&st_w2w_netbuf_hdr) &&
        OAL_PTR_NULL != oal_netbuf_peek(&st_w2w_netbuf_hdr))
    {
        OAL_NETBUF_NEXT((oal_netbuf_tail(&st_w2w_netbuf_hdr))) = OAL_PTR_NULL;
        OAL_NETBUF_PREV((oal_netbuf_peek(&st_w2w_netbuf_hdr))) = OAL_PTR_NULL;

        hmac_rx_transmit_to_wlan(&st_event_hdr, &st_w2w_netbuf_hdr);
    }
    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_TO_WLAN);

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_END);

}

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_sta
 功能描述  : STA模式下，HMAC模块接收WLAN_DRX事件(数据帧)的处理函数
 输入参数  : 事件结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月5日
    作    者   : 
    修改内容   : 新生成函数

************************ *****************************************************/
oal_uint32  hmac_rx_process_data_sta(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    dmac_wlan_drx_event_stru           *pst_wlan_rx_event;
    oal_netbuf_stru                    *pst_netbuf;                /* 用于临时保存下一个需要处理的netbuf指针 */
    oal_uint16                          us_netbuf_num;                  /* netbuf链表的个数 */
    oal_netbuf_head_stru                st_netbuf_header;               /* 存储上报给网络层的数据 */
    oal_netbuf_stru                    *pst_temp_netbuf;
    hmac_vap_stru                      *pst_hmac_vap;
#ifdef _PRE_WLAN_TCP_OPT
    oal_netbuf_head_stru                st_temp_header;
    hmac_device_stru                   *pst_hmac_device;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_process_data_sta::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_START);
    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_DATA_START);

    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_wlan_rx_event   = (dmac_wlan_drx_event_stru *)(pst_event->auc_event_data);
    pst_temp_netbuf     = pst_wlan_rx_event->pst_netbuf;
    us_netbuf_num       = pst_wlan_rx_event->us_netbuf_num;

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_BASE_INFO);

#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_device = hmac_res_get_mac_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_process_data_sta::pst_hmac_device null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_process_data_sta::pst_hmac_vap null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* If mib info is null ptr,release the netbuf */
    if(NULL == pst_hmac_vap->st_vap_base_info.pst_mib_info)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_rx_process_data_sta::pst_mib_info null.}");
        hmac_rx_free_netbuf(pst_temp_netbuf, us_netbuf_num);
        return OAL_SUCC;
    }
#endif

    /*将所有netbuff全部入链表*/
    oal_netbuf_list_head_init(&st_netbuf_header);
    while (0 != us_netbuf_num)
    {
        pst_netbuf = pst_temp_netbuf;
        if (OAL_PTR_NULL == pst_netbuf)
        {
            break;
        }

        pst_temp_netbuf = OAL_NETBUF_NEXT(pst_netbuf);
        oal_netbuf_add_to_list_tail(pst_netbuf, &st_netbuf_header);
        us_netbuf_num--;
    }

    if(0 != us_netbuf_num)
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_rx_process_data_sta::us_netbuf_num[%d], event_buf_num[%d].}",
                        us_netbuf_num, pst_wlan_rx_event->us_netbuf_num);
    }

    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_GET_NETBUF_LIST);

    hmac_rx_process_data_filter(&st_netbuf_header, pst_wlan_rx_event->pst_netbuf, pst_wlan_rx_event->us_netbuf_num);

#ifdef _PRE_WLAN_TCP_OPT
    oal_netbuf_head_init(&st_temp_header);
    while(!!(pst_temp_netbuf = oal_netbuf_delist(&st_netbuf_header)))
    {
        if(OAL_FALSE == hmac_transfer_rx_handler(pst_hmac_device,pst_hmac_vap,pst_temp_netbuf))
        {
            oal_netbuf_list_tail(&st_temp_header,pst_temp_netbuf);
        }
    }
    /*lint -e522*/
    OAL_WARN_ON(!oal_netbuf_list_empty(&st_netbuf_header));
    /*lint +e522*/
    oal_netbuf_splice_init(&st_temp_header, &st_netbuf_header);
#endif
    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_TCP_ACK_OPT);

    hmac_rx_process_data_sta_tcp_ack_opt(pst_hmac_vap,&st_netbuf_header);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_process_data_sta
 功能描述  : STA模式下，HMAC模块接收WLAN_DRX事件(数据帧)的处理函数
 输入参数  : 事件结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_rx_process_data_sta_tcp_ack_opt(hmac_vap_stru *pst_vap,oal_netbuf_head_stru* pst_netbuf_header)
{
    /*将需要上报的帧逐一出队处理*/
    hmac_rx_lan_frame(pst_netbuf_header);

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_HMAC_END);
    OAL_MIPS_RX_STATISTIC(HMAC_PROFILING_FUNC_RX_HMAC_END);
#ifdef _PRE_WLAN_PROFLING_MIPS
    oal_profiling_stop_rx_save();
#endif
    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

