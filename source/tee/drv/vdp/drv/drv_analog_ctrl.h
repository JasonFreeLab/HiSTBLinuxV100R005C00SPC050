#ifndef __DRV_ANALOG_CTRL_H__
#define __DRV_ANALOG_CTRL_H__

#include "hi_tee_vdp.h"
#include "drv_vdp_com.h"
#include "drv_cgms.h"
#include "drv_mcvn.h"


HI_S32  DRV_VDP_Init();
HI_VOID DRV_DeInitAnalogCtrl();
HI_S32  DRV_GetSimilarFmtClass(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E *enFmt);
HI_VOID VDP_MonitorMcvnCgmsProcess();

HI_VOID VDP_McvnCgmsTest();

#endif
