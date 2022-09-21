/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_main
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : oam_main.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAM_MAIN_H__
#define __OAM_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAM_BEACON_HDR_LEN              24
#define OAM_TIMER_MAX_LEN               36
#define OAM_PRINT_CRLF_NUM              20              /* 输出换行符的个数 */

#define OAM_FEATURE_NAME_ABBR_LEN            (12)           /* 特性名称缩写最大长度 */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define OAM_DATA2SDT_FAIL_COUNT     1000
#endif

/* 打印方式定义 */
typedef oal_uint32  (* oal_print_func)(oal_int8 *pc_string);

/* 变参数据格式定义 */
typedef oal_int8*   oam_va_list;

/*****************************************************************************
  3 枚举定义
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
/* 日志特性列表结构体定义 */
typedef struct
{
    oam_feature_enum_uint8              en_feature_id;
    oal_uint8                           auc_feature_name_abbr[OAM_FEATURE_NAME_ABBR_LEN]; /* 以0结束 */
}oam_software_feature_stru;

/* 每隔ul_interval才允许ul_burst条日志输出 */
typedef enum
{
    OAM_RATELIMIT_OUTPUT        = 0,
    OAM_RATELIMIT_NOT_OUTPUT,
}oam_ratelimit_output_enum;
typedef oal_uint8   oam_ratelimit_output_enum_uint8;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
//extern oam_mng_ctx_stru             g_st_oam_mng_ctx;
extern oam_software_feature_stru    gst_oam_feature_list[];

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32  oam_main_init(oal_void);
extern oal_void   oam_main_exit(oal_void);
extern oal_uint32   oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);
extern oal_uint32  oam_set_file_path(oal_int8 *pc_file_path, oal_uint32 ul_length);
extern oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type);
extern oal_uint32  oam_print(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_file(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_sdt(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_console(oal_int8 *pc_string);
extern oal_uint32  oam_upload_log_to_sdt(oal_int8 *pc_string);
extern oal_void oam_dump_buff_by_hex(oal_uint8 *puc_buff, oal_int32 l_len, oal_int32 l_num);
extern oam_ratelimit_output_enum_uint8 oam_log_ratelimit(oam_ratelimit_type_enum_uint8 en_ratelimit_type );

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"

#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAM_BEACON_HDR_LEN              24
#define OAM_TIMER_MAX_LEN               36
#define OAM_PRINT_CRLF_NUM              20              /* 输出换行符的个数 */

#define OAM_FEATURE_NAME_ABBR_LEN            (12)           /* 特性名称缩写最大长度 */

#define LOG_NAME_LEN    20
#define LOG_OAM_PATH_LEN    30
#define WIFI_OAM_PREFIX    "wifi_oam_log_"
#define WIFI_OAM_PATH       "/jffs0/data/oam_wifi/"

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define OAM_DATA2SDT_FAIL_COUNT     1000
#endif

/* 打印方式定义 */
typedef oal_uint32  (* oal_print_func)(oal_int8 *pc_string);

/* 变参数据格式定义 */
typedef oal_int8*   oam_va_list;

/*等待的事件类型*/
#define oam_event_wait_bit0  1<<0
/*事件控制结构体*/
extern EVENT_CB_S oam_event;

/*****************************************************************************
  3 枚举定义
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
/*轮替日志操作结构体*/
typedef struct oam_log_save
{
    FILE*   pst_fd;                             /* 当前处理轮替日志文件fd*/
    oal_int8    ac_prefix[LOG_NAME_LEN];            /* 日志文件前缀类似"wifi_log_"*/
    oal_int32 st_size;               /*每个轮替日志大小(以kb为单位)*/
    oal_int32 st_num;                /* 轮替日志的数量*/
    oal_int8  st_path[LOG_OAM_PATH_LEN];               /* log config path in *.ini file */
    oal_int32   l_curr_num;                           /* log file num in curr path */
    oal_int8    ac_file[LOG_OAM_PATH_LEN + LOG_NAME_LEN + 1]; /* abs path log file */
}OAM_LOG_LUNTI;

typedef unsigned int	uint;
typedef struct oam_rx_sdt_cmd
{
    int (*uart_rx_sdt_cmd_dispose)(char* ch, uint ch_cnt);
}oam_rx_sdt_cmd_func_hook_stru;

extern oam_rx_sdt_cmd_func_hook_stru g_oam_uart_rx_sdt_cmd_func_hook;

/* 日志特性列表结构体定义 */
typedef struct
{
    oam_feature_enum_uint8              en_feature_id;
    oal_uint8                           auc_feature_name_abbr[OAM_FEATURE_NAME_ABBR_LEN]; /* 以0结束 */
}oam_software_feature_stru;

/* 每隔ul_interval才允许ul_burst条日志输出 */
typedef enum
{
    OAM_RATELIMIT_OUTPUT        = 0,
    OAM_RATELIMIT_NOT_OUTPUT,
}oam_ratelimit_output_enum;
typedef oal_uint8   oam_ratelimit_output_enum_uint8;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
//extern oam_mng_ctx_stru             g_st_oam_mng_ctx;
extern oam_software_feature_stru    gst_oam_feature_list[];

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_int32  oam_main_init(oal_void);
extern oal_void   oam_main_exit(oal_void);
extern oal_uint32   oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);
extern oal_uint32  oam_set_file_path(oal_int8 *pc_file_path, oal_uint32 ul_length);
//extern oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type);
extern oal_uint32  oam_print(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_file(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_sdt(oal_int8 *pc_string);
extern oal_uint32  oam_print_to_console(oal_int8 *pc_string);
extern oal_uint32  oam_upload_log_to_sdt(oal_int8 *pc_string);
extern oal_void oam_dump_buff_by_hex(oal_uint8 *puc_buff, oal_int32 l_len, oal_int32 l_num);
extern oam_ratelimit_output_enum_uint8 oam_log_ratelimit(oal_uint8 en_ratelimit_type );
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_main */
