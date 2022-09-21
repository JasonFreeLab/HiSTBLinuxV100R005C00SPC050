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

#define TEST_NORMAL_CNT 	3
#define SM2_TEST_MSG_SIZE   1000

#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U8 *_str; \
    _str = (HI_U8*)str; \
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("\\x%02x", *((_str)+_i));\
    }\
    HI_PRINT("\n");\
}


void get_rand(HI_U8 *buf, HI_U32 size)
{
    HI_U32 i;
    
    for(i=0; i<size; i+=4)
    {
        *(HI_U32*)(buf+i) = rand();
    }
}

/*SM2 signature and verify, use gold data*/
HI_S32 sm2_test0(HI_VOID)
{
	HI_S32 ret;
	HI_UNF_CIPHER_SM2_SIGN_S stSm2Sign;
    HI_UNF_CIPHER_SM2_VERIFY_S stSm2Verify;
    HI_U8 u8R[SM2_LEN_IN_BYTE];
    HI_U8 u8S[SM2_LEN_IN_BYTE];
    HI_U8 u8d[SM2_LEN_IN_BYTE]  = {"\x39\x45\x20\x8F\x7B\x21\x44\xB1\x3F\x36\xE3\x8A\xC6\xD3\x9F\x95\x88\x93\x93\x69\x28\x60\xB5\x1A\x42\xFB\x81\xEF\x4D\xF7\xC5\xB8"};
    HI_U8 u8Px[SM2_LEN_IN_BYTE] = {"\x09\xF9\xDF\x31\x1E\x54\x21\xA1\x50\xDD\x7D\x16\x1E\x4B\xC5\xC6\x72\x17\x9F\xAD\x18\x33\xFC\x07\x6B\xB0\x8F\xF3\x56\xF3\x50\x20"};
    HI_U8 u8Py[SM2_LEN_IN_BYTE] = {"\xCC\xEA\x49\x0C\xE2\x67\x75\xA5\x2D\xC6\xEA\x71\x8C\xC1\xAA\x60\x0A\xED\x05\xFB\xF3\x5E\x08\x4A\x66\x32\xF6\x07\x2D\xA9\xAD\x13"};
    HI_U8 IDA[18] = {"\x42\x4C\x49\x43\x45\x31\x32\x33\x40\x59\x41\x48\x4F\x4F\x2E\x43\x4F\x11"};
//    HI_U8 u8k[SM2_LEN_IN_BYTE]  = {"\x59\x27\x6E\x27\xD5\x06\x86\x1A\x16\x68\x0F\x3A\xD9\xC0\x2D\xCC\xEF\x3C\xC1\xFA\x3C\xDB\xE4\xCE\x6D\x54\xB8\x0D\xEA\xC1\xBC\x21"};    
//    HI_U8 u8GR[SM2_LEN_IN_BYTE] = {"\x31\xfc\x32\x2e\x42\x04\xd0\x38\x87\x51\x8a\x3b\xaf\x93\xec\x86\xa9\xe6\x50\xce\xe1\x85\xde\x18\x5d\xeb\xae\xd9\xcf\xcb\xdd\xee"};
//    HI_U8 u8GS[SM2_LEN_IN_BYTE] = {"\xc0\xd8\x4e\x8f\xd1\x24\x8b\x7b\xac\x38\x11\xc8\xf1\xdc\xe8\x37\x45\xe8\x5e\x03\x97\x60\x69\x08\x2d\xd3\x22\xd2\x5b\xf7\xcf\x14"};
    HI_U8 u8M[14] = {"\x6D\x65\x73\x73\x61\x67\x65\x20\x64\x69\x67\x65\x73\x74"};
    	
    stSm2Sign.pu8Id = IDA;
    stSm2Sign.u16IdLen = sizeof(IDA);
    memcpy(stSm2Sign.u32d, u8d, SM2_LEN_IN_BYTE);
    memcpy(stSm2Sign.u32Px, u8Px, SM2_LEN_IN_BYTE);
    memcpy(stSm2Sign.u32Py, u8Py, SM2_LEN_IN_BYTE);

    memset(&stSm2Verify, 0, sizeof(HI_UNF_CIPHER_SM2_VERIFY_S)); 
    memcpy(stSm2Verify.u32Px, u8Px, SM2_LEN_IN_BYTE);
    memcpy(stSm2Verify.u32Py, u8Py, SM2_LEN_IN_BYTE);
    stSm2Verify.pu8Id = IDA;
    stSm2Verify.u16IdLen = sizeof(IDA); 

    HI_UNF_CIPHER_Init();
    
    ret = HI_UNF_CIPHER_Sm2Sign(&stSm2Sign, u8M, sizeof(u8M), u8R, u8S);
	if (ret != HI_SUCCESS)
	{
		ret = HI_FAILURE;
		goto EXIT;
	}

    HI_PRINT_HEX("r", u8R, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX("s", u8S, SM2_LEN_IN_BYTE);

    HI_PRINT("Verify...\n");
    ret = HI_UNF_CIPHER_Sm2Verify(&stSm2Verify, u8M, sizeof(u8M), u8R, u8S);
	if (ret != HI_SUCCESS)
	{
		ret = HI_FAILURE;
		goto EXIT;
	}

EXIT:
	
	TEST_RESULT_PRINT();
    
    HI_UNF_CIPHER_DeInit();
    
	return HI_SUCCESS;
}

/*SM2 signature and verify, use rand data*/
HI_S32 sm2_test1(HI_VOID)
{
	HI_S32 ret;
	HI_UNF_CIPHER_SM2_SIGN_S stSm2Sign;
    HI_UNF_CIPHER_SM2_VERIFY_S stSm2Verify;
    HI_UNF_CIPHER_SM2_KEY_S stSm2Key;
    HI_U8 u8R[SM2_LEN_IN_BYTE];
    HI_U8 u8S[SM2_LEN_IN_BYTE];
    HI_U8 *pIDA;
    HI_U8 *pu8M;
    HI_U32 IDALen;
    HI_U32 MLen;
    HI_U32 i;

    HI_UNF_CIPHER_Init();
    
    pIDA = malloc(SM2_TEST_MSG_SIZE);
    pu8M = malloc(SM2_TEST_MSG_SIZE);

    for(i=0; i<TEST_NORMAL_CNT; i++)
    {
        HI_PRINT("\n-----------------Progress: %d/%d----------------\n", i, TEST_NORMAL_CNT-1);
        HI_UNF_CIPHER_Sm2GenKey(&stSm2Key);

        HI_PRINT_HEX("d", (HI_U8*)stSm2Key.u32d, SM2_LEN_IN_BYTE);
        HI_PRINT_HEX("Px", (HI_U8*)stSm2Key.u32Px, SM2_LEN_IN_BYTE);
        HI_PRINT_HEX("Py", (HI_U8*)stSm2Key.u32Py, SM2_LEN_IN_BYTE);

        IDALen = rand() % SM2_TEST_MSG_SIZE;
        MLen = rand() % SM2_TEST_MSG_SIZE;
        HI_PRINT("IDALEN: 0x%x, MLEN:0x%x \n", IDALen, MLen);

        get_rand(pIDA, IDALen);
        get_rand(pu8M, MLen);

        memset(&stSm2Sign, 0, sizeof(HI_UNF_CIPHER_SM2_SIGN_S));
        memcpy(stSm2Sign.u32d, stSm2Key.u32d, SM2_LEN_IN_BYTE);
                
        memcpy(stSm2Sign.u32Px, stSm2Key.u32Px, SM2_LEN_IN_BYTE);
        memcpy(stSm2Sign.u32Py, stSm2Key.u32Py, SM2_LEN_IN_BYTE);
        stSm2Sign.pu8Id = pIDA;
        stSm2Sign.u16IdLen = IDALen;

        memset(&stSm2Verify, 0, sizeof(HI_UNF_CIPHER_SM2_VERIFY_S)); 
        memcpy(stSm2Verify.u32Px, stSm2Key.u32Px, SM2_LEN_IN_BYTE);
        memcpy(stSm2Verify.u32Py, stSm2Key.u32Py, SM2_LEN_IN_BYTE);
        stSm2Verify.pu8Id = pIDA;
        stSm2Verify.u16IdLen = IDALen; 
        
        ret = HI_UNF_CIPHER_Sm2Sign(&stSm2Sign, pu8M, MLen, u8R, u8S);
		if (ret != HI_SUCCESS)
		{
			ret = HI_FAILURE;
			goto EXIT;
		}
        HI_PRINT_HEX("hi-r", u8R, SM2_LEN_IN_BYTE);
        HI_PRINT_HEX("hi-s", u8S, SM2_LEN_IN_BYTE);

        memcpy(stSm2Sign.u32d, stSm2Key.u32d, SM2_LEN_IN_BYTE);
        ret = HI_UNF_CIPHER_Sm2Verify(&stSm2Verify, pu8M, MLen, u8R, u8S);
		if (ret != HI_SUCCESS)
		{
			ret = HI_FAILURE;
			goto EXIT;
		}		
    }

EXIT:
	
	TEST_RESULT_PRINT();
	
    free(pIDA);
    free(pu8M);

    HI_UNF_CIPHER_DeInit();

	return HI_SUCCESS;
}

/*SM2 encrypt and decrypt, use gold data*/
HI_S32 sm2_test2(HI_VOID)
{
    HI_S32 ret;
	HI_U8 u8M[19] = {"encryption standard"};
    HI_U8 u8MO[19] = {0};  //len = M
    HI_U8 u8C[65+19+32] = {0};
    HI_UNF_CIPHER_SM2_ENC_S stSm2Enc;
    HI_UNF_CIPHER_SM2_DEC_S stSm2Dec;
    HI_U32 u32Mlen;
    HI_U32 u32Clen;
    HI_U8 u8d[SM2_LEN_IN_BYTE]  = {"\x39\x45\x20\x8F\x7B\x21\x44\xB1\x3F\x36\xE3\x8A\xC6\xD3\x9F\x95\x88\x93\x93\x69\x28\x60\xB5\x1A\x42\xFB\x81\xEF\x4D\xF7\xC5\xB8"};
    HI_U8 u8Px[SM2_LEN_IN_BYTE] = {"\x09\xF9\xDF\x31\x1E\x54\x21\xA1\x50\xDD\x7D\x16\x1E\x4B\xC5\xC6\x72\x17\x9F\xAD\x18\x33\xFC\x07\x6B\xB0\x8F\xF3\x56\xF3\x50\x20"};
    HI_U8 u8Py[SM2_LEN_IN_BYTE] = {"\xCC\xEA\x49\x0C\xE2\x67\x75\xA5\x2D\xC6\xEA\x71\x8C\xC1\xAA\x60\x0A\xED\x05\xFB\xF3\x5E\x08\x4A\x66\x32\xF6\x07\x2D\xA9\xAD\x13"};
/*  HI_U8 u8k[SM2_LEN_IN_BYTE]  = {"\x59\x27\x6E\x27\xD5\x06\x86\x1A\x16\x68\x0F\x3A\xD9\xC0\x2D\xCC\xEF\x3C\xC1\xFA\x3C\xDB\xE4\xCE\x6D\x54\xB8\x0D\xEA\xC1\xBC\x21"};    
    HI_U8 u8GC[65+19+32] = {
        "\x04\x04\xeb\xfc\x71\x8e\x8d\x17\x98\x62\x04\x32\x26\x8e\x77\xfe"
        "\xb6\x41\x5e\x2e\xde\x0e\x07\x3c\x0f\x4f\x64\x0e\xcd\x2e\x14\x9a"
        "\x73\xe8\x58\xf9\xd8\x1e\x54\x30\xa5\x7b\x36\xda\xab\x8f\x95\x0a"
        "\x3c\x64\xe6\xee\x6a\x63\x09\x4d\x99\x28\x3a\xff\x76\x7e\x12\x4d"
        "\xf0\x21\x88\x6c\xa9\x89\xca\x9c\x7d\x58\x08\x73\x07\xca\x93\x09"
        "\x2d\x65\x1e\xfa\x59\x98\x3c\x18\xf8\x09\xe2\x62\x92\x3c\x53\xae"
        "\xc2\x95\xd3\x03\x83\xb5\x4e\x39\xd6\x09\xd1\x60\xaf\xcb\x19\x08"
        "\xd0\xbd\x87\x66"}; */

    HI_UNF_CIPHER_Init();
        
    HI_PRINT("--------------------------Encrypt-------------------------\n");
    memset(&stSm2Enc, 0, sizeof(HI_UNF_CIPHER_SM2_ENC_S)); 
    memcpy(stSm2Enc.u32Px, u8Px, SM2_LEN_IN_BYTE);
    memcpy(stSm2Enc.u32Py, u8Py, SM2_LEN_IN_BYTE);

    memset(&stSm2Dec, 0, sizeof(HI_UNF_CIPHER_SM2_DEC_S)); 
    memcpy(stSm2Dec.u32d, u8d, 32);

    ret = HI_UNF_CIPHER_Sm2Encrypt(&stSm2Enc, u8M, sizeof(u8M), u8C, &u32Clen);
    if (u32Clen != ((SM2_LEN_IN_BYTE*2+1) + sizeof(u8M) + SM2_LEN_IN_BYTE))
    {
        HI_ERR_CIPHER("Error, sm2 encrypt failed, invalid Clen(0x%x)!\n", u32Clen);
		ret = HI_FAILURE;
		goto EXIT;
    }
    
    HI_PRINT_HEX("C", u8C, u32Clen);

    HI_PRINT("--------------------------Decrypt-------------------------\n");
    ret = HI_UNF_CIPHER_Sm2Decrypt(&stSm2Dec, u8C, u32Clen, u8MO, &u32Mlen);
	if (ret != HI_SUCCESS)
	{
		return HI_FAILURE;
	}	
		
    if (u32Mlen != sizeof(u8M))
	{
		HI_PRINT("u32Mlen %d error\n", u32Mlen);
		ret = HI_FAILURE;
		goto EXIT;
	}

	HI_PRINT_HEX("MO", u8MO, u32Mlen);
    if (memcmp(u8M, u8MO, u32Mlen) != 0)
	{
		HI_PRINT("SM2_Decrypt check error\n");
		ret = HI_FAILURE;
		goto EXIT;
	}

EXIT:
	
	TEST_RESULT_PRINT();
    
    HI_UNF_CIPHER_DeInit();
    
	return HI_SUCCESS;
}

/*SM2 encrypt and decrypt, use rand data*/
HI_S32 sm2_test3(HI_VOID)
{
	HI_S32 ret;
    HI_U8 *pu8MI;
    HI_U8 *pu8MO;
    HI_U8 *pu8MC;
    HI_UNF_CIPHER_SM2_ENC_S stSm2Enc;
    HI_UNF_CIPHER_SM2_DEC_S stSm2Dec;
    HI_UNF_CIPHER_SM2_KEY_S stSm2Key;
    HI_U32 u32Mlen;
    HI_U32 u32Clen;
    HI_U32 i;

    HI_UNF_CIPHER_Init();

    pu8MI = malloc(SM2_TEST_MSG_SIZE);
    pu8MO = malloc(SM2_TEST_MSG_SIZE);
    pu8MC = malloc(SM2_TEST_MSG_SIZE + 65 + 32);
    	
    for(i=0; i<TEST_NORMAL_CNT; i++)
    {
        HI_PRINT("\n----------------------------Progress: %d/%d---------------------------\n", i, TEST_NORMAL_CNT-1);
        HI_UNF_CIPHER_Sm2GenKey(&stSm2Key);
        HI_PRINT_HEX("d", (HI_U8*)stSm2Key.u32d, SM2_LEN_IN_BYTE);
        HI_PRINT_HEX("Px", (HI_U8*)stSm2Key.u32Px, SM2_LEN_IN_BYTE);
        HI_PRINT_HEX("Py", (HI_U8*)stSm2Key.u32Py, SM2_LEN_IN_BYTE);

        u32Mlen = rand() % SM2_TEST_MSG_SIZE;
        get_rand(pu8MI, u32Mlen);

        HI_PRINT("u32Mlen: 0x%x\n", u32Mlen);

        memset(&stSm2Enc, 0, sizeof(HI_UNF_CIPHER_SM2_ENC_S)); 
        memcpy(stSm2Enc.u32Px, stSm2Key.u32Px, SM2_LEN_IN_BYTE);
        memcpy(stSm2Enc.u32Py, stSm2Key.u32Py, SM2_LEN_IN_BYTE);

        memset(&stSm2Dec, 0, sizeof(HI_UNF_CIPHER_SM2_DEC_S)); 
        memcpy(stSm2Dec.u32d, stSm2Key.u32d, 32);

        HI_PRINT("--------------------------Encrypt-------------------------\n");
        ret = HI_UNF_CIPHER_Sm2Encrypt(&stSm2Enc, pu8MI, u32Mlen, pu8MC, &u32Clen);
		if (ret != HI_SUCCESS)
		{
    		ret = HI_FAILURE;
    		goto EXIT;
		}
        if (u32Clen != ((SM2_LEN_IN_BYTE*2+1) + u32Mlen + SM2_LEN_IN_BYTE))
        {
            HI_ERR_CIPHER("Error, sm2 encrypt failed, invalid Clen(0x%x)!\n", u32Clen);
            return HI_FAILURE;
        }
        HI_PRINT_HEX("C", pu8MC, u32Clen > 128 ? 128 : u32Clen);
        HI_PRINT("--------------------------Decrypt-------------------------\n");        
        if (u32Clen != ((SM2_LEN_IN_BYTE*2+1) + u32Mlen + SM2_LEN_IN_BYTE))
        {
            HI_ERR_CIPHER("Error, sm2 encrypt failed, invalid Clen(0x%x)!\n", u32Clen);
            return HI_FAILURE;
        }

        memcpy(stSm2Dec.u32d, stSm2Key.u32d, SM2_LEN_IN_BYTE);
        
        ret = HI_UNF_CIPHER_Sm2Decrypt(&stSm2Dec, pu8MC, u32Clen, pu8MO, &u32Mlen);
		if (ret != HI_SUCCESS)
		{
    		ret = HI_FAILURE;
    		goto EXIT;
		}
        
    	HI_PRINT_HEX("MO", pu8MO, u32Mlen > 128 ? 128 : u32Mlen);
        
        if (memcmp(pu8MI, pu8MO, u32Mlen) != 0)
		{
			HI_PRINT("SM2_Decrypt check error\n");
    		ret = HI_FAILURE;
    		goto EXIT;
		}			
    }

EXIT:
	
	TEST_RESULT_PRINT();
    
    free(pu8MI);
    free(pu8MO);
    free(pu8MC);

    HI_UNF_CIPHER_DeInit();
        
	return HI_SUCCESS;
}

HI_S32 main(int argc, char* argv[])
{
    HI_SYS_Init();

#if defined (CHIP_TYPE_hi3796mv200)
    sm2_test0();
	sm2_test1();
	sm2_test2();
	sm2_test3();
#endif

    HI_SYS_DeInit();

    return HI_SUCCESS;
}

