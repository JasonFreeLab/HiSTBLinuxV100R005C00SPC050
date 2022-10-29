/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_zme.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
  Author        : sdk
******************************************************************************/
#include <linux/fs.h>

#include "pq_hal_zme.h"
#include "pq_mng_zme_coef.h"

static HI_BOOL g_bHalVdpZmeFirEn  = HI_TRUE;
static HI_BOOL g_bHalVdpZmeMedEn  = HI_FALSE;

#define V0_SCALER1_AMPLIFY_ENABLE_THD   2
#define V0_SCALER1_REDUCE_ENABLE_THD    4
#define V0_SCALER1_RESO_ENABLE_THD      2
#define V0_READ_FMT_ZME_THD         2
#define V0_HPZME_ENABLE_THD         3
#define V0_PREZME_ENABLE_WIDTH_2_THD   2
#define V0_PREZME_ENABLE_WIDTH_4_THD   4
#define V0_PREZME_ENABLE_WIDTH_8_THD   8
#define V0_PREZME_ENABLE_WIDTH_16_THD  16
#define V0_PREZME_ENABLE_WIDTH_32_THD  32
#define V0_PREZME_ENABLE_HEIGHT_3_THD  3
#define V0_PREZME_ENABLE_HEIGHT_4_THD  4
#define V0_PREZME_ENABLE_HEIGHT_8_THD  8
#define V0_PREZME_ENABLE_HEIGHT_16_THD 16
#define V0_PREZME_ENABLE_2_THD      6
#define V0_PREZME_ENABLE_4_THD      12
#define V0_PREZME_ENABLE_8_THD      24
#define WBC_HSCALER_THD             4
#define DHD0_OUT_RESOLUTION_W_THD   3840
#define DHD0_OUT_RESOLUTION_H_THD   2160

#define SHARPEN_SUPPOR_MAX_WITDH    1920
#define SHARPEN_SUPPOR_MAX_HEIGHT   1080

static S_VDP_REGS_TYPE *pVdpReg;

static HI_BOOL sg_bVpssZmeDefault = HI_FALSE;
static HI_BOOL sg_bVdpZmeDefault  = HI_FALSE;
static HI_BOOL sg_bV0ReadFmtIn    = HI_TRUE;
static HI_BOOL sg_bHPZmeEnable    = HI_FALSE;
static HI_BOOL sg_bProcHDCPEn     = HI_FALSE;
static PQ_HAL_PREZME_HOR_MUL_E sg_enV0PreHScaler    = PQ_HAL_PREZME_HOR_DISABLE;
static PQ_HAL_PREZME_VER_MUL_E sg_enV0PreVScaler    = PQ_HAL_PREZME_VER_DISABLE;
static PQ_HAL_FROST_LEVEL_E    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_CLOSE;
static HI_PQ_FROST_LEVEL_E     sg_enProcFrostLevel  = HI_PQ_FROST_LEVEL_CLOSE;
static ZME_WBC_POINT_SEL_E     sg_enWbcPointSel     = ZME_WBC_POINT_V0;

/****************************Load VDP ZME COEF START*****************************************/
static HI_U32 VdpZmeTransCoefAlign(const HI_S16 *ps16Coef, VZME_TAP_E enTap, ZME_COEF_BITARRAY_S *pBitCoef)
{
    HI_U32 i, u32Cnt, u32Tap, u32Tmp;

    switch (enTap)
    {
        case VZME_TAP_8T32P:
            u32Tap = 8;
            break;
        case VZME_TAP_6T32P:
            u32Tap = 6;
            break;
        case VZME_TAP_4T32P:
            u32Tap = 4;
            break;
        default:
            u32Tap = 4;
            break;
    }

    /* Tran ZME coef to 128 bits order */
    u32Cnt = 18 * u32Tap / 12;
    for (i = 0; i < u32Cnt; i++)
    {
        pBitCoef->stBit[i].bits_0 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_1 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_2 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_32 = u32Tmp;
        pBitCoef->stBit[i].bits_38 = (u32Tmp >> 2);

        pBitCoef->stBit[i].bits_4 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_5 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_64 = u32Tmp;
        pBitCoef->stBit[i].bits_66 = u32Tmp >> 4;

        pBitCoef->stBit[i].bits_7 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_8 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_96 = u32Tmp;
        pBitCoef->stBit[i].bits_94 = u32Tmp >> 6;

        pBitCoef->stBit[i].bits_10 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_11 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_12 = 0;
    }

    pBitCoef->u32Size = u32Cnt * sizeof(ZME_COEF_BIT_S);

    return HI_SUCCESS;
}

/* load hor coef */
static HI_U32 VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U8 *pu8Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    /* load horizontal zoom coef */
    VdpZmeTransCoefAlign(g_pVZmeReduceCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);

    memcpy(pu8Addr, stArray.stBit, stArray.u32Size);

    return HI_SUCCESS;
}

/* load vert coef */
static HI_S32 VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U8 *pu8Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    /* load vertical zoom coef */
    VdpZmeTransCoefAlign(g_pVZmeReduceCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);
    memcpy(pu8Addr, stArray.stBit, stArray.u32Size);

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_VdpLoadCoef(ALG_VZME_MEM_S *pstVZmeCoefMem)
{
    HI_U8 *pu8CurAddr;
    HI_U32 u32PhyAddr;
    HI_U32 u32NumSizeLuma, u32NumSizeChro;
    ALG_VZME_COEF_ADDR_S *pstAddrTmp;

    pu8CurAddr = pstVZmeCoefMem->stMBuf.pu8StartVirAddr;
    u32PhyAddr = pstVZmeCoefMem->stMBuf.u32StartPhyAddr;
    pstAddrTmp = &(pstVZmeCoefMem->stZmeCoefAddr);


    /* H_L8C4:Luma-Hor-8T32P Chroma-Hor-4T32P */
    u32NumSizeLuma = 192; /* (8x18) / 12 * 16 = 192 */
    u32NumSizeChro = 96;  /* (4x18) / 12 * 16 = 96 */
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;


    /* V_L6C4:Luma-Vert-6T32P Chroma-Vert-4T32P */
    u32NumSizeLuma = 144;  /* (6x18) / 12 * 16 = 144 */
    u32NumSizeChro = 96;   /* (4x18) / 12 * 16 = 96 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;


    /* H_L8:Luma-Hor-8T32P(logic) */
    /* H_L6:Luma-Hor-6T32P(real) */
    u32NumSizeLuma = 192; /* (8x18) / 12 * 16 = 192 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_8T32P_LH,  VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    /* V_L4:Luma-Vert-4T32P */
    u32NumSizeLuma = 96; /*(4x18) / 12 * 16 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VDP_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;

    return;
}
/*****************************Load VDP ZME COEF END*****************************************/



/*******************************WBC ZME START***************************************/
static HI_VOID PQ_HAL_WBC_SetZmePhaseH(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC)
{
    U_WBC_DHD0_ZME_HLOFFSET WBC_DHD0_ZME_HLOFFSET;
    U_WBC_DHD0_ZME_HCOFFSET WBC_DHD0_ZME_HCOFFSET;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 )
    {
        /* VHD layer zoom enable */
        WBC_DHD0_ZME_HLOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32)));
        WBC_DHD0_ZME_HLOFFSET.bits.hor_loffset = s32PhaseL;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32))), WBC_DHD0_ZME_HLOFFSET.u32);

        WBC_DHD0_ZME_HCOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32)));
        WBC_DHD0_ZME_HCOFFSET.bits.hor_coffset = s32PhaseC;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32))), WBC_DHD0_ZME_HCOFFSET.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmePhaseV(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC)
{
    U_WBC_DHD0_ZME_VOFFSET WBC_DHD0_ZME_VOFFSET;
    pVdpReg = PQ_HAL_GetVdpReg();

    if (enLayer == VDP_LAYER_WBC_HD0 )
    {
        /* VHD layer zoom enable */
        WBC_DHD0_ZME_VOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_VOFFSET.u32)));
        WBC_DHD0_ZME_VOFFSET.bits.vluma_offset = s32PhaseL;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32))), WBC_DHD0_ZME_VOFFSET.u32);

        WBC_DHD0_ZME_VOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_VOFFSET.u32)));
        WBC_DHD0_ZME_VOFFSET.bits.vchroma_offset = s32PhaseC;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32))), WBC_DHD0_ZME_VOFFSET.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeHorRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hratio = u32Ratio;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeVerRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_VSR WBC_DHD0_ZME_VSR;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSR.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSR.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_VSR.bits.vratio = u32Ratio;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSR.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSR.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32firMode)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    pVdpReg = PQ_HAL_GetVdpReg();
    /* WBC zoom enable */
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hlfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hchfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vlfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vchfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 bEnable)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeVerTap(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32VerTap)
{
    /* vsc_luma_tap does not exist in 3798m_a and 3798m */
    /* vsc_chroma_tap does not exist in 3798m_a and 3798m */
    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr, HI_U32 u32CAddr)
{
    pVdpReg = PQ_HAL_GetVdpReg();

    if ( enLayer == VDP_LAYER_WBC_HD0 ||  enLayer == VDP_LAYER_WBC_ME  )
    {
        if (u32Mode == VDP_WBC_PARA_ZME_HOR)
        {
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_HLCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32Addr);
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_HCCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32CAddr);
        }
        else if (u32Mode == VDP_WBC_PARA_ZME_VER)
        {
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_VLCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32Addr);
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_VCCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32CAddr);
        }
        else
        {
            HI_ERR_PQ("Error,PQ_HAL_WBC_SetZmeCoefAddr() Select a Wrong Mode!\n");
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetParaUpd (VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E enMode)
{
    U_WBC_DHD0_PARAUP WBC_DHD0_PARAUP;
    /* WBC_ME exist in 98cv100, using for MEMC, does not exist in 98mv100_a and 98m */

    pVdpReg = PQ_HAL_GetVdpReg();

    if ( enLayer == VDP_LAYER_WBC_HD0 )
    {
        WBC_DHD0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_PARAUP.u32))));
        if (enMode == VDP_WBC_PARA_ZME_HOR)
        {
            WBC_DHD0_PARAUP.bits.wbc_hlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_hccoef_upd = 0x1;
        }
        else if (enMode == VDP_WBC_PARA_ZME_VER)
        {
            WBC_DHD0_PARAUP.bits.wbc_vlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_vccoef_upd = 0x1;
        }
        else
        {
            HI_ERR_PQ("error,VDP_WBC_DHD0_SetParaUpd() select wrong mode!\n");
        }
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_PARAUP.u32))), WBC_DHD0_PARAUP.u32);
    }
    else
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeInFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
    pVdpReg = PQ_HAL_GetVdpReg();

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_in_fmt = u32Fmt;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }
    else
    {}

    return;
}

/* Vdp WBC Cfg Set to reg*/
/* explanation: In WBC We just pay atention to WBC_HD0 */
HI_VOID PQ_HAL_WbcZmeRegCfg(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S *pstZmeRtlPara, HI_BOOL bFirEnable)
{
    if (u32LayerId >= VDP_ZME_LAYER_WBC0)
    {
        u32LayerId = u32LayerId - VDP_ZME_LAYER_WBC0;
    }

    PQ_HAL_WBC_SetZmeHorRatio(u32LayerId, pstZmeRtlPara->u32ZmeRatioHL);
    PQ_HAL_WBC_SetZmeVerRatio(u32LayerId, pstZmeRtlPara->u32ZmeRatioVL);

    PQ_HAL_WBC_SetZmePhaseH(u32LayerId, pstZmeRtlPara->s32ZmeOffsetHL, pstZmeRtlPara->s32ZmeOffsetHC);
    PQ_HAL_WBC_SetZmePhaseV(u32LayerId, pstZmeRtlPara->s32ZmeOffsetVL, pstZmeRtlPara->s32ZmeOffsetVC);


    /* zme enable and fir enable should not fix to a value. */
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HORL, pstZmeRtlPara->bZmeEnHL, pstZmeRtlPara->bZmeMdHL);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HORC, pstZmeRtlPara->bZmeEnHC, pstZmeRtlPara->bZmeMdHC);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VERL, pstZmeRtlPara->bZmeEnVL, pstZmeRtlPara->bZmeMdVL);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeEnVC, pstZmeRtlPara->bZmeMdVC);

    /* set media fir. */
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_HORL, pstZmeRtlPara->bZmeMedHL);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_HORC, pstZmeRtlPara->bZmeMedHC);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERL, pstZmeRtlPara->bZmeMedVL);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeMedVC);

    /* set zme order, h first or v first */
    PQ_HAL_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_HD0, pstZmeRtlPara->bZmeOrder);

    /* It does not exist in 98m_a and 98m */
    /* set v chroma zme tap */
    PQ_HAL_WBC_SetZmeVerTap(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeTapVC);

    /* set hor fir coef addr, and set updata flag */
    if (pstZmeRtlPara->u32ZmeRatioHL)
    {
        PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_HOR, pstZmeRtlPara->u32ZmeCoefAddrHL, pstZmeRtlPara->u32ZmeCoefAddrHC);
        PQ_HAL_WBC_SetParaUpd(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_HOR);
    }

    /* set ver fir coef addr, and set updata flag */
    if (pstZmeRtlPara->u32ZmeRatioVL)
    {
        PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_VER, pstZmeRtlPara->u32ZmeCoefAddrVL, pstZmeRtlPara->u32ZmeCoefAddrVC);
        PQ_HAL_WBC_SetParaUpd(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_VER);
    }

    PQ_HAL_WBC_SetZmeInFmt(VDP_LAYER_WBC_HD0, VDP_PROC_FMT_SP_422);

    return;
}

/*******************************WBC ZME END***************************************/


/*******************************Load VPSS ZME COEF START***********************************/
static HI_U32 VpssZmeTransCoefAlign(const HI_S16 *ps16Coef, VZME_TAP_E enTap, ZME_COEF_BITARRAY_S *pBitCoef)
{
    HI_U32 i, j, u32Tap, k;
    HI_S32 s32CoefTmp1, s32CoefTmp2, s32CoefTmp3;

    switch (enTap)
    {
        case VZME_TAP_8T32P:
            u32Tap = 8;
            break;
        case VZME_TAP_6T32P:
            u32Tap = 6;
            break;
        case VZME_TAP_4T32P:
            u32Tap = 4;
            break;
        default:
            u32Tap = 4;
            break;
    }

    j = 0;
    /* when tap == 8, there are 8 number in one group */
    if (u32Tap == 8)
    {
        /* 4 Bytes��32bits is the unit��every filter number is 10bits,
           There are 8 numbers in one group�� take place at one group include 3*4 Bytes,
           Array s32CoefAttr[51] add 1��The last 4 Bytes  only contain two numbers
           */
        for (i = 0; i < 17; i++)
        {
            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            s32CoefTmp3 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00) + (s32CoefTmp3 << 20);

            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            s32CoefTmp3 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00) + (s32CoefTmp3 << 20);

            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00);
        }

        pBitCoef->u32Size = 17 * 3 * 4; /* size unit is Byte */
    }
    else
    {
        for (i = 0; i < 17; i++)
        {
            for (k = 1; k <= (u32Tap / 2); k++)
            {
                s32CoefTmp1 = (HI_S32) * ps16Coef++;
                s32CoefTmp2 = (HI_S32) * ps16Coef++;
                pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0xffff) + (s32CoefTmp2 << 16);
            }
        }
        pBitCoef->u32Size = 17 * (u32Tap / 2) * 4;
    }

    return HI_SUCCESS;
}

/* load hor and vert coef */
static HI_U32 VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_VPSS_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U32 *pu32Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    //load chroma horizontal zoom coef
    VpssZmeTransCoefAlign(g_pVZmeReduceVpssCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);
    memcpy(pu32Addr, stArray.s32CoefAttr, stArray.u32Size);

    return HI_SUCCESS;
}

/* Vpss in 3798mv200 is LH6��CH4��LV4��CV4 */
HI_VOID PQ_HAL_VpssLoadCoef(HI_U32 *pu32CurAddr, HI_U32 u32PhyAddr, ALG_VZME_COEF_ADDR_S *pstAddrTmp)
{
    HI_U32 u32NumSize;

    /* HL6 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VPSS_COEF_6T32P_LH, VZME_TAP_6T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL6_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* HC4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* VL4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* VC4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, PQ_HAL_ZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    return;
}

/***********************************Load VPSS ZME COEF END*******************************************/

/***************************************VPSS ZME START*******************************************/

static HI_S32 PQ_HAL_VPSS_SetZmeEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode ==  REG_ZME_MODE_HORL ) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchmsc_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeInSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width)
{
    switch (ePort)
    {
        case VPSS_REG_HD:

            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInSize error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeOutSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            pstReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh = u32Height - 1;
            pstReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow = u32Width  - 1;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutSize error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeFirEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode ==  REG_ZME_MODE_HORL ) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchfir_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeFirEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeMidEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode == REG_ZME_MODE_HORL) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlmid_en = bEnable;
            }
            if ((eMode ==  REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchmid_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlmid_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchmid_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeMidEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmePhase(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_S32 s32Phase)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HORC)
            {
                pstReg->VPSS_VHD0_HCOFFSET.bits.hor_coffset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_HORL)
            {
                pstReg->VPSS_VHD0_HLOFFSET.bits.hor_loffset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_VERC)
            {
                pstReg->VPSS_VHD0_VOFFSET.bits.vchroma_offset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_VERL)
            {
                pstReg->VPSS_VHD0_VOFFSET.bits.vluma_offset = s32Phase;
            }
            else
            {
                HI_ERR_PQ("Error,VPSS_REG_SetZmePhase error\n");
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmePhase error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeRatio(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Ratio)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HOR)
            {
                pstReg->VPSS_VHD0_HSP.bits.hratio = u32Ratio;
            }
            else
            {
                pstReg->VPSS_VHD0_VSR.bits.vratio = u32Ratio;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeRatio error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeHfirOrder(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_BOOL bVfirst)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            //pstReg->VPSS_VHD_HSP.bits.hfir_order = bVfirst;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeHfirOrder error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeInFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat)
{
    HI_U32 u32Format;

    switch (eFormat)
    {
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV61:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_YUV400:
        case HI_DRV_PIX_FMT_YUV422_1X2:
        case HI_DRV_PIX_FMT_YUV420p:
        case HI_DRV_PIX_FMT_YUV410p:
            u32Format = 0x1;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_YUV_444:
        case HI_DRV_PIX_FMT_YUV422_2X1:
        case HI_DRV_PIX_FMT_YUV411:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
            u32Format = 0x0;
            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInFmt error\n");
            return HI_FAILURE;
    }

    switch (ePort)
    {
        case VPSS_REG_HD:
            //pstReg->VPSS_VHD0_VSP.bits.zme_in_fmt = u32Format;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInFmt error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeOutFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat)
{
    HI_U32 u32Format;

    switch (eFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            u32Format = 0x1;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
        case HI_DRV_PIX_FMT_ARGB8888:   /* sp420->sp422->csc->rgb */
        case HI_DRV_PIX_FMT_ABGR8888:
            //case HI_DRV_PIX_FMT_KBGR8888:
            u32Format = 0x0;
            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutFmt error\n");
            return HI_FAILURE;
    }

    switch (ePort)
    {
        case VPSS_REG_HD:
            pstReg->VPSS_VHD0_VSP.bits.zme_out_fmt = u32Format;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutFmt error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeCoefAddr(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Addr)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HORC)
            {
                pstReg->VPSS_VHD0_ZME_CHADDR.bits.vhd0_scl_ch = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_HORL)
            {
                pstReg->VPSS_VHD0_ZME_LHADDR.bits.vhd0_scl_lh = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_VERC)
            {
                pstReg->VPSS_VHD0_ZME_CVADDR.bits.vhd0_scl_cv = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_VERL)
            {
                pstReg->VPSS_VHD0_ZME_LVADDR.bits.vhd0_scl_lv = u32Addr;
            }
            else
            {
                HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeCoefAddr error\n");
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeCoefAddr error\n");
            break;
    }

    return HI_SUCCESS;
}

/* Vpss Cfg Set to reg */
HI_VOID PQ_HAL_VpssZmeRegCfg(HI_U32 u32LayerId, S_CAS_REGS_TYPE *pstReg, ALG_VZME_RTL_PARA_S *pstZmeRtlPara, HI_BOOL bFirEnable)
{
    HI_U32 ih;
    HI_U32 iw;
    HI_U32 oh;
    HI_U32 ow;
    HI_U32 u32HandleNo = 0;

    ih = pstZmeRtlPara->u32ZmeHIn;
    iw = pstZmeRtlPara->u32ZmeWIn;
    oh = pstZmeRtlPara->u32ZmeHOut;
    ow = pstZmeRtlPara->u32ZmeWOut;

    if (ih == oh && iw == ow && iw > 1920 && ih > 1200)
    {
        PQ_HAL_VPSS_SetZmeEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_ALL, HI_FALSE);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_ALL, HI_TRUE);
    }

    /* debug start sdk 2012-1-30; debug config for SDK debug: fixed to copy mode that don't need zme coefficient */
    /*
    pstZmeRtlPara->bZmeMdHL = 0;
    pstZmeRtlPara->bZmeMdHC = 0;
    pstZmeRtlPara->bZmeMdVL = 0;
    pstZmeRtlPara->bZmeMdVC = 0;
    */
    /* debug end sdk 2012-1-30 */

    if (!bFirEnable)
    {
        /* for fidelity output */
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMdHL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMdHC);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, HI_FALSE);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, HI_FALSE);
    }
    else
    {
        /* for normal output */
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMdHL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMdHC);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->bZmeMdVL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->bZmeMdVC);
    }

    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMedHL);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMedHC);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->bZmeMedVL);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->bZmeMedVC);

    PQ_HAL_VPSS_SetZmePhase(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->s32ZmeOffsetVL);
    PQ_HAL_VPSS_SetZmePhase(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->s32ZmeOffsetVC);

    PQ_HAL_VPSS_SetZmeRatio(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HOR, pstZmeRtlPara->u32ZmeRatioHL);
    PQ_HAL_VPSS_SetZmeRatio(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VER, pstZmeRtlPara->u32ZmeRatioVL);

    if (u32LayerId == VPSS_REG_SD)
    {
        PQ_HAL_VPSS_SetZmeHfirOrder(u32HandleNo, u32LayerId, pstReg, pstZmeRtlPara->bZmeOrder);
    }

    if (pstZmeRtlPara->u8ZmeYCFmtIn == PQ_ALG_ZME_PIX_FORMAT_SP420)
    {
        PQ_HAL_VPSS_SetZmeInFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV21);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeInFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV61_2X1);
    }

    if (pstZmeRtlPara->u8ZmeYCFmtOut == PQ_ALG_ZME_PIX_FORMAT_SP420)
    {
        PQ_HAL_VPSS_SetZmeOutFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV21);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeOutFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV61_2X1);
    }

    PQ_HAL_VPSS_SetZmeInSize(u32HandleNo, u32LayerId, pstReg, ih, iw);
    PQ_HAL_VPSS_SetZmeOutSize(u32HandleNo, u32LayerId, pstReg, oh, ow);

    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->u32ZmeCoefAddrHL);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->u32ZmeCoefAddrHC);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->u32ZmeCoefAddrVL);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->u32ZmeCoefAddrVC);

    return;
}

/*******************************VPSS ZME END*********************************/

static HI_VOID PQ_HAL_ColorSpaceTrans(PQ_HAL_DHD_COLORSPACE_E *penHDOutColorSpace, PQ_HAL_DHD_COLORSPACE_E *penSDOutColorSpace)
{
    HI_DRV_COLOR_SPACE_E enColorSpace_Dhd_HD, enColorSpace_Dhd_SD;

    if ((penHDOutColorSpace == HI_NULL) || (penSDOutColorSpace == HI_NULL))
    {
        return;
    }

    enColorSpace_Dhd_HD = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].enOutColorSpace;
    enColorSpace_Dhd_SD = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].enOutColorSpace;

    /* SD */
    if ((HI_DRV_CS_BT601_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT601_RGB_FULL == enColorSpace_Dhd_SD)
        || (HI_DRV_CS_BT709_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT709_RGB_FULL == enColorSpace_Dhd_SD)
        || (HI_DRV_CS_BT2020_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT2020_RGB_FULL == enColorSpace_Dhd_SD))
    {
        *penSDOutColorSpace = PQ_HAL_DHD_OUT_RGB;
    }
    else
    {
        *penSDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    }

    /* HD */
    if ((HI_DRV_CS_BT601_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT601_RGB_FULL == enColorSpace_Dhd_HD)
        || (HI_DRV_CS_BT709_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT709_RGB_FULL == enColorSpace_Dhd_HD)
        || (HI_DRV_CS_BT2020_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT2020_RGB_FULL == enColorSpace_Dhd_HD))
    {
        *penHDOutColorSpace = PQ_HAL_DHD_OUT_RGB;
    }
    else
    {
        *penHDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    }

    return;
}

static HI_S32 pq_hal_GetZmeCoefType(PQ_HAL_ZME_COEF_TYPE_E enCoefType,
                                    PQ_HAL_ZME_TAP_E enZmeTap,
                                    PQ_HAL_ZME_VDP_REDUCE_COEF_TYPE_E *penZmeCoefType,
                                    HI_U32 *pu32CoefSize)

{
    HI_U32 u32CoefSize = 0;
    PQ_HAL_ZME_VDP_REDUCE_COEF_TYPE_E enZmeCoefType = PQ_HAL_ZME_VDP_COEF_8T32P_LH;

    switch (enZmeTap)
    {
        case PQ_HAL_ZME_TAP_8T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LH == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_8T32P_LH;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 8 * 18;
            break;
        }
        case PQ_HAL_ZME_TAP_6T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LH == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_6T32P_LH;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_6T32P_LV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 6 * 18;
            break;
        }
        case PQ_HAL_ZME_TAP_4T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_4T32P_LV;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CH == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_4T32P_CH;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType)
            {
                enZmeCoefType = PQ_HAL_ZME_VDP_COEF_4T32P_CV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 4 * 18;
            break;
        }
        case PQ_HAL_ZME_TAP_5T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_5T32P_LV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 5 * 18;
            break;
        }
        case PQ_HAL_ZME_TAP_3T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_3T32P_CV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 3 * 18;
            break;
        }
        case PQ_HAL_ZME_TAP_8T2P:
        {
            if ((PQ_HAL_ZME_COEF_TYPE_LH == enCoefType) || (PQ_HAL_ZME_COEF_TYPE_CH == enCoefType))
            {
                enZmeCoefType = VZME_COEF_8T2P_HOR;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 8 * 2;
            break;
        }
        case PQ_HAL_ZME_TAP_6T2P:
        {
            if ((PQ_HAL_ZME_COEF_TYPE_LV == enCoefType) || (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType))
            {
                enZmeCoefType = VZME_COEF_6T2P_VER;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 6 * 2;
            break;
        }
        default:
        {
            HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
            *penZmeCoefType = PQ_HAL_ZME_VDP_COEF_8T32P_LH;
            *pu32CoefSize = 0;
            return HI_FAILURE;
        }
    }

    *penZmeCoefType = enZmeCoefType;
    *pu32CoefSize = u32CoefSize;

    return HI_SUCCESS;
}

/* Coef Choice = Tap + Type */
HI_S32 PQ_HAL_GetZmeCoef(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio,
                         PQ_HAL_ZME_COEF_TYPE_E enCoefType,
                         PQ_HAL_ZME_TAP_E enZmeTap,
                         HI_S16 *ps16Coef)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32CoefSize = 0;
    PQ_HAL_ZME_VDP_REDUCE_COEF_TYPE_E enZmeCoefType = PQ_HAL_ZME_VDP_COEF_8T32P_LH;

    s32Ret =  pq_hal_GetZmeCoefType(enCoefType, enZmeTap, &enZmeCoefType, &u32CoefSize);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (0 == u32CoefSize)
    {
        HI_FATAL_PQ("Wrong Coef Size\n");
        return HI_FAILURE;
    }

    if ((PQ_HAL_FROST_LEVEL_CLOSE != sg_enFrostGlassLevel)
        && ((enZmeCoefType == PQ_HAL_ZME_VDP_COEF_8T32P_LH) || (enZmeCoefType == PQ_HAL_ZME_VDP_COEF_6T32P_LV)))
    {
        memcpy((HI_VOID *)ps16Coef, (HI_VOID *)g_pVFrostZmeReduceCoef[enCoefRatio][enZmeCoefType][sg_enFrostGlassLevel - 1], u32CoefSize);
    }
    else
    {
        memcpy((HI_VOID *)ps16Coef, (HI_VOID *)g_pVZmeReduceCoef[enCoefRatio][enZmeCoefType], u32CoefSize);
    }

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetZmeDefault(HI_BOOL bOnOff)
{
    sg_bVpssZmeDefault = bOnOff;
    sg_bVdpZmeDefault  = bOnOff;

    return HI_SUCCESS;
}

static HI_VOID PQ_HAL_VpZmeDefaultConfig(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if (PQ_HAL_FROST_LEVEL_CLOSE != sg_enFrostGlassLevel)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC   = HI_TRUE;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL   = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC   = HI_TRUE;
    }

    if (HI_TRUE == sg_bVdpZmeDefault)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC   = HI_FALSE;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC   = HI_FALSE;

        pstZmeOut->bZmeDefault = HI_TRUE;  /* 1: rwzb */
    }
    else
    {
        pstZmeOut->bZmeDefault = HI_FALSE; /* 0: no rwzb */
    }

    return;
}

static HI_VOID PQ_HAL_WbcVpZmeDefaultConfig(HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    if (PQ_HAL_FROST_LEVEL_CLOSE != sg_enFrostGlassLevel)
    {
        pstZmeOut->stZmeFmt.bZmeFirHL   = HI_TRUE;
        pstZmeOut->stZmeFmt.bZmeFirHC   = HI_TRUE;
        pstZmeOut->stZmeFmt.bZmeFirVL   = HI_TRUE;
        pstZmeOut->stZmeFmt.bZmeFirVC   = HI_TRUE;
    }

    if (HI_TRUE == sg_bVdpZmeDefault)
    {
        pstZmeOut->stZmeFmt.bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirVC   = HI_FALSE;
        pstZmeOut->bZmeDefault = HI_TRUE;  /* 1: rwzb */
    }
    else
    {
        pstZmeOut->bZmeDefault = HI_FALSE; /* 0: no rwzb */
    }

    return;
}

static HI_BOOL PQ_HAL_GetDHD0P2IEnableFlag(HI_BOOL bSupportP2IOpen)
{
    if ((HI_TRUE == bSupportP2IOpen) && (HI_FALSE == g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID PQ_HAL_V0HdcpHPreZmeConfig(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
        HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    pstZmeOut->bOpenP2I = PQ_HAL_GetDHD0P2IEnableFlag(HI_FALSE); /* Modify: 98MV200����ʹ��P2I���� */

    pstZmeOut->bReadFmtIn = HI_TRUE;

    /* w : ��ȵĴ��� */
    if (pstZmeIn->u32FrmWIn <= pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
        /* out >= in  */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_FALSE;
        pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
    }
    else if (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
        /*  in < out * 2 */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_FALSE;
        pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
        /* >= 2 ~ < 4;  Open HPzme */
    {
        /* �����е�����--����: �ȴ�ֱ��ˮƽ�������߼����ܵ����ƣ����߼��Լ�Cover */
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
        /* >= 4 ~ < 8; read frame and Open HPzme */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        if (pstZmeIn->u32FrmWIn % 4 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_2X;
        }
        else
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
        /* >= 8 ~ < 16; read frame and Open HPzme */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        if (pstZmeIn->u32FrmWIn % 8 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_4X;
        }
        else if (pstZmeIn->u32FrmWIn % 4 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_2X;
        }
        else
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
        /* >= 16 ~ < 32; read frame and Open HPzme */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        if (pstZmeIn->u32FrmWIn % 16 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_8X;
        }
        else if (pstZmeIn->u32FrmWIn % 8 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_4X;
        }
        else if (pstZmeIn->u32FrmWIn % 4 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_2X;
        }
        else
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
    }
    else if (pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
        /* >= 32; read frame and Open HPzme */
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        if (pstZmeIn->u32FrmWIn % 16 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_8X;
        }
        else if (pstZmeIn->u32FrmWIn % 8 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_4X;
        }
        else if (pstZmeIn->u32FrmWIn % 4 == 0)
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_2X;
        }
        else
        {
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
    }
    else
    {
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
        pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
    }

    pstZmeOut->stPreZmeConfig.bPreZmeFir = (HI_TRUE == pstZmeOut->stPreZmeConfig.bPreZme) ? HI_TRUE : HI_FALSE;

    return;
}


static HI_VOID PQ_HAL_V0HdcpVPreZmeConfig(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
        HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    /* h : �߶��ϵĴ��� */
    if (pstZmeIn->u32FrmHIn <= pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
        /* out >= in  */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else if (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
        /*(> 1 ~ < 2); Close DrawPixel */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
        /* >= 2 ~ < 4; Close DrawPixel */
    {
        /*  �����е�����--����: �ȴ�ֱ��ˮƽ�������߼����ܵ����ƣ����߼��Լ�Cover */
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_2X;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
        /* >= 4 ~ < 8; Open DrawPixel */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_4X;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
        /* >= 8 ~ < 16; Open DrawPixel */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_8X;
    }
    else if (pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
        /* >= 16; Open DrawPixel */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_8X;
    }
    else
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }

    pstZmeOut->stPreZmeConfig.bPreZmeFir = (HI_TRUE == pstZmeOut->stPreZmeConfig.bPreZme) ? HI_TRUE : HI_FALSE;

    return;
}

static HI_VOID PQ_HAL_V0NormHPreZmeConfig(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
        HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{

    /***
        Progressive Output List:
                 in        out          mode  multiple               scheme                zme tap
          1) 3840x2160  1920x1080         1      2       read frame and Ver prescaler  1     8644
          2) 1920x1080  1280x 720        1/4     6       read frame and Ver prescaler 1/2    8543
          3) 3840x2160  1280x 720        1/4     12      read frame and Ver prescaler 1/4    8543
          4) 4096x2304  1280x 720        1/4    12.8     read frame and Ver prescaler 1/8    8644

        Interlace Output List:
                 in        out          mode   multiple              scheme                 zme tap
          1) 720 x 576  720 x 576(288)    1       2      read field and Ver prescaler  1     8644
          2) 1920x1080  1920x1080(540)    1       2      read field and Ver prescaler  1     8644
          3) 720 x 576  720 x 480(240)    1      2.4     read frame and Ver prescaler  1     8644  ---zme������
          4) 1920x1080  720 x 576(288)    1      3.75    read frame and Ver prescaler 1/2    8644
          5) 1920x1080  720 x 480(240)   1/4      18     read frame and Ver prescaler 1/8    8644  ---1080PԴ�ļ��޳���, ����Ҫ����
          6) 3840x2160  1920x1080(540)   1/4      16     read frame and Ver prescaler 1/8    8644
          7) 3840x2160  720 x 576(288)   1/3     22.5    read frame and Ver prescaler 1/8    8543  ---��Ҫzme����, 8644 -> 8543�ĳ���, cbb����
          8) 3840x2160  720 x 480(240)   1/4      36     read frame and Ver prescaler 1/8    8543
          9) 4096x2304  720 x 480(240)   1/4     38.4    read frame and Ver prescaler 1/8    8543  ---���޳���, 4KԴ�ܷ����?

          �����оٿ��Կ���: FHDԴ, ��1080i��ʽ���֮�⣬���಻��Ҫ����; ���޳�����Ҫ��P2I���߶�����, ����4KԴ;
        ***/

    pstZmeOut->bOpenP2I = PQ_HAL_GetDHD0P2IEnableFlag(HI_FALSE); /* Modify: 98MV200����ʹ��P2I���� */

    /* w : ��ȵĴ��� */
    if ((HI_FALSE == g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive)
        && ((pstZmeIn->u32FrmWIn == pstZmeIn->u32FrmWOut)
            && (pstZmeIn->u32FrmHIn == pstZmeIn->u32FrmHOut)))
        /* Interlace output and source resolution == out resolution */
    {
        pstZmeOut->bReadFmtIn               = HI_FALSE; /* preferential read field; ���ӿ�ʱ������׳� */
        pstZmeOut->stPreZmeConfig.bPreZme   = HI_FALSE;
        pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
    }
    else
    {
        pstZmeOut->bReadFmtIn = HI_TRUE;

        /* w : ��ȵĴ��� */
        if (pstZmeIn->u32FrmWIn <= pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
            /* out >= in  */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_FALSE;
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
        else if (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
            /*  in < out * 2 */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_FALSE;
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
        else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
                 && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
            /* >= 2 ~ < 4;  Open HPzme */
        {
            /* �����е�����--����: �ȴ�ֱ��ˮƽ�������߼����ܵ����ƣ����߼��Լ�Cover */
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
        else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
                 && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
            /* >= 4 ~ < 8; read frame and Open HPzme */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            if (pstZmeIn->u32FrmWIn % 8 == 0)
            {
                pstZmeOut->eHScalerMode = HI_PQ_PREZME_HOR_2X;
            }
            else
            {
                pstZmeOut->eHScalerMode = HI_PQ_PREZME_HOR_DISABLE;
            }
        }
        else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
                 && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
            /* >= 8 ~ < 16; read frame and Open HPzme */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            if (pstZmeIn->u32FrmWIn % 8 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_4X;
            }
            else if (pstZmeIn->u32FrmWIn % 4 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_2X;
            }
            else
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_DISABLE;
            }
        }
        else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
                 && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
            /* >= 16 ~ < 32; read frame and Open HPzme */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            if (pstZmeIn->u32FrmWIn % 16 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_8X;
            }
            else if (pstZmeIn->u32FrmWIn % 8 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_4X;
            }
            else if (pstZmeIn->u32FrmWIn % 4 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_2X;
            }
            else
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_DISABLE;
            }
        }
        else if (pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
            /* >= 32; read frame and Open HPzme */
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            if (pstZmeIn->u32FrmWIn % 16 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_8X;
            }
            else if (pstZmeIn->u32FrmWIn % 8 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_4X;
            }
            else if (pstZmeIn->u32FrmWIn % 4 == 0)
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_2X;
            }
            else
            {
                pstZmeOut->eHScalerMode  = HI_PQ_PREZME_HOR_DISABLE;
            }
        }
        else
        {
            pstZmeOut->stPreZmeConfig.bPreZme   = HI_TRUE;
            pstZmeOut->eHScalerMode             = HI_PQ_PREZME_HOR_DISABLE;
        }
    }

    pstZmeOut->stPreZmeConfig.bPreZmeFir = (HI_TRUE == pstZmeOut->stPreZmeConfig.bPreZme) ? HI_TRUE : HI_FALSE;

    return;
}


static HI_VOID PQ_HAL_V0NormVPreZmeConfig(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
        HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{

    /***
        Progressive Output List:
                 in        out          mode  multiple               scheme                zme tap
          1) 3840x2160  1920x1080         1      2       read frame and Ver prescaler  1     8644
          2) 1920x1080  1280x 720        1/4     6       read frame and Ver prescaler 1/2    8543
          3) 3840x2160  1280x 720        1/4     12      read frame and Ver prescaler 1/4    8543
          4) 4096x2304  1280x 720        1/4    12.8     read frame and Ver prescaler 1/8    8644

        Interlace Output List:
                 in        out          mode   multiple              scheme                 zme tap
          1) 720 x 576  720 x 576(288)    1       2      read field and Ver prescaler  1     8644
          2) 1920x1080  1920x1080(540)    1       2      read field and Ver prescaler  1     8644
          3) 720 x 576  720 x 480(240)    1      2.4     read frame and Ver prescaler  1     8644  ---zme������
          4) 1920x1080  720 x 576(288)    1      3.75    read frame and Ver prescaler 1/2    8644
          5) 1920x1080  720 x 480(240)   1/4      18     read frame and Ver prescaler 1/8    8644  ---1080PԴ�ļ��޳���, ����Ҫ����
          6) 3840x2160  1920x1080(540)   1/4      16     read frame and Ver prescaler 1/8    8644
          7) 3840x2160  720 x 576(288)   1/3     22.5    read frame and Ver prescaler 1/8    8543  ---��Ҫzme����, 8644 -> 8543�ĳ���, cbb����
          8) 3840x2160  720 x 480(240)   1/4      36     read frame and Ver prescaler 1/8    8543
          9) 4096x2304  720 x 480(240)   1/4     38.4    read frame and Ver prescaler 1/8    8543  ---���޳���, 4KԴ�ܷ����?

          �����оٿ��Կ���: FHDԴ, ��1080i��ʽ���֮�⣬���಻��Ҫ����; ���޳�����Ҫ��P2I���߶�����, ����4KԴ;
        ***/

    /* h : �߶��ϵĴ��� */
    if ((HI_FALSE == g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive)
        && ((pstZmeIn->u32FrmWIn == pstZmeIn->u32FrmWOut)
            && (pstZmeIn->u32FrmHIn == pstZmeIn->u32FrmHOut)))
        /* Interlace output and source resolution == out resolution */
    {
        pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else
    {
        if (pstZmeIn->u32FrmHIn <= pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
            /* out >= in  */
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
        }
        else if (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
            /*(> 1 ~ < 2); Close DrawPixel */
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
        }
        else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
                 && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
            /* >= 2 ~ < 4; Close DrawPixel */
        {
            /*  �����е�����--����: �ȴ�ֱ��ˮƽ�������߼����ܵ����ƣ����߼��Լ�Cover */
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_2X;
        }
        else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
                 && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
            /* >= 4 ~ < 8; Open DrawPixel */
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_4X;
        }
        else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
                 && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
            /* >= 8 ~ < 16; Open DrawPixel */
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_8X;
        }
        else if (pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight)
            /* >= 16; Open DrawPixel */
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_8X;
        }
        else
        {
            pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
        }
    }

    return;
}

HI_VOID PQ_HAl_TransResolutionToLevel(PQ_HAL_VID_RESOLUTION stVidResolution, PQ_HAL_RES_LEVEL_E *penInResLevel, PQ_HAL_RES_LEVEL_E *penOutResLevel)
{
    PQ_HAL_RES_LEVEL_E enInResLevel, enOutResLevel;

    if (stVidResolution.u32InImageWidth <= 720) /* SD Source */
    {
        enInResLevel = HAL_RES_SD;
    }
    else if (stVidResolution.u32InImageWidth <= 1280) /* HD Source */
    {
        enInResLevel = HAL_RES_HD;
    }
    else if (stVidResolution.u32InImageWidth <= 1920) /* FHD Source */
    {
        enInResLevel = HAL_RES_FHD;
    }
    else /* UHD Source */
    {
        enInResLevel = HAL_RES_UHD;
    }

    if (stVidResolution.u32OutImageWidth <= 720) /* SD OutPut */
    {
        enOutResLevel = HAL_RES_SD;
    }
    else if (stVidResolution.u32OutImageWidth <= 1280) /* HD OutPut */
    {
        enOutResLevel = HAL_RES_HD;
    }
    else if (stVidResolution.u32OutImageWidth <= 1920) /* FHD OutPut */
    {
        enOutResLevel = HAL_RES_FHD;
    }
    else /* UHD OutPut */
    {
        enOutResLevel = HAL_RES_UHD;
    }

    *penInResLevel = enInResLevel;

    return;
}

HI_VOID PQ_HAL_GetFrostLevelLowPara(PQ_HAL_RES_LEVEL_E enInResLevel, PQ_HAL_RES_LEVEL_E enOutResLevel,
                                    HI_PQ_PREZME_HOR_MUL_E *penHScalerMode, HI_PQ_PREZME_VER_MUL_E *penVScalerMode, HI_BOOL *pbHPZme)
{
    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_LOW;

    switch (enInResLevel)
    {
        case HAL_RES_SD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            break;
        case HAL_RES_HD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_MIDDLE;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_FHD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_2X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                    *pbHPZme = HI_TRUE;
                    break;
                case HAL_RES_HD:
                    break;
                case HAL_RES_FHD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                    break;
                case HAL_RES_UHD:
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_MIDDLE;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_UHD: /* Input FHD */
            *pbHPZme        = HI_TRUE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_4X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                case HAL_RES_HD:
                    break;
                case HAL_RES_FHD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                    break;
                case HAL_RES_UHD:
                    *penVScalerMode      = PQ_HAL_PREZME_VER_8X;
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_MIDDLE;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_BUTT:
            break;
    }
    return;
}

HI_VOID PQ_HAL_GetFrostLevelMiddlePara(PQ_HAL_RES_LEVEL_E enInResLevel, PQ_HAL_RES_LEVEL_E enOutResLevel,
                                       HI_PQ_PREZME_HOR_MUL_E *penHScalerMode, HI_PQ_PREZME_VER_MUL_E *penVScalerMode, HI_BOOL *pbHPZme)
{
    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_MIDDLE;

    switch (enInResLevel)
    {
        case HAL_RES_SD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            break;
        case HAL_RES_HD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_HIGH;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_FHD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_2X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                    *pbHPZme = HI_TRUE;
                    break;
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                    break;
                case HAL_RES_UHD:
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_HIGH;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_UHD: /* Input FHD */
            *pbHPZme        = HI_TRUE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
            *penVScalerMode = PQ_HAL_PREZME_VER_4X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                    break;
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    *penVScalerMode      = PQ_HAL_PREZME_VER_8X;
                    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_HIGH;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_BUTT:
            break;
    }

    return;
}

HI_VOID PQ_HAL_GetFrostLevelHighPara(PQ_HAL_RES_LEVEL_E enInResLevel, PQ_HAL_RES_LEVEL_E enOutResLevel,
                                     HI_PQ_PREZME_HOR_MUL_E *penHScalerMode, HI_PQ_PREZME_VER_MUL_E *penVScalerMode, HI_BOOL *pbHPZme)
{
    sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_HIGH;

    switch (enInResLevel)
    {
        case HAL_RES_SD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            break;
        case HAL_RES_HD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    *penVScalerMode = PQ_HAL_PREZME_VER_2X;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_FHD:
            *pbHPZme        = HI_FALSE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_4X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                    *pbHPZme = HI_TRUE;
                    break;
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_UHD: /* Input FHD */
            *pbHPZme        = HI_TRUE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_4X;
            *penVScalerMode = PQ_HAL_PREZME_VER_4X;
            switch (enOutResLevel)
            {
                case HAL_RES_SD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_2X;
                case HAL_RES_HD:
                case HAL_RES_FHD:
                    break;
                case HAL_RES_UHD:
                    *penHScalerMode = PQ_HAL_PREZME_HOR_8X;
                    *penVScalerMode = PQ_HAL_PREZME_VER_8X;
                    break;
                case HAL_RES_BUTT:
                    break;
            }
            break;
        case HAL_RES_BUTT:
            break;
    }

    return;
}


HI_VOID PQ_HAL_SetFrostPreZme(PQ_HAL_FROST_LEVEL_E enFrostLevel,
                              PQ_HAL_RES_LEVEL_E enInResLevel,
                              PQ_HAL_RES_LEVEL_E enOutResLevel,
                              HI_PQ_PREZME_HOR_MUL_E *penHScalerMode,
                              HI_PQ_PREZME_VER_MUL_E *penVScalerMode,
                              HI_BOOL *pbHPZme)
{
    switch (enFrostLevel)
    {
        case HI_PQ_FROST_LEVEL_LOW:
            PQ_HAL_GetFrostLevelLowPara(enInResLevel, enOutResLevel, penHScalerMode, penVScalerMode, pbHPZme);
            break;
        case HI_PQ_FROST_LEVEL_MIDDLE:
            PQ_HAL_GetFrostLevelMiddlePara(enInResLevel, enOutResLevel, penHScalerMode, penVScalerMode, pbHPZme);
            break;
        case HI_PQ_FROST_LEVEL_HIGH:
            PQ_HAL_GetFrostLevelHighPara(enInResLevel, enOutResLevel, penHScalerMode, penVScalerMode, pbHPZme);
            break;
        case HI_PQ_FROST_LEVEL_CLOSE:
        default:
            *pbHPZme        = PQ_HAL_PREZME_VER_DISABLE;
            *penHScalerMode = PQ_HAL_PREZME_HOR_DISABLE;
            *penVScalerMode = PQ_HAL_PREZME_VER_DISABLE;
            break;
    }

    return;
}

HI_VOID PQ_HAL_FrostCfgTrans(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, PQ_HAL_FROST_CFG_S *pstFrostCfg)
{
    pstFrostCfg->stV0Resolution.u32InImageWidth   = pstZmeIn->u32FrmWIn;
    pstFrostCfg->stV0Resolution.u32InImageHeight  = pstZmeIn->u32FrmHIn;
    pstFrostCfg->stV0Resolution.u32OutImageWidth  = pstZmeIn->u32FrmWOut;
    pstFrostCfg->stV0Resolution.u32OutImageHeight = pstZmeIn->u32FrmHOut;

    pstFrostCfg->eFrostLevel = pstZmeIn->eFrostLevel;

    if (sg_enProcFrostLevel != HI_PQ_FROST_LEVEL_CLOSE)
    {
        pstFrostCfg->eFrostLevel = sg_enProcFrostLevel;
    }

    sg_enFrostGlassLevel     = pstFrostCfg->eFrostLevel;
}
/*****
    * FrostGlass���ýӿ�:
    * 1. ������������ֱ��ʼ�ë����ǿ�ȣ�
    * 2. ����������ֱ���ת��Ϊ�ֱ��ʵȼ���
    * 3. ����ë����ǿ�ȵȼ��޸Ĵ��ݸ�cbb���˲�ϵ����(cbb��Ҫ��֤�ڴ˳�������ˢ���˲�ϵ��)
    * 4. ���������������ó����в��ԣ�
     ******/
HI_S32 PQ_HAL_SetFrostGlassLevel(PQ_HAL_FROST_CFG_S stFrostCfg,
                                 HI_BOOL *pbReadFrame,
                                 HI_PQ_PREZME_HOR_MUL_E *penHScalerMode,
                                 HI_PQ_PREZME_VER_MUL_E *penVScalerMode,
                                 HI_PQ_PREZME_CONFIG_S *pstPreZmeConfig,
                                 HI_BOOL *pbOpenP2I)
{
    PQ_HAL_RES_LEVEL_E enInResLevel  = HAL_RES_HD;
    PQ_HAL_RES_LEVEL_E enOutResLevel = HAL_RES_HD;

    /*ë����������������Ҳ������P2I */
    *pbReadFrame = HI_TRUE;
    *pbOpenP2I   = HI_FALSE;

    PQ_HAl_TransResolutionToLevel(stFrostCfg.stV0Resolution, &enInResLevel, &enOutResLevel);
    PQ_HAL_SetFrostPreZme(stFrostCfg.eFrostLevel,
                          enInResLevel,
                          enOutResLevel,
                          penHScalerMode,
                          penVScalerMode,
                          &(pstPreZmeConfig->bPreZme));

    pstPreZmeConfig->bPreZmeFir = (HI_TRUE == pstPreZmeConfig->bPreZme) ? HI_TRUE : HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetHDCPAttest(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
                            HI_BOOL *pbReadFrame,
                            HI_PQ_PREZME_HOR_MUL_E *penHScalerMode,
                            HI_PQ_PREZME_VER_MUL_E *penVScalerMode,
                            HI_PQ_PREZME_CONFIG_S *pstPreZmeConfig,
                            HI_BOOL *pbOpenP2I)
{
    HI_BOOL bHPZmeEnable = HI_FALSE;
    HI_U32  u32IntermedHeight, u32IntermedWidth;

    /* �м�ֱ�����VDP����: ��һ������(ֻ����С)��������������, Ҫʹ���м伶�ķֱ��ʼ������ű� */
    u32IntermedWidth  = pstZmeIn->stHDCPAttestFactor.u32IntermedWidth;
    u32IntermedHeight = pstZmeIn->stHDCPAttestFactor.u32IntermedHeight;

    /* HDCP2.2��֤������������Ҳ������P2I */
    *pbReadFrame    = HI_TRUE;
    *pbOpenP2I      = HI_FALSE;
    *penHScalerMode = HI_PQ_PREZME_HOR_DISABLE;

    if (pstZmeIn->u32FrmHIn <= V0_READ_FMT_ZME_THD * u32IntermedHeight) /* (in <= out) or (> 1 ~ <= 2); read frame and close prescaler*/
    {
        bHPZmeEnable    = HI_FALSE;
        *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else if ((pstZmeIn->u32FrmHIn > V0_READ_FMT_ZME_THD * u32IntermedHeight)
             && (pstZmeIn->u32FrmHIn <= V0_HPZME_ENABLE_THD * u32IntermedHeight)) /* > 2 ~ <= 3; read frame and Open HPzme */
    {
        bHPZmeEnable    = HI_TRUE;
        *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else if ((pstZmeIn->u32FrmHIn > V0_READ_FMT_ZME_THD * u32IntermedHeight)
             && (pstZmeIn->u32FrmHIn <= V0_PREZME_ENABLE_2_THD * u32IntermedHeight)) /* > 3 ~ <= 6; read frame and 1/2 prescaler*/
    {
        bHPZmeEnable    = HI_TRUE;
        *penVScalerMode = HI_PQ_PREZME_VER_2X;
    }
    else if ((pstZmeIn->u32FrmHIn > V0_PREZME_ENABLE_2_THD * u32IntermedHeight)
             && (pstZmeIn->u32FrmHIn <= V0_PREZME_ENABLE_4_THD * u32IntermedHeight)) /* > 6 ~ <= 12; read frame and 1/4 prescaler */
    {
        bHPZmeEnable    = HI_TRUE;
        *penVScalerMode = HI_PQ_PREZME_VER_4X;
    }
    else if ((pstZmeIn->u32FrmHIn > V0_PREZME_ENABLE_4_THD * u32IntermedHeight)
             && (pstZmeIn->u32FrmHIn <= V0_PREZME_ENABLE_8_THD * u32IntermedHeight)) /* > 12 ~ <= 24; read frame and 1/8 prescaler */
    {
        bHPZmeEnable    = HI_TRUE;
        *penVScalerMode = HI_PQ_PREZME_VER_8X;
    }
    else if (pstZmeIn->u32FrmHIn > V0_PREZME_ENABLE_8_THD * u32IntermedHeight)       /* > 24; read field and 1/8 prescaler */
    {
        bHPZmeEnable    = HI_TRUE;
        *penVScalerMode = HI_PQ_PREZME_VER_8X;
        *penHScalerMode = HI_PQ_PREZME_VER_2X;
    }

    return HI_SUCCESS;
}


static HI_VOID pq_hal_EnableSharp(HI_BOOL bOnOff)
{
    HI_U32 u32Data = 0;
    U_SPCTRL  SPCTRL;
    S_VDP_REGS_TYPE *pVDPReg = PQ_HAL_GetVdpReg();

    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVDPReg->SPCTRL.u32)) + u32Data * PQ_VID_OFFSET));
    SPCTRL.bits.sharpen_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVDPReg->SPCTRL.u32)) + u32Data * PQ_VID_OFFSET), SPCTRL.u32);

    return;
}

static HI_VOID PQ_HAL_SetSharpConfig(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth > SHARPEN_SUPPOR_MAX_WITDH)
        || (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight > SHARPEN_SUPPOR_MAX_HEIGHT))
    {
        pq_hal_EnableSharp(HI_FALSE);
        return;
    }

    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth != g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Width)
        || (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight != g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Height))
    {
        /*preview*/
        pq_hal_EnableSharp(HI_FALSE);
    }

    if (((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth <= SHARPEN_SUPPOR_MAX_WITDH)
         || (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight <= SHARPEN_SUPPOR_MAX_HEIGHT))
        &&
        ((g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Width >= DHD0_OUT_RESOLUTION_W_THD)
         || (g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Height >= DHD0_OUT_RESOLUTION_H_THD)))
    {
        if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth * V0_SCALER1_AMPLIFY_ENABLE_THD)
            && (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight * V0_SCALER1_AMPLIFY_ENABLE_THD)
            && ((HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL) || (HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC)
                || (HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL) || (HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC)))
        {
            pq_hal_EnableSharp(HI_TRUE);
        }
        else
        {
            pq_hal_EnableSharp(HI_FALSE);
        }
    }

    return;
}

static HI_S32 pq_hal_GetVerticalScalerOffset(HI_U32 u32VRatio, PQ_HAL_ALG_VZME_DRV_PARA_S *pstZmeDrvPara)
{
    HI_S32 s32VOffset = 0;


    if (pstZmeDrvPara->bZmeFrmFmtIn) /* processive input */
    {
        if (pstZmeDrvPara->bZmeFrmFmtOut) /* processive output */
        {
            s32VOffset = 0;
        }
        else /* interlaced output */
        {
            if (pstZmeDrvPara->bZmeBFOut) /* bottom field output */
            {
                s32VOffset = (HI_S32)u32VRatio >> 1;
            }
            else /*top field output */
            {
                s32VOffset = 0;
            }
        }
    }
    else /* interlaced input */
    {
        if (pstZmeDrvPara->bZmeFrmFmtOut) /* processive output */
        {
            if (pstZmeDrvPara->bZmeBFIn) /* bottom field input */
            {
                s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 1); /* -2048 */
            }
            else /* top field input */
            {
                s32VOffset = 0;
            }
        }
        else /* interlaced output */
        {
            if (pstZmeDrvPara->bZmeBFIn) /* bottom field input */
            {
                if (pstZmeDrvPara->bZmeBFOut) /* bottom field output */
                {
                    s32VOffset = ((HI_S32)u32VRatio - PQ_HAL_ALG_V_VZME_PRECISION) >> 1;
                }
                else /* top field output */
                {
                    s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 1); /* -2048 */
                }
            }
            else /* top field input */
            {
                if (pstZmeDrvPara->bZmeBFOut) /* bottom field output */
                {
                    s32VOffset = (HI_S32)u32VRatio >> 1;
                }
                else /* top field output */
                {
                    s32VOffset = 0;
                }
            }
        }
    }

    return s32VOffset;
}

static HI_VOID pq_hal_SetV0OneZmeOffset(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn,
                                        HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32 u32ZmeCWIn, u32ZmeCWOut, u32ZmeCHIn, u32ZmeCHOut;
    HI_S32 s32VOffset, s32HOffset;
    HI_U32 u32ZmeRatioVLReal, u32ZmeRatioVCReal;
    PQ_HAL_ALG_VZME_DRV_PARA_S  stZmeDrvPara;
    ALG_VZME_RTL_PARA_S         stZmeRtlPara;

    /* calculate luma real zme resolution of input and output */
    stZmeRtlPara.u32ZmeWIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth;
    stZmeRtlPara.u32ZmeWOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
    stZmeRtlPara.u32ZmeHIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight;
    stZmeRtlPara.u32ZmeHOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
    stZmeDrvPara.u8ZmeYCFmtIn  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt ;
    stZmeDrvPara.u8ZmeYCFmtOut = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt;
    /* zme in & out frame or field */
    stZmeDrvPara.bZmeFrmFmtIn  = pstZmeOut->bReadFmtIn;
    stZmeDrvPara.bZmeFrmFmtOut = pstZmeIn->bZmeFrmFmtOut; /* Field : Top Or Bottom */

    stZmeDrvPara.bZmeBFIn  = pstZmeIn->bZmeBFIn; /* Field : Top Or Bottom */
    stZmeDrvPara.bZmeBFOut = pstZmeIn->bZmeBFOut; /* Field : Top Or Bottom */

    //stZmeRtlPara.u32ZmeHIn  = ( stZmeDrvPara.bZmeFrmFmtIn  == 1 ) ? stZmeDrvPara.u32ZmeFrmHIn: stZmeDrvPara.u32ZmeFrmHIn/2;
    //stZmeRtlPara.u32ZmeHOut = ( stZmeDrvPara.bZmeFrmFmtOut == 1 ) ? stZmeDrvPara.u32ZmeFrmHOut: stZmeDrvPara.u32ZmeFrmHOut/2;

    /* when wide > 4096, overflow will occurs */
    if (stZmeRtlPara.u32ZmeWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHL = (stZmeRtlPara.u32ZmeWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / stZmeRtlPara.u32ZmeWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHL = stZmeRtlPara.u32ZmeWIn * PQ_HAL_ALG_V_HZME_PRECISION / stZmeRtlPara.u32ZmeWOut;
    }
    stZmeRtlPara.u32ZmeRatioVL = stZmeRtlPara.u32ZmeHIn * PQ_HAL_ALG_V_VZME_PRECISION / stZmeRtlPara.u32ZmeHOut;

    /* calculate chroma zme ratio */
    u32ZmeCWIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 2 ) ? stZmeRtlPara.u32ZmeWIn : stZmeRtlPara.u32ZmeWIn / 2;
    u32ZmeCWOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 2 ) ? stZmeRtlPara.u32ZmeWOut : stZmeRtlPara.u32ZmeWOut / 2;
    u32ZmeCHIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 1 ) ? stZmeRtlPara.u32ZmeHIn / 2 : stZmeRtlPara.u32ZmeHIn;
    u32ZmeCHOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 1 ) ? stZmeRtlPara.u32ZmeHOut / 2 : stZmeRtlPara.u32ZmeHOut;

    /* when wide > 4096, overflow will occurs */
    if (u32ZmeCWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHC = (u32ZmeCWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / u32ZmeCWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHC = u32ZmeCWIn * PQ_HAL_ALG_V_HZME_PRECISION / u32ZmeCWOut;
    }
    stZmeRtlPara.u32ZmeRatioVC = u32ZmeCHIn * PQ_HAL_ALG_V_VZME_PRECISION / u32ZmeCHOut;

    /* Input Progressive and Output Interlace */
    if (1 == stZmeDrvPara.bZmeFrmFmtIn && 0 == stZmeDrvPara.bZmeFrmFmtOut)
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL * 2;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC * 2;
    }
    else
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC;
    }

    /* calculate luma zme offset */
    stZmeRtlPara.s32ZmeOffsetHL = 0;

    /* Set Top filelds calc ZmeoffsetVL */
    stZmeRtlPara.s32ZmeOffsetVL = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);

    /* calculate chroma zme offset */
    s32VOffset = 0, s32HOffset = 0;
    if (1 == stZmeDrvPara.u8ZmeYCFmtIn) /* 4:2:0 */
    {
        /* horizontal offset for cosited or interspersed format *//* fixed to false; interspersed format */
        s32HOffset = 0;

        /* vertical offset for processive or interlaced input format */
        if (stZmeDrvPara.bZmeFrmFmtIn) /* processive input for zme */
        {
            s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
        }
        else /* interlaced input for zme */
        {
            if (stZmeDrvPara.bZmeBFIn) /* bottom field input for zme */
            {
                s32VOffset = -((3 * PQ_HAL_ALG_V_VZME_PRECISION) >> 2) >> 1; /* -3072 >> 1 */
            }
            else /* top field input for zme */
            {
                s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
            }
        }
    }

    stZmeRtlPara.s32ZmeOffsetHC = s32HOffset;
    stZmeRtlPara.s32ZmeOffsetVC = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    stZmeRtlPara.s32ZmeOffsetVLBtm = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);
    stZmeRtlPara.s32ZmeOffsetVCBtm = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL       = stZmeRtlPara.s32ZmeOffsetHL;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC       = stZmeRtlPara.s32ZmeOffsetHC;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL       = stZmeRtlPara.s32ZmeOffsetVL;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC       = stZmeRtlPara.s32ZmeOffsetVC;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm    = stZmeRtlPara.s32ZmeOffsetVLBtm;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm    = stZmeRtlPara.s32ZmeOffsetVCBtm;


    return;
}

static HI_VOID pq_hal_SetV0TwoZmeOffset(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32 u32ZmeCWIn, u32ZmeCWOut, u32ZmeCHIn, u32ZmeCHOut;
    HI_S32 s32VOffset, s32HOffset;
    HI_U32 u32ZmeRatioVLReal, u32ZmeRatioVCReal;

    PQ_HAL_ALG_VZME_DRV_PARA_S  stZmeDrvPara;
    ALG_VZME_RTL_PARA_S         stZmeRtlPara;

    HI_U32 u32Zme2CWIn, u32Zme2CWOut, u32Zme2CHIn, u32Zme2CHOut;
    HI_S32 s32Zme2VOffset, s32Zme2HOffset;
    HI_U32 u32Zme2RatioVLReal, u32Zme2RatioVCReal;

    PQ_HAL_ALG_VZME_DRV_PARA_S  stZmeDrvParaZme2;
    ALG_VZME_RTL_PARA_S         stZmeRtlParaZme2;

    /* calculate luma real zme resolution of input and output */
    stZmeRtlPara.u32ZmeWIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth;
    stZmeRtlPara.u32ZmeWOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
    stZmeRtlPara.u32ZmeHIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight;
    stZmeRtlPara.u32ZmeHOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
    stZmeDrvPara.u8ZmeYCFmtIn  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt ;
    stZmeDrvPara.u8ZmeYCFmtOut = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt;
    /* zme in & out frame or field */
    stZmeDrvPara.bZmeFrmFmtIn  = pstZmeOut->bReadFmtIn;
    stZmeDrvPara.bZmeFrmFmtOut = pstZmeOut->bReadFmtIn;

    stZmeDrvPara.bZmeBFIn  = pstZmeIn->bZmeBFIn; /* Field : Top Or Bottom */
    stZmeDrvPara.bZmeBFOut = pstZmeIn->bZmeBFOut; /* Field : Top Or Bottom */


    //stZmeRtlPara.u32ZmeHIn  = ( stZmeDrvPara.bZmeFrmFmtIn  == 1 ) ? stZmeDrvPara.u32ZmeFrmHIn: stZmeDrvPara.u32ZmeFrmHIn/2;
    //stZmeRtlPara.u32ZmeHOut = ( stZmeDrvPara.bZmeFrmFmtOut == 1 ) ? stZmeDrvPara.u32ZmeFrmHOut: stZmeDrvPara.u32ZmeFrmHOut/2;

    /* when wide > 4096, overflow will occurs */
    if (stZmeRtlPara.u32ZmeWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHL = (stZmeRtlPara.u32ZmeWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / stZmeRtlPara.u32ZmeWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHL = stZmeRtlPara.u32ZmeWIn * PQ_HAL_ALG_V_HZME_PRECISION / stZmeRtlPara.u32ZmeWOut;
    }
    stZmeRtlPara.u32ZmeRatioVL = stZmeRtlPara.u32ZmeHIn * PQ_HAL_ALG_V_VZME_PRECISION / stZmeRtlPara.u32ZmeHOut;

    /* calculate chroma zme ratio */
    u32ZmeCWIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 2 ) ? stZmeRtlPara.u32ZmeWIn : stZmeRtlPara.u32ZmeWIn / 2;
    u32ZmeCWOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 2 ) ? stZmeRtlPara.u32ZmeWOut : stZmeRtlPara.u32ZmeWOut / 2;
    u32ZmeCHIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 1 ) ? stZmeRtlPara.u32ZmeHIn / 2 : stZmeRtlPara.u32ZmeHIn;
    u32ZmeCHOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 1 ) ? stZmeRtlPara.u32ZmeHOut / 2 : stZmeRtlPara.u32ZmeHOut;

    /* when wide > 4096, overflow will occurs */
    if (u32ZmeCWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHC = (u32ZmeCWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / u32ZmeCWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHC = u32ZmeCWIn * PQ_HAL_ALG_V_HZME_PRECISION / u32ZmeCWOut;
    }
    stZmeRtlPara.u32ZmeRatioVC = u32ZmeCHIn * PQ_HAL_ALG_V_VZME_PRECISION / u32ZmeCHOut;

    /* Input Progressive and Output Interlace */
    if (1 == stZmeDrvPara.bZmeFrmFmtIn && 0 == stZmeDrvPara.bZmeFrmFmtOut)
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL * 2;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC * 2;
    }
    else
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC;
    }

    /* calculate luma zme offset */
    stZmeRtlPara.s32ZmeOffsetHL = 0;

    /* Set Top filelds calc ZmeoffsetVL */
    stZmeRtlPara.s32ZmeOffsetVL = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);

    /* calculate chroma zme offset */
    s32VOffset = 0, s32HOffset = 0;
    if (1 == stZmeDrvPara.u8ZmeYCFmtIn) /* 4:2:0 */
    {
        /* horizontal offset for cosited or interspersed format *//* fixed to false; interspersed format */
        s32HOffset = 0;

        /* vertical offset for processive or interlaced input format */
        if (stZmeDrvPara.bZmeFrmFmtIn) /* processive input for zme */
        {
            s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
        }
        else /* interlaced input for zme */
        {
            if (stZmeDrvPara.bZmeBFIn) /* bottom field input for zme */
            {
                s32VOffset = -((3 * PQ_HAL_ALG_V_VZME_PRECISION) >> 2) >> 1; /* -3072 >> 1 */
            }
            else /* top field input for zme */
            {
                s32VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
            }
        }
    }

    stZmeRtlPara.s32ZmeOffsetHC = s32HOffset;
    stZmeRtlPara.s32ZmeOffsetVC = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    stZmeRtlPara.s32ZmeOffsetVLBtm = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);
    stZmeRtlPara.s32ZmeOffsetVCBtm = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL       = stZmeRtlPara.s32ZmeOffsetHL;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC       = stZmeRtlPara.s32ZmeOffsetHC;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL       = stZmeRtlPara.s32ZmeOffsetVL;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC       = stZmeRtlPara.s32ZmeOffsetVC;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm    = stZmeRtlPara.s32ZmeOffsetVLBtm;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm    = stZmeRtlPara.s32ZmeOffsetVCBtm;


    /* zme2 settings */
    /* calculate luma real zme resolution of input and output */
    stZmeRtlParaZme2.u32ZmeWIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    stZmeRtlParaZme2.u32ZmeWOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth;
    stZmeRtlParaZme2.u32ZmeHIn     = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    stZmeRtlParaZme2.u32ZmeHOut    = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight;
    stZmeDrvParaZme2.u8ZmeYCFmtIn  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt ;
    stZmeDrvParaZme2.u8ZmeYCFmtOut = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt;
    /* zme in & out frame or field */
    stZmeDrvParaZme2.bZmeFrmFmtIn  = pstZmeOut->bReadFmtIn;
    stZmeDrvParaZme2.bZmeFrmFmtOut = pstZmeIn->bZmeFrmFmtOut; /* Field : Top Or Bottom */

    stZmeDrvParaZme2.bZmeBFIn = pstZmeIn->bZmeBFIn; /* Field : Top Or Bottom */
    stZmeDrvParaZme2.bZmeBFOut = pstZmeIn->bZmeBFOut; /* Field : Top Or Bottom */

    //stZmeRtlParaZme2.u32ZmeHIn  = ( stZmeDrvParaZme2.bZmeFrmFmtIn  == 1 ) ? stZmeDrvParaZme2.u32ZmeFrmHIn: stZmeDrvParaZme2.u32ZmeFrmHIn/2;
    //stZmeRtlParaZme2.u32ZmeHOut = ( stZmeDrvParaZme2.bZmeFrmFmtOut == 1 ) ? stZmeDrvParaZme2.u32ZmeFrmHOut: stZmeDrvParaZme2.u32ZmeFrmHOut/2;

    /* when wide > 4096, overflow will occurs */
    if (stZmeRtlParaZme2.u32ZmeWIn >= 4096)
    {
        stZmeRtlParaZme2.u32ZmeRatioHL = (stZmeRtlParaZme2.u32ZmeWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / stZmeRtlParaZme2.u32ZmeWOut * 2;
    }
    else
    {
        stZmeRtlParaZme2.u32ZmeRatioHL = stZmeRtlParaZme2.u32ZmeWIn * PQ_HAL_ALG_V_HZME_PRECISION / stZmeRtlParaZme2.u32ZmeWOut;
    }
    stZmeRtlParaZme2.u32ZmeRatioVL = stZmeRtlParaZme2.u32ZmeHIn * PQ_HAL_ALG_V_VZME_PRECISION / stZmeRtlParaZme2.u32ZmeHOut;

    /* calculate chroma zme ratio */
    u32Zme2CWIn  = ( stZmeDrvParaZme2.u8ZmeYCFmtIn  == 2 ) ? stZmeRtlParaZme2.u32ZmeWIn : stZmeRtlParaZme2.u32ZmeWIn / 2;
    u32Zme2CWOut = ( stZmeDrvParaZme2.u8ZmeYCFmtOut == 2 ) ? stZmeRtlParaZme2.u32ZmeWOut : stZmeRtlParaZme2.u32ZmeWOut / 2;
    u32Zme2CHIn  = ( stZmeDrvParaZme2.u8ZmeYCFmtIn  == 1 ) ? stZmeRtlParaZme2.u32ZmeHIn / 2 : stZmeRtlParaZme2.u32ZmeHIn;
    u32Zme2CHOut = ( stZmeDrvParaZme2.u8ZmeYCFmtOut == 1 ) ? stZmeRtlParaZme2.u32ZmeHOut / 2 : stZmeRtlParaZme2.u32ZmeHOut;

    /* when wide > 4096, overflow will occurs */
    if (u32Zme2CWIn >= 4096)
    {
        stZmeRtlParaZme2.u32ZmeRatioHC = (u32Zme2CWIn / 2 * PQ_HAL_ALG_V_HZME_PRECISION) / u32Zme2CWOut * 2;
    }
    else
    {
        stZmeRtlParaZme2.u32ZmeRatioHC = u32Zme2CWIn * PQ_HAL_ALG_V_HZME_PRECISION / u32Zme2CWOut;
    }
    stZmeRtlParaZme2.u32ZmeRatioVC = u32Zme2CHIn * PQ_HAL_ALG_V_VZME_PRECISION / u32Zme2CHOut;

    /* Input Progressive and Output Interlace */
    if (1 == stZmeDrvParaZme2.bZmeFrmFmtIn && 0 == stZmeDrvParaZme2.bZmeFrmFmtOut)
    {
        u32Zme2RatioVLReal = stZmeRtlParaZme2.u32ZmeRatioVL * 2;
        u32Zme2RatioVCReal = stZmeRtlParaZme2.u32ZmeRatioVC * 2;
    }
    else
    {
        u32Zme2RatioVLReal = stZmeRtlParaZme2.u32ZmeRatioVL;
        u32Zme2RatioVCReal = stZmeRtlParaZme2.u32ZmeRatioVC;
    }

    /* calculate luma zme offset */
    stZmeRtlParaZme2.s32ZmeOffsetHL = 0;

    /* Set Top filelds calc ZmeoffsetVL */
    stZmeRtlParaZme2.s32ZmeOffsetVL = pq_hal_GetVerticalScalerOffset(u32Zme2RatioVLReal, &stZmeDrvParaZme2);

    /* calculate chroma zme offset */
    s32Zme2VOffset = 0, s32Zme2HOffset = 0;
    if (1 == stZmeDrvParaZme2.u8ZmeYCFmtIn) /* 4:2:0 */
    {
        /* horizontal offset for cosited or interspersed format *//* fixed to false; interspersed format */
        s32Zme2HOffset = 0;

        /* vertical offset for processive or interlaced input format */
        if (stZmeDrvParaZme2.bZmeFrmFmtIn) /* processive input for zme */
        {
            s32Zme2VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
        }
        else /* interlaced input for zme */
        {
            if (stZmeDrvParaZme2.bZmeBFIn) /* bottom field input for zme */
            {
                s32Zme2VOffset = -((3 * PQ_HAL_ALG_V_VZME_PRECISION) >> 2) >> 1; /* -3072 >> 1 */
            }
            else /* top field input for zme */
            {
                s32Zme2VOffset = -(PQ_HAL_ALG_V_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
            }
        }
    }

    stZmeRtlParaZme2.s32ZmeOffsetHC = s32Zme2HOffset;
    stZmeRtlParaZme2.s32ZmeOffsetVC = s32Zme2VOffset + pq_hal_GetVerticalScalerOffset(u32Zme2RatioVCReal, &stZmeDrvParaZme2);

    stZmeRtlParaZme2.s32ZmeOffsetVLBtm = pq_hal_GetVerticalScalerOffset(u32Zme2RatioVLReal, &stZmeDrvParaZme2);
    stZmeRtlParaZme2.s32ZmeOffsetVCBtm = s32Zme2VOffset + pq_hal_GetVerticalScalerOffset(u32Zme2RatioVCReal, &stZmeDrvParaZme2);

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHL       = stZmeRtlParaZme2.s32ZmeOffsetHL       ;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHC       = stZmeRtlParaZme2.s32ZmeOffsetHC       ;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVL       = stZmeRtlParaZme2.s32ZmeOffsetVL    / 2;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVC       = stZmeRtlParaZme2.s32ZmeOffsetVC       ;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVLBtm    = stZmeRtlParaZme2.s32ZmeOffsetVLBtm / 2;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVCBtm    = stZmeRtlParaZme2.s32ZmeOffsetVCBtm    ;



    return;
}

static HI_VOID PQ_HAL_SetV0AllZmeOffset(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if (1 == pstZmeOut->u32ZmeNum)
    {
        pq_hal_SetV0OneZmeOffset(pstZmeIn, pstZmeOut);
    }
    else if (2 == pstZmeOut->u32ZmeNum)
    {
        pq_hal_SetV0TwoZmeOffset(pstZmeIn, pstZmeOut);
    }

    return;
}

static HI_VOID PQ_HAL_SetV1AllZmeOffset(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL       = 0;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC       = 0;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL       = 0;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC       = 0;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm    = 0;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm    = 0;

    return;
}

static HI_VOID pq_hal_SetWbcVpZmeOffset(HI_PQ_WBC_STRATEGY_IN_S *pstZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32 u32ZmeCWIn, u32ZmeCWOut, u32ZmeCHIn, u32ZmeCHOut;
    HI_S32 s32VOffset, s32HOffset;
    HI_U32 u32ZmeRatioVLReal, u32ZmeRatioVCReal;
    PQ_HAL_ALG_VZME_DRV_PARA_S  stZmeDrvPara;
    ALG_VZME_RTL_PARA_S         stZmeRtlPara;

    /* calculate luma real zme resolution of input and output */
    if (HI_PQ_PREZME_HOR_DISABLE == pstZmeOut->eHScalerMode)
    {
        stZmeRtlPara.u32ZmeWIn     = pstZmeOut->stZmeFmt.u32FrmInWidth;
    }
    else
    {
        stZmeRtlPara.u32ZmeWIn     = pstZmeOut->stZmeFmt.u32FrmInWidth >> pstZmeOut->eHScalerMode;
    }
    stZmeRtlPara.u32ZmeWOut    = pstZmeOut->stZmeFmt.u32FrmOutWidth;
    stZmeRtlPara.u32ZmeHIn     = pstZmeOut->stZmeFmt.u32FrmInHeight;
    stZmeRtlPara.u32ZmeHOut    = pstZmeOut->stZmeFmt.u32FrmOutHeight;

    stZmeDrvPara.u8ZmeYCFmtIn  = pstZmeOut->stZmeFmt.u32PixInFmt ;
    stZmeDrvPara.u8ZmeYCFmtOut = pstZmeOut->stZmeFmt.u32PixOutFmt;
    /* zme in & out frame or field */
    if (pstZmeOut->bReadFmtIn && pstZmeOut->bOpenP2I)
    {
        stZmeDrvPara.bZmeFrmFmtIn  = HI_FALSE;
    }
    else
    {
        stZmeDrvPara.bZmeFrmFmtIn  = pstZmeOut->bReadFmtIn;
    }
    stZmeDrvPara.bZmeFrmFmtOut = pstZmeOut->stZmeFmt.bOutFmt; /* Field : Top Or Bottom */

    stZmeDrvPara.bZmeBFIn      = pstZmeIn->stLayerInfo[1].bZmeBFIn; /* Field : Top Or Bottom */
    stZmeDrvPara.bZmeBFOut     = pstZmeIn->stLayerInfo[1].bZmeBFOut; /* Field : Top Or Bottom */

    //stZmeRtlPara.u32ZmeHIn  = ( stZmeDrvPara.bZmeFrmFmtIn  == 1 ) ? stZmeDrvPara.u32ZmeFrmHIn: stZmeDrvPara.u32ZmeFrmHIn/2;
    //stZmeRtlPara.u32ZmeHOut = ( stZmeDrvPara.bZmeFrmFmtOut == 1 ) ? stZmeDrvPara.u32ZmeFrmHOut: stZmeDrvPara.u32ZmeFrmHOut/2;

    /* when wide > 4096, overflow will occurs */
    if (stZmeRtlPara.u32ZmeWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHL = (stZmeRtlPara.u32ZmeWIn / 2 * PQ_HAL_ALG_WBCVP_HZME_PRECISION) / stZmeRtlPara.u32ZmeWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHL = stZmeRtlPara.u32ZmeWIn * PQ_HAL_ALG_WBCVP_HZME_PRECISION / stZmeRtlPara.u32ZmeWOut;
    }
    stZmeRtlPara.u32ZmeRatioVL = stZmeRtlPara.u32ZmeHIn * PQ_HAL_ALG_WBCVP_VZME_PRECISION / stZmeRtlPara.u32ZmeHOut;

    /* calculate chroma zme ratio */
    u32ZmeCWIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 2 ) ? stZmeRtlPara.u32ZmeWIn : stZmeRtlPara.u32ZmeWIn / 2;
    u32ZmeCWOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 2 ) ? stZmeRtlPara.u32ZmeWOut : stZmeRtlPara.u32ZmeWOut / 2;
    u32ZmeCHIn  = ( stZmeDrvPara.u8ZmeYCFmtIn  == 1 ) ? stZmeRtlPara.u32ZmeHIn / 2 : stZmeRtlPara.u32ZmeHIn;
    u32ZmeCHOut = ( stZmeDrvPara.u8ZmeYCFmtOut == 1 ) ? stZmeRtlPara.u32ZmeHOut / 2 : stZmeRtlPara.u32ZmeHOut;

    /* when wide > 4096, overflow will occurs */
    if (u32ZmeCWIn >= 4096)
    {
        stZmeRtlPara.u32ZmeRatioHC = (u32ZmeCWIn / 2 * PQ_HAL_ALG_WBCVP_HZME_PRECISION) / u32ZmeCWOut * 2;
    }
    else
    {
        stZmeRtlPara.u32ZmeRatioHC = u32ZmeCWIn * PQ_HAL_ALG_WBCVP_HZME_PRECISION / u32ZmeCWOut;
    }
    stZmeRtlPara.u32ZmeRatioVC = u32ZmeCHIn * PQ_HAL_ALG_WBCVP_VZME_PRECISION / u32ZmeCHOut;

    /* Input Progressive and Output Interlace */
    if (1 == stZmeDrvPara.bZmeFrmFmtIn && 0 == stZmeDrvPara.bZmeFrmFmtOut)
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL * 2;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC * 2;
    }
    else
    {
        u32ZmeRatioVLReal = stZmeRtlPara.u32ZmeRatioVL;
        u32ZmeRatioVCReal = stZmeRtlPara.u32ZmeRatioVC;
    }

    /* calculate luma zme offset */
    stZmeRtlPara.s32ZmeOffsetHL = 0;

    /* Set Top filelds calc ZmeoffsetVL */
    stZmeRtlPara.s32ZmeOffsetVL = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);

    /* calculate chroma zme offset */
    s32VOffset = 0, s32HOffset = 0;
    if (1 == stZmeDrvPara.u8ZmeYCFmtIn) /* 4:2:0 */
    {
        /* horizontal offset for cosited or interspersed format *//* fixed to false; interspersed format */
        s32HOffset = 0;

        /* vertical offset for processive or interlaced input format */
        if (stZmeDrvPara.bZmeFrmFmtIn) /* processive input for zme */
        {
            s32VOffset = -(PQ_HAL_ALG_WBCVP_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
        }
        else /* interlaced input for zme */
        {
            if (stZmeDrvPara.bZmeBFIn) /* bottom field input for zme */
            {
                s32VOffset = -((3 * PQ_HAL_ALG_WBCVP_VZME_PRECISION) >> 2) >> 1; /* -3072 >> 1 */
            }
            else /* top field input for zme */
            {
                s32VOffset = -(PQ_HAL_ALG_WBCVP_VZME_PRECISION >> 2) >> 1; /* -1024 >> 1 */
            }
        }
    }

    stZmeRtlPara.s32ZmeOffsetHC = s32HOffset;
    stZmeRtlPara.s32ZmeOffsetVC = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    stZmeRtlPara.s32ZmeOffsetVLBtm = pq_hal_GetVerticalScalerOffset(u32ZmeRatioVLReal, &stZmeDrvPara);
    stZmeRtlPara.s32ZmeOffsetVCBtm = s32VOffset + pq_hal_GetVerticalScalerOffset(u32ZmeRatioVCReal, &stZmeDrvPara);

    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetHL       = stZmeRtlPara.s32ZmeOffsetHL;
    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetHC       = stZmeRtlPara.s32ZmeOffsetHC;
    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetVL       = stZmeRtlPara.s32ZmeOffsetVL;
    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetVC       = stZmeRtlPara.s32ZmeOffsetVC;
    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetVLBtm    = stZmeRtlPara.s32ZmeOffsetVLBtm;
    pstZmeOut->stZmeFmt.stZmeOffset.s32ZmeOffsetVCBtm    = stZmeRtlPara.s32ZmeOffsetVCBtm;

    return;
}

static HI_VOID PQ_HAL_V0NormZme1ResoCalc(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32 u32WidthShift = (HI_U32)pstZmeOut->eHScalerMode + pstZmeOut->stPreZmeConfig.bPreZme;
    HI_U32 u32HeightShift = (HI_U32)pstZmeOut->eVScalerMode;

    if ((pstZmeIn->u32FrmWIn >= pstZmeIn->u32FrmWOut)
        && ((pstZmeIn->u32FrmWIn / (1 << u32WidthShift)) < pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
    {
        HI_ERR_PQ("PQ_HAL_V0NormZme1ResoCalc Width Amplify Set THD Error !\n");
    }
    else if ((pstZmeIn->u32FrmWIn < pstZmeIn->u32FrmWOut)
             && ((pstZmeIn->u32FrmWIn / (1 << u32WidthShift)) > pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth))
    {
        HI_ERR_PQ("PQ_HAL_V0NormZme1ResoCalc Width Reduce Set THD Error !\n");
    }

    if ((pstZmeIn->u32FrmHIn >= pstZmeIn->u32FrmHOut)
        && ((pstZmeIn->u32FrmHIn / (1 << u32HeightShift)) < pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
    {
        HI_ERR_PQ("PQ_HAL_V0NormZme1ResoCalc Heigth Amplify Set THD Error !\n");
    }
    else if ((pstZmeIn->u32FrmHIn < pstZmeIn->u32FrmHOut)
             && ((pstZmeIn->u32FrmHIn / (1 << u32HeightShift)) > pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
    {
        HI_ERR_PQ("PQ_HAL_V0NormZme1ResoCalc Width Reduce Set THD Error !\n");
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;

    if ((pstZmeIn->u32FmtIn == 3) || (pstZmeIn->u32FmtIn == 6) || (pstZmeIn->u32FmtIn == 7))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = 1;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = 0;
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */

    return;
}

static HI_VOID PQ_HAL_V0NormZme2ResoCalc(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if ((pstZmeIn->u32FrmWOut >= DHD0_OUT_RESOLUTION_W_THD) && (pstZmeIn->u32FrmHOut >= DHD0_OUT_RESOLUTION_H_THD)
        && (pstZmeIn->u32FrmHOut >= pstZmeIn->u32FrmHIn * V0_SCALER1_AMPLIFY_ENABLE_THD)
        && (pstZmeIn->u32FrmWOut >= pstZmeIn->u32FrmWIn * V0_SCALER1_AMPLIFY_ENABLE_THD))
        /* ˮƽ�ʹ�ֱ���Ŵ󳬹�2 ���ҽӿ���ʽΪ4K������zme2���̶�2���Ŵ� */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut / V0_SCALER1_RESO_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut / V0_SCALER1_RESO_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_SCALER1_REDUCE_ENABLE_THD * pstZmeIn->u32FrmWOut)
             && (pstZmeIn->u32FrmHIn >= V0_SCALER1_REDUCE_ENABLE_THD * pstZmeIn->u32FrmHOut))
        /* >= 4 : ˮƽ�ʹ�ֱ����С����4 ��������zme2���̶�2����С */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut * V0_SCALER1_RESO_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut * V0_SCALER1_RESO_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    }

    /* when zme2 in out reso do not the same , zme2 must be open */
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth)
        && (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight))
    {
        pstZmeOut->u32ZmeNum = 1; /* zme number */
    }
    else
    {
        pstZmeOut->u32ZmeNum = 2; /* zme number */
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = 0; /* zme input:  0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */

    return;
}


static HI_VOID PQ_HAL_V0HdcpZme2ResoCalc(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->stHDCPAttestFactor.u32IntermedHeight;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->stHDCPAttestFactor.u32IntermedWidth;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;

    /* when zme2 in out reso do not the same , zme2 must be open */
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth)
        && (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight))
    {
        pstZmeOut->u32ZmeNum = 1; /* zme number */
    }
    else
    {
        pstZmeOut->u32ZmeNum = 2; /* zme number */
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = 0; /* zme input:  0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */

    return;
}


static HI_VOID PQ_HAL_V0AllZmeResolutionRatioCalc(HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32 u32WidthShift = 0;
    HI_U32 u32HeightShift = (HI_U32)pstZmeOut->eVScalerMode;

    u32WidthShift = (HI_U32)pstZmeOut->eHScalerMode + pstZmeOut->stPreZmeConfig.bPreZme;

    /* w : ��ȵĴ��� */
    if ((pstZmeIn->u32FrmWOut >= DHD0_OUT_RESOLUTION_W_THD)
        && (pstZmeIn->u32FrmWOut >= pstZmeIn->u32FrmWIn * V0_SCALER1_AMPLIFY_ENABLE_THD))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeIn->u32FrmWOut / V0_SCALER1_AMPLIFY_ENABLE_THD;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
    }
    else if (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeIn->u32FrmWOut)
        /* (in <= out) or (> 1 ~ < 4); �Ŵ�С��4 ��������СС��2��*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_2_THD * pstZmeIn->u32FrmWOut)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeIn->u32FrmWOut))
        /* >= 2 ~ < 4; ��С2~4�� */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_4_THD * pstZmeIn->u32FrmWOut)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeIn->u32FrmWOut))
        /* >= 4 ~ < 8; ��С4~8��������zme2���̶�2����С */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_8_THD * pstZmeIn->u32FrmWOut)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeIn->u32FrmWOut))
        /* >= 8 ~ < 16; ��С8-16��������zme2���̶�2����С*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else if ((pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_16_THD * pstZmeIn->u32FrmWOut)
             && (pstZmeIn->u32FrmWIn < V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeIn->u32FrmWOut))
        /* >= 16 ~ < 32; ��С16-32��������zme2���̶�2����С*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else if (pstZmeIn->u32FrmWIn >= V0_PREZME_ENABLE_WIDTH_32_THD * pstZmeIn->u32FrmWOut)
        /* >= 32; ��С����32��������zme2���̶�2����С */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn / (1 << u32WidthShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    }

    /* h : �߶��ϵĴ��� */
    if ((pstZmeIn->u32FrmWOut >= DHD0_OUT_RESOLUTION_W_THD)
        && (pstZmeIn->u32FrmHOut >= DHD0_OUT_RESOLUTION_H_THD)
        && (pstZmeIn->u32FrmHOut >= pstZmeIn->u32FrmHIn * V0_SCALER1_AMPLIFY_ENABLE_THD))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeIn->u32FrmHOut / V0_SCALER1_AMPLIFY_ENABLE_THD;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    }
    else if (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeIn->u32FrmHOut)
        /* (in <= out) or (> 1 ~ < 2); �Ŵ�С��2��������СС��2��*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_3_THD * pstZmeIn->u32FrmHOut)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeIn->u32FrmHOut))
        /* >= 2 ~ < 4; ��С2~4�� */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_4_THD * pstZmeIn->u32FrmHOut)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeIn->u32FrmHOut))
        /* >= 4 ~ < 8; ��С4~8��������zme2���̶�2����С */
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else if ((pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_8_THD * pstZmeIn->u32FrmHOut)
             && (pstZmeIn->u32FrmHIn < V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeIn->u32FrmHOut))
        /* >= 8 ~ < 16; ��С8-16��������zme2���̶�2����С*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else if (pstZmeIn->u32FrmHIn >= V0_PREZME_ENABLE_HEIGHT_16_THD * pstZmeIn->u32FrmHOut)
        /* >= 16 ~ < 32; ��С16-32��������zme2���̶�2����С*/
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut * V0_SCALER1_AMPLIFY_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn / (1 << u32HeightShift);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }

    /* when zme2 in out reso do not the same , zme2 must be open */
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth)
        && (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight))
    {
        pstZmeOut->u32ZmeNum = 1; /* zme number */
    }
    else
    {
        pstZmeOut->u32ZmeNum = 2; /* zme number */
    }

    if (pstZmeIn->u32FmtIn == 3
        || pstZmeIn->u32FmtIn == 6
        || pstZmeIn->u32FmtIn == 7)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = 1;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = 0;
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = 0; /* zme input:  0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */

    return;
}

HI_VOID PQ_HAL_SetVdpZmeFirEn(HI_BOOL bZmeFirEn)
{
    g_bHalVdpZmeFirEn = bZmeFirEn;

    return;
}

HI_VOID PQ_HAL_SetVdpZmeMedEn(HI_BOOL bZmeModEn)
{
    g_bHalVdpZmeMedEn = bZmeModEn;

    return;
}

static HI_VOID PQ_HAL_SetV0OneZmeFirEnable(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = HI_TRUE;

    if (HI_TRUE == g_bHalVdpZmeFirEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = HI_FALSE ;
    }

    if (HI_TRUE == g_bHalVdpZmeMedEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_FALSE ;
    }

    return;
}

static HI_VOID PQ_HAL_SetV0TwoZmeFirEnable(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    /* zme2 */
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth) ||
        (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight) ||
        (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable = HI_TRUE;

        if (HI_TRUE == g_bHalVdpZmeFirEn)
        {
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_TRUE;
        }
        else
        {
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_FALSE;
        }
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable = HI_FALSE;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_FALSE;
    }

    if (HI_TRUE == g_bHalVdpZmeMedEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH  = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV  = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH  = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV  = HI_FALSE ;
    }

    return;
}

static HI_VOID PQ_HAL_V0AllZmeModeConfig(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if (1 == pstZmeOut->u32ZmeNum)
    {
        PQ_HAL_SetV0OneZmeFirEnable(pstZmeOut);
    }
    else if (2 == pstZmeOut->u32ZmeNum)
    {
        PQ_HAL_SetV0OneZmeFirEnable(pstZmeOut);
        PQ_HAL_SetV0TwoZmeFirEnable(pstZmeOut);
    }

    return;
}

static HI_PQ_WBC_VP_POINT_SEL_E PQ_HAL_WbcVpWriteBackPointConfig(HI_PQ_WBC_STRATEGY_IN_S *pstZmeIn)
{
    HI_PQ_WBC_VP_POINT_SEL_E   enVpPoint      = HI_PQ_WBC_VP_POINT_V0;

    PQ_HAL_DHD_COLORSPACE_E enHDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    PQ_HAL_DHD_COLORSPACE_E enSDOutColorSpace = PQ_HAL_DHD_OUT_YUV;

    PQ_HAL_ColorSpaceTrans(&enHDOutColorSpace, &enSDOutColorSpace);

    /***
    ��д��ѡ�����:
    (1) ��ָ�곡��: ��д����V0;
    (2) �ര�����: ѡ��VP��CSC֮��Ļ�д��;
    (3) ˮӡ����:   ѡ��VP��CSC֮��Ļ�д��;
    (4) ë��������: ѡ��VP��CSC֮��Ļ�д��;
    (5) �������С���:
        ��(Դ->SD��ʾ����С����������С10��)> (Դ->HD��ʾ����С����������С6��), ��ѡ��VP��CSC֮��Ļ�д��;
          (SD�����������С, ��������SD�����С��ͼ������) -- �ȼ��ڸ���ͨ·����С����;
    (6) Else, ѡ��V0 Scaler0֮ǰ�Ļ�д��;
    ***/
    if (HI_TRUE == sg_bVdpZmeDefault) /* rwzb */
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }
    else if (PQ_HAL_DHD_OUT_RGB == enHDOutColorSpace) /* Add 20160325 sdk when HD RGB out, write back from V0 */
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }
    else if (HI_TRUE == pstZmeIn->bForceWbcPoint2Vp) /* (1)multi-window, (2)watermark, (3)forstglass; force to vp0 */
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_VP;
    }
    else if ((pstZmeIn->stLayerInfo[0].u32FrmWIn == pstZmeIn->stLayerInfo[1].u32FrmWOut)
             && (pstZmeIn->stLayerInfo[0].u32FrmHIn == pstZmeIn->stLayerInfo[1].u32FrmHOut)) /* Interlace output and source resolution == out resolution */
    {
        /* Add 20160325 sdk ��ָ�곡��, ����Դ��CVBS�ķֱ���һ��ҲҪ��V0��д
           e.g.: 576i --> 576p --> 576i(Hdmi), 576i(Cvbs); ��д����V0;
                 480i --> 480p --> 480i(Hdmi), 480i(Cvbs); ��д����V0; */
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }
    else if ((pstZmeIn->stLayerInfo[0].u32FrmHOut < pstZmeIn->stLayerInfo[0].u32FrmHIn)
             && (pstZmeIn->stLayerInfo[0].u32FrmHOut > pstZmeIn->stLayerInfo[1].u32FrmHOut))
    {
        /* example: 720x576-->600x480(HD) ��Ҫ��V0��д;
           Judgement condition is height of V0, not the height of VP */
        enVpPoint = HI_PQ_WBC_VP_POINT_VP;
    }
    else
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }

    return enVpPoint;
}

static HI_BOOL PQ_HAL_WbcVpZmeOutFrameOrField(HI_PQ_WBC_STRATEGY_IN_S *pstZmeIn)
{
    HI_BOOL bOutFmt = 0;
    /***
      WBC_VP��д���ݵĸ�ʽ���������Ǹ���HD�ӿں�SD�ӿ�֮���Ƿ���Ҫ֡��ת����������д��ʽ��
      (1) ���HD֡��<SD֡��(��: HD���1080P24��SD���NTSC��ʽ), ��WBC_VP��д֡����;
          (�Ա�֤SD���ͼ�񲻻���ֻ��˻����¶���)
      (2) Else, WBC_VP��д������. ���������Ҫע��, HD���60hz, ��SD���NTSC(59.94hz)�����,
          HDÿ��16s��SD���ſ�һ��, SD��������ʱҪ��֤һ�ζ�������, �������ּ��Է�ת������Ӷ�����ͼ�����¶���;

      ע��: HD-4KP30, SD-NTSC; HD-4KP25, SD-PAL; HD-1080P24, SD-NTSC; ��ҪV3��֡������, Vdp�������ظ�����ӿ����;
      ***/
    if (HI_TRUE == pstZmeIn->bForceWbcFieldMode) /* ǿ�ƻ�д�� */
    {
        bOutFmt = 0; /* Frame format for zme output: 0-field; 1-frame */
    }
    else if (g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].u32RefreshRate !=  g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].u32RefreshRate)
    {
        bOutFmt = 1;
    }
    else
    {
        bOutFmt = 0;
    }

    return bOutFmt;
}

static HI_PQ_ZME_BIND_POSITION_E PQ_HAL_WbcVpZmePosition(HI_VOID)
{
    if (HI_FALSE == g_stPqStatus.bIsogenyMode) /* ��ͬԴ */
    {
        return HI_PQ_ZME_BIND_V3;
    }

    return HI_PQ_ZME_BIND_WBC;
}

static HI_PQ_PREZME_HOR_MUL_E PQ_HAL_WbcVpHScalerConfig(HI_U32 u32InWidth)
{
    /* 98CV200 WBC HScaler�Ŀ������������ܵ�����, ��������ڵ���4Kʱ��; ����оƬ�޷���֤�ж�Hscaler������������һ����;
       �����в��漰Hscaler��ʵ��; PQ��Hsacaler + Scaler(WBC)����һ��������Scaler;
       Hsacler�Ĳ����ɵײ�cbb�Լ���, ����ratio���zme�Ŀ��, ͬ����cbb����;
       */
    if (u32InWidth >= DHD0_OUT_RESOLUTION_W_THD)
    {
        return HI_PQ_PREZME_HOR_2X; /* �̶�2��1 */
    }

    return HI_PQ_PREZME_HOR_DISABLE;
}

static HI_BOOL PQ_HAL_WbcVpZmeP2IConfig(HI_BOOL bWbcAPointProgressive, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32  u32InWidth    = 0;
    HI_U32  u32InHeight   = 0;
    HI_U32  u32OutWidth   = 0;
    HI_U32  u32OutHeight  = 0;
    HI_BOOL bWbcOutFormat = HI_FALSE; /* HI_FALSE: Interlace */
    HI_BOOL bOpenP2I      = HI_FALSE;

    u32InHeight   = pstZmeOut->stZmeFmt.u32FrmInHeight;
    u32InWidth    = pstZmeOut->stZmeFmt.u32FrmInWidth;
    u32OutWidth   = pstZmeOut->stZmeFmt.u32FrmOutWidth;
    u32OutHeight  = pstZmeOut->stZmeFmt.u32FrmOutHeight;
    bWbcOutFormat = pstZmeOut->stZmeFmt.bOutFmt;

    /***
       WBC_VP P2I�Ŀ�������: (�ο�3798cv200 �㷨����ͼ)
       (1) ���B�����Progressive, ��P2I�ر�;
       (2) ���B�����Interlace, ����������;
           A) ���A������Interlace, ��P2I�ر�;
           B) ���A������Progressive, ���ַ��������:
              a) ���Դresolution==Ŀ��resolution, ��P2I��������Ҫƥ�䳡����;
              b) �����ֱ���ű�<THD'(��1/4, ����ֵ��Ҫ���Ժ���ȷ��), ��P2I����(�൱��������С��Ϊ�������������С��ͼ��Ч��);
              c) Else, P2I�ر�
      ***/
    /* ��ͬԴģʽ: ZME����V3��, do not care B Point is Progressive or not */
    if (HI_FALSE == g_stPqStatus.bIsogenyMode)
    {
        return HI_FALSE;
    }
    /* ����ͬԴģʽ: ZME����WBC��, ��Ϊ�������������Interlace, ��B�����Ϊ Interlace */
    if (HI_TRUE == bWbcOutFormat) /* WBC�����Progressive, ��B��Progressive */
    {
        bOpenP2I = HI_FALSE;
    }
    else if (HI_FALSE == bWbcAPointProgressive) /* B�����Interlace, A������Interlace */
    {
        bOpenP2I = HI_FALSE;
    }
    else if (HI_TRUE == bWbcAPointProgressive)  /* B�����Interlace, A������Progressive */
    {
        /* 1. ��������: ��ֻ��4K��Hscalerʱ, �ŻῪ��,��˲���Ҫ�����µ��ж������г���Hscaler.
           2. cvbs������̶���pal��ntsc, ��������������ֻ��: 576p --> 576i; 480p --> 480i;    */
        if ((u32OutWidth == u32InWidth) && (u32OutHeight == u32InHeight))
        {
            /* e.g.: 576i --> 576p --> 576i(Hdmi), 576i(Cvbs); ��д����V0��, V0����, ��A��ΪInterlace;   ������������;
                     576i --> 576p --> 720p(Hdmi), 576i(Cvbs); ��д����V0��, V0��֡, ��A��ΪProgressive; ����������;  */
            bOpenP2I = HI_TRUE;
        }
        else if (u32InHeight > WBC_HSCALER_THD * u32OutHeight)
        {
            bOpenP2I = HI_TRUE;
        }
        else
        {
            bOpenP2I = HI_FALSE;
        }
    }

    return bOpenP2I;
}

static HI_BOOL PQ_HAL_WbcVpZmeWriteBackPointIsProgressive(HI_VOID)
{
    if (ZME_WBC_POINT_V0 == sg_enWbcPointSel)
    {
        return sg_bV0ReadFmtIn; /* V0 �������ݸ����� */
    }

    return g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive;
}

static HI_VOID PQ_HAL_WbcVpZmeResolutionRatioCalc(HI_PQ_WBC_STRATEGY_IN_S *pstZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32  bWbcAPointPixFmt = 0; /* A point video format: 0-422; 1-420; 2-444 */
    HI_U32  u32InWidth       = 0;
    HI_U32  u32InHeight      = 0;
    HI_U32  u32OutWidth      = 0;
    HI_U32  u32OutHeight     = 0;

    if (ZME_WBC_POINT_V0 == sg_enWbcPointSel)
    {
        u32InWidth   = pstZmeIn->stLayerInfo[0].u32FrmWIn / (1 << (HI_U32)sg_enV0PreHScaler);
        u32InHeight  = pstZmeIn->stLayerInfo[0].u32FrmHIn / (1 << (HI_U32)sg_enV0PreVScaler);
        u32OutWidth  = pstZmeIn->stLayerInfo[1].u32FrmWOut; /* V3 FrmWOut */
        u32OutHeight = pstZmeIn->stLayerInfo[1].u32FrmHOut; /* V3 FrmHOut */

        if (2 == pstZmeIn->stLayerInfo[0].u32FmtIn) /* pix format: 0-422; 1-420; 2-444 */
        {
            bWbcAPointPixFmt = 0; /* pix format: 0-422; 1-420; 2-444 */
        }
        else
        {
            bWbcAPointPixFmt = pstZmeIn->stLayerInfo[0].u32FmtIn; /* V0 �������ݸ�ʽ */
        }
    }
    else if (ZME_WBC_POINT_VP == sg_enWbcPointSel)
    {
        /* ������VP��, ������ŵĿ��Ӧ���ǽӿڵĿ��, ���ǲ�Ŀ��; ����PIP��Ԥ���޷���дȫ��;
           Remark: ���ڿ�ߵ���V0��ʵ�ʿ��, ��ʽ��ߵ���VP�ϵĿ�� */
        u32InWidth       = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Width;
        u32InHeight      = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Height;
        u32OutWidth      = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].stFmtRect.s32Width;
        u32OutHeight     = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].stFmtRect.s32Height;
        bWbcAPointPixFmt = 0; /* pix format: 0-422; 1-420; 2-444 */
    }

    /* Scaler Info Calc */
    pstZmeOut->stZmeFmt.u32FrmInHeight  = u32InHeight;
    pstZmeOut->stZmeFmt.u32FrmInWidth   = u32InWidth; /* can not divide 2 */
    pstZmeOut->stZmeFmt.u32FrmOutWidth  = u32OutWidth;
    pstZmeOut->stZmeFmt.u32FrmOutHeight = u32OutHeight;

    pstZmeOut->stZmeFmt.u32PixInFmt     = bWbcAPointPixFmt;
    pstZmeOut->stZmeFmt.u32PixOutFmt    = 0; /* 0-422; 1-420; 2-444; write back must be 422 */

    return;
}


static HI_VOID PQ_HAL_WbcVpZmeModeConfig(HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    /* config zme mode; when frame resolution does not have change, can not open fir mode; e.g: (480i-->480i) or (576i --> 576i); other must open fir mode; */
    pstZmeOut->stZmeFmt.bZmeFirHL = (pstZmeOut->stZmeFmt.u32FrmOutWidth  == pstZmeOut->stZmeFmt.u32FrmInWidth)  ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVL = (pstZmeOut->stZmeFmt.u32FrmOutHeight == pstZmeOut->stZmeFmt.u32FrmInHeight) ? HI_FALSE : HI_TRUE;
    /* in format may be 420(write back from v0) or must be 422(write back from vp0), out format must be 422; when 420 -> 422; vertical need up-sampling, but horizontal does not need */
    pstZmeOut->stZmeFmt.bZmeFirHC = (HI_FALSE == pstZmeOut->stZmeFmt.bZmeFirHL) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVC = (HI_FALSE == pstZmeOut->stZmeFmt.bZmeFirVL) ? ((pstZmeOut->stZmeFmt.u32PixOutFmt == pstZmeOut->stZmeFmt.u32PixInFmt) ? HI_FALSE : HI_TRUE) : HI_TRUE;

    pstZmeOut->stZmeFmt.bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal: 0-off; 1-on*/
    pstZmeOut->stZmeFmt.bZmeMedV  = HI_FALSE;

    if ((HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirHL) || (HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirHC))
    {
        pstZmeOut->stZmeFmt.bZmeHorEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt.bZmeHorEnable = HI_FALSE;
    }

    if ((HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirVL) || (HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirVC))
    {
        pstZmeOut->stZmeFmt.bZmeVerEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt.bZmeVerEnable = HI_FALSE;
    }

    return;
}

static HI_S32 PQ_HAL_GetV0ZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_HAL_FROST_CFG_S stFrostCfg;

    PQ_CHECK_NULL_PTR(pstZmeOut);

    if ((HI_TRUE == pstZmeIn->stHDCPAttestFactor.bHDCPScene) || (HI_TRUE == sg_bProcHDCPEn))
    {
        sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_CLOSE;
        PQ_HAL_V0HdcpZme2ResoCalc(pstZmeIn, pstZmeOut);

        PQ_HAL_V0HdcpHPreZmeConfig(pstZmeIn, pstZmeOut);

        PQ_HAL_V0HdcpVPreZmeConfig(pstZmeIn, pstZmeOut);

        PQ_HAL_V0NormZme1ResoCalc(pstZmeIn, pstZmeOut);
    }
    else
    {
        /* ���������С���㡢P2I ���� */
        if ((pstZmeIn->eFrostLevel != HI_PQ_FROST_LEVEL_CLOSE) || (sg_enProcFrostLevel != HI_PQ_FROST_LEVEL_CLOSE))
        {
            PQ_HAL_FrostCfgTrans(pstZmeIn, &stFrostCfg);
            PQ_HAL_SetFrostGlassLevel(stFrostCfg,
                                      &(pstZmeOut->bReadFmtIn),
                                      &(pstZmeOut->eHScalerMode),
                                      &(pstZmeOut->eVScalerMode),
                                      &(pstZmeOut->stPreZmeConfig),
                                      &(pstZmeOut->bOpenP2I));
            PQ_HAL_V0AllZmeResolutionRatioCalc(pstZmeIn, pstZmeOut);

        }
        else
        {
            sg_enFrostGlassLevel = PQ_HAL_FROST_LEVEL_CLOSE;
            PQ_HAL_V0NormZme2ResoCalc(pstZmeIn, pstZmeOut);

            PQ_HAL_V0NormHPreZmeConfig(pstZmeIn, pstZmeOut);

            PQ_HAL_V0NormVPreZmeConfig(pstZmeIn, pstZmeOut);

            PQ_HAL_V0NormZme1ResoCalc(pstZmeIn, pstZmeOut);
        }
    }

    sg_bV0ReadFmtIn   = pstZmeOut->bReadFmtIn;
    sg_enV0PreHScaler = pstZmeOut->eHScalerMode;
    sg_enV0PreVScaler = pstZmeOut->eVScalerMode;
    sg_bHPZmeEnable   = pstZmeOut->stPreZmeConfig.bPreZme;

    PQ_HAL_V0AllZmeModeConfig(pstZmeOut);
    PQ_HAL_SetV0AllZmeOffset(pstZmeIn, pstZmeOut);
    PQ_HAL_SetSharpConfig(pstZmeIn, pstZmeOut);
    PQ_HAL_VpZmeDefaultConfig(pstZmeOut);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetV1ZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_CHECK_NULL_PTR(pstZmeOut);

    pstZmeOut->eHScalerMode = HI_PQ_PREZME_HOR_DISABLE;
    pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    pstZmeOut->bOpenP2I     = HI_FALSE; /* read frame */

    if (HI_TRUE == g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive)
    {
        pstZmeOut->bReadFmtIn = HI_TRUE;  /* read frame */
    }
    else
    {
        pstZmeOut->bReadFmtIn = HI_FALSE; /* read field */
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = (pstZmeIn->u32FrmWOut == pstZmeIn->u32FrmWIn) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = (pstZmeIn->u32FrmHOut == pstZmeIn->u32FrmHIn) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = (HI_FALSE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = (HI_FALSE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL) ? \
            ((pstZmeIn->u32FmtIn == 0) ? HI_FALSE : HI_TRUE) : HI_TRUE;

    if ((HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL) || (HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = HI_FALSE;
    }

    if ((HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL) || (HI_TRUE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = HI_FALSE;
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal luma: 0-off; 1-on*/
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_FALSE;

    pstZmeOut->u32ZmeNum = 1; /* chroma up-sampling */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = pstZmeIn->u32FrmWIn;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = pstZmeIn->u32FrmHIn;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt     = pstZmeIn->u32FmtIn;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt    = 0;

    PQ_HAL_SetV1AllZmeOffset(pstZmeIn, pstZmeOut);

    PQ_HAL_VpZmeDefaultConfig(pstZmeOut);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetWbcVpZmeStrategy (HI_PQ_WBC_STRATEGY_IN_S *pstZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_BOOL bWbcAPointProgressive = HI_TRUE; /* Wbc A point frame format: 0-field; 1-frame */

    PQ_CHECK_NULL_PTR(pstZmeOut);

    pstZmeOut->enVpPoint = PQ_HAL_WbcVpWriteBackPointConfig(pstZmeIn);
    sg_enWbcPointSel     = (ZME_WBC_POINT_SEL_E)pstZmeOut->enVpPoint;

    /* ����WBC�������������ߡ�֡/�� */
    PQ_HAL_WbcVpZmeResolutionRatioCalc(pstZmeIn, pstZmeOut);

    bWbcAPointProgressive    = PQ_HAL_WbcVpZmeWriteBackPointIsProgressive();
    pstZmeOut->bReadFmtIn    = bWbcAPointProgressive; /* Frame format for zme Intput: 0-field; 1-frame */
    pstZmeOut->stZmeFmt.bOutFmt = PQ_HAL_WbcVpZmeOutFrameOrField(pstZmeIn);
    pstZmeOut->eZmePosition  = PQ_HAL_WbcVpZmePosition();

    pstZmeOut->bOpenP2I      = PQ_HAL_WbcVpZmeP2IConfig(bWbcAPointProgressive, pstZmeOut);
    pstZmeOut->eHScalerMode  = PQ_HAL_WbcVpHScalerConfig(pstZmeOut->stZmeFmt.u32FrmInWidth);

    /* e.g.: 576i -> 576p -> 576i(Hdmi), 576i(Cvbs); Write back from V0, V0 read field, A point is interlace */
    pstZmeOut->stZmeFmt.bInFmt  = (HI_TRUE == pstZmeOut->bOpenP2I) ? 0 : bWbcAPointProgressive;

    PQ_HAL_WbcVpZmeModeConfig(pstZmeOut);

    pq_hal_SetWbcVpZmeOffset(pstZmeIn, pstZmeOut);

    PQ_HAL_WbcVpZmeDefaultConfig(pstZmeOut);

    pqprint(PQ_PRN_ZME, "V0 WIn:%d, HIn:%d, WOut:%d, HOut:%d\t", pstZmeIn->stLayerInfo[0].u32FrmWIn, pstZmeIn->stLayerInfo[0].u32FrmHIn,
            pstZmeIn->stLayerInfo[0].u32FrmWOut, pstZmeIn->stLayerInfo[0].u32FrmHOut);
    pqprint(PQ_PRN_ZME, "V3 WIn:%d, HIn:%d, WOut:%d, HOut:%d\n", pstZmeIn->stLayerInfo[1].u32FrmWIn, pstZmeIn->stLayerInfo[1].u32FrmHIn,
            pstZmeIn->stLayerInfo[1].u32FrmWOut, pstZmeIn->stLayerInfo[1].u32FrmHOut);
    pqprint(PQ_PRN_ZME, "OUT WIn:%d, HIn:%d, WOut:%d, HOut:%d\n", pstZmeOut->stZmeFmt.u32FrmInWidth, pstZmeOut->stZmeFmt.u32FrmInHeight,
            pstZmeOut->stZmeFmt.u32FrmOutWidth, pstZmeOut->stZmeFmt.u32FrmOutHeight);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetWbcDhdZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S *pstZmeIn, HI_PQ_WBC_DHD0_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_CHECK_NULL_PTR(pstZmeOut);

    pstZmeOut->eHScalerMode   = HI_PQ_PREZME_HOR_2X; /* �����߼����ܵ�����, Hscaler�̶�����1/2 */
    pstZmeOut->bInWbcVpZmeFmt = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive; /* ͼ������Ƶ����֮���д */

    pstZmeOut->stZmeFmt.u32FrmInHeight  = pstZmeIn->u32FrmHIn;
    pstZmeOut->stZmeFmt.u32FrmInWidth   = pstZmeIn->u32FrmWIn; /* can not divide 2 */
    pstZmeOut->stZmeFmt.u32FrmOutWidth  = pstZmeIn->u32FrmWOut;
    pstZmeOut->stZmeFmt.u32FrmOutHeight = pstZmeIn->u32FrmHOut;
    /* Layer strategry: input 444, output 420 */
    pstZmeOut->stZmeFmt.u32PixInFmt     = 2; /* 0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt.u32PixOutFmt    = 1; /* 0-422; 1-420; 2-444 */

    pstZmeOut->stZmeFmt.bZmeFirHL = HI_TRUE; /* 0-copy mode; 1-FIR filter mode*/
    pstZmeOut->stZmeFmt.bZmeFirVL = HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirHC = HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVC = HI_TRUE;

    pstZmeOut->stZmeFmt.bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal luma: 0-off; 1-on*/
    pstZmeOut->stZmeFmt.bZmeMedV  = HI_FALSE;

    if ((HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirHL) || (HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirHC))
    {
        pstZmeOut->stZmeFmt.bZmeHorEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt.bZmeHorEnable = HI_FALSE;
    }

    if ((HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirVL) || (HI_TRUE == pstZmeOut->stZmeFmt.bZmeFirVC))
    {
        pstZmeOut->stZmeFmt.bZmeVerEnable = HI_TRUE;
    }
    else
    {
        pstZmeOut->stZmeFmt.bZmeVerEnable = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetVdpZmeStrategy (VDP_ZME_LAYER_E enLayerId,
                                 HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn,
                                 HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (VDP_ZME_LAYER_V0 == enLayerId)
    {
        s32Ret = PQ_HAL_GetV0ZmeStrategy(&pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyLayerId));
    }
    else if (VDP_ZME_LAYER_V1 == enLayerId)
    {
        s32Ret = PQ_HAL_GetV1ZmeStrategy(&pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyLayerId));
    }
    else if (VDP_ZME_LAYER_WBC0 == enLayerId)
    {
        s32Ret = PQ_HAL_GetWbcVpZmeStrategy(&pstZmeIn->stWbcStrategy, &(pstZmeOut->stStrategyWbcVp));
    }
    else if (VDP_ZME_LAYER_WBC_DHD == enLayerId)
    {
        s32Ret = PQ_HAL_GetWbcDhdZmeStrategy(&pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyWbcDhd));
    }
    else
    {
        HI_ERR_PQ("LayerId:%d, unsupport zme strategy!\n", enLayerId);
    }

    return s32Ret;
}


HI_S32 PQ_HAL_SetProcFrostLevel(HI_PQ_FROST_LEVEL_E enFrostLevel)
{
    sg_enProcFrostLevel = enFrostLevel;
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetHDCPEn(HI_BOOL bOnOff)
{
    sg_bProcHDCPEn = bOnOff;
    return HI_SUCCESS;
}


