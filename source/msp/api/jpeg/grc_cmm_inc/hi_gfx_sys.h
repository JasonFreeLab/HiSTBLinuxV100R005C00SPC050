/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : hi_gfx_sys.h
Version          : version 1.0
Author           :
Created         : 2017/07/05
Description    : define system function
Function List  :

History          :
Date                        Author                Modification
2017/07/05              sdk                       create
******************************************************************************/
#ifndef  _HI_GFX_SYS_H_
#define  _HI_GFX_SYS_H_


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

/*********************************add include here******************************/
#ifdef CONFIG_GFX_ANDROID_SDK
#include <utils/Log.h>
#endif

/***************************** Macro Definition ********************************/
#ifdef CFG_HI_GFX_DEBUG_LOG_SUPPORT
   #ifdef LOG_TAG
     #undef LOG_TAG
   #endif
   #define LOG_TAG "libhi_gfx"
#endif

#if defined(HI_LOG_SUPPORT) && (0 == HI_LOG_SUPPORT)
	   #define GFX_Printf( fmt,args...)
#else
    #ifdef CONFIG_GFX_ANDROID_SDK
        #define GFX_Printf( fmt, args... )\
        do {\
             ALOGE(fmt, ##args );\
        }while (0)
    #else
        #define GFX_Printf( fmt, args... )\
        do {\
             fprintf(stderr,fmt, ##args );\
        } while (0)
    #endif
#endif


#define HI_GFX_Memcpy(dst,src,size)                          memcpy(dst, src, size);
#define HI_GFX_Memset(dst,value,size)                        memset(dst, value, size);

/*************************** Enum Definition ***********************************/

/*************************** Structure Definition ******************************/


/********************** Global Variable declaration ****************************/

/******************************* API declaration *******************************/
#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */
#endif /*_HI_GFX_SYS_H_ */
