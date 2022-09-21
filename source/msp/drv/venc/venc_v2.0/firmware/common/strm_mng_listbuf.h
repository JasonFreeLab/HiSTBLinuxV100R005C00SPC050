#ifndef __DRV_LIST_BUF_H__
#define __DRV_LIST_BUF_H__

#include "hi_error_mpi.h"
#include "strm_mng_intf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* Error Definition */
#define HI_ERR_LISTBUF_INVALID_PARA      (HI_ERR_VENC_INVALID_PARA)
#define HI_ERR_LISTBUF_NO_MEMORY         (HI_FAILURE)
#define HI_ERR_LISTBUF_BUFFER_FULL       (HI_FAILURE)
#define HI_ERR_LISTBUF_BUFFER_EMPTY      (HI_ERR_VENC_BUF_EMPTY)
#define HI_ERR_LISTBUF_FREE_ERR          (HI_FAILURE)
#define HI_ERR_LISTBUF_WRITE_FREE_ERR    (HI_FAILURE)
#define HI_ERR_LISTBUF_READ_FREE_ERR     (HI_FAILURE)
#define HI_ERR_LISTBUF_BUSY              (HI_ERR_VENC_INVALID_PARA)

#define HI_FATAL_LISTBUF(fmt...)     HI_FATAL_PRINT(HI_ID_VENC, fmt)
#define HI_ERR_LISTBUF(fmt...)       HI_ERR_PRINT(HI_ID_VENC, fmt)
#define HI_WARN_LISTBUF(fmt...)      HI_WARN_PRINT(HI_ID_VENC, fmt)
#define HI_INFO_LISTBUF(fmt...)      HI_INFO_PRINT(HI_ID_VENC, fmt)

#define LISTBUF_LOCK(sema) \
    do \
    { \
        if (down_interruptible(&sema)) \
        { \
            HI_ERR_LISTBUF("Lock fail"); \
        } \
    } while (0)
#define LISTBUF_UNLOCK(sema) do {up(&sema);} while (0)

#define LISTBUF_SPIN_LOCK(spinlock, ulFlags) \
    do \
    { \
        spin_lock_irqsave(&spinlock, ulFlags);\
    } while (0)
#define LISTBUF_SPIN_UNLOCK(spinlock, ulFlags) \
    do \
    { \
        spin_unlock_irqrestore(&spinlock, ulFlags);\
    } while (0)
// change end

/************************ Static Structure Definition ************************/
typedef enum tagLISTBUF_BLOCK_STATUS_E
{
    LISTBUF_BLOCK_FREE = 0,
    LISTBUF_BLOCK_READING,
    LISTBUF_BLOCK_WRITING,
    LISTBUF_BLOCK_BUTT
} LISTBUF_BLOCK_STATUS_E;


/* Describe a buffer block */
typedef struct tagLISTBUF_BLOCK_S
{
    HI_U32 u32Addr;                 /* Only save one address in block, use physical address */
    HI_U8* pu8VirAddr;              /* Start kernel virtual address. */
    HI_U32 u32Size;                 /* Size of block */
    HI_U32 u32NaluType;
    HI_U32 u32InvldByte;               /* InvalidByteNum */
    HI_U32 u32FillLen;
    HI_U32 u32Pts0Ms;                 /* pts */
    HI_U32 u32Pts1Ms;
    HI_BOOL bFrameEnd;
    struct list_head stBlockNode;   /* Block list node */
    LISTBUF_BLOCK_STATUS_E enstatus; /* Status of block */
} LISTBUF_BLOCK_S;

/* Describe a buffer instance */
typedef struct tagLISTBUF_INST_S
{
    HI_HANDLE   hBuf;               /* Handle of this buffer instance */
    HI_U32      u32PhyAddr;           /* Start physical address of the buffer instance. */
    HI_U8      *pu8KnlVirAddr;      /* Start kerenl virtual address of the buffer instance. */
    HI_U32      u32ParaSetPhyAddr;
    HI_U8      *pu8ParaSetKnlVirAddr;      /* Start kerenl virtual address of the buffer instance. */
    HI_U32      u32Size;            /* Size of the buffer instance */
    HI_U32      StrmHeadFree;        /* Head free size */
    HI_U32      StrmTailFree;        /* Tail free size */

    HI_U32      u32GetTry;          /* GetWriteBuf try times */
    HI_U32      u32GetOK;           /* GetWriteBuf ok times */
    HI_U32      u32PutTry;          /* PutWriteBuf try times */
    HI_U32      u32PutOK;           /* PutWriteBuf ok times */
    HI_U32      u32RecvTry;         /* GetReadBuf try times */
    HI_U32      u32RecvOK;          /* GetReadBuf ok times */
    HI_U32      u32RlsTry;          /* PutReadBuf try times */
    HI_U32      u32RlsOK;           /* PutReadBuf ok times */

#ifdef HI_TEE_SUPPORT
    HI_BOOL     bTvp;
#endif
    spinlock_t stSpinLock;          /* Spin lock */
    struct list_head stWriteBlockHead;  /* Buffer manager block list head for get buf*/
    struct list_head stFreeBlockHead;   /* Buffer manager block list head for put buf*/
    struct list_head stReadBlockHead;   /* Buffer manager block list head for aqcuire buf*/
    struct list_head stInstNode;    /* Instance node */

} LISTBUF_INST_S;

/* Global parameter of this module */
typedef struct tagBUFMNG_GLOBAL_S
{
    HI_U16 u16InstHandle;           /* Allocate handle according to this number */
    struct semaphore stSem;         /* Semaphore */
    spinlock_t stSpinLock;          /* Spin lock */
    struct list_head stInstHead;    /* Instance list head */
} BUFMNG_GLOBAL_S;
/****************************************************************/

HI_VOID ListBuf_Init(HI_VOID);
HI_VOID ListBuf_DeInit(HI_VOID);

HI_S32 ListBuf_Create(HI_HANDLE *phBuf, STRMMNG_INST_CONFIG_S *pstConfig);
HI_S32 ListBuf_Destroy(HI_HANDLE hBuf);

HI_S32 ListBuf_GetWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 ListBuf_PutWriteBuf(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

HI_S32 ListBuf_PutBufForRecode(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 ListBuf_PutWriteBufSlices(HI_HANDLE hBuf, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

HI_S32 ListBuf_AcquireBitStream(HI_HANDLE hBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket);
HI_S32 ListBuf_ReleaseBitStream(HI_HANDLE hBuf, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pstVeduPacket);

HI_S32 ListBuf_GetAcquireStreamInfo(HI_HANDLE hBuf, HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                     VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
HI_S32 ListBuf_GetRleaseStreamInfo(HI_HANDLE hBuf, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                    VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket);

HI_S32 ListBuf_GetRleaseStreamInfoIntar(HI_HANDLE hBuf, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket);

HI_S32 ListBuf_CheckBufferSize(HI_HANDLE hBuf, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize);
HI_U32 ListBuf_CalSlcSize(HI_HANDLE hBuf, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize);

HI_S32 ListBuf_GetStrmState(HI_HANDLE hBuf, STRMMNG_State_S* pStrmStatInfo);
HI_U32 ListBuf_GetWrittenLen(HI_HANDLE hBuf);
HI_U32 ListBuf_GetBitBufSize(HI_HANDLE hBuf, HI_U32 StreamBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize);
HI_S32 ListBuf_AllocStreamBuf(HI_HANDLE hBuf, VENC_BUFFER_S* pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize);
HI_S32 ListBuf_AllocParaSetBufAddr(HI_HANDLE hBuf, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR);
HI_S32 ListBuf_RlsParaSetBufAddr(HI_HANDLE hBuf, VENC_BUFFER_S *pParaSetBuf);

HI_S32 ListBuf_ResetBuffer(HI_HANDLE hBuf, HI_U32 Protocol);

#ifdef VENC_SUPPORT_JPGE
HI_S32 ListBuf_WriteHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 ListBuf_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 ListBuf_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 ListBuf_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket,
                                VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
#endif




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif



