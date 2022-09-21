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

#include "linux/interrupt.h"

#include "hi_kernel_adapt.h"
#include "hi_type.h"
#include "drv_plcipher_ioctl.h"
#include "hi_drv_mem.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_plcipher.h"
#include "drv_plcipher_define.h"
#include "hal_plcipher.h"
#include "hi_mpi_plcipher.h"

DEFINE_SEMAPHORE(g_PLCipherMutexKernel);
typedef struct hiPLCIPHER_COMM_S
{
    MMZ_BUFFER_S stMmzBuf;
    SMMU_BUFFER_S stSmmuBuf;
} PLCIPHER_COMM_S;

typedef struct hiPLCIPHER_OSR_CHN_S
{
    HI_U32  ChanID;
    HI_BOOL bOpen;
    HI_BOOL bDataDone;
    HI_BOOL bEncryptOrDecrypt;
    DESCR_CHAIN* pstDesc;
    HI_U32  DescBaseAddr;
    HI_U32  InPhyAddr;
    HI_U32  OutPhyAddr;
    HI_U32  DataLen;
    HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd;
    HI_BOOL bIsCWOrIV;
    HI_U32  OddCW[4];
    HI_U32  EvenCW[4];
    HI_U32  IV[4];
    HI_UNF_PLCIPHER_ATTR_S stAttr;
    wait_queue_head_t plcipher_wait_queue;    /* mutex method */
}PLCIPHER_OSR_CHN_S;

static PLCIPHER_COMM_S g_stPLCipherComm;
static PLCIPHER_DESC_MGR_S g_stDescMgr;
static PLCIPHER_OSR_CHN_S g_stChn[PLCIPHER_CHAN_NUM];
//static ADVCA_EXPORT_FUNC_S *g_pAdvcaFunc = HI_NULL;
static HI_S32 g_PLCipherOpenCounter = -1;

#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))

#define PLCIPHER_CHECKHANDLE(PLHandle) \
    do \
    { \
        HI_U32 ChanId = PLHandle & 0xF;  \
        if (((PLHandle >> 16) & 0xFF) != HI_ID_PLCIPHER || (ChanId >= PLCIPHER_CHAN_NUM )) \
        {\
            HI_ERR_PLCIPHER("PLHandle[0x%x] is invalid\n", PLHandle); \
            return HI_ERR_PLCIPHER_INVALID_HANDLE; \
        }\
        if (HI_FALSE == g_stChn[ChanId].bOpen) \
        { \
            HI_ERR_PLCIPHER("Chan[%d] is not open\n", ChanId); \
            return HI_ERR_PLCIPHER_INVALID_PARA; \
        } \
    } while (0)

#define PLCIPHER_CHECKPOINTER(ptr)                          \
    do                                                      \
    {                                                       \
        if (!(ptr))                                         \
        {                                                   \
            HI_ERR_PLCIPHER("pointer is null\n");           \
            return HI_ERR_PLCIPHER_INVALID_PTR;             \
        }                                                   \
    } while (0)

/* interrupt routine, callback */
irqreturn_t DRV_PLCipher_ISR(HI_S32 irq, HI_VOID *devId)
{
    int i = 0;
    U_DMA_GLB_STAT udma_glb_stat;
    U_DMA_OBUF_STAT_L udma_obuf_stat;
    U_DMA_SLOT_PO_W udma_slot_po;
    U_DMA_SLOT_PO_R udma_slot_pr;

    HAL_PLCipher_DisAllInt();
    HAL_PLCipher_GetDMAGlBStatus(&udma_glb_stat.u32);
    /*if dma obuf int happen*/
    if ( udma_glb_stat.bits.dma_pack_int & 0x1 )
    {
        HAL_PLCipher_GetDMAObufIntStatus(&udma_obuf_stat.u32);
        for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
        {
            if (udma_obuf_stat.bits.dma_obuf_stat_l & (1 << i))
            {
                HAL_PLCipher_ClrDMAObufIntStatus(i);
                HAL_PLCipher_GetDmaObufPW(i,&udma_slot_po.u32);
                HAL_PLCipher_GetDmaObufPR(i,&udma_slot_pr.u32);

                /*如果输出buffer写指针发生卷绕，标示已经写满了，此时读写指针都会等于0*/
                if ( udma_slot_po.bits.po_wptr_loopback && ( udma_slot_po.bits.hw_po_wptr == udma_slot_pr.bits.sw_po_rptr ))
                {
                    g_stChn[i].bDataDone = HI_TRUE;
                    wake_up_interruptible(&(g_stChn[i].plcipher_wait_queue));
                }
            }
        }
    }

    HAL_PLCipher_EnAllInt();
    return IRQ_HANDLED;
}

HI_S32 HI_DRV_PLCIPHER_Open(HI_VOID)
{
    HI_U32 u32MmuTlbBase = 0;
    HI_U32 ErrRdAddr = 0;
    HI_U32 ErrWrAddr = 0;

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    if (g_PLCipherOpenCounter > 0)
    {
        g_PLCipherOpenCounter++;
    }
    else
    {
        g_PLCipherOpenCounter = 1;
    }

    /* init and configure the plcipher hardware */
    HI_DRV_SMMU_GetPageTableAddr(&u32MmuTlbBase, &ErrRdAddr, &ErrWrAddr);
    BUG_ON(u32MmuTlbBase % 16);
    HAL_PLCipher_HardWareInit();
    HAL_PLCipher_EnMMU(u32MmuTlbBase);
    HAL_PLCipher_EnAllInt();
    HAL_PLCipher_CfgDMACoal(PLCIPHER_MAX_SIZE_PRE_DESC/188);

    up(&g_PLCipherMutexKernel);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_Close(HI_VOID)
{
    HI_U32 i = 0;
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    if(g_PLCipherOpenCounter > 0)
    {
        g_PLCipherOpenCounter--;
    }

    if (g_PLCipherOpenCounter == 0)
    {
        for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
        {
            memset(&g_stChn[i], 0x0, sizeof(PLCIPHER_OSR_CHN_S));
            g_stChn[i].ChanID = -1;
        }

        /* Deconfigure and deinit the plcipher hardware */
        HAL_PLCipher_DisAllInt();
        HAL_PLCipher_DisMMU();
        HAL_PLCipher_HardWareDeInit();
    }
    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_Init(HI_VOID)
{
    HI_U32 i = 0;
    HI_S32 ret = HI_FAILURE;

    ret = HI_DRV_MMZ_AllocAndMap("PLCIPHER_DescBuf", MMZ_OTHERS, sizeof(DESCR_CHAIN)*PLCIPHER_CHAN_NUM, 0, &g_stPLCipherComm.stMmzBuf);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PLCIPHER("Can NOT get mem for cipher, init failed, exit...\n");
        return HI_FAILURE;
    }

    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        memset((HI_U8*)&g_stChn[i],0x0,sizeof(PLCIPHER_OSR_CHN_S));
        g_stChn[i].ChanID = -1;
        init_waitqueue_head(&(g_stChn[i].plcipher_wait_queue));
    }

    /* request irq */
    ret = osal_request_irq(PLCIPHER_IRQ_NUMBER,(irq_handler_t) DRV_PLCipher_ISR, IRQF_SHARED, PLCIPHER_IRQ_NAME, (HI_VOID *)&g_stDescMgr);
    if(HI_SUCCESS != ret)
    {
        HI_DRV_MMZ_UnmapAndRelease(&g_stPLCipherComm.stMmzBuf);
        HI_ERR_PLCIPHER("Irq request failure, ret=%#x.", ret);
        return HI_FAILURE;
    }
    return ret;
}

HI_VOID HI_DRV_PLCIPHER_DeInit(HI_VOID)
{
    HI_U32 i = 0;
    (HI_VOID)HI_DRV_MMZ_UnmapAndRelease(&g_stPLCipherComm.stMmzBuf);
    memset(&g_stPLCipherComm, 0, sizeof(PLCIPHER_COMM_S));

    osal_free_irq(PLCIPHER_IRQ_NUMBER, PLCIPHER_IRQ_NAME, (HI_VOID *)&g_stDescMgr);
    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        memset(&g_stChn[i], 0x0, sizeof(PLCIPHER_OSR_CHN_S));
        g_stChn[i].ChanID = -1;
    }
    return;
}

HI_VOID HI_DRV_PLCIPHER_Suspend(HI_VOID)
{
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return;
    }

    /* Deconfigure and deinit the plcipher hardware */
    if (g_PLCipherOpenCounter > 0)
    {
        HAL_PLCipher_DisAllInt();
        HAL_PLCipher_DisMMU();
        HAL_PLCipher_HardWareDeInit();
    }

    up(&g_PLCipherMutexKernel);

    return;
}

HI_S32 HI_DRV_PLCIPHER_Resume(HI_VOID)
{
    HI_S32 i = 0;
    HI_U32 u32MmuTlbBase = 0;
    HI_U32 ErrRdAddr = 0;
    HI_U32 ErrWrAddr = 0;

    HI_HANDLE hPLCipher;
    HI_UNF_PLCIPHER_ATTR_S stAttr = {0};
    PLCIPHER_OSR_CHN_S* pstSoftChn = NULL;

    if (g_PLCipherOpenCounter <= 0)
    {
        HI_WARN_PLCIPHER("plcipher not init yet!\n");
        goto out;
    }

    /* init and configure the plcipher hardware */
    HI_DRV_SMMU_GetPageTableAddr(&u32MmuTlbBase, &ErrRdAddr, &ErrWrAddr);
    BUG_ON(u32MmuTlbBase % 16);
    HAL_PLCipher_HardWareInit();
    HAL_PLCipher_EnMMU(u32MmuTlbBase);
    HAL_PLCipher_CfgDMACoal(PLCIPHER_MAX_SIZE_PRE_DESC/188);

    for (i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        pstSoftChn = &g_stChn[i];
        /* we don't change the channel status */
        if (HI_TRUE == pstSoftChn->bOpen)
        {
            hPLCipher = HI_HANDLE_MAKEHANDLE(HI_ID_PLCIPHER, 0, i);
            /* resume attribute */
            HI_DRV_PLCIPHER_GetAttr(hPLCipher, &stAttr);
            HI_DRV_PLCIPHER_SetAttr(hPLCipher, &stAttr);
            /* resume CW and IV */

            if (HI_UNF_PLCIPHER_KEY_EVEN == pstSoftChn->enKeyEvenOdd)
            {
                HI_DRV_PLCIPHER_SetKey(hPLCipher, HI_UNF_PLCIPHER_KEY_EVEN, (HI_U8*)pstSoftChn->EvenCW, sizeof(pstSoftChn->EvenCW));
                HI_DRV_PLCIPHER_SetIV(hPLCipher, HI_UNF_PLCIPHER_KEY_EVEN, (HI_U8*)pstSoftChn->IV, sizeof(pstSoftChn->IV));
            }
            else
            {
                HI_DRV_PLCIPHER_SetKey(hPLCipher, HI_UNF_PLCIPHER_KEY_ODD, (HI_U8*)pstSoftChn->OddCW, sizeof(pstSoftChn->OddCW));
                HI_DRV_PLCIPHER_SetIV(hPLCipher, HI_UNF_PLCIPHER_KEY_ODD, (HI_U8*)pstSoftChn->IV, sizeof(pstSoftChn->IV));
            }
        }
    }

    HAL_PLCipher_EnAllInt();
out:
    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_CreateHandle(HI_HANDLE* phPLCipher)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;

    PLCIPHER_CHECKPOINTER(phPLCipher);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    for(i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (0 == g_stChn[i].bOpen)
        {
            break;
        }
    }

    if (i >= PLCIPHER_CHAN_NUM)
    {
        ret = HI_ERR_PLCIPHER_FAILED_GETHANDLE;
        HI_ERR_PLCIPHER("No more plcipher chan left.\n");
        up(&g_PLCipherMutexKernel);
        return HI_FAILURE;
    }

    memset(&g_stChn[i], 0x0, sizeof(PLCIPHER_OSR_CHN_S));
    g_stChn[i].ChanID = i;
    g_stChn[i].bOpen = HI_TRUE;
    g_stChn[i].pstDesc = (DESCR_CHAIN*)(g_stPLCipherComm.stMmzBuf.pu8StartVirAddr + sizeof(DESCR_CHAIN)*i);
    g_stChn[i].DescBaseAddr = g_stPLCipherComm.stMmzBuf.u32StartPhyAddr + sizeof(DESCR_CHAIN)*i;
    init_waitqueue_head(&(g_stChn[i].plcipher_wait_queue));

    *phPLCipher = HI_HANDLE_MAKEHANDLE(HI_ID_PLCIPHER, 0, i);
    HAL_PLCipher_DisDmaChn(i);
    up(&g_PLCipherMutexKernel);

    return ret;
}

HI_S32 HI_DRV_PLCIPHER_DestroyHandle(HI_HANDLE hPLCipherchn)
{
    HI_U32 ChnId = 0;
    ChnId = HI_HANDLE_GET_CHNID(hPLCipherchn);

    if ((HI_ID_PLCIPHER != HI_HANDLE_GET_MODID(hPLCipherchn)) || (ChnId >=  PLCIPHER_CHAN_NUM))
    {
       HI_ERR_PLCIPHER("error: Destory Invalid Handle : 0x%x \n",hPLCipherchn);
       return HI_ERR_PLCIPHER_INVALID_HANDLE;
    }

    if (HI_FALSE == g_stChn[ChnId].bOpen)
    {
        return HI_SUCCESS;
    }
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    memset(&g_stChn[ChnId],0x0,sizeof(PLCIPHER_OSR_CHN_S));
    g_stChn[ChnId].ChanID = -1;
    up(&g_PLCipherMutexKernel);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    HI_U32 ChnId = 0;

    PLCIPHER_CHECKPOINTER(pstAttr);
    PLCIPHER_CHECKHANDLE(hPLCipher);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    memcpy(pstAttr, &g_stChn[ChnId].stAttr, sizeof(HI_UNF_PLCIPHER_ATTR_S));

    up(&g_PLCipherMutexKernel);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    HI_U32 ChnId = 0;
    HI_U8 i = 0;

    PLCIPHER_CHECKPOINTER(pstAttr);
    PLCIPHER_CHECKHANDLE(hPLCipher);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    memcpy(&g_stChn[ChnId].stAttr, pstAttr, sizeof(HI_UNF_PLCIPHER_ATTR_S));

#ifndef PLCIPHER_TEE_SUPPORT
    HAL_PLCipher_SetSecChn(ChnId);
#endif


    if (!pstAttr->bPIDFilterEn)
    {
        HAL_PLCipher_CfgChanPIDFilter(ChnId, HI_FALSE);
    }
    else if (pstAttr->bPIDFilterEn && 0x0 != pstAttr->u32PidNum
               && pstAttr->u32PidNum <= HI_UNF_PLCIPHER_PIDFILTER_NUM)
    {
        HAL_PLCipher_CfgChanPIDFilter(ChnId, HI_TRUE);
        for (i = 0; i < pstAttr->u32PidNum; i++)
        {
            HAL_PLCipher_SetChnPID(ChnId, i, pstAttr->u16PID[i]);
        }

        /* disable the left PID slot */
        for (i = pstAttr->u32PidNum; i < HI_UNF_PLCIPHER_PIDFILTER_NUM; i++)
        {
            HAL_PLCipher_DisChnPID(ChnId, i);
        }
    }
    else
    {
        /* if pstAttr->bPIDFilterEn is TRUE and pstAttr->u32PidNum is not 0, the params are invalid */
        HI_ERR_PLCIPHER("Parameters Invalid!\n");
        up(&g_PLCipherMutexKernel);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    up(&g_PLCipherMutexKernel);
    return HI_SUCCESS;
}

static HI_VOID ConfigDMAChan(HI_U32 u32ChnId,HI_U32 u32InDescAddr,HI_U32 u32OBufPhyAddr,HI_U32 u32Len)
{
    HAL_PLCipher_ClrDMAObufMMU(u32ChnId);
    HAL_PLCipher_ClrDMAChanMMU(u32ChnId);
    HAL_PLCipher_DisDmaChn(u32ChnId);
    HAL_PLCipher_DisDmaObuf(u32ChnId);//增加关闭输出通道，防止输出buffer 卷绕状态无法恢复
    HAL_PLCipher_SetDmaChanBase(u32ChnId, u32InDescAddr);
    /*config the Desc depth as 2 , pay attention: the actual value of reg is 2-1=1,
          and the reg value must >= 1 ,otherwise ,logic will not work.*/
    HAL_PLCipher_SetDmaChanDepth(u32ChnId, 2);
    HAL_PLCipher_EnDmaChn(u32ChnId);

    HAL_PLCipher_SetDmaObufAddr(u32ChnId, u32OBufPhyAddr);
    HAL_PLCipher_SetDmaObufLen(u32ChnId, u32Len);
    HAL_PLCipher_EnDmaObuf(u32ChnId);
}

static HI_S32 _DRV_PLCIPHER_DataProcess(PLCIPHER_DATA_S *pstCIData, HI_BOOL bDeCrypt)
{
    HI_U32 ChnId = 0;

    HI_U32 DescBaseAddr = 0;
    DESCR_CHAIN* pstDesc = HI_NULL;

    HI_U32 InBufferAddr = pstCIData->ScrPhyAddr;
    HI_U32 OutBufferAddr = pstCIData->DestPhyAddr;
    HI_U32 BufferLen = pstCIData->u32DataLength;
    HI_U32 pld_nums = pstCIData->u32DataLength/188;

    PLCIPHER_CHECKHANDLE(pstCIData->CIHandle);
    ChnId = HI_HANDLE_GET_CHNID(pstCIData->CIHandle);

    g_stChn[ChnId].InPhyAddr = pstCIData->ScrPhyAddr;
    g_stChn[ChnId].OutPhyAddr = OutBufferAddr;
    g_stChn[ChnId].DataLen = pstCIData->u32DataLength;
    g_stChn[ChnId].bEncryptOrDecrypt = bDeCrypt;

    pstDesc = g_stChn[ChnId].pstDesc;
    DescBaseAddr = g_stChn[ChnId].DescBaseAddr;

    do
    {
        pstDesc->descr0.bits.pld_nums = pld_nums - 1;
        pstDesc->descr0.bits.type = PLCIPHER_DESC_TYPE_188;
        pstDesc->descr0.bits.desep = 1;
        pstDesc->slice_address = InBufferAddr;
        pstDesc->soc_define.bits.decrypt = bDeCrypt;
        if ( !bDeCrypt )
        {
            pstDesc->soc_define.bits.key_id = g_stChn[ChnId].enKeyEvenOdd;
        }
        pstDesc->user_define_check_code = 0x5A5AA5A5;
        ConfigDMAChan(ChnId,DescBaseAddr,OutBufferAddr,BufferLen);
        HAL_PLCipher_DmaChanAddDesc(ChnId);
    } while (0);

    g_stChn[ChnId].bDataDone = HI_FALSE;

    if (0 == wait_event_interruptible_timeout(g_stChn[ChnId].plcipher_wait_queue,
                g_stChn[ChnId].bDataDone, msecs_to_jiffies(2000)))
    {
        HI_ERR_PLCIPHER("Data process time out! PLCIPHER_IRQ_NUMBER: %d \n", PLCIPHER_IRQ_NUMBER);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_SetKeyIV(PLCIPHER_SetKey* pstKey)
{
    HI_U32 i = 0;
    HI_U32 ChnId = 0;
    PLCIPHER_OSR_CHN_S* pstSoftChn = NULL;
    HI_U32 KeyLen = PLCIPHER_KEY_SIZE / sizeof(HI_U32);
    HI_U32 Key[4] = {0};
    HI_U8 ReverIV[16] = {0};

    PLCIPHER_CHECKPOINTER(pstKey);
    PLCIPHER_CHECKHANDLE(pstKey->CIHandle);
    ChnId = HI_HANDLE_GET_CHNID(pstKey->CIHandle);

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    pstSoftChn = &g_stChn[ChnId];
    pstSoftChn->bIsCWOrIV = pstKey->bIsCWOrIV;
    pstSoftChn->enKeyEvenOdd = pstKey->enEvenOdd;

    HAL_PLCipher_SetCWAttr(ChnId, pstKey->enEvenOdd, pstSoftChn->stAttr.enAlg, pstKey->bIsCWOrIV);

    if (!pstKey->bIsCWOrIV)
    {
        /*before set IV ,need reverse it*/
        for (i = 0 ; i <  PLCIPHER_KEY_SIZE ; i++)
        {
            ReverIV[i] = pstKey->Key[PLCIPHER_KEY_SIZE - i -1];
        }
        for (i = 0; i < KeyLen; i++)
        {
            Key[i] = ((HI_U32*)ReverIV)[i];
            HAL_PLCipher_SetCWWord(Key[i],i);
            g_stChn[ChnId].IV[i] = Key[i];
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
                g_stChn[ChnId].EvenCW[i] = Key[i];
            }
            else
            {
                g_stChn[ChnId].OddCW[i] = Key[i];
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
    PLCIPHER_CHECKHANDLE(hPLCipher);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);

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
    PLCIPHER_CHECKHANDLE(hPLCipher);
    ChnId = HI_HANDLE_GET_CHNID(hPLCipher);

    stPlAttr.CIHandle = hPLCipher;
    stPlAttr.bIsCWOrIV = HI_FALSE; //IV KEY ,this member must be HI_FALSE
    stPlAttr.enEvenOdd = enKeyType;
    memcpy(stPlAttr.Key, pu8IV, MIN(sizeof(stPlAttr.Key), u32IVLen));

    return HI_DRV_PLCIPHER_SetKeyIV(&stPlAttr);
}

static HI_S32 _PLCIPHER_Data_Check(PLCIPHER_DATA_S *pstCIData)
{
    HI_U32 u32Len = 0;
    PLCIPHER_CHECKPOINTER(pstCIData);

    u32Len = pstCIData->u32DataLength;
    if (u32Len < PLCIPHER_MIN_SIZE_PRE_DESC || u32Len > PLCIPHER_MAX_SIZE_PRE_DESC)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid , correct rang is (0x%x ~ 0x%x )\n",\
            u32Len, PLCIPHER_MIN_SIZE_PRE_DESC, PLCIPHER_MAX_SIZE_PRE_DESC);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }
    if (u32Len%(188) != 0)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid , must be times of (188*16) \n",u32Len);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }
    return HI_SUCCESS;
}

HI_S32 HI_DRV_PLCIPHER_Encrypt(PLCIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;
    ret = _PLCIPHER_Data_Check(pstCIData);
    if (ret != HI_SUCCESS)
    {
        return ret;
    }

    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = _DRV_PLCIPHER_DataProcess(pstCIData, HI_FALSE);

    up(&g_PLCipherMutexKernel);

    return ret;
}

HI_S32 HI_DRV_PLCIPHER_Decrypt(PLCIPHER_DATA_S *pstCIData)
{
    HI_S32 ret = HI_SUCCESS;

    ret = _PLCIPHER_Data_Check(pstCIData);
    if (ret != HI_SUCCESS)
    {
        return ret;
    }
    if(down_interruptible(&g_PLCipherMutexKernel))
    {
        HI_ERR_PLCIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = _DRV_PLCIPHER_DataProcess(pstCIData,HI_TRUE);

    up(&g_PLCipherMutexKernel);

    return ret;
}

#if (1 == HI_PROC_SUPPORT)
HI_S32 DRV_PLCIPHER_GetChanStatus(PLCIPHER_CHN_STATUS_S *pstChanStatus)
{

    HI_U32 i = 0;

    for(i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        if (pstChanStatus->ChanID == g_stChn[i].ChanID)
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

    pstChanStatus->bOpen = g_stChn[i].bOpen;
    pstChanStatus->enAlg = g_stChn[i].stAttr.enAlg;
    pstChanStatus->bDataDone = g_stChn[i].bDataDone;
    pstChanStatus->enKeyEvenOdd = g_stChn[i].enKeyEvenOdd;
    pstChanStatus->InPhyAddr = g_stChn[i].InPhyAddr;
    pstChanStatus->OutPhyAddr = g_stChn[i].OutPhyAddr;
    pstChanStatus->bEncryptOrDecrypt = g_stChn[i].bEncryptOrDecrypt;
    pstChanStatus->DataLen = g_stChn[i].DataLen;

    memcpy(pstChanStatus->EvenCW,g_stChn[i].EvenCW,16);
    memcpy(pstChanStatus->OddCW,g_stChn[i].OddCW,16);
    memcpy(pstChanStatus->IV,g_stChn[i].IV,16);

    return HI_SUCCESS;
}
#endif

EXPORT_SYMBOL(HI_DRV_PLCIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_GetAttr);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetAttr);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetKeyIV);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_Decrypt);

/* export for keylad */
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetKey);
EXPORT_SYMBOL(HI_DRV_PLCIPHER_SetIV);

