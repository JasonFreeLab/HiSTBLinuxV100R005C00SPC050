#ifndef __DRV_VENC_RC_H__
#define __DRV_VENC_RC_H__

#include "venc_rc_ext.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    UINT32 PicBits;
    UINT32 IsIntraPic;

    SINT32 FrmNumInGop;                 //frame number in gop minus 1

    /*******bits***********/
    UINT64 GopBits;                     //bits in gop
    SINT32 AverageFrameBits;            //average bits of one frame
    SINT32 IPreQp;                      //Qp of previous six I frames
    SINT32 PPreQP;
    SINT32 PreTargetBits;

    /*********IMB***********/
    SINT32 NumIMBCurFrm;                //number of I MB in current  frame
    SINT32 NumIMB[6];                   //number of I MB of previous six frames
    SINT32 AveOfIMB;                    //average number of I MB of previous six frames

    /** scence change detect **/
    UINT32 IMBRatioCurScen[6];          //number of I MB of previous six frames just for scence change judge

    /*********RC Out***********/
    UINT32 CurQp;
    UINT32 TargetBits;
    UINT32 StartQP;
    SINT32 InitialQp;

    /***** parameter set ******/
    SINT32 MinTimeOfP;
    SINT32 MaxTimeOfP;
    SINT32 DeltaTimeOfP;
    SINT32 CurTimeOfP[2];                //0:Intra    1:Inter
    UINT32 IPQPDelta;
    SINT32 WaterlineInit;
    SINT32 Waterline;
    UINT32 LastFrameTypeIsIntra;

    /***** I/P bits set *******/
    UINT32 IPicBits[2];
    UINT32 PPicBits[5];
    UINT32 IPicBitsHead;
    UINT32 PPicBitsHead;

    /*** instant bits set ****/
    UINT32 InstBits[65];                  //the instant bitrate of last frame
    UINT32 InstBitsLen;
    UINT32 InstBitsSum;
    UINT32 InstBitsHead;                  //以上4个值跟外部stBitsFifo的功能有类似

    UINT32 PreInstBitsSum;
    UINT32 LastLen;
    UINT32 LastGop;
    UINT32 LastBitRate;

    /**********VBR set************/
    UINT32 VBR_SumOfQP;
    SINT32 VBR_SumOfDeltaPicBits;
    SINT32 LastSumOfDeltaPicBits;
    UINT32 VBR_MinQP;
    UINT32 VBR_MaxBitRate;
    SINT32 FrmNumSeq;                    //frame number in sequence

    VENC_RC_CFG_S ConfigInfo;

    //UINT32 RcStart;
    //UINT32 H264FrmNum;
    //UINT32 VencBufFull;
    //UINT32 VencPbitOverflow;
    //UINT32 bFrmRateSataError;
    //UINT32 IFrmInsertFlag;
    //UINT32 Recode;         //1: frame need to be recoded   0: not need;  just reencode one time
    //UINT32 ReStartQP;
    //SINT32 IQpDelta;                  //只有逻辑使用，RC并没有使用到
    //SINT32 PQpDelta;                  //只有逻辑使用，RC并没有使用到
} VENC_RC_CTX_S;



#ifdef __cplusplus
}
#endif

#endif  // __DRV_VENC_RC_H__