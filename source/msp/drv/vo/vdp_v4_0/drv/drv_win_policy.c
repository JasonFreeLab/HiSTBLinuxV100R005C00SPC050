/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_bufcore.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/04/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "drv_win_policy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */





HI_S32 WinParamAlignUp(HI_S32 s32X, HI_U32 u32A)
{
    if (!u32A)
    {
        return s32X;
    }
    else
    {
        return ( (( s32X + (u32A - 1) ) / u32A ) * u32A);
    }
}

HI_S32 WinParamAlignDown(HI_S32 s32X, HI_U32 u32A)
{
    if (!u32A)
    {
        return s32X;
    }
    else
    {
        return (( s32X / u32A ) * u32A);
    }
}

HI_VOID WinOutRectAlign(HI_RECT_S *pstRectAlign)
{
    if (WinGetHDWinNum() <= 1)
    {
        if (WinCheckHDIs3DMode(HI_DRV_DISPLAY_1) )
        {
            pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_3D_ALIGN);
            pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_3D_ALIGN);
            pstRectAlign->s32Width  = WinParamAlignUp(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_3D_ALIGN);
            pstRectAlign->s32Height = WinParamAlignUp(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_3D_ALIGN);
        }
        else
        {
            pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_ALIGN);
            pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_ALIGN);
            pstRectAlign->s32Width  = WinParamAlignUp(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_ALIGN);
            pstRectAlign->s32Height = WinParamAlignUp(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_ALIGN);
        }
    }
    else
    {
        if (WinCheckHDIs3DMode(HI_DRV_DISPLAY_1) )
        {
            pstRectAlign->s32X = WinParamAlignUp(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_3D_ALIGN);
            pstRectAlign->s32Y = WinParamAlignUp(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_3D_ALIGN);
            pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_3D_ALIGN);
            pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_3D_ALIGN);
        }
        else
        {
            pstRectAlign->s32X = WinParamAlignUp(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_ALIGN);
            pstRectAlign->s32Y = WinParamAlignUp(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_ALIGN);
            pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_ALIGN);
            pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_ALIGN);
        }
    }

    return ;
}

HI_VOID WinInRectAlign(HI_RECT_S *pstRectAlign  , HI_U32 u32LayerNO)
{
    if (WinCheckHDIs3DMode(HI_DRV_DISPLAY_1) || ( VDP_LAYER_VID0 == u32LayerNO))
    {
        pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_IN_RECT_X_3D_ALIGN);
        pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_IN_RECT_Y_3D_ALIGN);
        pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_IN_RECT_WIDTH_3D_ALIGN);
        pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_IN_RECT_HEIGHT_3D_ALIGN);
    }
    else
    {
        pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_IN_RECT_X_ALIGN);
        pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_IN_RECT_Y_ALIGN);
        pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_IN_RECT_WIDTH_ALIGN);
        pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_IN_RECT_HEIGHT_ALIGN);
    }

    return ;
}

HI_BOOL  Win_CheckTnrLocateOnVdp(WINDOW_S *pstWin,
                                 HI_RECT_S *pstFrameSize)
{
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_S32 ret = 0;

    if ((ret = pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer, &stVideoLayerCap)))
    {
        return  HI_FALSE;
    }

    if (stVideoLayerCap.bTnrSnrDbDMDrDs)
    {
        if ((pstFrameSize->s32Width > 1920)
            && (pstFrameSize->s32Height > 1080))
        {
            return  HI_TRUE;
        }
    }

    return  HI_FALSE;

}

HI_VOID WinAdjustVideoOutRect(HI_RECT_S *pstDispRect, HI_RECT_S *pstVideoOutRect)
{
    HI_S32 s32DispFirstX = 0;
    HI_S32 s32DispFirstY = 0;

    WinOutRectAlign(pstVideoOutRect);

    s32DispFirstX  = pstDispRect->s32X;
    s32DispFirstY  = pstDispRect->s32Y;

    if (pstVideoOutRect->s32X < s32DispFirstX)
    {
        pstVideoOutRect->s32X = s32DispFirstX;
    }

    if (pstVideoOutRect->s32Y < s32DispFirstY)
    {
        pstVideoOutRect->s32Y = s32DispFirstY;
    }

    return;
}

/*since we support out of window, so when out of window, the content and size of
 * the window  should be  cropped.
 */
HI_S32 Win_Revise_OutOfScreenWin_OutRect(HI_RECT_S *pstInRect,
        HI_RECT_S *pstVideoRect, HI_RECT_S *pstDispRect,
        HI_RECT_S stScreen,
        HI_DRV_DISP_OFFSET_S stOffsetRect,
        WIN_HAL_PARA_S *pstLayerPara)
{
    HI_RECT_S stInRect = *pstInRect;
    HI_RECT_S stVideoRect = *pstVideoRect;
    HI_RECT_S stDispRect = *pstDispRect;
    HI_RECT_S stOutRect = {0};
    HI_RECT_S stVideoRectOffset ;
    HI_S32 s32VaildWidth, s32VaildHeight;
    HI_S32 ix = 0, iy = 0, iw = 0, ih = 0;
    HI_S32 ox = 0, oy = 0, ow = 0, oh = 0;
    HI_BOOL bDispFlag = HI_FALSE;
    HI_CHIP_TYPE_E   enChipType;
    HI_CHIP_VERSION_E enChipVersion;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    stVideoRectOffset.s32X = stDispRect.s32X - stVideoRect.s32X ;
    stVideoRectOffset.s32Y = stDispRect.s32Y - stVideoRect.s32Y;
    stVideoRectOffset.s32Width = stDispRect.s32Width - stVideoRect.s32Width;
    stVideoRectOffset.s32Height = stDispRect.s32Height - stVideoRect.s32Height;

    ix = pstInRect->s32X;
    iy = pstInRect->s32Y;
    iw = pstInRect->s32Width;
    ih = pstInRect->s32Height;

    stScreen.s32X = 0;
    stScreen.s32Y = 0;

    stScreen.s32Width -= stOffsetRect.u32Left + stOffsetRect.u32Right;
    stScreen.s32Height -= stOffsetRect.u32Top + stOffsetRect.u32Bottom;
    /*stOutRect considered the offset already, so no need to - left.*/
    stVideoRect.s32X  -= stOffsetRect.u32Left;
    stVideoRect.s32Y  -= stOffsetRect.u32Top;

    if (stVideoRect.s32X < 0)
    {
        s32VaildWidth = stVideoRect.s32Width  + stVideoRect.s32X;

        if (s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = 0;
            iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            ix += stInRect.s32Width - iw;

            bDispFlag = HI_TRUE;
        }
        else
        {
            // >screen size
            ow = stScreen.s32Width;
            if (s32VaildWidth < ow) // no full screan
            {
                ow = s32VaildWidth;
            }

            ox = 0;
            iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            ix += stInRect.s32Width - stInRect.s32Width * s32VaildWidth / stVideoRect.s32Width;
        }
    }
    else if (stVideoRect.s32X < (stScreen.s32Width - WIN_INRECT_MIN_WIDTH))
    {
        s32VaildWidth = stVideoRect.s32Width;

        if (s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = stVideoRect.s32X;
            iw = stInRect.s32Width;
            ix += 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            ox = stVideoRect.s32X;
            ix += 0;

            if ((s32VaildWidth + ox) > stScreen.s32Width)
            {
                ow = stScreen.s32Width - stVideoRect.s32X;
                iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            }
            else
            {
                ow = stVideoRect.s32Width;
                iw = stInRect.s32Width;
            }
        }
    }
    else
    {
        ow = WIN_INRECT_MIN_WIDTH;
        ox = stScreen.s32Width  - ow;
        iw = stInRect.s32Width * ow / stVideoRect.s32Width;
        ix += 0;
        bDispFlag = HI_TRUE;
    }


    if (stVideoRect.s32Y < 0)
    {
        s32VaildHeight = stVideoRect.s32Height + stVideoRect.s32Y;
        if (s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = 0;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            iy += stInRect.s32Height - ih;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = 0;
            oh = stScreen.s32Height;
            if (s32VaildHeight < oh)
            {
                oh = s32VaildHeight;
            }

            ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            iy += stInRect.s32Height - stInRect.s32Height * s32VaildHeight / stVideoRect.s32Height;
        }
    }
    else if (stVideoRect.s32Y < (stScreen.s32Height - WIN_INRECT_MIN_HEIGHT))
    {
        s32VaildHeight = stVideoRect.s32Height;

        if (s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = stVideoRect.s32Y;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height;
            iy += 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = stVideoRect.s32Y;
            iy += 0;
            if ((s32VaildHeight + oy) > stScreen.s32Height)
            {
                oh = stScreen.s32Height - stVideoRect.s32Y;
                ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            }
            else
            {
                oh = stVideoRect.s32Height;
                ih = stInRect.s32Height;
            }
        }
    }
    else
    {
        oh = WIN_INRECT_MIN_HEIGHT;
        oy = stScreen.s32Height - oh;
        ih = stInRect.s32Height * oh / stVideoRect.s32Height;
        iy += 0;
        bDispFlag = HI_TRUE;
    }

    ox  += stOffsetRect.u32Left;
    oy  += stOffsetRect.u32Top;

    /*DTS2013100801678, pstInRect in fact is the output of vpss(zme,dei,crop dnr)
     * it does not confirm to  the align limit of inrect.
     * If we give a wrong use, and make a wrong align,
     * there will be no consistency bettween GFX and VIDEO, and the backgroud color will appears.
     */

    pstDispRect->s32X = ox + stVideoRectOffset.s32X;
    pstDispRect->s32Y = oy + stVideoRectOffset.s32Y;
    if (pstDispRect->s32X < 0)
    {
        pstDispRect->s32X = 0;
    }
    if (pstDispRect->s32Y < 0)
    {
        pstDispRect->s32Y = 0;
    }

    pstDispRect->s32Width = ow + stVideoRectOffset.s32Width;
    pstDispRect->s32Height = oh + stVideoRectOffset.s32Height;

    pstInRect->s32X = ix ;
    pstInRect->s32Y = iy ;
    pstInRect->s32Width = iw ;
    pstInRect->s32Height = ih ;

    WinInRectAlign(pstInRect, pstLayerPara->u32LayerNO);

    stOutRect.s32X = ox;
    stOutRect.s32Y = oy;
    stOutRect.s32Width  = ow;
    stOutRect.s32Height = oh;
    WinAdjustVideoOutRect(pstDispRect, &stOutRect);

    *pstVideoRect = stOutRect;

    return bDispFlag;
}

#define INVALID_INTERMEDIARect  0xFFFF
HI_VOID Win_Policy_GetPQDegradingConfigFromTEE(HI_BOOL bTEEMode,
                                                                HI_RECT_S *pstInRect,
                                                                HI_RECT_S *pstOutRect,
                                                                HI_U32    u32VideoLayer,
                                                                HI_RECT_S *pstFrameIntermediateRect,
                                                                HI_BOOL   *pbHdcpDegradePQ,
                                                                HI_RECT_S *pstHdcpIntermediateRect)
{
    if ((VDP_LAYER_VID0 != u32VideoLayer)
        || (HI_FALSE == bTEEMode)
        || ((pstFrameIntermediateRect->s32X == pstInRect->s32X)
             &&(pstFrameIntermediateRect->s32Y == pstInRect->s32Y)
             &&(pstFrameIntermediateRect->s32Width == pstInRect->s32Width)
             &&(pstFrameIntermediateRect->s32Height == pstInRect->s32Height))
        || ((INVALID_INTERMEDIARect == pstFrameIntermediateRect->s32Width)
             || (INVALID_INTERMEDIARect == pstFrameIntermediateRect->s32Height))
             || (0 == pstFrameIntermediateRect->s32Width)
             || (0 == pstFrameIntermediateRect->s32Width)
       )
    {

        pstHdcpIntermediateRect->s32X      = 0;
        pstHdcpIntermediateRect->s32Y      = 0;
        pstHdcpIntermediateRect->s32Width  = 0;
        pstHdcpIntermediateRect->s32Height = 0;

        *pbHdcpDegradePQ = HI_FALSE;
    }
    else
    {
        *pstHdcpIntermediateRect = *pstFrameIntermediateRect;
        *pbHdcpDegradePQ = HI_TRUE;
    }

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
