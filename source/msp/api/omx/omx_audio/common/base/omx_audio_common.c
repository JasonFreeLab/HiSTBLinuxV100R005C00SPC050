#include "omx_audio_base.h"
#include "omx_audio_common.h"
#include "ha_adec.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define DEFAULT_OUT_CHANNEL       (2)
#define DEFAULT_OUT_SAMPLERATE    (48000)

#define OMX_AUD_INBUFFERS_SIZE    (65536)
#define OMX_AUD_OUTBUFFERS_SIZE   (8192)    // would change by differ decoder


static HI_VOID OMXAudioCommon_InitPcmParam(OMX_AUDIO_PARAM_PCMMODETYPE* pstPcmParam)
{
    OMX_CONF_INIT_STRUCT_PTR(pstPcmParam, OMX_AUDIO_PARAM_PCMMODETYPE);

    pstPcmParam->nChannels = DEFAULT_OUT_CHANNEL;
    pstPcmParam->nSamplingRate = DEFAULT_OUT_SAMPLERATE;
}

static HI_VOID OMXAudioCommon_InitPort(OMX_PARAM_PORTDEFINITIONTYPE* pstInPortDef, OMX_PARAM_PORTDEFINITIONTYPE* pstOutPortDef)
{
    // Initialize the audio parameters for input port
    OMX_CONF_INIT_STRUCT_PTR(pstInPortDef, OMX_PARAM_PORTDEFINITIONTYPE);
    pstInPortDef->eDir                    = OMX_DirInput;
    pstInPortDef->eDomain                 = OMX_PortDomainAudio;
    pstInPortDef->bEnabled                = OMX_TRUE;
    pstInPortDef->nPortIndex              = OMX_IN_PORT_IDX;
    pstInPortDef->bPopulated              = OMX_FALSE;
    pstInPortDef->nBufferSize             = OMX_AUD_INBUFFERS_SIZE;
    pstInPortDef->nBufferCountMin         = NUM_IN_BUFFERS;
    pstInPortDef->nBufferCountActual      = NUM_IN_BUFFERS;
    pstInPortDef->format.audio.eEncoding  = OMX_AUDIO_CodingUnused;
    pstInPortDef->format.audio.pDeprecated0 = HI_NULL;
    pstInPortDef->format.audio.bFlagErrorConcealment = OMX_FALSE;

    // Initialize the audio parameters for output port
    OMX_CONF_INIT_STRUCT_PTR(pstOutPortDef, OMX_PARAM_PORTDEFINITIONTYPE);
    pstOutPortDef->eDir                   = OMX_DirOutput;
    pstOutPortDef->eDomain                = OMX_PortDomainAudio;
    pstOutPortDef->bEnabled               = OMX_TRUE;
    pstOutPortDef->nPortIndex             = OMX_OUT_PORT_IDX;
    pstOutPortDef->bPopulated             = OMX_FALSE;
    pstOutPortDef->nBufferSize            = OMX_AUD_OUTBUFFERS_SIZE;
    pstOutPortDef->nBufferCountMin        = NUM_OUT_BUFFERS;
    pstOutPortDef->nBufferCountActual     = NUM_OUT_BUFFERS;
    pstOutPortDef->format.audio.eEncoding = OMX_AUDIO_CodingPCM;
    pstOutPortDef->format.audio.pDeprecated0 = "audio/linearpcm";
    pstOutPortDef->format.audio.bFlagErrorConcealment = OMX_FALSE;
}

static OMX_ERRORTYPE OMXAudioCommon_InitBufferList(BufferList* pstInBufList, BufferList* pstOutBufList)
{
    OMX_U32 nIndex;

    // Initialize the input buffer list.
    memset(pstInBufList, 0x0, sizeof(BufferList));
    pstInBufList->pBufHdr = (OMX_BUFFERHEADERTYPE**)OMX_OSAL_Malloc(sizeof(OMX_BUFFERHEADERTYPE*) * NUM_IN_BUFFERS);
    if (HI_NULL == pstInBufList->pBufHdr)
    {
        return OMX_ErrorInsufficientResources;
    }

    for (nIndex = 0; nIndex < NUM_IN_BUFFERS; nIndex++)
    {
        pstInBufList->pBufHdr[nIndex] = HI_NULL;
    }

    pstInBufList->eDir      = OMX_DirInput;
    pstInBufList->nListEnd  = -1;
    pstInBufList->nReadPos  = -1;
    pstInBufList->nWritePos = -1;

    // Initialize the output buffer list
    memset(pstOutBufList, 0x0, sizeof(BufferList));
    pstOutBufList->pBufHdr = (OMX_BUFFERHEADERTYPE**)OMX_OSAL_Malloc(sizeof(OMX_BUFFERHEADERTYPE*) * NUM_OUT_BUFFERS);
    if (HI_NULL == pstOutBufList->pBufHdr)
    {
        OMX_OSAL_Free(pstInBufList->pBufHdr);
        pstInBufList->pBufHdr = HI_NULL;
        return OMX_ErrorInsufficientResources;
    }

    for (nIndex = 0; nIndex < NUM_OUT_BUFFERS; nIndex++)
    {
        pstOutBufList->pBufHdr[nIndex] = HI_NULL;
    }

    pstOutBufList->eDir      = OMX_DirOutput;
    pstOutBufList->nListEnd  = -1;
    pstOutBufList->nReadPos  = -1;
    pstOutBufList->nWritePos = -1;

    return OMX_ErrorNone;
}

static HI_VOID OMXAudioCommon_DeInitBufferList(BufferList* pstInBufList, BufferList* pstOutBufList)
{
    if (pstOutBufList->pBufHdr)
    {
        OMX_OSAL_Free(pstOutBufList->pBufHdr);
        pstOutBufList->pBufHdr = HI_NULL;
    }

    if (pstInBufList->pBufHdr)
    {
        OMX_OSAL_Free(pstInBufList->pBufHdr);
        pstInBufList->pBufHdr = HI_NULL;
    }
}

static OMX_ERRORTYPE OMXAudioCommon_InitPipe(HI_AUDDATATYPE* pHAData)
{
    OMX_S32 eError;

    // Create the pipe used to send commands to the thread
    eError = pipe((HI_S32*)pHAData->cmdspipe);
    if (0 != eError)
    {
        return OMX_ErrorInsufficientResources;
    }

    // Create the pipe used to send data to the thread
    eError = pipe((HI_S32*)pHAData->datapipe);
    if (0 != eError)
    {
        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

static HI_VOID OMXAudioCommon_DeInitPipe(HI_AUDDATATYPE* pHAData)
{
    // close the pipe handles
    close(pHAData->cmdspipe[PIPE_READ]);
    close(pHAData->cmdspipe[PIPE_WRITE]);
    close(pHAData->datapipe[PIPE_READ]);
    close(pHAData->datapipe[PIPE_WRITE]);
}

static HI_VOID OMXAudioCommon_SetComponentFunc(OMX_COMPONENTTYPE* pComponent)
{
    // Fill in function pointers
    pComponent->UseBuffer              = HI_OMX_CODEC_UseBuffer;
    pComponent->FreeBuffer             = HI_OMX_CODEC_FreeBuffer;
    pComponent->SetCallbacks           = HI_OMX_CODEC_SetCallbacks;
    pComponent->AllocateBuffer         = HI_OMX_CODEC_AllocateBuffer;
    pComponent->FillThisBuffer         = HI_OMX_CODEC_FillThisBuffer;
    pComponent->EmptyThisBuffer        = HI_OMX_CODEC_EmptyThisBuffer;
    pComponent->ComponentDeInit        = HI_OMX_CODEC_ComponentDeInit;
    pComponent->SendCommand            = HI_OMX_CODEC_SendCommand;
    pComponent->GetState               = HI_OMX_CODEC_GetState;
    pComponent->GetConfig              = StubbedGetConfig;
    pComponent->SetConfig              = StubbedSetConfig;
    pComponent->UseEGLImage            = StubbedUseEGLImage;
    pComponent->GetExtensionIndex      = StubbedGetExtensionIndex;
    pComponent->GetComponentVersion    = StubbedGetComponentVersion;
    pComponent->ComponentTunnelRequest = StubbedComponentTunnelRequest;
}

static HI_VOID OMXAudioCommon_SetMsgPriority(OMX_PRIORITYMGMTTYPE* pstMsgPriority)
{
    OMX_CONF_INIT_STRUCT_PTR(pstMsgPriority, OMX_PRIORITYMGMTTYPE);
}


HI_VOID OMX_AUDIO_COMMON_DeInit(HI_AUDDATATYPE* pAudioData)
{
    OMXAudioCommon_DeInitPipe(pAudioData);
    OMXAudioCommon_DeInitBufferList(&pAudioData->sInBufList, &pAudioData->sOutBufList);

    OMX_OSAL_Free(pAudioData);
}

OMX_ERRORTYPE OMX_AUDIO_COMMON_Init(OMX_HANDLETYPE Handle, HI_AUDDATATYPE** ppAudioData)
{
    OMX_ERRORTYPE eError;
    HI_AUDDATATYPE* pHAData = HI_NULL;
    OMX_COMPONENTTYPE* pComponent = HI_NULL;

    OMX_CONF_CHECK_NULLPTR(Handle);
    OMX_CONF_CHECK_NULLPTR(ppAudioData);

    // Create private component data
    pHAData = (HI_AUDDATATYPE*)OMX_OSAL_Malloc(sizeof(HI_AUDDATATYPE));
    if (HI_NULL == pHAData)
    {
        return OMX_ErrorInsufficientResources;
    }

    memset(pHAData, 0x0, sizeof(HI_AUDDATATYPE));

    OMXAudioCommon_InitPort(&pHAData->sInPortDef, &pHAData->sOutPortDef);
    OMXAudioCommon_InitPcmParam(&pHAData->sPcm);

    eError = OMXAudioCommon_InitPipe(pHAData);
    if (OMX_ErrorNone != eError)
    {
        goto ERR_EXIT;
    }

    eError = OMXAudioCommon_InitBufferList(&pHAData->sInBufList, &pHAData->sOutBufList);
    if (OMX_ErrorNone != eError)
    {
        OMXAudioCommon_DeInitPipe(pHAData);
        goto ERR_EXIT;
    }

    OMXAudioCommon_SetMsgPriority(&pHAData->sPriorityMgmt);

    pComponent = (OMX_COMPONENTTYPE*)Handle;
    pComponent->pComponentPrivate = (OMX_PTR)pHAData;
    OMXAudioCommon_SetComponentFunc(pComponent);

    pHAData->state = OMX_StateLoaded;
    pHAData->hSelf = Handle;
    *ppAudioData   = pHAData;

    return OMX_ErrorNone;

ERR_EXIT:
    OMX_OSAL_Free(pHAData);

    return eError;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

