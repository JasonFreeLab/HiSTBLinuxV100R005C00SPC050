/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : frw_main.c
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : FRW模块初始化与卸载
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
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
#include "frw_main.h"
#include "frw_task.h"
#include "frw_event_main.h"
#include "frw_event_deploy.h"
#include "frw_ext_if.h"
#include "frw_timer.h"

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#include "oal_hcc_host_if.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_MAIN_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
frw_init_enum_uint16 g_en_wlan_driver_init_state = FRW_INIT_STATE_BUTT;
OAL_STATIC frw_event_sub_table_item_stru g_ast_frw_timeout_event_sub_table[FRW_TIMEOUT_SUB_TYPE_BUTT];

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : frw_event_fsm_register
 功能描述  : frw 事件注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  frw_event_fsm_register(oal_void)
{
    g_ast_frw_timeout_event_sub_table[FRW_TIMEOUT_TIMER_EVENT].p_func = frw_timer_timeout_proc;
    frw_event_table_register(FRW_EVENT_TYPE_TIMEOUT, FRW_EVENT_PIPELINE_STAGE_0, g_ast_frw_timeout_event_sub_table);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_main_init
 功能描述  : FRW模块初始化总入口，包含FRW模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  frw_main_init(oal_void)
{
    oal_uint32          ul_ret;

    frw_set_init_state(FRW_INIT_STATE_START);

    /* 为了解各模块的启动时间，增加时间戳打印 TBD */

    /* 事件管理模块初始化 */
    ul_ret = frw_event_init();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_main_init:: frw_event_init return err code: %d}", ul_ret);
        return -OAL_EFAIL;
    }

    frw_task_init(); 

#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    /* 事件核间部署模块初始化 */
    ul_ret = frw_event_deploy_init();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_main_init:: frw_event_deploy_init return err code: %d}", ul_ret);
        return -OAL_EFAIL;
    }
#endif

    frw_timer_init(FRW_TIMER_DEFAULT_TIME, frw_timer_timeout_proc_event, 0);

    frw_event_fsm_register();


    /* 启动成功后，输出打印 设置状态始终放最后 */
    frw_set_init_state(FRW_INIT_STATE_FRW_SUCC);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : frw_main_exit
 功能描述  : FRW模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块卸载返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_main_exit(oal_void)
{
    /* HCC卸载接口 TBD */

    /* 卸载定时器 */
    frw_timer_exit();

    /* 卸载事件管理模块 */
    frw_event_exit();

    frw_task_exit();

#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    /* 事件核间部署模块卸载 */
    frw_event_deploy_exit();
#endif

    /* 卸载成功后在置状态位 */
    frw_set_init_state(FRW_INIT_STATE_START);

    /* 卸载成功后，输出打印 */
    OAL_IO_PRINT("frw exit ok!\n");

    return ;
}

/*****************************************************************************
 函 数 名  : frw_set_init_state
 功能描述  : 设置初始化状态
 输入参数  : 初始化状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  frw_set_init_state(frw_init_enum_uint16 en_init_state)
{
    if (en_init_state >= FRW_INIT_STATE_BUTT)
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_set_init_state:: en_init_state >= FRW_INIT_STATE_BUTT: %d}", en_init_state);
        return;
    }

    g_en_wlan_driver_init_state = en_init_state;

    return ;
}

/*****************************************************************************
 函 数 名  : frw_get_init_state
 功能描述  : 获取初始化状态
 输入参数  : 初始化状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
frw_init_enum_uint16  frw_get_init_state(oal_void)
{
    return g_en_wlan_driver_init_state;
}


/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(frw_main_init);
oal_module_exit(frw_main_exit);

#endif

oal_module_symbol(frw_main_init);
oal_module_symbol(frw_main_exit);

oal_module_symbol(frw_set_init_state);
oal_module_symbol(frw_get_init_state);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

