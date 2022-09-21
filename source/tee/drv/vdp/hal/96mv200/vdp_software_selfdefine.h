#ifndef __VDP_SOFTWARE_SELFDEFINE_H__
#define __VDP_SOFTWARE_SELFDEFINE_H__

#include "vdp_define.h"
#include "vdp_reg_define.h"

#define VDP_SEC_OUTPUT_CTRL_ADDR  0xf8a80020

typedef enum tagDISP_VENC_E
{
    DISP_VENC_HDATE0 = 0, 
    DISP_VENC_SDATE0,
    DISP_VENC_VGA0,
    DISP_VENC_MAX
}DISP_VENC_E;

HI_S32  VDP_SetLayerEnable(VDP_LAYER_VID_E enLayer, HI_BOOL bEnable);
HI_VOID VDP_Hw_Init(HI_VOID);
HI_VOID VDP_GetResolutionInfo(HI_S32 s32ChnOffsetNum, HI_U32 *pHact, HI_U32 *pVact, HI_U32 *pIop);
HI_VOID VDP_GetCoefInfo(U_DATE_COEFF0 *pDATE_COEFF0);


HI_VOID VDP_MVCN_SetMcvnEnable(HI_BOOL bEnable);
HI_S32  SDATE_MVCN_DATE_SetMcvn(HI_U32 *pu32Value);


HI_VOID SDATE_HDATE_VBI_SetWssEn(DISP_VENC_E enChanel,HI_BOOL bEnWss);
HI_VOID SDATE_HDATE_VBI_SetCgmsTypeAEn(DISP_VENC_E enChanel,HI_BOOL bEnTypeA);
HI_VOID VDP_VBI_SetCgmsTypeBEn(DISP_VENC_E enChanel, HI_BOOL bEnTypeB);
HI_VOID SDATE_HDATE_VBI_SetWssData(DISP_VENC_E enChanel,HI_U32 u32Data);
HI_VOID SDATE_HDATE_VBI_SetCgmsTypeA(DISP_VENC_E enChanel,HI_U32 u32Data);

#endif

