/******************************************************************************
 *
 * Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_cenc.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-03-25
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include <asm/atomic.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/traps.h>
#include <linux/miscdevice.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_dev.h"
#include "hi_drv_mem.h"
#include "hi_osal.h"
#include "drv_cipher_ioctl.h"
#include "drv_cipher_ext.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_cipher.h"

#ifdef HI_SMMU_SUPPORT

 // 长整型大小端互换
#define BigLittleSwap32(A)  ((((HI_U32)(A) & 0xff000000) >> 24) | \
                            (((HI_U32)(A) & 0x00ff0000) >> 8) | \
                            (((HI_U32)(A) & 0x0000ff00) << 8) | \
                            (((HI_U32)(A) & 0x000000ff) << 24))

#define CENC_MMU_NAME "cenc_buf"
#define AES_BLOCK_SIZE 16
#define CENC_MMU_SIZE  0x500000

#if 1
#define CENC_PRINTF(fmt...)
#define CENC_DUMP(a, b, c)
#else
#define CENC_PRINTF(fmt...)   HI_PRINT(fmt)
#define CENC_DUMP dump_hex

static void dump_hex(char* name, HI_U8* vector, HI_U32 length)
{
    HI_U32 i;

    CENC_PRINTF("\nname:%s length:%d \n", name,length);
    CENC_PRINTF("address:%x \n", vector);
    if (vector == NULL) {
        CENC_PRINTF("NULL;\n");
        return;
    }
    // TODO(fredgc): replace with HEXEncode.
    for (i = 0; i < length; i++) {
        if(i%16 == 0)
            CENC_PRINTF("\n");
        CENC_PRINTF("%x ", vector[i]);
    }
    CENC_PRINTF("\n");
}
#endif

 // 本机大端返回1，小端返回0
HI_S32 checkCPUendian(void)
{
    union {
        HI_U32 i;
        HI_UCHAR s[4];
    } c;

    c.i = 0x12345678;
    return (0x12 == c.s[0]);
}

// 模拟ntohl函数，网络字节序转本机字节序
HI_U32 wv_ntohl(HI_U32 n)
{
    // 若本机为大端，与网络字节序同，直接返回
    // 若本机为小端，网络数据转换成小端再返回
    return checkCPUendian() ? n : BigLittleSwap32(n);
}

//return aes ctr clac times before front 64 bits iv data change
static HI_U32 ctr128_get(HI_U8* iv , HI_U32 count)
{
    HI_U32 iv_number = *((HI_U32 *)&iv[8]);
    HI_U32 clacCount = 0xFFFFFFFF - iv_number;
    if(clacCount > 0)
    {
        return 0;
    }

    iv_number = *((HI_U32 *)&iv[12]);
    clacCount = 0xFFFFFFFF - iv_number;
    clacCount = wv_ntohl(clacCount);
    clacCount = clacCount + 1;
    if (clacCount < count)
    {
        return clacCount;
    }
    else
    {
        return 0;
    }
}

#if defined (CHIP_TYPE_hi3796mv200)
extern HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  CIPHER_CONFIG_CTRL_EX *pConfig);
extern HI_S32 DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData, HI_BOOL bIsDecrypt);
#else
extern HI_S32 DRV_CIPHER_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig);
extern HI_S32 DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData);
extern HI_S32 DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData);
extern HI_S32 DRV_CIPHER_GetHandleConfig(CIPHER_Config_CTRL *pstCipherConfig);
#endif

HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
#if defined (CHIP_TYPE_hi3796mv200)
    CIPHER_CONFIG_CTRL_EX configdata;

    if (NULL == pstCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if(pstCtrl->enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        HI_ERR_CIPHER("para set CIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&configdata, 0, sizeof(CIPHER_CONFIG_CTRL_EX));
    memcpy(configdata.u32Key, pstCtrl->u32Key, 32);
    memcpy(configdata.u32IV, pstCtrl->u32IV, 16);
    configdata.bKeyByCA = pstCtrl->bKeyByCA;
    configdata.enCaType = pstCtrl->enCaType;
    configdata.enAlg = pstCtrl->enAlg;
    configdata.enBitWidth = pstCtrl->enBitWidth;
    configdata.enWorkMode = pstCtrl->enWorkMode;
    configdata.enKeyLen = pstCtrl->enKeyLen;
    configdata.stChangeFlags = pstCtrl->stChangeFlags;
    configdata.CIHandle=hCipher;

    return DRV_CIPHER_ConfigChn(hCipher&0xFF, &configdata);
#else
    return DRV_CIPHER_ConfigChn(hCipher&0xFF, pstCtrl);
#endif
}

HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
#if defined (CHIP_TYPE_hi3796mv200)
    HI_S32 Ret;
    CIPHER_CONFIG_CTRL_EX  configdata;

    memset(&configdata, 0, sizeof(CIPHER_CONFIG_CTRL_EX));
    configdata.CIHandle = hCipher;

    Ret = HI_DRV_CIPHER_GetHandleConfigEx(&configdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    memcpy(pstCtrl->u32Key, configdata.u32Key, 32);
    memcpy(pstCtrl->u32IV, configdata.u32IV, 16);
    pstCtrl->bKeyByCA = configdata.bKeyByCA;
    pstCtrl->enCaType = configdata.enCaType;
    pstCtrl->enAlg = configdata.enAlg;
    pstCtrl->enBitWidth = configdata.enBitWidth;
    pstCtrl->enWorkMode = configdata.enWorkMode;
    pstCtrl->enKeyLen = configdata.enKeyLen;
    pstCtrl->stChangeFlags = configdata.stChangeFlags;

    return HI_SUCCESS;
#else
    HI_S32 ret;
    CIPHER_Config_CTRL stCipherConfig;

    stCipherConfig.CIHandle = hCipher;

    ret = DRV_CIPHER_GetHandleConfig(&stCipherConfig);
    if (ret == HI_SUCCESS)
    {
        memcpy(pstCtrl, &stCipherConfig.CIpstCtrl, sizeof(HI_UNF_CIPHER_CTRL_S));
    }

    return ret;
#endif
}

HI_S32 Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CIPHER_DATA_S stCIData;

    stCIData.CIHandle = hCipher;
    stCIData.ScrPhyAddr = u32SrcPhyAddr;
    stCIData.DestPhyAddr = u32DestPhyAddr;
    stCIData.u32DataLength = u32ByteLength;
#if defined (CHIP_TYPE_hi3796mv200)
    return DRV_CIPHER_Encrypt(&stCIData, HI_FALSE);
#else
    return DRV_CIPHER_Encrypt(&stCIData);
#endif
}

HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    CIPHER_DATA_S stCIData;

    stCIData.CIHandle = hCipher;
    stCIData.ScrPhyAddr = u32SrcPhyAddr;
    stCIData.DestPhyAddr = u32DestPhyAddr;
    stCIData.u32DataLength = u32ByteLength;
#if defined (CHIP_TYPE_hi3796mv200)
    return DRV_CIPHER_Encrypt(&stCIData, HI_TRACE_LEVEL_WARN);
#else
    return DRV_CIPHER_Decrypt(&stCIData);
#endif
}

static HI_U32 _get_cipher_data_length(CIPHER_CENC_DECRYPT_S *pstCencDecrypt)
{
    HI_S32 i = 0;
    HI_U32 length = 0;
    HI_UNF_CIPHER_SUBSAMPLE_S *psubsample;
    psubsample = pstCencDecrypt->pstSubSample;

    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        length += psubsample[i].u32PayLoadLen;

        CENC_PRINTF("_get_cipher_data_length length=0x%X\n", length);
    }
    return length;
}

HI_S32 _CencDecrypt_AESCTR(CIPHER_CENC_DECRYPT_S *pstCencDecrypt,
                        HI_UNF_CIPHER_CTRL_S *pstCipherCtrl,
                        HI_U32 chnid)
{
//check if have offset, iv overflow,more than one subsample
    HI_S32 ret;
    HI_S32 i;
    HI_U32 cipher_data_length = 0;        //total encrypted data length
    HI_U32 aesCalcCount = 0;            //total block count of encrypted data
    HI_U32 clacFirst = 0;                //block count before iv overflow

    HI_UNF_CIPHER_SUBSAMPLE_S *psubsample;    //point to subsample
    SMMU_BUFFER_S inputBuffer;            //map input MMU address
    SMMU_BUFFER_S outputBuffer;            //map output MMU address
    SMMU_BUFFER_S sTempSmmuBuf;            //malloc in this function, use for decrypt content

    psubsample = pstCencDecrypt->pstSubSample;

    inputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32NonSecInputPhyAddr;
    outputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32SecOutputPhyAddr;
    inputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    outputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    ret = HI_DRV_SMMU_Map(&inputBuffer);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&outputBuffer);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        return HI_FAILURE;
    }

    cipher_data_length = _get_cipher_data_length(pstCencDecrypt);

    if(0 == cipher_data_length)
    {
        memcpy(outputBuffer.pu8StartVirAddr,
                inputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        return HI_SUCCESS;
    }

    CENC_PRINTF("cipher_data_length=0x%X\n", cipher_data_length);

    aesCalcCount = cipher_data_length / AES_BLOCK_SIZE;
    if(cipher_data_length % AES_BLOCK_SIZE)
        aesCalcCount = aesCalcCount +1;
    clacFirst = ctr128_get( pstCencDecrypt->u8IV , aesCalcCount);

    CENC_PRINTF("clacFirst=0x%X\n", clacFirst);
    CENC_PRINTF("u32FirstEncryptOffset=0x%X\n", pstCencDecrypt->u32FirstEncryptOffset);
    CENC_PRINTF("u32SubsampleNum=0x%X\n", pstCencDecrypt->u32SubsampleNum);

    //deriect decrypt
    if(0 == clacFirst
        && 0 == pstCencDecrypt->u32FirstEncryptOffset
        && 1 == pstCencDecrypt->u32SubsampleNum)
    {
        CENC_PRINTF("deriect decrypt\n");
        //copy clear data
        if(0 != psubsample[0].u32ClearHeaderLen)
        {
            CENC_PRINTF("copy clear data\n");
            memcpy(outputBuffer.pu8StartVirAddr,
                inputBuffer.pu8StartVirAddr,psubsample[0].u32ClearHeaderLen);
        }

        //decrypt
        if(0 != psubsample[0].u32PayLoadLen)
        {
            memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
            memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
            ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                return HI_FAILURE;
            }
            CENC_PRINTF("Cipher_Decrypt\n");
            ret = Cipher_Decrypt(
                                pstCencDecrypt->hCipher,
                                pstCencDecrypt->u32NonSecInputPhyAddr + psubsample[0].u32ClearHeaderLen,
                                pstCencDecrypt->u32SecOutputPhyAddr   + psubsample[0].u32ClearHeaderLen,
                                psubsample[0].u32PayLoadLen);
            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                return HI_FAILURE;
            }
        }
    }
    else //need special process
    {
        HI_S32 totalLength = 0;

        CENC_PRINTF("need special process\n");

        ret = HI_DRV_SMMU_Alloc(
                            CENC_MMU_NAME,
                            pstCencDecrypt->u32ByteLength + pstCencDecrypt->u32FirstEncryptOffset ,
                            16,
                            &sTempSmmuBuf);
        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            return HI_FAILURE;
        }
        ret = HI_DRV_SMMU_Map(&sTempSmmuBuf);
        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }
        CENC_DUMP("malloc sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,pstCencDecrypt->u32ByteLength + pstCencDecrypt->u32FirstEncryptOffset);

        //copy clear to dst , copy encrypted data to a single continuous buffer
        cipher_data_length = 0;
        totalLength = 0;
        for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
        {
            CENC_PRINTF("memcpy_s dst:0x%X offset:0x%X\n",sTempSmmuBuf.pu8StartVirAddr,
                    cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);
            CENC_PRINTF("memcpy_s src:0x%X offset:0x%X\n",inputBuffer.pu8StartVirAddr,
                    totalLength + psubsample[i].u32ClearHeaderLen);
            CENC_PRINTF("memcpy_s length:0x%X\n",psubsample[i].u32PayLoadLen);

            //copy clear to dst

            memcpy(outputBuffer.pu8StartVirAddr + totalLength,
                inputBuffer.pu8StartVirAddr + totalLength ,
                psubsample[i].u32ClearHeaderLen);

            //copy encrypted data to a single continuous buffer
            memcpy(
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                inputBuffer.pu8StartVirAddr + totalLength + psubsample[i].u32ClearHeaderLen,
                psubsample[i].u32PayLoadLen);

            totalLength = totalLength + psubsample[i].u32PayLoadLen + psubsample[i].u32ClearHeaderLen;
            cipher_data_length = cipher_data_length + psubsample[i].u32PayLoadLen;
        }
        //*****copy clear to dst , copy encrypted data to a single continuous buffer end*****

        CENC_PRINTF("decrypt\n");
        CENC_PRINTF("decrypt totalLength:0x%x\n",totalLength);
        CENC_PRINTF("decrypt cipher_data_length:0x%x\n",cipher_data_length);
        CENC_PRINTF("decrypt clacFirst:0x%x\n",clacFirst);
        CENC_DUMP("inputBuffer",inputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

        //decrypt
        if(0 == clacFirst) //iv do not overflow
        {
            CENC_PRINTF("iv do not overflow\n");

            memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
            memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
            ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }

            CENC_DUMP("Key",pstCencDecrypt->u8Key,16);
            CENC_DUMP("IV",pstCencDecrypt->u8IV,16);
            //CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

            ret = Cipher_Decrypt(
                    pstCencDecrypt->hCipher,
                    sTempSmmuBuf.u32StartSmmuAddr,
                    sTempSmmuBuf.u32StartSmmuAddr,
                    cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);
            //CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }
        }
        else    //iv overflow
        {
            CENC_PRINTF("iv overflow\n");
            memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
            memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
            CENC_DUMP("key",pstCipherCtrl->u32Key,16);
            CENC_DUMP("IV",pstCipherCtrl->u32IV,16);
            ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }

            ret = Cipher_Decrypt(
                    pstCencDecrypt->hCipher,
                    sTempSmmuBuf.u32StartSmmuAddr,
                    sTempSmmuBuf.u32StartSmmuAddr,
                    clacFirst*AES_BLOCK_SIZE);

            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }
            //CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

            //IV rollback
            memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
            memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
            memset((HI_U8 *)pstCipherCtrl->u32IV + 8, 0, 8);
            CENC_DUMP("key",pstCipherCtrl->u32Key,16);
            CENC_DUMP("IV",pstCipherCtrl->u32IV,16);
            ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }

            ret = Cipher_Decrypt(
                    pstCencDecrypt->hCipher,
                    sTempSmmuBuf.u32StartSmmuAddr + (clacFirst*AES_BLOCK_SIZE),
                    sTempSmmuBuf.u32StartSmmuAddr + (clacFirst*AES_BLOCK_SIZE),
                    cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset - (clacFirst*AES_BLOCK_SIZE));

            if (HI_SUCCESS != ret)
            {
                HI_DRV_SMMU_Unmap(&inputBuffer);
                HI_DRV_SMMU_Unmap(&outputBuffer);
                HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
                HI_DRV_SMMU_Release(&sTempSmmuBuf);
                return HI_FAILURE;
            }
            //CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        }
        //*****decrypt end*****

        CENC_PRINTF("copy decrypted data to dst\n");

        //*****copy decrypted data to dst*****
        totalLength = 0;
        cipher_data_length = 0;
        for(i = 0 ; i < pstCencDecrypt->u32SubsampleNum ; i++)
        {
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength + psubsample[i].u32ClearHeaderLen,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                psubsample[i].u32PayLoadLen);

            totalLength = totalLength + psubsample[i].u32PayLoadLen + psubsample[i].u32ClearHeaderLen;
            cipher_data_length = cipher_data_length + psubsample[i].u32PayLoadLen;
        }
        //*****copy decrypted data to dst end*****

        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
    }//need special process

    CENC_DUMP("outputBuffer",outputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

    HI_DRV_SMMU_Unmap(&inputBuffer);
    HI_DRV_SMMU_Unmap(&outputBuffer);
    return HI_SUCCESS;
}


HI_S32 _CencDecrypt_PatternAESCTR(CIPHER_CENC_DECRYPT_S *pstCencDecrypt,
                        HI_UNF_CIPHER_CTRL_S *pstCipherCtrl,
                        HI_U32 chnid)
{
    HI_S32 ret;
    HI_S32 i,j;
    HI_U32 cipher_data_length = 0;        //total encrypted data length
    HI_U32 aesCalcCount = 0;              //total encrypted data block size
    HI_U32 clacFirst = 0;                 //data block size before iv overflow
    HI_U32 totalLength = 0;
    HI_S32 length;
    HI_UNF_CIPHER_SUBSAMPLE_S *psubsample;    //point to subsample
    SMMU_BUFFER_S inputBuffer;            //map input MMU address
    SMMU_BUFFER_S outputBuffer;            //map output MMU address
    SMMU_BUFFER_S sTempSmmuBuf;            //malloc in this function, use for decrypt content
    CENC_PRINTF("[ RUN      ]_CencDecrypt_PatternAESCTR enter\n");

    psubsample = pstCencDecrypt->pstSubSample;

    inputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32NonSecInputPhyAddr;
    outputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32SecOutputPhyAddr;
    inputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    outputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    ret = HI_DRV_SMMU_Map(&inputBuffer);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&outputBuffer);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Alloc(CENC_MMU_NAME,pstCencDecrypt->u32ByteLength,16,&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }

    CENC_DUMP("input",inputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

    CENC_PRINTF("copy clear data to dst\n");
    //copy clear data to dst
    memcpy(
            outputBuffer.pu8StartVirAddr ,
            inputBuffer.pu8StartVirAddr ,
            pstCencDecrypt->u32ByteLength);


    CENC_PRINTF("copy encrypted data to a single continuous buffer\n");

    //*****copy encrypted data to a single continuous buffer*****
    totalLength = 0;            //index of buffer in src encrypted buffer
    cipher_data_length = 0;        //index of buffer in temp buffer for decrypted
    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        j = 0;    //index of buffer in current Payload
        totalLength = totalLength + psubsample[i].u32ClearHeaderLen;    //skip clear data, NAL Header
        CENC_PRINTF("SubsampleNum index:0x%x\n",i);
        CENC_PRINTF("u32ClearHeaderLen:0x%x u32PayLoadLen:0x%x\n",psubsample[i].u32ClearHeaderLen , psubsample[i].u32PayLoadLen);
        CENC_PRINTF("totalLength:0x%x\n",totalLength);

        length = psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen;
        CENC_PRINTF("length 1 :0x%x\n",length);
        //handle block offset in current PayLoad
        if( length > 0 )
        {
            length = length > psubsample[i].u32PayLoadLen ? psubsample[i].u32PayLoadLen : length;
            CENC_PRINTF("length 2 :0x%x\n",length);
            // handle u32FirstEncryptOffset, EX: block_offset:0Xb ,pattern encrypt:0X2 ,pattern skip:0X1 ,pattern offset:0X0
            if(0 != pstCencDecrypt->u32FirstEncryptOffset)
            {
                HI_S32 temp_length  = (length + pstCencDecrypt->u32FirstEncryptOffset)
                        - (psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen);
                CENC_PRINTF("temp_length:0x%x\n",temp_length);
                if(temp_length > 0)
                {
                    length = length - temp_length;
                }
            }
            CENC_PRINTF("length:0x%x\n",length);

            memcpy(
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                inputBuffer.pu8StartVirAddr + totalLength ,
                length );

            totalLength = totalLength + length + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + length;
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
            CENC_PRINTF("totalLength:0x%x\n",totalLength);
            CENC_PRINTF("cipher_data_length:0x%x\n",cipher_data_length);
            CENC_PRINTF("j:0x%x\n",j);
        }
        else
        {
            // handle u32FirstEncryptOffset, u32FirstEncryptOffset=0xB, pattern encrypt:0X3, pattern skip:0X7 ,pattern offset:0X9
            // will go into this process
            if( 0 != pstCencDecrypt->u32FirstEncryptOffset )
            {
                HI_S32 temp_length    = psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen
                    - psubsample[i].u32PayloadPatternOffsetLen;
                CENC_PRINTF("handle temp_length:0x%x,u32FirstEncryptOffset:0x%x\n",temp_length,pstCencDecrypt->u32FirstEncryptOffset);

                if(temp_length > 0)
                {

                    memcpy(
                        sTempSmmuBuf.pu8StartVirAddr + cipher_data_length,
                        inputBuffer.pu8StartVirAddr + totalLength + temp_length - pstCencDecrypt->u32FirstEncryptOffset ,
                        pstCencDecrypt->u32FirstEncryptOffset );
                }
            }

            totalLength = totalLength + psubsample[i].u32PayloadPatternClearLen + length;
            //cipher_data_length do not change
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
            CENC_PRINTF("totalLength:0x%x\n",totalLength);
            CENC_PRINTF("cipher_data_length:0x%x\n",cipher_data_length);
            CENC_PRINTF("j:0x%x\n",j);
        }

        while(j + psubsample[i].u32PayloadPatternEncryptLen <= psubsample[i].u32PayLoadLen)
        {
            memcpy(
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                inputBuffer.pu8StartVirAddr + totalLength ,
                psubsample[i].u32PayloadPatternEncryptLen);

            totalLength = totalLength + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayloadPatternEncryptLen;
            j = j + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
            CENC_PRINTF("totalLength:0x%x\n",totalLength);
            CENC_PRINTF("cipher_data_length:0x%x\n",cipher_data_length);
            CENC_PRINTF("j:0x%x\n",j);
        }

        //handle  data left less than u32PayloadPatternEncryptLen
        if(psubsample[i].u32PayLoadLen > j)
        {
            memcpy(
                    sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                    inputBuffer.pu8StartVirAddr + totalLength ,
                    psubsample[i].u32PayLoadLen - j);

            totalLength = totalLength + psubsample[i].u32PayLoadLen - j ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayLoadLen - j;
            j = psubsample[i].u32PayLoadLen;
        }
    }
    //*****copy encrypted data to a single continuous buffer end*****

    //*****decrypt*****
    aesCalcCount = cipher_data_length / AES_BLOCK_SIZE;
    if(cipher_data_length % AES_BLOCK_SIZE)
        aesCalcCount = aesCalcCount +1;
    clacFirst = ctr128_get( pstCencDecrypt->u8IV , aesCalcCount);

    if( 0 == clacFirst )//iv do not overflow
    {
        memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
        memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
        ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }

        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        ret = Cipher_Decrypt(
            pstCencDecrypt->hCipher,
            sTempSmmuBuf.u32StartSmmuAddr,
            sTempSmmuBuf.u32StartSmmuAddr,
            cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);
        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }
    }
    else //iv overflow
    {
        memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
        memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
        ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }

        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        ret = Cipher_Decrypt(
            pstCencDecrypt->hCipher,
            sTempSmmuBuf.u32StartSmmuAddr,
            sTempSmmuBuf.u32StartSmmuAddr,
            clacFirst*AES_BLOCK_SIZE);
        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }

        memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
        memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
        memset((HI_U8 *)pstCipherCtrl->u32IV + 8, 0, 8);
        ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }

        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        ret = Cipher_Decrypt(
            pstCencDecrypt->hCipher,
            sTempSmmuBuf.u32StartSmmuAddr + clacFirst*AES_BLOCK_SIZE,
            sTempSmmuBuf.u32StartSmmuAddr + clacFirst*AES_BLOCK_SIZE,
            cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset - clacFirst*AES_BLOCK_SIZE);
        CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset);

        if (HI_SUCCESS != ret)
        {
            HI_DRV_SMMU_Unmap(&inputBuffer);
            HI_DRV_SMMU_Unmap(&outputBuffer);
            HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
            HI_DRV_SMMU_Release(&sTempSmmuBuf);
            return HI_FAILURE;
        }
    }
    //*****decrypt  end*****


    //*****copy decrypted data to dst*****
    totalLength = 0;            //index of buffer in src encrypted buffer
    cipher_data_length = 0;        //index of buffer in temp buffer for decrypted
    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        j = 0;    //index of buffer in current Payload
        totalLength = totalLength + psubsample[i].u32ClearHeaderLen;    //skip clear data, NAL Header

        length = psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen;
        //handle block offset in current PayLoad
        if( length > 0 )
        {
            length = length >  psubsample[i].u32PayLoadLen  ?
                psubsample[i].u32PayLoadLen : length;
            if(0 != pstCencDecrypt->u32FirstEncryptOffset)
            {
                HI_S32 temp_length  = (length + pstCencDecrypt->u32FirstEncryptOffset)
                        - (psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen);
                if(temp_length > 0)
                {
                    length = length - temp_length;
                }
            }

            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                length
                );

            totalLength = totalLength + length + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + length;
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }
        else
        {
            // handle u32FirstEncryptOffset, u32FirstEncryptOffset=0xB, pattern encrypt:0X3, pattern skip:0X7 ,pattern offset:0X9
            // will go into this process
            if( 0 != pstCencDecrypt->u32FirstEncryptOffset )
            {
                HI_S32 temp_length    = psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen
                    - psubsample[i].u32PayloadPatternOffsetLen;
                CENC_PRINTF("handle temp_length:0x%x,u32FirstEncryptOffset:0x%x\n",temp_length,pstCencDecrypt->u32FirstEncryptOffset);

                if(temp_length > 0)
                {
                    memcpy(
                        outputBuffer.pu8StartVirAddr + totalLength + temp_length - pstCencDecrypt->u32FirstEncryptOffset ,
                        sTempSmmuBuf.pu8StartVirAddr + cipher_data_length,
                        pstCencDecrypt->u32FirstEncryptOffset );
                }
            }
            totalLength = totalLength + psubsample[i].u32PayloadPatternClearLen + length;
            //cipher_data_length do not change
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }


        while(j + psubsample[i].u32PayloadPatternEncryptLen <= psubsample[i].u32PayLoadLen)
        {
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                psubsample[i].u32PayloadPatternEncryptLen
                );

            totalLength = totalLength + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayloadPatternEncryptLen;
            j = j + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
        }

        if(psubsample[i].u32PayLoadLen > j)
        {
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                psubsample[i].u32PayLoadLen - j);

            totalLength = totalLength + psubsample[i].u32PayLoadLen - j ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayLoadLen - j;
            j = psubsample[i].u32PayLoadLen;
        }

    }
    //*****copy decrypted data to dst end*****

    CENC_DUMP("clear",outputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

    HI_DRV_SMMU_Unmap(&inputBuffer);
    HI_DRV_SMMU_Unmap(&outputBuffer);
    HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
    HI_DRV_SMMU_Release(&sTempSmmuBuf);
    return HI_SUCCESS;
}

HI_S32 _CencDecrypt_AESCBC(CIPHER_CENC_DECRYPT_S *pstCencDecrypt,
                        HI_UNF_CIPHER_CTRL_S *pstCipherCtrl,
                        HI_U32 chnid)
{
    HI_S32 ret;
    HI_S32 i;
    HI_U32 cipher_data_length = 0;
    HI_S32 totalLength = 0;
    HI_UNF_CIPHER_SUBSAMPLE_S *psubsample;    //point to subsample
    SMMU_BUFFER_S inputBuffer;            //map input MMU address
    SMMU_BUFFER_S outputBuffer;            //map output MMU address
    SMMU_BUFFER_S sTempSmmuBuf;            //malloc in this function, use for decrypt content

    psubsample = pstCencDecrypt->pstSubSample;

    inputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32NonSecInputPhyAddr;
    outputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32SecOutputPhyAddr;
    inputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    outputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    ret = HI_DRV_SMMU_Map(&inputBuffer);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&outputBuffer);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Alloc(CENC_MMU_NAME,pstCencDecrypt->u32ByteLength,16,&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }
    CENC_DUMP("input",inputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

    //copy clear to dst
    memcpy(
            outputBuffer.pu8StartVirAddr ,
            inputBuffer.pu8StartVirAddr ,
            pstCencDecrypt->u32ByteLength);

    //copy encrypted data to a single continuous buffer
    cipher_data_length = 0;
    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        memcpy(
            sTempSmmuBuf.pu8StartVirAddr + cipher_data_length,
            inputBuffer.pu8StartVirAddr + totalLength + psubsample[i].u32ClearHeaderLen,
            psubsample[i].u32PayLoadLen);

        totalLength = totalLength + psubsample[i].u32PayLoadLen + psubsample[i].u32ClearHeaderLen;
        cipher_data_length = cipher_data_length + psubsample[i].u32PayLoadLen;
    }

    //decrypt
    memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
    memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
    ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }
    CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length);

    ret = Cipher_Decrypt(
        pstCencDecrypt->hCipher,
        sTempSmmuBuf.u32StartSmmuAddr,
        sTempSmmuBuf.u32StartSmmuAddr,
        cipher_data_length & 0xFFFFFFF0 );
    CENC_DUMP("sTempSmmuBuf",sTempSmmuBuf.pu8StartVirAddr,cipher_data_length);

    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }

    //copy decrypted data to dst
    totalLength = 0;
    cipher_data_length = 0;
    for(i = 0 ; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        memcpy(
            outputBuffer.pu8StartVirAddr + totalLength + psubsample[i].u32ClearHeaderLen,
            sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
            psubsample[i].u32PayLoadLen);

        totalLength = totalLength + psubsample[i].u32PayLoadLen + psubsample[i].u32ClearHeaderLen;
        cipher_data_length = cipher_data_length + psubsample[i].u32PayLoadLen;
    }
    CENC_DUMP("sTempSmmuBuf",outputBuffer.pu8StartVirAddr,pstCencDecrypt->u32ByteLength);

    HI_DRV_SMMU_Unmap(&inputBuffer);
    HI_DRV_SMMU_Unmap(&outputBuffer);
    HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
    HI_DRV_SMMU_Release(&sTempSmmuBuf);
    return HI_SUCCESS;
}

HI_S32 _CencDecrypt_PatternAESCBC(CIPHER_CENC_DECRYPT_S *pstCencDecrypt,
                        HI_UNF_CIPHER_CTRL_S *pstCipherCtrl,
                        HI_U32 chnid)
{
    HI_S32 ret;
    HI_S32 i,j;
    HI_U32 cipher_data_length = 0;        //total encrypted data length
    HI_U32 totalLength = 0;
    HI_U32 length;
    HI_UNF_CIPHER_SUBSAMPLE_S *psubsample;    //point to subsample
    SMMU_BUFFER_S inputBuffer;            //map input MMU address
    SMMU_BUFFER_S outputBuffer;            //map output MMU address
    SMMU_BUFFER_S sTempSmmuBuf;            //malloc in this function, use for decrypt content
    CENC_PRINTF("[ RUN      ]_CencDecrypt_PatternAESCBC enter\n");

    psubsample = pstCencDecrypt->pstSubSample;

    inputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32NonSecInputPhyAddr;
    outputBuffer.u32StartSmmuAddr = pstCencDecrypt->u32SecOutputPhyAddr;
    inputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    outputBuffer.u32Size = pstCencDecrypt->u32ByteLength;
    ret = HI_DRV_SMMU_Map(&inputBuffer);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&outputBuffer);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Alloc(CENC_MMU_NAME,pstCencDecrypt->u32ByteLength,16,&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        return HI_FAILURE;
    }
    ret = HI_DRV_SMMU_Map(&sTempSmmuBuf);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }

    //*****copy clear data to dst
    memcpy(
            outputBuffer.pu8StartVirAddr ,
            inputBuffer.pu8StartVirAddr ,
            pstCencDecrypt->u32ByteLength);

    //*****copy encrypted data to a single continuous buffer*****
    totalLength = 0;
    cipher_data_length = 0;
    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        j = 0;    //index of buffer in current Payload
        totalLength = totalLength + psubsample[i].u32ClearHeaderLen;    //skip clear data, NAL Header

        length = psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen;
        //handle block offset in current PayLoad
        if( length > 0 )
        {
            length = length > psubsample[i].u32PayLoadLen ? psubsample[i].u32PayLoadLen : length;
            memcpy(
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                inputBuffer.pu8StartVirAddr + totalLength ,
                length );

            totalLength = totalLength + length + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + length;
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }
        else
        {
            totalLength = totalLength + psubsample[i].u32PayloadPatternClearLen + length;
            //cipher_data_length do not change
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }


        while(j + psubsample[i].u32PayloadPatternEncryptLen <= psubsample[i].u32PayLoadLen)
        {
            memcpy(
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                inputBuffer.pu8StartVirAddr + totalLength ,
                psubsample[i].u32PayloadPatternEncryptLen);

            totalLength = totalLength + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayloadPatternEncryptLen;
            j = j + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
        }

        //handle  data left less than u32PayloadPatternEncryptLen
        if(psubsample[i].u32PayLoadLen > j)
        {
            memcpy(
                    sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                    inputBuffer.pu8StartVirAddr + totalLength ,
                    psubsample[i].u32PayLoadLen - j);

            totalLength = totalLength + psubsample[i].u32PayLoadLen - j ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayLoadLen - j;
            j = psubsample[i].u32PayLoadLen;
        }
    }
    //*****copy encrypted data to a single continuous buffer end*****

    //*****decrypt*****
    memcpy(pstCipherCtrl->u32Key, pstCencDecrypt->u8Key, 16);
    memcpy(pstCipherCtrl->u32IV, pstCencDecrypt->u8IV, 16);
    ret = Cipher_ConfigHandle(chnid, pstCipherCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }

    ret = Cipher_Decrypt(
        pstCencDecrypt->hCipher,
        sTempSmmuBuf.u32StartSmmuAddr,
        sTempSmmuBuf.u32StartSmmuAddr,
        cipher_data_length  & 0xFFFFFFF0 );

    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(&inputBuffer);
        HI_DRV_SMMU_Unmap(&outputBuffer);
        HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
        HI_DRV_SMMU_Release(&sTempSmmuBuf);
        return HI_FAILURE;
    }
    //*****decrypt end*****

    //*****copy decrypted data to dst*****
    totalLength = 0;            //index of buffer in src encrypted buffer
    cipher_data_length = 0;        //index of buffer in temp buffer for decrypted
    for(i = 0; i < pstCencDecrypt->u32SubsampleNum ; i++)
    {
        j = 0;    //index of buffer in current Payload
        totalLength = totalLength + psubsample[i].u32ClearHeaderLen;    //skip clear data, NAL Header

        length = psubsample[i].u32PayloadPatternEncryptLen - psubsample[i].u32PayloadPatternOffsetLen;
        //handle block offset in current PayLoad
        if( length > 0 )
        {
            length = length > psubsample[i].u32PayLoadLen ? psubsample[i].u32PayLoadLen  : length;
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                length
                );

            totalLength = totalLength + length + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + length;
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }
        else
        {
            totalLength = totalLength + psubsample[i].u32PayloadPatternClearLen + length;
            //cipher_data_length do not change
            j = j + length + psubsample[i].u32PayloadPatternClearLen;
        }


        while(j + psubsample[i].u32PayloadPatternEncryptLen <= psubsample[i].u32PayLoadLen)
        {
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                psubsample[i].u32PayloadPatternEncryptLen
                );

            totalLength = totalLength + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayloadPatternEncryptLen;
            j = j + psubsample[i].u32PayloadPatternEncryptLen + psubsample[i].u32PayloadPatternClearLen ;
        }

        if(psubsample[i].u32PayLoadLen > j)
        {
            memcpy(
                outputBuffer.pu8StartVirAddr + totalLength ,
                sTempSmmuBuf.pu8StartVirAddr + cipher_data_length + pstCencDecrypt->u32FirstEncryptOffset ,
                psubsample[i].u32PayLoadLen - j);

            totalLength = totalLength + psubsample[i].u32PayLoadLen - j ;
            cipher_data_length  = cipher_data_length + psubsample[i].u32PayLoadLen - j;
            j = psubsample[i].u32PayLoadLen;
        }

    }
    //*****copy decrypted data to dst end*****

    HI_DRV_SMMU_Unmap(&inputBuffer);
    HI_DRV_SMMU_Unmap(&outputBuffer);
    HI_DRV_SMMU_Unmap(&sTempSmmuBuf);
    HI_DRV_SMMU_Release(&sTempSmmuBuf);
    return HI_SUCCESS;
}

HI_S32 Cipher_CencDecrypt(CIPHER_CENC_DECRYPT_S *pstCencDecrypt)
{
    HI_U32 chnid = 0;
    HI_S32 ret;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    HI_UNF_CIPHER_SUBSAMPLE_S *pstSubSample;
    HI_U32 u32SubSampleLen = 0;

    CENC_PRINTF("CIPHERDRV Cipher_CencDecrypt enter\n");
    CENC_PRINTF("###CIPHERDRV Cipher_CencDecrypt enter\n");

    CENC_PRINTF("pstCencDecrypt:\n");
    CENC_PRINTF("u8Key=0x%X\n",pstCencDecrypt->u8Key);
    CENC_PRINTF("u8IV=0x%X\n",pstCencDecrypt->u8IV);
    CENC_PRINTF("u32NonSecInputPhyAddr=0x%X\n",pstCencDecrypt->u32NonSecInputPhyAddr);
    CENC_PRINTF("u32SecOutputPhyAddr=0x%X\n",pstCencDecrypt->u32SecOutputPhyAddr);
    CENC_PRINTF("u32ByteLength=0x%X\n",pstCencDecrypt->u32ByteLength);
    CENC_PRINTF("u32FirstEncryptOffset=0x%X\n",pstCencDecrypt->u32FirstEncryptOffset);
    CENC_PRINTF("pstSubSample=0x%X\n",pstCencDecrypt->pstSubSample);
    CENC_PRINTF("u32SubsampleNum=0x%X\n",pstCencDecrypt->u32SubsampleNum);

    if(NULL == pstCencDecrypt)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    ret = Cipher_GetHandleConfig(pstCencDecrypt->hCipher, &stCipherCtrl);
    if (ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    u32SubSampleLen = pstCencDecrypt->u32SubsampleNum * sizeof(HI_UNF_CIPHER_SUBSAMPLE_S);
    pstSubSample = (HI_UNF_CIPHER_SUBSAMPLE_S *)HI_KMALLOC(HI_ID_CIPHER, u32SubSampleLen, GFP_KERNEL);
    if (HI_NULL == pstSubSample)
    {
        HI_ERR_CIPHER("malloc for SubSample failed!\n");
        return HI_FAILURE;
    }
    memcpy(pstSubSample, pstCencDecrypt->pstSubSample, u32SubSampleLen);
    pstCencDecrypt->pstSubSample = pstSubSample;
    chnid = pstCencDecrypt->hCipher & 0xFF;
    ret = HI_FAILURE;

    /*CENC Decrypt Start*/
    if(HI_UNF_CIPHER_WORK_MODE_CTR == stCipherCtrl.enWorkMode)
    {
        if( pstCencDecrypt->pstSubSample->u32PayloadPatternEncryptLen == 0
            &&  pstCencDecrypt->pstSubSample->u32PayloadPatternClearLen == 0)
        {
            //AES CTR
            ret = _CencDecrypt_AESCTR(pstCencDecrypt,&stCipherCtrl,chnid);
        }
        else
        {
            //Pattern AES CTR
            ret = _CencDecrypt_PatternAESCTR(pstCencDecrypt,&stCipherCtrl,chnid);
        }
    }
    else if(HI_UNF_CIPHER_WORK_MODE_CBC == stCipherCtrl.enWorkMode)
    {
        if( pstCencDecrypt->pstSubSample->u32PayloadPatternEncryptLen == 0
            &&  pstCencDecrypt->pstSubSample->u32PayloadPatternClearLen == 0)
        {
            //AES CBC
            ret = _CencDecrypt_AESCBC(pstCencDecrypt,&stCipherCtrl,chnid);
        }
        else
        {
            //Pattern AES CBC
            ret = _CencDecrypt_PatternAESCBC(pstCencDecrypt,&stCipherCtrl,chnid);
        }
    }
    else
    {
        HI_ERR_CIPHER("invalid mode 0x%x\n", stCipherCtrl.enWorkMode);
        ret = HI_FAILURE;
    }

    HI_KFREE(HI_ID_CIPHER, pstSubSample);

    return ret;

    /*CENC Decrypt End*/
}
#endif

