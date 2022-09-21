/***********************************************************************************
*              Copyright 2004 - 2017, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  unf_payloadcipher.c
* Description:  Define function implement.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20161012    NA                 NULL      Create this file.
***********************************************************************************/

#include "hi_mpi_plcipher.h"

HI_S32 HI_UNF_PLCIPHER_Init(HI_VOID)
{
    return HI_MPI_PLCIPHER_Init();
}

HI_S32 HI_UNF_PLCIPHER_DeInit(HI_VOID)
{
    return HI_MPI_PLCIPHER_DeInit();
}

HI_S32 HI_UNF_PLCIPHER_Create(HI_HANDLE* phPLCipher)
{
    return HI_MPI_PLCIPHER_Create(phPLCipher);
}

HI_S32 HI_UNF_PLCIPHER_Destroy(HI_HANDLE hPLCipher)
{
    return HI_MPI_PLCIPHER_Destroy(hPLCipher);
}

HI_S32 HI_UNF_PLCIPHER_GetAttr(HI_HANDLE hPLCipher,HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    return HI_MPI_PLCIPHER_GetAttr(hPLCipher, pstAttr);
}

HI_S32 HI_UNF_PLCIPHER_SetAttr(HI_HANDLE hPLCipher,HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    return HI_MPI_PLCIPHER_SetAttr(hPLCipher, pstAttr);
}

HI_S32 HI_UNF_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, const HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    return HI_MPI_PLCIPHER_SetKey( hPLCipher, enKeyEvenOdd, pu8Key, u32KeyLen);
}

HI_S32 HI_UNF_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enIVEvenOdd,const HI_U8 *pu8IV, HI_U32 u32IVLen)
{
    return HI_MPI_PLCIPHER_SetIV( hPLCipher, enIVEvenOdd, pu8IV, u32IVLen);
}


HI_S32 HI_UNF_PLCIPHER_Encrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length)
{
    return HI_MPI_PLCIPHER_Encrypt(hPLCipher, pSrcBuf, pDestBuf, u32Length);
}

