/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_thread.h
 * Description   : 线程适配头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_THREAD_H__
#define __HI_ADPT_THREAD_H__

#include "hi_type.h"
#include <stdarg.h>
#include "hi_adp_interface.h"

#if HI_OS_TYPE == HI_OS_LINUX
#include <errno.h>
#elif HI_OS_TYPE == HI_OS_WIN32
#else
#error YOU MUST DEFINE HI OS TYPE HI_OS_TYPE == HI_OS_WIN32 OR HI_OS_LINUX !
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*************************** Structure Definition ****************************/
/** @defgroup hi_adpt_thread_structure thread模块数据结构
 *  @ingroup H2
 *  @brief 详细描述thread模块的数据结构
 *  @{  */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

/*----------------------------------------------*
 * types
 *----------------------------------------------*/

typedef HI_U32 HI_Pthread_T;

#define HI_ERR_OSCALL_ERROR  (-1)
#define HI_INFINITE            0xFFFFFFFF
typedef HI_VOID * (*HI_ThreadFun)(HI_VOID *);
/* Data structure to describe a process' schedulability.  */
typedef struct HI_sched_param
{
    HI_S32 sched_priority;
}HI_SchedParam_S;

/* Attributes for threads.  */
typedef struct HIpthread_attr_s
{
    HI_S32 detachstate;
    HI_S32 schedpolicy;
    HI_SchedParam_S schedparam;
    HI_S32 inheritsched;
    HI_S32 scope;
    HI_SIZE_T guardsize;
    HI_S32 stackaddr_set;
    HI_VOID *stackaddr;
    HI_SIZE_T stacksize;
} HI_ThreadAttr_S;

/*调整进程优先级*/
typedef enum hiVpriority_which
{
    HI_PRIO_PROCESS = 0,             /* WHO is a process ID.  */
    HI_PRIO_PGRP = 1,                /* WHO is a process group ID.  */
    HI_PRIO_USER = 2                 /* WHO is a user ID.  */
}HI_E_Which;

typedef enum hiVrusage_who
{
    /* The calling process.  */
    HI_RUSAGE_SELF = 0,

    /* All of its terminated child processes.  */
    HI_RUSAGE_CHILDREN = -1,

    /* Both.  */
    HI_RUSAGE_BOTH = -2
}HI_E_Who;

/*返回errno*/
HI_S32 HI_GetLastErr(HI_VOID);
/*设置errno*/
HI_VOID HI_SetLastErr(HI_S32 newErrNo);

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/
/*----------------------------------------------*
 * 进程操作
 *----------------------------------------------*/
HI_S32 HI_Execv(const HI_CHAR *path, HI_CHAR *const argv[]);
HI_S32 HI_Execvp(const HI_CHAR *file, HI_CHAR *const argv[]);
HI_S32 HI_Waitpid(HI_PID_T pid,  HI_S32 *status, HI_S32 options);

#if HI_OS_TYPE == HI_OS_WIN32

#define DEBUG_PROCESS               0x00000001
#define DEBUG_ONLY_THIS_PROCESS     0x00000002

#define CREATE_SUSPENDED            0x00000004

#define DETACHED_PROCESS            0x00000008

#define CREATE_NEW_CONSOLE          0x00000010

#define NORMAL_PRIORITY_CLASS       0x00000020
#define IDLE_PRIORITY_CLASS         0x00000040
#define HIGH_PRIORITY_CLASS         0x00000080
#define REALTIME_PRIORITY_CLASS     0x00000100

#define CREATE_NEW_PROCESS_GROUP    0x00000200
#define CREATE_UNICODE_ENVIRONMENT  0x00000400

#define CREATE_SEPARATE_WOW_VDM     0x00000800
#define CREATE_SHARED_WOW_VDM       0x00001000
#define CREATE_FORCEDOS             0x00002000

#define CREATE_DEFAULT_ERROR_MODE   0x04000000
#define CREATE_NO_WINDOW            0x08000000

#define PROFILE_USER                0x10000000
#define PROFILE_KERNEL              0x20000000
#define PROFILE_SERVER              0x40000000

typedef struct HI_PROCESS_INFORMATION {
    HI_VOID *hProcess;
    HI_VOID *hThread;
    HI_U32 dwProcessId;
    HI_U32 dwThreadId;
} HI_PROCESS_S_INFORMATION;
HI_PID_T HI_CreateProcess(HI_CHAR *lpszImageName, HI_CHAR *lpszCmdLine, HI_U32 fdwCreate,HI_PROCESS_S_INFORMATION * lppiProcInfo);

#endif

#ifdef HI_OS_SUPPORT_UCLINUX
#define HI_Fork vfork
#else
HI_PID_T HI_Fork(HI_VOID);
#endif
HI_PID_T HI_Wait(const HI_S32 *status);

#define HI_REBOOT_CMD_RESTART        0x01234567
#define HI_REBOOT_CMD_HALT           0xCDEF0123
#define HI_REBOOT_CMD_CAD_ON         0x89ABCDEF
#define HI_REBOOT_CMD_CAD_OFF        0x00000000
#define HI_REBOOT_CMD_POWER_OFF      0x4321FEDC
#define HI_REBOOT_CMD_RESTART2       0xA1B2C3D4

/** @} */  /*! <!-- Structure Definition end */
/******************************* API declaration *****************************/
/** @defgroup hi_adpt_thread_api sem模块api接口
*   @ingroup H1
*   @brief 详细描述thread模块的API函数
*   @{  */

/**
\brief 初始化一个线程
\attention \n
无
\param[in] attr 线程属性

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadAttrInit(HI_ThreadAttr_S *attr);

/**
\brief 销毁一个线程
\attention \n
无
\param[in] attr 线程属性

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadAttrDestroy(HI_ThreadAttr_S *attr);

/**
\brief 设置线程的分离属性
\attention \n
无
\param[in] attr 线程属性
\param[in] detachstate 分离属性，其合法值有如下两个:
            a)PTHREAD_CREATE_DETACHED，以分离状态启动线程
            b)PTHREAD_CREATE_JOINABLE，正常启动线程

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadAttrSetdetachstate(HI_ThreadAttr_S *attr, HI_S32 detachstate);

/**
\brief 设置当前线程的取消使能属性
\attention \n
无
\param[in] state 新的要设置的取消使能属性，取消状态使能有两种:PTHREAD_CANCEL_ENABLE和PTHREAD_CANCEL_DISABLE.
\param[out] oldstate 以前的取消使能属性
\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadSetCancelState(HI_S32 state, HI_S32 *oldstate);

/**
\brief 设置当前线程的取消类型属性
\attention \n
无
\param[in] state 新的要设置的取消类型属性，取消类型有两种:PTHREAD_CANCEL_DEFERRED和PTHREAD_CANCEL_ASYNCHRONOUS.
\param[out] oldstate 以前的取消使能属性
\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadSetCancelType(HI_S32 type, HI_S32 *oldtype);

/**
\brief 是指定的线程处于分离状态
\attention \n
无
\param[in] th 线程句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadDetach (HI_Pthread_T th) ;

HI_S32 HI_GetPriority(HI_S32 which, HI_S32 who);

HI_S32 HI_SetPriority(HI_S32 which, HI_S32 who, HI_S32 prio);

/**
\brief 创建一个线程
\attention \n
无
\param[in] attr 线程属性
\param[in] start_routine 线程起始执行函数
\param[in] arg start_routine函数输入参数
\param[out] threadp 线程句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32  HI_PthreadCreate (HI_Pthread_T *threadp,
                          const HI_ThreadAttr_S *attr,
                          HI_ThreadFun start_routine,
                          HI_VOID *arg) ;

/**
\brief 获取当前线程的句柄
\attention \n
无
\param[in] attr 线程属性

\retval ::当前线程句柄

\see \n
无
*/
HI_Pthread_T  HI_PthreadSelf (HI_VOID);

/**
\brief 线程退出
\attention \n
无
\param[in] retVal 线程终止码

\retval  \n
无

\see \n
无
*/
HI_VOID HI_PthreadExit ( HI_VOID* retVal);

/**
\brief 取消同一进程中的其他线程
\attention \n
无
\param[in] thread 线程句柄

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadCancel(HI_Pthread_T thread);

/**
\brief 阻塞等待指定的线程返回或取消
\attention \n
无
\param[in] 无

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_S32 HI_PthreadJoin (HI_Pthread_T th, HI_VOID **thread_return);

/**
\brief 延迟指定的秒数
\attention \n
无
\param[in] seconds 秒数

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_U32 HI_Sleep(HI_U32 seconds);

/**
\brief 延迟指定的毫秒数
\attention \n
无
\param[in] seconds 毫秒数

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
无
*/
HI_U32 HI_SleepMs(HI_U32 ms);

/*获取当前线程ID*/
HI_U32 HI_GetPID(HI_VOID);

/*退出*/
HI_VOID HI_Exit(HI_S32 status);

HI_S32 HI_Kill(HI_PID_T pid, HI_S32 sig);

HI_S32 HI_System(HI_CHAR *cmd);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif /* __HI_ADPT_THREAD_H__ */
