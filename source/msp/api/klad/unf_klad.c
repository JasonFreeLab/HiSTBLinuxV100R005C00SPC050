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
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_drv_struct.h"
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

#define KLAD_CHECKPOINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            HI_ERR_KLAD("pointer parameter is NULL.\n"); \
            return HI_ERR_KLAD_INVALID_PARA; \
        } \
    } while (0)

#define KLAD_INIT_CHECK \
    do{ \
        if (g_klad_init_nm <= 0)\
        {\
            HI_ERR_KLAD("klad is not inited\n");\
            return HI_ERR_KLAD_NOT_INIT;\
        }\
    }while(0)

HI_S32 HI_UNF_KLAD_Init(HI_VOID)
{
    HI_S32 dev_fd = 0;

    KLAD_FUNC_ENTER();

    if (g_klad_init_nm > 0)
    {
        g_klad_init_nm++;
        return HI_SUCCESS;
    }

    dev_fd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR, 0);
    if (dev_fd < 0)
    {
        HI_ERR_KLAD("klad dev open err. \n");
        KLAD_FUNC_EXIT();
        return HI_ERR_KLAD_OPEN_ERR;
    }

    g_klad_init_nm = 1;
    g_klad_fd = dev_fd;

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

    close(g_klad_fd);
    g_klad_fd   = -1;
    g_klad_init_nm = -1;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Create(HI_HANDLE* phKlad)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_HANDLE_S ctl_handle;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(phKlad);

    memset(&ctl_handle, 0, sizeof(KLAD_CTL_HANDLE_S));

    ret = ioctl(g_klad_fd, CMD_KLAD_CREATE, &ctl_handle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_CREATE error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    *phKlad = ctl_handle.create_handle;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Destroy(HI_HANDLE hKlad)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;

    ret = ioctl(g_klad_fd, CMD_KLAD_DESTORY, &hKlad);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_DESTORY error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Attach(HI_HANDLE hKlad, HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;

    memset(&target, 0, sizeof(KLAD_CTL_TARGET_S));
    target.handle = hKlad;
    target.target = hTarget;

    ret = ioctl(g_klad_fd, CMD_KLAD_ATTACH, &target);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_ATTACH error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Detach(HI_HANDLE hKlad, HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;

    memset(&target, 0, sizeof(KLAD_CTL_TARGET_S));
    target.handle = hKlad;
    target.target = hTarget;

    ret = ioctl(g_klad_fd, CMD_KLAD_DETACH, &target);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_DETACH error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstAttr);

    memset(&attr, 0, sizeof(KLAD_CTL_ATTR_S));
    attr.handle = hKlad;
    attr.attr.klad_type = pstAttr->u32KladType;
    attr.attr.alg = pstAttr->enAlg;
    attr.attr.engine = pstAttr->enEngine;

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_ATTR error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstAttr);

    memset(&attr, 0, sizeof(KLAD_CTL_ATTR_S));
    attr.handle = hKlad;

    ret = ioctl(g_klad_fd, CMD_KLAD_GET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_GET_ATTR error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    pstAttr->enAlg = attr.attr.alg;
    pstAttr->enEngine = attr.attr.engine;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetSessionKey(HI_HANDLE hKlad, HI_UNF_KLAD_SESSION_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_SESSION_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstKey);

    memset(&key, 0, sizeof(KLAD_CTL_SESSION_KEY_S));
    key.handle = hKlad;
    key.session_key.level = pstKey->enLevel;
    memcpy(key.session_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_SESSION_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_SESSION_KEY error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


HI_S32 HI_UNF_KLAD_SetContentKey(HI_HANDLE hKlad, HI_UNF_KLAD_CONTENT_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstKey);

    memset(&key, 0, sizeof(KLAD_CTL_CONTENT_KEY_S));
    key.handle = hKlad;
    key.content_key.odd = pstKey->bOdd;
    memcpy(key.content_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_CONTENT_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_CONTENT_KEY error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetContentIV(HI_HANDLE hKlad, HI_UNF_KLAD_CONTENT_IV_S *pstIV)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_IV_S init_vector;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstIV);

    memset(&init_vector, 0x0, sizeof(KLAD_CTL_CONTENT_IV_S));
    init_vector.handle = hKlad;
    init_vector.content_iv.length = pstIV->u32IVLength;
    init_vector.content_iv.odd = pstIV->bOdd;
    memcpy(init_vector.content_iv.iv, pstIV->au8IV, HI_UNF_KLAD_MAX_KEY_LEN);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_CONTENT_IV, &init_vector);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_SET_CONTENT_KEY error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GenerateEncKey(HI_HANDLE hKlad, HI_UNF_KLAD_ENC_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pstKey);

    memset(&key, 0, sizeof(KLAD_CTL_ENC_CLEAR_KEY_S));
    key.handle = hKlad;
    memcpy(key.key.clear_key, pstKey->au8ClearKey, HI_UNF_KLAD_MAX_KEY_LEN);

    ret = ioctl(g_klad_fd, CMD_KLAD_GEN_ENC_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_GEN_ENC_KEY error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    memcpy(pstKey->au8EncKey, &key.key.enc_key, HI_UNF_KLAD_MAX_KEY_LEN);

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SendSTBRootkeyToCipher(HI_HANDLE hKlad)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_INIT_CHECK;

    ret = ioctl(g_klad_fd, CMD_KLAD_STBROOTKEY2CIPHER, &hKlad);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_STBROOTKEY2CIPHER error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

#if 0 // 2017/02/13 - 14:24:57,
HI_S32 HI_UNF_KLAD_WIDEVINEGetDecFlag(HI_HANDLE hKlad, HI_U32 *pu32Flag)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_WIDEVINE_DEC_FLAG_S ctl_handle;

    KLAD_FUNC_ENTER();

    KLAD_INIT_CHECK;
    KLAD_CHECKPOINTER(pu32Flag);

    memset(&ctl_handle, 0x00, sizeof(KLAD_CTL_WIDEVINE_DEC_FLAG_S));
    ctl_handle.handle = hKlad;

    ret = ioctl(g_klad_fd, CMD_KLAD_WIDEVINE_GET_DEC_FLAG, &ctl_handle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Klad ioctl CMD_KLAD_WIDEVINE_GET_DEC_FLAG error. [%#x][%#x] [%d:%s]\n", g_klad_fd, ret, errno, strerror(errno));
        KLAD_FUNC_EXIT();
        return ret;
    }

    *pu32Flag = ctl_handle.flag;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
