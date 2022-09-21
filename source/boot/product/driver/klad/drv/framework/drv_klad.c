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
#include "drv_klad.h"

#include "list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HI_ID_DEMUX  (0x0A)
#define HI_ID_CIPHER (0x4D)
LIST_HEAD(ca_list);
LIST_HEAD(klad_session_list);

struct mutex g_klad_mutex;

HI_VOID mutex_init(struct mutex *lock)
{
    return;
}

HI_VOID mutex_lock(struct mutex *lock)
{
    return;
}

HI_VOID mutex_unlock(struct mutex *lock)
{
    return;
}


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

static HI_S32 DRV_KLAD_SESSION_Create(HI_U32 klad, HI_HANDLE* create_handle)
{
    HI_BOOL found = HI_FALSE;
    DRV_KLAD_SESSION *session = HI_NULL;
    DRV_KLAD_SESSION *p = HI_NULL;
    HI_U32 i = 0, j = 0;
    HI_U32 ca_type = 0, klad_type = 0;
    HI_HANDLE create;

    KLAD_FUNC_ENTER();
    DRV_KLAD_CHECK_NULL_PTR(create_handle);

    ca_type = (HI_U32)((klad >> 8) & 0xff);
    klad_type = klad & 0x1f;

    for (i = 0; i < HI_KLAD_MAX_SESSION; i++)
    {
        create = HI_KLAD_MAKEHANDLE(HI_ID_KLAD, ca_type, klad_type, i);

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
            session = (DRV_KLAD_SESSION *) malloc(sizeof (DRV_KLAD_SESSION));
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
            free(p);
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

    ret = DRV_KLAD_SESSION_Create(ctl_handle->klad, &create_handle);
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

HI_S32 DRV_KLAD_Release(HI_VOID)
{
    DRV_KLAD_SESSION* p = HI_NULL;

    KLAD_FUNC_ENTER();



    list_for_each_entry(p, &klad_session_list, list)
    {
            list_del(&p->list);
        free(p);
            p = HI_NULL;
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
    HI_U32 target = 0;

    DRV_KLAD_CHECK_NULL_PTR(session);
    target = HI_HANDLE_GET_MODID(session->target);

    switch (target)
    {

        case HI_ID_DEMUX:
            return DRV_KLAD_TARGET_DEMUX;

        case HI_ID_CIPHER:
            return DRV_KLAD_TARGET_MULTI_CIPHER;

        default:
            return DRV_KLAD_TARGET_BUTT;
    }

    return DRV_KLAD_TARGET_BUTT;
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

static HI_U32 __get_ca_type(unsigned int cmd, void* arg)
{
    if (CMD_KLAD_CREATE == cmd)
    {
        return (HI_U32)(((*(HI_U32 *)arg) >> 8) & 0xff);
    }
    else
    {
        return HI_KLAD_GET_CATYPE(*(HI_U32 *) arg);
    }
}


HI_S32 DRV_KLAD_Ioctl(unsigned int cmd, void* arg)
{
    KLAD_DRV_ZONE* p = HI_NULL;
    HI_S32 ret = HI_FAILURE;
    HI_U32 ca_type = 0;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR((HI_VOID *)arg);

    ca_type = __get_ca_type(cmd, arg);

    list_for_each_entry(p, &ca_list, list)
    {
        if (p->ca == ca_type)
        {
            ret = p->ioctl(cmd, arg);
            KLAD_FUNC_EXIT();
            return ret;
        }
    }

    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_FIND_KLAD;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
