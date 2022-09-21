/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : unf_cipher.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_osal.h"

static cipher_mutex  g_CipherMutex = PTHREAD_MUTEX_INITIALIZER;
static cipher_mutex  g_HashMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_CIPHER_LOCK()                (void)cipher_mutex_lock(&g_CipherMutex)
#define HI_CIPHER_UNLOCK()              (void)cipher_mutex_unlock(&g_CipherMutex)
#define HI_HASH_LOCK()                  (void)cipher_mutex_lock(&g_HashMutex)
#define HI_HASH_UNLOCK()                (void)cipher_mutex_unlock(&g_HashMutex)
HI_S32 g_CipherDevFd = -1;
static HI_S32 g_CipherInitCounter = -1;

#define CHECK_CIPHER_OPEN()\
do{\
    if (g_CipherInitCounter < 0)\
    {\
        HI_ERR_CIPHER("CIPHER is not open.\n");\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
}while(0)

HI_S32 HI_UNF_CIPHER_Init(HI_VOID)
{
    HI_S32 ret;

    HI_CIPHER_LOCK();

    if (g_CipherInitCounter > 0)
    {
        g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    g_CipherDevFd = cipher_open("/dev/"UMAP_DEVNAME_CIPHER, O_RDWR, 0);
    if (g_CipherDevFd < 0)
    {
        HI_ERR_CIPHER("Open CIPHER err.\n");
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    ret = Cipher_HashMmzInit();
    if (ret != HI_SUCCESS)
    {
        cipher_close(g_CipherDevFd);
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    g_CipherInitCounter = 1;
    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_CIPHER_DeInit(HI_VOID)
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

    Cipher_HashMmzDeInit();
    cipher_close(g_CipherDevFd);

    g_CipherInitCounter = -1;

    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_CreateHandle(phCipher, pstCipherAttr);
}

HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DestroyHandle(hCipher);
}

HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_ConfigHandle(hCipher, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_ConfigHandleEx(hCipher, pstExCtrl);
}

HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Encrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Decrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EncryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DecryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 HI_UNF_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetTag(hCipher, pu8Tag, pu32TagLen);
}

HI_S32 HI_UNF_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_GetRandomNumber(pu32RandomNumber, 0);
}

HI_S32 HI_UNF_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                                        HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_CalcMAC(hCipherHandle, pInputData, u32InputDataLen, pOutputMAC, bIsLastBlock);
}

HI_S32 HI_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret =  HI_MPI_CIPHER_HashInit(pstHashAttr, pHashHandle);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret = HI_MPI_CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret;

    CHECK_CIPHER_OPEN();

    HI_HASH_LOCK();

    ret = HI_MPI_CIPHER_HashFinal(hHashHandle, pu8OutputHash);

    HI_HASH_UNLOCK();

    return ret;
}

HI_S32 HI_UNF_CIPHER_RsaPublicEncrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPublicEncrypt(pstRsaEnc, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaPrivateDecrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPrivateDecrypt(pstRsaDec, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaSign(HI_UNF_CIPHER_RSA_SIGN_S *pstRsaSign,
                             HI_U8 *pu8InData, HI_U32 u32InDataLen,
                             HI_U8 *pu8HashData,
                             HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaSign(pstRsaSign, pu8InData, u32InDataLen, pu8HashData,
        pu8OutSign, pu32OutSignLen);
}

HI_S32 HI_UNF_CIPHER_RsaVerify(HI_UNF_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaVerify(pstRsaVerify, pu8InData, u32InDataLen, pu8HashData,
        pu8InSign, u32InSignLen);
}

HI_S32 HI_UNF_CIPHER_RsaPrivateEncrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaEnc,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPrivateEncrypt(pstRsaEnc, pu8Input, u32InLen, pu8Output, pu32OutLen);
}

HI_S32 HI_UNF_CIPHER_RsaPublicDecrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                               HI_U8 *pu8Input, HI_U32 u32InLen,
                               HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaPublicDecrypt(pstRsaDec, pu8Input, u32InLen, pu8Output,pu32OutLen);
}


HI_S32 HI_UNF_CIPHER_RsaGenKey(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_UNF_CIPHER_RSA_PRI_KEY_S *pstRsaPriKey)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaGenKey(u32NumBits, u32Exponent, pstRsaPriKey);
}

HI_S32 HI_UNF_CIPHER_RsaComputeCrtParams(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_U8 *pu8P,
                               HI_U8 *pu8Q, HI_U8 *pu8DP, HI_U8 *pu8DQ, HI_U8 *pu8QP)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_RsaComputeCrtParams(u32NumBits, u32Exponent, pu8P, pu8Q, pu8DP, pu8DQ, pu8QP);
}

HI_S32 HI_UNF_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DhComputeKey(pu8P, pu8PrivKey, pu8OtherPubKey, pu8SharedSecret, u32KeySize);
}

HI_S32 HI_UNF_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                                   HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                                   HI_U32 u32KeySize)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_DhGenKey(pu8G, pu8P, pu8InputPrivKey, pu8OutputPrivKey, pu8PubKey, u32KeySize);
}

HI_S32 HI_UNF_CIPHER_EcdhComputeKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                                    HI_U8 *pu8OtherPubKeyX, HI_U8 *pu8OtherPubKeyY,
                                    HI_U8 *pu8SharedSecret)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EcdhComputeKey(pstParams, pu8PrivKey, pu8OtherPubKeyX, pu8OtherPubKeyY, pu8SharedSecret);
}

HI_S32 HI_UNF_CIPHER_EccGenKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8InputPrivKey,
                                     HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EccGenKey(pstParams, pu8InputPrivKey, pu8OutputPrivKey, pu8PubKeyX, pu8PubKeyY);
}

HI_S32 HI_UNF_CIPHER_EcdsaSign(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                               HI_UNF_CIPHER_HASH_TYPE_E enShaType,
                               HI_U8 *pu8Message, HI_U32 u32MessageSize,
                               HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EcdsaSign(pstParams, pu8PrivKey, enShaType, pu8Message, u32MessageSize, pu8SigR, pu8SigS);
}

HI_S32 HI_UNF_CIPHER_EcdsaVerify(HI_UNF_CIPHER_ECC_PARAM_S *pstParams,
                                 HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY,
                                 HI_UNF_CIPHER_HASH_TYPE_E enShaType,
                                 HI_U8 *pu8Message, HI_U32 u32MessageSize,
                                 HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_EcdsaVerify(pstParams, pu8PubKeyX, pu8PubKeyY, enShaType, pu8Message, u32MessageSize, pu8SigR, pu8SigS);
}

HI_S32 HI_UNF_CIPHER_CENCDecrypt(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_U8 *pu8IV,
                            HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr, HI_U32 u32ByteLength,
                            HI_U32 u32FirstEncryptOffset,
                           HI_UNF_CIPHER_SUBSAMPLE_S *pstSubSample, HI_U32 u32SubsampleNum)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_CENCDecrypt(hCipher, pu8Key, pu8IV,
                            u32NonSecInPhyAddr, u32SecOutPhyAddr, u32ByteLength,
                            u32FirstEncryptOffset,pstSubSample, u32SubsampleNum);
}

HI_S32 HI_UNF_CIPHER_Sm2Sign(HI_UNF_CIPHER_SM2_SIGN_S *pstSm2Sign, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Sm2Sign(pstSm2Sign, pu8Msg, u32MsgLen, pu8R, pu8S);
}

HI_S32 HI_UNF_CIPHER_Sm2Verify(HI_UNF_CIPHER_SM2_VERIFY_S *pstSm2Verify, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Sm2Verify(pstSm2Verify, pu8Msg, u32MsgLen, pu8R, pu8S);
}

HI_S32 HI_UNF_CIPHER_Sm2Encrypt(HI_UNF_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Sm2Encrypt(pstSm2Enc, pu8Msg, u32MsgLen, pu8C, pu32Clen);
}

HI_S32 HI_UNF_CIPHER_Sm2Decrypt(HI_UNF_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C, HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Sm2Decrypt(pstSm2Dec, pu8C, u32Clen, pu8Msg, pu32MsgLen);
}

HI_S32 HI_UNF_CIPHER_Sm2GenKey(HI_UNF_CIPHER_SM2_KEY_S *pstSm2Key)
{
    CHECK_CIPHER_OPEN();

    return HI_MPI_CIPHER_Sm2GenKey(pstSm2Key);
}


