#ifndef __VDM_HAL_V4R3C1__HEVC_H__
#define __VDM_HAL_V4R3C1__HEVC_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 HEVCHAL_V4R3C1_InitHal(VDMHAL_HWMEM_S *pHwMem);
SINT32 HEVCHAL_V4R3C1_StartDec(HEVC_DEC_PIC_PARAM_S *pParam, SINT32 VdhId, VOID *pTask);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_HEVC_H__
