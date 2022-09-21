/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_backup.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年8月17日
  最近修改   :
  功能描述   : hmac_backup.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年8月17日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HMAC_BACKUP_H__
#define __HMAC_BACKUP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_net.h"
#include "hmac_vap.h"
#include "hmac_user.h"
#include "hmac_device.h"
#include "hmac_resource.h"
#include "data_process.h"
#ifndef WIN32
#include "frw_ext_if.h"
#include "frw_event_sched.h"
#include "frw_event_main.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_BACKUP_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern hmac_res_stru                  g_st_hmac_res;
extern mac_res_stru                   g_st_mac_res;
#ifndef WIN32
extern frw_event_mgmt_stru            g_ast_event_manager[WLAN_FRW_MAX_NUM_CORES];
#endif
extern struct data_process_interface  g_st_data_process_interface;
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
extern oal_int32 hmac_backup_user(hmac_user_stru *pst_hmac_user, oal_uint32 ul_user_num, oal_uint32 ul_cur_index);
extern oal_int32 hmac_backup_all_user(oal_void);
extern oal_int32 hmac_recover_user(data_summary_info *pst_user_info);
extern oal_int32 hmac_recover_all_user(oal_void);

extern oal_int32 hmac_backup_vap(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_vap_num, oal_uint32 ul_cur_index);
extern oal_int32 hmac_backup_all_vap(oal_void);
extern oal_int32 hmac_recover_vap(data_summary_info *pst_vap_info);
extern oal_int32 hmac_recover_all_vap(oal_void);

extern oal_int32 hmac_backup_device(hmac_device_stru *pst_hmac_dev, oal_uint32 ul_dev_num, oal_uint32 ul_cur_index);
extern oal_int32 hmac_backup_all_device(oal_void);
extern oal_int32 hmac_recover_device(data_summary_info *pst_hmac_dev_info, data_summary_info *pst_mac_dev_info);
extern oal_int32 hmac_recover_all_device(oal_void);
extern oal_void  hmac_event_printf(oal_void);

extern oal_int32 hmac_backup_mac_addr(oal_uint8 *puc_dev_name);
extern oal_int32 hmac_recover_mac_addr(oal_uint8 *puc_mac_addr);
extern oal_int32 hmac_backup_data(oal_void);
extern oal_int32 hmac_recover_data(oal_void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


