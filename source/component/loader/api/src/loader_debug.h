/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_debug.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2015-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2015-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __LOADER_DEBUG_H__
#define __LOADER_DEBUG_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_common.h"
#include "hi_module.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     LOADER_DEBUG */
/** @{ */  /** <!-- [LOADER_DEBUG] */

/****** Macro switch definition ***********/
#if defined (HI_LOG_SUPPORT)
#define LOADER_D_LOGENABLE          HI_LOG_SUPPORT
#else
#define LOADER_D_LOGENABLE          (0)
#endif

#define LOADER_D_FUNCTRACE          (0)

/****** Macro constants definition ********/
#if defined (HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#define LOADER_D_ENVIRONMENT        (0)
#elif defined (HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#define LOADER_D_ENVIRONMENT        (1)
#elif defined (DHI_LOADER_RUNNING_ENVIRONMENT_APPLOADER)
#define LOADER_D_ENVIRONMENT        (2)
#else
#define LOADER_D_ENVIRONMENT        (3)
#endif

#define LOADER_ERRCODE_DEF(errid) (HI_S32)(((HI_ID_LOADER) << 16) | ((LOADER_D_ENVIRONMENT) << 8) | (errid))

/** common error code define */
#define LOADER_ERR_MEM                      LOADER_ERRCODE_DEF(0x001)      /**< Memory Operation Error */
#define LOADER_ERR_SEM                      LOADER_ERRCODE_DEF(0x002)      /**< Semaphore Operation Error */
#define LOADER_ERR_FILE                     LOADER_ERRCODE_DEF(0x003)      /**< File Operation Error */
#define LOADER_ERR_LOCK                     LOADER_ERRCODE_DEF(0x004)      /**< Lock Operation Error */
#define LOADER_ERR_PARAM                    LOADER_ERRCODE_DEF(0x005)      /**< Invalid Parameter */
#define LOADER_ERR_TIMER                    LOADER_ERRCODE_DEF(0x006)      /**< Timer error */
#define LOADER_ERR_THREAD                   LOADER_ERRCODE_DEF(0x007)      /**< Thread Operation Error */
#define LOADER_ERR_TIMEOUT                  LOADER_ERRCODE_DEF(0x008)      /**< Time Out Error */
#define LOADER_ERR_DEVICE                   LOADER_ERRCODE_DEF(0x009)      /**< Device Operation Error */
#define LOADER_ERR_STATUS                   LOADER_ERRCODE_DEF(0x010)      /**< Status Error */
#define LOADER_ERR_IOCTRL                   LOADER_ERRCODE_DEF(0x011)      /**< IO Operation Error */
#define LOADER_ERR_INUSE                    LOADER_ERRCODE_DEF(0x012)      /**< In use */
#define LOADER_ERR_EXIST                    LOADER_ERRCODE_DEF(0x013)      /**< Have exist */
#define LOADER_ERR_NOEXIST                  LOADER_ERRCODE_DEF(0x014)      /**< no exist */
#define LOADER_ERR_UNSUPPORTED              LOADER_ERRCODE_DEF(0x015)      /**< Unsupported */
#define LOADER_ERR_UNAVAILABLE              LOADER_ERRCODE_DEF(0x016)      /**< Unavailable */
#define LOADER_ERR_UNINITED                 LOADER_ERRCODE_DEF(0x017)      /**< Uninited */
#define LOADER_ERR_DATABASE                 LOADER_ERRCODE_DEF(0x018)      /**< Database Operation Error */
#define LOADER_ERR_OVERFLOW                 LOADER_ERRCODE_DEF(0x019)      /**< Overflow */
#define LOADER_ERR_EXTERNAL                 LOADER_ERRCODE_DEF(0x020)      /**< External Error */
#define LOADER_ERR_UNKNOWNED                LOADER_ERRCODE_DEF(0x021)      /**< Unknow Error */
#define LOADER_ERR_FLASH                    LOADER_ERRCODE_DEF(0x022)      /**< Flash Operation Error*/
#define LOADER_ERR_ILLEGAL_IMAGE            LOADER_ERRCODE_DEF(0x023)      /**< Illegal Image */

/****** Macro Functions definition ********/
#if LOADER_D_LOGENABLE

#define LOADER_DEBUG(pszFormat...)             HI_DBG_PRINT(HI_ID_LOADER, pszFormat)
#define LOADER_INFO(pszFormat...)              HI_INFO_PRINT(HI_ID_LOADER, pszFormat)
#define LOADER_WARN(pszFormat...)              HI_WARN_PRINT(HI_ID_LOADER, pszFormat)
#define LOADER_ERROR(pszFormat...)             HI_ERR_PRINT(HI_ID_LOADER, pszFormat)
#define LOADER_FATAL(pszFormat...)             HI_FATAL_PRINT(HI_ID_LOADER, pszFormat)

#else

#define LOADER_DEBUG(pszFormat...)
#define LOADER_INFO(pszFormat...)
#define LOADER_WARN(pszFormat...)
#define LOADER_ERROR(pszFormat...)
#define LOADER_FATAL(pszFormat...)

#endif

#define LOADER_PrintFuncErr(Func, ErrCode)  LOADER_ERROR("Call [%s] return [0x%08X]\n", #Func, ErrCode);
#define LOADER_PrintErrCode(ErrCode)        LOADER_ERROR("Error Code: [0x%08X]\n", ErrCode);

#define LOADER_PrintS32(val)                LOADER_DEBUG("%s = %d\n",    #val, val)
#define LOADER_PrintU32(val)                LOADER_DEBUG("%s = %u\n",    #val, val)
#define LOADER_PrintS64(val)                LOADER_DEBUG("%s = %lld\n",  #val, val)
#define LOADER_PrintU64(val)                LOADER_DEBUG("%s = %llu\n",  #val, val)
#define LOADER_PrintStr(val)                LOADER_DEBUG("%s = %s\n",    #val, val)
#define LOADER_PrintVoid(val)               LOADER_DEBUG("%s = %p\n",    #val, val)
#define LOADER_Print32Hex(val)              LOADER_DEBUG("%s = 0x%08X\n",#val, val)
#define LOADER_Print64Hex(val)              LOADER_DEBUG("%s = 0x%016llX\n", #val, val)
#define LOADER_PrintFloat(val)              LOADER_DEBUG("%s = %f\n",    #val, val)
#define LOADER_PrintInfo(val)               LOADER_DEBUG("<%s>\n", val)

#if LOADER_D_FUNCTRACE
#define LOADER_FuncEnter()                  LOADER_DEBUG(" =====>[Enter]\n")
#define LOADER_FuncExit()                   LOADER_DEBUG(" =====>[Exit]\n")
#else
#define LOADER_FuncEnter()
#define LOADER_FuncExit()
#endif

#define LOADER_PrintBuffer(pcNotice, pu8Input, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR aciOutStr[64] = {0};  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Input);  \
    LOADER_DEBUG(" %s\n", pcNotice);  \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        if((u32ii % 16 == 0)  \
            && (u32ii != 0))  \
        {  \
            LOADER_DEBUG("%s\n", aciOutStr);  \
            LOADER_MemSet(aciOutStr, 0x00, sizeof(aciOutStr));\
        }  \
        snprintf(&aciOutStr[(u32ii % 16) * 3], 4, " %02X", pciBuffer[u32ii]);  \
    }  \
    if(u32ii != 0)  \
    { \
        LOADER_DEBUG("%s\n", aciOutStr);  \
        LOADER_MemSet(aciOutStr, 0x00, sizeof(aciOutStr));\
    }\
}

#define LOADER_CHECK(func)                              \
{                                                       \
    HI_S32 s32iErrCode = func;                          \
    if (HI_SUCCESS != s32iErrCode)                      \
    {                                                   \
        LOADER_PrintFuncErr(#func, s32iErrCode);        \
    }                                                   \
}


#define LOADER_CHECK_PARAM(val)                         \
{                                                       \
    if (val)                                            \
    {                                                   \
        LOADER_PrintErrCode(LOADER_ERR_PARAM);          \
        return LOADER_ERR_PARAM;                        \
    }                                                   \
}

#define LOADER_CHECK_PARAM_RETERR(val, errCode)         \
{                                                       \
    if (val)                                            \
    {                                                   \
        LOADER_PrintErrCode(errCode);                   \
        return errCode;                                 \
    }                                                   \
}

#define LOADER_CHECK_INITED(u32InitCount)               \
{                                                       \
    if (0 == u32InitCount)                              \
    {                                                   \
        LOADER_PrintErrCode(LOADER_ERR_UNINITED);       \
        return LOADER_ERR_UNINITED;                     \
    }                                                   \
}

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     LOADER_DEBUG */
/** @{ */  /** <!-- [LOADER_DEBUG] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     LOADER_DEBUG */
/** @{ */  /** <!-- [LOADER_DEBUG] */


/** @}*/  /** <!-- ==== API Declaration End ====*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif  /* __LOADER_DEBUG_H__ */

