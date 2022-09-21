#include <linux/string.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>

/* Drv headers */
#include "drv_adsp_private.h"
#include "drv_adsp_ext.h"
#include "hi_audsp_common.h"
#include "hi_audsp_aoe.h"
#include "hi_audsp_aflt.h"

#include "drv_adsp_hal.h"

static HI_VOID* g_pAoeRegAddr = HI_NULL;
#ifdef __DPT__
static HI_VOID* g_pAfltRegAddr = HI_NULL;
#endif

static const HI_U32 ADSP_AOE_RateProc(HI_U32 u32Rate)
{
    HI_U32 g_u32RateTab[] =
    {
        8000,
        11025,
        12000,
        16000,
        22050,
        24000,
        32000,
        44100,
        48000,
        88200,
        96000,
        176400,
        192000,
    };

    if (u32Rate < sizeof(g_u32RateTab) / sizeof(g_u32RateTab[0]))
    {
        return g_u32RateTab[u32Rate];
    }

    return g_u32RateTab[0];
}

static const HI_U32 ADSP_AOE_ChProc(HI_U32 ch)
{
    switch (ch)
    {
        case 0x00:
            return 1;
        case 0x01:
            return 2;
        case 0x03:
            return 8;
        default:
            return 0;
    }
}

static const HI_U32 ADSP_AOE_WidthProc(HI_U32 width)
{
    switch (width)
    {
        case 0x00:
            return 8;
        case 0x01:
            return 16;
        case 0x02:
            return 24;
        default:
            return 0;
    }
}

static const HI_CHAR*   ADSP_AOE_StatusName(HI_U32 u32Cmd, HI_U32 u32Done)
{
    const HI_CHAR* apcName[4] =
    {
        "start",
        "stop",
        "pause",
        "flush",
    };

    if (u32Done == 0 || u32Cmd >= 4)
    {
        return "invalid";
    }

    return apcName[u32Cmd];
}

#ifdef __DPT__
static const HI_CHAR* ADSP_AFLT_CmdName(AFLT_CMD_E enCmd)
{
    const HI_CHAR* apcName[AFLT_CMD_BUTT] =
    {
        "Create",
        "Destroy",
        "Start",
        "Stop",
        "SetParam",
        "GetParam",
        "SetConfig",
        "GetConfig",
        "RestoreSetting",
        "StoreSetting",
        "InitInbuf",
        "DeInitInbuf",
        "InitOutbuf",
        "DeInitOutbuf",
    };

    if (enCmd < AFLT_CMD_BUTT)
    {
        return apcName[enCmd];
    }

    return "UnknownCmd";
}

static const HI_CHAR* ADSP_AFLT_CompName(AFLT_COMPONENT_ID_E enComp)
{
    const HI_CHAR* apcName[AFLT_BUTT] =
    {
        "SWSEffect",
        "SRS3DEffect",
        "DBXEffect",
        "SWS3DEffect",
        "Custom1Effect"
    };

    if (enComp < AFLT_BUTT)
    {
        return apcName[enComp];
    }

    return "UnknownComp";
}
#endif

static const HI_U32 ADSP_BufUsedSizeProc(HI_U32 u32Size, HI_U32 u32ReadPtr, HI_U32 u32WritePtr)
{
    if (u32ReadPtr <= u32WritePtr)
    {
        return u32WritePtr - u32ReadPtr;
    }
    else
    {
        return u32Size - (u32ReadPtr - u32WritePtr);
    }
}

static const HI_U32 ADSP_BufUsedPercProc(HI_U32 u32Size, HI_U32 u32UsedSize)
{
    if (0 == u32Size)
    {
        return 0;
    }
    else
    {
        return u32UsedSize * 100 / u32Size;
    }
}

static const HI_U32 ADSP_BufLatencyMsProc(HI_U32 u32UsedSize, HI_U32 u32FrameSize, HI_U32 u32Rate)
{
    if (0 == u32FrameSize || 0 == u32Rate)
    {
        return 0;
    }
    else
    {
        return (u32UsedSize / u32FrameSize) * 1000 / u32Rate;
    }
}

static const HI_U32 ADSP_FrameSizeProc(HI_U32 u32BitWidth, HI_U32 u32Channel)
{
    if (16 == u32BitWidth)
    {
        return u32Channel * sizeof(HI_S16);
    }
    else
    {
        return u32Channel * sizeof(HI_S32);
    }
}

static HI_VOID ADSP_AOE_Proc_ReadKaraoke(struct seq_file* file)
{
    HI_VOID* pRptr = HI_NULL;
    HI_VOID* pWptr = HI_NULL;
    HI_U32 u32UsedSize = 0;
    HI_U32 u32FrameSize = 0;
    HI_U32 Aip = 0;
    HI_U32 Aop = 0; // read aop0
    S_AIP_REGS_TYPE* pAipReg = HI_NULL;
    S_AOP_REGS_TYPE* pAopReg = HI_NULL;

    for (Aip = 0; Aip < AOE_MAX_AIP_NUM; Aip++)
    {
        pAipReg = (S_AIP_REGS_TYPE*)(g_pAoeRegAddr + AOE_AIP_REG_OFFSET + Aip * sizeof(S_AIP_REGS_TYPE));

        /* find karaoke aip */
        if (1 == pAipReg->AIP_FIFO_ATTR.bits.fifo_bypass)
        {
            break;
        }
    }

    if (AOE_MAX_AIP_NUM == Aip)
    {
        return;
    }

    if (1 == pAipReg->AIP_BUF_SIZE.bits.buff_flag)
    {
#ifdef HI_SND_DSP_SUPPORT
        pRptr = adsp_ioremap(pAipReg->AIP_BUF_RPTR.ADDR_LOW, sizeof(HI_U32)); // TODO: unmap
        pWptr = adsp_ioremap(pAipReg->AIP_BUF_WPTR.ADDR_LOW, sizeof(HI_U32));

#else
        //AIP 目前仅支持间接寻址，即:pAipReg->AIP_BUF_SIZE.bits.buff_flag = 0
        ADSP_ReadAddr(pAipReg->AIP_BUF_RPTR, pRptr);
        ADSP_ReadAddr(pAipReg->AIP_BUF_WPTR, pWptr);
#endif
    }
    else
    {
        pRptr = (HI_VOID*)(&pAipReg->AIP_BUF_RPTR.ADDR_LOW);
        pWptr = (HI_VOID*)(&pAipReg->AIP_BUF_WPTR.ADDR_LOW);
    }
    u32UsedSize = ADSP_BufUsedSizeProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, *(HI_U32*)pRptr, *(HI_U32*)pWptr);
    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision), ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch));
    PROC_PRINT( file,
                "Karaoke     :Aip(%d), Size/Used/Latency(0x%.6x/%d%%/%dms)\n",
                Aip,
                pAipReg->AIP_BUF_SIZE.bits.buff_size,
                ADSP_BufUsedPercProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, u32UsedSize),
                ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs))
              );

    pAopReg = (S_AOP_REGS_TYPE*)(g_pAoeRegAddr + AOE_AOP_REG_OFFSET + Aop * sizeof(S_AOP_REGS_TYPE));
    if (1 == pAopReg->AOP_BUF_SIZE.bits.buff_flag)
    {
#ifdef HI_SND_DSP_SUPPORT
        pRptr = adsp_ioremap(pAopReg->AOP_BUF_RPTR.ADDR_LOW, sizeof(HI_U32)); // TODO: unmap
        pWptr = adsp_ioremap(pAopReg->AOP_BUF_WPTR.ADDR_LOW, sizeof(HI_U32));
#else
        ADSP_ReadAddr(pAopReg->AOP_BUF_RPTR, pRptr);
        ADSP_ReadAddr(pAopReg->AOP_BUF_WPTR, pWptr);
#endif
    }
    else  //Aop is Cast
    {
        pRptr = (HI_VOID*)(&pAopReg->AOP_BUF_RPTR);
        pWptr = (HI_VOID*)(&pAopReg->AOP_BUF_WPTR);
    }
    u32UsedSize = ADSP_BufUsedSizeProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, *(HI_U32*)pRptr, *(HI_U32*)pWptr);
    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision), ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch));
    PROC_PRINT( file,
                "            :Aop(%d), Size/Used/Latency(0x%.4x/%d%%/%dms)\n",
                Aop,
                pAopReg->AOP_BUF_SIZE.bits.buff_size,
                ADSP_BufUsedPercProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, u32UsedSize),
                ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs))
              );
}

static HI_VOID ADSP_AOE_Proc_ReadAip(struct seq_file* file, S_MIXER_REGS_TYPE* pEngineReg)
{
    HI_U32 Aip = 0;
    HI_U32 u32UsedSize = 0;
    HI_U32 u32FrameSize = 0;
    HI_VOID* pRptr = HI_NULL;
    HI_VOID* pWptr = HI_NULL;
    HI_VOID* pTmpAddr = HI_NULL;
    S_AIP_REGS_TYPE* pAipReg = HI_NULL;

    for (Aip = 0; Aip < AOE_MAX_AIP_NUM; Aip++)
    {
        if (!((pEngineReg->ENGINE_MIX_SRC.bits.aip_fifo_ena) & (1L << Aip)))
        {
            continue;
        }
        pAipReg = (S_AIP_REGS_TYPE*)(g_pAoeRegAddr + AOE_AIP_REG_OFFSET + Aip * sizeof(S_AIP_REGS_TYPE));
        PROC_PRINT( file,
                    "Aip(%d)      :Status(%s), Mute(%s), Vol(%ddB/%ddB), Prescale(%s%d.%ddB), ChMode(%d), SpeedAdjCnt(%d)\n",
                    Aip,
                    ADSP_AOE_StatusName(pAipReg->AIP_CTRL.bits.cmd, pAipReg->AIP_CTRL.bits.cmd_done),
                    (0 == pAipReg->AIP_EXT_CTRL.bits.mute) ? "Off" : "On",
                    (HI_S32)(pAipReg->AIP_EXT_CTRL.bits.volume_l) - 0x79,
                    (HI_S32)(pAipReg->AIP_EXT_CTRL.bits.volume_r) - 0x79,
                    (0x79 == pAipReg->AIP_EXT2_CTRL.bits.prescale_int && 1 == pAipReg->AIP_EXT2_CTRL.bits.prescale_dec_dir) ? "-" : "",
                    (HI_S32)(pAipReg->AIP_EXT2_CTRL.bits.prescale_int) - 0x79,
                    pAipReg->AIP_EXT2_CTRL.bits.prescale_dec * 125,
                    pAipReg->AIP_EXT_CTRL.bits.channel_mode,
                    pAipReg->AIP_FSADJ_CNT);

        if (1 == pAipReg->AIP_BUF_SIZE.bits.buff_flag)
        {
#ifdef HI_SND_DSP_SUPPORT
            pRptr = adsp_ioremap(pAipReg->AIP_BUF_RPTR.ADDR_LOW, sizeof(HI_U32));
            pWptr = adsp_ioremap(pAipReg->AIP_BUF_WPTR.ADDR_LOW, sizeof(HI_U32));
#else
            //AIP 目前仅支持间接寻址，即:pAipReg->AIP_BUF_SIZE.bits.buff_flag = 0
            ADSP_ReadAddr(pAipReg->AIP_BUF_WPTR, pRptr);
            ADSP_ReadAddr(pAipReg->AIP_BUF_RPTR, pWptr);
#endif
        }
        else
        {
            pRptr = (HI_VOID*)(&pAipReg->AIP_BUF_RPTR.ADDR_LOW);
            pWptr = (HI_VOID*)(&pAipReg->AIP_BUF_WPTR.ADDR_LOW);
        }
        u32UsedSize  = ADSP_BufUsedSizeProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, *((HI_U32*)pRptr), *((HI_U32*)pWptr));
        u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision), ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch));
        ADSP_ReadAddr(pAipReg->AIP_BUF_ADDR, pTmpAddr);
        PROC_PRINT( file,
                    "            :Buff Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%p), Size/Used/Latency(0x%.6x/%d%%/%dms), Rptr/Wptr(0x%.6x/0x%.6x)\n",
                    (0 == pAipReg->AIP_BUFF_ATTR.bits.aip_format) ? "pcm" : "iec61937",
                    ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs),
                    ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch),
                    ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision),
                    pTmpAddr,
                    pAipReg->AIP_BUF_SIZE.bits.buff_size,
                    ADSP_BufUsedPercProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, u32UsedSize),
                    ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs)),
                    *((HI_U32*)pRptr),
                    *((HI_U32*)pWptr));

        if (pEngineReg->ENGINE_ATTR.bits.format == 0)  // LPCM
        {
            u32UsedSize = ADSP_BufUsedSizeProc(pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size, pAipReg->AIP_FIFO_RPTR, pAipReg->AIP_FIFO_WPTR);
            u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_precision), ADSP_AOE_ChProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_ch));
            PROC_PRINT( file,
                        "            :Fifo Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%.8x), Size/Used/Latency/Underflow(0x%.4x/%d%%/%dms/%d), Rptr/Wptr(0x%.4x/0x%.4x)\n",
                        (0 == pAipReg->AIP_FIFO_ATTR.bits.fifo_format) ? "pcm" : "iec61937",
                        ADSP_AOE_RateProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_fs),
                        ADSP_AOE_ChProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_ch),
                        ADSP_AOE_WidthProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_precision),
                        pAipReg->AIP_FIFO_ADDR,
                        pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size,
                        ADSP_BufUsedPercProc(pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size, u32UsedSize),
                        ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_fs)),
                        pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_underflow_cnt,
                        pAipReg->AIP_FIFO_RPTR,
                        pAipReg->AIP_FIFO_WPTR);
        }
    }
}

static HI_VOID ADSP_AOE_Proc_ReadAopCast(struct seq_file* file, HI_U32 Aop)
{
    HI_U32 u32CastId;
    HI_U32 u32UsedSize = 0;
    HI_U32 u32FrameSize = 0;
    S_AOP_REGS_TYPE* pAopReg = HI_NULL;
    S_CAST_REGS_TYPE* pCastReg = HI_NULL;

    pAopReg = (S_AOP_REGS_TYPE*)(g_pAoeRegAddr + AOE_AOP_REG_OFFSET + Aop * sizeof(S_AOP_REGS_TYPE));
    if (0 == pAopReg->AOP_CTRL.bits.cast_flag)
    {
        /* aop is not cast, return */
        return;
    }
    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision), ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch));

    for (u32CastId = 0; u32CastId < AOE_MAX_CAST_NUM; u32CastId++)
    {
        pCastReg = (S_CAST_REGS_TYPE*)(g_pAoeRegAddr + AOE_CAST_REG_OFFSET + u32CastId * sizeof(S_CAST_REGS_TYPE));
        if (pCastReg->CAST_AOP_ID != Aop)
        {
            continue;
        }

        PROC_PRINT( file,
                    "            :BuffWritCnt(Total/Nomal/AddMute)(%.6u/%.6u/%.6u), BuffOverWriteCnt(%.6u)\n",
                    pCastReg->CAST_BUF_WRITETOTAL_CNT,
                    pCastReg->CAST_BUF_WRITEOK_CNT,
                    pCastReg->CAST_BUF_WRITEMUTE_CNT,
                    pCastReg->CAST_BUF_OVERWRITE_CNT);

        u32UsedSize = ADSP_BufUsedSizeProc(pCastReg->CAST_FIFO_SIZE, pCastReg->CAST_FIFO_RPTR, pCastReg->CAST_FIFO_WPTR);
        PROC_PRINT( file,
                    "            :FIFO Size/Used/Latency(0x%.4x/%d%%/%dms), Rptr/Wptr(0x%.4x/0x%.4x), FIFOWrite(Try/OK)(%.6u/%.6u), ForceFIFOReadCnt(%.6u)\n",
                    pCastReg->CAST_FIFO_SIZE,
                    ADSP_BufUsedPercProc(pCastReg->CAST_FIFO_SIZE, u32UsedSize),
                    ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs)),
                    pCastReg->CAST_FIFO_RPTR,
                    pCastReg->CAST_FIFO_WPTR,
                    pCastReg->CAST_FIFO_TRY_CNT,
                    pCastReg->CAST_FIFO_OK_CNT,
                    pCastReg->CAST_FIFO_FORCE_READ_CNT);
    }
}

static HI_VOID ADSP_AOE_Proc_ReadAop(struct seq_file* file, S_MIXER_REGS_TYPE* pEngineReg)
{
    HI_U32 u32UsedSize = 0;
    HI_U32 u32FrameSize = 0;
    HI_U32 Aop = 0;
    HI_VOID* pRptr = HI_NULL;
    HI_VOID* pWptr = HI_NULL;
    HI_VOID* pTmpAddr = HI_NULL;
    S_AOP_REGS_TYPE* pAopReg = HI_NULL;

    for (Aop = 0; Aop < AOE_MAX_AOP_NUM; Aop++)
    {
        if (!((pEngineReg->ENGINE_ROU_DST.bits.aop_buf_ena) & (1L << Aop)))
        {
            continue;
        }

        pAopReg = (S_AOP_REGS_TYPE*)(g_pAoeRegAddr + AOE_AOP_REG_OFFSET + Aop * sizeof(S_AOP_REGS_TYPE));
        if (pAopReg->AOP_CTRL.bits.cast_flag == 1) // aop is cast
        {
            PROC_PRINT( file,
                        "Aop(%d,Cast) :Status(%s), AddMute(%s), AefBypass(%s), Vol(%ddB/%ddB), Mute(%s), Latency(%dms), DelayComps(%dms)\n",
                        Aop,
                        ADSP_AOE_StatusName(pAopReg->AOP_CTRL.bits.cmd, pAopReg->AOP_CTRL.bits.cmd_done),
                        (pAopReg->AOP_CTRL.bits.ena_add_mute == 1) ? "on" : "off",
                        (0 == pAopReg->AOP_CTRL.bits.ena_aef_bypass) ? "Off" : "On",
                        (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                        (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                        (0 == pAopReg->AOP_EXT_CTRL.bits.mute) ? "Off" : "On",
                        pAopReg->AOP_BUFF_ATTR.bits.buf_latency,
                        pAopReg->AOP_CTRL.bits.realdelayms);
        }
        else
        {
            PROC_PRINT( file,
                        "Aop(%d)      :Status(%s), AefBypass(%s), Vol(%s%d.%ddB/%s%d.%ddB), Balance(%d), mute(%s) , Latency(%dms), AD(%s), DelayComps(%dms)\n",
                        Aop,
                        ADSP_AOE_StatusName(pAopReg->AOP_CTRL.bits.cmd, pAopReg->AOP_CTRL.bits.cmd_done),
                        (0 == pAopReg->AOP_CTRL.bits.ena_aef_bypass) ? "Off" : "On",
                        (0x79 == pAopReg->AOP_EXT_CTRL.bits.volume_l && 1 == pAopReg->AOP_EXT_CTRL.bits.volumedec_dir_l) ? "-" : "",
                        (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                        pAopReg->AOP_EXT_CTRL.bits.volumedec_l * 125,
                        (0x79 == pAopReg->AOP_EXT_CTRL.bits.volume_r && 1 == pAopReg->AOP_EXT_CTRL.bits.volumedec_dir_r) ? "-" : "",
                        (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_r) - 0x79,
                        pAopReg->AOP_EXT_CTRL.bits.volumedec_r * 125,
                        (0 == pAopReg->AOP_EXT_CTRL.bits.balance_dir) ? pAopReg->AOP_EXT_CTRL.bits.balance_val : -pAopReg->AOP_EXT_CTRL.bits.balance_val,
                        (0 == pAopReg->AOP_EXT_CTRL.bits.mute) ? "Off" : "On",
                        pAopReg->AOP_BUFF_ATTR.bits.buf_latency,
                        (0 == pAopReg->AOP_CTRL.bits.ena_ad) ? "Off" : "On",
                        pAopReg->AOP_CTRL.bits.realdelayms);
        }

        if (1 == pAopReg->AOP_BUF_SIZE.bits.buff_flag)
        {
#ifdef HI_SND_DSP_SUPPORT
            pRptr = adsp_ioremap(pAopReg->AOP_BUF_RPTR.ADDR_LOW, sizeof(HI_U32));
            pWptr = adsp_ioremap(pAopReg->AOP_BUF_WPTR.ADDR_LOW, sizeof(HI_U32));
#else
            ADSP_ReadAddr(pAopReg->AOP_BUF_RPTR, pRptr);
            ADSP_ReadAddr(pAopReg->AOP_BUF_WPTR, pWptr);
#endif
        }
        else  //Aop is Cast
        {
            pRptr = (HI_VOID*)(&pAopReg->AOP_BUF_RPTR);
            pWptr = (HI_VOID*)(&pAopReg->AOP_BUF_WPTR);
        }

        u32UsedSize = ADSP_BufUsedSizeProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, *((HI_U32*)pRptr), *((HI_U32*)pWptr));
        u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision), ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch));
        ADSP_ReadAddr(pAopReg->AOP_BUF_ADDR, pTmpAddr);
        PROC_PRINT( file,
                    "            :Buff Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%p), Size/Used/Latency(0x%.4x/%d%%/%dms), Rptr/Wptr(0x%.4x/0x%.4x)\n",
                    pAopReg->AOP_BUFF_ATTR.bits.buf_format == 0 ? "pcm" : "iec61937",
                    ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs),
                    ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch),
                    ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision),
                    pTmpAddr,
                    pAopReg->AOP_BUF_SIZE.bits.buff_size,
                    ADSP_BufUsedPercProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, u32UsedSize),
                    ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs)),
                    *((HI_U32*)pRptr),
                    *((HI_U32*)pWptr)
                  );
        if (pAopReg->AOP_CTRL.bits.audiodelay)
        {
            PROC_PRINT( file,
                        "            :AddMuteCnt(%.6u)\n", pAopReg->AOP_ADDMUTE_CNT);
        }

        ADSP_AOE_Proc_ReadAopCast(file, Aop);
    }
}

static HI_VOID ADSP_AOE_Proc_ReadEngine(struct seq_file* file, HI_U32 u32EngineId, S_MIXER_REGS_TYPE* pEngineReg)
{
    PROC_PRINT( file,
                "ENGINE(%d)   :Status(%s), Format(%s), Rate(%d), Ch(%d), Width(%d), AefMask(0x%x)",
                u32EngineId,
                ADSP_AOE_StatusName(pEngineReg->ENGINE_CTRL.bits.cmd, pEngineReg->ENGINE_CTRL.bits.cmd_done),
                pEngineReg->ENGINE_ATTR.bits.format == 0 ? "pcm" : "iec61937",
                ADSP_AOE_RateProc(pEngineReg->ENGINE_ATTR.bits.fs),
                ADSP_AOE_ChProc(pEngineReg->ENGINE_ATTR.bits.ch),
                ADSP_AOE_WidthProc(pEngineReg->ENGINE_ATTR.bits.precision),
                pEngineReg->ENGINE_ATT_AEF.bits.aef_att_ena);

    if (pEngineReg->ENGINE_ATT_AEF.bits.aef_att_ena & 0xf0)
    {
        PROC_PRINT( file, ", FifoDelayNum(%d)\n", pEngineReg->ENGINE_ATTR.bits.aef_delay);
    }
    else
    {
        PROC_PRINT( file, "\n");
    }
}

static HI_VOID ADSP_AOE_Proc(struct seq_file* file, HI_VOID* p)
{
    HI_U32 i;
    S_AOE_REGS_TYPE*   pComReg;
    S_MIXER_REGS_TYPE* pEneReg;

    PROC_PRINT( file, "\n---------------------------------  AOE Status  -------------------------------------------\n");

    pComReg = (S_AOE_REGS_TYPE*)g_pAoeRegAddr;
    PROC_PRINT( file,
                "CommonStatus   :ExecuteTimeOutCnt(%d), ScheduleTimeOutCnt(%d), AOE(%s), AOERegPhysAddr(0x%x)\n",
                pComReg->AOE_STATUS1.bits.excute_timeout_cnt,
                pComReg->AOE_STATUS1.bits.schedule_timeout_cnt,
                (HI_TRUE == g_stDspFwInfo.bAoeSwFlag) ? "sw" : "dsp",
                g_stDspFwInfo.tAoeRegPhyAddr);

    for (i = 0; i < AOE_MAX_ENGINE_NUM; i++)
    {
        pEneReg = (S_MIXER_REGS_TYPE*)(g_pAoeRegAddr + AOE_ENGINE_REG_OFFSET + i * sizeof(S_MIXER_REGS_TYPE));
        if ((pEneReg->ENGINE_CTRL.bits.cmd == 0 || pEneReg->ENGINE_CTRL.bits.cmd == 2) //when start or pause, proc
            && pEneReg->ENGINE_CTRL.bits.cmd_done == 1)
        {
            ADSP_AOE_Proc_ReadEngine(file, i, pEneReg);
            ADSP_AOE_Proc_ReadAip(file, pEneReg);
            ADSP_AOE_Proc_ReadAop(file, pEneReg);

            PROC_PRINT( file, "\n");
        }
    }

    ADSP_AOE_Proc_ReadKaraoke(file);
}

#ifdef __DPT__
static HI_VOID ADSP_AFLT_Proc(struct seq_file* p, HI_VOID* v)
{
    HI_U32 i;
    S_AFLT_REGS_TYPE* pAfltReg;
    S_AFLT_COM_ATTR*  pAfltComReg;
    HI_VOID* pTmpAddr;

    PROC_PRINT( p, "\n---------------------------------  AFLT Status  ------------------------------------------\n");

    pAfltComReg = (S_AFLT_COM_ATTR*)g_pAfltRegAddr;

    PROC_PRINT( p,
                "ComStatus  :ExecuteTimeOutCnt(%d)\n",
                pAfltComReg->AFLT_STATUS0.bits.timeout_cnt);

    PROC_PRINT( p, "\n");

    for (i = 0; i < AFLT_MAX_CHAN_NUM; i++)
    {
        pAfltReg = (S_AFLT_REGS_TYPE*)(g_pAfltRegAddr + AFLT_CHN_REG_OFFSET + i * sizeof(S_AFLT_REGS_TYPE));
        if (pAfltReg->ATTR.bits.use_flag) //aflt be created
        {
            ADSP_ReadAddr(pAfltReg->MSGPOOL_ADDR, pTmpAddr);
            PROC_PRINT( p,
                        "AFLT(%d) :Type(%s), CompName(%s), Status(%s), MsgPoolAddr(0x%p), MsgPoolSize(0x%x)\n",
                        i,
                        (pAfltReg->ATTR.bits.master_flag == 0) ? "slave" : "master",
                        ADSP_AFLT_CompName(pAfltReg->ATTR.bits.filter_id),
                        (pAfltReg->ATTR.bits.status == 0) ? "stop" : "start",
                        pTmpAddr,
                        pAfltReg->ATTR.bits.msgpool_size);

            PROC_PRINT( p,
                        "        :SettingIndex(0x%x), SettingSize(0x%x), CmdType(%s), CmdStatus(%s), CmdRetVal(%d)\n",
                        pAfltReg->CTRL.bits.param_index,
                        pAfltReg->CTRL.bits.param_wordsize,
                        ADSP_AFLT_CmdName((AFLT_CMD_E)pAfltReg->CTRL.bits.cmd),
                        (pAfltReg->CTRL.bits.cmd_done == 1) ? "done" : "no done",
                        pAfltReg->CTRL.bits.cmd_return_value);
            if (pAfltReg->ATTR.bits.master_flag == 1)
            {
                ADSP_ReadAddr(pAfltReg->IP_BUF_ADDR, pTmpAddr);
                PROC_PRINT( p,
                            "        :PtsBoundary(0x%x), InbufAddr(0x%p), InbufSize/Used(0x%x/%d%%), InbufRptr/Wptr(0x%x/0x%x), StreamReadPos(0x%x)\n",
                            pAfltReg->IPBUF_BOUNDARY,
                            pTmpAddr,
                            pAfltReg->IP_BUF_SIZE.bits.inbuff_size,
                            ADSP_BufUsedPercProc(pAfltReg->IP_BUF_SIZE.bits.inbuff_size, ADSP_BufUsedSizeProc(pAfltReg->IP_BUF_SIZE.bits.inbuff_size, pAfltReg->IP_BUF_RPTR, pAfltReg->IP_BUF_WPTR)),
                            pAfltReg->IP_BUF_RPTR,
                            pAfltReg->IP_BUF_WPTR,
                            pAfltReg->READPOS);
                PROC_PRINT( p,
                            "        :InfifoAddr(0x%x), InfifoSize(0x%x), InfifoRptr(0x%x), InfifoBytesLeft(0x%x)\n",
                            pAfltReg->IP_FIFO_ADDR,
                            pAfltReg->IP_FIFO_SIZE,
                            pAfltReg->IP_FIFO_RPTR,
                            pAfltReg->IP_FIFO_BYTES);
                ADSP_ReadAddr(pAfltReg->OP_BUF_ADDR, pTmpAddr);
                PROC_PRINT( p,
                            "        :OutbufAddr(0x%p), OutbufPeriodSize(0x%x), OutbufPeriodNum(0x%x), OutbufRidx/Widx(0x%x(%d)/0x%x(%d))\n",
                            pTmpAddr,
                            pAfltReg->OP_BUF_SIZE.bits.periond_size,
                            pAfltReg->OP_BUF_SIZE.bits.periond_num,
                            pAfltReg->OP_BUF_RIDX.bits.periond_read_idx,
                            pAfltReg->OP_BUF_RIDX.bits.periond_read_wrap,
                            pAfltReg->OP_BUF_WIDX.bits.periond_write_idx,
                            pAfltReg->OP_BUF_WIDX.bits.periond_write_wrap);
            }
            PROC_PRINT( p,
                        "        :TryCnt(%d), FrameCnt(%d), ErrFrameCnt(%d), ExcuteTimeOutCnt(%d), ScheduleTimeOutCnt(%d)\n",
                        pAfltReg->TRY_EXE_CNT,
                        pAfltReg->STATUS0.bits.frame_cnt,
                        pAfltReg->STATUS0.bits.frame_err_cnt,
                        pAfltReg->TIMEOUT.bits.exe_timeout_cnt,
                        pAfltReg->TIMEOUT.bits.sche_timeout_cnt);
            PROC_PRINT( p, "\n");
        }
    }

    return;
}
#endif

#ifdef HI_SND_DSP_SUPPORT
static HI_VOID ADSP_COM_Proc(struct seq_file* p, HI_VOID* v)
{
    HI_U32 j;
    volatile S_ADSP_CHN_REGS_TYPE* pADSPSysCrg = (volatile S_ADSP_CHN_REGS_TYPE*)(g_stDspFwInfo.pAoeRegVirAddr + DSP0_SHARESRAM_SYS_OFFSET);

    PROC_PRINT( p, "\n---------------------------------  Common Status  ------------------------------------------\n");
    PROC_PRINT( p, "DebugValue     :");
    for (j = 0; j < DSP_DEBUG_REG_NUM; j++)
    {
        PROC_PRINT( p,
                    "Debug%d(0x%x/%d)",
                    j,
                    pADSPSysCrg->ADSP_DEBUG[j],
                    pADSPSysCrg->ADSP_DEBUG[j]);
        if ((j + 1) % 4) //a line 4 reg
        {
            PROC_PRINT( p, ", ");
        }
        else
        {
            PROC_PRINT( p, "\n                ");
        }
    }

    PROC_PRINT( p, "\n");
}
#endif

HI_S32 ADSP_DRV_ReadProc(struct seq_file* file, HI_VOID* Param)
{
    if (HI_NULL == g_pAoeRegAddr)
    {
        PROC_PRINT(file, "\n-------------  ADSP NOT OPEN  -------------\n");
        return HI_SUCCESS;
    }

    ADSP_AOE_Proc(file, Param);

#ifdef __DPT__
    ADSP_AFLT_Proc(file, Param);
#endif

#ifdef HI_SND_DSP_SUPPORT
    ADSP_COM_Proc(file, Param);
#endif

    return HI_SUCCESS;
}

HI_S32 ADSP_DRV_WriteProc(struct file* file,
                          const char __user* buf, size_t count, loff_t* ppos)
{
    return count;
}

HI_S32 ADSP_DRV_RegisterProc(ADSP_REGISTER_PARAM_S* pstParam)
{
    DRV_PROC_ITEM_S* pProcItem;

    /* Check parameters */
    if (HI_NULL == pstParam)
    {
        return HI_FAILURE;
    }

    pProcItem = HI_DRV_PROC_AddModule("*adsp", HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_FATAL_ADSP("Create adsp proc entry fail!\n");
        return HI_FAILURE;
    }

    /* Set functions */
    pProcItem->read  = pstParam->pfnReadProc;
    pProcItem->write = pstParam->pfnWriteProc;

    return HI_SUCCESS;
}

HI_VOID ADSP_DRV_UnregisterProc(HI_VOID)
{
    HI_DRV_PROC_RemoveModule("*adsp");
}

HI_VOID ADSP_ProcDeInit(HI_VOID)
{
    g_pAoeRegAddr = HI_NULL;
#ifdef __DPT__
    g_pAfltRegAddr = HI_NULL;
#endif
}

HI_S32 ADSP_ProcInit(HI_VOID)
{
    if (HI_NULL == g_stDspFwInfo.pAoeRegVirAddr)
    {
        HI_ERR_ADSP("DSP share sram ptr is NULL\n");
        return HI_FAILURE;
    }

    g_pAoeRegAddr = g_stDspFwInfo.pAoeRegVirAddr + DSP0_SHARESRAM_AOE_OFFSET;

#ifdef __DPT__
    g_pAfltRegAddr = g_stDspFwInfo.pAoeRegVirAddr + DSP0_SHARESRAM_AFLT_OFFSET;
#endif

    return HI_SUCCESS;
}
