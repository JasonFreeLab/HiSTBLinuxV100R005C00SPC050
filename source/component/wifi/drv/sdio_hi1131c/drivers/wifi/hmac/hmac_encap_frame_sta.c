/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_encap_frame_sta.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月28日
  最近修改   :
  功能描述   : STA模式组帧，HMAC层 STA特有帧的组帧文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月28日
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
#include "wlan_spec.h"
#include "wlan_mib.h"
#include "mac_vap.h"
#include "mac_frame.h"
#include "hmac_encap_frame_sta.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_tx_data.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_mgmt_sta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ENCAP_FRAME_STA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : mac_set_supported_rates_ie
 功能描述  : 设置速率集
 输入参数  : pst_hmac_sta: 指向vap
             puc_buffer: 指向buffer
 输出参数  : puc_ie_len: element的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_set_supported_rates_ie_asoc_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{

    oal_uint8         uc_nrates;
    oal_uint8         uc_idx;

    /**************************************************************************
                        ---------------------------------------
                        |Element ID | Length | Supported Rates|
                        ---------------------------------------
             Octets:    |1          | 1      | 1~8            |
                        ---------------------------------------
    The Information field is encoded as 1 to 8 octets, where each octet describes a single Supported
    Rate or BSS membership selector.
    **************************************************************************/
    puc_buffer[0] = MAC_EID_RATES;

    uc_nrates = pst_hmac_sta->uc_rs_nrates;

    if (uc_nrates > MAC_MAX_SUPRATES)
    {
        uc_nrates = MAC_MAX_SUPRATES;
    }

    for (uc_idx = 0; uc_idx < uc_nrates; uc_idx++)
    {
        puc_buffer[MAC_IE_HDR_LEN + uc_idx] = pst_hmac_sta->auc_supp_rates[uc_idx];
    }

    puc_buffer[1] = uc_nrates;

    *puc_ie_len = MAC_IE_HDR_LEN + uc_nrates;
}
/*****************************************************************************
 函 数 名  : mac_set_exsup_rates_ie
 功能描述  : 填充extended supported rates信息
 输入参数  : pst_hmac_sta: 指向vap
             puc_buffer: 指向buffer
 输出参数  : puc_ie_len: element的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_set_exsup_rates_ie_asoc_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    oal_uint8         uc_nrates;
    oal_uint8         uc_idx;


    /***************************************************************************
                   -----------------------------------------------
                   |ElementID | Length | Extended Supported Rates|
                   -----------------------------------------------
       Octets:     |1         | 1      | 1-255                   |
                   -----------------------------------------------
    ***************************************************************************/
    if (pst_hmac_sta->uc_rs_nrates <= MAC_MAX_SUPRATES)
    {
        *puc_ie_len = 0;

        return;
    }

    puc_buffer[0] = MAC_EID_XRATES;
    uc_nrates     = pst_hmac_sta->uc_rs_nrates - MAC_MAX_SUPRATES;
    puc_buffer[1] = uc_nrates;

    for (uc_idx = 0; uc_idx < uc_nrates; uc_idx++)
    {
        puc_buffer[MAC_IE_HDR_LEN + uc_idx] = pst_hmac_sta->auc_supp_rates[uc_idx + MAC_MAX_SUPRATES];
    }

    *puc_ie_len = MAC_IE_HDR_LEN + uc_nrates;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_encap_asoc_req_sta
 功能描述  : 组帧(Re)assoc
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_mgmt_encap_asoc_req_sta(hmac_vap_stru *pst_hmac_sta,oal_uint8 *puc_req_frame)
{

    oal_uint8          uc_ie_len            = 0;
    oal_uint32         us_asoc_rsq_len      = 0;
    oal_uint8         *puc_req_frame_origin;
    mac_vap_stru      *pst_mac_vap;
    mac_device_stru   *pst_mac_device;
    oal_uint16         us_app_ie_len        = 0;

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_txbf_cap_stru *pst_txbf_cap;
#endif

    if ((OAL_PTR_NULL == pst_hmac_sta) || (OAL_PTR_NULL == puc_req_frame))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_req_sta::null param, pst_hmac_sta=%d puc_req_frame=%d.}",
                       pst_hmac_sta, puc_req_frame);
        return us_asoc_rsq_len;
    }

    /* 保存起始地址，方便计算长度*/
    puc_req_frame_origin = puc_req_frame;

    pst_mac_vap = &(pst_hmac_sta->st_vap_base_info);

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_req_sta::pst_mac_device null.}");
        return us_asoc_rsq_len;
    }

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* 设置 Frame Control field */
    /* 判断是否为reassoc操作 */
    if (pst_hmac_sta->bit_reassoc_flag)
    {
        mac_hdr_set_frame_control(puc_req_frame, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_REASSOC_REQ);

    }
    else
    {
        mac_hdr_set_frame_control(puc_req_frame, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ASSOC_REQ);
    }
    /* 设置 DA address1: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR1_OFFSET, pst_hmac_sta->st_vap_base_info.auc_bssid);

    /* 设置 SA address2: dot11MACAddress */
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR2_OFFSET, pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 设置 DA address3: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR3_OFFSET, pst_hmac_sta->st_vap_base_info.auc_bssid);

    puc_req_frame += MAC_80211_FRAME_LEN;

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Association Request Frame - Frame Body                   */
    /* --------------------------------------------------------------------- */
    /* | Capability Information | Listen Interval | SSID | Supported Rates | */
    /* --------------------------------------------------------------------- */
    /* |2                       |2                |2-34  |3-10             | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* |Externed Surpported rates| Power Capability | Supported Channels   | */
    /* --------------------------------------------------------------------- */
    /* |3-257                    |4                 |4-256                 | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | RSN   | QoS Capability | HT Capabilities | Extended Capabilities  | */
    /* --------------------------------------------------------------------- */
    /* |36-256 |3               |28               |3-8                     | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | WPS   | P2P |                                                       */
    /* --------------------------------------------------------------------- */
    /* |7-257  |X    |                                                       */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    mac_set_cap_info_sta((oal_void *)pst_mac_vap, puc_req_frame);
    puc_req_frame += MAC_CAP_INFO_LEN;

    /* 设置 Listen Interval IE */
    mac_set_listen_interval_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* Ressoc组帧设置Current AP address */
    if (pst_hmac_sta->bit_reassoc_flag)
    {
        oal_set_mac_addr(puc_req_frame, pst_mac_vap->auc_bssid);
        puc_req_frame += OAL_MAC_ADDR_LEN;
    }
    /* 设置 SSID IE */
    mac_set_ssid_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len, WLAN_FC0_SUBTYPE_ASSOC_REQ);
    puc_req_frame += uc_ie_len;
    /*:在关联请求时使用扫描时保存的速率集 --*/
#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    /* 设置 Supported Rates IE */
    mac_set_supported_rates_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* 设置 Extended Supported Rates IE */
    mac_set_exsup_rates_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

#else
    /* 设置 Supported Rates IE */
    hmac_set_supported_rates_ie_asoc_req(pst_hmac_sta, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* 设置 Extended Supported Rates IE */
    hmac_set_exsup_rates_ie_asoc_req(pst_hmac_sta, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif
    /* 设置 Power Capability IE */
    mac_set_power_cap_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* 设置 Supported channel IE */
    mac_set_supported_channel_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

/*  为增加兼容性，02不使用驱动组装的wpa/wpa2 ie，使用上层下发的 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    if (pst_hmac_sta->uc_80211i_mode == DMAC_RSNA_802_11I)
    {
        /* 设置 RSN Capability IE */
        mac_set_rsn_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
    else if (pst_hmac_sta->uc_80211i_mode == DMAC_WPA_802_11I)
    {
        /* 设置 WPA Capability IE */
        mac_set_wpa_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
#endif /* defined (_PRE_WLAN_FEATURE_WPA) || defiend (_PRE_WLAN_FEATURE_WPA) */
#endif

    /* 填充WMM element */
    if (OAL_TRUE == pst_hmac_sta->uc_wmm_cap)
    {
        mac_set_wmm_ie_sta((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }

    /* 设置 HT Capability IE  */
    mac_set_ht_capabilities_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
#ifdef _PRE_WLAN_FEATURE_TXBF
    if ((OAL_TRUE == pst_mac_vap->bit_ap_11ntxbf)
    && (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_11ntxbf)
    && (0 != uc_ie_len))
    {
        puc_req_frame += MAC_11N_TXBF_CAP_OFFSET;

        pst_txbf_cap  = (mac_txbf_cap_stru *)puc_req_frame;
        pst_txbf_cap->bit_rx_stagg_sounding             = OAL_TRUE;
        pst_txbf_cap->bit_explicit_compr_bf_fdbk        = 1;
        pst_txbf_cap->bit_compr_steering_num_bf_antssup = 1;
        puc_req_frame -= MAC_11N_TXBF_CAP_OFFSET;
    }
#endif
    puc_req_frame += uc_ie_len;

    /* 设置 Extended Capability IE */
    mac_set_ext_capabilities_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* 设置 VHT Capability IE */
    mac_set_vht_capabilities_ie((oal_void *) pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11AC2G
    mac_set_vendor_hisi_ie(pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie(pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_11R
    mac_set_md_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif //_PRE_WLAN_FEATURE_11R

    /* 填充P2P/WPS IE 信息 */
    mac_add_app_ie(pst_mac_vap, puc_req_frame, &us_app_ie_len, OAL_APP_ASSOC_REQ_IE);
    /*  P2P联调 解决发送的关联请求没有P2P WPS IE信息 */
    puc_req_frame += us_app_ie_len;

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    if (HISTREAM_SWITCH_ON == g_uc_histream_switch)
    {
        mac_set_histream_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
#endif //_PRE_WLAN_FEATURE_HISTREAM

    us_asoc_rsq_len = (oal_uint32)(puc_req_frame - puc_req_frame_origin);

    return us_asoc_rsq_len;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_prepare_auth_req
 功能描述  : 组seq = 1 的auth req帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_auth_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_mgmt_frame)
{
    oal_uint16      us_auth_req_len;
    hmac_user_stru *pst_user_ap;
    oal_uint16      us_auth_type;
    oal_uint32      ul_ret;
    oal_uint16      us_user_index;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    mac_hdr_set_frame_control(puc_mgmt_frame, WLAN_FC0_SUBTYPE_AUTH);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address1, pst_hmac_sta->st_vap_base_info.auc_bssid);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address2, pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address3, pst_hmac_sta->st_vap_base_info.auc_bssid);
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Authentication Frame (Sequence 1) - Frame Body           */
    /* --------------------------------------------------------------------  */
    /* |Auth Algorithm Number|Auth Transaction Sequence Number|Status Code|  */
    /* --------------------------------------------------------------------  */
    /* | 2                   |2                               |2          |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    if(OAL_FALSE == pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked)
    {
        /* Open System */
        puc_mgmt_frame[MAC_80211_FRAME_LEN]     = 0x00;
        puc_mgmt_frame[MAC_80211_FRAME_LEN + 1] = 0x00;
    }
    else
    {
        us_auth_type = (oal_uint16)pst_hmac_sta->en_auth_mode;

        if(WLAN_WITP_AUTH_SHARED_KEY == us_auth_type)
        {
            OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::WLAN_WITP_AUTH_SHARED_KEY.}");
            us_auth_type = WLAN_WITP_AUTH_SHARED_KEY;
        }
        else
        {
            OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::WLAN_WITP_AUTH_OPEN_SYSTEM.}");
            us_auth_type = WLAN_WITP_AUTH_OPEN_SYSTEM;
        }

        puc_mgmt_frame[MAC_80211_FRAME_LEN]     = (us_auth_type & 0xFF);
        puc_mgmt_frame[MAC_80211_FRAME_LEN + 1] = ((us_auth_type & 0xFF00) >> 8);
    }

    /* 设置 Authentication Transaction Sequence Number 为 1 */
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 2] = 0x01;
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 3] = 0x00;

    /* 设置 Status Code 为0. 这个包的这个字段没用 . */
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 4] = 0x00;
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 5] = 0x00;

    /* 设置 认证帧的长度 */
    us_auth_req_len = MAC_80211_FRAME_LEN + MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN +
                   MAC_STATUS_CODE_LEN;

    pst_user_ap = (hmac_user_stru *)mac_res_get_hmac_user((oal_uint16)pst_hmac_sta->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_user_ap)
    {
        OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::no present ap, alloc new ap.}");
        ul_ret = hmac_user_add(&pst_hmac_sta->st_vap_base_info, pst_hmac_sta->st_vap_base_info.auc_bssid, &us_user_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                             "{hmac_mgmt_encap_auth_req::hmac_user_add failed[%d].}", ul_ret);
            us_auth_req_len = 0;
        }
    }

    return us_auth_req_len;
}

/*****************************************************************************
 函 数 名  : hmac_prepare_auth_req_seq3
 功能描述  : 为shared key准备seq = 3 的认证帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_auth_req_seq3(hmac_vap_stru *pst_sta, oal_uint8 *puc_mgmt_frame, oal_uint8 *puc_mac_hrd)
{
    oal_uint8  *puc_data       = OAL_PTR_NULL;
    oal_uint16  us_index        = 0;
    oal_uint16  us_auth_req_len = 0;
    oal_uint8  *puc_ch_text     = OAL_PTR_NULL;
    oal_uint8   uc_ch_text_len  = 0;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    mac_hdr_set_frame_control(puc_mgmt_frame, WLAN_FC0_SUBTYPE_AUTH);

    /* 将帧保护字段置1 */
    mac_set_wep(puc_mgmt_frame, 1);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address1, pst_sta->st_vap_base_info.auc_bssid);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address2, pst_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address3, pst_sta->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Authentication Frame (Sequence 3) - Frame Body           */
    /* --------------------------------------------------------------------- */
    /* |Auth Algo Number|Auth Trans Seq Number|Status Code| Challenge Text | */
    /* --------------------------------------------------------------------- */
    /* | 2              |2                    |2          | 3 - 256        | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* 获取认证帧payload */
    us_index = MAC_80211_FRAME_LEN;
    puc_data = (oal_uint8 *)(puc_mgmt_frame + us_index);

    /* 设置 认证帧的长度 */
    us_auth_req_len = MAC_80211_FRAME_LEN + MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN +
                      MAC_STATUS_CODE_LEN;

    /* In case of no failure, the frame must be WEP encrypted. 4 bytes must  */
    /* be   left for the  IV  in  that  case. These   fields will  then  be  */
    /* reinitialized, using the correct index, with offset for IV field.     */
    puc_data[0] = WLAN_WITP_AUTH_SHARED_KEY;    /* Authentication Algorithm Number               */
    puc_data[1] = 0x00;

    puc_data[2] = 0x03;                    /* Authentication Transaction Sequence Number    */
    puc_data[3] = 0x00;

    /* If WEP subfield in the  incoming  authentication frame is 1,  respond */
    /* with  'challenge text failure' status,  since the STA does not expect */
    /* an encrypted frame in this state.                                     */
    if(1 == mac_is_protectedframe(puc_mac_hrd))
    {
        puc_data[4] = MAC_CHLNG_FAIL;
        puc_data[5] = 0x00;
    }

    /* If the STA does not support WEP, respond with 'unsupported algo'      */
    /* status, since WEP is necessary for Shared Key Authentication.         */
    else if(OAL_FALSE == mac_is_wep_enabled(&(pst_sta->st_vap_base_info)))
    {
        puc_data[4] = MAC_UNSUPT_ALG;
        puc_data[5] = 0x00;
    }

    /* If the default WEP key is NULL, respond with 'challenge text failure' */
    /* status, since a NULL key value cannot be used for WEP operations.     */
    else if(mac_get_wep_default_keysize(&pst_sta->st_vap_base_info) == 0)
    {
        puc_data[4] = MAC_CHLNG_FAIL;
        puc_data[5] = 0x00;
    }

    /* If there is a mapping in dot11WEPKeyMappings matching the address of  */
    /* the AP, and the corresponding key is NULL respond with 'challenge     */
    /* text failure' status. This is currently not being used.               */

    /* No error condition detected */
    else
    {

        /* Set Status Code to 'success' */
        puc_data[4] = MAC_SUCCESSFUL_STATUSCODE;
        puc_data[5] = 0x00;

        /* Extract 'Challenge Text' and its 'length' from the incoming       */
        /* authentication frame                                              */
        uc_ch_text_len = puc_mac_hrd[MAC_80211_FRAME_LEN + 7];
        puc_ch_text     = (oal_uint8 *)(&puc_mac_hrd[MAC_80211_FRAME_LEN + 8]);

        /* Challenge Text Element                  */
        /* --------------------------------------- */
        /* |Element ID | Length | Challenge Text | */
        /* --------------------------------------- */
        /* | 1         |1       |1 - 253         | */
        /* --------------------------------------- */

        puc_mgmt_frame[us_index + 6]   = MAC_EID_CHALLENGE;
        puc_mgmt_frame[us_index + 7]   = uc_ch_text_len;
        oal_memcopy(&puc_mgmt_frame[us_index + 8], puc_ch_text, uc_ch_text_len);

        /* Add the challenge text element length to the authentication       */
        /* request frame length. The IV, ICV element lengths will be added   */
        /* after encryption.                                                 */
        us_auth_req_len += (uc_ch_text_len + MAC_IE_HDR_LEN);
    }

    return us_auth_req_len;
}

/*****************************************************************************
 函 数 名  : hmac_encap_2040_coext_mgmt
 功能描述  : 封装 20/40 共存管理帧
 输入参数  : pst_mac_vap   : MAC VAP结构体指针
             puc_buffer    : 帧头指针
             uc_coext_info : 20/40 BSS Coexistence Information field(in 20/40 BSS Coexistence IE)
             ul_chan_report: Channel List(in 20/40 BSS Intolerant Channel Report IE)
 输出参数  : 无
 返 回 值  : 20/40 共存管理帧长度(帧头 + 帧体，不包括FCS)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  hmac_encap_2040_coext_mgmt(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_coext_info, oal_uint32 ul_chan_report)
{
    oal_uint8                      uc_chan_idx     = 0;
    oal_uint16                     us_ie_len_idx   = 0;
    oal_uint16                     us_index;
    wlan_channel_band_enum_uint8   en_band         = pst_mac_vap->st_channel.en_band;
    oal_uint8                      uc_max_num_chan = mac_get_num_supp_channel(en_band);
    oal_uint8                      uc_channel_num;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /* 设置 Frame Control field */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* 设置分片序号为0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* 设置 address1(接收端): AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, pst_mac_vap->auc_bssid);

    /* 设置 address2(发送端): dot11StationID */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 设置 address3: AP MAC地址 (BSSID) */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_mac_vap->auc_bssid);

    /*************************************************************************************/
    /*                 20/40 BSS Coexistence Management frame - Frame Body               */
    /* --------------------------------------------------------------------------------- */
    /* |Category |Public Action |20/40 BSS Coex IE| 20/40 BSS Intolerant Chan Report IE| */
    /* --------------------------------------------------------------------------------- */
    /* |1        |1             |3                |Variable                            | */
    /* --------------------------------------------------------------------------------- */
    /*                                                                                   */
    /*************************************************************************************/
    us_index = MAC_80211_FRAME_LEN;

    puc_buffer[us_index++] = MAC_ACTION_CATEGORY_PUBLIC;           /* Category */
    puc_buffer[us_index++] = MAC_PUB_COEXT_MGMT;                   /* Public Action */

    /* 封装20/40 BSS Coexistence element */
    puc_buffer[us_index++] = MAC_EID_2040_COEXT;                   /* Element ID */
    puc_buffer[us_index++] = MAC_2040_COEX_LEN;                    /* Length */
    puc_buffer[us_index++] = uc_coext_info;                        /* 20/40 BSS Coexistence Information field */

    /* 封装20/40 BSS Intolerant Channel Report element */
    /* 只有当STA检测到Trigger Event A时，才包含Operating Class，参见802.11n 10.15.12 */
    puc_buffer[us_index++] = MAC_EID_2040_INTOLCHREPORT;       /* Element ID */
    us_ie_len_idx          = us_index;
    puc_buffer[us_index++] = MAC_2040_INTOLCHREPORT_LEN_MIN;   /* Length */
    puc_buffer[us_index++] = 0;                               /* Operating Class */
    if (ul_chan_report > 0)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                      "{hmac_encap_2040_coext_mgmt::Channel List = 0x%x.}", ul_chan_report);
        /* Channel List */
        for (uc_chan_idx = 0; uc_chan_idx < uc_max_num_chan; uc_chan_idx++)
        {
            if (0 != ((ul_chan_report >> uc_chan_idx) & BIT0))
            {
                mac_get_channel_num_from_idx(en_band, uc_chan_idx, &uc_channel_num);
                puc_buffer[us_index++] = uc_channel_num;
                puc_buffer[us_ie_len_idx]++;
            }
        }
    }

    return us_index;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : hmac_mgmt_encap_smps_sta
 功能描述  : Hmac组帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 帧长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_mgmt_encap_smps_sta(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer)
{

    oal_uint16                     us_index;
    oal_uint8                      uc_smps_mode;
    mac_device_stru               *pst_mac_device;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/
    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        return 0;
    }

    /* 设置 Frame Control field */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* 设置分片序号为0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* 设置 address1(接收端): AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, pst_mac_vap->auc_bssid);

    /* 设置 address2(发送端): dot11StationID */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 设置 address3: AP MAC地址 (BSSID) */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                  SMPS Management frame - Frame Body                   */
    /* ----------------------------------------------------------------------*/
    /* |Category |HT Action |SMPS Control field|                             */
    /* ----------------------------------------------------------------------*/
    /* |1        |1         |1                 |                             */
    /* ----------------------------------------------------------------------*/
    /*                                                                       */
    /*************************************************************************/
    us_index = MAC_80211_FRAME_LEN;

    puc_buffer[us_index++] = MAC_ACTION_CATEGORY_HT;           /* Category  */
    puc_buffer[us_index++] = MAC_HT_ACTION_SMPS;               /* HT Action */

    /* SMPS Control field */
    /* Bit0 --- enable/disable smps   Bit1 --- SMPS MODE */
    puc_buffer[us_index] = 0;                                /* Element ID */

    uc_smps_mode = mac_mib_get_smps(pst_mac_vap);

    if ((OAL_FALSE == pst_mac_device->en_smps) || (WLAN_MIB_MIMO_POWER_SAVE_MIMO == uc_smps_mode))
    {
        puc_buffer[us_index++] = pst_mac_device->en_smps;
    }
    else
    {
        puc_buffer[us_index++] = ((uc_smps_mode | (pst_mac_device->en_smps)) & (BIT0 | BIT1));
    }

    return us_index;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

