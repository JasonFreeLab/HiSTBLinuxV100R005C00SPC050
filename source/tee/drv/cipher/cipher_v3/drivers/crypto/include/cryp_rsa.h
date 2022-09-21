/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_tee_cipher.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __CRYP_RSA_H_
#define __CRYP_RSA_H_

#include "drv_osal_lib.h"
#include "drv_srsa.h"

/******************************* API Declaration *****************************/
/** \addtogroup      rsa */
/** @{ */  /** <!--[rsa]*/

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/


/**
* \brief          Initialize crypto of rsa *
*/
s32 cryp_rsa_init(void);

/**
* \brief          Deinitialize crypto of rsa *
*/
void cryp_rsa_deinit(void);

/**
\brief RSA encryption a plaintext with a RSA key.
\param[in] key:         rsa key.
\param[in] scheme:      rsa encrypt scheme.
\param[in] in£º         input data to be encryption
\param[in] in£º         input data to be encryption
\param[out] inlen:      length of input data to be encryption
\param[out] out£º       output data to be encryption
\param[out] outlen:     length of output data to be encryption
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 cryp_rsa_encrypt(cryp_rsa_key *key, CRYP_CIPHER_RSA_ENC_SCHEME_E scheme,
                        u8 *in, u32 inlen,
                        u8 *out, u32 *outlen);

/**
\brief RSA decryption a plaintext with a RSA key.
\param[in] key:         rsa key.
\param[in] scheme:      rsa encrypt scheme.
\param[in] in£º         input data to be encryption
\param[in] in£º         input data to be encryption
\param[out] inlen:      length of input data to be encryption
\param[out] out£º       output data to be encryption
\param[out] outlen:     length of output data to be encryption
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 cryp_rsa_decrypt(cryp_rsa_key *key, CRYP_CIPHER_RSA_ENC_SCHEME_E scheme,
                        u8 *in, u32 inlen,
                        u8 *out, u32 *outlen);

/**
\brief RSA sign a hash value with a RSA private key.
\param[in] key:         rsa key.
\param[in] scheme:      rsa sign scheme.
\param[in] in£º         input data to be encryption
\param[in] in£º         input data to be encryption
\param[out] inlen:      length of input data to be encryption
\param[out] out£º       output data to be encryption
\param[out] outlen:     length of output data to be encryption
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 cryp_rsa_sign_hash(cryp_rsa_key *key, CRYP_CIPHER_RSA_SIGN_SCHEME_E scheme,
                        u8 *in, u32 inlen, u8 *out, u32 *outlen, u32 saltlen);

/**
\brief RSA verify a hash value with a RSA public key.
\param[in] key:         rsa key.
\param[in] scheme:      rsa sign scheme.
\param[in] in£º         input data to be encryption
\param[in] in£º         input data to be encryption
\param[out] inlen:      length of input data to be encryption
\param[out] out£º       output data to be encryption
\param[out] outlen:     length of output data to be encryption
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 cryp_rsa_verify_hash(cryp_rsa_key *key, CRYP_CIPHER_RSA_SIGN_SCHEME_E scheme,
                        u8 *in, u32 inlen, u8 *sign, u32 signlen, u32 saltlen);

/**
\brief Generate a RSA private key.
\param[in] numbits:     bit numbers of the integer public modulus.
\param[in] exponent£º   value of public exponent
\param[out] key:        rsa key.
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 cryp_rsa_gen_key(u32 numbits, u32 exponent, cryp_rsa_key *key);

/**
\brief Generate random.
N/A
*/
int mbedtls_get_random(void *param, u8 *rand, size_t size);

/** @} */  /** <!-- ==== API declaration end ==== */
#endif
