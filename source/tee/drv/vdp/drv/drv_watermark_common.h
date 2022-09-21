/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :
* Description:
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __VDP_WATERMARK_COMMON_EXT_H__
#define __VDP_WATERMARK_COMMON_EXT_H__

#define VMX_IDX_MAX 8
#define NXG_IDX_MAX 8

typedef struct tagNXG_CFG_S
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
}NXG_CFG_S;


//The VM-Ctrl provides a c-structure as described below. It is provided to a driver that will
//communicate those values to the hardware.
// VideoMark Core Parameters
typedef struct DRV_VMX_CORE_PARAMETERS_REND {

  /*
    Defines the version of the memory buffer as provided by the VM-Ctrl. Increases in the minor
    version will only append parameters to the end of the buffer allowing earlier versions to
    understand parameters and ignoring additions. Major versions need to be understood to proceed.
    Default: VERSION_MAJOR = 1, VERSION_MINOR =0
    Variation: rarely.
  */
  //versioning
  HI_U8 version_major;
  HI_U8 version_minor;

  //embedding part
  HI_U8 watermark_on;
  HI_U8 frequency_distance[3][3];
  HI_U8 background_embedding_on;
  HI_U16 embedding_strength_threshold_8[3];
  HI_U16 embedding_strength_threshold_bg_8[3];
  HI_U16 embedding_strength_threshold_10[12];
  HI_U16 embedding_strength_threshold_bg_10[12];
  HI_U16 embedding_strength_threshold_12[48];
  HI_U16 embedding_strength_threshold_bg_12[48];
  HI_U16 direction_max;
  HI_S8 strength_multiply;

  //rendering part
  HI_U8 payload_symbols[1920];
  HI_U8 symbols_rows;
  HI_U8 symbols_cols;
  HI_U8 symbols_xpos;
  HI_U8 symbols_ypos;
  HI_U8 symbol_size;
  HI_U16 spacing_vert;
  HI_U16 spacing_horz;
  HI_U8 symbol_scale_control;
}drv_vmx_hw_soc_rend_t;


typedef union hiVDP_DRV_VWM_PARAM_U
{
    drv_vmx_hw_soc_rend_t             stVerimatrix;
    HI_TEE_VWM_NEXGUARD_PARAM_S       stNextguard;
}VDP_DRV_VWM_PARAM_U;


typedef struct  hi_SERVE_CHANNEL_INFOR_S{
   HI_HANDLE  hServiceIndex;
   HI_BOOL    bOpen;
   VDP_DRV_VWM_PARAM_U uWaterMarkParam;
}HI_SERVICE_CHANNEL_INFOR_S;

HI_S32 Drv_Common_CheckuuidInvalid(TEE_UUID *paUUid, HI_U32 u32Num);
HI_S32 Drv_Common_CheckChannelOpen(HI_SERVICE_CHANNEL_INFOR_S *paChannelOpenInfor,
                                                 HI_U32 u32ArrayNum,
                                                 HI_U8 u8ServiceIdx);

HI_SERVICE_CHANNEL_INFOR_S * Drv_Common_GetChannelDiscription(HI_SERVICE_CHANNEL_INFOR_S *paChannelOpenInfor,
                                                         HI_U32 u32ArrayNum,
                                                         HI_U8 u8ServiceIdx);

HI_S32 Drv_Common_InsertServiceNode(HI_SERVICE_CHANNEL_INFOR_S *paChannelOpenInfor,
                                                HI_U32 u32ArrayNum,
                                                HI_U8 u8ServiceIdx);
HI_VOID Drv_Common_DeleteServiceNode(HI_SERVICE_CHANNEL_INFOR_S *paChannelOpenInfor,
                                                         HI_U32 u32ArrayNum,
                                                         HI_U8 u8ServiceIdx);
HI_U32 Drv_Common_GetOpenChannelCnts(HI_SERVICE_CHANNEL_INFOR_S *paChannelOpenInfor,
                                                    HI_U32 u32ArrayNum);

HI_VOID DRV_VDP_HAL_Init(HI_VOID);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DMX_HELPER_H__ */
