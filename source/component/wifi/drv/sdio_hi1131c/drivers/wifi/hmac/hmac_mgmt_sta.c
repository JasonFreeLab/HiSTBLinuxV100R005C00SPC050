/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_mgmt_sta.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月18日
  最近修改   :
  功能描述   : STA侧管理面处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月18日
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

#include "mac_frame.h"
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_user.h"
#include "mac_vap.h"

#include "mac_device.h"
#include "hmac_device.h"
#include "hmac_user.h"
#include "hmac_mgmt_sta.h"
#include "hmac_fsm.h"
#include "hmac_rx_data.h"
#include "hmac_chan_mgmt.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_encap_frame_sta.h"
#include "hmac_sme_sta.h"
#include "hmac_scan.h"

#include "hmac_tx_amsdu.h"

#include "hmac_11i.h"

#include "hmac_protection.h"

#include "hmac_config.h"
#include "hmac_ext_if.h"
#include "hmac_p2p.h"
#include "hmac_edca_opt.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#endif
#include "hmac_blockack.h"
#include "frw_ext_if.h"

#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_STA_C
#define MAC_ADDR(_puc_mac)   ((oal_uint32)(((oal_uint32)_puc_mac[2] << 24) |\
                                              ((oal_uint32)_puc_mac[3] << 16) |\
                                              ((oal_uint32)_puc_mac[4] << 8) |\
                                              ((oal_uint32)_puc_mac[5])))


/*****************************************************************************
  2 静态函数声明
*****************************************************************************/
OAL_STATIC oal_uint32 hmac_sta_update_join_req_params(hmac_vap_stru *pst_hmac_vap,hmac_join_req_stru *pst_join_req);
//OAL_STATIC oal_void hmac_handle_tbtt_chan_mgmt_sta(hmac_vap_stru *pst_hmac_vap);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
//OAL_STATIC oal_void hmac_btcoex_linkloss_check_and_process(hmac_vap_stru *pst_hmac_vap);
#endif


/*****************************************************************************
  3 全局变量定义
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_mgmt_timeout_sta
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_mgmt_timeout_sta(oal_void *p_arg)
{
    hmac_vap_stru *pst_hmac_vap;
    hmac_mgmt_timeout_param_stru    *pst_timeout_param;

    pst_timeout_param = (hmac_mgmt_timeout_param_stru *)p_arg;
    if (OAL_PTR_NULL == pst_timeout_param)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap      = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_timeout_param->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_TIMER0_OUT, pst_timeout_param);
}
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 函 数 名  : hmac_update_join_req_params_204080
 功能描述  : 在join之前，根据join request更新相关20/40共存参数(主要是更新带宽模式)
 输入参数  : pst_mac_vap : MAC VAP结构体(这里是STA模式)
             pst_bss_dscr: 要加入的bss网络信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_update_join_req_params_2040(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr)
{
    /* 如果STA或者AP不支持HT，则直接返回 */
    if ((OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)) ||
        (OAL_FALSE == pst_bss_dscr->en_ht_capable))
    {
        pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;
        return;
    }

    /* 使能40MHz */
    /* (1) 用户开启"40MHz运行"特性(即STA侧 dot11FortyMHzOperationImplemented为true) */
    /* (2) AP在40MHz运行 */
    if (OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
    {
        switch (pst_bss_dscr->en_channel_bandwidth)
        {
            case WLAN_BAND_WIDTH_40PLUS:
            case WLAN_BAND_WIDTH_80PLUSPLUS:
            case WLAN_BAND_WIDTH_80PLUSMINUS:
                pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40PLUS;
                break;

            case WLAN_BAND_WIDTH_40MINUS:
            case WLAN_BAND_WIDTH_80MINUSPLUS:
            case WLAN_BAND_WIDTH_80MINUSMINUS:
                pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40MINUS;
                break;

            default:
                pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;
                break;
        }
    }

    /* 更新STA侧带宽与AP一致 */
    /* (1) STA AP均支持11AC */
    /* (2) STA支持40M带宽(FortyMHzOperationImplemented为TRUE)，
           定制化禁止2GHT40时，2G下FortyMHzOperationImplemented=FALSE，不更新带宽 */
    /* (3) STA支持80M带宽(即STA侧 dot11VHTChannelWidthOptionImplemented为0) */
    if ((OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap)) &&
        (OAL_TRUE == pst_bss_dscr->en_vht_capable))
    {
        if ((OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
            && (WLAN_MIB_VHT_SUPP_WIDTH_80 == mac_mib_get_VHTChannelWidthOptionImplemented(pst_mac_vap)))
        {
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
            pst_mac_vap->st_channel.en_bandwidth = pst_bss_dscr->en_channel_bandwidth;
#else
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_update_join_req_params_2040::fpga is not support 80M.}");
#endif
        }
    }

    /* 如果AP和STA同时支持20/40共存管理功能，则使能STA侧频谱管理功能*/
    if ((OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
        (1 == pst_bss_dscr->uc_coex_mgmt_supp))
    {
        // TODO 确认一下
        mac_mib_set_SpectrumManagementImplemented(pst_mac_vap, OAL_TRUE);
    }
}
/*****************************************************************************
 函 数 名  : hmac_send_2040_coext_mgmt_frame_sta
 功能描述  : STA发送20/40 共存管理帧(根据Trigger Event A & Trigger Event B填写)
 输入参数  : pst_mac_vap: MAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_send_2040_coext_mgmt_frame_sta(mac_vap_stru *pst_mac_vap)
{
    oal_netbuf_stru   *pst_netbuf = OAL_PTR_NULL;
    mac_tx_ctl_stru   *pst_tx_ctl;
    oal_uint32         ul_ret;
    oal_uint16         us_frame_len = 0;
    oal_uint8          uc_coext_info = 0;
    oal_uint32         ul_channel_report = pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a;

    /* 根据dot11FortyMHzIntolerant填写此field */
    if ( (OAL_TRUE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)) ||
         (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_te_b) )
    {
        uc_coext_info |= BIT1;
    }

    /* 当检测到Trigger Event B时，设置此field为1 */
    if (0 != ul_channel_report)
    {
        uc_coext_info |= BIT2;
    }

    /* 清除上次扫描结果 */
    pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a = 0;
    pst_mac_vap->st_ch_switch_info.en_te_b = OAL_FALSE;

    /* 申请管理帧内存 */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_2040_coext_mgmt_frame_sta::pst_netbuf null.}");
        return;
    }
    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);

    OAL_NETBUF_PREV(pst_netbuf) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_netbuf) = OAL_PTR_NULL;

    /* 封装20/40 共存管理帧 */
    us_frame_len = hmac_encap_2040_coext_mgmt(pst_mac_vap, OAL_NETBUF_HEADER(pst_netbuf), uc_coext_info, ul_channel_report);

    oal_netbuf_put(pst_netbuf, us_frame_len);

    /* 填写netbuf的cb字段，供发送管理帧和发送完成接口使用 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());
    pst_tx_ctl->us_mpdu_len = us_frame_len;
    pst_tx_ctl->us_tx_user_idx = 0xFFFF;
    pst_tx_ctl->uc_ac = WLAN_WME_AC_MGMT;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{hmac_send_2040_coext_mgmt_frame_sta::uc_coext_info=%d, ul_channel_report=%d}",
        uc_coext_info, ul_channel_report);

    /* 抛事件到DMAC发送管理帧 */
    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_netbuf, us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_send_2040_coext_mgmt_frame_sta::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_2040_coext
 功能描述  : STA在UP状态下处理接收到的20/40共存管理帧
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             pst_netbuf : 包含20/40共存管理帧的netbuf指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_sta_up_rx_2040_coext(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint8          *puc_data;

    /* 非HT站点，不处理此帧 */
    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
    {
        return;
    }

    /* 如果STA不支持"20/40共存管理"特性，则直接忽略AP发过来的"20/40共存管理帧" */
    if (OAL_FALSE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_sta_up_rx_2040_coext::Ignoring the 20/40 Coexistence Management frame.}");
        return;
    }

    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* 获取帧体指针 */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* "Information Request" field */
    if (puc_data[MAC_ACTION_OFFSET_ACTION + 1 + 1 + 1] & BIT0)
    {
        /* 当STA收到一个Information Request为1的帧后，需要回一个20/40共存管理帧 */
        hmac_send_2040_coext_mgmt_frame_sta(pst_mac_vap);
    }
}

#endif
/*****************************************************************************
 函 数 名  : hmac_update_join_req_params_prot_sta
 功能描述  : 在join之前更新协议相关的参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_update_join_req_params_prot_sta(hmac_vap_stru * pst_hmac_vap, hmac_join_req_stru * pst_join_req)
{
    if (WLAN_MIB_DESIRED_BSSTYPE_INFRA  == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType)
    {
        pst_hmac_vap->uc_wmm_cap   = pst_join_req->st_bss_dscr.uc_wmm_cap;
        mac_vap_set_uapsd_cap(&pst_hmac_vap->st_vap_base_info, pst_join_req->st_bss_dscr.uc_uapsd_cap);
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    hmac_update_join_req_params_2040(&(pst_hmac_vap->st_vap_base_info), &(pst_join_req->st_bss_dscr));
#endif
}

/*****************************************************************************
 函 数 名  : hmac_is_rate_support
 功能描述  : 判断是否支持某种速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  hmac_is_rate_support(oal_uint8 *puc_rates, oal_uint8 uc_rate_num, oal_uint8 uc_rate)
{
    oal_bool_enum_uint8  en_rate_is_supp = OAL_FALSE;
    oal_uint8            uc_loop;

    if (OAL_PTR_NULL == puc_rates)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_is_rate_support::puc_rates null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_loop = 0; uc_loop < uc_rate_num; uc_loop++)
    {
        if ((puc_rates[uc_loop] & 0x7F) == uc_rate)
        {
            en_rate_is_supp = OAL_TRUE;
            break;
        }
    }

    return en_rate_is_supp;
}

/*****************************************************************************
 函 数 名  : hmac_is_support_11grate
 功能描述  : 是否支持11g速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  hmac_is_support_11grate(oal_uint8 *puc_rates, oal_uint8 uc_rate_num)
{
    if (OAL_PTR_NULL == puc_rates)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_is_rate_support::puc_rates null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x0C))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x12))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x18))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x24))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x30))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x48))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x60))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x6C)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}


/*****************************************************************************
 函 数 名  : hmac_is_support_11brate
 功能描述  : 是否支持11b速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  hmac_is_support_11brate(oal_uint8 *puc_rates, oal_uint8 uc_rate_num)
{
    if (OAL_PTR_NULL == puc_rates)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_is_support_11brate::puc_rates null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x02))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x04))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x0B))
        || (OAL_TRUE == hmac_is_rate_support(puc_rates, uc_rate_num, 0x16)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
#if 0
/*****************************************************************************
 函 数 名  : hmac_bss_is_rate_support
 功能描述  : 判断用户是否支持某种速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  hmac_bss_is_rate_support(mac_bss_dscr_stru* pst_bss_dscr, oal_uint8 uc_rate)
{
    oal_bool_enum_uint8  en_rate_is_supp = OAL_FALSE;
    oal_uint8            uc_loop;

    if (OAL_PTR_NULL == pst_bss_dscr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_bss_is_rate_support::pst_bss_dscr null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_loop = 0; uc_loop < pst_bss_dscr->uc_num_supp_rates; uc_loop++)
    {
        if ((pst_bss_dscr->auc_supp_rates[uc_loop] & 0x7F) == uc_rate)
        {
            en_rate_is_supp = OAL_TRUE;
            break;
        }
    }

    return en_rate_is_supp;
}
#endif
/*****************************************************************************
 函 数 名  : hmac_sta_get_user_protocol
 功能描述  : 获取用户的协议模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_sta_get_user_protocol(mac_bss_dscr_stru *pst_bss_dscr, wlan_protocol_enum_uint8  *pen_protocol_mode)
{
    /* 入参保护 */
    if (OAL_PTR_NULL == pst_bss_dscr || OAL_PTR_NULL == pen_protocol_mode)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_get_user_protocol::param null,%d %d.}", pst_bss_dscr, pen_protocol_mode);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_bss_dscr->en_vht_capable)
    {
        *pen_protocol_mode = WLAN_VHT_MODE;
    }
    else if (OAL_TRUE == pst_bss_dscr->en_ht_capable)
    {
        *pen_protocol_mode = WLAN_HT_MODE;
    }
    else
    {
    #ifdef _PRE_WLAN_FEATURE_5G
        if (WLAN_BAND_5G == pst_bss_dscr->st_channel.en_band)            /* 判断是否是5G */
        {
            *pen_protocol_mode = WLAN_LEGACY_11A_MODE;
        }
        else
    #endif /* _PRE_WLAN_FEATURE_5G */
        {
            if (OAL_TRUE == hmac_is_support_11grate(pst_bss_dscr->auc_supp_rates, pst_bss_dscr->uc_num_supp_rates))
            {
                *pen_protocol_mode = WLAN_LEGACY_11G_MODE;
                if (OAL_TRUE == hmac_is_support_11brate(pst_bss_dscr->auc_supp_rates, pst_bss_dscr->uc_num_supp_rates))
                {
                    *pen_protocol_mode = WLAN_MIXED_ONE_11G_MODE;
                }
            }
            else if (OAL_TRUE == hmac_is_support_11brate(pst_bss_dscr->auc_supp_rates, pst_bss_dscr->uc_num_supp_rates))
            {
                *pen_protocol_mode = WLAN_LEGACY_11B_MODE;
            }
            else
            {
                OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_sta_get_user_protocol::get user protocol failed.}");
            }
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_sta_wait_join
 功能描述  : 处理SME发送过来的JOIN_REQ命令，启动JOIN流程，将STA状态设置为WAIT_JOIN
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年4月7日
    作    者   : 
    修改内容   : 删除等待beacon及tbtt中断的操作

*****************************************************************************/
oal_uint32  hmac_sta_wait_join(hmac_vap_stru *pst_hmac_sta, oal_void *pst_msg)
{
    hmac_join_req_stru                  *pst_join_req;
    hmac_join_rsp_stru                   st_join_rsp;
#ifndef _PRE_WLAN_FEATURE_PROXYSTA
    dmac_ctx_set_dtim_tsf_reg_stru      *pst_set_dtim_tsf_reg_params;
    frw_event_mem_stru                  *pst_event_mem;
    frw_event_stru                      *pst_event;
#endif
    oal_uint32                           ul_ret;

    if (OAL_PTR_NULL == pst_hmac_sta || OAL_PTR_NULL == pst_msg)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_wait_join::param null,%d %d.}", pst_hmac_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 1102 P2PSTA共存 todo 更新参数失败的话需要返回而不是继续下发Join动作 */
    ul_ret = hmac_p2p_check_can_enter_state(&(pst_hmac_sta->st_vap_base_info), HMAC_FSM_INPUT_ASOC_REQ);
    if (ul_ret != OAL_SUCC)
    {
        /* 不能进入监听状态，返回设备忙 */
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_sta_wait_join fail,device busy: ul_ret=%d}\r\n", ul_ret);
        return OAL_ERR_CODE_CONFIG_BUSY;
    }

    pst_join_req = (hmac_join_req_stru *)pst_msg;

    /* 更新JOIN REG params 到MIB及MAC寄存器 */
    ul_ret = hmac_sta_update_join_req_params(pst_hmac_sta, pst_join_req);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_join::get hmac_sta_update_join_req_params fail[%d]!}", ul_ret);
        return ul_ret;
    }
    OAM_INFO_LOG3(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                  "{hmac_sta_wait_join::Join AP channel=%d Beacon Period=%d DTIM Period=%d.}",
                  pst_join_req->st_bss_dscr.st_channel.uc_chan_number,
                  pst_join_req->st_bss_dscr.us_beacon_period,
                  pst_join_req->st_bss_dscr.uc_dtim_period);

    /* 非proxy sta模式时，需要将dtim参数配置到dmac*/
#ifndef _PRE_WLAN_FEATURE_PROXYSTA
    /* 抛事件到DMAC, 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_join::event_mem alloc null, size[%d].}", OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
                       OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_sta->st_vap_base_info.uc_chip_id,
                       pst_hmac_sta->st_vap_base_info.uc_device_id,
                       pst_hmac_sta->st_vap_base_info.uc_vap_id);

    pst_set_dtim_tsf_reg_params = (dmac_ctx_set_dtim_tsf_reg_stru *)pst_event->auc_event_data;

    /* 将Ap bssid和tsf REG 设置值保存在事件payload中 */
    pst_set_dtim_tsf_reg_params->ul_dtim_cnt      = pst_join_req->st_bss_dscr.uc_dtim_cnt;
    pst_set_dtim_tsf_reg_params->ul_dtim_period   = pst_join_req->st_bss_dscr.uc_dtim_period;
    pst_set_dtim_tsf_reg_params->us_tsf_bit0      = BIT0;
    oal_memcopy(pst_set_dtim_tsf_reg_params->auc_bssid, pst_hmac_sta->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN);

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
#endif

    st_join_rsp.en_result_code = HMAC_MGMT_SUCCESS;
    /* 切换STA状态到JOIN_COMP */
    hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_STA_JOIN_COMP);

    /* 发送JOIN成功消息给SME */
    hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_JOIN_RSP,(oal_uint8 *)&st_join_rsp);

    OAM_INFO_LOG3(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                   "{hmac_sta_wait_join::Join AP[%08x] HT=%d VHT=%d SUCC.}",
                   MAC_ADDR(pst_join_req->st_bss_dscr.auc_bssid),
                   pst_join_req->st_bss_dscr.en_ht_capable,
                   pst_join_req->st_bss_dscr.en_vht_capable);

    OAM_INFO_LOG3(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                   "{hmac_sta_wait_join::Join AP channel=%d bandwidth=%d Beacon Period=%d SUCC.}",
                   pst_join_req->st_bss_dscr.st_channel.uc_chan_number,
                   pst_hmac_sta->st_vap_base_info.st_channel.en_bandwidth,
                   pst_join_req->st_bss_dscr.us_beacon_period);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_join_rx
 功能描述  : 接收Beacon帧，写mac reg，使能STA的TBTT中断，接收到TBTT中断之后，在hmac_sta_wait_join_misc函数中，
             将状态设置为JOIN_COMP
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
oal_uint32  hmac_sta_wait_join_rx(hmac_vap_stru *pst_hmac_sta, oal_void *p_param)
{
    dmac_wlan_crx_event_stru            *pst_mgmt_rx_event;
    dmac_rx_ctl_stru                    *pst_rx_ctrl;
    mac_rx_ctl_stru                     *pst_rx_info;
    oal_uint8                           *puc_mac_hdr;
    frw_event_mem_stru                  *pst_event_mem;
    frw_event_stru                      *pst_event;
    dmac_ctx_set_dtim_tsf_reg_stru       st_set_dtim_tsf_reg_params = {0};
    oal_uint8                           *puc_tim_elm;
    oal_uint16                           us_rx_len;

    oal_uint8                            auc_bssid[6] = {0};

     if ((OAL_PTR_NULL == pst_hmac_sta) || (OAL_PTR_NULL == p_param))
     {
         OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_wait_join_rx::param null,%d %d.}", pst_hmac_sta, p_param);
         return OAL_ERR_CODE_PTR_NULL;
     }

     pst_mgmt_rx_event   = (dmac_wlan_crx_event_stru *)p_param;
     pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);
     pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
     puc_mac_hdr         = (oal_uint8 *)(pst_rx_info->pul_mac_hdr_start_addr);
     us_rx_len           =  pst_rx_ctrl->st_rx_info.us_frame_len;  /* 消息总长度,不包括FCS */

     /* 在WAIT_JOIN状态下，处理接收到的beacon帧 */
    switch (mac_get_frame_sub_type(puc_mac_hdr))
    {
        case WLAN_FC0_SUBTYPE_BEACON:
        {
            /* 获取Beacon帧中的mac地址，即AP的mac地址 */
            mac_get_bssid(puc_mac_hdr, auc_bssid);

            /* 如果STA保存的AP mac地址与接收beacon帧的mac地址匹配，则更新beacon帧中的DTIM count值到STA本地mib库中 */
            if (0 == oal_memcmp(auc_bssid, pst_hmac_sta->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN))
            {
                //puc_tim_elm = mac_get_tim_ie(puc_mac_hdr, us_rx_len, MAC_TAG_PARAM_OFFSET);
                puc_tim_elm = mac_find_ie(MAC_EID_TIM, puc_mac_hdr + MAC_TAG_PARAM_OFFSET, us_rx_len - MAC_TAG_PARAM_OFFSET);

                /* 从tim IE中提取 DTIM count值,写入到MAC H/W REG中 */
                if ((OAL_PTR_NULL != puc_tim_elm) && (puc_tim_elm[1] >= MAC_MIN_TIM_LEN))
                {
                    pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = puc_tim_elm[3];

                    /* 将dtim_cnt和dtim_period保存在事件payload中 */
                    st_set_dtim_tsf_reg_params.ul_dtim_cnt      = puc_tim_elm[2];
                    st_set_dtim_tsf_reg_params.ul_dtim_period   = puc_tim_elm[3];
                }
                else
                {
                    OAM_WARNING_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                                     "{hmac_sta_wait_join::Do not find Tim ie.}");
                }

                /* 将Ap bssid和tsf REG 设置值保存在事件payload中 */
                oal_memcopy (st_set_dtim_tsf_reg_params.auc_bssid, auc_bssid, WLAN_MAC_ADDR_LEN);
                st_set_dtim_tsf_reg_params.us_tsf_bit0 = BIT0;

                 /* 抛事件到DMAC, 申请事件内存 */
                pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
                if (OAL_PTR_NULL == pst_event_mem)
                {
                    OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_sta_wait_join::pst_event_mem null.}");
                    return OAL_ERR_CODE_PTR_NULL;
                }

                /* 填写事件 */
                pst_event = (frw_event_stru *)pst_event_mem->puc_data;

                FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                                   FRW_EVENT_TYPE_WLAN_CTX,
                                   DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
                                   OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru),
                                   FRW_EVENT_PIPELINE_STAGE_1,
                                   pst_hmac_sta->st_vap_base_info.uc_chip_id,
                                   pst_hmac_sta->st_vap_base_info.uc_device_id,
                                   pst_hmac_sta->st_vap_base_info.uc_vap_id);

                /* 拷贝参数 */
                oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8*)&st_set_dtim_tsf_reg_params, OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));

                /* 分发事件 */
                frw_event_dispatch_event(pst_event_mem);
                FRW_EVENT_FREE(pst_event_mem);
            }
        }
        break;

        case WLAN_FC0_SUBTYPE_ACTION:
        {
            /* do nothing  */
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

   return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_join_timeout
 功能描述  : 在WAIT_JOIN状态下处理超时事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sta_wait_join_timeout(hmac_vap_stru *pst_hmac_sta, oal_void *pst_msg)
{

    hmac_join_rsp_stru      st_join_rsp        = {0};

    if (OAL_PTR_NULL == pst_hmac_sta || OAL_PTR_NULL == pst_msg)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_wait_join_timeout::param null,%d %d.}", pst_hmac_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_sta_wait_join_timeout::join timeout.}");
    /* 进入timeout处理函数表示join没有成功，把join的结果设置为timeout上报给sme */
    st_join_rsp.en_result_code = HMAC_MGMT_TIMEOUT;

    /* 将hmac状态机切换为MAC_VAP_STATE_STA_FAKE_UP */
    hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_STA_FAKE_UP);

    /* 发送超时消息给SME */
    hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_JOIN_RSP, (oal_uint8 *)&st_join_rsp);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_join_misc
 功能描述  : 在WAIT_JOIN状态下处理TBTT中断及其它异常事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sta_wait_join_misc(hmac_vap_stru *pst_hmac_sta, oal_void *pst_msg)
{
    hmac_join_rsp_stru      st_join_rsp;
    hmac_misc_input_stru    *st_misc_input = (hmac_misc_input_stru *)pst_msg;

    if((OAL_PTR_NULL == pst_hmac_sta) ||(OAL_PTR_NULL == pst_msg))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_wait_join_misc::param null,%d %d.}", pst_hmac_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_sta_wait_join_misc::enter func.}");
    switch (st_misc_input->en_type)
    {
        /* 处理TBTT中断  */
        case HMAC_MISC_TBTT:
        {
           /* 接收到TBTT中断，意味着JOIN成功了，所以取消JOIN开始时设置的定时器,发消息通知SME  */
           FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_sta->st_mgmt_timer);

           st_join_rsp.en_result_code = HMAC_MGMT_SUCCESS;

            OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_sta_wait_join_misc::join succ.}");
            /* 切换STA状态到JOIN_COMP */
            hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_STA_JOIN_COMP);

            /* 发送JOIN成功消息给SME */
            hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_JOIN_RSP,(oal_uint8 *)&st_join_rsp);
        }
        break;

        default:
        {
            /* Do Nothing */
        }
        break;
    }
    return OAL_SUCC;
}



/*****************************************************************************
 函 数 名  : hmac_wait_auth_sta
 功能描述  : 处理sme发来的auth req请求。将状态置为WAIT_AUTH_SEQ2 抛事件到dmac发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sta_wait_auth(hmac_vap_stru *pst_hmac_sta, oal_void *pst_msg)
{
    hmac_auth_req_stru  *pst_auth_req;
    oal_netbuf_stru     *pst_auth_frame;
    oal_uint16           us_auth_len;
    mac_tx_ctl_stru     *pst_tx_ctl;
    hmac_user_stru      *pst_hmac_user_ap;
    oal_uint32           ul_ret;

    if (OAL_PTR_NULL == pst_hmac_sta || OAL_PTR_NULL == pst_msg)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_sta_wait_auth::param null,%d %d.}", pst_hmac_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_auth_req = (hmac_auth_req_stru *)pst_msg;
    /* 申请认证帧空间 */
    pst_auth_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

    if (OAL_PTR_NULL == pst_auth_frame)
    {
        OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::puc_auth_frame null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_auth_frame, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_auth_frame), OAL_NETBUF_CB_SIZE());

    OAL_MEMZERO((oal_uint8 *)oal_netbuf_header(pst_auth_frame), MAC_80211_FRAME_LEN);

    /* 组seq = 1 的认证请求帧 */
    us_auth_len = hmac_mgmt_encap_auth_req(pst_hmac_sta, (oal_uint8 *)(OAL_NETBUF_HEADER(pst_auth_frame)));

    if (us_auth_len == 0)
    {
        /* 组帧失败 */
        OAM_WARNING_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::hmac_mgmt_encap_auth_req failed.}");

        oal_netbuf_free(pst_auth_frame);
        hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_STA_FAKE_UP);
        /* TBD: 报系统错误，reset MAC 之类的 */
    }
    else
    {
        oal_netbuf_put(pst_auth_frame, us_auth_len);
        pst_hmac_user_ap = mac_res_get_hmac_user((oal_uint16)pst_hmac_sta->st_vap_base_info.uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_user_ap)
        {
            oal_netbuf_free(pst_auth_frame);
            OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::pst_hmac_user_ap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 为填写发送描述符准备参数 */
        pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_auth_frame);                              /* 获取cb结构体 */
        pst_tx_ctl->us_mpdu_len   = us_auth_len;                                      /* dmac发送需要的mpdu长度 */
        pst_tx_ctl->us_tx_user_idx              = pst_hmac_user_ap->st_user_base_info.us_assoc_id;  /* 发送完成需要获取user结构体 */

        /*如果是WEP，需要将ap的mac地址写入lut*/
        ul_ret = hmac_init_security(&(pst_hmac_sta->st_vap_base_info), pst_hmac_user_ap->st_user_base_info.auc_user_mac_addr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                           "{hmac_sta_wait_auth::hmac_init_security failed[%d].}", ul_ret);
        }

        /* 抛事件让dmac将该帧发送 */
        ul_ret = hmac_tx_mgmt_send_event(&pst_hmac_sta->st_vap_base_info, pst_auth_frame, us_auth_len);
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_auth_frame);
            OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* 更改状态 */
        hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2);

        /* 启动认证超时定时器 */
        pst_hmac_sta->st_mgmt_timetout_param.en_state = MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2;
        pst_hmac_sta->st_mgmt_timetout_param.us_user_index = pst_hmac_user_ap->st_user_base_info.us_assoc_id;
        pst_hmac_sta->st_mgmt_timetout_param.uc_vap_id = pst_hmac_sta->st_vap_base_info.uc_vap_id;
        FRW_TIMER_CREATE_TIMER(&pst_hmac_sta->st_mgmt_timer,
                               hmac_mgmt_timeout_sta,
                               pst_auth_req->us_timeout,
                               &pst_hmac_sta->st_mgmt_timetout_param,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_hmac_sta->st_vap_base_info.ul_core_id);

    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_auth_seq2_rx
 功能描述  : 处理接收到seq num 等于2 的认证帧
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
oal_uint32  hmac_sta_wait_auth_seq2_rx(hmac_vap_stru *pst_sta, oal_void *pst_msg)
{
    dmac_wlan_crx_event_stru    *pst_crx_event;
    hmac_rx_ctl_stru            *pst_rx_ctrl;                    /* 每一个MPDU的控制信息 */
    oal_uint8                   *puc_mac_hdr;
    oal_uint16                   us_auth_frame_len = 0;
    oal_uint16                   us_auth_alg;
    oal_netbuf_stru             *pst_auth_frame    = 0;
    hmac_user_stru              *pst_hmac_user_ap;
    hmac_auth_rsp_stru           st_auth_rsp       = {{0},};
    mac_tx_ctl_stru             *pst_tx_ctl;
    oal_uint32                   ul_ret;

    if (OAL_PTR_NULL == pst_sta || OAL_PTR_NULL == pst_msg)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_sta_wait_auth_seq2_rx::param null,%d %d.}", pst_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_crx_event  = (dmac_wlan_crx_event_stru *)pst_msg;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf);                    /* 每一个MPDU的控制信息 */
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    if (WLAN_FC0_SUBTYPE_AUTH != mac_get_frame_sub_type(puc_mac_hdr) ||
        WLAN_AUTH_TRASACTION_NUM_TWO != mac_get_auth_seq_num(puc_mac_hdr))
    {
        return OAL_SUCC;
    }

    /* AUTH alg CHECK*/
    us_auth_alg = mac_get_auth_alg(puc_mac_hdr);
    if ((pst_sta->en_auth_mode != us_auth_alg) &&
        (WLAN_WITP_AUTH_AUTOMATIC != pst_sta->en_auth_mode))
    {
        OAM_WARNING_LOG2(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                         "{hmac_sta_wait_auth_seq2_rx::rcv unexpected auth alg[%d/%d].}", us_auth_alg, pst_sta->en_auth_mode);
    }

    if (MAC_SUCCESSFUL_STATUSCODE != mac_get_auth_status(puc_mac_hdr))
    {
        /* : 收到seq = 2 的认证帧，并且正常处理，取消定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_sta->st_mgmt_timer);

        st_auth_rsp.us_status_code = mac_get_auth_status(puc_mac_hdr);

        /* 上报给SME认证成功 */
        hmac_send_rsp_to_sme_sta(pst_sta, HMAC_SME_AUTH_RSP, (oal_uint8 *)&st_auth_rsp);
        return OAL_SUCC;
    }

    if (WLAN_WITP_AUTH_OPEN_SYSTEM == us_auth_alg)
    {
        /* : 收到seq = 2 的认证帧，并且正常处理，取消定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_sta->st_mgmt_timer);

        /* 将状态更改为AUTH_COMP */
        hmac_fsm_change_state(pst_sta, MAC_VAP_STATE_STA_AUTH_COMP);
        st_auth_rsp.us_status_code = HMAC_MGMT_SUCCESS;

        /* 上报给SME认证成功 */
        hmac_send_rsp_to_sme_sta(pst_sta, HMAC_SME_AUTH_RSP, (oal_uint8 *)&st_auth_rsp);
        return OAL_SUCC;
    }

    else if (WLAN_WITP_AUTH_SHARED_KEY == us_auth_alg)
    {
        /* 准备seq = 3的认证帧 */
        pst_auth_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

        if(OAL_PTR_NULL == pst_auth_frame)
        {
            /* TBD: 复位mac */
            OAM_ERROR_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::pst_auth_frame null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        OAL_MEM_NETBUF_TRACE(pst_auth_frame, OAL_TRUE);

        OAL_MEMZERO(oal_netbuf_cb(pst_auth_frame), OAL_NETBUF_CB_SIZE());

        us_auth_frame_len = hmac_mgmt_encap_auth_req_seq3(pst_sta, (oal_uint8 *)OAL_NETBUF_HEADER(pst_auth_frame), puc_mac_hdr);
        oal_netbuf_put(pst_auth_frame, us_auth_frame_len);

        pst_hmac_user_ap = mac_res_get_hmac_user((oal_uint16)pst_sta->st_vap_base_info.uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_user_ap)
        {
            oal_netbuf_free(pst_auth_frame);
            OAM_ERROR_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::pst_hmac_user_ap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 填写发送和发送完成需要的参数 */
        pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_auth_frame);
        pst_tx_ctl->us_mpdu_len   = us_auth_frame_len;                                 /* 发送需要帧长度 */
        pst_tx_ctl->us_tx_user_idx              = pst_hmac_user_ap->st_user_base_info.us_assoc_id;   /* 发送完成要获取用户 */

        /* 抛事件给dmac发送 */
        ul_ret = hmac_tx_mgmt_send_event(&pst_sta->st_vap_base_info, pst_auth_frame, us_auth_frame_len);
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_auth_frame);
            OAM_WARNING_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_wait_auth_sta::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* : 收到seq = 2 的认证帧，并且正常处理，取消定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_sta->st_mgmt_timer);

        /* 更改状态为MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4，并启动定时器 */
        hmac_fsm_change_state(pst_sta, MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4);

        FRW_TIMER_CREATE_TIMER(&pst_sta->st_mgmt_timer,
                               hmac_mgmt_timeout_sta,
                               pst_sta->st_mgmt_timer.ul_timeout,
                               &pst_sta->st_mgmt_timetout_param,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_sta->st_vap_base_info.ul_core_id);
        return OAL_SUCC;
    }
    else
    {
        /* : 收到seq = 2 的认证帧，并且正常处理，取消定时器 */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_sta->st_mgmt_timer);

        /* 接收到AP 回复的auth response 中支持认证算法当前不支持的情况下，status code 却是SUCC,
            认为认证成功，并且继续出发关联 */
        OAM_WARNING_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                         "{hmac_sta_wait_auth_seq2_rx::AP's auth_alg [%d] not support!}", us_auth_alg);

        /* 将状态更改为AUTH_COMP */
        hmac_fsm_change_state(pst_sta, MAC_VAP_STATE_STA_AUTH_COMP);
        st_auth_rsp.us_status_code = HMAC_MGMT_SUCCESS;

        /* 上报给SME认证成功 */
        hmac_send_rsp_to_sme_sta(pst_sta, HMAC_SME_AUTH_RSP, (oal_uint8 *)&st_auth_rsp);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_auth_seq4_rx
 功能描述  : 处理收到seq = 4 的认证帧
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
oal_uint32  hmac_sta_wait_auth_seq4_rx(hmac_vap_stru *pst_sta, oal_void *p_msg)
{
    dmac_wlan_crx_event_stru    *pst_crx_event;
    hmac_rx_ctl_stru            *pst_rx_ctrl; /* 每一个MPDU的控制信息 */
    oal_uint8                   *puc_mac_hdr;
    oal_uint16                   us_auth_status = MAC_UNSPEC_FAIL;
    hmac_auth_rsp_stru           st_auth_rsp    = {{0},};

    if (OAL_PTR_NULL == p_msg || OAL_PTR_NULL == pst_sta)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_sta_wait_auth_seq2_rx::param null,%d %d.}", p_msg, p_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_crx_event  = (dmac_wlan_crx_event_stru *)p_msg;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf); /* 每一个MPDU的控制信息 */
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    if (WLAN_FC0_SUBTYPE_AUTH == mac_get_frame_sub_type(puc_mac_hdr))
    {
        us_auth_status = mac_get_auth_status(puc_mac_hdr);

        if((WLAN_AUTH_TRASACTION_NUM_FOUR == mac_get_auth_seq_num(puc_mac_hdr)) &&
           (MAC_SUCCESSFUL_STATUSCODE == us_auth_status))
        {
            /* 接收到seq = 4 且状态位为succ 取消定时器 */
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_sta->st_mgmt_timer);

            st_auth_rsp.us_status_code = HMAC_MGMT_SUCCESS;

            /* 更改sta状态为MAC_VAP_STATE_STA_AUTH_COMP */
            hmac_fsm_change_state(pst_sta, MAC_VAP_STATE_STA_AUTH_COMP);
            OAM_INFO_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_sta_wait_auth_seq4_rx::auth succ.}");
            /* 将认证结果上报SME */
            hmac_send_rsp_to_sme_sta(pst_sta, HMAC_SME_AUTH_RSP, (oal_uint8 *)&st_auth_rsp);
        }
        else
        {
            OAM_WARNING_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_sta_wait_auth_seq4_rx::transaction num.status[%d]}", \
              us_auth_status);
            /* 等待定时器超时 */
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_sta_wait_asoc
 功能描述  : 在AUTH_COMP状态接收到SME发过来的ASOC_REQ请求，将STA状态设置为WAIT_ASOC,
             抛事件给DMAC，发送Asoc_req_frame
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
oal_uint32  hmac_sta_wait_asoc(hmac_vap_stru *pst_sta, oal_void *pst_msg)
{
    hmac_asoc_req_stru         *pst_hmac_asoc_req;
    oal_netbuf_stru            *pst_asoc_req_frame;
    mac_tx_ctl_stru            *pst_tx_ctl;
    hmac_user_stru             *pst_hmac_user_ap;
    oal_uint32                  ul_asoc_frame_len;
    oal_uint32                  ul_ret;

    if ((OAL_PTR_NULL == pst_sta) || (OAL_PTR_NULL == pst_msg))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::param null,%d %d.}", pst_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_asoc_req = (hmac_asoc_req_stru *)pst_msg;

    pst_asoc_req_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

    if (OAL_PTR_NULL == pst_asoc_req_frame)
    {
        OAM_ERROR_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::pst_asoc_req_frame null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_MEM_NETBUF_TRACE(pst_asoc_req_frame, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_asoc_req_frame), OAL_NETBUF_CB_SIZE());

    /* 将mac header清零 */
    OAL_MEMZERO((oal_uint8 *)oal_netbuf_header(pst_asoc_req_frame), MAC_80211_FRAME_LEN);

    /* 组帧 (Re)Assoc_req_Frame */
    ul_asoc_frame_len = hmac_mgmt_encap_asoc_req_sta(pst_sta,(oal_uint8 *)(OAL_NETBUF_HEADER(pst_asoc_req_frame)));
    oal_netbuf_put(pst_asoc_req_frame, ul_asoc_frame_len);

    if (0 == ul_asoc_frame_len)
    {
        OAM_WARNING_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::hmac_mgmt_encap_asoc_req_sta null.}");
        oal_netbuf_free(pst_asoc_req_frame);

        return OAL_FAIL;
    }

    if (OAL_PTR_NULL != pst_sta->puc_asoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_sta->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_sta->puc_asoc_req_ie_buff = OAL_PTR_NULL;
    }

    if(OAL_UNLIKELY(ul_asoc_frame_len < OAL_ASSOC_REQ_IE_OFFSET))
    {
        OAM_ERROR_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::invalid ul_asoc_req_ie_len[%u].}", ul_asoc_frame_len);
        oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)oal_netbuf_header(pst_asoc_req_frame),(oal_uint16)ul_asoc_frame_len, OAM_OTA_TYPE_80211_FRAME);
        oal_netbuf_free(pst_asoc_req_frame);
        return OAL_FAIL;
    }

    /*Should we change the ie buff from local mem to netbuf ?*/
    /* 此处申请的内存，只在上报给内核后释放 */
    pst_sta->ul_asoc_req_ie_len = (pst_sta->bit_reassoc_flag) ? (ul_asoc_frame_len - OAL_ASSOC_REQ_IE_OFFSET - OAL_MAC_ADDR_LEN) :
                                   (ul_asoc_frame_len - OAL_ASSOC_REQ_IE_OFFSET);
    pst_sta->puc_asoc_req_ie_buff = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(pst_sta->ul_asoc_req_ie_len), OAL_TRUE);
    if (OAL_PTR_NULL == pst_sta->puc_asoc_req_ie_buff)
    {
        OAM_ERROR_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::puc_asoc_req_ie_buff null,alloc %u bytes failed}",
                        (oal_uint16)(pst_sta->ul_asoc_req_ie_len));
        oal_netbuf_free(pst_asoc_req_frame);
        return OAL_FAIL;
    }

    if (pst_sta->bit_reassoc_flag)
    {
        oal_memcopy(pst_sta->puc_asoc_req_ie_buff, OAL_NETBUF_HEADER(pst_asoc_req_frame) + OAL_ASSOC_REQ_IE_OFFSET + OAL_MAC_ADDR_LEN, pst_sta->ul_asoc_req_ie_len);
    }
    else
    {
        oal_memcopy(pst_sta->puc_asoc_req_ie_buff, OAL_NETBUF_HEADER(pst_asoc_req_frame) + OAL_ASSOC_REQ_IE_OFFSET, pst_sta->ul_asoc_req_ie_len);
    }

    pst_hmac_user_ap = (hmac_user_stru *)mac_res_get_hmac_user((oal_uint16)pst_sta->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_user_ap)
    {
        OAM_ERROR_LOG0(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::pst_hmac_user_ap null.}");
        oal_netbuf_free(pst_asoc_req_frame);
        OAL_MEM_FREE(pst_sta->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_sta->puc_asoc_req_ie_buff = OAL_PTR_NULL;

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_asoc_req_frame);

    pst_tx_ctl->us_mpdu_len   = (oal_uint16)ul_asoc_frame_len;
    pst_tx_ctl->us_tx_user_idx              = pst_hmac_user_ap->st_user_base_info.us_assoc_id;

    /* 抛事件让DMAC将该帧发送 */
    ul_ret = hmac_tx_mgmt_send_event(&(pst_sta->st_vap_base_info), pst_asoc_req_frame, (oal_uint16)ul_asoc_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_asoc_req_frame);
        OAL_MEM_FREE(pst_sta->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_sta->puc_asoc_req_ie_buff = OAL_PTR_NULL;

        OAM_WARNING_LOG1(pst_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 更改状态 */
    hmac_fsm_change_state(pst_sta, MAC_VAP_STATE_STA_WAIT_ASOC);

    /* 启动关联超时定时器, 为对端ap分配一个定时器，如果超时ap没回asoc rsp则启动超时处理 */
    pst_sta->st_mgmt_timetout_param.en_state = MAC_VAP_STATE_STA_WAIT_ASOC;
    pst_sta->st_mgmt_timetout_param.us_user_index = pst_hmac_user_ap->st_user_base_info.us_assoc_id;
    pst_sta->st_mgmt_timetout_param.uc_vap_id = pst_sta->st_vap_base_info.uc_vap_id;

    FRW_TIMER_CREATE_TIMER(&(pst_sta->st_mgmt_timer),
                           hmac_mgmt_timeout_sta,
                           pst_hmac_asoc_req->us_assoc_timeout,
                           &(pst_sta->st_mgmt_timetout_param),
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_sta->st_vap_base_info.ul_core_id);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_P2P

/*****************************************************************************
 函 数 名  : hmac_p2p_listen_comp_cb
 功能描述  : P2P 监听超时处理函数
 输入参数  : void *p_arg
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_p2p_listen_comp_cb(void *p_arg)
{
    hmac_vap_stru                      *pst_hmac_vap;
    mac_device_stru                    *pst_mac_device;
    hmac_scan_record_stru              *pst_scan_record;

    pst_scan_record = (hmac_scan_record_stru *)p_arg;

    /* 判断listen完成时的状态 */
    if (MAC_SCAN_SUCCESS != pst_scan_record->en_scan_rsp_status)
    {
        OAM_WARNING_LOG1(0, OAM_SF_P2P, "{hmac_p2p_listen_comp_cb::listen failed, listen rsp status: %d.}",
                         pst_scan_record->en_scan_rsp_status);
    }

    pst_hmac_vap   = mac_res_get_hmac_vap(pst_scan_record->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_P2P, "{hmac_p2p_listen_comp_cb::pst_hmac_vap is null:vap_id %d.}",
                                 pst_scan_record->uc_vap_id);
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_scan_record->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_P2P, "{hmac_p2p_listen_comp_cb::pst_mac_device is null:vap_id %d.}",
                                 pst_scan_record->uc_device_id);
        return;
    }

    /* ：解决wifi 驱动不上报监听结束问题。
      此处上报ull_cookie不加1，因为在邋remain_on_channel下发时刻便已+1 */
    if (pst_scan_record->ull_cookie == pst_mac_device->st_p2p_info.ull_last_roc_id)
    {
        /* 状态机调用: hmac_p2p_listen_timeout */
        if (OAL_SUCC != hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_LISTEN_TIMEOUT, &(pst_hmac_vap->st_vap_base_info)))
            {
            OAM_WARNING_LOG0(0,OAM_SF_P2P,"{hmac_p2p_listen_comp_cb::hmac_fsm_call_func_sta fail.}");
            }
    }
    else
    {
        OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                        "{hmac_p2p_listen_comp_cb::ignore listen complete.scan_report_cookie[%x], current_listen_cookie[%x], ull_last_roc_id[%x].}",
                        pst_scan_record->ull_cookie,
                        pst_mac_device->st_scan_params.ull_cookie,
                        pst_mac_device->st_p2p_info.ull_last_roc_id);
    }


    return;
}

/*****************************************************************************
 函 数 名  : hmac_cfg80211_prepare_listen_req_param
 功能描述  : 准备p2p监听请求的对应参数
 输入参数  : mac_scan_req_stru *pst_scan_params,        扫描参数
             oal_int8 *puc_param,                       p2p监听参数
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_cfg80211_prepare_listen_req_param(mac_scan_req_stru *pst_scan_params, oal_int8 *puc_param)
{
    mac_remain_on_channel_param_stru *pst_remain_on_channel;
    mac_channel_stru                 *pst_channel_tmp;

    pst_remain_on_channel = (mac_remain_on_channel_param_stru *)puc_param;

    OAL_MEMZERO(pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    /* 设置监听信道信息到扫描参数中 */
    pst_scan_params->ast_channel_list[0].en_band        = pst_remain_on_channel->en_band;
    pst_scan_params->ast_channel_list[0].en_bandwidth   = pst_remain_on_channel->en_listen_channel_type;
    pst_scan_params->ast_channel_list[0].uc_chan_number = pst_remain_on_channel->uc_listen_channel;
    pst_scan_params->ast_channel_list[0].uc_idx         = 0;
    pst_channel_tmp = &(pst_scan_params->ast_channel_list[0]);
    if (OAL_SUCC != mac_get_channel_idx_from_num(pst_channel_tmp->en_band, pst_channel_tmp->uc_chan_number, &(pst_channel_tmp->uc_idx)))
    {
        OAM_WARNING_LOG2(0,OAM_SF_P2P,"{hmac_cfg80211_prepare_listen_req_param::mac_get_channel_idx_from_num fail.band[%u]  channel[%u]}",pst_channel_tmp->en_band, pst_channel_tmp->uc_chan_number);
    }

    /* 设置其它监听参数 */
    pst_scan_params->uc_max_scan_count_per_channel      = 1;
    pst_scan_params->uc_channel_nums = 1;
    pst_scan_params->uc_scan_func    = MAC_SCAN_FUNC_P2P_LISTEN;
    pst_scan_params->us_scan_time    = (oal_uint16)pst_remain_on_channel->ul_listen_duration;
    pst_scan_params->p_fn_cb         = hmac_p2p_listen_comp_cb;
    pst_scan_params->ull_cookie      = pst_remain_on_channel->ull_cookie;

    return;
}

/*****************************************************************************
 函 数 名  : hmac_p2p_listen_timeout
 功能描述  : P2P_DEVICE 监听超时
 输入参数  : hmac_vap_stru *pst_hmac_vap_sta
             oal_void *p_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月24日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_p2p_listen_timeout(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param)
{
    mac_device_stru                    *pst_mac_device;
    hmac_vap_stru                      *pst_hmac_vap;
    mac_vap_stru                       *pst_mac_vap;

    pst_mac_vap    = (mac_vap_stru *)p_param;
    pst_hmac_vap   = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG1(0,OAM_SF_P2P,"{hmac_p2p_listen_timeout::mac_res_get_hmac_vap fail.vap_id[%u]!}",pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0,OAM_SF_P2P,"{hmac_p2p_listen_timeout::mac_res_get_dev fail.device_id[%u]!}",pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                  "{hmac_p2p_listen_timeout::current pst_mac_vap channel is [%d] state[%d]}",
                  pst_mac_vap->st_channel.uc_chan_number,
                  pst_hmac_vap->st_vap_base_info.en_vap_state);

    OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                  "{hmac_p2p_listen_timeout::next pst_mac_vap channel is [%d] state[%d]}",
                  pst_mac_vap->st_channel.uc_chan_number,
                  pst_mac_device->st_p2p_info.en_last_vap_state);

    /* 由于P2P0 和P2P_CL 共用vap 结构体，监听超时，返回监听前保存的状态 */
    /*  p2p listen同步vap状态与背景扫描冲突，不同步到dmac */
    mac_vap_state_change(&pst_hmac_vap->st_vap_base_info, pst_mac_device->st_p2p_info.en_last_vap_state);
    hmac_set_rx_filter_value(&pst_hmac_vap->st_vap_base_info);

    /* 3.1 抛事件到WAL ，上报监听结束 */
    hmac_p2p_send_listen_expired_to_host(pst_hmac_vap);

    /* 3.2 抛事件到DMAC ，返回监听信道 */
    hmac_p2p_send_listen_expired_to_device(pst_hmac_vap);

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : hmac_p2p_listen_timeout_fn
 功能描述  : P2P 监听超时处理函数
 输入参数  : void *p_arg
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月24日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_p2p_listen_timeout_fn(void *p_arg)
{
    hmac_vap_stru                      *pst_hmac_vap;
    mac_vap_stru                       *pst_mac_vap;

    pst_mac_vap    = (mac_vap_stru *)p_arg;
    pst_hmac_vap   = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    /* 状态机调用: hmac_p2p_listen_timeout */
    hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_LISTEN_TIMEOUT, pst_mac_vap);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : hmac_p2p_remain_on_channel
 功能描述  : 设置device 到指定信道监听，并设置监听超时定时器
             如果是从up 状态进入listen ，则返回up
             如果是从scan complete 状态进入，则返回scan complete
 输入参数  : hmac_vap_stru *pst_hmac_vap_sta
             oal_void *p_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月24日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_p2p_remain_on_channel(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param)
{
    mac_device_stru                     *pst_mac_device;
    mac_vap_stru                        *pst_mac_vap;
    mac_remain_on_channel_param_stru    *pst_remain_on_channel;
    mac_scan_req_stru                    st_scan_params;
    oal_uint32                           ul_ret;

    pst_remain_on_channel = (mac_remain_on_channel_param_stru*)p_param;

    pst_mac_vap     = mac_res_get_mac_vap(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(0,OAM_SF_P2P,"{hmac_p2p_remain_on_channel::mac_res_get_mac_vap fail.vap_id[%u]!}",pst_hmac_vap_sta->st_vap_base_info.uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_p2p_listen_timeout::pst_mac_device[%d](%p) null!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }


    /*  设置P2P 监听超时定时器,
        P2P处于Listen状态下无法下发监听命令，导致Listen状态下不能重新出发监听，无法与商用设备关联 */
    if (MAC_VAP_STATE_STA_LISTEN == pst_hmac_vap_sta->st_vap_base_info.en_vap_state)
    {
        hmac_p2p_send_listen_expired_to_host(pst_hmac_vap_sta);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P,
                        "{hmac_p2p_remain_on_channel::listen nested, send remain on channel expired to host!curr_state[%d]\r\n}",
                        pst_hmac_vap_sta->st_vap_base_info.en_vap_state);
    }

    /* 修改P2P_DEVICE 状态为监听状态 */
    /*  P2P监听状态与背景扫描时DMAC的pause状态冲突，P2P_LISTEN状态不同步到DMAC去，DMAC不再使用P2P_LISTEN状态 */
    mac_vap_state_change((mac_vap_stru *)&pst_hmac_vap_sta->st_vap_base_info, MAC_VAP_STATE_STA_LISTEN);
    hmac_set_rx_filter_value((mac_vap_stru *)&pst_hmac_vap_sta->st_vap_base_info);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_P2P,
                  "{hmac_p2p_remain_on_channel : get in listen state!last_state %d, channel %d, duration %d, curr_state %d}\r\n",
                  pst_mac_device->st_p2p_info.en_last_vap_state,
                  pst_remain_on_channel->uc_listen_channel,
                  pst_remain_on_channel->ul_listen_duration,
                  pst_hmac_vap_sta->st_vap_base_info.en_vap_state);

    /* 准备监听参数 */
    hmac_cfg80211_prepare_listen_req_param(&st_scan_params, (oal_int8 *)pst_remain_on_channel);

    /* 调用扫描入口，准备进行监听动作，不管监听动作执行成功或失败，都返回监听成功 */
    /* 状态机调用: hmac_scan_proc_scan_req_event */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap_sta, HMAC_FSM_INPUT_SCAN_REQ, (oal_void *)(&st_scan_params));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_p2p_remain_on_channel::hmac_fsm_call_func_sta fail[%d].}", ul_ret);
    }

    return OAL_SUCC;
}


#endif /* _PRE_WLAN_FEATURE_P2P */

#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_P2P)

/*****************************************************************************
 函 数 名  : hmac_sta_not_up_rx_mgmt
 功能描述  : P2P_DEVICE 在监听状态接收到管理帧处理，HS2.0查询过程的ACTION上报(原函数名为hmac_p2p_listen_rx_mgmt)
 输入参数  : hmac_vap_stru  *pst_hmac_vap_sta,
             oal_void       *p_param
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年11月13日
    作    者   :  
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  hmac_sta_not_up_rx_mgmt(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param)
{
    dmac_wlan_crx_event_stru   *pst_mgmt_rx_event;
    mac_vap_stru               *pst_mac_vap;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_mac_hdr;
    oal_uint8                   uc_mgmt_frm_type;

    if (OAL_PTR_NULL == pst_hmac_vap_sta || OAL_PTR_NULL == p_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_sta_not_up_rx_mgmt::PTR_NULL, hmac_vap_addr[%p], param[%p].}",
                       pst_hmac_vap_sta, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap        = &(pst_hmac_vap_sta->st_vap_base_info);
    pst_mgmt_rx_event  =  (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_info        =  (mac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);
    puc_mac_hdr        =  (oal_uint8 *)(pst_rx_info->pul_mac_hdr_start_addr);
    if(OAL_PTR_NULL == puc_mac_hdr)
    {
        OAM_ERROR_LOG3(pst_rx_info->uc_mac_vap_id, OAM_SF_RX, "{hmac_sta_not_up_rx_mgmt::puc_mac_hdr null, vap_id %d,us_frame_len %d, uc_mac_header_len %d}",
                       pst_rx_info->bit_vap_id,
                       pst_rx_info->us_frame_len,
                       pst_rx_info->uc_mac_header_len);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* STA在NOT UP状态下接收到各种管理帧处理*/
    uc_mgmt_frm_type = mac_get_frame_sub_type(puc_mac_hdr);
    switch (uc_mgmt_frm_type)
    {
        /* 判断接收到的管理帧类型*/
        case WLAN_FC0_SUBTYPE_PROBE_REQ:
            #ifdef _PRE_WLAN_FEATURE_P2P
            /* 判断为P2P设备,则上报probe req帧到wpa_supplicant*/
            if (!IS_LEGACY_VAP(pst_mac_vap))
            {
                hmac_rx_mgmt_send_to_host(pst_hmac_vap_sta, pst_mgmt_rx_event->pst_netbuf);
            }
            break;
            #endif
        case WLAN_FC0_SUBTYPE_ACTION:
            /* 如果是Action 帧，则直接上报wpa_supplicant*/
            hmac_rx_mgmt_send_to_host(pst_hmac_vap_sta, pst_mgmt_rx_event->pst_netbuf);
            break;
        default:
            break;
    }
    return OAL_SUCC;
}
#endif /* _PRE_WLAN_FEATURE_HS20 and _PRE_WLAN_FEATURE_P2P */

/*****************************************************************************
 函 数 名  : hmac_update_vht_opern_ie_sta
 功能描述  : STA更新接收asoc_rsp帧中的Vht operation ie信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_update_vht_opern_ie_sta(
                    mac_vap_stru            *pst_mac_vap,
                    hmac_user_stru          *pst_hmac_user,
                    oal_uint8               *puc_payload,
                    oal_uint16               us_msg_idx)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ASSOC, "{hmac_update_vht_opern_ie_sta::param null,%d %d %d.}", pst_mac_vap, pst_hmac_user, puc_payload);
        return HMAC_NO_CHANGE;
    }

    /* 支持11ac，才进行后续的处理 */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return HMAC_NO_CHANGE;
    }

    return hmac_ie_proc_vht_opern_ie(pst_mac_vap, puc_payload, &(pst_hmac_user->st_user_base_info));
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_update_edca_params_machw
 功能描述  : 当与STA关联的AP不是QoS的时候，STA默认采用VO策略发送数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_sta_up_update_edca_params_machw(
                      hmac_vap_stru                          *pst_hmac_sta,
                      mac_wmm_set_param_type_enum_uint8      en_type)
{
    frw_event_mem_stru                       *pst_event_mem;
    frw_event_stru                           *pst_event;
    dmac_ctx_sta_asoc_set_edca_reg_stru       st_asoc_set_edca_reg_param = {0};

    /* 抛事件到dmac写寄存器 */
    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_update_vht_opern_ie_sta::event_mem alloc null, size[%d].}",
                OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_asoc_set_edca_reg_param.uc_vap_id = pst_hmac_sta->st_vap_base_info.uc_vap_id;
    st_asoc_set_edca_reg_param.en_set_param_type = en_type;

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                   FRW_EVENT_TYPE_WLAN_CTX,
                   DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG,
                   OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru),
                   FRW_EVENT_PIPELINE_STAGE_1,
                   pst_hmac_sta->st_vap_base_info.uc_chip_id,
                   pst_hmac_sta->st_vap_base_info.uc_device_id,
                   pst_hmac_sta->st_vap_base_info.uc_vap_id);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (MAC_WMM_SET_PARAM_TYPE_DEFAULT != en_type)
    {
        oal_memcopy((oal_uint8 *)&st_asoc_set_edca_reg_param.ast_wlan_mib_qap_edac, (oal_uint8 *)&pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac, (OAL_SIZEOF(wlan_mib_Dot11QAPEDCAEntry_stru) * WLAN_WME_AC_BUTT));
    }
#endif

    /* 拷贝参数 */
    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)&st_asoc_set_edca_reg_param, OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_update_edca_params_mib
 功能描述  : STA更新每一个AC的参数
 输入参数  : pst_hmac_sta:处于sta模式的vap
             puc_payload :帧体
 输出参数  : 无
 返 回 值  : OAL_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_sta_up_update_edca_params_mib(hmac_vap_stru  *pst_hmac_sta, oal_uint8  *puc_payload)
{
    oal_uint8               uc_aifsn;
    oal_uint8               uc_aci;
    oal_uint8               uc_ecwmin;
    oal_uint8               uc_ecwmax;
    oal_uint16              us_txop_limit;
    oal_bool_enum_uint8     en_acm;
    /******** AC Parameters Record Format *********/
    /* ------------------------------------------ */
    /* |     1     |       1       |      2     | */
    /* ------------------------------------------ */
    /* | ACI/AIFSN | ECWmin/ECWmax | TXOP Limit | */
    /* ------------------------------------------ */

    /************* ACI/AIFSN Field ***************/
    /*     ---------------------------------- */
    /* bit |   4   |  1  |  2  |    1     |   */
    /*     ---------------------------------- */
    /*     | AIFSN | ACM | ACI | Reserved |   */
    /*     ---------------------------------- */

    uc_aifsn = puc_payload[0] & MAC_WMM_QOS_PARAM_AIFSN_MASK;
    en_acm   = (puc_payload[0] & BIT4)?OAL_TRUE:OAL_FALSE;
    uc_aci   = (puc_payload[0] >> MAC_WMM_QOS_PARAM_ACI_BIT_OFFSET) & MAC_WMM_QOS_PARAM_ACI_MASK;

    /* ECWmin/ECWmax Field */
    /*     ------------------- */
    /* bit |   4    |   4    | */
    /*     ------------------- */
    /*     | ECWmin | ECWmax | */
    /*     ------------------- */
    uc_ecwmin = (puc_payload[1] & MAC_WMM_QOS_PARAM_ECWMIN_MASK);
    uc_ecwmax = ((puc_payload[1] & MAC_WMM_QOS_PARAM_ECWMAX_MASK) >> MAC_WMM_QOS_PARAM_ECWMAX_BIT_OFFSET);

    /* 在mib库中和寄存器里保存的TXOP值都是以us为单位的，但是传输的时候是以32us为
       单位进行传输的，因此在解析的时候需要将解析到的值乘以32
    */
    us_txop_limit = puc_payload[2] |
                    ((puc_payload[3] & MAC_WMM_QOS_PARAM_TXOPLIMIT_MASK) << MAC_WMM_QOS_PARAM_BIT_NUMS_OF_ONE_BYTE);
    us_txop_limit = (oal_uint16)(us_txop_limit << MAC_WMM_QOS_PARAM_TXOPLIMIT_SAVE_TO_TRANS_TIMES);

    /* 更新相应的MIB库信息 */
    if (uc_aci < WLAN_WME_AC_BUTT)
    {
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].ul_dot11QAPEDCATableIndex     = uc_aci + 1;
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].ul_dot11QAPEDCATableCWmin     = uc_ecwmin;
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].ul_dot11QAPEDCATableCWmax     = uc_ecwmax;
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].ul_dot11QAPEDCATableAIFSN     = uc_aifsn;
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].ul_dot11QAPEDCATableTXOPLimit = us_txop_limit;
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[uc_aci].en_dot11QAPEDCATableMandatory = en_acm;
    }
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_process_erp_ie
 功能描述  : STA接收到beacon帧或者关联响应帧后， 对ERP信息元素进行处理，
             保存use protection信息到user结构体中
 输入参数  : puc_payload         :帧体
             ul_msg_len          :帧体长度
             us_info_elem_offset :当前指向的帧体位置
             pst_hmac_user       :user结构体，保存AP相关信息
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_sta_up_process_erp_ie(
                    oal_uint8               *puc_payload,
                    oal_uint16               us_msg_len,
                    oal_uint16               us_info_elem_offset,
                    hmac_user_stru          *pst_hmac_user)
{
    oal_uint16              us_msg_offset;
    mac_erp_params_stru    *pst_erp_params;

    /* 设置偏移 */
    us_msg_offset = us_info_elem_offset;

    /************************ ERP Element *************************************
    --------------------------------------------------------------------------
    |EID  |Len  |NonERP_Present|Use_Protection|Barker_Preamble_Mode|Reserved|
    --------------------------------------------------------------------------
    |B0-B7|B0-B7|B0            |B1            |B2                  |B3-B7   |
    --------------------------------------------------------------------------
    ***************************************************************************/

    while (us_msg_offset < us_msg_len)
    {
        /* 判断当前的ie是否是ERP ie，如果不是，继续检查下一个ie，如果是，保存use protection 信息 */
        if (MAC_EID_ERP == puc_payload[us_msg_offset])
        {
            us_msg_offset += MAC_IE_HDR_LEN;
            pst_erp_params = (mac_erp_params_stru *)(&puc_payload[us_msg_offset]);

            /* 保存use_protect 信息 */
            pst_hmac_user->st_hmac_cap_info.bit_erp_use_protect = pst_erp_params->bit_use_protection;
            /*保存preamble mode*/
            mac_user_set_barker_preamble_mode(&pst_hmac_user->st_user_base_info, pst_erp_params->bit_preamble_mode);
            return ;
        }

        us_msg_offset += (puc_payload[us_msg_offset + 1] + MAC_IE_HDR_LEN);
    }

}

#if 0
/*****************************************************************************
 函 数 名  : hmac_sta_up_process_ht_operation_ie
 功能描述  : STA接收到beacon帧或者关联响应帧后， 对HT operation信息元素进行处理，
             保存AP HT相关能力信息到user结构体中
 输入参数  : puc_payload         :帧体
             ul_msg_len          :帧体长度
             us_info_elem_offset :当前指向的帧体位置
             pst_hmac_user       :user结构体，保存AP相关信息
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_sta_up_process_ht_operation_ie(
                    oal_uint8               *puc_payload,
                    oal_uint16               us_msg_len,
                    oal_uint16               us_info_elem_offset,
                    hmac_user_stru          *pst_hmac_user)
{
    oal_uint16              us_msg_offset;
    mac_ht_opern_stru      *pst_ht_opern;

    /* 设置偏移 */
    us_msg_offset = us_info_elem_offset;

    /************************ HT Operation Element *************************************
      ----------------------------------------------------------------------
      |EID |Length |PrimaryChannel |HT Operation Information |Basic MCS Set|
      ----------------------------------------------------------------------
      |1   |1      |1              |5                        |16           |
      ----------------------------------------------------------------------
    ***************************************************************************/

    /************************ HT Information Field ****************************
     |--------------------------------------------------------------------|
     | Primary | Seconday  | STA Ch | RIFS |           reserved           |
     | Channel | Ch Offset | Width  | Mode |                              |
     |--------------------------------------------------------------------|
     |    1    | B0     B1 |   B2   |  B3  |    B4                     B7 |
     |--------------------------------------------------------------------|

     |----------------------------------------------------------------|
     |     HT     | Non-GF STAs | resv      | OBSS Non-HT  | Reserved |
     | Protection |   Present   |           | STAs Present |          |
     |----------------------------------------------------------------|
     | B0     B1  |     B2      |    B3     |     B4       | B5   B15 |
     |----------------------------------------------------------------|

     |-------------------------------------------------------------|
     | Reserved |  Dual  |  Dual CTS  | Seconday | LSIG TXOP Protn |
     |          | Beacon | Protection |  Beacon  | Full Support    |
     |-------------------------------------------------------------|
     | B0    B5 |   B6   |     B7     |     B8   |       B9        |
     |-------------------------------------------------------------|

     |---------------------------------------|
     |  PCO   |  PCO  | Reserved | Basic MCS |
     | Active | Phase |          |    Set    |
     |---------------------------------------|
     |  B10   |  B11  | B12  B15 |    16     |
     |---------------------------------------|
    **************************************************************************/

    while (us_msg_offset < us_msg_len)
    {
        /* 判断当前的ie是否是ht operation ie，如果不是，继续检查下一个ie，如果是，保存HT信息 */
        if (MAC_EID_HT_OPERATION == puc_payload[us_msg_offset])
        {
            us_msg_offset += MAC_IE_HDR_LEN;
            pst_ht_opern  = (mac_ht_opern_stru *)(&puc_payload[us_msg_offset]);

            /*从帧体中取值*/
            pst_hmac_user->st_user_base_info.st_ht_hdl.bit_rifs_mode                         = pst_ht_opern->bit_rifs_mode;/*发送描述符填写时候需要此值*/
            pst_hmac_user->st_user_base_info.st_ht_hdl.bit_HT_protection                     = pst_ht_opern->bit_HT_protection;
            pst_hmac_user->st_user_base_info.st_ht_hdl.bit_nongf_sta_present                 = pst_ht_opern->bit_nongf_sta_present;
            pst_hmac_user->st_user_base_info.st_ht_hdl.bit_obss_nonht_sta_present            = pst_ht_opern->bit_obss_nonht_sta_present;
            pst_hmac_user->st_user_base_info.st_ht_hdl.bit_lsig_txop_protection_full_support = pst_ht_opern->bit_lsig_txop_protection_full_support;
            return ;
        }

        us_msg_offset += (puc_payload[us_msg_offset + 1] + MAC_IE_HDR_LEN);
    }

}
#endif

/*****************************************************************************
 函 数 名  : hmac_sta_up_update_edca_params
 功能描述  : STA接收到beacon帧或者关联响应帧更新自身的EDCA参数，涉及到mib值
             和寄存器
 输入参数  : puc_payload :帧体
             ul_msg_len  :帧长度
             us_info_elem_offset :当前指向的帧体位置
             pst_hmac_sta        :指向hmac_vap的指针，vap是sta模式
             uc_frame_sub_type   :帧的次类型
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_sta_up_update_edca_params(
                    oal_uint8               *puc_payload,
                    oal_uint16               us_msg_len,
                    oal_uint16               us_info_elem_offset,
                    hmac_vap_stru           *pst_hmac_sta,
                    oal_uint8                uc_frame_sub_type,
                    hmac_user_stru          *pst_hmac_user)
{
    oal_uint16              us_msg_offset;
    oal_uint8               uc_param_set_cnt;
    oal_uint8               uc_ac_num_loop;
    oal_uint32              ul_ret;
    mac_device_stru        *pst_mac_device;
    oal_uint8               uc_edca_param_set;
    oal_uint8              *puc_ie = OAL_PTR_NULL;

    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_hmac_sta->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0,OAM_SF_ASSOC,"{hmac_sta_up_update_edca_params::mac_res_get_dev fail.device_id[%u]!}",pst_hmac_sta->st_vap_base_info.uc_device_id);
        return;
    }

    /* 检查帧中是否有WMM信息元素 */
    us_msg_offset = us_info_elem_offset;

    /************************ WMM Parameter Element ***************************/
    /* ------------------------------------------------------------------------------ */
    /* | EID | LEN | OUI |OUI Type |OUI Subtype |Version |QoS Info |Resd |AC Params | */
    /* ------------------------------------------------------------------------------ */
    /* |  1  |  1  |  3  |    1    |     1      |    1   |    1    |  1  |    16    | */
    /* ------------------------------------------------------------------------------ */

    /******************* QoS Info field when sent from WMM AP *****************/
    /*        --------------------------------------------                    */
    /*          | Parameter Set Count | Reserved | U-APSD |                   */
    /*          --------------------------------------------                  */
    /*   bit    |        0~3          |   4~6    |   7    |                   */
    /*          --------------------------------------------                  */
    /**************************************************************************/

    while (us_msg_offset < us_msg_len)
    {
        /* 判断当前的ie是否是wmm ie，如果不是，继续检查下一个ie，如果是，更新WMM参数 */
        if (OAL_TRUE == mac_is_wmm_ie(&puc_payload[us_msg_offset]))
        {
            /* 解析wmm ie是否携带EDCA参数 */
            uc_edca_param_set = puc_payload[us_msg_offset + MAC_OUISUBTYPE_WMM_PARAM_OFFSET];

            us_msg_offset += HMAC_WMM_QOS_PARAMS_HDR_LEN;
            uc_param_set_cnt = puc_payload[us_msg_offset] & 0x0F;

            /* 如果收到的是beacon帧，并且param_set_count没有改变，说明AP的WMM参数没有变
               则STA也不用做任何改变，直接返回即可.
            */
            if ((WLAN_FC0_SUBTYPE_BEACON == uc_frame_sub_type)
                && (uc_param_set_cnt == pst_hmac_sta->st_vap_base_info.uc_wmm_params_update_count))
            {

                return;
            }

            pst_mac_device->en_wmm = OAL_TRUE;

            if(WLAN_FC0_SUBTYPE_BEACON == uc_frame_sub_type)
            {
                /* 保存QoS Info */
                mac_vap_set_wmm_params_update_count(&pst_hmac_sta->st_vap_base_info, uc_param_set_cnt);
            }

            if (puc_payload[us_msg_offset] & BIT7)
            {
                mac_user_set_apsd(&(pst_hmac_user->st_user_base_info), OAL_TRUE);
            }
            else
            {
                mac_user_set_apsd(&(pst_hmac_user->st_user_base_info), OAL_FALSE);
            }

            us_msg_offset += HMAC_WMM_QOSINFO_AND_RESV_LEN;

            /* wmm ie中不携带edca参数 直接返回 */
            if(MAC_OUISUBTYPE_WMM_PARAM != uc_edca_param_set)
            {
                return;
            }

            /* 针对每一个AC，更新EDCA参数 */
            for (uc_ac_num_loop = 0; uc_ac_num_loop < WLAN_WME_AC_BUTT; uc_ac_num_loop++)
            {
                hmac_sta_up_update_edca_params_mib(pst_hmac_sta, &puc_payload[us_msg_offset]);
                us_msg_offset += HMAC_WMM_AC_PARAMS_RECORD_LEN;
            }

#if 0 //验收通过后，此函数会删除-

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP

            if (1 == pst_hmac_sta->uc_edca_opt_flag_sta)
            {
                hmac_edca_opt_adj_param_sta((oal_void*)pst_hmac_sta);
            }
#endif

#endif

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
            hcc_host_update_vi_flowctl_param(pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin,
                pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin);
#endif
            /* 更新EDCA相关的MAC寄存器 */
            hmac_sta_up_update_edca_params_machw(pst_hmac_sta, MAC_WMM_SET_PARAM_TYPE_UPDATE_EDCA);

            return;
        }

        us_msg_offset += (puc_payload[us_msg_offset + 1] + MAC_IE_HDR_LEN);
    }

    /* AP 管理帧不携带wmm ie，检查如果存在HT CAP就开启wmm能力 */
    puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_payload + us_info_elem_offset, (oal_uint32)(us_msg_len - us_info_elem_offset));
    if (OAL_PTR_NULL != puc_ie)
    {
        mac_vap_init_wme_param(&pst_hmac_sta->st_vap_base_info);
        pst_mac_device->en_wmm = OAL_TRUE;
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
        hcc_host_update_vi_flowctl_param(pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin,
        pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin);
#endif
        /* 更新EDCA相关的MAC寄存器 */
        hmac_sta_up_update_edca_params_machw(pst_hmac_sta, MAC_WMM_SET_PARAM_TYPE_UPDATE_EDCA);

        return;
    }



    if(WLAN_FC0_SUBTYPE_ASSOC_RSP == uc_frame_sub_type)
    {
        /* 当与STA关联的AP不是QoS的，STA会去使能EDCA寄存器，并默认利用VO级别发送数据 */
        ul_ret = hmac_sta_up_update_edca_params_machw(pst_hmac_sta, MAC_WMM_SET_PARAM_TYPE_DEFAULT);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                            "{hmac_sta_up_update_edca_params::hmac_sta_up_update_edca_params_machw failed[%d].}", ul_ret);
        }

        pst_mac_device->en_wmm = OAL_FALSE;
    }
}

/* TBD 1102临时注释STA TXOPPS处理,后续调试再打开*/
#ifdef _PRE_WLAN_FEATURE_TXOPPS
/*****************************************************************************
 函 数 名  : hmac_sta_set_txopps_partial_aid
 功能描述  : STA收到关联响应帧以后，用AP分配的AID和BSS的BSSID计算自身的part-
             ial aid，用于TXOP PS
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sta_set_txopps_partial_aid(mac_vap_stru *pst_mac_vap)
{
    oal_uint16              us_temp_aid;
    oal_uint8               uc_temp_bssid;
    oal_uint32               ul_ret;
    mac_cfg_txop_sta_stru    st_txop_info;

    /* 此处需要注意:按照协议规定(802.11ac-2013.pdf,9.17a)，ap分配给sta的aid，不可以
       使计算出来的partial aid为0，后续如果ap支持的最大关联用户数目超过512，必须要
       对aid做这个合法性检查!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    */

    if (WLAN_VHT_MODE != pst_mac_vap->en_protocol && WLAN_VHT_ONLY_MODE != pst_mac_vap->en_protocol)
    {
        return OAL_SUCC;
    }


    us_temp_aid   = pst_mac_vap->us_sta_aid & 0x1FF;
    uc_temp_bssid = (pst_mac_vap->auc_bssid[5] & 0x0F) ^ ((pst_mac_vap->auc_bssid[5] & 0xF0) >> 4);
    st_txop_info.us_partial_aid = (us_temp_aid + (uc_temp_bssid << 5) ) & ((1 << 9) - 1);
    st_txop_info.en_protocol = pst_mac_vap->en_protocol;

    /***************************************************************************
    抛事件到DMAC层, 同步DMAC数据
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_STA_TXOP_AID, OAL_SIZEOF(mac_cfg_txop_sta_stru), (oal_uint8 *)&st_txop_info);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TXOP, "{hmac_sta_set_txopps_partial_aid::hmac_config_send_event failed[%d].}", ul_ret);
    }

    return OAL_SUCC;
}
#endif

/*   2015-03-24 begin */
/*****************************************************************************
 函 数 名  : hmac_sta_update_mac_user_info
 功能描述  : 在beacon HT IE状态变化下更新mac user info到device
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_sta_update_mac_user_info(hmac_user_stru *pst_hmac_user_ap,oal_uint16 us_user_idx)
{
    mac_vap_stru                   *pst_mac_vap;
    mac_user_stru                  *pst_mac_user_ap;
    oal_uint32                      ul_ret;

    if (OAL_PTR_NULL == pst_hmac_user_ap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_sta_update_mac_user_info::param null.}");
        return;
    }

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hmac_user_ap->st_user_base_info.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap)) {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{hmac_sta_update_mac_user_info::get mac_vap [vap_id:%d] null.}", pst_hmac_user_ap->st_user_base_info.uc_vap_id);
        return;
    }

    pst_mac_user_ap = &(pst_hmac_user_ap->st_user_base_info);


    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                       "{hmac_sta_update_mac_user_info::us_user_idx:%d,en_avail_bandwidth:%d,en_cur_bandwidth:%d}",
                         us_user_idx,
                         pst_mac_user_ap->en_avail_bandwidth,
                         pst_mac_user_ap->en_cur_bandwidth);

    ul_ret = hmac_config_user_info_syn(pst_mac_vap, pst_mac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                       "{hmac_sta_update_mac_user_info::hmac_config_user_info_syn failed[%d].}", ul_ret);
    }

    ul_ret = hmac_config_user_rate_info_syn(pst_mac_vap, pst_mac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                       "{hmac_sta_wait_asoc_rx::hmac_syn_rate_info failed[%d].}", ul_ret);
    }
    return;
}

/*   2015-03-24 end */

/*****************************************************************************
 函 数 名  : hmac_sta_find_ie_in_probe_rsp
 功能描述  : 在已保存的probe rsp中寻找指定IE，一般用于在asoc rsp中寻找IE失败时
             再在probe rsp做进一步查找
 输入参数  : pst_mac_vap : mac vap结构体
             uc_eid: 要查找的EID
 输出参数  : puc_payload: probe rsp帧体，以帧内第一个IE开头
             us_index:目标IE在payload中的相对位置
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 * hmac_sta_find_ie_in_probe_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 uc_eid, oal_uint16 *pus_index)
{
    hmac_scanned_bss_info              *pst_scanned_bss_info;
    hmac_bss_mgmt_stru                 *pst_bss_mgmt;
    hmac_device_stru                   *pst_hmac_device;
    mac_bss_dscr_stru                  *pst_bss_dscr;
    oal_uint8                          *puc_ie;
    oal_uint8                          *puc_payload;
    oal_uint8                           us_offset;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{find ie fail, pst_mac_vap is null.}");
        return OAL_PTR_NULL;
    }

    /* 获取hmac device 结构 */
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{find ie fail, pst_hmac_device is null, dev id[%d].}", pst_mac_vap->uc_device_id);
        return OAL_PTR_NULL;
    }

    /* 获取管理扫描的bss结果的结构体 */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    pst_scanned_bss_info = hmac_scan_find_scanned_bss_by_bssid(pst_bss_mgmt, pst_mac_vap->auc_bssid);
    if (OAL_PTR_NULL == pst_scanned_bss_info)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                         "{find the bss failed by bssid:%02X:XX:XX:%02X:%02X:%02X}",
                         pst_mac_vap->auc_bssid[0],
                         pst_mac_vap->auc_bssid[3],
                         pst_mac_vap->auc_bssid[4],
                         pst_mac_vap->auc_bssid[5]);

       /* 解锁 */
       oal_spin_unlock(&(pst_bss_mgmt->st_lock));
       return OAL_PTR_NULL;
    }

    pst_bss_dscr = &(pst_scanned_bss_info->st_bss_dscr_info);
    /* 解锁 */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    /* 以IE开头的payload，返回供调用者使用 */
    us_offset = MAC_80211_FRAME_LEN + MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    /*lint -e416*/
    puc_payload = (oal_uint8*)(pst_bss_dscr->auc_mgmt_buff + us_offset);
    /*lint +e416*/
    if (pst_bss_dscr->ul_mgmt_len < us_offset)
    {
        return OAL_PTR_NULL;
    }

    puc_ie = mac_find_ie(uc_eid, puc_payload, (oal_int32)(pst_bss_dscr->ul_mgmt_len - us_offset));
    if (OAL_PTR_NULL == puc_ie)
    {
        return OAL_PTR_NULL;
    }

    /* IE长度初步校验 */
    if (0 == *(puc_ie + 1))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{IE[%d] len in probe rsp is 0, find ie fail.}", uc_eid);
        return OAL_PTR_NULL;
    }

    *pus_index = (oal_uint16)(puc_ie - puc_payload);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{found ie[%d] in probe rsp.}", uc_eid);

    return puc_payload;
}

/*****************************************************************************
 函 数 名  : hmac_sta_check_ht_cap_ie
 功能描述  : 在STA为WAIT_ASOC状态时，解析ht cap IE，分别在asoc rsp和probe rsp
             中查找
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_sta_check_ht_cap_ie(mac_vap_stru    *pst_mac_sta,
                                            oal_uint8       *puc_payload,
                                            mac_user_stru   *pst_mac_user_ap,
                                            oal_uint16      *pus_amsdu_maxsize,
                                            oal_uint16      us_payload_len)
{
    oal_uint8                          *puc_ie;
    oal_uint8                          *puc_payload_for_ht_cap_chk = OAL_PTR_NULL;
    oal_uint16                          us_ht_cap_index;
    oal_uint16                          us_ht_cap_info = 0;

    if ((OAL_PTR_NULL == pst_mac_sta) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_mac_user_ap))
    {
        return;
    }

    puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_payload, us_payload_len);
    if (OAL_PTR_NULL == puc_ie || puc_ie[1] < MAC_HT_CAP_LEN)
    {
        puc_payload_for_ht_cap_chk = hmac_sta_find_ie_in_probe_rsp(pst_mac_sta, MAC_EID_HT_CAP, &us_ht_cap_index);
        if (OAL_PTR_NULL == puc_payload_for_ht_cap_chk)
        {
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_sta_check_ht_cap_ie::puc_payload_for_ht_cap_chk is null.}");
            return;
        }

        /*lint -e413*/
        if (puc_payload_for_ht_cap_chk[us_ht_cap_index + 1] < MAC_HT_CAP_LEN)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_sta_check_ht_cap_ie::invalid ht cap len[%d].}", puc_payload_for_ht_cap_chk[us_ht_cap_index + 1]);
            return;
        }
        /*lint +e413*/
    }
    else
    {
        if (puc_ie < puc_payload)
        {
            return;
        }
        us_ht_cap_index = (oal_uint16)(puc_ie - puc_payload);
        puc_payload_for_ht_cap_chk = puc_payload;
    }

    mac_user_set_ht_capable(pst_mac_user_ap, OAL_TRUE);

    /* 支持HT, 默认初始化 */
    /* hmac_amsdu_init_user(pst_hmac_user_ap); */

    /* 根据协议值设置特性，必须在hmac_amsdu_init_user后面调用 */
    mac_ie_proc_ht_sta(pst_mac_sta, puc_payload_for_ht_cap_chk, &us_ht_cap_index, pst_mac_user_ap, &us_ht_cap_info, pus_amsdu_maxsize);

    /*  问题单号:支持ht能力，但是空间流速率集为0，要置对端AP为不支持ht能力，从而以11a或者11g关联AP */
    if ((pst_mac_user_ap->st_ht_hdl.uc_rx_mcs_bitmask[3] == 0) && (pst_mac_user_ap->st_ht_hdl.uc_rx_mcs_bitmask[2] == 0)
        &&(pst_mac_user_ap->st_ht_hdl.uc_rx_mcs_bitmask[1] == 0)&&(pst_mac_user_ap->st_ht_hdl.uc_rx_mcs_bitmask[0]) == 0)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{hmac_sta_check_ht_cap_ie::AP support ht capability but support none space_stream.}");
        /* 对端ht能力置为不支持 */
        mac_user_set_ht_capable(pst_mac_user_ap, OAL_FALSE);
    }

}

/*****************************************************************************
 函 数 名  : hmac_sta_check_ext_cap_ie
 功能描述  : 在STA为WAIT_ASOC状态时，解析ext cap IE，分别在asoc rsp和probe rsp
             中查找
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月24日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_void hmac_sta_check_ext_cap_ie(mac_vap_stru    *pst_mac_sta,
                                    mac_user_stru   *pst_mac_user_ap,
                                    oal_uint8       *puc_payload,
                                    oal_uint16       us_rx_len)
{
    oal_uint8       *puc_ie;
    oal_uint8       *puc_payload_proc = OAL_PTR_NULL;
    oal_uint16       us_index;

    puc_ie = mac_find_ie(MAC_EID_EXT_CAPS, puc_payload, us_rx_len);
    if (OAL_PTR_NULL == puc_ie || puc_ie[1] < MAC_XCAPS_LEN)
    {
        puc_payload_proc = hmac_sta_find_ie_in_probe_rsp(pst_mac_sta, MAC_EID_EXT_CAPS, &us_index);
        if (OAL_PTR_NULL == puc_payload_proc)
        {
            return;
        }

        /*lint -e413*/
        if (puc_payload_proc[us_index + 1] < MAC_XCAPS_LEN)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_sta_check_ext_cap_ie::invalid ext cap len[%d].}", puc_payload_proc[us_index + 1]);
            return;
        }
        /*lint +e413*/
    }
    else
    {
        puc_payload_proc = puc_payload;
        if (puc_ie < puc_payload)
        {
            return;
        }

        us_index = (oal_uint16)(puc_ie - puc_payload);
    }

    /* 处理 Extended Capabilities IE */
    /*lint -e613*/
    mac_ie_proc_ext_cap_ie(pst_mac_user_ap, &puc_payload_proc[us_index]);
    /*lint +e613*/
}

/*****************************************************************************
 函 数 名  : hmac_sta_check_ht_opern_ie
 功能描述  : 在STA为WAIT_ASOC状态时，解析ht opern IE，分别在asoc rsp和probe rsp
             中查找
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_sta_check_ht_opern_ie(mac_vap_stru    *pst_mac_sta,
                                    mac_user_stru   *pst_mac_user_ap,
                                    oal_uint8       *puc_payload,
                                    oal_uint16       us_rx_len)
{
    oal_uint8       *puc_ie;
    oal_uint8       *puc_payload_proc = OAL_PTR_NULL;
    oal_uint16       us_index;
    oal_uint32       ul_change = HMAC_NO_CHANGE;

    puc_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_payload, us_rx_len);
    if (OAL_PTR_NULL == puc_ie || puc_ie[1] < MAC_HT_OPERN_LEN)
    {
        puc_payload_proc = hmac_sta_find_ie_in_probe_rsp(pst_mac_sta, MAC_EID_HT_OPERATION, &us_index);
        if (OAL_PTR_NULL == puc_payload_proc)
        {
            return ul_change;
        }

        /*lint -e413*/
        if (puc_payload_proc[us_index + 1] < MAC_HT_OPERN_LEN)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_sta_check_ht_opern_ie::invalid ht cap len[%d].}", puc_payload_proc[us_index + 1]);
            return ul_change;
        }
        /*lint +e413*/
    }
    else
    {
        puc_payload_proc = puc_payload;
        if (puc_ie < puc_payload)
        {
            return ul_change;
        }

        us_index = (oal_uint16)(puc_ie - puc_payload);
    }

    ul_change |= hmac_proc_ht_opern_ie(pst_mac_sta, &puc_payload_proc[us_index], pst_mac_user_ap);
    /* 只针对 HT Operation中的Secondary Channel Offset进行处理 */
    ul_change |= hmac_ie_proc_sec_chan_offset_2040(pst_mac_sta, puc_payload[us_index + MAC_IE_HDR_LEN + 1] & 0x3);

    return ul_change;
}

/*****************************************************************************
 函 数 名  : hmac_ie_check_ht_sta
 功能描述  : 在STA为WAIT_ASOC状态时，解析asoc rsp 或者reasoc rsp frame，更新相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_ie_check_ht_sta(mac_vap_stru    *pst_mac_sta,
                               oal_uint8       *puc_payload,
                               oal_uint16       us_offset,
                               oal_uint16       us_rx_len,
                               mac_user_stru   *pst_mac_user_ap,
                               oal_uint16      *pus_amsdu_maxsize)
{
    oal_uint32              ul_change = HMAC_NO_CHANGE;
    oal_uint8              *puc_ie_payload_start;
    oal_uint16              us_ie_payload_len;

    if ((OAL_PTR_NULL == pst_mac_sta) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_mac_user_ap))
    {
        return ul_change;
    }

    /* 初始化HT cap为FALSE，入网时会把本地能力跟随AP能力 */
    mac_user_set_ht_capable(pst_mac_user_ap, OAL_FALSE);

     /* 至少支持11n才进行后续的处理 */
    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_sta))
    {
        return ul_change;
    }

    puc_ie_payload_start = puc_payload + us_offset;
    us_ie_payload_len    = us_rx_len - us_offset;

    hmac_sta_check_ht_cap_ie(pst_mac_sta, puc_ie_payload_start, pst_mac_user_ap, pus_amsdu_maxsize, us_ie_payload_len);

    hmac_sta_check_ext_cap_ie(pst_mac_sta, pst_mac_user_ap, puc_ie_payload_start, us_ie_payload_len);

    ul_change = hmac_sta_check_ht_opern_ie(pst_mac_sta, pst_mac_user_ap, puc_ie_payload_start, us_ie_payload_len);

    return ul_change;
}

/*****************************************************************************
 函 数 名  : hmac_ie_proc_obss_ie
 功能描述  : 处理Overlapping BSS Scan Parameters IE，并更新STA相应MIB项
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             puc_payload: 指向Overlapping BSS Scan Parameters IE的指针
 输出参数  : 无
 返 回 值  :
 调用函数  : OAL_SUCC或其它错误码
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_ie_proc_obss_scan_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload)
{
    oal_uint16 us_trigger_scan_interval;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    wlan_mib_Dot11OperationEntry_stru st_old_mib;
#endif
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_ie_proc_obss_scan_ie::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /********************Overlapping BSS Scan Parameters element******************
     |ElementID |Length |OBSS    |OBSS   |BSS Channel   |OBSS Scan  |OBSS Scan   |
     |          |       |Scan    |Scan   |Width Trigger |Passive    |Active Total|
     |          |       |Passive |Active |Scan Interval |Total Per  |Per         |
     |          |       |Dwell   |Dwell  |              |Channel    |Channel     |
     ----------------------------------------------------------------------------
     |1         |1      |2       |2      |2             |2          |2           |
     ----------------------------------------------------------------------------
     |BSS Width   |OBSS Scan|
     |Channel     |Activity |
     |Transition  |Threshold|
     |Delay Factor|         |
     ------------------------
     |2           |2        |
    ***************************************************************************/
    if ( puc_payload[1] < MAC_OBSS_SCAN_IE_LEN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{mac_ie_proc_obss_scan_ie::invalid obss scan ie len[%d].}", puc_payload[1]);
        return OAL_FAIL;
    }

    us_trigger_scan_interval = OAL_MAKE_WORD16(puc_payload[6], puc_payload[7]);
    if (0 == us_trigger_scan_interval)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy(&st_old_mib, &pst_mac_vap->pst_mib_info->st_wlan_mib_operation, OAL_SIZEOF(st_old_mib));
#endif
    mac_mib_set_OBSSScanPassiveDwell(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[2], puc_payload[3]));
    mac_mib_set_OBSSScanActiveDwell(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[4], puc_payload[5]));
    /* obss扫描周期最小300秒,最大600S, 初始化默认为300秒 */
    mac_mib_set_BSSWidthTriggerScanInterval(pst_mac_vap, OAL_MIN(OAL_MAX(us_trigger_scan_interval, 300), 600));
    mac_mib_set_OBSSScanPassiveTotalPerChannel(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[8], puc_payload[9]));
    mac_mib_set_OBSSScanActiveTotalPerChannel(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[10], puc_payload[11]));
    mac_mib_set_BSSWidthChannelTransitionDelayFactor(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[12], puc_payload[13]));
    mac_mib_set_OBSSScanActivityThreshold(pst_mac_vap, OAL_MAKE_WORD16(puc_payload[14], puc_payload[15]));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (0 != oal_memcmp(&st_old_mib, &pst_mac_vap->pst_mib_info->st_wlan_mib_operation, OAL_SIZEOF(st_old_mib)))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_ie_proc_obss_scan_ie::sync obss mib to dmac");
        hmac_config_set_obss_scan_param(pst_mac_vap);
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_ie_proc_sec_chan_offset_2040
 功能描述  : 只针对HT Operation IE中的Secondary Channel Offset(SCO)进行处理
 输入参数  : pst_mac_vap       : MAC VAP结构体指针
             en_sec_chan_offset: HT Operation IE中的次信道偏移量
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 备    注  : 此函数将HT Operation IE中的SCO与STA自身的SCO进行比较，
             如果不一致，则需要根据AP的SCO与自身能力进行调整
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_ie_proc_sec_chan_offset_2040(mac_vap_stru *pst_mac_vap, mac_sec_ch_off_enum_uint8 en_sec_chan_offset)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "{hmac_ie_proc_sec_chan_offset_2040::pst_mac_vap null.}");
        return HMAC_NO_CHANGE;
    }

    /* HT Operation IE中的"次信道偏移量"与当前STA的"带宽模式"不符 */
    if (en_sec_chan_offset != mac_get_sco_from_bandwidth(pst_mac_vap->st_channel.en_bandwidth))
    {

        pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;
        /* 先判断是否支持HT模式在判断40M*/
        if (OAL_TRUE== mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)
            && OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
        {
            /* 更新带宽模式 */
            if (MAC_SCA == en_sec_chan_offset)
            {
                pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40PLUS;
            }
            else if (MAC_SCB == en_sec_chan_offset)
            {
                pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40MINUS;
            }

            /* 需要设置硬件以切换带宽 */
            return HMAC_BW_CHANGE;
        }
    }

    return HMAC_NO_CHANGE;
}

/*****************************************************************************
 函 数 名  : mac_ie_proc_ht_opern_ie
 功能描述  : 处理HT Operation IE
 输入参数  : pst_mac_vap : MAC VAP结构体指针，指向STA
             puc_payload : 指向HT Operation IE的指针
             pst_mac_user: MAC VAP结构体指针，指向AP
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_proc_ht_opern_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_user_stru *pst_mac_user)
{
    mac_ht_opern_stru       *pst_ht_opern;
    mac_user_ht_hdl_stru     st_ht_hdl;
/* #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST */
    wlan_bw_cap_enum_uint8   en_bwcap_vap;
    oal_uint32               ul_change = HMAC_NO_CHANGE;
/* #endif */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_mac_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_ie_proc_ht_opern_ie::param null.}");
        return ul_change;
    }

    /* 长度校验，此处仅用到前6字节，后面Basic MCS Set未涉及 */
    if (puc_payload[1] < 6)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_proc_ht_opern_ie::invalid ht opern ie len[%d].}", puc_payload[1]);
        return ul_change;
    }

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);

    /************************ HT Operation Element *************************************
      ----------------------------------------------------------------------
      |EID |Length |PrimaryChannel |HT Operation Information |Basic MCS Set|
      ----------------------------------------------------------------------
      |1   |1      |1              |5                        |16           |
      ----------------------------------------------------------------------
    ***************************************************************************/

    /************************ HT Information Field ****************************
     |--------------------------------------------------------------------|
     | Primary | Seconday  | STA Ch | RIFS |           reserved           |
     | Channel | Ch Offset | Width  | Mode |                              |
     |--------------------------------------------------------------------|
     |    1    | B0     B1 |   B2   |  B3  |    B4                     B7 |
     |--------------------------------------------------------------------|

     |----------------------------------------------------------------|
     |     HT     | Non-GF STAs | resv      | OBSS Non-HT  | Reserved |
     | Protection |   Present   |           | STAs Present |          |
     |----------------------------------------------------------------|
     | B0     B1  |     B2      |    B3     |     B4       | B5   B15 |
     |----------------------------------------------------------------|

     |-------------------------------------------------------------|
     | Reserved |  Dual  |  Dual CTS  | Seconday | LSIG TXOP Protn |
     |          | Beacon | Protection |  Beacon  | Full Support    |
     |-------------------------------------------------------------|
     | B0    B5 |   B6   |     B7     |     B8   |       B9        |
     |-------------------------------------------------------------|

     |---------------------------------------|
     |  PCO   |  PCO  | Reserved | Basic MCS |
     | Active | Phase |          |    Set    |
     |---------------------------------------|
     |  B10   |  B11  | B12  B15 |    16     |
     |---------------------------------------|
    **************************************************************************/

    pst_ht_opern  = (mac_ht_opern_stru *)(&puc_payload[MAC_IE_HDR_LEN]);

/* #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST */
    /* 提取HT Operation IE中的"STA Channel Width" */
    mac_user_set_bandwidth_info(pst_mac_user, pst_ht_opern->bit_sta_chan_width, pst_mac_user->en_cur_bandwidth);

    /* 提取HT Operation IE中的"Secondary Channel Offset" */
    st_ht_hdl.bit_secondary_chan_offset = pst_ht_opern->bit_secondary_chan_offset;

    /* 为了防止5G下用户声称20M，但发送80M数据的情况，在5G情况下该变量不切换 */
    if ((0 == pst_mac_user->en_avail_bandwidth) && (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band))
    {
        st_ht_hdl.bit_secondary_chan_offset = MAC_SCN;
    }

    ul_change = hmac_ie_proc_sec_chan_offset_2040(pst_mac_vap, pst_ht_opern->bit_secondary_chan_offset);

    /* 用户与VAP带宽能力取交集 */
    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap_vap);
    en_bwcap_vap = OAL_MIN(pst_mac_user->en_bandwidth_cap, en_bwcap_vap);
    en_bwcap_vap = OAL_MIN(pst_mac_user->en_avail_bandwidth, en_bwcap_vap);
    mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);

/* #endif *//* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

    /* 保护相关 */
    st_ht_hdl.bit_rifs_mode                         = pst_ht_opern->bit_rifs_mode;/*发送描述符填写时候需要此值*/
    st_ht_hdl.bit_HT_protection                     = pst_ht_opern->bit_HT_protection;
    st_ht_hdl.bit_nongf_sta_present                 = pst_ht_opern->bit_nongf_sta_present;
    st_ht_hdl.bit_obss_nonht_sta_present            = pst_ht_opern->bit_obss_nonht_sta_present;
    st_ht_hdl.bit_lsig_txop_protection_full_support = pst_ht_opern->bit_lsig_txop_protection_full_support;

    mac_user_set_ht_hdl(pst_mac_user, &st_ht_hdl);

    return ul_change;
}

/*****************************************************************************
 函 数 名  : hmac_ie_proc_assoc_user_legacy_rate
 功能描述  : 解析帧中legacy 速率集，更新到user的结构体速率变量成员中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ie_proc_assoc_user_legacy_rate(
                                                                oal_uint8           *puc_payload,
                                                                oal_uint16           us_offset,
                                                                oal_uint16           us_rx_len,
                                                                hmac_user_stru      *pst_hmac_user)
{
    oal_uint8   *puc_ie;
    oal_uint8    uc_num_rates    = 0;
    oal_uint8    uc_num_ex_rates = 0;

    //puc_ie = mac_get_supported_rates_ie(puc_payload, us_rx_len,us_offset);
    puc_ie = mac_find_ie(MAC_EID_RATES, puc_payload + us_offset, us_rx_len - us_offset);
    if (OAL_PTR_NULL != puc_ie)
    {
        uc_num_rates = puc_ie[1];

        if(uc_num_rates > WLAN_MAX_SUPP_RATES || uc_num_rates < MAC_MIN_XRATE_LEN)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ie_proc_assoc_user_legacy_rate:: invaild rates:%d}", uc_num_rates);
            return OAL_EFAIL;
        }
        oal_memcopy(pst_hmac_user->st_op_rates.auc_rs_rates, puc_ie + MAC_IE_HDR_LEN, uc_num_rates);
    }

    //puc_ie = mac_get_exsup_rates_ie(puc_payload, us_rx_len, us_offset);
    puc_ie = mac_find_ie(MAC_EID_XRATES, puc_payload + us_offset, us_rx_len - us_offset);
    if (OAL_PTR_NULL != puc_ie)
    {
        uc_num_ex_rates = puc_ie[1];

        if (uc_num_ex_rates < MAC_MIN_XRATE_LEN)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ie_proc_assoc_user_legacy_rate:: invaild xrates:%d}", uc_num_ex_rates);
            return OAL_EFAIL;
        }

        if (uc_num_rates + uc_num_ex_rates > WLAN_MAX_SUPP_RATES) /* 超出支持速率个数 */
        {
            uc_num_ex_rates = WLAN_MAX_SUPP_RATES - uc_num_rates;
        }

        oal_memcopy(&(pst_hmac_user->st_op_rates.auc_rs_rates[uc_num_rates]), puc_ie + MAC_IE_HDR_LEN, uc_num_ex_rates);
    }

    pst_hmac_user->st_op_rates.uc_rs_nrates = uc_num_rates + uc_num_ex_rates;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_asoc_rx
 功能描述  : 在WAIT_ASOC状态下接收到Asoc_rsp_frame的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_sta_wait_asoc_rx(hmac_vap_stru *pst_hmac_sta, oal_void *pst_msg)
{
    mac_status_code_enum_uint16     en_asoc_status;
    oal_uint8                       uc_frame_sub_type;
    dmac_wlan_crx_event_stru       *pst_mgmt_rx_event;
    dmac_rx_ctl_stru               *pst_rx_ctrl;
    mac_rx_ctl_stru                *pst_rx_info;
    oal_uint8                      *puc_mac_hdr;
    oal_uint8                      *puc_payload;
    oal_uint16                      us_msg_len;
    hmac_asoc_rsp_stru              st_asoc_rsp;
    oal_uint8                       auc_addr_sa[WLAN_MAC_ADDR_LEN];
    oal_uint16                      us_user_idx;
    oal_uint32                      ul_rslt;
    hmac_user_stru                 *pst_hmac_user_ap;
    oal_uint16                      us_offset;
    oal_uint16                      us_aid;
    oal_uint8                      *puc_vht_cap_ie;
#ifdef _PRE_WLAN_FEATURE_HISTREAM
    oal_uint8                      *puc_histream_ie;
#endif //_PRE_WLAN_FEATURE_HISTREAM
    oal_uint8                      *puc_vht_opern_ie_index;
    wlan_bw_cap_enum_uint8          en_bandwidth_cap;
    oal_uint32                      ul_ret;
    mac_device_stru                *pst_mac_device;
    mac_user_stru                  *pst_mac_user_ap;
    mac_vap_stru                   *pst_mac_vap;
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                      *puc_vendor_ie;
#endif
    wlan_bw_cap_enum_uint8          en_bwcap;
    oal_uint32                      ul_change = HMAC_NO_CHANGE;
    mac_cfg_user_info_param_stru    st_hmac_user_info_event;

    if ((OAL_PTR_NULL == pst_hmac_sta) || (OAL_PTR_NULL == pst_msg))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_sta_wait_asoc_rx::param null,%d %d.}", pst_hmac_sta, pst_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap     = &(pst_hmac_sta->st_vap_base_info);

    pst_mgmt_rx_event   = (dmac_wlan_crx_event_stru *)pst_msg;
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    puc_mac_hdr         = (oal_uint8 *)(pst_rx_info->pul_mac_hdr_start_addr);
    puc_payload         = (oal_uint8 *)(puc_mac_hdr) + pst_rx_info->uc_mac_header_len;
    us_msg_len          = pst_rx_info->us_frame_len - pst_rx_info->uc_mac_header_len;   /* 消息总长度,不包括FCS */

    if (us_msg_len < OAL_ASSOC_RSP_FIXED_OFFSET)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_sta_wait_asoc_rx::asoc_rsp_body is too short(%d) to going on!}", us_msg_len);
        return OAL_FAIL;
    }

    us_offset         =  0;
    uc_frame_sub_type = mac_get_frame_sub_type(puc_mac_hdr);

    oal_memset(&st_asoc_rsp, 0, OAL_SIZEOF(hmac_asoc_rsp_stru));

    /* 设置初始关联状态为成功 */
    st_asoc_rsp.en_result_code = HMAC_MGMT_SUCCESS;


    switch (uc_frame_sub_type)
    {
        case WLAN_FC0_SUBTYPE_ASSOC_RSP:
        case WLAN_FC0_SUBTYPE_REASSOC_RSP:
            break;

        default:
            /* do nothing,wait for time out */
            return OAL_FAIL;
    }

    /* 获取cap info *///
/*    us_cap_info     = puc_payload[us_offset] | (puc_payload[(us_offset + 1)] << 8);
    pst_cap_info    = (mac_cap_info_stru *)(&us_cap_info);*/
    us_offset      += MAC_CAP_INFO_LEN;

    en_asoc_status = mac_get_asoc_status(puc_payload);

    us_offset +=  MAC_STATUS_CODE_LEN;


    if (MAC_SUCCESSFUL_STATUSCODE != en_asoc_status)
    {
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_sta_wait_asoc_rx:: AP refuse STA assoc reason=%d.}", en_asoc_status);
        return OAL_FAIL;
    }

    /* 获取SA 地址 */
    mac_get_address2(puc_mac_hdr, auc_addr_sa);

    /* 根据SA 地地找到对应AP USER结构 */
    ul_rslt = mac_vap_find_user_by_macaddr(&(pst_hmac_sta->st_vap_base_info), auc_addr_sa, &us_user_idx);

    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_sta_wait_asoc_rx:: mac_vap_find_user_by_macaddr failed[%d].}", ul_rslt);

        return ul_rslt;
    }

    /* 获取STA关联的AP的用户指针 */
    pst_hmac_user_ap = mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user_ap)
    {
        return OAL_FAIL;
    }

    /* 获取Device指针 */
    pst_mac_device = mac_res_get_dev(pst_hmac_sta->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_sta_wait_asoc_rx::pst_mac_device[%d] null.}", pst_hmac_sta->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 取消定时器 */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_sta->st_mgmt_timer));
    pst_mac_user_ap = &(pst_hmac_user_ap->st_user_base_info);

    /* 更新关联ID */
    us_aid = mac_get_asoc_id(puc_payload);
    if ((us_aid > 0) && (us_aid <= 2007))
    {
        mac_vap_set_aid(&pst_hmac_sta->st_vap_base_info, us_aid);
/* TBD 1102临时注释STA TXOPPS处理,后续调试再打开*/
    #ifdef _PRE_WLAN_FEATURE_TXOPPS
        /* sta计算自身的partial aid，保存到vap结构中，并写入到mac寄存器 */
        hmac_sta_set_txopps_partial_aid(&pst_hmac_sta->st_vap_base_info);
    #endif
    }
    else
    {
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_sta_wait_asoc_rx::invalid us_sta_aid[%d].}", us_aid);
    }
    us_offset +=  MAC_AID_LEN;

    /* 初始化安全端口过滤参数 */
#if defined (_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    ul_rslt = hmac_init_user_security_port(&(pst_hmac_sta->st_vap_base_info), &(pst_hmac_user_ap->st_user_base_info));
    if (OAL_SUCC != ul_rslt)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_init_user_security_port failed[%d].}", ul_rslt);
    }

#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    /* STA模式下的pmf能力来源于WPA_supplicant，只有启动pmf和不启动pmf两种类型 */
    mac_user_set_pmf_active(&pst_hmac_user_ap->st_user_base_info, pst_mac_vap->en_user_pmf_cap);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    /* sta更新自身的edca parameters */
    hmac_sta_up_update_edca_params(puc_payload, us_msg_len, us_offset, pst_hmac_sta, uc_frame_sub_type, pst_hmac_user_ap);

    /* 更新关联用户的 QoS protocol table */
    hmac_mgmt_update_assoc_user_qos_table(puc_payload, us_msg_len, us_offset, pst_hmac_user_ap);

    /* 更新关联用户的legacy速率集合 */
    hmac_ie_proc_assoc_user_legacy_rate(puc_payload, us_offset, us_msg_len, pst_hmac_user_ap);

    /* 更新 HT 参数  */
    ul_change |= hmac_ie_check_ht_sta(&pst_hmac_sta->st_vap_base_info, puc_payload, us_offset, us_msg_len, &pst_hmac_user_ap->st_user_base_info, &pst_hmac_user_ap->us_amsdu_maxsize);

#ifdef _PRE_WLAN_FEATURE_TXBF
    /* 更新11n txbf能力 */
    puc_vendor_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_EID_11NTXBF, puc_payload + us_offset, us_msg_len - us_offset);
    hmac_mgmt_update_11ntxbf_cap(puc_vendor_ie, pst_hmac_user_ap);
#endif

    /* 更新11ac VHT capabilities ie */
    //puc_vht_cap_ie  = mac_get_vht_cap_ie(puc_payload, us_msg_len, us_offset);
    puc_vht_cap_ie = mac_find_ie(MAC_EID_VHT_CAP, puc_payload + us_offset, us_msg_len - us_offset);
    if (OAL_PTR_NULL != puc_vht_cap_ie)
    {
        hmac_proc_vht_cap_ie(pst_mac_vap, pst_hmac_user_ap, puc_vht_cap_ie);
    }

    /* 更新11ac VHT operation ie */
    //puc_vht_opern_ie_index  = mac_get_vht_opern_ie(puc_payload, us_msg_len, us_offset);
    puc_vht_opern_ie_index = mac_find_ie(MAC_EID_VHT_OPERN, puc_payload + us_offset, us_msg_len - us_offset);
    if (OAL_PTR_NULL != puc_vht_opern_ie_index)
    {
        ul_change |= hmac_update_vht_opern_ie_sta(pst_mac_vap, pst_hmac_user_ap, puc_vht_opern_ie_index, us_offset);
    }

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    if (HISTREAM_SWITCH_ON == g_uc_histream_switch)
    {
        /* 更新histream信息 */
        puc_histream_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_HISI_HISTREAM_IE, puc_payload + us_offset, us_msg_len - us_offset);
        hmac_mgmt_update_histream_info(pst_mac_vap, pst_hmac_user_ap, puc_histream_ie);
    }
#endif //_PRE_WLAN_FEATURE_HISTREAM

    /* 评估是否需要进行带宽切换 */
    //hmac_chan_reval_bandwidth_sta(pst_mac_vap, ul_change);
    if (HMAC_BW_CHANGE & ul_change)
    {
        OAM_WARNING_LOG3(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::change BW. ul_change[0x%x], uc_channel[%d], en_bandwidth[%d].}",
                       ul_change,
                       pst_mac_vap->st_channel.uc_chan_number,
                       pst_mac_vap->st_channel.en_bandwidth);
        hmac_chan_sync(pst_mac_vap,
                        pst_mac_vap->st_channel.uc_chan_number,
                        pst_mac_vap->st_channel.en_bandwidth,
                        OAL_TRUE);
    }

    /* 获取用户的协议模式 */
    hmac_set_user_protocol_mode(pst_mac_vap, pst_hmac_user_ap);

    /* 将协议模式更新到STA */
//    pst_mac_vap->en_protocol = pst_hmac_user_ap->st_user_base_info.en_protocol_mode;

    /* 获取用户与VAP协议模式交集 */
    mac_user_set_avail_protocol_mode(&pst_hmac_user_ap->st_user_base_info, g_auc_avail_protocol_mode[pst_mac_vap->en_protocol][pst_hmac_user_ap->st_user_base_info.en_protocol_mode]);
    mac_user_set_cur_protocol_mode(&pst_hmac_user_ap->st_user_base_info, pst_hmac_user_ap->st_user_base_info.en_avail_protocol_mode);

    /* 获取用户和VAP 可支持的11a/b/g 速率交集 */
    hmac_vap_set_user_avail_rates(&(pst_hmac_sta->st_vap_base_info), pst_hmac_user_ap);

    /* 获取用户与VAP带宽能力交集 */
    /* 获取用户的带宽能力 */
    mac_user_get_ap_opern_bandwidth(&(pst_hmac_user_ap->st_user_base_info), &en_bandwidth_cap);

    mac_vap_get_bandwidth_cap(pst_mac_vap, &en_bwcap);
    en_bwcap = OAL_MIN(en_bwcap, en_bandwidth_cap);
    mac_user_set_bandwidth_info(&pst_hmac_user_ap->st_user_base_info, en_bwcap, en_bwcap);

    OAM_WARNING_LOG3(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::mac user[%d] en_bandwidth_cap:%d,en_avail_bandwidth:%d}",
                       pst_hmac_user_ap->st_user_base_info.us_assoc_id,
                       en_bandwidth_cap,
                       pst_hmac_user_ap->st_user_base_info.en_avail_bandwidth);

    /* 获取用户与VAP空间流交集 */
    ul_ret = hmac_user_set_avail_num_space_stream(&(pst_hmac_user_ap->st_user_base_info), pst_hmac_sta->st_vap_base_info.en_vap_rx_nss);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::mac_user_set_avail_num_space_stream failed[%d].}", ul_ret);
    }

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY

    /* 处理Operating Mode Notification 信息元素 */
    ul_ret = hmac_check_opmode_notify(pst_hmac_sta, puc_mac_hdr, puc_payload, us_offset, us_msg_len, pst_hmac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_check_opmode_notify failed[%d].}", ul_ret);
    }

#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    pst_hmac_sta->en_amsdu_active = OAL_FALSE;
#endif
#endif

    /* STA切换到UP状态 */
    hmac_fsm_change_state(pst_hmac_sta, MAC_VAP_STATE_UP);

#ifdef _PRE_WLAN_FEATURE_ROAM
    hmac_roam_info_init(pst_hmac_sta);
#endif //_PRE_WLAN_FEATURE_ROAM

    /* 将用户(AP)在本地的状态信息设置为已关联状态 */
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    mac_user_change_info_event(pst_hmac_user_ap->st_user_base_info.auc_user_mac_addr,
                               pst_hmac_sta->st_vap_base_info.uc_vap_id,
                               pst_hmac_user_ap->st_user_base_info.en_user_asoc_state,
                               MAC_USER_STATE_ASSOC, OAM_MODULE_ID_HMAC,
                               OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
#endif
    mac_user_set_asoc_state(&pst_hmac_user_ap->st_user_base_info, MAC_USER_STATE_ASSOC);

    /* dmac offload架构下，同步STA USR信息到dmac */
    ul_ret = hmac_config_user_cap_syn(&(pst_hmac_sta->st_vap_base_info), pst_mac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_config_usr_cap_syn failed[%d].}", ul_ret);
    }

    ul_ret = hmac_config_user_info_syn(&(pst_hmac_sta->st_vap_base_info), pst_mac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_syn_vap_state failed[%d].}", ul_ret);
    }

    ul_ret = hmac_config_user_rate_info_syn(&(pst_hmac_sta->st_vap_base_info), pst_mac_user_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_syn_rate_info failed[%d].}", ul_ret);
    }


    /* 打开80211单播管理帧开关，观察关联过程，关联成功了就关闭 */
    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_TX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_OFF;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_OFF;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_OFF;
    oal_memcopy(st_80211_ucast_switch.auc_user_macaddr,
                (const oal_void *)pst_hmac_user_ap->st_user_base_info.auc_user_mac_addr,
                OAL_SIZEOF(st_80211_ucast_switch.auc_user_macaddr));
    hmac_config_80211_ucast_switch(&(pst_hmac_sta->st_vap_base_info),OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);

    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_RX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_OFF;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_OFF;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_OFF;
    hmac_config_80211_ucast_switch(&(pst_hmac_sta->st_vap_base_info),OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);

    /* user已经关联上，抛事件给DMAC，在DMAC层挂用户算法钩子 */
    hmac_user_add_notify_alg(&(pst_hmac_sta->st_vap_base_info), us_user_idx);

    /* 准备消息，上报给APP */
    st_asoc_rsp.en_result_code = HMAC_MGMT_SUCCESS;
    st_asoc_rsp.en_status_code = MAC_SUCCESSFUL_STATUSCODE;

    /* 记录关联响应帧的部分内容，用于上报给内核 */
    st_asoc_rsp.ul_asoc_rsp_ie_len = us_msg_len - OAL_ASSOC_RSP_FIXED_OFFSET;  /* 除去MAC帧头24字节和FIXED部分6字节 */
    st_asoc_rsp.puc_asoc_rsp_ie_buff = puc_mac_hdr + OAL_ASSOC_RSP_IE_OFFSET;

    /* 获取AP的mac地址 */
    mac_get_bssid(puc_mac_hdr, st_asoc_rsp.auc_addr_ap);

    /* 获取关联请求帧信息 */
    st_asoc_rsp.puc_asoc_req_ie_buff = pst_hmac_sta->puc_asoc_req_ie_buff;
    st_asoc_rsp.ul_asoc_req_ie_len   = pst_hmac_sta->ul_asoc_req_ie_len;

    hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_ASOC_RSP, (oal_uint8 *)(&st_asoc_rsp));

#if 0
    /*如果是WEP，需要将ap的mac地址写入lut*/
    ul_ret = hmac_init_security(&(pst_hmac_sta->st_vap_base_info), st_asoc_rsp.auc_addr_ap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_init_security failed[%d].}", ul_ret);
    }
#endif

    /* dmac offload架构下，同步STA USR信息到dmac */
    ul_ret = hmac_config_sta_vap_info_syn(&(pst_hmac_sta->st_vap_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_wait_asoc_rx::hmac_syn_vap_state failed[%d].}", ul_ret);
    }

    /* 1102 STA 入网后，上报VAP 信息和用户信息 */
    st_hmac_user_info_event.us_user_idx = us_user_idx;

    hmac_config_vap_info(pst_mac_vap, OAL_SIZEOF(oal_uint32), (oal_uint8 *)&ul_ret);
    hmac_config_user_info(pst_mac_vap, OAL_SIZEOF(mac_cfg_user_info_param_stru), (oal_uint8 *)&st_hmac_user_info_event);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_auth_timeout
 功能描述  : 认证超时处理
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
oal_uint32  hmac_sta_auth_timeout(hmac_vap_stru *pst_hmac_sta, oal_void *p_param)
{
    hmac_auth_rsp_stru            st_auth_rsp = {{0,},};

    /* and send it to the host.                                          */
    st_auth_rsp.us_status_code = HMAC_MGMT_TIMEOUT;

    /* Send the response to host now. */
    hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_AUTH_RSP, (oal_uint8 *)&st_auth_rsp);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_get_band
 功能描述  : 根据初始化的dev带宽能力和bss的带宽能力决定当前需要使用的带宽
 输入参数  :    en_dev_cap, en_bss_cap

 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
wlan_channel_bandwidth_enum_uint8 hmac_sta_get_band(wlan_bw_cap_enum_uint8 en_dev_cap, wlan_channel_bandwidth_enum_uint8 en_bss_cap)
{
    wlan_channel_bandwidth_enum_uint8       en_band;

    en_band = WLAN_BAND_WIDTH_20M;

    if((WLAN_BW_CAP_80M == en_dev_cap) &&
       (WLAN_BAND_WIDTH_80PLUSPLUS <= en_bss_cap))
    {
        /* 如果AP和STAUT都支持80M，则设置为AP一样 */
        en_band = en_bss_cap;
        return en_band;
    }

    switch (en_bss_cap)
    {
        case WLAN_BAND_WIDTH_40PLUS:
        case WLAN_BAND_WIDTH_80PLUSPLUS:
        case WLAN_BAND_WIDTH_80PLUSMINUS:
            if(WLAN_BW_CAP_40M <= en_dev_cap)
            {
                en_band = WLAN_BAND_WIDTH_40PLUS;
            }
            break;

        case WLAN_BAND_WIDTH_40MINUS:
        case WLAN_BAND_WIDTH_80MINUSPLUS:
        case WLAN_BAND_WIDTH_80MINUSMINUS:
            if(WLAN_BW_CAP_40M <= en_dev_cap)
            {
                en_band = WLAN_BAND_WIDTH_40MINUS;
            }
            break;

        default:
            en_band = WLAN_BAND_WIDTH_20M;
            break;
    }

    return en_band;
}


/*****************************************************************************
 函 数 名  : hmac_sta_update_join_req_params
 功能描述  : 根据join_request帧更新mib信息和填写相应寄存器
 输入参数  : hmac_vap_stru      *pst_hmac_vap,
             hmac_join_req_stru *pst_join_req
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月3日
    作    者   : 
    修改内容   : 新生成函数

 2.日    期   : 2014年4月7日
   作    者   : 
   修改内容   : 删除打印日志，整理错误码

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_sta_update_join_req_params(hmac_vap_stru *pst_hmac_vap,hmac_join_req_stru *pst_join_req)
{
    mac_vap_stru                   *pst_mac_vap;
    dmac_ctx_join_req_set_reg_stru *pst_reg_params;
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event;
    oal_uint32                      ul_ret;
    mac_device_stru                *pst_mac_device;
    wlan_mib_ieee802dot11_stru     *pst_mib_info;
    mac_cfg_mode_param_stru         st_cfg_mode;

    pst_mac_vap      = &(pst_hmac_vap->st_vap_base_info);
    pst_mib_info     = pst_mac_vap->pst_mib_info;
    if (OAL_PTR_NULL == pst_mib_info)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* 设置BSSID */
    mac_vap_set_bssid(pst_mac_vap, pst_join_req->st_bss_dscr.auc_bssid);

    /* 更新mib库对应的dot11BeaconPeriod值 */
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)(pst_join_req->st_bss_dscr.us_beacon_period);


    /* 更新mib库对应的ul_dot11CurrentChannel值*/
    mac_vap_set_current_channel(pst_mac_vap, pst_join_req->st_bss_dscr.st_channel.en_band, pst_join_req->st_bss_dscr.st_channel.uc_chan_number);

#ifdef _PRE_WLAN_FEATURE_11D
    /* 更新sta期望加入的国家字符串 */
    pst_hmac_vap->ac_desired_country[0] = pst_join_req->st_bss_dscr.ac_country[0];
    pst_hmac_vap->ac_desired_country[1] = pst_join_req->st_bss_dscr.ac_country[1];
    pst_hmac_vap->ac_desired_country[2] = pst_join_req->st_bss_dscr.ac_country[2];
#endif

    /* 更新mib库对应的ssid */
    oal_memcopy(pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID, pst_join_req->st_bss_dscr.ac_ssid, WLAN_SSID_MAX_LEN);
    pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID[WLAN_SSID_MAX_LEN - 1] = '\0';

    /* 更新频带、主20MHz信道号，与AP通信 DMAC切换信道时直接调用 */
    pst_mac_vap->st_channel.en_bandwidth   = hmac_sta_get_band(pst_mac_device->en_bandwidth_cap, pst_join_req->st_bss_dscr.en_channel_bandwidth);
    pst_mac_vap->st_channel.uc_chan_number = pst_join_req->st_bss_dscr.st_channel.uc_chan_number;
    pst_mac_vap->st_channel.en_band        = pst_join_req->st_bss_dscr.st_channel.en_band;

    /* 在STA未配置协议模式情况下，根据要关联的AP，更新mib库中对应的HT/VHT能力 */
    if (OAL_SWITCH_OFF == pst_hmac_vap->bit_sta_protocol_cfg)
    {
        oal_memset(&st_cfg_mode, 0, OAL_SIZEOF(mac_cfg_mode_param_stru));

        //TODO
        pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = pst_join_req->st_bss_dscr.en_ht_capable;
        pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = pst_join_req->st_bss_dscr.en_vht_capable;
        pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented = (pst_join_req->st_bss_dscr.en_ht_ldpc && pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated);
        pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented     = (pst_join_req->st_bss_dscr.en_ht_stbc && pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated );

        /* 关联2G AP，且2ght40禁止位为1时，不学习AP的HT 40能力 */
        if (!(WLAN_BAND_2G == pst_mac_vap->st_channel.en_band && pst_mac_vap->st_cap_flag.bit_disable_2ght40))
        {
            if(WLAN_BW_CAP_20M == pst_join_req->st_bss_dscr.en_bw_cap)
            {
                mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_FALSE);
            }
            else
            {
                mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_TRUE);
            }
        }

        /*根据要加入AP的协议模式更新STA侧速率集 */
        ul_ret = hmac_sta_get_user_protocol(&(pst_join_req->st_bss_dscr), &(st_cfg_mode.en_protocol));
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::hmac_sta_get_user_protocol fail %d.}", ul_ret);
            return ul_ret;
        }

        st_cfg_mode.en_band         = pst_join_req->st_bss_dscr.st_channel.en_band;
        st_cfg_mode.en_bandwidth    =  hmac_sta_get_band(pst_mac_device->en_bandwidth_cap, pst_join_req->st_bss_dscr.en_channel_bandwidth);
        st_cfg_mode.en_channel_idx  = pst_join_req->st_bss_dscr.st_channel.uc_chan_number;
        ul_ret = hmac_config_sta_update_rates(pst_mac_vap, &st_cfg_mode, (oal_void *)&pst_join_req->st_bss_dscr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::hmac_config_sta_update_rates fail %d.}", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_WLAN_FEATURE_WAPI
    /* wapi 需要降协议 */
    if(pst_join_req->st_bss_dscr.uc_wapi)
    {
        hmac_update_pcip_policy_prot_supplicant(pst_mac_vap, WLAN_80211_CIPHER_SUITE_WAPI);

        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::wapi prot fall!}");
    }
#endif

#if defined (_PRE_WLAN_FEATURE_WPA) || defined (_PRE_WLAN_FEATURE_WPA2)
    /* 更新mib库对应的加密相关值 */
    ul_ret = hmac_update_current_join_req_parms_11i(pst_mac_vap, &pst_join_req->st_bss_dscr.st_bss_sec_info);
    if(ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::update security parameter failed.}");
        return ul_ret;
    }
#ifndef _PRE_WIFI_DMT
    st_cfg_mode.en_protocol  = pst_mac_vap->en_protocol;
    st_cfg_mode.en_band      = pst_mac_vap->st_channel.en_band;
    st_cfg_mode.en_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
    st_cfg_mode.en_channel_idx  = pst_join_req->st_bss_dscr.st_channel.uc_chan_number;
    hmac_config_sta_update_rates(pst_mac_vap, &st_cfg_mode, (oal_void *)&pst_join_req->st_bss_dscr);
#endif
#endif

    /* STA首先以20MHz运行，如果要切换到40 or 80MHz运行，需要满足一下条件: */
    /* (1) 用户支持40 or 80MHz运行 */
    /* (2) AP支持40 or 80MHz运行(HT Supported Channel Width Set = 1 && VHT Supported Channel Width Set = 0) */
    /* (3) AP在40 or 80MHz运行(SCO = SCA or SCB && VHT Channel Width = 1) */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    pst_mac_vap->st_channel.en_bandwidth   = WLAN_BAND_WIDTH_20M;
#endif
    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &(pst_mac_vap->st_channel.uc_idx));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::band and channel_num are not compatible.band[%d], channel_num[%d]}",
                        pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number);
        return ul_ret;
    }

    /* 更新协议相关信息，包括WMM P2P 11I 20/40M等 */
    hmac_update_join_req_params_prot_sta(pst_hmac_vap, pst_join_req);
    /* 入网优化，不同频段下的能力不一样 */
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_TRUE);
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    /* 记录主sta的信号索引，proxysta扫描时仅扫描与此信道索引对应的信道 */
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        pst_mac_device->uc_sta0_chan_idx = pst_mac_vap->st_channel.uc_idx;
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&
            (OAL_FALSE== pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            return OAL_SUCC;
        }
    }
#endif


    if (0 == hmac_calc_up_ap_num(pst_mac_device))
    {
        pst_mac_device->uc_max_channel   = pst_mac_vap->st_channel.uc_chan_number;
        pst_mac_device->en_max_band      = pst_mac_vap->st_channel.en_band;
        pst_mac_device->en_max_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
    }

    /* 抛事件到DMAC, 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_sta_update_join_req_params::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG,
                       OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    pst_reg_params = (dmac_ctx_join_req_set_reg_stru *)pst_event->auc_event_data;

    /* 设置需要写入寄存器的BSSID信息 */
    oal_set_mac_addr(pst_reg_params->auc_bssid, pst_join_req->st_bss_dscr.auc_bssid);

    /* 填写信道相关信息 */
    pst_reg_params->st_current_channel.uc_chan_number = pst_mac_vap->st_channel.uc_chan_number;
    pst_reg_params->st_current_channel.en_band        = pst_mac_vap->st_channel.en_band;
    pst_reg_params->st_current_channel.en_bandwidth   = pst_mac_vap->st_channel.en_bandwidth;
    pst_reg_params->st_current_channel.uc_idx         = pst_mac_vap->st_channel.uc_idx;

    /* 设置beaocn period信息 */
    pst_reg_params->us_beacon_period      = (pst_join_req->st_bss_dscr.us_beacon_period);

    /* 同步FortyMHzOperationImplemented */
    pst_reg_params->en_dot11FortyMHzOperationImplemented   = mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap);

    /* 设置beacon filter关闭 */
    pst_reg_params->ul_beacon_filter    = OAL_FALSE;

    /* 设置no frame filter打开 */
    pst_reg_params->ul_non_frame_filter = OAL_TRUE;

    /* 下发ssid */
    oal_memcopy(pst_reg_params->auc_ssid, pst_join_req->st_bss_dscr.ac_ssid, WLAN_SSID_MAX_LEN);
    pst_reg_params->auc_ssid[WLAN_SSID_MAX_LEN - 1] = '\0';

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_wait_asoc_timeout
 功能描述  : 关联超时处理函数
 输入参数  : hmac_vap_stru *pst_hmac_sta, oal_void *p_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_sta_wait_asoc_timeout(hmac_vap_stru *pst_hmac_sta, oal_void *p_param)
{
    hmac_asoc_rsp_stru            st_asoc_rsp = {0};

    if ((OAL_PTR_NULL == pst_hmac_sta)|| (OAL_PTR_NULL == p_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_sta_wait_asoc_timeout::param null,%d %d.}", pst_hmac_sta,p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写关联结果 */
    st_asoc_rsp.en_result_code = HMAC_MGMT_TIMEOUT;

    /* 关联超时失败,原因码上报wpa_supplicant */
    st_asoc_rsp.en_status_code = MAC_AUTH_TIMEOUT;

    /* 发送关联结果给SME */
    hmac_send_rsp_to_sme_sta(pst_hmac_sta, HMAC_SME_ASOC_RSP, (oal_uint8 *)&st_asoc_rsp);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_handle_disasoc_rsp_sta
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_sta_handle_disassoc_rsp(hmac_vap_stru *pst_hmac_vap, oal_uint16 us_disasoc_reason_code)
{
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;

    /* 抛加入完成事件到WAL */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint16));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_sta_handle_disassoc_rsp::pst_event_mem null.}");
        return;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                     FRW_EVENT_TYPE_HOST_CTX,
                     HMAC_HOST_CTX_EVENT_SUB_TYPE_DISASOC_COMP_STA,
                     OAL_SIZEOF(oal_uint16),
                     FRW_EVENT_PIPELINE_STAGE_0,
                     pst_hmac_vap->st_vap_base_info.uc_chip_id,
                     pst_hmac_vap->st_vap_base_info.uc_device_id,
                     pst_hmac_vap->st_vap_base_info.uc_vap_id);

    *((oal_uint16 *)pst_event->auc_event_data) = us_disasoc_reason_code;      /* 事件payload填写的是错误码 */

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return;
}

/*****************************************************************************
函 数 名  : hmac_sta_rx_deauth_req
功能描述  : 处理接收去认证帧
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
OAL_STATIC oal_uint32 hmac_sta_rx_deauth_req(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_mac_hdr, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint8       auc_bssid[6]            = {0};
    hmac_user_stru *pst_hmac_user_vap       = OAL_PTR_NULL;
    oal_uint16      us_user_idx             = 0xffff;
    oal_uint32      ul_ret;
    oal_uint8      *puc_da;
    oal_uint8      *puc_sa = OAL_PTR_NULL;
    oal_uint32      ul_ret_del_user;


    if (OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == puc_mac_hdr)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_sta_rx_deauth_req::param null,%d %d.}", pst_hmac_vap, puc_mac_hdr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 增加接收到去认证帧或者去关联帧时的维测信息 */
    mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                     "{hmac_sta_rx_deauth_req::Because of err_code[%d], received deauth or disassoc frame frome source addr, sa xx:xx:xx:%2x:%2x:%2x.}",
                     *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)), puc_sa[3], puc_sa[4], puc_sa[5]);

    mac_get_address2(puc_mac_hdr, auc_bssid);

    ul_ret = mac_vap_find_user_by_macaddr(&pst_hmac_vap->st_vap_base_info, auc_bssid, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                         "{hmac_sta_rx_deauth_req::find user failed[%d],other bss deauth frame!}", ul_ret);
        /* 没有查到对应的USER,发送去认证消息 */
        //hmac_mgmt_send_deauth_frame(&(pst_hmac_vap->st_vap_base_info), auc_bssid, MAC_NOT_AUTHED, OAL_FALSE);
        return ul_ret;
    }
    pst_hmac_user_vap = mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user_vap)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                       "{hmac_sta_rx_deauth_req::pst_hmac_user_vap null.}");
        /* 没有查到对应的USER,发送去认证消息 */
        hmac_mgmt_send_deauth_frame(&(pst_hmac_vap->st_vap_base_info), auc_bssid, MAC_NOT_AUTHED, OAL_FALSE);

        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);
        /* 上报内核sta已经和某个ap去关联 */
	hmac_sta_handle_disassoc_rsp(pst_hmac_vap, *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)));
        return OAL_FAIL;
    }

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    /*检查是否需要发送SA query request*/
    if ((MAC_USER_STATE_ASSOC == pst_hmac_user_vap->st_user_base_info.en_user_asoc_state) &&
        (OAL_SUCC == hmac_pmf_check_err_code(&pst_hmac_user_vap->st_user_base_info, en_is_protected, puc_mac_hdr)))
    {
       /*在关联状态下收到未加密的ReasonCode 6/7需要启动SA Query流程*/
       ul_ret = hmac_start_sa_query(&pst_hmac_vap->st_vap_base_info, pst_hmac_user_vap, pst_hmac_user_vap->st_user_base_info.st_cap_info.bit_pmf_active);
       if(OAL_SUCC != ul_ret)
       {
           return OAL_ERR_CODE_PMF_SA_QUERY_START_FAIL;
       }

       return OAL_SUCC;
    }

#endif

    /*如果该用户的管理帧加密属性不一致，丢弃该报文*/
    mac_rx_get_da((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_da);
    if ((OAL_TRUE != ETHER_IS_MULTICAST(puc_da)) &&
       (en_is_protected != pst_hmac_user_vap->st_user_base_info.st_cap_info.bit_pmf_active))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                       "{hmac_sta_rx_deauth_req::PMF check failed.}");

        return OAL_FAIL;
    }

    hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);


    /* TBD 上报system error 复位 mac */

    /* 删除user */
    ul_ret_del_user = hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user_vap);
    if ( OAL_SUCC != ul_ret_del_user)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                       "{hmac_sta_rx_deauth_req::hmac_user_del failed.}");

        /* 上报内核sta已经和某个ap去关联 */
	hmac_sta_handle_disassoc_rsp(pst_hmac_vap, *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)));
        return OAL_FAIL;
    }

    /* 上报内核sta已经和某个ap去关联 */
    hmac_sta_handle_disassoc_rsp(pst_hmac_vap, *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_update_ht_params
 功能描述  : STA收到Beacon帧后，处理HT相关信息元素
 输入参数  : pst_mac_vap    : MAC VAP结构体指针，指向STA
             puc_payload    : 指向Beacon帧体的指针
             us_frame_len   : Beacon帧体的长度(不包括帧头)
             us_frame_offset: Beacon帧中第一个IE相对帧体地址的偏移
 输出参数  : pst_mac_user   : MAC USER结构体指针，指向AP
 返 回 值  : oal_bool_enum_uint8:相关信息是否有改变，是否需要同步?
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_sta_up_update_ht_params(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len,
                                                  oal_uint16 us_frame_offset, mac_user_stru *pst_mac_user)
{
    oal_uint16             us_index = us_frame_offset;
    mac_user_ht_hdl_stru   st_ht_hdl;
    oal_uint32             ul_change = HMAC_NO_CHANGE;

#if 0 /*曹海彬屏蔽， 保证non-ht站点也可以解析ht operation字段*/
    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
    {
        return;
    }
#endif

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);

    while (us_index < us_frame_len)
    {
        if (MAC_EID_HT_OPERATION == puc_payload[us_index])
        {
            ul_change |= hmac_proc_ht_opern_ie(pst_mac_vap, &puc_payload[us_index], pst_mac_user);
        }
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        else if (MAC_EID_OBSS_SCAN == puc_payload[us_index])
        {
            /* 处理 Overlapping BSS Scan Parameters IE */
            hmac_ie_proc_obss_scan_ie(pst_mac_vap, &puc_payload[us_index]);
        }
#endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

        us_index += puc_payload[us_index + 1] + MAC_IE_HDR_LEN;
    }

    if (0 != OAL_MEMCMP((oal_uint8 *)(&st_ht_hdl), (oal_uint8 *)(&pst_mac_user->st_ht_hdl), OAL_SIZEOF(mac_user_ht_hdl_stru)))
    {
        return (ul_change | HMAC_HT_CHANGE);
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_update_vht_params
 功能描述  : STA收到Beacon帧后，处理VHT相关信息元素
 输入参数  : pst_mac_vap    : MAC VAP结构体指针，指向STA
             puc_payload    : 指向Beacon帧体的指针
             us_frame_len   : Beacon帧体的长度(不包括帧头)
             us_frame_offset: Beacon帧中第一个IE相对帧体地址的偏移
 输出参数  : MAC USER结构体指针，指向AP
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_sta_up_update_vht_params(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len,
                                                   oal_uint16 us_frame_offset, mac_user_stru *pst_mac_user)
{
    oal_uint16        us_index = us_frame_offset;
    mac_vht_hdl_stru  st_vht_hdl;
    oal_uint32        ul_change = HMAC_NO_CHANGE;

    /* 支持11ac，才进行后续的处理 */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return ul_change;
    }

    mac_user_get_vht_hdl(pst_mac_user, &st_vht_hdl);

    while (us_index < us_frame_len)
    {
        if (MAC_EID_VHT_OPERN == puc_payload[us_index])
        {
            ul_change = hmac_ie_proc_vht_opern_ie(pst_mac_vap, &puc_payload[us_index], pst_mac_user);
        }

        us_index += puc_payload[us_index + 1] + MAC_IE_HDR_LEN;
    }

    if (0 != OAL_MEMCMP((oal_uint8 *)(&st_vht_hdl), (oal_uint8 *)(&pst_mac_user->st_vht_hdl), OAL_SIZEOF(mac_vht_hdl_stru)))
    {
        return (HMAC_VHT_CHANGE | ul_change);
    }

    return ul_change;
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_beacon
 功能描述  : sta up状态接收beacon帧处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_sta_up_rx_beacon(hmac_vap_stru *pst_hmac_vap_sta, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_rx_ctl_stru            *pst_rx_info;
    mac_ieee80211_frame_stru   *pst_mac_hdr;
    oal_uint32                  ul_ret;
    oal_uint16                  us_frame_len;
    oal_uint16                  us_frame_offset;
    oal_uint8                  *puc_frame_body;
    oal_uint8                   uc_frame_sub_type;
    hmac_user_stru             *pst_hmac_user;
    oal_uint8                   auc_addr_sa[WLAN_MAC_ADDR_LEN];
    oal_uint16                  us_user_idx;
    oal_uint32                  ul_change_flag = HMAC_NO_CHANGE;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_h2d_protection_stru     st_h2d_prot;
#endif
#ifdef _PRE_WLAN_CHIP_TEST
    oal_uint8                   *puc_tim_elm;
#endif
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                  *puc_txbf_vendor_ie;
#endif


    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    pst_mac_hdr         = (mac_ieee80211_frame_stru *)(pst_rx_info->pul_mac_hdr_start_addr);
    puc_frame_body      = (oal_uint8* )pst_mac_hdr + pst_rx_info->uc_mac_header_len;
    us_frame_len        = pst_rx_info->us_frame_len - pst_rx_info->uc_mac_header_len; /*帧体长度*/

    us_frame_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    uc_frame_sub_type = mac_get_frame_sub_type((oal_uint8 *)pst_mac_hdr);

    /* 来自其它bss的Beacon不做处理 */
    ul_ret = oal_compare_mac_addr(pst_hmac_vap_sta->st_vap_base_info.auc_bssid, pst_mac_hdr->auc_address3);
    if(0 != ul_ret)
    {
        return OAL_SUCC;
    }

    /* 获取管理帧的源地址SA */
    mac_get_address2((oal_uint8 *)pst_mac_hdr, auc_addr_sa);

    /* 根据SA 地地找到对应AP USER结构 */
    ul_ret = mac_vap_find_user_by_macaddr(&(pst_hmac_vap_sta->st_vap_base_info), auc_addr_sa, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                        "{hmac_sta_up_rx_beacon::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
        return ul_ret;
    }
    pst_hmac_user = mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{hmac_sta_up_rx_beacon::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*TIM IE处理*/
#ifdef _PRE_WLAN_CHIP_TEST
    //puc_tim_elm = mac_get_tim_ie((oal_uint8*)pst_mac_hdr, us_frame_len, MAC_TAG_PARAM_OFFSET);
    puc_tim_elm = mac_find_ie(MAC_EID_TIM, puc_frame_body + us_frame_offset, us_frame_len - us_frame_offset);
    if (OAL_PTR_NULL != puc_tim_elm)
    {
        pst_hmac_vap_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = puc_tim_elm[3];
        //pst_hmac_vap_sta->st_vap_base_info.uc_dtim_count = puc_tim_elm[2];
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    OAL_MEMZERO(&st_h2d_prot, OAL_SIZEOF(st_h2d_prot));
    st_h2d_prot.st_user_cap_info.bit_barker_preamble_mode = pst_hmac_user->st_user_base_info.st_cap_info.bit_barker_preamble_mode;

    /*处理ERP信息元素*/
    hmac_sta_up_process_erp_ie(puc_frame_body, us_frame_len, us_frame_offset, pst_hmac_user);


    /*如果barker_preamble发生变化，则同步到dmac*/
    if (st_h2d_prot.st_user_cap_info.bit_barker_preamble_mode !=
        pst_hmac_user->st_user_base_info.st_cap_info.bit_barker_preamble_mode)
    {
        st_h2d_prot.ul_sync_mask |= H2D_SYNC_MASK_BARK_PREAMBLE;
        st_h2d_prot.st_user_cap_info.bit_barker_preamble_mode =
            pst_hmac_user->st_user_base_info.st_cap_info.bit_barker_preamble_mode;
        st_h2d_prot.us_user_idx = us_user_idx;

        hmac_config_set_protection(&(pst_hmac_vap_sta->st_vap_base_info),
            OAL_SIZEOF(st_h2d_prot), (oal_uint8*)&st_h2d_prot);
    }
#else
    hmac_sta_up_process_erp_ie(puc_frame_body, us_frame_len, us_frame_offset, pst_hmac_user);
#endif

    /*处理HT 相关信息元素*/
    /* hmac_sta_up_process_ht_operation_ie(puc_frame_body, us_frame_len, us_frame_offset, pst_hmac_user); */
    ul_change_flag |= hmac_sta_up_update_ht_params(&(pst_hmac_vap_sta->st_vap_base_info), puc_frame_body, us_frame_len, us_frame_offset, &(pst_hmac_user->st_user_base_info));

    /*更新sta的保护级别*/
    ul_ret = hmac_protection_update_mode_sta(&(pst_hmac_vap_sta->st_vap_base_info), pst_hmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                        "{hmac_sta_up_rx_beacon::hmac_protection_update_mode_sta failed[%d].}", ul_ret);
    }

#ifdef _PRE_WLAN_FEATURE_TXBF
    /* 更新11n txbf能力 */
    puc_txbf_vendor_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_EID_11NTXBF, (oal_uint8 *)pst_mac_hdr + MAC_TAG_PARAM_OFFSET, us_frame_len - us_frame_offset);
    hmac_mgmt_update_11ntxbf_cap(puc_txbf_vendor_ie, pst_hmac_user);
#endif


     /* 处理 VHT 相关信息元素 */
    ul_change_flag |= hmac_sta_up_update_vht_params(&(pst_hmac_vap_sta->st_vap_base_info), puc_frame_body, us_frame_len, us_frame_offset, &(pst_hmac_user->st_user_base_info));

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    /* 处理Operating Mode Notification 信息元素 */
    ul_ret = hmac_check_opmode_notify(pst_hmac_vap_sta, (oal_uint8 *)pst_mac_hdr, puc_frame_body, us_frame_offset, us_frame_len, pst_hmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{hmac_sta_up_rx_beacon::hmac_check_opmode_notify failed[%d].}", ul_ret);
    }
#endif

    if ((HMAC_HT_CHANGE & ul_change_flag) || (HMAC_VHT_CHANGE & ul_change_flag))
    {
        ul_ret = hmac_config_user_rate_info_syn(&(pst_hmac_vap_sta->st_vap_base_info), &pst_hmac_user->st_user_base_info);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                           "{hmac_sta_up_rx_beacon::hmac_config_user_rate_info_syn failed[%d].}", ul_ret);
        }
    }

    if (HMAC_BW_CHANGE & ul_change_flag)
    {
        hmac_sta_update_mac_user_info(pst_hmac_user, us_user_idx);

        OAM_WARNING_LOG3(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_sta_up_rx_beacon::change BW. ul_change[0x%x], uc_channel[%d], en_bandwidth[%d].}",
                       ul_change_flag,
                       pst_hmac_vap_sta->st_vap_base_info.st_channel.uc_chan_number,
                       pst_hmac_vap_sta->st_vap_base_info.st_channel.en_bandwidth);
        hmac_chan_sync(&(pst_hmac_vap_sta->st_vap_base_info),
                        pst_hmac_vap_sta->st_vap_base_info.st_channel.uc_chan_number,
                        pst_hmac_vap_sta->st_vap_base_info.st_channel.en_bandwidth,
                        OAL_TRUE);
    }

    /* 评估是否需要进行带宽切换 */
    //hmac_chan_reval_bandwidth_sta(&pst_hmac_vap_sta->st_vap_base_info, ul_change_flag);

    hmac_chan_update_csw_info(&pst_hmac_vap_sta->st_vap_base_info, puc_frame_body, us_frame_len, us_frame_offset);

    /* 更新edca参数 */
    hmac_sta_up_update_edca_params(puc_frame_body, us_frame_len, us_frame_offset, pst_hmac_vap_sta, uc_frame_sub_type, pst_hmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_handle_tbtt_chan_mgmt_sta
 功能描述  : STA侧TBTT中断中进行信道管理
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针，指向sta
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#if 0
OAL_STATIC oal_void  hmac_handle_tbtt_chan_mgmt_sta(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru *pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        return;
    }

    /* 如果AP发送的CSA IE中的"信道切换计数"为零，则立即切换信道 */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero)
    {
        if (pst_hmac_vap->us_link_loss > WLAN_LINK_LOSS_THRESHOLD)
        {
            hmac_chan_sta_switch_channel(pst_mac_vap);
            pst_hmac_vap->us_link_loss = 0;
        }
    }

    /* 信道切换已经完成。现在新信道上等待接收AP发送的Beacon帧 */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_for_ap)
    {
        /* 等待一段时间后，在新信道上恢复硬件发送(即便这时AP有可能还没有切换至新信道) */
        if (pst_hmac_vap->us_link_loss > WLAN_LINK_LOSS_THRESHOLD)
        {
            pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = OAL_FALSE;
            hmac_chan_enable_machw_tx(pst_mac_vap);

            pst_hmac_vap->us_link_loss = 0;
        }
    }

    /* 如果AP发送的CSA IE中的"信道切换计数"不为零，则每一次TBTT中断中减一 */
    if (pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt > 0)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt--;

        if (0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)
        {
            if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel)
            {
                hmac_chan_sta_switch_channel(pst_mac_vap);
            }
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_ch_switch
 功能描述  : STA up状态接收Channel Switch Announcement帧处理
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             pst_netbuf : 包含Channel Switch Announcement帧的netbuf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_sta_up_rx_ch_switch(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint16          us_index;
    oal_uint8          *puc_data;
    oal_uint16          us_framebody_len;

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_sta_up_rx_ch_switch::Ignoring Spectrum Management frames.}");
        return;
    }

    pst_rx_ctrl      = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    us_framebody_len = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* 获取帧体指针 */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    us_index = MAC_ACTION_OFFSET_ACTION + 1;

    while (us_index < us_framebody_len)
    {
        if (MAC_EID_CHANSWITCHANN == puc_data[us_index])
        {
            hmac_ie_proc_ch_switch_ie(pst_mac_vap, &puc_data[us_index], MAC_EID_CHANSWITCHANN);
        }
        else if (MAC_EID_SEC_CH_OFFSET == puc_data[us_index])
        {
            if (MAC_SEC_CH_OFFSET_IE_LEN > puc_data[us_index + 1])
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_sta_up_rx_ch_switch::invalid sec chan offset ie len[%d]}", puc_data[us_index + 1]);
                us_index += MAC_IE_HDR_LEN + puc_data[us_index + 1];
                continue;
            }
            //TODO - 如果通道发生改变了，不需要切信道么?
            pst_mac_vap->st_ch_switch_info.en_new_bandwidth = mac_get_bandwidth_from_sco(puc_data[us_index + MAC_IE_HDR_LEN]);
        }
        else if (MAC_EID_WIDE_BW_CH_SWITCH == puc_data[us_index])
        {
            if (OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
            {
                hmac_ie_proc_wide_bandwidth_ie(pst_mac_vap, &puc_data[us_index]);
            }
        }

        us_index += MAC_IE_HDR_LEN + puc_data[us_index + 1];
    }
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_ext_ch_switch
 功能描述  : STA up状态接收Extended Channel Switch Announcement帧处理
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             pst_netbuf : 包含Extended Channel Switch Announcement帧的netbuf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_sta_up_rx_ext_ch_switch(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint16          us_index;
    oal_uint8          *puc_data;
    oal_uint16          us_framebody_len;
    oal_uint8          *puc_wide_bw_ch_switch_ie = OAL_PTR_NULL;

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_sta_up_rx_ext_ch_switch::Ignoring Spectrum Management frames.}");
        return;
    }

    pst_rx_ctrl      = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    us_framebody_len = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* 获取帧体指针 */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    hmac_ie_proc_ch_switch_ie(pst_mac_vap, puc_data, MAC_EID_EXTCHANSWITCHANN);

    /* 如果不支持VHT，则忽略后续的Wide Bandwidth Channel Switch IE */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return;
    }

    us_index = 6;

    puc_wide_bw_ch_switch_ie = mac_find_ie(MAC_EID_WIDE_BW_CH_SWITCH, &puc_data[us_index], (oal_int32)(us_framebody_len - us_index));
    if (OAL_PTR_NULL != puc_wide_bw_ch_switch_ie)
    {
        hmac_ie_proc_wide_bandwidth_ie(pst_mac_vap, puc_wide_bw_ch_switch_ie);
    }
}


/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_action
 功能描述  : STA在UP状态下的接收ACTION帧处理
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针
             pst_netbuf  : Action帧所在的netbuf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_sta_up_rx_action(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected)
{
    dmac_rx_ctl_stru               *pst_rx_ctrl;
    oal_uint8                      *puc_data;
    mac_ieee80211_frame_stru       *pst_frame_hdr;          /* 保存mac帧的指针 */
    hmac_user_stru                 *pst_hmac_user;
#ifdef _PRE_WLAN_FEATURE_P2P
    oal_uint8                      *puc_p2p0_mac_addr;
#endif
    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* 获取帧头信息 */
    pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P0设备所接受的action全部上报 */
    puc_p2p0_mac_addr = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID;
    if (0 == oal_compare_mac_addr(pst_frame_hdr->auc_address1, puc_p2p0_mac_addr))
    {
        hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
    }
#endif

    /* 获取发送端的用户指针 */
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_hmac_vap->st_vap_base_info, pst_frame_hdr->auc_address2);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_sta_up_rx_action::mac_vap_find_user_by_macaddr failed.}");
        return;
    }

    /* 获取帧体指针 */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* Category */
    switch (puc_data[MAC_ACTION_OFFSET_CATEGORY])
    {
        case MAC_ACTION_CATEGORY_BA:
        {
            switch(puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_BA_ACTION_ADDBA_REQ:
                    hmac_mgmt_rx_addba_req(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:
                    hmac_mgmt_rx_addba_rsp(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                case MAC_BA_ACTION_DELBA:
                    hmac_mgmt_rx_delba(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_SPECMGMT:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_SPEC_CH_SWITCH_ANNOUNCE:
                    hmac_sta_up_rx_ch_switch(&(pst_hmac_vap->st_vap_base_info), pst_netbuf);
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_WNM:
        #ifdef _PRE_WLAN_FEATURE_HS20
                /* 上报WNM Notification Request Action帧 */
                 hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
        #endif
             break;

        case MAC_ACTION_CATEGORY_PUBLIC:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_PUB_COEXT_MGMT:
                    hmac_sta_up_rx_2040_coext(&(pst_hmac_vap->st_vap_base_info), pst_netbuf);
                    break;
            #endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

                case MAC_PUB_EX_CH_SWITCH_ANNOUNCE:
                    hmac_sta_up_rx_ext_ch_switch(&(pst_hmac_vap->st_vap_base_info), pst_netbuf);
                    break;

                case MAC_PUB_VENDOR_SPECIFIC:
            #ifdef _PRE_WLAN_FEATURE_P2P
                /*查找OUI-OUI type值为 50 6F 9A - 09 (WFA P2P v1.0)  */
                /* 并用hmac_rx_mgmt_send_to_host接口上报 */
                    if (OAL_TRUE == mac_ie_check_p2p_action(puc_data + MAC_ACTION_OFFSET_ACTION))
                    {
                       hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
                    }
            #endif
                    break;

                case MAC_PUB_GAS_INIT_RESP:
                case MAC_PUB_GAS_COMBAK_RESP:
            #ifdef _PRE_WLAN_FEATURE_HS20
                /*上报GAS查询的ACTION帧 */
                 hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
            #endif
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_HT:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_HT_ACTION_NOTIFY_CHANNEL_WIDTH:
                    hmac_rx_notify_channel_width(&(pst_hmac_vap->st_vap_base_info), pst_netbuf);
                    break;
            #endif
                case MAC_HT_ACTION_BUTT:
                default:
                    break;
            }
        }
       break;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
        case MAC_ACTION_CATEGORY_SA_QUERY:
        {
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_SA_QUERY_ACTION_REQUEST:
                    hmac_rx_sa_query_req(pst_hmac_vap, pst_netbuf, en_is_protected);
                    break;
                case MAC_SA_QUERY_ACTION_RESPONSE:
                    hmac_rx_sa_query_rsp(pst_hmac_vap, pst_netbuf, en_is_protected);
                    break;

                default:
                    break;
            }
        }
        break;
#endif
        case MAC_ACTION_CATEGORY_VHT:
        {
            switch(puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
                case MAC_VHT_ACTION_OPREATE_MODE_NOTIFY:
                    hmac_mgmt_rx_opmode_notify_frame(pst_hmac_vap, pst_netbuf);
                    break;
            #endif
                case MAC_VHT_ACTION_BUTT:
                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_VENDOR:
        {
    #ifdef _PRE_WLAN_FEATURE_P2P
        /*查找OUI-OUI type值为 50 6F 9A - 09 (WFA P2P v1.0)  */
        /* 并用hmac_rx_mgmt_send_to_host接口上报 */
            if (OAL_TRUE == mac_ie_check_p2p_action(puc_data + MAC_ACTION_OFFSET_CATEGORY))
            {
               hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
            }
    #endif
        }
        break;
#ifdef _PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
        case MAC_ACTION_CATEGORY_FAST_BSS_TRANSITION:
        {
            hmac_roam_rx_ft_action(pst_hmac_vap, pst_netbuf);
            break;
        }
#endif //_PRE_WLAN_FEATURE_11R
#endif //_PRE_WLAN_FEATURE_ROAM

        default:
        break;
    }
}

/*****************************************************************************
 函 数 名  : hmac_sta_up_rx_mgmt
 功能描述  : AP在UP状态下的接收管理帧处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_sta_up_rx_mgmt(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param)
{
    dmac_wlan_crx_event_stru   *pst_mgmt_rx_event;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_mac_hdr;
    oal_uint8                   uc_mgmt_frm_type;
    oal_bool_enum_uint8         en_is_protected = OAL_FALSE;

    if (OAL_PTR_NULL == pst_hmac_vap_sta || OAL_PTR_NULL == p_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_sta_up_rx_mgmt::param null,%d %d.}", pst_hmac_vap_sta, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mgmt_rx_event   = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    puc_mac_hdr         = (oal_uint8 *)(pst_rx_info->pul_mac_hdr_start_addr);
    //en_is_protected     = (pst_rx_ctrl->st_rx_status.bit_cipher_protocol_type == hal_cipher_suite_to_ctype(WLAN_80211_CIPHER_SUITE_CCMP)) ? OAL_TRUE : OAL_FALSE;
    en_is_protected     = mac_get_protectedframe(puc_mac_hdr);

    /*Bar frame proc here*/
    if (WLAN_FC0_TYPE_CTL == mac_get_frame_type(puc_mac_hdr))
    {
        uc_mgmt_frm_type = mac_get_frame_sub_type(puc_mac_hdr);
        if (WLAN_BLOCKACK_REQ == (uc_mgmt_frm_type >> 4))
        {
            hmac_up_rx_bar(pst_hmac_vap_sta, pst_rx_ctrl, pst_mgmt_rx_event->pst_netbuf);
        }
    }

    /* AP在UP状态下 接收到的各种管理帧处理 */
    uc_mgmt_frm_type = mac_get_frame_sub_type(puc_mac_hdr);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(OAL_TRUE == g_ul_print_wakeup_mgmt)
    {
        g_ul_print_wakeup_mgmt = OAL_FALSE;
        OAM_WARNING_LOG1(pst_hmac_vap_sta->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_sta_up_rx_mgmt::wakeup mgmt type[0x%x]}",uc_mgmt_frm_type);
    }
#endif

    switch (uc_mgmt_frm_type)
    {
        case WLAN_FC0_SUBTYPE_DEAUTH:
        case WLAN_FC0_SUBTYPE_DISASSOC:
            hmac_sta_rx_deauth_req(pst_hmac_vap_sta, puc_mac_hdr, en_is_protected);
            break;

        case WLAN_FC0_SUBTYPE_BEACON:
            hmac_sta_up_rx_beacon(pst_hmac_vap_sta, pst_mgmt_rx_event->pst_netbuf);
            break;

        case WLAN_FC0_SUBTYPE_ACTION:
            hmac_sta_up_rx_action(pst_hmac_vap_sta, pst_mgmt_rx_event->pst_netbuf, en_is_protected);
            break;
        default:
            break;
    }

    return OAL_SUCC;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_check_capability_mac_phy_supplicant);
/*lint +e578*//*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

