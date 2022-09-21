/***********************************************************************
*
* Copyright (c) 2010 Hisilicon - All Rights Reserved
*
* File: $vdm_hal_real9.c$
* Date: $2010/06/09$
* Revision: $v1.0$
* Purpose: HiVDHV100 IP REAL9 VDM HAL Module.
*
* Change History:
*
* Date       Author            Change
* ======     ======            ======
* 20100609   q45134            Original
*
************************************************************************/

#ifndef __VDM_HAL_DIVX3_C__
#define __VDM_HAL_DIVX3_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID DIVX3HAL_V5R2C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask);
VOID DIVX3HAL_V5R2C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);
VOID DIVX3HAL_V5R2C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);


SINT32 DIVX3HAL_V5R2C1_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 DIVX3HAL_V5R2C1_StartDec( DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask)
{
    return VDMHAL_OK;
}

VOID DIVX3HAL_V5R2C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask)
{
    return;
}

VOID DIVX3HAL_V5R2C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}

VOID DIVX3HAL_V5R2C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}

#endif //__VDM_HAL_REAL9_C__
