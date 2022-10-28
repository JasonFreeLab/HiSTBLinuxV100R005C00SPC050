/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��˼�뵼�����޹�˾

 ******************************************************************************
  �� �� ��   : plat_firmware.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : firmware����
  �����б�   : firmware_read_msg
               firmware_send_msg
               recv_expect_result
               msg_send_and_recv_except
               malloc_cmd_buf
               delete_space
               string_to_num
               open_file_to_readm
               recv_device_mem
               check_version
               number_type_cmd_send
               exec_number_type_cmd
               exec_quit_type_cmd
               exec_file_type_cmd
               exec_shutdown_type_cmd
               execute_download_cmd
               firmware_read_cfg
               firmware_parse_cmd
               firmware_parse_cfg
               firmware_get_cfg
               firmware_download
               firmware_cfg_init
               firmware_cfg_clear
  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "plat_debug.h"
#include "plat_firmware.h"
#include "plat_sdio.h"
#include "plat_cali.h"
#include "plat_pm.h"
#include "oal_sdio_host_if.h"
#include "hisi_ini.h"
#include "oal_file.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310)
    #if defined(CFG_PRODUCT_TYPE_LINUX)
    #define WIFI_CFG_PATH                 "/etc/Wireless/firmware/wifi_cfg_linux"
    #define RAM_CHECK_CFG_PATH            "/etc/Wireless/firmware/ram_reg_test_cfg"
    #else
    #define WIFI_CFG_PATH                 "/system/vendor/firmware/wifi_cfg"
    #define RAM_CHECK_CFG_PATH            "/system/vendor/firmware/ram_reg_test_cfg"
    #endif
#elif defined(CONFIG_ARCH_HI3650)
#define WIFI_CFG_PATH                 "/system/vendor/firmware/wifi_cfg"
#define RAM_CHECK_CFG_PATH            "/system/vendor/firmware/ram_reg_test_cfg"
#endif

#define FILE_COUNT_PER_SEND           (1)
#define MIN_FIRMWARE_FILE_TX_BUF_LEN  (4096)

#define READ_MEG_TIMEOUT            (200)      /* 200ms */
#define READ_MEG_JUMP_TIMEOUT       (100000)   /* 100s */

#define FILE_CMD_WAIT_TIME_MIN      (5000)     /* 5000us */
#define FILE_CMD_WAIT_TIME_MAX      (5100)     /* 5100us */

#define VERSION_LEN                 (64)

#define READ_CFG_BUF_LEN            (2048)

#define DOWNLOAD_CMD_LEN            (32)
#define DOWNLOAD_CMD_PARA_LEN       (800)

#define HOST_DEV_TIMEOUT            (3)

#define INT32_STR_LEN               (32)



/*�����Ƿ���device����Ĺؼ���*/
#define VER_CMD_KEYWORD             "VERSION"
#define JUMP_CMD_KEYWORD            "JUMP"
#define FILES_CMD_KEYWORD           "FILES"
#define RMEM_CMD_KEYWORD            "READM"
#define WMEM_CMD_KEYWORD            "WRITEM"
#define QUIT_CMD_KEYWORD            "QUIT"

/*������device������ִ�гɹ����صĹؼ��֣�host�յ�һ�¹ؼ���������ִ�гɹ�*/
#define MSG_FROM_DEV_WRITEM_OK      "WRITEM OK"
#define MSG_FROM_DEV_READM_OK       ""
#define MSG_FROM_DEV_FILES_OK       "FILES OK"
#define MSG_FROM_DEV_READY_OK       "READY"
#define MSG_FROM_DEV_JUMP_OK        "JUMP OK"
#define MSG_FROM_DEV_QUIT_OK        ""

/*������cfg�ļ���������Ĳ���ͷ��һ���Ϸ���cfg�����ʽΪ:����ͷ+����ؼ���(QUIT�������)*/
#define FILE_TYPE_CMD_KEY           "ADDR_FILE_"
#define NUM_TYPE_CMD_KEY            "PARA_"

#define COMPART_KEYWORD             ' '
#define CMD_LINE_SIGN               ';'
#define CFG_INFO_RESERVE_LEN        (8)

#define TRANSFER_LIMIT_SIZE         (1024*32)    // temporary use

enum FIRMWARE_CFG_CMD_ENUM
{
    ERROR_TYPE_CMD = 0,            /* ��������� */
    FILE_TYPE_CMD,                 /* �����ļ������� */
    NUM_TYPE_CMD,                  /* �������ò��������� */
    QUIT_TYPE_CMD,                 /* �˳����� */
    SHUTDOWN_WIFI_TYPE_CMD,        /* SHUTDOWN WCPU���� */
};


typedef struct cmd_type_st
{
    int32       cmd_type;
    uint8       cmd_name[DOWNLOAD_CMD_LEN];
    uint8       cmd_para[DOWNLOAD_CMD_PARA_LEN];

}CMD_TYPE_STRUCT;

typedef struct firmware_globals_st
{
    int32            al_count[CFG_FILE_TOTAL];      /*�洢ÿ��cfg�ļ���������Ч���������*/
    CMD_TYPE_STRUCT *apst_cmd[CFG_FILE_TOTAL];      /*�洢ÿ��cfg�ļ�����Ч����*/
    uint8            auc_CfgVersion[VERSION_LEN];   /*�洢cfg�ļ������õİ汾����Ϣ*/
    uint8            auc_DevVersion[VERSION_LEN];   /*�洢����ʱdevice���ϱ��İ汾����Ϣ*/
}FIRMWARE_GLOBALS_STRUCT;

typedef struct _firmware_mem
{
    /*����firmware file���ݵ�buffer���Ƚ��ļ��������buffer�У�Ȼ��������device buffer����*/
    uint8 *pucDataBuf;
    /* pucDataBuf�ĳ��� */
    uint32 ulDataBufLen;
    
    #define CMD_BUFF_LEN       (256)
    uint8 *puc_recv_cmd_buff;
    uint8 *puc_send_cmd_buff;
}FIRMWARE_MEM;

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/

uint8 *g_auc_cfg_path[CFG_FILE_TOTAL] =
                    {
                        WIFI_CFG_PATH,
                        RAM_CHECK_CFG_PATH,
                    };

/*�洢cfg�ļ���Ϣ������cfg�ļ�ʱ��ֵ�����ص�ʱ��ʹ�øñ���*/
FIRMWARE_GLOBALS_STRUCT  g_st_cfg_info;

uint32 g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : firmware_read_msg
 ��������  : host����device��������Ϣ
 �������  : data: ������Ϣ��buffer
             len : ����buffer�ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ����򷵻�ʵ�ʽ��յĳ���
 ���ú���  : sdio_patch_readsb
 ��������  : recv_expect_result
             check_version
             recv_device_mem

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_read_msg(uint8 *data, int32 len)
{
    int32  l_len;

    if (OAL_UNLIKELY((NULL == data)))
    {
        PS_PRINT_ERR("data is NULL\n ");
        return -EFAIL;
    }

    l_len = sdio_patch_readsb(data, len, READ_MEG_TIMEOUT);
    PS_PRINT_DBG("Receive l_len=[%d], data = [%s]\n", l_len, data);

    return l_len;
}

static int32 firmware_read_msg_timeout(uint8 *data, int32 len, uint32 timeout)
{
    int32  l_len;

    if (OAL_UNLIKELY((NULL == data)))
    {
        PS_PRINT_ERR("data is NULL\n ");
        return -EFAIL;
    }

    l_len = sdio_patch_readsb(data, len, timeout);
    PS_PRINT_DBG("Receive l_len=[%d], data = [%s]\n", l_len, data);

    return l_len;
}

/*****************************************************************************
 �� �� ��  : firmware_send_msg
 ��������  : host��device������Ϣ
 �������  : data: ����buffer
             len : �������ݵĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ����򷵻�ʵ�ʷ��͵ĳ���
 ���ú���  : sdio_patch_writesb
 ��������  : msg_send_and_recv_except
             check_version
             number_type_cmd_send

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_send_msg(uint8 *data, int32 len)
{
    int32   l_ret;

    PS_PRINT_DBG("len = %d\n", len);
#ifdef HW_DEBUG
    print_hex_dump_bytes("firmware_send_msg :", DUMP_PREFIX_ADDRESS, data,
                        (len < 128 ? len : 128));
#endif
    l_ret = sdio_patch_writesb(data, len);

    return l_ret;
}

static FIRMWARE_MEM * firmware_mem_request(void)
{
    int32 ret;
    FIRMWARE_MEM * firmware_mem = NULL;
    
    firmware_mem = oal_kzalloc(sizeof(FIRMWARE_MEM),OAL_GFP_KERNEL);
    if (NULL ==  firmware_mem)
    {
        PS_PRINT_ERR("g_st_firmware_mem KMALLOC failed\n");
        ret = -EFAIL;
        goto alloc_g_st_firmware_mem_fail;
    }
        
    firmware_mem->ulDataBufLen = oal_sdio_func_max_req_size(oal_get_sdio_default_handler());
    PS_PRINT_INFO("sdio max transmit size is [%d]\n",  firmware_mem->ulDataBufLen);
    if (firmware_mem->ulDataBufLen < HISDIO_BLOCK_SIZE)
    {
        PS_PRINT_ERR("sdio max transmit size [%d] is error!\n",  firmware_mem->ulDataBufLen);
        ret = -EFAIL;
        goto alloc_pucDataBuf_fail;
    }

    do
    {
        PS_PRINT_INFO("try to malloc firmware download file buf len is [%d]\n", firmware_mem->ulDataBufLen);
        firmware_mem->pucDataBuf = (uint8 *)oal_memalloc(firmware_mem->ulDataBufLen);
        if (NULL ==  firmware_mem->pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem len [%d] fail, continue to try in a smaller size\n", firmware_mem->ulDataBufLen);
            firmware_mem->ulDataBufLen =  firmware_mem->ulDataBufLen >> 1;
        }
    }while((NULL == firmware_mem->pucDataBuf) && (firmware_mem->ulDataBufLen >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == firmware_mem->pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf KMALLOC failed\n");
        ret = -EFAIL;
        goto alloc_pucDataBuf_fail;
    }
    PS_PRINT_INFO("download firmware file buf len is [%d]\n", firmware_mem->ulDataBufLen);
    
    firmware_mem->puc_recv_cmd_buff = (uint8 *)oal_memalloc(CMD_BUFF_LEN);
    if (NULL == firmware_mem->puc_recv_cmd_buff)
    {
        PS_PRINT_ERR("puc_recv_cmd_buff KMALLOC failed\n");
        ret = -EFAIL;
        goto alloc_puc_recv_cmd_buff_fail;
    }
    
    firmware_mem->puc_send_cmd_buff = (uint8 *)oal_memalloc(CMD_BUFF_LEN);
    if (NULL == firmware_mem->puc_send_cmd_buff)
    {
        PS_PRINT_ERR("puc_recv_cmd_buff KMALLOC failed\n");
        ret = -EFAIL;
        goto alloc_puc_send_cmd_buff_fail;
    }

    return firmware_mem;
    
alloc_puc_send_cmd_buff_fail:
    oal_free(firmware_mem->puc_recv_cmd_buff);
alloc_puc_recv_cmd_buff_fail:
    oal_free(firmware_mem->pucDataBuf);
alloc_pucDataBuf_fail:
    oal_free(firmware_mem);
    firmware_mem = NULL;
alloc_g_st_firmware_mem_fail:
    return firmware_mem;
}

static void firmware_mem_free(FIRMWARE_MEM * firmware_mem)
{
    if(NULL == firmware_mem)
    {
        PS_PRINT_ERR("g_firmware_mem_mutex is null\n");
        return;
    }  
    if(NULL != firmware_mem->puc_send_cmd_buff)
    {
        oal_free(firmware_mem->puc_send_cmd_buff);
    }
    if(NULL != firmware_mem->puc_recv_cmd_buff)
    {
        oal_free(firmware_mem->puc_recv_cmd_buff);
    }
    if(NULL != firmware_mem->pucDataBuf)
    {
        oal_free(firmware_mem->pucDataBuf);
    }
    oal_free(firmware_mem);
    firmware_mem = NULL;
}

/*****************************************************************************
 �� �� ��  : recv_expect_result
 ��������  : ����host����device��ȷ���ص�����
 �������  : expect: ����device��ȷ���ص�����
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_read_msg
 ��������  : msg_send_and_recv_except
             exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 recv_expect_result(const uint8 *expect, FIRMWARE_MEM * firmware_mem)
{
    int32 l_len;
    int32 i;

    if (!OAL_STRLEN(expect))
    {
        PS_PRINT_DBG("not wait device to respond!\n");
        return SUCC;
    }
    if(NULL == firmware_mem || NULL == firmware_mem->puc_recv_cmd_buff)
    {
        PS_PRINT_ERR("puc_recv_cmd_buff = NULL \n");
        return -EFAIL;
    }
    oal_memset(firmware_mem->puc_recv_cmd_buff, 0, CMD_BUFF_LEN);
    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_len = firmware_read_msg(firmware_mem->puc_recv_cmd_buff, CMD_BUFF_LEN);
        if (0 > l_len)
        {
            PS_PRINT_ERR("recv result fail\n");
            return -EFAIL;
        }
        if (!oal_memcmp(firmware_mem->puc_recv_cmd_buff, expect, OAL_STRLEN(expect)))
        {
            PS_PRINT_DBG(" send SUCC, expect [%s] ok\n", expect);
            return SUCC;
        }
        else
        {
            PS_PRINT_WARNING(" error result[%s], expect [%s], read result again\n", firmware_mem->puc_recv_cmd_buff, expect);
        }
    }

    return -EFAIL;
}
static int32 recv_expect_result_timeout(const uint8 *expect, FIRMWARE_MEM * firmware_mem, uint32 timeout)
{
    int32 l_len;

    if (!OAL_STRLEN(expect))
    {
        PS_PRINT_DBG("not wait device to respond!\n");
        return SUCC;
    }

    oal_memset(firmware_mem->puc_recv_cmd_buff, 0, CMD_BUFF_LEN);
    l_len = firmware_read_msg_timeout(firmware_mem->puc_recv_cmd_buff, CMD_BUFF_LEN, timeout);
    if (0 > l_len)
    {
        PS_PRINT_ERR("recv result fail\n");
        return -EFAIL;
    }

    if (!oal_memcmp(firmware_mem->puc_recv_cmd_buff, expect, OAL_STRLEN(expect)))
    {
        PS_PRINT_DBG(" send SUCC, expect [%s] ok\n", expect);
        return SUCC;
    }
    else
    {
        PS_PRINT_WARNING(" error result[%s], expect [%s], read result again\n",
            firmware_mem->puc_recv_cmd_buff, expect);
    }

    return -EFAIL;
}


/*****************************************************************************
 �� �� ��  : msg_send_and_recv_except
 ��������  : host��device������Ϣ���ȴ�device������Ϣ
 �������  : data  : ����buffer
             len   : �������ݵĳ���
             expect: ����device�ظ�������
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : firmware_send_msg
             recv_expect_result
 ��������  : down_firmware_file
             exec_quit_type_cmd
             exec_quit_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 msg_send_and_recv_except(uint8 *data, int32 len, const uint8 *expect, FIRMWARE_MEM * firmware_mem)
{
    int32  i;
    int32  l_ret;

    for(i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_ret = firmware_send_msg(data, len);
        if (0 > l_ret)
        {
            continue;
        }

        l_ret = recv_expect_result(expect, firmware_mem);
        if (0 == l_ret)
        {
            return SUCC;
        }
    }

    return -EFAIL;
}

/*****************************************************************************
 �� �� ��  : malloc_cmd_buf
 ��������  : ����cfg�ļ����������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_cfg_info_buf: ������cfg�ļ����ݵ�buffer
             ul_index        : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : NULL��ʾ�����ڴ�ʧ�ܣ����򷵻�ָ�򱣴����cfg�ļ�����������׵�ַ
 ���ú���  :
 ��������  : firmware_parse_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static void *malloc_cmd_buf(uint8 *puc_cfg_info_buf, uint32 ul_index)
{
    int32           l_len;
    uint8          *flag;
    uint8          *p_buf;

    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("malloc_cmd_buf: buf is NULL!\n");
        return NULL;
    }

    /* ͳ��������� */
    flag = puc_cfg_info_buf;
    g_st_cfg_info.al_count[ul_index] = 0;
    while(NULL != flag)
    {
        /* һ����ȷ�������н�����Ϊ ; */
        flag = OAL_STRCHR(flag, CMD_LINE_SIGN);
        if (NULL == flag)
        {
            break;
        }
        g_st_cfg_info.al_count[ul_index]++;
        flag++;
    }
    PS_PRINT_DBG("cfg file cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    /* ����洢����ռ� */
    l_len = ((g_st_cfg_info.al_count[ul_index]) + CFG_INFO_RESERVE_LEN) * sizeof(struct cmd_type_st);
    p_buf = oal_memalloc(l_len);
    if (NULL == p_buf)
    {
        PS_PRINT_ERR("kmalloc cmd_type_st fail\n");
        return NULL;
    }
    oal_memset((void *)p_buf, 0, l_len);

    return p_buf;
}

/*****************************************************************************
 �� �� ��  : delete_space
 ��������  : ɾ���ַ������߶���Ŀո�
 �������  : string: ԭʼ�ַ���
             len   : �ַ����ĳ���
 �������  : ��
 �� �� ֵ  : ���󷵻�NULL�����򷵻�ɾ�����߿ո��Ժ��ַ������׵�ַ
 ���ú���  :
 ��������  : firmware_parse_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static uint8 *delete_space(uint8 *string, int32 *len)
{
    int i;

    if ((NULL == string) || (NULL == len))
    {
        return NULL;
    }

    /* ɾ��β���Ŀո� */
    for(i = *len - 1; i >= 0; i--)
    {
        if (COMPART_KEYWORD != string[i])
        {
            break;
        }
        string[i] = '\0';
    }
    /* ���� */
    if (i < 0)
    {
        PS_PRINT_ERR(" string is Space bar\n");
        return NULL;
    }
    /* ��for����м�ȥ1���������1 */
    *len = i + 1;

    /* ɾ��ͷ���Ŀո� */
    for(i = 0; i < *len; i++)
    {
        if (COMPART_KEYWORD != string[i])
        {
            /* ��ȥ�ո�ĸ��� */
            *len = *len - i;
            return &string[i];
        }
    }

    return NULL;
}

/*************************************************************************************
 �� �� ��  : open_file_to_readm
 ��������  : ���ļ�������read mem������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش��ļ���������
 ���ú���  :
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/
static oal_file_stru*  open_file_to_readm(uint8 *name)
{
    oal_file_stru *fp;
    uint8 *file_name = NULL;

    if (WARN_ON(NULL == name))
    {
        file_name = "/data/memdump/readm_wifi";
    }
    else
    {
        file_name = name;
    }
    fp = oal_file_open(file_name, (OAL_O_CREAT | OAL_O_RDWR), 0);

    return fp;
}

/*************************************************************************************
 �� �� ��  : recv_device_mem
 ��������  : ����device�����������ڴ棬���浽ָ�����ļ���
 �������  : fp : �����ڴ���ļ�ָ��
             len: ��Ҫ������ڴ�ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ����򷵻�ʵ�ʱ�����ڴ�ĳ���
 ���ú���  : read_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/
static int32 recv_device_mem(oal_file_stru *fp, uint8 *pucDataBuf, int32 len)
{
    int32 l_ret = -EFAIL;
    mm_segment_t fs;
    uint8 retry = 3;
    int32 lenbuf = 0;

    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("fp is error,fp = 0x%p\n", fp);
        return -EFAIL;
    }

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf is NULL\n");
        return -EFAIL;
    }

    PS_PRINT_DBG("expect recv len is [%d]\n", len);

    fs = get_fs();
    set_fs(KERNEL_DS);
    PS_PRINT_DBG("pos = %d\n", (int)OAL_FILE_POS(fp));
    while (len > lenbuf)
    {
        l_ret = firmware_read_msg(pucDataBuf + lenbuf, len - lenbuf);
        if (l_ret > 0)
        {
            lenbuf += l_ret;
        }
        else
        {
            retry--;
            lenbuf = 0;
            if (0 == retry)
            {
                l_ret = -EFAIL;
                PS_PRINT_ERR("time out\n");
                break;
            }
        }
    }

    if (len <= lenbuf)
    {
        oal_file_write(fp, pucDataBuf, len);
    }
    set_fs(fs);

    return l_ret;
}

/*************************************************************************************
 �� �� ��  : check_version
 ��������  : ���������device�汾�ţ������device�ϱ��İ汾�ź�host�İ汾���Ƿ�ƥ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : firmware_send_msg
             firmware_read_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/
static int32 check_version(FIRMWARE_MEM * firmware_mem)
{
    int32   l_ret;
    int32   l_len;
    int32   i;
    
    PS_PRINT_DBG("enter\n");

    if(NULL == firmware_mem ||
        NULL == firmware_mem->puc_recv_cmd_buff || 
        NULL == firmware_mem->puc_send_cmd_buff)
    {
        PS_PRINT_ERR("MEM IS NULL \n");
        return -EFAIL;
    }

    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        PS_PRINT_DBG("loop index %d\n", i);
        oal_memset(firmware_mem->puc_send_cmd_buff, 0, CMD_BUFF_LEN);

        oal_memcopy(firmware_mem->puc_send_cmd_buff, (uint8 *)VER_CMD_KEYWORD, OAL_STRLEN(VER_CMD_KEYWORD));
        l_len = OAL_STRLEN(VER_CMD_KEYWORD);

        firmware_mem->puc_send_cmd_buff[l_len] = COMPART_KEYWORD;
        l_len++;
        
        l_len = HISDIO_ALIGN_4_OR_BLK(l_len+1);

#if 0   //dead code
        if(CMD_BUFF_LEN < l_len)
        {
            PS_PRINT_ERR("len out of range\r\n");
            return -EFAIL;
        }
#endif

        l_ret = firmware_send_msg(firmware_mem->puc_send_cmd_buff, l_len);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send version fail![%d]\n", i);
            continue;
        }

        oal_memset(g_st_cfg_info.auc_DevVersion, 0, VERSION_LEN);
        oal_memset(firmware_mem->puc_recv_cmd_buff, 0, CMD_BUFF_LEN);
        PS_PRINT_DBG("read msg start\n");
        l_ret = firmware_read_msg(firmware_mem->puc_recv_cmd_buff, CMD_BUFF_LEN);
        
        PS_PRINT_DBG("read msg over\n");
        if (0 > l_ret)
        {
            PS_PRINT_ERR("read version fail![%d]\n", i);
            continue;
        }
        oal_memcopy(g_st_cfg_info.auc_DevVersion, firmware_mem->puc_recv_cmd_buff, VERSION_LEN);
        if (!oal_memcmp((int8 *)g_st_cfg_info.auc_DevVersion,
                              (int8 *)g_st_cfg_info.auc_CfgVersion,
                              OAL_STRLEN(g_st_cfg_info.auc_CfgVersion)))
        {
            PS_PRINT_INFO("SUCC: Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
            return SUCC;
        }
        else
        {
            PS_PRINT_ERR("ERROR version,Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
            return -EFAIL;
        }
    }

    return -EFAIL;
}

/*****************************************************************************
 �� �� ��  : number_type_cmd_send
 ��������  : ����number���͵���������͵�device
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ������ʾ�ɹ�
 ���ú���  : firmware_send_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 number_type_cmd_send(uint8 *Key, uint8 *Value, FIRMWARE_MEM * firmware_mem)
{
    int32       l_ret;
    int32       data_len;
    int32       Value_len;
    int32       i;
    int32       n;

    if(NULL == firmware_mem ||
        NULL == firmware_mem->puc_recv_cmd_buff || 
        NULL == firmware_mem->puc_send_cmd_buff)
    {
        PS_PRINT_ERR("MEM IS NULL \n");
        return -EFAIL;
    }
    
    if(CMD_BUFF_LEN< OAL_STRLEN(Key)+OAL_STRLEN(Value)+10)
    {
        PS_PRINT_ERR("the cmd string must be error, key=%s, vlaue=%s \n", Key, Value);
        return -EFAIL;
    }
    
    Value_len = OAL_STRLEN((int8 *)Value);

    oal_memset(firmware_mem->puc_recv_cmd_buff, 0, CMD_BUFF_LEN);
    oal_memset(firmware_mem->puc_send_cmd_buff, 0, CMD_BUFF_LEN);

    data_len = OAL_STRLEN(Key);
    oal_memcopy(firmware_mem->puc_send_cmd_buff, Key, data_len);

    firmware_mem->puc_send_cmd_buff[data_len] = COMPART_KEYWORD;
    data_len = data_len + 1;

    for (i = 0, n = 0; (i <= Value_len) && (n < INT32_STR_LEN); i++)
    {
        if ((',' == Value[i]) || (i == Value_len ))
        {
            PS_PRINT_DBG("auc_num = %s, i = %d, n = %d\n", firmware_mem->puc_recv_cmd_buff,  i, n);
            if (0 == n)
            {
                continue;
            }
            oal_memcopy((uint8 *)&firmware_mem->puc_send_cmd_buff[data_len], 
                firmware_mem->puc_recv_cmd_buff, n);
            data_len = data_len + n;

            firmware_mem->puc_send_cmd_buff[data_len] = COMPART_KEYWORD;
            data_len = data_len + 1;

            oal_memset(firmware_mem->puc_recv_cmd_buff, 0, INT32_STR_LEN);
            n = 0;
        }
        else if (COMPART_KEYWORD == Value[i])
        {
            continue;
        }
        else
        {
            firmware_mem->puc_recv_cmd_buff[n] = Value[i];
            n++;
        }

    }
    firmware_mem->puc_send_cmd_buff[data_len+1]='\0';
    PS_PRINT_DBG("cmd=%s\r\n", firmware_mem->puc_send_cmd_buff);
    l_ret = firmware_send_msg(firmware_mem->puc_send_cmd_buff, data_len);

    return l_ret;
}



/*****************************************************************************
 �� �� ��  : parse_file_cmd
 ��������  : ����file�������
 �������  : string   : file����Ĳ���
             addr     : ���͵����ݵ�ַ
             file_path: �����ļ���·��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : string_to_num
 ��������  : exec_file_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 parse_file_cmd(uint8 *string, ulong *addr, int8 **file_path)
{
    uint8 *tmp;
    int32 count = 0;
    int8 *after = NULL;

    if (string == NULL || addr == NULL || file_path == NULL)
    {
        PS_PRINT_ERR("param is error!\n");
        return -EFAIL;
    }

    /*��÷��͵��ļ��ĸ������˴�����Ϊ1��string�ַ����ĸ�ʽ������"1,0xXXXXX,file_path"*/
    tmp = string;
    
    while(COMPART_KEYWORD == *tmp)
    {
        tmp++;
    }
    count = oal_simple_strtoul(tmp,NULL,10);
    if (count != FILE_COUNT_PER_SEND)
    {
        PS_PRINT_ERR("the count of send file must be 1, count = [%d]\n", count);
        return -EFAIL;
    }

    /*��tmpָ���ַ������ĸ*/
    tmp = OAL_STRCHR(string, ',');
    if (tmp == NULL)
    {
        PS_PRINT_ERR("param string is err!\n");
        return -EFAIL;
    }
    else
    {
        tmp++;
        while(COMPART_KEYWORD == *tmp)
        {
            tmp++;
        }
    }

    *addr = oal_simple_strtoul(tmp, &after, 16);

    PS_PRINT_DBG("file to send addr:[0x%lx]\n", *addr);

    /*"1,0xXXXX,file_path"*/
    /*         ^          */
    /*       after        */
    after++;
    while(COMPART_KEYWORD == *after)
    {
        after++;
    }

    PS_PRINT_DBG("after:[%s]\n", after);

    *file_path = after;

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : sdio_read_device_mem
 ��������  : ��device����bootloaderʱ��DEVICE��ȡ�ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : С��0��ʾʧ��
 ���ú���  :

 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��5��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 read_device_mem(p_st_wifi_demp_mem_info pst_mem_dump_info,
                                  oal_file_stru *fp, FIRMWARE_MEM * firmware_mem)
{
    int32 ret = 0;
    uint32 size = 0;
    uint32 offset;
    uint32 remainder = pst_mem_dump_info->size;

    offset=0;
    if(NULL == firmware_mem || NULL == firmware_mem->puc_send_cmd_buff)
    {
        PS_PRINT_ERR("puc_send_cmd_buff = NULL \n");
        return -EFAIL;
    }
    while(remainder > 0)
    {
        oal_memset(firmware_mem->puc_send_cmd_buff, 0, CMD_BUFF_LEN);

        size = OAL_MIN(remainder, firmware_mem->ulDataBufLen);
        OAL_SPRINTF(firmware_mem->puc_send_cmd_buff, CMD_BUFF_LEN, "%s%c0x%lx%c%d%c",
                                                RMEM_CMD_KEYWORD,
                                                COMPART_KEYWORD,
                                                pst_mem_dump_info->mem_addr + offset,
                                                COMPART_KEYWORD,
                                                size,
                                                COMPART_KEYWORD);
        PS_PRINT_DBG("read mem cmd:[%s]\n", firmware_mem->puc_send_cmd_buff);
        ret = firmware_send_msg(firmware_mem->puc_send_cmd_buff, 
            OAL_STRLEN(firmware_mem->puc_send_cmd_buff) );
        if(ret < 0)
        {
            PS_PRINT_ERR("wifi mem dump fail, mem_addr is [0x%lx],ret=%d\n", pst_mem_dump_info->mem_addr, ret);
            break;
        }

        ret = recv_device_mem(fp, firmware_mem->pucDataBuf, size);
        if(ret < 0)
        {
            PS_PRINT_ERR("wifi mem dump fail, mem_addr is [0x%lx],ret=%d\n", pst_mem_dump_info->mem_addr, ret);
            break;
        }

        offset += size;

        remainder -= size;
    }

    return ret;
}

static int32 read_mem(uint8 *Key, uint8 *Value, FIRMWARE_MEM * firmware_mem)
{
    int32 l_ret = -EFAIL;
    int32 size;
    uint8 *flag;
    oal_file_stru *fp;
    struct st_wifi_dump_mem_info read_memory;
    OAL_MEMZERO(&read_memory, sizeof(struct st_wifi_dump_mem_info));

    flag = OAL_STRCHR(Value, ',');
    if (NULL == flag)
    {
        PS_PRINT_ERR("RECV LEN ERROR..\n");
        return -EFAIL;
    }
    if(NULL == firmware_mem ||
        NULL == firmware_mem->pucDataBuf)
    {
        PS_PRINT_ERR("MEM IS NULL \n");
        return -EFAIL;
    }
    
    flag++;
    PS_PRINT_DBG("recv len [%s]\n", flag);
    while(COMPART_KEYWORD == *flag)
    {
        flag++;
    }
    size = oal_simple_strtoul(flag,NULL,10);

    fp = open_file_to_readm(NULL);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
        return SUCC;
    }
    read_memory.mem_addr=(uint32)oal_simple_strtoul(Value, NULL, 16);
    read_memory.size=(uint32)size;
    l_ret = read_device_mem(&read_memory, fp, firmware_mem);

    oal_file_close(fp);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��number���͵�����
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : check_version
             number_type_cmd_send
             recv_expect_result
             open_file_to_readm
             string_to_num
             recv_device_mem
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 exec_number_type_cmd(uint8 *Key, uint8 *Value, FIRMWARE_MEM * firmware_mem)
{
    int32       l_ret = -EFAIL;

    if (!oal_memcmp(Key, VER_CMD_KEYWORD, OAL_STRLEN(VER_CMD_KEYWORD)))
    {
        l_ret = check_version(firmware_mem);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("check version FAIL [%d]\n", l_ret);
            return -EFAIL;
        }
    }

    if (!oal_strcmp((int8 *)Key, WMEM_CMD_KEYWORD))
    {
        l_ret = number_type_cmd_send(Key, Value, firmware_mem);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
            return l_ret;
        }


        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK, firmware_mem);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }

    }
    else if (!oal_strcmp((int8 *)Key, JUMP_CMD_KEYWORD))
    {
        g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;
        l_ret = number_type_cmd_send(Key, Value, firmware_mem);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
            return l_ret;
        }

        /*100000ms timeout*/
        l_ret = recv_expect_result_timeout(MSG_FROM_DEV_JUMP_OK, firmware_mem, READ_MEG_JUMP_TIMEOUT);
        if (l_ret >= 0)
        {
            PS_PRINT_INFO("JUMP success!\n");
            return l_ret;
        }
        else
        {
            PS_PRINT_ERR("CMD JUMP timeout! l_ret=%d\n", l_ret);
            g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_FAIL;
            return l_ret;
        }
    }
    else if (!oal_strcmp((int8 *)Key, RMEM_CMD_KEYWORD))
    {
        l_ret = read_mem(Key, Value, firmware_mem);
    }

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��quit���͵�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : msg_send_and_recv_except
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 exec_quit_type_cmd(FIRMWARE_MEM * firmware_mem)
{
    int32   l_ret;
    int32   l_len;
    
    if(NULL == firmware_mem || NULL == firmware_mem->puc_send_cmd_buff)
    {
        PS_PRINT_ERR("puc_send_cmd_buff = NULL \n");
        return -EFAIL;
    }
    
    oal_memset(firmware_mem->puc_send_cmd_buff, 0, 8);

    oal_memcopy(firmware_mem->puc_send_cmd_buff, (uint8 *)QUIT_CMD_KEYWORD, OAL_STRLEN(QUIT_CMD_KEYWORD));
    l_len = OAL_STRLEN(QUIT_CMD_KEYWORD);

    firmware_mem->puc_send_cmd_buff[l_len] = COMPART_KEYWORD;
    l_len++;

    l_ret = msg_send_and_recv_except(firmware_mem->puc_send_cmd_buff, l_len, MSG_FROM_DEV_QUIT_OK, firmware_mem);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��file���͵�����
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : parse_file_cmd
             msg_send_and_recv_except
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 exec_file_type_cmd(uint8 *Key, uint8 *Value, FIRMWARE_MEM * firmware_mem)
{
    ulong addr;
    uint32 addr_send;
    int8 *path;
    int32 ret;
    uint32 file_len;
    uint32 per_send_len;
    uint32 send_count;
    int32 rdlen;
    uint32 i;
    uint32 offset = 0;
    oal_file_stru * fp;
    
    if(NULL == firmware_mem ||
        NULL == firmware_mem->pucDataBuf ||
        NULL == firmware_mem->puc_send_cmd_buff || 
        NULL == firmware_mem->pucDataBuf)
    {
        PS_PRINT_ERR("mem is NULL \n");
        return -EFAIL;
    }
    
    ret = parse_file_cmd(Value, &addr, &path);
    if (ret < 0)
    {
        PS_PRINT_ERR("parse file cmd fail!\n");
        return ret;
    }

    PS_PRINT_INFO("download firmware:%s\n", path);

    fp = oal_file_open(path,(OAL_O_RDONLY),0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("filp_open [%s] fail!!, fp=%p\n", path, fp);
        fp = NULL;
        return -EFAIL;
    }

    /* ��ȡfile�ļ���С */
    file_len = oal_file_lseek(fp, 0, OAL_SEEK_END);
    
    /* �ָ�fp->f_pos���ļ���ͷ */
    oal_file_lseek(fp, 0, OAL_SEEK_SET);  

    PS_PRINT_DBG("file len is [%d]\n", file_len);

    per_send_len = (firmware_mem->ulDataBufLen > file_len) ? file_len : firmware_mem->ulDataBufLen;
    send_count = (file_len + per_send_len - 1)/per_send_len;

    for (i = 0; i < send_count; i++)
    {
        rdlen = oal_file_read(fp, firmware_mem->pucDataBuf, per_send_len);
        if (rdlen > 0)
        {
            PS_PRINT_DBG("len of kernel_read is [%d], i=%d\n", rdlen, i);
            OAL_FILE_POS(fp) += rdlen;
        }
        else
        {
            PS_PRINT_ERR("len of kernel_read is error! ret=[%d], i=%d\n", rdlen, i);
            oal_file_close(fp);
            return -EFAIL;
        }

        addr_send = addr + offset;
        PS_PRINT_DBG("send addr is [0x%x], i=%d\n", addr_send, i);

        snprintf(firmware_mem->puc_send_cmd_buff, CMD_BUFF_LEN, "%s%c%d%c0x%x%c",
                                            FILES_CMD_KEYWORD,
                                            COMPART_KEYWORD,
                                            FILE_COUNT_PER_SEND,
                                            COMPART_KEYWORD,
                                            addr_send,
                                            COMPART_KEYWORD);

        /*���͵�ַ*/
        PS_PRINT_DBG("send file addr cmd is [%s]\n", firmware_mem->puc_send_cmd_buff);
        ret = msg_send_and_recv_except(firmware_mem->puc_send_cmd_buff, 
           OAL_STRLEN(firmware_mem->puc_send_cmd_buff), MSG_FROM_DEV_READY_OK, firmware_mem);
        if (0 > ret)
        {
            PS_PRINT_ERR("SEND [%s] error\n", firmware_mem->puc_send_cmd_buff);
            oal_file_close(fp);
            return -EFAIL;
        }

        /* Wait at least 5 ms */
        usleep_range(FILE_CMD_WAIT_TIME_MIN, FILE_CMD_WAIT_TIME_MAX);

        /*�����ļ�����*/
        ret = msg_send_and_recv_except(firmware_mem->pucDataBuf, rdlen, MSG_FROM_DEV_FILES_OK, firmware_mem);
        if(0 > ret)
        {
            PS_PRINT_ERR(" send data fail\n");
            oal_file_close(fp);
            
            return -EFAIL;
        }

        offset += rdlen;
    }
    oal_file_close(fp);

    /*���͵ĳ���Ҫ���ļ��ĳ���һ��*/
    if (offset != file_len)
    {
        PS_PRINT_ERR("file send len is err! send len is [%d], file len is [%d]\n", offset, file_len);
        return -EFAIL;
    }

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : execute_download_cmd
 ��������  : ִ��firmware download������
 �������  : cmd_type: �������������
             cmd_name: ����Ĺؼ���
             cmd_para: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ��Ǹ�����ʾ�ɹ�
 ���ú���  : exec_file_type_cmd
             exec_number_type_cmd
             exec_quit_type_cmd
 ��������  : firmware_download

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 execute_download_cmd(int32 cmd_type, uint8 *cmd_name, uint8 *cmd_para, FIRMWARE_MEM * firmware_mem)
{
    int32 l_ret;

    switch(cmd_type)
    {
         case FILE_TYPE_CMD:
            PS_PRINT_DBG(" command type FILE_TYPE_CMD\n");
            l_ret = exec_file_type_cmd(cmd_name, cmd_para, firmware_mem);
            break;
         case NUM_TYPE_CMD:
            PS_PRINT_DBG(" command type NUM_TYPE_CMD\n");
            l_ret = exec_number_type_cmd(cmd_name, cmd_para, firmware_mem);
            break;
         case QUIT_TYPE_CMD:
            PS_PRINT_DBG(" command type QUIT_TYPE_CMD\n");
            l_ret = exec_quit_type_cmd(firmware_mem);
            break;
         default:
            PS_PRINT_ERR("command type error[%d]\n", cmd_type);
            l_ret = -EFAIL;
            break;
    }

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_read_cfg
 ��������  : ��ȡcfg�ļ������ݣ��ŵ�������̬�����buffer��
 �������  : puc_CfgPatch    : cfg�ļ���·��
             puc_read_buffer : ����cfg�ļ����ݵ�buffer
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  :
 ��������  : firmware_get_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_read_cfg(uint8 *puc_CfgPatch, uint8 *puc_read_buffer)
{
    oal_file_stru    *fp;
    int32                   l_ret;

    if ((NULL == puc_CfgPatch) || (NULL == puc_read_buffer))
    {
        PS_PRINT_ERR("para is NULL\n");
        return -EFAIL;
    }
    
    fp = oal_file_open(puc_CfgPatch,(OAL_O_RDONLY),0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("open file %s fail, fp=%p\n", puc_CfgPatch, fp);
        fp = NULL;
        return -EFAIL;
    }

    oal_memset(puc_read_buffer, 0, READ_CFG_BUF_LEN);
    l_ret = oal_file_read(fp,puc_read_buffer,READ_CFG_BUF_LEN);
    oal_file_close(fp);
    fp = NULL;

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_parse_cmd
 ��������  : ����cfg�ļ��е�����
 �������  : puc_cfg_buffer: ����cfg�ļ����ݵ�buffer
             puc_cmd_name  : ��������Ժ�����ؼ��ֵ�buffer
             puc_cmd_para  : ��������Ժ����������buffer
 �������  : ��
 �� �� ֵ  : �������������
 ���ú���  : delete_space
 ��������  : firmware_parse_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_parse_cmd(uint8 *puc_cfg_buffer, uint8 *puc_cmd_name, uint8 *puc_cmd_para)
{
    int32       l_ret;
    int32       l_cmdlen;
    int32       l_paralen;
    uint8      *begin;
    uint8      *end;
    uint8      *link;
    uint8      *handle;
    uint8      *handle_temp;

    begin = puc_cfg_buffer;
    if((NULL == puc_cfg_buffer) || (NULL == puc_cmd_name) || (NULL == puc_cmd_para))
    {
        PS_PRINT_ERR("para is NULL\n");
        return ERROR_TYPE_CMD;
    }

    /* ע���� */
    if ('@' == puc_cfg_buffer[0])
    {
        return ERROR_TYPE_CMD;
    }

    /* �����У������˳������� */
    link = OAL_STRCHR((int8 *)begin, '=');
    if (NULL == link)
    {
        /* �˳������� */
        if (NULL != OAL_STRSTR((int8 *)puc_cfg_buffer, QUIT_CMD_KEYWORD))
        {
            return QUIT_TYPE_CMD;
        }
        return ERROR_TYPE_CMD;
    }

    /* �����У�û�н����� */
    end = OAL_STRCHR(link, ';');
    if (NULL == end)
    {
        return ERROR_TYPE_CMD;
    }

    l_cmdlen = link - begin;

    /* ɾ���ؼ��ֵ����߿ո� */
    handle = delete_space((uint8 *)begin, &l_cmdlen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }

    /* �ж��������� */
    if (!oal_memcmp(handle, (uint8 *)FILE_TYPE_CMD_KEY, OAL_STRLEN((uint8 *)FILE_TYPE_CMD_KEY)))
    {
        handle_temp = OAL_STRSTR(handle, (uint8 *)FILE_TYPE_CMD_KEY);
        if (NULL == handle_temp)
        {
            PS_PRINT_ERR("'ADDR_FILE_'is not handle child string, handle=%s", handle);
            return ERROR_TYPE_CMD;
        }
        handle= handle_temp + OAL_STRLEN(FILE_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OAL_STRLEN(FILE_TYPE_CMD_KEY);
        l_ret = FILE_TYPE_CMD;
    }
    else if (!oal_memcmp(handle, (uint8 *)NUM_TYPE_CMD_KEY, OAL_STRLEN(NUM_TYPE_CMD_KEY)))
    {
        handle_temp = OAL_STRSTR(handle, (uint8 *)NUM_TYPE_CMD_KEY);
        if (NULL == handle_temp)
        {
            PS_PRINT_ERR("'PARA_' is not handle child string, handle=%s", handle);
            return ERROR_TYPE_CMD;
        }
        handle= handle_temp + OAL_STRLEN(NUM_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OAL_STRLEN(NUM_TYPE_CMD_KEY);
        l_ret = NUM_TYPE_CMD;
    }
    else
    {
        return ERROR_TYPE_CMD;
    }

    if (DOWNLOAD_CMD_LEN < l_cmdlen || 0 > l_cmdlen)
    {
        PS_PRINT_ERR("cmd len out of range!\n");
        return ERROR_TYPE_CMD;
    }
    oal_memcopy(puc_cmd_name, handle, l_cmdlen);

    /* ɾ��ֵ���߿ո� */
    begin = link + 1;
    l_paralen = end - begin;
    if (DOWNLOAD_CMD_PARA_LEN < l_paralen || 0 > l_paralen)
    {
        PS_PRINT_ERR("para len out of range!\n");
        return ERROR_TYPE_CMD;
    }

    handle = delete_space((uint8 *)begin, &l_paralen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }
    oal_memcopy(puc_cmd_para, handle, l_paralen);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_parse_cfg
 ��������  : ����cfg�ļ����������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_cfg_info_buf: ������cfg�ļ����ݵ�buffer
             l_buf_len       : puc_cfg_info_buf�ĳ���
             ul_index        : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : malloc_cmd_buf
             firmware_parse_cmd
 ��������  : firmware_get_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_parse_cfg(uint8 *puc_cfg_info_buf, int32 l_buf_len, uint32 ul_index)
{
    int32           i;
    int32           l_len;
    uint8          *flag;
    uint8          *begin;
    uint8          *end;
    int32           cmd_type;
    uint8           cmd_name[DOWNLOAD_CMD_LEN];
    uint8           cmd_para[DOWNLOAD_CMD_PARA_LEN];
    uint32          cmd_para_len = 0;
    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("puc_cfg_info_buf is NULL!\n");
        return -EFAIL;
    }

    g_st_cfg_info.apst_cmd[ul_index] = (struct cmd_type_st *)malloc_cmd_buf(puc_cfg_info_buf, ul_index);
    if (NULL == g_st_cfg_info.apst_cmd[ul_index])
    {
        PS_PRINT_ERR(" malloc_cmd_buf fail!\n");
        return -EFAIL;
    }

    /* ����CMD BUF*/
    flag = puc_cfg_info_buf;
    l_len = l_buf_len;
    i = 0;
    while((i < g_st_cfg_info.al_count[ul_index]) && (flag < &puc_cfg_info_buf[l_len]))
    {
        /*
         *��ȡ�����ļ��е�һ��,�����ļ�������unix��ʽ.
         *�����ļ��е�ĳһ�к����ַ� @ ����Ϊ����Ϊע����
         */
        begin = flag;
        end   = OAL_STRCHR(flag, '\n');
        if (NULL == end)           /*�ļ������һ�У�û�л��з�*/
        {
            PS_PRINT_DBG("lost of new line!\n");
            end = &puc_cfg_info_buf[l_len];
        }
        else if (end == begin)     /* ����ֻ��һ�����з� */
        {
            PS_PRINT_DBG("blank line\n");
            flag = end + 1;
            continue;
        }
        *end = '\0';

        PS_PRINT_DBG("operation string is [%s]\n", begin);

        oal_memset(cmd_name, 0, DOWNLOAD_CMD_LEN);
        oal_memset(cmd_para, 0, DOWNLOAD_CMD_PARA_LEN);

        cmd_type = firmware_parse_cmd(begin, cmd_name, cmd_para);

        PS_PRINT_DBG("cmd type=[%d],cmd_name=[%s],cmd_para=[%s]\n", cmd_type, cmd_name, cmd_para);

        if (ERROR_TYPE_CMD != cmd_type)/* ��ȷ���������ͣ����� */
        {
            g_st_cfg_info.apst_cmd[ul_index][i].cmd_type = cmd_type;
            oal_memcopy(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name, cmd_name, DOWNLOAD_CMD_LEN);
            oal_memcopy(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para, cmd_para, DOWNLOAD_CMD_PARA_LEN);
            /* ��ȡ���ð汾�� */
            if (!oal_memcmp(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name,
                            VER_CMD_KEYWORD,
                            OAL_STRLEN(VER_CMD_KEYWORD)))
            {
                cmd_para_len = OAL_STRLEN(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para);
                if (VERSION_LEN >= cmd_para_len)
                {
                    oal_memcopy(g_st_cfg_info.auc_CfgVersion,
                        g_st_cfg_info.apst_cmd[ul_index][i].cmd_para,
                        cmd_para_len);
                }
                else
                {
                    PS_PRINT_DBG("cmd_para_len = %d over auc_CfgVersion length", cmd_para_len);
                    return -EFAIL;
                }
                PS_PRINT_DBG("g_CfgVersion = [%s].\n", g_st_cfg_info.auc_CfgVersion);
            }
            i++;
        }
        flag = end + 1;
    }

    /* ����ʵ������������޸����յ�������� */
    g_st_cfg_info.al_count[ul_index] = i;
    PS_PRINT_INFO("effective cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : firmware_get_cfg
 ��������  : ��ȡcfg�ļ����������������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_CfgPatch: cfg�ļ���·��
             ul_index     : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_read_cfg
             firmware_parse_cfg
 ��������  : firmware_cfg_init

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_get_cfg(uint8 *puc_CfgPatch, uint32 ul_index)
{
    uint8   *puc_read_cfg_buf;
    int32   l_readlen;
    int32   l_ret;

    if (NULL == puc_CfgPatch)
    {
        PS_PRINT_ERR("cfg file path is null!\n");
        return -EFAIL;
    }

    /*cfg�ļ��޶���С��2048,���cfg�ļ��Ĵ�Сȷʵ����2048�������޸�READ_CFG_BUF_LEN��ֵ*/
    puc_read_cfg_buf = oal_memalloc(READ_CFG_BUF_LEN);
    if (NULL == puc_read_cfg_buf)
    {
        PS_PRINT_ERR("kmalloc READ_CFG_BUF fail!\n");
        return -EFAIL;
    }

    l_readlen = firmware_read_cfg(puc_CfgPatch, puc_read_cfg_buf);
    if(0 > l_readlen)
    {
        PS_PRINT_ERR("read cfg error!\n");
        oal_free(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }
    /*��1��Ϊ��ȷ��cfg�ļ��ĳ��Ȳ�����READ_CFG_BUF_LEN����Ϊfirmware_read_cfg���ֻ���ȡREAD_CFG_BUF_LEN���ȵ�����*/
    else if (l_readlen > READ_CFG_BUF_LEN - 1)
    {
        PS_PRINT_ERR("cfg file [%s] larger than %d\n", puc_CfgPatch, READ_CFG_BUF_LEN);
        oal_free(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }
    else
    {
        PS_PRINT_DBG("read cfg file [%s] ok, size is [%d]\n", puc_CfgPatch, l_readlen);
    }

    l_ret = firmware_parse_cfg(puc_read_cfg_buf, l_readlen, ul_index);
    if(0 > l_ret)
    {
        PS_PRINT_ERR("parse cfg error!\n");
    }

    oal_free(puc_read_cfg_buf);
    puc_read_cfg_buf = NULL;

    return l_ret;
}

EXPORT_SYMBOL(firmware_download);

#if 0

static int32 print_firmwrae_download_cmd(uint32 ul_index)
{
    int32 i;
    int32 l_cmd_type;
    uint8 *puc_cmd_name;
    uint8 *puc_cmd_para;
    uint32 count;

    count = g_st_cfg_info.al_count[ul_index];
    PS_PRINT_INFO("[%s] download cmd, total count is [%d]\n", g_auc_cfg_path[ul_index], count);

    for (i = 0; i < count; i++)
    {
        l_cmd_type   = g_st_cfg_info.apst_cmd[ul_index][i].cmd_type;
        puc_cmd_name = g_st_cfg_info.apst_cmd[ul_index][i].cmd_name;
        puc_cmd_para = g_st_cfg_info.apst_cmd[ul_index][i].cmd_para;

        PS_PRINT_INFO("cmd[%d]:type[%d], name[%s], para[%s]\n", i, l_cmd_type, puc_cmd_name, puc_cmd_para);
    }

    return 0;
}

static int32 print_cfg_file_cmd(void)
{
    int32 i;

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        print_firmwrae_download_cmd(i);
    }

    return 0;
}
/*****************************************************************************
 �� �� ��  : firmware_cfg_cmd_fill
 ��������  :
 �������  : uint32 index
             uint32 cmd_count
             uint8* cmd_str
 �������  : ��
 �� �� ֵ  : static int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��4��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_cfg_cmd_fill(uint32 index, uint32 cmd_count, uint8* cmd_str)
{
    if ((NULL == cmd_str) || (cmd_count > g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN - 1))
    {
        return -EFAIL;
    }

    g_st_cfg_info.apst_cmd[index][cmd_count].cmd_type = NUM_TYPE_CMD;
    oal_memcopy(g_st_cfg_info.apst_cmd[index][cmd_count].cmd_name, WMEM_CMD_KEYWORD, OAL_STRLEN((uint8 *)WMEM_CMD_KEYWORD) + 1);
    oal_memcopy(g_st_cfg_info.apst_cmd[index][cmd_count].cmd_para, cmd_str, DOWNLOAD_CMD_PARA_LEN);

    return 0;
}
/*****************************************************************************
 �� �� ��  : firmware_cfg_fill
 ��������  :
 �������  : uint32 index
             uint32 cmd_count
 �������  : ��
 �� �� ֵ  : static int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��4��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 firmware_cfg_fill (uint32 index, uint32 cmd_count)
{
    int32  result = 0;
    uint32 count;

    if (CFG_FILE_TOTAL <= index || (0 == cmd_count))
    {
        return -EFAIL;
    }

    count = cmd_count;

    /*ɾ�����һ������: QUIT*/
    count -= 1;

    result  = firmware_cfg_cmd_fill(index, count++, "2,0x50002210,0x351C");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002214,0x301C");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002280,0x5413");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002284,0x2C00");

    /*�������һ������: QUIT*/
    if (count > g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN - 1)
    {
        PS_PRINT_ERR("cfg space overflow, maxlen[0x%x] < reallen[0x%x]",(g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN),count);
        return -EFAIL;
    }
    g_st_cfg_info.apst_cmd[index][count++].cmd_type = QUIT_TYPE_CMD;
    g_st_cfg_info.al_count[index] = count;

    return result;
}

/*****************************************************************************
 �� �� ��  : firmware_cfg_init_extra
 ��������  : firmware���ص�cfg�ļ���ʼ������ȡ������cfg�ļ����������Ľ��������
             g_st_cfg_infoȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_get_cfg
 ��������  : firmware_download_function

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 firmware_cfg_init_extra(void)
{
    oal_int32  result;
    oal_int32  wifi_5g_enable_info = 1;
    //uint32 index = BFGX_AND_WIFI_CFG;
    //uint32 cmd_count = g_st_cfg_info.al_count[BFGX_AND_WIFI_CFG];

    result = get_cust_conf_int32(INI_MODU_WIFI, CHECK_5G_ENABLE, &wifi_5g_enable_info);
    if (0 > result)
    {
        /*��ȡiniʧ�ܣ����Դ�dts�ж�ȡ*/
        result = get_cust_conf_int32(CUST_MODU_DTS, CHECK_5G_ENABLE, &wifi_5g_enable_info);
        if (0 > result)
        {
            PS_PRINT_WARNING("host get wifi 5g enable info fail\n");
            /* ��ȡʧ��,Ĭ��Ϊ5G */
            wifi_5g_enable_info = WIFI_MODE_5G;
        }
        else
        {
            PS_PRINT_INFO("read wifi mode from dts succ\n");
        }
    }
    else
    {
        PS_PRINT_INFO("read wifi mode from ini succ\n");
    }

#if 0
    /*���ж�WIFI�Ƿ���2.4G*/
    if (WIFI_MODE_2_4G == wifi_5g_enable_info)
    {
        result = firmware_cfg_fill(index, cmd_count);
        if (SUCC != result)
        {
            PS_PRINT_ERR("cfg space overflow (err = 0x%x)\n",result);
        }
    }
    else
    {
        result = SUCC;
    }
#endif

    return result;
}
#endif


/*****************************************************************************
 �� �� ��  : sdio_device_mem_dump
 ��������  : firmware����ʱ��ȡwifi���ڴ�
 �������  : pst_mem_dump_info  : ��Ҫ��ȡ���ڴ���Ϣ
             count              : ��Ҫ��ȡ���ڴ�����
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : num_to_string
             recv_device_mem
             open_file_to_readm
 ��������  : wifi_exception_mem_dump

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 device_mem_dump(p_st_wifi_demp_mem_info * pst_mem_dump_info)
{
    oal_file_stru *fp;
    int32 ret = -EFAIL;
    uint32 i=0;
    char filename[100] = {0};
    FIRMWARE_MEM * firmware_mem = NULL;

    oal_time_t_stru time_start, time_stop;
    oal_uint64  trans_us;

#ifdef PLATFORM_DEBUG_ENABLE
    oal_timeval_stru tv;
    oal_rtctime_stru tm;
    OAL_MEMZERO(&tv, sizeof(oal_timeval_stru));
    OAL_MEMZERO(&tm, sizeof(oal_rtctime_stru));
    
    oal_do_gettimeofday(&tv);
    oal_rtc_time_to_tm(tv.tv_sec, &tm);
    PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
           tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
#endif

    if (NULL == pst_mem_dump_info)
    {
        PS_PRINT_ERR("pst_wifi_dump_info is NULL\n");
        return -EFAIL;
    }
    firmware_mem = firmware_mem_request();
    if(NULL == firmware_mem)
    {
        PS_PRINT_ERR("firmware_mem_request fail\n");
        return -EFAIL;
    }

    while( NULL != pst_mem_dump_info[i] )
    {
        time_start = oal_ktime_get();
        /*���ļ���׼������wifi mem dump*/
        oal_memset(filename, 0, sizeof(filename));

#ifdef PLATFORM_DEBUG_ENABLE
        OAL_SPRINTF(filename, sizeof(filename),"/data/memdump/%s_%04d%02d%02d%02d%02d%02d_%s.bin", SDIO_STORE_WIFI_MEM, tm.tm_year + 1900,
           tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, pst_mem_dump_info[i]->file_name);
#else
        OAL_SPRINTF(filename, sizeof(filename),"/data/memdump/%s_%s.bin", SDIO_STORE_WIFI_MEM, pst_mem_dump_info[i]->file_name);
#endif

        PS_PRINT_INFO("readm %s\n",filename);

        fp = open_file_to_readm(filename);
        if (IS_ERR_OR_NULL(fp))
        {
            PS_PRINT_ERR("create file error,fp = 0x%p, filename is [%s]\n", fp, pst_mem_dump_info[i]->file_name);
            break;
        }

        ret = read_device_mem(pst_mem_dump_info[i], fp, firmware_mem);
        if (ret < 0)
        {
            oal_file_close(fp);
            break;
        }
        oal_file_close(fp);
        time_stop = oal_ktime_get();
        trans_us = (oal_uint64)oal_ktime_to_us(oal_ktime_sub(time_stop, time_start));
        OAL_IO_PRINT("device get mem %s cost %llu us\n", filename, trans_us);
        i++;
    }
    
    firmware_mem_free(firmware_mem);
    return ret;
}

/*****************************************************************************
 �� �� ��  : firmware_download
 ��������  : firmware����
 �������  : ul_index: ��Ч�����������������
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : execute_download_cmd
 ��������  : firmware_download_function

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 firmware_download(uint32 ul_index)
{
    int32 l_ret;
    int32 i;
    int32 l_cmd_type;
    uint8 *puc_cmd_name;
    uint8 *puc_cmd_para;
    FIRMWARE_MEM * firmware_mem = NULL;

    if (ul_index >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("ul_index [%d] is error!\n", ul_index);
        return -EFAIL;
    }

    PS_PRINT_INFO("start download firmware, ul_index = [%d]\n", ul_index);

    if (0 == g_st_cfg_info.al_count[ul_index])
    {
        PS_PRINT_ERR("firmware download cmd count is 0, ul_index = [%d]\n", ul_index);
        return -EFAIL;
    }
    
    firmware_mem = firmware_mem_request();
    if(NULL == firmware_mem)
    {
        PS_PRINT_ERR("firmware_mem_request fail\n");
        return -EFAIL;
    }
    
    for (i = 0; i < g_st_cfg_info.al_count[ul_index]; i++)
    {
        l_cmd_type   = g_st_cfg_info.apst_cmd[ul_index][i].cmd_type;
        puc_cmd_name = g_st_cfg_info.apst_cmd[ul_index][i].cmd_name;
        puc_cmd_para = g_st_cfg_info.apst_cmd[ul_index][i].cmd_para;

        PS_PRINT_DBG("cmd[%d]:type[%d], name[%s], para[%s]\n", i, l_cmd_type, puc_cmd_name, puc_cmd_para);

        PS_PRINT_DBG("firmware down start cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);

        l_ret = execute_download_cmd(l_cmd_type, puc_cmd_name, puc_cmd_para, firmware_mem);
        if (0 > l_ret)
        {
            if (RAM_REG_TEST_CFG == ul_index)
            {
                if ((!oal_memcmp(puc_cmd_name, JUMP_CMD_KEYWORD, OAL_STRLEN(JUMP_CMD_KEYWORD))) && (CMD_JUMP_EXEC_RESULT_FAIL == g_ulJumpCmdResult))
                {
                    /*device mem check ����ʧ�ܣ�����ִ��READM��������������*/
                    PS_PRINT_ERR("Device Mem Reg check result is fail\n");
                    continue;
                }
            }
            PS_PRINT_ERR("download firmware fail\n");
            l_ret = -EFAIL;
            goto done;
        }

        PS_PRINT_DBG("firmware down finish cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);
    }
    PS_PRINT_INFO("finish download firmware\n");
    l_ret = SUCC;
done:
    firmware_mem_free(firmware_mem);
    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_cfg_init
 ��������  : firmware���ص�cfg�ļ���ʼ������ȡ������cfg�ļ����������Ľ��������
             g_st_cfg_infoȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_get_cfg
 ��������  : 

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 plat_firmware_init(void)
{
    int32  l_ret;
    uint32 i;

    /*����cfg�ļ�*/
    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        l_ret = firmware_get_cfg(g_auc_cfg_path[i], i);
        if(0 > l_ret)
        {
            if (RAM_REG_TEST_CFG == i)
            {
                PS_PRINT_WARNING("ram_reg_test_cfg maybe not exist, please check\n");
                continue;
            }

            PS_PRINT_ERR("get cfg file [%s] fail\n", g_auc_cfg_path[i]);
            return -EFAIL;
        }
    }
    return SUCC;
}

EXPORT_SYMBOL(plat_firmware_init);

/*****************************************************************************
 �� �� ��  : firmware_cfg_clear
 ��������  : �ͷ�firmware_cfg_initʱ������ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���Ƿ���0����ʾ�ɹ�
 ���ú���  :
 ��������  : low_power_exit

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 plat_firmware_clear(void)
{
    int32 i;

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        g_st_cfg_info.al_count[i]= 0;
        if (NULL != g_st_cfg_info.apst_cmd[i])
        {
            oal_free(g_st_cfg_info.apst_cmd[i]);
            g_st_cfg_info.apst_cmd[i] = NULL;
        }
    }
    return SUCC;
}

EXPORT_SYMBOL(plat_firmware_clear);

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

/*****************************************************************************
  1 ͷ�ļ�����
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
#include "oal_file.h"
#include "oal_util.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WIFI_CFG_PATH                 "/jffs0/etc/hisi_wifi/firmware/wifi_cfg"
#define FILE_COUNT_PER_SEND           (1)
#define MIN_FIRMWARE_FILE_TX_BUF_LEN  (4096)
#define IS_ERR_OR_NULL(fp)            ( (fp) < 0 ) 

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/

uint8_t *g_auc_cfg_path[CFG_FILE_TOTAL] =
                    {
                        WIFI_CFG_PATH,
                    };

/*�洢cfg�ļ���Ϣ������cfg�ļ�ʱ��ֵ�����ص�ʱ��ʹ�øñ���*/
FIRMWARE_GLOBALS_STRUCT  g_st_cfg_info;

/*����firmware file���ݵ�buffer���Ƚ��ļ��������buffer�У�Ȼ��������device buffer����*/
uint8_t *g_pucDataBuf = NULL;

/* g_pucDataBuf�ĳ��� */
uint32_t g_ulDataBufLen = 0;

uint32_t g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

uint8_t *g_aus_recv_cmd_buff=NULL;
uint8_t *g_aus_send_cmd_buff=NULL;
volatile uint8_t firmwaredownload_flag=1;
/*****************************************************************************
 �� �� ��  : recv_expect_result
 ��������  : ����host����device��ȷ���ص�����
 �������  : expect: ����device��ȷ���ص�����
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : read_msg
 ��������  : msg_send_and_recv_except
             exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/

int32_t recv_expect_result(const uint8_t *expect)
{

    int32_t l_len;
    int32_t i;

    if (!OS_STR_LEN(expect))
    {
        PS_PRINT_DBG("not wait device to respond!\n");
        return SUCC;
    }
    if(NULL == g_aus_recv_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_recv_cmd_buff = NULL \n");
        return -EFAIL;
    }
    OS_MEM_SET(g_aus_recv_cmd_buff, 0, CMD_BUFF_LEN);
    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_len = read_msg(g_aus_recv_cmd_buff, CMD_BUFF_LEN, READ_MEG_TIMEOUT);
        if (0 > l_len)
        {
            PS_PRINT_ERR("recv result fail\n");
            return -EFAIL;
        }
        if (!OS_MEM_CMP(g_aus_recv_cmd_buff, expect, OS_STR_LEN(expect)))
        {
            PS_PRINT_DBG(" send SUCC, expect [%s] ok\n", expect);
            return SUCC;
        }
        else
        {
            PS_PRINT_WARNING(" error result[%s], expect [%s], read result again\n", g_aus_recv_cmd_buff, expect);
        }
    }

    return -EFAIL;
}

/*****************************************************************************
 �� �� ��  : msg_send_and_recv_except
 ��������  : host��device������Ϣ���ȴ�device������Ϣ
 �������  : data  : ����buffer
             len   : �������ݵĳ���
             expect: ����device�ظ�������
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : send_msg
             recv_expect_result
 ��������  : down_firmware_file
             exec_quit_type_cmd
             exec_quit_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t msg_send_and_recv_except(uint8_t *data, int32_t len, const uint8_t *expect)
{
    int32_t  i;
    int32_t  l_ret;

    for(i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_ret = send_msg(data, len);
        if (0 > l_ret)
        {
            continue;
        }

        l_ret = recv_expect_result(expect);
        if (0 == l_ret)
        {
            return SUCC;
        }
    }

    return -EFAIL;
}

/*****************************************************************************
 �� �� ��  : malloc_cmd_buf
 ��������  : ����cfg�ļ����������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_cfg_info_buf: ������cfg�ļ����ݵ�buffer
             ul_index        : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : NULL��ʾ�����ڴ�ʧ�ܣ����򷵻�ָ�򱣴����cfg�ļ�����������׵�ַ
 ���ú���  :
 ��������  : firmware_parse_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
void *malloc_cmd_buf(uint8_t *puc_cfg_info_buf, uint32_t ul_index)
{
    int32_t           l_len;
    uint8_t          *flag;
    uint8_t          *p_buf;

    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("malloc_cmd_buf: buf is NULL!\n");
        return NULL;
    }

    /* ͳ��������� */
    flag = puc_cfg_info_buf;
    g_st_cfg_info.al_count[ul_index] = 0;
    while(NULL != flag)
    {
        /* һ����ȷ�������н�����Ϊ ; */
        flag = OS_STR_CHR(flag, CMD_LINE_SIGN);
        if (NULL == flag)
        {
            break;
        }
        g_st_cfg_info.al_count[ul_index]++;
        flag++;
    }
    PS_PRINT_DBG("cfg file cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    /* ����洢����ռ� */
    l_len = (g_st_cfg_info.al_count[ul_index]) * sizeof(struct cmd_type_st);
    p_buf = OS_KMALLOC_GFP(l_len);
    if (NULL == p_buf)
    {
        PS_PRINT_ERR("kmalloc cmd_type_st fail\n");
        return NULL;
    }
    OS_MEM_SET((void *)p_buf, 0, l_len);

    return p_buf;
}

/*****************************************************************************
 �� �� ��  : delete_space
 ��������  : ɾ���ַ������߶���Ŀո�
 �������  : string: ԭʼ�ַ���
             len   : �ַ����ĳ���
 �������  : ��
 �� �� ֵ  : ���󷵻�NULL�����򷵻�ɾ�����߿ո��Ժ��ַ������׵�ַ
 ���ú���  :
 ��������  : firmware_parse_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
uint8_t *delete_space(uint8_t *string, int32_t *len)
{
    int i;

    if ((NULL == string) || (NULL == len))
    {
        return NULL;
    }

    /* ɾ��β���Ŀո� */
    for(i = *len - 1; i >= 0; i--)
    {
        if (COMPART_KEYWORD != string[i])
        {
            break;
        }
        string[i] = '\0';
    }
    /* ���� */
    if (i < 0)
    {
        PS_PRINT_ERR(" string is Space bar\n");
        return NULL;
    }
    /* ��for����м�ȥ1���������1 */
    *len = i + 1;

    /* ɾ��ͷ���Ŀո� */
    for(i = 0; i < *len; i++)
    {
        if (COMPART_KEYWORD != string[i])
        {
            /* ��ȥ�ո�ĸ��� */
            *len = *len - i;
            return &string[i];
        }
    }

    return NULL;
}

/*************************************************************************************
 �� �� ��  : open_file_to_readm
 ��������  : ���ļ�������read mem������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش��ļ���������
 ���ú���  :
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/
oal_file_stru*  open_file_to_readm(uint8 *name)
{
    oal_file_stru *fp;
    uint8_t *file_name = NULL;

    if (NULL == name)
    {
        file_name = "/data/memdump/readm_wifi";
    }
    else
    {
        file_name = name;
    }
    fp = oal_file_open(file_name, (OAL_O_CREAT | OAL_O_RDWR), 0);

    return fp;
}

/*************************************************************************************
 �� �� ��  : recv_device_mem
 ��������  : ����device�����������ڴ棬���浽ָ�����ļ���
 �������  : fp : �����ڴ���ļ�ָ��
             len: ��Ҫ������ڴ�ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ����򷵻�ʵ�ʱ�����ڴ�ĳ���
 ���ú���  : read_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/
int32_t recv_device_mem(oal_file_stru *fp, uint8_t *pucDataBuf, int32_t len)
{
    int32_t l_ret;
//    mm_segment_t fs;
    uint8_t retry = 3;
    int32_t lenbuf = 0;

    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("fp is error,fp = 0x%p\n", fp);
        return -EFAIL;
    }

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf is NULL\n");
        return -EFAIL;
    }

    PS_PRINT_DBG("expect recv len is [%d]\n", len);

//    fs = get_fs();
//    set_fs(KERNEL_DS);
//    l_ret = vfs_llseek(fp, 0, SEEK_END);
    l_ret = lseek(fp, 0, SEEK_END);
    while (len > lenbuf)
    {
        l_ret = read_msg(pucDataBuf + lenbuf, len - lenbuf, READ_MEG_TIMEOUT);
        if (l_ret > 0)
        {
            lenbuf += l_ret;
        }
        else
        {
            retry--;
            lenbuf = 0;
            if (0 == retry)
            {
                l_ret = -EFAIL;
                PS_PRINT_ERR("time out\n");
                break;
            }
        }
    }

    if (len <= lenbuf)
    {
        oal_file_write(fp, pucDataBuf, len);
    }
 //   set_fs(fs);

    return l_ret;
}
extern int usleep(unsigned useconds);

/*************************************************************************************
 �� �� ��  : check_version
 ��������  : ���������device�汾�ţ������device�ϱ��İ汾�ź�host�İ汾���Ƿ�ƥ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : send_msg
             read_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*************************************************************************************/

int32_t check_version(void)
{
    int32_t   l_ret;
    int32_t   l_len;
    int32_t   i;
//    uint8_t   rec_buf[VERSION_LEN];
    printf("enter %s\n", __func__);

    if(NULL == g_aus_recv_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_recv_cmd_buff = NULL \n");
        return -EFAIL;
    }
    if(NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_send_cmd_buff = NULL \n");
        return -EFAIL;
    }

    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        printf("[%s]loop index %d\n", __func__, i);
        OS_MEM_SET(g_aus_send_cmd_buff, 0, CMD_BUFF_LEN);

        OS_MEM_CPY(g_aus_send_cmd_buff, (uint8_t *)VER_CMD_KEYWORD, OS_STR_LEN(VER_CMD_KEYWORD));
        l_len = OS_STR_LEN(VER_CMD_KEYWORD);

        g_aus_send_cmd_buff[l_len] = COMPART_KEYWORD;
        l_len++;

        l_len = HISI_CHANNEL_ALIGN(l_len+1);
        if(CMD_BUFF_LEN < l_len)
        {
            PS_PRINT_ERR("len out of range\r\n");
            return -EFAIL;
        }

        l_ret = send_msg(g_aus_send_cmd_buff, l_len);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send version fail![%d]\n", i);
            continue;
        }

        OS_MEM_SET(g_st_cfg_info.auc_DevVersion, 0, VERSION_LEN);
        OS_MEM_SET(g_aus_recv_cmd_buff, 0, VERSION_LEN);
        printf("read msg start\n");
        l_ret = read_msg(g_aus_recv_cmd_buff, VERSION_LEN, READ_MEG_TIMEOUT);

        printf("read msg over\n");
        if (0 > l_ret)
        {
            PS_PRINT_ERR("read version fail![%d]\n", i);
            continue;
        }
        OS_MEM_CPY(g_st_cfg_info.auc_DevVersion, g_aus_recv_cmd_buff, VERSION_LEN);
        if (!OS_MEM_CMP((int8_t *)g_st_cfg_info.auc_DevVersion,
                              (int8_t *)g_st_cfg_info.auc_CfgVersion,
                              OS_STR_LEN(g_st_cfg_info.auc_CfgVersion)))
        {
            PS_PRINT_INFO("SUCC: Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
            return SUCC;
        }
        else
        {
            PS_PRINT_ERR("ERROR version,Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
        }
    }

    return -EFAIL;
}

/*****************************************************************************
 �� �� ��  : number_type_cmd_send
 ��������  : ����number���͵���������͵�device
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ������ʾ�ɹ�
 ���ú���  : send_msg
 ��������  : exec_number_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t number_type_cmd_send(uint8_t *Key, uint8_t *Value)
{
    int32_t       l_ret;
    int32_t       data_len;
    int32_t       Value_len;
    int32_t       i;
    int32_t       n;

    if(NULL == g_aus_recv_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_recv_cmd_buff = NULL \n");
        return -EFAIL;
    }
    if(NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_send_cmd_buff = NULL \n");
        return -EFAIL;
    }

    Value_len = OS_STR_LEN((int8_t *)Value);

    OS_MEM_SET(g_aus_recv_cmd_buff, 0, CMD_BUFF_LEN);
    OS_MEM_SET(g_aus_send_cmd_buff, 0, CMD_BUFF_LEN);

    data_len = 0;
    data_len = OS_STR_LEN(Key);
    OS_MEM_CPY(g_aus_send_cmd_buff, Key, data_len);

    g_aus_send_cmd_buff[data_len] = COMPART_KEYWORD;
    data_len = data_len + 1;

    for (i = 0, n = 0; (i <= Value_len) && (n < INT32_STR_LEN); i++)
    {
        if ((',' == Value[i]) || (i == Value_len ))
        {
            PS_PRINT_DBG("auc_num = %s, i = %d, n = %d\n", g_aus_recv_cmd_buff,  i, n);
            if (0 == n)
            {
                continue;
            }
            OS_MEM_CPY((uint8_t *)&g_aus_send_cmd_buff[data_len], g_aus_recv_cmd_buff, n);
            data_len = data_len + n;

            g_aus_send_cmd_buff[data_len] = COMPART_KEYWORD;
            data_len = data_len + 1;

            OS_MEM_SET(g_aus_recv_cmd_buff, 0, INT32_STR_LEN);
            n = 0;
        }
        else if (COMPART_KEYWORD == Value[i])
        {
            continue;
        }
        else
        {
            g_aus_recv_cmd_buff[n] = Value[i];
            n++;
        }

    }
    g_aus_send_cmd_buff[data_len+1]='\0';
    PS_PRINT_DBG("cmd=%s\r\n", g_aus_send_cmd_buff);
    l_ret = send_msg(g_aus_send_cmd_buff, data_len);

    return l_ret;
}


int32_t update_device_cali_count(uint8_t *Key, uint8_t *Value)
{
    PS_PRINT_INFO("adapter in feature\n");
    return SUCC;
}


int32_t download_bfgx_cali_data(uint8_t *Key, uint8_t *Value)
{
    PS_PRINT_INFO("adapter in feature\n");
    return SUCC;
}

/*****************************************************************************
 �� �� ��  : parse_file_cmd
 ��������  : ����file�������
 �������  : string   : file����Ĳ���
             addr     : ���͵����ݵ�ַ
             file_path: �����ļ���·��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : string_to_num
 ��������  : exec_file_type_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t parse_file_cmd(uint8_t *string, int32_t *addr, int8_t **file_path)
{
    uint8_t *tmp;
    int32_t count = 0;
    int8_t *after;

    if (string == NULL || addr == NULL || file_path == NULL)
    {
        PS_PRINT_ERR("param is error!\n");
        return -EFAIL;
    }

    /*��÷��͵��ļ��ĸ������˴�����Ϊ1��string�ַ����ĸ�ʽ������"1,0xXXXXX,file_path"*/
    tmp = string;
    while(COMPART_KEYWORD == *tmp)
    {
        tmp++;
    }
    count = strtoul(tmp,NULL,10);
    if (count != FILE_COUNT_PER_SEND)
    {
        PS_PRINT_ERR("the count of send file must be 1, count = [%d]\n", count);
        return -EFAIL;
    }

    /*��tmpָ���ַ������ĸ*/
    tmp = OS_STR_CHR(string, ',');
    if (tmp == NULL)
    {
        PS_PRINT_ERR("param string is err!\n");
        return -EFAIL;
    }
    else
    {
        tmp++;
        while(COMPART_KEYWORD == *tmp)
        {
            tmp++;
        }
    }

    *addr = strtoul(tmp, &after, 16);

    PS_PRINT_DBG("file to send addr:[0x%lx]\n", *addr);

    /*"1,0xXXXX,file_path"*/
    /*         ^          */
    /*       after        */
    after++;
    while(COMPART_KEYWORD == *after)
    {
        after++;
    }

    PS_PRINT_DBG("after:[%s]\n", after);

    *file_path = after;

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : sdio_read_device_mem
 ��������  : ��device����bootloaderʱ��DEVICE��ȡ�ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : С��0��ʾʧ��
 ���ú���  :

 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��5��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t sdio_read_device_mem(struct st_wifi_dump_mem_info *pst_mem_dump_info,
                                  OS_KERNEL_FILE_STRU *fp,
                                  uint8_t *pucDataBuf,
                                  uint32_t ulDataBufLen)
{
    int32_t ret = 0;
    uint32_t size = 0;
    uint32_t offset;
    uint32_t remainder = pst_mem_dump_info->size;

    offset=0;
    if(NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_send_cmd_buff = NULL \n");
        return -EFAIL;
    }
    while(remainder > 0)
    {
        OS_MEM_SET(g_aus_send_cmd_buff, 0, CMD_BUFF_LEN);

        size = (remainder<ulDataBufLen)?remainder:ulDataBufLen;
        snprintf(g_aus_send_cmd_buff,CMD_BUFF_LEN,"%s%c0x%lx%c%d%c",
                                                RMEM_CMD_KEYWORD,
                                                COMPART_KEYWORD,
                                                pst_mem_dump_info->mem_addr + offset,
                                                COMPART_KEYWORD,
                                                size,
                                                COMPART_KEYWORD);
        PS_PRINT_DBG("read mem cmd:[%s]\n", g_aus_send_cmd_buff);
        send_msg(g_aus_send_cmd_buff, OS_STR_LEN(g_aus_send_cmd_buff));

        ret = recv_device_mem(fp, pucDataBuf, size);
        if(ret < 0)
        {
            PS_PRINT_ERR("wifi mem dump fail, filename is [%s],ret=%d\n", pst_mem_dump_info->file_name,ret);
            break;
        }

        offset += size;

        remainder -= size;
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : sdio_device_mem_dump
 ��������  : firmware����ʱ��ȡwifi���ڴ�
 �������  : pst_mem_dump_info  : ��Ҫ��ȡ���ڴ���Ϣ
             count              : ��Ҫ��ȡ���ڴ�����
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : num_to_string
             recv_device_mem
             open_file_to_readm
 ��������  : wifi_exception_mem_dump

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t sdio_device_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32_t count)
{
    oal_file_stru *fp;
    int32_t ret = -EFAIL;
    uint32_t i;
    char filename[100] = {0};
 //   struct timeval tv;
 //   struct rtc_time tm;
 //   ktime_t time_start, time_stop;
 //   uint64_t  trans_us;
    uint8_t *pucDataBuf = NULL;
    uint32_t sdio_transfer_limit = usb_max_req_size();

//    /*���ڴ��ȿ��ǳɹ���,ҳ��С������ڴ���������ɹ���*/
//    sdio_transfer_limit = OAL_MIN(PAGE_SIZE, sdio_transfer_limit);

    if (NULL == pst_mem_dump_info)
    {
        PS_PRINT_ERR("pst_wifi_dump_info is NULL\n");
        return -EFAIL;
    }

    do
    {
        PS_PRINT_INFO("try to malloc mem dump buf len is [%d]\n", sdio_transfer_limit);
        pucDataBuf = (uint8_t *)OS_KMALLOC_GFP(sdio_transfer_limit);
        if (NULL == pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem  len [%d] fail, continue to try in a smaller size\n", sdio_transfer_limit);
            sdio_transfer_limit = sdio_transfer_limit >> 1;
        }
    }while((NULL == pucDataBuf) && (sdio_transfer_limit >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf KMALLOC failed\n");
        return -EFAIL;
    }

    PS_PRINT_INFO("mem dump data buf len is [%d]\n", sdio_transfer_limit);

 //   do_gettimeofday(&tv);
  //  rtc_time_to_tm(tv.tv_sec, &tm);
 //   PS_PRINT_INFO("%4d-%02d-%02d  %02d:%02d:%02d\n",
 //                  tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    for (i = 0; i < count; i++)
    {
 //       time_start = ktime_get();
        /*���ļ���׼������wifi mem dump*/
        OS_MEM_SET(filename, 0, sizeof(filename));
//        snprintf(filename, sizeof(filename),"/data/memdump/%04d%02d%02d%02d%02d%02d_%s.bin",
 //       tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
 //       tm.tm_hour, tm.tm_min, tm.tm_sec,pst_mem_dump_info[i].file_name);
        snprintf(filename, sizeof(filename),"/data/memdump/%s.bin",
        pst_mem_dump_info[i].file_name);

        PS_PRINT_INFO("readm %s\n",filename);

        fp = open_file_to_readm(filename);
        if ( IS_ERR_OR_NULL(fp) )
        {
            PS_PRINT_ERR("create file error,fp = 0x%p, filename is [%s]\n", fp, pst_mem_dump_info[i].file_name);
            break;
        }

        ret = sdio_read_device_mem(&pst_mem_dump_info[i], fp, pucDataBuf, sdio_transfer_limit);
        if (ret < 0)
        {
            oal_file_close(fp);
            break;
        }
        close(fp);
  //      time_stop = ktime_get();
  //      trans_us = (uint64_t)ktime_to_us(ktime_sub(time_stop, time_start));
  //      PS_PRINT_INFO("device get mem %s cost %llu us\n", filename, trans_us);
    }

    OS_MEM_KFREE(pucDataBuf);

    return ret;
}

int32_t sdio_read_mem(uint8_t *Key, uint8_t *Value)
{
    int32_t l_ret = -EFAIL;
    int32_t size;
    uint8_t *flag;
    oal_file_stru *fp;
    uint8_t *pucDataBuf = NULL;
    struct st_wifi_dump_mem_info read_memory;
    uint32_t sdio_transfer_limit = usb_max_req_size();

    flag = OS_STR_CHR(Value, ',');
    if (NULL == flag)
    {
        PS_PRINT_ERR("RECV LEN ERROR..\n");
        return -EFAIL;
    }
    flag++;
    PS_PRINT_DBG("recv len [%s]\n", flag);
    while(COMPART_KEYWORD == *flag)
    {
        flag++;
    }
    size = strtoul(flag,NULL,10);
    do
    {
        PS_PRINT_INFO("try to malloc sdio mem read buf len is [%d]\n", sdio_transfer_limit);
        pucDataBuf = (uint8_t *)OS_KMALLOC_GFP(sdio_transfer_limit);
        if (NULL == pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem len [%d] fail, continue to try in a smaller size\n", sdio_transfer_limit);
            sdio_transfer_limit = sdio_transfer_limit >> 1;
        }
    }while((NULL == pucDataBuf) && (sdio_transfer_limit >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf KMALLOC failed\n");
        return -EFAIL;
    }

    fp = open_file_to_readm(NULL);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
        OS_MEM_KFREE(pucDataBuf);
        return SUCC;
    }
    read_memory.mem_addr=(uint32_t)strtoul(Value, NULL, 16);
    read_memory.size=(uint32_t)size;
    l_ret = sdio_read_device_mem(&read_memory, fp, pucDataBuf, sdio_transfer_limit);

    oal_file_close(fp);
    OS_MEM_KFREE(pucDataBuf);

    return l_ret;
}

//���ļ��������

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��number���͵�����
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : check_version
             number_type_cmd_send
             recv_expect_result
             open_file_to_readm
             string_to_num
             recv_device_mem
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t exec_number_type_cmd(uint8_t *Key, uint8_t *Value)
{
    int32_t       l_ret = -EFAIL;
    int32_t       timeout = 10000;

    if (!OS_MEM_CMP(Key, VER_CMD_KEYWORD, OS_STR_LEN(VER_CMD_KEYWORD)))
    {
        l_ret = check_version();
        if (0 > l_ret)
        {
            PS_PRINT_ERR("check version FAIL [%d]\n", l_ret);
            return -EFAIL;
        }
    }

    if (!OS_STR_CMP((int8_t *)Key, WMEM_CMD_KEYWORD))
    {
        l_ret = number_type_cmd_send(Key, Value);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
            return l_ret;
        }


        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }

    }
    else if (!OS_STR_CMP((int8_t *)Key, CALI_COUNT_CMD_KEYWORD))
    {
    #if 0
        /*����У׼������device*/
        l_ret = update_device_cali_count(Key, Value);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("update device cali count fail\n");
            return l_ret;
        }
    #endif
        PS_PRINT_WARNING("adapt IN FEATURE\n");
        return SUCC;
    }
    else if (!OS_STR_CMP((int8_t *)Key, CALI_BFGX_DATA_CMD_KEYWORD))
    {
    #if 0
        /*����BFGX��У׼����*/
        l_ret = download_bfgx_cali_data(FILES_CMD_KEYWORD, Value);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("download bfgx cali data fail\n");
            return l_ret;
        }
    #endif
        PS_PRINT_WARNING("adapt IN FEATURE\n");
        return SUCC;
    }
    else if (!OS_STR_CMP((int8_t *)Key, JUMP_CMD_KEYWORD))
    {
        g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;
        l_ret = number_type_cmd_send(Key, Value);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
            return l_ret;
        }

        do {
            l_ret = recv_expect_result(MSG_FROM_DEV_JUMP_OK);
            if (l_ret >= 0)
            {
                PS_PRINT_INFO("RF calibretion time is [%d]ms!\n", (10000-timeout));
                break;
            }

            timeout -= 100;
            usleep(100000);
        }while(timeout > 0);

        if (0 == timeout)
        {
            PS_PRINT_ERR("CMD JUMP timeout!\n");
            g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_FAIL;
            return l_ret;
        }
    }
    else if (!OS_STR_CMP((int8_t *)Key, SETPM_CMD_KEYWORD) || !OS_STR_CMP((int8_t *)Key, SETBUCK_CMD_KEYWORD)
          || !OS_STR_CMP((int8_t *)Key, SETSYSLDO_CMD_KEYWORD) || !OS_STR_CMP((int8_t *)Key, SETNFCRETLDO_CMD_KEYWORD)
          || !OS_STR_CMP((int8_t *)Key, SETPD_CMD_KEYWORD) || !OS_STR_CMP((int8_t *)Key, SETNFCCRG_CMD_KEYWORD)
          || !OS_STR_CMP((int8_t *)Key, SETABB_CMD_KEYWORD) || !OS_STR_CMP((int8_t *)Key, SETTCXODIV_CMD_KEYWORD))
    {
        l_ret = number_type_cmd_send(Key, Value);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
            return l_ret;
        }

        l_ret = recv_expect_result(MSG_FROM_DEV_SET_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }
    }
    else if (!OS_STR_CMP((int8_t *)Key, RMEM_CMD_KEYWORD))
    {
        l_ret = sdio_read_mem(Key, Value);
    }

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��quit���͵�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : msg_send_and_recv_except
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t exec_quit_type_cmd(void)
{
    int32_t   l_ret;
    int32_t   l_len;

    if(NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_send_cmd_buff = NULL \n");
        return -EFAIL;
    }

    OS_MEM_SET(g_aus_send_cmd_buff, 0, 8);

    OS_MEM_CPY(g_aus_send_cmd_buff, (uint8_t *)QUIT_CMD_KEYWORD, OS_STR_LEN(QUIT_CMD_KEYWORD));
    l_len = OS_STR_LEN(QUIT_CMD_KEYWORD);

    g_aus_send_cmd_buff[l_len] = COMPART_KEYWORD;
    l_len++;

    l_ret = msg_send_and_recv_except(g_aus_send_cmd_buff, l_len, MSG_FROM_DEV_QUIT_OK);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : exec_file_type_cmd
 ��������  : ִ��file���͵�����
 �������  : Key  : ����Ĺؼ���
             Value: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ�0��ʾ�ɹ�
 ���ú���  : parse_file_cmd
             msg_send_and_recv_except
 ��������  : execute_download_cmd

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t exec_file_type_cmd(uint8_t *Key, uint8_t *Value)
{
    uint32_t addr;
    uint32_t addr_send;
    int8_t *path;
    int32_t ret;
    uint32_t file_len;
    uint32_t transmit_limit;
    uint32_t per_send_len;
    uint32_t send_count;
    int32_t rdlen;
    uint32_t i;
    uint32_t offset = 0;
    oal_file_stru *fp;

    if(NULL == g_pucDataBuf)
    {
        PS_PRINT_ERR("g_pucDataBuf = NULL \n");
        return -EFAIL;
    }
    if(NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_send_cmd_buff = NULL \n");
        return -EFAIL;
    }
    ret = parse_file_cmd(Value, &addr, &path);
    if (ret < 0)
    {
        PS_PRINT_ERR("parse file cmd fail!\n");
        return ret;
    }

    PS_PRINT_INFO("download firmware:%s\n", path);

    fp = oal_file_open(path,(OAL_O_RDONLY),0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("filp_open [%s] fail!!, fp=%p\n", path, fp);
        return -EFAIL;
    }

    /* ��ȡfile�ļ���С */
    file_len = oal_file_lseek(fp, 0, OAL_SEEK_END);
    
    /* �ָ�fp->f_pos���ļ���ͷ */
    oal_file_lseek(fp, 0, OAL_SEEK_SET);  

    PS_PRINT_DBG("file len is [%d]\n", file_len);
#ifdef _PRE_FEATURE_USB
    transmit_limit = g_ulDataBufLen;
#else
    transmit_limit = 32*1024;
#endif
    per_send_len = (transmit_limit > file_len) ? file_len : transmit_limit;
    send_count = (file_len + per_send_len - 1)/per_send_len;

    for (i = 0; i < send_count; i++)
    {
        rdlen = oal_file_read(fp, g_pucDataBuf, per_send_len);
        if (rdlen > 0)
        {
            PS_PRINT_DBG("len of kernel_read is [%d], i=%d\n", rdlen, i);
        }
        else
        {
            PS_PRINT_ERR("len of kernel_read is error! ret=[%d], i=%d\n", rdlen, i);
            oal_file_close(fp);
            
            return -EFAIL;
        }

        addr_send = addr + offset;
        PS_PRINT_DBG("send addr is [0x%lx], i=%d\n", addr_send, i);

        OS_MEM_SET(g_aus_send_cmd_buff, CMD_BUFF_LEN, 0);
        snprintf(g_aus_send_cmd_buff, SEND_BUF_LEN, "%s%c%d%c0x%lx%c",
                                            FILES_CMD_KEYWORD,
                                            COMPART_KEYWORD,
                                            FILE_COUNT_PER_SEND,
                                            COMPART_KEYWORD,
                                            addr_send,
                                            COMPART_KEYWORD);

        /*���͵�ַ*/
        PS_PRINT_DBG("send file addr cmd is [%s]\n", g_aus_send_cmd_buff);
        ret = msg_send_and_recv_except(g_aus_send_cmd_buff, OS_STR_LEN(g_aus_send_cmd_buff), MSG_FROM_DEV_READY_OK);
        if (0 > ret)
        {
            PS_PRINT_ERR("SEND [%s] error\n", g_aus_send_cmd_buff);
            oal_file_close(fp);
            return -EFAIL;
        }

        /* Wait at least 1 ms */
        usleep(1000);

        /*�����ļ�����*/
        ret = msg_send_and_recv_except(g_pucDataBuf, rdlen, MSG_FROM_DEV_FILES_OK);
        if(0 > ret)
        {
            PS_PRINT_ERR(" sdio send data fail\n");
            oal_file_close(fp);
            return -EFAIL;
        }

        offset += rdlen;
    }

    oal_file_close(fp);

    /*���͵ĳ���Ҫ���ļ��ĳ���һ��*/
    if (offset != file_len)
    {
        PS_PRINT_ERR("file send len is err! send len is [%d], file len is [%d]\n", offset, file_len);
        return -EFAIL;
    }

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : exec_shutdown_type_cmd
 ��������  : ִ��shutdown cpu type������
 �������  : which_cpu: Ҫ�رյ�cpu
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ��Ǹ�����ʾ�ɹ�
 ���ú���  : exec_file_type_cmd
             exec_number_type_cmd
             exec_quit_type_cmd
 ��������  : firmware_download

 �޸���ʷ      :
  1.��    ��   : 2015��8��17��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t exec_shutdown_type_cmd(uint32_t which_cpu)
{
    int32_t l_ret = -EFAIL;
    uint8_t Value_SHUTDOWN[SHUTDOWN_TX_CMD_LEN];

    if (DEV_WCPU == which_cpu)
    {
        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, SOFT_WCPU_EN_ADDR, 0);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_WIFI_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }
    }
    else if (DEV_BCPU == which_cpu)
    {
        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, SOFT_BCPU_EN_ADDR, 0);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_BFGX_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }

        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }

        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, BCPU_DE_RESET_ADDR, 1);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_BFGX_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }

        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }
    }
    else
    {
        PS_PRINT_ERR("para is error, which_cpu=[%d]\n", which_cpu);
        return  -EFAIL;
    }

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : execute_download_cmd
 ��������  : ִ��firmware download������
 �������  : cmd_type: �������������
             cmd_name: ����Ĺؼ���
             cmd_para: ����Ĳ���
 �������  : ��
 �� �� ֵ  : -1��ʾʧ�ܣ��Ǹ�����ʾ�ɹ�
 ���ú���  : exec_file_type_cmd
             exec_number_type_cmd
             exec_quit_type_cmd
 ��������  : firmware_download

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t execute_download_cmd(int32_t cmd_type, uint8_t *cmd_name, uint8_t *cmd_para)
{
    int32_t l_ret;
    switch(cmd_type)
    {
         case FILE_TYPE_CMD:
            PS_PRINT_DBG(" command type FILE_TYPE_CMD\n");
            l_ret = exec_file_type_cmd(cmd_name, cmd_para);
            break;
         case NUM_TYPE_CMD:
            PS_PRINT_DBG(" command type NUM_TYPE_CMD\n");
            l_ret = exec_number_type_cmd(cmd_name, cmd_para);
            break;
         case QUIT_TYPE_CMD:
            PS_PRINT_DBG(" command type QUIT_TYPE_CMD\n");
            l_ret = exec_quit_type_cmd();
            break;
         default:
            PS_PRINT_ERR("command type error[%d]\n", cmd_type);
            l_ret = -EFAIL;
            break;
    }

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_read_cfg
 ��������  : ��ȡcfg�ļ������ݣ��ŵ�������̬�����buffer��
 �������  : puc_CfgPatch    : cfg�ļ���·��
             puc_read_buffer : ����cfg�ļ����ݵ�buffer
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  :
 ��������  : firmware_get_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_read_cfg(uint8_t *puc_CfgPatch, uint8_t *puc_read_buffer)
{
    oal_file_stru    *fp;
    int32_t                l_ret;

    if ((NULL == puc_CfgPatch) || (NULL == puc_read_buffer))
    {
        PS_PRINT_ERR("para is NULL\n");
        return -EFAIL;
    }

    fp = oal_file_open(puc_CfgPatch,(OAL_O_RDONLY),0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("open file %s fail, fp=%p\n", puc_CfgPatch, fp);
        return -EFAIL;
    }

    OS_MEM_SET(puc_read_buffer, 0, READ_CFG_BUF_LEN);
    l_ret = oal_file_read(fp,puc_read_buffer,READ_CFG_BUF_LEN);

    oal_file_close(fp);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_parse_cmd
 ��������  : ����cfg�ļ��е�����
 �������  : puc_cfg_buffer: ����cfg�ļ����ݵ�buffer
             puc_cmd_name  : ��������Ժ�����ؼ��ֵ�buffer
             puc_cmd_para  : ��������Ժ����������buffer
 �������  : ��
 �� �� ֵ  : �������������
 ���ú���  : delete_space
 ��������  : firmware_parse_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_parse_cmd(uint8_t *puc_cfg_buffer, uint8_t *puc_cmd_name, uint8_t *puc_cmd_para)
{
    int32_t       l_ret;
    int32_t       l_cmdlen;
    int32_t       l_paralen;
    uint8_t      *begin;
    uint8_t      *end;
    uint8_t      *link;
    uint8_t      *handle;

    begin = puc_cfg_buffer;
    if((NULL == puc_cfg_buffer) || (NULL == puc_cmd_name) || (NULL == puc_cmd_para))
    {
        PS_PRINT_ERR("para is NULL\n");
        return ERROR_TYPE_CMD;
    }

    /* ע���� */
    if ('@' == puc_cfg_buffer[0])
    {
        return ERROR_TYPE_CMD;
    }

    /* �����У������˳������� */
    link = OS_STR_CHR((int8_t *)begin, '=');
    if (NULL == link)
    {
        /* �˳������� */
        if (NULL != OS_STR_STR((int8_t *)puc_cfg_buffer, QUIT_CMD_KEYWORD))
        {
            return QUIT_TYPE_CMD;
        }
        else if (NULL != OS_STR_STR((int8_t *)puc_cfg_buffer, SHUTDOWN_WIFI_CMD_KEYWORD))
        {
            return SHUTDOWN_WIFI_TYPE_CMD;
        }

        return ERROR_TYPE_CMD;
    }

    /* �����У�û�н����� */
    end = OS_STR_CHR(link, ';');
    if (NULL == end)
    {
        return ERROR_TYPE_CMD;
    }

    l_cmdlen = link - begin;

    /* ɾ���ؼ��ֵ����߿ո� */
    handle = delete_space((uint8_t *)begin, &l_cmdlen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }

    /* �ж��������� */
    if (!OS_MEM_CMP(handle, (uint8_t *)FILE_TYPE_CMD_KEY, OS_STR_LEN((uint8_t *)FILE_TYPE_CMD_KEY)))
    {
        handle = OS_STR_STR(handle, (uint8_t *)FILE_TYPE_CMD_KEY) + OS_STR_LEN(FILE_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OS_STR_LEN(FILE_TYPE_CMD_KEY);
        l_ret = FILE_TYPE_CMD;
    }
    else if (!OS_MEM_CMP(handle, (uint8_t *)NUM_TYPE_CMD_KEY, OS_STR_LEN(NUM_TYPE_CMD_KEY)))
    {
        handle = OS_STR_STR(handle, (uint8_t *)NUM_TYPE_CMD_KEY) + OS_STR_LEN(NUM_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OS_STR_LEN(NUM_TYPE_CMD_KEY);
        l_ret = NUM_TYPE_CMD;
    }
    else
    {
        return ERROR_TYPE_CMD;
    }

    if (DOWNLOAD_CMD_LEN < l_cmdlen || 0 > l_cmdlen)
    {
        PS_PRINT_ERR("cmd len out of range!\n");
        return ERROR_TYPE_CMD;
    }
    OS_MEM_CPY(puc_cmd_name, handle, l_cmdlen);

    /* ɾ��ֵ���߿ո� */
    begin = link + 1;
    l_paralen = end - begin;
    if (DOWNLOAD_CMD_PARA_LEN < l_paralen || 0 > l_paralen)
    {
        PS_PRINT_ERR("para len out of range!\n");
        return ERROR_TYPE_CMD;
    }

    handle = delete_space((uint8_t *)begin, &l_paralen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }
    OS_MEM_CPY(puc_cmd_para, handle, l_paralen);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : firmware_parse_cfg
 ��������  : ����cfg�ļ����������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_cfg_info_buf: ������cfg�ļ����ݵ�buffer
             l_buf_len       : puc_cfg_info_buf�ĳ���
             ul_index        : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : malloc_cmd_buf
             firmware_parse_cmd
 ��������  : firmware_get_cfg

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_parse_cfg(uint8_t *puc_cfg_info_buf, int32_t l_buf_len, uint32_t ul_index)
{
    int32_t           i;
    int32_t           l_len;
    uint8_t          *flag;
    uint8_t          *begin;
    uint8_t          *end;
    int32_t           cmd_type;
    uint8_t           cmd_name[DOWNLOAD_CMD_LEN];
    uint8_t           cmd_para[DOWNLOAD_CMD_PARA_LEN];

    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("puc_cfg_info_buf is NULL!\n");
        return -EFAIL;
    }

    g_st_cfg_info.apst_cmd[ul_index] = (struct cmd_type_st *)malloc_cmd_buf(puc_cfg_info_buf, ul_index);
    if (NULL == g_st_cfg_info.apst_cmd[ul_index])
    {
        PS_PRINT_ERR(" malloc_cmd_buf fail!\n");
        return -EFAIL;
    }

    /* ����CMD BUF*/
    flag = puc_cfg_info_buf;
    l_len = l_buf_len;
    i = 0;
    while((i < g_st_cfg_info.al_count[ul_index]) && (flag < &puc_cfg_info_buf[l_len]))
    {
        /*
         *��ȡ�����ļ��е�һ��,�����ļ�������unix��ʽ.
         *�����ļ��е�ĳһ�к����ַ� @ ����Ϊ����Ϊע����
         */
        begin = flag;
        end   = OS_STR_CHR(flag, '\n');
        if (NULL == end)           /*�ļ������һ�У�û�л��з�*/
        {
            PS_PRINT_DBG("lost of new line!\n");
            end = &puc_cfg_info_buf[l_len];
        }
        else if (end == begin)     /* ����ֻ��һ�����з� */
        {
            PS_PRINT_DBG("blank line\n");
            flag = end + 1;
            continue;
        }
        *end = '\0';

        PS_PRINT_DBG("operation string is [%s]\n", begin);

        OS_MEM_SET(cmd_name, 0, DOWNLOAD_CMD_LEN);
        OS_MEM_SET(cmd_para, 0, DOWNLOAD_CMD_PARA_LEN);

        cmd_type = firmware_parse_cmd(begin, cmd_name, cmd_para);

        PS_PRINT_DBG("cmd type=[%d],cmd_name=[%s],cmd_para=[%s]\n", cmd_type, cmd_name, cmd_para);

        if (ERROR_TYPE_CMD != cmd_type)/* ��ȷ���������ͣ����� */
        {
            g_st_cfg_info.apst_cmd[ul_index][i].cmd_type = cmd_type;
            OS_MEM_CPY(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name, cmd_name, DOWNLOAD_CMD_LEN);
            OS_MEM_CPY(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para, cmd_para, DOWNLOAD_CMD_PARA_LEN);
            /* ��ȡ���ð汾�� */
            if (!OS_MEM_CMP(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name,
                            VER_CMD_KEYWORD,
                            OS_STR_LEN(VER_CMD_KEYWORD)))
            {
                OS_MEM_CPY(g_st_cfg_info.auc_CfgVersion,
                           g_st_cfg_info.apst_cmd[ul_index][i].cmd_para,
                           OS_STR_LEN(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para));


                PS_PRINT_DBG("g_CfgVersion = [%s].\n", g_st_cfg_info.auc_CfgVersion);
            }
            i++;
        }
        flag = end + 1;
    }

    /* ����ʵ������������޸����յ�������� */
    g_st_cfg_info.al_count[ul_index] = i;
    PS_PRINT_INFO("effective cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    return SUCC;
}

uint32_t usb_max_req_size()
{
    return (32*1024)*10;
}

/*****************************************************************************
 �� �� ��  : firmware_get_cfg
 ��������  : ��ȡcfg�ļ����������������Ľ��������g_st_cfg_infoȫ�ֱ�����
 �������  : puc_CfgPatch: cfg�ļ���·��
             ul_index     : ��������������������ֵ
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_read_cfg
             firmware_parse_cfg
 ��������  : firmware_cfg_init

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_get_cfg(uint8_t *puc_CfgPatch, uint32_t ul_index)
{
    uint8_t   *puc_read_cfg_buf;
    int32_t   l_readlen;
    int32_t   l_ret;

    if (NULL == puc_CfgPatch)
    {
        PS_PRINT_ERR("cfg file path is null!\n");
        return -EFAIL;
    }

    /*cfg�ļ��޶���С��2048,���cfg�ļ��Ĵ�Сȷʵ����2048�������޸�READ_CFG_BUF_LEN��ֵ*/
    puc_read_cfg_buf = OS_KMALLOC_GFP(READ_CFG_BUF_LEN);
    if (NULL == puc_read_cfg_buf)
    {
        PS_PRINT_ERR("kmalloc READ_CFG_BUF fail!\n");
        return -EFAIL;
    }

    l_readlen = firmware_read_cfg(puc_CfgPatch, puc_read_cfg_buf);
    if(0 > l_readlen)
    {
        PS_PRINT_ERR("read cfg error!\n");
        OS_MEM_KFREE(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }
    /*��1��Ϊ��ȷ��cfg�ļ��ĳ��Ȳ�����READ_CFG_BUF_LEN����Ϊfirmware_read_cfg���ֻ���ȡREAD_CFG_BUF_LEN���ȵ�����*/
    else if (l_readlen > READ_CFG_BUF_LEN - 1)
    {
        PS_PRINT_ERR("cfg file [%s] larger than %d\n", puc_CfgPatch, READ_CFG_BUF_LEN);
        OS_MEM_KFREE(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }
    else
    {
        PS_PRINT_DBG("read cfg file [%s] ok, size is [%d]\n", puc_CfgPatch, l_readlen);
    }

    l_ret = firmware_parse_cfg(puc_read_cfg_buf, l_readlen, ul_index);
    if(0 > l_ret)
    {
        PS_PRINT_ERR("parse cfg error!\n");
    }

    OS_MEM_KFREE(puc_read_cfg_buf);
    puc_read_cfg_buf = NULL;

    return l_ret;
}


/*****************************************************************************
 �� �� ��  : firmware_download
 ��������  : firmware����
 �������  : ul_index: ��Ч�����������������
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : execute_download_cmd
 ��������  : firmware_download_function

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_download(uint32_t ul_index)
{
    int32_t l_ret;
    int32_t i;
    int32_t l_cmd_type;
    uint8_t *puc_cmd_name;
    uint8_t *puc_cmd_para;
    firmwaredownload_flag=1;

    if (ul_index >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("ul_index [%d] is error!\n", ul_index);
        return -EFAIL;
    }
    //PS_PRINT_INFO("start download firmware, ul_index = [%d]\n", ul_index);
    printf("start download firmware, ul_index = [%d]\n", ul_index);
#ifdef _PRE_FEATURE_USB
    g_ulDataBufLen = usb_max_req_size();
#else
    g_ulDataBufLen = oal_sdio_func_max_req_size(oal_get_sdio_default_handler());
#endif

    do
    {
        PS_PRINT_INFO("try to malloc firmware download file buf len is [%d]\n", g_ulDataBufLen);

        g_pucDataBuf = (uint8_t *)OS_KMALLOC_GFP(g_ulDataBufLen);
        if (NULL == g_pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem len [%d] fail, continue to try in a smaller size\n", g_ulDataBufLen);
            g_ulDataBufLen = g_ulDataBufLen >> 1;
        }
    }while((NULL == g_pucDataBuf) && (g_ulDataBufLen >= MIN_FIRMWARE_FILE_TX_BUF_LEN));
    if (NULL == g_pucDataBuf)
    {
        PS_PRINT_ERR("g_pucDataBuf KMALLOC failed\n");
        l_ret = -EFAIL;
        goto alloc_g_pucDataBuf_fail;
    }

    g_aus_recv_cmd_buff = (uint8_t *)OS_KMALLOC_GFP(CMD_BUFF_LEN);
    if (NULL == g_aus_recv_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_recv_cmd_buff KMALLOC failed\n");
        l_ret = -EFAIL;
        goto alloc_g_aus_recv_cmd_buff_fail;
    }

    g_aus_send_cmd_buff = (uint8_t *)OS_KMALLOC_GFP(CMD_BUFF_LEN);
    if (NULL == g_aus_send_cmd_buff)
    {
        PS_PRINT_ERR("g_aus_recv_cmd_buff KMALLOC failed\n");
        l_ret = -EFAIL;
        goto alloc_g_aus_send_cmd_buff_fail;
    }
    PS_PRINT_INFO("download firmware file buf len is [%d]\n", g_ulDataBufLen);

    for (i = 0; i < g_st_cfg_info.al_count[ul_index]; i++)
    {
        l_cmd_type   = g_st_cfg_info.apst_cmd[ul_index][i].cmd_type;
        puc_cmd_name = g_st_cfg_info.apst_cmd[ul_index][i].cmd_name;
        puc_cmd_para = g_st_cfg_info.apst_cmd[ul_index][i].cmd_para;

        PS_PRINT_DBG("cmd[%d]:type[%d], name[%s], para[%s]\n", i, l_cmd_type, puc_cmd_name, puc_cmd_para);

        PS_PRINT_DBG("firmware down start cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);

        l_ret = execute_download_cmd(l_cmd_type, puc_cmd_name, puc_cmd_para);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("download firmware fail\n");
            l_ret = -EFAIL;
            goto download_firmware_fail;
        }

        PS_PRINT_DBG("firmware down finish cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);
    }
    PS_PRINT_INFO("finish download firmware\n");
    l_ret = SUCC;
    firmwaredownload_flag=0;

download_firmware_fail:
    OS_MEM_KFREE(g_aus_send_cmd_buff);
    g_aus_send_cmd_buff=NULL;
alloc_g_aus_send_cmd_buff_fail:
    OS_MEM_KFREE(g_aus_recv_cmd_buff);
    g_aus_recv_cmd_buff = NULL;
alloc_g_aus_recv_cmd_buff_fail:
    OS_MEM_KFREE(g_pucDataBuf);
    g_pucDataBuf = NULL;
alloc_g_pucDataBuf_fail:
    return l_ret;
}

EXPORT_SYMBOL(firmware_download);

/*****************************************************************************
 �� �� ��  : firmware_cfg_init
 ��������  : firmware���ص�cfg�ļ���ʼ������ȡ������cfg�ļ����������Ľ��������
             g_st_cfg_infoȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  : firmware_get_cfg
 ��������  : firmware_download_function

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_cfg_init(void)
{
    int32_t  l_ret;
    uint32_t i;

    /*����cfg�ļ�*/
    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        l_ret = firmware_get_cfg(g_auc_cfg_path[i], i);
        if(0 > l_ret)
        {
            PS_PRINT_ERR("get cfg file [%s] fail\n", g_auc_cfg_path[i]);
            goto cfg_file_init_fail;
        }
    }


    return SUCC;

cfg_file_init_fail:
    firmware_cfg_clear();

    return -EFAIL;
}


/*****************************************************************************
 �� �� ��  : firmware_cfg_clear
 ��������  : �ͷ�firmware_cfg_initʱ������ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���Ƿ���0����ʾ�ɹ�
 ���ú���  :
 ��������  : low_power_exit

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
int32_t firmware_cfg_clear(void)
{
    int32_t i;

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        g_st_cfg_info.al_count[i]= 0;
        if (NULL != g_st_cfg_info.apst_cmd[i])
        {
            OS_MEM_KFREE(g_st_cfg_info.apst_cmd[i]);
            g_st_cfg_info.apst_cmd[i] = NULL;
        }
    }

    return SUCC;
}

#endif
