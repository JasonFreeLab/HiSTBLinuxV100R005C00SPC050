/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_net.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月16日
  最近修改   :
  功能描述   : hwal_ioctl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HWAL_NET_H__
#define __HWAL_NET_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "driver_hisi_common.h"
#include "oal_net.h"
#include "oal_sdio_comm.h"
#include "oam_ext_if.h"
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HWAL_NET_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/** Ask if a drvier is ready to send */
#define NETIF_IS_NOT_READY() (NETIF_FLOW_CTRL_ON == g_en_netif_flow_ctrl)

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
extern oal_netbuf_stru *hwal_lwip_skb_alloc(oal_net_device_stru *pst_net_dev, oal_uint16 us_lwip_buflen);
extern oal_int32    hwal_netif_rx(oal_net_device_stru *pst_net_dev, oal_netbuf_stru *pst_netbuf);
extern oal_int32    hwal_lwip_init(oal_net_device_stru *pst_net_dev);
extern oal_void     hwal_lwip_deinit(oal_net_device_stru *pst_net_dev);
extern oal_uint32       hwal_skb_struct_free(oal_netbuf_stru *pst_sk_buf);
extern oal_netbuf_stru *hwal_skb_struct_alloc(oal_void);
extern oal_uint32       hwal_pbuf_convert_2_skb(oal_lwip_buf *pst_lwip_buf, oal_netbuf_stru *pst_sk_buf);
extern oal_lwip_buf    *hwal_skb_convert_2_pbuf(oal_netbuf_stru *pst_sk_buf);
extern oal_void     hwal_lwip_receive(oal_lwip_netif *pst_netif, oal_netbuf_stru *pst_drv_buf);
extern oal_int32    hwal_lwip_notify(oal_lwip_netif *pst_netif, oal_uint32 ul_notify_type);
extern oal_lwip_netif  *hwal_lwip_get_netif(const oal_int8 *pc_name);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
