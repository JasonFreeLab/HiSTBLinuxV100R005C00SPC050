/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_otp.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_OTP_H__
#define __TEE_DRV_OTP_H__

#include "hi_type.h"

HI_VOID OTP_SetReset(HI_VOID);
HI_S32 OTP_GetChipID(HI_U8 *pChipID, HI_U32 u32Len);
HI_S32 OTP_ReadByte(HI_U32 Addr, HI_U8 *pu8Value);
HI_S32 OTP_WriteByte(HI_U32 Addr, HI_U8 u8Value);
HI_S32 OTP_SecureOSVersionGet(HI_U32 *pu32VersionNum);
HI_S32 OTP_SecureOSVersionSet(HI_U32 u32Version);
#endif  /* __TEE_DRV_OTP_H__ */

