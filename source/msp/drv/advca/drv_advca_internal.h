/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_advca_internal.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :

******************************************************************************/
#ifndef __DRV_ADVCA_INTERNAL_H__
#define __DRV_ADVCA_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "drv_ca_otp_v200.h"
#include "drv_ca_otp_reg_v200.h"
#include "drv_ca_otp.h"
#include "drv_ca_otp_common.h"
#include "drv_advca_common.h"
#include "drv_advca_v300_reg.h"
#include "hal_advca_v300.h"


typedef struct
{
    CA_CMD_CHILD_ID_E enCmd;
    HI_S32 (*pfnIoctlChild)(CA_CMD_SUPPER_ID_S *pstCmdParam);
}DRV_ADVCA_IOCTL_CHILD_FUNC_MAP_S;

typedef struct
{
    HI_U32 u32Cmd;
    HI_S32 (*pfnIoctl)(HI_VOID *pvArg);
}DRV_ADVCA_IOCTL_FUNC_MAP_S;

typedef struct
{
    HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse;
    HI_S32 (*pfnOtpFuse)(HI_UNF_ADVCA_OTP_ATTR_S *pstOtpAttr);
}DRV_ADVCA_OTP_FUSE_FUNC_MAP_S;


#ifdef __cplusplus
}
#endif
#endif /* __DRV_ADVCA_INTERNAL_H__ */
