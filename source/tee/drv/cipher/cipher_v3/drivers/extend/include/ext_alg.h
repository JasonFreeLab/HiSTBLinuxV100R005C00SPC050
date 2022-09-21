/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_alg.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __EXT_ALG_H_
#define __EXT_ALG_H_

#include "drv_osal_lib.h"
#include "drv_hash.h"
#include "drv_symc.h"

/******************************* API Declaration *****************************/
/** \addtogroup      hash */
/** @{ */  /** <!--[hash]*/


/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/**
* \brief          AES CMAC init
* \param id       hard key or not
* \param hkey     input data
* \param key      key buffer
* \param klen     key length
*/
s32 ext_aes_cmac_init(u32 id, u32 hkey, u8 *key, CRYP_CIPHER_KEY_LENGTH_E klen);

/**
* \brief          AES CMAC update data
* \param id       kapi symc channel ID
* \param input    input data
* \param inlen    input data length, must align at aes block size
*/
s32 ext_aes_cmac_update(u32 id, u8 *input, u32 inlen);

/**
* \brief          AES CMAC Finish
* \param id       kapi symc channel ID
* \param input    input data
* \param inlen    input data length, must align at aes block size
* \param mac      cmac output data
*/
s32 ext_aes_cmac_finish(u32 id, u8 *input, u32 inlen, u8 *mac);

/**
 * \brief          Create symc handle
 *
 * \param handle   symc handle to be initialized
 * \param hard_key symc use hard key ot not
 */
void * ext_mbedtls_aead_create(u32 hard_key);

/**
 * \brief          Clear symc context
 *
 * \param handle      symc handle to be destory
 */
s32 ext_mbedtls_aead_destory( void *ctx);

/**
 * \brief          symc iv schedule
 *
 * \param handle   symc handle
 * \param IV       encryption key
 * \param ivlen    length of iv
 *
 * \return         0 if successful.
 */
s32 ext_mbedtls_aead_setiv( void *ctx, const u8 *iv, u32 ivlen, u32 usage);

/**
 * \brief          symc key schedule
 *
 * \param ctx      SYMC handle
 * \param key      SYMC key
 * \param keylen   SYMC key length
 *
 * \return         0 if successful, or HI_SYMC_ERR_KEY_LEN_INVALID
 */
s32 ext_mbedtls_aead_setkey( void *ctx, const u8 *fkey, const u8 *skey, u32 hisi_klen);

/**
 * \brief          SYMC alg and mode
 *
 * \param ctx      SYMC handle
 * \param aad      Associated Data
 * \param alen     Associated Data Length
 * \param tlen     Tag length
 *
 * \return         0 if successful.
 */
s32 ext_mbedtls_aead_set_aad( void *ctx, compat_addr aad, u32 alen, u32 tlen);

/**
\brief  get ccm/gcm tag.
\param[in]   chn_num The channel number.
\param[out]  tag The tag value.
\param[out]  taglen tag length
\retval     On received interception, HI_TRUE is returned  otherwise HI_FALSE is returned.
*/
s32 ext_mbedtls_aead_get_tag(void *ctx, u32 tag[AEAD_TAG_SIZE_IN_WORD], u32 *taglen);

/**
 * \brief          aead ccm buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param handle   symc handle
 * \param decrypt  decrypt or encrypt
 * \param mode     mode
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param usage_list usage of buffer
 * \param pkg_num  numbers of buffer
 *
 * \return         0 if successful
 */
s32 ext_mbedtls_aead_ccm_crypto( void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    u32 usage_list[],
                    u32 pkg_num, u32 last);

/**
 * \brief          aead gcm buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param handle   symc handle
 * \param decrypt  decrypt or encrypt
 * \param mode     mode
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param usage_list usage of buffer
 * \param pkg_num  numbers of buffer
 *
 * \return         0 if successful
 */
s32 ext_mbedtls_aead_gcm_crypto( void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    u32 usage_list[],
                    u32 pkg_num, u32 last);

/**
 * \brief          Create symc handle
 *
 * \param handle   symc handle to be initialized
 * \param hard_key symc use hard key ot not
 */
void * ext_mbedtls_symc_create(u32 hard_key);

/**
 * \brief          Clear symc context
 *
 * \param handle      symc handle to be destory
 */
s32 ext_mbedtls_symc_destory( void *ctx);

/**
 * \brief          SYMC alg and mode
 *
 * \param handle   SYMC handle
 * \param alg      Symmetric cipher alg
 * \param mode     Symmetric cipher mode
 *
 * \return         0 if successful.
 */
void ext_mbedtls_symc_setmode( void *ctx, symc_alg alg, symc_mode mode, symc_width width);

/**
 * \brief          symc iv schedule
 *
 * \param handle   symc handle
 * \param IV       encryption key
 * \param ivlen    length of iv
 *
 * \return         0 if successful.
 */
s32 ext_mbedtls_symc_setiv( void *ctx, const u8 *iv, u32 ivlen, u32 usage);

/**
 * \brief          Symc iv schedule
 *
 * \param handle   symc handle
 * \param IV       Symc IV
 * \param ivlen    must be 128, 192 or 256
 *
 * \return         0 if successful.
 */
void ext_mbedtls_symc_getiv( void *ctx, u8 *iv, u32 *ivlen);

/**
 * \brief          symc key schedule
 *
 * \param ctx      SYMC handle
 * \param key      SYMC key
 * \param keylen   SYMC key length
 *
 * \return         0 if successful, or HI_SYMC_ERR_KEY_LEN_INVALID
 */
s32 ext_mbedtls_symc_setkey( void *ctx, const u8 *fkey, const u8 *skey, u32 hisi_klen);

/**
 * \brief          symc buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param handle   symc handle
 * \param decrypt  decrypt or encrypt
 * \param mode     mode
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param usage_list usage of buffer
 * \param pkg_num  numbers of buffer
 *
 * \return         0 if successful
 */
s32 ext_mbedtls_symc_crypto( void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last);

/**
 * \brief          Create sm4 handle
 *
 * \param handle   sm4 handle to be initialized
 * \param hard_key sm4 use hard key ot not
 */
void * ext_sm4_create(u32 hard_key);

/**
 * \brief          Clear sm4 context
 *
 * \param handle      sm4 handle to be destory
 */
s32 ext_sm4_destory( void *ctx);

/**
 * \brief          sm4 alg and mode
 *
 * \param handle   sm4 handle
 * \param alg      Symmetric cipher alg
 * \param mode     Symmetric cipher mode
 *
 * \return         NA.
 */
void ext_sm4_setmode( void *ctx, symc_alg alg, symc_mode mode, symc_width width);

/**
 * \brief          sm4 iv schedule
 *
 * \param handle   sm4 handle
 * \param IV       encryption key
 * \param ivlen    length of iv
 *
 * \return         0 if successful.
 */
s32 ext_sm4_setiv( void *ctx, const u8 *iv, u32 ivlen, u32 usage);

/**
 * \brief          Symc iv schedule
 *
 * \param handle   symc handle
 * \param IV       Symc IV
 * \param ivlen    must be 128, 192 or 256
 *
 * \return         NA.
 */
void ext_sm4_getiv( void *ctx, u8 *iv, u32 *ivlen);

/**
 * \brief          sm4 key schedule
 *
 * \param ctx      sm4 handle
 * \param key      sm4 key
 * \param keylen   sm4 key length
 *
 * \return         0 if successful, or HI_SYMC_ERR_KEY_LEN_INVALID
 */
s32 ext_sm4_setkey( void *ctx, const u8 *fkey, const u8 *skey, u32 hisi_klen);

/**
 * \brief          sm4 buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param handle   sm4 handle
 * \param decrypt  decrypt or encrypt
 * \param mode     mode
 * \param length   length of the input data
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param usage_list usage of buffer
 * \param pkg_num  numbers of buffer
 *
 * \return         0 if successful
 */
s32 ext_sm4_crypto( void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last);

/**
 * \brief          Clear hash context
 *
 * \param ctx      symc handle to be destory
 */
void * mbedtls_hash_create(hash_mode mode);

/**
 * \brief          Hash message chunk calculation
 *
 * Note: the message must be write to the buffer
 * which get from cryp_hash_get_cpu_addr, and the length of message chunk
 * can't large than the length which get from cryp_hash_get_cpu_addr.
 *
 * \param ctx      hash handle to be destory
 * \param chunk    hash message to update
 * \param length   length of hash message
 * \param src      source of hash message
 */
s32 mbedtls_hash_update( void *ctx, u8 *chunk, u32 chunkLen, hash_chunk_src src);

/**
 * \brief          HASH final digest
 *
 * \param ctx      Hash handle
 * \param hash     HASH checksum result
 * \param hashlen  Length of HASH checksum result
 */
s32 mbedtls_hash_finish( void *ctx,  void *hash, u32 *hashlen);

/**
 * \brief          Clear hash context
 *
 * \param ctx      symc handle to be destory
 */
s32 mbedtls_hash_destory( void *ctx);

/* sm3 */
void * ext_sm3_create(hash_mode mode);

s32 ext_sm3_update( void *ctx, u8 *chunk, u32 chunkLen, hash_chunk_src src);

s32 ext_sm3_finish( void *ctx,  void *hash, u32 *hashlen);

s32 ext_sm3_destory( void *ctx);

/* sm2 */
s32 mbedtls_sm2_sign(u32 e[SM2_LEN_IN_WROD], u32 d[SM2_LEN_IN_WROD],
                     u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);

s32 mbedtls_sm2_verify(u32 e[SM2_LEN_IN_WROD],
                       u32 px[SM2_LEN_IN_WROD],u32 py[SM2_LEN_IN_WROD],
                       u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);

s32 mbedtls_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                        u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                        u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD]);

s32 mbedtls_sm2_decrypt(u32 d[SM2_LEN_IN_WROD],
                        u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                        u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD]);

s32 mbedtls_sm2_gen_key(u32 d[SM2_LEN_IN_WROD],
                        u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD]);

/**
* \ brief Computes CRT parameters dP, dQ and qInv from the two primes p and q and the public exponent e.
* \param key      rsa key
* \return         0 if successful
*/
s32 ext_rsa_compute_crt(cryp_rsa_key *key);

/**
* \ brief gen rsa key.
* \param key      rsa key
* \return         0 if successful
*/
s32 ext_rsa_gen_key(cryp_rsa_key *key);

/**
* \brief Compute ECDH shared secret key. This key corresponds to the X coordinates of the computed P point.
* \param d         ecc private key
* \param px        ecc x public key
* \param py        ecc y public key
* \param sharekey  ecdh share key
* \retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 ext_ecdh_compute_key(ecc_param_t *ecc, u8 *d, u8 *px, u8 *py, u8 *sharekey);

/**
* \brief Generate a ECC key pair.
* \param inkey    input private key
* \param outkey   input private key
* \param px       ECC x public key
* \param py       ECC y public key
* \retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 ext_ecc_gen_key(ecc_param_t *ecc, u8 *inkey, u8 *outkey, u8 *px, u8 *py);

/**
* \brief ECDSA signature a context with appendix, where a signer¡¯s ECC private key is used.
* \param d         ECC private key
* \param hash      hash to be sign
* \param hlen      length of hash to be sign
* \param r         ECC sign result of r
* \param s         ECC sign result of s
* \retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 ext_ecdsa_sign_hash(ecc_param_t *ecc, u8 *d, u8 *hash, u32 hlen, u8 *r, u8 *s);

/**
* \brief ECDSA signature verification a context with appendix, where a signer¡¯s ECC public key is used.
* \param px       ECC x public key
* \param py       ECC y public key
* \param hash     hash to be verification
* \param hlen     length of hash to be verification
* \param r        ECDSA sign result of r
* \param s        ECDSA sign result of s
* \retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 ext_ecdsa_verify_hash(ecc_param_t *ecc, u8 *px, u8 *py, u8 *hash, u32 hlen, u8 *r, u8 *s);

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

/** @} */  /** <!-- ==== API declaration end ==== */
#endif
