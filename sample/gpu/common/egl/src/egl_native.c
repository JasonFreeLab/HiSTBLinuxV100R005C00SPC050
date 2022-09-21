/*
** Copyright 1999-2005, Silicon Graphics, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of Silicon Graphics, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
**
** $Header: /export/home/cvs/conformes/conformes_patch/linux_nws_patch.txt,v 1.2 2005/07/27 10:23:23 mah Exp $
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "egl_native.h"

#if defined (EGL_API_FB)
#ifndef EXCLUDE_EGL_SPECIFICS
#include "EGL/eglplatform.h"
#endif
#endif

#if defined (EGL_API_FB)
/*static NativeDisplay g_Display;*/
/*static NativeWindow g_Window;*/
#endif

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

#define DEBUG_POS(Ret)

NativeDisplay nativeCreateDisplay(void)
{
#if defined (EGL_API_FB)
    return (NativeDisplay)EGL_DEFAULT_DISPLAY;
#endif
}

void nativeDestroyDisplay(NativeDisplay display)
{
#if defined (EGL_API_FB)
    return;
#endif
}

NativeWindow nativeCreateWindow(const char *title, int width, int height, EGLint visualId)
{
#if defined (EGL_API_FB)
    fbdev_window *fbwin = malloc( sizeof(fbdev_window));
    if (NULL == fbwin)
    {
        return 0;
    }

    fbwin->width  = width;
    fbwin->height = height;
    return fbwin;
#endif
}

void nativeDestroyWindow(NativeWindow window)
{
#if defined (EGL_API_FB)
    free(window);
#endif
}

#if 0
NativePixmap nativeCreatePixmap(int width, int height, EGLint visualId)
{

}

void nativeDestroyPixmap(NativePixmap pixmap)
{

}
#endif