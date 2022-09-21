/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_keyladder.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KEYLADDER_H__
#define __HI_TEE_KEYLADDER_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      KLAD */
/** @{ */  /** <!-- [KLAD] */

#define HI_TEE_KLAD_MAX_KEY_LEN     (16)


#define HI_TEE_KLAD_TYPE_BLPK       (0x0000)
#define HI_TEE_KLAD_TYPE_SWPK       (0x0001)
#define HI_TEE_KLAD_TYPE_STBROOTKEY (0x0002)
#define HI_TEE_KLAD_TYPE_CLEARCW    (0x0003)
#define HI_TEE_KLAD_TYPE_WIDEVINE   (0x0004)
#define HI_TEE_KLAD_TYPE_RKP        (0x0005)
#define HI_TEE_KLAD_TYPE_SOS        (0x0006)
#define HI_TEE_KLAD_TYPE_AUX        (0x0007)
#define HI_TEE_KLAD_TYPE_CATA       (0x0008)
#define HI_TEE_KLAD_TYPE_HISITA     (0x0009)
#define HI_TEE_KLAD_TYPE_STBTA      (0x000a)
#define HI_TEE_KLAD_TYPE_SECSTORGE  (0x000b)

/**Target crypto engine of key ladder*/
typedef enum hiTEE_KLAD_TARGET_CRYPTO_ENGINE_E
{
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_CSA2              = 0x0000,   /**<Demux PAYLOAD CSA2 */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_CSA3              = 0x0010,   /**<Demux PAYLOAD CSA3 */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_AES_CBC_IDSA      = 0x0020,   /**<Demux PAYLOAD AES  IPTV Mode */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_AES_ECB           = 0x0021,   /**<Demux PAYLOAD AES  ECB Mode */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_AES_CBC_CI        = 0x0022,   /**<Demux PAYLOAD AES  CIPLUS */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_DES_IPTV          = 0x0030,   /**<Demux PAYLOAD DES  CIPLUS */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_DES_CIPLUS        = 0x0032,   /**<Demux PAYLOAD DES  CIPLUS */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_DES_CBC           = 0x0033,   /**<Demux PAYLOAD DES  CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_AES_NOVEL         = 0x0040,   /**<Demux PAYLOAD AES  NOVEL */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_SMS4_NOVEL        = 0x0041,   /**<Demux PAYLOAD SMS4 NOVEL */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_SMS4_IPTV         = 0x0050,   /**<Demux PAYLOAD SMS4 IPTV */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_SMS4_ECB          = 0x0051,   /**<Demux PAYLOAD SMS4 ECB */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_SMS4_CBC          = 0x0053,   /**<Demux PAYLOAD SMS4 CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_AES_CBC           = 0x0063,   /**<Demux PAYLOAD AES  CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_TDES_IPTV         = 0x0070,   /**<Demux PAYLOAD TDES IPTV */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_TDES_ECB          = 0x0071,   /**<Demux PAYLOAD TDES ECB */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_TDES_CBC          = 0x0073,   /**<Demux PAYLOAD TDES CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_AES_CBC               = 0x4020,   /**<MultiCipher AES CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_AES_ECB               = 0x4021,   /**<MultiCipher AES ECB */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_AES_CBC_PIFF          = 0x4022,   /**<MultiCipher AES CBC PIFF */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_AES_CBC_APPLE         = 0x4023,   /**<MultiCipher AES CBC APPLE */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_AES_CTR               = 0x4024,   /**<MultiCipher AES CTR */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_TDES_CBC              = 0x4040,   /**<MultiCipher AES CBC */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_RAW_TDES_ECB              = 0x4041,   /**<MultiCipher AES ECB */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_FIXED,                                /**<Can't config by software */
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_BUTT
} HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_E;

typedef enum hiTEE_KLAD_SEC_E
{
    HI_TEE_KLAD_SEC_ENABLE = 0,
    HI_TEE_KLAD_SEC_DISABLE,
    HI_TEE_KLAD_SEC_BUTT
} HI_TEE_KLAD_SEC_E;

/**Encryption algorithm of key ladder*/
typedef enum hiTEE_KLAD_ALG_TYPE_E
{
    HI_TEE_KLAD_ALG_TYPE_TDES      = 0,    /**<Encryption algorithm : TDES*/
    HI_TEE_KLAD_ALG_TYPE_AES,              /**<Encryption algorithm : AES*/
    HI_TEE_KLAD_ALG_TYPE_SM4,              /**<Encryption algorithm : SM4*/
    HI_TEE_KLAD_ALG_TYPE_BUTT
} HI_TEE_KLAD_ALG_TYPE_E;

/**Level of key ladder*/
typedef enum hiTEE_KLAD_LEVEL_E
{
    HI_TEE_KLAD_LEVEL1 = 0,
    HI_TEE_KLAD_LEVEL2,
    HI_TEE_KLAD_LEVEL3,
    HI_TEE_KLAD_LEVEL4,
    HI_TEE_KLAD_LEVEL5,
    HI_TEE_KLAD_LEVEL6,
    HI_TEE_KLAD_LEVEL_BUTT
} HI_TEE_KLAD_LEVEL_E;

/**Session key*/
typedef struct hiTEE_KLAD_SESSION_KEY_S
{
    HI_TEE_KLAD_LEVEL_E enLevel;
    HI_U8 au8Key[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_SESSION_KEY_S;

/**Content key*/
typedef struct hiTEE_KLAD_CONTENT_KEY_S
{
    HI_BOOL bOdd;
    HI_U8 au8Key[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_CONTENT_KEY_S;

typedef struct hiTEE_KLAD_CONTENT_IV_S
{
    HI_BOOL bOdd;
    HI_U32 u32IVLength;
    HI_U8 au8IV[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_CONTENT_IV_S;

/**Encrypted key*/
typedef struct hiTEE_KLAD_ENC_KEY_S
{
    HI_U8 au8ClearKey[HI_TEE_KLAD_MAX_KEY_LEN];
    HI_U8 au8EncKey[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_ENC_KEY_S;

/**Attributes of key ladder*/
typedef struct hiTEE_KLAD_ATTR_S
{
    HI_U32 u32KladType;
    HI_TEE_KLAD_SEC_E enSecType;
    HI_TEE_KLAD_ALG_TYPE_E enAlg;
    HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_E enEngine;
} HI_TEE_KLAD_ATTR_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      KLAD */
/** @{ */  /** <!--[KLAD]*/


/**
\brief Init the key ladder device
\param  None
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_Init(HI_VOID);

/**
\brief Deinit the key ladder device
\param  None
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_DeInit(HI_VOID);

/**
\brief Create a handle of key ladder
\param[in] u32Type   key ladder type, ref: HI_UNF_KLAD_TYPE_
\param[out] phKlad   Handle of key ladder
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_Create(HI_HANDLE *phKlad);

/**
\brief Destroy key ladder handle
\param[in] hKlad   Handle of key ladder
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_Destroy(const HI_HANDLE hKlad);

/**
\brief Attach key ladder to the taget, include mcipher, plcipher, demux
\param[in] hKlad   Handle of key ladder
\param[in] hTarget   Handle of target
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_Attach(const HI_HANDLE hKlad, const HI_HANDLE hTarget);

/**
\brief Detach a key ladder from a target
\param[in] hKlad   Handle of key ladder
\param[in] hTarget   Handle of target
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_Detach(const HI_HANDLE hKlad, const HI_HANDLE hTarget);

/**
\brief Set the attributes of a key ladder
\param[in] hKlad   Handle of key ladder
\param[in] pstAttr   Pointer to the attributes of a key ladder
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_SetAttr(const HI_HANDLE hKlad, const HI_TEE_KLAD_ATTR_S* pstAttr);

/**
\brief Get the attributes of a key ladder
\param[in] hKlad   Handle of key ladder
\param[out] pstAttr   Pointer to the attributes of a key ladder
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_GetAttr(const HI_HANDLE hKlad, HI_TEE_KLAD_ATTR_S *pstAttr);

/**
\brief Set session key of a keyladder
\param[in] hKlad   Handle of key ladder
\param[in] pstKey   Pointer to the session key
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_SetSessionKey(const HI_HANDLE hKlad, const HI_TEE_KLAD_SESSION_KEY_S* pstKey);

/**
\brief Set content key of a keyladder
\param[in] hKlad   Handle of key ladder
\param[in] pstKey   Pointer to the content key
\retval HI_SUCCESS    Success
\retval HI_FAILURE      Failure
*/
HI_S32 HI_TEE_KLAD_SetContentKey(const HI_HANDLE hKlad, const HI_TEE_KLAD_CONTENT_KEY_S* pstKey);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KEYLADDER_H__ */

