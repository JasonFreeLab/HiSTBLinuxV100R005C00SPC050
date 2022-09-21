/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_AAC_Adec.c
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
#include <OMX_Other.h>

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_StubbedComponent.h"
#include "ha_adec.h"
#include "omx_audio_base.h"
#include "omx_audio_common.h"
#include "HA.AUDIO.AAC.decode.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_AAC"
#endif

/* defination related to aac decoder */
#define AUDIO_DEC_AAC_ROLE    "audio_decoder.aac"
#define HA_AAC_LIB_NAME       "libHA.AUDIO.AAC.decode.so"


typedef struct
{
    HI_UCHAR configbuf[FILEREAD_MAX_LAYERS];;
    HI_U32 buflength[FILEREAD_MAX_LAYERS];
} HA_AAC_PRIVDATA;


/*
 *  Functions
*/
static OMX_ERRORTYPE OMXAACInitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec data
    pHAData->pCodecParam = (OMX_AUDIO_PARAM_AACPROFILETYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecParam OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam, OMX_AUDIO_PARAM_AACPROFILETYPE);
    //Default values for Aac audio param port
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nPortIndex       = 0x0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nChannels        = 2;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nSampleRate      = 48000;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nBitRate         = 0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nAudioBandWidth  = 0x0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nFrameLength     = 0x0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nAACtools        = 0x0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->nAACERtools      = 0x0;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->eAACProfile      = OMX_AUDIO_AACObjectMain;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP4ADTS;
    ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->eChannelMode     = OMX_AUDIO_ChannelModeStereo;

    // Create private codec Param
    pHAData->pCodecPrivData = (HA_AAC_PRIVDATA*)OMX_OSAL_Malloc(sizeof(HA_AAC_PRIVDATA));
    if (HI_NULL == pHAData->pCodecPrivData)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecPrivData OMX_OSAL_Malloc failed\n");
        OMX_OSAL_Free(pHAData->pCodecParam);
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecPrivData, 0x0, sizeof(HA_AAC_PRIVDATA));

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXAACGetParameter(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_INDEXTYPE nIndex, OMX_INOUT OMX_PTR pParamStructure)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    HI_AUDDATATYPE* pHAData;

    TRP_IN();

    pHAData = (HI_AUDDATATYPE*)(((OMX_COMPONENTTYPE*)hComponent)->pComponentPrivate);

    OMX_CONF_CHECK_NULLPTR(pHAData);
    OMX_CONF_CHECK_NULLPTR(pParamStructure);

    if (OMX_StateReserved_0x00000000 == pHAData->state)
    {
        return OMX_ErrorIncorrectStateOperation;
    }

    switch ((HI_U32)nIndex)
    {
        case OMX_IndexParamPortDefinition:
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
                eError = OMX_ErrorBadPortIndex;
            }
            break;
        case OMX_IndexParamAudioAac:
            memcpy(pParamStructure, (OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
            break;
        case OMX_IndexParamAudioPcm:
        {
            OMX_AUDIO_PARAM_PCMMODETYPE* pcmParams = (OMX_AUDIO_PARAM_PCMMODETYPE*)pParamStructure;
            if (OMX_OUT_PORT_IDX != pcmParams->nPortIndex)
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
            pcmParams->eChannelMapping[2] = OMX_AUDIO_ChannelCF;
            pcmParams->eChannelMapping[3] = OMX_AUDIO_ChannelLFE;
            pcmParams->eChannelMapping[4] = OMX_AUDIO_ChannelLS;
            pcmParams->eChannelMapping[5] = OMX_AUDIO_ChannelRS;
            pcmParams->nChannels          = pHAData->sPcm.nChannels;
            pcmParams->nSamplingRate      = pHAData->sPcm.nSamplingRate;
            break;
        }
        default:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_ErrorUnsupportedIndex\n", __FUNCTION__);
            eError = OMX_ErrorUnsupportedIndex;
            break;
    }

    TRP_OUT();
    return eError;
}

static OMX_ERRORTYPE OMXAACSetParameter(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_INDEXTYPE nIndex, OMX_IN OMX_PTR pParamStructure)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    HI_AUDDATATYPE* pHAData;

    TRP_IN();

    pHAData = (HI_AUDDATATYPE*)(((OMX_COMPONENTTYPE*)hComponent)->pComponentPrivate);

    OMX_CONF_CHECK_NULLPTR(pHAData);
    OMX_CONF_CHECK_NULLPTR(pParamStructure);

    if (OMX_StateLoaded != pHAData->state)
    {
        return OMX_ErrorIncorrectStateOperation;
    }

    switch ((HI_U32)nIndex)
    {
        case OMX_IndexParamStandardComponentRole:
        {
            const OMX_PARAM_COMPONENTROLETYPE* roleParams = (const OMX_PARAM_COMPONENTROLETYPE*)pParamStructure;
            if (strncmp((const char*)roleParams->cRole, "audio_decoder.aac", OMX_MAX_STRINGNAME_SIZE - 1))
            {
                eError = OMX_ErrorUndefined;
            }
            break;
        }
        case OMX_IndexParamPortDefinition:
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
        case OMX_IndexParamAudioAac:
            memcpy((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam, pParamStructure, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
            break;
        case OMX_IndexParamAudioPcm:
        case OMX_IndexParamAudioAndroidAacPresentation:
            break;
        default:
            OAD_PRINT_TRACE("%s -> OMX_ErrorUnsupportedIndex\n", __FUNCTION__);
            eError = OMX_ErrorUnsupportedIndex;
            break;
    }

    TRP_OUT();

    return eError;
}

static OMX_ERRORTYPE OMXAACGetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent, OMX_OUT OMX_U8* cRole, OMX_IN OMX_U32 nIndex)
{
    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_AAC_ROLE, sizeof(AUDIO_DEC_AAC_ROLE));
    }
    else
    {
        OAD_PRINT_ERROR("%s -> Fail: Can not get HI_OMX_AAC_ComponentRoleEnum!\n", __FUNCTION__);
        return OMX_ErrorUnsupportedIndex;
    }

    return OMX_ErrorNone;
}

static HI_VOID OMXAACUpdateEOSState(HI_AUDDATATYPE* pHAData, OMX_BUFFERHEADERTYPE* pInBufHdr, OMX_BUFFERHEADERTYPE* pOutBufHdr, HI_S32 s32Ret)
{
    HA_ADEC_S*        pstAdec     = &pHAData->stAdec;
    HA_INTERNALBUF_S* pstInnerBuf = &pstAdec->sInternalBuf;

    if ((HI_FALSE == pstAdec->bPacketDecoder) && (HI_TRUE == pHAData->bInnerBufFlag))
    {
        if (HA_ErrorNone != s32Ret)
        {
            /* Flush Inner Buffer */
            if (0 != pstInnerBuf->s32Insize) //unlikely
            {
                pstInnerBuf->s32Insize  = 0;
                pHAData->bInnerBufFlag  = HI_FALSE;
                pOutBufHdr->nFilledLen  = pHAData->sPcm.nSize * pHAData->sPcm.nChannels * sizeof(HI_S16);
                pHAData->mAnchorTimeUs += pHAData->sPcm.nSize * 1000000 / pHAData->sPcm.nSamplingRate;
                memset(pOutBufHdr->pBuffer, 0, pOutBufHdr->nFilledLen);
            }

            pOutBufHdr->nTimeStamp = pHAData->mAnchorTimeUs;
            pHAData->mEndOfInput = HI_TRUE;
        }
        else
        {
            pHAData->enInBufState = OWNED_BY_CLIENT;
        }
    }
    else
    {
        if (0 == pInBufHdr->nFilledLen)
        {
            if (HA_ErrorNone != s32Ret)
            {
                pOutBufHdr->nTimeStamp = pHAData->mAnchorTimeUs;
            }

            pHAData->mEndOfInput = HI_TRUE;
        }
    }
}

static HI_S32 OMXAACProcessFrame(HI_VOID* pHAState, OMX_BUFFERHEADERTYPE* pInBufHdr, OMX_BUFFERHEADERTYPE* pOutBufHdr)
{
    HI_S32 s32Ret = HA_ErrorNone;
    HI_AUDDATATYPE* pHAData = (HI_AUDDATATYPE*)pHAState;
    HA_ADEC_S*        pstAdec     = &pHAData->stAdec;
    HA_INTERNALBUF_S* pstInnerBuf = &pstAdec->sInternalBuf;
    HI_HADECODE_INPACKET_S avpkt;
    HI_HADECODE_OUTPUT_S   avOut;
    HA_AAC_PRIVDATA*  pridata = pHAData->pCodecPrivData;
    avOut.ps32PcmOutBuf  = (HI_S32*)pOutBufHdr->pBuffer;

    if (0 == pHAData->mInputBufferCnt)
    {
        OMX_AUDIO_AACSTREAMFORMATTYPE enAACStreamFormat = ((OMX_AUDIO_PARAM_AACPROFILETYPE*)pHAData->pCodecParam)->eAACStreamFormat;

        if (OMX_AUDIO_AACStreamFormatMP4FF == enAACStreamFormat)
        {
            //without adts, default adif
            HA_AAC_SET_TRANSPORT_TYPE_S stType;
            HA_AAC_SET_CONFIGRAW_S    stConfigData;

            //step 1
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s setStreamFormat TT_MP4_ADIF\n", __FUNCTION__);
            stType.enCmd = HA_CODEC_AAC_SET_TRANSPORT_TYPE_CMD;
            stType.stType = HA_TT_MP4_ADIF;
            s32Ret = OMX_HAADEC_SetConfig(pHAData, &stType);
            if (HI_SUCCESS != s32Ret)
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "Config Code failed 0x%x", s32Ret);
                return s32Ret;
            }

            //step 2, configraw only for adif
            memset(&stConfigData, 0, sizeof(HA_AAC_SET_CONFIGRAW_S));
            stConfigData.enCmd = HA_CODEC_AAC_SET_CONFIGRAW_CMD;
            if (0 != (pInBufHdr->nFlags & OMX_BUFFERFLAG_CODECCONFIG))
            {
                HI_UCHAR* inBuffer[FILEREAD_MAX_LAYERS];
                HI_U32 inBufferLength[FILEREAD_MAX_LAYERS] = {0};
                inBuffer[0] = pInBufHdr->pBuffer + pInBufHdr->nOffset;
                inBufferLength[0] = pInBufHdr->nFilledLen;
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "Config Code   0x%x 0x%x 0x%x 0x%x   size=0x%x", *(inBuffer[0]), *(inBuffer[0] + 1), *(inBuffer[0] + 2), *(inBuffer[0] + 3), inBufferLength[0]);

                stConfigData.conf[0] = inBuffer[0];
                stConfigData.length[0] = inBufferLength[0];

                pridata->configbuf[0] = *(inBuffer[0]);
                pridata->configbuf[1] = *(inBuffer[0] + 1);
                pridata->buflength[0] = inBufferLength[0];
            }
            else    //without configraw
            {
                stConfigData.conf[0] = &(pridata->configbuf[0]);
                stConfigData.length[0] = pridata->buflength[0];
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "Config Private Code   0x%x 0x%x   size=0x%x", *(stConfigData.conf[0]), *(stConfigData.conf[0] + 1), stConfigData.length[0]);
            }

            s32Ret = OMX_HAADEC_SetConfig(pHAData, &stConfigData);
            if (HI_SUCCESS != s32Ret)
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "Config Code failed 0x%x", s32Ret);
                return s32Ret;
            }

            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "Config Code Ok");

            pHAData->sPcm.nSamplingRate = 0;
            pHAData->sPcm.nChannels     = 0;

            if (0 != (pInBufHdr->nFlags & OMX_BUFFERFLAG_CODECCONFIG))
            {
                pInBufHdr->nOffset    = pInBufHdr->nFilledLen;
                pInBufHdr->nFilledLen = 0;
                pHAData->enInBufState = OWNED_BY_COMPONENT;

                pHAData->mInputBufferCnt++;
                return HA_ErrorNotEnoughData;
            }
        }
    }

    /* Get the time stamp */
    if ((HI_TRUE == pHAData->bNewPacketIn) && pInBufHdr->nFilledLen)
    {
        pHAData->mInputBufferCnt++;
        pHAData->bNewPacketIn = HI_FALSE;

        if (0 <= pInBufHdr->nTimeStamp)
        {
            pHAData->mAnchorTimeUs = pInBufHdr->nTimeStamp;
        }
    }

    pOutBufHdr->nFlags    = pInBufHdr->nFlags & (~OMX_BUFFERFLAG_EOS);
    pHAData->enInBufState = OWNED_BY_US;

    /* Begin to decode */
    s32Ret = OMX_HAADEC_DecodeFrame(pHAData, &avpkt, &avOut, pInBufHdr);
    if (s32Ret == HA_ErrorNone)
    {
        pOutBufHdr->nFilledLen  = avOut.u32PcmOutSamplesPerFrame * sizeof(HI_S16) * avOut.u32OutChannels;
        pHAData->sPcm.nSize     = avOut.u32PcmOutSamplesPerFrame;
        pOutBufHdr->nTimeStamp  = pHAData->mAnchorTimeUs;
        pHAData->mAnchorTimeUs += avOut.u32PcmOutSamplesPerFrame * 1000000 / avOut.u32OutSampleRate;

        /* Change channel and samplerate information */
        if ((pHAData->sPcm.nSamplingRate != avOut.u32OutSampleRate) || (pHAData->sPcm.nChannels != avOut.u32OutChannels))
        {
            pHAData->sPcm.nSamplingRate = avOut.u32OutSampleRate;
            pHAData->sPcm.nChannels     = avOut.u32OutChannels;
            pHAData->bPortSetChange     = HI_TRUE;
        }

        OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "ADECDecodeFrame Success\n");
    }
    else
    {
        pHAData->enInBufState = OWNED_BY_COMPONENT;

        if ((HI_FALSE == pstAdec->bPacketDecoder) && (HI_TRUE == pHAData->bInnerBufFlag))
        {
            if ((0 != pstInnerBuf->s32Insize) && (0 != pstInnerBuf->s32Offset))
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "Inner Buffer NotEnoughData\n");
                memmove((HI_U8*)pstInnerBuf->pInBuffer, (HI_U8*)pstInnerBuf->pInBuffer + pstInnerBuf->s32Offset, pstInnerBuf->s32Insize);
            }
        }
        else
        {
            if ((0 != pInBufHdr->nFilledLen) && (HI_FALSE == pstAdec->bPacketDecoder))
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "New packet -> Inner (length=%ld)\n", pInBufHdr->nFilledLen);
                memcpy(pstInnerBuf->pInBuffer, pInBufHdr->pBuffer + pInBufHdr->nOffset, pInBufHdr->nFilledLen);
                pstInnerBuf->s32Insize = pInBufHdr->nFilledLen;
                pHAData->bInnerBufFlag = HI_TRUE;
            }
            pInBufHdr->nOffset   += pInBufHdr->nFilledLen;
            pInBufHdr->nFilledLen = 0;
        }

        OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "ADECDecodeFrame NotEnoughData or Error s32Ret=0x%x\n", s32Ret);
    }

    /* Get a packet when all inbuf consumed to decode a frame */
    if ((HI_FALSE == pstAdec->bPacketDecoder) && (HI_TRUE == pHAData->bInnerBufFlag))
    {
        if (0 == pstInnerBuf->s32Insize)
        {
            pHAData->enInBufState  = OWNED_BY_COMPONENT;
            pHAData->bInnerBufFlag = HI_FALSE;
        }
    }
    else
    {
        if (0 == pInBufHdr->nFilledLen)
        {
            pHAData->enInBufState  = OWNED_BY_COMPONENT;
        }
    }

    /* OMX_BUFFERFLAG_EOS PROCESS */
    if (pInBufHdr->nFlags & OMX_BUFFERFLAG_EOS)
    {
        OMXAACUpdateEOSState(pHAData, pInBufHdr, pOutBufHdr, s32Ret);
    }

    return s32Ret;
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

    eError = OMXAACInitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT0;
    }

    HA_AAC_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_AAC_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT1;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXAACGetParameter;
    pComponent->SetParameter = OMXAACSetParameter;
    pComponent->ComponentRoleEnum = OMXAACGetRoleEnum;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/aac";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingAAC;

    pHAData->CodecFrame = OMXAACProcessFrame;

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT2;
    }

    OAD_PRINT_STATE("AAC decoder init ok!\n");

    return OMX_ErrorNone;

INIT_EXIT2:
    OMX_HAADEC_DeInit(pHAData);
INIT_EXIT1:
    OMX_HAADEC_PrivDataDeInit(pHAData);
INIT_EXIT0:
    OMX_AUDIO_COMMON_DeInit(pHAData);

    return eError;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
