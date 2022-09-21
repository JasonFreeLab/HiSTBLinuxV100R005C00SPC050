#include "vfmw_proc.h"
#include "scd_drv.h"
#include "fsp.h"
#include "vfmw_ctrl.h"

#ifdef ENV_ARMLINUX_KERNEL

#ifdef HI_ADVCA_FUNCTION_RELEASE
#undef  HI_VFMW_PROC_SUPPORT
#else
#define HI_VFMW_PROC_SUPPORT
#endif

#ifdef HI_VFMW_PROC_SUPPORT

#define MAX_VID_PROTOCOL_NAME 20

#define VFMW_PROC_NAME_INFO     "info"
#define VFMW_PROC_NAME_HELP     "help"
#define VFMW_PROC_NAME_SCD      "scd"
#define VFMW_PROC_NAME_CHN      "channel"
#define VFMW_PROC_NAME_BUF      "buffer"
#define VFMW_PROC_NAME_LWD      "lowdelay"
#define VFMW_PROC_NAME_STATIS   "vfmw_statis"
#define VFMW_PROC_NAME_DIFF     "vfmw_diff"

extern SINT32 extra_ref;
extern SINT32 extra_disp;
extern UINT32 extra_cmd;
extern SINT32 g_VfmwInitCount;
extern SINT32 g_CurProcChan;
extern SINT32 g_SecProcSelect;
extern SM_IIS_S  s_SmIIS[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern DSP_STATE_E g_DspDrvState[2];
extern SMDRV_PARAM_S   g_ScdDrvParam[MAX_SCD_NUM];
extern UINT32  g_ResetCreateNewSave;
extern SINT8 s_VfmwSavePath[64];
extern VFMW_CHAN_S *s_pstVfmwChan[MAX_CHAN_NUM];
extern UINT32 g_ClkSelect;
extern UINT32 g_StandardObedience;
extern UINT32  g_TimeRecTable[MAX_RECORD_POS][MAX_RECORD_NUM];
extern UINT8   g_TimeRecId[MAX_RECORD_POS];
extern UINT32  g_DataTable[MAX_RECORD_DATA][MAX_RECORD_NUM];
extern UINT8   g_DataRecId[MAX_RECORD_DATA];

module_param(extra_ref,  int, 0000);
module_param(extra_disp, int, 0000);
module_param(extra_cmd,  int, 0000);

struct proc_dir_entry *g_pVfmwProc = NULL;

SINT32 vfmw_proc_open(struct inode *inode, struct file *file);
ssize_t vfmw_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);

static const struct file_operations vfmw_proc_fops =
{
    .owner   = THIS_MODULE,
    .open    = vfmw_proc_open,
    .read    = seq_read,
    .write   = vfmw_proc_write,
    .llseek  = seq_lseek,
    .release = single_release,
};


VOID show_standard(VID_STD_E eVidStd, char *strVidStd)
{
    char *strVidstdTemp = NULL;

    switch (eVidStd)
    {
        case VFMW_H264:
            strVidstdTemp = "H264";
            break;

        case VFMW_VC1:
            strVidstdTemp = "VC1";
            break;

        case VFMW_MPEG4:
            strVidstdTemp = "MPEG4";
            break;

        case VFMW_MPEG2:
            strVidstdTemp = "MPEG2";
            break;

        case VFMW_H263:
            strVidstdTemp = "H263";
            break;

        case VFMW_DIVX3:
            strVidstdTemp = "DIVX3";
            break;

        case VFMW_AVS:
            strVidstdTemp = "AVS";
            break;

        case VFMW_JPEG:
            strVidstdTemp = "JPEG";
            break;

        case VFMW_REAL8:
            strVidstdTemp = "REAL8";
            break;

        case VFMW_REAL9:
            strVidstdTemp = "REAL9";
            break;

        case VFMW_VP6:
            strVidstdTemp = "VP6";
            break;

        case VFMW_VP6F:
            strVidstdTemp = "VP6F";
            break;

        case VFMW_VP6A:
            strVidstdTemp = "VP6A";
            break;

        case VFMW_VP8:
            strVidstdTemp = "VP8";
            break;

        case VFMW_VP9:
            strVidstdTemp = "VP9";
            break;

        case VFMW_SORENSON:
            strVidstdTemp = "SORENSON";
            break;

        case VFMW_MVC:
            strVidstdTemp = "MVC";
            break;

        case VFMW_HEVC:
            strVidstdTemp = "HEVC";
            break;

        case VFMW_RAW:
            strVidstdTemp = "RAW";
            break;

        case VFMW_USER:
            strVidstdTemp = "USER";
            break;

        case VFMW_AVS2:
            strVidstdTemp = "AVS2.0";
            break;

        case VFMW_END_RESERVED:
            strVidstdTemp = "RESERVED";
            break;

        default:
            *strVidStd = '\0';
            break;
    }

    if (strVidstdTemp)
    {
        strncpy(strVidStd, strVidstdTemp, strlen(strVidstdTemp));
        strVidStd[strlen(strVidstdTemp)] = '\0';
    }

    return;
}

VOID show_eof_state(LAST_FRAME_STATE_E eState, char *strState)
{
    char *strStateTemp = NULL;

    switch (eState)
    {
        case LAST_FRAME_INIT:
            strStateTemp = "BLANK";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_RECEIVE:
            strStateTemp = "RECEIVED";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_SUCCESS:
            strStateTemp = "SUCCESS";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FAILURE:
            strStateTemp = "FAILURE";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FRAMEID:
            strStateTemp = "FRAMEID";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        default:
            *strState = '\0';
            break;
    }

    return;
}

#ifdef MV_HEVC_SUPPORT
VOID show_layer_state(UINT32 LayerId, OUTPUT_ORDER_E eOrder, char *strState)
{
    char *strStateTemp = NULL;

    switch (eOrder)
    {
        case DISP_ORDER:
            strStateTemp = (LayerId == 0)? "Output" : "Discard";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_BASE_LAYER:
            strStateTemp = (LayerId == 0)? "Output" : "Discard";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_ENHANCED_LAYER:
            strStateTemp = (LayerId == 0)? "Ignor" : "Output";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_ALL_LAYERS:
        default:
            strStateTemp = (LayerId == 0)? "Output" : "Output";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;
    }

    return;
}

VOID vfmw_read_proc_shvc(struct seq_file *p, VFMW_CHAN_S *pChan)
{
    SINT32 i;
    UINT32 OverLap = 0;
    char strLayerState[MAX_VID_PROTOCOL_NAME];

    HEVC_CTX_S *pCtx = (HEVC_CTX_S *)(&pChan->stSynCtx.unSyntax);

    seq_printf(p, "%-40s :%d\n", "IsMvHevc", pCtx->IsMultiLayers);
    seq_printf(p, "%-40s :%d\n", "IsShvc",   pCtx->IsShvcType);

    for (i=0; i<pCtx->LayerNum; i++)
    {
    show_layer_state(i, pChan->stSynExtraData.eOutputOrder, strLayerState);
    seq_printf(p, "%s%-34d :%dx%d -- %s\n", "Layer ",   i, pCtx->LayerWidth[i], pCtx->LayerHeight[i], strLayerState);
    }

    for (i=0; i<pCtx->MaxVpsNum; i++)
    {
        OverLap = HEVC_CheckVpsExtOverlap(&(pCtx->pVPS[i].vps_extension));
        if (OverLap != 0)
        {
            seq_printf(p, "%s%-36d :%s\n", "VPS ", i, (OverLap==3)? "both overlap" : ((OverLap==2)? "tail overlap" : "head overlap"));
        }
    }

    for (i=0; i<pCtx->MaxPpsNum; i++)
    {
        OverLap = HEVC_CheckPpsExtOverlap(&(pCtx->pPPS[i].pps_extension));
        if (OverLap != 0)
        {
            seq_printf(p, "%s%-36d :%s\n", "PPS ", i, (OverLap==3)? "both overlap" : ((OverLap==2)? "tail overlap" : "head overlap"));
        }
    }

    OverLap = HEVC_CheckSliceExtOverlap(&(pCtx->CurrSlice.slice_extension));
    if (OverLap != 0)
    {
        seq_printf(p, "%-40s :%s\n", "Slice ", (OverLap==3)? "both overlap" : ((OverLap==2)? "tail overlap" : "head overlap"));
    }

    return;
}
#endif

SINT32 string_to_value(char *str, UINT32 *data)
{
    UINT32 i, d, dat, weight;

    dat = 0;

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        weight = 16;
    }
    else
    {
        i = 0;
        weight = 10;
    }

    for (; i < 10; i++)
    {
        if (str[i] < 0x20) { break; }
        else if (weight == 16 && str[i] >= 'a' && str[i] <= 'f')
        {
            d = str[i] - 'a' + 10;
        }
        else if (weight == 16 && str[i] >= 'A' && str[i] <= 'F')
        {
            d = str[i] - 'A' + 10;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            d = str[i] - '0';
        }
        else
        {
            return -1;
        }

        dat = dat * weight + d;
    }

    *data = dat;

    return 0;
}

SINT32 vfmw_read_proc_info(struct seq_file *p, VOID *v)
{
    SINT32 i;
    extern UADDR  TracerPhyAddr;

    seq_printf(p, "\n");
    seq_printf(p, "------------------------- VFMW INFO ---------------------------\n");
    seq_printf(p, "%-40s :%s\n",   "Version",                     VFMW_VERSION);
    seq_printf(p, "%-40s :%s\n\n", "Modification Date",           VFMW_MODIFICATION_DATE);
    seq_printf(p, "%-40s :%d\n",   "VfmwInitCount",               g_VfmwInitCount);
    seq_printf(p, "%-40s :%#x\n",  "print enable word",           g_PrintEnable);
    seq_printf(p, "%-40s :%s\n",   "path to save debug data",     (char *)s_VfmwSavePath);
    seq_printf(p, "%-40s :%#x\n",  "tracer address",              TracerPhyAddr);
    seq_printf(p, "%-40s :%#x\n",  "vfmw_state enable word",      g_TraceCtrl);
    seq_printf(p, "%-40s :%d\n",   "bitstream control period",    g_TraceBsPeriod);
    seq_printf(p, "%-40s :%d\n",   "frame control period",        g_TraceFramePeriod);
    seq_printf(p, "%-40s :%d\n",   "rcv/rls img control period",  g_TraceImgPeriod);
    seq_printf(p, "%-40s :%d\n",   "extra_ref",                   extra_ref);
    seq_printf(p, "%-40s :%d\n",   "extra_disp",                  extra_disp);
    seq_printf(p, "%-40s :%d\n",   "extra_cmd",                   extra_cmd);
    seq_printf(p, "%-40s :%d\n",   "USE_FF_APT_EN",               USE_FF_APT_EN);
    seq_printf(p, "%-40s :%d\n",   "ResetCreateNewSave",          g_ResetCreateNewSave);
    seq_printf(p, "%-40s :0x%x\n", "ClkSelect",                   g_ClkSelect);
    seq_printf(p, "%-40s :%d\n",   "StandardObedience",           g_StandardObedience);
    seq_printf(p, "\n");

    seq_printf(p, "---------------------- TOTAL %d CHAN --------------------------\n", MAX_CHAN_NUM);
    seq_printf(p, "chan by vdh:\n");
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        seq_printf(p, "%-3d", g_ChanCtx.ChanDecByVdhPlusOne[i] - 1);
    }
    seq_printf(p, "\n");

    seq_printf(p, "priority queue:\n");
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        seq_printf(p, "%-3d", g_ChanCtx.ChanIdTabByPrior[i]);
    }
    seq_printf(p, "\n");

    seq_printf(p, "chan status:\n");
    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (s_pstVfmwChan[i] != NULL)
        {
            seq_printf(p, "chan: %d, is open: %d, is run: %d, priority: %d\n", i, s_pstVfmwChan[i]->s32IsOpen, s_pstVfmwChan[i]->s32IsRun, s_pstVfmwChan[i]->s32Priority);
        }
    }
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_help(struct seq_file *p, VOID *v)
{
    seq_printf(p, "\n");
    seq_printf(p, "------------------------- HELP INFO ---------------------------\n");
    seq_printf(p, "you can perform vfmw debug with such commond:\n");
    seq_printf(p, "echo [arg1] [arg2] > /proc/vfmw\n");
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "debug action                    arg1       arg2\n");
    seq_printf(p, "------------------------------  --------  ---------------------\n");
    seq_printf(p, "set print enable                0x0       print_enable_word\n");
    seq_printf(p, "set err_thr                     0x2       (chan_id<<24)|err_thr\n");
    seq_printf(p, "set dec order output            0x4       (chan_id<<24)|dec_order_output_enable\n");
    seq_printf(p, "set dec_mode(0/1/2=IPB/IP/I)    0x5       (chan_id<<24)|dec_mode\n");
    seq_printf(p, "set discard_before_dec_thr      0x7       (chan_id<<24)|stream_size_thr\n");
    seq_printf(p, "set postprocess options         0xa       (dc<<8)|(db<<4)|dr, 0000=auto,0001=on,0010=off\n");
    seq_printf(p, "set frame/adaptive storage      0xb       0:frame only, 1:adaptive\n");
    seq_printf(p, "pay attention to the channel    0xd       channel number\n");
    seq_printf(p, "channel vcmp config             0xe       chanId: arg2>>27,\n%42smirror_en: (arg2>>26)&1,\n%42svcmp_en: (arg2>>25)&1,\n%42swm_en: (arg2>>24)&1,\n%42swm_start: (arg2>>12)&0xfff,\n%42swm_end: (arg2)&0xfff\n", " ", " ", " ", " ", " ");
    seq_printf(p, "print tracer                    0x100     tracer address. do not care if vfmw still running\n");
    seq_printf(p, "start/stop raw stream saving    0x200     chan_id\n");
    seq_printf(p, "start/stop stream seg saving    0x201     chan_id\n");
    seq_printf(p, "start/stop 2D yuv saving        0x202     (chan_id<<24)|crop_enable\n");
    seq_printf(p, "save a single 2D frame          0x203     frame phy addr\n");
    seq_printf(p, "save a single 1D frame          0x204     frame phy addr width height=(height+PicStructure)\n");
    seq_printf(p, "set dec_task_schedule_delay     0x400     schedual_delay_time(ms)\n");
    seq_printf(p, "stop/start syntax dec           0x402     do not care\n");
    seq_printf(p, "set trace controller            0x500     vfmw_state_word in /proc/vfmw_prn\n");
    seq_printf(p, "set bitstream control period    0x501     period (ms)\n");
    seq_printf(p, "set frame control period        0x502     period (ms)\n");
    seq_printf(p, "set rcv/rls img control period  0x503     period (ms)\n");
    seq_printf(p, "set no stream report period     0x504     period (ms)\n");
    seq_printf(p, "set save YUV bitWidth           0x505     set save yuv bit width (must be 8 or 10)\n");
    seq_printf(p, "set module lowdelay start       0x600     channel number\n");
    seq_printf(p, "set module lowdelay stop        0x601     channel number\n");
    seq_printf(p, "set tunnel line number          0x602     channel number\n");
    seq_printf(p, "set scd lowdelay start          0x603     channel number\n");
    seq_printf(p, "set scd lowdelay stop           0x604     channel number\n");
    seq_printf(p, "set mmu add_err int switch      0x700     vdh number\n");
    seq_printf(p, "set vdh work clock              0x900     clock Config\n");
    seq_printf(p, "set vdh work clock              0x901     standard obedience\n");
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'print_enable_word' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>  DEC_MODE    PTS         DNR\n");
    seq_printf(p, "FOD         SCD_INFO    SCD_STREAM  SCD_REGMSG\n");
    seq_printf(p, "BLOCK       DBG         SE          SEI\n");
    seq_printf(p, "SLICE       PIC         SEQ         MARK_MMCO\n");
    seq_printf(p, "POC         DPB         REF         QUEUE\n");
    seq_printf(p, "IMAGE       STR_BODY    STR_TAIL    STR_HEAD\n");
    seq_printf(p, "STREAM      UPMSG       RPMSG       DNMSG\n");
    seq_printf(p, "VDMREG      CTRL        ERROR       FATAL\n");
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'vfmw_state' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <VO_REL_IMG>  <VO_RCV_IMG>\n");
    seq_printf(p, "<2D_TO_QUEUE>    <DNR_INTERRUPT>  <DNR_START>   <1D_TO_QUEUE>\n");
    seq_printf(p, "<VDH_REPAIR>     <VDH_INTERRUPT>  <VDH_START>   <GENERATE_DECPARAM>\n");
    seq_printf(p, "<DECSYNTAX_SEG>  <SCD_INTERRUPT>  <SCD_START>   <RCV_RAW>\n");
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'extra_cmd' definition, from bit31 to bit0:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <not used>    <not used>\n");
    seq_printf(p, "<not used>       <not used>       <direct 8x8>  <B before P>\n");
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_scd(struct seq_file *p, VOID *v)
{
    SINT32 ret;
    SINT32 ChanId;
    SINT32 ModuleId;
    SINT32 SegUsedPercent;
    SINT32 RawNum, RawSize, SegNum, SegSize, BufSize;
    SM_INSTANCE_S *pInst = NULL;
    SMDRV_PARAM_S *pScdDrvParam = NULL;
    char strVidStd[MAX_VID_PROTOCOL_NAME];

    seq_printf(p, "\n");
    seq_printf(p, "--------------------------- SCD INFO --------------------------\n");
    for (ModuleId = 0; ModuleId < MAX_VDH_NUM; ModuleId++)
    {
        pScdDrvParam = &g_ScdDrvParam[ModuleId];
        seq_printf(p, "%-40s :%d\n",  "IsScdDrvOpen",    pScdDrvParam->IsScdDrvOpen);
        seq_printf(p, "%-40s :%d\n",  "SCDState",        pScdDrvParam->SCDState);
        seq_printf(p, "%-40s :%d\n",  "ThisInstID",      pScdDrvParam->ThisInstID);
        seq_printf(p, "%-40s :%d\n",  "LastProcessTime", pScdDrvParam->LastProcessTime);
        seq_printf(p, "%-40s :%#x\n", "HwMemAddr",       pScdDrvParam->ScdDrvMem.HwMemAddr);
        seq_printf(p, "%-40s :%d\n",  "HwMemSize",       pScdDrvParam->ScdDrvMem.HwMemSize);
        seq_printf(p, "%-40s :%#x\n", "DownMsgMemAddr",  pScdDrvParam->ScdDrvMem.DownMsgMemAddr);
        seq_printf(p, "%-40s :%#x\n", "UpMsgMemAddr",    pScdDrvParam->ScdDrvMem.UpMsgMemAddr);
    }
    seq_printf(p, "\n");

    ChanId = g_CurProcChan;
    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    pInst = s_SmIIS[ChanId].pSmInstArray;
    if (pInst == NULL || pInst->Mode == SM_INST_MODE_IDLE)
    {
        dprint(PRN_ALWS, "pInst %d invalid\n", ChanId);
        return 0;
    }

    ret = GetRawStreamSize(&pInst->RawPacketArray, &RawSize);
    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetRawStreamSize return failed!\n", __func__);
    }

    ret = GetRawStreamNum(&pInst->RawPacketArray, &RawNum);
    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetRawStreamNum return failed!\n", __func__);
    }

    ret = GetSegStreamSize(&pInst->StreamSegArray, &SegSize);
    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetSegStreamSize return failed!\n", __func__);
    }

    SegNum = GetSegStreamNum(&pInst->StreamSegArray);
    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetSegStreamNum return failed!\n", __func__);
    }

    BufSize = pInst->StreamSegArray.SegBufSize;
    if (BufSize == 0)
    {
        SegUsedPercent = 0;
    }
    else
    {
        SegUsedPercent = SegSize * 100 / BufSize;
    }

    show_standard(pInst->Config.VidStd, strVidStd);

    seq_printf(p, "------------------------- STREAM INFO -------------------------\n");
    seq_printf(p, "%-40s :%d\n",      "Mode",              pInst->Mode);
    seq_printf(p, "%-40s :%d\n",      "Chan",              ChanId);
    seq_printf(p, "%-40s :%s\n",      "Cfg standard",      strVidStd);
    seq_printf(p, "%-40s :%#x\n",     "Cfg buf addr",      pInst->Config.BufPhyAddr);
    seq_printf(p, "%-40s :%d\n",      "Cfg buf size",      pInst->Config.BufSize);
    seq_printf(p, "%-40s :%#x\n",     "Seg read addr",     pInst->StreamSegArray.SegBufReadAddr);
    seq_printf(p, "%-40s :%#x\n",     "Seg write addr",    pInst->StreamSegArray.SegBufWriteAddr);
    seq_printf(p, "%-40s :%d\n",      "Is counting",       pInst->IsCounting);
    seq_printf(p, "%-40s :%d\n",      "Is omx path",       pInst->Config.IsOmxPath);
    seq_printf(p, "%-40s :%d\n",      "Raw current size",  RawSize);
    seq_printf(p, "%-40s :%d\n",      "Raw current num",   RawNum);
    seq_printf(p, "%-40s :%d\n",      "Raw size count",    pInst->u32RawSizeCount);
    seq_printf(p, "%-40s :%d\n",      "Raw num count",     pInst->u32RawNumCount);
    seq_printf(p, "%-40s :%d\n",      "Seg current size",  SegSize);
    seq_printf(p, "%-40s :%d\n",      "Seg current num",   SegNum);
    seq_printf(p, "%-40s :%d%%\n",    "Seg used percent)", SegUsedPercent);
    seq_printf(p, "%-40s :%d Kbps\n", "Actual bitrate", pInst->BitRate);
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_chn(struct seq_file *p, VOID *v)
{
    SINT32 i, ChanId;
    VFMW_CHAN_S *pChan = NULL;
    SINT32 VdhLoad  = 0;
    SINT32 VdhFps   = 0;
    SINT32 VdhCycle = 0;
    VFMW_GLOBAL_STAT_S *pVfmwGlobalStat = NULL;
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;
    IMAGE_VO_QUEUE *pstDecQue = NULL;
    FSP_INST_S *pFsp = NULL;
    SINT8 szAttach[12] = "NA";
    SINT32 RefNum = 0, ReadNum = 0, NewNum = 0, VdhId;
    SINT32 QueHist = 0, QueHead = 0, QueTail = 0;
    char strVidStd[MAX_VID_PROTOCOL_NAME];
    char strEofState[MAX_VID_PROTOCOL_NAME];

    ChanId = g_CurProcChan;
    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    pChan = s_pstVfmwChan[ChanId];
    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "ChanId %d inactive\n", ChanId);
        return 0;
    }

    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    VdhId = g_ChanCtx.ChanDecByVdhPlusOne[ChanId] - 1;
    if (VdhId < 0)
    {
        memcpy(szAttach, "NA", 3);
    }
    else
    {
        if (g_VdmExtParam[VdhId].VdmAttachStr.VdmAttachMode == VDMDRV_ATTACH_NULL)
        {
            memcpy(szAttach, "Non_Attach", 11);
        }
        else
        {
            memcpy(szAttach, "Attach", 7);
        }
    }

    VCTRL_GetChanImgNum(ChanId, &RefNum, &ReadNum, &NewNum);

    pstDecQue = VCTRL_GetChanVoQue(ChanId);
    if (pstDecQue != NULL)
    {
        QueHist = pstDecQue->history;
        QueHead = pstDecQue->head;
        QueTail = pstDecQue->tail;
    }

    show_standard(pChan->eVidStd, strVidStd);
    show_eof_state(pChan->eLastFrameState, strEofState);

    seq_printf(p, "\n");
    seq_printf(p, "------------------------ CHAN [%d] INFO -----------------------\n", ChanId);
    seq_printf(p, "%-40s :%d(%s)\n", "Dec by VDH",           VdhId, szAttach);
    seq_printf(p, "%-40s :%d\n",     "IsOpen",               pChan->s32IsOpen);
    seq_printf(p, "%-40s :%d\n",     "IsRun",                pChan->s32IsRun);
    seq_printf(p, "%-40s :%d\n",     "Priority",             pChan->s32Priority);
    seq_printf(p, "%-40s :%s\n",     "eVidStd",              strVidStd);
    seq_printf(p, "%-40s :%d\n",     "ChanCapLevel",         pChan->eChanCapLevel);
    seq_printf(p, "%-40s :%s\n",     "LastFrameState",       strEofState);
    seq_printf(p, "%-40s :%d\n",     "IsOmxPath",            pChan->stChanCfg.s32IsOmxPath);
    seq_printf(p, "%-40s :%d\n",     "CfgDecMode",           pChan->stChanCfg.s32DecMode);
    seq_printf(p, "%-40s :%d\n",     "CfgOutputOrder",       pChan->stChanCfg.s32DecOrderOutput);
    seq_printf(p, "%-40s :%d\n",     "ErrorThred",           pChan->stChanCfg.s32ChanErrThr);
    seq_printf(p, "%-40s :%d\n",     "StreamThred",          pChan->stChanCfg.s32ChanStrmOFThr);
    seq_printf(p, "%-40s :%d\n",     "Compress",             pChan->stSynExtraData.CompressEn);
    seq_printf(p, "%-40s :%d\n",     "LossCompress",         pChan->stSynExtraData.s32LossCompressEn);
    seq_printf(p, "%-40s :%d\n",     "BitDepth",             pChan->stSynExtraData.s32BitDepth);
    seq_printf(p, "%-40s :%d\n",     "DecodeFrameNum",       pChan->DecodeFrameNumber);
    seq_printf(p, "%-40s :%d\n",     "OutputFrameNum",       pChan->OutputFrameNumber);

    if (pChan->stSynExtraData.s32LossCompressEn == 1)
    {
        seq_printf(p, "%-40s :%d\n",     "YCompressRatio",   pChan->stSynExtraData.s32YCompRatio);
        seq_printf(p, "%-40s :%d\n",     "UVCompressRatio",   pChan->stSynExtraData.s32UVCompRatio);
    }

    if (pChan->eVidStd == VFMW_VC1)
    {
        seq_printf(p, "%-40s :%d\n", "USE_FF_APT_EN",        USE_FF_APT_EN);
        seq_printf(p, "%-40s :%d\n", "StdExt AP",            pChan->stChanCfg.StdExt.Vc1Ext.IsAdvProfile);
        seq_printf(p, "%-40s :%d\n", "StdExt CodecVer",      pChan->stChanCfg.StdExt.Vc1Ext.CodecVersion);
    }
    else if (pChan->eVidStd == VFMW_VP6 || pChan->eVidStd == VFMW_VP6F || pChan->eVidStd == VFMW_VP6A)
    {
        seq_printf(p, "%-40s :%d\n", "StdExt Reversed",      pChan->stChanCfg.StdExt.Vp6Ext.bReversed);
    }
    else if (pChan->eVidStd == VFMW_MPEG4)
    {
        seq_printf(p, "%-40s :%d\n", "Skip Frame Found",     pVfmwChanStat->u32SkipFind);
        seq_printf(p, "%-40s :%d\n", "Skip Frame Discarded", pVfmwChanStat->u32SkipDiscard);
        seq_printf(p, "%-40s :%d\n", "Is Short Headed",      ((MP4_CTX_S *)(&pChan->stSynCtx.unSyntax))->ScdUpMsg.IsShStreamFlag);
    }
    else if (pChan->eVidStd == VFMW_USER)
    {
        USRDEC_FRAME_DESC_S *FrameDesc = &pChan->stRecentUsrdecFrame;
        seq_printf(p, "Recent UsrdecFrame: enFmt=%d,w=%d,h=%d,Ystride=%d,Cstride=%d,PTS=%lld\n",
                   FrameDesc->enFmt, FrameDesc->s32YWidth, FrameDesc->s32YHeight, FrameDesc->s32LumaStride, FrameDesc->s32ChromStride, FrameDesc->Pts);
    }
    else if (pChan->eVidStd == VFMW_HEVC)
    {
#ifdef MV_HEVC_SUPPORT
        vfmw_read_proc_shvc(p, pChan);
#endif
    }

    seq_printf(p, "\n");
    seq_printf(p, "%-40s :%#x\n",         "CTX Mem Phy",           pChan->stChanMem_ctx.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "CTX Mem Size",          pChan->stChanMem_ctx.Length);
    seq_printf(p, "%-40s :%#x\n",         "SCD Mem Phy",           pChan->stChanMem_scd.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "SCD Mem Size",          pChan->stChanMem_scd.Length);
    seq_printf(p, "%-40s :%#x\n",         "VDH Mem Phy",           pChan->stChanMem_vdh.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "VDH Mem Size",          pChan->stChanMem_vdh.Length);
    seq_printf(p, "\n");
    seq_printf(p, "%-40s :(%d,%d,%d)\n",  "Ref,Read,New",          RefNum, ReadNum, NewNum);
    seq_printf(p, "%-40s :(%d,%d,%d)\n",  "VoQue detail",          QueHist, QueHead, QueTail);
    seq_printf(p, "%-40s :%d\n",          "Act DecMode ",          pChan->stSynExtraData.s32DecMode);
    seq_printf(p, "%-40s :%d\n",          "Act OutputOrder",       pChan->stSynExtraData.eOutputOrder);
    //seq_printf(p, "%-40s :0x%d\n",        "Image Format",          (UINT32)(pChan->stRecentImgformat));
    seq_printf(p, "%-40s :%d\n",          "Frame Packing Type",    pChan->stRecentImgPackingType);
    seq_printf(p, "\n");

    seq_printf(p, "--------------------------- VDH INFO --------------------------\n");
    pFsp = FSP_GetInst(ChanId);
    if (pFsp == NULL)
    {
        dprint(PRN_ALWS, "pFsp %d invalid\n", ChanId);
        return 0;
    }

    for (i = 0; i < MAX_VDH_NUM; i++)
    {
        pVfmwGlobalStat = &g_VfmwGlobalStat[i];
        VdhLoad  = pVfmwGlobalStat->u32VdhLoad / 10;
        VdhFps   = pVfmwChanStat->u32FrFrameRate / 10;

        if ((VdhFps != 0) && (pFsp->stInstCfg.DecFsWidth / 16 != 0) && (pFsp->stInstCfg.DecFsHeight / 16 != 0))
        {
            VdhCycle = pVfmwGlobalStat->u32VdhKiloCyclePerSecond * 1000 / VdhFps / (pFsp->stInstCfg.DecFsWidth / 16) / (pFsp->stInstCfg.DecFsHeight / 16);
        }
        else
        {
            VdhCycle = 0;
        }
        seq_printf(p, "%s%-36d :%d.%d%%\n", "VDH ",   i, VdhLoad, pVfmwGlobalStat->u32VdhLoad % 10);
        seq_printf(p, "%-40s :%d.%d fps(Chan %d)\n",  "Frame Rate",  VdhFps,  pVfmwChanStat->u32FrFrameRate % 10, ChanId);
        seq_printf(p, "%-40s :%d/mb\n",               "Cycle State", VdhCycle);
    }
    seq_printf(p, "\n");

    if (1 == pChan->stSynExtraData.stChanOption.u32DynamicFrameStoreAllocEn)
    {
        seq_printf(p, "--------------------------- DFS INFO --------------------------\n");
        seq_printf(p, "%-40s :%d\n",    "Frame size(byte)",       pChan->s32CurFsSize);
        seq_printf(p, "%-40s :%d\n",    "Reference frame num", pChan->s32RefNum);
        seq_printf(p, "%-40s :%d/%d\n", "Pre alloced frame num/time(ms)",
                   pChan->s32PreAllocFrmNum, pChan->stDynamicFSTimestamp.u32PreAllocTime);
        seq_printf(p, "%-40s :%d/%d\n", "Dynamic alloced frame num/time(ms)",
                   pChan->s32MMZFrmNum,  pChan->stDynamicFSTimestamp.u32MMZAllocTime);
        seq_printf(p, "%-40s :%d/%d\n", "All frame num/time(ms)",
                   pChan->s32NeededFrameNum, pChan->stDynamicFSTimestamp.u32AllTime);
    }
    seq_printf(p, "\n");

    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_buf(struct seq_file *p, VOID *v)
{
    SINT32 ChanId, i;
    UINT8  IsFree;
    UINT32 TotalFree;
    FSP_INST_S *pFsp = NULL;

    ChanId = g_CurProcChan;
    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    seq_printf(p, "\n");
    seq_printf(p, "--------------------------- FSP INFO --------------------------\n");
    pFsp = FSP_GetInst(ChanId);
    if (pFsp == NULL)
    {
        dprint(PRN_ALWS, "pFsp %d invalid\n", ChanId);
        return 0;
    }

    seq_printf(p, "%-20s :%d\n", "FSP DecFsWidth",       pFsp->stInstCfg.DecFsWidth);
    seq_printf(p, "%-20s :%d\n", "FSP DecFsHeight",      pFsp->stInstCfg.DecFsHeight);
    seq_printf(p, "%-20s :%d\n", "FSP DispFsWidth",      pFsp->stInstCfg.DispFsWidth);
    seq_printf(p, "%-20s :%d\n", "FSP DispFsHeight",     pFsp->stInstCfg.DispFsHeight);
    seq_printf(p, "%-20s :%d\n", "FSP ExpectedDecFsNum", pFsp->stInstCfg.ExpectedDecFsNum);
    seq_printf(p, "%-20s :%d\n", "FSP TotalValidFSNum",  pFsp->TotalValidFsNum);

    seq_printf(p, "\n");
    TotalFree = 0;
    seq_printf(p, "%-20s :%d\n", "FSP ActualPmvNum",     pFsp->PmvNum);
    seq_printf(p, "%-10s %-10s %-10s %-10s\n", "Num", "IsValid", "InUse", "Address");
    for (i = 0; i < pFsp->PmvNum; i++)
    {
        IsFree = FSP_IsPmvAvailable(&pFsp->stPmvRec[i]);
        TotalFree += IsFree;

        seq_printf(p, "%-10d %-10d %-10d 0x%-10x %s\n", i,
                   pFsp->stPmvRec[i].IsValid, pFsp->stPmvRec[i].IsInUse,
                   pFsp->stPmvRec[i].PmvAddr, ((IsFree)? "(Free)": ""));
    }
    seq_printf(p, "%-20s :%d\n", "FSP FreePmvNum",      TotalFree);

    seq_printf(p, "\n");
    TotalFree = 0;
    seq_printf(p, "%-20s :%d\n", "FSP ActualDecFsNum",   pFsp->DecFsNum);
    seq_printf(p, "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Num", "IsValid", "IsRef", "DispState", "IsOccupied", "Size", "Address");
    for (i = 0; i < pFsp->DecFsNum; i++)
    {
        IsFree = FSP_IsDecFsAvailable(ChanId, &pFsp->stDecFsRec[i]);
        TotalFree += IsFree;

        seq_printf(p, "%-10d %-10d %-10d %-10d %-10d %-10d 0x%-10x %s\n", i,
                   pFsp->stDecFsRec[i].IsValid, pFsp->stDecFsRec[i].PhyFS.IsDecRef,
                   pFsp->stDecFsRec[i].PhyFS.DispState, FSP_IsSpecialFrm(ChanId, pFsp->stDecFsRec[i].PhyFS.PhyAddr),
                   pFsp->stDecFsRec[i].PhyFS.BufSize, pFsp->stDecFsRec[i].PhyFS.PhyAddr, ((IsFree)? "(Free)": ""));
    }
    seq_printf(p, "%-20s :%d\n", "FSP FreeDecFsNum",    TotalFree);

    seq_printf(p, "\n");
    seq_printf(p, "%-20s :%d\n",   "FSP LogicFsNum",    MAX_FRAME_NUM);
    for (i = 0; i < MAX_FRAME_NUM; i++)
    {
        if ((i != 0) && ((i & 15) == 0) ) { seq_printf(p, "\n"); }
        seq_printf(p, "%d%d ", pFsp->stLogicFs[i].IsRef, pFsp->stLogicFs[i].DispState);
    }
    seq_printf(p, "\n\n");

    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_statis(struct seq_file *p, VOID *v)
{
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    UINT32 TotalDiff = 0;
    UINT32 cycle = 0;

    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet(&diff, 0, sizeof(UINT32)*(7));

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    seq_printf(p, "---------------------------- VFMW STATICS (Unit:us)---------------\n");
    seq_printf(p, "Task\t SegCope(Size)\t RandTab  Syntax  VDH    IsrProcess   Wakeup\t fps\n");

    for (i = (MAX_RECORD_NUM -1); i >= 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_END][i] - g_TimeRecTable[THREAD_START][i])/1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_END][i] - g_TimeRecTable[SEGCOPY_START][i])/1000;
        diff[2] = (g_TimeRecTable[MAP_END][i] - g_TimeRecTable[MAP_START][i])/1000;
        diff[3] = (g_TimeRecTable[SYNTAX_END][i] - g_TimeRecTable[SYNTAX_START][i])/1000;
        diff[4] = (g_TimeRecTable[VDH_END][i] - g_TimeRecTable[VDH_START][i])/1000;
        diff[5] = (g_TimeRecTable[ISR_END][i] - g_TimeRecTable[ISR_START][i])/1000;
        diff[6] = (g_TimeRecTable[NEXT_THREAD_START][i] - g_TimeRecTable[ISR_END][i])/1000;

        cycle = g_DataTable[VDH_DATA][i] / (345600) ;

        TotalDiff = (g_TimeRecTable[ISR_END][i] - g_TimeRecTable[SEGCOPY_START][i]);
        seq_printf(p, "%6u %6u(%8u) %6u %6u %6u(%6u) %6u %6u || %d.%dfps==> %u\n",
            diff[0],diff[1],g_DataTable[COPY_SIZE_DATA][i],diff[2],diff[3],diff[4],cycle,diff[5],diff[6],
            pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10,g_DataTable[VDH_DATA][i]);
    }

    seq_printf(p, "----------------------------------------------------------------\n");

    return 0;
}


SINT32 vfmw_read_proc_diff(struct seq_file *p, VOID *v)
{
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet(&diff, 0, sizeof(UINT32)*(7));

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    seq_printf(p, "---------------------------- VFMW STATICS (Unit:ms)---------------\n");
    seq_printf(p, "Task\t   SegCope(Size)\t    RandTab     Syntax     VDH       IsrProcess      Wakeup\t    fps\n");

    for (i = (MAX_RECORD_NUM -1); i > 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_START][i] - g_TimeRecTable[THREAD_START][i - 1])/1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_START][i] - g_TimeRecTable[SEGCOPY_START][i - 1])/1000;
        diff[2] = (g_TimeRecTable[MAP_START][i] - g_TimeRecTable[MAP_START][i - 1])/1000;
        diff[3] = (g_TimeRecTable[SYNTAX_START][i] - g_TimeRecTable[SYNTAX_START][i - 1]);
        diff[4] = (g_TimeRecTable[VDH_START][i] - g_TimeRecTable[VDH_START][i - 1])/1000;
        diff[5] = (g_TimeRecTable[ISR_START][i] - g_TimeRecTable[ISR_START][i - 1])/1000;
        diff[6] = (g_TimeRecTable[VDH_END][i] - g_TimeRecTable[VDH_START][i])/1000;
        seq_printf(p, "%u    %10u    %10u    %10u    %10u    %10u   ==>   %15u|| %d.%dfps\n",
            diff[0],diff[1],diff[2],diff[3],diff[4],diff[5],diff[6],
            pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10);
    }

    seq_printf(p, "----------------------------------------------------------------\n");

    return 0;
}

static void GetStrFromCmd(char *cmd, UINT32 count, SINT32 *index, char *str)
{
    SINT32 i, j;

    i = *index;
    j = 0;
    for (; i < count; i++)
    {
        if (j == 0 && cmd[i] == ' ') { continue; }

        if (cmd[i] > ' ') { str[j++] = cmd[i]; }

        if (j > 0 && cmd[i] == ' ') { break; }
    }
    str[j] = 0;

    *index = i;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
SINT32 vfmw_write_proc(struct file *file, const char __user *buffer, unsigned long count, VOID *data)
#else
SINT32 vfmw_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
#endif
{
    static char cmd[256], str[256];
    SINT32 i, j;
    UINT32 dat1, dat2, dat3, dat4, dat5, dat6;
    UINT32 args[8];

    dat1 = dat2 = dat3 = dat4 = dat5 = dat6 = 0;

    if (count >= sizeof(cmd))
    {
        dprint(PRN_ALWS, "MMZ: your parameter string is too long!\n");
        return -EIO;
    }

    memset(cmd, 0, sizeof(cmd));

    if (copy_from_user(cmd, buffer, count))
    {
        dprint(PRN_ALWS, "MMZ: copy_from_user failed!\n");
        return -EIO;
    }
    cmd[count] = 0;

    /* dat1 */
    i = 0;

    GetStrFromCmd(cmd, count, &i, str);

    if (string_to_value(str, &dat1) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* dat2 */
    GetStrFromCmd(cmd, count, &i, str);

    if (string_to_value(str, &dat2) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* extra arguments */
    if (dat1 >= 0x200 && dat1 < 0x300)
    {
        if (dat1 == 0x204)
        {
            GetStrFromCmd(cmd, count, &i, str);

            if (string_to_value(str, &dat3) != 0)
            {
                dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
                return -1;
            }

            GetStrFromCmd(cmd, count, &i, str);

            if (string_to_value(str, &dat4) != 0)
            {
                dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
                return -1;
            }
        }

        j = 0;

        for (; i < count; i++)
        {
            if (j == 0 && cmd[i] == ' ') { continue; }

            if (cmd[i] > ' ') { str[j++] = cmd[i]; }

            if (j > 0 && cmd[i] <= ' ') { break; }
        }

        str[j] = 0;

        if (str[0] == '/')
        {
            if (j >= 1)
            {
                if (str[j - 1] == '/')
                {
                    str[j - 1] = 0;
                }

                dprint(PRN_ALWS, "******* vfmw save path: %s ********\n", str);
                strncpy(s_VfmwSavePath, str, sizeof(s_VfmwSavePath));
                s_VfmwSavePath[sizeof(s_VfmwSavePath) - 1] = '\0';
            }
            else
            {
                dprint(PRN_ALWS, "%s %d j < 1!!\n", __FUNCTION__, __LINE__);
                return -1;
            }
        }
    }

    if (dat1 == 0x800)
    {
        /* dat3 */
        GetStrFromCmd(cmd, count, &i, str);

        if (string_to_value(str, &dat3) != 0)
        {
            dprint(PRN_ALWS, "%s,%d, error echo cmd '%s'!\n", __func__, __LINE__, cmd);
            return -1;
        }

         /* dat4 */
        GetStrFromCmd(cmd, count, &i, str);

        if (string_to_value(str, &dat4) != 0)
        {
            dprint(PRN_ALWS, "%s,%d, error echo cmd '%s'!\n", __func__, __LINE__, cmd);
            return -1;
        }

         /* dat5 */
        GetStrFromCmd(cmd, count, &i, str);

        if (string_to_value(str, &dat5) != 0)
        {
            dprint(PRN_ALWS, "%s,%d, error echo cmd '%s'!\n", __func__, __LINE__, cmd);
            return -1;
        }

         /* dat6 */
        GetStrFromCmd(cmd, count, &i, str);

        if (string_to_value(str, &dat6) != 0)
        {
            dprint(PRN_ALWS, "%s,%d, error echo cmd '%s'!\n", __func__, __LINE__, cmd);
            return -1;
        }
    }

    dprint(PRN_ALWS, "\nvfmw debug: arg1=%#x, arg2=%#x, dat3=%#x, dat4=%#x, dat5=%#x, dat6=%#x\n", dat1, dat2, dat3, dat4, dat5, dat6);

    args[0] = dat2;
    args[1] = dat3;
    args[2] = dat4;
    args[3] = dat5;
    args[4] = dat6;
    VCTRL_SetDbgOption(dat1, (UINT8 *)args);

    return count;
}

SINT32 vfmw_proc_open(struct inode *inode, struct file *file)
{
    vfmw_proc_func *proc;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    proc = PDE(inode)->data;
#else
    proc = PDE_DATA(inode);
#endif

    if (NULL == proc)
    {
        return -ENOSYS;
    }

    if (proc->read)
    {
        return single_open(file, proc->read, proc);
    }

    return -ENOSYS;
}

ssize_t vfmw_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct seq_file *s      = file->private_data;
    vfmw_proc_func  *proc   = s->private;

    if (proc->write)
    {
        return proc->write(file, buf, count, ppos);
    }

    return -ENOSYS;
}

static vfmw_proc_func  vfmw_proc[32];

SINT32 vfmw_proc_create(HI_CHAR *proc_name, vfmw_proc_read_fn read, vfmw_proc_write_fn write)
{
    struct proc_dir_entry  *entry;
    vfmw_proc_func         *proc = NULL;
    UINT32 i;
    UINT32 count = sizeof(vfmw_proc) / sizeof(vfmw_proc[0]);

    for (i = 0; i < count; i++)
    {
        if ((NULL == vfmw_proc[i].read) && (NULL == vfmw_proc[i].write))
        {
            proc = &vfmw_proc[i];

            strncpy(proc->proc_name, proc_name, sizeof(proc->proc_name));
            proc->proc_name[sizeof(proc->proc_name) - 1] = 0;

            proc->read  = read;
            proc->write = write;

            break;
        }
    }

    if (i >= count)
    {
        return -1;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    entry = create_proc_entry(proc_name, 0644, g_pVfmwProc);

    if (!entry)
    {
        return -1;
    }

    entry->proc_fops    = &vfmw_proc_fops;
    entry->data         = proc;
#else
    entry = proc_create_data(proc_name, 0644, g_pVfmwProc, &vfmw_proc_fops, (VOID *)proc);

    if (!entry)
    {
        return -1;
    }

#endif

    return 0;
}

VOID vfmw_proc_destroy(HI_CHAR *proc_name)
{
    UINT32  i;
    UINT32  count = sizeof(vfmw_proc) / sizeof(vfmw_proc[0]);

    for (i = 0; i < count; i++)
    {
        vfmw_proc_func *proc = &vfmw_proc[i];

        if (0 == strncmp(proc_name, proc->proc_name, sizeof(proc->proc_name)))
        {
            remove_proc_entry(proc_name, g_pVfmwProc);

            memset(proc->proc_name, 0, sizeof(proc->proc_name));

            proc->read  = NULL;
            proc->write = NULL;

            break;
        }
    }
}

VOID vfmw_proc_destroy_all(VOID)
{
    UINT32 i;
    UINT32 count = sizeof(vfmw_proc) / sizeof(vfmw_proc[0]);

    for (i = 0; i < count; i++)
    {
        vfmw_proc_func *proc = &vfmw_proc[i];

        if (proc->read != NULL)
        {
            remove_proc_entry(proc->proc_name, g_pVfmwProc);

            memset(proc->proc_name, 0, sizeof(proc->proc_name));

            proc->read  = NULL;
            proc->write = NULL;
        }
    }
}

#endif

SINT32 vfmw_proc_init(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    SINT32  ret;

    g_pVfmwProc = proc_mkdir("vfmw", NULL);

    ret = vfmw_proc_create(VFMW_PROC_NAME_INFO, vfmw_read_proc_info, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_HELP, vfmw_read_proc_help, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_SCD, vfmw_read_proc_scd, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_CHN, vfmw_read_proc_chn, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_STATIS, vfmw_read_proc_statis, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_DIFF, vfmw_read_proc_diff, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_BUF, vfmw_read_proc_buf, vfmw_write_proc);
    if (0 != ret)
    {
        return -1;
    }
#endif

    return 0;
}

VOID vfmw_proc_exit(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    vfmw_proc_destroy_all();

    remove_proc_entry("vfmw", NULL);
#endif
}

#endif
