/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : spacc_intf.h
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef _SPACC_INTF_H_
#define _SPACC_INTF_H_

HI_S32 DRV_CIPHER_Init(HI_VOID);

HI_VOID DRV_CIPHER_DeInit(HI_VOID);

HI_S32 Cipher_HashMmzInit(HI_VOID);

HI_VOID Cipher_HashMmzDeInit(HI_VOID);

HI_S32 CIPHER_HashInit(HI_TEE_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);

HI_S32 CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);

HI_S32 CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);

HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);

HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
#endif

