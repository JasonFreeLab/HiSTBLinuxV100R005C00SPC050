/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_11i.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年8月15日
  最近修改   :
  功能描述   : STA侧管理帧处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月15日
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
#include "mac_resource.h"
#include "hmac_vap.h"
#include "hmac_user.h"
//#include "mac_11i.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_11i_H

/*****************************************************************************/
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
  10 函数声明
*****************************************************************************/
oal_uint32 hmac_init_security(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_addr);

extern oal_bool_enum_uint8 hmac_check_pcip_wpa_policy(wlan_mib_ieee802dot11_stru *pst_mib_info, oal_uint8 uc_policy);
extern oal_bool_enum_uint8 hmac_check_pcip_wpa2_policy(wlan_mib_ieee802dot11_stru *pst_mib_info, oal_uint8 uc_policy);
extern oal_uint32 hmac_check_pcip_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                            oal_uint8 uc_policy,
                                            oal_uint8 uc_80211i_mode);

oal_uint8 * hmac_get_security_oui(oal_uint8 uc_80211i_mode);
oal_uint8 hmac_get_pcip_policy_auth(oal_uint8 *puc_frame, oal_uint8 *puc_len, oal_uint8 *puc_oui);
oal_uint8 hmac_get_auth_policy_auth(oal_uint8 * puc_frame, oal_uint8 *uc_len, oal_uint8 *puc_oui);
oal_uint32 hmac_check_join_req_parewise_cipher_supplicant(
                                wlan_mib_ieee802dot11_stru  *pst_mib_info,
                                oal_uint8                   *puc_pcip_policy_match,
                                oal_uint8                    uc_802_11i_mode,
                                oal_uint8                   *puc_pcip_policy);
oal_bool_enum_uint8 hmac_check_pcip_wpa_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                            oal_uint8 uc_policy);

oal_bool_enum_uint8 hmac_check_pcip_wpa2_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                         oal_uint8 uc_policy);

oal_uint32  hmac_check_bss_cap_info(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap);

oal_uint32  hmac_update_current_join_req_parms_11i(
                    mac_vap_stru           *pst_mac_vap,
                    mac_bss_80211i_info_stru     *pst_11i);

oal_void    hmac_update_pcip_policy_prot_supplicant(mac_vap_stru *pst_mac_vap,
                                                            oal_uint8 uc_pcip_policy_match);

oal_uint32 hmac_check_rsn_capability(mac_vap_stru *pst_mac_vap, const oal_uint8 *puc_rsn_ie, mac_status_code_enum_uint16 *pen_status_code);
oal_uint32 hmac_en_mic(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf, oal_uint8 *puc_iv_len);
oal_uint32 hmac_de_mic(hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_netbuf);
oal_uint32 hmac_rx_tkip_mic_failure_process(frw_event_mem_stru *pst_event_mem);
oal_uint32 hmac_11i_ether_type_filter(hmac_vap_stru *pst_vap, oal_uint8 *puc_mac_addr, oal_uint16 us_ether_type);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



