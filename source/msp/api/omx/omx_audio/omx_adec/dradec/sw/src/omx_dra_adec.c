/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_DRA_Adec.c
Author:  Audio
Date:    2016

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
#include "HA.AUDIO.DRA.decode.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_DRA"
#endif


/* defination related to dra decoder */
#define AUDIO_DEC_DRA_ROLE   "audio_decoder.dra"
#define HA_DRA_LIB_NAME      "libHA.AUDIO.DRA.decode.so"


/*
 *  Functions
 */
static OMX_ERRORTYPE OMXDRAInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec Param
    pHAData->pCodecParam =(OMX_AUDIO_PARAM_DRATYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_DRATYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_DRATYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam, OMX_AUDIO_PARAM_DRATYPE);
    //Default values for Dra audio param port
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->nPortIndex      = 0x0;
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->nChannels       = 2;
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->nBitRate        = 0;
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->nSampleRate     = 48000;
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->nAudioBandWidth = 0x0;
    ((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam)->eChannelMode    = OMX_AUDIO_ChannelModeStereo;

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXDRAGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

        case OMX_IndexParamAudioDra:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioDra\n", __FUNCTION__);
            memcpy(pParamStructure, (OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam, sizeof(OMX_AUDIO_PARAM_DRATYPE));
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

static OMX_ERRORTYPE OMXDRASetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

            if (strncmp((const char*)roleParams->cRole, "audio_decoder.dra", OMX_MAX_STRINGNAME_SIZE - 1))
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

        case OMX_IndexParamAudioDra:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioDra\n", __FUNCTION__);
            memcpy((OMX_AUDIO_PARAM_DRATYPE*)pHAData->pCodecParam, pParamStructure,
                   sizeof(OMX_AUDIO_PARAM_DRATYPE));
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


static OMX_ERRORTYPE OMXDRAGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent, OMX_OUT OMX_U8* cRole, OMX_IN OMX_U32 nIndex)
{
    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_DRA_ROLE, sizeof(AUDIO_DEC_DRA_ROLE));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_DRA_ComponentRoleEnum!\n", __FUNCTION__);
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

    eError = OMXDRAInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    HA_DRA_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_DRA_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXDRAGetParameter;
    pComponent->SetParameter = OMXDRASetParameter;
    pComponent->ComponentRoleEnum = OMXDRAGetRoleEnum;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/mpeg";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingDRA;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("DRA decoder init ok!\n");

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

