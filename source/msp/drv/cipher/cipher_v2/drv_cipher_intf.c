/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 CIPHER_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *argp)
{
    HI_S32 ret = HI_SUCCESS;

//    HI_PRINT("cmd, MOD_ID=0x%X, NR=0x%x, SIZE=0x%x!\n", CIPHER_IOC_TYPE (cmd), CIPHER_IOC_NR (cmd), CIPHER_IOC_SIZE(cmd));

    if (argp == HI_NULL)
    {
        HI_ERR_CIPHER("Error, argp is NULL!\n");
        return HI_FAILURE;
    }

    switch(cmd)
    {
        case CMD_CIPHER_CREATEHANDLE:
        {
            CIPHER_HANDLE_S *pstCIHandle = (CIPHER_HANDLE_S *)argp;
            ret = HI_DRV_CIPHER_CreateHandle(pstCIHandle, file);
            break;
        }
        case CMD_CIPHER_DESTROYHANDLE:
        {
            HI_HANDLE hCipherChn = *(HI_HANDLE *)argp;
            ret = HI_DRV_CIPHER_DestroyHandle(hCipherChn);
            break;
        }
        case CMD_CIPHER_CONFIGHANDLE_EX:
        {
            CIPHER_CONFIG_CTRL_EX stCIConfig = *(CIPHER_CONFIG_CTRL_EX *)argp;

            HI_U32 softChnId = HI_HANDLE_GET_CHNID(stCIConfig.CIHandle);
            ret = HI_DRV_CIPHER_ConfigChnEx(softChnId, &stCIConfig);
            break;
        }
        case CMD_CIPHER_ENCRYPT:
        {
            CIPHER_DATA_S *pstCIData = (CIPHER_DATA_S *)argp;
            ret = HI_DRV_CIPHER_Encrypt(pstCIData);
            break;
        }
        case CMD_CIPHER_DECRYPT:
        {
            CIPHER_DATA_S *pstCIData = (CIPHER_DATA_S *)argp;
            ret = HI_DRV_CIPHER_Decrypt(pstCIData);
            break;
        }
        case CMD_CIPHER_ENCRYPTMULTI:
        {
            CIPHER_PKG_S *pstPkg = (CIPHER_PKG_S *)argp;
            ret = HI_DRV_CIPHER_EncryptMulti(pstPkg);
            break;
        }
        case CMD_CIPHER_DECRYPTMULTI:
        {
            CIPHER_PKG_S *pstPkg = (CIPHER_PKG_S *)argp;
            ret = HI_DRV_CIPHER_DecryptMulti(pstPkg);
            break;
        }
        case CMD_CIPHER_CENC_DECRYPT:
        {
            CIPHER_CENC_DECRYPT_S *pstCencDecrypt = (CIPHER_CENC_DECRYPT_S *)argp;

            ret = HI_DRV_CIPHER_CencDecrypt(pstCencDecrypt);
            break;
        }
#ifdef SM2_ENABLE
        case CMD_SM2_SIGN:
        {
            SM2_SIGN_DATA_S *pstSign = (SM2_SIGN_DATA_S*)argp;
            ret = HI_DRV_SM2_Sign(pstSign);
            break;
        }
        case CMD_SM2_VERIFY:
        {
            SM2_VERIFY_DATA_S *pstVerify = (SM2_VERIFY_DATA_S*)argp;
            ret = HI_DRV_SM2_Verify(pstVerify);
            break;
        }
        case CMD_SM2_ENCRYPT:
        {
            SM2_ENC_DATA_S *pstEnc = (SM2_ENC_DATA_S*)argp;
            ret = HI_DRV_SM2_Encrypt(pstEnc);
            break;
        }
        case CMD_SM2_DECRYPT:
        {
            SM2_DEC_DATA_S *pstDec = (SM2_DEC_DATA_S*)argp;
            ret = HI_DRV_SM2_Decrypt(pstDec);
            break;
        }
        case CMD_SM2_KEY:
        {
            SM2_KEY_DATA_S *pstKey = (SM2_KEY_DATA_S*)argp;
            ret = HI_DRV_SM2_Key(pstKey);
            break;
        }
#endif
        case CMD_CIPHER_GETTAG:
        {
            CIPHER_TAG_S *pstTag = (CIPHER_TAG_S *)argp;
            ret = HI_DRV_CIPHER_GetTag(pstTag);
            break;
        }
        case CMD_CIPHER_GETRANDOMNUMBER:
        {
            CIPHER_RNG_S *pstRNG  = (CIPHER_RNG_S *)argp;
            ret = HI_DRV_CIPHER_GetRandomNumber(pstRNG);
            break;
        }
        case CMD_CIPHER_GETHANDLECONFIG_EX:
        {
            CIPHER_CONFIG_CTRL_EX *pstCIData = (CIPHER_CONFIG_CTRL_EX *)argp;
            ret = HI_DRV_CIPHER_GetHandleConfigEx(pstCIData);
            break;
        }
        case CMD_CIPHER_CALCHASHINIT:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcHashInit(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_CALCHASHUPDATE:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcHashUpdate(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_CALCHASHFINAL:
        {
            CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S*)argp;
               ret = HI_DRV_CIPHER_CalcHashFinal(pstCipherHashData);
            break;
        }
        case CMD_CIPHER_ENCRYPTHDCPKEY:
        {
            CIPHER_HDCP_KEY_TRANSFER_S *pstParam = (CIPHER_HDCP_KEY_TRANSFER_S *)argp;
            ret = HI_DRV_CIPHER_EncryptHDCPKey(pstParam);
            break;
        }
        case CMD_CIPHER_LOADHDCPKEY:
        {
            HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstParam = (HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *)argp;
            ret = HI_DRV_CIPHER_LoadHdcpKey(pstParam);
            break;
        }
        case CMD_CIPHER_CALCRSA:
        {
            CIPHER_RSA_DATA_S *pCipherRsaData = (CIPHER_RSA_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcRsa(pCipherRsaData);
            break;
        }
#ifdef CONFIG_COMPAT
        case CMD_CIPHER_COMPAT_CALCRSA:
        {
            CIPHER_COMPAT_RSA_DATA_S *pCipherCompatRsaData = (CIPHER_COMPAT_RSA_DATA_S*)argp;
            CIPHER_RSA_DATA_S stCipherRsaData;

            stCipherRsaData.pu8Input = U32_TO_POINT(pCipherCompatRsaData->u32InputVia);
            stCipherRsaData.pu8Output = U32_TO_POINT(pCipherCompatRsaData->u328OutputVia);
            stCipherRsaData.pu8K = U32_TO_POINT(pCipherCompatRsaData->u328KVia);
            stCipherRsaData.pu8N = U32_TO_POINT(pCipherCompatRsaData->u328NVia);
            stCipherRsaData.u16KLen = pCipherCompatRsaData->u16KLen;
            stCipherRsaData.u16NLen = pCipherCompatRsaData->u16NLen;
            stCipherRsaData.u32DataLen = pCipherCompatRsaData->u32DataLen;

            ret = HI_DRV_CIPHER_CalcRsa(&stCipherRsaData);
            break;
        }
        case CMD_CIPHER_COMPAT_ENCRYPTMULTI:
        {
            CIPHER_COMPAT_PKG_S *pstPkg = (CIPHER_COMPAT_PKG_S *)argp;
            CIPHER_PKG_S stPkg;

            stPkg.CIHandle = pstPkg->CIHandle;
            stPkg.u32PkgNum = pstPkg->u32PkgNum;
            stPkg.pu8Pkg = U32_TO_POINT(pstPkg->u32PkgVia);

            ret = HI_DRV_CIPHER_EncryptMulti(&stPkg);
            break;
        }
        case CMD_CIPHER_COMPAT_DECRYPTMULTI:
        {
            CIPHER_COMPAT_PKG_S *pstPkg = (CIPHER_COMPAT_PKG_S *)argp;
            CIPHER_PKG_S stPkg;

            stPkg.CIHandle = pstPkg->CIHandle;
            stPkg.u32PkgNum = pstPkg->u32PkgNum;
            stPkg.pu8Pkg = U32_TO_POINT(pstPkg->u32PkgVia);

            ret = HI_DRV_CIPHER_DecryptMulti(&stPkg);
            break;
        }
        case CMD_CIPHER_COMPAT_CENC_DECRYPT:
        {
            CIPHER_COMPAT_CENC_DECRYPT_S *pstCencDecrypt = (CIPHER_COMPAT_CENC_DECRYPT_S *)argp;
            CIPHER_CENC_DECRYPT_S stCencDecrypt;

            stCencDecrypt.hCipher = pstCencDecrypt->hCipher;
            stCencDecrypt.u32ByteLength = pstCencDecrypt->u32ByteLength;
            stCencDecrypt.u32FirstEncryptOffset = pstCencDecrypt->u32FirstEncryptOffset;
            stCencDecrypt.u32NonSecInputPhyAddr = pstCencDecrypt->u32NonSecInputPhyAddr;
            stCencDecrypt.u32SecOutputPhyAddr =  pstCencDecrypt->u32SecOutputPhyAddr;
            stCencDecrypt.u32SubsampleNum =  pstCencDecrypt->u32SubsampleNum;
            memcpy(stCencDecrypt.u8Key, pstCencDecrypt->u8Key, sizeof(pstCencDecrypt->u8Key));
            memcpy(stCencDecrypt.u8IV, pstCencDecrypt->u8Key, sizeof(pstCencDecrypt->u8IV));
            stCencDecrypt.pstSubSample = U32_TO_POINT(pstCencDecrypt->u32SubSampleVia);
            ret = HI_DRV_CIPHER_CencDecrypt(&stCencDecrypt);
            break;
        }
#endif
        default:
        {
            HI_ERR_CIPHER("Unsupport cmd, MOD_ID=0x%02X, NR=0x%02x, SIZE=0x%02x!\n", _IOC_TYPE (cmd), _IOC_NR (cmd), _IOC_SIZE(cmd));
            ret = HI_FAILURE;
            break;
        }
    }

//    HI_PRINT("cipher ioctl return, ret = 0x%x!\n",ret);

    return ret;
}

HI_S32 CIPHER_MODULE_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    ret = DRV_CIPHER_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = DRV_RNG_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

#ifdef SHA3_ENABLE
    ret = DRV_SHA3_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
#endif

#ifdef SM2_ENABLE
    ret = DRV_SM2_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
#endif

    ret = DRV_RSA_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    return HI_SUCCESS;
}

HI_VOID CIPHER_MODULE_Exit(HI_VOID)
{
    (HI_VOID)DRV_CIPHER_DeInit();
    (HI_VOID)DRV_RNG_DeInit();

#ifdef SHA3_ENABLE
    (HI_VOID)DRV_SHA3_DeInit();
#endif

    (HI_VOID)DRV_RSA_DeInit();

#ifdef SM2_ENABLE
    (HI_VOID)DRV_SM2_DeInit();
#endif

    return ;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


