/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_data_acq.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年4月25日
  最近修改   :
  功能描述   : hmac数据采集功能
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "wlan_spec.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "hmac_data_acq.h"
#include "hmac_config.h"
#include "hmac_vap.h"
#include "hmac_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DATA_ACQ_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

oal_uint8 g_uc_data_acq_used = OAL_FALSE;



/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hmac_data_acq_init
 功能描述  : 数据采集功能Hmac初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_data_acq_init(oal_void)
{
    g_uc_data_acq_used = OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_data_acq_exit
 功能描述  : 数据采集功能Hmac退出
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_data_acq_exit(oal_void)
{
    g_uc_data_acq_used = OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_data_acq_down_vap
 功能描述  : 使能数采将VAP down掉
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_data_acq_down_vap(mac_vap_stru *pst_mac_vap)
{
    oal_uint32                   ul_ret;
    mac_device_stru             *pst_device;
    oal_uint8                    uc_vap_idx;
    mac_cfg_down_vap_param_stru  st_down_vap;
    hmac_vap_stru               *pst_hmac_vap;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_data_acq_down_vap::pst_device null.}");
        return;
    }

    /* 遍历device下所有vap，设置vap 下的信道号 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_hmac_vap = mac_res_get_hmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_data_acq_down_vap::pst_hmac_vap null.}");
            continue;
        }

        st_down_vap.pst_net_dev = pst_hmac_vap->pst_net_device;

        ul_ret = hmac_config_down_vap(&pst_hmac_vap->st_vap_base_info, OAL_SIZEOF(mac_cfg_down_vap_param_stru), (oal_uint8 *)&st_down_vap);

        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_data_acq_down_vap::hmac_config_down_vap failed.}");
        }
    }

    g_uc_data_acq_used = OAL_TRUE;
    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_data_acq_down_vap::g_uc_data_acq_used=%d.}", g_uc_data_acq_used);
}


#endif  /* end of _PRE_WLAN_FEATURE_DAQ*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

