/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_ecc.c
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"
#include "mbedtls/rsa.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/ecdsa.h"

HI_S32 HI_MPI_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize)
{
    HI_UNF_CIPHER_RSA_PUB_KEY_S stPubKey;

    INLET_PARAM_CHECK_U32_ZERO(u32KeySize);

    cipher_memset_s(&stPubKey, sizeof(stPubKey), 0, sizeof(HI_UNF_CIPHER_RSA_PUB_KEY_S));

    stPubKey.pu8N = pu8P;
    stPubKey.pu8E = pu8PrivKey;
    stPubKey.u16NLen = u32KeySize;
    stPubKey.u16ELen = u32KeySize;

    return RSA_Public(&stPubKey, pu8OtherPubKey, pu8SharedSecret);
}

HI_S32 HI_MPI_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                                   HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                                   HI_U32 u32KeySize)
{
    HI_S32 ret= HI_FAILURE;
    HI_UNF_CIPHER_RSA_PUB_KEY_S stPubKey;
    INLET_PARAM_CHECK_POINT_NULL(pu8P);
    INLET_PARAM_CHECK_U32_ZERO(u32KeySize);

    if ((HI_NULL == pu8InputPrivKey ) && (HI_NULL == pu8OutputPrivKey ))
    {
        HI_ERR_CIPHER("Invalid param!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    cipher_memset_s(&stPubKey, sizeof(stPubKey), 0, sizeof(HI_UNF_CIPHER_RSA_PUB_KEY_S));

    if (pu8P[0] == 0x00)
    {
        HI_ERR_CIPHER("Invalid P[0], must large than 0!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pu8InputPrivKey == HI_NULL)
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
        stPubKey.pu8E = pu8OutputPrivKey;
    }
    else
    {
        stPubKey.pu8E = pu8InputPrivKey;
    }

    stPubKey.pu8N = pu8P;
    stPubKey.u16NLen = u32KeySize;
    stPubKey.u16ELen = u32KeySize;

    return RSA_Public(&stPubKey, pu8G, pu8PubKey);
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
    HI_S32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi z;
    mbedtls_mpi d;

    INLET_PARAM_CHECK_POINT_NULL(pstParams);
    INLET_PARAM_CHECK_POINT_NULL(pu8PrivKey);
    INLET_PARAM_CHECK_POINT_NULL(pu8OtherPubKeyX);
    INLET_PARAM_CHECK_POINT_NULL(pu8OtherPubKeyY);
    INLET_PARAM_CHECK_POINT_NULL(pu8SharedSecret);

    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8p);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8a);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8b);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GX);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GY);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8n);

    INLET_PARAM_CHECK_U32_ZERO(pstParams->u32keySize);

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
    HI_S32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;

    INLET_PARAM_CHECK_POINT_NULL(pstParams);
    INLET_PARAM_CHECK_POINT_NULL(pu8PubKeyX);
    INLET_PARAM_CHECK_POINT_NULL(pu8PubKeyY);

    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8p);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8a);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8b);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GX);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GY);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8n);

    INLET_PARAM_CHECK_U32_ZERO(pstParams->u32keySize);

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
    HI_S32 ret = HI_FAILURE;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN];
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U32 u32HashLen;
    mbedtls_ecp_group grp;
    mbedtls_mpi r;
    mbedtls_mpi s;
    mbedtls_mpi d;

    INLET_PARAM_CHECK_POINT_NULL(pstParams);
    INLET_PARAM_CHECK_POINT_NULL(pu8PrivKey);
    INLET_PARAM_CHECK_POINT_NULL(pu8Message);
    INLET_PARAM_CHECK_POINT_NULL(pu8SigR);
    INLET_PARAM_CHECK_POINT_NULL(pu8SigS);

    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8p);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8a);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8b);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GX);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GY);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8n);

    INLET_PARAM_CHECK_U32_ZERO(pstParams->u32keySize);

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
    HI_S32 ret = HI_FAILURE;
    HI_U8  u8Hash[HASH_RESULT_MAX_LEN];
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
    HI_U32 u32HashLen;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi r;
    mbedtls_mpi s;

    INLET_PARAM_CHECK_POINT_NULL(pstParams);
    INLET_PARAM_CHECK_POINT_NULL(pu8PubKeyX);
    INLET_PARAM_CHECK_POINT_NULL(pu8PubKeyY);
    INLET_PARAM_CHECK_POINT_NULL(pu8Message);
    INLET_PARAM_CHECK_POINT_NULL(pu8SigR);
    INLET_PARAM_CHECK_POINT_NULL(pu8SigS);

    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8p);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8a);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8b);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GX);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8GY);
    INLET_PARAM_CHECK_POINT_NULL(pstParams->pu8n);

    INLET_PARAM_CHECK_U32_ZERO(pstParams->u32keySize);

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
