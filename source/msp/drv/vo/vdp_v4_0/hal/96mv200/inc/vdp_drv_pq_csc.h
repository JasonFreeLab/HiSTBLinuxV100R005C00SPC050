#ifndef __DRV_PQ_CSC_H__
#define __DRV_PQ_CSC_H__
#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif

#include "vdp_define.h"
#include "vdp_drv_comm.h"

HI_S32 VDP_PQ_GetCSCCoefPtr(HI_VOID* pstCscCtrl,VDP_CSC_MODE_E enCbbCscMode, HI_PQ_CSC_MODE_E enCscMode, HI_VOID* pstCscCoef, HI_VOID* pstCscDcCoef);
HI_S32 VDP_PQ_GetWcgGmmCoef(HI_U32 u32Layer, HI_U16 *pu16GmmCoef);
HI_S32 VDP_PQ_GetWcgDegmmCoef(HI_U32 u32Layer, HI_U16 *pu16DegmmCoef);
HI_S32 VDP_DRV_SetWcgGmmCoef(HI_U32 u32Layer, HI_U16 *pu16GmmCoef);
HI_S32 VDP_DRV_SetWcgDeGmmCoef(HI_U32 u32Layer, HI_U16 *pu16DegmmCoef);

#endif