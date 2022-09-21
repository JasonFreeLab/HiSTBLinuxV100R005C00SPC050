/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : jpeg_sdec_exif.h
Version          : Initial Draft
Author           : sdk
Created         : 2017/03/08
Description    :
Function List  :


History          :
Date                          Author                  Modification
2017/03/08          sdk            Created file
******************************************************************************/

/*******************************add include here**********************************/

#include "hi_type.h"

/*****************************************************************************/

#ifndef __JPEG_SDEC_EXIF__H__
#define __JPEG_SDEC_EXIF__H__

/*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


/***************************** Macro Definition ******************************/
#define  JPEG_EXIF_BUFFER_SIZE            20
#define  JPEG_EXIF_THUMBNAIL_FMT_JPEG     6
#define  JPEG_EXIF_MIN_LENGTH             18
#define  JPEG_EXIF_ENTRY_LENGTH           12
#define  JPEG_EXIF_DATE_STR_LENGTH        10
#define  JPEG_EXIF_TIME_STR_LENGTH        8
#define  JPEG_EXIF_SHORT_LENGTH           2
#define  JPEG_EXIF_LONG_LENGTH            4

#define  JPEG_EXIF_ENDIAN_LITTLE          0x4949
#define  JPEG_EXIF_ENDIAN_BIG             0x4D4D

#define  JPEG_EXIF_IMAGE_TITLE            0x010E
#define  JPEG_EXIF_DATE_TIME              0x0132
#define  JPEG_EXIF_SUB_IFD                0x8769
#define  JPEG_EXIF_CUSTOM_RENDERED        0xA401

#define  JPEG_EXIF_IMAGE_COMMPRESS_TYPE   0x0103
#define  JPEG_EXIF_THUMBNAIL_OFFSET       0x0201
#define  JPEG_EXIF_THUMBNAIL_SIZE         0x0202


/*************************** Enum Definition *********************************/

/*************************** Structure Definition ******************************/
typedef struct tagJPEG_EXIF_ENTRY_S
{
    HI_BOOL  bIsBigEndian;
    HI_BOOL  bJpegCommpress;
    HI_CHAR  u8Value[JPEG_EXIF_BUFFER_SIZE];
    HI_U32   u32IFD1Offset;
    HI_U32   u32ExifDataLength;
    HI_CHAR* pNextInputByte;
    HI_CHAR* pExifBaseAddr;
} JPEG_EXIF_ENTRY_S;

typedef struct tagJPEG_EXIF_INFO_S
{
    HI_CHAR     u8Date[JPEG_EXIF_DATE_STR_LENGTH + 1];
    HI_CHAR     u8Time[JPEG_EXIF_TIME_STR_LENGTH + 1];
} JPEG_EXIF_INFO_S;

/********************** Global Variable declaration *****************************/

/******************************* API declaration *****************************/

/****************************************************************************/



#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_SDEC_EXIF__H__*/
