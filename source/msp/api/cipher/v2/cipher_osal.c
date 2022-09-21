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
    pstMem->szStartPhyAddr = (HI_SIZE_T)HI_MMZ_New(pstMem->u32Size, 0, NULL, name);
    if (0 == pstMem->szStartPhyAddr)
    {
        HI_ERR_CIPHER("Error: Get phyaddrfailed!\n");
        return HI_FAILURE;
    }
    
    pstMem->pu8StartVirAddr = HI_MMZ_Map(pstMem->szStartPhyAddr, 0);
    if (pstMem->pu8StartVirAddr == HI_NULL)
    {
        HI_MMZ_Delete(pstMem->szStartPhyAddr);
        HI_ERR_CIPHER("Error: map phyaddr failed!\n");
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 CIPHER_Free(cipher_mmz_buf_t *pstMem)
{
    if (pstMem->szStartPhyAddr > 0)
    {
        (HI_VOID)HI_MMZ_Unmap(pstMem->szStartPhyAddr);
        HI_MMZ_Delete(pstMem->szStartPhyAddr);
        pstMem->szStartPhyAddr = 0;
    }

    return HI_SUCCESS;
}

void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len)
{
    if (dstlen < len)
    {
        HI_ERR_CIPHER("cipher_memcpy_s dstlen %d < len %d\n", dstlen, len);
    }
    
    return memcpy(dst, src, MIN(dstlen, len));
}

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len)
{    
    if (dlen < len)
    {
        HI_ERR_CIPHER("cipher_memset_s dlen %d < len %d\n", dlen, len);
    }

    return memset(dst, val, MIN(dlen, len));   
}

int cipher_memcmp_s(const void *a, const void *b, unsigned int len)
{
    if (a == b)
    {
        return -1;
    }

    return memcmp(a, b, len);
}

static void HEX2STR(char buf[2], HI_U8 val)
{
    HI_U8 high, low;

    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;
    
    if(high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }

    if(low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }
    
}

void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size)
{ 
    HI_U32 i;
    char buf[2];

    if (pbName != HI_NULL)
    {
        HI_PRINT("[%s-%p]:\n", pbName, pbData);
    }
    for (i=0; i<u32Size; i++)
    {
        HEX2STR(buf, pbData[i]);
        HI_PRINT("%c%c ", buf[0], buf[1]);
        if(((i+1) % 16) == 0)
            HI_PRINT("\n");  
    }
    if (( i % 16) != 0)
    {
        HI_PRINT("\n");
    }
}

