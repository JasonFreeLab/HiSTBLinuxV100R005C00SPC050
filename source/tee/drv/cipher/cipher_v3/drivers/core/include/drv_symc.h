/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_symc.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_CIPHER_H__
#define __DRV_CIPHER_H__

/*************************** Structure Definition ****************************/
/** \addtogroup     symmetric cipher */
/** @{ */  /** <!-- [symc] */

/*! \symmetric cipher max key size in words */
#define SYMC_KEY_MAX_SIZE_IN_WORD      (8)

/*! \symmetric cipher max iv size in word */
#define SYMC_IV_MAX_SIZE_IN_WORD       (4)

/*! \symmetric sm1 sk size in words */
#define SYMC_SM1_SK_SIZE_IN_WORD       (4)

/*! \DES BLOCK size */
#define DES_BLOCK_SIZE      (8)

/*! \Numbers of nodes list */
#define SYMC_MAX_LIST_NUM        (64)

/*! \Length of CCM N */
#define SYMC_CCM_N_LEN            (16)

/*! \Length of CCM A head */
#define SYMC_CCM_A_HEAD_LEN        (16)

/*! \Length of GCM CLEN */
#define SYMC_GCM_CLEN_LEN        (16)

/*! \Small length of CCM A  */
#define SYMC_CCM_A_SMALL_LEN     (0x10000 - 0x100)

/*! \AES KEY size 128bit*/
#define AES_KEY_128BIT      (16)

/*! \AES KEY size 192bit*/
#define AES_KEY_192BIT      (24)

/*! \AES KEY size 256bit*/
#define AES_KEY_256BIT      (32)

/*! \DES KEY size 128bit*/
#define DES_KEY_SIZE        (8)

/*! \TDES KEY size 128bit*/
#define TDES_KEY_128BIT      (16)

/*! \TDES KEY size 192bit*/
#define TDES_KEY_192BIT      (24)

/*! \DES block size*/
#define DES_BLOCK_SIZE       (8)

/*! \SM1 KEY size */
#define SM1_AK_EK_SIZE       (32)
#define SM1_SK_SIZE          (16)

/*! \SM4 KEY size */
#define SM4_KEY_SIZE         (16)

/*! \symmetric cipher width */
typedef enum
{
    SYMC_DAT_WIDTH_64 = 0,
    SYMC_DAT_WIDTH_128 = 0,
    SYMC_DAT_WIDTH_8,
    SYMC_DAT_WIDTH_1,
    SYMC_DAT_WIDTH_COUNT,
}symc_width;

/*! \symmetric cipher algorithm */
typedef enum
{
    SYMC_ALG_DES,         /*!<  Data Encryption Standard  */
    SYMC_ALG_TDES,        /*!<  Triple Data Encryption Standard  */
    SYMC_ALG_AES,         /*!<  Advanced Encryption Standard  */
    SYMC_ALG_SM4,         /*!<  SM4 Algorithm  */
    SYMC_ALG_SM1,         /*!<  SM1 Algorithm  */
    SYMC_ALG_NULL_CIPHER, /*!<  null cipher, dma copy  */
    SYMC_ALG_COUNT,
}symc_alg;

/*! \symmetric cipher key length */
typedef enum
{
    SYMC_KEY_DEFAULT = 0,   /*!<  Default, aes-128, 3des-192, sm1-256, sm4-128 */
    SYMC_KEY_AES_192BIT,        /*!<  AES 192 bit key */
    SYMC_KEY_AES_256BIT,        /*!<  AES 256 bit key */
    SYMC_KEY_TDES_2KEY,         /*!<  3DES 128 bit key */
    SYMC_KEY_LEN_COUNT,
}symc_klen;

/*! \symmetric cipher mode */
typedef enum
{
    SYMC_MODE_ECB = 0, /*!<  Electronic Codebook Mode */
    SYMC_MODE_CBC,     /*!<  Cipher Block Chaining */
    SYMC_MODE_CFB,     /*!<  Cipher Feedback Mode */
    SYMC_MODE_OFB,     /*!<  Output Feedback Mode */
    SYMC_MODE_CTR,     /*!<  Counter Mode */
    SYMC_MODE_CCM,     /*!<  Counter with Cipher Block Chaining-Message Authentication Code */
    SYMC_MODE_GCM,     /*!<  Galois/Counter Mode */
    SYMC_MODE_CTS,     /*!<  CTS Mode */
    SYMC_MODE_COUNT,
}symc_mode;

/*! \locational of buffer under symmetric cipher */
typedef enum
{
    SYMC_NODE_USAGE_NORMAL = 0x00,  /*!<  The normal buffer, don't update the iv */
    SYMC_NODE_USAGE_FIRST = 0x01,   /*!<  The first buffer, the usage of iv is expired */
    SYMC_NODE_USAGE_LAST  = 0x02,   /*!<  The last buffer, must update the iv */
    SYMC_NODE_USAGE_ODD_KEY = 0x40, /*!<  Use the odd key to encrypt/decrypt this buffer*/
    SYMC_NODE_USAGE_EVEN_KEY = 0x00,/*!<  Use the even key to encrypt/decrypt this buffer*/
    SYMC_NODE_USAGE_IN_GCM_A    = 0x00, /*!<  The buffer of GCM A */
    SYMC_NODE_USAGE_IN_GCM_P    = 0x08, /*!<  The buffer of GCM P */
    SYMC_NODE_USAGE_IN_GCM_LEN  = 0x10, /*!<  The buffer of GCM LEN */
    SYMC_NODE_USAGE_IN_CCM_N    = 0x00, /*!<  The buffer of CCM N */
    SYMC_NODE_USAGE_IN_CCM_A    = 0x08, /*!<  The buffer of CCM A */
    SYMC_NODE_USAGE_IN_CCM_P    = 0x10, /*!<  The buffer of CCM P */
    SYMC_NODE_USAGE_CCM_LAST    = 0x20, /*!<  The buffer of CCM LAST */
}symc_node_usage;

/*! \symc error code */
enum symc_error_code
{
    HI_SYMC_ERR_ALG_INVALID = HI_BASE_ERR_BASE_SYMC, /*!<  invalid algorithm */
    HI_SYMC_ERR_MODE_INVALID,       /*!<  invalid mode */
    HI_SYMC_ERR_LEN_INVALID,        /*!<  data length invalid */
    HI_SYMC_ERR_IV_LEN_INVALID,     /*!<  IV length invalid */
    HI_SYMC_ERR_TAG_LEN_INVALID,    /*!<  TAG length invalid */
    HI_SYMC_ERR_KEY_LEN_INVALID,    /*!<  key length invalid */
    HI_SYMC_ERR_KEY_INVALID,        /*!<  key invalid */
    HI_SYMC_ERR_ID_INVALID,         /*!<  channel id invalid */
    HI_SYMC_ERR_SMMU_INVALID,       /*!<  SMMU invalid */
    HI_SYMC_ERR_TIME_OUT,           /*!<  encrypt/decrypt timeout */
    HI_SYMC_ERR_BUSY,               /*!<  busy */
};

typedef struct
{
    u32 id;
    char *open;
    char *alg;
    char *mode;
    u32 klen;
    char *ksrc;
    u8 decrypt;
    u32 inlen;
    u32 inaddr;
    u32 outlen;
    u32 outaddr;
    u8 intswitch;
    u8 inten;
    u8 inraw;
    u8 outen;
    u8 outraw;
    u32 outintcnt;
    u8  iv[AES_IV_SIZE *2 + 1];
}symc_chn_status;

/*! \symc capacity, 0-nonsupport, 1-support */
typedef struct
{
    u32 aes_ecb     : 1 ;    /*!<  Support AES ECB  */
    u32 aes_cbc     : 1 ;    /*!<  Support AES CBC  */
    u32 aes_cfb     : 1 ;    /*!<  Support AES CFB  */
    u32 aes_ofb     : 1 ;    /*!<  Support AES OFB  */
    u32 aes_ctr     : 1 ;    /*!<  Support AES CTR  */
    u32 aes_ccm     : 1 ;    /*!<  Support AES CCM  */
    u32 aes_gcm     : 1 ;    /*!<  Support AES GCM  */
    u32 aes_cts     : 1 ;    /*!<  Support AES CTS  */
    u32 tdes_ecb    : 1 ;    /*!<  Support TDES ECB */
    u32 tdes_cbc    : 1 ;    /*!<  Support TDES CBC */
    u32 tdes_cfb    : 1 ;    /*!<  Support TDES CFB */
    u32 tdes_ofb    : 1 ;    /*!<  Support TDES OFB */
    u32 tdes_ctr    : 1 ;    /*!<  Support TDES CTR */
    u32 des_ecb     : 1 ;    /*!<  Support DES ECB */
    u32 des_cbc     : 1 ;    /*!<  Support DES CBC */
    u32 des_cfb     : 1 ;    /*!<  Support DES CFB */
    u32 des_ofb     : 1 ;    /*!<  Support DES OFB */
    u32 des_ctr     : 1 ;    /*!<  Support DES CTR */
    u32 sm1_ecb     : 1 ;    /*!<  Support SM1 ECB  */
    u32 sm1_cbc     : 1 ;    /*!<  Support SM1 CBC  */
    u32 sm1_cfb     : 1 ;    /*!<  Support SM1 CFB  */
    u32 sm1_ofb     : 1 ;    /*!<  Support SM1 OFB  */
    u32 sm1_ctr     : 1 ;    /*!<  Support SM1 CTR  */
    u32 sm4_ecb     : 1 ;    /*!<  Support SM4 ECB  */
    u32 sm4_cbc     : 1 ;    /*!<  Support SM4 CBC  */
    u32 sm4_cfb     : 1 ;    /*!<  Support SM4 CFB  */
    u32 sm4_ofb     : 1 ;    /*!<  Support SM4 OFB  */
    u32 sm4_ctr     : 1 ;    /*!<  Support SM4 CTR  */
    u32 dma         : 1 ;    /*!<  Support DMA  */
}symc_capacity;

typedef s32 (*callback_symc_isr)(void *ctx);

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      symc */
/** @{ */  /** <!--[symc]*/


/**
\brief  Initialize the symc module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_init(void);

/**
\brief  Deinitialize the symc module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_deinit(void);

/**
\brief  suspend the symc module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
void drv_symc_suspend(void);

/**
\brief  resume the symc module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_resume(void);

/**
\brief  allocate a hard symc channel.
\param[out]  chn_num The channel number.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_alloc_chn(u32 *chn_num);

/**
\brief  free a hard symc channel.
\param[in]  chn_num The channel number.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
void drv_symc_free_chn(u32 chn_num);

/**
\brief  set the iv to the symc module.
\param[in]  chn_num The channel number.
\retval     NA.
*/
s32 drv_symc_reset(u32 chn_num);

/**
\brief  check the length of nodes list.
\param[in]  alg The symmetric cipher algorithm.
\param[in]  mode The symmetric cipher mode.
\param[in]  block_size The block size.
\param[in]  input The MMZ/SMMU address of in buffer.
\param[in]  output The MMZ/SMMU address of out buffer.
\param[in]  length The MMZ/SMMU siae of in buffer.
\param[in]  klen The key length.
\param[in]  usage_list The usage of node.
\param[in]  pkg_num The numbers of node.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_node_check(symc_alg alg, symc_mode mode,
                    symc_klen klen, u32 block_size,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num);

/**
\brief  set work params.
\param[in]  chn_num The channel number.
\param[in]  alg The symmetric cipher algorithm.
\param[in]  mode The symmetric cipher mode.
\param[in]  decrypt Decrypt or encrypt.
\param[in]  sm1_round_num The round number of sm1.
\param[in]  klen The key length.
\param[in]  hard_key whether use the hard key or not.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_config(u32 chn_num, symc_alg alg, symc_mode mode, symc_width width, u32 decrypt,
                u32 sm1_round_num, symc_klen klen, u32 hard_key);

/**
\brief  set the iv to the symc module.
\param[in]  chn_num The channel number.
\param[in]  iv The IV data, hardware use the valid bytes according to the alg.
\param[in]  flag The IV flag, should be CIPHER_IV_CHANGE_ONE_PKG or CIPHER_IV_CHANGE_ALL_PKG.
\retval     NA.
*/
void drv_symc_set_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD], u32 ivlen, u32 flag);

/**
\brief  get the iv to the symc module.
\param[in]  chn_num The channel number.
\param[out] iv The IV data, the length is 16.
\retval     NA.
*/
void drv_symc_get_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD]);

/**
\brief  set the key to the symc module.
\param[in]  chn_num The channel number.
\param[in]  key The key data, hardware use the valid bytes according to the alg.
\param[in]  odd This id odd key or not .
\retval     NA.
*/
void drv_symc_set_key(u32 chn_num, u32 key[SYMC_KEY_MAX_SIZE_IN_WORD], u32 odd);

/**
\brief  set the sm1 sk to the symc module.
\param[in]  chn_num The channel number.
\param[in]  key The sk data, the length is 16.
\retval     NA.
*/
void drv_symc_set_sm1_sk(u32 chn_num, u32 key[SYMC_SM1_SK_SIZE_IN_WORD]);

/**
\brief  add a in buffer to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  buf_phy The MMZ/SMMU address of in buffer.
\param[in]  buf_size The MMZ/SMMU siae of in buffer.
\param[in]  local The locational of in buffer under a symmetric cipher.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_add_inbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage);

/**
\brief  add a out buffer to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  buf_phy The MMZ/SMMU address of out buffer.
\param[in]  buf_size The MMZ/SMMU siae of out buffer.
\param[in]  local The locational of in buffer under a symmetric cipher.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_add_outbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage);

/**
\brief  add a buffer usage to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  in in or out.
\param[in]  usage uasge.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
void drv_symc_add_buf_usage(u32 chn_num, u32 in, symc_node_usage usage);

/**
\brief  add N of CCM to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  n The buffer of n, the size is 16.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_aead_ccm_add_n(u32 chn_num, u8 *n);

/**
\brief  add A of CCM to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  buf_phy The MMZ/SMMU address of A.
\param[in]  buf_size The MMZ/SMMU size of A.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_aead_ccm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size);

/**
\brief  add A of GCM to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  buf_phy The MMZ/SMMU address of A.
\param[in]  buf_size The MMZ/SMMU size of A.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_aead_gcm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size);

/**
\brief  add length field of GCM to the nodes list.
\param[in]  chn_num The channel number.
\param[in]  buf_phy The MMZ/SMMU address of length field, the size is 16.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_aead_gcm_add_clen(u32 chn_num, u8 *clen);

/**
\brief  get ccm/gcm tag.
\param[in]   chn_num The channel number.
\param[out]  tag The tag value.
\retval     On received interception, HI_TRUE is returned  otherwise HI_FALSE is returned.
*/
s32 drv_aead_get_tag(u32 chn_num, u32 *tag);

/**
\brief  start symmetric cipher calculation.
\param[in]  chn_num The channel number.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_symc_start(u32 chn_num);

/**
\brief  wait running finished.
\param[in]  chn_num The channel number.
\retval     On received interception, HI_TRUE is returned  otherwise HI_FALSE is returned.
*/
s32 drv_symc_wait_done(u32 chn_num, u32 timeout);

/**
\brief  set isr callback function.
\param[in]  chn_num The channel number.
\retval     On finished, HI_TRUE is returned otherwise HI_FALSE is returned.
*/
s32 drv_symc_set_isr_callback(u32 chn_num, callback_symc_isr callback, void *ctx);

/**
\brief  proc status.
\param[in]  status The  proc status.
\retval     On received interception, HI_TRUE is returned  otherwise HI_FALSE is returned.
*/
s32 drv_symc_proc_status(symc_chn_status *status);

/**
\brief  get the symc capacity.
\param[out] capacity The symc capacity.
\retval     NA.
*/
void drv_symc_get_capacity(symc_capacity *capacity);

/** @} */  /** <!-- ==== API declaration end ==== */

#endif
