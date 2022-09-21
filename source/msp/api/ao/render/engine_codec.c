/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: engine_codec.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"
#include "engine_codec.h"
#include "engine_codec_private.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define HA_DECODEC_ENTRY       "ha_audio_decode_entry"
#define HA_DOLBY_MS12_LIB_NAME "libHA.AUDIO.DOLBYMS12.decode.so"

#define HACodecCheckDecType(enType) \
    do{ \
        if ((HA_AUDIO_ID_MS12_AAC != enType) && (HA_AUDIO_ID_MS12_DDP != enType)) \
        { \
            HI_ERR_AO("Invalid CodeID(0x%x)!\n", enType); \
            return HI_ERR_AO_INVALID_ID; \
        } \
    } while(0)


static HI_S32 HACodecCheckEntry(const HI_HA_DECODE_S* pEntry)
{
    trace();

    CHECK_AO_NULL_PTR(pEntry->DecInit);
    CHECK_AO_NULL_PTR(pEntry->DecDeInit);
    CHECK_AO_NULL_PTR(pEntry->DecSetConfig);
    CHECK_AO_NULL_PTR(pEntry->DecGetMaxPcmOutSize);
    CHECK_AO_NULL_PTR(pEntry->DecGetMaxBitsOutSize);

    return  HI_SUCCESS;
}

static HI_S32 HADecLoadLib(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;
    HI_VOID* pDllModule;
    HI_HA_DECODE_S* pEntry;

    trace();

#ifdef ANDROID
    pDllModule = dlopen(HA_DOLBY_MS12_LIB_NAME, RTLD_LAZY | RTLD_GLOBAL);
#else
    pDllModule = dlopen(HA_DOLBY_MS12_LIB_NAME, RTLD_LAZY | RTLD_GLOBAL | RTLD_DEEPBIND);
#endif
    if (HI_NULL == pDllModule)
    {
        HI_ERR_AO("dlopen %s failed(%s)\n", HA_DOLBY_MS12_LIB_NAME, dlerror());
        return HI_FAILURE;
    }

    pEntry = (HI_HA_DECODE_S*)dlsym(pDllModule, HA_DECODEC_ENTRY);
    if (HI_NULL == pEntry)
    {
        HI_ERR_AO("dlsym %s failed(%s)\n", HA_DOLBY_MS12_LIB_NAME, dlerror());
        goto ERR_DLOPEN;
    }

    s32Ret = HACodecCheckEntry(pEntry);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodecCheckEntry failed(0x%x)\n", s32Ret);
        goto ERR_DLOPEN;
    }

    pstCodec->pEntry = pEntry;
    pstCodec->pDllModule = pDllModule;

    return HI_SUCCESS;

ERR_DLOPEN:
    (HI_VOID)dlclose(pDllModule);

    return HI_FAILURE;
}

static HI_VOID HADecUnLoadLib(ENGINE_CODEC_S* pstCodec)
{
    (HI_VOID)dlclose(pstCodec->pDllModule);
}

static HI_BOOL HACodecCheckIsRenderLibInited(ENGINE_CODEC_S* pstCodec)
{
	return pstCodec->bLibInited;
}

static HI_S32 HACodecInit(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;

    trace();

    s32Ret = pstCodec->pEntry->DecInit(&pstCodec->hDecoder, &pstRenderAttr->stDecodeParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    pstCodec->enCodecID = pstRenderAttr->enType;

    return HI_SUCCESS;
}

static HI_S32 HaCodecRegistProc(ENGINE_CODEC_S* pstCodec)
{
    trace();

    pstCodec->pstMs12Proc->enCmd = HA_CODEC_MS12_SET_PROCINFO_CMD;

    return pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pstCodec->pstMs12Proc);
}

static HI_VOID HaCodecUnRegistProc(ENGINE_CODEC_S* pstCodec)
{
    trace();
}

static HI_S32 HACodecInit_Default(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;
    DOLBYMS12_CODEC_OPENCONFIG_S stMs12Cfg;
    HI_HADECODE_OPENPARAM_S stOpenParam;

    trace();

    HA_DOLBYMS12_CodecGetDefaultOpenConfig(&stMs12Cfg);
    HA_DOLBYMS12_CodecGetDefaultOpenParam(&stOpenParam, &stMs12Cfg);

    s32Ret = pstCodec->pEntry->DecInit(&pstCodec->hDecoder, &stOpenParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    pstCodec->enCodecID = HA_AUDIO_ID_MS12_DDP;

    return HI_SUCCESS;
}

static HI_S32 HACodecDeInit(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;

    trace();

    s32Ret = pstCodec->pEntry->DecDeInit(pstCodec->hDecoder);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecDeInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 HACodecGetCapability(ENGINE_CODEC_S* pstCodec, HI_U32* pu32Capability)
{
    HI_S32 s32Ret;
    HA_MS12_GET_CAPABILITY_S stCapability;

    trace();

    stCapability.enCmd = HA_CODEC_MS12_GET_CAPABILITY_CMD;

    s32Ret = pstCodec->pEntry->DecSetConfig(&pstCodec->hDecoder, &stCapability);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("GetCapability failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *pu32Capability = stCapability.u32Capability;

    return HI_SUCCESS;
}

static HI_S32 HACodecCtlCommand(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;
    HA_MS12_SET_STREAM_INDEX_S stStreamIndex;

    trace();

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_AO("HACodecCtlCommand render lib is not inited\n");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    stStreamIndex.enCmd = HA_CODEC_MS12_SET_STREAM_INDEX_CMD;
    stStreamIndex.u32Index = enSourceID;

    (HI_VOID)pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stStreamIndex);

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

static HI_S32 HACodecSetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;

    trace();

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_AO("render lib is not inited\n");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

static HI_S32 HACodecGetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;

    trace();

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_AO("render lib is not inited\n");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

HI_BOOL HACodec_CheckIsRenderLibLoaded(ENGINE_CODEC_S* pstCodec)
{
    return HACodecCheckIsRenderLibInited(pstCodec);
}

HI_S32 HACodec_Init(ENGINE_CODEC_S** ppstCodec)
{
    ENGINE_CODEC_S* pstCodec;
    trace();

    pstCodec = (ENGINE_CODEC_S*)malloc(sizeof(ENGINE_CODEC_S));
    if (HI_NULL == pstCodec)
    {
        HI_ERR_AO("HACodec malloc failed!\n");
        return HI_FAILURE;
    }
    memset(pstCodec, 0, sizeof(ENGINE_CODEC_S));

    pstCodec->pstMs12Proc = (HA_MS12_SET_PROCINFO_S*)malloc(sizeof(HA_MS12_SET_PROCINFO_S));
    if (HI_NULL == pstCodec->pstMs12Proc)
    {
        HI_ERR_AO("HAMs12Proc malloc failed!\n");
        free(pstCodec);
        return HI_FAILURE;
    }
    memset(pstCodec->pstMs12Proc, 0, sizeof(HA_MS12_SET_PROCINFO_S));

    *ppstCodec = pstCodec;

    return HI_SUCCESS;
}

HI_VOID HACodec_DeInit(ENGINE_CODEC_S* pstCodec)
{
    trace();

    if (HI_NULL != pstCodec)
    {
        if (HI_NULL != pstCodec->pstMs12Proc)
        {
            free(pstCodec->pstMs12Proc);
        }
        free(pstCodec);
    }
}

HI_S32 HACodec_LoadRenderLib_Default(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;

    trace();

    if (HI_TRUE == pstCodec->bLibInited)
    {
        HI_WARN_AO("Render lib already load\n");
        return HI_SUCCESS;
    }

    s32Ret = HADecLoadLib(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecLoadLib failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HACodecInit_Default(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecInit failed(0x%x)\n", s32Ret);  //TODO unload lib
        return s32Ret;
    }

#ifdef RENDER_DEBUG_SUPPORT
    s32Ret = HaCodecRegistProc(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HaCodecRegistProc default failed(0x%x)\n", s32Ret);
    }
#endif

    pstCodec->bLibInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 HACodec_LoadRenderLib(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;

    trace();

    HACodecCheckDecType(pstRenderAttr->enType);

    if (HI_FALSE == pstCodec->bLibInited)
    {
        s32Ret = HADecLoadLib(pstCodec);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("HADecLoadLib failed(0x%x)\n", s32Ret);
            return s32Ret;
        }
    }

    if (pstCodec->enCodecID == pstRenderAttr->enType)
    {
        pstCodec->bLibInited = HI_TRUE;
        HI_WARN_AO("The same codec type(0x%x)\n", pstRenderAttr->enType);
        return HI_SUCCESS;
    }

    if (HI_TRUE == pstCodec->bLibInited)
    {
        s32Ret = HACodecDeInit(pstCodec);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("HADecDeInit failed(0x%x)\n", s32Ret);  //TODO unload lib
            return s32Ret;
        }

        pstCodec->bLibInited = HI_FALSE;
    }

    s32Ret = HACodecInit(pstCodec, pstRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecInit failed(0x%x)\n", s32Ret);  //TODO unload lib
        return s32Ret;
    }

    s32Ret = HaCodecRegistProc(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HaCodecRegistProc failed(0x%x)\n", s32Ret);
    }

    pstCodec->bLibInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID HACodec_UnLoadRenderLib(ENGINE_CODEC_S* pstCodec)
{
    HaCodecUnRegistProc(pstCodec);

    if (HI_TRUE == pstCodec->bLibInited)
    {
        HACodecDeInit(pstCodec);
        HADecUnLoadLib(pstCodec);
    }

    pstCodec->pEntry = HI_NULL;
    pstCodec->pDllModule = HI_NULL;
    pstCodec->bLibInited = HI_FALSE;
}

HI_S32 HACodec_GetRenderLibCapability(HI_U32* pu32Capability)
{
    HI_S32 s32Ret;
    ENGINE_CODEC_S stCodec;

    trace();

    memset(&stCodec, 0, sizeof(ENGINE_CODEC_S));

    s32Ret = HADecLoadLib(&stCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecLoadLib failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HACodecGetCapability(&stCodec, pu32Capability);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodecGetCapability failed(0x%x)\n", s32Ret);
    }

    HADecUnLoadLib(&stCodec);

    return s32Ret;
}

HI_S32 HACodec_InitDecodeInfo(ENGINE_CODEC_S* pstCodec, HA_MS12_DECODE_STREAM_S* pstDecodeStream)
{
    HI_S32 s32Ret;
    HI_U32 u32Index = 0;
    HI_U32 u32TotalSize = 0;
    HI_U32 u32InpkgSize = 0;
    HI_U32 u32OutputSize = 0;
    HI_U32 u32MallocPcmSize = 0;
    HI_U32 u32MallocBitSize = 0;
    HI_U8* pu8Memory = HI_NULL;

    trace();

    CHECK_AO_NULL_PTR(pstDecodeStream);

    u32InpkgSize = sizeof(HI_HADECODE_INPACKET_S);
    u32OutputSize = sizeof(HI_HADECODE_OUTPUT_S);

    s32Ret = pstCodec->pEntry->DecGetMaxPcmOutSize(pstCodec->hDecoder, &u32MallocPcmSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Hacoder DecGetMaxPcmOutSize failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = pstCodec->pEntry->DecGetMaxBitsOutSize(pstCodec->hDecoder, &u32MallocBitSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Hacoder DecGetMaxBitsOutSize failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    u32TotalSize = u32InpkgSize * SOURCE_ID_BUTT + u32OutputSize + u32MallocPcmSize + u32MallocBitSize;

    pstCodec->pAdecIOMem = (HI_VOID*)malloc(u32TotalSize);
    if (HI_NULL == pstCodec->pAdecIOMem)
    {
        HI_ERR_AO("Malloc pAdecIOMem failed\n");
        return HI_FAILURE;
    }

    memset(pstCodec->pAdecIOMem, 0, u32TotalSize);
    pu8Memory = pstCodec->pAdecIOMem;

    memset(pstDecodeStream, 0, sizeof(HA_MS12_DECODE_STREAM_S));

    for (u32Index = 0; u32Index < SOURCE_ID_BUTT; u32Index++)
    {
        pstDecodeStream->stStream.stInput.pstInPack[u32Index] = (HI_HADECODE_INPACKET_S*)pu8Memory;
        pu8Memory += u32InpkgSize;
    }

    pstDecodeStream->stStream.stOutput.pstOutput = (HI_HADECODE_OUTPUT_S*)pu8Memory;
    pu8Memory += u32OutputSize;

    pstDecodeStream->stStream.stOutput.pstOutput->ps32PcmOutBuf = (HI_S32*)pu8Memory;
    pu8Memory += u32MallocPcmSize;

    pstDecodeStream->stStream.stOutput.pstOutput->ps32BitsOutBuf = (HI_S32*)pu8Memory;

    return HI_SUCCESS;
}

HI_VOID HACodec_DeInitDecodeInfo(ENGINE_CODEC_S* pstCodec)
{
    if (HI_NULL != pstCodec->pAdecIOMem)
    {
        free(pstCodec->pAdecIOMem);
        pstCodec->pAdecIOMem = HI_NULL;
    }
}

HI_S32 HACodec_Render(ENGINE_CODEC_S* pstCodec, HI_VOID* pstConfigStructure)
{
    CHANNEL_TRACE();

    return pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pstConfigStructure);
}

HI_S32 HACodec_CtlCommand(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_VOID* pCmdData)
{
    return HACodecCtlCommand(pstCodec, enSourceID, pCmdData);
}

HI_S32 HACodec_SetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    return HACodecSetCmd(pstCodec, pCmdData);
}

HI_S32 HACodec_GetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    return HACodecGetCmd(pstCodec, pCmdData);
}

HI_S32 HACodec_EnableDecoder(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable)
{
    HA_MS12_DECODE_ENABLE_S stDecodeEnable;

    trace();

    stDecodeEnable.enCmd = HA_CODEC_MS12_ENABLE_DECODE_CMD;
    stDecodeEnable.bEnable = bEnable;

    SYNC_PRINTF("HADecEnableDecoder bEnableDecoder = %d\n", bEnable);

    return HACodecCtlCommand(pstCodec, enSourceID, &stDecodeEnable);
}

HI_S32 HACodec_EnableMixer(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable)
{
    HA_MS12_MIX_ENABLE_S stMixerEnable;

    trace();

    stMixerEnable.enCmd = HA_CODEC_MS12_ENABLE_MIX_CMD;
    stMixerEnable.bEnable = bEnable;

    SYNC_PRINTF("HADecEnableMixer bEnableMixer = %d\n", bEnable);

    return HACodecCtlCommand(pstCodec, enSourceID, &stMixerEnable);
}

HI_S32 HACodec_DropPts(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_S32 s32DropPts)
{
    HA_MS12_ADJUST_STRATEGY_S stStrategyAdjust;

    trace();

    stStrategyAdjust.enCmd = HA_CODEC_MS12_ADJUST_STRATEGY_CMD;
    stStrategyAdjust.s32AdjustTime = s32DropPts > 0 ? s32DropPts : 0;

    SYNC_PRINTF("HADecDropPts s32AdjustTime = %d\n", s32DropPts);

    return HACodecCtlCommand(pstCodec, enSourceID, &stStrategyAdjust);
}

HI_S32 HACodec_DropFrame(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_U32 u32FrameCnt)
{
    HA_MS12_DROP_FRAME_S stDropFrame;

    trace();

    stDropFrame.enCmd = HA_CODEC_MS12_DROP_FRAME_CMD;
    stDropFrame.u32FrameCnt = u32FrameCnt;

    SYNC_PRINTF("HADecDropFrame u32FrameCnt = %d\n", u32FrameCnt);

    return HACodecCtlCommand(pstCodec, enSourceID, &stDropFrame);
}

HI_VOID HACodec_UpdateDataStatus(ENGINE_CODEC_S* pstCodec, HI_BOOL* pbStreamDataEnough)
{
    memcpy(pstCodec->bDataAvailable, pbStreamDataEnough, sizeof(pstCodec->bDataAvailable));
}

HI_BOOL HACodec_CheckIsDataAvailable(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID)
{
    return pstCodec->bDataAvailable[enSourceID];
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
