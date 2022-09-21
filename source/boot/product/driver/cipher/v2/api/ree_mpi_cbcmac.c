/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_cbcmac.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

#define CIPHER_MIN_CRYPT_LEN      8
#define CIPHER_MAX_CRYPT_LEN      0xfffff

#define AES_BLOCK_SIZE              (16)

/*********************************************************
 * The function below is added for AES CBC-MAC
 *
 *********************************************************/
#define MAX_DATA_LEN    (0x2000) //the max data length for encryption / decryption is  8k one time

/* For CMAC Calculation */

static const HI_U8 const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* Basic Functions */
static HI_VOID xor_128(const HI_U8 *a, const HI_U8 *b, HI_U8 *out)
{
    HI_U32 i;

    for (i = 0; i < 16; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

/* AES-CMAC Generation Function */
static HI_VOID leftshift_onebit(HI_U8 *input, HI_U8 *output)
{
    HI_S32 i;
    HI_U8 overflow = 0;

    for ( i = 15; i >= 0; i-- )
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
}

//the output is the last 16 bytes only
HI_S32 AES_Encrypt(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32EncryptDataLen = 0;
    HI_U32 u32LeftDataLen = 0;
    HI_U32 i = 0;
    HI_U32 u32BlockNum = 0;
    cipher_mmz_buf_t stMem;
    HI_S32 ret = HI_FAILURE;

    stMem.u32Size = MAX_DATA_LEN;
    ret = CIPHER_Maloc(&stMem, "CIPHER_BufIn");
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("mmz map for pu8InputAddrVir failed!\n");
        return HI_FAILURE;
    }

    cipher_memset_s(stMem.pu8StartVirAddr, MAX_DATA_LEN, 0, MAX_DATA_LEN);

    u32LeftDataLen = datalen;
    u32BlockNum = (datalen + MAX_DATA_LEN - 1) / MAX_DATA_LEN;
    for(i = 0; i < u32BlockNum; i++)
    {
        u32EncryptDataLen = u32LeftDataLen >= MAX_DATA_LEN ? MAX_DATA_LEN : u32LeftDataLen;
        u32LeftDataLen -= u32EncryptDataLen;
        cipher_memcpy_s(stMem.pu8StartVirAddr, MAX_DATA_LEN, input + i * MAX_DATA_LEN, u32EncryptDataLen);
        Ret = HI_MPI_CIPHER_Encrypt(hCipherHandle, stMem.szStartPhyAddr, stMem.szStartPhyAddr, u32EncryptDataLen);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Cipher encrypt failed!\n");
            goto CIPHER_RELEASE_BUF;
        }
    }
    cipher_memcpy_s(output, 16, stMem.pu8StartVirAddr + u32EncryptDataLen - 16, 16);

CIPHER_RELEASE_BUF:
    CIPHER_Free(&stMem);

    return Ret;
}

static HI_S32 generate_subkey(HI_HANDLE hCipherHandle, HI_U8 *K1, HI_U8 *K2)
{
    HI_U8 L[16];
    HI_U8 Z[16];
    HI_U8 tmp[16];
    HI_U32 u32DataLen = 16;
    HI_S32 Ret = HI_SUCCESS;

    cipher_memset_s(tmp, sizeof(tmp), 0x0, sizeof(tmp));
    cipher_memset_s(L, sizeof(L), 0x0, sizeof(L));
    cipher_memset_s(Z, sizeof(Z), 0x0, sizeof(Z));

    Ret = AES_Encrypt(hCipherHandle, Z, u32DataLen, L);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }

    if ( (L[0] & 0x80) == 0 ) /* If MSB(L) = 0, then K1 = L << 1 */
    {
        leftshift_onebit(L, K1);
    }
    else  /* Else K1 = ( L << 1 ) (+) Rb */
    {
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }

    if ( (K1[0] & 0x80) == 0 )
    {
        leftshift_onebit(K1,K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }

    return HI_SUCCESS;
}

static HI_VOID padding ( HI_U8 *lastb, HI_U8 *pad, HI_U32 length )
{
    HI_U32 j;

    /* original last block */
    for ( j = 0; j < 16; j++ )
    {
        if ( j < length )
        {
            pad[j] = lastb[j];
        }
        else if ( j == length )
        {
            pad[j] = 0x80;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

/**********************************************************
*                        AES_CBCMAC                       *
***********************************************************/
HI_S32 HI_MPI_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData,
                             HI_U32 u32InputDataLen, HI_U8 *pOutputMAC,
                             HI_BOOL bIsLastBlock)
{
    HI_U8 X[16], M_last[16], padded[16];
    static HI_U8 K1[16] = {0};
    static HI_U8 K2[16] = {0};
    HI_U32 n, i, flag;
    HI_U8 u8TmpBuf[16];
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    static HI_BOOL bIsFirstBlock = HI_TRUE;

    INLET_PARAM_CHECK_POINT_NULL(pOutputMAC);
    INLET_PARAM_CHECK_POINT_NULL(pInputData);

    cipher_memset_s(&stCipherCtrl, sizeof(stCipherCtrl), 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    cipher_memset_s(u8TmpBuf, sizeof(u8TmpBuf), 0, sizeof(u8TmpBuf));
    cipher_memset_s(X, sizeof(X), 0, sizeof(X));
    cipher_memset_s(M_last, sizeof(M_last), 0, sizeof(M_last));
    cipher_memset_s(padded, sizeof(padded), 0, sizeof(padded));

    if(bIsFirstBlock) //if first block, reset the configure handle and generate the subkey again
    {
        Ret = HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, &stCipherCtrl);
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        cipher_memset_s ((HI_U8*)stCipherCtrl.u32IV, sizeof(stCipherCtrl.u32IV), 0, 16);
        Ret |= HI_MPI_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        Ret = generate_subkey(hCipherHandle, K1, K2);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        //After genreate the subkey, reset the configure handle
        Ret = HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, &stCipherCtrl);
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        cipher_memset_s ((HI_U8*)stCipherCtrl.u32IV, sizeof(stCipherCtrl.u32IV), 0, 16);
        Ret |= HI_MPI_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }
        bIsFirstBlock = HI_FALSE;
    }

    if(!bIsLastBlock)
    {
       Ret = AES_Encrypt(hCipherHandle, pInputData, u32InputDataLen, u8TmpBuf); /* X := AES-128(KEY, Y); */
       if(Ret != HI_SUCCESS)
       {
            return Ret;
       }
    }
    else
    {
        bIsFirstBlock = HI_TRUE;

        n = (u32InputDataLen + 15) / 16; /* n is number of rounds */
        if ( n == 0 )
        {
            n = 1;
            flag = 0;
        }
        else
        {
            if ( (u32InputDataLen % 16) == 0 ) /* last block is a complete block */
            {
                flag = 1;
            }
            else /* last block is not complete block */
            {
                flag = 0;
            }
        }

        if ( flag )  /* last block is complete block */
        {
            xor_128(&pInputData[16 * (n - 1)], K1, M_last);
        }
        else
        {
            padding(&pInputData[16 * (n - 1)], padded, u32InputDataLen % 16);
            xor_128(padded, K2, M_last);
        }

        if(n > 1)
        {
           Ret = AES_Encrypt(hCipherHandle, pInputData, 16 * (n - 1), u8TmpBuf); /* X := AES-128(KEY, Y); */
           if(Ret != HI_SUCCESS)
           {
                return Ret;
           }
        }

        Ret = AES_Encrypt(hCipherHandle, M_last, 16, X);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        for ( i = 0; i < 16; i++ )
        {
            pOutputMAC[i] = X[i];
        }
    }

    return HI_SUCCESS;
}

/**********************************************************
*                        AES_CBCMAC_AUTH                  *
***********************************************************/
HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    HI_ERR_CIPHER("AES cbc mac don't support!");

    return HI_FAILURE;
}

