#include "strm_mng_recyclebuf.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_mem.h"
#include <linux/delay.h>
#include "hi_error_mpi.h"

/***************************** Static Definition *****************************/
static RECYCLEBUF_GLOBAL_S s_stRBParam =
{
    .u16InstHandle = 0,
    .stInstHead = LIST_HEAD_INIT(s_stRBParam.stInstHead)
};

#define HI_KMALLOC_ATOMIC_RECYCLEBUF(size)     HI_KMALLOC(HI_ID_VENC, size, GFP_ATOMIC)
#define HI_KFREE_RECYCLEBUF(addr)       HI_KFREE(HI_ID_VENC, addr)

#define RECYCLEBUF_FIND_INST(hInst, pInst, ulFlags) \
    { \
        struct list_head* pos; \
        struct list_head* n; \
        RECYCLEBUF_INST_S* pstTmp; \
        pInst = HI_NULL; \
        RECYCLEBUF_SPIN_LOCK(s_stRBParam.stSpinLock, ulFlags); \
        list_for_each_safe(pos, n, &s_stRBParam.stInstHead) \
        { \
            pstTmp = list_entry(pos, RECYCLEBUF_INST_S, stInstNode); \
            if (hInst == pstTmp->hBuf) \
            { \
                pInst = pstTmp; \
                break; \
            } \
        } \
        RECYCLEBUF_SPIN_UNLOCK(s_stRBParam.stSpinLock, ulFlags); \
    }

/************************************static Func**********************************************/
static HI_S32 BufferInit(VALG_CRCL_BUF_S* pstCB, STRMMNG_INST_CONFIG_S* pstConfig)
{
    if (((pstConfig->u32Size & (WORD_ALIGN - 1)) != 0) || (pstConfig->u32Size < pstConfig->u32RsvByte))
    {
        return HI_FAILURE;
    }
    else
    {
        pstCB->u32BufLen = pstConfig->u32Size;
    }

    if ((pstConfig->u32RsvByte == 0) || (pstConfig->u32RsvByte & (WORD_ALIGN - 1)) != 0)
    {
        return HI_FAILURE;
    }
    else
    {
        pstCB->u32RsvByte = pstConfig->u32RsvByte;
    }

    pstCB->pBase = pstConfig->pu8KnlVirAddr;
    pstCB->u32PhyAddr = pstConfig->u32PhyAddr;
    pstCB->u32RdHead = 0;
    pstCB->u32RdTail = 0;
    pstCB->u32WrHead = 0;
    pstCB->u32WrTail = 0;

    return HI_SUCCESS;
}

static HI_VOID BufUpdateWp(VALG_CRCL_BUF_S* pstCB)
{
    pstCB->u32WrTail = pstCB->u32WrHead;

    return;
}

static HI_U32 BufGetFreeLen(VALG_CRCL_BUF_S* pstCB)
{
    HI_U32 u32FreeLen;

    if (pstCB->u32WrHead >= pstCB->u32RdTail)/* Write head before read tail, that did not turn back buffer*/
    {
        /*Calculate data length in buffer when not turn back yet*/
        u32FreeLen = pstCB->u32BufLen - (pstCB->u32WrHead - pstCB->u32RdTail) - pstCB->u32RsvByte;
    }
    else
    {
        /*Calculate data length in buffer when not turn back yet*/
        u32FreeLen = pstCB->u32RdTail - pstCB->u32WrHead - pstCB->u32RsvByte;
    }

    return u32FreeLen;
}

static HI_S32 BufWrite(VALG_CRCL_BUF_S* pstCB, HI_VOID* pVirtSrc, HI_U32 u32WrLen)
{
    HI_U32 freeLen;
    HI_U32 i;
    VALG_CB_INFO_S stWrInfo;
    CPU_WORD*  pDst;
    CPU_WORD*  pSrc;
    HI_U32 u32WrHeadNew = 0;

    /* added by juchaodong */
    if (pVirtSrc == NULL) /* When VEDU finish encoding, update write head*/
    {
        pstCB->u32WrHead = u32WrLen; /* u32WrLen is reuse as VEDU's write pointer */
        return HI_SUCCESS;
    }

    /* add end */

    if ((u32WrLen & (WORD_ALIGN - 1)) != 0)
    {
        return HI_FAILURE;
    }

    /*Call get buffer data len function, get the actual len*/
    freeLen = BufGetFreeLen(pstCB);

    /*No enough space to write*/
    if (freeLen < u32WrLen)
    {
        return HI_FAILURE;
    }

    /*Get enough space to write two data packets*/
    /*If write head cross or even reach the bottom of buffer, turn back*/
    if ((pstCB->u32WrHead + u32WrLen) >= pstCB->u32BufLen)
    {
        /*Calculate two packets's length and addr*/
        stWrInfo.pSrc[0]   = (ADDR_UNIT*)pstCB->pBase + pstCB->u32WrHead;
        stWrInfo.u32Len[0] = pstCB->u32BufLen - pstCB->u32WrHead;
        stWrInfo.pSrc[1]   = pstCB->pBase;
        stWrInfo.u32Len[1] = u32WrLen - stWrInfo.u32Len[0];

        /*  pstCB->u32WrHead = stWrInfo.u32Len[1];
            write head point to start of the next packet */
        u32WrHeadNew = stWrInfo.u32Len[1];
    }
    else
    {
        stWrInfo.pSrc[0]   = (ADDR_UNIT*)pstCB->pBase + pstCB->u32WrHead;
        stWrInfo.u32Len[0] = u32WrLen;
        stWrInfo.pSrc[1]   = (ADDR_UNIT*)stWrInfo.pSrc[0] + u32WrLen;
        stWrInfo.u32Len[1] = 0;       /*The second packet length is 0*/

        /*   pstCB->u32WrHead += u32WrLen;
             write head point to start of the next packet */
        u32WrHeadNew = pstCB->u32WrHead + u32WrLen;
    }

    /* y45339 copy end*/

    /*The first input packet copy to buffer*/
    pSrc = (CPU_WORD*)pVirtSrc;
    pDst = (CPU_WORD*)stWrInfo.pSrc[0];
    i = stWrInfo.u32Len[0] / sizeof(CPU_WORD);
    while (i--)
    {
        *pDst++ = *pSrc++;
    }

    /*The second input packet copy to buffer*/
    pDst = (CPU_WORD*)stWrInfo.pSrc[1];
    i = stWrInfo.u32Len[1] / sizeof(CPU_WORD);
    while (i--)
    {
        *pDst++ = *pSrc++;
    }

    pstCB->u32WrHead = u32WrHeadNew;

    return HI_SUCCESS;
}

static HI_S32 GetParaSetWriteBuffer(VALG_CRCL_BUF_S* pstStrBuf, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    if (!pstInputInfo->Recode)
    {
        if ((pstInputInfo->PrependSpsPpsEnable == HI_TRUE) || (pstInputInfo->GetFrameNumOK == 1))
        {
            VeduEfl_NaluHdr_S NaluHdr;

            if (pstInputInfo->Protocol != VEDU_H265)
            {
                NaluHdr.PacketLen  = 128;
                NaluHdr.InvldByte  = 64 - pstInputInfo->SpsBits / 8;
                NaluHdr.bLastSlice = 0;
                NaluHdr.Type = 7;

                NaluHdr.PTS0 = pstInputInfo->PTS0;
                NaluHdr.PTS1 = pstInputInfo->PTS1;

                BufWrite(pstStrBuf, &NaluHdr, 64);
                BufWrite(pstStrBuf, pstInputInfo->pSpsStream, 64);

                NaluHdr.InvldByte = 64 - pstInputInfo->PpsBits / 8;
                NaluHdr.Type = 8;

                BufWrite(pstStrBuf, &NaluHdr, 64 );
                BufWrite(pstStrBuf, pstInputInfo->pPpsStream, 64);
            }
            else
            {
                // vps
                NaluHdr.PacketLen  = 128;
                NaluHdr.InvldByte  = 64 - pstInputInfo->VpsBits / 8;
                NaluHdr.bLastSlice = 0;
                NaluHdr.Type       = 32;
                NaluHdr.bBotField  = 0;
                NaluHdr.bField     = 0;

                NaluHdr.PTS0  = pstInputInfo->PTS0;
                NaluHdr.PTS1  = pstInputInfo->PTS1;

                BufWrite(pstStrBuf, &NaluHdr, 64);
                BufWrite(pstStrBuf, pstInputInfo->pVpsStream, 64);

                // sps
                NaluHdr.InvldByte  = 64 - pstInputInfo->SpsBits / 8;
                NaluHdr.Type       = 33;

                BufWrite(pstStrBuf, &NaluHdr, 64);
                BufWrite(pstStrBuf, pstInputInfo->pSpsStream, 64);

                // pps
                NaluHdr.InvldByte = 64 - pstInputInfo->PpsBits / 8;
                NaluHdr.Type      = 34;

                BufWrite(pstStrBuf, &NaluHdr, 64);
                BufWrite(pstStrBuf, pstInputInfo->pPpsStream, 64);
            }

            BufUpdateWp(pstStrBuf);
        }
    }

    return HI_SUCCESS;
}

static HI_S32 GetStreamWriteBuffer(VALG_CRCL_BUF_S* pstStrBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    *(pstStreamInfo->StrmBufRpVirAddr) = pstStrBuf->u32RdTail;
    *(pstStreamInfo->StrmBufWpVirAddr) = pstStrBuf->u32WrHead;

    pstStreamInfo->CurStrmBufSize = D_VENC_ALIGN_UP(pstInputInfo->TargetBits * BUF_SIZE_MULT / 8, 64);

    return HI_SUCCESS;
}

static HI_S32 IsBufVaild(VALG_CRCL_BUF_S* pstCB)
{
    /*  HI_U32 u32Rh;*/

    /* Judge input length is correct
     * Notes: read head cannot cross write tail after update
     * Notes:
     * 1. The write tail pointer does not turn back
     * 2. The write tail pointer turn back
     *    1)read head does not turn back, read head will not cross write tail
     *    2)read head turn back;
     */
    if (((pstCB->u32RdTail <= pstCB->u32RdHead)
         && (pstCB->u32RdHead <= pstCB->u32WrTail)
         && (pstCB->u32WrTail <= pstCB->u32WrHead))
        || ((pstCB->u32WrHead <= pstCB->u32RdTail)
            && (pstCB->u32RdTail <= pstCB->u32RdHead)
            && (pstCB->u32RdHead <= pstCB->u32WrTail))
        || ((pstCB->u32WrTail <= pstCB->u32WrHead)
            && (pstCB->u32WrHead <= pstCB->u32RdTail)
            && (pstCB->u32RdTail <= pstCB->u32RdHead))
        || ((pstCB->u32RdHead <= pstCB->u32WrTail)
            && (pstCB->u32WrTail <= pstCB->u32WrHead)
            && (pstCB->u32WrHead <= pstCB->u32RdTail)))
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID* GetBufRdHead(VALG_CRCL_BUF_S* pstCB)
{
    HI_VOID* pRh;

    pRh = (ADDR_UNIT*)(pstCB->pBase) + pstCB->u32RdHead;
    return pRh;
}

static HI_S32 BufRead(VALG_CRCL_BUF_S* pstCB, HI_U32 u32RdLen, VALG_CB_INFO_S* pstRdInfo)
{
    HI_U32 u32Rh;

    /* Judge input length is correct
     * Notes: read head cannot cross write tail after update
     * Notes:
     * 1. The write tail pointer does not turn back
     * 2. The write tail pointer turn back
     *    1)read head does not turn back, read head will not cross write tail
     *    2)read head turn back;
     */
    u32Rh = pstCB->u32RdHead + u32RdLen;
    if (pstCB->u32RdHead <= pstCB->u32WrTail)
    {
        if (u32Rh > pstCB->u32WrTail)
        {
            return HI_FAILURE;
        }
    }
    else if (u32Rh >= pstCB->u32BufLen)
    {
        u32Rh -= pstCB->u32BufLen;
        if (u32Rh > pstCB->u32WrTail)
        {
            return HI_FAILURE;
        }
    }

    /*According to input out-packet length, to determine whether the loop buffer turn back*/
    /*Reach the bottom is also turn back */
    if ((pstCB->u32RdHead + u32RdLen) >= pstCB->u32BufLen)
    {
        /*Calculate two packets's length and addr*/
        pstRdInfo->pSrc[0]   = pstCB->pBase + pstCB->u32RdHead;
        pstRdInfo->u32Len[0] = pstCB->u32BufLen - pstCB->u32RdHead;

        /*The second input packet addr equal to buffer start addr*/
        pstRdInfo->pSrc[1]   = pstCB->pBase;
        pstRdInfo->u32Len[1] = u32RdLen - pstRdInfo->u32Len[0];

        /*Read head point to the next packet start position*/
        pstCB->u32RdHead = pstRdInfo->u32Len[1];
    }
    else
    {
        pstRdInfo->pSrc[0]   = (ADDR_UNIT*)pstCB->pBase + pstCB->u32RdHead;
        pstRdInfo->u32Len[0] = u32RdLen;
        pstRdInfo->pSrc[1] = (ADDR_UNIT*)pstRdInfo->pSrc[0] + u32RdLen;

        /*The second input packet length is 0*/
        pstRdInfo->u32Len[1] = 0;

        /*Read head point to the next packet start position*/
        pstCB->u32RdHead += u32RdLen;
    }

    return HI_SUCCESS;
}

static HI_U32 GetWrittenLength(VALG_CRCL_BUF_S *pstRecycleBuf)
{
    HI_U32 u32DataLen = 0;

    if (!pstRecycleBuf)
    {
        return u32DataLen;
    }
    if (pstRecycleBuf->u32WrTail >= pstRecycleBuf->u32RdHead)/* Write tail before read head, that did not turn back buffer*/
    {
        /*Calculate data length in buffer when turn back*/
        u32DataLen = pstRecycleBuf->u32WrTail - pstRecycleBuf->u32RdHead;
    }
    else
    {
        /*Calculate data length in buffer when turn back*/
        u32DataLen = pstRecycleBuf->u32BufLen - (pstRecycleBuf->u32RdHead - pstRecycleBuf->u32WrTail);
    }

    return u32DataLen;
}


static HI_S32 GetBitStream(VALG_CRCL_BUF_S *pstStrBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu)
{
    VeduEfl_NaluHdr_S  *pNaluHdr;
    VALG_CB_INFO_S     stRdInfo;
    HI_U32 bit_offset = 0;
    HI_U32 bit_offset1 = 0;

    if (IsBufVaild(pstStrBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    if (GetWrittenLength(pstStrBuf) == 0)
    {
        return HI_FAILURE;
    }

    pNaluHdr = (VeduEfl_NaluHdr_S*) GetBufRdHead(pstStrBuf);  /* parse the head   */

    /******* get addr and len, updata readhead *******/
    if (HI_SUCCESS != BufRead(pstStrBuf, pNaluHdr->PacketLen, &stRdInfo))
    {
        return HI_FAILURE;
    }

    pNalu->pVirtAddr[0] = stRdInfo.pSrc  [0];
    pNalu->pVirtAddr[1] = stRdInfo.pSrc  [1];
    pNalu->SlcLen   [0] = stRdInfo.u32Len[0];
    pNalu->SlcLen   [1] = stRdInfo.u32Len[1];
    pNalu->InvldByte    = pNaluHdr->InvldByte;
    if (pNalu->SlcLen[1] > 0)
    {
        pNalu->SlcLen[1] -= pNaluHdr->InvldByte;
    }
    else
    {
        pNalu->SlcLen[0] -= pNaluHdr->InvldByte;
    }

    pNalu->PTS0 = pNaluHdr->PTS0;
    pNalu->PTS1 = pNaluHdr->PTS1;
    pNalu->bFrameEnd = (pNaluHdr->bLastSlice) & 1;
    pNalu->NaluType = pNaluHdr->Type;

    /* add by j35383, discard nal header of 64 byte */
    pNalu->SlcLen   [0] -= 64;
    pNalu->pVirtAddr[0] = (HI_VOID*)(pNalu->pVirtAddr[0] + 64);
    bit_offset = (HI_U32)((HI_U8*)pNalu->pVirtAddr[0] - (HI_U8*)pstStreamInfo->StreamMMZBuf.pu8StartVirAddr);
    bit_offset1 = (HI_U32)((HI_U8*)pNalu->pVirtAddr[1] - (HI_U8*)pstStreamInfo->StreamMMZBuf.pu8StartVirAddr);

    pNalu->PhyAddr[0] = pstStreamInfo->StreamMMZBuf.u32StartPhyAddr + bit_offset;
    pNalu->PhyAddr[1] = pstStreamInfo->StreamMMZBuf.u32StartPhyAddr + bit_offset1;

    pstStreamInfo->StreamTotalByte += pNalu->SlcLen[0];
    pstStreamInfo->StreamTotalByte += pNalu->SlcLen[1];

    if (pNalu->SlcLen[1] > 0)
    {
        memcpy((pNalu->pVirtAddr[0] + pNalu->SlcLen[0]),pNalu->pVirtAddr[1],pNalu->SlcLen[1]);
    }

    return HI_SUCCESS;
}

static HI_VOID* GetBufRdTail(VALG_CRCL_BUF_S* pstCB)
{
    HI_VOID* pRt;

    pRt = (ADDR_UNIT*)(pstCB->pBase) + pstCB->u32RdTail;
    return pRt;
}

static HI_S32 UpdateBufRp(VALG_CRCL_BUF_S* pstCB, HI_U32 u32RdLen)
{
    HI_U32 u32Rt;

    if ((u32RdLen & (WORD_ALIGN - 1)) != 0)
    {
        return HI_FAILURE;
    }

    /*The length of the correctness of judgments*/
    u32Rt = pstCB->u32RdTail + u32RdLen;

    /* Judge input length is correct
     * Notes: read head cannot cross write tail after update
     * Notes:
     * 1. The write tail pointer does not turn back
     * 2. The write tail pointer turn back
     *    1)read head does not turn back, read head will not cross write tail
     *    2)read head turn back;
     */

    if (pstCB->u32RdHead >= pstCB->u32RdTail)
    {
        if (u32Rt > pstCB->u32RdHead)
        {
            return HI_FAILURE;
        }
    }
    else if (u32Rt >= pstCB->u32BufLen)
    {
        u32Rt -= pstCB->u32BufLen;
        if (u32Rt > pstCB->u32RdHead)
        {
            return HI_FAILURE;
        }
    }

    pstCB->u32RdTail = u32Rt;

    return HI_SUCCESS;
}

HI_S32 SkpBitStream(VALG_CRCL_BUF_S *pstStrBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu)
{
    HI_U32 u32InputLen;

    if (IsBufVaild(pstStrBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    u32InputLen = pNalu->SlcLen[0] + pNalu->SlcLen[1] + 64;
    u32InputLen = u32InputLen & 63 ? (u32InputLen | 63) + 1 : u32InputLen;

    /******* check start addr *******/
    if ((HI_VOID*)((HI_U8*)pNalu->pVirtAddr[0] - 64) != GetBufRdTail(pstStrBuf))
    {
        return HI_FAILURE;
    }

    /******* update Read index *******/
    if (HI_FAILURE == UpdateBufRp(pstStrBuf, u32InputLen))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#ifdef VENC_SUPPORT_JPGE
static HI_S32 GetBufNextRp(VALG_CRCL_BUF_S* pstCB, HI_U32 u32RdLen)
{
    HI_U32 u32Rt;

    if ((u32RdLen & (WORD_ALIGN - 1)) != 0)
    {
        return HI_FAILURE;
    }

    /*The length of the correctness of judgments*/
    u32Rt = pstCB->u32RdHead + u32RdLen;

    /* Judge input length is correct
     * Notes: read head cannot cross write tail after update
     * Notes:
     * 1. The write tail pointer does not turn back
     * 2. The write tail pointer turn back
     *    1)read head does not turn back, read head will not cross write tail
     *    2)read head turn back;
     */
    if (pstCB->u32WrTail >= u32Rt)
    {
        if (pstCB->u32WrTail == u32Rt)
        {
            return HI_FAILURE;
        }
    }
    else if (u32Rt >= pstCB->u32BufLen)
    {
        u32Rt -= pstCB->u32BufLen;
        if (u32Rt > pstCB->u32WrTail)
        {
            return HI_FAILURE;
        }
    }

    pstCB->u32RdHead = u32Rt;
    return HI_SUCCESS;
}
#endif

/************************************Func**********************************************/

/*open vedu use*/
HI_VOID RecycleBuf_Init(HI_VOID)
{
    /* Init global parameter */
    s_stRBParam.u16InstHandle = 0;

    /* Init global mutex */
    HI_INIT_MUTEX(&s_stRBParam.stSem);

    /* Init global Inst */
    INIT_LIST_HEAD(&s_stRBParam.stInstHead);

    return;
}

HI_VOID RecycleBuf_DeInit(HI_VOID)
{
    struct list_head *pos;
    struct list_head *n;
    struct list_head *head;
    RECYCLEBUF_INST_S *pstInst;

    RECYCLEBUF_LOCK(s_stRBParam.stSem);
    head = &s_stRBParam.stInstHead;
    if (!list_empty(head))
    {
        list_for_each_safe(pos, n, head)
        {
            pstInst = list_entry(pos, RECYCLEBUF_INST_S, stInstNode);
            RECYCLEBUF_UNLOCK(s_stRBParam.stSem);
            RecycleBuf_Destroy(pstInst->hBuf);
            RECYCLEBUF_LOCK(s_stRBParam.stSem);
        }
    }

    s_stRBParam.u16InstHandle = 0;
    RECYCLEBUF_UNLOCK(s_stRBParam.stSem);
}

HI_S32 RecycleBuf_Create(HI_HANDLE *phHandle, STRMMNG_INST_CONFIG_S *pstConfig)
{
    HI_S32 Ret = 0;
    RECYCLEBUF_INST_S *pstInst;
    HI_HANDLE *phBuf_temp = NULL;

    phBuf_temp = phHandle;

    if (pstConfig == HI_NULL)
    {
        return HI_FAILURE;
    }

    /* Allocate an instance */
    pstInst = HI_KMALLOC_ATOMIC_RECYCLEBUF(sizeof(RECYCLEBUF_INST_S));

    if (HI_NULL == pstInst)
    {
        HI_FATAL_RECYCLEBUF("No memory.\n");

        return HI_FAILURE;
    }

    /*set instant number*/
    RECYCLEBUF_LOCK(s_stRBParam.stSem);

    *phBuf_temp = s_stRBParam.u16InstHandle;
    /* Init instance parameter */
    pstInst->hBuf = *phBuf_temp;

#ifdef HI_TEE_SUPPORT
    pstInst->bTvp = pstConfig->bTvp;
#endif

    /* Init recycle buffer info */
    Ret = BufferInit(&pstInst->stRecycleBuf, pstConfig);

    if (Ret != HI_SUCCESS)
    {
        RECYCLEBUF_UNLOCK(s_stRBParam.stSem);

        HI_KFREE_RECYCLEBUF(pstInst);

        return Ret;
    }

    /* Init stream packet info for release */
    memset(&pstInst->stChnPacket, 0, sizeof(VeduEfl_NALU_S));

    spin_lock_init(&pstInst->stSpinLock);

    /* Init block list parameter */
    pstInst->u32GetTry  = 0;
    pstInst->u32GetOK   = 0;
    pstInst->u32PutTry  = 0;
    pstInst->u32PutOK   = 0;
    pstInst->u32RecvTry = 0;
    pstInst->u32RecvOK  = 0;
    pstInst->u32RlsTry  = 0;
    pstInst->u32RlsOK   = 0;

    /* Add this instance to instance list */
    list_add_tail(&pstInst->stInstNode, &s_stRBParam.stInstHead);

    s_stRBParam.u16InstHandle++;

    RECYCLEBUF_UNLOCK(s_stRBParam.stSem);

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_Destroy(HI_HANDLE hHandle)
{
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    HI_SIZE_T ulFlags;

    /* Find instance by handle */
    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    /*set instant number*/
    RECYCLEBUF_LOCK(s_stRBParam.stSem);
    if (s_stRBParam.u16InstHandle == 0)
    {
        HI_ERR_VENC("Destroy failed! There is no channel!");
        RECYCLEBUF_UNLOCK(s_stRBParam.stSem);

        return HI_FAILURE;
    }

    s_stRBParam.u16InstHandle--;

    /* Remove instance from list */
    list_del(&pstInst->stInstNode);

    RECYCLEBUF_UNLOCK(s_stRBParam.stSem);

    /* Free resource */
    HI_KFREE_RECYCLEBUF(pstInst);

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_GetWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 ret = HI_SUCCESS;
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    if ((pstInputInfo == HI_NULL) || (pstStreamInfo == HI_NULL))
    {
        return HI_FAILURE;
    }

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    if (pstInputInfo->IsIntraPic)
    {
        ret = GetParaSetWriteBuffer(&pstInst->stRecycleBuf, pstInputInfo, pstStreamInfo);

        if (ret != HI_SUCCESS)
        {
            RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

            return ret;
        }
    }

    ret =  GetStreamWriteBuffer(&pstInst->stRecycleBuf, pstInputInfo, pstStreamInfo);

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return ret;
}

HI_S32 RecycleBuf_PutWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 wrptr;
    HI_SIZE_T ulFlags;

    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    VALG_CRCL_BUF_S* pstStrBuf = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstStrBuf = &pstInst->stRecycleBuf;

    if (!pstInputInfo->VencBufFull && !pstInputInfo->VencPbitOverflow)
    {
        /* Read Wp which be changed by HW */
        wrptr = *(pstStreamInfo->StrmBufWpVirAddr);

        BufWrite   (pstStrBuf, NULL, wrptr);
        BufUpdateWp(pstStrBuf);
    }
    else
    {
        pstStreamInfo->TooFewBufferSkip++;
    }

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_U32 RecycleBuf_GetWrittenLength(HI_HANDLE hHandle)
{
    HI_U32 u32DataLen = 0;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    HI_SIZE_T ulFlags;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK  (pstInst->stSpinLock, ulFlags);
    u32DataLen = GetWrittenLength(&pstInst->stRecycleBuf);
    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return u32DataLen;
}

HI_S32 RecycleBuf_AcqReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu)
{
    HI_SIZE_T ulFlags;
    HI_S32 ret;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);
    ret = GetBitStream(&pstInst->stRecycleBuf, pstStreamInfo, pNalu);
    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return ret;
}

HI_S32 RecycleBuf_RlsReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu )
{
    HI_SIZE_T ulFlags;
    HI_S32 ret;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK (pstInst->stSpinLock, ulFlags);
    ret = SkpBitStream(&pstInst->stRecycleBuf, pstStreamInfo, pNalu);
    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return ret;
}

HI_S32 RecycleBuf_GetAcqStrmInfo(HI_HANDLE hHandle,  HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                  VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S* pstBufOffSet)
{
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (pstVeduPacket->SlcLen[1] > 0)
    {
        memcpy(&pstInst->stChnPacket, pstVeduPacket, sizeof(VeduEfl_NALU_S));
    }

    pstStream->VirAddr      = (HI_VIRT_ADDR_T)pstVeduPacket->pVirtAddr[0];
    pstStream->u32SlcLen    = pstVeduPacket->SlcLen[0] + pstVeduPacket->SlcLen[1];
    pstStream->u32PtsMs     = pstVeduPacket->PTS0;

    pstStream->bFrameEnd = (0 == pstVeduPacket->bFrameEnd) ? HI_FALSE : HI_TRUE;

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
        pstBufOffSet->u32StrmBufOffset[0] = pstVeduPacket->PhyAddr[0] - pstInst->stRecycleBuf.u32PhyAddr;
    }

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_GetRlsStrmInfo(HI_HANDLE hHandle, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                  VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket)
{
    HI_SIZE_T ulFlags;
    VENC_STREAM_S  stStream = pstAcqStrm->stStream;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    stStream.VirAddr  = (HI_VIRT_ADDR_T)(pstInst->stRecycleBuf.pBase + pstAcqStrm->H264_stream_off);

    if ((HI_VIRT_ADDR_T)pstInst->stChnPacket.pVirtAddr[0] == stStream.VirAddr)
    {
       memcpy(pstVeduPacket, &pstInst->stChnPacket, sizeof(VeduEfl_NALU_S));
       memset(&pstInst->stChnPacket, 0 ,sizeof(VeduEfl_NALU_S));
    }
    else
    {
        pstVeduPacket->pVirtAddr[0] = (HI_VOID*)stStream.VirAddr ;
        pstVeduPacket->SlcLen[0]    = stStream.u32SlcLen;
        pstVeduPacket->pVirtAddr[1] = pstVeduPacket->pVirtAddr[0] + pstVeduPacket->SlcLen[0];
        pstVeduPacket->SlcLen[1]    = 0;
        pstVeduPacket->PTS0         = stStream.u32PtsMs;
        pstVeduPacket->PTS1         = 0;
        pstVeduPacket->bFrameEnd    = (HI_U32)stStream.bFrameEnd;
    }

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_GetRlsStrmInfoIntar(HI_HANDLE hHandle, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket)
{
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((HI_VIRT_ADDR_T)pstInst->stChnPacket.pVirtAddr[0] == pstStream->VirAddr)
    {
        memcpy(pstVeduPacket, &pstInst->stChnPacket, sizeof(VeduEfl_NALU_S));
        memset(&pstInst->stChnPacket, 0, sizeof(VeduEfl_NALU_S));
    }
    else
    {
        pstVeduPacket->pVirtAddr[0] = (HI_VOID*)pstStream->VirAddr ;
        pstVeduPacket->SlcLen[0]    = pstStream->u32SlcLen;
        pstVeduPacket->pVirtAddr[1] = pstVeduPacket->pVirtAddr[0] + pstVeduPacket->SlcLen[0];
        pstVeduPacket->SlcLen[1]    = 0;
        pstVeduPacket->PTS0         = pstStream->u32PtsMs;
        pstVeduPacket->PTS1         = 0;
        pstVeduPacket->bFrameEnd    = (HI_U32)pstStream->bFrameEnd;
    }

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_CheckBufSize(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize)
{
    HI_U32 FreeLen = 0;
    HI_U32 CheckBufSize = 0;
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    FreeLen = BufGetFreeLen(&pstInst->stRecycleBuf);
    CheckBufSize = CurStrmBufSize;

    if (CheckBufSize > StrmBufSize - 64)
    {
        CheckBufSize = StrmBufSize - 64;
    }

    if (FreeLen < D_VENC_ALIGN_UP(CheckBufSize, 64))
    {
        RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

        return HI_FAILURE;
    }

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_U32 RecycleBuf_CalSlcSize(HI_HANDLE hHandle, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize)
{
    return UnfSplitSize;
}

HI_S32 RecycleBuf_ResetBuffer(HI_HANDLE hHandle, HI_U32 Protocol)
{
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    VALG_CRCL_BUF_S *pstRecycleBuf = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstRecycleBuf = &pstInst->stRecycleBuf;

    if (Protocol != VEDU_JPGE)
    {
        pstRecycleBuf->u32WrHead = pstRecycleBuf->u32RdHead;
        pstRecycleBuf->u32WrTail = pstRecycleBuf->u32RdHead;
    }
#ifdef VENC_SUPPORT_JPGE
    else
    {
        VeduEfl_NaluHdr_S *pNaluHdr;
        HI_U32    u32NewWrHead;
        VALG_CRCL_BUF_S stCycBuf_1;

        memset(&stCycBuf_1, 0, sizeof(VALG_CRCL_BUF_S));
        memcpy(&stCycBuf_1, pstRecycleBuf, sizeof(VALG_CRCL_BUF_S));

        pNaluHdr = (VeduEfl_NaluHdr_S*)(stCycBuf_1.pBase + stCycBuf_1.u32RdHead);
        if (pNaluHdr->bLastSlice == 1)    /*当前包是图像数据*/
        {
             if (HI_SUCCESS == GetBufNextRp(&stCycBuf_1,pNaluHdr->PacketLen))
             {
                  u32NewWrHead = stCycBuf_1.u32RdHead;
             }
             else   /*下一包已没数据*/
             {
                  u32NewWrHead = stCycBuf_1.u32WrHead;
             }
        }
        else        /*当前包不是有效数据:或者是头，或者没有数据*/
        {
             u32NewWrHead = stCycBuf_1.u32RdHead;
        }

        pstRecycleBuf->u32WrHead = u32NewWrHead;
        pstRecycleBuf->u32WrTail = u32NewWrHead;
    }
#endif

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_U32 RecycleBuf_GetBitBufSize(HI_HANDLE hHandle, HI_U32 StreamBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize)
{
    HI_U32 BitBufSize = 0;

    if (SlcSplitEn)
    {
        BitBufSize = StreamBufSize + D_VENC_ALIGN_UP((LumaSize * 3 / 2 / 4), VEDU_MMZ_ALIGN);
    }
    else
    {
        BitBufSize = StreamBufSize + D_VENC_ALIGN_UP((LumaSize * 3 / 2), VEDU_MMZ_ALIGN);
    }

    return BitBufSize;
}

HI_S32 RecycleBuf_AllocStreamBuf(HI_HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 AllocBufSize = 0;

    if (pStreamMMZBuf == HI_NULL)
    {
        return HI_FAILURE;
    }

#ifdef VENC_SUPPORT_JPGE
    if (Protocol == VEDU_JPGE)
    {
        AllocBufSize = BitBufSize;
        s32Ret = HI_DRV_VENC_MMZ_AllocAndMap("VENC_JpegBuf", HI_NULL, AllocBufSize, 64, pStreamMMZBuf);

        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VENC("JPGE HI_DRV_VENC_AllocAndMap failed\n");

            return HI_FAILURE;
        }
    }
    else
#endif
    {
        HI_U32 RcnBufSize = 0;

        RcnBufSize = LumaSize * 3 + 0x600000;
        AllocBufSize = BitBufSize + RcnBufSize;

        s32Ret = HI_DRV_VENC_AllocAndMap("VENC_SteamBuf", HI_NULL, AllocBufSize, 64, pStreamMMZBuf);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_VENC("HI_DRV_VENC_AllocAndMap failed\n");

            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_PutBufForRecode(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    return HI_SUCCESS;
}

HI_S32 RecycleBuf_GetStrmState(HI_HANDLE hHandle, STRMMNG_State_S* pStrmStatInfo)
{
    return HI_SUCCESS;
}

HI_S32 RecycleBuf_AllocParaSetBufAddr(HI_HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR)
{
    return HI_SUCCESS;
}

HI_S32 RecycleBuf_RlsParaSetBufAddr(HI_HANDLE hHandle, VENC_BUFFER_S* pParaSetBuf)
{
    return HI_SUCCESS;
}

/* FOR JPGE*/
#ifdef VENC_SUPPORT_JPGE
HI_S32 RecycleBuf_WriteHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 JfifHdrLen = pstInputInfo->SlcSplitEn ? 698 : 698 - 6;
    VeduEfl_NaluHdr_S NaluHdr;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    VALG_CRCL_BUF_S* pstStrBuf = HI_NULL;
    HI_SIZE_T ulFlags;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstStrBuf = &pstInst->stRecycleBuf;

    NaluHdr.PacketLen  = 64 + D_VENC_ALIGN_UP(JfifHdrLen , 64);
    NaluHdr.InvldByte  = D_VENC_ALIGN_UP(JfifHdrLen , 64) - JfifHdrLen;
    NaluHdr.bLastSlice = 0;
    NaluHdr.PTS0       = pstInputInfo->PTS0;
    NaluHdr.PTS1       = pstInputInfo->PTS1;

    BufWrite(pstStrBuf, &NaluHdr, 64);
    BufWrite(pstStrBuf, pstInputInfo->pJfifHdr , D_VENC_ALIGN_UP(JfifHdrLen , 64));

    BufUpdateWp( pstStrBuf );

    *(pstStreamInfo->StrmBufRpVirAddr) = pstStrBuf->u32RdTail;
    *(pstStreamInfo->StrmBufWpVirAddr) = pstStrBuf->u32WrHead;

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_U32 wrptr;
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    VALG_CRCL_BUF_S* pstStrBuf = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstStrBuf = &pstInst->stRecycleBuf;

    if (!pstInputInfo->VencBufFull && !pstInputInfo->VencPbitOverflow)
    {
        /* Read Wp which be changed by HW */
        wrptr = *(pstStreamInfo->StrmBufWpVirAddr);
        BufWrite   (pstStrBuf, NULL, wrptr);
        BufUpdateWp(pstStrBuf);
    }
    else
    {
        pstStreamInfo->TooFewBufferSkip++;
    }

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    HI_SIZE_T ulFlags;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;
    VALG_CRCL_BUF_S* pstStrBuf = HI_NULL;
    HI_U32 JfifHdrLen = pstInputInfo->SlcSplitEn ? 698 : 698 - 6;
    HI_U32 u32Len = 64 + D_VENC_ALIGN_UP(JfifHdrLen, 64);

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    RECYCLEBUF_SPIN_LOCK(pstInst->stSpinLock, ulFlags);

    pstStrBuf = &pstInst->stRecycleBuf;


    if (pstStrBuf->u32WrHead < u32Len)   /*turn back*/
    {
        pstStrBuf->u32WrHead = pstStrBuf->u32BufLen + pstStrBuf->u32WrHead - u32Len;
    }
    else
    {
        pstStrBuf->u32WrHead -= u32Len;
    }

    BufUpdateWp(pstStrBuf);
    *(pstStreamInfo->StrmBufRpVirAddr) = pstStrBuf->u32RdTail;
    *(pstStreamInfo->StrmBufWpVirAddr) = pstStrBuf->u32WrHead;

    RECYCLEBUF_SPIN_UNLOCK(pstInst->stSpinLock, ulFlags);

    return HI_SUCCESS;
}

HI_S32 RecycleBuf_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket, VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_SIZE_T ulFlags;
    HI_S32 s32Ret = -1;
    HI_U32 ModeHandle = 0;
    HI_U32 u32StreamTemp = 0;
    HI_U32 RecycleCnt = 0;
    HI_VOID* pVirAddr = (HI_VOID*)pstStreamInfo->pstJpgMMZBuf->pu8StartVirAddr;
    HI_U32 StreamBufLen = pstStreamInfo->pstJpgMMZBuf->u32Size;
    RECYCLEBUF_INST_S *pstInst = HI_NULL;

    RECYCLEBUF_FIND_INST(hHandle, pstInst, ulFlags);

    if (pstInst == HI_NULL)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }
    ModeHandle = 0x10000 + hHandle;

    if ((pstVeduPacket->SlcLen[0] + pstVeduPacket->SlcLen[1]) > StreamBufLen)
    {
        HI_ERR_VENC("Get stream failed, DstBufLen= %d(need %d), not enough\n", StreamBufLen, (pstVeduPacket->SlcLen[0] + pstVeduPacket->SlcLen[1]));

        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (pstVeduPacket->SlcLen[0] > 0)
    {
        memcpy(pVirAddr, pstVeduPacket->pVirtAddr[0], pstVeduPacket->SlcLen[0]);
    }

    if (pstVeduPacket->SlcLen[1] > 0)
    {
        memcpy(pVirAddr + pstVeduPacket->SlcLen[0], pstVeduPacket->pVirtAddr[1], pstVeduPacket->SlcLen[1]);
    }

    u32StreamTemp = pstVeduPacket->SlcLen[0] + pstVeduPacket->SlcLen[1];

    s32Ret = STRM_RlsReadBuffer(ModeHandle, pstStreamInfo, pstVeduPacket);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("Release stream failed, ret= %#x.\n", s32Ret);

        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }
    do
    {
        memset(pstVeduPacket, 0, sizeof(VeduEfl_NALU_S));

        s32Ret = STRM_AcqReadBuffer(ModeHandle, pstStreamInfo, pstVeduPacket);
        if (s32Ret != HI_SUCCESS)
        {
            msleep(5);
            RecycleCnt++;
        }
    }
    while (((s32Ret != HI_SUCCESS) || (pstVeduPacket->bFrameEnd != HI_TRUE)) && (RecycleCnt < 15));

    if (RecycleCnt >= 15)
    {
        HI_ERR_VENC("The time of getting stream is too long!\n");
    }

    if (pstVeduPacket->SlcLen[0] > 0)
    {
        memcpy(pVirAddr + u32StreamTemp , pstVeduPacket->pVirtAddr[0], pstVeduPacket->SlcLen[0]);
        u32StreamTemp += pstVeduPacket->SlcLen[0];
    }

    if (pstVeduPacket->SlcLen[1] > 0)
    {
        memcpy(pVirAddr + u32StreamTemp, pstVeduPacket->pVirtAddr[1], pstVeduPacket->SlcLen[1]);
        u32StreamTemp += pstVeduPacket->SlcLen[1];
    }

    s32Ret = STRM_RlsReadBuffer(ModeHandle, pstStreamInfo, pstVeduPacket);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("Release stream failed, ret= %#x.\n", s32Ret);

        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }

    pstStream->VirAddr      = (HI_VIRT_ADDR_T)pVirAddr;
    pstStream->u32SlcLen    = u32StreamTemp;
    pstStream->u32PtsMs     = pstVeduPacket->PTS0;

    pstStream->bFrameEnd    = (0 == pstVeduPacket->bFrameEnd) ? HI_FALSE : HI_TRUE;
    pstStream->enDataType.enH264EType = HI_UNF_H264E_NALU_BUTT;

    if (pstStream->u32SlcLen > 0)
    {
        pstBufOffSet->u32StrmBufOffset[0] = pstVeduPacket->PhyAddr[0] - pstInst->stRecycleBuf.u32PhyAddr;
    }

    return HI_SUCCESS;
}

#endif





