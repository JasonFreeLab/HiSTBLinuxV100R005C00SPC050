#ifndef __VDP_HAL_IP_NXG_H__
#define __VDP_HAL_IP_NXG_H__

#include "hi_reg_common.h"
#include "vdp_define.h"


HI_VOID VDP_NXG_SetNxgDwmEn      ( HI_U32 u32Data, HI_U32 dwm_en);
HI_VOID VDP_NXG_SetNxgDebugEn    ( HI_U32 u32Data, HI_U32 debug_en);
HI_VOID VDP_NXG_SetNxgFrameRate  ( HI_U32 u32Data, HI_U32 frame_rate);
HI_VOID VDP_NXG_SetNxgWm3dEn     ( HI_U32 u32Data, HI_U32 wm_3d_en) ;
HI_VOID VDP_NXG_SetNxgWm3dEyeEn  ( HI_U32 u32Data, HI_U32 wm_3d_eye) ;
HI_VOID VDP_NXG_SetNxgKeyin      ( HI_U32 u32Data, HI_U32 keyin);
HI_VOID VDP_NXG_SetNxgPayload    ( HI_U32 u32Data, HI_U32 payload_0,HI_U32 payload_1);
HI_VOID VDP_NXG_SetNxgSetting0   ( HI_U32 u32Data, HI_U32 setting_0);
HI_VOID VDP_NXG_SetNxgSetting1   ( HI_U32 u32Data, HI_U32 setting_1);
HI_VOID VDP_NXG_SetNxgSetting2   ( HI_U32 u32Data, HI_U32 setting_2);
HI_VOID VDP_NXG_SetNxgSetting3   ( HI_U32 u32Data, HI_U32 setting_3);
HI_VOID VDP_NXG_SetNxgSetting4   ( HI_U32 u32Data, HI_U32 setting_4);
HI_VOID VDP_NXG_SetNxgSetting5   ( HI_U32 u32Data, HI_U32 setting_5);

HI_VOID VDP_NXG_SetNxgVideoYfpos ( HI_U32 u32Data, HI_U32 video_yfpos);
HI_VOID VDP_NXG_SetNxgVideoXfpos ( HI_U32 u32Data, HI_U32 video_xfpos);
HI_VOID VDP_NXG_SetNxgVideoYlpos ( HI_U32 u32Data, HI_U32 video_ylpos);
HI_VOID VDP_NXG_SetNxgVideoXlpos ( HI_U32 u32Data, HI_U32 video_xlpos);

#endif//__VDP_HAL_IP_NXG_H__
