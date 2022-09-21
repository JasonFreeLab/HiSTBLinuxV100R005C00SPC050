/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_drv_otp.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_DRV_OTP_H__
#define __HI_TEE_DRV_OTP_H__
#define HI_LOG_D_MODULE_ID     HI_MODULE_ID_OTP
#define HI_LOG_D_FUNCTRACE     (1)
#define HI_LOG_D_UNFTRACE      (1)
#include "hi_type.h"
#include "hi_tee_debug.h"
#include "hi_tee_otp.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define OTP_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            HI_LOG_PrintErrCode(HI_ERR_OTP_NULL_PTR); \
            return HI_ERR_OTP_NULL_PTR; \
        } \
    } while (0)

#define OTP_CHECK_ADDR(addr) \
    do {  \
        if (addr < 0 || addr >= 0xC00)\
        {\
            HI_LOG_PrintErrCode(HI_ERR_OTP_INVALID_ADDR); \
            return HI_ERR_OTP_INVALID_ADDR; \
        } \
    } while (0)

#define OTP_CHECK_KEYLEN(len) \
    do {  \
        if (len != HI_TEE_OTP_ROOTKEY_LENGTH)\
        {\
            HI_LOG_PrintErrCode(HI_ERR_OTP_INVALID_KEYLEN); \
            return HI_ERR_OTP_INVALID_KEYLEN; \
        } \
    } while (0)

#define OTP_CHECK_CHIPIDLEN(len) \
    do {  \
        if (len != HI_TEE_OTP_CHIPID_LENGTH)\
        {\
            HI_LOG_PrintErrCode(HI_ERR_OTP_INVALID_CHIPIDLEN); \
            return HI_ERR_OTP_INVALID_CHIPIDLEN; \
        } \
    } while (0)

#define OTP_CHECK_PARAM(val) \
    do { \
        if (val) \
        { \
            HI_LOG_PrintErrCode(HI_ERR_OTP_INVALID_PARAM); \
            return HI_ERR_OTP_INVALID_PARAM; \
        }\
    } while (0)


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HI_TEE_DRV_OTP*/
