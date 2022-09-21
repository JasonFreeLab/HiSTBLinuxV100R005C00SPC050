#ifndef __VDP_GEN_COEF_H__
#define __VDP_GEN_COEF_H__

#include "vdp_drv_coef.h"
#if EDA_TEST
#include "vdp_env_def.h"
#endif

typedef struct
{
    void   *                    p_coef          ;
    void   *                    p_coef_new      ;
    VDP_DRV_COEF_DATA_TYPE_E    coef_data_type  ;
    HI_U32                      length          ;
    VDP_RM_COEF_MODE_E          coef_data_mode  ;
    HI_S32                      coef_max        ;
    HI_S32                      coef_min        ;
}VDP_DRV_COEF_GEN_CFG;

HI_U32 VDP_DRV_GenCoef(VDP_DRV_COEF_GEN_CFG* stCfg);

#endif

