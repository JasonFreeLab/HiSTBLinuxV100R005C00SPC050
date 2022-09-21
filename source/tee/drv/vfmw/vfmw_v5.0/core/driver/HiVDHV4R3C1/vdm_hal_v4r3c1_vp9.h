#ifndef __VDM_HAL_V4R3C1_VP9_H__
#define __VDM_HAL_V4R3C1_VP9_H__


#include "basedef.h"
#include "mem_manage.h"


//上行消息组
typedef struct
{
    USIGN reserved0:                          16;
    USIGN error_flag:                           1;
    USIGN endofvop_flag:                    1;
    USIGN reserved1:                           3;
    USIGN error_mode:                       11;
} VP9_V4R3C1_UPMSG_D0;

typedef struct
{
    USIGN tile0_start_ctb_num:           20;
    USIGN reserved0:                          12;
} VP9_V4R3C1_UPMSG_D1;

typedef struct
{
    USIGN tile0_end_ctb_num:            20;
    USIGN reserved0:                          12;
} VP9_V4R3C1_UPMSG_D2;


#ifdef __cplusplus
extern "C" {
#endif


SINT32 VP9HAL_V4R3C1_InitHal(VDMHAL_HWMEM_S *pHwMem);
SINT32 VP9HAL_V4R3C1_StartDec(VP9_DEC_PARAM_S *pVp9DecParam, SINT32 VdhId, VOID *pTask);

#ifdef __cplusplus
}
#endif

#endif //__VDM_HAL_V4R3C1_VP9_H__

