/******************************************************************************
Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name   :  hi_unf_payloadcipher.h
Author        :  Hisilicon multimedia software group
Created      :  2016/10/21
Description :
******************************************************************************/
#ifndef __HI_UNF_PAYLOADCIPHER_H__
#define __HI_UNF_PAYLOADCIPHER_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      PayloadCipher */
/** @{ */  /** <!-- [PayloadCipher] */

/** Max pidFilter Num */
/**CNcomment:最大PID过滤数*/
#define HI_UNF_PLCIPHER_PIDFILTER_NUM 16

/** PLCipher algorithm */
/** CNcomment:PLCipher加密算法*/
typedef enum
{
    HI_UNF_PLCIPHER_ALG_AES_IPTV            = 0x20,  /**<AES IPTV*/
    HI_UNF_PLCIPHER_ALG_AES_ECB             = 0x21,  /**<AES ECB*/
    HI_UNF_PLCIPHER_ALG_AES_CBC             = 0x22,  /**<AES CBC*/
    HI_UNF_PLCIPHER_ALG_BUTT                = 0x84
}HI_UNF_PLCIPHER_ALG_E;

/** PLCipher Key Type */
/** CNcomment:PLCipher Key 类型*/
typedef enum
{
    HI_UNF_PLCIPHER_KEY_EVEN       = 0,   /**< Even key type */ /**< CNcomment:偶KEY类型*/
    HI_UNF_PLCIPHER_KEY_ODD        = 1,   /**< Odd key type */ /**< CNcomment:奇KEY类型*/
    HI_UNF_PLCIPHER_KEY_BUTT,
}HI_UNF_PLCIPHER_KEY_EVENODD_E;

/** Structure of the plcipher control information */
/** CNcomment:加密控制信息结构 */
typedef struct
{
    HI_UNF_PLCIPHER_ALG_E enAlg;                   /**< Algorithm  type*/ /**< CNcomment:算法类型*/
    HI_BOOL bPIDFilterEn;                          /**< Pid filter switch, default disable, plcipher will encrypt all pids in the ts when the switch is setted with HI_FALSE, and plcipher will just encrypt the assigned pids when the switch is setted with HI_TRUE*/
                                                   /**< CNcomment:Pid 过滤使用开关，默认关闭，关闭时plcipher将对TS包的所有PID进行加密，而当开启时plcipher仅对指定的PID数据进行加密*/
    HI_U32  u32PidNum;                             /**< valid when bPIDFilterEn is HI_TRUE, the pid number need to be filted.*/ /**< CNcomment:仅当bPIDFilterEn为HI_TRUE时有效，要过滤的PID个数*/
    HI_U16  u16PID[HI_UNF_PLCIPHER_PIDFILTER_NUM]; /**< valid when bPIDFilterEn is HI_TRUE, the pid arrays need to be filted.*/ /**< CNcomment:仅当bPIDFilterEn为HI_TRUE时有效，要过滤的PID数组*/
} HI_UNF_PLCIPHER_ATTR_S;

/** @} */  /** <!-- ==== Structure Definition End ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      PayloadCipher */
/** @{ */  /** <!--[PayloadCipher]*/

/**
\brief Initializes the PLCIPHER module.CNcomment:初始化PLCIPHER模块。CNend
\attention \n
Before using PLCIPHERs, you must call this application programming interface (API).\n
Before using the ts level encryption function, you need to initialize the PLCIPHER module.\n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:在进行PLCIPHER相关操作前应该首先调用本接口\n
在使用TS级加密功能前请提前进行PLCIPHER模块的初始化\n
重复调用本接口返回成功。CNend
\param  N/A.CNcomment:无。CNend
\retval ::HI_SUCCESS Success. CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\see \n
N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_Init(HI_VOID);

/**
\brief Deinitializes the PLCIPHER module. CNcomment:去初始化PLCIPHER模块。CNend
\attention \n
After this API is called, the PLCIPHER module is stopped, and the PLCIPHER resources used by the process are released.\n
This API is valid when it is called for the first time. If this API is called repeatedly, the error code HI_SUCCESS is returned.
CNcomment:调用本接口停止使用PLCIPHER模块，并释放本进程所占用的PLCIPHER资源\n
本接口第一次调用起作用，重复调用返回成功。CNend
\param  N/A.CNcomment:无。CNend
\retval ::HI_SUCCESS Success CNcomment:成功。CNend
\retval ::HI_FAILURE Calling this API fails. CNcomment:API系统调用失败。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_DeInit(HI_VOID);

/**
\brief Creates a PLCIPHER channel for encryption.CNcomment:创建一路PLCIPHER通道。CNend
\param[out] phPLCipher     Pointer to the handle of a PLCIPHER.CNcomment:指针类型，输出申请到的PLCIPHER Handle。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_PLCIPHER_FAILED_GETHANDLE There is no more PLCIPHER channel left. CNcomment:没有空闲的PLCIPHER通道。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_Create(HI_HANDLE *phPLCipher);

/**
\brief Destroys an existing PLCIPHER channel.CNcomment:销毁一路PLCIPHER通道。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel to be destroyed.CNcomment:待销毁的PLCIPHER 通道句柄。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_Destroy(HI_HANDLE hPLCipher);

/**
\brief Gets the attributes of a PLCIPHER channel.CNcomment:获取一路PLCIPHER通道的属性。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER 通道句柄。CNend
\param[out] pstAttr  Pointer to the attributes of a PLCIPHER channel.CNcomment:PLCIPHER通道属性指针。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S *pstAttr);

/**
\brief Sets the attributes of a PLCIPHER channel.CNcomment:设置一路PLCIPHER通道的属性。CNend
\attention \n
plcipher will encrypt all pids in the ts when bPIDFilterEn is setted with HI_FALSE,\n
and plcipher will just encrypt the assigned pids when bPIDFilterEn is setted with HI_TRUE.
CNcomment:bPIDFilterEn 为HI_FALSE时plcipher将对TS包的所有PID进行加密，而当bPIDFilterEn 为HI_TRUE时plcipher仅对指定的PID数据进行加密。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER 通道句柄。CNend
\param[in] pstAttr  Pointer to the attributes of a PLCIPHER channel.CNcomment:PLCIPHER通道属性指针。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:输入属性结构成员非法。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S *pstAttr);

/**
\brief Sets the CW keys of a PLCIPHER channel. This API is used to configure the PLCIPHER channel.CNcomment:配置PLCIPHER通道的密钥，本接口用于配置PLCIPHER通道的密钥。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER 通道句柄。CNend
\param[in] enKeyEvenOdd  Type of CW key odd or even.CNcomment:待设置密钥的奇偶类型。CNend
\param[in] pu8Key  Pointer to odd or even CW key buffer to be set, always a 8 or 16 bytes array.CNcomment:指针类型，指向要设置的奇或偶密钥数据，一般8或16个字节的数组。CNend
\param[in] u32KeyLen  The length of CW key data to be set, always 8 or 16.CNcomment:要设置的密钥数据的长度，一般8或16。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:输入属性结构成员非法。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, const HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
\brief Sets the IV vector of a PLCIPHER channel. This API is used to configure the PLCIPHER channel.CNcomment:配置PLCIPHER通道的IV向量，本接口用于配置PLCIPHER通道的IV向量。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER 通道句柄。CNend
\param[in] enIVEvenOdd  Type of IV vector odd or even.CNcomment:待设置IV向量的奇偶类型。CNend
\param[in] pu8IV  Pointer to odd or even IV vector buffer to be set, always a 8 or 16 bytes array.CNcomment:指针类型，指向要设置的奇或偶IV向量，一般8或16个字节的数组。CNend
\param[in] u32IVLen  The length of IV vector to be set, always 8 or 16.CNcomment:要设置的IV向量数据的长度，一般8或16。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:输入属性结构成员非法。CNend
\see \n
 N/A.CNcomment:无。CNend
*/

HI_S32 HI_UNF_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enIVEvenOdd, const HI_U8 *pu8IV, HI_U32 u32IVLen);

/**
\brief Encrypt TS package data in a PLCIPHER channel.CNcomment:使用PLCIPHER通道对TS包数据进行TS级加密。CNend
\attention \n
PLCIPHER support pSrcBuf and pDestBuf are the same address, in other word, PLCIPHER support encryption at the same adress.
CNcomment:PLCIPHER支持pSrcBuf和pDestBuf的值相同，换句话说PLCIPHER支持就地加密。CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER 通道句柄。CNend
\param[in] pSrcBuf  The physical address of TS package data to be encrypted.CNcomment:VOID指针类型，待加密TS包数据的起始物理地址。CNend
\param[in] pDestBuf  The physical address of the encryted TS package data.CNcomment:VOID指针类型，加密完成后TS包数据数据的物理地址。CNend
\param[in] u32Length  The length of TS package data to be encrypted.CNcomment:待加密TS包数据的长度。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:输入PLCIPHER句柄非法。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:输入属性结构成员非法。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_UNF_PLCIPHER_Encrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_PAYLOADCIPHER_H__ */
