/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ree_mpi_cipher.h
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef __REE_MPI_CIPHER_H__
#define __REE_MPI_CIPHER_H__

#include "cipher_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

HI_S32 Cipher_HashMmzInit(HI_VOID);

HI_VOID Cipher_HashMmzDeInit(HI_VOID);

HI_S32 AES_Encrypt(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output);

HI_S32 RSA_Private(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey, HI_U8 *pu8In, HI_U8 *pu8Out);

HI_S32 RSA_Public(HI_UNF_CIPHER_RSA_PUB_KEY_S *pstPubKey, HI_U8 *pu8In, HI_U8 *pu8Out);

HI_S32 Mbedtls_GetRandomNumber(HI_VOID *param, HI_U8 *pu8Rand, size_t u32Size);

#ifdef __cplusplus
#if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_MPI_CIPHER_H__ */

