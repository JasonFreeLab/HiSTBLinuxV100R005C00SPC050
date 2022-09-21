/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_common_ca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad_common_ca.h"
#include "hal_klad.h"
#include "hal_klad_common_ca.h"
#include "hal_klad_basic_reg.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_common_ca.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

KLAD_DRV_ZONE g_klad_common_ca_drv_zone;


static HI_S32 DRV_KLAD_COMMON_CA_CheckHalError(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0;

    ret = HAL_KLAD_CheckState();
    if (ret != HI_SUCCESS)
    {
        state = HAL_KLAD_COMMON_CA_GetState();
        HI_ERR_KLAD("common ca klad state %#x\n", state);
    }

    return ret;
}

static HI_S32 DRV_KLAD_COMMON_CA_SetCSA2Key(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (HI_TRUE != session->attr_flag)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;
    DRV_KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);

    level = HAL_KLAD_COMMON_CA_CSA2GetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index=0; index<level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_CSA2Start(index, (HI_U8)alg, addr, 0);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_CSA2Start(level-1, alg, addr, (HI_U8)session->content_key.odd);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetCSA3Key(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (HI_TRUE != session->attr_flag)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;
    DRV_KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);

    level = HAL_KLAD_COMMON_CA_CSA3GetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index=0; index<level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_CSA3Start(index, (HI_U8)alg, addr, 0);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_CSA3Start(level-1, alg, addr, (HI_U8)session->content_key.odd);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetSPKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_SPGetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index = 0; index < level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_SPStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);
        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }
    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_SPStart(level-1, (HI_U8)alg, addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetR2RKey(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_R2RGetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index=0; index<level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_R2RStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);
        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (ret != HI_SUCCESS)
        {
            return ret;
        }
    }

    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_R2RStart(level-1, (HI_U8)alg, addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetMISCKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_MISCGetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index=0; index<level-1; index++)
    {
        if (HI_TRUE != session->sessiong_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_MISCStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }
    // set content key
    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_MISCStart(level-1, (HI_U8)alg, addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(session);

    mutex_lock(&g_klad_mutex);

    switch (session->attr.klad_type)
    {
        case HI_UNF_KLAD_COMMON_CA_TYPE_CSA2:
        {
            ret = DRV_KLAD_COMMON_CA_SetCSA2Key(handle, session);
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_CSA3:
        {
            ret = DRV_KLAD_COMMON_CA_SetCSA3Key(handle, session);
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_SP:
        {
            ret = DRV_KLAD_COMMON_CA_SetSPKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_R2R:
        {
            ret = DRV_KLAD_COMMON_CA_SetR2RKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_MISC:
        {
            ret = DRV_KLAD_COMMON_CA_SetMISCKey(handle, session);
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

    KLAD_FUNC_EXIT();
    return ret;
}

static HI_S32 DRV_KLAD_COMMON_CA_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SetContentKey failed. [%#x]\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_GetSession failed. [%x]\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    ret = DRV_KLAD_COMMON_CA_Crypto(*(HI_HANDLE *)arg, session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_COMMON_CA_Crypto failed. [%x]\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static DRV_KLAD_IOCTL_S s_klad_IO_ctl[] =
{
    {CMD_KLAD_CREATE,           DRV_KLAD_Create},
    {CMD_KLAD_DESTORY,          DRV_KLAD_Destory},
    {CMD_KLAD_ATTACH,           DRV_KLAD_Attach},
    {CMD_KLAD_DETACH,           DRV_KLAD_Detach},
    {CMD_KLAD_GET_ATTR,         DRV_KLAD_GetAttr},
    {CMD_KLAD_SET_ATTR,         DRV_KLAD_SetAttr},
    {CMD_KLAD_SET_SESSION_KEY,  DRV_KLAD_SetSessionKey},
    {CMD_KLAD_SET_CONTENT_KEY,  DRV_KLAD_COMMON_CA_SetContentKey},
    {CMD_KLAD_GET_DBG,          DRV_KLAD_GetDBG},
    {CMD_KLAD_SET_CONTENT_IV,   DRV_KLAD_SetContentIV}
};

static HI_S32 DRV_KLAD_COMMON_CA_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    cmd_num = sizeof(s_klad_IO_ctl) / sizeof(s_klad_IO_ctl[0]);
    for (loop=0; loop<cmd_num; loop++)
    {
        if (s_klad_IO_ctl[loop].cmd == cmd)
        {
            ret = s_klad_IO_ctl[loop].f_driver_cmd_process(arg);
            KLAD_FUNC_EXIT();
            return ret;
        }
    }

    KLAD_FUNC_EXIT();

    return HI_ERR_KLAD_INVALID_PARA;
}


HI_S32 DRV_KLAD_COMMON_CA_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    HAL_KLAD_WriteReg(KL_C5_SEC_EN, 0x1f);
    HAL_KLAD_WriteReg(KL_SEC_EN_LOCK, 0x1);

    KLAD_FUNC_ENTER();
    memset(&g_klad_common_ca_drv_zone, 0x0, sizeof (KLAD_DRV_ZONE));

    g_klad_common_ca_drv_zone.ca = CA_ID_COMMON_CA;
    g_klad_common_ca_drv_zone.ioctl = DRV_KLAD_COMMON_CA_Ioctl;

    ret = DRV_KLAD_Register(&g_klad_common_ca_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_COMMON_CA_Exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_KLAD_UnRegister(&g_klad_common_ca_drv_zone);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_UnRegister failed. [%#x]\n", ret);
        return ret;
    }

    memset(&g_klad_common_ca_drv_zone, 0x0, sizeof (KLAD_DRV_ZONE));

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
