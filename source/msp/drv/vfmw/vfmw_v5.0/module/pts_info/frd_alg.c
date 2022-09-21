
/***********************************************************************
*
* Copyright (c) 2006  - All Rights Reserved
*
* File: $hdr.h$
* Date: $2016/09/27$
* Revision: $v1.0$
* Purpose: interface header file of HDR module
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2016/11/22                              Original
*
*
* Dependencies:
*
************************************************************************/

#include "public.h"
#include "vfmw_osal_ext.h"
#include "frd_alg.h"
#include <asm/div64.h>


/*-------------------------------LOCAL MACRO----------------------------------*/
/* 专为DPT 猜帧帧率而增加的宏定义，定义常用的帧率，后续可以增加 */
#define FRD_FPS_24                             (24)
#define FRD_FPS_25                             (25)
#define FRD_FPS_30                             (30)
#define FRD_FPS_50                             (50)
#define FRD_FPS_60                             (60)
#define FRD_FPS_120                            (120)

#define FRD_INFRAME_RATE_JUMP_THRESHOLD        (10)
#define FRD_INFRAME_RATE_WAVE_THRESHOLD        (2)

/* 定义为1200的意义是表示支持最大的帧率为120fps,可根据后续的发展而重新修改 */
#define FRD_SAMPLE_FRAME_RATE_MAX_DIFF         (1200)

#define FRD_MAX_PTS_DIFF_IN_100US              (100000)
#define FRD_MIN_PTS_DIFF_IN_100US              (40)


/*-----------------------------LOCAL DEFINITION-------------------------------*/
typedef enum
{
    NORMAL_FRATE_MODE = 0,
    SAMPLE_FRATE_MODE,
    INVALIDE_FRATE_MODE,

} FRD_FRATE_MODE_E;


/*----------------------------INTERNAL FUNCTION-------------------------------*/
static UINT32 FRD_InPtsSqn_CalNowRate(FRD_ALG_INFO_S *pPtsInfo, UINT32 env, FRD_FRATE_MODE_E eMode)
{
    UINT32 nowRate = 0;
    SINT64 PtsDiff = 0;
    SINT32 tmp = 0;

    switch (eMode)
    {
        case NORMAL_FRATE_MODE:
            if (1 == env)
            {
                PtsDiff = pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr] - pPtsInfo->InPtsSqn[0];
                PtsDiff = FRD_Divide(10 * PtsDiff, pPtsInfo->CurPtsPtr);
            }
            else
            {
                PtsDiff = pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr] - pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr - 1];
                PtsDiff = 10 * PtsDiff;
            }
            break;

        case SAMPLE_FRATE_MODE:
            if (1 == env)
            {
                PtsDiff = pPtsInfo->SamplePtsInfo[pPtsInfo->SampleActNum - 1] - pPtsInfo->SamplePtsInfo[0];
                PtsDiff = FRD_Divide(10 * PtsDiff, pPtsInfo->SampleActNum);
            }
            else
            {
                PtsDiff = pPtsInfo->SamplePtsInfo[pPtsInfo->SampleActNum - 1] - pPtsInfo->SamplePtsInfo[pPtsInfo->SampleActNum - 2];
                PtsDiff = 10 * PtsDiff;
            }
            break;

        default:
            break;
    }

    if ((PtsDiff <= (SINT64)(FRD_MAX_PTS_DIFF_IN_100US * (UINT64)(pPtsInfo->PtsUnit))) && (PtsDiff >= (SINT64)(FRD_MIN_PTS_DIFF_IN_100US * (UINT64)(pPtsInfo->PtsUnit)))) //fps>0.1 && fps< 250
    {
        tmp = (SINT32)(FRD_Divide(PtsDiff, pPtsInfo->PtsUnit));

        if (tmp != 0)
        {
            nowRate = 1000000 / tmp;
            nowRate = FRD_ROUND(nowRate);
            nowRate = nowRate / 10;
        }
    }
    else
    {
        nowRate = 0;
    }

    return nowRate;
}

static VOID FRD_InPtsSqn_ChangeInFrameRate(FRD_ALG_INFO_S *pPtsInfo, UINT32 nowRate)
{
    pPtsInfo->InFrameRate = nowRate;

    if (nowRate > 50)
    {
        pPtsInfo->Length = pPtsInfo->InFrameRate / 10;
    }
    else
    {
        pPtsInfo->Length = 5;
    }

    if (pPtsInfo->InFrameRate > 300)
    {
        pPtsInfo->StableThreshold = pPtsInfo->InFrameRate/100;
    }
    else
    {
        pPtsInfo->StableThreshold = 3;
    }

    return;
}

static VOID FRD_CalAvrgFrameRate(FRD_ALG_INFO_S *pPtsInfo)
{
    UINT32 nowRate;
    SINT32 rateDiff;
    UINT32 CalRate;
    SINT32 s32WaveDelta;

    nowRate = FRD_InPtsSqn_CalNowRate(pPtsInfo, 1, NORMAL_FRATE_MODE);

    rateDiff = (pPtsInfo->InFrameRate > nowRate)? (pPtsInfo->InFrameRate - nowRate): (nowRate - pPtsInfo->InFrameRate);

    /* For stream about 30fps, use bigger JUMP hreshold, accept wider PTS diff range */
    /* CNcomment: 对30fps左右的常用码流,加大微小变化回归门限，
        因为前面门限加大，可能会导致全队列算出的平均帧率存在抖动，放大该门限，避免输出帧率频繁微小变化 */
    if(pPtsInfo->InFrameRateLast >= 200 && pPtsInfo->InFrameRateLast <= 400)
    {
        s32WaveDelta = 50;
    }
    else
    {
        s32WaveDelta = pPtsInfo->InFrameRateLast / FRD_INFRAME_RATE_JUMP_THRESHOLD / FRD_INFRAME_RATE_WAVE_THRESHOLD;
    }

    /* detect the tiny rate wave*/
    if (rateDiff > s32WaveDelta)
    {
        CalRate = (pPtsInfo->InFrameRate != 0)? (nowRate+pPtsInfo->InFrameRate) / 2 : nowRate;
        FRD_InPtsSqn_ChangeInFrameRate(pPtsInfo, CalRate);
        pPtsInfo->InFrameRateLast = nowRate;
    }
    else
    {
        /* the second time pPtsInfo->InFrameRateLast == nowRate,we adjust InFrameRate as
           nowRate,because the tiny ratediff between InframeRate and actual FrameRate may exist*/
        if (pPtsInfo->InFrameRateLast == nowRate)
        {
            if (FRD_ABS(rateDiff) > (pPtsInfo->InFrameRateLast / FRD_INFRAME_RATE_JUMP_THRESHOLD / FRD_INFRAME_RATE_WAVE_THRESHOLD)
             && pPtsInfo->InFrameRate != 0)
            {
                CalRate = (nowRate+pPtsInfo->InFrameRate) / 2;
            }
            else
            {
                CalRate = nowRate;
            }
            FRD_InPtsSqn_ChangeInFrameRate(pPtsInfo, CalRate);
        }
        else
        {
            pPtsInfo->InFrameRateLast = nowRate;
        }
    }

    /* reset the PTSSqn,reserve the latest one pts data*/
    FRD_Reset(pPtsInfo, 1);

    return;
}

static VOID FRD_AdjustRateDiff(FRD_ALG_INFO_S *pPtsInfo, UINT32 nowRate)
{
    UINT32 u32Stable;
    SINT32 rateDiff;

    pPtsInfo->InFrameRateEqueTime++;

    /* if 3 == pPtsInfo->InFrameRateEqueTime, we think the fps has been stable, so reset the unableTime */
    if (3 == pPtsInfo->InFrameRateEqueTime
        || nowRate == pPtsInfo->InFrameRate)
    {
        pPtsInfo->UnableTime = 0;
    }

    /* For stream about 30fps, use bigger JUMP hreshold, accept wider PTS diff range */
    /* CNcomment: 对30fps左右的常用码流,加大帧率变化稳定门限，保证不会因为两三帧稳定的PTS抖动导致无法检测出有效帧率*/
    /* calculate the times of occurrence of stability of new frame rate*/
    if(pPtsInfo->InFrameRateLast >= 200 && pPtsInfo->InFrameRateLast <= 400)
    {
        u32Stable = 10;
    }
    else
    {
        u32Stable = pPtsInfo->StableThreshold;
    }

    if (pPtsInfo->InFrameRateEqueTime == u32Stable)
    {
        nowRate = FRD_InPtsSqn_CalNowRate(pPtsInfo, 1, NORMAL_FRATE_MODE);
        rateDiff = nowRate - pPtsInfo->InFrameRate;

        if (FRD_ABS(rateDiff) > pPtsInfo->InFrameRate / FRD_INFRAME_RATE_JUMP_THRESHOLD)
        {
            FRD_InPtsSqn_ChangeInFrameRate(pPtsInfo, nowRate);

            pPtsInfo->InFrameRateLast = pPtsInfo->InFrameRate;
        }
    }

    /* when InPtsSqn is full,calculate the average fps */
    if (pPtsInfo->CurPtsPtr == pPtsInfo->Length-1)
    {
        FRD_CalAvrgFrameRate(pPtsInfo);
    }
    else
    {
        pPtsInfo->CurPtsPtr++;
    }

    return;
}

static VOID FRD_AdjustRate(FRD_ALG_INFO_S *pPtsInfo, UINT32 nowRate)
{
    UINT32 u32JumpDelta;
    SINT32 rateDiff;

    rateDiff = nowRate - pPtsInfo->InFrameRateLast;

    /* For stream about 30fps, use bigger JUMP hreshold, accept wider PTS diff range */
    /* CNcomment: 对30fps左右的常用码流,放大JUMP门限，将PTS抖动纳入正常范围*/
    if(pPtsInfo->InFrameRateLast >= 200 && pPtsInfo->InFrameRateLast <= 400)
    {
        u32JumpDelta = 200;
    }
    else
    {
        u32JumpDelta = pPtsInfo->InFrameRateLast / FRD_INFRAME_RATE_JUMP_THRESHOLD;
    }

    if (FRD_ABS(rateDiff) > u32JumpDelta)
    {
        pPtsInfo->UnableTime++;
        if (10 == pPtsInfo->UnableTime)
        {
            pPtsInfo->InFrameRate = 0;
            pPtsInfo->UnableTime  = 0;
        }

        pPtsInfo->InFrameRateLast = nowRate;

        /* the StableThreshold = fps/10; in order to detect the fps change quickly; */
        if (nowRate > 300)
        {
            pPtsInfo->StableThreshold = nowRate / 100;
        }
        else
        {
            pPtsInfo->StableThreshold = 3;
        }

        /* reset the PTSSqn,reserve the lastest two pts data*/
        FRD_Reset(pPtsInfo, 2);
    }
    else
    {
        FRD_AdjustRateDiff(pPtsInfo, nowRate);
    }

    return;
}

static VOID FRD_PTS_Sample(FRD_ALG_INFO_S *pPtsInfo, UINT64 Pts)
{
    UINT32 nowRate;

    pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr] = Pts;

    nowRate = FRD_InPtsSqn_CalNowRate(pPtsInfo, 0, NORMAL_FRATE_MODE);

    if (nowRate)
    {
        FRD_AdjustRate(pPtsInfo, nowRate);
    }
    else
    {
        /* nowRate = 0,we think it is a unstable fps*/
        pPtsInfo->UnableTime++;
        if (10 == pPtsInfo->UnableTime)
        {
            pPtsInfo->InFrameRate = 0;
            pPtsInfo->UnableTime  = 0;
        }

        FRD_Reset(pPtsInfo, 1);
    }

    return;
}

static VOID FRD_UpdateNewRate(FRD_ALG_INFO_S *pPtsInfo, UINT64 Pts)
{
    UINT32 Delta = 0;
    UINT32 NewRate = 0;

    if (Pts > pPtsInfo->CalPts)
    {
        Delta = FRD_Divide(Pts - pPtsInfo->CalPts, 60);
    }
    else
    {
        Delta = FRD_Divide(pPtsInfo->CalPts - Pts, 60);
    }

    if(0 != Delta)
    {
        NewRate = FRD_Divide((SINT64)(10000*(UINT64)(pPtsInfo->PtsUnit)), Delta);
    }

    if (FRD_ABS((SINT32)(NewRate - pPtsInfo->QueRate)) < 10)
    {
        if (pPtsInfo->QueStable < 3)
        {
            pPtsInfo->QueStable++;
        }
    }
    else
    {
        pPtsInfo->QueRate = NewRate;
        pPtsInfo->QueStable = 0;
    }

    pPtsInfo->CalPts = Pts;
    pPtsInfo->QueCnt = 0;

    return;
}


/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID FRD_Reset(FRD_ALG_INFO_S *pPtsInfo, UINT32 PtsNum)
{
    UINT64 nowPts;
    UINT64 prePts;
    UINT32 i;

    if (PtsNum)
    {
        if (PtsNum == 1)
        {
            nowPts = pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr];
            for (i = 0; i < FRD_IN_PTS_SEQUENCE_LENGTH; i++)
            {
                pPtsInfo->InPtsSqn[i] = FRD_INVALID_PTS_64;
            }
            pPtsInfo->InPtsSqn[0] = nowPts;
            pPtsInfo->CurPtsPtr = 1;
            pPtsInfo->InFrameRateEqueTime = 0;
        }
        else//PtsNum == 2
        {
            nowPts = pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr];
            prePts = pPtsInfo->InPtsSqn[pPtsInfo->CurPtsPtr-1];
            for (i = 0; i < FRD_IN_PTS_SEQUENCE_LENGTH; i++)
            {
                pPtsInfo->InPtsSqn[i] = FRD_INVALID_PTS_64;
            }
            pPtsInfo->InPtsSqn[0] = prePts;
            pPtsInfo->InPtsSqn[1] = nowPts;
            pPtsInfo->CurPtsPtr = 2;
            pPtsInfo->InFrameRateEqueTime = 1;
        }
    }
    else
    {
        for (i = 0; i < FRD_IN_PTS_SEQUENCE_LENGTH; i++)
        {
            pPtsInfo->InPtsSqn[i] = FRD_INVALID_PTS_64;
        }
        pPtsInfo->InFrameRateEqueTime = 0;
        pPtsInfo->CalPts = FRD_INVALID_PTS_64;
        pPtsInfo->QueCnt = 0;
        pPtsInfo->QueStable = 0;
    }

    return;
}

/* 函数功能描述如下
   1. 检测传入的帧率，如果在常见标准值范围内，则返回一个标准的NewFrameRate
   当前认为标准的帧率有: (24,25,29.975,30,50,59.975,60,120) 后续持续更新,如果不是
   规范帧率，且又不在规范帧率正负一之间，那么保持原样。(24列外，正0.5负1) */
VOID FRD_RoundFrmRate(UINT32 u32FrameRate, UINT32 *pNewFrameRate)
{
    UINT32 u32Integer = 0;
    UINT32 NewFrameRate = 0;

    u32Integer = u32FrameRate/10;
    switch(u32Integer)
    {
        case (FRD_FPS_24 - 1):
            NewFrameRate = 240;
            break;
        case (FRD_FPS_24):
            if (FRD_ABS((SINT32)(u32FrameRate - 240)) < 5)
            {
                NewFrameRate = 240;
            }
            else
            {
                NewFrameRate = 250;
            }
            break;
        case (FRD_FPS_25):
            NewFrameRate = 250;
            break;
        case (FRD_FPS_30 - 1):
        case (FRD_FPS_30):
        case (FRD_FPS_30 + 1):
            NewFrameRate = 300;
            break;
        case (FRD_FPS_50 - 1):
        case (FRD_FPS_50):
        case (FRD_FPS_50 + 1):
            NewFrameRate = 500;
            break;
        case (FRD_FPS_60 - 1):
        case (FRD_FPS_60):
        case (FRD_FPS_60 + 1):
            NewFrameRate = 600;
            break;
        case (FRD_FPS_120 - 1):
        case (FRD_FPS_120):
        case (FRD_FPS_120 + 1):
            NewFrameRate = 1200;
            break;
        default:
            NewFrameRate = 0;
            break;
    }

    *pNewFrameRate = NewFrameRate;

    return;
}

SINT64 FRD_Divide(SINT64 Dividend, UINT32 Divider)
{
    SINT64 remainder = 0, ret = 0;
    SINT64 tmp = Dividend;

    if (Divider)
    {
        remainder = do_div(tmp, Divider);
        ret = tmp;
    }

    return ret;
}

UINT32 FRD_FrameRateDetect(FRD_ALG_INFO_S *pPtsInfo, UINT64 Pts)
{
    if (pPtsInfo->CalPts == FRD_INVALID_PTS_64)
    {
        pPtsInfo->CalPts = Pts;
    }
    else
    {
        pPtsInfo->QueCnt = pPtsInfo->QueCnt+1;
    }

    if (pPtsInfo->QueCnt == 61)
    {
        FRD_UpdateNewRate(pPtsInfo, Pts);
    }

    if (pPtsInfo->InPtsSqn[0] != FRD_INVALID_PTS_64)
    {
        FRD_PTS_Sample(pPtsInfo, Pts);
    }
    else
    {
        FRD_InPtsSqn_ChangeInFrameRate(pPtsInfo, 0);

        FRD_Reset(pPtsInfo,0);

        pPtsInfo->InPtsSqn[0] = Pts;
        pPtsInfo->CurPtsPtr = 1;
        pPtsInfo->UnableTime = 0;
        pPtsInfo->InFrameRateLast = pPtsInfo->InFrameRate;
    }

    if(pPtsInfo->QueStable == 3 && pPtsInfo->InFrameRate == 0)
    {
        pPtsInfo->InFrameRate = pPtsInfo->QueRate;
    }

    return pPtsInfo->InFrameRate;
}

/*函数功能描述如下
   1. 记录前N帧的PTS，计算出两两帧的帧率(N可被指定，默认为10)
   2. 找出其最大&最小值，并计算其平均值
   3. 当达到预定值N时，且平均值与最大最小值的绝对值相差在可接受范围内则给出平均值做为帧率 */
UINT32 FRD_SampleFrmRateDetect(FRD_ALG_INFO_S *pPtsInfo,HI_U64 Pts)
{
    UINT32 u32FrameRate = 0;
    UINT32 NowRate = 0;
    SINT32 MaxAvgDiff = 0;
    SINT32 MinAvgDiff = 0;

    /* 1. 如果SampleIndexMaxNum大于门限100，则不进行Sample猜帧策略 */
    if (pPtsInfo->SampleMaxNum > FRD_IN_PTS_SEQUENCE_LENGTH ||
        pPtsInfo->SampleMaxNum == 0)
    {
        return u32FrameRate;
    }

    /* 1.1 如果PTSInfoIdex的值超过了门限，则返回之前的有效的帧率，不再进行计算。*/
    if (pPtsInfo->SampleActNum >= FRD_IN_PTS_SEQUENCE_LENGTH)
    {
        u32FrameRate = (pPtsInfo->SampleLastFrameRate / 1000) * 10 + (pPtsInfo->SampleLastFrameRate % 1000);

        return u32FrameRate;
    }

    /* 2. 当计算收到两帧PTS时，即可算得一个帧率，@@@无效的PTS如何处理??
          按照之前的PTS收敛帧率的算法，先确保第一帧PTS为有效帧。*/
    if (FRD_INVALID_PTS_64 != pPtsInfo->SamplePtsInfo[0])
    {
        pPtsInfo->SamplePtsInfo[pPtsInfo->SampleActNum] = Pts;
    }
    else
    {
        pPtsInfo->SamplePtsInfo[0] = Pts;
    }
    pPtsInfo->SampleActNum++;

    if (pPtsInfo->SampleActNum < 2)
    {
        return u32FrameRate;
    }
    NowRate = FRD_InPtsSqn_CalNowRate(pPtsInfo, 0, SAMPLE_FRATE_MODE);

    /* 3. 更新最大最小值,SampleMaxRate为0，说明SampleMaxRate从来没有收到过一个有效的值。
          只要收到过有效的值，则自行更新最大最小值。*/
    if (0 == pPtsInfo->SampleMaxRate)
    {
        pPtsInfo->SampleMaxRate = pPtsInfo->SampleMinRate = NowRate;
    }
    else
    {
        pPtsInfo->SampleMaxRate = NowRate > pPtsInfo->SampleMaxRate? NowRate:
                                  pPtsInfo->SampleMaxRate;
        pPtsInfo->SampleMinRate = (0 == NowRate? pPtsInfo->SampleMinRate:
                                   (NowRate < pPtsInfo->SampleMinRate? NowRate: pPtsInfo->SampleMinRate));
    }

    /* 4. 当满足条件时，计算一个平均帧率，计算方法为最后一个PTS与第一个PTS的差值
          取平均再来计算相关帧率; 判断是否满足条，选择是否给出一个有效帧率 */
    if (pPtsInfo->SampleActNum >= pPtsInfo->SampleMaxNum)
    {
        NowRate = FRD_InPtsSqn_CalNowRate(pPtsInfo, 1, SAMPLE_FRATE_MODE);
        /* 如果通过上面的计算得到的平均值不在最大与最小值范围内，则
           该值已经不可信,则取最大与最小值的和平均。*/

        if ((NowRate >= pPtsInfo->SampleMaxRate) || (NowRate <= pPtsInfo->SampleMinRate))
        {
            NowRate = (pPtsInfo->SampleMaxRate + pPtsInfo->SampleMinRate)/2;
        }

        pPtsInfo->SampleAvgRate = NowRate;
        MaxAvgDiff = FRD_ABS((SINT32)(pPtsInfo->SampleMaxRate - NowRate));
        MinAvgDiff = FRD_ABS((SINT32)(pPtsInfo->SampleMinRate - NowRate));
        if ((MaxAvgDiff <= FRD_SAMPLE_FRAME_RATE_MAX_DIFF) &&
            (MinAvgDiff <= FRD_SAMPLE_FRAME_RATE_MAX_DIFF))
        {
            u32FrameRate = pPtsInfo->SampleAvgRate;
        }
    }

    return u32FrameRate;
}

