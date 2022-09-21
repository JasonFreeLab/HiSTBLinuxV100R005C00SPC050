/******************************************************************************
Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_dh.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2017
Last Modified :
Description   : sample for dh
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

#define HI_ERR_CIPHER(format, arg...)     HI_PRINT( "\033[0;1;31m" format "\033[0m", ## arg)
#define HI_INFO_CIPHER(format, arg...)    HI_PRINT( "\033[0;1;32m" format "\033[0m", ## arg)
#define TEST_END_PASS()				  	  HI_INFO_CIPHER("****************** %s test PASS !!! ******************\n", __FUNCTION__)
#define TEST_END_FAIL()				  	  HI_ERR_CIPHER("****************** %s test FAIL !!! ******************\n", __FUNCTION__)
#define TEST_RESULT_PRINT()				  { if (ret) TEST_END_FAIL(); else TEST_END_PASS();}

static HI_S32 printBuffer(const HI_CHAR *string, const HI_U8 *pu8Input, HI_U32 u32Length)
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

#define MBEDTLS_DHM_RFC3526_MODP_2048_P               \
    "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1" \
    "29024E088A67CC74020BBEA63B139B22514A08798E3404DD" \
    "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245" \
    "E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED" \
    "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3D" \
    "C2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F" \
    "83655D23DCA3AD961C62F356208552BB9ED529077096966D" \
    "670C354E4ABC9804F1746C08CA18217C32905E462E36CE3B" \
    "E39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9" \
    "DE2BCBF6955817183995497CEA956AE515D2261898FA0510" \
    "15728E5A8AACAA68FFFFFFFFFFFFFFFF"

#define MBEDTLS_DHM_RFC3526_MODP_2048_G           \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "000000000000000000000000000000000000000000000000" \
    "00000000000000000000000000000002"

#define MBEDTLS_DHM_RFC5114_MODP_2048_P               \
    "AD107E1E9123A9D0D660FAA79559C51FA20D64E5683B9FD1" \
    "B54B1597B61D0A75E6FA141DF95A56DBAF9A3C407BA1DF15" \
    "EB3D688A309C180E1DE6B85A1274A0A66D3F8152AD6AC212" \
    "9037C9EDEFDA4DF8D91E8FEF55B7394B7AD5B7D0B6C12207" \
    "C9F98D11ED34DBF6C6BA0B2C8BBC27BE6A00E0A0B9C49708" \
    "B3BF8A317091883681286130BC8985DB1602E714415D9330" \
    "278273C7DE31EFDC7310F7121FD5A07415987D9ADC0A486D" \
    "CDF93ACC44328387315D75E198C641A480CD86A1B9E587E8" \
    "BE60E69CC928B2B9C52172E413042E9B23F10B0E16E79763" \
    "C9B53DCF4BA80A29E3FB73C16B8E75B97EF363E2FFA31F71" \
    "CF9DE5384E71B81C0AC4DFFE0C10E64F"

#define MBEDTLS_DHM_RFC5114_MODP_2048_G              \
    "AC4032EF4F2D9AE39DF30B5C8FFDAC506CDEBE7B89998CAF"\
    "74866A08CFE4FFE3A6824A4E10B9A6F0DD921F01A70C4AFA"\
    "AB739D7700C29F52C57DB17C620A8652BE5E9001A8D66AD7"\
    "C17669101999024AF4D027275AC1348BB8A762D0521BC98A"\
    "E247150422EA1ED409939D54DA7460CDB5F6C6B250717CBE"\
    "F180EB34118E98D119529A45D6F834566E3025E316A330EF"\
    "BB77A86F0C1AB15B051AE3D428C8F8ACB70A8137150B8EEB"\
    "10E183EDD19963DDD9E263E4770589EF6AA21E7F5F2FF381"\
    "B539CCE3409D13CD566AFBB48D6C019181E1BCFE94B30269"\
    "EDFE72FE9B6AA4BD7B5A0F1C71CFFF4C19C418E1F6EC0179"\
    "81BC087F2A7065B384B890D3191F2BFA"

#define MAX_KEY_SIZE     256

int main(int argc, char* argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i;
    HI_U32 dhm_sizes[] = { MAX_KEY_SIZE, MAX_KEY_SIZE };
    const char *dhm_P[] = {MBEDTLS_DHM_RFC3526_MODP_2048_P, MBEDTLS_DHM_RFC3526_MODP_2048_P};
    const char *dhm_G[] = {MBEDTLS_DHM_RFC5114_MODP_2048_P, MBEDTLS_DHM_RFC5114_MODP_2048_G};
    HI_U8 *pu8P;
    HI_U8 *pu8G;
    HI_U8 *pu8PrivKeyA;
    HI_U8 *pu8PrivKeyB;
    HI_U8 *pu8PubKeyA;
    HI_U8 *pu8PubKeyB;
    HI_U8 *pu8SharedSecretA;
    HI_U8 *pu8SharedSecretB;
    HI_U8 *pu8Buf;

    HI_SYS_Init();

    pu8Buf = (HI_U8*)malloc(MAX_KEY_SIZE * 8);
    if(pu8Buf == HI_NULL)
    {
        HI_ERR_CIPHER("malloc for buf failed\n");
        return HI_FAILURE;
    }

    pu8P = pu8Buf;
    pu8G = pu8P + MAX_KEY_SIZE;
    pu8PrivKeyA = pu8G + MAX_KEY_SIZE;
    pu8PrivKeyB = pu8PrivKeyA + MAX_KEY_SIZE;
    pu8PubKeyA = pu8PrivKeyB + MAX_KEY_SIZE;
    pu8PubKeyB = pu8PubKeyA + MAX_KEY_SIZE;
    pu8SharedSecretA = pu8PubKeyB + MAX_KEY_SIZE;
    pu8SharedSecretB = pu8SharedSecretA + MAX_KEY_SIZE;

    ret = HI_UNF_CIPHER_Init();
    if ( HI_SUCCESS != ret )
    {
        return HI_FAILURE;
    }

    for(i=0; i<2; i++)
    {
        HI_INFO_CIPHER("\n*************************** D H - T E S T %d ***********************\n", i);

        readString(dhm_G[i], pu8G, dhm_sizes[i]);
        readString(dhm_P[i], pu8P, dhm_sizes[i]);

//        printBuffer("G", pu8G, dhm_sizes[i]);
//        printBuffer("P", pu8P, dhm_sizes[i]);

        ret = HI_UNF_CIPHER_DhGenKey(pu8G, pu8P, HI_NULL, pu8PrivKeyA, pu8PubKeyA, dhm_sizes[i]);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey A failed\n");
            return HI_FAILURE;
        }
        printBuffer("PrivKeyA", pu8PrivKeyA, dhm_sizes[i]);
        printBuffer("PubKeyA", pu8PubKeyA, dhm_sizes[i]);

        ret = HI_UNF_CIPHER_DhGenKey(pu8G, pu8P, HI_NULL, pu8PrivKeyB, pu8PubKeyB, dhm_sizes[i]);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey B failed\n");
            return HI_FAILURE;
        }
        printBuffer("PrivKeyB", pu8PrivKeyB, dhm_sizes[i]);
        printBuffer("PubKeyB", pu8PubKeyB, dhm_sizes[i]);

        ret = HI_UNF_CIPHER_DhComputeKey(pu8P, pu8PrivKeyA, pu8PubKeyB, pu8SharedSecretA, dhm_sizes[i]);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey A failed\n");
            return HI_FAILURE;
        }
        printBuffer("SharedSecretA", pu8SharedSecretA, dhm_sizes[i]);

        ret = HI_UNF_CIPHER_DhComputeKey(pu8P, pu8PrivKeyB, pu8PubKeyA, pu8SharedSecretB, dhm_sizes[i]);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CIPHER("HI_UNF_CIPHER_DhGenerateKey B failed\n");
            return HI_FAILURE;
        }
        printBuffer("SharedSecretB", pu8SharedSecretB, dhm_sizes[i]);

        if(memcmp(pu8SharedSecretA, pu8SharedSecretB, dhm_sizes[i]) != 0)
        {
            HI_ERR_CIPHER("SharedSecretA != SharedSecretB failed\n");
            printBuffer("A", pu8SharedSecretA, dhm_sizes[i]);
            printBuffer("B", pu8SharedSecretB, dhm_sizes[i]);
            return HI_FAILURE;
        }
    }

    TEST_END_PASS();

    free(pu8Buf);

    HI_UNF_CIPHER_DeInit();
    HI_SYS_DeInit();
    
    return HI_SUCCESS;
}
