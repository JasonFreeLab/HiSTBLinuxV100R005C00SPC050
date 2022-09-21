/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_wow.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年05月05日
  最近修改   :
  功能描述   : WOW hmac功能
  函数列表   :
  修改历史   :
  1.日    期   : 2016年05月05日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)


#ifdef _PRE_WLAN_FEATURE_WOW

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "frw_ext_if.h"
#include "hmac_wow.h"

#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
#include "data_process.h"
#endif

#include "plat_pm_wlan.h"

#include "wal_linux_scan.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_WOW_C

#define WOW_HOST_TEST
#define WOW_USE_CHANNEL_MSG
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

hmac_wow_info_stru g_st_wow_info = {0};

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/
extern oal_void host_pow_off(oal_void);
extern unsigned int g_ul_wlan_resume_wifi_init_flag;
extern unsigned int g_ul_wlan_reusme_wifi_mode;
extern oal_net_device_stru  *g_past_net_device[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
extern unsigned int g_ul_wlan_resume_wifi_init_flag;
#endif
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
extern oal_int32                       hmac_backup_data(oal_void);
extern oal_int32                       save_wpa_supplicant_data(oal_void);
extern oal_int32                       lwip_save_info(oal_int8 *pc_network_name);
extern struct  data_process_interface  g_st_data_process_interface;
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hmac_wow_get_time
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 距离开机时间 ms
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_wow_get_time(oal_void)
{
    unsigned long time_2 = *(volatile unsigned long *)(0x20010000+4);

    time_2 = CALC_TIME_TEST_FUNC(time_2);

    return time_2;
}

/*****************************************************************************
 函 数 名  : hmac_wow_set_host_state
 功能描述  :
 输入参数  : oal_uint8 uc_sleep_state
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_set_host_state(oal_uint8 uc_sleep_state)
{
    /*  mutex  */
    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{Hmac_wow::state[%d]->[%d]!}",g_st_wow_info.uc_host_sleep_state, uc_sleep_state);

    g_st_wow_info.uc_host_sleep_state = uc_sleep_state;
}

/*****************************************************************************
 函 数 名  : hmac_wow_get_host_state
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 hmac_wow_get_host_state(oal_void)
{
     /*  mutex  */
    return g_st_wow_info.uc_host_sleep_state;
}

/*****************************************************************************
 函 数 名  : hmac_wow_init
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_init(oal_void)
{
    oal_uint8 auc_pattern[6] = {0x98,0x3B,0x16,0xF8,0xF3,0x9C};

    if (HMAC_WOW_MODULE_STATE_INIT == g_st_wow_info.uc_is_wow_init)
    {
        return;
    }

    OAL_MEMZERO(&g_st_wow_info, OAL_SIZEOF(hmac_wow_info_stru));

    if (!g_ul_wlan_resume_wifi_init_flag)
    {
        hmac_wow_set_host_state(HMAC_HOST_STATE_WAKEUP);
    }
    else
    {
        hmac_wow_set_host_state(HMAC_HOST_STATE_SLEPT);
    }

    g_st_wow_info.st_wow_cfg.uc_wow_en = MAC_WOW_ENABLE;
    g_st_wow_info.st_wow_cfg.ul_wow_event = MAC_WOW_FIELD_MAGIC_PACKET | MAC_WOW_FIELD_NETPATTERN_TCP | MAC_WOW_FIELD_NETPATTERN_UDP
                              | MAC_WOW_FIELD_AUTH_RX | MAC_WOW_FIELD_TCP_UDP_KEEP_ALIVE;

    oal_memcopy(&g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[0].auc_pattern_data[0], auc_pattern, OAL_SIZEOF(auc_pattern));
    g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[0].ul_pattern_len = OAL_SIZEOF(auc_pattern);
    g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num = 1;
    g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map |= BIT0;

    hmac_wow_create_lock();

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    /* If ANY */
    /*
    hmac_wow_add_pattern(us_pattern_index, ul_pattern_len, puc_pattern);
    */
#endif

    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_init, time = %d}",hmac_wow_get_time());

    #if 0
    /* 下发参数到 DMAC */
    if (!g_ul_wlan_resume_wifi_init_flag)
    {
        hmac_wow_set_dmac_cfg();
    }
    #endif

    g_st_wow_info.uc_is_wow_init = HMAC_WOW_MODULE_STATE_INIT;
}

/*****************************************************************************
 函 数 名  : hmac_wow_get_cfg_vap
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void* hmac_wow_get_cfg_vap(oal_void)
{
    return mac_res_get_mac_vap(0);
}

/*****************************************************************************
 函 数 名  : hmac_wow_tx_check_filter_switch
 功能描述  : 判断当前状态是否需要进入 wow 过滤接口
 输入参数  :
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_tx_check_filter_switch(
                oal_void
                )
{
    oal_uint8 uc_sleep_state;

    uc_sleep_state = hmac_wow_get_host_state();

    if (MAC_WOW_ENABLE == g_st_wow_info.st_wow_cfg.uc_wow_en)
    {
        if (HMAC_HOST_STATE_SLEEP_REQ                   == uc_sleep_state
         || HMAC_HOST_STATE_DEV_READY_FOR_HOST_SLEEP    == uc_sleep_state
         || HMAC_HOST_STATE_HOST_READY                  == uc_sleep_state
         || HMAC_HOST_STATE_SLEPT                       == uc_sleep_state)
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_wow_stop_scan_assoc
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_stop_scan_assoc(oal_void)
{
    oal_uint32   ul_netdev_index;

    /* 停止扫描 */
    for (ul_netdev_index = 0; ul_netdev_index < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_netdev_index++)
    {
        if ((OAL_PTR_NULL != g_past_net_device[ul_netdev_index]))
        {
            wal_force_scan_complete(g_past_net_device[ul_netdev_index], OAL_TRUE);
        }
    }

    /* 停止未完成的关联----非镜像模式无需处理 */
    //remove user not associated
    //per VAP, per USER

    /* 清空 HMAC层TID信息----非镜像模式无需处理 */
    //hmac_tid_clear(pst_mac_vap, pst_hmac_user_sta);
    //per VAP, per USER
}

/*****************************************************************************
 函 数 名  : hmac_wow_stop_upper_layer_queue
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_stop_upper_layer_queue(oal_void)
{
    oal_uint32   ul_netdev_index;

    for (ul_netdev_index = 0; ul_netdev_index < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_netdev_index++)
    {
        if ((OAL_PTR_NULL != g_past_net_device[ul_netdev_index]))
        {
            /*stop the netdev's queues*/
            oal_net_tx_stop_all_queues(g_past_net_device[ul_netdev_index]);/* 停止发送队列 */
        }
    }
}

/*****************************************************************************
 函 数 名  : hmac_wow_clear_data_channal
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_clear_data_channal(oal_void)
{
    hcc_clear_all_queues(hcc_get_default_handler(), OAL_TRUE);
#if 0
    oal_uint32      ul_hcc_cnt = 0;
    oal_uint32      ul_queue_id = 0;
    hcc_handler     *pst_hcc_handler = OAL_PTR_NULL;
    hcc_trans_queue *pst_hcc_queue;

    pst_hcc_handler = hcc_get_default_handler();

    /* 清理数据 */
    for (ul_hcc_cnt = 0; ul_hcc_cnt < HCC_DIR_COUNT; ul_hcc_cnt++)
    {
        for (ul_queue_id = 0; ul_queue_id < HCC_QUEUE_COUNT; ul_queue_id++)
        {
            pst_hcc_queue = &pst_hcc_handler->hcc_transer_info.hcc_queues[HCC_TX].queues[ul_queue_id];
            oal_netbuf_free_list(&pst_hcc_queue->data_queue, oal_netbuf_list_len(&pst_hcc_queue->data_queue));
        }
    }
#endif
}

/*****************************************************************************
 函 数 名  : hmac_wow_clear_event_queue
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_clear_event_queue(oal_void)
{
    /* 清理事件 */
}

/*****************************************************************************
 函 数 名  : hmac_wow_prepare_wakeup
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_prepare_wakeup(oal_void)
{
    /* wakeup 后操作 */
}

/*****************************************************************************
 函 数 名  : hmac_wow_host_sleep_cmd
 功能描述  :
 输入参数  : mac_vap_stru  *pst_mac_vap
             oal_uint32     ul_is_host_sleep
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_host_sleep_cmd(oal_uint32 ul_is_host_sleep)
{
    if (ul_is_host_sleep)
    {
        hmac_wow_host_sleep_request();
    }
    else
    {
        hmac_wow_host_wakeup_notify();
    }
}

/*****************************************************************************
 函 数 名  : hmac_wow_set_wow_cmd
 功能描述  :
 输入参数  : oal_uint32 ul_wow_event
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_set_wow_cmd(oal_uint32 ul_wow_event)
{
    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_set_wow_cmd, ul_wow_event[0x%x]}", ul_wow_event);

    g_st_wow_info.st_wow_cfg.ul_wow_event = ul_wow_event;

    /* 下发参数到 DMAC */
    hmac_wow_set_dmac_cfg();
}

/*****************************************************************************
 函 数 名  : hmac_wow_set_wow_en_cmd
 功能描述  :
 输入参数  : oal_uint32 ul_wow_en
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_set_wow_en_cmd(oal_uint32 ul_wow_en)
{
    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_set_wow_en_cmd, ul_wow_en[0x%x]}", ul_wow_en);

    g_st_wow_info.st_wow_cfg.uc_wow_en = (oal_uint8)ul_wow_en;

    if (!g_st_wow_info.st_wow_cfg.uc_wow_en)
    {
        g_st_wow_info.uc_host_sleep_state = HMAC_HOST_STATE_WAKEUP;
    }

    /* 下发参数到 DMAC */
    hmac_wow_set_dmac_cfg();
}

/*****************************************************************************
 函 数 名  : hmac_wow_add_pattern
 功能描述  :
 输入参数  : oal_uint16 us_pattern_index,
             oal_uint32 ul_pattern_len,
             oal_uint8 *puc_pattern
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_wow_add_pattern(oal_uint16 us_pattern_index, oal_uint32 ul_pattern_len, oal_uint8 *puc_pattern)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_pattern))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd::puc_pattern is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WOW_NETPATTERN_MAX_NUM <= us_pattern_index
        || 0 == ul_pattern_len
        || WOW_NETPATTERN_MAX_LEN < ul_pattern_len)
    {
        OAM_ERROR_LOG2(0, OAM_SF_WOW, "{hmac_wow_add_pattern:: param error, index = %d, len = %d.}", us_pattern_index, ul_pattern_len);
        return OAL_FAIL;
    }

    oal_memcopy(g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[us_pattern_index].auc_pattern_data, puc_pattern, ul_pattern_len);
    g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[us_pattern_index].ul_pattern_len = ul_pattern_len;

    if (!((1<<us_pattern_index) & g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map))
    {
        g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map |= (1<<us_pattern_index);
        g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num ++;
    }

    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd, add new pattern, len[%d], total_num[%d]}",
                        ul_pattern_len, g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_wow_set_pattern_cmd
 功能描述  :
 输入参数  : hmac_cfg_wow_pattern_param_stru * pst_pattern
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_wow_set_pattern_cmd(hmac_cfg_wow_pattern_param_stru * pst_pattern)
{
    oal_uint8   uc_is_del;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_pattern))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd::pst_pattern is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_WOW_PATTERN_PARAM_OPTION_ADD == pst_pattern->us_pattern_option)
    {
        if (WOW_NETPATTERN_MAX_NUM <= pst_pattern->us_pattern_index
         || 0 == pst_pattern->ul_pattern_len
         || WOW_NETPATTERN_MAX_LEN < pst_pattern->ul_pattern_len)
        {
            OAM_ERROR_LOG2(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd::ADD::param error, index = %d, len = %d.}", pst_pattern->us_pattern_index, pst_pattern->ul_pattern_len);
            return OAL_FAIL;
        }
        oal_memcopy(g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[pst_pattern->us_pattern_index].auc_pattern_data,
                    pst_pattern->auc_pattern_value, pst_pattern->ul_pattern_len);
        g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[pst_pattern->us_pattern_index].ul_pattern_len = pst_pattern->ul_pattern_len;

        if (!((1<< pst_pattern->us_pattern_index) & g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map))
        {
            g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map |= (1<< pst_pattern->us_pattern_index);
            g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num ++;
        }

        OAM_WARNING_LOG4(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd, add new pattern, len[%d], total_num[%d], Value[%X][%X]}",
                        pst_pattern->ul_pattern_len, g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num,pst_pattern->auc_pattern_value[0],pst_pattern->auc_pattern_value[1]);

    }
    else if (MAC_WOW_PATTERN_PARAM_OPTION_DEL == pst_pattern->us_pattern_option)
    {
        if (WOW_NETPATTERN_MAX_NUM <= pst_pattern->us_pattern_index)
        {
            OAM_ERROR_LOG1(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd::DEL: param error, index = %d}", pst_pattern->ul_pattern_len);
            return OAL_FAIL;
        }
        if ((1<< pst_pattern->us_pattern_index) & g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map)
        {
            g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_map &= ~(1<< pst_pattern->us_pattern_index);
            g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num --;

            g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[pst_pattern->us_pattern_index].ul_pattern_len = 0;
            OAL_MEMZERO(g_st_wow_info.st_wow_cfg.st_wow_pattern.ast_pattern[pst_pattern->us_pattern_index].auc_pattern_data, WOW_NETPATTERN_MAX_LEN);

            uc_is_del = OAL_TRUE;
        }
        else
        {
            uc_is_del = OAL_FALSE;
        }

        OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd, del pattern, is_del[%d], total_num[%d]}",
                uc_is_del, g_st_wow_info.st_wow_cfg.st_wow_pattern.us_pattern_num);

    }
    else if (MAC_WOW_PATTERN_PARAM_OPTION_CLR == pst_pattern->us_pattern_option)
    {
        OAL_MEMZERO(&g_st_wow_info.st_wow_cfg.st_wow_pattern, OAL_SIZEOF(g_st_wow_info.st_wow_cfg.st_wow_pattern));
        OAM_WARNING_LOG0(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd, pattern clear}");
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_set_pattern_cmd, error option[%d]}", pst_pattern->us_pattern_option);
    }

    /* 下发参数到 DMAC */
    hmac_wow_set_dmac_cfg();

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_wow_host_sleep_request_asyn_handle
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_wow_host_sleep_request_asyn_handle(oal_void)
{
    oal_uint32 ul_ret;

    {
    /*
    这里需要异步操作 或者 外部循环， 等 liteos 接口明了
    */
    hmac_wow_set_host_state(HMAC_HOST_STATE_SLEEP_REQ);

    ul_ret = hmac_wow_host_sleep_wakeup_notify(MAC_WOW_SLEEP_REQUEST);

    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_host_sleep_request_asyn_handle, ret = %d}", ul_ret);

    hmac_wow_stop_scan_assoc();

    hmac_wow_stop_upper_layer_queue();

    hmac_wow_clear_data_channal();

    hmac_wow_clear_event_queue();

    hmac_wow_enable_pm(OAL_TRUE);

    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_wow_host_wakeup_notify_asyn_handle
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_wow_host_wakeup_notify_asyn_handle(oal_void)
{
    oal_uint32 ul_ret;

    {
    /*
    这里需要异步操作 或者 外部循环， 等 liteos 接口明了
    */

    hmac_wow_set_host_state(HMAC_HOST_STATE_WAKEUP);

    /* 获取锁 */
    //hmac_wow_obtain_lock();

    ul_ret = hmac_wow_host_sleep_wakeup_notify(MAC_WOW_WAKEUP_NOTIFY);

    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_host_wakeup_notify_asyn_handle, ret = %d}", ul_ret);

    hmac_wow_enable_pm(OAL_FALSE);

    hmac_wow_prepare_wakeup();

    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_wow_host_sleep_request
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/* 此函数由 平台调用，需求为外部线程 */
oal_uint32 hmac_wow_host_sleep_request(oal_void)
{
    oal_uint8  uc_sleep_state;

    uc_sleep_state = hmac_wow_get_host_state();

    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_host_sleep_request, time = %d, uc_sleep_state = %d}",hmac_wow_get_time(),uc_sleep_state);

    if (HMAC_HOST_STATE_WAKEUP == uc_sleep_state)
    {
        /* 需要给 host 发个消息,调用线程通信接口  */
        //hmac_wow_notify_wifi_drv(OAL_TRUE);
        hmac_wow_set_host_state(HMAC_HOST_STATE_SLEEP_REQ);

        /* for debug */
        hmac_wow_host_sleep_request_asyn_handle();

        /* 获取锁, 被挂起 */
        hmac_wow_obtain_lock();

    }
    else
    {
        OAM_ERROR_LOG2(0, OAM_SF_WOW, "{hmac_wow_host_sleep_request:: ERROR_state[%d], Expect_state[%d]!}",
                        uc_sleep_state, HMAC_HOST_STATE_WAKEUP);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_wow_host_wakeup_notify
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/* 此函数由平台调用，需求为外部本线程，如果不是则需要调用线程通信接口 */
oal_uint32 hmac_wow_host_wakeup_notify(oal_void)
{
    oal_uint8  uc_sleep_state;

    uc_sleep_state = hmac_wow_get_host_state();

    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_host_wakeup_notify, time = %d, uc_sleep_state = %d}",hmac_wow_get_time(),uc_sleep_state);
    if (HMAC_HOST_STATE_SLEPT == uc_sleep_state)
    {
        /* 需要给 host 发个消息,调用线程通信接口  */
        //hmac_wow_notify_wifi_drv(OAL_FALSE);
        hmac_wow_set_host_state(HMAC_HOST_STATE_WAKEUP);

        /* for debug */
        hmac_wow_host_wakeup_notify_asyn_handle();
    }
    else
    {
        OAM_ERROR_LOG2(0, OAM_SF_WOW, "{hmac_wow_host_wakeup_notify:: ERROR_state[%d], Expect_state[%d]!}",
                        uc_sleep_state, HMAC_HOST_STATE_SLEPT);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_wow_create_lock
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_create_lock(oal_void)
{
    OAL_INIT_COMPLETION(&g_st_wow_info.st_sleep_req_done_event);
}

/*****************************************************************************
 函 数 名  : hmac_wow_obtain_lock
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_obtain_lock(oal_void)
{
    oal_uint32 ul_ret = 0;

    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_obtain_lock, Enter, time = %d, uc_sleep_state = %d}",hmac_wow_get_time(),hmac_wow_get_host_state());

    ul_ret = oal_wait_for_completion_timeout(&g_st_wow_info.st_sleep_req_done_event, (oal_uint32)OAL_MSECS_TO_JIFFIES(WOW_SLEEP_REQ_WAIT_TIMEOUT));

    if (0 == ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_WOW, "hmac_wow_obtain_lock, -> timeout[%d]!!!\n",ul_ret);
    }

    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{hmac_wow_obtain_lock, Exit, time = %d, uc_sleep_state = %d}",hmac_wow_get_time(),hmac_wow_get_host_state());
}

/*****************************************************************************
 函 数 名  : hmac_wow_release_lock
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_release_lock(oal_void)
{
    OAM_WARNING_LOG0(0, OAM_SF_WOW, "hmac_wow_release_lock Enter\n");
    OAL_COMPLETE(&g_st_wow_info.st_sleep_req_done_event);
}

/*****************************************************************************
 函 数 名  : hmac_wow_trigger_host_state
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
/* 如果此处还没有准备好，则需要在其他地方异步 hmac_wow_release_lock(); */
oal_void hmac_wow_trigger_host_state(oal_void)
{
    if (HMAC_HOST_STATE_DEV_READY_FOR_HOST_SLEEP == hmac_wow_get_host_state())
    {
        /* if HOST is ready*/
        /* TBD */

        hmac_wow_set_host_state(HMAC_HOST_STATE_HOST_READY);

        /* 确保镜像中为 SLEPT 状态 */
        hmac_wow_set_host_state(HMAC_HOST_STATE_SLEPT);

        /* 释放锁 */
        hmac_wow_release_lock();
    }
}

/*****************************************************************************
 函 数 名  : hmac_wow_proc_dev_ready_slp_event
 功能描述  :
 输入参数  : frw_event_mem_stru *pst_event_mem
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_proc_dev_ready_slp_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hmac_vap_stru           *pst_hmac_vap;
    oal_uint8                uc_param;
    //oal_uint8                uc_sleep_state;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_proc_dev_ready_slp_event::pst_event_mem is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event    = (frw_event_stru *)pst_event_mem->puc_data;
    uc_param     = *(oal_uint8 *)pst_event->auc_event_data;
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_proc_dev_ready_slp_event::pst_hmac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_wow_proc_dev_ready_slp();

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_wow_proc_dev_ready_slp
 功能描述  : Device is ready for Host's sleep request.
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_proc_dev_ready_slp(oal_void)
{
    oal_uint8   uc_sleep_state;

    OAM_WARNING_LOG0(0, OAM_SF_WOW, "hmac_wow_proc_dev_ready_slp Enter\n");

    uc_sleep_state = hmac_wow_get_host_state();

    if (HMAC_HOST_STATE_SLEEP_REQ == uc_sleep_state)
    {
        hmac_wow_set_host_state(HMAC_HOST_STATE_DEV_READY_FOR_HOST_SLEEP);

        /* 检查是否可以直接 unlock */
        hmac_wow_trigger_host_state();
    }
    else if (HMAC_HOST_STATE_HOST_READY == uc_sleep_state)
    {
        /* 确保镜像中为 SLEPT 状态 */
        hmac_wow_set_host_state(HMAC_HOST_STATE_SLEPT);

        /* 释放锁 */
        hmac_wow_release_lock();
    }
    else
    {
        OAM_ERROR_LOG3(0, OAM_SF_WOW, "{hmac_wow_proc_dev_ready_slp:: ERROR_state[%d], Expect_state[%d][%d]!}",
                       uc_sleep_state, HMAC_HOST_STATE_SLEEP_REQ, HMAC_HOST_STATE_HOST_READY);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_wow_msg_handle
 功能描述  : 处理device侧发来的msg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hmac_wow_msg_handle(void *data)
{
    OAM_WARNING_LOG0(0, OAM_SF_WOW, "hmac_wow_msg_handle Enter\n");
    hmac_wow_proc_dev_ready_slp();
}

/*****************************************************************************
 函 数 名  : hmac_wow_proc_dev_sync_host_event
 功能描述  : dmac 唤醒后同步 host data
 输入参数  : frw_event_mem_stru *pst_event_mem
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_proc_dev_sync_host_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;
    dmac_tx_event_stru    *pst_ctx_event;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_proc_dev_sync_host_event::pst_event_mem is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_WOW, "{hmac_wow_proc_dev_sync_host_event:: enter.}");

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    /* DATA process, TBD */


    /* 释放同步消息的netbuf信息 */
    oal_netbuf_free(pst_ctx_event->pst_netbuf);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : hmac_wow_set_dmac_cfg
 功能描述  : H2D WOW 参数下发
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_set_dmac_cfg(oal_void)
{
    oal_uint32    ul_ret;
    mac_vap_stru *pst_mac_vap;

    OAM_WARNING_LOG1(0, OAM_SF_WOW, "hmac_wow_set_dmac_cfg, flag[%d]\n",g_ul_wlan_resume_wifi_init_flag);

    if (1 == g_ul_wlan_resume_wifi_init_flag)
    {
        return OAL_SUCC;
    }

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(0);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_set_dmac_cfg::pst_mac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /***************************************************************************
        抛事件到DMAC层, 同步DMAC数据
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_SET_WOW_PARAM, OAL_SIZEOF(g_st_wow_info.st_wow_cfg), (oal_uint8 *)&g_st_wow_info.st_wow_cfg);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_WOW, "{hmac_wow_set_dmac_cfg::send_event failed[%d]}", ul_ret);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_wow_host_sleep_wakeup_notify
 功能描述  : H2D 睡眠/唤醒通知
 输入参数  : oal_uint8 uc_is_sleep_req
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_host_sleep_wakeup_notify(oal_uint8 uc_is_sleep_req)
{
#ifndef WOW_USE_CHANNEL_MSG
    oal_uint32    ul_ret;
    mac_vap_stru *pst_mac_vap;

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(0);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{hmac_wow_host_sleep_wakeup_notify::pst_mac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /***************************************************************************
        抛事件到DMAC层, 同步DMAC数据
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_HOST_SLEEP_NOTIFY, OAL_SIZEOF(oal_uint8), &uc_is_sleep_req);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WOW, "{hmac_config_host_sleep_wakeup_notify::send_event failed[%d],uc_is_sleep_req = %d}",
                        ul_ret, uc_is_sleep_req);
    }

    return ul_ret;

#else
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint32           ul_msg_type = 0;

    /* 唤醒通道 */
    wlan_pm_wakeup_channel();

    ul_msg_type = (uc_is_sleep_req)?(H2D_MSG_WOW_WIFI_SUSPEND):(H2D_MSG_WOW_WIFI_RESUME);

#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_lock(pst_wlan_pm->pst_usb);
    oal_usb_send_msg(pst_wlan_pm->pst_usb, ul_msg_type);
    oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    oal_sdio_send_msg(pst_wlan_pm->pst_sdio, ul_msg_type);
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif

#endif
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
oal_uint32 wlan_data_backup_process(oal_void)
{
    oal_int32   l_flag;
    OAM_WARNING_LOG0(0, OAM_SF_WOW, "wlan_data_backup_process::backup begin!!");
    if (OAL_SUCC != hmac_backup_data())
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{fail to backup hmac data.}");
        return OAL_FAIL;
    }

    if (OAL_SUCC != save_wpa_supplicant_data())
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{fail to backup wpa_supplicant data.}");
        return OAL_FAIL;
    }

    if (OAL_SUCC != lwip_save_info("wlan0"))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WOW, "{fail to backup lwip data.}");
        return OAL_FAIL;
    }
    l_flag = g_st_data_process_interface.save_data_cb();
    if(l_flag !=0)
    {
       OAM_ERROR_LOG0(0, OAM_SF_WOW, "fail to power off process\n");
       return OAL_FAIL;
    }
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : wlan_suspend
 功能描述  : 睡眠入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_suspend(oal_void)
{
    OAM_WARNING_LOG0(0, OAM_SF_WOW, "{wlan_suspend.}");

    wlan_pm_set_forceslp();

    /* 业务暂停接口 */
    wlan_wifi_suspend();

    /* 平台暂停接口 */
    wlan_pm_suspend();
    /* 备份数据 */
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    wlan_data_backup_process();
#endif
    //LOS_MakeImage();

    OAM_WARNING_LOG0(0, OAM_SF_WOW, "{host_pow_off.}");

    /* 平台下电接口 */
    //host_pow_off();
}

/*****************************************************************************
 函 数 名  : wlan_resume
 功能描述  : 被唤醒入口，恢复入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_resume(oal_void)
{
    OAM_WARNING_LOG1(0, OAM_SF_WOW, "{wlan_resume, time = %d}",hmac_wow_get_time());

    wlan_pm_set_forceslp_wakeup();

    hmac_wow_init();
    hmac_wow_set_host_state(HMAC_HOST_STATE_SLEPT);

    /* 镜像恢复接口  */
    //LOS_RestoreImage();

    /* 平台恢复接口 */
    wlan_pm_resume();

    /* 业务恢复接口 */
    wlan_wifi_resume();
}

/*****************************************************************************
 函 数 名  : wlan_wifi_suspend
 功能描述  : 业务暂停接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_wifi_suspend(oal_void)
{
    /* sleep req */
    hmac_wow_host_sleep_request();
}

/*****************************************************************************
 函 数 名  : wlan_wifi_resume
 功能描述  : 业务恢复接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年7月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_wifi_resume(oal_void)
{
    OAM_WARNING_LOG2(0, OAM_SF_WOW, "{wlan_wifi_resume, time = %d, uc_sleep_state = %d}\n",hmac_wow_get_time(),hmac_wow_get_host_state());

    wifi_init();

    /* wakeup notify */
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    g_ul_wlan_resume_wifi_init_flag = 0;
#endif
    hmac_wow_host_wakeup_notify();
}

/*****************************************************************************
 函 数 名  : hmac_wow_check_event
 功能描述  : 判断当前是否需要过滤事件
 输入参数  :
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_wow_check_event(
                frw_event_hdr_stru *pst_event_hrd,
                oal_uint8           uc_event_dir
                )
{
    oal_uint8 uc_sleep_state;
    oal_uint8 uc_cnt;

    /*
    if (g_ul_wlan_reusme_wifi_mode)
    {
        return FALSE;
    }
    */

    if (OAL_PTR_NULL == pst_event_hrd)
    {
        return FALSE;
    }

    uc_sleep_state = hmac_wow_get_host_state();

    if (OAL_TRUE == hmac_wow_tx_check_filter_switch() &&
      (FRW_EVENT_PIPELINE_STAGE_1 == pst_event_hrd->en_pipeline))
    {
        switch (uc_event_dir)
        {
        case EVENT_TX_TYPE:
            g_st_wow_info.st_event_info.uc_tx_cnt ++;
            uc_cnt = g_st_wow_info.st_event_info.uc_tx_cnt;
            break;
        case EVENT_RX_TYPE:
            g_st_wow_info.st_event_info.uc_rx_cnt ++;
            uc_cnt = g_st_wow_info.st_event_info.uc_rx_cnt;
            break;
        case EVENT_DUAL_TYPE:
            g_st_wow_info.st_event_info.uc_dual_cnt ++;
            uc_cnt = g_st_wow_info.st_event_info.uc_dual_cnt;
            break;
        case EVENT_TYPE_BUTT:
        default:
            return FALSE;
            break;
        }
        OAM_WARNING_LOG4(0, OAM_SF_WOW, "hmac_wow_check_event, wow_blocked, event|sub[0x%08X],dir[%d],cnt[%d]state[%d]\n",
            (pst_event_hrd->en_type<<16)|pst_event_hrd->uc_sub_type,uc_event_dir,uc_cnt,hmac_wow_get_host_state());
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : hmac_wow_enable_pm
 功能描述  : 低功耗下业务开关配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月05日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_wow_enable_pm(oal_uint8 uc_pm_enable)
{
    mac_device_stru  *pst_mac_device = mac_res_get_dev(0);

    if ((OAL_TRUE == uc_pm_enable)
#ifdef _PRE_WLAN_FEATURE_WAPI
     && (OAL_TRUE != pst_mac_device->uc_wapi)
#endif
        )
    {
        pst_mac_device->uc_arpoffload_switch = OAL_TRUE;
    }
    else
    {
        pst_mac_device->uc_arpoffload_switch = OAL_FALSE;
    }
}

oal_module_symbol(hmac_wow_host_sleep_request);
oal_module_symbol(hmac_wow_host_wakeup_notify);
oal_module_symbol(hmac_wow_proc_dev_ready_slp_event);
oal_module_symbol(hmac_wow_proc_dev_sync_host_event);
oal_module_symbol(hmac_wow_set_wow_en_cmd);
oal_module_symbol(hmac_wow_tx_check_filter_switch);
oal_module_symbol(hmac_wow_set_pattern_cmd);
oal_module_symbol(hmac_wow_set_wow_cmd);
oal_module_symbol(hmac_wow_init);
oal_module_symbol(hmac_wow_host_sleep_cmd);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif //#ifdef _PRE_WLAN_FEATURE_WOW

#endif //#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

