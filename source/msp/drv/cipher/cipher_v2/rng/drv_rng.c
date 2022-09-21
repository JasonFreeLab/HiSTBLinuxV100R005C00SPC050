/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_rng.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <linux/random.h>
#include "cipher_adapt.h"

#define  REG_RNG_BASE_ADDR                   g_u32RngRegBase
#define  HISEC_COM_TRNG_CTRL                 (REG_RNG_BASE_ADDR + 0x200)
#define  HISEC_COM_TRNG_FIFO_DATA            (REG_RNG_BASE_ADDR + 0x204)
#define  HISEC_COM_TRNG_DATA_ST              (REG_RNG_BASE_ADDR + 0x208)

HI_VOID *g_u32RngRegBase;

HI_S32 DRV_RNG_Init(HI_VOID)
{
    g_u32RngRegBase = cipher_ioremap_nocache(CIPHER_RNG_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32RngRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache sha2 Reg failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID DRV_RNG_DeInit(HI_VOID)
{
    cipher_iounmap(g_u32RngRegBase);
}

HI_S32 DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
#ifdef REE_NONSECURE_ENABLE
    get_random_bytes(&pstRNG->u32RNG, 4);
    return HI_SUCCESS;
#else
    HI_U32 u32RngStat = 0;
    HI_U32 u32TimeOut = 0;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(0 == pstRNG->u32TimeOutUs)
    {
        /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
        HAL_CIPHER_ReadReg(HISEC_COM_TRNG_DATA_ST, &u32RngStat);
        if(((u32RngStat >> 8) & 0x3F) <= 0)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }
    else
    {
        while(u32TimeOut ++ < pstRNG->u32TimeOutUs)
        {
            /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
            HAL_CIPHER_ReadReg(HISEC_COM_TRNG_DATA_ST, &u32RngStat);
            if(((u32RngStat >> 8) & 0x3F) > 0)
            {
                break;
            }
        }
        if (u32TimeOut >= pstRNG->u32TimeOutUs)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }

    HAL_CIPHER_ReadReg(HISEC_COM_TRNG_FIFO_DATA, &pstRNG->u32RNG);
 //   HI_PRINT("RNG: 0x%x\n", pstRNG->u32RNG);

    return HI_SUCCESS;
 #endif
}

HI_U32 DRV_CIPHER_Rand(HI_VOID)
{
    CIPHER_RNG_S stRNG;

    stRNG.u32TimeOutUs = - 1;
    DRV_CIPHER_GetRandomNumber(&stRNG);

    return stRNG.u32RNG;

 //   return prandom_u32();
}

HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_S32 ret = HI_SUCCESS;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    ret = DRV_CIPHER_GetRandomNumber(pstRNG);

    return ret;
}

