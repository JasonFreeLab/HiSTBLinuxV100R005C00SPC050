/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : es20_output_yuv_framebufferobject.c
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
#include <sys/time.h>
#include <string.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "GLES2/gl2ext.h"
#include "hifb.h"
#include "es20_common.h"

#define FHD_WIDTH  1920
#define FHD_HEIGHT 1080
#define HD_WIDTH  1280
#define HD_HEIGHT 720

#define TEXTURE_WIDTH  1024
#define TEXTURE_HEIGHT 684

#define YUV_FILE_IN  "yvu420sp_children.yuv"

#define VERT_SRC   "../res/shaders/pass_two_attribs.vert.glsl"
#if defined(EGL_API_UTGARD)
#define FRAG_SRC   "../res/shaders/texture_yuv_2_rgb.frag_utgard.glsl"
#elif defined(EGL_API_MIDGARD)
#define FRAG_SRC   "../res/shaders/texture_yuv_2_rgb.frag_midgard.glsl"
#endif

int attribute0_location = 0;    /* vetex coordinate */
int attribute1_location = 0;    /* texture coordinate */
int uniform0_location   = 0;
int uniform1_location   = 0;

unsigned int buffer0_id = 0;    /* glGenBuffers used */
unsigned int buffer1_id = 0;
unsigned int program_id = 0;
unsigned int vshader_id = 0;
unsigned int fshader_id = 0;
unsigned int texture_id_yuv_in[2];

HI_MMZ_BUF_S *pBuf_yuv_in[2] = {NULL};

GLfloat texturecoords_data_yuv[] =
{
   0.0f, 0.0f,
   1.0f, 0.0f,
   1.0f, 1.0f,
   0.0f, 1.0f
};

GLfloat vetex_data[] =
{
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
};

int main(int argc, char * argv[])
{
    fprintf(stderr, "\n>>>>>>>>>>>>>>>>start>>>>>>>>>>>>>>>>\n");

    NativeDisplayType native_display;
    EGLConfig egl_config;
    EGLContext egl_context;
    EGLDisplay egl_display;
    EGLSurface egl_window_surface;
    EGLImageKHR egl_image_yuv_in[2];
    NativePixmapType native_pixmap_yuv_in[2];
    NativeWindowType native_window;
    int matching_configs;
    int ret, i;
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
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE,
    };

    int ctxAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
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

    native_display = HI_COMMON_CreateNativeDisplay();

    native_window = HI_COMMON_CreateNativeWindow(window_width, window_height);

    /* create native pixmap*/
#if defined(EGL_API_UTGARD)

    for(i = 0; i < 2; i++)
    {
        pBuf_yuv_in[i] = HI_COMMON_CreateMMZMemory(texture_width * texture_height / (i+1));

        native_pixmap_yuv_in[i] = HI_COMMON_CreateNativePixmap(pBuf_yuv_in[i]->phyaddr, texture_width/(1+i), texture_height/(1+i), 0, 0, 0, 8*i, 8);
    }

#elif defined(EGL_API_MIDGARD)

    pBuf_yuv_in[0] = HI_COMMON_CreateMMZMemory(texture_width * texture_height * 3/2);

    native_pixmap_yuv_in[0] = HI_COMMON_CreateNativePixmap(pBuf_yuv_in[0]->phyaddr, texture_width, texture_height, EGL_PIXMAP_FORMAT_NV21_BT709_WIDE);

#endif

#endif

    /* >>>>>>>>>>>>>>>>>>>>>>>>>>> EGL process >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    egl_display = eglGetDisplay(native_display);
    ASSERT_NOT_EQUAL(egl_display, EGL_NO_DISPLAY);

    ret = eglBindAPI(EGL_OPENGL_ES_API);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglInitialize(egl_display ,NULL ,NULL);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglChooseConfig(egl_display, configAttribs, &egl_config, 1, &matching_configs);
    ASSERT_EQUAL(ret,EGL_TRUE);

    /* create egl surfaces */
    egl_window_surface = eglCreateWindowSurface(egl_display, egl_config, native_window, NULL);
    ASSERT_NOT_EQUAL(egl_window_surface, EGL_NO_SURFACE);

    egl_context = eglCreateContext(egl_display, egl_config, NULL, ctxAttribs);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglMakeCurrent(egl_display, egl_window_surface, egl_window_surface, egl_context);
    ASSERT_EQUAL(ret,EGL_TRUE);

    /* step 1: create vetex shader and fragment shader */
    vshader_id = HI_COMMON_CreateShader(VERT_SRC, GL_VERTEX_SHADER);
    fshader_id = HI_COMMON_CreateShader(FRAG_SRC, GL_FRAGMENT_SHADER);

    /* step 2: create program */
    program_id = HI_COMMON_CreateProgram(vshader_id, fshader_id);

    /* step 3: create buffer */
    buffer0_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*3*4, (const void*)vetex_data);
    buffer1_id = HI_COMMON_CreateBuffer(GL_ARRAY_BUFFER, sizeof(float)*2*4, (const void*)texturecoords_data_yuv);

#if defined(EGL_API_UTGARD)

    /* step 4: create eglimage */
    for (i = 0; i < 2; i++)
    {
        void *src = HI_COMMON_LoadFile(YUV_FILE_IN, texture_width*texture_height*i, texture_width*texture_height/(i+1), "r");
        memcpy( (void*)pBuf_yuv_in[i]->user_viraddr, src, texture_width*texture_height/(i+1) );
        free(src);
    }

    for(i = 0; i < 2; i++)
    {
        egl_image_yuv_in[i] = eglCreateImageKHR(egl_display, NULL, EGL_NATIVE_PIXMAP_KHR, (EGLClientBuffer)native_pixmap_yuv_in[i], NULL);
    }

    /* step 5: create texture */
    for(i = 0; i < 2; i++)
    {
        texture_id_yuv_in[i] = HI_COMMON_CreateTexture(GL_TEXTURE0+i, GL_TEXTURE_EXTERNAL_OES, GL_CLAMP_TO_EDGE, GL_NEAREST);

        glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, egl_image_yuv_in[i]);
    }

#elif defined(EGL_API_MIDGARD)

    /* step 4: create eglimage */
	memcpy(
			(void*)pBuf_yuv_in[0]->user_viraddr,
			(void*)HI_COMMON_LoadFile(YUV_FILE_IN, 0, texture_width * texture_height * 3/2, "r"),
			(texture_width * texture_height * 3/2)
		);

    /* step 5: create texture */
	egl_image_yuv_in[0] = eglCreateImageKHR(egl_display, NULL, EGL_NATIVE_PIXMAP_KHR, (EGLClientBuffer)native_pixmap_yuv_in[0], NULL);

	texture_id_yuv_in[0] = HI_COMMON_CreateTexture(GL_TEXTURE0, GL_TEXTURE_EXTERNAL_OES, GL_CLAMP_TO_EDGE, GL_NEAREST);

	glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, egl_image_yuv_in[0]);

#endif

    /* step 6: get the location of attribute and uniform */
    HI_COMMON_DestroyProgram(program_id);
    program_id = HI_COMMON_CreateProgram(vshader_id, fshader_id);

    attribute0_location = glGetAttribLocation(program_id, "aposition");
    glEnableVertexAttribArray(attribute0_location);

    attribute1_location = glGetAttribLocation(program_id, "atexcoord");
    glEnableVertexAttribArray(attribute1_location);

#if defined(EGL_API_UTGARD)

    uniform0_location = glGetUniformLocation(program_id, "luminance");
    glUniform1i(uniform0_location, 0);

    uniform1_location = glGetUniformLocation(program_id, "luminance_alpha");
    glUniform1i(uniform1_location, 1);

#elif defined(EGL_API_MIDGARD)

    uniform0_location = glGetUniformLocation(program_id, "YUV");
    glUniform1i(uniform0_location, 0);

#endif

    for(i = 0; i < 200; i++)
    {
        /* step 8: start opengles process */
        glViewport(0,0, window_width, window_height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, buffer0_id);
        glVertexAttribPointer(attribute0_location, 3, GL_FLOAT, 0, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffer1_id);
        glVertexAttribPointer(attribute1_location, 2, GL_FLOAT, 0, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        ret = eglSwapBuffers(egl_display, egl_window_surface);
        if (ret == EGL_TRUE)
        {
            fprintf(stderr, "success %d\n", i);
        }
        else
        {
            fprintf(stderr, "eglSwapBuffers failed\n");
            break;
        }
    }

    HI_COMMON_DestroyBuffer(buffer0_id);
    HI_COMMON_DestroyBuffer(buffer1_id);

#if defined(EGL_API_UTGARD)

    for(i = 0; i < 2; i++)
    {
        HI_COMMON_DestroyTexture(texture_id_yuv_in[i]);
    }

#elif defined(EGL_API_MIDGARD)

    HI_COMMON_DestroyTexture(texture_id_yuv_in[0]);

#endif

    HI_COMMON_DestroyProgram(program_id);
    HI_COMMON_DestroyShader(vshader_id);
    HI_COMMON_DestroyShader(fshader_id);

    ret = eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroyContext(egl_display, egl_context);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglDestroySurface(egl_display, egl_window_surface);
    ASSERT_EQUAL(ret,EGL_TRUE);

    ret = eglTerminate(egl_display);
    ASSERT_EQUAL(ret,EGL_TRUE);

#if defined(EGL_API_FBDEV)

#if defined(EGL_API_UTGARD)

    for(i = 0; i < 2; i++)
    {
        HI_COMMON_DestroyMMZMemory(pBuf_yuv_in[i]);
        HI_COMMON_DestroyNativePixmap(native_pixmap_yuv_in[i]);
    }

#elif defined(EGL_API_MIDGARD)

    HI_COMMON_DestroyMMZMemory(pBuf_yuv_in[0]);
    HI_COMMON_DestroyNativePixmap(native_pixmap_yuv_in[0]);

#endif

    HI_COMMON_DestroyNativeWindow(native_window);
    HI_COMMON_DestroyNativeDisplay(native_display);

#endif

#if defined(FRAMEBUFFER_DEVICE_OPEN)
    HI_COMMON_CloseFramebufferDevice(framebuffer_fd);
#endif

    fprintf(stderr, "\n>>>>>>>>>>>>>>>>end>>>>>>>>>>>>>>>>\n");

    return 0;
}
