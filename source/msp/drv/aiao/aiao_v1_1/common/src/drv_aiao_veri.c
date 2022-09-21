/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_ao.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/04/17
  Description   :
  History       :
  1.Date        : 2013/04/17
    Author      : zgjie
    Modification: Created file

******************************************************************************/

/******************************* Include Files *******************************/

/* Sys headers */
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/hardware.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_drv_module.h"

/* Drv headers */
#include "hi_drv_ao.h"
#include "hi_drv_ai.h"
#include "drv_ao_ioctl.h"
#include "drv_ao_ext.h"
#include "drv_adsp_ext.h"
#include "drv_ao_private.h"

#include "hi_audsp_aoe.h"
#include "hal_aoe.h"
#include "hal_cast.h"
#include "hal_aiao.h"

#include "drv_ao_op.h"
#include "drv_ao_track.h"
#include "audio_util.h"
#include "drv_aiao_ioctl_veri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* private state */
typedef struct
{
    HI_U32   u32Port[AIAO_INT_BUTT];

    HI_U32   u32PeriodBufSize[AIAO_INT_BUTT];
    HI_VOID* pPortDataBuf[AIAO_INT_BUTT];
} AIAO_STATE_S;

#define CHECK_AIAO_PORT_OPEN(Port) \
    do \
    { \
        if (AIAO_PORT_BUTT == g_pAiaoState->u32Port[Port]) \
        { \
            HI_ERR_AIAO("Invalid Port id 0x%x\n", Port); \
            return HI_FAILURE; \
        } \
    } while (0)

static AIAO_STATE_S g_AIAODevState;
static AIAO_STATE_S* g_pAiaoState = &g_AIAODevState;

static HI_U32 GetDfPeriondSize(AIAO_SAMPLE_RATE_E enRate, AIAO_I2S_CHNUM_E enCh, AIAO_BITDEPTH_E enBitDepth)
{
    HI_U32 uFrameSize = AIAOFrameSize(enCh, enBitDepth);
    HI_U32 uPeriondSize;

    uPeriondSize = (((HI_U32)enRate) * uFrameSize * 20) / 1000;

    if (uPeriondSize % uFrameSize)
    {
        uPeriondSize -= uPeriondSize % uFrameSize;
    }

    if (uPeriondSize % AIAO_BUFFER_SIZE_ALIGN)
    {
        uPeriondSize += AIAO_BUFFER_SIZE_ALIGN - uPeriondSize % AIAO_BUFFER_SIZE_ALIGN;
    }

    return uPeriondSize;
}

static HI_VOID AIAO_FreePortDataBuffer(AIAO_PORT_ID_E enPortID)
{
    HI_U32 Id = PORT2ID(enPortID);

    if (HI_NULL != g_pAiaoState->pPortDataBuf[Id])
    {
        HI_KFREE(HI_ID_AIAO, g_pAiaoState->pPortDataBuf[Id]);
        g_pAiaoState->pPortDataBuf[Id] = HI_NULL;
    }
}

static HI_S32 AIAO_MallocPortDataBuffer(AIAO_PORT_ID_E enPortID, AIAO_PORT_USER_CFG_S* pstConfig)
{
    HI_U32 Id = PORT2ID(enPortID);

    g_pAiaoState->u32PeriodBufSize[Id] =
        GetDfPeriondSize(pstConfig->stIfAttr.enRate,
                         pstConfig->stIfAttr.enChNum,
                         pstConfig->stIfAttr.enBitDepth);
    if (0 == g_pAiaoState->u32PeriodBufSize[Id])
    {
        HI_ERR_AIAO("port(0x%x) data buffer size is zero!", enPortID);
        return HI_FAILURE;
    }

    g_pAiaoState->pPortDataBuf[Id] = HI_KMALLOC(HI_ID_AIAO, g_pAiaoState->u32PeriodBufSize[Id], GFP_KERNEL);
    if (HI_NULL == g_pAiaoState->pPortDataBuf[Id])
    {
        HI_ERR_AIAO("malloc port data buffer failed!");
        g_pAiaoState->u32PeriodBufSize[Id] = 0;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID AIAO_VERI_Open(HI_VOID)
{
    HI_S32 Id;

    /* init aiao state */
    for (Id = 0; Id < AIAO_INT_BUTT; Id++)
    {
        g_pAiaoState->u32Port[Id] = AIAO_PORT_BUTT;
        g_pAiaoState->u32PeriodBufSize[Id] = 0;
        g_pAiaoState->pPortDataBuf[Id] = HI_NULL;
    }
}

HI_VOID AIAO_VERI_Release(HI_VOID)
{
    HI_S32 Id;

    for (Id = 0; Id < AIAO_INT_BUTT; Id++)
    {
        if (AIAO_INT_BUTT != g_pAiaoState->u32Port[Id])
        {
            HAL_AIAO_P_Close_Veri(ID2PORT(g_pAiaoState->u32Port[Id]));
            g_pAiaoState->u32Port[Id] = AIAO_PORT_BUTT;
            g_pAiaoState->u32PeriodBufSize[Id] = 0;
            if (HI_NULL != g_pAiaoState->pPortDataBuf[Id])
            {
                HI_KFREE(HI_ID_AIAO, g_pAiaoState->pPortDataBuf[Id]);
                g_pAiaoState->pPortDataBuf[Id] = HI_NULL;
            }
        }
    }
}

HI_S32 AIAO_VERI_ProcRead(struct seq_file* p, HI_VOID* v)
{
    HI_U32 Id;
    HI_S32 s32Ret;
    AIAO_PORT_STAUTS_S stStatus;
#ifdef HI_SND_HDMI_I2S_SPDIF_MUX
    AIAO_PORT_STAUTS_S stPortProcStatus;
    AIAO_PORT_ID_E enTmpPortID;
#endif

    for (Id = 0; Id < AIAO_INT_BUTT; Id++)
    {
        AIAO_PORT_ID_E enPortID = ID2PORT(g_pAiaoState->u32Port[Id]);
        if (AIAO_PORT_BUTT != enPortID)
        {
            HI_U32 u32Bytes = HAL_AIAO_P_QueryBufData(enPortID);
            HI_U32 u32Percent;

            s32Ret = HAL_AIAO_P_GetStatus( enPortID, &stStatus);
            if (HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }
#ifdef HI_SND_HDMI_I2S_SPDIF_MUX
            if (enPortID == AIAO_PORT_SPDIF_TX0)
            {
                enTmpPortID = AIAO_PORT_TX2;//SndOpGetPort(HI_UNF_SND_OUTPUTPORT_HDMI0, SND_AOP_TYPE_I2S);

                s32Ret = HAL_AIAO_P_GetStatus(enTmpPortID, &stPortProcStatus);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_AIAO("HAL_AIAO_P_GetStatus (port:%d) failed\n", (HI_U32)enPortID);
                    return s32Ret;
                }
                memcpy(&stStatus.stProcStatus, &stPortProcStatus.stProcStatus, sizeof(AIAO_PROC_STAUTS_S));
            }
#endif
            u32Percent = (u32Bytes * 100) / stStatus.stBuf.u32BUFF_SIZE;

            if ((AIAO_DIR_TX == PORT2DIR(enPortID)))
            {
                PROC_PRINT(p,
                           "%s_%s(%.2d),status(%s), Fs(%.6d), Ch(%.2d), Bit(%2d),DmaCnt(%.6u),DmaTry(%.6u),TotByte(%.6u),BufUsed(%.2u%%), PeriodSize(0x%.6x), PeriodNum(%.2d)\n",
                           (HI_CHAR*)(AIAO_MODE_TXI2S == PORT2MODE(enPortID) ? "i2s" : "spd"),
                           "tx", PORT2CHID(enPortID),
                           (HI_CHAR*)((AIAO_PORT_STATUS_START == stStatus.enStatus) ? "start" : ((AIAO_PORT_STATUS_STOP == stStatus.enStatus) ? "stop" : "stopping")),
                           stStatus.stUserConfig.stIfAttr.enRate,
                           stStatus.stUserConfig.stIfAttr.enChNum,
                           stStatus.stUserConfig.stIfAttr.enBitDepth,
                           stStatus.stProcStatus.uDMACnt,
                           stStatus.stProcStatus.uTryWriteCnt,
                           stStatus.stProcStatus.uTotalByteWrite,
                           u32Percent,
                           stStatus.stUserConfig.stBufConfig.u32PeriodBufSize,
                           stStatus.stUserConfig.stBufConfig.u32PeriodNumber);

                PROC_PRINT(p,
                           "    BufEmptyCnt(%.6u), BufEmptyWarningCnt(%.6u),BusFiFoEmptyCnt(%.6u),IfFiFoEmptyCnt(%.6u),BusTimeOutCnt(%.6u)\n\n",
                           stStatus.stProcStatus.uBufEmptyCnt, stStatus.stProcStatus.uBufEmptyWarningCnt, stStatus.stProcStatus.uBusFiFoEmptyCnt,
                           stStatus.stProcStatus.uInfFiFoEmptyCnt, stStatus.stProcStatus.uBusTimeOutCnt);
            }
            else
            {
                PROC_PRINT(p,
                           "i2s_%s(%.2d),status(%s), Fs(%.6d), Ch(%.2d), Bit(%.2d),DmaCnt(%.6u),DmaTry(%.6u),TotByte(%.6u),BufUsed(%.2u%%), PeriodSize(0x%.6x), PeriodNum(%.2d)\n",
                           "rx", PORT2CHID(enPortID),
                           (HI_CHAR*)((AIAO_PORT_STATUS_START == stStatus.enStatus) ? "start" : ((AIAO_PORT_STATUS_STOP == stStatus.enStatus) ? "stop" : "stopping")),
                           stStatus.stUserConfig.stIfAttr.enRate,
                           stStatus.stUserConfig.stIfAttr.enChNum,
                           stStatus.stUserConfig.stIfAttr.enBitDepth,
                           stStatus.stProcStatus.uDMACnt,
                           stStatus.stProcStatus.uTryWriteCnt,
                           stStatus.stProcStatus.uTotalByteRead,
                           u32Percent,
                           stStatus.stUserConfig.stBufConfig.u32PeriodBufSize,
                           stStatus.stUserConfig.stBufConfig.u32PeriodNumber);

                PROC_PRINT(p,
                           "    BufFullCnt(%.7u), BufFullWarningCnt(%.7u),BusFiFoFullCnt(:%.7u),IfFiFoFullCnt(%.7u),BusTimeOutCnt(%.7u)\n\n",
                           stStatus.stProcStatus.uBufFullCnt, stStatus.stProcStatus.uBufFullWarningCnt, stStatus.stProcStatus.uBusFiFoFullCnt,
                           stStatus.stProcStatus.uInfFiFoFullCnt, stStatus.stProcStatus.uBusTimeOutCnt);
            }
        }
    }

    return HI_SUCCESS;
}


static HI_S32 AIAO_IOCTL_GetHwCapability(struct file* file, HI_VOID* arg)
{
    AIAO_Port_GetCapability_S* Param = (AIAO_Port_GetCapability_S*)arg;
    HAL_AIAO_GetHwCapability(&Param->u32Capability);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_SetSysCrg(struct file* file, HI_VOID* arg)
{
    //HAL_AIAO_SetSysCrg(Param->u32CrgSkip);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_DBG_RWReg(struct file* file, HI_VOID* arg)
{
    AIAO_Dbg_Reg_S* pstDbgReg = (AIAO_Dbg_Reg_S*)arg;
    HAL_AIAO_DBG_RWReg(pstDbgReg);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_Open_Veri(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_Port_Open_S* Param = (AIAO_Port_Open_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);

    if (AIAO_PORT_BUTT != g_pAiaoState->u32Port[Id])
    {
        HI_ERR_AIAO("enPortID(0x%x), had already open.\n", Param->enPortID);
        return HI_FAILURE;
    }

    Param->stConfig.pIsrFunc = HAL_AIAO_P_ProcStatistics;
    s32Ret = HAL_AIAO_P_Open_Veri(Param->enPortID, &Param->stConfig);
    if (HI_SUCCESS == s32Ret)
    {
        g_pAiaoState->u32Port[Id] = Id;
        AIAO_MallocPortDataBuffer(Param->enPortID, &Param->stConfig);
        HI_INFO_AIAO("enPortID(0x%x), open success.\n", Param->enPortID);
    }
    else
    {
        HI_ERR_AIAO("enPortID(0x%x), open fail(0x%x).\n", Param->enPortID, s32Ret);
    }

    return s32Ret;
}

static HI_S32 AIAO_IOCTL_P_Close_Veri(struct file* file, HI_VOID* arg)
{
    AIAO_Port_Close_S* Param = (AIAO_Port_Close_S*)arg;

    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    HAL_AIAO_P_Close_Veri(Param->enPortID);
    AIAO_FreePortDataBuffer(Param->enPortID);
    g_pAiaoState->u32Port[Id] = AIAO_PORT_BUTT;
    HI_INFO_AIAO("enPortID(0x%x), close.\n", Param->enPortID);

    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_Start(struct file* file, HI_VOID* arg)
{
    AIAO_Port_Start_S* Param = (AIAO_Port_Start_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_Start(Param->enPortID);
}

static HI_S32 AIAO_IOCTL_P_Stop(struct file* file, HI_VOID* arg)
{
    AIAO_Port_Stop_S* Param = (AIAO_Port_Stop_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_Stop(Param->enPortID, Param->enStopMode);
}

static HI_S32 AIAO_IOCTL_P_Mute(struct file* file, HI_VOID* arg)
{
    AIAO_Port_Mute_S* Param = (AIAO_Port_Mute_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_Mute(Param->enPortID, Param->bMute);
}

static HI_S32 AIAO_IOCTL_P_SetTrackMode(struct file* file, HI_VOID* arg)
{
    AIAO_Port_TrackMode_S* Param = (AIAO_Port_TrackMode_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_SetTrackMode(Param->enPortID, Param->enTrackMode);
}

static HI_S32 AIAO_IOCTL_P_SetVolume(struct file* file, HI_VOID* arg)
{
    AIAO_Port_Volume_S* Param = (AIAO_Port_Volume_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    return HAL_AIAO_P_SetVolume(Param->enPortID, Param->u32VolumedB);
}

static HI_S32 AIAO_IOCTL_P_GetUserCongfig(struct file* file, HI_VOID* arg)
{
    AIAO_Port_GetUserConfig_S* Param = (AIAO_Port_GetUserConfig_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    return HAL_AIAO_P_GetUserCongfig(Param->enPortID, &Param->stUserConfig);
}

static HI_S32 AIAO_IOCTL_P_GetStatus(struct file* file, HI_VOID* arg)
{
    AIAO_Port_GetSTATUS_S* Param = (AIAO_Port_GetSTATUS_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_GetStatus(Param->enPortID, &Param->stStatus);
}

static HI_S32 AIAO_IOCTL_P_SelectSpdifSource(struct file* file, HI_VOID* arg)
{
    AIAO_Port_SelectSpdifSource_S* Param = (AIAO_Port_SelectSpdifSource_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_SelectSpdifSource(Param->enPortID, Param->eSrcChnId);
}

static HI_S32 AIAO_IOCTL_P_SetSpdifOutPort(struct file* file, HI_VOID* arg)
{
    AIAO_Port_SetSpdifOutPort_S* Param = (AIAO_Port_SetSpdifOutPort_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_SetSpdifOutPort(Param->enPortID, Param->bEn);
}

static HI_S32 AIAO_IOCTL_P_SetI2SSdSelect(struct file* file, HI_VOID* arg)
{
    AIAO_Port_I2SDataSel_S* Param = (AIAO_Port_I2SDataSel_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    return HAL_AIAO_P_SetI2SSdSelect(Param->enPortID, &Param->stSdSel);
}

static HI_S32 AIAO_IOCTL_P_ReadData(struct file* file, HI_VOID* arg)
{
    AIAO_Port_ReadData_S* Param = (AIAO_Port_ReadData_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    if (0 == g_pAiaoState->u32PeriodBufSize[Id] ||
        Param->u32DestSize > g_pAiaoState->u32PeriodBufSize[Id] ||
        HI_NULL == g_pAiaoState->pPortDataBuf[Id])
    {
        HI_ERR_AIAO("Param->u32DestSize(%d) > g_pAiaoState->u32PeriodBufSize[Id](%d)", Param->u32DestSize, g_pAiaoState->u32PeriodBufSize[Id]);
        return HI_FAILURE;
    }

    Param->u32ReadBytes = HAL_AIAO_P_ReadData(Param->enPortID, g_pAiaoState->pPortDataBuf[Id], Param->u32DestSize);

    if (copy_to_user(Param->pu32Dest, g_pAiaoState->pPortDataBuf[Id], Param->u32ReadBytes))
    {
        HI_ERR_AIAO("copy_to_user failed.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_WriteData(struct file* file, HI_VOID* arg)
{
    AIAO_Port_WriteData_S* Param = (AIAO_Port_WriteData_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    if (0 == g_pAiaoState->u32PeriodBufSize[Id] ||
        Param->u32SrcLen > g_pAiaoState->u32PeriodBufSize[Id] ||
        HI_NULL == g_pAiaoState->pPortDataBuf[Id])
    {
        HI_ERR_AIAO("Param->u32SrcLen(%d) > g_pAiaoState->u32PeriodBufSize[Id](%d)", Param->u32SrcLen, g_pAiaoState->u32PeriodBufSize[Id]);
        return HI_FAILURE;
    }

    if (copy_from_user(g_pAiaoState->pPortDataBuf[Id], Param->pu32Src, Param->u32SrcLen))
    {
        HI_ERR_AIAO("copy_from_user failed.\n");
        return HI_FAILURE;
    }

    Param->u32WriteBytes = HAL_AIAO_P_WriteData(Param->enPortID, g_pAiaoState->pPortDataBuf[Id], Param->u32SrcLen);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_QueryBuf(struct file* file, HI_VOID* arg)
{
    AIAO_Port_BufStatus_S* Param = (AIAO_Port_BufStatus_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    Param->u32DataSize = HAL_AIAO_P_QueryBufData(Param->enPortID);
    Param->u32FreeSize = HAL_AIAO_P_QueryBufFree(Param->enPortID);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_UpdateRptr(struct file* file, HI_VOID* arg)
{
    AIAO_Port_ReadData_S* Param = (AIAO_Port_ReadData_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);
    Param->u32ReadBytes = HAL_AIAO_P_UpdateRptr(Param->enPortID, Param->pu32Dest, Param->u32DestSize);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_P_UpdateWptr(struct file* file, HI_VOID* arg)
{
    AIAO_Port_WriteData_S* Param = (AIAO_Port_WriteData_S*)arg;
    HI_U32 Id = PORT2ID(Param->enPortID);
    CHECK_AIAO_PORT_OPEN(Id);

    Param->u32WriteBytes = HAL_AIAO_P_UpdateWptr(Param->enPortID, Param->pu32Src, Param->u32SrcLen);
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_HdmiSetAudioAttr(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_HDMI_AUDIO_ATRR_S* Param = (AIAO_HDMI_AUDIO_ATRR_S*)arg;
    HDMI_AUDIO_ATTR_S stHDMIAtr;
    HDMI_EXPORT_FUNC_S* pstHdmiFunc;

    /* Get hdmi functions */
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_HDMI, (HI_VOID**)&pstHdmiFunc);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AIAO("Get hdmi function err(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (pstHdmiFunc && pstHdmiFunc->pfnHdmiGetAoAttr)
    {
        s32Ret = (pstHdmiFunc->pfnHdmiGetAoAttr)(HI_UNF_HDMI_ID_0, &stHDMIAtr);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AIAO("hdmi function pfnHdmiGetAoAttr err(0x%x)\n", s32Ret);
            return s32Ret;
        }

        stHDMIAtr.enSoundIntf  = Param->enSoundIntf;
        stHDMIAtr.enSampleRate = Param->enSampleRate;
        stHDMIAtr.u32Channels  = Param->u32Channels;
        stHDMIAtr.enBitDepth   = Param->enBitDepth;

        s32Ret = (pstHdmiFunc->pfnHdmiAudioChange)(HI_UNF_HDMI_ID_0, &stHDMIAtr);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AIAO("hdmi function pfnHdmiAudioChange err:%#x!\n", s32Ret);
            return s32Ret;
        }
    }
    else
    {
        HI_ERR_AIAO("hdmi function dont support pfnHdmiGetAoAttr err\n");
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

#ifdef HI_AIAO_TIMER_SUPPORT
static HI_S32 AIAO_IOCTL_TimerCreate(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_Timer_Create_S* Param = (AIAO_Timer_Create_S*)arg;
    HI_U32 Id = TIMER2ID(Param->enTimerID);

    if (AIAO_PORT_BUTT != g_pAiaoState->u32Port[Id])
    {
        HI_ERR_AIAO("enPortID(0x%x), had open\n", Param->enTimerID);
       return HI_FAILURE;
    }

    Param->pTimerIsrFunc = HAL_AIAO_T_TIMERProcess;
    s32Ret = HAL_AIAO_T_Create(Param->enTimerID, Param);
    if (HI_SUCCESS == s32Ret)
    {
        g_pAiaoState->u32Port[Id] = Id;
    }
    else
    {
        HI_ERR_AIAO("TimerID(0x%x), create timer fail(0x%x).\n", Param->enTimerID, s32Ret);
    }

    return s32Ret;
}

static HI_S32 AIAO_IOCTL_TimerDestory(struct file* file, HI_VOID* arg)
{
    AIAO_Timer_Destroy_S* Param = (AIAO_Timer_Destroy_S*)arg;
    HI_U32 Id = TIMER2ID(Param->enTimerID);
    CHECK_AIAO_PORT_OPEN(Id);
    HAL_AIAO_T_Destroy(Param->enTimerID);
    g_pAiaoState->u32Port[Id] = AIAO_PORT_BUTT;
    return HI_SUCCESS;
}

static HI_S32 AIAO_IOCTL_TimerSetAttr(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_TIMER_Attr_S* Param = (AIAO_TIMER_Attr_S*)arg;
    HI_U32 Id = TIMER2ID(Param->enTimerID);
    CHECK_AIAO_PORT_OPEN(Id);

    s32Ret = HAL_AIAO_T_SetTimerAttr(Param->enTimerID, Param);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AIAO("enPortID(0x%x), HAL_AIAO_T_SetTimerAttr fail(0x%x).\n", Param->enTimerID, s32Ret);
    }

    return s32Ret;
}

static HI_S32 AIAO_IOCTL_TimerSetEnable(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_TIMER_Enable_S* Param = (AIAO_TIMER_Enable_S*)arg;
    HI_U32 Id = TIMER2ID(Param->enTimerID);
    CHECK_AIAO_PORT_OPEN(Id);

    s32Ret = HAL_AIAO_T_SetTimerEnable(Param->enTimerID, Param->bEnable);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AIAO("enPortID(0x%x), HAL_AIAO_T_SetTimerEnable fail(0x%x).\n", Param->enTimerID, s32Ret);
    }

    return s32Ret;
}

static HI_S32 AIAO_IOCTL_TimerGetStatus(struct file* file, HI_VOID* arg)
{
    HI_S32 s32Ret;
    AIAO_TIMER_Status_S* Param = (AIAO_TIMER_Status_S*)arg;
    HI_U32 Id = TIMER2ID(Param->enTimerID);
    CHECK_AIAO_PORT_OPEN(Id);

    s32Ret = HAL_AIAO_T_GetStatus(Param->enTimerID, Param);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AIAO("enPortID(0x%x), CMD_AIAO_TIMER_GETSTATUS fail(0x%x).\n", Param->enTimerID, s32Ret);
    }

    return s32Ret;
}
#endif

static const struct
{
    HI_U32 u32Cmd;
    HI_S32 (*ioctl)(struct file* file, HI_VOID* arg);
} g_fnAiaoIoctl[CMD_ID_AIAO_BUTT] =
{
    [CMD_ID_AIAO_GET_CAPABILITY]          = {CMD_AIAO_GET_CAPABILITY          , AIAO_IOCTL_GetHwCapability},
    [CMD_ID_AIAO_SET_SYSCRG]              = {CMD_AIAO_SET_SYSCRG              , AIAO_IOCTL_SetSysCrg},
    [CMD_ID_AIAO_RW_REGISTER]             = {CMD_AIAO_RW_REGISTER             , AIAO_IOCTL_DBG_RWReg},
    [CMD_ID_AIAO_PORT_OPEN]               = {CMD_AIAO_PORT_OPEN               , AIAO_IOCTL_P_Open_Veri},
    [CMD_ID_AIAO_PORT_CLOSE]              = {CMD_AIAO_PORT_CLOSE              , AIAO_IOCTL_P_Close_Veri},
    [CMD_ID_AIAO_PORT_START]              = {CMD_AIAO_PORT_START              , AIAO_IOCTL_P_Start},
    [CMD_ID_AIAO_PORT_STOP]               = {CMD_AIAO_PORT_STOP               , AIAO_IOCTL_P_Stop},
    [CMD_ID_AIAO_PORT_MUTE]               = {CMD_AIAO_PORT_MUTE               , AIAO_IOCTL_P_Mute},
    [CMD_ID_AIAO_PORT_TRACKMODE]          = {CMD_AIAO_PORT_TRACKMODE          , AIAO_IOCTL_P_SetTrackMode},
    [CMD_ID_AIAO_PORT_VOLUME]             = {CMD_AIAO_PORT_VOLUME             , AIAO_IOCTL_P_SetVolume},
    [CMD_ID_AIAO_PORT_GET_USERCONFIG]     = {CMD_AIAO_PORT_GET_USERCONFIG     , AIAO_IOCTL_P_GetUserCongfig},
    [CMD_ID_AIAO_PORT_GET_STATUS]         = {CMD_AIAO_PORT_GET_STATUS         , AIAO_IOCTL_P_GetStatus},

    [CMD_ID_AIAO_PORT_SEL_SPDIFOUTSOURCE] = {CMD_AIAO_PORT_SEL_SPDIFOUTSOURCE , AIAO_IOCTL_P_SelectSpdifSource},
    [CMD_ID_AIAO_PORT_SET_SPDIFOUTPORT]   = {CMD_AIAO_PORT_SET_SPDIFOUTPORT   , AIAO_IOCTL_P_SetSpdifOutPort},
    [CMD_ID_AIAO_PORT_SET_I2SDATASEL]     = {CMD_AIAO_PORT_SET_I2SDATASEL     , AIAO_IOCTL_P_SetI2SSdSelect},

    [CMD_ID_AIAO_PORT_READ_DATA]          = {CMD_AIAO_PORT_READ_DATA          , AIAO_IOCTL_P_ReadData},
    [CMD_ID_AIAO_PORT_WRITE_DATA]         = {CMD_AIAO_PORT_WRITE_DATA         , AIAO_IOCTL_P_WriteData},
    [CMD_ID_AIAO_PORT_PREPARE_DATA]       = {CMD_AIAO_PORT_PREPARE_DATA       , AIAO_IOCTL_P_WriteData},
    [CMD_ID_AIAO_PORT_QUERY_BUF]          = {CMD_AIAO_PORT_QUERY_BUF          , AIAO_IOCTL_P_QueryBuf},
    [CMD_ID_AIAO_PORT_UPDATE_RPTR]        = {CMD_AIAO_PORT_UPDATE_RPTR        , AIAO_IOCTL_P_UpdateRptr},
    [CMD_ID_AIAO_PORT_UPDATE_WPTR]        = {CMD_AIAO_PORT_UPDATE_WPTR        , AIAO_IOCTL_P_UpdateWptr},

    [CMD_ID_AIAO_HDMI_SETAUDIO_ATTR]      = {CMD_AIAO_HDMI_SETAUDIO_ATTR      , AIAO_IOCTL_HdmiSetAudioAttr},

#ifdef HI_AIAO_TIMER_SUPPORT
    [CMD_ID_AIAO_TIMER_CREATE]            = {CMD_AIAO_TIMER_CREATE            , AIAO_IOCTL_TimerCreate},
    [CMD_ID_AIAO_TIMER_DESTROY]           = {CMD_AIAO_TIMER_DESTROY           , AIAO_IOCTL_TimerDestory},
    [CMD_ID_AIAO_TIMER_SETATTR]           = {CMD_AIAO_TIMER_SETATTR           , AIAO_IOCTL_TimerSetAttr},
    [CMD_ID_AIAO_TIMER_SETENABLE]         = {CMD_AIAO_TIMER_SETENABLE         , AIAO_IOCTL_TimerSetEnable},
    [CMD_ID_AIAO_TIMER_GETSTATUS]         = {CMD_AIAO_TIMER_GETSTATUS         , AIAO_IOCTL_TimerGetStatus},
#endif
};

HI_S32 AIAO_VERI_ProcessCmd(struct inode* inode, struct file* file, HI_U32 u32Cmd, HI_VOID* arg)
{
    HI_U32 u32CmdType = _IOC_TYPE(u32Cmd);
    HI_U32 u32CmdId = _IOC_NR(u32Cmd);

    if (HI_ID_AIAO == u32CmdType)
    {
        if (CMD_ID_AIAO_BUTT <= u32CmdId)
        {
            HI_WARN_AO("unknown cmd: 0x%x\n", u32Cmd);
            return HI_ERR_AO_INVALID_PARA;
        }

        if (u32Cmd != g_fnAiaoIoctl[u32CmdId].u32Cmd)
        {
            HI_WARN_AO("unknown cmd: 0x%x\n", u32Cmd);
            return HI_ERR_AO_INVALID_PARA;
        }

        if (HI_NULL == g_fnAiaoIoctl[u32CmdId].ioctl)
        {
            return HI_ERR_AO_NOTSUPPORT;
        }

        return (g_fnAiaoIoctl[u32CmdId].ioctl)(file, arg);
    }
    else
    {
        HI_WARN_AIAO("Unknown CMD Type.\n");
        return HI_ERR_AO_INVALID_PARA;
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
