/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_encap_frame.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月28日
  最近修改   :
  功能描述   : AP模式和STA模式共有帧的组帧文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 创建文件

*******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "wlan_spec.h"
#include "mac_resource.h"
#include "hmac_encap_frame.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ENCAP_FRAME_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
     函 数 名  : hmac_encap_sa_query_req
     功能描述  : 组sa query 请求帧
     输入参数  : pst_mac_vap :mac vap结构体
                 puc_data    :netbuf data指针
                 puc_da      :目标用户的mac地址
                 trans_id    :sa query ie,用于辨别response和request是否一致
     输出参数  : 无
     返 回 值  : 帧头+帧体的长度
     调用函数  :
     被调函数  :

     修改历史      :
      1.日    期   : 2014年4月19日
        作    者   : 
        修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_encap_sa_query_req(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da,oal_uint16 us_trans_id)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /*  Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
     puc_data[MAC_80211_FRAME_LEN] = MAC_ACTION_CATEGORY_SA_QUERY;
     puc_data[MAC_80211_FRAME_LEN+1] = MAC_SA_QUERY_ACTION_REQUEST;
     puc_data[MAC_80211_FRAME_LEN+2] = (us_trans_id & 0x00FF);
     puc_data[MAC_80211_FRAME_LEN+3] = (us_trans_id & 0xFF00) >> 8;

     us_len = MAC_80211_FRAME_LEN + MAC_SA_QUERY_LEN;
     return us_len;
}

/*****************************************************************************
     函 数 名  : hmac_encap_sa_query_rsp
     功能描述  : 组sa query 反馈帧
     输入参数  : pst_hdr:sa query request frame
                 puc_data:sa query response frame
     输出参数  : 无
     返 回 值  : 帧头+帧体的长度
     调用函数  :
     被调函数  :

     修改历史      :
      1.日    期   : 2014年4月19日
        作    者   : 
        修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_encap_sa_query_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 *pst_hdr, oal_uint8 *puc_data)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /* Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, ((mac_ieee80211_frame_stru *)pst_hdr)->auc_address2);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_data[MAC_80211_FRAME_LEN] = pst_hdr[MAC_80211_FRAME_LEN];
    puc_data[MAC_80211_FRAME_LEN+1] = MAC_SA_QUERY_ACTION_RESPONSE;
    puc_data[MAC_80211_FRAME_LEN+2] = pst_hdr[MAC_80211_FRAME_LEN+2];
    puc_data[MAC_80211_FRAME_LEN+3] = pst_hdr[MAC_80211_FRAME_LEN+3];

    us_len = MAC_80211_FRAME_LEN + MAC_SA_QUERY_LEN;
    return us_len;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_prepare_deauth
 功能描述  : 组去认证帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_deauth(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code)
{
    oal_uint16          us_deauth_len = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_up_vap1;
    mac_vap_stru       *pst_up_vap2;
    oal_uint32          ul_ret;
#endif

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

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_DEAUTH);

    /* Set DA to address of unauthenticated STA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);

#ifdef _PRE_WLAN_FEATURE_P2P
    if (us_err_code & MAC_SEND_TWO_DEAUTH_FLAG)
    {
        us_err_code = us_err_code & ~MAC_SEND_TWO_DEAUTH_FLAG;

        pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
        {
            us_deauth_len = 0;
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_mgmt_encap_deauth::pst_mac_device[%d] null!}", pst_mac_vap->uc_device_id);
            return us_deauth_len;
        }

        ul_ret = mac_device_find_2up_vap(pst_mac_device, &pst_up_vap1, &pst_up_vap2);
        if (OAL_SUCC == ul_ret)
        {
            /* 获取另外一个VAP，组帧时修改地址2为另外1个VAP的MAC地址 */
            if (pst_mac_vap->uc_vap_id != pst_up_vap1->uc_vap_id)
            {
                pst_up_vap2 = pst_up_vap1;
            }

            if (OAL_PTR_NULL == pst_up_vap2->pst_mib_info)
            {
                us_deauth_len = 0;
                OAM_ERROR_LOG0(pst_up_vap2->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: pst_up_vap2 mib ptr null.");
                return us_deauth_len;
            }
            oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_up_vap2->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
            oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_up_vap2->auc_bssid);
        }

        OAM_WARNING_LOG1(0, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: send the second deauth frame. error code:%d", us_err_code);
    }
    else
#endif
    {
        if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
        {
            us_deauth_len = 0;
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_deauth: pst_mac_vap mib ptr null.");
            return us_deauth_len;
        }

        /* SA is the dot11MACAddress */
        oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
        oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);
    }
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  Deauthentication Frame - Frame Body                  */
    /* --------------------------------------------------------------------- */
    /* |                           Reason Code                             | */
    /* --------------------------------------------------------------------- */
    /* |2 Byte                                                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* Set Reason Code to 'Class2 error' */
    puc_data[MAC_80211_FRAME_LEN]     = (us_err_code & 0x00FF);
    puc_data[MAC_80211_FRAME_LEN + 1] = (us_err_code & 0xFF00) >> 8;

    us_deauth_len = MAC_80211_FRAME_LEN + WLAN_REASON_CODE_LEN;

    return us_deauth_len;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_encap_disassoc
 功能描述  : 组去关联帧
 输入参数  : vap指针,DA,ErrCode
 输出参数  : 帧缓冲区
 返 回 值  : 帧长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_disassoc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da, oal_uint16 us_err_code)
{
    oal_uint16 us_disassoc_len = 0;

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
    /*                            设置帧头                                   */
    /*************************************************************************/

    /* 设置subtype   */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_DISASSOC);

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        us_disassoc_len = 0;
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "hmac_mgmt_encap_disassoc: pst_mac_vap mib ptr null.");
        return us_disassoc_len;
    }
    /* 设置DA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);

    /* 设置SA */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 设置bssid */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_AP ?
                                                            pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID : pst_mac_vap->auc_bssid);



    /*************************************************************************/
    /*                  Disassociation 帧 - 帧体                  */
    /* --------------------------------------------------------------------- */
    /* |                           Reason Code                             | */
    /* --------------------------------------------------------------------- */
    /* |2 Byte                                                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* 设置reason code*/
    puc_data[MAC_80211_FRAME_LEN]     = (us_err_code & 0x00FF);
    puc_data[MAC_80211_FRAME_LEN + 1] = (us_err_code & 0xFF00) >> 8;

    us_disassoc_len = MAC_80211_FRAME_LEN + WLAN_REASON_CODE_LEN;

    return us_disassoc_len;
}

/*****************************************************************************
 函 数 名  : hmac_check_sta_base_rate
 功能描述  : 检查当前STA是否支持AP的基本速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_check_sta_base_rate(oal_uint8 *pst_user, mac_status_code_enum_uint16 *pen_status_code)
{
    oal_uint8            num_basic_rates;
    oal_uint8            uc_loop;
    oal_uint8            uc_index;
    oal_bool_enum_uint8  en_found;
    oal_uint8            uc_num_rates;
    oal_uint8            uc_ap_base_rate;
    mac_vap_stru        *pst_mac_vap;
    hmac_user_stru      *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)pst_user;

    /* 获取VAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return;
    }

    num_basic_rates = pst_mac_vap->st_curr_sup_rates.uc_br_rate_num;
    uc_num_rates    = pst_hmac_user->st_op_rates.uc_rs_nrates;


    for (uc_loop = 0; uc_loop < num_basic_rates; uc_loop++)
    {
        en_found = OAL_FALSE;
        uc_ap_base_rate = mac_vap_get_curr_baserate(pst_mac_vap,uc_loop);

        for (uc_index = 0; uc_index < uc_num_rates; uc_index++)
        {
            if ((pst_hmac_user->st_op_rates.auc_rs_rates[uc_index] & 0x7F) == (uc_ap_base_rate & 0x7F))
            {
                en_found = OAL_TRUE;
                break;
            }
        }

        /* 不支持某基本速率，返回false  */
        if (OAL_FALSE == en_found)
        {
            *pen_status_code = MAC_UNSUP_RATE;
            return;
        }
    }
}
/*****************************************************************************
 函 数 名  : hmac_encap_notify_chan_width
 功能描述  : 组装Notify Channel Width Action帧
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
oal_uint16 hmac_encap_notify_chan_width(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, oal_uint8 *puc_da)
{
    oal_uint16 us_len = 0;

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
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_ACTION);
    /*  Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, puc_da);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  SA Query Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* |   Category   |SA Query Action |  Transaction Identifier           | */
    /* --------------------------------------------------------------------- */
    /* |1             |1               |2 Byte                             | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
     puc_data[MAC_80211_FRAME_LEN] = MAC_ACTION_CATEGORY_HT;
     puc_data[MAC_80211_FRAME_LEN+1] = MAC_HT_ACTION_NOTIFY_CHANNEL_WIDTH;
     puc_data[MAC_80211_FRAME_LEN+2] = (pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M) ? 1 : 0;

     us_len = MAC_80211_FRAME_LEN + MAC_HT_NOTIFY_CHANNEL_WIDTH_LEN;
     return us_len;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

