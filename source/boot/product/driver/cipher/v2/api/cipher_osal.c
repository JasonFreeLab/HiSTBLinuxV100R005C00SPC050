/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_osal.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/

#include "cipher_osal.h"

HI_S32 CIPHER_Maloc(cipher_mmz_buf_t *pstMem, HI_CHAR *name)
{
    pstMem->szStartPhyAddr = (HI_SIZE_T)devmemalign(16, pstMem->u32Size);
    if (0 == pstMem->szStartPhyAddr)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        return HI_FAILURE;
    }
    pstMem->pu8StartVirAddr = (HI_U8*)pstMem->szStartPhyAddr;

    return HI_SUCCESS;
}

HI_S32 CIPHER_Free(cipher_mmz_buf_t *pstMem)
{
    if (pstMem->szStartPhyAddr > 0)
    {
        free(pstMem->pu8StartVirAddr);
        pstMem->szStartPhyAddr = 0;
        pstMem->pu8StartVirAddr = NULL;
    }

    return HI_SUCCESS;
}

