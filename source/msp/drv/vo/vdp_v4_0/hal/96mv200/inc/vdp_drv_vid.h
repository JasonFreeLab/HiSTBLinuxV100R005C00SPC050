#ifndef __DRV_VID_H__
#define __DRV_VID_H__
#include "vdp_define.h"
#include "vdp_hal_vid.h"
#include "vdp_drv_pq_ext.h"
#include "vdp_drv_ip_vdm.h"
#include "vdp_drv_ip_gdm.h"

#define MAX_WINDOWS_NUM  36


typedef enum tagXDP_THE_NUM_ZME_E
{
    XDP_THE_NUM_ZME1 = 1,
    XDP_THE_NUM_ZME2 = 2,
    XDP_THE_NUM_ZME_BUTT

}XDP_THE_NUM_ZME_E;

typedef struct tagVDP_ADDR_S
{
    HI_U32 u32LumAddr;
    HI_U32 u32ChmAddr;

    HI_U32 u32LumStr;
    HI_U32 u32ChmStr;

    HI_U32  u32DcmpHeadSize;

    HI_BOOL bSecure;
    HI_BOOL bSmmu;
}VDP_ADDR_S;

typedef enum tagVDP_ADDR_E
{
    VDP_ADDR_DATA = 0,//2d left eye data
    VDP_ADDR_3D      ,//3d right eye data
    VDP_ADDR_TILE    ,//tile64 2bit
    VDP_ADDR_HEAD    ,//dcmp head data
    VDP_ADDR_BUTT
}VDP_ADDR_E;

typedef enum tagVDP_CLR_SPACE_E
{
    VDP_CLR_SPACE_YUV_601   = 0x1,
    VDP_CLR_SPACE_YUV_709   ,
    VDP_CLR_SPACE_YUV_2020  ,
    VDP_CLR_SPACE_RGB_601   ,
    VDP_CLR_SPACE_RGB_709   ,
    VDP_CLR_SPACE_RGB_2020  ,
    VDP_CLR_SPACE_YUV_601_L   ,
    VDP_CLR_SPACE_YUV_709_L   ,
    VDP_CLR_SPACE_YUV_2020_L  ,
    VDP_CLR_SPACE_RGB_601_L   ,
    VDP_CLR_SPACE_RGB_709_L   ,
    VDP_CLR_SPACE_RGB_2020_L  ,

    VDP_CLR_SPACE_BUTT

}VDP_CLR_SPACE_E;

typedef enum hiXDP_VIDEO_FRAME_TYPE_E
{
    XDP_VIDEO_FRAME_TYPE_SDR = 0,      /*Normal SDR frame.*/
    XDP_VIDEO_FRAME_TYPE_DOLBY_BL,     /*Dolby BL frame.*/
    XDP_VIDEO_FRAME_TYPE_DOLBY_EL,     /*Dolby EL frame.*/
    XDP_VIDEO_FRAME_TYPE_HDR10,        /*HDR10 frame.*/
    XDP_VIDEO_FRAME_TYPE_HLG,          /*HLG frame.*/
    XDP_VIDEO_FRAME_TYPE_SLF,          /*SLF frame.*/
    XDP_VIDEO_FRAME_TYPE_TECHNICOLOR,  /*TECHNICOLOR frame.*/
    XDP_VIDEO_FRAME_TYPE_BUTT
}XDP_VIDEO_FRAME_TYPE_E;

typedef enum hiXDP_DISP_OUT_TYPE_E
{
    XDP_DISP_TYPE_NORMAL = 0,    /* 普通信号显示 BT601 BT709*/
    XDP_DISP_TYPE_SDR_CERT,      /* SDR输出认证时需要*/
    XDP_DISP_TYPE_DOLBY,         /* DolbyVision信号显示 */
    XDP_DISP_TYPE_HDR10,         /* 标准HDR信号显示 */
    XDP_DISP_TYPE_HDR10_CERT,
    XDP_DISP_TYPE_HLG,
    XDP_DISP_TYPE_TECHNICOLOR,

    XDP_DISP_TYPE_BUTT
}XDP_DISP_OUT_TYPE_E;


typedef enum
{
    HIHDR_HDR10_IN_SDR_OUT = 0,
    HIHDR_HDR10_IN_HDR10_OUT ,
    HIHDR_HDR10_IN_HLG_OUT,
    HIHDR_HLG_IN_SDR_OUT ,
    HIHDR_HLG_IN_HDR10_OUT ,
    HIHDR_HLG_IN_HLG_OUT ,

    HIHDR_SLF_IN_SDR_OUT ,
    HIHDR_SLF_IN_HDR10_OUT ,
    HIHDR_SLF_IN_HLG_OUT ,
    HIHDR_XVYCC,

    HIHDR_SDR_BT2020CL_IN_BT709_OUT,
    HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT,
    HIHDR_BT2020_IN_RGB_709_OUT,
    HIHDR_BT2020_IN_709_OUT,
    HIHDR_BT2020_IN_2020_OUT,
    HIHDR_SDR_IN_HDR10_OUT ,
    HIHDR_SDR_IN_HLG_OUT ,
    HIHDR_709_IN_BT2020_OUT,
    HIHDR_BYPASS_MODE ,
    HIHDR_TECHNI_IN_HDR10_OUT,
    HIHDR_TECHNI_IN_HLG_OUT,
    HIHDR_TECHNI_IN_SDR_OUT,

    HIHDR_AVS_IN_SDR_OUT,
    HIHDR_AVS_IN_HDR10_OUT,

    HIHDR_SCENE_BUTT
} HIHDR_SCENE_MODE_E;

typedef struct tagXDP_LAYER_SRC_INFO_S
{
    VDP_ADDR_S             stAddr[VDP_ADDR_BUTT] ;//
    VDP_CLR_SPACE_E        enSrcClrSpace         ;//
    VDP_RECT_S             stSrcRect             ;
    HI_BOOL                bSmmuEn               ;//
    XDP_VIDEO_FRAME_TYPE_E enXdpViDeoFrameType   ;//
    HI_BOOL                bDolbyCompatible;
    VDP_VID_IFMT_E         enInFmt     ;
    VDP_DATA_WTH           enDataWidth ;
    HI_BOOL                bDcmpEn     ;
    HI_BOOL                bDcmpLost   ;
	
    HI_BOOL                bUVOrder;

    HI_BOOL                bCompatibleSource;
    VDP_RECT_S             stElSrcRect             ;

}XDP_LAYER_SRC_INFO_S;

typedef struct tagXDP_LAYER_HZME_CFG_S
{
    VDP_HZME_MODE_E  enHzmeMode;
    HI_BOOL          bHzmeEn;

}XDP_LAYER_HZME_CFG_S;

typedef struct tagXDP_LAYER_EXTERN_S
{
    HI_U32 u32HorRation;
    HI_U32 u32VerRation;
    HI_BOOL bReduceDataWth;
    HI_BOOL bConfigWholeLayer;

    HI_BOOL bVtapReduce;

    HI_PQ_ZME_COEF_RATIO_E enRationHL;
    HI_PQ_ZME_COEF_RATIO_E enRationHC;
    HI_PQ_ZME_COEF_RATIO_E enRationVL;
    HI_PQ_ZME_COEF_RATIO_E enRationVC;

    VDP_VID_IFMT_E         enXdpElInfmt     ;
    HI_PQ_ZME_COEF_RATIO_E enZme2RationHL;
    HI_PQ_ZME_COEF_RATIO_E enZme2RationHC;
    HI_PQ_ZME_COEF_RATIO_E enZme2RationVL;
    HI_PQ_ZME_COEF_RATIO_E enZme2RationVC;

    //....
  //VDP_VID_IFMT_E  enXdpElInfmt;

}XDP_LAYER_EXTERN_S;

typedef struct tagXDP_LAYER_ZME_CFG_S
{
    VDP_RECT_S stZme2InRect                 ;

    HI_BOOL bZmeFrmFmtOut;
    HI_BOOL bZmeBFIn ;
    HI_BOOL bZmeBFOut;
    HI_U32 u32ZmeNum;

    HI_PQ_IMAGE_FMT_S   stZmeFmt[HI_PQ_V0_ZME_NODE_BUTT];

} XDP_LAYER_ZME_CFG_S;

typedef struct tagXDP_CSC_CFG_S
{
    VDP_CSC_MODE_E     enCbbCscMode ;
    HI_PQ_CSC_MODE_E   enPqCscMode;

    HI_PQ_CSC_COEF_S   stPqCscCoef ;
    HI_PQ_CSC_DCCOEF_S stPqCscDc ;

} XDP_CSC_CFG_S;


typedef struct
{
    HI_S32 s32ZmeOffsetHC;
    HI_S32 s32ZmeOffsetVC;
    HI_S32 s32ZmeOffsetVLBtm;
    HI_S32 s32ZmeOffsetVCBtm;
    HI_S32 bZmeOrder;

    HI_U32 u32ZmeWIn ;
    HI_U32 u32ZmeWOut;
    HI_U32 u32ZmeHIn ;
    HI_U32 u32ZmeHOut;
    HI_U32 u32ZmeRatioHL;
    HI_U32 u32ZmeRatioVL;
    HI_U32 u32ZmeRatioHC;
    HI_U32 u32ZmeRatioVC;

    HI_S32 s32ZmeOffsetHL;
    HI_S32 s32ZmeOffsetVL;
}VDP_VZME_RTL_PARA_S;

typedef struct tagXDP_LAYER_DISP_INF_S
{
    HI_BOOL                bInterlace;
    VDP_RECT_S             stFmtReso;
    VDP_DISP_MODE_E        enDispMode                     ;
    VDP_CLR_SPACE_E        enOutClrSpace              ;
    XDP_DISP_OUT_TYPE_E    enDisPlayMode;

}XDP_LAYER_DISP_INF_S;

typedef enum XDP_ADDR_3D_2LOWBIT_E
{
    XDP_ADDR_3D_2LOWBIT_LEFT_EYE = 0x0,
    XDP_ADDR_3D_2LOWBIT_RIGHT_EYE = 0x1,
    XDP_ADDR_3D_2LOWBIT_2LOWBIT = XDP_ADDR_3D_2LOWBIT_RIGHT_EYE,

    XDP_ADDR_3D_2LOWBIT_BUTT

}XDP_ADDR_3D_2LOWBIT_E;


typedef struct tagXDP_LAYER_SYS_CFG_S
{
    HI_U32  u32RegionNO                    ;
    HI_U32  u32LayerZorder                 ;
    HI_BOOL bRegionEn     ;//
    HI_BOOL bEnable                        ;
    HI_BOOL bMuteEn       ;//
    HI_BOOL bRegionModeEn                  ;
    HI_BOOL bSecureEn                      ;
	HI_U32 u32Alpha                        ;
	HI_U32 u32AllAlpha                     ;
    HI_BOOL bVdmProcess[MAX_WINDOWS_NUM]   ;//
    HI_U32  u32VdmOnLayerId;
}XDP_LAYER_SYS_CFG_S;

typedef struct tagXDP_LAYER_FDR_CFG_S
{
    VDP_DATA_RMODE_E       enReadMode  ;
    VDP_RECT_S             stCropRect  ;
    VDP_RECT_S             stTileCropRect;
    VDP_DRAW_MODE_E        enDrawMode;
    VDP_DRAW_PIXEL_MODE_E  enDrawPixelMode;
}XDP_LAYER_FDR_CFG_S;

typedef struct tagXDP_LAYER_BKG_CFG_S
{
    VDP_BKG_S              stMuteColor                    ;
    VDP_BKG_S              stLetterBoxColor               ;
    VDP_BKG_S              stMixvColor                    ;

}XDP_LAYER_BKG_CFG_S;

typedef struct tagXDP_LAYER_DISP_POSITION_CFG_S
{

    VDP_RECT_S             stVideoRect                    ;
    VDP_RECT_S             stDispRect                     ;
    VDP_RECT_S             stVp0DispRect                  ;

}XDP_LAYER_DISP_POSITION_CFG_S;

typedef struct tagXDP_LAYER_VID_INFO_S
{
    XDP_LAYER_SYS_CFG_S           stXdpSysCfg              ;
    XDP_LAYER_SRC_INFO_S          stXdpSrcCfg              ;
    XDP_LAYER_FDR_CFG_S           stXdpFdrCfg              ;
    XDP_LAYER_BKG_CFG_S           stXdpBkgCfg              ;
    XDP_LAYER_DISP_POSITION_CFG_S stXdpPositionCfg         ;
    XDP_LAYER_DISP_INF_S          stXdpDispCfg            ;
    XDP_LAYER_ZME_CFG_S           stXdpZmeCfg;

    XDP_LAYER_HZME_CFG_S          stXdpHZmeCfg;
    XDP_LAYER_EXTERN_S            stXdpLayerExtern;


} XDP_LAYER_VID_INFO_S;

typedef struct tagVDP_DRV_ADDR_INFO_S
{
    //for flip calc
    HI_U32 u32Hgt;
    HI_U32 u32ChmRatio;

    VDP_VID_IFMT_E enInFmt;
    VDP_DISP_MODE_E enDispMode;

    //addr
    VDP_ADDR_S stAddr[VDP_ADDR_BUTT];

    //dcmp
    HI_BOOL bDcmpEn;

    //draw mode
    VDP_DRAW_MODE_E enDrawMode;

VDP_DATA_WTH      enDataWidth          ;

}VDP_DRV_ADDR_INFO_S;


typedef struct tagVDP_DRV_CROP_INFO_S
{
    VDP_RECT_S         stSrcRect   ;
    VDP_RECT_S         stCropRect  ;//Crop Out
    VDP_VID_IFMT_E     enInFmt     ;
    VDP_DATA_RMODE_E   enReadMode  ;
    VDP_DISP_MODE_E    enDispMode  ;
    VDP_DRAW_MODE_E    enDrawMode  ;

    VDP_DRAW_PIXEL_MODE_E  enDrawPixelMode;
    VDP_ADDR_S        stAddr[VDP_ADDR_BUTT] ;

}VDP_DRV_CROP_INFO_S;

typedef struct tagVDP_DISPLAY_INFO_S
{
    HI_BOOL bInterlace;
    VDP_DISP_MODE_E        enDispMode;
    VDP_RECT_S            stFmtResolution;
}VDP_DISPLAY_INFO_S;

typedef struct tagXDP_DRV_ZME_OFFSET_S
{
    HI_S32 s32ZmeOffsetVL;
    HI_S32 s32ZmeOffsetVC;
    HI_S32 s32ZmeOffsetVLBtm;
    HI_S32 s32ZmeOffsetVCBtm;

}XDP_DRV_ZME_OFFSET_S;

typedef struct tagVDP_DRV_ZME_INFO_S
{
        VDP_RECT_S stZme1OutRect;
        VDP_RECT_S stZme2InRect;
        VDP_RECT_S stInRect         ;
        VDP_RECT_S stOutRect        ;
        VDP_VID_IFMT_E enInFmt      ;

        VDP_DATA_WTH   enDataWith     ;
        VDP_DATA_RMODE_E enReadMode ;
        VDP_DISP_MODE_E enDispMode  ;
        VDP_DRAW_MODE_E enDrawMode;
        VDP_DRAW_PIXEL_MODE_E  enDrawPixelMode;
        VDP_HZME_MODE_E  enHzmeMode;
        HI_BOOL  bHzmeEn;


        HI_BOOL  bzme1En;
        HI_BOOL  bzme2En;

        HI_U32 u32HorRation;
        HI_U32 u32VerRation;

        VDP_DISPLAY_INFO_S      stVdpDispInfo;

        XDP_DRV_ZME_OFFSET_S stXdpDrvZmeOffset[XDP_THE_NUM_ZME_BUTT];

        VDP_VID_CVFIR_VCOEF_S pstCvfirVCoef;

}VDP_DRV_ZME_INFO_S;

//typedef struct tagVDP_DRV_CROP_INFO_S
//{
//  VDP_RECT_S stSrcRect;
//  VDP_RECT_S stCropRect;
//  HI_U32     u32ChmRatio;
//
//  VDP_DISP_MODE_E enDispMode;
//
//}VDP_DRV_CROP_INFO_S;
#ifndef __DISP_PLATFORM_BOOT__
HI_S32 VDP_DRV_SetVidLayer(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstLayerInfoIn, HI_PQ_HDR_CFG  *pstPqHdrCfg);
HI_S32 VDP_DRV_SetVidCrop (HI_U32 u32LayerId, const VDP_DRV_CROP_INFO_S *pstCropInfo, VDP_DRV_ADDR_INFO_S *pstAddrInfo);
HI_S32 VDP_DRV_SetVidAddr(HI_U32 u32LayerId, const VDP_DRV_ADDR_INFO_S *pstAddrInfo);
HI_S32 VDP_DRV_SetVidZme(HI_U32 u32LayerId, VDP_DRV_ZME_INFO_S *pstZmeInfo,HI_BOOL enForceOutFMT420);
HI_S32 VDP_DRV_SetVid1Cvfir(HI_U32 u32LayerId, VDP_DRV_ZME_INFO_S *pstZmeInfo);
HI_S32 VDP_DRV_SetVidCsc(HI_U32 u32LayerId, VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr);
//HI_VOID VdpZmeComnSet(VDP_ZME_DRV_PARA_S* pstZmeDrvPara, VDP_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_S32 VDP_DRV_GetVidZmeStrategy(XDP_LAYER_VID_INFO_S *pstInfoOut,
                                 HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio,
                                 HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefType);

HI_S32 XDP_DRV_SetVidLayerFdr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut);
HI_S32 XDP_DRV_SetVidAddr(HI_U32 u32LayerId, const XDP_LAYER_VID_INFO_S *pstOutInfo);
HI_S32 XDP_DRV_GetVidZmeCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_LAYER_VID_INFO_S *pstInfoOut);
HI_S32 XDP_DRV_SetVidZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut);
HI_S32 XDP_DRV_SetVidReso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut);
HI_S32 XDP_DRV_SetVP0Reso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut);
HI_VOID VDP_DRV_HdrRegClean(HI_VOID);

HI_VOID VDP_DRV_SetHiHdrAjust(HI_PQ_HDR_CFG  *HiHdrCfg,DmCfg_t  *pstDmCfg);
HI_VOID VDP_DRV_SetGdmMode(HI_U32 u32LayerId, GDM_SCENE_MODE_E  enGdmSceneMode);

#endif

#endif
