
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
* 20100609              Original
*
************************************************************************/

#ifndef __VDM_HAL_REAL9_C__
#define __VDM_HAL_REAL9_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID RV9HAL_V300R001_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId);
VOID RV9HAL_V300R001_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);
VOID RV9HAL_V300R001_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);
VOID RV9HAL_V300R001_StartVDH(RV9_DEC_PARAM_S *pRv9DecParam);


SINT32 RV9HAL_V300R001_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV9HAL_V300R001_StartDec( RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId )
{
    return VDMHAL_OK;
}

VOID RV9HAL_V300R001_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId)
{
    return;
}

VOID RV9HAL_V300R001_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}

VOID RV9HAL_V300R001_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}
VOID RV9HAL_V300R001_StartVDH(RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL9_C__
