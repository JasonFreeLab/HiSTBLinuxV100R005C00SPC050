/******************************************************************************
Copyright (C), 2015-2025, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     : hi_time.h
Version       : Initial draft
Author        : HiSilicon DTV stack software group
Created Date  : 2015-08-24
Last Modified by: T00219055
Description   : Application programming interfaces (APIs) of Time module.
Function List :
Change History:
******************************************************************************/

#ifndef __HI_LOG_H__
#define __HI_LOG_H__

#include <stdio.h>
#include <stdlib.h>

#include "hi_type.h"

#include "utils/Logger.h"
#include "hi_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifndef SVR_MODULE_DECLARE
#define SVR_MODULE_DECLARE(MODULE_NAME)
#endif

#ifndef HI_LOG_DEBUG
#define HI_LOG_DEBUG(...) ((void)LOGGER(HI_LOGGER_DEBUG, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#ifndef HI_LOG_INFO
#define HI_LOG_INFO(...) ((void)LOGGER(HI_LOGGER_INFO, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef HI_LOG_ERROR
#define HI_LOG_ERROR(...) ((void)LOGGER(HI_LOGGER_ERROR, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef HI_FRM_LOGD
#define HI_FRM_LOGD(...) ((void)LOGGER(HI_LOGGER_DEBUG, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#ifndef HI_FRM_LOGI
#define HI_FRM_LOGI(...) ((void)LOGGER(HI_LOGGER_INFO, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef HI_FRM_LOGE
#define HI_FRM_LOGE(...) ((void)LOGGER(HI_LOGGER_ERROR, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef SVR_LOG_DEBUG
#define SVR_LOG_DEBUG(...) ((void)LOGGER(HI_LOGGER_DEBUG, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef SVR_LOG_ERROR
#define SVR_LOG_ERROR(...) ((void)LOGGER(HI_LOGGER_ERROR, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#ifndef SVR_LOG_INFO
#define SVR_LOG_INFO(...) ((void)LOGGER(HI_LOGGER_INFO, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif

#define HI_LOG_ERROR_NO( error_no, pszFormat...)

//#define SVR_PROC_Printf HI_PROC_Printf

//函数参数检查
#define SVR_LOG_CHK_PARA( val  )           \
        do                                                      \
        {                                                       \
            if ((val))                                          \
            {                                                   \
                SVR_LOG_ERROR("Invalid Parameter"); \
                return HI_FAILURE;                                    \
            };                                                   \
        } while (0)

#define HI_LOG_CHK_PARA( val  )           \
                    do                                                      \
                    {                                                       \
                        if ((val))                                          \
                        {                                                   \
                            SVR_LOG_ERROR("Invalid Parameter"); \
                            return HI_FAILURE;                                    \
                        };                                                   \
                    } while (0)

/*-----------------------------------------------------------------*/
// 检查期望值，如果不对，返回该指定错误码 , val要写错误情况的判断
#define SVR_LOG_CHK_RETURN_ERR(val, ret )                            \
            do                                                      \
            {                                                       \
                if ((val))                                          \
                {                                                   \
                    SVR_LOG_ERROR("");                       \
                    return ret;                                    \
                }                                                   \
            } while (0)

#define HI_LOG_CHK_RETURN_ERR(val, ret )                            \
            do                                                      \
            {                                                       \
                if ((val))                                          \
                {                                                   \
                    SVR_LOG_ERROR("");                       \
                    return ret;                                    \
                }                                                   \
            } while (0)

/*-----------------------------------------------------------------*/
// 检查期望值，如果不对，打印错误信息, val要写错误情况的判断
#define SVR_LOG_CHK_PRINT_ERR(val, ret)                  \
do                                                      \
{                                                       \
    if ((val))                                          \
    {                                                   \
        SVR_LOG_ERROR("");                    \
    }                                                   \
} while (0)

#define HI_LOG_CHK_PRINT_ERR(val, ret)                  \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            SVR_LOG_ERROR("");                    \
        }                                                   \
    } while (0)

/* 如果func执行失败，只打印出错信息，不返回 */
#define SVR_LOG_DOFUNC( func )                            \
            do{                                         \
                HI_S32 s32LogRet = 0 ;                        \
                s32LogRet = func ;                            \
                if(s32LogRet != HI_SUCCESS)                   \
                {                                        \
                    SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);           \
                };                                       \
            }while(0)

#define HI_LOG_DOFUNC( func )                            \
            do{                                         \
                HI_S32 s32LogRet = 0 ;                        \
                s32LogRet = func ;                            \
                if(s32LogRet != HI_SUCCESS)                   \
                {                                        \
                    SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);           \
                };                                       \
            }while(0)

/*-----------------------------------------------------------------*/
 /* 如果func执行失败，则直接返回被调函数的返回值 */
#define SVR_LOG_DOFUNC_RETURN( func )                            \
                    do{                                         \
                        HI_S32 s32LogRet = 0 ;                        \
                        s32LogRet = func ;                            \
                        if(s32LogRet != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);          \
                            return s32LogRet;                        \
                        };                                       \
                    }while(0)

#define HI_LOG_DOFUNC_RETURN( func )                            \
                    do{                                         \
                        HI_S32 s32LogRet = 0 ;                        \
                        s32LogRet = func ;                            \
                        if(s32LogRet != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);          \
                            return s32LogRet;                        \
                        };                                       \
                    }while(0)

/*-----------------------------------------------------------------*/
/* 如果func执行失败，则返回指定的错误码 */
#define SVR_LOG_DOFUNC_RETURN_ERR( func ,err)                            \
                    do{                                         \
                        HI_S32 s32LogRet = 0 ;                        \
                        s32LogRet = func ;                            \
                        if(s32LogRet != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);          \
                            return err;                        \
                        };                                       \
                    }while(0)

#define HI_LOG_DOFUNC_RETURN_ERR( func ,err)                            \
                    do{                                         \
                        HI_S32 s32LogRet = 0 ;                        \
                        s32LogRet = func ;                            \
                        if(s32LogRet != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);          \
                            return err;                        \
                        };                                       \
                    }while(0)
/*-----------------------------------------------------------------*/
/* 如果func执行失败，则返回void */
#define SVR_LOG_DOFUNC_RETURN_VOID(func)                 \
                do{\
                    HI_S32 s32LogRet = func;                  \
                    if(s32LogRet != HI_SUCCESS)               \
                    { \
                        SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);    \
                        return ;                        \
                    }                                   \
                }while(0)
#define HI_LOG_DOFUNC_RETURN_VOID(func)                 \
                do{\
                    HI_S32 s32LogRet = func;                  \
                    if(s32LogRet != HI_SUCCESS)               \
                    { \
                        SVR_LOG_ERROR("%s fail:%d(0x%x)" , #func, s32LogRet, s32LogRet);    \
                        return ;                        \
                    }                                   \
                }while(0)

/*-----------------------------------------------------------------*/

#define SVR_LOG_DOFUNC_GOTO(func, errhandle) \
    do{\
        HI_S32 s32LogRet = func;\
        if (s32LogRet != HI_SUCCESS )\
        {\
            SVR_LOG_ERROR("%s fail:%d(0x%x)", #func, s32LogRet, s32LogRet);    \
            goto errhandle;\
        }\
    }while(0)

#define HI_LOG_DOFUNC_GOTO(func, errhandle) \
            do{\
                HI_S32 s32LogRet = func;\
                if (s32LogRet != HI_SUCCESS )\
                {\
                    SVR_LOG_ERROR("%s fail:%d(0x%x)", #func, s32LogRet, s32LogRet);    \
                    goto errhandle;\
                }\
            }while(0)

#ifdef __cplusplus
#if __cplusplus
 }
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_TIME_H__ */
