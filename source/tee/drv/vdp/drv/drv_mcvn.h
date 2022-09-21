#ifndef __DRV_MCVN_H__
#define __DRV_MCVN_H__


#define __TEE_WZ_XMU__

#ifdef __TEE_WZ_XMU__
#include "hi_tee_vdp.h"
#include "hi_tee_debug.h"
//#include "hi_tee_vdp_common.h"
#include "drv_vdp_com.h"

#define DISP_ERROR(fmt...)      HI_ERR_VDP(HI_MODULE_ID_VO, fmt)
#else
#include "hi_drv_disp.h"
#include "drv_disp_hal.h"
#endif


#ifdef __TEE_WZ_XMU__
typedef enum hiDRV_DISP_MACROVISION_E
{
    HI_DRV_DISP_MACROVISION_TYPE0,
    HI_DRV_DISP_MACROVISION_TYPE1,
    HI_DRV_DISP_MACROVISION_TYPE2,
    HI_DRV_DISP_MACROVISION_TYPE3,
    HI_DRV_DISP_MACROVISION_CUSTOMER,
    HI_DRV_DISP_MACROVISION_BUTT
}HI_DRV_DISP_MACROVISION_E;
#endif


typedef struct  hiDRV_MCVN_S
{
	HI_DRV_DISP_MACROVISION_E enMcvn;
    HI_DRV_DISP_FMT_E enFmt;
}DRV_MCVN_S;


HI_S32 DRV_MCVN_Init(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_FMT_E enFmt);

HI_S32 DRV_MCVN_DeInit(HI_DRV_DISPLAY_E enDisp);

HI_S32 DRV_MCVN_SetMacrovision(HI_DRV_DISPLAY_E enDisp, 
                                HI_DRV_DISP_MACROVISION_E enMode,
                                HI_DRV_DISP_FMT_E enFmt);
HI_S32 DRV_MCVN_SetDateMcvn(HI_DRV_DISP_FMT_E enFmt, HI_DRV_DISP_MACROVISION_E enMcvn);

HI_S32 DRV_MCVN_GetMacrovision(HI_DRV_DISPLAY_E enDisp, 
                                HI_DRV_DISP_MACROVISION_E *penMode);

#endif
