/*
 *
 * Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : oal_usb_host.c
 * Version       : Initial Draft
 * Author        : 
 * Created       : 2016/3/12
 * Last Modified :
 * Description   : usb driver for hisilicon connectivity device
 * Function List :
 * History       :
 * 1.Date        : 2016/3/12
 *   Author      : 
 *   Modification: Created file
 *
 */
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifdef _PRE_FEATURE_USB

#include "los_event.h"



#define  HISI_LOG_TAG "[USB]"
#include "oal_usb_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_USB_HOST_C


#define TYPE_MSG_DATA   0x00000001
#define TYPE_BULK_DATA  0x00000010
#define USB_TASK_SIZE   0x2000
#define USB_TASK_PRIO   10

//OAL_STATIC first_usb_rx_info_stru  *g_usb_first_sg;

struct     eth_drv_sg                   *g_drv_sg_message;
OAL_STATIC oal_int32                    g_usb_message;
struct     oal_usb                      *_hi_usb_;
oal_semaphore_stru                    chan_wake_sema;


oal_int32 hiusb_intr_mode = 0;  /* 0 -usb 1-gpio*/
oal_uint32 g_ul_pm_wakeup_event = OAL_FALSE;

oal_atomic g_wakeup_dev_wait_ack;

oal_uint64 oal_get_gpio_int_count_para(oal_void)
{
    struct oal_usb *  hi_usb;

    hi_usb = oal_get_usb_default_handler();

    return hi_usb->gpio_int_count;
}

oal_uint32 oal_printf(char *descr,void *buf,oal_int32 len)
{

}

oal_uint32 oal_printf_sglist(struct eth_drv_sg *sg_list, unsigned int sg_num)
{

}



struct eth_drv_sg* oal_alloc_scatt_buff(oal_uint32 max_scatt_num);


struct oal_usb* oal_get_usb_default_handler(oal_void)
{
    return _hi_usb_;
}


oal_int32 oal_usb_bulk_send(struct eth_drv_sg *sg_list, unsigned int sg_num)
{

    return usb_bulk_send(sg_list, sg_num);
}



oal_uint32 oal_data_tx_wait_send_finish(struct oal_usb *hi_usb)
{
    OAL_IO_PRINT("oal_data_tx_wait_send_finish");
    oal_uint64 begain;

    begain=tickcount_get();
    //printf("oal_data_tx_wait_send_finish begain time =%lld",begain);
   return oal_wait_for_completion_timeout(&hi_usb->st_wait_finish_tx_data, (oal_uint32)OAL_MSECS_TO_JIFFIES(35000));
  // return oal_wait_for_completion(&hi_usb->st_wait_finish_tx_data);
}

struct eth_drv_sg *sg_list_tail;
struct eth_drv_sg *sg_list_tail_tmp;

oal_int32 oal_usb_transfer_netbuf_list(struct oal_usb *hi_usb,
                                      oal_netbuf_head_stru * head,
                                      oal_int32 rw)
{
    oal_uint8          sg_realloc = 0;
    oal_int32          ret = OAL_SUCC;
    oal_int32          idx = 0;
    oal_uint32         queue_len;
    oal_uint32         sum_len = 0;
    oal_uint32         request_sg_len;
    oal_netbuf_stru   *tmp_buff = NULL;

    struct eth_drv_sg *sg;
    struct eth_drv_sg *sg_head;
    struct eth_drv_sg *sg_tmp;

    struct eth_drv_sg *sg_test;

    mutex_lock(&hi_usb->tx_transfer_lock);


    if((NULL == hi_usb) || (NULL == head))
    {
        printf("hi_usb or head is null\n");
        mutex_unlock(&hi_usb->tx_transfer_lock);
        return -OAL_FAIL;
    }

    queue_len = oal_netbuf_list_len(head);

    if(!queue_len)
    {
        printf("queue_len is 0\n");
        mutex_unlock(&hi_usb->tx_transfer_lock);
        return -OAL_FAIL;

    }
    /*must realloc the sg list mem, alloc more sg for the align buff*/
    request_sg_len = queue_len + 1;

    if(request_sg_len > hi_usb->scatt_info[rw].max_scatt_num)
    {
        OAL_IO_PRINT("transfer_netbuf_list realloc sg!, request:%d,max scatt num:%d\n",
                        request_sg_len,hi_usb->scatt_info[rw].max_scatt_num);
        /*must realloc the sg list mem, alloc more sgs for the align buff*/
        sg_tmp = oal_alloc_scatt_buff(request_sg_len);
        sg_realloc = 1;
        sg = sg_tmp;
    }
    else
    {
        sg = hi_usb->scatt_info[rw].sglist;
    }
    /*point the head of the scatter buffer*/

    ret = oal_memset_scatt_buff(sg);
    if(OAL_SUCC != ret)
    {
        printf("fail to memset scatt buffer\n");
         mutex_unlock(&hi_usb->tx_transfer_lock);
        return -OAL_FAIL;
    }

    sg_head  = sg;
    tmp_buff = head->next;
    sg->buf = (oal_int32)(void*)OAL_NETBUF_DATA(tmp_buff);
    sg->len = 64;

    tmp_buff = tmp_buff->next;

    if(tmp_buff != NULL)
    {
       for(tmp_buff; tmp_buff != head;tmp_buff = tmp_buff->next)
       {
            OAL_IO_PRINT("eloop,idx:%d\n",idx++);

            sg  = sg->next;
            sg->buf = (oal_int32)(void *)OAL_NETBUF_DATA(tmp_buff);
            sg->len = 64;

            sg = sg->next;
            sg->buf = (oal_int32)(void *)OAL_NETBUF_DATA(tmp_buff) +64;
            sg->len = OAL_NETBUF_LEN(tmp_buff)-64;
        }
    }
    sg_list_tail=sg;
    sg_list_tail_tmp=sg->next;
    sg->next=NULL;




    ret = oal_usb_bulk_send(sg_head,2*queue_len-1);
    if(ret)
    {
        printf("send data fail rw:%d\n", rw);
         mutex_unlock(&hi_usb->tx_transfer_lock);
        return -OAL_FAIL;
    }

    ret =  wifi_usb_bulk_write_event_read();

    if ( OS_ERRNO_EVENT_READ_TIMEOUT == ret) {
        printf(" wifi_usb_bulk_write_event_read,time out\n");
        return OAL_FAIL;
    }

    sg_list_tail->next = sg_list_tail_tmp;



    if(sg_realloc)
    {
        oal_free(sg_tmp);
    }

    mutex_unlock(&hi_usb->tx_transfer_lock);

    return ret;
}


oal_void oal_usb_bulk_send_cb(int error)
{
    sg_list_tail->next = sg_list_tail_tmp;

    //printf("##########sg_list_tail=%x\n",sg_list_tail);
    //printf("##########sg_list_tail_tmp=%x\n",sg_list_tail_tmp);
#if 0
    struct eth_drv_sg *sg_test;
    sg_test=sg_list_tail_tmp;
    int loop_test=0;
    while(sg_test)
    {
        sg_test=sg_test->next;
        loop_test++;
    }
#endif
    //printf("#######oal_usb_bulk_send_cb loop_test=%d\n",loop_test);


    OAL_COMPLETE(&(_hi_usb_->st_wait_finish_tx_data));
    //printf("oal_usb_bulk_send_cb:send finish,the result is :%d",error);
}


oal_void oal_usb_int_send_cb(int error)
{
    OAL_IO_PRINT("oal_usb_int_send_cb: send finish,the result is :%d",error);
}





oal_netbuf_stru *oal_usb_alloc_rx_netbuf(oal_uint32 ul_len)
{

/*   Hi1131C bug fix  / begin */
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    return dev_alloc_skb(ul_len);
#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#ifdef _PRE_LWIP_ZERO_COPY

    oal_netbuf_stru *pst_sk_buff = OAL_PTR_NULL;
    oal_lwip_buf    *pst_lwip_buf = OAL_PTR_NULL;

    pst_lwip_buf = pbuf_alloc(PBUF_RAW, ul_len, PBUF_RAM);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_lwip_buf))
    {
        return OAL_PTR_NULL;
    }

    /*
    |---PBUF_STRU---|-------HEADROOM-------|------ul_len-------|----TAILROOM-----|
    |    16BYTE     |         64BYTE       |      ul_len       |      32BYTE     |
    p_mem_head      head                   data/tail                             end
    */
    pst_sk_buff = (oal_netbuf_stru *)oal_memalloc(SKB_DATA_ALIGN(OAL_SIZEOF(oal_netbuf_stru)));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_sk_buff))
    {
        pbuf_free(pst_lwip_buf);
        return OAL_PTR_NULL;
    }

    OAL_MEMZERO(pst_sk_buff, OAL_SIZEOF(oal_netbuf_stru));
    oal_atomic_set(&pst_sk_buff->users, 1);

    pst_sk_buff->p_mem_head = (oal_uint8 *)pst_lwip_buf;
    pst_sk_buff->head       = pst_sk_buff->p_mem_head + LWIP_PBUF_STRUCT_SIZE;
    pst_sk_buff->data       = pst_sk_buff->head + PBUF_NETDEV_HEADROOM_RESERVE;
    skb_reset_tail_pointer(pst_sk_buff);
    pst_sk_buff->end        = pst_sk_buff->tail + ul_len + PBUF_NETDEV_TAILROOM_RESERVE;

    return pst_sk_buff;
#else
    return dev_alloc_skb(ul_len);
#endif
#endif
/*   Hi1131C bug fix  / end */
}

struct eth_drv_sg *sg_list_recv_tail;
struct eth_drv_sg *sg_list_recv_tail_next;


oal_int32 oal_usb_build_rx_netbuf_list(struct oal_usb *hi_sdio,
                                                oal_netbuf_head_stru  *head,
                                                oal_int32 reg_count,
                                                struct eth_drv_sg *usb_drv_sg_head)
{

    oal_int32          i;
    oal_int32          ret = OAL_SUCC;
    oal_uint32         sum_len = 0;
    oal_netbuf_stru   *netbuf = NULL;
    struct eth_drv_sg *sg_head;
    struct eth_drv_sg *sg_head_tmp;

    OAL_BUG_ON(!oal_netbuf_list_empty(head));

    sg_head = usb_drv_sg_head;

    for(i = 0; i< 2*reg_count-1; i++)
    {
        sg_head=sg_head->next;
    }


    sg_list_recv_tail      = sg_head;

    sg_list_recv_tail_next = sg_head->next;

    sg_head ->next= NULL;



    sg_head = usb_drv_sg_head;

    for(i = 0; i < reg_count; i++)
    {
        netbuf = oal_usb_alloc_rx_netbuf(HCC_HEADER_LENGTH+HCC_PAYLOAD_LENGTH);
        if(NULL == netbuf)
        {
            DECLARE_DFT_TRACE_KEY_INFO("sdio_rx_no_mem", OAL_DFT_TRACE_OTHER);
            goto failed_netbuf_alloc;
        }

        oal_netbuf_put(netbuf,(HCC_HEADER_LENGTH+HCC_PAYLOAD_LENGTH));
        sum_len += (HCC_HEADER_LENGTH+HCC_PAYLOAD_LENGTH);
        __skb_queue_tail(head, netbuf);

       if((NULL != sg_head) && (NULL != sg_head->next))
       {
           sg_head->buf = netbuf->data;
           sg_head->len = HCC_HEADER_LENGTH;

           sg_head->next->buf = netbuf->data + HCC_HEADER_LENGTH;
           sg_head->next->len = HCC_PAYLOAD_LENGTH;
           sg_head = sg_head->next->next;
       }

    }

    if(OAL_TRUE == oal_netbuf_list_empty(head))
    {

        OAL_IO_PRINT("oal_netbuf_list_empty(head) is empty\n");
        return -OAL_EINVAL;
    }

    return OAL_SUCC;

failed_netbuf_alloc:
    skb_queue_purge(head);

    skb_queue_purge(usb_drv_sg_head);


    return -OAL_ENOMEM;

}




oal_int32 oal_usb_data_recv_process()
{
    if(NULL == _hi_usb_)
    {
        OAL_IO_PRINT("g_hi_sdio->bus_ops.rx is null");
        return OAL_FAIL;
    }
    _hi_usb_->bus_ops.rx(_hi_usb_->bus_data);

    return OAL_SUCC;

}

oal_uint send_msg_val = 0;

/******************************message begin***********************************/
oal_int32 oal_usb_send_msg(struct oal_usb* hi_usb, oal_uint val)
{
    oal_int32       ret  = OAL_SUCC;

    OAL_BUG_ON(!hi_usb);

    struct eth_drv_sg *oal_usb_msg_sg = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
    if(!oal_usb_msg_sg)
    {
        OAL_IO_PRINT("oal_usb_msg_sg mem alloc  failed!\n");
        return NULL;
    }


    if(val >= USB_D2H_MSG_COUNT)
    {
        OAL_IO_PRINT("[Error]invaild param[%lu]!\n", val);
        return -OAL_EINVAL;
    }

    /*sdio message can sent when wifi power on*/
 #if 0 /*wait for opening power on gpio */
    if(0 == hi110x_get_wifi_power_stat())
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY,"{oal_sdio_send_msg::wifi power off,can't send sdio msg!}");
        return -OAL_EBUSY;
    }
 #endif
    val = 1 << val;
    send_msg_val = val;
    oal_usb_msg_sg->buf = &send_msg_val;
    oal_usb_msg_sg->len = sizeof(oal_uint);
    oal_usb_msg_sg->next = NULL;
    //dprintf("send_msg_val = 0x%x\n" , *(oal_uint *)(oal_usb_msg_sg->buf));
    ret = usb_int_send(oal_usb_msg_sg);
    if (ret)
    {
        OAL_IO_PRINT("{oal_usb_int_send_msg::failed to send usb msg[%lu]!ret=%d}", val, ret);
        oal_free(oal_usb_msg_sg);
    }

   oal_free(oal_usb_msg_sg);
   return ret;
}

oal_int32 oal_usb_msg_recv_process(struct eth_drv_sg *sg)
{
    oal_int32           bit = 0;
    oal_uint32          msg;
    oal_int32           ret;

    OAL_IO_PRINT("msg info,sg->buf:%d,len:%d\n",*(int*)((void*)sg->buf),sg->len);
    msg = *(int*)((void*)sg->buf);

    OAL_IO_PRINT("msg info,message:%x\n",msg);


    if(!!((1<<USB_D2H_MSG_FLOWCTRL_OFF) & msg) & !!((1<<USB_D2H_MSG_FLOWCTRL_ON) & msg))
    {
        OAL_IO_PRINT("[ERROR]on/off should come at the same time!\n");
    }

    /*优先处理Panic消息*/

    if(oal_bit_atomic_test_and_clear(USB_D2H_MSG_DEVICE_PANIC, (unsigned long *)&msg))
    {
         OAL_IO_PRINT("USB_D2H_MSG_DEVICE_PANIC");
        bit = USB_D2H_MSG_DEVICE_PANIC;
        _hi_usb_->msg[bit].count++;
        _hi_usb_->last_msg = bit;
        //g_hi_sdio->msg[bit].cpu_time = cpu_clock(UINT_MAX);
        if(_hi_usb_->msg[bit].msg_rx)
            _hi_usb_->msg[bit].msg_rx(_hi_usb_->msg[bit].data);
    }

    for(bit = 0; bit<16; bit++)
    {
        if((msg&(1UL<<bit))!=0)
        {
            _hi_usb_->msg[bit].count++;
            _hi_usb_->last_msg = bit;
            //g_hi_sdio->msg[bit].cpu_time = cpu_clock(UINT_MAX);
            if(_hi_usb_->msg[bit].msg_rx)
            {
                _hi_usb_->msg[bit].msg_rx(_hi_usb_->msg[bit].data);
            }

            OAL_IO_PRINT("message,_hi_usb_->msg[%d].msg_rx==NULL:%d\n",bit , _hi_usb_->msg[bit].msg_rx == NULL);

        }
    }

    g_usb_message = -1;
    ret = usb_set_intr_buffer(g_drv_sg_message);
    if (ret <0)
    {
       OAL_IO_PRINT("failed to usb_set_intr_buffer\n");
       return OAL_FAIL;
    }

    return OAL_SUCC;

}

oal_void oal_usb_credit_info_init(struct oal_usb* hi_usb)
{
    hi_usb->usb_credit_info.large_free_cnt = 0;
    hi_usb->usb_credit_info.short_free_cnt = 0;
    oal_spin_lock_init(&hi_usb->usb_credit_info.credit_lock);
}

oal_int32 oal_usb_message_register(struct oal_usb *hi_usb,
                                                            oal_uint8 msg, usb_msg_rx cb,
                                                            oal_void* data)
{
    if(NULL == hi_usb || msg >= USB_D2H_MSG_COUNT)
        return -OAL_EFAIL;
    hi_usb->msg[msg].msg_rx = cb;
    hi_usb->msg[msg].data = data;
    OAL_IO_PRINT("enter oal_usb_message_register \n");
    return OAL_SUCC;
}

oal_void oal_usb_message_unregister(struct oal_usb *hi_usb,oal_uint8 msg)
{
    if(NULL == hi_usb || msg >= USB_D2H_MSG_COUNT)
        return;

    hi_usb->msg[msg].msg_rx = NULL;
    hi_usb->msg[msg].msg_rx = NULL;

    OAL_IO_PRINT("enter oal_usb_message_unregister \n");
}


oal_int32 oal_usb_device_panic_callback(void *data)
{
    struct oal_usb* hi_usb = (struct oal_usb*)data;
    //oal_sdio_exception_submit(hi_sdio, WIFI_DEVICE_PANIC);
    return OAL_SUCC;
}

oal_int32 oal_clear_first_recv_buf(struct eth_drv_sg *sg)
{
    struct eth_drv_sg *sg_temp;

    if(NULL == sg)
    {
        OAL_IO_PRINT("oal_clear_first_recv_buf,sg is null\n");
        return -OAL_EFAIL;
    }

    sg_temp = sg;

    while(sg_temp != NULL)
    {
        oal_memset((oal_void *)sg_temp->buf, 0, sg_temp->len);
        sg_temp = sg_temp ->next;
    }

    OAL_IO_PRINT("oal_clear_first_recv_buf,success to clear sg buffer data \n");

    return OAL_SUCC;
}


oal_int32 oal_alloc_first_recv_buf(struct eth_drv_sg *sg)
{
    struct eth_drv_sg *sg_aggr;
    struct eth_drv_sg *sg_hcc_head;
    struct eth_drv_sg *sg_hcc_payload;

    OAL_IO_PRINT("enter oal_alloc_first_recv_buf \n");

    sg_aggr        = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
    sg_hcc_head    = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
    sg_hcc_payload = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));


   // sg_aggr->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(OAL_SIZEOF(usb_rx_info_stru)));
    sg_aggr->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(32));
    sg_aggr->len  = 32;
    sg_aggr->next = sg_hcc_head;

    sg_hcc_head->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(64));
    sg_hcc_head->len  = 64;
    sg_hcc_head->next = sg_hcc_payload;

    sg_hcc_payload->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(1536));
    sg_hcc_payload->len  = 1536;
    sg_hcc_payload->next = NULL;

    sg->next = sg_aggr;

    OAL_IO_PRINT("sg->next=0x%x\n",sg->next);
    OAL_IO_PRINT("oal_alloc_first_recv_buf succ");
    return OAL_SUCC;
}


oal_int32 set_next_recv_info(struct eth_drv_sg *sg, int num)
{
   return usb_bulk_recv(sg, num);
}


oal_int32 oal_usb_init_callback()
{
    oal_int32 ret;

    /*init messge rx call back,use int port*/
    ret = usb_register_int_recv_callback(oal_usb_msg_recv_process);
    if (ret < 0)
    {
        OAL_IO_PRINT("failed to register int message interrupt\n");
        return -OAL_EFAIL;
    }

    ret = usb_register_int_send_callback(oal_usb_int_send_cb);
    if (ret < 0)
    {
        OAL_IO_PRINT("failed to usb_register_int_send_callback\n");
           return -OAL_EFAIL;
    }


    OAL_IO_PRINT("oal_usb_func_probe,usb_register_int_send_callback\n");

#if 0
    ret = usb_register_bulk_send_callback(oal_usb_bulk_send_cb);
    if (ret < 0)
    {
        OAL_IO_PRINT("failed to usb_register_bulk_send_callback\n");
        return -OAL_EFAIL;
    }
    OAL_IO_PRINT("oal_usb_func_probe,usb_register_bulk_send_callback\n");

    ret = usb_register_bulk_recv_callback(oal_usb_data_recv_process);
    if (ret < 0)
    {
        OAL_IO_PRINT("failed to usb_register_bulk_recv_callback\n");
        return -OAL_EFAIL;
    }
#endif
    return OAL_SUCC;


}

oal_int32 oal_set2usb_recv_buffer(struct oal_usb* hi_usb)
{
    oal_int32           ret;

    /*set the first recv buffer,ass(16) + hcc head(64) +payload(1540)*/
    ret = set_next_recv_info(hi_usb->usb_drv_rx_data, 3);
    if (ret < 0)
    {
        OAL_IO_PRINT("failed to usb_bulk_recv\n");
        return -OAL_EFAIL;
    }

    OAL_IO_PRINT("oal_usb_func_probe,set_next_recv_info\n");

#if 0
    ret = usb_set_intr_buffer(hi_usb->usb_drv_rx_message);
    if (ret <0)
    {
      OAL_IO_PRINT("failed to usb_set_intr_buffer\n");
      return -OAL_EFAIL;
    }
#endif

    OAL_IO_PRINT("oal_usb_func_probe,finish usb_set_intr_buffer\n");
    return ret;

}

oal_int32 oal_usb_alloc_org_buffer(struct oal_usb* hi_usb)
{
    oal_int32           ret;
    struct eth_drv_sg  *drv_sg_bulk;
#if 0
    struct eth_drv_sg  *drv_sg_bulk_test;
#endif
    if(NULL == hi_usb)
        return -OAL_EFAIL;

#if 0
    /*###########fore test begin*/
      drv_sg_bulk_test = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
      if(NULL == drv_sg_bulk_test)
      {
          OAL_IO_PRINT("oal_usb_func_probe,drv_sg is null");
          return -OAL_EFAIL;
      }
      OAL_IO_PRINT("oal_usb_func_probe,finish oal_memalloc drv_sg_bulk\n");

      ret = oal_alloc_first_recv_buf_test(drv_sg_bulk_test);
      if (ret < 0)
      {
          OAL_IO_PRINT("failed to alloc first rev buff\n");
          return -OAL_EFAIL;
      }

      hi_usb->usb_drv_sg_test = drv_sg_bulk_test->next;

    /*###########################*/
#endif

    /*1.bulk: rx buffer init begin*/
      drv_sg_bulk = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
      if(NULL == drv_sg_bulk)
      {
          OAL_IO_PRINT("oal_usb_func_probe,drv_sg is null");
          return -OAL_EFAIL;
      }
      OAL_IO_PRINT("oal_usb_func_probe,finish oal_memalloc drv_sg_bulk\n");

      ret = oal_alloc_first_recv_buf(drv_sg_bulk);
      if (ret < 0)
      {
          OAL_IO_PRINT("failed to alloc first rev buff\n");
          return -OAL_EFAIL;
      }

      hi_usb->usb_drv_rx_data = drv_sg_bulk->next;

      OAL_IO_PRINT("##first,drv_sg_bulk->next->buf=%x\n",drv_sg_bulk->next->buf);
      OAL_IO_PRINT("##second,drv_sg_bulk->next->next->buf=%x\n",drv_sg_bulk->next->next->buf);
      OAL_IO_PRINT("##third,drv_sg_bulk->next->next->next->buf=%x\n",drv_sg_bulk->next->next->next->buf);

      /*1.bulk: rx buffer init end*/


      /*2.int: rx buffer init begin*/

      g_drv_sg_message=(struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
      g_drv_sg_message->buf =(oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(4));
      g_drv_sg_message->len = 4;
      g_drv_sg_message->next = NULL;

      hi_usb->usb_drv_rx_message = g_drv_sg_message;

      /*2.int: rx buffer init end*/


}



/*
 * Prototype    : oal_usb_process_rxdata
 * Description  : through usb ,process rx data
 * Input        : struct oal_usb *hi_usb
 * Output       : None
 * Return Value : oal_int32
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2016/4/15
 *     Author       :  00217036
 *     Modification : Created function
 *
 */
oal_int32 oal_usb_process_rxdata(struct oal_usb *hi_usb)
{
    oal_uint8                   int_mask;
    oal_int32                   ret;
    oal_int32                   data_type;

    /*sdio bus state access lock by sdio bus claim locked.*/
    if(NULL == hi_usb)
    {
        OAL_IO_PRINT("oal_usb_do_isr, hi_usb is null!\r\n");
        return OAL_FAIL;
    }

    ret = wifi_usb_bulk_read_event_read();

    if ( OS_ERRNO_EVENT_READ_TIMEOUT == ret) {
        OAL_IO_PRINT("wifi_usb_bulk_read_event_read,time out\n");
        return OAL_FAIL;
    }

    /*Get event data*/
 //   data_type = get_wifi_event_type();
//#ifdef _PRE_WLAN_FEATURE_DEBUG_LOG
 //   OAL_IO_PRINT("get_wifi_event_type,data_type:0x%x\r\n",data_type);
//#endif
#if 0
    if (TYPE_MSG_DATA == (data_type & TYPE_MSG_DATA)) /*message data event*/
    {
        #ifdef _PRE_WLAN_FEATURE_DEBUG_LOG
            OAL_IO_PRINT("get_wifi_event_type,message data\r\n");
        #endif
        ret = oal_usb_msg_recv_process(g_drv_sg_message);
        if (OAL_FAIL == ret)
        {
            OAL_IO_PRINT("fail to oal_usb_msg_recv_process\r\n");
        }
        hi_usb->message_int_count++;
    }
#endif
 //   if (TYPE_BULK_DATA == (data_type & TYPE_BULK_DATA))/*bulk data event*/
 //   {
     //   #ifdef _PRE_WLAN_FEATURE_DEBUG_LOG
     //       OAL_IO_PRINT("get_wifi_event_type,bulk data\r\n");
    //    #endif
        ret = oal_usb_data_recv_process();
        if (OAL_FAIL == ret)
        {
            OAL_IO_PRINT("fail to oal_usb_data_recv_process\r\n");
        }
        hi_usb->data_bulk_count++;
        OAL_IO_PRINT("oal_usb_process_rxdata:%d\n",hi_usb->data_bulk_count);
  #if 0
    }
    else
    {
        OAL_IO_PRINT("recv message is not message event and data event\r\n");
        return OAL_FAIL;
    }
  #endif
    OAL_IO_PRINT("succeed to handle usb irq\n");

    return OAL_SUCC;
}





/*
 * Prototype    : oal_usb_rxdata_thread
 * Description  : usb rx data function
 * Input        : adapter   oal_usb handler
 * Output       :
 * Return Value : succ or fail
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2016/4/15
 *     Author       :  00217036
 *     Modification : Created function
 *
 */
OAL_STATIC oal_int32 oal_usb_rxdata_thread(oal_void *data)
{
    oal_int32                     ret;
    struct oal_usb               *hi_usb;

    hi_usb = (struct oal_usb *)data;

    OAL_BUG_ON(!hi_usb);


    OAL_IO_PRINT("hisi wifi sched ctrl rx thread high speed\n");

    for(;;)
    {

        /* start to read usb interrupt */
        //  oal_usb_rx_transfer_lock(hi_usb);
        OAL_IO_PRINT("oal_usb_process_rxdata\n");
        /*wait firmware close run*/
        ret = OAL_WAIT_EVENT_INTERRUPTIBLE(hi_usb->hcc_rx_thread_active_wq,(OAL_TRUE == hi_usb->hcc_rx_active_flag));
        if(OAL_UNLIKELY(-ERESTARTSYS == ret))
        {
            OAL_IO_PRINT("wifi task %s was interrupted by a signal\n", oal_get_current_task_name());
            break;
        }

        ret = oal_usb_process_rxdata(hi_usb);
        if(OAL_UNLIKELY(ret))
        {
            //TODO later,modified by 
            OAL_IO_PRINT("oal_usb_do_isr error,process exception\n");
            //oal_usb_exception_submit(hi_usb, SDIO_TRANS_FAIL);
        }
     //   oal_usb_rx_transfer_unlock(hi_usb);

    }

    OAL_IO_PRINT("usb rx data is terminated\n");
    return OAL_SUCC;
}


/*
 * Prototype    : oal_register_usb_intr
 * Description  : register usb rx task
 * Input        : struct oal_usb *hi_usb
 * Output       :
 * Return Value : succ or fail
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2016/4/15
 *     Author       :  00217036
 *     Modification : Created function
 *
 */
oal_int32 oal_register_usb_intr(struct oal_usb *hi_usb)
{
    oal_int32 ret = OAL_SUCC;
    oal_kthread_param_stru thread_param = {0};

   // oal_spin_lock_init(&hi_usb->st_irq_lock);
   // hi_usb->ul_wlan_irq = pst_board->wlan_irq;

    /* create thread for gpio rx data in interrupt handler*/

    thread_param.l_cpuid      = NOT_BIND_CPU;
    thread_param.l_policy     = OAL_SCHED_FIFO;
    thread_param.l_prio       = USB_TASK_PRIO;
    thread_param.ul_stacksize = USB_TASK_SIZE;

    hi_usb->gpio_rx_tsk = oal_kthread_create("oal_usb_rx_data",oal_usb_rxdata_thread, (void *)hi_usb,&thread_param);
    if (NULL == hi_usb->gpio_rx_tsk)
    {
        OAL_IO_PRINT("[SDIO][ERROR]failed to create rx data thread\n");
        return -OAL_EFAIL;
    }


    OAL_IO_PRINT("success to register usb intr\n");
    return OAL_SUCC;

}

/*
 * Prototype    : oal_unregister_usb_intr
 * Description  : unregister usb rx task
 * Input        : struct oal_usb *hi_usb
 * Output       :
 * Return Value : succ or fail

 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2016/7/22
 *     Author       :  
 *     Modification : Created function
 *
 */
oal_int32 oal_unregister_usb_intr(struct oal_usb *hi_usb)
{
    oal_int32 status;

    status = LOS_TaskDelete(hi_usb->taskid);
    if(status != LOS_OK)
    {
        OAL_IO_PRINT("stop the usb rx data failed!\n");
    }

    return status;
}


/*
 * Prototype    : oal_usb_interrupt_register
 * Description  : register interrupt
 * Input        : None
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2016/4/15
 *     Author       : 
 *     Modification : Created function
 *
 */
oal_int32 oal_usb_interrupt_register(struct oal_usb *hi_usb)
{
    oal_int32 ret;

    if (hiusb_intr_mode)
    {
        /* use gpio interrupt for sdio data interrupt */
        //ret = oal_usb_register_gpio_intr(hi_usb);
    }
    else
    {
        ret = oal_register_usb_intr(hi_usb);
    }

    return ret;
}




oal_int32 oal_usb_init(struct oal_usb* hi_usb)
{
    oal_int32           ret;
    struct eth_drv_sg  *drv_sg_bulk;

    if(NULL == hi_usb)
    {
        OAL_IO_PRINT("hi_usb is null");
        return -OAL_EFAIL;
    }
    OAL_IO_PRINT("oal_usb_func_probe...\n");

    hi_usb->hcc_rx_active_flag = -OAL_EFAIL;;
    OAL_WAIT_QUEUE_INIT_HEAD(&hi_usb->hcc_rx_thread_active_wq);    /*queues init*/

    ret = oal_usb_init_callback();
    if(-OAL_EFAIL == ret)
    {
        OAL_IO_PRINT("init oal_usb_init_callback");
        return -OAL_EFAIL;
    }


    /* register interrupt process function */
    ret = oal_usb_interrupt_register(hi_usb);
    if(ret < 0)
    {
        OAL_IO_PRINT("oal_usb_interrupt_register fail \n");
        return -OAL_EFAIL;
    }


    ret = oal_usb_alloc_org_buffer(hi_usb);
    if(-OAL_EFAIL == ret)
    {
        OAL_IO_PRINT("init oal_usb_alloc_org_buffer");
        return -OAL_EFAIL;
    }

    OAL_IO_PRINT("oal_usb_func_probe,finish\n");


    return OAL_SUCC;
}

oal_int32 oal_memset_scatt_buff(struct eth_drv_sg *sg)
{
    struct eth_drv_sg *sg_temp;

    if(NULL == sg)
    {
       OAL_IO_PRINT("oal_memset_scatt_buff, sg is null\n");
       return -OAL_FAIL;
    }

    sg_temp = sg;
    oal_int i=0;

    while(NULL != sg_temp->next)
    {
        sg_temp->buf = 0;
        sg_temp->len =0;
        sg_temp = sg_temp->next;
        i++;
    }
    return OAL_SUCC;
}

struct eth_drv_sg* oal_alloc_scatt_buff(oal_uint32 max_scatt_num)
{
    struct eth_drv_sg *sg_head;
    struct eth_drv_sg *temp;

    oal_int32          idx;


    if(max_scatt_num <= 0)
    {
        OAL_IO_PRINT("oal_alloc_scatt_buff,max_scatt_num isn't bigger than zero\n");
        return NULL;
    }

    OAL_IO_PRINT("oal_alloc_scatt_buff,max_scatt_num=%d\n",max_scatt_num);

    sg_head = (struct eth_drv_sg*)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(OAL_SIZEOF(struct eth_drv_sg)));
    temp = sg_head;

    for(idx = 0;idx < 2*(max_scatt_num -1); idx++)
    {
        temp->next = (struct eth_drv_sg*)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(OAL_SIZEOF(struct eth_drv_sg)));
        temp = temp->next;
    }
    temp->next = NULL;

    OAL_IO_PRINT("sg_head=%x",sg_head);
    return sg_head;
}

struct oal_usb* oal_usb_init_module(oal_void* data)
{
#ifdef CONFIG_HISDIO_H2D_SCATT_LIST_ASSEMBLE
    oal_uint32 tx_scatt_buff_len = 0;
#endif
    oal_uint32 ul_rx_seg_size;
    struct oal_usb* hi_usb;

    OAL_IO_PRINT("hii110x usb driver installing...\n");
    hi_usb = (struct oal_usb*)oal_memalloc(OAL_SIZEOF(struct oal_usb));
    if(NULL == hi_usb)
    {
        OAL_IO_PRINT("[E]alloc oal_usb failed [%d]\n", (oal_int32)OAL_SIZEOF(struct oal_usb));
        return NULL;
    }
    oal_memset((oal_void*)hi_usb,0,OAL_SIZEOF(struct oal_usb));

#if 0  //TODO ,open later,
    /*init sdio exception work*/
    oal_spin_lock_init(&hi_usb->sdio_excp_lock);
    OAL_INIT_WORK(&hi_usb->sdio_excp_worker, oal_sdio_exception_handler);
#endif


    oal_usb_credit_info_init(hi_usb);

    hi_usb->usb_data_head = (struct oal_netbuf_head_stru*)oal_memalloc(OAL_SIZEOF(oal_netbuf_head_stru));
     if(NULL == hi_usb->usb_data_head)
    {
        OAL_IO_PRINT("[E]alloc hi_usb->usb_data_head failed [%d]\n", (oal_int32)sizeof(oal_netbuf_head_stru));
         return NULL;
    }
    oal_memset(hi_usb->usb_data_head, 0 , sizeof(oal_netbuf_head_stru));

    hi_usb->bus_data = data;
    _hi_usb_ = hi_usb;



    hi_usb->scatt_info[USB_READ].max_scatt_num = HIUSB_DEV2HOST_SCATT_MAX + 1;
    hi_usb->scatt_info[USB_READ].sglist = oal_alloc_scatt_buff(HIUSB_DEV2HOST_SCATT_MAX + 1);
    if(NULL == hi_usb->scatt_info[USB_READ].sglist)
    {
        goto failed_usb_read_sg_alloc;
    }

    /*1 for algin buff, 1 for scatt info buff*/
    hi_usb->scatt_info[USB_WRITE].max_scatt_num = HIUSB_HOST2DEV_SCATT_MAX + 2;
    hi_usb->scatt_info[USB_WRITE].sglist = oal_alloc_scatt_buff(HIUSB_HOST2DEV_SCATT_MAX + 2);

    if(NULL == hi_usb->scatt_info[USB_WRITE].sglist)
    {
        goto failed_usb_write_sg_alloc;
    }
#if 0 //TODO ,open later,
    low_power_init();
#endif
    oal_usb_message_register(hi_usb,
                               USB_D2H_MSG_DEVICE_PANIC,
                               oal_usb_device_panic_callback,
                               hi_usb);
    return hi_usb;

failed_usb_read_sg_alloc:
    kfree(hi_usb->usb_data_head);
failed_usb_write_sg_alloc:
    kfree(hi_usb->scatt_info[USB_READ].sglist);
    kfree(hi_usb);
    return NULL;
}


oal_void  oal_usb_exit_module(struct oal_usb* hi_usb)
{
    OAL_IO_PRINT("usb module unregistered\n");
#if 0 //TODO ,open later,
    low_power_exit();
#endif

#ifdef CONFIG_HISDIO_H2D_SCATT_LIST_ASSEMBLE
    kfree(hi_usb->scatt_buff.buff);
#endif
    kfree(hi_usb->scatt_info[USB_WRITE].sglist);
    kfree(hi_usb->scatt_info[USB_READ].sglist);
    kfree(hi_usb->rx_reserved_buff);
    kfree(hi_usb);

    kfree(hi_usb->usb_drv_rx_data);
    kfree(hi_usb->usb_drv_rx_message);
    _hi_usb_ = NULL;
}



oal_int32 oal_usb_transfer_rx_register(struct oal_usb *hi_usb, hiusb_rx rx)
{
    /*FIXME? add lock later.*/
    hi_usb->bus_ops.rx = rx;
    return OAL_SUCC;
}


oal_void oal_usb_transfer_rx_unregister(struct oal_usb *hi_usb)
{
    /*FIXME? add lock later.*/
    hi_usb->bus_ops.rx = NULL;
}

#if 0
oal_int32 oal_alloc_first_recv_buf_test(struct eth_drv_sg *sg)
{
    struct eth_drv_sg *sg_aggr;
    struct eth_drv_sg *sg_hcc_head;
    struct eth_drv_sg *sg_hcc_payload;

    OAL_IO_PRINT("enter oal_alloc_first_recv_buf \n");

    sg_aggr        = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
    sg_hcc_head    = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));
    sg_hcc_payload = (struct eth_drv_sg*)oal_memalloc(OAL_SIZEOF(struct eth_drv_sg));


    sg_aggr->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(64));
    sg_aggr->len  = 64;
    sg_aggr->next = sg_hcc_head;

    sg_hcc_head->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(64));
    sg_hcc_head->len  = 64;
    sg_hcc_head->next = sg_hcc_payload;

    sg_hcc_payload->buf  = (oal_uint32)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(1540));
    sg_hcc_payload->len  = 1540;
    sg_hcc_payload->next = NULL;

    sg->next = sg_aggr;

    OAL_IO_PRINT("sg->next=0x%x\n",sg->next);
    OAL_IO_PRINT("oal_alloc_first_recv_buf succ");
    return OAL_SUCC;
}
#endif


#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
