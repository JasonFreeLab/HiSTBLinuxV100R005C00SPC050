/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_COOK_Adec.c
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
#include "HA.AUDIO.COOK.decode.h"
#include "OMX_Audio_Hisi.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_COOK"
#endif


/* defination related to cook decoder */
#define AUDIO_DEC_RA_ROLE   "audio_decoder.ra"
#define HA_COOK_LIB_NAME    "libHA.AUDIO.COOK.decode.so"
#define GECKO_VERSION       ((1L<<24)|(0L<<16)|(0L<<8)|(3L))


typedef struct
{
    RA_FORMAT_INFO_S  stRaFormat;
    HI_U8   u8Extradata[30];
} HA_COOK_PRIVDATA;


/*
 *  Functions
 */
static HI_S32 OMXCOOKInitDecoder(HI_AUDDATATYPE* pHAData)
{
    HI_S32  s32Ret;
    HI_U8*  pExtradata;
    HI_U8   u8Temp = 0;
    HI_U32* pVersion;
    OMX_AUDIO_PARAM_RATYPE* pOmxRAtype;
    RA_FORMAT_INFO_S*  pRaFormat;

    pRaFormat  = &((HA_COOK_PRIVDATA*)(pHAData->pCodecPrivData))->stRaFormat;
    pOmxRAtype = (OMX_AUDIO_PARAM_RATYPE*)pHAData->pCodecParam;

    pRaFormat->ulActualRate    = pOmxRAtype->nSamplingRate;
    pRaFormat->ulBitsPerFrame  = pOmxRAtype->nBitsPerFrame;
    pRaFormat->ulGranularity   = pOmxRAtype->nBitsPerFrame;
    pRaFormat->ulSampleRate    = pOmxRAtype->nSamplingRate;
    pRaFormat->usAudioQuality  = 100;
    pRaFormat->usFlavorIndex   = 7;
    pRaFormat->usNumChannels   = pOmxRAtype->nChannels;

    if (pOmxRAtype->nBitsPerFrame)
    {
        pRaFormat->usBitsPerSample = pOmxRAtype->nBitsPerFrame;
    }
    else
    {
        pRaFormat->usBitsPerSample = 16;
    }

    pVersion = (HI_U32*)(&pOmxRAtype->nVersion);

    pExtradata = ((HA_COOK_PRIVDATA*)(pHAData->pCodecPrivData))->u8Extradata;

    pExtradata[u8Temp + 3] = (*pVersion & 0xff);
    pExtradata[u8Temp + 2] = (*pVersion & (0xff << 8))  >> 8;
    pExtradata[u8Temp + 1] = (*pVersion & (0xff << 16)) >> 16;
    pExtradata[u8Temp + 0] = (*pVersion & (0xff << 24)) >> 24;

    pExtradata[u8Temp + 5] = (pOmxRAtype->nSamplePerFrame & 0xff);
    pExtradata[u8Temp + 4] = (pOmxRAtype->nSamplePerFrame & (0xff << 8)) >> 8;

    pExtradata[u8Temp + 7] = (pOmxRAtype->nNumRegions & 0xff);
    pExtradata[u8Temp + 6] = (pOmxRAtype->nNumRegions & (0xff << 8)) >> 8;

    pExtradata[u8Temp + 13] = (pOmxRAtype->nCouplingStartRegion & 0xff);
    pExtradata[u8Temp + 12] = (pOmxRAtype->nCouplingStartRegion & (0xff << 8)) >> 8;

    pExtradata[u8Temp + 15] = (pOmxRAtype->nCouplingQuantBits & 0xff);
    pExtradata[u8Temp + 14] = (pOmxRAtype->nCouplingQuantBits & (0xff << 8)) >> 8;

    pRaFormat->pOpaqueData = pExtradata;
    pRaFormat->ulOpaqueDataSize = 16;

    HA_COOK_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram, pRaFormat);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_COOK_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXCOOKInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec data
    pHAData->pCodecParam = (OMX_AUDIO_PARAM_RATYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_RATYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecParam OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_RATYPE));
    ((OMX_AUDIO_PARAM_RATYPE*)(pHAData->pCodecParam))->eFormat = OMX_AUDIO_RA9;

    // Create private codec Param
    pHAData->pCodecPrivData = (HA_COOK_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_COOK_PRIVDATA));
    if (HI_NULL == pHAData->pCodecPrivData)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecPrivData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_COOK_PRIVDATA));

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXCOOKGetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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
            if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sInPortDef.nPortIndex)
            {
                memcpy(pParamStructure, &pHAData->sInPortDef,  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else if (((OMX_PARAM_PORTDEFINITIONTYPE*)(pParamStructure))->nPortIndex == pHAData->sOutPortDef.nPortIndex)
            {
                pHAData->sOutPortDef.nBufferSize = 8192;
                memcpy(pParamStructure, &pHAData->sOutPortDef, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
            }
            else
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorBadPortIndex\n", __FUNCTION__);
                eError = OMX_ErrorBadPortIndex;
            }
            break;

        case OMX_IndexParamAudioRa:
        {
            OMX_AUDIO_PARAM_RATYPE* Params = (OMX_AUDIO_PARAM_RATYPE*)pParamStructure;
            Params->nChannels     = pHAData->sPcm.nChannels;
            Params->nSamplingRate = pHAData->sPcm.nSamplingRate;

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioRa\n", __FUNCTION__);
            break;
        }

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

static OMX_ERRORTYPE OMXCOOKSetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamStandardComponentRole\n", __FUNCTION__);
            const OMX_PARAM_COMPONENTROLETYPE* roleParams = (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;
            if (strncmp((const char*)roleParams->cRole, "audio_decoder.ra", OMX_MAX_STRINGNAME_SIZE - 1))
            {
                return OMX_ErrorUndefined;
            }
            break;

        case OMX_IndexParamAudioPcm:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioPcm\n", __FUNCTION__);
            const OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams = (const OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
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

        case OMX_IndexParamAudioRa:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioRa\n", __FUNCTION__);
            memcpy((OMX_AUDIO_PARAM_RATYPE*)pHAData->pCodecParam, pParamStructure, sizeof(OMX_AUDIO_PARAM_RATYPE));
            eError = OMXCOOKInitDecoder(pHAData);
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

static OMX_ERRORTYPE OMXCOOKGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent,
                                        OMX_OUT OMX_U8*       cRole,
                                        OMX_IN OMX_U32        nIndex)
{
    TRP_IN();

    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_RA_ROLE, sizeof(AUDIO_DEC_RA_ROLE));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_RA_ComponentRoleEnum!\n", __FUNCTION__);
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

    HA_UNUSED_PARAMETER(comp_name);

    eError = OMX_AUDIO_COMMON_Init(pHandle, &pHAData);
    if (OMX_ErrorNone != eError)
    {
        return eError;
    }

    eError = OMXCOOKInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter      = OMXCOOKGetParameter;
    pComponent->SetParameter      = OMXCOOKSetParameter;
    pComponent->ComponentRoleEnum = OMXCOOKGetRoleEnum;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/cook";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingRA;

    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("COOK decoder init ok!\n");

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

