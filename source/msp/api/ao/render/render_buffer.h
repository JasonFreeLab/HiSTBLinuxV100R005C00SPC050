/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_buffer.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_BUFFER_H__
#define  __RENDER_BUFFER_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define RBUFFER_ERR_BUFFER_FULL (0x80000001)

HI_S32 RENDER_Buffer_Init(HI_VOID** phHandle, HI_U32 u32BufferSize, HI_VOID* pExtOutBuf);

HI_S32 RENDER_Buffer_Get(HI_VOID* handle, HI_U32 u32RequestSize, HI_U8** ppu8Data);

HI_S32 RENDER_Buffer_Put(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data);

HI_U32 RENDER_Buffer_Acquire(HI_VOID* handle, HI_U32 u32DataSize, HI_U8** ppu8Data);

HI_S32 RENDER_Buffer_Release(HI_VOID* handle, HI_U32 u32DataSize);

HI_S32 RENDER_Buffer_Enquire(HI_VOID* handle, HI_U32 *pu32UsedSize, HI_U32 *pu32TotalSize);

HI_S32 RENDER_Buffer_Send(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data);

HI_S32 RENDER_Buffer_Reset(HI_VOID* handle);

HI_S32 RENDER_Buffer_DeInit(HI_VOID* handle);

HI_S32 RENDER_Buffer_GetDataSize(HI_VOID* handle, HI_S32* ps32BufSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
