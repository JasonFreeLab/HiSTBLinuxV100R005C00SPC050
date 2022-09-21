/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_fsm.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月18日
  最近修改   :
  功能描述   : 全局静态状态机二维函数表
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月18日
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
#include "hmac_fsm.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_scan.h"
#include "hmac_mgmt_sta.h"
#include "hmac_mgmt_ap.h"
#include "frw_ext_if.h"
#include "hmac_config.h"
#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FSM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 全局状态机函数表 */
OAL_STATIC hmac_fsm_func   g_pa_hmac_ap_fsm_func[MAC_VAP_AP_STATE_BUTT][HMAC_FSM_AP_INPUT_TYPE_BUTT];
OAL_STATIC hmac_fsm_func   g_pa_hmac_sta_fsm_func[MAC_VAP_STA_STATE_BUTT][HMAC_FSM_STA_INPUT_TYPE_BUTT];


/*****************************************************************************
 函 数 名  : hmac_fsm_set_state
 功能描述  : 改变状态机状态
 输入参数  : pst_hmac_vap: HMAC VAP
             en_vap_state: 要切换到的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_fsm_change_state(hmac_vap_stru *pst_hmac_vap, mac_vap_state_enum_uint8 en_vap_state)
{
    mac_cfg_mode_param_stru  st_cfg_mode;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_vap_state_enum_uint8 en_old_state;
    oal_uint32 ul_ret;
    en_old_state = pst_hmac_vap->st_vap_base_info.en_vap_state;
#endif

    /*将vap状态改变信息上报*/
    mac_vap_state_change(&pst_hmac_vap->st_vap_base_info, en_vap_state);

    /* OFFLOAD模式下dmac vap状态同步*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    //en_old_state = pst_hmac_vap->st_vap_base_info.en_vap_state;

    ul_ret = hmac_config_vap_state_syn(&(pst_hmac_vap->st_vap_base_info), sizeof(en_vap_state), (oal_uint8 *)(&en_vap_state));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_fsm_change_state::hmac_syn_vap_state failed[%d], old_state=%d, new_state=%d.}",
                       ul_ret, en_old_state, en_vap_state);
    }

#ifdef _PRE_WLAN_FEATURE_STA_PM

    /* STA 模式下只有UP状态才开启低功耗开关定时器 */
    if(MAC_VAP_STATE_UP == en_vap_state)
    {
        if (pst_hmac_vap->st_vap_base_info.en_vap_mode == WLAN_VAP_MODE_BSS_STA)
        {
            FRW_TIMER_CREATE_TIMER(&(pst_hmac_vap->st_ps_sw_timer),
                       hmac_set_ipaddr_timeout,
                       HMAC_SWITCH_STA_PSM_PERIOD,
                       (void *)pst_hmac_vap,
                       OAL_FALSE,
                       OAM_MODULE_ID_HMAC,
    				   pst_hmac_vap->st_vap_base_info.ul_core_id);

        }
    }
#endif

#endif
    /* 设置帧过滤寄存器 */
    hmac_set_rx_filter_value(&pst_hmac_vap->st_vap_base_info);

    if ((MAC_VAP_STATE_STA_FAKE_UP == en_vap_state)
        && (pst_hmac_vap->st_vap_base_info.en_vap_mode == WLAN_VAP_MODE_BSS_STA))
    {

        st_cfg_mode.en_protocol  = pst_hmac_vap->st_preset_para.en_protocol;
        st_cfg_mode.en_band      = pst_hmac_vap->st_preset_para.en_band;
        st_cfg_mode.en_bandwidth = pst_hmac_vap->st_preset_para.en_bandwidth;

        hmac_config_sta_update_rates(&(pst_hmac_vap->st_vap_base_info), &st_cfg_mode, OAL_PTR_NULL);
    }

}

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_fsm_null_fn
 功能描述  : 空函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_fsm_null_fn(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    /* 什么都不做 */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_fsm_init_ap
 功能描述  : 初始化ap状态机函数表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_fsm_init_ap(oal_void)
{
    oal_uint32  ul_state;
    oal_uint32  ul_input;

    for (ul_state = 0; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
    {
        for (ul_input = 0; ul_input < HMAC_FSM_AP_INPUT_TYPE_BUTT; ul_input++)
        {
            g_pa_hmac_ap_fsm_func[ul_state][ul_input] = hmac_fsm_null_fn;
        }
    }

    /* 接收管理帧输入
    +----------------------------------+---------------------
     | FSM State                        | FSM Function
     +----------------------------------+---------------------
     | MAC_VAP_STATE_INIT               | null_fn
     | MAC_VAP_STATE_UP                 | hmac_ap_up_rx_mgmt
     | MAC_VAP_STATE_PAUSE              | null_fn
     +----------------------------------+---------------------
    */
    g_pa_hmac_ap_fsm_func[MAC_VAP_STATE_AP_WAIT_START][HMAC_FSM_INPUT_RX_MGMT] = hmac_ap_wait_start_rx_mgmt;
    g_pa_hmac_ap_fsm_func[MAC_VAP_STATE_AP_WAIT_START][HMAC_FSM_INPUT_MISC]    = hmac_ap_wait_start_misc;

    g_pa_hmac_ap_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_RX_MGMT] = hmac_ap_up_rx_mgmt;
    g_pa_hmac_ap_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_MISC]    = hmac_ap_up_misc;
}

/*****************************************************************************
 函 数 名  : hmac_fsm_init_sta
 功能描述  : 初始化sta状态机函数表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void hmac_fsm_init_sta(oal_void)
{
    oal_uint32  ul_state;

    /* 初始化扫描请求输入函数 HMAC_FSM_INPUT_SCAN_REQ
     +----------------------------------+---------------------
     | FSM State                        | FSM Function
     +----------------------------------+---------------------
     | MAC_VAP_STATE_INIT               | null_fn
     | MAC_VAP_STATE_UP                 | null_fn
     | MAC_VAP_STATE_FAKE_UP            | hmac_mgmt_scan_req
     | MAC_VAP_STATE_WAIT_SCAN          | null_fn
     | MAC_VAP_STATE_SCAN_COMP          | hmac_mgmt_scan_req
     | MAC_VAP_STATE_WAIT_JOIN          | null_fn
     | MAC_VAP_STATE_JOIN_COMP          | hmac_mgmt_scan_req
     | MAC_VAP_STATE_WAIT_AUTH_SEQ2     | null_fn
     | MAC_VAP_STATE_WAIT_AUTH_SEQ4     | null_fn
     | MAC_VAP_STATE_AUTH_COMP          | hmac_mgmt_scan_req
     | MAC_VAP_STATE_WAIT_ASOC          | null_fn
     | MAC_VAP_STATE_OBSS_SCAN          | null_fn
     | MAC_VAP_STATE_BG_SCAN            | null_fn
     +----------------------------------+---------------------
    */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_SCAN_REQ] = hmac_scan_proc_scan_req_event_exception;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_INIT][HMAC_FSM_INPUT_SCAN_REQ]   = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_FAKE_UP][HMAC_FSM_INPUT_SCAN_REQ]   = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_SCAN_COMP][HMAC_FSM_INPUT_SCAN_REQ] = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_JOIN_COMP][HMAC_FSM_INPUT_SCAN_REQ] = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_AUTH_COMP][HMAC_FSM_INPUT_SCAN_REQ] = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_SCAN_REQ]            = hmac_scan_proc_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_LISTEN][HMAC_FSM_INPUT_SCAN_REQ]    = hmac_scan_proc_scan_req_event;


    /* Initialize the elements in the JOIN_REQ input column. This input is   */
    /* valid only in the SCAN_COMP state.                                    */
    /*                                                                       */
    /* +------------------+---------------------+                            */
    /* | FSM State        | FSM Function        |                            */
    /* +------------------+---------------------+                            */
    /* | SCAN_COMP        | hmac_sta_wait_join  |                            */
    /* | All other states | null_fn             |                            */
    /* +------------------+---------------------+                            */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_JOIN_REQ] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_FAKE_UP][HMAC_FSM_INPUT_JOIN_REQ]   = hmac_sta_wait_join;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_SCAN_COMP][HMAC_FSM_INPUT_JOIN_REQ] = hmac_sta_wait_join;

    /* Initialize the elements in the AUTH_REQ input column. This input is   */
    /* valid only in the JOIN_COMP state.                                    */
    /*                                                                       */
    /* +------------------+---------------------+                            */
    /* | FSM State        | FSM Function        |                            */
    /* +------------------+---------------------+                            */
    /* | JOIN_COMP        | hmac_sta_wait_auth  |                            */
    /* | All other states | null_fn             |                            */
    /* +------------------+---------------------+                            */

    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_AUTH_REQ] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_JOIN_COMP][HMAC_FSM_INPUT_AUTH_REQ] = hmac_sta_wait_auth;


    /* Initialize the elements in the ASOC_REQ input column. This input is   */
    /* valid only in the AUTH_COMP state.                                    */
    /*                                                                       */
    /* +------------------+---------------------+                            */
    /* | FSM State        | FSM Function        |                            */
    /* +------------------+---------------------+                            */
    /* | AUTH_COMP        | hmac_sta_wait_asoc       |                            */
    /* | All other states | null_fn             |                            */
    /* +------------------+---------------------+                            */

    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_ASOC_REQ] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_AUTH_COMP][HMAC_FSM_INPUT_ASOC_REQ] = hmac_sta_wait_asoc;


    /* Initialize the elements in the HMAC_FSM_INPUT_RX_MGMT input column. The   */
    /* functions for all the states with this input is listed below.         */
    /*                                                                       */
    /*
     +----------------------------------+---------------------
     | FSM State                        | FSM Function
     +----------------------------------+---------------------
     | MAC_VAP_STATE_INIT               | null_fn
     | MAC_VAP_STATE_UP                 | hmac_sta_up_rx_mgmt
     | MAC_VAP_STATE_FAKE_UP            | null_fn
     | MAC_VAP_STATE_WAIT_SCAN          | hmac_sta_wait_scan_rx
     | MAC_VAP_STATE_SCAN_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_JOIN          | hmac_sta_wait_join_rx
     | MAC_VAP_STATE_JOIN_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_AUTH_SEQ2     | hmac_sta_wait_auth_seq2_rx
     | MAC_VAP_STATE_WAIT_AUTH_SEQ4     | hmac_sta_wait_auth_seq4_rx
     | MAC_VAP_STATE_AUTH_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_ASOC          | hmac_sta_wait_asoc_rx
     | MAC_VAP_STATE_OBSS_SCAN          | null_fn
     | MAC_VAP_STATE_BG_SCAN            | null_fn
     +----------------------------------+---------------------
    */

    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_RX_MGMT] = hmac_fsm_null_fn;
    }

    /* 增加 HMAC_FSM_INPUT_RX_MGMT事件 处理函数 */
    /* g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_JOIN_COMP][HMAC_FSM_INPUT_RX_MGMT]      = hmac_sta_scan_comp_rx;*/
    //g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_JOIN][HMAC_FSM_INPUT_RX_MGMT]      = hmac_sta_wait_join_rx;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2][HMAC_FSM_INPUT_RX_MGMT] = hmac_sta_wait_auth_seq2_rx;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4][HMAC_FSM_INPUT_RX_MGMT] = hmac_sta_wait_auth_seq4_rx;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_ASOC][HMAC_FSM_INPUT_RX_MGMT]      = hmac_sta_wait_asoc_rx;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_RX_MGMT]                 = hmac_sta_up_rx_mgmt;

#ifdef _PRE_WLAN_FEATURE_ROAM
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_ROAMING][HMAC_FSM_INPUT_RX_MGMT]            = hmac_sta_roam_rx_mgmt;
#endif //_PRE_WLAN_FEATURE_ROAM

    /* 增加 HotSpot中状态机sta侧处理函数 */
#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_P2P)
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_SCAN_COMP][HMAC_FSM_INPUT_RX_MGMT]      = hmac_sta_not_up_rx_mgmt;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_SCAN][HMAC_FSM_INPUT_RX_MGMT]      = hmac_sta_not_up_rx_mgmt;
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_FAKE_UP][HMAC_FSM_INPUT_RX_MGMT]        = hmac_sta_not_up_rx_mgmt;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_LISTEN][HMAC_FSM_INPUT_RX_MGMT]         = hmac_sta_not_up_rx_mgmt;
#endif

    /* 初始化timer0超时请求输入函数 HMAC_FSM_INPUT_TIMER0_OUT
     +----------------------------------+---------------------
     | FSM State                        | FSM Function
     +----------------------------------+---------------------
     | MAC_VAP_STATE_INIT               | null_fn
     | MAC_VAP_STATE_PAUSE              | null_fn
     | MAC_VAP_STATE_FAKE_UP            | null_fn
     | MAC_VAP_STATE_WAIT_SCAN          | null_fn
     | MAC_VAP_STATE_SCAN_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_JOIN          | null_fn
     | MAC_VAP_STATE_JOIN_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_AUTH_SEQ2     | null_fn
     | MAC_VAP_STATE_WAIT_AUTH_SEQ4     | null_fn
     | MAC_VAP_STATE_AUTH_COMP          | null_fn
     | MAC_VAP_STATE_WAIT_ASOC          | null_fn
     | MAC_VAP_STATE_OBSS_SCAN          | null_fn
     | MAC_VAP_STATE_BG_SCAN            | null_fn
     +----------------------------------+---------------------
    */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_TIMER0_OUT] = hmac_fsm_null_fn;
    }

    //g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_JOIN][HMAC_FSM_INPUT_TIMER0_OUT]      = hmac_sta_wait_join_timeout;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2][HMAC_FSM_INPUT_TIMER0_OUT] = hmac_sta_auth_timeout;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4][HMAC_FSM_INPUT_TIMER0_OUT] = hmac_sta_auth_timeout;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_ASOC][HMAC_FSM_INPUT_TIMER0_OUT]      = hmac_sta_wait_asoc_timeout;

    /* 初始化HMAC_FSM_INPUT_MISC事件请求的处理函数
       +----------------------------------+---------------------
       | FSM State                        | FSM Function
       +----------------------------------+---------------------
       | MAC_VAP_STATE_INIT               | null_fn
       | MAC_VAP_STATE_PAUSE              | null_fn
       | MAC_VAP_STATE_FAKE_UP            | null_fn
       | MAC_VAP_STATE_WAIT_SCAN          | null_fn
       | MAC_VAP_STATE_SCAN_COMP          | null_fn
       | MAC_VAP_STATE_WAIT_JOIN          | null_fn
       | MAC_VAP_STATE_JOIN_COMP          | null_fn
       | MAC_VAP_STATE_WAIT_AUTH_SEQ2     | null_fn
       | MAC_VAP_STATE_WAIT_AUTH_SEQ4     | null_fn
       | MAC_VAP_STATE_AUTH_COMP          | null_fn
       | MAC_VAP_STATE_WAIT_ASOC          | null_fn
       | MAC_VAP_STATE_OBSS_SCAN          | null_fn
       | MAC_VAP_STATE_BG_SCAN            | null_fn
       +----------------------------------+---------------------
      */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
      g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_MISC] = hmac_fsm_null_fn;
    }

    //g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_WAIT_JOIN][HMAC_FSM_INPUT_MISC] = hmac_sta_wait_join_misc;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* Initialize the elements in the LISTEN_REQ input column. This input is */
    /* valid in the SCAN_COMP and FAKE_UP state.                             */
    /*                                                                       */
    /* +------------------+---------------------+                            */
    /* | FSM State        | FSM Function        |                            */
    /* +------------------+---------------------+                            */
    /* | FAKE_UP          | hmac_sta_wait_listen|                            */
    /* | SCAN_COMP        | hmac_sta_wait_listen|                            */
    /* | All other states | null_fn             |                            */
    /* +------------------+---------------------+                            */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_LISTEN_REQ] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_FAKE_UP][HMAC_FSM_INPUT_LISTEN_REQ]   = hmac_p2p_remain_on_channel;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_SCAN_COMP][HMAC_FSM_INPUT_LISTEN_REQ] = hmac_p2p_remain_on_channel;
    /*  设置P2P 监听超时定时器,
        P2P处于Listen状态下无法下发监听命令，导致Listen状态下不能重新出发监听，无法与商用设备关联 */
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_LISTEN][HMAC_FSM_INPUT_LISTEN_REQ]    = hmac_p2p_remain_on_channel;//在监听状态接收到新的监听命令，则执行新的监听。
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_LISTEN_REQ]            = hmac_p2p_remain_on_channel;

    /* Initialize the elements in the HMAC_FSM_INPUT_LISTEN_TIMEOUT          */
    /* input column. This input is valid in MAC_VAP_STATE_STA_LISTEN state.  */
    /*                                                                       */
    /* +----------------------------+------------------------+               */
    /* | FSM State                  | FSM Function           |               */
    /* +----------------------------+------------------------+               */
    /* | MAC_VAP_STATE_STA_LISTEN   | hmac_p2p_listen_timeout|               */
    /* | All other states           | null_fn                |               */
    /* +----------------------------+------------------------+               */

    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_LISTEN_TIMEOUT] = hmac_fsm_null_fn;
    }
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_LISTEN][HMAC_FSM_INPUT_LISTEN_TIMEOUT] = hmac_p2p_listen_timeout;

#endif  /* _PRE_WLAN_FEATURE_P2P */

    /* Initialize the elements in the SCHED_SCAN_REQ input column. This input is */
    /* valid in the SCAN_COMP and FAKE_UP state.                             */
    /*                                                                       */
    /* +------------------+------------------------------------+             */
    /* | FSM State        | FSM Function                       |             */
    /* +------------------+------------------------------------+             */
    /* | FAKE_UP          | hmac_scan_proc_sched_scan_req_event|             */
    /* | SCAN_COMP        | hmac_scan_proc_sched_scan_req_event|             */
    /* | All other states | null_fn                            |             */
    /* +------------------+------------------------------------+             */
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_SCHED_SCAN_REQ] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_FAKE_UP][HMAC_FSM_INPUT_SCHED_SCAN_REQ]   = hmac_scan_proc_sched_scan_req_event;
    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_STA_SCAN_COMP][HMAC_FSM_INPUT_SCHED_SCAN_REQ] = hmac_scan_proc_sched_scan_req_event;
#ifdef _PRE_WLAN_FEATURE_ROAM
    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
      g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_ROAMING_START] = hmac_fsm_null_fn;
    }

    g_pa_hmac_sta_fsm_func[MAC_VAP_STATE_UP][HMAC_FSM_INPUT_ROAMING_START]       = hmac_roam_pause_user;

    for (ul_state = 0; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
      g_pa_hmac_sta_fsm_func[ul_state][HMAC_FSM_INPUT_ROAMING_STOP] = hmac_roam_resume_user;
    }
#endif //_PRE_WLAN_FEATURE_ROAM
}

/*****************************************************************************
 函 数 名  : hmac_fsm_init
 功能描述  : 初始化状态机处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_fsm_init(oal_void)
{
    /* 初始化ap状态机函数表 */
    hmac_fsm_init_ap();

    /* 初始化sta状态机函数表 */
    hmac_fsm_init_sta();
}

/*****************************************************************************
 函 数 名  : hmac_fsm_call_func_ap
 功能描述  : 调用AP状态机函数表
 输入参数  : pst_hmac_vap: hmac vap
             en_input: 输入类型
             p_param: 输入参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_fsm_call_func_ap(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_fsm_call_func_ap::vap is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*  1102 解决VAP已经删除的情况下，HMAC才处理DMAC抛上来的事件导致状态非法问题 */
    if (MAC_VAP_STATE_BUTT == pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                         "{hmac_fsm_call_func_ap::the vap has been deleted, its state is STATE_BUTT, input type is %d}",
                         en_input);
        return OAL_SUCC;
    }
    else
#endif
    {
        if (pst_hmac_vap->st_vap_base_info.en_vap_state >= MAC_VAP_AP_STATE_BUTT ||
            en_input >= HMAC_FSM_AP_INPUT_TYPE_BUTT)
        {
            OAM_ERROR_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                            "{hmac_fsm_call_func_ap::vap state[%d] or input type[%d] is over limit!}",
                            pst_hmac_vap->st_vap_base_info.en_vap_state, en_input);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }

    return g_pa_hmac_ap_fsm_func[pst_hmac_vap->st_vap_base_info.en_vap_state][en_input](pst_hmac_vap, p_param);
}

/*****************************************************************************
 函 数 名  : hmac_fsm_call_func_sta
 功能描述  : 调用STA状态机函数表
 输入参数  : pst_hmac_vap: hmac vap
             en_input: 输入类型
             p_param: 输入参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_fsm_call_func_sta(hmac_vap_stru *pst_hmac_vap, hmac_fsm_input_type_enum_uint8 en_input, oal_void *p_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_fsm_call_func_sta::vap is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*  解决VAP已经删除的情况下，HMAC才处理DMAC抛上来的事件导致状态非法问题 */
    if (MAC_VAP_STA_STATE_BUTT == pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                         "{hmac_fsm_call_func_sta::the vap has been deleted, its state is STATE_BUTT, input type is %d}",
                         en_input);
        return OAL_SUCC;
    }
    else
#endif
    {
        if (pst_hmac_vap->st_vap_base_info.en_vap_state >= MAC_VAP_STA_STATE_BUTT ||
            en_input >= HMAC_FSM_STA_INPUT_TYPE_BUTT)
        {
            OAM_ERROR_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                            "{hmac_fsm_call_func_sta::vap state[%d] or input type[%d] is over limit!}",
                            pst_hmac_vap->st_vap_base_info.en_vap_state, en_input);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }

    return g_pa_hmac_sta_fsm_func[pst_hmac_vap->st_vap_base_info.en_vap_state][en_input](pst_hmac_vap, p_param);
}











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

