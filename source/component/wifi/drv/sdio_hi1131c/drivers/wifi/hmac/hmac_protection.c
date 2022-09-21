/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_protection.c
  版 本 号   : 初稿
  作    者   : 曹海彬
  生成日期   : 2014年1月18日
  最近修改   :
  功能描述   : 放置与保护相关的函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月18日
    作    者   : 曹海彬
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
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_vap.h"
#include "hmac_protection.h"
#include "mac_vap.h"
#include "mac_ie.h"
#include "hmac_config.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_PROTECTION_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

OAL_STATIC oal_uint32 hmac_protection_set_mode(
                                 mac_vap_stru *pst_mac_vap,
                                 wlan_prot_mode_enum_uint8 en_prot_mode);

/*****************************************************************************
 函 数 名  : hmac_protection_is_autoprot_enabled
 功能描述  : 查询自动保护机制是否开启
 输入参数  : pst_hmac_vap : hmac vap结构体指针
 输出参数  : 无
 返 回 值  : OAL_FALSE: 保护未开启， OAL_TRUE:  保护开启
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_switch_enum_uint8 hmac_protection_is_autoprot_enabled(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->st_protection.bit_auto_protection;
}

/*****************************************************************************
 函 数 名  : hmac_protection_set_autoprot
 功能描述  : 设置VAP自动保护机制是否开启
 输入参数  : pst_hmac_vap : hmac vap结构体指针
             en_mode      : 0 :设置自动保护机制关闭， 1:设置自动保护机制打开
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
 oal_uint32 hmac_protection_set_autoprot(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_mode)
{
    oal_uint32      ul_ret = OAL_SUCC;
    hmac_user_stru *pst_hmac_user;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_SWITCH_OFF == en_mode)
    {
        pst_mac_vap->st_protection.bit_auto_protection = OAL_SWITCH_OFF;
        ul_ret = hmac_protection_set_mode(pst_mac_vap, WLAN_PROT_NO);
    }
    else
    {
        pst_mac_vap->st_protection.bit_auto_protection = OAL_SWITCH_ON;
        /*VAP 为 AP情况下*/
        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            ul_ret = hmac_protection_update_mode_ap(pst_mac_vap);
        }
        /*VAP 为 STA情况下*/
        else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            pst_hmac_user = mac_res_get_hmac_user(pst_mac_vap->uc_assoc_vap_id); /*user保存的是AP的信息*/
            if (OAL_PTR_NULL == pst_hmac_user)
            {
                return OAL_ERR_CODE_PTR_NULL;
            }

            ul_ret = hmac_protection_update_mode_sta(pst_mac_vap, pst_hmac_user);
        }
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_set_rtscts_mechanism
 功能描述  : 设置rts-cts保护机制是否开启及保护范围
 输入参数  : pst_hmac_vap : hmac vap结构体指针
             en_flag      : 0:关闭rts cts保护机制   / 1: 打开rts cts保护机制
             en_prot_mode : 指示保护级别(rts cts机制可以做erp保护，也可以做ht保护)
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_protection_set_rtscts_mechanism(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag, wlan_prot_mode_enum_uint8 en_prot_mode)
{
    oal_uint32 ul_ret = OAL_SUCC;
    mac_cfg_rts_tx_param_stru st_rts_tx_param;

    /*只有启用erp保护时候，RTS[0~2]速率才设为5.5Mpbs(11b), 其余时候都为24Mpbs(leagcy ofdm) */
    if ((WLAN_PROT_ERP == en_prot_mode) && (OAL_SWITCH_ON == en_flag))
    {
        st_rts_tx_param.en_band = WLAN_BAND_2G;

        /* RTS[0~2]设为5.5Mbps, RTS[3]设为1Mbps */
        st_rts_tx_param.auc_protocol_mode[0]    = WLAN_11B_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[0]             = WLAN_LONG_11b_5_HALF_M_BPS;
        st_rts_tx_param.auc_protocol_mode[1]    = WLAN_11B_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[1]             = WLAN_LONG_11b_5_HALF_M_BPS;
        st_rts_tx_param.auc_protocol_mode[2]    = WLAN_11B_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[2]             = WLAN_LONG_11b_5_HALF_M_BPS;
        st_rts_tx_param.auc_protocol_mode[2]    = WLAN_11B_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[2]             = WLAN_LONG_11b_5_HALF_M_BPS;
        st_rts_tx_param.auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
    }
    else
    {
        st_rts_tx_param.en_band = pst_mac_vap->st_channel.en_band;

        /* RTS[0~2]设为24Mbps */
        st_rts_tx_param.auc_protocol_mode[0]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[0]             = WLAN_LEGACY_OFDM_24M_BPS;
        st_rts_tx_param.auc_protocol_mode[1]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[1]             = WLAN_LEGACY_OFDM_24M_BPS;
        st_rts_tx_param.auc_protocol_mode[2]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        st_rts_tx_param.auc_rate[2]             = WLAN_LEGACY_OFDM_24M_BPS;

        /* 2G的RTS[3]设为1Mbps */
        if (WLAN_BAND_2G == st_rts_tx_param.en_band)
        {
            st_rts_tx_param.auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
            st_rts_tx_param.auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
        }
        /* 5G的RTS[3]设为24Mbps */
        else
        {
            st_rts_tx_param.auc_protocol_mode[3]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            st_rts_tx_param.auc_rate[3]             = WLAN_LEGACY_OFDM_24M_BPS;
        }
    }

    ul_ret = hmac_config_set_rts_param(pst_mac_vap, OAL_SIZEOF(mac_cfg_rts_tx_param_stru), (oal_uint8*)(&st_rts_tx_param));

    /*数据帧/管理帧发送时候，需要根据bit_rts_cts_protect_mode值填写发送描述符中的RTS/CTS enable位*/
    pst_mac_vap->st_protection.bit_rts_cts_protect_mode = en_flag;

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_set_lsig_txop_mechanism
 功能描述  : 设置lsig txop保护机制是否开启及保护范围
 输入参数  : pst_hmac_vap : hmac vap结构体指针
             en_flag      : 0:关闭lsig txop保护机制   / 1: 打开lsig txop保护机制
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_protection_set_lsig_txop_mechanism(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag)
{
    /*数据帧/管理帧发送时候，需要根据bit_lsig_txop_protect_mode值填写发送描述符中的L-SIG TXOP enable位*/
    pst_mac_vap->st_protection.bit_lsig_txop_protect_mode = en_flag;

}

/*****************************************************************************
 函 数 名  : hmac_protection_set_erp_protection
 功能描述  : 设置erp保护是否开启
 输入参数  : pst_hmac_vap : hmac vap结构体指针
             en_flag      : 0:关闭erp保护   / 1: 打开erp保护
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 hmac_protection_set_erp_protection(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag)
{
    oal_uint32 ul_ret = OAL_SUCC;
    /*1151只支持RTS-CTS机制来保护， 不支持Self-To-CTS机制*/
    ul_ret = hmac_protection_set_rtscts_mechanism(pst_mac_vap, en_flag, WLAN_PROT_ERP);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_lsigtxop_check
 功能描述  : 查询是否可以使用lsigtxop保护
 输入参数  : pst_mac_vap : mac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_bool_enum : 0: 不可以使用lsig txop保护
                             1: 可以使用lsig txop保护
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum hmac_protection_lsigtxop_check(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru  *pst_mac_user;

    /*如果不是11n站点，则不支持lsigtxop保护*/
    if ((WLAN_HT_MODE != pst_mac_vap->en_protocol)
        && (WLAN_HT_ONLY_MODE != pst_mac_vap->en_protocol)
        && (WLAN_HT_11G_MODE != pst_mac_vap->en_protocol))
    {
        return OAL_FALSE;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id); /*user保存的是AP的信息*/
        if (OAL_PTR_NULL == pst_mac_user)
        {
            return OAL_FALSE;
        }
    }
    /*lint -e644*/
    /*BSS 中所有站点都支持Lsig txop protection, 则使用Lsig txop protection机制，开销小, AP和STA采用不同的判断*/
    if (((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) && (OAL_TRUE == mac_mib_get_LsigTxopFullProtectionActivated(pst_mac_vap)))
         ||((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) && (OAL_TRUE == pst_mac_user->st_ht_hdl.bit_lsig_txop_protection_full_support)))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
    /*lint +e644*/

}

/*****************************************************************************
 函 数 名  : hmac_protection_update_ht_protection
 功能描述  : 由于en_dot11LSIGTXOPFullProtectionActivated值发生变化，
             需要更新HT protection的机制， lsig txop protection 或者 rts cts protection
 输入参数  : pst_mac_vap : mac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_protection_update_ht_protection(mac_vap_stru *pst_mac_vap)
{
    oal_uint32    ul_ret      = OAL_SUCC;
    oal_bool_enum en_lsigtxop = OAL_FALSE;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*当前vap并没有设置ht 保护，直接返回*/
    if (WLAN_PROT_HT != pst_mac_vap->st_protection.en_protection_mode)
    {
        return OAL_SUCC;
    }

    en_lsigtxop = hmac_protection_lsigtxop_check(pst_mac_vap);

    /*如果可以设置lsigtxop保护， 则优先设置lsigtxop保护*/
    if (OAL_TRUE == en_lsigtxop)
    {
        /*如果启用了rts cts protection机制， 则更新为lsig txop protection机制*/
        if (OAL_SWITCH_ON == pst_mac_vap->st_protection.bit_rts_cts_protect_mode)
        {
            ul_ret = hmac_protection_set_rtscts_mechanism(pst_mac_vap, OAL_SWITCH_OFF, WLAN_PROT_HT);
            if(OAL_SUCC != ul_ret)
            {
                return ul_ret;
            }

            hmac_protection_set_lsig_txop_mechanism(pst_mac_vap, OAL_SWITCH_ON);
        }
    }
    else/*其余情况需要设置ht保护方式为rts cts protection 机制*/
    {
        /*如果启用了rts cts protection机制， 则更新为lsig txop protection机制*/
        if (OAL_SWITCH_ON == pst_mac_vap->st_protection.bit_lsig_txop_protect_mode)
        {
            hmac_protection_set_lsig_txop_mechanism(pst_mac_vap, OAL_SWITCH_OFF);
            ul_ret = hmac_protection_set_rtscts_mechanism(pst_mac_vap, OAL_SWITCH_ON, WLAN_PROT_HT);
            if(OAL_SUCC != ul_ret)
	     {
                return ul_ret;
	     }
        }
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_set_ht_protection
 功能描述  : 设置ht保护是否开启
 输入参数  : pst_mac_vap : mac vap结构体指针
             en_flag      : 0:关闭ht保护   / 1: 打开ht保护
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_protection_set_ht_protection(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag)
{
    oal_uint32      ul_ret = OAL_SUCC;
    oal_bool_enum   en_lsigtxop = OAL_FALSE;

    en_lsigtxop = hmac_protection_lsigtxop_check(pst_mac_vap);
    /*优先使用lsigtxop保护，开销小*/
    if (OAL_TRUE == en_lsigtxop)
    {
        hmac_protection_set_lsig_txop_mechanism(pst_mac_vap, en_flag);
    }
    else
    {
        ul_ret = hmac_protection_set_rtscts_mechanism(pst_mac_vap, en_flag, WLAN_PROT_HT);
        if(OAL_SUCC != ul_ret)
        {
	     return ul_ret;
	 }
    }

    return ul_ret;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

oal_bool_enum_uint8 hmac_protection_need_sync(mac_vap_stru *pst_mac_vap,
                                mac_h2d_protection_stru *pst_h2d_prot)
{
    mac_h2d_protection_stru *pst_prot_old;
    hmac_vap_stru       *pst_hmac_vap;
    mac_protection_stru *pst_old;
    mac_protection_stru *pst_new;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{hmac_protection_need_sync::null hmac_vap}");
        return OAL_FALSE;
    }
    pst_prot_old = &pst_hmac_vap->st_prot;

    if ( (pst_prot_old->en_dot11HTProtection != pst_h2d_prot->en_dot11HTProtection) ||
         (pst_prot_old->en_dot11RIFSMode != pst_h2d_prot->en_dot11RIFSMode) ||
         (pst_prot_old->en_dot11LSIGTXOPFullProtectionActivated != pst_h2d_prot->en_dot11LSIGTXOPFullProtectionActivated) ||
         (pst_prot_old->en_dot11NonGFEntitiesPresent != pst_h2d_prot->en_dot11NonGFEntitiesPresent)
         )
    {
        oal_memcopy(pst_prot_old, pst_h2d_prot, OAL_SIZEOF(mac_h2d_protection_stru));
        return OAL_TRUE;
    }

    pst_old = &pst_prot_old->st_protection;
    pst_new = &pst_h2d_prot->st_protection;

    if ( (pst_old->en_protection_mode != pst_new->en_protection_mode) ||
         (pst_old->bit_auto_protection != pst_new->bit_auto_protection) ||
         (pst_old->bit_obss_non_erp_present != pst_new->bit_obss_non_erp_present) ||
         (pst_old->bit_obss_non_ht_present != pst_new->bit_obss_non_ht_present) ||
         (pst_old->bit_rts_cts_protect_mode != pst_new->bit_rts_cts_protect_mode) ||
         (pst_old->bit_lsig_txop_protect_mode != pst_new->bit_lsig_txop_protect_mode) ||
         (pst_old->uc_sta_non_ht_num != pst_new->uc_sta_non_ht_num)
      )
    {
        oal_memcopy(pst_prot_old, pst_h2d_prot, OAL_SIZEOF(mac_h2d_protection_stru));
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_protection_set_mode
 功能描述  : 同步保护相关的参数到Dmac
 输入参数  : pst_hmac_vap : hmac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : 
    修改内容   : 新生成函数

***************************************************************************/
OAL_STATIC oal_uint32 hmac_protection_sync_data(mac_vap_stru *pst_mac_vap)
{
    mac_h2d_protection_stru           st_h2d_prot;
    wlan_mib_Dot11OperationEntry_stru *pst_mib;
    oal_uint32                        ul_ret = OAL_SUCC;

    OAL_MEMZERO(&st_h2d_prot, OAL_SIZEOF(st_h2d_prot));

    st_h2d_prot.ul_sync_mask |= H2D_SYNC_MASK_MIB;
    st_h2d_prot.ul_sync_mask |= H2D_SYNC_MASK_PROT;

    oal_memcopy((oal_uint8*)&st_h2d_prot.st_protection, (oal_uint8*)&pst_mac_vap->st_protection,
                OAL_SIZEOF(mac_protection_stru));

    pst_mib = &pst_mac_vap->pst_mib_info->st_wlan_mib_operation;
    st_h2d_prot.en_dot11HTProtection         = pst_mib->en_dot11HTProtection;
    st_h2d_prot.en_dot11RIFSMode             = pst_mib->en_dot11RIFSMode;
    st_h2d_prot.en_dot11LSIGTXOPFullProtectionActivated =
                    pst_mib->en_dot11LSIGTXOPFullProtectionActivated;
    st_h2d_prot.en_dot11NonGFEntitiesPresent = pst_mib->en_dot11NonGFEntitiesPresent;

    if (OAL_TRUE == hmac_protection_need_sync(pst_mac_vap, &st_h2d_prot))
    {
        ul_ret = hmac_config_set_protection(pst_mac_vap, OAL_SIZEOF(st_h2d_prot),
                                        (oal_uint8*)&st_h2d_prot);
    }

    return ul_ret;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_protection_set_mode
 功能描述  : 设置vap的保护类型
 输入参数  : pst_hmac_vap : hmac vap结构体指针
             en_prot_mode : 保护类型
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_protection_set_mode(
                                 mac_vap_stru *pst_mac_vap,
                                 wlan_prot_mode_enum_uint8 en_prot_mode)
{
    oal_uint32 ul_ret = OAL_SUCC;

    if (en_prot_mode != pst_mac_vap->st_protection.en_protection_mode)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_protection_sync_data::mode[%d]->mode[%d]}",
             pst_mac_vap->st_protection.en_protection_mode,en_prot_mode);
    }

    /*相同的保护模式已经被设置，直接返回*/
    if (en_prot_mode == pst_mac_vap->st_protection.en_protection_mode)
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        ul_ret = hmac_protection_sync_data(pst_mac_vap);
#endif
        return ul_ret;
    }

    /*关闭之前的保护模式*/
    if (WLAN_PROT_ERP == pst_mac_vap->st_protection.en_protection_mode)
    {
        ul_ret = hmac_protection_set_erp_protection(pst_mac_vap, OAL_SWITCH_OFF);
        if(OAL_SUCC != ul_ret)
        {
		return ul_ret;
	 }
    }
    else if (WLAN_PROT_HT == pst_mac_vap->st_protection.en_protection_mode)
    {
        ul_ret = hmac_protection_set_ht_protection(pst_mac_vap, OAL_SWITCH_OFF);
        if(OAL_SUCC != ul_ret)
        {
		return ul_ret;
	 }
    }
    else
    {
        /*GF保护和无保护无需额外操作*/
    }

    pst_mac_vap->st_protection.en_protection_mode = en_prot_mode;

    /*开启新的保护模式*/
    if (WLAN_PROT_ERP == en_prot_mode)
    {
        ul_ret = hmac_protection_set_erp_protection(pst_mac_vap, OAL_SWITCH_ON);
        if(OAL_SUCC != ul_ret)
        {
		return ul_ret;
	 }
    }
    else if (WLAN_PROT_HT == en_prot_mode)
    {
        ul_ret = hmac_protection_set_ht_protection(pst_mac_vap, OAL_SWITCH_ON);
        if(OAL_SUCC != ul_ret)
        {
		return ul_ret;
	 }
    }
    else
    {
        /*GF保护和无保护无需额外操作*/
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_ret = hmac_protection_sync_data(pst_mac_vap);
#else
    /*更新数据帧或管理帧与保护特性相关的发送参数*/
    hmac_config_update_protection_tx_param(pst_mac_vap, OAL_SIZEOF(ul_ret), (oal_uint8*)(&ul_ret)); /*后面两个参数无作用*/
#endif

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : hmac_protection_update_mib_ap
 功能描述  : 更新AP保护相关mib量
 输入参数  : pst_hmac_vap : hmac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_update_mib_ap(mac_vap_stru *pst_mac_vap)
{
    oal_uint32           ul_ret         = OAL_SUCC;
    mac_protection_stru *pst_protection = OAL_PTR_NULL;
    oal_bool_enum_uint8  en_lsig_txop_full_protection_activated;
    oal_bool_enum_uint8  en_non_gf_entities_present;
    oal_bool_enum_uint8  en_rifs_mode;
    oal_bool_enum_uint8  en_ht_protection;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_protection = &(pst_mac_vap->st_protection);

    /*更新vap的en_dot11NonGFEntitiesPresent字段*/
    en_non_gf_entities_present = (0 != pst_protection->uc_sta_non_gf_num) ? OAL_TRUE : OAL_FALSE;
    mac_mib_set_NonGFEntitiesPresent(pst_mac_vap, en_non_gf_entities_present);

    /*更新vap的en_dot11LSIGTXOPFullProtectionActivated字段*/
    en_lsig_txop_full_protection_activated = (0 == pst_protection->uc_sta_no_lsig_txop_num) ? OAL_TRUE : OAL_FALSE;

    mac_mib_set_LsigTxopFullProtectionActivated(pst_mac_vap, en_lsig_txop_full_protection_activated);

    ul_ret = hmac_protection_update_ht_protection(pst_mac_vap);
    if(OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_protection_update_mib_ap::hmac_protection_update_ht_protection fail.err code %u}",ul_ret);
        return ul_ret;
    }

    /*更新vap的en_dot11HTProtection和en_dot11RIFSMode字段*/
    if (0 != pst_protection->uc_sta_non_ht_num)
    {
        en_ht_protection = WLAN_MIB_HT_NON_HT_MIXED;
        en_rifs_mode     = OAL_FALSE;
    }
    else if (OAL_TRUE == pst_protection->bit_obss_non_ht_present)
    {
        en_ht_protection = WLAN_MIB_HT_NONMEMBER_PROTECTION;
        en_rifs_mode     = OAL_FALSE;
    }
    else if ((WLAN_BAND_WIDTH_20M != pst_mac_vap->st_channel.en_bandwidth)
               && (0 != pst_protection->uc_sta_20M_only_num))
    {
        en_ht_protection = WLAN_MIB_HT_20MHZ_PROTECTION;
        en_rifs_mode     = OAL_TRUE;
    }
    else
    {
        en_ht_protection = WLAN_MIB_HT_NO_PROTECTION;
        en_rifs_mode     = OAL_TRUE;
    }

    mac_mib_set_HtProtection(pst_mac_vap, en_ht_protection);
    mac_mib_set_RifsMode(pst_mac_vap, en_rifs_mode);

    ul_ret = hmac_protection_update_mode_ap(pst_mac_vap);
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_update_mode_ap
 功能描述  : 根据mac vap结构体统计值更新AP保护模式
 输入参数  : pst_mac_vap : mac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_update_mode_ap(mac_vap_stru *pst_mac_vap)
{
    oal_uint32                ul_ret             = OAL_SUCC;
    wlan_prot_mode_enum_uint8 en_protection_mode = WLAN_PROT_NO;
    mac_protection_stru      *pst_protection     = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_protection = &(pst_mac_vap->st_protection);

    /*如果保护机制不启用， 直接返回*/
    if (OAL_SWITCH_OFF == hmac_protection_is_autoprot_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    /*在2G频段下，如果有non erp站点与AP关联， 或者OBSS中存在non erp站点， 设置为erp保护*/
    if ((WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
         && ((0 != pst_protection->uc_sta_non_erp_num) || (OAL_TRUE == pst_protection->bit_obss_non_erp_present)))
    {
        en_protection_mode = WLAN_PROT_ERP;
    }
    /*如果有non ht站点与AP关联， 或者OBSS中存在non ht站点， 设置为ht保护*/
    else if ((0 != pst_protection->uc_sta_non_ht_num) || (OAL_TRUE == pst_protection->bit_obss_non_ht_present))
    {
        en_protection_mode = WLAN_PROT_HT;
    }
    /*如果有non gf站点与AP关联， 设置为gf保护*/
    else if (0 != pst_protection->uc_sta_non_gf_num)
    {
        en_protection_mode = WLAN_PROT_GF;
    }
    /*剩下的情况不做保护*/
    else
    {
        en_protection_mode = WLAN_PROT_NO;
    }

    /*设置具体保护模式*/
    ul_ret = hmac_protection_set_mode(pst_mac_vap, en_protection_mode);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_update_mode_sta
 功能描述  : 根据保存在user结构体中的AP信息更新STA保护模式
 输入参数  : mac_vap_stru        : mac VAP结构体， 保存sta信息
             pst_mac_sta         : mac user结构体， 保存ap信息
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_update_mode_sta(mac_vap_stru *pst_mac_vap_sta, hmac_user_stru *pst_hmac_user)
{
    oal_uint32                ul_ret             = OAL_SUCC;
    wlan_prot_mode_enum_uint8 en_protection_mode = WLAN_PROT_NO;
    mac_user_stru            *pst_mac_user       = &pst_hmac_user->st_user_base_info;

    if ((OAL_PTR_NULL == pst_mac_vap_sta) || (OAL_PTR_NULL == pst_mac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*如果保护机制不启用， 直接返回*/
    if (OAL_SWITCH_OFF == hmac_protection_is_autoprot_enabled(pst_mac_vap_sta))
    {
        return OAL_SUCC;
    }

    /*在2G频段下，如果AP发送的beacon帧ERP ie中Use Protection bit置为1，则将保护级别设置为ERP保护*/
    if ((WLAN_BAND_2G == pst_mac_vap_sta->st_channel.en_band) && (OAL_TRUE == pst_hmac_user->st_hmac_cap_info.bit_erp_use_protect))
    {
        en_protection_mode = WLAN_PROT_ERP;
    }
    /*如果AP发送的beacon帧ht operation ie中ht protection字段为mixed或non-member，则将保护级别设置为HT保护*/
    else if ((WLAN_MIB_HT_NON_HT_MIXED == pst_mac_user->st_ht_hdl.bit_HT_protection)
              ||(WLAN_MIB_HT_NONMEMBER_PROTECTION == pst_mac_user->st_ht_hdl.bit_HT_protection))
    {
        en_protection_mode = WLAN_PROT_HT;
    }
    /*如果AP发送的beacon帧ht operation ie中non-gf sta present字段为1，则将保护级别设置为GF保护*/
    else if (OAL_TRUE == pst_mac_user->st_ht_hdl.bit_nongf_sta_present)
    {
        en_protection_mode = WLAN_PROT_GF;
    }
    /*剩下的情况不做保护*/
    else
    {
        en_protection_mode = WLAN_PROT_NO;
    }

    /*设置具体保护模式*/
    ul_ret = hmac_protection_set_mode(pst_mac_vap_sta, en_protection_mode);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_obss_aging_ap
 功能描述  : OBSS老化处理， 本函数定期执行(5000ms 执行一次)
 输入参数  : pst_mac_vap : mac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_obss_aging_ap(mac_vap_stru *pst_mac_vap)
{
    oal_uint32    ul_ret               = OAL_SUCC;
    oal_bool_enum em_update_protection = OAL_FALSE; /*指示是否需要更新vap的protection*/

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*更新ERP老化计数*/
    if (OAL_TRUE == pst_mac_vap->st_protection.bit_obss_non_erp_present)
    {
        pst_mac_vap->st_protection.uc_obss_non_erp_aging_cnt++;
        if (pst_mac_vap->st_protection.uc_obss_non_erp_aging_cnt >= WLAN_PROTECTION_NON_ERP_AGING_THRESHOLD)
        {
            pst_mac_vap->st_protection.bit_obss_non_erp_present = OAL_FALSE;
            em_update_protection = OAL_TRUE;
            pst_mac_vap->st_protection.uc_obss_non_erp_aging_cnt = 0;
        }
    }

    /*更新HT老化计数*/
    if (OAL_TRUE == pst_mac_vap->st_protection.bit_obss_non_ht_present)
    {
        pst_mac_vap->st_protection.uc_obss_non_ht_aging_cnt++;

        if (pst_mac_vap->st_protection.uc_obss_non_ht_aging_cnt >= WLAN_PROTECTION_NON_HT_AGING_THRESHOLD)
        {
            pst_mac_vap->st_protection.bit_obss_non_ht_present = OAL_FALSE;
            em_update_protection = OAL_TRUE;
            pst_mac_vap->st_protection.uc_obss_non_ht_aging_cnt = 0;
        }
    }

    /*需要更新保护模式*/
    if(OAL_TRUE == em_update_protection)
    {
        ul_ret = hmac_protection_update_mib_ap(pst_mac_vap);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_del_user_stat_legacy_ap
 功能描述  : 删除保护模式相关user统计(legacy)
 输入参数  : pst_mac_vap  : mac vap结构体指针
             pst_mac_user : mac user结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_protection_del_user_stat_legacy_ap(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    mac_protection_stru    *pst_protection = &(pst_mac_vap->st_protection);
    hmac_user_stru         *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_mac_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                        "hmac_protection_del_user_stat_legacy_ap::Get Hmac_user(idx=%d) NULL POINT!", pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*如果去关联的站点不支持ERP*/
    if ((OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_erp)
        && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_erp_stats_flag)
        && (0 != pst_protection->uc_sta_non_erp_num))
    {
        pst_protection->uc_sta_non_erp_num--;
    }

    /*如果去关联的站点不支持short preamble*/
    if ((OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_short_preamble)
        && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_short_preamble_stats_flag)
        && (0 != pst_protection->uc_sta_no_short_preamble_num))
    {
        pst_protection->uc_sta_no_short_preamble_num--;
    }

    /*如果去关联的站点不支持short slot*/
    if ((OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_short_slot_time)
        && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_short_slot_stats_flag)
        && (0 != pst_protection->uc_sta_no_short_slot_num))
    {
        pst_protection->uc_sta_no_short_slot_num--;
    }

    pst_hmac_user->st_user_stats_flag.bit_no_short_slot_stats_flag     = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_no_short_preamble_stats_flag = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_no_erp_stats_flag            = OAL_FALSE;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_protection_del_user_stat_ht_ap
 功能描述  : 删除保护模式相关user统计(ht)
 输入参数  : pst_mac_vap  : mac vap结构体指针
             pst_mac_user : mac user结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_protection_del_user_stat_ht_ap(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    mac_user_ht_hdl_stru   *pst_ht_hdl     = &(pst_mac_user->st_ht_hdl);
    mac_protection_stru    *pst_protection = &(pst_mac_vap->st_protection);
    hmac_user_stru         *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_mac_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                        "hmac_protection_del_user_stat_ht_ap::Get Hmac_user(idx=%d) NULL POINT!", pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*如果去关联的站点不支持HT*/
    if ((OAL_FALSE == pst_ht_hdl->en_ht_capable)
        && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_ht_stats_flag)
        && (0 != pst_protection->uc_sta_non_ht_num))
    {
        pst_protection->uc_sta_non_ht_num--;
    }
    else /*支持HT*/
    {
        /*如果去关联的站点不支持20/40Mhz频宽*/
        if ((OAL_FALSE == pst_ht_hdl->bit_supported_channel_width)
            && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_20M_only_stats_flag)
            && (0 != pst_protection->uc_sta_20M_only_num))
        {
            pst_protection->uc_sta_20M_only_num--;
        }

        /*如果去关联的站点不支持GF*/
        if ((OAL_FALSE == pst_ht_hdl->bit_ht_green_field)
            && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_gf_stats_flag)
            && (0 != pst_protection->uc_sta_non_gf_num))
        {
            pst_protection->uc_sta_non_gf_num--;
        }

        /*如果去关联的站点不支持L-SIG TXOP Protection*/
        if ((OAL_FALSE == pst_ht_hdl->bit_lsig_txop_protection)
            && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_lsig_txop_stats_flag)
            && (0 != pst_protection->uc_sta_no_lsig_txop_num))
        {
            pst_protection->uc_sta_no_lsig_txop_num--;
        }

        /*如果去关联的站点不支持40Mhz cck*/
        if ((OAL_FALSE == pst_ht_hdl->bit_dsss_cck_mode_40mhz)
             && (OAL_TRUE == pst_ht_hdl->bit_supported_channel_width)
             && (OAL_TRUE == pst_hmac_user->st_user_stats_flag.bit_no_40dsss_stats_flag)
             && (0 != pst_protection->uc_sta_no_40dsss_cck_num))
        {
            pst_protection->uc_sta_no_40dsss_cck_num--;
        }
    }

    pst_hmac_user->st_user_stats_flag.bit_no_ht_stats_flag             = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_no_gf_stats_flag             = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_20M_only_stats_flag          = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_no_40dsss_stats_flag         = OAL_FALSE;
    pst_hmac_user->st_user_stats_flag.bit_no_lsig_txop_stats_flag      = OAL_FALSE;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_protection_del_user_stat_ap
 功能描述  : 删除保护模式相关user统计
 输入参数  : pst_mac_vap  : mac vap结构体指针
             pst_mac_user : mac user结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_protection_del_user_stat_ap(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    hmac_protection_del_user_stat_legacy_ap(pst_mac_vap, pst_mac_user);
    hmac_protection_del_user_stat_ht_ap(pst_mac_vap, pst_mac_user);


}

/*****************************************************************************
 函 数 名  : hmac_protection_del_user
 功能描述  : AP:删除user统计， 并更新保护模式
             STA: 更新为无保护模式
 输入参数  : pst_mac_vap  : mac vap结构体指针
             pst_mac_user : mac user结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_del_user(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    oal_uint32 ul_ret = OAL_SUCC;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_mac_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*AP 更新VAP结构体统计量，更新保护机制*/
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /*删除保护模式相关user统计*/
        hmac_protection_del_user_stat_ap(pst_mac_vap, pst_mac_user);

        /*更新AP中保护相关mib量*/
        ul_ret = hmac_protection_update_mib_ap(pst_mac_vap);
        if(OAL_SUCC != ul_ret)
        {
		return ul_ret;
	 }
    }
    /*恢复STA为无保护状态*/
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        ul_ret = hmac_protection_set_mode(pst_mac_vap, WLAN_PROT_NO);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_protection_obss_aging_ap
 功能描述  : OBSS老化处理， 本函数定期对device每个VAP进行保护老化处理(5000ms 执行一次)
 输入参数  : p_arg : 定时器传入的指针参数
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_protection_obss_update_timer(void *p_arg)
{
    mac_device_stru     *pst_mac_device;
    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_protection_obss_update_timer::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = (mac_device_stru *)p_arg;

    /* 遍历device下对应VAP, 定时更新OBSS 保护模式 */
    /* 业务vap从1开始 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG0(uc_vap_idx, OAM_SF_ANY, "{hmac_protection_obss_update_timer::pst_mac_vap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* OBSS老化只针对AP模式，非AP模式则跳出 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        hmac_protection_obss_aging_ap(pst_mac_vap);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_protection_obss_aging_ap
 功能描述  : 启动OBSS老化处理定时器
 输入参数  : pst_hmac_vap : hmac vap结构体指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_protection_start_timer(hmac_vap_stru  *pst_hmac_vap)
{
    mac_device_stru                *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_protection_start_timer::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 启动OBSS保护老化定时器 定时器已开启，则不用再开启 */
    if (OAL_FALSE == pst_mac_device->st_obss_aging_timer.en_is_registerd)
    {
        FRW_TIMER_CREATE_TIMER(&(pst_mac_device->st_obss_aging_timer),
                               hmac_protection_obss_update_timer,
                               WLAN_USER_AGING_TRIGGER_TIME,                    /* 5000ms触发一次 */
                               pst_mac_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_HMAC,
                               pst_mac_device->ul_core_id);
    }

    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

