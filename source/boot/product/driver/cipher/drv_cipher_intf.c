/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_cipher_intf.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef HI_MINIBOOT_SUPPORT
#include "linux/mtd/compat.h"
#include <common.h>
#else
#include "string.h"
#include "stdio.h"
#include "delay.h"
#endif

#include "hi_type.h"
#include "drv_cipher_intf.h"
#include "drv_cipher.h"
#include "drv_rsa.h"
#include "drv_cipher_define.h"
#include "hi_unf_cipher.h"
#include "malloc.h"

extern HI_S32 HI_CIPHER_EncryptEx(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output);

#define HI_ID_CIPHER 0x4D

#define HI_HANDLE_MAKEHANDLE(mod, privatedata, chnid)  (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((((privatedata)& 0xff) << 8) ) | (((chnid) & 0xff)) )

#define HI_HANDLE_GET_MODID(handle)    (((handle) >> 16) & 0xffff)
#define HI_HANDLE_GET_PriDATA(handle)  (((handle) >> 8) & 0xff)
#define HI_HANDLE_GET_CHNID(handle)    (((handle)) & 0xff)

typedef struct hiCIPHER_OSR_CHN_S
{
    HI_BOOL g_bSoftChnOpen; /* mark soft channel open or not*/
    HI_BOOL g_bDataDone;    /* mark the data done or not */

    HI_UNF_CIPHER_DATA_S *pstDataPkg;
    HI_U32                u32DataPkgNum;
}CIPHER_OSR_CHN_S;

static CIPHER_OSR_CHN_S g_stCipherOsrChn[CIPHER_SOFT_CHAN_NUM];
static HI_HANDLE  g_cipherChn = 0;          /* cipher handle */
static HI_U32 g_softChnId = 0;                  /* soft channel ID */

static HI_S32 g_CipherDevFd = -1;
//CIPHER_HASH_DATA_S g_stCipherHashData;

static HI_U8 g_u8CbcMac[16];

#define HASH_BLOCK_SIZE            (64)
#define HASH_PAD_MAX_LEN        (64)
#define HASH1_SIGNATURE_SIZE        (20)
#define HASH256_SIGNATURE_SIZE        (32)
#define HASH_CHANNAL_MAX_NUM    (8)

typedef struct hiHASH_INFO_S
{
    HI_BOOL   bIsUsed;
    HI_HANDLE hHandle;
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;
    HI_U32 u32TotalDataLen;
    HI_U32 u32ShaVal[8];
    HI_U32 u32ShaLen;
    HI_U32 u32LastBlock[32];
    HI_U8  u8Mac[HASH_BLOCK_SIZE];
    HI_U32 u32LastBlockSize;
}HASH_INFO_S;

static HASH_INFO_S g_stCipherHashData[HASH_CHANNAL_MAX_NUM];


#define CIPHER_CheckHandle(softChnId) do{\
        if (HI_FALSE == g_stCipherOsrChn[softChnId].g_bSoftChnOpen)\
        {\
            HI_ERR_CIPHER("invalid chn %d, open=%d.\n", softChnId, g_stCipherOsrChn[softChnId].g_bSoftChnOpen);\
            return HI_ERR_CIPHER_INVALID_HANDLE;\
        }\
    }while(0)

static HI_S32 cipher_waitStat(HI_U32 chnId)
{
    HI_U32 cnt;
    HI_U32 cipherStat;

    /* wait for Cipher calc done */
    cnt = 0;
    // corform one value when test, about 500
    while (cnt < 10000)
    {
        DRV_Cipher_Stat(chnId, &cipherStat);
        if (CIPHER_PKGx1_CHAN == chnId)
        {
            if (cipherStat == 0)
            {
                break;
            }
        }
        else
        {
            if (cipherStat == 1)
            {
                break;
            }
        }
        udelay(10);
        cnt++;
    }

    if (cnt >= 10000)
    {
        HI_ERR_CIPHER("cipher_waitStat handle too long \n");
        return HI_FAILURE;      /* overtime */
    }

    DRV_CipherDataDoneMultiPkg(chnId);
    return HI_SUCCESS;        /* success */
}

static HI_VOID DRV_CIPHER_UserCommCallBack(HI_U32 arg)
{
    //HI_ERR_CIPHER("arg=%#x.\n", arg);

    //g_stCipherOsrChn[arg].g_bDataDone = HI_TRUE;

    return ;
}

/* New unf interface: HI_UNF_CIHPER_Init */
HI_S32 Cipher_Init(HI_VOID)
{
    if (g_CipherDevFd >= 0)
    {
        g_CipherDevFd++;
        return HI_SUCCESS;
    }
#ifndef CONFIG_SBL
    HI_U32 i;
    HI_S32 ret;
    ret = DRV_Cipher_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
        g_stCipherOsrChn[i].g_bDataDone = HI_FALSE;
        g_stCipherOsrChn[i].pstDataPkg = NULL;
    }
#endif
    g_CipherDevFd = 0;
    
    return HI_SUCCESS;
}

/* New unf interface: HI_UNF_CIHPER_DeInit */
HI_VOID Cipher_Exit(HI_VOID)
{
    if (g_CipherDevFd > 0)
    {
        g_CipherDevFd--;
        return;
    }
	
	if (g_CipherDevFd < 0)
    {
        g_CipherDevFd = -1;
        return;
    }
 #ifndef CONFIG_SBL 
    HI_U32 i;  
    for (i = 0; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        DRV_Cipher_CloseChn(i);
        g_stCipherOsrChn[i].g_bSoftChnOpen = HI_FALSE;
		if (g_stCipherOsrChn[i].pstDataPkg)
	    {
		    free(g_stCipherOsrChn[i].pstDataPkg);
		    g_stCipherOsrChn[i].pstDataPkg = NULL;
	    }
    }
    
    DRV_Cipher_DeInit();
#endif
    g_CipherDevFd = -1;

    return ;
}

/* New unf interface: HI_UNF_CIHPER_CreateHandle */
HI_S32 Cipher_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_U32 i;
    HI_S32         Ret = 0;

    if (NULL == phCipher)
    {
        HI_ERR_CIPHER("para phCipher is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ( HI_UNF_CIPHER_TYPE_NORMAL != pstCipherAttr->enCipherType )
    {
        if( HI_UNF_CIPHER_TYPE_COPY_AVOID != pstCipherAttr->enCipherType )
        {
            Ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
            HI_ERR_CIPHER("Invalid Cipher Type!\n");
            return Ret;
        }

        if (0 == g_stCipherOsrChn[0].g_bSoftChnOpen)
        {
            i = 0;
        }
        else
        {
            i = CIPHER_INVALID_CHN;
        }
    }
    else
    {
        for(i = CIPHER_PKGxN_CHAN_MIN; i < CIPHER_SOFT_CHAN_NUM; i++)
        {
            if (0 == g_stCipherOsrChn[i].g_bSoftChnOpen)
            {
                break;
            }
        }
    }

    for(i = CIPHER_PKGxN_CHAN_MIN; i < CIPHER_SOFT_CHAN_NUM; i++)
    {
        if (0 == g_stCipherOsrChn[i].g_bSoftChnOpen)
        {
            break;
        }
    }

    if (i >= CIPHER_SOFT_CHAN_NUM)
    {
        Ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
        HI_ERR_CIPHER("No more cipher chan left.\n");
        return HI_FAILURE;
    }
    else /* get a free chn */
    {
        g_stCipherOsrChn[i].pstDataPkg = (HI_UNF_CIPHER_DATA_S *)malloc(sizeof(HI_UNF_CIPHER_DATA_S) * CIPHER_MAX_LIST_NUM);
        if (NULL == g_stCipherOsrChn[i].pstDataPkg)
        {
            Ret = HI_ERR_CIPHER_FAILED_GETHANDLE;
            HI_ERR_CIPHER("can NOT malloc memory for cipher.\n");
            return HI_FAILURE;
        }

        g_softChnId = i;
        g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen = HI_TRUE;
    }


    g_cipherChn = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, g_softChnId);

    Ret = DRV_Cipher_OpenChn(g_softChnId);
    if (HI_SUCCESS != Ret)
    {
        free(g_stCipherOsrChn[i].pstDataPkg);
        g_stCipherOsrChn[i].pstDataPkg = NULL;
        return HI_FAILURE;
    }

    *phCipher = g_cipherChn;

    Ret = HI_SUCCESS;

    return Ret;
}

/* New unf interface: HI_UNF_CIHPER_DestroyHandle */
HI_S32 Cipher_DestroyHandle(HI_HANDLE hCipher)
{
    HI_S32         Ret = 0;

    g_cipherChn = hCipher;

    g_softChnId = HI_HANDLE_GET_CHNID(g_cipherChn);
    if (HI_FALSE == g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen)
    {
        Ret = HI_SUCCESS; /* success on re-Destroy */
        return Ret;
    }

    if (g_stCipherOsrChn[g_softChnId].pstDataPkg)
    {
        free(g_stCipherOsrChn[g_softChnId].pstDataPkg);
        g_stCipherOsrChn[g_softChnId].pstDataPkg = NULL;
    }

    g_stCipherOsrChn[g_softChnId].g_bSoftChnOpen = HI_FALSE;
    Ret = DRV_Cipher_CloseChn(g_softChnId);

    return Ret;
}

/* New unf interface: HI_UNF_CIHPER_ConfigHandle */
HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_U32 Ret;
    CIPHER_Config_CTRL  configdata;

    if (NULL == pstCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    memcpy(&configdata.CIpstCtrl, pstCtrl, sizeof(HI_UNF_CIPHER_CTRL_S));
    configdata.CIHandle=hCipher;

    if(configdata.CIpstCtrl.enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        HI_ERR_CIPHER("para setCIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    g_softChnId = HI_HANDLE_GET_CHNID(configdata.CIHandle);
    CIPHER_CheckHandle(g_softChnId);

    Ret = DRV_Cipher_ConfigChn(g_softChnId, &configdata.CIpstCtrl, DRV_CIPHER_UserCommCallBack);

    return Ret;
}

HI_S32 Cipher_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl)
{
    CIPHER_Config_CTRL configdata;

    if (NULL == pstExCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (pstExCtrl->enAlg == HI_UNF_CIPHER_ALG_DMA)
    {
        HI_ERR_CIPHER("Don't support DMA.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if (NULL == pstExCtrl->pParam)
    {
        HI_ERR_CIPHER("para pstCtrl param is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pstExCtrl->enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
        || (pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_CCM)
        || (pstExCtrl->enWorkMode == HI_UNF_CIPHER_WORK_MODE_GCM))
    {
        HI_ERR_CIPHER("para set CIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    memset(&configdata, 0, sizeof(CIPHER_Config_CTRL));

    configdata.CIHandle= hCipher;
    configdata.CIpstCtrl.enAlg = pstExCtrl->enAlg;
    configdata.CIpstCtrl.enWorkMode = pstExCtrl->enWorkMode;
    configdata.CIpstCtrl.bKeyByCA = pstExCtrl->bKeyByCA;

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
        HI_UNF_CIPHER_CTRL_DES_S *pstDesCtrl = (HI_UNF_CIPHER_CTRL_DES_S *)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pstDesCtrl->u32Key, 8);
        memcpy(configdata.CIpstCtrl.u32IV, pstDesCtrl->u32IV, 8);
        configdata.CIpstCtrl.enBitWidth = pstDesCtrl->enBitWidth;
        configdata.CIpstCtrl.stChangeFlags = pstDesCtrl->stChangeFlags;
        configdata.CIpstCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DEFAULT;
        break;
    }
    case HI_UNF_CIPHER_ALG_3DES:
    {
        HI_UNF_CIPHER_CTRL_3DES_S *pst3DesCtrl = (HI_UNF_CIPHER_CTRL_3DES_S*)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pst3DesCtrl->u32Key, 16);
        memcpy(configdata.CIpstCtrl.u32IV, pst3DesCtrl->u32IV, 8);
        configdata.CIpstCtrl.enBitWidth = pst3DesCtrl->enBitWidth;
        configdata.CIpstCtrl.enKeyLen = pst3DesCtrl->enKeyLen;
        configdata.CIpstCtrl.stChangeFlags = pst3DesCtrl->stChangeFlags;
        break;
    }
    case HI_UNF_CIPHER_ALG_AES:
    {
        HI_UNF_CIPHER_CTRL_AES_S *pstAesCtrl = (HI_UNF_CIPHER_CTRL_AES_S*)pstExCtrl->pParam;
        memcpy(configdata.CIpstCtrl.u32Key, pstAesCtrl->u32EvenKey, 32);
        memcpy(configdata.CIpstCtrl.u32IV, pstAesCtrl->u32IV, 16);
        configdata.CIpstCtrl.enBitWidth = pstAesCtrl->enBitWidth;
        configdata.CIpstCtrl.enKeyLen = pstAesCtrl->enKeyLen;
        configdata.CIpstCtrl.stChangeFlags = pstAesCtrl->stChangeFlags;
        break;
    }
    default:
        HI_ERR_CIPHER("para set CIPHER alg is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return DRV_Cipher_ConfigChn(g_softChnId, &configdata.CIpstCtrl, DRV_CIPHER_UserCommCallBack);;
}

/* New unf interface: HI_UNF_CIHPER_Encrypt */
HI_S32 Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_U32 Ret;
    HI_U32 chnid;
    CIPHER_DATA_S CIdata;
    HI_DRV_CIPHER_TASK_S pCITask;

    chnid = HI_HANDLE_GET_CHNID(hCipher);

    if (0 == chnid || u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.ByteLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    g_softChnId = HI_HANDLE_GET_CHNID(CIdata.CIHandle);
    CIPHER_CheckHandle(g_softChnId);

    pCITask.stData2Process.u32src = CIdata.ScrPhyAddr;
    pCITask.stData2Process.u32dest = CIdata.DestPhyAddr;
    pCITask.stData2Process.u32length = CIdata.ByteLength;
    pCITask.stData2Process.bDecrypt = HI_FALSE;
    pCITask.u32CallBackArg = g_softChnId;

    g_stCipherOsrChn[g_softChnId].g_bDataDone = HI_FALSE;

    Ret = DRV_Cipher_CreatTask(g_softChnId,&pCITask, NULL, NULL);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

    //HI_INFO_CIPHER("\nencrypt wait channel %d queue event\n", softChnId);

    Ret = cipher_waitStat(chnid);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CIPHER("Cipher_Encrypt  timeout\n");
        return HI_FAILURE;
    }

    Ret = HI_SUCCESS;

    return Ret;
}

/* New unf interface: HI_UNF_CIHPER_Decrypt */
HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_U32 Ret;
    HI_U32 chnid;
    CIPHER_DATA_S CIdata;
    HI_DRV_CIPHER_TASK_S       pCITask;

    chnid = HI_HANDLE_GET_CHNID(hCipher);

    if (0 == chnid || u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.ByteLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    g_softChnId = HI_HANDLE_GET_CHNID(CIdata.CIHandle);
    CIPHER_CheckHandle(g_softChnId);
    pCITask.stData2Process.u32src=CIdata.ScrPhyAddr;
    pCITask.stData2Process.u32dest=CIdata.DestPhyAddr;
    pCITask.stData2Process.u32length=CIdata.ByteLength;
    pCITask.stData2Process.bDecrypt=HI_TRUE;

    pCITask.u32CallBackArg=g_softChnId;

    g_stCipherOsrChn[g_softChnId].g_bDataDone = HI_FALSE;

    Ret = DRV_Cipher_CreatTask(g_softChnId,&pCITask,NULL,NULL);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

    Ret = cipher_waitStat(chnid);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CIPHER("Cipher_Encrypt  timeout\n");
        return HI_FAILURE;
    }


    Ret = HI_SUCCESS;

    return Ret;
}

HI_S32 Cipher_GetRandomNumber(HI_U32 *pu32RandomNumber)
{
    return HAL_Cipher_GetRandomNumber(pu32RandomNumber);
}

static HI_U32 HashMsgPadding(HI_U8 *pu8Msg, HI_U32 u32ByteLen, HI_U32 u32TotalLen)
{
    HI_U32 u32Tmp = 0;
    HI_U32 u32PaddingLen;

    if( NULL == pu8Msg )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return -1;
    }

    u32Tmp = u32TotalLen % 64;
    /* 56 = 64 - 8, 120 = 56 + 64 */
    u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
    /* add 8 bytes fix data length */
    u32PaddingLen += 8;

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    pu8Msg[u32ByteLen++] = 0x80;
    memset(&pu8Msg[u32ByteLen], 0, u32PaddingLen - 1 - 8);
    u32ByteLen+=u32PaddingLen - 1 - 8;

    /* write 8 bytes fix data length */
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = 0x00;
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 29)&0x07);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 21)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 13)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen >> 5)&0xff);
    pu8Msg[u32ByteLen++] = (HI_U8)((u32TotalLen << 3)&0xff);

    return u32ByteLen;
}

//#ifndef HI_MINIBOOT_SUPPORT
/* New unf interface: HI_UNF_CIHPER_HashInit */
HI_S32 HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;
    HI_U32 u32SoftId;
    HI_HANDLE hCipherHandle;
    CIPHER_HASH_DATA_S stHashData;
    HASH_INFO_S *pstHashInfo;

    if( (NULL== pstHashAttr) || (NULL == pHashHandle) )
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    if(pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT)
    {
        HI_ERR_CIPHER("Invalid hash type input!\n");
        return HI_FAILURE;
    }

    for(u32SoftId=0; u32SoftId<HASH_CHANNAL_MAX_NUM; u32SoftId++)
    {
        if (!g_stCipherHashData[u32SoftId].bIsUsed)
        {
            break;
        }
    }
    if(u32SoftId >= HASH_CHANNAL_MAX_NUM)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        return HI_FAILURE;
    }
    pstHashInfo = &g_stCipherHashData[u32SoftId];
    memset(pstHashInfo, 0, sizeof(HASH_INFO_S));
    memset(&stHashData, 0, sizeof(CIPHER_HASH_DATA_S));
    stHashData.enShaType = pstHashAttr->eShaType;
    pstHashInfo->enShaType = pstHashAttr->eShaType;

    switch(pstHashAttr->eShaType)
    {
        case HI_UNF_CIPHER_HASH_TYPE_SHA1:
        case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1:
        {
            pstHashInfo->u32ShaLen = HASH1_SIGNATURE_SIZE;
            pstHashInfo->u32ShaVal[0] = 0x01234567;
            pstHashInfo->u32ShaVal[1] = 0x89abcdef;
            pstHashInfo->u32ShaVal[2] = 0xfedcba98;
            pstHashInfo->u32ShaVal[3] = 0x76543210;
            pstHashInfo->u32ShaVal[4] = 0xf0e1d2c3;
            Ret = DRV_Cipher_CalcHashInit(&stHashData);
            break;
        }
        case HI_UNF_CIPHER_HASH_TYPE_SHA256:
        case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256:
        {
            pstHashInfo->u32ShaLen = HASH256_SIGNATURE_SIZE;
            pstHashInfo->u32ShaVal[0] = 0x67e6096a;
            pstHashInfo->u32ShaVal[1] = 0x85ae67bb;
            pstHashInfo->u32ShaVal[2] = 0x72f36e3c;
            pstHashInfo->u32ShaVal[3] = 0x3af54fa5;
            pstHashInfo->u32ShaVal[4] = 0x7f520e51;
            pstHashInfo->u32ShaVal[5] = 0x8c68059b;
            pstHashInfo->u32ShaVal[6] = 0xabd9831f;
            pstHashInfo->u32ShaVal[7] = 0x19cde05b;
            Ret = DRV_Cipher_CalcHashInit(&stHashData);
            break;
        }
        case HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC:
        {
            memset(pstHashInfo, 0, sizeof(HASH_INFO_S));
            pstHashInfo->enShaType = pstHashAttr->eShaType;

            memset(&stCipherAtts, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
            stCipherAtts.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
            Ret = Cipher_CreateHandle(&hCipherHandle, &stCipherAtts);
            if (Ret != HI_SUCCESS)
            {
               HI_ERR_CIPHER("Fail to create Handle.\n");
               return HI_FAILURE;
            }
            memset(stCipherCtrl.u32IV, 0, sizeof(stCipherCtrl.u32IV));
            stCipherCtrl.bKeyByCA = HI_TRUE;
            stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            stCipherCtrl.stChangeFlags.bit1IV = 1;
            stCipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_IRDETO_HCA;
            Ret = Cipher_ConfigHandle(hCipherHandle, &stCipherCtrl);
            pstHashInfo->hHandle = hCipherHandle;
            break;
        }
        default:
        {
            HI_ERR_CIPHER("Invalid hash type 0x%x!\n", pstHashAttr->eShaType);
            return HI_FAILURE;
        }
    }

    if(Ret == HI_SUCCESS)
    {
        *pHashHandle = u32SoftId;
         pstHashInfo->bIsUsed = HI_TRUE;
    }
    else
    {
       HI_ERR_CIPHER("Fail to init Hash.\n");
    }

    return Ret;
}

HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtr)
{
    CIPHER_CheckHandle(hCipherHandle);

    return DRV_Cipher_GetHandleConfig(hCipherHandle, pstCtr);
}

/* New unf interface: HI_UNF_CIHPER_HashUpdate */
HI_S32 HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    static HI_U32 u32MmzPhyAddr = 0;
    static HI_BOOL bIsDstMmzInit = HI_FALSE;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];
    HI_U32 u32TotalSize, u32Copy, u32FirstPart;
    HI_U8 *pu8Buf;
    CIPHER_HASH_DATA_S stHashData;

    if(hHashHandle >= HASH_CHANNAL_MAX_NUM)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8InputData == NULL || u32InputDataLen == 0)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    if(pstHashInfo->enShaType == HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC)
    {
        if(!bIsDstMmzInit)
        {
            #if 0
            Ret = HI_MEM_Alloc(&u32MmzPhyAddr, MAX_DATA_LEN);
            if (Ret != HI_SUCCESS)
            {
                HI_ERR_CIPHER("malloc input memory failed!\n");
                return HI_FAILURE;
            }
            #else
            u32MmzPhyAddr = (HI_U32)devmemalign(16, MAX_DATA_LEN);
            if (u32MmzPhyAddr == 0)
            {
                HI_ERR_CIPHER("malloc input memory failed!\n");
                return HI_FAILURE;
            }
            #endif
            memset((void *)u32MmzPhyAddr, 0, MAX_DATA_LEN);

            bIsDstMmzInit = HI_TRUE;
        }

        Ret = HI_CIPHER_EncryptEx(pstHashInfo->hHandle, pu8InputData, u32InputDataLen, (HI_U8 *)u32MmzPhyAddr);
        memcpy(g_u8CbcMac, (HI_U8 *)(u32MmzPhyAddr + u32InputDataLen - 16), 16);
    }
    else
    {
        pstHashInfo->u32TotalDataLen += u32InputDataLen;
        u32TotalSize = pstHashInfo->u32LastBlockSize + u32InputDataLen;
        if( u32TotalSize < HASH_BLOCK_SIZE)
        {
            pu8Buf = (HI_U8*)pstHashInfo->u32LastBlock;
            memcpy(pu8Buf+pstHashInfo->u32LastBlockSize, pu8InputData, u32InputDataLen);
            pstHashInfo->u32LastBlockSize+=u32InputDataLen;
            return HI_SUCCESS;
        }
        else
        {
            memcpy(stHashData.u32ShaVal, pstHashInfo->u32ShaVal, pstHashInfo->u32ShaLen);
            stHashData.enShaType = pstHashInfo->enShaType;

            if (pstHashInfo->u32LastBlockSize > 0)
            {
                u32FirstPart = HASH_BLOCK_SIZE - pstHashInfo->u32LastBlockSize;
                pu8Buf = (HI_U8*)pstHashInfo->u32LastBlock;
                memcpy(pu8Buf+pstHashInfo->u32LastBlockSize, pu8InputData, u32FirstPart);
                stHashData.u32DataLen = HASH_BLOCK_SIZE;
                stHashData.u32DataPhy = (HI_U32)pstHashInfo->u32LastBlock;
                Ret = DRV_Cipher_CalcHashUpdate(&stHashData);
                if(Ret != HI_SUCCESS)
                {
                    HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
                    pstHashInfo->bIsUsed = HI_FALSE;
                    return Ret;
                }
            }
            else
            {
                u32FirstPart = 0;
            }

            u32TotalSize  = (u32InputDataLen - u32FirstPart) & (~0x3F);
            if (u32TotalSize > 0)
            {
                pu8Buf = pu8InputData + u32FirstPart;
                if ((((HI_U32)pu8Buf) & 0x03) == 0)
                {
                    stHashData.u32DataLen = u32TotalSize;
                    stHashData.u32DataPhy = (HI_U32)pu8Buf;
                    Ret = DRV_Cipher_CalcHashUpdate(&stHashData);
                    if(Ret != HI_SUCCESS)
                    {
                        HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
                        pstHashInfo->bIsUsed = HI_FALSE;
                        return Ret;
                    }
                }
                else
                {
                    u32Copy = 0;
                    while(u32Copy < u32TotalSize)
                    {
                        memcpy(pstHashInfo->u32LastBlock, pu8Buf, HASH_BLOCK_SIZE);
                        stHashData.u32DataLen = HASH_BLOCK_SIZE;
                        stHashData.u32DataPhy = (HI_U32)pstHashInfo->u32LastBlock;
                        Ret = DRV_Cipher_CalcHashUpdate(&stHashData);
                        if(Ret != HI_SUCCESS)
                        {
                            HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
                            pstHashInfo->bIsUsed = HI_FALSE;
                            return Ret;
                        }
                        u32Copy += HASH_BLOCK_SIZE;
                        pu8Buf += HASH_BLOCK_SIZE;
                    }
                }
            }

            memcpy(pstHashInfo->u32ShaVal, stHashData.u32ShaVal, pstHashInfo->u32ShaLen);

            /* save tail data */
            memset(pstHashInfo->u32LastBlock, 0, HASH_BLOCK_SIZE);
            pstHashInfo->u32LastBlockSize = u32InputDataLen - u32FirstPart - u32TotalSize;
            memcpy(pstHashInfo->u32LastBlock, pu8InputData + (u32InputDataLen - pstHashInfo->u32LastBlockSize),
                pstHashInfo->u32LastBlockSize);
        }
    }

    return HI_SUCCESS;
}

HI_S32 HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 Ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo = &g_stCipherHashData[hHashHandle];
    CIPHER_HASH_DATA_S stHashData;
    HI_U32 u32Tmp = 0;

    if(( NULL == pu8OutputHash ) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }
    if(pstHashInfo->enShaType == HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC)
    {
        memcpy(pu8OutputHash, g_u8CbcMac, 16);
        Cipher_DestroyHandle(pstHashInfo->hHandle);
    }
    else
    {
        u32Tmp = HashMsgPadding((HI_U8*)pstHashInfo->u32LastBlock, pstHashInfo->u32LastBlockSize, pstHashInfo->u32TotalDataLen);
        stHashData.enShaType = pstHashInfo->enShaType;
        stHashData.u32DataLen = u32Tmp;
        stHashData.u32DataPhy = (HI_U32)pstHashInfo->u32LastBlock;
        memcpy(stHashData.u32ShaVal, pstHashInfo->u32ShaVal, pstHashInfo->u32ShaLen);
        Ret = DRV_Cipher_CalcHashFinal(&stHashData);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
            pstHashInfo->bIsUsed = HI_FALSE;
            return Ret;
        }

        memset(pstHashInfo->u32LastBlock, 0, HASH_BLOCK_SIZE);
        pstHashInfo->u32LastBlockSize = 0;
        memcpy(pu8OutputHash, stHashData.u32ShaVal, pstHashInfo->u32ShaLen);

   }

   pstHashInfo->bIsUsed = HI_FALSE;

   return HI_SUCCESS;
}

#ifdef HASH_HAMC_SUPPORT
static HI_S32 HmacKeyInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_U8 au8Hmackey[HASH_BLOCK_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    HI_HANDLE hHash = 0;

    if((pstHashAttr == NULL)||(pstHashAttr->u8HMACKey == NULL)||(pstHashAttr->u32HMACKeyLen == 0))
    {
        HI_ERR_CIPHER("Invalid parameters.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*key length is less than 64bytes, copy directly*/
    if(pstHashAttr->u32HMACKeyLen <= HASH_BLOCK_SIZE)
    {
        memcpy(au8Hmackey, pstHashAttr->u8HMACKey, pstHashAttr->u32HMACKeyLen);
        return HI_SUCCESS;
    }

    /*key length more than 64bytes, calcute the hash result*/
    ret = HashInit(pstHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashInit failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = HashUpdate(hHash, pstHashAttr->u8HMACKey, pstHashAttr->u32HMACKeyLen);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashUpdate failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = HashFinal(hHash,au8Hmackey);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashFinal failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HmacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 key_pad[HASH_BLOCK_SIZE];
    HASH_INFO_S *pstHashInfo;
    HI_U32 i = 0;

    if( (NULL == pstHashAttr)
     || (NULL == pHashHandle)
     || (pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT)
     || (0 == pstHashAttr->u32HMACKeyLen))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    /* Init hmac key */
    memset(key_pad, 0, sizeof(key_pad));
    ret = HmacKeyInit(pstHashAttr, key_pad);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Hmac key initial failed!\n");
        return HI_FAILURE;
    }
    /* hash i_key_pad and message start */
    ret = HashInit(pstHashAttr, pHashHandle);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("hash i_key_pad and message start failed!\n");
        return HI_FAILURE;
    }
    pstHashInfo = (HASH_INFO_S *)&g_stCipherHashData[*pHashHandle];
    memcpy(pstHashInfo->u8Mac, key_pad, HASH_BLOCK_SIZE);
    /* generate i_key_pad */
    for(i=0; i < HASH_BLOCK_SIZE; i++)
    {
        key_pad[i] ^= 0x36;
    }

    /* hash i_key_pad update */
    ret = HashUpdate(*pHashHandle, key_pad, HASH_BLOCK_SIZE);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("hash i_key_pad and message update failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HmacUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("hmac message update failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HmacFinal(HI_HANDLE hHashHandle, HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    HASH_INFO_S *pstHashInfo;
    HI_HANDLE hHash = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 hash_sum_1[HASH256_SIGNATURE_SIZE];
    HI_U8 key_pad[HASH_BLOCK_SIZE];
    HI_U32 i;

    if (( NULL == pu8Output ) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid param input, hmac final failed!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    pstHashInfo = &g_stCipherHashData[hHashHandle];

    memset(&stHashAttr, 0, sizeof(stHashAttr));
    stHashAttr.eShaType = pstHashInfo->enShaType;
    memcpy(key_pad, pstHashInfo->u8Mac, HASH_BLOCK_SIZE);

    /* hash i_key_pad+message finished */
    ret = HashFinal(hHashHandle, hash_sum_1);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final i_key_pad+message failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* generate o_key_pad */
    for(i=0; i < HASH_BLOCK_SIZE; i++)
    {
        key_pad[i] ^= 0x5c;
    }

    /* hash o_key_pad+hash_sum_1 start */
    ret = HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Init o_key_pad+hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash o_key_pad */
    ret = HashUpdate(hHash, key_pad, HASH_BLOCK_SIZE);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update o_key_pad failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash hash_sum_1 */
    if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == stHashAttr.eShaType )
    {
        ret = HashUpdate(hHash, (HI_U8 *)hash_sum_1, HASH1_SIGNATURE_SIZE);
    }
    else
    {
        ret = HashUpdate(hHash, (HI_U8 *)hash_sum_1, HASH256_SIGNATURE_SIZE);
    }

    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash o_key_pad+hash_sum_1 finished */
    ret = HashFinal(hHash, pu8Output);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final o_key_pad+hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif

HI_S32 Cipher_HashInit(HI_UNF_CIPHER_HASH_ATTS_S * pstHashAttr, HI_HANDLE * pHashHandle)
{
    if ((HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashAttr->eShaType) )
    {
        return HashInit(pstHashAttr, pHashHandle);
    }
#ifdef HASH_HAMC_SUPPORT
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType))
    {
        return HmacInit(pstHashAttr, pHashHandle);
    }
#endif

    return HI_FAILURE;
}

HI_S32 Cipher_HashUpdate(HI_HANDLE hHashHandle, HI_U8 * pu8InputData, HI_U32 u32InputDataLen)
{
    HASH_INFO_S *pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    if((NULL == pu8InputData) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashInfo->enShaType ) )
    {
        return HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }
#ifdef HASH_HAMC_SUPPORT
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashInfo->enShaType))
    {
        return HmacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }
#endif
    return HI_FAILURE;
}

HI_S32 Cipher_HashFinal(HI_HANDLE hHashHandle, HI_U8 * pu8OutputHash)
{
    HASH_INFO_S *pstHashInfo = (HASH_INFO_S*)&g_stCipherHashData[hHashHandle];

    if((NULL == pu8OutputHash) || (hHashHandle >= HASH_CHANNAL_MAX_NUM))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashInfo->enShaType) )
    {
        return HashFinal(hHashHandle, pu8OutputHash);
    }
#ifdef HASH_HAMC_SUPPORT
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashInfo->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashInfo->enShaType))
    {
        return HmacFinal(hHashHandle, pu8OutputHash);
    }
#endif
    return HI_FAILURE;
}

HI_S32 Cipher_AuthCbcMac(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    return DRV_Cipher_AuthCbcMac(pu8RefCbcMac, u32AppLen);
}

HI_S32 Cipher_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData)
{
#ifdef RSA_HARDWARE_SUPPORT
    return DRV_CIPHER_CalcRsa(pCipherRsaData);
#else
    return DRV_CIPHER_CalcRsa_SW(pCipherRsaData);
#endif
}

//#endif
