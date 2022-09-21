/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_user.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
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
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "mac_user.h"
//#include "mac_11i.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_USER_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : mac_user_add_wep_key
 功能描述  : 添加wep密钥到指定的密钥槽
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_add_wep_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{
    if (uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    if ((oal_uint32)pst_key->key_len > WLAN_WEP104_KEY_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    if ((oal_uint32)pst_key->seq_len > WLAN_WPA_SEQ_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_add_rsn_key
 功能描述  : 更新rsn单播信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_add_rsn_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{
    if (uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }
    if ((oal_uint32)pst_key->key_len > WLAN_WPA_KEY_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    if ((oal_uint32)pst_key->seq_len > WLAN_WPA_SEQ_LEN)
    {
        return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_key_info.en_cipher_type    = (oal_uint8)pst_key->cipher;
    pst_mac_user->st_key_info.uc_default_index  = uc_key_index;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_add_bip_key
 功能描述  : 更新bip信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_add_bip_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key)
{

    /* keyid校验 */
    if (uc_key_index < WLAN_NUM_TK || uc_key_index > WLAN_MAX_IGTK_KEY_INDEX)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_cipher    = pst_key->cipher;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_key_len   = (oal_uint32)pst_key->key_len;
    pst_mac_user->st_key_info.ast_key[uc_key_index].ul_seq_len   = (oal_uint32)pst_key->seq_len;

    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_key, pst_key->auc_key, (oal_uint32)pst_key->key_len);
    oal_memcopy(&pst_mac_user->st_key_info.ast_key[uc_key_index].auc_seq, pst_key->auc_seq, (oal_uint32)pst_key->seq_len);

    pst_mac_user->st_key_info.uc_igtk_key_index = uc_key_index;

    return  OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_get_key
 功能描述  : 根据en_key_type，调用相应的函数，更新vap信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
wlan_priv_key_param_stru *mac_user_get_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_id)
{
    if(uc_key_id >= WLAN_NUM_TK + WLAN_NUM_IGTK)
    {
        return OAL_PTR_NULL;
    }
    return &pst_mac_user->st_key_info.ast_key[uc_key_id];
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_set_port
 功能描述  : 复位11X端口
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_set_port(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_port_valid)
{
    pst_mac_user->en_port_valid = en_port_valid;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_HISTREAM
/*****************************************************************************
 函 数 名  : mac_user_set_histream
 功能描述  : 设置histream信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_set_histream(mac_user_stru *pst_mac_user, mac_histream_stru *pst_histream_info)
{

    pst_mac_user->st_histream_info.en_hidevice_type = pst_histream_info->en_hidevice_type;
#if 0
    puc_data += 1;

    uc_port_num = *puc_data;
    if (uc_port_num > 8)
    {
        return OAL_FAIL;
    }
    puc_data += 1;
    pst_mac_user->st_histream_info.uc_udp_filter_num = uc_port_num;
    for (uc_port_idx = 0; uc_port_idx < uc_port_num; uc_port_idx++)
    {
        pst_mac_user->st_histream_info.aus_udp_port[uc_port_idx] = OAL_NTOH_16(puc_data)

        puc_data += 2;
    }

    uc_port_num = *puc_data;
    if (uc_port_num > 8)
    {
        return OAL_FAIL;
    }
    puc_data += 1;
    pst_mac_user->st_histream_info.uc_tcp_filter_num = uc_port_num;
    for (uc_port_idx = 0; uc_port_idx < uc_port_num; uc_port_idx++)
    {
        pst_mac_user->st_histream_info.aus_tcp_port[uc_port_idx] = OAL_NTOH_16(puc_data)

        puc_data += 2;
    }
#endif
    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_HISTREAM

/*****************************************************************************
 函 数 名  : mac_user_init_key
 功能描述  : 初始化用户的密钥信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_init_key(mac_user_stru *pst_mac_user)
{

    OAL_MEMZERO(&pst_mac_user->st_key_info, sizeof(mac_key_mgmt_stru));
    pst_mac_user->st_key_info.en_cipher_type  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    pst_mac_user->st_key_info.uc_last_gtk_key_idx = 0xFF;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_set_key
 功能描述  : 设置用户的安全信息
 输入参数  :
 输出参数  :
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :
 其    他  : 截止此函数编写时，只有keyid得到使用，multiuser下的安全信息可以优化一下
 修改历史      :
  1.日    期   : 2015年03月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_set_key(mac_user_stru *pst_multiuser,
                            wlan_cipher_key_type_enum_uint8 en_keytype,
                            wlan_ciper_protocol_type_enum_uint8 en_ciphertype,
                            oal_uint8       uc_keyid)
{

    pst_multiuser->st_user_tx_info.st_security.en_cipher_key_type      = en_keytype;
    pst_multiuser->st_user_tx_info.st_security.en_cipher_protocol_type = en_ciphertype;
    pst_multiuser->st_user_tx_info.st_security.uc_cipher_key_id        = uc_keyid;
    OAM_WARNING_LOG4(0, OAM_SF_WPA,
                   "{mac_user_set_key::keytpe==%u, ciphertype==%u, keyid==%u, usridx==%u}",
                   en_keytype, en_ciphertype, uc_keyid, pst_multiuser->us_assoc_id);


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_init
 功能描述  : 初始化mac user公共部分
 输入参数  : pst_mac_user: 指向user的结构体
             us_user_idx : 用户索引
             puc_mac_addr: MAC地址
             uc_chip_id  :
             uc_device_id:
             uc_vap_id   :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_user_init(
                mac_user_stru  *pst_mac_user,
                oal_uint16      us_user_idx,
                oal_uint8      *puc_mac_addr,
                oal_uint8       uc_chip_id,
                oal_uint8       uc_device_id,
                oal_uint8       uc_vap_id)
{

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_user_init::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化chip id, device ip, vap id */
    pst_mac_user->uc_chip_id    = uc_chip_id;
    pst_mac_user->uc_device_id  = uc_device_id;
    pst_mac_user->uc_vap_id     = uc_vap_id;
    pst_mac_user->us_assoc_id   = us_user_idx;
    pst_mac_user->uc_drop_ncw   = OAL_FALSE;

    /* 初始化密钥 */
    pst_mac_user->st_user_tx_info.st_security.en_cipher_key_type      = WLAN_KEY_TYPE_PTK;
    pst_mac_user->st_user_tx_info.st_security.en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    //pst_mac_user->st_user_tx_info.st_security.en_cipher_protocol_type = WLAN_NO_ENCRYP;

    /* 初始化安全加密信息 */
    mac_user_init_key(pst_mac_user);
    mac_user_set_key(pst_mac_user, WLAN_KEY_TYPE_PTK, WLAN_80211_CIPHER_SUITE_NO_ENCRYP, 0);
    mac_user_set_port(pst_mac_user, OAL_FALSE);
    pst_mac_user->en_user_asoc_state = MAC_USER_STATE_BUTT;

    if (OAL_PTR_NULL == puc_mac_addr)
    {
        pst_mac_user->en_is_multi_user   = OAL_TRUE;
        pst_mac_user->en_user_asoc_state = MAC_USER_STATE_ASSOC;
    }
    else
    {
        /* 初始化一个用户是否是组播用户的标志，组播用户初始化时不会调用本函数 */
        pst_mac_user->en_is_multi_user = OAL_FALSE;

        /* 设置mac地址 */
        oal_set_mac_addr(pst_mac_user->auc_user_mac_addr, puc_mac_addr);
    }


    /* 初始化能力 */
    mac_user_set_pmf_active(pst_mac_user, OAL_FALSE);

    mac_user_set_avail_num_spatial_stream(pst_mac_user, MAC_USER_INIT_STREAM);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_set_avail_bf_num_spatial_stream
 功能描述  : 设置user公共区域uc_avail_num_spatial_stream Tx和Rx支持Nss的交集,供算法调用的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_avail_bf_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_avail_bf_num_spatial_stream = uc_value;
}

/*****************************************************************************
 函 数 名  : mac_user_set_avail_num_spatial_stream
 功能描述  : 设置user公共区域uc_avail_num_spatial_stream Tx和Rx支持Nss的交集,供算法调用的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_avail_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_avail_num_spatial_stream = uc_value;
}
/*****************************************************************************
 函 数 名  : mac_user_set_num_spatial_stream
 功能描述  : 设置user公共区域uc_num_spatial_stream用户支持空间流个数的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value)
{
    pst_mac_user->uc_num_spatial_stream = uc_value;
}
/*****************************************************************************
 函 数 名  : mac_user_set_bandwidth_cap
 功能描述  : 设置用户的bandwidth能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_bandwidth_cap(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bandwidth_value)
{
    pst_mac_user->en_bandwidth_cap = en_bandwidth_value;
}
/*****************************************************************************
 函 数 名  : mac_user_set_bandwidth_info
 功能描述  : 设置可用带宽的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月27日
    作    者   : 
    修改内容   : 新生成函数
  1.日    期   : 2015年5月27日
    作    者   :  68207
    修改内容   : 针对协议切换, 对带宽更新进行特殊判断

*****************************************************************************/
oal_void mac_user_set_bandwidth_info(mac_user_stru *pst_mac_user,
                                                wlan_bw_cap_enum_uint8 en_avail_bandwidth,
                                                wlan_bw_cap_enum_uint8 en_cur_bandwidth)
{
    pst_mac_user->en_avail_bandwidth = en_avail_bandwidth;
    pst_mac_user->en_cur_bandwidth   = en_cur_bandwidth;

    /* Autorate将协议从11n切换成11b后, cur_bandwidth会变为20M
       此时如果软件将带宽改为40M, cur_bandwidth仍需要保持20M */
    if ((WLAN_LEGACY_11B_MODE == pst_mac_user->en_cur_protocol_mode) &&
        (WLAN_BW_CAP_20M != pst_mac_user->en_cur_bandwidth))
    {
        pst_mac_user->en_cur_bandwidth = WLAN_BW_CAP_20M;
    }
}

/*****************************************************************************
 函 数 名  : mac_user_get_sta_cap_bandwidth
 功能描述  : 获取用户的带宽
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_user_get_sta_cap_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    wlan_bw_cap_enum_uint8        en_bandwidth_cap;

    /* 获取HT和VHT结构体指针 */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        if (0 == pst_mac_vht_hdl->bit_supported_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else
        {
            en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }
    else if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (1 == pst_mac_ht_hdl->bit_supported_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
        else

        {
            en_bandwidth_cap = WLAN_BW_CAP_20M;
        }
    }
    else
    {
        en_bandwidth_cap = WLAN_BW_CAP_20M;
    }

    mac_user_set_bandwidth_cap(pst_mac_user, en_bandwidth_cap);

    /* 将带宽值由出参带出 */
    *pen_bandwidth_cap = en_bandwidth_cap;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_get_ap_opern_bandwidth
 功能描述  : 根据AP的operation ie获取ap的工作带宽
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_user_get_ap_opern_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    wlan_bw_cap_enum_uint8        en_bandwidth_cap;

    /* 获取HT和VHT结构体指针 */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    en_bandwidth_cap = WLAN_BW_CAP_20M;


    if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (MAC_SCN != pst_mac_ht_hdl->bit_secondary_chan_offset)
        {
            en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
    }

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        /* uc_channel_width的取值，0 -- 20/40M, 1 -- 80M, 2 -- 160M */

        if (1 == pst_mac_vht_hdl->uc_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else if (2 == pst_mac_vht_hdl->uc_channel_width)
        {
            en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }
    *pen_bandwidth_cap = en_bandwidth_cap;
    mac_user_set_bandwidth_cap(pst_mac_user, en_bandwidth_cap);
}
/*****************************************************************************
 函 数 名  : mac_user_update_bandwidth
 功能描述  : 根据AP的operation ie获取ap的工作带宽
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_user_update_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bwcap)
{
    mac_user_ht_hdl_stru           *pst_mac_ht_hdl;
    mac_vht_hdl_stru               *pst_mac_vht_hdl;
    ;

    if (OAL_PTR_NULL == pst_mac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取HT和VHT结构体指针 */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_20M;

    if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (MAC_SCN != pst_mac_ht_hdl->bit_secondary_chan_offset)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_40M;
        }
    }

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        /* uc_channel_width的取值，0 -- 20/40M, 1 -- 80M, 2 -- 160M */

        if (1 == pst_mac_vht_hdl->uc_channel_width)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_80M;
        }
        else if (2 == pst_mac_vht_hdl->uc_channel_width)
        {
            pst_mac_user->en_bandwidth_cap = WLAN_BW_CAP_160M;
        }
    }

    pst_mac_user->en_avail_bandwidth = OAL_MIN(en_bwcap, pst_mac_user->en_bandwidth_cap);
    pst_mac_user->en_cur_bandwidth   = pst_mac_user->en_avail_bandwidth;
    return OAL_SUCC;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 函 数 名  : mac_user_change_info_event
 功能描述  : 将用户状态或者能力变化的信息上报
 输入参数  : auc_user_macaddr: 用户mac地址
             uc_vap_id       : 作为vap的vap_id
             ul_val_old      : 变化前的值
             ul_val_new      : 变化后的值
             en_mod          : 模块号
             en_type         : 哪一种信息变化
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_user_change_info_event(
                                    oal_uint8  auc_user_macaddr[],
                                    oal_uint8  uc_vap_id,
                                    oal_uint32 ul_val_old,
                                    oal_uint32 ul_val_new,
                                    oam_module_id_enum_uint16 en_mod,
                                    oam_user_info_change_type_enum_uint8 en_type)
{

    oal_uint8       auc_event_info[OAM_EVENT_INFO_MAX_LEN] = {0};
    oam_user_info_change_stru  *pst_change_info;

    pst_change_info = (oam_user_info_change_stru *)auc_event_info;
    pst_change_info->en_change_type = en_type;
    pst_change_info->ul_val_before_change = ul_val_old;
    pst_change_info->ul_val_after_change  = ul_val_new;

    oam_event_report(auc_user_macaddr, uc_vap_id, en_mod, OAM_EVENT_USER_INFO_CHANGE, auc_event_info);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : mac_user_set_assoc_id
 功能描述  : 设置user的assoc id
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_assoc_id(mac_user_stru *pst_mac_user, oal_uint16 us_assoc_id)
{
    pst_mac_user->us_assoc_id = us_assoc_id;
}
/*****************************************************************************
 函 数 名  : mac_user_set_avail_protocol_mode
 功能描述  : 这只mac user中的user与vap协议模式的交集模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_coid
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_avail_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_avail_protocol_mode)
{
    pst_mac_user->en_avail_protocol_mode = en_avail_protocol_mode;
}
/*****************************************************************************
 函 数 名  : mac_user_set_cur_protocol_mode
 功能描述  : 设置mac user中的cur_protocol_mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_coid
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_cur_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_cur_protocol_mode)
{
    pst_mac_user->en_cur_protocol_mode = en_cur_protocol_mode;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_set_cur_bandwidth
 功能描述  : 设置mac user中的带宽信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_user_set_cur_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8  en_cur_bandwidth)
{
    pst_mac_user->en_cur_bandwidth = en_cur_bandwidth;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_user_set_avail_protocol_mode
 功能描述  : 这只mac user中的user与vap协议模式的交集模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_coid
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_protocol_mode)
{
    pst_mac_user->en_protocol_mode = en_protocol_mode;
}
/*****************************************************************************
 函 数 名  : mac_user_set_asoc_state
 功能描述  : 设置en_user_asoc_state 的统一接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_asoc_state(mac_user_stru *pst_mac_user, mac_user_asoc_state_enum_uint8 en_value)
{
    pst_mac_user->en_user_asoc_state = en_value;
}
/*****************************************************************************
 函 数 名  : mac_user_set_avail_op_rates
 功能描述  : 设置user下可用速率集
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_avail_op_rates(mac_user_stru *pst_mac_user, oal_uint8 uc_rs_nrates, oal_uint8 *puc_rs_rates)
{
    pst_mac_user->st_avail_op_rates.uc_rs_nrates = uc_rs_nrates;
    oal_memcopy(pst_mac_user->st_avail_op_rates.auc_rs_rates, puc_rs_rates, WLAN_RATE_MAXSIZE);
}
/*****************************************************************************
 函 数 名  : mac_user_set_vht_hdl
 功能描述  : 对用户的vht信息进行设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl)
{
   oal_memcopy((oal_uint8 *)(&pst_mac_user->st_vht_hdl), (oal_uint8 *)pst_vht_hdl, OAL_SIZEOF(mac_vht_hdl_stru));
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_get_vht_hdl
 功能描述  : 获取用户的vht信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_get_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl)
{
    oal_memcopy((oal_uint8 *)pst_vht_hdl, (oal_uint8 *)(&pst_mac_user->st_vht_hdl), OAL_SIZEOF(mac_vht_hdl_stru));
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_set_vht_hdl
 功能描述  : 对用户的vht信息进行设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl)
{
   oal_memcopy((oal_uint8 *)(&pst_mac_user->st_ht_hdl), (oal_uint8 *)pst_ht_hdl, OAL_SIZEOF(mac_user_ht_hdl_stru));
}
/*****************************************************************************
 函 数 名  : mac_user_get_ht_hdl
 功能描述  : 获取用户的ht信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_get_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl)
{
    oal_memcopy((oal_uint8 *)pst_ht_hdl, (oal_uint8 *)(&pst_mac_user->st_ht_hdl), OAL_SIZEOF(mac_user_ht_hdl_stru));
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_set_ht_capable
 功能描述  : 设置ht cap信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_ht_capable(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_ht_capable)
{
    pst_mac_user->st_ht_hdl.en_ht_capable = en_ht_capable;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : mac_user_set_sm_power_save
 功能描述  : 设置用户的ht能力中sm_power_save的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_sm_power_save(mac_user_stru *pst_mac_user, oal_uint8 uc_sm_power_save)
{
    pst_mac_user->st_ht_hdl.bit_sm_power_save = uc_sm_power_save;
}
#endif
/*****************************************************************************
 函 数 名  : mac_user_set_pmf_active
 功能描述  : 设置与用户pmf能力协商的结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_pmf_active(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_pmf_active)
{
    pst_mac_user->st_cap_info.bit_pmf_active = en_pmf_active;
}
/*****************************************************************************
 函 数 名  : mac_user_set_barker_preamble_mode
 功能描述  : 设置用户barker_preamble的模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_barker_preamble_mode(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_barker_preamble_mode)
{
    pst_mac_user->st_cap_info.bit_barker_preamble_mode = en_barker_preamble_mode;
}

/*****************************************************************************
 函 数 名  : mac_user_set_qos
 功能描述  : 设置与用户的qos使能结果‘
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_qos(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_qos_mode)
{
    pst_mac_user->st_cap_info.bit_qos = en_qos_mode;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_user_set_spectrum_mgmt
 功能描述  : 设置更新用户bit_spectrum_mgmt能力的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_user_set_spectrum_mgmt(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_spectrum_mgmt)
{
    pst_mac_user->st_cap_info.bit_spectrum_mgmt = en_spectrum_mgmt;
}

/*****************************************************************************
 函 数 名  : mac_user_set_apsd
 功能描述  : 设置用户公共区域的bit_apsd能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_user_set_apsd(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_apsd)
{
    pst_mac_user->st_cap_info.bit_apsd = en_apsd;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_user_update_wep_key
 功能描述  : 设置用户wep加密密钥信息
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_user_update_wep_key(mac_user_stru *pst_mac_usr, oal_uint16 us_multi_user_idx)
{
    mac_user_stru        *pst_multi_user   = OAL_PTR_NULL;

    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_usr, OAL_ERR_CODE_PTR_NULL);

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    if (pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_104 &&
        pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_40)
    {

        OAM_ERROR_LOG1(0, OAM_SF_WPA, "{mac_wep_add_usr_key::en_cipher_type==%d}",
                       pst_multi_user->st_key_info.en_cipher_type);
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    if (pst_multi_user->st_key_info.uc_default_index >= WLAN_MAX_WEP_KEY_COUNT)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    /* wep加密下，拷贝组播用户的密钥信息到单播用户 */
    oal_memcopy(&pst_mac_usr->st_key_info, &pst_multi_user->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));

    /* TBD 发送信息要挪出去 */
    pst_mac_usr->st_user_tx_info.st_security.en_cipher_key_type = pst_mac_usr->st_key_info.uc_default_index + HAL_KEY_TYPE_PTK;//获取WEP default key id

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_addr_is_zero
 功能描述  : 判断mac地址是否全0
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 mac_addr_is_zero(oal_uint8 *puc_mac)
{
    oal_uint8    auc_mac_zero[OAL_MAC_ADDR_LEN] = {0};

    MAC_11I_ASSERT((OAL_PTR_NULL != puc_mac), OAL_TRUE);

    return (0 == oal_memcmp(auc_mac_zero, puc_mac, OAL_MAC_ADDR_LEN));
}

/*****************************************************************************
 函 数 名  : mac_res_get_mac_user
 功能描述  : 获取对应MAC USER索引的内存
 输入参数  : 对应MAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void*  mac_res_get_mac_user(oal_uint16 us_idx)
{
    mac_user_stru*    pst_mac_user;

    pst_mac_user = (mac_user_stru*)_mac_res_get_mac_user(us_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        return OAL_PTR_NULL;
    }

    /* 异常: 用户资源已被释放 */ /* user id=0为特殊user,单播不为0 */
    if ((MAC_USER_ALLOCED != pst_mac_user->uc_is_user_alloced) && (0 != us_idx))
    {
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        /*lint -e718*//*lint -e746*/
        OAM_WARNING_LOG2(0, OAM_SF_UM, "{mac_res_get_mac_user::[E]user has been freed,user_idx=%d, func[%x].}", us_idx, (oal_uint32)__return_address());
        /*lint +e718*//*lint +e746*/
#else
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_mac_user::[E]user has been freed,user_idx=%d.}", us_idx);
#endif
        //return OAL_PTR_NULL;
    }

    return  (void*)pst_mac_user;
}


/*lint -e19*/

oal_module_symbol(mac_user_get_key);

oal_module_symbol(mac_user_set_port);

oal_module_symbol(mac_user_set_key);
oal_module_symbol(mac_user_init);
oal_module_symbol(mac_user_set_avail_num_spatial_stream);
oal_module_symbol(mac_user_set_num_spatial_stream);
oal_module_symbol(mac_user_set_bandwidth_cap);
oal_module_symbol(mac_user_get_sta_cap_bandwidth);
oal_module_symbol(mac_user_get_ap_opern_bandwidth);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
oal_module_symbol(mac_user_change_info_event);
#endif

oal_module_symbol(mac_user_set_bandwidth_info);
oal_module_symbol(mac_user_set_assoc_id);
oal_module_symbol(mac_user_set_protocol_mode);
oal_module_symbol(mac_user_set_avail_protocol_mode);
oal_module_symbol(mac_user_set_cur_protocol_mode);
oal_module_symbol(mac_user_set_cur_bandwidth);

oal_module_symbol(mac_user_avail_bf_num_spatial_stream);
oal_module_symbol(mac_user_set_asoc_state);
oal_module_symbol(mac_user_set_avail_op_rates);
oal_module_symbol(mac_user_set_vht_hdl);
oal_module_symbol(mac_user_get_vht_hdl);
oal_module_symbol(mac_user_set_ht_hdl);
oal_module_symbol(mac_user_get_ht_hdl);
oal_module_symbol(mac_user_set_ht_capable);
#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(mac_user_set_sm_power_save);
#endif
oal_module_symbol(mac_user_set_pmf_active);
oal_module_symbol(mac_user_set_barker_preamble_mode);
oal_module_symbol(mac_user_set_qos);
oal_module_symbol(mac_user_set_spectrum_mgmt);
oal_module_symbol(mac_user_set_apsd);

oal_module_symbol(mac_user_init_key);
oal_module_symbol(mac_user_update_wep_key);
oal_module_symbol(mac_addr_is_zero);
oal_module_symbol(mac_res_get_mac_user);
/*lint +e19*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

