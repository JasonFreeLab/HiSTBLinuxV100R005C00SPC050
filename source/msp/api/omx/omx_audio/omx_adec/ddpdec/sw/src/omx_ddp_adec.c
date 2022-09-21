/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_DDP_Adec.c
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
#include "HA.AUDIO.DOLBYPLUS.decode.h"
#include "OMX_Audio_Hisi.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_DDP"
#endif


/* defination related to ddp decoder */
#define AUDIO_DEC_DDP_ROLE1  "audio_decoder.ac3"
#define AUDIO_DEC_DDP_ROLE2  "audio_decoder.ec3"
#define HA_DDP_LIB_NAME      "libHA.AUDIO.DOLBYPLUS.decode.so"


typedef struct
{
    DOLBYPLUS_STREAM_INFO_S sDDPStreamInfo;
    DOLBYPLUS_DECODE_OPENCONFIG_S sDDPConfig;
} HA_DOLBY_PRIVDATA;


/*
 *  Functions
*/
static HI_VOID DDPlusCallBack(DOLBYPLUS_EVENT_E Event, HI_VOID* pUserData)
{
    DOLBYPLUS_STREAM_INFO_S* pstInfo = (DOLBYPLUS_STREAM_INFO_S*)pUserData;
    if (HA_DOLBYPLUS_EVENT_BUTT <= Event)
    {
        // error event
        return;
    }

    HA_UNUSED_PARAMETER(pstInfo);
#if 0
    printf( "DDPlusCallBack show info:\n \
                s16StreamType          = %d\n \
                s16Acmod               = %d\n \
                s32BitRate             = %d\n \
                s32SampleRateRate      = %d\n \
                Event                  = %d\n",
            pstInfo->s16StreamType, pstInfo->s16Acmod, pstInfo->s32BitRate, pstInfo->s32SampleRateRate, Event);
#endif
}

static OMX_ERRORTYPE OMXDDPInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec data
    pHAData->pCodecParam = (OMX_HA_PARAM_DOLBYTYPE*)OMX_OSAL_Malloc(sizeof(OMX_HA_PARAM_DOLBYTYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecParam OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_HA_PARAM_DOLBYTYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam, OMX_HA_PARAM_DOLBYTYPE);
    //Default values for Dolby audio param port
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nPortIndex  = 0x0;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nChannels   = 2;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nBitRate    = 0;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nSampleRate = 44100;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nDRCPercent = 0;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->nDRCPercent = DOLBYPLUS_DRC_LINE;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->eStreamType = OMX_DOLBY_STREAMTYPE_DD;
    ((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam)->eAcmod      = OMX_DOLBY_CHANCFG_OUT_MODE20;

    // Create private codec Param
    pHAData->pCodecPrivData = (HA_DOLBY_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_DOLBY_PRIVDATA));
    if (HI_NULL == pHAData->pCodecPrivData)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecPrivData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_DOLBY_PRIVDATA));

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXDDPGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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
                memcpy(pParamStructure, &pHAData->sInPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
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

        case OMX_HA_IndexParamAudioDolby:
            ((OMX_HA_PARAM_DOLBYTYPE*)(pHAData->pCodecParam))->eStreamType =
                (OMX_HA_DOLBYSTREAMTYPE)(((HA_DOLBY_PRIVDATA*)(pHAData->pCodecPrivData))->sDDPStreamInfo.s16StreamType);
            ((OMX_HA_PARAM_DOLBYTYPE*)(pHAData->pCodecParam))->eAcmod =
                (OMX_HA_DOLBYCHANCFG) (((HA_DOLBY_PRIVDATA*)(pHAData->pCodecPrivData))->sDDPStreamInfo.s16Acmod);

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_HA_IndexParamAudioDolby StreamType:%d, ChanConfig:%d\n", __FUNCTION__,
                           ((OMX_HA_PARAM_DOLBYTYPE*)(pHAData->pCodecParam))->eStreamType,
                           ((OMX_HA_PARAM_DOLBYTYPE*)(pHAData->pCodecParam))->eAcmod);

            memcpy(pParamStructure, (OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam, sizeof(OMX_HA_PARAM_DOLBYTYPE));
            break;


        case OMX_IndexParamAudioPcm:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioPcm\n", __FUNCTION__);
            OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams = (OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
            if (pcmParams->nPortIndex > OMX_OUT_PORT_IDX)
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorUndefined\n", __FUNCTION__);
                return OMX_ErrorUndefined;
            }
            pcmParams->eNumData = OMX_NumericalDataSigned;
            pcmParams->eEndian = OMX_EndianLittle;
            pcmParams->bInterleaved = OMX_TRUE;
            pcmParams->nBitPerSample = 16;
            pcmParams->ePCMMode = OMX_AUDIO_PCMModeLinear;
            pcmParams->eChannelMapping[0] = OMX_AUDIO_ChannelLF;
            pcmParams->eChannelMapping[1] = OMX_AUDIO_ChannelRF;
            pcmParams->eChannelMapping[2] = OMX_AUDIO_ChannelCF;
            pcmParams->eChannelMapping[3] = OMX_AUDIO_ChannelLFE;
            pcmParams->eChannelMapping[4] = OMX_AUDIO_ChannelLS;
            pcmParams->eChannelMapping[5] = OMX_AUDIO_ChannelRS;
            pcmParams->eChannelMapping[6] = OMX_AUDIO_ChannelLR;
            pcmParams->eChannelMapping[7] = OMX_AUDIO_ChannelRR;
            pcmParams->nChannels     = pHAData->sPcm.nChannels;
            pcmParams->nSamplingRate = pHAData->sPcm.nSamplingRate;
            break;

        case OMX_IndexParamAudioAndroidAc3:
        case OMX_IndexParamAudioAndroidEac3:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> TOCHECK  0x%x\n", __FUNCTION__, nParamIndex);
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

static OMX_ERRORTYPE OMXDDPSetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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
            const OMX_PARAM_COMPONENTROLETYPE* roleParams = (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;
            if (strncmp((const char*)roleParams->cRole, "audio_decoder.ac3",  OMX_MAX_STRINGNAME_SIZE - 1) &&
                strncmp((const char*)roleParams->cRole, "audio_decoder.eac3", OMX_MAX_STRINGNAME_SIZE - 1))
            {
                return OMX_ErrorUndefined;
            }
            break;

        case OMX_IndexParamAudioPcm:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioPcm\n", __FUNCTION__);
            const OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams = (OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
            pHAData->sPcm.nChannels     = pcmParams->nChannels;
            pHAData->sPcm.nSamplingRate = pcmParams->nSamplingRate;
            if (pcmParams->nPortIndex != OMX_OUT_PORT_IDX)
            {
                return OMX_ErrorUndefined;
            }
            if (pcmParams->nChannels < 1 || pcmParams->nChannels > 8)
            {
                return OMX_ErrorUndefined;
            }
            break;

        case OMX_HA_IndexParamAudioDolby:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_HA_IndexParamAudioDolby\n", __FUNCTION__);
            memcpy((OMX_HA_PARAM_DOLBYTYPE*)pHAData->pCodecParam, pParamStructure, sizeof(OMX_HA_PARAM_DOLBYTYPE));
            //TODO DRC Setting
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
                eError = OMX_ErrorBadPortIndex;
            }
            break;

        case OMX_IndexParamAudioAndroidAc3:
        case OMX_IndexParamAudioAndroidEac3:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> TOCHECK  0x%x\n", __FUNCTION__, nIndex);
            break;

        default:
            eError = OMX_ErrorUnsupportedIndex;
            break;
    }

OMX_CONF_CMD_BAIL:
    TRP_OUT();
    return eError;
}

static OMX_ERRORTYPE OMXDDPGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent,
                                       OMX_OUT OMX_U8*       cRole,
                                       OMX_IN OMX_U32        nIndex)
{
    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_DDP_ROLE1, sizeof(AUDIO_DEC_DDP_ROLE1));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_DDP_ComponentRoleEnum!\n", __FUNCTION__);
        return OMX_ErrorUnsupportedIndex;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE component_init(OMX_HANDLETYPE pHandle, OMX_STRING comp_name)
{
    HI_S32 s32Ret;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    HI_AUDDATATYPE* pHAData = HI_NULL;
    OMX_COMPONENTTYPE* pComponent;
    DOLBYPLUS_STREAM_INFO_S* pstDDPStreamInfo;
    DOLBYPLUS_DECODE_OPENCONFIG_S* pstDDPConfig;

    HA_UNUSED_PARAMETER(comp_name);

    eError = OMX_AUDIO_COMMON_Init(pHandle, &pHAData);
    if (OMX_ErrorNone != eError)
    {
        return eError;
    }

    eError = OMXDDPInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    pstDDPConfig = &((HA_DOLBY_PRIVDATA*)(pHAData->pCodecPrivData))->sDDPConfig;
    pstDDPStreamInfo = &((HA_DOLBY_PRIVDATA*)(pHAData->pCodecPrivData))->sDDPStreamInfo;

    HA_DOLBYPLUS_DecGetDefalutOpenConfig(pstDDPConfig);

    /* Dolby Default Settings */
    pstDDPConfig->enDrcMode = DOLBYPLUS_DRC_LINE;
    pstDDPConfig->enDmxMode = DOLBYPLUS_DMX_SRND;
    pstDDPConfig->enOutLfe  = DOLBYPLUS_LFEOUTOFF;
    pstDDPConfig->pAppData[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE] = pstDDPStreamInfo;
    pstDDPConfig->pfnEvtCbFunc[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE] = DDPlusCallBack;

    HA_DOLBYPLUS_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram, pstDDPConfig);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_DDP_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXDDPGetParameter;
    pComponent->SetParameter = OMXDDPSetParameter;
    pComponent->ComponentRoleEnum = OMXDDPGetRoleEnum;

    pHAData->stAdec.bPassThrough = HI_TRUE;
    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/ac3";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingAndroidEAC3;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("DDP decoder init ok!\n");

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

/* File EOF */
