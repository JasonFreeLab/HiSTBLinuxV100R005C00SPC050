/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_cipher.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

#define CIPHER_MIN_CRYPT_LEN      8
#define CIPHER_MAX_CRYPT_LEN      0xfffff

HI_S32 HI_MPI_CIPHER_CreateHandle(HI_HANDLE* phCipher,
                                  const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_S32 Ret = HI_FAILURE;
    CIPHER_HANDLE_S stCIHandle = {0};

    INLET_PARAM_CHECK_POINT_NULL(phCipher);
    INLET_PARAM_CHECK_POINT_NULL(pstCipherAttr);

    cipher_memcpy_s(&stCIHandle.stCipherAtts, sizeof(stCIHandle.stCipherAtts),
        pstCipherAttr, sizeof(HI_UNF_CIPHER_ATTS_S));
    Ret=cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CREATEHANDLE, &stCIHandle);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *phCipher = stCIHandle.hCIHandle;

    return Ret;
}

HI_S32 HI_MPI_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_DESTROYHANDLE, &hCipher);
}

HI_S32 HI_MPI_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    CIPHER_CONFIG_CTRL_EX configdata;

    INLET_PARAM_CHECK_POINT_NULL(pstCtrl);

    cipher_memset_s(&configdata, sizeof(configdata), 0, sizeof(CIPHER_CONFIG_CTRL_EX));

    cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key), pstCtrl->u32Key, 32);
    cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV), pstCtrl->u32IV, 16);
    configdata.bKeyByCA = pstCtrl->bKeyByCA;
    configdata.enCaType = pstCtrl->enCaType;
    configdata.enAlg = pstCtrl->enAlg;
    configdata.enBitWidth = pstCtrl->enBitWidth;
    configdata.enWorkMode = pstCtrl->enWorkMode;
    configdata.enKeyLen = pstCtrl->enKeyLen;
    configdata.stChangeFlags = pstCtrl->stChangeFlags;
    configdata.CIHandle=hCipher;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CONFIGHANDLE_EX, &configdata);
}

HI_S32 HI_MPI_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl)
{
    CIPHER_CONFIG_CTRL_EX configdata;

    INLET_PARAM_CHECK_POINT_NULL(pstExCtrl);

    if ((pstExCtrl->enAlg != HI_UNF_CIPHER_ALG_DMA) && (NULL == pstExCtrl->pParam))
    {
        HI_ERR_CIPHER("para pstCtrl param is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    cipher_memset_s(&configdata, sizeof(configdata), 0, sizeof(CIPHER_CONFIG_CTRL_EX));

    configdata.CIHandle = hCipher;
    configdata.enAlg = pstExCtrl->enAlg;
    configdata.enWorkMode = pstExCtrl->enWorkMode;
    configdata.bKeyByCA = pstExCtrl->bKeyByCA;

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
        HI_UNF_CIPHER_CTRL_DES_S *pstDesCtrl =
            (HI_UNF_CIPHER_CTRL_DES_S *)pstExCtrl->pParam;

        cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key),
            pstDesCtrl->u32Key, sizeof(pstDesCtrl->u32Key));
        cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
            pstDesCtrl->u32IV, sizeof(pstDesCtrl->u32IV));

        configdata.enBitWidth = pstDesCtrl->enBitWidth;
        configdata.stChangeFlags = pstDesCtrl->stChangeFlags;
        configdata.enKeyLen = HI_UNF_CIPHER_KEY_DEFAULT;
        configdata.u32IVLen = 8;
        break;
    }
    case HI_UNF_CIPHER_ALG_3DES:
    {
        HI_UNF_CIPHER_CTRL_3DES_S *pst3DesCtrl =
            (HI_UNF_CIPHER_CTRL_3DES_S*)pstExCtrl->pParam;

        cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key),
            pst3DesCtrl->u32Key, 24);
        cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
            pst3DesCtrl->u32IV, 8);

        configdata.enBitWidth = pst3DesCtrl->enBitWidth;
        configdata.enKeyLen = pst3DesCtrl->enKeyLen;
        configdata.stChangeFlags = pst3DesCtrl->stChangeFlags;
        break;
    }
    case HI_UNF_CIPHER_ALG_AES:
    {
        if ((pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
            || (pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
        {

            HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S *pstAesCcmGcmCtrl
                = (HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S*)pstExCtrl->pParam;

            cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key),
                pstAesCcmGcmCtrl->u32Key, sizeof(pstAesCcmGcmCtrl->u32Key));
            cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
                pstAesCcmGcmCtrl->u32IV, sizeof(pstAesCcmGcmCtrl->u32IV));

            configdata.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            configdata.enKeyLen = pstAesCcmGcmCtrl->enKeyLen;
            configdata.u32IVLen = pstAesCcmGcmCtrl->u32IVLen;
            configdata.u32TagLen = pstAesCcmGcmCtrl->u32TagLen;
            configdata.u32APhyAddr = pstAesCcmGcmCtrl->u32APhyAddr;
            configdata.u32ALen = pstAesCcmGcmCtrl->u32ALen;
            configdata.stChangeFlags.bit1IV = 1;
        }
        else
        {
            HI_UNF_CIPHER_CTRL_AES_S *pstAesCtrl =
                (HI_UNF_CIPHER_CTRL_AES_S*)pstExCtrl->pParam;

            cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key),
                pstAesCtrl->u32EvenKey, sizeof(pstAesCtrl->u32EvenKey));
            cipher_memcpy_s(&configdata.u32OddKey, sizeof(configdata.u32Key),
                pstAesCtrl->u32OddKey, sizeof(pstAesCtrl->u32OddKey));
            cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
                pstAesCtrl->u32IV, sizeof(pstAesCtrl->u32IV));

            configdata.enBitWidth = pstAesCtrl->enBitWidth;
            configdata.enKeyLen = pstAesCtrl->enKeyLen;
            configdata.stChangeFlags = pstAesCtrl->stChangeFlags;
            configdata.u32IVLen = 16;
        }
        break;
    }
    case HI_UNF_CIPHER_ALG_SM1:
    {
        HI_UNF_CIPHER_CTRL_SM1_S *pstSm1Ctrl = (HI_UNF_CIPHER_CTRL_SM1_S*)pstExCtrl->pParam;

        cipher_memcpy_s(&configdata.u32Key[0], sizeof(configdata.u32Key),
            pstSm1Ctrl->u32EK, sizeof(pstSm1Ctrl->u32EK));
        cipher_memcpy_s(&configdata.u32Key[4], sizeof(configdata.u32Key),
            pstSm1Ctrl->u32AK, sizeof(pstSm1Ctrl->u32AK));
        cipher_memcpy_s(&configdata.u32Key[8], sizeof(configdata.u32Key),
            pstSm1Ctrl->u32SK, sizeof(pstSm1Ctrl->u32SK));
        cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
            pstSm1Ctrl->u32IV, sizeof(pstSm1Ctrl->u32IV));

        configdata.enSm1Round = pstSm1Ctrl->enSm1Round;
        configdata.enKeyLen = HI_UNF_CIPHER_KEY_DEFAULT;
        configdata.stChangeFlags = pstSm1Ctrl->stChangeFlags;
        configdata.enBitWidth = pstSm1Ctrl->enBitWidth;
        configdata.u32IVLen = 16;

        break;
    }
    case HI_UNF_CIPHER_ALG_SM4:
    {
        HI_UNF_CIPHER_CTRL_SM4_S *pstSm4Ctrl
            = (HI_UNF_CIPHER_CTRL_SM4_S*)pstExCtrl->pParam;

        cipher_memcpy_s(&configdata.u32Key, sizeof(configdata.u32Key),
            pstSm4Ctrl->u32Key, sizeof(pstSm4Ctrl->u32Key));
        cipher_memcpy_s(&configdata.u32IV, sizeof(configdata.u32IV),
            pstSm4Ctrl->u32IV, sizeof(pstSm4Ctrl->u32IV));

        configdata.enKeyLen = HI_UNF_CIPHER_KEY_DEFAULT;
        configdata.stChangeFlags = pstSm4Ctrl->stChangeFlags;
        configdata.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        configdata.u32IVLen = 16;

        break;
    }
    case HI_UNF_CIPHER_ALG_DMA:
    {
        break;
    }
    default:
        HI_ERR_CIPHER("para set CIPHER alg is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CONFIGHANDLE_EX, &configdata);
}

HI_S32 HI_MPI_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CIPHER_DATA_S CIdata;

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPT, &CIdata);
}

HI_S32 HI_MPI_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CIPHER_DATA_S CIdata;

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength = u32ByteLength;
    CIdata.CIHandle=hCipher;

    return cipher_ioctl(g_CipherDevFd,CMD_CIPHER_DECRYPT, &CIdata);
}

HI_S32 HI_MPI_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CIPHER_PKG_S stPkg;
    HI_UNF_CIPHER_DATA_S *pstPkg;
    HI_U32 u32Len;
    HI_S32 ret;

    INLET_PARAM_CHECK_POINT_NULL(pstDataPkg);
    INLET_PARAM_CHECK_U32_ZERO(u32DataPkgNum);

    u32Len = sizeof(HI_UNF_CIPHER_DATA_S) * u32DataPkgNum;
    pstPkg = cipher_malloc(u32Len);
    if (pstPkg == HI_NULL)
    {
        HI_ERR_CIPHER("Error, malloc pkg buffer failed\n");
        return HI_FAILURE;
    }
    cipher_memcpy_s(pstPkg, u32Len, pstDataPkg, u32Len);

    stPkg.CIHandle = hCipher;
    stPkg.pu8Pkg = pstPkg;
    stPkg.u32PkgNum = u32DataPkgNum;

    ret =  cipher_ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPTMULTI, &stPkg);

    cipher_free(pstPkg);

    return ret;
}

HI_S32 HI_MPI_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    CIPHER_PKG_S stPkg;
    HI_UNF_CIPHER_DATA_S *pstPkg;
    HI_U32 u32Len;
    HI_S32 ret;

    INLET_PARAM_CHECK_POINT_NULL(pstDataPkg);
    INLET_PARAM_CHECK_U32_ZERO(u32DataPkgNum);

    u32Len = sizeof(HI_UNF_CIPHER_DATA_S) * u32DataPkgNum;
    pstPkg = cipher_malloc(u32Len);
    if (pstPkg == HI_NULL)
    {
        HI_ERR_CIPHER("Error, malloc pkg buffer failed\n");
        return HI_FAILURE;
    }
    cipher_memcpy_s(pstPkg, u32Len, pstDataPkg, u32Len);

    stPkg.CIHandle = hCipher;
    stPkg.pu8Pkg = pstPkg;
    stPkg.u32PkgNum = u32DataPkgNum;

    ret =  cipher_ioctl(g_CipherDevFd, CMD_CIPHER_DECRYPTMULTI, &stPkg);

    cipher_free(pstPkg);

    return ret;
}

HI_S32 HI_MPI_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_S32 Ret;
    CIPHER_CONFIG_CTRL_EX  configdata;

    INLET_PARAM_CHECK_POINT_NULL(pstCtrl);

    cipher_memset_s(&configdata, sizeof(configdata), 0, sizeof(CIPHER_CONFIG_CTRL_EX));
    configdata.CIHandle = hCipherHandle;
    Ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_GETHANDLECONFIG_EX, &configdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    cipher_memcpy_s(pstCtrl->u32Key, sizeof(pstCtrl->u32Key),
        &configdata.u32Key, 32);
    cipher_memcpy_s(pstCtrl->u32IV, sizeof(pstCtrl->u32IV),
        &configdata.u32IV, sizeof(configdata.u32IV));

    pstCtrl->bKeyByCA = configdata.bKeyByCA;
    pstCtrl->enCaType = configdata.enCaType;
    pstCtrl->enAlg = configdata.enAlg;
    pstCtrl->enBitWidth = configdata.enBitWidth;
    pstCtrl->enWorkMode = configdata.enWorkMode;
    pstCtrl->enKeyLen = configdata.enKeyLen;
    pstCtrl->stChangeFlags = configdata.stChangeFlags;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen)
{
    CIPHER_TAG_S stTag;
    HI_S32 Ret = HI_FAILURE;

    INLET_PARAM_CHECK_POINT_NULL(pu8Tag);
    INLET_PARAM_CHECK_POINT_NULL(pu32TagLen);

    stTag.CIHandle = hCipher;
    Ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_GETTAG, &stTag);
    if (Ret == HI_SUCCESS)
    {
        INLET_PARAM_CHECK_U32_MAX(stTag.u32TagLen, *pu32TagLen);
        cipher_memcpy_s(pu8Tag, *pu32TagLen, stTag.u32Tag, stTag.u32TagLen);
        *pu32TagLen = stTag.u32TagLen;
    }

    return Ret;
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

    cipher_memset_s(&stCencDecrypt, sizeof(stCencDecrypt), 0,  sizeof(stCencDecrypt));
    stCencDecrypt.hCipher = hCipher;
    cipher_memcpy_s(stCencDecrypt.u8Key, 16, pu8Key, 16);
    cipher_memcpy_s(stCencDecrypt.u8IV, 16, pu8IV, 16);
    stCencDecrypt.u32NonSecInputPhyAddr = u32NonSecInPhyAddr;
    stCencDecrypt.u32SecOutputPhyAddr = u32SecOutPhyAddr;
    stCencDecrypt.u32ByteLength = u32ByteLength;
    stCencDecrypt.u32FirstEncryptOffset = u32FirstEncryptOffset;
    stCencDecrypt.pstSubSample = pstSubSample;
    stCencDecrypt.u32SubsampleNum = u32SubsampleNum;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_CENC_DECRYPT, &stCencDecrypt);
}

