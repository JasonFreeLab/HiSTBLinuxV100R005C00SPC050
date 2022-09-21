/****************************************************************************
 *             Copyright 2016, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: tee_drv_log.h
 * Description:
 *
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * 1.0       2016-12-13              NULL         Create
 ****************************************************************************/
#ifndef __TEE_DRV_LOG_H__
#define __TEE_DRV_LOG_H__

#include "hi_type.h"
#include "hi_tee_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

HI_S32  TEE_DRV_LOG_Set_LogLevel(HI_MODULE_ID_E ModId, HI_TEE_LOG_LEVEL_E LogLevel);
HI_S32  TEE_DRV_LOG_Get_LogLevel(HI_MODULE_ID_E ModId, HI_TEE_LOG_LEVEL_E *pLogLevel);
HI_VOID HI_TEE_LogOut(HI_TEE_LOG_LEVEL_E LogLevel, HI_MODULE_ID_E ModId, HI_U8 *pFuncName, HI_U32 LineNum, const HI_CHAR *format, ...);

#ifdef __cplusplus
}
#endif

#endif /*__TEE_DRV_LOG_H__*/

