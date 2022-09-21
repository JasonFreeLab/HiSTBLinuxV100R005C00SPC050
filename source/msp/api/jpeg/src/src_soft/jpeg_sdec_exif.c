/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name      : jpeg_sdec_exif.c
Version          : Initial Draft
Author           : sdk
Created         : 2017/03/08
Description    :
Function List  :


History          :
Date                           Author                Modification
2017/03/08          sdk            Created file
******************************************************************************/


/*********************************add include here*******************************/
#define JPEG_INTERNALS

#include "jinclude.h"
#include "hi_gfx_sys.h"

#include "jpeg_hdec_api.h"
#include "hi_jpeg_checkpara.h"

#ifdef CONFIG_JPEG_EXIF_SUPPORT

/***************************** Macro Definition *********************************/

/*************************** Structure Definition *******************************/


/********************** Global Variable declaration *******************************/


/******************************* API forward declarations ***********************/
static HI_BOOL JPEG_ReadIFDTree(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_ReadEntryInfo(JPEG_EXIF_ENTRY_S* pstEntry);

static HI_BOOL JPEG_GetImageCompressType(JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_GetThumbnailOffset(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_GetThumbnailSize(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);


static HI_BOOL JPEG_GetImageTitle(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_GetCustomRendered(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_GetDateTime(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_SkipToIFD0Addr(JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_SkipToIFD1Addr(JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_SkipToSubIFDAddr(JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_IsExif(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);
static HI_BOOL JPEG_AllocExifBufferAndCopyDataToBuffer(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry);

static HI_U16  JPEG_GetShort(HI_CHAR* pData, HI_BOOL bBigEndian);
static HI_U32  JPEG_GetLong(HI_CHAR* pData, HI_BOOL bBigEndian);

static HI_VOID JPEG_GetExifDataEndian(JPEG_EXIF_ENTRY_S* pstEntry);
static HI_VOID JPEG_SkipTheEntry(JPEG_EXIF_ENTRY_S* pstEntry);


/******************************* API realization *********************************/
boolean JPEG_SDEC_GetExif(j_decompress_ptr cinfo)
{
    JPEG_EXIF_ENTRY_S  stEntry;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FALSE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(NULL, pJpegHandle, HI_FALSE);

    HI_GFX_Memset(&stEntry, 0, sizeof(JPEG_EXIF_ENTRY_S));
    stEntry.bIsBigEndian = HI_TRUE;

    INPUT_VARS(cinfo);
    INPUT_2BYTES(cinfo, stEntry.u32ExifDataLength, return FALSE);
    stEntry.u32ExifDataLength -= JPEG_EXIF_SHORT_LENGTH;
    INPUT_SYNC(cinfo);

    if (stEntry.u32ExifDataLength < JPEG_EXIF_MIN_LENGTH)
    {
        (*cinfo->src->skip_input_data) (cinfo, (long)stEntry.u32ExifDataLength);
        return HI_TRUE;
    }

    if ((!JPEG_IsExif(cinfo, &stEntry)) || (HI_TRUE != pJpegHandle->bExifSupport))
    {
        (*cinfo->src->skip_input_data) (cinfo, (long)stEntry.u32ExifDataLength);
        return HI_TRUE;
    }

    if (!JPEG_AllocExifBufferAndCopyDataToBuffer(cinfo, &stEntry))
    {
        (*cinfo->src->skip_input_data) (cinfo, (long)stEntry.u32ExifDataLength);
        return HI_FALSE;
    }

    JPEG_GetExifDataEndian(&stEntry);

    if (!JPEG_SkipToIFD0Addr(&stEntry))
    {
        return HI_FALSE;
    }

    if (!JPEG_ReadIFDTree(cinfo, &stEntry))
    {
        return HI_FALSE;
    }
    if (!JPEG_SkipToIFD1Addr(&stEntry))
    {
        return HI_TRUE;
    }

    if (!JPEG_ReadIFDTree(cinfo, &stEntry))
    {
        return HI_FALSE;
    }
    return HI_TRUE;
}

static HI_U16 JPEG_GetShort(HI_CHAR* pData, HI_BOOL bBigEndian)
{
    HI_U16 u16Val = 0;

    if (HI_TRUE == bBigEndian)
    {
        u16Val = (((HI_U16) * pData) << 8 ) | (((HI_U16) * (pData + 1)));
    }
    else
    {
        u16Val = ((HI_U16) * pData) | ((HI_U16) * (pData + 1) << 8);
    }

    return u16Val;
}

static HI_U32 JPEG_GetLong(HI_CHAR* pData, HI_BOOL bBigEndian)
{
    HI_U32 u32Val = 0;

    if (HI_TRUE == bBigEndian)
    {
        u32Val = (*pData << 24 ) | (*(pData + 1) << 16) | (*(pData + 2) << 8) | (*(pData + 3));
    }
    else
    {
        u32Val = (*pData) | (*(pData + 1) << 8) | (*(pData + 2) << 16) | (*(pData + 3) << 24);
    }

    return u32Val;
}

static HI_BOOL JPEG_ReadIFDTree(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16 u16EntryCount = 0;
    HI_U16 u16EntryTag = 0;
    HI_BOOL bRetVal = HI_TRUE;
    u16EntryCount = JPEG_GetShort(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    if (0 == u16EntryCount)
    {
       return HI_TRUE;
    }
    pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;

    pstEntry->u32IFD1Offset = JPEG_GetLong(pstEntry->pNextInputByte + (u16EntryCount * 12), pstEntry->bIsBigEndian);
    if (pstEntry->u32ExifDataLength < pstEntry->u32IFD1Offset)
    {
        return HI_FALSE;
    }

    while ((u16EntryCount > 0) && (HI_TRUE == bRetVal))
    {
        u16EntryTag = JPEG_GetShort(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
        pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;

        switch (u16EntryTag)
        {
            case JPEG_EXIF_IMAGE_COMMPRESS_TYPE:
                bRetVal = JPEG_GetImageCompressType(pstEntry);
                break;

            case JPEG_EXIF_THUMBNAIL_OFFSET:
                bRetVal = JPEG_GetThumbnailOffset(cinfo, pstEntry);
                break;

            case JPEG_EXIF_THUMBNAIL_SIZE:
                bRetVal = JPEG_GetThumbnailSize(cinfo, pstEntry);
                break;

            case JPEG_EXIF_IMAGE_TITLE:
                bRetVal = JPEG_GetImageTitle(cinfo, pstEntry);
                break;

            case JPEG_EXIF_CUSTOM_RENDERED:
                bRetVal = JPEG_GetCustomRendered(cinfo, pstEntry);
                break;

            case JPEG_EXIF_DATE_TIME:
                bRetVal = JPEG_GetDateTime(cinfo, pstEntry);
                break;

            case JPEG_EXIF_SUB_IFD:
                bRetVal = JPEG_SkipToSubIFDAddr(pstEntry);
                u16EntryCount = JPEG_GetShort(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
                pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;
                continue;

            default:
                JPEG_SkipTheEntry(pstEntry);
                break;
        }

        u16EntryCount--;

    }

    return bRetVal;
}

static HI_BOOL JPEG_ReadEntryInfo(JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16   u16Type;
    HI_U32   u32Count, u32Length;
    HI_U32   u32IFDOffsetAddr = 0;
    HI_CHAR* pCurrentAddr = NULL;
    HI_CHAR  u8SizeOfDataType[12] = {1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 4, 8};      /*数据类型大小对照表*/

    u16Type = JPEG_GetShort(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;

    u32Count = JPEG_GetLong(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    pstEntry->pNextInputByte += JPEG_EXIF_LONG_LENGTH;

    if ((u16Type > 12) || (u16Type < 1))
    {
        return HI_FALSE;
    }
    u32Length = u8SizeOfDataType[u16Type - 1] * u32Count;

    if (JPEG_EXIF_BUFFER_SIZE < u32Length)
    {
        u32Length = JPEG_EXIF_BUFFER_SIZE;
    }

    HI_GFX_Memset(pstEntry->u8Value, 0, JPEG_EXIF_BUFFER_SIZE);

    if (u32Length <= 4)
    {
        HI_GFX_Memcpy(pstEntry->u8Value, pstEntry->pNextInputByte, 4);
        pstEntry->pNextInputByte += JPEG_EXIF_LONG_LENGTH;
        return HI_TRUE;
    }

    u32IFDOffsetAddr = JPEG_GetLong(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    pstEntry->pNextInputByte += JPEG_EXIF_LONG_LENGTH;
    pCurrentAddr = pstEntry->pNextInputByte;
    pstEntry->pNextInputByte = (HI_CHAR* )(u32IFDOffsetAddr + pstEntry->pExifBaseAddr);
    HI_GFX_Memcpy(pstEntry->u8Value, pstEntry->pNextInputByte, u32Length);
    pstEntry->pNextInputByte = pCurrentAddr;

    return HI_TRUE;
}

static HI_BOOL JPEG_GetImageCompressType(JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16 u16ImgCommpressType;

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    u16ImgCommpressType = JPEG_GetShort((HI_CHAR*)pstEntry->u8Value, pstEntry->bIsBigEndian);

    if (JPEG_EXIF_THUMBNAIL_FMT_JPEG == u16ImgCommpressType)
    {
        pstEntry->bJpegCommpress  = HI_TRUE ;
    }

    return HI_TRUE;;
}

static HI_BOOL JPEG_GetThumbnailOffset(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U32 u32ThumbnailOffdet;
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (HI_TRUE != pstEntry->bJpegCommpress)
    {
        pstEntry->pNextInputByte += JPEG_EXIF_ENTRY_LENGTH - JPEG_EXIF_SHORT_LENGTH;
        return HI_TRUE;
    }

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    u32ThumbnailOffdet = JPEG_GetLong((HI_CHAR*)pstEntry->u8Value, pstEntry->bIsBigEndian);
    pJpegHandle->pThumbnailAddr = (HI_CHAR*)(u32ThumbnailOffdet + pstEntry->pExifBaseAddr);

    return HI_TRUE;
}

static HI_BOOL JPEG_GetThumbnailSize(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U32 u32ThumbnailSize;
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (HI_TRUE != pstEntry->bJpegCommpress)
    {
        pstEntry->pNextInputByte += JPEG_EXIF_ENTRY_LENGTH - JPEG_EXIF_SHORT_LENGTH;
        return HI_TRUE;
    }

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    u32ThumbnailSize = JPEG_GetLong((HI_CHAR*)pstEntry->u8Value, pstEntry->bIsBigEndian);

    if ((pJpegHandle->pThumbnailAddr - pstEntry->pExifBaseAddr + u32ThumbnailSize) > pstEntry->u32ExifDataLength)
    {
        u32ThumbnailSize = 0;
        return HI_TRUE;
    }

    pJpegHandle->u8ImageCount = 2;
    pJpegHandle->u32ThumbnailSize = u32ThumbnailSize;
    return HI_TRUE;;
}

static HI_BOOL JPEG_GetImageTitle(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    if (strncmp(pstEntry->u8Value, "hdr", 3) == 0)
    {
        pJpegHandle->bIsHDR = HI_TRUE;
    }

    return HI_TRUE;;
}

static HI_BOOL JPEG_GetCustomRendered(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16 u16RenderType = 0;
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    u16RenderType = JPEG_GetShort((HI_CHAR*)pstEntry->u8Value, pstEntry->bIsBigEndian);

    if (3 == u16RenderType)
    {
        pJpegHandle->bIsHDR = HI_TRUE;
    }

    return HI_TRUE;
}

static HI_BOOL JPEG_GetDateTime(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    strncpy(pJpegHandle->stExifInfo.u8Date, pstEntry->u8Value, JPEG_EXIF_DATE_STR_LENGTH);
    pJpegHandle->stExifInfo.u8Date[JPEG_EXIF_DATE_STR_LENGTH] = '\0';

    strncpy(pJpegHandle->stExifInfo.u8Time, pstEntry->u8Value + JPEG_EXIF_DATE_STR_LENGTH + 1, JPEG_EXIF_TIME_STR_LENGTH);
    pJpegHandle->stExifInfo.u8Time[JPEG_EXIF_DATE_STR_LENGTH] = '\0';

    return HI_TRUE;
}

static HI_BOOL JPEG_SkipToIFD0Addr(JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U32 u32IFDOffsetAddr = 0;

    pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;

    u32IFDOffsetAddr = JPEG_GetLong(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    pstEntry->pNextInputByte += JPEG_EXIF_LONG_LENGTH;

    if (u32IFDOffsetAddr > pstEntry->u32ExifDataLength)
    {
        return HI_FALSE;
    }

    pstEntry->pNextInputByte = u32IFDOffsetAddr + pstEntry->pExifBaseAddr;

    return HI_TRUE;
}

static HI_BOOL JPEG_SkipToIFD1Addr(JPEG_EXIF_ENTRY_S* pstEntry)
{
    if ((pstEntry->u32IFD1Offset > pstEntry->u32ExifDataLength) || (0 == pstEntry->u32IFD1Offset))
    {
        return HI_FALSE;
    }

    pstEntry->pNextInputByte = pstEntry->u32IFD1Offset + pstEntry->pExifBaseAddr;

    return HI_TRUE;
}

static HI_BOOL JPEG_SkipToSubIFDAddr(JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U32 u32IFDOffsetAddr = 0;

    if (!JPEG_ReadEntryInfo(pstEntry))
    {
        return HI_FALSE;
    }

    u32IFDOffsetAddr = JPEG_GetLong((HI_CHAR*)pstEntry->u8Value, pstEntry->bIsBigEndian);

    if (u32IFDOffsetAddr > pstEntry->u32ExifDataLength)
    {
        return HI_FALSE;
    }

    pstEntry->pNextInputByte = pstEntry->pExifBaseAddr + u32IFDOffsetAddr;

    return HI_TRUE;
}

static HI_BOOL JPEG_IsExif(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    /**< 'E'   'x'    'i'    'f'    >**/
    HI_U8   u8ExifTag[6] = {0x45, 0x78, 0x69, 0x66, 0x0, 0x0};
    HI_U8   u8TmpBuffer[6] = {0};
    HI_U8   u8Cnt = 0;

    INPUT_VARS(cinfo);

    for (u8Cnt = 0; u8Cnt < 6; u8Cnt++)
    {
        INPUT_BYTE(cinfo, u8TmpBuffer[u8Cnt], return FALSE);
    }

    pstEntry->u32ExifDataLength -= 6;
    INPUT_SYNC(cinfo);

    if (memcmp(u8TmpBuffer, u8ExifTag, 6))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_BOOL JPEG_AllocExifBufferAndCopyDataToBuffer(j_decompress_ptr cinfo, JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16 u16Cnt = 0;

    pstEntry->pExifBaseAddr = (HI_CHAR* )(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT, pstEntry->u32ExifDataLength);
    if (NULL == pstEntry->pExifBaseAddr)
    {
        return HI_FALSE;
    }

    INPUT_VARS(cinfo);

    for (u16Cnt = 0; u16Cnt < pstEntry->u32ExifDataLength; u16Cnt++)
    {
        INPUT_BYTE(cinfo, *(pstEntry->pExifBaseAddr + u16Cnt), return FALSE);
    }

    pstEntry->pNextInputByte = pstEntry->pExifBaseAddr;
    INPUT_SYNC(cinfo);

    return HI_TRUE;
}

static HI_VOID JPEG_GetExifDataEndian(JPEG_EXIF_ENTRY_S* pstEntry)
{
    HI_U16 u16Endian;

    u16Endian = JPEG_GetShort(pstEntry->pNextInputByte, pstEntry->bIsBigEndian);
    pstEntry->pNextInputByte += JPEG_EXIF_SHORT_LENGTH;

    if (JPEG_EXIF_ENDIAN_LITTLE == u16Endian)
    {
        pstEntry->bIsBigEndian = HI_FALSE;
    }

    return;
}

static HI_VOID JPEG_SkipTheEntry(JPEG_EXIF_ENTRY_S* pstEntry)
{
    pstEntry->pNextInputByte += JPEG_EXIF_ENTRY_LENGTH - JPEG_EXIF_SHORT_LENGTH;
    return;
}

#endif
