/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_backup.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年8月17日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2016年8月17日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
#include "hmac_backup.h"
#include "hmac_device.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_BACKUP_C

/*****************************************************************************
 函 数 名  : hmac_backup_user
 功能描述  : 向备份列表中添加备份用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_user(hmac_user_stru *pst_hmac_user, oal_uint32 ul_user_num, oal_uint32 ul_cur_index)
{
    data_summary_info  st_info;
    oal_int32          l_ret;

    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_user::pst_hmac_user is null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = pst_hmac_user;
    st_info.ul_value_length        = OAL_SIZEOF(hmac_user_stru);
    st_info.st_head.en_data_type   = TYPE_LIST;
    st_info.st_head.ul_list_numer  = ul_user_num;
    st_info.st_head.ul_cur_number  = ul_cur_index;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "user", MAX_DATA_NAME_LEN);

    l_ret =g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_user::backup user fail!");
        return l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_backup_all_user
 功能描述  : 向备份列表中添加所有备份用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_all_user(oal_void)
{
    oal_uint8         uc_max_num;
    hmac_user_stru   *pst_user;
    oal_uint8         uc_index;
    oal_int32         l_ret;
    oal_uint32        ul_user_num  = 0;
    oal_uint32        ul_cur_index = 0;
    data_summary_info st_info;

    /* 最大支持的user资源个数 */
    uc_max_num = g_st_mac_res.st_user_res.st_queue.uc_max_elements;

    /* 统计当前需要备份的user个数,组播用户不统计 */
    for(uc_index = 0; uc_index < uc_max_num; uc_index++)
    {
        if (0 != g_st_mac_res.st_user_res.puc_user_cnt[uc_index])
        {
            pst_user = (hmac_user_stru *)&(g_st_mac_res.st_user_res.pst_user_info[uc_index]);
            if (OAL_PTR_NULL == pst_user)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::pst_user is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if (OAL_FALSE == pst_user->st_user_base_info.en_is_multi_user)
            {
                ul_user_num++;
            }
        }
    }
    for(uc_index = 0; uc_index < uc_max_num; uc_index++)
    {
        if (0 != g_st_mac_res.st_user_res.puc_user_cnt[uc_index])
        {
            pst_user = (hmac_user_stru *)&(g_st_mac_res.st_user_res.pst_user_info[uc_index]);
            if (OAL_PTR_NULL == pst_user)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::pst_user is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if (OAL_FALSE == pst_user->st_user_base_info.en_is_multi_user)
            {
                l_ret = hmac_backup_user(pst_user, ul_user_num, ul_cur_index);
                if (OAL_SUCC != l_ret)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::backup user fail!");
                    return l_ret;
                }
                ul_cur_index++;
            }
        }
    }

    /* 备份user资源池的puc_user_cnt信息 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = g_st_mac_res.st_user_res.puc_user_cnt;
    st_info.ul_value_length        = uc_max_num;
    st_info.st_head.en_data_type   = TYPE_BASE_DATA_TYPE;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "user_flag", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::backup puc_user_cnt fail!");
        return l_ret;
    }
    /* 备份user资源池的queue */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = &g_st_mac_res.st_user_res.st_queue;
    st_info.ul_value_length        = OAL_SIZEOF(oal_queue_stru);
    st_info.st_head.en_data_type   = TYPE_STRUCT;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "user_queue", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::backup puc_user_cnt fail!");
        return l_ret;
    }
    /* 备份user资源池的queue的pul_buf */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = g_st_mac_res.st_user_res.st_queue.pul_buf;
    st_info.ul_value_length        = OAL_SIZEOF(oal_uint) * uc_max_num;
    st_info.st_head.en_data_type   = TYPE_BASE_DATA_TYPE;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "user_queue_buf", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_user::backup puc_user_cnt fail!");
        return l_ret;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_user
 功能描述  : 恢复备份的user信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_user(data_summary_info *pst_user_info)
{
    hmac_user_stru    *pst_hmac_user;
    mac_user_stru     *pst_mac_user;
    hmac_vap_stru     *pst_hmac_vap;
    mac_vap_stru      *pst_mac_vap;
    oal_uint8          uc_index;
    oal_int32          l_ret;

    if (OAL_PTR_NULL == pst_user_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_user_info is null!");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 只考虑一个vap的情况 */
    for(uc_index = 0; uc_index < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_index++)
    {
        if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[uc_index])
        {
            pst_hmac_vap = (hmac_vap_stru *)&g_st_mac_res.st_vap_res.ast_vap_info[uc_index];
            if (OAL_PTR_NULL == pst_hmac_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_hmac_vap is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_recover_user::pst_mac_vap is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
                || (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode))
            {
                break;
            }
        }
    }
    /* 恢复user信息 */
    pst_hmac_user = (hmac_user_stru *)pst_user_info->ul_value_address;
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_hmac_user is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user  = &(pst_hmac_user->st_user_base_info);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_mac_user is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&g_st_mac_res.st_user_res.pst_user_info[pst_mac_user->us_assoc_id], pst_hmac_user, OAL_SIZEOF(hmac_user_stru));
    pst_hmac_user = &g_st_mac_res.st_user_res.pst_user_info[pst_mac_user->us_assoc_id];
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_hmac_user is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user  = &(pst_hmac_user->st_user_base_info);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_user::pst_mac_user is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* hmac_user数据的维护 */
    hmac_user_init(pst_hmac_user);
    /* 设置amsdu域 */
    hmac_amsdu_init_user(pst_hmac_user);
    /* mac_user数据的维护 */
    pst_mac_user->uc_vap_id = pst_mac_vap->uc_vap_id;
    OAL_MEMZERO(&pst_hmac_user->st_mgmt_timer, OAL_SIZEOF(frw_timeout_stru));
    /* 添加用户到MAC VAP,维护链表关系 */
    l_ret = mac_vap_add_assoc_user(pst_mac_vap, pst_mac_user->us_assoc_id);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_BACKUP, "{hmac_recover_user::mac_vap_add_assoc_user failed[%d].}", l_ret);

        /* 异常处理，释放内存，device下关联用户数还没有++，这里不需要判断返回值做--操作 */
        hmac_user_free(pst_mac_user->us_assoc_id);
        return OAL_FAIL;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_all_user
 功能描述  : 恢复所有备份的user信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_all_user(oal_void)
{
    data_summary_info *pst_info;
    oal_uint32        *pul_buf;
    oal_uint32         ul_user_num;
    oal_uint32         ul_index;
    oal_int32          l_ret;

    /* 恢复user资源池的puc_user_cnt信息 */
    pst_info = g_st_data_process_interface.get_info_by_name_cb("user_flag");
    if (OAL_PTR_NULL == pst_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::pst_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_info->ul_value_address)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BACKUP, "hmac_recover_all_user::ul_value_address = %x",pst_info->ul_value_address);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(g_st_mac_res.st_user_res.puc_user_cnt, pst_info->ul_value_address, pst_info->ul_value_length);
    /* 恢复user资源池的queue */
    pul_buf  = g_st_mac_res.st_user_res.st_queue.pul_buf;
    pst_info = g_st_data_process_interface.get_info_by_name_cb("user_queue");
    if (OAL_PTR_NULL == pst_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::pst_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_PTR_NULL == pst_info->ul_value_address)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BACKUP, "hmac_recover_all_user::ul_value_address = %x",pst_info->ul_value_address);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&(g_st_mac_res.st_user_res.st_queue), pst_info->ul_value_address, OAL_SIZEOF(oal_queue_stru));
    g_st_mac_res.st_user_res.st_queue.pul_buf = pul_buf;
    /* 恢复user资源池的queue的pul_buf */
    pst_info = g_st_data_process_interface.get_info_by_name_cb("user_queue_buf");
    if (OAL_PTR_NULL == pst_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::pst_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_info->ul_value_address)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BACKUP, "hmac_recover_all_user::ul_value_address = %x",pst_info->ul_value_address);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(g_st_mac_res.st_user_res.st_queue.pul_buf, pst_info->ul_value_address, pst_info->ul_value_length);
    /* 恢复user信息 */
    pst_info = g_st_data_process_interface.get_list_info_cb("user", 0);
    if (OAL_PTR_NULL == pst_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::pst_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    l_ret   = hmac_recover_user(pst_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::recover user fail!");
        return l_ret;
    }

    ul_user_num = pst_info->st_head.ul_list_numer;
    OAM_WARNING_LOG1(0, OAM_SF_BACKUP, "hmac_recover_all_user::recover user %d",ul_user_num);

    for(ul_index = 1; ul_index < ul_user_num; ul_index++)
    {
        pst_info = g_st_data_process_interface.get_list_info_cb("user", ul_index);
        if (OAL_PTR_NULL == pst_info)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::pst_info is null");
            return OAL_ERR_CODE_PTR_NULL;
        }

        l_ret   = hmac_recover_user(pst_info);
        if (OAL_SUCC != l_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_user::recover user fail!");
            return l_ret;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_backup_vap
 功能描述  : 向备份列表中添加vap
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_vap(hmac_vap_stru *pst_hmac_vap, oal_uint32 ul_vap_num, oal_uint32 ul_cur_index)
{
    oal_uint8          uc_index;
    oal_int32          l_ret;
    data_summary_info  st_info;
    oal_uint32         ul_ie_num   = 0;
    oal_uint32         ul_ie_index = 0;
    mac_vap_stru      *pst_mac_vap;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_vap::pst_hmac_vap is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 添加备份vap信息到备份表 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = pst_hmac_vap;
    st_info.ul_value_length        = OAL_SIZEOF(hmac_vap_stru);
    st_info.st_head.en_data_type   = TYPE_LIST;
    st_info.st_head.ul_list_numer  = ul_vap_num;
    st_info.st_head.ul_cur_number  = ul_cur_index;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "vap", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_vap::backup vap fail");
        return l_ret;
    }
    /* 备份mib信息 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = pst_hmac_vap->st_vap_base_info.pst_mib_info;
    st_info.ul_value_length        = OAL_SIZEOF(wlan_mib_ieee802dot11_stru);
    st_info.st_head.en_data_type   = TYPE_STRUCT;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "vap_mib", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_vap::backup vap_mib fail");
        return l_ret;
    }
    /* 备份vap下挂的app ie */
    /* 统计当前有多少ie信息 */
    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_vap::pst_mac_vap is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for(uc_index = 0; uc_index < OAL_APP_IE_NUM; uc_index++)
    {
        if (0 < pst_mac_vap->ast_app_ie[uc_index].ul_ie_len)
        {
            ul_ie_num++;
        }
    }
    for(uc_index = 0; uc_index < OAL_APP_IE_NUM; uc_index++)
    {
        if (0 < pst_mac_vap->ast_app_ie[uc_index].ul_ie_len)
        {
            OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
            st_info.ul_value_address       = pst_mac_vap->ast_app_ie[uc_index].puc_ie;
            st_info.ul_value_length        = pst_mac_vap->ast_app_ie[uc_index].ul_ie_len;
            st_info.st_head.en_data_type   = TYPE_LIST;
            st_info.st_head.ul_list_numer  = ul_ie_num;
            st_info.st_head.ul_cur_number  = ul_ie_index;
            st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
            oal_memcopy(st_info.st_head.ac_name, "app_ie", MAX_DATA_NAME_LEN);
            l_ret = g_st_data_process_interface.add_info_cb(&st_info);
            if (OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_vap::back vap fali!");
                return l_ret;
            }
            ul_ie_index++;
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_backup_all_vap
 功能描述  : 向备份列表中添加vap,目前只考虑一个vap的场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_all_vap(oal_void)
{
    hmac_vap_stru     *pst_vap;
    data_summary_info  st_info;
    oal_uint8          uc_index;
    oal_uint8          uc_max_num;
    oal_uint32         ul_vap_num   = 0;//除配置vap的个数
    oal_uint32         ul_vap_index = 0;
    oal_int32          l_ret;

    uc_max_num = g_st_mac_res.st_vap_res.st_queue.uc_max_elements;
    /* 统计需要备份的vap个数 */
    for(uc_index = 0; uc_index < uc_max_num; uc_index++)
    {
        if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[uc_index])
        {
            pst_vap = (hmac_vap_stru *)&(g_st_mac_res.st_vap_res.ast_vap_info[uc_index]);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_vap:: pst_vap is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if ((WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode)
                || (WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode))
            {
                ul_vap_num++;
            }
        }
    }
    /* index为0的是配置vap,不备份 */
    for(uc_index = 0; uc_index < uc_max_num; uc_index++)
    {
        if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[uc_index])
        {
            pst_vap = (hmac_vap_stru *)&(g_st_mac_res.st_vap_res.ast_vap_info[uc_index]);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_vap:: pst_vap is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if ((WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode)
                || (WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode))
            {
                l_ret = hmac_backup_vap(pst_vap, ul_vap_num, ul_vap_index);
                if (OAL_SUCC != l_ret)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_vap::backup vap fail!");
                    return l_ret;
                }
                ul_vap_index++;
            }
        }
    }
    /* 备份auc_user_cnt信息 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = g_st_mac_res.st_vap_res.auc_user_cnt;
    st_info.ul_value_length        = OAL_SIZEOF(oal_uint8) * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT;
    st_info.st_head.en_data_type   = TYPE_BASE_DATA_TYPE;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "vap_flag", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_vap::backup auc_user_cnt fail!");
        return l_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_recover_vap
 功能描述  : 恢复vap信息,目前这里只考虑一个sta的场景，
             即备份时只有一个STA的信息，恢复时只考虑
             恢复sta的信息。
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_vap(data_summary_info *pst_vap_info)
{
    hmac_vap_stru               *pst_hmac_vap;
    hmac_vap_stru               *pst_hmac_vap_temp;
    mac_vap_stru                *pst_mac_vap;
    wlan_mib_ieee802dot11_stru  *pst_mib;
    data_summary_info           *pst_mib_info;
    oal_uint8                    uc_vap_id;
    oal_uint8                    uc_index;
    oal_uint8                    uc_loop;

    if (OAL_PTR_NULL == pst_vap_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_vap_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)pst_vap_info->ul_value_address;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_hmac_vap is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for(uc_index = 0; uc_index < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_index++)
    {
        if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[uc_index])
        {
            pst_hmac_vap_temp = &g_st_mac_res.st_vap_res.ast_vap_info[uc_index];
            if (OAL_PTR_NULL == pst_hmac_vap_temp)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_hmac_vap_temp is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_mac_vap = &(pst_hmac_vap_temp->st_vap_base_info);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_mac_vap is null");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
                || (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode))
            {
                /* 判断vap模式是否相同 */
                if (pst_mac_vap->en_vap_mode != pst_hmac_vap->st_vap_base_info.en_vap_mode)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::now vap mode is diffent with backup vap");
                    return OAL_FAIL;
                }
                /* 恢复hmac_vap信息 */
                pst_hmac_vap_temp->en_auth_mode   = pst_hmac_vap->en_auth_mode;
                pst_hmac_vap_temp->uc_80211i_mode = pst_hmac_vap->uc_80211i_mode;
                pst_hmac_vap_temp->center_freq    = pst_hmac_vap->center_freq;
                /* 恢复mac_vap信息 */
                /* 保持新的vap id */
                uc_vap_id   = pst_mac_vap->uc_vap_id;
                pst_mib     = pst_mac_vap->pst_mib_info;
                oal_memcopy(pst_mac_vap, &(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(mac_vap_stru));
                pst_mac_vap->uc_vap_id    = uc_vap_id;
                pst_mac_vap->pst_mib_info = pst_mib;
                /* 初始化部分参数 */
                for (uc_loop= 0; uc_loop < MAC_VAP_USER_HASH_MAX_VALUE; uc_loop++)
                {
                    oal_dlist_init_head(&(pst_mac_vap->ast_user_hash[uc_loop]));
                }
                oal_dlist_init_head(&pst_mac_vap->st_mac_user_list_head);
                pst_mac_vap->us_user_nums = 0;//该值会在恢复user时被更新
                /* 恢复mib信息 */
                pst_mib_info = g_st_data_process_interface.get_info_by_name_cb("vap_mib");
                if (OAL_PTR_NULL == pst_mib_info)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_mib_info is null");
                    return OAL_ERR_CODE_PTR_NULL;
                }

                if ((OAL_PTR_NULL == pst_mac_vap->pst_mib_info) || (OAL_PTR_NULL == pst_mib_info->ul_value_address))
                {
                    OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_vap::pst_mib_info = %x, ul_value_address = %x",pst_mac_vap->pst_mib_info, pst_mib_info->ul_value_address);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                oal_memcopy(pst_mac_vap->pst_mib_info, pst_mib_info->ul_value_address, OAL_SIZEOF(wlan_mib_ieee802dot11_stru));
            }
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_all_vap
 功能描述  : 恢复所有vap信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_all_vap(oal_void)
{
    data_summary_info *pst_vap_info;
    oal_uint32         ul_vap_num;
    oal_uint32         ul_index;
    oal_int32          l_ret;

    /* 恢复vap资源 */
    pst_vap_info = g_st_data_process_interface.get_list_info_cb("vap", 0);
    if (OAL_PTR_NULL == pst_vap_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_vap::pst_vap_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_vap_num   = pst_vap_info->st_head.ul_list_numer;
    OAM_WARNING_LOG1(0, OAM_SF_BACKUP, "hmac_recover_all_vap::recover vap begin %d",ul_vap_num);

    l_ret = hmac_recover_vap(pst_vap_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_vap::recover vap fail!");
        return l_ret;
    }

    for(ul_index = 1; ul_index < ul_vap_num; ul_index++)
    {
        pst_vap_info = g_st_data_process_interface.get_list_info_cb("vap", ul_index);
        if (OAL_PTR_NULL == pst_vap_info)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_vap::pst_vap_info is null");
            return OAL_ERR_CODE_PTR_NULL;
        }

        l_ret = hmac_recover_vap(pst_vap_info);
        if (OAL_SUCC != l_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_vap::recover vap fail!");
            return l_ret;
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_backup_device
 功能描述  : 向备份列表中添加device备份信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_device(hmac_device_stru *pst_hmac_dev, oal_uint32 ul_dev_num, oal_uint32 ul_cur_index)
{
    mac_device_stru    *pst_mac_dev;
    data_summary_info   st_info;
    oal_int32           l_ret;

    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_device::pst_hmac_dev is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 备份device私有部分 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = pst_hmac_dev;
    st_info.ul_value_length        = OAL_SIZEOF(hmac_device_stru);
    st_info.st_head.en_data_type   = TYPE_LIST;
    st_info.st_head.ul_list_numer  = ul_dev_num;
    st_info.st_head.ul_cur_number  = ul_cur_index;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "hmac_dev", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_device::backuup hmac_dev fail!");
        return l_ret;
    }

    /* 备份共有部分 */
    pst_mac_dev = pst_hmac_dev->pst_device_base_info;
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_device::pst_mac_dev is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = pst_mac_dev;
    st_info.ul_value_length        = OAL_SIZEOF(mac_device_stru);
    st_info.st_head.en_data_type   = TYPE_LIST;
    st_info.st_head.ul_list_numer  = ul_dev_num;
    st_info.st_head.ul_cur_number  = ul_cur_index;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "mac_dev", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_device::backuup mac_dev fail!");
        return l_ret;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_backup_all_device
 功能描述  : 向备份列表中添加device备份信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_all_device(oal_void)
{
    hmac_device_stru  *pst_hmac_dev;
    oal_uint8          uc_max_num;
    oal_uint8          uc_index;
    oal_uint32         ul_dev_num   = 0;
    oal_uint32         ul_dev_index = 0;
    oal_int32          l_ret;
    data_summary_info  st_info;

    uc_max_num = g_st_hmac_res.st_hmac_dev_res.st_queue.uc_max_elements;
    /* 统计需要备份的dev个数 */
    for(uc_index = 0; uc_index <uc_max_num; uc_index++)
    {
        if (0 != g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[uc_index])
        {
            ul_dev_num++;
        }
    }

    for (uc_index = 0; uc_index < uc_max_num; uc_index++)
    {
        if (0 != g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[uc_index])
        {
            pst_hmac_dev = (hmac_device_stru *)&(g_st_hmac_res.st_hmac_dev_res.ast_hmac_dev_info[uc_index]);
            l_ret = hmac_backup_device(pst_hmac_dev, ul_dev_num, ul_dev_index);
            if (OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "hmac_backup_all_device::backup device fail!");
                return l_ret;
            }
            ul_dev_index++;
        }
    }
    /* 备份hmac_device_stru资源池的auc_user_cnt信息 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = g_st_hmac_res.st_hmac_dev_res.auc_user_cnt;
    st_info.ul_value_length        = OAL_SIZEOF(oal_uint8) * MAC_RES_MAX_DEV_NUM;
    st_info.st_head.en_data_type   = TYPE_BASE_DATA_TYPE;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "dev_flag", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_device::backup auc_user_cnt fail!");
        return l_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_recover_device
 功能描述  : 恢复device备份信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_device(data_summary_info *pst_hmac_dev_info, data_summary_info *pst_mac_dev_info)
{
    hmac_device_stru         *pst_hmac_dev;
    mac_device_stru          *pst_mac_dev;
    mac_device_stru          *pst_mac_dev_temp;
    oal_uint8                 uc_index;
    oal_uint32                ul_chip_ver;    
    hmac_scan_stru            st_scan_mgmt;
    oal_wait_queue_head_stru  st_netif_change_event;
    hmac_rx_dscr_opt_stru     st_rx_dscr_opt; 
    oal_int32                 l_ret;

    if ((OAL_PTR_NULL == pst_hmac_dev_info) || (OAL_PTR_NULL == pst_mac_dev_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_device::pst_hmac_dev_info = %x,pst_mac_dev_info = %x",pst_hmac_dev_info,pst_mac_dev_info);
        return OAL_ERR_CODE_PTR_NULL;
    }
    for(uc_index = 0; uc_index < MAC_RES_MAX_DEV_NUM; uc_index++)
    {
        if (0 != g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[uc_index])
        {
            pst_hmac_dev = (hmac_device_stru *)&(g_st_hmac_res.st_hmac_dev_res.ast_hmac_dev_info[uc_index]);
            if ((OAL_PTR_NULL == pst_hmac_dev) || (OAL_PTR_NULL == pst_hmac_dev_info->ul_value_address))
            {
                OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_device::pst_hmac_dev = %x, ul_value_address = %d"
                              ,pst_hmac_dev, pst_hmac_dev_info->ul_value_address);
                return OAL_ERR_CODE_PTR_NULL;
            }

            /* 恢复hmac dev数据 */
            oal_memcopy(&st_scan_mgmt, &(pst_hmac_dev->st_scan_mgmt), OAL_SIZEOF(hmac_scan_stru));
            oal_memcopy(&st_rx_dscr_opt, &(pst_hmac_dev->st_rx_dscr_opt), OAL_SIZEOF(hmac_rx_dscr_opt_stru));
            oal_memcopy(pst_hmac_dev, pst_hmac_dev_info->ul_value_address, OAL_SIZEOF(hmac_device_stru));
            oal_memcopy(&(pst_hmac_dev->st_scan_mgmt), &st_scan_mgmt, OAL_SIZEOF(hmac_scan_stru));
            oal_memcopy(&(pst_hmac_dev->st_rx_dscr_opt), &st_rx_dscr_opt, OAL_SIZEOF(hmac_rx_dscr_opt_stru));
            /* 将hmac dev资源池的auc_user_cnt相应位重新写0 */
            g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[uc_index] = 0;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
            oal_spin_lock_init(&pst_hmac_dev->st_suspend_lock);
#ifdef CONFIG_HAS_EARLYSUSPEND
            pst_hmac_dev->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + MAX_DATA_NAME_LEN;
            pst_hmac_dev->early_suspend.suspend = hmac_early_suspend;
            pst_hmac_dev->early_suspend.resume  = hmac_late_resume;
            register_early_suspend(&pst_hmac_dev->early_suspend);
#else
            pst_hmac_dev->pm_notifier.notifier_call = hmac_fb_notify;
            fb_register_client(&pst_hmac_dev->pm_notifier);
#endif
#endif
            /* 初始化P2P 等待队列 */
            OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_dev->st_netif_change_event));
#ifdef _PRE_WLAN_TCP_OPT
            pst_hmac_dev->sys_tcp_tx_ack_opt_enable = DEFAULT_TX_TCP_ACK_OPT_ENABLE;
            pst_hmac_dev->sys_tcp_rx_ack_opt_enable = DEFAULT_RX_TCP_ACK_OPT_ENABLE;
            pst_hmac_dev->en_need_notify = OAL_FALSE;
#endif
            /* 恢复mac dev数据 */
            pst_mac_dev  = (mac_device_stru *)&(g_st_mac_res.st_dev_res.ast_dev_info[uc_index]);
            pst_mac_dev_temp = (mac_device_stru *)pst_mac_dev_info->ul_value_address;
            if ((OAL_PTR_NULL == pst_mac_dev) || (OAL_PTR_NULL == pst_mac_dev_temp))
            {
                OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_device::pst_mac_dev = %x,pst_mac_dev_temp = %x",pst_mac_dev,pst_mac_dev_temp);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAM_WARNING_LOG2(0, OAM_SF_BACKUP, "recover_dev:user_cnt= %d,sta_num=%d\n",pst_mac_dev_temp->uc_asoc_user_cnt,pst_mac_dev_temp->uc_sta_num);
            pst_mac_dev->uc_max_channel     = pst_mac_dev_temp->uc_max_channel;
            pst_mac_dev->en_max_band        = pst_mac_dev_temp->en_max_band;
            pst_mac_dev->en_max_bandwidth   = pst_mac_dev_temp->en_max_bandwidth;
            pst_mac_dev->uc_active_user_cnt = pst_mac_dev_temp->uc_active_user_cnt;
            pst_mac_dev->uc_asoc_user_cnt   = pst_mac_dev_temp->uc_asoc_user_cnt;
            pst_mac_dev->en_2040bss_switch  = pst_mac_dev_temp->en_2040bss_switch;
            pst_mac_dev->uc_in_suspend      = pst_mac_dev_temp->uc_in_suspend;
            pst_hmac_dev->pst_device_base_info = pst_mac_dev;
            
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_all_device
 功能描述  : 恢复device备份信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_all_device(oal_void)
{
    data_summary_info *pst_data_info;
    data_summary_info *pst_hmac_dev_info;
    data_summary_info *pst_mac_dev_info;
    oal_uint32         ul_index;
    oal_uint32         ul_list_num;
    oal_uint32         l_ret;

    /* 恢复g_st_hmac_res资源池的auc_user_cnt */
    OAM_WARNING_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::recover device find dev_flag");
    pst_data_info = g_st_data_process_interface.get_info_by_name_cb("dev_flag");
    if (OAL_PTR_NULL == pst_data_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::pst_data_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_data_info->ul_value_address)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::pst_data_info->ul_value_address is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memcopy(g_st_hmac_res.st_hmac_dev_res.auc_user_cnt, pst_data_info->ul_value_address, pst_data_info->ul_value_length);
    /* 恢复device */
    pst_hmac_dev_info = g_st_data_process_interface.get_list_info_cb("hmac_dev", 0);
    pst_mac_dev_info  = g_st_data_process_interface.get_list_info_cb("mac_dev", 0);
    if ((OAL_PTR_NULL == pst_hmac_dev_info) || (OAL_PTR_NULL == pst_mac_dev_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_all_device::pst_hmac_dev_info = %x,pst_mac_dev_info = %x",pst_hmac_dev_info,pst_mac_dev_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    l_ret = hmac_recover_device(pst_hmac_dev_info, pst_mac_dev_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::recover dev fail!");
        return l_ret;
    }

    ul_list_num = pst_hmac_dev_info->st_head.ul_list_numer;
    OAM_WARNING_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::recover device begin");
    for(ul_index = 1;ul_index < ul_list_num; ul_index++)
    {
        pst_hmac_dev_info = g_st_data_process_interface.get_list_info_cb("hmac_dev", ul_index);
        pst_mac_dev_info  = g_st_data_process_interface.get_list_info_cb("mac_dev", ul_index);
        if ((OAL_PTR_NULL == pst_hmac_dev_info) || (OAL_PTR_NULL == pst_mac_dev_info))
        {
            OAM_ERROR_LOG2(0, OAM_SF_BACKUP, "hmac_recover_all_device::pst_hmac_dev_info = %x,pst_mac_dev_info = %x",pst_hmac_dev_info,pst_mac_dev_info);
            return OAL_ERR_CODE_PTR_NULL;
        }
        l_ret = hmac_recover_device(pst_hmac_dev_info, pst_mac_dev_info);
        if (OAL_SUCC != l_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::recover dev fail!");
            return l_ret;
        }
    }

    /* 再一次恢复g_st_hmac_res资源池的auc_user_cnt */
    if (OAL_PTR_NULL == pst_data_info->ul_value_address)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_all_device::pst_data_info->ul_value_address is null");
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memcopy(g_st_hmac_res.st_hmac_dev_res.auc_user_cnt, pst_data_info->ul_value_address, pst_data_info->ul_value_length);
    return OAL_SUCC;
}
#ifndef WIN32
/*****************************************************************************
 函 数 名  : frw_event_printf
 功能描述  : 查看当前事件队列里的事件类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_event_printf(oal_void)
{
    oal_uint32                     ul_core_id;
    frw_event_mem_stru            *pst_event_mem;
    frw_event_sched_queue_stru    *pst_sched_queue;
    frw_event_hdr_stru            *pst_event_hrd;
    frw_event_sched_queue_stru    *pst_queue;
    frw_event_queue_stru          *pst_event_queue;
    oal_dlist_head_stru           *pst_list;
    oal_uint8                      uc_index;
    oal_uint8                      uc_event_index;

    ul_core_id      = OAL_GET_CORE_ID();
    pst_sched_queue = g_ast_event_manager[ul_core_id].st_sched_queue;
    for(uc_index = 0; uc_index < FRW_SCHED_POLICY_BUTT; uc_index++)
    {
        pst_queue = &pst_sched_queue[uc_index];
        if (OAL_FALSE != oal_dlist_is_empty(&pst_queue->st_head))
        {
            /* 遍历整个调度链表 */
            OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_queue->st_head)
            {
                pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);
                if (OAL_PTR_NULL == pst_event_queue)
                {
                    OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "frw_event_printf::pst_event_queue is null");
                    return;
                }
                for(uc_event_index = 0; uc_event_index < pst_event_queue->st_queue.uc_max_elements; uc_event_index++)
                {
                    pst_event_mem = (frw_event_mem_stru *)&pst_event_queue->st_queue.pul_buf[uc_event_index];
                    if (OAL_PTR_NULL != pst_event_mem)
                    {
                        pst_event_hrd = (frw_event_hdr_stru *)(pst_event_mem->puc_data);
                        if (OAL_PTR_NULL != pst_event_hrd)
                        {
                            OAM_WARNING_LOG2(0, OAM_SF_BACKUP, "[RL]frw_event_printf::event type = %d,sub_type = %d",pst_event_hrd->en_type,pst_event_hrd->uc_sub_type);
                            return;
                        }
                    }
                }
            }
        }
    }
}
#endif
/*****************************************************************************
 函 数 名  : hmac_backup_mac_addr
 功能描述  : 备份mac地址数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_mac_addr(oal_uint8 *puc_dev_name)
{
    oal_net_device_stru        *pst_net_dev;
    data_summary_info           st_info;
    oal_int32                   l_ret;
    oal_uint8                  *puc_mac;

    if (OAL_PTR_NULL == puc_dev_name)
    {
        OAM_WARNING_LOG0(0, OAM_SF_BACKUP,"hmac_backup_mac_addr::puc_dev_name is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_net_dev = oal_dev_get_by_name(puc_dev_name);
    if (OAL_PTR_NULL == pst_net_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_BACKUP, "{hmac_backup_mac_addr::the net_device is already exist!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 备份auc_user_cnt信息 */
    OAL_MEMZERO(&st_info, OAL_SIZEOF(data_summary_info));
    st_info.ul_value_address       = OAL_NETDEVICE_MAC_ADDR(pst_net_dev);
    st_info.ul_value_length        = ETH_ADDR_LEN;
    st_info.st_head.en_data_type   = TYPE_BASE_DATA_TYPE;
    st_info.st_head.en_module_type = MODULE_WIFI_DRIVER;
    oal_memcopy(st_info.st_head.ac_name, "mac_addr", MAX_DATA_NAME_LEN);

    l_ret = g_st_data_process_interface.add_info_cb(&st_info);
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_all_vap::backup auc_user_cnt fail!");
        return l_ret;
    }

    puc_mac = (oal_uint8 *)OAL_NETDEVICE_MAC_ADDR(pst_net_dev);
    OAM_WARNING_LOG4(0, OAM_SF_BACKUP, "backup mac addr:%02x %02x ... %02x %02x",puc_mac[0],puc_mac[1],puc_mac[4],puc_mac[5]);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_mac_addr
 功能描述  : 恢复mac地址数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年8月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_mac_addr(oal_uint8 *puc_mac_addr)
{
    data_summary_info   *pst_info;

    if (OAL_PTR_NULL == puc_mac_addr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_mac_addr::puc_mac_addr is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_info = g_st_data_process_interface.get_info_by_name_cb("mac_addr");
    if (OAL_PTR_NULL == pst_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_mac_addr::pst_data_info is null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_info->ul_value_address)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BACKUP, "hmac_recover_mac_addr::ul_value_address = %x",pst_info->ul_value_address);
        return OAL_ERR_CODE_PTR_NULL;
    }
    oal_memcopy(puc_mac_addr, pst_info->ul_value_address, ETH_ADDR_LEN);
    OAM_WARNING_LOG4(0, OAM_SF_BACKUP, "hmac_recover_mac_addr:%02x %02x %02x %02x",puc_mac_addr[0],puc_mac_addr[1],puc_mac_addr[4],puc_mac_addr[5]);
    return OAL_SUCC;  
}
/*****************************************************************************
 函 数 名  : hmac_backup_data
 功能描述  : 备份数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : MAX_DATA_NAME_LEN16年8月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_backup_data(oal_void)
{
    oal_int32  l_ret;

    l_ret = hmac_backup_all_device();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_data::backup all device is fail");
        return l_ret;
    }

    l_ret = hmac_backup_all_vap();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_data::backup all vap is fail");
        return l_ret;
    }

    l_ret = hmac_backup_all_user();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_data::backup all user is fail");
        return l_ret;
    }

    l_ret = hmac_backup_mac_addr("wlan0");
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_backup_data::backup mac addr is fail");
        return l_ret;
    }
#ifndef WIN32
    hmac_event_printf();
#endif
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_recover_data
 功能描述  : 恢复数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : MAX_DATA_NAME_LEN16年8月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_recover_data(oal_void)
{
    oal_int32          l_ret;
    mac_device_stru   *pst_mac_dev;
    oal_uint8          uc_vap_num;
    
    l_ret = hmac_recover_all_device();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_data::recover all device fail");
        return l_ret;
    }
    
    l_ret = hmac_recover_all_vap();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_data::recover all vap fail");
        return l_ret;
    }
    
    l_ret = hmac_recover_all_user();
    if (OAL_SUCC != l_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BACKUP, "hmac_recover_data::recover all user fail");
        return l_ret;
    }

    return OAL_SUCC;
}

#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



