/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_drv_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __HI_DRV_OTP_H__
#define __HI_DRV_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OTP_CUSTOMER_KEY_LEN    16
#define OTP_HDCP_ROOT_KEY_LEN   16
#define OTP_STB_ROOT_KEY_LEN    16

#define OTP_ROOTKEY_LEN         16

#define HI_FATAL_OTP(fmt...)    HI_FATAL_PRINT(HI_ID_OTP, fmt)
#define HI_ERR_OTP(fmt...)      HI_ERR_PRINT(HI_ID_OTP, fmt)
#define HI_WARN_OTP(fmt...)     HI_WARN_PRINT(HI_ID_OTP, fmt)
#define HI_INFO_OTP(fmt...)     HI_INFO_PRINT(HI_ID_OTP, fmt)
#define HI_DBG_OTP(fmt...)     HI_DBG_PRINT(HI_ID_OTP, fmt)

#define OTP_FIELD_VALUE_MAX_LEN 1024
#define OTP_PV_MAGIC_LEN 32
#define OTP_FIELD_NAME_MAX_LEN 32

typedef struct
{
    HI_CHAR field_name[OTP_FIELD_NAME_MAX_LEN];
    HI_U32 value_len;
    HI_U8 value[OTP_FIELD_VALUE_MAX_LEN];
    HI_BOOL lock;
}OTP_BURN_PV_ITEM_S;

typedef struct
{
    HI_CHAR magic[OTP_PV_MAGIC_LEN];    /* "Hisilicon PV description file" */
    HI_U32 version;                     /* 0x01000000: 1.0.0.0 */
    HI_U32 number;                      /* Item number need to be burnt */
    HI_U32 reserve[6];
}OTP_BURN_PV_HEADER_S;


HI_S32 HI_DRV_OTP_Resume(HI_VOID);
HI_S32 HI_DRV_OTP_Suspend(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif

