/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_trace.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年12月18日
  最近修改   :
  功能描述   : (1)用于测试流程或者函数运行时间的接口函数的源文件
               (2)trace相关操作的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_main.h"
#include "oam_trace.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_TRACE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#ifdef _PRE_PROFILING_MODE
/*****************************************************************************
    2.1 profiling全局变量定义
*****************************************************************************/
/* 保存tx profiling测试的所有数据 */
oam_profiling_tx_statistic_stru g_oam_profiling_statistic_tx;

/* 保存rx profiling测试的所有数据 */
oam_profiling_rx_statistic_stru g_oam_profiling_statistic_rx;

/* 保存tx profiling测试的所有数据 */
oam_profiling_alg_statistic_stru g_oam_profiling_statistic_alg;

/* 保存芯片start time测试数据 */
oam_profiling_starttime_statistic_stru g_oam_profiling_statistic_starttime;

/* 保存芯片信道切换测试数据 */
oam_profiling_chswitch_statistic_stru g_oam_profiling_statistic_chswitch;

/* 用于profiling test的全局开关 */
oam_profiling_statistic_debug_stru g_oam_profiling_statistic_debug;


#endif

/*****************************************************************************
    2.2 trace全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#ifdef _PRE_PROFILING_MODE
/*****************************************************************************
 函 数 名  : oam_profiling_switch_test_process
 功能描述  : proc指令调用的入口函数
 输入参数  : (1)配置类型
             (2)配置值
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_profiling_switch_test_process(oal_uint8  uc_config_type, oal_uint8 uc_config_value)
{
    switch (uc_config_type)
    {
        case OAM_PROFILING_SWITCH_DEBUG_CONFIG:
        {
            //oal_spin_lock(&g_oam_profiling_statistic_ping_data.st_spin_lock);

            if (OAM_PROFILING_STATISTIC_TX_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = OAL_FALSE;
            }

            if (OAM_PROFILING_STATISTIC_RX_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = OAL_FALSE;
            }
            if (OAM_PROFILING_STATISTIC_ALG_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = OAL_FALSE;
            }
        }

        break;

        default:

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : oam_profiling_compute_time_offset
 功能描述  : 计算两个时间之间的偏移差
 输入参数  : (1)时间值一
             (2)时间值二
 输出参数  : 两次时间的时间差
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_compute_time_offset(
                oal_time_us_stru    st_time_first,
                oal_time_us_stru    st_time_second,
                oal_time_us_stru   *pst_time_offset)
{
    /* 未跨越1sec */
    if (st_time_first.i_sec == st_time_second.i_sec)
    {
        pst_time_offset->i_sec     = 0;
        pst_time_offset->i_usec    = st_time_second.i_usec - st_time_first.i_usec;
    }
    /* 跨越1sec */
    else
    {
        pst_time_offset->i_sec     = 0;
        pst_time_offset->i_usec    = 1000 * (st_time_second.i_sec - st_time_first.i_sec) - st_time_first.i_usec + st_time_second.i_usec;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_rx_init
 功能描述  : 初始化接收流程的全局测试变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_rx_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_RX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* 注意，netbuf的对应的SKB_ID，需要从0开始，并且 */
        g_oam_profiling_statistic_rx.aus_rx_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_rx.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_rx.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_rx.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_RX_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_rx.ast_rx_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_rx.aus_rx_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_rx_save_data
 功能描述  : 接收时根据skb id将时间差,基准时间,经过函数次数保存到skb_run_time_offset
 输入参数  : 函数索引
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index)
{
    /* 开关判断 */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable)
    {
        return;
    }*/

    if (0 == g_oam_profiling_statistic_rx.ast_rx_func_stand_time[g_oam_profiling_statistic_rx.uc_skb_id_idx][en_func_index])
    {
        g_oam_profiling_statistic_rx.ast_rx_func_stand_time[g_oam_profiling_statistic_rx.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }
}

/*****************************************************************************
 函 数 名  : oam_profiling_rx_show_offset
 功能描述  : 打印接收函数运行时间和运行次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_rx_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_RX_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("RX time show:\n");

        /* 打印报文入tid队列的时间 */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_RX_COMP_IRQ_START; ul_func_idx <= OAM_PROFILING_FUNC_RX_DMAC_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_RX_COMP_IRQ_START)
            {
                ul_time_offset = g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_RX_COMP_IRQ_START] -  g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_RX_DMAC_END];
        OAL_IO_PRINT("\nRX total time is: %d (10ns)   \n\n", ul_time_offset);

    }

    /* 清零 */
    oam_profiling_rx_init();

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_tx_init
 功能描述  : 初始化发送流程的全局测试变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_tx_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_TX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* 注意，netbuf的对应的SKB_ID，需要从0开始，并且 */
        g_oam_profiling_statistic_tx.aus_tx_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_tx.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_tx.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_tx.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_TX_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_tx.ast_tx_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_tx.aus_tx_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_tx_save_data
 功能描述  : 发送时根据skb id将时间差,基准时间,经过函数次数保存到skb_run_time_offset
 输入参数  : (1)指向要操作的netbuf
             (2)函数索引
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oam_profiling_tx_save_data(
                oal_void                    *pst_netbuf,
                oam_profiling_tx_func_enum_uint8    en_func_index)
{
    /* 开关判断 */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable)
    {
        return;
    }*/

    /*原值等于0才计数， 不会去覆盖已经记录好的值*/
    if (0 == g_oam_profiling_statistic_tx.ast_tx_func_stand_time[g_oam_profiling_statistic_tx.uc_skb_id_idx][en_func_index])
    {
       g_oam_profiling_statistic_tx.ast_tx_func_stand_time[g_oam_profiling_statistic_tx.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }

    return;
}

/*****************************************************************************
 函 数 名  : oam_profiling_tx_show_offset
 功能描述  : 打印发送函数运行时间和运行次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_tx_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_TX_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("TX time show:\n");
        /* 打印报文入tid队列的时间 */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_CONFIG_XMIT_START; ul_func_idx <= OAM_PROFILING_FUNC_CONFIG_XMIT_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_CONFIG_XMIT_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_CONFIG_XMIT_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_CONFIG_XMIT_END];
        OAL_IO_PRINT("\ntid enqueue total time is: %d (10ns)   \n\n", ul_time_offset);

        /* 打印ampdu调度并发送队列的时间 */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_SCHEDULE_START; ul_func_idx <= OAM_PROFILING_FUNC_SCHEDULE_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_SCHEDULE_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }
        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_SCHEDULE_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_SCHEDULE_END];
        OAL_IO_PRINT("\nampdu schedule total time is: %d (10ns)     \n\n", ul_time_offset);


        /* 打印ampdu发送完成中断下半部处理时间 */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_TX_COMP_IRQ_START; ul_func_idx <= OAM_PROFILING_FUNC_TX_COMP_DMAC_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_TX_COMP_IRQ_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }
        }
        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_TX_COMP_IRQ_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_TX_COMP_DMAC_END];
        OAL_IO_PRINT("\nampdu tx complete total time is: %d (10ns)     \n\n", ul_time_offset);

    }

    ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_CONFIG_XMIT_START]
		             - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_CONFIG_XMIT_END]
                     + g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_SCHEDULE_START]
					 - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_SCHEDULE_END]
                     + g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_TX_COMP_IRQ_START]
					 - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_TX_COMP_DMAC_END];


    OAL_IO_PRINT("TX total time is: %d (10ns)     \n", ul_time_offset);

    /* 清零 */
    oam_profiling_tx_init();

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_profiling_alg_init
 功能描述  : 初始化发送流程的全局测试变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月29日
    作    者   :  291193
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_alg_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_ALG_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* 注意，netbuf的对应的SKB_ID，需要从0开始，并且 */
        g_oam_profiling_statistic_alg.aus_alg_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_alg.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_alg.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_alg.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_ALG_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_alg.ast_alg_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_alg.aus_alg_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_alg_save_data
 功能描述  : 发送时根据skb id将时间差,基准时间,经过函数次数保存到skb_run_time_offset
 输入参数  : (1)指向要操作的netbuf
             (2)函数索引
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月29日
    作    者   :  291193
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8    en_func_index)
{
    /* 开关判断 */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable)
    {
        return;
    }*/

    /*原值等于0才计数， 不会去覆盖已经记录好的值*/
    if (0 == g_oam_profiling_statistic_alg.ast_alg_func_stand_time[g_oam_profiling_statistic_alg.uc_skb_id_idx][en_func_index])
    {
       g_oam_profiling_statistic_alg.ast_alg_func_stand_time[g_oam_profiling_statistic_alg.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }

    return;
}

/*****************************************************************************
 函 数 名  : oam_profiling_alg_show_offset
 功能描述  : 打印发送函数运行时间和运行次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月29日
    作    者   :  291193
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_alg_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_ALG_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("ALG time show:\n");
        /* 打印XX的时间 */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_ALG_START; ul_func_idx <= OAM_PROFILING_ALG_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_ALG_START)
            {
                ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][OAM_PROFILING_ALG_START] -  g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][OAM_PROFILING_ALG_END];
        OAL_IO_PRINT("\nALG stage 1 total time is: %d (10ns)   \n\n", ul_time_offset);



    }

    ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[0][OAM_PROFILING_ALG_START]
		             - g_oam_profiling_statistic_alg.ast_alg_func_stand_time[0][OAM_PROFILING_ALG_END];



    OAL_IO_PRINT("ALG total time is: %d (10ns)     \n", ul_time_offset);

    /* 清零 */
    oam_profiling_alg_init();

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_statistic_init
 功能描述  : 初始化芯片启动时间统计全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_statistic_init(oal_void)
{
    OAL_MEMZERO(&g_oam_profiling_statistic_starttime, OAL_SIZEOF(g_oam_profiling_statistic_starttime));

    OAL_MEMZERO(&g_oam_profiling_statistic_chswitch, OAL_SIZEOF(g_oam_profiling_statistic_chswitch));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_starttime_save_timestamp
 功能描述  : 芯片启动流程打时间戳函数
 输入参数  : en_func_idx: 打时间戳的索引号
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_profiling_starttime_save_timestamp(oam_profiling_starttime_func_enum_uint8 en_func_idx)
{
    g_oam_profiling_statistic_starttime.aul_timestamp[en_func_idx] = oal_5115timer_get_10ns();

    return;
}

/*****************************************************************************
 函 数 名  : oam_profiling_starttime_show_offset
 功能描述  : 打印芯片各模块启动时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_profiling_starttime_show_offset(oal_void)
{
    oal_uint32 ul_idx;

    /* 打印所有记录的时间点 */
    OAL_IO_PRINT("Print all chip start timestamps: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_STARTTIME_FUNC_BUTT; ul_idx++)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx]);
    }

    OAL_IO_PRINT("Print chip start timestamp offset: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_STARTTIME_FUNC_BUTT; ul_idx += 2)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx] - g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx + 1]);
    }

    return;
}


/*****************************************************************************
 函 数 名  : oam_profiling_chswitch_save_timestamp
 功能描述  : 芯片启动流程打时间戳函数
 输入参数  : en_func_idx: 打时间戳的索引号
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_profiling_chswitch_save_timestamp(oam_profiling_chswitch_func_enum_uint8 en_func_idx)
{
    g_oam_profiling_statistic_chswitch.aul_timestamp[en_func_idx] = oal_5115timer_get_10ns();

    return;
}

/*****************************************************************************
 函 数 名  : oam_profiling_chswitch_show_offset
 功能描述  : 打印信道切换时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oam_profiling_chswitch_show_offset(oal_void)
{
    oal_uint32 ul_idx;

    /* 打印所有记录的时间点 */
    OAL_IO_PRINT("Print all chswitch timestamps: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_CHSWITCH_FUNC_BUTT; ul_idx++)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx]);
    }

    OAL_IO_PRINT("Print chswitch timestamp offset: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_CHSWITCH_FUNC_BUTT; ul_idx += 2)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx] - g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx + 1]);
    }

    return;
}


/*****************************************************************************
 函 数 名  : oam_profiling_set_switch
 功能描述  : 设置profiling的控制开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_set_switch(oam_profiling_enum_uint8 en_profiling_type, oam_profiling_swith_enum_uint8 en_profiling_switch)
{

    if ((en_profiling_switch >= OAL_SWITCH_BUTT) || (en_profiling_type >= OAM_PROFILING_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    switch (en_profiling_type)
    {
        /* 接收流程 */
        case OAM_PROFILING_RX:
            g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = en_profiling_switch;

            break;

        /* 发送流程 */
        case OAM_PROFILING_TX:
            g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = en_profiling_switch;

            break;

        /* ALG流程 */
        case OAM_PROFILING_ALG:
            g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = en_profiling_switch;

            break;

        default:

            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_profiling_init
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_profiling_init(oal_void)
{
    /* 初始化定时器 */
    oal_5115timer_init();

    /* 初始化接收流程profiling结构 */
    oam_profiling_rx_init();

    /* 初始化发送流程profiling结构 */
    oam_profiling_tx_init();

     /* 初始化发送流程profiling结构 */
    oam_profiling_alg_init();

    /* 初始化芯片启动profiling结构 */
    oam_profiling_statistic_init();

    /* profiling初始化:默认不打开 */
    oam_profiling_set_switch(OAM_PROFILING_RX, OAM_PROFILING_SWITCH_OFF);
    oam_profiling_set_switch(OAM_PROFILING_TX, OAM_PROFILING_SWITCH_OFF);
    oam_profiling_set_switch(OAM_PROFILING_ALG, OAM_PROFILING_SWITCH_OFF);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_PROFILING_MODE
oal_module_symbol(g_oam_profiling_statistic_tx);
oal_module_symbol(g_oam_profiling_statistic_rx);
oal_module_symbol(oam_profiling_set_switch);

oal_module_symbol(oam_profiling_rx_save_data);
oal_module_symbol(oam_profiling_rx_show_offset);
oal_module_symbol(oam_profiling_tx_save_data);
oal_module_symbol(oam_profiling_tx_show_offset);
oal_module_symbol(oam_profiling_alg_save_data);
oal_module_symbol(oam_profiling_alg_show_offset);


oal_module_symbol(oam_profiling_starttime_save_timestamp);
oal_module_symbol(oam_profiling_starttime_show_offset);

oal_module_symbol(oam_profiling_chswitch_save_timestamp);
oal_module_symbol(oam_profiling_chswitch_show_offset);
#endif

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

