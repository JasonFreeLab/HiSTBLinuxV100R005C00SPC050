/***********************************************************************************
*              Copyright 2006 - 2006, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_adp_threadmng.h
* Description: wait thread finish model .
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.1       2006-04-26   q63946     NULL         Create this file.
***********************************************************************************/

#ifndef __HI_ADPT_THREADMNG_H__
#define __HI_ADPT_THREADMNG_H__

#include "hi_type.h"
#include "hi_adp_thread.h"
#include "hi_unf_version.h"
#include "hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HI_PTHREAD_INVALID_THREADID 0x0

#define HI_PTHREAD_STATUS_INIT  0x0
#define HI_PTHREAD_STATUS_START 0x1
#define HI_PTHREAD_STATUS_STOP  0x2
//#ifndef HI_ADVCA_FUNCTION_RELEASE

typedef HI_VOID* (*HI_PTR_FN_THREAD_ENDProc)(HI_VOID* pvParam);
HI_S32 HI_PthreadMNG_Init();

HI_S32 HI_PthreadMNG_Deinit();

HI_S32  HI_PthreadMNG_CreateD(HI_CHAR* pszPthreadInfo,HI_Pthread_T *pu32Threadp,
                             const HI_ThreadAttr_S *pstruAttr,
                             HI_ThreadFun pfunStart_routine, HI_VOID* pvArg,
                             HI_CHAR* pszFile,HI_S32 s32Line);

#define HI_PthreadMNG_Create(pszPthreadInfo,pu32Threadp, pstruAttr,    \
                              pfunStart_routine, pvArg)    \
        HI_PthreadMNG_CreateD((pszPthreadInfo),(pu32Threadp),(pstruAttr),   \
                             (pfunStart_routine), (pvArg),__FILE__,__LINE__)

HI_S32 HI_PthreadMNG_RegisterEndProc(HI_Pthread_T u32Thread,
                                    HI_PTR_FN_THREAD_ENDProc pfunEndProc,
                                    HI_VOID* pvParam);

HI_S32 HI_PthreadMNG_Join(HI_Pthread_T u32Thread);

HI_S32 HI_PthreadMNG_Add(HI_Pthread_T u32Thread, HI_CHAR* pszPthreadInfo);

HI_S32 HI_PthreadMNG_Del(HI_Pthread_T u32Thread);

HI_S32 HI_PthreadMNG_Exit();

HI_S32 HI_PthreadMNG_Wait();

//HI_S32 HI_PthreadMNG_Query(HI_Pthread_T u32Thread);

HI_S32 HI_PthreadMNG_PrintInfo(HI_U32 u32OutHandle, HI_PID_T u32ThreadPID);

/*
thread
    -pid [0~]   ;打印指定线程PID信息，0代表打印所以线程
*/
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
HI_S32 HI_CMD_ThreadList(HI_PROC_SHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);
#else
HI_S32 HI_CMD_ThreadList(HI_U32 u32Handle, HI_S32 argc, const char* argv[]);
#endif
//#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ADPT_THREADMNG_H__ */
