/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : oal对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_EXT_IF_H__
#define __OAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_util.h"
#include "oal_hardware.h"
#include "oal_schedule.h"
#include "oal_bus_if.h"
#include "oal_mem.h"
#include "oal_net.h"
#include "oal_list.h"
#include "oal_queue.h"
#include "oal_workqueue.h"
#include "arch/oal_ext_if.h"
#include "oal_thread.h"

//#include "oal_gpio.h"
#if (_PRE_PRODUCT_ID !=_PRE_PRODUCT_ID_HI1131C_DEV)
#include "oal_aes.h"
#include "oal_gpio.h"
#endif

/*infusion检查对预编译宏支持不好，在此定义宏支持infusion检查，正式代码不需要*/
#ifdef _PRE_INFUSION_CHECK
#include "oal_infusion.h"
#endif
/*end infusion*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "exception_rst.h"
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    OAL_TRACE_ENTER_FUNC,
    OAL_TRACE_EXIT_FUNC,

    OAL_TRACE_DIRECT_BUTT
}oal_trace_direction_enum;
typedef oal_uint8 oal_trace_direction_enum_uint8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_void                       *g_pst_5115_sys_ctl;
extern oal_void                       *g_pst_5610_mode;
extern oal_void                       *g_pst_5610_gpio;
#if(_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
extern oal_void                       *g_pst_5610_gpio1;
extern oal_void                       *g_pst_5610_gpio2;
#endif
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

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32   oal_main_init(oal_void);
extern oal_void    oal_main_exit(oal_void);
extern oal_uint32 oal_chip_get_version(oal_void);
extern oal_uint8 oal_chip_get_device_num(oal_uint32 ul_chip_ver);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_ext_if.h */
