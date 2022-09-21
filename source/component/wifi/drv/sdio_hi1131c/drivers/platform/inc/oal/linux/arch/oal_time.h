/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_time.h
  版 本 号   : 初稿
  作    者   : ds
  生成日期   : 2016年7月27日
  最近修改   :
  功能描述   : oal_time.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年7月27日
    作    者   : ds
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_TIME_H__
#define __OAL_LINUX_TIME_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/rtc.h>

#include <oal_types.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (_PRE_CHIP_BITS_MIPS32 == _PRE_CHIP_BITS)
/* 32位寄存器最大长度 */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFF - 1)

#elif (_PRE_CHIP_BITS_MIPS64 == _PRE_CHIP_BITS)
/* 64位寄存器最大长度 */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFFFFFFFFFF - 1)

#endif


/* 获取毫秒级时间戳*/
#define OAL_TIME_GET_STAMP_MS() jiffies_to_msecs(jiffies)

/* 获取高精度毫秒时间戳,精度1ms*/
#define OAL_TIME_GET_HIGH_PRECISION_MS()  oal_get_time_stamp_from_timeval()

#define OAL_ENABLE_CYCLE_COUNT()
#define OAL_DISABLE_CYCLE_COUNT()
#define OAL_GET_CYCLE_COUNT() 0

/* 寄存器反转模块运行时间计算 */
#define OAL_TIME_CALC_RUNTIME(_ul_start, _ul_end)   ((((OAL_TIME_US_MAX_LEN) / HZ) * 1000) + ((OAL_TIME_US_MAX_LEN) % HZ) * (1000 / HZ) - (_ul_start) + (_ul_end))

#define OAL_TIME_JIFFY    jiffies

#define OAL_TIME_HZ       HZ

#define OAL_MSECS_TO_JIFFIES(_msecs)    msecs_to_jiffies(_msecs)

#define OAL_JIFFIES_TO_MSECS(_jiffies)      jiffies_to_msecs(_jiffies)

/* 获取从_ul_start到_ul_end的时间差 */
#define OAL_TIME_GET_RUNTIME(_ul_start, _ul_end) \
    (((_ul_start) > (_ul_end))?(OAL_TIME_CALC_RUNTIME((_ul_start), (_ul_end))):((_ul_end) - (_ul_start)))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
typedef struct
{
    oal_int i_sec;
    oal_int i_usec;
}oal_time_us_stru;

typedef ktime_t oal_time_t_stru;
typedef struct timeval oal_timeval_stru;
typedef struct rtc_time oal_rtctime_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : oal_time_get_stamp_us
 功能描述  : 获取微妙精度级的时间戳
 输入参数  : pst_usec: 时间结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_time_get_stamp_us(oal_time_us_stru *pst_usec)
{
    struct timespec ts;

    getnstimeofday(&ts);

    pst_usec->i_sec     = ts.tv_sec;

    pst_usec->i_usec    = ts.tv_nsec /1000;

}

/*****************************************************************************
 函 数 名  : oal_ktime_get
 功能描述  : 调用内核函数获取当前时间戳
 输入参数  : oal_void
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_get(oal_void)
{
    return ktime_get();
}

/*****************************************************************************
 函 数 名  : oal_ktime_sub
 功能描述  : 调用内核函数获取时间差值
 输入参数  : const oal_time_t_stru lhs,
             const oal_time_t_stru rhs
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_time_t_stru oal_ktime_sub(const oal_time_t_stru lhs, const oal_time_t_stru rhs)
{
    return ktime_sub(lhs, rhs);
}


/*****************************************************************************
 函 数 名  : oal_get_time_stamp_from_timeval
 功能描述  : 获取时间精度
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint64 oal_get_time_stamp_from_timeval(oal_void)
{
    struct timeval tv;
    oal_uint64 curr_time;

    do_gettimeofday(&tv);
    curr_time = tv.tv_usec;
    do_div(curr_time, 1000);
    curr_time = curr_time + tv.tv_sec * 1000;

    return curr_time;

}

OAL_STATIC OAL_INLINE oal_void oal_do_gettimeofday(oal_timeval_stru *tv)
{
    do_gettimeofday(tv);
}
OAL_STATIC OAL_INLINE oal_void oal_rtc_time_to_tm(oal_ulong time, oal_rtctime_stru *tm)
{
    rtc_time_to_tm(time, tm);
}

/*****************************************************************************
 函 数 名  : oal_time_is_before
 功能描述  : 判断ul_time是否比当前时间早
             若早，表示超时时间已过；若不早，表明还未超时
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : OAL_STATIC OAL_INLINE oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日,星期二
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_is_before(oal_uint ui_time)
{
    return (oal_uint32)time_is_before_jiffies(ui_time);
}

/*****************************************************************************
 函 数 名  : oal_time_after
 功能描述  : 判断时间戳ul_time_a是否在ul_time_b之后:
 输入参数  : oal_uint ui_time
 输出参数  : 无
 返 回 值  : Return: 1 ul_time_a在ul_time_b之后; 否则 Return: 0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_time_after(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return (oal_uint32)time_after((oal_ulong)ul_time_a, (oal_ulong)ul_time_b);
}

OAL_STATIC OAL_INLINE oal_ulong oal_ktime_to_us(const oal_time_t_stru kt)
{
    return ktime_to_us(kt);
}

OAL_STATIC OAL_INLINE oal_uint32 oal_time_before_eq(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return time_before_eq((oal_ulong)ul_time_a, (oal_ulong)ul_time_b);
}

OAL_STATIC OAL_INLINE oal_uint32 oal_time_before(oal_uint32 ul_time_a, oal_uint32 ul_time_b)
{
    return time_before((oal_ulong)ul_time_a, (oal_ulong)ul_time_b);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_time.h */
