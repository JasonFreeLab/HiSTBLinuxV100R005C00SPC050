/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_mem.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     :
Function List   :


History           :
Date                             Author                   Modification
2017/07/05                   sdk                        Created file
******************************************************************************/
#ifndef __JPEG_HDEC_MEM_H__
#define __JPEG_HDEC_MEM_H__

/*********************************add include here********************************/

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ********************************/
     #define CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN   64

     #define JPEG_MCU_8ALIGN                       8
     #define JPEG_MCU_16ALIGN                      16

     #define JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN     16

     #if   defined(CHIP_TYPE_hi3716mv310)  \
        || defined(CHIP_TYPE_hi3110ev500)  \
        || defined(CHIP_TYPE_hi3716mv320)  \
        || defined(CHIP_TYPE_hi3716mv330)  \
        || defined(CHIP_TYPE_hi3712)       \
        || defined(CHIP_TYPE_hi3716c)      \
        || defined(CHIP_TYPE_hi3716m)      \
        || defined(CHIP_TYPE_hi3716h)
       #define JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN    128
   #else
       #define JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN    64
   #endif

     #define JPGD_HDEC_MMZ_ARGB_STRIDE_ALIGN       128
     #define JPGD_HDEC_MMZ_ARGB_BUFFER_ALIGN       4
     #define JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN     16
     #define JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN      128

     /*************************** Enum Definition *********************************/


    /*************************** Structure Definition ********************************/


    /********************** Global Variable declaration *******************************/

    /******************************* API declaration *******************************/

    /**************************************************************************/

#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_HDEC_MEM_H__*/
