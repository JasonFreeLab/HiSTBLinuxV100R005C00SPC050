#include "hi_type.h"
#include "hi_tee_log.h"

#ifndef __TEE_AVPLAY_UTILS_H__
#define __TEE_AVPLAY_UTILS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define TEE_WARN_AVPLAY(fmt...)                    HI_LOG_WARN(fmt)
#define TEE_DEBUG_AVPLAY(fmt...)                   HI_LOG_DEBUG(fmt)
#define TEE_FATAL_AVPLAY(fmt...)                   HI_LOG_FATAL(fmt)
#define TEE_ERR_AVPLAY(fmt...)                     HI_LOG_ERROR(fmt)

#define TEE_AVPLAY_ENTER()                         HI_LOG_FuncEnter()
#define TEE_AVPLAY_EXIT()                          HI_LOG_FuncExit()

#define TEE_AVPLAY_PrintFuncWar(Func, ErrCode)     HI_LOG_PrintFuncWar(Func, ErrCode)
#define TEE_AVPLAY_PrintFuncErr(Func, ErrCode)     HI_LOG_PrintFuncErr(Func, ErrCode)
#define TEE_AVPLAY_PrintErrCode(ErrCode)           HI_LOG_PrintErrCode(ErrCode)

#define TEE_AVPLAY_LOG_PrintS32(val)               HI_LOG_PrintS32(val)
#define TEE_AVPLAY_LOG_PrintU32(val)               HI_LOG_PrintU32(val)
#define TEE_AVPLAY_LOG_PrintS64(val)               HI_LOG_PrintS64(val)
#define TEE_AVPLAY_LOG_PrintU64(val)               HI_LOG_PrintU64(val)
#define TEE_AVPLAY_LOG_PrintH32(val)               HI_LOG_PrintH32(val)
#define TEE_AVPLAY_LOG_PrintH64(val)               HI_LOG_PrintH64(val)
#define TEE_AVPLAY_LOG_PrintStr(val)               HI_LOG_PrintStr(val)
#define TEE_AVPLAY_LOG_PrintVoid(val)              HI_LOG_PrintVoid(val)
#define TEE_AVPLAY_LOG_PrintFloat(val)             HI_LOG_PrintFloat(val)
#define TEE_AVPLAY_LOG_PrintInfo(val)              HI_LOG_PrintInfo(val)

#define TEE_AVPLAY_LOG_CHECK_PARAM(bVal)           HI_TEE_LOG_CHECK_PARAM(bVal)
#define TEE_AVPLAY_LOG_CHECK(fnFunc)               HI_TEE_LOG_CHECK(fnFunc)
#define TEE_AVPLAY_LOG_CHECK_INITED(u32InitCount)  HI_TEE_LOG_CHECK_INITED(u32InitCount)

#define TEE_AVPLAY_DBG_PrintS32(val)               HI_DBG_PrintS32(val)
#define TEE_AVPLAY_DBG_PrintU32(val)               HI_DBG_PrintU32(val)
#define TEE_AVPLAY_DBG_PrintS64(val)               HI_DBG_PrintS64(val)
#define TEE_AVPLAY_DBG_PrintU64(val)               HI_DBG_PrintU64(val)
#define TEE_AVPLAY_DBG_PrintH32(val)               HI_DBG_PrintH32(val)
#define TEE_AVPLAY_DBG_PrintH64(val)               HI_DBG_PrintH64(val)
#define TEE_AVPLAY_DBG_PrintStr(val)               HI_DBG_PrintStr(val)
#define TEE_AVPLAY_DBG_PrintVoid(val)              HI_DBG_PrintVoid(val)
#define TEE_AVPLAY_DBG_PrintFloat(val)             HI_DBG_PrintFloat(val)
#define TEE_AVPLAY_DBG_PrintInfo(val)              HI_DBG_PrintInfo(val)

HI_S32 TEE_AVPLAY_Ree2TeeMemCopy(TEE_Param stParams[4]);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
