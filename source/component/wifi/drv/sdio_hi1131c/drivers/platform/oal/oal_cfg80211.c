/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_cfg80211.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2014年5月9日
  最近修改   :
  功能描述   : 80211的事件上报hostapd和wpa_supplicant事件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月9日
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
#include "oam_wdk.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_CFG80211_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
static oal_kobj_uevent_env_stru env;
#endif
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_cfg80211_ready_on_channel
 功能描述  : 上报linux 内核已经处于指定信道
 输入参数  : oal_wireless_dev_stru       *pst_wdev
             oal_uint64                  ull_cookie
             oal_ieee80211_channel_stru *pst_chan
             oal_uint32                  ul_duration
             oal_gfp_enum_uint8          en_gfp
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月22日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_cfg80211_ready_on_channel(oal_wireless_dev_stru       *pst_wdev,
                                        oal_uint64                  ull_cookie,
                                        oal_ieee80211_channel_stru *pst_chan,
                                        oal_uint32                  ul_duration,
                                        oal_gfp_enum_uint8          en_gfp)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 44))
     cfg80211_ready_on_channel(pst_wdev, ull_cookie, pst_chan, ul_duration, en_gfp);
#endif
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_remain_on_channel_expired
 功能描述  : 监听超时上报
 输入参数  : oal_wireless_dev_stru        *pst_wdev
             oal_uint64                   ull_cookie
             oal_ieee80211_channel_stru  *pst_listen_channel
             oal_gfp_enum_uint8           en_gfp
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_cfg80211_remain_on_channel_expired(oal_wireless_dev_stru        *pst_wdev,
                                        oal_uint64                   ull_cookie,
                                        oal_ieee80211_channel_stru  *pst_listen_channel,
                                        oal_gfp_enum_uint8           en_gfp)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 44))
    cfg80211_remain_on_channel_expired(pst_wdev,
                                        ull_cookie,
                                        pst_listen_channel,
                                        GFP_ATOMIC);
#endif
#endif
}

oal_void oal_cfg80211_mgmt_tx_status(struct wireless_dev *wdev, oal_uint64 cookie,
                 OAL_CONST oal_uint8 *buf, size_t len, oal_bool_enum_uint8 ack, oal_gfp_enum_uint8 gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    cfg80211_mgmt_tx_status(wdev, cookie, buf, len, ack, gfp);
#endif
}

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#else
/*****************************************************************************
 函 数 名  : oal_cfg80211_calculate_bitrate
 功能描述  : oal_cfg80211_new_sta上报new sta事件获取比特率值(参考内核实现)
             如果MCS大于等于32，就返回错误OAL_ERR_CODE_CFG80211_MCS_EXCEED
 输入参数  : pst_rate: 速率信息结构
 输出参数  :
 返 回 值  : l_bitrate: 比特率
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32 oal_cfg80211_calculate_bitrate(oal_rate_info_stru *pst_rate)
{
    oal_int32  l_modulation;
    oal_int32  l_streams;
    oal_int32  l_bitrate;

    if (0 == (pst_rate->flags & RATE_INFO_FLAGS_MCS))
    {
        return pst_rate->legacy;
    }

    /* the formula below does only work for MCS values smaller than 32 */
    if (pst_rate->mcs >= 32)
    {
        return -OAL_ERR_CODE_CFG80211_MCS_EXCEED;
    }
    l_modulation = pst_rate->mcs & 7;
    l_streams = (pst_rate->mcs >> 3) + 1;

    l_bitrate = (pst_rate->flags & RATE_INFO_FLAGS_40_MHZ_WIDTH) ? 13500000 : 6500000;

    if (l_modulation < 4)
    {
        l_bitrate *= (l_modulation + 1);
    }
    else if (l_modulation == 4)
    {
        l_bitrate *= (l_modulation + 2);
    }
    else
    {
        l_bitrate *= (l_modulation + 3);
    }
    l_bitrate *= l_streams;

    if(pst_rate->flags & RATE_INFO_FLAGS_SHORT_GI)
    {
        l_bitrate = (l_bitrate / 9) * 10;
    }
    /* do NOT round down here */
    return (l_bitrate + 50000) / 100000;
}

/*****************************************************************************
 函 数 名  : oal_nl80211_send_station
 功能描述  : netlink上报send new sta事件进行命令符号和属性值填充
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32  oal_nl80211_send_station(
                oal_netbuf_stru *pst_buf, oal_uint32 ul_pid, oal_uint32 ul_seq,
				oal_int32 l_flags, oal_net_device_stru *pst_net_dev,
				const oal_uint8 *puc_mac_addr, oal_station_info_stru *pst_station_info)
{
	oal_nlattr_stru   *pst_sinfoattr = OAL_PTR_NULL;
	oal_nlattr_stru   *pst_txrate    = OAL_PTR_NULL;
	oal_void          *p_hdr         = OAL_PTR_NULL;
	oal_int32          us_bitrate;

    /* Add generic netlink header to netlink message, returns pointer to user specific header */
	p_hdr = oal_genlmsg_put(pst_buf, ul_pid, ul_seq, &nl80211_fam, l_flags, PRIV_NL80211_CMD_NEW_STATION);
	if (OAL_PTR_NULL == p_hdr)
	{
	    return OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL;
	}

	OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_ATTR_IFINDEX, pst_net_dev->ifindex);
	OAL_NLA_PUT(pst_buf, PRIV_NL80211_ATTR_MAC, OAL_ETH_ALEN_SIZE, puc_mac_addr);

    /*
        linux-2.6.30内核station_info没有generation成员
    	NLA_PUT_U32(pst_buf, PRIV_NL80211_ATTR_GENERATION, pst_station_info->generation);
    */

	pst_sinfoattr = oal_nla_nest_start(pst_buf, PRIV_NL80211_ATTR_STA_INFO);
	if (OAL_PTR_NULL == pst_sinfoattr)
	{
        oal_genlmsg_cancel(pst_buf, p_hdr);
        return OAL_ERR_CODE_CFG80211_EMSGSIZE;
	}
	if (pst_station_info->filled & STATION_INFO_INACTIVE_TIME)
	{
		OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_STA_INFO_INACTIVE_TIME, pst_station_info->inactive_time);
	}
	if (pst_station_info->filled & STATION_INFO_RX_BYTES)
	{
	    OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_STA_INFO_RX_BYTES, pst_station_info->rx_bytes);
    }
	if (pst_station_info->filled & STATION_INFO_TX_BYTES)
	{
	    OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_STA_INFO_TX_BYTES, pst_station_info->tx_bytes);
    }
	if (pst_station_info->filled & STATION_INFO_LLID)
	{
	    OAL_NLA_PUT_U16(pst_buf, PRIV_NL80211_STA_INFO_LLID, pst_station_info->llid);
	}
	if (pst_station_info->filled & STATION_INFO_PLID)
	{
	    OAL_NLA_PUT_U16(pst_buf, PRIV_NL80211_STA_INFO_PLID, pst_station_info->plid);
	}
	if (pst_station_info->filled & STATION_INFO_PLINK_STATE)
	{
	    OAL_NLA_PUT_U8(pst_buf, PRIV_NL80211_STA_INFO_PLINK_STATE, pst_station_info->plink_state);
	}
	if (pst_station_info->filled & STATION_INFO_SIGNAL)
	{
	    OAL_NLA_PUT_U8(pst_buf, PRIV_NL80211_STA_INFO_SIGNAL, pst_station_info->signal);
	}
	if (pst_station_info->filled & STATION_INFO_TX_BITRATE)
	{
		pst_txrate = oal_nla_nest_start(pst_buf, PRIV_NL80211_STA_INFO_TX_BITRATE);
		if (OAL_PTR_NULL == pst_txrate)
		{
            oal_genlmsg_cancel(pst_buf, p_hdr);
            return OAL_ERR_CODE_CFG80211_EMSGSIZE;
		}

		/* cfg80211_calculate_bitrate will return negative for mcs >= 32 */
		us_bitrate = oal_cfg80211_calculate_bitrate(&pst_station_info->txrate);
		if (us_bitrate > 0)
			OAL_NLA_PUT_U16(pst_buf, PRIV_NL80211_RATE_INFO_BITRATE, us_bitrate);
		if (pst_station_info->txrate.flags & RATE_INFO_FLAGS_MCS)
			OAL_NLA_PUT_U8(pst_buf, PRIV_NL80211_RATE_INFO_MCS, pst_station_info->txrate.mcs);
		if (pst_station_info->txrate.flags & RATE_INFO_FLAGS_40_MHZ_WIDTH)
			OAL_NLA_PUT_FLAG(pst_buf, PRIV_NL80211_RATE_INFO_40_MHZ_WIDTH);
		if (pst_station_info->txrate.flags & RATE_INFO_FLAGS_SHORT_GI)
			OAL_NLA_PUT_FLAG(pst_buf, PRIV_NL80211_RATE_INFO_SHORT_GI);

		oal_nla_nest_end(pst_buf, pst_txrate);
	}
	if (pst_station_info->filled & STATION_INFO_RX_PACKETS)
	{
		OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_STA_INFO_RX_PACKETS, pst_station_info->rx_packets);
	}
	if (pst_station_info->filled & STATION_INFO_TX_PACKETS)
	{
		OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_STA_INFO_TX_PACKETS, pst_station_info->tx_packets);
	}

	oal_nla_nest_end(pst_buf, pst_sinfoattr);

	if(oal_genlmsg_end(pst_buf, p_hdr) < 0)
	{
//	    oal_nlmsg_free(pst_buf);
		return OAL_ERR_CODE_CFG80211_ENOBUFS;
	}

	return OAL_SUCC;

nla_put_failure:
	oal_genlmsg_cancel(pst_buf, p_hdr);
	return OAL_ERR_CODE_CFG80211_EMSGSIZE;
}

/*****************************************************************************
 函 数 名  : oal_nl80211_send_connect_result
 功能描述  : 驱动调用内核netlink接口上报关联结构
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oal_nl80211_send_connect_result(
                        oal_netbuf_stru             *pst_buf,
                        oal_net_device_stru         *pst_net_device,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                              oal_uint16             us_status,
                        oal_gfp_enum_uint8           en_gfp)
{
	oal_void         *p_hdr = OAL_PTR_NULL;
	oal_int32         ul_let;

	p_hdr = oal_genlmsg_put(pst_buf, 0, 0, &nl80211_fam, 0, PRIV_NL80211_CMD_CONNECT);
	if (OAL_PTR_NULL == p_hdr)
	{
		oal_nlmsg_free(pst_buf);
		return OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL;
	}

    /*
        这个属性上层没有解析，可以不上报
        OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_ATTR_WIPHY, pst_net_device->wiphy_idx);
    */
	OAL_NLA_PUT_U32(pst_buf, PRIV_NL80211_ATTR_IFINDEX, pst_net_device->ifindex);
	if(OAL_PTR_NULL != puc_bssid)
	{
		OAL_NLA_PUT(pst_buf, PRIV_NL80211_ATTR_MAC, OAL_ETH_ALEN_SIZE, puc_bssid);
	}
	OAL_NLA_PUT_U16(pst_buf, PRIV_NL80211_ATTR_STATUS_CODE, us_status);
	if(OAL_PTR_NULL != puc_req_ie)
	{
		OAL_NLA_PUT(pst_buf, PRIV_NL80211_ATTR_REQ_IE, ul_req_ie_len, puc_req_ie);
	}
	if(OAL_PTR_NULL != puc_resp_ie)
	{
		OAL_NLA_PUT(pst_buf, PRIV_NL80211_ATTR_RESP_IE, ul_resp_ie_len, puc_resp_ie);
	}

	if(oal_genlmsg_end(pst_buf, p_hdr) < 0)
	{
	    oal_nlmsg_free(pst_buf);
		return OAL_ERR_CODE_CFG80211_ENOBUFS;
	}

    ul_let = oal_genlmsg_multicast(pst_buf, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(ul_let < 0)
    {
        /* 如果不加载hostapd和wpa_supplicant的话，这个也会失败，这里报fail，影响使用，去掉报错 */
        return OAL_FAIL;
    }

	return OAL_SUCC;

 nla_put_failure:
	oal_genlmsg_cancel(pst_buf, p_hdr);
	oal_nlmsg_free(pst_buf);
	return OAL_ERR_CODE_CFG80211_EMSGSIZE;
}

/*****************************************************************************
 函 数 名  : oal_nl80211_send_disconnected
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32 oal_nl80211_send_disconnected(
                   oal_net_device_stru *pst_net_device,
                   oal_uint16           us_reason,
                   const oal_uint8     *puc_ie,
			       oal_uint32           ul_ie_len,
			       oal_bool_enum_uint8  from_ap,
			       oal_gfp_enum_uint8   en_gfp)
{
    oal_netbuf_stru   *pst_msg = OAL_PTR_NULL;
	oal_void          *p_hdr  = OAL_PTR_NULL;
	oal_int32          ul_let;

	pst_msg = oal_nlmsg_new(OAL_NLMSG_GOODSIZE, en_gfp);
	if (OAL_PTR_NULL == pst_msg)
	{
		return OAL_ERR_CODE_CFG80211_ENOBUFS;
	}

	p_hdr = oal_genlmsg_put(pst_msg, 0, 0, &nl80211_fam, 0, PRIV_NL80211_CMD_DISCONNECT);
	if (OAL_PTR_NULL == p_hdr)
	{
		oal_nlmsg_free(pst_msg);
		return OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL;
	}

/*
    这个属性上层没有解析，可以不上报
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_WIPHY, pst_net_device->wiphy_idx);
*/

	OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_IFINDEX, pst_net_device->ifindex);
	if (from_ap && us_reason)
		OAL_NLA_PUT_U16(pst_msg, PRIV_NL80211_ATTR_REASON_CODE, us_reason);
	if (from_ap)
		OAL_NLA_PUT_FLAG(pst_msg, PRIV_NL80211_ATTR_DISCONNECTED_BY_AP);
	if (OAL_PTR_NULL == puc_ie)
		OAL_NLA_PUT(pst_msg, PRIV_NL80211_ATTR_IE, ul_ie_len, puc_ie);

	if (oal_genlmsg_end(pst_msg, p_hdr) < 0)
	{
		oal_nlmsg_free(pst_msg);
		return OAL_ERR_CODE_CFG80211_ENOBUFS;
	}

    ul_let = oal_genlmsg_multicast(pst_msg, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(ul_let < 0)
    {
        return OAL_FAIL;
    }

	return OAL_SUCC;

 nla_put_failure:
	oal_genlmsg_cancel(pst_msg, p_hdr);
	oal_nlmsg_free(pst_msg);
	return OAL_ERR_CODE_CFG80211_EMSGSIZE;
}
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,10,44)) && (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : oal_nl80211_send_mgmt
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oal_nl80211_send_mgmt(
                        oal_cfg80211_registered_device_stru *pst_rdev,
                        oal_net_device_stru *pst_netdev,
                        oal_int32 l_freq, const oal_uint8 *puc_buf,
                        oal_uint32 ul_len, oal_gfp_enum_uint8 en_gfp)
{
    oal_netbuf_stru   *pst_msg = OAL_PTR_NULL;
    oal_void          *p_hdr   = OAL_PTR_NULL;
    oal_int32          l_let;

    pst_msg = oal_nlmsg_new(OAL_NLMSG_DEFAULT_SIZE, en_gfp);
    if(OAL_PTR_NULL == pst_msg)
    {
        return OAL_ERR_CODE_CFG80211_ENOBUFS;
    }

    p_hdr = oal_genlmsg_put(pst_msg, 0, 0, &nl80211_fam, 0, PRIV_NL80211_CMD_ACTION);
    if (OAL_PTR_NULL == p_hdr)
    {
        oal_nlmsg_free(pst_msg);
        return OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL;
    }

    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_WIPHY, pst_rdev->wiphy_idx);
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_IFINDEX, pst_netdev->ifindex);
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_WIPHY_FREQ, l_freq);
    OAL_NLA_PUT(pst_msg, PRIV_NL80211_ATTR_FRAME, ul_len, puc_buf);

    if (oal_genlmsg_end(pst_msg, p_hdr) < 0)
    {
        oal_nlmsg_free(pst_msg);
        return OAL_ERR_CODE_CFG80211_ENOBUFS;
    }

    l_let = oal_genlmsg_multicast(pst_msg, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(l_let < 0)
    {
        return OAL_FAIL;
    }

    return OAL_SUCC;

nla_put_failure:
    oal_genlmsg_cancel(pst_msg, p_hdr);
    oal_nlmsg_free(pst_msg);

    return OAL_ERR_CODE_CFG80211_EMSGSIZE;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : oal_cfg80211_sched_scan_result
 功能描述  : 上报调度扫描结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_sched_scan_result(oal_wiphy_stru *pst_wiphy)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    return cfg80211_sched_scan_results(pst_wiphy);
#endif
}
#else
/*****************************************************************************
 函 数 名  : oal_cfg80211_sched_scan_result
 功能描述  : 上报调度扫描结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_sched_scan_result(oal_wiphy_stru *pst_wiphy)
{
    /* 51不支持，do nothing */
    return;
}
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
oal_void oal_kobject_uevent_env_sta_join(oal_net_device_stru *pst_net_device, const oal_uint8 *puc_mac_addr)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_memset(&env, 0, sizeof(env));
    /* Android上层需要STA_JOIN和mac地址，中间参数无效，但是必须是4个参数 */
    add_uevent_var(&env, "SOFTAP=STA_JOIN wlan0 wlan0 %02x:%02x:%02x:%02x:%02x:%02x",
                puc_mac_addr[0], puc_mac_addr[1], puc_mac_addr[2], puc_mac_addr[3], puc_mac_addr[4], puc_mac_addr[5]);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,1,0))
    kobject_uevent_env(&(pst_net_device->dev.kobj), KOBJ_CHANGE, env.envp);
#else
    kobject_uevent_env(&(pst_net_device->dev.kobj), KOBJ_CHANGE, (char**)&env);
#endif
#endif /*#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)*/
}

oal_void oal_kobject_uevent_env_sta_leave(oal_net_device_stru *pst_net_device, const oal_uint8 *puc_mac_addr)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_memset(&env, 0, sizeof(env));
    /* Android上层需要STA_LEAVE和mac地址，中间参数无效，但是必须是4个参数 */
    add_uevent_var(&env, "SOFTAP=STA_LEAVE wlan0 wlan0 %02x:%02x:%02x:%02x:%02x:%02x",
                puc_mac_addr[0], puc_mac_addr[1], puc_mac_addr[2], puc_mac_addr[3], puc_mac_addr[4], puc_mac_addr[5]);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,1,0))
    kobject_uevent_env(&(pst_net_device->dev.kobj), KOBJ_CHANGE, env.envp);
#else
    kobject_uevent_env(&(pst_net_device->dev.kobj), KOBJ_CHANGE, (char**)&env);
#endif
#endif /*#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)*/
}
#endif

/*****************************************************************************
 函 数 名  : oal_cfg80211_put_bss
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_put_bss(oal_cfg80211_bss_stru *pst_cfg80211_bss)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
        /*cfg80211_put_bss(struct wiphy *wiphy, struct cfg80211_bss *pub)*/
#else
        return cfg80211_put_bss(pst_cfg80211_bss);
#endif

}


/*****************************************************************************
 函 数 名  : oal_cfg80211_inform_bss_frame
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_cfg80211_bss_stru *oal_cfg80211_inform_bss_frame(
                                oal_wiphy_stru              *pst_wiphy,
                                oal_ieee80211_channel_stru  *pst_ieee80211_channel,
                                oal_ieee80211_mgmt_stru     *pst_mgmt,
                                oal_uint32                   ul_len,
                                oal_int32                    l_signal,
                                oal_gfp_enum_uint8           en_ftp)
{
    return cfg80211_inform_bss_frame(pst_wiphy, pst_ieee80211_channel, pst_mgmt, ul_len, l_signal, en_ftp);
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_scan_done
 功能描述  : 上报扫描完成结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_scan_done(oal_cfg80211_scan_request_stru *pst_cfg80211_scan_request,oal_int8 c_aborted)
{
    return cfg80211_scan_done(pst_cfg80211_scan_request,c_aborted);
}


/*****************************************************************************
 函 数 名  : oal_cfg80211_connect_result
 功能描述  : STA上报给关联结果结构体
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2014年5月21日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_connect_result(
                        oal_net_device_stru         *pst_net_device,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                              oal_uint16             us_status,
                        oal_gfp_enum_uint8           en_gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

    cfg80211_connect_result(pst_net_device, puc_bssid, puc_req_ie,ul_req_ie_len,
                            puc_resp_ie, ul_resp_ie_len, us_status, en_gfp);

    return OAL_SUCC;
#else
    oal_netbuf_stru         *pst_msg  = OAL_PTR_NULL;
    oal_wireless_dev_stru   *pst_wdev = OAL_PTR_NULL;

    /* 分配一个新的netlink消息 */
    pst_msg = oal_nlmsg_new(OAL_NLMSG_GOODSIZE, en_gfp);
    if(OAL_PTR_NULL == pst_msg)
    {
        return OAL_ERR_CODE_CFG80211_ENOBUFS;
    }

    pst_wdev = pst_net_device->ieee80211_ptr;
	if (OAL_PTR_NULL == pst_wdev)
	{
		return OAL_ERR_CODE_PTR_NULL;
	}

	if (pst_wdev->iftype != NL80211_IFTYPE_STATION)
	{
		return OAL_ERR_CODE_CONFIG_UNSUPPORT;
	}

    /* 如果不加载hostapd和wpa_supplicant的话，这个也会失败，这里报fail，影响使用，去掉报错
        成功的话，打印SUCC, 不成功的话，不打印 */
    return oal_nl80211_send_connect_result(pst_msg, pst_net_device, puc_bssid, puc_req_ie, ul_req_ie_len,
                                    puc_resp_ie, ul_resp_ie_len, us_status, en_gfp);
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_disconnected
 功能描述  : STA上报给内核去关联结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2014年5月21日
    作    者   : d
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  oal_cfg80211_disconnected(
                    oal_net_device_stru        *pst_net_device,
                    oal_uint16                  us_reason,
                    oal_uint8                  *puc_ie,
                    oal_uint32                  ul_ie_len,
                    oal_gfp_enum_uint8          en_gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

    cfg80211_disconnected(pst_net_device,us_reason, puc_ie, ul_ie_len, en_gfp);

    return OAL_SUCC;
#else
    oal_wireless_dev_stru   *pst_wdev = OAL_PTR_NULL;

    pst_wdev = pst_net_device->ieee80211_ptr;
    if(OAL_PTR_NULL == pst_wdev)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

	if (pst_wdev->iftype != NL80211_IFTYPE_STATION)
	{
		return OAL_ERR_CODE_CONFIG_UNSUPPORT;
	}

	/*
	 * If this disconnect was due to a disassoc, we
	 * we might still have an auth BSS around. For
	 * the userspace SME that's currently expected,
	 * but for the kernel SME (nl80211 CONNECT or
	 * wireless extensions) we want to clear up all
	 * state.
	 */
    return oal_nl80211_send_disconnected(pst_net_device, us_reason, puc_ie,
                                         ul_ie_len, OAL_TRUE, en_gfp);
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_roamed
 功能描述  : STA上报给内核去关联结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月18日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  oal_cfg80211_roamed(
                        oal_net_device_stru         *pst_net_device,
                        struct ieee80211_channel    *pst_channel,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                        oal_gfp_enum_uint8           en_gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    cfg80211_roamed(pst_net_device, pst_channel, puc_bssid,
                    puc_req_ie, ul_req_ie_len,
                    puc_resp_ie, ul_resp_ie_len, en_gfp);
#endif
    return OAL_SUCC;

#else
    return OAL_ERR_CODE_CONFIG_UNSUPPORT;
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_ft_event
 功能描述  : STA上报给内核ft事件
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  oal_cfg80211_ft_event(oal_net_device_stru *pst_net_device, oal_cfg80211_ft_event_stru  *pst_ft_event)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    cfg80211_ft_event(pst_net_device, pst_ft_event);

    return OAL_SUCC;
#endif
    return OAL_ERR_CODE_CONFIG_UNSUPPORT;
#else
    return OAL_ERR_CODE_CONFIG_UNSUPPORT;
#endif
}

/*****************************************************************************
 函 数 名  : cfg80211_new_sta
 功能描述  : AP上报新关联某个STA情况
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2014年5月14日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_new_sta(
                oal_net_device_stru     *pst_net_device,
                const oal_uint8         *puc_mac_addr,
                oal_station_info_stru   *pst_station_info,
                oal_gfp_enum_uint8      en_gfp)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
	oal_kobject_uevent_env_sta_join(pst_net_device, puc_mac_addr);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    cfg80211_new_sta(pst_net_device, puc_mac_addr, pst_station_info, en_gfp);

    return OAL_SUCC;
#else
    oal_netbuf_stru   *pst_msg = OAL_PTR_NULL;
	oal_int32          l_let;

    /* 分配一个新的netlink消息 */
    pst_msg = oal_nlmsg_new(OAL_NLMSG_GOODSIZE, en_gfp);
    if(OAL_PTR_NULL == pst_msg)
    {
        return OAL_ERR_CODE_CFG80211_ENOBUFS;
    }

    l_let = oal_nl80211_send_station(pst_msg, 0, 0, 0, pst_net_device, puc_mac_addr, pst_station_info);
    if(OAL_SUCC != l_let)
    {
        oal_nlmsg_free(pst_msg);
        return l_let;
    }

    /* 调用封装的内核netlink广播发送函数，发送成功返回0，失败为负值 */
    l_let = oal_genlmsg_multicast(pst_msg, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(l_let < 0)
    {
        return OAL_FAIL;
    }

    return OAL_SUCC;
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_mic_failure
 功能描述  : 上报mic攻击
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2014年5月15日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_mic_failure(
                        oal_net_device_stru     *pst_net_device,
                        const oal_uint8         *puc_mac_addr,
                        enum nl80211_key_type    key_type,
                        oal_int32                key_id,
                        const oal_uint8         *puc_tsc,
                        oal_gfp_enum_uint8       en_gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    cfg80211_michael_mic_failure(pst_net_device, puc_mac_addr, key_type, key_id, puc_tsc, en_gfp);
#endif
#else
    oal_wireless_dev_stru               *pst_wdev  = OAL_PTR_NULL;
    oal_cfg80211_registered_device_stru *pst_rdev  = OAL_PTR_NULL;
    oal_netbuf_stru                     *pst_msg   = OAL_PTR_NULL;
    oal_void                            *p_hdr     = OAL_PTR_NULL;
	oal_int32                            l_let;

    pst_wdev = pst_net_device->ieee80211_ptr;
    if(OAL_PTR_NULL == pst_wdev)
    {
        return;
    }

    if(OAL_PTR_NULL == pst_wdev->wiphy)
    {
        return;
    }
    pst_rdev = oal_wiphy_to_dev(pst_wdev->wiphy);

    pst_msg = oal_nlmsg_new(OAL_NLMSG_DEFAULT_SIZE, en_gfp);
    if(OAL_PTR_NULL == pst_msg)
    {
        return;
    }

	p_hdr = oal_genlmsg_put(pst_msg, 0, 0, &nl80211_fam, 0, PRIV_NL80211_CMD_MICHAEL_MIC_FAILURE);
	if (OAL_PTR_NULL == p_hdr)
	{
        oal_nlmsg_free(pst_msg);
	    return;
	}

    /* rdev对应内核core.h中的cfg80211_registered_device结构体，这个属性在上层没有处理 */
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_WIPHY, pst_rdev->wiphy_idx);
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_IFINDEX, pst_net_device->ifindex);

    if (OAL_PTR_NULL != puc_mac_addr)
    {
        OAL_NLA_PUT(pst_msg, PRIV_NL80211_ATTR_MAC, OAL_ETH_ALEN_SIZE, puc_mac_addr);
    }
    OAL_NLA_PUT_U32(pst_msg, PRIV_NL80211_ATTR_KEY_TYPE, key_type);
    OAL_NLA_PUT_U8(pst_msg, PRIV_NL80211_ATTR_KEY_IDX, key_id);
    if (OAL_PTR_NULL != puc_tsc)
    {
         OAL_NLA_PUT(pst_msg, PRIV_NL80211_ATTR_KEY_SEQ, 6, puc_tsc);
    }

    if (oal_genlmsg_end(pst_msg, p_hdr) < 0)
    {
         oal_nlmsg_free(pst_msg);
         return;
    }

    l_let = oal_genlmsg_multicast(pst_msg, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(l_let < 0)
    {
         return;
    }
    return;
nla_put_failure:
	oal_genlmsg_cancel(pst_msg, p_hdr);
    oal_nlmsg_free(pst_msg);
    return;
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_del_sta
 功能描述  : AP上报去关联某个STA情况
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2014年5月21日
    作    者   : d
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_del_sta(oal_net_device_stru *pst_net_device,
                                   const oal_uint8      *puc_mac_addr,
                                   oal_gfp_enum_uint8    en_gfp)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
	oal_kobject_uevent_env_sta_leave(pst_net_device, puc_mac_addr);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    cfg80211_del_sta(pst_net_device, puc_mac_addr, en_gfp);

    return OAL_SUCC;
#else

    /*
        TBD   内核2.6.34中没有内核3.x版本中 cfg80211_del_sta这个函数
        linux-2.6.30和linux-2.6.34实现方式可以统一，目前34内核仍打桩，不然需要修改5115内核代码
    */
    oal_netbuf_stru  *pst_msg = OAL_PTR_NULL;
    oal_void         *p_hdr   = OAL_PTR_NULL;
    oal_int32         l_let;

    pst_msg = oal_nlmsg_new(OAL_NLMSG_DEFAULT_SIZE, en_gfp);
    if(OAL_PTR_NULL == pst_msg)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    p_hdr = oal_genlmsg_put(pst_msg, 0, 0, &nl80211_fam, 0, PRIV_NL80211_CMD_DEL_STATION);
    if(OAL_PTR_NULL == p_hdr)
    {
        oal_nlmsg_free(pst_msg);
        return OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL;
    }

    if(oal_nla_put_u32(pst_msg, PRIV_NL80211_ATTR_IFINDEX, pst_net_device->ifindex) ||
       oal_nla_put(pst_msg, PRIV_NL80211_ATTR_MAC, OAL_ETH_ALEN_SIZE, puc_mac_addr))
    {
        oal_genlmsg_cancel(pst_msg, p_hdr);
        oal_nlmsg_free(pst_msg);
        return OAL_ERR_CODE_CFG80211_EMSGSIZE;
    }

    if (oal_genlmsg_end(pst_msg, p_hdr) < 0)
    {
        oal_nlmsg_free(pst_msg);
        return OAL_ERR_CODE_CFG80211_ENOBUFS;
    }

/*
    liuux-2.6.30和liuux-2.6.34内核都是从这个函数上,都能达到要求
    linux-2.6.34内核接着调用genlmsg_multicast_netns(&init_net......)
    linux-2.6.30内核接着调用nlmsg_multicast(genl_sock......)
*/
    l_let = oal_genlmsg_multicast(pst_msg, 0, nl80211_mlme_mcgrp.id, en_gfp);
    if(l_let < 0)
    {
        return OAL_FAIL;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_rx_mgmt
 功能描述  : 上报接收到的管理帧
 输入参数  : oal_net_device_stru    *pst_dev,
             oal_int32               l_freq,
             const oal_uint8        *puc_buf,
             oal_uint32              ul_len,
             gfp_t                   gfp
 输出参数  : OAL_SUCC 上报成功，其它错误码 上报失败
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oal_cfg80211_rx_mgmt(oal_net_device_stru *pst_dev,
                                                    oal_int32               l_freq,
                                                    const oal_uint8        *puc_buf,
                                                    oal_uint32              ul_len,
                                                    oal_gfp_enum_uint8      en_gfp)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_wireless_dev_stru   *pst_wdev = OAL_PTR_NULL;
    oal_uint32               ul_ret;
    oal_bool_enum_uint8      uc_ret;
    pst_wdev = pst_dev->ieee80211_ptr;
    uc_ret   = cfg80211_rx_mgmt(pst_wdev, l_freq, 0, puc_buf, ul_len, en_gfp);
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    uc_ret=OAL_TRUE;
#endif
    /* 返回值适配   */
    (OAL_TRUE == uc_ret) ? (ul_ret = OAL_SUCC) : (ul_ret = OAL_FAIL);
    return ul_ret;
#else
    oal_wireless_dev_stru               *pst_wdev = OAL_PTR_NULL;
    oal_cfg80211_registered_device_stru *pst_rdev = OAL_PTR_NULL;
    const oal_uint8                     *action_data;

    pst_wdev = pst_dev->ieee80211_ptr;
    if(OAL_PTR_NULL == pst_wdev)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_rdev = oal_wiphy_to_dev(pst_wdev->wiphy);

    /* action data starts with category */
    action_data = puc_buf + OAL_IEEE80211_MIN_ACTION_SIZE - 1;

    return oal_nl80211_send_mgmt(pst_rdev, pst_dev, l_freq, puc_buf, ul_len, en_gfp);
#endif
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_rx_exception
 功能描述  : 收到异常后上报上层,私有命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_rx_exception(oal_net_device_stru *pst_netdev,
                                               oal_uint8           *puc_data,
                                               oal_uint32          ul_data_len)
{
 //   genl_msg_send_to_user(puc_data, ul_data_len);
    dev_netlink_send (puc_data, ul_data_len);
    OAL_IO_PRINT("DFR OAL send[%s] over\n", puc_data);
    return OAL_SUCC;
}

#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : oal_cfg80211_put_bss
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_put_bss(oal_cfg80211_bss_stru *pst_cfg80211_bss)
{

}

/*****************************************************************************
 函 数 名  : oal_cfg80211_inform_bss_frame
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_cfg80211_bss_stru *oal_cfg80211_inform_bss_frame(
                                oal_wiphy_stru              *pst_wiphy,
                                oal_ieee80211_channel_stru  *pst_ieee80211_channel,
                                oal_ieee80211_mgmt_stru     *pst_mgmt,
                                oal_uint32                   ul_len,
                                oal_int32                    l_signal,
                                oal_gfp_enum_uint8           en_ftp)
{
    oal_cfg80211_bss_stru  *pst_cfg80211_bss;

    pst_cfg80211_bss = OAL_PTR_NULL;

    return pst_cfg80211_bss;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_scan_done
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_scan_done(oal_cfg80211_scan_request_stru *pst_cfg80211_scan_req, oal_int8 c_aborted)
{

}

/*****************************************************************************
 函 数 名  : oal_cfg80211_sched_scan_result
 功能描述  : 上报调度扫描结果
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_sched_scan_result(oal_wiphy_stru *pst_wiphy)
{
    return;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_connect_result
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_connect_result(
                        oal_net_device_stru         *pst_net_device,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                              oal_uint16             us_status,
                              oal_gfp_enum_uint8     en_gfp)
{
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : oal_cfg80211_roamed
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_roamed(
                        oal_net_device_stru         *pst_net_device,
                        struct ieee80211_channel    *pst_channel,
                        const oal_uint8             *puc_bssid,
                        const oal_uint8             *puc_req_ie,
                              oal_uint32             ul_req_ie_len,
                        const oal_uint8             *puc_resp_ie,
                              oal_uint32             ul_resp_ie_len,
                        oal_gfp_enum_uint8           en_gfp)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_ft_event
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_ft_event(oal_net_device_stru *pst_net_device, oal_cfg80211_ft_event_stru  *pst_ft_event)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_disconnected
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_disconnected(
                    oal_net_device_stru        *pst_net_device,
                    oal_uint16                  us_reason,
                    oal_uint8                   *puc_ie,
                    oal_uint32                  ul_ie_len,
                    oal_gfp_enum                en_gfp)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_new_sta
 功能描述  : AP 上报关联了某个sta的情况
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_new_sta(
                       oal_net_device_stru     *pst_net_device,
                       const oal_uint8         *puc_mac_addr,
                       oal_station_info_stru   *pst_station_info,
                       oal_gfp_enum_uint8      en_gfp)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_mic_failure
 功能描述  : 上报mic攻击
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_cfg80211_mic_failure(
                        oal_net_device_stru     *pst_net_device,
                        const oal_uint8         *puc_mac_addr,
                        enum nl80211_key_type    key_type,
                        oal_int32                key_id,
                        const oal_uint8         *tsc,
                        oal_gfp_enum_uint8       en_gfp)
{
    /* do nothing */
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_del_sta
 功能描述  : AP 上报去关联了某个sta的情况
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_del_sta(oal_net_device_stru *pst_net_device,
                                   const oal_uint8      *puc_mac_addr,
                                   oal_gfp_enum_uint8    en_gfp)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_rx_mgmt
 功能描述  : 上报接收到的管理帧
 输入参数  : oal_net_device_stru    *pst_dev,
             oal_int32               l_freq,
             const oal_uint8        *puc_buf,
             oal_uint32              ul_len,
             gfp_t                   gfp
 输出参数  : OAL_SUCC 上报成功，其它错误码 上报失败
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oal_cfg80211_rx_mgmt(oal_net_device_stru   *pst_dev,
                                oal_int32              l_freq,
                                const oal_uint8       *puc_buf,
                                oal_uint32             ul_len,
                                oal_gfp_enum_uint8     en_gfp)
{
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_cfg80211_rx_exception
 功能描述  : 收到异常后上报上层,私有命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_cfg80211_rx_exception(oal_net_device_stru *pst_netdev,
                                               oal_uint8          *puc_data,
                                               oal_uint32          ul_data_len)

{
    OAL_IO_PRINT("DFR report excp to APP!!");
    return OAL_SUCC;

}

#endif

/*lint -e578*//*lint -e19*/
oal_module_symbol(oal_cfg80211_put_bss);
oal_module_symbol(oal_cfg80211_inform_bss_frame);
oal_module_symbol(oal_cfg80211_scan_done);
oal_module_symbol(oal_cfg80211_sched_scan_result);
oal_module_symbol(oal_cfg80211_connect_result);
oal_module_symbol(oal_cfg80211_roamed);
oal_module_symbol(oal_cfg80211_ft_event);
oal_module_symbol(oal_cfg80211_disconnected);
oal_module_symbol(oal_cfg80211_new_sta);
oal_module_symbol(oal_cfg80211_mic_failure);
oal_module_symbol(oal_cfg80211_del_sta);
oal_module_symbol(oal_cfg80211_rx_mgmt);
oal_module_symbol(oal_cfg80211_mgmt_tx_status);
oal_module_symbol(oal_cfg80211_ready_on_channel);
oal_module_symbol(oal_cfg80211_remain_on_channel_expired);
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
oal_module_symbol(oal_kobject_uevent_env_sta_join);
oal_module_symbol(oal_kobject_uevent_env_sta_leave);
#endif
#endif

oal_module_symbol(oal_cfg80211_rx_exception);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

