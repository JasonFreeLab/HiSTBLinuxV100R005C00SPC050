/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : vmx_verify.c
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2016-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2016-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#include <stdio.h>
#include <string.h>
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#include "common.h"
#else
#include <stdio.h>
#include <string.h>
#endif

#include "hi_unf_cipher.h"

#include "loader_debug.h"
#include "loader_osal.h"
#include "vmx_verify.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define BLSH_LEN_RSA_PUBLIC_KEY_E    (256)
#define BLSH_LEN_RSA_PUBLIC_KEY_N    (256)

static HI_U8 s_au8RSAKey_N[BLSH_LEN_RSA_PUBLIC_KEY_N] =
{
    0xd2, 0xce, 0x43, 0x15, 0xcc, 0xa9, 0xba, 0x8a, 0x43, 0x15, 0xe0, 0x37, 0x7c, 0x0d, 0x09, 0x07,
    0xa8, 0x93, 0xa6, 0xd4, 0x20, 0x6e, 0x1a, 0x1a, 0x61, 0x5a, 0x08, 0xc2, 0x57, 0x35, 0xdb, 0xd2,
    0xca, 0x9a, 0x41, 0x4d, 0x5c, 0xe6, 0x0d, 0x65, 0xc0, 0x43, 0xa5, 0xed, 0x7e, 0x91, 0x96, 0xf5,
    0x41, 0x45, 0x0e, 0x63, 0x39, 0xec, 0x73, 0x59, 0xa8, 0xd3, 0x0e, 0x30, 0x95, 0xa4, 0xb4, 0x1c,
    0xf4, 0x73, 0x89, 0x96, 0x78, 0x77, 0x7b, 0x8f, 0x7f, 0xe3, 0x4a, 0x6f, 0x8f, 0x3e, 0xdb, 0x8d,
    0xc0, 0x2d, 0x4a, 0x55, 0x98, 0x37, 0xbe, 0xdd, 0x77, 0x34, 0xea, 0x5c, 0xe7, 0xbc, 0x5c, 0xac,
    0xe9, 0xf4, 0x45, 0x95, 0xf4, 0x25, 0xad, 0x6f, 0xd7, 0xaa, 0x10, 0xe8, 0xd7, 0xbb, 0x90, 0xd9,
    0x68, 0x5c, 0x64, 0x42, 0x6f, 0x8d, 0xca, 0x7d, 0x22, 0xdf, 0x0e, 0xe9, 0x84, 0xce, 0xbe, 0xc3,
    0xb1, 0xa0, 0x90, 0xd6, 0x44, 0x72, 0x52, 0xca, 0xc3, 0x0f, 0xef, 0xd5, 0xe4, 0x38, 0x2c, 0xb2,
    0x55, 0xcf, 0x87, 0x53, 0x9d, 0x32, 0x73, 0x49, 0x38, 0x3c, 0x71, 0x21, 0x66, 0x58, 0xea, 0x7a,
    0x41, 0x41, 0x8f, 0x4c, 0x3f, 0x8f, 0x0e, 0x88, 0x57, 0xfa, 0xf6, 0x18, 0x42, 0x0e, 0xd1, 0x92,
    0x93, 0xa6, 0x7c, 0xb3, 0x5e, 0x0d, 0x2b, 0x27, 0x2b, 0x78, 0x69, 0xc4, 0x81, 0x67, 0x1a, 0xf0,
    0x8c, 0xec, 0x58, 0xd9, 0x07, 0x8e, 0x2c, 0x90, 0xb5, 0x40, 0xb5, 0x6d, 0xf0, 0x2d, 0xbb, 0x8f,
    0xc8, 0x15, 0x5a, 0xcd, 0xd6, 0x93, 0xac, 0xf3, 0x8a, 0x8d, 0xb4, 0x0f, 0x75, 0x46, 0x7b, 0x30,
    0xb9, 0x7c, 0x0f, 0x59, 0xce, 0x03, 0x6e, 0xa0, 0x9e, 0xf9, 0x67, 0xb9, 0xf6, 0x72, 0xfe, 0xfe,
    0x8e, 0x4c, 0x5c, 0x04, 0x89, 0x0b, 0xb5, 0x7c, 0xdf, 0x27, 0x99, 0xbb, 0x23, 0xec, 0xde, 0xe1
};

static HI_U8 s_au8RSAKey_E[BLSH_LEN_RSA_PUBLIC_KEY_E] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
};

static BLSH_RSA_PUBKEY_S s_stRSAKeyDefault =
{
    s_au8RSAKey_N,
    s_au8RSAKey_E,
    BLSH_LEN_RSA_PUBLIC_KEY_N,
    BLSH_LEN_RSA_PUBLIC_KEY_E
};

static BLSH_RSA_PUBKEY_S* s_pstRSAKeyExtern = HI_NULL_PTR;

HI_S32 BLSH_ConfigExternKey(BLSH_RSA_PUBKEY_S* pstPubKey)
{
    s_pstRSAKeyExtern = pstPubKey;

    return HI_SUCCESS;
}

HI_S32 BLSH_ClearExternKey(HI_VOID)
{
    s_pstRSAKeyExtern = HI_NULL_PTR;

    return HI_SUCCESS;
}

HI_S32 BLSH_VerifySignature(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8Signature, HI_U32 u32SignatureSize)
{
    HI_UNF_CIPHER_RSA_VERIFY_S stRsaVerify;
    BLSH_RSA_PUBKEY_S* pstPubKey = HI_NULL_PTR;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Data);
    LOADER_CHECK_PARAM(0 == u32Size);

    LOADER_MemSet(&stRsaVerify, 0x00, sizeof(stRsaVerify));

    s32Ret = HI_UNF_CIPHER_Init();
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_UNF_CIPHER_Init, s32Ret);
        return LOADER_ERR_EXTERNAL;
    }

    pstPubKey = (HI_NULL_PTR == s_pstRSAKeyExtern) ? &s_stRSAKeyDefault : s_pstRSAKeyExtern;

    stRsaVerify.stPubKey.pu8E    = pstPubKey->pu8E;
    stRsaVerify.stPubKey.pu8N    = pstPubKey->pu8N;
    stRsaVerify.stPubKey.u16ELen = pstPubKey->u16ELen;
    stRsaVerify.stPubKey.u16NLen = pstPubKey->u16NLen;
    stRsaVerify.enScheme         = HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256;

    LOADER_PrintBuffer("Data:", pu8Data, 256);
    LOADER_PrintBuffer("Data Signature:", pu8Signature, BLSH_LEN_IMG_HEADER_SIGN);

    s32Ret = HI_UNF_CIPHER_RsaVerify(&stRsaVerify, pu8Data, u32Size, HI_NULL_PTR, pu8Signature, u32SignatureSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_UNF_CIPHER_RsaVerify, s32Ret);

        HI_UNF_CIPHER_DeInit();
        return LOADER_ERR_EXTERNAL;
    }

    HI_UNF_CIPHER_DeInit();

    LOADER_FuncExit();
    return HI_SUCCESS;
}


HI_S32 BLSH_VerifyImageHeader(HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize)
{
    BLSH_IMAGE_HEAD_S* pstImageHeader = HI_NULL_PTR;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);
    LOADER_CHECK_PARAM(sizeof(BLSH_IMAGE_HEAD_S) > u32DataBufferSize);

    LOADER_PrintBuffer("Header:", pu8DataBuffer, sizeof(BLSH_IMAGE_HEAD_S));
    LOADER_PrintBuffer("Header Signature:", pu8DataBuffer + BLSH_POS_IMG_HEADER_SIGN, BLSH_LEN_IMG_HEADER_SIGN);

    pstImageHeader = (BLSH_IMAGE_HEAD_S*)pu8DataBuffer;

    if ((BLSH_LEN_IMG_HEADER >= pstImageHeader->u32TotalLen)
        || (BLSH_LEN_IMG_HEADER != pstImageHeader->u32CodeOffset)
        || (BLSH_LEN_IMG_HEADER_SIGN != pstImageHeader->u32SignatureLen)
        || (pstImageHeader->u32SignedImageLen + pstImageHeader->u32CodeOffset != pstImageHeader->u32SignatureOffset)
        || (pstImageHeader->u32SignatureOffset + pstImageHeader->u32SignatureLen != pstImageHeader->u32TotalLen))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    s32Ret = BLSH_VerifySignature(pu8DataBuffer,
                                  BLSH_POS_IMG_HEADER_SIGN,
                                  pu8DataBuffer + BLSH_POS_IMG_HEADER_SIGN,
                                  BLSH_LEN_IMG_HEADER_SIGN);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifySignature, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 BLSH_VerifyImageData(BLSH_IMAGE_HEAD_S* pstImageHeader, HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize)
{
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstImageHeader);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);

    s32Ret = BLSH_VerifySignature(pu8DataBuffer + pstImageHeader->u32CodeOffset,
                                  pstImageHeader->u32SignedImageLen,
                                  pu8DataBuffer + pstImageHeader->u32SignatureOffset,
                                  pstImageHeader->u32SignatureLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifySignature, s32Ret);
        return s32Ret;
    }

    s32Ret = LOADER_MemCmp(pu8DataBuffer + BLSH_POS_IMG_HEADER_SIGN,
                           pu8DataBuffer + pstImageHeader->u32SignatureOffset - BLSH_LEN_IMG_HEADER_SIGN,
                           BLSH_LEN_IMG_HEADER_SIGN);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 BLSH_VerifyWholeImage(HI_U8* pu8Data, HI_U32 u32Size)
{
    BLSH_IMAGE_HEAD_S* pstImageHeader = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Data);
    LOADER_CHECK_PARAM(sizeof(BLSH_IMAGE_HEAD_S) >= u32Size);

    s32Ret = BLSH_VerifyImageHeader(pu8Data, u32Size);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageHeader, s32Ret);
        return s32Ret;
    }

    pstImageHeader = (BLSH_IMAGE_HEAD_S*)pu8Data;
    s32Ret = BLSH_VerifyImageData(pstImageHeader, pu8Data, pstImageHeader->u32TotalLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageData, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

