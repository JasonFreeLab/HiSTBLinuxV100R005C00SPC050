
/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_board.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月17日
  最近修改   :
  功能描述   :board级别操作函数实现的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月17日
    作    者   : 侯寅
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
#include "wlan_spec.h"
#include "mac_board.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_BOARD_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* HOST CRX子表 */
frw_event_sub_table_item_stru g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_BUTT];

/* DMAC模块，HOST_DRX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_tx_host_drx[DMAC_TX_HOST_DRX_BUTT];

/* DMAC模块，WLAN_DTX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_tx_wlan_dtx[DMAC_TX_WLAN_DTX_BUTT];

//#ifndef _PRE_WLAN_PROFLING_MIPS
//#ifdef _PRE_WLAN_FEATURE_TCM
//#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
//#endif
//#endif
/* DMAC模块，WLAN_CTX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块,WLAN_DRX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_wlan_drx_event_sub_table[HAL_WLAN_DRX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块，ERROR_IRQ事件处理函数注册结构体定义 */
frw_event_sub_table_item_stru g_ast_dmac_high_prio_event_sub_table[HAL_EVENT_ERROR_IRQ_SUB_TYPE_BUTT];

/* DMAC模块,WLAN_CRX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_wlan_crx_event_sub_table[HAL_WLAN_CRX_EVENT_SUB_TYPE_BUTT];

/* DMAC模块，TX_COMP事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_dmac_tx_comp_event_sub_table[HAL_TX_COMP_SUB_TYPE_BUTT];

/* DMAC模块, TBTT事件处理函数表定义 */
frw_event_sub_table_item_stru g_ast_dmac_tbtt_event_sub_table[HAL_EVENT_TBTT_SUB_TYPE_BUTT];

/*DMAC模块, MISC事件处理函数表定义 */
frw_event_sub_table_item_stru g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT];

/* WLAN_DTX 事件子类型表 */
frw_event_sub_table_item_stru g_ast_hmac_wlan_dtx_event_sub_table[DMAC_TX_WLAN_DTX_BUTT];

/* HMAC模块 WLAN_DRX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 WLAN_CRX事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 TBTT事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_tbtt_event_sub_table[DMAC_TBTT_EVENT_SUB_TYPE_BUTT];

/* HMAC模块 发向HOST侧的配置事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_SYN_BUTT];

/* HMAC模块 MISC杂散事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_BUTT];

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
/* HMAC模块 IPC事件处理函数注册结构定义 */
frw_event_sub_table_item_stru g_ast_hmac_host_drx_event_sub_table[DMAC_TX_HOST_DRX_BUTT];
#endif


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
frw_event_sub_table_item_stru g_ast_hmac_hcc_rx_event_sub_table[DMAC_HCC_RX_EVENT_SUB_TYPE_BUTT];

//#ifndef _PRE_WLAN_PROFLING_MIPS
//#ifdef _PRE_WLAN_FEATURE_TCM
//#pragma arm section rodata, code, rwdata, zidata  // return to default placement
//#endif
//#endif

#endif
/*****************************************************************************
DFX公用全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
dfx_performance_log_switch_enum_uint8 g_auc_dfx_performance_log_switch[DFX_PERFORMANCE_LOG_BUTT] = {0};
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_event_fsm_table_register
 功能描述  : dmac模块事件处理表注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void  event_fsm_table_register(oal_void)
{
    /* Part1: 以下是Dmac收的事件*/

    /* 注册DMAC模块HOST_CRX事件 */
    frw_event_table_register(FRW_EVENT_TYPE_HOST_CRX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_dmac_host_crx_table);

    /* 注册DMAC模块HOST_DRX事件处理函数表 */
    frw_event_table_register(FRW_EVENT_TYPE_HOST_DRX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_dmac_tx_host_drx);

    /* 注册DMAC模块WLAN_DTX事件处理函数表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_DTX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_dmac_tx_wlan_dtx);

    /* 注册DMAC模块WLAN_CTX事件处理函数表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_CTX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_dmac_wlan_ctx_event_sub_table);

    /* 注册DMAC模块WLAN_DRX事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_DRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_wlan_drx_event_sub_table);

    /* 注册DMAC模块WLAN_CRX事件pipeline 0子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_CRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_wlan_crx_event_sub_table);

    /* 注册DMAC模块TX_COMP事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_TX_COMP, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_tx_comp_event_sub_table);

    /* 注册DMAC模块TBTT事件字表 */
    frw_event_table_register(FRW_EVENT_TYPE_TBTT, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_tbtt_event_sub_table);

    /* 注册DMAC模块ERR事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_HIGH_PRIO, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_high_prio_event_sub_table);

    /* 注册DMAC模块MISC事件字表 */
    frw_event_table_register(FRW_EVENT_TYPE_DMAC_MISC, FRW_EVENT_PIPELINE_STAGE_0, g_ast_dmac_misc_event_sub_table);

    /* Part2: 以下是Hmac收的事件*/

    /* 注册WLAN_DTX事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_DTX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_hmac_wlan_dtx_event_sub_table);

    /* 注册WLAN_DRX事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_DRX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_drx_event_sub_table);

    /* 注册HMAC模块WLAN_CRX事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_WLAN_CRX, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_crx_event_sub_table);

     /* 注册DMAC模块MISC事件字表 */
    frw_event_table_register(FRW_EVENT_TYPE_DMAC_MISC, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_misc_event_sub_table);

    /* 注册TBTT事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_TBTT, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_tbtt_event_sub_table);

    /* 注册统计结果查询事件子表 */
    frw_event_table_register(FRW_EVENT_TYPE_HOST_SDT_REG, FRW_EVENT_PIPELINE_STAGE_1, g_ast_hmac_wlan_ctx_event_sub_table);
}

/*****************************************************************************
 函 数 名  : dmac_event_fsm_unregister
 功能描述  : 去注册事件处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  event_fsm_unregister(oal_void)
{
    /* Part1: 以下是Dmac侧的事件*/

    /* 去注册DMAC模块HOST_CRX事件 */
    OAL_MEMZERO(g_ast_dmac_host_crx_table, OAL_SIZEOF(g_ast_dmac_host_crx_table));

    /* 去注册DMAC模块HOST_DRX事件处理函数表 */
    OAL_MEMZERO(g_ast_dmac_tx_host_drx, OAL_SIZEOF(g_ast_dmac_tx_host_drx));

    /* 去注册DMAC模块WLAN_DTX事件处理函数表 */
    OAL_MEMZERO(g_ast_dmac_tx_wlan_dtx, OAL_SIZEOF(g_ast_dmac_tx_wlan_dtx));

    /* 去注册DMAC模块WLAN_DRX事件子表 */
    OAL_MEMZERO(g_ast_dmac_wlan_drx_event_sub_table, OAL_SIZEOF(g_ast_dmac_wlan_drx_event_sub_table));

    /* 去注册DMAC模块WLAN_CRX事件子表 */
    OAL_MEMZERO(g_ast_dmac_wlan_crx_event_sub_table, OAL_SIZEOF(g_ast_dmac_wlan_crx_event_sub_table));

    /* 去注册DMAC模块TX_COMP事件子表 */
    OAL_MEMZERO(g_ast_dmac_tx_comp_event_sub_table, OAL_SIZEOF(g_ast_dmac_tx_comp_event_sub_table));

    /* 去注册DMAC模块TBTT事件字表 */
    OAL_MEMZERO(g_ast_dmac_tbtt_event_sub_table, OAL_SIZEOF(g_ast_dmac_tbtt_event_sub_table));

    /* 去注册DMAC模块MAC_ERROR事件子表 */
    OAL_MEMZERO(g_ast_dmac_high_prio_event_sub_table, OAL_SIZEOF(g_ast_dmac_high_prio_event_sub_table));

    /* 去注册DMAC模块MAC_ERROR事件子表 */
    OAL_MEMZERO(g_ast_dmac_misc_event_sub_table, OAL_SIZEOF(g_ast_dmac_misc_event_sub_table));

    /* Part2: 以下是Hmac侧的事件*/
    OAL_MEMZERO(g_ast_hmac_wlan_dtx_event_sub_table, OAL_SIZEOF(g_ast_hmac_wlan_dtx_event_sub_table));

    OAL_MEMZERO(g_ast_hmac_wlan_drx_event_sub_table, OAL_SIZEOF(g_ast_hmac_wlan_drx_event_sub_table));

    OAL_MEMZERO(g_ast_hmac_wlan_crx_event_sub_table, OAL_SIZEOF(g_ast_hmac_wlan_crx_event_sub_table));

    OAL_MEMZERO(g_ast_hmac_tbtt_event_sub_table, OAL_SIZEOF(g_ast_hmac_tbtt_event_sub_table));

    OAL_MEMZERO(g_ast_hmac_wlan_ctx_event_sub_table, OAL_SIZEOF(g_ast_hmac_wlan_ctx_event_sub_table));

    OAL_MEMZERO(g_ast_hmac_wlan_misc_event_sub_table, OAL_SIZEOF(g_ast_hmac_wlan_misc_event_sub_table));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    OAL_MEMZERO(g_ast_hmac_hcc_rx_event_sub_table, OAL_SIZEOF(g_ast_hmac_hcc_rx_event_sub_table));
#endif
}
/*lint -e19*/
oal_module_symbol(g_ast_dmac_host_crx_table);
oal_module_symbol(g_ast_dmac_tx_host_drx);
oal_module_symbol(g_ast_dmac_tx_wlan_dtx);
oal_module_symbol(g_ast_dmac_wlan_ctx_event_sub_table);
oal_module_symbol(g_ast_dmac_wlan_drx_event_sub_table);
oal_module_symbol(g_ast_dmac_high_prio_event_sub_table);
oal_module_symbol(g_ast_dmac_wlan_crx_event_sub_table);
oal_module_symbol(g_ast_dmac_tx_comp_event_sub_table);
oal_module_symbol(g_ast_dmac_tbtt_event_sub_table);
oal_module_symbol(g_ast_dmac_misc_event_sub_table);

oal_module_symbol(g_ast_hmac_wlan_dtx_event_sub_table);
oal_module_symbol(g_ast_hmac_wlan_drx_event_sub_table);
oal_module_symbol(g_ast_hmac_wlan_crx_event_sub_table);
oal_module_symbol(g_ast_hmac_tbtt_event_sub_table);
oal_module_symbol(g_ast_hmac_wlan_ctx_event_sub_table);
oal_module_symbol(g_ast_hmac_wlan_misc_event_sub_table);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(g_ast_hmac_hcc_rx_event_sub_table);
#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(g_ast_hmac_host_drx_event_sub_table);
#endif
oal_module_symbol(event_fsm_table_register);
oal_module_symbol(event_fsm_unregister);
/*lint +e19*/
/*****************************************************************************
DFX公用函数实现
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 函 数 名  : dfx_get_performance_log_switch_enable
 功能描述  : 获取性能维测开关值
 输入参数  : dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dfx_get_performance_log_switch_enable(dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type)
{
    return g_auc_dfx_performance_log_switch[uc_performance_log_switch_type];
}
/*****************************************************************************
 函 数 名  : dfx_set_performance_log_switch_enable
 功能描述  : 设置性能维测开关值
 输入参数  : dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type
             oal_uint8 uc_value
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dfx_set_performance_log_switch_enable(dfx_performance_log_switch_enum_uint8 uc_performance_log_switch_type, oal_uint8 uc_value)
{
    if(DFX_PERFORMANCE_LOG_BUTT <= uc_performance_log_switch_type)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "dfx_set_performance_log_switch_enable::log_switch type:%d.", uc_performance_log_switch_type);
        return;
    }
    g_auc_dfx_performance_log_switch[uc_performance_log_switch_type] = uc_value;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


