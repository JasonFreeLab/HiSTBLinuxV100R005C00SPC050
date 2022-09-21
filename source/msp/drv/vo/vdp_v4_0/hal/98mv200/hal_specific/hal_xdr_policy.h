/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_xdr_policy.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2017/06/12
Last Modified :
Description   : interfaces to adapt hal's structures.
Function List :
History       :
******************************************************************************/
#ifndef __HAL_XDR_POLICY_H__
#define __HAL_XDR_POLICY_H__

#include "drv_win_share.h"

#ifdef __cplusplus
#if __cplusplus
 extern "C"
{
#endif
#endif

HI_BOOL XDR_SPECIFIC_CheckUserSetColorSpaceValid(HI_DRV_DISP_COLOR_SPACE_E enUserSetColorSpace);

#ifndef __DISP_PLATFORM_BOOT__
HI_VOID VDP_DRV_MaskAndBackupGfx(HI_U32 u32GfxLayerId,HI_U32 *pu32Alpha,HI_U32 *pu32MuteState);
HI_VOID VDP_DRV_UnmaskGfx(HI_U32 u32GfxLayerId,HI_U32 u32Alpha,HI_U32 u32MuteState);
HI_VOID VDP_DRV_SetGfxMixvBypassState(HI_U32 u32GfxLayerId,HI_BOOL bEnable);

HI_BOOL XDR_SPECIFIC_CheckOutputSignalValid(HI_DRV_DISP_OUT_TYPE_E enDispType);

HI_VOID XDR_SPECIFIC_AdjustConfig(WIN_SHARE_INFO_S  *pstWinShareInfo,
                                       HI_U32             u32MaxWinIndex,
                                       HI_BOOL            *pbVdmProcess,
                                       HI_DRV_DISP_PROCESS_MODE_E  enLastDispProcessMode,
                                       HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                                       HI_DRV_COLOR_SPACE_E   *penOutCs,
                                       HI_DRV_DISP_OUT_TYPE_E *penOutType);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

