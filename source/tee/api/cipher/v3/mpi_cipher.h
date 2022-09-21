/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : mpi_cipher.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __MPI_CIPHER_H__
#define __MPI_CIPHER_H__

#include "user_osal_lib.h"

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */

/******************************* API Declaration *****************************/
/** \addtogroup      mpi */
/** @{ */  /** <!--[mpi]*/

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      crypto*/
/** @{*/  /** <!-- [link]*/

/**
\brief   mpi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_symc_init(void);

/**
\brief   Kapi Deinit.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_symc_deinit(void);

/**
\brief   Create symc handle.
\param[in]  id The channel number.
\param[in]  uuid The user identification.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_symc_create(u32 *id);

/**
\brief   Destroy symc handle.
\param[in]  id The channel number.
\param[in]  uuid The user identification.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_symc_destroy(u32 id);

/**
\brief  set work params.
* \param[in]  id The channel number.
* \param[in]  hard_key whether use the hard key or not.
* \param[in]  alg The symmetric cipher algorithm.
* \param[in]  mode The symmetric cipher mode.
* \param[in]  sm1_round_num The round number of sm1.
* \param[in]  fkey first  key buffer, defualt
* \param[in]  skey second key buffer, expand
* \param[in]  klen The key length.
* \param[in]  aad      Associated Data
* \param[in]  alen     Associated Data Length
* \param[in]  tlen     Tag length
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_symc_config(u32 id,
                    u32 hard_key,
                    CRYP_CIPHER_ALG_E enAlg,
                    CRYP_CIPHER_WORK_MODE_E enWorkMode,
                    CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                    CRYP_CIPHER_KEY_LENGTH_E enKeyLen,
                    CRYP_CIPHER_SM1_ROUND_E sm1_round_num,
                    u8 *fkey, u8 *skey,
                    u8 *iv, u32 ivlen, u32 iv_usage,
                    compat_addr aad, u32 alen, u32 tlen);


/**
 * \brief          SYMC  buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param length   length of the input data
 * \param decrypt  decrypt or encrypt
 *
 * \return         0 if successful
 */
s32 mpi_symc_crypto(u32 id, compat_addr input,
                      compat_addr output, u32 length,
                      u32 operation);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param pkg       Buffer of package infomation
 * \param pkg_num   Number of package infomation
 * \param decrypt  decrypt or encrypt
 *
 * \return         0 if successful
 */
s32 mpi_symc_crypto_multi(u32 id, void *pkg,
                           u32 pkg_num, u32 operation);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param pkg       Buffer of package infomation
 * \param pkg_num   Number of package infomation
 * \param decrypt  decrypt or encrypt
 *
 * \return         0 if successful
 */
s32 mpi_symc_crypto_multi_asyn(u32 id, void *pkg,
                           u32 pkg_num, u32 operation);

/**
 * \brief          SYMC wait done.
 *
 * \param[in]  id The channel number.
 *
 * \return         0 if successful
 */
s32 mpi_symc_crypto_waitdone(u32 id, u32 timeout);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param in      Buffer of input
 * \param inlen   Length of input
 * \param mac     CMAC
 * \param last    last or not
 *
 * \return         0 if successful
 */
s32 mpi_symc_aes_cmac(u32 id, u8 *in, u32 inlen, u8 *mac, u32 last);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 * \param[in]  id The channel number.
 * \param[in]  tag tag data of CCM/GCM
 * \param uuid uuid The user identification.
 *
 * \return         0 if successful
 */
s32 mpi_aead_get_tag(u32 id, u8 *tag, u32 *taglen);

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_hash_init(void);

/**
\brief   Kapi Deinit.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_hash_deinit(void);

/**
 * \brief          HASH context setup.
 *
 *
 * \param[out] id The channel number.
 * \param[in] type    Hash type
 * \param[in] key     hmac key
 * \param[in] keylen  hmac key length
 *
 * \return         0 if successful
 */
s32 mpi_hash_start(u32 *id, CRYP_CIPHER_HASH_TYPE_E type,
                    u8 *key, u32 keylen);

/**
 * \brief          HASH process buffer.
 *
 * \param[in]  id The channel number.
 * \param[in] input    buffer holding the input data
 * \param[in] length   length of the input data
 * \param[in] src      source of hash message
 *
 * \return         0 if successful
 */
s32 mpi_hash_update(u32 id, u8 *input, u32 length,
                     hash_chunk_src src);

/**
 * \brief          HASH final digest.
 *
 * \param[in]  id The channel number.
 * \param[out] hash    buffer holding the hash data
 * \param[out] hashlen length of the hash data
 * \param[in] uuid uuid The user identification.
 *
 * \return         0 if successful
 */
s32 mpi_hash_finish(u32 id, u8 *hash, u32 *hashlen);

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_rsa_init(void);

/**
\brief   Kapi Deinitialize.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_rsa_deinit(void);

/**
* \brief RSA encryption a plaintext with a RSA private key.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa encrypt/decrypt scheme.
* \param[in] in£º   input data to be encryption
* \param[out] inlen:  length of input data to be encryption
* \param[out] out£º   output data of encryption
* \param[out] outlen: length of output data to be encryption
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_encrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
            u8 *in, u32 inlen, u8 *out, u32 *outlen);

/**
* \brief RSA decryption a ciphertext with a RSA public key.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa encrypt/decrypt scheme.
* \param[in] in£º   input data to be encryption
* \param[in] inlen:  length of input data to be encryption
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_decrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
            u8 *in, u32 inlen, u8 *out, u32 *outlen);

/**
* \brief RSA signature a context with appendix, where a signer¡¯s RSA private key is used.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa signature/verify scheme.
* \param[in] in£º    input data to be encryption
* \param[in] inlen:  length of input data to be encryption
* \param[in] hash:   hash value of context,if NULL, let hash = Hash(context) automatically
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \param[in]  src      source of hash message
* \param[in]  uuid uuid The user identification.
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_sign_hash(cryp_rsa_key *key,
                      CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
              u8* hash, u32 hlen, u8 *sign, u32 *signlen);

/**
* \brief RSA verify a ciphertext with a RSA public key.
*
* \param[in]  key_info:   encryption struct.
* \param[in]  in£º   input data to be encryption
* \param[out] inlen:  length of input data to be encryption
* \param[in]  hash:   hash value of context,if NULL, let hash = Hash(context) automatically
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \param[in]  src      source of hash message
* \param[in]  uuid uuid The user identification.
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_verify_hash(cryp_rsa_key *key,
                        CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                        u8 *hash, u32 hlen, u8 *sign, u32 signlen);

/**
* \brief Generate a RSA private key.
*
* \param[in]  key:   rsa key struct.
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_gen_key(cryp_rsa_key *key);

/**
* \brief Compute Diffie-Hellman shared secret as otherPubKey^privKey mod p.
*
* \param[in]  key:   rsa key struct.
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/
s32 mpi_rsa_compute_ctr(cryp_rsa_key *key);

/**
* \brief klad call this function to set iv.
*
* \param[in]  hCIHandle:   handle.
* \param[in]  iv£º   iv data
* \param[in]  inlen:  length of input data to be encryption
* \retval HI_SUCCESS  Call this API successful
* \retval HI_FAILURE  Call this API fails.
*/

s32 mpi_symc_setiv(u32 hCIHandle, u8 *iv, u32 ivlen);

/**
\brief  HDCP encrypt/decrypt use AES-CBC, IV is all zero.
\param[in]  keysel Hdcp root key sel.
\param[in]  ramsel hdmi ram sel.
\param[in]  in The input data.
\param[in]  operation decrypt or decrypt
\param[out] out The input data.
\param[out] len The input data length, must align with 16.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_hdcp_operation(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u8 *hostkey,
                       u8 *in, u8 *out, u32 len, u32 operation);

/**
\brief get rand number.
\param[out]  randnum rand number.
\param[in]   timeout time out.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_trng_get_random( u32 *randnum, u32 timeout);

/**
\brief SM2 signature a context with appendix, where a signer¡¯s SM2 private key is used.
\param d[in]     sm2 private key
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param id[in]    sm2 user id
\param idlen[in] length of sm2 user id
\param msg[in]   mesaage to be sign
\param msglen[in] length of mesaage to be sign
\param src[in]    source of hash message
\param r[out]      sm2 sign result of r
\param s[out]      sm2 sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_sm2_sign(u32 d[SM2_LEN_IN_WROD],
                  u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                  u8 *id, u16 idlen,
                  u8 *msg, u32 msglen, hash_chunk_src src,
                  u8 r[SM2_LEN_IN_BYTE], u8 s[SM2_LEN_IN_BYTE]);
/**
\brief SM2 signature verification a context with appendix, where a signer¡¯s SM2 public key is used.
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param id[in]    sm2 user id
\param idlen[in] length of sm2 user id
\param msg[in]   mesaage to be sign
\param msglen[in] length of mesaage to be sign
\param src[in]    source of hash message
\param r[in]      sm2 sign result of r
\param s[in]      sm2 sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_sm2_verify(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                    u8 *id, u16 idlen, u8 *msg, u32 msglen, hash_chunk_src src,
                    u8 r[SM2_LEN_IN_BYTE], u8 s[SM2_LEN_IN_BYTE]);

/**
\brief SM2 encryption a plaintext with a RSA public key.
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param msg[in]   mesaage to be encryption
\param msglen[in] length of mesaage to be encryption
\param enc[out]    encryption mesaage
\param enclen[out] length of encryption mesaage
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u8 *msg, u32 msglen, u8 *enc, u32 *enclen);
/**
\brief SM2 decryption a plaintext with a RSA public key.
\param d[in]     sm2 private key
\param enc[out]    mesaage to be decryption
\param enclen[out] length of mesaage to be decryption
\param msg[in]     decryption mesaage
\param msglen[in]  length of decryption mesaage
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_sm2_decrypt(u32 d[SM2_LEN_IN_WROD], u8 *enc,
                     u32 enclen, u8 *msg, u32 *msglen);

/**
\brief Generate a SM2 key pair..
\param d[in]     sm2 private key
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_sm2_gen_key(u32 d[SM2_LEN_IN_WROD],
    u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD]);

/**
\brief Compute ECDH shared secret key. This key corresponds to the X coordinates of the computed P point.
\param d[in]     ecc private key
\param px[in]    ecc x public key
\param py[in]    ecc y public key
\param sharekey[out]    ecdh share key
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_ecdh_compute_key(ecc_param_t *ecc, u8 *d, u8 *px, u8 *py, u8 *sharekey);

/**
\brief Generate a ECC key pair.
\param inkey[in]  input private key
\param outkey[in] input private key
\param px[in]    ECC x public key
\param py[in]    ECC y public key
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_ecc_gen_key(ecc_param_t *ecc, u8 *inkey, u8 *outkey, u8 *px, u8 *py);

/**
\brief ECDSA signature a context with appendix, where a signer¡¯s ECC private key is used.
\param d[in]     ECC private key
\param hash[in]  hash to be sign
\param hlen[in]  length of hash to be sign
\param r[out]    ECC sign result of r
\param s[out]    ECC sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_ecdsa_sign_hash(ecc_param_t *ecc, u8 *d, u8 *hash, u32 hlen, u8 *r, u8 *s);

/**
\brief ECDSA signature verification a context with appendix, where a signer¡¯s ECC public key is used.
\param px[in]    ECC x public key
\param py[in]    ECC y public key
\param hash[in]  hash to be verification
\param hlen[in]  length of hash to be verification
\param r[in]    ECDSA sign result of r
\param s[in]    ECDSA sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 mpi_ecdsa_verify_hash(ecc_param_t *ecc, u8 *px, u8 *py, u8 *hash, u32 hlen, u8 *r, u8 *s);

/**
\brief CENC decryption a ciphertext.
\param id[in] Cipher handle
\param key[in] for cipher decryption
\param iv[in] for cipher decryption
\param inphy[in] non-secure Physical address of the source data
\param outphy[in] secure Physical address of the target data
\param length[in] Length of the decrypted data
\param firstoffset[in] offset of the first encrypt block data
\retval HI_SUCCESS  Call this API succussful.
\retval HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 mpi_cenc_decrypt(u32 id, u8 *key, u8 *iv, u32 inphy, u32 outphy,
                     u32 length, u32 firstoffset,
                     CRYP_CIPHER_SUBSAMPLE_S *subsample, u32 subsample_num);

#if defined(HI_PLATFORM_TYPE_TEE)

/**
\brief Calculate a key of PBKDF2
\param password[in] The PBKDF2 password.
\param plen[in]     The length of PBKDF2 password.
\param salt[in]     The salt password.
\param slen[in]     The length of salt.
\param iteration_count[in] iteration count.
\param outlen[in]   The length PBKDF2 key.
\param output[out]  The PBKDF2 key.
\retval HI_SUCCESS  Call this API successful.
\retval HI_FAILURE  Call this API fails.
*/
s32 mpi_pbkdf_hmac256(u8 *password, u32 plen, u8 *salt, u32 slen,
                      u32 iteration_count, u32 outlen, u8 *out);
/**
\brief Set usage rule.
\param[in] hCipher Cipher handle.
\param[in] pstCipherUR usage rule information.
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
*/
s32 mpi_set_usage_rule(u32 hCipher, CRYP_CIPHER_UR_S *pstCipherUR);

/**
\brief self test
\param param[in]  params.
\param size[in]   size of params.
\retval HI_SUCCESS  Call this API successful.
\retval HI_FAILURE  Call this API fails.
*/
s32 mpi_crypto_self_test(u32 cmd, void *param, u32 size);
#endif

/** @}*/  /** <!-- ==== API Code end ====*/

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#endif    /* End of #ifndef __MPI_CIPHER_H__*/
