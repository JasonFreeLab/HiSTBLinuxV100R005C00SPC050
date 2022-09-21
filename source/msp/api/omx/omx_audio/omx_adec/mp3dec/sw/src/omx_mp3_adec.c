/*=================================================

Open MAX   Component: Hisi Audio Decoder
This module contains
File:    OMX_MP3_Adec.c
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
#include "HA.AUDIO.MP3.decode.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef ANDROID
#undef  LOG_TAG
#define LOG_TAG  "HIOMX_ADEC_MP3"
#endif


/* defination related to mp3 decoder */
#define AUDIO_DEC_MP3_ROLE   "audio_decoder.mp3"
#define HA_MP3_LIB_NAME      "libHA.AUDIO.MP3.decode.so"


/*
 *  Functions
 */
static OMX_ERRORTYPE OMXMP3InitPrivData(HI_AUDDATATYPE* pHAData)
{
    // Create private codec Param
    pHAData->pCodecParam = (OMX_AUDIO_PARAM_MP3TYPE*)OMX_OSAL_Malloc(sizeof(OMX_AUDIO_PARAM_MP3TYPE));
    if (HI_NULL == pHAData->pCodecParam)
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "pCodecData OMX_OSAL_Malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData->pCodecParam, 0x0, sizeof(OMX_AUDIO_PARAM_MP3TYPE));

    OMX_CONF_INIT_STRUCT_PTR((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam, OMX_AUDIO_PARAM_MP3TYPE);
    //Default values for Mp3 audio param port
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->nPortIndex      = 0x0;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->nChannels       = 2;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->nBitRate        = 0;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->nSampleRate     = 44100;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->nAudioBandWidth = 0x0;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->eChannelMode    = OMX_AUDIO_ChannelModeStereo;
    ((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam)->eFormat         = OMX_AUDIO_MP3StreamFormatMP1Layer3;

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE OMXMP3GetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

        case OMX_IndexParamAudioMp3:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioMp3\n", __FUNCTION__);
            memcpy(pParamStructure, (OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam, sizeof(OMX_AUDIO_PARAM_MP3TYPE));
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

static OMX_ERRORTYPE OMXMP3SetParameter(OMX_IN OMX_HANDLETYPE hComponent,
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

            if (strncmp((const char*)roleParams->cRole, "audio_decoder.mp3", OMX_MAX_STRINGNAME_SIZE - 1)
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

        case OMX_IndexParamAudioMp3:
            OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "%s -> OMX_IndexParamAudioMp3\n", __FUNCTION__);
            memcpy((OMX_AUDIO_PARAM_MP3TYPE*)pHAData->pCodecParam, pParamStructure,
                   sizeof(OMX_AUDIO_PARAM_MP3TYPE));
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


static OMX_ERRORTYPE OMXMP3GetRoleEnum(OMX_IN OMX_HANDLETYPE hComponent, OMX_OUT OMX_U8* cRole, OMX_IN OMX_U32 nIndex)
{
    HA_UNUSED_PARAMETER(hComponent);

    if (nIndex == 0)
    {
        strncpy((char*)cRole, AUDIO_DEC_MP3_ROLE, sizeof(AUDIO_DEC_MP3_ROLE));
    }
    else
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s -> Fail: Can not get HI_OMX_MP3_ComponentRoleEnum!\n", __FUNCTION__);
        return OMX_ErrorUnsupportedIndex;
    }

    return OMX_ErrorNone;
}

#ifdef ANDROID
static HI_VOID OMXMP3UpdateEOSState(HI_AUDDATATYPE* pHAData, OMX_BUFFERHEADERTYPE* pInBufHdr, OMX_BUFFERHEADERTYPE* pOutBufHdr, HI_S32 s32Ret)
{
    HA_ADEC_S*        pstAdec     = &pHAData->stAdec;
    HA_INTERNALBUF_S* pstInnerBuf = &pstAdec->sInternalBuf;

    if ((HI_FALSE == pstAdec->bPacketDecoder) && (HI_TRUE == pHAData->bInnerBufFlag))
    {
        if (HA_ErrorNone != s32Ret)
        {
            /* Flush Inner Buffer */
            if (0 != pstInnerBuf->s32Insize)
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
                if (HI_FALSE == pHAData->bFirstFrame)
                {
                    // pad the end of the stream with 529 samples, since that many samples
                    // were trimmed off the beginning when decoding started
                    pOutBufHdr->nFilledLen = 529 * pHAData->sPcm.nChannels * sizeof(HI_S16);
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
    }
}

static HI_S32 OMXMP3ProcessFrame(HI_VOID* pHAState, OMX_BUFFERHEADERTYPE* pInBufHdr, OMX_BUFFERHEADERTYPE* pOutBufHdr)
{
    HI_S32 s32Ret = HA_ErrorNone;
    HI_AUDDATATYPE* pHAData = (HI_AUDDATATYPE*)pHAState;
    HA_ADEC_S* pstAdec  = &pHAData->stAdec;
    HA_INTERNALBUF_S* pstInnerBuf = &pstAdec->sInternalBuf;
    HI_HADECODE_INPACKET_S avpkt;
    HI_HADECODE_OUTPUT_S   avOut;

    //When mInputBufferCnt=0, do some config setting
    if (0 == pHAData->mInputBufferCnt)
    {
        HA_MP3_CHECKONESYNC_FLAG_S  stConfigData;
        memset(&stConfigData, 0, sizeof(HA_MP3_CHECKONESYNC_FLAG_S));
        stConfigData.enCmd = HA_CODEC_SET_MP3_CHECKONESYNC_CMD;
        stConfigData.bCheckOneSync = HI_TRUE;

        s32Ret = OMX_HAADEC_SetConfig(pHAData, &stConfigData);
        if (HI_SUCCESS != s32Ret)
        {
            OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "OMX_HAADEC_SetConfig failed 0x%x", s32Ret);
            // not return avoid cannot comsume inbuf that result in halting playback
        }
    }

    pHAData->mInputBufferCnt++;

    avOut.ps32PcmOutBuf  = (HI_S32*)pOutBufHdr->pBuffer;

    /* Get the time stamp */
    if ((HI_TRUE == pHAData->bNewPacketIn) && pInBufHdr->nFilledLen)
    {
        pHAData->bNewPacketIn  = HI_FALSE;
        if (0 <= pInBufHdr->nTimeStamp)
        {
            pHAData->mAnchorTimeUs = pInBufHdr->nTimeStamp;
        }
    }

    pOutBufHdr->nFlags        = pInBufHdr->nFlags & (~OMX_BUFFERFLAG_EOS);
    pHAData->enInBufState     = OWNED_BY_US;

    /* Begin to decode */
    s32Ret = OMX_HAADEC_DecodeFrame(pHAData, &avpkt, &avOut, pInBufHdr);
    if (s32Ret == HA_ErrorNone)
    {
        if (HI_TRUE == pHAData->bFirstFrame)
        {
            pHAData->bFirstFrame = HI_FALSE;
            // The decoder delay is 529 samples, so trim that many samples off
            // the start of the first output buffer. This essentially makes this
            // decoder have zero delay, which the rest of the pipeline assumes.
            pOutBufHdr->nOffset    = 529 * avOut.u32OutChannels * sizeof(HI_S16);
            pOutBufHdr->nFilledLen = avOut.u32PcmOutSamplesPerFrame * sizeof(HI_S16) * avOut.u32OutChannels - pOutBufHdr->nOffset;
        }
        else
        {
            pOutBufHdr->nOffset    = 0;
            pOutBufHdr->nFilledLen = avOut.u32PcmOutSamplesPerFrame * sizeof(HI_S16) * avOut.u32OutChannels;
        }

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

        OMX_OSAL_Trace(OMX_OSAL_TRACE_DEBUG, "ADECDecodeMp3Frame Success\n");
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
        OMXMP3UpdateEOSState(pHAData, pInBufHdr, pOutBufHdr, s32Ret);
    }

    return s32Ret;
}
#endif
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

    eError = OMXMP3InitPrivData(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto INIT_EXIT;
    }

    HA_MP3_DecGetDefalutOpenParam(&pHAData->stAdec.sOpenPram);

    s32Ret = OMX_HAADEC_Init(pHAData, HA_MP3_LIB_NAME);
    if (HI_SUCCESS != s32Ret)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    // Fill in function pointers
    pComponent = (OMX_COMPONENTTYPE*)pHandle;
    pComponent->GetParameter = OMXMP3GetParameter;
    pComponent->SetParameter = OMXMP3SetParameter;
    pComponent->ComponentRoleEnum = OMXMP3GetRoleEnum;

    pHAData->sInPortDef.format.audio.pDeprecated0 = (OMX_PTR)"audio/mpeg";
    pHAData->sInPortDef.format.audio.eEncoding = OMX_AUDIO_CodingMP3;

#ifdef ANDROID
    //For Android CTS
    pHAData->CodecFrame = OMXMP3ProcessFrame;
#else
    pHAData->CodecFrame = OMX_HAADEC_ProcessFrame;
#endif

    // Create the component thread
    s32Ret = pthread_create(&pHAData->thread_id, HI_NULL, HI_OMX_ADEC_ComponentThread, pHAData);
    if (s32Ret || !pHAData->thread_id)
    {
        eError = OMX_ErrorInsufficientResources;
        goto INIT_EXIT;
    }

    OAD_PRINT_STATE("MP3 decoder init ok!\n");

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

