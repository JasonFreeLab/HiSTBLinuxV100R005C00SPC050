#include "vdp_drv_ip_nxg.h"
#include "vdp_drv_func.h"

extern S_VDP_REGS_TYPE *pVdpReg;

HI_S32 VDP_DRV_SetNxgMode(HI_U32 enLayer, VDP_NXG_CFG_S *stCfg)
{

    VDP_NXG_SetNxgWm3dEn     ( enLayer, stCfg->wm3d_en);
    VDP_NXG_SetNxgWm3dEyeEn  ( enLayer, stCfg->wm3d_righteye);
    VDP_NXG_SetNxgDwmEn      ( enLayer, stCfg->dwm_en);
    VDP_NXG_SetNxgDebugEn    ( enLayer, stCfg->debug_en);
    VDP_NXG_SetNxgFrameRate  ( enLayer, stCfg->frame_rate);
    VDP_NXG_SetNxgKeyin      ( enLayer, stCfg->keyin);
    VDP_NXG_SetNxgPayload    ( enLayer, stCfg->payload_0, stCfg->payload_1);
    VDP_NXG_SetNxgSetting0   ( enLayer, stCfg->setting[0]);
    VDP_NXG_SetNxgSetting1   ( enLayer, stCfg->setting[1]);
    VDP_NXG_SetNxgSetting2   ( enLayer, stCfg->setting[2]);
    VDP_NXG_SetNxgSetting3   ( enLayer, stCfg->setting[3]);
    VDP_NXG_SetNxgSetting4   ( enLayer, stCfg->setting[4]);
    VDP_NXG_SetNxgSetting5   ( enLayer, stCfg->setting[5]);
    VDP_NXG_SetNxgVideoYfpos ( enLayer, stCfg->video_yfpos);
    VDP_NXG_SetNxgVideoXfpos ( enLayer, stCfg->video_xfpos);
    VDP_NXG_SetNxgVideoYlpos ( enLayer, stCfg->video_ylpos);
    VDP_NXG_SetNxgVideoXlpos ( enLayer, stCfg->video_xlpos);
    //VDP_NXG_SetNxgWm3dEn( enLayer, wm3d_en);
    //VDP_NXG_SetNxgWm3dEyeEn( enLayer, wm3d_righteye);

    return HI_SUCCESS;

}

HI_S32 VDP_FUNC_GetNxgCfg(VDP_NXG_NXG_MODE_E NxgMode, HI_U32 iw, HI_U32 ih, VDP_NXG_CFG_S *stCfg)
{
    if(NxgMode == VDP_NXG_NXG_TYP)
    {
        stCfg->dwm_en        = 1 ;
        stCfg->debug_en      = 0 ;
        stCfg->frame_rate    = 24 ;
        stCfg->keyin         = 0x01ac7f33 ;
        stCfg->payload_0     = 0x6789abcd ;
        stCfg->payload_1     = 0x012345 ;
        stCfg->setting[0]    = 0x86318c63 ;
        stCfg->setting[1]    = 0x21084210 ;
        stCfg->setting[2]    = 0x08421084 ;
        stCfg->setting[3]    = 0x6318c421 ;
        stCfg->setting[4]    = 0x2108418c ;
        stCfg->setting[5]    = 0x04 ;
        stCfg->video_xfpos   = 0 ;  //no use
        stCfg->video_yfpos   = 0 ; //no use
        stCfg->video_xlpos   = iw ; //no use
        stCfg->video_ylpos   = ih ; //no use
        stCfg->wm3d_en       = 0;
        stCfg->wm3d_righteye = 0;
    }
    else if(NxgMode == VDP_NXG_NXG_NORM)
    {
        stCfg->dwm_en        = stCfg->dwm_en ;
        stCfg->debug_en      = stCfg->debug_en ;
        stCfg->frame_rate    = stCfg->frame_rate ;
        stCfg->keyin         = stCfg->keyin ;
        stCfg->payload_0     = stCfg->payload_0 ;
        stCfg->payload_1     = stCfg->payload_1 ;
        stCfg->setting[0]    = stCfg->setting[0] ;
        stCfg->setting[1]    = stCfg->setting[1] ;
        stCfg->setting[2]    = stCfg->setting[2] ;
        stCfg->setting[3]    = stCfg->setting[3] ;
        stCfg->setting[4]    = stCfg->setting[4] ;
        stCfg->setting[5]    = stCfg->setting[5] ;
        stCfg->video_xfpos   = 0 ;  //no use
        stCfg->video_yfpos   = 0 ; //no use
        stCfg->video_xlpos   = iw ; //no use
        stCfg->video_ylpos   = ih ; //no use
        stCfg->wm3d_en       = stCfg->wm3d_en;
        stCfg->wm3d_righteye = stCfg->wm3d_righteye;
    }
    return HI_SUCCESS;
}

