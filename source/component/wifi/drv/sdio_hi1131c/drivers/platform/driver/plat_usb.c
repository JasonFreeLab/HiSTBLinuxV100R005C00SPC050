/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : plat_usb.c
 * Version       : Hi1131
 * Author        : 
 * Created       : 2015/04/08
 * Last Modified :
 * Description   : plat sdio driver
 * Function List :


 * History       :
 * 1.Date        : 2015/04/08
 *   Author      : 
 *   Modification: Created file
 *
 */
#ifdef _PRE_FEATURE_USB

#include "usb_eth_drv.h"
#include "los_typedef.h"
#include "plat_debug.h"
#include "plat_firmware.h"

#define SEND_XFER_STRING_LEN                     (128)
#define XFER_COUNT_END_CHAR                      ('@')
#define RECV_BUFF_LEN                            (1024*400)

uint8_t * g_puc_recv_xfer_string = NULL;
uint8_t * g_puc_send_xfer_string = NULL;
uint8_t * g_puc_recv_buff = NULL;


struct eth_drv_sg g_ast_recv_msg_sg[2];
struct eth_drv_sg g_ast_send_msg_sg[2];

/*****************************************************************************
  4 函数实现
*****************************************************************************/
extern int usb_firmware_send(struct eth_drv_sg *sg_list, unsigned int sg_num);
extern int usb_bulk_recv_modify(struct eth_drv_sg *sg, int num, int rcv_flag) ;
extern void wait_usb_enum_done();

extern int32_t firmware_test(void);


/*****************************************************************************
 Prototype    : firmware_str_to_num
 Description  :
 this function turn string to number, the string must be a Hexadecimal data,
 start with '0x', end with macro XFER_COUNT_END_CHAR, if it's not, this
 function will return error

 Input        : const char *cp
                uint32_t *num
 Output       : None
 Return Value : ERR or SUCC
 Calls        :
 Called By    :

  History        :
  1.Date         : 2016/3/23
    Author       : 
    Modification : Created function

*****************************************************************************/
#define TOLOWER(x) ((x) | 0x20)
#define ISDIGIT(c) (((c) >= '0') && ((c) <= '9'))
#define ISXDIGIT(c) (ISDIGIT (c) || (TOLOWER(c) >= 'a') && (TOLOWER(c) <= 'f'))
static int32_t firmware_str_to_num(const char *cp, UINT32 *num)
{
	UINT32 result = 0;
	if (cp[0] == '0' && ( (cp[1] == 'x')||(cp[1] == 'X')) )
		cp += 2;
    else
        return -EFAIL;
	while (ISXDIGIT(*cp)) {
		UINT32 value;
		value = ISDIGIT(*cp) ? *cp - '0' : TOLOWER(*cp) - 'a' + 10;
		result = result * 16 + value;
		cp++;
	}
    if(XFER_COUNT_END_CHAR!=(*cp))
    {
        return -EFAIL;
    }
    *num=result;
	return SUCC;
}
extern int wifi_usb_bulk_read_event_read();

int32_t read_msg(uint8_t *data, int32_t len, uint32_t ms_timeout)
{
    int32_t  i;
    int32_t  ret_len;
    char * ver_info=NULL;

    printf(" plat_usb read_msg begin\r\n");

    if (NULL == data)
    {
        PS_PRINT_ERR("data is NULL\n ");
        return -EFAIL;
    }
    g_ast_recv_msg_sg[0].buf= (uint32_t)g_puc_recv_xfer_string;
    g_ast_recv_msg_sg[0].len= SEND_XFER_STRING_LEN;
    g_ast_recv_msg_sg[0].next=&g_ast_recv_msg_sg[1];
    g_ast_recv_msg_sg[1].buf= (uint32_t)g_puc_recv_buff;
    g_ast_recv_msg_sg[1].len= RECV_BUFF_LEN;
    g_ast_recv_msg_sg[1].next=NULL;
    usb_bulk_recv(g_ast_recv_msg_sg, 2);
	wifi_usb_bulk_read_event_read();
    ret_len = g_ast_recv_msg_sg[1].len;
    if( 0 != (ret_len%32) )
    {
        PS_PRINT_ERR("the read back length is not alignmemt, ret len=%d\n", ret_len);
    }
    if(ret_len<len)
    {
        len=ret_len;
    }
    ver_info=(char *)g_ast_recv_msg_sg[1].buf;
    for (i = 0; i < len; i++)
    {
        data[i] = ver_info[i];
    }
    PS_PRINT_DBG("read back len=%d\n", ret_len);

    printf(" plat_usb read_msg\r\n");
    return ret_len;
}

/*****************************************************************************
 函 数 名  : send_msg
 功能描述  : host往device发送消息
 输入参数  : data: 发送buffer
             len : 发送数据的长度
 输出参数  : 无
 返 回 值  : -1表示失败，否则返回实际发送的长度
 调用函数  : sdio_patch_writesb
 被调函数  : msg_send_and_recv_except
             check_version
             number_type_cmd_send

 修改历史      :
  1.日    期   : 2015年4月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32_t send_msg(uint8_t *data, uint32_t len)
{
    int32_t   l_ret;
    if(((uint32_t)data % 32!=0)||(len % 32!=0))
    {
        len = HIUSB_ALIGN_32(len);
   //     PS_PRINT_ERR("send msg aligment is error ,buff address = 0x%x, len=0x%x\r\n", data, len);
    }

    snprintf(g_puc_send_xfer_string,SEND_XFER_STRING_LEN,"0x%x@", len);
    g_ast_send_msg_sg[0].buf=(uint32_t)g_puc_send_xfer_string;
    g_ast_send_msg_sg[0].len=SEND_XFER_STRING_LEN;
    g_ast_send_msg_sg[0].next=&g_ast_send_msg_sg[1];
    g_ast_send_msg_sg[1].buf=(uint32_t)data;
    g_ast_send_msg_sg[1].len=len;
    g_ast_send_msg_sg[1].next=NULL;

    PS_PRINT_DBG("len = %s\n", g_puc_send_xfer_string);
    if(len<30)
    {
        PS_PRINT_DBG("string = %s\n", (char *)g_ast_send_msg_sg[1].buf);
    }

    usb_bulk_send(g_ast_send_msg_sg, 2); //全局
    extern int wifi_usb_bulk_write_event_read();
	wifi_usb_bulk_write_event_read();

 //   LOS_EventRead(&g_firmware_usb_send_event, FIRMWARE_USB_WRITE_OVER,
 //       OS_WAITMODE_AND|OS_WAITMODE_CLR, OS_WAIT_FOREVER);
//切换时间 动态调整线程优先级 USB线程优先级 callback是否中断
    l_ret = SUCC;
    return l_ret;
}

int32 wlan_power_on_usb()
{
    uint32_t ret;
    
    board_power_on();
    PS_PRINT_INFO("wait_usb_enum_done\n");
    wait_usb_enum_done();
    PS_PRINT_INFO("wait_usb_enum_done over\n");


    //usb_bulk_recv_modify(g_ast_recv_msg_sg, 2, 1);
  //  ret=firmware_test();
    ret = firmware_download(WIFI_CFG);
    if(SUCC!=ret)
    {
        PS_PRINT_ERR("firmware power on fail\n");
        board_power_off();
    }

 //   hiusb_reset_hcd();

    return ret;
}

void plat_usb_init(void)
{
    g_puc_recv_xfer_string = OS_KMALLOC_GFP(SEND_XFER_STRING_LEN);
    if(NULL == g_puc_recv_xfer_string)
    {
        PS_PRINT_ERR("g_aus_recv_xfer_string malloc fail\r\n");
        return;
    }
    g_puc_send_xfer_string = OS_KMALLOC_GFP(SEND_XFER_STRING_LEN);
    if(NULL == g_puc_send_xfer_string)
    {
        PS_PRINT_ERR("g_aus_send_xfer_string malloc fail\r\n");
        return;
    }
    g_puc_recv_buff = OS_KMALLOC_GFP(RECV_BUFF_LEN);
    if(NULL == g_puc_recv_buff)
    {
        PS_PRINT_ERR("g_aus_send_xfer_string malloc fail\r\n");
        return;
    }

    g_ast_recv_msg_sg[0].buf= (uint32_t)g_puc_recv_xfer_string;
    g_ast_recv_msg_sg[0].len= SEND_XFER_STRING_LEN;
    g_ast_recv_msg_sg[0].next=&g_ast_recv_msg_sg[1];
    g_ast_recv_msg_sg[1].buf= (uint32_t)g_puc_recv_buff;
    g_ast_recv_msg_sg[1].len= RECV_BUFF_LEN;
    g_ast_recv_msg_sg[1].next=NULL;

    g_ast_send_msg_sg[0].buf=(uint32_t)g_puc_send_xfer_string;
    g_ast_send_msg_sg[0].len=SEND_XFER_STRING_LEN;
    g_ast_send_msg_sg[0].next=&g_ast_send_msg_sg[1];
    g_ast_send_msg_sg[1].next=NULL;

}

#endif

