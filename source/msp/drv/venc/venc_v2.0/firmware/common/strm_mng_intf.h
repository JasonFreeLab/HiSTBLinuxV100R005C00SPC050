#ifndef __DRV_STRMINTF_H__
#define __DRV_STRMINTF_H__

#include "venc_strm_mng.h"
#include "public.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define BUF_SIZE_MULT                (10)
#define BUF_SIZE_MULT_CHECK          (15)
#define BUF_SIZE_MULT_SPLIT          (15)
#define BUF_SIZE_MULT_SPLIT_CHECK    (20)

#define WORD_ALIGN 0x04       /*Bytes included in one word*/

typedef struct
{
    HI_U32 PacketLen;     /* 64 aligned */
    HI_U32 InvldByte;     /* InvalidByteNum */
    HI_U8  Type;
    HI_U8  bBotField;
    HI_U8  bField;
    HI_U8  bLastSlice;
    HI_U32 ChnID;
    HI_U32 PTS0;
    HI_U32 PTS1;
    HI_U32 Reserved[10];
} VeduEfl_NaluHdr_S;

typedef struct hiVENC_STRM_FUN_PTR_S
{
    HI_VOID (*pfun_STRM_Init)(HI_VOID);
    HI_VOID (*pfun_STRM_DeInit)(HI_VOID);
    HI_S32  (*pfun_STRM_Create)(HI_HANDLE *phHandle, STRMMNG_INST_CONFIG_S *pstConfig);
    HI_S32  (*pfun_STRM_Destroy)(HI_HANDLE hHandle);

    HI_S32  (*pfun_STRM_GetWriteBuffer)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
    HI_S32  (*pfun_STRM_PutWriteBuffer)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

    HI_S32 (*pfun_STRM_PutBufferForRecode)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);

    HI_S32  (*pfun_STRM_AcqReadBuffer)(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket);
    HI_S32  (*pfun_STRM_RlsReadBuffer)(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S* pstVeduPacket);

    HI_S32 (*pfun_STRM_GetAcqStreamInfo)(HI_HANDLE hHandle, HI_U32 Protocol, HI_U8* StartVirAddr, VeduEfl_NALU_S *pstVeduPacket,
                                          VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
    HI_S32 (*pfun_STRM_GetRlsBufferInfo)(HI_HANDLE hHandle, HI_U32 Protocol, STRMMNG_STREAM_INFO_S *pstStreamInfo,
                                          VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm, VeduEfl_NALU_S* pstVeduPacket);
    HI_S32  (*pfun_STRM_GetRlsBufferInfoIntar)(HI_HANDLE hHandle, VENC_STREAM_S *pstStream, VeduEfl_NALU_S* pstVeduPacket);

    HI_S32  (*pfun_STRM_CheckBufferSize)(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 CurStrmBufSize);
    HI_U32  (*pfun_STRM_CalSlcSize)(HI_HANDLE hHandle, HI_U32 Protocol, HI_U32 PicHeight, HI_U32 UnfSplitSize);

    HI_S32  (*pfun_STRM_GetStrmState)(HI_HANDLE hHandle, STRMMNG_State_S* pStrmStatInfo);
    HI_U32  (*pfun_STRM_GetWrittenLen)(HI_HANDLE hHandle);
    HI_S32  (*pfun_STRM_ResetBuffer)(HI_HANDLE hHandle, HI_U32 Protocol);
    HI_U32  (*pfun_STRM_GetBitBufSize)(HI_HANDLE hHandle, HI_U32 StrmBufSize, HI_U32 SlcSplitEn, HI_U32 LumaSize);
    HI_S32  (*pfun_STRM_AllocStreamBuf)(HI_HANDLE hHandle, VENC_BUFFER_S *pStreamMMZBuf, HI_U32 Protocol, HI_U32 BitBufSize, HI_U32 LumaSize);
    HI_S32  (*pfun_STRM_AllocParaSetBufAddr)(HI_HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf, HI_U32 *pParaSetADDR);
    HI_S32  (*pfun_STRM_RlsParaSetBufAddr)(HI_HANDLE hHandle, VENC_BUFFER_S *pParaSetBuf);

#ifdef VENC_SUPPORT_JPGE
    HI_S32  (*pfun_STRM_JPGEWriteHeader)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
    HI_S32  (*pfun_STRM_PutJPGEWriteBuffer)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
    HI_S32  (*pfun_STRM_JPGERemoveHeader)(HI_HANDLE hHandle, STRMMNG_INPUT_INFO_S *pstInputInfo, STRMMNG_STREAM_INFO_S *pstStreamInfo);
    HI_S32  (*pfun_STRM_GetJpgeStream)(HI_HANDLE hHandle, STRMMNG_STREAM_INFO_S *pstStreamInfo, VeduEfl_NALU_S *pstVeduPacket, VENC_STREAM_S *pstStream, VENC_BUF_OFFSET_S *pstBufOffSet);
#endif

} VENC_STRM_FUN_PTR_S;

HI_UNF_HEVCE_NALU_TYPE_E TransNaluTypeNumForH265(HI_U32 NaluType);
HI_U32 InverseTransNaluTypeNumForH265(HI_UNF_HEVCE_NALU_TYPE_E enHEVCEType);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif











