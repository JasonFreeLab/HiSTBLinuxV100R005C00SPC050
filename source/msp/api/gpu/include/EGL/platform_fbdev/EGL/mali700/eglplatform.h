/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file eglplatform.h
 * Platform related definitions
 */

#ifndef _EGLPLATFORM_H_
#define _EGLPLATFORM_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#include <KHR/khrplatform.h>
#include <stdint.h>

#include "mali_fbdev_types.h"

#ifndef EGLAPI
#define EGLAPI
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY
#endif

#ifndef EGLAPIENTRYP
#define EGLAPIENTRYP EGLAPIENTRY *
#endif

typedef fbdev_window * EGLNativeWindowType;
typedef int32_t EGLNativePixmapType;
typedef void * EGLNativeDisplayType;

typedef EGLNativeWindowType NativeWindowType;
typedef EGLNativePixmapType NativePixmapType;
typedef EGLNativeDisplayType NativeDisplayType;

typedef int32_t EGLint;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _EGLPLATFORM_H_ */
