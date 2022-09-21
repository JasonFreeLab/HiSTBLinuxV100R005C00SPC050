/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
//#include <asm/arch/hardware.h>
#include <asm/setup.h>
#include <asm/barrier.h>    /* mb() */
#include <asm/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/fcntl.h>
#include <linux/param.h>
#include <linux/delay.h>

#include <linux/init.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/wait.h>
#include <linux/spinlock.h>
#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/random.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "drv_plcipher_ioctl.h"
#include "drv_plcipher_ext.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_mem.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_plcipher.h"
#include "hal_plcipher.h"
#include "drv_plcipher.h"
#include "hi_drv_struct.h"
#include "drv_advca_ext.h"


//#define PLCIPHER_DEBUG
DEFINE_SEMAPHORE(g_PLCipherMutexKernel);

typedef struct hiPLCIPHER_OSR_CHN_S
{
    HI_U32 ChanID;
    HI_BOOL bOpen;                 /* mark soft channel open or not*/
    HI_BOOL bDataDone;                    /* mark the data done or not */
    HI_BOOL bEncryptOrDecrypt;
    HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd;
    HI_UNF_PLCIPHER_ALG_E enAlg;           /**< Operating mode */
    HI_U32 InPhyAddr;
    HI_U32 OutPhyAddr;
    HI_U32 DataLen;
    HI_U32 OddCW[4];
    HI_U32 EvenCW[4];
    HI_U32 IV[4];
    HI_BOOL bDrop;
    /* tmp for 420b03 */
    PLCIPHER_DATA_S stTmpPlcipherData;
    MMZ_BUFFER_S    stTmpPlcipherMMz;
    wait_queue_head_t plcipher_wait_queue;    /* mutex method */
}PLCIPHER_OSR_CHN_S;

typedef struct hiPLCIPHER_COMM_S
{
    MMZ_BUFFER_S stMmzBuf;
    SMMU_BUFFER_S stSmmuBuf;
} PLCIPHER_COMM_S;

static PLCIPHER_COMM_S g_stPLCipherComm;
static PLCIPHER_DESC_MGR_S g_stDescMgr;
static PLCIPHER_OSR_CHN_S g_stSoftChn[PLCIPHER_CHAN_NUM];

#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))

#define PLCIPHER_CheckHandle(ChanId)   \
    do \
    { \
        if (ChanId >= PLCIPHER_CHAN_NUM) \
        { \
            HI_ERR_PLCIPHER("chan %d is too large, max: %d\n", ChanId, PLCIPHER_CHAN_NUM); \
            return HI_ERR_PLCIPHER_INVALID_PARA; \
        } \
        if (HI_FALSE == g_stSoftChn[ChanId].bOpen) \
        { \
            HI_ERR_PLCIPHER("chan %d is not open\n", ChanId); \
            return HI_ERR_PLCIPHER_INVALID_HANDLE; \
        } \
    } while (0)

#define PLCIPHER_CHECKPOINTER(ptr)                                  \
            do                                                      \
            {                                                       \
                if (!(ptr))                                         \
                {                                                   \
                    HI_ERR_PLCIPHER("pointer is null\n");           \
                    return HI_ERR_PLCIPHER_INVALID_PTR;             \
                }                                                   \
            } while (0)
/*ScrambleFlag : 0,1 未加扰， 2 偶密钥加扰，3 奇密钥加扰
   AFLen = 188 - 4 - PayLoadLen - 1, only support 183 and 179
   pid = 0
*/
static HI_VOID CreateTSPacket(HI_U8* pu8Buf, HI_U32 AFLen, HI_U32 ScrambleFlag)
{
    memset(pu8Buf, 0x0, 188);
    pu8Buf[0] = 0x47;
    pu8Buf[1] = (0 & 0x1f00) >> 8 ;
    pu8Buf[2] = (0 & 0xff);

    if (183 == AFLen)
    {
        pu8Buf[3] = (( ScrambleFlag & 0x3 ) << 6) | (0x2 << 4) ;
        pu8Buf[4] =  AFLen;
        memset(&pu8Buf[5], 0xff, AFLen);

    }
    else if (179 == AFLen)
    {
        pu8Buf[3] = (( ScrambleFlag & 0x3 ) << 6) | (0x3 << 4);
        pu8Buf[4] =  AFLen;
        memset(&pu8Buf[5], 0xff, AFLen);
        memset(&pu8Buf[AFLen+4+1], 0x11, 4);
    }
    else
    {
        HI_ERR_PLCIPHER("invalid adapt filed length[%d], only support 183 and 181\n", AFLen);
        return;
    }
}

/* interrupt routine, callback */
irqreturn_t DRV_PLCipher_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 InDescvalidNum = 0;
    HI_U32 IntState = 0;
    PLCIPHER_DESC_MGR_S* pstDescMgr = (PLCIPHER_DESC_MGR_S*)&g_stDescMgr;

    HAL_PLCipher_GetIntState(&IntState);
    HAL_PLCipher_ClrIntState();
    HAL_PLCipher_DisableAllInt();
    if (IntState >> 24 & 0x1)
    {
        if (IntState >> 19 & 0x1)
        {
            HAL_PLCIPHER_GetDescReadPtr(&pstDescMgr->InDescRPtr,&pstDescMgr->OutDescRPtr);
            HAL_PLCIPHER_GetInDescInvalidNum(&InDescvalidNum );
            if (InDescvalidNum == 0)// it means hardware finished deal all desc
            {
                if ((pstDescMgr->InDescWPtr != pstDescMgr->InDescRPtr) || (pstDescMgr->OutDescWPtr !=  pstDescMgr->OutDescRPtr))
                {
                    HI_FATAL_PLCIPHER("fatale error: in_sw(%d) != in_hr(%d) or out_sr(%d) != out_hr(%d)\n",\
                        pstDescMgr->InDescWPtr,pstDescMgr->InDescRPtr,pstDescMgr->OutDescWPtr,pstDescMgr->OutDescRPtr);
                }
                else
                {
                    g_stSoftChn[pstDescMgr->LastChanNum].bDataDone = HI_TRUE;
                    wake_up_interruptible(&(g_stSoftChn[pstDescMgr->LastChanNum].plcipher_wait_queue));
                }
            }
        }
    }

    HAL_PLCipher_EnableAllInt();
    HAL_PLCipher_EnableOutDescDataDoneInt();
    return IRQ_HANDLED;
}

HI_S32 DRV_PLCIPHER_Init(HI_VOID)
{
    HI_U32 i = 0;
    HI_S32 ret = HI_FAILURE;
    HI_U32 DescBufSize = 0;

    memset(&g_stPLCipherComm, 0, sizeof(PLCIPHER_COMM_S));
    DescBufSize = sizeof(PLCIPHER_DESC_S)*PLCIPHER_DSC_NUM*2;
    ret = HI_DRV_MMZ_AllocAndMap("PLCIPHER_DescBuf", MMZ_OTHERS, DescBufSize, 0, &g_stPLCipherComm.stMmzBuf);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PLCIPHER("Can NOT get mem for cipher, init failed, exit...\n");
        return HI_FAILURE;
    }

    /*attention :
    1. ENA_INT[24].int_ena_all 是该寄存器的其余中断bit使能的必要条件.
    */
    HAL_PLCipher_HardWareInit();
    HAL_PLCipher_EnableGloableInt();
    HAL_PLCipher_EnableOutDescDataDoneInt();

    //HAL_PLCipher_SetKeySecureAttr(HI_TRUE);
    HAL_PLCipher_ResetDescQueue();

    memset(&g_stDescMgr, 0, sizeof(g_stDescMgr));
    g_stDescMgr.InDescStartPhyAddr = g_stPLCipherComm.stMmzBuf.u32StartPhyAddr;
    g_stDescMgr.pu8InDescStartVirAddr = g_stPLCipherComm.stMmzBuf.pu8StartVirAddr;
    g_stDescMgr.OutDescStartPhyAddr = g_stPLCipherComm.stMmzBuf.u32StartPhyAddr + sizeof(PLCIPHER_DESC_S)*PLCIPHER_DSC_NUM;
    g_stDescMgr.pu8OutDescStartVirAddr = g_stPLCipherComm.stMmzBuf.pu8StartVirAddr + sizeof(PLCIPHER_DESC_S)*PLCIPHER_DSC_NUM;


    //DescQSize =  sizeof(PLCIPHER_DESC_S) * PLCIPHER_DSC_NUM;
    HAL_PLCipher_ConfigDescQueue(g_stDescMgr.InDescStartPhyAddr, PLCIPHER_DSC_NUM,g_stDescMgr.OutDescStartPhyAddr, PLCIPHER_DSC_NUM );

    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        memset((HI_U8*)&g_stSoftChn[i],0x0,sizeof(PLCIPHER_OSR_CHN_S));
        g_stSoftChn[i].ChanID = -1;
        init_waitqueue_head(&(g_stSoftChn[i].plcipher_wait_queue));
    }

    /* request irq */
    ret = osal_request_irq(PLCIPHER_IRQ_NUMBER,(irq_handler_t) DRV_PLCipher_ISR, IRQF_SHARED, "plcipher", (HI_VOID *)&g_stDescMgr);
    if(HI_SUCCESS != ret)
    {
        HAL_PLCipher_DisableGloableInt();
        HAL_PLCipher_ClrIntState();
        HI_DRV_MMZ_UnmapAndRelease(&g_stPLCipherComm.stMmzBuf);
        HI_ERR_PLCIPHER("Irq request failure, ret=%#x.", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID DRV_PLCIPHER_DeInit(HI_VOID)
{
    HI_U32 i = 0;
    memset(&g_stDescMgr, 0, sizeof(g_stDescMgr));
    (HI_VOID)HI_DRV_MMZ_UnmapAndRelease(&g_stPLCipherComm.stMmzBuf);
    memset(&g_stPLCipherComm, 0, sizeof(PLCIPHER_COMM_S));
    HAL_PLCipher_ResetDescQueue();
    HAL_PLCipher_DisableGloableInt();
    HAL_PLCipher_DisableOutDescDataDoneInt();
    HAL_PLCipher_ClrOutDescDataDoneIntStatus();
    HAL_PLCipher_HardWareDeInit();
    osal_free_irq(PLCIPHER_IRQ_NUMBER,"plcipher", (HI_VOID *)&g_stDescMgr);
    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        memset(&g_stSoftChn[i],0x0,sizeof(PLCIPHER_OSR_CHN_S));
        g_stSoftChn[i].ChanID = -1;
    }

    return;
}

HI_S32 DRV_PLCIPHER_Open(struct inode * inode, struct file * file)
{
    return HI_SUCCESS;
}

HI_S32 DRV_PLCIPHER_Release(struct inode * inode, struct file * file)
{
    HI_U32 i = 0;

    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        memset(&g_stSoftChn[i],0x0,sizeof(PLCIPHER_OSR_CHN_S));
        g_stSoftChn[i].ChanID = -1;
    }

    return HI_SUCCESS;
}

HI_VOID HI_DRV_PLCIPHER_Suspend(HI_VOID)
{
    DRV_PLCIPHER_DeInit();
    return;
}

HI_S32 HI_DRV_PLCIPHER_Resume(HI_VOID)
{
    (HI_VOID)DRV_PLCIPHER_Init();
    return 0;
}


HI_S32 HI_DRV_PLCIPHER_CreateHandle(HI_HANDLE* phPLCipher)
{
    HI_U32 i = 0;
    HI_U32 ret = HI_FAILURE;
    HI_CHAR BufName[16];

    PLCIPHER_CHECKPOINTER(phPLCipher);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    for(i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (0 == g_stSoftChn[i].bOpen)
        {
            break;
        }
    }

    if (i >= PLCIPHER_CHAN_NUM)
    {
        HI_ERR_PLCIPHER("No more plcipher chan left.\n");
        up(&g_PLCipherMutexKernel);
        return HI_ERR_PLCIPHER_FAILED_GETHANDLE;
    }

    memset(&g_stSoftChn[i],0x0,sizeof(PLCIPHER_OSR_CHN_S));
    g_stSoftChn[i].ChanID = i;
    g_stSoftChn[i].bOpen = HI_TRUE;
    g_stSoftChn[i].bDataDone = HI_TRUE;

     /* tmp for 420b03 plcipher */
    snprintf(BufName, sizeof(BufName), "PL_TmpEn[%u]", i);
    ret = HI_DRV_MMZ_AllocAndMap(BufName, MMZ_OTHERS, 188*16, 0, &g_stSoftChn[i].stTmpPlcipherMMz);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PLCIPHER("Can NOT get mmz for plcipher, init failed, exit...\n");
        return HI_FAILURE;
    }

    g_stSoftChn[i].stTmpPlcipherData.CIHandle = HI_HANDLE_MAKEHANDLE(HI_ID_PLCIPHER, 0, i);
    g_stSoftChn[i].stTmpPlcipherData.DestPhyAddr = g_stSoftChn[i].stTmpPlcipherMMz.u32StartPhyAddr;
    g_stSoftChn[i].stTmpPlcipherData.ScrPhyAddr = g_stSoftChn[i].stTmpPlcipherMMz.u32StartPhyAddr;
    g_stSoftChn[i].stTmpPlcipherData.u32DataLength = g_stSoftChn[i].stTmpPlcipherMMz.u32Size;
    init_waitqueue_head(&(g_stSoftChn[i].plcipher_wait_queue));

    *phPLCipher = HI_HANDLE_MAKEHANDLE(HI_ID_PLCIPHER, 0, i);
    //only set chan id and alg valid
    //HAL_PLCipher_SetCWAttr(i, HI_TRUE, pstAttr->enAlg, HI_TRUE );
    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_DestroyHandle(HI_HANDLE hPLCipherchn)
{
    HI_U32 softChnId = 0;
    softChnId = HI_HANDLE_GET_CHNID(hPLCipherchn);

    if ((HI_ID_PLCIPHER !=  HI_HANDLE_GET_MODID(hPLCipherchn)) || (softChnId >=  PLCIPHER_CHAN_NUM))
    {
       HI_ERR_PLCIPHER("error: Destory Invalid Handle : 0x%x \n",hPLCipherchn);
       return HI_ERR_PLCIPHER_INVALID_HANDLE;
    }

    if (HI_FALSE == g_stSoftChn[softChnId].bOpen)
    {
        return HI_SUCCESS;
    }
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    memset(&g_stSoftChn[softChnId], 0x0, sizeof(PLCIPHER_OSR_CHN_S));
    g_stSoftChn[softChnId].ChanID = -1;

    if (g_stSoftChn[softChnId].stTmpPlcipherMMz.pu8StartVirAddr)
    {
        (HI_VOID)HI_DRV_MMZ_UnmapAndRelease(&g_stSoftChn[softChnId].stTmpPlcipherMMz);
        memset(&g_stSoftChn[softChnId].stTmpPlcipherMMz, 0, sizeof(MMZ_BUFFER_S));
    }
    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    HI_U32 softChnId = 0;

    softChnId = HI_HANDLE_GET_CHNID(hPLCipher);
    PLCIPHER_CheckHandle(softChnId);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    pstAttr->enAlg = g_stSoftChn[softChnId].enAlg;
    pstAttr->bPIDFilterEn = HI_FALSE;

    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    HI_U32 softChnId = 0;

    softChnId = HI_HANDLE_GET_CHNID(hPLCipher);
    PLCIPHER_CheckHandle(softChnId);
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    /*
    only keep these attr in DDR , it wiil be set into register when call HI_DRV_PLCIPHER_SetKeyIV
    */
    g_stSoftChn[softChnId].enAlg = pstAttr->enAlg;
    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 DRV_PLCIPHER_DealData(HI_BOOL bEncryptOrDecrypt,  PLCIPHER_DATA_S *pstCIData)
{
    HI_U32 softChnId = 0;
    HI_U32 EvenOdd;
    PLCIPHER_DESC_S* pstInDesc = HI_NULL;
    PLCIPHER_DESC_S* pstOutDesc = HI_NULL;
    HI_U32 InBufferAddr = pstCIData->ScrPhyAddr;
    HI_U32 OutBufferAddr = pstCIData->DestPhyAddr;
    HI_U32 BufferLen = pstCIData->u32DataLength;
    softChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);
    PLCIPHER_CheckHandle(softChnId);
    EvenOdd = g_stSoftChn[softChnId].enKeyEvenOdd;
    g_stSoftChn[softChnId].bEncryptOrDecrypt = bEncryptOrDecrypt;
    g_stSoftChn[softChnId].InPhyAddr = pstCIData->ScrPhyAddr;
    g_stSoftChn[softChnId].OutPhyAddr = pstCIData->DestPhyAddr;
    g_stSoftChn[softChnId].DataLen = pstCIData->u32DataLength;

    do
    {
        HI_U32 len = (BufferLen >= PLCIPHER_MAX_SIZE_PRE_DESC) ? PLCIPHER_MAX_SIZE_PRE_DESC : BufferLen;
        pstInDesc = (PLCIPHER_DESC_S*)(g_stDescMgr.pu8InDescStartVirAddr + g_stDescMgr.InDescWPtr * sizeof(PLCIPHER_DESC_S));
        pstInDesc->buf_start_addr = InBufferAddr ;
        pstInDesc->buf_len = len;
        pstInDesc->chan_num_data_size = (softChnId << 16) & 0xff0000;
        pstInDesc->DescAttr.u32 = 0;
        pstInDesc->DescAttr.bits.crypt_type = (bEncryptOrDecrypt)?1:0;
        pstInDesc->DescAttr.bits.cw_odd_even = EvenOdd;
        pstInDesc->DescAttr.bits.rec_ts_length = 0;



        pstOutDesc = (PLCIPHER_DESC_S*)(g_stDescMgr.pu8OutDescStartVirAddr + g_stDescMgr.OutDescWPtr * sizeof(PLCIPHER_DESC_S));
        pstOutDesc->buf_start_addr = OutBufferAddr ;
        pstOutDesc->buf_len = len;
        pstOutDesc->chan_num_data_size = (softChnId << 16) & 0xff0000;

        if (++g_stDescMgr.InDescWPtr >= PLCIPHER_DSC_NUM)
        {
            g_stDescMgr.InDescWPtr     = 0;
            g_stDescMgr.InDescStartPhyAddr  = g_stPLCipherComm.stMmzBuf.u32StartPhyAddr;
        }
        if (++g_stDescMgr.OutDescWPtr >= PLCIPHER_DSC_NUM)
        {
            g_stDescMgr.OutDescWPtr    = 0;
            g_stDescMgr.OutDescStartPhyAddr = g_stPLCipherComm.stMmzBuf.u32StartPhyAddr + sizeof(PLCIPHER_DESC_S)*PLCIPHER_DSC_NUM;
        }

        HAL_PLCipher_InDescAdd();
        HAL_PLCipher_OutDescAdd();

        InBufferAddr  += len;
        OutBufferAddr += len;
        BufferLen   -= len;

        if (0 == BufferLen)
        {
            break;
        }
    } while (1);

    g_stDescMgr.LastChanNum = softChnId;
    g_stSoftChn[softChnId].bDataDone = HI_FALSE;
    if (0 == wait_event_interruptible_timeout(g_stSoftChn[softChnId].plcipher_wait_queue,
                g_stSoftChn[softChnId].bDataDone != HI_FALSE, msecs_to_jiffies(2000)))
    {
        HI_ERR_PLCIPHER("Encrypt time out! PLCIPHER_IRQ_NUMBER: %d \n", PLCIPHER_IRQ_NUMBER);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_SetKeyIV(PLCIPHER_SetKey* pstKey)
{
    HI_U32 i = 0;
    HI_U32 softChnId = 0;
    PLCIPHER_OSR_CHN_S* pstSoftChn = NULL;
    HI_U32 KeyLen       = PLCIPHER_KEY_SIZE / sizeof(HI_U32);
    HI_U32 Key[4] = {0};
    HI_U8 ReverIV[16] = {0};

    PLCIPHER_CHECKPOINTER(pstKey);
    softChnId = HI_HANDLE_GET_CHNID(pstKey->CIHandle);
    PLCIPHER_CheckHandle(softChnId);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    pstSoftChn = &g_stSoftChn[softChnId];
    pstSoftChn->enKeyEvenOdd = pstKey->enEvenOdd;

    HAL_PLCipher_SetCWAttr(softChnId, pstKey->enEvenOdd, pstSoftChn->enAlg, pstKey->bIsCWOrIV);

    if ( !pstKey->bIsCWOrIV )
    {
        /*before set IV ,need reverse it*/
        for ( i = 0 ; i <  PLCIPHER_KEY_SIZE ; i++ )
        {
            ReverIV[i] = pstKey->Key[PLCIPHER_KEY_SIZE - i -1];
        }
        for (i = 0; i < KeyLen; i++)
        {
            Key[i] = ((HI_U32*)ReverIV)[i];
            HAL_PLCipher_SetCWWord(Key[i],i);
            g_stSoftChn[softChnId].IV[i] = Key[i] ;
        }
    }
    else
    {
        for (i = 0; i < KeyLen; i++)
        {
            Key[i] = ((HI_U32*)pstKey->Key)[i];
            HAL_PLCipher_SetCWWord(Key[i],i);
            if ( pstKey->enEvenOdd == HI_UNF_PLCIPHER_KEY_EVEN)
            {
                g_stSoftChn[softChnId].EvenCW[i] = Key[i];
            }
            else
            {
                g_stSoftChn[softChnId].OddCW[i] = Key[i];
            }
        }
    }

    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_U32 ChnId = 0;
    PLCIPHER_SetKey stPlAttr = {0};

    PLCIPHER_CHECKPOINTER(pu8Key);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);
    PLCIPHER_CheckHandle(ChnId);

    stPlAttr.CIHandle = hPLCipher;
    stPlAttr.bIsCWOrIV = HI_TRUE;  //CW KEY ,this member must be HI_TRUE
    stPlAttr.enEvenOdd = enKeyType;
    memcpy(stPlAttr.Key, pu8Key, MIN(sizeof(stPlAttr.Key), u32KeyLen));

    return HI_DRV_PLCIPHER_SetKeyIV(&stPlAttr);
}

HI_S32 HI_DRV_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen)
{
    HI_U32 ChnId = 0;
    PLCIPHER_SetKey stPlAttr = {0};

    PLCIPHER_CHECKPOINTER(pu8IV);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);
    PLCIPHER_CheckHandle(ChnId);

    stPlAttr.CIHandle = hPLCipher;
    stPlAttr.bIsCWOrIV = HI_FALSE; //IV KEY ,this member must be HI_FALSE
    stPlAttr.enEvenOdd = enKeyType;
    memcpy(stPlAttr.Key, pu8IV, MIN(sizeof(stPlAttr.Key), u32IVLen));

    return HI_DRV_PLCIPHER_SetKeyIV(&stPlAttr);
}

HI_S32 HI_DRV_PLCIPHER_Encrypt(PLCIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_S32 j = 0;
    HI_U8 * pu8TmpBuf;
    PLCIPHER_CHECKPOINTER(pstCIData);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    /* tmp for 420B03 Encrypt */
    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (pstCIData->CIHandle == g_stSoftChn[i].stTmpPlcipherData.CIHandle)
        {

            pu8TmpBuf = g_stSoftChn[i].stTmpPlcipherMMz.pu8StartVirAddr;
            for (j = 0; j < 15; j++)
            {
                CreateTSPacket(pu8TmpBuf, 183, 0);
                pu8TmpBuf += 188;
            }
            CreateTSPacket(pu8TmpBuf, 179, 0);
            g_stSoftChn[i].stTmpPlcipherData.u32DataLength = 188 * 16;
            (HI_VOID)DRV_PLCIPHER_DealData(HI_TRUE, &g_stSoftChn[i].stTmpPlcipherData);
            break;
        }
    }

    ret = DRV_PLCIPHER_DealData(HI_TRUE, pstCIData);

    up(&g_PLCipherMutexKernel);

    return ret;
}


HI_S32 HI_DRV_PLCIPHER_Decrypt(PLCIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_S32 j = 0;
    HI_U8 * pu8TmpBuf;
    PLCIPHER_CHECKPOINTER(pstCIData);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    /* tmp for 420B03 Decrypt */
    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (pstCIData->CIHandle == g_stSoftChn[i].stTmpPlcipherData.CIHandle)
        {
            pu8TmpBuf = g_stSoftChn[i].stTmpPlcipherMMz.pu8StartVirAddr;
            /* create odd or even scrambled ts data */
            if (HI_UNF_PLCIPHER_KEY_ODD == g_stSoftChn[i].enKeyEvenOdd)
            {
                for (j = 0; j < 15; j++)
                {
                    CreateTSPacket(pu8TmpBuf, 183, 3);
                    pu8TmpBuf += 188;
                }
                CreateTSPacket(pu8TmpBuf, 179, 3);
            }
            else
            {
                for (j = 0; j < 15; j++)
                {
                    CreateTSPacket(pu8TmpBuf, 183, 2);
                    pu8TmpBuf += 188;
                }
                CreateTSPacket(pu8TmpBuf, 179, 2);
            }

            g_stSoftChn[i].stTmpPlcipherData.u32DataLength = 188 * 16;
            (HI_VOID)DRV_PLCIPHER_DealData(HI_FALSE, &g_stSoftChn[i].stTmpPlcipherData);

            break;
        }
    }

    ret = DRV_PLCIPHER_DealData(HI_FALSE, pstCIData);

    up(&g_PLCipherMutexKernel);

    return ret;
}
#if (1 == HI_PROC_SUPPORT)
HI_S32 DRV_PLCIPHER_GetChanStatus(PLCIPHER_CHN_STATUS_S *pstChanStatus)
{

    HI_U32 i = 0;

    for(i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (pstChanStatus->ChanID == g_stSoftChn[i].ChanID)
        {
            break;
        }
    }

    if ( i >= PLCIPHER_CHAN_NUM)
    {
        pstChanStatus->bOpen = HI_FALSE;
        pstChanStatus->enAlg = HI_UNF_PLCIPHER_ALG_BUTT;
        pstChanStatus->bDataDone = HI_FALSE;
        pstChanStatus->enKeyEvenOdd = HI_UNF_PLCIPHER_KEY_BUTT;
        pstChanStatus->InPhyAddr = 0;
        pstChanStatus->OutPhyAddr = 0;
        pstChanStatus->bEncryptOrDecrypt = HI_FALSE;
        pstChanStatus->DataLen = 0;

        memset(pstChanStatus->EvenCW, 0, 16);
        memset(pstChanStatus->OddCW, 0, 16);
        memset(pstChanStatus->IV, 0, 16);

        return HI_SUCCESS;
    }

    //HAL_PLCipher_GetCWAttr(i, &pstChanStatus->enKeyEvenOdd, &pstChanStatus->enAlg );
    pstChanStatus->bOpen = g_stSoftChn[i].bOpen;
    pstChanStatus->enAlg = g_stSoftChn[i].enAlg;
    pstChanStatus->bDataDone = g_stSoftChn[i].bDataDone;
    pstChanStatus->enKeyEvenOdd = g_stSoftChn[i].enKeyEvenOdd;
    pstChanStatus->InPhyAddr = g_stSoftChn[i].InPhyAddr;
    pstChanStatus->OutPhyAddr = g_stSoftChn[i].OutPhyAddr;
    pstChanStatus->bEncryptOrDecrypt = g_stSoftChn[i].bEncryptOrDecrypt;
    pstChanStatus->DataLen = g_stSoftChn[i].DataLen;

    memcpy(pstChanStatus->EvenCW, g_stSoftChn[i].EvenCW, 16);
    memcpy(pstChanStatus->OddCW, g_stSoftChn[i].OddCW, 16);
    memcpy(pstChanStatus->IV, g_stSoftChn[i].IV, 16);


    return HI_SUCCESS;
}

HI_S32 DRV_PLCIPHER_GetDESCStatus(PLCIPHER_DESC_STATUS_S *pstDescStatus)
{

    pstDescStatus->InDescStartAddr = g_stDescMgr.InDescStartPhyAddr;
    pstDescStatus->OutDescStartAddr = g_stDescMgr.OutDescStartPhyAddr;
    pstDescStatus->LastChanNum = g_stDescMgr.LastChanNum;
    pstDescStatus->DescDepth = PLCIPHER_DSC_NUM;
    HAL_PLCIPHER_GetInDescInvalidNum(&pstDescStatus->InDescValidNum);
    HAL_PLCIPHER_GetOutDescInvalidNum(&pstDescStatus->OutDescValidNum);
    HAL_PLCIPHER_GetDescReadPtr(&pstDescStatus->InDescRPtr,&pstDescStatus->OutDescRPtr);
    HAL_PLCIPHER_GetDescWritePtr(&pstDescStatus->InDescWPtr,&pstDescStatus->OutDescWPtr);

    return HI_SUCCESS;
}
#endif

EXPORT_SYMBOL(HI_DRV_PLCIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_GetAttr);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetAttr);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_Decrypt);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetKeyIV);

EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetKey);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetIV);


