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

#ifdef _WIN32
 #define WIN32_LEAN_AND_MEAN 1
#endif

#include "common.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX
 #include <sys/time.h>
#else
 #include <windows.h>
#endif

#include "hi_3d_config.h"

#include "hi_type.h"
#include "hi_common.h"

/***************************************************************************************
***************************************************************************************/

// Computes file u32Length.
static HI_U32 SPHERE_COMMON_Flength(FILE * pFilePtr)
{
    HI_U32 u32Length;

    fseek(pFilePtr, 0, SEEK_END);
    u32Length = ftell(pFilePtr);
    fseek(pFilePtr, 0, SEEK_SET);
    return u32Length;
}

// Compile a vertex or pixel shader.
// returns 0: fail
//         1: success
HI_S32 SPHERE_COMMON_CompileShader(const HI_CHAR * pFileName, GLuint ShaderNumber)
{
    FILE * pFilePtr = NULL;

#ifdef UNDER_CE
    static wchar_t buffer[MAX_PATH + 1];
    HI_U32 i = GetModuleFileName(NULL, buffer, MAX_PATH);
    while (buffer[i - 1] != L'\\')
    {
        i--;
    }

    while (*pFileName != '\0')
    {
        buffer[i++] = (wchar_t)(*pFileName++);
    }

    buffer[i] = L'\0';
    pFilePtr = _wfopen(buffer, L"rb");
#else
    pFilePtr = fopen(pFileName, "rb");
#endif
    if (pFilePtr == NULL)
    {
        HI3D_TRACE("Can not open file: %s\n", pFileName);
        return 0;
    }

    HI_S32 u32Length = SPHERE_COMMON_Flength(pFilePtr);

    HI_CHAR * shaderSource = (HI_CHAR*)HI_MEM_Malloc(0, sizeof (HI_CHAR) * u32Length);
    if (shaderSource == NULL)
    {
        HI3D_TRACE("Out of memory.\n");
        return 0;
    }

    fread(shaderSource, u32Length, 1, pFilePtr);

    glShaderSource(ShaderNumber, 1, (const HI_CHAR**)&shaderSource, &u32Length);
    glCompileShader(ShaderNumber);

    HI_MEM_Free(0, shaderSource);
    fclose(pFilePtr);

    GLint compiled = 0;
    glGetShaderiv(ShaderNumber, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        // Retrieve error buffer u32BufferSize.
        GLint errorBufSize, errorLength;
        glGetShaderiv(ShaderNumber, GL_INFO_LOG_LENGTH, &errorBufSize);

        HI_CHAR * infoLog = (HI_CHAR*)HI_MEM_Malloc(0, errorBufSize * sizeof(HI_CHAR) + 1);
        if (!infoLog)
        {
            // Retrieve error.
            glGetShaderInfoLog(ShaderNumber, errorBufSize, &errorLength, infoLog);
            infoLog[errorBufSize + 1] = '\0';
            HI3D_TRACE("%s\n", infoLog);

            HI_MEM_Free(0, infoLog);
        }

        return 0;
    }

    return 1;
}

/***************************************************************************************
***************************************************************************************/

static HI_VOID SPHERE_COMMON_ConvertARGBtoABGR(HI_U32 * pBufferData, HI_U32 u32BufferSize)
{
    HI_U32 i;
    for (i = 0; i < u32BufferSize * u32BufferSize; i++, pBufferData++)
    {
        register  HI_U32 temp = *pBufferData;

        // Swap R and B.
        *pBufferData = (temp & 0xFF00FF00) | ((temp & 0xFF) << 16) | ((temp & 0xFF0000) >> 16);
    }
}

// loads a 256x256 ARGB (32bit) format pstCube map texture dds file.
SPHERE_COMMON_CubeTexture* SPHERE_COMMON_LoadCubeDDS(const HI_CHAR * pFileName)
{
    FILE * pFilePtr = NULL;

#ifdef UNDER_CE
    static wchar_t buffer[MAX_PATH + 1];
    HI_U32 i = GetModuleFileName(NULL, buffer, MAX_PATH);
    while (buffer[i - 1] != L'\\')
    {
        i--;
    }

    while (*pFileName != '\0')
    {
        buffer[i++] = (wchar_t)(*pFileName++);
    }

    buffer[i] = L'\0';
    pFilePtr = _wfopen(buffer, L"rb");
#else
    pFilePtr = fopen(pFileName, "rb");
#endif
    if (pFilePtr == NULL)
    {
        HI3D_TRACE("Can not open file: %s\n", pFileName);
        return NULL;
    }

    // read dds file routine.
    SPHERE_COMMON_CubeTexture * pstCbTexture = NULL;
    do
    {
        HI_U32 u32Dummy, u32BufferSize, offset, width;

        // read first 4 bytes, magic number.
        if (!fread(&u32Dummy, sizeof (HI_U32), 1, pFilePtr))
        {
            break;
        }

        // check magic number, should be "DDS ": 0x20534444.
        if (u32Dummy != 0x20534444UL)
        {
            HI3D_TRACE("File format incorrect.\n");
            break;
        }

        // second 4 bytes: texture offset in file.
        if (!fread(&u32Dummy, sizeof (HI_U32), 1, pFilePtr))
        {
            break;
        }

        offset = u32Dummy + 4;

        // no care.
        if (!fread(&u32Dummy, sizeof (HI_U32), 1, pFilePtr))
        {
            break;
        }

        // no care.
        if (!fread(&u32Dummy, sizeof (HI_U32), 1, pFilePtr))
        {
            break;
        }

        // texture width
        if (!fread(&width, sizeof (HI_U32), 1, pFilePtr))
        {
            break;
        }

        u32BufferSize = width * width;

        if (fseek(pFilePtr, offset, SEEK_SET))
        {
            break;
        }

        if ((pstCbTexture = (SPHERE_COMMON_CubeTexture*)HI_MEM_Malloc(0, sizeof (SPHERE_COMMON_CubeTexture))) == NULL)
        {
            break;
        }

        // read faces
        // positive x
        if ((pstCbTexture->posx = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->posx, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->posx, width);

        // negative x
        if (fseek(pFilePtr, 87380, SEEK_CUR))
        {
            // FIXME, assuming u32BufferSize is 256 and mipmaps included
            break;
        }

        if ((pstCbTexture->negx = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->negx, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->negx, width);

        // positive y
        if (fseek(pFilePtr, 87380, SEEK_CUR))
        {
            // FIXME, assuming u32BufferSize is 256 and mipmaps included
            break;
        }

        if ((pstCbTexture->posy = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->posy, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->posy, width);

        // negative y
        if (fseek(pFilePtr, 87380, SEEK_CUR))
        {
            // FIXME, assuming u32BufferSize is 256 and mipmaps included
            break;
        }

        if ((pstCbTexture->negy = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->negy, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->negy, width);

        // positive z
        if (fseek(pFilePtr, 87380, SEEK_CUR))
        {
            // FIXME, assuming u32BufferSize is 256 and mipmaps included
            break;
        }

        if ((pstCbTexture->posz = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->posz, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->posz, width);

        // negative z
        if (fseek(pFilePtr, 87380, SEEK_CUR))
        {
            // FIXME, assuming u32BufferSize is 256 and mipmaps included
            break;
        }

        if ((pstCbTexture->negz = (HI_U32*)HI_MEM_Malloc(0, sizeof (HI_U32) * u32BufferSize)) == NULL)
        {
            break;
        }

        if (fread(pstCbTexture->negz, sizeof (HI_U32), u32BufferSize, pFilePtr) != u32BufferSize)
        {
            break;
        }

        SPHERE_COMMON_ConvertARGBtoABGR(pstCbTexture->negz, width);

        pstCbTexture->img_size = width;

        fclose(pFilePtr);
        return pstCbTexture;
    } while (-1);

    // error handle
    HI3D_TRACE("Error while read DDS file.\n");

    fclose(pFilePtr);
    SPHERE_COMMON_DeleteCubeTexture(pstCbTexture);

    return NULL;
}

/***************************************************************************************
***************************************************************************************/

HI_VOID SPHERE_COMMON_DeleteCubeTexture(SPHERE_COMMON_CubeTexture * pstCube)
{
    HI_U32 i;
    if (pstCube != NULL)
    {
        HI_VOID * pointers[] = {
            (HI_VOID*)pstCube->posx,
            (HI_VOID*)pstCube->posy,
            (HI_VOID*)pstCube->posz,
            (HI_VOID*)pstCube->negx,
            (HI_VOID*)pstCube->negy,
            (HI_VOID*)pstCube->negz,
            (HI_VOID*)pstCube
        };

        for (i = 0; i < (sizeof (pointers) / sizeof (pointers[0])); i++)
        {
            if (pointers[i] != NULL)
            {
                HI_MEM_Free(0, pointers[i]);
            }
        }
    }
}

HI_ULONG SPHERE_COMMON_GetTimeMillis()
{
#ifdef LINUX
    static struct timeval stTimeStart = {0, 0};
    struct timeval stTimeNow;
    if ((stTimeStart.tv_sec == 0) && (stTimeStart.tv_usec == 0))
    {
        gettimeofday(&stTimeStart, NULL);
    }

    gettimeofday(&stTimeNow, NULL);

    return (HI_ULONG)(((HI_ULONG)(stTimeNow.tv_sec - stTimeStart.tv_sec)) * 1000
                           + (stTimeNow.tv_usec - stTimeStart.tv_usec) / 1000);
#else
    static long stTimeStart = 0;
    if (stTimeStart == 0)
    {
        stTimeStart = GetTickCount();
    }

    return (HI_ULONG)(GetTickCount() - stTimeStart);
#endif
}
