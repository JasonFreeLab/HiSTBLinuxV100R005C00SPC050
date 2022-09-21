/******************************************************************************
Copyright (C), 2015-2025, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     : hi_time.h
Version       : Initial draft
Author        : HiSilicon DTV stack software group
Created Date  : 2015-08-24
Last Modified by: T00219055
Description   : Application programming interfaces (APIs) of Time module.
Function List :
Change History:
******************************************************************************/

#ifndef __HI_TIME_H__
#define __HI_TIME_H__

#include <stdio.h>
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      time */
/** @{ */  /** <!--[time]*/

/** Decode time BCD. */
#define HI_TIME_BCD_DEC(val) ((val>>4)*10 + (val&0xF))
/** Encode time BCD. */
#define HI_TIME_BCD_ENC(val) (((val/10)<<4) + (val%10))

/** Definition of week day index. */
/** CNcomment:星期一到星期天 */
typedef enum hiTIME_WEEK_DAY_E
{
    HI_TIME_WEEK_DAY_SUN = 0x0,
    HI_TIME_WEEK_DAY_MON,
    HI_TIME_WEEK_DAY_TUE,
    HI_TIME_WEEK_DAY_WED,
    HI_TIME_WEEK_DAY_THU,
    HI_TIME_WEEK_DAY_FRI,
    HI_TIME_WEEK_DAY_SAT,
    HI_TIME_WEEK_DAY_BUTT
} HI_TIME_WEEK_DAY_E;

/** Definition of time infomation struct. */
/** CNcomment:时间格式结构体 */
typedef struct hiTIME_INFO_S {
    HI_S32 s32Sec;  /**<The  number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.*/
    HI_S32 s32Min;  /**<The number of minutes after the hour, in the range 0 to 59.*/
    HI_S32 s32Hour; /**<The number of hours past midnight, in the range 0 to 23.*/
    HI_S32 s32Mday; /**<The day of the month, in the range 1 to 31.*/
    HI_S32 s32Mon;  /**<The number of months since January, in the range 1 to 12.*/
    HI_S32 s32Year; /**<The number of years since A.D. 0.,eg.2009*/
    HI_S32 s32Wday; /**<The number of days since Sunday, in the range 0 to 6.*/
    HI_S32 s32Yday; /**<The number of days since January 1, in the range 1 to 366.*/
} HI_TIME_INFO_S;

/** Definition of MJD and UTC format time. */
/** CNcomment:MJD和UTC时间 */
typedef struct hiTIME_MJDUTC_S
{
    HI_U16 u16MJD;  /**<UTC time of year/month/day in TOT table.*//**<CNcomment:TOT表中UTC时间高16bit，年/月/日 */
    HI_U32 u32UTC;  /**<UTC time of hour/minute/second in TOT table.*//**<CNcomment:TOT表中UTC时间低24bit，时/分/秒 */
} HI_TIME_MJDUTC_S;

/** Definition of MJD and UTC and duration format time. */
/** CNcomment:MJD和UTC时间，再加上持续时间 */
typedef struct hiTIME_MJDUTC_DURATION_S
{
    HI_TIME_MJDUTC_S             stTime;
    HI_U32                         u32Duration:24;
} HI_TIME_MJDUTC_DURATION_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      time */
/** @{ */  /** <!--[time]*/

/**
\brief time module init. CNcomment:初始化时间模块 CNend
\attention \n
N/A
\param[in] pVoid reserved. CNcomment:预留扩展用 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_Init(const HI_VOID *pVoid);

/**
\brief EPG module deinit. CNcomment:去初始化模块 CNend
\attention \n
N/A
\param[in] pVoid reserved. CNcomment:预留扩展用 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DeInit(const HI_VOID *pVoid);

/**
\brief Get time zone. CNcomment:获取时区 CNend
\attention \n
N/A
\param[out] ps32TimeZoneSeconds Time zone, unit is second. CNcomment:时区时间,单位:秒 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetTimeZone(HI_S32 *ps32TimeZoneSeconds);

/**
\brief Set time zone. CNcomment:设置时区 CNend
\attention \n
N/A
\param[in] s32TimeZoneSeconds Time zone, unit is second. CNcomment:时区时间,单位:秒 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeZone(HI_S32 s32TimeZoneSeconds);

/**
\brief Set daylight saving time. CNcomment:设置夏令时 CNend
\attention \n
N/A
\param[in] bEnable If turn on daylight saving time. CNcomment:是否启用夏令时, TRUE(+1小时) FALSE(+0小时) CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetDaylight(HI_BOOL bEnable);

/**
\brief Get offset of system time. CNcomment:获取偏移时间(时区 + 夏令时) CNend
\attention \n
N/A
\param[out] ps32OffsetSeconds Offset = timezone + daylight. CNcomment:偏移时间(秒) CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetOffset(HI_S32 *ps32OffsetSeconds);

/**
\brief Get system time. CNcomment:获取系统时间(秒) CNend
\attention \n
N/A
\param[out] ps32Seconds Seconds of time format. CNcomment:系统时间 CNend
\param[in] bWithOffset If include offset time. CNcomment:参数是否包含偏移时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetSeconds(HI_S32 *ps32Seconds, HI_BOOL bWithOffset);

/**
\brief Get date and time. CNcomment:获取系统日期时间(年月日时分秒形式) CNend
\attention \n
N/A
\param[out] pstTimeInfo Time. CNcomment:系统时间 CNend
\param[in] bWithOffset If include offset time. CNcomment:参数是否包含偏移时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetDateTime(HI_TIME_INFO_S *pstTimeInfo, HI_BOOL bWithOffset);

/**
\brief Set date and time. CNcomment:设置系统日期时间(年月日时分秒形式) CNend
\attention \n
N/A
\param[in] pstTimeInfo Time. CNcomment:系统时间 CNend
\param[in] bWithOffset If include offset time. CNcomment:参数是否包含偏移时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetDateTime(const HI_TIME_INFO_S *pstTimeInfo, HI_BOOL bWithOffset);

/**
\brief Set data time to operate system. CNcomment:通过HI_TIME_SetDateTime设置DTV时间时是否同时将时间设置到操作系统时钟去 CNend
\attention \n
N/A
\param[in] bEnable If set to system. CNcomment:是否设置, 本模块中该值默认为TRUE CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeToSystem(HI_BOOL bEnable);

/**
\brief Set data time to operate system. CNcomment:通过HI_TIME_SetDateTime设置DTV时间时是否同时将时区设置到操作系统时钟去 CNend
\attention \n
N/A
\param[in] bEnable If set to system. CNcomment:是否设置, 本模块中该值默认为TRUE CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeZoneToSystem(HI_BOOL bEnable);

/**
\brief Get date and time. CNcomment:获取系统日期时间(MJD+UTC格式) CNend
\attention \n
N/A
\param[out] pstMjdUtcTime Time. CNcomment:时间 CNend
\param[in] bWithOffset If include offset time. CNcomment:参数是否包含偏移时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetMJDUTCTime(HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_BOOL bWithOffset);

/**
\brief Compare two time structs. CNcomment:日期时间比较 CNend
\attention \n
N/A
\param[in] pstTimeInfo1 The first time struct. CNcomment:时间1 CNend
\param[in] pstTimeInfo2 The second time struct. CNcomment:时间2 CNend
\param[out] ps32Result Result, 0 is equal, positive is more than, negative is less than. CNcomment:比较结果,0,相等;>0,时间1>时间2的秒数;<0,时间1<时间2的秒数 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_CompareDateTime(const HI_TIME_INFO_S *pstTimeInfo1, const HI_TIME_INFO_S *pstTimeInfo2, HI_S32 *ps32Result);

/**
\brief Compare two time structs. CNcomment:日期时间比较(MJD+UTC形式) CNend
\attention \n
N/A
\param[in] pstTimeInfo1 The first time struct. CNcomment:时间1 CNend
\param[in] pstTimeInfo2 The second time struct. CNcomment:时间2 CNend
\param[out] ps32Result Result, 0 is equal, positive is more than, negative is less than. CNcomment:比较结果,0,相等;>0,时间1>时间2的秒数;<0,时间1<时间2的秒数 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_CompareMJDUTCTime(const HI_TIME_MJDUTC_S *pstTimeInfo1, const HI_TIME_MJDUTC_S *pstTimeInfo2, HI_S32 *ps32Result);

/**
\brief Transform date time format to second format. CNcomment:将时间转换为秒数(from 1970) CNend
\attention \n
N/A
\param[in] pstTimeInfo Date and time. CNcomment:待转换的时间 CNend
\param[out] ps32Seconds Seconds, from 1970.1.1 CNcomment:秒数，以1970年为0开始计算 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DateTimeToSeconds(const HI_TIME_INFO_S *pstTimeInfo, HI_S32 *ps32Seconds);

/**
\brief Transform second format to date time format. CNcomment:将秒数(from 1970)转换为年月日时分秒形式的时间 CNend
\attention \n
N/A
\param[in] s32Seconds Seconds, from 1970.1.1 CNcomment:秒数，以1970为0开始计算 CNend
\param[out] pstTimeInfo Date and time. CNcomment:输出年月日时分秒形式的时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToDateTime(HI_S32 s32Seconds, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform Y/M/D H/M/S format to MJD+BCD UTC format. CNcomment:将系统时间转换为MJD/UTC时间 CNend
\attention \n
N/A
\param[in] pstTimeInfo Y/M/D H/M/S format time. CNcomment:年月日时分秒形式的日期时间 CNend
\param[out] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC形式的日期时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DateTimeToMJDUTC(const HI_TIME_INFO_S *pstTimeInfo, HI_TIME_MJDUTC_S *pstMjdUtcTime);

/**
\brief Transform MJD+BCD UTC format to Y/M/D H/M/S format. CNcomment:MJD+BCDUTC形式时间转换成年月日时分秒形式的日期时间 CNend
\attention \n
N/A
\param[in] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC形式的时间 CNend
\param[out] pstTimeInfo Y/M/D H/M/S format time. CNcomment:年月日时分秒形式的日期时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDUTCToDateTime(const HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to second format. CNcomment:BCD UTC时间转换成秒(相对于00:00:00) CNend
\attention \n
N/A
\param[in] u32UTC BCD UTC format time. CNcomment:BCD形式的UTC时间 CNend
\param[out] ps32Seconds Seconds. CNcomment:秒数 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_BCDUTCToSeconds(HI_U32 u32UTC, HI_S32 *ps32Seconds);

/**
\brief Transform second format to BCD UTC format. CNcomment:秒转换成BCD UTC时间(相对于00:00:00) CNend
\attention \n
N/A
\param[in] s32Seconds Seconds. CNcomment:秒数 CNend
\param[out] pu32UTC BCD UTC format time. CNcomment:BCD形式的UTC时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToBCDUTC(HI_S32 s32Seconds, HI_U32 *pu32UTC);

/**
\brief Transform MJD+BCD UTC format to second format. CNcomment:MJD+BCD UTC形式时间转换成秒 CNend
\attention \n
N/A
\param[in] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC形式的时间 CNend
\param[out] ps32Seconds Seconds. CNcomment:秒 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDUTCToSeconds(const HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_S32 *ps32Seconds);

/**
\brief Transform second format to MJD/UTC format. CNcomment:将秒转换为MJD/UTC时间 CNend
\attention \n
N/A
\param[in] s32Seconds Seconds. CNcomment:秒 CNend
\param[out] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC形式的日期时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToMJDUTC(HI_S32 s32Seconds, HI_TIME_MJDUTC_S *pstMjdUtcTime);

/**
\brief Transform MJD date format to Y/M/D format. CNcomment:MJD日期转换成年月日形式的日期 CNend
\attention \n
N/A
\param[in] u32MJD MJD date format. CNcomment:MJD格式的年月日 CNend
\param[out] pstTimeInfo Y/M/D date format. CNcomment:年月日时分秒形式的日期时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDToYMD(HI_U32 u32MJD, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to H/M/S format. CNcomment:UTC时间转换成时分秒 CNend
\attention \n
N/A
\param[in] u32UTC BCD UTC format time. CNcomment:BCD形式的UTC时间 CNend
\param[out] pstTimeInfo H/M/S format. CNcomment:时分秒信息 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_BCDUTCToHMS(HI_U32 u32UTC, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to H/M/S format. CNcomment:时分秒转换成UTC时间 CNend
\attention \n
N/A
\param[in] pstTimeInfo H/M/S format. CNcomment:时分秒信息 CNend
\param[out] pu32UTC BCD UTC format time. CNcomment:BCD形式的UTC时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_HMSToBCDUTC(const HI_TIME_INFO_S *pstTimeInfo, HI_U32 *pu32UTC);

/**
\brief Add time with seconds. CNcomment:将指定时间偏移n秒 CNend
\attention \n
N/A
\param[in] pstTimeInfo Source date time. CNcomment:原始日期时间 CNend
\param[in] s32Seconds Offset seconds. CNcomment:偏移秒数 CNend
\param[out] pstTimeInfo Target date time. CNcomment:偏移后的日期时间 CNend
\retval ::HI_SUCCESS success CNcomment:成功 CNend
\retval ::HI_FAILURE fail    CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_TIME_AddSeconds(HI_TIME_INFO_S *pstTimeInfo, HI_S32 s32Seconds);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
 }
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_TIME_H__ */
