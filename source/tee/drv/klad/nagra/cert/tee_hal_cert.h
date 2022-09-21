/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : tee_hal_cert.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-04-01
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __TEE_HAL_CERT_H__
#define __TEE_HAL_CERT_H__

#include "hi_tee_drv_cert.h"
#include "tee_drv_cert_reg.h"
#include "tee_drv_cert_ioctl.h"
#include "hi_tee_errcode.h"

#ifdef __cplusplus
extern "C" {
#endif

HI_VOID HAL_CERT_ReadReg(HI_ULONG addr, HI_U32* value);
HI_VOID HAL_CERT_WriteReg(HI_ULONG addr, HI_U32 value);
CERT_AKL_STATUS_U HAL_CERT_GetAklStatus(HI_VOID);
HI_VOID HAL_CERT_SetAklCommand(HI_U32 cmd);
HI_U32 HAL_CERT_GetAklCommand(HI_VOID);
HI_U32 HAL_CERT_GetAklKeySendDbg(HI_VOID);
HI_U32 HAL_CERT_GetAklKeySendNone(HI_VOID);
HI_VOID HAL_CERT_SetAklLockReg(HI_U32 reg);
HI_U32 HAL_CERT_GetAklLockReg(HI_VOID);
HI_U32 HAL_CERT_GetAklLockState(HI_VOID);
HI_U32 HAL_CERT_SetAklKeySendCtl(CERT_AKL_SEND_CTL_U reg);
CERT_AKL_SEND_CTL_U HAL_CERT_GetAklKeySendCtl(HI_VOID);
HI_VOID HAL_CERT_GetAklDataIn(CERT_DATA_S* data_in);
HI_VOID HAL_CERT_SetAklDataIn(CERT_DATA_S* data_in);
HI_VOID HAL_CERT_GetAklDataOut(CERT_DATA_S* data_out);
HI_VOID HAL_CERT_Reset(HI_VOID);
HI_U32 HAL_CERT_SetAklKeySendDone(CERT_KEY_CTL_E flag);
HI_U32 HAL_CERT_CheckAklKeyStatus(HI_VOID);
HI_VOID HAL_CERT_SetAklSecEn(HI_BOOL sec_en);
HI_U32 HAL_CERT_GetAklSecState(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __TEE_HAL_CERT_H__ */


