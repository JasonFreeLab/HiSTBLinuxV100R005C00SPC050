/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_plcipher_utils.h
* Description:  tee plcipher helper functions.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20170227    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_PLCIPHER_UTILS_H__
#define __TEE_PLCIPHER_UTILS_H__
#define HI_LOG_D_MODULE_ID     HI_ID_PLCIPHER
#define HI_LOG_D_FUNCTRACE     (1)
#define HI_LOG_D_UNFTRACE      (1)

#include "hi_type.h"
#include "hi_tee_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HI_FATAL_PLCIPHER(fmt...)    HI_LOG_FATAL(fmt)
#define HI_ERR_PLCIPHER(fmt...)      HI_LOG_ERROR(fmt)
#define HI_WARN_PLCIPHER(fmt...)     HI_LOG_WARN(fmt)
#define HI_INFO_PLCIPHER(fmt...)     HI_LOG_INFO(fmt)
#define HI_DBG_PLCIPHER(fmt...)      HI_LOG_DEBUG(fmt)


#define PLCIPHER_FUNC_ENTER() HI_LOG_FuncEnter()
#define PLCIPHER_FUNC_EXIT()  HI_LOG_FuncExit()


#define TEE_PLCIPHER_PrintFuncWar(Func, ErrCode)     HI_LOG_PrintFuncWar(Func, ErrCode)
#define TEE_PLCIPHER_PrintFuncErr(Func, ErrCode)     HI_LOG_PrintFuncErr(Func, ErrCode)
#define TEE_PLCIPHER_PrintErrCode(ErrCode)           HI_LOG_PrintErrCode(ErrCode)

#define TEE_PLCIPHER_LOG_PrintS32(val)               HI_LOG_PrintS32(val)
#define TEE_PLCIPHER_LOG_PrintU32(val)               HI_LOG_PrintU32(val)
#define TEE_PLCIPHER_LOG_PrintS64(val)               HI_LOG_PrintS64(val)
#define TEE_PLCIPHER_LOG_PrintU64(val)               HI_LOG_PrintU64(val)
#define TEE_PLCIPHER_LOG_PrintH32(val)               HI_LOG_PrintH32(val)
#define TEE_PLCIPHER_LOG_PrintH64(val)               HI_LOG_PrintH64(val)
#define TEE_PLCIPHER_LOG_PrintStr(val)               HI_LOG_PrintStr(val)
#define TEE_PLCIPHER_LOG_PrintVoid(val)              HI_LOG_PrintVoid(val)
#define TEE_PLCIPHER_LOG_PrintFloat(val)             HI_LOG_PrintFloat(val)
#define TEE_PLCIPHER_LOG_PrintInfo(val)              HI_LOG_PrintInfo(val)

#define TEE_PLCIPHER_DBG_PrintS32(val)               HI_DBG_PrintS32(val)
#define TEE_PLCIPHER_DBG_PrintU32(val)               HI_DBG_PrintU32(val)
#define TEE_PLCIPHER_DBG_PrintS64(val)               HI_DBG_PrintS64(val)
#define TEE_PLCIPHER_DBG_PrintU64(val)               HI_DBG_PrintU64(val)
#define TEE_PLCIPHER_DBG_PrintH32(val)               HI_DBG_PrintH32(val)
#define TEE_PLCIPHER_DBG_PrintH64(val)               HI_DBG_PrintH64(val)
#define TEE_PLCIPHER_DBG_PrintStr(val)               HI_DBG_PrintStr(val)
#define TEE_PLCIPHER_DBG_PrintVoid(val)              HI_DBG_PrintVoid(val)
#define TEE_PLCIPHER_DBG_PrintFloat(val)             HI_DBG_PrintFloat(val)
#define TEE_PLCIPHER_DBG_PrintInfo(val)              HI_DBG_PrintInfo(val)



/*
 * keep synchronization with sdk/source/common/include/hi_xxxx.h
 */
#define HI_ID_PLCIPHER                   (0x69)
#define HI_MAX_PID                       (0x1FFF)
#define PLCIPHER_KEY_MIN_LEN             (8)
#define PLCIPHER_KEY_MAX_LEN             (16)

#define PLCIPHER_MIN_SIZE_PRE_DESC       (188)
#define PLCIPHER_MAX_SIZE_PRE_DESC       (47 * 1024)


/*
 * the next definition keep similar with sdk/source/msp/api/include/hi_xxxx.h.
 */
#define MAX(a, b)         (( (a) < (b) ) ?  (b) : (a))
#define MIN(a, b)         (( (a) > (b) ) ?  (b) : (a))


/**

define of HI_HANDLE :
bit31                                                           bit0
  |<----   16bit --------->|<---   8bit    --->|<---  8bit   --->|
  |--------------------------------------------------------------|
  |           HI_MOD_ID_E       |  mod defined data |     chnID       |
  |--------------------------------------------------------------|

mod defined data: private data define by each module(for example: sub-mod id), usually, set to 0.
*/

#define HI_HANDLE_MAKEHANDLE(mod, privatedata, chnid)  (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((((privatedata)& 0xff) << 8) ) | (((chnid) & 0xff)) )

#define HI_HANDLE_GET_MODID(handle)     (((handle) >> 16) & 0xffff)
#define HI_HANDLE_GET_PriDATA(handle)   (((handle) >> 8) & 0xff)
#define HI_HANDLE_GET_CHNID(handle)     (((handle)) & 0xff)

#define CHECK_PLCIPHER_CHANHANDLE(Handle)                                \
    do                                                                  \
    {                                                                   \
        if (((Handle >> 16) & 0x000000FF) != HI_ID_PLCIPHER) \
        {\
            TEE_PLCIPHER_LOG_PrintInfo("Handle");\
            TEE_PLCIPHER_LOG_PrintH32(Handle);\
            TEE_PLCIPHER_PrintErrCode(HI_TEE_ERR_INVALID_PARAM);\
            return HI_TEE_ERR_INVALID_PARAM;\
        }\
    } while (0)


#define CHECK_PLCIPHER_POINTER(p)           \
    do                                  \
    {                                   \
        if (HI_NULL == p)               \
        {                               \
            TEE_PLCIPHER_LOG_PrintInfo("Null Pointer!\n"); \
            TEE_PLCIPHER_PrintErrCode(HI_TEE_ERR_INVALID_PARAM);\
            return HI_TEE_ERR_INVALID_PARAM; \
        }                               \
    } while (0)

#define PLCIPHER_CALLFUNC(func)                             \
    {                                                       \
        HI_S32 s32ErrCode = func;                           \
        if (HI_SUCCESS != s32ErrCode)                       \
        {                                                   \
            TEE_PLCIPHER_PrintFuncErr(func,s32ErrCode);\
        }                                                   \
    }


#define HI_PRINT_HEX(name, str, len) \
    {\
        HI_U32 _i = 0;\
        HI_PRINT("[%s]:\n", name);\
        for ( _i = 0 ; _i < (len); _i++ )\
        {\
            if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
            HI_PRINT("%02x ", *((str)+_i));\
        }\
        HI_PRINT("\n");\
    }

#define TEE_PLCIPHER_CMD_INVALID(cmd) \
        (  (cmd != TEE_CMD_PLCIPHER_INIT) \
        && (cmd != TEE_CMD_PLCIPHER_DEINIT) \
        && (cmd != TEE_CMD_PLCIPHER_CREATEHANDLE) \
        && (cmd != TEE_CMD_PLCIPHER_DESTROYHANDLE) \
        && (cmd != TEE_CMD_PLCIPHER_GETATTR) \
        && (cmd != TEE_CMD_PLCIPHER_SETATTR) \
        && (cmd != TEE_CMD_PLCIPHER_SETKEY) \
        && (cmd != TEE_CMD_PLCIPHER_ENCRYPT) \
        && (cmd != TEE_CMD_PLCIPHER_DECRYPT) \
        && (cmd != TEE_CMD_PLCIPHER_GETHANDLEID) \
        && (cmd != TEE_CMD_PLCIPHER_PUTHANDLEID) )

#define  TEE_PLCIPHER_CMD_CHECK(cmd) \
        if (TEE_PLCIPHER_CMD_INVALID(cmd)) \
        { \
            TEE_PLCIPHER_LOG_PrintInfo("unknown cmd");\
            return HI_TEE_ERR_INVALID_PARAM; \
        }


HI_S32 TEE_PLCIPHER_GetHandleId(HI_U32 *HandleId);
HI_S32 TEE_PLCIPHER_PutHandleId(HI_U32 HandleId);

HI_S32 __TEE_PLCIPHER_Ioctl(unsigned int cmd, void *args, HI_U32 argsLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DEMUX_UTILS_H__ */
