/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : plat_firmware_test.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : firmware加载
  函数列表   : 
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "los_event.h"
#include "plat_firmware.h"
#include "los_typedef.h"
#include "plat_debug.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "los_exc.h"

extern int32_t check_version(void);
extern int32_t send_msg(uint8_t *data, uint32_t len);
extern int32_t read_msg(uint8_t *data, int32_t len, uint32_t ms_timeout);
extern int32_t msg_send_and_recv_except(uint8_t *data, int32_t len, const uint8_t *expect);
extern int32_t recv_expect_result(const uint8_t *expect);

#define BUFF_LEN         (1024*100)

char* download_file_cmd_head = "FILES 1 ";
#if 1
char* download_address="0x40100000 ";
char* read_memory_address="0x40100000 ";
#else
char* download_address="0x000F8000 ";
char* read_memory_address="0x000F8000 ";
#endif

char* read_memory_cmd_head="READM ";

char *switch_mem_reg_address="0x40010100 ";
char *switch_mem_reg_value="0x2 ";
char *write_reg_cmd_head="WRITEM 2 ";


uint8_t * read_buff = NULL;
uint8_t * send_buff = NULL;
uint8_t * cmd_buff = NULL;

static int32_t check_version_test(void)
{
    PS_PRINT_DBG(" check version\n");

    return check_version();
}

static int32_t read_memory_test(char *cmd, uint32_t read_mem_len)
{
    int32_t ret=0;
    int32_t len;
    PS_PRINT_DBG(" read memory\n"); 
    len = HISI_CHANNEL_ALIGN(OS_STR_LEN(cmd)+1);
    if(CMD_BUFF_LEN < len)
    {
        PS_PRINT_ERR("len out of range\r\n");
        return -EFAIL;
    }
    send_msg(cmd, len);
    ret=read_msg(read_buff, read_mem_len, READ_MEG_TIMEOUT);
    if(ret < 0)
    {
        PS_PRINT_ERR("read memory fail \r\n");
        return -EFAIL;
    }
    return SUCC;
}

static int32_t send_file_test(char *cmd, uint32_t file_len)
{
    int32_t ret;
    int32_t len;
    PS_PRINT_DBG(" write file\n");
    len = HISI_CHANNEL_ALIGN(OS_STR_LEN(cmd)+1);
    if(CMD_BUFF_LEN < len)
    {
        PS_PRINT_ERR("len out of range\r\n");
        return -EFAIL;
    }
    ret = msg_send_and_recv_except(cmd, len, MSG_FROM_DEV_READY_OK);
    if (0 > ret)
    {
        PS_PRINT_ERR("SEND file cmd error\r\n");
        return -EFAIL;
    }

    /* Wait at least 1 ms */
  //  usleep(1000);

    /*发送文件内容*/
    ret = msg_send_and_recv_except(send_buff, file_len, MSG_FROM_DEV_FILES_OK);
    if(0 > ret)
    {
        PS_PRINT_ERR(" sdio send data fail\n");
        return -EFAIL;
    }
    return SUCC;
}

static int32_t write_reg_test(char *cmd)
{
    int32_t ret;
    int32_t len;
    PS_PRINT_DBG(" write regest\n");
    //ret = number_type_cmd_send(Key, Value);
    len = HISI_CHANNEL_ALIGN(OS_STR_LEN(cmd)+1);
    if(CMD_BUFF_LEN < len)
    {
        PS_PRINT_ERR("len out of range\r\n");
        return -EFAIL;
    }
    ret = send_msg(cmd, len);
    if (0 > ret)
    {
        PS_PRINT_ERR("send write reg cmd fail\r\n");
        return -EFAIL;
    }


    ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
    if (0 > ret)
    {
        PS_PRINT_ERR("recv expect result fail!\n");
        return -EFAIL;
    }
    return SUCC;
}

static void setbuff(uint8_t * buf, uint32_t buf_len)
{
    uint8_t value=0;
    for(uint32_t index=0; index<buf_len; index++)
    {
        buf[index]=value;
        value++;
    }
}

int32_t loop_file_test(void)
{
    int32_t ret;
    uint32_t len=1024*16 + 32;
    uint32_t align_len;
    uint64_t index=0;
    setbuff((uint8_t *)send_buff,BUFF_LEN);
    while(len<BUFF_LEN)
    {
        PS_PRINT_DBG(">>>>>>>>>>>>>>>>>>>>>>index=%llu\r\n", ++index);
        align_len  = HISI_CHANNEL_ALIGN(len);
        PS_PRINT_DBG("--------------------->len=%d, align_len=%d\r\n", len, align_len);
        snprintf((char *)cmd_buff,CMD_BUFF_LEN,"%s%s",
                                                download_file_cmd_head,
                                                download_address); 
        ret=send_file_test(cmd_buff, align_len);
        if(SUCC!=ret)
        {
            return -EFAIL;
        }
        snprintf(cmd_buff,CMD_BUFF_LEN,"%s%s%d%s",
                                                read_memory_cmd_head,
                                                read_memory_address,
                                                align_len,
                                                "  ");
        ret=read_memory_test(cmd_buff, align_len);
        if(SUCC!=ret)
        {
            return -EFAIL;
        }
        if (!OS_MEM_CMP(send_buff, read_buff, len))
        {
            PS_PRINT_DBG(" cmp succ, len=0x%x\n", len);
            #if 0
            len+=4;
            len = len % (BUFF_LEN - 512);
            if(len==0)
            {
                len=4;
            }
            #endif
            continue;
        }
        else
        {
            PS_PRINT_ERR(" cmp error, len=0x%x\n", len);
            return -EFAIL;
        }
     }
    return SUCC;
}


int32_t firmware_test(void)
{
    int32_t ret;
    read_buff = OS_KMALLOC_GFP(BUFF_LEN);
    send_buff = OS_KMALLOC_GFP(BUFF_LEN);
    cmd_buff  = OS_KMALLOC_GFP(CMD_BUFF_LEN);
    g_aus_recv_cmd_buff= OS_KMALLOC_GFP(CMD_BUFF_LEN);
    g_aus_send_cmd_buff= OS_KMALLOC_GFP(CMD_BUFF_LEN);
    if(NULL == read_buff || NULL == send_buff || NULL == cmd_buff
        || NULL == g_aus_recv_cmd_buff || NULL == g_aus_send_cmd_buff)
    {
        printf("malloc buff fail\r\n");
        return -1;
    }
    
    #if 0
    ret=check_version_test();
    if(SUCC!=ret)
    {
        return -EFAIL;
    }
    #else
    ret=check_version_test();
    if(SUCC!=ret)
    {
        ret= -EFAIL;
        goto firmware_test_end;
    }
    setbuff((uint8_t *)send_buff,BUFF_LEN);

    snprintf((char *)cmd_buff,CMD_BUFF_LEN,"%s%s%s",
                                                    write_reg_cmd_head,
                                                    switch_mem_reg_address,
                                                    switch_mem_reg_value);
    ret=write_reg_test((char *)cmd_buff);
    if(SUCC!=ret)
    {
        ret= -EFAIL;
        goto firmware_test_end;
    }
    
    ret=loop_file_test();
    if(SUCC!=ret)
    {
        ret= -EFAIL;
        goto firmware_test_end;
    }
   #endif 
    ret= SUCC;
   
firmware_test_end:
    OS_MEM_KFREE(read_buff);
    OS_MEM_KFREE(send_buff);
    OS_MEM_KFREE(cmd_buff);
    OS_MEM_KFREE(g_aus_recv_cmd_buff);
    OS_MEM_KFREE(g_aus_send_cmd_buff);
    return ret;
}

