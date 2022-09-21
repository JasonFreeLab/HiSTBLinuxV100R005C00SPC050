/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_roam_connect.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2015年3月18日
  最近修改   :
  功能描述   : 漫游connect流程实现
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
#include "hmac_mgmt_sta.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_tx_amsdu.h"
#include "hmac_rx_data.h"
#include "hmac_chan_mgmt.h"
#include "hmac_11i.h"
#include "hmac_roam_main.h"
#include "hmac_roam_connect.h"
#include "hmac_roam_alg.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_CONNECT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OAL_STATIC hmac_roam_fsm_func g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_BUTT][ROAM_CONNECT_FSM_EVENT_TYPE_BUTT];

OAL_STATIC oal_uint32  hmac_roam_connect_null_fn(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_start_join(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_process_beacon(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_send_auth_seq1(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
#ifdef _PRE_WLAN_FEATURE_11R
OAL_STATIC oal_uint32  hmac_roam_send_ft_req(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32 hmac_roam_process_ft_rsp(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
#endif //_PRE_WLAN_FEATURE_11R
OAL_STATIC oal_uint32  hmac_roam_process_auth_seq2(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_process_assoc_rsp(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_connect_succ(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32  hmac_roam_connect_fail(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);
OAL_STATIC oal_uint32 hmac_roam_connect_terminate(hmac_roam_info_stru *pst_roam_info, oal_void *p_param);

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hmac_roam_connect_fsm_init
 功能描述  : roam connect模块状态-事件-行为表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_roam_connect_fsm_init(oal_void)
{
    oal_uint32  ul_state;
    oal_uint32  ul_event;

    for (ul_state = 0; ul_state < ROAM_CONNECT_STATE_BUTT; ul_state++)
    {
        for (ul_event = 0; ul_event < ROAM_CONNECT_FSM_EVENT_TYPE_BUTT; ul_event++)
        {
            g_hmac_roam_connect_fsm_func[ul_state][ul_event] = hmac_roam_connect_null_fn;
        }
    }
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_INIT][ROAM_CONNECT_FSM_EVENT_START]                = hmac_roam_start_join;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_JOIN][ROAM_CONNECT_FSM_EVENT_MGMT_RX]         = hmac_roam_process_beacon;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_JOIN_COMP][ROAM_CONNECT_FSM_EVENT_TBTT]            = hmac_roam_send_auth_seq1;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_JOIN][ROAM_CONNECT_FSM_EVENT_TIMEOUT]         = hmac_roam_connect_fail;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_JOIN_COMP][ROAM_CONNECT_FSM_EVENT_TIMEOUT]         = hmac_roam_connect_fail;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_AUTH_COMP][ROAM_CONNECT_FSM_EVENT_MGMT_RX]    = hmac_roam_process_auth_seq2;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_AUTH_COMP][ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX] = hmac_roam_connect_terminate;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_AUTH_COMP][ROAM_CONNECT_FSM_EVENT_TIMEOUT]    = hmac_roam_connect_fail;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_ASSOC_COMP][ROAM_CONNECT_FSM_EVENT_MGMT_RX]   = hmac_roam_process_assoc_rsp;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_ASSOC_COMP][ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX] = hmac_roam_connect_terminate;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_ASSOC_COMP][ROAM_CONNECT_FSM_EVENT_TIMEOUT]   = hmac_roam_connect_fail;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_HANDSHAKING][ROAM_CONNECT_FSM_EVENT_KEY_DONE]      = hmac_roam_connect_succ;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_HANDSHAKING][ROAM_CONNECT_FSM_EVENT_TIMEOUT]       = hmac_roam_connect_fail;
#ifdef _PRE_WLAN_FEATURE_11R
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_INIT][ROAM_CONNECT_FSM_EVENT_FT_OVER_DS]           = hmac_roam_send_ft_req;
    g_hmac_roam_connect_fsm_func[ROAM_CONNECT_STATE_WAIT_FT_COMP][ROAM_CONNECT_FSM_EVENT_MGMT_RX]      = hmac_roam_process_ft_rsp;
#endif //_PRE_WLAN_FEATURE_11R
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_fsm_action
 功能描述  : 调用漫游connect状态机函数表
 输入参数  : pst_hmac_vap: hmac vap
             en_event: 事件类型
             p_param: 输入参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_connect_fsm_action(hmac_roam_info_stru *pst_roam_info, roam_connect_fsm_event_type_enum en_event, oal_void *p_param)
{
    if (OAL_PTR_NULL == pst_roam_info)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_roam_info->st_connect.en_state >= ROAM_CONNECT_STATE_BUTT)
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    if (en_event >= ROAM_CONNECT_FSM_EVENT_TYPE_BUTT)
    {
        return OAL_ERR_CODE_ROAM_EVENT_UXEXPECT;
    }

    return g_hmac_roam_connect_fsm_func[pst_roam_info->st_connect.en_state][en_event](pst_roam_info, p_param);
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_change_state
 功能描述  : 改变状态机状态
 输入参数  : pst_hmac_vap      : HMAC VAP
             en_roam_main_state: 要切换到的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2015年3月18日
  作    者   : 
  修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_void  hmac_roam_connect_change_state(hmac_roam_info_stru *pst_roam_info, roam_connect_state_enum_uint8 en_state)
{
    if (pst_roam_info)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ROAM,
                      "{hmac_roam_connect_change_state::[%d]->[%d]}", pst_roam_info->st_connect.en_state, en_state);
        pst_roam_info->st_connect.en_state= en_state;
    }
}
/*****************************************************************************
 函 数 名  : hmac_roam_connect_timeout
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
oal_uint32 hmac_roam_connect_timeout(oal_void *p_arg)
{
    hmac_roam_info_stru *pst_roam_info;

    pst_roam_info = (hmac_roam_info_stru *)p_arg;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_timeout::p_arg is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_timeout::OCCURR.}");

    return hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_TIMEOUT, OAL_PTR_NULL);
}
/*****************************************************************************
 函 数 名  : hmac_roam_connect_null_fn
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
OAL_STATIC oal_uint32  hmac_roam_connect_null_fn(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    /* TBD 维测 */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_start_timer
 功能描述  : 如果定时器已存在，重启，否则创建定时器
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
OAL_STATIC oal_void hmac_roam_connect_start_timer(hmac_roam_info_stru *pst_roam_info, oal_uint32 ul_timeout)
{
    frw_timeout_stru    *pst_timer = &(pst_roam_info->st_connect.st_timer);

    OAM_INFO_LOG1(0, OAM_SF_ROAM, "{hmac_roam_connect_start_timer [%d].}", ul_timeout);

    /* 启动认证超时定时器 */
    FRW_TIMER_CREATE_TIMER(pst_timer,
                           hmac_roam_connect_timeout,
                           ul_timeout,
                           pst_roam_info,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_roam_info->pst_hmac_vap->st_vap_base_info.ul_core_id);
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_del_timer
 功能描述  : 立即删除roam connect定时器
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
OAL_STATIC oal_uint32  hmac_roam_connect_del_timer(hmac_roam_info_stru *pst_roam_info)
{
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_roam_info->st_connect.st_timer));
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_set_join_reg
 功能描述  : 根据bss更新mib信息
 输入参数  : hmac_vap_stru      *pst_hmac_vap,
             mac_bss_dscr_stru  *pst_bss_dscr
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_connect_set_join_reg(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru               *pst_event_mem;
    frw_event_stru                   *pst_event;
    dmac_ctx_join_req_set_reg_stru   *pst_reg_params;

    /* 抛事件DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG到DMAC */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_set_join_reg::pst_event_mem ALLOC FAIL, size = %d.}",
                       OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG,
                       OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_reg_params = (dmac_ctx_join_req_set_reg_stru *)pst_event->auc_event_data;

    /* 设置需要写入寄存器的BSSID信息 */
    oal_set_mac_addr(pst_reg_params->auc_bssid, pst_mac_vap->auc_bssid);

    /* 填写信道相关信息 */
    pst_reg_params->st_current_channel.uc_chan_number = pst_mac_vap->st_channel.uc_chan_number;
    pst_reg_params->st_current_channel.en_band        = pst_mac_vap->st_channel.en_band;
    pst_reg_params->st_current_channel.en_bandwidth   = pst_mac_vap->st_channel.en_bandwidth;
    pst_reg_params->st_current_channel.uc_idx         = pst_mac_vap->st_channel.uc_idx;

    /* 设置dtim period信息 */
    pst_reg_params->us_beacon_period = (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

    /* 同步FortyMHzOperationImplemented */
    pst_reg_params->en_dot11FortyMHzOperationImplemented   = mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap);

    /* 设置beacon filter关闭 */
    pst_reg_params->ul_beacon_filter = OAL_FALSE;

    /* 设置no frame filter打开 */
    pst_reg_params->ul_non_frame_filter = OAL_TRUE;

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_set_dtim_param
 功能描述  : 根据bss更新mib信息
 输入参数  : hmac_vap_stru      *pst_hmac_vap,
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_roam_connect_set_dtim_param(mac_vap_stru *pst_mac_vap, oal_uint32 ul_dtim_cnt, oal_uint32 ul_dtim_period, oal_uint16 us_tsf_bit0)
{
    frw_event_mem_stru               *pst_event_mem;
    frw_event_stru                   *pst_event;
    dmac_ctx_set_dtim_tsf_reg_stru   *pst_set_dtim_tsf_reg_params;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_set_dtim_param, pst_mac_vap = NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 抛事件 DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG 到DMAC, 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_set_dtim_param::pst_event_mem ALLOC FAIL, size = %d.}",
                       OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
                       OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_set_dtim_tsf_reg_params = (dmac_ctx_set_dtim_tsf_reg_stru *)pst_event->auc_event_data;

    /* 将dtim相关参数抛到dmac */
    pst_set_dtim_tsf_reg_params->ul_dtim_cnt        = ul_dtim_cnt;
    pst_set_dtim_tsf_reg_params->ul_dtim_period     = ul_dtim_period;
    oal_memcopy (pst_set_dtim_tsf_reg_params->auc_bssid, pst_mac_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_set_dtim_tsf_reg_params->us_tsf_bit0        = us_tsf_bit0;

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_set_join_params
 功能描述  : 根据bss更新mib信息
 输入参数  : hmac_vap_stru      *pst_hmac_vap,
             mac_bss_dscr_stru  *pst_bss_dscr
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_connect_set_join_params(hmac_vap_stru *pst_hmac_vap, mac_bss_dscr_stru *pst_bss_dscr)
{
    mac_vap_stru                   *pst_mac_vap;
    mac_device_stru                *pst_mac_device;
    wlan_mib_ieee802dot11_stru     *pst_mib_info;
    mac_channel_stru               *pst_vap_channel;
    oal_uint32                      ul_ret;
    mac_cfg_mode_param_stru         st_cfg_mode = {0};

    pst_mac_vap      = &(pst_hmac_vap->st_vap_base_info);
    pst_vap_channel  = &(pst_mac_vap->st_channel);
    pst_mib_info     = pst_mac_vap->pst_mib_info;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if ((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_mib_info))
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 设置BSSID */
    mac_vap_set_bssid(pst_mac_vap, pst_bss_dscr->auc_bssid);

    /* 更新mib库对应的ssid */
    oal_memcopy(pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID, pst_bss_dscr->ac_ssid, WLAN_SSID_MAX_LEN);
    pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID[WLAN_SSID_MAX_LEN - 1] = '\0';

    /* 更新mib库对应的dot11BeaconPeriod、ul_dot11DTIMPeriod值 */
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)(pst_bss_dscr->us_beacon_period);
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod   = (oal_uint32)(pst_bss_dscr->uc_dtim_period);

#ifdef _PRE_WLAN_FEATURE_11D
    /* 更新sta期望加入的国家字符串 */
    pst_hmac_vap->ac_desired_country[0] = pst_bss_dscr->ac_country[0];
    pst_hmac_vap->ac_desired_country[1] = pst_bss_dscr->ac_country[1];
    pst_hmac_vap->ac_desired_country[2] = pst_bss_dscr->ac_country[2];
#endif

    /* 更新mib库对应的ul_dot11CurrentChannel值*/
    ul_ret = mac_vap_set_current_channel(pst_mac_vap, pst_bss_dscr->st_channel.en_band, pst_bss_dscr->st_channel.uc_chan_number);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* 根据要关联的AP，更新mib库中对应的HT/VHT能力 */
    pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = pst_bss_dscr->en_ht_capable;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented            = pst_bss_dscr->en_vht_capable;

    /* 更新LDPC、STBC能力，取最小能力 */
    pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented  = (pst_bss_dscr->en_ht_ldpc && pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated);
    pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented      = (pst_bss_dscr->en_ht_stbc && pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated );

    /* 关联2G AP，且2ght40禁止位为1时，不学习AP的HT 40能力 */
    if (!(WLAN_BAND_2G == pst_mac_vap->st_channel.en_band && pst_mac_vap->st_cap_flag.bit_disable_2ght40))
    {
        if (WLAN_BW_CAP_20M == pst_bss_dscr->en_bw_cap)
        {
            mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_FALSE);
        }
        else
        {
            mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_TRUE);
        }
    }

    /* 根据要加入BSS的协议模式更新速率集 */
    ul_ret = hmac_sta_get_user_protocol(pst_bss_dscr, &(st_cfg_mode.en_protocol));
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    pst_mac_vap->en_protocol = st_cfg_mode.en_protocol;

    st_cfg_mode.en_band        = pst_bss_dscr->st_channel.en_band;
    st_cfg_mode.en_bandwidth   = hmac_sta_get_band(pst_mac_device->en_bandwidth_cap, pst_bss_dscr->en_channel_bandwidth);

    ul_ret = hmac_config_sta_update_rates(pst_mac_vap, &st_cfg_mode, pst_bss_dscr);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

#if defined (_PRE_WLAN_FEATURE_WPA) || defined (_PRE_WLAN_FEATURE_WPA2)
    /* 更新mib库对应的加密相关值 */
    ul_ret = hmac_update_current_join_req_parms_11i(pst_mac_vap, &pst_bss_dscr->st_bss_sec_info);
    if(ul_ret != OAL_SUCC)
    {
        return ul_ret;
    }
#endif

    /* STA首先以20MHz运行，如果要切换到40 or 80MHz运行，需要满足一下条件: */
    /* (1) 用户支持40 or 80MHz运行 */
    /* (2) AP支持40 or 80MHz运行(HT Supported Channel Width Set = 1 && VHT Supported Channel Width Set = 0) */
    /* (3) AP在40 or 80MHz运行(SCO = SCA or SCB && VHT Channel Width = 1) */

    /* 更新协议相关信息，包括WMM P2P 11I 20/40M等 */
    if (WLAN_MIB_DESIRED_BSSTYPE_INFRA  == pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType)
    {
        pst_mac_vap->uc_wmm_cap   = pst_bss_dscr->uc_wmm_cap;
        pst_mac_vap->uc_uapsd_cap = pst_bss_dscr->uc_uapsd_cap;
    }

    pst_vap_channel->en_bandwidth   = st_cfg_mode.en_bandwidth;

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    pst_vap_channel->en_bandwidth   = WLAN_BAND_WIDTH_20M;
    hmac_update_join_req_params_2040(pst_mac_vap, pst_bss_dscr);
#endif

    /* 入网优化，不同频段下的能力不一样 */
    if (WLAN_BAND_2G == pst_vap_channel->en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_TRUE);
    }

    /* 配置相关参数到dmac */
    ul_ret = hmac_roam_connect_set_join_reg(pst_mac_vap);
    if(ul_ret != OAL_SUCC)
    {
        return ul_ret;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_connect_notify_wpas
 功能描述  : 将关联成功消息通知wpa_supplicant，以便开始4-way握手流程
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
OAL_STATIC oal_uint32  hmac_roam_connect_notify_wpas(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_mac_hdr, oal_uint16 us_msg_len)
{
    hmac_roam_rsp_stru               st_roam_rsp;
    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;

    oal_memset(&st_roam_rsp, 0, OAL_SIZEOF(hmac_asoc_rsp_stru));

    /* 记录关联响应帧的部分内容，用于上报给内核 */
    st_roam_rsp.ul_asoc_rsp_ie_len     = us_msg_len - OAL_ASSOC_RSP_IE_OFFSET;
    st_roam_rsp.puc_asoc_rsp_ie_buff   = puc_mac_hdr + OAL_ASSOC_RSP_IE_OFFSET;
    /* 获取AP的mac地址 */
    mac_get_address3(puc_mac_hdr, st_roam_rsp.auc_bssid);

    /* 获取关联请求帧信息 */
    st_roam_rsp.puc_asoc_req_ie_buff = pst_hmac_vap->puc_asoc_req_ie_buff;
    st_roam_rsp.ul_asoc_req_ie_len   = pst_hmac_vap->ul_asoc_req_ie_len;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_roam_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_handle_asoc_rsp_sta::FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_ROAM_COMP_STA,
                       OAL_SIZEOF(hmac_asoc_rsp_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);
    oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem), (oal_uint8 *)&st_roam_rsp, OAL_SIZEOF(hmac_roam_rsp_stru));

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_11R
/*****************************************************************************
 函 数 名  : hmac_roam_connect_notify_wpas
 功能描述  : 将关联成功消息通知wpa_supplicant，以便开始4-way握手流程
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
OAL_STATIC oal_uint32  hmac_roam_ft_notify_wpas(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_mac_hdr, oal_uint16 us_msg_len)
{
    hmac_roam_ft_stru               *pst_ft_event;
    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;
    oal_uint16                       us_ie_offset;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_roam_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_ft_notify_wpas::FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_FT_EVENT_STA,
                       OAL_SIZEOF(hmac_roam_ft_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    pst_ft_event = (hmac_roam_ft_stru *)pst_event->auc_event_data;

    mac_get_address3(puc_mac_hdr, pst_ft_event->auc_bssid);

    if (WLAN_FC0_SUBTYPE_AUTH == mac_get_frame_sub_type(puc_mac_hdr))
    {
        us_ie_offset = OAL_AUTH_IE_OFFSET;
    }
    else
    {
        us_ie_offset = OAL_FT_ACTION_IE_OFFSET;
    }

    pst_ft_event->puc_ft_ie_buff = puc_mac_hdr + us_ie_offset;
    pst_ft_event->us_ft_ie_len   = us_msg_len - us_ie_offset;

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_send_ft_req
 功能描述  : 发送FT REQUEST帧
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
OAL_STATIC oal_uint32 hmac_roam_send_ft_req(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32              ul_ret;
    hmac_vap_stru          *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;
    hmac_user_stru         *pst_hmac_user = pst_roam_info->pst_hmac_user;
    oal_netbuf_stru        *pst_ft_frame;
    oal_uint8              *puc_ft_buff;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint8              *puc_my_mac_addr;
    oal_uint8              *puc_current_bssid;
    oal_uint16              us_ft_len;
    oal_uint16              us_app_ie_len;
    oal_uint8               uc_vap_id;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_send_ft_req::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    /* 漫游开关没有开时，失败 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_ft_req::roam disabled.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_ft_req::main state[%d] error.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非INIT状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_INIT)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_ft_req::connect state[%d] error.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_ft_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_ft_frame)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_ft_req::OAL_MEM_NETBUF_ALLOC fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    puc_ft_buff = (oal_uint8 *)OAL_NETBUF_HEADER(pst_ft_frame);
    OAL_MEMZERO(oal_netbuf_cb(pst_ft_frame), 48);
    OAL_MEMZERO(puc_ft_buff, MAC_80211_FRAME_LEN);

    puc_my_mac_addr     = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;
    puc_current_bssid   = pst_hmac_vap->st_vap_base_info.auc_bssid;
    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_ft_buff, WLAN_FC0_SUBTYPE_ACTION);
    /*  Set DA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_ft_buff)->auc_address1, puc_current_bssid);
    /*  Set SA  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_ft_buff)->auc_address2, puc_my_mac_addr);
    /*  Set SSID  */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_ft_buff)->auc_address3, puc_current_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                  FT Request Frame - Frame Body                          */
    /* --------------------------------------------------------------------- */
    /* | Category | Action | STA Addr |Target AP Addr | FT Req frame body  |*/
    /* --------------------------------------------------------------------- */
    /* |     1    |   1    |     6    |       6       |       varibal      | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_ft_buff  += MAC_80211_FRAME_LEN;
    us_ft_len     = MAC_80211_FRAME_LEN;

    puc_ft_buff[0]   = MAC_ACTION_CATEGORY_FAST_BSS_TRANSITION;
    puc_ft_buff[1]   = MAC_FT_ACTION_REQUEST;
    puc_ft_buff  += 2;
    us_ft_len    += 2;

    oal_set_mac_addr(puc_ft_buff, puc_my_mac_addr);
    puc_ft_buff  += OAL_MAC_ADDR_LEN;
    us_ft_len    += OAL_MAC_ADDR_LEN;

    oal_set_mac_addr(puc_ft_buff, pst_roam_info->st_connect.auc_bssid);
    puc_ft_buff  += OAL_MAC_ADDR_LEN;
    us_ft_len    += OAL_MAC_ADDR_LEN;

    mac_add_app_ie((oal_void *)&pst_hmac_vap->st_vap_base_info, puc_ft_buff, &us_app_ie_len, OAL_APP_FT_IE);
    us_ft_len      += us_app_ie_len;
    puc_ft_buff    += us_app_ie_len;

    oal_netbuf_put(pst_ft_frame, us_ft_len);

    /* 为填写发送描述符准备参数 */
    pst_tx_ctl                   = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_ft_frame);
    pst_tx_ctl->us_mpdu_len      = us_ft_len;
    pst_tx_ctl->us_tx_user_idx   = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_tx_ctl->uc_netbuf_num    = 1;

    /* 抛事件让dmac将该帧发送 */
    ul_ret = hmac_tx_mgmt_send_event(&pst_hmac_vap->st_vap_base_info, pst_ft_frame, us_ft_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_ft_frame);
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_ft_req::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_FT_COMP);

    /* 启动认证超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_AUTH_TIME_MAX);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_process_ft_rsp
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
OAL_STATIC oal_uint32 hmac_roam_process_ft_rsp(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32                   ul_ret;
    hmac_vap_stru               *pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    dmac_wlan_crx_event_stru    *pst_crx_event;
    hmac_rx_ctl_stru            *pst_rx_ctrl;
    oal_uint8                   *puc_mac_hdr;
    oal_uint8                   *puc_ft_frame_body;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_process_ft_rsp::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_ft_rsp::roam disabled.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_ft_rsp::main state[%d] error.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非WAIT_AUTH_COMP状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_WAIT_FT_COMP)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_ft_rsp::connect state[%d] error.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }


    pst_crx_event  = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf);
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;


    /* 只处理action帧 */
    if (WLAN_FC0_SUBTYPE_ACTION != mac_get_frame_sub_type(puc_mac_hdr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_process_ft_rsp::not action frame.}");
        return OAL_SUCC;
    }

    puc_ft_frame_body = puc_mac_hdr + MAC_80211_FRAME_LEN;

    if ((MAC_ACTION_CATEGORY_FAST_BSS_TRANSITION != puc_ft_frame_body[0]) ||
        (MAC_FT_ACTION_RESPONSE != puc_ft_frame_body[1]))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ROAM, "{hmac_roam_process_ft_rsp::unexpected category[%d] ft_action_type[%d].}",
                       puc_ft_frame_body[0], puc_ft_frame_body[1]);
        return OAL_SUCC;
    }
    /* 上报FT成功消息给APP，以便APP下发新的FT_IE用于发送reassociation */
    ul_ret = hmac_roam_ft_notify_wpas(pst_hmac_vap, puc_mac_hdr, pst_rx_ctrl->st_rx_info.us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_ft_rsp::hmac_roam_ft_notify_wpas failed[%d].}", ul_ret);
        return ul_ret;
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_ASSOC_COMP);

    /* 启动关联超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_ASSOC_TIME_MAX);
    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_11R
/*****************************************************************************
 函 数 名  : hmac_roam_start_join
 功能描述  : 启动定时器用来接收tbtt中断
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
OAL_STATIC oal_uint32 hmac_roam_start_join(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32              ul_ret;
    hmac_vap_stru          *pst_hmac_vap;
    mac_bss_dscr_stru      *pst_bss_dscr;
    oal_app_ie_stru         st_app_ie;
    oal_uint8               uc_ie_len = 0;

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_start_join::pst_hmac_vap null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，失败 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_start_join::ROAM DISABLED.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (ROAM_MAIN_STATE_CONNECTING != pst_roam_info->en_main_state)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_start_join::ROAM main status[%d] ERROR.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非INIT状态，失败 */
    if (ROAM_CONNECT_STATE_INIT != pst_roam_info->st_connect.en_state)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{hmac_roam_start_join::ROAM connect status[%d] ERROR.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_bss_dscr = (mac_bss_dscr_stru *)p_param;

    /* 配置join参数 */
    ul_ret = hmac_roam_connect_set_join_params(pst_hmac_vap, pst_bss_dscr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{hmac_roam_start_join::hmac_roam_connect_set_join_params fail[%d].}", ul_ret);
        return ul_ret;
    }

#if defined(_PRE_WLAN_FEATURE_WPA)
    if (DMAC_WPA_802_11I == pst_hmac_vap->uc_80211i_mode)
    {
        /* 设置 WPA Capability IE */
        mac_set_wpa_ie((oal_void *)&pst_hmac_vap->st_vap_base_info, st_app_ie.auc_ie, &uc_ie_len);
    }
#endif /* defined (_PRE_WLAN_FEATURE_WPA) */

#if defined(_PRE_WLAN_FEATURE_WPA2)
    if (DMAC_RSNA_802_11I == pst_hmac_vap->uc_80211i_mode)
    {
        /* 设置 RSN Capability IE */
        mac_set_rsn_ie((oal_void *)&pst_hmac_vap->st_vap_base_info, st_app_ie.auc_ie, &uc_ie_len);
    }
#endif /* defiend (_PRE_WLAN_FEATURE_WPA2) */

    if (0 != uc_ie_len)
    {
        st_app_ie.en_app_ie_type = OAL_APP_REASSOC_REQ_IE;
        st_app_ie.ul_ie_len      = uc_ie_len;
        hmac_config_set_app_ie_to_vap(&pst_hmac_vap->st_vap_base_info, &st_app_ie, OAL_APP_REASSOC_REQ_IE);
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_JOIN);

    /* 启动超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_JOIN_TIME_MAX);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_process_beacon
 功能描述  : 接收beacon帧以完成join，帧体释放在外面完成。
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
OAL_STATIC oal_uint32 hmac_roam_process_beacon(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru                       *pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    dmac_wlan_crx_event_stru            *pst_crx_event;
    hmac_rx_ctl_stru                    *pst_rx_ctrl;
    oal_uint8                           *puc_tim_ie;
    oal_uint8                           *puc_mac_hdr;
    oal_uint8                            auc_bssid[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint16                           us_rx_len;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_roam_process_beacon::pst_hmac_vap null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非WAIT_JOIN状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_WAIT_JOIN)
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_crx_event  = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf);
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
    us_rx_len      =  pst_rx_ctrl->st_rx_info.us_frame_len;

    /* beacon帧校验 */
    if (WLAN_FC0_SUBTYPE_BEACON != mac_get_frame_sub_type(puc_mac_hdr))
    {
        return OAL_SUCC;
    }

    /* bssid校验 */
    mac_get_bssid(puc_mac_hdr, auc_bssid);
    if (0 != oal_memcmp(auc_bssid, pst_hmac_vap->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN))
    {
        return OAL_SUCC;
    }
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                    "{hmac_roam_process_beacon:: [%02X:XX:XX:%02X:%02X:%02X]}",
                    auc_bssid[0],auc_bssid[3],auc_bssid[4],auc_bssid[5]);

    /* 从tim IE中提取 DTIM count值,写入到MAC H/W REG中 */
    //puc_tim_ie = mac_get_tim_ie(puc_mac_hdr, us_rx_len, MAC_TAG_PARAM_OFFSET);
    puc_tim_ie = mac_find_ie(MAC_EID_TIM, puc_mac_hdr + MAC_TAG_PARAM_OFFSET, us_rx_len - MAC_TAG_PARAM_OFFSET);
    if ((OAL_PTR_NULL == puc_tim_ie) || (puc_tim_ie[1] < MAC_MIN_TIM_LEN))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_beacon::Do not find Tim ie.}");
        return OAL_SUCC;
    }
    /* 更新beacon帧中的DTIM count值到STA本地mib库中 */
    pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = puc_tim_ie[3];

    hmac_roam_connect_set_dtim_param(&pst_hmac_vap->st_vap_base_info, (oal_uint32)puc_tim_ie[2], (oal_uint32)puc_tim_ie[3], BIT0);
    OAM_INFO_LOG0(0, OAM_SF_SCAN, "{hmac_roam_process_beacon OK.}");

    hmac_roam_connect_rx_tbtt(pst_hmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_send_auth_seq1
 功能描述  : 发送auth_seq1，并且启动auth超时定时器
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
OAL_STATIC oal_uint32 hmac_roam_send_auth_seq1(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32              ul_ret;
    hmac_vap_stru          *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;
    hmac_user_stru         *pst_hmac_user = pst_roam_info->pst_hmac_user;
    oal_netbuf_stru        *pst_auth_frame;
    oal_uint8              *puc_auth_buff;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint8              *puc_my_mac_addr;
    oal_uint16              us_auth_len;
#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint16              us_app_ie_len;
#endif //_PRE_WLAN_FEATURE_11R
    oal_uint8               uc_vap_id;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    /* 漫游开关没有开时，失败 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::roam disabled.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::main state[%d] error.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非WAIT_JOIN状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_JOIN_COMP)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::connect state[%d] error.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_auth_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_auth_frame)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::OAL_MEM_NETBUF_ALLOC fail.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    /* 更新用户mac */
    oal_set_mac_addr(pst_hmac_user->st_user_base_info.auc_user_mac_addr, pst_roam_info->st_connect.auc_bssid);

    /*ul_ret = hmac_user_add(&pst_hmac_vap->st_vap_base_info, pst_hmac_vap->st_vap_base_info.auc_bssid, &us_user_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                         "{hmac_roam_send_auth_seq1::hmac_user_add failed[%d].}", ul_ret);
        return OAL_FAIL;
    }*/

    puc_auth_buff = (oal_uint8 *)OAL_NETBUF_HEADER(pst_auth_frame);
    OAL_MEMZERO(oal_netbuf_cb(pst_auth_frame), 48);
    OAL_MEMZERO(puc_auth_buff, MAC_80211_FRAME_LEN);

    puc_my_mac_addr = pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;

    /* 设置 Frame Control field */
    mac_hdr_set_frame_control(puc_auth_buff, WLAN_FC0_SUBTYPE_AUTH);
    /* 设置 DA address1: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_auth_buff + WLAN_HDR_ADDR1_OFFSET, pst_roam_info->st_connect.auc_bssid);
    /* 设置 SA address2: dot11MACAddress */
    oal_set_mac_addr(puc_auth_buff + WLAN_HDR_ADDR2_OFFSET, puc_my_mac_addr);
    /* 设置 DA address3: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_auth_buff + WLAN_HDR_ADDR3_OFFSET, pst_roam_info->st_connect.auc_bssid);
    us_auth_len        = MAC_80211_FRAME_LEN;
    puc_auth_buff     += MAC_80211_FRAME_LEN;

    /* Open System */
    puc_auth_buff[0]     = 0x00;
    puc_auth_buff[1]     = 0x00;

    /* 设置 Authentication Transaction Sequence Number 为 1 */
    puc_auth_buff[2]     = 0x01;
    puc_auth_buff[3]     = 0x00;

    /* 设置 Status Code 为0. 这个包的这个字段没用 . */
    puc_auth_buff[4]     = 0x00;
    puc_auth_buff[5]     = 0x00;
    us_auth_len         += MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN + MAC_STATUS_CODE_LEN;

#ifdef _PRE_WLAN_FEATURE_11R
    if (OAL_TRUE == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
    {
        /* FT System */
        puc_auth_buff[0]     = 0x02;
        puc_auth_buff[1]     = 0x00;
        puc_auth_buff       += MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN + MAC_STATUS_CODE_LEN;

        mac_add_app_ie((oal_void *)&pst_hmac_vap->st_vap_base_info, puc_auth_buff, &us_app_ie_len, OAL_APP_FT_IE);
        us_auth_len      += us_app_ie_len;
        puc_auth_buff    += us_app_ie_len;
    }
#endif //_PRE_WLAN_FEATURE_11R

    oal_netbuf_put(pst_auth_frame, us_auth_len);

    /* 为填写发送描述符准备参数 */
    pst_tx_ctl                   = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_auth_frame);
    pst_tx_ctl->us_mpdu_len      = us_auth_len;
    pst_tx_ctl->us_tx_user_idx   = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_tx_ctl->uc_netbuf_num    = 1;

    /* 抛事件让dmac将该帧发送 */
    ul_ret = hmac_tx_mgmt_send_event(&pst_hmac_vap->st_vap_base_info, pst_auth_frame, us_auth_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_auth_frame);
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_auth_seq1::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_AUTH_COMP);

    /* 启动认证超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_AUTH_TIME_MAX);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_send_assoc_req
 功能描述  : 发送assoc req，并且启动assoc超时定时器
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
OAL_STATIC oal_uint32 hmac_roam_send_reassoc_req(hmac_roam_info_stru *pst_roam_info)
{
    oal_uint32              ul_ret;
    hmac_vap_stru          *pst_hmac_vap  = pst_roam_info->pst_hmac_vap;
    hmac_user_stru         *pst_hmac_user = pst_roam_info->pst_hmac_user;
    mac_vap_stru           *pst_mac_vap;
    oal_netbuf_stru        *pst_assoc_req_frame;
    oal_uint8              *puc_assoc_buff;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint8              *puc_my_mac_addr;
    oal_uint16              us_assoc_len;
    oal_uint8               uc_ie_len = 0;
    oal_uint16              us_app_ie_len = 0;
    en_app_ie_type_uint8    en_app_ie_type;
#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_txbf_cap_stru      *pst_txbf_cap;
#endif
    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    if (OAL_PTR_NULL != pst_hmac_vap->puc_asoc_req_ie_buff)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::puc_asoc_req_ie_buff NOT null.}");
        return OAL_FAIL;
    }

    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    pst_assoc_req_frame = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_assoc_req_frame)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::OAL_MEM_NETBUF_ALLOC fail.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    puc_assoc_buff = (oal_uint8 *)OAL_NETBUF_HEADER(pst_assoc_req_frame);

    OAL_MEMZERO(oal_netbuf_cb(pst_assoc_req_frame), 48);
    OAL_MEMZERO(puc_assoc_buff, MAC_80211_FRAME_LEN);

    puc_my_mac_addr = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;

    /* 设置 Frame Control field */
    mac_hdr_set_frame_control(puc_assoc_buff, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_REASSOC_REQ);

    /* 设置 DA address1: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_assoc_buff + WLAN_HDR_ADDR1_OFFSET, pst_roam_info->st_connect.auc_bssid);
    /* 设置 SA address2: dot11MACAddress */
    oal_set_mac_addr(puc_assoc_buff + WLAN_HDR_ADDR2_OFFSET, puc_my_mac_addr);
    /* 设置 DA address3: AP MAC地址 (BSSID)*/
    oal_set_mac_addr(puc_assoc_buff + WLAN_HDR_ADDR3_OFFSET, pst_roam_info->st_connect.auc_bssid);
    us_assoc_len       = MAC_80211_FRAME_LEN;
    puc_assoc_buff    += MAC_80211_FRAME_LEN;

    /*************************************************************************/
    /*              Association Request Frame - Frame Body                   */
    /* --------------------------------------------------------------------- */
    /* | Capability Information | Listen Interval | SSID | Supported Rates | */
    /* --------------------------------------------------------------------- */
    /* |2                       |2                |2-34  |3-10             | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* |Externed Surpported rates| Power Capability | Supported Channels   | */
    /* --------------------------------------------------------------------- */
    /* |3-257                    |4                 |4-256                 | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | RSN   | QoS Capability | HT Capabilities | Extended Capabilities  | */
    /* --------------------------------------------------------------------- */
    /* |36-256 |3               |28               |3-8                     | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | WPS   | P2P |                                                       */
    /* --------------------------------------------------------------------- */
    /* |7-257  |X    |                                                       */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    /* 设置 capability information field */
    mac_set_cap_info_sta((oal_void *)pst_mac_vap, puc_assoc_buff);
    us_assoc_len      += MAC_CAP_INFO_LEN;
    puc_assoc_buff    += MAC_CAP_INFO_LEN;

    /* 设置 Listen Interval IE */
    mac_set_listen_interval_ie((oal_uint8 *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 CURRENT AP ADDR */
    oal_set_mac_addr(puc_assoc_buff, pst_roam_info->pst_old_bss->auc_bssid);
    us_assoc_len      += OAL_MAC_ADDR_LEN;
    puc_assoc_buff    += OAL_MAC_ADDR_LEN;

    /* 设置 SSID IE */
    mac_set_ssid_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len, WLAN_FC0_SUBTYPE_ASSOC_REQ);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 Supported Rates IE */
    mac_set_supported_rates_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 Extended Supported Rates IE */
    mac_set_exsup_rates_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 Power Capability IE */
    mac_set_power_cap_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 Supported channel IE */
    mac_set_supported_channel_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 填充WMM element */
    mac_set_wmm_ie_sta((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 HT Capability IE  */
    mac_set_ht_capabilities_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
#ifdef _PRE_WLAN_FEATURE_TXBF
    if ((OAL_TRUE == pst_hmac_user->st_hmac_cap_info.bit_11ntxbf)
    && (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_11ntxbf)
    && (0 != uc_ie_len))
    {
        puc_assoc_buff += MAC_11N_TXBF_CAP_OFFSET;

        pst_txbf_cap  = (mac_txbf_cap_stru *)puc_assoc_buff;
        pst_txbf_cap->bit_rx_stagg_sounding             = OAL_TRUE;
        pst_txbf_cap->bit_explicit_compr_bf_fdbk        = 1;
        pst_txbf_cap->bit_compr_steering_num_bf_antssup = 1;
        puc_assoc_buff -= MAC_11N_TXBF_CAP_OFFSET;
    }
#endif
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 Extended Capability IE */
    mac_set_ext_capabilities_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

    /* 设置 VHT Capability IE */
    mac_set_vht_capabilities_ie((oal_void *) pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11AC2G
    mac_set_vendor_hisi_ie(pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie(pst_mac_vap, puc_assoc_buff, &uc_ie_len);
    us_assoc_len      += uc_ie_len;
    puc_assoc_buff    += uc_ie_len;
#endif

    en_app_ie_type = OAL_APP_REASSOC_REQ_IE;
#ifdef _PRE_WLAN_FEATURE_11R
    if (OAL_TRUE == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
    {
        en_app_ie_type = OAL_APP_FT_IE;
    }
#endif //_PRE_WLAN_FEATURE_11R
    /* 填充P2P/WPS IE 信息 */
    mac_add_app_ie((oal_void *)pst_mac_vap, puc_assoc_buff, &us_app_ie_len, en_app_ie_type);
    us_assoc_len      += us_app_ie_len;
    puc_assoc_buff    += us_app_ie_len;

    oal_netbuf_put(pst_assoc_req_frame, us_assoc_len);

    /* 帧长异常 */
    if (us_assoc_len <= OAL_ASSOC_REQ_IE_OFFSET)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::unexpected assoc len[%d].}", us_assoc_len);
        oal_netbuf_free(pst_assoc_req_frame);
        return OAL_FAIL;
    }

    if (OAL_PTR_NULL != pst_hmac_vap->puc_asoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_hmac_vap->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;
    }

    /* 记录关联请求帧的部分内容，用于上报给内核 */
    pst_hmac_vap->puc_asoc_req_ie_buff = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(us_assoc_len - OAL_ASSOC_REQ_IE_OFFSET - 6), OAL_TRUE);
    if (OAL_PTR_NULL == pst_hmac_vap->puc_asoc_req_ie_buff)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::OAL_MEM_ALLOC len[%d] fail.}", us_assoc_len);
        oal_netbuf_free(pst_assoc_req_frame);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    /* 记录关联请求帧的部分内容，用于上报给内核 */
    pst_hmac_vap->ul_asoc_req_ie_len = us_assoc_len - OAL_ASSOC_REQ_IE_OFFSET - 6;
    oal_memcopy(pst_hmac_vap->puc_asoc_req_ie_buff, OAL_NETBUF_HEADER(pst_assoc_req_frame) + OAL_ASSOC_REQ_IE_OFFSET + 6, pst_hmac_vap->ul_asoc_req_ie_len);

    /* 为填写发送描述符准备参数 */
    pst_tx_ctl                   = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_assoc_req_frame);
    pst_tx_ctl->us_mpdu_len      = us_assoc_len;
    pst_tx_ctl->us_tx_user_idx   = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_tx_ctl->uc_netbuf_num    = 1;

    /* 抛事件让dmac将该帧发送 */
    ul_ret = hmac_tx_mgmt_send_event(&pst_hmac_vap->st_vap_base_info, pst_assoc_req_frame, us_assoc_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_assoc_req_frame);
        OAL_MEM_FREE(pst_hmac_vap->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{hmac_roam_send_assoc_req::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_process_auth_seq2
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
OAL_STATIC oal_uint32 hmac_roam_process_auth_seq2(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32                   ul_ret;
    hmac_vap_stru               *pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    dmac_wlan_crx_event_stru    *pst_crx_event;
    hmac_rx_ctl_stru            *pst_rx_ctrl;
    oal_uint8                   *puc_mac_hdr;
    oal_uint16                  us_auth_state  = MAC_UNSPEC_FAIL;
    oal_uint8                   uc_frame_sub_type;
    oal_uint16                  us_auth_seq_num;
    oal_uint8                   *puc_sa = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_process_auth_seq2::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_auth_seq2::roam disabled.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_auth_seq2::main state[%d] error.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非WAIT_JOIN状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_WAIT_AUTH_COMP)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_auth_seq2::connect state[%d] error.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* TBD mac地址校验 */
    pst_crx_event  = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf);
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    uc_frame_sub_type = mac_get_frame_sub_type(puc_mac_hdr);
    us_auth_seq_num = mac_get_auth_seq_num(puc_mac_hdr);
    us_auth_state = mac_get_auth_status(puc_mac_hdr);

    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_auth_seq2::frame_sub_type = 0x%x, seq_num = 0x%x, auth_alg = 0x%x, auth_state = %d}",
                       uc_frame_sub_type,us_auth_seq_num,mac_get_auth_alg(puc_mac_hdr),us_auth_state);

    if (WLAN_FC0_SUBTYPE_AUTH == uc_frame_sub_type)
    {
        if (WLAN_AUTH_TRASACTION_NUM_TWO == us_auth_seq_num)
        {
            if(MAC_SUCCESSFUL_STATUSCODE != us_auth_state)
            {
                ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX, (oal_void *)OAL_PTR_NULL);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_auth_seq2::fsm_action FAIL[%d]!}", ul_ret);
                }
                return OAL_FAIL;
            }
        }
    }
    else if(WLAN_FC0_SUBTYPE_DEAUTH     == uc_frame_sub_type ||
            WLAN_FC0_SUBTYPE_DISASSOC   == uc_frame_sub_type)
    {
        /* 增加接收到去认证帧或者去关联帧时的维测信息 */
        mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);
        OAM_WARNING_LOG4(0, OAM_SF_ROAM,
                         "{hmac_roam_process_auth_seq2::Because of error_code[%d], received deauth or disassoc frame frome source addr, sa [%02X:XX:XX:XX:%02X:%02X]}",
                         *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)), puc_sa[0], puc_sa[4], puc_sa[5]);

        ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX, (oal_void *)OAL_PTR_NULL);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_auth_seq2::fsm_action FAIL[%d]!}", ul_ret);
        }
        return OAL_FAIL;
    }

    /* auth_seq2帧校验，错误帧不处理，在超时中统一处理 */
    if ((WLAN_FC0_SUBTYPE_AUTH != uc_frame_sub_type) ||
        (WLAN_AUTH_TRASACTION_NUM_TWO != us_auth_seq_num))
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_11R
    if (WLAN_WITP_AUTH_FT == mac_get_auth_alg(puc_mac_hdr))
    {
        /* 上报FT成功消息给APP，以便APP下发新的FT_IE用于发送reassociation */
        ul_ret = hmac_roam_ft_notify_wpas(pst_hmac_vap, puc_mac_hdr, pst_rx_ctrl->st_rx_info.us_frame_len);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                           "{hmac_roam_process_auth_seq2::hmac_roam_ft_notify_wpas failed[%d].}", ul_ret);
            return ul_ret;
        }

        hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_ASSOC_COMP);

        /* 启动关联超时定时器 */
        hmac_roam_connect_start_timer(pst_roam_info, ROAM_ASSOC_TIME_MAX);
        return OAL_SUCC;
    }
#endif //_PRE_WLAN_FEATURE_11R

    if (WLAN_WITP_AUTH_OPEN_SYSTEM != mac_get_auth_alg(puc_mac_hdr))
    {
        return OAL_SUCC;
    }

    /* 发送关联请求 */
    ul_ret = hmac_roam_send_reassoc_req(pst_roam_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_auth_seq2::hmac_roam_send_assoc_req failed[%d].}", ul_ret);
        return ul_ret;
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_ASSOC_COMP);

    /* 启动关联超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_ASSOC_TIME_MAX);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_process_assoc_rsp
 功能描述  : 根据关联响应中的ie，更新本地用户能力及vap能力
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
OAL_STATIC oal_uint32 hmac_roam_process_assoc_rsp(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    oal_uint32                       ul_ret;
    hmac_vap_stru                   *pst_hmac_vap;
    hmac_user_stru                  *pst_hmac_user;
    dmac_wlan_crx_event_stru        *pst_crx_event;
    hmac_rx_ctl_stru                *pst_rx_ctrl;
    oal_uint8                       *puc_mac_hdr;
    oal_uint8                       *puc_payload;
    oal_uint8                       *puc_tmp_ie;
    mac_status_code_enum_uint16      en_asoc_status;
    wlan_bw_cap_enum_uint8           en_bwcap;
    oal_uint16                       us_msg_len;
    oal_uint16                       us_aid;
    oal_uint16                       us_ie_offset;
    oal_uint8                        auc_bss_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8                        uc_frame_sub_type;
    oal_uint8                       *puc_sa = OAL_PTR_NULL;

    pst_hmac_vap  = pst_roam_info->pst_hmac_vap;
    pst_hmac_user = pst_roam_info->pst_hmac_user;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态/CONNECT状态机为非WAIT_JOIN状态，失败 */
    if ((pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING) ||
        (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_WAIT_ASSOC_COMP))
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_crx_event  = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl    = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_crx_event->pst_netbuf);
    puc_mac_hdr    = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;
    puc_payload    = puc_mac_hdr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;
    us_msg_len     = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* mac地址校验 */
    mac_get_address3(puc_mac_hdr, auc_bss_addr);
    if (oal_compare_mac_addr(pst_hmac_user->st_user_base_info.auc_user_mac_addr, auc_bss_addr))
    {
        return OAL_ERR_CODE_ROAM_INVALID_USER;
    }

    /* assoc帧校验，错误帧处理 */
    uc_frame_sub_type = mac_get_frame_sub_type(puc_mac_hdr);
    en_asoc_status = mac_get_asoc_status(puc_payload);

    OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                    "{hmac_roam_process_assoc_rsp::frame_sub_type = 0x%x, en_asoc_status = 0x%x, us_frame_len = %d}", uc_frame_sub_type, en_asoc_status, pst_rx_ctrl->st_rx_info.us_frame_len);

    if (WLAN_FC0_SUBTYPE_ASSOC_RSP      == uc_frame_sub_type ||
        WLAN_FC0_SUBTYPE_REASSOC_RSP    == uc_frame_sub_type)
    {
        if(MAC_SUCCESSFUL_STATUSCODE != en_asoc_status)
        {
            ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX, (oal_void *)OAL_PTR_NULL);
            if (OAL_SUCC != ul_ret)
            {
                /* TBD 加入黑名单 */
                OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_assoc_rsp::fsm_action FAIL[%d]!}", ul_ret);
            }
            return OAL_FAIL;
        }
    }
    else if(WLAN_FC0_SUBTYPE_DEAUTH     == uc_frame_sub_type ||
            WLAN_FC0_SUBTYPE_DISASSOC   == uc_frame_sub_type)
    {
        /* 增加接收到去认证帧或者去关联帧时的维测信息 */
        mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);
        OAM_WARNING_LOG4(0, OAM_SF_ROAM,
                         "{hmac_roam_process_assoc_rsp::Because of error_code[%d], received deauth or disassoc frame frome source addr, sa [%02X:XX:XX:XX:%02X:%02X]}",
                         *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)), puc_sa[0], puc_sa[4], puc_sa[5]);

        ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_MGMT_FAIL_RX, (oal_void *)OAL_PTR_NULL);
        if (OAL_SUCC != ul_ret)
        {
            /* TBD 加入黑名单 */
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_process_assoc_rsp::fsm_action FAIL[%d]!}", ul_ret);
        }
        return OAL_FAIL;
    }
    else
    {
        /* 其他类型的帧不处理，只增加维测，确认漫游过程中的管理帧 */
        return OAL_SUCC;
    }

    /* 关联响应帧长度校验 */
    if (pst_rx_ctrl->st_rx_info.us_frame_len <= OAL_ASSOC_RSP_IE_OFFSET)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                               "{hmac_roam_process_assoc_rsp::rsp ie length error, us_frame_len[%d].}", pst_rx_ctrl->st_rx_info.us_frame_len);
        return OAL_ERR_CODE_ROAM_FRAMER_LEN;
    }

    /* sta更新关联ID */
    us_aid = mac_get_asoc_id(puc_payload);
    mac_vap_set_aid(&pst_hmac_vap->st_vap_base_info, us_aid);
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    /* sta计算自身的partial aid，保存到vap结构中，并写入到mac寄存器 */
    hmac_sta_set_txopps_partial_aid(&pst_hmac_vap->st_vap_base_info);
#endif

    /* 更新用户的mac地址，漫游时mac会更新 */
    oal_set_mac_addr(pst_hmac_user->st_user_base_info.auc_user_mac_addr, pst_hmac_vap->st_vap_base_info.auc_bssid);

    ul_ret = hmac_config_user_info_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_config_user_info_syn failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 初始化安全端口过滤参数 */
#if defined (_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    ul_ret = hmac_init_user_security_port(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        return OAL_FAIL;
    }
#endif

    us_ie_offset = MAC_CAP_INFO_LEN + MAC_STATUS_CODE_LEN + MAC_AID_LEN;

#ifdef _PRE_WLAN_FEATURE_PMF
    /* STA模式下的pmf能力来源于WPA_supplicant，只有启动pmf和不启动pmf两种类型 */
    mac_user_set_pmf_active(&pst_hmac_user->st_user_base_info, pst_hmac_vap->st_vap_base_info.en_user_pmf_cap);
#endif /* #ifdef _PRE_WLAN_FEATURE_PMF */

    /* sta更新自身的edca parameters */
    hmac_sta_up_update_edca_params(puc_payload, us_msg_len, us_ie_offset, pst_hmac_vap, uc_frame_sub_type, pst_hmac_user);

    /* 更新关联用户的 QoS protocol table */
    hmac_mgmt_update_assoc_user_qos_table(puc_payload, us_msg_len, us_ie_offset, pst_hmac_user);

    /* 更新关联用户的legacy速率集合 */
    hmac_user_init_rates(pst_hmac_user, &pst_hmac_vap->st_vap_base_info);
    //puc_tmp_ie  = mac_get_supported_rates_ie(puc_payload, us_msg_len, us_ie_offset);
    puc_tmp_ie = mac_find_ie(MAC_EID_RATES, puc_payload + us_ie_offset, (oal_int32)(us_msg_len - us_ie_offset));
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        hmac_add_user_rates(pst_hmac_user, puc_tmp_ie[1], puc_tmp_ie + MAC_IE_HDR_LEN);
    }

    /* 处理扩展速率集信息元素，更新用户信息 */
    //puc_tmp_ie  = mac_get_exsup_rates_ie(puc_payload, us_msg_len, us_ie_offset);
    puc_tmp_ie = mac_find_ie(MAC_EID_XRATES, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        hmac_add_user_rates(pst_hmac_user, puc_tmp_ie[1], puc_tmp_ie + MAC_IE_HDR_LEN);
    }

    /* 更新 HT 参数  */
    mac_user_set_ht_capable(&pst_hmac_user->st_user_base_info, OAL_FALSE);
    //puc_tmp_ie = mac_get_ht_cap_ie((oal_uint8*)puc_payload, us_msg_len, us_ie_offset);
    puc_tmp_ie = mac_find_ie(MAC_EID_HT_CAP, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        hmac_proc_ht_cap_ie(&pst_hmac_vap->st_vap_base_info, &pst_hmac_user->st_user_base_info, puc_tmp_ie);

        /* 处理 Extended Capabilities IE */
        //puc_tmp_ie  = mac_get_ext_cap_ie(puc_payload, us_msg_len, us_ie_offset);
        puc_tmp_ie = mac_find_ie(MAC_EID_EXT_CAPS, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
        if (OAL_PTR_NULL != puc_tmp_ie)
        {
            mac_ie_proc_ext_cap_ie(&pst_hmac_user->st_user_base_info, puc_tmp_ie);
        }
        /* 处理 HT Operation IE */
        //puc_tmp_ie  = mac_get_ht_opern_ie(puc_payload, us_msg_len, us_ie_offset);
        puc_tmp_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
        if (OAL_PTR_NULL != puc_tmp_ie)
        {
            hmac_proc_ht_opern_ie(&pst_hmac_vap->st_vap_base_info, puc_tmp_ie, &pst_hmac_user->st_user_base_info);
            /* 只针对 HT Operation中的Secondary Channel Offset进行处理 */
            hmac_ie_proc_sec_chan_offset_2040(&pst_hmac_vap->st_vap_base_info, puc_tmp_ie[MAC_IE_HDR_LEN + 1] & 0x3);
        }
    }

    /* 处理Overlapping BSS Scan Parameters信息元素，更新用户信息 */
    puc_tmp_ie  = mac_get_obss_scan_ie(puc_payload, us_msg_len, us_ie_offset);
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        hmac_ie_proc_obss_scan_ie(&pst_hmac_vap->st_vap_base_info, puc_tmp_ie);
    }

#ifdef _PRE_WLAN_FEATURE_TXBF
    /* 更新11n txbf能力 */
    puc_tmp_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_EID_11NTXBF, puc_payload + us_ie_offset, (oal_int32)(us_msg_len - us_ie_offset));
    hmac_mgmt_update_11ntxbf_cap(puc_tmp_ie, pst_hmac_user);
#endif

    /* 更新11ac VHT capabilities ie */
    oal_memset(&(pst_hmac_user->st_user_base_info.st_vht_hdl), 0, OAL_SIZEOF(mac_vht_hdl_stru));

    puc_tmp_ie = mac_find_ie(MAC_EID_VHT_CAP, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        hmac_proc_vht_cap_ie(&pst_hmac_vap->st_vap_base_info, pst_hmac_user, puc_tmp_ie);

        /* 更新11ac VHT operation ie */
        //puc_tmp_ie  = mac_get_vht_opern_ie(puc_payload, us_msg_len, us_ie_offset);
        puc_tmp_ie = mac_find_ie(MAC_EID_VHT_OPERN, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
        if (OAL_PTR_NULL != puc_tmp_ie)
        {
            hmac_ie_proc_vht_opern_ie(&pst_hmac_vap->st_vap_base_info, puc_tmp_ie, &(pst_hmac_user->st_user_base_info));
        }
    }

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    if (HISTREAM_SWITCH_ON == g_uc_histream_switch)
    {
        /* 更新histream信息 */
        puc_tmp_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_HISI_HISTREAM_IE, puc_payload + us_ie_offset, us_msg_len - us_ie_offset);
        hmac_mgmt_update_histream_info(&pst_hmac_vap->st_vap_base_info, pst_hmac_user, puc_tmp_ie);
    }
#endif //_PRE_WLAN_FEATURE_HISTREAM

    hmac_chan_reval_bandwidth_sta(&pst_hmac_vap->st_vap_base_info, HMAC_BW_CHANGE);

    /* 更新协议模式 */
    hmac_set_user_protocol_mode(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
    mac_user_set_avail_protocol_mode(&pst_hmac_user->st_user_base_info, g_auc_avail_protocol_mode[pst_hmac_vap->st_vap_base_info.en_protocol][pst_hmac_user->st_user_base_info.en_protocol_mode]);
    mac_user_set_cur_protocol_mode(&pst_hmac_user->st_user_base_info, pst_hmac_user->st_user_base_info.en_avail_protocol_mode);

    OAM_WARNING_LOG3(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                     "{hmac_roam_process_assoc_rsp::mac_vap->en_protocol:%d,mac_user->en_protocol_mode:%d,en_avail_protocol_mode:%d.}",
                     pst_hmac_vap->st_vap_base_info.en_protocol, pst_hmac_user->st_user_base_info.en_protocol_mode,
                     pst_hmac_user->st_user_base_info.en_avail_protocol_mode);

    /* 更新用户和VAP 可支持的11a/b/g 速率交集 */
    hmac_vap_set_user_avail_rates(&(pst_hmac_vap->st_vap_base_info), pst_hmac_user);

    /* 更新用户的带宽能力 */
    mac_vap_get_bandwidth_cap(&pst_hmac_vap->st_vap_base_info, &en_bwcap);
    ul_ret = mac_user_update_bandwidth(&(pst_hmac_user->st_user_base_info), en_bwcap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                        "{hmac_roam_process_assoc_rsp::mac_user_update_bandwidth failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 根据用户支持带宽能力，协商出当前带宽，dmac offload架构下，同步带宽信息到device */
    ul_ret = hmac_config_user_info_syn(&pst_hmac_vap->st_vap_base_info, &pst_hmac_user->st_user_base_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_config_user_info_syn failed[%d].}", ul_ret);
    }

    /* 更新用户的空间流 */
    ul_ret = hmac_user_set_avail_num_space_stream(&pst_hmac_user->st_user_base_info, pst_hmac_vap->st_vap_base_info.en_vap_rx_nss);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::mac_user_set_avail_num_space_stream failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 处理Operating Mode Notification信息元素，更新用户信息 */
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    //puc_tmp_ie = mac_get_opmode_notify_ie((oal_uint8*)puc_payload, us_msg_len, us_ie_offset);
    puc_tmp_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_payload + us_ie_offset, (oal_int32)(us_msg_len - us_ie_offset));
    if (OAL_PTR_NULL != puc_tmp_ie)
    {
        ul_ret = hmac_ie_proc_opmode_field(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info, (mac_opmode_notify_stru *)puc_tmp_ie, mac_get_frame_sub_type(puc_mac_hdr));
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(0,OAM_SF_ROAM,"{hmac_roam_process_assoc_rsp::hmac_ie_proc_opmode_field fail.return err code}");
        }
    }
#endif

    /* dmac offload架构下，同步STA USR信息到dmac */
    ul_ret = hmac_config_user_cap_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_config_usr_cap_syn failed[%d].}", ul_ret);
        return ul_ret;
    }

    /*  更新用户的mac地址，漫游时mac会更新 */
    //oal_set_mac_addr(pst_hmac_user->st_user_base_info.auc_user_mac_addr, pst_hmac_vap->st_vap_base_info.auc_bssid);

    ul_ret = hmac_config_user_info_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_config_user_info_syn failed[%d].}", ul_ret);
        return ul_ret;
    }

    ul_ret = hmac_config_user_rate_info_syn(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_syn_rate_info failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 上报关联成功消息给APP */
    ul_ret = hmac_roam_connect_notify_wpas(pst_hmac_vap, puc_mac_hdr, pst_rx_ctrl->st_rx_info.us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_roam_connect_notify_wpas failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* user已经关联上，抛事件给DMAC，在DMAC层挂用户算法钩子 */
    ul_ret = hmac_user_add_notify_alg(&(pst_hmac_vap->st_vap_base_info), pst_hmac_user->st_user_base_info.us_assoc_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_process_assoc_rsp::hmac_user_add_notify_alg failed[%d].}", ul_ret);
        return ul_ret;
    }

    if (OAL_TRUE != mac_mib_get_privacyinvoked(&pst_hmac_vap->st_vap_base_info))
    {
        /* 非加密情况下，漫游成功 */
        hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_UP);
        hmac_roam_connect_succ(pst_roam_info, OAL_PTR_NULL);
    }
    else
    {
#ifdef _PRE_WLAN_FEATURE_11R
        if (OAL_TRUE == pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
        {
            /* FT情况下，漫游成功 */
            hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_UP);
            hmac_roam_connect_succ(pst_roam_info, OAL_PTR_NULL);
            return OAL_SUCC;
        }
#endif //_PRE_WLAN_FEATURE_11R
        if (OAL_TRUE == mac_mib_get_rsnaactivated(&pst_hmac_vap->st_vap_base_info))
        {
            hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_HANDSHAKING);
            /* 启动握手超时定时器 */
            hmac_roam_connect_start_timer(pst_roam_info, ROAM_HANDSHAKE_TIME_MAX);
        }
        else
        {
            /* 非 WPA 或者 WPA2 加密情况下(WEP_OPEN/WEP_SHARED)，漫游成功 */
            hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_UP);
            hmac_roam_connect_succ(pst_roam_info, OAL_PTR_NULL);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_succ
 功能描述  : 关联过程成功后，通知roam main状态机
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
OAL_STATIC oal_uint32 hmac_roam_connect_succ(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru                   *pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    hmac_user_stru                  *pst_hmac_user = pst_roam_info->pst_hmac_user;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user))
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态/CONNECT状态机为非UP状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }
    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_UP);

    /* 删除定时器 */
    hmac_roam_connect_del_timer(pst_roam_info);

    /* 通知ROAM主状态机 */
    hmac_roam_connect_complete(pst_hmac_vap, OAL_SUCC);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_stop
 功能描述  : 停止connect状态机，删除connect定时器。并通知roam main状态机
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
OAL_STATIC oal_uint32 hmac_roam_connect_fail(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_vap_stru                   *pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    roam_connect_state_enum_uint8    connect_state = pst_roam_info->st_connect.en_state;
    /* connect状态切换 */
    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_FAIL);

    /* connect信息初始化 */
    oal_memset(pst_roam_info->st_connect.auc_bssid, 0, WLAN_MAC_ADDR_LEN);
    pst_roam_info->st_connect.st_channel.uc_chan_number = 0;
    pst_roam_info->st_connect.st_channel.en_band        = WLAN_BAND_BUTT;
    pst_roam_info->st_connect.st_channel.en_bandwidth   = WLAN_BAND_WIDTH_BUTT;
    pst_roam_info->st_connect.st_channel.uc_idx         = 0;

    /* 释放关联请求帧 */
    if (OAL_PTR_NULL != pst_hmac_vap->puc_asoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_hmac_vap->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;
    }

    /* 通知ROAM主状态机，BSS回退由主状态机完成 */

    if(ROAM_CONNECT_STATE_HANDSHAKING == connect_state)
    {
        hmac_roam_connect_complete(pst_hmac_vap, OAL_ERR_CODE_ROAM_HANDSHAKE_FAIL);
    }
    else
    {
        hmac_roam_connect_complete(pst_hmac_vap, OAL_FAIL);
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_roam_connect_terminate
 功能描述  : 停止connect状态机，删除connect定时器。并通知roam main状态机
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
OAL_STATIC oal_uint32 hmac_roam_connect_terminate(hmac_roam_info_stru *pst_roam_info, oal_void *p_param)
{
    hmac_roam_connect_del_timer(pst_roam_info);
    return hmac_roam_connect_fail(pst_roam_info, p_param);
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_start
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
oal_uint32 hmac_roam_connect_start(hmac_vap_stru *pst_hmac_vap, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_roam_info_stru                             *pst_roam_info;
#ifdef _PRE_WLAN_FEATURE_11R
    wlan_mib_Dot11FastBSSTransitionConfigEntry_stru *pst_wlan_mib_ft_cfg;
#endif //_PRE_WLAN_FEATURE_11R

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_start::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }


    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_start::roam_info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    /* 漫游开关没有开时，不处理tbtt中断 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_start::roam disabled!}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    oal_memcopy(pst_roam_info->st_connect.auc_bssid, pst_bss_dscr->auc_bssid, WLAN_MAC_ADDR_LEN);
    oal_memcopy(&(pst_roam_info->st_connect.st_channel), &(pst_bss_dscr->st_channel), OAL_SIZEOF(mac_channel_stru));
    pst_roam_info->st_connect.pst_bss_dscr = pst_bss_dscr;


#ifdef _PRE_WLAN_FEATURE_11R
    pst_wlan_mib_ft_cfg = &pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg;
    if ((OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FastBSSTransitionActivated) &&
        (OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FTOverDSActivated))
    {
        return hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_FT_OVER_DS, (oal_void *)pst_bss_dscr);
    }
#endif //_PRE_WLAN_FEATURE_11R

    return hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_START, (oal_void *)pst_bss_dscr);

}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_stop
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
oal_uint32 hmac_roam_connect_stop(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_start::vap null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }


    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_start::roam_info null!}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }
    pst_roam_info->st_connect.en_state = ROAM_CONNECT_STATE_INIT;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_rx_tbtt
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
oal_void hmac_roam_connect_rx_tbtt(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_uint32                        ul_ret;


    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_scan_complete::vap null!}");
        return;
    }


    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        return;
    }

    /* 漫游开关没有开时，不处理tbtt中断 */
    if (pst_roam_info->uc_enable == 0)
    {
        return;
    }
    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_JOIN_COMP);

    ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_TBTT, (oal_void *)OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_rx_tbtt::EVENT_TBTT FAIL[%d]!}", ul_ret);
    }
    return;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_rx_mgmt
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
oal_void  hmac_roam_connect_rx_mgmt(hmac_vap_stru *pst_hmac_vap, dmac_wlan_crx_event_stru *pst_crx_event)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_uint32                        ul_ret;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_rx_mgmt::vap null!}");
        return;
    }


    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        return;
    }

    /* 漫游开关没有开时，不处理管理帧接收 */
    if (0 == pst_roam_info->uc_enable)
    {
        return;
    }

    ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_MGMT_RX, (oal_void *)pst_crx_event);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_rx_mgmt::MGMT_RX FAIL[%d]!}", ul_ret);
    }

    return;
}

/*****************************************************************************
 函 数 名  : hmac_roam_connect_key_done
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
oal_void hmac_roam_connect_key_done(hmac_vap_stru *pst_hmac_vap)
{
    hmac_roam_info_stru              *pst_roam_info;
    oal_uint32                        ul_ret;

    if (pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_key_done::vap null!}");
        return;
    }


    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (pst_roam_info == OAL_PTR_NULL)
    {
        return;
    }

    /* 漫游开关没有开时，不处理管理帧接收 */
    if (0 == pst_roam_info->uc_enable)
    {
        return;
    }

    /* 主状态机为非CONNECTING状态/CONNECT状态机为非UP状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        return;
    }

    ul_ret = hmac_roam_connect_fsm_action(pst_roam_info, ROAM_CONNECT_FSM_EVENT_KEY_DONE, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_key_done::KEY_DONE FAIL[%d]!}", ul_ret);
    }
    OAM_WARNING_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_key_done::KEY_DONE !}");

    return;
}

#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
/*****************************************************************************
 函 数 名  : hmac_roam_connect_ft_reassoc
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
oal_uint32 hmac_roam_connect_ft_reassoc(hmac_vap_stru *pst_hmac_vap)
{
    wlan_mib_Dot11FastBSSTransitionConfigEntry_stru *pst_wlan_mib_ft_cfg;
    hmac_roam_info_stru                             *pst_roam_info;
    oal_uint32                                       ul_ret;

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_ft_reassoc::param null.}");
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_roam_info = (hmac_roam_info_stru *)pst_hmac_vap->pul_roam_info;
    if (OAL_PTR_NULL == pst_roam_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_connect_ft_reassoc::pul_roam_info null.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 漫游开关没有开时，不处理 */
    if (0 == pst_roam_info->uc_enable)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM, "{hmac_roam_connect_ft_reassoc::roam disabled.}");
        return OAL_ERR_CODE_ROAM_DISABLED;
    }

    /* 主状态机为非CONNECTING状态，失败 */
    if (pst_roam_info->en_main_state != ROAM_MAIN_STATE_CONNECTING)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_connect_ft_reassoc::main state[%d] error.}", pst_roam_info->en_main_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    /* CONNECT状态机为非WAIT_JOIN状态，失败 */
    if (pst_roam_info->st_connect.en_state != ROAM_CONNECT_STATE_WAIT_ASSOC_COMP)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_connect_ft_reassoc::connect state[%d] error.}", pst_roam_info->st_connect.en_state);
        return OAL_ERR_CODE_ROAM_STATE_UNEXPECT;
    }

    pst_wlan_mib_ft_cfg = &pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg;
    if ((OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FastBSSTransitionActivated) &&
        (OAL_TRUE == pst_wlan_mib_ft_cfg->en_dot11FTOverDSActivated))
    {
        /* 配置join参数 */
        ul_ret = hmac_roam_connect_set_join_params(pst_hmac_vap, pst_roam_info->st_connect.pst_bss_dscr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                           "{hmac_roam_connect_ft_reassoc::hmac_roam_connect_set_join_params fail[%d].}", ul_ret);
            return ul_ret;
        }
    }

    /* 发送关联请求 */
    ul_ret = hmac_roam_send_reassoc_req(pst_roam_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ROAM,
                       "{hmac_roam_connect_ft_reassoc::hmac_roam_send_assoc_req failed[%d].}", ul_ret);
        return ul_ret;
    }

    hmac_roam_connect_change_state(pst_roam_info, ROAM_CONNECT_STATE_WAIT_ASSOC_COMP);

    /* 启动关联超时定时器 */
    hmac_roam_connect_start_timer(pst_roam_info, ROAM_ASSOC_TIME_MAX);

    return OAL_SUCC;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

