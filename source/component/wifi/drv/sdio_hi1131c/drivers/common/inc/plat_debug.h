/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : plat_debug.h
  Version    : first draft
  Author     : 
  Create date: 2012-10-11
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015-04-25
    Author   : 
    Modify
    content  : Create File

******************************************************************************/
#ifndef __PLAT_DEBUG_H__
#define __PLAT_DEBUG_H__

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#include "plat_type.h"
#endif

#include "chr_user.h"

enum PLAT_LOGLEVLE{
    PLAT_LOG_ALERT = 0,
    PLAT_LOG_ERR = 1,
    PLAT_LOG_WARNING = 2,
    PLAT_LOG_INFO = 3,
    PLAT_LOG_DEBUG = 4,
};
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define KBUILD_MODNAME "1131 for compile" /*´ò×®*/
enum BUG_ON_CTRL{
    BUG_ON_DISABLE = 0,
    BUG_ON_ENABLE  = 1,
};

static int32 g_plat_loglevel = PLAT_LOG_DEBUG;
static int32 g_bug_on_enable = BUG_ON_DISABLE;

#define PS_PRINT_FUNCTION_NAME              do { \
        if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
        { \
            printf("[%s]" ,__func__);     \
        } \
    }while(0)

#define PS_PRINT_DBG(s, args...)            do{ \
        if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_DEBUG, CHR_LOG_TAG_PLAT, s, ##args); \
        }\
    }while(0)

#define PS_PRINT_INFO(s, args...)           do{ \
        if (PLAT_LOG_INFO <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args);\
            CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_SUC(s, args...)            do{ \
        if (PLAT_LOG_INFO <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_WARNING(s, args...)        do{ \
        if (PLAT_LOG_WARNING <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args);\
            CHR_LOG(CHR_LOG_WARN, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_ERR(s, args...)            do{ \
        if (PLAT_LOG_ERR <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_ALERT(s, args...)          do{ \
        if (PLAT_LOG_ALERT <= g_plat_loglevel) \
        { \
            printf("[%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_BUG_ON(s)                       do{ \
        if((BUG_ON_ENABLE == g_bug_on_enable)) \
        { \
           BUG_ON(s);\
        } \
    }while(0)
#elif (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern int g_plat_loglevel;

/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define PS_PRINT_FUNCTION_NAME              do { \
        if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
        { \
            printk(KERN_DEBUG KBUILD_MODNAME ":D]%s]" ,__func__);     \
        } \
    }while(0)

#define PS_PRINT_DBG(s, args...)            do{ \
        if (PLAT_LOG_DEBUG <= g_plat_loglevel) \
        { \
            printk(KERN_DEBUG KBUILD_MODNAME ":D]%s]" s,__func__, ## args); \
        }\
    }while(0)

#define PS_PRINT_INFO(s, args...)           do{ \
        if (PLAT_LOG_INFO <= g_plat_loglevel) \
        { \
            printk(KERN_DEBUG KBUILD_MODNAME ":I]%s]" s,__func__, ## args);\
            CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_SUC(s, args...)            do{ \
        if (PLAT_LOG_INFO <= g_plat_loglevel) \
        { \
            printk(KERN_DEBUG KBUILD_MODNAME ":S]%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_INFO, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_WARNING(s, args...)        do{ \
        if (PLAT_LOG_WARNING <= g_plat_loglevel) \
        { \
            printk(KERN_WARNING KBUILD_MODNAME ":W]%s]" s,__func__, ## args);\
            CHR_LOG(CHR_LOG_WARN, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_ERR(s, args...)            do{ \
        if (PLAT_LOG_ERR <= g_plat_loglevel) \
        { \
            printk(KERN_ERR KBUILD_MODNAME ":E]%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_PRINT_ALERT(s, args...)          do{ \
        if (PLAT_LOG_ALERT <= g_plat_loglevel) \
        { \
            printk(KERN_ALERT KBUILD_MODNAME ":ALERT]%s]" s,__func__, ## args); \
            CHR_LOG(CHR_LOG_ERROR, CHR_LOG_TAG_PLAT, s, ##args); \
        } \
    }while(0)

#define PS_BUG_ON(s)                       do{ \
        if((BUG_ON_ENABLE == g_bug_on_enable)) \
        { \
           BUG_ON(s);\
        } \
    }while(0)
#endif

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/

#endif /* PLAT_DEBUG_H */


