/******************************************************************************

  Copyright (C), 2016-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_hdmi_reg_sec_cfg.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/07/13
  Description   :
  History       :
  Date          : 2016/07/13
  Author        : sdk
  Modification  :
*******************************************************************************/


#ifndef __TEE_REG_HDMI_SEC_H__
#define __TEE_REG_HDMI_SEC_H__

#include "hi_type.h"

#define HDMI_BASE_ADDR_SEC_CFG          0xF8A80000
#define REG_ADDR_PERI_HDMITX_AVCTTPT    (HDMI_BASE_ADDR_SEC_CFG +  0x0038)
#define REG_ADDR_PERI_VDP_DOWNSCAL_V0   (HDMI_BASE_ADDR_SEC_CFG +  0x003c)
#define REG_ADDR_PERI_VDP_DOWNSCAL_V1   (HDMI_BASE_ADDR_SEC_CFG +  0x0040)
#define REG_ADDR_PERI_CTRL_EN			(HDMI_BASE_ADDR_SEC_CFG +  0x0050)



/*
*breaf      PERI_HDMITX_AVCTTPT	HDMI????????
*base       0xF8A80000
*addr       0x0038
*data       32
*default    0xF0000000
*/
typedef union
{
    struct{
        HI_U32 hdcp2x_video_mute   : 1  ;//[0    ]  RW  0x0
        HI_U32 hdcp2x_audio_mute   : 2  ;//[2:1  ]  RW  0x0
        HI_U32 hdcp1x_video_mute   : 1  ;//[3    ]  RW  0x0
        HI_U32 hdcp1x_audio_mute   : 2  ;//[5:4  ]  RW  0x0
        HI_U32 reserved            : 2  ;//[7:6  ]  RW  0x0
        HI_U32 hdcp2p2_req         : 1  ;//[8    ]  RW  0x0
        HI_U32 hdcpx_req           : 1  ;//[9    ]  RW  0x0
        HI_U32 downscale_check_v0  : 1  ;//[10   ]  RW  0x0
        HI_U32 downscale_check_v1  : 1  ;//[11   ]  RW  0x0
        HI_U32 hdmitx_sec_access_en: 1  ;//[12   ]  RW  0x0
        HI_U32 hdmitx_vdp_mute_en  : 1  ;//[13   ]  RW  0x0
        HI_U32 hdcp1x_apb_sec_en   : 1  ;//[14   ]  RW  0x0
        HI_U32 hdcp2x_apb_sec_en   : 1  ;//[15   ]  RW  0x0
        HI_U32 reserved1           : 15 ;//[31:16]  RW  0xF000
    }bits;

    HI_U32 u32;

}REG_PERI_HDMITX_AVCTTPT;

typedef union
{
    struct{
        HI_U32 special_sec_en       : 4 ;//[31:16]  RW  0xF000  ???
        HI_U32 hdcp2x_apb_sec_en    : 4 ;
		HI_U32 hdcp1x_apb_sec_en    : 4 ;
		HI_U32 reserved             : 16;
		HI_U32 hdcp_sec_ctrl_lock   : 1 ;
		HI_U32 reserved1            : 3 ;
    }bits;
    HI_U32 u32;
}REG_PERI_HDCP_AVCTTPT;
typedef union
{
    struct{
        HI_U32  width  : 16  ;
        HI_U32  hight  : 16  ;
    }bits;
    HI_U32 u32;
}REG_PERI_VDP_DOWNSCAL;

HI_VOID REG_HDMI_SEC_hdcp2x_video_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2x_audio_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_video_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_audio_mute_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2p2_req_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcpx_req_Set(HI_U32);
HI_VOID REG_HDMI_SEC_downscale_check_v0_Set(HI_U32);
HI_VOID REG_HDMI_SEC_downscale_check_v1_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp_ctr_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp_sec_ctrl_lock_Set(HI_U32 vaule);
HI_VOID REG_HDMI_SEC_hdmitx_sec_access_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp1x_apb_sec_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_hdcp2x_apb_sec_en_Set(HI_U32);
HI_VOID REG_HDMI_SEC_vdp_down_scal_v0_width_set(HI_U32);
HI_VOID REG_HDMI_SEC_vdp_down_scal_v0_hight_set(HI_U32);
HI_VOID REG_HDMI_SEC_vdp_down_scal_v1_width_set(HI_U32);
HI_VOID REG_HDMI_SEC_vdp_down_scal_v1_hight_set(HI_U32);

HI_U32 REG_HDMI_SEC_hdcp2x_video_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2x_audio_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_video_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_audio_mute_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2p2_req_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcpx_req_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_downscale_check_v0_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_downscale_check_v1_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdmitx_sec_access_en_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp1x_apb_sec_en_Get(HI_VOID);
HI_U32 REG_HDMI_SEC_hdcp2x_apb_sec_en_Get(HI_VOID);


#endif //__TEE_REG_HDMI_SEC_H__


