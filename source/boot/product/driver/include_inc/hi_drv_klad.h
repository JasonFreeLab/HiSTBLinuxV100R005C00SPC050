/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_drv_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_DRV_KLAD_H__
#define __HI_DRV_KLAD_H__

#include "hi_type.h"
#include "hi_common.h"
#include "exports.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */



#define KLAD_FUNC_ENTER()        HI_INFO_PRINT(HI_ID_CA, "[ENTER]---------->\n")
#define KLAD_FUNC_EXIT()         HI_INFO_PRINT(HI_ID_CA, "[EXIT]---------->\n")

#define HI_DEBUG_KLAD(fmt...)    HI_DEBUG_PRINT(HI_ID_CA, fmt)
#define HI_FATAL_KLAD(fmt...)    HI_FATAL_PRINT(HI_ID_CA, fmt)
#define HI_ERR_KLAD(fmt...)      HI_ERR_PRINT(HI_ID_CA, fmt)
#define HI_WARN_KLAD(fmt...)     HI_WARN_PRINT(HI_ID_CA, fmt)
#define HI_INFO_KLAD(fmt...)     HI_INFO_PRINT(HI_ID_CA, fmt)

HI_S32 KLAD_ModInit(HI_VOID);
HI_VOID KLAD_ModExit(HI_VOID);



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HI_TEE_DRV_KLAD*/
