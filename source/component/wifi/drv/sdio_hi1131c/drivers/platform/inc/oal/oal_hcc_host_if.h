/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_hcc_if.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年10月20日
  最近修改   :
  功能描述   : oal_hcc_if.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月20日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_HCC_HOST_IF_H
#define __OAL_HCC_HOST_IF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "oal_util.h"
#include "oal_net.h"
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*add by  begin*/
#ifdef _PRE_FEATURE_USB
#include "arch/oal_usb_if.h"
#endif
/*add by  end*/
#endif
#include "oal_sdio_host_if.h"
#include "oal_hcc_comm.h"
#include "oal_workqueue.h"
#include "oal_thread.h"

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/kernel.h>
#endif

#ifdef _PRE_WLAN_TCP_OPT
#define TCP_ACK_WAIT_HCC_SCHDULE_COUNT (1)
#endif
#define CONFIG_CREDIT_MSG_FLOW_WATER_LINE   (60)

#define HCC_FLOW_HIGH_PRI_BUFF_CNT      5   /* device侧预留的高优先级专用buffer个数，要与OAL_NETBUF_HIGH_PRIORITY_COUNT相同 */

#define HCC_FLUSH_ALL   (~0UL)

/*hcc tx transfer flow control*/
#define HCC_FC_NONE         (0x0)   /*对调用者不进行流控，netbuf一直缓冲在hcc队列中,这种类型的数据包不宜过多*/
#define HCC_FC_WAIT         (0x1)   /*阻塞等待，如果是在中断上下文调用，该标记被自动清除,非中断上下文生效*/
#define HCC_FC_NET          (0x2)   /*对于网络层的流控*/
#define HCC_FC_DROP         (0x4)   /*流控采用丢包方式,流控时返回成功*/
#define HCC_FC_ALL          (HCC_FC_WAIT|HCC_FC_NET|HCC_FC_DROP)

struct hcc_transfer_param
{
    oal_uint32  main_type;
    oal_uint32  sub_type;
    oal_uint32  extend_len;
    oal_uint32  fc_flag;/*流控标记*/
    oal_uint32  queue_id;/*期望进入的队列号,*/
};

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL

#define LO_QUEUE_ADJUST_PRIORITY_PERIOD     (4)    /* 周期性抬高 LO QUEUE 的间隔 */

typedef enum _hcc_queue_type_
{
    CTRL_QUEUE = 0,
    DATA_HI_QUEUE,
    DATA_LO_QUEUE,

    DATA_TCP_DATA_QUEUE,
    DATA_TCP_ACK_QUEUE,

    DATA_UDP_BK_QUEUE,
    DATA_UDP_BE_QUEUE,
    DATA_UDP_VI_QUEUE,
    DATA_UDP_VO_QUEUE,

    HCC_QUEUE_COUNT
} hcc_queue_type;

#else

typedef enum _hcc_queue_type_
{
    DATA_HI_QUEUE = 0,
    DATA_LO_QUEUE =1,
    HCC_QUEUE_COUNT
} hcc_queue_type;

#endif
#if 0
#define HCC_TX_PARAM_INITIALIZER(name,mtype,stype,ext_len,arg_flag,queueid) \
        do{\
            name.main_type = mtype;\
            name.sub_type =  stype;\
            name.extend_len = ext_len;\
            name.fc_flag = arg_flag;\
            name.queue_id = queueid;\
        }while(0)

/*default*/
#define DECLARE_HCC_TX_PARAM_DEFAULT(name)					\
	        struct hcc_transfer_param name = {\
            .fc_flag = HCC_FC_NONE,\
            .queue_id = DATA_LO_QUEUE,\
        }
#endif

#define DECLARE_HCC_TX_PARAM_INITIALIZER(name,mtype,stype,ext_len,arg_flag,queueid)					\
	        struct hcc_transfer_param name;\
			hcc_hdr_param_init(&name,mtype,stype,ext_len,arg_flag,queueid);

/*the macro to set hcc hdr*/
OAL_STATIC OAL_INLINE oal_void  hcc_hdr_param_init(struct hcc_transfer_param* param,
                                                        oal_uint32 main_type,
                                                        oal_uint32 sub_type,
                                                        oal_uint32 extend_len,
                                                        oal_uint32 fc_flag,
                                                        oal_uint32 queue_id)
{
    //OAL_BUG_ON(main_type >= HCC_ACTION_TYPE_BUTT);
    //OAL_WARN_ON(extend_len > HCC_HDR_RESERVED_MAX_LEN);
    param->main_type = main_type;
    param->sub_type = sub_type;
    param->extend_len = extend_len;
    param->fc_flag = fc_flag;
    param->queue_id = queue_id;
}

typedef enum _hcc_chan_type_
{
    HCC_TX,
    HCC_RX,
    HCC_DIR_COUNT
} hcc_chan_type;
#define HCC_GET_CHAN_STRING(type) ((HCC_TX==(type))?"tx":"rx")

typedef enum _hcc_send_mode_
{
    hcc_single_send  = 0,
    hcc_assem_send,
    hcc_mode_count
} hcc_send_mode;

typedef enum _hcc_flowctrl_type_
{
    HCC_FLOWCTRL_SDIO,
    HCC_FLOWCTRL_CREDIT,
    HCC_FLOWCTRL_BUTT
}hcc_flowctrl_type;

typedef struct _hcc_flow_ctrl_
{
    oal_uint8                       flowctrl_flag;
    oal_uint8                       enable;
    oal_uint16                      flow_type;
    oal_uint16                      is_stopped;
    oal_uint16                      low_waterline;
    oal_uint16                      high_waterline;
} hcc_flow_ctrl;

typedef struct _hcc_trans_queue_
{
    /*transfer pkts limit every loop*/
    oal_uint32                  netbuf_pool_type;
    oal_uint32                  burst_limit;
    hcc_flow_ctrl               flow_ctrl;
    hcc_send_mode               send_mode;
    oal_uint32                  total_pkts;
    oal_uint32                  loss_pkts;
    oal_netbuf_head_stru        data_queue;
    oal_spin_lock_stru          data_queue_lock;
    wlan_net_queue_type         wlan_queue_id;
} hcc_trans_queue;

#define HCC_TX_ASSEM_INFO_MAX_NUM  (HISDIO_HOST2DEV_SCATT_MAX + 1)
#define HCC_RX_ASSEM_INFO_MAX_NUM    (HISDIO_DEV2HOST_SCATT_MAX + 1)
typedef struct _hcc_tx_assem_info_{
    /*The +1 for the single pkt*/
    oal_uint32                       info[HCC_TX_ASSEM_INFO_MAX_NUM];

    /*The max support assemble pkts*/
    oal_uint32                      assemble_max_count;
    /*next assem pkts count*/
    /*oal_uint32                      assembled_cnt;*/
    /*netx assem pkts list*/
    oal_netbuf_head_stru            assembled_head;
    /*the queue is assembling*/
    hcc_queue_type                  assembled_queue_type;

} hcc_tx_assem_info;

typedef struct _hcc_rx_assem_info_{
    oal_uint32                       info[HCC_RX_ASSEM_INFO_MAX_NUM];
} hcc_rx_assem_info;

typedef struct _hcc_netbuf_stru_
{
    oal_netbuf_stru* pst_netbuf;
    oal_int32        len;/*for hcc transfer*/
}hcc_netbuf_stru;

typedef oal_int32 (* hcc_rx_pre_do)(oal_uint8 stype, hcc_netbuf_stru* pst_netbuf, oal_uint8 **pre_do_context);
typedef oal_int32 (* hcc_rx_post_do)(oal_uint8 stype, hcc_netbuf_stru* pst_netbuf, oal_uint8 *pre_do_context);

typedef struct _hcc_rx_action_
{
    oal_uint32          pkts_count;
    hcc_rx_pre_do       pre_do;
    hcc_rx_post_do      post_do;
    oal_void            *context;/*the callback argument*/
}hcc_rx_action;

typedef struct _hcc_rx_action_info_{
    hcc_rx_action          action[HCC_ACTION_TYPE_BUTT];
} hcc_rx_action_info;

typedef struct _hcc_trans_queues_
{
    hcc_trans_queue              queues[HCC_QUEUE_COUNT];
} hcc_trans_queues;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
typedef oal_bool_enum_uint8 (*hcc_flowctl_get_mode)(oal_void);
oal_void hcc_flowctl_get_device_mode_register(hcc_flowctl_get_mode get_mode);

typedef oal_void (*hcc_flowctl_start_subq)(oal_uint16 us_queue_idx);
typedef oal_void (*hcc_flowctl_stop_subq)(oal_uint16 us_queue_idx);
oal_void hcc_flowctl_operate_subq_register(hcc_flowctl_start_subq start_subq, hcc_flowctl_stop_subq stop_subq);
oal_void   hcc_host_set_flowctl_param(oal_uint8 uc_queue_type, oal_uint16 us_burst_limit, oal_uint16 us_low_waterline, oal_uint16 us_high_waterline);
oal_void   hcc_host_get_flowctl_stat(oal_void);
#endif

typedef oal_void (*flowctrl_cb)(oal_void);

typedef struct _hcc_tx_flow_ctrl_info_
{
    oal_uint32 flowctrl_flag;
    oal_uint32 flowctrl_on_count;
    oal_uint32 flowctrl_off_count;
    oal_uint32 flowctrl_reset_count;
    oal_uint32 flowctrl_hipri_update_count;
    oal_uint8  uc_hipriority_cnt;
    oal_uint8  auc_resv[3];
    oal_spin_lock_stru  st_hipri_lock;  /* 读写uc_hipriority_cnt时要加锁 */
    oal_wait_queue_head_stru   wait_queue;
    flowctrl_cb net_stopall;
    flowctrl_cb net_startall;
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    hcc_flowctl_get_mode    get_mode;
    hcc_flowctl_stop_subq   stop_subq;
    hcc_flowctl_start_subq  start_subq;
#endif
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_uint16               flow_timer;
#else
    oal_timer_list_stru      flow_timer;
#endif
    oal_ulong             timeout;
    oal_delayed_work  worker;
    oal_spin_lock_stru lock;
}hcc_tx_flow_ctrl_info;

typedef struct _hcc_thread_stat_
{
    oal_uint64  wait_event_block_count;
    oal_uint64  wait_event_run_count;
    oal_uint64  loop_have_data_count;
    oal_uint64  loop_no_data_count;/*空转*/
}hcc_thread_stat;

struct hcc_transfer_handler
{
    oal_kthread_stru            *hcc_transfer_thread;
    oal_wait_queue_head_stru    hcc_transfer_wq;
#ifdef _PRE_CONFIG_WLAN_THRANS_THREAD_DEBUG
    hcc_thread_stat             thread_stat;
#endif
    hcc_trans_queues            hcc_queues[HCC_DIR_COUNT];
    hcc_tx_assem_info           tx_assem_info;
    hcc_rx_assem_info           rx_assem_info;
    hcc_tx_flow_ctrl_info       tx_flow_ctrl;
    hcc_rx_action_info          rx_action_info;
#if(_PRE_OS_VERSION==_PRE_OS_VERSION_LITEOS)
    oal_uint32                    taskid;
#endif

};

typedef oal_int32 (*hcc_rx_cb)(oal_netbuf_stru* netbuf,
                                    struct hcc_header * hdr,
                                    oal_void* data);

struct hcc_tx_assem_descr{
    oal_uint8                   descr_num;
    oal_netbuf_head_stru        tx_assem_descr_hdr;
};
typedef oal_void (*hcc_sched_transfer_func)(oal_void);
typedef oal_int32 (*hmac_tcp_ack_process_func)(oal_void);
typedef oal_bool_enum_uint8 (*hmac_tcp_ack_need_schedule_func)(oal_void);

#define HCC_OFF     (0)
#define HCC_ON      (1)
#define HCC_EXCEPTION (2)

struct hcc_handler
{
    oal_atomic                  state;/*hcc's state*/
    oal_atomic                  tx_seq;
#ifdef _PRE_FEATURE_USB
    oal_void*                   hi_usb;
#else
    oal_void*                   hi_sdio;
#endif
    oal_uint                    hdr_rever_max_len;

    oal_mutex_stru              tx_transfer_lock;
    oal_wakelock_stru           tx_wake_lock;

    struct hcc_transfer_handler hcc_transer_info;

    /*the tx descr info, first descr*/
    struct hcc_tx_assem_descr   tx_descr_info;
    hmac_tcp_ack_process_func p_hmac_tcp_ack_process_func;
    hmac_tcp_ack_need_schedule_func p_hmac_tcp_ack_need_schedule_func;
};

typedef oal_void (*hcc_tx_cb_callback)(struct hcc_handler* hcc);

#define HCC_TX_WAKELOCK_MAGIC   0xdead5ead
struct hcc_tx_cb_stru
{
    hcc_tx_cb_callback destory;
    oal_uint32  magic;
};

#define HCC_TC_TX_PKT_FLAG  (0x5A)
#define HCC_TC_RX_PKT_FLAG  (0xA5)
#define HCC_TC_TX_TCM_FLAG  (0xEF)
#define HCC_TC_RX_TCM_FLAG  (0xFE)

typedef sdio_msg_rx hcc_msg_rx;

oal_int32 hcc_tx(struct hcc_handler* hcc, oal_netbuf_stru* netbuf, struct hcc_transfer_param* param);
#ifdef _PRE_WLAN_TCP_OPT
oal_int32 hcc_thread_process(struct hcc_handler *hcc);
oal_int32 hcc_transfer_thread(oal_void *data);
#endif
#ifndef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
oal_void hcc_tx_flow_ctrl_cb_register(flowctrl_cb stopall, flowctrl_cb startall);
#endif

struct hcc_handler* hcc_module_init(oal_void);

extern oal_void hcc_change_state_exception(oal_void);

oal_void hcc_tx_assem_info_reset(struct hcc_handler *hcc);
oal_void hcc_rx_assem_info_reset(struct hcc_handler *hcc);
oal_void hcc_assem_info_reset(struct hcc_handler* hcc);

oal_void hcc_module_exit(struct hcc_handler*);


oal_int32 hcc_message_register(struct hcc_handler* hcc, oal_uint8 msg,
                                    hcc_msg_rx cb, oal_void* data);

oal_void hcc_clear_all_queues(struct hcc_handler * hcc, oal_int32 is_need_lock);
oal_void hcc_enable(struct hcc_handler * hcc, oal_int32 is_need_lock);
oal_void hcc_disable(struct hcc_handler * hcc, oal_int32 is_need_lock);

/*获取默认的HCC通道句柄*/
extern struct hcc_handler* hcc_get_default_handler(oal_void);
extern oal_void hcc_dev_flowctrl_on(struct hcc_handler *hcc, oal_uint8 need_notify_dev);
extern oal_void hcc_dev_flowctrl_off(struct hcc_handler *hcc);

/*自动调频处理函数，在hcc的收发线程中调用*/
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
typedef oal_void (*hmac_auto_freq_count_func)(oal_uint32 ul_pkt_cout);
typedef oal_uint32 (*hmac_auto_freq_process_func)(oal_void);
typedef oal_uint8 (*hmac_auto_freq_set_lock_mod)(oal_uint8 uc_freq_enable);
typedef oal_void (*hmac_auto_freq_adjust_to_level_func)(oal_void);
struct alg_process_func_handler
{
    hmac_auto_freq_count_func p_auto_freq_count_func;
    hmac_auto_freq_process_func p_auto_freq_process_func;
    hmac_auto_freq_set_lock_mod p_auto_freq_set_lock_mod_func;
    hmac_auto_freq_adjust_to_level_func p_auto_freq_adjust_to_level_func;
};
extern struct alg_process_func_handler* oal_get_alg_process_func(oal_void);
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
typedef oal_uint32 (*custom_cali_func)(oal_void);
struct custom_process_func_handler
{
    custom_cali_func p_custom_cali_func;
};
extern struct custom_process_func_handler* oal_get_custom_process_func(oal_void);

#endif

OAL_STATIC OAL_INLINE void hcc_tx_transfer_lock(struct hcc_handler *hcc)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_mutex_lock(&hcc->tx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE void hcc_tx_transfer_unlock(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_mutex_unlock(&hcc->tx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE void hcc_rx_transfer_lock(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
/*add by  begin*/
#ifdef _PRE_FEATURE_USB
   oal_usb_rx_transfer_lock((struct oal_usb *)hcc->hi_usb);
#else
    oal_sdio_rx_transfer_lock((struct oal_sdio *)hcc->hi_sdio);
#endif
}

OAL_STATIC OAL_INLINE void hcc_rx_transfer_unlock(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
/*add by  begin*/
#ifdef _PRE_FEATURE_USB
    oal_usb_rx_transfer_unlock((struct oal_usb *)hcc->hi_usb);
#else
    oal_sdio_rx_transfer_unlock((struct oal_sdio *)hcc->hi_sdio);
#endif

}

OAL_STATIC OAL_INLINE void hcc_transfer_lock(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
    
    hcc_rx_transfer_lock(hcc);
    
    hcc_tx_transfer_lock(hcc);
}

OAL_STATIC OAL_INLINE void hcc_transfer_unlock(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
    hcc_tx_transfer_unlock(hcc);
    hcc_rx_transfer_unlock(hcc);
}

OAL_STATIC OAL_INLINE oal_void hcc_sched_transfer(struct hcc_handler *hcc)
{
    if(OAL_WARN_ON(NULL == hcc))
    {
        OAL_IO_PRINT("%s,hcc is null\n",__FUNCTION__);
        return;
    }
    /*OAL_IO_PRINT("sched hcc transfer\n");*/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    wake_up_interruptible(&hcc->hcc_transer_info.hcc_transfer_wq);
#endif
}
extern oal_void hcc_set_tcpack_cnt(oal_uint32 ul_val);
extern oal_int32 hcc_rx_register(struct hcc_handler *hcc, oal_uint8 mtype, hcc_rx_post_do post_do, hcc_rx_pre_do pre_do);
extern oal_int32 hcc_rx_unregister(struct hcc_handler *hcc, oal_uint8 mtype);
extern oal_void hcc_tx_wlan_queue_map_set(struct hcc_handler* hcc,hcc_queue_type hcc_queue_id,wlan_net_queue_type wlan_queue_id);

extern oal_void hi_wlan_power_set(oal_int32 on);

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
extern oal_int32  hcc_test_init_module(struct hcc_handler* hcc);
extern oal_void  hcc_test_exit_module(struct hcc_handler* hcc);
#else
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
extern oal_int32  hcc_test_init_module(struct hcc_handler* hcc);
extern oal_void  hcc_test_exit_module(struct hcc_handler* hcc);
#else
/*function stub*/
OAL_STATIC OAL_INLINE oal_int32  hcc_test_init_module(struct hcc_handler* hcc)
{
    OAL_REFERENCE(hcc);
    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_void  hcc_test_exit_module(struct hcc_handler* hcc)
{
    OAL_REFERENCE(hcc);
    return;
}
#endif
#endif

extern oal_void hcc_print_device_mem_info(oal_void);
extern oal_void hcc_trigger_device_panic(oal_void);

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
extern struct alg_process_func_handler g_pst_alg_process_func;
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
extern struct custom_process_func_handler g_pst_custom_process_func;
#endif


#define HCC_NETBUF_RESERVED_ROOM_SIZE   (HCC_HDR_TOTAL_LEN+HISDIO_H2D_SCATT_BUFFLEN_ALIGN)
/*****************************************************************************
 函 数 名  : hcc_netbuf_alloc
 功能描述  : reserved the fixed headroom and tailroom for hcc transfer!
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
#define hcc_netbuf_alloc(ul_size)   oal_netbuf_alloc(ul_size + HCC_NETBUF_RESERVED_ROOM_SIZE,HCC_NETBUF_RESERVED_ROOM_SIZE,0)

OAL_STATIC OAL_INLINE oal_void hcc_tx_netbuf_free(oal_netbuf_stru* pst_netbuf)
{
    struct hcc_tx_cb_stru* pst_cb_stru;

    OAL_BUG_ON(NULL == pst_netbuf);

    pst_cb_stru = (struct hcc_tx_cb_stru*)OAL_NETBUF_CB(pst_netbuf);

    if(OAL_UNLIKELY(HCC_TX_WAKELOCK_MAGIC != pst_cb_stru->magic))
    {
#ifdef CONFIG_PRINTK
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

        printk(KERN_EMERG "BUG: tx netbuf:%p on CPU#%d,magic:%08x should be %08x\n", pst_cb_stru,
                    raw_smp_processor_id(),pst_cb_stru->magic,HCC_TX_WAKELOCK_MAGIC);
        print_hex_dump(KERN_ERR, "tx_netbuf_magic", DUMP_PREFIX_ADDRESS, 16, 1,
       (oal_uint8 *)pst_netbuf, sizeof(oal_netbuf_stru), true);
        printk(KERN_ERR"\n");
#endif
#endif
        OAL_WARN_ON(1);
        DECLARE_DFT_TRACE_KEY_INFO("tx_wakelock_crash", OAL_DFT_TRACE_EXCEP);
        return;
    }

    if(OAL_LIKELY(pst_cb_stru->destory))
    {
        pst_cb_stru->destory(hcc_get_default_handler());
    }

    pst_cb_stru->magic = 0x0;

    oal_netbuf_free(pst_netbuf);
}
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
static inline oal_uint64 div_u64_rem(oal_uint64 dividend, oal_uint32 divisor, oal_uint32*remainder)
{
    *remainder = dividend % divisor;
    return dividend / divisor;
}

static inline oal_uint64 div_u64(oal_uint64 dividend, oal_uint32 divisor)
{
    oal_uint32 remainder;
    return div_u64_rem(dividend, divisor, &remainder);
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_hcc_if.h */
