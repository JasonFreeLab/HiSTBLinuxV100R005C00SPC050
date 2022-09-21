/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_tee_debug.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Last Modified by: Linux Integration Group
 Description     : All functions and macros, not begin with HI_, prohibited to use
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2017-07-29  STB_Linux  N/A               Create this file.
 ******************************************************************************/

#ifndef __HI_TEE_DEBUG_H__
#define __HI_TEE_DEBUG_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "hi_tee_module_id.h"
#include "hi_tee_errcode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     HI_TEE_DEBUG */
/** @{ */  /** <!-- [HI_TEE_DEBUG] */

/****** Macro switch definition ***********/

/**< Defined by menuconfig, HI_TEE_LOG_SUPPORT should be 0 in the release version */
/**< Modules prohibits modification and addition. Anyone who want to change, need to go through the PM and Security SE review */
#ifndef HI_TEE_LOG_SUPPORT
#define HI_TEE_LOG_SUPPORT          (0)
#define HI_TEE_LOG_LEVEL            (0)
#endif

/**< allow modules to modify, If the related module does not define it, no information output */
#ifndef HI_LOG_D_FUNCTRACE
#define HI_LOG_D_FUNCTRACE          (0)
#endif

/**< allow modules to modify, If the related module does not define it, no information output */
#ifndef HI_LOG_D_UNFTRACE
#define HI_LOG_D_UNFTRACE           (0)
#endif


/**< allow modules to modify, default value is HI_ID_STB, the general module id*/
#ifndef HI_LOG_D_MODULE_ID
#define HI_LOG_D_MODULE_ID          HI_MODULE_ID_UNKNOWN
#endif

#define TEE_LOG_MAX_TRACE_LEN       (256)

/****** Macro constants definition ********/

typedef enum tagTEE_LOG_LEVEL_E
{
    HI_TEE_LOG_LEVEL_FATAL = 0,     /**<Fatal error. It indicates that a critical problem occurs in the system. Therefore, you must pay attention to it.*/
    HI_TEE_LOG_LEVEL_ERROR,         /**<Major error. It indicates that a major problem occurs in the system and the system cannot run.*/
    HI_TEE_LOG_LEVEL_WARNING,       /**<Warning. It indicates that a minor problem occurs in the system, but the system still can run properly.*/
    HI_TEE_LOG_LEVEL_INFO,          /**<Message. It is used to prompt users. Users can open the message when locating problems. It is recommended to disable this message in general.*/
    HI_TEE_LOG_LEVEL_DBG,           /**<Debug. It is used to prompt developers. Developers can open the message when locating problems. It is recommended to disable this message in general.*/
    HI_TEE_LOG_LEVEL_BUTT

} HI_TEE_LOG_LEVEL_E;

/****** Macro Functions definition ********/

#if HI_TEE_LOG_SUPPORT

#define HI_TEE_TRACE(level, module_id, fmt...)  HI_TEE_LogOut(level, module_id, (HI_U8*)__FUNCTION__, __LINE__, fmt)

#if (HI_TEE_LOG_LEVEL == 0)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)   HI_TEE_TRACE(HI_TEE_LOG_LEVEL_FATAL, module_id, fmt)
#define HI_TEE_ERR_PRINT(module_id, fmt...)
#define HI_TEE_WARN_PRINT(module_id, fmt...)
#define HI_TEE_INFO_PRINT(module_id, fmt...)
#define HI_TEE_DBG_PRINT(module_id, fmt...)
#elif (HI_TEE_LOG_LEVEL == 1)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)   HI_TEE_TRACE(HI_TEE_LOG_LEVEL_FATAL, module_id, fmt)
#define HI_TEE_ERR_PRINT(module_id, fmt...)     HI_TEE_TRACE(HI_TEE_LOG_LEVEL_ERROR, module_id, fmt)
#define HI_TEE_WARN_PRINT(module_id, fmt...)
#define HI_TEE_INFO_PRINT(module_id, fmt...)
#define HI_TEE_DBG_PRINT(module_id, fmt...)
#elif (HI_TEE_LOG_LEVEL == 2)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)   HI_TEE_TRACE(HI_TEE_LOG_LEVEL_FATAL, module_id, fmt)
#define HI_TEE_ERR_PRINT(module_id, fmt...)     HI_TEE_TRACE(HI_TEE_LOG_LEVEL_ERROR, module_id, fmt)
#define HI_TEE_WARN_PRINT(module_id, fmt...)    HI_TEE_TRACE(HI_TEE_LOG_LEVEL_WARNING, module_id, fmt)
#define HI_TEE_INFO_PRINT(module_id, fmt...)
#define HI_TEE_DBG_PRINT(module_id, fmt...)
#elif (HI_TEE_LOG_LEVEL == 3)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)   HI_TEE_TRACE(HI_TEE_LOG_LEVEL_FATAL, module_id, fmt)
#define HI_TEE_ERR_PRINT(module_id, fmt...)     HI_TEE_TRACE(HI_TEE_LOG_LEVEL_ERROR, module_id, fmt)
#define HI_TEE_WARN_PRINT(module_id, fmt...)    HI_TEE_TRACE(HI_TEE_LOG_LEVEL_WARNING, module_id, fmt)
#define HI_TEE_INFO_PRINT(module_id, fmt...)    HI_TEE_TRACE(HI_TEE_LOG_LEVEL_INFO, module_id, fmt)
#define HI_TEE_DBG_PRINT(module_id, fmt...)
#elif (HI_TEE_LOG_LEVEL == 4)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)   HI_TEE_TRACE(HI_TEE_LOG_LEVEL_FATAL, module_id, fmt)
#define HI_TEE_ERR_PRINT(module_id, fmt...)     HI_TEE_TRACE(HI_TEE_LOG_LEVEL_ERROR, module_id, fmt)
#define HI_TEE_WARN_PRINT(module_id, fmt...)    HI_TEE_TRACE(HI_TEE_LOG_LEVEL_WARNING, module_id, fmt)
#define HI_TEE_INFO_PRINT(module_id, fmt...)    HI_TEE_TRACE(HI_TEE_LOG_LEVEL_INFO, module_id, fmt)
#define HI_TEE_DBG_PRINT(module_id, fmt...)     HI_TEE_TRACE(HI_TEE_LOG_LEVEL_DBG, module_id, fmt)
#else
#define HI_TEE_FATAL_PRINT(module_id, fmt...)
#define HI_TEE_ERR_PRINT(module_id, fmt...)
#define HI_TEE_WARN_PRINT(module_id, fmt...)
#define HI_TEE_INFO_PRINT(module_id, fmt...)
#define HI_TEE_DBG_PRINT(module_id, fmt...)
#endif

#else

#define HI_TEE_TRACE(level, module_id, fmt...)
#define HI_TEE_FATAL_PRINT(module_id, fmt...)
#define HI_TEE_ERR_PRINT(module_id, fmt...)
#define HI_TEE_WARN_PRINT(module_id, fmt...)
#define HI_TEE_INFO_PRINT(module_id, fmt...)
#define HI_TEE_DBG_PRINT(module_id, fmt...)

#endif

#define HI_LOG_FATAL(fmt...)                    HI_TEE_FATAL_PRINT(HI_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERROR(fmt...)                    HI_TEE_ERR_PRINT(HI_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)                     HI_TEE_WARN_PRINT(HI_LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)                     HI_TEE_INFO_PRINT(HI_LOG_D_MODULE_ID, fmt)
#define HI_LOG_DEBUG(fmt...)                    HI_TEE_DBG_PRINT(HI_LOG_D_MODULE_ID, fmt)

#if ((HI_TEE_LOG_SUPPORT == 1) && (HI_TEE_LOG_LEVEL == 4))
/**< Used in tee api */
#define HI_LOG_PrintBlock(pu8Datablock, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR aciOutStr[64] = {0};  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Datablock);  \
    HI_LOG_DEBUG(" %s\n", #pu8Datablock);  \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        snprintf_s(&aciOutStr[(u32ii % 16) * 3], 4, 4, " %02X", pciBuffer[u32ii]);  \
        if((u32ii + 1) % 16 == 0)  \
        {  \
            HI_LOG_DEBUG("%s\n", aciOutStr);  \
            memset_s(aciOutStr, sizeof(aciOutStr), 0x00, sizeof(aciOutStr));\
        }  \
    }  \
    if((u32ii % 16 != 0)  \
        && (u32ii != 0))  \
    { \
        HI_LOG_DEBUG("%s\n", aciOutStr);  \
    }\
}

/**< Used in tee drv */
#define HI_DRV_LOG_PrintBlock(pu8Datablock, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Datablock);  \
    HI_LOG_DEBUG(" %s\n", #pu8Datablock);  \
    tee_hal_printf("[TEE-DRV-%04X: %s %d] ", HI_LOG_D_MODULE_ID, __FUNCTION__, __LINE__); \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        if((u32ii % 16 == 0) && (u32ii != 0))  \
        {  \
            tee_hal_printf("\n");  \
            tee_hal_printf("[TEE-DRV-%04X: %s %d] ", HI_LOG_D_MODULE_ID, __FUNCTION__, __LINE__); \
        }  \
        tee_hal_printf(" %02x", pciBuffer[u32ii]);  \
    } \
    tee_hal_printf("\n");  \
}

#else
#define HI_LOG_PrintBlock(pu8Datablock, u32Length)
#define HI_DRV_LOG_PrintBlock(pu8Datablock, u32Length)
#endif

/**< Function trace log, strictly prohibited to expand */
#define HI_LOG_PrintFuncWar(Func, ErrCode)      HI_LOG_WARN("Call %s return [0x%08X]\n", #Func, ErrCode);
#define HI_LOG_PrintFuncErr(Func, ErrCode)      HI_LOG_ERROR("Call %s return [0x%08X]\n", #Func, ErrCode);
#define HI_LOG_PrintErrCode(ErrCode)            HI_LOG_ERROR("Error Code: [0x%08X]\n", ErrCode);

/**< Used for displaying more detailed error information */
#define HI_LOG_PrintS32(val)                    HI_LOG_WARN("%s = %d\n",        #val, val)
#define HI_LOG_PrintU32(val)                    HI_LOG_WARN("%s = %u\n",        #val, val)
#define HI_LOG_PrintS64(val)                    HI_LOG_WARN("%s = %lld\n",      #val, val)
#define HI_LOG_PrintU64(val)                    HI_LOG_WARN("%s = %llu\n",      #val, val)
#define HI_LOG_PrintH32(val)                    HI_LOG_WARN("%s = 0x%08X\n",    #val, val)
#define HI_LOG_PrintH64(val)                    HI_LOG_WARN("%s = 0x%016llX\n", #val, val)
#define HI_LOG_PrintStr(val)                    HI_LOG_WARN("%s = %s\n",        #val, val)
#define HI_LOG_PrintVoid(val)                   HI_LOG_WARN("%s = %p\n",        #val, val)
#define HI_LOG_PrintFloat(val)                  HI_LOG_WARN("%s = %f\n",        #val, val)
#define HI_LOG_PrintInfo(val)                   HI_LOG_WARN("<%s>\n", val)

/**< Only used for self debug, Can be expanded as needed */
#define HI_DBG_PrintS32(val)                    HI_LOG_DEBUG("%s = %d\n",       #val, val)
#define HI_DBG_PrintU32(val)                    HI_LOG_DEBUG("%s = %u\n",       #val, val)
#define HI_DBG_PrintS64(val)                    HI_LOG_DEBUG("%s = %lld\n",     #val, val)
#define HI_DBG_PrintU64(val)                    HI_LOG_DEBUG("%s = %llu\n",     #val, val)
#define HI_DBG_PrintH32(val)                    HI_LOG_DEBUG("%s = 0x%08X\n",   #val, val)
#define HI_DBG_PrintH64(val)                    HI_LOG_DEBUG("%s = 0x%016llX\n",#val, val)
#define HI_DBG_PrintStr(val)                    HI_LOG_DEBUG("%s = %s\n",       #val, val)
#define HI_DBG_PrintVoid(val)                   HI_LOG_DEBUG("%s = %p\n",       #val, val)
#define HI_DBG_PrintFloat(val)                  HI_LOG_DEBUG("%s = %f\n",       #val, val)
#define HI_DBG_PrintInfo(val)                   HI_LOG_DEBUG("<%s>\n", val)

#if (HI_LOG_D_FUNCTRACE == 1) || (HI_LOG_D_UNFTRACE == 1)
#define HI_UNF_FuncEnter()                      HI_LOG_DEBUG(" >>>>>>[Enter]\n")    /**< Only used for unf interface */
#define HI_UNF_FuncExit()                       HI_LOG_DEBUG(" <<<<<<[Exit]\n")     /**< Only used for unf interface */
#else
#define HI_UNF_FuncEnter()
#define HI_UNF_FuncExit()
#endif

#if HI_LOG_D_FUNCTRACE
#define HI_LOG_FuncEnter()                      HI_LOG_DEBUG(" =====>[Enter]\n")    /**< Used for all interface except unf */
#define HI_LOG_FuncExit()                       HI_LOG_DEBUG(" =====>[Exit]\n")     /**< Used for all interface except unf */
#else
#define HI_LOG_FuncEnter()
#define HI_LOG_FuncExit()
#endif

#define HI_TEE_CHECK_RESULT(fnFunc)                     \
do                                                      \
{                                                       \
    HI_S32 s32iErrCode = fnFunc;                        \
    if (HI_SUCCESS != s32iErrCode)                      \
    {                                                   \
        HI_LOG_PrintFuncErr(#fnFunc, s32iErrCode);      \
    }                                                   \
} while (0)


#define HI_TEE_CHECK_PARAM(bVal)                        \
do                                                      \
{                                                       \
    if (bVal)                                           \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_INVALID_PARAM);  \
        return HI_TEE_ERR_INVALID_PARAM;                \
    }                                                   \
} while (0)

#define HI_TEE_CHECK_RETERR(bVal, s32iErrCode, Ret)     \
do                                                      \
{                                                       \
    if (bVal)                                           \
    {                                                   \
        HI_LOG_PrintErrCode(s32iErrCode);               \
        return Ret;                                     \
    }                                                   \
} while (0)

#define HI_TEE_CHECK_INITED(u32InitCount)               \
do                                                      \
{                                                       \
    if (0 == u32InitCount)                              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_UNINITED);       \
        return HI_TEE_ERR_UNINITED;                     \
    }                                                   \
} while (0)

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#define VERSION_STRING ("SDK_VERSION: [" MKMARCOTOSTR(SDK_VERSION) "] Build Time: [" __DATE__ ", " __TIME__ "]")
#define USER_VERSION_STRING ("SDK_VERSION: [" MKMARCOTOSTR(SDK_VERSION) "]")

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     HI_TEE_DEBUG */
/** @{ */  /** <!-- [HI_TEE_DEBUG] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     HI_TEE_DEBUG */
/** @{ */  /** <!-- [HI_TEE_DEBUG] */

extern HI_VOID HI_TEE_LogOut(HI_TEE_LOG_LEVEL_E LogLevel, HI_MODULE_ID_E ModId, HI_U8 *pFuncName, HI_U32 LineNum, const HI_CHAR *format, ...);

/** @}*/  /** <!-- ==== API Declaration End ====*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif  /* __HI_TEE_DEBUG_H__ */

