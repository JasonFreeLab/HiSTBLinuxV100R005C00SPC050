#ifndef __EGL_NATIVE_H__
#define __EGL_NATIVE_H__

#include <EGL/egl.h>
#include <EGL/eglplatform.h>

typedef NativeDisplayType NativeDisplay;
typedef void *            NativeWindow;
typedef void *            NativePixmap;

extern NativeDisplay NATIVE_CreateDisplay(void);
extern void          NATIVE_DestroyDisplay(NativeDisplay display);
extern NativeWindow  NATIVE_CreateWindow(const char *title, int width, int height,
                                                        EGLint visualId);
extern void          NATIVE_DestroyWindow(NativeWindow window);
extern NativePixmap  NATIVE_CreatePixmap(int width, int height, EGLint visualId);
extern void          NATIVE_DestroyPixmap(NativePixmap pixmap);

#endif /* NATIVE_H */
