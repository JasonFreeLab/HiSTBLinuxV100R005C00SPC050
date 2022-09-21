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


HI_S32 CIPHER_Ioctl(HI_VOID *inode, HI_VOID *file, unsigned int cmd, HI_VOID *argp)
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
        case CMD_CIPHER_CALCRSA:
        {
            CIPHER_RSA_DATA_S *pCipherRsaData = (CIPHER_RSA_DATA_S*)argp;
            ret = HI_DRV_CIPHER_CalcRsa(pCipherRsaData);
            break;
        }
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

    (HI_VOID)DRV_RSA_DeInit();

    return ;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


