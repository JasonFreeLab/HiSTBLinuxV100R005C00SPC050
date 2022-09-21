/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_main
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : dmac_main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_MAIN_H__
#define __DMAC_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "mac_resource.h"
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MAIN_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_EVENT
#define DMAC_EVENT_PAUSE_OR_RESUME_TID(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)  oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_DMAC, en_event_type, _puc_string)
#define DMAC_EVENT_PAUSE_OR_RESUME_USER(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string) oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_DMAC, en_event_type, _puc_string)
#else
#define DMAC_EVENT_PAUSE_OR_RESUME_TID(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)
#define DMAC_EVENT_PAUSE_OR_RESUME_USER(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string) ((void)(_puc_string))
#endif
typedef oal_void  (*dmac_set_dscr_func)(oal_int32,oal_uint8,dmac_vap_stru*);

/*检查函数返回值是否是OAL_SUCC*/
/*lint -e607*/
#define DMAC_CHECK_RET(ul_ret)        \
    if (OAL_SUCC != ul_ret)                      \
    {                                            \
        return ul_ret;                           \
    }

#define DMAC_CHECK_NULL(ptr)        \
    if (OAL_PTR_NULL == ptr)                     \
    {                                            \
        return OAL_ERR_CODE_PTR_NULL;            \
    }

/*lint +e607*/

/* 填写DMAC到HMAC配置同步消息头 */
#define DMAC_INIT_SYN_MSG_HDR(_pst_syn_msg, _en_syn_id, _us_len) \
    do {                                            \
        (_pst_syn_msg)->en_syn_id = (_en_syn_id);   \
        (_pst_syn_msg)->us_len = (_us_len);   \
    } while(0)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    FRW_DMAC_TO_HMAC_UPDATE_USER_TIMESTAMP,  /* 更新USER时间戳 */

    FRW_DMAC_TO_HMAC_BUTT
}frw_dmac_to_hmac_syn_enum;
typedef oal_uint16 frw_dmac_to_hmac_syn_enum_uint16;

/*dmac层时间维护结构体*/
typedef struct
{
    oal_time_us_stru  st_timestamp_us;        /* 保存向外提供的时间戳 */
    oal_uint32        ul_last_timestamp;      /* 保存最近一次的硬件时间戳*/
    frw_timeout_stru  st_timer;               /* 定时器 */

}dmac_timeStamp_stru;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* DMAC模块, MISC事件处理函数表定义 */
#ifdef _PRE_WLAN_FEATURE_DBAC
extern frw_event_sub_table_item_stru g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT];
#endif


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/* 读取和设置寄存器的结构体 */
typedef struct
{
    oal_uint32      ul_addr;
    oal_uint16      us_len;
    oal_uint8       uc_mode;
    oal_uint8       auc_resv[1];
    oal_uint32      ul_reg_val;
}dmac_sdt_reg_frame_stru;

#ifdef _PRE_WLAN_DFT_REG
oal_uint32 dmac_reg_report(frw_event_mem_stru *pst_event_mem);
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_tx_excp_free_mgmt_frame
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_excp_free_mgmt_frame(oal_netbuf_stru *pst_netbuf)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_netbuf_free(pst_netbuf);
#endif
}

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  dmac_main_exit(oal_void);
extern oal_int32  dmac_main_init(oal_void);
extern oal_void dmac_timestamp_get(oal_time_us_stru *pst_usec);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem);
#endif
#ifdef _PRE_WLAN_REALTIME_CALI
extern oal_uint32  dmac_rf_realtime_cali_timeout(oal_void * p_arg);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_main */
