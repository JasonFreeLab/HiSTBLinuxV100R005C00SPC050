/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2013-12-28
  Description   :
  History       :
  1.Date        : 2016/06/23
    Author      : sdk
    Modification: format file

*******************************************************************************/
/**
 * \file
 * \brief Describes the API about the otp.
          CNcomment:提供otp API CNend
 */

#ifndef __HI_TEE_OTP_H__
#define __HI_TEE_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/** @} */  /** <!-- ==== Structure Definition end ==== */
typedef enum
{
    OTP_TA_INDEX_1 = 0,
    OTP_TA_INDEX_2,
    OTP_TA_INDEX_3,
    OTP_TA_INDEX_4,
    OTP_TA_INDEX_5,
    OTP_TA_INDEX_6
} OTP_TA_INDEX_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

#define HI_TEE_OTP_ROOTKEY_LENGTH       (0x10)
#define HI_TEE_OTP_CHIPID_LENGTH        (0x08)

/******************************* API declaration *****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/**
\brief Init an otp device.
\brief CNcomment:初始化OTP设备。 CNend
\attention \n
N/A
\param N/A                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_Init(HI_VOID);

/**
\brief Deinit an otp device.
\brief CNcomment:去初始化OTP设备。 CNend
\attention \n
N/A
\param N/A                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_DeInit(HI_VOID);

/**
\brief reset the otp device.
\brief CNcomment:复位OTP设备。 CNend
\attention \n
N/A
\param N/A                                          CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_Reset(HI_VOID);

/**
\brief Get the device chip ID.
\brief CNcomment:获取设备芯片标识。 CNend
\attention \n
N/A
\param[out] pKey:  Buffer to store the chip ID.     CNcomment:存储获取芯片标识的缓冲区指针。 CNend
\param[in] u32ChipIDLength:  Buffer length.         CNcomment:缓冲区长度。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetChipID(HI_U8 *pu8ChipID, const HI_U32 u32ChipIDLength);

/**
\brief Read otp value by word.
\brief CNcomment按字读取OTP的值。 CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                           CNcomment:OTP 地址。 CNend
\param[out] pu32Value:  Buffer to store the otp by word.    CNcomment:存储按字获取OTP值的缓冲区指针。 CNend
\retval ::HI_SUCCESS  Call this API successful.             CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                  CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_ReadWord(const HI_U32 u32Addr, HI_U32 *pu32Value);

/**
\brief Read otp value by byte.
\brief CNcomment按字节读取OTP的值。 CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                           CNcomment:OTP 地址。 CNend
\param[out] pu32Value:  Buffer to store the otp by word.    CNcomment:存储按字节获取OTP值的缓冲区指针。 CNend
\retval ::HI_SUCCESS  Call this API successful.             CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                  CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_ReadByte(const HI_U32 u32Addr, HI_U8 *pu8Value);


/**
\brief Write otp value by byte.
\brief CNcomment按字节写OTP的值。 CNend
\attention \n
N/A
\param[in] u32Addr:  OTP address.                       CNcomment:OTP 地址。 CNend
\param[in] u32Value:   value to be write.                 CNcomment:待写入OTP的值。 CNend
\retval ::HI_SUCCESS  Call this API successful.         CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.              CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_WriteByte(const HI_U32 u32Addr, const HI_U8 u8Value);

/**
\brief Set secure store root key.
\brief CNcomment:设置安全存储密钥。 CNend
\attention \n
N/A
\param[in] pu8Key: Buffer to store secure store rookey.     CNcomment:存储安全存储密钥的指针。 CNend
\param[out] u32Length:  Secure store rootkey length.        CNcomment:安全存储密钥的长度。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_SetSecStoreKey(const HI_U8 *pu8Key, const HI_U32 u32Length);

/**
\brief Get secure store rootkey lock flag.
\brief CNcomment:获取安全存储密钥锁状态。 CNend
\attention \n
N/A
\param[out] pbFlag:  Point to the secure store rootkey lock status.     CNcomment:获取安全存储锁状态指针。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetSecStoreKeyLockFlag(HI_U8 *pbFlag);


/**
\brief Get the device ca chip ID.
\brief CNcomment:获取高安芯片ID。 CNend
\attention \n
N/A
\param[out] pKey:  Buffer to store the CA chip ID.     CNcomment:存储获取芯片标识的缓冲区指针。 CNend
\param[in]  u32ChipIDLength:  The length of the buffer.   CNcomment:存储高安ChipID的缓冲区长度。 CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetCAChipID(HI_U8 *pu8CAChipID, const HI_U32 u32CAChipIDLen);

/**
\brief Set antirollback version
\brief CNcomment 设置防回滚版本号。 CNend
\attention \n
N/A
\param[in] u32Addr:    OTP address.                       CNcomment:OTP 地址。 CNend
\param[in] u32Length:  The length of otp.                 CNcomment:防回滚版本号OTP长度。 CNend
\param[in] u32Version:  The version of otp.               CNcomment:设置的version。 CNend
\retval ::HI_SUCCESS  Call this API successful.         CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.              CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_SetAntiRollBackVersion(const HI_U32 u32OTPAddr, const HI_U32 u32Length, const HI_U32 u32Version);

/**
\brief Get antirollback version
\brief CNcomment 获取防回滚版本号。 CNend
\attention \n
N/A
\param[in] u32Addr:    OTP address.                       CNcomment:OTP 地址。 CNend
\param[in] u32Length:  The length of otp.                 CNcomment:防回滚版本号OTP长度。 CNend
\param[out] pu32Version: antirollback version.            CNcomment:防回滚版本号。 CNend
\retval ::HI_SUCCESS  Call this API successful.         CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.              CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetAntiRollBackVersion(const HI_U32 u32OTPAddr, const HI_U32 u32Length, HI_U32 *pu32Version);



/**
\brief Set ta certificate version
\brief CNcomment 设置TA证书版本号。 CNend
\attention \n
N/A
\param[in] enIndex:     TA index.                   CNcomment:TA 索引 CNend
\param[in] u32Version:  version.                    CNcomment:版本号  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_SetTACertificateVersion(const OTP_TA_INDEX_E enIndex, const HI_U32 u32Version);

/**
\brief Get ta certificate version
\brief CNcomment 获取TA证书版本号。 CNend
\attention \n
N/A
\param[in] enIndex:  TA index.                      CNcomment:TA 索引 CNend
\param[out] pu32Version:  the point of version.     CNcomment:获取版本号指针  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetTACertificateVersion(const OTP_TA_INDEX_E enIndex, HI_U32 *pu32Version);

/**
\brief Set ta secure version
\brief CNcomment 设置TA版本号。 CNend
\attention \n
N/A
\param[in] enIndex:     TA index.                   CNcomment:TA 索引 CNend
\param[in] u32Version:  version.                    CNcomment:版本号  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_SetTASecureVersion(const OTP_TA_INDEX_E enIndex, const HI_U32 version);

/**
\brief Get ta secure version
\brief CNcomment 获取TA版本号。 CNend
\attention \n
N/A
\param[in] enIndex:     TA index.                   CNcomment:TA 索引 CNend
\param[out] pu32Version:  the point of version.     CNcomment:获取版本号指针  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetTASecureVersion(const OTP_TA_INDEX_E enIndex, HI_U32 *pu32Version);


/**
\brief Get ta segmentid
\brief CNcomment 获取TA区域码。 CNend
\attention \n
N/A
\param[in] enIndex:     TA index.                   CNcomment:TA 索引 CNend
\param[out] pu32TAID:  the point of TA id.          CNcomment:获取TA ID号指针  CNend
\param[out] pu32SMID:  the point of TA segment id.  CNcomment:获取TA区域码指针  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetTAIDAndSegmentID(const OTP_TA_INDEX_E enIndex, HI_U32 *pu32TAID, HI_U32 *pu32SMID);

/**
\brief Get ta index
\brief CNcomment 根据TA ID号获取索引值。 CNend
\attention \n
N/A
\param[in] u32TAID:     TA ID.                      CNcomment:TA ID号 CNend
\param[out] enIndex:    the point of TA index.      CNcomment:获取TA索引的指针  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetTAIndex(const HI_U32 u32TAID, OTP_TA_INDEX_E *enIndex);

/**
\brief Get ta index
\brief CNcomment 获取可用的索引值。 CNend
\attention \n
N/A
\param[out] enIndex:    the point of available TA index.      CNcomment:获取可用TA索引的指针  CNend
\retval ::HI_SUCCESS  Call this API successful.     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_GetAvailableTAIndex(OTP_TA_INDEX_E *enIndex);
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif

