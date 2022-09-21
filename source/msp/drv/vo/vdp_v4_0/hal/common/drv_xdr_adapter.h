/******************************************************************************
Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_xdr_adapter.h
Version       : Initial Draft
Author        : Hisilicon multimedia software  group
Created       : 2017/05/26
Last Modified :q00293180
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_XDR_ADAPTER_H__
#define __DRV_XDR_ADAPTER_H__

#include "hi_type.h"
#include "drv_win_share.h"
#include "vdp_drv_vid.h"
#ifndef __DISP_PLATFORM_BOOT__
#include "drv_disp_dolby.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define LOGIC_MAX_ALPHA 255
#define XDR_COLOR_SPACE_TRANSFER(a) ({\
        VDP_CLR_SPACE_E b = VDP_CLR_SPACE_YUV_709_L;\
        switch(a)\
        {\
            case HI_DRV_CS_BT601_YUV_LIMITED:\
            {\
                b = VDP_CLR_SPACE_YUV_601_L;\
                break;\
            }\
            case HI_DRV_CS_BT601_YUV_FULL:\
            {\
                b = VDP_CLR_SPACE_YUV_601;\
                break;\
            }\
            case HI_DRV_CS_BT709_YUV_LIMITED:\
            {\
                b = VDP_CLR_SPACE_YUV_709_L;\
                break;\
            }\
            case HI_DRV_CS_BT709_YUV_FULL:\
            {\
                b = VDP_CLR_SPACE_YUV_709; \
                break;\
            }\
            case HI_DRV_CS_BT709_RGB_FULL:\
            {\
                b = VDP_CLR_SPACE_RGB_709; \
                break;\
            }\
            case HI_DRV_CS_BT2020_YUV_LIMITED:\
            {\
                b = VDP_CLR_SPACE_YUV_2020_L;\
                break;\
            }\
            case HI_DRV_CS_BT2020_RGB_FULL:\
            {\
                b = VDP_CLR_SPACE_RGB_2020;\
                break;\
            }\
            default:\
            {\
                DISP_ERROR("Invalid color space->%d\n",a);\
                break;\
            }\
        }\
        b;\
})

#define XDR_OUT_TYPE_TRANSFER(a) ({\
        VDP_CLR_SPACE_E b = XDP_DISP_TYPE_NORMAL;\
        switch(a)\
        {\
            case HI_DRV_DISP_TYPE_NORMAL:\
            {\
                b = XDP_DISP_TYPE_NORMAL;\
                break;\
            }\
            case HI_DRV_DISP_TYPE_SDR_CERT:\
            {\
                b = XDP_DISP_TYPE_SDR_CERT;\
                break;\
            }\
            case HI_DRV_DISP_TYPE_DOLBY:\
            {\
                b = XDP_DISP_TYPE_DOLBY;\
                break;\
            }\
            case HI_DRV_DISP_TYPE_HDR10:\
            {\
                b = XDP_DISP_TYPE_HDR10; \
                break;\
            }\
            case HI_DRV_DISP_TYPE_HDR10_CERT:\
            {\
                b = XDP_DISP_TYPE_HDR10_CERT; \
                break;\
            }\
            case HI_DRV_DISP_TYPE_HLG:\
            {\
                b = XDP_DISP_TYPE_HLG;\
                break;\
            }\
            case HI_DRV_DISP_TYPE_TECHNICOLOR:\
            {\
                b = XDP_DISP_TYPE_TECHNICOLOR;\
                break;\
            }\
            default:\
            {\
                DISP_ERROR("Invalid out type->%d\n",a);\
                break;\
            }\
        }\
        b;\
})


#define XDR_PIXEL_FMT_TRANSFER(a) ({\
        VDP_VID_IFMT_E b = VDP_VID_IFMT_SP_420;\
        switch(a)\
        {\
            case HI_DRV_PIX_FMT_NV12: \
            case HI_DRV_PIX_FMT_NV21: \
            case HI_DRV_PIX_FMT_NV21_CMP: \
            case HI_DRV_PIX_FMT_NV12_CMP: \
            {\
                b = VDP_VID_IFMT_SP_420;\
                break;\
            }\
            case HI_DRV_PIX_FMT_NV16_2X1: \
            case HI_DRV_PIX_FMT_NV61_2X1: \
            {\
                b = VDP_VID_IFMT_SP_422;\
                break;\
            }\
            case HI_DRV_PIX_FMT_NV21_TILE: \
            case HI_DRV_PIX_FMT_NV21_TILE_CMP: \
            {\
                b = VDP_VID_IFMT_SP_TILE_64;\
                break;\
            }\
            case HI_DRV_PIX_FMT_UYVY:\
            {\
                b = VDP_VID_IFMT_PKG_UYVY; \
                break;\
            }\
            case HI_DRV_PIX_FMT_YUYV:\
            {\
                b = VDP_VID_IFMT_PKG_YUYV; \
                break;\
            }\
            case HI_DRV_PIX_FMT_YVYU:\
            {\
                b = VDP_VID_IFMT_PKG_YVYU;\
                break;\
            }\
            default:\
            {\
                DISP_ERROR("Invalid pixel fmt->%d\n",a);\
                break;\
            }\
        }\
        b;\
    })

#define XDR_DISPMODE_TRANSFER(a) ({\
        VDP_DISP_MODE_E b = VDP_DISP_MODE_2D;\
        switch(a)\
        {\
            case DISP_STEREO_NONE:\
            {\
                b = VDP_DISP_MODE_2D;\
                break;\
            }\
            case DISP_STEREO_FPK:\
            {\
                b = VDP_DISP_MODE_FP;\
                break;\
            }\
            case DISP_STEREO_SBS_HALF:\
            {\
                b = VDP_DISP_MODE_SBS;\
                break;\
            }\
            case DISP_STEREO_TAB:\
            {\
                b = VDP_DISP_MODE_TAB; \
                break;\
            }\
            case DISP_STEREO_SBS_FULL:\
            {\
                b = VDP_DISP_MODE_FS; \
                break;\
            }\
            default:\
            {\
                DISP_ERROR("Invalid disp mode->%d\n",a);\
                break;\
            }\
        }\
        b;\
    })


#define XDR_FRM_TYPE_TRANSFER(a) ({\
        VDP_DISP_MODE_E b = VDP_DISP_MODE_2D;\
        switch(a)\
        {\
            case HI_DRV_FT_FPK:\
            {\
                b = VDP_DISP_MODE_FP;\
                break;\
            }\
            case HI_DRV_FT_SBS:\
            {\
                b = VDP_DISP_MODE_SBS;\
                break;\
            }\
            case HI_DRV_FT_TAB:\
            {\
                b = VDP_DISP_MODE_TAB; \
                break;\
            }\
            default:\
            {\
                break;\
            }\
        }\
        b;\
    })

#ifndef __DISP_PLATFORM_BOOT__
//===================dolby process functions==========================
#ifdef VDP_DOLBY_HDR_SUPPORT
HI_VOID ADAPTER_SetDolbyCfg(WIN_INFO_S *pstWinInfo, DRV_DISP_DOLBY_PLAY_INFO_S *pstDolbyInfo);

#else
#define ADAPTER_SetDolbyCfg(a)

#endif
#endif


//===================adapter functions  =============================
#ifdef CFG_HI3798CV200
HI_VOID ADAPTER_SetHisiMode(HI_U32      u32LayerId,
                                    WIN_INFO_S *pstWinInfo);
#endif

HI_VOID ADAPTER_CloseV0V1Layer(HI_VOID);
HI_VOID ADAPTER_SetLayerCfg(HI_U32      u32LayerId,
                                    WIN_INFO_S *pstWinInfo,
                                    HI_BOOL    *pbVdmArray,
                                    HI_BOOL bConfigWholeLayer);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*  __DRV_XDR_ADAPTER_H__  */
