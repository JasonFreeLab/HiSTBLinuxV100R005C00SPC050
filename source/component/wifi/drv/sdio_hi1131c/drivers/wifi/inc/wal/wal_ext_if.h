/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : wal_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : wal对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WAL_EXT_IF_H__
#define __WAL_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_schedule.h"
#include "wlan_types.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_EXT_IF_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WAL_SDT_MEM_MAX_LEN             32      /* SDT读写内存的最大长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* offload时，表示哪一个核的枚举 */
typedef enum
{
    WAL_OFFLOAD_CORE_MODE_HMAC,
    WAL_OFFLOAD_CORE_MODE_DMAC,

    WAL_OFFLOAD_CORE_MODE_BUTT
}wal_offload_core_mode_enum;
typedef oal_uint8 wal_offload_core_mode_enum_uint8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFR
/* dfr相关功能信息 */
typedef struct
{
    oal_uint32            *past_netdev[WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT+1];
    oal_uint32             ul_netdev_num;
    oal_uint32             bit_hw_reset_enable              : 1,        /* 硬件不去关联复位开关 */
                           bit_device_reset_enable          : 1,        /* device挂死异常恢复开关 */
                           bit_soft_watchdog_enable         : 1,        /* 软狗功能开关 */
                           bit_device_reset_process_flag    : 1,        /* device挂死异常复位操作启动 */

                           bit_ready_to_recovery_flag  : 1,
                           bit_user_disconnect_flag    : 1,            /* device挂死异常，需要在dfr恢复后告诉对端去关联的状态 */
                           bit_resv                    : 26;
    oal_uint32             ul_excp_type;       /* 异常类型 */

}wal_dfr_info_stru;
#endif //_PRE_WLAN_FEATURE_DFR
/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/* SDT上传接口的注册函数类型 */
typedef oal_int32   (* wal_sdt_up_func)(oal_netbuf_stru *pst_netbuf);

/*lint -e958*/ /*lint -e959*/
/* 读取和设置全局变量的结构体 */
#define WAL_GLB_VAR_NAME_LEN         (31)
#define WAL_GLB_VAR_VAL_LEN          (128)
typedef struct
{
	oal_uint8	uc_mode;             /* 读写模式 */
	oal_uint16  us_len;              /* 读写长度 */
	oal_uint8   en_offload_core_mode;
	oal_uint8	auc_global_value_name[WAL_GLB_VAR_NAME_LEN + 1];
	oal_uint8   auc_global_value[WAL_GLB_VAR_VAL_LEN];
}wal_sdt_global_var_stru;
/*lint -e958*/ /*lint -e959*/

/* 读取和设置寄存器的结构体 */
typedef struct
{
    oal_uint8       auc_vapname[16];
    oal_uint32      ul_addr;
    oal_uint16      us_len;
    oal_uint8       uc_mode;
    oal_uint8       auc_resv[1];
    oal_uint32      ul_reg_val;
}wal_sdt_reg_frame_stru;

/* 读取和设置内存的结构体 */
typedef struct
{
    oal_uint                            ul_addr;
    oal_uint16                          us_len;
    oal_uint8                           uc_mode;
    wal_offload_core_mode_enum_uint8    en_offload_core_mode;
    oal_uint8                           auc_data[WAL_SDT_MEM_MAX_LEN];
}wal_sdt_mem_frame_stru;

/* 维测，设置某一种具体event上报开关的参数结构体 */
typedef struct
{
    oal_int32                           l_event_type;
    oal_int32                           l_param;
}wal_specific_event_type_param_stru;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

extern oal_uint8         g_uc_custom_cali_done; /* 标识是否是上电第一次校准 */

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32  wal_main_init(oal_void);
extern oal_void  wal_main_exit(oal_void);
extern oal_int32  wal_recv_memory_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_global_var_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_reg_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);
extern oal_int32  wal_recv_config_cmd(oal_uint8 *puc_buf, oal_uint16 us_len);

extern oal_uint32  wal_hipriv_get_mac_addr(oal_int8 *pc_param,
                                            oal_uint8 auc_mac_addr[],
                                            oal_uint32 *pul_total_offset);

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern oal_uint32 wal_hipriv_register_inetaddr_notifier(oal_void);
extern oal_uint32 wal_hipriv_unregister_inetaddr_notifier(oal_void);
extern oal_uint32 wal_hipriv_register_inet6addr_notifier(oal_void);
extern oal_uint32 wal_hipriv_unregister_inet6addr_notifier(oal_void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_ext_if.h */
