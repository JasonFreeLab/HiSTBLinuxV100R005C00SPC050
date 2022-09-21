#ifndef __CRYP_COMPAT_H__
#define __CRYP_COMPAT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* enum defined */
#define CRYP_CIPHER_WORK_MODE_E                                       HI_TEE_CIPHER_WORK_MODE_E
#define CRYP_CIPHER_WORK_MODE_ECB                                     HI_TEE_CIPHER_WORK_MODE_ECB
#define CRYP_CIPHER_WORK_MODE_CBC                                     HI_TEE_CIPHER_WORK_MODE_CBC
#define CRYP_CIPHER_WORK_MODE_CFB                                     HI_TEE_CIPHER_WORK_MODE_CFB
#define CRYP_CIPHER_WORK_MODE_OFB                                     HI_TEE_CIPHER_WORK_MODE_OFB
#define CRYP_CIPHER_WORK_MODE_CTR                                     HI_TEE_CIPHER_WORK_MODE_CTR
#define CRYP_CIPHER_WORK_MODE_CCM                                     HI_TEE_CIPHER_WORK_MODE_CCM
#define CRYP_CIPHER_WORK_MODE_GCM                                     HI_TEE_CIPHER_WORK_MODE_GCM
#define CRYP_CIPHER_WORK_MODE_CBC_CTS                                 HI_TEE_CIPHER_WORK_MODE_CBC_CTS
#define CRYP_CIPHER_WORK_MODE_BUTT                                    HI_TEE_CIPHER_WORK_MODE_BUTT

#define CRYP_CIPHER_ALG_E                                             HI_TEE_CIPHER_ALG_E
#define CRYP_CIPHER_ALG_DES                                           HI_TEE_CIPHER_ALG_DES
#define CRYP_CIPHER_ALG_3DES                                          HI_TEE_CIPHER_ALG_3DES
#define CRYP_CIPHER_ALG_AES                                           HI_TEE_CIPHER_ALG_AES
#define CRYP_CIPHER_ALG_SM1                                           HI_TEE_CIPHER_ALG_SM1
#define CRYP_CIPHER_ALG_SM4                                           HI_TEE_CIPHER_ALG_SM4
#define CRYP_CIPHER_ALG_DMA                                           HI_TEE_CIPHER_ALG_DMA
#define CRYP_CIPHER_ALG_BUTT                                          HI_TEE_CIPHER_ALG_BUTT

#define CRYP_CIPHER_KEY_LENGTH_E                                      HI_TEE_CIPHER_KEY_LENGTH_E
#define CRYP_CIPHER_KEY_AES_128BIT                                    HI_TEE_CIPHER_KEY_AES_128BIT
#define CRYP_CIPHER_KEY_AES_192BIT                                    HI_TEE_CIPHER_KEY_AES_192BIT
#define CRYP_CIPHER_KEY_AES_256BIT                                    HI_TEE_CIPHER_KEY_AES_256BIT
#define CRYP_CIPHER_KEY_DES_3KEY                                      HI_TEE_CIPHER_KEY_DES_3KEY
#define CRYP_CIPHER_KEY_DES_2KEY                                      HI_TEE_CIPHER_KEY_DES_2KEY
#define CRYP_CIPHER_KEY_DEFAULT                                       HI_TEE_CIPHER_KEY_DEFAULT

#define CRYP_CIPHER_BIT_WIDTH_E                                       HI_TEE_CIPHER_BIT_WIDTH_E
#define CRYP_CIPHER_BIT_WIDTH_64BIT                                   HI_TEE_CIPHER_BIT_WIDTH_64BIT
#define CRYP_CIPHER_BIT_WIDTH_8BIT                                    HI_TEE_CIPHER_BIT_WIDTH_8BIT
#define CRYP_CIPHER_BIT_WIDTH_1BIT                                    HI_TEE_CIPHER_BIT_WIDTH_1BIT
#define CRYP_CIPHER_BIT_WIDTH_128BIT                                  HI_TEE_CIPHER_BIT_WIDTH_128BIT

#define CRYP_CIPHER_SM1_ROUND_E                                       HI_TEE_CIPHER_SM1_ROUND_E
#define CRYP_CIPHER_SM1_ROUND_08                                      HI_TEE_CIPHER_SM1_ROUND_08
#define CRYP_CIPHER_SM1_ROUND_10                                      HI_TEE_CIPHER_SM1_ROUND_10
#define CRYP_CIPHER_SM1_ROUND_12                                      HI_TEE_CIPHER_SM1_ROUND_12
#define CRYP_CIPHER_SM1_ROUND_14                                      HI_TEE_CIPHER_SM1_ROUND_14
#define CRYP_CIPHER_SM1_ROUND_BUTT                                    HI_TEE_CIPHER_SM1_ROUND_BUTT

#define CRYP_CIPHER_CTRL_CHANGE_FLAG_S                                HI_TEE_CIPHER_CTRL_CHANGE_FLAG_S

#define CRYP_CIPHER_CA_TYPE_E                                         HI_TEE_CIPHER_CA_TYPE_E
#define CRYP_CIPHER_CA_TYPE_R2R                                       HI_TEE_CIPHER_CA_TYPE_R2R
#define CRYP_CIPHER_CA_TYPE_SP                                        HI_TEE_CIPHER_CA_TYPE_SP
#define CRYP_CIPHER_CA_TYPE_CSA2                                      HI_TEE_CIPHER_CA_TYPE_CSA2
#define CRYP_CIPHER_CA_TYPE_CSA3                                      HI_TEE_CIPHER_CA_TYPE_CSA3
#define CRYP_CIPHER_CA_TYPE_MISC                                      HI_TEE_CIPHER_CA_TYPE_MISC
#define CRYP_CIPHER_CA_TYPE_GDRM                                      HI_TEE_CIPHER_CA_TYPE_GDRM
#define CRYP_CIPHER_CA_TYPE_BLPK                                      HI_TEE_CIPHER_CA_TYPE_BLPK
#define CRYP_CIPHER_CA_TYPE_LPK                                       HI_TEE_CIPHER_CA_TYPE_LPK
#define CRYP_CIPHER_CA_TYPE_IRDETO_HCA                                HI_TEE_CIPHER_CA_TYPE_IRDETO_HCA
#define CRYP_CIPHER_CA_TYPE_STBROOTKEY                                HI_TEE_CIPHER_CA_TYPE_STBROOTKEY
#define CRYP_CIPHER_CA_TYPE_BUTT                                      HI_TEE_CIPHER_CA_TYPE_BUTT

#define CRYP_CIPHER_UR_S                                              HI_TEE_CIPHER_UR_S

#define CRYP_CIPHER_TYPE_E                                            HI_TEE_CIPHER_TYPE_E
#define CRYP_CIPHER_TYPE_NORMAL                                       HI_TEE_CIPHER_TYPE_NORMAL
#define CRYP_CIPHER_TYPE_COPY_AVOID                                   HI_TEE_CIPHER_TYPE_COPY_AVOID
#define CRYP_CIPHER_TYPE_BUTT                                         HI_TEE_CIPHER_TYPE_BUTT

#define CRYP_CIPHER_HASH_TYPE_SHA1                                    HI_TEE_CIPHER_HASH_TYPE_SHA1
#define CRYP_CIPHER_HASH_TYPE_SHA224                                  HI_TEE_CIPHER_HASH_TYPE_SHA224
#define CRYP_CIPHER_HASH_TYPE_SHA256                                  HI_TEE_CIPHER_HASH_TYPE_SHA256
#define CRYP_CIPHER_HASH_TYPE_SHA384                                  HI_TEE_CIPHER_HASH_TYPE_SHA384
#define CRYP_CIPHER_HASH_TYPE_SHA512                                  HI_TEE_CIPHER_HASH_TYPE_SHA512
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA1                               HI_TEE_CIPHER_HASH_TYPE_HMAC_SHA1
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA224                             HI_TEE_CIPHER_HASH_TYPE_HMAC_SHA224
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA256                             HI_TEE_CIPHER_HASH_TYPE_HMAC_SHA256
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA384                             HI_TEE_CIPHER_HASH_TYPE_HMAC_SHA384
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA512                             HI_TEE_CIPHER_HASH_TYPE_HMAC_SHA512
#define CRYP_CIPHER_HASH_TYPE_SM3                                     HI_TEE_CIPHER_HASH_TYPE_SM3
#define CRYP_CIPHER_HASH_TYPE_IRDETO_CBCMAC                           HI_TEE_CIPHER_HASH_TYPE_IRDETO_CBCMAC
#define CRYP_CIPHER_HASH_TYPE_BUTT                                    HI_TEE_CIPHER_HASH_TYPE_BUTT

#define CRYP_CIPHER_RSA_ENC_SCHEME_E                                  HI_TEE_CIPHER_RSA_ENC_SCHEME_E
#define CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING                         HI_TEE_CIPHER_RSA_ENC_SCHEME_NO_PADDING
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0                       HI_TEE_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1                       HI_TEE_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2                       HI_TEE_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1                    HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224                  HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256                  HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384                  HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512                  HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5                   HI_TEE_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5
#define CRYP_CIPHER_RSA_ENC_SCHEME_BUTT                               HI_TEE_CIPHER_RSA_ENC_SCHEME_BUTT

#define CRYP_CIPHER_RSA_SIGN_SCHEME_E                                 HI_TEE_CIPHER_RSA_SIGN_SCHEME_E
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1             HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1             HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512           HI_TEE_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512
#define CRYP_CIPHER_RSA_SIGN_SCHEME_BUTT                              HI_TEE_CIPHER_RSA_SIGN_SCHEME_BUTT

/* struct defined */
#define CRYP_CIPHER_ATTS_S                                            HI_TEE_CIPHER_ATTS_S
#define CRYP_CIPHER_CTRL_S                                            HI_TEE_CIPHER_CTRL_S
#define CRYP_CIPHER_CTRL_AES_S                                        HI_TEE_CIPHER_CTRL_AES_S
#define CRYP_CIPHER_CTRL_AES_CCM_GCM_S                                HI_TEE_CIPHER_CTRL_AES_CCM_GCM_S
#define CRYP_CIPHER_CTRL_DES_S                                        HI_TEE_CIPHER_CTRL_DES_S
#define CRYP_CIPHER_CTRL_3DES_S                                       HI_TEE_CIPHER_CTRL_3DES_S
#define CRYP_CIPHER_CTRL_SM1_S                                        HI_TEE_CIPHER_CTRL_SM1_S
#define CRYP_CIPHER_CTRL_SM4_S                                        HI_TEE_CIPHER_CTRL_SM4_S
#define CRYP_CIPHER_CTRL_EX_S                                         HI_TEE_CIPHER_CTRL_EX_S
#define CRYP_CIPHER_DATA_S                                            HI_TEE_CIPHER_DATA_S

#define CRYP_CIPHER_HASH_TYPE_E                                       HI_TEE_CIPHER_HASH_TYPE_E
#define CRYP_CIPHER_HASH_ATTS_S                                       HI_TEE_CIPHER_HASH_ATTS_S

#define CRYP_CIPHER_RSA_PUB_KEY_S                                     HI_TEE_CIPHER_RSA_PUB_KEY_S
#define CRYP_CIPHER_RSA_PRI_KEY_S                                     HI_TEE_CIPHER_RSA_PRI_KEY_S
#define CRYP_CIPHER_RSA_PUB_ENC_S                                     HI_TEE_CIPHER_RSA_PUB_ENC_S
#define CRYP_CIPHER_RSA_PRI_ENC_S                                     HI_TEE_CIPHER_RSA_PRI_ENC_S
#define CRYP_CIPHER_RSA_SIGN_S                                        HI_TEE_CIPHER_RSA_SIGN_S

#define CRYP_CIPHER_RSA_VERIFY_S                                      HI_TEE_CIPHER_RSA_VERIFY_S
#define CRYP_CIPHER_SM2_SIGN_S                                        HI_TEE_CIPHER_SM2_SIGN_S
#define CRYP_CIPHER_SM2_VERIFY_S                                      HI_TEE_CIPHER_SM2_VERIFY_S
#define CRYP_CIPHER_SM2_ENC_S                                         HI_TEE_CIPHER_SM2_ENC_S
#define CRYP_CIPHER_SM2_DEC_S                                         HI_TEE_CIPHER_SM2_DEC_S
#define CRYP_CIPHER_SM2_KEY_S                                         HI_TEE_CIPHER_SM2_KEY_S
#define CRYP_CIPHER_ECC_PARAM_S                                       HI_TEE_CIPHER_ECC_PARAM_S

#define CRYP_CIPHER_SUBSAMPLE_S                                       HI_TEE_CIPHER_SUBSAMPLE_S

/* function defined */
#define CRYP_CIPHER_Init                                              HI_TEE_CIPHER_Init
#define CRYP_CIPHER_DeInit                                            HI_TEE_CIPHER_DeInit
#define CRYP_CIPHER_CreateHandle                                      HI_TEE_CIPHER_CreateHandle
#define CRYP_CIPHER_DestroyHandle                                     HI_TEE_CIPHER_DestroyHandle
#define CRYP_CIPHER_ConfigHandle                                      HI_TEE_CIPHER_ConfigHandle
#define CRYP_CIPHER_ConfigHandleEx                                    HI_TEE_CIPHER_ConfigHandleEx
#define CRYP_CIPHER_Encrypt                                           HI_TEE_CIPHER_Encrypt
#define CRYP_CIPHER_Decrypt                                           HI_TEE_CIPHER_Decrypt
#define CRYP_CIPHER_EncryptMulti                                      HI_TEE_CIPHER_EncryptMulti
#define CRYP_CIPHER_DecryptMulti                                      HI_TEE_CIPHER_DecryptMulti
#define CRYP_CIPHER_GetTag                                            HI_TEE_CIPHER_GetTag
#define CRYP_CIPHER_SetUsageRule                                      HI_TEE_CIPHER_SetUsageRule

#define CRYP_CIPHER_GetRandomNumber                                   HI_TEE_CIPHER_GetRandomNumber

#define CRYP_CIPHER_CalcMAC                                           HI_TEE_CIPHER_CalcMAC
#define CRYP_CIPHER_HashInit                                          HI_TEE_CIPHER_HashInit
#define CRYP_CIPHER_HashUpdate                                        HI_TEE_CIPHER_HashUpdate
#define CRYP_CIPHER_HashFinal                                         HI_TEE_CIPHER_HashFinal

#define CRYP_CIPHER_RsaPublicEncrypt                                  HI_TEE_CIPHER_RsaPublicEncrypt
#define CRYP_CIPHER_RsaPrivateDecrypt                                 HI_TEE_CIPHER_RsaPrivateDecrypt
#define CRYP_CIPHER_RsaPrivateEncrypt                                 HI_TEE_CIPHER_RsaPrivateEncrypt
#define CRYP_CIPHER_RsaPublicDecrypt                                  HI_TEE_CIPHER_RsaPublicDecrypt
#define CRYP_CIPHER_RsaSign                                           HI_TEE_CIPHER_RsaSign
#define CRYP_CIPHER_RsaVerify                                         HI_TEE_CIPHER_RsaVerify
#define CRYP_CIPHER_RsaGenKey                                         HI_TEE_CIPHER_RsaGenKey
#define CRYP_CIPHER_RsaComputeCrtParams                               HI_TEE_CIPHER_RsaComputeCrtParams

#define CRYP_CIPHER_Sm2Sign                                           HI_TEE_CIPHER_Sm2Sign
#define CRYP_CIPHER_Sm2Verify                                         HI_TEE_CIPHER_Sm2Verify
#define CRYP_CIPHER_Sm2Encrypt                                        HI_TEE_CIPHER_Sm2Encrypt
#define CRYP_CIPHER_Sm2Decrypt                                        HI_TEE_CIPHER_Sm2Decrypt
#define CRYP_CIPHER_Sm2GenKey                                         HI_TEE_CIPHER_Sm2GenKey

#define CRYP_CIPHER_CENCDecrypt                                       HI_TEE_CIPHER_CENCDecrypt

#define CRYP_CIPHER_DhComputeKey                                      HI_TEE_CIPHER_DhComputeKey
#define CRYP_CIPHER_DhGenKey                                          HI_TEE_CIPHER_DhGenKey
#define CRYP_CIPHER_EcdhComputeKey                                    HI_TEE_CIPHER_EcdhComputeKey
#define CRYP_CIPHER_EccGenKey                                         HI_TEE_CIPHER_EccGenKey
#define CRYP_CIPHER_EcdsaSign                                         HI_TEE_CIPHER_EcdsaSign
#define CRYP_CIPHER_EcdsaVerify                                       HI_TEE_CIPHER_EcdsaVerify

#define CRYP_CIPHER_Test                                              HI_TEE_CIPHER_Test
#define CRYP_CIPHER_PBKDF2                                            HI_TEE_CIPHER_PBKDF2
#define CRYP_CIPHER_EncryptMultiAsyn                                  HI_TEE_CIPHER_EncryptMultiAsyn
#define CRYP_CIPHER_DecryptMultiAsyn                                  HI_TEE_CIPHER_DecryptMultiAsyn
#define CRYP_CIPHER_WaitDone                                          HI_TEE_CIPHER_WaitDone
#define CRYP_CIPHER_GetHandleConfig                                   HI_TEE_CIPHER_GetHandleConfig
#define CRYP_CIPHER_PBKDF2_S                                          HI_TEE_CIPHER_PBKDF2_S

#define HI_ERR_CIPHER_NOT_INIT                                        HI_TEE_ERR_UNINITED
#define HI_ERR_CIPHER_INVALID_HANDLE                                  HI_TEE_ERR_CIPHER_INVALID_HANDLE
#define HI_ERR_CIPHER_INVALID_POINT                                   HI_TEE_ERR_INVALID_PTR
#define HI_ERR_CIPHER_INVALID_PARA                                    HI_TEE_ERR_INVALID_PARAM
#define HI_ERR_CIPHER_FAILED_INIT                                     HI_TEE_ERR_INITED
#define HI_ERR_CIPHER_FAILED_CONFIGAES                                HI_TEE_ERR_CIPHER_FAILED_CONFIGAES
#define HI_ERR_CIPHER_FAILED_CONFIGDES                                HI_TEE_ERR_CIPHER_FAILED_CONFIGDES
#define HI_ERR_CIPHER_FAILED_ENCRYPT                                  HI_TEE_ERR_ENCRYPT
#define HI_ERR_CIPHER_FAILED_DECRYPT                                  HI_TEE_ERR_DECRYPT
#define HI_ERR_CIPHER_BUSY                                            HI_TEE_ERR_INUSE
#define HI_ERR_CIPHER_NO_AVAILABLE_RNG                                HI_TEE_ERR_CIPHER_NO_AVAILABLE_RNG
#define HI_ERR_CIPHER_FAILED_MEM                                      HI_TEE_ERR_MEM
#define HI_ERR_CIPHER_UNAVAILABLE                                     HI_TEE_ERR_UNAVAILABLE
#define HI_ERR_CIPHER_OVERFLOW                                        HI_TEE_ERR_OVERFLOW
#define HI_ERR_CIPHER_HARD_STATUS                                     HI_TEE_ERR_STATUS
#define HI_ERR_CIPHER_TIMEOUT                                         HI_TEE_ERR_TIMER
#define HI_ERR_CIPHER_UNSUPPORTED                                     HI_TEE_ERR_UNSUPPORTED
#define HI_ERR_CIPHER_REGISTER_IRQ                                    HI_TEE_ERR_CIPHER_REGISTER_IRQ
#define HI_ERR_CIPHER_ILLEGAL_UUID                                    HI_TEE_ERR_ILLEGAL_UUID
#define HI_ERR_CIPHER_ILLEGAL_KEY                                     HI_TEE_ERR_ILLEGAL_KEY
#define HI_ERR_CIPHER_INVALID_ADDR                                    HI_TEE_ERR_INVALID_ADDR
#define HI_ERR_CIPHER_INVALID_LENGTH                                  HI_TEE_ERR_INVALID_LENGTH
#define HI_ERR_CIPHER_ILLEGAL_DATA                                    HI_TEE_ERR_CIPHER_ILLEGAL_DATA
#define HI_ERR_CIPHER_RSA_SIGN                                        HI_TEE_ERR_CIPHER_RSA_SIGN
#define HI_ERR_CIPHER_RSA_VERIFY                                      HI_TEE_ERR_CIPHER_RSA_VERIFY

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __CRYP_CIPHER_H__ */
