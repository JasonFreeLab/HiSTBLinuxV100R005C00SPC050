/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_spinlock.h
  版 本 号   : 初稿
  作    者   : ds
  生成日期   : 2016年7月27日
  最近修改   :
  功能描述   : oal_spinlock.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年7月27日
    作    者   : ds
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_SPINLOCK_H__
#define __OAL_LINUX_SPINLOCK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_SPINLOCK_H

#include <linux/spinlock.h>


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define OAL_SPIN_LOCK_MAGIC_TAG (0xdead4ead)
typedef struct _oal_spin_lock_stru_
{
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
    oal_uint32  magic;
    oal_uint32  reserved;
#endif
    spinlock_t  lock;
}oal_spin_lock_stru;

#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
#define OAL_DEFINE_SPINLOCK(x) 	 oal_spin_lock_stru x = {\
            .magic = OAL_SPIN_LOCK_MAGIC_TAG,\
            .lock = __SPIN_LOCK_UNLOCKED(x)}
#else
#define OAL_DEFINE_SPINLOCK(x) 	 oal_spin_lock_stru x = {\
            .lock = __SPIN_LOCK_UNLOCKED(x)}
#endif

/* 函数指针，用来指向需要自旋锁保护的的函数 */
typedef oal_uint32              (*oal_irqlocked_func)(oal_void *);


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
/*****************************************************************************
 函 数 名  : oal_spin_lock_init
 功能描述  : 自旋锁初始化，把自旋锁设置为1（未锁状态）。
 输入参数  : *pst_lock: 锁的地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_init(oal_spin_lock_stru *pst_lock)
{
    spin_lock_init(&pst_lock->lock);
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG	
    pst_lock->magic = OAL_SPIN_LOCK_MAGIC_TAG;
#endif
}

OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_magic_bug(oal_spin_lock_stru *pst_lock)
{
#ifdef CONFIG_SPIN_LOCK_MAGIC_DEBUG
    if(OAL_UNLIKELY((oal_uint32)OAL_SPIN_LOCK_MAGIC_TAG != pst_lock->magic))
    {
#ifdef CONFIG_PRINTK
        /*spinlock never init or memory overwrite?*/
    	printk(KERN_EMERG "[E]SPIN_LOCK_BUG: spinlock:%p on CPU#%d, %s,magic:%08x should be %08x\n", pst_lock,
    	                    raw_smp_processor_id(),current->comm, pst_lock->magic,OAL_SPIN_LOCK_MAGIC_TAG);
        print_hex_dump(KERN_EMERG, "spinlock_magic: ", DUMP_PREFIX_ADDRESS, 16, 1,
	       (oal_uint8 *)((oal_ulong)pst_lock - 32), 32 + sizeof(oal_spin_lock_stru) + 32, true);
        printk(KERN_EMERG"\n");
#endif
        OAL_WARN_ON(1);
    }
#endif
}

/*****************************************************************************
 函 数 名  : oal_spin_lock
 功能描述  : 自旋锁在软中断以及内核线程等核心态上下文环境下的加锁操作。如果
             能够立即获得锁，它就马上返回，否则，它将自旋在那里，直到该自旋
             锁的保持者释放，这时，它获得锁并返回。
 输入参数  : *pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock
 功能描述  : Spinlock在内核线程等核心态上下文环境下的解锁操作。
 输入参数  : *pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_bh
 功能描述  : 自旋锁在软中断以及内核线程等核心态上下文环境下的加锁操作。如果
             能够立即获得锁，它就马上返回，否则，它将自旋在那里，直到该自旋
             锁的保持者释放，这时，它获得锁并返回。
 输入参数  : pst_lock:自旋锁地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_spin_lock_bh(oal_spin_lock_stru *pst_lock)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_bh(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_bh
 功能描述  : Spinlock在软中断以及内核线程等核心态上下文环境下的解锁操作。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_spin_unlock_bh(oal_spin_lock_stru *pst_lock)
{
     oal_spin_lock_magic_bug(pst_lock);
     spin_unlock_bh(&pst_lock->lock);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_save
 功能描述  : 获得自旋锁的同时获得保存标志寄存器的值，并且失效本地中断。
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_lock_irq_save(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_lock_irqsave(&pst_lock->lock, *pui_flags);
}

/*****************************************************************************
 函 数 名  : oal_spin_unlock_irq_restore
 功能描述  : 释放自旋锁的同时，恢复标志寄存器的值，恢复本地中断。它与oal_sp-
             in_lock_irq配对使用
 输入参数  : *pst_lock:自旋锁地址
             pui_flags:标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_spin_unlock_irq_restore(oal_spin_lock_stru *pst_lock, oal_uint *pui_flags)
{
    oal_spin_lock_magic_bug(pst_lock);
    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);
}

/*****************************************************************************
 函 数 名  : oal_spin_lock_irq_exec
 功能描述  : 获取自旋锁，关闭中断，执行某个函数，完了之后再打开中断，释放自
             旋锁。
 输入参数  : *pst_lock:自旋锁地址
             func：函数指针地址
             *p_arg：函数参数
             *pui_flags: 中断标志寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_spin_lock_irq_exec(oal_spin_lock_stru *pst_lock, oal_irqlocked_func func, oal_void *p_arg, oal_uint *pui_flags)
{
    oal_uint32  ul_rslt;

    spin_lock_irqsave(&pst_lock->lock, *pui_flags);

    ul_rslt = func(p_arg);

    spin_unlock_irqrestore(&pst_lock->lock, *pui_flags);

    return ul_rslt;
}











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_spinlock.h */

