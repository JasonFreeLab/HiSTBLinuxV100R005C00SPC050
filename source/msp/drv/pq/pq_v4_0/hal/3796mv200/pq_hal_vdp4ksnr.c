/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

 File Name    : pq_hal_vdp4ksnr.c
 Version        : Initial Draft
 Author         : sdk
 Created       : 2017/04/14
 Description   :

******************************************************************************/
#include "hi_type.h"
#include "hi_drv_mem.h"
#include "drv_pq_table.h"
#include "pq_hal_comm.h"
#include "pq_hal_vdp4ksnr.h"

/*SNR*/

static HI_U8 au8Vdp4KSnrMotionEdgeLUT[32] =
{
    31, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
    16, 15, 14, 14, 13, 12, 11, 10, 10,  9,  8,  7,  6,  5,  4,  3
};

HI_S32  PQ_HAL_SetVdp4KSnrParaUpd (HI_U32 u32Data)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_PARAUP V0_PARAUP;

    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_PARAUP.u32)) + u32Data * PQ_VID_OFFSET));
    V0_PARAUP.bits.snr_upd = 0x1;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_PARAUP.u32)) + u32Data * PQ_VID_OFFSET), V0_PARAUP.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVdp4KSnrCfgAddr(HI_U32 u32Data, HI_U32 u32Addr)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_SNR_CFGAD         V0_SNR_CFGAD;
    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_SNR_CFGAD.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_CFGAD.u32) ) + u32Data * PQ_VID_OFFSET));
    V0_SNR_CFGAD.bits.coef_addr = u32Addr;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_CFGAD.u32) ) + u32Data * PQ_VID_OFFSET), V0_SNR_CFGAD.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVdp4KSnrMotionEdgeLut (HI_U32 u32Data, HI_U32 u32Width)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_MOTION_EDGE_LUT_01a V0_MOTION_EDGE_LUT_01a;
    U_V0_MOTION_EDGE_LUT_01b V0_MOTION_EDGE_LUT_01b;
    U_V0_MOTION_EDGE_LUT_01c V0_MOTION_EDGE_LUT_01c;
    U_V0_MOTION_EDGE_LUT_01d V0_MOTION_EDGE_LUT_01d;
    U_V0_MOTION_EDGE_LUT_01e V0_MOTION_EDGE_LUT_01e;
    U_V0_MOTION_EDGE_LUT_01f V0_MOTION_EDGE_LUT_01f;
    U_V0_MOTION_EDGE_LUT_01g V0_MOTION_EDGE_LUT_01g;
    U_V0_MOTION_EDGE_LUT_01h V0_MOTION_EDGE_LUT_01h;

    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();

    V0_MOTION_EDGE_LUT_01h.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01h.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01g.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01g.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01f.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01f.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01e.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01e.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01d.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01d.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01c.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01c.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01b.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01b.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01a.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01a.u32)) + u32Data * PQ_VID_OFFSET));
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__0_  = au8Vdp4KSnrMotionEdgeLUT[0];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__1_  = au8Vdp4KSnrMotionEdgeLUT[1];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__2_  = au8Vdp4KSnrMotionEdgeLUT[2];
    V0_MOTION_EDGE_LUT_01a.bits.snrmotionedgelut_0__3_  = au8Vdp4KSnrMotionEdgeLUT[3];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__4_  = au8Vdp4KSnrMotionEdgeLUT[4];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__5_  = au8Vdp4KSnrMotionEdgeLUT[5];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__6_  = au8Vdp4KSnrMotionEdgeLUT[6];
    V0_MOTION_EDGE_LUT_01b.bits.snrmotionedgelut_0__7_  = au8Vdp4KSnrMotionEdgeLUT[7];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__8_  = au8Vdp4KSnrMotionEdgeLUT[8];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__9_  = au8Vdp4KSnrMotionEdgeLUT[9];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__10_ = au8Vdp4KSnrMotionEdgeLUT[10];
    V0_MOTION_EDGE_LUT_01c.bits.snrmotionedgelut_0__11_ = au8Vdp4KSnrMotionEdgeLUT[11];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__12_ = au8Vdp4KSnrMotionEdgeLUT[12];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__13_ = au8Vdp4KSnrMotionEdgeLUT[13];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__14_ = au8Vdp4KSnrMotionEdgeLUT[14];
    V0_MOTION_EDGE_LUT_01d.bits.snrmotionedgelut_0__15_ = au8Vdp4KSnrMotionEdgeLUT[15];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__16_ = au8Vdp4KSnrMotionEdgeLUT[16];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__17_ = au8Vdp4KSnrMotionEdgeLUT[17];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__18_ = au8Vdp4KSnrMotionEdgeLUT[18];
    V0_MOTION_EDGE_LUT_01e.bits.snrmotionedgelut_0__19_ = au8Vdp4KSnrMotionEdgeLUT[19];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__20_ = au8Vdp4KSnrMotionEdgeLUT[20];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__21_ = au8Vdp4KSnrMotionEdgeLUT[21];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__22_ = au8Vdp4KSnrMotionEdgeLUT[22];
    V0_MOTION_EDGE_LUT_01f.bits.snrmotionedgelut_0__23_ = au8Vdp4KSnrMotionEdgeLUT[23];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__24_ = au8Vdp4KSnrMotionEdgeLUT[24];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__25_ = au8Vdp4KSnrMotionEdgeLUT[25];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__26_ = au8Vdp4KSnrMotionEdgeLUT[26];
    V0_MOTION_EDGE_LUT_01g.bits.snrmotionedgelut_0__27_ = au8Vdp4KSnrMotionEdgeLUT[27];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__28_ = au8Vdp4KSnrMotionEdgeLUT[28];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__29_ = au8Vdp4KSnrMotionEdgeLUT[29];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__30_ = au8Vdp4KSnrMotionEdgeLUT[30];
    V0_MOTION_EDGE_LUT_01h.bits.snrmotionedgelut_0__31_ = au8Vdp4KSnrMotionEdgeLUT[31];
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01h.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01h.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01g.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01g.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01f.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01f.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01e.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01e.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01d.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01d.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01c.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01c.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01b.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01b.u32);
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_MOTION_EDGE_LUT_01a.u32)) + u32Data * PQ_VID_OFFSET), V0_MOTION_EDGE_LUT_01a.u32);

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetVdp4KSnrEnable(HI_U32 u32Data, HI_BOOL bEnable)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_PRERD V0_PRERD;
    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_PRERD.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_PRERD.u32) ) + u32Data * PQ_VID_OFFSET));
    V0_PRERD.bits.snr_en = bEnable;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_PRERD.u32) ) + u32Data * PQ_VID_OFFSET), V0_PRERD.u32);

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetVdp4KSnrstrength(HI_U32 u32Data, HI_U32 snrstrength)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_SNR_ENABLE V0_SNR_ENABLE;

    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_SNR_ENABLE.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET));
    V0_SNR_ENABLE.bits.snrstrength = snrstrength;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET), V0_SNR_ENABLE.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVdp4KSnrDemomodelr(HI_U32 u32Data, HI_U32 demomodelr)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_SNR_ENABLE V0_SNR_ENABLE;

    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_SNR_ENABLE.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET));
    V0_SNR_ENABLE.bits.demomodelr = demomodelr;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET), V0_SNR_ENABLE.u32);

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetVdp4KSnrDemomodeen(HI_U32 u32Data, HI_BOOL bDemoEn)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_V0_SNR_ENABLE V0_SNR_ENABLE;

    if (u32Data >= VID_MAX)
    {
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    V0_SNR_ENABLE.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET));
    V0_SNR_ENABLE.bits.demomodeen = bDemoEn;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVDPReg->V0_SNR_ENABLE.u32) ) + u32Data * PQ_VID_OFFSET), V0_SNR_ENABLE.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVdp4KSnrDemoModeCoor(HI_U32 u32Data, HI_U32 u32XPos)
{
    HI_UNUSED(u32Data);
    HI_UNUSED(u32XPos);
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetVdp4KSnrMeanRatio(HI_U32 u32Data, PQ_HAL_VDP4KSNR_MEAN_RATIO_S *pstMeanRatio)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    PQ_CHECK_NULL_PTR(pstMeanRatio);

    HI_UNUSED(u32Data);
    pstVDPReg = PQ_HAL_GetVdpReg();

    pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox0 = pstMeanRatio->s32MappingX[0];
    pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox1 = pstMeanRatio->s32MappingX[1];
    pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox2 = pstMeanRatio->s32MappingX[2];
    pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox3 = pstMeanRatio->s32MappingX[3];
    pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox4 = pstMeanRatio->s32MappingX[4];
    pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox5 = pstMeanRatio->s32MappingX[5];

    pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy0 = pstMeanRatio->s32MappingY[0];
    pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy1 = pstMeanRatio->s32MappingY[1];
    pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy2 = pstMeanRatio->s32MappingY[2];
    pstVDPReg->V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy3 = pstMeanRatio->s32MappingY[3];
    pstVDPReg->V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy4 = pstMeanRatio->s32MappingY[4];

    pstVDPReg->V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok0 = pstMeanRatio->s32MappingK[0];
    pstVDPReg->V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok1 = pstMeanRatio->s32MappingK[1];
    pstVDPReg->V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok2 = pstMeanRatio->s32MappingK[2];
    pstVDPReg->V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok3 = pstMeanRatio->s32MappingK[3];

    pstVDPReg->V0_SNR_EDGE_RATIO.bits.meanedgeratiomax  = pstMeanRatio->s32MappingMax;
    pstVDPReg->V0_SNR_EDGE_RATIO.bits.meanedgeratiomin  = pstMeanRatio->s32MappingMin;

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_GetVdp4KSnrMeanRatio(HI_U32 u32Data, PQ_HAL_VDP4KSNR_MEAN_RATIO_S *pstMeanRatio)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    PQ_CHECK_NULL_PTR(pstMeanRatio);
    HI_UNUSED(u32Data);

    pstVDPReg = PQ_HAL_GetVdpReg();
    pstMeanRatio->s32MappingX[0] = pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox0;
    pstMeanRatio->s32MappingX[1] = pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox1;
    pstMeanRatio->s32MappingX[2] = pstVDPReg->V0_SNR_EDGE_RATIOX0.bits.meanedgeratiox2;
    pstMeanRatio->s32MappingX[3] = pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox3;
    pstMeanRatio->s32MappingX[4] = pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox4;
    pstMeanRatio->s32MappingX[5] = pstVDPReg->V0_SNR_EDGE_RATIOX1.bits.meanedgeratiox5;

    pstMeanRatio->s32MappingY[0] = pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy0;
    pstMeanRatio->s32MappingY[1] = pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy1;
    pstMeanRatio->s32MappingY[2] = pstVDPReg->V0_SNR_EDGE_RATIOY0.bits.meanedgeratioy2;
    pstMeanRatio->s32MappingY[3] = pstVDPReg->V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy3;
    pstMeanRatio->s32MappingY[4] = pstVDPReg->V0_SNR_EDGE_RATIOY1.bits.meanedgeratioy4;

    pstMeanRatio->s32MappingK[0] = pstVDPReg->V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok0;
    pstMeanRatio->s32MappingK[1] = pstVDPReg->V0_SNR_EDGE_RATIOK0.bits.meanedgeratiok1;
    pstMeanRatio->s32MappingK[2] = pstVDPReg->V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok2;
    pstMeanRatio->s32MappingK[3] = pstVDPReg->V0_SNR_EDGE_RATIOK1.bits.meanedgeratiok3;

    pstMeanRatio->s32MappingMax  = pstVDPReg->V0_SNR_EDGE_RATIO.bits.meanedgeratiomax;
    pstMeanRatio->s32MappingMin  = pstVDPReg->V0_SNR_EDGE_RATIO.bits.meanedgeratiomin;

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetVdp4KSnrEdgeStr(HI_U32 u32Data, PQ_HAL_VDP4KSNR_EDGE_STR_S *pstEdgeStr)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    PQ_CHECK_NULL_PTR(pstEdgeStr);
    HI_UNUSED(u32Data);

    pstVDPReg = PQ_HAL_GetVdpReg();
    pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx0 = pstEdgeStr->s32MappingX[0];
    pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx1 = pstEdgeStr->s32MappingX[1];
    pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx2 = pstEdgeStr->s32MappingX[2];
    pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx3 = pstEdgeStr->s32MappingX[3];
    pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx4 = pstEdgeStr->s32MappingX[4];
    pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx5 = pstEdgeStr->s32MappingX[5];
    pstVDPReg->V0_SNR_EDGE_STRX2.bits.edgestrmappingx6 = pstEdgeStr->s32MappingX[6];
    pstVDPReg->V0_SNR_EDGE_STRX2.bits.edgestrmappingx7 = pstEdgeStr->s32MappingX[7];

    pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy0 = pstEdgeStr->s32MappingY[0];
    pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy1 = pstEdgeStr->s32MappingY[1];
    pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy2 = pstEdgeStr->s32MappingY[2];
    pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy3 = pstEdgeStr->s32MappingY[3];
    pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy4 = pstEdgeStr->s32MappingY[4];
    pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy5 = pstEdgeStr->s32MappingY[5];
    pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy6 = pstEdgeStr->s32MappingY[6];

    pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk0 = pstEdgeStr->s32MappingK[0];
    pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk1 = pstEdgeStr->s32MappingK[1];
    pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk2 = pstEdgeStr->s32MappingK[2];
    pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk3 = pstEdgeStr->s32MappingK[3];
    pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk4 = pstEdgeStr->s32MappingK[4];
    pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk5 = pstEdgeStr->s32MappingK[5];

    pstVDPReg->V0_SNR_EDGE_STR.bits.edgestrmappingmax  = pstEdgeStr->s32MappingMax;
    pstVDPReg->V0_SNR_EDGE_STR.bits.edgestrmappingmin  = pstEdgeStr->s32MappingMin;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetVdp4KSnrEdgeStr(HI_U32 u32Data, PQ_HAL_VDP4KSNR_EDGE_STR_S *pstEdgeStr)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    PQ_CHECK_NULL_PTR(pstEdgeStr);
    HI_UNUSED(u32Data);

    pstVDPReg = PQ_HAL_GetVdpReg();
    pstEdgeStr->s32MappingX[0] = pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx0;
    pstEdgeStr->s32MappingX[1] = pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx1;
    pstEdgeStr->s32MappingX[2] = pstVDPReg->V0_SNR_EDGE_STRX0.bits.edgestrmappingx2;
    pstEdgeStr->s32MappingX[3] = pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx3;
    pstEdgeStr->s32MappingX[4] = pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx4;
    pstEdgeStr->s32MappingX[5] = pstVDPReg->V0_SNR_EDGE_STRX1.bits.edgestrmappingx5;
    pstEdgeStr->s32MappingX[6] = pstVDPReg->V0_SNR_EDGE_STRX2.bits.edgestrmappingx6;
    pstEdgeStr->s32MappingX[7] = pstVDPReg->V0_SNR_EDGE_STRX2.bits.edgestrmappingx7;

    pstEdgeStr->s32MappingY[0] = pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy0;
    pstEdgeStr->s32MappingY[1] = pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy1;
    pstEdgeStr->s32MappingY[2] = pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy2;
    pstEdgeStr->s32MappingY[3] = pstVDPReg->V0_SNR_EDGE_STRY0.bits.edgestrmappingy3;
    pstEdgeStr->s32MappingY[4] = pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy4;
    pstEdgeStr->s32MappingY[5] = pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy5;
    pstEdgeStr->s32MappingY[6] = pstVDPReg->V0_SNR_EDGE_STRY1.bits.edgestrmappingy6;

    pstEdgeStr->s32MappingK[0] = pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk0;
    pstEdgeStr->s32MappingK[1] = pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk1;
    pstEdgeStr->s32MappingK[2] = pstVDPReg->V0_SNR_EDGE_STRK0.bits.edgestrmappingk2;
    pstEdgeStr->s32MappingK[3] = pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk3;
    pstEdgeStr->s32MappingK[4] = pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk4;
    pstEdgeStr->s32MappingK[5] = pstVDPReg->V0_SNR_EDGE_STRK1.bits.edgestrmappingk5;

    pstEdgeStr->s32MappingMax  = pstVDPReg->V0_SNR_EDGE_STR.bits.edgestrmappingmax;
    pstEdgeStr->s32MappingMin  = pstVDPReg->V0_SNR_EDGE_STR.bits.edgestrmappingmin;

    return HI_SUCCESS;
}



