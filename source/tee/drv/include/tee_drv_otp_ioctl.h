/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __TEE_DRV_OTP_IOCTL_H__
#define __TEE_DRV_OTP_IOCTL_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    HI_U32 addr;
    HI_U8 value;
}OTP_ENTRY_S;

#define TEE_IOC_NA        0U
#define TEE_IOC_W         1U
#define TEE_IOC_R         2U
#define TEE_IOC_RW        3U

#define TEE_OTP_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

/* This is just magic number */
#define IOC_TYPE_OTP    0x51

#define CMD_OTP_READ_BYTE   TEE_OTP_IOC(TEE_IOC_RW, IOC_TYPE_OTP, 0x1, sizeof(OTP_ENTRY_S))
#define CMD_OTP_WRITE_BYTE  TEE_OTP_IOC(TEE_IOC_W, IOC_TYPE_OTP, 0x2, sizeof(OTP_ENTRY_S))
#define CMD_OTP_RESET       TEE_OTP_IOC(TEE_IOC_NA, IOC_TYPE_OTP, 0x3, 0)


#ifdef __cplusplus
}
#endif
#endif /* __TEE_DRV_OTP_IOCTL_H__ */

