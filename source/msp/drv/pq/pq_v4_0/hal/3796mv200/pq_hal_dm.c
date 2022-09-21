/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_dering.c
  Version        : Initial Draft
  Author         : sdk
  Created       : 2017/02/14
  Description   :

******************************************************************************/

#include <linux/string.h>   /* memcpy() */
#include "pq_hal_dm.h"
#include "pq_hal_comm.h"
#include "drv_pq_comm.h"

HI_S32 PQ_HAL_SetRegDmDirStrGainLut(HI_U32 u32HandleNo, const HI_U16 u16SrcLut[])
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p0  = u16SrcLut[0];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p1  = u16SrcLut[1];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p2  = u16SrcLut[2];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p3  = u16SrcLut[3];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p4  = u16SrcLut[4];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p5  = u16SrcLut[5];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p6  = u16SrcLut[6];
    pstVpssVirReg->VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p7  = u16SrcLut[7];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetRegDmSwWhtLut(HI_U32 u32HandleNo, const HI_U16 u16SrcLut[])
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DM_LUT0.bits.dm_sw_wht_lut_p0  = u16SrcLut[0];
    pstVpssVirReg->VPSS_DM_LUT0.bits.dm_sw_wht_lut_p1  = u16SrcLut[1];
    pstVpssVirReg->VPSS_DM_LUT0.bits.dm_sw_wht_lut_p2  = u16SrcLut[2];
    pstVpssVirReg->VPSS_DM_LUT0.bits.dm_sw_wht_lut_p3  = u16SrcLut[3];

    pstVpssVirReg->VPSS_DM_LUT1.bits.dm_sw_wht_lut_p4  = u16SrcLut[4];

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetRegDmDirStrLut(HI_U32 u32HandleNo, const HI_U16 u16SrcLut[])
{
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p0   = u16SrcLut[0];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p1   = u16SrcLut[1];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p2   = u16SrcLut[2];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p3   = u16SrcLut[3];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p4   = u16SrcLut[4];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p5   = u16SrcLut[5];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p6   = u16SrcLut[6];
    pstVpssVirReg->VPSS_DM_LUT3.bits.dm_dir_str_lut_p7   = u16SrcLut[7];

    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p8   = u16SrcLut[8];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p9   = u16SrcLut[9];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p10  = u16SrcLut[10];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p11  = u16SrcLut[11];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p12  = u16SrcLut[12];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p13  = u16SrcLut[13];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p14  = u16SrcLut[14];
    pstVpssVirReg->VPSS_DM_LUT4.bits.dm_dir_str_lut_p15  = u16SrcLut[15];


    return HI_SUCCESS;
}

HI_S32 PQ_HAL_EnableDM(HI_U32 u32Data, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32Data);
    PQ_CHECK_NULL_PTR(pstVpssReg);
    pstVpssReg->VPSS_SNR_CTRL.bits.dm_en = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_EnableDMDemo(HI_U32 u32Data, HI_BOOL bOnOff)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32Data);
    PQ_CHECK_NULL_PTR(pstVpssReg);
    pstVpssReg->VPSS_SNR_CTRL.bits.dbm_demo_en = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetDMApiReg(HI_U32 u32HandleNo, DM_API_REG_S *pstDmApiReg)
{
    HI_U32 i = 0;
    VPSS_REG_S *pstVpssVirReg = HI_NULL;

    PQ_CHECK_NULL_PTR(pstDmApiReg);
    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR(pstVpssVirReg);

    pstVpssVirReg->VPSS_DM_DIR.bits.dm_ctrst_thresh         = pstDmApiReg->u8CtrstThresh;

    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_init_val_step       = pstDmApiReg->InitValStep;
    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_mmf_set             = pstDmApiReg->MMFSet;
    pstVpssVirReg->VPSS_DM_LUT1.bits.dm_limit_t_10          = pstDmApiReg->LimitT10bit;
    pstVpssVirReg->VPSS_DM_LUT1.bits.dm_limit_t             = pstDmApiReg->LimitT;

    pstVpssVirReg->VPSS_DM_DIRC.bits.dm_mmf_limit_en        = pstDmApiReg->MMFlimitEn;

    pstVpssVirReg->VPSS_DM_DIRO.bits.dm_csw_trsnt_st_10     = pstDmApiReg->cSWTrsntST;

    pstVpssVirReg->VPSS_DM_LSW.bits.dm_lsw_ratio            = pstDmApiReg->LSWRatio;
    pstVpssVirReg->VPSS_DM_LSW.bits.dm_csw_trsnt_st         = pstDmApiReg->cSWTrsntST;
    pstVpssVirReg->VPSS_DM_LSW.bits.dm_lw_ctrst_t_10        = pstDmApiReg->LWCtrstT10bit;
    pstVpssVirReg->VPSS_DM_LSW.bits.dm_lw_ctrst_t           = pstDmApiReg->LWCtrstT;

    pstVpssVirReg->VPSS_DM_MMFLR.bits.dm_csw_trsnt_lt       = pstDmApiReg->cSWTrsntLT;
    pstVpssVirReg->VPSS_DM_MMFLR.bits.dm_mmf_lr_10          = pstDmApiReg->MMFLR10bit;
    pstVpssVirReg->VPSS_DM_MMFLR.bits.dm_mmf_lr             = pstDmApiReg->MMFLR;

    pstVpssVirReg->VPSS_DM_MMFSR.bits.dm_csw_trsnt_lt_10    = pstDmApiReg->cSWTrsntLT10bit;
    pstVpssVirReg->VPSS_DM_MMFSR.bits.dm_mmf_sr_10          = pstDmApiReg->MMFSR10bit;
    pstVpssVirReg->VPSS_DM_MMFSR.bits.dm_mmf_sr             = pstDmApiReg->MMFSR;

    pstVpssVirReg->VPSS_DM_THR0.bits.dm_dir_blend_str       = pstDmApiReg->DirBlendStr;
    pstVpssVirReg->VPSS_DM_THR0.bits.dm_lim_res_blend_str2  = pstDmApiReg->LimResBlendStr2;
    pstVpssVirReg->VPSS_DM_THR0.bits.dm_lim_res_blend_str1  = pstDmApiReg->LimResBlendStr1;
    pstVpssVirReg->VPSS_DM_THR0.bits.dm_limit_lsw_ratio     = pstDmApiReg->LimitLSWRatio;

    pstVpssVirReg->VPSS_DM_LUT11.bits.dm_trans_band_lut_p30 = pstDmApiReg->TransBand[30];

    /* VPSS_DM_LUT5-> VPSS_DM_LUT10 cfg set */
    for (i = 0; i < 6; i++)
    {
        *(&(pstVpssVirReg->VPSS_DM_LUT5.u32) + i * 1 ) =
                (((HI_U32)(pstDmApiReg->TransBand[i * 5 + 0]) << 0) & 0x3f) |
                (((HI_U32)(pstDmApiReg->TransBand[i * 5 + 1]) << 6) & 0xFC0) |
                (((HI_U32)(pstDmApiReg->TransBand[i * 5 + 2]) << 12) & 0x3F000) |
                (((HI_U32)(pstDmApiReg->TransBand[i * 5 + 3]) << 18) & 0xFC0000) |
                (((HI_U32)(pstDmApiReg->TransBand[i * 5 + 4]) << 24) & 0x3F000000) ;
    }

    pstVpssVirReg->VPSS_DM_LUT17.bits.dm_ang_ctrst_pun_lutp25 = pstDmApiReg->AngCtrstPun[25];
    pstVpssVirReg->VPSS_DM_LUT17.bits.dm_ang_ctrst_pun_lutp24 = pstDmApiReg->AngCtrstPun[24];
    /* VPSS_DM_LUT13-> VPSS_DM_LUT16 cfg set */
    for (i = 0; i < 4; i++)
    {
        *((&(pstVpssVirReg->VPSS_DM_LUT13.u32) + i * 1 )) =
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 0]) << 0) & 0x1f) |
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 1]) << 5) & 0x3e0) |
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 2]) << 10) & 0x7c00) |
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 3]) << 15) & 0xF8000) |
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 4]) << 20) & 0x1F00000) |
            (((HI_U32)(pstDmApiReg->AngCtrstPun[i * 6 + 5]) << 25) & 0x3E000000) |
            ((0 << 30) & 0xC0000000) ;
    }

    pstVpssVirReg->VPSS_DM_TRANS_WID.bits.dm_trans_wid_10 = pstDmApiReg->TransWid10bit;
    pstVpssVirReg->VPSS_DM_TRANS_WID.bits.dm_trans_wid    = pstDmApiReg->TransWid;

    pstVpssVirReg->VPSS_DM_EDGE.bits.dm_global_str        = pstDmApiReg->u8DmGlobalStr ;//u8Dm_global_str;

    return HI_SUCCESS;
}

