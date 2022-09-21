/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_p2p.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2014年11月26日
  最近修改   :
  功能描述   : dmac_p2p.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月26日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_P2P_H__
#define __DMAC_P2P_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_P2P_H


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_P2P_SOCIAL_CHAN_1 1
#define DMAC_P2P_SOCIAL_CHAN_2 6
#define DMAC_P2P_SOCIAL_CHAN_3 11
#define IS_P2P_SOCIAL_CHANNEL(channel) ((channel == DMAC_P2P_SOCIAL_CHAN_1) || \
                                        (channel == DMAC_P2P_SOCIAL_CHAN_2) || \
                                        (channel == DMAC_P2P_SOCIAL_CHAN_3))
#define DMAC_P2P_SOCIAL_CHAN_CNT 3

#define DMAC_P2P_WILDCARD_SSID      "DIRECT-"
#define DMAC_P2P_WILDCARD_SSID_LEN  7

#define IS_P2P_WILDCARD_SSID(ssid, len) (((len) == DMAC_P2P_WILDCARD_SSID_LEN) && \
                                        !oal_memcmp((ssid), DMAC_P2P_WILDCARD_SSID, DMAC_P2P_WILDCARD_SSID_LEN))

#define P2P_NOA_ACTIVE(_pst_dmac_vap)           (_pst_dmac_vap->st_p2p_noa_param.en_is_active)
#define P2P_NOA_UPDATE(_pst_dmac_vap)           (_pst_dmac_vap->st_p2p_noa_param.en_need_update)


#define IS_P2P_OPPPS_ENABLED(_pst_dmac_vap)     (_pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl != 0)
#define IS_P2P_NOA_ENABLED(_pst_dmac_vap)       (_pst_dmac_vap->st_p2p_noa_param.uc_count !=0)
#define IS_P2P_PS_ENABLED(_pst_dmac_vap)        ((IS_P2P_OPPPS_ENABLED(_pst_dmac_vap))||(IS_P2P_NOA_ENABLED(_pst_dmac_vap)))

#define GET_ATTR_LEN(buf_ptr)   (OAL_MAKE_WORD16((buf_ptr)[1], (buf_ptr)[2]))
#define P2P_NOA_DESC_NUM    1
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
oal_uint8  dmac_p2p_listen_rx_mgmt(dmac_vap_stru   *pst_dmac_vap,
                                   oal_netbuf_stru *pst_netbuf);

extern oal_uint32  dmac_ap_up_rx_probe_req(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);

extern oal_void  mac_set_p2p0_ssid_ie(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len, oal_uint16 us_frm_type);
extern oal_void mac_set_p2p_noa(oal_void * pst_vap, oal_uint8 * puc_buffer, oal_uint8 * puc_ie_len);
extern oal_bool_enum_uint8 dmac_is_p2p_presence_req_frame(oal_uint8 * puc_data);
extern oal_uint32 dmac_process_p2p_presence_req(dmac_vap_stru * pst_dmac_vap, oal_netbuf_stru * pst_netbuf);
extern oal_uint16 dmac_mgmt_encap_p2p_presence_rsp(dmac_vap_stru * pst_dmac_vap, oal_netbuf_stru * pst_netbuf, oal_uint8 * puc_ra, oal_uint8 * puc_data);
extern oal_void dmac_process_p2p_noa(dmac_vap_stru * pst_dmac_vap, oal_netbuf_stru * pst_netbuf);
extern oal_uint8  *dmac_get_p2p_noa_attr(oal_uint8 * puc_frame_body, oal_uint16 us_rx_len, oal_uint16 uc_tag_param_offset, oal_uint16 *pus_attr_len);
extern oal_bool_enum_uint8 dmac_is_p2p_ie(oal_uint8 * puc_data);
extern oal_void mac_set_p2p_status(oal_uint8 * puc_buffer, oal_uint8 * puc_ie_len, P2P_STATUS_CODE_T status);
extern oal_uint32 dmac_p2p_noa_absent_start_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_p2p_noa_absent_end_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 dmac_p2p_oppps_ctwindow_end_event(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_p2p_oppps_ctwindow_start_event(dmac_vap_stru * pst_dmac_vap);
extern oal_void dmac_p2p_handle_ps(dmac_vap_stru * pst_dmac_vap, oal_bool_enum_uint8 en_pause);
extern oal_void dmac_p2p_reset_ps_status_for_dbac(
                                mac_device_stru  *pst_device,
                                mac_vap_stru     *pst_led_vap,
                                mac_vap_stru     *pst_flw_vap);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_p2p.h */
