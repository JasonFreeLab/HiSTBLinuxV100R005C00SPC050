#ifndef __DRV_VENCSTRM_H__
#define __DRV_VENCSTRM_H__

#include "drv_venc_ioctl.h"
#include "drv_venc_osal_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define D_VENC_ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )
#define H264_NALU_TYPE_SPS     (7)
#define H264_NALU_TYPE_PPS     (8)
#define H264_NALU_TYPE_IDR     (5)
#define H264_NALU_TYPE_P       (1)

#define H265_NALU_TYPE_VPS     (32)
#define H265_NALU_TYPE_SPS     (33)
#define H265_NALU_TYPE_PPS     (34)
#define H265_NALU_TYPE_IDR     (5)
#define H265_NALU_TYPE_P       (1)
#define H265_NALU_TYPE_SEI     (39)

#define BUF_SIZE_MULT_CHECK_INIT     (20)

#ifdef VENC_DPT_ONLY
#define VEDU_MMZ_ALIGN       (256)
#else
#define VEDU_MMZ_ALIGN       (64)
#endif

typedef struct
{
    HI_VOID*   pVirtAddr[2];
    HI_U32     PhyAddr[2];
    HI_U32     SlcLen[2];  /* byte */
    HI_U32     PTS0;
    HI_U32     PTS1;
    HI_U32     bFrameEnd;
    HI_U32     NaluType;   /* 1(P),5(I),6(SEI),7(SPS) or 8(PPS), only used by H264    */
    HI_U32     InvldByte;
} VeduEfl_NALU_S;

typedef struct
{
    /*for list buf*/
    HI_U32 u32PhyAddr;      /* Start physical address. */
    HI_U8* pu8KnlVirAddr;   /* Start kernel virtual address. */
    HI_U32 u32ParaSetPhyAddr;
    HI_U8 *pu8ParaSetKnlVirAddr;
    HI_U32 u32Size;         /* Size */
    HI_BOOL bTvp;

    /*for loop buf*/
    HI_U32 u32RsvByte;
} STRMMNG_INST_CONFIG_S;

typedef struct
{
    HI_U32      UsedStreamBuf;       /* Used size */
    HI_U32      StrmHeadFree;        /* Head free size */
    HI_U32      StrmTailFree;        /* Tail free size */
    HI_U32      StrmGetTry;          /* GetWriteBuf try times */
    HI_U32      StrmGetOK;           /* GetWriteBuf ok times */
    HI_U32      StrmPutTry;          /* PutWriteBuf try times */
    HI_U32      StrmPutOK;           /* PutWriteBuf ok times */
    HI_U32      StrmRecvTry;         /* GetReadBuf try times */
    HI_U32      StrmRecvOK;          /* GetReadBuf ok times */
    HI_U32      StrmRlsTry;          /* PutReadBuf try times */
    HI_U32      StrmRlsOK;           /* PutReadBuf ok times */
} STRMMNG_State_S;

typedef struct
{
    //paraset
    HI_S32 PrependSpsPpsEnable;
    HI_U32 VpsBits;
    HI_U32 SpsBits;
    HI_U32 PpsBits;
    HI_U8* pVpsStream;
    HI_U8* pSpsStream;
    HI_U8* pPpsStream;

    //real stream
    HI_U32   SliceLength[16];
    HI_U32   SliceIsEnd[16];

    //common info
    HI_U16 SlcSplitEn;
    HI_U32 Protocol;
    HI_U32 IsIntraPic;
    HI_U32 PTS0;
    HI_U32 PTS1;
    HI_U32 TargetBits;
    HI_U32 VencBufFull;
    HI_U32 VencPbitOverflow;
    HI_U32 GetFrameNumOK;
    HI_S32 LowDlyMod;
    HI_U32 Recode;

    //JPGE
    #ifdef VENC_SUPPORT_JPGE
    HI_U8*   pJfifHdr;
    #endif

} STRMMNG_INPUT_INFO_S;

typedef struct
{
    HI_U32 u32Addr;                 /* Only save one address in block, use physical address */
    HI_U32 u32Size;                 /* Size of block */
    HI_U8* pu8VirAddr;              /* Start kernel virtual address. */
    HI_U32 u32NaluType;
    HI_U32 u32InvldByte;               /* InvalidByteNum */
    HI_U32 u32Pts0Ms;                  /* pts */
    HI_U32 u32Pts1Ms;
    HI_BOOL bFrameEnd;
} STRMMNG_BUF_S;

typedef struct
{
    //paraset
    HI_U32 ParaSetLen;
    HI_U32 ParaSetRealLen;
    HI_U32 *pParaSetArray;
    //real stream
    HI_U32* StrmBufRpVirAddr; /* phy addr for hardware */
    HI_U32* StrmBufWpVirAddr;
    HI_U32* pStreamBufAddrArray;
    HI_U32* pStreamBufLenArray;
    HI_U32  StrmBufSize;
    HI_U32  CurStrmBufSize;
    HI_U32  StreamTotalByte;

    VENC_BUFFER_S   StreamMMZBuf;
    VENC_BUFFER_S   SliceBuf;
    STRMMNG_BUF_S   *pstBuf;

    //common info
    HI_U32   SliceIdx;
    HI_U32   TooFewBufferSkip;
    HI_BOOL  bFirstSlcOneFrm;

    #ifdef VENC_SUPPORT_JPGE
    VENC_BUFFER_S *pstJpgMMZBuf;
    #endif

} STRMMNG_STREAM_INFO_S;

HI_S32 STRM_Init(HI_VOID);
HI_S32 STRM_DeInit(HI_VOID);
HI_S32 STRM_Create(HI_U32 *phHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 STRM_Destroy(HI_U32 hHandle);
HI_S32 STRM_GetWriteBuffer(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 STRM_PutWriteBuffer(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

HI_S32 STRM_PutBufferForRecode(HI_U32 hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

HI_S32 STRM_AcqReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket);
HI_S32 STRM_RlsReadBuffer(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket);
HI_S32 STRM_GetAcquireStreamInfo(HI_HANDLE hHandle, HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                  VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
HI_S32 STRM_GetRleaseStreamInfo(HI_HANDLE hHandle, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                 VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket);
HI_S32 STRM_GetRleaseStreamInfoIntar(HI_HANDLE hHandle, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket);

HI_S32 STRM_CheckBufferSize(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize);
HI_U32 STRM_CalSlcSize(HI_HANDLE hHandle, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize);
HI_S32 STRM_GetStrmState(HI_HANDLE hHandle, STRMMNG_State_S* pStrmStatInfo);
HI_U32 STRM_GetWrittenLength(HI_HANDLE hHandle);
HI_S32 STRM_GetMatchMode(HI_U32 Protocol, HI_HANDLE* phStrmMng, HI_BOOL IsChipIDV500R001);

HI_U32 STRM_GetBitBufSize(HANDLE hHandle, HI_U32 *pStrmBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize);
HI_S32 STRM_AllocStreamBuf(HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize);
HI_S32 STRM_RlsStreamBuf(HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol);

HI_S32 STRM_AllocWriteReadPtrBuf(HANDLE hHandle, VENC_BUFFER_S* pWpRpMMZBuf);
HI_S32 STRM_RlsWriteReadPtrBuf(HANDLE hHandle, VENC_BUFFER_S* pWpRpMMZBuf);


#ifdef VENC_SUPPORT_JPGE
HI_S32 STRM_JPGEWriteHeader(HANDLE hHandle, STRMMNG_INPUT_INFO_S* pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 STRM_PutJPGEWriteBuffer(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 STRM_JPGERemoveHeader(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
HI_S32 STRM_GetJpgeStream(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket, VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
#endif

HI_S32 STRM_ResetBuffer(HANDLE hHandle, HI_U32 Protocol);
HI_S32 STRM_AllocParaSetBufAddr(HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR);
HI_S32 STRM_RlsParaSetBufAddr(HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
