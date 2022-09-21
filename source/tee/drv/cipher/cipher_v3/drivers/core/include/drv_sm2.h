/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_SM2_H__
#define __DRV_SM2_H__

/*************************** Structure Definition ****************************/
/** \addtogroup     sm2 */
/** @{ */  /** <!-- [sm2] */

/*! \sm2 capacity, 0-nonsupport, 1-support */
typedef struct
{
    u32 sm2         : 1 ;    /*!<  Support SM2 */
}sm2_capacity;

/*! \sm2 error code */
enum sm2_error_code
{
    HI_SM2_ERR_KEY_LEN = HI_BASE_ERR_BASE_SM2, /*!<  key length invalid */
    HI_SM2_ERR_INPUT_LEN_INVALID,  /*!<  input length invalid */
    HI_SM2_ERR_DECRYPT_FAILED,     /*!<  decrypt failed */
    HI_SM2_ERR_VERIFY_FAILED,      /*!<  verify failed */
    HI_SM2_ERR_BUSY,               /*!<  busy */
    HI_SM2_ERR_COPY_FROM_USER,     /*!<  copy from user failed */
    HI_SM2_ERR_CRT_NONSUPPORT,     /*!<  CRT nonsupport */
    HI_SM2_ERR_HARD_ERR,           /*!<  hardware error */
    HI_SM2_ERR_TIME_OUT,           /*!<  timeout */
};

/*! Define the constant value */
extern const u32 sm2p[SM2_LEN_IN_WROD];
extern const u32 sm2a[SM2_LEN_IN_WROD];
extern const u32 sm2b[SM2_LEN_IN_WROD];
extern const u32 sm2n[SM2_LEN_IN_WROD];
extern const u32 sm2n1[SM2_LEN_IN_WROD];
extern const u32 sm2n2[SM2_LEN_IN_WROD];
extern const u32 sm2Gx[SM2_LEN_IN_WROD];
extern const u32 sm2Gy[SM2_LEN_IN_WROD];
extern const u32 sm2P[SM2_LEN_IN_WROD];
extern const u32 sm2wp[SM2_LEN_IN_WROD];
extern const u32 sm2N[SM2_LEN_IN_WROD];
extern const u32 sm2wn[SM2_LEN_IN_WROD];
extern const u32 sm21[SM2_LEN_IN_WROD];
extern const u32 sm20[SM2_LEN_IN_WROD];
extern const u32 sm2ma[SM2_LEN_IN_WROD];
extern const u32 sm2mb[SM2_LEN_IN_WROD];
extern const u32 sm2m1[SM2_LEN_IN_WROD];

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      sm2 */
/** @{ */  /** <!--[sm2]*/


/**
\brief  Initialize the sm2 module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_sm2_init(void);

/**
\brief  Deinitialize the sm2 module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_sm2_deinit(void);

/**
\brief  enable the sm2 module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_sm2_resume(void);

/**
\brief  disable the sm2 module.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_sm2_suspend(void);

/* c = a + b mod p */
s32 drv_sm2_add_mod(const u32 a[SM2_LEN_IN_WROD],
                      const u32 b[SM2_LEN_IN_WROD],
                      const u32 p[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD]);

/* c = a - b mod p */
s32 drv_sm2_sub_mod(const u32 a[SM2_LEN_IN_WROD],
                      const u32 b[SM2_LEN_IN_WROD],
                      const u32 p[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD]);

/* c = a * b mod p */
s32 drv_sm2_mul_modp(const u32 a[SM2_LEN_IN_WROD],
                      const u32 b[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD],
                      u32 private);

/* c = a * b mod n */
s32 drv_sm2_mul_modn(const u32 a[SM2_LEN_IN_WROD],
                      const u32 b[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD],
                      u32 private);

/* c = a^-1 mod p */
s32 drv_sm2_inv_mod(const u32 a[SM2_LEN_IN_WROD],
                      const u32 p[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD]);

/* c = a mod p */
s32 drv_sm2_mod(const u32 a[SM2_LEN_IN_WROD],
                      const u32 p[SM2_LEN_IN_WROD],
                      u32 c[SM2_LEN_IN_WROD]);

/* c = a * b */
s32 drv_sm2_mul( const u32 a[SM2_LEN_IN_WROD],
                    const u32 b[SM2_LEN_IN_WROD],
                    u32 c[SM2_LEN_IN_WROD*2]);

/* R = k . P(x,y) */
s32 drv_sm2_mul_dot( const u32 k[SM2_LEN_IN_WROD],
                    const u32 px[SM2_LEN_IN_WROD],
                    const u32 py[SM2_LEN_IN_WROD],
                    u32 rx[SM2_LEN_IN_WROD],
                    u32 ry[SM2_LEN_IN_WROD],
                    u32 private);

/* C = S(x,y) + R(x,y) */
s32 drv_sm2_add_dot( const u32 sx[SM2_LEN_IN_WROD],
                    const u32 sy[SM2_LEN_IN_WROD],
                    const u32 rx[SM2_LEN_IN_WROD],
                    const u32 ry[SM2_LEN_IN_WROD],
                    u32 cx[SM2_LEN_IN_WROD],
                    u32 cy[SM2_LEN_IN_WROD]);

/**
\brief  clean sm2 ram .
*/
s32 drv_sm2_clean_ram(void);

/**
\brief  get the sm2 capacity.
\param[out] capacity The hash capacity.
\retval     NA.
*/
void drv_sm2_get_capacity(sm2_capacity *capacity);

/** @} */  /** <!-- ==== API declaration end ==== */

#endif
