/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_advca.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#include "hi_unf_advca.h"
#include "drv_advca_ext.h"
#include "drv_advca.h"
#include "hi_module.h"
#include "hi_common.h"
#include "hi_drv_otp.h"
#include "hi_drv_sys.h"
#include "hi_drv_dev.h"
#include "hi_error_mpi.h"
#include "drv_advca_ioctl.h"
#include "drv_advca.h"
#include "hi_drv_struct.h"
#include "drv_tee_advca.h"
#ifdef HI_TEE_SUPPORT
#include "teek_client_api.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef HI_TEE_SUPPORT
typedef struct hiDmx_Teec_S
{
    TEEC_Context context;
    TEEC_Session session;
    HI_BOOL  connected;
    struct mutex lock;
}klad_teec_s;
klad_teec_s g_klad_teec;
#define TEEC_CMD_KLAD_OPERATION          0XFF

static HI_S32 DEV_ADVCA_OpenTeec(klad_teec_s *teec)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 sec_id = 0;
    TEEC_Operation operation;
    HI_CHAR session_name[] = "tee_keyladder_session";

    TEEC_UUID klad_task_uuid =
    {
        0xc9cf6b2a,
        0x4b60, 
        0x11e7, 
        {0xa9, 0x19, 0x92, 0xeb, 0xcb, 0x67, 0xfe, 0x33 }
    };
    mutex_lock(&teec->lock);
    if (unlikely(HI_TRUE == teec->connected))
    {
        ret = HI_SUCCESS;
        goto out0;
    }

    ret = TEEK_InitializeContext(NULL, &teec->context);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Initialise klad teec context failed(0x%x)\n", ret);
        goto out1;
    }

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&sec_id);
    operation.params[2].tmpref.size = sizeof(sec_id);
    operation.params[3].tmpref.buffer = (void *)(session_name);
    operation.params[3].tmpref.size = strlen(session_name) + 1;

    ret = TEEK_OpenSession(&teec->context, &teec->session, &klad_task_uuid, TEEC_LOGIN_IDENTIFY, NULL, &operation, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("open klad teec session failed(0x%x)\n", ret);
        goto out2;
    }
    teec->connected = HI_TRUE;
    mutex_unlock(&teec->lock);
    return HI_SUCCESS;

out2:
    TEEK_FinalizeContext(&teec->context);
out1:
    teec->connected = HI_FALSE;
out0:
    mutex_unlock(&teec->lock);
    return ret;
}

static HI_VOID DEV_ADVCA_CloseTeec(klad_teec_s *teec)
{
    mutex_lock(&teec->lock);

    if (HI_TRUE == teec->connected)
    {
        teec->connected = HI_FALSE;

        TEEK_CloseSession(&teec->session);
        TEEK_FinalizeContext(&teec->context);
    }
    mutex_unlock(&teec->lock);
    return;
}

static HI_S32 DEV_ADVCA_SendCmdToTA(HI_U32 cmd_id, TEEC_Operation *operation, HI_U32 *ret_origin)
{
    HI_S32 ret = HI_FAILURE;
    klad_teec_s *teec = &g_klad_teec;

    if (unlikely(HI_FALSE == teec->connected))
    {
        ret = DEV_ADVCA_OpenTeec(teec);
        if (HI_SUCCESS != ret)
        {
            goto out;
        }
    }
    ret = TEEK_InvokeCommand(&teec->session, cmd_id, operation, ret_origin);
out:
    return ret;
}

HI_S32 DEV_ADVCA_TeecSetKey(klad_session_para_s * parameter)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].tmpref.buffer = (void *)parameter;
    operation.params[0].tmpref.size = sizeof(klad_session_para_s);
    ret = DEV_ADVCA_SendCmdToTA(TEEC_CMD_KLAD_OPERATION, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("send TEEC_CMD_KLAD_OPERATION to TA failed(0x%x).\n", ret);
        ret = HI_FAILURE;
        goto out;
    }
out:
    return ret;
}

HI_S32 DEV_ADVCA_InitTeec(HI_VOID)
{
    memset(&g_klad_teec, 0, sizeof(klad_teec_s));
    mutex_init(&g_klad_teec.lock);
    return DEV_ADVCA_OpenTeec(&g_klad_teec);
}

HI_S32 DEV_ADVCA_DeInitTeec(HI_VOID)
{
    DEV_ADVCA_CloseTeec(&g_klad_teec);
    memset(&g_klad_teec, 0, sizeof(klad_teec_s));
    return HI_SUCCESS;
}
#else
HI_S32 DEV_ADVCA_TeecSetKey(klad_session_para_s * parameter)
{
    return HI_SUCCESS;
}

HI_S32 DEV_ADVCA_InitTeec(HI_VOID)
{
    return HI_SUCCESS;
}
HI_S32 DEV_ADVCA_DeInitTeec(HI_VOID)
{
    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
