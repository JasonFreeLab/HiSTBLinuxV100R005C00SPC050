/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_time.h
 * Description   : 时间适配头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_TIME_H__
#define __HI_ADPT_TIME_H__

#include "hi_type.h"
#include "hi_adp_interface.h"
#include <time.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define HI_ADPT_MCR_SYSTM2ADPTTM(stTmTime,stAdptTime)    \
do  \
{   \
    (stAdptTime).tm_sec  = (stTmTime).tm_sec        ; \
    (stAdptTime).tm_min  = (stTmTime).tm_min        ; \
    (stAdptTime).tm_hour = (stTmTime).tm_hour       ; \
    (stAdptTime).tm_mday = (stTmTime).tm_mday       ; \
    (stAdptTime).tm_mon  = (stTmTime).tm_mon        ; \
    (stAdptTime).tm_year = (stTmTime).tm_year       ; \
    (stAdptTime).tm_wday = (stTmTime).tm_wday       ; \
    (stAdptTime).tm_yday = (stTmTime).tm_yday       ; \
    (stAdptTime).tm_isdst= (stTmTime).tm_isdst      ; \
}   \
while(0)

#define HI_ADPT_MCR_ADPTTM2SYSTM(stAdptTime,stTmTime)    \
do  \
{   \
    (stTmTime).tm_sec  = (stAdptTime).tm_sec        ; \
    (stTmTime).tm_min  = (stAdptTime).tm_min        ; \
    (stTmTime).tm_hour = (stAdptTime).tm_hour       ; \
    (stTmTime).tm_mday = (stAdptTime).tm_mday       ; \
    (stTmTime).tm_mon  = (stAdptTime).tm_mon        ; \
    (stTmTime).tm_year = (stAdptTime).tm_year       ; \
    (stTmTime).tm_wday = (stAdptTime).tm_wday       ; \
    (stTmTime).tm_yday = (stAdptTime).tm_yday       ; \
    (stTmTime).tm_isdst= (stAdptTime).tm_isdst      ; \
}   \
while(0)

/*----------------------------------------------*
 * types
 *----------------------------------------------*/

typedef struct _HI_TM_S {
     HI_S32     tm_sec;         /*The  number of seconds after the minute,
                                  normally in the range 0 to 59, but can be up to
                                  60 to allow for leap seconds.*/
     HI_S32     tm_min;         /*The number of minutes after the hour, in the range 0 to 59.*/
     HI_S32     tm_hour;        /*The number of hours past midnight, in the range 0 to 23.*/
     HI_S32     tm_mday;        /*The day of the month, in the range 1 to 31.*/
     HI_S32     tm_mon;         /*The number of months since January, in the range 0 to 11.*/
     HI_S32     tm_year;        /*The number of years since 1900.*/
     HI_S32     tm_wday;        /*The number of days since Sunday, in the range 0 to 6.*/
     HI_S32     tm_yday;        /*The number of days since January 1, in the range 0 to 365.*/
     HI_S32     tm_isdst;       /*A flag that indicates whether daylight saving time is in effect at the  time  described.
                                  The value is positive if daylight saving time is in effect, zero if it is not, and nega-
                                  tive if the information is not available.*/
}HI_TM_S;

typedef struct HI_timeval
{
    HI_TIME_T tv_sec;           /* Seconds.  */
    HI_TIME_T tv_usec;          /* Microseconds.  */
}HI_TimeVal_S;

typedef struct HI_timespec
{
    HI_TIME_T tv_sec;           /* Seconds.  */
    HI_S32 tv_nsec;             /* Nanoseconds.  */
}HI_Timespec_S;

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/

/*将time_t timep 转换为tm*/
HI_S32 HI_LocalTime(const HI_TIME_T *ptTime,HI_TM_S *pstDateTime);

HI_SIZE_T HI_StrFtime(HI_CHAR*s, HI_SIZE_T max, const HI_CHAR *format,  const HI_TM_S *time);

HI_CHAR *HI_Ctime(const HI_TIME_T *ptime);

/*获取随机数*/
HI_U32 HI_Random(HI_VOID);

/*获取系统时间，自系统启动来的毫秒数*/
HI_U64 HI_GetSystemTime(HI_VOID);

/*获取系统时间，(00:00:00 UTC, January 1, 1970) 秒数*/
HI_U32 HI_GetSysTimeSec(HI_VOID);

 /*获取当前的系统时间，年，月日时分秒毫秒*/
HI_VOID HI_GetTime(HI_TM_S* curdate);

HI_BOOL HI_Stime(time_t* ptime);

HI_S32 HI_GmTime(const HI_TIME_T *tTime, HI_TM_S* pstAdptTm);

HI_TIME_T HI_Mktime(HI_TM_S* pstAdptTm);

/*获取从开机到现在的时间，毫秒*/
HI_U32 HI_GetTimeNow(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __HI_ADPT_TIME_H__ */
