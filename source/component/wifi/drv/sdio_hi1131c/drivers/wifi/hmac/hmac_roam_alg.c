/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_roam_alg.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2015年3月18日
  最近修改   :
  功能描述   : 漫游模块算法实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月18日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_roam_main.h"
#include "hmac_roam_connect.h"
#include "hmac_roam_alg.h"
#include "hmac_mgmt_sta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_ALG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
hmac_roam_rssi_capacity_stru   gst_rssi_table_11a_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               29300},
    {-82,               17300},
    {-90,               5400}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_11b[ROAM_RSSI_LEVEL] = {
    {-88,               8100},
    {-92,               4900},
    {-94,               900}

};
hmac_roam_rssi_capacity_stru   gst_rssi_table_11g_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               29300},
    {-82,               17300},
    {-90,               5400}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_ht20_ofdm[ROAM_RSSI_LEVEL] = {
    {-72,               58800},
    {-80,               35300},
    {-90,               5800}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_ht40_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               128100},
    {-77,               70500},
    {-87,               11600}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_vht80_ofdm[ROAM_RSSI_LEVEL] = {
    {-72,               256200},
    {-74,               141000},
    {-84,               23200}
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_roam_alg_init
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_roam_alg_init(hmac_roam_info_stru *pst_roam_info, oal_int8 c_current_rssi)
{
    hmac_roam_alg_stru         *pst_roam_alg;

    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_init::param null.}");
        return;
    }
    /*lint -e571*/
    OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_init c_current_rssi = %d.}", c_current_rssi);
    /*lint +e571*/

    pst_roam_alg = &(pst_roam_info->st_alg);
    if (c_current_rssi == ROAM_RSSI_LINKLOSS_TYPE)
    {
        pst_roam_info->st_static.ul_trigger_linkloss_cnt++;
    }
    else
    {
        pst_roam_info->st_static.ul_trigger_rssi_cnt++;
    }

    pst_roam_alg->ul_max_capacity       = 0;
    pst_roam_alg->pst_max_capacity_bss  = OAL_PTR_NULL;
    pst_roam_alg->c_current_rssi        = c_current_rssi;
    pst_roam_alg->c_max_rssi            = 0;
    pst_roam_alg->uc_another_bss_scaned = 0;
    /* 首次关联时初始化 pst_roam_alg->uc_invalid_scan_cnt   = 0x0; */
    pst_roam_alg->pst_max_rssi_bss      = OAL_PTR_NULL;

    return;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_get_delta_rssi
 功能描述  : 调整rssi增益
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int8 hmac_roam_alg_adjust_rssi_increase(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    oal_int8  c_current_rssi;
    oal_int8  c_target_rssi;
    oal_uint8 uc_delta_rssi;

#ifdef _PRE_WLAN_FEATURE_5G
    if (WLAN_BAND_5G == pst_bss_dscr->st_channel.en_band)
    {
        uc_delta_rssi = pst_roam_info->st_config.uc_delta_rssi_5G;
    }
    else
#endif
    {
        uc_delta_rssi = pst_roam_info->st_config.uc_delta_rssi_2G;
    }

    c_current_rssi = pst_roam_info->st_alg.c_current_rssi;
    c_target_rssi  = pst_bss_dscr->c_rssi;

    if(uc_delta_rssi < ROAM_RSSI_DIFF_4_DB)
    {
        uc_delta_rssi = ROAM_RSSI_DIFF_4_DB;
    }

    if (c_current_rssi >= ROAM_RSSI_NE70_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    if (uc_delta_rssi >= ROAM_RSSI_DIFF_4_DB + 2)
    {
        /* 步进2DB至4DB*/
        uc_delta_rssi -= 2;
    }

    if (c_current_rssi >= ROAM_RSSI_NE75_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    if (uc_delta_rssi >= ROAM_RSSI_DIFF_4_DB + 2)
    {
        /* 步进2DB至4DB*/
        uc_delta_rssi -= 2;
    }

    if (c_current_rssi >= ROAM_RSSI_NE80_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    return (c_target_rssi - c_current_rssi - ROAM_RSSI_DIFF_4_DB);
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_add_list
 功能描述  : 将bssid添加到列表中
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_add_bsslist(hmac_roam_bss_list_stru *pst_roam_bss_list, oal_uint8 *puc_bssid, roam_blacklist_type_enum_uint8 list_type)
{
    hmac_roam_bss_info_stru    *pst_cur_bss;
    hmac_roam_bss_info_stru    *pst_oldest_bss;
    hmac_roam_bss_info_stru    *pst_zero_bss;
    oal_uint8                   auc_mac_zero[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint32                  ul_current_index;
    oal_uint32                  ul_now;
    oal_uint32                  ul_timeout;

    pst_oldest_bss = OAL_PTR_NULL;
    pst_zero_bss   = OAL_PTR_NULL;
    ul_now = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    for (ul_current_index = 0; ul_current_index < ROAM_LIST_MAX; ul_current_index++)
    {
        pst_cur_bss = &pst_roam_bss_list->ast_bss[ul_current_index];
        ul_timeout = (oal_uint32)pst_cur_bss->ul_timeout;
        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, puc_bssid))
        {
            /* 优先查找已存在的记录，如果名单超时更新时间戳，否则更新count */

            if (OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now) > ul_timeout)
            {
                pst_cur_bss->ul_time_stamp = ul_now;
                pst_cur_bss->us_count      = 1;
                /*漫游黑名单，以后有用*/
                if(ROAM_BLACKLIST_TYPE_REJECT_AP == list_type)
                {
                    pst_cur_bss->ul_timeout = ROAM_BLACKLIST_REJECT_AP_TIME_OUT;
                }
            }
            else
            {
                pst_cur_bss->us_count++;
                if(pst_cur_bss->us_count == pst_cur_bss->us_count_limit)
                {
                    pst_cur_bss->ul_time_stamp = ul_now;
                    OAM_WARNING_LOG4(0, OAM_SF_ROAM,"{hmac_roam_alg_add_bsslist::  add new, [%02X:XX:XX:%02X:%02X:%02X]}",
                                                 pst_cur_bss->auc_bssid[0],pst_cur_bss->auc_bssid[3],pst_cur_bss->auc_bssid[4],pst_cur_bss->auc_bssid[5]);
                }
            }
            return OAL_SUCC;
        }

        /* 记录第一个空记录 */
        if (OAL_PTR_NULL != pst_zero_bss)
        {
            continue;
        }

        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, auc_mac_zero))
        {
            pst_zero_bss = pst_cur_bss;
            continue;
        }

        /* 记录一个非空最老记录 */
        if (OAL_PTR_NULL == pst_oldest_bss)
        {
            pst_oldest_bss = pst_cur_bss;
        }
        else
        {
            if (OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now) >
                OAL_TIME_GET_RUNTIME(pst_oldest_bss->ul_time_stamp, ul_now))
            {
                pst_oldest_bss = pst_cur_bss;
            }
        }
    }

    if (OAL_PTR_NULL == pst_zero_bss)
    {
        pst_zero_bss = pst_oldest_bss;
    }

    if (OAL_PTR_NULL != pst_zero_bss)
    {
        oal_set_mac_addr(pst_zero_bss->auc_bssid, puc_bssid);
        pst_zero_bss->ul_time_stamp = ul_now;
        pst_zero_bss->us_count      = 1;
        return OAL_SUCC;
    }
    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : hmac_roam_find_in_blacklist
 功能描述  : 检查列表中是否存在该bssid
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_roam_alg_find_in_bsslist(hmac_roam_bss_list_stru *pst_roam_bss_list, oal_uint8 *puc_bssid)
{
    hmac_roam_bss_info_stru    *pst_cur_bss;
    oal_uint32                  ul_current_index;
    oal_uint32                  ul_now;
    oal_uint32                  ul_timeout;
    oal_uint32                  ul_delta_time;
    oal_uint16                  us_count_limit;

    ul_now         = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    for (ul_current_index = 0; ul_current_index < ROAM_LIST_MAX; ul_current_index++)
    {
        pst_cur_bss = &pst_roam_bss_list->ast_bss[ul_current_index];
        ul_timeout     = (oal_uint32)pst_cur_bss->ul_timeout;
        us_count_limit =  pst_cur_bss->us_count_limit;

        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, puc_bssid))
        {
            /* 如果在超时时间内出现count_limit次以上记录 */
            ul_delta_time = OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now);
            if ((ul_delta_time <= ul_timeout) &&
                (pst_cur_bss->us_count >= us_count_limit))
            {
                OAM_WARNING_LOG4(0, OAM_SF_ROAM,"{hmac_roam_alg_find_in_bsslist::  time_left = [%d], [%02X:XX:XX:XX:%02X:%02X]}",
                                ul_timeout - ul_delta_time,pst_cur_bss->auc_bssid[0],pst_cur_bss->auc_bssid[4],pst_cur_bss->auc_bssid[5]);
                return OAL_TRUE;
            }
            return OAL_FALSE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_add_blacklist
 功能描述  : 将bssid添加到黑名单列表中
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_alg_add_blacklist(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid, roam_blacklist_type_enum_uint8 list_type)
{
    oal_uint32      ul_ret;
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_roam_alg_add_bsslist(&pst_roam_info->st_alg.st_blacklist, puc_bssid, list_type);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_add_blacklist::hmac_roam_alg_add_list failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_find_in_blacklist
 功能描述  : 检查黑名单列表中是否存在该bssid
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_find_in_blacklist(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_FALSE;
    }

    return hmac_roam_alg_find_in_bsslist(&pst_roam_info->st_alg.st_blacklist, puc_bssid);
}


/*****************************************************************************
 函 数 名  : hmac_roam_add_bss_history
 功能描述  : 将bssid添加到历史优选AP列表中
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_alg_add_history(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    oal_uint32      ul_ret;

    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_roam_alg_add_bsslist(&pst_roam_info->st_alg.st_history, puc_bssid, ROAM_BLACKLIST_TYPE_NORMAL_AP);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_add_history::hmac_roam_alg_add_list failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_roam_find_in_blacklist
 功能描述  : 检查历史优选列表中是否存在该bssid
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_find_in_history(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_FALSE;
    }

    return hmac_roam_alg_find_in_bsslist(&pst_roam_info->st_alg.st_history, puc_bssid);
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_scan_channel_init
 功能描述  : chu
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_alg_scan_channel_init(hmac_roam_info_stru *pst_roam_info, mac_scan_req_stru *pst_scan_params)
{
    oal_uint32         ul_ret;
    oal_uint8          uc_chan_idx;
    oal_uint8          uc_chan_number;

    if ((pst_roam_info == OAL_PTR_NULL) || (pst_scan_params == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_scan_channel_init::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_scan_params->uc_channel_nums  = 0;
    if (pst_roam_info->st_config.uc_scan_band & ROAM_BAND_2G_BIT)
    {
        switch (pst_roam_info->st_config.uc_scan_orthogonal)
        {
            case ROAM_SCAN_CHANNEL_ORG_1:
            {
                pst_scan_params->ast_channel_list[0].uc_chan_number = 1;
                pst_scan_params->ast_channel_list[0].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[0].uc_idx         = 0;

                pst_scan_params->ast_channel_list[1].uc_chan_number = 6;
                pst_scan_params->ast_channel_list[1].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[1].uc_idx         = 5;

                pst_scan_params->ast_channel_list[2].uc_chan_number = 11;
                pst_scan_params->ast_channel_list[2].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[2].uc_idx         = 10;

                pst_scan_params->uc_channel_nums = 3;
                break;
            }
            case ROAM_SCAN_CHANNEL_ORG_3:
            {
                pst_scan_params->ast_channel_list[0].uc_chan_number = 1;
                pst_scan_params->ast_channel_list[0].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[0].uc_idx         = 0;

                pst_scan_params->ast_channel_list[1].uc_chan_number = 5;
                pst_scan_params->ast_channel_list[1].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[1].uc_idx         = 4;

                pst_scan_params->ast_channel_list[2].uc_chan_number = 7;
                pst_scan_params->ast_channel_list[2].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[2].uc_idx         = 6;

                pst_scan_params->ast_channel_list[3].uc_chan_number = 13;
                pst_scan_params->ast_channel_list[3].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[3].uc_idx         = 12;

                pst_scan_params->uc_channel_nums = 4;
                break;
            }
            default:
            {
                for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
                {
                    ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_chan_idx);
                    if (OAL_SUCC != ul_ret)
                    {
                        continue;
                    }
                    mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_number);
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_chan_number = uc_chan_number;
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].en_band        = WLAN_BAND_2G;
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_idx         = uc_chan_idx;
                    pst_scan_params->uc_channel_nums++;
                }
                break;
            }
        }
    }

#ifdef _PRE_WLAN_FEATURE_5G
    if (pst_roam_info->st_config.uc_scan_band & ROAM_BAND_5G_BIT)
    {
        for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
        {
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_5G, uc_chan_idx);
            if (OAL_SUCC != ul_ret)
            {
                continue;
            }
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_chan_idx, &uc_chan_number);
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_chan_number = uc_chan_number;
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].en_band        = WLAN_BAND_5G;
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_idx         = uc_chan_idx;
            pst_scan_params->uc_channel_nums++;
        }
    }
#endif /* _PRE_WLAN_FEATURE_5G */

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_alg_get_capacity_by_rssi
 功能描述  : chu
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_get_capacity_by_rssi(wlan_protocol_enum_uint8 en_protocol, wlan_bw_cap_enum_uint8 en_bw_cap, oal_int8 c_rssi)
{
    hmac_roam_rssi_capacity_stru   *pst_rssi_table = OAL_PTR_NULL;
    oal_uint8                       uc_index;

    switch (en_protocol)
    {
        case WLAN_LEGACY_11A_MODE:
           pst_rssi_table = gst_rssi_table_11a_ofdm;
           break;

        case WLAN_LEGACY_11B_MODE:
            pst_rssi_table = gst_rssi_table_11b;
            break;

        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
            pst_rssi_table = gst_rssi_table_11g_ofdm;
            break;

        case WLAN_HT_MODE:
        case WLAN_VHT_MODE:
            if (en_bw_cap == WLAN_BW_CAP_20M)
            {
                pst_rssi_table = gst_rssi_table_ht20_ofdm;
            }
            else if (en_bw_cap == WLAN_BW_CAP_40M)
            {
                pst_rssi_table = gst_rssi_table_ht40_ofdm;
            }
            else
            {
                pst_rssi_table = gst_rssi_table_vht80_ofdm;
            }
            break;

        default:
            break;
    }

    if (OAL_PTR_NULL == pst_rssi_table)
    {
        return 0;
    }

    for(uc_index = 0; uc_index < ROAM_RSSI_LEVEL; uc_index++)
    {
        if (c_rssi >= pst_rssi_table[uc_index].c_rssi)
        {
            return pst_rssi_table[uc_index].ul_capacity_kbps;
        }
    }

    return 0;
}
/*****************************************************************************
 函 数 名  : hmac_roam_alg_calc_avail_channel_capacity
 功能描述  : chu
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_calc_avail_channel_capacity(mac_bss_dscr_stru *pst_bss_dscr)
{
    oal_uint32                 ul_capacity = 0;
    oal_uint32                 ul_avail_channel_capacity = 0;
    oal_uint32                 ul_ret;
    oal_uint8                  uc_channel_utilization = 0;
    oal_uint8                 *puc_obss_ie;
    oal_uint8                  uc_ie_offset;
    wlan_protocol_enum_uint8   en_protocol;

    ul_ret = hmac_sta_get_user_protocol(pst_bss_dscr, &en_protocol);
    if (OAL_SUCC != ul_ret)
    {
        return 0;
    }
    /***************************************************************************
        ------------------------------------------------------------------------
        |EID |Len |StationCount |ChannelUtilization |AvailableAdmissionCapacity|
        ------------------------------------------------------------------------
        |1   |1   |2            |1                  |2                         |
        ------------------------------------------------------------------------
        ***************************************************************************/
    /*lint -e416*/
    uc_ie_offset = MAC_80211_FRAME_LEN + MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    puc_obss_ie = mac_find_ie(MAC_EID_QBSS_LOAD, (oal_uint8 *)(pst_bss_dscr->auc_mgmt_buff + uc_ie_offset), (oal_int32)(pst_bss_dscr->ul_mgmt_len - uc_ie_offset));
    /*lint +e416*/
     /* 长度要到达ChannelUtilization这个域，至少为3 */
    if (puc_obss_ie && (puc_obss_ie[1] >= 3))
    {
        uc_channel_utilization = *(puc_obss_ie + 4);
    }

    ul_capacity = hmac_roam_alg_get_capacity_by_rssi(en_protocol, pst_bss_dscr->en_bw_cap, pst_bss_dscr->c_rssi);

    ul_avail_channel_capacity = ul_capacity * (255 - uc_channel_utilization) / 255 / ROAM_CONCURRENT_USER_NUMBER;

    return ul_avail_channel_capacity;
}
/*****************************************************************************
 函 数 名  : hmac_roam_alg_bss_in_ess
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_alg_bss_in_ess(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;
    mac_cfg_ssid_param_stru     st_cfg_ssid;
    oal_uint8                   uc_stru_len;

    if ((OAL_PTR_NULL == pst_roam_info) || (OAL_PTR_NULL == pst_bss_dscr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_bss_in_ess::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    mac_mib_get_ssid(pst_mac_vap, &uc_stru_len, (oal_uint8 *)(&st_cfg_ssid));

    if ((OAL_STRLEN(pst_bss_dscr->ac_ssid) != st_cfg_ssid.uc_ssid_len) ||
        (0 != oal_memcmp(st_cfg_ssid.ac_ssid, pst_bss_dscr->ac_ssid, st_cfg_ssid.uc_ssid_len)))
    {
        return OAL_SUCC;
    }
    pst_roam_alg = &(pst_roam_info->st_alg);

    /* 是否扫描到了当前关联的 bss, 仅置位，不过滤 */
    if (0 != oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        pst_roam_alg->uc_another_bss_scaned = 1;
        hmac_roam_ignore_rssi_trigger(pst_hmac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_bss_check
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_alg_bss_check(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;
    mac_cap_info_stru          *pst_cap_info;
    mac_cfg_ssid_param_stru     st_cfg_ssid;
    oal_uint32                  ul_ret;
    oal_uint32                  ul_avail_channel_capacity;
    oal_uint8                   uc_stru_len;
    oal_int8                    c_delta_rssi;

    if ((OAL_PTR_NULL == pst_roam_info) || (OAL_PTR_NULL == pst_bss_dscr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_bss_check::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    mac_mib_get_ssid(pst_mac_vap, &uc_stru_len, (oal_uint8 *)(&st_cfg_ssid));

    if ((OAL_STRLEN(pst_bss_dscr->ac_ssid) != st_cfg_ssid.uc_ssid_len) ||
        (0 != oal_memcmp(st_cfg_ssid.ac_ssid, pst_bss_dscr->ac_ssid, st_cfg_ssid.uc_ssid_len)))
    {
        return OAL_SUCC;
    }
    pst_roam_alg = &(pst_roam_info->st_alg);

    /* 检查黑名单 */
    ul_ret = hmac_roam_alg_find_in_blacklist(pst_roam_info, pst_bss_dscr->auc_bssid);
    if (OAL_TRUE == ul_ret)
    {
        return OAL_SUCC;
    }

    /* 排除当前bss的rssi值计算，本地已经保存了dmac上报的rssi */
    if (0 == oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        return OAL_SUCC;
    }

    /*  wep的bss直接过滤掉 */
    pst_cap_info = (mac_cap_info_stru *)&pst_bss_dscr->us_cap_info;
    if ((0 == pst_bss_dscr->st_bss_sec_info.uc_bss_80211i_mode) &&
        (0 != pst_cap_info->bit_privacy))
    {
        return OAL_SUCC;
    }

    /*  open加密方式到wpa/wpa2直接过滤掉 */
    /*lint -e731*/
    if ((0 == pst_cap_info->bit_privacy) != (OAL_TRUE != mac_mib_get_privacyinvoked(&pst_hmac_vap->st_vap_base_info)))
    {
        return OAL_SUCC;
    }
    /*lint +e731*/

    /* c_current_rssi为0时，表示linkloss上报的触发，不需要考虑rssi增益 */
    c_delta_rssi = hmac_roam_alg_adjust_rssi_increase(pst_roam_info, pst_bss_dscr);
    if (c_delta_rssi <= 0)
    {
        return OAL_SUCC;
    }


    ul_avail_channel_capacity = hmac_roam_alg_calc_avail_channel_capacity(pst_bss_dscr);
    if ((0 != ul_avail_channel_capacity) &&
        ((OAL_PTR_NULL == pst_roam_alg->pst_max_capacity_bss) ||
        (ul_avail_channel_capacity > pst_roam_alg->ul_max_capacity)))
    {
	    //暂时不考虑容量
        //pst_roam_alg->ul_max_capacity      = ul_avail_channel_capacity;
        //pst_roam_alg->pst_max_capacity_bss = pst_bss_dscr;
    }

    if ((OAL_PTR_NULL == pst_roam_alg->pst_max_rssi_bss) ||
        (pst_bss_dscr->c_rssi > pst_roam_alg->c_max_rssi))
    {
        pst_roam_alg->c_max_rssi        = pst_bss_dscr->c_rssi;
        pst_roam_alg->pst_max_rssi_bss  = pst_bss_dscr;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_need_to_stop_roam_trigger
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_need_to_stop_roam_trigger(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru              *pst_hmac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;

    if (OAL_PTR_NULL == pst_roam_info)
    {
         return OAL_FALSE;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_FALSE;
    }


    pst_roam_alg  = &(pst_roam_info->st_alg);

    if (pst_roam_alg->uc_another_bss_scaned)
    {
        pst_roam_alg->uc_invalid_scan_cnt = 0xff;
        return OAL_FALSE;
    }

    if (pst_roam_alg->uc_invalid_scan_cnt == 0xff)
    {
        return OAL_FALSE;
    }

    if (pst_roam_alg->uc_invalid_scan_cnt++ > 4)
    {
        pst_roam_alg->uc_invalid_scan_cnt = 0xff;
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_roam_alg_bss_check
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
mac_bss_dscr_stru *hmac_roam_alg_select_bss(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    mac_bss_dscr_stru          *pst_bss_dscr;
    hmac_roam_alg_stru         *pst_roam_alg;
    oal_int8                    c_delta_rssi;

    if (OAL_PTR_NULL == pst_roam_info)
    {
         return OAL_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_PTR_NULL;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);

    pst_roam_alg = &(pst_roam_info->st_alg);

    /* 取得最大 rssi 的 bss */
    pst_bss_dscr = pst_roam_alg->pst_max_rssi_bss;

    if ((OAL_PTR_NULL != pst_roam_alg->pst_max_capacity_bss) && (pst_roam_alg->ul_max_capacity >= ROAM_THROUGHPUT_THRESHOLD))
    {
        /* 取得最大 capacity 的 bss*/
        pst_bss_dscr = pst_roam_alg->pst_max_capacity_bss;
    }

    if(OAL_PTR_NULL == pst_bss_dscr)
    {
        /* should not be here */
        return OAL_PTR_NULL;
    }

    /* 过滤当前关联的 bss */
    if (0 == oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        return OAL_PTR_NULL;
    }

    /* rssi增益处理 */
    c_delta_rssi = hmac_roam_alg_adjust_rssi_increase(pst_roam_info, pst_bss_dscr);
    if (c_delta_rssi <= 0)
    {
        return OAL_PTR_NULL;
    }

    return pst_bss_dscr;
}

#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

