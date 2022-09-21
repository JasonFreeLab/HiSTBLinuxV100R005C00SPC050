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

#ifndef _COMMON_H_
#define _COMMON_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

#include "hi_type.h"

// Compile a vertex or pixel shader.
HI_S32 SPHERE_COMMON_CompileShader(const HI_CHAR * pFileName, GLuint ShaderNumber);

typedef struct SPHERE_COMMON_CubeTexture
{
    HI_U32 * posx;
    HI_U32 * negx;
    HI_U32 * posy;
    HI_U32 * negy;
    HI_U32 * posz;
    HI_U32 * negz;
    HI_U32 img_size;
}SPHERE_COMMON_CubeTexture;

// loads a 256x256 ARGB (32bit) format pstCube map texture dds file.
SPHERE_COMMON_CubeTexture*  SPHERE_COMMON_LoadCubeDDS(const HI_CHAR * pFileName);

HI_VOID                        SPHERE_COMMON_DeleteCubeTexture(SPHERE_COMMON_CubeTexture * pstCube);

HI_ULONG                    SPHERE_COMMON_GetTimeMillis();

#endif
