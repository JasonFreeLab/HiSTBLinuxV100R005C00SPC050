#ifndef __VDP_DRV_BKG_PROCESS_H__
#define __VDP_DRV_BKG_PROCESS_H__
#include "vdp_drv_vid.h"


typedef struct stVDP_COLOR_SPACE_INFO_S
{
    HI_BOOL bSourceIsSdr;
    VDP_CLR_SPACE_E enInClrSpace;
    VDP_CLR_SPACE_E enOutClrSpace;

} VDP_COLOR_SPACE_INFO_S;

typedef struct stVDP_BKG_SET_S
{
    HI_BOOL bIsSeneSwitch;

    HI_BOOL bIsSeneVesaSwitch;
    HI_BOOL bCurSceneMixvBkgIsYuv;
    HI_BOOL bIsVesa;
} VDP_BKG_SET_S;

HI_VOID  VDP_DRV_GetVdpIsVesa(VDP_COLOR_SPACE_INFO_S  *pstColorSpaceInfo,VDP_BKG_SET_S  *pstVdpBkgSet);
HI_VOID  VDP_DRV_GetVdpIsSceneSwitch(VDP_COLOR_SPACE_INFO_S  *pstColorSpaceInfo,VDP_BKG_SET_S  *pstVdpBkgSet);
HI_S32   VDP_DRV_SetVdpBkg(HI_U32 u32LayerId,VDP_COLOR_SPACE_INFO_S  *pstColorSpaceInfo);

HI_VOID XDP_DRV_JudgeRgbColorSpace(VDP_CLR_SPACE_E enOutClrSpace,HI_BOOL *pbRgbColorSpace);
HI_VOID XDP_DRV_AdjustMixvColor(VDP_BKG_S *pstMixvColor, HI_BOOL bRgbColorSpace);

HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_VOID);

#endif