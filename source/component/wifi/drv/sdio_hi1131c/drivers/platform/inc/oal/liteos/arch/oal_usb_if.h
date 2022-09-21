/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_usb_if.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年2月29日
  最近修改   :
  功能描述   : oal_usb_host.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年3月12日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_USB_IF_LITEOS_H__
#define __OAL_USB_IF_LITEOS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_thread.h"

#define HCC_HEADER_LENGTH   64
#define HCC_PAYLOAD_LENGTH  1536

#define HIUSB_HOST2DEV_SCATT_MAX       (64)
#define HIUSB_HOST2DEV_SCATT_SIZE      (64)
#define HIUSB_DEV2HOST_SCATT_MAX       (64)
#define HIUSB_BLOCK_SIZE                     512
#define HUSB_HOST2DEV_PKTS_MAX_LEN     (1544)


#define HIUSB_H2D_SCATT_BUFFLEN_ALIGN    (8)



enum {
    USB_READ = 0,
    USB_WRITE,
    USB_OPT_BUTT
};


typedef enum _HIUSB_D2H_MSG_TYPE_{
    USB_D2H_MSG_WLAN_READY = 0,
    USB_D2H_MSG_FLOWCTRL_UPDATE = 1,/*For the credit flow ctrl*/
    USB_D2H_MSG_FLOWCTRL_OFF =2,/*can't send data*/
    USB_D2H_MSG_FLOWCTRL_ON =3, /*can send data*/
    USB_D2H_MSG_WAKEUP_SUCC =4, /*Wakeup done*/
    USB_D2H_MSG_ALLOW_SLEEP =5, /*ALLOW Sleep*/
    USB_D2H_MSG_DISALLOW_SLEEP = 6, /*DISALLOW Sleep*/
    USB_D2H_MSG_DEVICE_PANIC =7, /*arm abort*/
    USB_D2H_MSG_POWEROFF_ACK = 8, /* Poweroff cmd ack*/
    USB_D2H_MSG_OPEN_BCPU_ACK = 9, /* OPEN BCPU cmd ack*/
    USB_D2H_MSG_CLOSE_BCPU_ACK = 10, /* CLOSE BCPU cmd ack*/
    USB_D2H_MSG_CREDIT_UPDATE = 11,  /* update high priority buffer credit value */
    USB_D2H_MSG_HIGH_PKT_LOSS = 12,  /* high pri pkts loss count */
#ifdef _PRE_WLAN_FEATURE_WOW
    USB_D2H_MSG_WOW_WIFI_REDAY = 15, /*Device ready for Host sleep*/
#endif
    USB_D2H_MSG_COUNT = 16 /*max support msg count*/
}HIUSB_D2H_MSG_TYPE;


extern oal_atomic g_wakeup_dev_wait_ack;


typedef oal_int32 (*usb_msg_rx)(oal_void* data);
typedef oal_int32 (*hiusb_rx)(oal_void* data);
typedef struct _usb_bus_ops_
{
    hiusb_rx rx;
}usb_bus_ops;


struct usb_msg_stru
{
    usb_msg_rx msg_rx;
    void* data;
    oal_uint32 count;
    oal_uint64 cpu_time;/*the time of the last come!*/
};



typedef struct _husb_tx_scatt_buff_
{
    /*record the tx scatt list assembled buffer*/
    oal_void* buff;
    oal_uint32 len;
}husb_tx_scatt_buff;


struct husb_credit_info{
    oal_uint8   short_free_cnt;
    oal_uint8   large_free_cnt;
    oal_spin_lock_stru credit_lock;
};

struct usb_scatt
{
    oal_uint32          max_scatt_num;
    struct eth_drv_sg  *sglist;
};



struct oal_usb
{
    /*sdio work state, sleep , work or shutdown?*/
    oal_uint32                  state;

    oal_spin_lock_stru          st_pm_state_lock;       //pm state互斥锁，pm和gpio中断都用到
    //wlan_pm_callback_stru      *pst_pm_callback;

    oal_spin_lock_stru          st_irq_lock;         //wlan gpio中断操作锁
    oal_uint                    ul_wlan_irq ;        //wlan gpio中断

    oal_wakelock_stru           st_sdio_wakelock;

#ifdef CONFIG_MMC
    struct sdio_func           *func;
#endif
    oal_mutex_stru             rx_transfer_lock;
    /*used to sg list sdio block align*/
    oal_uint8                  *sdio_align_buff;

    oal_uint64                  message_int_count;
    oal_uint64                  gpio_int_count;
    oal_uint64                  data_bulk_count;
    oal_uint64                  wakeup_int_count;
    oal_uint32                  ul_sdio_suspend;
    oal_uint32                  ul_sdio_resume;

    oal_kthread_stru         *gpio_rx_tsk;

    /*used to process the sdio int*/
    struct semaphore            gpio_rx_sema;


    oal_void*                   bus_data;
    usb_bus_ops                 bus_ops;
    hiusb_rx                    credit_update_cb;

#ifdef _PRE_FEATURE_USB
    struct eth_drv_sg          *usb_drv_rx_data;
    oal_int32                   usb_drv_rx_data_sg_num;
    struct eth_drv_sg          *usb_drv_sg_test;
    struct eth_drv_sg          *usb_drv_rx_message;
    oal_netbuf_head_stru       *usb_data_head;
    oal_completion              st_wait_finish_tx_data;
    oal_mutex_stru              tx_transfer_lock;
    oal_mutex_stru              usb_rx_transfer_lock;

    struct task_struct         *usb_rx_tsk;
    struct semaphore            usb_rx_sema;

    oal_wait_queue_head_stru      hcc_rx_thread_active_wq;
    oal_uint32                    hcc_rx_active_flag;
#endif

    struct usb_scatt      scatt_info[USB_OPT_BUTT];

    struct usb_msg_stru   msg[16];
    oal_uint32 last_msg;

    /*This is get from sdio , must alloc for dma,
      the extend area only can access by CMD53*/
    struct hisdio_extend_func   *sdio_extend;
    struct husb_credit_info     usb_credit_info;
    oal_uint32               func1_int_mask;
   // struct hsdio_func1_info  func1_stat;
   // struct hsdio_error_info  error_stat;

    husb_tx_scatt_buff scatt_buff;
    oal_void*       rx_reserved_buff;/*use the mem when rx alloc mem failed!*/
    oal_uint32      rx_reserved_buff_len;
#ifdef 
    oal_work_stru       usb_excp_worker;
#endif
    oal_uint32                    taskid;

    oal_int32           sdio_excp_type;
    oal_spin_lock_stru  sdio_excp_lock;

};



struct eth_drv_sg {
    unsigned int buf;   /* buffer的地址 */
    unsigned int len;   /* buffer中数据的长度 */
    struct eth_drv_sg* next;
};


typedef enum {
    USB_SEND_SUCCESS = 0,
    USB_SEND_FAILURE = -1
} USB_SEND_RESULT_T;


typedef struct _usb_rx_info_stru_
{
    oal_uint32                       ul_aggr_num;
    oal_uint32                       ul_free_buf_num;
    oal_uint32                       ul_reserve[2];
}usb_rx_info_stru;


/*
typedef struct _first_usb_rx_info_stru_
{
    usb_rx_info_stru   usb_rx_aggre;
    oal_uint8          usb_hcc_head[64];
    oal_uint8          payload[1500];

}first_usb_rx_info_stru;
*/



OAL_STATIC OAL_INLINE oal_void oal_usb_rx_transfer_lock(struct oal_usb *hi_usb)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    if(OAL_WARN_ON(NULL == hi_usb))
    {
        return;
    }
    mutex_lock(&hi_usb->rx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_usb_rx_transfer_unlock(struct oal_usb *hi_usb)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    if(OAL_WARN_ON(NULL == hi_usb))
    {
        return;
    }
    mutex_unlock(&hi_usb->rx_transfer_lock);
#endif
}



typedef void (*usb_int_send_cb)(int error);
typedef void (*usb_int_recv_cb)(struct eth_drv_sg *sg);


oal_uint32 oal_printf(char *descr,void *buf,oal_int32 len);

int wifi_usb_bulk_intr_read_event_read();
int wifi_usb_bulk_read_event_read ();

int get_wifi_event_type();
int wifi_usb_bulk_write_event_read();
int wifi_usb_intr_write_event_read();


oal_int32 oal_usb_msg_recv_process(struct eth_drv_sg *sg);
oal_void oal_usb_int_send_cb(int error);

oal_void oal_usb_bulk_send_cb(int error);
oal_int32 oal_usb_data_recv_process();

oal_netbuf_stru *oal_usb_alloc_rx_netbuf(oal_uint32 ul_len);

oal_int32 oal_usb_send_msg(struct oal_usb* hi_usb, oal_uint val);

struct oal_usb* oal_get_usb_default_handler(oal_void);

oal_int32 oal_set2usb_recv_buffer(struct oal_usb* hi_usb);

oal_int32 oal_usb_transfer_netbuf_list(struct oal_usb *hi_usb,
                                      oal_netbuf_head_stru * head,
                                      oal_int32 rw);

oal_netbuf_stru *oal_usb_alloc_rx_netbuf(oal_uint32 ul_len);

oal_int32 oal_usb_build_rx_netbuf_list(struct oal_usb *hi_sdio,
                                       oal_netbuf_head_stru   * head,
                                       oal_int32 reg_count,
                                       struct eth_drv_sg *usb_drv_sg_head);


oal_int32 oal_usb_send_msg(struct oal_usb* hi_usb, oal_uint val);

oal_int32 oal_alloc_first_recv_buf(struct eth_drv_sg *sg);
oal_int32 oal_clear_first_recv_buf(struct eth_drv_sg *sg);


oal_int32 set_next_recv_info_bulk(struct eth_drv_sg *sg, int num);

oal_int32 oal_usb_init(struct oal_usb* hi_usb);

struct oal_usb* oal_usb_init_module(oal_void* data);

oal_void  oal_usb_exit_module(struct oal_usb* hi_usb);

oal_int32 oal_usb_transfer_rx_register(struct oal_usb *hi_usb, hiusb_rx rx);

oal_void oal_usb_transfer_rx_unregister(struct oal_usb *hi_usb);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_sdio_if.h */

