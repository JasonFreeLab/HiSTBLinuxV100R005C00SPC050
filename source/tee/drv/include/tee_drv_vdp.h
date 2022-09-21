#ifndef __TEE_DRV_VDP_H__
#define __TEE_DRV_VDP_H__

#include "hi_type.h"
#include "drv_mcvn.h"
#include "drv_cgms.h"

/* Define dispctrl para */
typedef struct {
    HI_BOOL   bMute;//close
}DRV_VDP_DISPCTRL_ANALOGOUTPUT_PARAMETER_S;



HI_S32 HI_DRV_VDP_SetAnalogOutStrategy(const DRV_VDP_DISPCTRL_ANALOGOUTPUT_PARAMETER_S *stPara);
HI_S32 HI_DRV_VDP_SetMacrovision(HI_DRV_DISP_MACROVISION_E enMode);
//HI_S32 HI_DRV_VDP_SetCgms(HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg) ;

#endif
