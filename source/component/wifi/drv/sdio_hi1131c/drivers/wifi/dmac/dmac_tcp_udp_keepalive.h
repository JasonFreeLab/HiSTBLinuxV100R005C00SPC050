/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_tcp_udp_keepalive.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年4月12日
  最近修改   :
  功能描述   : dmac_tcp_udp_keepalive.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月12日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_TCP_UDP_KEEPALIVE_H__
#define __DMAC_TCP_UDP_KEEPALIVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mac_vap.h"
#include "dmac_vap.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TCP_UDP_KEEPALIVE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_TCP_CONNECT_NUM  4   /* 保活TCP连接条数 */
#define DMAC_UDP_CONNECT_NUM  4   /* 保活UDP连接条数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    DMAC_TCP_OFFSET_SEQ_NUM  = 4, /* TCP的seq num字段从TCP头首部偏移4字节 */
    DMAC_TCP_OFFSET_ACK_NUM  = 8, /* TCP的ack num字段从TCP头首部偏移8字节 */
    DMAC_TCP_OFFSET_CHECKSUM = 12,/* TCP的校验和字段从TCP头首部偏移12字节 */
    DMAC_TCP_OFFSET_BUTT
}dmac_tcp_offset_enum;
typedef oal_uint8 dmac_tcp_offset_enum_uint8;

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
    mac_tcp_params_stru           *pst_tcp_params;        /* TCP连接的参数信息 */
    oal_netbuf_stru               *pst_tcp_netbuf;        /* 将要发送的TCP心跳包,不包含MAC头 */
    mac_vap_stru                  *pst_mac_vap;           /* 对应的VAP */
    oal_uint32                     ul_payload_len;        /* 心跳包的payload长度 */ 
    oal_uint32                     ul_tcp_wait_time;      /* 距上次发送心跳包的时间 */
    oal_uint16                     us_retry_count;        /* 已经重传次数*/
    oal_uint8                      uc_get_ack_flag;       /* 是否接收到TCP ACK，收到赋值为1，没收到赋值为0 */
    oal_uint8                      auc_resv[1];
}dmac_tcp_conn_stru;

typedef struct
{
    mac_udp_params_stru            *pst_udp_params;        /* UDP连接的参数信息 */
    oal_netbuf_stru                *pst_udp_netbuf;       /* 将要发送的UDP心跳包 */
    oal_netbuf_stru                *pst_udp_ack_netbuf;   /* 设备收到服务器的UDP包后回复的UDP响应包 */
    mac_vap_stru                   *pst_mac_vap;          /* 对应的VAP */    
    oal_uint32                      ul_payload_len;       /* 心跳包的payload长度 */ 
    oal_uint32                      ul_udp_wait_time;     /* 距上次发送心跳包的时间 */
    oal_uint16                      us_retry_count;        /* 已经重传次数 */
    oal_uint8                       uc_get_ack_flag;       /* 是否接收到UDP响应包，1接收到，0没有接收到 */
    oal_uint8                       auc_resv[1];
}dmac_udp_conn_stru;

typedef struct
{
    dmac_tcp_conn_stru        st_tcp_connect[DMAC_TCP_CONNECT_NUM];      /* TCP连接相关参数指针 */
    dmac_udp_conn_stru        st_udp_connect[DMAC_UDP_CONNECT_NUM];      /* UDP连接相关参数指针 */
    oal_uint8                 uc_tcp_conn_num;      /* 保活的TCP连接个数 */
    oal_uint8                 uc_udp_conn_num;      /* 保活的UDP连接个数 */
    oal_uint8                 uc_keepalive_switch;  /* TCP&UDP keepalive特性开关 */
    oal_uint8                 auc_resv[1];   
}dmac_tcp_udp_conn_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
typedef enum
{
    DMAC_NETBUF_TYPE_TCP,
    DMAC_NETBUF_TYPE_UDP,
    DMAC_NETBUF_TYPE_BUTT
}dmac_netbuf_type_enum;
typedef oal_uint8 dmac_netbuf_type_enum_uint8;


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32 dmac_rx_tcp_ack(oal_netbuf_stru *pst_netbuf);
extern oal_uint32 dmac_rx_udp_ack(oal_netbuf_stru *pst_netbuf);
extern oal_uint32 dmac_tcp_udp_conn_process(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32 dmac_tx_process_tcp_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_tx_process_udp_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_set_tcp_seq_num(oal_uint8 *puc_netbuf, oal_uint32 ul_seq_num);
extern oal_uint32 dmac_destory_tcp_udp_connects(oal_void);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif



