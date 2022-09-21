/******************************************************************************
Copyright (C), 2015-2025, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     : hi_define.h
Version       : Initial draft
Author        : HiSilicon
Created Date  : 2015-08-24
Last Modified by:
Description   : Application programming interfaces (APIs) of Time module.
Function List :
Change History:
******************************************************************************/

#ifndef __HI_DEFINE_H__
#define __HI_DEFINE_H__

#include "hi_type.h"
#include "utils/Logger.h"
#include "hi_ref_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

// check param is valid
#define COMMON_CHK_PARA(val)                            \
do {                                                    \
    if ((val))                                          \
    {                                                   \
        HI_LOGE("para invalid");                        \
        return HI_EINVAL;                               \
    };                                                  \
} while (0)

#define COMMON_CHK_PRINT_ERR(val, ret)                  \
do {                                                    \
    if ((val))                                          \
    {                                                   \
        HI_LOGE("%d ",ret);                             \
    }                                                   \
} while (0)

#define COMMON_CHK_RETURN_ERR(val, ret )                \
do {                                                    \
    if ((val))                                          \
    {                                                   \
        HI_LOGE("value invalid");                       \
        return ret;                                     \
    }                                                   \
} while (0)

#define COMMON_DOFUNC( func )                           \
do {                                                    \
    HI_S32 ret = 0;                                     \
    ret = func;                                         \
    if (ret != HI_SUCCESS)                              \
    {                                                   \
        HI_LOGE("CALL %s, ret = %d", # func, ret);      \
    };                                                  \
} while (0)

#define COMMON_DOFUNC_RETURN( func )                    \
do {                                                    \
    HI_S32 ret = 0;                                     \
    ret = func;                                         \
    if (ret != HI_SUCCESS)                              \
    {                                                   \
        HI_LOGE("CALL %s, ret is %d ", # func, ret);    \
        return ret;                                     \
    };                                                  \
} while (0)

#define COMMON_DOFUNC_RETURN_ERR( func, err)            \
do {                                                    \
    HI_S32 ret = 0;                                     \
    ret = func;                                         \
    if (ret != HI_SUCCESS)                              \
    {                                                   \
        HI_LOGE("CALL %s , ret id %d ", # func , ret);  \
        return err;                                     \
    };                                                  \
} while (0)

#ifdef __cplusplus
#if __cplusplus
             }
#endif
#endif  /* End of #ifdef __cplusplus */

#endif  /* #define __HI_DEFINE_H__ */
