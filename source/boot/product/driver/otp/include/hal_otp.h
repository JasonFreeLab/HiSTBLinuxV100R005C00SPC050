/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __HAL_OTP_H__
#define __HAL_OTP_H__

#include "hi_common.h"
#include "hi_type.h"

#define HI_FATAL_OTP(fmt...)    HI_FATAL_PRINT(HI_ID_OTP, fmt)
#define HI_ERR_OTP(fmt...)      HI_ERR_PRINT(HI_ID_OTP, fmt)
#define HI_WARN_OTP(fmt...)     HI_WARN_PRINT(HI_ID_OTP, fmt)
#define HI_INFO_OTP(fmt...)     HI_INFO_PRINT(HI_ID_OTP, fmt)
#define HI_DBG_OTP(fmt...)      HI_DBG_PRINT(HI_ID_OTP, fmt)

#define msleep(ms) udelay(ms * 1000)

#define OTP_CHECK_PARAM(val)                            \
{                                                       \
    if (val)                                            \
    {                                                   \
        HI_ERR_OTP("param is invalid\n");               \
        return HI_FAILURE;                 \
    }                                                   \
}

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *tdata);
HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *tdata);
HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value);
HI_S32 HAL_OTP_Write(HI_U32 addr,HI_U32 tdata);
HI_S32 HAL_OTP_WriteByte(HI_U32 addr,HI_U8 tdata);
HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32  bit_value);
HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value);

#endif /* __HAL_OTP_H__ */
