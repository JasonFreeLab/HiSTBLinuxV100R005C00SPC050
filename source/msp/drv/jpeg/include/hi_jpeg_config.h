/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_jpeg_config.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : this file is through set macro to select different funciton,
                        and select different platform
Function List   :


History           :
Date                          Author                Modification
2017/07/05                  sdk                  Created file
******************************************************************************/

#ifndef __HI_JPEG_CONFIG_H__
#define __HI_JPEG_CONFIG_H__

/*********************************add include here*********************************/
#ifndef HI_BUILD_IN_BOOT
    #ifdef __KERNEL__
      #include "hi_gfx_comm_k.h"
    #else
      #include "hi_gfx_sys.h"
    #endif
#else
    #include "exports.h"
#endif

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ********************************/
    #if (1 == HI_PROC_SUPPORT)
       #define CONFIG_JPEG_PROC_ENABLE
    #endif

    /** if support crop */
    /** CNcomment:是否支持裁剪功能 */
    #define CONFIG_JPEG_OUTPUT_CROP
    /** if support suspend */
    /** CNcomment:是否支持待机功能,在解码过程中待机的时候处理时钟等有点问题，先关闭该功能 */
    //#define CONFIG_JPEG_SUSPEND

    /** get jpeg dec time */
    /** CNcomment:获取jpeg解码的时间 */
    #define CONFIG_JPEG_GETDECTIME

    /** all jpeg dec output yuv420sp */
    /** CNcomment:统一解码输出yuv420sp,硬件和软件都不支持yuv400 -> yuv420
                　要是需要支持填充0x80 */
    #define CONFIG_JPEG_OUTPUT_YUV420SP

    /** dec jpeg file output lu pixel value sum */
    /** CNcomment:统计亮度值 */
    #define CONFIG_JPEG_OUTPUT_LUPIXSUM

    /** sample factor support **/
    /** CNcomment:hifone之后修改的按照采样因子来解码 **/
    #define CONFIG_JPEG_SET_SAMPLEFACTOR

    /** dri support **/
    /** CNcomment:在dri不符合标准协议得情况下解码花屏 **/
    #define CONFIG_JPEG_DRI_SUPPORT

    /**<-- support exif parase and decode >**/
    /**<-- 支持exif  信息解析和解码>**/
    #define CONFIG_JPEG_EXIF_SUPPORT

    /**<-- support stream seek >**/
    /**<-- 支持码流回退>**/
    #ifdef CONFIG_GFX_ANDROID_SDK
    #define CONFIG_JPEG_SEEK_SUPPORT
    #endif

    /**<-- savn scen >**/
    /**<-- 调试使用保存现场>**/
    //#define CONFIG_JPEG_SAVE_SCEN

    #ifdef CONFIG_GFX_BVT_SDK
        #undef CONFIG_JPEG_SUSPEND
        #undef CONFIG_JPEG_GETDECTIME
        #undef CONFIG_JPEG_PROC_ENABLE
        #define CONFIG_JPEG_CSC_DISABLE
        #define CONFIG_JPEG_CODE_CUT_RGB
    #endif

    #if   defined(HI_CHIP_TYPE_hi3531) || defined(HI_CHIP_TYPE_hi3532)   \
       || defined(HI_CHIP_TYPE_hi3521) || defined(HI_CHIP_TYPE_hi3520A)  \
       || defined(HI_CHIP_TYPE_hi3520D)
        #undef CONFIG_JPEG_OUTPUT_YUV420SP
        #undef CONFIG_JPEG_OUTPUT_LUPIXSUM
    #endif

    #if    defined(CHIP_TYPE_hi3716cv200)   \
        || defined(CHIP_TYPE_hi3716mv400)   \
        || defined(CHIP_TYPE_hi3718cv100)   \
        || defined(CHIP_TYPE_hi3718mv100)   \
        || defined(CHIP_TYPE_hi3719cv100)   \
        || defined(CHIP_TYPE_hi3719mv100)   \
        || defined(CHIP_TYPE_hi3719mv100_a)
        #undef CONFIG_JPEG_OUTPUT_YUV420SP
        #undef CONFIG_JPEG_OUTPUT_LUPIXSUM
        /** the save stream buffer whether 4 byte align */
        /** CNcomment:存储码流buffer是否需要4字节对齐**/
        #define CONFIG_JPEG_STREAMBUF_4ALIGN
    #endif

    #ifdef CONFIG_JPEG_OUTPUT_CROP
        #undef CONFIG_JPEG_OUTPUT_CROP
    #endif

    #if   !defined(CHIP_TYPE_hi3798cv200)     \
       && !defined(CHIP_TYPE_hi3798mv200)     \
       && !defined(CHIP_TYPE_hi3798mv300)	  \
       && !defined(CHIP_TYPE_hi3798mv200_a)   \
       && !defined(CHIP_TYPE_hi3796mv200)     \
       && !defined(CHIP_TYPE_hi3716mv410)     \
       && !defined(CHIP_TYPE_hi3716mv420)     \
       && !defined(CHIP_TYPE_hi3751av500)
        #undef CONFIG_JPEG_SET_SAMPLEFACTOR
    #endif

    #if   !defined(CHIP_TYPE_hi3716mv410)     \
       && !defined(CHIP_TYPE_hi3716mv420)     \
       && !defined(CHIP_TYPE_hi3798cv200)     \
       && !defined(CHIP_TYPE_hi3798mv200)     \
       && !defined(CHIP_TYPE_hi3798mv300)	  \
       && !defined(CHIP_TYPE_hi3798mv200_a)   \
       && !defined(CHIP_TYPE_hi3796mv200)     \
       && !defined(CHIP_TYPE_hi3531a)
        #undef CONFIG_JPEG_DRI_SUPPORT
    #endif

    #if    defined(CHIP_TYPE_hi3716mv310) \
        || defined(CHIP_TYPE_hi3110ev500) \
        || defined(CHIP_TYPE_hi3716mv320) \
        || defined(CHIP_TYPE_hi3716mv330) \
        || defined(CHIP_TYPE_hi3712)      \
        || defined(CHIP_TYPE_hi3716c)     \
        || defined(CHIP_TYPE_hi3716m)     \
        || defined(CHIP_TYPE_hi3716h)
        #undef CONFIG_JPEG_OUTPUT_YUV420SP
        #undef CONFIG_JPEG_OUTPUT_LUPIXSUM
    #endif

    #if   defined(CHIP_TYPE_hi3716mv310) || defined(CHIP_TYPE_hi3716mv320) \
       || defined(CHIP_TYPE_hi3716mv330) || defined(CHIP_TYPE_hi3110ev500)
        #ifdef UPSAMPLE_MERGING_SUPPORTED
          #undef UPSAMPLE_MERGING_SUPPORTED
        #endif
    #endif

    #if    !defined(CHIP_TYPE_hi3716mv310) && !defined(CHIP_TYPE_hi3110ev500)  \
        && !defined(CHIP_TYPE_hi3716mv320) && !defined(CHIP_TYPE_hi3716mv330)
        #ifdef HI_MCE_SUPPORT
            #undef HI_MCE_SUPPORT
        #endif
    #endif


    #if    defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)   \
        || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200) \
        && !defined(HI_BUILD_IN_BOOT)
        #define CONFIG_JPEG_HARDDEC2ARGB
    #endif

    #if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
        #define CONFIG_JPEG_LOW_DELAY_SUPPORT
    #endif

    #ifdef CONFIG_GFX_ADVCA_RELEASE
        #define JPEG_TRACE( fmt,args...)
    #else
        #ifndef HI_BUILD_IN_BOOT
            #ifdef __KERNEL__
            #define JPEG_TRACE               GFX_Printk
            #else
             #define JPEG_TRACE              GFX_Printf
            #endif
        #else
            #define JPEG_TRACE               printf
        #endif
    #endif

    /*************************** Structure Definition ********************************/

    /***************************  The enum of Jpeg image format  **********************/


    /********************** Global Variable declaration ********************************/


    /******************************* API declaration ********************************/


    #ifdef __cplusplus
        #if __cplusplus
}
        #endif
   #endif /* __cplusplus */
#endif /* __HI_JPEG_CONFIG_H__*/
