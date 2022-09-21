/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : user_ctrl.h
  Version    : first draft
  Author     : 
  Create date: 2015/04/08
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015/04/08
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

#ifndef __USER_CTRL_H__
#define __USER_CTRL_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "plat_type.h"
#include "hisi_customize_wifi.h"
#include "hisi_ini.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define HISI_UART_DEV_NAME_LEN      (32)

enum UART_DUMP_CTRL{
    UART_DUMP_CLOSE =0,
    UART_DUMP_OPEN=1,
};

enum BUG_ON_CTRL{
    BUG_ON_DISABLE = 0,
    BUG_ON_ENABLE  = 1,
};

struct ps_plat_s {
    struct platform_device *pm_pdev;
    atomic_t dbg_func_has_open;
    
    /* timeout for dbg read */
    #define DBG_READ_DEFAULT_TIME       (500)
    uint16 dbg_read_delay;
    
    int g_debug_cnt;
    
    
};

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/
extern struct kobject *g_sysfs_hi110x_bfgx;
extern int32 g_plat_loglevel;
extern int32 g_bug_on_enable;

#ifdef PLATFORM_DEBUG_ENABLE
extern int32 g_uart_rx_dump;
#endif

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern int32 user_ctrl_init(void);
extern void user_ctrl_exit(void);
#endif

