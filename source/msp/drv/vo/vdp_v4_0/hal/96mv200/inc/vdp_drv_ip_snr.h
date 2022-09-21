#ifndef __DRV_IP_SNR_H__
#define __DRV_IP_SNR_H__

#include "vdp_drv_comm.h"
#include "vdp_hal_ip_snr.h"
//#include <stdio.h>

typedef enum tagVDP_V0_SNR_MODE_E
{
    VDP_V0_SNR_TYP_1    = 0x0,
    VDP_V0_SNR_TYP_2    = 0x0,
    VDP_V0_SNR_ZERO     ,
    VDP_V0_SNR_RAND     ,
    VDP_V0_SNR_MAX      ,
    VDP_V0_SNR_MIN      ,
    VDP_V0_SNR_TYP_PQ   ,
    VDP_V0_SNR_CFG_BUTT

}VDP_V0_SNR_MODE_E;


//---------------------------------
//SNR BEGIN
//---------------------------------
typedef struct tagVDP_SNR_PARA_INFO
{
    HI_U32             snr_en           ;
    HI_U32             lumasnren        ;
    HI_U32             chromasnren      ;
    HI_U32             debugmodeen      ;
    HI_U32             debugmode        ;
    HI_U32             demomodeen       ;
    HI_U32             demomodelr       ;
    HI_U32             demomodecoor       ;
    HI_U32             diredgesmoothen  ;
    HI_U32             motionedgeen     ;
}VDP_SNR_PARA_INFO;

//---------------------------------
//SNR END
//---------------------------------

HI_VOID VDP_FUNC_SetSnrMode(VDP_SNR_PARA_INFO SnrParaInfo, VDP_V0_SNR_MODE_E SnrMode);

#endif
