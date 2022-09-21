/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : otp_debug.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __OTP_DEBUG_H__
#define __OTP_DEBUG_H__

#include "hi_common.h"
#include "hi_type.h"

#define HI_FATAL_OTP(fmt...)    HI_FATAL_PRINT(HI_ID_OTP, fmt)
#define HI_ERR_OTP(fmt...)      HI_ERR_PRINT(HI_ID_OTP, fmt)
#define HI_WARN_OTP(fmt...)     HI_WARN_PRINT(HI_ID_OTP, fmt)
#define HI_INFO_OTP(fmt...)     HI_INFO_PRINT(HI_ID_OTP, fmt)
#define HI_DBG_OTP(fmt...)      HI_DBG_PRINT(HI_ID_OTP, fmt)

#define OTP_CHECK_PARAM(val)                            \
{                                                       \
    if (val)                                            \
    {                                                   \
        HI_ERR_OTP("param is invalid\n");               \
        return HI_FAILURE;                 \
    }                                                   \
}

#endif /* __OTP_DEBUG_H__ */
