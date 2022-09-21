/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_ioctl.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月16日
  最近修改   :
  功能描述   : hwal ioctl文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月16日
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
#include "hwal_wpa_ioctl.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HWAL_IOCTL_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OAL_CONST hwal_ioctl_handler g_ast_hwal_ioctl_handlers[] =
{
    (hwal_ioctl_handler) hwal_ioctl_set_ap,             /* HISI_IOCTL_SET_AP     */
    (hwal_ioctl_handler) hwal_ioctl_new_key,            /* HISI_IOCTL_NEW_KEY    */
    (hwal_ioctl_handler) hwal_ioctl_del_key,            /* HISI_IOCTL_DEL_KEY    */
    (hwal_ioctl_handler) hwal_ioctl_set_key,            /* HISI_IOCTL_SET_KEY    */
    (hwal_ioctl_handler) hwal_ioctl_send_mlme,          /* HISI_IOCTL_SEND_MLME  */
    (hwal_ioctl_handler) hwal_ioctl_send_eapol,         /* HISI_IOCTL_SEND_EAPOL */
    (hwal_ioctl_handler) hwal_ioctl_receive_eapol,      /* HISI_IOCTL_RECEIVE_EAPOL */
    (hwal_ioctl_handler) hwal_ioctl_enable_eapol,       /* HISI_IOCTL_ENALBE_EAPOL */
    (hwal_ioctl_handler) hwal_ioctl_disable_eapol,      /* HISI_IOCTL_DISABLE_EAPOL */
    (hwal_ioctl_handler) hwal_ioctl_get_addr,           /* HIIS_IOCTL_GET_ADDR */
    (hwal_ioctl_handler) hwal_ioctl_set_power,          /* HISI_IOCTL_SET_POWER */
    (hwal_ioctl_handler) hwal_ioctl_set_mode,           /* HISI_IOCTL_SET_MODE */
    (hwal_ioctl_handler) hwal_ioctl_get_hw_feature,     /* HIIS_IOCTL_GET_HW_FEATURE */
    (hwal_ioctl_handler) hwal_ioctl_stop_ap,            /* HIIS_IOCTL_STOP_AP */
    (hwal_ioctl_handler) hwal_ioctl_del_virtual_intf,   /* HISI_IOCTL_DEL_VIRTUAL_INTF */
    (hwal_ioctl_handler) hwal_ioctl_scan,               /* HISI_IOCTL_SCAN */
    (hwal_ioctl_handler) hwal_ioctl_disconnect,         /* HISI_IOCTL_DISCONNET */
    (hwal_ioctl_handler) hwal_ioctl_assoc,              /* HISI_IOCTL_ASSOC */
    (hwal_ioctl_handler) hwal_ioctl_set_netdev,         /* HISI_IOCTL_SET_NETDEV */
    (hwal_ioctl_handler) hwal_ioctl_set_ap_wps_p2p_ie,  /* HISI_IOCTL_SET_AP_WPS_P2P_IE */
    (hwal_ioctl_handler) hwal_ioctl_change_beacon,      /* HISI_IOCTL_CHANGE_BEACON */
    (hwal_ioctl_handler) hwal_ioctl_dhcp_start,         /* HISI_IOCTL_DHCP_START */
    (hwal_ioctl_handler) hwal_ioctl_dhcp_stop,          /* HISI_IOCTL_DHCP_STOP */
    (hwal_ioctl_handler) hwal_ioctl_dhcp_succ_check     /* HISI_IOCTL_DHCP_SUCC_CHECK */
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
    ,
    (hwal_ioctl_handler) hwal_ioctl_set_rekey_info      /* HISI_IOCTL_SET_REKEY_INFO */
#endif
};
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_key
 功能描述  : set key数据传递至WAL层
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_key(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_unicast;
    oal_bool_enum_uint8      en_multicast;
    oal_uint8               *puc_mac_addr;
    hisi_key_ext_stru       *pst_key_ext;
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_set_key parameter NULL.");
        return -OAL_EFAIL;
    }

    en_unicast   = OAL_TRUE;
    en_multicast = OAL_FALSE;
    pst_netdev   = oal_dev_get_by_name(puc_ifname);
    pst_wiphy    = oal_wiphy_get();

    pst_key_ext      = (hisi_key_ext_stru *)p_buf;
    uc_key_index     = pst_key_ext->ul_key_idx;
    puc_mac_addr     = pst_key_ext->puc_addr;

    if (HISI_TRUE == pst_key_ext->en_def)
    {
        en_unicast = OAL_TRUE;
        en_multicast = OAL_TRUE;
    }

    if (HISI_TRUE == pst_key_ext->en_defmgmt)
    {
        en_multicast = OAL_TRUE;
    }

    if (HISI_KEY_DEFAULT_TYPE_UNICAST == pst_key_ext->en_default_types)
    {
        en_unicast = OAL_TRUE;
    }
    else if (HISI_KEY_DEFAULT_TYPE_MULTICAST == pst_key_ext->en_default_types)
    {
        en_multicast = OAL_TRUE;
    }

    return wal_cfg80211_set_default_key(pst_wiphy, pst_netdev, uc_key_index, en_unicast,en_multicast);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_new_key
 功能描述  : set key数据传递至WAL层
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_new_key(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;
    hisi_key_ext_stru       *pst_key_ext;
    oal_uint8               *puc_mac_addr;
    oal_key_params_stru      st_params;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_new_key parameter NULL.");
        return -OAL_EFAIL;
    }

    oal_memset(&st_params, 0, OAL_SIZEOF(oal_key_params_stru));

    pst_netdev = oal_dev_get_by_name(puc_ifname);
    pst_wiphy  = oal_wiphy_get();

    pst_key_ext  = (hisi_key_ext_stru *)p_buf;
    uc_key_index = pst_key_ext->ul_key_idx;
    en_pairwise  = (HISI_KEYTYPE_PAIRWISE == pst_key_ext->l_type);
    puc_mac_addr = pst_key_ext->puc_addr;

    st_params.key       = (oal_uint8 *)(pst_key_ext->puc_key);
    st_params.key_len   = pst_key_ext->ul_key_len;
    st_params.seq_len   = pst_key_ext->ul_seq_len;
    st_params.seq       = pst_key_ext->puc_seq;
    st_params.cipher    = pst_key_ext->ul_cipher;

    return wal_cfg80211_add_key(pst_wiphy, pst_netdev, uc_key_index, en_pairwise, puc_mac_addr, &st_params);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_del_key
 功能描述  : del key数据传递至WAL层
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_del_key(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;
    hisi_key_ext_stru       *pst_key_ext;
    oal_uint8               *puc_mac_addr;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_del_key parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_netdev   = oal_dev_get_by_name(puc_ifname);
    pst_wiphy    = oal_wiphy_get();

    pst_key_ext  = (hisi_key_ext_stru *)p_buf;
    en_pairwise  = (HISI_KEYTYPE_PAIRWISE == pst_key_ext->l_type);
    puc_mac_addr = pst_key_ext->puc_addr;
    uc_key_index = pst_key_ext->ul_key_idx;

    return wal_cfg80211_remove_key(pst_wiphy, pst_netdev, uc_key_index, en_pairwise, puc_mac_addr);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_setap
 功能描述  : set ap数据传递至WAL层
 输入参数  : struct wt_param *iwtp
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_ap(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;
    hisi_ap_settings_stru   *pst_apsettings;
    oal_ap_settings_stru     st_oal_apsettings;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_set_ap parameter NULL.");
        return -OAL_EFAIL;
    }

    oal_memset(&st_oal_apsettings, 0, OAL_SIZEOF(oal_ap_settings_stru));

    pst_netdev = oal_dev_get_by_name(puc_ifname);
    pst_wiphy  = oal_wiphy_get();

    pst_apsettings = (hisi_ap_settings_stru *)p_buf;

    st_oal_apsettings.ssid_len        = pst_apsettings->ul_ssid_len;
    st_oal_apsettings.beacon_interval = pst_apsettings->l_beacon_interval;
    st_oal_apsettings.dtim_period     = pst_apsettings->l_dtim_period;
    st_oal_apsettings.hidden_ssid     = pst_apsettings->en_hidden_ssid;
    st_oal_apsettings.beacon.head_len = pst_apsettings->st_beacon_data.ul_head_len;
    st_oal_apsettings.beacon.tail_len = pst_apsettings->st_beacon_data.ul_tail_len;

    st_oal_apsettings.ssid          = pst_apsettings->puc_ssid;
    st_oal_apsettings.beacon.head   = pst_apsettings->st_beacon_data.puc_head;
    st_oal_apsettings.beacon.tail   = pst_apsettings->st_beacon_data.puc_tail;
    st_oal_apsettings.auth_type     = pst_apsettings->en_auth_type;

    if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr)
    {
        pst_netdev->ieee80211_ptr = (oal_wireless_dev_stru*)oal_memalloc(OAL_SIZEOF(struct wireless_dev));
        if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr)
        {
            OAM_ERROR_LOG0(0, 0, "ieee80211_ptr parameter NULL.");
            return -OAL_EFAIL;
        }
        oal_memset(pst_netdev->ieee80211_ptr, 0, OAL_SIZEOF(struct wireless_dev));
    }

    if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr->preset_chandef.chan)
    {
        pst_netdev->ieee80211_ptr->preset_chandef.chan = (oal_ieee80211_channel*)oal_memalloc(OAL_SIZEOF(oal_ieee80211_channel));
        if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr->preset_chandef.chan)
        {
            oal_free(pst_netdev->ieee80211_ptr);
            pst_netdev->ieee80211_ptr = OAL_PTR_NULL;

            OAM_ERROR_LOG0(0, 0, "chan parameter NULL.");
            return -OAL_EFAIL;
        }
        oal_memset(pst_netdev->ieee80211_ptr->preset_chandef.chan, 0, OAL_SIZEOF(oal_ieee80211_channel));
    }

    pst_netdev->ieee80211_ptr->preset_chandef.width             = pst_apsettings->st_freq_params.l_bandwidth;
    pst_netdev->ieee80211_ptr->preset_chandef.center_freq1      = pst_apsettings->st_freq_params.l_center_freq1;
    pst_netdev->ieee80211_ptr->preset_chandef.chan->hw_value    = pst_apsettings->st_freq_params.l_channel;
    pst_netdev->ieee80211_ptr->preset_chandef.chan->band        = IEEE80211_BAND_2GHZ;

    return wal_cfg80211_start_ap(pst_wiphy, pst_netdev, &st_oal_apsettings);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_change_beacon
 功能描述  : 修改beacon帧参数
 输入参数  : oal_int8 *puc_ifname
             oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_change_beacon(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    oal_beacon_data_stru     st_beacon;
    oal_wiphy_stru          *pst_wiphy;
    hisi_ap_settings_stru   *pst_apsettings;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_change_beacon parameter NULL.");
        return -OAL_EFAIL;
    }

    oal_memset(&st_beacon, 0, OAL_SIZEOF(oal_beacon_data_stru));

    pst_netdev           = oal_dev_get_by_name(puc_ifname);
    pst_wiphy            = oal_wiphy_get();
    pst_apsettings       = (hisi_ap_settings_stru *)p_buf;

    /* 获取修改beacon帧参数的结构体 */
    st_beacon.head       = pst_apsettings->st_beacon_data.puc_head;
    st_beacon.tail       = pst_apsettings->st_beacon_data.puc_tail;
    st_beacon.head_len   = pst_apsettings->st_beacon_data.ul_head_len;
    st_beacon.tail_len   = pst_apsettings->st_beacon_data.ul_tail_len;

    return wal_cfg80211_change_beacon(pst_wiphy, pst_netdev, &st_beacon);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_set_ap_wps_p2p_ie
 功能描述  : 设置app ie 到wifi驱动
 输入参数  : oal_int8 *puc_ifname
             oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_ap_wps_p2p_ie(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    hisi_app_ie_stru        *pst_app_ie;
    oal_app_ie_stru          st_wps_p2p_ie;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_set_ap_wps_p2p_ie parameter NULL.");
        return -OAL_EFAIL;
    }

    oal_memset(&st_wps_p2p_ie, 0, OAL_SIZEOF(oal_app_ie_stru));

    pst_netdev               = oal_dev_get_by_name(puc_ifname);
    pst_app_ie               = (oal_app_ie_stru *)p_buf;

    st_wps_p2p_ie.ul_ie_len      = pst_app_ie->ul_ie_len;
    st_wps_p2p_ie.en_app_ie_type = pst_app_ie->uc_app_ie_type;

    if (st_wps_p2p_ie.ul_ie_len > WLAN_WPS_IE_MAX_SIZE)
    {
        OAM_ERROR_LOG0(0, 0, "app ie length is too large!");
        return -OAL_EFAIL;
    }

    oal_memcopy(st_wps_p2p_ie.auc_ie, pst_app_ie->puc_ie, pst_app_ie->ul_ie_len);

    return wal_ioctl_set_wps_p2p_ie(pst_netdev, st_wps_p2p_ie.auc_ie, st_wps_p2p_ie.ul_ie_len, st_wps_p2p_ie.en_app_ie_type);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_sendmlme
 功能描述  : send mlme数据传递至WAL层
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_send_mlme(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru         *pst_netdev;
    oal_wiphy_stru              *pst_wiphy;
    hisi_mlme_data_stru         *pst_mlme_data;
    oal_ieee80211_channel        st_chan;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_send_mlme parameter NULL.");
        return -OAL_EFAIL;
    }

    oal_memset(&st_chan, 0, OAL_SIZEOF(oal_ieee80211_channel));

    pst_netdev = oal_dev_get_by_name(puc_ifname);
    pst_wiphy = oal_wiphy_get();

    pst_mlme_data = (hisi_mlme_data_stru *)p_buf;

    st_chan.center_freq = pst_mlme_data->ul_freq;

    return wal_cfg80211_mgmt_tx(pst_wiphy, pst_netdev->ieee80211_ptr, &st_chan, 0, 0,pst_mlme_data->puc_data, pst_mlme_data->ul_data_len, 0, pst_mlme_data->l_noack, pst_mlme_data->pull_send_action_cookie);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_send_eapol
 功能描述  : 发送EAPOL报文
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_send_eapol(oal_int8 *puc_ifname, oal_void *p_buf)
{
    hisi_tx_eapol_stru     *pst_tx_eapol;
    oal_net_device_stru    *pst_netdev;
    oal_ether_header_stru  *pst_ether_hdr;
    oal_netbuf_stru        *pst_netbuf;
    oal_int32               l_ret;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_send_eapol parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_netdev      = oal_dev_get_by_name(puc_ifname);
    pst_tx_eapol    = (hisi_tx_eapol_stru *)p_buf;

    /* 申请SKB内存内存发送 */
    pst_netbuf      = hwal_lwip_skb_alloc(pst_netdev, pst_tx_eapol->ul_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_send_eapol skb_alloc NULL.");
        return -OAL_EFAIL;
    }

    oal_netbuf_put(pst_netbuf, pst_tx_eapol->ul_len);
    oal_memcopy(OAL_NETBUF_DATA(pst_netbuf), pst_tx_eapol->puc_buf, pst_tx_eapol->ul_len);

    if ((OAL_PTR_NULL == pst_netdev->netdev_ops) || (OAL_PTR_NULL == pst_netdev->netdev_ops->ndo_start_xmit))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_send_eapol netdev_ops NULL.");
        oal_netbuf_free(pst_netbuf);
        return -OAL_EFAIL;
    }

    return pst_netdev->netdev_ops->ndo_start_xmit(pst_netbuf, pst_netdev);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_receive_eapol
 功能描述  : 处理接收EAPOL报文
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_receive_eapol(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru    *pst_netdev;
    oal_netbuf_stru        *pst_skb_buf;
    hisi_rx_eapol_stru     *pst_rx_eapol;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_receive_eapol parameter NULL.\r\n");
        return -OAL_EFAIL;
    }

    pst_rx_eapol    = (hisi_rx_eapol_stru *)p_buf;
    pst_netdev      = oal_dev_get_by_name(puc_ifname);

    if (OAL_TRUE == oal_netbuf_list_empty(&pst_netdev->st_hisi_eapol.st_eapol_skb_head))
    {
        /* 此处hostapd在取链表数据时，会一直取到链表为空，所以每次都会打印，此时为正常打印 */
        /* 所以设置为info */
        OAM_INFO_LOG0(0, 0, "hwal_ioctl_receive_eapol eapol pkt Q empty.\r\n");
        return -OAL_EINVAL;
    }

    pst_skb_buf     = oal_netbuf_delist(&pst_netdev->st_hisi_eapol.st_eapol_skb_head);
    if (pst_skb_buf->len > pst_rx_eapol->ul_len)
    {
        /* 如果收到EAPOL报文大小超过接收报文内存，返回失败 */
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_receive_eapol eapol pkt len(%d) > buf size(%d).\r\n", pst_skb_buf->len, pst_rx_eapol->ul_len);
        oal_netbuf_free(pst_skb_buf);
        return -OAL_EFAIL;
    }

    oal_memcopy(pst_rx_eapol->puc_buf, pst_skb_buf->data, pst_skb_buf->len);
    pst_rx_eapol->ul_len = pst_skb_buf->len;

    oal_netbuf_free(pst_skb_buf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_enable_eapol
 功能描述  : 向驱动注册处理接收EAPOL报文回调
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_enable_eapol(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru    *pst_netdev;
    hisi_enable_eapol_stru *pst_enable_param;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_enable_eapol parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_enable_param    = (hisi_enable_eapol_stru *)p_buf;
    pst_netdev          = oal_dev_get_by_name(puc_ifname);

    pst_netdev->st_hisi_eapol.en_register       = OAL_TRUE;
    pst_netdev->st_hisi_eapol.notify_callback   = pst_enable_param->pfn_callback;
    pst_netdev->st_hisi_eapol.context           = pst_enable_param->p_contex;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_disable_eapol
 功能描述  : 向驱动解注册处理EAPOL报文回调
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_disable_eapol(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru    *pst_netdev;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_disable_eapol parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_netdev          = oal_dev_get_by_name(puc_ifname);

    pst_netdev->st_hisi_eapol.en_register       = OAL_FALSE;
    pst_netdev->st_hisi_eapol.notify_callback   = OAL_PTR_NULL;
    pst_netdev->st_hisi_eapol.context           = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_get_addr
 功能描述  : 从驱动获取MAC地址
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_get_addr(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru    *pst_netdev;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_enable_eapol parameter NULL.");
        return -OAL_EFAIL;
    }

    /* 调用获取MAC地址操作 */
    pst_netdev  = oal_dev_get_by_name(puc_ifname);
    oal_memcopy(p_buf, pst_netdev->dev_addr, ETH_ADDR_LEN);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_get_hw_feature
 功能描述  : 从驱动获取HW feature
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_get_hw_feature(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru            *pst_netdev;
    oal_wiphy_stru                 *pst_wiphy;
    oal_ieee80211_supported_band   *pst_band;
    hisi_hw_feature_data_stru      *pst_hw_feature_data;
    oal_wireless_dev_stru          *pst_iee80211;
    oal_uint32                      ul_loop;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_get_hw_feature parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_hw_feature_data = (hisi_hw_feature_data_stru *)p_buf;

    /* 调用获取HW feature */
    pst_netdev  = oal_dev_get_by_name(puc_ifname);
    pst_iee80211 = pst_netdev->ieee80211_ptr;
    if (OAL_PTR_NULL == pst_iee80211)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_get_hw_feature ieee80211_ptr NULL.");
        return -OAL_EFAIL;
    }

    pst_wiphy   = oal_wiphy_get();
    if (OAL_PTR_NULL == pst_wiphy)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_get_hw_feature pst_wiphy NULL.");
        return -OAL_EFAIL;
    }

    pst_band    = pst_wiphy->bands[IEEE80211_BAND_2GHZ];
    if (OAL_PTR_NULL == pst_band)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_get_hw_feature pst_band NULL.");
        return -OAL_EFAIL;
    }

    pst_hw_feature_data->l_channel_num = pst_band->n_channels;
    pst_hw_feature_data->us_ht_capab   = pst_band->ht_cap.cap;

    /* 数组越界判断 */
    if (pst_band->n_channels > 14)
    {
        OAM_ERROR_LOG1(0, 0, "error: n_channels = %d > 14.", pst_band->n_channels);
        return -OAL_EFAIL;
    }
    for (ul_loop = 0; ul_loop < pst_band->n_channels; ++ul_loop)
    {
        pst_hw_feature_data->ast_iee80211_channel[ul_loop].ul_flags      = pst_band->channels[ul_loop].flags;
        pst_hw_feature_data->ast_iee80211_channel[ul_loop].ul_freq       = pst_band->channels[ul_loop].center_freq;
        pst_hw_feature_data->ast_iee80211_channel[ul_loop].us_channel    = pst_band->channels[ul_loop].hw_value;
    }

    /* 数组越界判断 */
    if (pst_band->n_bitrates > 12)
    {
        OAM_ERROR_LOG1(0, 0, "error: n_bitrates = %d > 12.", pst_band->n_bitrates);
        return -OAL_EFAIL;
    }
    for (ul_loop = 0; ul_loop < pst_band->n_bitrates; ++ul_loop)
    {
        pst_hw_feature_data->aus_bitrate[ul_loop] = pst_band->bitrates[ul_loop].bitrate;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_power
 功能描述  : wifi上电
 输入参数  : (oal_int8 *puc_ifname, oal_void *p_buf)
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_power(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_int32               l_ret;
    oal_net_device_stru    *pst_net_dev;
    oal_bool_enum_uint8     en_power;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_set_power parameter NULL.%x,%x\r\n", puc_ifname, p_buf);
        return -OAL_EFAIL;
    }

    en_power    = *(oal_bool_enum_uint8 *)p_buf;
    pst_net_dev = oal_dev_get_by_name(puc_ifname);


    //ap上下电，配置VAP
    if (0 == en_power)//下电
    {
        /* 下电host device_stru去初始化*/
        wal_host_dev_exit(pst_net_dev);

        wal_wake_lock();
        wlan_pm_close();
        wal_wake_unlock();
        l_ret = OAL_SUCC;
    }
    else if (1 == en_power) //上电
    {
        en_power = 0;

        wal_wake_lock();
        l_ret = wlan_pm_open();
        wal_wake_unlock();
        if (OAL_FAIL == l_ret)
        {
             return -OAL_EFAIL;
        }
        else if (OAL_ERR_CODE_ALREADY_OPEN != l_ret)
        {
#ifdef _PRE_WLAN_FEATURE_DFR
            wal_dfr_init_param();
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
            /* 重新上电时调用定制化接口 */
            hwifi_config_init_force();
#endif

            // 重新上电场景，下发配置VAP
            l_ret = wal_cfg_vap_h2d_event(pst_net_dev);
            if (OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG1(0, 0, "wal_cfg_vap_h2d_event FAIL %d \r\n",l_ret);
                return -OAL_EFAIL;
            }
        }
        /* 上电host device_stru初始化*/
        l_ret = wal_host_dev_init(pst_net_dev);
        if (OAL_SUCC != l_ret)
        {
            OAM_ERROR_LOG1(0, 0, "wal_host_dev_init FAIL %d \r\n",l_ret);
            return -OAL_EFAIL;
        }

    #ifdef _PRE_WLAN_FEATURE_WOW
        hmac_wow_set_dmac_cfg();
    #endif

    }
    else
    {
        return -OAL_EFAIL;
    }
    return l_ret;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_set_mode
 功能描述  : AP STA p2p模式切换
 输入参数  : (oal_int8 *puc_ifname, oal_void *p_buf)
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_mode(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_uint32               ul_flags;
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;
    oal_vif_params_stru      st_params;
    hisi_set_mode_stru      *pst_set_mode;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_hapdinit parameter NULL.%x,%x\r\n", puc_ifname, p_buf);
        return -OAL_EFAIL;
    }

    oal_memset(&st_params, 0, OAL_SIZEOF(oal_vif_params_stru));

    ul_flags        = 0;
    pst_set_mode    = (hisi_set_mode_stru *)p_buf;
    pst_netdev      = oal_dev_get_by_name(puc_ifname);
    pst_wiphy       = oal_wiphy_get();

    if ((OAL_PTR_NULL == pst_netdev) || (OAL_PTR_NULL == pst_wiphy))
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_hapdinit pst_netdev or pst_wiphy NULL.%x,%x\r\n", pst_netdev, pst_wiphy);
        return -OAL_EFAIL;
    }

    st_params.use_4addr = 0;
    st_params.macaddr   = pst_set_mode->auc_bssid;

    return wal_cfg80211_change_virtual_intf(pst_wiphy, pst_netdev, pst_set_mode->en_iftype, &ul_flags, &st_params);
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_stop_ap
 功能描述  : AP下电
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_stop_ap(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;

    /* 上层p_buf入参为NULL，且未被使用, 此处不需做判空处理 */
    if (OAL_PTR_NULL == puc_ifname)
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_hapdinit parameter NULL.%x,%x\r\n", puc_ifname, p_buf);
        return -OAL_EFAIL;
    }

    pst_netdev = oal_dev_get_by_name(puc_ifname);
    pst_wiphy  = oal_wiphy_get();

    if (OAL_SUCC != wal_cfg80211_stop_ap(pst_wiphy, pst_netdev))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_stop_ap::wal_cfg80211_stop_ap failed.\r\n");
        return -OAL_EFAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_del_virtual_intf
 功能描述  : 删除对应VAP
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_del_virtual_intf(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    oal_wiphy_stru          *pst_wiphy;
    oal_wireless_dev_stru   *pst_wdev;

    /* 上层p_buf入参为NULL，且未被使用, 此处不需做判空处理 */
    if (OAL_PTR_NULL == puc_ifname)
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_hapdinit parameter NULL.%x,%x\r\n", puc_ifname, p_buf);
        return -OAL_EFAIL;
    }

    pst_netdev          = oal_dev_get_by_name(puc_ifname);
    pst_wiphy           = oal_wiphy_get();

    pst_wdev            = oal_memalloc(OAL_SIZEOF(oal_wireless_dev_stru));
    if (OAL_PTR_NULL == pst_wdev)
    {
        OAM_ERROR_LOG0(0, 0, "pst_wdev is NULL\r\n");
        return -OAL_EFAIL;
    }

    oal_memset(pst_wdev, 0, OAL_SIZEOF(oal_wireless_dev_stru));

    pst_wdev->netdev    = pst_netdev;

    if (OAL_SUCC != wal_cfg80211_del_virtual_intf(pst_wiphy, pst_wdev))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_del_virtual_intf::wal_cfg80211_del_virtual_intf failed.\r\n");
        oal_free(pst_wdev);
        return -OAL_EFAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_set_netdev
 功能描述  : set_netdev
 输入参数  : (oal_int8 *puc_ifname, oal_void *p_buf)
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_netdev(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_int32               l_ret;
    oal_net_device_stru    *pst_net_dev;
    oal_bool_enum_uint8     en_netdev;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG2(0, 0, "hwal_ioctl_set_netdev parameter NULL.%x,%x\r\n", puc_ifname, p_buf);
        return -OAL_EFAIL;
    }

    en_netdev       = *(oal_bool_enum_uint8 *)p_buf;
    pst_net_dev     = oal_dev_get_by_name(puc_ifname);

    if (HISI_FALSE == en_netdev)
    {
        l_ret = wal_netdev_stop(pst_net_dev);
    }
    else if (HISI_TRUE == en_netdev)
    {
        l_ret = wal_netdev_open(pst_net_dev);
    }
    else
    {
        OAM_ERROR_LOG1(0, 0, "hwal_ioctl_set_netdev en_netdev ERROR: %d\r\n", en_netdev);
        l_ret = -OAL_EFAIL;
    }

    return l_ret;
}

/*****************************************************************************
 函 数 名  : hwal_get_channel
 功能描述  : 获取信道
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_ieee80211_channel *hwal_get_channel(oal_wiphy_stru *pst_wiphy, oal_int32 l_freq)
{
    enum ieee80211_band             en_band;
    oal_ieee80211_supported_band   *pst_sband;
    oal_int32                       l_loop;

    for (en_band = 0; en_band < IEEE80211_NUM_BANDS; en_band++)
    {
        pst_sband = pst_wiphy->bands[en_band];

        if (OAL_PTR_NULL == pst_sband)
        {
            continue;
        }

        for (l_loop = 0; l_loop < pst_sband->n_channels; l_loop++)
        {
            if (pst_sband->channels[l_loop].center_freq == l_freq)
            {
                return &pst_sband->channels[l_loop];
            }
        }
    }

    return OAL_PTR_NULL;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_scan
 功能描述  : 发送扫描至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_scan(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_wiphy_stru                     *pst_wiphy;
    hisi_scan_stru                     *pst_scan_params;
    oal_net_device_stru                *pst_netdev;
    oal_cfg80211_scan_request_stru      st_request;
    oal_wireless_dev_stru               st_wdev;
    oal_ieee80211_channel_stru         *pst_chan;
    oal_uint32                          ul_count = 0;
    oal_int32                           l_loop;
    enum ieee80211_band                 en_band;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan parameter NULL.");
        return -HISI_EFAIL;
    }

    oal_memset(&st_request, 0, OAL_SIZEOF(oal_cfg80211_scan_request_stru));
    oal_memset(&st_wdev, 0, OAL_SIZEOF(oal_wireless_dev_stru));

    pst_scan_params = (hisi_scan_stru *)p_buf;
    pst_netdev      = oal_dev_get_by_name(puc_ifname);
    pst_wiphy       = oal_wiphy_get();

    st_request.wiphy    = pst_wiphy;
    st_request.dev      = pst_netdev;
    st_request.wdev     = pst_netdev->ieee80211_ptr;
    st_request.n_ssids  = pst_scan_params->ul_num_ssids;

    if (OAL_PTR_NULL != pst_scan_params->pl_freqs)
    {
        for (l_loop = 0; l_loop < pst_scan_params->ul_num_freqs; l_loop++)
        {
            pst_chan = hwal_get_channel(pst_wiphy, pst_scan_params->pl_freqs[l_loop]);
            if (OAL_PTR_NULL == pst_chan)
            {
                OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan: pst_chan parameter NULL.");
                return -HISI_EFAIL;
            }

            st_request.channels[ul_count] = pst_chan;
            ul_count++;
        }
    }
    else
    {
        for (en_band = 0; en_band < IEEE80211_BAND_5GHZ; en_band++)
        {
            if (OAL_PTR_NULL == pst_wiphy->bands[en_band])
            {
                continue;
            }

            for (l_loop = 0; l_loop < pst_wiphy->bands[en_band]->n_channels; l_loop++)
            {
                pst_chan = &pst_wiphy->bands[en_band]->channels[l_loop];
                if (OAL_PTR_NULL == pst_chan)
                {
                    OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan: pst_chan2 parameter NULL.");
                    return -HISI_EFAIL;
                }

                if (0 != (pst_chan->flags & HISI_CHAN_DISABLED))
                {
                    continue;
                }

                st_request.channels[ul_count] = pst_chan;
                ul_count++;
            }
        }
    }

    if (0 == ul_count)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan: ul_count = 0.");
        return -HISI_EFAIL;
    }
    st_request.n_channels = ul_count;

    if (0 != pst_scan_params->ul_num_ssids)
    {
        st_request.ssids = oal_memalloc(pst_scan_params->ul_num_ssids * sizeof(oal_cfg80211_ssid_stru));
        if (OAL_PTR_NULL == st_request.ssids)
        {
            OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan: st_request.ssids malloc failed.");
            return -HISI_EFAIL;
        }
        OAL_MEMZERO(st_request.ssids, pst_scan_params->ul_num_ssids * sizeof(oal_cfg80211_ssid_stru));
    }

    for (ul_count = 0; (ul_count < pst_scan_params->ul_num_ssids) && (ul_count < HISI_WPAS_MAX_SCAN_SSIDS); ul_count++ )
    {
        if (pst_scan_params->ast_ssids[ul_count].ul_ssid_len > IEEE80211_MAX_SSID_LEN)
        {
            OAM_ERROR_LOG2(0, 0, "hwal_ioctl_scan: ul_count = %d, len = %d.", ul_count, pst_scan_params->ast_ssids[ul_count].ul_ssid_len);
            oal_free(st_request.ssids);
            return -HISI_EFAIL;
        }

        st_request.ssids[ul_count].ssid_len = pst_scan_params->ast_ssids[ul_count].ul_ssid_len;
        oal_memcopy(st_request.ssids[ul_count].ssid, pst_scan_params->ast_ssids[ul_count].auc_ssid, pst_scan_params->ast_ssids[ul_count].ul_ssid_len);
    }

    if (OAL_PTR_NULL != pst_scan_params->puc_extra_ies)
    {
        st_request.ie_len   = pst_scan_params->ul_extra_ies_len;
        st_request.ie       = pst_scan_params->puc_extra_ies;
    }

    if (OAL_SUCC != wal_cfg80211_scan(pst_wiphy, &st_request))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan:wal_cfg80211_scan failed");
        if (OAL_PTR_NULL != st_request.ssids)
        {
            oal_free(st_request.ssids);
        }
        return -HISI_EFAIL;
    }

    if (OAL_PTR_NULL != st_request.ssids)
    {
        oal_free(st_request.ssids);
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_disconnect
 功能描述  : 发送去关联至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_disconnect(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_wiphy_stru                  *pst_wiphy;
    oal_net_device_stru             *pst_netdev;
    oal_uint16                       us_reason_code;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_disconnect parameter NULL.");
        return -HISI_EFAIL;
    }

    pst_netdev      = oal_dev_get_by_name(puc_ifname);
    pst_wiphy       = oal_wiphy_get();
    us_reason_code  = *(oal_uint16 *)p_buf;

    if ((OAL_PTR_NULL != pst_netdev)
     && (OAL_PTR_NULL != pst_netdev->pst_lwip_netif))
    {
        hwal_lwip_notify(pst_netdev->pst_lwip_netif, NETDEV_DOWN);
    }

    return wal_cfg80211_disconnect(pst_wiphy, pst_netdev, us_reason_code);
}
/*****************************************************************************
 函 数 名  : hwal_is_valid_ie_attr
 功能描述  : 判断是否为无效ie
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 hwal_is_valid_ie_attr(oal_uint8 *puc_ie, oal_uint32 ul_ie_len)
{
    oal_uint8 uc_elemlen;

    /* ie可以为空*/
    if (OAL_PTR_NULL == puc_ie)
    {
        return OAL_TRUE;
    }

    while (0 != ul_ie_len)
    {
        if (ul_ie_len < 2)
        {
            return OAL_FALSE;
        }
        ul_ie_len -= 2;

        uc_elemlen = puc_ie[1];
        if (uc_elemlen > ul_ie_len)
        {
            return OAL_FALSE;
        }
        ul_ie_len -= uc_elemlen;
        puc_ie += 2 + uc_elemlen;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_assoc
 功能描述  : 发送关联至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_assoc(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_wiphy_stru                       *pst_wiphy;
    oal_net_device_stru                  *pst_netdev;
    oal_cfg80211_connect_params_stru      st_sme;
    hisi_associate_params_stru           *pst_assoc_params;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_assoc parameter NULL.");
        goto error;
    }

    oal_memset(&st_sme, 0, OAL_SIZEOF(oal_cfg80211_connect_params_stru));

    pst_netdev          = oal_dev_get_by_name(puc_ifname);
    pst_wiphy           = oal_wiphy_get();
    pst_assoc_params    = (hisi_associate_params_stru *)p_buf;

    if ((OAL_PTR_NULL == pst_assoc_params->puc_ssid) || (0 == pst_assoc_params->ul_ssid_len))
    {
        OAM_ERROR_LOG0(0, 0, "pst_assoc_params parameter NULL.");
        goto error;
    }

    st_sme.ssid        = pst_assoc_params->puc_ssid;
    st_sme.ssid_len    = pst_assoc_params->ul_ssid_len;
    if (OAL_FALSE == hwal_is_valid_ie_attr(pst_assoc_params->puc_ie, pst_assoc_params->ul_ie_len))
    {
        OAM_ERROR_LOG0(0, 0, "pst_assoc_params->puc_ie parameter FALSE.");
        goto error;
    }
    st_sme.ie          = pst_assoc_params->puc_ie;
    st_sme.ie_len      = pst_assoc_params->ul_ie_len;

    if ((pst_assoc_params->uc_auth_type > NL80211_AUTHTYPE_AUTOMATIC) || (NL80211_AUTHTYPE_SAE == pst_assoc_params->uc_auth_type))
    {
        OAM_ERROR_LOG0(0, 0, "pst_assoc_params->uc_auth_type ERROR.");
        goto error;
    }
    else
    {
        st_sme.auth_type = pst_assoc_params->uc_auth_type;
    }

    st_sme.channel = hwal_get_channel(pst_wiphy, pst_assoc_params->ul_freq);
    if ((OAL_PTR_NULL == st_sme.channel) || (st_sme.channel->flags & HISI_CHAN_DISABLED))
    {
        OAM_ERROR_LOG0(0, 0, "st_sme.channel ERROR.");
        goto error;
    }

    if (OAL_PTR_NULL != pst_assoc_params->puc_bssid)
    {
        st_sme.bssid = pst_assoc_params->puc_bssid;
    }

    st_sme.privacy = pst_assoc_params->uc_privacy;

    if ((pst_assoc_params->uc_mfp != HISI_MFP_REQUIRED) &&
        (pst_assoc_params->uc_mfp != HISI_MFP_NO))
    {
        OAM_ERROR_LOG1(0, 0, "pst_assoc_params->uc_mfp ERROR. uc_mfp = %d", pst_assoc_params->uc_mfp);
        goto error;
    }

    st_sme.mfp = pst_assoc_params->uc_mfp;

    if (OAL_PTR_NULL != pst_assoc_params->puc_key)
    {
        st_sme.key     = pst_assoc_params->puc_key;
        st_sme.key_len = pst_assoc_params->uc_key_len;
        st_sme.key_idx = pst_assoc_params->uc_key_idx;
    }

    oal_memcopy(&st_sme.crypto, &pst_assoc_params->st_crypto, OAL_SIZEOF(hisi_crypto_settings_stru));

    return wal_cfg80211_connect(pst_wiphy, pst_netdev, &st_sme);

error:
     return -HISI_EFAIL;
}
/*****************************************************************************
 函 数 名  : hwal_ioctl_dhcp_start
 功能描述  : 发送DHCP启动命令至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_dhcp_start(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru                *pst_netdev;

    if (OAL_PTR_NULL == puc_ifname)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan parameter NULL.");
        return -HISI_EFAIL;
    }

    pst_netdev = oal_dev_get_by_name(puc_ifname);

    return hwal_dhcp_start(pst_netdev);

}
/*****************************************************************************
 函 数 名  : hwal_dhcp_stop
 功能描述  : 发送DHCP停止命令至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_dhcp_stop(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru                *pst_netdev;

    if (OAL_PTR_NULL == puc_ifname)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_scan parameter NULL.");
        return -HISI_EFAIL;
    }

    pst_netdev = oal_dev_get_by_name(puc_ifname);

    return hwal_dhcp_stop(pst_netdev);
}

/*****************************************************************************
 函 数 名  : hwal_ioctl_dhcp_succ_check
 功能描述  : 发送DHCP检查命令至WAL层
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年10月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_dhcp_succ_check(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru                *pst_netdev;

    if (OAL_PTR_NULL == puc_ifname)
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_dhcp_succ_check parameter NULL.");
        return -HISI_EFAIL;
    }

    pst_netdev = oal_dev_get_by_name(puc_ifname);

    return hwal_dhcp_succ_check(pst_netdev);
}

#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
/*****************************************************************************
 函 数 名  : hwal_ioctl_set_rekey_info
 功能描述  : set rekey info数据传递至WAL层
 输入参数  : oal_int8 *puc_ifname, oal_void *p_buf
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_ioctl_set_rekey_info(oal_int8 *puc_ifname, oal_void *p_buf)
{
    oal_net_device_stru     *pst_netdev;
    hisi_rekey_offload_stru *pst_rekey_offload;

    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == p_buf))
    {
        OAM_ERROR_LOG0(0, 0, "hwal_ioctl_set_ap parameter NULL.");
        return -OAL_EFAIL;
    }

    pst_netdev          = oal_dev_get_by_name(puc_ifname);
    pst_rekey_offload   = (mac_rekey_offload_stru *)p_buf;

    return wal_cfg80211_set_rekey_info(pst_netdev, pst_rekey_offload);
}
#endif

/*****************************************************************************
 函 数 名  : hwal_wpa_ioctl
 功能描述  : 驱动对外提供统一调用接口
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年6月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hwal_wpa_ioctl(oal_int8 *puc_ifname, hisi_ioctl_command_stru *pst_cmd)
{
    if ((OAL_PTR_NULL == puc_ifname) || (OAL_PTR_NULL == pst_cmd))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwal_wpa_ioctl::puc_ifname = %x,p_buf = %x",puc_ifname,pst_cmd);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((pst_cmd->ul_cmd < HWAL_EVENT_BUTT) && (OAL_PTR_NULL != g_ast_hwal_ioctl_handlers[pst_cmd->ul_cmd]))
    {
        return g_ast_hwal_ioctl_handlers[pst_cmd->ul_cmd](puc_ifname, pst_cmd->p_buf);
    }
    OAM_ERROR_LOG1(0, 0, "hwal_wpa_ioctl ::The CMD[%d] handlers is NULL.\r\n",pst_cmd->ul_cmd);

    return -OAL_EFAIL;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

