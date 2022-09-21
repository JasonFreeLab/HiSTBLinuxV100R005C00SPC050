/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_otp_common_ca.h
  Version       : Initial Draft
  Author        : Hisilicon otp software group
  Created       : 2017/1/14
  Description   :
*******************************************************************************/
#ifndef __HI_UNF_OTP_COMMON_CA_H__
#define __HI_UNF_OTP_COMMON_CA_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP_COMMON_CA */
/** @{ */  /** <!-- [OTP_COMMON_CA] */

/** advanced CA session serect key class*/
typedef enum
{
    HI_UNF_OTP_COMMON_CA_KLAD_LEV1 = 0,   /**<session serect key level 1*/
    HI_UNF_OTP_COMMON_CA_KLAD_LEV2,       /**<session serect key level 2*/
    HI_UNF_OTP_COMMON_CA_KLAD_LEV3,       /**<session serect key level 3*/
    HI_UNF_OTP_COMMON_CA_KLAD_LEV4,       /**<session serect key level 4*/
    HI_UNF_OTP_COMMON_CA_KLAD_LEV5,       /**<session serect key level 5*/
    HI_UNF_OTP_COMMON_CA_KLAD_LEV_BUTT
} HI_UNF_OTP_COMMON_CA_KLAD_LEV_E;


/** advanced CA session serect key class*/
typedef enum
{
    HI_UNF_OTP_COMMON_CA_KLAD_TARGET_DEMUX_CIPHER = 0,
    HI_UNF_OTP_COMMON_CA_KLAD_TARGET_DEMUX,
    HI_UNF_OTP_COMMON_CA_KLAD_TARGET_CIPHER,
    HI_UNF_OTP_COMMON_CA_KLAD_TARGET_NULL,
    HI_UNF_OTP_COMMON_CA_KLAD_TARGET_BUTT
} HI_UNF_OTP_COMMON_CA_KLAD_TARGET_E;


typedef enum
{
    HI_UNF_OTP_COMMON_CA_KLAD_CSA2 = 0,
    HI_UNF_OTP_COMMON_CA_KLAD_CSA3,
    HI_UNF_OTP_COMMON_CA_KLAD_SP,
    HI_UNF_OTP_COMMON_CA_KLAD_MISC,
    HI_UNF_OTP_COMMON_CA_KLAD_R2R,
    HI_UNF_OTP_COMMON_CA_KLAD_BUTT
} HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E;

/** Rootkey type*/
typedef enum
{
    HI_UNF_OTP_COMMON_CA_CSA2 = 0,
    HI_UNF_OTP_COMMON_CA_CSA3,
    HI_UNF_OTP_COMMON_CA_SP,
    HI_UNF_OTP_COMMON_CA_MISC,
    HI_UNF_OTP_COMMON_CA_R2R,
    HI_UNF_OTP_COMMON_CA_BOOT,
    HI_UNF_OTP_COMMON_CA_BUTT
} HI_UNF_OTP_COMMON_CA_ROOTKEY_E;


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      OTP_COMMON_CA */
/** @{ */  /** <!-- [OTP_COMMON_CA] */


/**
\brief Set the chipID. CNcomment:设置芯片ID CNend
\attention \n
\param[in] pu8ChipID point to chip id. CNcomment:指针类型，芯片ID CNend
\param[in] u32Len The length of ChipID, current is 8. CNcomment:芯片ID长度，8 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:重复设置 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_COMMON_CA_SetChipID(HI_U8 *pu8ChipID, HI_U32 u32Len);


/**
\brief Get the chipID. CNcomment:获取芯片ID CNend
\attention \n
\param[out] pu8ChipID point to chip id. CNcomment:指针类型，芯片ID CNend
\param[in/out] pu32Len Point to the length of ChipID, current output length is 8. CNcomment:指针类型，芯片ID长度，当前输出8 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:重复设置 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_COMMON_CA_GetChipID(HI_U8 *pu8ChipID, HI_U32 *pu32Len);


/**
\brief Set klad level. CNcomment:设置keylad级数 CNend
\attention \n
N/A
\param[in] enType: klad type.   CNcomment:Klad类型 CNend
\param[in] enLevel: klad level. CNcomment:Klad级数 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_SetKladLevel(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_LEV_E enLevel);


/**
\brief Get klad level. CNcomment:设置keylad级数 CNend
\attention \n
N/A
\param[in] enType: klad type.       CNcomment:Klad类型 CNend
\param[out] penLevel: klad level.   CNcomment:指针类型，Klad级数 CNend
\retval ::HI_SUCCESS  Success.      CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.      CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_GetKladLevel(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_LEV_E *penLevel);


/**
\brief Set klad target. CNcomment:设置keylad目标 CNend
\attention \n
N/A
\param[in] enType: klad type.           CNcomment:Klad类型 CNend
\param[in] enTarget: target type.       CNcomment:目标类型 CNend
\retval ::HI_SUCCESS  Success.          CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.          CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_SetKladTarget(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_TARGET_E enTarget);


/**
\brief Get klad target control. CNcomment:获取keylad目标 CNend
\attention \n
N/A
\param[in] enType: klad type.           CNcomment:Klad类型 CNend
\param[out] penTarget: target type.     CNcomment:指针类型，目标类型 CNend
\retval ::HI_SUCCESS  Success.          CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.          CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_GetKladTarget(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_TARGET_E *penTarget);

/**
\brief Disable keyladder. CNcomment:禁用keyladder CNend
\attention \n
N/A
\param[in] enType: klad type.               CNcomment:Klad类型 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_DisableKlad(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType);

/**
\brief Get klad disable status. CNcomment:获取klad使能状态 CNend
\attention \n
N/A
\param[in] enType: klad type.               CNcomment:Klad类型 CNend
\param[out] pbEnable:  Klad enable status.  CNcomment:指针类型，Klad使能状态 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_GetKladStat(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_BOOL *pbEnable);


/**
\brief Set root key to otp. CNcomment:向芯片内部设置根密钥 CNend
\attention \n
N/A
\param[in] enType: Type of keyladder rootkey.       CNcomment:根密钥类型 CNend
\param[in] pu8Key: Point to root key value.         CNcomment:指针类型，根密钥 CNend
\param[in] u32KeyLen: The length of root key.       CNcomment:根密钥长度 CNend
\retval ::HI_SUCCESS Success                                            CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called                        CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized  CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid   CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_SetRootKey(HI_UNF_OTP_COMMON_CA_ROOTKEY_E enType, HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
\brief Set JTAG key to otp. CNcomment:向芯片内部设置JTAG密钥 CNend
\attention \n
N/A
\param[in] pu8Key: Point to JTAG key value.         CNcomment:指针类型，JTAG密钥 CNend
\param[in] u32KeyLen: The length of JRAG key.       CNcomment:JTAG密钥长度 CNend
\retval ::HI_SUCCESS Success                                            CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called                        CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized  CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid   CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_COMMON_CA_SetJTAGKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_OTP_COMMON_CA_H__ */
