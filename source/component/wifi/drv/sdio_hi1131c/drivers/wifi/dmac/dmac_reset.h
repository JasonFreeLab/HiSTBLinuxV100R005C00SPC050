/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_reset.h
  版 本 号   : 初稿
  作    者   :  52447
  生成日期   : 2013年11月6日
  最近修改   :
  功能描述   : dmac_reset.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年11月6日
    作    者   :  52447
    修改内容   : 创建文件
******************************************************************************/

#ifndef __DMAC_RESET_H__
#define __DMAC_RESET_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_kernel_file.h"
#include "mac_device.h"
#include "dmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RESET_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WLAN_BA_LUT_ENTRY_SIZE               3             /*MAC BA LUT表项每个条目的大小，以4字节为单位*/

#define DMAC_RESET_NOT_REG   0
#define DMAC_RESET_REG       1

#define DMAC_TIME_USEC_INT64(_pst_time) \
    ((oal_int64)((_pst_time)->i_sec) * 1000000 + (_pst_time)->i_usec)

#define DMAC_TIME_USEC_DIFF(_pst_time1, _pst_time2)    \
    (DMAC_TIME_USEC_INT64(_pst_time2)- DMAC_TIME_USEC_INT64(_pst_time1))

#define DMAC_RESET_DUMP_LUT_PATH "/tmp/reset_dump_lut.txt"

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef struct
{
   oal_uint32    bit_seq_lut_reset      :1    ,
                 bit_ba_lut_reset       :1    ,
                 bit_pn_lut_reset       :1    ,
                 bit_key_lut_reset      :1    ,
                 bit_txbf_lut_reset     :1    ,
                 bit_smartant_lut_reset :1    ,
                 bit_peer_addr_lut_reset:1    ,
                 bit_save_tx_fake_fifo  :1    ,
                 bit_rsv                :25   ;

   oal_uint32   *pst_sequence_qos ;
   oal_uint32   *pst_ba_rx        ;
   oal_uint32   *pst_tsf          ;

   /*单播PN lut表，每条目8字节*/
   oal_uint32   *pst_rx_pn_ucast  ;
   oal_uint32   *pst_tx_pn_ucast  ;

   /* 接收方向,STA最大关联2个AP,每个AP 8个tid，组播RX PN有2*8个条目,每条目8字节*/
   oal_uint32   *pst_rx_pn_mcast ;

   /* 发送方向,最大4个业务VAP,STA不会发组播加密帧。组播TX PN有4个条目，每条目8字节 */
   oal_uint32   *pst_tx_pn_mcast ;

   oal_uint32   *pst_txbf ;

   oal_netbuf_stru *pst_fake_queue;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
   oal_file     *pst_debug_file;
   oal_mm_segment_t    old_fs;
#endif
}dmac_reset_mng_stru;

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
extern oal_uint32  dmac_reset_hw(mac_device_stru* pst_device,oal_uint8* pst_param);
extern oal_void dmac_reset_debug_all(mac_device_stru* pst_device,dmac_reset_para_stru* pst_debug_para);
extern oal_void dmac_reset_init(oal_void);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 dmac_reset_sys_event(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif
extern  oal_void dmac_reset_rx_dscr_queue_flush(hal_to_dmac_device_stru* pst_hal);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_reset.h */
