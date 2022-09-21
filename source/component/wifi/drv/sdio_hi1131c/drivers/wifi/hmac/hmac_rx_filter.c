/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_rx_filter.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年7月14日
  最近修改   :
  功能描述   : 帧过滤处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "wlan_spec.h"
#include "wlan_types.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_rx_filter.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RX_FILTER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oal_bool_enum_uint8 g_en_rx_filter_enable;
oal_uint32 g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BUTT][MAC_VAP_STATE_BUTT];
oal_uint32 g_ast_multi_staup_sta_rx_filter[MAC_VAP_STA_STATE_BUTT];
oal_uint32 g_ast_multi_staup_ap_rx_filter[MAC_VAP_AP_STATE_BUTT];
oal_uint32 g_ast_multi_apup_sta_rx_filter[MAC_VAP_STA_STATE_BUTT];



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_find_is_sta_up
 功能描述  : 查找是否有已经UP的STA
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_find_is_sta_up(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_find_is_sta_up::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_find_is_ap_up
 功能描述  : 查找是否有已经UP的AP
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_find_is_ap_up(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_find_is_ap_up::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((MAC_VAP_STATE_INIT != pst_vap->en_vap_state) && (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_calc_up_ap_num
 功能描述  : 计算不处于inti状态的VAP个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_calc_up_ap_num(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;
    oal_uint8                      ul_up_ap_num = 0;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_calc_up_ap_num::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((MAC_VAP_STATE_INIT != pst_vap->en_vap_state) && (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
            ul_up_ap_num++;
        }
        else if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            ul_up_ap_num++;
        }
    }

    return ul_up_ap_num;
}

/*****************************************************************************
 函 数 名  : hmac_find_up_vap
 功能描述  : 找到up vap (优先级:AP > STA)
 输入参数  : pst_mac_device
 输出参数  : ppst_mac_vap
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_find_up_vap(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap)
{
    oal_uint32                     ul_ret;
    mac_vap_stru                  *pst_vap_up;     /* 处在UP状态的VAP */

    /* find up VAP */
    ul_ret = mac_device_find_up_vap(pst_mac_device, &pst_vap_up);
    if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
    {
        *ppst_mac_vap = pst_vap_up;
        /* find up AP */
        ul_ret = mac_device_find_up_ap(pst_mac_device, &pst_vap_up);
        if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
        {
            *ppst_mac_vap = pst_vap_up;
        }

        return OAL_SUCC;
    }
    else
    {
        *ppst_mac_vap = OAL_PTR_NULL;
        return OAL_FALSE;
    }
}

#if 0
/*****************************************************************************
 函 数 名  : hmac_set_rx_filter_value
 功能描述  : AP侧接收到对应STA的关联请求消息
             待修订为dmac_set_rx_filter_value
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_set_rx_filter_value(mac_vap_stru *pst_mac_vap)
{

#ifndef _PRE_WLAN_PHY_PERFORMANCE
    mac_device_stru                        *pst_mac_device;
    frw_event_mem_stru                     *pst_event_mem;
    frw_event_stru                         *pst_event;
    oal_uint32                              ul_ret;
    oal_uint32                              ul_rx_filter_val;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_vap_stru                           *pst_vap_up;     /* 处在UP状态的VAP */
#endif

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    /* 若为常收，直接返回 */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }
#endif

    if (OAL_FALSE == g_en_rx_filter_enable)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::g_en_rx_filter_enable is false.}");
        return OAL_SUCC;
    }


    if ((MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state) || (MAC_VAP_STATE_AP_PAUSE == pst_mac_vap->en_vap_state))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::not need change rx filter!}");
        return OAL_SUCC;
    }

    /* 只有1个VAP STA/AP */
    if ((1 == pst_mac_device->uc_vap_num) || (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode))
    {
        ul_rx_filter_val = g_ast_normal_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }
    else if ((1 < pst_mac_device->uc_vap_num) && (0 == pst_mac_device->uc_sta_num))
    {
        /* 如果此时有AP不处于Down的状态，不需要配置任何值，直接返回 */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device)) && (MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }

        ul_rx_filter_val = g_ast_normal_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }
#ifdef _PRE_WLAN_FEATURE_P2P
    /* 多STA情况下配置 */
    else if ((1 < pst_mac_device->uc_vap_num) && (pst_mac_device->uc_vap_num == pst_mac_device->uc_sta_num))
    {
        /*  如果此时有STA不处于Down的状态，不需要配置任何值，直接返回 */
        /*  解决多VAP情况下，其中一个被down，导致其他STA beacon miss问题 */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device))
            && ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_SCAN_COMP == pst_mac_vap->en_vap_state)))
        {
            /*查找up vap. 优先级: AP > STA*/
            ul_ret = hmac_find_up_vap(pst_mac_device, &pst_vap_up);
            if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
            {
                /* 如果有其他up vap,不设置vap状态为MAC_VAP_STATE_INIT,MAC_VAP_STATE_STA_FAKE_UP,
                   MAC_VAP_STATE_STA_SCAN_COMP的rx filter, 设置当前up VAP的rx filter, 优先级：AP > STA */
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_vap_up->en_vap_mode][MAC_VAP_STATE_UP];
            }
            else
            {
                return OAL_SUCC;
            }
        }
        else
        {
            /* WLAN/P2P_DEV/P2P_GO 或WLAN/P2P_DEV/P2P_CL 共存情况 */
            ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
        }
    }
    /* 多AP和STA共存情况下配置 */
    else if ((1 < pst_mac_device->uc_vap_num) && (0 != pst_mac_device->uc_sta_num)
              && (pst_mac_device->uc_vap_num > pst_mac_device->uc_sta_num))
    {
        /*  如果此时有STA不处于Down的状态，不需要配置任何值，直接返回 */
        /*  解决多VAP情况下，其中一个被down，导致其他STA beacon miss问题 */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device))
            && ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_SCAN_COMP == pst_mac_vap->en_vap_state)))
        {
            /*查找up vap. 优先级: AP > STA*/
            ul_ret = hmac_find_up_vap(pst_mac_device, &pst_vap_up);
            if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
            {
                /* 如果有其他up vap,不设置vap状态为MAC_VAP_STATE_INIT,MAC_VAP_STATE_STA_FAKE_UP,
                   MAC_VAP_STATE_STA_SCAN_COMP的rx filter, 设置当前up VAP的rx filter, 优先级：AP > STA */
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_vap_up->en_vap_mode][MAC_VAP_STATE_UP];
            }
            else
            {
                return OAL_SUCC;
            }
        }
        else
        {
            /* WLAN/P2P_DEV/P2P_GO 共存情况,由于扫描阶段需要收到其他BSS的单播管理帧，
               所以如果是SCAN状态下必须使用STA状态下的配置值，否则使用AP UP状态下配置值 */
            if ((pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_WAIT_SCAN)
               || (pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_OBSS_SCAN)
               || (pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_BG_SCAN))
            {
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
            }
            else
            {
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP];
            }

        }
    }
#endif /* _PRE_WLAN_FEATURE_P2P */
    else
    {
        ul_rx_filter_val = g_ast_repeater_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }

     /* 抛事件到DMAC, 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,
                    OAL_SIZEOF(oal_uint32),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 拷贝参数 */
    oal_memcopy(pst_event->auc_event_data, (oal_void *)&ul_rx_filter_val, OAL_SIZEOF(oal_uint32));

    /*  add test code */
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::start dispatch.}");

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    FRW_EVENT_FREE(pst_event_mem);

#endif

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : hmac_set_rx_filter_value
 功能描述  : AP侧接收到对应STA的关联请求消息
             待修订为dmac_set_rx_filter_value
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_set_rx_filter_value(mac_vap_stru *pst_mac_vap)
{
#ifndef _PRE_WLAN_PHY_PERFORMANCE
    mac_device_stru                        *pst_mac_device;
    frw_event_mem_stru                     *pst_event_mem;
    frw_event_stru                         *pst_event;
    oal_uint32                              ul_ret;
    oal_uint32                              ul_rx_filter_val;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    /* 若为常收，直接返回 */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }
#endif

    if (OAL_FALSE == g_en_rx_filter_enable)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::g_en_rx_filter_enable is false.}");
        return OAL_SUCC;
    }

    if (MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state)
    {
        return OAL_SUCC;
    }

    if (hmac_find_is_ap_up(pst_mac_device)) /* 多VAP模式，AP已经UP*/
    {
        if ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
            || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }

        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            if (hmac_find_is_sta_up(pst_mac_device) && pst_mac_vap->en_vap_state < MAC_VAP_AP_STATE_BUTT)
            {
                ul_rx_filter_val = g_ast_multi_staup_ap_rx_filter[pst_mac_vap->en_vap_state];
            }
            else
            {
                ul_rx_filter_val = g_ast_single_vap_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
            }
        }
        else
        {
            /* 多VAP模式，STA配置(在STA已经up和没有STA up的情况下，配置AP模式都使用该配置) */
            ul_rx_filter_val = g_ast_multi_apup_sta_rx_filter[pst_mac_vap->en_vap_state];
        }
    }
    else if (hmac_find_is_sta_up(pst_mac_device)) /* 多VAP模式，STA已经UP*/
    {
        /* 多VAP模式，STA配置(在STA已经up和没有STA up的情况下，配置AP模式都使用该配置) */
        if ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state) || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }
        /* STA已经UP的状态下，STA的配置 */
        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            ul_rx_filter_val = g_ast_multi_staup_sta_rx_filter[pst_mac_vap->en_vap_state];
        }
        else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            ul_rx_filter_val = g_ast_multi_staup_ap_rx_filter[pst_mac_vap->en_vap_state];
        }
        else
        {
            return OAL_SUCC;
        }
    }
    else
    {
        /* 没有任何设备处于UP状态，即单VAP存在 */
        ul_rx_filter_val = g_ast_single_vap_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }

     /* 抛事件到DMAC, 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,
                    OAL_SIZEOF(oal_uint32),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* 拷贝参数 */
    oal_memcopy(pst_event->auc_event_data, (oal_void *)&ul_rx_filter_val, OAL_SIZEOF(oal_uint32));

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    FRW_EVENT_FREE(pst_event_mem);

#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_filter_init_normal
 功能描述  : 帧过滤各状态值初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_init_single_vap(oal_void)
{
    oal_uint32  ul_state;
    oal_uint32  ul_vap_mode;

    /*           开启 FCS ERROR 过滤            */
    for (ul_vap_mode = WLAN_VAP_MODE_CONFIG; ul_vap_mode < WLAN_VAP_MODE_BUTT; ul_vap_mode++)
    {
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
        {
            g_ast_single_vap_rx_filter[ul_vap_mode][ul_state] = (1<<21);
        }
    }

    /*            WLAN_VAP_MODE_CONFIG, 配置模式                */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | All states                | 0x37BDEEFA               | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0x37B9FEFA;
    }

    /* WLAN_VAP_MODE_BSS_STA          BSS STA模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_STA_FAKE_UP        | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EECA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = (1<<21);
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_INIT]             = 0xF7B9FEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_FAKE_UP]      = 0xF7B9FEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_UP]               = 0x73B9FADA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_PAUSE]            = 0x73B9FADA;

    for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_WAIT_ASOC; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x73B9FADA;
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x37B9DECA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_OBSS_SCAN]    = 0x37B9DEEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_BG_SCAN]      = 0x37B9DEEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_LISTEN]       = 0x33A9FECA;

#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_ROAMING]          = 0x73B9FADA;
#endif

    /* WLAN_VAP_MODE_BSS_AP                BSS AP模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0xF7B9EEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x73B9EAEA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0x73B9EAEA               | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x73B9EAEA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = (1<<21);
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0xF7B9FEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x73B9FAEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_PAUSE]            = 0x73B9FAEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x73B9FAEA;

    /* WLAN_VAP_MODE_MONITOER                侦听模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | all status                       | 0x1                      | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_MONITOER][ul_state] = 0x1 | (1<<21);
    }
}

/*****************************************************************************
 函 数 名  : hmac_rx_filter_init_normal
 功能描述  : 帧过滤各状态值初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_init_multi_vap(oal_void)
{
    oal_uint32  ul_state;

    /*           开启 FCS ERROR 过滤            */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_sta_rx_filter[ul_state] = (1<<21);
        g_ast_multi_apup_sta_rx_filter[ul_state] = (1<<21);
    }
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_ap_rx_filter[ul_state] = (1<<21);
    }

#ifndef _PRE_WLAN_FEATURE_PROXYSTA
    /*  多STA模式    WLAN_VAP_MODE_BSS_STA          BSS STA模式        */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EACA               | */
    /* | ALL OTHER STATE                  | 0x73B9EADA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_sta_rx_filter[ul_state] = 0x73B9FADA;
    }

    g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x33B9DACA;
    g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_OBSS_SCAN]    = 0x33B9DACA;
    g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_BG_SCAN]      = 0x33B9DACA;
    g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_LISTEN]       = 0x33A9FACA;


    /* 多AP UP时,STA配置场景:  WLAN_VAP_MODE_BSS_STA   BSS STA模式     */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 保持原有值不配置         | */
    /* | MAC_VAP_STATE_UP                 | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_FAKE_UP        | 保持原有值不配置         | */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x33B9CACA               | */
    /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EACA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_ast_multi_apup_sta_rx_filter[ul_state] = (1<<21);
    }
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_WAIT_SCAN] = 0x33B9DACA;
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_OBSS_SCAN] = 0x33B9DACA;
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_BG_SCAN]   = 0x33B9DACA;
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_LISTEN]    = 0x33A9FACA;
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_UP]            = 0x73B9FACA;
#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_ROAMING]       = 0x73B9FACA;
#endif
    for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_WAIT_ASOC; ul_state++)
    {
        g_ast_multi_apup_sta_rx_filter[ul_state] = 0x73B9FACA;
    }

    /* 多STA UP时,AP配置场景:  WLAN_VAP_MODE_BSS_AP    BSS AP模式      */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 保持原有值不配置         | */
    /* | MAC_VAP_STATE_UP                 | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0x73B9EACA               | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x73B9EACA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_ap_rx_filter[ul_state] = 0x73B9FACA;
    }

    g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_INIT] = (1<<21);

#else
    /* Proxy ARP模式下不能过滤重复帧 */
    /*  多STA模式    WLAN_VAP_MODE_BSS_STA          BSS STA模式        */
    /* +----------------------------------+--------------------------+ */
    /* 多AP UP时,STA配置场景:  WLAN_VAP_MODE_BSS_STA   BSS STA模式     */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | ALL STATE                        | 0x33ADEACA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_sta_rx_filter[ul_state] = 0x33ADFACA;
        g_ast_multi_apup_sta_rx_filter[ul_state] = 0x33ADFACA;
    }

    /* WLAN_VAP_MODE_BSS_STA               BSS AP模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0                        | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_ap_rx_filter[ul_state] = (1<<21);
    }

    g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_INIT]             = 0x33B9FADA;
    g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_UP]               = 0x33B9FACA;
    g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9FACA;

#endif
}

#if 0
/*****************************************************************************
 函 数 名  : hmac_rx_filter_init_repeater
 功能描述  : 帧过滤各状态值初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_init_repeater(oal_void)
{
    oal_uint32  ul_state;

    /* WLAN_VAP_MODE_CONFIG,         配置模式 */
    /*                                                          */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT        | 0x37BDEEFA               | */
    /* | All other states          | 0                        | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = 0; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0;
    }

    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_CONFIG][MAC_VAP_STATE_INIT] = 0x37B9EEFA;

    /* WLAN_VAP_MODE_BSS_STA               BSS STA模式(Proxy STA)      */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | all status                       | 0x37ADEACA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x33ADEACA;
    }

    /* WLAN_VAP_MODE_BSS_STA               BSS AP模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0                        | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = 0;
    }

    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0x33B9EADA;
    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x33B9EACA;
    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9EACA;
}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : hmac_rx_filter_init_p2p
 功能描述  : 帧过滤各状态值初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月29日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_init_p2p(oal_void)
{
    oal_uint32  ul_state;

    /* WLAN_VAP_MODE_CONFIG,         配置模式 */
    /*                                                          */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT        | 0x37BDEEFA               | */
    /* | All other states          | 0                        | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = 0; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_CONFIG][MAC_VAP_STATE_INIT] = 0x37B9EEFA;

    /* WLAN_VAP_MODE_BSS_STA               BSS STA模式                 */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_STA_FAKE_UP        | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x37BDCEEA               | */
    /* +----------------------------------+--------------------------+ */

    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x33ADEEDA;//33BDEECA
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_INIT]             = 0x37B9EEFA;/* init 状态不接收帧 */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_UP]               = 0x33B9EEDA;/* up 状态，接收本bss beacon，过滤其他bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_FAKE_UP]      = 0x37B9EEFA;/* fake up状态不接收帧 */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x37B9CEEA;/* scan 状态接收所有beacon帧 */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_LISTEN]       = 0x33ADEECA;/* listen 状态接收其他bss 组播管理帧(probe req) */

    for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_AUTH_COMP; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x37B9EEDA;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_ASOC] = 0x33B9EEDA;/* 等待关联状态，接收本bss beacon，过滤其他bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_OBSS_SCAN] = 0x37B9CEEA;
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_BG_SCAN]   = 0x37B9CEEA;

    /* WLAN_VAP_MODE_BSS_AP                BSS AP模式                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0                        | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = 0;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0x33B9EADA;/* init 状态不接收其他bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x33B9EACA;/* UP 状态TKIP MIC错误的帧不被过滤，密钥寻找失败不过滤，direct控制帧（除CF_END,BA，RTS,CTS,ACK）不过滤，本bss 组播帧不过滤 */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9EACA;/* UP 状态TKIP MIC错误的帧不被过滤，密钥寻找失败不过滤，direct控制帧（除CF_END,BA，RTS,CTS,ACK）不过滤，本bss 组播帧不过滤 */
}
#endif
#endif
/*****************************************************************************
 函 数 名  : hmac_rx_filter_init
 功能描述  : 帧过滤各状态值初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_init(oal_void)
{
    g_en_rx_filter_enable = OAL_TRUE;

    /* Normal模式帧过滤值初始化 */
    hmac_rx_filter_init_single_vap();
    hmac_rx_filter_init_multi_vap();

#if 0
    /* Repeater模式帧过滤值初始化 */
    hmac_rx_filter_init_repeater();

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P 模式帧过滤值初始化 */
    hmac_rx_filter_init_p2p();
#endif
#endif
}

/*****************************************************************************
 函 数 名  : hmac_rx_filter_exit
 功能描述  : 帧过滤退出函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_rx_filter_exit(oal_void)
{
    g_en_rx_filter_enable = OAL_FALSE;
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : hmac_set_rx_filter_en
 功能描述  : hmac设置帧过滤使能开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_set_rx_filter_en(oal_uint8 uc_rx_filter_en)
{
    g_en_rx_filter_enable = uc_rx_filter_en;
}

/*****************************************************************************
 函 数 名  : hmac_get_rx_filter_en
 功能描述  : hmac获取帧过滤使能开关状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_get_rx_filter_en(oal_void)
{
    oal_int8      ac_tmp_buff[200];
    oal_int8     *pac_string[] = {"close", "open", "error"};

    OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "rx filer function is : %s.\n", pac_string[g_en_rx_filter_enable]);
    oam_print(ac_tmp_buff);
}

/*****************************************************************************
 函 数 名  : hmac_set_status_rx_filter_val
 功能描述  : 设置指定状态的帧过滤值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_set_status_rx_filter_val(oal_uint uc_dev_mode, oal_uint uc_vap_mode, oal_uint uc_vap_status, oal_uint32 uc_val)
{
    switch(uc_dev_mode)
    {
        case 0:
            g_ast_single_vap_rx_filter[uc_vap_mode][uc_vap_status] = uc_val;
            break;

        case 1:
            g_ast_multi_staup_sta_rx_filter[uc_vap_status] = uc_val;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_set_status_rx_filter_val::uc_dev_mode is exceed.[%d]}", uc_dev_mode);
            return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_get_status_rx_filter_val
 功能描述  : 获取指定状态的帧过滤值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_get_status_rx_filter_val(oal_uint uc_dev_mode, oal_uint uc_vap_mode, oal_uint uc_vap_status)
{
    oal_uint32    uc_val = 0;
    oal_int8      ac_tmp_buff[200];
    oal_int8     *pac_vapmode2string[]   = {"CONFIG", "STA", "AP", "WDS", "MONITOER", "TEST", "error"};
    oal_int8     *pac_vapstatus2string[] = {"INIT", "UP", "PAUSE", "WAIT_START", "AP_PAUSE",
                                            "FAKE_UP", "WAIT_SCAN", "SCAN_COMP", "WAIT_JOIN", "JOIN_COMP", "WAIT_AUTH_SEQ2",
                                            "WAIT_AUTH_SEQ4", "AUTH_COMP", "STA_WAIT_ASOC", "STA_OBSS_SCAN", "STA_BG_SCAN", "error"};
    switch(uc_dev_mode)
    {
        case 0:
            uc_val = g_ast_single_vap_rx_filter[uc_vap_mode][uc_vap_status];
            break;

        case 1:
            uc_val = g_ast_multi_staup_sta_rx_filter[uc_vap_status];
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_get_status_rx_filter_val::uc_dev_mode is exceed.[%d]}", uc_dev_mode);
            return OAL_FAIL;
    }

    OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "The %s when it is %s status. \r\nThe rx filter value is 0x%08x.\r\n",
                pac_vapmode2string[uc_vap_mode], pac_vapstatus2string[uc_vap_status], uc_val);

    oam_print(ac_tmp_buff);

    return OAL_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

