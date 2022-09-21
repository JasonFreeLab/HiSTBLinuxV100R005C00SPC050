/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_linux_flowctl.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年3月3日
  最近修改   :
  功能描述   : wal_linux_flowctl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月3日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_LINUX_FLOWCTL_H__
#define __WAL_LINUX_FLOWCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_FLOWCTL_H

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WAL_NETDEV_USER_MAX_NUM             (WLAN_ACTIVE_USER_MAX_NUM + 4)
#define WAL_NETDEV_SUBQUEUE_PER_USE         4
#define WAL_NETDEV_SUBQUEUE_MAX_NUM         ((WAL_NETDEV_USER_MAX_NUM) * (WAL_NETDEV_SUBQUEUE_PER_USE))

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
    oal_uint8       auc_mac_addr[OAL_MAC_ADDR_LEN];
}wal_macaddr_subq_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint16   wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf);
extern oal_uint32   wal_flowctl_backp_event_handler(frw_event_mem_stru *pst_event_mem);

#endif /* endif for _PRE_WLAN_FEATURE_FLOWCTL */

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
extern oal_uint16   wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf);
#else
extern oal_uint16   wal_netdev_select_queue(oal_net_device_stru *pst_dev, oal_netbuf_stru *pst_buf, void *accel_priv, select_queue_fallback_t fallback);
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)) */

#endif /* end if for _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_flowctl.h */

