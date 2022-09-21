/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_stat.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年1月10日
  最近修改   :
  功能描述   : dmac_stat.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月10日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_STAT_H__
#define __DMAC_STAT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_PERFORM_STAT

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "hal_ext_if.h"
#include "frw_ext_if.h"
#include "dmac_user.h"
#include "dmac_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STAT_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define	DMAC_STAT_ITEM_LIMIT                    100     /* 时延，吞吐量，per最大统计周期数 */

#define	DMAC_STAT_TID_DELAY_NODE_LIMIT          128		/* tid时延统计最大节点数量 */
#define DMAC_STAT_TID_PER_NODE_LIMIT            128     /* tid per统计最大节点数 */
#define	DMAC_STAT_TID_THRPT_NODE_LIMIT          128		/* tid吞吐量统计最大节点数量 */
#define	DMAC_STAT_USER_THRPT_NODE_LIMIT         32		/* user吞吐量统计最大节点数量 */
#define DMAC_STAT_VAP_THRPT_NODE_LIMIT          8		/* vap吞吐量统计最大节点数量 */
#define DMAC_STAT_TIMER_CYCLE_MS                100     /* 默认统计周期 */

#define DMAC_STAT_TIME_USEC_INT64(_pst_time) \
    ((oal_int64)((_pst_time)->i_sec) * 1000000 + (_pst_time)->i_usec)

#define DMAC_STAT_TIME_USEC_DIFF(_pst_time1, _pst_time2)    \
    (DMAC_STAT_TIME_USEC_INT64(_pst_time2)- DMAC_STAT_TIME_USEC_INT64(_pst_time1))


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
/* stat_node结构体 */
typedef struct
{
    oal_dlist_head_stru	        st_entry;                               /* 双向链表entry */
    frw_timeout_stru            st_timer;		                        /* 定时器 */

    oal_bool_enum_uint8         uc_stat_flag;                           /* 统计是否使能 */
    oal_uint8                   uc_resv[3];                             /* 字节对齐 */

    dmac_stat_param_stru       *pst_stat_param;                          /* 统计参数 */
    oal_uint32                  us_total_item;                          /* 记录总条数 */
    oal_uint32                  us_curr_item;                           /* 当前第几条 */
    oal_uint32                  aul_stat_cnt[DMAC_STAT_PER_BUTT];            /* 某个统计周期次数 */
    oal_uint32                  aul_stat_sum[DMAC_STAT_PER_BUTT];            /* 某个周期内统计量的累计值 */
    dmac_stat_timeout_func      p_inner_func;                           /* 内部统计模块的函数指针 */

    oal_uint32                 *pul_stat_avg;                           /* 由CFG模块得到的统计平均值存放首地址 */
}dmac_stat_node_stru;

typedef struct
{
	oal_uint32			 ul_node_num;           /* 统计节点数量 */
	oal_dlist_head_stru	 st_stat_node_dlist;    /* 统计节点双向链表头节点 */
}dmac_stat_stru;

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  dmac_stat_init(oal_void);
extern oal_uint32  dmac_stat_exit(oal_void);
extern oal_uint32  dmac_stat_tid_delay(dmac_tid_stru *pst_dmac_tid);
extern oal_uint32  dmac_stat_tx_thrpt(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tidno, hal_tx_dscr_ctrl_one_param st_tx_dscr_param);
extern oal_uint32  dmac_stat_rx_thrpt(frw_event_hdr_stru *pst_event_hdr, mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl);
extern oal_uint32  dmac_stat_display(oam_module_id_enum_uint16       en_module_id,
                                      mac_stat_type_enum_uint8       en_stat_type,
                                      oal_void                      *p_void);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_stat.h */


