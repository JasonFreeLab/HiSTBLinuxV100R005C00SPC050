/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : higo_list.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       :  CNcomment: TDEÁ´±íÊ¹ÓÃCNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                     sdk                         Created file
******************************************************************************/

/*********************************add include here******************************/
#include "hi_gfx_list.h"
#include "hi_type.h"

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

void __list_add(struct list_head *pnew,struct list_head *pprev,struct list_head *pnext)
{
    if ((NULL == pnew) || (NULL == pprev) || (NULL == pnext))
    {
        return;
    }
    pnext->prev = pnew;
    pnew->next  = pnext;
    pnew->prev  = pprev;
    pprev->next = pnew;
}

void list_add(struct list_head *pnew, struct list_head *pHead)
{
    __list_add(pnew, pHead, pHead->next);
}
void list_add_tail(struct list_head *pnew, struct list_head *pHead)
{
    __list_add(pnew, pHead->prev, pHead);
}
void __list_del(struct list_head *pprev, struct list_head *pnext)
{
    if ((NULL == pprev) || (NULL == pnext))
    {
        return;
    }
    pnext->prev = pprev;
    pprev->next = pnext;
}

void list_del(struct list_head *pentry)
{
    if (NULL == pentry)
    {
        return;
    }
    __list_del(pentry->prev, pentry->next);
    pentry->next = (void *) 0;
    pentry->prev = (void *) 0;
}

void list_del_init(struct list_head *pentry)
{
    if (NULL == pentry)
    {
        return;
    }

    __list_del(pentry->prev, pentry->next);

    INIT_LIST_HEAD(pentry);
}

int list_empty(struct list_head *pHead)
{
    if (NULL == pHead)
    {
        return -1;
    }
    return pHead->next == pHead;
}
