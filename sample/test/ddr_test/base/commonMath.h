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

#ifndef _COMMONMATH_H_
#define _COMMONMATH_H_

#include <GLES2/gl2.h>

#include "hi_type.h"

#ifndef M_PI
 #define M_PI 3.14159265f
#endif

#define D3DX_PI 3.14159265f

typedef struct SPHERE_3DMATH_D3DXVECTOR3_S
{
    HI_FLOAT x, y, z;
}SPHERE_3DMATH_D3DXVECTOR3_S;

typedef struct SPHERE_3DMATH_D3DXVECTOR4_S
{
    HI_FLOAT x, y, z, w;
}SPHERE_3DMATH_D3DXVECTOR4_S;

typedef struct SPHERE_3DMATH_D3DXMATRIX_S
{
    HI_FLOAT _11, _12, _13, _14;
    HI_FLOAT _21, _22, _23, _24;
    HI_FLOAT _31, _32, _33, _34;
    HI_FLOAT _41, _42, _43, _44;
} SPHERE_3DMATH_D3DXMATRIX_S;

typedef struct SPHERE_3DMATH_STATE_S
{
    SPHERE_3DMATH_D3DXVECTOR3_S  m_Eye,
                                 m_Lookat,
                                 m_UpVec,
                                 m_EyeVector;

    HI_FLOAT                     m_Time,
                                 m_TimeStep,
                                 m_StepsPerCircle;

    SPHERE_3DMATH_D3DXMATRIX_S  m_ViewMatrix,
                                m_ProjMatrix,
                                m_ScaleMatrix,
                                m_RotateMatrix,
                                m_MoveMatrix,
                                m_WorldMatrix;

    HI_U32 FRAME_BUFFER_WIDTH,
           FRAME_BUFFER_HEIGHT;
}SPHERE_3DMATH_STATE_S;

// Setup matrices.
HI_VOID SPHERE_3DMATH_SetupMatrices(SPHERE_3DMATH_STATE_S* renderState);

// Setup transformation maxtrix.
HI_VOID SPHERE_3DMATH_SetupTransform(SPHERE_3DMATH_STATE_S* renderState,
                                                    SPHERE_3DMATH_D3DXMATRIX_S* matrix);

HI_VOID SPHERE_3DMATH_GetFrustum(GLfloat *matrix,
                                            GLfloat  left,
                                            GLfloat  right,
                                            GLfloat  bottom,
                                            GLfloat  top,
                                            GLfloat  zNear,
                                            GLfloat  zFar);

HI_VOID SPHERE_3DMATH_MatMult(GLfloat* Result,
                                         GLfloat* Mat1,
                                         GLfloat  Mat2[16]);

HI_VOID SPHERE_3DMATH_Sphere(GLfloat**  VertexArray,
                                        HI_U32        Width,
                                        HI_U32        u32Height,
                                        HI_U32        u32Colors,
                                        GLfloat**     ColorArray,
                                        HI_U32        u32Textures,
                                        GLfloat**     TextureArray,
                                        GLushort**    IndexArray,
                                        HI_U32 *      u32NumPrimitives,
                                        HI_U32*       u32NumIndices,
                                        HI_U32*       u32NumVertices);

// Set eye position.
HI_VOID SPHERE_3DMATH_SetEye(SPHERE_3DMATH_STATE_S* pstState,
                                        HI_FLOAT  X,
                                        HI_FLOAT  Y,
                                        HI_FLOAT  Z);

// Set object scale in each direction.
HI_VOID SPHERE_3DMATH_SetScale(SPHERE_3DMATH_STATE_S* pstState,
                                          HI_FLOAT  X,
                                          HI_FLOAT  Y,
                                          HI_FLOAT  Z);

// Set object rotation in each direction.
HI_VOID SPHERE_3DMATH_SetRotation(SPHERE_3DMATH_STATE_S* pstState,
                                             HI_FLOAT  X,
                                             HI_FLOAT  Y,
                                             HI_FLOAT  Z);

// Set object 3D position in each direction.
HI_VOID SPHERE_3DMATH_SetMove(SPHERE_3DMATH_STATE_S* pstState,
                                         HI_FLOAT  X,
                                         HI_FLOAT  Y,
                                         HI_FLOAT  Z);

// Set time step.
HI_VOID SPHERE_3DMATH_SetTimeStep(SPHERE_3DMATH_STATE_S* pstState,
                                                 HI_ULONG  ulTimeStep);

HI_VOID SPHERE_3DMATH_InitializeRenderState(SPHERE_3DMATH_STATE_S* pstState,
                                                       HI_U32    u32Width,
                                                       HI_U32    u32Height);

#endif
