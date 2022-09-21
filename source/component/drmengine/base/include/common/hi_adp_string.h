/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_string.h
 * Description   : 字符串操作适配头文件
 *
 * History       :
 * Version     Date        Author      DefectNum    Modification:
 * 1.1         2009-2-27   q63946      NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_STRINT_H__
#define __HI_ADPT_STRINT_H__

#include "hi_type.h"
#include "hi_adp_interface.h"
#include <string.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * macro
 *----------------------------------------------*/

#if HI_OS_TYPE == HI_OS_LINUX
#elif HI_OS_TYPE == HI_OS_WIN32

    #define strcasecmp      _stricmp
    #define strncasecmp     _strnicmp
    #define strdup          _strdup
    #define atoll           _atoi64

#endif
//HI_SIZE_T strlen(const char *s);
/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/

/*将字符串转为全大写*/
HI_CHAR* HI_StrToUper(HI_CHAR *szSource);

/*转换nptr为int32 value*/
HI_S32 HI_StrToInt32(const HI_CHAR *nptr, HI_S32 *value);

/*合并多个字符串,最后一个参数必须为HI_NULL_PTR*/
HI_CHAR* HI_StrConcat (const HI_CHAR *string1, ...);

/*整数转换为字符串*/
HI_CHAR* HI_IntToStr(HI_S32 value, HI_CHAR* string);

/*整数转换为字符串,string 空间由外部提供*/
HI_CHAR* HI_Int64ToStr(HI_S64 value, HI_CHAR* string);

/*字符串转换为整数*/
HI_CHAR * HI_FloatToStr(HI_FLOAT floatValue, HI_CHAR *strValue);

/*----------------------------------------------*
 * 格式化字符串操作接口
 *----------------------------------------------*/

HI_S32 HI_Sprintf(HI_CHAR *str, const HI_CHAR *format, ...);

HI_S32 HI_Snprintf(HI_CHAR *str, HI_SIZE_T size, const HI_CHAR *format, ...);

HI_S32 HI_VSprintf(HI_CHAR *str, const HI_CHAR *format, HI_VA_LIST argList);

HI_S32 HI_VSnprintf(HI_CHAR *str, HI_SIZE_T size, const HI_CHAR *format, HI_VA_LIST argList);

/* Write formatted output to stdout. */
HI_S32  HI_Printf (const HI_CHAR *format, ...);

/* Read formatted input from stdin.*/
HI_S32 HI_Scanf (const HI_CHAR * format, ...);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ADPT_STRINT_H__ */
