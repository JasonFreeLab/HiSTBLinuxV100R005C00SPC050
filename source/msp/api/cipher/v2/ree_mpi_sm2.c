/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_sm2.c
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

/* max length of SM2 ID */
#define SM2_ID_MAX_LEN          0x1FFF

/* SM2 PC of uncompress */
#define SM2_PC_UNCOMPRESS       0x04

#define SM_CHECK(f) if( 0 != ( ret = f )) goto cleanup

static HI_S32 SM2_KDF(HI_U32 u32X[8], HI_U32 u32Y[8], HI_U8* pu8k, HI_U32 u32klen)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE hSm3Handle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U32 u32ct = 0;
    HI_U8 u8H[SM2_LEN_IN_BYTE];
    HI_U32 i;
    HI_U32 u32Block = 0;

    if (0 == u32klen)
    {
        return HI_SUCCESS;
    }

    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    cipher_memset_s(u8H, sizeof(u8H), 0, SM2_LEN_IN_BYTE);
    u32Block = (u32klen + SM2_LEN_IN_BYTE - 1) / SM2_LEN_IN_BYTE;
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;

    for(i=0; i<u32Block; i++)
    {
        u32ct = CPU_TO_BE32(i+1);

        /* H = SM3(X || Y || CT)*/
        SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
        SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)u32X, SM2_LEN_IN_BYTE));
        SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)u32Y, SM2_LEN_IN_BYTE));
        SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)&u32ct, sizeof(u32ct)));
        SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8H));
        if (i == (u32Block - 1))
        {
            cipher_memcpy_s(pu8k+i*32, SM2_LEN_IN_BYTE, u8H, u32klen - i * SM2_LEN_IN_BYTE);
        }
        else
        {
            cipher_memcpy_s(pu8k+i*32, SM2_LEN_IN_BYTE, u8H, sizeof(u8H));
        }
    }

    /*check k != 0*/
    for(i=0; i<u32klen; i++)
    {
        if (pu8k[i] != 0)
        {
            break;
        }
    }

    ret = (i<u32klen) ? HI_SUCCESS : HI_FAILURE;

 cleanup:

    return ret;
}

HI_S32 HI_MPI_CIPHER_Sm2Sign(HI_UNF_CIPHER_SM2_SIGN_S *pstSm2Sign,
                              HI_U8 *pu8Msg, HI_U32 u32MsgLen,
                              HI_U8 *pu8R, HI_U8 *pu8S)
{
    HI_S32 ret = HI_FAILURE;
    SM2_SIGN_DATA_S stSm2SignData;
    HI_HANDLE hSm3Handle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 u8Entla[2];
    HI_U8 u8ZA[SM2_LEN_IN_BYTE];
    HI_U8 u8e[SM2_LEN_IN_BYTE];

    INLET_PARAM_CHECK_POINT_NULL(pstSm2Sign);
    INLET_PARAM_CHECK_POINT_NULL(pstSm2Sign->pu8Id);
    INLET_PARAM_CHECK_POINT_NULL(pu8Msg);
    INLET_PARAM_CHECK_POINT_NULL(pu8R);
    INLET_PARAM_CHECK_POINT_NULL(pu8S);
    INLET_PARAM_CHECK_U32_MAX(pstSm2Sign->u16IdLen, SM2_ID_MAX_LEN);

    cipher_memset_s(&stSm2SignData, sizeof(stSm2SignData), 0, sizeof(SM2_SIGN_DATA_S));
    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    cipher_memset_s(u8ZA, sizeof(u8ZA), 0, SM2_LEN_IN_BYTE);
    cipher_memset_s(u8e, sizeof(u8e), 0, SM2_LEN_IN_BYTE);
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;

    u8Entla[0] = (HI_U8)((pstSm2Sign->u16IdLen * 8) >> 8);
    u8Entla[1] = (HI_U8)((pstSm2Sign->u16IdLen * 8));

    /*ZA=H256(ENTLA||IDA||a||b||xG||yG||xA||yA)*/
    /*SM2 and sm3 use two different lock, so have to use SM3 Instead of MPI*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, u8Entla, sizeof(u8Entla)));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pstSm2Sign->pu8Id, pstSm2Sign->u16IdLen));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32a, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32b, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32Gx, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32Gy, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)pstSm2Sign->u32Px, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)pstSm2Sign->u32Py, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8ZA));

//    HI_PRINT_HEX("ZA", u8ZA, SM2_LEN_IN_BYTE);

    /*e=H256(ZA||M)*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, u8ZA, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pu8Msg, u32MsgLen));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8e));

//    HI_PRINT_HEX("e", u8e, SM2_LEN_IN_BYTE);

    /*Copy params to SM2_SIGN_DATA_S*/
    cipher_memset_s(&stSm2SignData, sizeof(stSm2SignData), 0, sizeof(SM2_SIGN_DATA_S));
    cipher_memcpy_s(&stSm2SignData.u32e, sizeof(stSm2SignData.u32e), u8e, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2SignData.u32d, sizeof(stSm2SignData.u32d), pstSm2Sign->u32d, SM2_LEN_IN_BYTE);

    /***************************************
      1. generate a randnum k, k∈[1,n-1],
      2. (x1,y1)=[k]G,
      3. r=(e+x1)mod n, if r=0 or r+k=n, return step 1
      4. s=((1+dA)^-1 ·(k-r·dA))mod n
    ****************************************/
    ret = cipher_ioctl(g_CipherDevFd, CMD_SM2_SIGN, &stSm2SignData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Error, sm2 sign failed!\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }

    cipher_memcpy_s(pu8R, SM2_LEN_IN_BYTE, stSm2SignData.u32r, sizeof(stSm2SignData.u32r));
    cipher_memcpy_s(pu8S, SM2_LEN_IN_BYTE, stSm2SignData.u32s, sizeof(stSm2SignData.u32s));

 cleanup:

    return ret;
}

HI_S32 HI_MPI_CIPHER_Sm2Verify(HI_UNF_CIPHER_SM2_VERIFY_S *pstSm2Verify, HI_U8 *pu8Msg,
                         HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S)
{
    HI_S32 ret = HI_FAILURE;
    SM2_VERIFY_DATA_S stSm2VerifyData;
    HI_HANDLE hSm3Handle;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 u8Entla[2] = {0};
    HI_U8 u8ZA[SM2_LEN_IN_BYTE];
    HI_U8 u8e[SM2_LEN_IN_BYTE];

    INLET_PARAM_CHECK_POINT_NULL(pstSm2Verify);
    INLET_PARAM_CHECK_POINT_NULL(pstSm2Verify->pu8Id);
    INLET_PARAM_CHECK_POINT_NULL(pu8Msg);
    INLET_PARAM_CHECK_POINT_NULL(pu8R);
    INLET_PARAM_CHECK_POINT_NULL(pu8S);
    INLET_PARAM_CHECK_U32_MAX(pstSm2Verify->u16IdLen, SM2_ID_MAX_LEN);

    cipher_memset_s(&stSm2VerifyData, sizeof(stSm2VerifyData), 0, sizeof(SM2_VERIFY_DATA_S));
    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    cipher_memset_s(u8Entla, sizeof(u8Entla), 0, 2);
    cipher_memset_s(u8ZA, sizeof(u8ZA), 0, SM2_LEN_IN_BYTE);
    cipher_memset_s(u8e, sizeof(u8e), 0, SM2_LEN_IN_BYTE);
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;

    u8Entla[0] = (HI_U8)((pstSm2Verify->u16IdLen * 8) >> 8);
    u8Entla[1] = (HI_U8)((pstSm2Verify->u16IdLen * 8));

    /*ZA=H256(ENTLA||IDA||a||b||xG||yG||xA||yA)*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, u8Entla, 2));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pstSm2Verify->pu8Id, pstSm2Verify->u16IdLen));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32a, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32b, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32Gx, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)s_u32Gy, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)pstSm2Verify->u32Px, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)pstSm2Verify->u32Py, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8ZA));

//    HI_PRINT_HEX("ZA", u8ZA, SM2_LEN_IN_BYTE);

    /*e=H256(ZA||M)*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, u8ZA, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pu8Msg, u32MsgLen));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8e));

//  HI_PRINT_HEX("e", u8e, SM2_LEN_IN_BYTE);

    /*Copy params to SM2_VERIFY_DATA_S*/
    cipher_memcpy_s(&stSm2VerifyData.u32e, sizeof(stSm2VerifyData.u32e), u8e, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2VerifyData.u32Px, sizeof(stSm2VerifyData.u32Px),pstSm2Verify->u32Px, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2VerifyData.u32Py, sizeof(stSm2VerifyData.u32Py),pstSm2Verify->u32Py, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2VerifyData.u32r, sizeof(stSm2VerifyData.u32r),pu8R, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2VerifyData.u32s,sizeof(stSm2VerifyData.u32s), pu8S, SM2_LEN_IN_BYTE);

    /***************************************
      1. t=(r+s)mod n, if t==0, return fail
      2. (x1,y1)=[s]G+tP,
      3. r=(e+x1)mod n, if r==R, return pass
    ****************************************/
    ret = cipher_ioctl(g_CipherDevFd, CMD_SM2_VERIFY, &stSm2VerifyData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Error, sm2 verify failed!\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }

 cleanup:

    return ret;
}

HI_S32 HI_MPI_CIPHER_Sm2Encrypt(HI_UNF_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg,
                          HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen)
{
    HI_S32 ret = HI_FAILURE;
    SM2_ENC_DATA_S stSm2EncData;
    HI_HANDLE hSm3Handle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U32 u32Index = 0;
    HI_U32 i;

    INLET_PARAM_CHECK_POINT_NULL(pstSm2Enc);
    INLET_PARAM_CHECK_POINT_NULL(pu8Msg);
    INLET_PARAM_CHECK_POINT_NULL(pu8C);
    INLET_PARAM_CHECK_POINT_NULL(pu32Clen);

    cipher_memset_s(&stSm2EncData, sizeof(stSm2EncData), 0, sizeof(SM2_ENC_DATA_S));
    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;

    /*Copy params to SM2_ENC_DATA_S*/
    cipher_memcpy_s(&stSm2EncData.u32Px, sizeof(stSm2EncData.u32Px), pstSm2Enc->u32Px, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2EncData.u32Py, sizeof(stSm2EncData.u32Py), pstSm2Enc->u32Py, SM2_LEN_IN_BYTE);

    /*C1=k*G*/
    while(1)
    {
        /* C1(x, y) = k * G(x, y), XY = k * P(x, y)*/
        ret = cipher_ioctl(g_CipherDevFd, CMD_SM2_ENCRYPT, &stSm2EncData);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Error, sm2 encrypt failed!\n");
            ret =  HI_FAILURE;
            goto cleanup;
        }
//      HI_PRINT_HEX("C1x", (HI_U8*)stSm2EncData.u32C1x, SM2_LEN_IN_BYTE);
//      HI_PRINT_HEX("C1y", (HI_U8*)stSm2EncData.u32C1y, SM2_LEN_IN_BYTE);
//      HI_PRINT_HEX("X2", (HI_U8*)stSm2EncData.u32X2, SM2_LEN_IN_BYTE);
//      HI_PRINT_HEX("Y2", (HI_U8*)stSm2EncData.u32Y2, SM2_LEN_IN_BYTE);

        /*在此C1选用未压缩的表示形式，点转换成字节串的形式为PC||x1||y1，其中PC为单一字节，且PC=4*/
        u32Index = 0;
        pu8C[u32Index++] = SM2_PC_UNCOMPRESS;
        cipher_memcpy_s(&pu8C[u32Index], SM2_LEN_IN_BYTE, stSm2EncData.u32C1x, SM2_LEN_IN_BYTE);
        u32Index+=SM2_LEN_IN_BYTE;
        cipher_memcpy_s(&pu8C[u32Index], SM2_LEN_IN_BYTE, stSm2EncData.u32C1y, SM2_LEN_IN_BYTE);
        u32Index+=SM2_LEN_IN_BYTE;
//      HI_PRINT_HEX("C1", &pu8C[0], SM2_LEN_IN_BYTE*2+1);

        /*gen mask for msg encrypt*/
        ret = SM2_KDF(stSm2EncData.u32X2, stSm2EncData.u32Y2, &pu8C[u32Index], u32MsgLen);
        if (HI_SUCCESS == ret)
        {
            break;
        }
    }

    /*C2=M ^ k*/
    for(i=0; i<u32MsgLen; i++)
    {
        pu8C[u32Index++] ^= pu8Msg[i];
    }
//    HI_PRINT_HEX("C2", &pu8C[SM2_LEN_IN_BYTE*2+1], u32MsgLen);

    /*C3 =Hash(x2||M||y2)*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)stSm2EncData.u32X2, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pu8Msg, u32MsgLen));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)stSm2EncData.u32Y2, SM2_LEN_IN_BYTE));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, &pu8C[u32Index]));
    u32Index+=SM2_LEN_IN_BYTE;
//    HI_PRINT_HEX("C3", &pu8C[SM2_LEN_IN_BYTE*2+1+u32MsgLen], SM2_LEN_IN_BYTE);

    *pu32Clen = u32Index;

 cleanup:

    return ret;
}

HI_S32 HI_MPI_CIPHER_Sm2Decrypt(HI_UNF_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C,
                          HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 u8H[SM2_LEN_IN_BYTE];
    SM2_DEC_DATA_S stSm2DecData;
    HI_HANDLE hSm3Handle = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U32 u32Index = 0;
    HI_U32 u32Mlen = 0;
    HI_U32 i;

    INLET_PARAM_CHECK_POINT_NULL(pstSm2Dec);
    INLET_PARAM_CHECK_POINT_NULL(pu8Msg);
    INLET_PARAM_CHECK_POINT_NULL(pu8C);
    INLET_PARAM_CHECK_POINT_NULL(pu32MsgLen);

    cipher_memset_s(u8H, sizeof(u8H), 0, SM2_LEN_IN_BYTE);
    cipher_memset_s(&stSm2DecData, sizeof(stSm2DecData), 0, sizeof(SM2_DEC_DATA_S));
    cipher_memset_s(&stHashAttr, sizeof(stHashAttr), 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SM3;
    u32Index = 0;
    u32Mlen = u32Clen - (SM2_LEN_IN_BYTE*2+1) - SM2_LEN_IN_BYTE; //C2 = C - C1 -C3

    /*Check C1*/
    if (SM2_PC_UNCOMPRESS != pu8C[u32Index++])
    {
        HI_ERR_CIPHER("Error, sm2 Decrypt failed, C1[0] != 0x04!\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }
    cipher_memset_s(&stSm2DecData, sizeof(stSm2DecData), 0, sizeof(SM2_DEC_DATA_S));
    cipher_memcpy_s(&stSm2DecData.u32d, sizeof(stSm2DecData.u32d), pstSm2Dec->u32d, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&stSm2DecData.u32C1x, sizeof(stSm2DecData.u32C1x), &pu8C[u32Index], SM2_LEN_IN_BYTE);
    u32Index+=SM2_LEN_IN_BYTE;
    cipher_memcpy_s(&stSm2DecData.u32C1y, sizeof(stSm2DecData.u32C1y), &pu8C[u32Index], SM2_LEN_IN_BYTE);
    u32Index+=SM2_LEN_IN_BYTE;

    /*Compute M(x, y) = C1(x, y) * d*/
    ret = cipher_ioctl(g_CipherDevFd, CMD_SM2_DECRYPT, &stSm2DecData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Error, sm2 decrypt failed!\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }
//    HI_PRINT_HEX("X2", (HI_U8*)stSm2DecData.u32X2, SM2_LEN_IN_BYTE);
//    HI_PRINT_HEX("Y2", (HI_U8*)stSm2DecData.u32Y2, SM2_LEN_IN_BYTE);

    /*Compute mask for msg*/
    ret = SM2_KDF(stSm2DecData.u32X2, stSm2DecData.u32Y2, pu8Msg, u32Mlen);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Err, SM2 decrypt failed, KDF key is all zero\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }

    /*Get clear msg from C2*/
    for(i=0; i<u32Mlen; i++)
    {
        pu8Msg[i] ^= pu8C[u32Index++];
    }

    /*Check C3*/
    SM_CHECK(HI_UNF_CIPHER_HashInit(&stHashAttr, &hSm3Handle));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)stSm2DecData.u32X2, 32));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, pu8Msg, u32Mlen));
    SM_CHECK(HI_UNF_CIPHER_HashUpdate(hSm3Handle, (HI_U8*)stSm2DecData.u32Y2, 32));
    SM_CHECK(HI_UNF_CIPHER_HashFinal(hSm3Handle, u8H));

//    HI_PRINT_HEX("H", u8H, SM2_LEN_IN_BYTE);

    if(memcmp(&pu8C[u32Index], u8H, SM2_LEN_IN_BYTE)!=0)
    {
        HI_ERR_CIPHER("Err, SM2 decrypt failed, invalid C3\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }
    u32Index+=32;

    *pu32MsgLen = u32Mlen;

 cleanup:

    return ret;
}

HI_S32 HI_MPI_CIPHER_Sm2GenKey(HI_UNF_CIPHER_SM2_KEY_S *pstSm2Key)
{
    HI_S32 ret = HI_FAILURE;
    SM2_KEY_DATA_S Sm2Key;

    INLET_PARAM_CHECK_POINT_NULL(pstSm2Key);

    cipher_memset_s(&Sm2Key, sizeof(Sm2Key), 0, sizeof(SM2_KEY_DATA_S));

    /* d is randnum, P(x,y) =d * G(x,y) */
    ret = cipher_ioctl(g_CipherDevFd, CMD_SM2_KEY, &Sm2Key);

    cipher_memcpy_s(&pstSm2Key->u32d, sizeof(pstSm2Key->u32d), Sm2Key.u32d, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&pstSm2Key->u32Px, sizeof(pstSm2Key->u32Px), Sm2Key.u32Px, SM2_LEN_IN_BYTE);
    cipher_memcpy_s(&pstSm2Key->u32Py, sizeof(pstSm2Key->u32Py), Sm2Key.u32Py, SM2_LEN_IN_BYTE);

    return ret;
}

