
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_edid.h"
#include "hi_unf_vo.h"
#include "hi_unf_frontend.h"
#include "hi_unf_demux.h"
#include "hi_unf_avplay.h"
#include "hi_unf_mce.h"
#include "hi_psi_si.h"
#include "hi_play.h"
#include "hi_osd.h"
#include "hi_demux.h"
#ifdef HI_VENC_SUPPORT
#include "hi_transcode.h"
#endif
#ifdef HI_GPU_SUPPORT
#include "hi_gpu.h"
#endif


#define HI_HDMI_DEFAULT_MODE    HI_UNF_HDMI_DEFAULT_ACTION_HDMI

static HI_UNF_HDMI_CALLBACK_FUNC_S  HdmiProcFunc;

static HI_S32 RegisterAudioLib(HI_CHAR* LibName)
{
    HI_S32 ret = HI_SUCCESS;

    if (HI_SUCCESS != HI_UNF_AVPLAY_RegisterAcodecLib(LibName))
    {
        printf("[%s - %u] %s not found\n", __FUNCTION__, __LINE__, LibName);

        ret = HI_FAILURE;
    }

    return ret;
}

static HI_S32 ClearLogo(HI_VOID)
{
    HI_S32                  ret = HI_SUCCESS;
    HI_UNF_MCE_STOPPARM_S   MceStop;

    memset(&MceStop, 0x00, sizeof(MceStop));

    ret = HI_UNF_MCE_Init(HI_NULL);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_MCE_Init failed 0x%x\n", __FUNCTION__, ret);

        return ret;
    }

    ret = HI_UNF_MCE_ClearLogo();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_MCE_ClearLogo failed 0x%x\n", __FUNCTION__, ret);
        (HI_VOID)HI_UNF_MCE_DeInit();
        return ret;
    }

    MceStop.enStopMode      = HI_UNF_AVPLAY_STOP_MODE_STILL;
    MceStop.enCtrlMode      = HI_UNF_MCE_PLAYCTRL_BY_TIME;
    MceStop.u32PlayTimeMs   = 0;

    ret = HI_UNF_MCE_Stop(&MceStop);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_MCE_Stop failed 0x%x\n", __FUNCTION__, ret);
        (HI_VOID)HI_UNF_MCE_DeInit();
        return ret;
    }

    ret = HI_UNF_MCE_Exit(HI_NULL);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_MCE_Exit failed 0x%x\n", __FUNCTION__, ret);
        (HI_VOID)HI_UNF_MCE_DeInit();
        return ret;
    }

    HI_UNF_MCE_DeInit();

    return HI_SUCCESS;
}

static HI_VOID HdmiHotPlugProc(HI_VOID* Param)
{
    HI_S32                      ret;
    HI_UNF_HDMI_ID_E            HdmiId = HI_UNF_HDMI_ID_0;
    HI_UNF_HDMI_STATUS_S        HdmiStatus;
    HI_UNF_EDID_BASE_INFO_S     BaseInfo;
    HI_UNF_HDMI_ATTR_S          HdmiAttr;

    ret = HI_UNF_HDMI_GetStatus(HdmiId, &HdmiStatus);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_GetStatus failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return;
    }

    if (HI_FALSE == HdmiStatus.bConnected)
    {
        return;
    }

    ret = HI_UNF_HDMI_GetSinkCapability(HdmiId, &BaseInfo);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_GetSinkCapability failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return;
    }

    ret = HI_UNF_HDMI_GetAttr(HdmiId, &HdmiAttr);
    if (HI_SUCCESS == ret)
    {
        if (HI_TRUE == BaseInfo.bSupportHdmi)
        {
            HdmiAttr.bEnableHdmi = HI_TRUE;
            if (HI_TRUE != BaseInfo.stColorSpace.bYCbCr444)
            {
                HdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
            }
            else
            {
                HdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;
            }
        }
        else
        {
            HdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;

            //读取到了edid，并且不支持hdmi则进入dvi模式
            //read real edid ok && sink not support hdmi,then we run in dvi mode
            HdmiAttr.bEnableHdmi = HI_FALSE;
        }
    }
    else
    {
        if (HI_HDMI_DEFAULT_MODE == HI_UNF_HDMI_DEFAULT_ACTION_HDMI)
        {
            HdmiAttr.bEnableHdmi = HI_TRUE;
        }
        else
        {
            HdmiAttr.bEnableHdmi = HI_FALSE;
        }
    }

    if (HI_TRUE == HdmiAttr.bEnableHdmi)
    {
        HdmiAttr.bEnableAudio           = HI_TRUE;
        HdmiAttr.bEnableVideo           = HI_TRUE;
        HdmiAttr.bEnableAudInfoFrame    = HI_TRUE;
        HdmiAttr.bEnableAviInfoFrame    = HI_TRUE;
    }
    else
    {
        HdmiAttr.bEnableAudio           = HI_FALSE;
        HdmiAttr.bEnableVideo           = HI_TRUE;
        HdmiAttr.bEnableAudInfoFrame    = HI_FALSE;
        HdmiAttr.bEnableAviInfoFrame    = HI_FALSE;
        HdmiAttr.enVidOutMode           = HI_UNF_HDMI_VIDEO_MODE_RGB444;
    }

    ret = HI_UNF_HDMI_SetAttr(HdmiId, &HdmiAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_SetAttr failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return;
    }

    ret = HI_UNF_HDMI_Start(HdmiId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Start failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return;
    }
}

static HI_VOID HdmiUnPlugProc(HI_VOID* Param)
{
    HI_S32      ret;
    HI_HANDLE   HdmiId = HI_UNF_HDMI_ID_0;

    ret = HI_UNF_HDMI_Stop(HdmiId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Stop failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }
}

static HI_VOID HdmiEventProc(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID* Param)
{
    switch (event)
    {
        case HI_UNF_HDMI_EVENT_HOTPLUG:
            HdmiHotPlugProc(Param);
            break;

        case HI_UNF_HDMI_EVENT_NO_PLUG:
            HdmiUnPlugProc(Param);
            break;

        case HI_UNF_HDMI_EVENT_EDID_FAIL:
        case HI_UNF_HDMI_EVENT_HDCP_FAIL:
        case HI_UNF_HDMI_EVENT_HDCP_SUCCESS:
        case HI_UNF_HDMI_EVENT_RSEN_CONNECT:
        case HI_UNF_HDMI_EVENT_RSEN_DISCONNECT:
        case HI_UNF_HDMI_EVENT_HDCP_USERSETTING:
        default:
            break;
    }
}

static HI_UNF_ENC_FMT_E FormatStringToEnum(HI_CHAR* str)
{
    if (NULL == str)
    {
        return HI_UNF_ENC_FMT_BUTT;
    }

    if (!strcasecmp(str, "1080P_60"))
    {
        return HI_UNF_ENC_FMT_1080P_60;
    }
    else if (!strcasecmp(str, "1080P_50"))
    {
        return HI_UNF_ENC_FMT_1080P_50;
    }
    else if (!strcasecmp(str, "1080P_30"))
    {
        return HI_UNF_ENC_FMT_1080P_30;
    }
    else if (!strcasecmp(str, "1080P_25"))
    {
        return HI_UNF_ENC_FMT_1080P_25;
    }
    else if (!strcasecmp(str, "1080P_24"))
    {
        return HI_UNF_ENC_FMT_1080P_24;
    }
    else if (!strcasecmp(str, "1080i_60"))
    {
        return HI_UNF_ENC_FMT_1080i_60;
    }
    else if (!strcasecmp(str, "1080i_50"))
    {
        return HI_UNF_ENC_FMT_1080i_50;
    }
    else if (!strcasecmp(str, "720P_60"))
    {
        return HI_UNF_ENC_FMT_720P_60;
    }
    else if (!strcasecmp(str, "720P_50"))
    {
        return HI_UNF_ENC_FMT_720P_50;
    }
    else if (!strcasecmp(str, "576P_50"))
    {
        return HI_UNF_ENC_FMT_576P_50;
    }
    else if (!strcasecmp(str, "480P_60"))
    {
        return HI_UNF_ENC_FMT_480P_60;
    }
    else if (!strcasecmp(str, "PAL"))
    {
        return HI_UNF_ENC_FMT_PAL;
    }
    else if (!strcasecmp(str, "PAL_N"))
    {
        return HI_UNF_ENC_FMT_PAL_N;
    }
    else if (!strcasecmp(str, "PAL_Nc"))
    {
        return HI_UNF_ENC_FMT_PAL_Nc;
    }
    else if (!strcasecmp(str, "NTSC"))
    {
        return HI_UNF_ENC_FMT_NTSC;
    }
    else if (!strcasecmp(str, "NTSC_J"))
    {
        return HI_UNF_ENC_FMT_NTSC_J;
    }
    else if (!strcasecmp(str, "NTSC_PAL_M"))
    {
        return HI_UNF_ENC_FMT_NTSC_PAL_M;
    }
    else if (!strcasecmp(str, "SECAM_SIN"))
    {
        return HI_UNF_ENC_FMT_SECAM_SIN;
    }
    else if (!strcasecmp(str, "SECAM_COS"))
    {
        return HI_UNF_ENC_FMT_SECAM_COS;
    }
    else if (!strcasecmp(str, "2160P_24"))
    {
        return HI_UNF_ENC_FMT_3840X2160_24;
    }
    else if (!strcasecmp(str, "2160P_25"))
    {
        return HI_UNF_ENC_FMT_3840X2160_25;
    }
    else if (!strcasecmp(str, "2160P_30"))
    {
        return HI_UNF_ENC_FMT_3840X2160_30;
    }
    else if (!strcasecmp(str, "2160P_50"))
    {
        return HI_UNF_ENC_FMT_3840X2160_50;
    }
    else if (!strcasecmp(str, "2160P_60"))
    {
        return HI_UNF_ENC_FMT_3840X2160_60;
    }
    else if (!strcasecmp(str, "4096X2160_24"))
    {
        return HI_UNF_ENC_FMT_4096X2160_24;
    }
    else if (!strcasecmp(str, "4096X2160_25"))
    {
        return HI_UNF_ENC_FMT_4096X2160_25;
    }
    else if (!strcasecmp(str, "4096X2160_30"))
    {
        return HI_UNF_ENC_FMT_4096X2160_30;
    }
    else if (!strcasecmp(str, "4096X2160_50"))
    {
        return HI_UNF_ENC_FMT_4096X2160_50;
    }
    else if (!strcasecmp(str, "4096X2160_60"))
    {
        return HI_UNF_ENC_FMT_4096X2160_60;
    }

    return HI_UNF_ENC_FMT_BUTT;
}

HI_S32 HiInit(HI_UNF_ENC_FMT_E fmt)
{
    HI_S32                  ret;
    HI_UNF_SND_ATTR_S       SndAttr;
    HI_UNF_DISP_BG_COLOR_S  BgColor;
    HI_UNF_DISP_OFFSET_S    DispOffset;
    HI_UNF_DISP_INTF_S      DispIntf;
    HI_UNF_HDMI_DELAY_S     HdmiDelay;
    HI_UNF_HDMI_OPEN_PARA_S HdmiPara;
    HI_UNF_ENC_FMT_E        SdFmt           = HI_UNF_ENC_FMT_PAL;
    HI_U32                  ScreenWidth     = 3840;
    HI_U32                  ScreenHeight    = 2160;

    ret = HI_SYS_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_SYS_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        return -1;
    }

    ret = ClearLogo();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] ClearLogo failed\n", __FUNCTION__, __LINE__);
        goto INIT_EXIT;
    }

    ret = HI_UNF_SND_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto INIT_EXIT;
    }

    ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &SndAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_GetDefaultOpenAttr failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto SND_INIT_EXIT;
    }

    ret = HI_UNF_SND_Open(HI_UNF_SND_0, &SndAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_Open failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto SND_INIT_EXIT;
    }

    ret = HI_UNF_DISP_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto SND_OPEN_EXIT;
    }

    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    DispIntf.unIntf.enHdmi = HI_UNF_HDMI_ID_0;

    ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_AttachIntf HDMI failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_INIT_EXIT;
    }

#if defined(HI_DAC_YPBPR_Y) && defined(HI_DAC_YPBPR_PB) && defined(HI_DAC_YPBPR_PR)
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    DispIntf.unIntf.stYPbPr.u8DacY   = HI_DAC_YPBPR_Y;
    DispIntf.unIntf.stYPbPr.u8DacPb  = HI_DAC_YPBPR_PB;
    DispIntf.unIntf.stYPbPr.u8DacPr  = HI_DAC_YPBPR_PR;

    ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_AttachIntf YPBPR failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH1_EXIT;
    }
#endif

#ifdef HI_DAC_CVBS
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    DispIntf.unIntf.stCVBS.u8Dac = HI_DAC_CVBS;

    ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &DispIntf, 1);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_AttachIntf CVBS failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_YPBPR_EXIT;
        return ret;
    }
#endif

    ret = HI_UNF_DISP_Attach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_Attach failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_CVBS_EXIT;
    }

    ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, fmt);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetFormat failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_EXIT;
    }

    switch (fmt)
    {
        case HI_UNF_ENC_FMT_4096X2160_60 :
        case HI_UNF_ENC_FMT_4096X2160_30 :
        case HI_UNF_ENC_FMT_4096X2160_24 :
        case HI_UNF_ENC_FMT_3840X2160_60 :
        case HI_UNF_ENC_FMT_3840X2160_30 :
        case HI_UNF_ENC_FMT_3840X2160_24 :
        case HI_UNF_ENC_FMT_1080P_60 :
        case HI_UNF_ENC_FMT_1080P_30 :
        case HI_UNF_ENC_FMT_1080P_24 :
        case HI_UNF_ENC_FMT_1080i_60 :
        case HI_UNF_ENC_FMT_720P_60 :
        case HI_UNF_ENC_FMT_480P_60 :
        case HI_UNF_ENC_FMT_NTSC :
        {
            SdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }

        case HI_UNF_ENC_FMT_4096X2160_50 :
        case HI_UNF_ENC_FMT_4096X2160_25 :
        case HI_UNF_ENC_FMT_3840X2160_50 :
        case HI_UNF_ENC_FMT_3840X2160_25 :
        case HI_UNF_ENC_FMT_1080P_50 :
        case HI_UNF_ENC_FMT_1080P_25 :
        case HI_UNF_ENC_FMT_1080i_50 :
        case HI_UNF_ENC_FMT_720P_50 :
        case HI_UNF_ENC_FMT_576P_50 :
        case HI_UNF_ENC_FMT_PAL :
        {
            SdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }

        default :
            break;
    }

    ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, SdFmt);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetFormat failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    switch (fmt)
    {
        case HI_UNF_ENC_FMT_4096X2160_60 :
        case HI_UNF_ENC_FMT_4096X2160_50 :
        case HI_UNF_ENC_FMT_4096X2160_30 :
        case HI_UNF_ENC_FMT_4096X2160_25 :
        case HI_UNF_ENC_FMT_4096X2160_24 :
        case HI_UNF_ENC_FMT_3840X2160_60 :
        case HI_UNF_ENC_FMT_3840X2160_50 :
        case HI_UNF_ENC_FMT_3840X2160_30 :
        case HI_UNF_ENC_FMT_3840X2160_25 :
        case HI_UNF_ENC_FMT_3840X2160_24 :
        {
            ScreenWidth     = 3840;
            ScreenHeight    = 2160;
            break;
        }

        case HI_UNF_ENC_FMT_1080P_60 :
        case HI_UNF_ENC_FMT_1080i_60 :
        case HI_UNF_ENC_FMT_1080P_50 :
        case HI_UNF_ENC_FMT_1080i_50 :
        case HI_UNF_ENC_FMT_1080P_30 :
        case HI_UNF_ENC_FMT_1080P_25 :
        case HI_UNF_ENC_FMT_1080P_24 :
        {
            ScreenWidth     = 1920;
            ScreenHeight    = 1080;
            break;
        }

        default :
        {
            ScreenWidth     = 1280;
            ScreenHeight    = 720;
            break;
        }
    }
    //fix visual screen size.
    ScreenWidth     = 1920;
    ScreenHeight    = 1080;

    ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, ScreenWidth, ScreenHeight);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetVirtualScreen failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    DispOffset.u32Left      = 0;
    DispOffset.u32Top       = 0;
    DispOffset.u32Right     = 0;
    DispOffset.u32Bottom    = 0;

    ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY1, &DispOffset);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetScreenOffset failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY0, &DispOffset);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetScreenOffset failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 0;
    BgColor.u8Blue  = 0;

    ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY0, &BgColor);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetBgColor failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_EXIT;
    }

    ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_SetBgColor failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_EXIT;
    }

    ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_Open failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_ATTACH_EXIT;
    }

    ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_Open failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_OPEN1_EXIT;
    }

    ret = HI_UNF_HDMI_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DISP_OPEN0_EXIT;
    }

    ret = HI_UNF_HDMI_GetDelay(HI_UNF_HDMI_ID_0, &HdmiDelay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_GetDelay failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto HDMI_INIT_EXIT;
    }

    HdmiDelay.bForceFmtDelay    = HI_TRUE;
    HdmiDelay.bForceMuteDelay   = HI_TRUE;
    HdmiDelay.u32FmtDelay       = 500;
    HdmiDelay.u32MuteDelay      = 120;

    ret = HI_UNF_HDMI_SetDelay(HI_UNF_HDMI_ID_0, &HdmiDelay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_SetDelay failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto HDMI_INIT_EXIT;
    }

    HdmiProcFunc.pfnHdmiEventCallback   = HdmiEventProc;
    HdmiProcFunc.pPrivateData           = HI_NULL;

    ret = HI_UNF_HDMI_RegCallbackFunc(HI_UNF_HDMI_ID_0, &HdmiProcFunc);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_RegCallbackFunc failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto HDMI_INIT_EXIT;
    }

    HdmiPara.enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;

    ret = HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, &HdmiPara);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Open failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto HDMI_REGISTER_CB;
    }

    ret = HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL/*HI_UNF_VO_DEV_MODE_MOSAIC*/);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto HDMI_OPEN_EXIT;
    }

    ret = HiDemuxInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiDemuxInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto VO_INIT_EXIT;
    }

    ret = HI_UNF_AVPLAY_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_Init failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto DEMUX_INIT_EXIT;
    }

    RegisterAudioLib("libHA.AUDIO.AMRWB.codec.so");
    RegisterAudioLib("libHA.AUDIO.MP3.decode.so");
    RegisterAudioLib("libHA.AUDIO.MP2.decode.so");
    RegisterAudioLib("libHA.AUDIO.AAC.decode.so");
    RegisterAudioLib("libHA.AUDIO.DRA.decode.so");
    RegisterAudioLib("libHA.AUDIO.TRUEHDPASSTHROUGH.decode.so");
    RegisterAudioLib("libHA.AUDIO.AMRNB.codec.so");
    RegisterAudioLib("libHA.AUDIO.WMA.decode.so");
    RegisterAudioLib("libHA.AUDIO.COOK.decode.so");
    RegisterAudioLib("libHA.AUDIO.DTSPASSTHROUGH.decode.so");
    RegisterAudioLib("libHA.AUDIO.AC3PASSTHROUGH.decode.so");
    RegisterAudioLib("libHA.AUDIO.PCM.decode.so");
    RegisterAudioLib("libHA.AUDIO.DOLBYPLUS.decode.so");
    RegisterAudioLib("libHA.AUDIO.DTSHD.decode.so");

    ret = HiPsiInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiPsiInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        goto AVPLAY_INIT_EXIT;
    }

    ret = HiPlayInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiPlayInit failed\n", __FUNCTION__, __LINE__);
        goto PSI_INIT_EXIT;
    }

#ifdef HI_VENC_SUPPORT
    ret = HiTranscodeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiTranscodeInit failed\n", __FUNCTION__, __LINE__);
        goto PLAY_INIT_EXIT;
    }
#endif

    return ret;

#ifdef HI_VENC_SUPPORT
PLAY_INIT_EXIT:
    (HI_VOID)HiPlayDeInit();
#endif
PSI_INIT_EXIT:
    (HI_VOID)HiPsiDeInit();
AVPLAY_INIT_EXIT:
    (HI_VOID)HI_UNF_AVPLAY_DeInit();
DEMUX_INIT_EXIT:
    (HI_VOID)HiDemuxDeInit();
VO_INIT_EXIT:
    (HI_VOID)HI_UNF_VO_DeInit();
HDMI_OPEN_EXIT:
    (HI_VOID)HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_0);
HDMI_REGISTER_CB:
    HI_UNF_HDMI_UnRegCallbackFunc(HI_UNF_HDMI_ID_0, &HdmiProcFunc);
HDMI_INIT_EXIT:
    (HI_VOID)HI_UNF_HDMI_DeInit();
DISP_OPEN0_EXIT:
    (HI_VOID)HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
DISP_OPEN1_EXIT:
    (HI_VOID)HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
DISP_ATTACH_EXIT:
    (HI_VOID)HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
DISP_ATTACH_CVBS_EXIT:
#ifdef HI_DAC_CVBS
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    DispIntf.unIntf.stCVBS.u8Dac = HI_DAC_CVBS;
    (HI_VOID)HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY0, &DispIntf, 1);
DISP_ATTACH_YPBPR_EXIT:
#endif
#if defined(HI_DAC_YPBPR_Y) && defined(HI_DAC_YPBPR_PB) && defined(HI_DAC_YPBPR_PR)
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    DispIntf.unIntf.stYPbPr.u8DacY   = HI_DAC_YPBPR_Y;
    DispIntf.unIntf.stYPbPr.u8DacPb  = HI_DAC_YPBPR_PB;
    DispIntf.unIntf.stYPbPr.u8DacPr  = HI_DAC_YPBPR_PR;
    (HI_VOID)HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
DISP_ATTACH1_EXIT:
#endif
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    DispIntf.unIntf.enHdmi = HI_UNF_HDMI_ID_0;
    (HI_VOID)HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
DISP_INIT_EXIT:
    (HI_VOID)HI_UNF_DISP_DeInit();
SND_OPEN_EXIT:
    (HI_VOID)HI_UNF_SND_Close(HI_UNF_SND_0);
SND_INIT_EXIT:
    (HI_VOID)HI_UNF_SND_DeInit();
INIT_EXIT:
    (HI_VOID)HI_SYS_DeInit();

    return ret;
}

static HI_VOID HiDeInit(HI_VOID)
{
    HI_S32  ret;

#ifdef HI_VENC_SUPPORT
    ret = HiTranscodeDeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiTranscodeDeInit failed\n", __FUNCTION__, __LINE__);
    }
#endif

    ret = HiPlayDeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiPlayDeInit failed\n", __FUNCTION__, __LINE__);
    }

    ret = HiPsiDeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiPsiDeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HiDemuxDeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HiDemuxDeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_VO_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_DeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_0);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Stop failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_0);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_Close failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_HDMI_UnRegCallbackFunc(HI_UNF_HDMI_ID_0, &HdmiProcFunc);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_UnRegCallbackFunc failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_HDMI_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_HDMI_DeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_DISP_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DISP_DeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_Close failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_SND_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_DeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_SYS_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_SYS_DeInit failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32              ret;
    HI_UNF_ENC_FMT_E    Format  = HI_UNF_ENC_FMT_1080P_60;
    HI_U32              DecNum  = 2;
    HI_U32              EncNum  = 1;
    HI_CHAR*            TsFile1 = HI_NULL;
    HI_CHAR*            TsFile2 = HI_NULL;
#ifdef HI_VENC_SUPPORT
    HI_CHAR*            Path    = HI_NULL;
#endif
    HI_U32              i;
    HI_BOOL             bHDDisplay = HI_TRUE;
    HI_BOOL             bDoGpu = HI_TRUE;
    HI_U32              u32JpegMode = 1;
    HI_SYS_VERSION_S    stVersion;

    if (argc < 4)
    {
        printf("Usage: %s format ts_file1 ts_file2\n", argv[0]);
        printf("\tformat\t- 2160P_60, 2160P_50, 2160P_30, 2160P_25, 2160P_24,\n");
        printf("\t\t  1080P_60, 1080P_50, 1080i_60, 1080i_50,\n");
        printf("\t\t  720P_60, 720P_50, 576P_50, 480P_60, PAL\n");
        printf("\t\t  default 1080P_60\n");
        printf("example:\n");
        printf("\t%s 1080i_50 ./cctv1.ts ./cctv1.ts\n", argv[0]);
        return -1;
    }

    TsFile1 = argv[2];
    TsFile2 = argv[3];
    Format = FormatStringToEnum(argv[1]);
    if (HI_UNF_ENC_FMT_BUTT == Format)
    {
        Format = HI_UNF_ENC_FMT_1080P_60;
    }

    ret = HiInit(Format);
    if (HI_SUCCESS != ret)
    {
        printf("HiInit failed 0x%x\n", ret);

        return -1;
    }
    memset(&stVersion, 0x00, sizeof(stVersion));
    ret = HI_SYS_GetVersion(&stVersion);
    if (HI_SUCCESS != ret)
    {
        printf("get chip info failed,ret = 0x%08x\n", ret);
        HiDeInit();
        return -1;
    }

    /*先处理98mv200的*/
    switch (stVersion.enChipTypeHardWare)
    {
        case HI_CHIP_TYPE_HI3798M:
            if (HI_CHIP_VERSION_V200 == stVersion.enChipVersion)
            {
#ifndef HI_VENC_SUPPORT
                printf("please open the venc in make menuconfig\n");
                HiDeInit();
                return -1;
#endif
#ifndef HI_GPU_SUPPORT
                printf("please open the gpu in make menuconfig\n");
                HiDeInit();
                return -1;
#endif
            }
            break;
        default:
            break;
    }
    if (2 < DecNum)
    {
        bHDDisplay = HI_FALSE;
    }
    for (i = 0; i < DecNum; i++)
    {
        if (0 == i)
        {
            HiPlayTs(i, TsFile1, HI_INVALID_PID, HI_NULL, HI_INVALID_PID, HI_NULL, bHDDisplay);
        }
        else if (3 > i)
        {
            if (0 == strcmp(TsFile2, "null"))
            {
                HiPlayTs(i, TsFile1, HI_INVALID_PID, HI_NULL, HI_INVALID_PID, HI_NULL, bHDDisplay);
            }
            else
            {
                HiPlayTs(i, TsFile2, HI_INVALID_PID, HI_NULL, HI_INVALID_PID, HI_NULL, bHDDisplay);
            }
        }
        else
        {
            printf("the %d ts play has been created\n", i);
        }
    }

#ifdef HI_VENC_SUPPORT
    EncNum = (EncNum < HI_TRANSCODE_COUNT) ? EncNum : HI_TRANSCODE_COUNT;
    for (i = 0; i < EncNum; i++)
    {
        HI_U32  PlayId = (i < EncNum) ? i : 0;
        HI_CHAR VidFile[MAX_FILENAME_LEN];
        HI_CHAR AudFile[MAX_FILENAME_LEN];

        sprintf(VidFile, "%s/vid_%d.h264", Path, i);
        sprintf(AudFile, "%s/aud_%d.aac", Path, i);

        PlayId = 1; //only support 1080p transcode, not support 4k.
        HiTranscodeStart(PlayId, VidFile, AudFile);
    }
#endif
    HiOsdStart(u32JpegMode);
    if (HI_TRUE == bDoGpu)
    {
#ifdef HI_GPU_SUPPORT
        sleep(3);
        HI_SPHERE_Init();
#else
        printf("Not support gpu!\n");
#endif
    }
    printf("DecNum=%u, EncNum=%u\n", DecNum, EncNum);

    while (1)
    {
#if 1
        HI_CHAR str[32] = {0};

        fgets(str, sizeof(str), stdin);

        if ('q' == str[0])
        {
            printf("quit\n");
            break;
        }
#else
        sleep(1);
#endif
    }

    if (HI_TRUE == bDoGpu)
    {
#ifdef HI_GPU_SUPPORT
        HI_SPHERE_DeInit();
#else
        printf("Not support gpu\n");
#endif
    }
    HiOsdStop();
    HiDeInit();

    return 0;
}

