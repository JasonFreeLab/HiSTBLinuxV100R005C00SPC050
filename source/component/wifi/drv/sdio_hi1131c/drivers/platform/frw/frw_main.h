/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_main
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : frw_main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FRW_MAIN_H__
#define __FRW_MAIN_H__

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
#include "frw_ext_if.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_MAIN_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define FRW_ERR_LOG(_uc_vap_id, _puc_string)
#define FRW_ERR_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_ERR_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_ERR_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_ERR_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_ERR_VAR(_uc_vap_id, _c_fmt, ...)

#define FRW_WARNING_LOG(_uc_vap_id, _puc_string)
#define FRW_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_WARNING_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_WARNING_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_WARNING_VAR(_uc_vap_id, _c_fmt, ...)

#define FRW_INFO_LOG(_uc_vap_id, _puc_string)
#define FRW_INFO_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define FRW_INFO_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define FRW_INFO_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define FRW_INFO_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define FRW_INFO_VAR(_uc_vap_id, _c_fmt, ...)

#ifdef _PRE_DEBUG_MODE
#define FRW_EVENT_INTERNAL(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)       oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_FRW, en_event_type, _puc_string)
#else
#define FRW_EVENT_INTERNAL(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)
#endif



#define FRW_TIMER_DEFAULT_TIME          10


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    FRW_TIMEOUT_TIMER_EVENT,      /* 以FRW_TIMER_DEFAULT_TIME为周期的定时器事件子类型 */

    FRW_TIMEOUT_SUB_TYPE_BUTT
}hmac_timeout_event_sub_type_enum;
typedef oal_uint8 hmac_timeout_event_sub_type_enum_uint8;



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
extern oal_int32  frw_main_init(oal_void);
extern oal_void  frw_main_exit(oal_void);
extern oal_void  frw_set_init_state(frw_init_enum_uint16 en_init_state);
extern frw_init_enum_uint16  frw_get_init_state(oal_void);












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_main */
