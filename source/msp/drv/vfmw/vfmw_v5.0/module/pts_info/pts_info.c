
/***********************************************************************
*
* Copyright (c) 2006 - All Rights Reserved
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
* 2016/11/22               Original
*
*
* Dependencies:
*
************************************************************************/

#include "public.h"
#include "vfmw_osal_ext.h"
#include "vfmw_proc.h"
#include "pts_info.h"
#include "frd_alg.h"


/*-------------------------------LOCAL MACRO----------------------------------*/
#define PTS_INVALID_TIME_64            (-1)
#define PTS_MAX_CHAN_NUM               (MAX_CHAN_NUM)
#define PTS_MAX_FRAME_RATE             (60)                  /* fps*/
#define PTS_MAX_VALUE                  (0x1638E38B88)        /* us */
#define PTS_MAX_PASS_TIME              (120 * 1000 * 1000)   /* us */
#define PTS_MAX_FRAME_TIME_CNT         (2)
#define PTS_MAX_FRAME_TIME_JUMP        (1000)
#define PTS_DEFAULT_SAMPLE_NUM         (10)

#define PTS_PROC_NAME                  "pts_info"
#define PTS_CMD_NUM                    (2)
#define PTS_CMD_LEN                    (50)

#define PTS_CMD_SET_SAMPLE_NUM         "sample_num"


/*-----------------------------LOCAL DEFINITION-------------------------------*/
typedef struct
{
    VBOOL               bInited;
    UINT64              u64LastSrcPts;     /* Last valid src pts */
    UINT32              u32LastSrcFrmIdx;  /* The index of last frame with a valid src pts */
    UINT32              u32FrameNum;       /* Total frame number */
    UINT32              u32FrameTimeCnt;   /* Frame interval counter */
    UINT64              u64LastCalcFrmTime;/* Last calculated frame time(us) */
    UINT64              u64CalcFrameTime;  /* Calculated frame time(us) */
    UINT64              u64SetFrameTime;   /* Setted frame time(us) */
    UINT64              u64GesFrameTime;   /* Guessed frame time(us) */
    SINT32              s32InterPtsDelta;  /* interleaved source, use to adjust pts for field to frame */
    PTS_FRMRATE_S       stUserFrameRate;   /* User config frame rate */
    FRD_ALG_INFO_S      stPtsInfo;

} PTS_CHAN_INFO_S;


/*-----------------------------EXTERN VALUE-----------------------------------*/
extern SINT32 g_CurProcChan;


/*------------------------------LOCAL VALUE-----------------------------------*/
static PTS_CHAN_INFO_S g_PtsChan[MAX_CHAN_NUM];
static UINT32 g_CfgSampleNum = PTS_DEFAULT_SAMPLE_NUM;
static UINT32 g_CurSampleNum = PTS_DEFAULT_SAMPLE_NUM;


/*----------------------------INTERNAL FUNCTION-------------------------------*/
static VOID PTS_Info_InitParam(SINT32 ChanID)
{
    SINT32 i = 0;

    g_PtsChan[ChanID].u64LastSrcPts = FRD_INVALID_PTS_64;
    g_PtsChan[ChanID].u32LastSrcFrmIdx = -1;
    g_PtsChan[ChanID].u32FrameNum = 0;
    g_PtsChan[ChanID].u32FrameTimeCnt = 0;
    g_PtsChan[ChanID].u64LastCalcFrmTime = PTS_INVALID_TIME_64;
    g_PtsChan[ChanID].u64CalcFrameTime = PTS_INVALID_TIME_64;
    g_PtsChan[ChanID].u64GesFrameTime  = PTS_INVALID_TIME_64;
    g_PtsChan[ChanID].s32InterPtsDelta = 0;
    g_PtsChan[ChanID].stPtsInfo.CalPts = FRD_INVALID_PTS_64;
    g_PtsChan[ChanID].stPtsInfo.QueCnt = 0;
    g_PtsChan[ChanID].stPtsInfo.QueStable = 0;

    for (i = 0; i < FRD_IN_PTS_SEQUENCE_LENGTH; i++)
    {
        g_PtsChan[ChanID].stPtsInfo.SamplePtsInfo[i] = FRD_INVALID_PTS_64;
    }
    g_PtsChan[ChanID].stPtsInfo.SampleMaxRate = 0;
    g_PtsChan[ChanID].stPtsInfo.SampleMinRate = 0;
    g_PtsChan[ChanID].stPtsInfo.SampleAvgRate = 0;
    g_PtsChan[ChanID].stPtsInfo.SampleActNum  = 0;
    g_PtsChan[ChanID].stPtsInfo.SampleMaxNum  = g_CurSampleNum;
    g_PtsChan[ChanID].stPtsInfo.SampleLastFrameRate = 0;

    return;
}

static UINT64 PTS_Info_GetFrameTime_User(PTS_CHAN_INFO_S *pstPtsInfo, IMAGE *pstImage)
{
    UINT64 u64FrameTime = PTS_INVALID_TIME_64;

    /* Choose u64FrameTime from: 1.SetFrameTime 2.CalcFrameTime 3.GuessFrameTime*/
    if (PTS_INVALID_TIME_64 != pstPtsInfo->u64SetFrameTime)
    {
        u64FrameTime = pstPtsInfo->u64SetFrameTime;
    }
    else if (PTS_INVALID_TIME_64 != pstPtsInfo->u64CalcFrameTime)
    {
        u64FrameTime = pstPtsInfo->u64CalcFrameTime;
    }
    else
    {
        if (PTS_INVALID_TIME_64 == pstPtsInfo->u64GesFrameTime)
        {
            if (pstImage->image_width <= 720 && pstImage->image_height <= 480)
            {
                pstPtsInfo->u64GesFrameTime = 33333;  /* MAYBE NTSC */
            }
            else if (pstImage->image_width <= 720 && pstImage->image_height <= 576)
            {
                pstPtsInfo->u64GesFrameTime = 40000;  /* MAYBE PAL */
            }
            else
            {
                pstPtsInfo->u64GesFrameTime = 40000;
            }

            if (pstImage->stHDRInput.BeDVHDRChan == 1)
            {
                pstPtsInfo->u64GesFrameTime = 40000;
            }
        }

        u64FrameTime = pstPtsInfo->u64GesFrameTime;
    }

    return u64FrameTime;
}

static UINT64 PTS_Info_GetFrameTime_Other(PTS_CHAN_INFO_S *pstPtsInfo, IMAGE *pstImage)
{
    UINT64 u64FrameTime = PTS_INVALID_TIME_64;

    /* Choose u64FrameTime from: 1.u64CalcFrameTime 2.u64SetFrameTime 3.GuessFrameTime*/
    if (PTS_INVALID_TIME_64 != pstPtsInfo->u64CalcFrameTime)
    {
        u64FrameTime = pstPtsInfo->u64CalcFrameTime;
    }
    else if (PTS_INVALID_TIME_64 != pstPtsInfo->u64SetFrameTime)
    {
        u64FrameTime = pstPtsInfo->u64SetFrameTime;
    }
    else
    {
        if (PTS_INVALID_TIME_64 == pstPtsInfo->u64GesFrameTime)
        {
            if ((pstImage->image_width <= 720) && (pstImage->image_height <= 480))
            {
                pstPtsInfo->u64GesFrameTime = 33333;  /* MAYBE NTSC */
            }
            else if ((pstImage->image_width <= 720) && (pstImage->image_height <= 576))
            {
                pstPtsInfo->u64GesFrameTime = 40000;  /* MAYBE PAL */
            }
            else
            {
                pstPtsInfo->u64GesFrameTime = 40000;
            }

            if (pstImage->stHDRInput.BeDVHDRChan == 1)
            {
                pstPtsInfo->u64GesFrameTime = 40000;
            }
        }

        u64FrameTime = pstPtsInfo->u64GesFrameTime;
    }

    return u64FrameTime;
}

static VOID PTS_Info_HandleValidSrcPTS(SINT32 ChanID, IMAGE *pstImage)
{
    UINT32 u32NumPass = 0;
    UINT64 u64PtsPass = 0;
    UINT32 u32PtsDiffStep;
    UINT64 u64FrameTimeABS;
    UINT64 u64SrcPts, u64Pts;
    PTS_CHAN_INFO_S *pstPtsInfo = NULL;

    pstPtsInfo = &g_PtsChan[ChanID];
    u64SrcPts = pstImage->SrcPts;

    /* calculate StatPtsDelta based on pts delta and frame numbers between two valid src pts */
    /* CNcomment: 根据两个有效PTS间的PTS差值和帧数计算StatPtsDelta */
    if (FRD_INVALID_PTS_64 != pstPtsInfo->u64LastSrcPts)
    {
        u32NumPass = pstPtsInfo->u32FrameNum - pstPtsInfo->u32LastSrcFrmIdx;

        if (u64SrcPts >= pstPtsInfo->u64LastSrcPts)
        {
            u64PtsPass = u64SrcPts - pstPtsInfo->u64LastSrcPts;
        }
        /* pts loopback */
        /* TODO:how to distinguish pts back and loopback */
        else if (u64SrcPts < pstPtsInfo->u64LastSrcPts)
        {
            u64PtsPass = PTS_MAX_VALUE - pstPtsInfo->u64LastSrcPts + u64SrcPts;
        }

        /*calculate the frame time*/
        if (u32NumPass)
        {
            if (u64PtsPass <= PTS_MAX_PASS_TIME)
            {
                u32PtsDiffStep = (pstPtsInfo->stPtsInfo.PtsUnit == 1) ? 1000 : 1;

                /*only successive twice u64FrameTime is the same, then update u64CalcFrameTime*/
                /**CNcomment: 只有连续2次的FrameTime计算相同才会更新CalcFrameTime*/
                if (PTS_INVALID_TIME_64 != pstPtsInfo->u64CalcFrameTime)
                {
                    u64FrameTimeABS = FRD_ABS((SINT64)FRD_Divide(u64PtsPass*u32PtsDiffStep, u32NumPass) - (SINT64)(pstPtsInfo->u64LastCalcFrmTime));
                    if (u64FrameTimeABS > PTS_MAX_FRAME_TIME_JUMP)
                    {
                        pstPtsInfo->u32FrameTimeCnt = 0;
                    }

                    pstPtsInfo->u32FrameTimeCnt++;
                    if (pstPtsInfo->u32FrameTimeCnt >= PTS_MAX_FRAME_TIME_CNT)
                    {
                        pstPtsInfo->u64CalcFrameTime = FRD_Divide(u64PtsPass*u32PtsDiffStep, u32NumPass);
                        pstPtsInfo->u32FrameTimeCnt = PTS_MAX_FRAME_TIME_CNT;
                    }
                }
                else
                {
                    pstPtsInfo->u64CalcFrameTime = FRD_Divide(u64PtsPass*u32PtsDiffStep, u32NumPass);
                    pstPtsInfo->u32FrameTimeCnt++;
                }

                pstPtsInfo->u64LastCalcFrmTime = FRD_Divide(u64PtsPass*u32PtsDiffStep, u32NumPass);

                g_PtsChan[ChanID].s32InterPtsDelta = FRD_Divide(pstPtsInfo->u64CalcFrameTime, 2000);
            }
            else
            {
                /*keep the u64CalcFrameTime while pts is abnormal*/
                //dprint(PRN_ERROR, "pts %lld is abnormal!\n", u64SrcPts);
                if (u64SrcPts >= pstPtsInfo->u64LastSrcPts) /* pts jump*/
                {
                    g_PtsChan[ChanID].s32InterPtsDelta = 20;
                }
                else
                {
                    g_PtsChan[ChanID].s32InterPtsDelta = -20; /* pts back and loopback  */
                }
            }
        }
        else
        {
            dprint(PRN_ERROR, "Frame index %d repeat\n", pstPtsInfo->u32FrameNum);
            g_PtsChan[ChanID].s32InterPtsDelta = 20;
        }
    }
    else
    {
        g_PtsChan[ChanID].s32InterPtsDelta = 20;
    }

    pstPtsInfo->u64LastSrcPts = u64SrcPts;
    pstPtsInfo->u32LastSrcFrmIdx = pstPtsInfo->u32FrameNum;
    u64Pts = u64SrcPts;

    pstImage->PTS = (UINT64)u64Pts;
    pstImage->InterPtsDelta = g_PtsChan[ChanID].s32InterPtsDelta;

    return;
}

static VOID PTS_Info_HandleInValidSrcPTS(SINT32 ChanID, IMAGE *pstImage)
{
    UINT32 u32NumPass = 0;
    UINT32 u32PtsDiffStep;
    UINT64 u64FrameTime = PTS_INVALID_TIME_64;
    UINT64 u64Pts;
    PTS_CHAN_INFO_S *pstPtsInfo = NULL;

    pstPtsInfo = &g_PtsChan[ChanID];

    if (FRD_INVALID_PTS_64 != pstPtsInfo->u64LastSrcPts)
    {
        u32NumPass = pstPtsInfo->u32FrameNum - pstPtsInfo->u32LastSrcFrmIdx;

        u32PtsDiffStep = (pstPtsInfo->stPtsInfo.PtsUnit == 1) ? 1000 : 1;

    #if 0
        if (((HI_UNF_VCODEC_TYPE_REAL8 == enVdecType)
             || (HI_UNF_VCODEC_TYPE_REAL9 == enVdecType))
            && (-1 != pstPtsInfo->u64SetFrameTime))
        {
            u64Pts = pstPtsInfo->u64LastSrcPts + pstPtsInfo->u64SetFrameTime / 1000;
            pstPtsInfo->u64LastSrcPts = u64Pts;
            pstImage->PTS = (UINT64)u64Pts;
            return u64Pts;
        }
    #endif

        if (g_PtsChan[ChanID].stUserFrameRate.enFrmRateType == PTS_FRMRATE_TYPE_USER)
        {
            u64FrameTime = PTS_Info_GetFrameTime_User(pstPtsInfo, pstImage);
        }
        else /* PTS_FRMRATE_TYPE_USER_PTS etc */
        {
            u64FrameTime = PTS_Info_GetFrameTime_Other(pstPtsInfo, pstImage);
        }

        u64Pts = pstPtsInfo->u64LastSrcPts + FRD_Divide((SINT64)(u64FrameTime * u32NumPass), u32PtsDiffStep);
        g_PtsChan[ChanID].s32InterPtsDelta = FRD_Divide(u64FrameTime, 2000);
    }
    else //if (FRD_INVALID_PTS_64 != pstPtsInfo->u64LastSrcPts)
    {
        u64Pts = FRD_INVALID_PTS_64;
        g_PtsChan[ChanID].s32InterPtsDelta = 0;
    }

    pstImage->PTS = (UINT64)u64Pts;
    pstImage->InterPtsDelta = g_PtsChan[ChanID].s32InterPtsDelta;

    return;
}

static SINT32 PTS_Info_GuessFirstFrameRate(SINT32 ChanID, UINT32 u32SrcFrameRate, IMAGE *pstImage)
{
    SINT32 s32Ret;
    PTS_FRMRATE_S stFrmRate;

    memset(&stFrmRate, 0x0, sizeof(PTS_FRMRATE_S));

    s32Ret = PTS_Info_GetFrmRate(ChanID, &stFrmRate);
    if (VDEC_OK != s32Ret)
    {
        dprint(PRN_ERROR, "Get frame rate failed!\n");

        return VDEC_ERR;
    }

    /* < CNcomment: 首先相信上层设置下来的合法帧率，其次考虑VFMW解码获得的合法帧率，最后进行猜测 */
    if ((12 <= stFrmRate.stSetFrmRate.FpsInteger) && (stFrmRate.stSetFrmRate.FpsInteger <= 60))
    {
        pstImage->frame_rate = stFrmRate.stSetFrmRate.FpsInteger * 1000 + stFrmRate.stSetFrmRate.FpsDecimal;
    }
    else if ((12 <= u32SrcFrameRate) && (u32SrcFrameRate <= 60))
    {
        pstImage->frame_rate = u32SrcFrameRate * 1000;
    }
    else
    {
        if (pstImage->image_width <= 720 && pstImage->image_height <= 480)
        {
            pstImage->frame_rate = 30 * 1000;  /* < NTSC, asume the framerate is 30fps */
        }
        else if (pstImage->image_width < 1280 && pstImage->image_height < 720)
        {
            pstImage->frame_rate = 25 * 1000;  /* > NTSC, asume the framerate is 25fps */
        }
        else
        {
            pstImage->frame_rate = 30 * 1000;  /* < NTSC, asume the framerate is 30fps */
        }
    }

    return VDEC_OK;
}

static VOID PTS_Info_FrameRateDetect(SINT32 ChanID, IMAGE *pstImage)
{
    UINT32 u32FrameRate;
    UINT32 u32SrcFrameRate;
    FRD_ALG_INFO_S *pPtsInfo = HI_NULL;
    UINT32 u32RoundRate = 0,u32RoundRateHiplayer = 0;
    PTS_FRMRATE_S stFrmRate;
    SINT32 s32Ret = 0;

    memset(&stFrmRate, 0x0, sizeof(PTS_FRMRATE_S));
    u32SrcFrameRate = pstImage->frame_rate;
    pPtsInfo = &(g_PtsChan[ChanID].stPtsInfo);

    /*
     * For RWZB test, VO will use default frame rate adapted to output norm.
     * If frame type was set to STREAM type, need not detect, use stream frame rate.
     * If frame type was set to USER type, need not detect, use the user set value.
     */
    if ((pstImage->optm_inf.Rwzb == 0)
     && (g_PtsChan[ChanID].stUserFrameRate.enFrmRateType != PTS_FRMRATE_TYPE_STREAM)
     && (g_PtsChan[ChanID].stUserFrameRate.enFrmRateType != PTS_FRMRATE_TYPE_USER))
    {
        u32FrameRate = FRD_FrameRateDetect(pPtsInfo, pstImage->PTS);

        pstImage->frame_rate = u32FrameRate * 1000 / 10;
    }

    /* For DPT, to avoid the framerate of the first frame is zero */
    if (0 == pstImage->frame_rate)
    {
        /*如果满足SampleIndexMaxNum & Sample猜帧策略收敛到有效帧率
           的条件，则输出有效值；如果满足SampleIndexMaxNum & Sample猜帧策略没有收敛到有
           效帧率，则通过分辨率来猜，即OLD方案；其它返回帧率为0，由VPSS来丢帧。*/
        if (0 != pPtsInfo->SampleMaxNum)
        {
            u32FrameRate = FRD_SampleFrmRateDetect(pPtsInfo, pstImage->PTS);

            if ((pPtsInfo->SampleActNum >= pPtsInfo->SampleMaxNum) &&
                (0 == u32FrameRate))
            {
                PTS_Info_GuessFirstFrameRate(ChanID, u32SrcFrameRate, pstImage);
            }
            else if ((pPtsInfo->SampleActNum >= pPtsInfo->SampleMaxNum) &&
                     (0 != u32FrameRate))
            {
                /* 当PTS是错乱的，这时候只能选择相信hiplayer设下来的
                   有效帧率:所以这里的策略是:
                   PTS 猜帧帧率有效，优先相信
                   hiplayer 设下来的帧率有效，次之相信
                   都无效，取PTS猜帧帧率*/
                FRD_RoundFrmRate(u32FrameRate, &u32RoundRate);
                s32Ret = PTS_Info_GetFrmRate(ChanID, &stFrmRate);
                FRD_RoundFrmRate(stFrmRate.stSetFrmRate.FpsInteger*10, &u32RoundRateHiplayer);
                if(u32RoundRate > 0)
                {
                    pstImage->frame_rate = u32FrameRate * 1000 / 10;
                }
                else if ((VDEC_OK == s32Ret) && (u32RoundRateHiplayer > 0))
                {
                    pstImage->frame_rate = u32RoundRateHiplayer * 1000 / 10;
                }
                else
                {
                    pstImage->frame_rate = u32FrameRate * 1000 / 10;
                }
            }
            else
            {
                pstImage->frame_rate = 0;
            }
        }
        else
        {
            PTS_Info_GuessFirstFrameRate(ChanID, u32SrcFrameRate, pstImage);
        }
    }

    if ((pstImage->optm_inf.Rwzb == 0)
     && (g_PtsChan[ChanID].stUserFrameRate.enFrmRateType != PTS_FRMRATE_TYPE_STREAM)
     && (g_PtsChan[ChanID].stUserFrameRate.enFrmRateType != PTS_FRMRATE_TYPE_USER))
    {
        /*对合法的帧率附近的值进行取整数 */
        FRD_RoundFrmRate(((pstImage->frame_rate / 1000) * 10), &u32RoundRate);
        if (u32RoundRate > 0)
        {
            pstImage->frame_rate = u32RoundRate * 1000 / 10;
        }
    }

    pPtsInfo->SampleLastFrameRate = pstImage->frame_rate;

    return;
}

/*
 * For PTS_FRMRATE_TYPE_PTS:      Recover PTS and detect frame rate;
 * For PTS_FRMRATE_TYPE_STREAM:   Only Recover PTS, use frame rate from stream;
 * For PTS_FRMRATE_TYPE_USER:     Only Recover PTS, use user set frame rate;
 * For PTS_FRMRATE_TYPE_USER_PTS: Recover PTS and detect frame rate;
 */
SINT32 PTS_Info_CalcStamp(SINT32 ChanID, IMAGE *pstImage)
{
    PTS_CHAN_INFO_S *pstPtsInfo = NULL;

    pstPtsInfo = &g_PtsChan[ChanID];

    if (pstPtsInfo->bInited == VDEC_FALSE)
    {
        dprint(PRN_ERROR, "Start first:%d\n", ChanID);
        return VDEC_ERR;
    }

    pstPtsInfo->u32FrameNum++;
    pstPtsInfo->stPtsInfo.PtsUnit = (pstImage->format.pts_unit) ? 1000 : 1;

    /* SrcPts is valid */
    if (FRD_INVALID_PTS_64 != pstImage->SrcPts)
    {
        PTS_Info_HandleValidSrcPTS(ChanID, pstImage);
    }
    else
    {
        PTS_Info_HandleInValidSrcPTS(ChanID, pstImage);
    }

#if 0
    if (0 == (pstImage->format & 0x300))/*PROGRESSIVE*/
    {
        g_PtsChan[ChanID].s32InterPtsDelta = 0;
    }
#endif

    PTS_Info_FrameRateDetect(ChanID, pstImage);

    return VDEC_OK;
}

static VOID PTS_Info_ProcParseParam(UINT8 *pParam, UINT8 pCmd[PTS_CMD_NUM][PTS_CMD_LEN])
{
    UINT32 ParsePos = 0;
    UINT32 ParseNum = 0;
    UINT32 StrLen = 0;
    UINT8 *pCurStr = NULL;

    OSAL_FP_memset(pCmd, 0, PTS_CMD_NUM*PTS_CMD_LEN);
    do
    {
        StrLen = 0;
        pCurStr = pCmd[ParseNum];
        for (; ParsePos < OSAL_FP_strlen(pParam); ParsePos++)
        {
            if (StrLen == 0 && pParam[ParsePos] == ' ')
            {
                continue;
            }
            if (pParam[ParsePos] > ' ')
            {
                pCurStr[StrLen++] = pParam[ParsePos];
            }
            if (StrLen > 0 && pParam[ParsePos] == ' ')
            {
                break;
            }
        }
        pCurStr[StrLen] = '\0';
        ParseNum++;

    }while (ParseNum < PTS_CMD_NUM);

    return;
}

static VOID PTS_Info_ProcCommandHanlder(UINT8 pCmd[PTS_CMD_NUM][PTS_CMD_LEN])
{
    UINT32 Value = 0;
    UINT32 CmdNum = 0;

    //Parse command
    if (!OSAL_FP_strncmp(pCmd[CmdNum], PTS_CMD_SET_SAMPLE_NUM, PTS_CMD_LEN))
    {
        if (string_to_value(pCmd[CmdNum+1], &Value) != 0)
        {
            dprint(PRN_ALWS, "error string_to_value '%s'!\n", pCmd[CmdNum+1]);
            return;
        }
        g_CfgSampleNum = Value;
        dprint(PRN_ALWS, "Set CfgSampleNum %d\n", g_CfgSampleNum);
    }
    else
    {
        dprint(PRN_ALWS, "Unsupport command '%s'!\n", pCmd[CmdNum]);
    }

    return;
}

static inline UINT8* PTS_Info_ShowFrmRateType(PTS_FRMRATE_TYPE_E enType)
{
    switch (enType)
    {
       case PTS_FRMRATE_TYPE_PTS:
            return "PTS";
            break;

       case PTS_FRMRATE_TYPE_STREAM:
            return "STREAM";
            break;

       case PTS_FRMRATE_TYPE_USER:
            return "USER";
            break;

       case PTS_FRMRATE_TYPE_USER_PTS:
            return "USER_PTS";
            break;

       default:
            return "Unkown";
            break;
    }
}


SINT32 PTS_Info_Read_Proc(struct seq_file *p, VOID *v)
{
    SINT32 ChanID = g_CurProcChan;
    FRD_ALG_INFO_S *pPtsInfo = HI_NULL;

    PROC_PRINT(p, "--------------------------- PTS INFO --------------------------\n\n");

    PROC_PRINT(p, "  CfgSampleNum       : %d\n\n", g_CfgSampleNum);

    if (g_PtsChan[ChanID].bInited == VDEC_TRUE)
    {
        pPtsInfo = &(g_PtsChan[ChanID].stPtsInfo);

        PROC_PRINT(p, "  Pts Chan           : %d\n",    ChanID);
        PROC_PRINT(p, "  bInited            : %d\n",    g_PtsChan[ChanID].bInited);
        PROC_PRINT(p, "  Frame Rate Type    : %s\n",    PTS_Info_ShowFrmRateType(g_PtsChan[ChanID].stUserFrameRate.enFrmRateType));
        PROC_PRINT(p, "  Fps Integer        : %d\n",    g_PtsChan[ChanID].stUserFrameRate.stSetFrmRate.FpsInteger);
        PROC_PRINT(p, "  Fps Decimal        : %d\n",    g_PtsChan[ChanID].stUserFrameRate.stSetFrmRate.FpsDecimal);
        PROC_PRINT(p, "  Set Frame Time     : %lld\n",  g_PtsChan[ChanID].u64SetFrameTime);
        PROC_PRINT(p, "  Pts Unit(ms/us)    : %s\n",    (pPtsInfo->PtsUnit==1)? "ms": "us");
        PROC_PRINT(p, "  Sample FRD En      : %d\n",    pPtsInfo->SampleFRDEnable);

        if (pPtsInfo->SampleFRDEnable == VDEC_TRUE)
        {
            PROC_PRINT(p, "  Max Rate           : %d.%d\n", pPtsInfo->SampleMaxRate / 10, pPtsInfo->SampleMaxRate % 10);
            PROC_PRINT(p, "  Min Rate           : %d.%d\n", pPtsInfo->SampleMinRate / 10, pPtsInfo->SampleMinRate % 10);
            PROC_PRINT(p, "  Avg Rate           : %d.%d\n", pPtsInfo->SampleAvgRate / 10, pPtsInfo->SampleAvgRate % 10);
            PROC_PRINT(p, "  Sample Num/Max     : %d/%d\n", pPtsInfo->SampleActNum, pPtsInfo->SampleMaxNum);
            PROC_PRINT(p, "  Last Frame Rate    : %d.%d\n", pPtsInfo->SampleLastFrameRate / 1000, pPtsInfo->SampleLastFrameRate % 1000);
        }
        PROC_PRINT(p, "\n");
        PROC_PRINT(p, "  Total  Frame Num   : %d\n",    g_PtsChan[ChanID].u32FrameNum);
        PROC_PRINT(p, "  Output Frame Rate  : %d.%d fps\n", pPtsInfo->SampleLastFrameRate / 1000, pPtsInfo->SampleLastFrameRate % 1000);
        PROC_PRINT(p, "\n");
    }

    PROC_PRINT(p, "---------------------------------------------------------------\n");

    return VDEC_OK;
}

SINT32 PTS_Info_Write_Proc(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
    UINT8 Param[PTS_CMD_LEN];
    UINT8 CmdStr[PTS_CMD_NUM][PTS_CMD_LEN];

    if (count < 1 || count >= sizeof(Param))
    {
        dprint(PRN_ALWS, "parameter string invalid!\n");

        return VDEC_ERR;
    }

    if (copy_from_user(Param, buffer, count))
    {
        dprint(PRN_ALWS, "copy_from_user failed!\n");

        return VDEC_ERR;
    }
    Param[count] = '\0';

    PTS_Info_ProcParseParam(Param, CmdStr);

    PTS_Info_ProcCommandHanlder(CmdStr);

    return count;
}


/*----------------------------EXTERNAL FUNCTION-------------------------------*/
SINT32 PTS_Info_Init(VOID)
{
    SINT32 Ret;
    SINT32 i;

    Ret = OSAL_FP_proc_create(PTS_PROC_NAME, PTS_Info_Read_Proc, PTS_Info_Write_Proc);
    if (Ret != VDEC_OK)
    {
        dprint(PRN_ALWS, "%s create proc %s failed!\n", __func__, PTS_PROC_NAME);

        return VDEC_ERR;
    }

    OSAL_FP_memset(&g_PtsChan, 0, MAX_CHAN_NUM * sizeof(PTS_CHAN_INFO_S));

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        PTS_Info_InitParam(i);
        FRD_Reset(&g_PtsChan[i].stPtsInfo, 0);
        OSAL_FP_memset(&g_PtsChan[i].stUserFrameRate, 0, sizeof(PTS_FRMRATE_S));
        g_PtsChan[i].u64SetFrameTime = PTS_INVALID_TIME_64;
        g_PtsChan[i].stPtsInfo.CalPts = FRD_INVALID_PTS_64;
        g_PtsChan[i].stPtsInfo.QueCnt = 0;
        g_PtsChan[i].stPtsInfo.QueStable = 0;
    }

    return VDEC_OK;
}

SINT32 PTS_Info_Exit(VOID)
{
    OSAL_FP_proc_destroy(PTS_PROC_NAME);

    return VDEC_OK;
}

SINT32 PTS_Info_Alloc(SINT32 ChanID)
{
    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    if (g_PtsChan[ChanID].bInited == VDEC_TRUE)
    {
        dprint(PRN_ERROR, "%s chan %d already inited.\n", __func__, ChanID);
        return VDEC_ERR;
    }

    PTS_Info_InitParam(ChanID);
    FRD_Reset(&g_PtsChan[ChanID].stPtsInfo, 0);
    OSAL_FP_memset(&g_PtsChan[ChanID].stUserFrameRate, 0, sizeof(PTS_FRMRATE_S));
    g_PtsChan[ChanID].u64SetFrameTime = PTS_INVALID_TIME_64;
    g_PtsChan[ChanID].bInited = VDEC_TRUE;

    return VDEC_OK;
}

SINT32 PTS_Info_Free(SINT32 ChanID)
{
    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    g_PtsChan[ChanID].bInited = VDEC_FALSE;

    return VDEC_OK;
}

SINT32 PTS_Info_Reset(SINT32 ChanID)
{
    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    if (g_PtsChan[ChanID].bInited == VDEC_FALSE)
    {
        dprint(PRN_ERROR, "%s chan %d is not inited.\n", __func__, ChanID);
        return VDEC_ERR;
    }

    PTS_Info_InitParam(ChanID);
    FRD_Reset(&g_PtsChan[ChanID].stPtsInfo, 0);

    return VDEC_OK;
}

SINT32 PTS_Info_SetFrmRate(SINT32 ChanID, PTS_FRMRATE_S *pstFrmRate)
{
    UINT32 u32DivNum;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    dprint(PRN_PTS, "%s: Chan %d enFrmRateType %d, FpsInteger %d, FpsDecimal %d.\n", __func__,
        ChanID, pstFrmRate->enFrmRateType, pstFrmRate->stSetFrmRate.FpsInteger, pstFrmRate->stSetFrmRate.FpsDecimal);

    if (g_PtsChan[ChanID].bInited == VDEC_FALSE)
    {
        dprint(PRN_ERROR, "%s chan %d is not inited.\n", __func__, ChanID);
        return VDEC_ERR;
    }

    if (pstFrmRate->enFrmRateType == PTS_FRMRATE_TYPE_USER || pstFrmRate->enFrmRateType == PTS_FRMRATE_TYPE_USER_PTS)
    {
        u32DivNum = pstFrmRate->stSetFrmRate.FpsInteger * 1000 + pstFrmRate->stSetFrmRate.FpsDecimal;

        if((u32DivNum > PTS_MAX_FRAME_RATE * 1000) || (0 == u32DivNum))
        {
            dprint(PRN_ERROR, "invalid frame rate, Integer(%d), Decimal(%d) \n", pstFrmRate->stSetFrmRate.FpsInteger, pstFrmRate->stSetFrmRate.FpsDecimal);
            return VDEC_ERR;
        }

        /* 保留小数点后三位 */
        g_PtsChan[ChanID].u64SetFrameTime = 1000000000 / u32DivNum;
    }
    else
    {
        g_PtsChan[ChanID].u64SetFrameTime = -1;
    }

    OSAL_FP_memcpy(&g_PtsChan[ChanID].stUserFrameRate, pstFrmRate, sizeof(PTS_FRMRATE_S));

    return VDEC_OK;
}

SINT32 PTS_Info_GetFrmRate(SINT32 ChanID, PTS_FRMRATE_S *pstFrmRate)
{
    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    if (g_PtsChan[ChanID].bInited == VDEC_FALSE)
    {
        dprint(PRN_ERROR, "%s chan %d is not inited.\n", __func__, ChanID);
        return VDEC_ERR;
    }

    if (g_PtsChan[ChanID].u64SetFrameTime != PTS_INVALID_TIME_64)
    {
        OSAL_FP_memcpy(pstFrmRate, &g_PtsChan[ChanID].stUserFrameRate, sizeof(PTS_FRMRATE_S));
    }
    else
    {
        dprint(PRN_PTS, "%s not set frame rate yet!\n");
        OSAL_FP_memset(pstFrmRate, 0, sizeof(PTS_FRMRATE_S));
    }

    return VDEC_OK;
}

SINT32 PTS_Info_Convert(SINT32 ChanID, IMAGE *pstImage)
{
    UINT64 InPts;
    UINT32 InFrameRate;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);
    VFMW_ASSERT_RETURN(pstImage != NULL, VDEC_ERR);

    if (g_PtsChan[ChanID].bInited == VDEC_FALSE)
    {
        dprint(PRN_ERROR, "%s chan %d is not inited.\n", __func__, ChanID);
        return VDEC_ERR;
    }

    InPts = pstImage->PTS;
    InFrameRate = pstImage->frame_rate;

    PTS_Info_CalcStamp(ChanID, pstImage);

    dprint(PRN_PTS, "PTSInfo: Width %d, Height %d, PtsUnit %d, PtsInfo{SrcPTS, InPts, OutPts, InFrmRate, OutFrmRate, PtsDelta} = {%lld, %lld, %lld, %d, %d, %d},\n",
           pstImage->image_width, pstImage->image_height, pstImage->format.pts_unit,
           pstImage->SrcPts, InPts, pstImage->PTS, InFrameRate, pstImage->frame_rate, pstImage->InterPtsDelta);

    return VDEC_OK;
}

SINT32 PTS_Info_EnableSampleFRD(SINT32 ChanID)
{
    FRD_ALG_INFO_S *pPtsInfo = HI_NULL;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    pPtsInfo = &(g_PtsChan[ChanID].stPtsInfo);

    /* Use config sample num in prority */
    g_CurSampleNum = g_CfgSampleNum;
    pPtsInfo->SampleMaxNum = g_CfgSampleNum;
    pPtsInfo->SampleFRDEnable = VDEC_TRUE;

    return VDEC_OK;
}

SINT32 PTS_Info_DisableSampleFRD(SINT32 ChanID)
{
    FRD_ALG_INFO_S *pPtsInfo = HI_NULL;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

    pPtsInfo = &(g_PtsChan[ChanID].stPtsInfo);

    g_CurSampleNum = 0;
    pPtsInfo->SampleMaxNum = 0;
    pPtsInfo->SampleFRDEnable = VDEC_FALSE;

    return VDEC_OK;
}

#ifdef VCODEC_UT_ENABLE
EXPORT_SYMBOL(PTS_Info_Init);
EXPORT_SYMBOL(PTS_Info_Exit);
EXPORT_SYMBOL(PTS_Info_Alloc);
EXPORT_SYMBOL(PTS_Info_Free);
EXPORT_SYMBOL(PTS_Info_Reset);
EXPORT_SYMBOL(PTS_Info_SetFrmRate);
EXPORT_SYMBOL(PTS_Info_GetFrmRate);
EXPORT_SYMBOL(PTS_Info_Convert);
EXPORT_SYMBOL(PTS_Info_EnableSampleFRD);
EXPORT_SYMBOL(PTS_Info_DisableSampleFRD);
#endif
