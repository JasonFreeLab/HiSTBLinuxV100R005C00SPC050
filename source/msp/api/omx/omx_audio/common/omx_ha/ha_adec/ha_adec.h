/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : ha_adec.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HA_ADEC_H__
#define __HA_ADEC_H__

#include <OMX_Core.h>
#include "hi_type.h"
#include "omx_audio_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32      OMX_HAADEC_Init(HI_AUDDATATYPE* pHAData, const HI_CHAR* pszDecDllName);
HI_VOID     OMX_HAADEC_DeInit(HI_AUDDATATYPE* pHAData);
HI_VOID     OMX_HAADEC_PrivDataDeInit(HI_AUDDATATYPE* pHAData);
HI_S32      OMX_HAADEC_SetConfig(HI_AUDDATATYPE* pHAData, HI_VOID *pstConfigStructure);
HI_S32      OMX_HAADEC_ProcessFrame(HI_VOID* pHAState, OMX_BUFFERHEADERTYPE* pInBufHdr, OMX_BUFFERHEADERTYPE* pOutBufHdr);
HI_VOID     OMX_HAADEC_FlushInnerState(HI_AUDDATATYPE* pHAData);
HI_S32      OMX_HAADEC_DecodeFrame(HI_AUDDATATYPE* pHAData, HI_HADECODE_INPACKET_S* avpkt, HI_HADECODE_OUTPUT_S* avOut, OMX_BUFFERHEADERTYPE* pInBufHdr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HA_ADEC_H__ */
