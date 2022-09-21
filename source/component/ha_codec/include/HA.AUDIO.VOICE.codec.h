/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : HA.AUDIO.G726.codec.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HI_AUDIO_VOICE_CODEC_H__
#define __HI_AUDIO_VOICE_CODEC_H__

#include "hi_type.h"
#include "hi_audio_codec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef enum
{
    HA_VOICE_G711_A      = 0x01,  /**<64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */ /**<CNcomment: G711 A格式*/
    HA_VOICE_G711_U      = 0x02,  /**<64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */ /**<CNcomment: G711 U格式*/
    HA_VOICE_ADPCM_DVI4  = 0x03,  /**<32kbps ADPCM(DVI4) for RTP; see DVI4 diiffers in three respects from the IMA ADPCM at RFC3551.txt 4.5.1 DVI4 */
                                                /**<CNcomment: RTP ADPCM DVI4格式*/
    HA_VOICE_G726_16KBPS = 0x04,  /**<16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */ /**<CNcomment: G726 16kbps格式*/
    HA_VOICE_G726_24KBPS = 0x05,  /**<24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */ /**<CNcomment: G726 24kbps格式*/
    HA_VOICE_G726_32KBPS = 0x06,  /**<32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */ /**<CNcomment: G726 32kbps格式*/
    HA_VOICE_G726_40KBPS = 0x07,  /**<40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */ /**<CNcomment: G726 40kbps格式*/

    HA_VOICE_ADPCM_IMA   = 0x23,  /**<32kbps ADPCM(IMA) */ /**<CNcomment: 32kbps ADPCM IMA格式*/

    /**
    An example of the packing scheme for G726-32 codewords is as shown, and bit A3 is the least significant bit of the first codeword:
    RTP G726-32:
    0                   1
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
    |B B B B|A A A A|D D D D|C C C C| ...
    |0 1 2 3|0 1 2 3|0 1 2 3|0 1 2 3|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

    MEDIA G726-32:
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
    |A A A A|B B B B|C C C C|D D D D| ...
    |3 2 1 0|3 2 1 0|3 2 1 0|3 2 1 0|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
    */
    HA_VOICE_MEDIA_G726_16KBPS = 0x24,  /**<media G726 16kbps for ASF ... */ /**<CNcomment: 媒体G726 16kbps格式*/
    HA_VOICE_MEDIA_G726_24KBPS = 0x25,  /**<media G726 24kbps for ASF ... */ /**<CNcomment: 媒体G726 24kbps格式*/
    HA_VOICE_MEDIA_G726_32KBPS = 0x26,  /**<media G726 32kbps for ASF ... */ /**<CNcomment: 媒体G726 32kbps格式*/
    HA_VOICE_MEDIA_G726_40KBPS = 0x27,  /**<media G726 40kbps for ASF ... */ /**<CNcomment: 媒体G726 40kbps格式*/

    /* ORIGINE VERSION CODEC */
    HA_VOICE_G711_ORG_A        = 0x41,  /**<original version 64kbps G.711 A */ /**<CNcomment: 原始G711 A格式*/
    HA_VOICE_G711_ORG_U        = 0x42,  /**<original version 64kbps G.711 U */ /**<CNcomment: 原始G711 U格式*/
    HA_VOICE_ADPCM_ORG_DVI4    = 0x43,  /**<original version 32kbps ADPCM */ /**<CNcomment: 原始ADPCM DVI4格式*/
    HA_VOICE_G726_ORG_16KBPS   = 0x44,  /**<original version(DVS1.0) 16kbps G.726 */ /**<CNcomment: 原始G726 16kbps格式*/
} HA_VOICE_FORMAT_E;

typedef struct
{
    HA_VOICE_FORMAT_E  enVoiceFormat;
    HI_U32             u32SamplePerFrame;
} HA_VOICE_OPENCONFIG_S;

#define HA_VOICE_EncGetDefalutOpenConfig(pConfigParam) \
    do { \
        ((HA_VOICE_OPENCONFIG_S *)(pConfigParam))->enVoiceFormat = HA_VOICE_G711_A; \
        ((HA_VOICE_OPENCONFIG_S *)(pConfigParam))->u32SamplePerFrame = 320; \
    } while (0)

#define HA_VOICE_GetEncDefaultOpenParam(pOpenParam, pstPrivateParams) \
do{ ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->u32DesiredOutChannels = 1; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->bInterleaved = HI_TRUE; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->s32BitPerSample = 16; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->u32DesiredSampleRate = 8000; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->u32SamplePerFrame = 160; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = (HI_VOID*)pstPrivateParams; \
    ((HI_HAENCODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = sizeof(HA_VOICE_OPENCONFIG_S); \
} while(0)

#define HA_VOICE_DecGetDefalutOpenConfig(pConfigParam) \
    do { \
        ((HA_VOICE_OPENCONFIG_S *)(pConfigParam))->enVoiceFormat = HA_VOICE_G711_A; \
        ((HA_VOICE_OPENCONFIG_S *)(pConfigParam))->u32SamplePerFrame = 320; \
    } while (0)

#define HA_VOICE_GetDecDefalutOpenParam(pOpenParam, pstPrivateParams) \
do{ HI_S32 i; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->enDecMode = HD_DEC_MODE_RAWPCM; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredOutChannels = 1; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.bInterleaved  = HI_TRUE; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32BitPerSample = 16; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredSampleRate = 8000; \
    for (i = 0; i < HA_AUDIO_MAXCHANNELS; i++) \
    { \
        ((HI_HADECODE_OPENPARAM_S *)pOpenParam)->sPcmformat.enChannelMapping[i] = HA_AUDIO_ChannelNone; \
    } \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = (HI_VOID*)pstPrivateParams; \
    ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = sizeof(HA_VOICE_OPENCONFIG_S); \
} while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_AUDIO_VOICE_CODEC_H__ */
