/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wlan_types.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月3日
  最近修改   :
  功能描述   : 对应所有公共的信息(HAL同时可以使用的)放到该文件中
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月3日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_PROXY_ARP_H__
#define __HMAC_PROXY_ARP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hmac_vap.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_PROXY_IPV4_HASHSIZE        MAC_VAP_USER_HASH_MAX_VALUE
#define HMAC_PROXY_IPV6_HASHSIZE        MAC_VAP_USER_HASH_MAX_VALUE

#define HMAC_PROXY_IPV4_HASH(n) \
        (((const oal_uint8 *)(&n))[3] % HMAC_PROXY_IPV4_HASHSIZE)

#define HMAC_PROXY_IPV6_HASH(n) \
        (((const oal_uint8 *)(n))[15] % HMAC_PROXY_IPV6_HASHSIZE)

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
typedef struct
{
    oal_dlist_head_stru     st_entry;
    oal_uint32              ul_ipv4;                        /* 记录对应的ipv4地址 */
    oal_uint8               auc_mac[WLAN_MAC_ADDR_LEN];     /* 记录对应的mac地址 */
    oal_uint8               auc_rsv[2];
}hmac_proxy_ipv4_hash_stru;

typedef struct
{
    oal_dlist_head_stru     st_entry;
    oal_in6_addr            st_ipv6;                        /* 记录对应的ipv4地址 */
    oal_uint8               auc_mac[WLAN_MAC_ADDR_LEN];     /* 记录对应的mac地址 */
    oal_uint8               auc_rsv[2];
}hmac_proxy_ipv6_hash_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void hmac_proxy_arp_init(mac_vap_stru *pst_mac_vap);
extern oal_void hmac_proxy_exit(mac_vap_stru *pst_mac_vap);
extern oal_bool_enum_uint8 hmac_proxy_arp_proc(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_buf);
extern oal_err_code_enum_uint32 hmac_proxy_remove_mac(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac);
extern oal_void hmac_proxyarp_on(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_on);
extern oal_uint32 hmac_proxy_display_info(mac_vap_stru *pst_mac_vap);
//extern oal_err_code_enum_uint32 mac_proxy_init_vap(mac_vap_stru * pst_mac_vap);


#endif/* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



#endif


