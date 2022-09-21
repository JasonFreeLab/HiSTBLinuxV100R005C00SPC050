

#ifndef __VDM_HAL_DIVX3_C__
#define __VDM_HAL_DIVX3_C__

#include "vdm_hal.h"
#include "decparam.h"



SINT32 DIVX3HAL_V300R001_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 DIVX3HAL_V300R001_StartDec( DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId )
{
    return VDMHAL_OK;
}

VOID DIVX3HAL_V300R001_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId)
{
    return;
}

VOID DIVX3HAL_V300R001_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}

VOID DIVX3HAL_V300R001_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}
VOID DIVX3HAL_V300R001_StartVDH(DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL9_C__
