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
    HI_U32 u32ptaddr;
    HI_U32 u32err_rdaddr;
    HI_U32 u32err_wraddr;

    HI_DRV_SMMU_GetPageTableAddr(&u32ptaddr, &u32err_rdaddr, &u32err_wraddr);

    return u32ptaddr;
}

HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz)
{
#ifdef SMMU_ENABLE
    HI_S32 ret = HI_SUCCESS;
    SMMU_BUFFER_S stSmmuBuf;

    ret = HI_DRV_SMMU_AllocAndMap(name, pstMmz->u32Size, 16, &stSmmuBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_DRV_SMMU_AllocAndMap failed. ret = 0x%x\n", ret);
        return HI_FAILURE;
    }

    pstMmz->u32StartPhyAddr = stSmmuBuf.u32StartSmmuAddr;
    pstMmz->pu8StartVirAddr = stSmmuBuf.pu8StartVirAddr;

    return HI_SUCCESS;
#else
    HI_S32 ret = HI_SUCCESS;
    MMZ_BUFFER_S stMmzBuf;

    ret = HI_DRV_MMZ_AllocAndMap(name, MMZ_OTHERS, pstMmz->u32Size, 16, &stMmzBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("DRV_TEE_MMZ_Alloc failed. ret = 0x%x\n", ret);
        return HI_FAILURE;
    }

    pstMmz->u32StartPhyAddr = stMmzBuf.u32StartPhyAddr;
    pstMmz->pu8StartVirAddr = stMmzBuf.pu8StartVirAddr;

    return HI_SUCCESS;
#endif
}

HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz)
{
#ifdef SMMU_ENABLE
    SMMU_BUFFER_S stSmmuBuf;

    stSmmuBuf.u32StartSmmuAddr= pstMmz->u32StartPhyAddr;
    stSmmuBuf.pu8StartVirAddr = pstMmz->pu8StartVirAddr;
    stSmmuBuf.u32Size = pstMmz->u32Size;
    (HI_VOID)HI_DRV_SMMU_Unmap(&stSmmuBuf);
    (HI_VOID)HI_DRV_SMMU_Release(&stSmmuBuf);
#else
    MMZ_BUFFER_S stMmzBuf;

    stMmzBuf.u32StartPhyAddr = pstMmz->u32StartPhyAddr;
    stMmzBuf.pu8StartVirAddr = pstMmz->pu8StartVirAddr;
    stMmzBuf.u32Size = pstMmz->u32Size;
    (HI_VOID)HI_DRV_MMZ_Unmap(&stMmzBuf);
    (HI_VOID)HI_DRV_MMZ_Release(&stMmzBuf);
#endif
}

HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz)
{
#ifdef SMMU_ENABLE
    HI_S32 ret = HI_SUCCESS;
    SMMU_BUFFER_S stSmmuBuf;

    stSmmuBuf.u32StartSmmuAddr= pstMmz->u32StartPhyAddr;
    stSmmuBuf.u32Size = pstMmz->u32Size;
    ret = HI_DRV_SMMU_Map(&stSmmuBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("DRV_TEE_SMMU_MapCpu failed. ret = 0x%x\n", ret);
        return HI_NULL;
    }

    pstMmz->pu8StartVirAddr = stSmmuBuf.pu8StartVirAddr;

    return HI_SUCCESS;
#else
    HI_S32 ret = HI_SUCCESS;
    MMZ_BUFFER_S stMmzBuf;

    stMmzBuf.u32StartPhyAddr = pstMmz->u32StartPhyAddr;
    stMmzBuf.u32Size = pstMmz->u32Size;
    ret = HI_DRV_MMZ_Map(&stMmzBuf);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("DRV_TEE_SMMU_MapCpu failed. ret = 0x%x\n", ret);
        return HI_NULL;
    }

    pstMmz->pu8StartVirAddr = stMmzBuf.pu8StartVirAddr;

    return HI_SUCCESS;
#endif

}

HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz)
{
#ifdef SMMU_ENABLE
    SMMU_BUFFER_S stSmmuBuf;

    stSmmuBuf.u32StartSmmuAddr= pstMmz->u32StartPhyAddr;
    stSmmuBuf.pu8StartVirAddr = pstMmz->pu8StartVirAddr;
    stSmmuBuf.u32Size = pstMmz->u32Size;
    (HI_VOID)HI_DRV_SMMU_Unmap(&stSmmuBuf);
#else
    MMZ_BUFFER_S stMmzBuf;

    stMmzBuf.u32StartPhyAddr = pstMmz->u32StartPhyAddr;
    stMmzBuf.pu8StartVirAddr = pstMmz->pu8StartVirAddr;
    stMmzBuf.u32Size = pstMmz->u32Size;
    (HI_VOID)HI_DRV_MMZ_Unmap(&stMmzBuf);
#endif
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

void HEX2STR(char buf[2], HI_U8 val)
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

