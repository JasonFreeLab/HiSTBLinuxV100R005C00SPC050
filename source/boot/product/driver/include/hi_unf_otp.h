/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_otp.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_OTP_H__
#define __HI_UNF_OTP_H__

HI_S32 HI_UNF_OTP_Init(HI_VOID);

HI_S32 HI_UNF_OTP_DeInit(HI_VOID);

HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);

HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);

HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);

HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);

HI_S32 HI_UNF_OTP_LockIDWord(HI_VOID);

HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID);

HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID);

HI_U32 HI_UNF_OTP_Read(HI_U32 addr);

HI_U8  HI_UNF_OTP_ReadByte(HI_U32 addr);

HI_S32 HI_UNF_OTP_WriteByte(HI_U32 addr, HI_U8 u8data);

HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable);

#endif

