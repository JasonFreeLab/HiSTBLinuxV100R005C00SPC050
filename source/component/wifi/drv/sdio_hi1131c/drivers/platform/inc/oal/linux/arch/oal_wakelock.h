/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_wakelock.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年07月29日
  最近修改   :
  功能描述   : oal_wakelock.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年07月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_WAKE_LOCK_H__
#define __OAL_LINUX_WAKE_LOCK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include <linux/wakelock.h>
#include "oal_mutex.h"

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
typedef struct _oal_wakelock_stru_
{
#ifdef CONFIG_HAS_WAKELOCK
    struct wake_lock        st_wakelock;        //wakelock锁
    oal_spin_lock_stru      lock;    //wakelock锁操作spinlock锁
#endif
    oal_ulong               lock_count;         //持有wakelock锁的次数
    oal_ulong               locked_addr;/*the locked address*/
}oal_wakelock_stru;


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
  7 宏定义
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


OAL_STATIC OAL_INLINE oal_void oal_wake_lock_init(oal_wakelock_stru *pst_wakelock,char* name)
{
#ifdef CONFIG_HAS_WAKELOCK
    oal_memset((oal_void*)pst_wakelock,0,sizeof(oal_wakelock_stru));

    wake_lock_init(&pst_wakelock->st_wakelock, WAKE_LOCK_SUSPEND, name ? name:"wake_lock_null");
    oal_spin_lock_init(&pst_wakelock->lock);
    pst_wakelock->lock_count = 0;
    pst_wakelock->locked_addr = 0;
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_wake_lock_exit(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_HAS_WAKELOCK
    wake_lock_destroy(&pst_wakelock->st_wakelock);
#endif
}

OAL_STATIC OAL_INLINE void oal_wake_lock(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_HAS_WAKELOCK
    oal_ulong ul_flags;

    oal_spin_lock_irq_save(&pst_wakelock->lock, &ul_flags);
    if(!pst_wakelock->lock_count)
    {
        wake_lock(&pst_wakelock->st_wakelock);
        pst_wakelock->locked_addr = (oal_ulong)_RET_IP_;
    }
    pst_wakelock->lock_count++;
    oal_spin_unlock_irq_restore(&pst_wakelock->lock, &ul_flags);
#endif
}

OAL_STATIC OAL_INLINE  void oal_wake_unlock(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_HAS_WAKELOCK
    oal_ulong ul_flags;

    oal_spin_lock_irq_save(&pst_wakelock->lock, &ul_flags);
    if(pst_wakelock->lock_count)
    {
        pst_wakelock->lock_count--;
        if(!pst_wakelock->lock_count)
        {
            wake_unlock(&pst_wakelock->st_wakelock);
            pst_wakelock->locked_addr = (oal_ulong)0x0;
        }
    }
    oal_spin_unlock_irq_restore(&pst_wakelock->lock, &ul_flags);
#endif
}

OAL_STATIC OAL_INLINE oal_uint oal_wakelock_active(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_HAS_WAKELOCK
    return wake_lock_active(&pst_wakelock->st_wakelock);
#else
    return 0;
#endif
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_wakelock.h */



