/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_tcp_opt_struc.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年5月16日
  最近修改   :
  功能描述   : hmac_dfs.c 的头文件
  函数列表   :
  修改历史   :
1.日    期   : 2015年5月16日
  作    者   : 
  修改内容   : 创建文件
******************************************************************************/

#ifndef __HMAC_TCP_OPT_STRUC_H__
#define __HMAC_TCP_OPT_STRUC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_TCP_OPT

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_net.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TCP_OPT_STRUC_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HMAC_TCP_STREAM  8
#define TCPDATA_INFO_MAXNUM 4
#define TCPDATA_PSH_INFO_MAXNUM (8 * TCPDATA_INFO_MAXNUM)
    


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum
{
    TCP_ACK_FILTER_TYPE  = 1,
    DUP_TCP_ACK_TYPE,
    TCP_TYPE_COUNT
};

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
    

typedef struct _wlan_perform_tcp_impl_
{
    oal_uint64 ull_drop_count;
    oal_uint64 ull_send_count;
    oal_uint64 ull_dup_ack_count;
}wlan_perform_tcp_impl;

typedef struct _wlan_perform_tcp_impls_
{
    oal_uint32 ul_ack_limit;
    oal_uint64 ull_ignored_count;
    wlan_perform_tcp_impl st_tcp_info[HMAC_TCP_STREAM];
}wlan_perform_tcp_impls;

struct skb_tcp_cb
{
    oal_uint16 us_index;
    oal_uint16 us_reserve;
    oal_uint32  ul_tcp_type;
    oal_uint32  ul_tcp_ack_no;
};

struct wlan_perform_tcp
{
    /*hcc rx/tx tcp ack param*/
    oal_netbuf_head_stru hcc_ack_queue[HMAC_TCP_STREAM];
    oal_uint32      aul_hcc_ack_count[HMAC_TCP_STREAM];               /* ack num in each queue */
    oal_uint32      aul_hcc_duplicate_ack_count[HMAC_TCP_STREAM];
    oal_uint32      aul_hcc_tcp_ack_no[HMAC_TCP_STREAM];
    oal_spin_lock_stru hmac_tcp_ack_lock;
#ifdef HCC_DEBUG
    oal_uint32 aul_ack_count[HMAC_TCP_STREAM];
    oal_uint32 aul_duplicate_ack_count[HMAC_TCP_STREAM];
#endif
    /*TBD filter upline ack later*/
};
struct wlan_tcp_flow
{
    oal_uint32 ul_src_ip;
    oal_uint32 ul_dst_ip;
    oal_uint16 us_src_port;
    oal_uint16 us_dst_port;
    oal_uint8 uc_protocol;
};
struct tcp_list_node
{
    oal_dlist_head_stru        list;
    oal_uint32              ul_used;       /* 0-free, 1-used */
    struct wlan_tcp_flow   wlan_tcp_info;
    oal_uint32              ul_index;
    oal_uint32              ul_last_ts;  /*time of last frame*/
};
struct wlan_perform_tcp_list
{
    struct tcp_list_node    tcp_pool[HMAC_TCP_STREAM];
    oal_uint32              ul_free_count;
    oal_spin_lock_stru              tcp_lock;      /* lock for tcp pool */
    oal_spin_lock_stru              tcp_list_lock; /* lock for tcp list */
    oal_dlist_head_stru        tcp_list;
};
    

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
  11 内联函数定义
*****************************************************************************/


#endif   /* end of _PRE_WLAN_TCP_OPT */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_tcp_opt_struc.h */
