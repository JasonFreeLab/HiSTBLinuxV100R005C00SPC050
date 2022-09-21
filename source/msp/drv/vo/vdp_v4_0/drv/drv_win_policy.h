#ifndef __WIN_POLICY_H_
#define __WIN_POLICY_H_

#include "drv_display.h"

#include "drv_window.h"
#include "drv_win_policy.h"
#include "drv_win_priv.h"
#include "hi_drv_sys.h"
#include "hi_drv_stat.h"
#include "drv_vdec_ext.h"
#include "drv_disp_hal.h"
#include "drv_disp_alg_service.h"
#include "hi_drv_module.h"
#include "drv_pq_ext.h"





HI_BOOL  Win_CheckTnrLocateOnVdp(WINDOW_S *pstWin,
                                 HI_RECT_S *pstFrameSize);

HI_S32 Win_Revise_OutOfScreenWin_OutRect(HI_RECT_S *pstInRect,
                        HI_RECT_S *pstVideoRect, HI_RECT_S *pstDispRect,
                        HI_RECT_S stScreen,
                        HI_DRV_DISP_OFFSET_S stOffsetRect,
                        WIN_HAL_PARA_S *pstLayerPara);



HI_VOID WinOutRectAlign(HI_RECT_S *pstRectAlign);
HI_VOID WinInRectAlign(HI_RECT_S *pstRectAlign,HI_U32 u32LayerNO);
HI_S32 WinParamAlignDown(HI_S32 s32X, HI_U32 u32A);
HI_S32 WinParamAlignUp(HI_S32 s32X, HI_U32 u32A);
HI_VOID Win_Policy_GetPQDegradingConfigFromTEE(HI_BOOL bTEEMode,
                                                                HI_RECT_S *pstInRect,
                                                                HI_RECT_S *pstOutRect,
                                                                HI_U32    u32VideoLayer,
                                                                HI_RECT_S *pstFrameIntermediateRect,
                                                                HI_BOOL   *pbHdcpDegradePQ,
                                                                HI_RECT_S *pstHdcpIntermediateRect);


#endif




