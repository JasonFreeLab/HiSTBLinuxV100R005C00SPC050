/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_dfx.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年10月16日
  最近修改   :
  功能描述   : wal层dfx相关功能文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月16日
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
#include "wlan_types.h"
#include "wal_dfx.h"
#include "oal_net.h"
#include "oal_cfg80211.h"
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_ext_if.h"
#include "hmac_device.h"
#include "hmac_resource.h"
#include "hmac_ext_if.h"
#include "hmac_vap.h"
#include "hmac_p2p.h"
#include "wal_ext_if.h"
#include "wal_linux_cfg80211.h"
#include "wal_linux_scan.h"
#include "wal_linux_event.h"
#include "wal_ext_if.h"
#include "wal_config.h"
#include "wal_regdb.h"
#include "wal_linux_ioctl.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
#include "plat_pm_wlan.h"
#include "exception_rst.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_DFX_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFR

#define DFR_WAIT_PLAT_FINISH_TIME   (25000) /* 等待平台完成dfr工作的等待时间 */
wal_dfr_info_stru  g_st_dfr_info;         /* DFR异常复位开关 */
oal_int8 *g_auc_dfr_error_type[] = {   \
            "AP",    \
            "STA",   \
            "P2P0",  \
            "GO",  \
            "CLIENT",  \
            "DFR UNKOWN ERR TYPE!!"};

/* 此枚举为g_auc_dfr_error_type字符串的indx集合 */
typedef enum
{
    DFR_ERR_TYPE_AP = 0,
    DFR_ERR_TYPE_STA,
    DFR_ERR_TYPE_P2P,
    DFR_ERR_TYPE_GO,
    DFR_ERR_TYPE_CLIENT,

    DFR_ERR_TYPE_BUTT
} wal_dfr_error_type;
typedef oal_uint8 wal_dfr_error_type_enum_uint8;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
extern struct st_exception_info *g_pst_exception_info;
#else
struct st_exception_info
{
    /* wifi异常触发 */
    oal_work_stru               wifi_excp_worker;
    oal_workqueue_stru         *wifi_exception_workqueue;
    oal_uint32                  wifi_excp_type;
}g_st_exception_info;
struct st_exception_info *g_pst_exception_info = &g_st_exception_info;

struct st_wifi_dfr_callback
{
    void  (*wifi_recovery_complete)(void);
    void  (*notify_wifi_to_recovery)(void);
};
#endif

oal_void wal_dfr_init_param(oal_void);

#endif //_PRE_WLAN_FEATURE_DFR
/*****************************************************************************
  3 函数实现
*****************************************************************************/

#ifdef _PRE_WLAN_FEATURE_DFR
/*****************************************************************************
 函 数 名  : hmac_dfr_kick_all_user
 功能描述  : 剔除vap下面的所有用户（配置vap除外）
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32  wal_dfr_kick_all_user(hmac_vap_stru *pst_hmac_vap)
{
    wal_msg_write_stru              st_write_msg;
    wal_msg_stru                   *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                      ul_err_code;
    oal_int32                       l_ret;
    mac_cfg_kick_user_param_stru   *pst_kick_user_param;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_KICK_USER, OAL_SIZEOF(mac_cfg_kick_user_param_stru));

    /* 设置配置命令参数 */
    pst_kick_user_param = (mac_cfg_kick_user_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_kick_user_param->auc_mac_addr, BROADCAST_MACADDR);

    /* 填写去关联reason code */
    pst_kick_user_param->us_reason_code = MAC_UNSPEC_REASON;

    l_ret = wal_send_cfg_event(pst_hmac_vap->pst_net_device,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_kick_user_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_TRUE,
                               &pst_rsp_msg);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_dfr_kick_all_user::return err code [%d]!}\r\n", l_ret);
        return l_ret;
    }


    /* 处理返回消息 */
    ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
    if(OAL_SUCC != ul_err_code)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_dfr_kick_all_user::hmac start vap fail,err code[%u]!}\r\n", ul_err_code);
        return -OAL_EINVAL;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : hmac_process_p2p_excp
 功能描述  : p2p模式下异常处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_process_p2p_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;
    hmac_device_stru *pst_hmac_dev;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin P2P exception recovery program,del user[num:%d] when P2P state is P2P0[%d]/CL[%d]/GO[%d] .}",
                     pst_mac_vap->us_user_nums,
                     IS_P2P_DEV(pst_mac_vap),
                     IS_P2P_CL(pst_mac_vap),
                     IS_P2P_GO(pst_mac_vap));

    /* 删除用户 */
    wal_dfr_kick_all_user(pst_hmac_vap);

    /* AP模式还是STA模式 */
    if (IS_AP(pst_mac_vap))
    {
        /* vap信息初始化 */
        //hmac_dfr_reinit_ap(pst_hmac_vap);
    }
    else if (IS_STA(pst_mac_vap))
    {
        pst_hmac_dev = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
        if (OAL_PTR_NULL == pst_hmac_dev)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                             "{hmac_process_p2p_excp::pst_hmac_device is null, dev_id[%d].}",
                             pst_mac_vap->uc_device_id);

            return OAL_ERR_CODE_MAC_DEVICE_NULL;
        }
        /* 删除扫描信息列表，停止扫描 */
        if (pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id == pst_mac_vap->uc_vap_id)
        {
            pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.p_fn_cb = OAL_PTR_NULL;
            pst_hmac_dev->st_scan_mgmt.en_is_scanning = OAL_FALSE;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_process_ap_excp
 功能描述  : ap模式下的异常处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_process_ap_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin AP exception recovery program, when AP have [%d] USERs.}",
                     pst_mac_vap->us_user_nums);

    /* 删除用户 */
    wal_dfr_kick_all_user(pst_hmac_vap);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_process_sta_excp
 功能描述  : sta模式下的异常处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_process_sta_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;
    hmac_device_stru *pst_hmac_dev;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    pst_hmac_dev = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                         "{hmac_process_sta_excp::pst_hmac_device is null, dev_id[%d].}",
                         pst_mac_vap->uc_device_id);

        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin sta exception recovery program, when sta have [%d] users.}",
                     pst_mac_vap->us_user_nums);

    /* 关联状态下上报关联失败，删除用户 */
    wal_dfr_kick_all_user(pst_hmac_vap);

    /* 删除扫描信息列表，停止扫描 */
    if (pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id == pst_mac_vap->uc_vap_id)
    {
        pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.p_fn_cb = OAL_PTR_NULL;
        pst_hmac_dev->st_scan_mgmt.en_is_scanning = OAL_FALSE;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : wal_dfr_destroy_vap
 功能描述  : dfr流程中删除vap
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32  wal_dfr_destroy_vap(oal_net_device_stru *pst_netdev)
{
    wal_msg_write_stru           st_write_msg;
    wal_msg_stru                *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                  ul_err_code;

    oal_int32                    l_ret;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DESTROY_VAP, OAL_SIZEOF(oal_int32));
    l_ret = wal_send_cfg_event(pst_netdev,
                        WAL_MSG_TYPE_WRITE,
                        WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                        (oal_uint8 *)&st_write_msg,
                         OAL_TRUE,
                        &pst_rsp_msg);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAL_IO_PRINT("DFR DESTROY_VAP[name:%s] fail, return[%d]!", pst_netdev->name, l_ret);
        OAM_WARNING_LOG2(0, OAM_SF_DFR, "{wal_dfr_excp_process::DESTROY_VAP return err code [%d], iftype[%d]!}\r\n",
                        l_ret,
                        pst_netdev->ieee80211_ptr->iftype);

        return l_ret;
    }

    /* 读取返回的错误码 */
    ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
    if(OAL_SUCC != ul_err_code)
    {
        OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::hmac add vap fail, err code[%u]!}\r\n", ul_err_code);
        return l_ret;
    }

    OAL_NET_DEV_PRIV(pst_netdev) = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_dfr_recovery_env
 功能描述  : 异常恢复部分 恢复所有vap，并上报异常信息
 输入参数  : recovery_flag
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  wal_dfr_recovery_env(oal_int32 recovery_flag)
{
    oal_uint32                    ul_ret;
    oal_int32                     l_ret;
    oal_net_device_stru          *pst_netdev;
    wal_dfr_error_type_enum_uint8 en_err_type = DFR_ERR_TYPE_BUTT;
    oal_wireless_dev_stru        *pst_wireless_dev;


    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_RECV_LASTWORD));
    if (OAL_TRUE != g_st_dfr_info.bit_ready_to_recovery_flag)
    {
        return OAL_SUCC;
    }

    if (EXCEPTION_SUCCESS != recovery_flag)
    {
        OAL_IO_PRINT("DFR EEOR: wait dev reset timeout[%d]!\n", DFR_WAIT_PLAT_FINISH_TIME);
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_process:wait dev reset timeout[%d]", DFR_WAIT_PLAT_FINISH_TIME);
        //return OAL_FAIL;
    }

    /* 恢复vap, 上报异常给上层 */
    for (; g_st_dfr_info.ul_netdev_num > 0; g_st_dfr_info.ul_netdev_num--)
    {
        ul_ret = OAL_SUCC;
        pst_netdev = (oal_net_device_stru *)g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num - 1];

        if (NL80211_IFTYPE_AP == pst_netdev->ieee80211_ptr->iftype)
        {

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
            wal_custom_cali(); /* 1131C-debug */
            hwifi_config_init_force(); /* 1131C-debug */
#endif
            l_ret = wal_cfg_vap_h2d_event(pst_netdev);
            if(OAL_SUCC != l_ret)
            {
                OAL_IO_PRINT("DFR EEOR: Device cfg_vap creat false[%d]!\n", l_ret);
                OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_recovery_env:DFR Device cfg_vap creat false[%d]!", l_ret);
                wal_dfr_init_param();
                return OAL_FAIL;
            }

            /* host device_stru初始化*/
            l_ret = wal_host_dev_init(pst_netdev);
            if(OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_recovery_env::DFR wal_host_dev_init FAIL %d ", l_ret);
            }

            ul_ret = wal_setup_ap(pst_netdev);
            en_err_type = DFR_ERR_TYPE_AP;


        }
        else if ((NL80211_IFTYPE_STATION == pst_netdev->ieee80211_ptr->iftype)||
                (NL80211_IFTYPE_P2P_DEVICE == pst_netdev->ieee80211_ptr->iftype))
        {
            l_ret = wal_netdev_open(pst_netdev);
            en_err_type = (!OAL_STRCMP(pst_netdev->name , "p2p0"))? DFR_ERR_TYPE_P2P : DFR_ERR_TYPE_STA;
        }
        else
        {
            pst_wireless_dev = OAL_NETDEVICE_WDEV(pst_netdev);
            /* 去注册netdev */
            oal_net_unregister_netdev(pst_netdev);
            OAL_MEM_FREE(pst_wireless_dev, OAL_TRUE);
            continue;
        }

        if (OAL_UNLIKELY(OAL_SUCC != l_ret) || OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAL_IO_PRINT("DFR BOOT_VAP[name:%s] fail! error_code[%d]", pst_netdev->name, ((oal_uint8)l_ret | ul_ret));
            OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_dfr_excep_process:: Boot vap Failure, vap_iftype[%d], error_code[%d]!}\r\n",
                            pst_netdev->ieee80211_ptr->iftype,
                            ((oal_uint8)l_ret | ul_ret));
            continue;
        }

        //需要恢复扫描么???
        oal_net_device_open(pst_netdev);

        /* 上报异常 */
        oal_cfg80211_rx_exception(pst_netdev,
                                (oal_uint8 *)g_auc_dfr_error_type[en_err_type],
                                OAL_STRLEN(g_auc_dfr_error_type[en_err_type]));

    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
    wlan_pm_enable();
#endif

    g_st_dfr_info.bit_device_reset_process_flag = OAL_FALSE;
    g_st_dfr_info.bit_ready_to_recovery_flag    = OAL_FALSE;

    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : wal_dfr_excp_process
 功能描述  : device异常，wal侧的处理流程，操作包括删除vap，对device进行重启
             恢复，并重新创建host&device的vap
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_dfr_excp_process(mac_device_stru *pst_mac_device, oal_uint32 ul_exception_type)
{
    hmac_vap_stru               *pst_hmac_vap;
    mac_vap_stru                *pst_mac_vap;
    oal_uint8                    uc_vap_idx;
    oal_int32                    l_ret;

    oal_net_device_stru          *pst_netdev = OAL_PTR_NULL;
    oal_net_device_stru          *pst_p2p0_netdev = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{wal_dfr_excp_process::pst_mac_device is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    //wlan_pm_disable();
    wlan_pm_disable_check_wakeup(OAL_FALSE);
#endif
    OAL_MEMZERO((oal_uint8 *)(g_st_dfr_info.past_netdev), OAL_SIZEOF(g_st_dfr_info.past_netdev[0]) * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT + 1));

    for (uc_vap_idx = pst_mac_device->uc_vap_num, g_st_dfr_info.ul_netdev_num = 0; uc_vap_idx > 0; uc_vap_idx--)
    {
        /* 获取最右边一位为1的位数，此值即为vap的数组下标 */
        pst_hmac_vap    = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx-1]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::mac_res_get_hmac_vap fail!vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }
        pst_mac_vap     = &(pst_hmac_vap->st_vap_base_info);
        pst_netdev      = pst_hmac_vap->pst_net_device;

#ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_DEV(pst_mac_vap))
        {
            pst_netdev = pst_hmac_vap->pst_p2p0_net_device;
        }
        else if (IS_P2P_CL(pst_mac_vap))
        {
            pst_p2p0_netdev = pst_hmac_vap->pst_p2p0_net_device;
            if (OAL_PTR_NULL != pst_p2p0_netdev)
            {
                g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num]  = (oal_uint32 *)pst_p2p0_netdev;
                g_st_dfr_info.ul_netdev_num ++;
            }
        }
#endif
        if (OAL_PTR_NULL == pst_netdev)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::pst_netdev NULL pointer !vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }
        else if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::ieee80211_ptr NULL pointer !vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }

        g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num]  = (oal_uint32 *)pst_netdev;
        g_st_dfr_info.ul_netdev_num ++;

        OAM_WARNING_LOG4(0 , OAM_SF_DFR, "wal_dfr_excp_process:vap_iftype [%d], vap_id[%d], vap_idx[%d], vap_mode_idx[%d]",
                    pst_netdev->ieee80211_ptr->iftype,
                    pst_mac_vap->uc_vap_id,
                    uc_vap_idx,
                    g_st_dfr_info.ul_netdev_num);

        wal_force_scan_complete(pst_netdev, OAL_TRUE);
        oal_net_device_close(pst_netdev);
        l_ret = wal_dfr_destroy_vap(pst_netdev);
        if (OAL_UNLIKELY(OAL_SUCC != l_ret))
        {
            continue;
        }

        if (OAL_PTR_NULL != pst_p2p0_netdev)
        {
            l_ret = wal_dfr_destroy_vap(pst_p2p0_netdev);
            if (OAL_UNLIKELY(OAL_SUCC != l_ret))
            {
                OAM_WARNING_LOG0(0, OAM_SF_DFR, "{wal_dfr_excp_process::DESTROY_P2P0 return err code [%d]!}\r\n");
                oal_net_unregister_netdev(pst_netdev);
                continue;
            }
            pst_p2p0_netdev = OAL_PTR_NULL;
        }

    }


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION))
    l_ret = plat_exception_handler(ul_exception_type);
#endif

    wal_dfr_recovery_env(l_ret);

    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : wal_dfr_excp_rx
 功能描述  : device异常接收总入口，目前用于device挂死，SDIO读写失败等异常
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wal_dfr_excp_rx(oal_uint8 uc_device_id, oal_uint32 ul_exception_type)
{
    oal_uint8                     uc_vap_idx;
    hmac_vap_stru                *pst_hmac_vap;
    mac_vap_stru                 *pst_mac_vap;
    mac_device_stru              *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_rx:ERROR dev_ID[%d] in DFR process!", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*  异常复位开关是否开启 */
    if ((!g_st_dfr_info.bit_device_reset_enable) || g_st_dfr_info.bit_device_reset_process_flag)
    {
        return OAL_SUCC;
    }

    /* log现在进入异常处理流程 */
    OAM_ERROR_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_rx:: Enter the exception processing, type[%d].}", ul_exception_type);

    g_st_dfr_info.bit_device_reset_process_flag = OAL_TRUE;
    g_st_dfr_info.bit_user_disconnect_flag      = OAL_TRUE;

    /* 按照每个vap模式进行异常处理 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_dev->uc_vap_num; uc_vap_idx++)
    {

        /* 获取最右边一位为1的位数，此值即为vap的数组下标 */
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_dev->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_rx::mac_res_get_hmac_vap fail!vap_idx = %u}\r",pst_mac_dev->auc_vap_id[uc_vap_idx]);
            continue;
        }

        pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
        if (!IS_LEGACY_VAP(pst_mac_vap))
        {
            wal_process_p2p_excp(pst_hmac_vap);
        }
        else if (IS_AP(pst_mac_vap))
        {
            wal_process_ap_excp(pst_hmac_vap);
        }
        else if (IS_STA(pst_mac_vap))
        {
            wal_process_sta_excp(pst_hmac_vap);
        }
        else
        {
            continue;
        }

    }

    return wal_dfr_excp_process(pst_mac_dev, ul_exception_type);
}

/*****************************************************************************
 函 数 名  : wal_dfr_excp_work
 功能描述  : excep_worker处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void  wal_dfr_excp_work(void)
{
    oal_uint8  uc_device_id;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        OAL_IO_PRINT("get exception info reference is error\n");
        return ;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        OAL_IO_PRINT("palt exception reset not enable!");
        return ;
    }

    /* 暂不支持多chip，多device */
    if ((1 != WLAN_CHIP_DBSC_DEVICE_NUM) || (1 != WLAN_CHIP_MAX_NUM_PER_BOARD))
    {
        OAM_ERROR_LOG2(0, OAM_SF_DFR, "DFR Can not support muti_chip[%d] or muti_device[%d].\n",
                        WLAN_CHIP_MAX_NUM_PER_BOARD, WLAN_CHIP_DBSC_DEVICE_NUM);
        return;
    }
    uc_device_id = 0;

    wal_dfr_excp_rx(uc_device_id, pst_exception_data->excetion_type);

}

/*****************************************************************************
 函 数 名  : wal_init_dfr_param
 功能描述  : 初始化dfr的相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wal_dfr_init_param(oal_void)
{
    OAL_MEMZERO((oal_uint8 *)&g_st_dfr_info, OAL_SIZEOF(wal_dfr_info_stru));

    g_st_dfr_info.bit_device_reset_enable        = OAL_TRUE;
    g_st_dfr_info.bit_hw_reset_enable            = OAL_FALSE;
    g_st_dfr_info.bit_soft_watchdog_enable       = OAL_FALSE;
    g_st_dfr_info.bit_device_reset_process_flag  = OAL_FALSE;
    g_st_dfr_info.bit_ready_to_recovery_flag     = OAL_FALSE;
    g_st_dfr_info.bit_user_disconnect_flag       = OAL_FALSE;
    g_st_dfr_info.ul_excp_type                   = 0xffffffff;

}

/*****************************************************************************
 函 数 名  : wal_init_dev_excp_handler
 功能描述  : 初始化device异常的各种设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 wal_dfr_excp_init_handler(oal_void)
{
    hmac_device_stru     *pst_hmac_dev;

    pst_hmac_dev = hmac_res_get_mac_dev(0);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_init_dev_excp_handler:ERROR hmac dev_ID[%d] in DFR process!", 0);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化dfr开关 */
    wal_dfr_init_param();
    g_pst_exception_info->wifi_dfr_func = wal_dfr_excp_work;
    OAM_WARNING_LOG0(0, OAM_SF_DFR, "DFR wal_init_dev_excp_handler init ok.\n");
    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : wal_dfr_excp_exit_handler
 功能描述  :  退出dfr netlink
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void wal_dfr_excp_exit_handler(oal_void)
{
    hmac_device_stru     *pst_hmac_dev;

    pst_hmac_dev = hmac_res_get_mac_dev(0);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_exit_handler:ERROR dev_ID[%d] in DFR process!", 0);
        return;
    }

    OAM_WARNING_LOG0(0, OAM_SF_DFR, "wal_dfr_excp_exit_handler::DFR dev_excp_handler remove ok.");

}
#else
oal_uint32 wal_dfr_excp_rx(oal_uint8 uc_device_id, oal_uint32 ul_exception_type)
{
    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_DFR


oal_uint32 wal_dfx_init(oal_void)
{
    oal_uint32      l_ret = OAL_SUCC;

#ifdef _PRE_WLAN_FEATURE_DFR
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    //genKernel_init();
    l_ret = init_dev_excp_handler();
    if (OAL_SUCC != l_ret)
    {
        return l_ret;
    }
#endif
    l_ret = wal_dfr_excp_init_handler();
#endif //_PRE_WLAN_FEATURE_DFR

    return l_ret;
}

oal_void wal_dfx_exit(oal_void)
{

#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfr_excp_exit_handler();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)  || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    //genKernel_exit();
    deinit_dev_excp_handler();
#endif
#endif //_PRE_WLAN_FEATURE_DFR

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

