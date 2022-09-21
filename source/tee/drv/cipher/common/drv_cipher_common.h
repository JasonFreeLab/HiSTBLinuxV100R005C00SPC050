/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_cipher_common.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __TEE_DRV_CIPHER_COMMON_H_
#define __TEE_DRV_CIPHER_COMMON_H_

typedef struct
{
    HI_VOID *pu8StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32ecMmzAddr;
    HI_U32 u32Size;
}cipher_mmz_buf_t;

HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz);
HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz);

HI_S32 Cipher_AESCBCCTS(HI_HANDLE hCipherHandle,
                                HI_U32 u32SrcPhyAddr,
                                HI_U32 u32DestPhyAddr,
                                HI_U32 u32ByteLength,
                                HI_BOOL bIsDecrypt);

HI_S32 Cipher_Test(HI_U32 u32Cmd, HI_VOID *pu8Param, HI_U32 u32Size);
#endif

