/******************************************************************************

  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_cipher.c
  Version       : Initial Draft
  Author        :
  Created       :
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "hi_mpi_cipher.h"
#include "hi_unf_hdcp.h"
#include "mpi_mmz.h"
#include "hi_mpi_mem.h"
#include "mbedtls/rsa.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/sha512.h"

static HI_S32 g_CipherDevFd = -1;
static HI_S32 g_CipherInitCounter = -1;
static pthread_mutex_t   g_CipherMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t   g_HashMutex = PTHREAD_MUTEX_INITIALIZER;

#define U32_TO_POINT(addr)  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)  ((HI_U32)((HI_SIZE_T)(addr)))
#define HASH_CHANNAL_MAX_NUM   (8)
#define HI_CIPHER_LOCK()	     (void)pthread_mutex_lock(&g_CipherMutex)
#define HI_CIPHER_UNLOCK()	 (void)pthread_mutex_unlock(&g_CipherMutex)
#define HI_HASH_LOCK()		     (void)pthread_mutex_lock(&g_HashMutex)
#define HI_HASH_UNLOCK()	 (void)pthread_mutex_unlock(&g_HashMutex)

#define CIPHER_MIN_CRYPT_LEN      8
#define CIPHER_MAX_CRYPT_LEN      0xfffff

#define RSA_MIN_KEY_LEN     (128)
#define RSA_MAX_KEY_LEN     (512)

#define RSA_KEY_BITWIDTH_1024     (1024)
#define RSA_KEY_BITWIDTH_2048     (2048)
#define RSA_KEY_BITWIDTH_3072     (3072)
#define RSA_KEY_BITWIDTH_4096     (4096)

#define RSA_KEY_EXPONENT_VALUE1 (0X3)
#define RSA_KEY_EXPONENT_VALUE2 (0X10001)

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
#define  CIPHER_RNG_REG_BASE_ADDR_PHY		    (0xF8ABC000)
#else
#define  CIPHER_RNG_REG_BASE_ADDR_PHY		    (0xF8005000)
#endif

#define CHECK_CIPHER_OPEN()\
do{\
    HI_CIPHER_LOCK();\
    if (g_CipherInitCounter < 0)\
    {\
        HI_ERR_CIPHER("CIPHER is not open.\n");\
        HI_CIPHER_UNLOCK();\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
    HI_CIPHER_UNLOCK();\
}while(0)

#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("%02x ", *((str)+_i));\
    }\
    HI_PRINT("\n");\
}

#define HASH_BLOCK_SIZE		(64)
#define HASH_PAD_MAX_LEN	(64)
#define HASH1_SIGNATURE_SIZE		(20)
#define HASH256_SIGNATURE_SIZE		(32)
#define HASH_RESULT_MAX_LEN         (64)
#define HASH_RESULT_MAX_LEN_IN_WORD (16)
#define HASH_MMZ_BUF_LEN	(1*1024*1024)		//1M
#define HASH_MMZ_TAIL_LEN	(8*1024)			//8K

#define HASH_CHANNAL_MAX_NUM   (8)
#define RSA_SIGN        1
#define ASN1_HASH_SHA1    "\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"
#define ASN1_HASH_SHA224  "\x30\x2D\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x04\x05\x00\x04\x1C"
#define ASN1_HASH_SHA256  "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x01\x05\x00\x04\x20"
#define ASN1_HASH_SHA384  "\x30\x41\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x02\x05\x00\x04\x30"
#define ASN1_HASH_SHA512  "\x30\x51\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x03\x05\x00\x04\x40"

typedef struct hiHASH_INFO_S
{
    HI_BOOL   bIsUsed;
    HI_HANDLE hHandle;
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;
    HI_U32 u32TotalDataLen;
    HI_U32 u32ShaVal[HASH_RESULT_MAX_LEN_IN_WORD];
    HI_U32 u32ShaLen;
    HI_U8  u8LastBlock[HASH_BLOCK_SIZE];
    HI_U8  u8Mac[HASH_BLOCK_SIZE];
    HI_U32 u8LastBlockSize;
    HI_MMZ_BUF_S stMMZBuffer;
    HI_VOID  *pu8Pri;
}HASH_INFO_S;

static HASH_INFO_S g_stCipherHashData[HASH_CHANNAL_MAX_NUM];
static HI_MMZ_BUF_S s_stMMZBuffer;
static const HI_S8 EMPTY_L_SHA1[]   = "\xda\x39\xa3\xee\x5e\x6b\x4b\x0d\x32\x55\xbf\xef\x95\x60\x18\x90\xaf\xd8\x07\x09";
static const HI_S8 EMPTY_L_SHA224[] = "\xd1\x4a\x02\x8c\x2a\x3a\x2b\xc9\x47\x61\x02\xbb\x28\x82\x34\xc4\x15\xa2\xb0\x1f\x82\x8e\xa6\x2a\xc5\xb3\xe4\x2f";
static const HI_S8 EMPTY_L_SHA256[] = "\xe3\xb0\xc4\x42\x98\xfc\x1c\x14\x9a\xfb\xf4\xc8\x99\x6f\xb9\x24\x27\xae\x41\xe4\x64\x9b\x93\x4c\xa4\x95\x99\x1b\x78\x52\xb8\x55";
static const HI_S8 EMPTY_L_SHA384[] = "\x38\xb0\x60\xa7\x51\xac\x96\x38\x4c\xd9\x32\x7e\xb1\xb1\xe3\x6a\x21\xfd\xb7\x11\x14\xbe\x07\x43\x4c\x0c\xc7\xbf\x63\xf6\xe1\xda\x27\x4e\xde\xbf\xe7\x6f\x65\xfb\xd5\x1a\xd2\xf1\x48\x98\xb9\x5b";
static const HI_S8 EMPTY_L_SHA512[] = "\xcf\x83\xe1\x35\x7e\xef\xb8\xbd\xf1\x54\x28\x50\xd6\x6d\x80\x07\xd6\x20\xe4\x05\x0b\x57\x15\xdc\x83\xf4\xa9\x21\xd3\x6c\xe9\xce\x47\xd0\xd1\x3c\x5d\x85\xf2\xb0\xff\x83\x18\xd2\x87\x7e\xec\x2f\x63\xb9\x31\xbd\x47\x41\x7a\x81\xa5\x38\x32\x7a\xf9\x27\xda\x3e";

HI_U32 g_u32HashBaseBufferLen = HASH_MMZ_BUF_LEN;

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

/*********************************************************
 * The function below is added for AES CBC-MAC
 *
 *********************************************************/
#define MAX_DATA_LEN    (0x2000) //the max data length for encryption / decryption is  8k one time



#if 0
static HI_U8 const_Zero[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

/* For CMAC Calculation */

static HI_U8 const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* Basic Functions */
static HI_VOID xor_128(HI_U8 *a, HI_U8 *b, HI_U8 *out)
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
    return;
}

//the output is the last 16 bytes only
static HI_S32 AES_Encrypt(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output)
{
    HI_U32 u32AddrPhy = 0;
    HI_U8* pu8AddrVir = NULL;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32EncryptDataLen = 0;
    HI_U32 u32LeftDataLen = 0;
    HI_U32 i = 0;
    HI_U32 u32BlockNum = 0;

    u32AddrPhy = POINT_TO_U32(HI_MMZ_New(MAX_DATA_LEN, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32AddrPhy)
    {
        HI_ERR_CIPHER("mmz new for u32InputAddrPhy failed!\n");
        return HI_FAILURE;
    }
    pu8AddrVir = HI_MMZ_Map(u32AddrPhy, 0);
    if( NULL == pu8AddrVir )
    {
        HI_MMZ_Delete(u32AddrPhy);
        HI_ERR_CIPHER("mmz map for pu8InputAddrVir failed!\n");
        return HI_FAILURE;
    }

    memset(pu8AddrVir, 0, MAX_DATA_LEN);

    u32LeftDataLen = datalen;
    u32BlockNum = (datalen + MAX_DATA_LEN - 1) / MAX_DATA_LEN;
    for(i = 0; i < u32BlockNum; i++)
    {
        u32EncryptDataLen = u32LeftDataLen >= MAX_DATA_LEN ? MAX_DATA_LEN : u32LeftDataLen;
        u32LeftDataLen -= u32EncryptDataLen;
        memcpy(pu8AddrVir, input + i * MAX_DATA_LEN, u32EncryptDataLen);
        Ret = HI_MPI_CIPHER_Encrypt(hCipherHandle, u32AddrPhy, u32AddrPhy, u32EncryptDataLen);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Cipher encrypt failed!\n");
            goto CIPHER_RELEASE_BUF;
        }
    }
    memcpy(output, pu8AddrVir + u32EncryptDataLen - 16, 16);

CIPHER_RELEASE_BUF:
    HI_MMZ_Unmap(u32AddrPhy);
    HI_MMZ_Delete(u32AddrPhy);

    return Ret;
}

static HI_S32 generate_subkey(HI_HANDLE hCipherHandle, HI_U8 *K1, HI_U8 *K2)
{
    HI_U8 L[16];
    HI_U8 Z[16];
    HI_U8 tmp[16];
    HI_U32 u32DataLen = 16;
    HI_S32 Ret = HI_SUCCESS;

    memset(tmp, 0x0, sizeof(tmp));
    memset(L, 0x0, sizeof(L));
    memset(Z, 0x0, sizeof(Z));

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

static HI_S32 Cipher_HashMmzInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 i;

    memset(&s_stMMZBuffer, 0, sizeof(HI_MMZ_BUF_S));
    memcpy(s_stMMZBuffer.bufname, "HASH_DATA", 9);
    for(i=0; i<10; i++)
	{
		s_stMMZBuffer.bufsize = g_u32HashBaseBufferLen + HASH_MMZ_TAIL_LEN;
		ret = HI_MPI_MMZ_Malloc(&s_stMMZBuffer);
		if(ret == HI_SUCCESS)
		{
			break;
		}
		else
		{
			g_u32HashBaseBufferLen /= 2;
		}
	}

	if(ret != HI_SUCCESS)
	{
		HI_ERR_CIPHER("Error: Get mmz buffer for hash failed, ret = 0x%x, buffer size 0x%x!\n",
			ret, s_stMMZBuffer.bufsize);
    }

    HI_INFO_CIPHER("g_u32HashBaseBufferLen: 0x%x\n", g_u32HashBaseBufferLen);

	return ret;
}

static HI_VOID Cipher_HashMmzDeInit(HI_VOID)
{

	(HI_VOID)HI_MPI_MMZ_Free(&s_stMMZBuffer);
	memset(&s_stMMZBuffer, 0, sizeof(s_stMMZBuffer));
}

static HI_U32 HashMsgPadding(HI_U8 *pu8Msg, HI_U32 u32ByteLen, HI_U32 u32TotalLen)
{
    HI_U32 u32Tmp = 0;
    HI_U32 u32PaddingLen;

    u32Tmp = u32TotalLen % 64;
    /* 56 = 64 - 8, 120 = 56 + 64 */
    u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
    /* add 8 bytes fix data length */
    u32PaddingLen += 8;

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    pu8Msg[u32ByteLen++] = 0x80;
    memset(&pu8Msg[u32ByteLen], 0, u32PaddingLen - 1 - 8);
    u32ByteLen+=u32PaddingLen - 1 - 8;

    /* write 8 bytes fix data length */
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 29)&0x07);
	pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 21)&0xff);
	pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 13)&0xff);
	pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 5)&0xff);
	pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen << 3)&0xff);

    return u32ByteLen;
}

static HI_S32 CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S stHashData;
    HI_U32 u32SoftId;
    HASH_INFO_S *pstHashInfo;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    for(u32SoftId=0; u32SoftId<HASH_CHANNAL_MAX_NUM; u32SoftId++)
    {
        if (!g_stCipherHashData[u32SoftId].bIsUsed)
        {
            break;
        }
    }

    if(u32SoftId >= HASH_CHANNAL_MAX_NUM)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        HI_HASH_UNLOCK();
        return HI_FAILURE;
    }

    pstHashInfo = &g_stCipherHashData[u32SoftId];
	memset(pstHashInfo, 0, sizeof(HASH_INFO_S));
    memset(&stHashData, 0, sizeof(CIPHER_HASH_DATA_S));
	pstHashInfo->stMMZBuffer = s_stMMZBuffer;
    pstHashInfo->enShaType = pstHashAttr->eShaType;

	if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashAttr->eShaType)
	  || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType ))
	{
	    stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
        pstHashInfo->u32ShaLen = HASH1_SIGNATURE_SIZE;
        pstHashInfo->u32ShaVal[0] = 0x01234567;
        pstHashInfo->u32ShaVal[1] = 0x89abcdef;
        pstHashInfo->u32ShaVal[2] = 0xfedcba98;
        pstHashInfo->u32ShaVal[3] = 0x76543210;
        pstHashInfo->u32ShaVal[4] = 0xf0e1d2c3;

        ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHINIT, &stHashData);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash initial failed!\n");
            HI_HASH_UNLOCK();
            return ret;
        }
	}
	else if ( (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashAttr->eShaType)
		 || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType))
	{
	    stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
        pstHashInfo->u32ShaLen = HASH256_SIGNATURE_SIZE;
        pstHashInfo->u32ShaVal[0] = 0x67e6096a;
        pstHashInfo->u32ShaVal[1] = 0x85ae67bb;
        pstHashInfo->u32ShaVal[2] = 0x72f36e3c;
        pstHashInfo->u32ShaVal[3] = 0x3af54fa5;
        pstHashInfo->u32ShaVal[4] = 0x7f520e51;
        pstHashInfo->u32ShaVal[5] = 0x8c68059b;
        pstHashInfo->u32ShaVal[6] = 0xabd9831f;
        pstHashInfo->u32ShaVal[7] = 0x19cde05b;

        ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHINIT, &stHashData);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash initial failed!\n");
            HI_HASH_UNLOCK();
            return ret;
        }
	}
	else if(HI_UNF_CIPHER_HASH_TYPE_SHA224 == pstHashAttr->eShaType)
    {
	    stHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA224;
        pstHashInfo->u32ShaLen = 28;
        pstHashInfo->u32ShaVal[0] = 0xd89e05c1;
        pstHashInfo->u32ShaVal[1] = 0x07d57c36;
        pstHashInfo->u32ShaVal[2] = 0x17dd7030;
        pstHashInfo->u32ShaVal[3] = 0x39590ef7;
        pstHashInfo->u32ShaVal[4] = 0x310bc0ff;
        pstHashInfo->u32ShaVal[5] = 0x11155868;
        pstHashInfo->u32ShaVal[6] = 0xa78ff964;
        pstHashInfo->u32ShaVal[7] = 0xa44ffabe;

        ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHINIT, &stHashData);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash initial failed!\n");
            HI_HASH_UNLOCK();
            return ret;
        }
    }
    else if((HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashAttr->eShaType) )
    {
        mbedtls_sha512_context *ctx;

        ctx = (mbedtls_sha512_context *)malloc(sizeof(mbedtls_sha512_context));
        if (ctx == HI_NULL)
        {
            HI_ERR_CIPHER("Malloc memory for ctx failed.\n");
	        HI_HASH_UNLOCK();
            return HI_FAILURE;
        }

        mbedtls_sha512_init(ctx);
        mbedtls_sha512_starts( ctx, HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashAttr->eShaType);
        pstHashInfo->pu8Pri = (HI_VOID*)ctx;
    }
	else
	{
	    HI_ERR_CIPHER("Invalid sha type 0x%x.\n", pstHashAttr->eShaType);
        HI_HASH_UNLOCK();
        return HI_FAILURE;
	}

    pstHashInfo->bIsUsed = HI_TRUE;
    *pHashHandle = u32SoftId;

    HI_HASH_UNLOCK();

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];
	HI_U32 u32Tmp = 0;
    HI_U32 u32TotalSize;
    HI_U32 u32CopySize;
    HI_U32 u32BufInUsedLen = 0;
    CIPHER_HASH_DATA_S stHashData;
	HI_U32 i = 0;

    CHECK_CIPHER_OPEN();

	if (0 == u32InputDataLen)
	{
	    return HI_SUCCESS;
	}

    if((HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashInfo->enShaType) )
    {
        mbedtls_sha512_context *ctx = (mbedtls_sha512_context *)pstHashInfo->pu8Pri;

        mbedtls_sha512_update( ctx, pu8InputData, u32InputDataLen);
        return HI_SUCCESS;
    }

    HI_HASH_LOCK();

    pstHashInfo->stMMZBuffer.bufsize = 0;
	pstHashInfo->u32TotalDataLen += u32InputDataLen;
    u32TotalSize = pstHashInfo->u8LastBlockSize + u32InputDataLen;
    if( (u32InputDataLen < HASH_BLOCK_SIZE) && (u32TotalSize < HASH_BLOCK_SIZE))
    {
        memcpy(pstHashInfo->u8LastBlock+pstHashInfo->u8LastBlockSize, pu8InputData, u32InputDataLen);
        pstHashInfo->u8LastBlockSize+=u32InputDataLen;
        HI_HASH_UNLOCK();
	    return HI_SUCCESS;
    }
    else
    {
        memcpy(pstHashInfo->stMMZBuffer.user_viraddr, pstHashInfo->u8LastBlock, pstHashInfo->u8LastBlockSize);
        pstHashInfo->stMMZBuffer.bufsize = pstHashInfo->u8LastBlockSize;

        /* save tail data */
        memset(pstHashInfo->u8LastBlock, 0, HASH_BLOCK_SIZE);
        pstHashInfo->u8LastBlockSize = (u32InputDataLen + pstHashInfo->stMMZBuffer.bufsize) % HASH_BLOCK_SIZE;
        memcpy(pstHashInfo->u8LastBlock, pu8InputData + (u32InputDataLen - pstHashInfo->u8LastBlockSize),
            pstHashInfo->u8LastBlockSize);
    }

    u32TotalSize  = u32InputDataLen - pstHashInfo->u8LastBlockSize;
    u32Tmp = (u32TotalSize + pstHashInfo->stMMZBuffer.bufsize + g_u32HashBaseBufferLen - 1) / g_u32HashBaseBufferLen;
    /* Send data down piece by piece */
    for ( i = 0 ; i < u32Tmp; i++ )
    {
        u32CopySize = g_u32HashBaseBufferLen - pstHashInfo->stMMZBuffer.bufsize;
        if (u32CopySize > (u32TotalSize - u32BufInUsedLen))
        {
            u32CopySize = u32TotalSize - u32BufInUsedLen;
        }
        HI_INFO_CIPHER("g_u32HashBaseBufferLen: 0x%x, u32TotalSize:0x%x, u32BufInUsedLen: 0x%x, buffersize: 0x%x\n",
            g_u32HashBaseBufferLen, u32TotalSize, u32BufInUsedLen, pstHashInfo->stMMZBuffer.bufsize);
        memcpy((HI_U8 *)pstHashInfo->stMMZBuffer.user_viraddr + pstHashInfo->stMMZBuffer.bufsize,
		       pu8InputData + u32BufInUsedLen, u32CopySize);
	    pstHashInfo->stMMZBuffer.bufsize += u32CopySize;
        u32BufInUsedLen+=u32CopySize;
        stHashData.enShaType = pstHashInfo->enShaType;
		stHashData.u32DataLen = pstHashInfo->stMMZBuffer.bufsize;
        stHashData.u32DataPhy = pstHashInfo->stMMZBuffer.phyaddr;
        memcpy(stHashData.u32ShaVal, pstHashInfo->u32ShaVal, sizeof(stHashData.u32ShaVal));
		pstHashInfo->stMMZBuffer.bufsize = 0;
		ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHUPDATE, &stHashData);
	    if(ret != HI_SUCCESS)
	    {
	        HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
            pstHashInfo->bIsUsed = HI_FALSE;
            HI_HASH_UNLOCK();
	        return ret;
	    }
       memcpy(pstHashInfo->u32ShaVal, stHashData.u32ShaVal, sizeof(stHashData.u32ShaVal));
    }

    HI_HASH_UNLOCK();

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];
    CIPHER_HASH_DATA_S stHashData;
	HI_U32 u32Tmp = 0;

    CHECK_CIPHER_OPEN();
    if((HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashInfo->enShaType) )
    {
        mbedtls_sha512_context *ctx = (mbedtls_sha512_context *)pstHashInfo->pu8Pri;

        mbedtls_sha512_finish( ctx, pu8OutputHash);
        mbedtls_sha512_free( ctx);
        free(pstHashInfo->pu8Pri);
        pstHashInfo->pu8Pri = HI_NULL;
        pstHashInfo->bIsUsed = HI_FALSE;

        return HI_SUCCESS;
    }

    HI_HASH_LOCK();

    memcpy(pstHashInfo->stMMZBuffer.user_viraddr, pstHashInfo->u8LastBlock, pstHashInfo->u8LastBlockSize);
    pstHashInfo->stMMZBuffer.bufsize = pstHashInfo->u8LastBlockSize;
    memset(pstHashInfo->u8LastBlock, 0, HASH_BLOCK_SIZE);
    pstHashInfo->u8LastBlockSize = 0;

	u32Tmp = HashMsgPadding(pstHashInfo->stMMZBuffer.user_viraddr, pstHashInfo->stMMZBuffer.bufsize, pstHashInfo->u32TotalDataLen);

    stHashData.enShaType = pstHashInfo->enShaType;
    stHashData.u32DataLen = u32Tmp;
    stHashData.u32DataPhy = pstHashInfo->stMMZBuffer.phyaddr;
    memcpy(stHashData.u32ShaVal, pstHashInfo->u32ShaVal, sizeof(stHashData.u32ShaVal));
    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHFINAL, &stHashData);

    memcpy(pu8OutputHash, stHashData.u32ShaVal, pstHashInfo->u32ShaLen);

    pstHashInfo->bIsUsed = HI_FALSE;

    HI_HASH_UNLOCK();

    return ret;
}

static HI_S32 CIPHER_CbcMacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    HI_HANDLE hCipher;
    HI_U32 u32SoftId;
    HASH_INFO_S *pstHashInfo;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    for(u32SoftId=0; u32SoftId<HASH_CHANNAL_MAX_NUM; u32SoftId++)
    {
        if (!g_stCipherHashData[u32SoftId].bIsUsed)
        {
            break;
        }
    }

    if(u32SoftId >= HASH_CHANNAL_MAX_NUM)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        HI_HASH_UNLOCK();
        return HI_FAILURE;
    }

    pstHashInfo = &g_stCipherHashData[u32SoftId];
	memset(pstHashInfo, 0, sizeof(HASH_INFO_S));
	pstHashInfo->stMMZBuffer = s_stMMZBuffer;
    pstHashInfo->enShaType = HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC;
    pstHashInfo->bIsUsed = HI_TRUE;

    HI_HASH_UNLOCK();

    memset(&stCipherAttr, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = HI_MPI_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Create cipher handle failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return ret;
    }

    pstHashInfo->hHandle = hCipher;
    *pHashHandle = u32SoftId;

    memset(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    stCipherCtrl.bKeyByCA = HI_TRUE;
    stCipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_IRDETO_HCA;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    stCipherCtrl.stChangeFlags.bit1IV = HI_TRUE;

    ret = HI_MPI_CIPHER_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Configure cipher handle failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return ret;
    }

    return ret;
}

static HI_S32 CIPHER_CbcMacUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];

    if(u32InputDataLen == 0)
    {
        return HI_SUCCESS;
    }

    if(u32InputDataLen % 16 != 0)
    {
        HI_ERR_CIPHER("Invalid parameter, u32InputDataLen should be aligned with 16 byte!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = AES_Encrypt(pstHashInfo->hHandle, pu8InputData, u32InputDataLen, pstHashInfo->u8Mac);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CBC-MAC update failed!\n");
        pstHashInfo->bIsUsed = HI_FALSE;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 CIPHER_CbcMacFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];

    CHECK_CIPHER_OPEN();

    memcpy(pu8OutputHash, pstHashInfo->u8Mac, 16);
    ret = HI_MPI_CIPHER_DestroyHandle(pstHashInfo->hHandle);

    pstHashInfo->bIsUsed = HI_FALSE;

    return ret;
}

static HI_S32 CIPHER_HmacKeyInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_U8 au8Hmackey[HASH_BLOCK_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    HI_HANDLE hHash = 0;

    /*key length is less than 64bytes, copy directly*/
    if(pstHashAttr->u32HMACKeyLen <= HASH_BLOCK_SIZE)
    {
        memcpy(au8Hmackey, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
        return HI_SUCCESS;
    }

    /*key length more than 64bytes, calcute the hash result*/
    ret = CIPHER_HashInit(pstHashAttr, &hHash)
	      || CIPHER_HashUpdate(hHash, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen)
		  || CIPHER_HashFinal(hHash,au8Hmackey);

    return ret;
}

static HI_S32 CIPHER_HmacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 key_pad[HASH_BLOCK_SIZE];
    HASH_INFO_S *pstHashInfo;
	HI_U32 i = 0;

    if( (NULL == pstHashAttr)
     || (NULL == pHashHandle)
     || (pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT)
     || (NULL == pstHashAttr->pu8HMACKey)
     || (0 == pstHashAttr->u32HMACKeyLen))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

	/* Init hmac key */
    memset(key_pad, 0, sizeof(key_pad));
    ret = CIPHER_HmacKeyInit(pstHashAttr, key_pad);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Hmac key initial failed!\n");
		return HI_FAILURE;
	}

	/* hash i_key_pad and message start */
	ret = CIPHER_HashInit(pstHashAttr, pHashHandle);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("hash i_key_pad and message start failed!\n");
		return HI_FAILURE;
	}
    pstHashInfo = (HASH_INFO_S *)&g_stCipherHashData[*pHashHandle];
    memcpy(pstHashInfo->u8Mac, key_pad, HASH_BLOCK_SIZE);

	/* generate i_key_pad */
    for(i=0; i < HASH_BLOCK_SIZE; i++)
    {
        key_pad[i] ^= 0x36;
    }

	/* hash i_key_pad update */
	ret = CIPHER_HashUpdate(*pHashHandle, key_pad, HASH_BLOCK_SIZE);

    return ret;
}

static HI_S32 CIPHER_HmacUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;

	ret = CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);

    return ret;
}

static HI_S32 CIPHER_HmacFinal(HI_HANDLE hHashHandle, HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo;
	HI_HANDLE hHash = HI_INVALID_HANDLE;
	HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 hash_sum_1[HASH_RESULT_MAX_LEN];
    HI_U8 key_pad[HASH_BLOCK_SIZE];
	HI_U32 u32ShaSize = 0;
    HI_U32 i;

    pstHashInfo = &g_stCipherHashData[hHashHandle];

    memset(&stHashAttr, 0, sizeof(stHashAttr));
	stHashAttr.eShaType = pstHashInfo->enShaType;
    memcpy(key_pad, pstHashInfo->u8Mac, HASH_BLOCK_SIZE);

    /* hash i_key_pad+message finished */
    ret = CIPHER_HashFinal(hHashHandle, hash_sum_1);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final i_key_pad+message failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* generate o_key_pad */
    for(i=0; i < HASH_BLOCK_SIZE; i++)
    {
        key_pad[i] ^= 0x5c;
    }

	if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == stHashAttr.eShaType )
	{
	    u32ShaSize = HASH1_SIGNATURE_SIZE;
	}
	else
	{
		u32ShaSize = HASH256_SIGNATURE_SIZE;
	}

    /* hash o_key_pad+hash_sum_1 start */
    ret = CIPHER_HashInit(&stHashAttr, &hHash)
	      || CIPHER_HashUpdate(hHash, key_pad, HASH_BLOCK_SIZE)
		  || CIPHER_HashUpdate(hHash, (HI_U8 *)hash_sum_1, u32ShaSize)
		  || CIPHER_HashFinal(hHash, pu8Output);

    return ret;
}

HI_S32 HI_MPI_CIPHER_Init(HI_VOID)
{
    HI_U32 ret;

    HI_CIPHER_LOCK();

    if (g_CipherInitCounter > 0)
    {
        g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    g_CipherDevFd = open("/dev/"UMAP_DEVNAME_CIPHER, O_RDWR, 0);
    if (g_CipherDevFd < 0)
    {
        HI_FATAL_CIPHER("Open CIPHER err.\n");
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    ret = Cipher_HashMmzInit();
    if (ret != HI_SUCCESS)
    {
        close(g_CipherDevFd);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    memset(&g_stCipherHashData, 0, sizeof(g_stCipherHashData));

    g_CipherInitCounter = 1;
    HI_CIPHER_UNLOCK();

    return ret;
}

HI_S32 HI_MPI_CIPHER_DeInit(HI_VOID)
{
    HI_CIPHER_LOCK();

    if(g_CipherInitCounter > 0)
    {
        g_CipherInitCounter--;
    }

    if(g_CipherInitCounter != 0)
    {
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    close(g_CipherDevFd);

    Cipher_HashMmzDeInit();

    g_CipherInitCounter = -1;

    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_HANDLE_S stCIHandle = {0};

    CHECK_CIPHER_OPEN();

    if ( ( NULL == phCipher ) || ( NULL == pstCipherAttr ) )
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    stCIHandle.stCipherAtts.enCipherType = pstCipherAttr->enCipherType;
    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_CREATEHANDLE, &stCIHandle);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *phCipher = stCIHandle.hCIHandle;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    HI_S32 Ret;

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_DESTROYHANDLE, &hCipher);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_S32 Ret;
    CIPHER_Config_CTRL configdata;

    CHECK_CIPHER_OPEN();

    if (NULL == pstCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if((pstCtrl->enAlg > HI_UNF_CIPHER_ALG_AES))
    {
        HI_ERR_CIPHER("para setCIPHER alg is invalid.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pstCtrl->enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
        || (pstCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        || (pstCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        HI_ERR_CIPHER("para set CIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memcpy(&configdata.CIpstCtrl, pstCtrl, sizeof(HI_UNF_CIPHER_CTRL_S));
    configdata.CIHandle=hCipher;

    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_CONFIGHANDLE, &configdata);

    return Ret;
}

HI_S32 HI_MPI_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl)
{
    CIPHER_Config_CTRL configdata;

    CHECK_CIPHER_OPEN();

    if (NULL == pstExCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (pstExCtrl->enAlg > HI_UNF_CIPHER_ALG_AES)
    {
        HI_ERR_CIPHER("para setCIPHER alg is invalid.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (NULL == pstExCtrl->pParam)
    {
        HI_ERR_CIPHER("para pstCtrl param is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pstExCtrl->enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
        || (pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        || (pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        HI_ERR_CIPHER("para set CIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&configdata, 0, sizeof(CIPHER_Config_CTRL));

    configdata.CIHandle= hCipher;
    configdata.CIpstCtrl.enAlg = pstExCtrl->enAlg;
    configdata.CIpstCtrl.enWorkMode = pstExCtrl->enWorkMode;
    configdata.CIpstCtrl.bKeyByCA = pstExCtrl->bKeyByCA;

    /*****************************************************************************
     * for AES, the pointer should point to HI_UNF_CIPHER_CTRL_AES_S;
     * for AES_CCM or AES_GCM, the pointer should point to HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S;
     * for DES, the pointer should point to HI_UNF_CIPHER_CTRL_DES_S;
     * for 3DES, the pointer should point to HI_UNF_CIPHER_CTRL_3DES_S;
     * for SM1, the pointer should point to HI_UNF_CIPHER_CTRL_SM1_S;
     * for SM4, the pointer should point to HI_UNF_CIPHER_CTRL_SM4_S;
    */
    switch(pstExCtrl->enAlg)
    {
    case HI_UNF_CIPHER_ALG_DES:
    {
        HI_UNF_CIPHER_CTRL_DES_S *pstDesCtrl = (HI_UNF_CIPHER_CTRL_DES_S *)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pstDesCtrl->u32Key, 8);
        memcpy(configdata.CIpstCtrl.u32IV, pstDesCtrl->u32IV, 8);
        configdata.CIpstCtrl.enBitWidth = pstDesCtrl->enBitWidth;
        configdata.CIpstCtrl.stChangeFlags = pstDesCtrl->stChangeFlags;
        configdata.CIpstCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DEFAULT;
        break;
    }
    case HI_UNF_CIPHER_ALG_3DES:
    {
        HI_UNF_CIPHER_CTRL_3DES_S *pst3DesCtrl = (HI_UNF_CIPHER_CTRL_3DES_S*)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pst3DesCtrl->u32Key, 24);
        memcpy(configdata.CIpstCtrl.u32IV, pst3DesCtrl->u32IV, 8);
        configdata.CIpstCtrl.enBitWidth = pst3DesCtrl->enBitWidth;
        configdata.CIpstCtrl.enKeyLen = pst3DesCtrl->enKeyLen;
        configdata.CIpstCtrl.stChangeFlags = pst3DesCtrl->stChangeFlags;
        break;
    }
    case HI_UNF_CIPHER_ALG_AES:
    {
        HI_UNF_CIPHER_CTRL_AES_S *pstAesCtrl = (HI_UNF_CIPHER_CTRL_AES_S*)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pstAesCtrl->u32EvenKey, 32);
        memcpy(configdata.CIpstCtrl.u32IV, pstAesCtrl->u32IV, 16);
        configdata.CIpstCtrl.enBitWidth = pstAesCtrl->enBitWidth;
        configdata.CIpstCtrl.enKeyLen = pstAesCtrl->enKeyLen;
        configdata.CIpstCtrl.stChangeFlags = pstAesCtrl->stChangeFlags;
        break;
    }
    default:
        HI_ERR_CIPHER("para set CIPHER alg is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return ioctl(g_CipherDevFd, CMD_CIPHER_CONFIGHANDLE, &configdata);
}

HI_S32 HI_MPI_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 Ret;
    CIPHER_DATA_S CIdata;

    CHECK_CIPHER_OPEN();

    if ( u32ByteLength < CIPHER_MIN_CRYPT_LEN)
    {
        HI_ERR_CIPHER("u32ByteLength(0x%x) is invalid.\n", u32ByteLength);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPT, &CIdata);

    return Ret;
}

HI_S32 HI_MPI_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 Ret;
    CIPHER_DATA_S CIdata;

    CHECK_CIPHER_OPEN();

    if ( u32ByteLength < CIPHER_MIN_CRYPT_LEN)
    {
        HI_ERR_CIPHER("u32ByteLength(0x%x) is invalid.\n", u32ByteLength);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength = u32ByteLength;
    CIdata.CIHandle=hCipher;

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_DECRYPT, &CIdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_S32 Ret;
    HI_U32 chnid;
    HI_U32 i;
    CIPHER_PKG_S stPkg;
    HI_UNF_CIPHER_DATA_S *pPkgTmp;

    CHECK_CIPHER_OPEN();

    if (pstDataPkg == HI_NULL)
    {
        HI_ERR_CIPHER("invalid point.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    chnid=hCipher&0x00ff;
    if ( 0 == chnid )
    {
        HI_ERR_CIPHER("invalid chnid 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    stPkg.pu8Pkg = pstDataPkg;
    stPkg.CIHandle = hCipher;
    stPkg.u32PkgNum = u32DataPkgNum;

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_ENCRYPTMULTI, &stPkg);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_S32 Ret;
    HI_U32 chnid;
    HI_U32 i;
    CIPHER_PKG_S stPkg;
    HI_UNF_CIPHER_DATA_S *pPkgTmp;

    CHECK_CIPHER_OPEN();

    if (pstDataPkg == HI_NULL)
    {
        HI_ERR_CIPHER("invalid point.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    chnid=hCipher&0x00ff;
    if ( 0 == chnid )
    {
        HI_ERR_CIPHER("invalid chnid 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    stPkg.pu8Pkg = pstDataPkg;
    stPkg.CIHandle = hCipher;
    stPkg.u32PkgNum = u32DataPkgNum;

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_DECRYPTMULTI, &stPkg);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_S32 Ret;
    CIPHER_Config_CTRL  configdata;

    CHECK_CIPHER_OPEN();

    configdata.CIHandle = hCipherHandle;
    memset(&configdata.CIpstCtrl, 0, sizeof(configdata.CIpstCtrl));

    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_GETHANDLECONFIG, &configdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    memcpy(pstCtrl, &configdata.CIpstCtrl, sizeof(configdata.CIpstCtrl));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_CENCDecrypt(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_U8 *pu8IV,
                            HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr, HI_U32 u32ByteLength,
                            HI_U32 u32FirstEncryptOffset,
                            HI_UNF_CIPHER_SUBSAMPLE_S *pstSubSample, HI_U32 u32SubsampleNum)
{
    CIPHER_CENC_DECRYPT_S stCencDecrypt;

    if ((pu8Key == HI_NULL) || (pu8IV == HI_NULL) || (pstSubSample == HI_NULL)
        || (u32SubsampleNum == 0) || (u32ByteLength == 0))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_FAILURE;
    }

    memset(&stCencDecrypt, 0,  sizeof(stCencDecrypt));
    stCencDecrypt.hCipher = hCipher;
    memcpy(&stCencDecrypt.u8Key, pu8Key, 16);
    memcpy(&stCencDecrypt.u8IV, pu8IV, 16);
    stCencDecrypt.u32NonSecInputPhyAddr = u32NonSecInPhyAddr;
    stCencDecrypt.u32SecOutputPhyAddr = u32SecOutPhyAddr;
    stCencDecrypt.u32ByteLength = u32ByteLength;
    stCencDecrypt.u32FirstEncryptOffset = u32FirstEncryptOffset;
    stCencDecrypt.pstSubSample = pstSubSample;
    stCencDecrypt.u32SubsampleNum = u32SubsampleNum;

    return ioctl(g_CipherDevFd, CMD_CIPHER_CENC_DECRYPT, &stCencDecrypt);
}

HI_S32 HI_MPI_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                                        HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    HI_U8 X[16], M_last[16], padded[16];
    static HI_U8 K1[16] = {0};
	static HI_U8 K2[16] = {0};
    HI_U32 n, i, flag;
    HI_U8 u8TmpBuf[16];
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    static HI_BOOL bIsFirstBlock = HI_TRUE;

    CHECK_CIPHER_OPEN();

    if((NULL == pOutputMAC) || (NULL == pInputData))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&stCipherCtrl, 0, sizeof(stCipherCtrl));
    memset(u8TmpBuf, 0, sizeof(u8TmpBuf));
    memset(X, 0, sizeof(X));
    memset(M_last, 0, sizeof(M_last));
    memset(padded, 0, sizeof(padded));

    if(bIsFirstBlock) //if first block, reset the configure handle and generate the subkey again
    {
        Ret = HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, &stCipherCtrl);
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        memset ((HI_U8*)stCipherCtrl.u32IV, 0, 16);
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
        memset ((HI_U8*)stCipherCtrl.u32IV, 0, 16);
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

HI_S32 HI_MPI_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    if((NULL == pstHashAttr) || (NULL == pHashHandle))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

	if ((HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashAttr->eShaType)
	    ||(HI_UNF_CIPHER_HASH_TYPE_SHA224 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashAttr->eShaType)
        ||(HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashAttr->eShaType))
	{
	    return CIPHER_HashInit(pstHashAttr, pHashHandle);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType))
    {
        return CIPHER_HmacInit(pstHashAttr, pHashHandle);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstHashAttr->eShaType)
    {
        return CIPHER_CbcMacInit(pstHashAttr, pHashHandle);
    }

    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_FAILURE;
    HASH_INFO_S *pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    if((NULL == pu8InputData) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

	if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashInfo->enShaType)
	    ||(HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA224 == pstHashInfo->enShaType)
        ||(HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashInfo->enShaType))
	{
		ret = CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashInfo->enShaType))
    {
        ret = CIPHER_HmacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstHashInfo->enShaType)
    {
        ret = CIPHER_CbcMacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_FAILURE;
    HASH_INFO_S *pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    if((NULL == pu8OutputHash) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

		if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashInfo->enShaType)
	    ||(HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA224 == pstHashInfo->enShaType)
        ||(HI_UNF_CIPHER_HASH_TYPE_SHA384 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA512 == pstHashInfo->enShaType))
	{
		ret =  CIPHER_HashFinal(hHashHandle, pu8OutputHash);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashInfo->enShaType))
    {
        ret =  CIPHER_HmacFinal(hHashHandle, pu8OutputHash);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstHashInfo->enShaType)
    {
        ret =  CIPHER_CbcMacFinal(hHashHandle, pu8OutputHash);
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    HI_S32 Ret;
    CIPHER_CBCMAC_DATA_S CIdata;

    CHECK_CIPHER_OPEN();

    if (pu8RefCbcMac == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (u32AppLen % 16 != 0)
    {
        HI_ERR_CIPHER("Invalid parameter, u32AppLen should be algined with 16 byte!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memcpy(CIdata.u8RefCbcMac, pu8RefCbcMac, 16);
    CIdata.u32AppLen = u32AppLen;

    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_CBCMAC_AUTH, &CIdata);

    return Ret;
}


HI_S32 HI_MPI_CIPHER_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pstHdcpKey, HI_BOOL bIsUseOTPRootKey, HI_U8 u8OutEncryptKey[HDCP_KEY_CHIP_FILE_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HDCP_KEY_TRANSFER_S stDecryptHdcpKeyTransfer;

    CHECK_CIPHER_OPEN();

    if ( NULL == pstHdcpKey || NULL == u8OutEncryptKey)
    {
        HI_ERR_CIPHER("Invalid param , null pointer!\n");
        return HI_FAILURE;
    }

    memset(&stDecryptHdcpKeyTransfer, 0x0, sizeof(CIPHER_HDCP_KEY_TRANSFER_S));
    stDecryptHdcpKeyTransfer.bIsUseOTPRootKey = bIsUseOTPRootKey;
    memcpy(&stDecryptHdcpKeyTransfer.stHdcpKey, pstHdcpKey, sizeof(HI_UNF_HDCP_HDCPKEY_S));

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPTHDCPKEY, &stDecryptHdcpKeyTransfer);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("cmd encrypt hdcpkey failed!\n");
        return HI_FAILURE;
    }

    memcpy(u8OutEncryptKey, stDecryptHdcpKeyTransfer.u8FlashEncryptedHdcpKey, HDCP_KEY_CHIP_FILE_SIZE);

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_LoadHDCPKey(HI_U8 *pu8EncryptedHDCPKey, HI_U32 u32Len)
{
    HI_S32 ret = HI_SUCCESS;
    HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S stHdcpKey;

    CHECK_CIPHER_OPEN();

    if ( (NULL == pu8EncryptedHDCPKey) || (HDCP_KEY_CHIP_FILE_SIZE != u32Len) )
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    memset(&stHdcpKey, 0, sizeof(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S));
    memcpy(stHdcpKey.u8Key, pu8EncryptedHDCPKey, u32Len);
    stHdcpKey.u32KeyLen = u32Len;
    stHdcpKey.enHDCPVersion = HI_DRV_HDCP_VERIOSN_1x;
    stHdcpKey.enHDCPKeyType = HI_DRV_HDCPKEY_TX0;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_LOADHDCPKEY, &stHdcpKey);

    return ret;
}

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_RNG_S stRNG;

    CHECK_CIPHER_OPEN();

    if (NULL == pu32RandomNumber)
    {
        HI_ERR_CIPHER("Input pointer is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    stRNG.u32RNG = 0;
    stRNG.u32TimeOutUs = u32TimeOutUs;
    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_GETRANDOMNUMBER, &stRNG);

    *pu32RandomNumber = stRNG.u32RNG;

    return Ret;
}

static HI_S32 RSA_GetAttr(HI_U32 u32SchEme,
                          HI_U16 u16NLen,
                          HI_U32 *pu32HLen,
                          HI_U32 *pu32KeyLen,
                          HI_UNF_CIPHER_HASH_TYPE_E *pstenHashType)
{
    HI_S32 ret = HI_SUCCESS;

    if (RSA_MIN_KEY_LEN <= u16NLen && RSA_MAX_KEY_LEN >= u16NLen)
    {
        *pu32KeyLen = u16NLen;
    }
    else
    {
        HI_ERR_CIPHER("u16NLen(0x%x) is invalid\n", u16NLen);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    *pu32HLen = 0;
    *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_BUTT;

    switch(u32SchEme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        *pu32HLen = 0;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_BUTT;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        *pu32HLen = 20;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
        *pu32HLen = 28;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA224;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        *pu32HLen = 32;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        *pu32HLen = 48;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA384;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
        *pu32HLen = 64;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA512;
        break;
    default:
        HI_ERR_CIPHER("RSA scheme (0x%x) is invalid.\n", u32SchEme);
        ret = HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}

static HI_S32 RSA_PKCS1_MGF1(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                             HI_U8  *pu8Seed,
                             HI_U32 u32Seedlen,
                             HI_U8 *pu8Mask, HI_U32 u32MaskLen)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 i,j, u32Outlen = 0;
    HI_U8 u8Cnt[4];
    HI_U8 u8Md[64];
    HI_U32 u32MdLen = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

    /*PKCS#1 V2.1 only use sha1 function, Others allow for future expansion*/
    stHashAttr.eShaType = enHashType;
    if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA1)
    {
        u32MdLen = 20;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA224)
    {
        u32MdLen = 28;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA256)
    {
        u32MdLen = 32;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA384)
    {
        u32MdLen = 48;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA512)
    {
        u32MdLen = 64;
    }
    else
    {
        HI_ERR_CIPHER("hash type is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    for (i = 0; u32Outlen < u32MaskLen; i++)
    {
        u8Cnt[0] = (HI_U8)((i >> 24) & 0xFF);
        u8Cnt[1] = (HI_U8)((i >> 16) & 0xFF);
        u8Cnt[2] = (HI_U8)((i >> 8)) & 0xFF;
        u8Cnt[3] = (HI_U8)(i & 0xFF);

        Ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle)
		      || HI_MPI_CIPHER_HashUpdate(HashHandle, pu8Seed, u32Seedlen)
			  || HI_MPI_CIPHER_HashUpdate(HashHandle, u8Cnt, 4)
			  || HI_MPI_CIPHER_HashFinal(HashHandle, u8Md);
        if (Ret != HI_SUCCESS)
        {
		return Ret;
        }
        for(j=0; (j<u32MdLen) && (u32Outlen < u32MaskLen); j++)
		{
			pu8Mask[u32Outlen++] ^= u8Md[j];
		}
    }

    return HI_SUCCESS;
}

HI_S32 Mbedtls_GetRandomNumber(HI_VOID *param, HI_U8 *pu8Rand,  size_t u32Size)
{
    HI_U32 i;
    HI_U32 u32Rand = 0;

    memset(pu8Rand, 0, u32Size);
    for(i=0; i<u32Size; i+=4)
    {
        HI_MPI_CIPHER_GetRandomNumber(&u32Rand, -1);
        pu8Rand[i+3]   = (HI_U8)(u32Rand >> 24)& 0xFF;
        pu8Rand[i+2] = (HI_U8)(u32Rand >> 16)& 0xFF;
        pu8Rand[i+1] = (HI_U8)(u32Rand >> 8)& 0xFF;
        pu8Rand[i+0] = (HI_U8)(u32Rand) & 0xFF;
    }

    /*non-zero random octet string*/
    for(i=0; i<u32Size; i++)
    {
        if (pu8Rand[i] == 0x00)
        {
            HI_MPI_CIPHER_GetRandomNumber(&u32Rand, -1);
            pu8Rand[i] = (HI_U8)(u32Rand) & 0xFF;
            i = 0;
        }
    }

    return HI_SUCCESS;
}

static HI_U32 HI_MPI_CIPHER_GetBitNum(HI_U8 *pu8BigNum, HI_U32 u32NumLen)
{
	static const HI_S8 u8Bits[16] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};
	HI_U32 i;
	HI_U32 u32Num;

	for(i=0; i<u32NumLen; i++)
	{
		u32Num = u8Bits[(pu8BigNum[i] & 0xF0) >> 4] ;
		if(u32Num > 0)
		{
			return (u32NumLen - i - 1) * 8 + u32Num + 4;
		}
		u32Num = u8Bits[pu8BigNum[i] & 0xF] ;
		if(u32Num > 0)
		{
			return (u32NumLen - i - 1) * 8 + u32Num;
		}
	}
	return  0;
}

static HI_S32 RSA_Crt2Nocrt(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey,HI_U8 *pu8Output)
{
	int ret;
	mbedtls_mpi P1, Q1, P, Q, H, D, E;

	if((pstPriKey->pu8P == HI_NULL)
		|| (pstPriKey->pu8Q == HI_NULL)
		|| (pstPriKey->pu8E == HI_NULL)
		|| (pu8Output == HI_NULL))
	{
		HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
	}

	mbedtls_mpi_init( &P1 );
	mbedtls_mpi_init( &Q1 );
	mbedtls_mpi_init( &P );
	mbedtls_mpi_init( &Q );
	mbedtls_mpi_init( &E );
	mbedtls_mpi_init( &H );
	mbedtls_mpi_init( &D );

	 /*
	 * D  = E^-1 mod ((P-1)*(Q-1))
	 */
	MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&P, pstPriKey->pu8P, pstPriKey->u16PLen));
	MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&Q, pstPriKey->pu8Q, pstPriKey->u16QLen));
	MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&E, pstPriKey->pu8E, pstPriKey->u16ELen));

	MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &P1, &P, 1 ) );
	MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &Q1, &Q, 1 ) );
	MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &H, &P1, &Q1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &D , &E, &H  ) );

	MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary(&D, pu8Output, pstPriKey->u16NLen));
cleanup:

	mbedtls_mpi_free( &P1 );
	mbedtls_mpi_free( &Q1 );
	mbedtls_mpi_free( &P );
	mbedtls_mpi_free( &Q );
	mbedtls_mpi_free( &E );
	mbedtls_mpi_free( &H );
	mbedtls_mpi_free( &D );

	return ret;
}

/*PKCS #1: EME-OAEP encoding*/
/*************************************************************
                    +----------+---------+--+-------+
               DB = |  lHash   |    PS   |01|   M   |
                    +----------+---------+--+-------+
                                   |
         +----------+              V
         |   seed   |--> MGF ---> xor
         +----------+              |
               |                   |
      +--+     V                   |
      |00|    xor <----- MGF <-----|
      +--+     |                   |
        |      |                   |
        V      V                   V
      +--+----------+----------------------------+
EM =  |00|maskedSeed|          maskedDB          |
      +--+----------+----------------------------+
       1     hlen              k - hlen- 1

so: PS_LEN = k - hlen - 1 -  (hlen  + mlen + 1) = k - 2hlen - mlen - 2 > 0
so: mlen < k - 2hlen - 2
*************************************************************/
static HI_S32 RSA_padding_add_PKCS1_OAEP(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                  HI_U32 u32HLen,
                                  HI_U32 u32KeyLen,
                                  HI_U8 *pu8Input,
                                  HI_U32 u32InLen,
                                  HI_U8 *pu8Output,
                                  HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32DBLen;
    HI_U8 *pu8DB;
    HI_U8 *pu8Seed;
    const HI_S8 *pu8LHASH = EMPTY_L_SHA1;

    /*In the v2.1 of PKCS #1, L is the empty string;    */
    /*other uses outside the scope of rsa specifications*/
    if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA224)
    {
        pu8LHASH = EMPTY_L_SHA224;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA256)
    {
        pu8LHASH = EMPTY_L_SHA256;
    }
    else if( (enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA384) )
    {
        pu8LHASH = EMPTY_L_SHA384;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA512)
    {
        pu8LHASH = EMPTY_L_SHA512;
    }

    if ((u32KeyLen < 2 * u32HLen + 2) || (u32InLen > u32KeyLen - 2 * u32HLen - 2))
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen = 0;
    pu8Output[0] = 0;
    pu8Seed = pu8Output + 1;
    pu8DB = pu8Output + u32HLen + 1;
    u32DBLen = u32KeyLen - u32HLen -1;

    memcpy(pu8DB, pu8LHASH, u32HLen);                                 /*set lHash*/
    memset(&pu8DB[u32HLen], 0, u32DBLen - u32InLen - u32HLen -1);     /*set PS with 0x00*/
    pu8DB[u32DBLen - u32InLen - 1] = 0x01;                            /*set 0x01 after PS*/
    memcpy(&pu8DB[u32DBLen - u32InLen], pu8Input, u32InLen);          /*set M*/
    (HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, pu8Seed, u32HLen);
    ret = RSA_PKCS1_MGF1(enHashType, pu8Seed, u32HLen, pu8DB, u32KeyLen - u32HLen - 1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    ret = RSA_PKCS1_MGF1(enHashType, pu8DB, u32KeyLen - u32HLen - 1, pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    *pu32OutLen = u32KeyLen;

     return HI_SUCCESS;
}

/*PKCS #1: RSAES-PKCS1-V1_5-ENCRYPT*/
/*************************************************
EM = 0x00 || 0x02 || PS || 0x00 || M

PS_LEN > 8, mlen < u32KeyLen - 11
*************************************************/
static HI_S32 RSA_padding_add_PKCS1_V15( HI_U32 u32KeyLen,
                                 HI_U8 *pu8Input,
                                 HI_U32 u32InLen,
                                 HI_U8 *pu8Output,
                                 HI_U32 *pu32OutLen)
{
    HI_U32 u32Index = 0;

    if (u32InLen > u32KeyLen - 11)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen = 0;
    pu8Output[u32Index++] = 0x00;
    pu8Output[u32Index++] = 0x02;
    (HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, &pu8Output[u32Index], u32KeyLen - u32InLen -3);
    u32Index+=u32KeyLen - u32InLen -3;
    pu8Output[u32Index++] = 0x00;
    memcpy(&pu8Output[u32Index], pu8Input, u32InLen);

    *pu32OutLen = u32KeyLen;

    return HI_SUCCESS;
}

/*PKCS #1: block type 0,1,2 message padding*/
/*************************************************
EB = 00 || BT || PS || 00 || D

PS_LEN >= 8, mlen < u32KeyLen - 11
*************************************************/
static HI_S32 RSA_padding_add_PKCS1_type(HI_U32 u32KeyLen,
                               HI_U8  u8BT,
                               HI_U8 *pu8Input,
                               HI_U32 u32InLen,
                               HI_U8 *pu8Output,
                               HI_U32 *pu32OutLen)
{
    HI_U32 u32PLen;
    HI_U8 *pu8EB;

    if (u32InLen > u32KeyLen - 11)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen =0;
    pu8EB = pu8Output;

    *(pu8EB++) = 0;
    *(pu8EB++) = u8BT;                 /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    u32PLen = u32KeyLen - 3 - u32InLen;
    switch(u8BT)
    {
    case 0x00:
        memset(pu8EB, 0x00, u32PLen);
        break;
    case 0x01:
        memset(pu8EB, 0xFF, u32PLen);
        break;
    case 0x02:
        (HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, pu8EB, u32PLen);
        break;
    default:
        HI_ERR_CIPHER("BT(0x%x) is invalid.\n", u8BT);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    pu8EB += u32PLen;
    *(pu8EB++) = 0x00;
    memcpy(pu8EB, pu8Input, u32InLen);

    *pu32OutLen = u32KeyLen;

    return HI_SUCCESS;
}

/*PKCS #1: RSAES-PKCS1-V1_5-Signature*/
/*********************************************************
EM = 0x00 || 0x01 || PS || 0x00 || T

T ::= SEQUENCE {
          digestAlgorithm AlgorithmIdentifier,
          digest OCTET STRING
      }
The first field identifies the hash function and the second
contains the hash value
**********************************************************/
static HI_S32 RSA_padding_add_EMSA_PKCS1_v15(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                        HI_U32 u32HLen,
                                        HI_U32 u32KeyLen,
                                        HI_U8 *pu8Input,
                                        HI_U32 u32InLen,
                                        HI_U8 *pu8Output,
                                        HI_U32 *pu32OutLen)
{
	HI_U32 u32PadLen;
    HI_U8  *p;

    *pu32OutLen = u32KeyLen;

     p = pu8Output;
    *p++ = 0;
    *p++ = RSA_SIGN;
    switch(enHashType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        u32PadLen = u32KeyLen - 3 - 35;
        memset(p, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        memcpy(p, ASN1_HASH_SHA1, 15);
        memcpy(p + 15, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        memset(p, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        memcpy( p, ASN1_HASH_SHA224, 19);
        memcpy( p + 19, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        memset(p, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        memcpy( p, ASN1_HASH_SHA256, 19);
        memcpy( p + 19, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        memset(p, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        memcpy( p, ASN1_HASH_SHA384, 19);
        memcpy( p + 19, pu8Input, u32InLen);
        break;
     case HI_UNF_CIPHER_HASH_TYPE_SHA512:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        memset(p, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        memcpy( p, ASN1_HASH_SHA512, 19);
        memcpy( p + 19, pu8Input, u32InLen);
        break;
    default:
        HI_ERR_CIPHER("RSA unsuporrt hash type: 0x%x.\n", enHashType);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

/******************************************************************
								  +-----------+
								  |     M     |
								  +-----------+
										|
										V
									   Hash
										|
										V
					     +--------+----------+----------+
			       M' =  |Padding1|  mHash   |   salt   |
					     +--------+----------+----------+
										|
		    +--------+----------+       V
	 DB =   |Padding2|maskedseed|      Hash
			+--------+----------+       |
					|					|
					V					|	  +--+
					xor <----- MGF <----|	  |bc|
					|					|	  +--+
					|					|      |
					V					V      V
			+-------------------+----- -------+--+
	EM =    |    maskedDB       |  maskedseed |bc|
			+-------------------+-------------+--+
 ******************************************************************/
static HI_S32 RSA_padding_add_PKCS1_PSS(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                        HI_U32 u32HLen,
                                        HI_U32 u32EmBit,
							            HI_U8 *pu8Input,
							            HI_U32 u32InLen,
							            HI_U8 *pu8Output,
                                        HI_U32 *pu32OutLen)
{
	HI_U32 ret = 0;
	HI_U32 u32SLen;
	HI_U8 *pu8M = HI_NULL;
	HI_U8 u8Salt[HASH_RESULT_MAX_LEN];
	HI_U8 *pu8MaskedDB;
	HI_U8 *pu8Maskedseed;
	HI_U32 u32Index;
	HI_U32 u32KeyLen;
	HI_U32 u32MSBits;
    HI_HANDLE HashHandle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	u32SLen = u32HLen;
    u32KeyLen = (u32EmBit + 7)/8;
	u32MSBits = (u32EmBit - 1) & 0x07;

    *pu32OutLen = u32KeyLen;

	if (u32KeyLen < (u32HLen + u32SLen + 2))
	{
		HI_ERR_CIPHER("message too long\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

	if (u32MSBits == 0)
	{
		*pu8Output++ = 0;
		u32KeyLen--;
	}

	pu8MaskedDB = pu8Output;
	pu8Maskedseed = pu8Output + u32KeyLen - u32HLen -1;

	/* Generate a random octet string salt of length sLen */
	(HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, u8Salt, u32SLen);
    pu8M = (HI_U8*)malloc(u32SLen + u32HLen + 8);
	if (pu8M == HI_NULL)
	{
		HI_ERR_CIPHER("malloc failed\n");
		return HI_FAILURE;
	}

	/*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
	u32Index = 0;
	memset(pu8M, 0x00, 8);
	u32Index+=8;
	memcpy(&pu8M[u32Index], pu8Input, u32InLen);
	u32Index+=u32InLen;
    memcpy(&pu8M[u32Index], u8Salt, u32SLen);
	u32Index+=u32SLen;
    stHashAttr.eShaType = enHashType;
    ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle)
	      || HI_MPI_CIPHER_HashUpdate(HashHandle, pu8M, u32Index)
		  || HI_MPI_CIPHER_HashFinal(HashHandle, pu8Maskedseed);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash failed\n");
        free(pu8M);
        pu8M = HI_NULL;
        return ret;
    }
    free(pu8M);
    pu8M = HI_NULL;

	/*maskedDB = DB xor dbMask, DB = PS || 0x01 || salt*/
	u32Index = 0;
	memset(&pu8MaskedDB[u32Index], 0x00, u32KeyLen - u32SLen -u32HLen - 2);
	u32Index+=u32KeyLen - u32SLen -u32HLen - 2;
	pu8MaskedDB[u32Index++] = 0x01;
	memcpy(&pu8MaskedDB[u32Index], u8Salt, u32SLen);
	ret = RSA_PKCS1_MGF1(enHashType, pu8Maskedseed, u32HLen, pu8MaskedDB, u32KeyLen - u32HLen -1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

	pu8Output[u32KeyLen - 1] = 0xBC;

	if (u32MSBits)
	{
		pu8Output[0] &= 0xFF >> (8 - u32MSBits);
	}

	return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_RsaPublicEncrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
								  HI_U8 *pu8Input, HI_U32 u32InLen,
								  HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_RSA_DATA_S stRsaData;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];

    CHECK_CIPHER_OPEN();

    if ((pstRsaEnc == HI_NULL) || (pu8Input == HI_NULL)
        || (pu8Output == HI_NULL) || (pu32OutLen == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (u32InLen == 0)
    {
        HI_ERR_CIPHER("inlen is 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = RSA_GetAttr(pstRsaEnc->enScheme, pstRsaEnc->stPubKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    if (u32InLen > u32KeyLen)
    {
        HI_ERR_CIPHER("inlen is too large.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(u8EM, 0, sizeof(u8EM));

    switch(pstRsaEnc->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        /*if u32InLen < u32KeyLen, padding 0 before input data*/
        *pu32OutLen = u32KeyLen;
        memcpy(u8EM+(u32KeyLen - u32InLen), pu8Input, u32InLen);
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaEnc->enScheme);
        HI_ERR_CIPHER("For a public key encryption operation, the block type shall be 02.\n");
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        u8BT = (HI_U8)(pstRsaEnc->enScheme - HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0);
        ret = RSA_padding_add_PKCS1_type(u32KeyLen, u8BT, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
        ret = RSA_padding_add_PKCS1_OAEP(enHashType, u32HLen, u32KeyLen, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        ret = RSA_padding_add_PKCS1_V15(u32KeyLen, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    default:
        HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaEnc->enScheme);
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    }

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA padding error, ret = 0x%x.\n", ret);
        return ret;
    }

    stRsaData.pu8N = pstRsaEnc->stPubKey.pu8N;
    stRsaData.pu8K = pstRsaEnc->stPubKey.pu8E;
    stRsaData.u16NLen = pstRsaEnc->stPubKey.u16NLen;
    stRsaData.u16KLen = pstRsaEnc->stPubKey.u16ELen;
    stRsaData.pu8Input = u8EM;
    stRsaData.pu8Output = pu8Output;
    stRsaData.u32DataLen = u32KeyLen;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);

    return ret;
}

static HI_S32 RSA_padding_check_PKCS1_OAEP(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                  HI_U32 u32HLen,
                                  HI_U32 u32KeyLen,
                                  HI_U8 *pu8Input,
                                  HI_U32 u32InLen,
                                  HI_U8 *pu8Output,
                                  HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i;
    const HI_S8 *pu8LHASH = EMPTY_L_SHA1;
    HI_U8 *pu8Seed;
    HI_U8 *pu8DB;
    HI_U8 *pu8MaskedDB;

    if(enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA224)
    {
        pu8LHASH = EMPTY_L_SHA224;
    }
    else if(enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA256)
    {
        pu8LHASH = EMPTY_L_SHA256;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA384)
    {
        pu8LHASH = EMPTY_L_SHA384;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA512)
    {
        pu8LHASH = EMPTY_L_SHA512;
    }

    if (u32InLen != u32KeyLen)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (u32KeyLen < 2 * u32HLen + 2)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8Input[0] != 0x00)
    {
        HI_ERR_CIPHER("EM[0] != 0.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    *pu32OutLen = 0;
    pu8MaskedDB= pu8Input + u32HLen + 1;
    pu8Seed = pu8Input + 1;
    pu8DB = pu8Input + u32HLen + 1;
    ret = RSA_PKCS1_MGF1(enHashType, pu8MaskedDB, u32KeyLen - u32HLen - 1, pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    ret = RSA_PKCS1_MGF1(enHashType, pu8Seed, u32HLen, pu8DB, u32KeyLen - u32HLen - 1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    if(memcmp(pu8DB, pu8LHASH, u32HLen) != 0)
    {
        HI_ERR_CIPHER("LHASH error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    for(i=u32HLen; i < u32KeyLen - u32HLen - 1; i++)
    {
        if(pu8DB[i] == 0x01)
        {
            memcpy(pu8Output, pu8DB+i+1, u32KeyLen - u32HLen - i - 2);
            *pu32OutLen = u32KeyLen - u32HLen - i - 2;
            break;
        }
    }
    if (i >= u32KeyLen - u32HLen - 1)
    {
        HI_ERR_CIPHER("PS error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    return HI_SUCCESS;
}

static HI_S32 RSA_padding_check_PKCS1_V15(HI_U32 u32KeyLen,
                                          HI_U8 *pu8Input,
                                          HI_U32 u32InLen,
                                          HI_U8 *pu8Output,
                                          HI_U32 *pu32OutLen)
{
    HI_U32 u32Index = 0;

    if (u32KeyLen < 11)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8Input[u32Index] != 0x00)
    {
        HI_ERR_CIPHER("EM[0] != 0x00.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    u32Index++;
    if(pu8Input[u32Index] != 0x02)
    {
        HI_ERR_CIPHER("EM[1] != 0x02.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    u32Index++;
    for( ; u32Index < u32KeyLen; u32Index++)
    {
        if( (u32Index >= 10) //The length of PS is large than 8 octets
            && (pu8Input[u32Index] == 0x00))
        {
            memcpy(pu8Output, &pu8Input[u32Index+1], u32KeyLen - 1 - u32Index);
            *pu32OutLen = u32KeyLen - 1 - u32Index;
            break;
        }
    }
    if (u32Index >= u32KeyLen)
    {
        HI_ERR_CIPHER("PS error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    return HI_SUCCESS;
}

static HI_S32 RSA_padding_check_PKCS1_type(HI_U32 u32KeyLen,
                               HI_U8  u8BT,
                               HI_U8 *pu8Input,
                               HI_U32 u32InLen,
                               HI_U8 *pu8Output,
                               HI_U32 *pu32OutLen)
{
    HI_U8 *pu8EB;

    *pu32OutLen = 0x00;
    pu8EB = pu8Input;
    if(*pu8EB != 0x00)
    {
        HI_ERR_CIPHER("EB[0] != 0x00.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    pu8EB++;
    if(*pu8EB != u8BT)
    {
        HI_ERR_CIPHER("EB[1] != BT(0x%x).\n", u8BT);
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    pu8EB++;
    switch(u8BT)
    {
    case 0x00:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if( (*pu8EB == 0x00) && (*(pu8EB+1) != 0))
            {
                break;
            }
        }
        break;
    case 0x01:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if(*pu8EB == 0xFF)
            {
                continue;
            }
            else if (*pu8EB == 0x00)
            {
                break;
            }
            else
            {
                pu8EB = pu8Input + u32InLen - 1;
                break;
            }
        }
        break;
    case 0x02:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if(*pu8EB == 0x00)
            {
                break;
            }
        }
        break;
    default:
        HI_ERR_CIPHER("BT(0x%x) is invalid.\n", u8BT);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8EB >= (pu8Input + u32InLen - 1))
    {
        HI_ERR_CIPHER("PS Error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    pu8EB++;
    *pu32OutLen = pu8Input + u32KeyLen - pu8EB;
    memcpy(pu8Output, pu8EB, *pu32OutLen);

    return HI_SUCCESS;
}

static HI_S32 RSA_padding_check_EMSA_PKCS1_v15(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                        HI_U32 u32HLen,
                                        HI_U32 u32KeyLen,
                                        HI_U8 *pu8Input,
                                        HI_U32 u32InLen,
                                        HI_U8 *pu8Output,
                                        HI_U32 *pu32OutLen)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 u32Len;
    HI_U8  *p;

    *pu32OutLen = u32HLen;

    /*EM = 01 || PS || 00 || T*/
    p = pu8Input;

    if( *p++ != 0)
    {
        HI_ERR_CIPHER("RSA EM[0] must be 0\n");
        return HI_FAILURE;
    }
    if( *p++ != RSA_SIGN )
    {
        HI_ERR_CIPHER("RSA EM PS error\n");
        return HI_FAILURE;
    }

    while( *p != 0 )
    {
        if( p >= pu8Input + u32KeyLen - 1 || *p != 0xFF )
        {
            HI_ERR_CIPHER("RSA PS error\n");
            return HI_FAILURE;
        }
        p++;
    }
    p++; //skip 0x00

    u32Len = u32KeyLen - (HI_U32)( p - pu8Input);
    ret = HI_FAILURE;
    switch(enHashType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        if (u32Len != 35)
        {
            HI_ERR_CIPHER("RSA T len error: %d\n", u32Len);
            break;
        }
        if(memcmp(p, ASN1_HASH_SHA1, 15) == 0)
        {
            memcpy(pu8Output, p + 15, u32HLen);
            ret = HI_SUCCESS;
        }
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
        if (u32Len != (19 + u32HLen))
        {
            HI_ERR_CIPHER("RSA T len error: %d\n", u32Len);
            break;
        }
        if(memcmp(p, ASN1_HASH_SHA224, 19) == 0)
        {
            memcpy(pu8Output, p + 19, u32HLen);
            ret = HI_SUCCESS;
        }
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        if (u32Len != (19 + u32HLen))
        {
            HI_ERR_CIPHER("RSA T len error: %d\n", u32Len);
            break;
        }
        if(memcmp(p, ASN1_HASH_SHA256, 19) == 0)
        {
            memcpy(pu8Output, p + 19, u32HLen);
            ret = HI_SUCCESS;
        }
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
        if (u32Len != (19 + u32HLen))
        {
            HI_ERR_CIPHER("RSA T len error: %d\n", u32Len);
            break;
        }
        if(memcmp(p, ASN1_HASH_SHA384, 19) == 0)
        {
            memcpy(pu8Output, p + 19, u32HLen);
            ret = HI_SUCCESS;
        }
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
        if (u32Len != (19 + u32HLen))
        {
            HI_ERR_CIPHER("RSA T len error: %d\n", u32Len);
            break;
        }
        if(memcmp(p, ASN1_HASH_SHA512, 19) == 0)
        {
            memcpy(pu8Output, p + 19, u32HLen);
            ret = HI_SUCCESS;
        }
        break;
    default:
            HI_ERR_CIPHER("RSA unsuporrt hash type: 0x%x.\n", enHashType);
    }

    return ret;
}

static HI_U32 RSA_padding_check_PKCS1_PSS(HI_UNF_CIPHER_HASH_TYPE_E enHashType,
                                          HI_U32 u32HLen,
                                          HI_U32 u32EmBit,
							              HI_U8 *pu8Input,
							              HI_U32 u32InLen,
							              HI_U8 *pu8MHash)
{
	HI_U32 ret = 0;
	HI_U32 u32SLen;
	HI_U8 *pu8M = HI_NULL;
	HI_U8 u8Salt[HASH_RESULT_MAX_LEN] = {0};
    HI_U8 u8H[64] = {0};
	HI_U8 *pu8MaskedDB;
	HI_U8 *pu8Maskedseed;
	HI_U32 u32Index;
	HI_U32 u32KeyLen;
	HI_U32 u32MSBits;
    HI_HANDLE HashHandle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	u32SLen = u32HLen;
    u32KeyLen = (u32EmBit + 7)/8;
	u32MSBits = (u32EmBit - 1) & 0x07;

	if (u32KeyLen < (u32HLen + u32SLen + 2))
	{
		HI_ERR_CIPHER("message too long\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}

	if (pu8Input[0] & (0xFF << u32MSBits))
	{
		HI_ERR_CIPHER("inconsistent, EM[0] invalid\n");
		return HI_FAILURE;
	}

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

	if (u32MSBits == 0)
	{
		pu8Input++;
		u32KeyLen--;
	}

	pu8MaskedDB = pu8Input;
	pu8Maskedseed = pu8Input + u32KeyLen - u32HLen -1;

	if (pu8Input[u32KeyLen - 1] != 0xBC)
	{
		HI_ERR_CIPHER("inconsistent, EM[u32KeyLen - 1] != 0xBC\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}

	/*maskedDB = DB xor dbMask, DB = PS || 0x01 || salt*/
	ret = RSA_PKCS1_MGF1(enHashType, pu8Maskedseed, u32HLen, pu8MaskedDB, u32KeyLen - u32HLen -1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return ret;
    }
    if (u32MSBits)
	{
		pu8MaskedDB[0] &= 0xFF >> (8 - u32MSBits);
	}
	for (u32Index=0; u32Index<u32KeyLen - u32SLen -u32HLen - 2; u32Index++)
	{
		if (pu8MaskedDB[u32Index] != 0x00)
		{
			HI_ERR_CIPHER("inconsistent, PS != 0x00 in DB\n");
			return HI_FAILURE;
		}
	}
	if (pu8MaskedDB[u32Index++] != 0x01)
	{
		HI_ERR_CIPHER("inconsistent, can't find 0x01 in DB\n");
		return HI_FAILURE;
	}
	memcpy(u8Salt, &pu8MaskedDB[u32Index], u32SLen);

	pu8M = (HI_U8*)HI_MALLOC(HI_ID_CIPHER, u32SLen + u32HLen + 8);
	if (pu8M == NULL)
	{
		HI_ERR_CIPHER("malloc failed\n");
		return HI_FAILURE;
	}

	/*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
	u32Index = 0;
	memset(pu8M, 0x00, 8);
	u32Index+=8;
	memcpy(&pu8M[u32Index], pu8MHash, u32HLen);
	u32Index+=u32HLen;
    memcpy(&pu8M[u32Index], u8Salt, u32SLen);
	u32Index+=u32SLen;
    stHashAttr.eShaType = enHashType;
    ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle)
	      || HI_MPI_CIPHER_HashUpdate(HashHandle, pu8M, u32Index)
		  || HI_MPI_CIPHER_HashFinal(HashHandle, u8H);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash failed\n");
        free(pu8M);
        pu8M = HI_NULL;
        return ret;
    }
    free(pu8M);
    pu8M = HI_NULL;

	ret = memcmp(u8H, pu8Maskedseed, u32HLen);
	if (ret != 0)
	{
		HI_ERR_CIPHER("consistent, hash compare failed\n");
        ret = HI_FAILURE;
	}

	return ret;
}

HI_S32 HI_MPI_CIPHER_RsaPrivateDecrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
								   HI_U8 *pu8Input, HI_U32 u32InLen,
								   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_RSA_DATA_S stRsaData;
    HI_U8 u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;

    CHECK_CIPHER_OPEN();


    if ((pstRsaDec == HI_NULL) || (pu8Input == HI_NULL)
        || (pu8Output == HI_NULL) || (pu32OutLen == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    ret = RSA_GetAttr(pstRsaDec->enScheme, pstRsaDec->stPriKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    if(u32InLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InLen != u32KeyLen.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

	if(pstRsaDec->stPriKey.pu8D == HI_NULL)
	{
        ret = RSA_Crt2Nocrt(&pstRsaDec->stPriKey,u8EM);
        if (ret != HI_SUCCESS)
        {
        	HI_ERR_CIPHER("RSA_Crt2Nocrt failed, ret = %x\n", ret);
        	return HI_FAILURE;
        }
        stRsaData.pu8K = u8EM;
        stRsaData.u16KLen = pstRsaDec->stPriKey.u16NLen;
    }
    else
    {
        stRsaData.pu8K = pstRsaDec->stPriKey.pu8D;
        stRsaData.u16KLen = pstRsaDec->stPriKey.u16DLen;
    }

    stRsaData.pu8N = pstRsaDec->stPriKey.pu8N;
    stRsaData.u16NLen = pstRsaDec->stPriKey.u16NLen;
    stRsaData.pu8Input = pu8Input;
    stRsaData.pu8Output = u8EM;
    stRsaData.u32DataLen = u32KeyLen;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CMD_CIPHER_CALCRSA failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    switch(pstRsaDec->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        *pu32OutLen = u32InLen;
        memcpy(pu8Output, u8EM, u32KeyLen);
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaDec->enScheme);
        HI_ERR_CIPHER("For a private key decryption operation, the block type shall be 02.\n");
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        u8BT = (HI_U8)(pstRsaDec->enScheme - HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0);
        ret = RSA_padding_check_PKCS1_type(u32KeyLen, u8BT, u8EM, u32InLen, pu8Output, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
        ret = RSA_padding_check_PKCS1_OAEP(enHashType, u32HLen, u32KeyLen, u8EM, u32InLen, pu8Output, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        ret = RSA_padding_check_PKCS1_V15(u32KeyLen, u8EM, u32InLen, pu8Output, pu32OutLen);
        break;
    default:
        HI_ERR_CIPHER("RSA scheme error, scheme = 0x%x.\n", pstRsaDec->enScheme);
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    }

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA padding error, ret = 0x%x.\n", ret);
        return ret;
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_RsaSign(HI_UNF_CIPHER_RSA_SIGN_S *pstRsaSign,
							 HI_U8 *pu8InData, HI_U32 u32InDataLen,
							 HI_U8 *pu8HashData,
							 HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen)
{
    HI_U32 u32KeyLen;
    HI_U32 u32HLen;
    HI_U32 u32EmBit;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN];
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_S32 ret = HI_SUCCESS;
    CIPHER_RSA_DATA_S stRsaData;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U8 *pHash;
    CHECK_CIPHER_OPEN();

    if (pstRsaSign == HI_NULL)
    {
        HI_ERR_CIPHER("pstRsaSign is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pstRsaSign == HI_NULL)|| (pu8OutSign == HI_NULL)||(pu32OutSignLen == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

	if ((pu8InData == HI_NULL) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pstRsaSign->stPriKey.pu8N == HI_NULL) || (pstRsaSign->stPriKey.pu8D == HI_NULL))
    {
        HI_ERR_CIPHER("key is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((u32InDataLen == 0) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("inlen is 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

    ret = RSA_GetAttr(pstRsaSign->enScheme, pstRsaSign->stPriKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    /*hash is NULl, need to calc by self*/
    if (pu8HashData == HI_NULL)
    {
        stHashAttr.eShaType = enHashType;
        ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle)
		   || HI_MPI_CIPHER_HashUpdate(HashHandle, pu8InData, u32InDataLen)
		   || HI_MPI_CIPHER_HashFinal(HashHandle, u8Hash);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Hash error\n");
            return ret;
        }
        pHash = u8Hash;
    }
    else
    {
        pHash = pu8HashData;
    }

    memset(u8EM, 0, sizeof(u8EM));
    switch(pstRsaSign->enScheme)
    {
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
         ret = RSA_padding_add_EMSA_PKCS1_v15(enHashType, u32HLen, u32KeyLen,
             pHash, u32HLen, u8EM, pu32OutSignLen);
         break;
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
         u32EmBit = HI_MPI_CIPHER_GetBitNum(pstRsaSign->stPriKey.pu8N, u32KeyLen);
         ret = RSA_padding_add_PKCS1_PSS(enHashType, u32HLen, u32EmBit,
             pHash, u32HLen, u8EM, pu32OutSignLen);
         break;
    default:
         HI_ERR_CIPHER("invalid scheme; 0x%x\n", pstRsaSign->enScheme);
         return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA pading error\n");
        return ret;
    }

    if(*pu32OutSignLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InSigntLen != u32KeyLen.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

	if(pstRsaSign->stPriKey.pu8D == HI_NULL)
	{
        ret = RSA_Crt2Nocrt(&pstRsaSign->stPriKey,pu8OutSign);
        if (ret != HI_SUCCESS)
        {
        	HI_ERR_CIPHER("RSA_Crt2Nocrt failed, ret = %x\n", ret);
        	return HI_FAILURE;
        }
        stRsaData.pu8K = pu8OutSign;
        stRsaData.u16KLen = pstRsaSign->stPriKey.u16NLen;
    }
    else
    {
        stRsaData.pu8K = pstRsaSign->stPriKey.pu8D;
        stRsaData.u16KLen = pstRsaSign->stPriKey.u16DLen;
    }

    stRsaData.pu8N = pstRsaSign->stPriKey.pu8N;
    stRsaData.u16NLen = pstRsaSign->stPriKey.u16NLen;
    stRsaData.pu8Input = u8EM;
    stRsaData.pu8Output = pu8OutSign;
    stRsaData.u32DataLen = u32KeyLen;

//    HI_PRINT_HEX ("N", stRsaData.pu8N, stRsaData.u16NLen);
//    HI_PRINT_HEX ("K", stRsaData.pu8K, stRsaData.u16KLen);
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);

    return ret;
}

HI_S32 HI_MPI_CIPHER_RsaPrivateEncrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaEnc,
								   HI_U8 *pu8Input, HI_U32 u32InLen,
								   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_RSA_DATA_S stRsaData;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];

    CHECK_CIPHER_OPEN();

    if ((pstRsaEnc == HI_NULL) || (pu8Input == HI_NULL)
        || (pu8Output == HI_NULL) || (pu32OutLen == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (u32InLen == 0)
    {
        HI_ERR_CIPHER("inlen is 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = RSA_GetAttr(pstRsaEnc->enScheme, pstRsaEnc->stPriKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    if (u32InLen > u32KeyLen)
    {
        HI_ERR_CIPHER("inlen is too large.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(u8EM, 0, sizeof(u8EM));

    switch(pstRsaEnc->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        /*if u32InLen < u32KeyLen, padding 0 before input data*/
        *pu32OutLen = u32KeyLen;
        memcpy(u8EM+(u32KeyLen - u32InLen), pu8Input, u32InLen);
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        u8BT = (HI_U8)(pstRsaEnc->enScheme - HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0);
        ret = RSA_padding_add_PKCS1_type(u32KeyLen, u8BT, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaEnc->enScheme);
        HI_ERR_CIPHER("For a private- key encryption operation, the block type shall be 00 or 01.\n");
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
        ret = RSA_padding_add_PKCS1_OAEP(enHashType, u32HLen, u32KeyLen, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        ret = RSA_padding_add_PKCS1_type(u32KeyLen, 0x01, pu8Input, u32InLen, u8EM, pu32OutLen);
        break;
    default:
        HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaEnc->enScheme);
        ret = HI_ERR_CIPHER_INVALID_PARA;
        break;
    }

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA padding error, ret = 0x%x.\n", ret);
        return ret;
    }

    if(*pu32OutLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32OutLen != u32KeyLen.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

	if(pstRsaEnc->stPriKey.pu8D == HI_NULL)
	{
        ret = RSA_Crt2Nocrt(&pstRsaEnc->stPriKey, pu8Output);
        if (ret != HI_SUCCESS)
        {
        	HI_ERR_CIPHER("RSA_Crt2Nocrt failed, ret = %x\n", ret);
        	return HI_FAILURE;
        }
        stRsaData.pu8K = pu8Output;
        stRsaData.u16KLen = pstRsaEnc->stPriKey.u16NLen;
    }
    else
    {
        stRsaData.pu8K = pstRsaEnc->stPriKey.pu8D;
        stRsaData.u16KLen = pstRsaEnc->stPriKey.u16DLen;
    }

    stRsaData.pu8N = pstRsaEnc->stPriKey.pu8N;
    stRsaData.u16NLen = pstRsaEnc->stPriKey.u16NLen;
    stRsaData.pu8Input = u8EM;
    stRsaData.pu8Output = pu8Output;
    stRsaData.u32DataLen = u32KeyLen;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);

    return ret;

}

HI_S32 HI_MPI_CIPHER_RsaVerify(HI_UNF_CIPHER_RSA_VERIFY_S *pstRsaVerify,
							   HI_U8 *pu8InData, HI_U32 u32InDataLen,
							   HI_U8 *pu8HashData,
							   HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    HI_U32 ret = HI_SUCCESS;
    HI_U32 u32KeyLen;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];
    CIPHER_RSA_DATA_S stRsaData;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle = 0;
    HI_U8  u8Hash[64] = {0};
    HI_U8  u8SignHash[64] = {0};
    HI_U32 u32HLen;
    HI_U32 u32EmBit;
    HI_U8  *pHash;

    CHECK_CIPHER_OPEN();

    if (pstRsaVerify == HI_NULL)
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    if ((pstRsaVerify->stPubKey.pu8N == HI_NULL) || (pstRsaVerify->stPubKey.pu8E == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    ret = RSA_GetAttr(pstRsaVerify->enScheme, pstRsaVerify->stPubKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    if(u32InSignLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InSigntLen != u32KeyLen.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

    stRsaData.pu8N = pstRsaVerify->stPubKey.pu8N;
    stRsaData.pu8K = pstRsaVerify->stPubKey.pu8E;
    stRsaData.u16NLen = pstRsaVerify->stPubKey.u16NLen;
    stRsaData.u16KLen = pstRsaVerify->stPubKey.u16ELen;
    stRsaData.pu8Input = pu8InSign;
    stRsaData.pu8Output = u8EM;
    stRsaData.u32DataLen = u32KeyLen;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA verify dec error, ret=%d\n", ret);
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    if (pu8HashData == HI_NULL)
    {
        stHashAttr.eShaType = enHashType;
        ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle)
		    || HI_MPI_CIPHER_HashUpdate(HashHandle, pu8InData, u32InDataLen)
			|| HI_MPI_CIPHER_HashFinal(HashHandle, u8Hash);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Hash error\n");
            return ret;
        }
        pHash = u8Hash;
    }
    else
    {
        pHash = pu8HashData;
    }

    switch(pstRsaVerify->enScheme)
    {
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
         ret = RSA_padding_check_EMSA_PKCS1_v15(enHashType, u32HLen, u32KeyLen, u8EM,
               u32InSignLen, u8SignHash, &u32HLen);
         if (ret != HI_SUCCESS)
         {
             HI_ERR_CIPHER("RSA_padding_add_RSASSA_PKCS1_v15 error\n");
             return ret;
         }
         if (memcmp(pHash, u8SignHash, u32HLen) != 0)
         {
             HI_ERR_CIPHER("RSA verify, hash error\n");
             ret = HI_ERR_CIPHER_FAILED_DECRYPT;
         }
         break;
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
         u32EmBit = HI_MPI_CIPHER_GetBitNum(pstRsaVerify->stPubKey.pu8N, u32KeyLen);
         ret = RSA_padding_check_PKCS1_PSS(enHashType, u32HLen, u32EmBit,
               u8EM, u32InSignLen, pHash);
         break;
    default:
         HI_ERR_CIPHER("invalid scheme; 0x%x\n", pstRsaVerify->enScheme);
         return HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_RsaPublicDecrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
							   HI_U8 *pu8Input, HI_U32 u32InLen,
							   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_RSA_DATA_S stRsaData;
    HI_U8 u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;

    CHECK_CIPHER_OPEN();

    if ((pstRsaDec == HI_NULL) || (pu8Input == HI_NULL)
        || (pu8Output == HI_NULL) || (pu32OutLen == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    ret = RSA_GetAttr(pstRsaDec->enScheme, pstRsaDec->stPubKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    if(u32InLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InLen != u32KeyLen.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    stRsaData.pu8N = pstRsaDec->stPubKey.pu8N;
    stRsaData.pu8K = pstRsaDec->stPubKey.pu8E;
    stRsaData.u16NLen = pstRsaDec->stPubKey.u16NLen;
    stRsaData.u16KLen = pstRsaDec->stPubKey.u16ELen;
    stRsaData.pu8Input = pu8Input;
    stRsaData.pu8Output = u8EM;
    stRsaData.u32DataLen = u32KeyLen;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CMD_CIPHER_CALCRSA failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    switch(pstRsaDec->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
         *pu32OutLen = u32InLen;
         memcpy(pu8Output, u8EM, u32KeyLen);
         ret = HI_SUCCESS;
         break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
         u8BT = (HI_U8)(pstRsaDec->enScheme - HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0);
         ret = RSA_padding_check_PKCS1_type(u32KeyLen, u8BT, u8EM, u32InLen, pu8Output, pu32OutLen);
         break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
         HI_ERR_CIPHER("RSA padding mode error, mode = 0x%x.\n", pstRsaDec->enScheme);
         HI_ERR_CIPHER("For a public key decryption operation, the block type shall be 00 or 01.\n");
         ret = HI_ERR_CIPHER_INVALID_PARA;
         break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
         ret = RSA_padding_check_PKCS1_OAEP(enHashType, u32HLen, u32KeyLen, u8EM, u32InLen, pu8Output, pu32OutLen);
         break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
         ret = RSA_padding_check_PKCS1_type(u32KeyLen, 0x01, u8EM, u32InLen, pu8Output, pu32OutLen);
         break;
    default:
         HI_ERR_CIPHER("RSA scheme error, scheme = 0x%x.\n", pstRsaDec->enScheme);
         ret = HI_ERR_CIPHER_INVALID_PARA;
         break;
    }

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA padding error, ret = 0x%x.\n", ret);
        return ret;
    }

    return ret;
}

static HI_S32 CIPHER_RsaRandomNumber(HI_VOID *param, HI_U8 *rng, size_t size)
{
    HI_U32 u32Randnum = 0x165e9fb5;
    HI_VOID *pu32RngBase;
    HI_U32 i, byte;

   // u32RngBase = (HI_U32)param;
   pu32RngBase = param;

    for(i=0; i<size; i+=4)
    {
#if defined (CHIP_TYPE_hi3716mv410) || defined (CHIP_TYPE_hi3716mv420) || defined (CHIP_TYPE_hi3798cv200) || defined (CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined (CHIP_TYPE_hi3798mv200_a)
        u32Randnum = *(volatile unsigned int *)( pu32RngBase + 0x04);
#else
        HI_U32 u32RngStat;
        HI_U32 u32Timeout = 0;

        while(u32Timeout < 10000)
        {
            u32RngStat = *(volatile unsigned int *)( pu32RngBase + 0x08); //REG_RNG_STAT
            if((u32RngStat & 0x7) > 0)
            {
                u32Randnum = *(volatile unsigned int *)( pu32RngBase + 0x04);//REG_RNG_NUMBER
                break;
            }
        }
#endif
        byte = size - i;
        byte = byte > 4 ? 4: byte;
        memcpy(rng+i, &u32Randnum, byte);
    }
    return HI_SUCCESS;
}

static HI_VOID CIPHER_CopyKey(mbedtls_mpi *X, HI_U8 *buf)
{
    HI_S32 ret = 0;

    if (buf == HI_NULL)
    {
        return;
    }

    ret = mbedtls_mpi_write_binary(X, buf, mbedtls_mpi_size(X));
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mbedtls_mpi_write_binary error!\n");
    }
}

HI_S32 HI_MPI_CIPHER_RsaGenKey(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_UNF_CIPHER_RSA_PRI_KEY_S *pstRsaPriKey)
{
    HI_S32 ret = HI_SUCCESS;
    mbedtls_rsa_context rsa;
    HI_VOID *pu32RngBase;

    CHECK_CIPHER_OPEN();

    if (HI_NULL == pstRsaPriKey )
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pstRsaPriKey) ||(HI_NULL == pstRsaPriKey->pu8D) ||(HI_NULL == pstRsaPriKey->pu8E)
         ||(HI_NULL == pstRsaPriKey->pu8N) ||(HI_NULL == pstRsaPriKey->pu8P) ||(HI_NULL == pstRsaPriKey->pu8Q)
         ||(HI_NULL == pstRsaPriKey->pu8DP) ||(HI_NULL == pstRsaPriKey->pu8DQ) ||(HI_NULL == pstRsaPriKey->pu8QP))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((0 == u32NumBits ) || (0 == u32Exponent ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if((RSA_KEY_BITWIDTH_1024 != u32NumBits) && (RSA_KEY_BITWIDTH_2048 != u32NumBits)
        && (RSA_KEY_BITWIDTH_3072 != u32NumBits) && (RSA_KEY_BITWIDTH_4096 != u32NumBits))
    {
        HI_ERR_CIPHER("RSA Rsa Gen Key, u32NumBits error\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if((RSA_KEY_EXPONENT_VALUE1 != u32Exponent) && (RSA_KEY_EXPONENT_VALUE2 != u32Exponent))
    {
        HI_ERR_CIPHER("RSA Rsa Gen Key, u32Exponent error\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = (HI_U32)HI_SYS_MapRegister(CIPHER_RNG_REG_BASE_ADDR_PHY + 0x200, 0x10, &pu32RngBase);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Map RNG regiest failed!\n");
        return HI_FAILURE;
    }

    *(volatile unsigned int *)(pu32RngBase) = 0x0a;

    mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);
    ret = mbedtls_rsa_gen_key(&rsa, CIPHER_RsaRandomNumber, (HI_VOID*)pu32RngBase, u32NumBits, (HI_S32)u32Exponent);
    if( 0 == ret )
    {
        pstRsaPriKey->u16NLen = mbedtls_mpi_size(&rsa.N);
        pstRsaPriKey->u16ELen = mbedtls_mpi_size(&rsa.E);
        pstRsaPriKey->u16DLen = mbedtls_mpi_size(&rsa.D);
        pstRsaPriKey->u16PLen = mbedtls_mpi_size(&rsa.P);
        pstRsaPriKey->u16QLen = mbedtls_mpi_size(&rsa.Q);
        pstRsaPriKey->u16DPLen = mbedtls_mpi_size(&rsa.DP);
        pstRsaPriKey->u16DQLen = mbedtls_mpi_size(&rsa.DQ);
        pstRsaPriKey->u16QPLen = mbedtls_mpi_size(&rsa.QP);
        CIPHER_CopyKey(&rsa.N, pstRsaPriKey->pu8N);
        CIPHER_CopyKey(&rsa.E, pstRsaPriKey->pu8E);
        CIPHER_CopyKey(&rsa.D, pstRsaPriKey->pu8D);
        CIPHER_CopyKey(&rsa.P, pstRsaPriKey->pu8P);
        CIPHER_CopyKey(&rsa.Q, pstRsaPriKey->pu8Q);
        CIPHER_CopyKey(&rsa.DP, pstRsaPriKey->pu8DP);
        CIPHER_CopyKey(&rsa.DQ, pstRsaPriKey->pu8DQ);
        CIPHER_CopyKey(&rsa.QP, pstRsaPriKey->pu8QP);
    }
    else
    {
        HI_ERR_CIPHER("RSA public error!\n");
        ret = HI_FAILURE;
    }
    mbedtls_rsa_free(&rsa);

    HI_SYS_UnmapRegister((HI_VOID*)pu32RngBase);

    return ret;
}

HI_S32 HI_MPI_CIPHER_RsaComputeCrtParams(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_U8 *pu8P,
                               HI_U8 *pu8Q, HI_U8 *pu8DP, HI_U8 *pu8DQ, HI_U8 *pu8QP)
{
    HI_S32 ret = HI_SUCCESS;
    mbedtls_mpi E, D, P, Q, DP, DQ, QP, P1, Q1, H;

    CHECK_CIPHER_OPEN();

    if ((HI_NULL == pu8P ) || (HI_NULL == pu8Q ) || (HI_NULL == pu8DP )
        || (HI_NULL == pu8DQ ) || (HI_NULL == pu8QP ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((0 == u32NumBits ) || (0 == u32Exponent ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if((RSA_KEY_BITWIDTH_1024 != u32NumBits) && (RSA_KEY_BITWIDTH_2048 != u32NumBits)
        && (RSA_KEY_BITWIDTH_3072 != u32NumBits) && (RSA_KEY_BITWIDTH_4096 != u32NumBits))
    {
        HI_ERR_CIPHER("RSA compute crt params, u32NumBits error\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if((RSA_KEY_EXPONENT_VALUE1 != u32Exponent) && (RSA_KEY_EXPONENT_VALUE2 != u32Exponent))
    {
        HI_ERR_CIPHER("RSA compute crt params, u32Exponent error\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    mbedtls_mpi_init( &E );
    mbedtls_mpi_init( &D );
    mbedtls_mpi_init( &P );
    mbedtls_mpi_init( &Q );
    mbedtls_mpi_init( &DP );
    mbedtls_mpi_init( &DQ );
    mbedtls_mpi_init( &QP );
    mbedtls_mpi_init( &P1 );
    mbedtls_mpi_init( &Q1 );
    mbedtls_mpi_init( &H );

    MBEDTLS_MPI_CHK(mbedtls_mpi_lset( &E, u32Exponent ));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&P, pu8P, u32NumBits/16));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q, pu8Q, u32NumBits/16));

    /* D  = E^-1 mod ((P-1)*(Q-1))
     * DP = D mod (P - 1)
     * DQ = D mod (Q - 1)
     * QP = Q^-1 mod P
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &P1, &P, 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &Q1, &Q, 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &H, &P1, &Q1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &D , &E, &H  ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &DP, &D, &P1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &DQ, &D, &Q1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &QP, &Q, &P ) );

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&DP, pu8DP, u32NumBits/16));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&DQ, pu8DQ, u32NumBits/16));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&QP, pu8QP, u32NumBits/16));

cleanup:

    mbedtls_mpi_free( &E );
    mbedtls_mpi_free( &D );
    mbedtls_mpi_free( &P );
    mbedtls_mpi_free( &Q );
    mbedtls_mpi_free( &DP );
    mbedtls_mpi_free( &DQ );
    mbedtls_mpi_free( &QP );
    mbedtls_mpi_free( &P1 );
    mbedtls_mpi_free( &Q1 );
    mbedtls_mpi_free( &H );

    return ret;

}

HI_S32 HI_MPI_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize)
{
    HI_S32 ret;
    CIPHER_RSA_DATA_S stRsaData;

    CHECK_CIPHER_OPEN();

    if ((HI_NULL == pu8P ) || (HI_NULL == pu8SharedSecret )
        || (HI_NULL == pu8PrivKey ) || (HI_NULL == pu8OtherPubKey ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == u32KeySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    stRsaData.pu8N = pu8P;
    stRsaData.pu8K = pu8PrivKey;
    stRsaData.pu8Input = pu8OtherPubKey;
    stRsaData.u16NLen = u32KeySize;
    stRsaData.u16KLen = u32KeySize;
    stRsaData.u32DataLen = u32KeySize;
    stRsaData.pu8Output = pu8SharedSecret;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CMD_CIPHER_CALCRSA failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                                   HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                                   HI_U32 u32KeySize)
{
    HI_S32 ret;
    CIPHER_RSA_DATA_S stRsaData;

    CHECK_CIPHER_OPEN();

    if ((HI_NULL == pu8G ) || (HI_NULL == pu8P ) || (HI_NULL == pu8PubKey ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == u32KeySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pu8InputPrivKey ) && (HI_NULL == pu8OutputPrivKey ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pu8P[0] == 0x00)
    {
        HI_ERR_CIPHER("Invalid P[0], must large than 0!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (HI_NULL == pu8InputPrivKey)
    {
        ret = Mbedtls_GetRandomNumber(HI_NULL, pu8OutputPrivKey, u32KeySize);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Mbedtls_GetRandomNumber failed, ret = %x\n", ret);
            return HI_FAILURE;
        }

        //make sure PrivKey < P
        if(pu8OutputPrivKey[0] >= pu8P[0])
        {
            pu8OutputPrivKey[0] = pu8P[0] - 1;
        }
        stRsaData.pu8K = pu8OutputPrivKey;
    }
    else
    {
        stRsaData.pu8K = pu8InputPrivKey;
    }

    stRsaData.pu8N = pu8P;
    stRsaData.pu8Input = pu8G;
    stRsaData.u16NLen = u32KeySize;
    stRsaData.u16KLen = u32KeySize;
    stRsaData.u32DataLen = u32KeySize;
    stRsaData.pu8Output = pu8PubKey;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CMD_CIPHER_CALCRSA failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*
void mpi_print(const char *name, const mbedtls_mpi *X)
{
    char buf[256];
    size_t olen;

    mbedtls_mpi_write_string (X, 16, buf, 256, &olen);
    printf("[%s] %s\n", name, buf);
}
*/
HI_S32 HI_MPI_CIPHER_EcdhComputeKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
									HI_U8 *pu8OtherPubKeyX, HI_U8 *pu8OtherPubKeyY,
                                    HI_U8 *pu8SharedSecret)
{
    HI_S32 ret = HI_SUCCESS;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi z;
    mbedtls_mpi d;


    if ((HI_NULL == pstParams )
        || (HI_NULL == pu8PrivKey )
        || (HI_NULL == pu8OtherPubKeyX )
        || (HI_NULL == pu8OtherPubKeyY )
        || (HI_NULL == pu8SharedSecret ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

     if ((HI_NULL == pstParams->pu8p)
        || (HI_NULL == pstParams->pu8b )
        || (HI_NULL == pstParams->pu8a )
        || (HI_NULL == pstParams->pu8GX)
        || (HI_NULL == pstParams->pu8GY ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == pstParams->u32keySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&z);
    mbedtls_mpi_init(&d);

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&grp.P, pstParams->pu8p, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.A, pstParams->pu8a, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.B, pstParams->pu8b, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.N, pstParams->pu8n, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.X, pstParams->pu8GX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.Y, pstParams->pu8GY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp.G.Z, 1 ) );
    grp.pbits = mbedtls_mpi_bitlen( &grp.P );
    grp.nbits = mbedtls_mpi_bitlen( &grp.N );
    grp.h = pstParams->u32h;

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &Q.X, pu8OtherPubKeyX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &Q.Y, pu8OtherPubKeyY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &Q.Z, 1 ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &d, pu8PrivKey, pstParams->u32keySize ) );

    MBEDTLS_MPI_CHK( mbedtls_ecdh_compute_shared(&grp, &z, &Q, &d, HI_NULL, 0));

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &z, pu8SharedSecret, pstParams->u32keySize ) );
cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&z);
    mbedtls_mpi_free(&d);

    return( ret );
}

HI_S32 HI_MPI_CIPHER_EccGenKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8InputPrivKey,
                                     HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY)
{
    HI_S32 ret;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;

    if ((HI_NULL == pstParams )
        || (HI_NULL == pu8PubKeyX )
        || (HI_NULL == pu8PubKeyY ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pstParams->pu8p)
        || (HI_NULL == pstParams->pu8b )
        || (HI_NULL == pstParams->pu8a )
        || (HI_NULL == pstParams->pu8GX)
        || (HI_NULL == pstParams->pu8GY ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == pstParams->u32keySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pu8InputPrivKey ) && (HI_NULL == pu8OutputPrivKey ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&d);

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.P, pstParams->pu8p, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.A, pstParams->pu8a, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.B, pstParams->pu8b, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.N, pstParams->pu8n, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.X, pstParams->pu8GX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.Y, pstParams->pu8GY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp.G.Z, 1 ) );
    grp.pbits = mbedtls_mpi_bitlen( &grp.P );
    grp.nbits = mbedtls_mpi_bitlen( &grp.N );
    grp.h = pstParams->u32h;

    if (pu8InputPrivKey == HI_NULL)
    {
        MBEDTLS_MPI_CHK( mbedtls_ecdh_gen_public(&grp, &d, &Q, Mbedtls_GetRandomNumber, 0));
        MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &d, pu8OutputPrivKey, pstParams->u32keySize ) );
    }
    else
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &d, pu8InputPrivKey, pstParams->u32keySize ) );
        if ((mbedtls_mpi_cmp_int( &d, 1 ) < 0) || (mbedtls_mpi_cmp_mpi( &d, &grp.N ) >= 0 ))
        {
             HI_ERR_CIPHER("Invalid private key !!!\n");
                goto cleanup;
        }
        MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &Q, &d, &grp.G, HI_NULL, 0 ) );
    }

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &Q.X, pu8PubKeyX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &Q.Y, pu8PubKeyY, pstParams->u32keySize ) );

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&d);

    return( ret );
}

HI_S32 HI_MPI_CIPHER_EcdsaSign(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
							   HI_UNF_CIPHER_HASH_TYPE_E enShaType,
							   HI_U8 *pu8Message, HI_U32 u32MessageSize,
							   HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    HI_S32 ret;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN];
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U32 u32HashLen;
    mbedtls_ecp_group grp;
    mbedtls_mpi r;
    mbedtls_mpi s;
    mbedtls_mpi d;

    if ((HI_NULL == pstParams )
        || (HI_NULL == pu8PrivKey )
        || (HI_NULL == pu8Message )
        || (HI_NULL == pu8SigR )
        || (HI_NULL == pu8SigS ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pstParams->pu8p)
        || (HI_NULL == pstParams->pu8b )
        || (HI_NULL == pstParams->pu8a )
        || (HI_NULL == pstParams->pu8GX)
        || (HI_NULL == pstParams->pu8GY )
        || (HI_NULL == pstParams->pu8n ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == pstParams->u32keySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    switch(enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        u32HashLen = 20;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
        u32HashLen = 28;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        u32HashLen = 32;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
        u32HashLen = 48;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
        u32HashLen = 64;
        break;
    default:
        HI_ERR_CIPHER("Invalid sha type 0x%x\n", enShaType);
        return HI_FAILURE;
    }

    stHashAttr.eShaType = enShaType;
    ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashInit error\n");
        return ret;
    }
    ret = HI_MPI_CIPHER_HashUpdate(HashHandle, pu8Message, u32MessageSize);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashUpdate error\n");
        return ret;
    }
    ret = HI_MPI_CIPHER_HashFinal(HashHandle, u8Hash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashUpdate error\n");
        return ret;
    }

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_mpi_init(&r);
    mbedtls_mpi_init(&s);
    mbedtls_mpi_init(&d);

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&grp.P, pstParams->pu8p, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.A, pstParams->pu8a, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.B, pstParams->pu8b, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.N, pstParams->pu8n, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.X, pstParams->pu8GX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.Y, pstParams->pu8GY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp.G.Z, 1 ) );
    grp.pbits = mbedtls_mpi_bitlen( &grp.P );
    grp.nbits = mbedtls_mpi_bitlen( &grp.N );
    grp.h = pstParams->u32h;

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &d, pu8PrivKey, pstParams->u32keySize ) );

    MBEDTLS_MPI_CHK( mbedtls_ecdsa_sign(&grp, &r, &s, &d, u8Hash, u32HashLen, Mbedtls_GetRandomNumber, 0 ));

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &r, pu8SigR, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &s, pu8SigS, pstParams->u32keySize ) );

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_mpi_free(&r);
    mbedtls_mpi_free(&s);
    mbedtls_mpi_free(&d);

    return( ret );
}

HI_S32 HI_MPI_CIPHER_EcdsaVerify(HI_UNF_CIPHER_ECC_PARAM_S *pstParams,
								 HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY,
							     HI_UNF_CIPHER_HASH_TYPE_E enShaType,
							     HI_U8 *pu8Message, HI_U32 u32MessageSize,
							     HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    HI_S32 ret;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN];
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U32 u32HashLen;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi r;
    mbedtls_mpi s;

    if ((HI_NULL == pstParams )
        || (HI_NULL == pu8PubKeyX )
        || (HI_NULL == pu8PubKeyY )
        || (HI_NULL == pu8Message )
        || (HI_NULL == pu8SigR )
        || (HI_NULL == pu8SigS ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_NULL == pstParams->pu8p)
        || (HI_NULL == pstParams->pu8b )
        || (HI_NULL == pstParams->pu8a )
        || (HI_NULL == pstParams->pu8GX)
        || (HI_NULL == pstParams->pu8GY )
        || (HI_NULL == pstParams->pu8n ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (0 == pstParams->u32keySize)
    {
        HI_ERR_CIPHER("Invalid Key Size!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    switch(enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        u32HashLen = 20;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
        u32HashLen = 28;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        u32HashLen = 32;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
        u32HashLen = 48;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA512:
        u32HashLen = 64;
        break;
    default:
        HI_ERR_CIPHER("Invalid sha type 0x%x\n", enShaType);
        return HI_FAILURE;
    }

    stHashAttr.eShaType = enShaType;
    ret = HI_MPI_CIPHER_HashInit(&stHashAttr, &HashHandle);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashInit error\n");
        return ret;
    }
    ret = HI_MPI_CIPHER_HashUpdate(HashHandle, pu8Message, u32MessageSize);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashUpdate error\n");
        return ret;
    }
    ret = HI_MPI_CIPHER_HashFinal(HashHandle, u8Hash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("HI_MPI_CIPHER_HashUpdate error\n");
        return ret;
    }

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&r);
    mbedtls_mpi_init(&s);

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary(&grp.P, pstParams->pu8p, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.A, pstParams->pu8a, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.B, pstParams->pu8b, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.N, pstParams->pu8n, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.X, pstParams->pu8GX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &grp.G.Y, pstParams->pu8GY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &grp.G.Z, 1 ) );
    grp.pbits = mbedtls_mpi_bitlen( &grp.P );
    grp.nbits = mbedtls_mpi_bitlen( &grp.N );
    grp.h = pstParams->u32h;

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &Q.X, pu8PubKeyX, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &Q.Y, pu8PubKeyY, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &Q.Z, 1 ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &r, pu8SigR, pstParams->u32keySize ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &s, pu8SigS, pstParams->u32keySize ) );

    MBEDTLS_MPI_CHK( mbedtls_ecdsa_verify(&grp, u8Hash, u32HashLen, &Q, &r, &s));

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&r);
    mbedtls_mpi_free(&s);

    return( ret );
}

/*#################################SM2 Start##################################*/
HI_S32 HI_MPI_CIPHER_Sm2Sign(HI_UNF_CIPHER_SM2_SIGN_S *pstSm2Sign, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S)
{
    HI_ERR_CIPHER("SM2 don't support\n");
    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_Sm2Verify(HI_UNF_CIPHER_SM2_VERIFY_S *pstSm2Verify, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S)
{
    HI_ERR_CIPHER("SM2 don't support\n");
    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_Sm2Encrypt(HI_UNF_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen)
{
    HI_ERR_CIPHER("SM2 don't support\n");
    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_Sm2Decrypt(HI_UNF_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C, HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen)
{
    HI_ERR_CIPHER("SM2 don't support\n");
    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_Sm2GenKey(HI_UNF_CIPHER_SM2_KEY_S *pstSm2Key)
{
    HI_ERR_CIPHER("SM2 don't support\n");
    return HI_FAILURE;
}

HI_S32 HI_MPI_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen)
{
    HI_ERR_CIPHER("Don't support get tag\n");
    return HI_FAILURE;
}

