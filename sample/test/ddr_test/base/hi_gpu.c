/****************************************************************************
 *
 *    Copyright (c) 2005 - 2010 by Vivante Corp.  All rights reserved.
 *
 *    The material in this file is confidential and contains trade secrets
 *    of Vivante Corporation. This is proprietary information owned by
 *    Vivante Corporation. No part of this work may be disclosed,
 *    reproduced, copied, transmitted, or used in any way for any purpose,
 *    without the express written permission of Vivante Corporation.
 *
 *****************************************************************************
 *
 *    Auto-generated file on 4/13/2010. Do not edit!!!
 *
 *****************************************************************************/

/*
 * OpenGL ES 2.0 Tutorial 4
 *
 * Draws a glass sphere inside a big sphere (enviroment mapping).
 * The glass sphere shows both reflection and refraction effects.
 */
#include <GLES2/gl2.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <sys/time.h>

#include "hi_unf_video.h"
#include "hi_unf_vo.h"

#include "common.h"
#include "commonMath.h"
#include "hi_egl.h"
#include "hi_texture.h"

#include "hi_type.h"
#include <pthread.h>
#include "hi_gpu.h"

#define TUTORIAL_NAME "OpenGL ES 2.0 Tutorial 4"


static pthread_t thread_id;
static pthread_mutex_t mutex;
static pthread_cond_t  cond;
static pthread_mutex_t lock_deinit;
static int flag_pause  = 0;
static int flag_deinit = 0;


static int flag_init = 0;

static HI_U32 frames      = 4;
static HI_U32 sampling    = 0;
static HI_U32 fps_print   = 0;

// Global Variables
static GLuint programHandleGlass;
static GLuint programHandleBgrnd;

static GLuint vertShaderNum, pixelShaderNum, pixelShaderNum2;

// Generic used buffer
static GLuint bufs[5];

// hold sphere data
static HI_U32 numVertices, numFaces, numIndices;
static GLfloat* sphereVertices = NULL;
static GLushort* indices = NULL;

// attribute and uniform handle.
static GLint locVertices[2], locTransformMat[2], locRadius[2], locEyePos[2],locSamplerCb[2];

// render state
static  SPHERE_3DMATH_STATE_S renderState;

static  SPHERE_3DMATH_D3DXMATRIX_S transformMatrix;

HI_U32 HIADP_Disp_Init(HI_UNF_ENC_FMT_E enFormat);
HI_U32 HIADP_Disp_DeInit(HI_VOID);

#ifdef ADVCA_SUPPORT
#define GPU_SOURCE_FILENAME_VS_ES20T4           "/home/stb/res/ddr_test/gpu/vs_es20t4.vert"
#define GPU_SOURCE_FILENAME_VS_ES20T4_GLASS     "/home/stb/res/ddr_test/gpu/ps_es20t4_glass.frag"
#define GPU_SOURCE_FILENAME_VS_ES20T4_BGRND     "/home/stb/res/ddr_test/gpu/ps_es20t4_bgrnd.frag"
#define GPU_SOURCE_FILENAME_VS_STPETERS         "/home/stb/res/ddr_test/gpu/stpeters_cross_mipmap_256.dds"
#else
#define GPU_SOURCE_FILENAME_VS_ES20T4           "../../res/ddr_test/gpu/vs_es20t4.vert"
#define GPU_SOURCE_FILENAME_VS_ES20T4_GLASS     "../../res/ddr_test/gpu/ps_es20t4_glass.frag"
#define GPU_SOURCE_FILENAME_VS_ES20T4_BGRND     "../../res/ddr_test/gpu/ps_es20t4_bgrnd.frag"
#define GPU_SOURCE_FILENAME_VS_STPETERS         "../../res/ddr_test/gpu/stpeters_cross_mipmap_256.dds"
#endif

/***************************************************************************************
***************************************************************************************/

HI_VOID SPHERE_EglInit(HI_U32 width, HI_U32 height)
{
    SPHERE_3DMATH_Sphere(&sphereVertices, 40, 60, 0, NULL, 0, NULL, &indices, &numFaces, &numIndices, &numVertices);

    // Grab location of shader attributes.
    locVertices[0] = glGetAttribLocation(programHandleGlass, "my_Vertex");
    locVertices[1] = glGetAttribLocation(programHandleBgrnd, "my_Vertex");

    locRadius[0] = glGetUniformLocation(programHandleGlass, "my_Radius");
    locRadius[1] = glGetUniformLocation(programHandleBgrnd, "my_Radius");

    locEyePos[0] = glGetUniformLocation(programHandleGlass, "my_EyePos");
    locEyePos[1] = glGetUniformLocation(programHandleBgrnd, "my_EyePos");

    // Transform Matrix is uniform for all vertices here.
    locTransformMat[0] = glGetUniformLocation(programHandleGlass, "my_TransformMatrix");
    locTransformMat[1] = glGetUniformLocation(programHandleBgrnd, "my_TransformMatrix");

    glEnableVertexAttribArray(locVertices[0]);
    glEnableVertexAttribArray(locVertices[1]);

    glGenBuffers(2, bufs);
    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, bufs[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), sphereVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(locVertices[0], 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(locVertices[1], 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);

    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Textures
    // Set s0 for samplerCube location.
    locSamplerCb[0] = glGetUniformLocation(programHandleGlass, "samplerCb");
    locSamplerCb[1] = glGetUniformLocation(programHandleBgrnd, "samplerCb");

    GLuint textureHandle;
    glGenTextures(1, &textureHandle);
     SPHERE_COMMON_CubeTexture* cubeTexData = SPHERE_COMMON_LoadCubeDDS(GPU_SOURCE_FILENAME_VS_STPETERS);
    if ((glGetError() != GL_NO_ERROR) || (cubeTexData == NULL))
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    HI_U32 texSize = cubeTexData->img_size;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandle);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posx);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negx);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posy);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negy);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posz);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negz);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Deletes the texture data, it's now in OpenGL memory.
    SPHERE_COMMON_DeleteCubeTexture(cubeTexData);

    SPHERE_3DMATH_InitializeRenderState(&renderState, width, height);

    // Set eye position.
    SPHERE_3DMATH_SetEye(&renderState, 0, 0, -3.8f);

    // Enable needed states.
    glEnable(GL_CULL_FACE);
}


HI_U64 hi_egl_get_time_ns( HI_VOID )
{
    struct timeval tv;
    HI_U64 time_ns;

    gettimeofday(&tv, NULL);

    time_ns  = ((HI_U64) tv.tv_sec) * 1000000000;
    time_ns += ((HI_U64) tv.tv_usec) * 1000;
    return time_ns;
}


/***************************************************************************************
***************************************************************************************/

static HI_UNF_ENC_FMT_E SPHERE_FormatStringToEnum(HI_CHAR *str)
{
    if (NULL == str)
    {
        return HI_UNF_ENC_FMT_BUTT;
    }

    if (!strcasecmp(str, "1080P_60"))
    {
        return HI_UNF_ENC_FMT_1080P_60;
    }
    else if (!strcasecmp(str, "1080P_50"))
    {
        return HI_UNF_ENC_FMT_1080P_50;
    }
    else if (!strcasecmp(str, "1080P_30"))
    {
        return HI_UNF_ENC_FMT_1080P_30;
    }
    else if (!strcasecmp(str, "1080P_25"))
    {
        return HI_UNF_ENC_FMT_1080P_25;
    }
    else if (!strcasecmp(str, "1080P_24"))
    {
        return HI_UNF_ENC_FMT_1080P_24;
    }
    else if (!strcasecmp(str, "1080i_60"))
    {
        return HI_UNF_ENC_FMT_1080i_60;
    }
    else if (!strcasecmp(str, "1080i_50"))
    {
        return HI_UNF_ENC_FMT_1080i_50;
    }
    else if (!strcasecmp(str, "720P_60"))
    {
        return HI_UNF_ENC_FMT_720P_60;
    }
    else if (!strcasecmp(str, "720P_50"))
    {
        return HI_UNF_ENC_FMT_720P_50;
    }
    else if (!strcasecmp(str, "576P_50"))
    {
        return HI_UNF_ENC_FMT_576P_50;
    }
    else if (!strcasecmp(str, "480P_60"))
    {
        return HI_UNF_ENC_FMT_480P_60;
    }
    else if (!strcasecmp(str, "PAL"))
    {
        return HI_UNF_ENC_FMT_PAL;
    }
    else if (!strcasecmp(str, "PAL_N"))
    {
        return HI_UNF_ENC_FMT_PAL_N;
    }
    else if (!strcasecmp(str, "PAL_Nc"))
    {
        return HI_UNF_ENC_FMT_PAL_Nc;
    }
    else if (!strcasecmp(str, "NTSC"))
    {
        return HI_UNF_ENC_FMT_NTSC;
    }
    else if (!strcasecmp(str, "NTSC_J"))
    {
        return HI_UNF_ENC_FMT_NTSC_J;
    }
    else if (!strcasecmp(str, "NTSC_PAL_M"))
    {
        return HI_UNF_ENC_FMT_NTSC_PAL_M;
    }
    else if (!strcasecmp(str, "SECAM_SIN"))
    {
        return HI_UNF_ENC_FMT_SECAM_SIN;
    }
    else if (!strcasecmp(str, "SECAM_COS"))
    {
        return HI_UNF_ENC_FMT_SECAM_COS;
    }
    else if (!strcasecmp(str, "2160P_24"))
    {
        return HI_UNF_ENC_FMT_3840X2160_24;
    }
    else if (!strcasecmp(str, "2160P_25"))
    {
        return HI_UNF_ENC_FMT_3840X2160_25;
    }
    else if (!strcasecmp(str, "2160P_30"))
    {
        return HI_UNF_ENC_FMT_3840X2160_30;
    }
    else if (!strcasecmp(str, "2160P_50"))
    {
        return HI_UNF_ENC_FMT_3840X2160_50;
    }
    else if (!strcasecmp(str, "2160P_60"))
    {
        return HI_UNF_ENC_FMT_3840X2160_60;
    }
    else if (!strcasecmp(str, "4096X2160_24"))
    {
        return HI_UNF_ENC_FMT_4096X2160_24;
    }
    else if (!strcasecmp(str, "4096X2160_25"))
    {
        return HI_UNF_ENC_FMT_4096X2160_25;
    }
    else if (!strcasecmp(str, "4096X2160_30"))
    {
        return HI_UNF_ENC_FMT_4096X2160_30;
    }
    else if (!strcasecmp(str, "4096X2160_50"))
    {
        return HI_UNF_ENC_FMT_4096X2160_50;
    }
    else if (!strcasecmp(str, "4096X2160_60"))
    {
        return HI_UNF_ENC_FMT_4096X2160_60;
    }

    return HI_UNF_ENC_FMT_BUTT;
}

HI_UNF_ENC_FMT_E SPHERE_ParseCommandLine(HI_U32 argc, HI_CHAR * argv[])
{
    HI_U32 i;
    if (argc <= 1)
    {
        printf("Usage: %s fmt f[value] s[value]\n", argv[0]);
        printf("\tfmt:\tthe display fmt, default value is 1080P_60. 2160P_60 | 1080P_60 | 720P_60\n");
        printf("\tf:\tthe number of frames, default value is %d\n", frames);
        printf("\ts:\tthe sampling, default value is %d\n", sampling);
        printf("\nFor example:\n\t%s 1080P_60 f2000 s4\n\n", argv[0]);
    }

    for (i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
            case 'f':
                frames = atoi (&argv[i][1]);
                break;

            case 's':
                sampling = atoi (&argv[i][1]);
                break;

    #if 0
            case '1':
                fps_print = 1;
                break;
    #endif
        }
    }

    return SPHERE_FormatStringToEnum(argv[1]);
}

/***************************************************************************************
***************************************************************************************/


HI_S32 SPHERE_DeInit()
{
    glDisableVertexAttribArray(locVertices[0]);
    glDisableVertexAttribArray(locVertices[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, bufs);

    if (sphereVertices != NULL)
    {
        free(sphereVertices);
    }

    if (indices != NULL)
    {
        free(indices);
    }
    // cleanup
    glDeleteShader(vertShaderNum);
    glDeleteShader(pixelShaderNum);
    glDeleteShader(pixelShaderNum2);
    glDeleteProgram(programHandleGlass);
    glDeleteProgram(programHandleBgrnd);
    glUseProgram(0);

    glFinish();

    hi_egl_destroy();

#ifdef DISP_INIT_IN_SPHERE
    HIADP_Disp_DeInit();
#endif

    return 0;
}

// Program entry.
HI_S32 SPHERE_Init( )
{
#ifdef DISP_INIT_IN_SPHERE
    HI_U32 ret;
#endif

    HI_UNF_ENC_FMT_E fmt;
    HI_U32 width;
    HI_U32 height;

    fmt = HI_UNF_ENC_FMT_1080P_60;

    switch (fmt)
    {
        case HI_UNF_ENC_FMT_1080P_60:
        case HI_UNF_ENC_FMT_1080P_50:
        case HI_UNF_ENC_FMT_1080P_30:
        case HI_UNF_ENC_FMT_1080P_25:
        case HI_UNF_ENC_FMT_1080P_24:
        case HI_UNF_ENC_FMT_1080i_60:
        case HI_UNF_ENC_FMT_1080i_50:
            width    = 1920;
            height    = 1080;
            break;

        case HI_UNF_ENC_FMT_720P_60:
        case HI_UNF_ENC_FMT_720P_50:
            width    = 1280;
            height    = 720;
            break;

        case HI_UNF_ENC_FMT_3840X2160_24:
        case HI_UNF_ENC_FMT_3840X2160_25:
        case HI_UNF_ENC_FMT_3840X2160_30:
        case HI_UNF_ENC_FMT_3840X2160_50:
        case HI_UNF_ENC_FMT_3840X2160_60:
            width    = 3840;
            height    = 2160;
            break;

        case HI_UNF_ENC_FMT_4096X2160_24:
        case HI_UNF_ENC_FMT_4096X2160_25:
        case HI_UNF_ENC_FMT_4096X2160_30:
        case HI_UNF_ENC_FMT_4096X2160_50:
        case HI_UNF_ENC_FMT_4096X2160_60:
            width    = 4096;
            height    = 2160;
            break;

        default:
            width    = 1920;
            height    = 1080;

            fmt = HI_UNF_ENC_FMT_1080P_60;

    }

    width    = 1920;
    height    = 1080;

#ifdef DISP_INIT_IN_SPHERE
    HIADP_Disp_Init(fmt);

    // 虚拟屏幕大小要与UI大小一致
    ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, width, height);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_DISP_SetVirtualScreen failed 0x%x\n", ret);
    }

    sleep(1);
#endif

    hi_egl_setup(0, 0, width, height, sampling, 1);

    vertShaderNum   = glCreateShader(GL_VERTEX_SHADER);
    pixelShaderNum  = glCreateShader(GL_FRAGMENT_SHADER);
    pixelShaderNum2 = glCreateShader(GL_FRAGMENT_SHADER);

    if (SPHERE_COMMON_CompileShader(GPU_SOURCE_FILENAME_VS_ES20T4, vertShaderNum) == 0)
    {
        return 0;
    }

    if (SPHERE_COMMON_CompileShader(GPU_SOURCE_FILENAME_VS_ES20T4_GLASS, pixelShaderNum) == 0)
    {
        return 0;
    }

    if (SPHERE_COMMON_CompileShader(GPU_SOURCE_FILENAME_VS_ES20T4_BGRND, pixelShaderNum2) == 0)
    {
        return 0;
    }

    programHandleGlass = glCreateProgram();
    glAttachShader(programHandleGlass, vertShaderNum);
    glAttachShader(programHandleGlass, pixelShaderNum);
    glLinkProgram(programHandleGlass);

    programHandleBgrnd = glCreateProgram();
    glAttachShader(programHandleBgrnd, vertShaderNum);
    glAttachShader(programHandleBgrnd, pixelShaderNum2);
    glLinkProgram(programHandleBgrnd);

    if ((programHandleGlass == 0) || (programHandleBgrnd == 0))
    {
        return 0;
    }

    SPHERE_EglInit(width, height);

    return 0;
}


// Actual rendering here.
HI_VOID SPHERE_Render( )
{

    HI_U64 time_save, time_record;
    HI_U32 framescnt = 0;

    SPHERE_Init( );

    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(flag_pause == 1)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        time_save = hi_egl_get_time_ns();

        SPHERE_3DMATH_SetupTransform(&renderState, &transformMatrix);

        // SPHERE_Render background sphere.
        glCullFace(GL_BACK);
        glUseProgram(programHandleBgrnd);
        glUniform1i(locSamplerCb[1], 0);
        glUniform1f(locRadius[1], 10.0f);
        glUniform3fv(locEyePos[1], 1, (GLfloat*)&renderState.m_EyeVector);
        glUniformMatrix4fv(locTransformMat[1], 1, GL_FALSE, (GLfloat*)&transformMatrix);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

        // SPHERE_Render glass ball.
        glCullFace(GL_FRONT);
        glUseProgram(programHandleGlass);
        glUniform1i(locSamplerCb[0], 0);
        glUniform1f(locRadius[0], 1.0f);
        glUniform3fv(locEyePos[0], 1, (GLfloat*)&renderState.m_EyeVector);
        glUniformMatrix4fv(locTransformMat[0], 1, GL_FALSE, (GLfloat*)&transformMatrix);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

        // swap display with drawn surface.
        hi_egl_swap();

        if (fps_print)
        {
            if (++framescnt == 1000)
            {
                time_record = hi_egl_get_time_ns();
                fprintf(stderr, "fps is %f...\n", 1000.0 * 1000.0 * 1000.0 * 1000 / (time_record - time_save));
                framescnt = 0;
                time_save = time_record;
            }
        }

        pthread_mutex_lock(&lock_deinit);
        if(flag_deinit == 1)
        {
            SPHERE_DeInit();

            pthread_exit(0);
        }
        pthread_mutex_unlock(&lock_deinit);

        flag_init = 1;
    }
}

HI_S32 HI_SPHERE_Pause()
{
    pthread_mutex_lock(&mutex);
    flag_pause = 1;
    pthread_mutex_unlock(&mutex);

    return 0;
}

HI_S32 HI_SPHERE_Resume()
{
    pthread_mutex_lock(&mutex);
    flag_pause = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return 0;
}

HI_S32 HI_SPHERE_Init( )
{
    flag_deinit = 0;
    flag_pause  = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&lock_deinit, NULL);

    pthread_create(&thread_id, NULL, (HI_VOID *)SPHERE_Render, NULL);
    if(thread_id == 0)
        printf("thread creat error!\n");

    return 0;
}

HI_S32 HI_SPHERE_DeInit()
{
    if(flag_init == 1)
    {
        pthread_mutex_lock(&lock_deinit);
        flag_deinit = 1;
        pthread_mutex_unlock(&lock_deinit);
    }

    sleep(10);

    return 0;
}

