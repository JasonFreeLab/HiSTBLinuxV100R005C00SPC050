/***********************************************************************************
*              Copyright 2004 - 2017, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  hi_mpi_plcipher.h
* Description:  Define function implement.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20161012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __HI_MPI_PLCIPHER_H__
#define __HI_MPI_PLCIPHER_H__

#include "hi_unf_payloadcipher.h"
#include "hi_common.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/** MAX PID*/
/** CNcomment: ×î´óPIDÖµ*/
#define PLCIPHER_MAX_PID                    0x1FFF

HI_S32 HI_MPI_PLCIPHER_Init(HI_VOID);
HI_S32 HI_MPI_PLCIPHER_DeInit(HI_VOID);
HI_S32 HI_MPI_PLCIPHER_Create(HI_HANDLE* phPLCipher);
HI_S32 HI_MPI_PLCIPHER_Destroy(HI_HANDLE hPLCipher);
HI_S32 HI_MPI_PLCIPHER_GetAttr(HI_HANDLE hPLCipher,HI_UNF_PLCIPHER_ATTR_S* pstAttr);
HI_S32 HI_MPI_PLCIPHER_SetAttr(HI_HANDLE hPLCipher,HI_UNF_PLCIPHER_ATTR_S* pstAttr);
HI_S32 HI_MPI_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, const HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enIVEvenOdd,const HI_U8 *pu8IV, HI_U32 u32IVLen);
HI_S32 HI_MPI_PLCIPHER_Encrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length);
HI_S32 HI_MPI_PLCIPHER_Decrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_MPI_PLCIPHER_H__ */

