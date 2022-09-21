/***********************************************************
*                      Copyright    , 2009-2050, Hisilicon Tech. Co., Ltd.
*                                   ALL RIGHTS RESERVED
* FileName:  hi_timer.h
* Description:timer组件对外头文件
*
* History:
* Version   Date                Author            DefectNum      Description
* main\1    2009-3-17     chenling102556      NULL          Create this file.
************************************************************/
#ifndef __HI_TIMER_H__
#define __HI_TIMER_H__

/*include header files*/
#include "hi_type.h"
#include <pthread.h>
#include "petimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/******************************* API declaration *****************************/
/** @defgroup hi_timer_api timer模块api接口
*   @ingroup H1
*   @brief 详细描述timer模块的API函数
*   @{  */

/**
\brief 创建一个timer
\attention \n
无
\param[in] HI_VOID (*timeout)(HI_VOID *) timer到时回调函数
\param[in] mode timer模式，有下面三种:
           a)PETF_AUTO_RESTART:timer定时到时自动进入下一次timer计时
           b)PETF_ONE_SHOOT:timer定时到时停止
           c)PETF_AUTO_FREE:timer定时到时自动销毁

\retval ::timer句柄
\retval ::HI_ERRCODE

\see \n
无
*/
petimer_t  HI_TIMER_Create(HI_VOID (*timeout)(HI_VOID *), HI_S32 mode);

/**
\brief 销毁一个timer
\attention \n
无
\param[in] timer timer句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32  HI_TIMER_Destroy(petimer_t timer);

/**
\brief 去使能一个timer
\attention \n
无
\param[in] timer timer句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32  HI_TIMER_Disable(petimer_t timer);

/**
\brief 使能一个timer
\attention \n
无
\param[in] timer timer句柄
\param[in] msec timer时间间隔

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32  HI_TIMER_Enable (petimer_t timer, HI_U32 msec);

/**
\brief 使能一个timer
\attention \n
无
\param[in] timer timer句柄
\param[in] msec timer时间间隔
\param[in] args timer回掉函数的输入参数

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32  HI_TIMER_EnableEx (petimer_t timer, HI_U32 msec, HI_VOID *args);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */
#endif /*__HI_TIMER_H__*/
