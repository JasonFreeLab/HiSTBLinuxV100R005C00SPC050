/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_tcp_udp_keepalive.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月18日
  最近修改   :
  功能描述   : hmac_tcp_udp_keepalive.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_TCP_UDP_KEEPALIVE_H__
#define __HMAC_TCP_UDP_KEEPALIVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mac_vap.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TCP_UDP_KEEPALIVE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_TCP_CONNECT_NUM  4   /* 保活TCP连接条数 */
#define HMAC_UDP_CONNECT_NUM  4   /* 保活UDP连接条数 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    HMAC_NETBUF_TYPE_TCP,
    HMAC_NETBUF_TYPE_UDP,
    HMAC_NETBUF_TYPE_BUTT
}hmac_netbuf_type_enum;
typedef oal_uint8 hmac_netbuf_type_enum_uint8;


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
    oal_uint32      ul_sess_id;
    oal_uint8       uc_dst_mac[6];  /* 目的MAC地址 */
    oal_uint8       auc_resv[2];
    oal_uint8       uc_src_ip[4];   /* 源IP地址 */
    oal_uint8       uc_dst_ip[4];   /* 目的IP地址 */
    oal_uint16      us_src_port;    /* 源端口号 */
    oal_uint16      us_dst_port;    /* 目的端口号 */
    oal_uint32      ul_seq_num;     /* 序列号 */
    oal_uint32      ul_ack_num;     /* 确认号 */
    oal_uint16      us_window;      /* TCP窗口大小 */
    oal_uint16      us_interval_timer;       /* 心跳包发送周期 */
    oal_uint16      us_retry_interval_timer; /* 重传时心跳包发送周期 */
    oal_uint16      us_retry_max_count;      /* 最大重传次数 */
    oal_uint32      ul_time_value;
    oal_uint32      ul_time_echo;
    oal_uint8      *puc_tcp_payload;
    oal_uint32      ul_payload_len;
}hmac_tcp_params_stru;

typedef struct
{
    oal_uint32     ul_sess_id;
    oal_uint8      uc_dst_mac[6];    /* 目的MAC地址 */
    oal_uint8      auc_resv[2];
    oal_uint8      uc_src_ip[4];     /* 源IP地址 */
    oal_uint8      uc_dst_ip[4];     /* 目的IP地址 */
    oal_uint16     us_src_port;      /* 源端口号 */
    oal_uint16     us_dst_port;      /* 目的端口号 */
    oal_uint16     us_interval_timer;       /* 心跳包发送周期 */
    oal_uint16     us_retry_interval_timer; /* 重传时心跳包发送周期 */
    oal_uint16     us_retry_max_count;      /* 最大重传次数 */
    oal_uint32     ul_time_value;
    oal_uint32     ul_time_echo;
    oal_uint8     *puc_udp_payload;
    oal_uint8      ul_payload_len;
}hmac_udp_params_stru;

typedef struct
{
    hmac_tcp_params_stru st_tcp_connects[HMAC_TCP_CONNECT_NUM];
    hmac_udp_params_stru st_udp_connects[HMAC_UDP_CONNECT_NUM];
}hmac_tcp_udp_conn_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint16 hmac_encap_tcp(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, hmac_tcp_params_stru *pst_tcp_params);
extern oal_uint16 hmac_encap_udp(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_data, hmac_udp_params_stru *pst_udp_params);
extern oal_uint32 hmac_tcp_udp_process(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_get_tcp_params(oal_netbuf_stru *pst_netbuf);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif




