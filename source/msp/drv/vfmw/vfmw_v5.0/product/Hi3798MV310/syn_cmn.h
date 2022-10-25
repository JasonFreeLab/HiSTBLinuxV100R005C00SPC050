

#ifndef __SYNTAX_COMMON_HEADER__
#define __SYNTAX_COMMON_HEADER__

#include "vfmw.h"
#include "scd_drv.h"


#define IMG_ID_MAGIC_STEP      (100)

/* MPEG2, MPEG4����ƴ����������ݽṹ */
typedef struct
{
    STREAM_SEG_S    StreamPack[2];  // for vfmw decode
} DEC_STREAM_PACKET_S;

typedef struct
{
    //     STREAM_SEG_S    StreamSeg[MAX_STREAM_SEG_NUM];
    //     UINT32          SegNum;
    UINT8           FoundPicFlag;
    UINT8           IsCurrSegWaitDec;
    UINT8           ConvolutionPacketNum;
    STREAM_SEG_S    CurrSeg;
    DEC_STREAM_PACKET_S    Pack;  // for vfmw decode
    DEC_STREAM_PACKET_S    LastPack;
    UINT8                  u32SCDWrapAround;
} STREAM_SEG_PACKET_S;

typedef struct hiIMAGE_SIDE_INFO_S
{
    UINT32     OldAspectRatio;
    UINT32     OldScanType;
    UINT32     OldSeqCnt;
    UINT32     OldFrameRate;
    UINT32     OldDispSize;
    UINT32     OldDispCenter;
    UINT32     LastImageIdPlus2;

    UINT32     ImageWidth;
    UINT32     ImageHeight;
    UINT32     VideoFormat;
    IMAGE_FORMAT ImageFormat;

    UINT32     SeqImgCnt;
    UINT32     SeqCnt;

    /* time stamp calculation */
    UINT32     PrevNumFramesBtwPTS;
    UINT64     PrevPts;
    UINT64     AveragePtsStep;  /* smoothed by a FIR filter */

} IMAGE_SIDE_INFO_S;

/* video output queue(VO queue)  */
typedef struct
{
    UINT16     max_queue_size;
    UINT16     queue_size;
    UINT16     history;
    UINT16     head;
    UINT16     tail;
    IMAGE      *image_ptr[MAX_QUEUE_IMAGE_NUM];
    IMAGE_SIDE_INFO_S  SideInfo;
    UINT32     ResetMagicWord;
} IMAGE_VO_QUEUE;


typedef struct hiSYNTAX_EXTRA_DATA_S
{
    SINT32     s32RefErrThr;
    SINT32     s32OutErrThr;
    SINT32     s32DecMode;   /* 0,1,2 = IPB,IP,I */
    SINT32     s32CrcMode;
    UADDR      s32SyntaxMemAddr;
    SINT32     s32SyntaxMemSize;
    OUTPUT_ORDER_E eOutputOrder;
    VDEC_CHAN_CAP_LEVEL_E eCapLevel;
    UADDR      s32BpdMemAddr;
    SINT32     s32BpdMemSize;
    UADDR      s32Vp8SegIdMemAddr;
    SINT32     s32Vp8SegIdMemSize;
    UADDR      s32Vp9SegIdMemAddr;
    SINT32     s32Vp9SegIdMemSize;
    //VFMW_STATE stState;
    UINT64     pts;
    UINT64     NextPts;
    UINT64     Usertag;
    UINT64     NextUsertag;
    UINT64     DispTime;
    UINT64     NextDispTime;
    UINT32     DispEnableFlag;
    UINT32     DispFrameDistance;
    UINT32     DistanceBeforeFirstFrame;
    UINT32     NextDispEnableFlag;
    UINT32     NextDispFrameDistance;
    UINT32     NextDistanceBeforeFirstFrame;
    UINT32     GopNum;
    UINT32     NextGopNum;

    STREAM_SEG_PACKET_S  stSegPacket;
    SINT32     s32NewPicSegDetector;
    STD_EXTENSION_U    StdExt;
    //VDEC_CHAN_STATE_S  stChanState;
    UINT32     profile;
    UINT32     level;
    SINT32     error_frame_num;
    SINT32     s32BasicCtxSize;
    UADDR      s32ContextMemAddr;
    SINT32     s32ContextMemSize;
    SINT32     CompressEn;
    SINT32     s32LossCompressEn;
    SINT32     s32YCompRatio;
    SINT32     s32UVCompRatio;
    SINT32     s32MoreGapEnable;
    SINT32     s32FastForwardBackwardSpeed;
    SINT32     s32KeepSPSPPS;                      /* keep global info in ctx for seek reset */
    SINT32     s32SupportAllP;                     /* support stream of all p frames */
    SINT32     s32ModuleLowlyEnable;               /*ģ������ʱʹ�ܱ�־*/
    SINT32     s32LowdlyEnable;                    /*SCD֡�ڵ���ʱʹ�ܱ�־*/
    SINT32     s32SedOnlyEnable;                    /*SED֡�ڵ���ʱʹ�ܱ�־*/
    SINT32     s32UVMOSEnable;                     /*UVMOSʹ�ܱ�־*/
    SINT32     s32ScdMmuEn;
    SINT32     s32VdhMmuEn;
    VFMW_CONTROLINFO_S stPvrInfo;
#if 0
    SINT32    s32SupportBFrame;  /* ͨ���Ƿ�֧��B֡�����Ƿ�֧��B֡���� 0: ��֧�� 1: ֧��*/
    SINT32    s32MaxRefFrameNum;  /*������֧�ֲο�֡���������ֵ,���ĳ�����ο�֡�������ڴ�ֵ������ܲ������
                                      0:   ��ָʾͨ���ο�֡ϸ�ں��Ƿ�֧��B֡�� s32SupportBFrame��s32MaxRefFrameNum����Ч����ȫ������ǰ�ӿ�����ͨ��
                                      ��0: ������֧�ֲο�֡���������ֵ��s32SupportBFrame��s32MaxRefFrameNum����Ч������ͨ��ʱ��ο�������Ԫ�ء�*/
#endif
    VDEC_CHAN_OPTION_S stChanOption;/*ͨ������ΪCAP_LEVEL_USER_DEFINE_WITH_OPTIONʱ���û�ָ��ѡ������*/


    //add  2012.11.20
    VDEC_DISPIC_PARAM_S stDisParams;  //��֡����
    SINT32 s32WaitFsFlag;//�ȴ�����֡���־l00273086

    UINT32 widthInMB;
    UINT32 heightInMB;
    //HEVC 10Bit
    SINT32 s32BitDepth;
    SINT32 s32BitDepthChanged;
    SINT32      s32Is4k60fps;      //1: ��ͨ�����ڲ��ŵ���4k60����
    UINT8       StopRecord;
    SINT32    b98mv200Vp9Burst;
} SYNTAX_EXTRA_DATA_S;



VOID ReleasePacket(VID_STD_E VidStd, VOID *pCtx);


SINT32 OpenUsdPool(SINT32 ChanID);
VOID CloseUsdPool(SINT32 ChanID);

SINT32  InitUsdPool(SINT32 ChanID);
VDEC_USRDAT_S *GetUsd(SINT32 ChanID);
VOID FreeUsdByDec(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );
VOID MarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );
VOID UnMarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );

#endif


