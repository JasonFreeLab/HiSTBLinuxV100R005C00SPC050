/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_advca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "hi_unf_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 g_klad_fd = -1;
HI_S32 g_klad_init_nm = -1;

#define MODID(handle)     (((handle) >> 16) & 0xffff)

#define KLAD_CHECKPOINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            HI_ERR_KLAD("pointer parameter is NULL.\n"); \
            return HI_ERR_KLAD_INVALID_PARA; \
        } \
    } while (0)

#define KLAD_CHECKINIT \
    do{ \
        if (g_klad_init_nm <= 0)\
        {\
            HI_ERR_KLAD("klad is not inited\n");\
            return HI_ERR_KLAD_NOT_INIT;\
        }\
    }while(0)

#define KLAD_CHECKKLADTYPE(type) \
    do{ \
        if (type < 0 || type >= 0x3FFF)\
        {\
            HI_ERR_KLAD("klad type(0x%x) is invalid\n", type);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)
#define KLAD_CHECKHANDLE(handle) \
    do{ \
        if (MODID(handle) != HI_ID_KLAD)\
        {\
            HI_ERR_KLAD("klad handle(0x%x) is invalid\n", handle);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)
#define KLAD_CHECKTARGET(target) \
    do{ \
        if (target <= 0)\
        { \
            HI_ERR_KLAD("target handle(0x%x) is invalid\n", target);\
            return HI_ERR_KLAD_INVALID_PARA;\
        } \
    }while(0)
#define KLAD_CHECKALG(alg) \
    do{ \
        if ((alg < HI_UNF_KLAD_ALG_TYPE_TDES) || (alg >= HI_UNF_KLAD_ALG_TYPE_BUTT))\
        {\
            HI_ERR_KLAD("alg(0x%x) is invalid\n", alg);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)
#define KLAD_CHECKENGINE(engine) \
    do{ \
        if (engine < HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA2 || engine >= HI_UNF_KLAD_TARGET_ENGINE_BUTT)\
        {\
            HI_ERR_KLAD("engine(0x%x) is invalid\n", engine);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)
#define KLAD_CHECKKEYLEVEL(level) \
    do{ \
        if (level < HI_UNF_KLAD_LEVEL1 || level >= HI_UNF_KLAD_LEVEL_BUTT) \
        {\
            HI_ERR_KLAD("level(0x%x) is invalid\n", level);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)
#define KLAD_CHECKEVEN(even) \
    do{ \
        if ((HI_TRUE != even) && (HI_FALSE != even)) \
        {\
            HI_ERR_KLAD("even(0x%x) is invalid\n", even);\
            return HI_ERR_KLAD_INVALID_PARA;\
        }\
    }while(0)

HI_S32 HI_UNF_KLAD_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    if (g_klad_init_nm > 0)
    {
        g_klad_init_nm++;

        KLAD_FUNC_EXIT();
        return HI_SUCCESS;
    }

    ret = KLAD_ModInit();
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    g_klad_init_nm = 1;
    g_klad_fd = 1;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_DeInit(HI_VOID)
{
    KLAD_FUNC_ENTER();

    if (g_klad_init_nm > 0)
    {
        g_klad_init_nm--;
    }

    if (g_klad_init_nm != 0)
    {
        KLAD_FUNC_EXIT();
        return HI_SUCCESS;
    }

    g_klad_fd   = -1;
    g_klad_init_nm = -1;

    KLAD_ModExit();
    KLAD_FUNC_EXIT();

    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Create(const HI_U32 kladType, HI_HANDLE *phKlad)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_HANDLE_S ctl_handle = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKKLADTYPE(kladType);
    KLAD_CHECKPOINTER(phKlad);

    ctl_handle.klad = kladType;

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_CREATE, &ctl_handle);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_CREATE error:%x.\n", ret);
        return ret;
    }

    *phKlad = ctl_handle.create_handle;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Destroy(const HI_HANDLE hKlad)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE handle = HI_INVALID_HANDLE;

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;

    KLAD_CHECKHANDLE(hKlad);
    handle = hKlad;
    ret = BOOT_KLAD_Ioctl(CMD_KLAD_DESTORY, &handle);
    if (ret != HI_SUCCESS)
    {
        KLAD_FUNC_EXIT();
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_DESTORY error:%x.\n", ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Attach(const HI_HANDLE hKlad, const HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;

    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKTARGET(hTarget);
    target.handle = hKlad;
    target.target = hTarget;

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_ATTACH, &target);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_ATTACH error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Detach(const HI_HANDLE hKlad, const HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;

    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKTARGET(hTarget);
    target.handle = hKlad;
    target.target = hTarget;

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_DETACH, &target);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_DETACH error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetAttr(const HI_HANDLE hKlad, const HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKPOINTER(pstAttr);

    attr.handle = hKlad;
    attr.attr.alg = pstAttr->enAlg;
    attr.attr.engine = pstAttr->enEngine;
    KLAD_CHECKALG(attr.attr.alg);
    KLAD_CHECKENGINE(attr.attr.engine);

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_SET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_ATTR error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GetAttr(const HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKPOINTER(pstAttr);

    attr.handle = hKlad;

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_GET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_GET_ATTR error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    pstAttr->enAlg = attr.attr.alg;
    pstAttr->enEngine = attr.attr.engine;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetSessionKey(const HI_HANDLE hKlad, const HI_UNF_KLAD_SESSION_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_SESSION_KEY_S key = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKPOINTER(pstKey);

    key.handle = hKlad;
    key.session_key.level = pstKey->enLevel;
    memcpy(key.session_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECKKEYLEVEL(key.session_key.level);

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_SET_SESSION_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_SESSION_KEY error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


HI_S32 HI_UNF_KLAD_SetContentKey(const HI_HANDLE hKlad, const HI_UNF_KLAD_CONTENT_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_KEY_S key = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKPOINTER(pstKey);

    key.handle = hKlad;
    key.content_key.odd = pstKey->bOdd;
    memcpy(key.content_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECKEVEN(key.content_key.odd);

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_SET_CONTENT_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_CONTENT_KEY error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GenerateEncKey(const HI_HANDLE hKlad, HI_UNF_KLAD_ENC_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S key = {0};

    KLAD_FUNC_ENTER();

    KLAD_CHECKINIT;
    KLAD_CHECKHANDLE(hKlad);
    KLAD_CHECKPOINTER(pstKey);

    key.handle = hKlad;
    memcpy(key.key.clear_key, pstKey->au8ClearKey, HI_UNF_KLAD_MAX_KEY_LEN);

    ret = BOOT_KLAD_Ioctl(CMD_KLAD_GEN_ENC_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_GEN_ENC_KEY error:%x.\n", ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    memcpy(pstKey->au8EncKey, key.key.enc_key, HI_UNF_KLAD_MAX_KEY_LEN);

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
