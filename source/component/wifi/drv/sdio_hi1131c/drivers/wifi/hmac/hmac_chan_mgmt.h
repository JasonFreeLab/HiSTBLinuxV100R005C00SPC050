/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_chan_mgmt_ap.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年2月22日
  最近修改   :
  功能描述   : hmac_chan_mgmt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月22日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_CHAN_MGMT_H__
#define __HMAC_CHAN_MGMT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CHAN_MGMT_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_MAX_20M_SUB_CH    4      /* VHT80中，20MHz信道总个数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    HMAC_OP_ALLOWED  = BIT0,
    HMAC_SCA_ALLOWED = BIT1,
    HMAC_SCB_ALLOWED = BIT2,
}hmac_chan_op_enum;
typedef oal_uint8 hmac_chan_op_enum_uint8;

typedef enum
{
    HMAC_NETWORK_SCA = 0,
    HMAC_NETWORK_SCB = 1,

    HMAC_NETWORK_BUTT,
}hmac_network_type_enum;
typedef oal_uint8 hmac_network_type_enum_uint8;

typedef enum
{
    MAC_CHNL_AV_CHK_NOT_REQ  = 0,   /* 不需要进行信道扫描 */
    MAC_CHNL_AV_CHK_IN_PROG  = 1,   /* 正在进行信道扫描 */
    MAC_CHNL_AV_CHK_COMPLETE = 2,   /* 信道扫描已完成 */

    MAC_CHNL_AV_CHK_BUTT,
}mac_chnl_av_chk_enum;
typedef oal_uint8 mac_chnl_av_chk_enum_uint8;


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
typedef struct
{
    oal_uint16                 aus_num_networks[HMAC_NETWORK_BUTT];
    hmac_chan_op_enum_uint8    en_chan_op;
    oal_uint8                  auc_resv[3];
}hmac_eval_scan_report_stru;

typedef struct
{
    oal_uint8     uc_idx;     /* 信道索引号 */
    oal_uint16    us_freq;    /* 信道频点 */
    oal_uint8     auc_resv;
}hmac_dfs_channel_info_stru;

typedef struct
{
    oal_uint16  us_freq;        /* 中心频率，单位MHz */
    oal_uint8   uc_number;      /* 信道号 */
    oal_uint8   uc_idx;         /* 信道索引(软件用) */
}mac_freq_channel_map_stru;

typedef struct
{
    oal_uint32                   ul_channels;
    mac_freq_channel_map_stru    ast_channels[HMAC_MAX_20M_SUB_CH];
}hmac_channel_list_stru;
/* 频率信道索引映射关系 */

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_5g[MAC_CHANNEL_FREQ_5_BUTT];
extern OAL_CONST mac_freq_channel_map_stru g_ast_freq_map_2g[MAC_CHANNEL_FREQ_2_BUTT];

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  hmac_chan_reval_status(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap);
extern oal_void  hmac_chan_reval_bandwidth_sta(mac_vap_stru *pst_mac_vap, oal_uint32 ul_change);
extern oal_void  hmac_chan_disable_machw_tx(mac_vap_stru *pst_mac_vap);
extern oal_void  hmac_chan_enable_machw_tx(mac_vap_stru *pst_mac_vap);
extern oal_void  hmac_chan_update_csw_info(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len, oal_uint16 us_offset);
extern oal_void  hmac_chan_multi_switch_to_20MHz_ap(hmac_vap_stru *pst_hmac_vap);
extern oal_void  hmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
extern mac_chnl_av_chk_enum_uint8  hmac_chan_do_channel_availability_check(
                mac_device_stru       *pst_mac_device,
                mac_vap_stru          *pst_mac_vap,
                oal_bool_enum_uint8    en_first_time);
extern oal_uint32  hmac_start_bss_in_available_channel(hmac_vap_stru *pst_hmac_vap);
extern oal_uint32  hmac_chan_select_channel_for_operation(
                mac_vap_stru                        *pst_mac_vap,
                oal_uint8                           *puc_new_channel,
                wlan_channel_bandwidth_enum_uint8   *pen_new_bandwidth);
extern oal_void  hmac_chan_get_ext_chan_info(
                oal_uint8                            uc_pri20_channel_idx,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth,
                hmac_channel_list_stru              *pst_chan_info);
extern oal_uint32  hmac_chan_restart_network_after_switch(mac_vap_stru *pst_mac_vap);
extern oal_void  hmac_chan_multi_switch_to_new_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
extern oal_void hmac_dfs_set_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel);

extern oal_uint32  hmac_ie_proc_ch_switch_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, mac_eid_enum_uint8 en_eid_type);
extern oal_bool_enum_uint8  hmac_ie_check_csa_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload, oal_uint16 us_frame_len, oal_uint16 us_offset);
extern oal_uint32  hmac_ie_proc_wide_bandwidth_ie(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_payload);
extern oal_uint32  hmac_chan_switch_to_new_chan_complete(frw_event_mem_stru *pst_event_mem);
extern oal_void hmac_chan_sync(mac_vap_stru *pst_mac_vap,
            oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth,
            oal_bool_enum_uint8 en_switch_immediately);
extern oal_uint32  hmac_dbac_status_notify(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
extern oal_void hmac_chan_start_40M_recovery_timer(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_chan_update_40M_intol_user(mac_vap_stru *pst_mac_vap,
                                    mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_40M_intol_bit);
#endif

extern oal_uint32  hmac_chan_start_bss(hmac_vap_stru *pst_hmac_vap);

/*****************************************************************************
  11 inline函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_chan_initiate_switch_to_20MHz_ap
 功能描述  : 设置VAP信道参数，准备切换至20MHz运行
 输入参数  : pst_mac_vap: MAC VAP指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 备    注  : 频宽切换，不会改变频带(2.4G or 5G)、以及主信道号，因此不用设置
             vap.st_channel.uc_chan_number和vap.st_channel.en_band，只需改变
             带宽模式vap.st_channel.en_bandwidth

 修改历史      :
  1.日    期   : 2014年2月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_chan_initiate_switch_to_20MHz_ap(mac_vap_stru *pst_mac_vap)
{

    /* 设置VAP带宽模式为20MHz */
    pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;

    /* 设置带宽切换状态变量，表明在下一个DTIM时刻切换至20MHz运行 */
    pst_mac_vap->st_ch_switch_info.en_bw_switch_status = WLAN_BW_SWITCH_40_TO_20;

}

/*****************************************************************************
 函 数 名  : hmac_chan_scan_availability
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_scan_availability(
                mac_device_stru       *pst_mac_device,
                mac_ap_ch_info_stru   *pst_channel_info)
{
#ifdef _PRE_WLAN_FEATURE_DFS
    if (OAL_FALSE == mac_dfs_get_dfs_enable(pst_mac_device))
    {
        return OAL_TRUE;
    }

    if ((MAC_CHAN_NOT_SUPPORT != pst_channel_info->en_ch_status) &&
        (MAC_CHAN_BLOCK_DUE_TO_RADAR != pst_channel_info->en_ch_status))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
#else
    return OAL_TRUE;
#endif
}

/*****************************************************************************
 函 数 名  : hmac_chan_is_ch_op_allowed
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_chan_is_ch_op_allowed(hmac_eval_scan_report_stru *pst_chan_scan_report, oal_uint8 uc_chan_idx)
{
    if (pst_chan_scan_report[uc_chan_idx].en_chan_op & HMAC_OP_ALLOWED)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_chan_mgmt.h */
