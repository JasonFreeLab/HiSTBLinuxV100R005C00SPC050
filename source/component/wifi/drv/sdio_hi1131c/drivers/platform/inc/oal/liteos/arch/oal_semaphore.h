/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_semaphore.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月10日
  最近修改   :
  功能描述   : oal_semaphore.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月10日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LITEOS_SEMAPHORE_H__
#define __OAL_LITEOS_SEMAPHORE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <los_sem.ph>
#include <los_sem.h>

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
typedef SEM_CB_S oal_semaphore_stru;

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

OAL_STATIC OAL_INLINE oal_void oal_sema_init(oal_semaphore_stru *pst_sem, oal_uint16 us_val)
{
    oal_uint32 ul_semhandle;
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return;
    }

    if (LOS_OK != LOS_SemCreate(us_val, &ul_semhandle))
    {
        OAL_IO_PRINT("LOS_SemCreate failed!\n");
        return;
    }
    *pst_sem = *(GET_SEM(ul_semhandle));    
}


OAL_STATIC OAL_INLINE oal_void oal_up(oal_semaphore_stru *pst_sem)
{
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return;
    }

    if (LOS_OK != LOS_SemPost(pst_sem->usSemID))
    {
        OAL_IO_PRINT("LOS_SemPost failed!\n");
        return;
    }    
}

OAL_STATIC OAL_INLINE oal_void oal_down(oal_semaphore_stru *pst_sem)
{   
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return;
    }

    if (LOS_OK != LOS_SemPend(pst_sem->usSemID, OS_WAIT_FOREVER))
    {
        OAL_IO_PRINT("LOS_SemPend failed!\n");
        return;
    }  
}

OAL_STATIC OAL_INLINE oal_int32 oal_down_timeout(oal_semaphore_stru *pst_sem,oal_uint32 ul_timeout)
{
    oal_uint32 ul_reval = 0;
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return -OAL_EFAIL;
    }

    ul_reval = LOS_SemPend(pst_sem->usSemID, ul_timeout);
    if (LOS_OK != ul_reval)
    {
        return ul_reval;
    }
    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_int32 oal_down_interruptible(oal_semaphore_stru *pst_sem)
{
    oal_uint32 ul_reval = 0;
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return -OAL_EFAIL;
    }

    ul_reval = LOS_SemPend(pst_sem->usSemID, OS_WAIT_FOREVER);
    if (LOS_OK != ul_reval)
    {
        return ul_reval;
    }
    return OAL_SUCC;
}

 OAL_STATIC OAL_INLINE oal_int32 oal_down_trylock(oal_semaphore_stru *pst_sem)
{
    oal_uint32 ul_reval = 0;
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return -OAL_EFAIL;
    }

    ul_reval = LOS_SemPend(pst_sem->usSemID, OS_NO_WAIT);
    if (LOS_OK != ul_reval)
    {
        return ul_reval;
    }
    return OAL_SUCC;
}

 OAL_STATIC OAL_INLINE oal_int32 oal_sema_destroy(oal_semaphore_stru *pst_sem)
 {
    oal_uint32 ul_reval = 0;
    if (NULL == pst_sem)
    {
        OAL_IO_PRINT("[%s]pst_sem is null!\n",__func__);
        return -OAL_EFAIL;
    }

    ul_reval = LOS_SemDelete(pst_sem->usSemID);
    if (LOS_OK != ul_reval)
    {
        return ul_reval;
    }
    return OAL_SUCC;
 }


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_semaphore.h */

