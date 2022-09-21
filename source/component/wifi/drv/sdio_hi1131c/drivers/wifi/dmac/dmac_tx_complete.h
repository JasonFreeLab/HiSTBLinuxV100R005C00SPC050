/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_tx_complete.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月13日
  最近修改   :
  功能描述   : dmac_tx_complete.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月13日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_TX_COMPLETE_H__
#define __DMAC_TX_COMPLETE_H__

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
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "mac_device.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_user.h"
#include "dmac_vap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_stat.h"
#include "dmac_main.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_COMPLETE_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
#define DMAC_MAX_RA_LUT_INDEX   32
#define WLAN_CHIP_MAX_NUM       2
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint8 g_uc_aggr_num_switch;     /* 设置最大AMPDU聚合个数开关 */
extern oal_uint8 g_uc_max_aggr_num;     /* 设置最大AMPDU聚合个数 */


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
typedef struct
{
    oal_uint8   uc_pn_peer_idx;     /* 对端peer索引,0~31 */
    oal_uint32  ul_pn_msb;          /* 发送描述符pn值的高32位 */
    oal_uint32  ul_pn_lsb;          /* 发送描述符pn值的低32位 */
}dmac_tx_dscr_pn_stru;

typedef struct
{
    oal_uint32  ul_pn_msb;          /* 发送描述符pn值的高32位 */
    oal_uint32  ul_pn_lsb;          /* 发送描述符pn值的低32位 */
    oal_uint32  ul_phy_mode_one;    /* 发送描述符phy mode字段 */
    oal_uint16  us_seq_num;    /* 发送描述符seq num */
    hal_tx_dscr_ctrl_one_param st_tx_dscr_one; /* 发送描述符中的ctrl one param字段 */
}dmac_tx_dscr_mac_phy_param_stru;
#endif
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_tx_complete_event_handler(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_tx_reset_flush(hal_to_dmac_device_stru *pst_device);
extern oal_uint32  dmac_tx_complete_schedule(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ac_num);
#if 0
extern oal_void  dmac_tx_delete_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_delete_dscr);
#endif
extern oal_uint32  dmac_tx_complete_buff(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_dscr);
extern oal_uint32  dmac_mgmt_tx_complete(mac_vap_stru *pst_mac_vap, oal_uint8 mgmt_frame_id, oal_uint32 uc_dscr_status, oal_uint8 uc_user_idx);
extern oal_void  dmac_tx_complete_free_dscr(hal_tx_dscr_stru *pst_dscr);
extern oal_void  dmac_tx_complete_free_dscr_list(hal_tx_dscr_stru *pst_dscr, oal_uint8 uc_dscr_num);
extern oal_void  dmac_tx_delete_ba(dmac_user_stru *pst_dmac_user);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_tx_complete.h */
