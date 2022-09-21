/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_log.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月10日
  最近修改   :
  功能描述   : OAM LOG功能。
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月10日
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
#include "oam_log.h"
#ifdef CONFIG_PRINTK
#include <linux/kernel.h>
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_LOG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
    oam_tx_complete_stat_stru   g_ast_tx_complete_stat[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef CONFIG_PRINTK
static char* g_loglevel_string[OAM_LOG_LEVEL_BUTT] ;
#endif
#endif


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : OAL_PRINT2KERNEL
 功能描述  : 把打印信息保存一份到内核中
 输入参数  : o
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/1/23
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 OAL_PRINT2KERNEL(
        oal_uint8                uc_vap_id,
        oal_uint16      us_file_no,
        oal_uint8       clog_level,
        const oal_int8* pfunc_local_name,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4
        )
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef CONFIG_PRINTK
    oal_int32 l_ret;
    oal_int8   pc_buf[OAM_LOG_PRINT_DATA_LENGTH];

    pc_buf[0] = '\0';

    if(OAM_LOG_LEVEL_ERROR == clog_level)
    {
        DECLARE_DFT_TRACE_KEY_INFO("oam error log", OAL_DFT_TRACE_OTHER);
    }

    l_ret = snprintf(pc_buf,OAM_LOG_PRINT_DATA_LENGTH, KERN_DEBUG"[%s][vap:%d]%s [F:%d][L:%d]\n",
        g_loglevel_string[clog_level],
        uc_vap_id,
        fmt,
        us_file_no,
        us_line_no);
    if (l_ret < 0)

    {
        OAM_IO_PRINTK("l_ret < 0 \r\n");
        return l_ret;
    }

    printk(pc_buf, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, (oal_int32)p4);
#endif
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : OAL_PRINT_NLOGS
 功能描述  : 把打印信息保存一份到内核中
 输入参数  : o
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015/1/23
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 OAL_PRINT_NLOGS(
        const oal_int8* pfunc_local_name,
        oal_uint16      us_file_no,
        oal_uint16      us_line_no,
        void*           pfunc_addr,
        oal_uint8       uc_vap_id,
        oal_uint8       en_feature_id,
        oal_uint8       clog_level,
        oal_int8*       fmt,
        oal_uint p1, oal_uint p2, oal_uint p3, oal_uint p4)
{
	if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, clog_level))
        OAL_PRINT2KERNEL(uc_vap_id, us_file_no,clog_level,pfunc_local_name, us_line_no, pfunc_addr, fmt, p1, p2, p3, p4);
    oam_log_print4(uc_vap_id, en_feature_id, us_file_no, us_line_no, clog_level, fmt, (oal_int32)p1, (oal_int32)p2, (oal_int32)p3, (oal_int32)p4);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_log_set_global_switch
 功能描述  : 设置日志全局开关状态
 输入参数  : oal_switch_enum_uint8 en_log_switch
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_global_switch(oal_switch_enum_uint8 en_log_switch)
{
    if (OAL_UNLIKELY(en_log_switch >= OAL_SWITCH_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_switch[%d]. \r\n", en_log_switch);
        return OAL_FAIL;
    }

    g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch = en_log_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_ratelimit_switch
 功能描述  : 设置日志的流控开关
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oal_switch_enum_uint8 en_log_switch
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  oal_uint32 oam_log_set_ratelimit_switch(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oal_switch_enum_uint8 en_log_switch)
{
    if (OAL_UNLIKELY(en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (en_log_switch >= OAL_SWITCH_BUTT)
    {
        OAM_IO_PRINTK("invalid en_log_switch[%d]. \r\n", en_log_switch);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type].en_ratelimit_switch = en_log_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_ratelimit_switch
 功能描述  : 获取日志的流控开关
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oal_switch_enum_uint8 *pen_log_switch
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_get_ratelimit_switch(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oal_switch_enum_uint8 *pen_log_switch)
{
    if (OAL_UNLIKELY(en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_switch = g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type].en_ratelimit_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_printk_ratelimit_intervel
 功能描述  : 设置printk流控时间间隔，以秒为单位
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oal_uint32 ul_interval
 输出参数  : 无
 返 回 值  : OAL_STATIC  oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  oal_uint32 oam_log_set_ratelimit_intervel(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oal_uint32 ul_interval)
{
    if (OAL_UNLIKELY(en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if ((ul_interval < OAM_RATELIMIT_MIN_INTERVAL)
        || (ul_interval > OAM_RATELIMIT_MAX_INTERVAL))
    {
        OAM_IO_PRINTK("ul_interval[%d] must be range[%d~%d]. \r\n",
                       ul_interval, OAM_RATELIMIT_MIN_INTERVAL, OAM_RATELIMIT_MAX_INTERVAL);

        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type].ul_interval = ul_interval * OAL_TIME_HZ;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_printk_ratelimit_burst
 功能描述  : 设置printk流控的阈值
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oal_uint32 ul_burst
 输出参数  : 无
 返 回 值  : OAL_STATIC  oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  oal_uint32 oam_log_set_ratelimit_burst(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oal_uint32 ul_burst)
{
    if (OAL_UNLIKELY(en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if ((ul_burst < OAM_RATELIMIT_MIN_BURST)
        || (ul_burst > OAM_RATELIMIT_MAX_BURST))
    {
        OAM_IO_PRINTK("ul_burst[%d] must be range[%d~%d]. \r\n",
                       ul_burst, OAM_RATELIMIT_MIN_BURST, OAM_RATELIMIT_MAX_BURST);

        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type].ul_burst = ul_burst;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_ratelimit_param
 功能描述  : 设置日志流控参数
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oam_ratelimit_stru *pst_printk_ratelimit
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit)
{
    oal_uint32          ul_ret = OAL_SUCC;

    if (en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT)
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_printk_ratelimit))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = oam_log_set_ratelimit_switch(en_ratelimit_type, pst_printk_ratelimit->en_ratelimit_switch);

    ul_ret += oam_log_set_ratelimit_intervel(en_ratelimit_type, pst_printk_ratelimit->ul_interval);

    ul_ret += oam_log_set_ratelimit_burst(en_ratelimit_type, pst_printk_ratelimit->ul_burst);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_get_ratelimit_param
 功能描述  : 获取日志流控参数
 输入参数  : oam_ratelimit_type_enum_uint8  en_ratelimit_type
             oam_ratelimit_stru *pst_printk_ratelimit
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_get_ratelimit_param(
                oam_ratelimit_type_enum_uint8  en_ratelimit_type,
                oam_ratelimit_stru *pst_printk_ratelimit)
{
    oal_uint32          ul_ret = OAL_SUCC;

    if (en_ratelimit_type >= OAM_RATELIMIT_TYPE_BUTT)
    {
        OAM_IO_PRINTK("invalid en_ratelimit_type[%d]. \r\n", en_ratelimit_type);
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_printk_ratelimit))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_printk_ratelimit, &g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type],
                OAL_SIZEOF(oam_ratelimit_stru));

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_printk_ratelimit
 功能描述  : 检测相应的流控类型是否满足输出条件
             在ul_interval时间范围内只允许ul_burst条记录输出；
             在ul_interval内，若输出日志已经超过设定值，不再输出；
             等待ul_interval之后再重新输出，ul_begin重新赋当前值
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : OAL_STATIC    oam_ratelimit_output_enum_uint8
             RATELIMIT_NOT_OUTPUT  -- 不输出  RATELIMIT_OUTPUT  -- 输出
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oam_ratelimit_output_enum_uint8 oam_log_ratelimit(oam_ratelimit_type_enum_uint8 en_ratelimit_type )
{
    oal_uint                            ui_flags;
    oam_ratelimit_stru      	       *pst_ratelimit;
    oam_ratelimit_output_enum_uint8     en_ret = OAM_RATELIMIT_OUTPUT;

    pst_ratelimit = &g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_ratelimit_type];

    //判断流控开关状态
    if (OAL_SWITCH_OFF == pst_ratelimit->en_ratelimit_switch)
    {
        return OAM_RATELIMIT_OUTPUT;
    }

    //若间隔为0 表明不流控
    if (0 == pst_ratelimit->ul_interval)
    {
        return OAM_RATELIMIT_OUTPUT;
    }

    oal_spin_lock_irq_save(&pst_ratelimit->spin_lock, &ui_flags);

    //记录第一条日志的当前时间
    if (0 == pst_ratelimit->ul_begin)
    {
		pst_ratelimit->ul_begin = OAL_TIME_JIFFY;
    }

    //起时时间+间隔在当前时间之前，表明间隔时间已经超时，需要重新计数了
    if (oal_time_is_before(pst_ratelimit->ul_begin + pst_ratelimit->ul_interval))
    {
		pst_ratelimit->ul_begin   = 0;
		pst_ratelimit->ul_printed = 0;
		pst_ratelimit->ul_missed  = 0;
    }

    /* 若未超时，判断当前时间周期内已输出日志计数是否达到限制输出数 */
    /* 未达到限制的输出日志个数，继续输出 */
    if (pst_ratelimit->ul_burst && (pst_ratelimit->ul_burst > pst_ratelimit->ul_printed))
    {
		pst_ratelimit->ul_printed++;
		en_ret = OAM_RATELIMIT_OUTPUT;
    }
    /* 达到限制的输出日志个数，不输出；待下一个周期再输出 */
    else
    {
		pst_ratelimit->ul_missed++;
		en_ret = OAM_RATELIMIT_NOT_OUTPUT;
    }

    oal_spin_unlock_irq_restore(&pst_ratelimit->spin_lock, &ui_flags);

    return en_ret;
}


/*****************************************************************************
 函 数 名  : oam_log_set_vap_switch
 功能描述  : 设置VAP日志开关
 输入参数  : oal_uint8 uc_vap_id
             oam_log_switch_enum_uint8 en_log_switch
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_vap_switch(oal_uint8 uc_vap_id,
                                         oal_switch_enum_uint8 en_log_switch)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d]. \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_log_switch >= OAL_SWITCH_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_switch[%d]. \r\n", en_log_switch);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id] = en_log_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_vap_level
 功能描述  : 设置VAP下所有特性日志级别为en_log_level
             不允许设置成OAM_LOG_LEVEL_INFO级别,在命令行里进行限制，本函数不处理
 输入参数  : oal_uint8 uc_vap_id
             oam_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 en_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 en_log_level)
{
    oam_feature_enum_uint8       en_feature_idx;

    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid vap id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 设置当前VAP的日志级别 */
    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id] = en_log_level;

    /* 同时设置当前VAP下所有特性日志级别 */
    for (en_feature_idx = 0; en_feature_idx < OAM_SOFTWARE_FEATURE_BUTT; en_feature_idx++)
    {
        oam_log_set_feature_level(uc_vap_id, en_feature_idx, en_log_level);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_vap_level
 功能描述  : 获取VAP的日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_log_level_enum_uint8 *pen_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_get_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 *pen_log_level)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid vap id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_level))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_level = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_feature_level
 功能描述  : 设置VAP下特性日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 en_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_feature_level(oal_uint8 uc_vap_id,
                                           oam_feature_enum_uint8 en_feature_id,
                                           oam_log_level_enum_uint8 en_log_level)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id.[%d] \r\n", uc_vap_id);
        return  OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id.[%d] \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY((en_log_level >= OAM_LOG_LEVEL_BUTT) || (en_log_level < OAM_LOG_LEVEL_ERROR)))
    {
        OAM_IO_PRINTK("invalid en_log_level.[%d] \r\n", en_log_level);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id] = en_log_level;
    //OAL_IO_PRINT("oam_log_set_feature_level:: uc_vap_id=%u, en_feature_id=%u, en_log_level=%u\r\n", uc_vap_id, en_feature_id, en_log_level);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_get_feature_id
 功能描述  : 由特性名称获取特性ID
 输入参数  : oal_uint8 *puc_feature_name
             oam_feature_enum_uint8 *puc_feature_id
 输出参数  : puc_feature_id  对应特性名称的ID号
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_get_feature_id(oal_uint8 *puc_feature_name,
                                   oam_feature_enum_uint8 *puc_feature_id)
{
    oam_feature_enum_uint8   en_feature_idx;

    if (OAL_UNLIKELY((OAL_PTR_NULL == puc_feature_name) || (OAL_PTR_NULL == puc_feature_id)))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (en_feature_idx = 0; en_feature_idx < OAM_SOFTWARE_FEATURE_BUTT; en_feature_idx++)
    {
        if (0 == oal_strcmp((oal_int8 *)gst_oam_feature_list[en_feature_idx].auc_feature_name_abbr, (oal_int8 *)puc_feature_name))
        {
            *puc_feature_id = en_feature_idx;
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : oam_get_feature_name
 功能描述  : 获取指定特性ID的特性名称
 输入参数  : oam_feature_enum_uint8     en_feature_id
             oal_uint8    *puc_feature_name
             oal_uint8     uc_size
 输出参数  : puc_feature_name
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_get_feature_name( oam_feature_enum_uint8     en_feature_id,
                                      oal_uint8    *puc_feature_name,
                                      oal_uint8     uc_size)
{
    oal_uint8       uc_feature_len;

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("en_feature_id override. %d. \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_feature_name))
    {
        OAM_IO_PRINTK("puc_feature_name is NULL. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_feature_len = (oal_uint8)OAL_STRLEN((oal_int8*)gst_oam_feature_list[en_feature_id].auc_feature_name_abbr);
    uc_size = (uc_size > uc_feature_len) ? uc_feature_len : uc_size;

    oal_memcopy(puc_feature_name, gst_oam_feature_list[en_feature_id].auc_feature_name_abbr, uc_size);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_show_feature_list
 功能描述  : 显示特性缩写与全称的帮助信息
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日,星期五
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_show_feature_list(oal_void)
{
    oam_feature_enum_uint8              en_feature_id;

    OAL_IO_PRINT("feature_list: \r\n");
    for (en_feature_id = 0; en_feature_id < OAM_SOFTWARE_FEATURE_BUTT; en_feature_id++)
    {
        OAL_IO_PRINT("%s\r\n", gst_oam_feature_list[en_feature_id].auc_feature_name_abbr);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_format_string
 功能描述  : 根据格式,将日志信息写入到指定的文件中
 输入参数  : oal_int8                        *pac_output_data
             oal_uint16                       us_data_len
             oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_uint8                        uc_param_cnt
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_format_string(
                oal_int8                        *pac_output_data,
                oal_uint16                       us_data_len,
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_uint8                        uc_param_cnt,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4)
{
    oal_int8            *pac_print_level_tbl[]= {"OFF", "ERROR", "WARNING", "INFO"};
    oal_uint32           ul_tick;
    oal_uint8            auc_feature_name[OAM_FEATURE_NAME_ABBR_LEN] = {0};
    oal_int8            *pac_print_format[] =
    {
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu, %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu, %lu, %lu \r\n"
     };

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    oam_get_feature_name(en_feature_id, auc_feature_name, OAL_SIZEOF(auc_feature_name));

    /* 根据参数个数,将LOG信息保存到ac_file_data中 */
    switch (uc_param_cnt)
    {
        case 0:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string);
            break;

        case 1:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string, l_param1);
            break;

        case 2:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string, l_param1, l_param2);
            break;

        case 3:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string,
                        l_param1, l_param2, l_param3);
            break;

        case 4:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string,
                        l_param1, l_param2, l_param3, l_param4);
            break;

        default:
            OAM_IO_PRINTK("invalid uc_param_cnt.[%d] \r\n", uc_param_cnt);
            return OAL_FAIL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_set_log_info_stru
 功能描述  : 填写log结构体信息
 输入参数  : 1) 输出内容
             2) 输出最长长度
             3) 打印级别
             4) VAP编号
             5) 模块ID
             6) 文件ID
             7) 行号
             8) 要打印的字符串
             9)打印的参数个数
             10) 需要打印的第一个参数
             11) 需要打印的第二个参数
             12)需要打印的第三个参数
             13)需要打印的第四个参数
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  oam_set_log_info_stru(
                 oam_log_info_stru               *pst_log_info,
                 oal_uint8                        uc_vap_id,
                 oam_feature_enum_uint8           en_feature_id,
                 oal_uint16                       us_file_id,
                 oal_uint16                       us_line_num,
                 oam_log_level_enum_uint8         en_log_level,
                 oal_int32                        l_param1,
                 oal_int32                        l_param2,
                 oal_int32                        l_param3,
                 oal_int32                        l_param4)
{
    oal_uint32                      ul_tick;

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 为日志结构体整数成员赋值 */
    pst_log_info->st_vap_log_level.bit_vap_id       = uc_vap_id;
    pst_log_info->st_vap_log_level.bit_log_level    = en_log_level;
    pst_log_info->us_file_id                        = us_file_id;
    pst_log_info->us_line_num                       = us_line_num;
    pst_log_info->en_feature_id                     = en_feature_id;
    pst_log_info->ul_tick                           = ul_tick;
    pst_log_info->al_param[0]                       = l_param1;
    pst_log_info->al_param[1]                       = l_param2;
    pst_log_info->al_param[2]                       = l_param3;
    pst_log_info->al_param[3]                       = l_param4;
}

#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) /* UT需要部分接口进行测试 */
/*****************************************************************************
 函 数 名  : oam_log_check_param
 功能描述  : 检查VAP编号、模块ID和打印级别的有效性
 输入参数  : oal_uint8                           uc_vap_id
             oam_feature_enum_uint8              en_feature_id
             oam_log_level_enum_uint8            en_log_level
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_check_param(
                oal_uint8                           uc_vap_id,
                oam_feature_enum_uint8              en_feature_id,
                oam_log_level_enum_uint8            en_log_level)
{
    /* 判断VAP是否合理 */
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d]. \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 判断特性ID的合理性 */
    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id[%d]. \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 判断打印级别的合理性 */
    if (OAL_UNLIKELY(en_log_level >= OAM_LOG_LEVEL_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_level[%d]. \r\n", en_log_level);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_feature_level
 功能描述  : 获取VAP特性日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_soft_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 *pen_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_feature_level( oal_uint8 uc_vap_id,
                                                        oam_feature_enum_uint8 en_feature_id,
                                                        oam_log_level_enum_uint8 *pen_log_level)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id.[%d] \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_level))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_level = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_global_switch
 功能描述  : 获取全局开关状态
 输入参数  : oal_switch_enum_uint8 *pen_log_switch
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月6日,星期五
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_global_switch(oal_switch_enum_uint8 *pen_log_switch)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_switch = g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_vap_switch
 功能描述  : 获取VAP日志开关
 输入参数  : oal_uint8 uc_vap_id
             oal_switch_enum_uint8 *pen_log_switch
 输出参数  : pen_log_switch
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_vap_switch(oal_uint8 uc_vap_id,
                                                    oal_switch_enum_uint8 *pen_log_switch)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_switch = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id];

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : oam_log_print_check
 功能描述  : 打印前参数的合理性检查
 输入参数  : 1) VAP编号
             2) 模块ID
             3) 打印级别
             4) 是否需要打印标识
 输出参数  : 无
 返 回 值  : 1) OAL_ERR_CODE_PTR_NULL: 空指针
             2) OAL_ERR_CODE_ARRAY_OVERFLOW: 枚举溢出
             3) OAL_FAIL :失败
             4) OAL_SUCC :成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_switch_check(
                oal_uint8                           uc_vap_id,
                oam_feature_enum_uint8              en_feature_id,
                oam_log_level_enum_uint8            en_log_level,
                oal_switch_enum_uint8              *pen_log_switch)
{
    oal_uint32                      ul_rslt             = OAL_FAIL;
    oam_log_level_enum_uint8        en_log_cfg_level    = OAM_LOG_LEVEL_BUTT;
    oal_switch_enum_uint8           en_log_switch       = OAL_SWITCH_OFF;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

     /* VAP编号、模块ID和打印级别参数检查 */
    ul_rslt = oam_log_check_param(uc_vap_id, en_feature_id, en_log_level);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    /* 获取全局日志开关 */
    oam_log_get_global_switch(&en_log_switch);
    if (OAL_SWITCH_OFF == en_log_switch)
    {
        return OAL_SUCC;
    }

    /* 获取VAP日志开关 */
    oam_log_get_vap_switch(uc_vap_id, &en_log_switch);
    if (OAL_SWITCH_OFF == en_log_switch)
    {
        return OAL_SUCC;
    }

    /* 获取特性日志级别 */
    oam_log_get_feature_level(uc_vap_id, en_feature_id, &en_log_cfg_level);
    if (en_log_level > en_log_cfg_level)
    {
        return OAL_SUCC;
    }

    /* 日志级别大于等于特性日志级别，则符合日志输出条件 */
    *pen_log_switch = OAL_SWITCH_ON;

    return OAL_SUCC;
}
#endif
#endif

/*****************************************************************************
 函 数 名  : oam_log_print_to_console
 功能描述  : 日志输出至串口终端
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_uint8                        uc_param_cnt
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_print_to_console(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_uint8                        uc_param_cnt,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4)
{
    oal_int8    ac_print_buff[OAM_PRINT_FORMAT_LENGTH]; /* 用于保存写入到文件中的格式 */

    oam_log_format_string(ac_print_buff,
                          OAM_PRINT_FORMAT_LENGTH,
                          uc_vap_id,
                          en_feature_id,
                          us_file_id,
                          us_line_num,
                          en_log_level,
                          pc_string,
                          uc_param_cnt,
                          l_param1,
                          l_param2,
                          l_param3,
                          l_param4);

    oam_print_to_console(ac_print_buff);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_alarm_print_to_file
 功能描述  : 将日志信息打印到文件中
 输入参数  : 1) VAP编号
             2) 文件ID
             3) 行号
             4) 模块ID
             5) 打印级别
             6) 要打印的字符串
             7) 打印的参数个数
             8) 需要打印的第一个参数
             9) 需要打印的第二个参数
             10)需要打印的第三个参数
             11)需要打印的第四个参数
 输出参数  : 无
 返 回 值  : 1) OAL_ERR_CODE_PTR_NULL: 空指针
             2) OAL_ERR_CODE_ARRAY_OVERFLOW: 枚举溢出
             3) OAL_SUCC :成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print_to_file(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_uint8                        uc_param_cnt,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4)
{
#ifdef _PRE_WIFI_DMT
    oal_int8    ac_output_data[OAM_PRINT_FORMAT_LENGTH]; /* 用于保存写入到文件中的格式 */
    oal_uint32  ul_ret;

    oam_log_format_string(ac_output_data,
                          OAM_PRINT_FORMAT_LENGTH,
                          uc_vap_id,
                          en_feature_id,
                          us_file_id,
                          us_line_num,
                          en_log_level,
                          pc_string,
                          uc_param_cnt,
                          l_param1,
                          l_param2,
                          l_param3,
                          l_param4);

    ul_ret = oam_print_to_file(ac_output_data);

    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_alarm_print_to_sdt
 功能描述  : 日志的标准输出函数
 输入参数  : 1) VAP编号
             2) 文件ID
             3) 行号
             4) 模块ID
             5) 打印级别
             6) 要打印的字符串
             7) 打印的参数个数
             8) 需要打印的第一个参数
             9) 需要打印的第二个参数
             10)需要打印的第三个参数
             11)需要打印的第四个参数
 输出参数  : 无
 返 回 值  : OAL_SUCC: 成功,或其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_print_to_sdt(
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4)
{
    oal_uint32                      ul_ret;
    oam_log_info_stru               st_log_info;

    OAL_MEMZERO(&st_log_info, OAL_SIZEOF(oam_log_info_stru));

    oam_set_log_info_stru(&st_log_info,
                          uc_vap_id,
                          en_feature_id,
                          us_file_id,
                          us_line_num,
                          en_log_level,
                          l_param1,
                          l_param2,
                          l_param3,
                          l_param4);

    /* WARNING和ERROR级别流控 */
    if ((OAM_LOG_LEVEL_INFO != en_log_level)
        && (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_LOG)))
    {
        return OAL_SUCC;
    }

    ul_ret = oam_upload_log_to_sdt((oal_int8 *)&st_log_info);

    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_print_n_param
 功能描述  : LOG模块提供的LOG打印函数总入口(N个参数)
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_uint8                        uc_param_cnt
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_print_n_param(oal_uint8                        uc_vap_id,
                                                    oam_feature_enum_uint8           en_feature_id,
                                                    oal_uint16                       us_file_id,
                                                    oal_uint16                       us_line_num,
                                                    oam_log_level_enum_uint8         en_log_level,
                                                    oal_int8                        *pc_string,
                                                    oal_uint8                        uc_param_cnt,
                                                    oal_int32                        l_param1,
                                                    oal_int32                        l_param2,
                                                    oal_int32                        l_param3,
                                                    oal_int32                        l_param4)
{
    oal_uint32                  ul_ret          = OAL_SUCC;
    //oal_switch_enum_uint8       en_log_switch   = OAL_SWITCH_OFF;
    oam_output_type_enum_uint8  en_output_type;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_string))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if 0   /* 日志输出检查放在宏实现中 */
    /* 判断是否满足日志输出条件 */
    oam_log_switch_check(uc_vap_id, en_feature_id, en_log_level, &en_log_switch);
    if (OAL_SWITCH_OFF == en_log_switch)
    {
        return OAL_SUCC;
    }
#endif

    /* 若输出条件满足，判断输出方向 */
    oam_get_output_type(&en_output_type);
    switch (en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_ret = oam_log_print_to_console(uc_vap_id,
                                               en_feature_id,
                                               us_file_id,
                                               us_line_num,
                                               en_log_level,
                                               pc_string,
                                               uc_param_cnt,
                                               l_param1,
                                               l_param2,
                                               l_param3,
                                               l_param4);
            break;

        /* 输出至文件系统中 */
        case OAM_OUTPUT_TYPE_FS:
            ul_ret =  oam_log_print_to_file(uc_vap_id,
                                            en_feature_id,
                                            us_file_id,
                                            us_line_num,
                                            en_log_level,
                                            pc_string,
                                            uc_param_cnt,
                                            l_param1,
                                            l_param2,
                                            l_param3,
                                            l_param4);
            break;

        /* 输出至PC侧调测工具平台 */
        case OAM_OUTPUT_TYPE_SDT:
            ul_ret =  oam_log_print_to_sdt(uc_vap_id,
                                           en_feature_id,
                                           us_file_id,
                                           us_line_num,
                                           en_log_level,
                                           pc_string,
                                           l_param1,
                                           l_param2,
                                           l_param3,
                                           l_param4);

            break;

        /* 无效配置 */
        default:
            ul_ret = OAL_ERR_CODE_INVALID_CONFIG;
            break;
    }

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_log_print0
 功能描述  : 日志打印函数：无参数日志输出
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print0( oal_uint8                        uc_vap_id,
                                oam_feature_enum_uint8           en_feature_id,
                                oal_uint16                       us_file_id,
                                oal_uint16                       us_line_num,
                                oam_log_level_enum_uint8         en_log_level,
                                oal_int8                        *pc_string,
                                oal_int32                        l_param1,
                                oal_int32                        l_param2,
                                oal_int32                        l_param3,
                                oal_int32                        l_param4)
{
    oal_uint32 ul_ret = OAL_SUCC;
    if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, en_log_level))
    {
        ul_ret = oam_log_print_n_param(uc_vap_id, en_feature_id, us_file_id, us_line_num, en_log_level, pc_string, 0, 0, 0, 0, 0);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_print1
 功能描述  : 日志打印函数：一个参数
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print1( oal_uint8                        uc_vap_id,
                            oam_feature_enum_uint8           en_feature_id,
                            oal_uint16                       us_file_id,
                            oal_uint16                       us_line_num,
                            oam_log_level_enum_uint8         en_log_level,
                            oal_int8                        *pc_string,
                            oal_int32                        l_param1,
                            oal_int32                        l_param2,
                            oal_int32                        l_param3,
                            oal_int32                        l_param4)
{
    oal_uint32 ul_ret = OAL_SUCC;
    if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, en_log_level))
    {
        ul_ret = oam_log_print_n_param(uc_vap_id, en_feature_id, us_file_id, us_line_num,\
                                 en_log_level, pc_string, 1, l_param1, 0, 0, 0);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_print2
 功能描述  : 日志打印函数：两个参数
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print2( oal_uint8                        uc_vap_id,
                                oam_feature_enum_uint8           en_feature_id,
                                oal_uint16                       us_file_id,
                                oal_uint16                       us_line_num,
                                oam_log_level_enum_uint8         en_log_level,
                                oal_int8                        *pc_string,
                                oal_int32                        l_param1,
                                oal_int32                        l_param2,
                                oal_int32                        l_param3,
                                oal_int32                        l_param4)
{
    oal_uint32 ul_ret = OAL_SUCC;
    if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, en_log_level))
    {
        ul_ret = oam_log_print_n_param(uc_vap_id, en_feature_id, us_file_id, us_line_num,\
                                 en_log_level, pc_string, 2, l_param1, l_param2, 0, 0);
    }

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : oam_log_print3
 功能描述  : 日志打印函数：三个参数
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print3( oal_uint8                        uc_vap_id,
                                oam_feature_enum_uint8           en_feature_id,
                                oal_uint16                       us_file_id,
                                oal_uint16                       us_line_num,
                                oam_log_level_enum_uint8         en_log_level,
                                oal_int8                        *pc_string,
                                oal_int32                        l_param1,
                                oal_int32                        l_param2,
                                oal_int32                        l_param3,
                                oal_int32                        l_param4)
{
    oal_uint32 ul_ret = OAL_SUCC;
    if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, en_log_level))
    {
        ul_ret = oam_log_print_n_param(uc_vap_id, en_feature_id, us_file_id, us_line_num,\
                                 en_log_level, pc_string, 3, l_param1, l_param2, l_param3, 0);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_print4
 功能描述  : 日志打印函数：四个参数
 输入参数  : oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_print4( oal_uint8                        uc_vap_id,
                                oam_feature_enum_uint8           en_feature_id,
                                oal_uint16                       us_file_id,
                                oal_uint16                       us_line_num,
                                oam_log_level_enum_uint8         en_log_level,
                                oal_int8                        *pc_string,
                                oal_int32                        l_param1,
                                oal_int32                        l_param2,
                                oal_int32                        l_param3,
                                oal_int32                        l_param4)
{
    oal_uint32 ul_ret = OAL_SUCC;
    if (OAL_SWITCH_ON == oam_get_log_switch(uc_vap_id, en_feature_id, en_log_level))
    {
        ul_ret = oam_log_print_n_param(uc_vap_id, en_feature_id, us_file_id, us_line_num, en_log_level,\
                                 pc_string, 4, l_param1, l_param2, l_param3, l_param4);
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_log_printk
 功能描述  : 串口输出日志
 输入参数  : oal_uint16                       us_file_no
             oal_uint16                       us_line_num
             const oal_int8                  *pc_func_name
             oal_int8                        *pc_args_buf
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                oal_int8                        *pc_args_buf)
{
    oal_int8    ac_output_data[OAM_PRINT_FORMAT_LENGTH]; /* 用于保存写入到文件中的格式 */
    oal_int8    ac_printk_format[] = {"Tick=%lu, FileId=%d, LineNo=%d, FuncName::%s, \"%s\"\r\n"};
    oal_uint32  ul_tick;

    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    OAL_SPRINTF(ac_output_data, OAM_PRINT_FORMAT_LENGTH, ac_printk_format, ul_tick, us_file_no,
                us_line_num, pc_func_name, pc_args_buf);

    OAL_IO_PRINT("%s\r\n", ac_output_data);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_console_printk
 功能描述  : 输出串口日志函数
             防止串口频繁打印，该串口使用了流控
 输入参数  : oal_uint16                       us_file_no
             oal_uint16                       us_line_num
             const oal_int8                  *pc_func_name
             const oal_int8                  *pc_fmt
             ...
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_console_printk(
                oal_uint16                       us_file_no,
                oal_uint16                       us_line_num,
                const oal_int8                  *pc_func_name,
                const oal_int8                  *pc_fmt,
                ...)

{
    oal_int8                    ac_args_buf[OAM_PRINT_FORMAT_LENGTH];
    OAL_VA_LIST                 pc_args;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pc_func_name) || (OAL_PTR_NULL == pc_fmt)))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 流控判断 */
    if (OAM_RATELIMIT_NOT_OUTPUT == oam_log_ratelimit(OAM_RATELIMIT_TYPE_PRINTK))
    {
        return OAL_SUCC;
    }

    OAL_VA_START(pc_args, pc_fmt);
    OAL_VSPRINTF(ac_args_buf, OAM_PRINT_FORMAT_LENGTH, pc_fmt, pc_args);
    OAL_VA_END(pc_args);

    oam_log_printk(us_file_no, us_line_num, pc_func_name, ac_args_buf);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_ratelimit_init
 功能描述  : printk日志流控初始化
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_ratelimit_init(oal_void)
{
    oal_uint32                          ul_ret = OAL_SUCC;
    oam_ratelimit_type_enum_uint8       en_type_idx;

    OAL_MEMZERO(&g_st_oam_mng_ctx.st_log_ctx.st_ratelimit, OAL_SIZEOF(oam_ratelimit_stru) * OAM_RATELIMIT_TYPE_BUTT);

    for (en_type_idx = 0; en_type_idx < OAM_RATELIMIT_TYPE_BUTT; en_type_idx++)
    {
        oal_spin_lock_init(&g_st_oam_mng_ctx.st_log_ctx.st_ratelimit[en_type_idx].spin_lock);
        ul_ret += oam_log_set_ratelimit_switch(en_type_idx, OAL_SWITCH_OFF);
        ul_ret += oam_log_set_ratelimit_intervel(en_type_idx, OAM_RATELIMIT_DEFAULT_INTERVAL);
        ul_ret += oam_log_set_ratelimit_burst(en_type_idx, OAM_RATELIMIT_DEFAULT_BURST);
    }
    return ul_ret;
}

oal_void oam_log_param_init(oal_void)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef CONFIG_PRINTK
    oal_int32 i;
    for(i = 0; i < OAM_LOG_LEVEL_BUTT; i++)
    {
        g_loglevel_string[i] = "X";
    }
    g_loglevel_string[OAM_LOG_LEVEL_ERROR] = "E";
    g_loglevel_string[OAM_LOG_LEVEL_WARNING] = "W";
    g_loglevel_string[OAM_LOG_LEVEL_INFO] = "I";
#endif
#endif
}

/*****************************************************************************
 函 数 名  : oam_log_init
 功能描述  : 对LOG模块进行初始化操作
             (系统上电和系统复位调用，在oam_init函数执行完后调用)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC:成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_init(oal_void)
{
    oal_uint8   uc_vap_idx;
    oal_uint32  ul_ret      = OAL_SUCC;

    oam_log_param_init();

    /* 日志全局开关默认为开 */
    ul_ret = oam_log_set_global_switch(OAL_SWITCH_ON);

    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* VAP级别日志设置 */
    for (uc_vap_idx = 0; uc_vap_idx < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_idx++)
    {
        /* 设置VAP日志开关 */
        ul_ret += oam_log_set_vap_switch(uc_vap_idx, OAL_SWITCH_ON);

        /* 设置VAP日志级别 */
        ul_ret += oam_log_set_vap_level(uc_vap_idx, OAM_LOG_DEFAULT_LEVEL);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
        /* 设置feature打印级别 */
        ul_ret += oam_log_set_feature_level(uc_vap_idx, OAM_SF_WPA, OAM_LOG_LEVEL_INFO);
#endif
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    /* printk日志流控初始化 */
    ul_ret = oam_log_ratelimit_init();

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_exception_record
 功能描述  : 异常统计记录更新
 输入参数  : oal_uint8 uc_vap_id
             oam_excp_type_enum_uint8 en_excp_id
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_exception_record(oal_uint8 uc_vap_id, oam_excp_type_enum_uint8 en_excp_id)
{
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_excp_id >= OAM_EXCP_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_excp_id[%d]. \r\n", en_excp_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_id].ul_record_cnt++;

    /* 已刷新，可上报 */
    g_st_oam_mng_ctx.st_exception_ctx.en_status = OAM_EXCP_STATUS_REFRESHED;

    g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_id].en_status = OAM_EXCP_STATUS_REFRESHED;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_exception_stat_report
 功能描述  : 异常统计上报函数入口
 输入参数  : oal_uint8 uc_vap_id
             oam_excp_type_enum_uint8 en_excp_id
             oal_uint32 ul_cnt
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_exception_stat_report(
                oal_uint8 uc_vap_id,
                oam_excp_type_enum_uint8 en_excp_id,
                oal_uint32 ul_cnt)
{
    switch (en_excp_id)
    {
        case OAM_HAL_MAC_ERROR_PARA_CFG_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PARA_CFG_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_Q_EMPTY:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_Q_EMPTY.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_RLEN_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_RLEN_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_RADDR_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_RADDR_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_WLEN_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_WLEN_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_WADDR_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_WADDR_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_CCA_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_CCA_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BEACON_MISS:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BEACON_MISS.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_28:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_28.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_29:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_29.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_30:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_30.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_31:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_31.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_BUCK_OCP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_BUCK_OCP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_BUCK_SCP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_BUCK_SCP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_RFLDO1:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_RFLDO1.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_RFLDO2:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_RFLDO2.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_CLDO:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_CLDO.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_RF_OVER_TEMP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_RF_OVER_TEMP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_CMU_UNLOCK:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_CMU_UNLOCK.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_PCIE_SLV_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_PCIE_SLV_ERR.[%d]}\r\n", ul_cnt);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_exception_stat_handler
 功能描述  : 针对异常的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月16日
    作    者   : 张炜 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oam_exception_stat_handler(oal_uint8 en_moduleid, oal_uint8 uc_vap_idx)
{
    oam_excp_record_stru           *pst_excp_record;
    oam_excp_type_enum_uint8   en_excp_idx;

    switch (en_moduleid)
    {
        case OM_WIFI:
        {
            /* 当前VAP异常统计为0 */
            if (OAM_EXCP_STATUS_REFRESHED != g_st_oam_mng_ctx.st_exception_ctx.en_status)
            {
            }
            else
            {
                pst_excp_record = g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl;

                for (en_excp_idx = 0; en_excp_idx < OAM_EXCP_TYPE_BUTT; en_excp_idx++)
                {
                    /* 记录数已刷新 */
                    if (OAM_EXCP_STATUS_REFRESHED == pst_excp_record[en_excp_idx].en_status)
                    {
                        oam_exception_stat_report(uc_vap_idx, en_excp_idx, pst_excp_record[en_excp_idx].ul_record_cnt);
                        g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_idx].en_status = OAM_EXCP_STATUS_INIT;
                    }
                }

                /* 已上报，置初始状态 */
                g_st_oam_mng_ctx.st_exception_ctx.en_status = OAM_EXCP_STATUS_INIT;
            }
        }
        break;

        default:
        break;
    }
}



/*lint -e19*/
oal_module_symbol(OAL_PRINT2KERNEL);
oal_module_symbol(OAL_PRINT_NLOGS);
oal_module_symbol(oam_log_print0);
oal_module_symbol(oam_log_set_global_switch);
oal_module_symbol(oam_log_set_vap_switch);
oal_module_symbol(oam_log_set_vap_level);
oal_module_symbol(oam_log_set_feature_level);
oal_module_symbol(oam_log_console_printk);
oal_module_symbol(oam_log_set_ratelimit_param);
oal_module_symbol(oam_get_feature_id);
oal_module_symbol(oam_log_get_vap_level);
oal_module_symbol(oam_show_feature_list);

oal_module_symbol(oam_log_print1);
oal_module_symbol(oam_log_print2);
oal_module_symbol(oam_log_print3);
oal_module_symbol(oam_log_print4);
oal_module_symbol(oam_exception_record);
oal_module_symbol(oam_exception_stat_handler);

#ifdef _PRE_DEBUG_MODE
oal_module_symbol(g_ast_tx_complete_stat);
#endif

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_main.h"
#include "oam_log.h"
#ifdef CONFIG_PRINTK
#include <linux/kernel.h>
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_LOG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
    oam_tx_complete_stat_stru   g_ast_tx_complete_stat[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC];
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef CONFIG_PRINTK
static char* g_loglevel_string[OAM_LOG_LEVEL_BUTT] ;
#endif
#endif

#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
oal_uint16           g_print2sdt_control = 1;    //1为oam格式日志上报sdt，0为不上报
volatile oal_uint8   g_uc_uart_ctrl = SDT_DUMP_CLOSE;
oal_uint32           g_ul_file_count = 0;         //liteos dump 的文件大小，byte为单位
oal_uint32           g_ul_cnt_statistic = 0;      //统计已经通过sdt dump到liteos的字节数

FILE*                g_l_fopen_fd = NULL;

oal_uint16           g_us_oam_sn = 0;
oal_uint8            g_auc_log_buf[OAM_LOG_MSG_LEN];
oal_uint8            g_auc_oam_printf_log_buf[OAL_SIZEOF(OM_PRINTF_INTO_STRU)];
oal_netbuf_stru        g_st_skb_temp;
/*OAM日志处理全局变量*/
sdt_drv_mng_stru g_st_sdt_drv_mng_entry;
/*记录处理的OAM日志数，判断日志是否丢失时用*/
oal_uint32    g_uloam_test_cnt = 0;
/*记录处理的oam_task_thread 处理的cycle数*/
oal_uint32    g_uloam_test_step = 0;
/*记录OAM 日志链表待处理netbuf数*/
oal_uint32    g_uloam_skbuff_list_len = 0;
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : oam_log_set_global_switch
 功能描述  : 设置日志全局开关状态
 输入参数  : oal_switch_enum_uint8 en_log_switch
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_global_switch(oal_switch_enum_uint8 en_log_switch)
{
#if 0
    if (OAL_UNLIKELY(en_log_switch >= OAL_SWITCH_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_switch[%d]. \r\n", en_log_switch);
        return OAL_FAIL;
    }

    g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch = en_log_switch;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_vap_switch
 功能描述  : 设置VAP日志开关
 输入参数  : oal_uint8 uc_vap_id
             oam_log_switch_enum_uint8 en_log_switch
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_vap_switch(oal_uint8 uc_vap_id,
                                         oal_switch_enum_uint8 en_log_switch)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d]. \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_log_switch >= OAL_SWITCH_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_switch[%d]. \r\n", en_log_switch);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id] = en_log_switch;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_vap_level
 功能描述  : 设置VAP下所有特性日志级别为en_log_level
             不允许设置成OAM_LOG_LEVEL_INFO级别,在命令行里进行限制，本函数不处理
 输入参数  : oal_uint8 uc_vap_id
             oam_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 en_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 en_log_level)
{
#if 0
    oam_feature_enum_uint8       en_feature_idx;

    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid vap id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 设置当前VAP的日志级别 */
    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id] = en_log_level;

    /* 同时设置当前VAP下所有特性日志级别 */
    for (en_feature_idx = 0; en_feature_idx < OAM_SOFTWARE_FEATURE_BUTT; en_feature_idx++)
    {
        oam_log_set_feature_level(uc_vap_id, en_feature_idx, en_log_level);
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_vap_level
 功能描述  : 获取VAP的日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_log_level_enum_uint8 *pen_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_get_vap_level(oal_uint8 uc_vap_id, oam_log_level_enum_uint8 *pen_log_level)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid vap id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_level))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_level = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_level[uc_vap_id];
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_set_feature_level
 功能描述  : 设置VAP下特性日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 en_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_log_set_feature_level(oal_uint8 uc_vap_id,
                                           oam_feature_enum_uint8 en_feature_id,
                                           oam_log_level_enum_uint8 en_log_level)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id.[%d] \r\n", uc_vap_id);
        return  OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id.[%d] \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY((en_log_level >= OAM_LOG_LEVEL_BUTT) || (en_log_level < OAM_LOG_LEVEL_ERROR)))
    {
        OAM_IO_PRINTK("invalid en_log_level.[%d] \r\n", en_log_level);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id] = en_log_level;
#endif
    //OAL_IO_PRINT("oam_log_set_feature_level:: uc_vap_id=%u, en_feature_id=%u, en_log_level=%u\r\n", uc_vap_id, en_feature_id, en_log_level);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_get_feature_id
 功能描述  : 由特性名称获取特性ID
 输入参数  : oal_uint8 *puc_feature_name
             oam_feature_enum_uint8 *puc_feature_id
 输出参数  : puc_feature_id  对应特性名称的ID号
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_get_feature_id(oal_uint8 *puc_feature_name,
                                   oam_feature_enum_uint8 *puc_feature_id)
{
#if 0
    oam_feature_enum_uint8   en_feature_idx;

    if (OAL_UNLIKELY((OAL_PTR_NULL == puc_feature_name) || (OAL_PTR_NULL == puc_feature_id)))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (en_feature_idx = 0; en_feature_idx < OAM_SOFTWARE_FEATURE_BUTT; en_feature_idx++)
    {
        if (0 == oal_strcmp((oal_int8 *)gst_oam_feature_list[en_feature_idx].auc_feature_name_abbr, (oal_int8 *)puc_feature_name))
        {
            *puc_feature_id = en_feature_idx;
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_get_feature_name
 功能描述  : 获取指定特性ID的特性名称
 输入参数  : oam_feature_enum_uint8     en_feature_id
             oal_uint8    *puc_feature_name
             oal_uint8     uc_size
 输出参数  : puc_feature_name
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_get_feature_name( oam_feature_enum_uint8     en_feature_id,
                                      oal_uint8    *puc_feature_name,
                                      oal_uint8     uc_size)
{
    oal_uint8       uc_feature_len;

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("en_feature_id override. %d. \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_feature_name))
    {
        OAM_IO_PRINTK("puc_feature_name is NULL. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_feature_len = (oal_uint8)OAL_STRLEN((oal_int8*)gst_oam_feature_list[en_feature_id].auc_feature_name_abbr);
    uc_size = (uc_size > uc_feature_len) ? uc_feature_len : uc_size;

    oal_memcopy(puc_feature_name, gst_oam_feature_list[en_feature_id].auc_feature_name_abbr, uc_size);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_show_feature_list
 功能描述  : 显示特性缩写与全称的帮助信息
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月30日,星期五
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_show_feature_list(oal_void)
{
    oam_feature_enum_uint8              en_feature_id;

    OAL_IO_PRINT("feature_list: \r\n");
    for (en_feature_id = 0; en_feature_id < OAM_SOFTWARE_FEATURE_BUTT; en_feature_id++)
    {
        OAL_IO_PRINT("%s\r\n", gst_oam_feature_list[en_feature_id].auc_feature_name_abbr);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_format_string
 功能描述  : 根据格式,将日志信息写入到指定的文件中
 输入参数  : oal_int8                        *pac_output_data
             oal_uint16                       us_data_len
             oal_uint8                        uc_vap_id
             oam_feature_enum_uint8           en_feature_id
             oal_uint16                       us_file_id
             oal_uint16                       us_line_num
             oam_log_level_enum_uint8         en_log_level
             oal_int8                        *pc_string
             oal_uint8                        uc_param_cnt
             oal_int32                        l_param1
             oal_int32                        l_param2
             oal_int32                        l_param3
             oal_int32                        l_param4
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_format_string(
                oal_int8                        *pac_output_data,
                oal_uint16                       us_data_len,
                oal_uint8                        uc_vap_id,
                oam_feature_enum_uint8           en_feature_id,
                oal_uint16                       us_file_id,
                oal_uint16                       us_line_num,
                oam_log_level_enum_uint8         en_log_level,
                oal_int8                        *pc_string,
                oal_uint8                        uc_param_cnt,
                oal_int32                        l_param1,
                oal_int32                        l_param2,
                oal_int32                        l_param3,
                oal_int32                        l_param4)
{
    oal_int8            *pac_print_level_tbl[]= {"OFF", "ERROR", "WARNING", "INFO"};
    oal_uint32           ul_tick;
    oal_uint8            auc_feature_name[OAM_FEATURE_NAME_ABBR_LEN] = {0};
    oal_int8            *pac_print_format[] =
    {
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu, %lu \r\n",
        "【LOG=%s】:Tick=%lu, FileId=%d, LineNo=%d, VAP=%d, FeatureName=%s, \"%s\", %lu, %lu, %lu, %lu \r\n"
     };

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    oam_get_feature_name(en_feature_id, auc_feature_name, OAL_SIZEOF(auc_feature_name));

    /* 根据参数个数,将LOG信息保存到ac_file_data中 */
    switch (uc_param_cnt)
    {
        case 0:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string);
            break;

        case 1:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string, l_param1);
            break;

        case 2:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string, l_param1, l_param2);
            break;

        case 3:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string,
                        l_param1, l_param2, l_param3);
            break;

        case 4:
            OAL_SPRINTF(pac_output_data, us_data_len, pac_print_format[uc_param_cnt], pac_print_level_tbl[en_log_level],
                        ul_tick, us_file_id, us_line_num, uc_vap_id, auc_feature_name, pc_string,
                        l_param1, l_param2, l_param3, l_param4);
            break;

        default:
            OAM_IO_PRINTK("invalid uc_param_cnt.[%d] \r\n", uc_param_cnt);
            return OAL_FAIL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_set_log_info_stru
 功能描述  : 填写log结构体信息
 输入参数  : 1) 输出内容
             2) 输出最长长度
             3) 打印级别
             4) VAP编号
             5) 模块ID
             6) 文件ID
             7) 行号
             8) 要打印的字符串
             9)打印的参数个数
             10) 需要打印的第一个参数
             11) 需要打印的第二个参数
             12)需要打印的第三个参数
             13)需要打印的第四个参数
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  oam_set_log_info_stru(
                 oam_log_info_stru               *pst_log_info,
                 oal_uint8                        uc_vap_id,
                 oam_feature_enum_uint8           en_feature_id,
                 oal_uint16                       us_file_id,
                 oal_uint16                       us_line_num,
                 oam_log_level_enum_uint8         en_log_level,
                 oal_int32                        l_param1,
                 oal_int32                        l_param2,
                 oal_int32                        l_param3,
                 oal_int32                        l_param4)
{
    oal_uint32                      ul_tick;

    /* 获取系统TICK值 */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 为日志结构体整数成员赋值 */
    pst_log_info->st_vap_log_level.bit_vap_id       = uc_vap_id;
    pst_log_info->st_vap_log_level.bit_log_level    = en_log_level;
    pst_log_info->us_file_id                        = us_file_id;
    pst_log_info->us_line_num                       = us_line_num;
    pst_log_info->en_feature_id                     = en_feature_id;
    pst_log_info->ul_tick                           = ul_tick;
    pst_log_info->al_param[0]                       = l_param1;
    pst_log_info->al_param[1]                       = l_param2;
    pst_log_info->al_param[2]                       = l_param3;
    pst_log_info->al_param[3]                       = l_param4;
}

/*****************************************************************************
 函 数 名  : oam_log_check_param
 功能描述  : 检查VAP编号、模块ID和打印级别的有效性
 输入参数  : oal_uint8                           uc_vap_id
             oam_feature_enum_uint8              en_feature_id
             oam_log_level_enum_uint8            en_log_level
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_log_check_param(
                oal_uint8                           uc_vap_id,
                oam_feature_enum_uint8              en_feature_id,
                oam_log_level_enum_uint8            en_log_level)
{
    /* 判断VAP是否合理 */
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d]. \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 判断特性ID的合理性 */
    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id[%d]. \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 判断打印级别的合理性 */
    if (OAL_UNLIKELY(en_log_level >= OAM_LOG_LEVEL_BUTT))
    {
        OAM_IO_PRINTK("invalid en_log_level[%d]. \r\n", en_log_level);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_feature_level
 功能描述  : 获取VAP特性日志级别
 输入参数  : oal_uint8 uc_vap_id
             oam_soft_feature_enum_uint8 en_feature_id
             oam_log_level_enum_uint8 *pen_log_level
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月15日,星期四
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_feature_level( oal_uint8 uc_vap_id,
                                                        oam_feature_enum_uint8 en_feature_id,
                                                        oam_log_level_enum_uint8 *pen_log_level)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id.[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_feature_id >= OAM_SOFTWARE_FEATURE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_feature_id.[%d] \r\n", en_feature_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_level))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_level = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_feature_log_level[uc_vap_id][en_feature_id];
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_global_switch
 功能描述  : 获取全局开关状态
 输入参数  : oal_switch_enum_uint8 *pen_log_switch
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月6日,星期五
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_global_switch(oal_switch_enum_uint8 *pen_log_switch)
{
#if 0
    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param. \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_switch = g_st_oam_mng_ctx.st_log_ctx.en_global_log_switch;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_log_get_vap_switch
 功能描述  : 获取VAP日志开关
 输入参数  : oal_uint8 uc_vap_id
             oal_switch_enum_uint8 *pen_log_switch
 输出参数  : pen_log_switch
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月14日,星期三
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 oam_log_get_vap_switch(oal_uint8 uc_vap_id,
                                                    oal_switch_enum_uint8 *pen_log_switch)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_log_switch))
    {
        OAM_IO_PRINTK("null param \r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_log_switch = g_st_oam_mng_ctx.st_log_ctx.st_vap_log_info.aen_vap_log_switch[uc_vap_id];
#endif
    return OAL_SUCC;
}

oal_void oam_log_param_init(oal_void)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifdef CONFIG_PRINTK
    oal_int32 i;
    for(i = 0; i < OAM_LOG_LEVEL_BUTT; i++)
    {
        g_loglevel_string[i] = "X";
    }
    g_loglevel_string[OAM_LOG_LEVEL_ERROR] = "E";
    g_loglevel_string[OAM_LOG_LEVEL_WARNING] = "W";
    g_loglevel_string[OAM_LOG_LEVEL_INFO] = "I";
#endif
#endif
}

/*****************************************************************************
 函 数 名  : oam_log_init
 功能描述  : 对LOG模块进行初始化操作
             (系统上电和系统复位调用，在oam_init函数执行完后调用)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC:成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_log_init(oal_void)
{
    oal_uint8   uc_vap_idx;
    oal_uint32  ul_ret      = OAL_SUCC;

    oam_log_param_init();

    /* 日志全局开关默认为开 */
    ul_ret = oam_log_set_global_switch(OAL_SWITCH_ON);

    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* VAP级别日志设置 */
    for (uc_vap_idx = 0; uc_vap_idx < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_idx++)
    {
        /* 设置VAP日志开关 */
        ul_ret += oam_log_set_vap_switch(uc_vap_idx, OAL_SWITCH_ON);

        /* 设置VAP日志级别 */
        ul_ret += oam_log_set_vap_level(uc_vap_idx, OAM_LOG_DEFAULT_LEVEL);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
        /* 设置feature打印级别 */
        ul_ret += oam_log_set_feature_level(uc_vap_idx, OAM_SF_WPA, OAM_LOG_LEVEL_INFO);
#endif
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

#if 0
    /* printk日志流控初始化 */
    ul_ret = oam_log_ratelimit_init();
#endif

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : oam_exception_record
 功能描述  : 异常统计记录更新
 输入参数  : oal_uint8 uc_vap_id
             oam_excp_type_enum_uint8 en_excp_id
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_exception_record(oal_uint8 uc_vap_id, oam_excp_type_enum_uint8 en_excp_id)
{
#if 0
    if (OAL_UNLIKELY(uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        OAM_IO_PRINTK("invalid uc_vap_id[%d] \r\n", uc_vap_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (OAL_UNLIKELY(en_excp_id >= OAM_EXCP_TYPE_BUTT))
    {
        OAM_IO_PRINTK("invalid en_excp_id[%d]. \r\n", en_excp_id);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_id].ul_record_cnt++;

    /* 已刷新，可上报 */
    g_st_oam_mng_ctx.st_exception_ctx.en_status = OAM_EXCP_STATUS_REFRESHED;

    g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_id].en_status = OAM_EXCP_STATUS_REFRESHED;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_exception_stat_report
 功能描述  : 异常统计上报函数入口
 输入参数  : oal_uint8 uc_vap_id
             oam_excp_type_enum_uint8 en_excp_id
             oal_uint32 ul_cnt
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月26日,星期一
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 oam_exception_stat_report(
                oal_uint8 uc_vap_id,
                oam_excp_type_enum_uint8 en_excp_id,
                oal_uint32 ul_cnt)
{
    switch (en_excp_id)
    {
        case OAM_HAL_MAC_ERROR_PARA_CFG_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PARA_CFG_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PHY_TRLR_TIME_OUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_DATAFLOW_BREAK.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_RX_Q_EMPTY:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_RX_Q_EMPTY.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_HIRX_Q_EMPTY.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_RLEN_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_RLEN_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_RADDR_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_RADDR_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_WLEN_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_WLEN_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BUS_WADDR_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BUS_WADDR_ERR.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_CCA_TIMEOUT:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_CCA_TIMEOUT.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_DCOL_DATA_OVERLAP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_BEACON_MISS:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_BEACON_MISS.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_28:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_28.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_29:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_29.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_30:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_30.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_MAC_ERROR_UNKOWN_31:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_MAC_ERROR_UNKOWN_31.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_BUCK_OCP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_BUCK_OCP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_BUCK_SCP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_BUCK_SCP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_RFLDO1:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_RFLDO1.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_RFLDO2:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_RFLDO2.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_OCP_CLDO:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_OCP_CLDO.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_RF_OVER_TEMP:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_RF_OVER_TEMP.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_CMU_UNLOCK:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_CMU_UNLOCK.[%d]}\r\n", ul_cnt);
            break;

        case OAM_HAL_SOC_ERROR_PCIE_SLV_ERR:
            OAM_ERROR_LOG1(uc_vap_id, OAM_SF_ANY, "{Exception Statistics::OAM_HAL_SOC_ERROR_PCIE_SLV_ERR.[%d]}\r\n", ul_cnt);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}



static oal_void oam_log_header_fill(om_log_stru* pst_log_msg,
                                          oal_uint32 ul_para,
                                          oal_uint16 us_line_num)
{
    om_log_wifi_para_stru       st_para = {0};
    if (NULL == pst_log_msg)
    {
        return;
    }

    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));

    pst_log_msg->st_oam_header.ucFrameStart                 = OM_FRAME_DELIMITER;
    pst_log_msg->st_oam_header.ucFuncType                   = OAM_DATA_TYPE_LOG;
    pst_log_msg->st_oam_header.ucPrimeId                    = OM_WIFI;
    pst_log_msg->st_oam_header.usFrameLen                   = 0;
    pst_log_msg->st_oam_header.usSN                         = g_us_oam_sn;
    pst_log_msg->st_log_info.st_vap_log_level.bit_vap_id    = st_para.bit4_vap_id;
    pst_log_msg->st_log_info.st_vap_log_level.bit_log_level = st_para.bit4_log_level;
    pst_log_msg->st_log_info.en_feature_id                  = st_para.bit8_feature_id;
    pst_log_msg->st_log_info.us_file_id                     = st_para.bit16_file_id;
    pst_log_msg->st_log_info.us_line_num                    = us_line_num;
}


extern OAM_LOG_LUNTI g_st_global ;
void oam_log_roll_log(oal_uint8* pucdata, oal_uint16 len)
{
    FILE* fd = NULL;
    oam_get_log_file(&g_st_global);
    fd = g_st_global.pst_fd;
    if (NULL != fd)
    {
        fwrite(pucdata, len, 1, fd);
    }
    fclose(fd);
}

extern char uart_putc( char c);
extern oal_mutex_stru    g_oam_uart_print_mutex;
void oam_dev_host_uart_print(oal_uint8* pucdata, oal_uint16 us_len)
{
    oal_int32 ul_cnt;
    mutex_lock(&g_oam_uart_print_mutex);
    if (0 == g_print2sdt_control)
    {
        mutex_unlock(&g_oam_uart_print_mutex);
        return ;
    }

    for (ul_cnt = 0; ul_cnt < us_len; ul_cnt++)
    {
        uart_putc(*((oal_uint8 *)pucdata + ul_cnt));
    }
#if 0
    oam_log_roll_log(pucdata, us_len);
#endif
    mutex_unlock(&g_oam_uart_print_mutex);
}

OAL_STATIC OAL_INLINE oal_void  sdt_drv_netbuf_add_to_list(oal_netbuf_stru *pst_netbuf)
{
    oal_uint    ui_irq_save;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
    g_uloam_skbuff_list_len++;
    oal_netbuf_add_to_list_tail(pst_netbuf, &g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);
    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
}


oal_uint32 oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len)
{
    oal_netbuf_stru  *pst_netbuf;
    oal_uint8* pst_pos;
    pst_netbuf = oal_netbuf_alloc(len, 0, 0);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_FAIL;
    }
    oal_netbuf_put(pst_netbuf, len);
    pst_pos = (oal_uint8*)OAL_NETBUF_DATA(pst_netbuf);
    oal_memcopy(pst_pos, pc_string, (oal_uint16)len);
    sdt_drv_netbuf_add_to_list(pst_netbuf);
    LOS_EventWrite(&oam_event, oam_event_wait_bit0);
}

oal_uint32  oam_print0_press_ack(oal_uint32 ul_para,
                                         oal_uint16 us_line_num)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru*                pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 0;

    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));
#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg     = (om_log_stru*)g_auc_log_buf;
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.ucFuncType = OAM_DATA_TYPE_ACK;
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + OAL_SIZEOF(oal_uint8);    //加上分隔符的长度
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;
    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;
    /*走uart通道的命令为了实效性直接输出到串口*/
    oam_dev_host_uart_print(pst_log_msg, (oal_uint16) pst_log_msg->st_oam_header.usFrameLen);
    return OAL_SUCC;
}

oal_uint32  oam_log_print0_press(oal_uint32 ul_para,
                                         oal_uint16 us_line_num)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru               st_log_msg;
    om_log_stru*               pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 0;

    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));
#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg = (om_log_stru*)(&st_log_msg);
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + OAL_SIZEOF(oal_uint8);    //加上分隔符的长度
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;
    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;
    
    oam_send_device_data2sdt((oal_uint8*)pst_log_msg, pst_log_msg->st_oam_header.usFrameLen);

    return OAL_SUCC;
}

oal_uint32  oam_log_print1_press( oal_uint32            ul_para,
                                          oal_uint16            us_line_num,
                                          oal_int32             l_param1)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru                st_log_msg;
    om_log_stru*                pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 1;
    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));

#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg = (om_log_stru*)(&st_log_msg);
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + uc_para_num*OAL_SIZEOF(oal_uint32)
                                                    + OAL_SIZEOF(oal_uint8);
    pst_log_msg->st_log_info.al_param[0]            =  l_param1;
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;
    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;

    oam_send_device_data2sdt((oal_uint8*)pst_log_msg, pst_log_msg->st_oam_header.usFrameLen);

    return OAL_SUCC;
}
oal_uint32  oam_log_print2_press( oal_uint32    ul_para,
                                  oal_uint16            us_line_num,
                                  oal_int32             l_param1,
                                  oal_int32             l_param2)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru                st_log_msg;
    om_log_stru*                pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 2;
    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));

#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg = (om_log_stru*)(&st_log_msg);
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + uc_para_num*OAL_SIZEOF(oal_uint32)
                                                    + OAL_SIZEOF(oal_uint8);
    pst_log_msg->st_log_info.al_param[0]            =  l_param1;
    pst_log_msg->st_log_info.al_param[1]            =  l_param2;
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;
    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;

    oam_send_device_data2sdt((oal_uint8*)pst_log_msg, pst_log_msg->st_oam_header.usFrameLen);

    return OAL_SUCC;
}

oal_uint32  oam_log_print3_press( oal_uint32            ul_para,
                                          oal_uint16            us_line_num,
                                          oal_int32             l_param1,
                                          oal_int32             l_param2,
                                          oal_int32             l_param3)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru                st_log_msg;
    om_log_stru*                pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 3;

    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));

#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg = (om_log_stru*)(&st_log_msg);
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + uc_para_num*OAL_SIZEOF(oal_uint32)
                                                    + OAL_SIZEOF(oal_uint8);
    pst_log_msg->st_log_info.al_param[0]            =  l_param1;
    pst_log_msg->st_log_info.al_param[1]            =  l_param2;
    pst_log_msg->st_log_info.al_param[2]            =  l_param3;
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;
    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;

    oam_send_device_data2sdt((oal_uint8*)pst_log_msg, pst_log_msg->st_oam_header.usFrameLen);

    return OAL_SUCC;
}

oal_uint32  oam_log_print4_press( oal_uint32            ul_para,
                                          oal_uint16            us_line_num,
                                          oal_int32             l_param1,
                                          oal_int32             l_param2,
                                          oal_int32             l_param3,
                                          oal_int32             l_param4)
{
    om_log_wifi_para_stru       st_para = {0};
    om_log_stru                st_log_msg;
    om_log_stru*                pst_log_msg = NULL;
    oal_uint8                   uc_para_num = 4;

    oal_memcopy(&st_para, &ul_para, OAL_SIZEOF(om_log_wifi_para_stru));

#if 0
    if (OAL_SWITCH_ON != oam_get_log_switch(st_para.bit4_vap_id, st_para.bit8_feature_id, st_para.bit4_log_level))
    {
        return OAL_SUCC;
    }
#endif
    pst_log_msg = (om_log_stru*)(&st_log_msg);
    oam_log_header_fill(pst_log_msg,ul_para,us_line_num);
    pst_log_msg->st_oam_header.usFrameLen           = OAM_LOG_HEADER_LEN
                                                    + uc_para_num*OAL_SIZEOF(oal_uint32)
                                                    + OAL_SIZEOF(oal_uint8);
    pst_log_msg->st_log_info.al_param[0]            =  l_param1;
    pst_log_msg->st_log_info.al_param[1]            =  l_param2;
    pst_log_msg->st_log_info.al_param[2]            =  l_param3;
    pst_log_msg->st_log_info.al_param[3]            =  l_param4;
    pst_log_msg->st_log_info.al_param[uc_para_num]  = OM_FRAME_DELIMITER;

    ((oal_uint8*)pst_log_msg)[pst_log_msg->st_oam_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
    g_us_oam_sn++;

    oam_send_device_data2sdt((oal_uint8*)pst_log_msg, pst_log_msg->st_oam_header.usFrameLen);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oam_exception_stat_handler
 功能描述  : 针对异常的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月16日
    作    者   : 张炜 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oam_exception_stat_handler(oal_uint8 en_moduleid, oal_uint8 uc_vap_idx)
{
#if 0
    oam_excp_record_stru           *pst_excp_record;
    oam_excp_type_enum_uint8   en_excp_idx;

    switch (en_moduleid)
    {
        case OM_WIFI:
        {
            /* 当前VAP异常统计为0 */
            if (OAM_EXCP_STATUS_REFRESHED != g_st_oam_mng_ctx.st_exception_ctx.en_status)
            {
            }
            else
            {
                pst_excp_record = g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl;

                for (en_excp_idx = 0; en_excp_idx < OAM_EXCP_TYPE_BUTT; en_excp_idx++)
                {
                    /* 记录数已刷新 */
                    if (OAM_EXCP_STATUS_REFRESHED == pst_excp_record[en_excp_idx].en_status)
                    {
                        oam_exception_stat_report(uc_vap_idx, en_excp_idx, pst_excp_record[en_excp_idx].ul_record_cnt);
                        g_st_oam_mng_ctx.st_exception_ctx.ast_excp_record_tbl[en_excp_idx].en_status = OAM_EXCP_STATUS_INIT;
                    }
                }

                /* 已上报，置初始状态 */
                g_st_oam_mng_ctx.st_exception_ctx.en_status = OAM_EXCP_STATUS_INIT;
            }
        }
        break;

        default:
        break;
    }
#endif
}

oal_netbuf_stru* sdt_drv_netbuf_delist(oal_void)
{
    oal_uint                ui_irq_save;
    oal_netbuf_stru        *pst_netbuf;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    if (g_uloam_skbuff_list_len > 0)
    {
        g_uloam_skbuff_list_len--;
    }
    else
    {
        oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
        return NULL;
    }

    pst_netbuf = oal_netbuf_delist(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    return pst_netbuf;
}

void oam_printf_wpa(int level, char* pc_fmt, ...)
{
    if (level < MSG_DEBUG)
    {
        return;
    }
    oal_uint8* pst_pos;
    oal_netbuf_stru  *pst_netbuf;
    va_list                 pc_args;
    int frame_len_cnt = OAL_SIZEOF(OM_PRINTF_INTO_STRU);
    OM_PRINTF_INTO_STRU* om_printf_stru = NULL;
    om_printf_stru = (OM_PRINTF_INTO_STRU*)g_auc_oam_printf_log_buf;

    om_printf_stru->oam_printf_header.ucFrameStart     =    OM_FRAME_DELIMITER;
    om_printf_stru->oam_printf_header.ucFuncType                   = OAM_DATA_TYPE_ADAPTER_PRINTF;
    om_printf_stru->oam_printf_header.ucPrimeId                    = OM_WIFI;
    om_printf_stru->oam_printf_header.usFrameLen                   = frame_len_cnt;
    om_printf_stru->oam_printf_header.usSN                         = g_us_oam_sn++;

    memset(om_printf_stru->oam_printf_info.aucOam_printf_info, 0, OAM_PRINTF_LENGTH);
    va_start(pc_args, pc_fmt);
    vsnprintf(om_printf_stru->oam_printf_info.aucOam_printf_info, (OAM_PRINTF_LENGTH - 1), pc_fmt, pc_args);
    va_end(pc_args);
    om_printf_stru->oam_printf_info.ucFrameEnd = OM_FRAME_DELIMITER;
    pst_netbuf = oal_netbuf_alloc(frame_len_cnt, 0, 0);
    if (OAL_PTR_NULL== pst_netbuf)
    {
        OAM_WARNING_LOG0(0, 0, "oal_netbuf_alloc failed \r\n");
        return;
    }
    oal_netbuf_put(pst_netbuf, frame_len_cnt);
    pst_pos = (oal_uint8*)OAL_NETBUF_DATA(pst_netbuf);
    oal_memcopy(pst_pos, om_printf_stru, frame_len_cnt);
    sdt_drv_netbuf_add_to_list(pst_netbuf);
    LOS_EventWrite(&oam_event, oam_event_wait_bit0);
    return ;
}

oal_void oam_file_print(oal_int8* pc_file_name)
{
    FILE* p_file = NULL;
    oal_int32 l_file_size;
    oal_int32 l_rest_count;
    oal_int32 l_idx;
    oal_uint8 *pc_buf = NULL;
    oal_int32 l_read_num;
    oal_uint16 us_data_len = FILE_PRINT_DATA_LEN - FILE_FLAG_NUM * OAL_SIZEOF(oal_uint8);
    om_print_file_stru* pst_file_msg = NULL;

    p_file = fopen(pc_file_name, "r+");
    if (NULL == p_file)
    {
        return;
    }

    pc_buf = (oal_uint8*)oal_memalloc(us_data_len);
    if (NULL == pc_buf)
    {
        fclose(p_file);
        return;
    }

    pst_file_msg = (om_print_file_stru*)oal_memalloc(OAL_SIZEOF(om_print_file_stru));
    if (NULL == pst_file_msg)
    {
        free(pc_buf);
        fclose(p_file);
        return;
    }

    fseek(p_file, 0, SEEK_END);/* 将文件位置指示符定位到文件尾*/
    l_file_size = ftell(p_file);
    rewind(p_file);
    if (0 >= l_file_size)
    {
        free(pst_file_msg);
        free(pc_buf);
        fclose(p_file);
        return;
    }

    l_rest_count = l_file_size;
    pst_file_msg->st_file_header.ucFrameStart = OM_FRAME_DELIMITER;
    pst_file_msg->st_file_header.ucFuncType = OAM_DATA_TYPE_FILE;
    for (l_idx = 0; l_idx <= l_file_size / us_data_len; l_idx++)
    {
        l_read_num = fread(pc_buf, 1, us_data_len, p_file); /* 从文件流指定位置处读取一块us_data_len 长度数据*/
        if (0 >= l_read_num)
        {
            break;
        }
        l_rest_count -= l_read_num;
        if (0 != l_rest_count)
        {
            pst_file_msg->pucdata[0]= 0;  /* 0: 文件未读完 */
        }
        else
        {
            pst_file_msg->pucdata[0]= 1; /* 1: 文件读取完毕*/
        }
        oal_memcopy(&(pst_file_msg->pucdata[1]), pc_buf, l_read_num);
        pst_file_msg->st_file_header.usFrameLen = OM_FILE_HEADER_LEN + l_read_num
                                            + FILE_FLAG_NUM * OAL_SIZEOF(oal_uint8);
        ((oal_uint8*)pst_file_msg)[pst_file_msg->st_file_header.usFrameLen - 1] = OM_FRAME_DELIMITER;
        oam_dev_host_uart_print(pst_file_msg, (oal_uint16) pst_file_msg->st_file_header.usFrameLen);
    }

    free(pst_file_msg);
    free(pc_buf);
    fclose(p_file);
}

/*lint -e19*/
oal_module_symbol(OAL_PRINT2KERNEL);
oal_module_symbol(OAL_PRINT_NLOGS);
oal_module_symbol(oam_log_print0);
oal_module_symbol(oam_log_set_global_switch);
oal_module_symbol(oam_log_set_vap_switch);
oal_module_symbol(oam_log_set_vap_level);
oal_module_symbol(oam_log_set_feature_level);
oal_module_symbol(oam_log_console_printk);
oal_module_symbol(oam_log_set_ratelimit_param);
oal_module_symbol(oam_get_feature_id);
oal_module_symbol(oam_log_get_vap_level);
oal_module_symbol(oam_show_feature_list);

oal_module_symbol(oam_log_print1);
oal_module_symbol(oam_log_print2);
oal_module_symbol(oam_log_print3);
oal_module_symbol(oam_log_print4);
oal_module_symbol(oam_exception_record);
oal_module_symbol(oam_exception_stat_handler);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

