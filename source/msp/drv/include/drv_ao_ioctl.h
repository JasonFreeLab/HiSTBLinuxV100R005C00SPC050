/******************************************************************************

Copyright (C), 2009-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_ao_ioctl.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/09/22
Last Modified :
Description   : ao
Function List :
History       :
* main\1    2012-09-22   z40717     init.
******************************************************************************/
#ifndef __DRV_AO_IOCTL_H__
#define __DRV_AO_IOCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_unf_sound.h"
#include "hi_drv_ao.h"

typedef struct hiAO_SND_OpenDefault_Param_S
{
    HI_UNF_SND_E       enSound;
    HI_UNF_SND_ATTR_S  stAttr;
} AO_SND_OpenDefault_Param_S, *AO_SND_OpenDefault_Param_S_PTR;

typedef struct hiAO_SND_Open_Param_S
{
    HI_UNF_SND_E       enSound;
    HI_UNF_SND_ATTR_S  stAttr;
} AO_SND_Open_Param_S, *AO_SND_Open_Param_S_PTR;

typedef struct hiAO_SND_Mute_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bMute;
} AO_SND_Mute_Param_S, *AO_SND_Mute_Param_S_PTR;

typedef struct hiAO_SND_HdmiMode_Param_S
{
    HI_UNF_SND_E                        enSound;
    HI_UNF_SND_OUTPUTPORT_E             enOutPort;
    HI_UNF_SND_HDMI_MODE_E              enMode;
} AO_SND_HdmiMode_Param_S, *AO_SND_HdmiMode_Param_S_PTR;

typedef struct hiAO_SND_SpdifMode_Param_S
{
    HI_UNF_SND_E                        enSound;
    HI_UNF_SND_OUTPUTPORT_E             enOutPort;
    HI_UNF_SND_SPDIF_MODE_E             enMode;
} AO_SND_SpdifMode_Param_S, *AO_SND_SpdifMode_Param_S_PTR;

typedef struct hiAO_SND_SpdifSCMSMode_Param_S
{
    HI_UNF_SND_E                        enSound;
    HI_UNF_SND_OUTPUTPORT_E             enOutPort;
    HI_UNF_SND_SPDIF_SCMSMODE_E         enSCMSMode;
} AO_SND_SpdifSCMSMode_Param_S, *AO_SND_SpdifSCMSMode_Param_S_PTR;

typedef struct hiAO_SND_SpdifCategoryCode_Param_S
{
    HI_UNF_SND_E                        enSound;
    HI_UNF_SND_OUTPUTPORT_E             enOutPort;
    HI_UNF_SND_SPDIF_CATEGORYCODE_E     enCategoryCode;
} AO_SND_SpdifCategoryCode_Param_S, *AO_SND_SpdifCategoryCode_Param_S_PTR;

typedef struct hiAO_SND_Volume_Param_S
{
    HI_UNF_SND_E                        enSound;
    HI_UNF_SND_OUTPUTPORT_E             enOutPort;
    HI_UNF_SND_GAIN_ATTR_S stGain;
} AO_SND_Volume_Param_S, *AO_SND_Volume_Param_S_PTR;

typedef struct hiAO_SND_SampleRate_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_UNF_SAMPLE_RATE_E    enSampleRate;
} AO_SND_SampleRate_Param_S, *AO_SND_SampleRate_Param_S_PTR;

typedef struct hiAO_SND_TrackMode_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_UNF_TRACK_MODE_E     enMode;
} AO_SND_TrackMode_Param_S, *AO_SND_TrackMode_Param_S_PTR;

typedef struct hiAO_SND_AllTrackMute_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_BOOL                 bMute;
} AO_SND_AllTrackMute_Param_S, *AO_SND_AllTrackMute_Param_S_PTR;

typedef struct hiAO_SND_SmartVolume_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bSmartVolume;
} AO_SND_SmartVolume_Param_S, *AO_SND_SmartVolume_Param_S_PTR;

typedef struct hiAO_SND_Adac_Enable_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_BOOL                 bEnable;
} AO_SND_Adac_Enable_Param_S, *AO_SND_Adac_Enable_Param_S_PTR;

typedef struct hiAO_SND_PreciVolume_Param_S
{
    HI_UNF_SND_E                    enSound;
    HI_UNF_SND_OUTPUTPORT_E         enOutPort;
    HI_UNF_SND_PRECIGAIN_ATTR_S     stPreciGain;
} AO_SND_PreciVolume_Param_S, *AO_SND_PreciVolume_Param_S_PTR;

typedef struct hiAO_SND_Balance_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_S32                  s32Balance;
} AO_SND_Balance_Param_S, *AO_SND_Balance_Param_S_PTR;

typedef struct hiAO_SND_ARC_ENABLE_Param_S
{
    HI_UNF_SND_E                enSound;
    HI_UNF_SND_OUTPUTPORT_E     enOutPort;
    HI_BOOL                     bEnable;
} AO_SND_ARC_ENABLE_Param_S, *AO_SND_ARC_ENABLE_Param_S_PTR;

#ifdef __DPT__
typedef struct hiAO_SND_ARC_MODE_Param_S
{
    HI_UNF_SND_E                enSound;
    HI_UNF_SND_OUTPUTPORT_E     enOutPort;
    HI_UNF_SND_ARC_AUDIO_MODE_E enMode;
} AO_SND_ARC_MODE_Param_S, *AO_SND_ARC_MODE_Param_S_PTR;

typedef struct hiAO_SND_ARC_CAP_Param_S
{
    HI_UNF_SND_E                enSound;
    HI_UNF_SND_OUTPUTPORT_E     enOutPort;
    HI_UNF_SND_ARC_AUDIO_CAP_S  stCap;
} AO_SND_ARC_CAP_Param_S, *AO_SND_ARC_CAP_Param_S_PTR;

typedef struct hiAO_SND_Geq_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_GEQ_ATTR_S   stEqAttr;
} AO_SND_Geq_Param_S, *AO_SND_Geq_Param_S_PTR;
#endif

typedef struct hiAO_SND_Peq_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_UNF_SND_PEQ_ATTR_S   stEqAttr;
} AO_SND_Peq_Param_S, *AO_SND_Peq_Param_S_PTR;

typedef struct hiAO_SND_Eq_Enable_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bEqEnable;
} AO_SND_Eq_Enable_S, *AO_SND_Eq_Enable_S_PTR;

typedef struct hiAO_SND_Geq_Gain_S
{
    HI_UNF_SND_E            enSound;
    HI_U32                  u32Band;
    HI_S32                  s32Gain;
} AO_SND_Geq_Gain_S, *AO_SND_Geq_Gain_S_PTR;

typedef struct hiAO_SND_Avc_Enable_S
{
    HI_UNF_SND_E            enSound;
    HI_BOOL                 bAvcEnable;
} AO_SND_Avc_Enable_S, *AO_SND_Avc_Enable_S_PTR;

typedef struct hiAO_SND_Avc_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_AVC_ATTR_S   stAvcAttr;
} AO_SND_Avc_Param_S, *AO_SND_Avc_Param_S_PTR;

typedef struct hiAO_SND_Drc_Enable_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bDrcEnable;
} AO_SND_Drc_Enable_S, *AO_SND_Drc_Enable_S_PTR;

typedef struct hiAO_SND_Drc_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_UNF_SND_DRC_ATTR_S   stDrcAttr;
} AO_SND_Drc_Param_S, *AO_SND_Drc_Param_S_PTR;

#ifdef __DPT__
typedef struct hiAO_SND_TrackInfo_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_TRACK_INFO_S stTrackInfo;
} AO_SND_TrackInfo_Param_S, *AO_SND_TrackInfo_Param_S_PTR;
#endif

typedef struct hiAO_Track_Create_Param_S
{
    HI_UNF_SND_E             enSound;
    HI_UNF_AUDIOTRACK_ATTR_S stAttr;
    HI_BOOL                  bAlsaTrack;      //if bAlsaTrack = HI_TRUE ALSA, or UNF
    AO_BUF_ATTR_S            stBuf;          //Only for compatible alsa
    HI_HANDLE                hTrack;
} AO_Track_Create_Param_S, *AO_Track_Create_Param_S_PTR;

typedef struct hiAO_SND_ADOutput_Enable_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bADOutputEnable;
} AO_SND_ADOutput_Enable_S, *AO_SND_ADOutput_Enable_S_PTR;

typedef struct hiAO_Track_Attr_Param_S
{
    HI_HANDLE                    hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S     stAttr;
} AO_Track_Attr_Param_S, *AO_Track_Attr_Param_S_PTR;

typedef struct hiAO_Track_Weight_Param_S
{
    HI_HANDLE               hTrack;
    HI_UNF_SND_GAIN_ATTR_S  stTrackGain;
} AO_Track_Weight_Param_S, *AO_Track_Weight_Param_S_PTR;

typedef struct hiAO_Track_AbsGain_Param_S
{
    HI_HANDLE               hTrack;
    HI_UNF_SND_ABSGAIN_ATTR_S  stTrackAbsGain;
} AO_Track_AbsGain_Param_S, *AO_Track_AbsGain_Param_S_PTR;

typedef struct hiAO_Track_Prescale_Param_S
{
    HI_HANDLE               hTrack;
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;
} AO_Track_Prescale_Param_S, *AO_Track_Prescale_Param_S_PTR;

typedef struct hiAO_Track_Mute_Param_S
{
    HI_HANDLE               hTrack;
    HI_BOOL                 bMute;
} AO_Track_Mute_Param_S, *AO_Track_Mute_Param_S_PTR;

typedef struct hiAO_Track_ChannelMode_Param_S
{
    HI_HANDLE               hTrack;
    HI_UNF_TRACK_MODE_E     enMode;
} AO_Track_ChannelMode_Param_S, *AO_Track_ChannelMode_Param_S_PTR;

typedef struct hiAO_Track_SendData_Param_S
{
    HI_HANDLE              hTrack;
    AO_FRAMEINFO_S         stAOFrame;
} AO_Track_SendData_Param_S, *AO_Track_SendData_Param_S_PTR;

typedef struct
{
    HI_HANDLE                hTrack;
    HI_U32                   u32AipRegAddr;
    HI_U32                   u32BitPerSample;
    HI_U32                   u32SampleRate;
    HI_U32                   u32Channels;
} AO_Track_Mmap_Param_S, *AO_Track_Mmap_Param_S_PTR;

typedef struct hiAO_Track_SpeedAdjust_Param_S
{
    HI_HANDLE                 hTrack;
    AO_SND_SPEEDADJUST_TYPE_E enType;
    HI_S32                    s32Speed;
} AO_Track_SpeedAdjust_Param_S, *AO_Track_SpeedAdjust_Param_S_PTR;

typedef struct hiAO_Track_DelayMs_Param_S
{
    HI_HANDLE hTrack;
    HI_U32    u32DelayMs;
} AO_Track_DelayMs_Param_S, *AO_Track_DelayMs_Param_S_PTR;

typedef struct hiAO_Track_BufEmpty_Param_S
{
    HI_HANDLE hTrack;
    HI_BOOL   bEmpty;
} AO_Track_BufEmpty_Param_S, *AO_Track_BufEmpty_Param_S_PTR;

typedef struct hiAO_Track_EosFlag_Param_S
{
    HI_HANDLE hTrack;
    HI_BOOL   bEosFlag;
} AO_Track_EosFlag_Param_S, *AO_Track_EosFlag_Param_S_PTR;

typedef struct hiAO_Track_AttAi_Param_S
{
    HI_HANDLE hTrack;
    HI_HANDLE hAi;
} AO_Track_AttAi_Param_S, *AO_Track_AttAi_Param_S_PTR;

typedef struct hiAO_SND_AllCastMute_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_BOOL                 bMute;
} AO_SND_AllCastMute_Param_S, *AO_SND_AllCastMute_Param_S_PTR;

typedef struct hiAO_Cast_Mute_Param_S
{
    HI_HANDLE               hCast;
    HI_BOOL                 bMute;
} AO_Cast_Mute_Param_S, *AO_Cast_Mute_Param_S_PTR;

typedef struct hiAO_Cast_AbsGain_Param_S
{
    HI_HANDLE               hCast;
    HI_UNF_SND_ABSGAIN_ATTR_S  stCastAbsGain;
} AO_Cast_AbsGain_Param_S, *AO_Cast_AbsGain_Param_S_PTR;

typedef struct hiAO_Cast_Create_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_HANDLE               hCast;
    HI_U32                  u32ReqSize;
    HI_UNF_SND_CAST_ATTR_S  stCastAttr;
} AO_Cast_Create_Param_S, *AO_Cast_Create_Param_S_PTR;

typedef struct hiAO_Cast_Info_Param_S
{
    HI_HANDLE             hCast;
    HI_VIRT_ADDR_T        tUserVirtAddr;
    HI_VIRT_ADDR_T        tKernelVirtAddr;
    HI_PHYS_ADDR_T        tPhyAddr;

    HI_U32                u32FrameBytes;
    HI_U32                u32FrameSamples;
    HI_U32                u32Channels;
    HI_S32                s32BitPerSample;
} AO_Cast_Info_Param_S, *AO_Cast_Info_Param_S_PTR;

typedef struct hiAO_Cast_Enable_Param_S
{
    HI_HANDLE            hCast;
    HI_BOOL              bCastEnable;
} AO_Cast_Enable_Param_S, *AO_Cast_Enable_Param_S_PTR;

typedef struct hiAO_Cast_Data_Param_S
{
    HI_HANDLE             hCast;
    HI_U32                u32FrameBytes;
    HI_U32                u32SampleBytes;

    HI_U32                u32DataOffset;
    AO_FRAMEINFO_S        stAOFrame;
} AO_Cast_Data_Param_S, *AO_Cast_Data_Param_S_PTR;

typedef struct hiAO_SND_AttAef_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_U32                  u32AefId;
    HI_U32                  u32AefProcAddr;
    AO_AEF_ATTR_S           stAefAttr;
} AO_SND_AttAef_Param_S, *AO_SND_AttAef_Param_S_PTR;

typedef struct hiAO_SND_AefBypass_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL                 bBypass;
} AO_SND_AefBypass_Param_S, *AO_SND_AefBypass_Param_S_PTR;

typedef struct hiAO_SND_GET_XRUN_S
{
    HI_UNF_SND_E            enSound;
    HI_U32                  u32Count;
} AO_SND_Get_Xrun_Param_S, *AO_SND_Get_Xrun_Param_S_PTR;

typedef struct
{
    HI_UNF_SND_E            enSound;
    AO_AEF_BUF_ATTR_S       stAefBuf;
} AO_SND_Aef_Buf_Param_S, *AO_SND_Aef_Buf_Param_S_PTR;

typedef struct hiAO_SND_SET_LOWLATENCY
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E eOutPort;
    HI_U32                  u32LatencyMs;
} AO_SND_Set_LowLatency_Param_S, *AO_SND_Set_LowLatency_Param_S_PTR;

typedef struct hiAO_Track_Priority_Param_S
{
    HI_HANDLE hTrack;
    HI_BOOL   bEnable;
} AO_Track_Priority_Param_S, *AO_Track_Priority_Param_S_PTR;

typedef struct hiAO_Track_FifoBypass_Param_S
{
    HI_HANDLE hTrack;
    HI_BOOL   bEnable;
} AO_Track_FifoBypass_Param_S, *AO_Track_FifoBypass_Param_S_PTR;

typedef struct hiAO_SND_Debug_Param_S
{
    HI_UNF_SND_E                enSound;
    AO_DEBUG_ATTR_S             stDebugAttr;
} AO_SND_DEBUG_Param_S, *AO_SND_DEBUG_Param_S_PTR;

typedef struct hiAO_SND_TrackDuplicate_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_HANDLE               hTrack;
    HI_BOOL                 bEnable;
} AO_SND_TrackDuplicate_Param_S, *AO_SND_TrackDuplicate_Param_S_PTR;

typedef struct hiAO_SND_SET_ALSA_PRESCALE_S
{
    HI_UNF_SND_E enSound;
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;
} AO_SND_Set_Alsa_Prescale_S, *AO_SND_Set_Alsa_Prescale_S_PTR;

typedef struct hiAO_SND_OpDelay_Param_S
{
    HI_UNF_SND_E            enSound;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_U32                  u32DelayMs;
} AO_SND_OpDelay_Param_S, *AO_SND_OpDelay_Param_S_PTR;

#ifdef __DPT__
typedef struct hiAO_Track_Source_Param_S
{
    HI_HANDLE               hTrack;
    HI_UNF_SND_SOURCE_E     enSource;
} AO_Track_Source_Param_S, *AO_Track_Source_Param_S_PTR;

typedef struct hiAO_SND_TrackConfig_Param_S
{
    HI_UNF_SND_E                   enSound;
    HI_UNF_SND_TRACK_CONFIG_S      stTrackConfig;
} AO_SND_TrackConfig_Param_S, *AO_SND_TrackConfig_Param_S_PTR;
#endif

typedef struct hiAO_SND_SET_ExtDelayMs
{
    HI_UNF_SND_E            enSound;
    HI_U32                  u32DelayMs;
} AO_SND_Set_ExtDelayMs_Param_S, *AO_SND_Set_ExtDelayMs_Param_S_PTR;

typedef struct
{
    HI_UNF_SND_E           enSound;
    SND_PORT_KERNEL_ATTR_S stPortKAttr[HI_UNF_SND_OUTPUTPORT_MAX];
} AO_SND_DMACreate_Param_S, *AO_SND_DMACreate_Param_S_PTR;

typedef struct
{
    HI_UNF_SND_E           enSound;
} AO_SND_DMADestory_Param_S, *AO_SND_DMADestory_Param_S_PTR;

typedef struct
{
    HI_UNF_SND_E           enSound;
    HI_UNF_SAMPLE_RATE_E   enSampleRate;
} AO_SND_DMASetSampleRate_Param_S, *AO_SND_DMASetSampleRate_Param_S_PTR;

enum
{
    CMD_ID_AO_SND_GETDEFOPENATTR,
    CMD_ID_AO_SND_OPEN,
    CMD_ID_AO_SND_CLOSE,

    CMD_ID_AO_SND_SETMUTE,
    CMD_ID_AO_SND_GETMUTE,
    CMD_ID_AO_SND_SETVOLUME,
    CMD_ID_AO_SND_GETVOLUME,

    CMD_ID_AO_SND_SETHDMIMODE,
    CMD_ID_AO_SND_GETHDMIMODE,

    CMD_ID_AO_SND_SETSPDIFMODE,
    CMD_ID_AO_SND_GETSPDIFMODE,

    CMD_ID_AO_SND_SETSAMPLERATE,
    CMD_ID_AO_SND_GETSAMPLERATE,

    CMD_ID_AO_SND_SETTRACKMODE,
    CMD_ID_AO_SND_GETTRACKMODE,

    CMD_ID_AO_SND_SETSMARTVOLUME,
    CMD_ID_AO_SND_GETSMARTVOLUME,

    CMD_ID_AO_SND_SETSPDIFSCMSMODE,
    CMD_ID_AO_SND_GETSPDIFSCMSMODE,
    CMD_ID_AO_SND_SETSPDIFCATEGORYCODE,
    CMD_ID_AO_SND_GETSPDIFCATEGORYCODE,

    CMD_ID_AO_SND_SETALLTRACKMUTE,
    CMD_ID_AO_SND_GETALLTRACKMUTE,

    CMD_ID_AO_SND_SETADACENABLE,
    CMD_ID_AO_SND_GETADACENABLE,

    CMD_ID_AO_SND_ATTACHTRACK,
    CMD_ID_AO_SND_DETACHTRACK,

    CMD_ID_AO_SND_SETPRECIVOL,
    CMD_ID_AO_SND_GETPRECIVOL,

    CMD_ID_AO_SND_SETALSAPRESCALE,

    CMD_ID_AO_SND_SETBALANCE,
    CMD_ID_AO_SND_GETBALANCE,

#ifdef __DPT__
    CMD_ID_AO_SND_SETARCENABLE,
    CMD_ID_AO_SND_GETARCENABLE,
    CMD_ID_AO_SND_SETARCMODE,
    CMD_ID_AO_SND_GETARCMODE,
    CMD_ID_AO_SND_SETARCCAP,
    CMD_ID_AO_SND_GETARCCAP,
#endif

    CMD_ID_AO_SND_SETAVCATTR,
    CMD_ID_AO_SND_GETAVCATTR,
    CMD_ID_AO_SND_SETAVCENABLE,
    CMD_ID_AO_SND_GETAVCENABLE,

#ifdef __DPT__
    CMD_ID_AO_SND_SETGEQATTR,
    CMD_ID_AO_SND_GETGEQATTR,
    CMD_ID_AO_SND_SETGEQENABLE,
    CMD_ID_AO_SND_GETGEQENABLE,
    CMD_ID_AO_SND_SETGEQGAIN,
    CMD_ID_AO_SND_GETGEQGAIN,
#endif

    CMD_ID_AO_SND_SETDRCENABLE,
    CMD_ID_AO_SND_GETDRCENABLE,
    CMD_ID_AO_SND_SETDRCATTR,
    CMD_ID_AO_SND_GETDRCATTR,

    CMD_ID_AO_SND_SETPEQATTR,
    CMD_ID_AO_SND_GETPEQATTR,
    CMD_ID_AO_SND_SETPEQENABLE,
    CMD_ID_AO_SND_GETPEQENABLE,

#ifdef __DPT__
    CMD_ID_AO_SND_ATTACHAEF,
    CMD_ID_AO_SND_DETACHAEF,
    CMD_ID_AO_SND_SETAEFBYPASS,
    CMD_ID_AO_SND_GETAEFBYPASS,

    CMD_ID_AO_SND_GETTRACKINFO,

    CMD_ID_AO_SND_GETAEFBUFATTR,
    CMD_ID_AO_SND_GETDEBUGPARAM,

    CMD_ID_AO_SND_SETADOUTPUTENABLE,
    CMD_ID_AO_SND_GETADOUTPUTENABLE,

    CMD_ID_AO_SND_DUPLICATETRACK,

    CMD_ID_AO_SND_SETALLCASTMUTE,
    CMD_ID_AO_SND_GETALLCASTMUTE,

    CMD_ID_AO_SND_TRACKCONFIGINIT,
#endif

    CMD_ID_AO_SND_GETXRUNCOUNT,

    CMD_ID_AO_SND_SETSOUNDDELAY,
    CMD_ID_AO_SND_GETSOUNDDELAY,

    CMD_ID_AO_SND_SETLOWLATENCY,
    CMD_ID_AO_SND_GETLOWLATENCY,

    CMD_ID_AO_SND_SETEXTDELAYMS,

    CMD_ID_AO_SND_DMACREATE,
    CMD_ID_AO_SND_DMADESTORY,
    CMD_ID_AO_SND_DMASETSAMPLERATE,

    /* AO Track ioctl */
    CMD_ID_AO_TRACK_GETDEFATTR,
    CMD_ID_AO_TRACK_CREATE,
    CMD_ID_AO_TRACK_DESTROY,

    CMD_ID_AO_TRACK_START,
    CMD_ID_AO_TRACK_STOP,
    CMD_ID_AO_TRACK_PAUSE,
    CMD_ID_AO_TRACK_FLUSH,

    CMD_ID_AO_TRACK_SENDDATA,
    CMD_ID_AO_TRACK_SETWEITHT,
    CMD_ID_AO_TRACK_GETWEITHT,
    CMD_ID_AO_TRACK_SETSPEEDADJUST,
    CMD_ID_AO_TRACK_GETDELAYMS,
    CMD_ID_AO_TRACK_ISBUFEMPTY,
    CMD_ID_AO_TRACK_SETEOSFLAG,

    CMD_ID_AO_TRACK_GETATTR,
    CMD_ID_AO_TRACK_SETATTR,

    CMD_ID_AO_TRACK_ATTACHAI,
    CMD_ID_AO_TRACK_DETACHAI,

    CMD_ID_AO_TRACK_SETABSGAIN,
    CMD_ID_AO_TRACK_GETABSGAIN,

    CMD_ID_AO_TRACK_SETMUTE,
    CMD_ID_AO_TRACK_GETMUTE,
    CMD_ID_AO_TRACK_SETCHANNELMODE,
    CMD_ID_AO_TRACK_GETCHANNELMODE,

#ifdef __DPT__
    CMD_ID_AO_TRACK_SETPRESCALE,
    CMD_ID_AO_TRACK_GETPRESCALE,

    CMD_ID_AO_TRACK_SETSOURCE,
#endif

    /* AO Cast ioctl */
    CMD_ID_AO_TRACK_SETFIFOBYPASS,
    CMD_ID_AO_TRACK_MMAP,
    CMD_ID_AO_TRACK_SETPRIORITY,
    CMD_ID_AO_TRACK_GETPRIORITY,

    CMD_ID_AO_CAST_GETDEFATTR,
    CMD_ID_AO_CAST_CREATE,
    CMD_ID_AO_CAST_DESTROY,
    CMD_ID_AO_CAST_SETENABLE,
    CMD_ID_AO_CAST_GETENABLE,
    CMD_ID_AO_CAST_GETINFO,
    CMD_ID_AO_CAST_SETINFO,

    CMD_ID_AO_CAST_ACQUIREFRAME,
    CMD_ID_AO_CAST_RELEASEFRAME,

    CMD_ID_AO_CAST_SETABSGAIN,
    CMD_ID_AO_CAST_GETABSGAIN,

    CMD_ID_AO_CAST_SETMUTE,
    CMD_ID_AO_CAST_GETMUTE,

    CMD_ID_AO_BUTT,
};

/********************************************************
AO command code definition
*********************************************************/
/* AO SND CMD */
#define CMD_AO_GETSNDDEFOPENATTR                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETDEFOPENATTR, AO_SND_OpenDefault_Param_S)
#define CMD_AO_SND_OPEN                            _IOWR (HI_ID_AO, CMD_ID_AO_SND_OPEN, AO_SND_Open_Param_S)
#define CMD_AO_SND_CLOSE                           _IOW  (HI_ID_AO, CMD_ID_AO_SND_CLOSE, HI_UNF_SND_E)
#define CMD_AO_SND_SETMUTE                         _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETMUTE, AO_SND_Mute_Param_S)
#define CMD_AO_SND_GETMUTE                         _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETMUTE, AO_SND_Mute_Param_S)
#define CMD_AO_SND_SETVOLUME                       _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETVOLUME, AO_SND_Volume_Param_S)
#define CMD_AO_SND_GETVOLUME                       _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETVOLUME, AO_SND_Volume_Param_S)

#define CMD_AO_SND_SETHDMIMODE                     _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETHDMIMODE, AO_SND_HdmiMode_Param_S)
#define CMD_AO_SND_GETHDMIMODE                     _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETHDMIMODE, AO_SND_HdmiMode_Param_S)
#define CMD_AO_SND_SETSPDIFMODE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSPDIFMODE, AO_SND_SpdifMode_Param_S)
#define CMD_AO_SND_GETSPDIFMODE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSPDIFMODE, AO_SND_SpdifMode_Param_S)

#define CMD_AO_SND_SETSAMPLERATE                   _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSAMPLERATE, AO_SND_SampleRate_Param_S)
#define CMD_AO_SND_GETSAMPLERATE                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSAMPLERATE, AO_SND_SampleRate_Param_S)
#define CMD_AO_SND_SETTRACKMODE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETTRACKMODE, AO_SND_TrackMode_Param_S)
#define CMD_AO_SND_GETTRACKMODE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETTRACKMODE, AO_SND_TrackMode_Param_S)

#define CMD_AO_SND_SETSMARTVOLUME                  _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSMARTVOLUME, AO_SND_SmartVolume_Param_S)
#define CMD_AO_SND_GETSMARTVOLUME                  _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSMARTVOLUME, AO_SND_SmartVolume_Param_S)

#define CMD_AO_SND_SETSPDIFSCMSMODE                _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSPDIFSCMSMODE, AO_SND_SpdifSCMSMode_Param_S)
#define CMD_AO_SND_GETSPDIFSCMSMODE                _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSPDIFSCMSMODE, AO_SND_SpdifSCMSMode_Param_S)
#define CMD_AO_SND_SETSPDIFCATEGORYCODE            _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSPDIFCATEGORYCODE, AO_SND_SpdifCategoryCode_Param_S)
#define CMD_AO_SND_GETSPDIFCATEGORYCODE            _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSPDIFCATEGORYCODE, AO_SND_SpdifCategoryCode_Param_S)

#define CMD_AO_SND_SETALLTRACKMUTE                 _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETALLTRACKMUTE, AO_SND_AllTrackMute_Param_S)
#define CMD_AO_SND_GETALLTRACKMUTE                 _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETALLTRACKMUTE, AO_SND_AllTrackMute_Param_S)

#define CMD_AO_SND_SETADACENABLE                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_SETADACENABLE, AO_SND_Adac_Enable_Param_S)
#define CMD_AO_SND_GETADACENABLE                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETADACENABLE, AO_SND_Adac_Enable_Param_S)

#define CMD_AO_SND_ATTACHTRACK                     _IOW  (HI_ID_AO, CMD_ID_AO_SND_ATTACHTRACK, HI_HANDLE)
#define CMD_AO_SND_DETACHTRACK                     _IOW  (HI_ID_AO, CMD_ID_AO_SND_DETACHTRACK, HI_HANDLE)

#define CMD_AO_SND_SETPRECIVOL                     _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETPRECIVOL, AO_SND_PreciVolume_Param_S)
#define CMD_AO_SND_GETPRECIVOL                     _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETPRECIVOL, AO_SND_PreciVolume_Param_S)

#define CMD_AO_SND_SETALSAPRESCALE                 _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETALSAPRESCALE, AO_SND_Set_Alsa_Prescale_S)

#define CMD_AO_SND_SETBALANCE                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETBALANCE, AO_SND_Balance_Param_S)
#define CMD_AO_SND_GETBALANCE                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETBALANCE, AO_SND_Balance_Param_S)

#ifdef __DPT__
/* ARC */
#define CMD_AO_SND_SETARCENABLE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETARCENABLE, AO_SND_ARC_ENABLE_Param_S)
#define CMD_AO_SND_GETARCENABLE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETARCENABLE, AO_SND_ARC_ENABLE_Param_S)
#define CMD_AO_SND_SETARCMODE                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETARCMODE, AO_SND_ARC_MODE_Param_S)
#define CMD_AO_SND_GETARCMODE                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETARCMODE, AO_SND_ARC_MODE_Param_S)
#define CMD_AO_SND_SETARCCAP                       _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETARCCAP, AO_SND_ARC_CAP_Param_S)
#define CMD_AO_SND_GETARCCAP                       _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETARCCAP, AO_SND_ARC_CAP_Param_S)
#endif

#define CMD_AO_SND_SETAVCATTR                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETAVCATTR, AO_SND_Avc_Param_S)
#define CMD_AO_SND_GETAVCATTR                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETAVCATTR, AO_SND_Avc_Param_S)
#define CMD_AO_SND_SETAVCENABLE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETAVCENABLE, AO_SND_Avc_Enable_S)
#define CMD_AO_SND_GETAVCENABLE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETAVCENABLE, AO_SND_Avc_Enable_S)

#ifdef __DPT__
#define CMD_AO_SND_SETGEQATTR                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETGEQATTR, AO_SND_Geq_Param_S)
#define CMD_AO_SND_GETGEQATTR                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETGEQATTR, AO_SND_Geq_Param_S)
#define CMD_AO_SND_SETGEQENABLE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETGEQENABLE, AO_SND_Eq_Enable_S)
#define CMD_AO_SND_GETGEQENABLE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETGEQENABLE, AO_SND_Eq_Enable_S)
#define CMD_AO_SND_SETGEQGAIN                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETGEQGAIN, AO_SND_Geq_Gain_S)
#define CMD_AO_SND_GETGEQGAIN                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETGEQGAIN, AO_SND_Geq_Gain_S)
#endif

#define CMD_AO_SND_SETDRCENABLE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETDRCENABLE, AO_SND_Drc_Enable_S)
#define CMD_AO_SND_GETDRCENABLE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETDRCENABLE, AO_SND_Drc_Enable_S)
#define CMD_AO_SND_SETDRCATTR                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETDRCATTR, AO_SND_Drc_Param_S)
#define CMD_AO_SND_GETDRCATTR                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETDRCATTR, AO_SND_Drc_Param_S)

#define CMD_AO_SND_SETPEQATTR                      _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETPEQATTR, AO_SND_Peq_Param_S)
#define CMD_AO_SND_GETPEQATTR                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETPEQATTR, AO_SND_Peq_Param_S)
#define CMD_AO_SND_SETPEQENABLE                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETPEQENABLE, AO_SND_Eq_Enable_S)
#define CMD_AO_SND_GETPEQENABLE                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETPEQENABLE, AO_SND_Eq_Enable_S)

#ifdef __DPT__
#define CMD_AO_SND_ATTACHAEF                       _IOWR (HI_ID_AO, CMD_ID_AO_SND_ATTACHAEF, AO_SND_AttAef_Param_S)
#define CMD_AO_SND_DETACHAEF                       _IOW  (HI_ID_AO, CMD_ID_AO_SND_DETACHAEF, AO_SND_AttAef_Param_S)
#define CMD_AO_SND_SETAEFBYPASS                    _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETAEFBYPASS, AO_SND_AefBypass_Param_S)
#define CMD_AO_SND_GETAEFBYPASS                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETAEFBYPASS, AO_SND_AefBypass_Param_S)

#define CMD_AO_SND_GETTRACKINFO                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETTRACKINFO, AO_SND_TrackInfo_Param_S)
#define CMD_AO_SND_GETAEFBUFATTR                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETAEFBUFATTR, AO_SND_Aef_Buf_Param_S)
/* Debug */
#define CMD_AO_SND_GETDEBUGPARAM                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETDEBUGPARAM, AO_SND_DEBUG_Param_S)

#define CMD_AO_SND_SETADOUTPUTENABLE               _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETADOUTPUTENABLE, AO_SND_ADOutput_Enable_S)
#define CMD_AO_SND_GETADOUTPUTENABLE               _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETADOUTPUTENABLE, AO_SND_ADOutput_Enable_S)

#define CMD_AO_SND_DUPLICATETRACK                  _IOWR (HI_ID_AO, CMD_ID_AO_SND_DUPLICATETRACK, AO_SND_TrackDuplicate_Param_S)

#define CMD_AO_SND_SETALLCASTMUTE                  _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETALLCASTMUTE, AO_SND_AllCastMute_Param_S)
#define CMD_AO_SND_GETALLCASTMUTE                  _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETALLCASTMUTE, AO_SND_AllCastMute_Param_S)

#define CMD_AO_SND_TRACKCONFIGINIT                 _IOW  (HI_ID_AO, CMD_ID_AO_SND_TRACKCONFIGINIT, AO_SND_TrackConfig_Param_S)
#endif

#define CMD_AO_SND_GETXRUNCOUNT                    _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETXRUNCOUNT, AO_SND_Get_Xrun_Param_S)

#define CMD_AO_SND_SETSOUNDDELAY                   _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETSOUNDDELAY, AO_SND_OpDelay_Param_S)
#define CMD_AO_SND_GETSOUNDDELAY                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETSOUNDDELAY, AO_SND_OpDelay_Param_S)

#define CMD_AO_SND_SETLOWLATENCY                   _IOW  (HI_ID_AO, CMD_ID_AO_SND_SETLOWLATENCY, AO_SND_Set_LowLatency_Param_S)
#define CMD_AO_SND_GETLOWLATENCY                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_GETLOWLATENCY, AO_SND_Set_LowLatency_Param_S)

#define CMD_AO_SND_SETEXTDELAYMS                   _IOWR (HI_ID_AO, CMD_ID_AO_SND_SETEXTDELAYMS, AO_SND_Set_ExtDelayMs_Param_S)
#define CMD_AO_SND_DMACREATE                       _IOWR (HI_ID_AO, CMD_ID_AO_SND_DMACREATE, AO_SND_DMACreate_Param_S)
#define CMD_AO_SND_DMADESTORY                      _IOWR (HI_ID_AO, CMD_ID_AO_SND_DMADESTORY, AO_SND_DMADestory_Param_S)
#define CMD_AO_SND_DMASETSAMPLERATE                _IOWR (HI_ID_AO, CMD_ID_AO_SND_DMASETSAMPLERATE, AO_SND_DMASetSampleRate_Param_S)

/* AO Track CMD */
#define CMD_AO_TRACK_GETDEFATTR                    _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETDEFATTR, HI_UNF_AUDIOTRACK_ATTR_S)
#define CMD_AO_TRACK_CREATE                        _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_CREATE, AO_Track_Create_Param_S)
#define CMD_AO_TRACK_DESTROY                       _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_DESTROY, HI_HANDLE)

#define CMD_AO_TRACK_START                         _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_START, HI_HANDLE)
#define CMD_AO_TRACK_STOP                          _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_STOP, HI_HANDLE)
#define CMD_AO_TRACK_PAUSE                         _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_PAUSE, HI_HANDLE)
#define CMD_AO_TRACK_FLUSH                         _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_FLUSH, HI_HANDLE)

#define CMD_AO_TRACK_SENDDATA                      _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SENDDATA, AO_Track_SendData_Param_S)
#define CMD_AO_TRACK_SETWEITHT                     _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETWEITHT, AO_Track_Weight_Param_S)
#define CMD_AO_TRACK_GETWEITHT                     _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETWEITHT, AO_Track_Weight_Param_S)
#define CMD_AO_TRACK_SETSPEEDADJUST                _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETSPEEDADJUST, AO_Track_SpeedAdjust_Param_S)
#define CMD_AO_TRACK_GETDELAYMS                    _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETDELAYMS, AO_Track_DelayMs_Param_S)
#define CMD_AO_TRACK_ISBUFEMPTY                    _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_ISBUFEMPTY, AO_Track_BufEmpty_Param_S)
#define CMD_AO_TRACK_SETEOSFLAG                    _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETEOSFLAG, AO_Track_EosFlag_Param_S)
#define CMD_AO_TRACK_GETATTR                       _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETATTR, AO_Track_Attr_Param_S)
#define CMD_AO_TRACK_SETATTR                       _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETATTR, AO_Track_Attr_Param_S)

#define CMD_AO_TRACK_ATTACHAI                      _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_ATTACHAI, AO_Track_AttAi_Param_S)
#define CMD_AO_TRACK_DETACHAI                      _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_DETACHAI, AO_Track_AttAi_Param_S)
#define CMD_AO_TRACK_SETABSGAIN                    _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETABSGAIN, AO_Track_AbsGain_Param_S)
#define CMD_AO_TRACK_GETABSGAIN                    _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETABSGAIN, AO_Track_AbsGain_Param_S)

#define CMD_AO_TRACK_SETMUTE                       _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETMUTE, AO_Track_Mute_Param_S)
#define CMD_AO_TRACK_GETMUTE                       _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETMUTE, AO_Track_Mute_Param_S)
#define CMD_AO_TRACK_SETCHANNELMODE                _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETCHANNELMODE, AO_Track_ChannelMode_Param_S)
#define CMD_AO_TRACK_GETCHANNELMODE                _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETCHANNELMODE, AO_Track_ChannelMode_Param_S)

#ifdef __DPT__
#define CMD_AO_TRACK_SETPRESCALE                   _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETPRESCALE, AO_Track_Prescale_Param_S)
#define CMD_AO_TRACK_GETPRESCALE                   _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETPRESCALE, AO_Track_Prescale_Param_S)

#define CMD_AO_TRACK_SETSOURCE                     _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETSOURCE, AO_Track_Source_Param_S)
#endif

/*karaoke */
#define CMD_AO_TRACK_SETFIFOBYPASS                 _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETFIFOBYPASS, AO_Track_FifoBypass_Param_S)
#define CMD_AO_TRACK_MMAP                          _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_MMAP, AO_Track_Mmap_Param_S)
#define CMD_AO_TRACK_SETPRIORITY                   _IOW  (HI_ID_AO, CMD_ID_AO_TRACK_SETPRIORITY, AO_Track_Priority_Param_S)
#define CMD_AO_TRACK_GETPRIORITY                   _IOWR (HI_ID_AO, CMD_ID_AO_TRACK_GETPRIORITY, AO_Track_Priority_Param_S)

/* AO Cast CMD */
#define CMD_AO_CAST_GETDEFATTR                     _IOWR (HI_ID_AO, CMD_ID_AO_CAST_GETDEFATTR, HI_UNF_SND_CAST_ATTR_S)
#define CMD_AO_CAST_CREATE                         _IOWR (HI_ID_AO, CMD_ID_AO_CAST_CREATE, AO_Cast_Create_Param_S)
#define CMD_AO_CAST_DESTROY                        _IOW  (HI_ID_AO, CMD_ID_AO_CAST_DESTROY, HI_HANDLE)
#define CMD_AO_CAST_SETENABLE                      _IOW  (HI_ID_AO, CMD_ID_AO_CAST_SETENABLE, AO_Cast_Enable_Param_S)
#define CMD_AO_CAST_GETENABLE                      _IOWR (HI_ID_AO, CMD_ID_AO_CAST_GETENABLE, AO_Cast_Enable_Param_S)
#define CMD_AO_CAST_GETINFO                        _IOWR (HI_ID_AO, CMD_ID_AO_CAST_GETINFO, AO_Cast_Info_Param_S)
#define CMD_AO_CAST_SETINFO                        _IOW  (HI_ID_AO, CMD_ID_AO_CAST_SETINFO, AO_Cast_Info_Param_S)
#define CMD_AO_CAST_ACQUIREFRAME                   _IOWR (HI_ID_AO, CMD_ID_AO_CAST_ACQUIREFRAME, AO_Cast_Data_Param_S)
#define CMD_AO_CAST_RELEASEFRAME                   _IOW  (HI_ID_AO, CMD_ID_AO_CAST_RELEASEFRAME, AO_Cast_Data_Param_S)
#define CMD_AO_CAST_SETABSGAIN                     _IOW  (HI_ID_AO, CMD_ID_AO_CAST_SETABSGAIN, AO_Cast_AbsGain_Param_S)
#define CMD_AO_CAST_GETABSGAIN                     _IOWR (HI_ID_AO, CMD_ID_AO_CAST_GETABSGAIN, AO_Cast_AbsGain_Param_S)
#define CMD_AO_CAST_SETMUTE                        _IOW  (HI_ID_AO, CMD_ID_AO_CAST_SETMUTE, AO_Cast_Mute_Param_S)
#define CMD_AO_CAST_GETMUTE                        _IOWR (HI_ID_AO, CMD_ID_AO_CAST_GETMUTE, AO_Cast_Mute_Param_S)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
