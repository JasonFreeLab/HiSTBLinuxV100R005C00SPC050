/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_venc_strm_mng.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/07/22
  Description   : Definitions of buffer manager.
  History       :
  1.Date        : 2012/08/09
    Author      : l00185424
    Modification: Created file

 *******************************************************************************/

/******************************* Include Files ********************************/
/* Common headers */
#include "hi_kernel_adapt.h"
#include "hi_drv_mem.h"
/* Local headers */
#include "strm_mng_listbuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Static Definition *****************************/
static BUFMNG_GLOBAL_S s_stBMParam =
{
    .u16InstHandle = 0,
    .stInstHead = LIST_HEAD_INIT(s_stBMParam.stInstHead)
};
/*********************************** Code ************************************/
#define HI_KMALLOC_ATOMIC_LISTBUF(size)     HI_KMALLOC(HI_ID_VENC, size, GFP_ATOMIC)
#define HI_KFREE_LISTBUF(addr)       HI_KFREE(HI_ID_VENC, addr)

#define IS_READING(pBlock) (LISTBUF_BLOCK_READING == pBlock->enstatus)
#define IS_WRITING(pBlock) (LISTBUF_BLOCK_WRITING == pBlock->enstatus)
#define IS_FREE(pBlock) (LISTBUF_BLOCK_FREE == pBlock->enstatus)

#define LISTBUF_ASSERT_RETURN(Condition, RetValue)                  \
do                                                                 \
{                                                                  \
    if (!Condition)                                                \
    {                                                              \
        HI_ERR_LISTBUF("[%s %d]assert warning\n",__func__,__LINE__);\
        return RetValue;                                           \
    }                                                              \
}while(0)

#define LISTBUF_FIND_INST(hInst, pInst) \
    { \
        struct list_head* pos; \
        struct list_head* n; \
        LISTBUF_INST_S* pstTmp; \
        pInst = HI_NULL; \
        LISTBUF_SPIN_LOCK(s_stBMParam.stSpinLock, ulFlags); \
        list_for_each_safe(pos, n, &s_stBMParam.stInstHead) \
        { \
            pstTmp = list_entry(pos, LISTBUF_INST_S, stInstNode); \
            if (hInst == pstTmp->hBuf) \
            { \
                pInst = pstTmp; \
                break; \
            } \
        } \
        LISTBUF_SPIN_UNLOCK(s_stBMParam.stSpinLock, ulFlags); \
    }

/*********************************************/
static HI_VOID FreeBlockList(struct list_head* pstBlockHead)
{
    struct list_head* pos;
    struct list_head* n;
    LISTBUF_BLOCK_S* pstBlock;

    list_for_each_safe(pos, n, pstBlockHead)
    {
        pstBlock = list_entry(pos, LISTBUF_BLOCK_S, stBlockNode);
        list_del(pos);
        HI_KFREE_LISTBUF(pstBlock);
    }
}

static LISTBUF_BLOCK_S* FindListFirstHeadFrameBlock(struct list_head* pstBlockHead)
{
    struct list_head* pstList = pstBlockHead->next;
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;
    LISTBUF_BLOCK_S* pstTmp = HI_NULL;

    while (pstBlockHead != pstList)
    {
        pstTmp = list_entry(pstList, LISTBUF_BLOCK_S, stBlockNode);
        if ((pstTmp->u32NaluType == 1) || (pstTmp->u32NaluType == 5))
        {
            pstBlock = pstTmp;
            break;
        }
        pstList = pstList->next;
    }

    return pstBlock;
}

static LISTBUF_BLOCK_S* FindListFirstTailFrameBlock(struct list_head* pstBlockTail)
{
    struct list_head* pstList = pstBlockTail->prev;
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;
    LISTBUF_BLOCK_S* pstTmp = HI_NULL;

    while (pstBlockTail != pstList)
    {
        pstTmp = list_entry(pstList, LISTBUF_BLOCK_S, stBlockNode);
        if ((pstTmp->u32NaluType == 1) || (pstTmp->u32NaluType == 5))
        {
            pstBlock = pstTmp;
            break;
        }
        pstList = pstList->prev;
    }

    return pstBlock;
}

static LISTBUF_BLOCK_S* FindAllFirstTailFrameBlock(LISTBUF_INST_S* pstInst)
{
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;

    pstBlock = FindListFirstTailFrameBlock(&pstInst->stWriteBlockHead);
    if (pstBlock != HI_NULL)
    {
        return pstBlock;
    }

    pstBlock = FindListFirstTailFrameBlock(&pstInst->stFreeBlockHead);

    if (pstBlock != HI_NULL)
    {
        return pstBlock;
    }

    pstBlock = FindListFirstTailFrameBlock(&pstInst->stReadBlockHead);

    return pstBlock;
}

static LISTBUF_BLOCK_S* FindAllFirstHeadFrameBlock(LISTBUF_INST_S* pstInst)
{
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;

    pstBlock = FindListFirstHeadFrameBlock(&pstInst->stReadBlockHead);
    if (pstBlock != HI_NULL)
    {
        return pstBlock;
    }

    pstBlock = FindListFirstHeadFrameBlock(&pstInst->stFreeBlockHead);

    if (pstBlock != HI_NULL)
    {
        return pstBlock;
    }

    pstBlock = FindListFirstHeadFrameBlock(&pstInst->stWriteBlockHead);

    return pstBlock;
}


static LISTBUF_BLOCK_S* FindListHeadBlock(struct list_head* pstBlockHead)
{
    struct list_head* pstList = pstBlockHead->next;
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;

    if (list_empty(pstBlockHead))
    {
       return HI_NULL;
    }
    else
    {
        pstBlock = list_entry(pstList, LISTBUF_BLOCK_S, stBlockNode);
    }

    return pstBlock;
}

HI_S32 ListBuf_GetStrmState(HI_HANDLE hBuf, STRMMNG_State_S* pStrmStatInfo)
{
    LISTBUF_INST_S* pstInst  = HI_NULL;

    HI_SIZE_T ulFlags;

    LISTBUF_FIND_INST(hBuf, pstInst);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pStrmStatInfo->StrmHeadFree = pstInst->StrmHeadFree;
    pStrmStatInfo->StrmTailFree = pstInst->StrmTailFree;
    pStrmStatInfo->StrmGetTry  = pstInst->u32GetTry;
    pStrmStatInfo->StrmGetOK   = pstInst->u32GetOK;
    pStrmStatInfo->StrmPutTry  = pstInst->u32PutTry;
    pStrmStatInfo->StrmPutOK   = pstInst->u32PutOK;
    pStrmStatInfo->StrmRecvTry = pstInst->u32RecvTry;
    pStrmStatInfo->StrmRecvOK  = pstInst->u32RecvOK;
    pStrmStatInfo->StrmRlsTry  = pstInst->u32RlsTry;
    pStrmStatInfo->StrmRlsOK   = pstInst->u32RlsOK;

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

/*********************************************/

/*open vedu use*/
HI_VOID ListBuf_Init(HI_VOID)
{
    /* Init global parameter */
    s_stBMParam.u16InstHandle = 0;

    /* Init global mutex */
    HI_INIT_MUTEX(&s_stBMParam.stSem);

    INIT_LIST_HEAD(&s_stBMParam.stInstHead);

    return;
}

HI_VOID ListBuf_DeInit(HI_VOID)
{
    struct list_head *pos;
    struct list_head *n;
    struct list_head *head;
    LISTBUF_INST_S *pstInst;

    LISTBUF_LOCK(s_stBMParam.stSem);
    head = &s_stBMParam.stInstHead;

    if (!list_empty(head))
    {
        list_for_each_safe(pos, n, head)
        {
            pstInst = list_entry(pos, LISTBUF_INST_S, stInstNode);
            LISTBUF_UNLOCK(s_stBMParam.stSem);
            ListBuf_Destroy(pstInst->hBuf);
            LISTBUF_LOCK(s_stBMParam.stSem);
        }
    }

    s_stBMParam.u16InstHandle = 0;
    LISTBUF_UNLOCK(s_stBMParam.stSem);
}

HI_S32 ListBuf_Create(HI_HANDLE *phBuf, STRMMNG_INST_CONFIG_S *pstConfig)
{
    LISTBUF_INST_S *pstInst;
    HI_HANDLE *phBuf_temp = NULL;

    phBuf_temp = phBuf;

    if (HI_NULL == pstConfig)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }


    /* Allocate an instance */
    pstInst = HI_KMALLOC_ATOMIC_LISTBUF(sizeof(LISTBUF_INST_S));
    if (HI_NULL == pstInst)
    {
        HI_FATAL_LISTBUF("No memory.\n");

        return HI_ERR_LISTBUF_NO_MEMORY;
    }

    LISTBUF_LOCK(s_stBMParam.stSem);

    /* Allocate handle */
    *phBuf_temp = s_stBMParam.u16InstHandle;
    /* Init instance parameter */
    pstInst->hBuf = *phBuf_temp;

#ifdef HI_TEE_SUPPORT
    pstInst->bTvp = pstConfig->bTvp;
#endif
    pstInst->u32PhyAddr = pstConfig->u32PhyAddr;
    pstInst->pu8KnlVirAddr = pstConfig->pu8KnlVirAddr;
    pstInst->u32ParaSetPhyAddr  = pstConfig->u32ParaSetPhyAddr;
    pstInst->pu8ParaSetKnlVirAddr = pstConfig->pu8ParaSetKnlVirAddr;
    pstInst->u32Size = pstConfig->u32Size;
    HI_INFO_LISTBUF("[BUFMNG_Create] PHY:%x, K-VIR:%llx, SIZE:%d\n",
                   pstInst->u32PhyAddr, pstInst->pu8KnlVirAddr, pstInst->u32Size);

    spin_lock_init(&pstInst->stSpinLock);

    /* Init block list parameter */
    pstInst->StrmHeadFree = pstConfig->u32Size;
    pstInst->StrmTailFree = 0;
    pstInst->u32GetTry  = 0;
    pstInst->u32GetOK   = 0;
    pstInst->u32PutTry  = 0;
    pstInst->u32PutOK   = 0;
    pstInst->u32RecvTry = 0;
    pstInst->u32RecvOK  = 0;
    pstInst->u32RlsTry  = 0;
    pstInst->u32RlsOK   = 0;
    INIT_LIST_HEAD(&pstInst->stWriteBlockHead);
    INIT_LIST_HEAD(&pstInst->stFreeBlockHead);
    INIT_LIST_HEAD(&pstInst->stReadBlockHead);

    /* Add this instance to instance list */
    list_add_tail(&pstInst->stInstNode, &s_stBMParam.stInstHead);
    s_stBMParam.u16InstHandle++;
    LISTBUF_UNLOCK(s_stBMParam.stSem);

    return HI_SUCCESS;
}

HI_S32 ListBuf_Destroy(HI_HANDLE hBuf)
{
    LISTBUF_INST_S *pstInst = HI_NULL;
    HI_SIZE_T ulFlags;

    /* Find instance by handle */
    LISTBUF_FIND_INST(hBuf, pstInst);

    if (HI_NULL == pstInst)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }
    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* If has blocks, free them */
    if (!list_empty(&pstInst->stWriteBlockHead))
    {
        FreeBlockList(&pstInst->stWriteBlockHead);
    }

    if (!list_empty(&pstInst->stFreeBlockHead))
    {
        FreeBlockList(&pstInst->stFreeBlockHead);
    }

    if (!list_empty(&pstInst->stReadBlockHead))
    {
        FreeBlockList(&pstInst->stReadBlockHead);
    }

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    LISTBUF_LOCK(s_stBMParam.stSem);

    if (s_stBMParam.u16InstHandle == 0)
    {
        HI_ERR_VENC("Destroy failed! There is no channel!");
        LISTBUF_UNLOCK(s_stBMParam.stSem);

        return HI_FAILURE;
    }

    s_stBMParam.u16InstHandle--;

    /* Remove instance from list */
    list_del(&pstInst->stInstNode);

    LISTBUF_UNLOCK(s_stBMParam.stSem);

    /* Free resource */
    HI_KFREE_LISTBUF(pstInst);

    return HI_SUCCESS;
}

static HI_S32 CheckAllListEmpty(LISTBUF_INST_S* pstInst)
{
    if (list_empty(&pstInst->stWriteBlockHead)
        && list_empty(&pstInst->stFreeBlockHead)
        && list_empty(&pstInst->stReadBlockHead))
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

static HI_S32 GetOneWriteBuffer(HI_HANDLE hBuf, STRMMNG_BUF_S *pstBuf)
{
    LISTBUF_INST_S *pstInst   = HI_NULL;
    LISTBUF_BLOCK_S stBlock_tmp = {0};
    LISTBUF_BLOCK_S *pstBlock = HI_NULL;
    LISTBUF_BLOCK_S *pstBlockTail = HI_NULL;
    LISTBUF_BLOCK_S *pstBlockRead = HI_NULL;
    HI_U32 u32ReadOffset;
    HI_U32 u32WriteOffset;
    HI_U32 u32TailFree;
    HI_U32 u32HeadFree;
    HI_BOOL bAlloc = HI_FALSE;
    HI_SIZE_T ulFlags;

    LISTBUF_ASSERT_RETURN(pstBuf != HI_NULL, HI_ERR_LISTBUF_INVALID_PARA);

    LISTBUF_FIND_INST(hBuf, pstInst);
    LISTBUF_ASSERT_RETURN(pstInst != HI_NULL, HI_ERR_LISTBUF_INVALID_PARA);

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* Get buffer try times increase */
    pstInst->u32GetTry++;

    /* If paraset , don't need to calculate write/read offset */
    if ((pstBuf->u32NaluType != 1) && (pstBuf->u32NaluType != 5))
    {
        pstBuf->u32Addr = stBlock_tmp.u32Addr = pstInst->u32ParaSetPhyAddr;
        pstBuf->pu8VirAddr = stBlock_tmp.pu8VirAddr = pstInst->pu8ParaSetKnlVirAddr;
        goto get_attr;
    }
    /* If empty, write from start */
    else if (CheckAllListEmpty(pstInst) == HI_SUCCESS)
    {
        pstBuf->u32Addr = stBlock_tmp.u32Addr = pstInst->u32PhyAddr;
        pstBuf->pu8VirAddr = stBlock_tmp.pu8VirAddr = pstInst->pu8KnlVirAddr;

        goto get_attr;
    }
    /* Else, find write offset and read offset */
    else
    {
        pstBlockTail = FindAllFirstTailFrameBlock(pstInst);

        if (pstBlockTail == HI_NULL)/*only have one para set node in writting list*/
        {
            pstBuf->u32Addr = stBlock_tmp.u32Addr = pstInst->u32PhyAddr;
            pstBuf->pu8VirAddr = stBlock_tmp.pu8VirAddr = pstInst->pu8KnlVirAddr;

            goto get_attr;
        }
        else
        {
            u32WriteOffset = pstBlockTail->u32Addr + pstBlockTail->u32Size - pstInst->u32PhyAddr;
            pstBlockRead = FindAllFirstHeadFrameBlock(pstInst);

            if (pstBlockRead != HI_NULL)
            {
                u32ReadOffset = pstBlockRead->u32Addr - pstInst->u32PhyAddr;
            }
            else
            {
                LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

                return HI_ERR_LISTBUF_NO_MEMORY;
            }
        }
    }

    /* Normal: write pointer after read pointer, the free area isn't continuous */
    if (u32ReadOffset <= u32WriteOffset)
    {
        u32TailFree = pstInst->u32Size - u32WriteOffset;
        u32HeadFree = u32ReadOffset;

        if (u32TailFree >= pstBuf->u32Size)
        {
            bAlloc = HI_TRUE;
        }
        else if (u32HeadFree >= pstBuf->u32Size)
        {
            bAlloc = HI_TRUE;

            /* Alloc from head */
            u32WriteOffset = 0;
       }
    }
    /* Reverse: write pointer before read pointer, the free area is continuous , size is enough*/
    else if ((u32ReadOffset - u32WriteOffset) >= pstBuf->u32Size)
    {
        bAlloc = HI_TRUE;
    }

    /* Allocate fail, return */
    if (!bAlloc)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);
        return HI_ERR_LISTBUF_BUFFER_FULL;
    }

    /* Init block parameter */
    pstBuf->u32Addr = stBlock_tmp.u32Addr = pstInst->u32PhyAddr + u32WriteOffset;
    pstBuf->pu8VirAddr = stBlock_tmp.pu8VirAddr = pstInst->pu8KnlVirAddr + u32WriteOffset;
get_attr:
    /* Allocate new block */
    pstBlock = HI_KMALLOC_ATOMIC_LISTBUF(sizeof(LISTBUF_BLOCK_S));
    if (pstBlock == HI_NULL)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_ERR_LISTBUF_NO_MEMORY;
    }
    pstBlock->u32Addr = stBlock_tmp.u32Addr;
    pstBlock->pu8VirAddr = stBlock_tmp.pu8VirAddr;
    pstBlock->u32Size = pstBuf->u32Size;
    pstBlock->u32NaluType = pstBuf->u32NaluType;
    pstBlock->u32InvldByte = pstBuf->u32InvldByte;
    pstBlock->enstatus = LISTBUF_BLOCK_WRITING;

    /* Add block to list */
    list_add_tail(&pstBlock->stBlockNode, &pstInst->stWriteBlockHead);
    /* Get buffer OK times increase */
    pstInst->u32GetOK++;

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

static HI_S32 GetParaSetWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 ret = HI_SUCCESS;
    STRMMNG_BUF_S stBuf;
    HI_U8 StreamHeader[400];
    HI_U32 HeaderRealLength;
    HI_S32 iBytes;
    HI_U32* buf;
    HI_U32 i;
    HI_U8* pStreamHeader = (HI_U8*)StreamHeader;

    memset(pStreamHeader, 0, sizeof(StreamHeader));
    memset(&stBuf, 0, sizeof(STRMMNG_BUF_S));

    for (i = 0; i < 48; i++)
    {
        pstStreamInfo->pParaSetArray[i] = 0;
    }

    if ((pstInputInfo->PrependSpsPpsEnable == HI_TRUE) || (pstInputInfo->GetFrameNumOK == 1))
    {
        if (pstInputInfo->Protocol == VEDU_H264)
        {
            HeaderRealLength = pstInputInfo->SpsBits / 8 + pstInputInfo->PpsBits / 8;
            pstStreamInfo->ParaSetRealLen = HeaderRealLength;
            pstStreamInfo->ParaSetLen = D_VENC_ALIGN_UP(HeaderRealLength, 64);

            memcpy(pStreamHeader, pstInputInfo->pSpsStream, pstInputInfo->SpsBits / 8);
            pStreamHeader += pstInputInfo->SpsBits / 8;
            memcpy(pStreamHeader, pstInputInfo->pPpsStream, pstInputInfo->PpsBits / 8);

            stBuf.u32NaluType = H264_NALU_TYPE_PPS;
        }
        else
        {
            HeaderRealLength = pstInputInfo->SpsBits / 8 + pstInputInfo->PpsBits / 8 + pstInputInfo->VpsBits / 8;
            pstStreamInfo->ParaSetRealLen = HeaderRealLength;
            pstStreamInfo->ParaSetLen = D_VENC_ALIGN_UP(HeaderRealLength, 64);

            memcpy(pStreamHeader, pstInputInfo->pVpsStream, pstInputInfo->VpsBits / 8);
            pStreamHeader += pstInputInfo->VpsBits / 8;

            memcpy(pStreamHeader, pstInputInfo->pSpsStream, pstInputInfo->SpsBits / 8);
            pStreamHeader += pstInputInfo->SpsBits / 8;

            memcpy(pStreamHeader, pstInputInfo->pPpsStream, pstInputInfo->PpsBits / 8);

            stBuf.u32NaluType = H265_NALU_TYPE_PPS;/*para set only use sps as Nalu Type*/
        }
        stBuf.u32Size = pstStreamInfo->ParaSetLen;
        stBuf.u32Addr = pstStreamInfo->SliceBuf.u32StartPhyAddr;
        stBuf.pu8VirAddr = pstStreamInfo->SliceBuf.pu8StartVirAddr;
        stBuf.u32InvldByte = stBuf.u32Size - HeaderRealLength;
        ret = GetOneWriteBuffer(hHandle, &stBuf);

        if (ret != HI_SUCCESS)
        {
            return ret;
        }

        iBytes = HeaderRealLength;
        buf = (HI_U32*)StreamHeader;

        for (i = 0; iBytes > 0; i++, iBytes -= 4)
        {
            pstStreamInfo->pParaSetArray[i] = buf[i] ;
        }
    }

    return HI_SUCCESS;
}

static HI_VOID GetStrmBufInfoForSlice(STRMMNG_BUF_S *pstBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo, HI_U32 BufNum)
{
    HI_U32 BufferSize = 0;
    HI_U32 CheckBufSize = 0;
    HI_U32 MaxBufSize = 0;
    memset(pstBuf, 0, sizeof(STRMMNG_BUF_S));
    if (BufNum == 1)
    {
        BufferSize = pstInputInfo->TargetBits * BUF_SIZE_MULT / 8;
        CheckBufSize = pstInputInfo->TargetBits * BUF_SIZE_MULT_CHECK / 8;
    }
    else
    {
        BufferSize = pstInputInfo->TargetBits * BUF_SIZE_MULT_SPLIT / 8;
        CheckBufSize = pstInputInfo->TargetBits * BUF_SIZE_MULT_SPLIT_CHECK / 8;
    }

    pstBuf->u32Size = D_VENC_ALIGN_UP(BufferSize / BufNum, 64);

    if ((pstBuf->u32Size * BufNum) > pstStreamInfo->StrmBufSize)
    {
        MaxBufSize = (pstStreamInfo->StrmBufSize - 64 * HI_VENC_SLICE_NUM) / BufNum;
    }
    else
    {
        MaxBufSize = BufferSize / BufNum;
    }

    pstBuf->u32Size = D_VENC_ALIGN_UP(MaxBufSize, 64);
    pstBuf->u32InvldByte = pstBuf->u32Size - MaxBufSize;
    pstStreamInfo->CurStrmBufSize = D_VENC_ALIGN_UP(CheckBufSize, 64);

    if (pstInputInfo->Protocol != VEDU_H265)
    {
        pstBuf->u32NaluType = (pstInputInfo->IsIntraPic) ?  H264_NALU_TYPE_IDR : H264_NALU_TYPE_P;
    }
    else
    {
        pstBuf->u32NaluType = (pstInputInfo->IsIntraPic) ?  H265_NALU_TYPE_IDR : H265_NALU_TYPE_P;
    }
}

static HI_S32 PutOneWriteBuffer(HI_HANDLE hBuf, STRMMNG_BUF_S *pstBuf)
{
    LISTBUF_INST_S *pstInst   = HI_NULL;
    LISTBUF_BLOCK_S *pstBlock = HI_NULL;
    HI_SIZE_T ulFlags;

    if (pstBuf == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }
    LISTBUF_FIND_INST(hBuf, pstInst);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }
    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* Put buffer try times increase */
    pstInst->u32PutTry++;

    /* Find the tail block */
    pstBlock = FindListHeadBlock(&pstInst->stWriteBlockHead);
    if (pstBlock == HI_NULL)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_ERR_LISTBUF_WRITE_FREE_ERR;
    }

    if (pstBuf->u32Size > pstBlock->u32Size)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);
        HI_ERR_LISTBUF("Put size err:%d>%d\n", pstBuf->u32Size, pstBlock->u32Size);
        return HI_ERR_LISTBUF_WRITE_FREE_ERR;
    }

    /* The block must be WRITING status and its address must be right */
    if (IS_WRITING(pstBlock) && (pstBuf->u32Addr == pstBlock->u32Addr))
    {
        /* If size=0, drop this block */
        if (pstBuf->u32Size == 0)
        {
            /* Delete block from list */
            list_del(&pstBlock->stBlockNode);

            /* Free block resource */
            HI_KFREE_LISTBUF(pstBlock);

            pstInst->u32PutOK++;
            LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

            return HI_SUCCESS;
        }

        pstBlock->u32Size  = pstBuf->u32Size;
        pstBlock->u32InvldByte = pstBuf->u32InvldByte;
        pstBlock->bFrameEnd = pstBuf->bFrameEnd;
        pstBlock->u32Pts0Ms = pstBuf->u32Pts0Ms;
        pstBlock->u32Pts1Ms = pstBuf->u32Pts1Ms;
        pstBlock->enstatus = LISTBUF_BLOCK_FREE;
    }
    else
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);
        HI_ERR_LISTBUF("Put fail.\n");
        return HI_ERR_LISTBUF_WRITE_FREE_ERR;
    }
    /* Delete block from write list, add the free list */
    list_del(&pstBlock->stBlockNode);
    list_add_tail(&pstBlock->stBlockNode, &pstInst->stFreeBlockHead);

    /* Put buffer OK times increase */
    pstInst->u32PutOK++;

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

static HI_VOID PutParaSetBuf(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo, HI_U32 ParaSetLen)
{
    if ((pstInputInfo->PrependSpsPpsEnable == HI_TRUE) || (pstInputInfo->GetFrameNumOK == 1))
    {
        STRMMNG_BUF_S stBuf;
        memset(&stBuf, 0, sizeof(STRMMNG_BUF_S));
        stBuf.u32Size = ParaSetLen;
        stBuf.u32Addr = pstStreamInfo->SliceBuf.u32StartPhyAddr;
        stBuf.u32InvldByte = stBuf.u32Size - pstStreamInfo->ParaSetRealLen;
        stBuf.u32Pts0Ms = pstInputInfo->PTS0;
        stBuf.u32Pts1Ms = pstInputInfo->PTS1;
        stBuf.bFrameEnd = 0;
        PutOneWriteBuffer(hBuf, &stBuf);
    }
}

static HI_VOID PutSliceStrmBufNormal(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 i = 0, j = 0;
    HI_U32 RealSliceSize = 0;
    HI_U32 EndOfSlice = 0;
    HI_U32 BufNum = 0;
    HI_U32 SlicIdx = 0;
    STRMMNG_BUF_S  *pstBuf = pstStreamInfo->pstBuf;

    BufNum = pstInputInfo->SlcSplitEn ? HI_VENC_SLICE_NUM : 1;

    SlicIdx = pstStreamInfo->SliceIdx;

    for (i = SlicIdx; i < BufNum; i++)
    {
        RealSliceSize = pstInputInfo->SliceLength[i];
        EndOfSlice    = pstInputInfo->SliceIsEnd[i];
        if (RealSliceSize)
        {
            pstBuf[i].u32Size = D_VENC_ALIGN_UP(pstInputInfo->SliceLength[i], VEDU_MMZ_ALIGN);
            pstBuf[i].u32InvldByte = pstBuf[i].u32Size - pstInputInfo->SliceLength[i];
            pstBuf[i].u32Pts0Ms = pstInputInfo->PTS0;
            pstBuf[i].u32Pts1Ms = pstInputInfo->PTS1;
            pstBuf[i].bFrameEnd = EndOfSlice;
            pstStreamInfo->SliceIdx++;

            PutOneWriteBuffer(hBuf, &pstBuf[i]);
        }

        if (EndOfSlice)
        {
            for (j = pstStreamInfo->SliceIdx; j < BufNum; j++)
            {
                /*buf do not be used*/
                pstBuf[j].u32Size = 0;
                PutOneWriteBuffer(hBuf, &pstBuf[j]);
            }

            break;
        }

        if ((!RealSliceSize) && (!EndOfSlice))
        {
            break;
        }
    }
}

static HI_VOID PutSliceStrmBufAbnormal(HI_HANDLE hBuf, HI_U16 SlcSplitEn, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 i = 0;
    HI_U32 BufNum = 0;

    BufNum = SlcSplitEn ? HI_VENC_SLICE_NUM : 1;
    for (i = pstStreamInfo->SliceIdx; i < BufNum; i++)
    {
        pstStreamInfo->pstBuf[i].u32Size = 0;
        PutOneWriteBuffer(hBuf, &pstStreamInfo->pstBuf[i]);
    }
}

HI_S32 ListBuf_PutBufForRecode(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    pstStreamInfo->SliceIdx = 0;

    if (pstInputInfo->IsIntraPic)
    {
        PutParaSetBuf(hBuf, pstInputInfo, pstStreamInfo, 0);
    }

    PutSliceStrmBufAbnormal(hBuf, pstInputInfo->SlcSplitEn, pstStreamInfo);

    return HI_SUCCESS;
}

static HI_S32 GetStreamWriteBuffer(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    STRMMNG_BUF_S stBuf;
    HI_U32 BufNum = 0;
    HI_U32 i = 0, j = 0;
    HI_U32 ret = HI_SUCCESS;

    *(pstStreamInfo->StrmBufRpVirAddr) = 0;
    *(pstStreamInfo->StrmBufWpVirAddr) = 0;
    BufNum = pstInputInfo->SlcSplitEn ? HI_VENC_SLICE_NUM : 1;

    for (i = 0; i < 16; i++)
    {
        pstStreamInfo->pStreamBufAddrArray[i] = 0;
        pstStreamInfo->pStreamBufLenArray[i] = 0;
    }

    GetStrmBufInfoForSlice(&stBuf, pstInputInfo, pstStreamInfo, BufNum);
    for (i = 0; i < BufNum; i++)
    {
        ret = GetOneWriteBuffer(hBuf, &stBuf);

        if (ret != HI_SUCCESS)
        {
            if (pstInputInfo->IsIntraPic)
            {
                PutParaSetBuf(hBuf, pstInputInfo, pstStreamInfo, 0);
            }

            for (j = 0; j < i; j++)
            {
               memset(&stBuf, 0, sizeof(STRMMNG_BUF_S));
               stBuf.u32Addr = pstStreamInfo->pstBuf[j].u32Addr;
               stBuf.u32Size = 0;
               PutOneWriteBuffer(hBuf, &stBuf);
            }

            return ret;
        }
        pstStreamInfo->pstBuf[i] = stBuf;
        pstStreamInfo->pStreamBufAddrArray[i] = stBuf.u32Addr;
        pstStreamInfo->pStreamBufLenArray[i] = stBuf.u32Size;
    }
    pstStreamInfo->bFirstSlcOneFrm = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 ListBuf_GetWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 ret = HI_SUCCESS;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_FAILURE;
    }

    if (pstInputInfo->IsIntraPic)
    {
        ret = GetParaSetWriteBuffer(hHandle, pstInputInfo, pstStreamInfo);

        if (ret != HI_SUCCESS)
        {
            return ret;
        }
    }

    ret =  GetStreamWriteBuffer(hHandle, pstInputInfo, pstStreamInfo);

    return ret;
}

HI_S32 ListBuf_PutWriteBufSlices(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    if ((pstInputInfo->IsIntraPic) && (pstStreamInfo->bFirstSlcOneFrm))
    {
        pstStreamInfo->bFirstSlcOneFrm = HI_FALSE;
        PutParaSetBuf(hBuf, pstInputInfo, pstStreamInfo, pstStreamInfo->ParaSetLen);
    }

    PutSliceStrmBufNormal(hBuf, pstInputInfo, pstStreamInfo);

    return HI_SUCCESS;
}

HI_S32 ListBuf_PutWriteBufSlicesAb(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    if ((pstInputInfo->IsIntraPic) && (pstStreamInfo->bFirstSlcOneFrm == HI_TRUE))
    {
        pstStreamInfo->bFirstSlcOneFrm = HI_FALSE;
        PutParaSetBuf(hBuf, pstInputInfo, pstStreamInfo, 0);
    }

    PutSliceStrmBufAbnormal(hBuf, pstInputInfo->SlcSplitEn, pstStreamInfo);

    pstStreamInfo->TooFewBufferSkip++;

    return HI_SUCCESS;
}


HI_S32 ListBuf_PutWriteBuf(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    if (!pstInputInfo->VencBufFull && !pstInputInfo->VencPbitOverflow)
    {
        ListBuf_PutWriteBufSlices(hBuf, pstInputInfo, pstStreamInfo);
    }
    else
    {
        ListBuf_PutWriteBufSlicesAb(hBuf, pstInputInfo, pstStreamInfo);
    }

    return HI_SUCCESS;
}

static HI_S32 AcqOneReadBuffer(HI_HANDLE hBuf, STRMMNG_BUF_S *pstBuf)
{
    LISTBUF_INST_S* pstInst   = HI_NULL;
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;
    HI_SIZE_T ulFlags;

    if (pstBuf == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }

    pstBuf->u32Size = 0;

    LISTBUF_FIND_INST(hBuf, pstInst);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* Request buffer try times increase */
    pstInst->u32RecvTry++;

    /* Find first free block */
    pstBlock = FindListHeadBlock(&pstInst->stFreeBlockHead);

    if (pstBlock == HI_NULL)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);
        return HI_ERR_LISTBUF_BUFFER_EMPTY;
    }

    /* Read from the block */
    pstBuf->u32Addr = pstBlock->u32Addr;
    pstBuf->pu8VirAddr = pstBlock->pu8VirAddr;
    pstBuf->u32Size = pstBlock->u32Size;
    pstBuf->u32NaluType = pstBlock->u32NaluType;
    pstBuf->u32InvldByte = pstBlock->u32InvldByte;
    pstBuf->bFrameEnd = pstBlock->bFrameEnd;
    pstBuf->u32Pts0Ms  = pstBlock->u32Pts0Ms ;
    pstBuf->u32Pts1Ms  = pstBlock->u32Pts1Ms ;

    /* Change status */
    pstBlock->enstatus = LISTBUF_BLOCK_READING;

    list_del(&pstBlock->stBlockNode);
    list_add_tail(&pstBlock->stBlockNode, &pstInst->stReadBlockHead);

    /* Request buffer OK times increase */
    pstInst->u32RecvOK++;

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 ListBuf_GetAcquireStreamInfo(HI_HANDLE hBuf, HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                     VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_U32 AddrOffset = 0;

    pstStream->VirAddr   = (HI_VIRT_ADDR_T)(pstVeduPacket->pVirtAddr[0]);
    if ((pstVeduPacket->NaluType == 1) || (pstVeduPacket->NaluType == 5))/*I frame or P frame*/
    {
        AddrOffset = pstStream->VirAddr - (HI_VIRT_ADDR_T)StartVirAddr - 64;
    }
    else
    {
        AddrOffset = 0;
    }

    pstStream->u32SlcLen = pstVeduPacket->SlcLen[0];
    pstStream->bFrameEnd = pstVeduPacket->bFrameEnd;
    pstStream->u32PtsMs = pstVeduPacket->PTS0;
    if (Protocol == VEDU_H265)
    {
        pstStream->enDataType.enHEVCEType = TransNaluTypeNumForH265(pstVeduPacket->NaluType);
    }
    else
    {
        pstStream->enDataType.enH264EType = pstVeduPacket->NaluType;
    }

    if (pstStream->u32SlcLen > 0)
    {
        pstBufOffSet->u32StrmBufOffset[0] = AddrOffset;
    }

    return HI_SUCCESS;
}

HI_S32 ListBuf_AcquireBitStream(HI_HANDLE hBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket)
{
    STRMMNG_BUF_S stBuf;
    HI_S32 s32Ret;

    memset(&stBuf, 0, sizeof(STRMMNG_BUF_S));
    s32Ret = AcqOneReadBuffer(hBuf, &stBuf);

    pstVeduPacket->pVirtAddr[0] = (HI_VOID*)(stBuf.pu8VirAddr);
    pstVeduPacket->NaluType     = stBuf.u32NaluType;
    pstVeduPacket->SlcLen[0]    = stBuf.u32Size - stBuf.u32InvldByte;
    pstVeduPacket->bFrameEnd    = (stBuf.bFrameEnd == 0) ? HI_FALSE : HI_TRUE;
    pstVeduPacket->PTS0         = stBuf.u32Pts0Ms;
    pstVeduPacket->InvldByte    = stBuf.u32InvldByte;
    pstStreamInfo->StreamTotalByte += pstVeduPacket->SlcLen[0];

    return s32Ret;
}

HI_S32 ListBuf_GetFreeLength(LISTBUF_INST_S* pstInst, HI_U32 NaluType)
{
    LISTBUF_BLOCK_S* pstBlockTail = HI_NULL;
    LISTBUF_BLOCK_S* pstBlockRead = HI_NULL;
    HI_U32 u32ReadOffset;
    HI_U32 u32WriteOffset;

    /* If paraset , don't need to calculate write/read offset */
    if ((NaluType != 1) && (NaluType != 5))
    {
        return HI_SUCCESS;
    }
    /* If empty, write from start */
    else if (CheckAllListEmpty(pstInst) == HI_SUCCESS)
    {
        pstInst->StrmHeadFree = pstInst->u32Size;
        pstInst->StrmTailFree = 0;
        return HI_SUCCESS;
    }
    /* Else, find write offset and read offset */
    else
    {
        pstBlockTail = FindAllFirstTailFrameBlock(pstInst);

        if (pstBlockTail == HI_NULL)/*only have one para set node in writting list*/
        {
            pstInst->StrmHeadFree = pstInst->u32Size;
            pstInst->StrmTailFree = 0;
            return HI_SUCCESS;
        }
        else
        {
            u32WriteOffset = pstBlockTail->u32Addr + pstBlockTail->u32Size - pstInst->u32PhyAddr;
            pstBlockRead = FindAllFirstHeadFrameBlock(pstInst);
            if (pstBlockRead != HI_NULL)
            {
                u32ReadOffset = pstBlockRead->u32Addr - pstInst->u32PhyAddr;
            }
            else
            {
                return HI_FAILURE;
            }
        }
    }

    /* Normal: write pointer after read pointer, the free area isn't continuous */
    if (u32ReadOffset <= u32WriteOffset)
    {
        pstInst->StrmTailFree = pstInst->u32Size - u32WriteOffset;
        pstInst->StrmHeadFree = u32ReadOffset;
    }
    /* Reverse: write pointer before read pointer, the free area is continuous , size is enough*/
    else
    {
        pstInst->StrmTailFree = -1;
        pstInst->StrmHeadFree = u32ReadOffset - u32WriteOffset;
    }

    return HI_SUCCESS;
}

HI_S32 ListBuf_RlsReadBuffer(HI_HANDLE hBuf, STRMMNG_BUF_S *pstBuf)
{
    HI_U32 u32PhyAddr;
    LISTBUF_INST_S *pstInst   = HI_NULL;
    LISTBUF_BLOCK_S *pstBlock = HI_NULL;
    HI_U32 NaluType = 0;
    HI_SIZE_T ulFlags;

    if (pstBuf == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }

    LISTBUF_FIND_INST(hBuf, pstInst);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_LISTBUF_INVALID_PARA;
    }

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* Release buffer try times increase */
    pstInst->u32RlsTry++;
    NaluType = pstBuf->u32NaluType;

    /* Find block by address */
    if ((NaluType == 1) || (NaluType == 5))
    {
        u32PhyAddr = pstBuf->pu8VirAddr - pstInst->pu8KnlVirAddr + pstInst->u32PhyAddr;/*pstBuf why has no phyaddr*/
    }
    else
    {
        u32PhyAddr = pstInst->u32ParaSetPhyAddr;
    }

    pstBlock = FindListHeadBlock(&pstInst->stReadBlockHead);

    if ((pstBlock == HI_NULL) || (u32PhyAddr != pstBlock->u32Addr))
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_ERR_LISTBUF_READ_FREE_ERR;
    }

    /* Support free out-of-order */
    if (IS_READING(pstBlock))
    {
        /* Delete block from list */
        list_del(&pstBlock->stBlockNode);

        /* Free block resource */
        HI_KFREE_LISTBUF(pstBlock);
    }
    else
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_ERR_LISTBUF_READ_FREE_ERR;
    }

    /* Release buffer OK times increase */
    if (ListBuf_GetFreeLength(pstInst, NaluType) != HI_SUCCESS)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_ERR_LISTBUF_READ_FREE_ERR;
    }

    pstInst->u32RlsOK++;
    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 ListBuf_GetRleaseStreamInfo(HI_HANDLE hBuf, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                    VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket)
{
    HI_U32 NaluType = 0;
    HI_VOID*  pBase = pstStreamInfo->StreamMMZBuf.pu8StartVirAddr + VEDU_MMZ_ALIGN;
    VENC_STREAM_S  stStream = pstAcqStrm->stStream;

    if (Protocol == VEDU_H264)
    {
        if (stStream.enDataType.enH264EType == HI_UNF_H264E_NALU_PPS)
        {
            stStream.VirAddr  = (HI_VIRT_ADDR_T)(pstStreamInfo->SliceBuf.pu8StartVirAddr + pstAcqStrm->H264_stream_off);
        }
        else
        {
            stStream.VirAddr  = (HI_VIRT_ADDR_T)(pBase + pstAcqStrm->H264_stream_off);
        }
        NaluType = stStream.enDataType.enH264EType;
    }
    else
    {
        if (stStream.enDataType.enHEVCEType == HI_UNF_HEVCE_NALU_PPS)
        {
            stStream.VirAddr  = (HI_VIRT_ADDR_T)(pstStreamInfo->SliceBuf.pu8StartVirAddr + pstAcqStrm->H264_stream_off);
        }
        else
        {
            stStream.VirAddr  = (HI_VIRT_ADDR_T)(pBase + pstAcqStrm->H264_stream_off);
        }
        NaluType = InverseTransNaluTypeNumForH265(stStream.enDataType.enHEVCEType);
    }

    pstVeduPacket->pVirtAddr[0] = (HI_VOID*)stStream.VirAddr;
    pstVeduPacket->NaluType     = NaluType;

    return HI_SUCCESS;
}

HI_S32 ListBuf_ReleaseBitStream(HI_HANDLE hBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pstVeduPacket)
{
    STRMMNG_BUF_S stBuf;
    HI_S32 s32Ret;

    stBuf.pu8VirAddr = (HI_U8*)pstVeduPacket->pVirtAddr[0];
    stBuf.u32NaluType = pstVeduPacket->NaluType;
    s32Ret = ListBuf_RlsReadBuffer(hBuf, &stBuf);

    return s32Ret;
}

static HI_S32 CheckBufferSize(HI_HANDLE hBuf, STRMMNG_BUF_S *pstBuf)
{
    LISTBUF_INST_S *pstInst   = HI_NULL;
    LISTBUF_BLOCK_S *pstBlockTail = HI_NULL;
    LISTBUF_BLOCK_S *pstBlockRead = HI_NULL;
    HI_U32 u32ReadOffset;
    HI_U32 u32WriteOffset;
    HI_U32 u32TailFree;
    HI_U32 u32HeadFree;
    HI_BOOL bAlloc = HI_FALSE;
    HI_SIZE_T ulFlags;

    LISTBUF_ASSERT_RETURN(pstBuf != HI_NULL, HI_ERR_LISTBUF_INVALID_PARA);

    LISTBUF_FIND_INST(hBuf, pstInst);
    LISTBUF_ASSERT_RETURN(pstInst != HI_NULL, HI_ERR_LISTBUF_INVALID_PARA);

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    /* Buffer full */
    if (CheckAllListEmpty(pstInst) == HI_SUCCESS)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_SUCCESS;
    }
    /* Else, find write offset and read offset */
    else
    {
        pstBlockTail = FindAllFirstTailFrameBlock(pstInst);

        if (pstBlockTail == HI_NULL)/*only have one para set node in writting list*/
        {
            LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

            return HI_SUCCESS;
        }
        else
        {
            u32WriteOffset = pstBlockTail->u32Addr + pstBlockTail->u32Size - pstInst->u32PhyAddr;
            pstBlockRead = FindAllFirstHeadFrameBlock(pstInst);

            if (pstBlockRead != HI_NULL)
            {
                u32ReadOffset = pstBlockRead->u32Addr - pstInst->u32PhyAddr;
            }
            else
            {
                LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

                return HI_ERR_LISTBUF_BUFFER_FULL;
            }
        }
    }

    /* Normal: write pointer after read pointer, the free area isn't continuous */
    if (u32ReadOffset <= u32WriteOffset)
    {
        u32TailFree = pstInst->u32Size - u32WriteOffset;
        u32HeadFree = u32ReadOffset;
        if (u32TailFree >= pstBuf->u32Size)
        {
            bAlloc = HI_TRUE;
        }
        else if (u32HeadFree >= pstBuf->u32Size)
        {
            bAlloc = HI_TRUE;
        }
    }
    /* Reverse: write pointer before read pointer, the free area is continuous , size is enough*/
    else if ((u32ReadOffset - u32WriteOffset) >= pstBuf->u32Size)
    {
        bAlloc = HI_TRUE;
    }

    /* Allocate fail, return */
    if (!bAlloc)
    {
        LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);
        return HI_ERR_LISTBUF_BUFFER_FULL;
    }
    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 ListBuf_CheckBufferSize(HI_HANDLE hBuf, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize)
{
    STRMMNG_BUF_S stBuf;

    memset(&stBuf, 0, sizeof(STRMMNG_BUF_S));
    stBuf.u32Size = D_VENC_ALIGN_UP(CurStrmBufSize, 64);

    if (stBuf.u32Size > StrmBufSize)
    {
        stBuf.u32Size = D_VENC_ALIGN_UP(StrmBufSize, 64);
    }

    if (CheckBufferSize(hBuf, &stBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_U32 ListBuf_GetWrittenLen(HI_HANDLE hBuf)
{
    LISTBUF_INST_S *pstInst   = HI_NULL;
    struct list_head *pstFreeBlockHead = HI_NULL;
    struct list_head *pstList = HI_NULL;
    LISTBUF_BLOCK_S* pstBlock = HI_NULL;
    HI_SIZE_T ulFlags;
    HI_U32 StrmLen = 0;

    LISTBUF_FIND_INST(hBuf, pstInst);
    LISTBUF_ASSERT_RETURN(pstInst != HI_NULL, 0);

    LISTBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstFreeBlockHead = &pstInst->stFreeBlockHead;

    if (!list_empty(pstFreeBlockHead))
    {
        pstList = pstInst->stFreeBlockHead.next;

        while (pstFreeBlockHead != pstList)
        {
            pstBlock = list_entry(pstList, LISTBUF_BLOCK_S, stBlockNode);
            StrmLen += pstBlock->u32Size - pstBlock->u32InvldByte;

            pstList = pstList->next;
        }
    }

    LISTBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return StrmLen;
}

HI_U32 ListBuf_CalSlcSize(HI_HANDLE hBuf, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize)
{
    HI_U32 SliceNum = 0;
    HI_U32 LineHeight = 0;
    HI_U32 EverSliceLineNum = 0;
    HI_U32 PicHeightAlign = 0;
    const HI_U32 LcuSizeHevc = 32;
    const HI_U32 LcuSizeH264 = 16;
    HI_U32 SlcSize = 0;

    LineHeight = (Protocol == VEDU_H264) ? LcuSizeH264 : LcuSizeHevc;
    PicHeightAlign = D_VENC_ALIGN_UP(PicHeight, LineHeight);
    SliceNum = (PicHeightAlign +  LineHeight - 1) / LineHeight;
    EverSliceLineNum = (SliceNum + HI_VENC_SLICE_NUM - 1) / HI_VENC_SLICE_NUM;

    /*the info about splitsize logic gets is the real value minus 1*/
    SlcSize = EverSliceLineNum - 1;

    return SlcSize;
}

HI_U32 ListBuf_GetBitBufSize(HI_HANDLE hBuf, HI_U32 StreamBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize)
{
    return StreamBufSize;
}

HI_S32 ListBuf_AllocStreamBuf(HI_HANDLE hBuf, VENC_BUFFER_S* pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 AllocBufSize = 0;
    HI_U32 RcnBufSize = 0;

    if (pStreamMMZBuf == HI_NULL)
    {
        return HI_FAILURE;
    }

    RcnBufSize = LumaSize * 3 + 0x600000;
    AllocBufSize = (BitBufSize + RcnBufSize) * 3 / 2;

    s32Ret = HI_DRV_VENC_AllocAndMap("VENC_SteamBuf", HI_NULL, AllocBufSize, 64, pStreamMMZBuf);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("HI_DRV_VENC_AllocAndMap failed\n");
    }

    return s32Ret;
}

static HI_S32 AllocParaSetBuf(VENC_BUFFER_S* pSliceMMZBuf)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 BitBufSize = 4096;

    s32Ret = HI_DRV_VENC_MMZ_AllocAndMap("VENC_ParaSetBuf", HI_NULL, BitBufSize, 64, pSliceMMZBuf);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("ParaSetBuf HI_DRV_VENC_AllocAndMap failed\n");
    }

    return s32Ret;
}

HI_S32 ListBuf_AllocParaSetBufAddr(HI_HANDLE hBuf, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR)
{
    if (AllocParaSetBuf(pParaSetBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    memset(pParaSetBuf->pu8StartVirAddr, 0, 4096);
    *pParaSetADDR = pParaSetBuf->u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_S32 ListBuf_RlsParaSetBufAddr(HI_HANDLE hBuf, VENC_BUFFER_S* pParaSetBuf)
{
    HI_DRV_VENC_MMZ_UnmapAndRelease(pParaSetBuf);

    return HI_SUCCESS;
}

HI_S32 ListBuf_ResetBuffer(HI_HANDLE hBuf, HI_U32 Protocol)
{
    return HI_SUCCESS;
}

HI_S32 ListBuf_GetRleaseStreamInfoIntar(HI_HANDLE hBuf, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket)
{
    return HI_SUCCESS;
}

#ifdef VENC_SUPPORT_JPGE
HI_S32 ListBuf_WriteHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    return HI_SUCCESS;
}

HI_S32 ListBuf_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    return HI_SUCCESS;
}

HI_S32 ListBuf_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    return HI_SUCCESS;
}

HI_S32 ListBuf_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S* pstStreamInfo, VeduEfl_NALU_S* pstVeduPacket,
                             VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S* pstBufOffSet)
{
    return HI_SUCCESS;
}
#endif


