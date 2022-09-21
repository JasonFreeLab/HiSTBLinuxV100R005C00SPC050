/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_dcas.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-21
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad_dcas.h"
#include "hal_klad.h"
#include "hal_klad_dcas.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_dcas.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static KLAD_DRV_ZONE g_klad_dcas_drv_zone;

static HI_S32 DRV_KLAD_DCAS_CheckHalError(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0;

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_DCAS_GetState();
        HI_ERR_KLAD("dcas klad state %#x\n", state);
    }

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_SetRkdKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_CONTENT_KEY;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_DCAS_RKDStart();

    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_DCAS_SetK30Key(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    HI_UNF_KLAD_TARGET_ENGINE_E engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (HI_TRUE != session->attr_flag)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;
    DRV_KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    target = DRV_KLAD_GetTarget(session);
    DRV_KLAD_CHECK_TARGET(target, DRV_KLAD_TARGET_BUTT);

    engine = session->attr.engine;
    // TODO: check valid

    addr = HI_HANDLE_GET_CHNID(session->target);
    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }

    level = HAL_KLAD_DCAS_K30GetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index = 0; index < level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_SESSION_KEY;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_DCAS_K30Start(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);

        ret = DRV_KLAD_DCAS_CheckHalError();
        if (ret != HI_SUCCESS)
        {
            return ret;
        }
    }

    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_CONTENT_KEY;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_DCAS_K30Start(index, (HI_U8)alg, addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    ret = DRV_KLAD_DCAS_CheckHalError();

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;

    DRV_KLAD_CHECK_NULL_PTR(session);

    mutex_lock(&g_klad_mutex);

    switch (session->attr.klad_type)
    {
        case HI_UNF_KLAD_DCAS_TYPE_RKD:
        {
            ret = DRV_KLAD_DCAS_SetRkdKey(handle, session);
            break;
        }
        case HI_UNF_KLAD_DCAS_TYPE_K30:
        {
            ret = DRV_KLAD_DCAS_SetK30Key(handle, session);
            break;
        }

        default:
        {
            ret = HI_ERR_KLAD_NOT_SUPPORT;
            HI_ERR_KLAD("not support klad type %#x\n", session->attr.klad_type);
            break;
        }
    }

    mutex_unlock(&g_klad_mutex);

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SetContentKey failed. [%#x]\n", ret);
        return ret;
    }

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_GetSession failed. [%#x]\n", ret);
        return ret;
    }

    ret = DRV_KLAD_DCAS_Crypto(*(HI_HANDLE *)arg, session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_NAGRA_Crypto failed. [%#x]\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_DCAS_K30GenDaNonce(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_DA_NONCE_S *da_nonce;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    DRV_KLAD_SESSION *session = HI_NULL;
    HI_U32 state = 0;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    da_nonce = (KLAD_CTL_DA_NONCE_S*)arg;

    ret = DRV_KLAD_GetSession(da_nonce->handle, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_GetSession failed. [%#x]\n", ret);
        return ret;
    }

    if (session->attr_flag == HI_FALSE)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;
    DRV_KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    if (HI_TRUE != session->sessiong_key_flag[0])
    {
        HI_ERR_KLAD("Not set level1 session key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_SESSION_KEY;
    }
    HAL_KLAD_SetDataIn(session->session_key[0].key);
    HAL_KLAD_DCAS_K30Start((HI_U8)HI_UNF_KLAD_LEVEL1, (HI_U8)alg, 0, 0, 0, 0);
    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    HAL_KLAD_SetDataIn(da_nonce->nonce);
    HAL_KLAD_DCAS_K30Start((HI_U8)HI_UNF_KLAD_LEVEL4, (HI_U8)alg, 0, 0, 0, 0);

    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    state = HAL_KLAD_DCAS_K30GetDaNonceState();
    if (state != 0x1)
    {
        HI_ERR_KLAD("K3_0 DANonce not ready\n");
        return HI_ERR_KLAD_KEY_NOT_READY;
    }

    HAL_KLAD_DCAS_K30GetDaNonce(da_nonce->da_nonce);

    return HI_SUCCESS;
}

static DRV_KLAD_IOCTL_S g_klad_dcas_ioctl[] =
{
    {CMD_KLAD_CREATE,           DRV_KLAD_Create},
    {CMD_KLAD_DESTORY,          DRV_KLAD_Destory},
    {CMD_KLAD_ATTACH,           DRV_KLAD_Attach},
    {CMD_KLAD_DETACH,           DRV_KLAD_Detach},
    {CMD_KLAD_GET_ATTR,         DRV_KLAD_GetAttr},
    {CMD_KLAD_SET_ATTR,         DRV_KLAD_SetAttr},
    {CMD_KLAD_SET_SESSION_KEY,  DRV_KLAD_SetSessionKey},
    {CMD_KLAD_SET_CONTENT_KEY,  DRV_KLAD_DCAS_SetContentKey},
    {CMD_KLAD_GET_DBG,          DRV_KLAD_GetDBG},
    {CMD_KLAD_GEN_K30_DA_NONCE,  DRV_KLAD_DCAS_K30GenDaNonce},
};

static HI_S32 DRV_KLAD_DCAS_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    cmd_num = sizeof(g_klad_dcas_ioctl) / sizeof(g_klad_dcas_ioctl[0]);
    for (loop=0; loop<cmd_num; loop++)
    {
        if (g_klad_dcas_ioctl[loop].cmd == cmd)
        {
            return g_klad_dcas_ioctl[loop].f_driver_cmd_process(arg);
        }
    }

    HI_ERR_KLAD("not support cmd %d\n", cmd);

    return HI_ERR_KLAD_INVALID_PARA;
}

HI_S32 DRV_KLAD_DCAS_FuncInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    memset(&g_klad_dcas_drv_zone, 0x00, sizeof(KLAD_DRV_ZONE));

    g_klad_dcas_drv_zone.ca = CA_ID_DCAS;
    g_klad_dcas_drv_zone.ioctl = DRV_KLAD_DCAS_Ioctl;

    ret = DRV_KLAD_Register(&g_klad_dcas_drv_zone);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_Register failed. [%#x]\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_DCAS_FuncExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_KLAD_UnRegister(&g_klad_dcas_drv_zone);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_UnRegister failed. [%#x]\n", ret);
        return ret;
    }

    memset(&g_klad_dcas_drv_zone, 0x00, sizeof(KLAD_DRV_ZONE));

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
