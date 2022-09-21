#ifndef __VDP_DRV_PQ_TCHDR_H__
#define __VDP_DRV_PQ_TCHDR_H__

#include "hi_type.h"

HI_S32 VDP_DRV_SetTchdrCoef_C(HI_U16 * plutc);
HI_S32 VDP_DRV_SetTchdrCoef_P(HI_U16 * plutp);
HI_S32 VDP_DRV_SetTchdrCoef_S(HI_U16 * pluts);
HI_S32 VDP_DRV_SetTchdrCoef_I(HI_U16 * pluti);
HI_S32 VDP_DRV_SetTchdrCoef_D(HI_U16 * plutd);
HI_VOID VDP_Tchdr_SetReadCoef(HI_VOID);

#endif
