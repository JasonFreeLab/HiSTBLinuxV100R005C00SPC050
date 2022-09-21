#ifndef __DRV_RECYCLE_BUF_H__
#define __DRV_RECYCLE_BUF_H__

#include "strm_mng_intf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/************************struct define***************************************/
#define HI_ERR_STRMMNG(fmt...)       HI_ERR_PRINT(HI_ID_VENC, fmt)
#define HI_FATAL_RECYCLEBUF(fmt...)     HI_FATAL_PRINT(HI_ID_VENC, fmt)

#define RECYCLEBUF_LOCK(sema) \
    do \
    { \
        if (down_interruptible(&sema)) \
        { \
            HI_ERR_STRMMNG("Lock fail"); \
        } \
    } while (0)

#define RECYCLEBUF_UNLOCK(sema) do {up(&sema);} while (0)

#define RECYCLEBUF_SPIN_LOCK(spinlock, ulFlags) \
    do \
    { \
        spin_lock_irqsave(&spinlock, ulFlags);\
    } while (0)

#define RECYCLEBUF_SPIN_UNLOCK(spinlock, ulFlags) \
    do \
    { \
        spin_unlock_irqrestore(&spinlock, ulFlags);\
    } while (0)
/************************struct define***************************************/
/* Global parameter of this module */
typedef struct tagRECYCLEBUF_GLOBAL_S
{
    HI_U16 u16InstHandle;           /* Allocate handle according to this number */
    struct semaphore stSem;         /* Semaphore */ //use for global variable
    spinlock_t stSpinLock;          /* Spin lock */
    struct list_head stInstHead;    /* Instance list head */
} RECYCLEBUF_GLOBAL_S;

typedef struct
{
    HI_U32    u32PhyAddr;     /*Loop-buffer's start phy addr*/
    HI_VOID*  pBase;          /*Loop-buffer's start vir addr*/
    HI_U32    u32BufLen;      /*Loop-buffer total len, unit is byte*/
    HI_U32    u32RsvByte;     /*Judge loop-buffer is full or not, unit is byte*/
    HI_U32    u32RdHead;      /*Loop-buffer read head offset, unit is byte*/
    HI_U32    u32RdTail;      /*Loop-buffer read tail offset, unit is byte*/
    HI_U32    u32WrHead;      /*Loop-buffer write head offset, unit is byte*/
    HI_U32    u32WrTail;      /*Loop-buffer read tail offset, unit is byte*/
} VALG_CRCL_BUF_S;

/* Describe a buffer instance */
typedef struct tagRECYCLEBUF_INST_S
{
    HI_HANDLE   hBuf;               /* Handle of this buffer instance */

    VALG_CRCL_BUF_S stRecycleBuf;   /* Stream Buffer addr and wp/rp */
    VeduEfl_NALU_S  stChnPacket;    /* use to release the stream */

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
    struct list_head stInstNode;    /* Instance node */

} RECYCLEBUF_INST_S;

typedef HI_UCHAR ADDR_UNIT;  /*Addressing step of processor, unit of the address*/
typedef HI_U32   CPU_WORD;   /*Word lenght of processor, unit of W/R operations*/

/*Read/write loop-buffer's out data type*/
typedef struct
{
    HI_VOID*   pSrc[2];
    HI_U32     u32Len[2];
} VALG_CB_INFO_S;

/************************function define***************************************/
HI_VOID RecycleBuf_Init(HI_VOID);
HI_VOID RecycleBuf_DeInit(HI_VOID);
HI_S32 RecycleBuf_Create(HI_HANDLE *phHandle, STRMMNG_INST_CONFIG_S *pstConfig);
HI_S32 RecycleBuf_Destroy(HI_HANDLE hHandle);

HI_S32 RecycleBuf_GetWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 RecycleBuf_PutWriteBuf(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

HI_S32 RecycleBuf_PutBufForRecode(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo);

HI_S32 RecycleBuf_AcqReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu);
HI_S32 RecycleBuf_RlsReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pNalu );

HI_S32 RecycleBuf_GetAcqStrmInfo(HI_HANDLE hHandle,  HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                  VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S* pstBufOffSet);
HI_S32 RecycleBuf_GetRlsStrmInfo(HI_HANDLE hHandle, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                  VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket);
HI_S32 RecycleBuf_GetRlsStrmInfoIntar(HI_HANDLE hHandle, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket);

HI_S32 RecycleBuf_CheckBufSize(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize);
HI_U32 RecycleBuf_CalSlcSize(HI_HANDLE hHandle, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize);
HI_U32 RecycleBuf_GetWrittenLength(HI_HANDLE hHandle);

HI_S32 RecycleBuf_ResetBuffer(HI_HANDLE hHandle, HI_U32 Protocol);
HI_U32 RecycleBuf_GetBitBufSize(HI_HANDLE hHandle, HI_U32 StreamBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize);
HI_S32 RecycleBuf_AllocStreamBuf(HI_HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize);

HI_S32 RecycleBuf_PutBufForRecode(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S* pstStreamInfo);
HI_S32 RecycleBuf_GetStrmState(HI_HANDLE hHandle, STRMMNG_State_S* pStrmStatInfo);
HI_S32 RecycleBuf_AllocParaSetBufAddr(HI_HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR);
HI_S32 RecycleBuf_RlsParaSetBufAddr(HI_HANDLE hHandle, VENC_BUFFER_S* pParaSetBuf);

#ifdef VENC_SUPPORT_JPGE
HI_S32 RecycleBuf_WriteHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 RecycleBuf_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 RecycleBuf_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 RecycleBuf_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket,
                                VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif




