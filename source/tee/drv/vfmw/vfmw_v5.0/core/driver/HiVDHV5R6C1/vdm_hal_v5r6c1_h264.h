#ifndef __VDM_HAL_V5R6C1_H264_H__
#define __VDM_HAL_V5R6C1_H264_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 H264HAL_V5R6C1_InitHal(VDMHAL_HWMEM_S *pHwMem);
SINT32 H264HAL_V5R6C1_StartDec(H264_DEC_PIC_PARAM_S *pParam, SINT32 VdhId, VOID *pTask);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_H264_H__
