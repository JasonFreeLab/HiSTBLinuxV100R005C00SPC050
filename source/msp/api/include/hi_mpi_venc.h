/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name             :   hi_mpi_venc.h
  Version               :   Initial Draft
  Author                :   Hisilicon multimedia software group
  Created               :   2010/03/31
  Last Modified         :
  Description           :
  Function List         :
  History               :
  1.Date                :   2010/03/31
    Author              :   sdk
Modification            :   Created file
******************************************************************************/

#ifndef  __HI_MPI_VENC_H__
#define  __HI_MPI_VENC_H__

#include "hi_error_mpi.h"
#include "hi_unf_venc.h"
#include "drv_venc_ext.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define VENC_MAX_CHN_NUM 16

HI_S32 HI_MPI_VENC_Init(HI_VOID);
HI_S32 HI_MPI_VENC_DeInit(HI_VOID);
HI_S32 HI_MPI_VENC_SetAttr(HI_HANDLE hVencChn, const HI_UNF_VENC_CHN_ATTR_S *pstAttr);
HI_S32 HI_MPI_VENC_GetAttr(HI_HANDLE hVencChn, HI_UNF_VENC_CHN_ATTR_S *pstAttr);
HI_S32 HI_MPI_VENC_Create(HI_HANDLE *phVencChn, const HI_UNF_VENC_CHN_ATTR_S *pstAttr);
HI_S32 HI_MPI_VENC_Destroy(HI_HANDLE hVencChn);
HI_S32 HI_MPI_VENC_AttachInput(HI_HANDLE hVencChn, HI_HANDLE hSrc);
HI_S32 HI_MPI_VENC_DetachInput(HI_HANDLE hVencChn);
HI_S32 HI_MPI_VENC_AcquireStream(HI_HANDLE hVencChn, HI_UNF_VENC_STREAM_S *pstStream, HI_U32 u32BlockFlag);
HI_S32 HI_MPI_VENC_ReleaseStream(HI_HANDLE hVencChn, const HI_UNF_VENC_STREAM_S *pstStream);
HI_S32 HI_MPI_VENC_Start(HI_HANDLE hVencChn);
HI_S32 HI_MPI_VENC_Stop(HI_HANDLE hVencChn);

HI_S32 HI_MPI_VENC_QueueFrame(HI_HANDLE hVencChn,HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo);
HI_S32 HI_MPI_VENC_DequeueFrame(HI_HANDLE hVencChn,HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo);
//HI_S32 HI_MPI_VENC_GetFrame(HI_HANDLE hVencChn, HI_UNF_VI_BUF_S *pstFrame);
//HI_S32 HI_MPI_VENC_PutFrame(HI_HANDLE hVencChn, const HI_UNF_VI_BUF_S *pstFrame);
HI_S32 HI_MPI_VENC_RequestIFrame(HI_HANDLE hVencChn);
HI_S32 HI_MPI_VENC_SetSource(HI_HANDLE hVencChn, HI_DRV_VENC_SRC_HANDLE_S* pstSrc);
HI_S32 HI_MPI_VENC_GetCapability(HI_UNF_VENC_CAP_S *pstCapability);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__HI_MPI_VENC_H__
