
#ifndef __DRV_HDMI_INTF_H__
#define __DRV_HDMI_INTF_H__
#include "hi_type.h"
#include "hdmi_hal.h"
#include "drv_hdmi_common.h"
#include "drv_hdmi_ioctl.h"
#include "drv_hdmi_edid.h"
#include "drv_hdmi_event.h"

#ifdef HDMI_TEE_SUPPORT
#include "drv_hdmi_tee.h"
#endif

typedef enum
{
	STATE_PLUG_UNKNOWN = -1,
	STATE_HOTPLUGOUT = 0,
	STATE_HOTPLUGIN = 1
}HDMI_SWITCH_STATE;


typedef enum
{
	HDMI_AO_MODE_DRV_AO,		//acr &  hbra/audio sample pakege enable from drv audio
	HDMI_AO_MODE_DRV_SELF,		//acr &  hbra/audio sample pakege enable from drv hdmi
	HDMI_AO_MODE_UNF,			//acr &  hbra/audio sample pakege enable from unf attr bAudioEnable
	HDMI_AO_MODE_INFOFRAME,		//audio infoframe enable from unf attr bAudioInfoframe

}HDMI_AO_MODE_E;


typedef struct {
	HI_BOOL		bAoAppEnable;
	HI_BOOL		bAoIfAppEanble;
	HI_BOOL		bAoDrvEnable;
	HI_BOOL		bAoSelEanble;
}HDMI_AO_ENABLE_S;

typedef struct
{
    HI_U32                   u32HdmiDevId;
    HI_U32                   u32KernelCnt;
    HI_U32                   u32UserCnt;
    HI_U32                   u32UserCallBackCnt;
    HI_U32                   *pu32VirtualBaseAddr;
    HI_BOOL                  bEmiEnable;
    HI_BOOL                  bOpenCapGet;
    HI_BOOL                  bResumeEnable;
    HDMI_RUN_STATE_E         enRunState;
    HDMI_TRANSITION_STATE_E  enTransitionState;
    HDMI_TMDS_MODE_E         enTmdsMode;
    HMDI_CALLBACK            pKCallback;
    HDMI_THREAD_INFO_S       stThreadInfo;
    HDMI_HDCP_INFO_S         stHdcpInfo;
    HDMI_CEC_INFO_S          stCecInfo;
    HDMI_EDID_INFO_S         stEdidInfo;
    HDMI_EVENT_INFO_S        stEventInfo;
    HDMI_INFOFRAME_S         stInfoFrame;
	HDMI_AO_ENABLE_S		 stAudioEn;
    HDMI_ATTR_S              stAttr;
    HDMI_DELAY_S             stDelay;
    HDMI_HAL_S*              pstHdmiHal;
    HDMI_INTF_STATUS_S       stIntfStatus;
    //HDMI_DEBUG_CONEXT_S      stDebugContext;
    HDMI_MUTEX				 stMutexThread;
    HDMI_HDR_INFO_S          stHdrInfo;
#ifdef HDMI_TEE_SUPPORT
    HDMI_TEE_INFO_S          stTeeInfo;
#endif
}HDMI_DEVICE_S;

HI_S32 DRV_HDMI_Init(HI_VOID);
HI_S32 DRV_HDMI_DeInit(HI_VOID);
HI_S32 DRV_HDMI_Open(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bUser);
HI_S32 DRV_HDMI_Close(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bUser);
HI_S32 DRV_HDMI_Start(HDMI_DEVICE_S* pstHdmiDev);
HI_S32 DRV_HDMI_Stop(HDMI_DEVICE_S* pstHdmiDev);

HI_S32 DRV_HDMI_DeepColorSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEEP_COLOR_E enDeepColor);
HI_S32 DRV_HDMI_DeepColorGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEEP_COLOR_E* enDeepColor);
HI_S32 DRV_HDMI_XvYCCModeSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);

HI_VOID DRV_HDMI_AVMuteSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bAvMute);
HI_S32 DRV_HDMI_VOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr);
//HI_S32 DRV_HDMI_PreFormat(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr);
HI_S32 DRV_HDMI_VideoOutputEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);

HI_S32 DRV_HDMI_PlayStatusGet(HDMI_DEVICE_S* pstHdmiDev, HI_U32* u32Status);
#ifdef HDMI_HDCP_SUPPORT
HI_S32 DRV_HDMI_KeyLoad(HDMI_DEVICE_S* pstHdmiDev, HDMI_LOAD_KEY_S *pstLoadKey,HI_BOOL bFromUser);
#endif
HI_S32 DRV_HDMI_AOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr);
HI_S32 DRV_HDMI_AOAttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr);


HI_S32 DRV_HDMI_AttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr);
HI_S32 DRV_HDMI_AttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr);

HI_S32 HI_DRV_HDMI_PixClkGet(HI_UNF_ENC_FMT_E enFormat,HI_U32 *pu32PixClk);

//HI_S32 DRV_HDMI_SinkCapabilityGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_SINK_CAPABILITY_S *pstSinkCapability);
//HI_S32 DRV_HDMI_EdidUpdate(HDMI_DEVICE_S* pstHdmiDev, HDMI_EDID_RAWDATA_S *pstEDID);



//HI_S32 DRV_HDMI_CECAddressGet(HDMI_DEVICE_S* pstHdmiDev, HI_U8 *pPhyAddr, HI_U8 *pLogicalAddr);
#ifdef HDMI_CEC_SUPPORT
HI_S32 DRV_HDMI_CecCmdSend(HDMI_DEVICE_S* pstHdmiDev,  HDMI_CEC_CMD_S  *pstCecCmd);
HI_S32 DRV_HDMI_CecCmdReceive(HDMI_DEVICE_S* pstHdmiDev, HDMI_CEC_CMD_S  *pstCecCmd);
HI_S32 DRV_HDMI_CecStatusGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_CEC_INFO_S  *pstCecStatus);
HI_S32 DRV_HDMI_CecEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable);
#endif
HI_S32 DRV_HDMI_InfoFrameGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_INFOFRAME_ID_E enInfoFrameId, HDMI_INFOFRAME_U *puInfoFrame);
HI_S32 DRV_HDMI_InfoFrameSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_INFOFRAME_ID_E enInfoFrameId, HDMI_INFOFRAME_U *puInfoFrame);

HI_S32 DRV_HDMI_CmdProcess(unsigned int cmd, HI_VOID *arg, HI_BOOL bUser);
HDMI_VIDEO_TIMING_E DispFmt2HdmiTiming(HDMI_DEVICE_S* pstHdmiDev, HI_U32 u32DispFmt);
HDMI_DEVICE_S* GetHdmiDevice(HDMI_DEVICE_ID_E enHdmiID);
HDMI_DEFAULT_ACTION_E DRV_HDMI_DefaultActionGet(HDMI_DEVICE_S* pstHdmiDev);
HI_S32 DRV_HDMI_DefaultActionSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DEFAULT_ACTION_E enAction);
HI_S32 DRV_HDMI_ThreadStateSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_THREAD_STATE_E enState);

HI_S32 DRV_HDMI_DelayGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DELAY_S *pHdmiDelay);
HI_S32 DRV_HDMI_DelaySet(HDMI_DEVICE_S* pstHdmiDev, HDMI_DELAY_S *pHdmiDelay);
HI_S32 DRV_HDMI_EmiSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstHwVOAttr, HDMI_APP_ATTR_S* pstHwAPPAttr);
HI_S32 DRV_HDMI_AudioEnable(HDMI_DEVICE_S* pstHdmiDev,HDMI_AO_MODE_E enMode,HI_BOOL bEnable);

#endif
