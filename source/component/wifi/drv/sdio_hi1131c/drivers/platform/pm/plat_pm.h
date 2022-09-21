/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : plat_pm.h
  Version    : first draft
  Author     : 
  Create date: 2012-12-10
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015-04-10
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

#ifndef __PLAT_PM_H__
#define __PLAT_PM_H__

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/

#include "plat_pm_wlan.h"
#include "board.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
/*#define ENABLE_BFG_LOWPOWER_FEATURE*/

#define FIRMWARE_CFG_INIT_OK            0x01

#define SUCCESS                         (0)
#define FAILURE                         (1)

#define HOST_DISALLOW_TO_SLEEP          (0)
#define HOST_ALLOW_TO_SLEEP             (1)

#define WAIT_DEVACK_MSEC               (100)
#define WAIT_DEVACK_TIMEOUT_MSEC       (200)

#define WAIT_WKUPDEV_MSEC              (3400)

#define SDIO_REINIT_RETRY              (5)


enum WIFI_POWER_ON_EXCEPTION_ENUM
{
    WIFI_POWER_FAIL                                 = -1,
    WIFI_POWER_SUCCESS                              = 0,
    WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL                = 1,
    WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL      = 2,

    WIFI_POWER_ENUM_BUTT,
};

typedef enum {
    POWER_STATE_SHUTDOWN = 0,
    POWER_STATE_OPEN     = 1,
    POWER_STATE_BUTT     = 2,
}power_state_enum;


/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*private data for pm driver*/
struct pm_drv_data
{
    /*wlan interface pointer*/
    struct wlan_pm_s                *pst_wlan_pm_info;

	/* board customize info */
	BOARD_INFO						*board;

    /*mutex for sync*/
    oal_mutex_stru                    host_mutex;

    /*Tasklet to respond to change in hostwake line */
    oal_tasklet_stru           hostwake_task;

    /* workqueue for wkup device */
    struct workqueue_struct *wkup_dev_workqueue;
    struct work_struct wkup_dev_work;
    struct work_struct send_disallow_msg_work;

    /* wait device ack timer */
    struct timer_list bfg_timer;
    struct timer_list dev_ack_timer;

    /* the completion for waiting for host wake up device ok */
    oal_completion host_wkup_dev_comp;
    /* the completion for waiting for dev ack(host allow sleep) ok */
    oal_completion dev_ack_comp;
    /* the completion for waiting for dev boot ok */
    oal_completion dev_bootok_ack_comp;
};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 host_wkup_dev(void);
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 wlan_is_shutdown(void);
extern int32 wlan_power_on(void);
extern int32 wlan_power_off(void);
extern int32 sdio_reinit(void);
extern int firmware_download_function(uint32 which_cfg);
extern oal_int32 hi110x_get_wifi_power_stat(oal_void);
extern int32 device_mem_check(unsigned long long *time);

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/wakelock.h>

#include "plat_pm_wlan.h"
#include "board.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
/*#define ENABLE_BFG_LOWPOWER_FEATURE*/
#define BFG_LOCK_NAME                   "bfg_wake_lock"

#define FIRMWARE_CFG_INIT_OK            0x01

#define SUCCESS                         (0)
#define FAILURE                         (1)

#define GNSS_AGREE_SLEEP                (1)
#define GNSS_NOT_AGREE_SLEEP            (0)

#define BFGX_SLEEP                      (0)
#define BFGX_ACTIVE                     (1)

#define UART_READY                      (1)
#define UART_NOT_READY                  (0)

#define BFGX_PM_ENABLE                  (1)
#define BFGX_PM_DISABLE                 (0)

#define WAIT_DEVACK_MSEC               (100)
#define WAIT_DEVACK_TIMEOUT_MSEC       (200)

#define WAIT_WKUPDEV_MSEC              (3400)

#define PM_SUSPEND_PREPARE	0x0003 /* Going to suspend the system */
#define PM_POST_SUSPEND		0x0004 /* Suspend finished */
#define MMC_PM_KEEP_POWER	(1 << 0)	/* preserve card power during suspend */

enum WLAN_DEV_STATUS_ENUM
{
    HOST_DISALLOW_TO_SLEEP = 0,
    HOST_ALLOW_TO_SLEEP = 1,
    DEV_SHUTDOWN = 2,
};

/* BFGX系统上电加载异常类型 */
enum BFGX_POWER_ON_EXCEPTION_ENUM
{
    BFGX_POWER_FAILED                               = -1,
    BFGX_POWER_SUCCESS                              = 0,

    BFGX_POWER_PULL_POWER_GPIO_FAIL                 = 1,
    BFGX_POWER_TTY_OPEN_FAIL                        = 2,
    BFGX_POWER_TTY_FLOW_ENABLE_FAIL                 = 3,

    BFGX_POWER_WIFI_DERESET_BCPU_FAIL               = 4,
    BFGX_POWER_WIFI_ON_BOOT_UP_FAIL                 = 5,

    BFGX_POWER_WIFI_OFF_BOOT_UP_FAIL                = 6,
    BFGX_POWER_DOWNLOAD_FIRMWARE_FAIL               = 7,

    BFGX_POWER_WAKEUP_FAIL                          = 8,
    BFGX_POWER_OPEN_CMD_FAIL                        = 9,

    BFGX_POWER_ENUM_BUTT,
};

/* wifi系统上电加载异常类型 */
enum WIFI_POWER_ON_EXCEPTION_ENUM
{
    WIFI_POWER_FAIL                                 = -1,
    WIFI_POWER_SUCCESS                              = 0,
    WIFI_POWER_PULL_POWER_GPIO_FAIL                 = 1,

    WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL                = 2,
    WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL      = 3,

    WIFI_POWER_BFGX_ON_BOOT_UP_FAIL                 = 4,
    WIFI_POWER_BFGX_DERESET_WCPU_FAIL               = 5,
    WIFI_POWER_BFGX_ON_FIRMWARE_DOWNLOAD_FAIL       = 6,

    WIFI_POWER_ENUM_BUTT,
};

typedef enum {
    POWER_STATE_SHUTDOWN = 0,
    POWER_STATE_OPEN     = 1,
    POWER_STATE_BUTT     = 2,
}power_state_enum;

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
#define ASYNCB_SUSPENDED	30 /* Serial port is suspended */
struct mutex {
	/* 1: unlocked, 0: locked, negative: locked, possible waiters */
	atomic_t		count;
	spinlock_t		wait_lock;
	struct list_head	wait_list;
#if defined(CONFIG_DEBUG_MUTEXES) || defined(CONFIG_SMP)
	struct task_struct	*owner;
#endif
#ifdef CONFIG_MUTEX_SPIN_ON_OWNER
	void			*spin_mlock;	/* Spinner MCS lock */
#endif
#ifdef CONFIG_DEBUG_MUTEXES
	const char 		*name;
	void			*magic;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif
#ifdef CONFIG_ILOCKDEP
	struct ilockdep_map idep_map;
#endif
};

struct tasklet_struct
{
	struct tasklet_struct *next;
	unsigned long state;
	atomic_t count;
	void (*func)(unsigned long);
	unsigned long data;
};


/*private data for pm driver*/
struct pm_drv_data
{
    /*3 in 1 interface pointer*/
    struct ps_pm_s                  *ps_pm_interface;

    /*wlan interface pointer*/
    struct wlan_pm_s                *pst_wlan_pm_info;

	/* board customize info */
	BOARD_INFO						*board;

    /*wake lock for bfg,be used to prevent host form suspend*/
    struct wake_lock                bfg_wake_lock;

    /*mutex for sync*/
    struct mutex                    host_mutex;

    /*Tasklet to respond to change in hostwake line */
    struct tasklet_struct           hostwake_task;

    /*bfgx VS. bfg timer spinlock */
    spinlock_t                      node_timer_spinlock;

    /* uart could be used or not */
    uint8   uart_ready;

    /* mark receiving data after set dev as sleep state but before get ack of device */
    uint8 rcvdata_bef_devack_flag;


    /*bfgx sleep state*/
    uint8 bfgx_dev_state;

    /*flag for firmware cfg file init*/
    uint64 firmware_cfg_init_flag;

    /*bfg irq num*/
    uint32 bfg_irq;

    /*bfg wakeup host count*/
    uint32 bfg_wakeup_host;

    /* gnss lowpower state */
    atomic_t gnss_sleep_flag;

    atomic_t bfg_needwait_devboot_flag;

    /* flag to mark whether enable lowpower or not */
    uint32 bfgx_pm_ctrl_enable;
    uint8  bfgx_lowpower_enable;
    uint8  bfgx_bt_lowpower_enable;
    uint8  bfgx_gnss_lowpower_enable;
    uint8  bfgx_nfc_lowpower_enable;

    /* workqueue for wkup device */
    struct workqueue_struct *wkup_dev_workqueue;
    struct work_struct wkup_dev_work;
    struct work_struct send_disallow_msg_work;

    /* wait device ack timer */
    struct timer_list bfg_timer;
    struct timer_list dev_ack_timer;

    /* the completion for waiting for host wake up device ok */
    struct completion host_wkup_dev_comp;
    /* the completion for waiting for dev ack(host allow sleep) ok */
    struct completion dev_ack_comp;
    /* the completion for waiting for dev boot ok */
    struct completion dev_bootok_ack_comp;
};

typedef	int (*notifier_fn_t)(struct notifier_block *nb,
			unsigned long action, void *data);

struct notifier_block {
	notifier_fn_t notifier_call;
	struct notifier_block *next;
	int priority;
};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/
extern unsigned int g_ul_wlan_resume_state;    
/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 host_wkup_dev(void);
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 bfgx_other_subsys_all_shutdown(uint8 subsys);
extern int32 wlan_is_shutdown(void);
extern int32 bfgx_is_shutdown(void);
extern int32 wlan_power_on(void);
extern int32 wlan_power_off(void);
extern int32 bfgx_power_on(uint8 subsys);
extern int32 bfgx_power_off(uint8 subsys);
extern int32 bfgx_pm_feature_set(void);
extern int firmware_download_function(uint32 which_cfg);
extern oal_int32 hi110x_get_wifi_power_stat(oal_void);
extern int32 device_mem_check(unsigned long long *time);
static void pm_set_drvdata(struct pm_drv_data * data);

#endif

#endif

