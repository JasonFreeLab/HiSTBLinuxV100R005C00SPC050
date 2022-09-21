/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_DTS_Adec.c
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
#include "OMX_IndexExt.h"
#include "OMX_AudioExt.h"

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_StubbedComponent.h"
#include "ha_adec.h"
#include "omx_audio_base.h"
#include "omx_audio_common.h"
#include "HA.AUDIO.DTSM6.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_DTS"
#endif


/* defination related to DTS decoder */
#define AUDIO_DEC_DTS_ROLE   "audio_decoder.dts"
#define HA_DTSM6_LIB_NAME    "libHA.AUDIO.DTSM6.decode.so"
#define HA_DTSHD_LIB_NAME    "libHA.AUDIO.DTSHD.decode.so"


typedef struct
{
    DTSM6_DECODE_OPENCONFIG_S  stConfig;
    DTSM6_STREAM_INFO_S        sM6StreamInfo;
} HA_DTSM6_PRIVDATA;

typedef struct
{
    DTSHD_DECODE_OPENCONFIG_S  stConfig;
} HA_DTSHD_PRIVDATA;


/*
 *  Functions
 */
static OMX_ERRORTYPE OMXDTSInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec data
    pHAData->pCodecParam = (OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_ANDROID_DTSTYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecParam OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_ANDROID_DTSTYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam, OMX_AUDIO_PARAM_ANDROID_DTSTYPE);
    //Default values for DTS audio param port
    ((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam)->nPortIndex  = 0x0;
    ((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam)->nChannels   = 2;
    ((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam)->nBitRate    = 0;
    ((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam)->nSampleRate = 44100;

    // Create dtsm6 private codec Param
    pHAData->pCodecPrivData = (HA_DTSM6_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_DTSM6_PRIVDATA));
    if (HI_NULL == pHAData->pCodecPrivData)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecPrivData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_DTSM6_PRIVDATA));

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXDTSGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

        case OMX_IndexParamAudioAndroidDts:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioAndroidDts\n", __FUNCTION__);
            memcpy(pParamStructure, (OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam, sizeof(OMX_AUDIO_PARAM_ANDROID_DTSTYPE));
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

static OMX_ERRORTYPE OMXDTSSetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

    switch ((HI_U32)nIndex)
    {
        case OMX_IndexParamStandardComponentRole:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamStandardComponentRole\n", __FUNCTION__);
            const OMX_PARAM_COMPONENTROLETYPE* roleParams =
                (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;
            if (strncmp((const char*)roleParams->cRole, "audio_decoder.dts", OMX_MAX_STRINGNAME_SIZE - 1))
            {
                return OMX_ErrorUndefined;
            }
            break;

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

        case OMX_IndexParamAudioAndroidDts:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioAndroidDts\n", __FUNCTION__);
            memcpy((OMX_AUDIO_PARAM_ANDROID_DTSTYPE*)pHAData->pCodecParam, pParamStructure, sizeof(OMX_AUDIO_PARAM_ANDROID_DTSTYPE));
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

static OMX_ERRORTYPE OMXDTSGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent,
                                       OMX_OUT OMX_U8*       cRole,
                                       OMX_IN OMX_U32        nIndex)
{
    TRP_IN();

    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_DTS_ROLE, sizeof(AUDIO_DEC_DTS_ROLE));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_DTS_ComponentRoleEnum!\n", __FUNCTION__);
        return OMX_ErrorUnsupportedIndex;
    }

    TRP_OUT();
    return OMX_ErrorNone;
}

OMX_ERRORTYPE component_init(OMX_HANDLETYPE pHandle, OMX_STRING comp_name)
{
    HI_S32 s32Ret;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    HI_AUDDATATYPE* pHAData = HI_NULL;
    OMX_COMPONENTTYPE* pComponent;
    DTSM6_DECODE_OPENCONFIG_S* pstM6Config;
    DTSM6_STREAM_INFO_S*       pstM6StreamInfo;
    DTSHD_DECODE_OPENCONFIG_S* pstHDConfig;

    HA_UNUSED_PARAMETER(comp_name);

    eError = OMX_AUDIO_COMMON_Init(pHandle, &pHAData);
    if (OMX_ErrorNone != eError)
    {
        return eError;
    }

    eError = OMXDTSInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    pstM6Config = &((HA_DTSM6_PRIVDATA*)(pHAData->pCodecPrivData))->stConfig;
    pstM6StreamInfo = &((HA_DTSM6_PRIVDATA*)(pHAData->pCodecPrivData))->sM6StreamInfo;

    HA_DTSM6_DecGetDefalutOpenConfig(pstM6Config);
    pstM6Config->pAppData[HA_DTSM6_EVENT_SOURCE_CHANGE] = pstM6StreamInfo;
    HA_DTSM6_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram, pstM6Config);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_DTSM6_LIB_NAME);
    if (OMX_ErrorComponentNotFound == s32Ret)
    {
        OMX_OSAL_Free(pHAData->pCodecPrivData);
        pHAData->pCodecPrivData = HI_NULL;

        // Create dtshd private codec Param
        pHAData->pCodecPrivData = (HA_DTSHD_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_DTSHD_PRIVDATA));
        if (HI_NULL == pHAData->pCodecPrivData)
        {
            eError = OMX_ErrorInsufficientResources;
            goto INIT_EXIT;
        }

        memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_DTSHD_PRIVDATA));
        pstHDConfig = &((HA_DTSHD_PRIVDATA*)(pHAData->pCodecPrivData))->stConfig;

        HA_DTSHD_DecGetDefalutOpenConfig(pstHDConfig);
        HA_DTSHD_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram, pstHDConfig);
        s32Ret = OMX_HAADEC_Init(pHAData, HA_DTSHD_LIB_NAME);
        if (HI_SUCCESS != s32Ret)
        {
            eError = OMX_ErrorInsufficientResources;
            goto INIT_EXIT;
        }
    }
    else if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXDTSGetParameter;
    pComponent->SetParameter = OMXDTSSetParameter;
    pComponent->ComponentRoleEnum = OMXDTSGetRoleEnum;

    pHAData->stAdec.bDTSDecode   = HI_TRUE;
    pHAData->stAdec.bPassThrough = HI_TRUE;
    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/dts";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingAndroidDTS;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("DTS decoder init ok!\n");

    return OMX_ErrorNone;

INIT_EXIT:
    OMX_HAADEC_DeInit(pHAData);
    OMX_HAADEC_PrivDataDeInit(pHAData);
    OMX_AUDIO_COMMON_DeInit(pHAData);

    return eError;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

