/******************************************************************************

  Copyright (C), 2010-2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_mpi_cipher.h
  Version       : Initial Draft
  Author        :
  Created       :
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef __HI_MPI_CIPHER_H__
#define __HI_MPI_CIPHER_H__

#include "hi_unf_cipher.h"
#include "hi_unf_hdcp.h"
#include "drv_cipher_ioctl.h"
#include "hi_common.h"
#include "hi_drv_struct.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

HI_S32 HI_MPI_CIPHER_Init(HI_VOID);
HI_S32 HI_MPI_CIPHER_DeInit(HI_VOID);
HI_S32 HI_MPI_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr);
HI_S32 HI_MPI_CIPHER_DestroyHandle(HI_HANDLE hCipher);
HI_S32 HI_MPI_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);
HI_S32 HI_MPI_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl);
HI_S32 HI_MPI_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 HI_MPI_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 HI_MPI_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 HI_MPI_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl);
HI_S32 HI_MPI_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen, HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock);
HI_S32 HI_MPI_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);
HI_S32 HI_MPI_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);
HI_S32 HI_MPI_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);
HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen);
HI_S32 HI_MPI_CIPHER_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pstHdcpKey, HI_BOOL bIsUseOTPRootKey, HI_U8 u8OutEncryptKey[332]);
HI_S32 HI_MPI_CIPHER_LoadHDCPKey(HI_U8 *pu8EncryptedHDCPKey, HI_U32 u32Len);
HI_S32 HI_MPI_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen);
HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs);
HI_S32 HI_MPI_CIPHER_RsaPublicEncrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen);

HI_S32 HI_MPI_CIPHER_RsaPrivateDecrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen);

HI_S32 HI_MPI_CIPHER_RsaSign(HI_UNF_CIPHER_RSA_SIGN_S *pstRsaSign,
                             HI_U8 *pu8InData, HI_U32 u32InDataLen,
                             HI_U8 *pu8HashData,
                             HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen);

HI_S32 HI_MPI_CIPHER_RsaVerify(HI_UNF_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen);

HI_S32 HI_MPI_CIPHER_RsaPrivateEncrypt(HI_UNF_CIPHER_RSA_PRI_ENC_S *pstRsEnc,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen);

HI_S32 HI_MPI_CIPHER_RsaPublicDecrypt(HI_UNF_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                               HI_U8 *pu8Input, HI_U32 u32InLen,
                               HI_U8 *pu8Output, HI_U32 *pu32OutLen);

HI_S32 HI_MPI_CIPHER_Sm2Sign(HI_UNF_CIPHER_SM2_SIGN_S *pstSm2Sign, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S);
HI_S32 HI_MPI_CIPHER_Sm2Verify(HI_UNF_CIPHER_SM2_VERIFY_S *pstSm2Verify, HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8R, HI_U8 *pu8S);
HI_S32 HI_MPI_CIPHER_Sm2Encrypt(HI_UNF_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg, HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen);
HI_S32 HI_MPI_CIPHER_Sm2Decrypt(HI_UNF_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C, HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen);
HI_S32 HI_MPI_CIPHER_Sm2GenKey(HI_UNF_CIPHER_SM2_KEY_S *pstSm2Key);

HI_S32 HI_MPI_CIPHER_RsaGenKey(HI_U32 u32NumBits, HI_U32 u32Exponent,
                               HI_UNF_CIPHER_RSA_PRI_KEY_S *pstRsaPriKey);

HI_S32 HI_MPI_CIPHER_RsaComputeCrtParams(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_U8 *pu8P,
                               HI_U8 *pu8Q, HI_U8 *pu8DP, HI_U8 *pu8DQ, HI_U8 *pu8QP);


HI_S32 HI_MPI_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize);

HI_S32 HI_MPI_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                                   HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                                   HI_U32 u32KeySize);

HI_S32 HI_MPI_CIPHER_EcdhComputeKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                                    HI_U8 *pu8OtherPubKeyX, HI_U8 *pu8OtherPubKeyY,
                                    HI_U8 *pu8SharedSecret);

HI_S32 HI_MPI_CIPHER_EccGenKey(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8InputPrivKey,
                                     HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY);

HI_S32 HI_MPI_CIPHER_EcdsaSign(HI_UNF_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                               HI_UNF_CIPHER_HASH_TYPE_E enShaType,
                               HI_U8 *pu8Message, HI_U32 u32MessageSize,
                               HI_U8 *pu8SigR, HI_U8 *pu8SigS);

HI_S32 HI_MPI_CIPHER_EcdsaVerify(HI_UNF_CIPHER_ECC_PARAM_S *pstParams,
                                 HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY,
                                 HI_UNF_CIPHER_HASH_TYPE_E enShaType,
                                 HI_U8 *pu8Message, HI_U32 u32MessageSize,
                                 HI_U8 *pu8SigR, HI_U8 *pu8SigS);

HI_S32 HI_MPI_CIPHER_CENCDecrypt(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_U8 *pu8IV,
                            HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr, HI_U32 u32ByteLength,
                            HI_U32 u32FirstEncryptOffset,
                            HI_UNF_CIPHER_SUBSAMPLE_S *pstSubSample, HI_U32 u32SubsampleNum);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_MPI_CIPHER_H__ */
