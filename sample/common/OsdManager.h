/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : OsdManager.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/02/18
  Description   :
  History       :
  1.Date        : 2014/02/18
    Author      : sdk
    Modification: Created file

******************************************************************************/


#ifndef __OSD_MANAGER_H__
#define __OSD_MANAGER_H__

#ifndef LINUX_OS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <fcntl.h>
#include <utils/misc.h>
#include <signal.h>
#include <time.h>
#include <sched.h>
#include <sys/resource.h>
#include <cutils/memory.h>
#include <utils/Log.h>
#include <cutils/memory.h>

#include "jni.h"
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>
#include <android_runtime/android_view_Surface.h>
#include <android_runtime/android_view_SurfaceSession.h>
#include <android_runtime/android_graphics_SurfaceTexture.h>
#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <ui/GraphicBufferMapper.h>
#ifndef ANDROIDN
#include <ui/FramebufferNativeWindow.h>
#endif

#ifdef ANDROIDN
#include <gui/Surface.h>
#endif

#include <ui/GraphicBuffer.h>
#include <ui/PixelFormat.h>
#include "SkBitmap.h"
#include "SkImageDecoder.h"
#include "gralloc_priv.h"
#include "SkImageEncoder.h"
#include "SkCanvas.h"
#include "SkTypeface.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"
#include "hi_common.h"
#include "hi_tde_api.h"
#include "hi_tde_type.h"
#include "hi_unf_video.h"


#define MAX_SURFACE_NUM         (16)

#define SURFACE_DEFAULT_WIDTH   (1280)
#define SURFACE_DEFAULT_HEIGHT  (720)

#define SURFACE_HANDLE_INDEX   (0x00010000)

typedef struct tagSURFACE_ATTR_S
{
    HI_U32   u32Width;
    HI_U32   u32Height;
    HI_U32   u32Stride;
    HI_S32   s32PixelFormat;
}SURFACE_ATTR_S;

typedef struct tagCCTEXT_ATTR_S
{
    HI_U32  u32BufLen;

    HI_U32  u32bgColor;
    HI_U32  u32fgColor;
    HI_U32  u32edgeColor;

    HI_U8   u8justify;
    HI_U32  u8WordWrap;

    HI_U32  u8fontstyle;
    HI_U32  u8fontSize;
    HI_U32  u8edgeType;

    HI_BOOL bUnderline;
    HI_BOOL bItalic;

}CCTEXT_ATTR_S;

namespace android{

typedef struct tagOSD_DISP_SURFACE_S
{
    HI_U32                      hSurface;

    sp<SurfaceComposerClient>   Client;
    sp<SurfaceControl>          surfaceControl;
    sp<Surface>                 surface;

    ANativeWindow               *Window;
    ANativeWindowBuffer         *WindowBuffer;

    HI_U32                      PhyAddr;
    HI_VOID                     *VirtualAddr;

    SURFACE_ATTR_S              stAttr;
}OSD_DISP_SURFACE_S;


class OsdManager: public RefBase
{
private:
    OSD_DISP_SURFACE_S      m_DispSurface[MAX_SURFACE_NUM];

    OSD_DISP_SURFACE_S      *GetSurfaceInst(HI_HANDLE hSurface);

    void    *pPixels;

    HI_U32  captionSurfaceW;

    HI_U32  captionSurfaceH;

    HI_U8  *pu8ScaleBuffer;

public:
    OsdManager();
    ~OsdManager();

    HI_S32 lock(HI_HANDLE hSurface);
    HI_S32 unLock(HI_HANDLE hSurface);

    HI_S32 CreateSurface(SURFACE_ATTR_S *pstAttr, HI_HANDLE *phSurface);
    HI_S32 DestroySurface(HI_HANDLE hSurface);

    HI_S32 FillRect(HI_HANDLE hSurface, HI_RECT_S *pstRect, HI_U32 u32Color);
    HI_S32 Refresh(HI_HANDLE hSurface);

    HI_S32 Blit(HI_HANDLE hSrcSurface, HI_RECT_S *pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect);

    HI_S32 BlitFrameToSurface(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame,HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect);

    HI_S32 ClearSurface(HI_HANDLE hSurface);

    HI_S32 Videoframe2jpg(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_CHAR *DstFile);

    HI_S32 GetCCTextSize(HI_CHAR* pTest,HI_S32 *pWidth, HI_S32 *pHeigh );
    HI_S32 FillCCRect(HI_HANDLE hSurface,SURFACE_ATTR_S * pstSurfaceAttr , HI_RECT_S *pstRect, HI_U32 u32Color);
    HI_S32 DrawCCText(HI_HANDLE hSurface, SURFACE_ATTR_S * pstSurfaceAttr ,HI_RECT_S *pstRect, HI_CHAR *pText,CCTEXT_ATTR_S * pstAttr);
    HI_S32 CCBlit(HI_HANDLE hSrcSurface,SURFACE_ATTR_S * pstSurfaceAttr , HI_RECT_S *pstSrcRect, HI_RECT_S *pstDstRect);

    HI_S32 TeletextDrawBitmap(HI_HANDLE hSurface, HI_U8 *bitmapBuffer,HI_RECT_S *pstSrcRect,HI_RECT_S *pstDstRect);
    HI_S32 SubDrawBitmap(HI_HANDLE hSurface, HI_U8 *pu8BitmapBuffer,SURFACE_ATTR_S * pstSurfaceAttr ,HI_RECT_S *pstSrcRect);
};

} // end of namespace
#ifdef __cplusplus
}
#endif

#endif

#endif
