/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_cert.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_CERT_H__
#define __DRV_CERT_H__

/* add include here */
#include "hi_tee_drv_klad.h"
#include "tee_hal_cert.h"
#include "tee_drv_cert_ioctl.h"
#include "tee_os_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    HI_TEE_CERT_TARGET_ENGINE_E engine;
    HI_U8 sw_type;
} TARGET_ENGINE_MAP;


typedef struct
{
    HI_U32 owner;
    struct tee_hal_mutex g_cert_mutex;
    struct tee_hal_mutex g_lock_hw;
} DRV_CERT_SESSION_S;

extern DRV_CERT_SESSION_S g_cert_session;


#define  NUM_CERT_TIMEOUT_DEFAULT  500000   /*500*1000*10us = 5s*/
#define  NUM_CERT_TIMEOUT_OTP      1000000  /*1000*1000*10us = 10s*/

#define CERT_CHECK_KEYHANDLE(handle) \
    do \
    {  \
        if (handle != (HI_HANDLE)(g_cert_session.owner))\
        { \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_HANDLE);\
            return HI_ERR_KLAD_INVALID_HANDLE; \
        }  \
    } while (0)

#define TEE_CERT_CMD_INVALID(cmd) \
    ((cmd != CMD_CERT_AKLEXCHANGE) \
     && (cmd != CMD_CERT_AKLKEYSEND_CTL) \
     && (cmd != CMD_CERT_LOCK) \
     && (cmd != CMD_CERT_UNLOCK) \
     && (cmd != CMD_CERT_AKLSETIV) \
     && (cmd != CMD_CERT_READL) \
     && (cmd != CMD_CERT_WRITEL))

#define TEE_CERT_CMD_CHECK(cmd) \
    if (TEE_CERT_CMD_INVALID(cmd)) \
    { \
        KLAD_PrintErrorCode(HI_ERR_KLAD_CERT_UNKNOWN_CMD);\
        return HI_ERR_KLAD_CERT_UNKNOWN_CMD; \
    }

/***************************** Func Definition ******************************/
HI_S32 DRV_CERT_Init(HI_VOID);
HI_VOID DRV_CERT_DeInit(HI_VOID);
HI_VOID DRV_CERT_Suspend(HI_VOID);
HI_S32 DRV_CERT_Resume(HI_VOID);
HI_S32 HI_DRV_CERT_Lock(HI_TEE_CERT_RES_HANDLE* handle);
HI_S32 HI_DRV_CERT_UnLock(HI_TEE_CERT_RES_HANDLE* handle);
HI_VOID HI_DRV_CERT_Reset(HI_VOID);
HI_S32 HI_DRV_CERT_AklExchange(CERT_CMD_CTL* cmd_ctl);
HI_S32 HI_DRV_CERT_AklKeySndCtl(HI_TEE_CERT_KEY_DATA_S* key_ctl);
HI_S32 HI_DRV_CERT_AklSetIV(HI_TEE_CERT_IV_S* iv_ctl);

#ifdef __cplusplus
}
#endif
#endif /* __DRV_CERT_H__ */
