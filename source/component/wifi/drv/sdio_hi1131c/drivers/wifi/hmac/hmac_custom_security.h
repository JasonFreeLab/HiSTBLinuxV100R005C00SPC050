/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_custom_security.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年3月26日
  最近修改   :
  功能描述   : hmac_custom_security.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_CRYPTO_FRAME_H__
#define __HMAC_CRYPTO_FRAME_H__

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY

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

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CS_INVALID_AGING_TIME         0
#define CS_DEFAULT_AGING_TIME         3600
#define CS_DEFAULT_RESET_TIME         3600
#define CS_DEFAULT_THRESHOLD          100



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 隔离模式 mode*/
typedef enum
{
    CS_ISOLATION_MODE_BROADCAST=0x01,        /* 广播     */
    CS_ISOLATION_MODE_MULTICAST=0x02,        /* 组播     */
    CS_ISOLATION_MODE_UNICAST=0x04,          /* 单播     */
}cs_isolation_mode_enum;

/* 隔离类型 */
typedef enum
{
    CS_ISOLATION_TYPE_NONE,             /* 关闭隔离        */
    CS_ISOLATION_TYPE_MULTI_BSS,        /* 多BSS隔离       */
    CS_ISOLATION_TYPE_SINGLE_BSS,       /* 单BSS隔离       */

    CS_ISOLATION_TYPE_BUTT
}cs_isolation_type_enum;
typedef oal_uint8 cs_isolation_type_enum_uint8;

/* 隔离forwording方式 */
typedef enum
{
    CS_ISOLATION_FORWORD_NONE,         /* 隔离forword为不丢弃       */
    CS_ISOLATION_FORWORD_TOLAN,        /* 隔离forword为发送到lan  */
    CS_ISOLATION_FORWORD_DROP,         /* 隔离forword为丢弃       */

    CS_ISOLATION_FORWORD_BUTT
}cs_isolation_forward_enum;
typedef oal_uint8 cs_isolation_forward_enum_uint8;


/* 黑名单模式 */
typedef enum
{
    CS_BLACKLIST_MODE_NONE,            /* 关闭         */
    CS_BLACKLIST_MODE_BLACK,           /* 黑名单       */
    CS_BLACKLIST_MODE_WHITE,           /* 白名单       */

    CS_BLACKLIST_MODE_BUTT
}cs_blacklist_mode_enum;
typedef oal_uint8 cs_blacklist_mode_enum_uint8;

/* 黑名单类型 */
typedef enum
{
    CS_BLACKLIST_TYPE_ADD,           /* 增加       */
    CS_BLACKLIST_TYPE_DEL,           /* 删除       */

    CS_BLACKLIST_TYPE_BUTT
}cs_blacklist_type_enum;
typedef oal_uint8 cs_blacklist_type_enum_uint8;




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
/* 自动黑名单配置参数 */
typedef struct
{
    oal_uint8                       uc_enabled;               /* 使能标志 0:未使能  1:使能 */
    oal_uint8                       auc_reserved[3];          /* 字节对齐                  */
    oal_uint32                      ul_threshold;             /* 门限                      */
    oal_uint32                      ul_reset_time;            /* 重置时间                  */
    oal_uint32                      ul_aging_time;            /* 老化时间                  */
} hmac_autoblacklist_cfg_stru;

/* 黑白名单配置 */
typedef struct
{
    oal_uint8                       uc_type;                  /* 配置类型    */
    oal_uint8                       uc_mode;                  /* 配置模式    */
    oal_uint8                       auc_sa[6];                /* mac地址     */
} hmac_blacklist_cfg_stru;


/* 隔离参数配置 */
typedef struct
{
    oal_uint8                      uc_isolation_type;        /* 隔离类型  */
    oal_uint8                      uc_isolation_mode;        /* 隔离模式  */
    oal_uint8                      auc_reserved[2];          /* 字节对齐  */
}hmac_isolation_cfg_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32 hmac_isolation_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode);
extern oal_uint32 hmac_isolation_set_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_type);
extern oal_uint32 hmac_isolation_set_forward(mac_vap_stru *pst_mac_vap, oal_uint8 uc_forward);
extern cs_isolation_forward_enum hmac_isolation_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_uint32 hmac_autoblacklist_enable(mac_vap_stru *pst_mac_vap, oal_uint8 uc_enabled);
extern oal_uint32 hmac_autoblacklist_set_aging(mac_vap_stru *pst_mac_vap, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_autoblacklist_set_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_threshold);
extern oal_uint32 hmac_autoblacklist_set_reset_time(mac_vap_stru *pst_mac_vap, oal_uint32 ul_reset_time);
extern oal_void hmac_autoblacklist_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_uint32 hmac_blacklist_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode);
extern oal_uint32 hmac_blacklist_add(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_blacklist_add_only(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time);
extern oal_uint32 hmac_blacklist_del(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);

extern oal_uint32 hmac_blacklist_update(mac_vap_stru *pst_mac_vap, hmac_blacklist_cfg_stru *pst_blacklist_cfg);
extern oal_bool_enum_uint8 hmac_blacklist_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_void hmac_show_blacklist_info(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_backlist_get_drop(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr);
extern oal_uint32 hmac_isolation_clear_counter(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_isolation_get_bcast_counter(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_isolation_get_mcast_counter(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_isolation_get_ucast_counter(mac_vap_stru *pst_mac_vap);
extern oal_void hmac_show_isolation_info(mac_vap_stru *pst_mac_vap);
extern oal_uint8 hmac_backlist_get_list_num(mac_vap_stru *pst_mac_vap);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif  /* #ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY */

#endif /* end of hmac_crypto_tkip.h */

