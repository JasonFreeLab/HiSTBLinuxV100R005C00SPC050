/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_adapt.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"

HI_U32  cipher_mmu_table_addr(HI_VOID)
{
    return 0;
}

HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz)
{
    pstMmz->u32StartPhyAddr = (HI_SIZE_T)devmemalign(16, pstMmz->u32Size);
    if (0 == pstMmz->u32StartPhyAddr)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        return HI_FAILURE;
    }
    pstMmz->pu8StartVirAddr = (HI_U8*)pstMmz->u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz)
{
    if (pstMmz->u32StartPhyAddr > 0)
    {
        free(pstMmz->pu8StartVirAddr);
        pstMmz->u32StartPhyAddr = 0;
        pstMmz->pu8StartVirAddr = NULL;
    }
}

HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz)
{
    pstMmz->pu8StartVirAddr = (HI_U8*)pstMmz->u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz)
{

}

/************************* SYSTEM API ************************/
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len)
{
    if (dstlen < len)
    {
        return NULL;
    }

    return memcpy(dst, src, len);
}

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len)
{

    if (dlen < len)
    {
        return NULL;
    }

    return memset(dst, val, len);
}

int cipher_memcmp_s(const void *a, const void *b, unsigned int len)
{
    if (a == b)
    {
        return HI_FAILURE;
    }

    return memcmp(a, b, len);
}

void HEX2STR(HI_U8 buf[2], HI_U8 val)
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
    HI_U8 buf[2];

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

