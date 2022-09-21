/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : tee_mpi_cipher.h
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef __HI_MPI_CIPHER_H__
#define __HI_MPI_CIPHER_H__

#include "cipher_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*** CIPHER API ***/
HI_S32 HI_MPI_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_TEE_CIPHER_ATTS_S *pstCipherAttr);
HI_S32 HI_MPI_CIPHER_DestroyHandle(HI_HANDLE hCipher);
HI_S32 HI_MPI_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_TEE_CIPHER_CTRL_S* pstCtrl);
HI_S32 HI_MPI_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_TEE_CIPHER_CTRL_EX_S* pstExCtrl);
HI_S32 HI_MPI_CIPHER_SetUsageRule(HI_U32 hCipher, HI_TEE_CIPHER_UR_S *pstCipherUR);
HI_S32 HI_MPI_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 HI_MPI_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 HI_MPI_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_EncryptMultiAsyn(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_WaitDone(HI_HANDLE hCipher, HI_U32 u32TimeOut);
HI_S32 HI_MPI_CIPHER_DecryptMultiAsyn(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_TEE_CIPHER_CTRL_S* pstCtrl);
HI_S32 HI_MPI_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen);
HI_S32 HI_MPI_CIPHER_CENCDecrypt(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_U8 *pu8IV,
                            HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr, HI_U32 u32ByteLength,
                            HI_U32 u32FirstEncryptOffset,
                            HI_TEE_CIPHER_SUBSAMPLE_S *pstSubSample, HI_U32 u32SubsampleNum);
HI_S32 HI_MPI_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize);
HI_S32 HI_MPI_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                                   HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                                   HI_U32 u32KeySize);
 
/*** HASH API ***/
HI_S32 HI_MPI_CIPHER_HashInit(HI_TEE_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);
HI_S32 HI_MPI_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);
HI_S32 HI_MPI_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);

/*** RNG API ***/
HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs);

/*** RSA API ***/
HI_S32 HI_MPI_CIPHER_RsaPublicEncrypt(HI_TEE_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen);
HI_S32 HI_MPI_CIPHER_RsaPrivateDecrypt(HI_TEE_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen);
HI_S32 HI_MPI_CIPHER_RsaSign(HI_TEE_CIPHER_RSA_SIGN_S *pstRsaSign,
                        HI_U8 *pu8InData, HI_U32 u32InDataLen,
                        HI_U8 *pu8HashData,
                        HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen);
HI_S32 HI_MPI_CIPHER_RsaVerify(HI_TEE_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                            HI_U8 *pu8InData, HI_U32 u32InDataLen,
                            HI_U8 *pu8HashData,
                            HI_U8 *pu8InSign, HI_U32 u32InSignLen);
HI_S32 HI_MPI_CIPHER_RsaPrivateEncrypt(HI_TEE_CIPHER_RSA_PRI_ENC_S *pstRsEnc,
                                    HI_U8 *pu8Input, HI_U32 u32InLen,
                                    HI_U8 *pu8Output, HI_U32 *pu32OutLen);
HI_S32 HI_MPI_CIPHER_RsaPublicDecrypt(HI_TEE_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                                    HI_U8 *pu8Input, HI_U32 u32InLen,
                                    HI_U8 *pu8Output, HI_U32 *pu32OutLen);

/*** SM2 API ***/
HI_S32 HI_MPI_CIPHER_Sm2Sign(HI_TEE_CIPHER_SM2_SIGN_S *pstSm2Sign, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S);
HI_S32 HI_MPI_CIPHER_Sm2Verify(HI_TEE_CIPHER_SM2_VERIFY_S *pstSm2Verify, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S);
HI_S32 HI_MPI_CIPHER_Sm2Encrypt(HI_TEE_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen);
HI_S32 HI_MPI_CIPHER_Sm2Decrypt(HI_TEE_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C, HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen);
HI_S32 HI_MPI_CIPHER_Sm2Key(HI_TEE_CIPHER_SM2_KEY_S *pstSm2Key);

/*** OTHER API ***/
HI_S32 HI_MPI_CIPHER_PBKDF2(HI_TEE_CIPHER_PBKDF2_S *pstInfo, HI_U8 *pu8Output);
HI_S32 HI_MPI_CIPHER_Test(HI_U32 u32Cmd, HI_VOID *pu8Param, HI_U32 u32ParamSize);

#ifdef __cplusplus
#if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_MPI_CIPHER_H__ */

