/******************************************************************************
Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ecdsa.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2017
Last Modified :
Description   : sample for ecdsa
Function List :
History       :
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_common.h"

#define HI_ERR_CIPHER(format, arg...)     HI_PRINT( "\033[0;1;31m" format "\033[0m", ## arg)
#define HI_INFO_CIPHER(format, arg...)    HI_PRINT( "\033[0;1;32m" format "\033[0m", ## arg)
#define TEST_END_PASS()				  	  HI_INFO_CIPHER("****************** %s test PASS !!! ******************\n", __FUNCTION__)
#define TEST_END_FAIL()				  	  HI_ERR_CIPHER("****************** %s test FAIL !!! ******************\n", __FUNCTION__)
#define TEST_RESULT_PRINT()				  { if (ret) TEST_END_FAIL(); else TEST_END_PASS();}

typedef enum
{
	TIME_TYPE_START,
	TIME_TYPE_SUSPEND,
	TIME_TYPE_RESUME,
	TIME_TYPE_END,
}TIME_TYPE_EN;

HI_S32 printBuffer(const HI_CHAR *string, const HI_U8 *pu8Input, HI_U32 u32Length)
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

static HI_U8 readChar(const char *pu8Str)
{
    HI_U8 u8Ch = 0;

    if ((pu8Str[0] >= 'A') && (pu8Str[0] <= 'F'))
    {
        u8Ch = pu8Str[0] - 'A' + 10;
    }
    else if ((pu8Str[0] >= 'a') && (pu8Str[0] <= 'f'))
    {
        u8Ch = pu8Str[0] - 'a' + 10;
    }
    else if ((pu8Str[0] >= '0') && (pu8Str[0] <= '9'))
    {
        u8Ch = pu8Str[0] - '0';
    }

    u8Ch *= 16;

    if ((pu8Str[1] >= 'A') && (pu8Str[1] <= 'F'))
    {
        u8Ch += pu8Str[1] - 'A' + 10;
    }
    else if ((pu8Str[1] >= 'a') && (pu8Str[1] <= 'f'))
    {
        u8Ch += pu8Str[1] - 'a' + 10;
    }
    else if ((pu8Str[1] >= '0') && (pu8Str[1] <= '9'))
    {
        u8Ch += pu8Str[1] - '0';
    }

    return u8Ch;
}

static void readString(const char *pu8Str, HI_U8 * pu8Buf, HI_U32 u32Len)
{
    HI_U32 i;
    HI_U32 u32Strlen;

    memset(pu8Buf, 0, u32Len);

    u32Strlen = strlen(pu8Str);
    if (u32Len < u32Strlen/2)
    {
        u32Strlen = u32Len *2;
    }

    for(i= (u32Len-u32Strlen/2); i<u32Len; i++)
    {
        pu8Buf[i] = readChar(pu8Str+i*2);
    }
}

//http://www.secg.org/sec2-v2.pdf
#define ECDH_SECP192R1_P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF"
#define ECDH_SECP192R1_A  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFC"
#define ECDH_SECP192R1_B  "64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1"
#define ECDH_SECP192R1_GX "188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012"
#define ECDH_SECP192R1_GY "07192B95FFC8DA78631011ED6B24CDD573F977A11E794811"
#define ECDH_SECP192R1_N  "FFFFFFFFFFFFFFFFFFFFFFFF99DEF836146BC9B1B4D22831"
#define ECDH_SECP192R1_H                                                   1

#define ECDH_SECP224R1_P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001"
#define ECDH_SECP224R1_A  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE"
#define ECDH_SECP224R1_B  "B4050A850C04B3ABF54132565044B0B7D7BFD8BA270B39432355FFB4"
#define ECDH_SECP224R1_GX "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21"
#define ECDH_SECP224R1_GY "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34"
#define ECDH_SECP224R1_N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D"
#define ECDH_SECP224R1_H                                                    1

#define ECDH_SECP256R1_P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define ECDH_SECP256R1_A  "0000000000000000000000000000000000000000000000000000000000000000"
#define ECDH_SECP256R1_B  "0000000000000000000000000000000000000000000000000000000000000007"
#define ECDH_SECP256R1_GX "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"
#define ECDH_SECP256R1_GY "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"
#define ECDH_SECP256R1_N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define ECDH_SECP256R1_H                                                   1

#define ECDH_SECP384R1_P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF"
#define ECDH_SECP384R1_A  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFC"
#define ECDH_SECP384R1_B  "B3312FA7E23EE7E4988E056BE3F82D19181D9C6EFE8141120314088F5013875AC656398D8A2ED19D2A85C8EDD3EC2AEF"
#define ECDH_SECP384R1_GX "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7"
#define ECDH_SECP384R1_GY "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F"
#define ECDH_SECP384R1_N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973"
#define ECDH_SECP384R1_H                                                   1

#define ECDH_SECP512R1_P  "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
#define ECDH_SECP512R1_A  "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC"
#define ECDH_SECP512R1_B  "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00"
#define ECDH_SECP512R1_GX "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66"
#define ECDH_SECP512R1_GY "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650"
#define ECDH_SECP512R1_N  "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409"
#define ECDH_SECP512R1_H                                                   1

#define MAX_KEY_SIZE     66

int main(int argc, char* argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i;
    HI_UNF_CIPHER_ECC_PARAM_S stEccParam;
    HI_U32 ecdh_sizes[] =   { 24, 28, 32, 48, 66};
    const char *ecdh_P[] =  {ECDH_SECP192R1_P, ECDH_SECP224R1_P, ECDH_SECP256R1_P, ECDH_SECP384R1_P, ECDH_SECP512R1_P};
    const char *ecdh_A[] =  {ECDH_SECP192R1_A, ECDH_SECP224R1_A, ECDH_SECP256R1_A, ECDH_SECP384R1_A, ECDH_SECP512R1_A};
    const char *ecdh_B[] =  {ECDH_SECP192R1_B, ECDH_SECP224R1_B, ECDH_SECP256R1_B, ECDH_SECP384R1_B, ECDH_SECP512R1_B};
    const char *ecdh_GX[] = {ECDH_SECP192R1_GX, ECDH_SECP224R1_GX, ECDH_SECP256R1_GX, ECDH_SECP384R1_GX, ECDH_SECP512R1_GX};
    const char *ecdh_GY[] = {ECDH_SECP192R1_GY, ECDH_SECP224R1_GY, ECDH_SECP256R1_GY, ECDH_SECP384R1_GY, ECDH_SECP512R1_GY};
    const char *ecdh_N[] =  {ECDH_SECP192R1_N, ECDH_SECP224R1_N, ECDH_SECP256R1_N, ECDH_SECP384R1_N, ECDH_SECP512R1_N};
    const HI_U32 ecdh_H[] =  {ECDH_SECP192R1_H, ECDH_SECP224R1_H, ECDH_SECP256R1_H, ECDH_SECP384R1_H, ECDH_SECP512R1_H};
    HI_U8 msg[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    HI_U8 *pu8PrivKey;
    HI_U8 *pu8PubKeyX;
    HI_U8 *pu8PubKeyY;
    HI_U8 *pu8R;
    HI_U8 *pu8S;
    HI_U8 *pu8Buf;

    HI_SYS_Init();

    pu8Buf = (HI_U8*)malloc(MAX_KEY_SIZE * 11);
    if(pu8Buf == HI_NULL)
    {
        HI_ERR_CIPHER("malloc for buf failed\n");
        return HI_FAILURE;
    }

    stEccParam.pu8p  = pu8Buf;
    stEccParam.pu8a  = stEccParam.pu8p + MAX_KEY_SIZE;
    stEccParam.pu8b  = stEccParam.pu8a + MAX_KEY_SIZE;
    stEccParam.pu8GX = stEccParam.pu8b + MAX_KEY_SIZE;
    stEccParam.pu8GY = stEccParam.pu8GX+ MAX_KEY_SIZE;
    stEccParam.pu8n  = stEccParam.pu8GY + MAX_KEY_SIZE;
    pu8R = stEccParam.pu8n + MAX_KEY_SIZE;
    pu8S = pu8R + MAX_KEY_SIZE;
    pu8PrivKey = pu8S + MAX_KEY_SIZE;
    pu8PubKeyX = pu8PrivKey + MAX_KEY_SIZE;
    pu8PubKeyY = pu8PubKeyX + MAX_KEY_SIZE;

    ret = HI_UNF_CIPHER_Init();
    if ( HI_SUCCESS != ret )
    {
        return HI_FAILURE;
    }

    for(i=0; i<5; i++)
    {
        HI_INFO_CIPHER("\n*************************** E C D S A - T E S T %d ***********************\n", i);
        readString(ecdh_P[i], stEccParam.pu8p, ecdh_sizes[i]);
        readString(ecdh_A[i], stEccParam.pu8a, ecdh_sizes[i]);
        readString(ecdh_B[i], stEccParam.pu8b, ecdh_sizes[i]);
        readString(ecdh_GX[i], stEccParam.pu8GX, ecdh_sizes[i]);
        readString(ecdh_GY[i], stEccParam.pu8GY, ecdh_sizes[i]);
        readString(ecdh_N[i], stEccParam.pu8n, ecdh_sizes[i]);
        stEccParam.u32h = ecdh_H[i];
        stEccParam.u32keySize = ecdh_sizes[i];

        printf("ecdh_sizes: %d\n", ecdh_sizes[i]);

//       printBuffer("P", stEccParam.pu8p, ecdh_sizes[i]);
//       printBuffer("A", stEccParam.pu8a, ecdh_sizes[i]);
//       printBuffer("GX", stEccParam.pu8GX, ecdh_sizes[i]);
//       printBuffer("GY", stEccParam.pu8GY, ecdh_sizes[i]);
//       printBuffer("N", stEccParam.pu8n, ecdh_sizes[i]);

        ret = HI_UNF_CIPHER_EccGenKey(&stEccParam, HI_NULL, pu8PrivKey, pu8PubKeyX, pu8PubKeyY);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey B failed\n");
            return HI_FAILURE;
        }
    /*  printBuffer("PrivKey", pu8PrivKey, ecdh_sizes[i]);
        printBuffer("PubKeyX", pu8PubKeyX, ecdh_sizes[i]);
        printBuffer("PubKeyY", pu8PubKeyY, ecdh_sizes[i]);*/

        ret = HI_UNF_CIPHER_EcdsaSign(&stEccParam, pu8PrivKey, HI_UNF_CIPHER_HASH_TYPE_SHA1,
               msg, strlen((char*)msg), pu8R, pu8S);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey A failed, ret = 0x%x\n", -ret);
            return HI_FAILURE;
        }
    //  printBuffer("R", pu8R, ecdh_sizes[i]);
    //  printBuffer("S", pu8S, ecdh_sizes[i]);

        ret = HI_UNF_CIPHER_EcdsaVerify(&stEccParam, pu8PubKeyX, pu8PubKeyY,
            HI_UNF_CIPHER_HASH_TYPE_SHA1, msg, strlen((char*)msg), pu8R, pu8S);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey B failed\n");
            return HI_FAILURE;
        }
    }

    TEST_END_PASS();

    free(pu8Buf);

    HI_UNF_CIPHER_DeInit();
    HI_SYS_DeInit();

    return HI_SUCCESS;
}
