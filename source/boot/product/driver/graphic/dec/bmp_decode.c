/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : bmp_decode.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : decode images
                          CNcomment: BMP图片解码CNend\n
Function List     :
History             :
Date                              Author                     Modification
2017/06/08                  sdk                         Created file
******************************************************************************/


/*********************************add include here******************************/
#include "hi_gfx_surface.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_io.h"
#include "hi_gfx_sys.h"
#include "bmp_decode.h"

#ifdef HI_BUILD_IN_MINI_BOOT
#include "mmu.h"
#endif

/***************************** Macro Definition ******************************/

#define BMP_WORD_LEN                  sizeof(HI_U16)
#define BMP_DWORD_LEN                 sizeof(HI_U32)
#define BMP_FILEHEADER_LEN            0x0E /**<--  14   -->**/
#define BMP_INFOHEADER_LEN            0x28 /**<--  40   -->**/
#define BMP_INFOV4HEADER_LEN          0x6C /**<--  108  -->**/
#define BMP_INFOV5HEADER_LEN          0x7C /**<--  124 -->**/


/*************************** Structure Definition ****************************/
typedef struct tagCIEXYZ
{
  HI_U32 X;
  HI_U32 Y;
  HI_U32 Z;
}BMP_CIEXYZ;

typedef struct tagCIEXYZTRIPLE
{
  BMP_CIEXYZ ciexyzRed;
  BMP_CIEXYZ ciexyzGreen;
  BMP_CIEXYZ ciexyzBlue;
}BMP_CIEXYZTRIPLE;

typedef struct tag_HIGFX_BITMAPFILEHEADER
{
    HI_U16 bfType;
    HI_U32 bfSize;
    HI_U16 bfReserved1;
    HI_U16 bfReserved2;
    HI_U32 bfOffBits;
} HIGFX_BITMAPFILEHEADER;

typedef struct tagHIGFX_BITMAPINFOHEADER
{
    HI_U32 biSize;
    HI_S32 biWidth;
    HI_S32 biHeight;
    HI_U16 biPlanes;
    HI_U16 biBitCount;       /** 每个像素所需的位数, 1: 双色 4: 16色 8: 256色 24: 真彩色 32: 32位真彩 **/
    HI_U32 biCompression;    /** 位图压缩类型, 0: 不压缩 1: BI_RLE8压缩类型 2: BI_RLE4压缩类型        **/
    HI_U32 biSizeImage;      /** 位图的大小, 以字节为单位, 对于BI_RGB必须设置为0                      **/
    HI_S32 biXPelsPerMeter;
    HI_S32 biYPelsPerMeter;
    HI_U32 biClrUsed;
    HI_U32 biClrImportant;
    /** V4 + V5 **/
    HI_U32 biRedMask;                /**<-- Red color mask           -->**/
    HI_U32 biGreenMask;              /**<-- Green color mask        -->**/
    HI_U32 biBlueMask;               /**<-- Blue color mask           -->**/
    HI_U32 biAlphaMask;              /**<-- Alpha mask                 -->**/
    HI_U32 biCSType;                 /**<-- color space type         -->**/
    BMP_CIEXYZTRIPLE biEndpoints;    /**<-- XYZ values                  -->**/
    HI_U32 biGammaRed;               /**<-- Red gamma value        -->**/
    HI_U32 biGammaGreen;             /**<-- Green gamma value     -->**/
    HI_U32 biGammaBlue;              /**<-- Blue gamma value       -->**/
    /** V5 **/
    HI_U32 biIntent;                 /**<-- rendering intent                               -->**/
    HI_U32 biProfileData;            /**<-- profile data or filename                    -->**/
    HI_U32 biProfileSize;            /**<-- size of embedded data or filename   -->**/
    HI_U32 biReserved;
}HIGFX_BITMAPINFOHEADER;

typedef struct BMP_DECODER
{
    HIGFX_IO_INSTANCE_S    stStream;
    HIGFX_BITMAPFILEHEADER FileHeader;
    HIGFX_BITMAPINFOHEADER InfoHeader;
}BMP_DECODER_S;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

static HI_S32 BMP_ParseBitMapV3InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader);
static HI_S32 BMP_ParseBitMapV4InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader);
static HI_S32 BMP_ParseBitMapV5InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader);

/***************************************************************************************
* func          : BMP_Read_DecData
* description   : CNcomment: 读取解码后的数据 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 BMP_Read_DecData(BMP_DECODER_S *pBmpDec,HI_HANDLE hSurface)
{
    HI_U32 u32Row        = 0;
    HI_U32 u32Col        = 0;
    HI_CHAR *pDstData    = NULL;
    HI_CHAR *pDstPos     = NULL;
    HI_CHAR *pSrcData    = NULL;
    HI_CHAR *pSrcPos     = NULL;
    HI_U32 u32CopyLen    = 0;

    HIGFX_IO_INSTANCE_S *pstStream = NULL;
    HI_LOGO_SURFACE_S *pstSurface   = (HI_LOGO_SURFACE_S*)hSurface;

    CHECK_POINT_NULL(pBmpDec);

    pstStream = &(pBmpDec->stStream);
    CHECK_POINT_NULL(pstSurface);
    CHECK_POINT_NULL(pstStream);

    if (0 == pstSurface->u32Stride[0] || 0 == pstSurface->u32Height[0])
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pDstData = (HI_CHAR*)(pstSurface->pVirAddr[0]);
    pSrcData = (HI_CHAR*)(pstStream->pAddr + pstStream->u32Position);
    CHECK_POINT_NULL(pDstData);
    CHECK_POINT_NULL(pSrcData);

    if (pstStream->u32Length < pstStream->u32Position)
    {
        return HI_FAILURE;
    }

#ifdef HI_BUILD_IN_MINI_BOOT
    mmu_cache_enable();
#else
    dcache_enable(0);
#endif

#if 0
    HI_GFX_Print("\n=============================================\n");
    HI_GFX_Print("pstStream->u32Length    = %d\n",  pstStream->u32Length);
    HI_GFX_Print("pstStream->u32Position  = %d pBmpDec->InfoHeader.biBitCount = %d\n",  pstStream->u32Position,pBmpDec->InfoHeader.biBitCount);
    HI_GFX_Print("=============================================\n");
#endif

    for (u32Row = 0; u32Row < pstSurface->u32Height[0]; u32Row++)
    {
        if (pBmpDec->InfoHeader.biHeight > 0)
        {
             pDstPos = pDstData + ((pstSurface->u32Height[0] - 1) - u32Row) * pstSurface->u32Stride[0];
        }
        else
        {
             pDstPos = pDstData + u32Row * pstSurface->u32Stride[0];
        }
        pSrcPos = pSrcData + u32CopyLen;

        if (32 == pBmpDec->InfoHeader.biBitCount)
        {
            for (u32Col = 0; u32Col < pstSurface->u32Width[0]; u32Col++)
            {
                HI_GFX_Memcpy(pDstPos, pSrcPos, 4);
                pDstPos[3]  = 0xff;
                pDstPos    += 4;
                pSrcPos    += 4;
                u32CopyLen += 4;
            }
        }
        else
        {
            for (u32Col = 0; u32Col < pstSurface->u32Width[0]; u32Col++)
            {
                HI_GFX_Memcpy(pDstPos, pSrcPos, 3);
                pDstPos[3] = 0xff;
                pDstPos    += 4;
                pSrcPos    += 3;
                u32CopyLen += 3;
            }
        }
    }

#ifdef HI_BUILD_IN_MINI_BOOT
    mmu_cache_disable();
#else
    dcache_disable();
#endif

    return HI_SUCCESS;
}

/*****************************************************************************
* func          : BMP_ParseFileHeader
* description: 解析bmp文件
* retval       :
* others:    :
*****************************************************************************/
static HI_S32 BMP_ParseFileHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPFILEHEADER *pFileHeader)
{
    HI_S32 Ret  = HI_SUCCESS;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0, Reserved;
    HI_BOOL EndFlag;

    /** FileType */
    Ret = HI_GFX_IORead(pstStream, Bytes, 2, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != Ret) || (CopyLen < 2))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pFileHeader->bfType = Bytes[0] | ((HI_U16)Bytes[1] << 8);

    /** FileSize */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != Ret) || (CopyLen < BMP_DWORD_LEN))
    {
       HI_GFX_Log();
       return HI_FAILURE;
    }

    pFileHeader->bfSize = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** Reserver Validation */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != Ret) || (CopyLen < BMP_DWORD_LEN))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Reserved = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);
    if (0 != Reserved)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pFileHeader->bfReserved1 = pFileHeader->bfReserved2 = 0;

    /** OffBits */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != Ret) || (CopyLen < BMP_DWORD_LEN))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pFileHeader->bfOffBits = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    return HI_SUCCESS;
}

static HI_S32 BMP_ParseBitMapInfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0;
    HI_BOOL EndFlag = HI_SUCCESS;

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    pInfoHeader->biSize = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);
    if ((pInfoHeader->biSize != BMP_INFOHEADER_LEN) && (pInfoHeader->biSize != BMP_INFOV4HEADER_LEN) && (pInfoHeader->biSize != BMP_INFOV5HEADER_LEN))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = BMP_ParseBitMapV3InfoHeader(pstStream,pInfoHeader);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    if (BMP_INFOHEADER_LEN == pInfoHeader->biSize)
    {
        return HI_SUCCESS;
    }

    Ret = BMP_ParseBitMapV4InfoHeader(pstStream,pInfoHeader);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    if (BMP_INFOV4HEADER_LEN == pInfoHeader->biSize)
    {
        return HI_SUCCESS;
    }

    Ret = BMP_ParseBitMapV5InfoHeader(pstStream,pInfoHeader);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_S32 BMP_ParseBitMapV3InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0;
    HI_BOOL EndFlag = HI_SUCCESS;

    /** ImageWidth */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biWidth = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** ImageHeight为正表示负向位图 为负表示正向位图 */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biHeight = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** Planes 总为1 */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_WORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biPlanes = Bytes[0] | ((HI_U16)Bytes[1] << 8);
    if (1 != pInfoHeader->biPlanes)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    /** BitCount */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_WORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biBitCount = Bytes[0] | ((HI_U16)Bytes[1] << 8);

    /** Compression 0-不压缩 1- RLE 8  2-RLE 4 3-Bitfields */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biCompression = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** ImageSize */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biSizeImage = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** HResolution */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biXPelsPerMeter = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** VResolution */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biYPelsPerMeter = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** Colors */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biClrUsed = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /** Colors Important */
    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biClrImportant = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    return HI_SUCCESS;
}

static HI_S32 BMP_ParseBitMapV4InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0;
    HI_BOOL EndFlag = HI_SUCCESS;


    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biRedMask = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biGreenMask = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biBlueMask = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biAlphaMask = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biCSType = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    /**bEndpoints**/
    Ret = HI_GFX_IORead(pstStream, &(pInfoHeader->biEndpoints), sizeof(BMP_CIEXYZTRIPLE), &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biGammaRed = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biGammaGreen = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biGammaBlue = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    return HI_SUCCESS;
}


static HI_S32 BMP_ParseBitMapV5InfoHeader(HIGFX_IO_INSTANCE_S* const pstStream, HIGFX_BITMAPINFOHEADER *pInfoHeader)
{

    HI_S32 Ret = HI_SUCCESS;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0;
    HI_BOOL EndFlag = HI_SUCCESS;

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
	    HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biIntent = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
	    HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biProfileData = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
	    HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biProfileSize = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    Ret = HI_GFX_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != Ret)
    {
	    HI_GFX_Log();
        return HI_FAILURE;
    }
    pInfoHeader->biReserved = Bytes[0] | ((HI_U16)Bytes[1] << 8) | ((HI_U32)Bytes[2] << 16) | ((HI_U32)Bytes[3] << 24);

    return HI_SUCCESS;
}


/***************************************************************************************
* func            : BMP_ParseFile
* description  : CNcomment: 文件解析 CNend\n
* param[in]   : HI_VOID
* retval         : NA
* others:       : NA
***************************************************************************************/
static HI_S32 BMP_ParseFile(BMP_DECODER_S *pDecoder)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = BMP_ParseFileHeader((HIGFX_IO_INSTANCE_S* const)(&(pDecoder->stStream)), &(pDecoder->FileHeader));
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = BMP_ParseBitMapInfoHeader((HIGFX_IO_INSTANCE_S* const)(&(pDecoder->stStream)), &(pDecoder->InfoHeader));
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func            : BMP_GetPixelFmt
* description  : CNcomment: 获取像素格式 CNend\n
* param[in]   : HI_VOID
* retval         : NA
* others:      : NA
***************************************************************************************/
static HI_VOID BMP_GetPixelFmt(const BMP_DECODER_S *pBmpDec, HI_GFX_PF_E *enPixelFormat)
{
    if ( (NULL == pBmpDec) || (NULL == enPixelFormat))
    {
        return;
    }

    switch (pBmpDec->InfoHeader.biBitCount)
    {
        case 24:
        case 32:
          *enPixelFormat = HI_GFX_PF_8888;
          break;
        default:
          *enPixelFormat = HI_GFX_PF_BUTT;
    }

    return;
}

/***************************************************************************************
* func             : BMP_ADP_CreateDecode
* description   : CNcomment: 创建bmp解码器 CNend\n
* param[in]    : HI_VOID
* retval          : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_ADP_CreateDecode(HI_U32 *pDecHandle,HI_CHAR* pSrcBuf,HI_U32 u32SrcLen)
{

    HI_S32 Ret  = HI_SUCCESS;
    BMP_DECODER_S *pBmpDecoder = NULL;

    pBmpDecoder = (BMP_DECODER_S*)HI_GFX_Malloc(sizeof(BMP_DECODER_S),"bmp-adp-handle");
    CHECK_POINT_NULL(pBmpDecoder);
    HI_GFX_Memset(pBmpDecoder, 0, sizeof(BMP_DECODER_S));

    Ret = HI_GFX_IOCreate(&(pBmpDecoder->stStream),pSrcBuf,u32SrcLen);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERR1;
    }

    Ret = BMP_ParseFile(pBmpDecoder);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERR2;
    }

    if (0 != pBmpDecoder->InfoHeader.biCompression)
    {/** 只支持非压缩的的bmp文件 **/
        HI_GFX_Log();
        goto ERR2;
    }

    *pDecHandle = (unsigned long)pBmpDecoder;

    return HI_SUCCESS;

ERR2:
    HI_GFX_IODestroy(&(pBmpDecoder->stStream));

ERR1:
    if (NULL != pBmpDecoder)
    {
        HI_GFX_Free((HI_CHAR*)pBmpDecoder);
        pBmpDecoder = NULL;
    }
    *pDecHandle = 0;

    return HI_FAILURE;
}

/***************************************************************************************
* func            : BMP_ADP_StartDecode
* description  : CNcomment:开始解码CNend\n
* param[in]   : HI_VOID
* retval         : NA
* others:      : NA
***************************************************************************************/
HI_S32 BMP_ADP_StartDecode(HI_U32 DecHandle, HI_HANDLE hSurface)
{
    HI_S32 Ret = HI_SUCCESS;

    BMP_DECODER_S *pBmpDec  = (BMP_DECODER_S*)(unsigned long)DecHandle;
    CHECK_POINT_NULL(pBmpDec);

    Ret = HI_GFX_IOSeek((HIGFX_IO_INSTANCE_S* const)(&(pBmpDec->stStream)),pBmpDec->FileHeader.bfOffBits);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = BMP_Read_DecData(pBmpDec, hSurface);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    return HI_SUCCESS;

}

/***************************************************************************************
* func            : BMP_ADP_GetImgInfo
* description  : CNcomment:获取图片信息CNend\n
* param[in]   : HI_VOID
* retval          : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_ADP_GetImgInfo(HI_U32 DecHandle, HI_HANDLE hSurface)
{

    BMP_DECODER_S *pBmpDec = (BMP_DECODER_S*)(unsigned long)DecHandle;
    HI_LOGO_SURFACE_S *pstSurface  = (HI_LOGO_SURFACE_S*)hSurface;

    CHECK_POINT_NULL(pstSurface);
    CHECK_POINT_NULL(pBmpDec);

    pstSurface->u32Width[0]  = (HI_U32)pBmpDec->InfoHeader.biWidth;
    pstSurface->u32Height[0] = (HI_U32)(pBmpDec->InfoHeader.biHeight);

    if (pBmpDec->InfoHeader.biHeight < 0)
    {
       pstSurface->u32Height[0] = -pBmpDec->InfoHeader.biHeight;
    }
    else
    {
       pstSurface->u32Height[0] = pBmpDec->InfoHeader.biHeight;
    }

    BMP_GetPixelFmt(pBmpDec, &(pstSurface->enPixelFormat));

    if (HI_GFX_PF_BUTT == pstSurface->enPixelFormat)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pstSurface->u32Stride[0] = ((pstSurface->u32Width[0] * 32 + 31) / 32) * 4;
    pstSurface->u32Size[0]   = pstSurface->u32Stride[0] * pstSurface->u32Height[0];

    if ((0 == pstSurface->u32Width[0]) || (0 == pstSurface->u32Height[0]) || (0 == pstSurface->u32Stride[0]))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func            : BMP_ADP_DestroyDecoder
* description  : CNcomment:销毁bmp解码器 CNend\n
* param[in]   : HI_VOID
* retval         : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_ADP_DestroyDecode(HI_U32 DecHandle)
{
    BMP_DECODER_S *pBmpDecoder = (BMP_DECODER_S*)(unsigned long)DecHandle;
    CHECK_POINT_NULL(pBmpDecoder);

    HI_GFX_IODestroy(&(pBmpDecoder->stStream));

    HI_GFX_Free((HI_CHAR*)pBmpDecoder);
    pBmpDecoder = NULL;

    return HI_SUCCESS;
}
