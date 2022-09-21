/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_mgmt_classifier.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : HMAC模块管理帧操作函数定义的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月20日
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
#include "hmac_rx_data.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_mgmt_classifier.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_mgmt_sta.h"
#include "hmac_mgmt_ap.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) && !defined(_PRE_PC_LINT) && !defined(WIN32))
OAL_STATIC oal_uint8 g_ucLinklossLogSwitch = 0;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hmac_mgmt_tx_action
 功能描述  : ACTION帧发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_action(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_action_mgmt_args_stru  *pst_action_args)
{
    if ((OAL_PTR_NULL == pst_hmac_vap)
     || (OAL_PTR_NULL == pst_hmac_user)
     || (OAL_PTR_NULL == pst_action_args))
    {
        OAM_ERROR_LOG3(0, OAM_SF_TX, "{hmac_mgmt_tx_action::param null, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_action_args);
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch (pst_action_args->uc_category)
    {
        case MAC_ACTION_CATEGORY_BA:

            switch (pst_action_args->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_REQ:
                    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_mgmt_tx_action::MAC_BA_ACTION_ADDBA_REQ.}");
                    hmac_mgmt_tx_addba_req(pst_hmac_vap, pst_hmac_user, pst_action_args);
                    break;

                #if 0 /* 可以不使用该接口，直接调用 */
                case BA_ACTION_ADDBA_RSP:
                    hmac_mgmt_tx_addba_rsp(hmac_vap_stru * pst_hmac_vap, hmac_user_stru * pst_hmac_user, mac_action_mgmt_args_stru * pst_action_args)
                    break;
                #endif

                case MAC_BA_ACTION_DELBA:
                    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_mgmt_tx_action::MAC_BA_ACTION_DELBA.}");
                    hmac_mgmt_tx_delba(pst_hmac_vap, pst_hmac_user, pst_action_args);
                    break;

                default:
                    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_mgmt_tx_action::invalid ba type[%d].}", pst_action_args->uc_action);
                    return OAL_FAIL;    /* 错误类型待修改 */
            }
            break;

        default:
            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_mgmt_tx_action::invalid ba type[%d].}", pst_action_args->uc_category);
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_tx_priv_req
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_mgmt_tx_priv_req(
                hmac_vap_stru              *pst_hmac_vap,
                hmac_user_stru             *pst_hmac_user,
                mac_priv_req_args_stru     *pst_priv_req)
{
    mac_priv_req_11n_enum_uint8  en_req_type;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_priv_req))
    {
        OAM_ERROR_LOG3(0, OAM_SF_TX, "{hmac_mgmt_tx_priv_req::param null, %d %d %d.}", pst_hmac_vap, pst_hmac_user, pst_priv_req);
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_req_type = pst_priv_req->uc_type;

    switch (en_req_type)
    {
        case MAC_A_MPDU_START:

            hmac_mgmt_tx_ampdu_start(pst_hmac_vap, pst_hmac_user, pst_priv_req);
            break;

        case MAC_A_MPDU_END:
            hmac_mgmt_tx_ampdu_end(pst_hmac_vap, pst_hmac_user, pst_priv_req);
            break;

       default:

            OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{hmac_mgmt_tx_priv_req::invalid en_req_type[%d].}", en_req_type);
            break;
    };

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : hmac_mgmt_rx_action
 功能描述  : 用于处理从wlan接收过来的管理帧，此函数中包含对端发送过来的DELBA
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_mgmt_rx_action(
                hmac_vap_stru          *pst_vap,
                oal_netbuf_stru        *pst_mgmt_netbuf)
{
    oal_uint8                          *puc_frame_payload;
    mac_ieee80211_frame_stru           *pst_frame_hdr;          /* 保存mac帧的指针 */
    hmac_rx_ctl_stru                   *pst_rx_ctrl;
    hmac_user_stru                     *pst_hmac_user;
    oal_uint32                          ul_rslt;
    oal_uint16                          us_user_idx;

    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_mgmt_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_mgmt_rx_action::param null, %d %d.}", pst_vap, pst_mgmt_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取该MPDU的控制信息 */
    pst_rx_ctrl = (hmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_netbuf);

    /* 获取帧头信息 */
    pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    /* 获取发送端的用户指针 */
    ul_rslt = mac_vap_find_user_by_macaddr(&pst_vap->st_vap_base_info, pst_frame_hdr->auc_address2, &us_user_idx);

    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_mgmt_rx_action::mac_vap_find_user_by_macaddr failed[%d].}", ul_rslt);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);

    /* 获取payload的指针 */
    puc_frame_payload = (oal_uint8 *)pst_frame_hdr + MAC_80211_FRAME_LEN;

    /* 不同ACTION帧的分发入口 */
    switch(puc_frame_payload[MAC_ACTION_OFFSET_CATEGORY])
    {
        case MAC_ACTION_CATEGORY_BA:
        {
            /* BA相关的ACTION帧的分发 */
            switch(puc_frame_payload[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_BA_ACTION_ADDBA_REQ:
                    hmac_mgmt_rx_addba_req(pst_vap, pst_hmac_user, puc_frame_payload);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:
                    hmac_mgmt_rx_addba_rsp(pst_vap, pst_hmac_user, puc_frame_payload);
                    break;

                case MAC_BA_ACTION_DELBA:
                    hmac_mgmt_rx_delba(pst_vap, pst_hmac_user, puc_frame_payload);
                    break;

                default:
                    break;
            }
        }

        break;

        default:
            OAM_INFO_LOG0(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_mgmt_rx_action::invalid action type.}");
            break;

    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : hmac_mgmt_rx_delba_event
 功能描述  : 自身DMAC模块产生DELBA的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_mgmt_rx_delba_event(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    dmac_ctx_action_event_stru         *pst_delba_event;
    oal_uint8                          *puc_da;                                 /* 保存用户目的地址的指针 */
    hmac_vap_stru                      *pst_vap;                                /* vap指针 */
    hmac_user_stru                     *pst_hmac_user;
    mac_action_mgmt_args_stru           st_action_args;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{hmac_mgmt_rx_delba_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_delba_event     = (dmac_ctx_action_event_stru *)(pst_event->auc_event_data);

    /* 获取vap结构信息 */
    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba_event::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取目的用户的MAC ADDR */
    puc_da = pst_delba_event->auc_mac_addr;

    /* 获取发送端的用户指针 */
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_vap->st_vap_base_info, puc_da);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba_event::mac_vap_find_user_by_macaddr failed.}");
        return OAL_FAIL;
    }

    st_action_args.uc_category = MAC_ACTION_CATEGORY_BA;
    st_action_args.uc_action   = MAC_BA_ACTION_DELBA;
    st_action_args.ul_arg1     = pst_delba_event->uc_tidno;     /* 该数据帧对应的TID号 */
    st_action_args.ul_arg2     = pst_delba_event->uc_initiator; /* DELBA中，触发删除BA会话的发起端 */
    st_action_args.ul_arg3     = pst_delba_event->uc_stauts;    /* DELBA中代表删除reason */
    st_action_args.puc_arg5    = puc_da;                        /* DELBA中代表目的地址 */

    hmac_mgmt_tx_action(pst_vap, pst_hmac_user, &st_action_args);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_rx_process_mgmt_event
 功能描述  : HMAC模块接收WLAN_CRX事件的处理函数
 输入参数  : pst_event_mem: 事件内存结构体指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_rx_process_mgmt_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    dmac_wlan_crx_event_stru           *pst_crx_event;
    oal_netbuf_stru                    *pst_netbuf;                     /* 用于保存管理帧指向的NETBUF */
    hmac_vap_stru                      *pst_vap;                        /* vap指针 */
    oal_uint32                          ul_ret;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_rx_process_mgmt_event::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_crx_event       = (dmac_wlan_crx_event_stru *)(pst_event->auc_event_data);
    pst_netbuf     = pst_crx_event->pst_netbuf;

    /* 获取vap结构信息 */
    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_BA, "{hmac_mgmt_rx_delba_event::pst_vap null.}");
        /* 将管理帧的空间归还内存池 */
        //oal_netbuf_free(pst_netbuf); /* 返回不成功，最外层会统一释放，这里不需要释放 */
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 接收管理帧是状态机的一个输入，调用状态机接口 */
    if (WLAN_VAP_MODE_BSS_AP == pst_vap->st_vap_base_info.en_vap_mode)
    {
        ul_ret = hmac_fsm_call_func_ap(pst_vap, HMAC_FSM_INPUT_RX_MGMT, pst_crx_event);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0,OAM_SF_BA,"{hmac_rx_process_mgmt_event::hmac_fsm_call_func_ap fail.err code1 [%u]}",ul_ret);
        }
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_vap->st_vap_base_info.en_vap_mode)
    {
        ul_ret = hmac_fsm_call_func_sta(pst_vap, HMAC_FSM_INPUT_RX_MGMT, pst_crx_event);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0,OAM_SF_BA,"{hmac_rx_process_mgmt_event::hmac_fsm_call_func_ap fail.err code2 [%u]}",ul_ret);
        }
    }

    /* 管理帧统一释放接口 */
    oal_netbuf_free(pst_netbuf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_mgmt_tbtt_event
 功能描述  : tbtt事件处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_mgmt_tbtt_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hmac_vap_stru                      *pst_hmac_vap;
    hmac_misc_input_stru                st_misc_input;
    oal_uint32                          ul_ret;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_mgmt_tbtt_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_misc_input, OAL_SIZEOF(hmac_misc_input_stru));

    /* 获取事件头和事件结构体指针 */
    pst_event      = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr  = &(pst_event->st_event_hdr);

    pst_hmac_vap   = mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{hmac_mgmt_tbtt_event::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_misc_input.en_type = HMAC_MISC_TBTT;

    /* 调用sta状态机，只有sta的tbtt事件上报到hmac */
    ul_ret = hmac_fsm_call_func_sta(pst_hmac_vap, HMAC_FSM_INPUT_MISC, &st_misc_input);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{hmac_mgmt_tbtt_event::hmac_fsm_call_func_sta fail. erro code is %u}", ul_ret);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_send_del_user_event
 功能描述  : hmac抛事件删除dmac用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_send_del_user_event(mac_vap_stru  *pst_mac_vap, oal_uint8 *puc_da)
{
    frw_event_mem_stru                 *pst_event_del_user;
    frw_event_stru                     *pst_event;
    dmac_ctx_del_user_stru             *pst_del_user_payload;

    pst_event_del_user = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_del_user_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_del_user))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_send_del_user_event::cannot alloc event,size[%d].}",OAL_SIZEOF(dmac_ctx_del_user_stru));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_del_user->puc_data;
    pst_del_user_payload = (dmac_ctx_del_user_stru *)pst_event->auc_event_data;
    pst_del_user_payload->us_user_idx = MAC_INVALID_USER_ID;
    oal_memcopy(pst_del_user_payload->auc_user_mac_addr, puc_da, WLAN_MAC_ADDR_LEN);

    /* 填充事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_WLAN_CTX,
                        DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,
                        OAL_SIZEOF(dmac_ctx_del_user_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    frw_event_dispatch_event(pst_event_del_user);
    FRW_EVENT_FREE(pst_event_del_user);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : hmac_mgmt_send_disasoc_deauth_event
 功能描述  : 去关联/去认证事件处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_mgmt_send_disasoc_deauth_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    dmac_diasoc_deauth_event           *pst_disasoc_deauth_event;
    oal_uint8                          *puc_da;                                 /* 保存用户目的地址的指针 */
    hmac_vap_stru                      *pst_vap;                                /* vap指针 */
    hmac_user_stru                     *pst_hmac_user = OAL_PTR_NULL;
    oal_uint32                          ul_rslt;
    oal_uint16                          us_user_idx;
    oal_uint8                           uc_event = 0;
    mac_vap_stru                       *pst_mac_vap = OAL_PTR_NULL;
    oal_uint16                          us_err_code = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_vap_stru                       *pst_up_vap1;
    mac_vap_stru                       *pst_up_vap2;
    mac_device_stru                    *pst_mac_device;
#endif

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_mgmt_send_disasoc_deauth_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_disasoc_deauth_event     = (dmac_diasoc_deauth_event *)(pst_event->auc_event_data);

    /* 获取vap结构信息 */
    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_send_disasoc_deauth_event::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap = &pst_vap->st_vap_base_info;

    /* 获取目的用户的MAC ADDR */
    puc_da      = pst_disasoc_deauth_event->auc_des_addr;
    uc_event    = pst_disasoc_deauth_event->uc_event;
    us_err_code = pst_disasoc_deauth_event->uc_reason;

    /* 发送去认证, 未关联状态收到第三类帧 */
    if(DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH == uc_event)
    {
        hmac_mgmt_send_deauth_frame(pst_mac_vap,
                                    puc_da,
                                    us_err_code,
                                    OAL_FALSE); // 非PMF

#ifdef _PRE_WLAN_FEATURE_P2P
        pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

        /*  */
        /* 判断是异频DBAC模式时，无法判断是哪个信道收到的数据帧，两个信道都需要发去认证 */
        ul_rslt = mac_device_find_2up_vap(pst_mac_device, &pst_up_vap1, &pst_up_vap2);
        if (OAL_SUCC != ul_rslt)
        {
            return OAL_SUCC;
        }

        if (pst_up_vap1->st_channel.uc_chan_number == pst_up_vap2->st_channel.uc_chan_number)
        {
            return OAL_SUCC;
        }

        /* 获取另一个VAP */
        if (pst_mac_vap->uc_vap_id != pst_up_vap1->uc_vap_id)
        {
            pst_up_vap2 = pst_up_vap1;
        }

        /* 另外一个VAP也发去认证帧。error code加上特殊标记，组去认证帧时要修改源地址 */
        hmac_mgmt_send_deauth_frame(pst_up_vap2,
                                    puc_da,
                                    us_err_code | MAC_SEND_TWO_DEAUTH_FLAG,
                                    OAL_FALSE);
#endif

        return OAL_SUCC;
    }

    /* 获取发送端的用户指针 */
    ul_rslt = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_da, &us_user_idx);
    if (ul_rslt != OAL_SUCC)
    {

        OAM_WARNING_LOG4(0, OAM_SF_RX, "{hmac_mgmt_send_disasoc_deauth_event::Hmac cannot find USER by addr[%02X:XX:XX:%02X:%02X:%02X], just del DMAC user}",
                  puc_da[0],
                  puc_da[3],
                  puc_da[4],
                  puc_da[5]);

        return hmac_send_del_user_event(pst_mac_vap, puc_da);
    }

    /* 获取到hmac user,使用protected标志 */
    pst_hmac_user = mac_res_get_hmac_user(us_user_idx);

    hmac_mgmt_send_disassoc_frame(pst_mac_vap, puc_da, us_err_code, ((OAL_PTR_NULL==pst_hmac_user) ? OAL_FALSE : pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active));

    /* 删除用户 */
    hmac_user_del(pst_mac_vap, pst_hmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_proc_disasoc_misc_event
 功能描述  : HMAC去关联用户处理入口函数
 输入参数  : pst_event_mem: 事件内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  hmac_proc_disasoc_misc_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hmac_vap_stru           *pst_hmac_vap;
    hmac_user_stru          *pst_hmac_user;
    oal_bool_enum_uint8      en_is_protected = OAL_FALSE;  /* PMF */
    dmac_disasoc_misc_stru  *pdmac_disasoc_misc_stru;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_disasoc_misc_event::pst_event_mem is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pdmac_disasoc_misc_stru = (dmac_disasoc_misc_stru*)pst_event->auc_event_data;
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_disasoc_misc_event::pst_hmac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_proc_disasoc_misc_event::Device noticed to dissasoc user[%d] within reason[%d]!}",
                    pdmac_disasoc_misc_stru->us_user_idx,
                    pdmac_disasoc_misc_stru->en_disasoc_reason);

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) && !defined(_PRE_PC_LINT) && !defined(WIN32))
    /* 较强信号(大于-65dBm)下出现link loss则通过Bcpu输出全部寄存器，同时该维测默认不生效*/
    /* 因为一旦出错需要重启手机才能正常使用，使用时需要手动修改g_ucLinklossLogSwitch=1，并编译版本 */
    if (g_ucLinklossLogSwitch && (DMAC_DISASOC_MISC_LINKLOSS == pdmac_disasoc_misc_stru->en_disasoc_reason)&& (pst_hmac_vap->station_info.signal > -65))
    {
        wifi_open_bcpu_set(1);

#ifdef PLATFORM_DEBUG_ENABLE
        debug_uart_read_wifi_mem(OAL_TRUE);
#endif
    }
#endif

    #ifdef _PRE_WLAN_CHIP_TEST
    /* CCA测试时，需要保持STA不去关联, 如果有打开chip_test宏开关 */
    if(0 != g_st_dmac_test_mng.uc_chip_test_open)
    {
        /* 如果有打开cca测试 */
        if (1 == g_st_dmac_test_mng.uc_cca_flag)
        {
            // 是不是应该将break;换成return
        }
    }
    #endif


    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_hmac_user = mac_res_get_hmac_user(pdmac_disasoc_misc_stru->us_user_idx);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_disasoc_misc_event ap::pst_hmac_user is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_is_protected = pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active;

        /* 抛事件上报内核，已经去关联某个STA */
        hmac_handle_disconnect_rsp_ap(pst_hmac_vap, pst_hmac_user);

        /* 发去关联帧 */
        hmac_mgmt_send_disassoc_frame(&pst_hmac_vap->st_vap_base_info, pst_hmac_user->st_user_base_info.auc_user_mac_addr, MAC_ASOC_NOT_AUTH, en_is_protected);

        /* 删除用户 */
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);

    }
    else
    {

        /* 获用户 */
        pst_hmac_user = mac_res_get_hmac_user(pst_hmac_vap->st_vap_base_info.uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_disasoc_misc_event::pst_hmac_user is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_is_protected = pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active;

        /* BEGIN: STA发现AP信道修改，则删除用户，而不发送去认证帧 */
        if (pdmac_disasoc_misc_stru->en_disasoc_reason != DMAC_DISASOC_MISC_CHANNEL_MISMATCH)
        /* END: STA发现AP信道修改，则删除用户，而不发送去认证帧 */
        {
            /* 发送去认证帧到AP */
            hmac_mgmt_send_disassoc_frame(&pst_hmac_vap->st_vap_base_info, pst_hmac_user->st_user_base_info.auc_user_mac_addr, MAC_UNSPEC_REASON, en_is_protected);
        }

        /* 删除对应用户 */
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
        /* 设置状态为FAKE UP */
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);
        hmac_sta_handle_disassoc_rsp(pst_hmac_vap, HMAC_REPORT_DEAUTH);
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 函 数 名  : hmac_proc_roam_trigger_event
 功能描述  : HMAC漫游触发处理入口函数
 输入参数  : pst_event_mem: 事件内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  hmac_proc_roam_trigger_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    hmac_vap_stru           *pst_hmac_vap;
    oal_int8                 c_rssi;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_roam_trigger_event::pst_event_mem is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event    = (frw_event_stru *)pst_event_mem->puc_data;
    c_rssi       = *(oal_int8 *)pst_event->auc_event_data;
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_proc_roam_trigger_event::pst_hmac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    hmac_roam_trigger_handle(pst_hmac_vap, c_rssi);

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_ROAM

/*lint -e19*/
oal_module_symbol(hmac_mgmt_tx_priv_req);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

