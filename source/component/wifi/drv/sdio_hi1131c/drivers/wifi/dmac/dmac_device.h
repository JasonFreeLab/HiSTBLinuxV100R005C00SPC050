/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_device.h
  版 本 号   : 初稿
  作    者   : 张炜 
  生成日期   : 2015年5月7日
  最近修改   :
  功能描述   : dmac_main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月7日
    作    者   : 张炜 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_DEVICE_H__
#define __DMAC_DEVICE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mac_device.h"
#include "dmac_alg_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DEVICE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MAX_MAC_ERR_IN_TBTT 5   /*每一个tbtt间隙允许出现的最大错误数*/

#define DMAC_COMPATIBILITY_RATE_LIMIT_TABLE \
  { /* 带宽       11A  11B  11G  MIXED_ONE_11G  MIXED_TWO_11G  HT       VHT      HT_ONLY   VHT_ONLY   HT_11G  (Kbp/s)*/  \
    /* 20M  */ {   0,   0,   0,   0,             0,            60000,   70000,   60000,    70000,     60000}, \
    /* 40M  */ {   0,   0,   0,   0,             0,            80000,   100000,  80000,    100000,    80000}, \
    /* 80M  */ {   0,   0,   0,   0,             0,            0,       0,       0,        0,         0}, \
    /* 160M */ {   0,   0,   0,   0,             0,            0,       0,       0,        0,         0}, \
  }


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
/* Dmac device结构体，记录只保存在Dmac的device公共信息 */
/* 设备距离状态 */
typedef struct
{
    dmac_alg_tpc_user_distance_enum_uint8           en_dmac_device_distance_enum;
    dmac_alg_cca_opt_intf_mode_enum_uint8           en_cca_intf_state;
    oal_bool_enum_uint8                             en_co_intf_state;
    oal_uint8                                       uc_resv[1];
} dmac_alg_stat_stru;

typedef struct
{
    oal_uint32              ul_rx_rate;
    oal_uint16              us_rx_rate_stat_count;
    oal_bool_enum_uint8     en_compatibility_enable;
    oal_bool_enum_uint8     en_compatibility_stat;
    oal_uint32              aul_compatibility_rate_limit[WLAN_BW_CAP_BUTT][WLAN_PROTOCOL_BUTT];
} dmac_compatibility_stat_stru;


/* dmac device结构体，记录只保存在dmac的device公共信息 */
typedef struct
{
    mac_device_stru                    *pst_device_base_info;                   /* 指向公共部分mac device */
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_bool_enum_uint8                 en_dfr_hw_reset_enable;                 //device侧hw reset的使能开关
    oal_uint8                           auc_rev[3];
#endif //_PRE_WLAN_DFT_STAT

    dmac_alg_stat_stru                  st_dmac_alg_stat;
    dmac_compatibility_stat_stru        st_dmac_compatibility_stat;
}dmac_device_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
 函 数 名  : dmac_fcs_get_mgr_stru
 功能描述  : 获取指定device的fcs mgr
 输入参数  : mac_device_stru *pst_device
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE mac_fcs_mgr_stru *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_fcs_mgr_stru* dmac_fcs_get_mgr_stru(mac_device_stru *pst_device)
{
#if IS_DEVICE
    return  &pst_device->st_fcs_mgr;
#else
    return OAL_PTR_NULL;
#endif
}


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
  10.1 公共结构体初始化、删除
*****************************************************************************/

extern oal_uint32  dmac_board_exit(mac_board_stru *pst_board);
extern oal_uint32  dmac_board_init(mac_board_stru *pst_board);

/*****************************************************************************
  10.2 公共成员访问部分
*****************************************************************************/
extern oal_uint32  dmac_mac_error_overload(mac_device_stru *pst_mac_device, hal_mac_error_type_enum_uint8 en_error_id);
extern oal_void  dmac_mac_error_cnt_clr(mac_device_stru *pst_mac_device);
extern oal_void  dmac_mac_error_cnt_inc(mac_device_stru *pst_mac_device, oal_uint8 uc_mac_int_bit);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_device.h */
