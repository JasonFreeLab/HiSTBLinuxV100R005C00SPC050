/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_hal_otp.h
* Description:  Define otp hal interface.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20170317    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_HAL_OTP_H__
#define __TEE_HAL_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_U8 HAL_OTP_ReadByte(HI_U32 addr);

HI_S32 HAL_OTP_WriteByte(HI_U32 addr, HI_U8 value);

HI_S32 HAL_OTP_Reset(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_HAL_OTP_H__ */