/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_ext_if.h
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : oam对外公共接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAM_EXT_IF_H__
#define __OAM_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*oam功能k3、liteos共代码，先整体保证k3和liteos库oam功能涉及代码
一致，再逐步完善

完善时须确保k3有的oam功能必要的liteos不得缺失，oam功能k3和
liteos同步优化，能复用的函数及流程尽量复用且保证代码简洁
*/

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "wlan_spec.h"
#include "platform_spec.h"
#include "oal_types.h"
#include "oal_net.h"
#ifdef _PRE_WLAN_DFT_REG
#include "oam_register.h"
#endif
#include "oam_wdk.h"
#include "oam_config.h"
#include "chr_user.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_EXT_IF_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/* 日志宏定义 */
/* 该接口需要严格控制调用，主要用于中断上半部和OAM OAL等模块频繁触发的异常分支 */

#ifdef _PRE_WLAN_DFT_LOG
#define OAM_EXCP_RECORD(_uc_vap_id, _excp_id)   \
        oam_exception_record(_uc_vap_id, _excp_id)

#define OAM_IO_PRINTK(fmt, ...)      \
        oam_log_console_printk(THIS_FILE_ID, (oal_uint16)__LINE__, OAL_FUNC_NAME, fmt, ##__VA_ARGS__)

#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_INFO, fmt, 0, 0, 0, 0);
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_INFO, fmt, (oal_uint)p1, 0, 0, 0);
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_INFO, fmt, (oal_uint)p1, (oal_uint)p2, 0, 0);
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_INFO, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, 0);
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_INFO, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4);

#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_WARNING, fmt, 0, 0, 0, 0);
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_WARNING, fmt, (oal_uint)p1, 0, 0, 0);
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_WARNING, fmt, (oal_uint)p1, (oal_uint)p2, 0, 0);
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_WARNING, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, 0);
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_WARNING, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4);
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)  \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_ERROR, fmt, 0, 0, 0, 0);
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_ERROR, fmt, (oal_uint)p1, 0, 0, 0);
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_ERROR, fmt, (oal_uint)p1, (oal_uint)p2, 0, 0);
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_ERROR, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, 0);
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4) \
    OAL_PRINT_NLOGS(OAL_FUNC_NAME, (oal_uint16)THIS_FILE_ID, (oal_uint16)__LINE__, (void*)OAL_RET_ADDR,_uc_vap_id, _en_feature_id, OAM_LOG_LEVEL_ERROR, fmt, (oal_uint)p1, (oal_uint)p2, (oal_uint)p3, (oal_uint)p4);

#else
#define OAM_EXCP_RECORD(_uc_vap_id, _excp_id)
#define OAM_IO_PRINTK(fmt, ...)
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_DEV)
#if 0
//#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)                      OAL_IO_PRINT("[INFO]"fmt"\r\n")
//#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)                  OAL_IO_PRINT("[INFO]"fmt"\r\n", p1)
//#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)              OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2)
//#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)          OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2, p3)
//#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)      OAL_IO_PRINT("[INFO]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)                   OAL_IO_PRINT("[WARNING]"fmt"\r\n")
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)               OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)           OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)       OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2, p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   OAL_IO_PRINT("[WARNING]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)                     OAL_IO_PRINT("[ERROR]"fmt"\r\n")
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)                 OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)             OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)         OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2, p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)     OAL_IO_PRINT("[ERROR]"fmt"\r\n", p1, p2, p3, p4)
#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#else

#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)   \
        oam_log_print0(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_INFO, NULL, 0, 0, 0, 0);

#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)  \
        oam_log_print1(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_INFO, NULL, (oal_int32)p1, 0, 0, 0);

#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)  \
        oam_log_print2(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_INFO, NULL, (oal_int32)p1, (oal_int32)p2, 0, 0);

#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
        oam_log_print3(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_INFO, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, 0);

#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4) \
        oam_log_print4(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_INFO, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, (oal_int32)p4);
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt) \
        oam_log_print0(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_WARNING, NULL, 0, 0, 0, 0);

#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)  \
        oam_log_print1(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_WARNING, NULL, (oal_int32)p1, 0, 0, 0);

#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)  \
        oam_log_print2(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_WARNING, NULL, (oal_int32)p1, (oal_int32)p2, 0, 0);

#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)  \
        oam_log_print3(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_WARNING, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, 0);

#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)  \
        oam_log_print4(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_WARNING, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, (oal_int32)p4);

#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)  \
        oam_log_print0(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_ERROR, NULL, 0, 0, 0, 0);

#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)  \
        oam_log_print1(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_ERROR, NULL, (oal_int32)p1, 0, 0, 0);

#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)  \
        oam_log_print2(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_ERROR, NULL, (oal_int32)p1, (oal_int32)p2, 0, 0);

#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
       oam_log_print3(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_ERROR, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, 0);

#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)   \
        oam_log_print4(_uc_vap_id, _en_feature_id, THIS_FILE_ID, (oal_uint16)__LINE__, OAM_LOG_LEVEL_ERROR, NULL, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, (oal_int32)p4);
#endif
#else
#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#define OAM_DIFF_LOG0           OAM_INFO_LOG0
#define OAM_DIFF_LOG1           OAM_INFO_LOG1
#define OAM_DIFF_LOG2           OAM_INFO_LOG2
#define OAM_DIFF_LOG3           OAM_INFO_LOG3
#define OAM_DIFF_LOG4           OAM_INFO_LOG4
#else
#define OAM_DIFF_LOG0           OAM_WARNING_LOG0
#define OAM_DIFF_LOG1           OAM_WARNING_LOG1
#define OAM_DIFF_LOG2           OAM_WARNING_LOG2
#define OAM_DIFF_LOG3           OAM_WARNING_LOG3
#define OAM_DIFF_LOG4           OAM_WARNING_LOG4
#endif


/*****************************************************************************
    2.1 TRACE相关宏定义
*****************************************************************************/
/* 计算profiling宏定义 */
#ifdef _PRE_PROFILING_MODE
#define OAM_PROFILING_RX_STATISTIC(_uc_func_idx) oam_profiling_rx_save_data(_uc_func_idx)
#define OAM_PROFILING_TX_STATISTIC(_pst_pointer, _uc_func_idx) oam_profiling_tx_save_data(_pst_pointer, _uc_func_idx)
#define OAM_PROFILING_ALG_STATISTIC(_uc_func_idx) oam_profiling_alg_save_data(_uc_func_idx)
#define OAM_PROFILING_STARTTIME_STATISTIC(_uc_func_idx) oam_profiling_starttime_save_timestamp(_uc_func_idx)
#define OAM_PROFILING_CHSWITCH_STATISTIC(_uc_func_idx) oam_profiling_chswitch_save_timestamp(_uc_func_idx)
#else
#define OAM_PROFILING_RX_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_TX_STATISTIC(_pst_pointer, _uc_func_idx)
#define OAM_PROFILING_ALG_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_STARTTIME_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_CHSWITCH_STATISTIC(_uc_func_idx)
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_DEBUG_MODE
/* 统计信息宏定义 *//*lint -e506*/ /*lint -e774*/
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)do{                           \
            if (_uc_dev_id < WLAN_DEVICE_MAX_NUM_PER_CHIP)                            \
            {                                                                         \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member += (_num);  \
            }                                                                         \
        }while(0)

/* 为了对数组下标进行保护，必须要传入数组长度(第4个参数) */
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)do{            \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) && (_uc_array_index < _uc_array_max_size)) \
            {                                                                                          \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].aul_##_member[_uc_array_index]++;         \
            }                                                                                          \
        }while(0)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)do{  \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) \
                && (_uc_q_id < OAM_RX_DSCR_QUEUE_CNT) && (_uc_index < OAM_IRQ_FREQ_STAT_MEMORY))               \
            {                                                                                                   \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].aul_##_member[_uc_q_id][_uc_index] = (_ul_val); \
            }                                                                                                   \
        }while(0)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val) do{                             \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
               *(_pul_val)= g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member;      \
            }                                                                           \
        }while(0)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)do { \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
                g_st_stat_info.ast_dev_stat_info[_uc_dev_id].ul_##_member = (_uc_val); \
            }                                                                           \
        }while(0)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].ul_##_member += (_num);   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member) do{  \
            if ((_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC) && (_uc_mgmt_id < WLAN_MGMT_SUBTYPE_BUTT))   \
            {                                                                                        \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].aul_##_member[_uc_mgmt_id]++;           \
            }                                                                                        \
        }while(0)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num) do{                                       \
            if (_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)                     \
            {                                                                           \
                g_st_stat_info.ast_user_stat_info[_uc_user_id].ul_##_member += (_num);              \
            }                                                                               \
        }while(0)

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num) do {\
            if ((_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM) && (_uc_tid_num < WLAN_TIDNO_BUTT))        \
            {                                                                                       \
                g_st_stat_info.ast_user_stat_info[_uc_user_id].aul_##_member[_uc_tid_num] += (_num);\
            }                                                                                       \
        }while(0)

#define OAM_STAT_GET_STAT_ALL() (&g_st_stat_info)
#else
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)
#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)
#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)
#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)
#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num)
#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)
#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)
#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)
#define OAM_STAT_GET_STAT_ALL()

#endif
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/* 统计信息宏定义 *//*lint -e506*/ /*lint -e774*/
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)

/* 为了对数组下标进行保护，必须要传入数组长度(第4个参数) */
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
                g_st_stat_info.ast_vap_stat_info[_uc_vap_id].ul_##_member += (_num);   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num) 

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)

#define OAM_STAT_GET_STAT_ALL() (&g_st_stat_info)
#else
#ifdef _PRE_DEBUG_MODE
/* 统计信息宏定义 *//*lint -e506*/ /*lint -e774*/
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)do{                           \
            if (_uc_dev_id < WLAN_DEVICE_MAX_NUM_PER_CHIP)                            \
            {                                                                         \
            }                                                                         \
        }while(0)

/* 为了对数组下标进行保护，必须要传入数组长度(第4个参数) */
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)do{            \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) && (_uc_array_index < _uc_array_max_size)) \
            {                                                                                          \
            }                                                                                          \
        }while(0)

#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)do{  \
            if ((_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) \
                && (_uc_q_id < OAM_RX_DSCR_QUEUE_CNT) && (_uc_index < OAM_IRQ_FREQ_STAT_MEMORY))               \
            {                                                                                                   \
            }                                                                                                   \
        }while(0)

#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val) do{                             \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
            }                                                                           \
        }while(0)

#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)do { \
            if (_uc_dev_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)                              \
            {                                                                           \
            }                                                                           \
        }while(0)

#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num) do{ \
            if (_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)          \
            {                                                   \
            }                                                                               \
        }while(0)

#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member) do{  \
            if ((_uc_vap_id < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC) && (_uc_mgmt_id < WLAN_MGMT_SUBTYPE_BUTT))   \
            {                                                                                        \
            }                                                                                        \
        }while(0)

#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num) do{                                       \
            if (_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)                     \
            {                                                                           \
            }                                                                               \
        }while(0)

#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num) do {\
            if ((_uc_user_id < WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM) && (_uc_tid_num < WLAN_TIDNO_BUTT))        \
            {                                                                                       \
            }                                                                                       \
        }while(0)

#define OAM_STAT_GET_STAT_ALL()
#else
#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)
#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)
#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)
#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)
#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num)
#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)
#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)
#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)
#define OAM_STAT_GET_STAT_ALL()

#endif

#endif

#ifdef _PRE_DEBUG_MODE
#define OAM_TID_AMPDU_STATS_INCR(_member, _cnt)     ((_member) += (_cnt))
#else
#define OAM_TID_AMPDU_STATS_INCR(_member, _cnt)
#endif


#ifdef _PRE_WIFI_DMT
#define OAM_PRINT_FORMAT_LENGTH     1024                    /* 打印格式字符串的最大长度:DMT调试的打印信息会比较长，不够时会踩内存 */
#else
#define OAM_PRINT_FORMAT_LENGTH     256                     /* 打印格式字符串的最大长度 */
#endif

/* 日志结构体相关宏，用于oam_log_info_stru */
#define OAM_FUNC_NAME_MAX_LEN           48                                      /* 函数名的最大长度 */
#define OAM_LOG_INFO_MAX_LEN            100                                     /* 日志信息最大长度 */
#define OAM_LOG_INFO_IN_MEM_MAX_NUM     5000   /* oam模块最多保存5000条log信息，超过以后从头自动覆盖 */
#define OAM_LOG_ENTRY_PARA_NUM          4

//#define OAM_SEQ_TRACK_NUM              256
#define OAM_SEQ_TRACK_NUM              128

/* device级别的各类中断错误最大个数 */
#define OAM_MAC_ERROR_TYPE_MAX_NUM      25
#define OAM_SOC_IRQ_MAX_NUM             5
#define OAM_PMU_BUCK_IRQ_MAX_NUM        5
#define OAM_MAC_SUB_IRQ_MAX_NUM         11

/* 内存块信息除掉最后一个成员占用的大小 */
#define OAM_MEMBLOCK_INFO_STRU_LEN      8

/* oam_stats_device_subtype_irq_stru前三个成员占用空间大小 */
#define OAM_FIRST_THREE_MEMBER_LEN      4

/* 每一个事件队列中事件个数最大值 */
#define OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE 8

/* OAM模块申请skb时，头部和尾部为sdt分别预留8个和1个字节 */
#define OAM_RESERVE_SKB_HEADROOM_LEN    8
#define OAM_RESERVE_SKB_TAILROOM_LEN    1
#define OAM_RESERVE_SKB_LEN             (OAM_RESERVE_SKB_HEADROOM_LEN + OAM_RESERVE_SKB_TAILROOM_LEN)

/* 字符串以0结尾上报，实际字符串内容最大长度 */
#define OAM_REPORT_MAX_STRING_LEN       (WLAN_SDT_NETBUF_MAX_PAYLOAD - 1)   /*以\0结束*/


/* 统计相关宏 */
#define OAM_MAC_ERROR_TYPE_CNT    25
#define OAM_RX_DSCR_QUEUE_CNT     2
#define OAM_IRQ_FREQ_STAT_MEMORY  50

#define OAM_TID_TRACK_NUM         4

/**********************性能维测相关宏定义******************/
#ifdef _PRE_WLAN_DFT_STAT
#define  OAM_PHY_STAT_NODE_ENABLED_MAX_NUM    4
#define  OAM_PHY_STAT_RX_PPDU_CNT             8
#define  OAM_PHY_STAT_ITEM_MIN_IDX            1
#define  OAM_PHY_STAT_ITEM_MAX_IDX            16
#define  OAM_MACHW_STAT_RX_MEMBER_CNT         18
#define  OAM_MACHW_STAT_TX_MEMBER_CNT         8
#define  OAM_PSM_STAT_CNT                     10
#define  OAM_UAPSD_STAT_CNT                   11
#define  OAM_TID_STAT_CNT                     14
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*data type */
typedef enum
{
    OAM_DATA_TYPE_LOG       = 0x1,
    OAM_DATA_TYPE_OTA       = 0x2,
    OAM_DATA_TYPE_TRACE     = 0x3,
    OAM_DATA_TYPE_EVENT     = 0x4,
    OAM_DATA_TYPE_MEM_RW    = 0x9,
    OAM_DATA_TYPE_REG_RW    = 0x15,
    OAM_DATA_TYPE_CFG       = 0x0b,
    OAM_DATA_TYPE_GVAR_RW   = 0x27,   /* global value read or write */
    OAM_DATA_TYPE_STRING    = 0x28,   /* report string  */

    OAM_DATA_TYPE_DEVICE_LOG = 0x40,
    OAM_DATA_TYPE_BUTT
}oam_data_type_enum;
typedef oal_uint8 oam_data_type_enum_uint8;

/* SDT驱动侧向SDT APP侧发送数据的类型 */
typedef enum
{
    OAM_PRIMID_TYPE_PC_TO_DEV_DATA = 1,
    OAM_PRIMID_TYPE_DEV_ACK,
    OAM_PRIMID_TYPE_DEV_ACTIVE_UPLOAD,
    OAM_PRIMID_TYPE_OUTPUT_CONTENT,

    SDT_DRV_PRIMID_TYPE_BUTT
}oam_primid_type_enum;
typedef oal_uint8 oam_primid_type_enum_uint8;

typedef enum
{
    OAM_MODULE_ID_ALL,
    OAM_MODULE_ID_WAL,
    OAM_MODULE_ID_HMAC,
    OAM_MODULE_ID_DMAC,

    OAM_MODULE_ID_MAC,  /* 此模块ID只用于HMAC、DMAC公共文件日志记录使用，软件中不存在MAC此模块 */

    OAM_MODULE_ID_HAL,
    OAM_MODULE_ID_OAM,
    OAM_MODULE_ID_OAL,
    OAM_MODULE_ID_FRW,
    OAM_MODULE_ID_ALG,
    OAM_MODULE_ID_BLD,

    OAM_MODULE_ID_ALG_SCHEDULE,
    OAM_MODULE_ID_ALG_AUTORATE,
    OAM_MODULE_ID_ALG_SMARTANT,
    OAM_MODULE_ID_ALG_ACS,
    OAM_MODULE_ID_ALG_DBAC,

#ifdef _PRE_WIFI_DMT
    OAM_MODULE_ID_DMT,
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    OAM_MODULE_ID_ALG_TXBF,
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
    OAM_MODULE_ID_PERFORM_STAT,
#endif

    OAM_MODULE_ID_ALG_ANTI_INTF,

    OAM_MODULE_ID_HUT,

    OAM_MODULE_ID_ALG_CCA_OPT,


    /* 待补充 */

    OAM_MODULE_ID_BUTT
}oam_module_id_enum;
typedef oal_uint16 oam_module_id_enum_uint16;

/* 日志级别 */
typedef enum
{
    OAM_LOG_LEVEL_ERROR     =    1,       /* ERROR级别打印 */
    OAM_LOG_LEVEL_WARNING,                /* WARNING级别打印 */
    OAM_LOG_LEVEL_INFO,                   /* INFO级别打印 */

    OAM_LOG_LEVEL_BUTT
}oam_log_level_enum;
typedef oal_uint8 oam_log_level_enum_uint8;

#define OAM_LOG_DEFAULT_LEVEL           OAM_LOG_LEVEL_WARNING

/* 配置文件，配置的类型 */
typedef enum
{
    OAM_CFG_TYPE_MAX_ASOC_USER            = 0,

    OAM_CFG_TYPE_BUTT
}oam_cfg_type_enum;
typedef oal_uint16 oam_cfg_type_enum_uint16;

/* 打印模式定义 */
typedef enum
{
    OAM_OUTPUT_TYPE_CONSOLE  = 0,            /* 控制台输出 */
    OAM_OUTPUT_TYPE_FS,                      /* 写到文件系统 */
    OAM_OUTPUT_TYPE_SDT,                     /* 输出到SDT */
    //OAM_OUTPUT_TYPE_IPC,                     /* 通过核间通讯方式，发送至另一核，一般是从核将可维可测内容发送至主核 */

    OAM_OUTPUT_TYPE_BUTT
}oam_output_type_enum;
typedef oal_uint8 oam_output_type_enum_uint8;

/* event上报事件消息类型 */
typedef enum
{
    OAM_EVENT_WID_QUERY,                     /* 配置命令消息，查询命令 */
    OAM_EVENT_WID_WRITE,                     /* 配置命令消息，写命令 */
    OAM_EVENT_INTERNAL,                      /* WiTP内部各层之间的事件消息 */
    OAM_EVENT_VAP_STATE_CHANGE,              /* VAP状态迁移事件消息 */
    OAM_EVENT_PAUSE_OR_RESUME_TID,           /* 暂停或者恢复tid */
    OAM_EVENT_PAUSE_OR_RESUME_USER,          /* 暂停或者恢复user消息 */
    OAM_EVENT_VAP_CHANGE_CHANNEL,            /* VAP切换信道 */
    OAM_EVENT_USER_INFO_CHANGE,              /* 用户状态信息或者能力信息变化 */
    OAM_EVENT_USER_TXRX_PARAM,               /* 用户收发参数 */
    OAM_EVENT_REGISTER = 9,                   /* 寄存器 */

    OAM_EVENT_TYPE_BUTT
}oam_event_type_enum;
typedef oal_uint16 oam_event_type_enum_uint16;

/* OTA上报事件类型 */
typedef enum
{
    /* 默认关闭上报 */
    OAM_OTA_TYPE_RX_DSCR,                     /* 接收描述符 */
    OAM_OTA_TYPE_TX_DSCR,                     /* 发送描述符 */
    OAM_OTA_TYPE_80211_FRAME,                 /* 80211帧(不包括beacon) */
    OAM_OTA_TYPE_BEACON,                      /* beacon */
    OAM_OTA_TYPE_ETH_FRAME,                   /* 以太网帧 */
    OAM_OTA_TYPE_RX_DMAC_CB,
    OAM_OTA_TYPE_RX_HMAC_CB,
    OAM_OTA_TYPE_TX_CB,
    OAM_OTA_TYPE_TIMER_TRACK,                 /* 定时器创建删除的行号和文件号追踪 ,已废弃*/

    /* 默认打开上报 */
    OAM_OTA_TYPE_IRQ,                         /* 中断信息 */
    OAM_OTA_TYPE_TIMER,                       /* 软件定时器信息 */
    OAM_OTA_TYPE_MEMPOOL,                     /* 某一内存池及所有子池使用信息 */
    OAM_OTA_TYPE_MEMBLOCK,                    /* 某一内存池的所有内存块使用信息及内容，或者任意连续内存块的内容 */
    OAM_OTA_TYPE_EVENT_QUEUE,                 /* 当前所有存在事件的事件队列中的事件个数和事件头信息 */
    OAM_OTA_TYPE_MPDU_NUM,
    OAM_OTA_TYPE_PHY_STAT,                    /* phy收发包统计值 */
    OAM_OTA_TYPE_MACHW_STAT,                  /* mac收发包统计值 */
    OAM_OTA_TYPE_MGMT_STAT,                   /* 管理帧统计 */
    OAM_OTA_TYPE_DBB_ENV_PARAM,               /* 空口环境类维测参数 */
    OAM_OTA_TYPE_USR_QUEUE_STAT,              /* 用户队列统计信息 */
    OAM_OTA_TYPE_VAP_STAT,                    /* vap吞吐相关统计信息 */
    OAM_OTA_TYPE_USER_THRPUT_PARAM,           /* 影响用户实时吞吐相关的统计信息 */
    OAM_OTA_TYPE_AMPDU_STAT,                  /* ampdu业务流程统计信息 */
    OAM_OTA_TYPE_HARDWARE_INFO,               /* hal mac相关信息 */
    OAM_OTA_TYPE_USER_QUEUE_INFO,             /* 用户队列信息 */

    /* VAP与USER等结构体的信息，上报整个结构体内存 */
    OAM_OTA_TYPE_HMAC_VAP,
    OAM_OTA_TYPE_DMAC_VAP,
    OAM_OTA_TYPE_HMAC_USER,
    OAM_OTA_TYPE_MAC_USER,
    OAM_OTA_TYPE_DMAC_USER,

    /* hmac 与 dmac vap中部分成员的大小 */
    OAM_OTA_TYPE_HMAC_VAP_MEMBER_SIZE,
    OAM_OTA_TYPE_DMAC_VAP_MEMBER_SIZE,

    /* 三种级别的统计信息,这三个必放到一起!!! */
    OAM_OTA_TYPE_DEV_STAT_INFO,
    OAM_OTA_TYPE_VAP_STAT_INFO,
    OAM_OTA_TYPE_USER_STAT_INFO,

    OAM_OTA_TYPE_PHY_BANK1_INFO,     /* PHY寄存器 BANK1 信息 */
    OAM_OTA_TYPE_PHY_BANK2_INFO,     /* PHY寄存器 BANK2 信息 */
    OAM_OTA_TYPE_PHY_BANK3_INFO,     /* PHY寄存器 BANK3 信息 */
    OAM_OTA_TYPE_PHY_BANK4_INFO,     /* PHY寄存器 BANK4 信息 */
    OAM_OTA_TYPE_MAC_BANK0_INFO,     /* MAC寄存器 BANK0 信息 */
    OAM_OTA_TYPE_MAC_BANK1_INFO,     /* MAC寄存器 BANK1 信息 */
    OAM_OTA_TYPE_MAC_BANK2_INFO,      /* MAC寄存器 BANK2 信息 */
    OAM_OTA_TYPE_MAC_BANK3_INFO,   /* MAC寄存器 BANK3 信息（存在几字节信息不能读取） */
    OAM_OTA_TYPE_MAC_BANK4_INFO,     /* MAC寄存器 BANK4 信息 */
    OAM_OTA_TYPE_RF_REG_INFO,     /* RF寄存器 */
    OAM_OTA_TYPE_SOC_REG_INFO,     /* SOC寄存器 */


    OAM_OTA_TYPE_BUTT
}oam_ota_type_enum;
typedef oal_uint8 oam_ota_type_enum_uint8;

/* 定时器追踪类型 */
typedef enum
{
    OAM_TIMER_TRACK_TYPE_CREATE = 0,
    OAM_TIMER_TRACK_TYPE_DESTROY,
    OAM_TIMER_TRACK_TYPE_IMMEDIATE_DESTROY,

    OAM_TIMER_TRACK_TYPE_BUTT
}oam_timer_track_type_enum;
typedef oal_uint8 oam_timer_track_type_enum_uint8;

/****************************单用户跟踪相关枚举*******************************/
/* 单用户跟踪内容，帧内容，CB字段，描述符 */
typedef enum
{
    OAM_USER_TRACK_CONTENT_FRAME = 0,
    OAM_USER_TRACK_CONTENT_CB,
    OAM_USER_TRACK_CONTENT_DSCR,

    OAM_USER_TRACK_CONTENT_BUTT
}oam_user_track_content_enum;
typedef oal_uint8 oam_user_track_content_enum_uint8;

/* 单用户跟踪帧类型:数据和管理 */
typedef enum
{
    OAM_USER_TRACK_FRAME_TYPE_MGMT = 0,
    OAM_USER_TRACK_FRAME_TYPE_DATA,

    OAM_USER_TRACK_FRAME_TYPE_BUTT
}oam_user_track_frame_type_enum;
typedef oal_uint8 oam_user_track_frame_type_enum_uint8;

/* 跟踪用户信息变化类型，event类型信息，状态变化驱动 */
typedef enum
{
    OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE = 0,         /* 用户关联状态 */
    OAM_USER_INFO_CHANGE_TYPE_TX_PROTOCOL,             /* 发送数据帧使用的协议模式 */
    OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL,             /* 接收数据帧使用的协议模式 */

    /* ... */

    OAM_USER_INFO_CHANGE_TYPE_BUTT
}oam_user_info_change_type_enum;
typedef oal_uint8 oam_user_info_change_type_enum_uint8;

/* 跟踪用户收发参数,event类型信息,配置命令驱动 */
typedef enum
{
    OAM_USER_TXRX_PARAM_TYPE_RSSI = 0,
    OAM_USER_TXRX_PARAM_TYPE_RATE,

    /* ... */

    OAM_USER_TXRX_PARAM_TYPE_BUTT
}oam_user_txrx_param_type_enum;
typedef oal_uint8 oam_user_txrx_param_type_enum_uint8;
/*****************************************************************************/


/* 统计信息上报类型，分为device级别，vap级别，user级别 */
typedef enum
{
    OAM_STATS_TYPE_DEVICE,
    OAM_STATS_TYPE_VAP,
    OAM_STATS_TYPE_USER,

    OAM_STATS_TYPE_BUTT
}oam_stats_type_enum;
typedef oal_uint8 oam_stats_type_enum_uint8;

/* device级别统计信息上报子类型， */
typedef enum
{
    OAM_STATS_DEVICE_SUBTYPE_IRQ,
    OAM_STATS_DEVICE_SUBTYPE_TIMER,
    OAM_STATS_DEVICE_SUBTYPE_MEMPOOL,
    OAM_STATS_DEVICE_SUBTYPE_EVENT_QUEUE,

    OAM_STATS_DEVICE_SUBTYPE_BUTT
}oam_stats_device_subtype_enum;
typedef oal_uint8 oam_stats_device_subtype_enum_uint8;

/* ALARM上报事件类型 */
typedef enum
{
    OAM_ALARM_TYPE_MEM_OVER_LEAK,
    OAM_ALARM_TYPE_PKT_RECV_LOST,
    OAM_ALARM_TYPE_PKT_SEND_LOST,

    OAM_ALARM_TYPE_BUTT
}oam_alarm_type_enum;
typedef oal_uint16 oam_alarm_type_enum_uint16;

/* 内存块信息上报类型 */
typedef enum
{
    OAM_MEMBLOCK_INFO_TYPE_UNIFORM,         /* 某一个内存池的所有内存块信息 */
    OAM_MEMBLOCK_INFO_TYPE_NON_UNIFORM,     /* 业务流程中需要查看的任意连续内存的信息 */

    OAM_MEMBLOCK_INFO_TYPE_BUTT
}oam_memblock_info_type_enum;
typedef oal_uint8 oam_memblock_info_type_enum_uint8;

/* STURCT上报事件类型 */
typedef enum
{
    OAM_STRUCT_TYPE_DEVICE,
    OAM_STRUCT_TYPE_HMAC_VAP,
    OAM_STRUCT_TYPE_MAC_VAP,
    OAM_STRUCT_TYPE_DMAC_VAP,
    OAM_STRUCT_TYPE_HMAC_USER,
    OAM_STRUCT_TYPE_MAC_USER,
    OAM_STRUCT_TYPE_DMAC_USER,
    OAM_STRUCT_TYPE_TID,

    OAM_STRUCT_TYPE_BUTT
}oam_struct_type_enum;
typedef oal_uint8 oam_struct_type_enum_uint8;

/*****************************************************************************
    trace、profiling相关枚举定义
*****************************************************************************/
/* profiling开关枚举定义 */
typedef enum
{
    OAM_PROFILING_SWITCH_OFF,
    OAM_PROFILING_SWITCH_ON,

    OAM_PROFILING_SWITCH_BUTT
}oam_profiling_swith_enum;
typedef oal_uint8 oam_profiling_swith_enum_uint8;

/* 报文发送统计函数列表 */
typedef enum
{
    OAM_PROFILING_FUNC_CONFIG_XMIT_START,    /*以太网报文进入wifi驱动*/
    OAM_PROFILING_FUNC_BRIDGE_XMIT_START,
    OAM_PROFILING_FUNC_TX_TO_WLAN,
    OAM_PROFILING_FUNC_DMAC_TX_START,
    OAM_PROFILING_FUNC_TID_ENQUEUE,
    OAM_PROFILING_FUNC_BRIDGE_XMIT_END,
    OAM_PROFILING_FUNC_CONFIG_XMIT_END,

    OAM_PROFILING_FUNC_SCHEDULE_START,       /*调度开始*/
    OAM_PROFILING_FUNC_SCHEDULE,
    OAM_PROFILING_FUNC_SCHEDULE_GET_TID,
    OAM_PROFILING_FUNC_AMPDU_AGGR_PREPARE,
    OAM_PROFILING_FUNC_AMPDU_CALCULATE_MINLEN,
    OAM_PROFILING_FUNC_AMPDU_REMOVE_QUEUE,
    OAM_PROFILING_FUNC_TX_GET_TSF,
    OAM_PROFILING_FUNC_TX_SET_DSCR,
    OAM_PROFILING_FUNC_TX_PUT_DSCR,
    OAM_PROFILING_FUNC_SCHEDULE_END,

    OAM_PROFILING_FUNC_TX_COMP_IRQ_START,   /*发送完成处理*/
    OAM_PROFILING_FUNC_TX_COMP_IRQ_END,
    OAM_PROFILING_FUNC_TX_COMP_DMAC_START,
    OAM_PROFILING_FUNC_AMPDU_AMPDU_PREPARE,
    OAM_PROFILING_FUNC_AMPDU_UPDATE_MIB,
    OAM_PROFILING_FUNC_AMPDU_TX_COMP_CHECK,
    OAM_PROFILING_FUNC_AMPDU_EXTRACT_BA,
    OAM_PROFILING_FUNC_AMPDU_COMP_ACK,
    OAM_PROFILING_FUNC_AMPDU_COMP_ENQUEUE_RETRY,
    OAM_PROFILING_FUNC_TX_COMP_DMAC_END,

    OAM_PROFILING_TX_FUNC_BUTT
} oam_profiling_tx_func_enum;
typedef oal_uint8 oam_profiling_tx_func_enum_uint8;

/* profiling的类型枚举 */
typedef enum
{
    OAM_PROFILING_RX,       /* 接收流程 */
    OAM_PROFILING_TX,       /* 发送流程 */
    OAM_PROFILING_ALG,      /* ALG流程 */

    OAM_PROFILING_CHIPSTART,    /* 芯片启动时间 */
    OAM_PROFILING_CHSWTICH,     /* 信道切换 */

    OAM_PROFILING_BUTT
}oam_profiling_enum;
typedef oal_uint8 oam_profiling_enum_uint8;

/* 报文接收统计函数列表 */
typedef enum
{
    OAM_PROFILING_FUNC_RX_COMP_IRQ_START,
    OAM_PROFILING_FUNC_RX_COMP_START,               /* 接收的基准时间 函数:hal_irq_rx_complete_isr */
    OAM_PROFILING_FUNC_RX_COMP_BASE_INFO,           /* 基本信息读写 */
    OAM_PROFILING_FUNC_RX_COMP_ALLOC_EVENT,         /* 申请事件内存 */
    OAM_PROFILING_FUNC_RX_COMP_IRQ_END,


    OAM_PROFILING_FUNC_RX_DMAC_START,               /* 函数:dmac_rx_process_data_event */
    OAM_PROFILING_FUNC_RX_DMAC_GET_CB_LIST,         /* 获取cb 链表*/
    OAM_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU,          /* 处理MPDU*/

    OAM_PROFILING_FUNC_RX_HMAC_START,
    OAM_PROFILING_FUNC_RX_HMAC_BASE_INFO,
    OAM_PROFILING_FUNC_RX_HMAC_TO_LAN,
    OAM_PROFILING_FUNC_RX_HMAC_TO_WLAN,
    OAM_PROFILING_FUNC_RX_HMAC_END,
    OAM_PROFILING_FUNC_RX_DMAC_END,

    OAM_PROFILING_RX_FUNC_BUTT
} oam_profiling_rx_func_enum;
typedef oal_uint8 oam_profiling_rx_func_enum_uint8;

/* ALG统计函数列表 */
typedef enum
{
    OAM_PROFILING_ALG_START,

#ifdef _PRE_WLAN_FEATURE_AUTORATE
    OAM_PROFILING_AUTORATE_QUERY_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_END,
    OAM_PROFILING_AUTORATE_QUERY_RATE_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_END,
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_START,
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_END,
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_START,
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_END,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_START,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_END,
    OAM_PROFILING_SCHEDULE_TX_COMP_START,
    OAM_PROFILING_SCHEDULE_TX_COMP_END,
#endif

    OAM_PROFILING_ALG_END,
    OAM_PROFILING_ALG_FUNC_BUTT
} oam_profiling_alg_func_enum;
typedef oal_uint8 oam_profiling_alg_func_enum_uint8;


/* 芯片统计时间加时间戳枚举 */
typedef enum
{
    OAM_PROFILING_STARTTIME_SELF_BEGIN,     /* 测量profiling函数本身时间开销 */
    OAM_PROFILING_STARTTIME_SELF_END,
    OAM_PROFILING_STARTTIME_SOC_BEGIN,
    OAM_PROFILING_STARTTIME_SOC_END,
    OAM_PROFILING_STARTTIME_MAC_BEGIN,
    OAM_PROFILING_STARTTIME_MAC_END,
    OAM_PROFILING_STARTTIME_PHY_BEGIN,
    OAM_PROFILING_STARTTIME_PHY_END,
    OAM_PROFILING_STARTTIME_ABB_BEGIN,
    OAM_PROFILING_STARTTIME_ABB_END,
    OAM_PROFILING_STARTTIME_RF_BEGIN,
    OAM_PROFILING_STARTTIME_RF_END,

    OAM_PROFILING_RESET_HW_BEGIN,
    OAM_PROFILING_RESET_HW_END,
    OAM_PROFILING_RESET_TOTAL_BEGIN,
    OAM_PROFILING_RESET_TOTAL_END,

    OAM_PROFILING_STARTTIME_FUNC_BUTT
}oam_profiling_starttime_func_enum;
typedef oal_uint8 oam_profiling_starttime_func_enum_uint8;

/* 信道切换时间枚举 */
typedef enum
{
    OAM_PROFILING_CHSWITCH_START,
    OAM_PROFILING_CHSWITCH_END,

    OAM_PROFILING_CHSWITCH_FUNC_BUTT
}oam_profiling_chswitch_func_enum;
typedef oal_uint8 oam_profiling_chswitch_func_enum_uint8;


/* SDT操作模式枚举 */
typedef enum
{
    OAM_SDT_MODE_WRITE = 0,
    OAM_SDT_MODE_READ,

    OAM_SDT_MODE_BUTT
}oam_sdt_rw_mode_enum;
typedef oal_uint8 oam_sdt_rw_mode_enum_uint8;

/* SDT打印beacon帧和beacon帧接收描述符的开关类型,其中beacon帧的打印收发流程都适用 */
typedef enum
{
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BEACON = 1,    /* 打印beacon帧，不打印beacon帧的接收描述符 */
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_RXDSCR,        /* 打印beacon帧的接收描述符，不打印beacon帧 */
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH,          /* 打印beacon帧以及接收描述符 */

    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BUTT
}oam_sdt_print_beacon_rxdscr_type_enum;
typedef oal_uint8 oam_sdt_print_beacon_rxdscr_type_enum_uint8;

/* 表明帧是属于接收流程还是发送流程的枚举 */
typedef enum
{
    OAM_OTA_FRAME_DIRECTION_TYPE_TX = 0,
    OAM_OTA_FRAME_DIRECTION_TYPE_RX,

    OAM_OTA_FRAME_DIRECTION_TYPE_BUTT
}oam_ota_frame_direction_type_enum;
typedef oal_uint8 oam_ota_frame_direction_type_enum_uint8;

typedef enum
{
    OAM_NL_CMD_SDT = 0,    /* SDT模块 */
    OAM_NL_CMD_HUT,        /* HUT模块 */
    OAM_NL_CMD_ALG,        /* ALG模块 */
    OAM_NL_CMD_ACS,        /* ACS模块 */
    OAM_NL_CMD_DAQ,
    OAM_NL_CMD_REG,        /* 寄存器读取模块 */

    OAM_NL_CMD_BUTT
}oam_nl_cmd_enum;
typedef oal_uint8 oam_nl_cmd_enum_uint8;

/* 特性宏的缩写见gst_oam_feature_list */
typedef enum
{
    OAM_SF_SCAN                 = 0,
    OAM_SF_AUTH,
    OAM_SF_ASSOC,
    OAM_SF_FRAME_FILTER,
    OAM_SF_WMM,

    OAM_SF_DFS                  = 5,
    OAM_SF_NETWORK_MEASURE,
    OAM_SF_ENTERPRISE_VO,
    OAM_SF_HOTSPOTROAM,
    OAM_SF_NETWROK_ANNOUNCE,

    OAM_SF_NETWORK_MGMT         = 10,
    OAM_SF_NETWORK_PWS,
    OAM_SF_PROXYARP,
    OAM_SF_TDLS,
    OAM_SF_CALIBRATE,

    OAM_SF_EQUIP_TEST           = 15,
    OAM_SF_CRYPTO,
    OAM_SF_WPA,
    OAM_SF_WEP,
    OAM_SF_WPS,

    OAM_SF_PMF                  = 20,
    OAM_SF_WAPI,
    OAM_SF_BA,
    OAM_SF_AMPDU,
    OAM_SF_AMSDU,

    OAM_SF_STABILITY            = 25,
    OAM_SF_TCP_OPT,
    OAM_SF_ACS,
    OAM_SF_AUTORATE,
    OAM_SF_TXBF,

    OAM_SF_DYN_RECV             = 30,                        /* dynamin recv*/
    OAM_SF_VIVO,                            /* video_opt voice_opt */
    OAM_SF_MULTI_USER,
    OAM_SF_MULTI_TRAFFIC,
    OAM_SF_ANTI_INTF,

    OAM_SF_EDCA                 = 35,
    OAM_SF_SMART_ANTENNA,
    OAM_SF_TPC,
    OAM_SF_TX_CHAIN,
    OAM_SF_RSSI,

    OAM_SF_WOW                  = 40,
    OAM_SF_GREEN_AP,
    OAM_SF_PWR,                             /* psm uapsd fastmode */
    OAM_SF_SMPS,
    OAM_SF_TXOP,

    OAM_SF_WIFI_BEACON          = 45,
    OAM_SF_KA_AP,                           /* keep alive ap */
    OAM_SF_MULTI_VAP,
    OAM_SF_2040,                            /* 20m+40m coex*/
    OAM_SF_DBAC,

    OAM_SF_PROXYSTA             = 50,
    OAM_SF_UM,                              /* user managment */
    OAM_SF_P2P,								/* P2P 特性 */
    OAM_SF_M2U,
    OAM_SF_IRQ,                             /* top half */

    OAM_SF_TX                   = 55,
    OAM_SF_RX,
    OAM_SF_DUG_COEX,
    OAM_SF_CFG,                             /* wal dmac config函数 */
    OAM_SF_FRW,                             /* frw层 */

    OAM_SF_KEEPALIVE            = 60,
    OAM_SF_COEX,
    OAM_SF_HS20                 = 62,	    /* HotSpot 2.0特性 */
    OAM_SF_MWO_DET,
    OAM_SF_CCA_OPT,

    OAM_SF_ROAM                 = 65,       /* roam module, #ifdef _PRE_WLAN_FEATURE_ROAM */
    OAM_SF_DFT,
    OAM_SF_DFR,
    OAM_SF_BACKUP,
    OAM_SF_ANY,                             /* rifs protection shortgi frag datarate countrycode
                                                coustom_security startup_time lsig monitor wds
                                                hidessid */
    OAM_SOFTWARE_FEATURE_BUTT
}oam_feature_enum;
typedef oal_uint8   oam_feature_enum_uint8;

typedef enum
{
    OAM_RATELIMIT_TYPE_PRINTK        = 0,
    OAM_RATELIMIT_TYPE_LOG,
    OAM_RATELIMIT_TYPE_DSCR,
    OAM_RATELIMIT_TYPE_FRAME_WLAN,
    OAM_RATELIMIT_TYPE_FRAME_ETH,
    OAM_RATELIMIT_TYPE_CB,
    OAM_RATELIMIT_TYPE_BUTT
}oam_ratelimit_type_enum;
typedef oal_uint8   oam_ratelimit_type_enum_uint8;

#define OAM_EXCP_STATS_TIMEOUT          (5000)
/* 该枚举类型不建议频繁添加,只适用于异常原因明确的分支,周期上报异常触发日志 */
typedef enum
{
    OAM_HAL_MAC_ERROR_PARA_CFG_ERR                  = 0,        /*描述符参数配置异常,包括AMPDU长度配置不匹配,AMPDU中MPDU长度超长,sub msdu num错误*/
    OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL          = 1,        /*接收非AMSDU帧长大于RxBuff大小异常*/
    OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND            = 2,        /*未找到BA会话表项异常0*/
    OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT             = 3,        /*PHY_RX_TRAILER超时*/
    OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN           = 4,        /*PHY_RX_FIFO满写异常*/
    OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK             = 5,        /*发送帧数据断流*/
    OAM_HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT             = 6,        /*RX_FSM状态机超时*/
    OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT             = 7,        /*TX_FSM状态机超时*/
    OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT         = 8,        /*RX_HANDLER状态机超时*/
    OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT         = 9,        /*TX_HANDLER状态机超时*/
    OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN          = 10,       /*TX 中断FIFO满写*/
    OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN          = 11,       /*RX中断 FIFO满写*/
    OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN        = 12,       /*HIRX中断FIFO满写*/
    OAM_HAL_MAC_ERROR_RX_Q_EMPTY                    = 13,       /*接收到普通优先级帧但此时RX BUFFER指针为空*/
    OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY                  = 14,       /*接收到高优先级帧但此时HI RX BUFFER指针为空*/
    OAM_HAL_MAC_ERROR_BUS_RLEN_ERR                  = 15,       /*总线读请求长度为0异常*/
    OAM_HAL_MAC_ERROR_BUS_RADDR_ERR                 = 16,       /*总线读请求地址无效异常*/
    OAM_HAL_MAC_ERROR_BUS_WLEN_ERR                  = 17,       /*总线写请求长度为0异常*/
    OAM_HAL_MAC_ERROR_BUS_WADDR_ERR                 = 18,       /*总线写请求地址无效异常*/
    OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN             = 19,       /*tx acbk队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN             = 20,       /*tx acbe队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN             = 21,       /*tx acvi队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN             = 22,       /*tx acv0队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN            = 23,       /*tx hipri队列fifo满写*/
    OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT           = 24,       /*matrix计算超时*/
    OAM_HAL_MAC_ERROR_CCA_TIMEOUT                   = 25,       /*cca超时*/
    OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP             = 26,       /*数采overlap告警*/
    OAM_HAL_MAC_ERROR_BEACON_MISS                   = 27,       /*连续发送beacon失败*/
    OAM_HAL_MAC_ERROR_UNKOWN_28                     = 28,
    OAM_HAL_MAC_ERROR_UNKOWN_29                     = 29,
    OAM_HAL_MAC_ERROR_UNKOWN_30                     = 30,
    OAM_HAL_MAC_ERROR_UNKOWN_31                     = 31,

    OAM_HAL_SOC_ERROR_BUCK_OCP                      = 32,       /* PMU BUCK过流中断 */
    OAM_HAL_SOC_ERROR_BUCK_SCP,                                 /* PMU BUCK短路中断 */
    OAM_HAL_SOC_ERROR_OCP_RFLDO1,                               /* PMU RFLDO1过流中断 */
    OAM_HAL_SOC_ERROR_OCP_RFLDO2,                               /* PMU RFLDO2过流中断 */
    OAM_HAL_SOC_ERROR_OCP_CLDO,                                 /* PMU CLDO过流中断 */
    OAM_HAL_SOC_ERROR_RF_OVER_TEMP,                             /* RF过热中断 */
    OAM_HAL_SOC_ERROR_CMU_UNLOCK,                               /* CMU PLL失锁中断 */
    OAM_HAL_SOC_ERROR_PCIE_SLV_ERR,

    OAM_EXCP_TYPE_BUTT
}oam_excp_type_enum;
typedef oal_uint8   oam_excp_type_enum_uint8;

typedef enum
{
    OAM_EXCP_STATUS_INIT = 0,            /* 初始状态:上报完成后切换至初始状态 */
    OAM_EXCP_STATUS_REFRESHED,           /* 有更新，可上报； */
    OAM_EXCP_STATUS_BUTT
}oam_excp_status_enum;
typedef oal_uint8   oam_excp_status_enum_uint8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* 维测，下发调试类型值，代码可临时根据调测值实现相应功能 */
#ifdef _PRE_DEBUG_MODE
extern oal_uint32   g_aul_debug_feature_switch[];

#define             MAX_DEBUG_TYPE_NUM              OAM_DEBUG_TYPE_BUTT
typedef enum
{
    OAM_DEBUG_TYPE_ECHO_REG          = 0,

    OAM_DEBUG_TYPE_BUTT
}oam_debug_type_enum;

#endif

#ifdef _PRE_WLAN_DFT_STAT
typedef enum
{
    OAM_STATS_PHY_NODE_TX_CNT = 1,
    OAM_STATS_PHY_NODE_RX_OK_CNT,
    OAM_STATS_PHY_NODE_SYN_CNT,
    OAM_STATS_PHY_NODE_OFDM_SYN_ERR_CNT,
    OAM_STATS_PHY_NODE_AGC_LOCK_CNT,
    OAM_STATS_PHY_NODE_11B_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_OFDM_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_UNSUPPORTED_CNT,
    OAM_STATS_PHY_NODE_CARRIER_LOSE_CNT,
    OAM_STATS_PHY_NODE_LDPC_FAIL_CNT,
    OAM_STATS_PHY_NODE_RX_TIMEOUT_CNT,
    OAM_STATS_PHY_NODE_HI_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_LO_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_LARGER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_SMALLER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_EQUAL_CNT,

    OAM_STATS_PHY_NODE_BUTT
}oam_stats_phy_node_idx_enum;
typedef oal_uint8 oam_stats_phy_node_idx_enum_uint8;
#endif

extern oal_uint8 g_auc_bcast_addr[WLAN_MAC_ADDR_LEN];
#define BROADCAST_MACADDR       g_auc_bcast_addr

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
typedef oal_int32   (* oam_sdt_up_func)(oal_netbuf_stru *pst_netbuf);
typedef oal_int32   (* oam_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
typedef oal_int32   (* oam_sdt_status_func)(oal_void);

/* 其他模块调用SDT钩子函数 用结构体 */
typedef struct
{
    oal_int32       (* p_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
    oal_int32       (* p_sdt_get_wq_len_func)(oal_void);
}oam_sdt_func_hook_stru;

/* 外部函数声明 */
extern oam_sdt_func_hook_stru       g_st_oam_sdt_func_hook;

/* 其他模块调用WAL钩子函数 用结构体 */
typedef struct
{
   oal_int32       (* p_wal_recv_mem_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_reg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_cfg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_global_var_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
}oam_wal_func_hook_stru;

extern oam_wal_func_hook_stru       g_st_oam_wal_func_hook;

/*lint -e958*/ /*lint -e959*/
/* 读取和设置全局变量的结构体 */
typedef struct
{
    oal_uint32  ul_offset;
    oal_uint8   uc_lenth;
    oal_uint8   uc_mode;
    oal_uint8   auc_val[4];
    oal_uint8   auc_var_name[4];
}oal_sdt_global_var_stru;
/*lint -e958*/ /*lint -e959*/

/* VAPID 日志级别结构体 */
typedef struct
{
    oam_feature_enum_uint8              en_feature_id;
    oam_log_level_enum_uint8            en_log_level;
    oal_switch_enum_uint8               en_switch;
    oal_uint8                           uc_resv;
}oam_cfg_log_level_stru;

typedef struct
{
    oal_uint8    bit_vap_id      :  4;
    oal_uint8    bit_log_level   :  4;
}oam_vap_log_level_stru;

/* 日志消息结构体 */
typedef struct
{
    oam_vap_log_level_stru              st_vap_log_level;   /* vapid + loglevel */
    oam_feature_enum_uint8              en_feature_id;       /* 特性id */
    oal_uint16                          us_resv;
    oal_uint16                          us_file_id;         /* 文件号 */
    oal_uint16                          us_line_num;        /* 行号 */
    oal_uint32                          ul_tick;            /* 时间戳，精度ms */
    oal_int32                           al_param[OAM_LOG_ENTRY_PARA_NUM];
}oam_log_info_stru;

/* oam模块保存的日志 */
typedef struct
{
    oam_log_info_stru                ast_log_info[OAM_LOG_INFO_IN_MEM_MAX_NUM];
    oal_uint16                       us_index;               /* 当前刚保存的log在数组中的位置 */
}oam_log_info_in_mem_stru;

/*  oam流控结构体
    流控的实现原理具体参考 oam_log_ratelimit函数实现
*/
typedef struct
{
    oal_spin_lock_stru              spin_lock;
    oal_switch_enum_uint8           en_ratelimit_switch; /* 流控控制开关 */
    oal_uint32                      ul_interval;         /* 流控时间范围 */
    oal_uint32                      ul_burst;            /* 流控流量值 */
    oal_uint32                      ul_printed;          /* 满足流控条件输出记录 */
    oal_uint32                      ul_missed;           /* 不满足流控条件屏蔽记录 */
    oal_uint32                      ul_begin;            /* 本次流控起始时间 */
}oam_ratelimit_stru;

/* 定时器创建删除追踪信息结构 */
typedef struct
{
    oal_uint32                      ul_file_id;
    oal_uint32                      ul_line_num;
    oam_timer_track_type_enum_uint8 en_type;
    oal_uint8                       auc_resv[3];
}oam_timer_track_info_stru;

/* 上报mpdu数目结构 */
typedef struct
{
    oal_uint16              us_total_mpdu_num_in_device;   /* device下所有TID中总共的mpdu_num数量 */
    oal_uint16              us_mpdu_num_in_tid0;
    oal_uint16              us_mpdu_num_in_tid1;
    oal_uint16              us_mpdu_num_in_tid2;
    oal_uint16              us_mpdu_num_in_tid3;
    oal_uint16              us_mpdu_num_in_tid4;
    oal_uint16              us_mpdu_num_in_tid5;
    oal_uint16              us_mpdu_num_in_tid6;
    oal_uint16              us_mpdu_num_in_tid7;
    oal_uint8               auc_resv[2];
}oam_report_mpdu_num_stru;

/* OTA头部信息 */
typedef struct
{
    oal_uint32                              ul_tick;            /* 时间戳，精度ms */
    oam_ota_type_enum_uint8                 en_ota_type;        /* OTA类型 */
    oal_uint8                               uc_frame_hdr_len;   /* 如果是帧，代表帧头长度；如果是其它类型，此字段没有用 */
    oal_uint16                              us_ota_data_len;    /* OTA数据长度，如果是帧，代表帧头和帧体的总长度 */
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction; /* 表明帧是属于发送流程还是接收流程，只有ota_type是帧的时候这个字段才有意义 */
    oal_uint8                               auc_resv[1];
}oam_ota_hdr_stru;

/* OTA数据结构体 */
typedef struct
{
    oam_ota_hdr_stru                st_ota_hdr;         /* OTA头部信息 */
    oal_uint8                       auc_ota_data[4];    /* OTA数据 */
}oam_ota_stru;

/* 消息上报给SDT封装的结构体 */
/* EVENT消息体最大长度 */
#define OAM_EVENT_INFO_MAX_LEN          48

typedef struct
{
    oal_uint32				         ul_tick;                            /* 消息时间 */
    oam_event_type_enum_uint16	     en_event_type;                      /* 消息类型，WID，抛事件，状态转移等 */
 	oam_module_id_enum_uint16        en_module;                          /* 模块 */
 	oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                        uc_vap_id;                          /* vap id */
    oal_uint8                        auc_resv[1];                        /* 保留 */
}oam_event_hdr_stru;

typedef struct
{
    oam_event_hdr_stru               st_event_hdr;         /* EVENT头部信息 */
	oal_int8                         auc_event_info[OAM_EVENT_INFO_MAX_LEN];  /* 消息内容，最多保存50个字节 */
}oam_event_stru;


#define OAM_EVENT_STRU_SIZE         OAL_SIZEOF(oam_event_stru)

/* 内存池使用信息查询 */
typedef struct
{
    oal_uint8                               uc_mem_pool_id;
    oal_uint8                               uc_subpool_id;
    oal_uint8                               auc_resv[2];
    oal_uint16                              us_mem_pool_total_cnt;
    oal_uint16                              us_mem_pool_used_cnt;
    oal_uint16                              us_subpool_total_cnt;
    oal_uint16                              us_subpool_free_cnt;
}oam_stats_mempool_stru;

/* 内存块使用信息，包括标准内存块信息，和任意某一块连续内存信息 */
typedef struct
{
    oal_uint8                               uc_pool_id;                 /* 如果是任意连续内存 */
    oal_uint8                               uc_subpool_id;
    oal_uint8                               uc_user_cnt;                /* 本内存块的引用计数 */
    oal_uint8                               auc_resv[1];
    oal_uint32                              ul_file_id;                 /* 申请该内存块的文件号 */
    oal_uint32                              ul_alloc_line_num;          /* 申请该内存块的行号 */
}oam_memblock_info_stru;

/* 事件队列使用情况信息结构体 */
typedef struct
{
    oal_uint8							    en_type;                    /* 事件类型 */
    oal_uint8                               uc_sub_type;                /* 事件子类型 */
    oal_uint16                              us_length;                  /* 事件长度 */
    oal_uint8                               en_pipeline;                /* 事件分段号 */
    oal_uint8                               uc_chip_id;                 /* 芯片ID */
    oal_uint8                               uc_device_id;               /* 设备ID */
    oal_uint8                               uc_vap_id;                  /* VAP ID */
}oam_event_hdr_info_stru;

/* 上报给SDT事件队列使用情况信息 */
typedef struct
{
    oal_uint8                               uc_event_num_in_queue;      /* 当前事件队列中事件的个数 */
    oal_uint8                               auc_resv[3];

    oam_event_hdr_info_stru                 ast_event_hdr_info[OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE];
}oam_event_queue_info_stru;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* 单用户跟踪  用户能力变化上报sdt结构 */
typedef struct
{
    oal_uint32                              ul_val_before_change;   /* 变化前的值 */
    oal_uint32                              ul_val_after_change;    /* 变化后的值 */
    oam_user_info_change_type_enum_uint8    en_change_type;         /* 用户的何种能力或者状态变化了 */
    oal_uint8                               auc_resv[3];
}oam_user_info_change_stru;

/* 最优速率统计参数结构 */
typedef struct
{
    oal_uint32      ul_best_rate_kbps;          /* 统计周期内的最优速率 */
    oal_uint16      us_best_rate_per;           /* 统计周期内最优速率下的平均per */
    oal_uint8       uc_best_rate_aggr_num;      /* 统计周期内最优速率的aggr */
    oal_uint8       uc_resv;
}oam_best_rate_stat_stru;

/* 单用户跟踪，影响用户实时吞吐的参数结构 */
typedef struct
{
    oal_int8                                c_avg_tx_rssi;         /* 发送平均rssi */
    oal_int8                                c_avg_rx_rssi;         /* 接收平均rssi */
    oal_uint16                              us_avg_rx_aggr_num;    /* 接收平均聚合个数,device级别 */
    oal_uint32                              ul_avg_tx_rate;        /* 统计周期内发送平均速率 */
    oal_uint32                              ul_avg_rx_rate;        /* 统计周期内接收平均速率 */
    oam_best_rate_stat_stru                 ast_best_rate_stat[WLAN_WME_AC_BUTT];    /* 统计周期内最优速率，平均per，平均发送聚合长度 */
}oam_user_track_thrput_param_stru;

/* 统计接收ampdu平均聚合个数结构 */
typedef struct
{
    oal_bool_enum_uint8                     en_flg;                 /* 是否统计 */
    oal_uint8                               auc_resv[1];
    oal_uint16                              us_rx_ampdu_num;        /* 统计周期内接收ampdu个数 */
    oal_uint32                              ul_rx_mpdu_in_ampdu;    /* 统计周期内接收到属于ampdu的mpdu个数 */
}oam_user_track_rx_ampdu_stat;
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/* 设备级别统计信息结构体 */
typedef struct
{
    /**************************************************************************
                               中断个数统计信息
    **************************************************************************/
    /* 总的中断请求个数 */
    oal_uint32  ul_irq_cnt;

    /* SOC五类中断计数 */
    oal_uint32  ul_pmu_err_irq_cnt;                 /* 电源错误中断 */
    oal_uint32  ul_rf_over_temp_irq_cnt;            /* RF过热中断 */
    oal_uint32  ul_unlock_irq_cnt;                  /* CMU PLL失锁中断 */
    oal_uint32  ul_mac_irq_cnt;                     /* Mac业务中断 */
    oal_uint32  ul_pcie_slv_err_irq_cnt;            /* PCIE总线错误中断 */

    /* pmu/buck错误子中断源计数 */
    oal_uint32  ul_buck_ocp_irq_cnt;                /* BUCK过流中断 */
    oal_uint32  ul_buck_scp_irq_cnt;                /* BUCK短路中断 */
    oal_uint32  ul_ocp_rfldo1_irq_cnt;              /* PMU RFLDO1过流中断 */
    oal_uint32  ul_ocp_rfldo2_irq_cnt;              /* PMU RFLDO2过流中断 */
    oal_uint32  ul_ocp_cldo_irq_cnt;                /* PMU CLDO过流中断 */

    /* MAC子中断源计数(与MACINTERRUPT_STATUS寄存器对应) */
    oal_uint32  ul_rx_complete_cnt;                 /* 数据帧接收完成 */
    oal_uint32  ul_tx_complete_cnt;                 /* 发送完成 */
    oal_uint32  ul_hi_rx_complete_cnt;              /* 管理帧、控制帧接收完成 */
    oal_uint32  ul_error_cnt;                       /* error中断 */
    oal_uint32  aul_tbtt_cnt[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];/* tbtt中断,0~3代表ap的，4代表sta的 */
    oal_uint32  ul_abort_intr_start;
    oal_uint32  ul_abort_intr_end;
    oal_uint32  ul_radar_detect_cnt;                /* 检测到雷达 */
    oal_uint32  ul_pa_tx_suspended;
    oal_uint32  ul_de_authentication;
    oal_uint32  ul_one_packet;
    oal_uint32  ul_abort_intr_done;
    oal_uint32  ul_ch_statistics_cnt;               /* 信道统计完成中断 */
    oal_uint32  ul_wow_prep_done;
    oal_uint32  ul_other_int_cnt;                   /* 其它 */

    /* MAC错误中断类型, 注意此处枚举值与错误中断状态寄存器的位一一对应 ! */
    oal_uint32  aul_mac_error_cnt[OAM_MAC_ERROR_TYPE_CNT];

    /* 接收中断上报频度统计 */
    oal_uint32  ul_normal_rx_idx;                   /* 当前中断时间戳所在位置 */
    oal_uint32  ul_hi_rx_idx;                       /* 当前中断时间戳所在位置 */
    oal_uint32  aul_rx_freq[OAM_RX_DSCR_QUEUE_CNT][OAM_IRQ_FREQ_STAT_MEMORY];   /* 接收频度统计，时间戳精度10ns */
    oal_uint32  ul_rx_freq_stop_flag;               /* 接收频度标志，一旦上报fifo overun之后则停止统计 */

    /* 中断时延统计, 单位10ns */
    oal_uint32  ul_max_delay;                       /* 最大时长 */
    oal_uint32  ul_min_delay;                       /* 最小时长 */
    oal_uint32  ul_delay_sum;                       /* 总时长 */
    oal_uint32  ul_timer_start;                     /* 开始时间记录 */
}oam_device_stat_info_stru;

/* VAP级别统计信息结构 */
typedef struct
{
    /***************************************************************************
                                接收包统计
    ***************************************************************************/

    /* 发往lan的数据包统计 */
    oal_uint32  ul_rx_pkt_to_lan;                               /* 接收流程发往以太网的数据包数目，MSDU */
    oal_uint32  ul_rx_bytes_to_lan;                             /* 接收流程发往以太网的字节数 */

    /* 接收流程遇到严重错误(描述符异常等)，释放所有MPDU的统计 */
    oal_uint32  ul_rx_ppdu_dropped;                             /* 硬件上报的vap_id错误，释放的MPDU个数 */

    /* 软件统计的接收到MPDU个数，正常情况下应该与MAC硬件统计值相同 */
    oal_uint32  ul_rx_mpdu_total_num;                           /* 接收流程上报到软件进行处理的MPDU总个数 */

    /* MPDU级别进行处理时发生错误释放MPDU个数统计 */
    oal_uint32  ul_rx_ta_check_dropped;                         /* 检查发送端地址异常，释放一个MPDU */
    oal_uint32  ul_rx_da_check_dropped;                         /* 检查目的端地址异常，释放一个MPDU */
    oal_uint32  ul_rx_phy_perform_dropped;                      /* 测试phy性能，将帧直接释放 */
    oal_uint32  ul_rx_key_search_fail_dropped;                  /*  */
    oal_uint32  ul_rx_tkip_mic_fail_dropped;                    /* 接收描述符status为 tkip mic fail释放MPDU */
    oal_uint32  ul_rx_replay_fail_dropped;                      /* 重放攻击，释放一个MPDU */
    oal_uint32  ul_rx_11i_check_fail_dropped;
    oal_uint32  ul_rx_wep_check_fail_dropped;
    oal_uint32  ul_rx_alg_process_dropped;                      /* 算法处理返回失败 */
    oal_uint32  ul_rx_null_frame_dropped;                       /* 接收到空帧释放(之前节能特性已经对其进行处理) */
    oal_uint32  ul_rx_abnormal_dropped;                         /* 其它异常情况释放MPDU */
    oal_uint32  ul_rx_mgmt_abnormal_dropped;                    /* 接收到管理帧出现异常，比如vap或者dev为空等 */
    oal_uint32  ul_rx_ack_dropped;                              /* ack直接过滤掉 */
    oal_uint32  ul_rx_pspoll_process_dropped;                   /* 处理ps-poll的时候释放包 */
    oal_uint32  ul_rx_bar_process_dropped;                      /* 处理block ack req释放包 */
    oal_uint32  ul_rx_abnormal_cnt;                             /* 处理MPDU时发现异常的次数，并非丢包数目 */

    oal_uint32  ul_rx_no_buff_dropped;                          /* 组播帧或者wlan_to_wlan流程申请buff失败 */
    oal_uint32  ul_rx_defrag_process_dropped;                   /* 去分片处理失败 */
    oal_uint32  ul_rx_de_mic_fail_dropped;                      /* mic码校验失败 */
    oal_uint32  ul_rx_portvalid_check_fail_dropped;             /* 接收到数据帧，安全检查失败释放MPDU */

    /* 接收到组播帧个数 */
    oal_uint32  ul_rx_mcast_cnt;

    /* 管理帧统计 */
    oal_uint32  aul_rx_mgmt_num[WLAN_MGMT_SUBTYPE_BUTT];        /* VAP接收到各种管理帧的数目统计 */


    /***************************************************************************
                                发送包统计
    ***************************************************************************/

    /* 从lan接收到的数据包统计 */
    oal_uint32  ul_tx_pkt_num_from_lan;                         /* 从lan过来的包数目,MSDU */
    oal_uint32  ul_tx_bytes_from_lan;                           /* 从lan过来的字节数 */

    /* 发送流程发生异常导致释放的数据包统计，MSDU级别 */
    oal_uint32  ul_tx_abnormal_msdu_dropped;                    /* 异常情况释放MSDU个数，指vap或者user为空等异常 */
    oal_uint32  ul_tx_security_check_faild;                     /* 安全检查失败释放MSDU */
    oal_uint32  ul_tx_abnormal_mpdu_dropped;                    /* 异常情况释放MPDU个数，指vap或者user为空等异常 */
    oal_uint32  ul_tx_uapsd_process_dropped;                    /* UAPSD特性处理失败，释放MPDU个数 */
    oal_uint32  ul_tx_psm_process_dropped;                      /* PSM特性处理失败，释放MPDU个数 */
    oal_uint32  ul_tx_alg_process_dropped;                      /* 算法处理认为应该丢包，释放MPDU个数 */

    /* 发送完成中发送成功与失败的数据包统计，MPDU级别 */
    oal_uint32  ul_tx_mpdu_succ_num;                            /* 发送MPDU总个数 */
    oal_uint32  ul_tx_mpdu_fail_num;                            /* 发送MPDU失败个数 */
    oal_uint32  ul_tx_ampdu_succ_num;                           /* 发送成功的AMPDU总个数 */
    oal_uint32  ul_tx_ampdu_bytes;                              /* 发送AMPDU总字节数 */
    oal_uint32  ul_tx_mpdu_in_ampdu;                            /* 属于AMPDU的MPDU发送总个数 */
    oal_uint32  ul_tx_ampdu_fail_num;                           /* 发送AMPDU失败个数 */
    oal_uint32  ul_tx_mpdu_fail_in_ampdu;                       /* 属于AMPDU的MPDU发送失败个数 */

    /* 组播转单播发送流程统计 */
    oal_uint32  ul_tx_m2u_ucast_cnt;                            /* 组播转单播 单播发送成功个数 */
    oal_uint32  ul_tx_m2u_ucast_droped;                         /* 组播转单播 单播发送失败个数 */
    oal_uint32  ul_tx_m2u_mcast_cnt;                            /* 组播转单播 组播发送成功个数 */
    oal_uint32  ul_tx_m2u_mcast_droped;                         /* 组播转单播 组播发送成功个数 */

    /* 管理帧统计 */
    oal_uint32  aul_tx_mgmt_num_sw[WLAN_MGMT_SUBTYPE_BUTT];     /* VAP挂到硬件队列上的各种管理帧的数目统计 */
    oal_uint32  aul_tx_mgmt_num_hw[WLAN_MGMT_SUBTYPE_BUTT];     /* 发送完成中各种管理帧的数目统计 */
}oam_vap_stat_info_stru;

/* USER级别统计信息结构 */
typedef struct
{
    /* 接收包统计，从某个用户处接收到的包统计(TO DS) */
    oal_uint32  ul_rx_mpdu_num;                                 /* 从某个用户接收到的MPDU数目 */

    /* 发送包统计，发送给某个用户的包统计(FROM DS)，粒度是TID(具体到从VAP的某个TID发出) */
    oal_uint32  aul_tx_mpdu_succ_num[WLAN_TIDNO_BUTT];          /* 发送MPDU总个数 */
    oal_uint32  aul_tx_mpdu_fail_num[WLAN_TIDNO_BUTT];          /* 发送MPDU失败个数 */
    oal_uint32  aul_tx_ampdu_succ_num[WLAN_TIDNO_BUTT];         /* 发送AMPDU总个数 */
    oal_uint32  aul_tx_ampdu_bytes[WLAN_TIDNO_BUTT];            /* 发送AMPDU总字节数 */
    oal_uint32  aul_tx_mpdu_in_ampdu[WLAN_TIDNO_BUTT];          /* 属于AMPDU的MPDU发送总个数 */
    oal_uint32  aul_tx_ampdu_fail_num[WLAN_TIDNO_BUTT];         /* 发送AMPDU失败个数 */
    oal_uint32  aul_tx_mpdu_fail_in_ampdu[WLAN_TIDNO_BUTT];     /* 属于AMPDU的MPDU发送失败个数 */
}oam_user_stat_info_stru;

/* 统计结构信息，包括设备级别，vap级别，user级别的各种统计信息 */
typedef struct
{
    /* 设备级别的统计信息 */
    oam_device_stat_info_stru               ast_dev_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];

    /* VAP级别的统计信息 */
    oam_vap_stat_info_stru                  ast_vap_stat_info[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    /* USER级别的统计信息 */
    oam_user_stat_info_stru                 ast_user_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM];
}oam_stat_info_stru;
#endif

#if 0
typedef struct
{
    /*类型*/
    oal_bool_enum_uint8 en_is_before_tx_track;

    /*tid队列相关信息*/
    oal_uint8       uc_tid;                    /*tid*/
    oal_uint16      us_tid_total_mpdu_num;     /*tid队列中总的mpdu数目*/
    oal_uint8       uc_tid_retry_mpdu_num;     /*tid队列中存在多少个重传mpdu*/
    oal_uint8       uc_tid_record_mpdu_num;    /*aus_tid_seqnum中记录了tid队列中多少个mpdu的seqnum*/
    oal_uint16      aus_tid_seqnum[32];        /*保存tid队列中的seqnum*/

    /*ba handle中相关信息*/
    oal_uint32      aul_bitmap[4];             /*ba handle中的bitmap*/
    oal_uint16      us_seq_start;
    oal_uint16      us_lsn;
    oal_uint16      us_baw_head;
    oal_uint16      us_baw_tail;

    union
    {
        struct
        {
            /*调度出的描述符链信息*/
            oal_uint16      aus_schedule_seqnum[32];
            oal_uint8       uc_schedule_mpdu_num;
            oal_uint8       auc_resv0[3];
        } st_schedule;
        struct
        {
            /*发送完成上报的描述符链信息*/
            oal_uint16      aus_report_seqnum[32];     /*发送完成描述符链seqnum*/
            oal_uint8       uc_report_mpdu_num;        /*发送完成的mpdu数目*/
            oal_uint8       uc_tx_status;              /*发送完成描述符状态*/
            oal_uint8       auc_resv1[2];
        } st_report;

    } un_mix_dscr;

}oam_seq_track_stru;
#endif

/*lint -e717*/
#define OAM_SDT_STAT_INCR(_cnt)             do{g_st_sdt_stat_info._cnt++;} while(0)

enum oam_filter_type_enum
{
    OAM_FLT_PASS = 0,
    OAM_FLT_DROP,
    OAM_FLT_BUTT,
};

typedef struct
{
    oal_uint32      ul_nlk_sd_cnt;         /* 上报消息总数:含失败个数*/
    oal_uint32      ul_nlk_sd_fail;        /* 发送失败统计 */
    oal_uint32      ul_wq_len;              /* 队列中消息个数 */
    oal_uint32      ul_filter_cnt;          /* 过滤消息个数 */
    oal_bool_enum   en_filter_switch;       /* 过滤开关状态 */
	oal_uint8		uc_recv[3];
}oam_sdt_stat_info_stru;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
extern oam_stat_info_stru g_st_stat_info;
#endif
extern oam_sdt_stat_info_stru g_st_sdt_stat_info;

/* 保存配置文件相关信息结构 */
typedef struct
{
    oam_cfg_type_enum_uint16            en_cfg_type;
    oal_int8                           *pc_section;                /* 配置项所属的section字符串 */
    oal_int8                           *pc_key;                    /* 配置项在配置文件中的字符串表示 */
    oal_int32                           l_val;                     /* 配置项的值 */
}oam_cfg_data_stru;


#ifdef _PRE_DEBUG_MODE
typedef struct
{
    /* 用于统计发送完成中断是否丢失(非聚合) */
    oal_uint32          ul_tx_data_num;           /* 放入硬件队列的非聚合帧个数 */
    oal_uint32          ul_tx_mgnt_num;           /* 发送管理帧的个数 */
    oal_uint32          ul_tx_complete_total_num; /* 所有发送完成中断的个数 */
    oal_uint32          ul_tx_complete_uh1_num;   /* 发送完成中断上半部统计次数1(函数入口处) */
    oal_uint32          ul_tx_complete_uh2_num;   /* 发送完成中断上半部统计次数2(函数出口处) */
    oal_uint32          ul_tx_complete_bh1_num;   /* 发送完成中断下半部统计次数1(函数入口处) */
    oal_uint32          ul_tx_complete_bh2_num;   /* 发送完成中断下半部统计次数2(函数出口处) */
    oal_uint32          ul_tx_complete_bh3_num;   /* 发送完成中断下半部统计次数3(释放netbuf处) */
}oam_tx_complete_stat_stru;
#endif

/* 异常统计结构体:当ul_reported_cnt与ul_record_cnt相同时*/
typedef struct
{
    oal_uint32              en_status;                 /* 每类异常类型是否刷新 */
    oal_uint32              ul_record_cnt;             /* 记录上一次更新的次数 */
}oam_excp_record_stru;

/* oam异常统计 */
typedef struct
{
    oal_uint32                          en_status;                 /* VAP级别异常统计是否有刷新*/
    oam_excp_record_stru                ast_excp_record_tbl[OAM_EXCP_TYPE_BUTT];
}oam_exception_ctx_stru;

/* VAP日志开关与特性日志级别 */
typedef struct
{
    oal_switch_enum_uint8     aen_vap_log_switch[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];    /* VAP日志开关 */
    oam_log_level_enum_uint8  aen_vap_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];     /* VAP日志开关，INFO级别关闭时恢复 */
    oam_log_level_enum_uint8  aen_feature_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT][OAM_SOFTWARE_FEATURE_BUTT]; /* 特性日志级别 */
}oam_vap_log_stru;

#define OAM_RATELIMIT_MAX_INTERVAL                    60         /* 60秒 */
#define OAM_RATELIMIT_MIN_INTERVAL                    1          /* 1秒 */
#define OAM_RATELIMIT_DEFAULT_INTERVAL                5          /* 秒 间隔 */
#define OAM_RATELIMIT_MAX_BURST                       60         /* 最大允许打印条数 */
#define OAM_RATELIMIT_MIN_BURST                       1          /* 最大允许打印条数 */
#define OAM_RATELIMIT_DEFAULT_BURST                   10         /* 最大允许打印条数 */

/* 日志模块全局结构体 */
typedef struct
{
    oal_switch_enum_uint8               en_global_log_switch;                               /* 日志全局开关 */
    oam_vap_log_stru                    st_vap_log_info;                                    /* VAP日志开关与特性日志级别 */
    oam_ratelimit_stru                  st_ratelimit[OAM_RATELIMIT_TYPE_BUTT];                                       /* 普通printk流控信息 */
}oam_log_ctx_stru;

/* OAM的EVENT模块的整体控制结构上下文 */
typedef struct
{
    oal_switch_enum_uint8           en_event_switch;                            /* 启动EVENT功能开关 */
    oal_uint8                       auc_resv[3];
}oam_event_ctx_stru;

/* OAM的event模块，具体某一种event的控制开关 */
typedef struct
{
    oal_switch_enum_uint8           aen_specific_event_switch[OAM_EVENT_TYPE_BUTT];
    oal_uint8                       auc_resv[1];
}oam_specific_event_ctx_stru;

/* oam的ota模块，具体某一种ota的控制开关 */
typedef struct
{
#if 0
    oal_switch_enum_uint8           aen_ota_switch[OAM_OTA_TYPE_BUTT];
#endif
    oam_sdt_print_beacon_rxdscr_type_enum_uint8           en_beacon_switch;
    oal_switch_enum_uint8           en_rx_dscr_switch;
//    oal_uint8                       auc_resv[2];
}oam_ota_ctx_stru;

/* OAM的ALARM模块的整体控制结构上下文 */
typedef struct
{
    oal_switch_enum_uint8           en_alarm_switch;                            /* 启动ALARM功能开关 */
    oal_uint8                       auc_resv[3];
}oam_alarm_ctx_stru;

/* 80211帧上报控制结构 */
typedef struct
{
    oal_switch_enum_uint8           en_frame_content_switch;
    oal_switch_enum_uint8           en_frame_cb_switch;
    oal_switch_enum_uint8           en_frame_dscr_switch;
    oal_uint8                       auc_resv[1];
}oam_80211_frame_ctx_stru;

/* 单用户跟踪控制开关结构 */
typedef struct
{
    oam_80211_frame_ctx_stru   ast_80211_mcast_mgmt_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];          /* 80211广播\组播管理帧上报控制结构 */
    oam_80211_frame_ctx_stru   ast_80211_mcast_data_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];          /* 80211广播\组播数据帧上报控制结构 */
    oam_80211_frame_ctx_stru   ast_80211_ucast_mgmt_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 单播帧开关，不同用户开关可以不同 */
    oam_80211_frame_ctx_stru   ast_80211_ucast_data_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 单播帧开关，不同用户开关可以不同 */
    oam_80211_frame_ctx_stru   aen_80211_probe_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* probe request和probe response太多，单独搞个开关*/
    oal_switch_enum_uint8      aen_eth_data_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oal_switch_enum_uint8      en_tx_mcast_dhcp_arp_switch;
    oal_switch_enum_uint8      aen_data_global_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 数据帧流程打印总开关，只要有一个用户的数据开关打开，总开关就开，否则关闭，避免消耗mips */
    oal_switch_enum_uint8      aen_user_info_change_switch[OAM_USER_INFO_CHANGE_TYPE_BUTT];
}oam_user_track_ctx_stru;

#define OAM_FILE_PATH_LENGTH            256                     /* 用于保存LOG文件地址的字符串最大长度,路径最长为255字节，最后需要有一字节存放\0 */

typedef struct
{
    oal_uint8                       auc_resv[3];
    oam_output_type_enum_uint8      en_output_type;                             /* 输出方式 */
    oal_int8                        ac_file_path[OAM_FILE_PATH_LENGTH];         /* 保存可维可测文件的地址 */

    /* LOG模块管理上下文 */
    oam_log_ctx_stru                st_log_ctx;

    /* EVENT模块管理上下文 */
    oam_event_ctx_stru              ast_event_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    /* 某一种具体的event控制结构 */
    oam_specific_event_ctx_stru     ast_specific_event_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    /* 某一种OTA消息的控制结构 */
    oam_ota_ctx_stru                ast_ota_ctx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    oam_exception_ctx_stru          st_exception_ctx;

	/* 单用户跟踪管理上下文 */
    oam_user_track_ctx_stru         st_user_track_ctx;
}oam_mng_ctx_stru;

/******************************************************************************
                          统计与性能维测相关的结构定义
*******************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

/* 反应空口环境繁忙程度的参数结构，有PHY的参数也有MAC的参数 */
typedef struct
{
    oal_uint16          us_mac_ch_stats_period_us;                    /* mac进行信道空闲时间统计的周期，20ms，20000us */
    oal_uint16          us_mac_pri20_free_time_us;                    /* 统计周期内主20M信道空闲时间，us */
    oal_uint16          us_mac_pri40_free_time_us;                    /* 统计周期内主40M信道空闲时间，us */
    oal_uint16          us_mac_pri80_free_time_us;                    /* 统计周期内主80M信道空闲时间,us */
    oal_uint16          us_mac_ch_rx_time_us;                         /* 统计周期内接收占用的时间，us */
    oal_uint16          us_mac_ch_tx_time_us;                         /* 统计周期内发送占用的时间，us */

    oal_uint8           uc_phy_ch_estimate_time_ms;                   /* phy测量信道空闲时功率的周期，ms */
    oal_int8            c_phy_pri20_idle_power_dBm;                   /* 统计周期内主20M信道空闲时的功率，一直不空闲就不统计 */
    oal_int8            c_phy_pri40_idle_power_dBm;                   /* 统计周期内主40M信道空闲时的功率，一直不空闲就不统计 */
    oal_int8            c_phy_pri80_idle_power_dBm;                   /* 统计周期内主80M信道空闲时的功率，一直不空闲就不统计 */

    oal_uint32          aul_beacon_miss_max_num[WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE]; /* mac记录的每个AP BEACON MISS历史最大值 */
    oal_uint32          ul_non_directed_frame_num;
}oam_stats_dbb_env_param_stru;

/* phy统计节点设置，保存节点idx的结构 */
typedef struct
{
    oal_uint8           auc_node_idx[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];
}oam_stats_phy_node_idx_stru;

/* phy的收发包数目统计值，包括用户指定需要的4个，和phy一直统计的8个按照协议模式的统计值 */
typedef struct
{
    oal_uint32          aul_user_requested_stat_cnt[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];

    /* phy统计的接收到11b,ht,vht,legecy ofdm帧正确和错误的个数 */
    oal_uint32          aul_phy_stat_rx_ppdu_cnt[OAM_PHY_STAT_RX_PPDU_CNT];
}oam_stats_phy_stat_stru;

/* mac统计收发包数目 */
typedef struct
{
    /* rx统计 */
    oal_uint32 ul_machw_rx_ampdu_count;
    oal_uint32 ul_machw_rx_passed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_octects_in_ampdu;
    oal_uint32 ul_machw_rx_delimit_fail_count;
    oal_uint32 ul_machw_rx_dup_mpdu_cnt;
    oal_uint32 ul_machw_rx_passed_mpdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_cnt;
    oal_uint32 ul_machw_rx_bcn_cnt;
    oal_uint32 ul_machw_rx_phy_err_mac_passed_cnt;
    oal_uint32 ul_machw_rx_phy_longer_err_cnt;
    oal_uint32 ul_machw_rx_phy_shorter_err_cnt;
    oal_uint32 ul_machw_rx_filtered_cnt;

    /* tx统计 */
    oal_uint32 ul_machw_tx_hi_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_normal_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_ampdu_count;
    oal_uint32 ul_machw_tx_mpdu_inampdu_count;
    oal_uint32 ul_machw_tx_octects_in_ampdu;
    oal_uint32 ul_machw_tx_bcn_count;
    oal_uint32 ul_machw_tx_normal_pri_retry_cnt;
    oal_uint32 ul_machw_tx_hi_pri_retry_cnt;
}oam_stats_machw_stat_stru;

/* 管理帧收发数目统计，包括硬件统计的发送beacon帧数目和高优先级队列发送数目 */
typedef struct
{
    oal_uint32          ul_machw_stat_tx_bcn_cnt;
    oal_uint32          ul_machw_stat_tx_hi_cnt;
    oal_uint32          aul_sw_rx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_sw_tx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_tx_complete_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
}oam_stats_mgmt_stat_stru;

/* 用户队列统计信息，包括节能队列和tid队列 */
typedef struct
{
    oal_uint32          aul_uapsd_stat[OAM_UAPSD_STAT_CNT];
    oal_uint32          aul_psm_stat[OAM_PSM_STAT_CNT];
    oal_uint32          aul_tid_stat[WLAN_TID_MAX_NUM][OAM_TID_STAT_CNT];
}oam_stats_usr_queue_stat_stru;

/* vap吞吐统计信息结构，包个数，字节数，平均速率(字节数/上报周期) */
typedef struct
{
    oal_uint32          ul_lan_tx_pkts;     /* 以太网过来的包数目 */
    oal_uint32          ul_lan_tx_bytes;    /* 以太网过来的字节数，不算以太网头 */
    oal_uint32          ul_drv_tx_pkts;     /* 驱动发包数目，交给硬件的数目 */
    oal_uint32          ul_drv_tx_bytes;    /* 驱动发包字节数，不算80211头尾 */
    oal_uint32          ul_hw_tx_pkts;      /* 发送完成中断上报发送成功的个数 */
    oal_uint32          ul_hw_tx_bytes;     /* 发送完成中断上报发送成功字节数 */

    oal_uint32          ul_drv_rx_pkts;     /* 驱动接收包数目 */
    oal_uint32          ul_drv_rx_bytes;    /* 驱动接收字节数，不包括80211头尾 */
    oal_uint32          ul_lan_rx_pkts;     /* 驱动交给以太网包数目 */
    oal_uint32          ul_lan_rx_bytes;    /* 驱动交给以太网字节数，不包括以太网头 */
    oal_uint32          ul_app_rx_pkts;     /* 驱动交给以APP包数目 */
    oal_uint32          ul_app_rx_bytes;    /* 驱动交给以APP字节数，不包括以太网头 */

    /* 平均速率 单位: kbps */
    oal_uint32          ul_lan_tx_rate;     /* lan发包平均速率 */
    oal_uint32          ul_drv_tx_rate;     /* 驱动发包平均速率 */
    oal_uint32          ul_hw_tx_rate;      /* 发送完成上报成功的发包平均速率 */
    oal_uint32          ul_drv_rx_rate;     /* 驱动收包平均速率 */
    oal_uint32          ul_lan_rx_rate;     /* lan收包平均速率 */
}oam_stats_vap_stat_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    /* 接收方向统计 */

    oal_uint32          ul_ba_recipient_tid_recv_pkt;    /* 该TID建立BA会话后，接收数据包数目 */
    oal_uint32          ul_ba_recipient_no_ba_session;
    oal_uint32          ul_ba_recipient_recv_ampdu_no_ba;
    oal_uint32          ul_ba_recipient_send_delba_count;
    oal_uint32          ul_ba_recipient_dup_frame_count;
    oal_uint32          ul_ba_recipient_dup_frame_drop_count;
    oal_uint32          ul_ba_recipient_dup_frame_up_count;
    oal_uint32          ul_ba_recipient_direct_up_count;
    oal_uint32          ul_ba_recipient_buffer_frame_count;
    oal_uint32          ul_ba_recipient_buffer_frame_overlap_count;
    oal_uint32          ul_ba_recipient_between_baw_count;
    oal_uint32          ul_ba_recipient_greater_baw_count;
    oal_uint32          ul_ba_recipient_sync_loss_count;
    oal_uint32          ul_ba_recipient_update_hw_baw_count;

}oam_stats_ampdu_stat_stru;
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明    OAM模块对外提供的接口
*****************************************************************************/
extern oam_mng_ctx_stru             g_st_oam_mng_ctx;

extern oal_uint32 oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);
extern oal_int32  oam_main_init(oal_void);
extern oal_void  oam_main_exit(oal_void);
extern oal_uint32  oam_print(oal_int8 *pc_string);
extern oal_uint32  oam_set_file_path(oal_int8 *pc_file_path, oal_uint32 ul_length);
extern oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type);
extern oal_uint32  oam_get_output_type(oam_output_type_enum_uint8 *pen_output_type);


/*******************************************************************************
            LOG模块对外接口
*******************************************************************************/
extern oal_void oam_exception_stat_handler(oam_msg_moduleid_enum_uint8 en_moduleid, oal_uint8 uc_vap_idx);

extern oal_uint32 oam_log_set_global_switch(oal_switch_enum_uint8 en_log_switch);
extern oal_uint32 oam_log_set_vap_switch(oal_uint8 uc_vap_id,
                                         oal_switch_enum_uint8    en_log_switch);

extern oal_uint32 oam_log_set_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit);

extern oal_uint32 oam_log_set_feature_level(oal_uint8 uc_vap_id,
                                           oam_feature_enum_uint8   en_feature_id,
                                           oam_log_level_enum_uint8 en_log_level);
extern oal_uint32 oam_get_feature_id(oal_uint8 *puc_feature_name,
                                              oam_feature_enum_uint8 *puc_feature_id);
extern oal_uint32 oam_show_feature_list(oal_void);
extern oal_uint32 oam_log_set_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 en_log_level);

extern oal_uint32 oam_log_get_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 *pen_log_level);

extern  oal_int32 OAL_PRINT_NLOGS(
        const oal_int8* pfunc_local_name,
        oal_uint16      us_file_no,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_uint8       uc_vap_id,
        oal_uint8       en_feature_id,
        oal_uint8       clog_level,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4);

extern oal_uint32  oam_log_print0(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print1(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print2(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print3(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print4(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_console_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                const oal_int8                  *pc_fmt,
                ...);

extern oal_uint32 oam_exception_record(oal_uint8 uc_vap_id, oam_excp_type_enum_uint8 en_excp_id);

/*******************************************************************************
            EVENT模块对外接口
*******************************************************************************/
extern oal_uint32  oam_event_set_switch(
                       oal_uint8               uc_vap_id,
                       oal_switch_enum_uint8   en_switch_type);
extern oal_uint32  oam_event_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_event_report(
                                    oal_uint8                  *puc_user_macaddr,
                                    oal_uint8                   uc_vap_id,
                                    oam_module_id_enum_uint16   en_mod,
                                    oam_event_type_enum_uint16  en_event_type,
                                    oal_uint8                  *puc_string);
extern oal_uint32  oam_ota_report(oal_uint8   *puc_param_one_addr,
                               oal_uint16   us_param_one_len,
                               oal_uint8   *puc_param_two_addr,
                               oal_uint16   us_param_two_len,
                               oam_ota_type_enum_uint8  en_ota_type);
#if 0
extern oal_uint32  oam_ota_set_switch(
                            oal_uint8                   uc_vap_id,
                            oal_switch_enum_uint8       en_switch_type,
                            oam_ota_type_enum_uint8     en_ota_type);
#endif
extern oal_uint32  oam_ota_set_beacon_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_beacon_switch(oal_void);
extern oal_uint32  oam_ota_set_rx_dscr_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_rx_dscr_switch(oal_void);


extern oal_uint32  oam_report_eth_frame(oal_uint8               *puc_user_mac_addr,
                                       oal_uint8               *puc_eth_frame_hdr_addr,
                                       oal_uint16               us_eth_frame_len,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction);
extern oal_uint32 oam_report_dscr(oal_uint8  *puc_user_macaddr,
                               oal_uint8  *puc_dscr_addr,
                               oal_uint16  us_dscr_len,
                               oam_ota_type_enum_uint8  en_ota_type);
extern oal_uint32  oam_report_beacon(
                                    oal_uint8     *puc_beacon_hdr_addr,
                                    oal_uint8      uc_beacon_hdr_len,
                                    oal_uint8     *puc_beacon_body_addr,
                                    oal_uint16     us_beacon_len,
                                    oam_ota_frame_direction_type_enum_uint8 en_beacon_direction);
extern oal_uint32  oam_report_80211_frame(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction);
#if 0
extern oal_switch_enum_uint8 oam_report_get_switch(oam_ota_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_80211_mcast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_ucast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32  oam_report_80211_probe_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probereq_direction,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_probe_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_eth_frame_get_switch(
                                 oal_uint16             us_user_idx,
                                 oam_ota_frame_direction_type_enum_uint8 en_eth_direction,
                                 oal_switch_enum_uint8  *pen_eth_switch);
extern oal_uint32  oam_report_netbuf_cb(oal_uint8  *puc_user_mac_addr,
                                       oal_uint8  *puc_netbuf_cb,
                                       oam_ota_type_enum_uint8 en_ota_type);
#if 0
extern oal_uint32  oam_report_timer_track(oal_uint32 ul_file_id,
                                        oal_uint32 ul_line_num,
                                        oam_timer_track_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_mpdu_num(oal_uint8  *puc_user_mac_addr,
                                        oam_report_mpdu_num_stru *pst_mpdu_num);
extern oal_uint32  oam_report_dft_params(oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16      us_param_len,
                                        oam_ota_type_enum_uint8 en_type);
extern oal_uint32  oam_report_set_all_switch(oal_switch_enum_uint8 en_switch);
extern oal_uint32  oam_report_80211_ucast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32 oam_report_eth_frame_set_switch(oal_uint16               us_user_idx,
                                                   oal_switch_enum_uint8    en_switch,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_direction);
extern oal_uint32  oam_report_80211_mcast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_dhcp_arp_set_switch(oal_switch_enum_uint8 en_switch);
extern oal_switch_enum_uint8  oam_report_dhcp_arp_get_switch(oal_void);
extern oal_switch_enum_uint8  oam_report_data_get_global_switch(oam_ota_frame_direction_type_enum_uint8 en_direction);

/*******************************************************************************
            ALARM模块对外接口
*******************************************************************************/
extern oal_uint32  oam_alarm_set_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8  en_switch_type);
extern oal_uint32  oam_alarm_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_alarm_report(
                       oal_uint8                   uc_vap_id,
                       oal_uint16                  us_file_no,
                       oal_uint32                  ul_file_line_no,
                       oam_module_id_enum_uint16   en_mod,
                       oam_alarm_type_enum_uint16  en_alarm_type);

/*******************************************************************************
            SDT模块对外接口
*******************************************************************************/
extern oal_void    oam_sdt_func_fook_register(oam_sdt_func_hook_stru *pfun_st_oam_sdt_hook);
extern oal_void    oam_sdt_func_fook_unregister(oal_void);
extern oal_void    oam_wal_func_fook_register(oam_wal_func_hook_stru *pfun_st_oam_wal_hook);
extern oal_void    oam_wal_func_fook_unregister(oal_void);

extern oal_uint32  oam_event_set_specific_type_switch(
                                oal_uint8                   uc_vap_id,
                                oal_switch_enum_uint8       en_switch_type,
                                oam_event_type_enum_uint16  en_event_type);

extern oal_uint32 oam_report_data2sdt(oal_netbuf_stru *pst_netbuf,
                                       oam_data_type_enum_uint8 en_type,
                                       oam_primid_type_enum_uint8 en_prim);
extern oal_netbuf_stru *oam_alloc_data2sdt(oal_uint16  us_data_len);
/*******************************************************************************
            TRACE模块对外接口
*******************************************************************************/

#ifdef _PRE_PROFILING_MODE
extern oal_void oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index);
extern oal_void oam_profiling_tx_save_data(oal_void *pst_netbuf,oam_profiling_tx_func_enum_uint8 en_func_index);
extern oal_void oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8 en_func_index);

#endif

/*******************************************************************************
            STATISTICS模块对外接口
*******************************************************************************/
extern oal_uint32  oam_stats_report_timer_info_to_sdt(
                                    oal_uint8 *puc_timer_addr,
                                    oal_uint8  uc_timer_len);
extern oal_uint32  oam_stats_report_event_queue_info_to_sdt(
                                    oal_uint8   *puc_event_queue_addr,
                                    oal_uint16    us_event_queue_info_len);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

extern oal_uint32 oam_stats_report_info_to_sdt(oam_ota_type_enum_uint8 en_ota_type);
extern oal_uint32  oam_report_vap_pkt_stat_to_sdt(oal_uint8 uc_vap_id);
extern oal_void  oam_stats_clear_stat_info(oal_void);
extern oal_uint32  oam_stats_report_usr_info(oal_uint16  us_usr_id);
extern oal_uint32  oam_stats_clear_user_stat_info(oal_uint16   us_usr_id);

extern oal_uint32  oam_stats_clear_vap_stat_info(oal_uint8   uc_vap_id);
#endif


extern oal_uint32  oam_stats_report_mempool_info_to_sdt(
                                        oal_uint8           uc_pool_id,
                                        oal_uint16          us_pool_total_cnt,
                                        oal_uint16          us_pool_used_cnt,
                                        oal_uint8           uc_subpool_id,
                                        oal_uint16          us_subpool_total_cnt,
                                        oal_uint16          us_subpool_free_cnt);
extern oal_uint32  oam_stats_report_memblock_info_to_sdt(oal_uint8  *puc_origin_data,
                                             oal_uint8   uc_user_cnt,
                                             oal_uint8   uc_pool_id,
                                             oal_uint8   uc_subpool_id,
                                             oal_uint16  us_len,
                                             oal_uint32  ul_file_id,
                                             oal_uint32  ul_alloc_line_num);
extern oal_void  oam_stats_report_irq_info_to_sdt(
                                    oal_uint8 *puc_irq_info_addr,
                                    oal_uint16  us_irq_info_len);

/*****************************************************************************
                                与配置文件相关的函数声明
*****************************************************************************/
extern oal_int32  oam_cfg_get_item_by_id(oam_cfg_type_enum_uint16  en_cfg_type);

//#ifdef _PRE_PROFILING_MODE
/*****************************************************************************
    profiling对应函数声明
*****************************************************************************/
extern oal_void    oam_profiling_switch_test_process(oal_uint8  uc_config_type, oal_uint8 uc_config_value);
extern oal_uint32  oam_profiling_compute_time_offset(
                       oal_time_us_stru    st_time_first,
                       oal_time_us_stru    st_time_second,
                       oal_time_us_stru   *pst_time_offset);
extern oal_uint32  oam_profiling_init(oal_void);
extern oal_uint32  oam_profiling_set_switch(oam_profiling_enum_uint8 en_profiling_type, oam_profiling_swith_enum_uint8 en_profiling_switch);

extern oal_void    oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index);
extern oal_uint32  oam_profiling_rx_show_offset(oal_void);

extern oal_void    oam_profiling_tx_save_data(
                       oal_void                    *pst_netbuf,
                       oam_profiling_tx_func_enum_uint8    en_func_index);
extern oal_uint32  oam_profiling_tx_show_offset(oal_void);

extern oal_void    oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8    en_func_index);
extern oal_uint32  oam_profiling_alg_show_offset(oal_void);

extern oal_void  oam_profiling_starttime_save_timestamp(oam_profiling_starttime_func_enum_uint8 en_func_idx);
extern oal_void  oam_profiling_starttime_show_offset(oal_void);
extern oal_void  oam_profiling_chswitch_save_timestamp(oam_profiling_chswitch_func_enum_uint8 en_func_idx);
extern oal_void  oam_profiling_chswitch_show_offset(oal_void);
extern oal_void oam_print_record_time(oal_void);
extern oal_void oam_record_time(oal_uint32 ul_idx);
//#endif

#ifdef _PRE_DEBUG_MODE
extern oam_tx_complete_stat_stru   g_ast_tx_complete_stat[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];
#endif
extern oal_void  oam_netlink_ops_register(oam_nl_cmd_enum_uint8 en_type, oal_uint32 (*p_func)(oal_uint8 *puc_data, oal_uint32 ul_len));
extern oal_void  oam_netlink_ops_unregister(oam_nl_cmd_enum_uint8 en_type);
extern oal_int32  oam_netlink_kernel_send(oal_uint8 *puc_data, oal_uint32 ul_data_len, oam_nl_cmd_enum_uint8 en_type);
extern oal_int32  oam_netlink_kernel_send_ex(oal_uint8 *puc_data_1st, oal_uint8 *puc_data_2nd,
                                             oal_uint32 ul_len_1st, oal_uint32 ul_len_2nd,
                                             oam_nl_cmd_enum_uint8 en_type);

OAL_STATIC OAL_INLINE  oal_switch_enum_uint8 oam_get_log_switch(
                oal_uint8                           uc_vap_id,
                oam_feature_enum_uint8              en_feature_id,
                oam_log_level_enum_uint8            en_log_level)
{
    /* 从执行性能角度考虑，提前判断特性开关，大部分info日志可以在第一层命令就直接退出 */

	if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch)
    	{
        return OAL_SWITCH_OFF;
 	}
	else if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id])
    	{

        return OAL_SWITCH_OFF;

	}
	 else if (en_log_level > g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id])
	{

		return OAL_SWITCH_OFF;

	}
	else   if (en_log_level > g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id])
    {
        return OAL_SWITCH_OFF;
    }

    return OAL_SWITCH_ON;
}


/*****************************************************************************
 函 数 名  : oam_event_chan_report
 功能描述  : 信道改变时间上报接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月22日
    作    者   : zouhongliang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oam_event_chan_report(oal_uint8 uc_channel_num)
{
    oal_uint8               auc_event[4];

    auc_event[0] = uc_channel_num;

    return oam_event_report(BROADCAST_MACADDR, 0, OAM_MODULE_ID_HAL, OAM_EVENT_VAP_CHANGE_CHANNEL, auc_event);
}

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "wlan_spec.h"
#include "platform_spec.h"
#include "oal_types.h"
#include "oal_net.h"
#include "oam_log.h"
#include "oam_common.h"
#include "oam_wdk.h"
#include "oam_config.h"
#ifdef _PRE_CONFIG_HW_CHR
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "chr_user.h"
#else
#define CHR_LOG(prio, tag, fmt,...)
#define CHR_EXCEPTION(chr_errno)
#endif
#else
#define CHR_LOG(prio, tag, fmt,...)
#define CHR_EXCEPTION(chr_errno)
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_EXT_IF_H

typedef enum
{
    MSG_EXCESSIVE      =    0,
    MSG_MSGDUMP        =    1,
    MSG_DEBUG          =    2,
    MSG_INFO           =    3,
    MSG_WARNING        =    4,
    MSG_ERROR          =    5,
    MSG_OAM_BUTT
};

#define wpa_printf           oam_printf_wpa
#define oam_printf(fmt, arg...)  oam_printf_wpa(MSG_WARNING, fmt, ##arg)
#define printk(fmt, arg...)  oam_printf_wpa(MSG_WARNING, fmt, ##arg)
#define OAM_IO_PRINTK(fmt, arg...)    oam_printf_wpa(MSG_WARNING, fmt, ##arg)

#define OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,fileid,lev)   ((fileid&0xFFFF)|((feature_id&0xFF)<<16)|((vap_id&0xF)<<24)|((lev&0xF)<<28))
/* 日志结构体相关宏，用于oam_log_info_stru */
#define OAM_FUNC_NAME_MAX_LEN           48                                      /* 函数名的最大长度 */
#define OAM_LOG_INFO_MAX_LEN            100                                     /* 日志信息最大长度 */
#define OAM_LOG_INFO_IN_MEM_MAX_NUM     5000   /* oam模块最多保存5000条log信息，超过以后从头自动覆盖 */
#define OAM_LOG_ENTRY_PARA_NUM          4
#if 0
#define OAM_INFO_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_INFO_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_INFO_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_INFO_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_INFO_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_WARNING_LOG0(vap_id, feature_id, fmt)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt)
#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1)
#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2)
#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3)
#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4)
#else
#define OAM_INFO_LOG0(vap_id, feature_id, fmt)
   //     oam_log_print0_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__)
#define OAM_INFO_LOG1(vap_id, feature_id, fmt, p1)
  //      oam_log_print1_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__,(oal_int32)p1)
#define OAM_INFO_LOG2(vap_id, feature_id, fmt, p1, p2)
  //      oam_log_print2_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2)
#define OAM_INFO_LOG3(vap_id, feature_id, fmt, p1, p2, p3)
    //    oam_log_print3_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3)
#define OAM_INFO_LOG4(vap_id, feature_id, fmt, p1, p2, p3, p4)
   //     oam_log_print4_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_INFO), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3,(oal_int32)p4)
#ifdef OAM_SDT_OUT
#define OAM_WARNING_LOG0_ACK(vap_id, feature_id, fmt)   \
        oam_print0_press_ack(OAM_WIFI_LOG_PARA_PRESS(vap_id, feature_id, THIS_FILE_ID, OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__)
#define OAM_WARNING_LOG0(vap_id, feature_id, fmt)  \
        oam_log_print0_press(OAM_WIFI_LOG_PARA_PRESS(vap_id, feature_id, THIS_FILE_ID, OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__)
#define OAM_WARNING_LOG1(vap_id, feature_id, fmt, p1)  \
        oam_log_print1_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__,(oal_int32)p1)
#define OAM_WARNING_LOG2(vap_id, feature_id, fmt, p1, p2)  \
        oam_log_print2_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2)
#define OAM_WARNING_LOG3(vap_id, feature_id, fmt, p1, p2, p3) \
        oam_log_print3_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3)
#define OAM_WARNING_LOG4(vap_id, feature_id, fmt, p1, p2, p3, p4) \
        oam_log_print4_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3,(oal_int32)p4)

#define OAM_ERROR_LOG0(vap_id, feature_id, fmt)   \
        oam_log_print0_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__)
#define OAM_ERROR_LOG1(vap_id, feature_id, fmt, p1)  \
        oam_log_print1_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__,(oal_int32)p1)
#define OAM_ERROR_LOG2(vap_id, feature_id, fmt, p1, p2)  \
        oam_log_print2_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2)
#define OAM_ERROR_LOG3(vap_id, feature_id, fmt, p1, p2, p3) \
        oam_log_print3_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3)
#define OAM_ERROR_LOG4(vap_id, feature_id, fmt, p1, p2, p3, p4) \
        oam_log_print4_press(OAM_WIFI_LOG_PARA_PRESS(vap_id,feature_id,THIS_FILE_ID,OAM_LOG_LEVEL_ERROR), (oal_uint16)__LINE__,(oal_int32)p1,(oal_int32)p2,(oal_int32)p3,(oal_int32)p4)
#else
#define OAM_WARNING_LOG0_ACK(vap_id, feature_id, fmt)   \
        oam_print0_press_ack(OAM_WIFI_LOG_PARA_PRESS(vap_id, feature_id, THIS_FILE_ID, OAM_LOG_LEVEL_WARNING), (oal_uint16)__LINE__)
#define OAM_WARNING_LOG0(_uc_vap_id, _en_feature_id, fmt) \
do{ \
    printf(fmt); \
	printf("\n"); \
    }while(0)
#define OAM_WARNING_LOG1(_uc_vap_id, _en_feature_id, fmt, p1) \
do{ \
    printf(fmt, p1); \
	printf("\n"); \
    }while(0)
#define OAM_WARNING_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2) \
do{ \
    printf(fmt, p1, p2); \
	printf("\n"); \
    }while(0)
#define OAM_WARNING_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
do{ \
    printf(fmt, p1, p2, p3); \
	printf("\n"); \
	}while(0)
#define OAM_WARNING_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4) \
do{ \
    printf(fmt, p1, p2, p3, p4); \
	printf("\n"); \
	}while(0)

#define OAM_ERROR_LOG0(_uc_vap_id, _en_feature_id, fmt) \
do{ \
    printf(fmt); \
    printf("\n"); \
	}while(0)

#define OAM_ERROR_LOG1(_uc_vap_id, _en_feature_id, fmt, p1) \
do{ \
    printf(fmt, p1); \
    printf("\n"); \
	}while(0)

#define OAM_ERROR_LOG2(_uc_vap_id, _en_feature_id, fmt, p1, p2) \
do{ \
    printf(fmt, p1, p2); \
    printf("\n"); \
	}while(0)

#define OAM_ERROR_LOG3(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3) \
do{ \
    printf(fmt, p1, p2, p3); \
    printf("\n"); \
	}while(0)

#define OAM_ERROR_LOG4(_uc_vap_id, _en_feature_id, fmt, p1, p2, p3, p4) \
do{ \
    printf(fmt, p1, p2, p3, p4); \
    printf("\n"); \
	}while(0)

#endif
#endif

/* 日志级别 */
typedef enum
{
    OAM_LOG_LEVEL_ERROR     =    1,       /* ERROR级别打印 */
    OAM_LOG_LEVEL_WARNING,                /* WARNING级别打印 */
    OAM_LOG_LEVEL_INFO,                   /* INFO级别打印 */

    OAM_LOG_LEVEL_BUTT
}oam_log_level_enum;
typedef oal_uint8 oam_log_level_enum_uint8;

typedef oal_uint8   oam_feature_enum_uint8;

typedef struct
{
    oal_uint32  bit16_file_id:   16;
    oal_uint32  bit8_feature_id: 8;
    oal_uint32  bit4_vap_id:     4;
    oal_uint32  bit4_log_level:  4;
}om_log_wifi_para_stru;

typedef struct
{
    oal_uint8    bit_vap_id      :  4;
    oal_uint8    bit_log_level   :  4;
}oam_vap_log_level_stru;

typedef struct
{
    oal_netbuf_stru     *pst_buffer;
    oal_uint             ul_res_index;
    oal_uint16           us_netbuf_len;
    oal_uint16           us_used_len;
    oal_dlist_head_stru  st_entry;
}oam_log_buff_stru;


/*data type */
typedef enum
{
    OAM_DATA_TYPE_LOG       = 0x1,
    OAM_DATA_TYPE_OTA       = 0x2,
    OAM_DATA_TYPE_TRACE     = 0x3,
    OAM_DATA_TYPE_EVENT     = 0x4,
    OAM_DATA_TYPE_MEM_RW    = 0x9,
    OAM_DATA_TYPE_REG_RW    = 0x15,
    OAM_DATA_TYPE_CFG       = 0x0b,
    OAM_DATA_TYPE_GVAR_RW   = 0x27,   /* global value read or write */
    OAM_DATA_TYPE_STRING    = 0x28,   /* report string  */

    OAM_DATA_TYPE_DEVICE_LOG     = 0x40,
    OAM_DATA_TYPE_ADAPTER_PRINTF = 0x42,
    OAM_DATA_TYPE_ACK            = 0x43,
    OAM_DATA_TYPE_FILE           = 0x44,
    OAM_DATA_TYPE_BUTT
}oam_data_type_enum;
typedef oal_uint8 oam_data_type_enum_uint8;

#define OM_FILE_HEADER_LEN     OAL_SIZEOF(OM_MSG_HEADER_STRU)
#define FILE_PRINT_DATA_LEN    32
#define FILE_FLAG_NUM          2

#pragma pack(push,1)
/* 日志消息结构体 */
typedef struct
{
    oam_vap_log_level_stru              st_vap_log_level;   /* vapid + loglevel */
    oam_feature_enum_uint8              en_feature_id;       /* 特性id */
    oal_uint16                          us_resv;
    oal_uint16                          us_file_id;         /* 文件号 */
    oal_uint16                          us_line_num;        /* 行号 */
    oal_uint32                          ul_tick;            /* 时间戳，精度ms */
    oal_int32                           al_param[OAM_LOG_ENTRY_PARA_NUM + 1];     //device
}oam_log_info_stru;

typedef struct
{
    OM_MSG_HEADER_STRU  st_oam_header;
    oam_log_info_stru   st_log_info;
}om_log_stru;
/* 文件发送结构体 */
typedef struct
{
    OM_MSG_HEADER_STRU st_file_header;  /* 文件头信息 */
    oal_uint8 pucdata[FILE_PRINT_DATA_LEN]; /* 文件数据 */
}om_print_file_stru;
#pragma pack(pop)



/*  oam流控结构体
    流控的实现原理具体参考 oam_log_ratelimit函数实现
*/
typedef struct
{
    oal_spin_lock_stru              spin_lock;
    oal_switch_enum_uint8           en_ratelimit_switch; /* 流控控制开关 */
    oal_uint32                      ul_interval;         /* 流控时间范围 */
    oal_uint32                      ul_burst;            /* 流控流量值 */
    oal_uint32                      ul_printed;          /* 满足流控条件输出记录 */
    oal_uint32                      ul_missed;           /* 不满足流控条件屏蔽记录 */
    oal_uint32                      ul_begin;            /* 本次流控起始时间 */
}oam_ratelimit_stru;



#if 0
typedef struct
{
    oam_log_buff_stru       ast_buff_info[WLAN_SDT_NETBUF_CNT];
    oal_queue_stru          st_queue;
    oal_uint                aul_idx[WLAN_SDT_NETBUF_CNT];
}oam_log_res_stru;
#endif
#define OAM_LOG_PARAM_MAX_NUM           4                                       /* 可打印最多的参数个数 */
#define OAM_LOG_PRINT_DATA_LENGTH       512                                     /* 每次写入文件的最大长度 */
//#if ((_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
#define OAM_LOG_MSG_LEN                 (OAL_SIZEOF(om_log_stru))
#define OAM_LOG_HEADER_LEN              (OAM_LOG_MSG_LEN - (OAM_LOG_ENTRY_PARA_NUM+1)*4)
//#endif

#define OAM_DIFF_LOG0           OAM_WARNING_LOG0
#define OAM_DIFF_LOG1           OAM_WARNING_LOG1
#define OAM_DIFF_LOG2           OAM_WARNING_LOG2
#define OAM_DIFF_LOG3           OAM_WARNING_LOG3
#define OAM_DIFF_LOG4           OAM_WARNING_LOG4

#define OAM_PROFILING_RX_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_TX_STATISTIC(_pst_pointer, _uc_func_idx)
#define OAM_PROFILING_ALG_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_STARTTIME_STATISTIC(_uc_func_idx)
#define OAM_PROFILING_CHSWITCH_STATISTIC(_uc_func_idx)

#define OAM_STAT_DEV_INCR(_uc_dev_id, _member, _num)
#define OAM_STAT_DEV_ARRAY_INCR(_uc_dev_id, _member, _uc_array_index, _uc_array_max_size)
#define OAM_STAT_DEV_UPDATE(_uc_dev_id, _member, _uc_q_id, _uc_index, _ul_val)
#define OAM_STAT_DEV_GET_VAL(_uc_dev_id, _member,_pul_val)
#define OAM_STAT_DEV_SET_VAL(_uc_dev_id, _member, _uc_val)
#define OAM_STAT_VAP_INCR(_uc_vap_id, _member, _num)
#define OAM_STAT_MGMT_INCR(_uc_vap_id, _uc_mgmt_id, _member)
#define OAM_STAT_USER_INCR(_uc_user_id, _member, _num)
#define OAM_STAT_TID_INCR(_uc_user_id, _uc_tid_num, _member, _num)

//#define OAM_STAT_GET_STAT_ALL() (&g_st_stat_info)
#define OAM_STAT_GET_STAT_ALL()  NULL

#ifdef _PRE_WIFI_DMT
#define OAM_PRINT_FORMAT_LENGTH     1024                    /* 打印格式字符串的最大长度:DMT调试的打印信息会比较长，不够时会踩内存 */
#else
#define OAM_PRINT_FORMAT_LENGTH     256                     /* 打印格式字符串的最大长度 */
#endif

/* 日志结构体相关宏，用于oam_log_info_stru */
#define OAM_FUNC_NAME_MAX_LEN           48                                      /* 函数名的最大长度 */
#define OAM_LOG_INFO_MAX_LEN            100                                     /* 日志信息最大长度 */
#define OAM_LOG_INFO_IN_MEM_MAX_NUM     5000   /* oam模块最多保存5000条log信息，超过以后从头自动覆盖 */
#define OAM_LOG_ENTRY_PARA_NUM          4

//#define OAM_SEQ_TRACK_NUM              256
#define OAM_SEQ_TRACK_NUM              128

/* device级别的各类中断错误最大个数 */
#define OAM_MAC_ERROR_TYPE_MAX_NUM      25
#define OAM_SOC_IRQ_MAX_NUM             5
#define OAM_PMU_BUCK_IRQ_MAX_NUM        5
#define OAM_MAC_SUB_IRQ_MAX_NUM         11

/* 内存块信息除掉最后一个成员占用的大小 */
#define OAM_MEMBLOCK_INFO_STRU_LEN      8

/* oam_stats_device_subtype_irq_stru前三个成员占用空间大小 */
#define OAM_FIRST_THREE_MEMBER_LEN      4

/* 每一个事件队列中事件个数最大值 */
#define OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE 8

/* OAM模块申请skb时，头部和尾部为sdt分别预留8个和1个字节 */
#define OAM_RESERVE_SKB_HEADROOM_LEN    8
#define OAM_RESERVE_SKB_TAILROOM_LEN    1
#define OAM_RESERVE_SKB_LEN             (OAM_RESERVE_SKB_HEADROOM_LEN + OAM_RESERVE_SKB_TAILROOM_LEN)

/* 字符串以0结尾上报，实际字符串内容最大长度 */
#define OAM_REPORT_MAX_STRING_LEN       (WLAN_SDT_NETBUF_MAX_PAYLOAD - 1)   /*以\0结束*/


/* 统计相关宏 */
#define OAM_MAC_ERROR_TYPE_CNT    25
#define OAM_RX_DSCR_QUEUE_CNT     2
#define OAM_IRQ_FREQ_STAT_MEMORY  50

#define OAM_TID_TRACK_NUM         4

/**********************性能维测相关宏定义******************/
#ifdef _PRE_WLAN_DFT_STAT
#define  OAM_PHY_STAT_NODE_ENABLED_MAX_NUM    4
#define  OAM_PHY_STAT_RX_PPDU_CNT             8
#define  OAM_PHY_STAT_ITEM_MIN_IDX            1
#define  OAM_PHY_STAT_ITEM_MAX_IDX            16
#define  OAM_MACHW_STAT_RX_MEMBER_CNT         18
#define  OAM_MACHW_STAT_TX_MEMBER_CNT         8
#define  OAM_PSM_STAT_CNT                     10
#define  OAM_UAPSD_STAT_CNT                   11
#define  OAM_TID_STAT_CNT                     14
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* SDT驱动侧向SDT APP侧发送数据的类型 */
typedef enum
{
    OAM_PRIMID_TYPE_PC_TO_DEV_DATA = 1,
    OAM_PRIMID_TYPE_DEV_ACK,
    OAM_PRIMID_TYPE_DEV_ACTIVE_UPLOAD,
    OAM_PRIMID_TYPE_OUTPUT_CONTENT,

    SDT_DRV_PRIMID_TYPE_BUTT
}oam_primid_type_enum;

typedef oal_uint8 oam_primid_type_enum_uint8;

typedef enum
{
    OAM_MODULE_ID_ALL,
    OAM_MODULE_ID_WAL,
    OAM_MODULE_ID_HMAC,
    OAM_MODULE_ID_DMAC,

    OAM_MODULE_ID_MAC,  /* 此模块ID只用于HMAC、DMAC公共文件日志记录使用，软件中不存在MAC此模块 */

    OAM_MODULE_ID_HAL,
    OAM_MODULE_ID_OAM,
    OAM_MODULE_ID_OAL,
    OAM_MODULE_ID_FRW,
    OAM_MODULE_ID_ALG,
    OAM_MODULE_ID_BLD,

    OAM_MODULE_ID_ALG_SCHEDULE,
    OAM_MODULE_ID_ALG_AUTORATE,
    OAM_MODULE_ID_ALG_SMARTANT,
    OAM_MODULE_ID_ALG_ACS,
    OAM_MODULE_ID_ALG_DBAC,

#ifdef _PRE_WIFI_DMT
    OAM_MODULE_ID_DMT,
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    OAM_MODULE_ID_ALG_TXBF,
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
    OAM_MODULE_ID_PERFORM_STAT,
#endif

    OAM_MODULE_ID_ALG_ANTI_INTF,

    OAM_MODULE_ID_HUT,

    OAM_MODULE_ID_ALG_CCA_OPT,


    /* 待补充 */

    OAM_MODULE_ID_BUTT
}oam_module_id_enum;
typedef oal_uint16 oam_module_id_enum_uint16;
typedef oal_uint8  oam_msg_moduleid_enum_uint8;



#define OAM_LOG_DEFAULT_LEVEL           OAM_LOG_LEVEL_WARNING

/* 配置文件，配置的类型 */
typedef enum
{
    OAM_CFG_TYPE_MAX_ASOC_USER            = 0,

    OAM_CFG_TYPE_BUTT
}oam_cfg_type_enum;
typedef oal_uint16 oam_cfg_type_enum_uint16;

/* 打印模式定义 */
typedef enum
{
    OAM_OUTPUT_TYPE_CONSOLE  = 0,            /* 控制台输出 */
    OAM_OUTPUT_TYPE_FS,                      /* 写到文件系统 */
    OAM_OUTPUT_TYPE_SDT,                     /* 输出到SDT */
    //OAM_OUTPUT_TYPE_IPC,                     /* 通过核间通讯方式，发送至另一核，一般是从核将可维可测内容发送至主核 */

    OAM_OUTPUT_TYPE_BUTT
}oam_output_type_enum;
typedef oal_uint8 oam_output_type_enum_uint8;

/* event上报事件消息类型 */
typedef enum
{
    OAM_EVENT_WID_QUERY,                     /* 配置命令消息，查询命令 */
    OAM_EVENT_WID_WRITE,                     /* 配置命令消息，写命令 */
    OAM_EVENT_INTERNAL,                      /* WiTP内部各层之间的事件消息 */
    OAM_EVENT_VAP_STATE_CHANGE,              /* VAP状态迁移事件消息 */
    OAM_EVENT_PAUSE_OR_RESUME_TID,           /* 暂停或者恢复tid */
    OAM_EVENT_PAUSE_OR_RESUME_USER,          /* 暂停或者恢复user消息 */
    OAM_EVENT_VAP_CHANGE_CHANNEL,            /* VAP切换信道 */
    OAM_EVENT_USER_INFO_CHANGE,              /* 用户状态信息或者能力信息变化 */
    OAM_EVENT_USER_TXRX_PARAM,               /* 用户收发参数 */
    OAM_EVENT_REGISTER = 9,                   /* 寄存器 */

    OAM_EVENT_TYPE_BUTT
}oam_event_type_enum;
typedef oal_uint16 oam_event_type_enum_uint16;

/* OTA上报事件类型 */
typedef enum
{
    /* 默认关闭上报 */
    OAM_OTA_TYPE_RX_DSCR,                     /* 接收描述符 */
    OAM_OTA_TYPE_TX_DSCR,                     /* 发送描述符 */
    OAM_OTA_TYPE_80211_FRAME,                 /* 80211帧(不包括beacon) */
    OAM_OTA_TYPE_BEACON,                      /* beacon */
    OAM_OTA_TYPE_ETH_FRAME,                   /* 以太网帧 */
    OAM_OTA_TYPE_RX_DMAC_CB,
    OAM_OTA_TYPE_RX_HMAC_CB,
    OAM_OTA_TYPE_TX_CB,
    OAM_OTA_TYPE_TIMER_TRACK,                 /* 定时器创建删除的行号和文件号追踪 ,已废弃*/

    /* 默认打开上报 */
    OAM_OTA_TYPE_IRQ,                         /* 中断信息 */
    OAM_OTA_TYPE_TIMER,                       /* 软件定时器信息 */
    OAM_OTA_TYPE_MEMPOOL,                     /* 某一内存池及所有子池使用信息 */
    OAM_OTA_TYPE_MEMBLOCK,                    /* 某一内存池的所有内存块使用信息及内容，或者任意连续内存块的内容 */
    OAM_OTA_TYPE_EVENT_QUEUE,                 /* 当前所有存在事件的事件队列中的事件个数和事件头信息 */
    OAM_OTA_TYPE_MPDU_NUM,
    OAM_OTA_TYPE_PHY_STAT,                    /* phy收发包统计值 */
    OAM_OTA_TYPE_MACHW_STAT,                  /* mac收发包统计值 */
    OAM_OTA_TYPE_MGMT_STAT,                   /* 管理帧统计 */
    OAM_OTA_TYPE_DBB_ENV_PARAM,               /* 空口环境类维测参数 */
    OAM_OTA_TYPE_USR_QUEUE_STAT,              /* 用户队列统计信息 */
    OAM_OTA_TYPE_VAP_STAT,                    /* vap吞吐相关统计信息 */
    OAM_OTA_TYPE_USER_THRPUT_PARAM,           /* 影响用户实时吞吐相关的统计信息 */
    OAM_OTA_TYPE_AMPDU_STAT,                  /* ampdu业务流程统计信息 */
    OAM_OTA_TYPE_HARDWARE_INFO,               /* hal mac相关信息 */
    OAM_OTA_TYPE_USER_QUEUE_INFO,             /* 用户队列信息 */

    /* VAP与USER等结构体的信息，上报整个结构体内存 */
    OAM_OTA_TYPE_HMAC_VAP,
    OAM_OTA_TYPE_DMAC_VAP,
    OAM_OTA_TYPE_HMAC_USER,
    OAM_OTA_TYPE_MAC_USER,
    OAM_OTA_TYPE_DMAC_USER,

    /* hmac 与 dmac vap中部分成员的大小 */
    OAM_OTA_TYPE_HMAC_VAP_MEMBER_SIZE,
    OAM_OTA_TYPE_DMAC_VAP_MEMBER_SIZE,

    /* 三种级别的统计信息,这三个必放到一起!!! */
    OAM_OTA_TYPE_DEV_STAT_INFO,
    OAM_OTA_TYPE_VAP_STAT_INFO,
    OAM_OTA_TYPE_USER_STAT_INFO,

    OAM_OTA_TYPE_PHY_BANK1_INFO,     /* PHY寄存器 BANK1 信息 */
    OAM_OTA_TYPE_PHY_BANK2_INFO,     /* PHY寄存器 BANK2 信息 */
    OAM_OTA_TYPE_PHY_BANK3_INFO,     /* PHY寄存器 BANK3 信息 */
    OAM_OTA_TYPE_PHY_BANK4_INFO,     /* PHY寄存器 BANK4 信息 */
    OAM_OTA_TYPE_MAC_BANK0_INFO,     /* MAC寄存器 BANK0 信息 */
    OAM_OTA_TYPE_MAC_BANK1_INFO,     /* MAC寄存器 BANK1 信息 */
    OAM_OTA_TYPE_MAC_BANK2_INFO,      /* MAC寄存器 BANK2 信息 */
    OAM_OTA_TYPE_MAC_BANK3_INFO,   /* MAC寄存器 BANK3 信息（存在几字节信息不能读取） */
    OAM_OTA_TYPE_MAC_BANK4_INFO,     /* MAC寄存器 BANK4 信息 */
    OAM_OTA_TYPE_RF_REG_INFO,     /* RF寄存器 */
    OAM_OTA_TYPE_SOC_REG_INFO,     /* SOC寄存器 */


    OAM_OTA_TYPE_BUTT
}oam_ota_type_enum;
typedef oal_uint8 oam_ota_type_enum_uint8;

/* 定时器追踪类型 */
typedef enum
{
    OAM_TIMER_TRACK_TYPE_CREATE = 0,
    OAM_TIMER_TRACK_TYPE_DESTROY,
    OAM_TIMER_TRACK_TYPE_IMMEDIATE_DESTROY,

    OAM_TIMER_TRACK_TYPE_BUTT
}oam_timer_track_type_enum;
typedef oal_uint8 oam_timer_track_type_enum_uint8;

/****************************单用户跟踪相关枚举*******************************/
/* 单用户跟踪内容，帧内容，CB字段，描述符 */
typedef enum
{
    OAM_USER_TRACK_CONTENT_FRAME = 0,
    OAM_USER_TRACK_CONTENT_CB,
    OAM_USER_TRACK_CONTENT_DSCR,

    OAM_USER_TRACK_CONTENT_BUTT
}oam_user_track_content_enum;
typedef oal_uint8 oam_user_track_content_enum_uint8;

/* 单用户跟踪帧类型:数据和管理 */
typedef enum
{
    OAM_USER_TRACK_FRAME_TYPE_MGMT = 0,
    OAM_USER_TRACK_FRAME_TYPE_DATA,

    OAM_USER_TRACK_FRAME_TYPE_BUTT
}oam_user_track_frame_type_enum;
typedef oal_uint8 oam_user_track_frame_type_enum_uint8;

/* 跟踪用户信息变化类型，event类型信息，状态变化驱动 */
typedef enum
{
    OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE = 0,         /* 用户关联状态 */
    OAM_USER_INFO_CHANGE_TYPE_TX_PROTOCOL,             /* 发送数据帧使用的协议模式 */
    OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL,             /* 接收数据帧使用的协议模式 */

    /* ... */

    OAM_USER_INFO_CHANGE_TYPE_BUTT
}oam_user_info_change_type_enum;
typedef oal_uint8 oam_user_info_change_type_enum_uint8;

/* 跟踪用户收发参数,event类型信息,配置命令驱动 */
typedef enum
{
    OAM_USER_TXRX_PARAM_TYPE_RSSI = 0,
    OAM_USER_TXRX_PARAM_TYPE_RATE,

    /* ... */

    OAM_USER_TXRX_PARAM_TYPE_BUTT
}oam_user_txrx_param_type_enum;
typedef oal_uint8 oam_user_txrx_param_type_enum_uint8;
/*****************************************************************************/


/* 统计信息上报类型，分为device级别，vap级别，user级别 */
typedef enum
{
    OAM_STATS_TYPE_DEVICE,
    OAM_STATS_TYPE_VAP,
    OAM_STATS_TYPE_USER,

    OAM_STATS_TYPE_BUTT
}oam_stats_type_enum;
typedef oal_uint8 oam_stats_type_enum_uint8;

/* device级别统计信息上报子类型， */
typedef enum
{
    OAM_STATS_DEVICE_SUBTYPE_IRQ,
    OAM_STATS_DEVICE_SUBTYPE_TIMER,
    OAM_STATS_DEVICE_SUBTYPE_MEMPOOL,
    OAM_STATS_DEVICE_SUBTYPE_EVENT_QUEUE,

    OAM_STATS_DEVICE_SUBTYPE_BUTT
}oam_stats_device_subtype_enum;
typedef oal_uint8 oam_stats_device_subtype_enum_uint8;

/* ALARM上报事件类型 */
typedef enum
{
    OAM_ALARM_TYPE_MEM_OVER_LEAK,
    OAM_ALARM_TYPE_PKT_RECV_LOST,
    OAM_ALARM_TYPE_PKT_SEND_LOST,

    OAM_ALARM_TYPE_BUTT
}oam_alarm_type_enum;
typedef oal_uint16 oam_alarm_type_enum_uint16;

/* 内存块信息上报类型 */
typedef enum
{
    OAM_MEMBLOCK_INFO_TYPE_UNIFORM,         /* 某一个内存池的所有内存块信息 */
    OAM_MEMBLOCK_INFO_TYPE_NON_UNIFORM,     /* 业务流程中需要查看的任意连续内存的信息 */

    OAM_MEMBLOCK_INFO_TYPE_BUTT
}oam_memblock_info_type_enum;
typedef oal_uint8 oam_memblock_info_type_enum_uint8;

/* STURCT上报事件类型 */
typedef enum
{
    OAM_STRUCT_TYPE_DEVICE,
    OAM_STRUCT_TYPE_HMAC_VAP,
    OAM_STRUCT_TYPE_MAC_VAP,
    OAM_STRUCT_TYPE_DMAC_VAP,
    OAM_STRUCT_TYPE_HMAC_USER,
    OAM_STRUCT_TYPE_MAC_USER,
    OAM_STRUCT_TYPE_DMAC_USER,
    OAM_STRUCT_TYPE_TID,

    OAM_STRUCT_TYPE_BUTT
}oam_struct_type_enum;
typedef oal_uint8 oam_struct_type_enum_uint8;

/* 报文接收统计函数列表 */
typedef enum
{
    OAM_PROFILING_FUNC_RX_COMP_IRQ_START,
    OAM_PROFILING_FUNC_RX_COMP_START,               /* 接收的基准时间 函数:hal_irq_rx_complete_isr */
    OAM_PROFILING_FUNC_RX_COMP_BASE_INFO,           /* 基本信息读写 */
    OAM_PROFILING_FUNC_RX_COMP_ALLOC_EVENT,         /* 申请事件内存 */
    OAM_PROFILING_FUNC_RX_COMP_IRQ_END,


    OAM_PROFILING_FUNC_RX_DMAC_START,               /* 函数:dmac_rx_process_data_event */
    OAM_PROFILING_FUNC_RX_DMAC_GET_CB_LIST,         /* 获取cb 链表*/
    OAM_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU,          /* 处理MPDU*/

    OAM_PROFILING_FUNC_RX_HMAC_START,
    OAM_PROFILING_FUNC_RX_HMAC_BASE_INFO,
    OAM_PROFILING_FUNC_RX_HMAC_TO_LAN,
    OAM_PROFILING_FUNC_RX_HMAC_TO_WLAN,
    OAM_PROFILING_FUNC_RX_HMAC_END,
    OAM_PROFILING_FUNC_RX_DMAC_END,

    OAM_PROFILING_RX_FUNC_BUTT
} oam_profiling_rx_func_enum;
typedef oal_uint8 oam_profiling_rx_func_enum_uint8;

/* ALG统计函数列表 */
typedef enum
{
    OAM_PROFILING_ALG_START,

#ifdef _PRE_WLAN_FEATURE_AUTORATE
    OAM_PROFILING_AUTORATE_QUERY_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_START,
    OAM_PROFILING_AUTORATE_SET_RATE_END,
    OAM_PROFILING_AUTORATE_QUERY_RATE_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_START,
    OAM_PROFILING_AUTORATE_UPDATE_STAT_INFO_END,
    OAM_PROFILING_AUTORATE_UPDATE_RATE_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_NON_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_START,
    OAM_PROFILING_AUTORATE_PROBE_STATE_PROCESS_END,
    OAM_PROFILING_AUTORATE_SELECT_RATE_END,
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_START,
    OAM_PROFILING_TRAFFIC_DOWNLINK_FLOWCTRL_END,
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_START,
    OAM_PROFILING_SCHEDULE_TX_TID_SCH_END,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_START,
    OAM_PROFILING_SCHEDULE_UPDATE_TXTID_END,
    OAM_PROFILING_SCHEDULE_TX_COMP_START,
    OAM_PROFILING_SCHEDULE_TX_COMP_END,
#endif

    OAM_PROFILING_ALG_END,
    OAM_PROFILING_ALG_FUNC_BUTT
} oam_profiling_alg_func_enum;
typedef oal_uint8 oam_profiling_alg_func_enum_uint8;


/* 芯片统计时间加时间戳枚举 */
typedef enum
{
    OAM_PROFILING_STARTTIME_SELF_BEGIN,     /* 测量profiling函数本身时间开销 */
    OAM_PROFILING_STARTTIME_SELF_END,
    OAM_PROFILING_STARTTIME_SOC_BEGIN,
    OAM_PROFILING_STARTTIME_SOC_END,
    OAM_PROFILING_STARTTIME_MAC_BEGIN,
    OAM_PROFILING_STARTTIME_MAC_END,
    OAM_PROFILING_STARTTIME_PHY_BEGIN,
    OAM_PROFILING_STARTTIME_PHY_END,
    OAM_PROFILING_STARTTIME_ABB_BEGIN,
    OAM_PROFILING_STARTTIME_ABB_END,
    OAM_PROFILING_STARTTIME_RF_BEGIN,
    OAM_PROFILING_STARTTIME_RF_END,

    OAM_PROFILING_RESET_HW_BEGIN,
    OAM_PROFILING_RESET_HW_END,
    OAM_PROFILING_RESET_TOTAL_BEGIN,
    OAM_PROFILING_RESET_TOTAL_END,

    OAM_PROFILING_STARTTIME_FUNC_BUTT
}oam_profiling_starttime_func_enum;
typedef oal_uint8 oam_profiling_starttime_func_enum_uint8;

/* 信道切换时间枚举 */
typedef enum
{
    OAM_PROFILING_CHSWITCH_START,
    OAM_PROFILING_CHSWITCH_END,

    OAM_PROFILING_CHSWITCH_FUNC_BUTT
}oam_profiling_chswitch_func_enum;
typedef oal_uint8 oam_profiling_chswitch_func_enum_uint8;


/* SDT操作模式枚举 */
typedef enum
{
    OAM_SDT_MODE_WRITE = 0,
    OAM_SDT_MODE_READ,

    OAM_SDT_MODE_BUTT
}oam_sdt_rw_mode_enum;
typedef oal_uint8 oam_sdt_rw_mode_enum_uint8;

/* SDT打印beacon帧和beacon帧接收描述符的开关类型,其中beacon帧的打印收发流程都适用 */
typedef enum
{
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BEACON = 1,    /* 打印beacon帧，不打印beacon帧的接收描述符 */
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_RXDSCR,        /* 打印beacon帧的接收描述符，不打印beacon帧 */
    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH,          /* 打印beacon帧以及接收描述符 */

    OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BUTT
}oam_sdt_print_beacon_rxdscr_type_enum;
typedef oal_uint8 oam_sdt_print_beacon_rxdscr_type_enum_uint8;

/* 表明帧是属于接收流程还是发送流程的枚举 */
typedef enum
{
    OAM_OTA_FRAME_DIRECTION_TYPE_TX = 0,
    OAM_OTA_FRAME_DIRECTION_TYPE_RX,

    OAM_OTA_FRAME_DIRECTION_TYPE_BUTT
}oam_ota_frame_direction_type_enum;
typedef oal_uint8 oam_ota_frame_direction_type_enum_uint8;

typedef enum
{
    OAM_NL_CMD_SDT = 0,    /* SDT模块 */
    OAM_NL_CMD_HUT,        /* HUT模块 */
    OAM_NL_CMD_ALG,        /* ALG模块 */
    OAM_NL_CMD_ACS,        /* ACS模块 */
    OAM_NL_CMD_DAQ,
    OAM_NL_CMD_REG,        /* 寄存器读取模块 */

    OAM_NL_CMD_BUTT
}oam_nl_cmd_enum;
typedef oal_uint8 oam_nl_cmd_enum_uint8;

/* 特性宏的缩写见gst_oam_feature_list */
typedef enum
{
    OAM_SF_SCAN                 = 0,
    OAM_SF_AUTH,
    OAM_SF_ASSOC,
    OAM_SF_FRAME_FILTER,
    OAM_SF_WMM,

    OAM_SF_DFS                  = 5,
    OAM_SF_NETWORK_MEASURE,
    OAM_SF_ENTERPRISE_VO,
    OAM_SF_HOTSPOTROAM,
    OAM_SF_NETWROK_ANNOUNCE,

    OAM_SF_NETWORK_MGMT         = 10,
    OAM_SF_NETWORK_PWS,
    OAM_SF_PROXYARP,
    OAM_SF_TDLS,
    OAM_SF_CALIBRATE,

    OAM_SF_EQUIP_TEST           = 15,
    OAM_SF_CRYPTO,
    OAM_SF_WPA,
    OAM_SF_WEP,
    OAM_SF_WPS,

    OAM_SF_PMF                  = 20,
    OAM_SF_WAPI,
    OAM_SF_BA,
    OAM_SF_AMPDU,
    OAM_SF_AMSDU,

    OAM_SF_STABILITY            = 25,
    OAM_SF_TCP_OPT,
    OAM_SF_ACS,
    OAM_SF_AUTORATE,
    OAM_SF_TXBF,

    OAM_SF_DYN_RECV             = 30,                        /* dynamin recv*/
    OAM_SF_VIVO,                            /* video_opt voice_opt */
    OAM_SF_MULTI_USER,
    OAM_SF_MULTI_TRAFFIC,
    OAM_SF_ANTI_INTF,

    OAM_SF_EDCA                 = 35,
    OAM_SF_SMART_ANTENNA,
    OAM_SF_TPC,
    OAM_SF_TX_CHAIN,
    OAM_SF_RSSI,

    OAM_SF_WOW                  = 40,
    OAM_SF_GREEN_AP,
    OAM_SF_PWR,                             /* psm uapsd fastmode */
    OAM_SF_SMPS,
    OAM_SF_TXOP,

    OAM_SF_WIFI_BEACON          = 45,
    OAM_SF_KA_AP,                           /* keep alive ap */
    OAM_SF_MULTI_VAP,
    OAM_SF_2040,                            /* 20m+40m coex*/
    OAM_SF_DBAC,

    OAM_SF_PROXYSTA             = 50,
    OAM_SF_UM,                              /* user managment */
    OAM_SF_P2P,								/* P2P 特性 */
    OAM_SF_M2U,
    OAM_SF_IRQ,                             /* top half */

    OAM_SF_TX                   = 55,
    OAM_SF_RX,
    OAM_SF_DUG_COEX,
    OAM_SF_CFG,                             /* wal dmac config函数 */
    OAM_SF_FRW,                             /* frw层 */

    OAM_SF_KEEPALIVE            = 60,
    OAM_SF_COEX,
    OAM_SF_HS20                 = 62,	    /* HotSpot 2.0特性 */
    OAM_SF_MWO_DET,
    OAM_SF_CCA_OPT,

    OAM_SF_ROAM                 = 65,       /* roam module, #ifdef _PRE_WLAN_FEATURE_ROAM */
    OAM_SF_DFT,
    OAM_SF_DFR,
    OAM_SF_BACKUP,
    OAM_SF_ANY,                             /* rifs protection shortgi frag datarate countrycode
                                                coustom_security startup_time lsig monitor wds
                                                hidessid */
    OAM_SOFTWARE_FEATURE_BUTT
}oam_feature_enum;
typedef oal_uint8   oam_feature_enum_uint8;

typedef enum
{
    OAM_RATELIMIT_TYPE_PRINTK        = 0,
    OAM_RATELIMIT_TYPE_LOG,
    OAM_RATELIMIT_TYPE_DSCR,
    OAM_RATELIMIT_TYPE_FRAME_WLAN,
    OAM_RATELIMIT_TYPE_FRAME_ETH,
    OAM_RATELIMIT_TYPE_CB,
    OAM_RATELIMIT_TYPE_BUTT
}oam_ratelimit_type_enum;
typedef oal_uint8   oam_ratelimit_type_enum_uint8;

#define OAM_EXCP_STATS_TIMEOUT          (5000)
/* 该枚举类型不建议频繁添加,只适用于异常原因明确的分支,周期上报异常触发日志 */
typedef enum
{
    OAM_HAL_MAC_ERROR_PARA_CFG_ERR                  = 0,        /*描述符参数配置异常,包括AMPDU长度配置不匹配,AMPDU中MPDU长度超长,sub msdu num错误*/
    OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL          = 1,        /*接收非AMSDU帧长大于RxBuff大小异常*/
    OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND            = 2,        /*未找到BA会话表项异常0*/
    OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT             = 3,        /*PHY_RX_TRAILER超时*/
    OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN           = 4,        /*PHY_RX_FIFO满写异常*/
    OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK             = 5,        /*发送帧数据断流*/
    OAM_HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT             = 6,        /*RX_FSM状态机超时*/
    OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT             = 7,        /*TX_FSM状态机超时*/
    OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT         = 8,        /*RX_HANDLER状态机超时*/
    OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT         = 9,        /*TX_HANDLER状态机超时*/
    OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN          = 10,       /*TX 中断FIFO满写*/
    OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN          = 11,       /*RX中断 FIFO满写*/
    OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN        = 12,       /*HIRX中断FIFO满写*/
    OAM_HAL_MAC_ERROR_RX_Q_EMPTY                    = 13,       /*接收到普通优先级帧但此时RX BUFFER指针为空*/
    OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY                  = 14,       /*接收到高优先级帧但此时HI RX BUFFER指针为空*/
    OAM_HAL_MAC_ERROR_BUS_RLEN_ERR                  = 15,       /*总线读请求长度为0异常*/
    OAM_HAL_MAC_ERROR_BUS_RADDR_ERR                 = 16,       /*总线读请求地址无效异常*/
    OAM_HAL_MAC_ERROR_BUS_WLEN_ERR                  = 17,       /*总线写请求长度为0异常*/
    OAM_HAL_MAC_ERROR_BUS_WADDR_ERR                 = 18,       /*总线写请求地址无效异常*/
    OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN             = 19,       /*tx acbk队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN             = 20,       /*tx acbe队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN             = 21,       /*tx acvi队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN             = 22,       /*tx acv0队列fifo满写*/
    OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN            = 23,       /*tx hipri队列fifo满写*/
    OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT           = 24,       /*matrix计算超时*/
    OAM_HAL_MAC_ERROR_CCA_TIMEOUT                   = 25,       /*cca超时*/
    OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP             = 26,       /*数采overlap告警*/
    OAM_HAL_MAC_ERROR_BEACON_MISS                   = 27,       /*连续发送beacon失败*/
    OAM_HAL_MAC_ERROR_UNKOWN_28                     = 28,
    OAM_HAL_MAC_ERROR_UNKOWN_29                     = 29,
    OAM_HAL_MAC_ERROR_UNKOWN_30                     = 30,
    OAM_HAL_MAC_ERROR_UNKOWN_31                     = 31,

    OAM_HAL_SOC_ERROR_BUCK_OCP                      = 32,       /* PMU BUCK过流中断 */
    OAM_HAL_SOC_ERROR_BUCK_SCP,                                 /* PMU BUCK短路中断 */
    OAM_HAL_SOC_ERROR_OCP_RFLDO1,                               /* PMU RFLDO1过流中断 */
    OAM_HAL_SOC_ERROR_OCP_RFLDO2,                               /* PMU RFLDO2过流中断 */
    OAM_HAL_SOC_ERROR_OCP_CLDO,                                 /* PMU CLDO过流中断 */
    OAM_HAL_SOC_ERROR_RF_OVER_TEMP,                             /* RF过热中断 */
    OAM_HAL_SOC_ERROR_CMU_UNLOCK,                               /* CMU PLL失锁中断 */
    OAM_HAL_SOC_ERROR_PCIE_SLV_ERR,

    OAM_EXCP_TYPE_BUTT
}oam_excp_type_enum;
typedef oal_uint8   oam_excp_type_enum_uint8;

typedef enum
{
    OAM_EXCP_STATUS_INIT = 0,            /* 初始状态:上报完成后切换至初始状态 */
    OAM_EXCP_STATUS_REFRESHED,           /* 有更新，可上报； */
    OAM_EXCP_STATUS_BUTT
}oam_excp_status_enum;
typedef oal_uint8   oam_excp_status_enum_uint8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* 维测，下发调试类型值，代码可临时根据调测值实现相应功能 */
#ifdef _PRE_DEBUG_MODE
extern oal_uint32   g_aul_debug_feature_switch[];

#define             MAX_DEBUG_TYPE_NUM              OAM_DEBUG_TYPE_BUTT
typedef enum
{
    OAM_DEBUG_TYPE_ECHO_REG          = 0,

    OAM_DEBUG_TYPE_BUTT
}oam_debug_type_enum;

#endif

#ifdef _PRE_WLAN_DFT_STAT
typedef enum
{
    OAM_STATS_PHY_NODE_TX_CNT = 1,
    OAM_STATS_PHY_NODE_RX_OK_CNT,
    OAM_STATS_PHY_NODE_SYN_CNT,
    OAM_STATS_PHY_NODE_OFDM_SYN_ERR_CNT,
    OAM_STATS_PHY_NODE_AGC_LOCK_CNT,
    OAM_STATS_PHY_NODE_11B_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_OFDM_HDR_ERR_CNT,
    OAM_STATS_PHY_NODE_UNSUPPORTED_CNT,
    OAM_STATS_PHY_NODE_CARRIER_LOSE_CNT,
    OAM_STATS_PHY_NODE_LDPC_FAIL_CNT,
    OAM_STATS_PHY_NODE_RX_TIMEOUT_CNT,
    OAM_STATS_PHY_NODE_HI_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_LO_PIN_UNLOCK_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_LARGER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_SMALLER_CNT,
    OAM_STATS_PHY_NODE_INIT_BW_EQUAL_CNT,

    OAM_STATS_PHY_NODE_BUTT
}oam_stats_phy_node_idx_enum;
typedef oal_uint8 oam_stats_phy_node_idx_enum_uint8;
#endif

extern oal_uint8 g_auc_bcast_addr[WLAN_MAC_ADDR_LEN];
#define BROADCAST_MACADDR       g_auc_bcast_addr

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
typedef oal_int32   (* oam_sdt_up_func)(oal_netbuf_stru *pst_netbuf);
typedef oal_int32   (* oam_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
typedef oal_int32   (* oam_sdt_status_func)(oal_void);

/* 其他模块调用SDT钩子函数 用结构体 */
typedef struct
{
    oal_int32       (* p_sdt_report_data_func)(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim);
    oal_int32       (* p_sdt_get_wq_len_func)(oal_void);
}oam_sdt_func_hook_stru;

/* 外部函数声明 */
extern oam_sdt_func_hook_stru       g_st_oam_sdt_func_hook;

oam_sdt_func_hook_stru          g_st_oam_sdt_func_hook;

/* 其他模块调用WAL钩子函数 用结构体 */
typedef struct
{
   oal_int32       (* p_wal_recv_mem_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_reg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_cfg_data_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
   oal_int32       (* p_wal_recv_global_var_func)(oal_uint8 *puc_buf, oal_uint16 us_len);
}oam_wal_func_hook_stru;

extern oam_wal_func_hook_stru       g_st_oam_wal_func_hook;

/*lint -e958*/ /*lint -e959*/
/* 读取和设置全局变量的结构体 */
typedef struct
{
    oal_uint32  ul_offset;
    oal_uint8   uc_lenth;
    oal_uint8   uc_mode;
    oal_uint8   auc_val[4];
    oal_uint8   auc_var_name[4];
}oal_sdt_global_var_stru;
/*lint -e958*/ /*lint -e959*/

/* VAPID 日志级别结构体 */
typedef struct
{
    oam_feature_enum_uint8              en_feature_id;
    oam_log_level_enum_uint8            en_log_level;
    oal_switch_enum_uint8               en_switch;
    oal_uint8                           uc_resv;
}oam_cfg_log_level_stru;

/* oam模块保存的日志 */
typedef struct
{
    oam_log_info_stru                ast_log_info[OAM_LOG_INFO_IN_MEM_MAX_NUM];
    oal_uint16                       us_index;               /* 当前刚保存的log在数组中的位置 */
}oam_log_info_in_mem_stru;


/* 定时器创建删除追踪信息结构 */
typedef struct
{
    oal_uint32                      ul_file_id;
    oal_uint32                      ul_line_num;
    oam_timer_track_type_enum_uint8 en_type;
    oal_uint8                       auc_resv[3];
}oam_timer_track_info_stru;

/* 上报mpdu数目结构 */
typedef struct
{
    oal_uint16              us_total_mpdu_num_in_device;   /* device下所有TID中总共的mpdu_num数量 */
    oal_uint16              us_mpdu_num_in_tid0;
    oal_uint16              us_mpdu_num_in_tid1;
    oal_uint16              us_mpdu_num_in_tid2;
    oal_uint16              us_mpdu_num_in_tid3;
    oal_uint16              us_mpdu_num_in_tid4;
    oal_uint16              us_mpdu_num_in_tid5;
    oal_uint16              us_mpdu_num_in_tid6;
    oal_uint16              us_mpdu_num_in_tid7;
    oal_uint8               auc_resv[2];
}oam_report_mpdu_num_stru;

/* OTA头部信息 */
typedef struct
{
    oal_uint32                              ul_tick;            /* 时间戳，精度ms */
    oam_ota_type_enum_uint8                 en_ota_type;        /* OTA类型 */
    oal_uint8                               uc_frame_hdr_len;   /* 如果是帧，代表帧头长度；如果是其它类型，此字段没有用 */
    oal_uint16                              us_ota_data_len;    /* OTA数据长度，如果是帧，代表帧头和帧体的总长度 */
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction; /* 表明帧是属于发送流程还是接收流程，只有ota_type是帧的时候这个字段才有意义 */
    oal_uint8                               auc_resv[1];
}oam_ota_hdr_stru;

/* OTA数据结构体 */
typedef struct
{
    oam_ota_hdr_stru                st_ota_hdr;         /* OTA头部信息 */
    oal_uint8                       auc_ota_data[4];    /* OTA数据 */
}oam_ota_stru;

/* 消息上报给SDT封装的结构体 */
/* EVENT消息体最大长度 */
#define OAM_EVENT_INFO_MAX_LEN          48

typedef struct
{
    oal_uint32				         ul_tick;                            /* 消息时间 */
    oam_event_type_enum_uint16	     en_event_type;                      /* 消息类型，WID，抛事件，状态转移等 */
 	oam_module_id_enum_uint16        en_module;                          /* 模块 */
 	oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                        uc_vap_id;                          /* vap id */
    oal_uint8                        auc_resv[1];                        /* 保留 */
}oam_event_hdr_stru;

typedef struct
{
    oam_event_hdr_stru               st_event_hdr;         /* EVENT头部信息 */
	oal_int8                         auc_event_info[OAM_EVENT_INFO_MAX_LEN];  /* 消息内容，最多保存50个字节 */
}oam_event_stru;


#define OAM_EVENT_STRU_SIZE         OAL_SIZEOF(oam_event_stru)

/* 内存池使用信息查询 */
typedef struct
{
    oal_uint8                               uc_mem_pool_id;
    oal_uint8                               uc_subpool_id;
    oal_uint8                               auc_resv[2];
    oal_uint16                              us_mem_pool_total_cnt;
    oal_uint16                              us_mem_pool_used_cnt;
    oal_uint16                              us_subpool_total_cnt;
    oal_uint16                              us_subpool_free_cnt;
}oam_stats_mempool_stru;

/* 内存块使用信息，包括标准内存块信息，和任意某一块连续内存信息 */
typedef struct
{
    oal_uint8                               uc_pool_id;                 /* 如果是任意连续内存 */
    oal_uint8                               uc_subpool_id;
    oal_uint8                               uc_user_cnt;                /* 本内存块的引用计数 */
    oal_uint8                               auc_resv[1];
    oal_uint32                              ul_file_id;                 /* 申请该内存块的文件号 */
    oal_uint32                              ul_alloc_line_num;          /* 申请该内存块的行号 */
}oam_memblock_info_stru;

/* 事件队列使用情况信息结构体 */
typedef struct
{
    oal_uint8							    en_type;                    /* 事件类型 */
    oal_uint8                               uc_sub_type;                /* 事件子类型 */
    oal_uint16                              us_length;                  /* 事件长度 */
    oal_uint8                               en_pipeline;                /* 事件分段号 */
    oal_uint8                               uc_chip_id;                 /* 芯片ID */
    oal_uint8                               uc_device_id;               /* 设备ID */
    oal_uint8                               uc_vap_id;                  /* VAP ID */
}oam_event_hdr_info_stru;

/* 上报给SDT事件队列使用情况信息 */
typedef struct
{
    oal_uint8                               uc_event_num_in_queue;      /* 当前事件队列中事件的个数 */
    oal_uint8                               auc_resv[3];

    oam_event_hdr_info_stru                 ast_event_hdr_info[OAM_MAX_EVENT_NUM_IN_EVENT_QUEUE];
}oam_event_queue_info_stru;


#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151 || _PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/* 设备级别统计信息结构体 */
typedef struct
{
    /**************************************************************************
                               中断个数统计信息
    **************************************************************************/
    /* 总的中断请求个数 */
    oal_uint32  ul_irq_cnt;

    /* SOC五类中断计数 */
    oal_uint32  ul_pmu_err_irq_cnt;                 /* 电源错误中断 */
    oal_uint32  ul_rf_over_temp_irq_cnt;            /* RF过热中断 */
    oal_uint32  ul_unlock_irq_cnt;                  /* CMU PLL失锁中断 */
    oal_uint32  ul_mac_irq_cnt;                     /* Mac业务中断 */
    oal_uint32  ul_pcie_slv_err_irq_cnt;            /* PCIE总线错误中断 */

    /* pmu/buck错误子中断源计数 */
    oal_uint32  ul_buck_ocp_irq_cnt;                /* BUCK过流中断 */
    oal_uint32  ul_buck_scp_irq_cnt;                /* BUCK短路中断 */
    oal_uint32  ul_ocp_rfldo1_irq_cnt;              /* PMU RFLDO1过流中断 */
    oal_uint32  ul_ocp_rfldo2_irq_cnt;              /* PMU RFLDO2过流中断 */
    oal_uint32  ul_ocp_cldo_irq_cnt;                /* PMU CLDO过流中断 */

    /* MAC子中断源计数(与MACINTERRUPT_STATUS寄存器对应) */
    oal_uint32  ul_rx_complete_cnt;                 /* 数据帧接收完成 */
    oal_uint32  ul_tx_complete_cnt;                 /* 发送完成 */
    oal_uint32  ul_hi_rx_complete_cnt;              /* 管理帧、控制帧接收完成 */
    oal_uint32  ul_error_cnt;                       /* error中断 */
    oal_uint32  aul_tbtt_cnt[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];/* tbtt中断,0~3代表ap的，4代表sta的 */
    oal_uint32  ul_abort_intr_start;
    oal_uint32  ul_abort_intr_end;
    oal_uint32  ul_radar_detect_cnt;                /* 检测到雷达 */
    oal_uint32  ul_pa_tx_suspended;
    oal_uint32  ul_de_authentication;
    oal_uint32  ul_one_packet;
    oal_uint32  ul_abort_intr_done;
    oal_uint32  ul_ch_statistics_cnt;               /* 信道统计完成中断 */
    oal_uint32  ul_wow_prep_done;
    oal_uint32  ul_other_int_cnt;                   /* 其它 */

    /* MAC错误中断类型, 注意此处枚举值与错误中断状态寄存器的位一一对应 ! */
    oal_uint32  aul_mac_error_cnt[OAM_MAC_ERROR_TYPE_CNT];

    /* 接收中断上报频度统计 */
    oal_uint32  ul_normal_rx_idx;                   /* 当前中断时间戳所在位置 */
    oal_uint32  ul_hi_rx_idx;                       /* 当前中断时间戳所在位置 */
    oal_uint32  aul_rx_freq[OAM_RX_DSCR_QUEUE_CNT][OAM_IRQ_FREQ_STAT_MEMORY];   /* 接收频度统计，时间戳精度10ns */
    oal_uint32  ul_rx_freq_stop_flag;               /* 接收频度标志，一旦上报fifo overun之后则停止统计 */

    /* 中断时延统计, 单位10ns */
    oal_uint32  ul_max_delay;                       /* 最大时长 */
    oal_uint32  ul_min_delay;                       /* 最小时长 */
    oal_uint32  ul_delay_sum;                       /* 总时长 */
    oal_uint32  ul_timer_start;                     /* 开始时间记录 */
}oam_device_stat_info_stru;

/* VAP级别统计信息结构 */
typedef struct
{
    /***************************************************************************
                                接收包统计
    ***************************************************************************/

    /* 发往lan的数据包统计 */
    oal_uint32  ul_rx_pkt_to_lan;                               /* 接收流程发往以太网的数据包数目，MSDU */
    oal_uint32  ul_rx_bytes_to_lan;                             /* 接收流程发往以太网的字节数 */

    /* 接收流程遇到严重错误(描述符异常等)，释放所有MPDU的统计 */
    oal_uint32  ul_rx_ppdu_dropped;                             /* 硬件上报的vap_id错误，释放的MPDU个数 */

    /* 软件统计的接收到MPDU个数，正常情况下应该与MAC硬件统计值相同 */
    oal_uint32  ul_rx_mpdu_total_num;                           /* 接收流程上报到软件进行处理的MPDU总个数 */

    /* MPDU级别进行处理时发生错误释放MPDU个数统计 */
    oal_uint32  ul_rx_ta_check_dropped;                         /* 检查发送端地址异常，释放一个MPDU */
    oal_uint32  ul_rx_da_check_dropped;                         /* 检查目的端地址异常，释放一个MPDU */
    oal_uint32  ul_rx_phy_perform_dropped;                      /* 测试phy性能，将帧直接释放 */
    oal_uint32  ul_rx_key_search_fail_dropped;                  /*  */
    oal_uint32  ul_rx_tkip_mic_fail_dropped;                    /* 接收描述符status为 tkip mic fail释放MPDU */
    oal_uint32  ul_rx_replay_fail_dropped;                      /* 重放攻击，释放一个MPDU */
    oal_uint32  ul_rx_11i_check_fail_dropped;
    oal_uint32  ul_rx_wep_check_fail_dropped;
    oal_uint32  ul_rx_alg_process_dropped;                      /* 算法处理返回失败 */
    oal_uint32  ul_rx_null_frame_dropped;                       /* 接收到空帧释放(之前节能特性已经对其进行处理) */
    oal_uint32  ul_rx_abnormal_dropped;                         /* 其它异常情况释放MPDU */
    oal_uint32  ul_rx_mgmt_abnormal_dropped;                    /* 接收到管理帧出现异常，比如vap或者dev为空等 */
    oal_uint32  ul_rx_ack_dropped;                              /* ack直接过滤掉 */
    oal_uint32  ul_rx_pspoll_process_dropped;                   /* 处理ps-poll的时候释放包 */
    oal_uint32  ul_rx_bar_process_dropped;                      /* 处理block ack req释放包 */
    oal_uint32  ul_rx_abnormal_cnt;                             /* 处理MPDU时发现异常的次数，并非丢包数目 */

    oal_uint32  ul_rx_no_buff_dropped;                          /* 组播帧或者wlan_to_wlan流程申请buff失败 */
    oal_uint32  ul_rx_defrag_process_dropped;                   /* 去分片处理失败 */
    oal_uint32  ul_rx_de_mic_fail_dropped;                      /* mic码校验失败 */
    oal_uint32  ul_rx_portvalid_check_fail_dropped;             /* 接收到数据帧，安全检查失败释放MPDU */

    /* 接收到组播帧个数 */
    oal_uint32  ul_rx_mcast_cnt;

    /* 管理帧统计 */
    oal_uint32  aul_rx_mgmt_num[WLAN_MGMT_SUBTYPE_BUTT];        /* VAP接收到各种管理帧的数目统计 */


    /***************************************************************************
                                发送包统计
    ***************************************************************************/

    /* 从lan接收到的数据包统计 */
    oal_uint32  ul_tx_pkt_num_from_lan;                         /* 从lan过来的包数目,MSDU */
    oal_uint32  ul_tx_bytes_from_lan;                           /* 从lan过来的字节数 */

    /* 发送流程发生异常导致释放的数据包统计，MSDU级别 */
    oal_uint32  ul_tx_abnormal_msdu_dropped;                    /* 异常情况释放MSDU个数，指vap或者user为空等异常 */
    oal_uint32  ul_tx_security_check_faild;                     /* 安全检查失败释放MSDU */
    oal_uint32  ul_tx_abnormal_mpdu_dropped;                    /* 异常情况释放MPDU个数，指vap或者user为空等异常 */
    oal_uint32  ul_tx_uapsd_process_dropped;                    /* UAPSD特性处理失败，释放MPDU个数 */
    oal_uint32  ul_tx_psm_process_dropped;                      /* PSM特性处理失败，释放MPDU个数 */
    oal_uint32  ul_tx_alg_process_dropped;                      /* 算法处理认为应该丢包，释放MPDU个数 */

    /* 发送完成中发送成功与失败的数据包统计，MPDU级别 */
    oal_uint32  ul_tx_mpdu_succ_num;                            /* 发送MPDU总个数 */
    oal_uint32  ul_tx_mpdu_fail_num;                            /* 发送MPDU失败个数 */
    oal_uint32  ul_tx_ampdu_succ_num;                           /* 发送成功的AMPDU总个数 */
    oal_uint32  ul_tx_ampdu_bytes;                              /* 发送AMPDU总字节数 */
    oal_uint32  ul_tx_mpdu_in_ampdu;                            /* 属于AMPDU的MPDU发送总个数 */
    oal_uint32  ul_tx_ampdu_fail_num;                           /* 发送AMPDU失败个数 */
    oal_uint32  ul_tx_mpdu_fail_in_ampdu;                       /* 属于AMPDU的MPDU发送失败个数 */

    /* 组播转单播发送流程统计 */
    oal_uint32  ul_tx_m2u_ucast_cnt;                            /* 组播转单播 单播发送成功个数 */
    oal_uint32  ul_tx_m2u_ucast_droped;                         /* 组播转单播 单播发送失败个数 */
    oal_uint32  ul_tx_m2u_mcast_cnt;                            /* 组播转单播 组播发送成功个数 */
    oal_uint32  ul_tx_m2u_mcast_droped;                         /* 组播转单播 组播发送成功个数 */

    /* 管理帧统计 */
    oal_uint32  aul_tx_mgmt_num_sw[WLAN_MGMT_SUBTYPE_BUTT];     /* VAP挂到硬件队列上的各种管理帧的数目统计 */
    oal_uint32  aul_tx_mgmt_num_hw[WLAN_MGMT_SUBTYPE_BUTT];     /* 发送完成中各种管理帧的数目统计 */
}oam_vap_stat_info_stru;

/* USER级别统计信息结构 */
typedef struct
{
    /* 接收包统计，从某个用户处接收到的包统计(TO DS) */
    oal_uint32  ul_rx_mpdu_num;                                 /* 从某个用户接收到的MPDU数目 */

    /* 发送包统计，发送给某个用户的包统计(FROM DS)，粒度是TID(具体到从VAP的某个TID发出) */
    oal_uint32  aul_tx_mpdu_succ_num[WLAN_TIDNO_BUTT];          /* 发送MPDU总个数 */
    oal_uint32  aul_tx_mpdu_fail_num[WLAN_TIDNO_BUTT];          /* 发送MPDU失败个数 */
    oal_uint32  aul_tx_ampdu_succ_num[WLAN_TIDNO_BUTT];         /* 发送AMPDU总个数 */
    oal_uint32  aul_tx_ampdu_bytes[WLAN_TIDNO_BUTT];            /* 发送AMPDU总字节数 */
    oal_uint32  aul_tx_mpdu_in_ampdu[WLAN_TIDNO_BUTT];          /* 属于AMPDU的MPDU发送总个数 */
    oal_uint32  aul_tx_ampdu_fail_num[WLAN_TIDNO_BUTT];         /* 发送AMPDU失败个数 */
    oal_uint32  aul_tx_mpdu_fail_in_ampdu[WLAN_TIDNO_BUTT];     /* 属于AMPDU的MPDU发送失败个数 */
}oam_user_stat_info_stru;

/* 统计结构信息，包括设备级别，vap级别，user级别的各种统计信息 */
typedef struct
{
    /* 设备级别的统计信息 */
    oam_device_stat_info_stru               ast_dev_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];

    /* VAP级别的统计信息 */
    oam_vap_stat_info_stru                  ast_vap_stat_info[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];

    /* USER级别的统计信息 */
    oam_user_stat_info_stru                 ast_user_stat_info[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM];
}oam_stat_info_stru;
#endif

/*lint -e717*/
#define OAM_SDT_STAT_INCR(_cnt)             do{g_st_sdt_stat_info._cnt++;} while(0)

enum oam_filter_type_enum
{
    OAM_FLT_PASS = 0,
    OAM_FLT_DROP,
    OAM_FLT_BUTT,
};

typedef struct
{
    oal_uint32      ul_nlk_sd_cnt;         /* 上报消息总数:含失败个数*/
    oal_uint32      ul_nlk_sd_fail;        /* 发送失败统计 */
    oal_uint32      ul_wq_len;              /* 队列中消息个数 */
    oal_uint32      ul_filter_cnt;          /* 过滤消息个数 */
    oal_bool_enum   en_filter_switch;       /* 过滤开关状态 */
	oal_uint8		uc_recv[3];
}oam_sdt_stat_info_stru;

extern oam_sdt_stat_info_stru g_st_sdt_stat_info;

/* 保存配置文件相关信息结构 */
typedef struct
{
    oam_cfg_type_enum_uint16            en_cfg_type;
    oal_int8                           *pc_section;                /* 配置项所属的section字符串 */
    oal_int8                           *pc_key;                    /* 配置项在配置文件中的字符串表示 */
    oal_int32                           l_val;                     /* 配置项的值 */
}oam_cfg_data_stru;


#ifdef _PRE_DEBUG_MODE
typedef struct
{
    /* 用于统计发送完成中断是否丢失(非聚合) */
    oal_uint32          ul_tx_data_num;           /* 放入硬件队列的非聚合帧个数 */
    oal_uint32          ul_tx_mgnt_num;           /* 发送管理帧的个数 */
    oal_uint32          ul_tx_complete_total_num; /* 所有发送完成中断的个数 */
    oal_uint32          ul_tx_complete_uh1_num;   /* 发送完成中断上半部统计次数1(函数入口处) */
    oal_uint32          ul_tx_complete_uh2_num;   /* 发送完成中断上半部统计次数2(函数出口处) */
    oal_uint32          ul_tx_complete_bh1_num;   /* 发送完成中断下半部统计次数1(函数入口处) */
    oal_uint32          ul_tx_complete_bh2_num;   /* 发送完成中断下半部统计次数2(函数出口处) */
    oal_uint32          ul_tx_complete_bh3_num;   /* 发送完成中断下半部统计次数3(释放netbuf处) */
}oam_tx_complete_stat_stru;
#endif

/* 异常统计结构体:当ul_reported_cnt与ul_record_cnt相同时*/
typedef struct
{
    oal_uint32              en_status;                 /* 每类异常类型是否刷新 */
    oal_uint32              ul_record_cnt;             /* 记录上一次更新的次数 */
}oam_excp_record_stru;

/* oam异常统计 */
typedef struct
{
    oal_uint32                          en_status;                 /* VAP级别异常统计是否有刷新*/
    oam_excp_record_stru                ast_excp_record_tbl[OAM_EXCP_TYPE_BUTT];
}oam_exception_ctx_stru;

/* VAP日志开关与特性日志级别 */
typedef struct
{
    oal_switch_enum_uint8     aen_vap_log_switch[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];    /* VAP日志开关 */
    oam_log_level_enum_uint8  aen_vap_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];     /* VAP日志开关，INFO级别关闭时恢复 */
    oam_log_level_enum_uint8  aen_feature_log_level[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT][OAM_SOFTWARE_FEATURE_BUTT]; /* 特性日志级别 */
}oam_vap_log_stru;

#define OAM_RATELIMIT_MAX_INTERVAL                    60         /* 60秒 */
#define OAM_RATELIMIT_MIN_INTERVAL                    1          /* 1秒 */
#define OAM_RATELIMIT_DEFAULT_INTERVAL                5          /* 秒 间隔 */
#define OAM_RATELIMIT_MAX_BURST                       60         /* 最大允许打印条数 */
#define OAM_RATELIMIT_MIN_BURST                       1          /* 最大允许打印条数 */
#define OAM_RATELIMIT_DEFAULT_BURST                   10         /* 最大允许打印条数 */

#if 0
/* 日志模块全局结构体 */
typedef struct
{
    oal_switch_enum_uint8               en_global_log_switch;                               /* 日志全局开关 */
    oam_vap_log_stru                    st_vap_log_info;                                    /* VAP日志开关与特性日志级别 */
    oam_ratelimit_stru                  st_ratelimit[OAM_RATELIMIT_TYPE_BUTT];                                       /* 普通printk流控信息 */
}oam_log_ctx_stru;
#endif


/* OAM的EVENT模块的整体控制结构上下文 */
typedef struct
{
    oal_switch_enum_uint8           en_event_switch;                            /* 启动EVENT功能开关 */
    oal_uint8                       auc_resv[3];
}oam_event_ctx_stru;

/* OAM的event模块，具体某一种event的控制开关 */
typedef struct
{
    oal_switch_enum_uint8           aen_specific_event_switch[OAM_EVENT_TYPE_BUTT];
    oal_uint8                       auc_resv[1];
}oam_specific_event_ctx_stru;

/* oam的ota模块，具体某一种ota的控制开关 */
typedef struct
{
#if 0
    oal_switch_enum_uint8           aen_ota_switch[OAM_OTA_TYPE_BUTT];
#endif
    oam_sdt_print_beacon_rxdscr_type_enum_uint8           en_beacon_switch;
    oal_switch_enum_uint8           en_rx_dscr_switch;
//    oal_uint8                       auc_resv[2];
}oam_ota_ctx_stru;

/* OAM的ALARM模块的整体控制结构上下文 */
typedef struct
{
    oal_switch_enum_uint8           en_alarm_switch;                            /* 启动ALARM功能开关 */
    oal_uint8                       auc_resv[3];
}oam_alarm_ctx_stru;

/* 80211帧上报控制结构 */
typedef struct
{
    oal_switch_enum_uint8           en_frame_content_switch;
    oal_switch_enum_uint8           en_frame_cb_switch;
    oal_switch_enum_uint8           en_frame_dscr_switch;
    oal_uint8                       auc_resv[1];
}oam_80211_frame_ctx_stru;

/* 单用户跟踪控制开关结构 */
typedef struct
{
    oam_80211_frame_ctx_stru   ast_80211_mcast_mgmt_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];          /* 80211广播\组播管理帧上报控制结构 */
    oam_80211_frame_ctx_stru   ast_80211_mcast_data_ctx[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];          /* 80211广播\组播数据帧上报控制结构 */
    oam_80211_frame_ctx_stru   ast_80211_ucast_mgmt_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 单播帧开关，不同用户开关可以不同 */
    oam_80211_frame_ctx_stru   ast_80211_ucast_data_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 单播帧开关，不同用户开关可以不同 */
    oam_80211_frame_ctx_stru   aen_80211_probe_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* probe request和probe response太多，单独搞个开关*/
    oal_switch_enum_uint8      aen_eth_data_ctx[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_OTA_FRAME_DIRECTION_TYPE_BUTT];
    oal_switch_enum_uint8      en_tx_mcast_dhcp_arp_switch;
    oal_switch_enum_uint8      aen_data_global_switch[OAM_OTA_FRAME_DIRECTION_TYPE_BUTT]; /* 数据帧流程打印总开关，只要有一个用户的数据开关打开，总开关就开，否则关闭，避免消耗mips */
    oal_switch_enum_uint8      aen_user_info_change_switch[WLAN_ACTIVE_USER_MAX_NUM * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][OAM_USER_INFO_CHANGE_TYPE_BUTT];
}oam_user_track_ctx_stru;

#define OAM_FILE_PATH_LENGTH            256                     /* 用于保存LOG文件地址的字符串最大长度,路径最长为255字节，最后需要有一字节存放\0 */

/******************************************************************************
                          统计与性能维测相关的结构定义
*******************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

/* 反应空口环境繁忙程度的参数结构，有PHY的参数也有MAC的参数 */
typedef struct
{
    oal_uint16          us_mac_ch_stats_period_us;                    /* mac进行信道空闲时间统计的周期，20ms，20000us */
    oal_uint16          us_mac_pri20_free_time_us;                    /* 统计周期内主20M信道空闲时间，us */
    oal_uint16          us_mac_pri40_free_time_us;                    /* 统计周期内主40M信道空闲时间，us */
    oal_uint16          us_mac_pri80_free_time_us;                    /* 统计周期内主80M信道空闲时间,us */
    oal_uint16          us_mac_ch_rx_time_us;                         /* 统计周期内接收占用的时间，us */
    oal_uint16          us_mac_ch_tx_time_us;                         /* 统计周期内发送占用的时间，us */

    oal_uint8           uc_phy_ch_estimate_time_ms;                   /* phy测量信道空闲时功率的周期，ms */
    oal_int8            c_phy_pri20_idle_power_dBm;                   /* 统计周期内主20M信道空闲时的功率，一直不空闲就不统计 */
    oal_int8            c_phy_pri40_idle_power_dBm;                   /* 统计周期内主40M信道空闲时的功率，一直不空闲就不统计 */
    oal_int8            c_phy_pri80_idle_power_dBm;                   /* 统计周期内主80M信道空闲时的功率，一直不空闲就不统计 */

    oal_uint32          aul_beacon_miss_max_num[WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE]; /* mac记录的每个AP BEACON MISS历史最大值 */
    oal_uint32          ul_non_directed_frame_num;
}oam_stats_dbb_env_param_stru;

/* phy统计节点设置，保存节点idx的结构 */
typedef struct
{
    oal_uint8           auc_node_idx[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];
}oam_stats_phy_node_idx_stru;

/* phy的收发包数目统计值，包括用户指定需要的4个，和phy一直统计的8个按照协议模式的统计值 */
typedef struct
{
    oal_uint32          aul_user_requested_stat_cnt[OAM_PHY_STAT_NODE_ENABLED_MAX_NUM];

    /* phy统计的接收到11b,ht,vht,legecy ofdm帧正确和错误的个数 */
    oal_uint32          aul_phy_stat_rx_ppdu_cnt[OAM_PHY_STAT_RX_PPDU_CNT];
}oam_stats_phy_stat_stru;

/* mac统计收发包数目 */
typedef struct
{
    /* rx统计 */
    oal_uint32 ul_machw_rx_ampdu_count;
    oal_uint32 ul_machw_rx_passed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_in_ampdu_cnt;
    oal_uint32 ul_machw_rx_octects_in_ampdu;
    oal_uint32 ul_machw_rx_delimit_fail_count;
    oal_uint32 ul_machw_rx_dup_mpdu_cnt;
    oal_uint32 ul_machw_rx_passed_mpdu_cnt;
    oal_uint32 ul_machw_rx_failed_mpdu_cnt;
    oal_uint32 ul_machw_rx_bcn_cnt;
    oal_uint32 ul_machw_rx_phy_err_mac_passed_cnt;
    oal_uint32 ul_machw_rx_phy_longer_err_cnt;
    oal_uint32 ul_machw_rx_phy_shorter_err_cnt;
    oal_uint32 ul_machw_rx_filtered_cnt;

    /* tx统计 */
    oal_uint32 ul_machw_tx_hi_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_normal_pri_mpdu_cnt;
    oal_uint32 ul_machw_tx_ampdu_count;
    oal_uint32 ul_machw_tx_mpdu_inampdu_count;
    oal_uint32 ul_machw_tx_octects_in_ampdu;
    oal_uint32 ul_machw_tx_bcn_count;
    oal_uint32 ul_machw_tx_normal_pri_retry_cnt;
    oal_uint32 ul_machw_tx_hi_pri_retry_cnt;
}oam_stats_machw_stat_stru;

/* 管理帧收发数目统计，包括硬件统计的发送beacon帧数目和高优先级队列发送数目 */
typedef struct
{
    oal_uint32          ul_machw_stat_tx_bcn_cnt;
    oal_uint32          ul_machw_stat_tx_hi_cnt;
    oal_uint32          aul_sw_rx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_sw_tx_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
    oal_uint32          aul_tx_complete_mgmt_cnt[WLAN_MGMT_SUBTYPE_BUTT];
}oam_stats_mgmt_stat_stru;

/* 用户队列统计信息，包括节能队列和tid队列 */
typedef struct
{
    oal_uint32          aul_uapsd_stat[OAM_UAPSD_STAT_CNT];
    oal_uint32          aul_psm_stat[OAM_PSM_STAT_CNT];
    oal_uint32          aul_tid_stat[WLAN_TID_MAX_NUM][OAM_TID_STAT_CNT];
}oam_stats_usr_queue_stat_stru;

/* vap吞吐统计信息结构，包个数，字节数，平均速率(字节数/上报周期) */
typedef struct
{
    oal_uint32          ul_lan_tx_pkts;     /* 以太网过来的包数目 */
    oal_uint32          ul_lan_tx_bytes;    /* 以太网过来的字节数，不算以太网头 */
    oal_uint32          ul_drv_tx_pkts;     /* 驱动发包数目，交给硬件的数目 */
    oal_uint32          ul_drv_tx_bytes;    /* 驱动发包字节数，不算80211头尾 */
    oal_uint32          ul_hw_tx_pkts;      /* 发送完成中断上报发送成功的个数 */
    oal_uint32          ul_hw_tx_bytes;     /* 发送完成中断上报发送成功字节数 */

    oal_uint32          ul_drv_rx_pkts;     /* 驱动接收包数目 */
    oal_uint32          ul_drv_rx_bytes;    /* 驱动接收字节数，不包括80211头尾 */
    oal_uint32          ul_lan_rx_pkts;     /* 驱动交给以太网包数目 */
    oal_uint32          ul_lan_rx_bytes;    /* 驱动交给以太网字节数，不包括以太网头 */
    oal_uint32          ul_app_rx_pkts;     /* 驱动交给以APP包数目 */
    oal_uint32          ul_app_rx_bytes;    /* 驱动交给以APP字节数，不包括以太网头 */

    /* 平均速率 单位: kbps */
    oal_uint32          ul_lan_tx_rate;     /* lan发包平均速率 */
    oal_uint32          ul_drv_tx_rate;     /* 驱动发包平均速率 */
    oal_uint32          ul_hw_tx_rate;      /* 发送完成上报成功的发包平均速率 */
    oal_uint32          ul_drv_rx_rate;     /* 驱动收包平均速率 */
    oal_uint32          ul_lan_rx_rate;     /* lan收包平均速率 */
}oam_stats_vap_stat_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    /* 接收方向统计 */

    oal_uint32          ul_ba_recipient_tid_recv_pkt;    /* 该TID建立BA会话后，接收数据包数目 */
    oal_uint32          ul_ba_recipient_no_ba_session;
    oal_uint32          ul_ba_recipient_recv_ampdu_no_ba;
    oal_uint32          ul_ba_recipient_send_delba_count;
    oal_uint32          ul_ba_recipient_dup_frame_count;
    oal_uint32          ul_ba_recipient_dup_frame_drop_count;
    oal_uint32          ul_ba_recipient_dup_frame_up_count;
    oal_uint32          ul_ba_recipient_direct_up_count;
    oal_uint32          ul_ba_recipient_buffer_frame_count;
    oal_uint32          ul_ba_recipient_buffer_frame_overlap_count;
    oal_uint32          ul_ba_recipient_between_baw_count;
    oal_uint32          ul_ba_recipient_greater_baw_count;
    oal_uint32          ul_ba_recipient_sync_loss_count;
    oal_uint32          ul_ba_recipient_update_hw_baw_count;

}oam_stats_ampdu_stat_stru;
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明    OAM模块对外提供的接口
*****************************************************************************/

extern oal_uint32 oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);
extern oal_int32  oam_main_init(oal_void);
extern oal_void  oam_main_exit(oal_void);
extern oal_uint32  oam_print(oal_int8 *pc_string);
extern oal_uint32  oam_set_file_path(oal_int8 *pc_file_path, oal_uint32 ul_length);
extern oal_uint32  oam_set_output_type(oam_output_type_enum_uint8 en_output_type);
extern oal_uint32  oam_get_output_type(oam_output_type_enum_uint8 *pen_output_type);


/*******************************************************************************
            LOG模块对外接口
*******************************************************************************/
extern oal_void oam_exception_stat_handler(oam_msg_moduleid_enum_uint8 en_moduleid, oal_uint8 uc_vap_idx);

extern oal_uint32 oam_log_set_global_switch(oal_switch_enum_uint8 en_log_switch);
extern oal_uint32 oam_log_set_vap_switch(oal_uint8 uc_vap_id,
                                         oal_switch_enum_uint8    en_log_switch);

#if 0
extern oal_uint32 oam_log_set_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit);
#endif

extern oal_uint32 oam_log_set_feature_level(oal_uint8 uc_vap_id,
                                           oam_feature_enum_uint8   en_feature_id,
                                           oam_log_level_enum_uint8 en_log_level);
extern oal_uint32 oam_get_feature_id(oal_uint8 *puc_feature_name,
                                              oam_feature_enum_uint8 *puc_feature_id);
extern oal_uint32 oam_show_feature_list(oal_void);
extern oal_uint32 oam_log_set_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 en_log_level);

extern oal_uint32 oam_log_get_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 *pen_log_level);
#if 0
extern  oal_int32 OAL_PRINT_NLOGS(
        const oal_int8* pfunc_local_name,
        oal_uint16      us_file_no,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_uint8       uc_vap_id,
        oal_uint8       en_feature_id,
        oal_uint8       clog_level,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4);
#endif

extern oal_uint32  oam_log_print0(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print1(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print2(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print3(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_print4(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4);

extern oal_uint32  oam_log_console_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                const oal_int8                  *pc_fmt,
                ...);

extern oal_uint32 oam_exception_record(oal_uint8 uc_vap_id, oam_excp_type_enum_uint8 en_excp_id);

/*******************************************************************************
            EVENT模块对外接口
*******************************************************************************/
extern oal_uint32  oam_event_set_switch(
                       oal_uint8               uc_vap_id,
                       oal_switch_enum_uint8   en_switch_type);
extern oal_uint32  oam_event_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_event_report(
                                    oal_uint8                  *puc_user_macaddr,
                                    oal_uint8                   uc_vap_id,
                                    oam_module_id_enum_uint16   en_mod,
                                    oam_event_type_enum_uint16  en_event_type,
                                    oal_uint8                  *puc_string);
extern oal_uint32  oam_ota_report(oal_uint8   *puc_param_one_addr,
                               oal_uint16   us_param_one_len,
                               oal_uint8   *puc_param_two_addr,
                               oal_uint16   us_param_two_len,
                               oam_ota_type_enum_uint8  en_ota_type);
#if 0
extern oal_uint32  oam_ota_set_switch(
                            oal_uint8                   uc_vap_id,
                            oal_switch_enum_uint8       en_switch_type,
                            oam_ota_type_enum_uint8     en_ota_type);
#endif
extern oal_uint32  oam_ota_set_beacon_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_beacon_switch(oal_void);
extern oal_uint32  oam_ota_set_rx_dscr_switch(
                            oal_uint8                   uc_vap_id,
                            oam_sdt_print_beacon_rxdscr_type_enum_uint8 en_switch_type);
extern oal_switch_enum_uint8  oam_ota_get_rx_dscr_switch(oal_void);


extern oal_uint32  oam_report_eth_frame(oal_uint8               *puc_user_mac_addr,
                                       oal_uint8               *puc_eth_frame_hdr_addr,
                                       oal_uint16               us_eth_frame_len,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_frame_direction);
extern oal_uint32 oam_report_dscr(oal_uint8  *puc_user_macaddr,
                               oal_uint8  *puc_dscr_addr,
                               oal_uint16  us_dscr_len,
                               oam_ota_type_enum_uint8  en_ota_type);
extern oal_uint32  oam_report_beacon(
                                    oal_uint8     *puc_beacon_hdr_addr,
                                    oal_uint8      uc_beacon_hdr_len,
                                    oal_uint8     *puc_beacon_body_addr,
                                    oal_uint16     us_beacon_len,
                                    oam_ota_frame_direction_type_enum_uint8 en_beacon_direction);
extern oal_uint32  oam_report_80211_frame(
                        oal_uint8     *puc_user_macaddr,
                        oal_uint8     *puc_mac_hdr_addr,
                        oal_uint8      uc_mac_hdr_len,
                        oal_uint8     *puc_mac_body_addr,
                        oal_uint16     us_mac_frame_len,
                        oam_ota_frame_direction_type_enum_uint8  en_frame_direction);
#if 0
extern oal_switch_enum_uint8 oam_report_get_switch(oam_ota_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_80211_mcast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_ucast_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32  oam_report_80211_probe_get_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probereq_direction,
                                        oal_switch_enum_uint8                  *pen_frame_switch,
                                        oal_switch_enum_uint8                  *pen_cb_switch,
                                        oal_switch_enum_uint8                  *pen_dscr_switch);
extern oal_uint32  oam_report_80211_probe_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_probe_direction,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_eth_frame_get_switch(
                                 oal_uint16             us_user_idx,
                                 oam_ota_frame_direction_type_enum_uint8 en_eth_direction,
                                 oal_switch_enum_uint8  *pen_eth_switch);
extern oal_uint32  oam_report_netbuf_cb(oal_uint8  *puc_user_mac_addr,
                                       oal_uint8  *puc_netbuf_cb,
                                       oam_ota_type_enum_uint8 en_ota_type);
#if 0
extern oal_uint32  oam_report_timer_track(oal_uint32 ul_file_id,
                                        oal_uint32 ul_line_num,
                                        oam_timer_track_type_enum_uint8 en_type);
#endif
extern oal_uint32  oam_report_mpdu_num(oal_uint8  *puc_user_mac_addr,
                                        oam_report_mpdu_num_stru *pst_mpdu_num);
extern oal_uint32  oam_report_dft_params(oal_uint8  *puc_user_mac_addr,
                                        oal_uint8  *puc_param,
                                        oal_uint16      us_param_len,
                                        oam_ota_type_enum_uint8 en_type);
extern oal_uint32  oam_report_set_all_switch(oal_switch_enum_uint8 en_switch);
extern oal_uint32  oam_report_80211_ucast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_ucast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch,
                                        oal_uint16                              us_user_idx);
extern oal_uint32 oam_report_eth_frame_set_switch(oal_uint16               us_user_idx,
                                                   oal_switch_enum_uint8    en_switch,
                                       oam_ota_frame_direction_type_enum_uint8 en_eth_direction);
extern oal_uint32  oam_report_80211_mcast_set_switch(
                                        oam_ota_frame_direction_type_enum_uint8 en_mcast_direction,
                                        oam_user_track_frame_type_enum_uint8    en_frame_type,
                                        oal_switch_enum_uint8                   en_frame_switch,
                                        oal_switch_enum_uint8                   en_cb_switch,
                                        oal_switch_enum_uint8                   en_dscr_switch);
extern oal_uint32  oam_report_dhcp_arp_set_switch(oal_switch_enum_uint8 en_switch);
extern oal_switch_enum_uint8  oam_report_dhcp_arp_get_switch(oal_void);
extern oal_switch_enum_uint8  oam_report_data_get_global_switch(oam_ota_frame_direction_type_enum_uint8 en_direction);

/*******************************************************************************
            ALARM模块对外接口
*******************************************************************************/
extern oal_uint32  oam_alarm_set_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8  en_switch_type);
extern oal_uint32  oam_alarm_get_switch(
                       oal_uint8              uc_vap_id,
                       oal_switch_enum_uint8 *pen_switch_type);
extern oal_uint32  oam_alarm_report(
                       oal_uint8                   uc_vap_id,
                       oal_uint16                  us_file_no,
                       oal_uint32                  ul_file_line_no,
                       oam_module_id_enum_uint16   en_mod,
                       oam_alarm_type_enum_uint16  en_alarm_type);

/*******************************************************************************
            SDT模块对外接口
*******************************************************************************/
extern oal_void    oam_sdt_func_fook_register(oam_sdt_func_hook_stru *pfun_st_oam_sdt_hook);
extern oal_void    oam_sdt_func_fook_unregister(oal_void);
extern oal_void    oam_wal_func_fook_register(oam_wal_func_hook_stru *pfun_st_oam_wal_hook);
extern oal_void    oam_wal_func_fook_unregister(oal_void);

extern oal_uint32  oam_event_set_specific_type_switch(
                                oal_uint8                   uc_vap_id,
                                oal_switch_enum_uint8       en_switch_type,
                                oam_event_type_enum_uint16  en_event_type);

extern oal_uint32 oam_report_data2sdt(oal_netbuf_stru *pst_netbuf,
                                       oam_data_type_enum_uint8 en_type,
                                       oam_primid_type_enum_uint8 en_prim);
extern oal_netbuf_stru *oam_alloc_data2sdt(oal_uint16  us_data_len);

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_ext_if.h */
