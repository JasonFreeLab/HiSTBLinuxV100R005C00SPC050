/*****************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_aenc.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01      2009-11-24   z40717     NULL         Create this file.
*
*****************************************************************************/
#include "hi_type.h"
#include "hi_drv_aenc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define AENCGetRealChn(hAdec) do {hAenc = hAenc & 0xffff;} while (0)

HI_S32 HI_MPI_AENC_Init(HI_VOID)
{
    return AENC_Init();
}

HI_S32 HI_MPI_AENC_RegisterEncoder(const HI_CHAR* pszCodecDllName)
{
    return AENC_RegisterEncoder(pszCodecDllName);
}

HI_S32 HI_MPI_AENC_DeInit(HI_VOID)
{
    return AENC_DeInit();
}

HI_S32 HI_MPI_AENC_Open(HI_HANDLE* phAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    HI_S32 s32Ret;

    s32Ret = AENC_Open(phAenc, pstAencAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENC_Open failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *phAenc = *phAenc | (HI_ID_AENC << 16);

    return s32Ret;
}

HI_S32 HI_MPI_AENC_Close(HI_HANDLE hAenc)
{
    AENCGetRealChn(hAenc);
    return AENC_Close(hAenc);
}

HI_S32 HI_MPI_AENC_SendBuffer(HI_U32 hAenc, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    AENCGetRealChn(hAenc);
    return AENC_SendBuffer(hAenc, pstAOFrame);
}

HI_S32 HI_MPI_AENC_ReceiveStream(HI_HANDLE hAenc, AENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs)
{
    AENCGetRealChn(hAenc);
    return AENC_ReceiveStream(hAenc, pstStream, u32TimeoutMs);
}

HI_S32 HI_MPI_AENC_ReleaseStream(HI_HANDLE hAenc, const AENC_STREAM_S* pstStream)
{
    AENCGetRealChn(hAenc);
    return AENC_ReleaseStream(hAenc, pstStream);
}

HI_S32 HI_MPI_AENC_SetConfigEncoder(HI_HANDLE hAenc, HI_VOID* pstConfigStructure)
{
    AENCGetRealChn(hAenc);
    return AENC_SetConfigEncoder(hAenc, pstConfigStructure);
}

HI_S32 HI_MPI_AENC_SetEnable(HI_HANDLE hAenc, HI_BOOL bEnable)
{
    AENCGetRealChn(hAenc);
    return AENC_SetEnable(hAenc, bEnable);
}

HI_S32 HI_MPI_AENC_AttachInput(HI_HANDLE hAenc, HI_HANDLE hSource)
{
    HI_S32 s32Ret;

    AENCGetRealChn(hAenc);
    s32Ret = AENC_AttachInput(hAenc, hSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENC_AttachInput failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return AENC_SetEnable(hAenc, HI_TRUE);
}

HI_S32 HI_MPI_AENC_GetAttachSrc(HI_HANDLE hAenc, HI_HANDLE* hSrc)
{
    AENCGetRealChn(hAenc);

    return AENC_GetAttachSrc(hAenc, hSrc);
}

HI_S32 HI_MPI_AENC_DetachInput(HI_HANDLE hAenc)
{
    HI_S32 s32Ret;

    AENCGetRealChn(hAenc);
    s32Ret = AENC_DetachInput(hAenc);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENC_DetachInput failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return AENC_SetEnable(hAenc, HI_FALSE);
}

HI_S32 HI_MPI_AENC_SetAttr(HI_HANDLE hAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    AENCGetRealChn(hAenc);
    return AENC_SetAttr(hAenc, pstAencAttr);
}

HI_S32 HI_MPI_AENC_GetAttr(HI_HANDLE hAenc, HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    AENCGetRealChn(hAenc);
    return AENC_GetAttr(hAenc, pstAencAttr);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
