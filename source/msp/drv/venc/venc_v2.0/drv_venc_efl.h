#ifndef __DRV_VENC_EFL_H__
#define __DRV_VENC_EFL_H__

#include "drv_venc_osal.h"
#include "drv_venc_buf_mng.h"
#include "hi_unf_common.h"
#include "hi_drv_video.h"
#include "drv_venc_queue_mng.h"
#include "hi_drv_mmz.h"
#include "drv_venc_ratecontrol.h"
#include "venc_strm_mng.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//#define __VENC_DRV_DBG__
//#define __VENC_RC_DBG__
//#define __OMXVENC_ONE_IN_ONE_OUT__
#define VEDU_TR_STEP 1
/*************************************************************************************/
#define MAX_VEDU_QUEUE_NUM 6
#define MAX_VEDU_STRM_QUEUE_NUM 20
#define MSG_QUEUE_NUM     100
#define INVAILD_CHN_FLAG   (-1)

#define OMX_OUTPUT_PORT_BUFFER_MAX (20)

/*******************************************************************/

#define __VEDU_NEW_RC_ALG__

typedef HI_S32 (*VE_IMAGE_FUNC)(HI_S32 handle, HI_DRV_VIDEO_FRAME_S* pstImage);
typedef HI_S32 (*VE_IMAGE_OMX_FUNC)(HI_S32 handle, venc_user_buf* pstImage);
typedef HI_S32 (*VE_CHANGE_INFO_FUNC)(HI_HANDLE handle, HI_U32 u32Width, HI_U32 u32Height, HI_U32 u32FrmRate);
typedef HI_S32 (*VE_DETACH_FUNC)(HI_HANDLE handle, HI_HANDLE hSrc);

typedef struct
{
    HI_U32 ProfileIDC;
    HI_U32 FrameWidthInMb;
    HI_U32 FrameHeightInMb;
    HI_U8  FrameCropLeft;
    HI_U8  FrameCropRight;
    HI_U8  FrameCropTop;
    HI_U8  FrameCropBottom;
} VeduEfl_H264e_SPS_S;

typedef struct
{
    HI_U32  ConstIntra;
    HI_S32  ChrQpOffset;
    HI_U32  H264HpEn;
    HI_U32  H264CabacEn;
    HI_S32* pScale8x8;
} VeduEfl_H264e_PPS_S;

typedef struct
{
    HI_U32 slice_type; /* 0-P, 2-I */
    HI_U32 frame_num;
    HI_U32 NumRefIndex; /* 0 or 1 */
} VeduEfl_H264e_SlcHdr_S;

typedef struct
{
    HI_BOOL general_progressive_source_flag;
    HI_BOOL general_interlaced_source_flag;
    HI_U32 uiMaxDecPicBufferMinus1[2];
} VeduEfl_H265e_VPS_S;

typedef struct
{
    HI_U32  ProfileIDC;
    HI_U32  uiPicWidthInLumaSamples;
    HI_U32  uiPicHeightInLumaSamples;
    HI_U32  bPicCroppingFlag;
    HI_U32  uiPicCropLeftOffset;
    HI_U32  uiPicCropRightOffset;
    HI_U32  uiPicCropTopOffset;
    HI_U32  uiPicCropBottomOffset;
    HI_U32  bPcmEnable;
    HI_U32  iPcmLog2MaxSize;
    HI_U32  bSAOEnabledFlag;
    HI_U32  iPcmLog2MinSize;
    HI_U32  sps_temporal_mvp_enable_flag;
    HI_U32  bStrongIntraSmoothingFlag;

} VeduEfl_H265e_SPS_S;

typedef struct
{
    HI_U32 bCUQpDeltaEnable;
    HI_S32 iCbQpOffset;
    HI_S32 iCrQpOffset;

    HI_U32 bPicDisableDBFilter;
    HI_S32 frm_qp_minus26;

}VeduEfl_H265e_PPS_S;

typedef struct
{
    HI_U32 bFirstSliceInPic;
    HI_U32 eSliceType; // 2->I, 1->P, 0->B
    HI_U32 uiPocLsb;
    HI_U32 bSpsTemporalMvpEnableFlag;
    HI_U32 bSAOEnabledFlag;
    HI_U32 bSliceSaoLuma;
    HI_U32 bSliceSaoChroma;
    HI_U32 five_minus_max_num_merge_cand;
    HI_S32 iSliceQPDelta;
    HI_U32 bDBFilterCtlPresent;
    HI_U32 bDBFilterOverrideEnabled;
    HI_U32 bDFOverrideFlag;
    HI_U32 bSliceHeaderDisableDF;
    HI_U32 bSliceLFAcrossSlice;
    HI_U32 frame_num;
    HI_U32 slice_type;
    HI_U32 collocated_from_l0_flag;
    HI_U32 num_ref_idx_l0_active_minus1;

}VeduEfl_H265e_SlcHdr_S;

typedef struct
{
    HI_U32              handle;
    VE_IMAGE_FUNC       pfGetImage;
    VE_IMAGE_OMX_FUNC   pfGetImage_OMX;
    VE_IMAGE_FUNC       pfPutImage;
    VE_CHANGE_INFO_FUNC pfChangeInfo;
    VE_DETACH_FUNC      pfDetachFunc;
} VeduEfl_SrcInfo_S;

typedef struct
{
    HI_BOOL bOMXChn;
    HI_BOOL bAutoRequestIfrm;
    HI_BOOL bPrependSpsPps;
    HI_BOOL bRCSkipFrmEn;

    HI_U32 Protocol;      /* VEDU_H264, VEDU_H263 or VEDU_MPEG4 */
    HI_U32 CapLevel;      /* VEDU buffer alloc*/
    HI_U32 Profile;       /* H264 Profile*/
    HI_U32 FrameWidth;    /* width    in pixel, 96 ~ 2048 */
    HI_U32 FrameHeight;   /* height in pixel, 96 ~ 2048 */

    HI_U32 RotationAngle; /* venc don't care */

    HI_U32 PackageSel;
    HI_U32 Priority;
    HI_U32 streamBufSize;

    HI_BOOL QuickEncode;
    HI_BOOL SlcSplitEn;   /* 0 or 1, slice split enable */
    HI_BOOL SlcSplitMod;  /* 0 or 1, 0:byte; 1:mb line */
    HI_U32 SplitSize;     /* <512 mb line @ H264, H263 don't care*/
    HI_U32 Gop;
    HI_U32 QLevel;        /* venc don't care */
    HI_U32 DriftRCThr;    /* the threshold of RC skip frame; vp default 20%*/
} VeduEfl_EncCfg_S;

typedef struct
{
    HI_U32 BitRate;       /* 32k ~ 20M, bits per second */
    HI_U32 OutFrmRate;    /* 1 ~ InFrmRate */
    HI_U32 InFrmRate;     /* 1 ~ 30  */

    HI_U32   MaxQp;       /* H264: 0 ~ 51, Mpeg4: 1 ~ 31 */
    HI_U32   MinQp;       /* MinQp <= MaxQp */
    HI_U32   Gop;         /* for new RC ALG*/
} VeduEfl_RcAttr_S;

typedef struct
{
    HI_U32 vcpi_ipcm_en;
    HI_U32 vcpi_sao_chroma;
    HI_U32 vcpi_sao_luma;
    HI_U32 max_num_mergecand;
    HI_U32 tmv_en;
    HI_U32 pmv_poc[6];
} VeduEfl_BaseAttr_S;

typedef struct
{
    HI_U16 SlcSplitEn;
    HI_U8  SlcSplitMod;       /* 0 or 1, byte or mb line ,just select 1*/
    HI_U32 SplitSize;

    VENC_BUFFER_S DdrRegCfgBuf;
    HI_U32  RegConfigMode;

    VENC_BUFFER_S SliceBuf;
    /*para*/
    HI_U32 StrmBufAddr;
    HI_U32 StrmBufRpAddr;     /* phy addr for hardware */
    HI_U32 StrmBufWpAddr;
    HI_U32 StrmBufSize;

    /* frame buffer parameter */
    HI_U32 SStrideY;
    HI_U32 SStrideC;
    HI_U32 YuvStoreType;      /* 0, semiplannar; 1, package; 2,planer */
    HI_U32 PackageSel;

    HI_U32 SrcYAddr;
    HI_U32 SrcCAddr;
    HI_U32 SrcVAddr;          /*just for input of planner*/

    HI_U32 RcnYAddr[2];
    HI_U32 RcnCAddr[2];
    HI_U32 RcnYAddr_head[2];
    HI_U32 RcnCAddr_head[2];
    HI_U32 TmvAddr[2];
    HI_U32 PmeAddr[2];
    HI_U32 PmeInfoAddr[3];

    HI_U32 SlcHdrBits;        /* 8bit_0 | mark | reorder | slchdr */
    HI_U32 CABAC_SLCHDR_PART2_SEG[8];
    HI_U32 slchdr_part1;
    HI_U32 slchdr_size_part1;
    HI_U32 slchdr_size_part2;

    HI_U32  PTS0;
    HI_U32  PTS1;

    HI_U32  RStrideY;
    HI_U32  RStrideC;
    HI_U32  RHStrideY;
    HI_U32  RHStrideC;

    HI_U32 SlcHdrStream [4];
    HI_U32 ReorderStream[2];
    HI_U32 MarkingStream[2];

    //for smmu
    HI_U32 tunlcellAddr;
    HI_S32 ClkGateEn;

    VeduEfl_BaseAttr_S  BaseCfg;

#ifdef HI_SMMU_SUPPORT
    HI_U32 u32SmmuPageBaseAddr;
    HI_U32 u32SmmuErrWriteAddr;
    HI_U32 u32SmmuErrReadAddr;
#endif

    HI_U32 VencEndOfPic;
    HI_U32 MeanQP;

    /*add for safe mode*/
    HI_U32   SliceLength[16];
    HI_U32   SliceIsEnd[16];
    HI_U32   VEDU_STRM_ADDR[16];
    HI_U32   VEDU_STRM_BUFLEN[16];
    HI_U32   SliceIdx;
    HI_BOOL  bFirstSlcOneFrm;

    HI_U32   ParaSetPhyAddr;
    HI_U32   ParaSetLen;
    HI_U32   ParaSetRealLen;
    HI_U32   ParaSetArray[48];
} Vedu_Hal_S;

typedef struct
{
    HI_S32 ICatchEnable;
    HI_S32 PrependSpsPpsEnable;
    HI_S32 AutoSkipFrameEn;
    HI_U32 DriftRcSkipThr;
    HI_S32 FrmCnt;
    /* channel parameter */
    HI_U32 Protocol;
    HI_U32 H264CabacEn;
    HI_U32 H264HpEn;

    HI_U32 YuvSampleType;
    HI_U32 RotationAngle;
    HI_U8  Priority;
    HI_BOOL QuickEncode;
    HI_BOOL OMXChn;

    /* stream buffer parameter */
    VENC_BUFFER_S StreamMMZBuf;
    VENC_BUFFER_S WpRpMMZBuf;
    HI_HANDLE       hStrmMng;             /*pInst num*/
    STRMMNG_BUF_S   stBuf[HI_VENC_SLICE_NUM];
    HI_U32          CurStrmBufSize;
    HI_BOOL         bNotEnoughBuf;
    HI_U32*         StrmBufRpVirAddr; /* phy addr for hardware */
    HI_U32*         StrmBufWpVirAddr;

    /* JPGE stream buffer parameter */
    VENC_BUFFER_S   JpgMMZBuf;
    HI_U32          Vir2BusOffset;   /* offset = vir - bus, @ stream buffer */

    /* header parameter */
    HI_U8  VpsStream[64],  tempVpsStream[64];
    HI_U8  SpsStream[64],  tempSpsStream[64];
    HI_U8  PpsStream[320], tempPpsStream[32];
    HI_U32 VpsBits;
    HI_U32 SpsBits;
    HI_U32 PpsBits;
    HI_BOOL IsProgressive;

    /*header for jpge*/
#ifdef VENC_SUPPORT_JPGE
    HI_U8   pJfifHdr[698];
    HI_U8   pJpgeYqt[64];
    HI_U8   pJpgeCqt[64];
    HI_U32  QLevel;
    volatile HI_U32  WaitingIsr_jpge;    /* to block STOP channel */
#endif

    /* other parameter */
    volatile HI_U32  WaitingIsr;         /* to block STOP channel */
    HI_BOOL bNeverEnc;
    HI_BOOL bFirstNal2Send;              /*for omx_venc send output buffer flags*/

    /* frame rate control out */
    HI_U32      TrCount;
    HI_U32      LastTR;
    HI_U32      InterFrmCnt;
    /* frame rate control mid */
    HI_U32  LastFrmRate[6];             /*from the struction of Image*/
    HI_U32  LastSecInputFrmRate[2];     /* from Timer stat.*/

    /* config reg*/
    Vedu_Hal_S stHal;

    /* rate control mid */
    VALG_FIFO_S stBitsFifo;
    HI_U32      MeanBit;
    HI_U32      BitsFifo[FrmRateCntBufNum];
    VeduEfl_Rc_S stRc;

    /* slice head */
    HI_S32  ChrQpOffset;
    HI_S32  ConstIntra;
    HI_S32  NumRefIndex;
    HI_S32  Scale8x8[128];
   /* register of low power work mode */
    HI_S32  IntraLowpowEn;
    HI_S32  fracLowpowEn;
    HI_S32  intpLowpowEn;

    /* attach vi or vo ,backup for vpss*/
    VeduEfl_SrcInfo_S     stSrcInfo;
    HI_DRV_VIDEO_FRAME_S  stImage;
    venc_user_buf         stImage_OMX;

    /* statistic */
    VeduEfl_StatInfo_S stStat;

    queue_info_s* FrameDequeue;
    queue_info_s* FrameQueue;
    queue_info_s* MsgQueue_OMX;
    queue_info_s* StreamQueue_OMX;
    queue_info_s* FrameQueue_OMX;

    HI_S32 RcDbgPrint;
} VeduEfl_EncPara_S;

typedef struct
{
    HI_U32 BusViY;      /* 16-byte aligned  */
    HI_U32 BusViC;      /* 16-byte aligned  */
    HI_U32 BusViV;
    HI_U32 ViYStride;   /* 16-byte aligned  */
    HI_U32 ViCStride;   /* 16-byte aligned  */

    HI_U32 PTS0;
    HI_U32 PTS1;

    HI_U32   RStrideY;      /* 16-byte aligned  */
    HI_U32   RStrideC;      /* 16-byte aligned  */
    HI_U32   TunlCellAddr;
} VeduEfl_EncIn_S;

typedef struct
{
    VeduEfl_EncPara_S *EncHandle;
} VeduEfl_ChnCtx_S;

typedef struct
{
    HI_U32   IpFree;       /* for channel control */
    VeduEfl_EncPara_S *CurrHandle;   /* used in ISR */
    HI_U32  *pRegBase;
    HI_VOID *pChnLock;     /* lock ChnCtx[MAX_CHN] */

    HI_VOID *pTask_Frame;  /*for both venc & omxvenc*/
    HI_VOID *pTask_Stream; /*juse for omxvenc*/
    HI_U32   StopTask;
    HI_U32   TaskRunning;  /* to block Close IP */
    HI_S32   CurrFreq;     /* for record the current frequency*/
    HI_BOOL  IsChipIDV500R001;    /* for record the chip type from hardware*/
} VeduEfl_IpCtx_S;

HI_S32    VENC_DRV_EflOpenVedu(HI_VOID);
HI_VOID   VENC_DRV_EflCloseVedu(HI_VOID);
HI_S32    VENC_DRV_EflCreateVenc(VeduEfl_EncPara_S** pEncHandle, VeduEfl_EncCfg_S* pEncCfg);
HI_S32    VENC_DRV_EflDestroyVenc(VeduEfl_EncPara_S* EncHandle );
HI_S32    VENC_DRV_EflAttachInput(VeduEfl_EncPara_S* EncHandle, VeduEfl_SrcInfo_S* pSrcInfo);
HI_S32    VENC_DRV_EflDetachInput(VeduEfl_EncPara_S* EncHandle, VeduEfl_SrcInfo_S* pSrcInfo);
HI_S32    VENC_DRV_EflStartVenc(VeduEfl_EncPara_S* EncHandle);
HI_S32    VENC_DRV_EflStopVenc(VeduEfl_EncPara_S* EncHandle);
HI_S32    VENC_DRV_EflRcGetAttr(VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr);
HI_S32    VENC_DRV_EflRcAttrInit(VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr);
HI_S32    VENC_DRV_EflRcSetAttr(VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr);
HI_S32    VENC_DRV_EflRcFrmRateCtrl(VeduEfl_EncPara_S* EncHandle, HI_U32 TR);
HI_S32    VENC_DRV_EflStartOneFrameVenc(VeduEfl_EncPara_S* EncHandle, VeduEfl_EncIn_S* pEncIn);
HI_S32    VENC_DRV_EflEndOneFrameVenc(VeduEfl_EncPara_S* EncHandle);
HI_VOID   VENC_DRV_EflRequestIframe(VeduEfl_EncPara_S* EncHandle);
HI_S32    VENC_DRV_EflSetResolution(VeduEfl_EncPara_S* EncHandle, HI_U32 FrameWidth, HI_U32 FrameHeight);
HI_S32    VENC_DRV_EflResumeVedu(HI_VOID);
HI_S32    VENC_DRV_EflSkpBitStream(VeduEfl_EncPara_S* EncHandle, VeduEfl_NALU_S* pNalu );
HI_S32    VENC_DRV_EflQueryStatInfo(VeduEfl_EncPara_S* EncHandle, VeduEfl_StatInfo_S* pStatInfo);
HI_S32    VENC_DRV_EflQueueFrame(VeduEfl_EncPara_S* EncHandle, HI_DRV_VIDEO_FRAME_S* pstFrame);
HI_S32    VENC_DRV_EflDequeueFrame(VeduEfl_EncPara_S* EncHandle, HI_DRV_VIDEO_FRAME_S* pstFrame);
HI_S32    VENC_DRV_EflGetImage(HI_S32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S* pstFrame);
HI_S32    VENC_DRV_EflGetImage_OMX(HI_S32 EncUsrHandle, venc_user_buf* pstFrame);
HI_S32    VENC_DRV_EflPutImage(HI_S32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S* pstFrame);

HI_S32  VENC_DRV_EflCfgRegVenc(VeduEfl_EncPara_S *EncHandle);
HI_VOID VENC_DRV_EflSortPriority(HI_VOID);

HI_VOID VENC_DRV_EflWakeUpThread(HI_VOID);

HI_S32  VENC_DRV_EflQFrameByAttach(HI_U32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S *pstFrame);
HI_S32  VENC_DRV_EflRlsAllFrame(VeduEfl_EncPara_S *EncHandle);

HI_S32  VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S *pstFrame,HI_CHAR *pFileName);
HI_VOID VENC_DRV_EflSuspendVedu(HI_VOID);
HI_S32  VENC_DRV_EflFlushStrmHeader(VeduEfl_EncPara_S  *pEncPara);

HI_S32  VENC_DRV_EflAllocBuf2Jpge(VeduEfl_EncPara_S *EncHandle, HI_U32 CapLevel);
HI_S32  VENC_DRV_EflFreeBuf2Jpge(VeduEfl_EncPara_S *EncHandle);


HI_VOID SetStreamInfo(VeduEfl_EncPara_S *pEncPara, STRMMNG_STREAM_INFO_S *pstStreamInfo);

/*************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif //__DRV_VENC_EFL_H__
