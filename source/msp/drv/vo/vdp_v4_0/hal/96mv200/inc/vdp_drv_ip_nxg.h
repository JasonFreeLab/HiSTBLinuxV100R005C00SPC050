#ifndef __VDP_IP_DRV_NXG_H__
#define __VDP_IP_DRV_NXG_H__

#include "vdp_hal_ip_nxg.h"
#include "vdp_drv_comm.h"

typedef struct tagVDP_NXG_CFG_S
{
    HI_U32 dwm_en;
    HI_U32 debug_en;
    HI_U32 frame_rate;
    HI_U32 keyin;
    HI_U32 payload_0;
    HI_U32 payload_1;
    HI_U32 setting[6];
    HI_U32 video_yfpos;
    HI_U32 video_xfpos;
    HI_U32 video_ylpos;
    HI_U32 video_xlpos;
    HI_U32 wm3d_en;
    HI_U32 wm3d_righteye;
}VDP_NXG_CFG_S;

//add VID_NXG LayerID 
typedef enum
{
    VDP_LAYER_NXG_VID0      = 0x0,
    VDP_LAYER_NXG_DHD0      = 0x0,
    VDP_LAYER_NXG_VID1      = 0x1,
    VDP_LAYER_NXG_DHD1      = 0x1,
    VDP_LAYER_NXG_VP0       = 0x2,
    VDP_LAYER_NXG_BUTT
} VDP_LAYER_NXG_E;

typedef enum tagVDP_NXG_NXG_MODE_E
{
    VDP_NXG_NXG_TYP = 0 ,
    VDP_NXG_NXG_NORM = 1 ,

    VDP_NXG_NXG_BUTT
}VDP_NXG_NXG_MODE_E;

HI_S32 VDP_FUNC_GetNxgCfg(VDP_NXG_NXG_MODE_E NxgMode, HI_U32 iw, HI_U32 ih, VDP_NXG_CFG_S *stCfg);

HI_S32 VDP_DRV_SetNxgMode(HI_U32 enLayer, VDP_NXG_CFG_S *stCfg);

#endif//__VDP_IP_DRV_NXG_H__
