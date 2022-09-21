/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_otp_nagra.h
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

#ifndef __HI_TEE_OTP_NAGRA_H__
#define __HI_TEE_OTP_NAGRA_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP_NAGRA */
/** @{ */  /** <!-- [OTP_NAGRA] */

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      OTP_NAGRA */
/** @{ */  /** <!-- [OTP_NAGRA] */

/**
\brief Get the nuid of the STB. CNcomment:获取NUID CNend
\attention \n
None CNcomment:无 CNend
\param[out] pu8Nuid NUID. CNcomment:指针类型，NUID CNend
\param[in/out] pu32Len point to the length of NUID, current is 4. CNcomment:指针类型，NUID长度，当前是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_TEE_ERR_UNINITED The advanced OTP module is not initialized CNcomment:HI_TEE_ERR_UNINITED  OTP未初始化 CNend
\retval ::HI_TEE_ERR_INVALID_PARAM The input parameter value is invalid CNcomment:HI_TEE_ERR_INVALID_PARAM  输入参数非法 CNend
\see \n
::HI_UNF_OTP_NAGRA_GetNUID
*/
HI_S32 HI_TEE_OTP_NAGRA_GetNUID(HI_U8 *pu8Nuid, HI_U32 *pu32Len);


/**
\brief enable nagra privileged mode. CNcomment:使能nagra 特权模式 CNend
\attention \n
N/A
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_TEE_ERR_UNINITED The advanced OTP module is not initialized CNcomment:HI_TEE_ERR_UNINITED  OTP未初始化 CNend
\retval ::HI_TEE_ERR_INVALID_PARAM The input parameter value is invalid CNcomment:HI_TEE_ERR_INVALID_PARAM  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_NAGRA_EnablePrivilegedMode(HI_VOID);

/**
\brief get nagra privileged mode. CNcomment:获取nagra 权模式 CNend
\attention \n
N/A
\param[out]  pbPVMode Point to the privileged mode . Ncomment: 指针类型，获取特权模式CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_TEE_ERR_UNINITED The advanced OTP module is not initialized CNcomment:HI_TEE_ERR_UNINITED  OTP未初始化 CNend
\retval ::HI_TEE_ERR_INVALID_PARAM The input parameter value is invalid CNcomment:HI_TEE_ERR_INVALID_PARAM  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_TEE_OTP_NAGRA_GetPrivilegedMode(HI_BOOL *pbPVMode);


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif

