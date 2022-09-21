/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : OMLCommon.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年1月7日
  最近修改   :
  功能描述   : OML的通用定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年1月7日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OMLCOMMON_H__
#define __OMLCOMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))


#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if 0
typedef unsigned    char        UINT8;
typedef unsigned    short       UINT16;
typedef unsigned    int         UINT32;
typedef unsigned long long      UINT64;

typedef char                    INT8;
typedef short                   INT16;
typedef int                     INT32;
typedef long long               INT64;
typedef int                     STATUS;
typedef unsigned int            size_t;


typedef signed char             oal_int8;           /* 数据前缀:c */
typedef signed short            oal_int16;          /* 数据前缀:s */
typedef signed int              oal_int32;          /* 数据前缀:l */
typedef signed long long        oal_int64;          /* 数据前缀:ll */
typedef unsigned char           oal_uint8;          /* 数据前缀:uc */
typedef unsigned short          oal_uint16;         /* 数据前缀:us */
typedef unsigned int            oal_uint32;         /* 数据前缀:ul */
typedef unsigned long long      oal_uint64;         /* 数据前缀:ull */
typedef void                    oal_void;

#endif

#define BIT_31                  ((UINT32)(1 << 31))
#define BIT_30                  ((UINT32)(1 << 30))
#define BIT_29                  ((UINT32)(1 << 29))
#define BIT_28                  ((UINT32)(1 << 28))
#define BIT_27                  ((UINT32)(1 << 27))
#define BIT_26                  ((UINT32)(1 << 26))
#define BIT_25                  ((UINT32)(1 << 25))
#define BIT_24                  ((UINT32)(1 << 24))
#define BIT_23                  ((UINT32)(1 << 23))
#define BIT_22                  ((UINT32)(1 << 22))
#define BIT_21                  ((UINT32)(1 << 21))
#define BIT_20                  ((UINT32)(1 << 20))
#define BIT_19                  ((UINT32)(1 << 19))
#define BIT_18                  ((UINT32)(1 << 18))
#define BIT_17                  ((UINT32)(1 << 17))
#define BIT_16                  ((UINT32)(1 << 16))
#define BIT_15                  ((UINT32)(1 << 15))
#define BIT_14                  ((UINT32)(1 << 14))
#define BIT_13                  ((UINT32)(1 << 13))
#define BIT_12                  ((UINT32)(1 << 12))
#define BIT_11                  ((UINT32)(1 << 11))
#define BIT_10                  ((UINT32)(1 << 10))
#define BIT_9                   ((UINT32)(1 << 9))
#define BIT_8                   ((UINT32)(1 << 8))
#define BIT_7                   ((UINT32)(1 << 7))
#define BIT_6                   ((UINT32)(1 << 6))
#define BIT_5                   ((UINT32)(1 << 5))
#define BIT_4                   ((UINT32)(1 << 4))
#define BIT_3                   ((UINT32)(1 << 3))
#define BIT_2                   ((UINT32)(1 << 2))
#define BIT_1                   ((UINT32)(1 << 1))
#define BIT_0                   ((UINT32)(1 << 0))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
//#include "itypes.h"
//#include "types.h"
#include "los_typedef.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OM_FRAME_DELIMITER                  0x7E
#define OM_FRAME_DELIMITER_LENGTH           1
#define OM_FRAME_HEADER_LEN                 8

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum OM_MSG_TYPE_ENUM
{
    OM_MSG_TYPE_LOG                 = 1,
    OM_MSG_TYPE_OTA                 = 2,
    OM_MSG_TYPE_TRACE               = 3,
    OM_MSG_TYPE_EVENT               = 4,
    OM_MSG_TYPE_ALARM               = 5,
    OM_MSG_TYPE_CATCH               = 6,
    OM_MSG_TYPE_COLLECT             = 7,
    OM_MSG_TYPE_DUMP                = 8,
    OM_MSG_MEM_COMMAND              = 9,
    //OM_MSG_REG_COMMAND              = 10,
    OM_MSG_ICONFIG_COMMAND          = 11,
    OM_MSG_HCI_COMMAND              = 12,
    OM_MSG_TYPE_WARNING             = 13,
    OM_MSG_TYPE_STATISTIC           = 15,
    OM_MSG_TYPE_LAST                = 16,
    OM_MSG_NFC_COMMAND              = 17,
    OM_MSG_TYPE_EDITION             = 18,
    OM_MSG_TYPE_COVERAGE            = 19,

    OM_MSG_GNSS_HOST_CMD_TYPE       = 20,   /* Add for GNSS, should modified later */
    OM_MSG_REG_COMMAND              = 21,
    OM_MSG_CS_STAT_CMD              = 22,
    OM_MSG_GNSS_SDT_CMD             = 23,
    OM_MSG_TRSSI_FSM                = 25,
    OM_MSG_TRSSI_VAL_CFG            = 26,
    OM_MSG_TYPE_CALIRESULT          = 27,
//    OM_MSG_SSIBLOCK_COMMAND         = 28,       /* Used by testfpga */
    OM_MSG_DBGUART_SWITCH_TO_BT     = 29,
    OM_MSG_DBGUART_SWITCH_TO_WIFI   = 30,

    OM_MSG_TYPE_STATUS              = 31,
    OM_MSG_TYPE_BUTT
};
typedef UINT8 OM_MSG_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern UINT16   g_usSN;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
#pragma pack(push,1)
typedef struct
{
   UINT8        ucFrameStart;
   UINT8        ucFuncType;
   UINT8        ucPrimeId;
   UINT8        aucReserver[1];
   UINT16       usFrameLen;
   UINT16       usSN;
}OM_MSG_HEADER_STRU;

typedef struct
{
    UINT8 aucOam_printf_info[OAM_PRINTF_LENGTH];
    UINT8 ucFrameEnd;
}oam_log_printf_info_stru;

typedef struct
{
    OM_MSG_HEADER_STRU oam_printf_header;
    oam_log_printf_info_stru   oam_printf_info;
}OM_PRINTF_INTO_STRU;
#pragma pack(pop)


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif /* end of OMLCommon.h */
