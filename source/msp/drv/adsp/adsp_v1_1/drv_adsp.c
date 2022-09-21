/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_adsp.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/04/17
  Description   :
  History       :
  1.Date        : 2013/04/17
    Author      : zgjie
    Modification: Created file

******************************************************************************/

#include <linux/string.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_reg_common.h"

/* Drv headers */
#include "drv_adsp_private.h"
#include "drv_adsp_ext.h"
#include "hi_audsp_common.h"
#include "hi_audsp_aoe.h"
#include "hi_audsp_aflt.h"

#include "drv_adsp_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct
{
    ADSP_EXPORT_FUNC_S      stExtFunc;      /* ADSP extenal functions */
} ADSP_GLOBAL_PARAM_S;

static HI_S32 ADSP_LoadFirmware(ADSP_CODEID_E u32DspCodeId);
static HI_S32 ADSP_UnLoadFirmware(ADSP_CODEID_E u32DspCodeId);
static HI_S32 ADSP_GetAoeFwmInfo(ADSP_CODEID_E u32DspCodeId, AOE_FW_INFO_S* pstInfo);

static ADSP_GLOBAL_PARAM_S s_stAdspDrv =
{
    .stExtFunc                     =
    {
        .pfnADSP_LoadFirmware      = ADSP_LoadFirmware,
        .pfnADSP_UnLoadFirmware    = ADSP_UnLoadFirmware,
        .pfnADSP_GetAoeFwmInfo     = ADSP_GetAoeFwmInfo,
    }
};

#ifdef HI_SND_DSP_SUPPORT
static volatile S_ADSP_CHN_REGS_TYPE* g_pADSPSysCrg = HI_NULL;

static ADSP_AOESYS_CMD_RET_E  ADSP_AOE_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL ADSP_SYSCTRL;

    for (loop = 0; loop < DSP_ACK_TIME; loop++)
    {
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.aoe_cmd_done)
        {
            return (ADSP_AOESYS_CMD_RET_E)ADSP_SYSCTRL.bits.aoe_cmd_return_value;
        }
        msleep(1);
    }

    return ADSP_AOE_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_AOE_SetCmd(ADSP_AOESYS_CMD_E newcmd)
{
    ADSP_AOESYS_CMD_RET_E Ack;
    U_ADSP_CTRL ADSP_SYSCTRL;
    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
        case ADSP_AOE_CMD_START:
        case ADSP_AOE_CMD_STOP:
            ADSP_SYSCTRL.bits.aoe_cmd = newcmd;
            break;

        default:
            return HI_SUCCESS;
    }

    ADSP_SYSCTRL.bits.aoe_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 = ADSP_SYSCTRL.u32;

    Ack = ADSP_AOE_Ack();
    if (ADSP_AOE_CMD_DONE != Ack)
    {
        HI_ERR_ADSP("ADSP_AOE SetCmd(0x%x) failed(0x%x)\n", newcmd, Ack);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#ifdef __DPT__
static ADSP_AFLTSYS_CMD_RET_E  ADSP_AFLT_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL ADSP_SYSCTRL;

    for (loop = 0; loop < DSP_ACK_TIME; loop++)
    {
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.aflt_cmd_done)
        {
            return (ADSP_AFLTSYS_CMD_RET_E)ADSP_SYSCTRL.bits.aflt_cmd_return_value;
        }
        msleep(1);
    }

    return ADSP_AFLT_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_AFLT_SetCmd(ADSP_AFLTSYS_CMD_E newcmd)
{
    ADSP_AFLTSYS_CMD_RET_E Ack;
    U_ADSP_CTRL ADSP_SYSCTRL;
    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
        case ADSP_AFLT_CMD_START:
        case ADSP_AFLT_CMD_STOP:
            ADSP_SYSCTRL.bits.aflt_cmd = newcmd;
            break;

        default:
            return HI_SUCCESS;
    }

    ADSP_SYSCTRL.bits.aflt_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 =  ADSP_SYSCTRL.u32;

    Ack = ADSP_AFLT_Ack();
    if (ADSP_AFLT_CMD_DONE != Ack)
    {
        HI_ERR_ADSP("ADSP_AFLT SetCmd(0x%x) failed(0x%x)\n", newcmd, Ack);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif

static ADSP_SYSCOM_CMD_RET_E ADSP_SYS_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL ADSP_SYSCTRL;

    for (loop = 0; loop < DSP_ACK_TIME; loop++)
    {
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.sys_cmd_done)
        {
            return (ADSP_SYSCOM_CMD_RET_E)ADSP_SYSCTRL.bits.sys_cmd_return_value;
        }
        msleep(1);
    }

    return ADSP_SYSCOM_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_E newcmd, HI_BOOL bBlock)
{
    ADSP_SYSCOM_CMD_RET_E Ack;
    U_ADSP_CTRL ADSP_SYSCTRL;

    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
        case ADSP_SYSCOM_CMD_START:
        case ADSP_SYSCOM_CMD_STOP:
            ADSP_SYSCTRL.bits.sys_cmd = newcmd;
            break;

        default:
            HI_ERR_ADSP("unknow Cmd(0x%x)",newcmd);
            return HI_FAILURE;
    }

    ADSP_SYSCTRL.bits.sys_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 = ADSP_SYSCTRL.u32;
    if (HI_TRUE == bBlock)
    {
        Ack = ADSP_SYS_Ack();
        if (ADSP_SYSCOM_CMD_DONE != Ack)
        {
            HI_ERR_ADSP("ADSP_SYS SetCmd(0x%x) failed(0x%x)\n", newcmd, Ack);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 ADSPSysRegInit(HI_VOID)
{
    volatile U_ADSP_CTRL ADSP_SYSCTRL;

    if (HI_NULL == g_stDspFwInfo.pAoeRegVirAddr)
    {
        HI_ERR_ADSP("DSP share sram ptr is NULL\n");
        return HI_FAILURE;
    }

    g_pADSPSysCrg = (volatile S_ADSP_CHN_REGS_TYPE*)(g_stDspFwInfo.pAoeRegVirAddr + DSP0_SHARESRAM_SYS_OFFSET);

    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
    ADSP_SYSCTRL.bits.aoe_cmd = ADSP_AOE_CMD_BUTT;
    ADSP_SYSCTRL.bits.aflt_cmd = ADSP_AFLT_CMD_BUTT;
    ADSP_SYSCTRL.bits.sys_cmd = ADSP_SYSCOM_CMD_BUTT;
    ADSP_SYSCTRL.bits.aoe_cmd_done = 1;
    ADSP_SYSCTRL.bits.aflt_cmd_done = 1;
    ADSP_SYSCTRL.bits.sys_cmd_done = 1;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 = ADSP_SYSCTRL.u32;

    return HI_SUCCESS;
}

static HI_VOID ADSPSysRegDeInit(HI_VOID)
{
    g_pADSPSysCrg = HI_NULL;
}

static HI_S32 ADSP_AOECreate(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HAL_ADSP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("call HAL_DSP_Init failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = ADSPSysRegInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("call ADSPSysRegInit failed(0x%x)\n", s32Ret);
        HAL_ADSP_DeInit();
        return s32Ret;
    }

    s32Ret = ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_START, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("call ADSP_SYS_SetCmd failed(0x%x)\n", s32Ret);
        ADSPSysRegDeInit();
        HAL_ADSP_DeInit();
        return s32Ret;
    }

    HI_INFO_ADSP("DSPPowerOn success.\n");

#if (1 == HI_PROC_SUPPORT)
    s32Ret = ADSP_ProcInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("ADSP_ProcInit failed(0x%x)\n", s32Ret);
        ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_STOP, HI_FALSE);
        ADSPSysRegDeInit();
        HAL_ADSP_DeInit();
        return s32Ret;
    }
#endif

    s32Ret = ADSP_AOE_SetCmd(ADSP_AOE_CMD_START);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("ADSP_AOE_SetCmd failed(0x%x)\n", s32Ret);
#if (1 == HI_PROC_SUPPORT)
        ADSP_ProcDeInit();
#endif
        ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_STOP, HI_FALSE);
        ADSPSysRegDeInit();
        HAL_ADSP_DeInit();
    }

    return s32Ret;
}

static HI_S32 ADSP_AOEDestory(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = ADSP_AOE_SetCmd(ADSP_AOE_CMD_STOP);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("ADSP_AOE_SetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

#if (1 == HI_PROC_SUPPORT)
    ADSP_ProcDeInit();
#endif

    ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_STOP, HI_FALSE);
    ADSPSysRegDeInit();
    HAL_ADSP_DeInit();

    return s32Ret;
}

#else

extern HI_S32 AOE_SwEngineCreate(HI_VOID* pDspReg);
extern HI_S32 AOE_SwEngineDestory(HI_VOID);

static HI_S32 ADSP_AOEDestory(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = AOE_SwEngineDestory();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADSP("AOE_SwEngineDestory failed(0x%x)\n", s32Ret);
    }

#if (1 == HI_PROC_SUPPORT)
    ADSP_ProcDeInit();
#endif
    HAL_ADSP_DeInit();

    HI_INFO_ADSP("AOE_SwEngineDestory success.\n");

    return s32Ret;
}

static HI_S32 ADSP_AOECreate(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HAL_ADSP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("call HAL_DSP_Init failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

#if (1 == HI_PROC_SUPPORT)
    s32Ret = ADSP_ProcInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADSP("ADSP_ProcInit failed(0x%x)\n", s32Ret);
        HAL_ADSP_DeInit();
        return s32Ret;
    }
#endif

    s32Ret = AOE_SwEngineCreate(g_stDspFwInfo.pAoeRegVirAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADSP("AOE_SwEngineCreate failed(0x%x)\n", s32Ret);
#if (1 == HI_PROC_SUPPORT)
        ADSP_ProcDeInit();
#endif
        HAL_ADSP_DeInit();
    }

    HI_INFO_ADSP("AOE_SwEngineCreate success.\n");

    return s32Ret;
}
#endif

#ifdef __DPT__
#if defined (HI_SND_AFLT_SWSIMULATE_SUPPORT)
extern HI_S32 AFLT_SwEngineCreate(HI_VOID);
extern HI_S32 AFLT_SwEngineDestory(HI_VOID);

static HI_S32 ADSP_AFLTDestory(HI_VOID)
{
    return AFLT_SwEngineDestory();
}

static HI_S32 ADSP_AFLTCreate(HI_VOID)
{
    return AFLT_SwEngineCreate();
}

#elif defined (HI_SND_DSP_SUPPORT)

static HI_S32 ADSP_AFLTDestory(HI_VOID)
{
    return ADSP_AFLT_SetCmd(ADSP_AFLT_CMD_STOP);
}

static HI_S32 ADSP_AFLTCreate(HI_VOID)
{
    return ADSP_AFLT_SetCmd(ADSP_AFLT_CMD_START);
}
#endif
#endif

static HI_S32 ADSP_LoadFirmware(ADSP_CODEID_E u32DspCodeId)
{
    HI_S32 s32Ret = HI_FAILURE;

    switch (u32DspCodeId)
    {
        case ADSP_CODE_AOE:
            s32Ret = ADSP_AOECreate();
            break;

#ifdef __DPT__
        case ADSP_CODE_AFLT:
            s32Ret = ADSP_AFLTCreate();
            break;
#endif

        default:
            HI_ERR_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
            break;
    }

    return s32Ret;
}

static HI_S32 ADSP_UnLoadFirmware(ADSP_CODEID_E u32DspCodeId)
{
    HI_S32 s32Ret = HI_SUCCESS;

    switch (u32DspCodeId)
    {
        case ADSP_CODE_AOE:
            s32Ret = ADSP_AOEDestory();
            break;

#ifdef __DPT__
        case ADSP_CODE_AFLT:
            s32Ret = ADSP_AFLTDestory();
            break;
#endif

        default:
            HI_WARN_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
            break;
    }

    return s32Ret;
}

static HI_S32 ADSP_GetAoeFwmInfo(ADSP_CODEID_E u32DspCodeId, AOE_FW_INFO_S* pstInfo)
{
    switch (u32DspCodeId)
    {
        case ADSP_CODE_AOE:
            memcpy(pstInfo, &g_stDspFwInfo, sizeof(AOE_FW_INFO_S));
            return HI_SUCCESS;

        default:
            HI_ERR_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
            return HI_FAILURE;
    }
}

HI_S32 ADSP_DRV_Suspend(PM_BASEDEV_S* dev, pm_message_t state)
{
    HI_PRINT("ADSP suspend OK\n");
    return HI_SUCCESS;
}

HI_S32 ADSP_DRV_Resume(PM_BASEDEV_S* dev)
{
    HI_PRINT("ADSP resume OK\n");
    return HI_SUCCESS;
}

HI_S32 ADSP_DRV_Init(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_ADSP, "HI_ADSP", (HI_VOID*)&s_stAdspDrv.stExtFunc);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("HI_DRV_MODULE_Register adsp fail(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_VOID ADSP_DRV_Exit(HI_VOID)
{
    HI_DRV_MODULE_UnRegister(HI_ID_ADSP);
}

HI_S32 HI_DRV_ADSP_Init(HI_VOID)
{
    return ADSP_DRV_Init();
}

HI_VOID HI_DRV_ADSP_DeInit(HI_VOID)
{
    ADSP_DRV_Exit();
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
