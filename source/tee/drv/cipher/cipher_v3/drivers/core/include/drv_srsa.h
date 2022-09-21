/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_srsa.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_RSA_H__
#define __DRV_RSA_H__

/*************************** Structure Definition ****************************/
/** \addtogroup     rsa */
/** @{ */  /** <!-- [rsa] */

/*! Define RSA 1024 key length */
#define RSA_KEY_LEN_1024             128

/*! Define RSA 1024 key length */
#define RSA_KEY_LEN_2048             256

/*! Define RSA 1024 key length */
#define RSA_KEY_LEN_3072             384

/*! Define RSA 1024 key length */
#define RSA_KEY_LEN_4096             512

/*! \rsa capacity, 0-nonsupport, 1-support */
typedef struct
{
    u32 rsa         : 1 ;    /*!<  Support RSA */
}rsa_capacity;

/*! \rsa key width */
typedef enum
{
    RSA_KEY_WIDTH_1024 = 0x00, /*!<  RSA 1024  */
    RSA_KEY_WIDTH_2048,        /*!<  RSA 2048  */
    RSA_KEY_WIDTH_4096,        /*!<  RSA 4096  */
    RSA_KEY_WIDTH_3072,        /*!<  RSA 3072  */
    RSA_KEY_WIDTH_COUNT,
}rsa_key_width;

/*! \rsa error code */
enum rsa_error_code
{
    HI_RSA_ERR_KEY_LEN = HI_BASE_ERR_BASE_RSA, /*!<  key length invalid */
    HI_RSA_ERR_INPUT_LEN_INVALID,  /*!<  input length invalid */
    HI_RSA_ERR_HEAD_INVALID,       /*!<  head invalid */
    HI_RSA_ERR_SCHEME_INVALID,     /*!<  scheme invalid */
    HI_RSA_ERR_DECRYPT_FAILED,     /*!<  decrypt failed */
    HI_RSA_ERR_VERIFY_FAILED,      /*!<  verify failed */
    HI_RSA_ERR_INPUT_ZERO,         /*!<  input data is zero */
    HI_RSA_ERR_KEY_ZERO,           /*!<  Key is zero */
    HI_RSA_ERR_INPUT_TOO_LARGER,   /*!<  input data too larger */
    HI_RSA_ERR_BUSY,               /*!<  busy */
    HI_RSA_ERR_COPY_FROM_USER,     /*!<  copy from user failed */
    HI_RSA_ERR_CRT_NONSUPPORT,     /*!<  CRT nonsupport */
    HI_RSA_ERR_HARD_ERR,           /*!<  hardware error */
    HI_RSA_ERR_TIME_OUT,           /*!<  timeout */
};

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      rsa */
/** @{ */  /** <!--[rsa]*/


/**
\brief  Initialize the rsa module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_rsa_init(void);

/**
\brief  Deinitialize the rsa module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_rsa_deinit(void);

/**
\brief  RSA encrypt/decrypt use rsa exponent-modular arithmetic.
\param[in]  n The N of rsa key.
\param[in]  k The d/e of rsa key.
\param[in]  in The input data.
\param[out] out The input data.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_ifep_rsa_exp_mod(u8 *n, u8 *k, u8 *in, u8 *out, rsa_key_width width);

/**
\brief  get the hash capacity.
\param[out] capacity The hash capacity.
\retval     NA.
*/
void drv_ifep_rsa_get_capacity(rsa_capacity *capacity);

/**
\brief  get the hash capacity.
\param[out] capacity The hash capacity.
\retval     NA.
*/
void drv_sic_rsa_get_capacity(rsa_capacity *capacity);

/** @} */  /** <!-- ==== API declaration end ==== */

#endif
