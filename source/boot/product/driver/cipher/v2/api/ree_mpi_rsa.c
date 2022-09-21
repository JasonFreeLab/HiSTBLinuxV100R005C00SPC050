/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_rsa.c
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

#define RSA_SIGN                     1
#define ASN1_HASH_SHA1    "\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"
#define ASN1_HASH_SHA224  "\x30\x2D\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x04\x05\x00\x04\x1C"
#define ASN1_HASH_SHA256  "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x01\x05\x00\x04\x20"
#define ASN1_HASH_SHA384  "\x30\x41\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x02\x05\x00\x04\x30"
#define ASN1_HASH_SHA512  "\x30\x51\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x03\x05\x00\x04\x40"

static const HI_S8 EMPTY_L_SHA1[]   = "\xda\x39\xa3\xee\x5e\x6b\x4b\x0d\x32\x55\xbf\xef\x95\x60\x18\x90\xaf\xd8\x07\x09";
static const HI_S8 EMPTY_L_SHA224[] = "\xd1\x4a\x02\x8c\x2a\x3a\x2b\xc9\x47\x61\x02\xbb\x28\x82\x34\xc4\x15\xa2\xb0\x1f\x82\x8e\xa6\x2a\xc5\xb3\xe4\x2f";
static const HI_S8 EMPTY_L_SHA256[] = "\xe3\xb0\xc4\x42\x98\xfc\x1c\x14\x9a\xfb\xf4\xc8\x99\x6f\xb9\x24\x27\xae\x41\xe4\x64\x9b\x93\x4c\xa4\x95\x99\x1b\x78\x52\xb8\x55";
static const HI_S8 EMPTY_L_SHA384[] = "\x38\xb0\x60\xa7\x51\xac\x96\x38\x4c\xd9\x32\x7e\xb1\xb1\xe3\x6a\x21\xfd\xb7\x11\x14\xbe\x07\x43\x4c\x0c\xc7\xbf\x63\xf6\xe1\xda\x27\x4e\xde\xbf\xe7\x6f\x65\xfb\xd5\x1a\xd2\xf1\x48\x98\xb9\x5b";
static const HI_S8 EMPTY_L_SHA512[] = "\xcf\x83\xe1\x35\x7e\xef\xb8\xbd\xf1\x54\x28\x50\xd6\x6d\x80\x07\xd6\x20\xe4\x05\x0b\x57\x15\xdc\x83\xf4\xa9\x21\xd3\x6c\xe9\xce\x47\xd0\xd1\x3c\x5d\x85\xf2\xb0\xff\x83\x18\xd2\x87\x7e\xec\x2f\x63\xb9\x31\xbd\x47\x41\x7a\x81\xa5\x38\x32\x7a\xf9\x27\xda\x3e";

#ifdef SIC_RSA_LIB_ENABLE
static HI_U32 RSA_Bn2Bin( const HI_U32 *pu32bn, HI_U8 *pbin, HI_S32 u32Len)
{
#if 1
    HI_S32 i, j, n;

    n = u32Len;

    memset( pbin, 0, u32Len);

    for( i = u32Len - 1, j = 0; n > 0; i--, j++, n-- )
        pbin[i] = (unsigned char)( pu32bn[j / 4] >> ((j % 4) << 3) );
#else
    memcpy(pbin, pu32bn, u32Len);
#endif
    return( 0 );
}

HI_U32 RSA_Bin2Bn(HI_U32 *pu32bn, const HI_U8 *pbin, HI_S32 u32Len)
{
#if 1
    HI_S32 i, j, n;

    memset(pu32bn, 0, u32Len);

    for( n = 0; n < u32Len; n++ )
        if( pbin[n] != 0 )
            break;

    for( i = u32Len - 1, j = 0; i >= n; i--, j++ )
        pu32bn[j / 4] |= ((int) pbin[i]) << ((j % 4) << 3);
#else
    memcpy(pu32bn, pbin, u32Len);
#endif

    return( 0 );
}

HI_S32 RSA_Private(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey, HI_U8 *pu8In, HI_U8 *pu8Out)
{
    HI_S32 ret;
    HI_U32 *pu32KeyBuf = HI_NULL;
    HI_U32 *pu32N;
    HI_U32 *pu32D;
    HI_U32 *pu32P;
    HI_U32 *pu32Q;
    HI_U32 *pu32DP;
    HI_U32 *pu32DQ;
    HI_U32 *pu32QP;
    HI_U32 *pu32M;
    HI_U32 *pu32C;

    if (((pstPriKey->pu8D == HI_NULL)
        && (pstPriKey->pu8N == HI_NULL))
        &&((pstPriKey->pu8P == HI_NULL)
        || (pstPriKey->pu8Q == HI_NULL)
        || (pstPriKey->pu8DP == HI_NULL)
        || (pstPriKey->pu8DQ == HI_NULL)
        || (pstPriKey->pu8QP == HI_NULL)))
    {
        HI_ERR_CIPHER("key is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pu8In== HI_NULL) || (pu8Out== HI_NULL))
    {
        HI_ERR_CIPHER("in/out is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    pu32KeyBuf = (HI_U32*)malloc(pstPriKey->u16NLen * 6);
    if (pu32KeyBuf == HI_NULL)
    {
        HI_ERR_CIPHER("RSA malloc failed\n");
        return HI_FAILURE;
    }

    pu32M = pu32KeyBuf;
    pu32C = pu32M + pstPriKey->u16NLen/4;

    RSA_Bin2Bn(pu32M, pu8In, pstPriKey->u16NLen);

    if(pstPriKey->pu8D == HI_NULL)
    {
        pu32P = pu32C + pstPriKey->u16NLen/4;
        pu32Q = pu32P + pstPriKey->u16PLen/4;
        pu32DP = pu32Q + pstPriKey->u16QLen/4;
        pu32DQ = pu32DP + pstPriKey->u16DPLen/4;
        pu32QP = pu32DQ + pstPriKey->u16DQLen/4;

        RSA_Bin2Bn(pu32P, pstPriKey->pu8P, pstPriKey->u16PLen);
        RSA_Bin2Bn(pu32Q, pstPriKey->pu8Q, pstPriKey->u16QLen);
        RSA_Bin2Bn(pu32DP, pstPriKey->pu8DP, pstPriKey->u16DPLen);
        RSA_Bin2Bn(pu32DQ, pstPriKey->pu8DQ, pstPriKey->u16DQLen);
        RSA_Bin2Bn(pu32QP, pstPriKey->pu8QP, pstPriKey->u16QPLen);
/*
        HI_PRINT_HEX ("N", (HI_U8*)pstPriKey->pu8N, pstPriKey->u16NLen);
        HI_PRINT_HEX ("P", (HI_U8*)pstPriKey->pu8P, pstPriKey->u16PLen);
        HI_PRINT_HEX ("Q", (HI_U8*)pstPriKey->pu8Q, pstPriKey->u16PLen);
        HI_PRINT_HEX ("DP", (HI_U8*)pstPriKey->pu8DP, pstPriKey->u16PLen);
        HI_PRINT_HEX ("DQ", (HI_U8*)pstPriKey->pu8DQ, pstPriKey->u16PLen);
        HI_PRINT_HEX ("QP", (HI_U8*)pstPriKey->pu8QP, pstPriKey->u16PLen);
        HI_PRINT_HEX ("M", (HI_U8*)pu8In, pstPriKey->u16NLen);
*/
        ret = rsa_crt_dec_prim(pu32P, pu32Q, pu32DP, pu32DQ, pu32QP, pu32M, pstPriKey->u16NLen/8, pu32C);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("rsa_crt_dec_prim failed, ret = %x\n", ret);
            printf("rsa_crt_dec_prim test end......\n");
            return HI_FAILURE;
        }
    }
    else
    {
        pu32N = pu32C + pstPriKey->u16NLen/4;
        pu32D = pu32N + pstPriKey->u16NLen/4;

        RSA_Bin2Bn(pu32N, pstPriKey->pu8N, pstPriKey->u16NLen);
        RSA_Bin2Bn(pu32D, pstPriKey->pu8D, pstPriKey->u16DLen);
/*
        HI_PRINT_HEX ("N", (HI_U8*)pstPriKey->pu8N, pstPriKey->u16NLen);
        HI_PRINT_HEX ("D", (HI_U8*)pstPriKey->pu8D, pstPriKey->u16DLen);
        HI_PRINT_HEX ("M", (HI_U8*)pu8In, pstPriKey->u16NLen);
*/
        ret = rsa_dec_prim(pu32N, pu32M, pu32D, pstPriKey->u16NLen/4, pu32C);
//        HI_PRINT_HEX ("C", (HI_U8*)pu32C, pstPriKey->u16NLen);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("rsa_dec_prim failed, ret = %d\n", ret);
            printf("rsa_dec_prim test end......\n");
            return HI_FAILURE;
        }
    }
    RSA_Bn2Bin(pu32C, pu8Out, pstPriKey->u16NLen);

    free(pu32KeyBuf);
    pu32KeyBuf = HI_NULL;

    return HI_SUCCESS;
}

HI_S32 RSA_Public(HI_UNF_CIPHER_RSA_PUB_KEY_S *pstPubKey, HI_U8 *pu8In, HI_U8 *pu8Out)
{
    HI_S32 ret;
    HI_U32 *pu32KeyBuf = HI_NULL;
    HI_U32 *pu32N;
    HI_U32 *pu32E;
    HI_U32 *pu32M;
    HI_U32 *pu32C;

    if ((pstPubKey->pu8N == HI_NULL) || (pstPubKey->pu8E == HI_NULL))
    {
        HI_ERR_CIPHER("key is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pu8In== HI_NULL) || (pu8Out== HI_NULL))
    {
        HI_ERR_CIPHER("in/out is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    pu32KeyBuf = (HI_U32*)malloc(pstPubKey->u16NLen * 6);
    if (pu32KeyBuf == HI_NULL)
    {
        HI_ERR_CIPHER("RSA malloc failed\n");
        return HI_FAILURE;
    }

    pu32M = pu32KeyBuf;
    pu32C = pu32M + pstPubKey->u16NLen/4;

    RSA_Bin2Bn(pu32M, pu8In, pstPubKey->u16NLen);

    pu32N = pu32C + pstPubKey->u16NLen/4;
    pu32E = pu32N + pstPubKey->u16NLen/4;


    RSA_Bin2Bn(pu32N, pstPubKey->pu8N, pstPubKey->u16NLen);
    RSA_Bin2Bn(pu32E, pstPubKey->pu8E, pstPubKey->u16ELen);
/*
    HI_PRINT_HEX ("N", (HI_U8*)pu32N, pstPubKey->u16NLen);
    HI_PRINT_HEX ("E", (HI_U8*)pu32E, pstPubKey->u16ELen);
    HI_PRINT_HEX ("M", (HI_U8*)pu32M, pstPubKey->u16NLen);
*/
    ret = rsa_enc_prim(pu32N, pu32M, pstPubKey->u16NLen/4, pu32E, pstPubKey->u16ELen/4, pu32C);

    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_Crt2Nocrt failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    RSA_Bn2Bin(pu32C, pu8Out, pstPubKey->u16NLen);
//    HI_PRINT_HEX ("C", pu8Out, pstPubKey->u16NLen);

    free(pu32KeyBuf);
    pu32KeyBuf = HI_NULL;

    return HI_SUCCESS;
}
#else
HI_S32 RSA_Crt2Nocrt(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey,HI_U8 *pu8Output)
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

HI_S32 RSA_Private(HI_UNF_CIPHER_RSA_PRI_KEY_S *pstPriKey, HI_U8 *pu8In, HI_U8 *pu8Out)
{
    HI_S32 ret;
    CIPHER_RSA_DATA_S stRsaData;

    if (pstPriKey->pu8N == HI_NULL)
    {
        HI_ERR_CIPHER("key is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

   if(pstPriKey->pu8D == HI_NULL)
   {
        ret = RSA_Crt2Nocrt(pstPriKey, pu8Out);
        if (ret != HI_SUCCESS)
        {
       HI_ERR_CIPHER("RSA_Crt2Nocrt failed, ret = %x\n", ret);
       return HI_FAILURE;
        }
        stRsaData.pu8K  = pu8Out;
        stRsaData.u16KLen = pstPriKey->u16NLen;
   }
   else
   {
        stRsaData.pu8K = pstPriKey->pu8D;
        stRsaData.u16KLen = pstPriKey->u16DLen;
   }

    stRsaData.u16NLen = pstPriKey->u16NLen;
    stRsaData.pu8N = pstPriKey->pu8N;
    stRsaData.pu8Input = pu8In;
    stRsaData.pu8Output = pu8Out;
    stRsaData.u32DataLen = pstPriKey->u16NLen;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
}

HI_S32 RSA_Public(HI_UNF_CIPHER_RSA_PUB_KEY_S *pstPubKey, HI_U8 *pu8In, HI_U8 *pu8Out)
{
    CIPHER_RSA_DATA_S stRsaData;

    INLET_PARAM_CHECK_POINT_NULL(pstPubKey);
    INLET_PARAM_CHECK_POINT_NULL(pstPubKey->pu8N);
    INLET_PARAM_CHECK_POINT_NULL(pstPubKey->pu8E);
    INLET_PARAM_CHECK_POINT_NULL(pu8In);
    INLET_PARAM_CHECK_POINT_NULL(pu8Out);

    stRsaData.pu8N = pstPubKey->pu8N;
    stRsaData.pu8K = pstPubKey->pu8E;
    stRsaData.u16NLen = pstPubKey->u16NLen;
    stRsaData.u16KLen = pstPubKey->u16ELen;
    stRsaData.pu8Input = pu8In;
    stRsaData.pu8Output = pu8Out;
    stRsaData.u32DataLen = pstPubKey->u16NLen;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CALCRSA, &stRsaData);
}
#endif

static HI_S32 RSA_GetAttr(HI_U32 u32SchEme,
                          HI_U16 u16NLen,
                          HI_U32 *pu32HLen,
                          HI_U32 *pu32KeyLen,
                          HI_UNF_CIPHER_HASH_TYPE_E *pstenHashType)
{
    HI_S32 ret = HI_FAILURE;

    if (u16NLen <= 512)
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
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        *pu32HLen = 20;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
        *pu32HLen = 28;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA224;
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        *pu32HLen = 32;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        *pu32HLen = 48;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA384;
        ret = HI_SUCCESS;
        break;
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
    case HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
        *pu32HLen = 64;
        *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_SHA512;
        ret = HI_SUCCESS;
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
    HI_S32 Ret = HI_FAILURE;
    HI_U32 i,j, u32Outlen = 0;
    HI_U8 u8Cnt[4];
    HI_U8 u8Md[HASH_RESULT_MAX_LEN];
    HI_U32 u32MdLen;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

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

    return Ret;
}

HI_S32 Mbedtls_GetRandomNumber(HI_VOID *param, HI_U8 *pu8Rand, size_t u32Size)
{
    HI_U32 i;
    HI_U32 u32Rand = 0;

    cipher_memset_s(pu8Rand, u32Size, 0, u32Size);
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

static HI_U32 RSA_GetBitNum(HI_U8 *pu8BigNum, HI_U32 u32NumLen)
{
    static const HI_S8 u8Bits[16] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};
    HI_U32 i;
    HI_U32 u32Num;

        INLET_PARAM_CHECK_POINT_NULL(pu8BigNum);

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
    HI_S32 ret = HI_FAILURE;
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
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA384)
    {
        pu8LHASH = EMPTY_L_SHA384;
    }
    else if( enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA512)
    {
        pu8LHASH = EMPTY_L_SHA512;
    }

    if (u32InLen > u32KeyLen - 2 * u32HLen - 2)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen = 0;
    pu8Output[0] = 0;
    pu8Seed = pu8Output + 1;
    pu8DB = pu8Output + u32HLen + 1;
    u32DBLen = u32KeyLen - u32HLen -1;

    /*set lHash*/
    cipher_memcpy_s(pu8DB, u32DBLen, pu8LHASH, u32HLen);

    /*set PS with 0x00*/
    cipher_memset_s(&pu8DB[u32HLen], u32DBLen - u32HLen, 0,
        u32DBLen - u32InLen - u32HLen -1);

    /*set 0x01 after PS*/
    pu8DB[u32DBLen - u32InLen - 1] = 0x01;

    /*set M*/
    cipher_memcpy_s(&pu8DB[u32DBLen - u32InLen], u32InLen, pu8Input, u32InLen);

    /*compute maskedDB*/
    (HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, pu8Seed, u32HLen);
    ret = RSA_PKCS1_MGF1(enHashType, pu8Seed, u32HLen, pu8DB, u32KeyLen - u32HLen - 1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    /*compute maskedSeed*/
    ret = RSA_PKCS1_MGF1(enHashType, pu8DB, u32KeyLen - u32HLen - 1, pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    *pu32OutLen = u32KeyLen;

     return ret;
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
    cipher_memcpy_s(&pu8Output[u32Index], u32KeyLen - u32Index, pu8Input, u32InLen);

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
        cipher_memset_s(pu8EB, u32KeyLen - (HI_U32)(pu8EB - pu8Output), 0x00, u32PLen);
        break;
    case 0x01:
        cipher_memset_s(pu8EB, u32KeyLen - (HI_U32)(pu8EB - pu8Output), 0xFF, u32PLen);
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
    cipher_memcpy_s(pu8EB, u32KeyLen - (HI_U32)(pu8EB - pu8Output), pu8Input, u32InLen);

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
    HI_U32 u32BufLen;

    *pu32OutLen = u32KeyLen;

     p = pu8Output;
    *p++ = 0;
    *p++ = RSA_SIGN;
    switch(enHashType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        u32PadLen = u32KeyLen - 3 - 35;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memset_s(p, u32BufLen, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s(p, u32BufLen, ASN1_HASH_SHA1, 15);
        p += 15;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s(p, u32BufLen, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA224:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memset_s(p, u32BufLen, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, ASN1_HASH_SHA224, 19);
        p += 19;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memset_s(p, u32BufLen, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, ASN1_HASH_SHA256, 19);
        p += 19;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, pu8Input, u32InLen);
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA384:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memset_s(p, u32BufLen, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, ASN1_HASH_SHA384, 19);
        p += 19;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, pu8Input, u32InLen);
        break;
     case HI_UNF_CIPHER_HASH_TYPE_SHA512:
        u32PadLen = u32KeyLen - 3 - 19 -u32InLen;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memset_s(p, u32BufLen, 0xFF, u32PadLen);
        p += u32PadLen;
        *p++ = 0;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32KeyLen, ASN1_HASH_SHA512, 19);
        p += 19;
        u32BufLen = u32KeyLen - (HI_U32)(p - pu8Output);
        cipher_memcpy_s( p, u32BufLen, pu8Input, u32InLen);
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
                    |                    |
                    V                    |      +--+
                    xor <----- MGF <----|      |bc|
                    |                    |      +--+
                    |                    |      |
                    V                    V      V
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
    HI_U32 ret = HI_FAILURE;
    HI_U32 u32SLen;
    HI_U8 *pu8M;
    HI_U8 u8Salt[HASH_RESULT_MAX_LEN];
    HI_U8 *pu8MaskedDB;
    HI_U8 *pu8Maskedseed;
    HI_U32 u32Index;
    HI_U32 u32KeyLen;
    HI_U32 u32MSBits;
    HI_U32 u32Mlen;
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

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

    if (u32MSBits == 0)
    {
        *pu8Output++ = 0;
        u32KeyLen--;
    }

    pu8MaskedDB = pu8Output;
    pu8Maskedseed = pu8Output + u32KeyLen - u32HLen -1;

    /* Generate a random octet string salt of length sLen */
    (HI_VOID)Mbedtls_GetRandomNumber(HI_NULL, u8Salt, u32SLen);
    u32Mlen = u32SLen + u32HLen + 8;
    pu8M = (HI_U8*)malloc(u32Mlen);
    if (pu8M == HI_NULL)
    {
        HI_ERR_CIPHER("malloc failed\n");
        return HI_FAILURE;
    }

    /*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
    u32Index = 0;
    cipher_memset_s(pu8M, u32Mlen, 0x00, 8);
    u32Index+=8;
    cipher_memcpy_s(&pu8M[u32Index], u32Mlen - u32Index, pu8Input, u32InLen);
    u32Index+=u32InLen;
    cipher_memcpy_s(&pu8M[u32Index], u32Mlen - u32Index, u8Salt, u32SLen);
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
    cipher_memset_s(&pu8MaskedDB[u32Index], u32KeyLen - u32Index, 0x00, u32KeyLen - u32SLen -u32HLen - 2);
    u32Index+=u32KeyLen - u32SLen -u32HLen - 2;
    pu8MaskedDB[u32Index++] = 0x01;
    cipher_memcpy_s(&pu8MaskedDB[u32Index], u32KeyLen - u32Index, u8Salt, u32SLen);
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
    HI_S32 ret = HI_FAILURE;
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
        if((pu8DB[i] == 0x01))
        {
            cipher_memcpy_s(pu8Output, u32KeyLen, pu8DB+i+1, u32KeyLen - u32HLen - i - 2);
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
            cipher_memcpy_s(pu8Output, u32KeyLen, &pu8Input[u32Index+1], u32KeyLen - 1 - u32Index);
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
    cipher_memcpy_s(pu8Output, u32KeyLen, pu8EB, *pu32OutLen);

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
    HI_U32 ret = HI_FAILURE;
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
            cipher_memcpy_s(pu8Output, u32KeyLen, p + 15, u32HLen);
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
            cipher_memcpy_s(pu8Output, u32KeyLen, p + 19, u32HLen);
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
            cipher_memcpy_s(pu8Output, u32KeyLen, p + 19, u32HLen);
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
            cipher_memcpy_s(pu8Output, u32KeyLen, p + 19, u32HLen);
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
            cipher_memcpy_s(pu8Output, u32KeyLen, p + 19, u32HLen);
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
    HI_U32 ret = HI_FAILURE;
    HI_U32 u32SLen;
    HI_U8 *pu8M = HI_NULL;
    HI_U32 u32MLen;
    HI_U8 u8Salt[HASH_RESULT_MAX_LEN] = {0};
    HI_U8 u8H[HASH_RESULT_MAX_LEN] = {0};
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

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

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
    cipher_memcpy_s(u8Salt, sizeof(u8Salt), &pu8MaskedDB[u32Index], u32SLen);

    u32MLen = u32SLen + u32HLen + 8;
    pu8M = (HI_U8*)cipher_malloc(u32MLen);
    if (pu8M == NULL)
    {
        HI_ERR_CIPHER("malloc failed\n");
        return HI_FAILURE;
    }

    /*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
    u32Index = 0;
    cipher_memset_s(pu8M, u32MLen, 0x00, 8);
    u32Index+=8;
    cipher_memcpy_s(&pu8M[u32Index], u32MLen - u32Index, pu8MHash, u32HLen);
    u32Index+=u32HLen;
    cipher_memcpy_s(&pu8M[u32Index], u32MLen - u32Index, u8Salt, u32SLen);
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

    ret = cipher_memcmp_s(u8H, pu8Maskedseed, u32HLen);
    if (ret != 0)
    {
        HI_ERR_CIPHER("consistent, hash compare failed\n");
        ret = HI_FAILURE;
    }

    return ret;
}

HI_S32 HI_MPI_CIPHER_RsaPublicEncrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];

    INLET_PARAM_CHECK_POINT_NULL(pstRsaEnc);
    INLET_PARAM_CHECK_POINT_NULL(pu8Input);
    INLET_PARAM_CHECK_POINT_NULL(pu8Output);
    INLET_PARAM_CHECK_POINT_NULL(pu32OutLen);
    INLET_PARAM_CHECK_U32_ZERO(u32InLen);

    ret = RSA_GetAttr(pstRsaEnc->enScheme, pstRsaEnc->stPubKey.u16NLen,
            &u32HLen, &u32KeyLen, &enHashType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return ret;
    }

    INLET_PARAM_CHECK_U32_MAX(u32InLen, u32KeyLen);

    cipher_memset_s(u8EM, sizeof(u8EM), 0, sizeof(u8EM));

    switch(pstRsaEnc->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        /*if u32InLen < u32KeyLen, padding 0 before input data*/
        *pu32OutLen = u32KeyLen;
        cipher_memcpy_s(u8EM+(u32KeyLen - u32InLen),
            sizeof(u8EM) - (u32KeyLen - u32InLen), pu8Input, u32InLen);
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

    return RSA_Public(&pstRsaEnc->stPubKey, u8EM, pu8Output);

}

HI_S32 HI_MPI_CIPHER_RsaPrivateDecrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;

    INLET_PARAM_CHECK_POINT_NULL(pstRsaDec);
    INLET_PARAM_CHECK_POINT_NULL(pu8Input);
    INLET_PARAM_CHECK_POINT_NULL(pu8Output);
    INLET_PARAM_CHECK_POINT_NULL(pu32OutLen);

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

    ret = RSA_Private(&pstRsaDec->stPriKey, pu8Input, u8EM);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_Private failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    switch(pstRsaDec->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        *pu32OutLen = u32InLen;
        cipher_memcpy_s(pu8Output, u32KeyLen, u8EM, u32KeyLen);
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

HI_S32 HI_MPI_CIPHER_RsaPrivateEncrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaEnc,
                                    HI_U8 *pu8Input, HI_U32 u32InLen,
                                    HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];

    INLET_PARAM_CHECK_POINT_NULL(pstRsaEnc);
    INLET_PARAM_CHECK_POINT_NULL(pu8Input);
    INLET_PARAM_CHECK_POINT_NULL(pu8Output);
    INLET_PARAM_CHECK_POINT_NULL(pu32OutLen);
    INLET_PARAM_CHECK_U32_ZERO(u32InLen);

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

    cipher_memset_s(u8EM, sizeof(u8EM), 0, sizeof(u8EM));

    switch(pstRsaEnc->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        /*if u32InLen < u32KeyLen, padding 0 before input data*/
        *pu32OutLen = u32KeyLen;
        cipher_memcpy_s(u8EM+(u32KeyLen - u32InLen),
            sizeof(u8EM) - (u32KeyLen - u32InLen), pu8Input, u32InLen);
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

    return RSA_Private(&pstRsaEnc->stPriKey, u8EM, pu8Output);

}

HI_S32 HI_MPI_CIPHER_RsaPublicDecrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                               HI_U8 *pu8Input, HI_U32 u32InLen,
                               HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    HI_U8  u8BT;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;

    INLET_PARAM_CHECK_POINT_NULL(pstRsaDec);
    INLET_PARAM_CHECK_POINT_NULL(pu8Input);
    INLET_PARAM_CHECK_POINT_NULL(pu8Output);
    INLET_PARAM_CHECK_POINT_NULL(pu32OutLen);
    INLET_PARAM_CHECK_U32_ZERO(u32InLen);

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

    ret = RSA_Public(&pstRsaDec->stPubKey, pu8Input, u8EM);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CMD_CIPHER_CALCRSA failed, ret = %x\n", ret);
        return HI_FAILURE;
    }

    switch(pstRsaDec->enScheme)
    {
    case HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        *pu32OutLen = u32InLen;
        cipher_memcpy_s(pu8Output, u32KeyLen, u8EM, u32KeyLen);
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

HI_S32 HI_MPI_CIPHER_RsaSign(HI_UNF_CIPHER_RSA_SIGN_S *pstRsaSign,
                             HI_U8 *pu8InData, HI_U32 u32InDataLen,
                             HI_U8 *pu8HashData,
                             HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen)
{
    HI_U32 u32KeyLen;
    HI_U32 u32HLen;
    HI_U32 u32EmBit;
    HI_U8  u8Hash[32];
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_S32 ret = HI_FAILURE;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U8 *pHash;

    INLET_PARAM_CHECK_POINT_NULL(pstRsaSign);
    INLET_PARAM_CHECK_POINT_NULL(pu8OutSign);
    INLET_PARAM_CHECK_POINT_NULL(pu32OutSignLen);

    if ((pu8InData == HI_NULL) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((u32InDataLen == 0) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("inlen is 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pstRsaSign->stPriKey.pu8N == HI_NULL)
    {
        HI_ERR_CIPHER("key is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

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
            HI_ERR_CIPHER("HI_MPI_CIPHER_HashUpdate error\n");
            return ret;
        }
        pHash = u8Hash;
    }
    else
    {
        pHash = pu8HashData;
    }

    cipher_memset_s(u8EM, sizeof(u8EM), 0, sizeof(u8EM));
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
        u32EmBit = RSA_GetBitNum(pstRsaSign->stPriKey.pu8N, u32KeyLen);
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

    return RSA_Private(&pstRsaSign->stPriKey, u8EM, pu8OutSign);
}

HI_S32 HI_MPI_CIPHER_RsaVerify(HI_UNF_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    HI_U32 ret = HI_FAILURE;
    HI_U32 u32KeyLen;
    HI_U8  u8EM[CIPHER_MAX_RSA_KEY_LEN];
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle = 0;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN] = {0};
    HI_U8  u8SignHash[HASH_RESULT_MAX_LEN] = {0};
    HI_U32 u32HLen;
    HI_U32 u32EmBit;
    HI_U8  *pHash;

    INLET_PARAM_CHECK_POINT_NULL(pstRsaVerify);
    INLET_PARAM_CHECK_POINT_NULL(pu8InSign);

    if ((pu8InData == HI_NULL) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((u32InDataLen == 0) && (pu8HashData == HI_NULL))
    {
        HI_ERR_CIPHER("inlen is 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
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

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));

    ret = RSA_Public(&pstRsaVerify->stPubKey, pu8InSign, u8EM);
    if (ret != HI_SUCCESS)
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
        u32EmBit = RSA_GetBitNum(pstRsaVerify->stPubKey.pu8N, u32KeyLen);
        ret = RSA_padding_check_PKCS1_PSS(enHashType, u32HLen, u32EmBit,
               u8EM, u32InSignLen, pHash);
        break;
    default:
        HI_ERR_CIPHER("invalid scheme; 0x%x\n", pstRsaVerify->enScheme);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}

