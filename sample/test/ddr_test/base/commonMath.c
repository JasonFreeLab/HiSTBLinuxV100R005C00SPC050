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

#include "commonMath.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "hi_type.h"
#include "hi_common.h"

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixRotationX(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                         HI_FLOAT  fAngle)
{
    HI_FLOAT _sin = (HI_FLOAT)sin(fAngle);
    HI_FLOAT _cos = (HI_FLOAT)cos(fAngle);

    pstOut->_11 = 1.0f;
    pstOut->_12 = 0.0f;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = _cos;
    pstOut->_23 = _sin;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = -_sin;
    pstOut->_33 = _cos;
    pstOut->_34 = 0.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = 0.0f;
    pstOut->_44 = 1.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixRotationY(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                        HI_FLOAT  fAngle)
{
    HI_FLOAT _sin = (HI_FLOAT)sin(fAngle);
    HI_FLOAT _cos = (HI_FLOAT)cos(fAngle);

    pstOut->_11 = _cos;
    pstOut->_12 = 0.0f;
    pstOut->_13 = -_sin;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = 1.0f;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = _sin;
    pstOut->_32 = 0.0f;
    pstOut->_33 = _cos;
    pstOut->_34 = 0.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = 0.0f;
    pstOut->_44 = 1.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixRotationZ(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                        HI_FLOAT  fAngle)
{
    HI_FLOAT _sin = (HI_FLOAT)sin(fAngle);
    HI_FLOAT _cos = (HI_FLOAT)cos(fAngle);

    pstOut->_11 = _cos;
    pstOut->_12 = _sin;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = -_sin;
    pstOut->_22 = _cos;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = 0.0f;
    pstOut->_33 = 1.0f;
    pstOut->_34 = 0.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = 0.0f;
    pstOut->_44 = 1.0f;

    return pstOut;
}

#if 0
static HI_VOID SPHERE_3DMATH_D3DXMatrixRotationZ(GLfloat* mat,
                                 HI_FLOAT    fAngle)
{
    // Set up rotation matrix rotating by fAngle around Z axis.
    HI_FLOAT _sin = (HI_FLOAT)sin(fAngle);
    HI_FLOAT _cos = (HI_FLOAT)cos(fAngle);

    mat[0]  = _cos;
    mat[1]  = _sin;
    mat[2]  = 0.0f;
    mat[3]  = 0.0f;
    mat[4]  = -_sin;
    mat[5]  = _cos;
    mat[6]  = 0.0f;
    mat[7]  = 0.0f;
    mat[8]  = 0.0f;
    mat[9]  = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

#endif

static SPHERE_3DMATH_D3DXVECTOR4_S* SPHERE_3DMATH__D3DXVec3Transform(SPHERE_3DMATH_D3DXVECTOR4_S* pstOut,
                                                                                           SPHERE_3DMATH_D3DXVECTOR3_S* pstVector1,
                                                                                           SPHERE_3DMATH_D3DXMATRIX_S*  pstMatrix)
{
    pstOut->x = pstVector1->x * pstMatrix->_11 + pstVector1->y * pstMatrix->_21 + pstVector1->z * pstMatrix->_31 + pstMatrix->_41;
    pstOut->y = pstVector1->x * pstMatrix->_12 + pstVector1->y * pstMatrix->_22 + pstVector1->z * pstMatrix->_32 + pstMatrix->_42;
    pstOut->z = pstVector1->x * pstMatrix->_13 + pstVector1->y * pstMatrix->_23 + pstVector1->z * pstMatrix->_33 + pstMatrix->_43;
    pstOut->w = pstVector1->x * pstMatrix->_14 + pstVector1->y * pstMatrix->_24 + pstVector1->z * pstMatrix->_34 + pstMatrix->_44;

    return pstOut;
}

static SPHERE_3DMATH_D3DXVECTOR3_S* SPHERE_3DMATH_D3DXVec3Cross(SPHERE_3DMATH_D3DXVECTOR3_S* pstOut,
                                                                                   SPHERE_3DMATH_D3DXVECTOR3_S* pstVector1,
                                                                                   SPHERE_3DMATH_D3DXVECTOR3_S* pstVector2)
{
    SPHERE_3DMATH_D3DXVECTOR3_S v;

    v.x = pstVector1->y * pstVector2->z - pstVector1->z * pstVector2->y;
    v.y = pstVector1->z * pstVector2->x - pstVector1->x * pstVector2->z;
    v.z = pstVector1->x * pstVector2->y - pstVector1->y * pstVector2->x;

    *pstOut = v;
    return pstOut;
}

static SPHERE_3DMATH_D3DXVECTOR3_S* SPHERE_3DMATH_D3DXVec3Subtract(SPHERE_3DMATH_D3DXVECTOR3_S* pstOut,
                                                                                      SPHERE_3DMATH_D3DXVECTOR3_S* pstVector1,
                                                                                      SPHERE_3DMATH_D3DXVECTOR3_S* pstVector2)
{
    pstOut->x = pstVector1->x - pstVector2->x;
    pstOut->y = pstVector1->y - pstVector2->y;
    pstOut->z = pstVector1->z - pstVector2->z;

    return pstOut;
}

static HI_FLOAT SPHERE_3DMATH_3DMATH_D3DXVec3Dot(SPHERE_3DMATH_D3DXVECTOR3_S* pstVector1,
                                                                       SPHERE_3DMATH_D3DXVECTOR3_S* pstVector2)
{
    return (pstVector1->x * pstVector2->x + pstVector1->y * pstVector2->y + pstVector1->z * pstVector2->z);
}

static SPHERE_3DMATH_D3DXVECTOR3_S* SPHERE_3DMATH_D3DXVec3Normalize(SPHERE_3DMATH_D3DXVECTOR3_S* pstOut,
                                                                                      SPHERE_3DMATH_D3DXVECTOR3_S* pstVector1)
{
    HI_FLOAT x2  = pstVector1->x * pstVector1->x;
    HI_FLOAT y2  = pstVector1->y * pstVector1->y;
    HI_FLOAT z2  = pstVector1->z * pstVector1->z;
    HI_FLOAT len = sqrtf(x2 + y2 + z2);

    pstOut->x = pstVector1->x / len;
    pstOut->y = pstVector1->y / len;
    pstOut->z = pstVector1->z / len;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixLookAtLH(SPHERE_3DMATH_D3DXMATRIX_S*  pstOut,
                                                                                       SPHERE_3DMATH_D3DXVECTOR3_S* pstVectorEye,
                                                                                       SPHERE_3DMATH_D3DXVECTOR3_S* pstVectorAt,
                                                                                       SPHERE_3DMATH_D3DXVECTOR3_S* pstVectorUp)
{
    SPHERE_3DMATH_D3DXVECTOR3_S xaxis, yaxis, zaxis, tmp;

    SPHERE_3DMATH_D3DXVec3Subtract(&tmp, pstVectorAt, pstVectorEye);
    SPHERE_3DMATH_D3DXVec3Normalize(&zaxis, &tmp);       //     zaxis = normal(At - Eye)

    SPHERE_3DMATH_D3DXVec3Cross(&tmp, pstVectorUp, &zaxis);
    SPHERE_3DMATH_D3DXVec3Normalize(&xaxis, &tmp);       //   xaxis = normal(cross(Up, zaxis))

    SPHERE_3DMATH_D3DXVec3Cross(&yaxis, &zaxis, &xaxis);  //   yaxis = cross(zaxis, xaxis)

    pstOut->_11 = xaxis.x;
    pstOut->_12 = yaxis.x;
    pstOut->_13 = zaxis.x;
    pstOut->_14 = 0.0f;
    pstOut->_21 = xaxis.y;
    pstOut->_22 = yaxis.y;
    pstOut->_23 = zaxis.y;
    pstOut->_24 = 0.0f;
    pstOut->_31 = xaxis.z;
    pstOut->_32 = yaxis.z;
    pstOut->_33 = zaxis.z;
    pstOut->_34 = 0.0f;

    pstOut->_41 = SPHERE_3DMATH_3DMATH_D3DXVec3Dot(&xaxis, pstVectorEye) * -1.0f;
    pstOut->_42 = SPHERE_3DMATH_3DMATH_D3DXVec3Dot(&yaxis, pstVectorEye) * -1.0f;
    pstOut->_43 = SPHERE_3DMATH_3DMATH_D3DXVec3Dot(&zaxis, pstVectorEye) * -1.0f;
    pstOut->_44 = 1.0f;           //    -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixPerspectiveFovLH(SPHERE_3DMATH_D3DXMATRIX_S *pstOut,
                                                                                                   HI_FLOAT       fFovy,
                                                                                                   HI_FLOAT       fAspect,
                                                                                                   HI_FLOAT       fZn,
                                                                                                   HI_FLOAT       fZf)
{
    HI_FLOAT yScale = 1.0f / (HI_FLOAT)tan(fFovy / 2);
    HI_FLOAT xScale = yScale / fAspect;

    pstOut->_11 = xScale;
    pstOut->_12 = 0.0f;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = yScale;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = 0.0f;
    pstOut->_33 = fZf / (fZf - fZn);
    pstOut->_34 = 1.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = -fZn * fZf / (fZf - fZn);
    pstOut->_44 = 0.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixMultiply(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                       SPHERE_3DMATH_D3DXMATRIX_S* pstVectorM1,
                                                                                       SPHERE_3DMATH_D3DXMATRIX_S* pstVectorM2)
{
    SPHERE_3DMATH_D3DXMATRIX_S tmpOut;

    tmpOut._11 = pstVectorM1->_11 * pstVectorM2->_11 + pstVectorM1->_12 * pstVectorM2->_21 + pstVectorM1->_13 * pstVectorM2->_31 + pstVectorM1->_14 * pstVectorM2->_41;
    tmpOut._12 = pstVectorM1->_11 * pstVectorM2->_12 + pstVectorM1->_12 * pstVectorM2->_22 + pstVectorM1->_13 * pstVectorM2->_32 + pstVectorM1->_14 * pstVectorM2->_42;
    tmpOut._13 = pstVectorM1->_11 * pstVectorM2->_13 + pstVectorM1->_12 * pstVectorM2->_23 + pstVectorM1->_13 * pstVectorM2->_33 + pstVectorM1->_14 * pstVectorM2->_43;
    tmpOut._14 = pstVectorM1->_11 * pstVectorM2->_14 + pstVectorM1->_12 * pstVectorM2->_24 + pstVectorM1->_13 * pstVectorM2->_34 + pstVectorM1->_14 * pstVectorM2->_44;

    tmpOut._21 = pstVectorM1->_21 * pstVectorM2->_11 + pstVectorM1->_22 * pstVectorM2->_21 + pstVectorM1->_23 * pstVectorM2->_31 + pstVectorM1->_24 * pstVectorM2->_41;
    tmpOut._22 = pstVectorM1->_21 * pstVectorM2->_12 + pstVectorM1->_22 * pstVectorM2->_22 + pstVectorM1->_23 * pstVectorM2->_32 + pstVectorM1->_24 * pstVectorM2->_42;
    tmpOut._23 = pstVectorM1->_21 * pstVectorM2->_13 + pstVectorM1->_22 * pstVectorM2->_23 + pstVectorM1->_23 * pstVectorM2->_33 + pstVectorM1->_24 * pstVectorM2->_43;
    tmpOut._24 = pstVectorM1->_21 * pstVectorM2->_14 + pstVectorM1->_22 * pstVectorM2->_24 + pstVectorM1->_23 * pstVectorM2->_34 + pstVectorM1->_24 * pstVectorM2->_44;

    tmpOut._31 = pstVectorM1->_31 * pstVectorM2->_11 + pstVectorM1->_32 * pstVectorM2->_21 + pstVectorM1->_33 * pstVectorM2->_31 + pstVectorM1->_34 * pstVectorM2->_41;
    tmpOut._32 = pstVectorM1->_31 * pstVectorM2->_12 + pstVectorM1->_32 * pstVectorM2->_22 + pstVectorM1->_33 * pstVectorM2->_32 + pstVectorM1->_34 * pstVectorM2->_42;
    tmpOut._33 = pstVectorM1->_31 * pstVectorM2->_13 + pstVectorM1->_32 * pstVectorM2->_23 + pstVectorM1->_33 * pstVectorM2->_33 + pstVectorM1->_34 * pstVectorM2->_43;
    tmpOut._34 = pstVectorM1->_31 * pstVectorM2->_14 + pstVectorM1->_32 * pstVectorM2->_24 + pstVectorM1->_33 * pstVectorM2->_34 + pstVectorM1->_34 * pstVectorM2->_44;

    tmpOut._41 = pstVectorM1->_41 * pstVectorM2->_11 + pstVectorM1->_42 * pstVectorM2->_21 + pstVectorM1->_43 * pstVectorM2->_31 + pstVectorM1->_44 * pstVectorM2->_41;
    tmpOut._42 = pstVectorM1->_41 * pstVectorM2->_12 + pstVectorM1->_42 * pstVectorM2->_22 + pstVectorM1->_43 * pstVectorM2->_32 + pstVectorM1->_44 * pstVectorM2->_42;
    tmpOut._43 = pstVectorM1->_41 * pstVectorM2->_13 + pstVectorM1->_42 * pstVectorM2->_23 + pstVectorM1->_43 * pstVectorM2->_33 + pstVectorM1->_44 * pstVectorM2->_43;
    tmpOut._44 = pstVectorM1->_41 * pstVectorM2->_14 + pstVectorM1->_42 * pstVectorM2->_24 + pstVectorM1->_43 * pstVectorM2->_34 + pstVectorM1->_44 * pstVectorM2->_44;

    *pstOut = tmpOut;
    return pstOut;
}

// Setup matrices.
HI_VOID SPHERE_3DMATH_SetupMatrices(SPHERE_3DMATH_STATE_S* renderState)
{
    // Compute the fAngle and advance the time counter.
    HI_FLOAT fAngle = renderState->m_Time * (2.0f * M_PI) / renderState->m_StepsPerCircle;

    renderState->m_Time += renderState->m_TimeStep;

    SPHERE_3DMATH_D3DXMATRIX_S eyeMatrix;
    SPHERE_3DMATH_D3DXMatrixRotationY(&eyeMatrix, fAngle);

    // Set eye position.
    SPHERE_3DMATH_D3DXVECTOR4_S eyeTransform;
    SPHERE_3DMATH__D3DXVec3Transform(&eyeTransform, &renderState->m_Eye, &eyeMatrix);
    renderState->m_EyeVector.x = eyeTransform.x;
    renderState->m_EyeVector.y = eyeTransform.y;
    renderState->m_EyeVector.z = eyeTransform.z;

    SPHERE_3DMATH_D3DXMatrixLookAtLH(&renderState->m_ViewMatrix,
                        &renderState->m_EyeVector,
                        &renderState->m_Lookat,
                        &renderState->m_UpVec);

    HI_FLOAT fAspect = (HI_FLOAT) (renderState->FRAME_BUFFER_WIDTH) / (HI_FLOAT) (renderState->FRAME_BUFFER_HEIGHT);

    SPHERE_3DMATH_D3DXMatrixPerspectiveFovLH(&renderState->m_ProjMatrix,
                                D3DX_PI / 4.0f,
                                fAspect,
                                1.0f,
                                100.0f);
}

// Setup transformation maxtrix.
HI_VOID SPHERE_3DMATH_SetupTransform(SPHERE_3DMATH_STATE_S*      renderState,
                            SPHERE_3DMATH_D3DXMATRIX_S* matrix)
{
    SPHERE_3DMATH_SetupMatrices(renderState);

    // Compute transformation matrix.
    // Matrix = scale * rotation * translation.
    SPHERE_3DMATH_D3DXMATRIX_S transform;
    SPHERE_3DMATH_D3DXMatrixMultiply(&transform,
                        SPHERE_3DMATH_D3DXMatrixMultiply(&transform,
                                                    &renderState->m_ScaleMatrix,
                                                    &renderState->m_RotateMatrix),
                                                    &renderState->m_MoveMatrix);

    // Transform view matrix with object transform matrices.
    SPHERE_3DMATH_D3DXMATRIX_S view;
    SPHERE_3DMATH_D3DXMatrixMultiply(&view, &transform, &renderState->m_ViewMatrix);

    // Transform view matrix with the world matrix.
    SPHERE_3DMATH_D3DXMATRIX_S worldView;
    SPHERE_3DMATH_D3DXMatrixMultiply(&worldView, &renderState->m_WorldMatrix, &view);

    // Transform view matrix with the projection matrix.
    SPHERE_3DMATH_D3DXMatrixMultiply(matrix, &worldView, &renderState->m_ProjMatrix);
}

HI_VOID SPHERE_3DMATH_GetFrustum(GLfloat *matrix,
                                            GLfloat  left,
                                            GLfloat  right,
                                            GLfloat  bottom,
                                            GLfloat  top,
                                            GLfloat  zNear,
                                            GLfloat  zFar)
{
    if ((left == right)
       || (bottom == top)
       || (zNear == zFar)
       || (zNear <= 0.0f)
       || (zFar <= 0.0f))
    {
        // Invalid value.
        return;
    }

    // Fill in frustum matrix.
    matrix[0]  = (2.0f * zNear) / (right - left);
    matrix[2]  = (right + left) / (right - left);
    matrix[5]  = (2.0f * zNear) / (top - bottom);
    matrix[6]  = (top + bottom) / (top - bottom);
    matrix[10] = -(zFar + zNear) / (zFar - zNear);
    matrix[11] = -(2.0f * zFar * zNear) / (zFar - zNear);
    matrix[14] = -1;
    matrix[1]  = 0;
    matrix[3]  = 0;
    matrix[4]  = 0;
    matrix[7]  = 0;
    matrix[8]  = 0;
    matrix[9]  = 0;
    matrix[12] = 0;
    matrix[13] = 0;
}

HI_VOID SPHERE_3DMATH_MatMult(GLfloat* Result,
                                         GLfloat* Mat1,
                                         GLfloat  Mat2[16])
{
    HI_U32 r, c;

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            Result[r * 4 + c] = Mat1[r * 4 + 0] * Mat2[0 + c]
                                + Mat1[r * 4 + 1] * Mat2[4 + c]
                                + Mat1[r * 4 + 2] * Mat2[8 + c]
                                + Mat1[r * 4 + 3] * Mat2[12 + c];
        }
    }
}

HI_VOID SPHERE_3DMATH_Sphere(GLfloat**  VertexArray,
                                        HI_U32        u32Width,
                                        HI_U32        u32Height,
                                        HI_U32        u32Colors,
                                        GLfloat**    ColorArray,
                                        HI_U32        u32Textures,
                                        GLfloat**  TextureArray,
                                        GLushort** IndexArray,
                                        HI_U32 *      u32NumPrimitives,
                                        HI_U32*       u32NumIndices,
                                        HI_U32*       u32NumVertices)
{
    HI_U32 x, y, vcnt = 0, icnt = 0, ccnt = 0, tcnt = 0;
    GLushort offset;

    GLfloat* vertexArray = (GLfloat*)HI_MEM_Malloc(0, 3 * u32Width * u32Height * sizeof(GLfloat));
    GLfloat* colorArray   = NULL;
    GLfloat* textureArray = NULL;
    GLushort* indexArray  = NULL;

    for (y = 0; y < u32Height; ++y)
    {
        HI_FLOAT normY = (HI_FLOAT) y / (HI_FLOAT) (u32Height - 1);
        HI_FLOAT polar = M_PI * normY;
        HI_FLOAT polarSin = (HI_FLOAT)sin(polar);
        HI_FLOAT polarCos = (HI_FLOAT)cos(polar);

        for (x = 0; x < u32Width; ++x)
        {
            HI_FLOAT normX = (HI_FLOAT) x / (HI_FLOAT) (u32Width - 1);
            HI_FLOAT azim = 2.0f * M_PI * normX;
            HI_FLOAT azimSin = (HI_FLOAT)sin(azim);
            HI_FLOAT azimCos = (HI_FLOAT)cos(azim);
            vertexArray[vcnt++] = polarSin * azimCos;
            vertexArray[vcnt++] = polarSin * azimSin;
            vertexArray[vcnt++] = polarCos;

            if (u32Colors)
            {
                colorArray = (GLfloat*)HI_MEM_Malloc(0, 4 * u32Width * u32Height * sizeof(GLfloat));
                colorArray[ccnt++] = 1.0f;
                colorArray[ccnt++] = 0.0f;
                colorArray[ccnt++] = 0.0f;
                colorArray[ccnt++] = 1.0f;
            }

            if (u32Textures > 1)
            {
                textureArray = (GLfloat*)HI_MEM_Malloc(0, 4 * u32Width * u32Height * sizeof(GLfloat));
            }
            else if (u32Textures)
            {
                textureArray = (GLfloat*)HI_MEM_Malloc(0, 2 * u32Width * u32Height * sizeof(GLfloat));
            }

            if (u32Textures)
            {
                HI_FLOAT u = 1.0f - normX;
                HI_FLOAT v = normY;
                textureArray[tcnt++] = u;
                textureArray[tcnt++] = v;
            }

            if (u32Textures > 1)
            {
                HI_FLOAT u = 4.0f * (1.0f - normX);
                HI_FLOAT v = 2.0f * normY;
                textureArray[tcnt++] = u;
                textureArray[tcnt++] = v;
            }
        }
    }

    offset = 0;
    *u32NumPrimitives = (u32Width - 1) * (u32Height - 1) * 2;
    indexArray = (GLushort*) HI_MEM_Malloc(0, (*u32NumPrimitives) * 3 * sizeof(GLushort));

    for (y = 0; y < u32Height - 1; ++y)
    {
        for (x = 1; x < u32Width; ++x)
        {
            indexArray[icnt++] = (GLushort)(offset + x - 1);
            indexArray[icnt++] = (GLushort)(offset + x - 1 + u32Width);
            indexArray[icnt++] = (GLushort)(offset + x);
            indexArray[icnt++] = (GLushort)(offset + x - 1 + u32Width);
            indexArray[icnt++] = (GLushort)(offset + x + u32Width);
            indexArray[icnt++] = (GLushort)(offset + x);
        }

        offset += u32Width;
    }

    *VertexArray = vertexArray;
    if (u32Colors)
    {
        *ColorArray = colorArray;
    }

    if (u32Textures)
    {
        *TextureArray = textureArray;
    }

    *IndexArray  = indexArray;
    *u32NumIndices  = icnt;
    *u32NumVertices = vcnt;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixTranslation(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                          HI_FLOAT       x,
                                                                                          HI_FLOAT       y,
                                                                                          HI_FLOAT       z)
{
    pstOut->_11 = 1.0f;
    pstOut->_12 = 0.0f;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = 1.0f;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = 0.0f;
    pstOut->_33 = 1.0f;
    pstOut->_34 = 0.0f;
    pstOut->_41 = x;
    pstOut->_42 = y;
    pstOut->_43 = z;
    pstOut->_44 = 1.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixScaling(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                      HI_FLOAT       x,
                                                                                      HI_FLOAT       y,
                                                                                      HI_FLOAT       z)
{
    pstOut->_11 = x;
    pstOut->_12 = 0.0f;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = y;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = 0.0f;
    pstOut->_33 = z;
    pstOut->_34 = 0.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = 0.0f;
    pstOut->_44 = 1.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S* SPHERE_3DMATH_D3DXMatrixIdentity(SPHERE_3DMATH_D3DXMATRIX_S* pstOut)
{
    pstOut->_11 = 1.0f;
    pstOut->_12 = 0.0f;
    pstOut->_13 = 0.0f;
    pstOut->_14 = 0.0f;
    pstOut->_21 = 0.0f;
    pstOut->_22 = 1.0f;
    pstOut->_23 = 0.0f;
    pstOut->_24 = 0.0f;
    pstOut->_31 = 0.0f;
    pstOut->_32 = 0.0f;
    pstOut->_33 = 1.0f;
    pstOut->_34 = 0.0f;
    pstOut->_41 = 0.0f;
    pstOut->_42 = 0.0f;
    pstOut->_43 = 0.0f;
    pstOut->_44 = 1.0f;

    return pstOut;
}

static SPHERE_3DMATH_D3DXMATRIX_S*  SPHERE_3DMATH_D3DXMatrixRotationYawPitchRoll(SPHERE_3DMATH_D3DXMATRIX_S* pstOut,
                                                                                                        HI_FLOAT       fYaw,
                                                                                                        HI_FLOAT       fPitch,
                                                                                                        HI_FLOAT       fRoll)
{
    SPHERE_3DMATH_D3DXMATRIX_S yaw, pitch, roll;

    SPHERE_3DMATH_D3DXMatrixRotationY(&yaw, fYaw);
    SPHERE_3DMATH_D3DXMatrixRotationX(&pitch, fPitch);
    SPHERE_3DMATH_D3DXMatrixRotationZ(&roll, fRoll);

    return SPHERE_3DMATH_D3DXMatrixMultiply(pstOut, SPHERE_3DMATH_D3DXMatrixMultiply(pstOut, &yaw, &pitch), &roll);
}

// Set eye position.
HI_VOID SPHERE_3DMATH_SetEye(SPHERE_3DMATH_STATE_S* pstState,
                                        HI_FLOAT  X,
                                        HI_FLOAT  Y,
                                        HI_FLOAT  Z)
{
    pstState->m_Eye.x = X;
    pstState->m_Eye.y = Y;
    pstState->m_Eye.z = Z;
}

// Set object scale in each direction.
HI_VOID SPHERE_3DMATH_SetScale(SPHERE_3DMATH_STATE_S* pstState,
                                          HI_FLOAT  X,
                                          HI_FLOAT  Y,
                                          HI_FLOAT  Z)
{
    SPHERE_3DMATH_D3DXMatrixScaling(&pstState->m_ScaleMatrix, X, Y, Z);
}

// Set object rotation in each direction.
HI_VOID SPHERE_3DMATH_SetRotation(SPHERE_3DMATH_STATE_S* pstState,
                                             HI_FLOAT  X,
                                             HI_FLOAT  Y,
                                             HI_FLOAT  Z)
{
    SPHERE_3DMATH_D3DXMatrixRotationYawPitchRoll(&pstState->m_RotateMatrix, Y, X, Z);
}

// Set object 3D position in each direction.
HI_VOID SPHERE_3DMATH_SetMove(SPHERE_3DMATH_STATE_S* pstState,
                                         HI_FLOAT  X,
                                         HI_FLOAT  Y,
                                         HI_FLOAT  Z)
{
    SPHERE_3DMATH_D3DXMatrixTranslation(&pstState->m_MoveMatrix, X, Y, Z);
}

// Set time step.
HI_VOID SPHERE_3DMATH_SetTimeStep(SPHERE_3DMATH_STATE_S* pstState,
                                                 HI_ULONG  ulTimeStep)
{
    pstState->m_TimeStep = (HI_FLOAT)ulTimeStep;
}

HI_VOID SPHERE_3DMATH_InitializeRenderState(SPHERE_3DMATH_STATE_S* pstState,
                                                       HI_U32    u32Width,
                                                       HI_U32    u32Height)
{
    SPHERE_3DMATH_D3DXMatrixIdentity(&pstState->m_ProjMatrix);
    SPHERE_3DMATH_D3DXMatrixIdentity(&pstState->m_WorldMatrix);
    SPHERE_3DMATH_D3DXMatrixIdentity(&pstState->m_ViewMatrix);

    SPHERE_3DMATH_SetScale(pstState, 1, 1, 1);
    SPHERE_3DMATH_SetRotation(pstState, 0, 0, 0);
    SPHERE_3DMATH_SetMove(pstState, 0, 0, 0);

    pstState->m_Eye.x = 0;
    pstState->m_Eye.y = 0;
    pstState->m_Eye.z = -1;

    pstState->m_EyeVector.x = 0;
    pstState->m_EyeVector.y = 0;
    pstState->m_EyeVector.z = -1;

    pstState->m_Lookat.x = 0;
    pstState->m_Lookat.y = 0;
    pstState->m_Lookat.z = 0;

    pstState->m_UpVec.x = 0;
    pstState->m_UpVec.y = 1;
    pstState->m_UpVec.z = 0;

    pstState->m_Time = 0;
    pstState->m_TimeStep = 4;
    pstState->m_StepsPerCircle    = 360;
    pstState->FRAME_BUFFER_WIDTH  = u32Width;
    pstState->FRAME_BUFFER_HEIGHT = u32Height;
}
