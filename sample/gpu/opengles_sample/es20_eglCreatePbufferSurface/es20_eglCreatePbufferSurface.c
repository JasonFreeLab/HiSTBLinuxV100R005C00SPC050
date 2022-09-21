/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : es20_eglCreatePbufferSurface.c
  Version       : Initial Draft
  Author        : Hisilicon Device Chipset Key Technologies GPU group
  Created       : 2016/12/15
  Description   :
  History       :
  1.Date        : 2016/12/15
    Author      :
    Modification: group review file

******************************************************************************/
#include <stdlib.h>
#include <unistd.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "hifb.h"
#include "es20_common.h"

#define COLOR_RED      0xffff0000
#define COLOR_GREEN    0xff00ff00
#define COLOR_BLUE     0xff0000ff

#define FHD_WIDTH  1920
#define FHD_HEIGHT 1080
#define HD_WIDTH  1280
#define HD_HEIGHT 720

#define TEXTURE_WIDTH  256
#define TEXTURE_HEIGHT 256
#define TEXTURE_RES_LENGTH (TEXTURE_WIDTH*TEXTURE_HEIGHT*3)
#define TEXTURE_RES "../res/texture_data"

#define VERT_SRC    "../res/shaders/original.vert.glsl"
#define FRAG_SRC    "../res/shaders/original.frag.glsl"

int attribute0_location = 0;    /* vetex coordinate */
int attribute1_location = 0;    /* texture coordinate */
int uniform0_location   = 0;
unsigned int texture_id = 0;    /* glGenTextures used */
unsigned int buffer0_id = 0;    /* glGenBuffers used */
unsigned int buffer1_id = 0;
unsigned int program_id = 0;
unsigned int vshader_id = 0;
unsigned int fshader_id = 0;

float texturecoords_data[] =
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};

float vetexcoords_data[] =
{
    -0.5f,  0.6f, 0.0f,
    0.5f,  0.6f, 0.0f,
    0.5f, -0.6f, 0.0f,
    -0.5f, -0.6f, 0.0f,
};

int main(void)
{
    fprintf(stderr, "\n>>>>>>>>>>>>>>>>start>>>>>>>>>>>>>>>>\n");

    NativeDisplayType native_display;
    NativePixmapType native_pixmap;
    EGLDisplay egl_display;
    EGLSurface egl_surface;
    EGLConfig egl_config;
    EGLContext egl_context;
    unsigned char * texture_data = NULL;
    int matching_configs;
    int ret, i;
    void *pdata;
    int window_width = FHD_WIDTH, window_height = FHD_HEIGHT;
    int texture_width = TEXTURE_WIDTH, texture_height = TEXTURE_HEIGHT;

    int configAttribs[] =
    {
        EGL_SAMPLES,      0,
        EGL_RED_SIZE,     8,
        EGL_GREEN_SIZE,   8,
        EGL_BLUE_SIZE,    8,
        EGL_ALPHA_SIZE,   8,
        EGL_DEPTH_SIZE,   0,
        EGL_STENCIL_SIZE, 0,
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_NONE,
    };

    int ctxAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    int attribListPbuffer[] =
    {
        EGL_WIDTH, FHD_WIDTH,
        EGL_HEIGHT, FHD_HEIGHT,
        /*EGL_PROTECTED_CONTENT_EXT, 1,*/
        EGL_NONE
    };

    /* >>>>>>>>>>>>>>>>>>>>>>>>> framebuffer process >>>>>>>>>>>>>>>>>>>>>>>> */
#if defined(FRAMEBUFFER_DEVICE_OPEN)
    int framebuffer_fd = HI_COMMON_OpenFramebufferDevice(window_width, window_height, DISPLAY_FORMAT_ARGB8888);
    if (-1 == framebuffer_fd)
    {
        HI_COMMON_CloseFramebufferDevice(framebuffer_fd);
        fprintf(stderr, "open framebuffer device failed\n");
        return 0;
    }
#endif

#if defined(EGL_API_FBDEV)

    HI_MMZ_BUF_S *pBuf = NULL;

    native_display = HI_COMMON_CreateNativeDisplay();

    pBuf = HI_COMMON_CreateMMZMemory(window_width * window_height * 4);

#if defined(EGL_API_UTGARD)

    native_pixmap = HI_COMMON_CreateNativePixmap(pBuf->phyaddr, window_width, window_height, 8, 8, 8, 8, 0);

#elif defined(EGL_API_MIDGARD)

    native_pixmap = HI_COMMON_CreateNativePixmap(pBuf->phyaddr, window_width, window_height, EGL_PIXMAP_FORMAT_ARGB8888);

#endif

#elif defined(EGL_API_DIRECTFB)

    native_display = HI_COMMON_CreateDFBNativeDisplay(window_width, window_height, DSPF_ARGB);

    native_pixmap = HI_COMMON_CreateDFBNativePixmap(window_width, window_height, DSPF_ARGB);

#endif

    /* >>>>>>>>>>>>>>>>>>>>>>>>> EGL process >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    egl_display = eglGetDisplay(native_display);

    ret = eglBindAPI(EGL_OPENGL_ES_API);
    ASSERT_EQUAL(ret, EGL_TRUE);

    ret = eglInitialize(egl_display, NULL, NULL);
    ASSERT_EQUAL(ret, EGL_TRUE);

    ret = eglChooseConfig(egl_display, configAttribs, &egl_config, 1, &matching_configs);
    ASSERT_EQUAL(ret, EGL_TRUE);

    egl_surface = eglCreatePbufferSurface(egl_display, egl_config, attribListPbuffer);
    ASSERT_NOT_EQUAL((unsigned long)egl_surface, (unsigned long)EGL_NO_SURFACE);

    egl_context = eglCreateContext(egl_display, egl_config, NULL, ctxAttribs);
    ASSERT_EQUAL(ret, EGL_TRUE);

    ret = eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
    ASSERT_EQUAL(ret, EGL_TRUE);

    /* >>>>>>>>>>>>>>>>>>>>>>>>> opengles process >>>>>>>>>>>>>>>>>>>>>>>>>>> */

    /* step 1: create vetex shader and fragment shader */
    vshader_id = HI_COMMON_CreateShader(VERT_SRC, GL_VERTEX_SHADER);
    fshader_id = HI_COMMON_CreateShader(FRAG_SRC, GL_FRAGMENT_SHADER);

    /* step 2: create program */
    program_id = HI_COMMON_CreateProgram(vshader_id, fshader_id);

    /* step 3: create buffer to store vetex coordinates and texture coordinates */
    buffer0_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*3*4, (const void*)vetexcoords_data);
    buffer1_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*2*4, (const void*)texturecoords_data);

    /* step 4: create texture */
    texture_id = HI_COMMON_CreateTexture(GL_TEXTURE0, GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR);

    /* step 5: get the location of attribute and uniform */
    attribute0_location = glGetAttribLocation(program_id, "aVetexCoord");
    glEnableVertexAttribArray(attribute0_location);

    attribute1_location = glGetAttribLocation(program_id, "aTexureCoord");
    glEnableVertexAttribArray(attribute1_location);

    uniform0_location = glGetUniformLocation(program_id, "uTextureSampler");
    glUniform1i(uniform0_location, 0);

    /* step 6 : load data to texure */
    texture_data = (unsigned char *)HI_COMMON_LoadFile(TEXTURE_RES, 0, TEXTURE_RES_LENGTH, "rb");
    if (texture_data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
        free(texture_data);
    }
    else
    {
        fprintf(stderr, "load texture datas failed\n");
    }

    /*get the pixmap memory virtual address*/
#if defined(EGL_API_FBDEV)

    pdata = pBuf->user_viraddr;

#elif defined(EGL_API_DIRECTFB)

    IDirectFBSurface *dfb_surface = (IDirectFBSurface*)native_pixmap;
    int pitch;

#endif

    for(i = 0; i < 10; i++)
    {
        /* other */
        glViewport(0,0, window_width, window_height);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /* load data from buffer to attribute valuable */
        glBindBuffer(GL_ARRAY_BUFFER, buffer0_id);
        glVertexAttribPointer(attribute0_location, 3, GL_FLOAT, 0, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffer1_id);
        glVertexAttribPointer(attribute1_location, 2, GL_FLOAT, 0, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glFinish();

        eglCopyBuffers(egl_display, egl_surface, native_pixmap);    /*attention: CopyBuffer would lock the DirectFB surface too*/

#if defined(EGL_API_DIRECTFB)
        ret = dfb_surface->Lock(dfb_surface, DSLF_WRITE, &pdata, &pitch);
        ASSERT_EQUAL(ret, DFB_OK);
#endif

        /* post the pixmap memory into the framebuffer to show */
        HI_COMMON_PostMemoryToFramebuffer(pdata, window_width * window_height * 4);

        sleep(1);

        /* clear the pixmap, post it into the framebuffer to show */
        HI_COMMON_ModifyVirtualMemory(&pdata, COLOR_RED, window_width * window_height);

        HI_COMMON_PostMemoryToFramebuffer(pdata, window_width * window_height * 4);

        sleep(1);

#if defined(EGL_API_DIRECTFB)
        ret = dfb_surface->Unlock(dfb_surface);
        ASSERT_EQUAL(ret, DFB_OK);
#endif

        fprintf(stderr, "success %d\n", i);
    }

    HI_COMMON_DestroyBuffer(buffer0_id);
    HI_COMMON_DestroyBuffer(buffer1_id);
    HI_COMMON_DestroyTexture(texture_id);
    HI_COMMON_DestroyProgram(program_id);
    HI_COMMON_DestroyShader(vshader_id);
    HI_COMMON_DestroyShader(fshader_id);

    ret = eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroyContext(egl_display, egl_context);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroySurface(egl_display, egl_surface);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglTerminate(egl_display);
    ASSERT_EQUAL(ret,EGL_TRUE);

#if defined(EGL_API_FBDEV)

    HI_COMMON_DestroyMMZMemory(pBuf);

    HI_COMMON_DestroyNativePixmap(native_pixmap);

    HI_COMMON_DestroyNativeDisplay(native_display);

#elif defined(EGL_API_DIRECTFB)

    HI_COMMON_DestroyDFBNativePixmap(native_pixmap);

    HI_COMMON_DestroyDFBNativeDisplay();

#endif

#if defined(FRAMEBUFFER_DEVICE_OPEN)
    HI_COMMON_CloseFramebufferDevice(framebuffer_fd);
#endif

    fprintf(stderr,"\n>>>>>>>>>>>>>>>>end>>>>>>>>>>>>>>>>\n");

    return 0;
}
