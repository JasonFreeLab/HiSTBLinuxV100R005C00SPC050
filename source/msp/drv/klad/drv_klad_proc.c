/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_proc.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hal_klad.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_proc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (1 == HI_PROC_SUPPORT)
#define CA_KLAD_BASE_ADDR 0xF8ABA000
#define DRV_KLAD_PROC_SEPARATE         "===============================================\n"
#define DRV_KLAD_PROC_PRINT(fmt...)    PROC_PRINT(p, fmt)

static HI_VOID DEV_KLAD_PROC_CaList(struct seq_file* p, HI_VOID* v, KLAD_DRV_ZONE* zone)
{
    return ;
}


static HI_S32 DEV_KLAD_PROC_DBGNode(struct seq_file* p, DRV_KLAD_SESSION *session)
{
    HI_U32 i = 0, j = 0;

    DRV_KLAD_CHECK_NULL_PTR(session);

    mutex_lock(&session->lock);
    DRV_KLAD_PROC_PRINT(DRV_KLAD_PROC_SEPARATE);
    DRV_KLAD_PROC_PRINT("hHandle = %x pzone = 0x%p\n", session->handle, session);

    DRV_KLAD_PROC_PRINT("\n    bond: %x\n", session->target);

    DRV_KLAD_PROC_PRINT("    attr: Flg[%d] alg[%x]  engine[%x]\n",
                        session->attr_flag, session->attr.alg,  session->attr.engine);

    for (i = 0; i < HI_UNF_KLAD_LEVEL_BUTT; i++)
    {

        DRV_KLAD_PROC_PRINT("\n   session key: Flg[%d]\n", session->sessiong_key_flag[i]);
        DRV_KLAD_PROC_PRINT("    level[%d] au8Key:\n      ", session->session_key[i].level);

        for (j = 0; j < 4; j++)
        {
            DRV_KLAD_PROC_PRINT("[0x%02x][0x%02x][0x%02x][0x%02x]",
                                session->session_key[i].key[j * 4 + 0],
                                session->session_key[i].key[j * 4 + 1],
                                session->session_key[i].key[j * 4 + 2],
                                session->session_key[i].key[j * 4 + 3]);
        }

        DRV_KLAD_PROC_PRINT("\n");

    }

    DRV_KLAD_PROC_PRINT("\n   content key: Flg[%d]\n", session->content_key_flag);
    DRV_KLAD_PROC_PRINT("    bOdd[%s]au8Key:\n      ", session->content_key.odd ? "odd" : "even");

    for (j = 0; j < 4; j++)
    {
        DRV_KLAD_PROC_PRINT("[0x%02x][0x%02x][0x%02x][0x%02x]",
                            session->content_key.key[j * 4 + 0],
                            session->content_key.key[j * 4 + 1],
                            session->content_key.key[j * 4 + 2],
                            session->content_key.key[j * 4 + 3]);
    }

    DRV_KLAD_PROC_PRINT("\n");

    mutex_unlock(&session->lock);
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ADP_PROC_SessionList(struct seq_file* p, HI_VOID* v)
{
    HI_U32 i = 0;
    DRV_KLAD_SESSION *session = HI_NULL;

    DRV_KLAD_PROC_PRINT(DRV_KLAD_PROC_SEPARATE);

    list_for_each_entry(session, &klad_session_list, list)
    {
        if (session)
        {
            DRV_KLAD_PROC_PRINT("\nSESSION LIST ID:%x\n" , i);
            DEV_KLAD_PROC_DBGNode(p, session);
            i++;
        }
    }

    DRV_KLAD_PROC_PRINT(DRV_KLAD_PROC_SEPARATE);
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_ProcWrite(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_ProcRead(struct seq_file* p, HI_VOID* v)
{
    KLAD_DRV_ZONE* zone = HI_NULL;

    DRV_KLAD_PROC_PRINT("CA_LIST\n");
    list_for_each_entry(zone, &ca_list, list)
    {
        DEV_KLAD_PROC_CaList(p, v, zone);
    }

    DRV_KLAD_PROC_PRINT("\n");
    DRV_KLAD_ADP_PROC_SessionList(p, v);

    DRV_KLAD_PROC_PRINT("\n");

    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
