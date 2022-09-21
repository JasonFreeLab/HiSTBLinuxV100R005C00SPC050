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
#ifndef __CRYP_SM2_H_
#define __CRYP_SM2_H_

#include "drv_osal_lib.h"
#include "drv_sm2.h"

/******************************* API Declaration *****************************/
/** \addtogroup      sm2 */
/** @{ */  /** <!--[sm2]*/

#define SM2_TRY_CNT             8

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/


/**
* \brief          Initialize crypto of sm2 *
*/
s32 cryp_sm2_init(void);

/**
* \brief          Deinitialize crypto of sm2 *
*/
void cryp_sm2_deinit(void);

/**
\brief SM2 encryption a plaintext with a SM2 key
\      Compute C1(x, y) = k * G(x, y), XY = k * P(x, y)
*/
typedef s32 (*func_sm2_encrypt)(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                     u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD]);

/**
\brief SM2 decryption a plaintext with a SM2 key.
\      Compute XY(x, y) = C1(x, y) * d
*/
typedef s32 (*func_sm2_decrypt)(u32 d[SM2_LEN_IN_WROD],
                     u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                     u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD]);

/**
\brief SM2 sign a sm3 value with a SM2 private key.
\  1. generate a randnum k, k within [1,n-1],
\  2. (x1,y1)=[k]G,
\  3. r=(e+x1)mod n, if r=0 or r+k=n, return step 1
\  4. s=((1+dA)^-1 * (k-rdA))mod n
*/
typedef s32 (*func_sm2_sign)(u32 e[SM2_LEN_IN_WROD], u32 d[SM2_LEN_IN_WROD],
                  u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);

/**
\brief SM2 verify a sm3 value with a SM2 public key.
\  1. t=(r+s)mod n, if t==0, return fail
\  2. (x1,y1)=[s]G+tP,
\  3. r=(e+x1)mod n, if r==R, return pass
*/
typedef s32 (*func_sm2_verify)(u32 e[SM2_LEN_IN_WROD],
                    u32 px[SM2_LEN_IN_WROD],u32 py[SM2_LEN_IN_WROD],
                    u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);

/**
\brief Generate a SM2 private key.
\      Compute P(x,y) = d * G(x,y)
*/
typedef s32 (*func_sm2_gen_key)(u32 d[SM2_LEN_IN_WROD],
                          u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD]);

/**
* \brief          get randnum for sm2 *
*/
s32 cryp_sm2_get_randnum(u32 randnum[SM2_LEN_IN_WROD], const u32 max[SM2_LEN_IN_WROD]);

/*! \struct of SM2 function template */
typedef struct
{
    func_sm2_encrypt encrypt;
    func_sm2_decrypt decrypt;
    func_sm2_sign  sign;
    func_sm2_verify verify;
    func_sm2_gen_key  genkey;
}sm2_func;

/**
\brief  Clone the function from template of sm2 engine.
\retval     On success, func is returned.  On error, HI_NULL is returned.
*/
sm2_func * cryp_get_sm2_op(void);

/** @} */  /** <!-- ==== API declaration end ==== */
#endif
