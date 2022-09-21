/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_FFMPEG_Adec.c
Author:  Audio
Date:    2015

=================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "unistd.h"

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Core.h>
#include <OMX_Index.h>
#include <OMX_IndexExt.h>
#include <OMX_Audio.h>
#include <OMX_AudioExt.h>
#include <OMX_Other.h>

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_StubbedComponent.h"
#include "ha_adec.h"
#include "omx_audio_base.h"
#include "omx_audio_common.h"
#include "HA.AUDIO.FFMPEG_DECODE.decode.h"
#include "OMX_Audio_Hisi.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_FFMPEG"
#endif


/* defination related to FFMPEG decoder */
#define AUDIO_DEC_FFMPEG_ROLE     "audio_decoder.ffmpeg"
#define HA_FFMPEG_LIB_NAME        "libHA.AUDIO.FFMPEG_ADEC.decode.so"


/**HA FFMPEG CODECID definition: equal the definition in "hidolphin\external\ffmpeg_dev\ffmpeg\libavcodec\Avcodec.h"*/
/**CNcomment:HA FFMPEG CODECID ¶¨Òå*/
typedef enum
{
    OMX_CODEC_ID_PCM_S16LE = 0x10000,
    OMX_CODEC_ID_FLAC      = 0x1500d,
} HAOMX_FFMPEG_CODECID;

typedef struct
{
    HA_FFMPEG_DECODE_OPENCONFIG_S  sFFmpegConfig;
    HI_U32  IndexAudioParam;  //indicate which format ffmpeg to decode
} HA_FFMPEG_PRIVDATA;


/*
 *  Functions
 */
static OMX_ERRORTYPE OMXFFMPEGInitDecoder(HI_AUDDATATYPE* pHAData)
{
    HI_S32 s32Ret;
    HI_U32 IndexAudioParam = -1;
    HA_FFMPEG_DECODE_OPENCONFIG_S* pstFFmpegConfig;

    pstFFmpegConfig = &((HA_FFMPEG_PRIVDATA*)(pHAData->pCodecPrivData))->sFFmpegConfig;
    HA_FFMPEG_DecGetDefalutOpenConfig(pstFFmpegConfig);

    IndexAudioParam = ((HA_FFMPEG_PRIVDATA*)(pHAData->pCodecPrivData))->IndexAudioParam;

    switch (IndexAudioParam)
    {
        case OMX_IndexParamAudioFlac:
            pstFFmpegConfig->stFfmpeg_AudInfo.codec_id = (HI_S32)OMX_CODEC_ID_FLAC;
            break;
        case OMX_IndexParamAudioAndroidLpcm:
            pstFFmpegConfig->stFfmpeg_AudInfo.u32SampleRate   = ((OMX_AUDIO_PARAM_PCMMODETYPE*)(pHAData->pCodecParam))->nSamplingRate;
            pstFFmpegConfig->stFfmpeg_AudInfo.u16Channels     = ((OMX_AUDIO_PARAM_PCMMODETYPE*)(pHAData->pCodecParam))->nChannels;
            pstFFmpegConfig->stFfmpeg_AudInfo.u16BitPerSample = ((OMX_AUDIO_PARAM_PCMMODETYPE*)(pHAData->pCodecParam))->nBitPerSample;
            pstFFmpegConfig->stFfmpeg_AudInfo.bBigEndian      = (HI_BOOL)(((OMX_AUDIO_PARAM_PCMMODETYPE*)(pHAData->pCodecParam))->eEndian);
            pstFFmpegConfig->stFfmpeg_AudInfo.codec_id = (HI_S32)OMX_CODEC_ID_PCM_S16LE;
            break;
        default:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "Unsupport IndexAudioParam(0x%x)\n", IndexAudioParam);
            return OMX_ErrorInsufficientResources;
    }

    HA_FFMPEGC_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram, pstFFmpegConfig);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_FFMPEG_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXFFMPEGInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec Param
    pHAData->pCodecPrivData = (HA_FFMPEG_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_FFMPEG_PRIVDATA));
    if (HI_NULL == pHAData->pCodecPrivData)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecPrivData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_FFMPEG_PRIVDATA));

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXFFMPEGGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
        OMX_IN OMX_INDEXTYPE  nParamIndex,
        OMX_INOUT OMX_PTR     pParamStructure)
{
    HI_AUDDATATYPE* pHAData;
    OMX_ERRORTYPE   eError = OMX_ErrorNone;
    TRP_IN();

    pHAData = (HI_AUDDATATYPE*)(((OMX_COMPONENTTYPE*)hComponent)->pComponentPrivate);
    OMX_CONF_CHECK_CMD(pHAData, pParamStructure, 1);

    if (pHAData->state == OMX_StateReserved_0x00000000)
    {
        OMX_CONF_SET_ERROR_BAIL(eError, OMX_ErrorIncorrectStateOperation);
    }

    //need to add which nParamIndex (such as OMX_IndexParamAudioFlac) ffmpeg to support
    switch ((HI_U32)nParamIndex)
    {
        case OMX_IndexParamPortDefinition:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamPortDefinition\n", __FUNCTION__);
            if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sInPortDef.nPortIndex)
            {
                memcpy(pParamStructure, &pHAData->sInPortDef,  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sOutPortDef.nPortIndex)
            {
                memcpy(pParamStructure, &pHAData->sOutPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorBadPortIndex\n", __FUNCTION__);
                eError = OMX_ErrorBadPortIndex;
            }
            break;

        case OMX_IndexParamAudioFlac:
        {
            OMX_AUDIO_PARAM_FLACTYPE* Params = (OMX_AUDIO_PARAM_FLACTYPE*)pParamStructure;
            Params->nChannels   = pHAData->sPcm.nChannels;
            Params->nSampleRate = pHAData->sPcm.nSamplingRate;

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioFlac\n", __FUNCTION__);
            break;
        }

        case OMX_IndexParamAudioPcm:
        case OMX_IndexParamAudioAndroidLpcm:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioPcm\n", __FUNCTION__);
            OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams = (OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
            if (pcmParams->nPortIndex > 1)
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorUndefined\n", __FUNCTION__);
                return OMX_ErrorUndefined;
            }
            pcmParams->eNumData           = OMX_NumericalDataSigned;
            pcmParams->eEndian            = OMX_EndianLittle;
            pcmParams->bInterleaved       = OMX_TRUE;
            pcmParams->nBitPerSample      = 16;
            pcmParams->ePCMMode           = OMX_AUDIO_PCMModeLinear;
            pcmParams->eChannelMapping[0] = OMX_AUDIO_ChannelLF;
            pcmParams->eChannelMapping[1] = OMX_AUDIO_ChannelRF;
            pcmParams->nChannels          = pHAData->sPcm.nChannels;
            pcmParams->nSamplingRate      = pHAData->sPcm.nSamplingRate;
            break;

        default:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorUnsupportedIndex\n", __FUNCTION__);
            eError = OMX_ErrorUnsupportedIndex;
            break;
    }

OMX_CONF_CMD_BAIL:
    TRP_OUT();
    return eError;
}

static OMX_ERRORTYPE OMXFFMPEGSetParameter(OMX_IN OMX_HANDLETYPE hComponent,
        OMX_IN OMX_INDEXTYPE  nIndex,
        OMX_IN OMX_PTR        pParamStructure)
{
    HI_AUDDATATYPE* pHAData;
    OMX_ERRORTYPE   eError = OMX_ErrorNone;
    TRP_IN();

    pHAData = (HI_AUDDATATYPE*)(((OMX_COMPONENTTYPE*)hComponent)->pComponentPrivate);
    OMX_CONF_CHECK_CMD(pHAData, pParamStructure, 1);

    if (pHAData->state != OMX_StateLoaded)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> OMX_ErrorIncorrectStateOperation\n", __FUNCTION__);
        OMX_CONF_SET_ERROR_BAIL(eError, OMX_ErrorIncorrectStateOperation);
    }

    /* need to add which nParamIndex (such as OMX_IndexParamAudioFlac) ffmpeg to support
       and should do the component init ! */
    switch ((HI_U32)nIndex)
    {
        case OMX_IndexParamStandardComponentRole:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamStandardComponentRole\n", __FUNCTION__);
            const OMX_PARAM_COMPONENTROLETYPE* roleParams = (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;
            //need to add which codec ffmpeg to support
            if ((strncmp((const char*)roleParams->cRole, "audio_decoder.flac", OMX_MAX_STRINGNAME_SIZE - 1)) &&
                (strncmp((const char*)roleParams->cRole, "audio_decoder.lpcm", OMX_MAX_STRINGNAME_SIZE - 1)))
            {
                return OMX_ErrorUndefined;
            }
            break;

        case OMX_IndexParamPortDefinition:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamPortDefinition\n", __FUNCTION__);
            if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sInPortDef.nPortIndex)
            {
                memcpy(&pHAData->sInPortDef, pParamStructure, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sOutPortDef.nPortIndex)
            {
                memcpy(&pHAData->sOutPortDef, pParamStructure, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorBadPortIndex\n", __FUNCTION__);
                eError = OMX_ErrorBadPortIndex;
            }
            break;

        case OMX_IndexParamAudioFlac:
        case OMX_IndexParamAudioAndroidLpcm:
            ((HA_FFMPEG_PRIVDATA*)(pHAData->pCodecPrivData))->IndexAudioParam = nIndex;  //record the codec index

            // Create private codec Param
            if (OMX_IndexParamAudioAndroidLpcm == (HI_U32)nIndex)
            {
                pHAData->pCodecParam = (OMX_AUDIO_PARAM_PCMMODETYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
                if (!pHAData->pCodecParam)
                {
                    OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecData OMX_OSAL_Malloc failed\n");
                    return OMX_ErrorInsufficientResources;
                }
                memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
                memcpy((OMX_AUDIO_PARAM_PCMMODETYPE*)pHAData->pCodecParam, pParamStructure, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
            }
            else
            {
                //TO Add more codec
            }

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioffmpeg(nIndex=0x%x)\n", __FUNCTION__, nIndex);
			eError = OMXFFMPEGInitDecoder(pHAData);
            if (OMX_ErrorNone != eError)
            {
                if (pHAData->pCodecParam)
                {
                    OMX_OSAL_Free(pHAData->pCodecParam);
                }
            }
            break;

        default:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorUnsupportedIndex\n", __FUNCTION__);
            eError = OMX_ErrorUnsupportedIndex;
            break;
    }

OMX_CONF_CMD_BAIL:
    TRP_OUT();
    return eError;
}

OMX_ERRORTYPE component_init(OMX_HANDLETYPE pHandle, OMX_STRING comp_name)
{
    HI_S32 s32Ret;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    HI_AUDDATATYPE* pHAData = HI_NULL;
    OMX_COMPONENTTYPE* pComponent;

    HA_UNUSED_PARAMETER(comp_name);

    eError = OMX_AUDIO_COMMON_Init(pHandle, &pHAData);
    if (OMX_ErrorNone != eError)
    {
        return eError;
    }

    eError = OMXFFMPEGInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter      = OMXFFMPEGGetParameter;
    pComponent->SetParameter      = OMXFFMPEGSetParameter;
    pComponent->ComponentRoleEnum = HI_NULL;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/mpeg";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingFLAC;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("FFMPEG decoder init ok!\n");

    return OMX_ErrorNone;

INIT_EXIT:
    OMX_HAADEC_DeInit(pHAData);
    OMX_HAADEC_PrivDataDeInit(pHAData);
    OMX_AUDIO_COMMON_DeInit(pHAData);

    return eError;
}

#ifdef __cplusplus
}
#endif

