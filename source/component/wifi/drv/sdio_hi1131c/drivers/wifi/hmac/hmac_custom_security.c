/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_custom_security.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年3月26日
  最近修改   :
  功能描述   : 自定义安全
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_main.h"
#include "hmac_custom_security.h"
#include "mac_vap.h"
#include "hmac_vap.h"
#include "mac_resource.h"
#include "hmac_user.h"
#include "hmac_mgmt_ap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CUSTOM_SECURITY_C

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
    /*
    CS_ISOLATION_MODE_BROADCAST =0x01
    CS_ISOLATION_MODE_MULTICAST =0x02
    CS_ISOLATION_MODE_UNICAST   =0x04    */
#define BROADCAST_ISOLATION(_a)   ((_a) & CS_ISOLATION_MODE_BROADCAST)
#define MULTICAST_ISOLATION(_a)   ((_a) & CS_ISOLATION_MODE_MULTICAST)
#define UNICAST_ISOLATION(_a)     ((_a) & CS_ISOLATION_MODE_UNICAST)


/*****************************************************************************
  3 全局变量定义
*****************************************************************************/

/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hmac_blacklist_mac_is_zero
 功能描述  : 判断mac地址是否为0
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_blacklist_mac_is_zero(oal_uint8 *puc_mac_addr)
{
    if (puc_mac_addr[0] == 0 &&
            puc_mac_addr[1] == 0 &&
            puc_mac_addr[2] == 0 &&
            puc_mac_addr[3] == 0 &&
            puc_mac_addr[4] == 0 &&
            puc_mac_addr[5] == 0)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_mac_is_bcast
 功能描述  : 判断mac地址是否为0
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_blacklist_mac_is_bcast(oal_uint8 *puc_mac_addr)
{
    if (puc_mac_addr[0] == 0xff &&
            puc_mac_addr[1] == 0xff &&
            puc_mac_addr[2] == 0xff &&
            puc_mac_addr[3] == 0xff &&
            puc_mac_addr[4] == 0xff &&
            puc_mac_addr[5] == 0xff)
    {
        return 1;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_init
 功能描述  : 关闭黑名单功能，并清空所有数据
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_blacklist_init(mac_vap_stru *pst_mac_vap, cs_blacklist_mode_enum_uint8 en_mode)
{
    oal_uint32                   ul_size;
    mac_blacklist_info_stru     *pst_blacklist_info;
    hmac_vap_stru               *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;
    ul_size = sizeof(mac_blacklist_info_stru);
    /* Max=32 => 新增加mac_vap结构大小= 0x494 = 1172 ; Max=8 => size = 308 */
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_init stru_size=%d}",ul_size);
    oal_memset(pst_blacklist_info, 0, ul_size);

    pst_blacklist_info->uc_mode = en_mode;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_is_aged
 功能描述  : 更新表单老化属性
 输入参数  :
 输出参数  : oal_void
 返 回 值  : OAL_TRUE 已经老化 OAL_FALSE 没有老化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_blacklist_is_aged(mac_vap_stru *pst_mac_vap, mac_blacklist_stru *pst_blacklist)
{
    oal_time_us_stru              st_cur_time;
    mac_blacklist_info_stru      *pst_blacklist_info;
    oal_uint8                    *puc_mac_addr;
    hmac_vap_stru                *pst_hmac_vap;

    /* 1.1 全零地址，属于非法地址 */
    if (hmac_blacklist_mac_is_zero(pst_blacklist->auc_mac_addr))
    {
        return OAL_FALSE;
    }

    /* 2.1 老化时间为0表示不需要老化 */
    if (0 == pst_blacklist->ul_aging_time)
    {
        return OAL_FALSE;
    }

    /* 2.2 没有超过老化时间 */
    oal_time_get_stamp_us(&st_cur_time);
    if (st_cur_time.i_sec < (oal_int)(pst_blacklist->ul_cfg_time + pst_blacklist->ul_aging_time))
    {
        return OAL_FALSE;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_is_aged::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    puc_mac_addr = pst_blacklist->auc_mac_addr;
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{aging time reach delete MAC:=%02X:XX:XX:%02X:%02X:%02X}",
            puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);

    /* 3.1 直接从黑名单中删除 */
    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;
    if (CS_BLACKLIST_MODE_BLACK == pst_blacklist_info->uc_mode)
    {
        oal_memset(pst_blacklist, 0, sizeof(mac_blacklist_stru));
        if(pst_blacklist_info->uc_list_num > 0)
        {
            pst_blacklist_info->uc_list_num--;      /* 2014.7.23 bug fixed */
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{del from blacklist & num=%d}",pst_blacklist_info->uc_list_num);
        }
        return OAL_TRUE;
    }

    /* 4.1 直接从白名单中恢复 */
    if (CS_BLACKLIST_MODE_WHITE == pst_blacklist_info->uc_mode)
    {
        pst_blacklist->ul_aging_time = 0;
        return OAL_TRUE;
    }

    return OAL_FALSE;

}

/*****************************************************************************
 函 数 名  : hmac_blacklist_get
 功能描述  : 从表单中查找mac地址相同的表单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_blacklist_get(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, mac_blacklist_stru **ppst_blacklist)
{
    oal_uint8                     ul_blacklist_index;
    mac_blacklist_info_stru      *pst_blacklist_info = OAL_PTR_NULL;
    hmac_vap_stru                *pst_hmac_vap;

    /* 1.1 广播地址，属于非法地址 */
    if (hmac_blacklist_mac_is_bcast(puc_mac_addr))
    {
        return OAL_ERR_CODE_SECURITY_MAC_INVALID;
    }

    /* 1.2 全零地址，属于非法地址 */
    if (hmac_blacklist_mac_is_zero(puc_mac_addr))
    {
        return OAL_ERR_CODE_SECURITY_MAC_INVALID;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 2.1 找到表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        *ppst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (!oal_memcmp((*ppst_blacklist)->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN))
        {
            break;
        }
        *ppst_blacklist = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_backlist_get_drop
 功能描述  : 获取对应mac的 ul_drop_counter 值，用于UT测试用!
 输入参数  : mac_addr
 输出参数  : null
 返 回 值  : ul_drop_counter 值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_backlist_get_drop(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    mac_blacklist_stru *pst_blacklist = OAL_PTR_NULL;	/* 2014.9.2 Add UT and found no init value set to it ! add initial value null */

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_backlist_get_drop::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_blacklist_get(pst_mac_vap, puc_mac_addr, &pst_blacklist);
    if(OAL_PTR_NULL !=  pst_blacklist)
    {
        return pst_blacklist->ul_drop_counter;
    }

    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : hmac_backlist_set_drop
 功能描述  : 减1 ul_drop_counter 值，用以恢复 counter 值 ++
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_backlist_sub_drop(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    oal_uint32  ul_ret;
    mac_blacklist_stru *pst_blacklist = OAL_PTR_NULL;	/* 2014.9.2 Add UT and found no init value set to it ! add initial value null */

    ul_ret = hmac_blacklist_get(pst_mac_vap, puc_mac_addr, &pst_blacklist);

    if( OAL_PTR_NULL !=  pst_blacklist){
        if(pst_blacklist->ul_drop_counter > 0)
            pst_blacklist->ul_drop_counter--;
        ul_ret = OAL_SUCC;
    }
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_backlist_get_list_num
 功能描述  : 获取黑白名单中有多少个项
 输入参数  :
 输出参数  : null
 返 回 值  : uc_list_num 值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 hmac_backlist_get_list_num(mac_vap_stru *pst_mac_vap)
{
    mac_blacklist_info_stru      *pst_blacklist_info;
    hmac_vap_stru                *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_backlist_get_list_num::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_backlist_get_list_num::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    return pst_blacklist_info->uc_list_num;
}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_get
 功能描述  : 从表单中查找mac地址相同的表单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_autoblacklist_get(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, mac_autoblacklist_stru **ppst_autoblacklist)
{
    oal_uint8                         ul_blacklist_index;
    mac_autoblacklist_info_stru      *pst_autoblacklist_info;
    oal_time_us_stru                  st_cur_time;
    oal_uint32                        ul_cfg_time_old;
    oal_uint32                        ul_blacklist_index_old;
    mac_autoblacklist_stru *          pst_autoblacklist = OAL_PTR_NULL;
    hmac_vap_stru                    *pst_hmac_vap;


    /* 1.1 广播地址，属于非法地址 */
    if (hmac_blacklist_mac_is_bcast(puc_mac_addr))
    {
        return OAL_ERR_CODE_SECURITY_MAC_INVALID;
    }

    /* 1.2 全零地址，属于非法地址 */
    if (hmac_blacklist_mac_is_zero(puc_mac_addr))
    {
        return OAL_ERR_CODE_SECURITY_MAC_INVALID;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    oal_time_get_stamp_us(&st_cur_time);

    *ppst_autoblacklist = OAL_PTR_NULL;

    /* 2.1 找到历史表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_ASSOC_USER_MAX_NUM_SPEC; ul_blacklist_index++)
    {
        /**ppst_autoblacklist = &pst_autoblacklist_info->ast_autoblack_list[ul_blacklist_index];*/
        pst_autoblacklist = &pst_autoblacklist_info->ast_autoblack_list[ul_blacklist_index];
        /* 2.2 无效表单*/
        if (pst_autoblacklist->ul_cfg_time == 0)
        {
            continue;
        }

        /* 2.2 过期表单直接清0*/
        if (st_cur_time.i_sec > (oal_int)(pst_autoblacklist->ul_cfg_time + pst_autoblacklist_info->ul_reset_time))
        {
            if(pst_autoblacklist_info->list_num > 0)
                pst_autoblacklist_info->list_num--;
            oal_memset(pst_autoblacklist, 0, OAL_SIZEOF(mac_autoblacklist_stru));
            continue;
        }

        /* 2.3 有效表单，mac地址比对*/
        if (!oal_memcmp(pst_autoblacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN))
        {
            *ppst_autoblacklist = pst_autoblacklist;
            break;
        }
        /*pst_autoblacklist = OAL_PTR_NULL;*/   /* bug fixed */
    }

    if (OAL_PTR_NULL != *ppst_autoblacklist)
    {
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{Get a history item from auto_blacklist.index=%d.MAC=x.x.x.x.%02x.%02x. assoc_count=%d.}",
            ul_blacklist_index,puc_mac_addr[4],puc_mac_addr[5],pst_autoblacklist->ul_asso_counter);
        return OAL_SUCC;
    }

    /* 3.1 找到新表单 */
    ul_cfg_time_old        = (st_cur_time.i_sec > 0) ? (oal_uint32)(st_cur_time.i_sec) : 0;
    ul_blacklist_index_old = 0;
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_ASSOC_USER_MAX_NUM_SPEC; ul_blacklist_index++)
    {
        pst_autoblacklist = &pst_autoblacklist_info->ast_autoblack_list[ul_blacklist_index];
        /* 2.2 找到空闲表单 */
        if (pst_autoblacklist->ul_cfg_time == 0)
        {
            pst_autoblacklist_info->list_num++;
            *ppst_autoblacklist = pst_autoblacklist;
            break;
        }

        /* 2.3 记录最老配置的表单 */
        if (pst_autoblacklist->ul_cfg_time < ul_cfg_time_old)
        {
            ul_cfg_time_old         = pst_autoblacklist->ul_cfg_time;
            ul_blacklist_index_old  = ul_blacklist_index;
        }

        /*pst_autoblacklist = OAL_PTR_NULL;*/
    }

    /* 4.1 如果没有空闲的表单，就使用最老的表单 */
    /*if (OAL_PTR_NULL == pst_autoblacklist)*/
    if (OAL_PTR_NULL == *ppst_autoblacklist)
    {
        pst_autoblacklist = &pst_autoblacklist_info->ast_autoblack_list[ul_blacklist_index_old];
        *ppst_autoblacklist = pst_autoblacklist;
    }

    /* 5.1 更新表单 */
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{add to auto_blacklist MAC:=%02X:XX:XX:%02X:%02X:%02X. assoc_count=1.}",
            puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);
    if (OAL_PTR_NULL == pst_autoblacklist)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{hmac_autoblacklist_get::pst_autoblacklist NULL}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memcopy(pst_autoblacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN);
    pst_autoblacklist->ul_cfg_time = (oal_uint32)st_cur_time.i_sec;
    pst_autoblacklist->ul_asso_counter = 0; /* bug 1 => 0 fixed */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_check_user
 功能描述  : 添加黑/白名单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_blacklist_check_user(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru                *pst_mac_user;
    hmac_user_stru                *pst_hmac_user;
    hmac_vap_stru                 *pst_hmac_vap;
    oal_uint32                  ul_ret;
    oal_uint16                  us_idx;
    oal_bool_enum_uint8         bool_ret;

    for (us_idx = 0;  us_idx < (mac_res_get_max_asoc_user() + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC; us_idx++)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_idx);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            continue;   // 2014.7.3  这里永远不会返回空指针
        } /*此分支造成UT不容易覆盖，打桩进入此流程失败，考虑到实际不会走到这里，所以删除它(还是不动保留它) */

        if (pst_mac_user->en_user_asoc_state != MAC_USER_STATE_ASSOC)
        {
            continue;
        }

        /* bug: check_user MAC: 00:00:00:00:00:00 => hmac_blacklist_get fail 21015 */
        if (hmac_blacklist_mac_is_zero(pst_mac_user->auc_user_mac_addr))
        {
            continue;   /* 2014.8.13 创建vap就会加入一个组播用户 mac全零，不对此user做处理  */
        }

        /* bug: check_user MAC: ff:ff:ff:ff:ff:ff => hmac_blacklist_get fail 21015 */
        if (hmac_blacklist_mac_is_bcast(pst_mac_user->auc_user_mac_addr))
        {
            continue;   /* 2015.5.19 创建vap就会加入一个用户 mac全F，不对此user做处理  */
        }

        bool_ret = hmac_blacklist_filter(pst_mac_vap, pst_mac_user->auc_user_mac_addr);
        if (OAL_TRUE != bool_ret)
        {
            continue;
        }
        /* 2014.6.30  在如上的hmac_blacklist_filter()中会 ul_drop_counter++ 它不是实际的过滤数，所以--恢复 */
        hmac_backlist_sub_drop(pst_mac_vap,pst_mac_user->auc_user_mac_addr);

        /* ul_ret = mac_vap_del_user(pst_mac_vap, us_idx); 2014.7.1  bug fixed */
        pst_hmac_user = mac_res_get_hmac_user(us_idx);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_check_user::mac_res_get_hmac_user fail IDX:%d}",us_idx);
            continue;
        }

        hmac_mgmt_send_disassoc_frame(pst_mac_vap, pst_hmac_user->st_user_base_info.auc_user_mac_addr,
            MAC_DISAS_LV_SS, OAL_FALSE);    /* 2014.7.24 发去关联 bug fixed */

        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
        if(OAL_PTR_NULL != pst_hmac_vap)
        {
            /* 删除黑名单内用户，需要上报内核 */
            hmac_handle_disconnect_rsp_ap(pst_hmac_vap, pst_hmac_user);
        }

        ul_ret = hmac_user_del(pst_mac_vap, pst_hmac_user);

        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_check_user::hmac_user_del fail %d}",ul_ret);
            return ul_ret;
        }
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_check_user::hmac_user_del succ}");
        break;  /* 2014.7.1  找到一个即可退出!  */
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_add
 功能描述  : 添加黑/白名单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_blacklist_add(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time)
{
    oal_uint32                    ul_ret;
    oal_uint8                     ul_blacklist_index;
    mac_blacklist_info_stru      *pst_blacklist_info;
    mac_blacklist_stru           *pst_blacklist = OAL_PTR_NULL;
    oal_time_us_stru              st_cur_time;
    hmac_vap_stru                *pst_hmac_vap;


    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_add::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 3.1 找到表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (!oal_memcmp(pst_blacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN))
        {
            break;
        }
        pst_blacklist = OAL_PTR_NULL;
    }

    /* 4.1 表单已经存在，只更新老化时间 */
    if (OAL_PTR_NULL != pst_blacklist)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{blacklist_add allready exist. update aging = %d}",ul_aging_time);
        pst_blacklist->ul_aging_time = ul_aging_time;
        return OAL_SUCC;
    }

    /* 5.1 找一个地址为空的表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (hmac_blacklist_mac_is_zero(pst_blacklist->auc_mac_addr))
        {
            break;
        }
        pst_blacklist = OAL_PTR_NULL;
    }

    /* 6.1 无可用表单 */
    if (OAL_PTR_NULL == pst_blacklist)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> blacklist_add:: src mac=x.x.x.%02x.%02x.%02x. new count is %d; full return}",
            puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5],pst_blacklist_info->uc_list_num);
        return OAL_ERR_CODE_SECURITY_LIST_FULL;
    }

    /* 7.1 更新表单 */
    oal_time_get_stamp_us(&st_cur_time);
    oal_memcopy(pst_blacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN);
    pst_blacklist->ul_cfg_time     = (oal_uint32)st_cur_time.i_sec;
    pst_blacklist->ul_aging_time   = ul_aging_time;
    pst_blacklist->ul_drop_counter = 0;
    pst_blacklist_info->uc_list_num++;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> blacklist_add:: src mac=x.x.x.x.%02x.%02x. new count is %d, time=%d}",
            puc_mac_addr[4],puc_mac_addr[5],pst_blacklist_info->uc_list_num,pst_blacklist->ul_cfg_time);

    /* 7.2 2014.6.30  这里检查添加的黑名单是否为assoc用户，是的话需要 delete user */
    ul_ret = hmac_blacklist_check_user(pst_mac_vap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_add::check_user failed %d}",ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_add_only
 功能描述  : 添加黑/白名单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_blacklist_add_only(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint32 ul_aging_time)
{
    oal_uint8                     ul_blacklist_index;
    mac_blacklist_info_stru      *pst_blacklist_info;
    mac_blacklist_stru           *pst_blacklist = OAL_PTR_NULL;
    oal_time_us_stru              st_cur_time;
    hmac_vap_stru                *pst_hmac_vap;


    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_add_only::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_add_only::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 3.1 找到表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (!oal_memcmp(pst_blacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN))
        {
            break;
        }
        pst_blacklist = OAL_PTR_NULL;
    }

    /* 4.1 表单已经存在，只更新老化时间 */
    if (OAL_PTR_NULL != pst_blacklist)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{blacklist_add allready exist. update aging = %d}",ul_aging_time);
        pst_blacklist->ul_aging_time = ul_aging_time;
        return OAL_SUCC;
    }

    /* 5.1 找一个地址为空的表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (hmac_blacklist_mac_is_zero(pst_blacklist->auc_mac_addr))
        {
            break;
        }
        pst_blacklist = OAL_PTR_NULL;
    }

    /* 6.1 无可用表单 */
    if (OAL_PTR_NULL == pst_blacklist)
    {
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> blacklist_add:: src mac=x.x.x.%02x.%02x.%02x. new count is %d; full return}",
            puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5],pst_blacklist_info->uc_list_num);
        return OAL_ERR_CODE_SECURITY_LIST_FULL;
    }

    /* 7.1 更新表单 */
    oal_time_get_stamp_us(&st_cur_time);
    oal_memcopy(pst_blacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN);
    pst_blacklist->ul_cfg_time     = (oal_uint32)st_cur_time.i_sec;
    pst_blacklist->ul_aging_time   = ul_aging_time;
    pst_blacklist->ul_drop_counter = 0;
    pst_blacklist_info->uc_list_num++;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> blacklist_add:: src mac=x.x.x.x.%02x.%02x. new count is %d, time=%d}",
            puc_mac_addr[4],puc_mac_addr[5],pst_blacklist_info->uc_list_num,pst_blacklist->ul_cfg_time);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_del
 功能描述  : 添加黑/白名单
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_blacklist_del(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    oal_uint8                     ul_blacklist_index;
    mac_blacklist_stru           *pst_blacklist = OAL_PTR_NULL;
    mac_blacklist_info_stru      *pst_blacklist_info;
    hmac_vap_stru                *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_del::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            "{hmac_blacklist_del::pst_hmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 如果模式不一致，不需要删除，返回失败即可 */
    /*if (pst_blacklist_info->uc_mode == CS_BLACKLIST_MODE_NONE)
    {
        return OAL_ERR_CODE_HMAC_SECURITY_MODE_INVALID;
    }*/
    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 3.1 广播地址，需要删除所有表单 */
    if (hmac_blacklist_mac_is_bcast(puc_mac_addr))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{hmac_blacklist_del::broadcast addr; delete all hmac_blacklist}");

        hmac_blacklist_init(pst_mac_vap, pst_blacklist_info->uc_mode);

        return OAL_SUCC;
    }

    /* 4.1 找到表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (!oal_memcmp(pst_blacklist->auc_mac_addr, puc_mac_addr, OAL_MAC_ADDR_LEN))
        {
            break;
        }
        pst_blacklist = OAL_PTR_NULL;
    }

    /* 5.1 如果找到表单，删除 */
    if (OAL_PTR_NULL != pst_blacklist)
    {
        oal_memset(pst_blacklist, 0, sizeof(mac_blacklist_stru));
        pst_blacklist_info->uc_list_num--;
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{hmac_blacklist_del:: mac=x.x.x.%02x.%02x.%02x. new count is %d}",
            puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5],pst_blacklist_info->uc_list_num);
    }
    else
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{hmac_blacklist_del:: didn't find this mac: %02X:XX:XX:%02X:%02X:%02X}",
            puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_blacklist_update
 功能描述  : 黑名单更新
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_blacklist_update(mac_vap_stru *pst_mac_vap, hmac_blacklist_cfg_stru *pst_blacklist_cfg)
{
    cs_blacklist_mode_enum_uint8    en_mode;
    oal_uint8                      *puc_mac_addr;
    oal_uint32                      ul_ret;

    /* 1.1 入参检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_blacklist_cfg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_update::null mac_vap or null cfg data}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    en_mode      = (cs_blacklist_type_enum_uint8)pst_blacklist_cfg->uc_mode;
    puc_mac_addr = (oal_uint8 *)pst_blacklist_cfg->auc_sa;

    /*  */
    if (hmac_blacklist_mac_is_zero(puc_mac_addr))
    {
        return OAL_ERR_CODE_SECURITY_MAC_INVALID;
    }

    /* 2.2 非法参数处理 */
    /*if (en_type != CS_BLACKLIST_TYPE_ADD)
    {
        en_type = CS_BLACKLIST_TYPE_DEL;
    } 只支持add & del ，其它将返回错误！2014.9.2  9月2日 */


    /* 3.1 根据不同模式增加表单 */
    switch (en_mode)
    {
        /*case CS_BLACKLIST_MODE_NONE:
            hmac_blacklist_init(pst_mac_vap, CS_BLACKLIST_MODE_NONE);
            break; 只支持add & del ，其它将返回错误！2014.9.2  9月2日 */

        case CS_BLACKLIST_MODE_BLACK:
        case CS_BLACKLIST_MODE_WHITE:
            ul_ret = hmac_blacklist_add(pst_mac_vap, puc_mac_addr, CS_INVALID_AGING_TIME);
            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_add::fail ret=%d}",ul_ret);
                return ul_ret;
            }
            break;

        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{unknown mode=%d}",en_mode);
            return OAL_ERR_CODE_SECURITY_MODE_INVALID;
    }

    ul_ret = hmac_blacklist_check_user(pst_mac_vap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_check_user failed ret=%d}",ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_blacklist_set_mode
 功能描述  : 黑名单更新
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_blacklist_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode)
{
    /*oal_uint32        ul_ret; */

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_set_mode::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> blacklist_set_mode::mode = %d}",uc_mode);

    /* 2.1 根据不同模式增加表单 */
    switch (uc_mode)
    {
        case CS_BLACKLIST_MODE_NONE:
        case CS_BLACKLIST_MODE_BLACK:
        case CS_BLACKLIST_MODE_WHITE:
            hmac_blacklist_init(pst_mac_vap, uc_mode);
            break;

        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{unknow mode = %d}",uc_mode);
            return OAL_ERR_CODE_SECURITY_MODE_INVALID;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_show_autoblacklist_info
 功能描述  : 显示黑名单信息
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_show_autoblacklist_info(mac_autoblacklist_info_stru *pst_autoblacklist_info)
{
    oal_uint8                    ul_blacklist_index;
    oal_uint8                   *puc_sa;
    mac_autoblacklist_stru      *pst_autoblacklist;
    oal_int8                    *pc_print_buff;
    oal_uint8                    buff_index;

    pc_print_buff = (oal_int8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAM_REPORT_MAX_STRING_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == pc_print_buff)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{hmac_show_autoblacklist_info::pc_print_buff null.}");
        return;
    }
    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);

    /* 2.1 黑名单配置信息 */

    OAM_INFO_LOG4(0, OAM_SF_ANY, "{>>>>>> AUTOBLACKLIST[%d] info: THRESHOLD: %u. RESET_TIME: %u sec. AGING_TIME: %u sec}",
        pst_autoblacklist_info->uc_enabled,pst_autoblacklist_info->ul_threshold,
        pst_autoblacklist_info->ul_reset_time,pst_autoblacklist_info->ul_aging_time);

    buff_index = OAL_SPRINTF(pc_print_buff,OAM_REPORT_MAX_STRING_LEN,
            "\nAUTOBLACKLIST[%d] info:\n"
            "  THRESHOLD: %u\n"
            "  RESET_TIME: %u sec\n"
            "  AGING_TIME: %u sec\n",
            pst_autoblacklist_info->uc_enabled,pst_autoblacklist_info->ul_threshold,
            pst_autoblacklist_info->ul_reset_time,pst_autoblacklist_info->ul_aging_time);

    /* 4.1 打印黑名单表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_ASSOC_USER_MAX_NUM_SPEC; ul_blacklist_index++)
    {
        pst_autoblacklist = &pst_autoblacklist_info->ast_autoblack_list[ul_blacklist_index];
        if (hmac_blacklist_mac_is_zero(pst_autoblacklist->auc_mac_addr))
        {
            continue;
        }
        puc_sa = pst_autoblacklist->auc_mac_addr;
        OAM_INFO_LOG4(0, OAM_SF_ANY,
            "{src mac=%02X:XX:XX:%02X:%02X:%02X}",puc_sa[0],puc_sa[3],puc_sa[4],puc_sa[5]);
        OAM_INFO_LOG2(0, OAM_SF_ANY,"{ ASSO_CNT: %u. cfg_time=%d. }",
            pst_autoblacklist->ul_asso_counter,pst_autoblacklist->ul_cfg_time);

        buff_index += OAL_SPRINTF(pc_print_buff+buff_index,(OAM_REPORT_MAX_STRING_LEN-buff_index),
            "\n[%02d] MAC: %02X:XX:XX:%02X:%02X:%02X\n"
            " cfg_time=%d. ASSO_CNT: %d\n",
            ul_blacklist_index,
            pst_autoblacklist->auc_mac_addr[0],
            pst_autoblacklist->auc_mac_addr[3],
            pst_autoblacklist->auc_mac_addr[4],
            pst_autoblacklist->auc_mac_addr[5],
            pst_autoblacklist->ul_cfg_time,pst_autoblacklist->ul_asso_counter);
    }
    oam_print(pc_print_buff);
    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

}

/*****************************************************************************
 函 数 名  : hmac_show_blacklist_info
 功能描述  : 显示黑名单信息
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_show_blacklist_info(mac_vap_stru *pst_mac_vap)
{
    oal_uint8                    *puc_sa;
    oal_uint8                     buff_index;
    oal_uint8                     ul_blacklist_index;
    mac_blacklist_stru           *pst_blacklist;
    mac_blacklist_info_stru      *pst_blacklist_info;
    oal_time_us_stru              st_cur_time;
    oal_int8                     *pc_print_buff;
    hmac_vap_stru                *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_show_blacklist_info::null mac_vap}");
        return ;
    }

    pc_print_buff = (oal_int8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAM_REPORT_MAX_STRING_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == pc_print_buff)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_show_blacklist_info::pc_print_buff null.}");
        return;
    }
    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_show_blacklist_info::pst_hmac_vap null.}");
        OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

        return;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 3.1 黑名单模式信息 */
    if (CS_BLACKLIST_MODE_BLACK == pst_blacklist_info->uc_mode)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> BLACKLIST[BLACK] num=%d info:}",pst_blacklist_info->uc_list_num);
        buff_index = OAL_SPRINTF(pc_print_buff,OAM_REPORT_MAX_STRING_LEN,"BLACKLIST[BLACK] num=%d info:\n",pst_blacklist_info->uc_list_num);
    }
    else if(CS_BLACKLIST_MODE_WHITE == pst_blacklist_info->uc_mode)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> BLACKLIST[WHITE] num=%d info:}",pst_blacklist_info->uc_list_num);
        buff_index = OAL_SPRINTF(pc_print_buff,OAM_REPORT_MAX_STRING_LEN,"BLACKLIST[WHITE] num=%d info:\n",pst_blacklist_info->uc_list_num);
    }
    else
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> BLACKLIST not enable! num=%d info:}",pst_blacklist_info->uc_list_num);
        buff_index = OAL_SPRINTF(pc_print_buff,OAM_REPORT_MAX_STRING_LEN,"BLACKLIST not enable! num=%d info:\n",pst_blacklist_info->uc_list_num);
    }

    /* 5.1 打印黑名单表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
        pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
        if (hmac_blacklist_mac_is_zero(pst_blacklist->auc_mac_addr))
        {
            continue;
        }
        puc_sa = pst_blacklist->auc_mac_addr;
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{src mac=%02X:XX:XX:%02X:%02X:%02X}",puc_sa[0],puc_sa[3],puc_sa[4],puc_sa[5]);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{ CFG_TIME: %u. AGE_TIME: %u. DROP_CNT: %u.}",
            pst_blacklist->ul_cfg_time,pst_blacklist->ul_aging_time,pst_blacklist->ul_drop_counter);

        buff_index += OAL_SPRINTF(pc_print_buff+buff_index,(OAM_REPORT_MAX_STRING_LEN-buff_index),
            "\n[%02d] MAC: %02X:XX:XX:%02X:%02X:%02X\n"
            " CFG_TIME: %u\t AGE_TIME: %u\t DROP_CNT: %u\n",
            ul_blacklist_index,
            pst_blacklist->auc_mac_addr[0],
            pst_blacklist->auc_mac_addr[3],
            pst_blacklist->auc_mac_addr[4],
            pst_blacklist->auc_mac_addr[5],
            pst_blacklist->ul_cfg_time,pst_blacklist->ul_aging_time,pst_blacklist->ul_drop_counter);
    }
    oam_print(pc_print_buff);
    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

    /* 4.1 自动黑名单信息 */
    hmac_show_autoblacklist_info(&pst_blacklist_info->st_autoblacklist_info);

    /* 加入当前时间 */
    oal_time_get_stamp_us(&st_cur_time);
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{ CURR_TIME: %d}",(oal_uint32)st_cur_time.i_sec);

}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_enable
 功能描述  : 去/使能自动黑名单
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_autoblacklist_enable(mac_vap_stru *pst_mac_vap, oal_uint8 uc_enabled)
{
    mac_autoblacklist_info_stru   *pst_autoblacklist_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_autoblacklist_enable::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_autoblacklist_enable::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    /* 参数跟原有一样 */
    if (uc_enabled == pst_autoblacklist_info->uc_enabled)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{hmac_autoblacklist_enable:autoblacklist is already %d}",uc_enabled);

        return OAL_SUCC;
    }

    /* 重新初始化 */
    if (uc_enabled == 1)
    {
        hmac_blacklist_init(pst_mac_vap, CS_BLACKLIST_MODE_BLACK);
        pst_autoblacklist_info->uc_enabled    = uc_enabled;
        pst_autoblacklist_info->ul_aging_time = CS_DEFAULT_AGING_TIME;
        pst_autoblacklist_info->ul_reset_time = CS_DEFAULT_RESET_TIME;
        pst_autoblacklist_info->ul_threshold  = CS_DEFAULT_THRESHOLD;
    }
    else    /* 关闭自动黑名单，清零相关数据 */
    {
        hmac_blacklist_init(pst_mac_vap, CS_BLACKLIST_MODE_NONE);   /* 2013.7.23 add clean */
    }

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
        "{hmac_autoblacklist_enable:autoblacklist is %d}",uc_enabled);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_set_aging
 功能描述  : 去/使能自动黑名单
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_autoblacklist_set_aging(mac_vap_stru *pst_mac_vap, oal_uint32 ul_aging_time)
{
    mac_autoblacklist_info_stru   *pst_autoblacklist_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_autoblacklist_set_aging::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    if (ul_aging_time == 0)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{ul_aging_time should not be 0}");
        return OAL_ERR_CODE_SECURITY_AGING_INVALID;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_autoblacklist_set_aging::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    /* 3.1 自动黑名单没有使能 */
    if (0 == pst_autoblacklist_info->uc_enabled)
    {
        hmac_autoblacklist_enable(pst_mac_vap, 1);
    }

    /* 4.1 更新老化时间 */
    pst_autoblacklist_info->ul_aging_time = ul_aging_time;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{blacklist set auto aging = %d}",ul_aging_time);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_set_threshold
 功能描述  : 去/使能自动黑名单
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_autoblacklist_set_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_threshold)
{
    mac_autoblacklist_info_stru   *pst_autoblacklist_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_autoblacklist_set_threshold::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    if (ul_threshold == 0)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{ul_threshold should not be 0}");
        return OAL_ERR_CODE_SECURITY_THRESHOLD_INVALID;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_autoblacklist_set_threshold::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    /* 3.1 自动黑名单没有使能 */
    if (0 == pst_autoblacklist_info->uc_enabled)
    {
        hmac_autoblacklist_enable(pst_mac_vap, 1);
    }

    /* 4.1 更新门限 */
    pst_autoblacklist_info->ul_threshold = ul_threshold;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{blacklist set auto threshold = %d}",ul_threshold);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_set_reset_time
 功能描述  : 去/使能自动黑名单
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_autoblacklist_set_reset_time(mac_vap_stru *pst_mac_vap, oal_uint32 ul_reset_time)
{
    mac_autoblacklist_info_stru   *pst_autoblacklist_info;
    hmac_vap_stru                  *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_autoblacklist_set_reset_time::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    if (ul_reset_time == 0)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{ul_aging_time should not be 0}");
        return OAL_ERR_CODE_SECURITY_RESETIME_INVALID;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_autoblacklist_set_reset_time::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    /* 3.1 自动黑名单没有使能 */
    if (0 == pst_autoblacklist_info->uc_enabled)
    {
        hmac_autoblacklist_enable(pst_mac_vap, 1);
    }

    /* 4.1 更新重置时间 */
    pst_autoblacklist_info->ul_reset_time = ul_reset_time;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{blacklist set auto reset_time = %d}", ul_reset_time);
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_isolation_set_mode
 功能描述  : 设置隔离模式
 输入参数  : uc_mode bit0 = 1 广播 bit1 = 1 组播 bit2 = 1 单播
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mode)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_set_mode::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    uc_mode = uc_mode & 0x7;
    if (0 == uc_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_isolation_set_mode invalid, The valid Para is:(1~7)}\n");
        /* add mode check  2014.7.7 */
        return OAL_ERR_CODE_SECURITY_MODE_INVALID;
    }

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;


    /* 3.1 重新初始化 */
    pst_isolation_info->uc_mode = uc_mode;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> isolation mode is set to %d}", uc_mode);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_set_type
 功能描述  : 设置隔离类型
 输入参数  :
 输出参数  : CS_ISOLATION_TYPE_MULTI_BSS CS_ISOLATION_TYPE_SINGLE_BSS
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_set_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_type)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_set_type::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    if (uc_type >= CS_ISOLATION_TYPE_BUTT)
    {
        uc_type = CS_ISOLATION_TYPE_NONE;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;


    /* 3.1 重新初始化 */
    pst_isolation_info->uc_type = uc_type;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> isolation type is set to %d}", uc_type);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_set_forword
 功能描述  : 设置隔离forword方式
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_set_forward(mac_vap_stru *pst_mac_vap, oal_uint8 uc_forward)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_set_forward::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 2.1 获取参数 */
    if (uc_forward >= CS_ISOLATION_FORWORD_BUTT)
    {
        uc_forward = CS_ISOLATION_FORWORD_TOLAN;
    }

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;
    pst_isolation_info->uc_forward = uc_forward;
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> isolation forward is set to %d}", uc_forward);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_isolation_clear_counter
 功能描述  : 去/使能自动黑名单
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_clear_counter(mac_vap_stru *pst_mac_vap)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_clear_counter::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_isolation_clear_counter::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;

    /* 2.1 刷新计数器 */
    pst_isolation_info->ul_counter_bcast = 0;
    pst_isolation_info->ul_counter_mcast = 0;
    pst_isolation_info->ul_counter_ucast = 0;

    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{isolation counters is cleared }");
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_get_bcast_counter
 功能描述  : 获取隔离了多少广播包
 输入参数  :
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_get_bcast_counter(mac_vap_stru *pst_mac_vap)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_get_bcast_counter::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_isolation_get_bcast_counter::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_isolation_info = &pst_hmac_vap->st_isolation_info;
    return pst_isolation_info->ul_counter_bcast;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_get_mcast_counter
 功能描述  : 获取隔离了多少组播包
 输入参数  :
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_get_mcast_counter(mac_vap_stru *pst_mac_vap)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_get_mcast_counter::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_blacklist_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_isolation_info = &pst_hmac_vap->st_isolation_info;
    return pst_isolation_info->ul_counter_mcast;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_get_ucast_counter
 功能描述  : 获取隔离了多少单播包
 输入参数  :
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_isolation_get_ucast_counter(mac_vap_stru *pst_mac_vap)
{
    mac_isolation_info_stru       *pst_isolation_info;
    hmac_vap_stru                 *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_get_ucast_counter::null mac_vap}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_isolation_get_ucast_counter::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_isolation_info = &pst_hmac_vap->st_isolation_info;
    return pst_isolation_info->ul_counter_ucast;
}

/*****************************************************************************
 函 数 名  : hmac_show_isolation_info
 功能描述  : 显示隔离信息
 输入参数  :
 输出参数  : oal_void
 返 回 值  : null
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_show_isolation_info(mac_vap_stru *pst_mac_vap)
{
    mac_isolation_info_stru         *pst_isolation_info;
    oal_int8                        *pc_print_buff;
    hmac_vap_stru                   *pst_hmac_vap;

    /* 1.1 入参检查 */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_show_isolation_info::null mac_vap}");
        return;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_show_isolation_info::pst_hmac_vap null.}");
        return;
    }

    pc_print_buff = (oal_int8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAM_REPORT_MAX_STRING_LEN, OAL_TRUE);
    if (OAL_PTR_NULL == pc_print_buff)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{hmac_show_autoblacklist_info::pc_print_buff null.}");
        return;
    }
    OAL_MEMZERO(pc_print_buff, OAM_REPORT_MAX_STRING_LEN);

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;

    /* 1.2 打印隔离信息 */
    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{>>>>>> isolation info is :}");
    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{ mode:%d. type:%d. forward:%d.}",
        pst_isolation_info->uc_mode,pst_isolation_info->uc_type,pst_isolation_info->uc_forward);
    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{ bcast_cnt: %u.mcast_cnt: %u.ucast_cnt: %u.}",
        pst_isolation_info->ul_counter_bcast,pst_isolation_info->ul_counter_mcast,pst_isolation_info->ul_counter_ucast);

    OAL_SPRINTF(pc_print_buff,OAM_REPORT_MAX_STRING_LEN,
            "vap%d isolation info is :\n"
            "\tmode:%d. type:%d. forward:%d.\n"
            "\tbcast_cnt: %u\n"
            "\tmcast_cnt: %u\n"
            "\tucast_cnt: %u\n",
            pst_mac_vap->uc_vap_id,
            pst_isolation_info->uc_mode,pst_isolation_info->uc_type,
            pst_isolation_info->uc_forward,
            pst_isolation_info->ul_counter_bcast,
            pst_isolation_info->ul_counter_mcast,
            pst_isolation_info->ul_counter_ucast);

    oam_print(pc_print_buff);
    OAL_MEM_FREE(pc_print_buff, OAL_TRUE);

    return;

}

/*****************************************************************************
 函 数 名  : hmac_blacklist_filter
 功能描述  : 黑名单过滤
 输入参数  : mac地址
 输出参数  : oal_void
 返 回 值  : OAL_TRUE 需要被过滤; OAL_FALSE 不需要被过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_blacklist_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    mac_blacklist_stru           *pst_blacklist;
    hmac_vap_stru                *pst_hmac_vap;
    mac_blacklist_info_stru      *pst_blacklist_info;
    oal_uint32                    ul_ret;
    oal_bool_enum_uint8           b_ret;

    /* 1.1 入参检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_mac_addr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_blacklist_filter::null mac_vap or null mac addr}");
        return OAL_FALSE;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            "{hmac_blacklist_filter::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_blacklist_info = &pst_hmac_vap->st_blacklist_info;

    /* 1.1 功能没有开启，不需要过滤 */
    if (CS_BLACKLIST_MODE_NONE == pst_blacklist_info->uc_mode)
    {
        return OAL_FALSE;
    }

    /* 2.1 黑名单模式下 */
    if (CS_BLACKLIST_MODE_BLACK == pst_blacklist_info->uc_mode)
    {
        ul_ret = hmac_blacklist_get(pst_mac_vap, puc_mac_addr, &pst_blacklist);
        /* 表示puc_mac_addr地址为广播地址或者全零地址, 不过滤 */
        if (OAL_SUCC != ul_ret)
        {
            return OAL_FALSE;
        }
        /* 2.2 如果找不到表单，不需要过滤 */
        if (OAL_PTR_NULL == pst_blacklist)
        {
            return OAL_FALSE;
        }

        /* 2.3 老化时间到了，不需要过滤 */
        b_ret = hmac_blacklist_is_aged(pst_mac_vap, pst_blacklist);
        if (OAL_TRUE == b_ret)
        {
            return OAL_FALSE;
        }
        /* 2.4 其他情况下都需要过滤 */
        pst_blacklist->ul_drop_counter++;
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{hmac_blacklist_filter::blacklist_filter drop_counter = %d MAC:=x.x.x.%02x.%02x.%02x}",
            pst_blacklist->ul_drop_counter,puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);

        return OAL_TRUE;
    }

    /* 3.1 白名单模式下 */
    if (CS_BLACKLIST_MODE_WHITE == pst_blacklist_info->uc_mode)
    {
        ul_ret = hmac_blacklist_get(pst_mac_vap, puc_mac_addr, &pst_blacklist);
        /* 表示puc_mac_addr地址为广播地址或者全零地址, 不过滤 */
        if (OAL_SUCC != ul_ret)
        {
            return OAL_FALSE;
        }
        /* 3.2 如果找不到表单，需要过滤 */
        if (OAL_PTR_NULL == pst_blacklist)
        {
            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                "{hmac_blacklist_filter::whitelist_filter MAC:=%02X:XX:XX:%02X:%02X:%02X}",
                puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);
            return OAL_TRUE;
        }

        /* 3.3 老化时间到了，不需要过滤 */
        b_ret = hmac_blacklist_is_aged(pst_mac_vap, pst_blacklist);
        if (OAL_TRUE == b_ret)
        {
            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                "{hmac_blacklist_filter::aging reach. go through=%02X:XX:XX:%02X:%02X:%02X}",
                puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);
            return OAL_FALSE;
        }

        /* 3.4 老化时间没有到，需要过滤 */
        if (0 != pst_blacklist->ul_aging_time)
        {
            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                "{hmac_blacklist_filter::aging not zero; whilte_filter MAC=%02X:XX:XX:%02X:%02X:%02X}",
                puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);

            return OAL_TRUE;
        }
    }

    /* 不满足黑白名单过滤条件的，均不需要过滤 */
    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_autoblacklist_filter
 功能描述  : 黑名单过滤
 输入参数  : mac地址
 输出参数  : oal_void
 返 回 值  : OAL_TRUE 需要被过滤; OAL_FALSE 不需要被过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_autoblacklist_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    mac_autoblacklist_stru           *pst_autoblacklist = OAL_PTR_NULL;	/* 添加初始化值，便于做UT打桩后此值是null */
    mac_autoblacklist_info_stru      *pst_autoblacklist_info;
    oal_uint32                        ul_ret;
    hmac_vap_stru                    *pst_hmac_vap;
    mac_blacklist_stru               *pst_blacklist = OAL_PTR_NULL;

    /* 1.1 入参检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_mac_addr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_autoblacklist_filter::null mac_vap or null mac addr}");
        return;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_autoblacklist_filter::pst_hmac_vap null.}");
        return;
    }

    pst_autoblacklist_info = &pst_hmac_vap->st_blacklist_info.st_autoblacklist_info;

    /* 1.1 功能没有开启 */
    if (0 == pst_autoblacklist_info->uc_enabled)
    {
        return;
    }

    /* 1.2 检查是否已经在黑名单中, 若在黑名单中，直接返回 */
    hmac_blacklist_get(pst_mac_vap, puc_mac_addr, &pst_blacklist);
    if (OAL_PTR_NULL != pst_blacklist)
    {
        return;
    }

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> auto_filter MAC:=%02X:XX:XX:%02X:%02X:%02X}",
            puc_mac_addr[0],puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);

    /* 2.1 找到关联请求统计表单  */
    ul_ret = hmac_autoblacklist_get(pst_mac_vap, puc_mac_addr, &pst_autoblacklist);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_autoblacklist_get failed %d}", ul_ret);
        return;
    }
    /* 2.2 如果找不到表单，不处理 */
    if (OAL_PTR_NULL == pst_autoblacklist)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{Can't find item to add}");
        return;
    }

    /* 3.1 关联计数器判断 */
    if (++pst_autoblacklist->ul_asso_counter > pst_autoblacklist_info->ul_threshold)
    {
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "{>>>>>> autoblacklist_filter: asso_counter=%d. threshold=%d. add to blacklist}",
            pst_autoblacklist->ul_asso_counter,pst_autoblacklist_info->ul_threshold);
        ul_ret = hmac_blacklist_add(pst_mac_vap, puc_mac_addr, pst_autoblacklist_info->ul_aging_time);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_blacklist_add failed %d}", ul_ret);
            return;
        }
        /* 3.2 删除统计表单*/
        oal_memset(pst_autoblacklist, 0, OAL_SIZEOF(mac_autoblacklist_stru));
        if(pst_autoblacklist_info->list_num > 0)
        {
            pst_autoblacklist_info->list_num--;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : hmac_isolation_filter
 功能描述  : 用户隔离过滤
 输入参数  : mac地址
 输出参数  : oal_void
 返 回 值  : OAL_TRUE 需要被过滤; OAL_FALSE 不需要被过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
cs_isolation_forward_enum hmac_isolation_filter(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    mac_isolation_info_stru      *pst_isolation_info;
    oal_uint32                    ul_ret;
    mac_user_stru                *pst_mac_user;
    hmac_vap_stru                *pst_hmac_vap;
    oal_uint16                    us_user_idx;
    /* 1.1 入参检查 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_mac_addr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_isolation_filter::null mac_vap or null mac addr}");
        return CS_ISOLATION_FORWORD_NONE;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_isolation_filter::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_isolation_info = &pst_hmac_vap->st_isolation_info;

    /* (默认)没有开启用户隔离功能，返回*/
    if (CS_ISOLATION_TYPE_NONE == pst_isolation_info->uc_type)
    {
        return CS_ISOLATION_FORWORD_NONE;
    }

    /* 1.1 多BSS隔离 */
    if (CS_ISOLATION_TYPE_MULTI_BSS == pst_isolation_info->uc_type)
    {
        /* 1.2 广播隔离 */
        if (ETHER_IS_BROADCAST(puc_mac_addr))
        {
            if (BROADCAST_ISOLATION(pst_isolation_info->uc_mode))
            {
                pst_isolation_info->ul_counter_bcast++;
                OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation MultiBSS Bcast=%d}", pst_isolation_info->ul_counter_bcast);
                return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
            }
            return CS_ISOLATION_FORWORD_NONE;
        }
        /* 1.3 组播隔离 */
        if (ETHER_IS_MULTICAST(puc_mac_addr))
        {
            if (MULTICAST_ISOLATION(pst_isolation_info->uc_mode))
            {
                pst_isolation_info->ul_counter_mcast++;
                OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation MultiBSS Mcast=%d}", pst_isolation_info->ul_counter_mcast);
                return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
            }
            return CS_ISOLATION_FORWORD_NONE;
        }
        /* 2.4 单播隔离,如果在本bss中找到用户，不隔离处理，否则需要在其他bss中找，找到就隔离 */
        if (UNICAST_ISOLATION(pst_isolation_info->uc_mode))
        {
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
            if (OAL_SUCC == ul_ret)
            {
                /* return CS_ISOLATION_FORWORD_NONE; 2014.9.20 多BSS隔离,同BSS也需要隔离 */
                return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
            }

            ul_ret = mac_device_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                return CS_ISOLATION_FORWORD_NONE;
            }
            pst_mac_user = mac_res_get_mac_user(us_user_idx);
            if (OAL_PTR_NULL == pst_mac_user)
            {
                return CS_ISOLATION_FORWORD_NONE;
            }
            pst_isolation_info->ul_counter_ucast++;
            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation MultiBSS Ucast=%d. to x.x.x.%02x.%02x.%02x}",
                    pst_isolation_info->ul_counter_ucast,puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);


            return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;

        }

        return CS_ISOLATION_FORWORD_NONE;
    }

    /* 2.1 单BSS隔离 */
    if (CS_ISOLATION_TYPE_SINGLE_BSS == pst_isolation_info->uc_type)
    {
        /* 2.2 广播隔离 */
        if (ETHER_IS_BROADCAST(puc_mac_addr))
        {
            if (BROADCAST_ISOLATION(pst_isolation_info->uc_mode))
            {
                pst_isolation_info->ul_counter_bcast++;
                OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation SingleBSS Bcast=%d}", pst_isolation_info->ul_counter_bcast);
                return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
            }
            return CS_ISOLATION_FORWORD_NONE;
        }
        /* 2.3 组播隔离 */
        if (ETHER_IS_MULTICAST(puc_mac_addr))
        {
            if (MULTICAST_ISOLATION(pst_isolation_info->uc_mode))
            {
                pst_isolation_info->ul_counter_mcast++;
                OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation SingleBSS Mcast=%d}", pst_isolation_info->ul_counter_mcast);
                return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
            }
            return CS_ISOLATION_FORWORD_NONE;
        }
        /* 2.4 单播隔离，如果在本bss中找到用户就隔离，否则不处理 */
        if (UNICAST_ISOLATION(pst_isolation_info->uc_mode))
        {
            ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                return CS_ISOLATION_FORWORD_NONE;
            }

            pst_mac_user = mac_res_get_mac_user(us_user_idx);
            if (OAL_PTR_NULL == pst_mac_user)
            {
                return CS_ISOLATION_FORWORD_NONE;
            }
            pst_isolation_info->ul_counter_ucast++;

            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                    "{>>>>>>isolation SingleBSS Ucast=%d. to x.x.x.%02x.%02x.%02x}",
                    pst_isolation_info->ul_counter_ucast,puc_mac_addr[3],puc_mac_addr[4],puc_mac_addr[5]);

            return (cs_isolation_forward_enum)pst_isolation_info->uc_forward;
        }
    }

    return CS_ISOLATION_FORWORD_NONE;
}

/*****************************************************************************
 函 数 名  : add_new_line_to_string_end
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/*OAL_INLINE  oal_uint16 add_new_line_to_string_end(oal_uint8 *pst_info_str)
{
    oal_uint16  str_idex;

    str_idex = OAL_STRLEN(pst_info_str);
    pst_info_str[str_idex]='\r';
    pst_info_str[str_idex+1]='\n';
    pst_info_str[str_idex+2]='\0';
    //str_idex = OAL_STRLEN(pst_info_str);
    return str_idex+2;
}*/

#if 0
/*****************************************************************************
 函 数 名  : hmac_config_get_blacklist
 功能描述  : 获取全部黑白名单信息
 输入参数  :
 输出参数  :
 返 回 值  : 信息字符串指针
 调用函数  :
 被调函数  : called by iwpriv

 修改历史      :
  1.日    期   : 2014年7月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_config_get_blacklist(mac_vap_stru *pst_mac_vap,oal_uint8 *pst_info_str,oal_int16 str_len)
{
    oal_int16                    strlen,str_idex,str_len_left;
    oal_uint8                    ul_blacklist_index;
    mac_blacklist_stru           *pst_blacklist;
    mac_autoblacklist_stru       *pst_autoblacklist_item;
    mac_blacklist_info_stru      *pst_blacklist_info;
    mac_autoblacklist_info_stru  *pst_autoblacklist_info;
    oal_time_us_stru              st_cur_time;

    str_len_left = str_len;
    pst_blacklist_info = &pst_mac_vap->st_blacklist_info;
    pst_autoblacklist_info = &pst_mac_vap->st_blacklist_info.st_autoblacklist_info;

    if (CS_BLACKLIST_MODE_BLACK == pst_blacklist_info->uc_mode)
    {
        str_idex = OAL_SPRINTF(pst_info_str,str_len_left,"\nBlacklist[BLACK] info:\n");
    }
    else if(CS_BLACKLIST_MODE_WHITE == pst_blacklist_info->uc_mode)
    {
        str_idex = OAL_SPRINTF(pst_info_str,str_len_left,"\nBlacklist[WHITE] info:\n");
    }
    else
    {
        str_idex = OAL_SPRINTF(pst_info_str,str_len_left,"\nBlacklist not enable! info:\n");
    }

    str_len_left -= str_idex;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\tblacklist mode[black:1; white:2] is : %d\n",pst_blacklist_info->uc_mode);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\tblacklist num is : %d\n",pst_blacklist_info->uc_list_num);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    /*  黑名单表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_BLACKLIST_MAX; ul_blacklist_index++)
    {
            pst_blacklist = &pst_blacklist_info->ast_black_list[ul_blacklist_index];
            if (hmac_blacklist_mac_is_zero(pst_blacklist->auc_mac_addr))
            {
                /*strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\t[%02d] MAC:0. left=%d\n",ul_blacklist_index,str_len_left);*/
                strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,".");
                str_idex += strlen;
                str_len_left -= strlen;
                if(str_len_left <= 0) return;

                continue;
            }
            strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\n\t[%02d] MAC: %02X:XX:XX:%02X:%02X:%02X. left=%d\n",
                ul_blacklist_index,
                pst_blacklist->auc_mac_addr[0],
                pst_blacklist->auc_mac_addr[3],
                pst_blacklist->auc_mac_addr[4],
                pst_blacklist->auc_mac_addr[5],
                ,str_len_left);
            str_idex += strlen;
            str_len_left -= strlen;
            if(str_len_left <= 0) return;

            strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\tCFG_TIME:%d. AGE_TIME:%d. DROP_CNT:%d\n\n",
                pst_blacklist->ul_cfg_time,pst_blacklist->ul_aging_time,pst_blacklist->ul_drop_counter);
            str_idex += strlen;
            str_len_left -= strlen;
            if(str_len_left <= 0) return;

    }

    /*  自动黑名单信息 */
    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\nAUTOBLACKLIST INFO : enable=%d. list_num=%d. left=%d\n",
        pst_autoblacklist_info->uc_enabled,pst_autoblacklist_info->list_num,str_len_left);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\tenable=%d\n",pst_autoblacklist_info->uc_enabled);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\taging=%d\n",pst_autoblacklist_info->ul_aging_time);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\treset=%d\n",pst_autoblacklist_info->ul_reset_time);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\tthreshold=%d\n",pst_autoblacklist_info->ul_threshold);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    /*  自动黑名单表单 */
    for (ul_blacklist_index = 0; ul_blacklist_index < WLAN_ASSOC_USER_MAX_NUM_SPEC; ul_blacklist_index++)
    {
            pst_autoblacklist_item = &pst_blacklist_info->st_autoblacklist_info.ast_autoblack_list[ul_blacklist_index];
            if (hmac_blacklist_mac_is_zero(pst_autoblacklist_item->auc_mac_addr))
            {
                /*strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\t[%02d] MAC:0. left=%d\n",ul_blacklist_index,str_len_left);*/
                strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,".");
                str_idex += strlen;
                str_len_left -= strlen;
                if(str_len_left <= 0) return;

                continue;
            }
            strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,
                "\n\t[%02d] MAC: %02X:XX:XX:%02X:%02X:%02X.cfg_time=%d.asso_cnt=%d.left=%d\n",
                ul_blacklist_index,
                pst_autoblacklist_item->auc_mac_addr[0],
                pst_autoblacklist_item->auc_mac_addr[3],
                pst_autoblacklist_item->auc_mac_addr[4],
                pst_autoblacklist_item->auc_mac_addr[5],
                pst_autoblacklist_item->ul_cfg_time,pst_autoblacklist_item->ul_asso_counter,str_len_left);
            str_idex += strlen;
            str_len_left -= strlen;
            if(str_len_left <= 0) return;
    }

    oal_time_get_stamp_us(&st_cur_time);
    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\ntotal str_len=%d. curr_time=%d\n",
        str_idex,(oal_uint32)st_cur_time.i_sec);

    oam_print(pst_info_str);    /* Add log to SDT */

    return;

}

/*****************************************************************************
 函 数 名  : hmac_config_get_isolation
 功能描述  : 获取隔离相关信息
 输入参数  :
 输出参数  :
 返 回 值  : 信息字符串指针
 调用函数  :
 被调函数  : called by iwpriv

 修改历史      :
  1.日    期   : 2014年7月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_config_get_isolation(mac_vap_stru *pst_mac_vap,oal_uint8 *pst_info_str,oal_int16 str_len)
{
    oal_int16                    strlen,str_idex;
    oal_int16                    str_len_left;
    mac_isolation_info_stru      *pst_isolation_info;
    oal_time_us_stru             st_cur_time;

    str_len_left = str_len;
    pst_isolation_info = &pst_mac_vap->st_isolation_info;

    str_idex = OAL_SPRINTF(pst_info_str,str_len_left,"isolation type = %d; mode = 0x%x; forward = %d\n"
        "\t[type multi:1; sigle:2] [mode bcast:1; mcast:2; ucast:4] [forward tolan:1; drop:2]",
        pst_isolation_info->uc_type,pst_isolation_info->uc_mode,pst_isolation_info->uc_forward);
    str_len_left -= str_idex;
    if(str_len_left <= 0) return;

    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,
        "\tisolation counter_bcast=%d\n" "  mcast=%d\n" "  ucast=%d\n",
        pst_isolation_info->ul_counter_bcast,pst_isolation_info->ul_counter_mcast,pst_isolation_info->ul_counter_ucast);
    str_idex += strlen;
    str_len_left -= strlen;
    if(str_len_left <= 0) return;

    oal_time_get_stamp_us(&st_cur_time);
    strlen = OAL_SPRINTF(pst_info_str + str_idex,str_len_left,"\ntotal str_len=%d. curr_time=%d\n",
        str_idex,(oal_uint32)st_cur_time.i_sec);

    oam_print(pst_info_str);    /* Add log to SDT */

    return;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_config_get_blacklist);
oal_module_symbol(hmac_config_get_isolation);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif	/* #ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY */




