/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : engine_codec_private.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/

#ifndef  __ENGINE_CODEC_PRIVATE_H__
#define  __ENGINE_CODEC_PRIVATE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum CONFIG_TYPE_E
{
    CONFIG_VOLUME     = 0x00001000,
    CONFIG_SETEOSFLAG = 0x00001001,
    CONFIG_GETSYSTEMTRACKALONEFLAG = 0x00001002,
    CONFIG_SETMEDIAVOLUMEATTENUATION = 0x00001003,
    CONFIG_SETCONTINUOUSOUTPUTSTATUS = 0x00001004,
    CONFIG_BUTT,
} CONFIG_TYPE_E;

typedef struct _VOLUME_CONFIG_S
{
    MS12_VOLUME_CURVE_E enVolumeCurve;
    HI_S32 s32VolumedB;
    HI_U32 u32FadeMs;
} VOLUME_CONFIG_S;

typedef struct _SETEOSFLAG_CONFIG_S
{
    HI_BOOL bEosFlag;
} SETEOSFLAG_CONFIG_S;

typedef struct _GETSYSTRACKALONEFLAG_CONFIG_S
{
    HI_BOOL bAlone;
} GETSYSTRACKALONE_CONFIG_S;

typedef struct _SETMEDIAVOLUMEATTENUATION_CONFIG_S
{
    HI_BOOL bAttenuate;
} SETMEDIAVOLUMEATTENUATION_CONFIG_S;

typedef struct _SETCONTINUOUSOUTPUT_CONFIG_S
{
    HI_BOOL bEnable;
} SETCONTINUOUSOUTPUT_CONFIG_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
