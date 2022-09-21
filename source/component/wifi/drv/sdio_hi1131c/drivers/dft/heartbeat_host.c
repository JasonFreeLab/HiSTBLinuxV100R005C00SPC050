/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : heartbeat_host.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include <linux/slab.h>
#include "heartbeat_host.h"
#include "plat_debug.h"
#include "plat_pm.h"
#include "oal_sdio_host_if.h"
#include "exception_rst.h"
#include "oal_timer.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HEARTBEAT_HOST_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define BEAT_TIME_MESC             (2000)      /* 心跳超时时间为2秒钟*/

typedef struct _heart_beat
{
    struct timer_list timer;

    #define HEARTBEATEN     (1)
    #define HEARTBEATDIS    (0)
    int32 heartbeat_en;
    
}heart_beat_stru;

heart_beat_stru *g_pst_heartbeat = NULL;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

void set_heartbeat_cfg(int32 cfg)
{
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_ERR("g_pst_heartbeat is  NULL\r\n");
        return;
    }
    g_pst_heartbeat->heartbeat_en = cfg?HEARTBEATEN:HEARTBEATDIS;
}

int32 start_heartbeat(void)
{
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_ERR("g_pst_heartbeat is  NULL\r\n");
        return -EINVAL;
    }
    
    PS_PRINT_INFO("add beat timer\n");
    //mod_timer(&(g_pst_heartbeat->timer), jiffies + BEAT_TIME * HZ);
    oal_timer_start(&(g_pst_heartbeat->timer), BEAT_TIME_MESC);
    g_pst_heartbeat->heartbeat_en = HEARTBEATEN;
    return SUCC;
}

int32 stop_heartbeat (void)
{
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_ERR("g_pst_heartbeat is  NULL\r\n");
        return -EINVAL;
    }
    
    PS_PRINT_INFO("delete beat timer\n");
    g_pst_heartbeat->heartbeat_en = HEARTBEATDIS;
    //del_timer_sync(&(g_pst_heartbeat->timer));
    oal_timer_delete_sync(&(g_pst_heartbeat->timer));
    return SUCC;
}

int32 update_heartbeat(void)
{
    if( (NULL == g_pst_heartbeat) || (HEARTBEATDIS == g_pst_heartbeat->heartbeat_en) )
    {
        PS_PRINT_ERR("g_pst_heartbeat is  NULL, or HEARTBEATDIS == g_pst_heartbeat->heartbeat_en\r\n");
        return -EINVAL;
    }
        
 //   PS_PRINT_DBG("update beat timer\n");
    //mod_timer(&(g_pst_heartbeat->timer), jiffies + BEAT_TIME * HZ);
    oal_timer_start(&(g_pst_heartbeat->timer), BEAT_TIME_MESC);
    return SUCC;
}

    
/***********************************************************************************
 函 数 名  : heartbeat_expire_func
 功能描述  : 心跳超时处理函数，该函数运行在软中断上下文中，不能有引起睡眠的操作
 输入参数  : uint64 data，不需要。加上是为了遵守内核的函数声明
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 
    作    者   : 
    修改内容   : 新生成函数

***********************************************************************************/
static void heartbeat_expire_func(uint64 data)
{
    OAL_REFERENCE(data);
    
    PS_PRINT_ERR("enter heartbeat_expire_func\r\n");
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_ERR("g_pst_heartbeat is NULL\r\n");
        return;
    }
    
    if(HEARTBEATDIS == g_pst_heartbeat->heartbeat_en)
    {
        PS_PRINT_WARNING("g_pst_heartbeat->heartbeat_en disable\r\n");
        update_heartbeat();
        return;
    }

    /*下电时，没有心跳消息上报*/
    if (wlan_is_shutdown())
    {
        PS_PRINT_INFO("device has power off!\r\n");
        return;
    }

    /*睡眠时，没有心跳消息上报*/
    if (HOST_ALLOW_TO_SLEEP == wlan_pm_state_get())
    {
        PS_PRINT_INFO("device has sleep!\r\n");
        return;
    }

    //  todo...    heartbeat exception
    //  in soft interrupt, cannot sleep
    oal_exception_submit(TRANS_FAIL);
    
    return;
}


int32 heart_beat_init(void)
{
    if(NULL != g_pst_heartbeat)
    {
        PS_PRINT_ERR("g_pst_heartbeat is not NULL\r\n");
        return -EINVAL;
    }
    g_pst_heartbeat = kzalloc(sizeof(heart_beat_stru), GFP_KERNEL);
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_ERR("malloc fail, g_pst_heartbeat is NULL\r\n");
        return -ENOMEM;
    }

    //init_timer( &(g_pst_heartbeat->timer) );
    //(g_pst_heartbeat->timer).function = heartbeat_expire_func;
    //(g_pst_heartbeat->timer).expires  = jiffies + BEAT_TIME*HZ;
    //(g_pst_heartbeat->timer).data     = 0;
    
    oal_timer_init(&(g_pst_heartbeat->timer), BEAT_TIME_MESC, heartbeat_expire_func, 0);

    g_pst_heartbeat->heartbeat_en = HEARTBEATDIS;
    return SUCC;
}

void heart_beat_release(void)
{
    if(NULL == g_pst_heartbeat)
    {
        PS_PRINT_WARNING("g_pst_heartbeat is  NULL\r\n");
        return;
    }
    stop_heartbeat();
    kfree(g_pst_heartbeat);
    g_pst_heartbeat = NULL;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

