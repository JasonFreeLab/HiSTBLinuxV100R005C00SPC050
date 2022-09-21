/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_encap_frame_ap.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月28日
  最近修改   :
  功能描述   : hmac_encap_frame_ap.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_ENCAP_FRAME_AP_H__
#define __HMAC_ENCAP_FRAME_AP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hmac_user.h"
#include "hmac_vap.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef enum
{
    /* 加密方式为open */
    HMAC_AP_AUTH_SEQ1_OPEN_ANY  = 0,
    /* 加密方式为wep,处理重传帧 */
    HMAC_AP_AUTH_SEQ1_WEP_NOT_RESEND,
    /* 加密方式为wep,处理非重传帧 */
    HMAC_AP_AUTH_SEQ1_WEP_RESEND,
    /* 加密方式为open */
    HMAC_AP_AUTH_SEQ3_OPEN_ANY,
    /* 加密方式为WEP,assoc状态为auth comlete */
    HMAC_AP_AUTH_SEQ3_WEP_COMPLETE,
    /* 加密方式为WEP,assoc状态为assoc */
    HMAC_AP_AUTH_SEQ3_WEP_ASSOC,
    /* 什么也不做 */
    HMAC_AP_AUTH_DUMMY,

    HMAC_AP_AUTH_BUTT
}hmac_ap_auth_process_code_enum;
typedef oal_uint8 hmac_ap_auth_process_code_enum_uint8;

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
typedef struct tag_hmac_auth_rsp_param_stru
{
    /* 收到auth request是否为重传帧 */
    oal_uint8                               uc_auth_resend;
    /* 记录是否为wep */
    oal_bool_enum_uint8                     en_is_wep_allowed;
    /* 记录认证的类型 */
    oal_uint16                              us_auth_type;
    /* 记录函数处理前，user的关联状态*/
    mac_user_asoc_state_enum_uint8          en_user_asoc_state;
    oal_uint8                               uc_pad[3];

}hmac_auth_rsp_param_stru;

typedef hmac_ap_auth_process_code_enum_uint8 (*hmac_auth_rsp_fun)(hmac_auth_rsp_param_stru *pst_auth_rsp_param, \
                                                    oal_uint8 *puc_code, \
                                                    mac_user_asoc_state_enum_uint8 *pst_usr_ass_stat);

typedef struct tag_hmac_auth_rsp_handle_stru
{
    hmac_auth_rsp_param_stru st_auth_rsp_param;
    hmac_auth_rsp_fun        st_auth_rsp_fun;
}hmac_auth_rsp_handle_stru;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_mgmt_encap_chtxt
 功能描述  : 封装chtxt
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hmac_mgmt_encap_chtxt(oal_uint8 *puc_frame,
                                                               oal_uint8 *puc_chtxt,
                                                               oal_uint16 *pus_auth_rsp_len,
                                                               hmac_user_stru *pst_hmac_user_sta)
{
    /* Challenge Text Element                  */
    /* --------------------------------------- */
    /* |Element ID | Length | Challenge Text | */
    /* --------------------------------------- */
    /* | 1         |1       |1 - 253         | */
    /* --------------------------------------- */
    puc_frame[6] = MAC_EID_CHALLENGE;
    puc_frame[7] = WLAN_CHTXT_SIZE;

    /* 将challenge text拷贝到帧体中去 */
    oal_memcopy(&puc_frame[8], puc_chtxt, WLAN_CHTXT_SIZE);

    /* 认证帧长度增加Challenge Text Element的长度 */
    *pus_auth_rsp_len += (WLAN_CHTXT_SIZE + MAC_IE_HDR_LEN);

    /* 保存明文的challenge text */
    oal_memcopy(pst_hmac_user_sta->auc_ch_text, &puc_frame[8], WLAN_CHTXT_SIZE);
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern oal_uint16  hmac_encap_auth_rsp(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_auth_rsp, oal_netbuf_stru *pst_auth_req, oal_uint8 *puc_chtxt);

extern oal_uint32 hmac_mgmt_encap_asoc_rsp_ap(
                    mac_vap_stru                   *pst_mac_ap,
                    oal_uint8                      *puc_sta_addr,
                    oal_uint16                      us_assoc_id,
                    mac_status_code_enum_uint16     en_status_code,
                    oal_uint8                      *puc_asoc_rsp,
                    oal_uint16                      us_type);





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_encap_frame_ap.h */
