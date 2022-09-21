#ifndef __FRD_ALG_H__
#define __FRD_ALG_H__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------EXTERNAL MACRO----------------------------------*/
#define FRD_INVALID_PTS_64           (-1)
#define FRD_IN_PTS_SEQUENCE_LENGTH   (100)

#define FRD_ABS(x)                   (((x) < 0) ? -(x) : (x))
#define FRD_ROUND(x)                 (((x % 10) > 4) ? (x / 10 + 1) * 10 : x)


/*----------------------------EXTERNAL DEFINITION-----------------------------*/
typedef struct
{
    UINT32  PtsUnit;
    UINT32  CurPtsPtr;                                     /* pointer of past PTS information, pointing to the oldest frame rate in record */
    UINT32  Length;
    UINT32  QueCnt;
    UINT32  QueRate;
    UINT32  QueStable;
    UINT32  UnableTime;
    UINT32  InFrameRateLast;                               /* last input frame rate */
    UINT32  StableThreshold;
    UINT32  InFrameRateEqueTime;                           /* counter of stable frame rate, to avoid display shake caused by shake of frame rate */
    UINT32  InFrameRate;
    UINT64  CalPts;
    UINT64  InPtsSqn[FRD_IN_PTS_SEQUENCE_LENGTH];          /* past PTS information */

    /* for sample frame rate detect */
    VBOOL   SampleFRDEnable;
    UINT32  SampleMaxRate;
    UINT32  SampleMinRate;
    UINT32  SampleAvgRate;
    UINT32  SampleActNum;
    UINT32  SampleMaxNum;
    UINT32  SampleLastFrameRate;
    HI_U64  SamplePtsInfo[FRD_IN_PTS_SEQUENCE_LENGTH];     /* past PTS information */

} FRD_ALG_INFO_S;


/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID   FRD_Reset(FRD_ALG_INFO_S *pPtsInfo, UINT32 PtsNum);
VOID   FRD_RoundFrmRate(UINT32 FrameRate, UINT32 *pNewFrameRate);
SINT64 FRD_Divide(SINT64 Dividend, UINT32 Divider);
UINT32 FRD_FrameRateDetect(FRD_ALG_INFO_S *pPtsInfo, UINT64 Pts);
UINT32 FRD_SampleFrmRateDetect(FRD_ALG_INFO_S *pPtsInfo, HI_U64 Pts);


#ifdef __cplusplus
}
#endif

#endif

