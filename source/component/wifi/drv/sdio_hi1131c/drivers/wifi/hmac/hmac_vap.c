/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_vap.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
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
#include "oal_net.h"
#include "oam_ext_if.h"

#include "wlan_spec.h"

#include "mac_ie.h"

#include "frw_event_main.h"

#include "hmac_vap.h"
#include "hmac_resource.h"
#include "hmac_tx_amsdu.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_fsm.h"
#include "hmac_ext_if.h"
#include "hmac_chan_mgmt.h"

#include "hmac_edca_opt.h"
#ifdef _PRE_WLAN_FEATURE_MCAST
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif
#include "hmac_blockack.h"
#include "hmac_p2p.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt.h"
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif

#include "hmac_mgmt_sta.h"
#include "hmac_mgmt_ap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_VAP_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define HMAC_NETDEVICE_WDT_TIMEOUT      (5*OAL_TIME_HZ)

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    OAL_STATIC oal_net_device_ops_stru gst_vap_net_dev_cfg_vap_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) || (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
        /* TBD */
#else
        .ndo_get_stats          = oal_net_device_get_stats,
        .ndo_open               = oal_net_device_open,
        .ndo_stop               = oal_net_device_close,
        .ndo_start_xmit         = OAL_PTR_NULL,
        .ndo_set_multicast_list = OAL_PTR_NULL,
        .ndo_do_ioctl           = oal_net_device_ioctl,
        .ndo_change_mtu         = oal_net_device_change_mtu,
        .ndo_init               = oal_net_device_init,
        .ndo_set_mac_address    = oal_net_device_set_macaddr
#endif
    };
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    OAL_STATIC oal_net_device_ops_stru gst_vap_net_dev_cfg_vap_ops = {
         oal_net_device_init,
         oal_net_device_open,
         oal_net_device_close,
         OAL_PTR_NULL,
         OAL_PTR_NULL,
         oal_net_device_get_stats,
         oal_net_device_ioctl,
         oal_net_device_change_mtu,
         oal_net_device_set_macaddr};
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void hmac_del_virtual_inf_worker(oal_work_stru *pst_del_virtual_inf_work);
#endif


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_vap_init
 功能描述  : 初始化要添加的hmac vap的一些特性信息
 输入参数  : 指向要添加的vap的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_init(
                hmac_vap_stru              *pst_hmac_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param)
{
    oal_uint32      ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_init::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    OAM_WARNING_LOG2(uc_vap_id, OAM_SF_ANY, "hmac_vap_init, uc_vap_id[%d], vap_mode[%d]\n",uc_vap_id,pst_param->en_vap_mode);

    ul_ret = mac_vap_init(&pst_hmac_vap->st_vap_base_info,
                          uc_chip_id,
                          uc_device_id,
                          uc_vap_id,
                          pst_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANY, "{hmac_vap_init::mac_vap_init failed[%d].}", ul_ret);
        return ul_ret;
    }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    /* 统计信息清零 */
    oam_stats_clear_vap_stat_info(uc_vap_id);
#endif

    /* 初始化预设参数 */
    pst_hmac_vap->st_preset_para.en_protocol   = pst_hmac_vap->st_vap_base_info.en_protocol;
    pst_hmac_vap->st_preset_para.en_bandwidth  = pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth;
    pst_hmac_vap->st_preset_para.en_band       = pst_hmac_vap->st_vap_base_info.st_channel.en_band;
    /* 初始化配置私有结构体 */
    //对于P2P CL 不能再初始化队列
    pst_hmac_vap->st_cfg_priv.dog_tag = OAL_DOG_TAG;
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_vap->st_cfg_priv.st_wait_queue_for_sdt_reg));
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_vap->st_mgmt_tx.st_wait_queue));

    /* 默认设置为自动触发BA回话的建立 */
    pst_hmac_vap->en_addba_mode = HMAC_ADDBA_MODE_AUTO;

    /* 1151默认不amsdu ampdu 联合聚合功能不开启 1102用于小包优化
     * 因tplink/syslink下行冲包兼容性问题，先关闭02的ampdu+amsdu
     */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_hmac_vap->en_amsdu_ampdu_active = OAL_FALSE;
#else
    pst_hmac_vap->en_amsdu_ampdu_active = OAL_FALSE;
#endif
    pst_hmac_vap->en_ampdu_tx_on_switch = OAL_TRUE;

    /* 初始化MIC faile 状态 */
    //pst_hmac_vap->en_mic_faile_in_progress = OAL_FALSE;

    /* 初始化认证类型为OPEN */
    pst_hmac_vap->en_auth_mode                 = WLAN_WITP_AUTH_OPEN_SYSTEM;
    pst_hmac_vap->uc_80211i_mode               = OAL_FALSE;
    pst_hmac_vap->en_psm_active                = WLAN_FEATURE_PSM_IS_OPEN;
    pst_hmac_vap->en_wme_active                = WLAN_FEATURE_WME_IS_OPEN;
    pst_hmac_vap->en_msdu_defrag_active        = WLAN_FEATURE_MSDU_DEFRAG_IS_OPEN;
    /* 2040共存信道切换开关初始化 */
    pst_hmac_vap->en_2040_switch_prohibited    = OAL_FALSE;
    pst_hmac_vap->en_wps_active                = OAL_FALSE;

    /*设置vap最大用户数*/
    pst_hmac_vap->us_user_nums_max = WLAN_ASSOC_USER_MAX_NUM_SPEC;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_hmac_vap->uc_rx_ba_session_num = 0;
    pst_hmac_vap->uc_tx_ba_session_num = 0;
#endif

#ifdef _PRE_WLAN_FEATURE_11D
    pst_hmac_vap->en_updata_rd_by_ie_switch = OAL_FALSE;
#endif
    OAL_WAIT_QUEUE_INIT_HEAD(&pst_hmac_vap->query_wait_q);
    /* 根据配置VAP，将对应函数挂接在业务VAP，区分AP、STA和WDS模式 */
    switch(pst_param->en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            /* 执行特性初始化vap的函数 */
        #ifdef _PRE_WLAN_FEATURE_AMSDU
            pst_hmac_vap->en_amsdu_active = OAL_FALSE;
        #endif
         /* 组播转单播初始化函数 */
        #ifdef _PRE_WLAN_FEATURE_MCAST
            hmac_m2u_attach(pst_hmac_vap);
        #endif

        #ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_vap->ul_edca_opt_time_ms       = HMAC_EDCA_OPT_TIME_MS;
            FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_edca_opt_timer), hmac_edca_opt_timeout_fn, pst_hmac_vap->ul_edca_opt_time_ms, pst_hmac_vap, OAL_TRUE, OAM_MODULE_ID_ALG_SCHEDULE, pst_hmac_vap->st_vap_base_info.ul_core_id);
            /* also open for 1102 at 2015-10-16 */
            pst_hmac_vap->uc_edca_opt_flag_ap       = 1;
            FRW_TIMER_RESTART_TIMER(&(pst_hmac_vap->st_edca_opt_timer), pst_hmac_vap->ul_edca_opt_time_ms, OAL_TRUE);
        #endif

        #ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
            pst_hmac_vap->uc_tx_traffic_classify_flag = OAL_SWITCH_ON;  /* AP模式默认业务识别功能开启 */
        #endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */
            break;

        case WLAN_VAP_MODE_BSS_STA:
             /* 组播转单播初始化函数 */
        #ifdef _PRE_WLAN_FEATURE_MCAST
            hmac_m2u_attach(pst_hmac_vap);
        #endif

        #ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
            pst_hmac_vap->uc_edca_opt_flag_sta = 0;
            pst_hmac_vap->uc_edca_opt_weight_sta    = WLAN_EDCA_OPT_WEIGHT_STA;
        #endif

        #ifdef _PRE_WLAN_FEATURE_DFS
            mac_mib_set_SpectrumManagementImplemented(&pst_hmac_vap->st_vap_base_info, OAL_TRUE);
        #endif
            pst_hmac_vap->bit_sta_protocol_cfg = OAL_SWITCH_OFF;
        #ifdef _PRE_WLAN_FEATURE_STA_PM
            pst_hmac_vap->uc_cfg_sta_pm_manual = 0xFF;
        #endif

        #ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
            pst_hmac_vap->uc_tx_traffic_classify_flag = OAL_SWITCH_ON;  /* STA模式默认业务识别功能开启 */
        #endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */
            break;

        case WLAN_VAP_MODE_WDS:
            break;

        case WLAN_VAP_MODE_CONFIG:
            /* 配置VAP直接返回 */
            return OAL_SUCC;

        default:
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_init::unsupported mod=%d.}", pst_param->en_vap_mode);
            return OAL_ERR_CODE_INVALID_CONFIG;
    }

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    OAL_NETBUF_QUEUE_HEAD_INIT(&(pst_hmac_vap->st_tx_queue_head[0]));
    OAL_NETBUF_QUEUE_HEAD_INIT(&(pst_hmac_vap->st_tx_queue_head[1]));
    pst_hmac_vap->uc_in_queue_id  = 0;
    pst_hmac_vap->uc_out_queue_id = 1;
    oal_atomic_set(&pst_hmac_vap->ul_tx_event_num,1);  /* ul_tx_event_num初始值修改为1，防止hmac_tx_post_event可能连续抛两个以上事件 */
    pst_hmac_vap->ul_tx_quata = 256;  /* ，将quata从1修改为256,目的是防止小包下行流量低,四个vap流量为0及内存泄露问题可以通过提高事件优先级解决 */
    oal_spin_lock_init(&pst_hmac_vap->st_smp_lock);
#endif

    oal_spin_lock_init(&pst_hmac_vap->st_lock_state);
    /* 创建vap时 初始状态为init */
    mac_vap_state_change(&(pst_hmac_vap->st_vap_base_info), MAC_VAP_STATE_INIT);

    /* 初始化重排序超时时间 */
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_BK] = HMAC_BA_RX_BK_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_BE] = HMAC_BA_RX_BE_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_VI] = HMAC_BA_RX_VI_TIMEOUT;
    pst_hmac_vap->us_rx_timeout[WLAN_WME_AC_VO] = HMAC_BA_RX_VO_TIMEOUT;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* 初始化删除虚拟网络接口工作队列 */
    OAL_INIT_WORK(&(pst_hmac_vap->st_del_virtual_inf_worker), hmac_del_virtual_inf_worker);
    pst_hmac_vap->pst_del_net_device    = OAL_PTR_NULL;
    pst_hmac_vap->pst_p2p0_net_device   = OAL_PTR_NULL;
#endif
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_vap->st_hamc_tcp_ack[HCC_TX].filter_info.ul_ack_limit = DEFAULT_TX_TCP_ACK_THRESHOLD;
    pst_hmac_vap->st_hamc_tcp_ack[HCC_RX].filter_info.ul_ack_limit = DEFAULT_RX_TCP_ACK_THRESHOLD;
    hmac_tcp_opt_init_filter_tcp_ack_pool(pst_hmac_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    hmac_roam_init(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_vap_get_priv_cfg
 功能描述  : 获取hmac_vap结构体中的私有配置项
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_get_priv_cfg(mac_vap_stru *pst_mac_vap, hmac_vap_cfg_priv_stru **ppst_cfg_priv)
{
    hmac_vap_stru   *pst_hmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_get_priv_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_vap_get_priv_cfg::mac_res_get_hmac_vap fail.vap_id = %u}",pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }


    *ppst_cfg_priv = &pst_hmac_vap->st_cfg_priv;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_vap_get_desired_country
 功能描述  : 读取期望的国家
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int8*  hmac_vap_get_desired_country(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{hmac_vap_get_desired_country::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    return pst_hmac_vap->ac_desired_country;
}
#ifdef _PRE_WLAN_FEATURE_11D
/*****************************************************************************
 函 数 名  : hmac_vap_get_updata_rd_by_ie_switch
 功能描述  : 读取是否根据关联ap更新国家码信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_get_updata_rd_by_ie_switch(oal_uint8 uc_vap_id,oal_bool_enum_uint8 *us_updata_rd_by_ie_switch)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(0);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_get_updata_rd_by_ie_switch::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    *us_updata_rd_by_ie_switch = pst_hmac_vap->en_updata_rd_by_ie_switch;
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : hmac_vap_get_net_device
 功能描述  : 通过vap id获取 net_device
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_net_device_stru  *hmac_vap_get_net_device(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{hmac_vap_get_net_device::pst_hmac_vap null.}");
        return OAL_PTR_NULL;
    }

    return (pst_hmac_vap->pst_net_device);
}


/*****************************************************************************
 函 数 名  : hmac_vap_set_puc_asoc_req_ie_buff_null
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_set_asoc_req_ie_ptr_null(oal_uint8 uc_vap_id)
{
    hmac_vap_stru   *pst_hmac_vap;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);


    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ASSOC, "{hmac_vap_set_asoc_req_ie_ptr_null::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_vap_creat_netdev
 功能描述  : 获取hmac_vap结构体中的私有配置项
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_creat_netdev(hmac_vap_stru *pst_hmac_vap, oal_int8 *puc_netdev_name, oal_int8 *puc_mac_addr)

{
    oal_net_device_stru *pst_net_device;
    oal_uint32           ul_return;
    mac_vap_stru        *pst_vap;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_netdev_name)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_vap_creat_netdev::param null %d %d.}", pst_hmac_vap, puc_netdev_name);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap = &pst_hmac_vap->st_vap_base_info;

    pst_net_device = oal_net_alloc_netdev(0, puc_netdev_name, oal_ether_setup);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_device))
    {
        MAC_WARNING_LOG(pst_vap->uc_vap_id, "mac_device_init:p_vap_netdev_alloc return fail.");
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_vap_creat_netdev::pst_net_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如下对netdevice的赋值暂时按如下操作 */
    OAL_NETDEVICE_OPS(pst_net_device)             = &gst_vap_net_dev_cfg_vap_ops;
    OAL_NETDEVICE_DESTRUCTOR(pst_net_device)      = oal_net_free_netdev;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /* TBD  need to check the net device diff*/
#else
    OAL_NETDEVICE_MASTER(pst_net_device)          = OAL_PTR_NULL;
#endif

    OAL_NETDEVICE_IFALIAS(pst_net_device)         = OAL_PTR_NULL;
    OAL_NETDEVICE_WATCHDOG_TIMEO(pst_net_device)  = HMAC_NETDEVICE_WDT_TIMEOUT;
    oal_memcopy(OAL_NETDEVICE_MAC_ADDR(pst_net_device), puc_mac_addr, WLAN_MAC_ADDR_LEN);
    OAL_NET_DEV_PRIV(pst_net_device) = pst_vap;
    OAL_NETDEVICE_QDISC(pst_net_device, OAL_PTR_NULL);

    ul_return = (oal_uint32)oal_net_register_netdev(pst_net_device);
    if (OAL_UNLIKELY(OAL_SUCC != ul_return))
    {
        MAC_WARNING_LOG(pst_vap->uc_vap_id, "mac_device_init:oal_net_register_netdev return fail.");
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_vap_creat_netdev::oal_net_register_netdev failed.}");

        return ul_return;
    }

    pst_hmac_vap->pst_net_device = pst_net_device;
    /* 包括'\0' */
    oal_memcopy(pst_hmac_vap->auc_name,pst_net_device->name,OAL_IF_NAME_SIZE);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_vap_destroy
 功能描述  : 销毁hmac vap的处理函数
 输入参数  : 指向要销毁的vap指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_vap_destroy(hmac_vap_stru *pst_hmac_vap)
{
    mac_cfg_down_vap_param_stru   st_down_vap;
    mac_cfg_del_vap_param_stru    st_del_vap_param;
    oal_uint32                    ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_vap_destroy::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_hmac_vap->uc_edca_opt_flag_ap   = 0;
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_vap->st_edca_opt_timer));
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_hmac_vap->uc_edca_opt_flag_sta = 0;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    hmac_roam_exit(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    /* 先down vap */
#ifdef _PRE_WLAN_FEATURE_P2P
    st_down_vap.en_p2p_mode = pst_hmac_vap->st_vap_base_info.en_p2p_mode;
#endif
    st_down_vap.pst_net_dev = pst_hmac_vap->pst_net_device;
    ul_ret = hmac_config_down_vap(&pst_hmac_vap->st_vap_base_info,
                                  OAL_SIZEOF(mac_cfg_down_vap_param_stru),
                                  (oal_uint8 *)&st_down_vap);
    if (ul_ret != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_destroy::hmac_config_down_vap failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 然后再delete vap */
    st_del_vap_param.en_p2p_mode = pst_hmac_vap->st_vap_base_info.en_p2p_mode;
    st_del_vap_param.en_vap_mode = pst_hmac_vap->st_vap_base_info.en_vap_mode;
    ul_ret = hmac_config_del_vap(&pst_hmac_vap->st_vap_base_info,
                        OAL_SIZEOF(mac_cfg_del_vap_param_stru),
                        (oal_uint8 *)&st_del_vap_param);
    if (ul_ret != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_vap_destroy::hmac_config_del_vap failed[%d].}", ul_ret);
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************

 函 数 名  : hmac_vap_check_ht_capabilities_ap
 功能描述  : 检查请求关联的STA的 HT Capabilities element
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_vap_check_ht_capabilities_ap(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                   *pst_hmac_user_sta)
{
    oal_uint16              us_index        = us_info_elem_offset;
    oal_bool_enum           en_prev_asoc_ht = OAL_FALSE;
    oal_bool_enum           en_prev_asoc_non_ht = OAL_FALSE;
    mac_user_ht_hdl_stru   *pst_ht_hdl      = &(pst_hmac_user_sta->st_user_base_info.st_ht_hdl);
    hmac_amsdu_stru        *pst_amsdu;
    oal_uint32              ul_amsdu_idx;
    mac_protection_stru    *pst_protection;
    oal_uint8               uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8               uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(&pst_hmac_vap->st_vap_base_info))
    {
        return MAC_SUCCESSFUL_STATUSCODE;
    }
    /* 检查STA是否是作为一个HT capable STA与AP关联 */
    if ((MAC_USER_STATE_ASSOC == pst_hmac_user_sta->st_user_base_info.en_user_asoc_state) && (OAL_TRUE == pst_ht_hdl->en_ht_capable))
    {
        mac_user_set_ht_capable(&(pst_hmac_user_sta->st_user_base_info), OAL_FALSE);
        en_prev_asoc_ht = OAL_TRUE;
    }

    /* 检查STA是否是作为一个non HT capable STA与AP关联 */
    else if (MAC_USER_STATE_ASSOC == pst_hmac_user_sta->st_user_base_info.en_user_asoc_state)
    {
        en_prev_asoc_non_ht = OAL_TRUE;
    }
    else
    {

    }

    /* 在关联请求帧中搜索 HT Capabilities Element */
    while (us_index < (ul_msg_len - WLAN_HDR_FCS_LENGTH))
    {
        if (puc_payload[us_index] == MAC_EID_HT_CAP)
        {
            /* 不允许HT STA 使用 TKIP/WEP 加密 */
            if (mac_is_wep_enabled(&pst_hmac_vap->st_vap_base_info))
            {
                OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_ht_capabilities_ap::Rejecting a HT STA because of its Pairwise Cipher[%d].}",
                                 pst_hmac_user_sta->st_user_base_info.st_key_info.en_cipher_type);
                return MAC_MISMATCH_HTCAP;
            }
            uc_pcip_policy = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested;
            uc_grp_policy  = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested;

            if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pcip_policy)
            {
                OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_ht_capabilities_ap::HT STA with TKIP Pairwise Cipher,uc_pcip_policy=%d uc_grp_policy=%d.}",
                                 uc_pcip_policy, uc_grp_policy);
                break;
            }

            /* 搜索 HT Capabilities Element */
            hmac_search_ht_cap_ie_ap(pst_hmac_vap, pst_hmac_user_sta, puc_payload, us_index, en_prev_asoc_ht);

            break;
        }
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
        else if (puc_payload[us_index] == MAC_EID_EXT_CAPS)
        {
            mac_ie_proc_ext_cap_ie(&(pst_hmac_user_sta->st_user_base_info), &puc_payload[us_index]);
        }
#endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

        /* 通过IE长度增加索引值 */
        us_index += puc_payload[us_index + 1] + MAC_IE_HDR_LEN;
    }

    /*走到这里，说明sta已经被统计到ht相关的统计量中*/
    pst_hmac_user_sta->st_user_stats_flag.bit_no_ht_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_gf_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_20M_only_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_lsig_txop_stats_flag = OAL_TRUE;
    pst_hmac_user_sta->st_user_stats_flag.bit_no_40dsss_stats_flag = OAL_TRUE;

    pst_protection = &(pst_hmac_vap->st_vap_base_info.st_protection);
    if (OAL_FALSE == pst_ht_hdl->en_ht_capable) /*STA不支持HT*/
    {
        /*  如果STA之前没有与AP关联*/
        if (MAC_USER_STATE_ASSOC != pst_hmac_user_sta->st_user_base_info.en_user_asoc_state)
        {
            pst_protection->uc_sta_non_ht_num++;
        }
        /*如果STA之前已经作为HT站点与AP关联*/
        else if (OAL_TRUE == en_prev_asoc_ht)
        {
            pst_protection->uc_sta_non_ht_num++;

            if ((OAL_FALSE == pst_ht_hdl->bit_supported_channel_width) && (0 != pst_protection->uc_sta_20M_only_num))
            {
                pst_protection->uc_sta_20M_only_num--;
            }

            if ((OAL_FALSE == pst_ht_hdl->bit_ht_green_field) && (0 != pst_protection->uc_sta_non_gf_num))
            {
                pst_protection->uc_sta_non_gf_num--;
            }

            if ((OAL_FALSE == pst_ht_hdl->bit_lsig_txop_protection) && (0 != pst_protection->uc_sta_no_lsig_txop_num))
            {
                pst_protection->uc_sta_no_lsig_txop_num--;
            }
        }
        else /*STA 之前已经作为非HT站点与AP关联*/
        {
        }
    }
    else  /*STA支持HT*/
    {
        for (ul_amsdu_idx = 0; ul_amsdu_idx < WLAN_WME_MAX_TID_NUM; ul_amsdu_idx++)
        {
            pst_amsdu = &(pst_hmac_user_sta->ast_hmac_amsdu[ul_amsdu_idx]);
            hmac_amsdu_set_maxsize(pst_amsdu, pst_hmac_user_sta, 7936);
            hmac_amsdu_set_maxnum(pst_amsdu, WLAN_AMSDU_MAX_NUM);
            oal_spin_lock_init(&pst_amsdu->st_amsdu_lock);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            pst_amsdu->uc_short_pkt_num = 0x00;
#endif
        }

        /* 设置amsdu域 */
        pst_hmac_user_sta->uc_amsdu_supported = 255;

        /*  如果STA之前已经以non-HT站点与AP关联, 则将uc_sta_non_ht_num减1*/
        if ((OAL_TRUE == en_prev_asoc_non_ht) && (0 != pst_protection->uc_sta_non_ht_num))
        {
            pst_protection->uc_sta_non_ht_num--;
        }
    }

    return MAC_SUCCESSFUL_STATUSCODE;
}

/*****************************************************************************

 函 数 名  : hmac_vap_check_vht_capabilities_ap
 功能描述  : 检查请求关联的STA的 VHT Capabilities element
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 hmac_vap_check_vht_capabilities_ap(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                  *pst_hmac_user_sta)
{
    oal_uint8              *puc_vht_cap_ie;
    mac_vap_stru           *pst_mac_vap;
    mac_user_stru          *pst_mac_user;
    oal_uint8               uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8               uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    if (OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == puc_payload || OAL_PTR_NULL == pst_hmac_user_sta)
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::param null,%d %d %d.}",
                                 pst_hmac_vap, puc_payload, pst_hmac_user_sta);
        return MAC_UNSPEC_FAIL;

    }
    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user_sta->st_user_base_info);

    //puc_vht_cap_ie  = mac_get_vht_cap_ie(puc_payload, (oal_uint16)ul_msg_len, us_info_elem_offset);
    puc_vht_cap_ie = mac_find_ie(MAC_EID_VHT_CAP, puc_payload + us_info_elem_offset, (oal_int32)(ul_msg_len - us_info_elem_offset));
    if (OAL_PTR_NULL != puc_vht_cap_ie)
    {
        /* 不允许VHT STA 使用 TKIP/WEP 加密 */
        if (mac_is_wep_enabled(pst_mac_vap))
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::Rejecting a VHT STA because of its Pairwise Cipher[%]d.}",
                                 pst_mac_user->st_key_info.en_cipher_type);
            return MAC_MISMATCH_HTCAP;
        }
        uc_pcip_policy = pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested;
        uc_grp_policy  = pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested;

        if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pcip_policy)
        {
            OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_vap_check_vht_capabilities_ap::VHT STA with TKIP Pairwise Cipher,uc_pcip_policy=%d uc_grp_policy=%d.}",
                                 uc_pcip_policy, uc_grp_policy);
            return MAC_SUCCESSFUL_STATUSCODE;
        }

        hmac_proc_vht_cap_ie(pst_mac_vap, pst_hmac_user_sta, puc_vht_cap_ie);
    }
    else
    {
        /* 不允许不支持11ac STA关联11aconly 模式的AP*/
        if (WLAN_VHT_ONLY_MODE == pst_mac_vap->en_protocol)
        {
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,"{hmac_vap_check_vht_capabilities_ap:AP 11ac only, but STA not support 11ac}");
            return MAC_MISMATCH_VHTCAP;
        }
    }

    return MAC_SUCCESSFUL_STATUSCODE;
}

/*****************************************************************************

 函 数 名  : hmac_search_txbf_cap_ie_ap
 功能描述  : 检查请求关联的STA的 TXBF Capabilities element
 输入参数  :
 输出参数  :
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_search_txbf_cap_ie_ap(mac_user_ht_hdl_stru *pst_ht_hdl,
                                     oal_uint32            ul_info_elem)
{
    oal_uint32  ul_tmp_txbf_elem = ul_info_elem;

    pst_ht_hdl->bit_imbf_receive_cap                = (ul_tmp_txbf_elem & BIT0);
    pst_ht_hdl->bit_receive_staggered_sounding_cap  = ((ul_tmp_txbf_elem & BIT1) >> 1);
    pst_ht_hdl->bit_transmit_staggered_sounding_cap = ((ul_tmp_txbf_elem & BIT2) >> 2);
    pst_ht_hdl->bit_receive_ndp_cap                 = ((ul_tmp_txbf_elem & BIT3) >> 3);
    pst_ht_hdl->bit_transmit_ndp_cap                = ((ul_tmp_txbf_elem & BIT4) >> 4);
    pst_ht_hdl->bit_imbf_cap                        = ((ul_tmp_txbf_elem & BIT5) >> 5);
    pst_ht_hdl->bit_calibration                     = ((ul_tmp_txbf_elem & 0x000000C0) >> 6);
    pst_ht_hdl->bit_exp_csi_txbf_cap                = ((ul_tmp_txbf_elem & BIT8) >> 8);
    pst_ht_hdl->bit_exp_noncomp_txbf_cap            = ((ul_tmp_txbf_elem & BIT9) >> 9);
    pst_ht_hdl->bit_exp_comp_txbf_cap               = ((ul_tmp_txbf_elem & BIT10) >> 10);
    pst_ht_hdl->bit_exp_csi_feedback                = ((ul_tmp_txbf_elem & 0x00001800) >> 11);
    pst_ht_hdl->bit_exp_noncomp_feedback            = ((ul_tmp_txbf_elem & 0x00006000) >> 13);

    pst_ht_hdl->bit_exp_comp_feedback               = ((ul_tmp_txbf_elem & 0x0001C000) >> 15);
    pst_ht_hdl->bit_min_grouping                    = ((ul_tmp_txbf_elem & 0x00060000) >> 17);
    pst_ht_hdl->bit_csi_bfer_ant_number             = ((ul_tmp_txbf_elem & 0x001C0000) >> 19);
    pst_ht_hdl->bit_noncomp_bfer_ant_number         = ((ul_tmp_txbf_elem & 0x00600000) >> 21);
    pst_ht_hdl->bit_comp_bfer_ant_number            = ((ul_tmp_txbf_elem & 0x01C00000) >> 23);
    pst_ht_hdl->bit_csi_bfee_max_rows               = ((ul_tmp_txbf_elem & 0x06000000) >> 25);
    pst_ht_hdl->bit_channel_est_cap                 = ((ul_tmp_txbf_elem & 0x18000000) >> 27);
}


/*****************************************************************************
 函 数 名  : hmac_search_ht_cap_ie_ap
 功能描述  : 在关联请求请求中搜索HT Cap IE
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_search_ht_cap_ie_ap(
                hmac_vap_stru               *pst_hmac_vap,
                hmac_user_stru              *pst_hmac_user_sta,
                oal_uint8                   *puc_payload,
                oal_uint16                   us_current_offset,
                oal_bool_enum                en_prev_asoc_ht)
{
    oal_uint8                   uc_smps;
    oal_uint8                   uc_supported_channel_width;
    oal_uint8                   uc_ht_green_field;
    oal_uint8                   uc_lsig_txop_protection_support;
    oal_uint8                   uc_mcs_bmp_index;
    oal_uint8                  *puc_tmp_payload;
    oal_uint16                  us_tmp_info_elem = 0;
    oal_uint16                  us_tmp_txbf_low = 0;
    oal_uint32                  ul_tmp_txbf_elem = 0;

    mac_user_ht_hdl_stru        *pst_ht_hdl;
    mac_user_ht_hdl_stru         st_ht_hdl;
    mac_vap_stru                *pst_mac_vap;
    mac_user_stru               *pst_mac_user;
    mac_device_stru             *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                                 "{hmac_search_ht_cap_ie_ap::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 保存 入参 */
    puc_tmp_payload =  puc_payload;

    pst_ht_hdl    = &st_ht_hdl;
    mac_user_get_ht_hdl(&(pst_hmac_user_sta->st_user_base_info), pst_ht_hdl);
    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user_sta->st_user_base_info);

    /* 带有 HT Capability Element 的 STA，标示它具有HT capable. */
    pst_ht_hdl->en_ht_capable = 1;
    us_current_offset += MAC_IE_HDR_LEN;

    /***************************************************************************
                    解析 HT Capabilities Info Field
    ***************************************************************************/

    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);

    /* 检查STA所支持的LDPC编码能力 B0，0:不支持，1:支持 */
    pst_ht_hdl->bit_ldpc_coding_cap = (us_tmp_info_elem & BIT0);

    /* 检查STA所支持的信道宽度 B1，0:仅20M运行，1:20M与40M运行 */
    uc_supported_channel_width = (us_tmp_info_elem & BIT1) >> 1;
    pst_ht_hdl->bit_supported_channel_width = mac_ie_proc_ht_supported_channel_width(pst_mac_user, pst_mac_vap, uc_supported_channel_width, en_prev_asoc_ht);

    /* 检查空间复用节能模式 B2~B3 */
    uc_smps = ((us_tmp_info_elem & (BIT2 | BIT3)) >> 2);
    pst_ht_hdl->bit_sm_power_save = mac_ie_proc_sm_power_save_field(pst_mac_user, uc_smps);

    /* 检查Greenfield 支持情况 B4， 0:不支持，1:支持*/
    uc_ht_green_field = (us_tmp_info_elem & BIT4) >> 4;
    pst_ht_hdl->bit_ht_green_field = mac_ie_proc_ht_green_field(pst_mac_user, pst_mac_vap, uc_ht_green_field, en_prev_asoc_ht);

    /* 检查20MHz Short-GI B5,  0:不支持，1:支持，之后与AP取交集  */
    pst_ht_hdl->bit_short_gi_20mhz = ((us_tmp_info_elem & BIT5) >> 5);
    pst_ht_hdl->bit_short_gi_20mhz &= pst_hmac_vap->st_vap_base_info.pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented;

    /* 检查40MHz Short-GI B6,  0:不支持，1:支持，之后与AP取交集 */
    pst_ht_hdl->bit_short_gi_40mhz = ((us_tmp_info_elem & BIT6) >> 6);
    pst_ht_hdl->bit_short_gi_40mhz &= mac_mib_get_ShortGIOptionInFortyImplemented(&pst_hmac_vap->st_vap_base_info);

    /* 检查支持接收STBC PPDU B8,  0:不支持，1:支持 */
    pst_ht_hdl->bit_rx_stbc = ((us_tmp_info_elem & 0x0300) >> 8);

    /* 检查最大A-MSDU长度 B11，0:3839字节, 1:7935字节 */
    pst_hmac_user_sta->us_amsdu_maxsize = (0 == (us_tmp_info_elem & BIT11)) ? WLAN_MIB_MAX_AMSDU_LENGTH_SHORT : WLAN_MIB_MAX_AMSDU_LENGTH_LONG;

    /* 检查在40M上DSSS/CCK的支持情况 B12 */
    /* 在非Beacon帧或probe rsp帧中时 */
    /* 0: STA在40MHz上不使用DSSS/CCK, 1: STA在40MHz上使用DSSS/CCK */
    pst_ht_hdl->bit_dsss_cck_mode_40mhz = ((us_tmp_info_elem & BIT12) >> 12);

    if ((0 == pst_ht_hdl->bit_dsss_cck_mode_40mhz)
     && (1 == pst_ht_hdl->bit_supported_channel_width))
    {
        pst_hmac_vap->st_vap_base_info.st_protection.uc_sta_no_40dsss_cck_num++;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* 检查Forty MHz Intolerant */
    pst_ht_hdl->bit_forty_mhz_intolerant = ((us_tmp_info_elem & BIT14) >> 14);

    hmac_chan_update_40M_intol_user(pst_mac_vap, pst_mac_user, (oal_bool_enum_uint8)pst_ht_hdl->bit_forty_mhz_intolerant);

    /* 如果Forty MHz Intolerant不等于0，则不允许AP在40MHz运行 */
    if (0 != pst_ht_hdl->bit_forty_mhz_intolerant)
    {
        mac_mib_set_FortyMHzIntolerant(pst_mac_vap, OAL_TRUE);
        OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                      "{hmac_search_ht_cap_ie_ap::40Int==%u, SMI==%u, 2040switch==%u.}",
                      pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant,
                      pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented,
                        pst_hmac_vap->en_2040_switch_prohibited);

        hmac_chan_start_40M_recovery_timer(pst_mac_vap);
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                      "{hmac_search_ht_cap_ie_ap::40MHz Intolerant STA joining.}");
        if (pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M)
        {
            /* AP准备切换置20MHz运行 */
            hmac_chan_multi_switch_to_20MHz_ap(pst_hmac_vap);
        }
        else
        {
            pst_mac_device->en_40MHz_intol_bit_recd = OAL_TRUE;
        }
    }
    else
    {
        mac_mib_set_FortyMHzIntolerant(pst_mac_vap, OAL_FALSE);
    }

#endif
    /*  检查对L-SIG TXOP 保护的支持情况 B15, 0:不支持，1:支持 */
    uc_lsig_txop_protection_support = (us_tmp_info_elem & BIT15) >> 15;
    pst_ht_hdl->bit_lsig_txop_protection = mac_ie_proc_lsig_txop_protection_support(pst_mac_user, pst_mac_vap, uc_lsig_txop_protection_support, en_prev_asoc_ht);

    us_current_offset += MAC_HT_CAPINFO_LEN;

    /***************************************************************************
                        解析 A-MPDU Parameters Field
    ***************************************************************************/

    /* 提取 Maximum Rx A-MPDU factor (B1 - B0) */
    pst_ht_hdl->uc_max_rx_ampdu_factor = (puc_tmp_payload[us_current_offset] & 0x03);

    /* 提取 the Minimum MPDU Start Spacing (B2 - B4) */
    pst_ht_hdl->uc_min_mpdu_start_spacing = (puc_tmp_payload[us_current_offset] >> 2)  & 0x07;

    us_current_offset += MAC_HT_AMPDU_PARAMS_LEN;

    /***************************************************************************
                        解析 Supported MCS Set Field
    ***************************************************************************/
    for (uc_mcs_bmp_index = 0; uc_mcs_bmp_index < WLAN_HT_MCS_BITMASK_LEN; uc_mcs_bmp_index++)
    {
        pst_ht_hdl->uc_rx_mcs_bitmask[uc_mcs_bmp_index] =
                (pst_hmac_vap->st_vap_base_info.pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[uc_mcs_bmp_index])
              & (*(oal_uint8 *)(puc_tmp_payload + us_current_offset + uc_mcs_bmp_index));
    }

    pst_ht_hdl->uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN - 1] &= 0x1F;

    us_current_offset += MAC_HT_SUP_MCS_SET_LEN;

    /***************************************************************************
                        解析 HT Extended Capabilities Info Field
    ***************************************************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);

    /* 提取 HTC support Information */
    if (0 != (us_tmp_info_elem & BIT10))
    {
        pst_ht_hdl->uc_htc_support = 1;
    }

    us_current_offset += MAC_HT_EXT_CAP_LEN;

    /***************************************************************************
                        解析 Tx Beamforming Field
    ***************************************************************************/
    us_tmp_info_elem = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset], puc_tmp_payload[us_current_offset + 1]);
    us_tmp_txbf_low  = OAL_MAKE_WORD16(puc_tmp_payload[us_current_offset + 2], puc_tmp_payload[us_current_offset + 3]);
    ul_tmp_txbf_elem = OAL_MAKE_WORD32(us_tmp_info_elem, us_tmp_txbf_low);
    hmac_search_txbf_cap_ie_ap(pst_ht_hdl, ul_tmp_txbf_elem);
    //us_current_offset += MAC_HT_TXBF_CAP_LEN;

    /***************************************************************************
                        解析 ASEL Field(天线选择能力)
    ***************************************************************************/
    //us_current_offset += MAC_HT_ASEL_LEN;

    /* 更新消息内容索引 */
    //us_current_offset = us_saved_offset + puc_tmp_payload[us_saved_offset + 1] + MAC_IE_HDR_LEN;

    mac_user_set_ht_hdl(&(pst_hmac_user_sta->st_user_base_info), pst_ht_hdl);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_vap_addba_check
 功能描述  : 判断该用户对应的TID是否已经建立BA会话
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_TRUE代表可以建立BA会话，OAL_FALSE表示不可以建立BA会话
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_vap_addba_check(
                hmac_vap_stru    *pst_hmac_vap,
                hmac_user_stru   *pst_hmac_user,
                oal_uint8         uc_tidno)
{
    mac_device_stru   *pst_mac_device;
    hmac_tid_stru     *pst_hmac_tid_info;

    /* 判断HMAC VAP的是否支持聚合 */
    if (!((pst_hmac_vap->en_tx_aggr_on) || (pst_hmac_vap->st_vap_base_info.st_cap_flag.bit_rifs_tx_on)))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_tx_aggr_on of vap is off");
        return OAL_FALSE;
    }

    pst_hmac_tid_info = &(pst_hmac_user->ast_tid_info[uc_tidno]);
    if (OAL_TRUE != pst_hmac_tid_info->st_ba_tx_info.en_ba_switch)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_tx_aggr_on of tid[%d] is off", uc_tidno);
        return OAL_FALSE;
    }

    if (DMAC_BA_COMPLETE == pst_hmac_tid_info->st_ba_tx_info.en_ba_status)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::en_ba_status of tid[%d] is COMPLETE", uc_tidno);
        return OAL_FALSE;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::pst_mac_dev null");
        return OAL_FALSE;
    }
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    if (pst_hmac_vap->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::uc_tx_ba_session_num[%d] exceed spec", pst_hmac_vap->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#else
    if (pst_mac_device->uc_tx_ba_session_num >= WLAN_MAX_TX_BA)
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{hmac_vap_addba_check::uc_tx_ba_session_num[%d] exceed spec", pst_mac_device->uc_tx_ba_session_num);
        return OAL_FALSE;
    }
#endif
    /* 需要先发送5个单播帧，再进行BA会话的建立 */
    if ((OAL_TRUE == pst_hmac_user->st_user_base_info.st_cap_info.bit_qos) &&
        (pst_hmac_user->auc_ba_flag[uc_tidno] < DMAC_UCAST_FRAME_TX_COMP_TIMES))
    {
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                      "{hmac_vap_addba_check::auc_ba_flag[%d]}", pst_hmac_user->auc_ba_flag[uc_tidno]);
        pst_hmac_user->auc_ba_flag[uc_tidno]++;
        return OAL_FALSE;
    }

    if ((pst_hmac_tid_info->st_ba_tx_info.en_ba_status != DMAC_BA_INPROGRESS)
     && (pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps < HMAC_ADDBA_EXCHANGE_ATTEMPTS))
    {
        pst_hmac_tid_info->st_ba_tx_info.en_ba_status = DMAC_BA_INPROGRESS;
        pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps++;

        return OAL_TRUE;
    }
    else
    {
        OAM_INFO_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA,
                     "{hmac_vap_addba_check::addba_attemps[%d] of tid[%d] is COMPLETE}", pst_hmac_tid_info->st_ba_tx_info.uc_addba_attemps, uc_tidno);
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_vap_net_stopall
 功能描述  : 停止所有VAP队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_vap_net_stopall(oal_void)
{
    oal_uint8 uc_vap_id;
    oal_net_device_stru  *pst_net_device = NULL;
    hmac_vap_stru    *pst_hmac_vap = NULL;
    for (uc_vap_id = 0; uc_vap_id < WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if (NULL == pst_hmac_vap)
            break;

        pst_net_device = pst_hmac_vap->pst_net_device;

        if (NULL == pst_net_device)
            break;

        oal_net_tx_stop_all_queues(pst_net_device);
        //OAL_IO_PRINT("stop net device:%p\n", pst_net_device);
    }
}

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/*****************************************************************************
 函 数 名  : hmac_flowctl_check_device_is_sta_mode
 功能描述  : 判断当前device是否工作在sta模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 hmac_flowctl_check_device_is_sta_mode(oal_void)
{
    mac_device_stru         *pst_dev;
    mac_vap_stru            *pst_vap;
    oal_uint8                uc_vap_index;
    oal_bool_enum_uint8      en_device_is_sta = OAL_FALSE;

    /* check 各VAP状态，只要有VAP工作在STA模式(包括BSS_STA或者P2P client)，则认为该device工作在sta模式 */
    pst_dev = mac_res_get_dev(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_p2p_check_can_enter_state::pst_mac_device[0] null!}");
        return OAL_FALSE;
    }

    if (pst_dev->uc_vap_num >= 1)
    {
        for (uc_vap_index = 0; uc_vap_index < pst_dev->uc_vap_num; uc_vap_index++)
        {
            pst_vap = mac_res_get_mac_vap(pst_dev->auc_vap_id[uc_vap_index]);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_INFO_LOG1(0, OAM_SF_BA, "{hmac_flowctl_check_device_is_sta_mode::mac_res_get_mac_vap fail.vap_index = %u}",uc_vap_index);
                continue;
            }

            if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
            {
                en_device_is_sta = OAL_TRUE;
                break;
            }
        }
    }

    OAM_INFO_LOG2(0, OAM_SF_TX, "{hmac_flowctl_check_device_is_sta_mode:: vap_num = %d, is_sta mode = %d}", pst_dev->uc_vap_num, en_device_is_sta);

    return en_device_is_sta;
}

/*****************************************************************************
 函 数 名  : hmac_vap_net_start_subqueue
 功能描述  : 使能某个VAP队列的某个队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_vap_wake_subq(oal_uint8 uc_vap_id, oal_uint16 us_queue_idx)
{
    oal_net_device_stru    *pst_net_device = NULL;
    hmac_vap_stru          *pst_hmac_vap = NULL;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (NULL == pst_hmac_vap)
    {
        return;
    }

#if 0
    if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        return;
    }
#endif

    pst_net_device = pst_hmac_vap->pst_net_device;
    if (NULL == pst_net_device)
    {
        return;
    }

    oal_net_wake_subqueue(pst_net_device, us_queue_idx);
}

/*****************************************************************************
 函 数 名  : hmac_vap_net_start_subqueue
 功能描述  : 使能所有VAP队列的某个队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_vap_net_start_subqueue(oal_uint16 us_queue_idx)
{
    oal_uint8               uc_vap_id;
    OAL_STATIC oal_uint8    g_uc_start_subq_flag = 0;

     /*自旋锁内，任务和软中断都被锁住，不需要FRW锁*/

    if (0 == g_uc_start_subq_flag)
    {
        g_uc_start_subq_flag = 1;

        /* vap id从低到高恢复 */
        for (uc_vap_id = 1; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
        {
            hmac_vap_wake_subq(uc_vap_id, us_queue_idx);
        }
    }
    else
    {
        g_uc_start_subq_flag = 0;

        /* vap id从高到低恢复 */
        for (uc_vap_id = WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id > 1; uc_vap_id--)
        {
            hmac_vap_wake_subq(uc_vap_id - 1, us_queue_idx);
        }
    }

}

/*****************************************************************************
 函 数 名  : hmac_vap_stop_subq
 功能描述  : 停止某个VAP队列的某个队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  hmac_vap_stop_subq(oal_uint8 uc_vap_id, oal_uint16 us_queue_idx)
{
    oal_net_device_stru    *pst_net_device = NULL;
    hmac_vap_stru          *pst_hmac_vap = NULL;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (NULL == pst_hmac_vap)
    {
        return;
    }

#if 0
    if ((MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        return;
    }
#endif

    pst_net_device = pst_hmac_vap->pst_net_device;
    if (NULL == pst_net_device)
    {
        return;
    }

    oal_net_stop_subqueue(pst_net_device, us_queue_idx);
}


/*****************************************************************************
 函 数 名  : hmac_vap_net_stop_subqueue
 功能描述  : 使能所有VAP队列的某个队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_vap_net_stop_subqueue(oal_uint16 us_queue_idx)
{
    oal_uint8               uc_vap_id;
    OAL_STATIC oal_uint8    g_uc_stop_subq_flag = 0;

    /*自旋锁内，任务和软中断都被锁住，不需要FRW锁*/

    /* 由按照VAP ID顺序停止subq，改为不依据VAP ID顺序 */
    if (0 == g_uc_stop_subq_flag)
    {
        g_uc_stop_subq_flag = 1;

        for (uc_vap_id = 1; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
        {
            hmac_vap_stop_subq(uc_vap_id, us_queue_idx);
        }
    }
    else
    {
        g_uc_stop_subq_flag = 0;

        for (uc_vap_id = WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id > 1; uc_vap_id--)
        {
            hmac_vap_stop_subq(uc_vap_id - 1, us_queue_idx);
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : hmac_vap_net_startall
 功能描述  : 使能所有VAP队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_vap_net_startall(oal_void)
{
    oal_uint8 uc_vap_id;
    oal_net_device_stru  *pst_net_device = NULL;
    hmac_vap_stru    *pst_hmac_vap = NULL;
    for (uc_vap_id = 0; uc_vap_id < WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE; uc_vap_id++)
    {
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
        if (NULL == pst_hmac_vap)
            break;

        pst_net_device = pst_hmac_vap->pst_net_device;

        if (NULL == pst_net_device)
            break;

        oal_net_tx_wake_all_queues(pst_net_device);
        //OAL_IO_PRINT("start net device:%p\n", pst_net_device);
    }
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 函 数 名  : hmac_check_opmode_notify
 功能描述  : 检查请求关联的STA的Operating Mode Notification
 输入参数  : hmac_vap_stru    *pst_hmac_vap --VAP指针
             oal_uint8        *puc_mac_hdr, --帧头指针
             oal_uint8        *puc_payload  --payload指针
             oal_uint16        us_info_elem_offset--偏移长度
             oal_uint32        ul_msg_len----信息长度
             hmac_user_stru   *pst_hmac_user_sta --用户指针
 输出参数  : 无
 返 回 值  : oal_uint16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月10日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 hmac_check_opmode_notify(
                hmac_vap_stru                   *pst_hmac_vap,
                oal_uint8                       *puc_mac_hdr,
                oal_uint8                       *puc_payload,
                oal_uint16                       us_info_elem_offset,
                oal_uint32                       ul_msg_len,
                hmac_user_stru                   *pst_hmac_user)
{
    oal_uint8              *puc_opmode_notify_ie;
    mac_vap_stru           *pst_mac_vap;
    mac_user_stru          *pst_mac_user;
    mac_opmode_notify_stru *pst_opmode_notify = OAL_PTR_NULL;
    oal_uint8               uc_mgmt_frm_type;
    oal_uint32              ul_relt;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == puc_mac_hdr))
    {
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{hmac_check_opmode_notify::pst_hmac_vap = [%x], puc_payload = [%x], pst_hmac_user = [%x],puc_mac_hdr = [%x]!}\r\n",
                        pst_hmac_vap, puc_payload, pst_hmac_user, puc_mac_hdr);
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{hmac_check_opmode_notify::param null, %d %d %d %d.}",
                       pst_hmac_vap, puc_payload, pst_hmac_user, puc_mac_hdr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user->st_user_base_info);

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        return OAL_SUCC;
    }

    //puc_opmode_notify_ie = mac_get_opmode_notify_ie(puc_payload, (oal_uint16)ul_msg_len, us_info_elem_offset);
    puc_opmode_notify_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_payload + us_info_elem_offset, (oal_int32)(ul_msg_len - us_info_elem_offset));
    if ((OAL_PTR_NULL != puc_opmode_notify_ie) && (puc_opmode_notify_ie[1] >= MAC_OPMODE_NOTIFY_LEN))
    {
        uc_mgmt_frm_type  = mac_get_frame_sub_type(puc_mac_hdr);
        pst_opmode_notify = (mac_opmode_notify_stru *)(puc_opmode_notify_ie + MAC_IE_HDR_LEN);
        ul_relt = hmac_ie_proc_opmode_field(pst_mac_vap, pst_mac_user, pst_opmode_notify, uc_mgmt_frm_type);
        if (OAL_UNLIKELY(OAL_SUCC != ul_relt))
        {
            OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_check_opmode_notify::hmac_ie_proc_opmode_field failed[%d].}", ul_relt);
            return ul_relt;
        }
        /* opmode息同步dmac */
        ul_relt = hmac_config_update_opmode_event(pst_mac_vap, pst_mac_user, uc_mgmt_frm_type);
        if (OAL_UNLIKELY(OAL_SUCC != ul_relt))
        {
            OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_check_opmode_notify::hmac_config_update_opmode_event failed[%d].}", ul_relt);
            return ul_relt;
        }
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : hmac_del_virtual_inf_worker
 功能描述  : cfg80211 删除虚拟接口工作队列，防止去注册网络设备时程序挂死。
 输入参数  : oal_work_stru *pst_del_virtual_inf_work
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月26日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_del_virtual_inf_worker(oal_work_stru *pst_del_virtual_inf_work)
{
    oal_net_device_stru         *pst_net_dev;
    hmac_vap_stru               *pst_hmac_vap;
    oal_wireless_dev_stru       *pst_wireless_dev;
    hmac_device_stru            *pst_hmac_device;

    pst_hmac_vap     = OAL_CONTAINER_OF(pst_del_virtual_inf_work, hmac_vap_stru, st_del_virtual_inf_worker);
    pst_net_dev      = pst_hmac_vap->pst_del_net_device;
    pst_wireless_dev = OAL_NETDEVICE_WDEV(pst_net_dev);

    /* 不存在rtnl_lock锁问题 */
    oal_net_unregister_netdev(pst_net_dev);

    /* 在释放net_device 后释放wireless_device 内存 */
    OAL_MEM_FREE(pst_wireless_dev, OAL_TRUE);

    pst_hmac_vap->pst_del_net_device = OAL_PTR_NULL;

    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (pst_hmac_device == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                    "{hmac_del_virtual_inf_worker::pst_hmac_device is null !device_id[%d]}",
                    pst_hmac_vap->st_vap_base_info.uc_device_id);
        return;
    }

    hmac_clr_p2p_status(&pst_hmac_device->ul_p2p_intf_status, P2P_STATUS_IF_DELETING);

    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                    "{hmac_del_virtual_inf_worker::end !pst_hmac_device->ul_p2p_intf_status[%x]}",
                    pst_hmac_device->ul_p2p_intf_status);
    OAL_SMP_MB();
    OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&pst_hmac_device->st_netif_change_event);

}
#endif  /* _PRE_WLAN_FEATURE_P2P */

/*****************************************************************************
 函 数 名  : hmac_handle_disconnect_rsp
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_handle_disconnect_rsp(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user,
                                                  hmac_report_disasoc_reason_uint16  en_disasoc_reason)
{
     /* 修改 state & 删除 user */
    switch (pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            {
                /* 抛事件上报内核，已经去关联某个STA */
                hmac_handle_disconnect_rsp_ap(pst_hmac_vap, pst_hmac_user);
            }
            break;

         case WLAN_VAP_MODE_BSS_STA:
            {
                hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);

                /* 上报内核sta已经和某个ap去关联 */
                hmac_sta_handle_disassoc_rsp(pst_hmac_vap, en_disasoc_reason);
            }
             break;
         default:
             break;
    }
    return;
}


/*****************************************************************************
 函 数 名  : hmac_tx_get_mac_vap
 功能描述  : 获取VAP，并判断VAP状态
 输入参数  : pst_event event结构体
 输出参数  : pst_vap_stru VAP结构体
 返 回 值  :
 调用函数  : hmac_tx_wlan_to_wlan_ap
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_tx_get_mac_vap(oal_uint8 uc_vap_id, mac_vap_stru **pst_vap_stru)
{
    mac_vap_stru         *pst_vap;

    /* 获取vap结构信息 */
    pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{hmac_tx_get_mac_vap::pst_vap null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* VAP模式判断 */
    if (WLAN_VAP_MODE_BSS_AP != pst_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "hmac_tx_get_mac_vap::vap_mode error[%d]", pst_vap->en_vap_mode);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    /* VAP状态判断 */
    if (MAC_VAP_STATE_UP == pst_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state)
    {
        *pst_vap_stru = pst_vap;

        return OAL_SUCC;
    }

    OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "hmac_tx_get_mac_vap::vap_state[%d] error", pst_vap->en_vap_state);

    return OAL_ERR_CODE_CONFIG_UNSUPPORT;
}

/*lint -e19*/
oal_module_symbol(hmac_vap_get_priv_cfg);
oal_module_symbol(hmac_vap_get_net_device);
oal_module_symbol(hmac_vap_set_asoc_req_ie_ptr_null);
oal_module_symbol(hmac_vap_get_desired_country);
oal_module_symbol(hmac_vap_destroy);

#ifdef _PRE_WLAN_FEATURE_11D
oal_module_symbol(hmac_vap_get_updata_rd_by_ie_switch);
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
oal_module_symbol(hmac_del_virtual_inf_worker);
#endif /* _PRE_WLAN_FEATURE_P2P */
/*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

