/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hwal_app_ioctl.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年6月27日
  最近修改   :
  功能描述   : hwal_app_ioctl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年6月27日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HWAL_APP_IOCTL_H__
#define __HWAL_APP_IOCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "driver_hisi_common.h"
/*******************************************************************************
 *  枚举类型定义区
*******************************************************************************/

/*******************************************************************************
 *   数据结构类型和联合体类型定义
*******************************************************************************/
typedef oal_int32 (*hwal_app_ioctl_handler)(oal_int8 *puc_ifname, oal_void *p_buf);
/*****************************************************************************
*   全局变量声明
*****************************************************************************/

/*****************************************************************************
     函数声明
*****************************************************************************/
oal_int32 hwal_ioctl_set_freq(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32 hwal_ioctl_set_monitor(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32 hwal_app_ioctl(oal_int8 *puc_ifname, hisi_ioctl_command_stru *pst_cmd);
oal_int32 hwal_ioctl_set_freq_40m(oal_int8 *puc_ifname, oal_void *p_buf);
#ifdef _PRE_WLAN_FEATURE_TCP_UDP_KEEPALIVE
oal_int32 hwal_ioctl_get_tcp_params(oal_int8 *puc_ifname, oal_void *p_buf);
oal_int32 hwal_ioctl_set_tcp_params(oal_int8 *puc_ifname, oal_void *p_buf);
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif