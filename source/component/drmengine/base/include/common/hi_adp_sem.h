/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_sem.h
 * Description   : 信号量适配头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_SEM_H__
#define __HI_ADPT_SEM_H__

#include "hi_type.h"
//#include "hi_adp_interface.h"
#include "hi_adp_time.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** @defgroup hi_adpt_sem_structure sem模块数据结构
 *  @ingroup H2
 *  @brief 详细描述sem模块的数据结构
 *  @{  */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/
#define HI_ADPT_SEM_SIZEOF_SEM_T 16
/*----------------------------------------------*
 * types
 *----------------------------------------------*/
typedef union hiSEM_T
{
  HI_CHAR aszSize[HI_ADPT_SEM_SIZEOF_SEM_T];
  HI_S32  s32Align;
} HI_SEM_T;

/** @} */  /*! <!-- Structure Definition end */
/******************************* API declaration *****************************/
/** @defgroup hi_adpt_sem_api sem模块api接口
*   @ingroup H1
*   @brief 详细描述sem模块的API函数
*   @{  */

/**
\brief 初始化一个信号量，在linux下通过man sem_init可以获取详细信息
\attention \n
无
\param[in] s32Pshared 是否进程、线程间共享，0:共享;非0:不共享
\param[in] u32Value 信号量的初始化值
\param[out] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Init(HI_SEM_T *pSem, HI_S32 s32Pshared, HI_U32 u32Value);

/**
\brief 销毁一个信号量，在linux下通过man sem_destroy可以获取详细信息
\attention \n
无
\param[in] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Destroy(HI_SEM_T *pSem);

/**
\brief 打开一个信号量，如果该信号量不存在则创建之
\attention \n
无
\param[in] pszName 信号量名称
\param[in] s32Oflag 信号量控制属性
\param[in] tMode 信号量许可属性，如果信号量已经存在，该参数无意义
\param[in] u32Value 信号量初始值，如果信号量已经存在，该参数无意义

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_SEM_T * HI_SEM_Open(const HI_CHAR *pszName, HI_S32 s32Oflag,HI_MODE_T tMode,
                       HI_U32 u32Value);

/**
\brief 关闭一个信号量
\attention \n
无
\param[in] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Close(HI_SEM_T *pSem);

/**
\brief 等待一个信号量
\attention \n
无
\param[in] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Wait(HI_SEM_T *pSem);

/**
\brief 试图等待一个信号量，如果该信号量已经被占用则直接返回
\attention \n
无
\param[in] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_TryWait(HI_SEM_T *pSem);

/**
\brief 带定时器等待一个信号量，如果在规定时间内等不到信号量则直接返回
\attention \n
无
\param[in] pSem 信号量句柄
\param[in] pstAbs_timeout 等待超时时间

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_TimedWait(HI_SEM_T *pSem,const HI_Timespec_S* pstAbs_timeout);

/**
\brief 释放一个信号量
\attention \n
无
\param[in] pSem 信号量句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Post(HI_SEM_T *pSem);

/**
\brief 获取信号量当前值
\attention \n
无
\param[in] pSem 信号量句柄
\param[out] ps32Sval 信号量的值

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_SEM_Getvalue(HI_SEM_T *pSem,HI_S32* ps32Sval);
/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_ADPT_SEM_H__*/
