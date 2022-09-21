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
#include "hi_unf_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define HI_KLAD_MAX_SESSION  32 /*5bit*/
/*|-------------------------handle----------------------------|
  |module:16bit | ca_type:6bit | klad_type:5bit | session:5bit|
  |-----------------------------------------------------------|*/
#define HI_KLAD_MAKEHANDLE(mod, session)  \
    (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((session) & 0xffff))
#define HI_KLAD_GET_MODID(handle)     (((handle) >> 16) & 0xffff)
#define HI_KLAD_GET_CATYPE(handle)    (((handle) >> 8) & 0xff)
#define HI_KLAD_GET_KLADTYPE(handle)     (((handle) >> 5) & 0x1f)
#define HI_KLAD_GET_SESSIONID(handle)     (((handle)) & 0x1f)
#define HI_KLAD_GET_UNF_KLADTYPE(catype, kltype) ((((catype & 0xff) << 8) | (kltype & 0x1f)) & 0xffff)

#define KLAD_FUNC_ENTER()              HI_DBG_PRINT(HI_ID_CA, "[Enter] -->\n")
#define KLAD_FUNC_EXIT()               HI_DBG_PRINT(HI_ID_CA, "[Exit]  -->\n")
#define HI_DEBUG_KLAD(fmt...)          HI_DBG_PRINT(HI_ID_CA, fmt)
#define HI_FATAL_KLAD(fmt...)          HI_FATAL_PRINT(HI_ID_CA, fmt)
#define HI_ERR_KLAD(fmt...)            HI_ERR_PRINT(HI_ID_CA, fmt)
#define HI_WARN_KLAD(fmt...)           HI_WARN_PRINT(HI_ID_CA, fmt)
#define HI_INFO_KLAD(fmt...)           HI_INFO_PRINT(HI_ID_CA, fmt)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_DRV_KLAD_H__ */
