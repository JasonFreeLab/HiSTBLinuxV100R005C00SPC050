/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_comm.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : common used
                          CNcomment: 公共使用的接口 CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                      sdk                        Created file
******************************************************************************/

#ifndef  __HI_GFX_COMM_H__
#define  __HI_GFX_COMM_H__


/*********************************add include here******************************/

#include "hi_type.h"
#ifndef CONFIG_GFX_LOGO_KERNEL
#include "exports.h"
#endif

/***************************** Macro Definition ******************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE
    #define HI_GFX_Log()   printf("=======%s %s %d failure\n",__FILE__,__FUNCTION__,__LINE__)
    #define HI_GFX_Print   printf
#else
    #define HI_GFX_Log()   {do{}while(0);}
    #define HI_GFX_Print   {do{}while(0);}
#endif


#define HI_GFX_INVALID_HANDLE   0

#define CHECK_POINT_NULL(para)\
do{\
    if (NULL == para)\
    {\
        HI_GFX_Log();\
        return HI_FAILURE;\
    }\
}while(0)

#define CHECK_POINT_NULL_UNRETURN(para)\
    do{\
        if (NULL == para)\
        {\
            HI_GFX_Log();\
            return;\
        }\
    }while(0)

/*************************** Structure Definition ****************************/

typedef struct hiGfxRectS
{
    HI_U32 x;
    HI_U32 y;
    HI_U32 w;
    HI_U32 h;
}HI_GFX_RECT_S;


typedef enum hiGfxLayerIdE
{
    HI_GFX_LAYER_HD_0         = 0,
    HI_GFX_LAYER_HD_1         = 1,
    HI_GFX_LAYER_HD_2         = 2,
    HI_GFX_LAYER_HD_3,
    HI_GFX_LAYER_SD_0,
    HI_GFX_LAYER_SD_1,
    HI_GFX_LAYER_ID_BUTT
}HI_GFX_LAYER_ID_E;


/********************** Global Variable declaration **************************/

typedef HI_GFX_RECT_S   HI_RECT;

/******************************* API declaration *****************************/

#endif /*__HI_GFX_COMM_H__ */
