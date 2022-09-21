/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : exception_rst.h
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

#ifndef __EXCEPTION_RST_H__
#define __EXCEPTION_RST_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "plat_type.h"
#include "oal_types.h"
#include "oal_spinlock.h"
#include "oal_workqueue.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define WIFI_DUMP_TIMEOUT          (1000)   /*wifi dump bcpu数据等待时间*/
    
#define PLAT_EXCEPTION_RESET_IDLE  (0)      /* plat 没有在处理异常*/
#define PLAT_EXCEPTION_RESET_BUSY  (1)      /* plat 正在处理异常*/
    
#define EXCEPTION_SUCCESS          (0)
#define EXCEPTION_FAIL             (1)
    
#define SDIO_STORE_WIFI_MEM        "readm_wifi_sdio"

/*plat cfg cmd */
#define PLAT_CFG_IOC_MAGIC                     'z'
#define PLAT_DFR_CFG_CMD                       _IOW(PLAT_CFG_IOC_MAGIC, PLAT_DFR_CFG, int)
#define PLAT_BEATTIMER_TIMEOUT_RESET_CFG_CMD   _IOW(PLAT_CFG_IOC_MAGIC, PLAT_BEATTIMER_TIMEOUT_RESET_CFG, int)

#define PLAT_EXCEPTION_ENABLE                  (1)
#define PLAT_EXCEPTION_DISABLE                 (0)

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
    
enum EXCEPTION_TYPE_ENUM
{
    DEVICE_PANIC      =0,/*arm exception*/
    TRANS_FAIL        =1,/*read or write failed*/

    EXCEPTION_TYPE_BUTT,
};

struct st_wifi_dump_mem_info
{
    ulong  mem_addr;
    uint32 size;
    uint8  *file_name;
};
typedef struct st_wifi_dump_mem_info * p_st_wifi_demp_mem_info;


struct st_exception_info
{
    uint32   exception_reset_enable;
    uint32   excetion_type;
        
    struct workqueue_struct *plat_exception_rst_workqueue;
    //struct completion wait_sdio_d2h_dump_ack;

    uint32 wifi_exception_cnt;

    /*when recv error data from device, dump device mem*/
    #define NOT_DUMP_MEM        (0)
    uint32  dump_mem_flag;

    oal_work_stru       excp_worker;
    oal_spin_lock_stru  excp_lock;

    void (*wifi_dfr_func)(void);
};

#if 0
struct sdio_dump_bcpu_buff
{
    uint8 *mem_addr;
    uint32 data_limit;
    uint32 data_len;
};

typedef struct DUMP_MEM_RES
{
    uint8 *file_name;
    uint32 start_addr;
    uint32 align_type;
    uint32 men_len;
}exception_bcpu_dump_msg;

enum dump_msg_align_type
{
    ALIGN_1_BYTE    = 0,
    ALIGN_2_BYTE    = 1,
    ALIGN_4_BYTE    = 2,
};
#endif

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/
extern p_st_wifi_demp_mem_info g_apst_panic_dump_mem[];
extern p_st_wifi_demp_mem_info g_apst_trans_fail_dump_mem[];

/*****************************************************************************
  5 全局变量定义
*****************************************************************************/
enum PLAT_CFG
{
    PLAT_DFR_CFG                           = 0,
    PLAT_BEATTIMER_TIMEOUT_RESET_CFG,
    PLAT_TRIGGER_EXCEPTION,
    PLAT_POWER_RESET,
    PLAT_CHANNEL_DISABLE,
    
    PLAT_CFG_BUFF,
};

/*****************************************************************************
  6 EXTERN FUNCTION
*****************************************************************************/
extern void  plat_dfr_cfg_set(uint64 arg);
extern int32 get_exception_info_reference(struct st_exception_info **exception_data);
extern int32 plat_exception_handler(uint32 exception_type);
extern int32 wifi_exception_mem_dump(p_st_wifi_demp_mem_info * pst_mem_dump_info);
extern int32 plat_exception_reset_init(void);
extern int32 plat_exception_reset_exit(void);
extern int32 wifi_system_reset(void);
extern void  oal_exception_submit(int32 excep_type);
extern int32 oal_device_panic_callback(void *data);
extern int32 oal_trigger_exception(int32 is_sync);
extern int32 oal_exception_is_busy(void);
extern void  oal_try_to_dump_device_mem(int32 is_sync);


#endif

