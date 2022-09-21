/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_basic.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad.h"
#include "hal_klad.h"
#include "drv_klad.h"
#include "hal_klad_basic.h"
#include "drv_klad_ioctl.h"
#include "drv_klad_basic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static KLAD_DRV_ZONE s_klad_basic_drv_zone;

static HI_S32 DRV_KLAD_BASIC_SetBOOTKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0x0;
    HI_U8 addr = 0x0;
    HI_U8 decrypt = 0x1;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (session->attr_flag == HI_FALSE)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;

    target = DRV_KLAD_GetTarget(session);
    if (DRV_KLAD_TARGET_MULTI_CIPHER != target)
    {
        HI_ERR_KLAD("invalid target: %d\n", target);
        return HI_ERR_KLAD_INVALID_PARA;
    }

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);

    HAL_KLAD_BOOTStart((HI_U8)alg, decrypt, addr, (HI_U8)target);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_BOOTGetState();
        HI_ERR_KLAD("BOOT klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SetSWKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0x0;
    HI_U8 addr = 0x0;
    HI_U8 decrypt = 0x1;

    DRV_KLAD_CHECK_NULL_PTR(session);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_SWStart(decrypt, addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_SWGetState();
        HI_ERR_KLAD("SW klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}

#if 0 // 2017/02/07 - 17:35:17,
static HI_S32 DRV_KLAD_BASIC_SetWIDEVINEKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0x0;
    HI_U8 addr = 0x0;
    HI_U8 decrypt = 0x1;
    HI_U8 level = 0;
    HI_U8 index = 0;

    DRV_KLAD_CHECK_NULL_PTR(session);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    level = HAL_KLAD_WIDEVINEGetLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    // set session key
    for (index = 0; index< level-1; index++)
    {
        if (session->sessiong_key_flag[index] != HI_TRUE)
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_WIDEVINEStart(index, (HI_U8)decrypt, addr);

        ret = HAL_KLAD_CheckState();
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
    HAL_KLAD_WIDEVINEStart(level-1, (HI_U8)decrypt, addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_WIDEVINEGetState();
        HI_ERR_KLAD("WIDEVINE klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SetCATAKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U32 state = 0x0;

    DRV_KLAD_CHECK_NULL_PTR(session);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_CA_TAStart(addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_CA_TAGetState();
        HI_ERR_KLAD("CA TA klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SetSTBTAKey(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U32 state = 0x0;

    DRV_KLAD_CHECK_NULL_PTR(session);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_STB_TAStart(addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_STB_TAGetState();
        HI_ERR_KLAD("STB TA klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SetSTBIMAGEKey(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U32 state = 0x0;

    DRV_KLAD_CHECK_NULL_PTR(session);

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_STB_IMAGEStart(addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_STB_IMAGEGetState();
        HI_ERR_KLAD("STB IMAGE klad state [%#x]\n", state);
        return ret;
    }

    return HI_SUCCESS;
}
#endif

static HI_S32 DRV_KLAD_BASIC_SetCLEARCWKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;
    HI_UNF_KLAD_TARGET_ENGINE_E engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;

    DRV_KLAD_CHECK_NULL_PTR(session);

    target = DRV_KLAD_GetTarget(session);
    DRV_KLAD_CHECK_TARGET(target, DRV_KLAD_TARGET_BUTT);

    addr = HI_HANDLE_GET_CHNID(session->target);
    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }

    if (HI_TRUE != session->attr_flag)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }
    engine = session->attr.engine;
    // TODO: check valid

    if (HI_TRUE != session->content_key_flag)
    {
        HI_ERR_KLAD("Not set content key to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    HAL_KLAD_SetClearCwDataIn(session->content_key.key);
    HAL_KLAD_CLEAR_CWStart(addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;

    DRV_KLAD_CHECK_NULL_PTR(session);

    mutex_lock(&g_klad_mutex);

    switch (session->attr.klad_type)
    {
        case HI_UNF_KLAD_TYPE_BLPK:
        {
            ret = DRV_KLAD_BASIC_SetBOOTKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_TYPE_SWPK:
        {
            ret = DRV_KLAD_BASIC_SetSWKey(handle, session);
            break;
        }

#if 0 // 2017/02/07 - 17:35:06,
        case HI_UNF_KLAD_TYPE_WIDEVINE:
        {
            ret = DRV_KLAD_BASIC_SetWIDEVINEKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_TYPE_CATA:
        {
            ret = DRV_KLAD_BASIC_SetCATAKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_TYPE_STBTA:
        {
            ret = DRV_KLAD_BASIC_SetSTBTAKey(handle, session);
            break;
        }

        case HI_UNF_KLAD_TYPE_STBIMAGE:
        {
            ret = DRV_KLAD_BASIC_SetSTBIMAGEKey(handle, session);
            break;
        }
#endif

        case HI_UNF_KLAD_TYPE_CLEARCW:
        {
            ret = DRV_KLAD_BASIC_SetCLEARCWKey(handle, session);
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

static HI_S32 DRV_KLAD_BASIC_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (ret != HI_SUCCESS)
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

    ret = DRV_KLAD_BASIC_Crypto(session->handle, session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_NAGRA_Crypto failed. [%#x]\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_BOOTGenEncKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S *enc_key = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    HI_U8 decrypt = 0x0;
    HI_U32 state = 0;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
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

    enc_key = (KLAD_CTL_ENC_CLEAR_KEY_S*)arg;
    HAL_KLAD_SetDataIn(enc_key->key.clear_key);
    HAL_KLAD_BOOTStart((HI_U8)alg, decrypt, 0, 0);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_BOOTGetState();
        HI_ERR_KLAD("BOOT klad state [%#x]\n", state);
        return ret;
    }

    HAL_KLAD_BOOTGetEncRslt(enc_key->key.enc_key);

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SWGenEncKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S *enc_key = HI_NULL;
    HI_U8 decrypt = 0x0;
    HI_U32 state = 0;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    enc_key = (KLAD_CTL_ENC_CLEAR_KEY_S*)arg;
    HAL_KLAD_SetDataIn(enc_key->key.clear_key);
    HAL_KLAD_SWStart(decrypt, 0);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_SWGetState();
        HI_ERR_KLAD("SW klad state [%#x]\n", state);
        return ret;
    }

    HAL_KLAD_SWGetEncRslt(enc_key->key.enc_key);

    return HI_SUCCESS;
}

#if 0 // 2017/02/07 - 17:36:06,
static HI_S32 DRV_KLAD_BASIC_WIDEVINEGenEncKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S *enc_key = HI_NULL;
    HI_U8 decrypt = 0x0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_U32 state = 0;
    HI_U8 addr = 0x0;
    DRV_KLAD_SESSION *session = HI_NULL;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    enc_key = (KLAD_CTL_ENC_CLEAR_KEY_S*)arg;

    ret = DRV_KLAD_GetSession(enc_key->handle, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_GetSession failed. [%#x]\n", ret);
        return ret;
    }

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    level = HAL_KLAD_WIDEVINEGetLevel();
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
        HAL_KLAD_WIDEVINEStart(index, (HI_U8)decrypt, addr);

        ret = HAL_KLAD_CheckState();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    // set content key
    HAL_KLAD_SetDataIn(enc_key->key.clear_key);
    HAL_KLAD_WIDEVINEStart(level-1, decrypt, 0);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_WIDEVINEGetState();
        HI_ERR_KLAD("WIDEVINE klad state [%#x]\n", state);
        return ret;
    }

    HAL_KLAD_WIDEVINEGetEncRslt(enc_key->key.enc_key);

    return HI_SUCCESS;
}
#endif

static HI_S32 DRV_KLAD_BASIC_GenEncKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE klad_handle = HI_INVALID_HANDLE;
    KLAD_CTL_ENC_CLEAR_KEY_S *key = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    key = (KLAD_CTL_ENC_CLEAR_KEY_S *) arg;

    klad_handle = key->handle;

    ret = DRV_KLAD_GetSession(klad_handle, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("not support klad type: 0x%x\n", session->klad_type);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    memcpy(session->content_key.key, key->key.clear_key, 16);
    session->content_key_flag = HI_TRUE;

    mutex_lock(&g_klad_mutex);

    switch (session->klad_type)
    {
        case HI_UNF_KLAD_TYPE_BLPK:
        {
            ret = DRV_KLAD_BASIC_BOOTGenEncKey(arg);
            break;
        }

        case HI_UNF_KLAD_TYPE_SWPK:
        {
            ret = DRV_KLAD_BASIC_SWGenEncKey(arg);
            break;
        }

#if 0 // 2017/02/07 - 17:36:00,
        case HI_UNF_KLAD_TYPE_WIDEVINE:
        {
            ret = DRV_KLAD_BASIC_WIDEVINEGenEncKey(arg);
            break;
        }
#endif

        default:
        {
            ret = HI_ERR_KLAD_NOT_SUPPORT;
            HI_ERR_KLAD("not support klad type %#x\n", session->klad_type);
            break;
        }
    }

    mutex_unlock(&g_klad_mutex);

    KLAD_FUNC_EXIT();
    return ret;
}

static HI_S32 DRV_KLAD_BASIC_WIDEVINEGetDecFlag(HI_VOID* arg)
{
    KLAD_CTL_WIDEVINE_DEC_FLAG_S *ctl_handle;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_handle = (KLAD_CTL_WIDEVINE_DEC_FLAG_S*)arg;
    ctl_handle->flag = HAL_KLAD_WIDEVINEGetDecFlag();

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_STBROOTKEYSendToCipher(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    DRV_KLAD_TARGET_E target = 0;
    HI_HANDLE *klad_handle = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    klad_handle = (HI_HANDLE *)arg;

    ret = DRV_KLAD_GetSession(*klad_handle, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("not support klad type: %#x\n", *klad_handle);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    addr = HI_HANDLE_GET_CHNID(session->target);
    DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    target = DRV_KLAD_GetTarget(session);
    if (target != DRV_KLAD_TARGET_MULTI_CIPHER)
    {
        HI_ERR_KLAD("invalid target: %#x\n", session->target);
        KLAD_FUNC_EXIT();
        return HI_ERR_KLAD_INVALID_PARA;
    }

    HAL_KLAD_STB_ROOTKEYStart(addr);
    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return ret;
}

static DRV_KLAD_IOCTL_S s_klad_basic_ioctl[] =
{
    {CMD_KLAD_CREATE,                DRV_KLAD_Create},
    {CMD_KLAD_DESTORY,               DRV_KLAD_Destory},
    {CMD_KLAD_ATTACH,                DRV_KLAD_Attach},
    {CMD_KLAD_DETACH,                DRV_KLAD_Detach},
    {CMD_KLAD_GET_ATTR,              DRV_KLAD_GetAttr},
    {CMD_KLAD_SET_ATTR,              DRV_KLAD_SetAttr},
    {CMD_KLAD_SET_SESSION_KEY,       DRV_KLAD_SetSessionKey},
    {CMD_KLAD_SET_CONTENT_KEY,       DRV_KLAD_BASIC_SetContentKey},
    {CMD_KLAD_GET_DBG,               DRV_KLAD_GetDBG},
    {CMD_KLAD_GEN_ENC_KEY,           DRV_KLAD_BASIC_GenEncKey},
    {CMD_KLAD_WIDEVINE_GET_DEC_FLAG, DRV_KLAD_BASIC_WIDEVINEGetDecFlag},
    {CMD_KLAD_STBROOTKEY2CIPHER,     DRV_KLAD_BASIC_STBROOTKEYSendToCipher},
};

static HI_S32 DRV_KLAD_BASIC_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    cmd_num = sizeof(s_klad_basic_ioctl) / sizeof(s_klad_basic_ioctl[0]);
    for (loop=0; loop<cmd_num; loop++)
    {
        if (s_klad_basic_ioctl[loop].cmd == cmd)
        {
            return s_klad_basic_ioctl[loop].f_driver_cmd_process(arg);
        }
    }

    KLAD_FUNC_EXIT();

    return HI_ERR_KLAD_INVALID_PARA;
}

HI_S32 DRV_KLAD_BASIC_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    memset(&s_klad_basic_drv_zone, 0, sizeof(KLAD_DRV_ZONE));

    s_klad_basic_drv_zone.ca = CA_ID_BASIC;
    s_klad_basic_drv_zone.ioctl= DRV_KLAD_BASIC_Ioctl;

    ret = DRV_KLAD_Register(&s_klad_basic_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    HAL_KLAD_BASIC_SetBasicKladSecen();
    HAL_KLAD_BASIC_SetBasicKladSecenLock();

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_BASIC_Exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_UnRegister(&s_klad_basic_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    memset(&s_klad_basic_drv_zone, 0, sizeof(KLAD_DRV_ZONE));

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
