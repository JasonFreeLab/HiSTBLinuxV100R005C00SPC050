/******************************************************************************
Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_type.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : 系统共用的数据类型定义
Function List :
History       :
******************************************************************************/
#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define OUT
#define IN

/*----------------------------------------------*
 * 基本数据类型定义，应用层和内核代码均使用     *
 *----------------------------------------------*/

typedef unsigned char           HI_U8;
typedef unsigned char           HI_UCHAR;
typedef unsigned short          HI_U16;
typedef unsigned int            HI_U32;

typedef signed char                    HI_S8;
typedef short                   HI_S16;
typedef int                     HI_S32;

#ifndef _M_IX86
typedef unsigned long long      HI_U64;
typedef long long               HI_S64;
#else
typedef __int64                   HI_U64;
typedef __int64                   HI_S64;
#endif

typedef char                    HI_CHAR;
typedef char*                   HI_PCHAR;

typedef float                   HI_FLOAT;
typedef double                  HI_DOUBLE;
typedef void                    HI_VOID;

typedef unsigned long           HI_SIZE_T;
typedef unsigned long           HI_LENGTH_T;
typedef long                    HI_LONG;

typedef HI_U32                  HI_HANDLE;

#define HI_VOID void

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/
typedef enum {
    HI_FALSE    = 0,
    HI_TRUE     = 1
} HI_BOOL;

#ifndef NULL
#define NULL             0L
#endif
#define HI_NULL          0L
#define HI_NULL_PTR      0L

#define HI_SUCCESS          0
#define HI_FAILURE          (-1)



/*----------------------------------------------*
 * 基本数据类型定义，应用层和内核代码均使用     *
 *----------------------------------------------*/
//#define HI_OS_LINUX         0
//#define HI_OS_WIN32         1






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */
