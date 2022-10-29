/****************************************************************************
*
* Copyright (C) 2014-2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_fmd.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/2/18
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_FMD_H__
#define __PQ_HAL_FMD_H__

#include <linux/string.h>   /* memcpy() */
#include "hi_type.h"
#include "pq_hal_comm.h"
#include "pq_mng_ifmd_alg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    HI_S32 IsProgressiveSeq;
    HI_S32 IsProgressiveFrm;
    HI_S32 RealFrmRate;

} VDEC_TRAN_INFO_S;

/*IFMD���㷨�����������������VPSS->PQ*/
typedef struct hi_PQ_REG_IFMD_CALC_S
{
    HI_U32  u32HandleNo;
    HI_U32  u32WidthY;
    HI_U32  u32HeightY;
    HI_S32  s32FieldOrder;                 /* ���׳��� �������ȵ׳����� */
    HI_S32  s32FieldMode;                  /* ���׳���־ */
    HI_U32  u32FrameRate;
    HI_BOOL bPreInfo;                      /* DEI�߼�����timeout���Ծɴ�����һ�� */
    VDEC_TRAN_INFO_S  stVdecInfo;
    S_VPSSWB_REGS_TYPE* pstIfmdHardOutReg; /* ��ȡifmd��״̬�Ĵ��� */

} PQ_IFMD_CALC_S;

typedef struct
{
    HI_S32 die_reset;
    HI_S32 die_stop;
    HI_S32 dir_mch;
    HI_S32 die_out_sel;
    HI_S32 jud_en;
    //HI_S32  ChromaVertFltEn;
    HI_S32 s32FieldOrder;      /* ���׳��� */
    HI_S32 s32SceneChanged;    /* �����л���Ϣ */
    HI_S32 s32FilmType;        /* ��Ӱģʽ */
    HI_U32 u32KeyValue;        /* ����ؼ�֡��Ϣ*/
    HI_U32 u32EdgeSmoothEn;

} REG_PLAYBACK_CONFIG_S;

typedef struct
{
    ALG_FMD_RTL_STATPARA_S stFmdRtlStatPara; /* ��Ҫ���߼�����ͳ����Ϣ */
    ALG_MAD_RTL_STATPARA_S stMadRtlStatPara; /* ��Ҫ���߼�����ͳ����Ϣ */
} IFMD_TotalHardPara;

HI_S32 PQ_HAL_GetIFmdStatInfo(PQ_IFMD_CALC_S* pstIfmdCalcInfo, IFMD_TotalHardPara* pIfmdTotalHardPara);
HI_S32 PQ_HAL_SetIFmdInfo(HI_U32 u32HandleNo, REG_PLAYBACK_CONFIG_S* NewCfg);
HI_S32 PQ_HAL_SetIFmdEn(HI_U32 u32HandleNo, HI_U32 u32IFmdEn);
HI_S32 PQ_HAL_SetEdgeSmoothEn(HI_U32 u32HandleNo, HI_BOOL bEdgeSmoothEn);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

