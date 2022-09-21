/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_otp.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <string.h>
#include "hi_debug.h"
#include "hi_unf_otp.h"
#include "hi_error_mpi.h"
#include "drv_otp_ioctl.h"
#ifdef OTP_VERSION_V100
    #include "hi_mpi_otp_v100.h"
#else
    #include "hi_mpi_otp_v200.h"
#endif

HI_S32 HI_UNF_OTP_Init(HI_VOID)
{
    return HI_MPI_OTP_Init();
}

HI_S32 HI_UNF_OTP_DeInit(HI_VOID)
{
    return HI_MPI_OTP_DeInit();
}

HI_S32 HI_UNF_OTP_SetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    return HI_MPI_OTP_SetCustomerKey(pKey, u32KeyLen);
}

HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    return HI_MPI_OTP_GetCustomerKey(pKey, u32KeyLen);
}

HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data)
{
    return HI_MPI_OTP_SetStbPrivData(u32Offset, u8Data);
}

HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data)
{
    return HI_MPI_OTP_GetStbPrivData(u32Offset, pu8Data);
}

HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID)
{
    return HI_MPI_OTP_BurnToNormalChipset();
}

HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID)
{
    return HI_MPI_OTP_BurnToSecureChipset();
}

HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_GetIDWordLockFlag(pbLockFlag);
#else
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_WriteHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_WriteHdcpRootKey(pu8HdcpRootKey, u32Keylen);
#else
    return HI_MPI_OTP_SetRootKey(HI_UNF_OTP_HDCP_ROOTKEY, pu8HdcpRootKey, u32Keylen);
#endif
}

HI_S32 HI_UNF_OTP_ReadHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen)
{
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
}

HI_S32 HI_UNF_OTP_LockHdcpRootKey(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_LockHdcpRootKey();
#else
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_GetHdcpRootKeyLockFlag(HI_BOOL *pbLockFlag)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_GetHdcpRootKeyLockFlag(pbLockFlag);
#else
    return HI_MPI_OTP_GetRootKeyLockStat(HI_UNF_OTP_HDCP_ROOTKEY, pbLockFlag);
#endif
}

HI_S32 HI_UNF_OTP_WriteStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_WriteStbRootKey(pu8StbRootKey, u32Keylen);
#else
    return HI_MPI_OTP_SetRootKey(HI_UNF_OTP_STB_ROOTKEY, pu8StbRootKey, u32Keylen);
#endif
}

HI_S32 HI_UNF_OTP_ReadStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen)
{
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
}

HI_S32 HI_UNF_OTP_LockStbRootKey(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_LockStbRootKey();
#else
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_GetStbRootKeyLockFlag(HI_BOOL *pbLockFlag)
{
#ifdef OTP_VERSION_V100
    return HI_MPI_OTP_GetStbRootKeyLockFlag(pbLockFlag);
#else
    return HI_MPI_OTP_GetRootKeyLockStat(HI_UNF_OTP_STB_ROOTKEY, pbLockFlag);
#endif
}

HI_S32 HI_UNF_OTP_GetVendorID(HI_UNF_OTP_VENDORID_E *penVendorID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetVendorID(penVendorID);
#endif
}

HI_S32 HI_UNF_OTP_GetStbSN(HI_U8 *pu8StbSN, HI_U32 *pu32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetStbSN(pu8StbSN, pu32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetStbSN(HI_U8 *pu8StbSN, HI_U32 u32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetStbSN(pu8StbSN, u32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetBootMode(enFlashType);
#endif
}

HI_S32 HI_UNF_OTP_DisableSelfBoot(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_DisableSelfBoot();
#endif
}

HI_S32 HI_UNF_OTP_GetSelfBootStat(HI_BOOL *pbDisable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetSelfBootStat(pbDisable);
#endif
}

HI_S32 HI_UNF_OTP_EnableBootDecrypt(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_EnableBootDecrypt();
#endif
}

HI_S32 HI_UNF_OTP_GetBootDecryptStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetBootDecryptStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_EnableSCS(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_EnableSCS();
#endif
}

HI_S32 HI_UNF_OTP_GetSCSStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetSCSStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_EnableTrustZone(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_EnableTrustZone();
#endif
}

HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetTrustZoneStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_GetMSID(HI_U8 *pu8MSID, HI_U32 *pu32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetMSID(pu8MSID, pu32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetMSID(HI_U8 *pu8MSID, HI_U32 u32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetMSID(pu8MSID, u32Len);
#endif
}

HI_S32 HI_UNF_OTP_GetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 *pu32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetSOSMSID(pu8SOSMSID, pu32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 u32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetSOSMSID(pu8SOSMSID, u32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetLongData( pFuseName, u32Offset, pu8Value, u32Length);
#endif
}

HI_S32 HI_UNF_OTP_GetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetLongData(pFuseName, u32Offset, pu8Value, u32Length);
#endif
}

HI_S32 HI_UNF_OTP_SetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetLongDataLock( pFuseName, u32Offset, u32Length);
#endif
}

HI_S32 HI_UNF_OTP_GetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length, HI_U32 * pu32Lock)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetLongDataLock( pFuseName, u32Offset, u32Length, pu32Lock);
#endif
}

HI_S32 HI_UNF_OTP_DisableDDRWakeup(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_DisableDDRWakeup();
#endif
}

HI_S32 HI_UNF_OTP_GetDDRWakeupStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetDDRWakeupStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_LockGlobalOTP(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_LockGlobalOTP();
#endif
}

HI_S32 HI_UNF_OTP_GetGlobalOTPLockStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetGlobalOTPLockStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_EnableRuntimeCheck(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_EnableRuntimeCheck();
#endif
}

HI_S32 HI_UNF_OTP_GetRuntimeCheckStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetRuntimeCheckStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_DisableDDRWakeupCheck(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_DisableDDRWakeupCheck();
#endif
}

HI_S32 HI_UNF_OTP_GetDDRWakeupCheckStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetDDRWakeupCheckStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_EnableDDRScramble(HI_VOID)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_EnableDDRScramble();
#endif
}

HI_S32 HI_UNF_OTP_GetDDRScrambleStat(HI_BOOL *pbEnable)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetDDRScrambleStat(pbEnable);
#endif
}

HI_S32 HI_UNF_OTP_GetJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetJtagMode(penJtagMode);
#endif
}

HI_S32 HI_UNF_OTP_SetJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetJtagMode(enJtagMode);
#endif
}

HI_S32 HI_UNF_OTP_GetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetTEEJtagMode(penJtagMode);
#endif
}

HI_S32 HI_UNF_OTP_SetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetTEEJtagMode(enJtagMode);
#endif
}

HI_S32 HI_UNF_OTP_GetBootVersionID(HI_U8 *pu8VersionID, HI_U32 *pu32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetBootVersionID(pu8VersionID, pu32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetBootVersionID(HI_U8 *pu8VersionID, HI_U32 u32Len)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetBootVersionID(pu8VersionID, u32Len);
#endif
}

HI_S32 HI_UNF_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_U8 *pu8Rootkey, HI_U32 u32Len)
{
    return HI_MPI_OTP_SetRootKey(enRootkeyType, pu8Rootkey, u32Len);
}

HI_S32 HI_UNF_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_BOOL *pbLock)
{
    return HI_MPI_OTP_GetRootKeyLockStat(enRootkeyType, pbLock);
}

HI_S32 HI_UNF_OTP_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_BurnProductPV(pstPV, u32Num);
#endif
}

HI_S32 HI_UNF_OTP_VerifyProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_VerifyProductPV(pstPV, u32Num);
#endif
}

HI_S32 HI_UNF_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_SetRSAKey(pu8Key, u32KeyLen);
#endif
}

HI_S32 HI_UNF_OTP_GetRSALockStat(HI_BOOL *pbLock)
{
#ifdef OTP_VERSION_V100
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#else
    return HI_MPI_OTP_GetRSALockStat(pbLock);
#endif
}
