/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_rx_rsp.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年8月26日
  最近修改   :
  功能描述   : wal_linux_rx_rsp.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_LINUX_RX_RSP_H__
#define __WAL_LINUX_RX_RSP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_types.h"
#include "wal_ext_if.h"
#include "frw_ext_if.h"
#include "hmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_RX_RSP_H
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
/* 驱动sta上报内核的扫描结果 */
typedef struct
{
    oal_int32               l_signal;      /* 信号强度 */

    oal_int16               s_freq;        /* bss所在信道的中心频率 */
    oal_uint8               auc_arry[2];

    oal_uint32                ul_mgmt_len;   /* 管理帧长度 */
    oal_ieee80211_mgmt_stru  *pst_mgmt;      /* 管理帧起始地址 */

}wal_scanned_bss_info_stru;

/* 驱动sta上报内核的关联结果 */
typedef struct
{
    oal_uint8       auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta关联的ap mac地址 */
    oal_uint16      us_status_code;                /* ieee协议规定的16位状态码 */

    oal_uint8       *puc_rsp_ie;                 /* asoc_req_ie  */
    oal_uint8       *puc_req_ie;

    oal_uint32      ul_req_ie_len;               /* asoc_req_ie len */
    oal_uint32      ul_rsp_ie_len;

    oal_uint16      us_connect_status;
    oal_uint8       auc_resv[2];

}oal_connet_result_stru;

/* 驱动sta上报内核的去关联结果 */
typedef struct
{
    oal_uint16  us_reason_code;         /* 去关联 reason code */
    oal_uint8   auc_resv[2];

    oal_uint8  *pus_disconn_ie;        /* 去关联关联帧 ie */
    oal_uint32  us_disconn_ie_len;      /* 去关联关联帧 ie 长度 */
}oal_disconnect_result_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  wal_scan_comp_proc_sta(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_asoc_comp_proc_sta(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_disasoc_comp_proc_sta(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_connect_new_sta_proc_ap(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_disconnect_sta_proc_ap(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_mic_failure_proc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_send_mgmt_to_host(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_p2p_listen_timeout(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_uint32  wal_send_other_bss_data_to_host(frw_event_mem_stru *pst_event_mem);
#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_rx_rsp.h */
