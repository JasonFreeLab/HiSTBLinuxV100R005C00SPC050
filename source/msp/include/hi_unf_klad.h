/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   : Key ladder basic API declaration
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_KLAD_H__
#define __HI_UNF_KLAD_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      KLAD */
/** @{ */  /** <!-- [KLAD] */

#define HI_UNF_KLAD_MAX_KEY_LEN     (16)

/*
Level: 1
Algorithm: TDES/AES
Target Engine: Multicipher - fixed; encrypted register - NA
*/
#define HI_UNF_KLAD_TYPE_BLPK       (0x0000)

/*
Level: 1
Algorithm: TDES
Target Engine: Multicipher - fixed; encrypted register - NA
*/
#define HI_UNF_KLAD_TYPE_SWPK       (0x0001)

/*
Level: 0
Algorithm: NA
Target Engine: Multicipher - fixed
*/
#define HI_UNF_KLAD_TYPE_STBROOTKEY (0x0002)

/*
Level: 0
Algorithm: NA
Target Engine: Demux - CSA2/CSA3/AES/DES/NOVEL/SM4/TDES; Payload cipher - AES; Multicipher - fixed
*/
#define HI_UNF_KLAD_TYPE_CLEARCW    (0x0003)


/**Target engine of key ladder*/
typedef enum
{
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA2             = 0x0000,   /**<Demux PAYLOAD CSA2 */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA3             = 0x0010,   /**<Demux PAYLOAD CSA3 */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC_IDSA     = 0x0020,   /**<Demux PAYLOAD AES  IPTV Mode */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_ECB          = 0x0021,   /**<Demux PAYLOAD AES  ECB Mode */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC_CI       = 0x0022,   /**<Demux PAYLOAD AES  CIPLUS */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_ECB = 0x0024,   /**<Demux PAYLOAD AES  CLRSTART ECB */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_CBC = 0x0025,   /**<Demux PAYLOAD AES  CLRSTART CBC */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CTR          = 0x0026,   /**<Demux PAYLOAD AES  CTR */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_DES_IPTV         = 0x0030,   /**<Demux PAYLOAD DES  CIPLUS */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_DES_CIPLUS       = 0x0032,   /**<Demux PAYLOAD DES  CIPLUS */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_DES_CBC          = 0x0033,   /**<Demux PAYLOAD DES  CBC */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_NOVEL        = 0x0040,   /**<Demux PAYLOAD AES  NOVEL */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_SMS4_NOVEL       = 0x0041,   /**<Demux PAYLOAD SMS4 NOVEL */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_SMS4_IPTV        = 0x0050,   /**<Demux PAYLOAD SMS4 IPTV */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_SMS4_ECB         = 0x0051,   /**<Demux PAYLOAD SMS4 ECB */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_SMS4_CBC         = 0x0053,   /**<Demux PAYLOAD SMS4 CBC */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC          = 0x0063,   /**<Demux PAYLOAD AES  CBC */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_TDES_IPTV        = 0x0070,   /**<Demux PAYLOAD TDES IPTV */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_TDES_ECB         = 0x0071,   /**<Demux PAYLOAD TDES ECB */
    HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_TDES_CBC         = 0x0073,   /**<Demux PAYLOAD TDES CBC */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_AES_CBC              = 0x4020,   /**<Cipher AES CBC */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_AES_ECB              = 0x4021,   /**<Cipher AES ECB */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_AES_CBC_PIFF         = 0x4022,   /**<Cipher AES CBC PIFF */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_AES_CBC_APPLE        = 0x4023,   /**<Cipher AES CBC APPLE */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_AES_CTR              = 0x4024,   /**<Cipher AES CTR */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_TDES_CBC             = 0x4040,   /**<Cipher AES CBC */
    HI_UNF_KLAD_TARGET_ENGINE_RAW_TDES_ECB             = 0x4041,   /**<Cipher AES ECB */
    HI_UNF_KLAD_TARGET_ENGINE_FIXED,                               /**<Can't config by software */
    HI_UNF_KLAD_TARGET_ENGINE_BUTT
} HI_UNF_KLAD_TARGET_ENGINE_E;

/**Encryption algorithm of key ladder*/
typedef enum
{
    HI_UNF_KLAD_ALG_TYPE_TDES = 0,      /**<Encryption algorithm : TDES*/
    HI_UNF_KLAD_ALG_TYPE_AES,           /**<Encryption algorithm : AES*/
    HI_UNF_KLAD_ALG_TYPE_BUTT
} HI_UNF_KLAD_ALG_TYPE_E;

/**Level of key ladder*/
typedef enum
{
    HI_UNF_KLAD_LEVEL1 = 0,
    HI_UNF_KLAD_LEVEL2,
    HI_UNF_KLAD_LEVEL3,
    HI_UNF_KLAD_LEVEL4,
    HI_UNF_KLAD_LEVEL5,
    HI_UNF_KLAD_LEVEL6,
    HI_UNF_KLAD_LEVEL_BUTT
} HI_UNF_KLAD_LEVEL_E;

/**Session key*/
typedef struct
{
    HI_UNF_KLAD_LEVEL_E enLevel;
    HI_U8 au8Key[HI_UNF_KLAD_MAX_KEY_LEN];
} HI_UNF_KLAD_SESSION_KEY_S;

/**Content key*/
typedef struct
{
    HI_BOOL bOdd;
    HI_U8 au8Key[HI_UNF_KLAD_MAX_KEY_LEN];
} HI_UNF_KLAD_CONTENT_KEY_S;


typedef struct
{
    HI_BOOL bOdd;
    HI_U32 u32IVLength;
    HI_U8 au8IV[HI_UNF_KLAD_MAX_KEY_LEN];
} HI_UNF_KLAD_CONTENT_IV_S;

typedef struct
{
    HI_U8 au8ClearKey[HI_UNF_KLAD_MAX_KEY_LEN];
    HI_U8 au8EncKey[HI_UNF_KLAD_MAX_KEY_LEN];
} HI_UNF_KLAD_ENC_KEY_S;

/**Attributes of key ladder*/
typedef struct
{
    HI_U32 u32KladType;
    HI_UNF_KLAD_ALG_TYPE_E enAlg;
    HI_UNF_KLAD_TARGET_ENGINE_E enEngine;
} HI_UNF_KLAD_ATTR_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      KLAD */
/** @{ */  /** <!--[KLAD]*/

/**
\brief Init the key ladder device
\param  None
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_Init(HI_VOID);

/**
\brief Deinit the key ladder device
\param  None
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_DeInit(HI_VOID);

/**
\brief Create a handle of key ladder
\param[in] u32Type  key ladder type, ref: HI_UNF_KLAD_TYPE_
\param[out] phKlad  Handle of key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_Create(HI_HANDLE* phKlad);

/**
\brief Destroy key ladder handle
\param[in] hKlad    Handle of key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_Destroy(HI_HANDLE hKlad);

/**
\brief Attach key ladder to the taget, include mcipher, plcipher, demux
\param[in] hKlad    Handle of key ladder
\param[in] hTarget  Handle of target
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_Attach(HI_HANDLE hKlad, HI_HANDLE hTarget);

/**
\brief Detach a key ladder from a target
\param[in] hKlad    Handle of key ladder
\param[in] hTarget  Handle of target
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_Detach(HI_HANDLE hKlad, HI_HANDLE hTarget);

/**
\brief Set the attributes of a key ladder
\param[in] hKlad    Handle of key ladder
\param[in] pstAttr  Pointer to the attributes of a key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_SetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr);

/**
\brief Get the attributes of a key ladder
\param[in] hKlad    Handle of key ladder
\param[out] pstAttr Pointer to the attributes of a key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_GetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr);

/**
\brief Set session key of a keyladder
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   Pointer to the session key
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_SetSessionKey(HI_HANDLE hKlad, HI_UNF_KLAD_SESSION_KEY_S* pstKey);

/**
\brief Set content key of a keyladder
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   Pointer to the content key
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_SetContentKey(HI_HANDLE hKlad, HI_UNF_KLAD_CONTENT_KEY_S* pstKey);

/**
\brief Set content iv of a keyladder
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   Pointer to the content iv
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_SetContentIV(HI_HANDLE hKlad, HI_UNF_KLAD_CONTENT_IV_S* pstIV);

/**
\brief Generate an encrypted key
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   Pointer to the encrypted key
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_GenerateEncKey(HI_HANDLE hKlad, HI_UNF_KLAD_ENC_KEY_S* pstKey);

/**
\brief Send STB rootkey to cipher
\param[in] hKlad    Handle of key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_UNF_KLAD_SendSTBRootkeyToCipher(HI_HANDLE hKlad);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_KLAD_H__ */

