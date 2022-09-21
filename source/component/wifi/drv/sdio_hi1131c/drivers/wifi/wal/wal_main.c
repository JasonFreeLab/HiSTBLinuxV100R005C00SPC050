
/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_main.c
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : WAL模块初始化与卸载
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
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
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#include "wlan_spec.h"

#include "hmac_ext_if.h"

#include "wal_main.h"
#include "wal_config.h"
#include "wal_linux_ioctl.h"
#include "wal_linux_cfg80211.h"
#include "wal_linux_flowctl.h"
#include "wal_config_acs.h"

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "wal_proxysta.h"
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK
#include "wal_linux_rx_rsp.h"
#endif

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
#include "oal_kernel_file.h"
#endif

#include "wal_dfx.h"

#include "hmac_vap.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_MAIN_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* HOST CRX子表 */
OAL_STATIC frw_event_sub_table_item_stru g_ast_wal_host_crx_table[WAL_HOST_CRX_SUBTYPE_BUTT];

/* HOST CTX字表 */
OAL_STATIC frw_event_sub_table_item_stru g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_BUTT];

/* HOST DRX子表 */
/* OAL_STATIC frw_event_sub_table_item_stru g_ast_wal_host_drx_table[WAL_HOST_DRX_SUBTYPE_BUTT]; */

/* wal对外钩子函数 */
oam_wal_func_hook_stru     g_st_wal_drv_func_hook;

oal_wakelock_stru   g_st_wal_wakelock;

oal_uint32  frw_event_fsm_unregister(oal_void);
oal_void    frw_timer_delete_all_timer(oal_void);
oal_void    frw_timer_exit(oal_void);

oal_uint32  mac_res_exit(void);
oal_uint32  hmac_res_exit(mac_board_stru *pst_hmac_board);


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : wal_event_fsm_init
 功能描述  : 注册事件处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_event_fsm_init(oal_void)
{
    g_ast_wal_host_crx_table[WAL_HOST_CRX_SUBTYPE_CFG].p_func = wal_config_process_pkt;
    frw_event_table_register(FRW_EVENT_TYPE_HOST_CRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_wal_host_crx_table);

    /* g_ast_wal_host_drx_table[WAL_HOST_DRX_SUBTYPE_TX].p_func = hmac_tx_lan_to_wlan_ap;
    frw_event_table_register(FRW_EVENT_TYPE_HOST_DRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_wal_host_drx_table); */

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_SCAN_COMP_STA].p_func     = wal_scan_comp_proc_sta;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ASOC_COMP_STA].p_func     = wal_asoc_comp_proc_sta;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_DISASOC_COMP_STA].p_func  = wal_disasoc_comp_proc_sta;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_CONNECT_AP].p_func    = wal_connect_new_sta_proc_ap;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_DISCONNECT_AP].p_func  = wal_disconnect_sta_proc_ap;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_MIC_FAILURE].p_func       = wal_mic_failure_proc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_RX_MGMT].p_func           = wal_send_mgmt_to_host;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_LISTEN_EXPIRED].p_func    = wal_p2p_listen_timeout;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ADD_PROXY_STA_VAP].p_func = wal_proxysta_add_vap;
#endif

#ifdef _PRE_SUPPORT_ACS
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ACS_RESPONSE].p_func      = wal_acs_response_event_handler;
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_FLOWCTL_BACKP].p_func      = wal_flowctl_backp_event_handler;
#endif

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_INIT].p_func  = wal_cfg80211_init_evt_handle;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_MGMT_TX_STATUS].p_func  = wal_cfg80211_mgmt_tx_status;
#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ROAM_COMP_STA].p_func   = wal_roam_comp_proc_sta;
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_FT_EVENT_STA].p_func   = wal_ft_event_proc_sta;
#endif //_PRE_WLAN_FEATURE_11R
#ifdef _PRE_WLAN_FEATURE_HILINK
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_OTHER_BSS_DATA].p_func   = wal_send_other_bss_data_to_host;
#endif

    frw_event_table_register(FRW_EVENT_TYPE_HOST_CTX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_wal_host_ctx_table);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_event_fsm_exit
 功能描述  : 卸载事件处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  wal_event_fsm_exit(oal_void)
{
    OAL_IO_PRINT("debug2");

    OAL_MEMZERO(g_ast_wal_host_crx_table, OAL_SIZEOF(g_ast_wal_host_crx_table));

    OAL_MEMZERO(g_ast_wal_host_ctx_table, OAL_SIZEOF(g_ast_wal_host_ctx_table));

    return OAL_SUCC;
}

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
/*debug sysfs*/
OAL_STATIC oal_kobject* g_conn_syfs_wal_object = NULL;

oal_int32 wal_wakelock_info_print(char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;

#ifdef CONFIG_PRINTK
    if(g_st_wal_wakelock.locked_addr)
    {
        ret +=  snprintf(buf + ret , buf_len - ret,"wakelocked by:%pf\n",
                    (oal_void*)g_st_wal_wakelock.locked_addr);
    }
#endif

    ret +=  snprintf(buf + ret , buf_len - ret,"hold %lu locks\n", g_st_wal_wakelock.lock_count);

    return ret;
}

OAL_STATIC ssize_t  wal_get_wakelock_info(struct device *dev, struct device_attribute *attr, char*buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret += wal_wakelock_info_print(buf,PAGE_SIZE - ret);

    return ret;
}

extern oal_int32 wal_atcmsrv_ioctl_get_rx_pckg(oal_net_device_stru *pst_net_dev, oal_int32 *pl_rx_pckg_succ_num);
OAL_STATIC ssize_t  wal_get_packet_statistics_wlan0_info(struct device *dev, struct device_attribute *attr, char*buf)
{
    ssize_t                     ret = 0;
    oal_net_device_stru*        pst_net_dev;
    mac_vap_stru*               pst_vap;
    hmac_vap_stru*              pst_hmac_vap;
    oal_int32                   l_rx_pckg_succ_num;
    oal_int32                   l_ret;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    pst_net_dev = oal_dev_get_by_name("wlan0");
    if (OAL_PTR_NULL == pst_net_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_packet_statistics_wlan0_info_print::oal_dev_get_by_name return null ptr!}\r\n");
        return ret;
    }
    oal_dev_put(pst_net_dev);   /* 调用oal_dev_get_by_name后，必须调用oal_dev_put使net_dev的引用计数减一 */
    /* 获取VAP结构体 */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev);
    /* 如果VAP结构体不存在，返回0 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_packet_statistics_wlan0_info_print::pst_vap = OAL_PTR_NULL!}\r\n");
        return ret;
    }
    /* 非STA直接返回 */
    if (WLAN_VAP_MODE_BSS_STA != pst_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_packet_statistics_wlan0_info_print::vap_mode:%d.}\r\n", pst_vap->en_vap_mode);
        return ret;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{wal_packet_statistics_wlan0_info_print::pst_hmac_vap null.}");
        return ret;
    }

    l_ret = wal_atcmsrv_ioctl_get_rx_pckg(pst_net_dev, &l_rx_pckg_succ_num);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_packet_statistics_wlan0_info_print::wal_atcmsrv_ioctl_get_rx_pckg failed, failed err:%d!}\r\n", l_ret);
        return ret;
    }

    ret +=  snprintf(buf, PAGE_SIZE, "rx_packet=%d\r\n", l_rx_pckg_succ_num);

    return ret;
}

OAL_STATIC DEVICE_ATTR(wakelock, S_IRUGO, wal_get_wakelock_info, NULL);
OAL_STATIC DEVICE_ATTR(packet_statistics_wlan0, S_IRUGO, wal_get_packet_statistics_wlan0_info, NULL);

oal_int32 wal_msg_queue_info_print(char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;

    ret +=  snprintf(buf + ret , buf_len - ret,"message count:%u\n", wal_get_request_msg_count());

    return ret;
}

OAL_STATIC ssize_t  wal_get_msg_queue_info(struct device *dev, struct device_attribute *attr, char*buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret += wal_msg_queue_info_print(buf,PAGE_SIZE - ret);

    return ret;
}

OAL_STATIC DEVICE_ATTR(msg_queue, S_IRUGO, wal_get_msg_queue_info, NULL);

OAL_STATIC struct attribute *wal_sysfs_entries[] = {
        &dev_attr_wakelock.attr,
        &dev_attr_msg_queue.attr,
        &dev_attr_packet_statistics_wlan0.attr,
        NULL
};

OAL_STATIC struct attribute_group wal_attribute_group = {
        //.name = "vap",
        .attrs = wal_sysfs_entries,
};

OAL_STATIC oal_int32 wal_sysfs_entry_init(oal_void)
{
    oal_int32       ret = OAL_SUCC;
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{wal_sysfs_entry_init::get sysfs root object failed!}");
        return -OAL_EFAIL;
    }

    g_conn_syfs_wal_object = kobject_create_and_add("wal", pst_root_object);
    if(NULL == g_conn_syfs_wal_object)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{wal_sysfs_entry_init::create wal object failed!}");
        return -OAL_EFAIL;
    }

    ret = sysfs_create_group(g_conn_syfs_wal_object, &wal_attribute_group);
    if (ret)
    {
        kobject_put(g_conn_syfs_wal_object);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{wal_sysfs_entry_init::sysfs create group failed!}");
        return ret;
    }
    return OAL_SUCC;
}

OAL_STATIC oal_int32 wal_sysfs_entry_exit(oal_void)
{
    if(g_conn_syfs_wal_object)
    {
        sysfs_remove_group(g_conn_syfs_wal_object, &wal_attribute_group);
        kobject_put(g_conn_syfs_wal_object);
    }
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : wal_main_init
 功能描述  : WAL模块初始化总入口，包含WAL模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  wal_main_init(oal_void)
{
    oal_uint32           ul_ret;
    frw_init_enum_uint16 en_init_state;

    oal_wake_lock_init(&g_st_wal_wakelock, "wlan_wal_lock");

    wal_msg_queue_init();

    en_init_state = frw_get_init_state();
    /* WAL模块初始化开始时，说明HMAC肯定已经初始化成功 */
    if ((FRW_INIT_STATE_BUTT == en_init_state) || (en_init_state < FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_main_init::en_init_state has a invalid value [%d]!}\r\n", en_init_state);

        frw_timer_delete_all_timer();
        return -OAL_EFAIL;
    }

    wal_event_fsm_init();

    /* 创建proc */
    ul_ret = wal_hipriv_create_proc(OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_main_init::wal_hipriv_create_proc has a wrong return value [%d]!}\r\n", ul_ret);

        frw_timer_delete_all_timer();
        return -OAL_EFAIL;
    }

    /* 初始化每个device硬件设备对应的wiphy */
    ul_ret = wal_cfg80211_init();
    if (ul_ret != OAL_SUCC)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_main_init::wal_cfg80211_init has a wrong return value [%d]!}\r\n", ul_ret);

        frw_timer_delete_all_timer();
        return -OAL_EFAIL;
    }

    /* 在host侧如果WAL初始化成功，即为全部初始化成功 */
    frw_set_init_state(FRW_INIT_STATE_ALL_SUCC);


    /* wal钩子函数初始化 */
    wal_drv_cfg_func_hook_init();

    /* wal层对外钩子函数注册至oam模块 */
    oam_wal_func_fook_register(&g_st_wal_drv_func_hook);

#ifdef _PRE_WLAN_FEATURE_P2P
    /* DTSxxxxxx 初始化cfg80211 删除网络设备工作队列 */
    g_pst_del_virtual_inf_workqueue = OAL_CREATE_SINGLETHREAD_WORKQUEUE("cfg80211_del_virtual_inf");
    if (!g_pst_del_virtual_inf_workqueue)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{mac_device_init::Failed to create cfg80211 del virtual infterface workqueue!}");

        return OAL_FAIL;
    }
#endif /* _PRE_WLAN_FEATURE_P2P */

#ifdef _PRE_SUPPORT_ACS
    wal_acs_init();
#endif

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
/*debug sysfs*/
    wal_sysfs_entry_init();
#endif
#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfx_init();
#endif //#ifdef _PRE_WLAN_FEATURE_DFR
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    //wal_set_custom_process_func(); /* 1131C-debug */
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wal_destroy_all_vap
 功能描述  : 卸载前删除所有vap
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void  wal_destroy_all_vap(oal_void)
{
#if (_PRE_TEST_MODE_UT != _PRE_TEST_MODE)

    oal_uint8               uc_vap_id = 0;
    oal_net_device_stru    *pst_net_dev;
    oal_int8                ac_param[10] = {0};
    OAL_IO_PRINT("wal_destroy_all_vap start");

    /* 删除业务vap，双芯片id从2开始，增加编译宏表示板级业务vap起始id 后续业务vap的处理，采用此宏   */
    for (uc_vap_id = WLAN_SERVICE_VAP_START_ID_PER_BOARD; uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id++)
    {
        pst_net_dev = hmac_vap_get_net_device(uc_vap_id);
        if (OAL_PTR_NULL != pst_net_dev)
        {
            oal_net_close_dev(pst_net_dev);

            wal_hipriv_del_vap(pst_net_dev, ac_param);
            frw_event_process_all_event(0);
        }
    }

    frw_timer_exit();
    frw_timer_delete_all_timer();
    pst_net_dev=oal_dev_get_by_name("wlan0");
    if(OAL_PTR_NULL != pst_net_dev)
    {
        OAL_IO_PRINT("wal_destroy_all_vap:remove wlan0\n");
        oal_dev_put(pst_net_dev);
        oal_net_unregister_netdev(pst_net_dev);
    }
    pst_net_dev=oal_dev_get_by_name("p2p0");
    if(OAL_PTR_NULL != pst_net_dev)
    {
        OAL_IO_PRINT("wal_destroy_all_vap:remove p2p0\n");
        oal_dev_put(pst_net_dev);
        oal_net_unregister_netdev(pst_net_dev);
    }
    frw_event_process_all_event(0);
    mac_res_exit();
    hmac_res_exit(&g_st_hmac_board);  /* 释放hmac res资源 */
#endif

    return;
}


/*****************************************************************************
 函 数 名  : wal_main_exit
 功能描述  : WAL模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块卸载返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  wal_main_exit(oal_void)
{
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
/*debug sysfs*/
    wal_sysfs_entry_exit();
#endif
    /* down掉所有的vap */
    wal_destroy_all_vap();

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* 此处02加载ko时出现，找不到符号的错误，待后续解决 TBD */

    /* 卸载每个device硬件设备对应的wiphy */
    wal_cfg80211_exit();
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    wal_cfg80211_exit();
#endif
    wal_event_fsm_exit();

    /* 删除proc */
    wal_hipriv_remove_proc();


    /* 卸载成功时，将初始化状态置为HMAC初始化成功 */
    frw_set_init_state(FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC);

    /* 去注册钩子函数 */
    oam_wal_func_fook_unregister();
#ifdef _PRE_WLAN_FEATURE_P2P
    /* DTSxxxxxx 删除cfg80211 删除网络设备工作队列 */
    oal_destroy_workqueue(g_pst_del_virtual_inf_workqueue);
#endif

#ifdef _PRE_SUPPORT_ACS
    wal_acs_exit();
#endif
#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfx_exit();
#endif //#ifdef _PRE_WLAN_FEATURE_DFR

    oal_wake_lock_exit(&g_st_wal_wakelock);

}

/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(wal_main_init);
oal_module_exit(wal_main_exit);
#endif
oal_module_symbol(wal_main_init);
oal_module_symbol(wal_main_exit);

oal_module_license("GPL");
/*lint +e578*//*lint +e19*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

