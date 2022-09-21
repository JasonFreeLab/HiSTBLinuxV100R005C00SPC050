/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : external.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "sha256.h"
#include "cipher_osal.h"

HI_VOID *s_u32RngBase;
HI_VOID *s_u32SicRsaBase;

int prng_init(void)
{
    HI_SYS_MapRegister(TRNG_BASE, 0x100, &s_u32RngBase);

    return 0;
}

int prng_get_random_bytes(unsigned char * buff, unsigned int len)
{
    HI_U32 i;
    HI_U32 u32Rand;

    for(i=0; i<len; i+=4)
    {
        u32Rand = *((volatile unsigned int *) (s_u32RngBase + 0x04)) ;
        memcpy(buff+i, &u32Rand, (len - i > 4) ? 4 : (len - i));
    }

    return 0;
}

unsigned long get_copro_base_address( void )
{
    HI_SYS_MapRegister(COPRO_BASE, 0x4000, &s_u32SicRsaBase);

    return (unsigned long)s_u32SicRsaBase;
}

void sha256_init(SHA256_CTX *ctx)
{
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE hHandle = 0;

    memset(&stHashAttr, 0, sizeof(stHashAttr));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    (HI_VOID)HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);

    ctx->datalen = hHandle;

}

void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len)
{
    HI_HANDLE hHandle;

    hHandle = ctx->datalen;

    (HI_VOID)HI_UNF_CIPHER_HashUpdate(hHandle, (HI_U8*)data, len);

}

void sha256_final(SHA256_CTX *ctx, BYTE hash[])
{
    HI_HANDLE hHandle;

    hHandle = ctx->datalen;

    (HI_VOID)HI_UNF_CIPHER_HashFinal(hHandle, hash);

}


