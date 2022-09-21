/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_m2u.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年4月23日
  最近修改   :
  功能描述   : 组播转单播处理函数所在文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月23日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_m2u.h"
#include "hmac_tx_data.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_M2U_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : hmac_m2u_add_member_list
 功能描述  : 将一个组成员加入到相对应的组中去
 输入参数  : pst_grp_list 组播组结构体; pst_list_entry 待更新节点结构体
 输出参数  : ul_ret
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_add_member_list(hmac_m2u_grp_list_entry_stru *pst_grp_list, hmac_m2u_list_update_stru *pst_list_entry)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_uint32 ul_ret = OAL_SUCC;

    pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                               OAL_SIZEOF(hmac_m2u_grp_member_stru),
                                                               OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_grp_member))
    {
        OAM_ERROR_LOG0(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_add_member_list::pst_grp_member null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_dlist_add_tail(&(pst_grp_member->st_member_entry), &(pst_grp_list->st_src_list));
    pst_grp_member->ul_src_ip_addr  = pst_list_entry->ul_src_ip_addr;
    pst_grp_member->pst_hmac_user   = pst_list_entry->pst_hmac_user;
    pst_grp_member->en_mode         = pst_list_entry->en_cmd;
    pst_grp_member->ul_timestamp    = pst_list_entry->ul_timestamp;
    oal_set_mac_addr(pst_grp_member->auc_grp_member_addr, pst_list_entry->auc_grp_member);
    return ul_ret;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_remove_expired_member
 功能描述  : 删除超时的组成员
 输入参数  : pst_grp_list 组播组结构体; pst_hmac_vap vap 结构体; ul_nowtimestamp nowtime变量
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_m2u_remove_expired_member(hmac_m2u_grp_list_entry_stru *pst_grp_list,
                                              hmac_vap_stru  *pst_hmac_vap,
                                              oal_uint32 ul_nowtimestamp)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;
    oal_dlist_head_stru      *pst_grp_member_entry_temp;
    hmac_m2u_stru            *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    oal_uint32                ul_ret = OAL_SUCC;

    if (OAL_PTR_NULL == pst_m2u)
    {
        return OAL_FAIL;
    }

    /* 遍历一个组，每次取出组中成员，超时则删除该成员 */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_member_entry, pst_grp_member_entry_temp, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                           hmac_m2u_grp_member_stru,
                                                                           st_member_entry);
        if (OAL_TIME_GET_RUNTIME((pst_grp_member->ul_timestamp), ul_nowtimestamp) > (pst_m2u->ul_timeout))
        {
            oal_dlist_delete_entry(&(pst_grp_member->st_member_entry));
            OAL_MEM_FREE(pst_grp_member, OAL_TRUE);
        }
    }
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_remove_all_grp_member
 功能描述  : 从一个给定的组播组下，删除某个组播组成员
 输入参数  : pst_grp_list 组播组结构体; puc_grp_member_addr 组播成员IP地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_m2u_remove_all_member_grp(hmac_m2u_grp_list_entry_stru *pst_grp_list,
                                                                oal_uint8 *puc_grp_member_addr)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;
    oal_dlist_head_stru      *pst_grp_member_entry_temp;

    /* 遍历一个组播组删除指定成员 */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_member_entry, pst_grp_member_entry_temp, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                         hmac_m2u_grp_member_stru,
                                                                         st_member_entry);

        if (!oal_compare_mac_addr(puc_grp_member_addr, pst_grp_member->auc_grp_member_addr))
        {
            oal_dlist_delete_entry(&(pst_grp_member->st_member_entry));
            OAL_MEM_FREE(pst_grp_member, OAL_TRUE);
        }
    }
}

/*****************************************************************************
 函 数 名  : hmac_m2u_find_member_src
 功能描述  : 根据成员的mac地址以及组播源地址返回所需的组成员
 输入参数  : pst_grp_list 组播组结构体; puc_grp_member_addr 组播成员IP地址; ul_src_ip_addr 组播源IP地址
 输出参数  : pst_grp_member 组播组成员结构体 OR 空指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hmac_m2u_grp_member_stru *hmac_m2u_find_member_src(hmac_m2u_grp_list_entry_stru *pst_grp_list,
                                                                        oal_uint8 *puc_grp_member_addr,
                                                                        oal_uint32 ul_src_ip_addr)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;

    /* 遍历一个组播组，找到该组中src ip匹配的成员 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_grp_member_entry, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                         hmac_m2u_grp_member_stru,
                                                                         st_member_entry);

        if (!oal_compare_mac_addr(puc_grp_member_addr, pst_grp_member->auc_grp_member_addr)
            && (ul_src_ip_addr == pst_grp_member->ul_src_ip_addr))
        {
            return pst_grp_member;
        }
    }
    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_find_member
 功能描述  : 根据成员的mac地址返回所需的组成员
 输入参数  : pst_grp_list 组播组结构体; puc_grp_member_addr 组播组成员IP地址
 输出参数  : pst_grp_member 组播组成员结构体 OR 空指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hmac_m2u_grp_member_stru *hmac_m2u_find_member(hmac_m2u_grp_list_entry_stru *pst_grp_list,
                                                                   oal_uint8 *puc_grp_member_addr)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;

    /* 遍历一个组播组，找到该组中地址匹配的成员 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_grp_member_entry, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                         hmac_m2u_grp_member_stru,
                                                                         st_member_entry);

        if (!oal_compare_mac_addr(puc_grp_member_addr, pst_grp_member->auc_grp_member_addr))
        {
            return pst_grp_member;
        }
    }

    return OAL_PTR_NULL;
}


/*****************************************************************************
 函 数 名  : hmac_m2u_find_group_list
 功能描述  : 根据组的mac地址返回所需的组
 输入参数  : pst_hmac_vap vap结构体; puc_grp_addr 组播组mac地址指针
 输出参数  : pst_grp_list_member 组播组结构体 OR 空指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hmac_m2u_grp_list_entry_stru *hmac_m2u_find_group_list(hmac_vap_stru  *pst_hmac_vap , oal_uint8 *puc_grp_addr)
{
    hmac_m2u_snoop_list_stru         *pst_snp_list;
    hmac_m2u_grp_list_entry_stru     *pst_grp_list_member;
    oal_dlist_head_stru              *pst_grp_list_entry;
    hmac_m2u_stru                    *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_PTR_NULL == pst_m2u)
    {
        return OAL_PTR_NULL;
    }

    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    /* 遍历组播组链表，找到地址匹配的组播组 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_grp_list_entry, &(pst_snp_list->st_grp_list))
    {
        pst_grp_list_member = (hmac_m2u_grp_list_entry_stru *)OAL_DLIST_GET_ENTRY(pst_grp_list_entry,
                                                                               hmac_m2u_grp_list_entry_stru,
                                                                               st_grp_entry);

        if (!oal_compare_mac_addr(puc_grp_addr, pst_grp_list_member->auc_group_addr))
        {
            return (pst_grp_list_member);
        }
     }

    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_create_grp_list
 功能描述  : 根据组播组的MAC地址创建一个组，如果此组存在则返回该组，否则重新创建
 输入参数  : pst_hmac_vap vap结构体; puc_grp_addr 组播组mac地址指针
 输出参数  : pst_grp_list_member 组播组结构体
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hmac_m2u_grp_list_entry_stru *hmac_m2u_create_grp_list(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_grp_addr)
{
    hmac_m2u_snoop_list_stru         *pst_snp_list;
    hmac_m2u_grp_list_entry_stru     *pst_grp_list_member = OAL_PTR_NULL;
    hmac_m2u_stru                    *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        return pst_grp_list_member;
    }

    pst_snp_list = &(pst_m2u->st_m2u_snooplist);
    pst_grp_list_member = hmac_m2u_find_group_list(pst_hmac_vap, puc_grp_addr);

    if (OAL_PTR_NULL == pst_grp_list_member)
    {
        pst_grp_list_member= (hmac_m2u_grp_list_entry_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                                   OAL_SIZEOF(hmac_m2u_grp_list_entry_stru),
                                                                   OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_grp_list_member))
        {
            OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_create_grp_list::pst_grp_list_member null.}");
            return (pst_grp_list_member);
        }

        oal_dlist_add_tail(&(pst_grp_list_member->st_grp_entry), &(pst_snp_list->st_grp_list));
        oal_set_mac_addr(pst_grp_list_member->auc_group_addr, puc_grp_addr);
        oal_dlist_init_head(&(pst_grp_list_member->st_src_list));
    }
    return (pst_grp_list_member);
}

/*****************************************************************************
 函 数 名  : hmac_m2u_Update_Snoop_List
 功能描述  : 根据接收到的用户信息更新链表
 输入参数  : pst_list_entry  待更新节点结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_update_snoop_list(hmac_m2u_list_update_stru *pst_list_entry)
{
    hmac_m2u_grp_list_entry_stru  *pst_grp_list;
    hmac_m2u_grp_member_stru      *pst_grp_member_list;
    oal_uint32                     ul_ret = OAL_SUCC;

    pst_list_entry->ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    pst_grp_list = hmac_m2u_create_grp_list(pst_list_entry->pst_hmac_vap, pst_list_entry->auc_grp_addr);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_grp_list))
    {
       OAM_WARNING_LOG0(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_update_snoop_list::pst_grp_list null.}");
       return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如果待更新的节点有指定的组播源，如果链表中存在指定该组播源的该节点，则更新该节点的状态，否则重新创建加入链表 */
    if (pst_list_entry->ul_src_ip_addr)
    {
        OAM_INFO_LOG4(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_update_snoop_list::pst_list_entry is assigned src_ip_addr [%x].[%x].[%x].[%x]}\r\n",
                                                    (oal_uint32)((pst_list_entry->ul_src_ip_addr>> 24) & 0xff),
                                                    (oal_uint32)((pst_list_entry->ul_src_ip_addr>> 16) & 0xff),
                                                    (oal_uint32)((pst_list_entry->ul_src_ip_addr>> 8)  & 0xff),
                                                    (oal_uint32)((pst_list_entry->ul_src_ip_addr) & 0xff));
        pst_grp_member_list = hmac_m2u_find_member_src(pst_grp_list, pst_list_entry->auc_grp_member, pst_list_entry->ul_src_ip_addr);
        if (OAL_PTR_NULL != pst_grp_member_list)
        {
            pst_grp_member_list->en_mode      = pst_list_entry->en_cmd;
            pst_grp_member_list->ul_timestamp = pst_list_entry->ul_timestamp;
        }
        else
        {
            ul_ret = hmac_m2u_add_member_list(pst_grp_list, pst_list_entry);
        }
    }
    else
    {
        pst_grp_member_list = hmac_m2u_find_member(pst_grp_list, pst_list_entry->auc_grp_member);
        if (OAL_PTR_NULL != pst_grp_member_list)
        {
            /* 存在该节点，并且该组中的该节点的有指定的组播源，清空组中的所有该节点，如果更新节点的cmd为INC 再add */
            if (pst_grp_member_list->ul_src_ip_addr)
            {
                hmac_m2u_remove_all_member_grp(pst_grp_list, pst_list_entry->auc_grp_member);
                if (HMAC_M2U_IGMP_CMD_ADD_INC_LIST == pst_grp_member_list->en_mode)
                {

                    OAM_INFO_LOG1(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_update_snoop_list::pst_grp_member_list->en_mode is [%d].}", pst_grp_member_list->en_mode);
                    ul_ret = hmac_m2u_add_member_list(pst_grp_list, pst_list_entry);
                }
            }
            /* 原组中的该节点未指定组播源，如果待更新节点的CMD为EXC，则删除原组播组中的该节点 */
            else if (HMAC_M2U_IGMP_CMD_ADD_EXC_LIST == pst_list_entry->en_cmd)
            {

                OAM_INFO_LOG1(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_update_snoop_list::pst_list_entry->en_cmd is [%d].}", pst_list_entry->en_cmd);
                oal_dlist_delete_entry(&(pst_grp_member_list->st_member_entry));
                OAL_MEM_FREE(pst_grp_member_list, OAL_TRUE);
            }
        }
        /* 特定组中不存在该节点，并且更新节点的CMD不为EXC则ADD */
        else
        {
            if (HMAC_M2U_IGMP_CMD_ADD_EXC_LIST != pst_list_entry->en_cmd)
            {

                OAM_INFO_LOG1(pst_list_entry->pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_update_snoop_list::pst_grp_member_list == NULL && pst_list_entry->en_cmd is [%d].}", pst_list_entry->en_cmd);
                ul_ret = hmac_m2u_add_member_list(pst_grp_list, pst_list_entry);
            }
        }
    }
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_show_snoop_deny_table
 功能描述  : 打印黑名单
 输入参数  : pst_hmac_vap vap结构体
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_show_snoop_deny_table(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_stru             *pst_m2u;
    oal_uint8                  uc_idx;
    hmac_m2u_snoop_list_stru  *pst_snp_list;

    pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        return;
    }
    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    if (0 == pst_snp_list->uc_deny_count)
    {
        return;
    }
    for (uc_idx = 0 ; uc_idx < pst_snp_list->uc_deny_count; uc_idx ++)
    {
         /* 打印黑名单的IP地址 */
        OAM_INFO_LOG4(0, OAM_SF_M2U, "{hmac_m2u_show_snoop_deny_table:: %d - deny addr = %x.%x.%x.%x}\r\n",
                                                (oal_uint32)((pst_snp_list->ul_deny_group[uc_idx] >> 24) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_group[uc_idx] >> 16) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_group[uc_idx] >> 8) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_group[uc_idx] & 0xff)));
        /* 打印黑名单的子网掩码 */
        OAM_INFO_LOG4(0, OAM_SF_M2U, "{hmac_m2u_show_snoop_deny_table:: deny mask = %x.%x.%x.%x}\r\n",
                                                (oal_uint32)((pst_snp_list->ul_deny_mask[uc_idx] >> 24) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_mask[uc_idx] >> 16) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_mask[uc_idx] >> 8) & 0xff),
                                                (oal_uint32)((pst_snp_list->ul_deny_mask[uc_idx] & 0xff)));
    }
}

/*****************************************************************************
 函 数 名  : hmac_m2u_snoop_is_denied
 功能描述  : 所加入组播组的IP地址是否在黑名单内
 输入参数  : pst_hmac_vap vap结构体; ul_grpaddr 组播组的IP地址
 输出参数  : OAL_FALSE OR OAL_TRUE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_m2u_snoop_is_denied(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_grpaddr)
{
    oal_uint8                 uc_idx;
    hmac_m2u_snoop_list_stru *pst_snp_list;
    hmac_m2u_stru            *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_PTR_NULL == pst_m2u)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    if (0 == pst_snp_list->uc_deny_count)
    {
        return OAL_FALSE;
    }
    for (uc_idx = 0; uc_idx < pst_snp_list->uc_deny_count; uc_idx++)
    {
        if (ul_grpaddr != pst_snp_list->ul_deny_group[uc_idx])
        {
             continue;
        }
        return OAL_TRUE;
    }
    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_clear_deny_table
 功能描述  : 清空黑名单
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_clear_deny_table(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_snoop_list_stru *pst_snp_list;
    hmac_m2u_stru            *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        return;
    }

    pst_snp_list = &(pst_m2u->st_m2u_snooplist);
    pst_snp_list->uc_deny_count = 3;
    return;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_add__snoop_deny_entry
 功能描述  : 增加黑名单成员
 输入参数  : pst_hmac_vap vap结构体; ul_grpaddr 组播组的IP地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_add_snoop_deny_entry(hmac_vap_stru *pst_hmac_vap, oal_uint32 *ul_grpaddr)
{
    oal_uint8                 uc_idx;
    hmac_m2u_snoop_list_stru *pst_snp_list;
    hmac_m2u_stru            *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        return;
    }

    pst_snp_list = &(pst_m2u->st_m2u_snooplist);
    uc_idx = pst_snp_list->uc_deny_count;

    if (uc_idx > HMAC_M2U_GRPADDR_FILTEROUT_NUM)
    {
        return;
    }
    pst_snp_list->uc_deny_count ++;
    pst_snp_list->ul_deny_group[uc_idx] = *(oal_uint32 *)ul_grpaddr;
    pst_snp_list->ul_deny_mask[uc_idx]  = HMAC_M2U_SUBNET_MASK; /* 255.255.255.0 */

    return;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_print_all_snoop_list
 功能描述  : 输出snoop表所有成员
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月9日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
/*lint -e550*/
oal_void hmac_m2u_print_all_snoop_list(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_snoop_list_stru      *pst_snp_list;
    hmac_m2u_grp_list_entry_stru  *pst_grp_list_member;
    hmac_m2u_grp_member_stru      *pst_grp_member = OAL_PTR_NULL;
    oal_dlist_head_stru           *pst_grp_member_entry;
    oal_dlist_head_stru           *pst_grp_member_entry_temp;
    oal_dlist_head_stru           *pst_grp_list_entry;
    oal_int8                       ac_tmp_buff[100];

    hmac_m2u_stru                 *pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{pst_m2u == null}");
        return;
    }
    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    if ((WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
         (pst_m2u->en_snoop_enable) && (pst_snp_list != OAL_PTR_NULL))
    {
        OAL_DLIST_SEARCH_FOR_EACH(pst_grp_list_entry, &(pst_snp_list->st_grp_list))
        {
            pst_grp_list_member = (hmac_m2u_grp_list_entry_stru *)OAL_DLIST_GET_ENTRY(pst_grp_list_entry,
                                                                               hmac_m2u_grp_list_entry_stru,
                                                                               st_grp_entry);
            /* 打印组播组的mac地址 */
            oal_memset(ac_tmp_buff, 0, 100);
            OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "snoop group addr = [%x]:[%x]:[%x]:[%x]:[%x]:[%x]\n",
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[0]),
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[1]),
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[2]),
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[3]),
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[4]),
                                                        (oal_uint32)(pst_grp_list_member->auc_group_addr[5]));
            oam_print(ac_tmp_buff);
            /* 打印组播组成员的mac地址以及组播源地址 */
            OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_member_entry, pst_grp_member_entry_temp, &(pst_grp_list_member->st_src_list))
            {
                pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                         hmac_m2u_grp_member_stru,
                                                                         st_member_entry);
                /* 打印组播组内成员的src ip地址和 mac地址 */
                oal_memset(ac_tmp_buff, 0, 100);
                OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "member_src_ip_addr = [%d].[%d].[%d].[%d]\n",
                                                        (oal_uint32)((pst_grp_member->ul_src_ip_addr>> 24) & 0xff),
                                                        (oal_uint32)((pst_grp_member->ul_src_ip_addr>> 16) & 0xff),
                                                        (oal_uint32)((pst_grp_member->ul_src_ip_addr>> 8)  & 0xff),
                                                        (oal_uint32)((pst_grp_member->ul_src_ip_addr) & 0xff));
                oam_print(ac_tmp_buff);

                oal_memset(ac_tmp_buff, 0, 100);
                OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "member_mac_addr and mode = [%x]:[%x]:[%x]:[%x]:[%x]:[%x]:%d\n",
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[0]),
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[1]),
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[2]),
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[3]),
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[4]),
                                                        (oal_uint32)(pst_grp_member->auc_grp_member_addr[5]),
                                                         pst_grp_member->en_mode);
                oam_print(ac_tmp_buff);
            }
        }
    }
    else
    {
        OAM_WARNING_LOG2(0, OAM_SF_M2U, "{hmac_m2u_print_all_snoop_list::en_snoop_enable en_vap_mode = [%d].[%d]}\r\n",
                                                    pst_m2u->en_snoop_enable,
                                                    pst_hmac_vap->st_vap_base_info.en_vap_mode);
    }
}
/*lint +e550*/
/*****************************************************************************
 函 数 名  : hmac_m2u_check
 功能描述  : 组播转单播输入检查
 输入参数  : pst_hmac_vap vap结构体;pst_ether_header 以太网头结构体
 输出参数  : OAL_FAIL OR OAL_SUCC
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_check(hmac_vap_stru *pst_hmac_vap, mac_ether_header_stru *pst_ether_header)
{
    oal_uint32       ul_ret  = OAL_SUCC;

    /*lint -e778*/
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) != pst_ether_header->us_ether_type)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_check::not ip protocol:ether_type is [0x%x].}", OAL_HOST2NET_SHORT(pst_ether_header->us_ether_type));
        return OAL_FAIL;
    }
    /*lint +e778*/
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_m2u_igmp_v1v2_update
 功能描述  : IGMP V1 V2 报文更新snoop链表
 输入参数  : pst_hmac_vap vap结构体; st_list_entry 待更新的节点结构体; pst_igmp IGMP报文结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_igmp_v1v2_update(hmac_vap_stru *pst_hmac_vap, hmac_m2u_list_update_stru *pst_list_entry, mac_igmp_header_stru *pst_igmp)
{
    oal_uint32           ul_group_addr = 0;                 /* to hold group address from group record */
    oal_uint8            uc_group_addr[WLAN_MAC_ADDR_LEN]; /* group multicast mac address */
    oal_uint32           ul_ret = OAL_SUCC;

    /* 初始化组播组地址 */
    uc_group_addr[0] = 0x01;
    uc_group_addr[1] = 0x00;
    uc_group_addr[2] = 0x5e;

    ul_group_addr = OAL_HOST2NET_LONG(pst_igmp->ul_group);

    if (hmac_m2u_snoop_is_denied(pst_hmac_vap, ul_group_addr))
    {
        OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v1v2_update::ul_group_addr [%x].[%x].[%x].[%x] is denied}\r\n}",
                                                                            (oal_uint32)((ul_group_addr>> 24) & 0xff),
                                                                            (oal_uint32)((ul_group_addr>> 16) & 0xff),
                                                                            (oal_uint32)((ul_group_addr>> 8)  & 0xff),
                                                                            (oal_uint32)((ul_group_addr) & 0xff));
        return ul_ret;
    }
    if (MAC_IGMPV2_LEAVE_TYPE  != pst_igmp->uc_type)
    {
        pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_INC_LIST;
    }
    else
    {
        pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_EXC_LIST;
    }
    uc_group_addr[3] = (ul_group_addr >> 16) & 0x7f;
    uc_group_addr[4] = (ul_group_addr >>  8) & 0xff;
    uc_group_addr[5] = (ul_group_addr >>  0) & 0xff;

    oal_set_mac_addr(pst_list_entry->auc_grp_addr, uc_group_addr);
    pst_list_entry->ul_src_ip_addr = 0;
    ul_ret = hmac_m2u_update_snoop_list(pst_list_entry);
    return ul_ret;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_igmp_v3_update
 功能描述  : IGMP V3报文更新snoop链表
 输入参数  : pst_hmac_vap vap结构体; st_list_entry 待更新的节点结构体; pst_igmpr3 IGMP v3报文结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_igmp_v3_update(hmac_vap_stru *pst_hmac_vap, hmac_m2u_list_update_stru *pst_list_entry, mac_igmp_v3_report_stru *pst_igmpr3)
{
    oal_uint32                           ul_group_addr = 0;                  /* to hold group address from group record */
    oal_uint8                            uc_group_addr[WLAN_MAC_ADDR_LEN]; /* group multicast mac address */
    oal_uint16                           us_no_grec;                        /* no of group records  */
    oal_uint16                           us_no_srec;                        /* no of source records */
    oal_uint32                          *pul_src_addr;                      /* 组播源的IP地址 */
    mac_igmp_v3_grec_stru               *pst_grec;                          /* igmp group record */
    hmac_m2u_grp_list_entry_stru        *pst_grp_list;
    hmac_m2u_grp_member_stru            *pst_grp_member_list;
    oal_uint32                           ul_ret = OAL_SUCC;

    uc_group_addr[0] = 0x01;
    uc_group_addr[1] = 0x00;
    uc_group_addr[2] = 0x5e;

    us_no_grec   = OAL_HOST2NET_SHORT(pst_igmpr3->us_ngrec);
    pst_grec     = (mac_igmp_v3_grec_stru *)(pst_igmpr3 + 1);

    if (0 == us_no_grec)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::us_no_grec is 0.}");
        return OAL_FAIL;
    }
    while (us_no_grec)
    {
        pst_list_entry->en_cmd = pst_grec->uc_grec_type;
        ul_group_addr          = OAL_HOST2NET_LONG(pst_grec->ul_grec_mca);

        if (hmac_m2u_snoop_is_denied(pst_hmac_vap, ul_group_addr))
        {
            OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::ul_group_addr [%x].[%x].[%x].[%x] is denied}\r\n}",
                                                                                        (oal_uint32)((ul_group_addr>> 24) & 0xff),
                                                                                        (oal_uint32)((ul_group_addr>> 16) & 0xff),
                                                                                        (oal_uint32)((ul_group_addr>> 8)  & 0xff),
                                                                                        (oal_uint32)((ul_group_addr) & 0xff));
            /* move the grec to next group record */
            pst_grec = (mac_igmp_v3_grec_stru *)((oal_uint8 *)pst_grec + IGMPV3_GRP_REC_LEN(pst_grec));
            us_no_grec--;
            continue;
        }
        /* 非IGMPV3六种cmd的异常处理 */
        if (!IS_IGMPV3_MODE(pst_grec->uc_grec_type))
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::uc_grec_type is [%x] not inside the six cmd.}", pst_grec->uc_grec_type);
            /* move the grec to next group record */
            pst_grec = (mac_igmp_v3_grec_stru *)((oal_uint8 *)pst_grec + IGMPV3_GRP_REC_LEN(pst_grec));
            us_no_grec--;
            continue;
        }

        us_no_srec = OAL_HOST2NET_SHORT(pst_grec->us_grec_nsrcs);
        uc_group_addr[3] = (ul_group_addr >> 16) & 0x7f;
        uc_group_addr[4] = (ul_group_addr >>  8) & 0xff;
        uc_group_addr[5] = (ul_group_addr >>  0) & 0xff;
        oal_set_mac_addr(pst_list_entry->auc_grp_addr, uc_group_addr);

        /* IGMP V3 exc的处理 */
        if ( IGMPV3_CHANGE_TO_EXCLUDE == (pst_grec->uc_grec_type)||
            IGMPV3_MODE_IS_EXCLUDE == (pst_grec->uc_grec_type))
        {
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::pst_grec->uc_grec_type is %d.}", pst_grec->uc_grec_type);
            pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_EXC_LIST;
            pst_grp_list = hmac_m2u_find_group_list(pst_hmac_vap, pst_list_entry->auc_grp_addr);

            /* 更新组播组内成员的状态，如果组播组内存在该目标成员，则清空目标成员 */
            if (OAL_PTR_NULL == pst_grp_list)
            {
                OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::pst_grp_list is null.}");
            }
            else
            {
                hmac_m2u_remove_all_member_grp(pst_grp_list, pst_list_entry->auc_grp_member);
            }

            /* 更新组播组内成员的状态，如果组播组内不存在该目标成员，该成员inc所有src ip */
            if (0 == us_no_srec)
            {
                OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::not exist the user us_no_srec is %d.}", us_no_srec);
                pst_list_entry->ul_src_ip_addr = 0;
                pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_INC_LIST;
                ul_ret = hmac_m2u_update_snoop_list(pst_list_entry);
            }
        }

        /* IGMP V3 INC的处理 */
        else if (IGMPV3_CHANGE_TO_INCLUDE == (pst_grec->uc_grec_type) ||
                  IGMPV3_MODE_IS_INCLUDE == (pst_grec->uc_grec_type))
        {
            pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_INC_LIST;
            pst_grp_list = hmac_m2u_find_group_list(pst_hmac_vap, pst_list_entry->auc_grp_addr);

            if (OAL_PTR_NULL == pst_grp_list)
            {
                OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_igmp_v3_update::pst_grp_list is null.}");
            }
            else
            {
                hmac_m2u_remove_all_member_grp(pst_grp_list, pst_list_entry->auc_grp_member);
            }
        }

        else if (IGMPV3_ALLOW_NEW_SOURCES == (pst_grec->uc_grec_type))
        {
            pst_list_entry->en_cmd = HMAC_M2U_IGMP_CMD_ADD_INC_LIST;
        }

        pul_src_addr = (oal_uint32 *)((oal_uint8 *)pst_grec + OAL_SIZEOF(mac_igmp_v3_grec_stru));

        /* 同一组播组内不同src ip的链表更新 */
        while (us_no_srec)
        {
            pst_list_entry->ul_src_ip_addr = *pul_src_addr;
            if (IGMPV3_BLOCK_OLD_SOURCES != (pst_grec->uc_grec_type))
            {
                ul_ret = hmac_m2u_update_snoop_list(pst_list_entry);
            }
            /* block old source时清空该成员 */
            else
            {
                pst_grp_list = hmac_m2u_find_group_list(pst_hmac_vap, pst_list_entry->auc_grp_addr);

                if (OAL_PTR_NULL != pst_grp_list)
                {
                    pst_grp_member_list = hmac_m2u_find_member_src(pst_grp_list,
                                                                   pst_list_entry->auc_grp_member, pst_list_entry->ul_src_ip_addr);
                    if (OAL_PTR_NULL != pst_grp_member_list)
                    {
                        oal_dlist_delete_entry(&pst_grp_member_list->st_member_entry);
                        OAL_MEM_FREE(pst_grp_member_list, OAL_TRUE);
                    }
                }
            }
            pul_src_addr++;
            us_no_srec--;
        }
        /* 取下一个组播组 */
        pst_grec = (mac_igmp_v3_grec_stru *)((oal_uint8 *)pst_grec + IGMPV3_GRP_REC_LEN(pst_grec));
        us_no_grec--;
    }
    return ul_ret;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_snoop_inspecting
 功能描述  : 监听IGMP报文来创建组播组链表
 输入参数  : pst_hmac_vap vap结构体; pst_hmac_user user结构体; pst_buf netbuf结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_snoop_inspecting(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user, oal_netbuf_stru *pst_buf)
{
    mac_ether_header_stru                *pst_ether_header;
    mac_ip_header_stru                   *pst_ip_hdr;
    mac_igmp_header_stru                 *pst_igmp;                             /* igmp header for v1 and v2 */
    mac_igmp_v3_report_stru              *pst_igmpr3;                           /* igmp header for v3 */
    oal_uint8                            *puc_src_addr;                          /* source address which send the report and it is the member */
    hmac_m2u_list_update_stru             st_list_entry;                        /* list entry where all member details will be updated and passed on updating the snoop list */
    oal_uint32                            ul_ret;
    hmac_m2u_stru                        *pst_m2u;
    oal_uint8                             uc_ip_hdr_len;

    pst_m2u = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    if (OAL_FALSE == pst_m2u->en_snoop_enable)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::snoop is [%d] not enable}", pst_m2u->en_snoop_enable);
        return;
    }

    /* 获取以太网头 */
    pst_ether_header  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /* ap模式的接收处理 */
    if ((WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
            (ETHER_IS_IPV4_MULTICAST(pst_ether_header->auc_ether_dhost)) &&
            (!ETHER_IS_BROADCAST(pst_ether_header->auc_ether_dhost)))
    {
        /*lint -e778*/
        if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) != pst_ether_header->us_ether_type)
        {
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::ether type is not IP Protocol.[0x%x]}", OAL_HOST2NET_SHORT(pst_ether_header->us_ether_type));
            return;
        }
        /*lint +e778*/

        /* 偏移一个以太网头，取ip头 */
        pst_ip_hdr = (mac_ip_header_stru *)(pst_ether_header + 1);

        if (IPPROTO_IGMP != pst_ip_hdr->uc_protocol)
        {
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::ip type is not IGMP Protocol[%x].}", pst_ip_hdr->uc_protocol);
            return;
        }
        puc_src_addr  = pst_ether_header->auc_ether_shost;
        oal_set_mac_addr(st_list_entry.auc_grp_member, puc_src_addr);
        st_list_entry.pst_hmac_vap  = pst_hmac_vap;
        st_list_entry.pst_hmac_user = pst_hmac_user;

        /* bit序不同，取不同的ip头长度*/
        if (OAL_BITFIELD_BIG_ENDIAN ==  oal_netbuf_get_bitfield())
        {
            uc_ip_hdr_len = pst_ip_hdr->uc_version_ihl & 0x0F;
        }
        else
        {
            uc_ip_hdr_len = (pst_ip_hdr->uc_version_ihl & 0xF0) >> 4;
        }
        if (MIN_IP_HDR_LEN > uc_ip_hdr_len )
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::ip_hdr_len is [%x].}", uc_ip_hdr_len);
            return;
        }
        /* v1 & v2 igmp */
        pst_igmp = (mac_igmp_header_stru *)(oal_netbuf_data(pst_buf) + OAL_SIZEOF(mac_ether_header_stru) + 4* uc_ip_hdr_len);

        /* v3 igmp */
        pst_igmpr3 = (mac_igmp_v3_report_stru *) pst_igmp;

        /* 如果报文不是IGMP report报文或leave报文,不进行链表更新 */
        if (!IS_IGMP_REPORT_LEAVE_PACKET(pst_igmp->uc_type))
        {
           OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::not igmp report[%x].}", pst_igmp->uc_type);
           return;
        }

        /* IGMP v1 v2 报文的链表更新  */
        if (pst_igmp->uc_type != MAC_IGMPV3_REPORT_TYPE)
        {
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::v1v2 update[%x].}", pst_igmp->uc_type);
            ul_ret = hmac_m2u_igmp_v1v2_update(pst_hmac_vap, &st_list_entry, pst_igmp);
        }

        /* IGMP v3 report 报文的链表更新*/
        else
        {
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::v3 update[%x].}", pst_igmp->uc_type);
            ul_ret = hmac_m2u_igmp_v3_update(pst_hmac_vap, &st_list_entry, pst_igmpr3);
        }
        /* 链表更新失败，则关闭组播转单播功能 */
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::igmp update fail [%d] .}", ul_ret);
            pst_m2u->en_snoop_enable = OAL_FALSE;
        }
    }

    /* STA模式的接收处理 去掉自定义的tunnel协议头 */
    if (OAL_HOST2NET_SHORT(ETHER_TUNNEL_TYPE) == pst_ether_header->us_ether_type &&
        WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_inspecting::STA Mode && Ether Type is ETHER_TUNNEL_TYPE.}");
        oal_netbuf_pull(pst_buf, OAL_SIZEOF(mac_ether_header_stru));
        oal_netbuf_pull(pst_buf, OAL_SIZEOF(mcast_tunnel_hdr_stru));
    }
    return;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_count_member_anysrclist
 功能描述  : 找出一个组播组内,组播源为所有源的所有STA用户
 输入参数  : pst_grp_list 组播组结构体; puc_table 组播组成员所在指针数组; us_timestamp nowtime变量
 输出参数  : uc_count
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint8 hmac_m2u_count_member_anysrclist(hmac_m2u_grp_list_entry_stru *pst_grp_list, oal_uint8 *puc_table,
                                                        oal_uint32 ul_timestamp)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;
    oal_uint8                 uc_count = 0;

    OAL_DLIST_SEARCH_FOR_EACH(pst_grp_member_entry, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                     hmac_m2u_grp_member_stru,
                                                                     st_member_entry);

        if (0 == pst_grp_member->ul_src_ip_addr)
        {
            if (uc_count > MAX_SNOOP_ENTRIES)
            {
                break;
            }
            oal_set_mac_addr(&puc_table[uc_count * WLAN_MAC_ADDR_LEN], pst_grp_member->auc_grp_member_addr);
            pst_grp_member->ul_timestamp = ul_timestamp;
            uc_count++;
        }
    }
    return (uc_count);
}

/*****************************************************************************
 函 数 名  : hmac_m2u_count_member_src_list
 功能描述  : 找出一个组播组内,组播源为指定源的所有STA用户
 输入参数  : pst_grp_list 组播组结构体; ul_src_ip_addr 组播源IP地址;
             puc_table 组播组成员的MAC地址所在指针数组
             us_timestamp nowtime
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_uint8 hmac_m2u_count_member_src_list(hmac_m2u_grp_list_entry_stru *pst_grp_list,
                                                    oal_uint32 ul_src_ip_addr, oal_uint8 *puc_table,
                                                    oal_uint32 ul_timestamp, oal_uint8 uc_count)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;
    //oal_uint8                 uc_count = 0;

    if (uc_count > MAX_SNOOP_ENTRIES)
    {
        return uc_count;
    }

    OAL_DLIST_SEARCH_FOR_EACH(pst_grp_member_entry, &(pst_grp_list->st_src_list))
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                         hmac_m2u_grp_member_stru,
                                                                         st_member_entry);

        /* 组播源地址符合，模式是inc，加入到输出的table中 */
        if (ul_src_ip_addr == pst_grp_member->ul_src_ip_addr)
        {
            if (HMAC_M2U_IGMP_CMD_ADD_INC_LIST == pst_grp_member->en_mode)
            {
                if (uc_count > MAX_SNOOP_ENTRIES)
                {
                    break;
                }
                oal_set_mac_addr(&puc_table[uc_count * WLAN_MAC_ADDR_LEN], pst_grp_member->auc_grp_member_addr);
                pst_grp_member->ul_timestamp = ul_timestamp;
                uc_count++;
            }
        }
        else
        {
            /* 组播源未匹配，但模式为exc的情况也加入到输出table中 */
            if (HMAC_M2U_IGMP_CMD_ADD_EXC_LIST == pst_grp_member->en_mode)
            {
                if (uc_count > MAX_SNOOP_ENTRIES)
                {
                    break;
                }
                oal_set_mac_addr(&puc_table[uc_count * WLAN_MAC_ADDR_LEN], pst_grp_member->auc_grp_member_addr);
                pst_grp_member->ul_timestamp = ul_timestamp;
                uc_count++;
            }
        }
     }
    return (uc_count);
}
/*****************************************************************************
 函 数 名  : hmac_m2u_get_snooplist_member
 功能描述  : 找到一个group内需要该组播源的所有STA用户
 输入参数  : pst_hmac_vap vap结构体;
             puc_grp_addr  组播组IP地址;
             ul_src_ip_addr 组播源IP地址;
             puc_table 组播组成员的MAC地址所在指针数组
 输出参数  : uc_count
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_uint8 hmac_m2u_get_snooplist_member(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_grp_addr,
                                oal_uint32 ul_src_ip_addr, oal_uint8 *puc_table)
{
    hmac_m2u_grp_list_entry_stru     *pst_grp_list_member;
    oal_uint8                         uc_count = 0;
    oal_uint32                        ul_nowtime;

    ul_nowtime = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    pst_grp_list_member = hmac_m2u_find_group_list(pst_hmac_vap, puc_grp_addr);

    if (OAL_PTR_NULL != pst_grp_list_member)
    {
        uc_count  = hmac_m2u_count_member_anysrclist(pst_grp_list_member, &puc_table[0], ul_nowtime);
        uc_count  = hmac_m2u_count_member_src_list(pst_grp_list_member, ul_src_ip_addr, &puc_table[0], ul_nowtime, uc_count);
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_get_snooplist_member::uc_count is [%d]}", uc_count);
    }

    return (uc_count);
}
/*****************************************************************************
 函 数 名  : hmac_m2u_remove_node_grp
 功能描述  : 删除一个组播组下属于特定STA的节点，如果该入参STA为空，则清空该组播组
 输入参数  : pst_grp_list 组播组结构体; pst_hmac_user user结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_m2u_remove_node_grp(hmac_m2u_grp_list_entry_stru *pst_grp_list, hmac_user_stru *pst_hmac_user)
{
    hmac_m2u_grp_member_stru *pst_grp_member;
    oal_dlist_head_stru      *pst_grp_member_entry;
    oal_dlist_head_stru      *pst_grp_member_entry_temp;

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_member_entry, pst_grp_member_entry_temp, &pst_grp_list->st_src_list)
    {
        pst_grp_member = (hmac_m2u_grp_member_stru *)OAL_DLIST_GET_ENTRY(pst_grp_member_entry,
                                                                             hmac_m2u_grp_member_stru,
                                                                                      st_member_entry);

        if ((pst_hmac_user == pst_grp_member->pst_hmac_user) || (OAL_PTR_NULL == pst_hmac_user))
        {
            oal_dlist_delete_entry(&(pst_grp_member->st_member_entry));
            OAL_MEM_FREE(pst_grp_member, OAL_TRUE);
        }
    }
}
/*****************************************************************************
 函 数 名  : hmac_m2u_clean_snp_list
 功能描述  : 清空组播组链表以及组播组内的成员
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_m2u_clean_snp_list(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_stru                 *pst_m2u;
    hmac_m2u_snoop_list_stru      *pst_snp_list;
    hmac_m2u_grp_list_entry_stru  *pst_grp_list;
    oal_dlist_head_stru           *pst_grp_list_entry;
    oal_dlist_head_stru           *pst_grp_list_entry_temp;

    /* 获取snoop链表头 */
    pst_m2u      = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_list_entry, pst_grp_list_entry_temp, &(pst_snp_list->st_grp_list))
    {
        pst_grp_list = (hmac_m2u_grp_list_entry_stru *)OAL_DLIST_GET_ENTRY(pst_grp_list_entry,
                                                                            hmac_m2u_grp_list_entry_stru,
                                                                                     st_grp_entry);
        hmac_m2u_remove_node_grp(pst_grp_list, OAL_PTR_NULL);
        oal_dlist_delete_entry(&(pst_grp_list->st_grp_entry));
        OAL_MEM_FREE(pst_grp_list, OAL_TRUE);
    }
}
/*****************************************************************************
 函 数 名  : hmac_m2u_cleanup_snoopwds_node
 功能描述  : 清空各个组播组内的某个STA用户
 输入参数  : pst_hmac_user user结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_cleanup_snoopwds_node(hmac_user_stru *pst_hmac_user)
{
    hmac_vap_stru                 *pst_hmac_vap ;
    hmac_m2u_stru                 *pst_m2u;
    hmac_m2u_snoop_list_stru      *pst_snp_list;
    hmac_m2u_grp_list_entry_stru  *pst_grp_list;
    oal_dlist_head_stru           *pst_grp_list_entry;
    oal_dlist_head_stru           *pst_grp_list_entry_temp;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_m2u_cleanup_snoopwds_node::pst_hmac_vap[id=%d] null!!}",
                    pst_hmac_user->st_user_base_info.uc_vap_id);
        return;
    }

    pst_m2u  = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    if(WLAN_VAP_MODE_BSS_AP == (pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
        OAL_PTR_NULL != pst_snp_list && (pst_m2u->en_snoop_enable))
    {
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_list_entry, pst_grp_list_entry_temp, &(pst_snp_list->st_grp_list))
        {
            pst_grp_list = (hmac_m2u_grp_list_entry_stru *)OAL_DLIST_GET_ENTRY(pst_grp_list_entry,
                                                                            hmac_m2u_grp_list_entry_stru,
                                                                                     st_grp_entry);
            hmac_m2u_remove_node_grp(pst_grp_list, pst_hmac_user);

            if (OAL_TRUE == (oal_dlist_is_empty(&(pst_grp_list->st_src_list))))
            {
                oal_dlist_delete_entry(&(pst_grp_list->st_grp_entry));
                OAL_MEM_FREE(pst_grp_list, OAL_TRUE);
            }
        }
    }
}
/*****************************************************************************
 函 数 名  : hmac_m2u_tx_event
 功能描述  : 组播转单播，单播封装802.11头以及发送事件
 输入参数  : pst_vap vap结构体; pst_user user结构体; pst_buf netbuf结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_tx_event( hmac_vap_stru *pst_vap, hmac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    frw_event_stru          *pst_event;        /* 事件结构体 */
    frw_event_mem_stru      *pst_event_mem;
    dmac_tx_event_stru      *pst_dtx_stru;
    oal_uint32               ul_ret = OAL_SUCC;

    /* 封装802.11头 */
     ul_ret = hmac_tx_encap(pst_vap, pst_user, pst_buf);
     if (OAL_UNLIKELY((OAL_SUCC != ul_ret)))
     {
         OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                          "{hmac_tx_lan_mpdu_process_ap::hmac_tx_encap failed[%d].}", ul_ret);
         OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
         return ul_ret;
     }

     /* 抛事件，传给DMAC */
     pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
     if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
     {
         OAM_ERROR_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::pst_event_mem null.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
         pst_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets++;
#endif
         return OAL_ERR_CODE_ALLOC_MEM_FAIL;
     }

     pst_event = (frw_event_stru *)pst_event_mem->puc_data;


     /* 填写事件头 */
     FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                      FRW_EVENT_TYPE_HOST_DRX,
                      DMAC_TX_HOST_DRX,
                      OAL_SIZEOF(dmac_tx_event_stru),
                      FRW_EVENT_PIPELINE_STAGE_1,
                      pst_vap->st_vap_base_info.uc_chip_id,
                      pst_vap->st_vap_base_info.uc_device_id,
                      pst_vap->st_vap_base_info.uc_vap_id);

     pst_dtx_stru             = (dmac_tx_event_stru *)pst_event->auc_event_data;
     pst_dtx_stru->pst_netbuf = pst_buf;


     /* 调度事件 */
     ul_ret = frw_event_dispatch_event(pst_event_mem);
     if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
     {
         OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::frw_event_dispatch_event failed[%d].}", ul_ret);
         OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_abnormal_msdu_dropped, 1);
     }

     /* 释放事件 */
     FRW_EVENT_FREE(pst_event_mem);

     return ul_ret;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_convert_loop_end
 输入参数  : pst_vap vap结构体; pst_buf netbuf 结构体
 输出参数  : ul_ret
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_convert_loop_end(oal_netbuf_stru *pst_copy_buf, oal_netbuf_stru **pst_buf,
                                    oal_uint8 *puc_newmaccnt, oal_uint8 *puc_newmacidx)
{
    if (OAL_PTR_NULL != pst_copy_buf)
    {
        *pst_buf = pst_copy_buf;
        pst_copy_buf = OAL_PTR_NULL;
    }
    (*puc_newmacidx)++;
    if(*puc_newmaccnt > 0)
    {
        (*puc_newmaccnt)--;
    }
}
/*****************************************************************************
 函 数 名  : hmac_m2u_snoop_convert_count
 功能描述  : 组播转单播发送计数
 输入参数  : pst_vap vap结构体; pst_buf netbuf 结构体
 输出参数  : ul_ret
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_snoop_convert_count(hmac_vap_stru *pst_vap, oal_uint32 uc_newmaccnt, oal_uint32 ul_ret, oal_netbuf_stru *pst_buf)
{
    /* ucast event fail 的发送计数 */
    if (OAL_SUCC != ul_ret)
    {
        if (uc_newmaccnt > 0)
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
        }
        else
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_droped, 1);
        }
        hmac_free_netbuf_list(pst_buf);
    }
    /* ucast发送成功的已发送组播和单播的计数 */
    else
    {
        if (uc_newmaccnt > 0)
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_cnt, 1);
        }
        else
        {
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_cnt, 1);
        }
    }
}
 /*****************************************************************************
 函 数 名  : hmac_m2u_snoop_change_mac_hdr
 功能描述  : 组播转单播发送计数
 输入参数  : pst_vap vap结构体; pst_buf netbuf 结构体
 输出参数  : ul_ret
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_snoop_change_mac_hdr(hmac_m2u_stru *pst_m2u, mac_ether_header_stru  **pst_ucast_ether_hdr, oal_netbuf_stru *pst_buf)
{
    mcast_tunnel_hdr_stru  *pst_mcast_tunHdr;
    mac_ether_header_stru  *pst_ether_hdr;
    oal_uint8               auc_srcmac[WLAN_MAC_ADDR_LEN];

    pst_ether_hdr  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    oal_set_mac_addr(auc_srcmac, pst_ether_hdr->auc_ether_shost);
    /* 加自定义tunnel协议 */
    if (pst_m2u->en_mcast_mode & BIT0)   /* en_mcast_mode = 1 */
    {
      pst_mcast_tunHdr = (mcast_tunnel_hdr_stru *) oal_netbuf_push(pst_buf, OAL_SIZEOF(mcast_tunnel_hdr_stru));
      *pst_ucast_ether_hdr = (mac_ether_header_stru *)oal_netbuf_push(pst_buf, OAL_SIZEOF(mac_ether_header_stru));
      pst_mcast_tunHdr->proto = MAC_ETH_PROTOCOL_SUBTYPE;

      /* 拷贝原始组播源地址 */
      oal_set_mac_addr(&((*pst_ucast_ether_hdr)->auc_ether_shost[0]), auc_srcmac);

      /*拷贝新的协议类型 */
      (*pst_ucast_ether_hdr)->us_ether_type = OAL_HOST2NET_SHORT(ETHER_TUNNEL_TYPE);
    }
    /* 不加自定义tunnel协议 */
    else                                /* en_mcast_mode = 2 */
    {
        *pst_ucast_ether_hdr = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);
    }
}
/*****************************************************************************
 函 数 名  : hmac_m2u_snoop_convert
 功能描述  : 发送方向的组播转单播处理
 输入参数  : pst_vap vap结构体; pst_buf netbuf 结构体
 输出参数  : ul_ret
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_snoop_convert(hmac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    hmac_user_stru         *pst_user = OAL_PTR_NULL;
    mac_ether_header_stru  *pst_ether_hdr;
    oal_uint8              *puc_dstmac;
    oal_uint32              ul_src_ip_addr = 0;
    oal_uint32              ul_grp_addr = 0;
    oal_uint8               auc_srcmac[WLAN_MAC_ADDR_LEN];
    oal_uint8               auc_grpmac[WLAN_MAC_ADDR_LEN];
    oal_uint8               auc_empty_entry_mac[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint8               newmac[MAX_SNOOP_ENTRIES][WLAN_MAC_ADDR_LEN];
    oal_uint8               uc_newmaccnt = 0;
    oal_uint8               uc_newmacidx = 0;
    mac_ether_header_stru  *pst_ucast_ether_hdr =  OAL_PTR_NULL;
    oal_netbuf_stru        *pst_copy_buf = OAL_PTR_NULL;
    oal_uint16              us_user_idx;
    oal_uint32              ul_ret = OAL_SUCC;
    mac_tx_ctl_stru        *pst_tx_ctl;
    mac_ip_header_stru     *pst_ip_header;
    hmac_m2u_stru          *pst_m2u = (hmac_m2u_stru *)(pst_vap->pst_m2u);

    /* 未打开组转单播开关，发送原组播 */
    if (OAL_FALSE == pst_m2u->en_snoop_enable)
    {
        OAM_INFO_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::snoop is [%d] not enable}", pst_m2u->en_snoop_enable);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_cnt, 1);
        return HMAC_TX_PASS;
    }
    pst_ether_hdr  = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /*组播转单播的输入检查 */
    ul_ret = hmac_m2u_check(pst_vap, pst_ether_hdr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_cnt, 1);
        return HMAC_TX_PASS;
    }

    /* 偏移一个以太网头，取ip头 */
    pst_ip_header  = (mac_ip_header_stru *)(pst_ether_hdr + 1);
    ul_src_ip_addr = pst_ip_header->ul_saddr;
    ul_grp_addr = OAL_HOST2NET_LONG(pst_ip_header->ul_daddr);

    /* 该组在黑名单内,不发送该netbuf ,直接释放 */
    if (hmac_m2u_snoop_is_denied(pst_vap, ul_grp_addr))
    {
        OAM_INFO_LOG4(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::group_addr [%x].[%x].[%x].[%x] is denied}\r\n}",
                                                                    (oal_uint32)((ul_grp_addr>> 24) & 0xff),
                                                                    (oal_uint32)((ul_grp_addr>> 16) & 0xff),
                                                                    (oal_uint32)((ul_grp_addr>> 8)  & 0xff),
                                                                    (oal_uint32)((ul_grp_addr) & 0xff));
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_cnt, 1);
        return HMAC_TX_PASS;
    }

    oal_set_mac_addr(auc_srcmac, pst_ether_hdr->auc_ether_shost);
    oal_set_mac_addr(auc_grpmac, pst_ether_hdr->auc_ether_dhost);
    uc_newmaccnt = hmac_m2u_get_snooplist_member(pst_vap, auc_grpmac, ul_src_ip_addr, newmac[0]);

    /* 如果有用户需要该netbuf，但不需要组播转单播，直接发送原组播 */
    if (uc_newmaccnt > 0 && 0 == pst_m2u->en_mcast_mode)  /* en_mcast_mode = 0 */
    {
        OAM_INFO_LOG2(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert:: %d user found , mcast mode is %d}", uc_newmaccnt, pst_m2u->en_mcast_mode);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_cnt, 1);
        return HMAC_TX_PASS;
    }

    /* 如果没有STA需要此netbuf,则不需要发送，丢弃该组播帧 */
    else if (0 == uc_newmaccnt)
    {
        OAM_INFO_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert:: %d user found}", uc_newmaccnt);
        OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_mcast_droped, 1);
        return HMAC_TX_DROP_MTOU_FAIL;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);

    /* 组播转单播 CB字段处理 */
    pst_tx_ctl->en_ismcast = OAL_FALSE;
    pst_tx_ctl->en_ack_policy  = WLAN_TX_NORMAL_ACK;
    pst_tx_ctl->us_tx_user_idx = 0xFFFF;
    pst_tx_ctl->uc_tid  = 0;
    pst_tx_ctl->uc_ac   = WLAN_WME_AC_BE;

    do{
        puc_dstmac = &newmac[uc_newmacidx][0];
        pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);

        if (uc_newmaccnt > 1)
        {
            pst_copy_buf = oal_netbuf_copy(pst_buf, GFP_ATOMIC);
        }

        /* 发送的目的地址和发来的源地址相同的异常处理 */
        if (!oal_compare_mac_addr(puc_dstmac, auc_srcmac))
        {
            hmac_free_netbuf_list(pst_buf);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
            OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::dstmac == srcmac.}");

            /* 组播转单播发送循环的末尾处理 */
            hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
            continue;
        }

        /* 如果接收端的STA的地址为空，则说明至少有一个STA加入到这个组后又离开了 */
        /* 这样的情况需要丢弃该帧 */
        if (!oal_compare_mac_addr(puc_dstmac, auc_empty_entry_mac))
        {
            OAM_INFO_LOG2(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::dstmac == NULL && newmaccnt is %d && discard mcast is %d}", uc_newmaccnt, pst_m2u->en_discard_mcast);
            if ((uc_newmaccnt > 1) || (pst_m2u->en_discard_mcast))
            {
                hmac_free_netbuf_list(pst_buf);
                OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
                /* 组播转单播发送循环的末尾处理 */
                hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
                continue;
            }
            /* 如果只有一个地址为空的STA用户,将该MAC地址还原成组播组的MAC地址 */
            else
            {
                uc_newmaccnt = 0;
                puc_dstmac = pst_ether_hdr->auc_ether_dhost;

                /* 组播CB字段处理 */
                pst_tx_ctl->en_ismcast = OAL_TRUE;
                pst_tx_ctl->en_ack_policy = WLAN_TX_NO_ACK;
                pst_tx_ctl->uc_tid  = WLAN_TIDNO_BCAST;
                pst_tx_ctl->uc_ac   = WLAN_WME_TID_TO_AC(pst_tx_ctl->uc_tid);
            }
        }

        /* 组播用户的查找 */
        if ((ETHER_IS_MULTICAST(puc_dstmac)) && (!ETHER_IS_BROADCAST(puc_dstmac)))
        {
            us_user_idx = pst_vap->st_vap_base_info.us_multi_user_idx;
            ul_ret = HMAC_TX_PASS;
        }

        /* 组播转单播用户的查找 */
        else
        {
            ul_ret = mac_vap_find_user_by_macaddr(&(pst_vap->st_vap_base_info), puc_dstmac, &us_user_idx);
        }

         /* 用户未找到，丢弃该帧 */
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::find user fail[%d].}", ul_ret);
            hmac_free_netbuf_list(pst_buf);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
            hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
            continue;
        }

        /* 转成HMAC的USER结构体 */
        pst_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_m2u_snoop_convert::null param,pst_user[%d].}",us_user_idx);
            hmac_free_netbuf_list(pst_buf);
            OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
            hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
            continue;
        }
        /* 用户状态判断 */
        if (OAL_UNLIKELY(MAC_USER_STATE_ASSOC != pst_user->st_user_base_info.en_user_asoc_state))
        {
            if (uc_newmaccnt > 0)
			{
				hmac_m2u_cleanup_snoopwds_node(pst_user);
			}
            /* 发送失败计数 */
            hmac_m2u_snoop_convert_count(pst_vap, uc_newmaccnt, OAL_FAIL, pst_buf);
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::asoc state is [%d].}", pst_user->st_user_base_info.en_user_asoc_state);
            /* 组播转单播发送循环的末尾处理 */
            hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
            continue;
        }

        /* 目标user指针 */
        pst_tx_ctl->us_tx_user_idx = us_user_idx;

        /* 组播转单播,单播以太网头的封装 */
        if (uc_newmaccnt > 0)
        {
            /* 组播转单播，mac头的封装 */
            hmac_m2u_snoop_change_mac_hdr(pst_m2u, &pst_ucast_ether_hdr, pst_buf);

            /* 拷贝新的目的地址 */
            oal_set_mac_addr(&pst_ucast_ether_hdr->auc_ether_dhost[0], &newmac[uc_newmacidx][0]);
            ul_ret = hmac_tx_ucast_process(pst_vap, pst_buf, pst_user, pst_tx_ctl);

            if (OAL_UNLIKELY(HMAC_TX_PASS != ul_ret))
            {
                if ((HMAC_TX_BUFF != ul_ret))
                {
                    /* 不等于HMAC_TX_BUFF，不缓存的直接释放 */
                    OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_snoop_convert::hmac_tx_ucast_process not pass or buff, ul_ret = [%d]}", ul_ret);
                    OAM_STAT_VAP_INCR(pst_vap->st_vap_base_info.uc_vap_id, tx_m2u_ucast_droped, 1);
                    hmac_free_netbuf_list(pst_buf);
                }

                /* 组播转单播发送循环的末尾处理 */
                hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);
                continue;
            }
        }
        ul_ret = hmac_m2u_tx_event(pst_vap, pst_user, pst_buf);

        /* 组播转单播发送计数统计 */
        hmac_m2u_snoop_convert_count(pst_vap, uc_newmaccnt, ul_ret, pst_buf);

        /* 组播转单播发送循环的末尾处理 */
        hmac_m2u_convert_loop_end(pst_copy_buf, &pst_buf, &uc_newmaccnt, &uc_newmacidx);

    }while (uc_newmaccnt > 0 && pst_m2u->en_snoop_enable);

    return HMAC_TX_DONE;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_snoop_list_init
 功能描述  : 发送方向的组播转单播处理
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_snoop_list_init( hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_stru            *pst_m2u  = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    hmac_m2u_snoop_list_stru *pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    pst_snp_list->us_group_list_count = 0;
    pst_snp_list->us_misc = 0;
    oal_dlist_init_head(&(pst_snp_list->st_grp_list));
}

/*****************************************************************************
 函 数 名  : hmac_m2u_time_fn
 功能描述  : 组播转单播的定时器，删除长时间沉默的成员
 输入参数  : p_arg 输入参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_m2u_time_fn(oal_void *p_arg)
{
    hmac_vap_stru *pst_hmac_vap = (hmac_vap_stru *)p_arg;
    hmac_m2u_stru *pst_m2u  = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);
    hmac_m2u_snoop_list_stru *pst_snp_list = &(pst_m2u->st_m2u_snooplist);
    hmac_m2u_grp_list_entry_stru  *pst_grp_list;
    oal_dlist_head_stru           *pst_grp_list_entry;
    oal_dlist_head_stru           *pst_grp_list_entry_temp;
    oal_uint32                     ul_ret = OAL_SUCC;

    oal_uint32  ul_nowtime = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_grp_list_entry, pst_grp_list_entry_temp, &(pst_snp_list->st_grp_list))
    {
        pst_grp_list = (hmac_m2u_grp_list_entry_stru *)OAL_DLIST_GET_ENTRY(pst_grp_list_entry,
                                                                        hmac_m2u_grp_list_entry_stru,
                                                                            st_grp_entry);
        ul_ret = hmac_m2u_remove_expired_member(pst_grp_list, pst_hmac_vap, ul_nowtime);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }

        if (OAL_TRUE == (oal_dlist_is_empty(&(pst_grp_list->st_src_list))))
        {
            oal_dlist_delete_entry(&(pst_grp_list->st_grp_entry));
            OAL_MEM_FREE(pst_grp_list, OAL_TRUE);
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_m2u_attach
 功能描述  : 组播转单播的初始化函数
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_attach(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_stru            *pst_m2u;
    hmac_m2u_snoop_list_stru *pst_snp_list;

    pst_m2u = (hmac_m2u_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                            OAL_SIZEOF(hmac_m2u_stru),
                                            OAL_TRUE);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_m2u))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_M2U, "{hmac_m2u_attach::pst_m2u is null!}");
        return;
    }

    pst_hmac_vap->pst_m2u = pst_m2u;
	pst_snp_list = &(pst_m2u->st_m2u_snooplist);

    oal_memset(pst_m2u, 0, OAL_SIZEOF(hmac_m2u_stru));
    /* 启动定时器 */
    FRW_TIMER_CREATE_TIMER(&(pst_m2u->st_snooplist_timer),
                           hmac_m2u_time_fn,
                           HMAC_DEF_M2U_TIMER,
                           pst_hmac_vap,
                           OAL_TRUE,
                           OAM_MODULE_ID_HMAC,
                           pst_hmac_vap->st_vap_base_info.ul_core_id);

    pst_m2u->en_snoop_enable = OAL_TRUE;  /* 默认使能，组播转发时需要根据snoop表确认是否有用户再转发 */
    pst_m2u->en_discard_mcast = 1;
    pst_m2u->ul_timeout = HMAC_DEF_M2U_TIMEOUT;

    pst_m2u->en_mcast_mode = 2;          /*默认打开组播转单播开关*/
    pst_snp_list->uc_deny_count = 3;
    pst_snp_list->ul_deny_group[0] = HMAC_M2U_ALL_GROUP; /* 224.0.0.1 */
    pst_snp_list->ul_deny_mask[0] =  HMAC_M2U_SUBNET_MASK; /* 255.255.255.0 */

    pst_snp_list->ul_deny_group[1] = HMAC_M2U_DENY_GROUP; /* 239.255.255.1 */
    pst_snp_list->ul_deny_mask[1] =  HMAC_M2U_SUBNET_MASK; /* 255.255.255.0 */

    /* IGMP v3协议224.0.0.22不被过滤 */
    pst_snp_list->ul_deny_group[2] = HMAC_M2U_IGMPV3_GROUP; /* 224.0.0.22 */
    pst_snp_list->ul_deny_mask[2] =  HMAC_M2U_SUBNET_MASK;   /* 255.255.255.0 */

    pst_snp_list->us_max_length = MAX_SNOOP_ENTRIES;
    hmac_m2u_snoop_list_init(pst_hmac_vap);
}
/*****************************************************************************
 函 数 名  : hmac_m2u_detach
 功能描述  : 组播转单播的detach
 输入参数  : pst_hmac_vap vap结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_m2u_detach(hmac_vap_stru *pst_hmac_vap)
{
    hmac_m2u_stru    *pst_m2u  = (hmac_m2u_stru *)(pst_hmac_vap->pst_m2u);

    if(pst_m2u != OAL_PTR_NULL)
    {
        hmac_m2u_clean_snp_list(pst_hmac_vap);
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_m2u->st_snooplist_timer));
        OAL_MEM_FREE(pst_m2u, OAL_TRUE);
        pst_hmac_vap->pst_m2u = OAL_PTR_NULL;
    }
}
/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_m2u_snoop_inspecting);
oal_module_symbol(hmac_m2u_attach);
oal_module_symbol(hmac_m2u_snoop_convert);
oal_module_symbol(hmac_m2u_detach);
oal_module_symbol(hmac_m2u_clear_deny_table);
oal_module_symbol(hmac_m2u_print_all_snoop_list);
oal_module_symbol(hmac_m2u_show_snoop_deny_table);
oal_module_symbol(hmac_m2u_add_snoop_deny_entry);
oal_module_symbol(hmac_m2u_cleanup_snoopwds_node);
#endif
/*lint +e578*//*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
