/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_drv_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_DRV_KLAD_H__
#define __HI_TEE_DRV_KLAD_H__
#define HI_LOG_D_MODULE_ID     HI_MODULE_ID_KLAD
#include "hi_type.h"
#include "hi_tee_debug.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     HI_TEE_DRV_KLAD */
/** @{ */  /** <!-- [HI_TEE_DRV_KLAD] */

/*dmx is different from cipher and plcipher*/
#define HI_ID_PLCIPHER    (0x69)
#define HI_ID_DEMUX       (0x0A)
#define HI_ID_CIPHER_TEE  (0x4D)
#define HI_ID_CIPHER_REE  (0x5F)

#define MODID(handle)     (((handle) >> 16) & 0xffff)


#define HI_DEBUG_KLAD(fmt...)    HI_TEE_DBG_PRINT(HI_MODULE_ID_KLAD,   fmt)
#define HI_FATAL_KLAD(fmt...)    HI_TEE_FATAL_PRINT(HI_MODULE_ID_KLAD, fmt)
#define HI_ERR_KLAD(fmt...)      HI_TEE_ERR_PRINT(HI_MODULE_ID_KLAD,   fmt)
#define HI_WARN_KLAD(fmt...)     HI_TEE_WARN_PRINT(HI_MODULE_ID_KLAD,  fmt)
#define HI_INFO_KLAD(fmt...)     HI_TEE_INFO_PRINT(HI_MODULE_ID_KLAD,  fmt)

#define KLAD_ERR_PrintHex(val)  HI_DBG_PrintH32(val)
#define KLAD_ERR_PrintInfo(val)  HI_DBG_PrintInfo(val)
#define KLAD_ERR_PrintPoint(val)  HI_DBG_PrintVoid(val)


#define KLAD_PrintErrorCode(errCode)  HI_LOG_PrintErrCode(errCode)
#define KLAD_PrintErrorFunc(func,errCode)  HI_LOG_PrintFuncErr(func, errCode)

#define KLAD_FUNC_ENTER   HI_LOG_FuncEnter
#define KLAD_FUNC_EXIT   HI_LOG_FuncExit


#define KLAD_CHECK_ALG(alg) \
    do {\
        if ((alg) > HI_TEE_KLAD_ALG_TYPE_SM4) \
        {\
            KLAD_ERR_PrintHex(alg); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_ALG); \
            return HI_ERR_KLAD_INVALID_ALG;\
        }\
    } while(0)

#define KLAD_CHECK_TARGET_MOD(mod) \
    do {\
        if ((mod) >= (DRV_KLAD_TARGET_BUTT)) \
        {\
            KLAD_ERR_PrintHex(mod); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGET); \
            return HI_ERR_KLAD_INVALID_TARGET;\
        }\
    } while(0)

#define KLAD_CHECK_TARGET_ADDR(addr, high) \
    do {\
        if ((addr) >= (high)) \
        {\
            KLAD_ERR_PrintHex(addr); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGETADDR); \
            return HI_ERR_KLAD_INVALID_TARGETADDR;\
        }\
    } while(0)

#define KLAD_CHECK_LEVEL(level) \
    do {\
        if (((level) < HI_TEE_KLAD_LEVEL1) || ((level) >= (HI_TEE_KLAD_LEVEL_BUTT))) \
        {\
            KLAD_ERR_PrintHex(level); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_LEVEL); \
            return HI_ERR_KLAD_INVALID_LEVEL;\
        }\
    } while(0)

#define KLAD_CHECK_ENGINE(engine) \
    do{ \
        if (engine < HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_PAYLOAD_CSA2 || engine >= HI_TEE_KLAD_TARGET_CRYPTO_ENGINE_BUTT)\
        {\
            KLAD_ERR_PrintHex(engine); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_ENGINE); \
            return HI_ERR_KLAD_INVALID_ENGINE;\
        }\
    }while(0)


#define KLAD_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            KLAD_ERR_PrintPoint(p); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_NULL_PTR); \
            return HI_ERR_KLAD_NULL_PTR; \
        } \
    } while (0)

#define KLAD_CHECK_INIT(init) \
    do{ \
        if (init <= 0)\
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_INIT); \
            return HI_ERR_KLAD_NOT_INIT;\
        }\
    }while(0)


#define KLAD_CHECK_HANDLE(handle) \
    do{ \
        if (MODID(handle) != HI_ID_KLAD)\
        {\
            KLAD_ERR_PrintHex(handle); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_HANDLE); \
            return HI_ERR_KLAD_INVALID_HANDLE;\
        }\
    }while(0)


#define KLAD_CHECK_EVENORODD(even) \
    do{ \
        if ((HI_TRUE != even) && (HI_FALSE != even)) \
        {\
            KLAD_ERR_PrintHex(even); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_EVENORODD); \
            return HI_ERR_KLAD_INVALID_EVENORODD;\
        }\
    }while(0)


#define KLAD_CHECK_BOOL(b) \
    do{ \
        if ((HI_TRUE != b) && (HI_FALSE != b)) \
        {\
            KLAD_ERR_PrintHex(b); \
            KLAD_PrintErrorCode(HI_TEE_ERR_INVALID_PARAM); \
            return HI_TEE_ERR_INVALID_PARAM;\
        }\
    }while(0)

#define KLAD_CHECK_IV(iv, len) \
    do{ \
        if (iv > len) \
        {\
            KLAD_ERR_PrintHex(iv); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_IVLENGTH); \
            return HI_ERR_KLAD_INVALID_IVLENGTH;\
        }\
    }while(0)

#define KLAD_CHECK_TARGET(handle) \
    do{ \
        if ((HI_HANDLE_GET_MODID(handle) != HI_ID_PLCIPHER) && \
            (HI_HANDLE_GET_MODID(handle) != HI_ID_CIPHER_TEE) && \
            (HI_HANDLE_GET_MODID(handle) != HI_ID_CIPHER_REE) && \
            (HI_HANDLE_GET_MODID(handle) >> 8 != HI_ID_DEMUX)) \
        {\
            KLAD_ERR_PrintHex(handle); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGET); \
            return HI_ERR_KLAD_INVALID_TARGET;\
        }\
    }while(0)

#define KLAD_CHECK_PARAM(val) \
    do{ \
        if (val) \
        {\
            KLAD_PrintErrorCode(HI_TEE_ERR_INVALID_PARAM); \
            return HI_TEE_ERR_INVALID_PARAM;\
        }\
    }while(0)

#define KLAD_CHECK_ATTR_FLAG(session) \
    do{ \
        if (HI_TRUE != session->instance.attr_flag) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SETATTR); \
            return HI_ERR_KLAD_NOT_SETATTR; \
        }\
    }while(0)

#define KLAD_CHECK_SESSION_KEY_FLAG(session,index) \
    do{ \
        if (HI_TRUE != session->instance.session_key_flag[index]) \
        {\
            KLAD_ERR_PrintHex(index); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_SESSIONKEY); \
            return HI_ERR_KLAD_NOT_SET_SESSIONKEY; \
        }\
    }while(0)

#define KLAD_CHECK_CONTENT_KEY_FLAG(session) \
    do{ \
        if (HI_TRUE != session->instance.content_key_flag) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_CONTENTKEY); \
            return HI_ERR_KLAD_NOT_SET_CONTENTKEY; \
        }\
    }while(0)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef HI_TEE_DRV_KLAD*/
