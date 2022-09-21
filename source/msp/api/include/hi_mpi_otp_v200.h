/******************************************************************************
 Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : mpi_otp.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HI_MPI_OTP_V200_H__
#define __HI_MPI_OTP_V200_H__
#include <pthread.h>
#include "hi_type.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
extern HI_S32 g_otp_dev_fd;
extern HI_S32 g_otp_open_cnt;
extern pthread_mutex_t g_otp_mutex;

#define HI_OTP_LOCK()    (HI_VOID)pthread_mutex_lock(&g_otp_mutex);
#define HI_OTP_UNLOCK()  (HI_VOID)pthread_mutex_unlock(&g_otp_mutex);

#define CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        HI_ERR_OTP("point is null\n");\
        return HI_ERR_OTP_PTR_NULL;\
    }\
}while(0)

#define CHECK_OTP_PARAM(val) \
do{\
    if(val) \
    {\
        HI_ERR_OTP("otp param is invalid\n");\
        return HI_ERR_OTP_INVALID_PARA;\
    }\
}while(0)


#define CHECK_OTP_INIT()\
do{\
    HI_OTP_LOCK();\
    if (g_otp_dev_fd < 0)\
    {\
        HI_ERR_OTP("OTP is not init.\n");\
        HI_OTP_UNLOCK();\
        return HI_ERR_OTP_NOT_INIT;\
    }\
    HI_OTP_UNLOCK();\
}while(0)


HI_S32 HI_MPI_OTP_Init(HI_VOID);
HI_S32 HI_MPI_OTP_DeInit(HI_VOID);
HI_S32 HI_MPI_OTP_SetCustomerKey(HI_U8 *key, HI_U32 key_len);
HI_S32 HI_MPI_OTP_GetCustomerKey(HI_U8 *key, HI_U32 key_len);
HI_S32 HI_MPI_OTP_SetStbPrivData(HI_U32 offset, HI_U8 data);
HI_S32 HI_MPI_OTP_GetStbPrivData(HI_U32 offset, HI_U8 *data);
HI_S32 HI_MPI_OTP_BurnToNormalChipset(HI_VOID);
HI_S32 HI_MPI_OTP_BurnToSecureChipset(HI_VOID);
HI_S32 HI_MPI_OTP_GetVendorID(HI_UNF_OTP_VENDORID_E *vender_id);
HI_S32 HI_MPI_OTP_GetStbSN(HI_U8 *stb_sn, HI_U32 *len);
HI_S32 HI_MPI_OTP_SetStbSN(HI_U8 *stb_sn, HI_U32 len);
HI_S32 HI_MPI_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E flash_type);
HI_S32 HI_MPI_OTP_DisableSelfBoot(HI_VOID);
HI_S32 HI_MPI_OTP_GetSelfBootStat(HI_BOOL *disable);
HI_S32 HI_MPI_OTP_EnableBootDecrypt(HI_VOID);
HI_S32 HI_MPI_OTP_GetBootDecryptStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_EnableSCS(HI_VOID);
HI_S32 HI_MPI_OTP_GetSCSStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_EnableTrustZone(HI_VOID);
HI_S32 HI_MPI_OTP_GetTrustZoneStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_GetMSID(HI_U8 *msid, HI_U32 *plen);
HI_S32 HI_MPI_OTP_SetMSID(HI_U8 *msid, HI_U32 len);
HI_S32 HI_MPI_OTP_GetSOSMSID(HI_U8 *sos_msid, HI_U32 *plen);
HI_S32 HI_MPI_OTP_SetSOSMSID(HI_U8 *sos_msid, HI_U32 len);
HI_S32 HI_MPI_OTP_SetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);
HI_S32 HI_MPI_OTP_GetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);
HI_S32 HI_MPI_OTP_SetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length);
HI_S32 HI_MPI_OTP_GetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length, HI_U32 * pu32Lock);
HI_S32 HI_MPI_OTP_DisableDDRWakeup(HI_VOID);
HI_S32 HI_MPI_OTP_GetDDRWakeupStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_LockGlobalOTP(HI_VOID);
HI_S32 HI_MPI_OTP_GetGlobalOTPLockStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_EnableRuntimeCheck(HI_VOID);
HI_S32 HI_MPI_OTP_GetRuntimeCheckStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_DisableDDRWakeupCheck(HI_VOID);
HI_S32 HI_MPI_OTP_GetDDRWakeupCheckStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_EnableDDRScramble(HI_VOID);
HI_S32 HI_MPI_OTP_GetDDRScrambleStat(HI_BOOL *enable);
HI_S32 HI_MPI_OTP_GetJtagMode(HI_UNF_OTP_JTAG_MODE_E *jtag_mode);
HI_S32 HI_MPI_OTP_SetJtagMode(HI_UNF_OTP_JTAG_MODE_E jtag_mode);
HI_S32 HI_MPI_OTP_GetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E *jtag_mode);
HI_S32 HI_MPI_OTP_SetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E jtag_mode);
HI_S32 HI_MPI_OTP_GetBootVersionID(HI_U8 *version_id, HI_U32 *plen);
HI_S32 HI_MPI_OTP_SetBootVersionID(HI_U8 *version_id, HI_U32 len);
HI_S32 HI_MPI_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E type, HI_U8 *key, HI_U32 len);
HI_S32 HI_MPI_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E type, HI_BOOL *pbLock);
HI_S32 HI_MPI_OTP_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv, HI_U32 u32Num);
HI_S32 HI_MPI_OTP_VerifyProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv, HI_U32 u32Num);
HI_S32 HI_MPI_OTP_SetOtpFuse(HI_CHAR *field_name, HI_U32 name_len, HI_U8 *value, HI_U32 value_len);
HI_S32 HI_MPI_OTP_GetOtpFuse(HI_CHAR *field_name, HI_U32 name_len, HI_U8 *value, HI_U32 value_len);
HI_S32 HI_MPI_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_GetRSALockStat(HI_BOOL *pbLock);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MPI_OTP_V200_H__ */

