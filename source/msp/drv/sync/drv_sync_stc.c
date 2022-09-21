/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

*******************************************************************************
  File Name     : drv_sync_stc.c
  Version       : Initial Draft
  Author        : l00370809
  Created       : 20016/9/28
  Description   :
******************************************************************************/

#include <asm/io.h>
#include <asm/div64.h>

#include "hi_reg_common.h"
#include "drv_ao_ext.h"
#include "drv_sync.h"
#include "drv_sync_stc.h"

#if    defined(CHIP_TYPE_hi3798cv200)  \
    || defined(CHIP_TYPE_hi3798mv200)  \
    || defined(CHIP_TYPE_hi3798mv300)  \
    || defined(CHIP_TYPE_hi3796mv200)

#define AIAO_SRC_PLL_HAS_CREECTED

#endif

spinlock_t StcLock = __SPIN_LOCK_UNLOCKED(StcLock);

extern SYNC_GLOBAL_STATE_S  g_SyncGlobalState;

/* init Vpll turning frq Crg*/
HI_VOID SYNC_PllTuneFreqCrgInit(HI_VOID)
{
    HI_U32 CrgFbdiv;
    HI_U32 CrgFrac;

    /* vpll tune crg init */
    CrgFbdiv = g_pstRegCrg->PERI_CRG140.bits.vpll_tune_int_cfg;
    CrgFrac  = g_pstRegCrg->PERI_CRG141.bits.vpll_tune_frac_cfg;

    if (CrgFbdiv == 0x0 && CrgFrac == 0x0)
    {
        CrgFbdiv = g_pstRegCrg->PERI_CRG_PLL9.u32;
        CrgFbdiv = CrgFbdiv & (0xfff);

        CrgFrac = g_pstRegCrg->PERI_CRG_PLL8.u32;
        CrgFrac = CrgFrac & (0xffffff);

        g_pstRegCrg->PERI_CRG140.bits.vpll_tune_int_cfg  = CrgFbdiv;
        g_pstRegCrg->PERI_CRG141.bits.vpll_tune_frac_cfg = CrgFrac;

        HI_INFO_SYNC("Vpll tune freq Crg init success !\n");
    }

    /* epll tune crg init */
    CrgFbdiv = g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg;
    CrgFrac  = g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg;

    if (CrgFbdiv == 0x0 && CrgFrac == 0x0)
    {

#ifdef  AIAO_SRC_PLL_HAS_CREECTED
        CrgFbdiv = AIAO_SRC_PLL_REG_INT_VAL;
        CrgFbdiv = CrgFbdiv & (0xfff);

        CrgFrac = AIAO_SRC_PLL_REG_FRAC_VAL;
        CrgFrac = CrgFrac & (0xffffff);
#else
        CrgFbdiv = g_pstRegCrg->PERI_CRG_PLL13.u32;
        CrgFbdiv = CrgFbdiv & (0xfff);

        CrgFrac = g_pstRegCrg->PERI_CRG_PLL12.u32;
        CrgFrac = CrgFrac & (0xffffff);
#endif
        g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg  = CrgFbdiv;
        g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg = CrgFrac;

        HI_INFO_SYNC("Epll tune freq Crg init success !\n");
    }

    /* hpll tune crg init */
    CrgFbdiv = g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg;
    CrgFrac  = g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg;

    if (CrgFbdiv == 0x0 && CrgFrac == 0x0)
    {
        CrgFbdiv = g_pstRegCrg->PERI_CRG_PLL11.u32;
        CrgFbdiv = CrgFbdiv & (0xfff);

        CrgFrac = g_pstRegCrg->PERI_CRG_PLL10.u32;
        CrgFrac = CrgFrac & (0xffffff);

        g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg  = CrgFbdiv;
        g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg = CrgFrac;

        HI_INFO_SYNC("Hpll tune freq Crg init success !\n");
    }

}

HI_BOOL SYNC_CheckPllTuneFreqIsEnable(HI_VOID)
{
    HI_U32 VpllTuneFreqFlag;
    HI_U32 EpllTuneFreqFlag;
    HI_U32 HpllTuneFreqFlag;

    VpllTuneFreqFlag = g_pstRegCrg->PERI_CRG_PLL9.u32;
    VpllTuneFreqFlag = (VpllTuneFreqFlag >> 25) & 0x01;

    EpllTuneFreqFlag = g_pstRegCrg->PERI_CRG_PLL13.u32;
    EpllTuneFreqFlag = (EpllTuneFreqFlag >> 25) & 0x01;

    HpllTuneFreqFlag = g_pstRegCrg->PERI_CRG_PLL11.u32;
    HpllTuneFreqFlag = (HpllTuneFreqFlag >> 25) & 0x01;

    if (VpllTuneFreqFlag || EpllTuneFreqFlag || HpllTuneFreqFlag)
    {
        HI_WARN_SYNC(" Pll tune Freq is disable! \n");
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_VOID SYNC_ProcStcAdjustFailEvent(HI_VOID)
{
    HI_U32 j = 0;

    for (j = 0; j < SYNC_MAX_NUM; j++)
    {
        if (HI_NULL != g_SyncGlobalState.SyncInfo[j].pSync
            && g_SyncGlobalState.SyncInfo[j].pSync->SyncAttr.enSyncRef == HI_UNF_SYNC_REF_PCR
            && g_SyncGlobalState.SyncInfo[j].pSync->PcrSyncInfo.enPcrAdjust == SYNC_PCR_ADJUST_SCR
            )
        {
            g_SyncGlobalState.SyncInfo[j].pSync->PcrSyncInfo.StcInfo.StcAdjustFail = HI_TRUE;
        }
    }
}

HI_BOOL SYNC_CheckStcAdjustFailEvent(HI_VOID)
{
    HI_U32 i = 0;

    for (i = 0; i < SYNC_MAX_NUM; i++)
    {
        if (HI_NULL != g_SyncGlobalState.SyncInfo[i].pSync
            && g_SyncGlobalState.SyncInfo[i].pSync->SyncAttr.enSyncRef == HI_UNF_SYNC_REF_PCR
            && g_SyncGlobalState.SyncInfo[i].pSync->PcrSyncInfo.enPcrAdjust == SYNC_PCR_ADJUST_SCR
            )
        {
            if (g_SyncGlobalState.SyncInfo[i].pSync->PcrSyncInfo.StcInfo.StcAdjustFail == HI_TRUE)
            {
               return HI_TRUE;
            }
        }
    }

    return HI_FALSE;
}

HI_S32 SYNC_CalculateDeltaFrac(HI_U32 Fbdiv, HI_U32 Frac, HI_S32 PPM, HI_S32 *DeltaFrac)
{
    HI_U64 PpmExpand;

    /*
    computational formula :
    PPM = PPM/100
    Fout = FReff(fbdiv+frac/2^24)/RefDiv
    DeltaFrac = (Fout/FReff * RefDiv * PPM/1000/1000 ) << 24
    */

    if (PPM >= 0)
    {
        PpmExpand = PPM;
        PpmExpand = ((PpmExpand * Fbdiv) << 24) + PpmExpand * Frac;
        do_div(PpmExpand, 100 * 1000000);

        *DeltaFrac = (HI_S32)(PpmExpand & 0xffffffff);
    }
    else
    {
        PpmExpand = -1 * PPM;
        PpmExpand = ((PpmExpand * Fbdiv) << 24) + PpmExpand * Frac;
        do_div(PpmExpand, 100 * 1000000);

        *DeltaFrac = -1 * (HI_S32)(PpmExpand & 0xffffffff);
    }

    return HI_SUCCESS;
}

HI_VOID SYNC_CalculateTargetFreq(HI_U32 *PllFbdiv, HI_U32 *PllFrac, HI_S32 PllDeltaFrac)
{
    if (PllDeltaFrac >= 0)
    {
        *PllFrac = *PllFrac + PllDeltaFrac;

        if (*PllFrac > 0xffffff)
        {
            *PllFbdiv = *PllFbdiv + 1;
            *PllFrac  = *PllFrac - 0x1000000;
        }
    }
    else
    {
        if (abs(PllDeltaFrac) > *PllFrac)
        {
            *PllFbdiv = *PllFbdiv - 1;
            *PllFrac  = *PllFrac + 0x1000000 + PllDeltaFrac;
        }
        else
        {
            *PllFrac = *PllFrac + PllDeltaFrac;
        }
    }

}

HI_VOID SYNC_VpllTuneFreq(HI_U32 VpllFbdiv, HI_U32 VpllFrac)
{
    g_pstRegCrg->PERI_CRG140.bits.vpll_tune_int_cfg   = VpllFbdiv;
    g_pstRegCrg->PERI_CRG141.bits.vpll_tune_frac_cfg  = VpllFrac;
    g_pstRegCrg->PERI_CRG142.bits.vpll_tune_step_int  = 0;
    g_pstRegCrg->PERI_CRG143.bits.vpll_tune_step_frac = 0x10;

    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_en        = 0;        /* 3: 0->1 tune frq */
    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_cken      = 1;        /* 0: clock en */
    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_srst_req  = 0;        /* 1: sorft req */
    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_mode      = 1;        /* 2: tune mode */
    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_divval    = 1;        /* 4-7: tune clock div */
    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_soft_cfg  = 0;        /* 8: sorft config en */

    g_pstRegCrg->PERI_CRG144.bits.vpll_tune_en = 0x1;              /* 3: 0->1 tune frq */
}

HI_VOID SYNC_VpllFreqReset(HI_VOID)
{
    HI_U32 VpllFbdiv;
    HI_U32 VpllFrac;

    VpllFbdiv = g_pstRegCrg->PERI_CRG_PLL9.u32;
    VpllFbdiv = VpllFbdiv & (0xfff);

    VpllFrac = g_pstRegCrg->PERI_CRG_PLL8.u32;
    VpllFrac = VpllFrac & (0xffffff);

    SYNC_VpllTuneFreq(VpllFbdiv, VpllFrac);

    HI_INFO_SYNC("Vpll Freq Reset !\n");
}

HI_VOID SYNC_EpllTuneFreq(HI_U32 EpllFbdiv, HI_U32 EpllFrac)
{
    g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg   = EpllFbdiv;
    g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg  = EpllFrac;
    g_pstRegCrg->PERI_CRG122.bits.epll_tune_step_int  = 0;
    g_pstRegCrg->PERI_CRG123.bits.epll_tune_step_frac = 0x10;

    g_pstRegCrg->PERI_CRG124.bits.epll_tune_en        = 0;        /* 3: 0->1 tune frq */
    g_pstRegCrg->PERI_CRG124.bits.epll_tune_cken      = 1;        /* 0: clock en */
    g_pstRegCrg->PERI_CRG124.bits.epll_tune_srst_req  = 0;        /* 1: sorft req */
    g_pstRegCrg->PERI_CRG124.bits.epll_tune_mode      = 1;        /* 2: tune mode */
    g_pstRegCrg->PERI_CRG124.bits.epll_tune_divval    = 1;        /* 4-7: tune clock div */
    g_pstRegCrg->PERI_CRG124.bits.epll_tune_soft_cfg  = 0;        /* 8: sorft config en */

    g_pstRegCrg->PERI_CRG124.bits.epll_tune_en = 0x1;              /* 3: 0->1 tune frq */
}

HI_VOID SYNC_EpllFreqReset(HI_VOID)
{
    HI_U32 EpllFbdiv;
    HI_U32 EpllFrac;

#ifdef AIAO_SRC_PLL_HAS_CREECTED
    EpllFbdiv = AIAO_SRC_PLL_REG_INT_VAL;
    EpllFbdiv = EpllFbdiv & (0xfff);

    EpllFrac = AIAO_SRC_PLL_REG_FRAC_VAL;
    EpllFrac = EpllFrac & (0xffffff);
#else
    EpllFbdiv = g_pstRegCrg->PERI_CRG_PLL13.u32;
    EpllFbdiv = EpllFbdiv & (0xfff);

    EpllFrac = g_pstRegCrg->PERI_CRG_PLL12.u32;
    EpllFrac = EpllFrac & (0xffffff);
#endif

    SYNC_EpllTuneFreq(EpllFbdiv, EpllFrac);

    HI_INFO_SYNC("Epll Freq Reset !\n");
}

HI_VOID SYNC_HpllTuneFreq(HI_U32 HpllFbdiv, HI_U32 HpllFrac)
{
    g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg   = HpllFbdiv;
    g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg  = HpllFrac;
    g_pstRegCrg->PERI_CRG137.bits.hpll_tune_step_int  = 0;
    g_pstRegCrg->PERI_CRG138.bits.hpll_tune_step_frac = 0x10;

    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_en        = 0;        /* 3: 0->1 tune frq */
    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_cken      = 1;        /* 0: clock en */
    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_srst_req  = 0;        /* 1: sorft req */
    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_mode      = 1;        /* 2: tune mode */
    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_divval    = 1;        /* 4-7: tune clock div */
    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_soft_cfg  = 0;        /* 8: sorft config en */

    g_pstRegCrg->PERI_CRG139.bits.hpll_tune_en = 0x1;              /* 3: 0->1 tune frq */
}

HI_VOID SYNC_HpllFreqReset(HI_VOID)
{
    HI_U32 HpllFbdiv;
    HI_U32 HpllFrac;

    HpllFbdiv = g_pstRegCrg->PERI_CRG_PLL11.u32;
    HpllFbdiv = HpllFbdiv & (0xfff);

    HpllFrac = g_pstRegCrg->PERI_CRG_PLL10.u32;
    HpllFrac = HpllFrac & (0xffffff);

    SYNC_HpllTuneFreq(HpllFbdiv, HpllFrac);

    HI_INFO_SYNC("Hpll Freq Reset !\n");
}

HI_S32 SYNC_CalculatePpm(HI_U32 Fbdiv, HI_U32 Frac, HI_S32 DeltaFrac, HI_S32 *PPM)
{
    HI_U64 DeltaFracExpand;
    HI_U64 FracExpand;

    FracExpand = Fbdiv;
    FracExpand = (FracExpand << 24) + Frac;

    if (DeltaFrac >= 0)
    {
        DeltaFracExpand = DeltaFrac;
        DeltaFracExpand = DeltaFracExpand * 100 *1000000;

        do_div(DeltaFracExpand, FracExpand);

        *PPM = (HI_S32)(DeltaFracExpand & 0xffffffff);
    }
    else
    {
        DeltaFracExpand = -1 * DeltaFrac;
        DeltaFracExpand = DeltaFracExpand * 100 *1000000;

        do_div(DeltaFracExpand, FracExpand);

        *PPM = -1 * (HI_S32)(DeltaFracExpand & 0xffffffff);
    }

    return HI_SUCCESS;
}



HI_VOID SYNC_PllTuneFreq(SYNC_S *pSync, HI_S32 PPM)
{
    HI_U32 VpllTurneBusy;
    HI_U32 EpllTurneBusy;
    HI_U32 HpllTurneBusy;
    HI_S32 VpllAdjust;
    HI_S32 EpllAdjust;
    HI_S32 HpllAdjust;

    HI_U32 VpllFbdiv;
    HI_U32 VpllFrac;
    HI_U32 EpllFbdiv;
    HI_U32 EpllFrac;
    HI_U32 HpllFbdiv;
    HI_U32 HpllFrac;

    HI_U32 VpllTargetFbdiv;
    HI_U32 VpllTargetFrac;
    HI_U32 EpllTargetFbdiv;
    HI_U32 EpllTargetFrac;
    HI_U32 HpllTargetFbdiv;
    HI_U32 HpllTargetFrac;

    HI_S32 VpllDeltaFrac;
    HI_S32 EpllDeltaFrac;
    HI_S32 HpllDeltaFrac;

    HI_S32 VpllPpm;
    HI_S32 EpllPpm;
    HI_S32 HpllPpm;

    if (spin_trylock(&StcLock) == 0)
    {
        return ;
    }

    if (SYNC_CheckStcAdjustFailEvent() == HI_TRUE)
    {
        spin_unlock(&StcLock);
        return ;
    }

    VpllFbdiv = g_pstRegCrg->PERI_CRG_PLL9.u32;
    VpllFbdiv = VpllFbdiv & (0xfff);

    VpllFrac = g_pstRegCrg->PERI_CRG_PLL8.u32;
    VpllFrac = VpllFrac & (0xffffff);

#ifdef  AIAO_SRC_PLL_HAS_CREECTED
    EpllFbdiv = AIAO_SRC_PLL_REG_INT_VAL;
    EpllFbdiv = EpllFbdiv & (0xfff);

    EpllFrac = AIAO_SRC_PLL_REG_FRAC_VAL;
    EpllFrac = EpllFrac & (0xffffff);
#else
    EpllFbdiv = g_pstRegCrg->PERI_CRG_PLL13.u32;
    EpllFbdiv = EpllFbdiv & (0xfff);

    EpllFrac = g_pstRegCrg->PERI_CRG_PLL12.u32;
    EpllFrac = EpllFrac & (0xffffff);
#endif

    HpllFbdiv = g_pstRegCrg->PERI_CRG_PLL11.u32;
    HpllFbdiv = HpllFbdiv & (0xfff);

    HpllFrac = g_pstRegCrg->PERI_CRG_PLL10.u32;
    HpllFrac = HpllFrac & (0xffffff);

    VpllTargetFbdiv = g_pstRegCrg->PERI_CRG140.bits.vpll_tune_int_cfg;
    VpllTargetFrac  = g_pstRegCrg->PERI_CRG141.bits.vpll_tune_frac_cfg;

    EpllTargetFbdiv = g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg;
    EpllTargetFrac  = g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg;

    HpllTargetFbdiv = g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg;
    HpllTargetFrac  = g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg;

    /* judge pll bdiv value change */
    if (abs(VpllFbdiv - VpllTargetFbdiv) >= 2 )
    {
        g_pstRegCrg->PERI_CRG140.bits.vpll_tune_int_cfg  = VpllFbdiv;
        g_pstRegCrg->PERI_CRG141.bits.vpll_tune_frac_cfg = VpllFrac;

        VpllTargetFbdiv = VpllFbdiv;
        VpllTargetFrac  = VpllFrac;

        HI_WARN_SYNC("Vpll Fbdiv is changed !\n");
    }

    if (abs(EpllFbdiv - EpllTargetFbdiv) >= 2 )
    {
        g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg  = EpllFbdiv;
        g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg = EpllFrac;

        EpllTargetFbdiv = EpllFbdiv;
        EpllTargetFrac  = EpllFrac;

        HI_WARN_SYNC("Epll Fbdiv is changed !\n");
    }

    if (abs(HpllFbdiv - HpllTargetFbdiv) >= 2 )
    {
        g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg  = HpllFbdiv;
        g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg = HpllFrac;

        HpllTargetFbdiv = HpllFbdiv;
        HpllTargetFrac  = HpllFrac;

        HI_WARN_SYNC("Hpll Fbdiv is changed !\n");
    }

    VpllAdjust = (VpllTargetFbdiv - VpllFbdiv) * 0x1000000 + (VpllTargetFrac - VpllFrac);
    EpllAdjust = (EpllTargetFbdiv - EpllFbdiv) * 0x1000000 + (EpllTargetFrac - EpllFrac);
    HpllAdjust = (HpllTargetFbdiv - HpllFbdiv) * 0x1000000 + (HpllTargetFrac - HpllFrac);

    SYNC_CalculatePpm(VpllFbdiv, VpllFrac, VpllAdjust, &VpllPpm);
    SYNC_CalculatePpm(EpllFbdiv, EpllFrac, EpllAdjust, &EpllPpm);
    SYNC_CalculatePpm(HpllFbdiv, HpllFrac, HpllAdjust, &HpllPpm);

    if (abs(VpllPpm - EpllPpm) > PPM_ADJUST_THRESHOLD)
    {
        EpllTargetFbdiv = EpllFbdiv;
        EpllTargetFrac  = EpllFrac;

        SYNC_CalculateDeltaFrac(EpllFbdiv, EpllFrac, VpllPpm, &EpllDeltaFrac);

        SYNC_CalculateTargetFreq(&EpllTargetFbdiv, &EpllTargetFrac, EpllDeltaFrac);

        EpllTurneBusy = g_pstRegCrg->PERI_CRG171.bits.epll_tune_busy;
        if (EpllTurneBusy == 0)
        {
            SYNC_EpllTuneFreq(EpllTargetFbdiv, EpllTargetFrac);
            g_pstRegCrg->PERI_CRG120.bits.epll_tune_int_cfg  = EpllTargetFbdiv;
            g_pstRegCrg->PERI_CRG121.bits.epll_tune_frac_cfg = EpllTargetFrac;
        }

        HI_WARN_SYNC("VpllPpm and EpllPpm are not equal, VpllPpm:%d, EpllPpm:%d\n", VpllPpm, EpllPpm);
    }

    if (abs(VpllPpm - HpllPpm) > PPM_ADJUST_THRESHOLD)
    {
        HpllTargetFbdiv = HpllFbdiv;
        HpllTargetFrac  = HpllFrac;

        SYNC_CalculateDeltaFrac(HpllFbdiv, HpllFrac, VpllPpm, &HpllDeltaFrac);

        SYNC_CalculateTargetFreq(&HpllTargetFbdiv, &HpllTargetFrac, HpllDeltaFrac);

        HpllTurneBusy = g_pstRegCrg->PERI_CRG177.bits.hpll_tune_busy;
        if (HpllTurneBusy == 0)
        {
            SYNC_HpllTuneFreq(HpllTargetFbdiv, HpllTargetFrac);
            g_pstRegCrg->PERI_CRG135.bits.hpll_tune_int_cfg  = HpllTargetFbdiv;
            g_pstRegCrg->PERI_CRG136.bits.hpll_tune_frac_cfg = HpllTargetFrac;
        }

        HI_WARN_SYNC("VpllPpm and HpllPpm are not equal, VpllPpm:%d, HpllPpm:%d \n", VpllPpm, HpllPpm);
    }

    /* calculate pll Delta Frac */
    SYNC_CalculateDeltaFrac(VpllTargetFbdiv, VpllTargetFrac, PPM, &VpllDeltaFrac);
    SYNC_CalculateDeltaFrac(EpllTargetFbdiv, EpllTargetFrac, PPM, &EpllDeltaFrac);
    SYNC_CalculateDeltaFrac(HpllTargetFbdiv, HpllTargetFrac, PPM, &HpllDeltaFrac);

    /* update pll Target Frequency */
    SYNC_CalculateTargetFreq(&VpllTargetFbdiv, &VpllTargetFrac, VpllDeltaFrac);
    SYNC_CalculateTargetFreq(&EpllTargetFbdiv, &EpllTargetFrac, EpllDeltaFrac);
    SYNC_CalculateTargetFreq(&HpllTargetFbdiv, &HpllTargetFrac, HpllDeltaFrac);

    /* stc adjust prscision is 0.1(PPM) */
    if (abs(PPM) < PPM_ADJUST_THRESHOLD)
    {
        spin_unlock(&StcLock);
        return ;
    }

    /* if adjust too large ,reset pll frq */
    if (abs(VpllPpm + PPM) / 100 > STC_MAX_PPM)
    {
        SYNC_VpllFreqReset();
        SYNC_EpllFreqReset();
        SYNC_HpllFreqReset();

        SYNC_ProcStcAdjustFailEvent();

        HI_WARN_SYNC("STC Adjust too large and Fail, AdjustPPM:%d \n", (VpllPpm + PPM) / 100);

        spin_unlock(&StcLock);
        return ;
    }

    VpllTurneBusy = g_pstRegCrg->PERI_CRG179.bits.vpll_tune_busy;
    EpllTurneBusy = g_pstRegCrg->PERI_CRG171.bits.epll_tune_busy;
    HpllTurneBusy = g_pstRegCrg->PERI_CRG177.bits.hpll_tune_busy;

    /* when Vpll is idle then tune Frq */
    if (!VpllTurneBusy && !EpllTurneBusy && !HpllTurneBusy)
    {
        SYNC_VpllTuneFreq(VpllTargetFbdiv, VpllTargetFrac);
        SYNC_EpllTuneFreq(EpllTargetFbdiv, EpllTargetFrac);
        SYNC_HpllTuneFreq(HpllTargetFbdiv, HpllTargetFrac);

        HI_INFO_SYNC("VpllTargetFbdiv:%d, VpllTargetFrac:%d \n \
                      EpllTargetFbdiv:%d, EpllTargetFrac:%d \n \
                      HpllTargetFbdiv:%d, HpllTargetFrac:%d \n",
                      VpllTargetFbdiv,      VpllTargetFrac,
                      EpllTargetFbdiv,      EpllTargetFrac,
                      HpllTargetFbdiv,      HpllTargetFrac);
    }

    spin_unlock(&StcLock);
    return;
}

/* stc Adjust Policy */
/* select first pcr channel to adjust stc */
HI_VOID SYNC_StcAdjustPolicy(SYNC_S *pSync, HI_S32 *PPM)
{
    HI_U32 i,j;

    if (pSync->CrtStatus == SYNC_STATUS_STOP)
    {
        pSync->PcrSyncInfo.StcAdjustReferFlag = HI_FALSE;

        *PPM = 0;
        return;
    }

    if (pSync->PcrSyncInfo.StcAdjustReferFlag == HI_TRUE)
    {
        *PPM = pSync->PcrSyncInfo.PpmInfo.PpmValid;
        return;
    }

    /* search refer channel */
    for (i = 0; i < SYNC_MAX_NUM; i++)
    {
        if (HI_NULL != g_SyncGlobalState.SyncInfo[i].pSync
            && g_SyncGlobalState.SyncInfo[i].pSync->SyncAttr.enSyncRef == HI_UNF_SYNC_REF_PCR
            && g_SyncGlobalState.SyncInfo[i].pSync->PcrSyncInfo.enPcrAdjust == SYNC_PCR_ADJUST_SCR
            && g_SyncGlobalState.SyncInfo[i].pSync->PcrSyncInfo.PcrFirstCome == HI_TRUE
            )
        {
            if(g_SyncGlobalState.SyncInfo[i].pSync->CrtStatus != SYNC_STATUS_STOP)
            {
                break;
            }
        }
    }

    if (i >= SYNC_MAX_NUM)
    {
        *PPM = 0;
        return;
    }

    /* judge the current channel is refer channel or not */
    if (g_SyncGlobalState.SyncInfo[i].pSync == pSync)
    {
        pSync->PcrSyncInfo.StcAdjustReferFlag = HI_TRUE;

        for (j = 0; j < SYNC_MAX_NUM; j++)
        {
            if (HI_NULL != g_SyncGlobalState.SyncInfo[j].pSync
                && g_SyncGlobalState.SyncInfo[j].pSync != pSync
                && g_SyncGlobalState.SyncInfo[j].pSync->SyncAttr.enSyncRef == HI_UNF_SYNC_REF_PCR
                && g_SyncGlobalState.SyncInfo[j].pSync->PcrSyncInfo.StcAdjustReferFlag == HI_TRUE
                )
            {
                g_SyncGlobalState.SyncInfo[j].pSync->PcrSyncInfo.StcAdjustReferFlag = HI_FALSE;
            }
        }

        HI_INFO_SYNC("current stc adjust refer sync channel change \n");
    }

    *PPM = 0;
    return;
}

HI_VOID SYNC_StcAdjust(SYNC_S *pSync, HI_U64 PCRValue ,HI_U64 STCValue)
{
    HI_S32      PcrDelta = 0;
    HI_S32      StcDelta = 0;

    if (   (pSync->PcrSyncInfo.enPcrAdjust != SYNC_PCR_ADJUST_SCR)
        || (pSync->PcrSyncInfo.StcInfo.StcAdjustFail == HI_TRUE) )
    {
        return;
    }

    /* init stc adjust */
    if (pSync->PcrSyncInfo.StcInfo.StcAdjustInitFlag != HI_TRUE)
    {
        if (SYNC_CheckPllTuneFreqIsEnable() == HI_FALSE)
        {
           pSync->PcrSyncInfo.StcInfo.StcAdjustFail = HI_TRUE;

           HI_WARN_SYNC("Pll Tune Freq Is disable !\n");
           return;
        }

        SYNC_PllTuneFreqCrgInit();
        pSync->PcrSyncInfo.StcInfo.StcLastValue = STCValue;
        pSync->PcrSyncInfo.PcrLastValue         = PCRValue;
        pSync->PcrSyncInfo.PpmInfo.PpmNumber    = 0;
        pSync->PcrSyncInfo.PpmInfo.PpmSum       = 0;
        pSync->PcrSyncInfo.PpmInfo.PpmValid     = 0;
        pSync->PcrSyncInfo.PcrDeltaNumber       = 0;
        pSync->PcrSyncInfo.PcrDeltaSum          = 0;
        pSync->PcrSyncInfo.StcInfo.StcDeltaSum  = 0;
        pSync->PcrSyncInfo.StcInfo.StcAdjustInitFlag = HI_TRUE;
        pSync->PcrSyncInfo.StcAdjustReferFlag        = HI_FALSE;

        HI_INFO_SYNC("stc adjust init success\n");
        return ;
    }

    /* pcr or stc smaller than the last one*/
    if ((PCRValue < pSync->PcrSyncInfo.PcrLastValue) || (STCValue < pSync->PcrSyncInfo.StcInfo.StcLastValue))
    {
        pSync->PcrSyncInfo.StcInfo.StcLastValue = STCValue;
        pSync->PcrSyncInfo.PcrLastValue         = PCRValue;

        HI_INFO_SYNC("pcr or stc smaller than the last one \n");
        return ;
    }

    /* pcr jump */
    if (PCRValue - pSync->PcrSyncInfo.PcrLastValue > PCR_MAX_STEP)
    {
        pSync->PcrSyncInfo.StcInfo.StcLastValue = STCValue;
        pSync->PcrSyncInfo.PcrLastValue         = PCRValue;

        HI_INFO_SYNC("PCR Jump !\n");
        return ;
    }

    StcDelta = STCValue - pSync->PcrSyncInfo.StcInfo.StcLastValue;
    PcrDelta = PCRValue - pSync->PcrSyncInfo.PcrLastValue;

    pSync->PcrSyncInfo.StcInfo.StcLastValue = STCValue;
    pSync->PcrSyncInfo.PcrLastValue         = PCRValue;

    /* refer StcDelta judge PcrDelta*/
    if (abs(PcrDelta - StcDelta) > PCR_STC_MAX_DELTA_DIFF)
    {
        HI_INFO_SYNC("PcrDelt is err, PcrDelt:%d, StcDelt:%d\n", PcrDelta, StcDelta);
        return ;
    }

     pSync->PcrSyncInfo.PcrDeltaSum += PcrDelta;
     pSync->PcrSyncInfo.StcInfo.StcDeltaSum += StcDelta;
     pSync->PcrSyncInfo.PcrDeltaNumber++;

    /* caculate ppm*100 */
    if ((pSync->PcrSyncInfo.PcrDeltaNumber == PCR_DELTA_FILTER_NUMBER) && (pSync->PcrSyncInfo.PcrDeltaSum != 0))
    {
        HI_U64 PcrStcDeltaExpand;
        HI_S32 PcrStcDelta;
        HI_S32 PPM;

        PcrStcDelta = (pSync->PcrSyncInfo.PcrDeltaSum - pSync->PcrSyncInfo.StcInfo.StcDeltaSum);

        if (PcrStcDelta > 0)
        {
            PcrStcDeltaExpand = PcrStcDelta;
            PcrStcDeltaExpand = PcrStcDeltaExpand * 1000 * 1000 * 100;

            do_div(PcrStcDeltaExpand, pSync->PcrSyncInfo.PcrDeltaSum);
            PPM = (HI_S32)(PcrStcDeltaExpand & 0xffffffff);
        }
        else
        {
            PcrStcDeltaExpand = -1 * PcrStcDelta;
            PcrStcDeltaExpand = PcrStcDeltaExpand * 1000 * 1000 * 100;

            do_div(PcrStcDeltaExpand, pSync->PcrSyncInfo.PcrDeltaSum);
            PPM = -1 * (HI_S32)(PcrStcDeltaExpand & 0xffffffff);
        }

        pSync->PcrSyncInfo.PcrDeltaNumber      = 0;
        pSync->PcrSyncInfo.PcrDeltaSum         = 0;
        pSync->PcrSyncInfo.StcInfo.StcDeltaSum = 0;

        if ((PPM / 100) > STC_MAX_PPM)
        {
           HI_INFO_SYNC("PPM err, PPM:%d \n", (PPM / 100));
           return;
        }

        pSync->PcrSyncInfo.PpmInfo.PpmSum += PPM;
        pSync->PcrSyncInfo.PpmInfo.PpmNumber++;
    }

    if (pSync->PcrSyncInfo.PpmInfo.PpmNumber == PPM_FILTER_NUMBER)
    {
        HI_S32 PPM = 0;

        pSync->PcrSyncInfo.PpmInfo.PpmValid = pSync->PcrSyncInfo.PpmInfo.PpmSum / pSync->PcrSyncInfo.PpmInfo.PpmNumber;

        SYNC_StcAdjustPolicy(pSync, &PPM);

        SYNC_PllTuneFreq(pSync, PPM);

        pSync->PcrSyncInfo.PpmInfo.PpmNumber = 0;
        pSync->PcrSyncInfo.PpmInfo.PpmSum    = 0;

        HI_INFO_SYNC("current channel Valid PPM*100:%d, adjust STC PPM*100:%d\n", pSync->PcrSyncInfo.PpmInfo.PpmValid, PPM);
    }
}



