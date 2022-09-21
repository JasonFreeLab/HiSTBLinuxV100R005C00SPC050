/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : dmac_data_acq.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年4月22日
  最近修改   :
  功能描述   : dmac_data_acq.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月22日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_DATA_ACQ_H__
#define __DMAC_DATA_ACQ_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_mem.h"
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "frw_ext_if.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "hal_witp_rf.h"
#include "oal_net.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DATA_ACQ_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_DATA_ACQ_MAX_UNITLEN 65528
#define DMAC_DATA_ACQ_MAX_UNITNUM 65535
#define DMAC_DATA_ACQ_MAX_LEN     (1024 * 4096)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/********************* 配置命令含义 *********************/
typedef enum
{
    DMAC_DATA_ACQ_PRE      = 0,       /* 数据采集准备配置 MAC寄存器 */
    DMAC_DATA_ACQ_COND     = 1,       /* 数据采集控制条件 PHY寄存器 */
    DMAC_DATA_ACQ_ENABLE   = 2,       /*       数据采集使能标志     */
    DMAC_DATA_ACQ_STATUS   = 3,       /*    数据采集完成状态查询    */
    DMAC_DATA_ACQ_RECODE   = 4,       /*    数据采集完成获取数据    */

    DMAC_DATA_ACQ_BUTT
} dmac_data_acq_enum;
typedef oal_uint8 dmac_data_acq_enum_uint8;

/********************* 采集条件定义 *********************/
typedef enum
{
    DMAC_DATA_ACQ_COND_ADC_TH     = 1,  /* ADC门限限定 */
    DMAC_DATA_ACQ_COND_AGC_BH     = 2,  /*   AGC饱和   */
    DMAC_DATA_ACQ_COND_AGC_LOCK   = 4,  /*   AGC锁定   */
    DMAC_DATA_ACQ_COND_PACK_L     = 8,  /*  包检测有效 */

    DMAC_DATA_ACQ_COND_BUTT       = 16
} dmac_data_acq_cond_enum;
typedef oal_uint8 dmac_data_acq_cond_enum_uint8;

/********************* BIT位选定义 *********************/
typedef enum
{
    DMAC_DATA_ACQ_BIT_0_7          = 0,  /* 采集[7:0]bits ADC 输出，含饱和操作 */
    DMAC_DATA_ACQ_BIT_1_8          = 1,  /* 采集[8:1]bits ADC 输出，含饱和操作 */
    DMAC_DATA_ACQ_BIT_2_9          = 2,  /* 采集[9:2]bits ADC 输出，含饱和操作 */

    DMAC_DATA_ACQ_BIT_BUTT
} dmac_data_acq_bit_enum;
typedef oal_uint8 dmac_data_acq_bit_enum_uint8;

/********************* 数据采集状态 *********************/
typedef enum
{
    DMAC_DATA_ACQ_STATUS_INIT            = 0,  /*       初始化状态      */
    DMAC_DATA_ACQ_STATUS_MAC_REG         = 1,  /* 处于配置MAC寄存器状态 */
    DMAC_DATA_ACQ_STATUS_PHY_REG         = 2,  /* 处于配置PHY寄存器状态 */
    DMAC_DATA_ACQ_STATUS_ENABLE          = 3,  /*    处于数据采集状态   */
    DMAC_DATA_ACQ_STATUS_COMPLETE        = 4,  /*  处于数据采集完成状态 */

    DMAC_DATA_ACQ_STATUS_BUTT
} dmac_data_acq_status_enum;
typedef oal_uint8 dmac_data_acq_status_enum_uint8;

/********************* 数据采集状态 *********************/
typedef enum
{
    DMAC_DATA_ACQ_SEND_TYPE_INFO         = 0,  /* 发送至APP的数据采集信息 */
    DMAC_DATA_ACQ_SEND_TYPE_UNIT         = 1,  /*    发送至APP的数据单元  */
    DMAC_DATA_ACQ_SEND_TYPE_READY        = 2,  /*   APP侧可以接收数据，Driver继续发送  */
    DMAC_DATA_ACQ_SEND_TYPE_FAIL         = 3,  /*   APP侧可以接收数据，Driver继续发送  */
    DMAC_DATA_ACQ_SEND_TYPE_ACK          = 4,  /*   APP侧可以接收数据，Driver继续发送  */

    DMAC_DATA_ACQ_SEND_TYPE_BUTT
} dmac_data_acq_send_type_enum;
typedef oal_uint8 dmac_data_acq_send_type_enum_uint8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint8  *g_puc_daq_mem_addr;


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* PHY寄存器对应数据采集条件寄存器结构体 */
typedef struct
{
    oal_uint32   bit_cfg_real_sample_bits_sel      :   2,    /*   bit位选择   */
                 bit_cfg_real_sample_data_th       :   9,    /*    ADC门限    */
                 bit_reserved                      :   5,    /*     保留      */
                 bit_cfg_real_sample_cond_ctrl     :   4,    /*   数采条件    */
                 bit_cfg_real_sample_ch_sel        :   2,    /*   通道选择    */
                 bit_cfg_real_sample_en            :   1,    /*   使能标志    */
                 bit_reserved1                     :   9;    /*     保留      */
}dmac_data_acq_cond_stru;

/* MAC相关数据采集寄存器结构体 */
typedef struct
{
    oal_uint8                *puc_start_addr;    /*   起始地址   */
    oal_bool_enum_uint8       en_daq_enable;     /* 是否使能数采 */
    oal_uint8                 uc_resv[1];
    oal_uint16                us_num;            /* 采集单元个数 */
    oal_uint16                us_depth;          /*   采集深度   */
    oal_uint16                us_len_unit;       /* 采集单元长度 */
}dmac_data_acq_prep_stru;

typedef struct
{
    oal_workqueue_stru                      *daq_rx_workqueue;
    oal_work_stru                            rx_daq_work;
    oal_netbuf_head_stru                     rx_daq_dbg_seq;
}dmac_data_acq_workqueue_stru;

/* 数据采集配置结构体 */
typedef struct
{
    dmac_data_acq_status_enum_uint8       en_daq_status;         /*   当前是否允许使能数据采集功能    */
    oal_bool_enum_uint8                   en_daq_apprecv_ready;  /*   当前APP是否允许继续上传数据  */
    oal_bool_enum_uint8                   uc_ack_flag;           /*          ack确认标志           */
    oal_bool_enum_uint8                   en_daq_app_error;      /*            app异常             */
    oal_uint32                            ul_length;             /*       深度 * 大小 <= 4M      */
    oal_uint32                            ul_daq_sn;             /*            数据序号            */
    dmac_data_acq_workqueue_stru          st_daq_workqueue;
    dmac_data_acq_cond_stru               st_daq_cond;
    dmac_data_acq_prep_stru               st_daq_prep_info;
}dmac_data_acq_stru;

/* 数采上报app的结构体 */
typedef struct
{
    oal_uint32      ul_daq_addr;         /* 数采数据首地址 */
    oal_uint32      ul_data_len;         /* 数采数据总的长度 */
    oal_uint32      ul_unit_len;         /* 单元数据的最大长度:不包含(daq_unit_head)头长度 */
}dmac_data_acq_info_stru;

/* 数采单元头结构体 */
typedef struct
{
    dmac_data_acq_send_type_enum_uint8  en_send_type;        /* 数采单元数据序列号 */
    oal_uint8                           uc_resv[3];
    oal_uint32                          ul_msg_sn;           /* 数采单元数据序列号 */
    oal_uint32                          ul_data_len;         /* 当前单元长度 */
}dmac_data_acq_data_head_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern dmac_data_acq_stru g_st_data_acq;

extern oal_uint32  dmac_config_data_acq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  dmac_data_acq_init(oal_void);
extern oal_uint32  dmac_data_acq_exit(oal_void);


#endif  /* end of _PRE_WLAN_FEATURE_DAQ */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_data_acq.h */
