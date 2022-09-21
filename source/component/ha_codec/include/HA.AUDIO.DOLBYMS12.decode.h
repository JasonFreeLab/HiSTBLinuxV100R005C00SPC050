/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : HA.AUDIO.DOLBYMS12.decode.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HA_AUDIO_DOLBYMS12_DECODE_H__
#define __HA_AUDIO_DOLBYMS12_DECODE_H__

#include "hi_type.h"
#include "hi_audio_codec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define  HA_MS12_ID         (0x2050)

#define  HA_CODEC_MS12_SET_VOLUME_CMD             ((((HI_U32)HA_MS12_ID) << 16) | 0x1000)
#define  HA_CODEC_MS12_GET_VOLUME_CMD             ((((HI_U32)HA_MS12_ID) << 16) | 0x1001)
#define  HA_CODEC_MS12_SET_DRC_MODE_CMD           ((((HI_U32)HA_MS12_ID) << 16) | 0x1002)
#define  HA_CODEC_MS12_SET_LFE_MODE_CMD           ((((HI_U32)HA_MS12_ID) << 16) | 0x1003)
#define  HA_CODEC_MS12_SET_DMX_MODE_CMD           ((((HI_U32)HA_MS12_ID) << 16) | 0x1004)
#define  HA_CODEC_MS12_SET_DYNSCALE_MODE_CMD      ((((HI_U32)HA_MS12_ID) << 16) | 0x1005)
#define  HA_CODEC_MS12_SET_AD_BALANCE_CMD         ((((HI_U32)HA_MS12_ID) << 16) | 0x1006)
#define  HA_CODEC_MS12_SET_PASSTHROUGH_STATUS_CMD ((((HI_U32)HA_MS12_ID) << 16) | 0x1007)
#define  HA_CODEC_MS12_SET_MIN_VOLUME_CMD         ((((HI_U32)HA_MS12_ID) << 16) | 0x1008)
#define  HA_CODEC_MS12_SET_PTS_MUTE_CMD           ((((HI_U32)HA_MS12_ID) << 16) | 0x1009)

/** Define DAP configuration:
    - 0: No DAP (default)
    - 1: Content processing only;
    - 2: Device processing only
    - 3: Both with two DAP instances
    - 4: Both with single instance DAP processing */
typedef enum
{
    MS12_DAP_NO_PROC = 0,
    MS12_DAP_CONTENT_PROC,
    MS12_DAP_DEVICE_PROC,
    MS12_DAP_DEVICE_CONTENT_PROC,
    MS12_DAP_SI_PROC,
} MS12_DAP_MODE_E;

/** Define input stream type:
    - 0: Dolby digital (plus) stream (default)
    - 1: AAC or HEAAC stream
    - 2: AC4 stream
    - 3: PCM stream */
typedef enum
{
    MS12_DOLBY_DIGITAL_PLUS = 0,
    MS12_HEAAC,
    MS12_AC4,
    MS12_EXTERNAL_PCM,
} MS12_INPUT_TYPE_E;

/** Define volume curve type:
    - 0: Linear curve, up:g(x)=x, down:f(x)=1-x (default)
    - 1: In cube curve, up:g(x)=x^3, down:f(x)=1-x^3
    - 2: Out cube curve, up:g(x)=1-(1-x)^3, down:f(x)=(1-x)^3 */
typedef enum
{
    MS12_VOLCURVE_LINEAR = 0,
    MS12_VOLCURVE_INCUBE,
    MS12_VOLCURVE_OUTCUBE,
} MS12_VOLUME_CURVE_E;

/** Define stereo down mix mode:
    - 0: 2/0 Dolby Surround compatible (Lt/Rt) (default)
    - 1: 2/0 Stereo without surround
    - 2: Only HEAAC and AC4 stream are vaild */
typedef enum
{
    MS12_DMX_LTRT = 0,
    MS12_DMX_LORO,
    MS12_DMX_ARIB,
} MS12_STEREODMX_MODE_E;

/** Define decoder compression mode:
    - 0: Line out mode, used in DMA
    - 1: RF out mode, used in broadcast or iptv (default) */
typedef enum
{
    MS12_DRC_LINE = 0,
    MS12_DRC_RF,
} MS12_DRC_MODE_E;

/** Define LFE Downmixing mode
    - 0: The LFE channel not included in the pcm output (default)
    - 1: The LFE channel included in the output PCM data */
typedef enum
{
    MS12_LFEOUT_OFF = 0,
    MS12_LFEOUT_ON,
} MS12_LFEOUT_MODE_E;

/** Define Setting and getting volume parameter
    - enCmd: HA_CODEC_MS12_SET_VOLUME_CMD or HA_CODEC_MS12_GET_VOLUME_CMD
    - s32VolumedB: -96 ~ 0 (dB)
    - u32FadeMs: Fade time:0 ~ 60000 (ms) */
typedef struct
{
    HI_U32 enCmd;
    MS12_VOLUME_CURVE_E enVolumeCurve;
    HI_S32 s32VolumedB;
    HI_U32 u32FadeMs;
} HA_MS12_VOLUME_S;

/** Define Setting parameter of drc mode
    - enCmd: HA_CODEC_MS12_SET_DRC_MODE_CMD */
typedef struct
{
    HI_U32  enCmd;
    MS12_DRC_MODE_E enDrcMode;
} HA_MS12_SET_DRC_MODE_S;

/** Define Setting parameter of lfe mode
    - enCmd: HA_CODEC_MS12_SET_LFE_MODE_CMD */
typedef struct
{
    HI_U32 enCmd;
    MS12_LFEOUT_MODE_E enLfeMode;
} HA_MS12_SET_LFE_MODE_S;

/** Define Setting parameter of downmix mode
    - enCmd: HA_CODEC_SET_DMX_MODE_CMD */
typedef struct
{
    HI_U32 enCmd;
    MS12_STEREODMX_MODE_E enDmxMode;
} HA_MS12_SET_DMX_MODE_S;

/** Define Setting parameter of dynamic scale mode
    -enCmd:       HA_CODEC_MS12_SET_DYNSCALE_MODE_CMD
    -u32DrcCut:   Scale factor for incoming DRC cut value: 0 ~ 100
    -u32DrcBoost: Scale factor for incoming DRC boost value: 0 ~ 100 */
typedef struct
{
    HI_U32 enCmd;
    HI_U16 u32DrcCut;
    HI_U16 u32DrcBoost;
} HA_MS12_SET_DYNSCALE_MODE_S;

/** Define Setting parameter of ad balance
    -enCmd:      HA_CODEC_MS12_SET_AD_BALANCE_CMD
    -s32Balance: User defined balance between main and associated signal
                 Value range is between -32 and +32 (in dB)
                 -32dB indicates main only (mute associated)
                 +32dB indicates associated only (mute main) */
typedef struct
{
    HI_U32 enCmd;
    HI_S32 s32Balance;
} HA_MS12_SET_AD_BALANCE_S;

/** Define Setting parameter of pts mute
    -enCmd:       HA_CODEC_MS12_SET_PTS_MUTE_CMD
    -u32StartPts: Start mute pts
    -u32StopPts:  Stop mute pts */
typedef struct
{
    HI_U32 enCmd;
    HI_U32 u32StartPts;
    HI_U32 u32StopPts;
} HA_MS12_SET_PTS_MUTE_S;

/** Define opening parameter of MS12 decoder
    -u32DrcCut:   Determines the percentage of application of DRC
                  attenuation factors for the 2 channel output.0 ~ 100 default: 100
    -u32DrcBoost: Determines the percentage of application of DRC
                  boost factors for the 2 channel output. 0 ~ 100 default: 100
    -s32Balance:  User defined balance between main and associated signal
                  Value range is between -32 and +32 (in dB)
                  -32dB indicates main only (mute associated)
                  +32dB indicates associated only (mute main) */
typedef struct
{
    MS12_INPUT_TYPE_E       enInputType;
    MS12_DAP_MODE_E         enDapMode;
    MS12_LFEOUT_MODE_E      enLfeOutMode;
    MS12_STEREODMX_MODE_E   enDmxMode;
    MS12_DRC_MODE_E         enDrcMode;
    HI_U32                  u32DrcCut;
    HI_U32                  u32DrcBoost;
    HI_S32                  s32AdBalance;
} DOLBYMS12_CODEC_OPENCONFIG_S;

#define HA_DOLBYMS12_CodecGetDefaultOpenConfig(pConfigParam) \
    do { \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->enInputType   = MS12_DOLBY_DIGITAL_PLUS; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->enDapMode     = MS12_DAP_NO_PROC; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->enLfeOutMode  = MS12_LFEOUT_OFF; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->enDmxMode     = MS12_DMX_LTRT; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->enDrcMode     = MS12_DRC_RF; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->u32DrcCut     = 100; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->u32DrcBoost   = 100; \
        ((DOLBYMS12_CODEC_OPENCONFIG_S *)(pConfigParam))->s32AdBalance  = 0; \
    } while (0)

#define HA_DOLBYMS12_CodecGetDefaultOpenParam(pOpenParam, pstPrivateParams) \
    do { HI_U32 i; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->enDecMode = HD_DEC_MODE_SIMUL; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredOutChannels = 2; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.bInterleaved    = HI_TRUE; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32BitPerSample = 16; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredSampleRate  = 48000; \
        for (i = 0; i < HA_AUDIO_MAXCHANNELS; i++) \
        { \
            ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.enChannelMapping[i] = HA_AUDIO_ChannelNone; \
        } \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = (HI_VOID*)pstPrivateParams; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = sizeof(DOLBYMS12_CODEC_OPENCONFIG_S); \
    } while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HA_AUDIO_DOLBYMS12_DECODE_H__ */
