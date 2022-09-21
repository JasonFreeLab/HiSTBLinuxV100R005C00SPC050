/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_config.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年11月6日
  最近修改   :
  功能描述   : wal_config.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月6日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_CONFIG_H__
#define __WAL_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "frw_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_CONFIG_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef oal_uint32  (*wal_config_get_func)(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
typedef oal_uint32  (*wal_config_set_func)(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

/* 填写配置消息头 */
#define WAL_CFG_MSG_HDR_INIT(_pst_cfg_msg_hdr, _en_type, _us_len, _uc_sn) \
    do                                                      \
    {                                                       \
        (_pst_cfg_msg_hdr)->en_msg_type = (_en_type);       \
        (_pst_cfg_msg_hdr)->us_msg_len  = (_us_len);        \
        (_pst_cfg_msg_hdr)->uc_msg_sn   = (_uc_sn);         \
    } while(0)

/* 填写write msg消息头 */
#define WAL_WRITE_MSG_HDR_INIT(_pst_write_msg, _en_wid, _us_len) \
    do                                                      \
    {                                                       \
        (_pst_write_msg)->en_wid = (_en_wid);               \
        (_pst_write_msg)->us_len = (_us_len);               \
    } while(0)

/* 获取msg序列号宏 */
extern oal_atomic g_wal_config_seq_num;
#define WAL_GET_MSG_SN()     (oal_atomic_inc_return(&g_wal_config_seq_num))

#define WAL_MSG_WRITE_MSG_HDR_LENGTH   (OAL_SIZEOF(wal_msg_hdr_stru))

#define WAL_MSG_WRITE_MAX_LEN   (WLAN_MEM_EVENT_SIZE2 - FRW_EVENT_HDR_LEN - FRW_IPC_MSG_HEADER_LENGTH - WAL_MSG_WRITE_MSG_HDR_LENGTH)

#define WAL_ALWAYS_TX_PACK_LEN  (4000 - 28) /* 1024 */
#define WAL_BCAST_MAC_ADDR       255
#define WAL_MAX_RATE_NUM        16

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 配置消息类型 */
typedef enum
{
    WAL_MSG_TYPE_QUERY,     /* 查询 */
    WAL_MSG_TYPE_WRITE,     /* 设置 */
    WAL_MSG_TYPE_RESPONSE,  /* 返回 */

    WAL_MSG_TYPE_BUTT
}wal_msg_type_enum;
typedef oal_uint8 wal_msg_type_enum_uint8;


/* 速率集种类，常发使用 */
typedef enum
{
    WAL_RF_TEST_11B_LEGACY_RATES,
    WAL_RF_TEST_20M_NORMAL_RATES,
    WAL_RF_TEST_20M_SHORT_GI_RATES,
    WAL_RF_TEST_40M_NORMAL_RATES,
    WAL_RF_TEST_40M_SHORT_GI_RATES,

    WAL_RF_TEST_RATES_BUTT
} wal_rf_test_enum;
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
/* 配置消息头 */
typedef struct
{
    wal_msg_type_enum_uint8     en_msg_type;       /* msg type:W or Q */
    oal_uint8                   uc_msg_sn;         /* msg 序列号 */
    oal_uint16                  us_msg_len;        /* msg 长度 */
}wal_msg_hdr_stru;

/* 配置消息 */
typedef struct
{
    wal_msg_hdr_stru            st_msg_hdr;         /* 配置消息头 */
    oal_uint8                   auc_msg_data[4];    /* 配置消息payload */
}wal_msg_stru;

typedef struct
{
    mac_vap_stru                *pst_mac_vap;
    oal_int8                     pc_param[4];      /* 查询或配置信息 */
}wal_event_stru;

/* write消息格式 */
typedef struct
{
    wlan_cfgid_enum_uint16  en_wid;
    oal_uint16              us_len;
    oal_uint8               auc_value[WAL_MSG_WRITE_MAX_LEN];
}wal_msg_write_stru;

/* write消息时的返回消息 */
typedef struct
{
    wlan_cfgid_enum_uint16  en_wid;
    oal_uint8               auc_resv[2];
    oal_uint32              ul_err_code;    /* write消息返回的错误码 */
}wal_msg_write_rsp_stru;

/* response消息格式，与Write消息格式相同 */
typedef wal_msg_write_stru wal_msg_rsp_stru;

/* query消息格式:2字节WID x N */
typedef struct
{
    wlan_cfgid_enum_uint16  en_wid;
}wal_msg_query_stru;

/* WID对应的操作 */
typedef struct
{
    wlan_cfgid_enum_uint16  en_cfgid;                /* wid枚举 */
    oal_bool_enum_uint8     en_reset;              /* 是否复位 */
    oal_uint8               auc_resv[1];
    wal_config_get_func     p_get_func;            /* get函数 */
    wal_config_set_func     p_set_func;            /* set函数 */
}wal_wid_op_stru;


/* WMM SET消息格式 */
typedef struct
{
    wlan_cfgid_enum_uint16      en_cfg_id;
    oal_uint8                   uc_resv[2];
    oal_uint32                  ul_ac;
    oal_uint32                  ul_value;
}wal_msg_wmm_stru;

/* WMM query消息格式:2字节WID x N */
typedef struct
{
    wlan_cfgid_enum_uint16  en_wid;
    oal_uint8               uc_resv[2];
    oal_uint32              ul_ac;
}wal_msg_wmm_query_stru;

/*WID request struct*/
typedef struct
{
    oal_dlist_head_stru pst_entry;
    oal_ulong      ul_request_address;
    oal_void       *pst_resp_mem;
    oal_uint32     ul_resp_len;
    oal_uint32     ul_ret;
}wal_msg_request_stru;

typedef struct
{
    oal_ulong  ul_request_address;
}wal_msg_rep_hdr;

#define DECLARE_WAL_MSG_REQ_STRU(name)  wal_msg_request_stru name;
#define WAL_MSG_REQ_STRU_INIT(name) do{oal_memset((oal_void*)(&name), 0,OAL_SIZEOF(name));name.ul_request_address = (oal_ulong)&name;}while(0)

typedef struct
{
    oal_dlist_head_stru st_head;
    oal_spin_lock_stru  st_lock;
    oal_wait_queue_head_stru  st_wait_queue;
    oal_uint32          count;
}wal_msg_queue;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 宏定义
*****************************************************************************/
#define WAL_MSG_HDR_LENGTH              OAL_SIZEOF(wal_msg_hdr_stru)
#define WAL_MSG_WID_LENGTH              OAL_SIZEOF(wlan_cfgid_enum_uint16)

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  wal_config_process_pkt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  wal_config_get_wmm_params(oal_net_device_stru *pst_net_dev, oal_uint8 *puc_param);
extern oal_int32   wal_recv_config_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_uint32  wal_config_get_assoc_req_ie(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_void    wal_drv_cfg_func_hook_init(oal_void);
extern oal_uint32  hmac_config_send_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
extern oal_void wal_cfg_msg_task_sched(oal_void);
extern oal_int32  wal_set_msg_response_by_addr(oal_ulong addr,oal_void * pst_resp_mem ,oal_uint32 ul_resp_ret,
                                                 oal_uint32 uc_rsp_len);
extern oal_void wal_msg_request_add_queue(wal_msg_request_stru* pst_msg);
extern oal_void wal_msg_request_remove_queue(wal_msg_request_stru* pst_msg);
extern oal_void wal_msg_queue_init(oal_void);
extern oal_uint32 wal_get_request_msg_count(oal_void);
extern oal_uint32  wal_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

extern oal_uint32 wal_send_cali_data(oal_net_device_stru *pst_net_dev);
extern oal_uint32 wal_check_and_release_msg_resp(wal_msg_stru   *pst_rsp_msg);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_config.h */
