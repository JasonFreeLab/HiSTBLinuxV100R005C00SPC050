/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_cipher.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#if defined (CHIP_TYPE_hi3716mv310)
#include "hi_boot_common.h"
#else
#include "hi_common.h"
#endif
#include "malloc.h"
#ifdef HI_MINIBOOT_SUPPORT
#include "string.h"
#include "stdio.h"
#else
#include "common.h"
#endif

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_cipher_define.h"
#include "hal_cipher.h"
#include "drv_cipher.h"
#include "hi_unf_cipher.h"

#define CI_BUF_LIST_SetIVFlag(u32Flags)
#define CI_BUF_LIST_SetEndFlag(u32Flags)

typedef struct hiCIPHER_IV_VALUE_S
{
    HI_U32    u32PhyAddr;
    HI_U32   *pu32VirAddr;
    //HI_U8   au8IVValue[CI_IV_SIZE];
} CIPHER_IV_VALUE_S;


/*
-----------------------------------------------------------
0 | input buf list Node(16Byte) | ...  * CIPHER_MAX_LIST_NUM  | = 16*CIPHER_MAX_LIST_NUM
-----------------------------------------------------------
  | output buf list Node(16Byte)| ...  * CIPHER_MAX_LIST_NUM  |
-----------------------------------------------------------
  | IV (16Byte)                 | ...  * CIPHER_MAX_LIST_NUM  |
-----------------------------------------------------------
... * 7 Channels


*/

typedef struct hiCIPHER_PKGN_MNG_S
{
    HI_U32              u32TotalPkg;  /*  */
    HI_U32              u32CurrentPtr;
    HI_U32              u32BusyCnt;
    HI_U32              u32FreeCnt;
} CIPHER_PKGN_MNG_S;

typedef struct hiCIPHER_PKG1_MNG_S
{
    HI_U32              au32Data[4];
} CIPHER_PKG1_MNG_S;

typedef union hiCIPHER_DATA_MNG_U
{
    CIPHER_PKGN_MNG_S  stPkgNMng;
    CIPHER_PKG1_MNG_S  stPkg1Mng;
}CIPHER_DATA_MNG_U;

typedef struct hiCIPHER_CHAN_S
{
    HI_U32                  chnId;
    CI_BUF_LIST_ENTRY_S     *pstInBuf;
    CI_BUF_LIST_ENTRY_S     *pstOutBuf;
    CIPHER_IV_VALUE_S       astCipherIVValue[CIPHER_MAX_LIST_NUM]; /*  */
    HI_U32                  au32WitchSoftChn[CIPHER_MAX_LIST_NUM];
    HI_U32                  au32CallBackArg[CIPHER_MAX_LIST_NUM];
    HI_BOOL                 bNeedCallback[CIPHER_MAX_LIST_NUM];
    CIPHER_DATA_MNG_U       unInData;
    CIPHER_DATA_MNG_U       unOutData;
} CIPHER_CHAN_S;

typedef struct hiCIPHER_SOFTCHAN_S
{
    HI_BOOL               bOpen;
    HI_U32                u32HardWareChn;

    HI_UNF_CIPHER_CTRL_S  stCtrl;

    HI_BOOL               bIVChange;
    HI_BOOL               bKeyChange;
    HI_U32                u32LastPkg;     /* save which pkg's IV we should use for next pkg */
    HI_BOOL               bDecrypt;       /* hi_false: encrypt */

    HI_U32                u32PrivateData;
    funcCipherCallback    pfnCallBack;

} CIPHER_SOFTCHAN_S;

/********************** Global Variable declaration **************************/
extern HI_U32 g_u32CipherStartCase;


typedef struct hiCIPHER_COMM_S
{
    MMZ_BUFFER_S        stPhyBuf;
} CIPHER_COMM_S;
extern HI_U32 g_u32CipherEndCase;

/* */
static CIPHER_COMM_S g_stCipherComm;
static CIPHER_CHAN_S g_stCipherChans[CIPHER_CHAN_NUM];
static CIPHER_SOFTCHAN_S g_stCipherSoftChans[CIPHER_SOFT_CHAN_NUM];

extern HI_VOID HAL_Cipher_ClearCbcMacVerifyFlag(HI_VOID);
extern HI_VOID HAL_Cipher_AuthCbcMac(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen);
HI_S32 DRV_CipherInitHardWareChn(HI_U32 chnId )
{
    HI_U32        i;
    //CIPHER_CHAN_S *pChan;

    //pChan = &g_stCipherChans[chnId];

    HAL_Cipher_SetInBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetInBufCnt(chnId, 0);
//    HAL_Cipher_SetInBufEmpty(chnId, CIPHER_MAX_LIST_NUM);

    HAL_Cipher_SetOutBufNum(chnId, CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufCnt(chnId, CIPHER_MAX_LIST_NUM);
//    HAL_Cipher_SetOutBufFull(chnId, 0);

    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_OUT_BUF, 0);
    HAL_Cipher_SetAGEThreshold(chnId, CIPHER_INT_TYPE_IN_BUF, 0);

    HAL_Cipher_DisableInt(chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);

    //HAL_Cipher_Config(chnId, 0);

    for (i = 0; i < CIPHER_MAX_LIST_NUM; i++)
    {
        ;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CipherDeInitHardWareChn(HI_U32 chnId)
{
/*
    HAL_Cipher_SetInBufNum(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetInBufCnt(0);
    HAL_Cipher_SetInBufEmpty(CIPHER_MAX_LIST_NUM);

    HAL_Cipher_SetOutBufNum(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufCnt(CIPHER_MAX_LIST_NUM);
    HAL_Cipher_SetOutBufFull(0);
*/

    HAL_Cipher_DisableInt(chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);
    return HI_SUCCESS;
}
/*
set interrupt threshold level and enable it, and flag soft channel opened
*/
HI_S32 DRV_Cipher_OpenChn(HI_U32 softChnId)
{
    HI_S32 ret = 0;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pSoftChan->u32HardWareChn = softChnId;

    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, CIPHER_DEFAULT_INT_NUM);
    //ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF | CIPHER_INT_TYPE_IN_BUF);
    ret = HAL_Cipher_EnableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF);

    pSoftChan->bOpen = HI_TRUE;
    return ret;
}

/*
flag soft channel closed
*/
HI_S32 DRV_Cipher_CloseChn(HI_U32 softChnId)
{
    HI_S32 ret = HI_SUCCESS;
    //CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    //pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    pSoftChan->bOpen = HI_FALSE;

    HAL_Cipher_ClearCbcMacVerifyFlag(); //clear irdeto_verify_flag of register HL_APP_CBC_CTRL anyway

//    ret = HAL_Cipher_DisableInt(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF);
    return ret;
}

HI_S32 DRV_Cipher_ConfigChn(HI_U32 softChnId,  HI_UNF_CIPHER_CTRL_S *pConfig,
                            funcCipherCallback fnCallBack)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bDecrypt = HI_FALSE;
    HI_U32 hardWareChn;
    HI_BOOL bIVSet;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];
    pSoftChan->pfnCallBack = fnCallBack;
    bIVSet = (pConfig->stChangeFlags.bit1IV & 0x1) ? HI_TRUE : HI_FALSE;

    ret = HAL_Cipher_Config(pChan->chnId, bDecrypt, bIVSet, pConfig);

    pSoftChan->bIVChange = bIVSet;
    pSoftChan->bKeyChange = HI_TRUE;

    memcpy(&(pSoftChan->stCtrl), pConfig, sizeof(HI_UNF_CIPHER_CTRL_S));

    /* set Key */
    if (pSoftChan->bKeyChange &&  (HI_TRUE == pConfig->bKeyByCA))
    {
        /* Used for copy protection mode */
        if( 0 == hardWareChn)
        {
            ret = HAL_CIPHER_LoadSTBRootKey(0);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("Load STB root key failed!\n");
                return ret;
            }
        }
        else
        {
            ret = HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
            if (HI_SUCCESS != ret)
            {
                return ret;
            }
        }
        pSoftChan->bKeyChange = HI_FALSE;
    }

    return ret;
}

/*
*/
HI_S32 DRV_CipherStartSinglePkgChn(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process)
{
    HI_U32 ret;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    HAL_Cipher_Config(0, pBuf2Process->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));

    HAL_Cipher_SetInIV(0, &(pSoftChan->stCtrl));

    HAL_Cipher_SetKey(0, &(pSoftChan->stCtrl));
    HAL_Cipher_SetDataSinglePkg(pBuf2Process);

    HAL_Cipher_StartSinglePkg(pChan->chnId);
    ret = HAL_Cipher_WaitIdle();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    HAL_Cipher_ReadDataSinglePkg(pBuf2Process->u32DataPkg);

    return HI_SUCCESS;
}

/*
*/
HI_S32 DRV_CipherStartMultiPkgChn(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process, HI_U32 callBackArg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 hardWareChn;
    HI_U32 BusyCnt;
    HI_U32 currentPtr;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[hardWareChn];


    HAL_Cipher_GetInBufCnt(hardWareChn, &BusyCnt);

    pChan->unInData.stPkgNMng.u32BusyCnt = BusyCnt;
    currentPtr = pChan->unInData.stPkgNMng.u32CurrentPtr;

    pInBuf = pChan->pstInBuf + currentPtr;
    pOutBuf = pChan->pstOutBuf + currentPtr;

    if (BusyCnt < CIPHER_MAX_LIST_NUM) /* */
    {
        /* set addr */
        pInBuf->u32DataAddr = pBuf2Process->u32src;
        pInBuf->U32DataLen = pBuf2Process->u32length;

        pOutBuf->u32DataAddr = pBuf2Process->u32dest;
        pOutBuf->U32DataLen = pBuf2Process->u32length;

        /* set IV */
        if (pSoftChan->bIVChange)
        {
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 1       /* for 1 pkg task,  save IV for next pkg unless user config the handle again */
            pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#else
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
            pChan->astCipherIVValue[pSoftChan->u32LastPkg].pu32VirAddr, CI_IV_SIZE);
            pInBuf->u32IVStartAddr = pChan->astCipherIVValue[currentPtr].u32PhyAddr;
            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#endif
        }

        /* set Key */
        if (pSoftChan->bKeyChange)
        {
            ret = HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
            if (HI_SUCCESS != ret)
            {
                return ret;
            }

            pSoftChan->bKeyChange = HI_FALSE;
        }
        else
        {
            ;
        }

        /* just set each node to End_of_list <--- changed by q46153, 20111108, no need,  we think the task is NOT over */
        //pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
        //pOutBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);

        //ret = HAL_Cipher_Config(hardWareChn, pSoftChan->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));
        ret = HAL_Cipher_Config(hardWareChn, pBuf2Process->bDecrypt, pSoftChan->bIVChange, &(pSoftChan->stCtrl));
        pSoftChan->bIVChange = HI_FALSE;

        pChan->au32WitchSoftChn[currentPtr] = softChnId;
        pChan->au32CallBackArg[currentPtr] = callBackArg;
        pSoftChan->u32PrivateData = callBackArg;
        pChan->bNeedCallback[currentPtr] = HI_TRUE;

        currentPtr++;
        if (currentPtr >=  CIPHER_MAX_LIST_NUM)
        {
            currentPtr = 0;
        }

        /* save list Node */
        pChan->unInData.stPkgNMng.u32CurrentPtr = currentPtr;
        pChan->unInData.stPkgNMng.u32TotalPkg++;
        pChan->unOutData.stPkgNMng.u32TotalPkg++;

        HAL_Cipher_GetOutBufCnt(hardWareChn, &BusyCnt);
#if 0
        HI_ERR_CIPHER("%s %#x->%#x, LEN:%#x\n", pBuf2Process->bDecrypt ? "Dec" : "ENC",
                pBuf2Process->u32src, pBuf2Process->u32dest,
                pBuf2Process->u32length );
#endif
        HAL_Cipher_SetInBufCnt(hardWareChn, 1); /* +1 */

    }
    else
    {
        return HI_FAILURE;
    }

    return ret;
}


HI_S32 DRV_Cipher_CreatMultiPkgTask(HI_U32 softChnId, HI_DRV_CIPHER_DATA_INFO_S *pBuf2Process, HI_U32 pkgNum, HI_U32 callBackArg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 hardWareChn;
    HI_U32 BusyCnt, i;
    HI_U32 currentPtr;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;
    HI_DRV_CIPHER_DATA_INFO_S *pTmpDataPkg = pBuf2Process;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    hardWareChn = pSoftChan->u32HardWareChn;
    pChan = &g_stCipherChans[hardWareChn];


    HAL_Cipher_GetInBufCnt(hardWareChn, &BusyCnt);

    pChan->unInData.stPkgNMng.u32BusyCnt = BusyCnt;

    if (BusyCnt + pkgNum > CIPHER_MAX_LIST_NUM) /* */
    {
         HI_ERR_CIPHER("%s: pkg want to do: %u, free pkg num:%u.\n", pBuf2Process->bDecrypt ? "Dec" : "ENC",
                pkgNum, CIPHER_MAX_LIST_NUM - BusyCnt);
         return HI_ERR_CIPHER_BUSY;
    }


    /* set Key */
    if (pSoftChan->bKeyChange)
    {
        HAL_Cipher_SetKey(hardWareChn, &(pSoftChan->stCtrl));
        pSoftChan->bKeyChange = HI_FALSE;
    }
    else
    {
        ;
    }


    currentPtr = pChan->unInData.stPkgNMng.u32CurrentPtr;

    for (i = 0; i < pkgNum; i++)
    {
        pTmpDataPkg = pBuf2Process + i;
        pInBuf = pChan->pstInBuf + currentPtr;
        pOutBuf = pChan->pstOutBuf + currentPtr;


        /* set addr */
        pInBuf->u32DataAddr = pTmpDataPkg->u32src;
        pInBuf->U32DataLen = pTmpDataPkg->u32length;

        pOutBuf->u32DataAddr = pTmpDataPkg->u32dest;
        pOutBuf->U32DataLen = pTmpDataPkg->u32length;

        /* set IV */
        if (pSoftChan->bIVChange)
        {
            memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
                pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

            pInBuf->u32IVStartAddr
                = pChan->astCipherIVValue[currentPtr].u32PhyAddr;

            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
        }
        else
        {
#if 0
			pInBuf->u32Flags &= ~(1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#else  /* for multi pkg task, reset IV(use the user configed IV ) each time. */
			memcpy(pChan->astCipherIVValue[currentPtr].pu32VirAddr,
				pSoftChan->stCtrl.u32IV, CI_IV_SIZE);

			pInBuf->u32IVStartAddr
				= pChan->astCipherIVValue[currentPtr].u32PhyAddr;

			pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_IVSET_BIT);
#endif

        }


        pChan->au32WitchSoftChn[currentPtr] = softChnId;
        pChan->au32CallBackArg[currentPtr] = callBackArg;
        pSoftChan->u32PrivateData = callBackArg;
        if ((i + 1) == pkgNum)
        {
            pChan->bNeedCallback[currentPtr] = HI_TRUE ;

            /* just set each node to End_of_list, <--- changed by q46153, 20111108, only the last pkg need this. */
            pInBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
            pOutBuf->u32Flags |= (1 << CI_BUF_LIST_FLAG_EOL_BIT);
        }
        else
        {
            pChan->bNeedCallback[currentPtr] = HI_FALSE ;
        }


        currentPtr++;
        if (currentPtr >=  CIPHER_MAX_LIST_NUM)
        {
            currentPtr = 0;
        }

        /* save list Node */
        pChan->unInData.stPkgNMng.u32CurrentPtr = currentPtr;
        pChan->unInData.stPkgNMng.u32TotalPkg++;
        pChan->unOutData.stPkgNMng.u32TotalPkg++;
    }


    ret = HAL_Cipher_Config(hardWareChn, pTmpDataPkg->bDecrypt,
                            pSoftChan->bIVChange, &(pSoftChan->stCtrl));
    if(HI_SUCCESS != ret)
    {
        return ret;
    }
    pSoftChan->bIVChange = HI_FALSE;

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, pkgNum);

    HAL_Cipher_GetOutBufCnt(hardWareChn, &BusyCnt);
    HAL_Cipher_SetInBufCnt(hardWareChn, pkgNum); /* commit task */

    return HI_SUCCESS;
}

/*
*/
HI_S32 DRV_Cipher_CreatTask(HI_U32 softChnId, HI_DRV_CIPHER_TASK_S *pTask, HI_U32 *pKey, HI_U32 *pIV)
{
    HI_S32 ret;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    pSoftChan = &g_stCipherSoftChans[softChnId];
    pChan = &g_stCipherChans[pSoftChan->u32HardWareChn];

    if (pKey)
    {
        pSoftChan->bKeyChange = HI_TRUE;
        memcpy(pSoftChan->stCtrl.u32Key, pKey, CI_KEY_SIZE);
    }

    if (pIV)
    {
        pSoftChan->bIVChange = HI_TRUE;
        memcpy(pSoftChan->stCtrl.u32IV, pIV, CI_IV_SIZE);
    }

    HAL_Cipher_SetIntThreshold(pChan->chnId, CIPHER_INT_TYPE_OUT_BUF, 1);

    if (CIPHER_PKGx1_CHAN == pSoftChan->u32HardWareChn)
    {
        ret = DRV_CipherStartSinglePkgChn(softChnId, &(pTask->stData2Process));
    }
    else
    {
        ret = DRV_CipherStartMultiPkgChn(softChnId, &(pTask->stData2Process), pTask->u32CallBackArg);
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("can't create task, ERR=%#x.\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CipherDataDoneSinglePkg(HI_U32 chnId)
{
    //CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;

    //pChan = &g_stCipherChans[chnId];
    HI_ERR_CIPHER("Data DONE, hwChn:%d\n", chnId);
    pSoftChan = &g_stCipherSoftChans[chnId];

    if (pSoftChan->pfnCallBack)
    {
        pSoftChan->pfnCallBack(pSoftChan->u32PrivateData);
    }
    return HI_SUCCESS;
}

HI_S32 DRV_CipherDataDoneMultiPkg(HI_U32 chnId)
{
    HI_S32 ret;
    HI_U32 currentPtr;
    HI_U32 softChnId;
    HI_U32 fullCnt;
    HI_U32 i, idx;
    CIPHER_CHAN_S *pChan;
    CIPHER_SOFTCHAN_S *pSoftChan;
    CI_BUF_LIST_ENTRY_S *pInBuf;
    CI_BUF_LIST_ENTRY_S *pOutBuf;

    pChan = &g_stCipherChans[chnId];
//    HI_ERR_CIPHER("Data DONE, hwChn:%d\n", chnId);

    currentPtr = pChan->unOutData.stPkgNMng.u32CurrentPtr;

//    HI_ERR_CIPHER("Data DONE, hwChn:%u, currentPtr=%u\n", chnId, currentPtr);

    /* get the finished output data buffer count */
    ret = HAL_Cipher_GetOutBufFull(chnId, &fullCnt);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
    idx = currentPtr;

    if(idx >= CIPHER_MAX_LIST_NUM)
    {
        HI_ERR_CIPHER("idx error: idx=%u, chnId=%d \n", idx, chnId);
    }

    if (fullCnt > 0) /* have list entry */
    {
        for (i = 0; i < fullCnt; i++)
        {
//            idx = currentPtr;

            softChnId = pChan->au32WitchSoftChn[idx];
            pChan->au32WitchSoftChn[idx] = CIPHER_INVALID_CHN;

            pSoftChan = &g_stCipherSoftChans[softChnId];
            pSoftChan->u32LastPkg = idx;
//            HI_ERR_CIPHER("softChnId=%d, idx=%u, needCallback:%d\n", softChnId, idx, pChan->bNeedCallback[idx]);
            if (pSoftChan->pfnCallBack && pChan->bNeedCallback[idx])
            {
//                HI_ERR_CIPHER("CallBack function\n");
                pSoftChan->pfnCallBack(pSoftChan->u32PrivateData);
            }

            pInBuf = pChan->pstInBuf + idx;  /* reset the flag of each pkg */
            pInBuf->u32Flags = 0;

            pOutBuf = pChan->pstOutBuf + idx; /* reset the flag of each pkg */
            pOutBuf->u32Flags = 0;

            idx++;
            if (idx >= CIPHER_MAX_LIST_NUM)
            {
                idx = 0;
            }
        }

        pChan->unOutData.stPkgNMng.u32CurrentPtr = idx;
        HAL_Cipher_SetInBufEmpty(chnId, fullCnt);  /* -  */
        HAL_Cipher_SetOutBufFull(chnId, fullCnt);  /* -  */
        HAL_Cipher_SetOutBufCnt(chnId, fullCnt);   /* +  */
    }
    else
    {
        HI_U32 regValue = 0xabcd;

        HI_ERR_CIPHER("Data done, but fullCnt=0, chn%d\n", chnId);

        HAL_Cipher_GetIntState(&regValue);
        HI_ERR_CIPHER("INTSt:%#x\n", regValue);

        HAL_Cipher_GetIntEnState(&regValue);
        HI_ERR_CIPHER("INTEnSt:%#x\n", regValue);

        HAL_Cipher_GetRawIntState(&regValue);
        HI_ERR_CIPHER("INTRawSt:%#x\n", regValue);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_Cipher_Stat(HI_U32 chnId, HI_U32 *pCipherStat)
{
    if (NULL == pCipherStat)
    {
        HI_ERR_CIPHER("Parameters Error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HAL_Cipher_Stat(chnId, pCipherStat);
}

#ifdef RSA_HARDWARE_SUPPORT

#define CRC16_POLYNOMIAL 0x1021

static HI_U16 s_CrcTable[256];

HI_VOID  DRV_RSA_Crc16Init(HI_VOID)
{
    HI_U16 nRemainder;
    HI_U16 n, m;
    HI_U16  *pulTable = s_CrcTable;

    for(n = 0; n < 256; n ++)
    {
        nRemainder = (HI_U16)n << 8;
        for(m = 8; m > 0; m --)
        {
            if(nRemainder & 0x8000)
            {
                nRemainder = (nRemainder << 1) ^ CRC16_POLYNOMIAL;
            }
            else
            {
                nRemainder = (nRemainder << 1);
            }
        }
        *(pulTable + n) = nRemainder;
    }
}

#endif

HI_S32 DRV_Cipher_Init(HI_VOID)
{
    HI_U32 i,j, hwChnId;
    //HI_S32 ret;
    HI_U32 bufSizeChn = 0; /* all the buffer list size, included data buffer size and IV buffer size */
    HI_U32 databufSizeChn = 0; /* max list number data buffer size */
    HI_U32 ivbufSizeChn = 0; /* all the list IV size */
    HI_U32 bufSizeTotal = 0; /* all the channel buffer size */
    MMZ_BUFFER_S   cipherListBuf;
    CIPHER_CHAN_S *pChan;

    memset(&g_stCipherComm, 0, sizeof(g_stCipherComm));
    memset(&g_stCipherChans, 0, sizeof(g_stCipherChans));
    memset(&g_stCipherSoftChans, 0, sizeof(g_stCipherSoftChans));

/*
==========================channel-1=============================
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |inBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |outBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |keyBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
=============================================================
...
...
...
==========================channel-7=============================
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |inBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |outBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
*| +++++++++++++++++++                               +++++++++++++++++++  |
*| +byte1|byte2|byte3|byte4 +       ... ...                 +byte1|byte2|byte3|byte4 +  |keyBuf
*| +++++++++++++++++++                               +++++++++++++++++++  |
*|             list-1                              ... ...                              list-128(MAX_LIST)    |
*----------------------------------------------------------------------
=============================================================
*/

    databufSizeChn = sizeof(CI_BUF_LIST_ENTRY_S) * CIPHER_MAX_LIST_NUM;
    ivbufSizeChn = CI_IV_SIZE * CIPHER_MAX_LIST_NUM;
    bufSizeChn = (databufSizeChn * 2) + ivbufSizeChn;/* inBuf + outBuf + keyBuf */
    bufSizeTotal = bufSizeChn * (CIPHER_PKGxN_CHAN_MAX - CIPHER_PKGxN_CHAN_MIN + 1) ; /* only 7 channels need buf */

    HAL_Cipher_Init();
    HAL_Cipher_HashSoftReset();
#ifdef RSA_HARDWARE_SUPPORT
    HAL_RSA_Reset();
    DRV_RSA_Crc16Init();
#endif
    HAL_Cipher_DisableAllInt();

    /* allocate 7 channels size */
    cipherListBuf.u32Size = bufSizeTotal;
    cipherListBuf.u32StartPhyAddr = (HI_U32)malloc(cipherListBuf.u32Size);
	if(0 == cipherListBuf.u32StartPhyAddr)
	{
		HI_ERR_CIPHER("malloc cipherListBuf.u32StartPhyAddr failed.\n");
		return HI_FAILURE;
	}
    cipherListBuf.u32StartVirAddr = cipherListBuf.u32StartPhyAddr;

    memset((void*)(cipherListBuf.u32StartVirAddr), 0, cipherListBuf.u32Size);

    /* save the whole memory info, included physical address, virtual address and their size */
    memcpy(&(g_stCipherComm.stPhyBuf), &(cipherListBuf), sizeof(g_stCipherComm.stPhyBuf));

    /* assign hardware channel ID from 0 to 7 */
    for (i = 0; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        pChan = &g_stCipherChans[i];
        pChan->chnId = i;
    }

/*
channel layout
==============================================================
|
|
==============================================================
/\                                     /\                                      /\
 |              IV buf                  |             IN buf                    |             OUT buf
startPhyAddr
==============================================================
|
|
==============================================================
/\                                     /\                                      /\
 |              IV buf                  |             IN buf                    |             OUT buf
 startVirAddr
*/
    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        /* config channel from 1 to 7 */
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];

        pChan->astCipherIVValue[0].u32PhyAddr
            = cipherListBuf.u32StartPhyAddr + (i * bufSizeChn);
        pChan->astCipherIVValue[0].pu32VirAddr
            = (HI_U32*)(cipherListBuf.u32StartVirAddr + (i * bufSizeChn));

        for (j = 1; j < CIPHER_MAX_LIST_NUM; j++)
        {
            pChan->astCipherIVValue[j].u32PhyAddr
                = pChan->astCipherIVValue[0].u32PhyAddr + (CI_IV_SIZE * j);
            pChan->astCipherIVValue[j].pu32VirAddr
                = (HI_U32*)(((HI_U32)pChan->astCipherIVValue[0].pu32VirAddr) + (CI_IV_SIZE * j));

            pChan->bNeedCallback[j] = HI_FALSE;
        }

        pChan->pstInBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->astCipherIVValue[0].pu32VirAddr) + ivbufSizeChn);
        pChan->pstOutBuf = (CI_BUF_LIST_ENTRY_S*)((HI_U32)(pChan->pstInBuf) + databufSizeChn);

        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_IN,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn);
        HAL_Cipher_SetBufAddr(hwChnId, CIPHER_BUF_TYPE_OUT,
            pChan->astCipherIVValue[0].u32PhyAddr + ivbufSizeChn + databufSizeChn);

        DRV_CipherInitHardWareChn(hwChnId);


    }

    /* debug info */
    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        pChan = &g_stCipherChans[hwChnId];
    }

#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100) \
	|| defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100) \
	|| defined (CHIP_TYPE_hi3798cv200_a) || defined (CHIP_TYPE_hi3798cv200_b) \
	|| defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) \
	|| defined (CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
	|| defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3798mv300)
	HAL_Cipher_EnableAllSecChn();
#endif
    return HI_SUCCESS;
}

HI_VOID DRV_Cipher_DeInit(HI_VOID)
{
    HI_U32 i, hwChnId;
//    HI_U32  REG_SYS_BASE_ADDR_VIRT = 0;

    HAL_Cipher_DisableAllInt();
    HAL_Cipher_ClrIntState(0xffffffff);

    for (i = 0; i < CIPHER_PKGxN_CHAN_MAX; i++)
    {
        hwChnId = i+CIPHER_PKGxN_CHAN_MIN;
        DRV_CipherDeInitHardWareChn(hwChnId);
    }

    HAL_Cipher_DeInit();
    if (HI_NULL != g_stCipherComm.stPhyBuf.u32StartPhyAddr)
    {
        free((void *)g_stCipherComm.stPhyBuf.u32StartPhyAddr);
        g_stCipherComm.stPhyBuf.u32StartPhyAddr = 0;
    }

    return;
}


//#ifndef HI_MINIBOOT_SUPPORT

HI_S32 DRV_Cipher_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;


#ifndef CIPHER_MHASH_SUPPORT
    ret = HAL_Cipher_CalcHashInit(pCipherHashData);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher hash init failed!\n");
        return HI_FAILURE;
    }
#endif

    return ret;
}

HI_S32 DRV_Cipher_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }
#ifdef CIPHER_MHASH_SUPPORT
    ret = HAL_Cipher_CalcHashInit(pCipherHashData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("HAL_Hash_Init failed! ret = 0x%08x\n", ret);
        return HI_FAILURE;
    }
    ret = HAL_Cipher_CalcHashUpdate(pCipherHashData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("HAL_Hash_Update failed! ret = 0x%08x\n", ret);
        return HI_FAILURE;
    }
    ret = HAL_Cipher_CalcHashFinal(pCipherHashData);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("HAL_Hash_Final failed! ret = 0x%08x\n", ret);
        return HI_FAILURE;
    }
#else
    ret = HAL_Cipher_CalcHashUpdate(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash update failed!\n");
        return HI_FAILURE;
    }
#endif
    return HI_SUCCESS;

}

HI_S32 DRV_Cipher_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    ret = DRV_Cipher_CalcHashUpdate(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash final failed!\n");
        return HI_FAILURE;
    }

#ifndef CIPHER_MHASH_SUPPORT
    ret = HAL_Cipher_CalcHashFinal(pCipherHashData);
    if(HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("Cipher hash final failed!\n");
        return HI_FAILURE;
    }
#endif

    return ret;
}


HI_S32 DRV_Cipher_AuthCbcMac(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    if(NULL == pu8RefCbcMac)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    HAL_Cipher_AuthCbcMac(pu8RefCbcMac, u32AppLen);
    return HI_SUCCESS;
}

HI_S32 DRV_Cipher_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtr)
{
    CIPHER_SOFTCHAN_S *pSoftChan = NULL;
    HI_U32 u32SoftChanId = 0;

    if(pstCtr == NULL)
    {
        HI_ERR_CIPHER("Error! NULL pointer!\n");
        return HI_FAILURE;
    }

    u32SoftChanId = HI_HANDLE_GET_CHNID(hCipherHandle);
    pSoftChan = &g_stCipherSoftChans[u32SoftChanId];
    memcpy(pstCtr, &(pSoftChan->stCtrl), sizeof(HI_UNF_CIPHER_CTRL_S));

    return HI_SUCCESS;
}

#ifdef RSA_HARDWARE_SUPPORT

static HI_U16 DRV_RSA_CRC16_BLOCK(HI_U16 crc, HI_U8 block[8], HI_U8 u32Rnadom[8])
{
    HI_U8 i, j;
    HI_U8 val;

    for(i=0; i<2; i++)
    {
        for(j=0; j<4; j++)
        {
            val = block[i*4+3-j] ^ u32Rnadom[i*4+3-j];
            crc = (crc<<8) ^ s_CrcTable[((crc>>8) ^ val) & 0xFF];
        }
    }

    return crc;
}

static HI_U16 DRV_RSA_KeyCRC(HI_U8 *pu8N, HI_U8 *pu8K, HI_U32 u32Klen, HI_U32 u32Rnadom[2])
{
    HI_U32 i;
    HI_U16 crc = 0;

    for(i=0; i<u32Klen; i+=8)
    {
        crc = DRV_RSA_CRC16_BLOCK(crc, pu8N+i, (HI_U8*)u32Rnadom);
    }
    for(i=0; i<u32Klen; i+=8)
    {
        crc = DRV_RSA_CRC16_BLOCK(crc, pu8K+i, (HI_U8*)u32Rnadom);
    }

    return crc;
}

HI_S32 DRV_CIPHER_CheckRsaData(HI_U8 *N, HI_U8 *E, HI_U8 *MC, HI_U32 u32Len)
{
    HI_U32 i;

    /*MC > 0*/
    for(i=0; i<u32Len; i++)
    {
        if(MC[i] > 0)
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA M/C is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*MC < N*/
    for(i=0; i<u32Len; i++)
    {
        if(MC[i] < N[i])
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA M/C is larger than N, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*E > 1*/
    for(i=0; i<u32Len; i++)
    {
        if(E[i] > 0)
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA D/E is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

//    HI_PRINT_HEX("N", N, u32Len);
//    HI_PRINT_HEX("K", E, u32Len);

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_ClearRsaRam(HI_U32 u32StartCode)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }
    HAL_RSA_ClearRam();
    HAL_RSA_Start(u32StartCode);
    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_RSA_RandMaskEnable(CIPHER_RSA_DATA_S *pCipherRsaData, HI_U32 u32KeyLen, HI_U32 u32Rnadom[2], HI_U32 u32EnableCrcCheck)
{
    HI_U16 u16CrC;

    if(u32EnableCrcCheck)
    {
        HAL_Cipher_GetRandomNumber(&u32Rnadom[0]);
        HAL_Cipher_GetRandomNumber(&u32Rnadom[1]);

        u16CrC = DRV_RSA_KeyCRC(pCipherRsaData->pu8N, pCipherRsaData->pu8K, u32KeyLen, u32Rnadom);
        HI_ERR_CIPHER("CRC16: 0x%x\n", u16CrC);
        HAL_RSA_SetRandom(u32Rnadom);
        HAL_RSA_SetCRC(u16CrC);
        HI_ERR_CIPHER("-1--u32Rnadom[0]=0x%x, u32Rnadom[1]=0x%x\n", u32Rnadom[0],u32Rnadom[1]);
    }
    else
    {
        u32Rnadom[0] = 0;
        u32Rnadom[1] = 0;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ErrorCode;
    HI_U32 u32KeyLen;
    CIPHER_RSA_KEY_WIDTH_E enKeyWidth;
    HI_U32 u32Rnadom[2] = {0,0};
    HI_U32 u32StartCode = 0x00;
    HI_BOOL u32EnableCrcCheck = HI_FALSE;
    HI_CHIP_TYPE_E penChipType;
    HI_CHIP_VERSION_E penChipID;
    static HI_U8  N[CIPHER_MAX_RSA_KEY_LEN];
    static HI_U8  K[CIPHER_MAX_RSA_KEY_LEN];
    static HI_U8  M[CIPHER_MAX_RSA_KEY_LEN];
    HI_U8 *p;
    CIPHER_RSA_DATA_S stCipherRsaData;

    if ((pCipherRsaData->pu8Input == HI_NULL) ||(pCipherRsaData->pu8Output== HI_NULL)
        || (pCipherRsaData->pu8N == HI_NULL) || (pCipherRsaData->pu8K == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pCipherRsaData->u16NLen == 0) || (pCipherRsaData->u16KLen == 0))
    {
        HI_ERR_CIPHER("RSA K size is zero.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pCipherRsaData->u32DataLen != pCipherRsaData->u16NLen)
    {
        HI_ERR_CIPHER("Error, DataLen != u16NLen!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pCipherRsaData->u16NLen <= 128)
    {
        u32KeyLen = 128;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_1K;
    }
    else if (pCipherRsaData->u16NLen <= 256)
    {
        u32KeyLen = 256;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_2K;
    }
    else if (pCipherRsaData->u16NLen <= 512)
    {
        u32KeyLen = 512;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_4K;
    }
    else
    {
        HI_ERR_CIPHER("u16NLen(0x%x) is invalid\n", pCipherRsaData->u16NLen);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    memset(N, 0, sizeof(N));
    memset(K, 0, sizeof(K));
    memset(M, 0, sizeof(M));

     /*if dataLen < u32KeyLen, padding 0 before data*/
    p = N + (u32KeyLen - pCipherRsaData->u16NLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8N, pCipherRsaData->u16NLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }
    p = K + (u32KeyLen - pCipherRsaData->u16KLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8K, pCipherRsaData->u16KLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }
    p = M + (u32KeyLen - pCipherRsaData->u32DataLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8Input, pCipherRsaData->u32DataLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }

    memset(&stCipherRsaData, 0, sizeof(stCipherRsaData));
    stCipherRsaData.pu8N = N;
    stCipherRsaData.pu8K = K;
    stCipherRsaData.pu8Input = M;
    stCipherRsaData.u16NLen = u32KeyLen;
    stCipherRsaData.u16KLen = u32KeyLen;
    stCipherRsaData.u32DataLen = u32KeyLen;
    stCipherRsaData.pu8Output = M;

    ret = DRV_CIPHER_CheckRsaData(stCipherRsaData.pu8N, stCipherRsaData.pu8K, stCipherRsaData.pu8Input, u32KeyLen);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA data invalid!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HI_DRV_SYS_GetChipVersion(&penChipType, &penChipID);
    if((HI_CHIP_TYPE_HI3798M == penChipType) && (HI_CHIP_VERSION_V300 == penChipID))
    {
        u32StartCode = 0x5;
        u32EnableCrcCheck = HI_TRUE;
    }
    else
    {
         u32StartCode = 0x1;
         u32EnableCrcCheck = HI_FALSE;
     }

    HI_ERR_CIPHER("penChipType=0x%x,penChipID=0x%x,u32StartCode=0x%x,u32EnableCrcCheck=0x%x!\n",penChipType,penChipID,u32StartCode,u32EnableCrcCheck);

    ret = DRV_CIPHER_ClearRsaRam(u32StartCode);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA clear ram error!\n");
        return HI_FAILURE;
    }

    /*Config Mode*/
    HAL_RSA_ConfigMode(enKeyWidth);

    ret = DRV_RSA_RandMaskEnable(&stCipherRsaData, u32KeyLen, u32Rnadom, u32EnableCrcCheck);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA rand mask error!\n");
        return HI_FAILURE;
    }

    /*Write N,E,M*/
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_MODULE, stCipherRsaData.pu8N, stCipherRsaData.u16NLen, u32KeyLen, u32Rnadom);
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_KEY, stCipherRsaData.pu8K, stCipherRsaData.u16KLen, u32KeyLen, u32Rnadom);
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_CONTEXT, stCipherRsaData.pu8Input, stCipherRsaData.u16NLen, u32KeyLen, u32Rnadom);

//    HI_PRINT_HEX("N", pCipherRsaData->pu8N, u32KeyLen);
//    HI_PRINT_HEX("K", pCipherRsaData->pu8K, u32KeyLen);
//    HI_PRINT_HEX("M_IN", pCipherRsaData->pu8Input, u32KeyLen);

    /*Sart*/
    HAL_RSA_Start(u32StartCode);
    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    u32ErrorCode = HAL_RSA_GetErrorCode();
    if( 0 != u32ErrorCode )
    {
        HI_ERR_CIPHER("RSA is err: chipset error code: 0x%x!\n", u32ErrorCode);
        return HI_FAILURE;
    }

    /*Get result*/
    HAL_RSA_ReadData(stCipherRsaData.pu8Output, stCipherRsaData.u16NLen, u32KeyLen);

    if (cipher_copy_to_user(pCipherRsaData->pu8Output, M+(u32KeyLen - pCipherRsaData->u16NLen),
            pCipherRsaData->u16NLen))
    {
        HI_ERR_CIPHER("copy data to user fail!\n");
        return HI_FAILURE;
    }

//    HI_PRINT_HEX("M_OUT", pCipherRsaData->pu8Output, u32KeyLen);

    return HI_SUCCESS;

}
#endif

//#endif
