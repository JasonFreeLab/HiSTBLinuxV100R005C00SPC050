/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_smps.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年4月17日
  最近修改   :
  功能描述   : SMPS hmac接口
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月17日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "hmac_smps.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_SMPS_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_smps_all_vap_update
 功能描述  : AP侧接收到对应STA的关联请求消息
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
oal_void hmac_smps_all_vap_update(mac_device_stru *pst_mac_device, wlan_mib_mimo_power_save_enum_uint8 en_smps_mode)
{
    mac_vap_stru                         *pst_mac_vap = OAL_PTR_NULL;
    oal_uint8                             uc_vap_idx;

    /* 遍历device下所有vap，设置vap 下的信道号 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_CFG, "{hmac_smps_all_vap_update::pst_mac_vap null.}");
            continue;
        }

        if (OAL_TRUE != pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
        {
            continue;
        }
        /* 信道设置只针对AP模式，非AP模式则跳出 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            /* STA暂时不开发 */
            /* 设置STA的SMPS能力，并发送SM Power Save Frame帧 */
            continue;
        }

        /* 设置VAP的当前SMPS模式 */
        pst_mac_vap->st_cap_flag.bit_smps = en_smps_mode;
    }
}

/*****************************************************************************
 函 数 名  : hmac_smps_update_status
 功能描述  : AP侧接收到对应STA的关联请求消息
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
oal_uint32 hmac_smps_update_status(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_plus_user)
{
    mac_device_stru                        *pst_mac_device;
    wlan_mib_mimo_power_save_enum_uint8     en_user_smps_mode;
    frw_event_mem_stru                     *pst_event_mem;
    frw_event_stru                         *pst_event;
    oal_uint32                              ul_ret;
    oal_bool_enum_uint8                     en_ht_cap;
    mac_cfg_smps_mode_stru                  st_smps_mode = {0};

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SMPS, "{hmac_smps_update_status: NULL PTR pst_mac_vap is [%d] and pst_mac_user is [%d].}", pst_mac_vap, pst_mac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{hmac_smps_update_status: pst_mac_vap is mimo.}");
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{hmac_smps_update_status: pst_mac_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_smps_mode.uc_smps_mode = WLAN_MIB_MIMO_POWER_SAVE_BUTT;
    st_smps_mode.us_user_idx = 0;

    en_user_smps_mode = (wlan_mib_mimo_power_save_enum_uint8)pst_mac_user->st_ht_hdl.bit_sm_power_save;
    en_ht_cap = (oal_bool_enum_uint8)pst_mac_user->st_ht_hdl.en_ht_capable;

    if (OAL_TRUE == en_plus_user)
    {
        if ((OAL_TRUE == en_ht_cap) && (WLAN_MIB_MIMO_POWER_SAVE_MIMO != en_user_smps_mode))
        {
            /* 如果不是第一个用户，则直接返回 */
            if (1 < pst_mac_device->uc_asoc_user_cnt)
            {
                return OAL_SUCC;
            }
            /* 如果是第一个用户，则进入SMPS模式 */
            /* 设置SMPS模式信息 mib值 */
            st_smps_mode.uc_smps_mode = (oal_uint8)pst_mac_vap->st_cap_flag.bit_smps;
        }
        else
        {
            pst_mac_device->uc_no_smps_user_cnt++;
            if (OAL_FALSE == pst_mac_device->en_smps)
            {
                return OAL_SUCC;
            }
            /* 设置SMPS模式disable */
            st_smps_mode.uc_smps_mode = WLAN_MIB_MIMO_POWER_SAVE_MIMO;
            hmac_smps_all_vap_update(pst_mac_device, WLAN_MIB_MIMO_POWER_SAVE_MIMO);
        }
     }
     else
     {
         if ((OAL_TRUE == en_ht_cap) && (WLAN_MIB_MIMO_POWER_SAVE_MIMO != en_user_smps_mode))
         {
             return OAL_SUCC;
         }

         if (0 < pst_mac_device->uc_no_smps_user_cnt)
         {
             pst_mac_device->uc_no_smps_user_cnt--;
         }

         if ((0 == pst_mac_device->uc_no_smps_user_cnt) && (OAL_FALSE == pst_mac_device->en_smps))
         {
             /* 设置SMPS模式信息 mib值 */
             st_smps_mode.uc_smps_mode = mac_mib_get_smps(pst_mac_vap);
             hmac_smps_all_vap_update(pst_mac_device, mac_mib_get_smps(pst_mac_vap));
         }
         else
         {
             return OAL_SUCC;
         }
     }


     /* 抛事件到DMAC, 申请事件内存 */
     pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(st_smps_mode));
     if (OAL_PTR_NULL == pst_event_mem)
     {
         OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{hmac_smps_update_status: FRW_EVENT_ALLOC fail.}");
         return OAL_ERR_CODE_PTR_NULL;
     }

     ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_mac_user->auc_user_mac_addr, &(st_smps_mode.us_user_idx));

     /* 查找用户失败或没有找到对应的用户 */
     if (OAL_SUCC != ul_ret)
     {
         OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{hmac_smps_update_status::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
         return ul_ret;
     }

     /* 填写事件 */
     pst_event = (frw_event_stru *)pst_event_mem->puc_data;

     FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_WLAN_CTX,
                        DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_SMPS,
                        OAL_SIZEOF(st_smps_mode),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

     /* 拷贝参数 */
     oal_memcopy(pst_event->auc_event_data, (oal_void *)&st_smps_mode, OAL_SIZEOF(st_smps_mode));

     /* 分发事件 */
     ul_ret = frw_event_dispatch_event(pst_event_mem);
     if (OAL_SUCC != ul_ret)
     {
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
     }

     FRW_EVENT_FREE(pst_event_mem);

     return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_smps_update_status
 功能描述  : AP侧接收到对应STA的关联请求消息
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
oal_uint32 hmac_smps_user_asoc_update(oal_uint8 uc_prev_smps_mode, mac_user_stru *pst_mac_user, mac_vap_stru *pst_mac_vap)
{

    /* 第一次关联请求 */
    if (0 == uc_prev_smps_mode)
    {
        if (OAL_FALSE == pst_mac_user->st_ht_hdl.en_ht_capable)
        {
            mac_user_set_sm_power_save(pst_mac_user, WLAN_MIB_MIMO_POWER_SAVE_MIMO);
        }

        hmac_smps_update_status((pst_mac_vap), pst_mac_user, OAL_TRUE);
    }
    /* 第N次关联请求 由MIMO->DYNAMIC STATIC */
    else if (uc_prev_smps_mode == WLAN_MIB_MIMO_POWER_SAVE_MIMO)
    {
        if ((WLAN_MIB_MIMO_POWER_SAVE_DYNAMIC == pst_mac_user->st_ht_hdl.bit_sm_power_save)
            || (WLAN_MIB_MIMO_POWER_SAVE_STATIC == pst_mac_user->st_ht_hdl.bit_sm_power_save))
        {
            uc_prev_smps_mode = (oal_uint8)pst_mac_user->st_ht_hdl.bit_sm_power_save;
            mac_user_set_sm_power_save(pst_mac_user, WLAN_MIB_MIMO_POWER_SAVE_MIMO);
            hmac_smps_update_status(pst_mac_vap, pst_mac_user, OAL_FALSE);
            mac_user_set_sm_power_save(pst_mac_user, uc_prev_smps_mode);
        }
    }
    /* 第N次关联请求 由DYNAMIC STATIC -> MIMO */
    else
    {
        if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == pst_mac_user->st_ht_hdl.bit_sm_power_save)
        {
            hmac_smps_update_status(pst_mac_vap, pst_mac_user, OAL_TRUE);
        }
    }

    return OAL_SUCC;
}


#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

