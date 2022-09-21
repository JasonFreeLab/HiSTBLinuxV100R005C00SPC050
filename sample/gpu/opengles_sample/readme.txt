
These samples support 4 platforms, include:
a. Utgard Fbdev EGL Platform
b. Utgard DirectFB EGL Platform
c. Midgard Fbdev EGL Platform
d. Midgard DirectFB EGL PLatform

The sdk chip tpye would select the Utgard or Midgard GPU, user don't care about it.
You should refer to the sdk cfg.mak, configure the "CFG_HI_EGL_TYPE" to select the Fbdev or DirectFB EGL platform.


If you would run the DirectFB EGL platfrom:

(1) some env valuable should be configured, make sure the system can find the DirectFB so.

    "export LD_LIBRARY_PATH=$(DIRECTFB_BIN)/directfb/lib:$LD_LIBRARY_PATH;"
    "export DFBARGS=depth=32,layer-size=1920x1080,pixelformat=ARGB,layer-bg-none,no-cursor,
     module-dir=$(DIRECTFB_BIN)/directfb/lib/directfb-1.6-0"

(2) guarantee enough framebuffer memory. for example, one 1080P RGBA8888 double buffer surface cost 16M memory.

    "insmod hi_fb.ko video="hi_fb:vram0_size:46000"   #FB can get 46M memory.

(3) you should export DFBEGL_NO_SMMU=1, if your platform could not support smmu.

Sample brief introduction:

(1) es20_eglCreateWindowSurface: output the on-screen memory.
(2) es20_eglCreatePixmapSurface: output the off-screen memory, which user specified.
(3) es20_eglCreatePbufferSurface: output the off-screen dumy memory.
(4) es20_glEGLImageTargetTexture2DOES: input the memory which user specified.

(5) es20_eglCreateFramebufeerObject: output the off-screen memory, which user specified in FBO way.
(6) es20_eglCreateSyncKHR: sync operation.
(7) es20_glBlendFunc: blend operation.
(8) es20_yuv420sp_to_rgba8888_windowsurface: input the yuv420sp memory, output the rgba8888 memory.
(9) es20_yuv420sp_to_yuv420sp_framebufferobject: input the yuv420sp memory, output the yuv420sp memory.


