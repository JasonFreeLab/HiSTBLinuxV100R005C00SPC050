/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_Vorbis_Adec.c
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
#include <OMX_Audio.h>
#include <OMX_Other.h>

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_StubbedComponent.h"
#include "ha_adec.h"
#include "omx_audio_base.h"
#include "omx_audio_common.h"
#include "HA.AUDIO.VORBIS.codec.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_Vorbis"
#endif


/* defination related to Vorbis decoder */
#define AUDIO_DEC_Vorbis_ROLE   "audio_decoder.Vorbis"
#define HA_Vorbis_LIB_NAME      "libHA.AUDIO.VORBIS.codec.so"


/*
 *  Functions
 */
static OMX_ERRORTYPE OMXVorbisInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec Param
    pHAData->pCodecParam = (OMX_AUDIO_PARAM_VORBISTYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_VORBISTYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_VORBISTYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam, OMX_AUDIO_PARAM_VORBISTYPE);
    //Default values for Vorbis audio param port
    ((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam)->nPortIndex      = 0x0;
    ((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam)->nChannels       = 2;
    ((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam)->nBitRate        = 0;
    ((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam)->nSampleRate     = 44100;
    ((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam)->nAudioBandWidth = 0x0;
    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXVorbisGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

    switch (nParamIndex)
    {
        case OMX_IndexParamPortDefinition:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamPortDefinition\n", __FUNCTION__);
            if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex
                == pHAData->sInPortDef.nPortIndex)
            {
                memcpy(pParamStructure, &pHAData->sInPortDef,  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else if (((OMX_PARAM_PORTDEFINITIONTYPE*)
                      (pParamStructure))->nPortIndex == pHAData->sOutPortDef.nPortIndex)
            {
                memcpy(pParamStructure, &pHAData->sOutPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorBadPortIndex\n", __FUNCTION__);
                eError = OMX_ErrorBadPortIndex;
            }

            break;

        case OMX_IndexParamAudioVorbis:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioVorbis\n", __FUNCTION__);
            memcpy(pParamStructure, (OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam, sizeof(OMX_AUDIO_PARAM_VORBISTYPE));
            break;

        case OMX_IndexParamAudioPcm:
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

static OMX_ERRORTYPE OMXVorbisSetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

    switch (nIndex)
    {
        case OMX_IndexParamStandardComponentRole:
        {
            const OMX_PARAM_COMPONENTROLETYPE* roleParams = (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamStandardComponentRole: %s\n", __FUNCTION__, (const char*)roleParams->cRole);

            if (strncmp((const char*)roleParams->cRole, "audio_decoder.Vorbis", OMX_MAX_STRINGNAME_SIZE - 1)
                && strncmp((const char*)roleParams->cRole, "audio_decoder.mp2", OMX_MAX_STRINGNAME_SIZE - 1)
                && strncmp((const char*)roleParams->cRole, "audio_decoder.mp1", OMX_MAX_STRINGNAME_SIZE - 1))
            {
                return OMX_ErrorUndefined;
            }

            break;
        }
        case OMX_IndexParamAudioPcm:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioPcm\n", __FUNCTION__);
            const OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams =
                (const OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
            if (pcmParams->nPortIndex != 1)
            {
                return OMX_ErrorUndefined;
            }

            pHAData->sPcm.nChannels     = pcmParams->nChannels;
            pHAData->sPcm.nSamplingRate = pcmParams->nSamplingRate;
            break;

        case OMX_IndexParamPortDefinition:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamPortDefinition\n", __FUNCTION__);
            if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex
                == pHAData->sInPortDef.nPortIndex)
            {
                memcpy(&pHAData->sInPortDef, pParamStructure, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else if (((OMX_PARAM_PORTDEFINITIONTYPE*)
                      (pParamStructure))->nPortIndex ==
                     pHAData->sOutPortDef.nPortIndex)
            {
                memcpy(&pHAData->sOutPortDef, pParamStructure, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorBadPortIndex\n", __FUNCTION__);
                eError = OMX_ErrorBadPortIndex;
            }

            break;

        case OMX_IndexParamAudioVorbis:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioVorbis\n", __FUNCTION__);
            memcpy((OMX_AUDIO_PARAM_VORBISTYPE*)pHAData->pCodecParam, pParamStructure,
                   sizeof(OMX_AUDIO_PARAM_VORBISTYPE));
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


static OMX_ERRORTYPE OMXVorbisGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent, OMX_OUT OMX_U8* cRole, OMX_IN OMX_U32 nIndex)
{
    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_Vorbis_ROLE, sizeof(AUDIO_DEC_Vorbis_ROLE));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_Vorbis_ComponentRoleEnum!\n", __FUNCTION__);
        return OMX_ErrorUnsupportedIndex;
    }

    return OMX_ErrorNone;
}

/*****************************************************************************/
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

    eError = OMXVorbisInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    HA_VORBIS_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_Vorbis_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXVorbisGetParameter;
    pComponent->SetParameter = OMXVorbisSetParameter;
    pComponent->ComponentRoleEnum = OMXVorbisGetRoleEnum;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/mpeg";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingVORBIS;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("Vorbis decoder init ok!\n");
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


