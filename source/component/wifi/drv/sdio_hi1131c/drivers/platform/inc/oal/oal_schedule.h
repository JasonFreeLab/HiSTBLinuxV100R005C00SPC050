/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_schedule.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月29日
  最近修改   :
  功能描述   : oal_types.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_SCHEDULE_H__
#define __OAL_SCHEDULE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_hardware.h"
#include "oal_mm.h"
#include "arch/oal_schedule.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define oal_sys_wdt_start(mode,msec)
#define oal_sys_wdt_start_int(msec)
#define oal_sys_wdt_start_noint(msec)
#define oal_sys_wdt_stop()
#define oal_sys_wdt_feed()

#define oal_sys_bus_idle()

typedef enum
{
    OAL_DFT_TRACE_OTHER = 0x0,
    OAL_DFT_TRACE_SUCC   ,
    OAL_DFT_TRACE_FAIL   ,/*> fail while dump the key_info to kernel*/
    OAL_DFT_TRACE_EXCEP  , /*exception*/
    OAL_DFT_TRACE_BUTT   ,
}oal_dft_type;

#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
#include "oal_list.h"
#include <linux/rtc.h>
typedef struct _oal_dft_trace_item_
{
    oal_list_entry_stru list;
    char* name;
    oal_uint16  dft_type;
    oal_uint16  trace_flag;/*add the the list*/
    oal_uint32  trace_count;
    struct timeval  first_timestamp;/*first keyinfo timestamp*/
    struct timeval  last_timestamp;/*last keyinfo timestamp*/
}oal_dft_trace_item;
//extern oal_spin_lock_stru;
extern oal_spin_lock_stru g_dft_head_lock;
extern oal_list_head_stru g_dft_head;
extern oal_int32 oal_dft_init(oal_void);
extern oal_void oal_dft_exit(oal_void);
extern oal_void oal_dft_print_error_key_info(oal_void);
extern oal_void oal_dft_print_all_key_info(oal_void);

/*关键流程发生时间点记录，有加锁动作，慎用*/
#define DECLARE_DFT_TRACE_KEY_INFO(dname,dtype)\
        do\
        {\
            oal_ulong flags;\
            OAL_STATIC oal_dft_trace_item st_dft_item = {{0},NULL,0,0,0,{0},{0}};\
            oal_spin_lock_irq_save(&g_dft_head_lock, &flags);\
            if(!st_dft_item.trace_flag)\
            {\
                oal_list_add(&st_dft_item.list, &g_dft_head);\
                st_dft_item.name = dname;\
                st_dft_item.dft_type = dtype;\
                st_dft_item.trace_flag =1;\
            }\
            st_dft_item.trace_count++;\
            oal_spin_unlock_irq_restore(&g_dft_head_lock, &flags);\
            if((!st_dft_item.first_timestamp.tv_sec) && (!st_dft_item.first_timestamp.tv_usec))\
            {\
                oal_do_gettimeofday(&st_dft_item.first_timestamp);\
            }\
            else\
            {\
                oal_do_gettimeofday(&st_dft_item.last_timestamp);\
            }\
            if(OAL_UNLIKELY(dtype >= OAL_DFT_TRACE_FAIL))\
            {\
                printk(KERN_ERR "[E]key_info:%s happened[%u]!\n",dname,st_dft_item.trace_count);\
                oal_dft_print_error_key_info();\
            }\
        }while(0)
#else
#define DECLARE_DFT_TRACE_KEY_INFO(dname,dtype)
#endif


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
#ifdef _PRE_CONFIG_HISI_CONN_SOFTWDFT
extern oal_int32 oal_softwdt_init(oal_void);
extern oal_void oal_softwdt_exit(oal_void);
#else
OAL_STATIC OAL_INLINE oal_int32 oal_softwdt_init(oal_void)
{
    return OAL_SUCC;
}
OAL_STATIC OAL_INLINE oal_void oal_softwdt_exit(oal_void)
{
    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
