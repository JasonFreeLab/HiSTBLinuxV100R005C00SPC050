#include "hi_reg_common.h"
#include "product.h"
#include "public.h"
#include "vfmw_osal_ext.h"

#ifdef VFMW_VDH_V5R2C1_SUPPORT
#include "vdm_hal_v5r2c1_api.h"
#endif

#if defined(ENV_ARMLINUX_KERNEL)
#include "hi_kernel_adapt.h"
#include "hi_drv_stat.h"
#include "hi_drv_sys.h"
#endif


/*======================================================================*/
/*   全局数据                                                           */
/*======================================================================*/

#define VFMW_TILE_WIDTH  1920
#define VFMW_TILE_HEIGHT 1088

SINT32 g_ChipMaxWidth  = 8192;   // chip support max width
SINT32 g_ChipMaxHeight = 8192;  // chip support max height

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
UINT8  g_LowDelayCalcStat[MAX_CHAN_NUM];
SINT32 g_LowDelayCalcHandle[MAX_CHAN_NUM];
UINT32 g_LowDelaySeqIndex[MAX_CHAN_NUM];
#endif

#ifdef ENV_SOS_KERNEL
volatile HI_REG_CRG_S  *g_pstRegCrg;
#endif


/*======================================================================*/
/*   内部接口                                                           */
/*======================================================================*/

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
/************************************************************************
    低延迟时间统计
 ************************************************************************/
VOID VDEC_Lowdelay_Event_Time(SINT32 ChanId, HI_LD_Event_ID_E eventId, HI_U32 u32FrameId)
{
    HI_LD_Event_S evt;
    HI_U32 TmpTime = 0;
    HI_DRV_SYS_GetTimeStampMs(&TmpTime);

    evt.evt_id = eventId;
    evt.frame = u32FrameId;
    evt.handle = g_LowDelayCalcHandle[ChanId];
    evt.time = TmpTime;

    if (1 == g_LowDelayCalcStat[ChanId])
    {
        HI_DRV_LD_Notify_Event(&evt);
    }
}
#endif

VOID VDM_SetClockSkip(UINT32 SkipValue)
{
    U_PERI_CRG30 u32TmpValue_30;

    u32TmpValue_30.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue_30.bits.vdhclk_skipcfg = SkipValue;

    /* To reset config, we should set 0 then 1 */
    u32TmpValue_30.bits.vdhclk_loaden = 0x0;
    g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue_30.u32;
    u32TmpValue_30.bits.vdhclk_loaden = 0x1;
    g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue_30.u32;

    return;
}

VOID VDM_OpenHardware(SINT32 VdhId)
{
    SINT32 ScdId, D32;

    if (0 == VdhId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
        u32TmpValue.bits.vdh_cken = 0x1;
        u32TmpValue.bits.vdh_all_srst_req = 0x0;
        u32TmpValue.bits.vdh_mfd_srst_req = 0x0;
        u32TmpValue.bits.vdh_clk_sel = 0x0;
        u32TmpValue.bits.vdhclk_skipcfg = 0x0;
        u32TmpValue.bits.vdhclk_loaden = 0x0;/*使能扣脉冲的操作，要扣脉冲的时候此位要配位1*/

        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

    	//VDM_SetClockSkip(25);

        vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);
    }
    else
    {
        dprint(PRN_FATAL, "VDM_OpenHardware failed, wrong VdhId %d\n", VdhId);
    }

    for (ScdId = 0; ScdId < MAX_SCD_NUM; ScdId++)
    {
        D32 = 0x481a1f7;
        WR_SCDREG(ScdId, REG_EMAR_ID, D32);
    }

    return;
}

VOID VDM_CloseHardware(SINT32 VdhId)
{
    if (0 == VdhId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;

        VDMHAL_GlbResetX(VdhId);

        u32TmpValue.bits.vdh_cken = 0x0;
        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

        vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);
    }
    else
    {
        dprint(PRN_FATAL, "VDM_CloseHardware failed, wrong VdhId %d\n", VdhId);
    }

    return;
}

VOID DSP_OpenHardware(SINT32 VdhId)
{
    if (0 == VdhId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
        u32TmpValue.bits.vdhdsp_cken = 0x1;

        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

        vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);
    }
    else
    {
        dprint(PRN_FATAL, "DSP_OpenHardware failed, wrong VdhId %d\n", VdhId);
    }

    return;
}

VOID DSP_CloseHardware(SINT32 VdhId)
{
    if (0 == VdhId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
        u32TmpValue.bits.vdhdsp_cken = 0x0;

        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

        vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);

    }
    else
    {
        dprint(PRN_FATAL, "DSP_CloseHardware failed, wrong VdhId %d\n", VdhId);
    }

    return;
}

VOID SCD_OpenHardware(SINT32 ScdId)
{
    if (0 == ScdId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
        u32TmpValue.bits.vdh_scd_srst_req = 0x0;
        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;
    }
    else
    {
        dprint(PRN_FATAL, "SCD_OpenHardware Wrong ScdId %d\n", ScdId);
    }

    return;
}

VOID SCD_CloseHardware(SINT32 ScdId)
{
    if (0 == ScdId)
    {
        U_PERI_CRG30 u32TmpValue;
        u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
        u32TmpValue.bits.vdh_scd_srst_req = 0x1;
        g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;
    }
    else
    {
        dprint(PRN_FATAL, "SCD_CloseHardware Wrong ScdId %d\n", ScdId);
    }

    return;
}

VOID BPD_OpenHardware(SINT32 BpdId)
{
    U_PERI_CRG34 u32TmpValue;
    u32TmpValue.u32 = g_pstRegCrg->PERI_CRG34.u32;
    u32TmpValue.bits.bpd_cken = 0x1;
    u32TmpValue.bits.bpd_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG34.u32 = u32TmpValue.u32;

    return;
}

VOID BPD_CloseHardware(SINT32 BpdId)
{
    U_PERI_CRG34 u32TmpValue;
    u32TmpValue.u32 = g_pstRegCrg->PERI_CRG34.u32;
    u32TmpValue.bits.bpd_cken = 0x0;
    u32TmpValue.bits.bpd_srst_req = 0x1;
    g_pstRegCrg->PERI_CRG34.u32 = u32TmpValue.u32;

    return;
}

VOID MMU_OpenHardware(SINT32 MmuId)
{
    U_PERI_CRG207 u32VdhSmmu;
    u32VdhSmmu.u32 = g_pstRegCrg->PERI_CRG207.u32;

    u32VdhSmmu.bits.vdh_smmu_cken = 0x1;
    g_pstRegCrg->PERI_CRG207.u32 = u32VdhSmmu.u32;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);

    u32VdhSmmu.bits.vdh_smmu_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG207.u32 = u32VdhSmmu.u32;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);

    return;
}

VOID MMU_CloseHardware(SINT32 MmuId)
{
#if 0
    U_PERI_CRG207 u32VdhSmmu;
    u32VdhSmmu.u32 = g_pstRegCrg->PERI_CRG207.u32;

    u32VdhSmmu.bits.vdh_smmu_srst_req = 0x1;
    g_pstRegCrg->PERI_CRG207.u32 = u32VdhSmmu.u32;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);

    u32VdhSmmu.bits.vdh_smmu_cken = 0x0;
    g_pstRegCrg->PERI_CRG207.u32 = u32VdhSmmu.u32;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay(30);
#endif

    return;
}

VOID PDT_GetOutputFormat(OUTPUT_FORMAT_S *pStreamInfo)
{
    if ((pStreamInfo->VideoStandard == VFMW_VP9)
        || ((pStreamInfo->Width > VFMW_TILE_WIDTH) || (pStreamInfo->Height > VFMW_TILE_HEIGHT)))
    {
        pStreamInfo->IsTile = 1;
    }
    else
    {
        pStreamInfo->IsTile = 0;
    }

    return;
}

/************************************************************************
    初始化hal层函数指针
 ************************************************************************/
VOID PDT_InitHalInterface(VDMHAL_FUN_PTR_S *pFuncPtr)
{
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet(pFuncPtr, 0, sizeof(VDMHAL_FUN_PTR_S));

    pFuncPtr->pfun_VDMDRV_SetClockSkip           = VDM_SetClockSkip;
    pFuncPtr->pfun_VDMDRV_OpenHardware           = VDM_OpenHardware;
    pFuncPtr->pfun_VDMDRV_CloseHardware          = VDM_CloseHardware;
    pFuncPtr->pfun_DSPDRV_OpenHardware           = DSP_OpenHardware;
    pFuncPtr->pfun_DSPDRV_CloseHardware          = DSP_CloseHardware;
    pFuncPtr->pfun_SCDDRV_OpenHardware           = SCD_OpenHardware;
    pFuncPtr->pfun_SCDDRV_CloseHardware          = SCD_CloseHardware;
    pFuncPtr->pfun_BPDDRV_OpenHardware           = BPD_OpenHardware;
    pFuncPtr->pfun_BPDDRV_CloseHardware          = BPD_CloseHardware;
    pFuncPtr->pfun_MMUDRV_OpenHardware           = MMU_OpenHardware;
    pFuncPtr->pfun_MMUDRV_CloseHardware          = MMU_CloseHardware;

#ifdef VFMW_VDH_V5R2C1_SUPPORT
    pFuncPtr->pfun_VDMHAL_GetHalMemSize          = VDMHAL_V5R2C1_GetHalMemSize;
    pFuncPtr->pfun_VDMHAL_CalcFsSize             = VDMHAL_V5R2C1_CalcFsSize;
    pFuncPtr->pfun_VDMHAL_OpenHAL                = VDMHAL_V5R2C1_OpenHAL;
    pFuncPtr->pfun_VDMHAL_CloseHAL               = VDMHAL_V5R2C1_CloseHAL;
    pFuncPtr->pfun_VDMHAL_ArrangeMem             = VDMHAL_V5R2C1_ArrangeMem;
    pFuncPtr->pfun_VDMHAL_ResetVdm               = VDMHAL_V5R2C1_ResetVdm;
    pFuncPtr->pfun_VDMHAL_GetRpuSize             = VDMHAL_V5R2C1_GetRpuSize;
    pFuncPtr->pfun_VDMHAL_SetSmmuPageTableAddr   = VDMHAL_V5R2C1_SetSmmuPageTableAddr;
    pFuncPtr->pfun_VDMHAL_EnableSmmu             = VDMHAL_V5R2C1_EnableSmmu;
    pFuncPtr->pfun_VDMHAL_GlbReset               = VDMHAL_V5R2C1_GlbReset;
    pFuncPtr->pfun_VDMHAL_GlbResetX              = VDMHAL_V5R2C1_GlbResetX;
    pFuncPtr->pfun_VDMHAL_ClearIntState          = VDMHAL_V5R2C1_ClearIntState;
    pFuncPtr->pfun_VDMHAL_ClearMMUIntState       = VDMHAL_V5R2C1_ClearMMUIntState;
    pFuncPtr->pfun_VDMHAL_MaskInt                = VDMHAL_V5R2C1_MaskInt;
    pFuncPtr->pfun_VDMHAL_EnableInt              = VDMHAL_V5R2C1_EnableInt;
    pFuncPtr->pfun_VDMHAL_CheckReg               = VDMHAL_V5R2C1_CheckReg;
    pFuncPtr->pfun_VDMHAL_ReadMMUMask            = VDMHAL_V5R2C1_ReadMMUMask;
    pFuncPtr->pfun_VDMHAL_WriteMMUMask           = VDMHAL_V5R2C1_WriteMMUMask;
    pFuncPtr->pfun_VDMHAL_StartHwRepair          = VDMHAL_V5R2C1_StartHwRepair;
    pFuncPtr->pfun_VDMHAL_StartHwDecode          = VDMHAL_V5R2C1_StartHwDecode;
    pFuncPtr->pfun_VDMHAL_PrepareDec             = VDMHAL_V5R2C1_PrepareDec;
    pFuncPtr->pfun_VDMHAL_IsVdmReady             = VDMHAL_V5R2C1_IsVdmReady;
    pFuncPtr->pfun_VDMHAL_IsVdmRun               = VDMHAL_V5R2C1_IsVdmRun;
    pFuncPtr->pfun_VDMHAL_PrepareRepair          = VDMHAL_V5R2C1_PrepareRepair;
    pFuncPtr->pfun_VDMHAL_MakeDecReport          = VDMHAL_V5R2C1_MakeDecReport;
    pFuncPtr->pfun_VDMHAL_UpdateHardwareInfo     = VDMHAL_V5R2C1_UpdateHardwareInfo;
    pFuncPtr->pfun_VDMHAL_GetCharacter           = VDMHAL_V5R2C1_GetCharacter;
    pFuncPtr->pfun_VDMHAL_Write1DYuv             = VDMHAL_V5R2C1_WriteBigTitle1DYuv;
    pFuncPtr->pfun_VDMHAL_IsVdhDecOver           = VDMHAL_V5R2C1_IsVdhDecOver;
    pFuncPtr->pfun_VDMHAL_IsVdhPartDecOver       = VDMHAL_V5R2C1_IsVdhPartDecOver;
#endif

    return;
}

VOID PDT_GetVdecCapability(VDEC_CAP_S *pCap)
{
    SINT32 StdCnt = 0;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet(pCap, 0, sizeof(VDEC_CAP_S));

    pCap->s32MaxChanNum = MAX_CHAN_NUM;
    pCap->s32MaxBitRate = 50;
    pCap->s32MaxFrameWidth  = 4096;
    pCap->s32MaxFrameHeight = 2304;
    pCap->s32MaxPixelPerSec = pCap->s32MaxFrameWidth * pCap->s32MaxFrameHeight * 30 * 3 / 2;

    pCap->SupportedStd[StdCnt++] = VFMW_H264;
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG2;
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG4;
    pCap->SupportedStd[StdCnt++] = VFMW_AVS;
#ifdef VFMW_REAL8_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_REAL8;
#endif
#ifdef VFMW_REAL9_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_REAL9;
#endif
    pCap->SupportedStd[StdCnt++] = VFMW_VC1;
    pCap->SupportedStd[StdCnt++] = VFMW_DIVX3;
#ifdef VFMW_H263_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_H263;
    pCap->SupportedStd[StdCnt++] = VFMW_SORENSON;
#endif
    pCap->SupportedStd[StdCnt++] = VFMW_VP6;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6F;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6A;
    pCap->SupportedStd[StdCnt++] = VFMW_VP8;
    pCap->SupportedStd[StdCnt++] = VFMW_MVC;
#ifdef VFMW_HEVC_SUPPORT
    pCap->SupportedStd[StdCnt++] = VFMW_HEVC;
#endif
#ifdef VFMW_VP9_SUPPORT
	pCap->SupportedStd[StdCnt++] = VFMW_VP9;
#endif
    pCap->SupportedStd[StdCnt++] = VFMW_RAW;
    pCap->SupportedStd[StdCnt++] = VFMW_USER;
    pCap->SupportedStd[StdCnt++] = VFMW_END_RESERVED;

    return;
}

/*======================================================================*/
/*   外部接口                                                           */
/*======================================================================*/

/************************************************************************
    查询解码器特性
 ************************************************************************/
SINT32 PDT_GetAttribute(ATTR_ID eAttrID, VOID *pArgs)
{
    SINT32 ret = PDT_OK;

    switch(eAttrID)
    {
        case ATTR_VDEC_CAP:
            PDT_GetVdecCapability((VDEC_CAP_S *)pArgs);
            break;

        case ATTR_OUT_FMT:
            PDT_GetOutputFormat((OUTPUT_FORMAT_S *)pArgs);
            break;

        default:
            dprint(PRN_ERROR, "%s unkown eAttrID %d\n", __func__, eAttrID);
            ret = PDT_ERR;
            break;
    }

    return ret;
}

/************************************************************************
    产品初始化
 ************************************************************************/
SINT32 PDT_Init(VDMHAL_FUN_PTR_S *pFuncPtr)
{
#ifdef ENV_SOS_KERNEL
    g_pstRegCrg = (HI_REG_CRG_S *)vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterMap(SYSTEM_REG_PHY_ADDR);
    if (g_pstRegCrg == NULL)
    {
        dprint(PRN_FATAL, "SOS map CRG reg failed!\n");

        return PDT_ERR;
    }
#endif

    PDT_InitHalInterface(pFuncPtr);

    VDMHAL_GetCharacter();

    return PDT_OK;
}


