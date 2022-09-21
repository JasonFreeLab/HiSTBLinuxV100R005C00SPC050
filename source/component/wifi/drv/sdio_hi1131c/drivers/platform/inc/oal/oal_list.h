/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_list.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月3日
  最近修改   :
  功能描述   : oal_queue.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月3日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LIST_H__
#define __OAL_LIST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_mm.h"
#include "oal_util.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 单向链表头初始化 */
#define OAL_LIST_HEAD_INIT(_list_name) {(oal_list_entry_stru *)&(_list_name), (oal_list_entry_stru*)&(_list_name)}

/* 单向创建链表头 */
/*lint -e773*/
#define OAL_LIST_CREATE_HEAD(_list_name) \
    oal_list_head_stru _list_name = OAL_LIST_HEAD_INIT(_list_name)

/* 单向遍历链表使用时请在其后加大括号 */
#define OAL_LIST_SEARCH_FOR_EACH(_list_pos, _list_head) \
    for (_list_pos = (_list_head)->pst_next; _list_pos != (oal_list_entry_stru *)(_list_head); _list_pos = _list_pos->pst_next)

/* 获得单向链表中指定的节点 第一个参数为模板链表结构体指针； 第二个参数为链表中数据结构体类型名； 第三个参数为数据结构体中模板链表结构体的名字 */
#define OAL_LIST_GET_ENTRY(_list_ptr, _data_type, _data_member_list_name) \
/*lint -e(413)*/        ((_data_type *)((oal_int8 *)(_list_ptr)-(oal_uint)(&((_data_type *)0)->_data_member_list_name)))

/* 双向链表头初始化 */
#define OAL_DLIST_HEAD_INIT(_dlist_name) {&(_dlist_name), &(_dlist_name)}

/* 创建双向链表头 */
/*lint -e773*/
#define OAL_DLIST_CREATE_HEAD(_dlist_name) \
    oal_dlist_head_stru _dlist_name = OAL_DLIST_HEAD_INIT(_dlist_name)

/* 遍历双向链表使用时请在其后加大括号 */
#define OAL_DLIST_SEARCH_FOR_EACH(_dlist_pos, _dilst_head) \
    for (_dlist_pos = (_dilst_head)->pst_next; _dlist_pos != (_dilst_head); _dlist_pos = _dlist_pos->pst_next)

/* 遍列双向链表，并可安全删除某个节点 */
#define OAL_DLIST_SEARCH_FOR_EACH_SAFE(_dlist_pos, n, _dilst_head) \
    for (_dlist_pos = (_dilst_head)->pst_next, n = _dlist_pos->pst_next; _dlist_pos != (_dilst_head); _dlist_pos = n, n = _dlist_pos->pst_next)

/* 获得双向链表中指定的节点 第一个参数为模板链表结构体指针； 第二个参数为链表中数据结构体类型名； 第三个参数为数据结构体中模板链表结构体的名字 */
#define OAL_DLIST_GET_ENTRY(_dlist_ptr, _data_type, _data_member_dlist_name) \
/*lint -e(413)*/        ((_data_type *)((oal_int8 *)(_dlist_ptr)-(oal_uint)(&((_data_type *)0)->_data_member_dlist_name)))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct tag_oal_list_entry_stru
{
    struct tag_oal_list_entry_stru *pst_next;
}oal_list_entry_stru;

typedef struct
{
    struct tag_oal_list_entry_stru *pst_next;
    struct tag_oal_list_entry_stru *pst_prev;
}oal_list_head_stru;

typedef struct tag_oal_dlist_head_stru
{
    struct tag_oal_dlist_head_stru *pst_next;
    struct tag_oal_dlist_head_stru *pst_prev;
}oal_dlist_head_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_list_init_head
 功能描述  : 初始化单向链表头
 输入参数  : pst_list_head: 单向链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_list_init_head(oal_list_head_stru *pst_list_head)
{
    pst_list_head->pst_next = (oal_list_entry_stru *)pst_list_head;
    pst_list_head->pst_prev = (oal_list_entry_stru *)pst_list_head;
}

/*****************************************************************************
 函 数 名  : oal_list_add
 功能描述  : 将链表节点加入到链表的尾部
 输入参数  : pst_new: 新加入节点指针
             pst_head: 链表头
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_list_add(oal_list_entry_stru *pst_new,
                            oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_tail = pst_head->pst_prev;

    pst_tail->pst_next = pst_new;
    pst_new->pst_next  = (oal_list_entry_stru *)pst_head;
    pst_head->pst_prev = pst_new;
}

/*****************************************************************************
 函 数 名  : oal_list_delete_head
 功能描述  : 从链表头删除一个节点，不负责释放，不判断链表是否为空，请注意
 输入参数  : pst_head: 链表头
 输出参数  : 无
 返 回 值  : 被删除的节点
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_list_entry_stru* oal_list_delete_head(oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_node;

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head)
    {
        return OAL_PTR_NULL;
    }

    pst_node           = pst_head->pst_next;
    pst_head->pst_next = pst_node->pst_next;

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head)
    {
        pst_head->pst_prev = pst_head->pst_next;
    }

    pst_node->pst_next = OAL_PTR_NULL;

    return pst_node;
}


/*****************************************************************************
 函 数 名  : oal_list_jion
 功能描述  : 将参数2的单向链表合入参数1的单向链表中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_list_jion(oal_list_head_stru *pst_head1, oal_list_head_stru *pst_head2)
{
    oal_list_entry_stru *pst_list1_tail;
    oal_list_entry_stru *pst_list2_tail;

    pst_list1_tail              = pst_head1->pst_prev;
    pst_list2_tail              = pst_head2->pst_prev;
    pst_list1_tail->pst_next    = pst_head2->pst_next;
    pst_head1->pst_prev         = pst_head2->pst_prev;
    pst_list2_tail->pst_next    = (oal_list_entry_stru *)pst_head1;

}

/*****************************************************************************
 函 数 名  : oal_dlist_is_empty
 功能描述  : 判断一个链表是否为空
 输入参数  : pst_head: 链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_list_is_empty(oal_list_head_stru *pst_head)
{
    return pst_head->pst_next == (oal_list_entry_stru *)pst_head;
}



/*****************************************************************************
 函 数 名  : oal_dlist_init_head
 功能描述  : 链表初始化函数
 输入参数  : pst_list: 链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_init_head(oal_dlist_head_stru *pst_list)
{
    pst_list->pst_next = pst_list;
    pst_list->pst_prev = pst_list;
}

/*****************************************************************************
 函 数 名  : oal_dlist_add
 功能描述  : 链表节点加入操作
 输入参数  : pst_new: 新加入节点指针
             pst_prev: 加入位置的前一个节点指针
             pst_next: 加入位置的下一个节点指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_add(oal_dlist_head_stru *pst_new,
                            oal_dlist_head_stru *pst_prev,
                            oal_dlist_head_stru *pst_next)
{
    pst_next->pst_prev  = pst_new;
    pst_new->pst_next   = pst_next;
    pst_new->pst_prev   = pst_prev;
    pst_prev->pst_next  = pst_new;
}

/*****************************************************************************
 函 数 名  : oal_dlist_delete
 功能描述  : 从链表的指定位置删除一个节点提炼
 输入参数  : pst_prev: 删除位置的前一个节点指针
             pst_next: 删除位置的下一个节点指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_delete(oal_dlist_head_stru *pst_prev, oal_dlist_head_stru *pst_next)
{
    pst_next->pst_prev = pst_prev;
    pst_prev->pst_next = pst_next;
}

/*****************************************************************************
 函 数 名  : oal_dlist_is_empty
 功能描述  : 判断一个链表是否为空
 输入参数  : pst_head: 链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_dlist_is_empty(oal_dlist_head_stru *pst_head)
{
    if (OAL_PTR_NULL == pst_head->pst_next || OAL_PTR_NULL == pst_head->pst_prev)
    {
        return OAL_TRUE;
    }

    return pst_head->pst_next == pst_head;
}

/*****************************************************************************
 函 数 名  : oal_dlist_add_head
 功能描述  : 往链表头部插入节点
 输入参数  : pst_new: 要插入的新节点
             pst_head: 链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_add_head(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head, pst_head->pst_next);
}

/*****************************************************************************
 函 数 名  : oal_dlist_add_tail
 功能描述  : 向链表尾部插入节点
 输入参数  : pst_new: 要插入的新节点
             pst_head: 链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_add_tail(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head->pst_prev, pst_head);
}

/*****************************************************************************
 函 数 名  : oal_dlist_delete_entry
 功能描述  : 删除链表中的指定节点,不负责释放，不判断链表是否为空，请注意
 输入参数  : pst_entry: 需要删除的节点
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_delete_entry(oal_dlist_head_stru *pst_entry)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_entry->pst_next) || (OAL_PTR_NULL == pst_entry->pst_prev)))
    {
        return;
    }

    oal_dlist_delete(pst_entry->pst_prev, pst_entry->pst_next);
    pst_entry->pst_next = OAL_PTR_NULL;
    pst_entry->pst_prev = OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : oal_dlist_delete_head
 功能描述  : 从双向链表头部删除一个节点,不判断链表是否为空，不负责释放内存 请注意
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_dlist_head_stru* oal_dlist_delete_head(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node;

    pst_node = pst_head->pst_next;

    OAL_BUG_ON(pst_node==pst_head);
    OAL_BUG_ON(OAL_PTR_NULL == pst_node);

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

/*****************************************************************************
 函 数 名  : oal_dlist_delete_tail
 功能描述  : 从双向链表头部删除一个节点,不判断链表是否为空，不负责释放内存 请注意
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_dlist_head_stru* oal_dlist_delete_tail(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node;

    pst_node = pst_head->pst_prev;

    OAL_BUG_ON(pst_node==pst_head);
    OAL_BUG_ON(OAL_PTR_NULL == pst_node);

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

/*****************************************************************************
 函 数 名  : oal_dlist_join_tail
 功能描述  : 将链表2 加入链表1的尾部
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_join_tail(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_dlist1_tail;
    oal_dlist_head_stru *pst_dlist2_tail;
    oal_dlist_head_stru *pst_dlist2_first;


    pst_dlist1_tail              = pst_head1->pst_prev;
    pst_dlist2_tail              = pst_head2->pst_prev;
    pst_dlist2_first             = pst_head2->pst_next;
    pst_dlist1_tail->pst_next    = pst_dlist2_first;
    pst_dlist2_first->pst_prev   = pst_dlist1_tail;
    pst_head1->pst_prev          = pst_dlist2_tail;
    pst_dlist2_tail->pst_next    = pst_head1;
}

/*****************************************************************************
 函 数 名  : oal_dlist_jion_head
 功能描述  : 将链表2 加入链表1的头部 也可用于将新链表 加入链表的指定节点后
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_join_head(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_head2_first;
    oal_dlist_head_stru *pst_head2_tail;
    oal_dlist_head_stru *pst_head1_first;

    if (oal_dlist_is_empty(pst_head2))
    {
        return;
    }

    pst_head2_first     = pst_head2->pst_next;
    pst_head2_tail      = pst_head2->pst_prev;
    pst_head1_first     = pst_head1->pst_next;

    pst_head1->pst_next         = pst_head2_first;
    pst_head2_first->pst_prev   = pst_head1;
    pst_head2_tail->pst_next    = pst_head1_first;
    pst_head1_first->pst_prev   = pst_head2_tail;


}


/*****************************************************************************
 函 数 名  : oal_dlist_remove_head
 功能描述  : 将链表2中从第一个元素到pst_last_dscr_entry元素摘出， 加入空链表1的头部
 输入参数  :  pst_head1 :链表头1, 空链表
              pst_head2 :链表头2
              pst_last_entry : 链表2中的元素

              默认入参都非NULL
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_dlist_remove_head(oal_dlist_head_stru *pst_head1,
                                                              oal_dlist_head_stru *pst_head2,
                                                              oal_dlist_head_stru *pst_last_entry)
{
    /*对pst_head1赋值*/
    pst_head1->pst_next = pst_head2->pst_next;
    pst_head1->pst_prev = pst_last_entry;

    pst_head2->pst_next = pst_last_entry->pst_next;
    /*pst_last_entry为pst_head2中最后一个成员*/
    if (pst_last_entry->pst_next == pst_head2)
    {
       pst_head2->pst_prev = pst_head2;
    }
    else /*pst_last_entry非pst_head2中最后一个成员*/
    {
       ((oal_dlist_head_stru*)(pst_last_entry->pst_next))->pst_prev = pst_head2;
    }

    pst_last_entry->pst_next = pst_head1;
	/*pst_last_entry为pst_head2中第一个成员*/
    if (pst_last_entry->pst_prev == pst_head2)
    {
       pst_last_entry->pst_prev = pst_head1;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_list.h */
