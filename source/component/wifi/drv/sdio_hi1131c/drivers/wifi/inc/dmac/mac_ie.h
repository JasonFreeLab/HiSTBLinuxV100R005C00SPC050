/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_ie.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年1月8日
  最近修改   :
  功能描述   : mac_ie.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_IE_H__
#define __MAC_IE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "wlan_mib.h"
#include "wlan_types.h"
#include "mac_user.h"
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_IE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 inline函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : mac_get_bandwidth_from_sco
 功能描述  : 根据"次信道偏移量"获取对应的带宽模式
 输入参数  : en_sec_chan_offset: 次信道偏移量
 输出参数  : 无
 返 回 值  : 带宽模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_channel_bandwidth_enum_uint8  mac_get_bandwidth_from_sco(mac_sec_ch_off_enum_uint8 en_sec_chan_offset)
{
    switch (en_sec_chan_offset)
    {
        case MAC_SCA:   /* Secondary Channel Above */
            return WLAN_BAND_WIDTH_40PLUS;

        case MAC_SCB:   /* Secondary Channel Below */
            return WLAN_BAND_WIDTH_40MINUS;

        default:        /* No Secondary Channel    */
            return WLAN_BAND_WIDTH_20M;
    }
}

/*****************************************************************************
 函 数 名  : mac_get_sco_from_bandwidth
 功能描述  : 根据"带宽模式"获取对应的"次信道偏移量"
 输入参数  : en_bandwidth: 带宽模式
 输出参数  : 无
 返 回 值  : 次信道偏移量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_sec_ch_off_enum_uint8  mac_get_sco_from_bandwidth(wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    switch (en_bandwidth)
    {
        case WLAN_BAND_WIDTH_40PLUS:
        case WLAN_BAND_WIDTH_80PLUSPLUS:
        case WLAN_BAND_WIDTH_80PLUSMINUS:
            return MAC_SCA;

        case WLAN_BAND_WIDTH_40MINUS:
        case WLAN_BAND_WIDTH_80MINUSPLUS:
        case WLAN_BAND_WIDTH_80MINUSMINUS:
            return MAC_SCB;

        default:
            return MAC_SCN;
    }
}

/*****************************************************************************
 函 数 名  : mac_get_bandwith_from_center_freq_seg0
 功能描述  : 根据信道中心频点获取对应的"带宽模式"
 输入参数  : uc_channel         : 信道号
             uc_chan_center_freq: 信道中心频点
 输出参数  : 无
 返 回 值  : 带宽模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_channel_bandwidth_enum_uint8  mac_get_bandwith_from_center_freq_seg0(oal_uint8 uc_channel, oal_uint8 uc_chan_center_freq)
{
    switch (uc_chan_center_freq - uc_channel)
    {
        case 6:
            /***********************************************************************
            | 主20 | 从20 | 从40       |
                          |
                          |中心频率相对于主20偏6个信道
            ************************************************************************/
            return WLAN_BAND_WIDTH_80PLUSPLUS;

        case -2:
            /***********************************************************************
            | 从40        | 主20 | 从20 |
                          |
                          |中心频率相对于主20偏-2个信道
            ************************************************************************/
            return WLAN_BAND_WIDTH_80PLUSMINUS;

        case 2:
            /***********************************************************************
            | 从20 | 主20 | 从40       |
                          |
                          |中心频率相对于主20偏2个信道
            ************************************************************************/
            return  WLAN_BAND_WIDTH_80MINUSPLUS;

        case -6:
            /***********************************************************************
            | 从40        | 从20 | 主20 |
                          |
                          |中心频率相对于主20偏-6个信道
            ************************************************************************/
            return WLAN_BAND_WIDTH_80MINUSMINUS;

        default:
            return 0;
    }
}

/*****************************************************************************
  11 函数声明
*****************************************************************************/
extern oal_void  mac_ie_get_vht_rx_mcs_map(mac_rx_max_mcs_map_stru    *pst_mac_rx_mcs_sta,
                                               mac_rx_max_mcs_map_stru    *pst_mac_rx_mcs_ap);
extern  wlan_mib_mimo_power_save_enum_uint8 mac_ie_proc_sm_power_save_field(mac_user_stru *pst_mac_user ,oal_uint8 uc_smps);

extern  oal_bool_enum_uint8  mac_ie_proc_ht_green_field(
                                        mac_user_stru    *pst_mac_user_sta ,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_ht_green_field,
                                        oal_bool_enum     en_prev_asoc_ht);

extern oal_bool_enum_uint8  mac_ie_proc_ht_supported_channel_width(
                                        mac_user_stru    *pst_mac_user_sta ,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_supported_channel_width,
                                        oal_bool_enum     en_prev_asoc_ht);

extern oal_bool_enum_uint8  mac_ie_proc_lsig_txop_protection_support(
                                        mac_user_stru    *pst_mac_user_sta,
                                        mac_vap_stru     *pst_mac_vap,
                                        oal_uint8         uc_lsig_txop_protection_support,
                                        oal_bool_enum     en_prev_asoc_ht);
extern oal_uint32  mac_ie_proc_ext_cap_ie(mac_user_stru *pst_mac_user, oal_uint8 *puc_payload);
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32  mac_check_is_assoc_frame(oal_uint8 uc_mgmt_frm_type);

#endif
extern oal_uint8  mac_ie_get_chan_num(
                                    oal_uint8   *puc_frame_body,
                                    oal_uint16   us_frame_len,
                                    oal_uint16   us_offset,
                                    oal_uint8    us_curr_chan);

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern oal_uint32  mac_ie_proc_chwidth_field(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user,oal_uint8 uc_chwidth);
#endif

#if 0
extern oal_uint32  mac_set_channel_switch_wrapper_ie(
                oal_uint8                            uc_channel,
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len);
#endif
extern oal_uint32  mac_set_second_channel_offset_ie(
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len);
extern oal_uint32  mac_set_11ac_wideband_ie(
                oal_uint8                            uc_channel,
                wlan_channel_bandwidth_enum_uint8    en_bw,
                oal_uint8                           *pauc_buffer,
                oal_uint8                           *puc_output_len);
extern oal_bool_enum_uint8 mac_ie_check_p2p_action(oal_uint8 *puc_payload);
extern oal_uint32  mac_config_set_mib(mac_vap_stru *pst_mac_vap,
        oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  mac_ie_proc_ht_sta(
                   mac_vap_stru            *pst_mac_sta,
                   oal_uint8                *puc_payload,
                   oal_uint16               *pus_index,
                   mac_user_stru           *pst_mac_user_ap,
                   oal_uint16               *pus_ht_cap_info,
                   oal_uint16               *pus_amsdu_maxsize);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_ie.h */
