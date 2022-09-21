/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hal_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : hal对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __HAL_EXT_IF_H__
#define __HAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_types.h"
#include "hal_commom_ops.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "hal_lpm_test.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HAL_EXT_IF_H

extern oal_int32 g_l_rf_channel_num;
extern oal_int32 g_l_rf_single_tran;
extern oal_int32 g_l_rf_fem_switch;

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/* 双芯片情况下，5G与2G对应的CHIP ID宏定义; 不同样片形态，5G与2G对应的CHIP ID不同 */
#if ((_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_VSPM310DMB) || (_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_WS835DMB))
#define HAL_DOUBLE_CHIP_5G_ID      0
#define HAL_DOUBLE_CHIP_2G_ID      1
#else
#define HAL_DOUBLE_CHIP_5G_ID      1
#define HAL_DOUBLE_CHIP_2G_ID      0
#endif
#endif

#define HAL_MAC_ERROR_THRESHOLD     10  /* mac硬件错误门限，用于软件协助硬件做不去关联复位动作 */
/* 0.1dbm单位 */
#define HAL_RSSI_SIGNAL_MIN                    (-1030)  /*信号跨度最小值 */
#define HAL_RSSI_SIGNAL_MAX                    (50)     /*信号跨度最大值*/
#define HAL_INVALID_SIGNAL_INITIAL             (1000)    /*非法初始信号极大值*/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/* HAL模块和DMAC模块共用的WLAN RX结构体 */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf链表一个元素 */
    oal_uint16              us_netbuf_num;      /* netbuf链表的个数 */
    oal_uint8               auc_resv[2];        /* 字节对齐 */
}hal_cali_hal2hmac_event_stru;

typedef struct
{
    oal_uint32 ul_packet_idx;

    oal_uint8 auc_payoald[4];
}hal_cali_hal2hmac_payload_stru;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32 hal_main_init(oal_void);
extern oal_void  hal_main_exit(oal_void);
#ifdef _PRE_WLAN_FEATURE_HUT
extern oal_void  hal_to_hut_irq_isr_register(hal_oper_mode_enum_uint8 en_oper_mode, oal_void (*p_func)(oal_void));
extern oal_void  hal_to_hut_irq_isr_unregister(oal_void);
#endif
extern oal_void  hal_get_hal_to_dmac_device(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_hal_device);

/*****************************************************************************
  10.1 芯片级别函数
*****************************************************************************/
extern oal_uint32 hal_chip_get_chip(oal_uint8 uc_chip_id,  hal_to_dmac_chip_stru **ppst_chip_stru);
extern oal_uint32 hal_chip_get_device_num(oal_uint8 uc_chip_id, oal_uint8 * puc_device_nums);
extern oal_uint32 hal_chip_get_device(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_device_stru);
/*****************************************************************************
  10.2 对外暴露的配置接口
*****************************************************************************/


/*****************************************************************************
  10.3 对应一套硬件MAC、PHY的静态内联函数
*****************************************************************************/
#define HAL_CHIP_LEVEL_FUNC
/*****************************************************************************
  10.3.1 CHIP级别   第一个入参类型为 hal_to_dmac_chip_stru
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_chip_version(hal_to_dmac_chip_stru * pst_hal_chip, oal_uint32 *pul_chip_ver)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_chip_version, pst_hal_chip, pul_chip_ver);
}

#define HAL_DEVICE_LEVEL_FUNC
/*****************************************************************************
  10.3.2 DEVICE级别   第一个入参类型为 hal_to_dmac_device_stru
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_set_hw)
{
    /* hi1102_rx_init_dscr_queue */
    HAL_PUBLIC_HOOK_FUNC2(_rx_init_dscr_queue, pst_device,uc_set_hw);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_destroy_netbuf)
{
    /* hi1102_rx_destroy_dscr_queue */
    HAL_PUBLIC_HOOK_FUNC2(_rx_destroy_dscr_queue, pst_device,uc_destroy_netbuf);
}

OAL_STATIC OAL_INLINE oal_void hal_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_al_rx_destroy_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_al_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_al_rx_init_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_init_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_destroy_dscr_queue(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_destroy_dscr_queue, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_init_hw_rx_isr_list, pst_device);
}
OAL_STATIC OAL_INLINE oal_void hal_free_rx_isr_list(hal_to_dmac_device_stru *pst_device, oal_dlist_head_stru  *pst_rx_isr_list)
{
    /* hi1102_free_rx_isr_list */
    HAL_PUBLIC_HOOK_FUNC1(_free_rx_isr_list, pst_rx_isr_list);
}

OAL_STATIC OAL_INLINE oal_void hal_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_destroy_hw_rx_isr_list, pst_device);
}

OAL_STATIC OAL_INLINE oal_void hal_free_rx_isr_info(hal_to_dmac_device_stru *pst_device, hal_hw_rx_dscr_info_stru *pst_rx_isr_info)
{
    oal_irq_disable();
    oal_dlist_add_tail(&(pst_rx_isr_info->st_dlist_head), &(pst_device->st_rx_isr_info_res_list));
    oal_irq_enable();
}

/*填充描述符的基本信息，包括帧长度、mac长度、安全信息*/
OAL_STATIC OAL_INLINE oal_void hal_tx_fill_basic_ctrl_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_fill_basic_ctrl_dscr, p_tx_dscr, pst_mpdu);
}

/* 将两个描述符连起来 */
OAL_STATIC OAL_INLINE oal_void  hal_tx_ctrl_dscr_link(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_ctrl_dscr_link, pst_tx_dscr_prev, pst_tx_dscr);
}

/* 从描述符的next获取下一个描述符地址 */
OAL_STATIC OAL_INLINE oal_void  hal_get_tx_dscr_next(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_tx_dscr_next, pst_tx_dscr, ppst_tx_dscr_next);
}

OAL_STATIC OAL_INLINE oal_void  hal_tx_ctrl_dscr_unlink(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC1(_tx_ctrl_dscr_unlink, pst_tx_dscr);
}

/* 设置除基本信息外的所有其他描述符字段 */
OAL_STATIC OAL_INLINE oal_void hal_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature)
{
    HAL_PUBLIC_HOOK_FUNC5(_tx_ucast_data_set_dscr, pst_hal_device, pst_tx_dscr, pst_txop_feature, pst_txop_alg, pst_ppdu_feature);
}

/* 设置管理帧，组播 广播数据帧除基本信息外的所有其他描述符字段 */
OAL_STATIC OAL_INLINE oal_void hal_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature)
{
    HAL_PUBLIC_HOOK_FUNC5(_tx_non_ucast_data_set_dscr, pst_hal_device, pst_tx_dscr, pst_txop_feature, pst_txop_alg, pst_ppdu_feature);
}

/*****************************************************************************
 函 数 名  : hal_tx_set_dscr_modify_mac_header_length
 功能描述  : 修改描述符中的mac 帧头长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_modify_mac_header_length(hal_to_dmac_device_stru *pst_hal_device,hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_modify_mac_header_length, pst_tx_dscr, uc_mac_header_length);
}

/*****************************************************************************
 函 数 名  : hal_tx_set_seqno_sw_generate
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_seqno_sw_generate(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_seqno_sw_generate, pst_tx_dscr, uc_sw_seqno_generate);
}

/*针对amsdu，根据输入的msdu个数，返回发送描述符的首段长度，以及第二段长度 */
OAL_STATIC OAL_INLINE oal_void hal_tx_get_size_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_size_dscr, us_msdu_num, pul_dscr_one_size, pul_dscr_two_size);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_get_vap_id(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id, oal_int32 is_proxysta_feature)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_vap_id, pst_tx_dscr, puc_vap_id,is_proxysta_feature);
}

OAL_STATIC OAL_INLINE oal_void hal_tx_get_dscr_ctrl_one_param(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ctrl_one_param, pst_tx_dscr, pst_tx_dscr_one_param);
}

/*****************************************************************************
 函 数 名  : hal_tx_get_dscr_tx_cnt
 功能描述  : 获取MAC发包的发送次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_tx_cnt(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_tx_cnt, pst_tx_dscr, puc_tx_count);
}

/*****************************************************************************
 函 数 名  : hal_tx_get_dscr_seq_num
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_seq_num(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_seq_num, pst_tx_dscr, pus_seq_num);
}

/*****************************************************************************
 函 数 名  : hal_tx_set_dscr_status
 功能描述  : 设置发送描述符状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   :  00241943
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_set_dscr_status(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_set_dscr_status, pst_tx_dscr, uc_status);
}

OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_dscr_chiper_type, pst_tx_dscr, puc_chiper_type, puc_chiper_key_id);
}


/*****************************************************************************
 函 数 名  : hal_tx_enable_peer_sta_ps_ctrl
 功能描述  : 使能peer_sta_ps_ctrl
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_enable_peer_sta_ps_ctrl, pst_hal_device, uc_lut_index);
}
/*****************************************************************************
 函 数 名  : hal_tx_disable_peer_sta_ps_ctrl
 功能描述  : 去使能peer_sta_ps_ctrl
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_disable_peer_sta_ps_ctrl, pst_hal_device, uc_lut_index);
}



/*****************************************************************************
 函 数 名  : hal_tx_get_dscr_status
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_status(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_status, pst_tx_dscr, puc_status);
}
/*****************************************************************************
 函 数 名  : hal_tx_get_dscr_send_rate_rank
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_send_rate_rank(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_send_rate_rank, pst_tx_dscr, puc_send_rate_rank);
}


/*****************************************************************************
 函 数 名  : hal_tx_get_bar_dscr_ba_ssn
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_ba_ssn(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ba_ssn, pst_tx_dscr, pus_ba_ssn);
}

/*****************************************************************************
 函 数 名  : hal_tx_get_bar_dscr_ba_ssn
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_dscr_ba_bitmap(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_ba_bitmap, pst_tx_dscr, pul_ba_bitmap);
}

/*****************************************************************************
 函 数 名  : hal_tx_put_dscr
 功能描述  : 根据队列类型，将一个描述符链表的首地址，告知硬MAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_put_dscr, pst_hal_device, en_tx_queue_type, past_tx_dscr);
}

/*****************************************************************************
 函 数 名  : hal_get_tx_q_status
 功能描述  : 获取发送队列状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_tx_q_status, pst_hal_device, pul_status, uc_qnum);
}

/*****************************************************************************
 函 数 名  : hal_tx_get_ampdu_len
 功能描述  : 获取ampdu字节数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_ampdu_len, pst_hal_device, pst_dscr, pul_ampdu_len);
}
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 函 数 名  : hal_tx_get_protocol_mode
 功能描述  : 获取发送当前数据帧所使用的协议模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_protocol_mode, pst_hal_device, pst_dscr, puc_protocol_mode);
}
#endif

/*获取接收描述符大小*/
OAL_STATIC OAL_INLINE oal_void hal_rx_get_size_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_dscr_size)
{
    *pul_dscr_size = WLAN_RX_DSCR_SIZE;
}

/*获取描述符信息*/
OAL_STATIC OAL_INLINE oal_void hal_rx_get_info_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics)
{
    HAL_PUBLIC_HOOK_FUNC4(_rx_get_info_dscr, pul_rx_dscr, pst_rx_ctl, pst_rx_status, pst_rx_statistics);
}

OAL_STATIC OAL_INLINE oal_void hal_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_hal_vap, pst_hal_device, uc_vap_id, ppst_hal_vap);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_get_netbuffer_addr_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_get_netbuffer_addr_dscr, pul_rx_dscr, ppul_mac_hdr_addr);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_rx_show_dscr_queue_info, pst_hal_device, en_rx_dscr_type);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_sync_invalid_dscr, pst_hal_device, pul_dscr, en_queue_num);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_free_dscr_list, pst_hal_device, en_queue_num, pul_rx_dscr);
}

OAL_STATIC OAL_INLINE oal_void hal_dump_tx_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC1(_dump_tx_dscr, pul_tx_dscr);
}

/*****************************************************************************
 函 数 名  : hal_reg_write
 功能描述  : 写SoC、MAC, PHY寄存器的值, 仅用于调测
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
OAL_STATIC OAL_INLINE oal_void  hal_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_reg_write, pst_hal_device, ul_addr, ul_val);
}

/*****************************************************************************
 函 数 名  : hal_set_counter_clear
 功能描述  : 统计计数器清零
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_counter_clear, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_reg_write16
 功能描述  : 写SoC、MAC, PHY寄存器的值, 仅用于调测
 输入参数  : pst_hal_device:51需要通过pst_hal_device来查找信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reg_write16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 us_val)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    HAL_PUBLIC_HOOK_FUNC3(_reg_write16, pst_hal_device, ul_addr, us_val);
#endif
}

/*****************************************************************************
 函 数 名  : hal_set_machw_rx_buff_addr
 功能描述  : 设置硬件接收描述符队列首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_machw_rx_buff_addr, pst_hal_device, ul_rx_dscr, en_queue_num);
}

/*****************************************************************************
 函 数 名  : set_machw_rx_buff_addr_sync
 功能描述  : 设置硬件接收描述符队列首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hal_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num)
{
    return HAL_PUBLIC_HOOK_FUNC3(_set_machw_rx_buff_addr_sync, pst_hal_device, ul_rx_dscr, en_queue_num);
}

#if (_PRE_MULTI_CORE_MODE ==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
OAL_STATIC OAL_INLINE oal_void hal_get_pwr_comp_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tx_ratio, oal_int16 * ps_pwr_comp_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_pwr_comp_val, pst_hal_device, ul_tx_ratio, ps_pwr_comp_val);
}

OAL_STATIC OAL_INLINE oal_void hal_over_temp_handler(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_over_temp_handler, pst_hal_device);
}


#endif

/*****************************************************************************
 函 数 名  : hal_rx_add_dscr
 功能描述  : 增加接收描述符
 输入参数  : en_queue_num     需要增加描述符的接收队列号
             us_rx_dscr_num   需要增加的描述符个数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_dscr_num)
{
    HAL_PUBLIC_HOOK_FUNC3(_rx_add_dscr, pst_hal_device, en_queue_num, us_rx_dscr_num);
}

/*****************************************************************************
 函 数 名  : hal_set_machw_tx_suspend
 功能描述  : 挂起硬件发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_machw_tx_suspend, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_set_machw_tx_resume
 功能描述  : 恢复硬件发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_machw_tx_resume, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_reset_phy_machw
 功能描述  : 复位MAC 和 PHY
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                                        oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg)
{
    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_HW_BEGIN);

    HAL_PUBLIC_HOOK_FUNC5(_reset_phy_machw, pst_hal_device,en_type,sub_mod,uc_reset_phy_reg,uc_reset_mac_reg);

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_HW_END);

}

/*****************************************************************************
  hal初始化/退出/复位相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_disable_machw_phy_and_pa
 功能描述  : 停止PA和PHY的工作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device)
{
    /* hi1102_disable_machw_phy_and_pa */
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_phy_and_pa, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_enable_machw_phy_and_pa
 功能描述  : 使能PA和PHY的工作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device)
{
    /* d 在使能pa之前，复位一下mac和phy的逻辑，防止硬件还有数据，概率性造成mac异常处理 */
    /* 不复位寄存器，后面三个参数为0，第二个参数为ALL */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
   hal_reset_phy_machw(pst_hal_device, HAL_RESET_HW_TYPE_MAC, 0, 0, 0);
#endif
    /* hi1102_enable_machw_phy_and_pa */
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_phy_and_pa, pst_hal_device);
}


/*****************************************************************************
  hal MAC hardware初始化接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_initialize_machw
 功能描述  : MAC hardware初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_machw(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_machw, pst_hal_device);
}

/*****************************************************************************
  频段、带宽、信道号相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_set_freq_band
 功能描述  : 设置工作频段
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_freq_band, pst_hal_device, en_band);
}

/*****************************************************************************
 函 数 名  : hal_set_bandwidth_mode
 功能描述  : 设置带宽
 输入参数  : en_bandwidth: 带宽枚举
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_bandwidth_mode, pst_hal_device, en_bandwidth);
}
OAL_STATIC OAL_INLINE oal_void hal_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_process_phy_freq, pst_hal_device);
}
/*****************************************************************************
 函 数 名  : hal_set_primary_channel
 功能描述  : 设置主20信道号
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_primary_channel, pst_hal_device, uc_channel_num, uc_band, uc_channel_idx, en_bandwidth);
}

#ifdef _PRE_WLAN_HW_TEST
/*****************************************************************************
 函 数 名  : hal_set_phy_tx_scale
 功能描述  : 设置phy的tx scale
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_tx_scale, pst_hal_device, en_2g_11ac);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hal_freq_adjust
 功能描述  : 设置频偏
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_freq_adjust(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_pll_int, oal_uint16 us_pll_frac)
{
    HAL_PUBLIC_HOOK_FUNC3(_freq_adjust, pst_hal_device, us_pll_int, us_pll_frac);
}
#endif
/*****************************************************************************
 函 数 名  : hal_set_rx_multi_ant
 功能描述  : 设置接收通道
 输入参数  : uc_rx_chain: 接收通道
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_multi_ant, pst_hal_device, uc_rx_chain);
}

/*****************************************************************************
 函 数 名  : hal_add_machw_ba_lut_entry
 功能描述  : 添加一个表项到BA LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size)
{
    HAL_PUBLIC_HOOK_FUNC6(_add_machw_ba_lut_entry, pst_hal_device,
                    uc_lut_index, puc_dst_addr, uc_tid, uc_seq_no, uc_win_size);
}

/*****************************************************************************
 函 数 名  : hal_remove_machw_ba_lut_entry
 功能描述  : 从BA LUT表中删除一个表项
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_remove_machw_ba_lut_entry, pst_hal_device, uc_lut_index);
}

/*****************************************************************************
 函 数 名  : hal_get_machw_ba_params
 功能描述  : 获取BA LUT表内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
														oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para)
{
    HAL_PUBLIC_HOOK_FUNC5(_get_machw_ba_params, pst_hal_device, uc_index,pst_addr_h,pst_addr_l,pst_ba_para);
}

/*****************************************************************************
 函 数 名  : hal_restore_machw_ba_params
 功能描述  : 恢复BA LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                                oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para)
{
    HAL_PUBLIC_HOOK_FUNC5(_restore_machw_ba_params, pst_hal_device, uc_index,ul_addr_h,ul_addr_l,ul_ba_para);
}

/*****************************************************************************
          RA LUT操作相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_machw_seq_num_index_update_per_tid
 功能描述  : 设置RA LUT index表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag)
{
    HAL_PUBLIC_HOOK_FUNC3(_machw_seq_num_index_update_per_tid, pst_hal_device, uc_lut_index, uc_qos_flag);
}

/*****************************************************************************
 函 数 名  : hal_set_tx_sequence_num
 功能描述  : 设置TX SEQUENCE NUM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_tx_sequence_num, pst_hal_device,uc_lut_index,uc_tid,uc_qos_flag, ul_val_write);
}

/*****************************************************************************
 函 数 名  : hal_get_tx_sequence_num
 功能描述  : 设置TX SEQUENCE NUM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read )
{
    HAL_PUBLIC_HOOK_FUNC5(_get_tx_sequence_num, pst_hal_device, uc_lut_index,uc_tid,uc_qos_flag,pst_val_read);
}

/*****************************************************************************
 函 数 名  : hal_reset_init
 功能描述  : 复位初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_init(hal_to_dmac_device_stru * pst_hal_device)
{
    /* hi1102_reset_init */
    HAL_PUBLIC_HOOK_FUNC1(_reset_init, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_reset_destroy
 功能描述  : 复位资源释放接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_destroy(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_reset_destroy, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_reset_reg_restore
 功能描述  : 复位寄存器恢复
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type)
{
    /* hi1102_reset_reg_restore */
    HAL_PUBLIC_HOOK_FUNC2(_reset_reg_restore, pst_hal_device,en_type);
}
/*****************************************************************************
 函 数 名  : hal_reset_reg_save
 功能描述  : 复位寄存器保存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   :  00241943
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type)
{
    /* hi1102_reset_reg_save */
    HAL_PUBLIC_HOOK_FUNC2(_reset_reg_save, pst_hal_device,en_type);
}

/*****************************************************************************
 函 数 名  : hal_reset_reg_dma_save
 功能描述  : MAC和PHY寄存器DMA方式保存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_dma_save(hal_to_dmac_device_stru * pst_hal_device,oal_uint8* pucdmach0,oal_uint8* pucdmach1,oal_uint8* pucdmach2)
{
    /* hi1102_reset_reg_dma_save */
    HAL_PUBLIC_HOOK_FUNC4(_reset_reg_dma_save, pst_hal_device,pucdmach0,pucdmach1,pucdmach2);
}

/*****************************************************************************
 函 数 名  : hal_reset_reg_dma_restore
 功能描述  : MAC和PHY寄存器DMA方式恢复
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reset_reg_dma_restore(hal_to_dmac_device_stru * pst_hal_device,oal_uint8* pucdmach0,oal_uint8* pucdmach1,oal_uint8* pucdmach2)
{
    /* hi1102_reset_reg_dma_restore */
    HAL_PUBLIC_HOOK_FUNC4(_reset_reg_dma_restore, pst_hal_device,pucdmach0,pucdmach1,pucdmach2);
}

/*****************************************************************************
 函 数 名  : hal_disable_machw_ack_trans
 功能描述  : 控制硬件在收到单播帧时不回ACK
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_ack_trans, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_disable_machw_ack_trans
 功能描述  : 控制硬件在收到单播帧时回ACK
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_ack_trans, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_disable_machw_cts_trans
 功能描述  : 控制硬件在收到RTS时不回CTS
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_cts_trans, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_enable_machw_cts_trans
 功能描述  : 控制硬件在收到RTS时回CTS
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_cts_trans, pst_hal_device);
}


/*****************************************************************************
  PHY相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_initialize_phy
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_phy(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_phy, pst_hal_device);
}

#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
/*****************************************************************************
 函 数 名  : hal_radar_config_reg
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain)
{
    HAL_PUBLIC_HOOK_FUNC2(_radar_config_reg, pst_hal_device, en_dfs_domain);
}
#endif

/*****************************************************************************
  RF相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_initialize_rf_sys
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_rf_sys, pst_hal_device);
}
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

OAL_STATIC OAL_INLINE oal_void  hal_set_rf_custom_reg(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_rf_custom_reg, pst_hal_device);
}
#endif
#endif
OAL_STATIC OAL_INLINE oal_void  hal_psm_rf_sleep(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg)
{
    /* hi1102_psm_rf_sleep */
    HAL_PUBLIC_HOOK_FUNC2(_psm_rf_sleep, pst_hal_device, uc_restore_reg);
}

OAL_STATIC OAL_INLINE oal_void  hal_psm_rf_awake(hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg)
{
    /* hi1102_psm_rf_awake */
    HAL_PUBLIC_HOOK_FUNC2(_psm_rf_awake, pst_hal_device,uc_restore_reg);
}




#ifdef _PRE_WLAN_REALTIME_CALI
/*****************************************************************************
 函 数 名  : hal_rf_cali_realtime
 功能描述  : online dc校准入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_rf_cali_realtime(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_freq,
                                                           oal_uint8 uc_chn_idx, oal_uint8 uc_bandwidth, oal_uint8 uc_protocol)
{
     HAL_PUBLIC_HOOK_FUNC5(_rf_cali_realtime, pst_hal_device, uc_freq, uc_chn_idx, uc_bandwidth, uc_protocol);
}
#endif

/*****************************************************************************
  SoC相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_initialize_soc
 功能描述  : SoC上电初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_initialize_soc(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_initialize_soc, pst_hal_device);
}

/*****************************************************************************
  中断相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_get_mac_int_status
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_mac_int_status, pst_hal_device, pul_status);
}

/*****************************************************************************
 函 数 名  : hal_clear_mac_int_status
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_clear_mac_int_status, pst_hal_device, ul_status);
}

/*****************************************************************************
 函 数 名  : hal_get_mac_error_int_status
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_mac_error_int_status, pst_hal_device, pst_state);
}

/*****************************************************************************
 函 数 名  : hal_clear_mac_error_int_status
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_clear_mac_error_int_status, pst_hal_device, pst_status);
}


/* ERROR IRQ中断寄存器相关操作 */
OAL_STATIC OAL_INLINE oal_void  hal_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_mac_error_init_status, pst_hal_device, pst_status);
}

/* mac中断寄存器相关操作 */
OAL_STATIC OAL_INLINE oal_void  hal_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_mac_init_status, pst_hal_device, ul_status);
}

OAL_STATIC OAL_INLINE oal_void  hal_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_show_irq_info, pst_hal_device, uc_param);
}

OAL_STATIC OAL_INLINE oal_void  hal_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dump_all_rx_dscr, pst_hal_device);
}

OAL_STATIC OAL_INLINE oal_void  hal_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_clear_irq_stat, pst_hal_device);
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
typedef enum
{
    HAL_IRQ_TX_COMP_CNT     = 0,
    HAL_IRQ_STAT_BUTT
}hal_irq_stat_enum;
typedef oal_uint8 hal_irq_stat_enum_uint8;

OAL_STATIC OAL_INLINE oal_void hal_get_irq_stat(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 *puc_param, oal_uint32 ul_len, hal_irq_stat_enum_uint8 en_type)
{
    HAL_PUBLIC_HOOK_FUNC4(_get_irq_stat, pst_hal_device, puc_param, ul_len, en_type);
}
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
typedef enum
{
  HAL_DPD_CALI_START        = 0,
  HAL_DPD_CALI_STATUS       = 1,
  HAL_DPD_CALI_DATA_READ   = 2,
  HAL_DPD_CALI_DATA_WRITE  = 3,

}hal_dpd_cali_enum;


#define HI1102_DMAC_DPD_CALI_LUT_LENGTH 128
/*
 * DPD Calibration function
 */
OAL_STATIC OAL_INLINE oal_void hal_dpd_cali_func(oal_uint8 en_functype, oal_uint32* pstatus, oal_uint32* pdpd_cal_data_read, oal_uint32* pdpd_cal_data_write)
{
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
  HAL_PUBLIC_HOOK_FUNC4(_dpd_cali_func, en_functype, pstatus, pdpd_cal_data_read, pdpd_cal_data_write);
#endif
}
#endif


OAL_STATIC OAL_INLINE oal_void hal_cali_send_func(oal_uint8* puc_cal_data_write)
{
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
  HAL_PUBLIC_HOOK_FUNC1(_cali_send_func, puc_cal_data_write);
#endif
}


/*
根据hal维护的vap id，获取hal vap
*/
OAL_STATIC OAL_INLINE oal_void hal_get_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC4(_get_vap, pst_hal_device, vap_mode, vap_id, ppst_hal_vap);
}

/*
输入vap模式，hal创建vap结构，并标记vap id
*/
OAL_STATIC OAL_INLINE oal_void hal_add_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC4(_add_vap, pst_hal_device, vap_mode, uc_mac_vap_id, ppst_hal_vap);
}

/*
输入vap模式，hal删除vap结构，并标记vap id
*/
OAL_STATIC OAL_INLINE oal_void hal_del_vap(hal_to_dmac_device_stru * pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id)
{
    HAL_PUBLIC_HOOK_FUNC3(_del_vap, pst_hal_device, vap_mode, vap_id);
}

OAL_STATIC OAL_INLINE oal_void hal_set_proxysta_enable(hal_to_dmac_device_stru * pst_hal_device, oal_int32 l_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_proxysta_enable, pst_hal_device, l_enable);
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
OAL_STATIC OAL_INLINE oal_void hal_set_proxysta_vap_addr(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 vap_id, oal_uint8 *puc_mac_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_proxysta_vap_addr, pst_hal_device, vap_id, puc_mac_addr);
}
#endif
/*****************************************************************************
 函 数 名  : hal_vap_config_eifs_reg
 功能描述  : 配置EIFS_TIME 寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol)
{
    HAL_PUBLIC_HOOK_FUNC2(_config_eifs_time, pst_hal_device, en_protocol);
}

/*****************************************************************************
 函 数 名  : hal_register_alg_isr_hook
 功能描述  : 注册算法中断上半部钩子函数
 输入参数  : hal_to_dmac_device_stru    *pst_hal_device
             hal_isr_type_enum_uint8     en_isr_type
             hal_alg_noify_enum_uint8    en_alg_notify
             _alg_isr_func          p_func
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_register_alg_isr_hook(hal_to_dmac_device_stru    *pst_hal_device,
                                                          hal_isr_type_enum_uint8     en_isr_type,
                                                          hal_alg_noify_enum_uint8    en_alg_notify,
                                                          p_hal_alg_isr_func          p_func)

{
    HAL_PUBLIC_HOOK_FUNC4(_register_alg_isr_hook, pst_hal_device, en_isr_type, en_alg_notify, p_func);
}
/*****************************************************************************
 函 数 名  : hal_unregister_alg_isr_hook
 功能描述  : 注销算法中断上半部钩子函数
 输入参数  : hal_to_dmac_device_stru    *pst_hal_device
             hal_isr_type_enum_uint8     en_isr_type
             hal_alg_noify_enum_uint8    en_alg_notify
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_unregister_alg_isr_hook(hal_to_dmac_device_stru    *pst_hal_device,
                                                            hal_isr_type_enum_uint8     en_isr_type,
                                                            hal_alg_noify_enum_uint8    en_alg_notify)
{
    HAL_PUBLIC_HOOK_FUNC3(_unregister_alg_isr_hook,pst_hal_device, en_isr_type, en_alg_notify);
}

/*****************************************************************************
 函 数 名  : hal_one_packet_start
 功能描述  : 启动FCS
 输入参数  : struct tag_hal_to_dmac_device_stru *pst_hal_device
             hal_one_packet_cfg_stru *pst_cfg
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_one_packet_start, pst_hal_device, pst_cfg);
}
/*****************************************************************************
 函 数 名  : hal_one_packet_stop
 功能描述  : 停止FCS
 输入参数  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_one_packet_stop, pst_hal_device);
}
/*****************************************************************************
 函 数 名  : hal_one_packet_get_status
 功能描述  : 读取FCS状态
 输入参数  : struct tag_hal_to_dmac_device_stru *pst_hal_device
             hal_one_packet_status_stru *pst_status
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_one_packet_get_status, pst_hal_device, pst_status);
}

/*****************************************************************************
 函 数 名  : hal_reset_nav_timer
 功能描述  : 重置NAV计数器
 输入参数  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_reset_nav_timer, pst_hal_device);
}


/*****************************************************************************
 函 数 名  : hal_clear_hw_fifo
 功能描述  : 清除硬件发送缓冲区
 输入参数  : struct tag_hal_to_dmac_device_stru *pst_hal_device
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_clear_hw_fifo, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_mask_interrupt
 功能描述  : 屏蔽指定中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_mask_interrupt, pst_hal_device, ul_offset);
}
/*****************************************************************************
 函 数 名  : hal_unmask_interrupt
 功能描述  : 恢复指定中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset)
{
    HAL_PUBLIC_HOOK_FUNC2(_unmask_interrupt, pst_hal_device, ul_offset);
}

/*****************************************************************************
  寄存器调测接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_reg_info
 功能描述  : 读取SoC, MAC, PHY寄存器的值, 仅用于调测
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_reg_info, pst_hal_device, ul_addr, pul_val);
}

OAL_STATIC OAL_INLINE oal_void  hal_reg_info16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 *pus_val)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
    HAL_PUBLIC_HOOK_FUNC3(_reg_info16, pst_hal_device, ul_addr, pus_val);
#endif
}
OAL_STATIC OAL_INLINE oal_void hal_get_all_tx_q_status(hal_to_dmac_device_stru *pst_hal_device,oal_uint32 *pul_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_all_tx_q_status, pst_hal_device, pul_val);
}

/*****************************************************************************
 函 数 名  : hal_get_ampdu_bytes
 功能描述  : 读取MAC寄存器 ampdu发送接收字节数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_ampdu_bytes(hal_to_dmac_device_stru *pst_hal_device,oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_ampdu_bytes, pst_hal_device, pul_tx_bytes, pul_rx_bytes);
}
/*****************************************************************************
 函 数 名  : hal_get_ampdu_bytes
 功能描述  : 读取MAC寄存器 错误计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_rx_err_count(hal_to_dmac_device_stru *pst_hal_device,
                                                          oal_uint32 *pul_cnt1,
                                                          oal_uint32 *pul_cnt2,
                                                          oal_uint32 *pul_cnt3,
                                                          oal_uint32 *pul_cnt4,
                                                          oal_uint32 *pul_cnt5,
                                                          oal_uint32 *pul_cnt6)
{
    HAL_PUBLIC_HOOK_FUNC7(_get_rx_err_count, pst_hal_device, pul_cnt1, pul_cnt2, pul_cnt3, pul_cnt4, pul_cnt5, pul_cnt6);
}

/*****************************************************************************
 函 数 名  : hal_show_fsm_info
 功能描述  : 用于调测中显示fsm状态机值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : caohb
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_show_fsm_info, pst_hal_device);
}


/*****************************************************************************
 函 数 名  : hal_mac_error_msg_report
 功能描述  : mac错误上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_mac_error_msg_report, pst_hal_device, en_error_type);
}

/*****************************************************************************
 函 数 名  : hal_show_fsm_info
 功能描述  : 用于调测中显示fsm状态机值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : caohb
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_en_soc_intr, pst_hal_device);
}
/*****************************************************************************
 函 数 名  : hal_enable_beacon_filter
 功能描述  : 使能BEACON帧过滤
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device)
{
    //HAL_PUBLIC_HOOK_FUNC1(_enable_beacon_filter, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_disable_beacon_filter
 功能描述  : 不过滤beacon帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device)
{
   HAL_PUBLIC_HOOK_FUNC1(_disable_beacon_filter, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_enable_non_frame_filter
 功能描述  : 使能non frame filter
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_non_frame_filter, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_enable_monitor_mode
 功能描述  : 使能monitor模式，不根据帧类型过滤
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_monitor_mode, pst_hal_device);
}
/*****************************************************************************
 函 数 名  : hal_disable_monitor_mode
 功能描述  : 关闭monitor模式，根据帧类型过滤
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_monitor_mode, pst_hal_device);
}
#if (_PRE_WLAN_FEATURE_PMF  != _PRE_PMF_NOT_SUPPORT)

/*****************************************************************************
 函 数 名  : hal_set_pmf_crypto
 功能描述  : 设置pmf加解密使能位
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_pmf_crypto(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_crypto)
{
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    HAL_PUBLIC_HOOK_FUNC2(_set_pmf_crypto, pst_hal_vap, en_crypto);
#else
    return;
#endif
}
#endif /* #if(_PRE_WLAN_FEATURE_PMF  != _PRE_PMF_NOT_SUPPORT)  */
/*****************************************************************************
 函 数 名  : hal_ce_add_key
 功能描述  : 将密钥写进硬件寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_ce_add_key, pst_hal_device,pst_security_key,puc_addr);
}

#ifdef _PRE_WLAN_INIT_PTK_TX_PN
/*****************************************************************************
 函 数 名  : hal_tx_get_dscr_phy_mode_one
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月28日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_tx_get_dscr_phy_mode_one(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_tx_dscr,  oal_uint32 *pul_phy_mode_one)
{
    HAL_PUBLIC_HOOK_FUNC2(_tx_get_dscr_phy_mode_one, pst_tx_dscr, pul_phy_mode_one);
}

/*****************************************************************************
 函 数 名  : hal_tx_get_ra_lut_index
 功能描述  : 获取ra lut index
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月28日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC3(_tx_get_ra_lut_index, pst_hal_device, pst_dscr, puc_ra_lut_index);
}

/*****************************************************************************
 函 数 名  : hal_init_ptk_tx_pn
 功能描述  : 初始化ptk的tx pn
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key)
{
    HAL_PUBLIC_HOOK_FUNC2(_init_ptk_tx_pn, pst_hal_device,pst_security_key);
}
#endif

/*****************************************************************************
 函 数 名  : hal_disable_ce
 功能描述  : 关闭硬件加密
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_disable_ce(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_ce, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_ce_del_key
 功能描述  : 将密钥写进硬件寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key)
{
    HAL_PUBLIC_HOOK_FUNC2(_ce_del_key, pst_hal_device,pst_security_key);
}

/*****************************************************************************
 函 数 名  : hal_ce_add_peer_macaddr
 功能描述  : 将指定的MAC 地址添加到硬件Lut表
 输入参数  : hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   :  218984
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC3(_ce_add_peer_macaddr, pst_hal_device,uc_lut_idx,puc_addr);
}
/*****************************************************************************
 函 数 名  : hal_ce_del_peer_macaddr
 功能描述  : 将指定的MAC 地址从硬件Lut表删除
 输入参数  : hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   :  218984
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx)
{
    HAL_PUBLIC_HOOK_FUNC2(_ce_del_peer_macaddr, pst_hal_device,uc_lut_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_rx_pn
 功能描述  : 将pn no写入接收RX PN LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 函 数 名  : hal_get_rx_pn
 功能描述  : 读RX pn LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 函 数 名  : hal_set_tx_pn
 功能描述  : 将pn no写入接收Tx PN LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_tx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 函 数 名  : hal_get_rx_pn
 功能描述  : 读tx pn LUT表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_tx_pn, pst_hal_device, pst_pn_lut_cfg);
}

/*****************************************************************************
 函 数 名  : hal_get_rate_80211g_table
 功能描述  : 获取80211g速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_rate_80211g_table(hal_to_dmac_device_stru *pst_hal_device, oal_void **pst_rate)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_rate_80211g_table, pst_rate);
}

/*****************************************************************************
 函 数 名  : hal_get_rate_80211g_num
 功能描述  : 获取80211g速率个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_rate_80211g_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pst_data_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_rate_80211g_num, pst_data_num);
}

/*****************************************************************************
 函 数 名  : hal_get_hw_addr
 功能描述  : 获取硬件mac地址，来自eeprom或flash
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_hw_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_addr)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_hw_addr, puc_addr);
}

/*****************************************************************************
 函 数 名  : hal_enable_ch_statics
 功能描述  : 设置MAC的信道统计使能寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_ch_statics, pst_hal_device, uc_enable);
}


/*****************************************************************************
 函 数 名  : hal_set_ch_statics_period
 功能描述  : 设置MAC的信道统计时间长度寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ch_statics_period, pst_hal_device, ul_period);
}

/*****************************************************************************
 函 数 名  : hal_set_ch_measurement_period
 功能描述  : 设置MAC的信道统计时间长度寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ch_measurement_period, pst_hal_device, uc_period);
}

/*****************************************************************************
 函 数 名  : hal_read_ch_stats_result
 功能描述  : 读取硬件MAC信道统计寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_ch_statics_result, pst_hal_device, pst_ch_statics);
}

/*****************************************************************************
 函 数 名  : hal_get_ch_measurement_result
 功能描述  : 读取硬件PHY信道空闲功率测量结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_ch_measurement_result, pst_hal_device, pst_ch_statics);
}
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
/*****************************************************************************
 函 数 名  : hal_enable_radar_det
 功能描述  : 设置硬件PHY雷达检测使能位
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_radar_det, pst_hal_device, uc_enable);
}
#endif
/*****************************************************************************
 函 数 名  : hal_enable_sigB
 功能描述  : 设置硬件sigB的使能位状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_sigB, pst_hal_device, uc_enable);
}

/*****************************************************************************
 函 数 名  : hi1102_enable_improve_ce
 功能描述  : 设置硬件信道增强估计的使能位状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_improve_ce, pst_hal_device, uc_enable);
}

OAL_STATIC OAL_INLINE oal_void hal_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_acc_symb_num, pst_hal_device, ul_num);
}
/*****************************************************************************
 函 数 名  : hal_set_improve_ce_threshold
 功能描述  : 设置1*1improve 门限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_improve_ce_threshold(hal_to_dmac_device_stru* pst_hal_device, oal_uint32 ul_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_improve_ce_threshold, pst_hal_device, ul_val);
}
#ifdef _PRE_WLAN_FEATURE_DFS //1131_debug
/*****************************************************************************
 函 数 名  : hal_get_radar_det_result
 功能描述  : 读取硬件PHY雷达检测结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_radar_det_result, pst_hal_device, pst_radar_info);
}
#endif
/*****************************************************************************
 函 数 名  : hal_set_rts_rate_params
 功能描述  : 设置rts速率参数寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rts_rate_params, pst_hal_device, pst_hal_rts_tx_param);
}

/*****************************************************************************
 函 数 名  : hal_set_rts_rate_selection_mode
 功能描述  : 设置rts速率选择模式
             0: RTS速率 = PROT_DATARATE的配置
             1: RTS速率 = 硬件根据TX描述符计算出的值
             2: RTS速率 = min(PROT_DATARATE,硬件根据TX描述符计算出的值)
             3: RTS速率 = max(PROT_DATARATE,硬件根据TX描述符计算出的值)
 输入参数  : pst_hal_device, uc_rts_rate_select_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月8日
    作    者   :  68207
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode)

{
    HAL_PUBLIC_HOOK_FUNC2(_set_rts_rate_selection_mode, pst_hal_device, uc_rts_rate_select_mode);
}

#ifdef _PRE_WLAN_FEATURE_TPC
/*****************************************************************************
 函 数 名  : hal_set_tpc_params
 功能描述  : 设置phy tpc参数
 输入参数  : pst_hal_device, uc_band, uc_channel_num
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
//OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num)
//{
    //HAL_PUBLIC_HOOK_FUNC3(_set_bcn_phy_tx_mode, pst_hal_device, uc_band, uc_channel_num);
//}

/*****************************************************************************
 函 数 名  : hi1151_get_rf_temp
 功能描述  : 获取RF的实时温度
 输入参数  : pst_hal_device
 输出参数  : puc_rf_tsensor_rf_data,
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rf_temp, pst_hal_device, puc_cur_temp);
}
/*****************************************************************************
 函 数 名  : hal_set_tpc_init_rate_dac_lpf_table
 功能描述  : 设置dac, lpf, pa, upc档位
 输入参数  : pauc_rate_len, pauc_rate_idx
 输出参数  : pauc_rate_pow_table_2G, pauc_rate_pow_table_5G
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_tpc_init_rate_dac_lpf_table, pauc_rate_pow_table_2G, pauc_rate_pow_table_5G,
                            pauc_mode_len, uc_pow_mode);
}

/*****************************************************************************
 函 数 名  : hal_set_dac_lpc_pa_upc_level
 功能描述  : 设置dac, lpf, pa, upc档位
 输入参数  : c_dac_val, c_lpf_val,en_band, pac_tpc_level_table, uc_tpc_level_num
 输出参数  : pauc_dac_lpf_pa_code_table, ps_upc_gain_table
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code,
        oal_int8   *pac_tpc_level_table, oal_uint8 uc_tpc_level_num,
        oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table,oal_int16 *pas_other_gain_table,
        wlan_channel_band_enum_uint8 en_freq_band)
{
    HAL_PUBLIC_HOOK_FUNC7(_set_dac_lpc_pa_upc_level, uc_dac_lpf_code, pac_tpc_level_table,
                        uc_tpc_level_num, pauc_dac_lpf_pa_code_table,pas_upc_gain_table,pas_other_gain_table,en_freq_band);
}
#ifdef _PRE_WLAN_REALTIME_CALI
/*****************************************************************************
 函 数 名  : hal_get_tpc_cali_upc_gain_in_rf_list
 功能描述  : 获取64档UPC RF增益
 输入参数  : 无
 输出参数  : pac_upc_gain_in_rf_list
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_tpc_cali_upc_gain_in_rf_list(oal_int8* pac_upc_gain_in_rf_list)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_tpc_cali_upc_gain_in_rf_list, pac_upc_gain_in_rf_list);
}
#endif

/*****************************************************************************
 函 数 名  : hal_get_bcn_rate
 功能描述  : 获取某个vap的beacon datarate
 输入参数  : pst_hal_device, uc_vap_id
 输出参数  : puc_data_rate
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_bcn_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint8 *puc_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_bcn_rate, pst_hal_device, uc_vap_id, puc_data_rate);
}

/*****************************************************************************
 函 数 名  : hal_set_bcn_phy_tx_mode
 功能描述  : 设置beacon帧的txmode
 输入参数  : pst_hal_device, uc_tpc_code, uc_vap_id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_bcn_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_tpc_code, oal_uint8 uc_vap_id)

{
    HAL_PUBLIC_HOOK_FUNC3(_set_bcn_phy_tx_mode, pst_hal_device, uc_tpc_code, uc_vap_id);
}

/*****************************************************************************
 函 数 名  : hal_get_spec_frm_rate
 功能描述  : 获取spec frm帧的datarate
 输入参数  : pst_hal_device
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_spec_frm_rate, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_set_spec_frm_phy_tx_mode
 功能描述  : 设置spec frm帧的txmode
 输入参数  : pst_hal_device, uc_band, uc_2g_subband_idx, uc_5g_subband_idx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_band, oal_uint8 uc_subband_idx)

{
    HAL_PUBLIC_HOOK_FUNC3(_set_spec_frm_phy_tx_mode, pst_hal_device, uc_band, uc_subband_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_tpc_ctrl_reg_param
 功能描述  : 设置tpc 控制寄存器
 输入参数  : pst_hal_device, ul_tpc_ctrl_param
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param)

{
    HAL_PUBLIC_HOOK_FUNC2(_set_tpc_ctrl_reg_param, pst_hal_device, ul_tpc_ctrl_param);
}

/*****************************************************************************
 函 数 名  : hal_set_tpc_delay_reg_param
 功能描述  : 设置tpc延时寄存器
 输入参数  : pst_hal_device, ul_phy_tx_up_down_time_reg,ul_phy_rx_up_down_time_reg, paul_rf_reg_wr_delay
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2)

{
    HAL_PUBLIC_HOOK_FUNC5(_set_tpc_delay_reg_param, pst_hal_device, ul_phy_tx_up_down_time_reg,
                        ul_phy_rx_up_down_time_reg, ul_rf_reg_wr_delay1, ul_rf_reg_wr_delay2);
}

/*****************************************************************************
 函 数 名  : hal_get_tpc_delay_reg_param
 功能描述  : 读取tpc延时寄存器
 输入参数  : pst_hal_device, pul_phy_tx_up_down_time_reg,pul_phy_rx_up_down_time_reg, paul_rf_reg_wr_delay
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2)

{
    HAL_PUBLIC_HOOK_FUNC5(_get_tpc_delay_reg_param, pst_hal_device, pul_phy_tx_up_down_time_reg,
                        pul_phy_rx_up_down_time_reg, pul_rf_reg_wr_delay1, pul_rf_reg_wr_delay2);
}

/*****************************************************************************
 函 数 名  : hal_get_tpc_rf_reg_param
 功能描述  : 读取tpc RF寄存器配置
 输入参数  : pst_hal_device, ast_rf_reg_val, uc_chain_idx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
  oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
  oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx)

{
    HAL_PUBLIC_HOOK_FUNC7(_get_tpc_rf_reg_param, pst_hal_device, pus_dac_val, pus_pa_val,pus_lpf_val,paus_2g_upc_val
        ,paus_5g_upc_val, uc_chain_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_tpc_rf_reg_param
 功能描述  : 设置tpc RF寄存器
 输入参数  : pst_hal_device, ast_rf_reg_val, uc_chain_idx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
  oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
  oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx)

{
    HAL_PUBLIC_HOOK_FUNC7(_set_tpc_rf_reg_param, pst_hal_device, us_dac_val, us_pa_val,us_lpf_val,paus_2g_upc_val
        ,paus_5g_upc_val, uc_chain_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_tpc_phy_reg_param
 功能描述  : 设置phy档位寄存器
 输入参数  : pst_hal_device
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_tpc_phy_reg_param, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_get_2g_subband_index
 功能描述  : 获取2g信道对应的subband
 输入参数  : uc_channel_num
 输出参数  : puc_subband_idx
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : lm
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_subband_index, en_band, uc_channel_num, puc_subband_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_dpd_by_power
 功能描述  : 根据配置，针对不同的速率、不同的功率进行dpd配置
 输入参数  : pst_pow_params
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate, oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx)
{

    HAL_PUBLIC_HOOK_FUNC4(_set_dpd_by_power, pst_rate, uc_power_level, ul_dpd_configure, ul_rate_idx);
}

/*****************************************************************************
 函 数 名  : hal_set_upc_data
 功能描述  : 配置upc data的phy寄存器
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx)
{

    HAL_PUBLIC_HOOK_FUNC3(_set_upc_data, pst_hal_device, uc_band, uc_subband_idx);
}

#endif

/*****************************************************************************
 函 数 名  : hal_irq_affinity_init
 功能描述  : 中断和核绑定初始化
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_irq_affinity_init(hal_to_dmac_device_stru * pst_device, oal_uint32 ul_core_id)
{
    HAL_PUBLIC_HOOK_FUNC2(_irq_affinity_init, pst_device, ul_core_id);
}

#ifdef _PRE_WLAN_FEATURE_TXBF
/*****************************************************************************
 函 数 名  : hal_set_legacy_matrix_buf_pointer
 功能描述  : 设置legacy beamformee矩阵信息填充到内存的起始地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_legacy_matrix_buf_pointer, pst_hal_device, ul_matrix);
}
/*****************************************************************************
 函 数 名  : hal_get_legacy_matrix_buf_pointer
 功能描述  : 获取legacy beamformee矩阵信息填充到内存的起始地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_legacy_matrix_buf_pointer, pst_hal_device, pul_matrix);
}
/*****************************************************************************
 函 数 名  : hal_set_dl_mumimo_ctrl
 功能描述  : 设置MU-MIMO控制寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_dl_mumimo_ctrl, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_membership_status_63_32
 功能描述  : 设置MU-MIMO时，sta的group信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_membership_status_63_32, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_membership_status_31_0
 功能描述  : 设置MU-MIMO时，sta的group信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_membership_status_31_0, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_user_p_63_48
 功能描述  : 设置MU-MIMO时，sta的user position信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_63_48, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_user_p_47_32
 功能描述  : 设置MU-MIMO时，sta的user position信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_47_32, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_user_p_31_16
 功能描述  : 设置MU-MIMO时，sta的user position信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_31_16, pst_hal_device, ul_value);
}
/*****************************************************************************
 函 数 名  : hal_set_sta_user_p_15_0
 功能描述  : 设置MU-MIMO时，sta的user position信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_user_p_15_0, pst_hal_device, ul_value);
}

/*****************************************************************************
 函 数 名  : hal_set_vht_report_rate
 功能描述  : 设置VHT时，发送report帧的速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_vht_report_rate, pst_hal_device, ul_rate);
}
/*****************************************************************************
 函 数 名  : hal_set_vht_report_phy_mode
 功能描述  : 设置VHT时，发送report帧的phy mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_vht_report_phy_mode, pst_hal_device, ul_phy_mode);
}
/*****************************************************************************
 函 数 名  : hal_set_ndp_rate
 功能描述  : 设置VHT时，发送NDP帧的rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_rate, pst_hal_device, ul_rate);
}
/*****************************************************************************
 函 数 名  : hal_set_ndp_phy_mode
 功能描述  : 设置VHT时，发送NDP帧的phy mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_phy_mode, pst_hal_device, ul_phy_mode);
}
/*****************************************************************************
 函 数 名  : hal_set_ndp_max_time
 功能描述  : 设置VHT时，发送NDP帧的max txtime
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_max_time, pst_hal_device, uc_ndp_time);
}
/*****************************************************************************
 函 数 名  : hal_set_ndpa_duration
 功能描述  : 设置VHT时，发送NDPA帧的max txtime
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndpa_duration, pst_hal_device, ul_ndpa_duration);
}
/*****************************************************************************
 函 数 名  : hal_set_ndp_group_id
 功能描述  : 设置VHT时，发送NDP帧的GROUP ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_group_id)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_group_id, pst_hal_device, ul_group_id);
}
/*****************************************************************************
 函 数 名  : hal_set_ndp_partial_aid
 功能描述  : 设置VHT时，发送NDP帧的PARTIAL AID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ndp_partial_aid, pst_hal_device, us_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_phy_legacy_bf_en
 功能描述  : 设置PHY 使能cfg_lega_bf_en寄存器，表示在Legacy帧格式下做BeamformingH矩阵分解
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_legacy_bf_en, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_phy_txbf_legacy_en
 功能描述  : 设置PHY 使能TX_BEAMFORMING_LEGA寄存器，表示为Legacy数据部分做beamforming
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_txbf_legacy_en, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_phy_pilot_bf_en
 功能描述  : 设置PHY 使能LEGACY_Q_0_COL_I寄存器，表示为2STS->2TX场景下Legacy 数据部分I路数据对应的Q矩阵第0列做bf
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_phy_pilot_bf_en, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_ht_buffer_num
 功能描述  : 设置ht beamformee循环buffer单元个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_num, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_ht_buffer_step
 功能描述  : 设置ht beamformee循环buffer步长
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_step, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_ht_buffer_pointer
 功能描述  : 设置ht beamformee矩阵信息填充到内存的起始地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_ht_buffer_pointer, pst_hal_device, ul_reg_value);
}
/*****************************************************************************
 函 数 名  : hal_set_h_matrix_timeout
 功能描述  : 设置TXBF 矩阵超时寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_h_matrix_timeout, pst_hal_device, ul_reg_value);
}

/*****************************************************************************
 函 数 名  : hal_set_mu_aid_matrix_info
 功能描述  : 设置mu-mimo aid以及matrix地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_mu_aid_matrix_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_vap_id, oal_uint16 us_aid, oal_uint8  *p_matrix)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_mu_aid_matrix_info, pst_hal_device, uc_vap_id, us_aid, p_matrix);
}

/*****************************************************************************
 函 数 名  : hal_delete_txbf_lut_info
 功能描述  : 删除用户的TXBF INFO LUT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC2(_delete_txbf_lut_info, pst_hal_device, uc_lut_index);
}

/*****************************************************************************
 函 数 名  : hal_set_peer_lut_info
 功能描述  : 设置对端lut_info数据寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月20日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 auc_mac_addr[], oal_uint8 uc_lut_index)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_peer_lut_info, pst_hal_device, auc_mac_addr, uc_lut_index);
}
/*****************************************************************************
 函 数 名  : hal_set_txbf_lut_info
 功能描述  : 设置TXBF INFO LUT数据寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_txbf_lut_info, pst_hal_device, uc_lut_index, ul_reg_value);
}

/*****************************************************************************
 函 数 名  : hal_get_txbf_lut_info
 功能描述  : 读取TXBF INFO LUT数据寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : x
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC3(_get_txbf_lut_info, pst_hal_device, uc_lut_index, pst_reg_value);
}
#endif

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
/*****************************************************************************
 函 数 名  : hal_set_weak_intf_rssi_th
 功能描述  : 抗干扰下设置non-direct帧丢帧使能和rssi门限
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   :  222654
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_weak_intf_rssi_th, pst_hal_device, l_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_set_agc_unlock_min_th
 功能描述  : 抗干扰下设置agc unlock的tx/rx最小失锁门限
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月4日
    作    者   :  222654
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_agc_unlock_min_th, pst_hal_device, l_tx_reg_val, l_rx_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_set_nav_max_duration
 功能描述  : 抗干扰nav免疫设置接收duration最大值
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint16 us_obss_dur)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_nav_max_duration, pst_hal_device, us_bss_dur, us_obss_dur);
}
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
/*****************************************************************************
 函 数 名  : hal_set_counter1_clear
 功能描述  : EDCA优化特性下清空部分mac统计寄存器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月4日
    作    者   :  222654
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_counter1_clear(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_counter1_clear, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_get_txrx_frame_time
 功能描述  : EDCA优化特性下获取tx/rx frame的时间值
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月4日
    作    者   :  222654
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_txrx_frame_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val)
{
    /* hi1102_get_txrx_frame_time */
    HAL_PUBLIC_HOOK_FUNC2(_get_txrx_frame_time, pst_hal_device, ul_reg_val);
}

/*****************************************************************************
函 数 名  : hal_set_mac_clken
功能描述  : 配置mac_tx/rx_clken门控模式
输入参数  : pst_hal_device:  device指针;
            en_wctrl_enable: mac tx/rx时钟门控模式
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2015年8月17日
  作    者   : 
  修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_mac_clken, pst_hal_device, en_wctrl_enable);
}
#endif
/*****************************************************************************
 函 数 名  : hal_get_mac_statistics_data
 功能描述  : 获取mac关键统计信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年3月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_mac_statistics_data, pst_hal_device, pst_mac_key_statis);
}

#ifdef _PRE_WLAN_FEATURE_CCA_OPT
/*****************************************************************************
 函 数 名  : hal_get_ed_high_th
 功能描述  : CCA优化下获取cca的20/40M当前检测门限
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   :  229070
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *l_ed_high_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_ed_high_th, pst_hal_device, l_ed_high_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_set_cca_opt_stat
 功能描述  : 开启或关闭CCA统计中的时间统计
 输入参数  : pst_hal_device
             debug_val
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年5月26日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_cca_opt_stat(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 debug_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_cca_opt_stat, pst_hal_device, debug_val);
}

/*****************************************************************************
 函 数 名  : hal_set_ed_high_th
 功能描述  : CCA优化下设置cca的20/40M检测门限
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   :  229070
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_ed_high_th, pst_hal_device, l_ed_high_20_reg_val, l_ed_high_40_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_enable_sync_error_counter
 功能描述  : CCA优化特性下使能sync error统计寄存器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   :  229070
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_enable_sync_error_counter, pst_hal_device, l_enable_cnt_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_get_sync_error_cnt
 功能描述  : CCA优化特性下获取sync error的统计计数值
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   :  229070
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_sync_error_cnt, pst_hal_device, ul_reg_val);
}

/*****************************************************************************
 函 数 名  : hal_set_sync_err_counter_clear
 功能描述  : CCA优化特性下清空sync error统计寄存器
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   :  229070
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_sync_err_counter_clear, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_get_cca_reg_th
 功能描述  : CCA优化下获取cca的20/40M当前检测门限
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_cca_reg_th, pst_hal_device, ac_reg_val);
}

#endif


/*****************************************************************************
 函 数 名  : hal_set_soc_lpm
 功能描述  : 设置SOC节能开启和关闭
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_soc_lpm, pst_hal_device,en_type, uc_on_off,uc_pcie_idle);
}

/*****************************************************************************
 函 数 名  : hal_set_psm_status
 功能描述  : 设置PSM寄存器中节能状态位
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_status, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 函 数 名  : hal_set_psm_wakeup_mode
 功能描述  : 设置PSM寄存器中唤醒方式
 输入参数  : uc_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_psm_dtim_period, pst_hal_vap, uc_dtim_period, uc_listen_intvl_to_dtim_times, en_receive_dtim);
}


/*****************************************************************************
 函 数 名  : hal_set_psm_wakeup_mode
 功能描述  : 设置PSM寄存器中唤醒方式
 输入参数  : uc_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_wakeup_mode, pst_hal_device, uc_mode);
}

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
/*****************************************************************************
 函 数 名  : hal_set_smps_mode
 功能描述  : 设置SMPS的模式 0:disable,1:static,2:dynamic
 输入参数  : uc_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_smps_mode, pst_hal_device, uc_mode);
}

/*****************************************************************************
 函 数 名  : hal_get_smps_mode
 功能描述  : 设置SMPS的模式 0:disable,1:static,2:dynamic
 输入参数  : uc_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_smps_mode, pst_hal_device, pst_reg_value);
}

#endif

#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
/*****************************************************************************
 函 数 名  : hal_set_txop_ps_enable
 功能描述  : 设置TXOP PS寄存器中使能位
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_enable, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 函 数 名  : hal_set_txop_ps_condition1
 功能描述  : 设置PSM寄存器中condition1状态位
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_condition1, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 函 数 名  : hal_set_txop_ps_condition2
 功能描述  : 设置PSM寄存器中condition2状态位
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_condition2, pst_hal_device, uc_on_off);
}

/*****************************************************************************
 函 数 名  : hal_set_txop_ps_partial_aid
 功能描述  : 设置mac partial aid寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void  hal_set_txop_ps_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_partial_aid)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_txop_ps_partial_aid, pst_hal_device, us_partial_aid);
}

#endif
/*****************************************************************************
 函 数 名  : hal_set_wow_en_para
 功能描述  : 设置wow
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_wow_en, pst_hal_device, ul_set_bitmap, pst_para);
}

/*****************************************************************************
 函 数 名  : hal_set_wow_en_para
 功能描述  : 设置wow
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para)
{
    HAL_PUBLIC_HOOK_FUNC4(_set_lpm_state, pst_hal_device,uc_state_from,uc_state_to, pst_para);
}

/*****************************************************************************
 函 数 名  : hal_disable_machw_edca
 功能描述  : 去使能EDCA寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_machw_edca, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_enable_machw_edca
 功能描述  : 使能EDCA寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_machw_edca, pst_hal_device);
}


/*****************************************************************************
 函 数 名  : hal_set_abort
 功能描述  : 触发或者退出硬件abort
 输入参数  : uc_on_off
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_tx_abort_en, pst_hal_device, uc_abort_en);
}

/*****************************************************************************
 函 数 名  : hal_set_coex_ctrl
 功能描述  : 打开或关闭共存
 输入参数  : uc_coex_en
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_coex_ctrl, pst_hal_device, ul_mac_ctrl, ul_rf_ctrl);
}

/*****************************************************************************
 函 数 名  : hal_get_hw_version
 功能描述  : 获取80211g速率个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num)
{
    HAL_PUBLIC_HOOK_FUNC4(_get_hw_version, pst_hal_device, pul_hw_vsn, pul_hw_vsn_data, pul_hw_vsn_num);
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : hal_get_all_reg_value
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月1日
    作    者   : wowoo
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_all_reg_value, pst_hal_device);
}
#endif

/*****************************************************************************
 函 数 名  : hal_set_tx_dscr_field
 功能描述  : 设置发送描述符的 0级速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_tx_dscr_field, pst_hal_device, ul_data, en_sect);
}

/*****************************************************************************
 函 数 名  : hal_rf_test_disable_al_tx
 功能描述  : 禁用常发
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_rf_test_disable_al_tx, pst_hal_device);
}

/*****************************************************************************
 函 数 名  : hal_rf_test_enable_al_tx
 功能描述  : 使能常发
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    HAL_PUBLIC_HOOK_FUNC2(_rf_test_enable_al_tx, pst_hal_device, pst_tx_dscr);
}

#ifdef _PRE_WLAN_PHY_PLL_DIV
/*****************************************************************************
 函 数 名  : hal_rf_set_freq_skew_info
 功能描述  : 设置频偏
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC  OAL_INLINE oal_void hal_rf_set_freq_skew(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[])
{
    HAL_PUBLIC_HOOK_FUNC3(_rf_set_freq_skew, us_idx, us_chn, as_corr_data);
}
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 函 数 名  : hal_rf_adjust_ppm
 功能描述  : 设置ppm
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : pengdunmeng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_rf_adjust_ppm(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_ppm, wlan_channel_bandwidth_enum_uint8  en_bandwidth, oal_uint8 uc_clock)
{
    HAL_PUBLIC_HOOK_FUNC4(_rf_adjust_ppm, pst_hal_device, c_ppm, en_bandwidth, uc_clock);
}
#endif

/*****************************************************************************
 函 数 名  : hal_set_daq_mac_reg
 功能描述  : 设置数据采集时的MAC寄存器
 输入参数  : pst_hal_device--device指针, pul_addr --地址, us_unit_len--单元长度, us_unit_num--单元个数, us_depth--数据保存深度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_daq_mac_reg, pst_hal_device, pul_addr, us_unit_len, us_unit_num, us_depth);
}

/*****************************************************************************
 函 数 名  : hal_set_daq_phy_reg
 功能描述  : 设置数据采集时的PHY寄存器
 输入参数  : pst_hal_device--device指针, ul_reg_value --配置值,
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_daq_phy_reg, pst_hal_device, ul_reg_value);
}

/*****************************************************************************
 函 数 名  : hal_set_daq_en
 功能描述  : 使能或去使能数据采集
 输入参数  : pst_hal_device--device指针, uc_reg_value --配置值,
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_daq_en, pst_hal_device, uc_reg_value);
}

/*****************************************************************************
 函 数 名  : hal_get_daq_status
 功能描述  : 使能或去使能数据采集
 输入参数  : pst_hal_device--device指针, pul_reg_value --回读的状态值,
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_daq_status, pst_hal_device, pul_reg_value);
}

/*****************************************************************************
 函 数 名  : hal_set_beacon_timeout_val
 功能描述  : 设置beacon等待的超时值
 输入参数  : us_offset
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value)
{
    /* hi1102_set_beacon_timeout_val */
    HAL_PUBLIC_HOOK_FUNC2(_set_beacon_timeout_val, pst_hal_device, us_value);
}

/*****************************************************************************
 函 数 名  : hal_psm_clear_mac_rx_isr
 功能描述  : 低功耗唤醒后清除rx中断,防止rx中断里保留上一次睡前的值造成rx new
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_psm_clear_mac_rx_isr, pst_hal_device);
}
#ifdef _PRE_WLAN_HW_TEST
/*****************************************************************************
 函 数 名  : hal_set_dac_lfp_gain
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                                 oal_uint8 en_band,
                                                 oal_uint8 en_bandwidth,
                                                 oal_uint8 en_protocol_mode,
                                                 oal_uint8 en_rate)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_dac_lpf_gain, pst_hal_device, en_band, en_bandwidth, en_protocol_mode, en_rate);
}
#endif

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
/*****************************************************************************
 函 数 名  : hal_set_dac_lfp_gain
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                                 oal_uint8 en_band,
                                                 oal_uint8 en_bandwidth,
                                                 oal_uint8 en_protocol_mode,
                                                 oal_uint8 en_rate)
{
    HAL_PUBLIC_HOOK_FUNC5(_set_dac_lpf_gain, pst_hal_device, en_band, en_bandwidth, en_protocol_mode, en_rate);
}
#endif
/*****************************************************************************
 函 数 名  : hal_set_rx_filter
 功能描述  : 设置SMPS的模式 0:disable,1:static,2:dynamic
 输入参数  : uc_mode
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_rx_filter, pst_hal_device, ul_rx_filter_val);
}

/*****************************************************************************
 函 数 名  : hal_get_rx_filter
 功能描述  : 获取帧过滤寄存器值
 输入参数  : hal_to_dmac_device_stru *pst_hal_device

 输出参数  : oal_uint32* pst_reg_value
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_rx_filter, pst_hal_device, pst_reg_value);
}

#define HAL_VAP_LEVEL_FUNC
/*****************************************************************************
 函 数 名  : hal_vap_tsf_get_32bit
 功能描述  : 获取tsf低32位值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_tsf_get_32bit, pst_hal_vap, pul_tsf_lo);
}
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_tsf_set_32bit, pst_hal_vap, ul_tsf_lo);
}

/*****************************************************************************
 函 数 名  : hal_vap_tsf_get_64bit
 功能描述  : 获取整个tsf 64位值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_tsf_get_64bit, pst_hal_vap, pul_tsf_hi, pul_tsf_lo);
}
OAL_STATIC OAL_INLINE oal_void  hal_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_tsf_set_64bit, pst_hal_vap, ul_tsf_hi, ul_tsf_lo);
}

/*****************************************************************************
 函 数 名  : hal_vap_send_beacon_pkt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_send_beacon_pkt(hal_to_dmac_vap_stru        *pst_hal_vap,
                                                        hal_beacon_tx_params_stru   *pst_params)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_send_beacon_pkt, pst_hal_vap, pst_params);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_beacon_rate
 功能描述  : 设置beacon发送速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_beacon_rate(hal_to_dmac_vap_stru        *pst_hal_vap,
                                                                 oal_uint32 ul_beacon_rate)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_beacon_rate, pst_hal_vap, ul_beacon_rate);
}

/*****************************************************************************
 函 数 名  : hal_vap_beacon_suspend
 功能描述  : 挂起beacon帧发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_beacon_suspend, pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : hal_vap_beacon_resume
 功能描述  : 恢复beacon帧发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_beacon_resume, pst_hal_vap);
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 函 数 名  : hal_get_beacon_miss_status
 功能描述  : beaconmiss时打印相关寄存器的维测
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_beacon_miss_status(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_beacon_miss_status, pst_hal_device);
}
#endif

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_prot_params
 功能描述  : 设置RTS phy tx mode与data rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_prot_params, pst_hal_vap, pst_phy_tx_mode, pst_data_rate);
}



/*****************************************************************************
  10.2 对应一套硬件MAC VAP的静态内联函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_macaddr, pst_hal_vap, puc_mac_addr);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_opmode
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_opmode, pst_hal_vap, en_vap_mode);
}




/*****************************************************************************
 函 数 名  : hal_vap_clr_opmode
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode)
{
    /* 根据产品不同调用不同的HAL层接口 */
    /* Hi1102: hi1102_vap_clr_opmode */
    /* Hi1151: hi1151_vap_clr_opmode */
    HAL_PUBLIC_HOOK_FUNC2(_vap_clr_opmode, pst_hal_vap, en_vap_mode);
}


/*****************************************************************************
  hal vap EDCA参数配置相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_vap_set_machw_aifsn_all_ac
 功能描述  : 设置所有AC的仲裁帧间距(arbitration inter-frame space, AIFS)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo)
{
    HAL_PUBLIC_HOOK_FUNC5(_vap_set_machw_aifsn_all_ac, pst_hal_vap, uc_bk, uc_be, uc_vi, uc_vo);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_aifsn_ac
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                                           wlan_wme_ac_type_enum_uint8   en_ac,
                                                           oal_uint8                     uc_aifs)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_aifsn_ac, pst_hal_vap, en_ac, uc_aifs);
}

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_aifsn_ac_wfa(hal_to_dmac_vap_stru         *pst_hal_vap,
                                                           wlan_wme_ac_type_enum_uint8   en_ac,
                                                           oal_uint8                     uc_aifs,
                                                           wlan_wme_ac_type_enum_uint8   en_wfa_lock)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_set_machw_aifsn_ac_wfa, pst_hal_vap, en_ac, uc_aifs, en_wfa_lock);
}

OAL_STATIC OAL_INLINE oal_void  hal_vap_set_edca_machw_cw_wfa(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmaxmin, oal_uint8 uc_ec_type, wlan_wme_ac_type_enum_uint8   en_wfa_lock)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_set_edca_machw_cw_wfa, pst_hal_vap, uc_cwmaxmin, uc_ec_type, en_wfa_lock);
}
#endif

/*****************************************************************************
 函 数 名  : hal_vap_set_edca_machw_cw
 功能描述  : 设置BE、BK、VI、VO竞争窗口的上下限(CWmin, CWmax)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ec_type)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_set_edca_machw_cw, pst_hal_vap, uc_cwmax, uc_cwmin, uc_ec_type);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_edca_machw_cw
 功能描述  : 获取BE、BK、VI、VO竞争窗口的上下限(CWmin, CWmax)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ec_type)
{
    HAL_PUBLIC_HOOK_FUNC4(_vap_get_edca_machw_cw, pst_hal_vap, puc_cwmax, puc_cwmin, uc_ec_type);
}

#if 0
/*****************************************************************************
 函 数 名  : hal_vap_set_machw_cw_bk
 功能描述  : 设置BK竞争窗口的上下限(CWmin[BK], CWmax[BK])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_bk, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_cw_bk
 功能描述  : 获取BK竞争窗口的上下限(CWmin[BK], CWmax[BK])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_bk, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_cw_be
 功能描述  : 设置BE竞争窗口的上下限(CWmin[BE], CWmax[BE])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_be, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_cw_be
 功能描述  : 获取BE竞争窗口的上下限(CWmin[BE], CWmax[BE])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_be, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_cw_vi
 功能描述  : 设置VI竞争窗口的上下限(CWmin[VI], CWmax[VI])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_vi, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_cw_vi
 功能描述  : 获取VI竞争窗口的上下限(CWmin[VI], CWmax[VI])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_vi, pst_hal_vap, puc_cwmax, puc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_cw_vo
 功能描述  : 设置VO竞争窗口的上下限(CWmin[VO], CWmax[VO])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_cw_vo, pst_hal_vap, uc_cwmax, uc_cwmin);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_cw_vo
 功能描述  : 获取VO竞争窗口的上下限(CWmin[VO], CWmax[VO])
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_cw_vo, pst_hal_vap, puc_cwmax, puc_cwmin);
}
#endif

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_txop_limit_bkbe
 功能描述  : 设置BK、BE的TXOP上限(单位: 微秒)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_txop_limit_bkbe, pst_hal_vap, us_be, us_bk);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_txop_limit_bkbe
 功能描述  : 获取BK、BE的TXOP上限(单位: 微秒)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_txop_limit_bkbe, pst_hal_vap, pus_be, pus_bk);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_txop_limit_vivo
 功能描述  : 设置VI、VO的TXOP上限(单位: 微秒)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_txop_limit_vivo, pst_hal_vap, us_vo, us_vi);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_txop_limit_vivo
 功能描述  : 获取VI、VO的TXOP上限(单位: 微秒)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_txop_limit_vivo, pst_hal_vap, pus_vo, pus_vi);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_edca_bkbe_lifetime
 功能描述  : 设置BK、BE的生存时限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_edca_bkbe_lifetime, pst_hal_vap, us_be, us_bk);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_edca_bkbe_lifetime
 功能描述  : 获取BK、BE的生存时限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_edca_bkbe_lifetime, pst_hal_vap, pus_be, pus_bk);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_edca_vivo_lifetime
 功能描述  : 设置VI、VO的生存时限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_machw_edca_vivo_lifetime, pst_hal_vap, us_vo, us_vi);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_machw_edca_vivo_lifetime
 功能描述  : 获取VI、VO的生存时限
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_get_machw_edca_vivo_lifetime, pst_hal_vap, pus_vo, pus_vi);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_prng_seed_val_all_ac
 功能描述  : 为每一类AC分别设置探测种子
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_set_machw_prng_seed_val_all_ac, pst_hal_vap);
}


/*****************************************************************************
  hal vap TSF参数配置相关接口
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hal_vap_start_tsf
 功能描述  : 使能TBTT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_start_tsf, pst_hal_vap, en_dbac_enable);
}

/*****************************************************************************
 函 数 名  : hal_vap_read_tbtt_timer
 功能描述  : 读取TBTT计数器
 输入参数  : hal_to_dmac_vap_stru *pst_hal_vap
             oal_uint32 *pul_value
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value)
{
    /* 1102: hi1102_vap_read_tbtt_timer */
    /* 1151: hi1151_vap_read_tbtt_timer */
    HAL_PUBLIC_HOOK_FUNC2(_vap_read_tbtt_timer, pst_hal_vap, pul_value);
}
/*****************************************************************************
 函 数 名  : hal_vap_write_tbtt_timer
 功能描述  : 写入TBTT计数器
 输入参数  : hal_to_dmac_vap_stru *pst_hal_vap
             oal_uint32 ul_value
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value)
{
    /* 1102: hi1102_vap_write_tbtt_timer */
    /* 1151: hi1151_vap_write_tbtt_timer */
    HAL_PUBLIC_HOOK_FUNC2(_vap_write_tbtt_timer, pst_hal_vap, ul_value);
}


/*****************************************************************************
 函 数 名  : hal_vap_set_machw_tsf_disable
 功能描述  : 设置vap不产生TBTT中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_vap_set_machw_tsf_disable, pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_machw_beacon_period
 功能描述  : 设置vap的Beacon Period
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_set_machw_beacon_period, pst_hal_vap, us_beacon_period);
}

/*****************************************************************************
 函 数 名  : hal_vap_update_beacon_period
 功能描述  : 与hal_vap_set_machw_beacon_period的区别是只更新Beacon周期寄存器，不设置tsf
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period)
{
    /* 1102: hi1102_vap_update_beacon_period */
    /* 1151: hi1151_vap_update_beacon_period */
    HAL_PUBLIC_HOOK_FUNC2(_vap_update_beacon_period, pst_hal_vap, us_beacon_period);
}

/*****************************************************************************
 函 数 名  : hal_set_psm_listen_interval
 功能描述  : 设置PSM寄存器中listen_interval的值
 输入参数  : us_interval
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_listen_interval, pst_hal_vap, us_interval);
}
/*****************************************************************************
 函 数 名  : hal_set_psm_listen_interval_count
 功能描述  : 设置PSM寄存器中listen_interval_count的值
 输入参数  : us_interval
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_listen_interval_count, pst_hal_vap, us_interval_count);
}

/*****************************************************************************
 函 数 名  : hal_set_psm_listen_interval
 功能描述  : 设置PSM寄存器中listen_interval的值
 输入参数  : us_offset
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset)
{
    /* hi1102_set_psm_tbtt_offset */
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_tbtt_offset, pst_hal_vap, us_offset);
}

/*****************************************************************************
 函 数 名  : hal_set_psm_listen_interval
 功能描述  : 设置PSM寄存器中listen_interval的值
 输入参数  : us_offset
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset)
{
    /* hi1102_set_psm_ext_tbtt_offset */
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_ext_tbtt_offset, pst_hal_vap, us_offset);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_beacon_period
 功能描述  : 读取beacon周期寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period)
{
    /* hi1102_set_psm_beacon_period */
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_beacon_period, pst_hal_vap, ul_beacon_period);
}
/*****************************************************************************
 函 数 名  : hal_vap_get_beacon_period
 功能描述  : 读取beacon周期寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_tsf_ctrl, pst_hal_vap, ul_tsf_ctrl_val);
}

/*****************************************************************************
 函 数 名  : hal_vap_get_beacon_period
 功能描述  : 读取beacon周期寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_get_beacon_period, pst_hal_vap, pul_beacon_period);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_noa
 功能描述  : 设置NoA寄存器
 输入参数  : pst_hal_vap: hal vap
             ul_start_tsf: start tsf
             ul_duration : absent时长, 单位us
             ul_interval : noa周期, 单位us
             uc_count    : 个数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count)
{
    HAL_PUBLIC_HOOK_FUNC5(_vap_set_noa, pst_hal_vap, ul_start_tsf, ul_duration, ul_interval, uc_count);
}

/*****************************************************************************
 函 数 名  : hal_sta_tsf_save
 功能描述  : 设置启动对应VAP的外置TSF
 输入参数  : pst_hal_vap: hal vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_sta_tsf_save(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_need_restore)
{
    /* 根据产品不同调用不同的HAL层接口 */
    /* Hi1102: hi1102_sta_tsf_save */
    /* Hi1151: hi1151_sta_tsf_save */
    HAL_PUBLIC_HOOK_FUNC2(_sta_tsf_save, pst_hal_vap, en_need_restore);
}

/*****************************************************************************
 函 数 名  : hal_sta_tsf_restore
 功能描述  : 设置停止对应VAP的外置TSF
 输入参数  : pst_hal_vap: hal vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_sta_tsf_restore(hal_to_dmac_vap_stru *pst_hal_vap)
{
    /* 根据产品不同调用不同的HAL层接口 */
    /* Hi1102: hi1102_sta_tsf_restore */
    /* Hi1151: hi1151_sta_tsf_restore */
    HAL_PUBLIC_HOOK_FUNC1(_sta_tsf_restore, pst_hal_vap);
}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : hal_vap_set_ops
 功能描述  : 设置P2P OPS寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window)
{
    HAL_PUBLIC_HOOK_FUNC3(_vap_set_ops, pst_hal_vap, en_ops_ctrl, uc_ct_window);
}

/*****************************************************************************
 函 数 名  : hal_vap_set_p2p_absent_suspend
 功能描述  : 设置NoA寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_bool_enum_uint8     en_suspend_enable)
{
    HAL_PUBLIC_HOOK_FUNC2(_vap_enable_p2p_absent_suspend, pst_hal_vap, en_suspend_enable);
}

#endif
/* beacon hal相关接口 原型声明 */
OAL_STATIC OAL_INLINE oal_void hal_tx_complete_update_rate(hal_tx_dscr_ctrl_one_param *pst_tx_dscr_param)
{
    oal_uint8       uc_retry;

    uc_retry = pst_tx_dscr_param->uc_long_retry + pst_tx_dscr_param->uc_short_retry;

    if (uc_retry <= pst_tx_dscr_param->ast_per_rate[0].rate_bit_stru.bit_tx_count) /* 本次使用第1种速率 */
    {
        pst_tx_dscr_param->uc_last_rate_rank = 0;
    }
    else
    {
        uc_retry -= pst_tx_dscr_param->ast_per_rate[0].rate_bit_stru.bit_tx_count;
        if(uc_retry <= pst_tx_dscr_param->ast_per_rate[1].rate_bit_stru.bit_tx_count) /* 本次使用第2种速率 */
        {
            pst_tx_dscr_param->uc_last_rate_rank = 1;
        }
        else
        {
            uc_retry -= pst_tx_dscr_param->ast_per_rate[1].rate_bit_stru.bit_tx_count;
            if(uc_retry <= pst_tx_dscr_param->ast_per_rate[2].rate_bit_stru.bit_tx_count)
            {
                pst_tx_dscr_param->uc_last_rate_rank = 2;
            }
            else
            {
                uc_retry -= pst_tx_dscr_param->ast_per_rate[2].rate_bit_stru.bit_tx_count;
                pst_tx_dscr_param->uc_last_rate_rank = 3;
            }
        }
    }

    pst_tx_dscr_param->ast_per_rate[pst_tx_dscr_param->uc_last_rate_rank].rate_bit_stru.bit_tx_count = uc_retry;

}


/*****************************************************************************
 函 数 名  : hal_get_random_byte
 功能描述  : 从硬件寄存器获取随即byte
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : wep加密获取随机数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hal_get_random_byte(oal_uint8 *puc_byte)
{
    /* wep加密 */
    *puc_byte = oal_get_random();
}
/*****************************************************************************
 函 数 名  : hal_set_sta_bssid
 功能描述  : 设置BSSID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_bssid, pst_hal_vap, puc_byte);
}

/*****************************************************************************
 函 数 名  : hal_set_sta_dtim_period
 功能描述  : 设置DTIM寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_dtim_period, pst_hal_vap, ul_dtim_period);
}
/*****************************************************************************
 函 数 名  : hal_get_sta_dtim_period
 功能描述  : 设置DTIM寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_sta_dtim_period, pst_hal_vap, pul_dtim_period);
}

/*****************************************************************************
 函 数 名  : hal_set_sta_dtim_count
 功能描述  : 设置ditm count寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_sta_dtim_count, pst_hal_vap, ul_dtim_count);
}
/*****************************************************************************
 函 数 名  : hal_get_psm_dtim_count
 功能描述  : 获取ditm count寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_dtim_count)
{
    /* hi1102_get_psm_dtim_count */
    HAL_PUBLIC_HOOK_FUNC2(_get_psm_dtim_count, pst_hal_vap, puc_dtim_count);
}

/*****************************************************************************
 函 数 名  : hal_get_psm_dtim_count
 功能描述  : 获取ditm count寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count)
{
    HAL_PUBLIC_HOOK_FUNC2(_set_psm_dtim_count, pst_hal_vap, uc_dtim_count);
}

/*****************************************************************************
 函 数 名  : hal_pm_wlan_servid_register
 功能描述  : wlan service 注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_pm_wlan_servid_register(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_ret)
{
    HAL_PUBLIC_HOOK_FUNC2(_pm_wlan_servid_register, pst_hal_vap, pul_ret);
}
/*****************************************************************************
 函 数 名  : hal_pm_wlan_servid_unregister
 功能描述  : wlan service 注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_pm_wlan_servid_unregister(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_pm_wlan_servid_unregister, pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : hal_enable_sta_tsf_tbtt
 功能描述  : 使能tbtt中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_enable_sta_tsf_tbtt, pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : hal_disable_sta_tsf_tbtt
 功能描述  : 关闭sta tsf tbtt中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap)
{
    HAL_PUBLIC_HOOK_FUNC1(_disable_sta_tsf_tbtt, pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : hal_cfg_slottime_type
 功能描述  : 配置long/short slottime
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hal_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_cfg_slottime_type, pst_hal_device, ul_slottime_type);
}

/*****************************************************************************
  10.4 SDT读写寄存器函数
*****************************************************************************/

/*****************************************************************************
    芯片加密类型和协议加密类型互相转换
*****************************************************************************/

/*****************************************************************************
 函 数 名  : hal_cipher_suite_to_ctype
 功能描述  : 将802.11 协议中的加密套件数值转换为witp硬件对应加密方式的数值。
 输入参数  : oal_uint8 uc_cipher_suite
 输出参数  : 无
 返 回 值  : hal_ciper_protocol_type_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE hal_cipher_protocol_type_enum_uint8 hal_cipher_suite_to_ctype(wlan_ciper_protocol_type_enum_uint8 en_cipher_suite)
{
    /********************************************************************
    *  加密方式      软件加密方式对应数据值        硬件发送描述符对应数值
    *  User Grp                 0
    *   WEP-40                  1                           0
    *   TKIP                    2                           1
    *   RES                     3
    *   CCMP                    4                           2
    *   WEP-104                 5                           4
    *   BIP                     6                           5
    *   对应不加密，设置硬件发送描述符bit3~0 为             3
    ********************************************************************/

    hal_cipher_protocol_type_enum_uint8 en_ciper_type = HAL_NO_ENCRYP;

    switch(en_cipher_suite)
    {
        case WLAN_80211_CIPHER_SUITE_WEP_40:
            en_ciper_type = HAL_WEP40;
            break;
        case WLAN_80211_CIPHER_SUITE_TKIP:
            en_ciper_type = HAL_TKIP;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            en_ciper_type = HAL_CCMP;
            break;
        case WLAN_80211_CIPHER_SUITE_WEP_104:
            en_ciper_type = HAL_WEP104;
            break;
        case WLAN_80211_CIPHER_SUITE_BIP:
            en_ciper_type = HAL_BIP;
            break;
        default:
            en_ciper_type = HAL_NO_ENCRYP;
            break;
    }
    return en_ciper_type;
}

/*****************************************************************************
 函 数 名  : hal_ctype_to_cipher_suite
 功能描述  : 将witp硬件对应加密方式的数值转换为802.11 协议中的加密套件数值。
 输入参数  : hal_ciper_protocol_type_enum_uint8 en_cipher_type
 输出参数  : 无
 返 回 值  : wlan_ciper_protocol_type_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE  wlan_ciper_protocol_type_enum_uint8 hal_ctype_to_cipher_suite(hal_cipher_protocol_type_enum_uint8 en_cipher_type)
{
    /********************************************************************
    *  加密方式      软件加密方式对应数据值        硬件发送描述符对应数值
    *  User Grp                 0
    *   WEP-40                  1                           0
    *   TKIP                    2                           1
    *   RES                     3
    *   CCMP                    4                           2
    *   WEP-104                 5                           4
    *   BIP                     6                           5
    *   对应不加密，设置硬件发送描述符bit3~0 为             3
    ********************************************************************/

    wlan_ciper_protocol_type_enum_uint8 en_ciper_suite = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    switch(en_cipher_type)
    {
        case HAL_WEP40:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_WEP_40;
            break;
        case HAL_TKIP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_TKIP;
            break;
        case HAL_CCMP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_CCMP;
            break;
        case HAL_WEP104:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_WEP_104;
            break;
        case HAL_BIP:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_BIP;
            break;
        default:
            en_ciper_suite = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
            break;
    }
    return en_ciper_suite;
}

/*****************************************************************************
 函 数 名  : hal_mwo_det_enable_mac_counter
 功能描述  : 检测到微波炉存在使能MAC计数
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_void hal_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val)
{
    HAL_PUBLIC_HOOK_FUNC2(_mwo_det_enable_mac_counter, pst_hal_device, l_enable_reg_val);
}

OAL_STATIC OAL_INLINE oal_void hal_rx_dscr_opt_reset_normal(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_rx_dscr_opt_reset_normal, pst_hal_device);
}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC OAL_INLINE oal_void hal_coex_sw_irq_set(oal_uint8 uc_irq_en)
{
    HAL_PUBLIC_HOOK_FUNC1(_coex_sw_irq_set, uc_irq_en);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_abort_qos_null_seq_num(oal_uint32 *ul_qosnull_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_abort_qos_null_seq_num, ul_qosnull_seq_num);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_occupied_period(oal_uint16 *ul_occupied_period)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_occupied_period, ul_occupied_period);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_pa_status(oal_uint32 *ul_pa_status)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_pa_status, ul_pa_status);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_null_buff_addr(oal_uint32 ul_abort_null_buff_addr)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_null_buff_addr, ul_abort_null_buff_addr);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_abort_qos_null_seq_num(oal_uint32 ul_qosnull_seq_num)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_abort_qos_null_seq_num, ul_qosnull_seq_num);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_hw_rx_priority_dis(oal_uint8 uc_hw_rx_prio_dis)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_hw_rx_priority_dis, uc_hw_rx_prio_dis);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_hw_priority_en(oal_uint8 uc_hw_prio_en)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_hw_priority_en, uc_hw_prio_en);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_get_rf_control(oal_uint16 ul_occupied_period, oal_uint32 *pul_wlbt_mode_sel, oal_uint16 us_wait_cnt)
{
    HAL_PUBLIC_HOOK_FUNC3(_btcoex_get_rf_control, ul_occupied_period, pul_wlbt_mode_sel, us_wait_cnt);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_occupied_period(oal_uint16 ul_occupied_period)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_occupied_period, ul_occupied_period);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_sw_all_abort_ctrl(oal_uint8 uc_sw_abort_ctrl)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_sw_all_abort_ctrl, uc_sw_abort_ctrl);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_sw_priority_flag(oal_uint8 uc_sw_prio_flag)
{
    HAL_PUBLIC_HOOK_FUNC1(_set_btcoex_sw_priority_flag, uc_sw_prio_flag);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_soc_gpreg0(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_btcoex_soc_gpreg0, uc_val, us_mask, uc_offset);
}
OAL_STATIC OAL_INLINE oal_void hal_set_btcoex_soc_gpreg1(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset)
{
    HAL_PUBLIC_HOOK_FUNC3(_set_btcoex_soc_gpreg1, uc_val, us_mask, uc_offset);
}
OAL_STATIC OAL_INLINE oal_void hal_update_btcoex_btble_status(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_update_btcoex_btble_status, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_init(oal_void *p_arg)
{
    HAL_PUBLIC_HOOK_FUNC1(_btcoex_init, p_arg);
}
OAL_STATIC OAL_INLINE oal_void hal_get_btcoex_statistic(oal_bool_enum_uint8 en_enable_abort_stat)
{
    HAL_PUBLIC_HOOK_FUNC1(_get_btcoex_statistic, en_enable_abort_stat);
}
OAL_STATIC OAL_INLINE oal_void hal_mpw_soc_write_reg(oal_uint32 ulQuryRegAddrTemp, oal_uint16 usQuryRegValueTemp)
{
    HAL_PUBLIC_HOOK_FUNC2(_mpw_soc_write_reg, ulQuryRegAddrTemp, usQuryRegValueTemp);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_update_ap_beacon_count(oal_uint32 *pul_beacon_count)
{
    HAL_PUBLIC_HOOK_FUNC1(_btcoex_update_ap_beacon_count, pul_beacon_count);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_post_event(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_sub_type)
{
    HAL_PUBLIC_HOOK_FUNC2(_btcoex_post_event, pst_hal_device, uc_sub_type);
}
OAL_STATIC OAL_INLINE oal_void hal_btcoex_process_bt_status(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_btcoex_process_bt_status, pst_hal_device);

}

#ifdef _PRE_WLAN_FEATURE_LTECOEX
OAL_STATIC OAL_INLINE oal_void hal_ltecoex_req_mask_ctrl(oal_uint16 lte_req_mask)
{
    HAL_PUBLIC_HOOK_FUNC1(_ltecoex_req_mask_ctrl, lte_req_mask);
}
#endif

#endif
OAL_STATIC OAL_INLINE oal_void hal_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_key_id)
{
    HAL_PUBLIC_HOOK_FUNC5(_tx_get_dscr_iv_word, pst_dscr, pul_iv_ms_word, pul_iv_ls_word, uc_chiper_type, uc_chiper_key_id);
}
OAL_STATIC  OAL_INLINE oal_void hal_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status)
{
    HAL_PUBLIC_HOOK_FUNC2(_get_hw_status, pst_hal_device, ul_cali_check_hw_status);
}

#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC OAL_INLINE oal_void hal_dft_get_machw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_machw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len)
{
    HAL_PUBLIC_HOOK_FUNC4(_dft_get_machw_stat_info, pst_hal_device, pul_machw_stat,us_bank_select, pul_len);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_set_phy_stat_node(hal_to_dmac_device_stru *pst_hal_device,oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    HAL_PUBLIC_HOOK_FUNC2(_dft_set_phy_stat_node, pst_hal_device, pst_phy_node_idx);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_get_phyhw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_phyhw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len)
{
    HAL_PUBLIC_HOOK_FUNC4(_dft_get_phyhw_stat_info, pst_hal_device, pul_phyhw_stat, us_bank_select, pul_len);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_get_rfhw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_rfhw_stat, oal_uint32 *pul_len)
{
    HAL_PUBLIC_HOOK_FUNC3(_dft_get_rfhw_stat_info, pst_hal_device, pul_rfhw_stat, pul_len);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_get_sochw_stat_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint16* pus_sochw_stat, oal_uint32 *pul_len)
{
    HAL_PUBLIC_HOOK_FUNC3(_dft_get_sochw_stat_info, pst_hal_device, pus_sochw_stat, pul_len);
}

OAL_STATIC OAL_INLINE oal_void hal_dft_print_machw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_machw_stat, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_print_phyhw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_phyhw_stat, pst_hal_device);
}
OAL_STATIC OAL_INLINE oal_void hal_dft_print_rfhw_stat(hal_to_dmac_device_stru *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_print_rfhw_stat, pst_hal_device);
}

OAL_STATIC OAL_INLINE oal_void  hal_dft_report_all_reg_state(hal_to_dmac_device_stru   *pst_hal_device)
{
    HAL_PUBLIC_HOOK_FUNC1(_dft_report_all_reg_state, pst_hal_device);
}
#endif
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC OAL_INLINE oal_void  hal_set_lte_gpio_mode(oal_uint32 ul_mode_value)
{

    HAL_PUBLIC_HOOK_FUNC1(_set_lte_gpio_mode,ul_mode_value);
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hal_ext_if.h */
