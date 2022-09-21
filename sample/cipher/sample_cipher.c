/******************************************************************************
Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_rng.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2012/07/10
Last Modified :
Description   : sample for cipher
Function List :
History       :
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_common.h"
#include "hi_adp.h"

#define HI_ERR_CIPHER(format, arg...)     HI_PRINT( "\033[0;1;31m" format "\033[0m", ## arg)
#define HI_INFO_CIPHER(format, arg...)    HI_PRINT( "\033[0;1;32m" format "\033[0m", ## arg)
#define TEST_END_PASS()				  	  HI_INFO_CIPHER("****************** %s test PASS !!! ******************\n", __FUNCTION__)
#define TEST_END_FAIL()				  	  HI_ERR_CIPHER("****************** %s test FAIL !!! ******************\n", __FUNCTION__)
#define TEST_RESULT_PRINT()				  { if (ret) TEST_END_FAIL(); else TEST_END_PASS();}
#define U32_TO_POINT(addr)  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)  ((HI_U32)((HI_SIZE_T)(addr)))

typedef HI_S32 (*list_func)();

/*
static HI_U8 aes_128_cbc_IV[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
static HI_U8 aes_128_cbc_key[16]= {0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
static HI_U8 aes_128_src_buf[16] = {0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static HI_U8 aes_128_dst_buf[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
*/

static HI_S32 printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("0x%02x ", pu8Input[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}


HI_S32 Setconfiginfo(HI_HANDLE chnHandle, HI_BOOL bKeyByCA, HI_UNF_CIPHER_ALG_E alg, HI_UNF_CIPHER_WORK_MODE_E mode, HI_UNF_CIPHER_KEY_LENGTH_E keyLen,
                                                const HI_U8 u8KeyBuf[16], const HI_U8 u8IVBuf[16])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.enAlg = alg;
    CipherCtrl.enWorkMode = mode;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = keyLen;
    CipherCtrl.bKeyByCA = bKeyByCA;
    if(CipherCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
        memcpy(CipherCtrl.u32IV, u8IVBuf, 16);
    }

    memcpy(CipherCtrl.u32Key, u8KeyBuf, 16);

    s32Ret = HI_UNF_CIPHER_ConfigHandle(chnHandle, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* encrypt data using special chn*/
HI_VOID CBC_AES128(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 16;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_U8 aes_key[16] = {0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C};
    HI_U8 aes_IV[16]  = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    HI_U8 aes_src[16] = {0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,0x7E,0x11,0x73,0x93,0x17,0x2A};
    HI_U8 aes_dst[16] = {0x76,0x49,0xAB,0xAC,0x81,0x19,0xB2,0x46,0xCE,0xE9,0x8E,0x9B,0x12,0xE9,0x19,0x7D};

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return ;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return ;
    }

    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    /* For encrypt */
    s32Ret = Setconfiginfo(hTestchnid,
                            HI_FALSE,
                            HI_UNF_CIPHER_ALG_AES,
                            HI_UNF_CIPHER_WORK_MODE_CBC,
                            HI_UNF_CIPHER_KEY_AES_128BIT,
                            aes_key,
                            aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CBC-AES-128-ORI:", aes_src, sizeof(aes_src));

    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CBC-AES-128-ENC:", pOutputAddrVir, sizeof(aes_dst));

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("cipher encrypt, memcmp failed!\n");
        s32Ret = HI_FAILURE;

        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = Setconfiginfo(hTestchnid,
                                    HI_FALSE,
                                    HI_UNF_CIPHER_ALG_AES,
                                    HI_UNF_CIPHER_WORK_MODE_CBC,
                                    HI_UNF_CIPHER_KEY_AES_128BIT,
                                    aes_key,
                                    aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CBC-AES-128-DEC:", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("cipher decrypt, memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return ;
}

HI_VOID CFB_AES128(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 32;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_U8 aes_key[16] = {"\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C"};
    HI_U8 aes_IV[16]  = {"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"};
    HI_U8 aes_src[32] = {"\x6B\xC1\xBE\xE2\x2E\x40\x9F\x96\xE9\x3D\x7E\x11\x73\x93\x17\x2A\xAE\x2D\x8A\x57\x1E\x03\xAC\x9C\x9E\xB7\x6F\xAC\x45\xAF\x8E\x51"};
    HI_U8 aes_dst[32] = {"\x3B\x3F\xD9\x2E\xB7\x2D\xAD\x20\x33\x34\x49\xF8\xE8\x3C\xFB\x4A\xC8\xA6\x45\x37\xA0\xB3\xA9\x3F\xCD\xE3\xCD\xAD\x9F\x1C\xE5\x8B"};

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return ;
    }
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return ;
    }
    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    /* For encrypt */
    s32Ret = Setconfiginfo(hTestchnid,
                            HI_FALSE,
                            HI_UNF_CIPHER_ALG_AES,
                            HI_UNF_CIPHER_WORK_MODE_CFB,
                            HI_UNF_CIPHER_KEY_AES_128BIT,
                            aes_key,
                            aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CFB-AES-128-ORI:", aes_src, u32TestDataLen);

    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CFB-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = Setconfiginfo(hTestchnid,
                                    HI_FALSE,
                                    HI_UNF_CIPHER_ALG_AES,
                                    HI_UNF_CIPHER_WORK_MODE_CFB,
                                    HI_UNF_CIPHER_KEY_AES_128BIT,
                                    aes_key,
                                    aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CFB-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	TEST_END_PASS();
	
__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return ;
}

HI_VOID CFB_AES128_COPY_AVOID(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 32;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_U8 aes_key[16] = {"\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C"};
    HI_U8 aes_IV[16]  = {"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"};
    HI_U8 aes_src[32] = {"\x6B\xC1\xBE\xE2\x2E\x40\x9F\x96\xE9\x3D\x7E\x11\x73\x93\x17\x2A\xAE\x2D\x8A\x57\x1E\x03\xAC\x9C\x9E\xB7\x6F\xAC\x45\xAF\x8E\x51"};
    HI_U8 aes_dst[32] = {"\x3B\x3F\xD9\x2E\xB7\x2D\xAD\x20\x33\x34\x49\xF8\xE8\x3C\xFB\x4A\xC8\xA6\x45\x37\xA0\xB3\xA9\x3F\xCD\xE3\xCD\xAD\x9F\x1C\xE5\x8B"};

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return ;
    }
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_COPY_AVOID;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return ;
    }
    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    /* For encrypt */
    s32Ret = Setconfiginfo(hTestchnid,
                            HI_FALSE,
                            HI_UNF_CIPHER_ALG_AES,
                            HI_UNF_CIPHER_WORK_MODE_CFB,
                            HI_UNF_CIPHER_KEY_AES_128BIT,
                            aes_key,
                            aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CFB-AES-128-ORI:", aes_src, u32TestDataLen);

    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CFB-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = Setconfiginfo(hTestchnid,
                                    HI_FALSE,
                                    HI_UNF_CIPHER_ALG_AES,
                                    HI_UNF_CIPHER_WORK_MODE_CFB,
                                    HI_UNF_CIPHER_KEY_AES_128BIT,
                                    aes_key,
                                    aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CFB-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return ;
}

HI_VOID CTR_AES128(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 32;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_U8 aes_key[16] = {"\x7E\x24\x06\x78\x17\xFA\xE0\xD7\x43\xD6\xCE\x1F\x32\x53\x91\x63"};
    HI_U8 aes_IV[16]  = {"\x00\x6C\xB6\xDB\xC0\x54\x3B\x59\xDA\x48\xD9\x0B\x00\x00\x00\x01"};
    HI_U8 aes_src[32] = {"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"};
    HI_U8 aes_dst[32] = {"\x51\x04\xA1\x06\x16\x8A\x72\xD9\x79\x0D\x41\xEE\x8E\xDA\xD3\x88\xEB\x2E\x1E\xFC\x46\xDA\x57\xC8\xFC\xE6\x30\xDF\x91\x41\xBE\x28"};

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return ;
    }
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return ;
    }
    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    /* For encrypt */
    s32Ret = Setconfiginfo(hTestchnid,
                            HI_FALSE,
                            HI_UNF_CIPHER_ALG_AES,
                            HI_UNF_CIPHER_WORK_MODE_CTR,
                            HI_UNF_CIPHER_KEY_AES_128BIT,
                            aes_key,
                            aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CTR-AES-128-ORI:", aes_src, u32TestDataLen);

    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CTR-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = Setconfiginfo(hTestchnid,
                                    HI_FALSE,
                                    HI_UNF_CIPHER_ALG_AES,
                                    HI_UNF_CIPHER_WORK_MODE_CTR,
                                    HI_UNF_CIPHER_KEY_AES_128BIT,
                                    aes_key,
                                    aes_IV);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CTR-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return ;
}

#if defined (CHIP_TYPE_hi3796mv200)

// Klen  = 128, Tlen =32, Nlen  = 56,  Alen  = 64, and  Plen  = 32
// t = 4, q=8, p=4
HI_S32 CCM_AES128(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 4;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32AadAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U32 u32TagLen;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_U8 *pAadAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_CTRL_EX_S CipherCtrl;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S stCtrl;
    HI_U8 aes_key[16] = {"\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"};
    HI_U8 aes_n[7] = {"\x10\x11\x12\x13\x14\x15\x16"};
    HI_U8 aes_a[8] = {"\x00\x01\x02\x03\x04\x05\x06\x07"};
    HI_U8 aes_src[4] = {"\x20\x21\x22\x23"};
    HI_U8 aes_dst[4] = {"\x71\x62\x01\x5b"};
    HI_U8 aes_tag[4] = {"\x4d\xac\x25\x5d"};
    HI_U8 out_tag[4];

    printf("\n--------------------------%s-----------------------\n", __FUNCTION__);

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return s32Ret;
    }

    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(32, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(32, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    u32AadAddrPhy = POINT_TO_U32(HI_MMZ_New(sizeof(aes_a), 0, NULL, "CIPHER_AAD"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for AAD failed!\n");
        goto __CIPHER_EXIT__;
    }
    pAadAddrVir = HI_MMZ_Map(u32AadAddrPhy, u32Testcached);

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_EX_S));
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CCM;
    CipherCtrl.bKeyByCA = HI_FALSE;
    stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    stCtrl.u32IVLen = sizeof(aes_n);
    stCtrl.u32TagLen = sizeof(aes_tag);
    stCtrl.u32ALen = sizeof(aes_a);
    stCtrl.u32APhyAddr = u32AadAddrPhy;
    memcpy(stCtrl.u32IV, aes_n, sizeof(aes_n));
    memcpy(stCtrl.u32Key, aes_key, 16);
    memcpy(pAadAddrVir, aes_a, sizeof(aes_a));
    CipherCtrl.pParam = &stCtrl;
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CCM-AES-128-ORI:", aes_src, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);
    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CCM-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("CCM-AES-128-TAG", out_tag, sizeof(aes_tag));
    if ( 0 != memcmp(out_tag, aes_tag, sizeof(aes_tag)) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CCM-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("CCM-AES-128-TAG", out_tag, sizeof(aes_tag));
    if ( 0 != memcmp(out_tag, aes_tag, sizeof(aes_tag)) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }
    TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }
    if (u32AadAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32AadAddrPhy);
        HI_MMZ_Delete(u32AadAddrPhy);
    }


    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return s32Ret;
}

/* *****************************************************************************
 * In the following example,  Klen  = 128, Tlen =112,  Nlen  = 104,
 * Alen  = 524288, and  Plen  = 256.
 ******************************************************************************/
HI_S32 CCM_AES128_2(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 32;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32AadAddrPhy = 0;
    HI_U32 u32TagLen, i;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_U8 *pAadAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_CTRL_EX_S CipherCtrl;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S stCtrl;
    HI_U8 aes_key[16] = {"\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"};
    HI_U8 aes_n[13] = {"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c"};
    static HI_U8 aes_a[65536];
    HI_U8 aes_src[32] = {"\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f"
                         "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f"};
    HI_U8 aes_dst[32] = {"\x69\x91\x5d\xad\x1e\x84\xc6\x37\x6a\x68\xc2\x96\x7e\x4d\xab\x61"
                         "\x5a\xe0\xfd\x1f\xae\xc4\x4c\xc4\x84\x82\x85\x29\x46\x3c\xcf\x72"};
    HI_U8 aes_tag[14] = {"\xb4\xac\x6b\xec\x93\xe8\x59\x8e\x7f\x0d\xad\xbc\xea\x5b"};
    HI_U8 out_tag[14];

    printf("\n--------------------------%s-----------------------\n", __FUNCTION__);

    for(i=0; i<65536; i++)
    {
        aes_a[i] = i;
    }

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return s32Ret;
    }
    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, 0);

    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, 0);

    u32AadAddrPhy = POINT_TO_U32(HI_MMZ_New(sizeof(aes_a), 0, NULL, "CIPHER_AAD"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for AAD failed!\n");
        goto __CIPHER_EXIT__;
    }
    pAadAddrVir = HI_MMZ_Map(u32AadAddrPhy, 0);

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_EX_S));
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CCM;
    stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.bKeyByCA = HI_FALSE;
    stCtrl.u32IVLen = sizeof(aes_n);
    stCtrl.u32TagLen = sizeof(aes_tag);
    stCtrl.u32ALen = sizeof(aes_a);
    stCtrl.u32APhyAddr = u32AadAddrPhy;
    memcpy(stCtrl.u32IV, aes_n, sizeof(aes_n));
    memcpy(stCtrl.u32Key, aes_key, 16);
    memcpy(pAadAddrVir, aes_a, sizeof(aes_a));
    CipherCtrl.pParam = &stCtrl;
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("CCM-AES-128-ORI:", aes_src, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);
    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CCM-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("CCM-AES-128-TAG", out_tag, sizeof(aes_tag));
    if ( 0 != memcmp(out_tag, aes_tag, sizeof(aes_tag)) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("CCM-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("CCM-AES-128-TAG", out_tag, sizeof(aes_tag));
    if ( 0 != memcmp(out_tag, aes_tag, sizeof(aes_tag)) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }
    TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }
    if (u32AadAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32AadAddrPhy);
        HI_MMZ_Delete(u32AadAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return s32Ret;
}

HI_S32 GCM_AES128(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TestDataLen = 60;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32AadAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_U8 *pAadAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_U32 u32TagLen;
    HI_UNF_CIPHER_CTRL_EX_S CipherCtrl;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S stCtrl;
    HI_U8 aes_key[32] = {"\xfe\xff\xe9\x92\x86\x65\x73\x1c\x6d\x6a\x8f\x94\x67\x30\x83\x08"};
    HI_U8 aes_iv[12] =  {"\xca\xfe\xba\xbe\xfa\xce\xdb\xad\xde\xca\xf8\x88"};
    HI_U8 aes_a[20] =   {"\xfe\xed\xfa\xce\xde\xad\xbe\xef\xfe\xed\xfa\xce\xde\xad\xbe\xef\xab\xad\xda\xd2"};
    HI_U8 aes_src[60] = {"\xd9\x31\x32\x25\xf8\x84\x06\xe5\xa5\x59\x09\xc5\xaf\xf5\x26\x9a"
                         "\x86\xa7\xa9\x53\x15\x34\xf7\xda\x2e\x4c\x30\x3d\x8a\x31\x8a\x72"
                         "\x1c\x3c\x0c\x95\x95\x68\x09\x53\x2f\xcf\x0e\x24\x49\xa6\xb5\x25"
                         "\xb1\x6a\xed\xf5\xaa\x0d\xe6\x57\xba\x63\x7b\x39"};
    HI_U8 aes_dst[60] = {"\x42\x83\x1e\xc2\x21\x77\x74\x24\x4b\x72\x21\xb7\x84\xd0\xd4\x9c"
                         "\xe3\xaa\x21\x2f\x2c\x02\xa4\xe0\x35\xc1\x7e\x23\x29\xac\xa1\x2e"
                         "\x21\xd5\x14\xb2\x54\x66\x93\x1c\x7d\x8f\x6a\x5a\xac\x84\xaa\x05"
                         "\x1b\xa3\x0b\x39\x6a\x0a\xac\x97\x3d\x58\xe0\x91"};
    HI_U8 aes_tag[16] = {"\x5b\xc9\x4f\xbc\x32\x21\xa5\xdb\x94\xfa\xe9\x5a\xe7\x12\x1a\x47"};
    HI_U8 out_tag[16];

    printf("\n--------------------------%s-----------------------\n", __FUNCTION__);


    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return s32Ret;
    }
    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);

    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    u32AadAddrPhy = POINT_TO_U32(HI_MMZ_New(sizeof(aes_a), 0, NULL, "CIPHER_AAD"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for AAD failed!\n");
        goto __CIPHER_EXIT__;
    }
    pAadAddrVir = HI_MMZ_Map(u32AadAddrPhy, u32Testcached);

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_EX_S));
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_GCM;
    stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.bKeyByCA = HI_FALSE;
    stCtrl.u32IVLen = sizeof(aes_iv);
    stCtrl.u32TagLen = sizeof(aes_tag);
    stCtrl.u32ALen = sizeof(aes_a);
    stCtrl.u32APhyAddr = u32AadAddrPhy;
    memcpy(stCtrl.u32IV, aes_iv, sizeof(aes_iv));
    memcpy(stCtrl.u32Key, aes_key, 16);
    memcpy(pAadAddrVir, aes_a, sizeof(aes_a));
    CipherCtrl.pParam = &stCtrl;
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, aes_src, u32TestDataLen);
    printBuffer("GCM-AES-128-ORI:", aes_src, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);
    s32Ret = HI_UNF_CIPHER_Encrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("GCM-AES-128-ENC:", pOutputAddrVir, u32TestDataLen);

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_dst, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("GCM-AES-128-TAG", out_tag, 16);
    if ( 0 != memcmp(out_tag, aes_tag, 16) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

   /* For decrypt */
    s32Ret = HI_UNF_CIPHER_ConfigHandleEx(hTestchnid, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memcpy(pInputAddrVir, aes_dst, u32TestDataLen);
    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_Decrypt(hTestchnid, u32InputAddrPhy, u32OutPutAddrPhy, u32TestDataLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher decrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    printBuffer("GCM-AES-128-DEC", pOutputAddrVir, u32TestDataLen);
    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, aes_src, u32TestDataLen) )
    {
        HI_ERR_CIPHER("Memcmp failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

	u32TagLen = 16;
    s32Ret = HI_UNF_CIPHER_GetTag(hTestchnid, out_tag, &u32TagLen);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Get tag failed.\n");
        goto __CIPHER_EXIT__;
    }
    printBuffer("GCM-AES-128-TAG", out_tag, 16);
    if ( 0 != memcmp(out_tag, aes_tag, 16) )
    {
        HI_ERR_CIPHER("Tag compare failed!\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    if (u32AadAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32AadAddrPhy);
        HI_MMZ_Delete(u32AadAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return s32Ret;
}
#endif

HI_S32 main(int argc, char* argv[])
{
    HI_SYS_Init();

    CBC_AES128();

    CFB_AES128();
    CFB_AES128_COPY_AVOID();
    CTR_AES128();

#if defined (CHIP_TYPE_hi3796mv200)
    CCM_AES128();
    CCM_AES128_2();
    GCM_AES128();
#endif

    HI_SYS_DeInit();

    return HI_SUCCESS;
}

