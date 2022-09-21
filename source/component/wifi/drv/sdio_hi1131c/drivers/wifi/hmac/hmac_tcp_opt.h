/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_tcp_opt.h
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

#ifndef __HMAC_TCP_OPT_H__
#define __HMAC_TCP_OPT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_TCP_OPT
#include "oal_hcc_host_if.h"
#include "hmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TCP_OPT_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define FIN_FLAG_BIT    (1 << 0)
#define SYN_FLAG_BIT    (1 << 1)
#define RESET_FLAG_BIT  (1 << 2)
#define URGENT_FLAG_BIT (1 << 5)
#define FILTER_FLAG_MASK (FIN_FLAG_BIT | SYN_FLAG_BIT | RESET_FLAG_BIT | URGENT_FLAG_BIT)
#define MAX_TIME_BY_TWO (1 << 16)
#define HCC_ASSEMBLE_INFO_SIZE          16


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
struct hcc_handler* hcc_get_default_handler(void);
void hmac_tcp_opt_ack_count_reset(hmac_vap_stru    *pst_hmac_vap,hcc_chan_type dir, oal_uint16 stream);
void hmac_tcp_opt_ack_all_count_reset(hmac_vap_stru    *pst_hmac_vap);
void hmac_tcp_opt_ack_show_count(hmac_vap_stru    *pst_hmac_vap);
struct tcp_list_node *hmac_tcp_opt_find_oldest_node(hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir);
struct tcp_list_node *hmac_tcp_opt_get_buf(hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir);
void hmac_tcp_opt_free_buf(hmac_vap_stru    *pst_hmac_vap, struct tcp_list_node *node, hcc_chan_type dir);
oal_uint32 hmac_tcp_opt_add_node(hmac_vap_stru    *pst_hmac_vap, struct wlan_tcp_flow *tcp_info, hcc_chan_type dir);
oal_uint32 hmac_tcp_opt_init_filter_tcp_ack_pool(hmac_vap_stru    *pst_hmac_vap);
void hmac_tcp_opt_deinit_list(hmac_vap_stru    *pst_hmac_vap);
oal_uint32 hmac_tcp_opt_get_flow_index(hmac_vap_stru    *pst_hmac_vap,
                                             oal_ip_header_stru     *pst_ip_hdr,
                                             oal_tcp_header_stru *pst_tcp_hdr,
                                             hcc_chan_type dir);

oal_uint32 hmac_tcp_opt_get_tcp_ack_type(hmac_vap_stru    *pst_hmac_vap,
                                             oal_ip_header_stru     *pst_ip_hdr,
                                             hcc_chan_type dir,
                                             oal_uint16 us_index);
oal_bool_enum_uint8 hmac_judge_rx_netbuf_classify(oal_netbuf_stru *pst_netbuff);
oal_bool_enum_uint8 hmac_judge_rx_netbuf_is_tcp_ack(mac_llc_snap_stru *pst_snap);
oal_bool_enum_uint8 hmac_judge_tx_netbuf_is_tcp_ack(oal_ether_header_stru *ps_ethmac_hdr);
oal_uint32  hmac_tcp_opt_rx_get_tcp_ack(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, oal_uint16 *p_us_index, oal_uint8 dir);
oal_uint32  hmac_tcp_opt_tx_get_tcp_ack(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, oal_uint16 *p_us_index, oal_uint8 dir);
oal_uint16 hmac_tcp_opt_tcp_ack_list_filter(hmac_vap_stru    *pst_hmac_vap, hmac_tcp_opt_queue type,hcc_chan_type dir, oal_netbuf_head_stru  *head);
oal_uint16 hmac_tcp_opt_rx_tcp_ack_filter(void *hmac_device, hmac_tcp_opt_queue type,hcc_chan_type dir, void* data);
oal_uint16 hmac_tcp_opt_tx_tcp_ack_filter(void *hmac_device, hmac_tcp_opt_queue type,hcc_chan_type dir, void* data);
oal_uint32 hmac_tcp_opt_tcp_ack_filter(oal_netbuf_stru *skb, hmac_vap_stru    *pst_hmac_vap, hcc_chan_type dir);

void hmac_trans_queue_filter(hmac_vap_stru    *pst_hmac_vap, oal_netbuf_head_stru  *head_t,
                                    hmac_tcp_opt_queue type, hcc_chan_type dir);
void hmac_tcp_ack_process_hcc_queue(hmac_vap_stru    *pst_hmac_vap,
                                    hcc_chan_type dir,hmac_tcp_opt_queue type);
oal_int32 hmac_tcp_ack_process(void);
oal_bool_enum_uint8 hmac_tcp_ack_need_schedule(void);
oal_void hmac_sched_transfer(void);
oal_int32 hmac_set_hmac_tcp_ack_process_func(hmac_tcp_ack_process_func p_func);
oal_int32 hmac_set_hmac_tcp_ack_need_schedule(hmac_tcp_ack_need_schedule_func p_func);

/*****************************************************************************
  11 内联函数定义
*****************************************************************************/


#endif   /* end of _PRE_WLAN_TCP_OPT */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_tcp_opt.h */
