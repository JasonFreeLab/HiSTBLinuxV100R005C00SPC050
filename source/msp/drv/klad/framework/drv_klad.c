/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <asm/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include "hi_drv_reg.h"
#include "hi_drv_mem.h"
#include "hi_drv_module.h"
#include "drv_klad.h"
#include "hi_drv_descrambler.h"
#include "drv_demux_ext.h"
#include "drv_cipher_ext.h"
#include "drv_plcipher_ext.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

LIST_HEAD(ca_list);
LIST_HEAD(klad_session_list);

struct mutex g_klad_mutex;

HI_S32 DRV_KLAD_Init(HI_VOID)
{
    KLAD_FUNC_ENTER();

    mutex_init(&g_klad_mutex);
    INIT_LIST_HEAD(&ca_list);
    INIT_LIST_HEAD(&klad_session_list);

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Exit(HI_VOID)
{
    KLAD_FUNC_ENTER();

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_SESSION_Create(HI_HANDLE* create_handle)
{
    HI_BOOL found = HI_FALSE;
    DRV_KLAD_SESSION *session = HI_NULL;
    DRV_KLAD_SESSION *p = HI_NULL;
    HI_U32 i = 0, j = 0;
    HI_HANDLE create;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(create_handle);


    for (i = 0; i < HI_KLAD_MAX_SESSION; i++)
    {
        create = HI_KLAD_MAKEHANDLE(HI_ID_CA, i);

        list_for_each_entry(p, &klad_session_list, list)
        {
            if (p && (p->handle == create))
            {
                found = HI_TRUE;
                break;
            }
        }

        if (found == HI_FALSE)
        {
            session = (DRV_KLAD_SESSION *) HI_KMALLOC(HI_ID_CA, sizeof (DRV_KLAD_SESSION), GFP_KERNEL);
            if (HI_NULL == session)
            {
                HI_ERR_KLAD("malloc cmd buffer failed\n");
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_NO_MEMORY;
            }
            memset(session, 0x0, sizeof (DRV_KLAD_SESSION));
            session->handle = create;
            session->target = HI_INVALID_HANDLE;
            session->attr_flag = HI_FALSE;

            for (j = 0; j < HI_UNF_KLAD_LEVEL_BUTT; j++)
            {
                session->sessiong_key_flag[j] = HI_FALSE;
            }

            session->content_key_flag = HI_FALSE;
            session->owner= task_tgid_nr(current);
            mutex_init(&session->lock);
            list_add(&session->list, &klad_session_list);
            *create_handle = session->handle;

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }

        found = HI_FALSE;
    }

    *create_handle = HI_INVALID_HANDLE;


    HI_ERR_KLAD("Can not create more session.\n");
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NO_RESOURCE;
}

static HI_S32 DRV_KLAD_SESSION_Destory(HI_HANDLE handle)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            list_del(&p->list);
            HI_KFREE(HI_ID_CA, p);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetAttr(HI_HANDLE handle, DRV_KLAD_ATTR_S* attr)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(attr);

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

            memcpy(&p->attr, attr, sizeof(DRV_KLAD_ATTR_S));
            p->attr_flag = HI_TRUE;

            mutex_unlock(&p->lock);

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
            }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);

    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_GetAttr(HI_HANDLE handle, DRV_KLAD_ATTR_S* attr)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(attr);

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            if (p->attr_flag == HI_FALSE)
            {
                HI_ERR_KLAD("Not set any attr info to handle=0x%x\n", handle);
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_NOT_SET_ATTR;
            }

            mutex_lock(&p->lock);
            memcpy(attr, &p->attr, sizeof(DRV_KLAD_ATTR_S));
            mutex_unlock(&p->lock);

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);

    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_Attach(HI_HANDLE handle, HI_HANDLE target)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

            if (p->target == HI_INVALID_HANDLE)
            {
                p->target = target;
            }
            else
            {

                mutex_unlock(&p->lock);
                HI_ERR_KLAD("Handle %x has been attach %x\n", handle, p->target);
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_ALREADY_SET_ATTR;
            }

            mutex_unlock(&p->lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_Detach(HI_HANDLE handle, HI_HANDLE target)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

            if (p->target == HI_INVALID_HANDLE)
            {
                mutex_unlock(&p->lock);
                HI_ERR_KLAD("Handle %x has not attached any engine.\n", handle);
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_NOT_SET_ATTR;
            }
            else if (p->target != target)
            {
                mutex_unlock(&p->lock);
                HI_ERR_KLAD("Handle %x has been attached %x but %x.\n", handle, p->target, target);
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_ALREADY_SET_ATTR;
            }
            else
            {
                p->target = HI_INVALID_HANDLE;
            }

            mutex_unlock(&p->lock);

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_KLAD;
}

static HI_S32 DRV_KLAD_SESSION_SetSessionKey(HI_HANDLE handle, DRV_KLAD_SESSION_KEY_S* session_key)
{
    DRV_KLAD_SESSION *p = HI_NULL;
    HI_U32 id = 0;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(session_key);

    id = session_key->level;

    if ( id < HI_UNF_KLAD_LEVEL1 ||  id >= HI_UNF_KLAD_LEVEL_BUTT)
    {
        HI_ERR_KLAD("set session key id check failed[%d]\n", id);

        KLAD_FUNC_EXIT();
        return HI_ERR_KLAD_INVALID_PARA;
    }

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

                memcpy(&p->session_key[id], session_key, sizeof(DRV_KLAD_SESSION_KEY_S));
                p->sessiong_key_flag[id] = HI_TRUE;
                mutex_unlock(&p->lock);

                KLAD_FUNC_EXIT();
                return HI_SUCCESS;
            }

            }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetContentKey(HI_HANDLE handle, DRV_KLAD_CONTENT_KEY_S* content_key)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(content_key);

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

                memcpy(&p->content_key, content_key, sizeof(DRV_KLAD_CONTENT_KEY_S));
                p->content_key_flag = HI_TRUE;
                mutex_unlock(&p->lock);

                KLAD_FUNC_EXIT();
                return HI_SUCCESS;
        }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetContentIV(HI_HANDLE handle, DRV_KLAD_CONTENT_IV_S* content_iv)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(content_iv);

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);

            memcpy(&p->content_iv, content_iv, sizeof(DRV_KLAD_CONTENT_IV_S));
            p->content_iv_flag = HI_TRUE;
            mutex_unlock(&p->lock);

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}



static HI_S32 DRV_KLAD_SESSION_GetDBG(HI_HANDLE handle, DRV_KLAD_DBG_S* dbg)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    DRV_KLAD_CHECK_NULL_PTR(dbg);

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            mutex_lock(&p->lock);
            memcpy(dbg, &p->dbg, sizeof(DRV_KLAD_DBG_S));
            mutex_unlock(&p->lock);

            return HI_SUCCESS;
        }
    }
    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_GetParaNode(HI_HANDLE handle, DRV_KLAD_SESSION **session)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->handle == handle)
        {
            *session = p;
            return HI_SUCCESS;
        }
    }

    HI_ERR_KLAD("can not find session handle, handle=0x%x\n", handle);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

HI_S32 DRV_KLAD_Create(HI_VOID* arg)
{
    HI_HANDLE create_handle = 0;
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_HANDLE_S* ctl_handle = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);
    ctl_handle = (KLAD_CTL_HANDLE_S*)arg;

    ret = DRV_KLAD_SESSION_Create(&create_handle);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_Create failed. [%#x]\n", ret);
    }

    ctl_handle->create_handle = create_handle;
    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Destory(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    ret = DRV_KLAD_SESSION_Destory(*(HI_HANDLE *)arg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_Destory failed. [%#x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Release(struct file* filp)
{
    pid_t pid, curr;
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_FUNC_ENTER();
    pid = (pid_t)(unsigned long)(filp->private_data);
    curr = task_tgid_nr(current);

    if (pid != curr)
    {
        HI_ERR_KLAD("Can not release any session, when drv is not open by the current process\n");
        return HI_ERR_KLAD_RELEASE_ERR;
    }

    list_for_each_entry(p, &klad_session_list, list)
    {
        if (p && p->owner == curr)
        {
            list_del(&p->list);
            HI_KFREE(HI_ID_CA, p);
            p = HI_NULL;
        }
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Attach(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S* ctl_target = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_target = (KLAD_CTL_TARGET_S*)arg;
    ret = DRV_KLAD_SESSION_Attach(ctl_target->handle, ctl_target->target);

    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_Attach failed. [%x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Detach(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S* ctl_target = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_target = (KLAD_CTL_TARGET_S*)arg;
    ret = DRV_KLAD_SESSION_Detach(ctl_target->handle, ctl_target->target);

    if (ret != HI_SUCCESS)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_Detach failed. [%#x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_GetAttr(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S* ctl_attr = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_attr = (KLAD_CTL_ATTR_S*)arg;
    ret = DRV_KLAD_SESSION_GetAttr(ctl_attr->handle, &ctl_attr->attr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_GetAttr failed. [%x]\n", ret);
    }

    return ret;
}
HI_S32 DRV_KLAD_SetAttr(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S* ctl_attr = HI_NULL;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_attr = (KLAD_CTL_ATTR_S*)arg;
    ret = DRV_KLAD_SESSION_SetAttr(ctl_attr->handle, &ctl_attr->attr);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_SetAttr failed. [%x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_SetSessionKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_SESSION_KEY_S* ctl_key = HI_NULL;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_key = (KLAD_CTL_SESSION_KEY_S*)(arg);

    ret = DRV_KLAD_SESSION_SetSessionKey(ctl_key->handle, &ctl_key->session_key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_SetSessionKey failed. [%x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_KEY_S* ctl_key = HI_NULL;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_key = (KLAD_CTL_CONTENT_KEY_S*)(arg);

    ret = DRV_KLAD_SESSION_SetContentKey(ctl_key->handle, &ctl_key->content_key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_SetSessionKey failed. [%x]\n", ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

static HI_S32 SetIVToCipher(HI_HANDLE hCipher, DRV_KLAD_CONTENT_IV_S *pstIV)
{
    HI_S32 ret = HI_FAILURE;
    CIPHER_EXPORT_FUNC_S *pCipherFunc = HI_NULL;

    KLAD_FUNC_ENTER();

    ret = HI_DRV_MODULE_GetFunction(HI_ID_CIPHER, (HI_VOID**)&pCipherFunc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Get cipher set iv function error, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    if (pCipherFunc && pCipherFunc->pfnCipherSetIV)
    {
        ret = (pCipherFunc->pfnCipherSetIV)(hCipher, pstIV->iv, pstIV->length);
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Set cipher IV fail, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}
static HI_S32 SetIVToPlcipher(HI_HANDLE hPlcipher, DRV_KLAD_CONTENT_IV_S *pstIV)
{
    HI_S32 ret = HI_FAILURE;
    PLCIPHER_EXPORT_FUNC_S *plcipher_func = HI_NULL;

    KLAD_FUNC_ENTER();

    ret = HI_DRV_MODULE_GetFunction(HI_ID_PLCIPHER, (HI_VOID**)&plcipher_func);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Get Plcipher set iv function error, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    if (plcipher_func && plcipher_func->pfnPlcipherSetIV)
    {
        if (pstIV->odd == HI_TRUE)
        {
            ret = (plcipher_func->pfnPlcipherSetIV)(hPlcipher, HI_UNF_PLCIPHER_KEY_ODD, pstIV->iv, pstIV->length);
        }
        else
        {
            ret = (plcipher_func->pfnPlcipherSetIV)(hPlcipher, HI_UNF_PLCIPHER_KEY_EVEN, pstIV->iv, pstIV->length);
        }
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Set plcipher IV fail, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 SetIVToDemux(HI_HANDLE hDemux, DRV_KLAD_CONTENT_IV_S *pstIV)
{
    HI_S32 ret = HI_FAILURE;
    DMX_KEY_TYPE_E type;
    DEMUX_EXPORT_FUNC_S *pDmxFunc = HI_NULL;

    KLAD_FUNC_ENTER();

    ret = HI_DRV_MODULE_GetFunction(HI_ID_DEMUX, (HI_VOID**)&pDmxFunc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Get demux set iv function error, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    type = (pstIV->odd == 1) ? DMX_KEY_TYPE_ODD : DMX_KEY_TYPE_EVEN;

    if (pDmxFunc && pDmxFunc->pfnDmxSetDescramblerKey)
    {
        ret = (pDmxFunc->pfnDmxSetDescramblerIV)(hDemux, type, pstIV->iv, pstIV->length);
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("Set demux IV fail, ret:%x\n", ret);
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


HI_S32 DRV_KLAD_SetContentIV(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_IV_S* ctl_iv = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_iv = (KLAD_CTL_CONTENT_IV_S*)(arg);

    ret = DRV_KLAD_SESSION_SetContentIV(ctl_iv->handle, &ctl_iv->content_iv);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_SetSessionKey failed. [%x]\n", ret);
    }

    DRV_KLAD_GetSession(ctl_iv->handle, &session);

    target = DRV_KLAD_GetTarget(session);

    if (DRV_KLAD_TARGET_MULTI_CIPHER == target)
    {
        ret = SetIVToCipher(session->target, &ctl_iv->content_iv);
    }
    else if (DRV_KLAD_TARGET_DEMUX == target)
    {
        ret = SetIVToDemux(session->target, &ctl_iv->content_iv);
    }
    else if (DRV_KLAD_TARGET_PAYLOAD_CIPHER == target)
    {
        ret = SetIVToPlcipher(session->target, &ctl_iv->content_iv);
    }
    else
    {
        HI_ERR_KLAD("target error\n");
    }

    KLAD_FUNC_EXIT();
    return ret;
}


HI_S32 DRV_KLAD_GetDBG(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_DBG_S* ctl_dbg = HI_NULL;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ctl_dbg = (KLAD_CTL_DBG_S*)arg;

    ret = DRV_KLAD_SESSION_GetDBG(ctl_dbg->handle, &ctl_dbg->dbg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SESSION_GetCRC failed. [%x]\n", ret);
    }

    return ret;
}

HI_S32 DRV_KLAD_GetSession(HI_HANDLE handle, DRV_KLAD_SESSION **session)
{
    DRV_KLAD_CHECK_NULL_PTR(session);

    return DRV_KLAD_SESSION_GetParaNode(handle, session);
}

DRV_KLAD_TARGET_E DRV_KLAD_GetTarget(DRV_KLAD_SESSION *session)
{
    DRV_KLAD_CHECK_NULL_PTR(session);

    if (HI_ID_DEMUX == ((session->target >> 24) & 0xff))
    {
        return DRV_KLAD_TARGET_DEMUX;
    }
    else if (HI_ID_PLCIPHER == ((session->target >> 16) & 0xff))
    {
        return DRV_KLAD_TARGET_PAYLOAD_CIPHER;
    }
    else if (HI_ID_CIPHER == ((session->target >> 16) & 0xff))
    {
        return DRV_KLAD_TARGET_MULTI_CIPHER;
    }
    else
    {
        return DRV_KLAD_TARGET_BUTT;
    }
}

HI_S32 DRV_KLAD_Register(KLAD_DRV_ZONE * zone)
{
    DRV_KLAD_CHECK_NULL_PTR(zone);

    list_add(&zone->list, &ca_list);

    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_UnRegister(KLAD_DRV_ZONE* zone)
{
    DRV_KLAD_CHECK_NULL_PTR(zone);

    list_del(&zone->list);

    return HI_SUCCESS;
}

HI_VOID DRV_KLAD_Msleep(HI_U32 time)
{
    msleep(time);
    return;
}

static HI_S32 DRV_KLAD_RunCACallBack(unsigned int cmd, void* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE handle = 0;
    DRV_KLAD_SESSION *pSession = HI_NULL;
    KLAD_DRV_ZONE* p = HI_NULL;
    HI_U32 ca_type = 0;

    KLAD_FUNC_ENTER();

    if (HI_NULL == arg)
    {
        return HI_ERR_KLAD_INVALID_PARA;
    }

    handle = *(HI_U32 *)arg;

    ret = DRV_KLAD_GetSession(handle, &pSession);
    if (HI_SUCCESS != ret)
    {
        return HI_ERR_KLAD_NOT_FIND_SESSION;
    }

    ca_type = HI_KLAD_GET_CATYPE(pSession->attr.klad_type);

    list_for_each_entry(p, &ca_list, list)
    {
        if (p->ca == ca_type)
        {
            ret = p->ioctl(cmd, arg);
            KLAD_FUNC_EXIT();
            return ret;
        }
    }

    return HI_ERR_KLAD_NOT_FIND_KLAD;
}

HI_S32 DRV_KLAD_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, void* arg)
{

    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR((HI_VOID *)arg);

    switch (cmd)

    {
    case CMD_KLAD_CREATE:
        ret = DRV_KLAD_Create(arg);
        break;
    case CMD_KLAD_DESTORY:
        ret = DRV_KLAD_Destory(arg);
        break;
    case CMD_KLAD_ATTACH:
        ret = DRV_KLAD_Attach(arg);
        break;
    case CMD_KLAD_DETACH:
        ret = DRV_KLAD_Detach(arg);
        break;
    case CMD_KLAD_GET_ATTR:
        ret = DRV_KLAD_GetAttr(arg);
        break;
    case CMD_KLAD_SET_ATTR:
        ret = DRV_KLAD_SetAttr(arg);
        break;
    case CMD_KLAD_SET_SESSION_KEY:
        ret = DRV_KLAD_SetSessionKey(arg);
        break;
    default:
        ret = DRV_KLAD_RunCACallBack(cmd, arg);
        break;
    }

    KLAD_FUNC_EXIT();
    return ret;
}


static HI_VOID print_key(HI_U8 *key, HI_U8 length)
{
    HI_S32 i = 0;

    for (i = 0; i < length; i++)
    {
        HI_INFO_KLAD("%x\n", key[i]);
    }

    HI_INFO_KLAD("\n");
    return;
}

HI_VOID DRV_KLAD_PrintSession(DRV_KLAD_SESSION *session)
{
    HI_S32 index = 0;

    HI_INFO_KLAD("====================================================\n");
    HI_INFO_KLAD("handle:              %x\n", session->handle);
    HI_INFO_KLAD("attr.alg:            %d\n", session->attr.alg);
    HI_INFO_KLAD("attr.engine:         %x\n", session->attr.engine);
    HI_INFO_KLAD("attr_flag:           %d\n", session->attr_flag);
    HI_INFO_KLAD("target               %x\n", session->target);
    HI_INFO_KLAD("----------------------------------------------------\n");

    for (index = 0; index < HI_UNF_KLAD_LEVEL_BUTT; index++)
    {
        HI_INFO_KLAD("session key flag[%d]:[%d]\n", index, session->sessiong_key_flag[index]);
        if (HI_TRUE == session->sessiong_key_flag[index])
        {
            print_key(session->session_key[index].key, 16);
        }
    }

    HI_INFO_KLAD("content_key.odd:    %d\n", session->content_key.odd);
    HI_INFO_KLAD("content_key.key: ");
    print_key(session->content_key.key, 16);

    HI_INFO_KLAD("content iv:\n");
    print_key(session->content_iv.iv, 16);
    HI_INFO_KLAD("\n");
    HI_INFO_KLAD("====================================================\n");
}
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
