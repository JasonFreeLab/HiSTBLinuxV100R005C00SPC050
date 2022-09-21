
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/prctl.h>
#include "hisoc/uart.h"
#include "hi_type.h"
#include "hi_ext_hal_mcu.h"



#define CHECK_STATE_FLAG(flag, state)\
    do{\
        if (flag != state)\
        {\
            printf("func:%s,line:%d,flag statue fail\n",__FUNCTION__,__LINE__);\
            return HI_FAILURE;\
        }\
    }while (0)

#define CHECK_NULL_PTR(ptr)\
    do{\
        if (NULL == ptr)\
        {\
            printf("func:%s,line:%d,NULL pointer\n",__FUNCTION__,__LINE__);\
            return HI_FAILURE;\
        }\
    }while (0)


HI_BOOL g_bMcuHostInit = HI_FALSE;
HI_BOOL g_bMcuHostState = HI_FALSE;
HI_BOOL g_bMcuHostEnableState = HI_FALSE;
static HI_BOOL s_bMcuHostRegister = HI_FALSE;
static PFN_MCUHOST_NotifyProc s_pfnMcuHostNotifyProc = NULL;
static HI_S32 g_stResponse = 0;
static HI_S32 g_s32WIFIRegDetResponse = 0;
pthread_mutex_t g_ResponseLock;
pthread_mutex_t g_WIFIRegDetResponseLock;
pthread_t g_tMcuHostDetect;
static pthread_mutex_t s_tMcuHostMutex;

extern int mcu_fd;
extern int use_hostapd;
unsigned char power_handle_flag = 0;



#define UF_START 0
#define UF_LEN 1
#define UF_CMD 2
#define UF_DATA 3
#define UF_MAX_LEN 50




#define UART2_BUF_LEN  100

static char uart2_buffer[UART2_BUF_LEN];

#if 0
void debug_dump(char* buffer, HI_U16 length, char* pDescription)
{
    char stream[60];
    char byteOffsetStr[10];
    HI_U32 i;
    HI_U16 offset, count, byteOffset;

    printf("<-----------Dumping %d Bytes : %s -------->\n", length, pDescription);
    //A_PRINTF("%s:%d = \n",  pDescription, length);
    count = 0;
    offset = 0;
    byteOffset = 0;

    for (i = 0; i < length; i++)
    {
        sprintf(stream + offset, "%2.2X ", buffer[i]);
        count ++;
        offset += 3;

        if (count == 16)
        {
            count = 0;
            offset = 0;
            sprintf(byteOffsetStr, "%4.4X", byteOffset);
            printf("[%s]: %s\n", byteOffsetStr, stream);
            memset(stream, 0, 60);
            byteOffset += 16;
        }
    }

    if (offset != 0)
    {
        sprintf(byteOffsetStr, "%4.4X", byteOffset);
        printf("[%s]: %s\n", byteOffsetStr, stream);
    }

    printf("<------------------------------------------------->\n");
}
#else
void debug_dump(char* buffer, HI_U16 length, char* pDescription)
{

}
#endif
unsigned char  XOR_Inverted_Check(unsigned char* inBuf, unsigned char inLen)
{
    unsigned char check = 0, i;

    for (i = 0; i < inLen; i++)
    { check ^= inBuf[i]; }

    return ~check;
}


int USART_Send_Data(HI_S32 fd, HI_U8* sbuf)
{
    int ret, i;

    sbuf[UF_START] = 0x7B;
    sbuf[sbuf[UF_LEN] - 1] = XOR_Inverted_Check(sbuf, sbuf[UF_LEN] - 1);

    ret = write(fd, sbuf, sbuf[UF_LEN]);

    if (ret < 0)
    {
        printf("write %d fd return %d\n", fd, ret);
        return -1;
    }
    else if (ret < sbuf[UF_LEN])
    {
        printf("uart send len =  %d , error! sbuf = ", ret);

        for (i = 0; i < ret; i++)
        { printf(" %02X", sbuf[i]); }

        printf("\n");
        return -1;
    }

    for (i = 0; i < sbuf[UF_LEN]; i++){
        printf("%x ", sbuf[i]);
    }

    printf("\nuart send ok!\n");
    return 0;
}



static HI_S32 USART_Receive_Data(HI_S32 fd, HI_U8* rbuf, HI_U8 rbuf_max_len)
{
    HI_S32 ret;
    HI_U8 len, i;
    HI_U32 timeout_cnt;
    HI_U8 bcc;
    //fd_set fs_read;
    struct timeval time;
    HI_S32 fs_sel;

    len = 0;
    timeout_cnt = 0;

    while (((len < 2) || (len < rbuf[UF_LEN])))
    {
        ret = read(fd, rbuf + len, UF_MAX_LEN);

        if (ret < -1)
        {
            perror("receive error!");
            printf("read ret = %d\n", ret);
            return (HI_FAILURE);
        }
        else if (ret == 0)
        {
            usleep(50000);
        }
        else
        {
            len += ret;
        }

        timeout_cnt++;

        if (timeout_cnt > 500)
        {
            //printf("receive timeout!\n");
            return (HI_FAILURE);
        }
    }

    printf("receive buf:");

    for (i = 0; i < len; i++)
    { printf(" %02X ", rbuf[i]); }

    printf("\n");
    bcc = XOR_Inverted_Check(rbuf, rbuf[UF_LEN] - 1);

    if ((rbuf[UF_START] != 0X7B) || (rbuf[rbuf[UF_LEN] - 1] != bcc))
    {
        printf("uart bcc err\n");
        return -1;
    }

    return (HI_SUCCESS);
}






HI_S32 HI_HAL_MCUHOST_Set_ShutDown_Interval(HI_U32 u32Interval)
{
    HI_U32 u32hour, u32min;

    uart2_buffer[UF_LEN] = 0x4 + 0x3;
    uart2_buffer[UF_CMD] = 0x86;

    if (u32Interval > 0)
    {
        uart2_buffer[UF_DATA] = 0x1;
    }
    else
    {
        uart2_buffer[UF_DATA] = 0x0;
    }

    u32hour = u32Interval / 60;
    u32min = u32Interval % 60;
    uart2_buffer[UF_DATA + 1] = u32hour;
    uart2_buffer[UF_DATA + 2] = u32min;
    USART_Send_Data(mcu_fd, uart2_buffer);
    //printf("%s, %x\n",__func__,uart2_buffer[UF_CMD]);



    while (1)
    {
        pthread_mutex_lock(&g_ResponseLock);

        if (-1 == g_stResponse)
        {
            return HI_FAILURE;
        }
        else if (1 == g_stResponse)
        {
            return HI_SUCCESS;
        }

        pthread_mutex_unlock(&g_ResponseLock);
        usleep(10000);
    }

    return HI_SUCCESS;
}


extern unsigned int wlan_pm_resume(void);
extern unsigned int wlan_pm_wakeup_host(void);
static void Uart_CMD_Handle(int fd, unsigned char* buf, unsigned char buf_max_len)
{
    unsigned char check = 0;
    int ret;

    ret = USART_Receive_Data(fd, buf, buf_max_len);

    if (ret == HI_FAILURE)
    {
        //printf("mcu host get frame fail");
        return;
    }

    printf("\nUart_CMD_Handle  buf[UF_CMD]: 0x%x\n", buf[UF_CMD]);

    switch (buf[UF_CMD])
    {
        case 0x00:
            printf("poweroff!\n");
#if 0
            system("himm 0x20220400 0x40");
            system("himm 0x20220100 0x40");
#else
            //system("poweroff");
            printf("\n#LPrint file: %s func: %s line: %d ticket: %d\n", __FILE__, __FUNCTION__, __LINE__, LOS_TickCountGet());
            ret = s_pfnMcuHostNotifyProc(MCUHOST_SYSTEMCLOSE);

            if (ret == HI_FAILURE)
            {
                return;
            }

            //HI_HAL_MCUHOST_PowreOff_Request();
            if (1)
            {
                char *p = 0x201b0004;//GPIO7_0  //GPIO7_1
                char *m = 0x201b0400;

                int val;

                val = *p;
                *p = val | 0x01;


                val = *m;
                *m = val | 0x01;
            }
#endif
            break;

        case 0x81:
            printf("receive poweroff response cmd!\n");

#if 0
            system("himm 0x20220400 0x40");
            system("himm 0x20220100 0x40");

#else
            power_handle_flag = 0;
            printf("\n#LPrint file: %s func: %s line: %d ticket: %d\n", __FILE__, __FUNCTION__, __LINE__, LOS_TickCountGet());
            ret = s_pfnMcuHostNotifyProc(MCUHOST_SYSTEMCLOSE);

            if (ret == HI_FAILURE)
            {return;}

#endif
            break;

        case 0x87:
        {
            pthread_mutex_lock(&g_ResponseLock);

            if (0 == buf[UF_DATA])
            {
                g_stResponse = 1;
            }
            else
            {
                g_stResponse = -1;
            }

            pthread_mutex_unlock(&g_ResponseLock);
            break;
        }

        case 0x85:
        {
            pthread_mutex_lock(&g_WIFIRegDetResponseLock);
            g_s32WIFIRegDetResponse = 1;
            printf("receive back of set reg\r\n");
            pthread_mutex_unlock(&g_WIFIRegDetResponseLock);
            break;
        }



        case 0xbb:
        {

            /*临时调用 后续会判断强制睡状态后决定是调用resume还是置标志位*/
            wlan_pm_wakeup_host();
            break;
        }
        default:
            break;
    }
}


HI_VOID* MCUHOST_Thread(HI_VOID* pPara)
{
    HI_S32 s32Ret;
    prctl(PR_SET_NAME, (HI_SIZE_T)"MCUHOST_Thread", 0, 0, 0);

    while (g_bMcuHostState)
    {
        //printf(">>>>>>>>>MCUHOST_Thread\n");
        if (HI_TRUE != g_bMcuHostEnableState)
        {
            usleep(500 * 1000);
            continue;
        }

        Uart_CMD_Handle(mcu_fd, uart2_buffer, UF_MAX_LEN);
    }

    return NULL;
}



HI_S32 HI_HAL_MCUHOST_Init()
{
    HI_S32 s32Ret;

    CHECK_STATE_FLAG(g_bMcuHostInit, HI_FALSE);

    pthread_mutex_init(&s_tMcuHostMutex, NULL);

    s32Ret = pthread_create(&g_tMcuHostDetect, 0, MCUHOST_Thread, NULL);

    if (s32Ret)
    {
        printf("mcu host create thread fail.\n");
        return s32Ret;
    }


    g_bMcuHostInit = HI_TRUE;
    g_bMcuHostState = HI_TRUE;
    g_bMcuHostEnableState = HI_TRUE;
    pthread_mutex_init(&g_ResponseLock, NULL);
    pthread_mutex_init(&g_WIFIRegDetResponseLock, NULL);
    //s_pfnUsbNotifyProc = NULL;
    printf("mcu host init ok \n");
    return HI_SUCCESS;
}

HI_S32 HI_HAL_MCUHOST_Deinit()
{
    HI_S32 s32Ret;

    if (g_bMcuHostInit == HI_TRUE)
    {
        g_bMcuHostState = HI_FALSE;
        pthread_mutex_lock(&s_tMcuHostMutex);
        s32Ret = pthread_join(g_tMcuHostDetect, NULL);

        if (s32Ret != 0)
        {
            printf("g_tMcuHostDetect: pthread_join failed\n");
            return s32Ret;
        }

        pthread_mutex_unlock(&s_tMcuHostMutex);
        pthread_mutex_destroy(&s_tMcuHostMutex);
        memset(&s_tMcuHostMutex, 0, sizeof(s_tMcuHostMutex));

        g_bMcuHostEnableState = HI_FALSE;


        g_bMcuHostInit = HI_FALSE;
    }

    return HI_SUCCESS;
}


HI_S32 HI_HAL_MCUHOST_RegisterNotifyProc(PFN_MCUHOST_NotifyProc pfnNotifyProc)
{
    CHECK_STATE_FLAG(g_bMcuHostInit, HI_TRUE);
    CHECK_STATE_FLAG(s_bMcuHostRegister, HI_FALSE);
    CHECK_NULL_PTR(pfnNotifyProc);
    s_pfnMcuHostNotifyProc = pfnNotifyProc;
    s_bMcuHostRegister = HI_TRUE;
    return HI_SUCCESS;
}



HI_S32 HI_HAL_MCUHOST_RegOn_Control(HI_CHAR u8enable)
{
    HI_U32 u32waitcount = 20;

    if ((u8enable != 0) && (u8enable != 1))
    {
        printf("intput err\r\n");
    }


    uart2_buffer[UF_START] = 0x7b;
    uart2_buffer[UF_LEN] = 0x5;
    uart2_buffer[UF_CMD] = 0x84;
    uart2_buffer[UF_DATA] = u8enable;
    debug_dump(uart2_buffer, 4, "send Wifi_Reg_Det_Control cmd");
    USART_Send_Data(mcu_fd, uart2_buffer);
    //printf("%s, %x\n",__func__,uart2_buffer[UF_CMD]);

    do
    {
        usleep(100 * 1000);
    }
    while (u32waitcount-- && (g_s32WIFIRegDetResponse == 0));

    printf("\nHI_Product_Wifi_Reg_Det_Control  g_s32WIFIRegDetResponse: %d u32waitcount: %d\n", g_s32WIFIRegDetResponse, u32waitcount);
    pthread_mutex_lock(&g_WIFIRegDetResponseLock);
    g_s32WIFIRegDetResponse = 0;
    pthread_mutex_unlock(&g_WIFIRegDetResponseLock);
    return HI_SUCCESS;

}


HI_S32 HI_HAL_MCUHOST_PowreOff_Request()
{
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    /*睡前写文件系统，下次上电时读取判断是wakeUp还是bootUp*/
    if (1 == use_hostapd)
    {
        wake_write_flag(1);
    }
    else
    {
        wake_write_flag(2);
    }
    /* 确保文件缓存写入 */
    wake_read_flag();
#endif
    if (power_handle_flag)
    {
        return HI_FAILURE;
    }

    power_handle_flag = 1;

    uart2_buffer[UF_START] = 0x7b;
    uart2_buffer[UF_LEN] = 0x4;
    uart2_buffer[UF_CMD] = 0x80;
    debug_dump(uart2_buffer, 4, "send power off cmd");
    USART_Send_Data(mcu_fd, uart2_buffer);
    //printf("%s, %x\n",__func__,uart2_buffer[UF_CMD]);

    return HI_SUCCESS;
}


int HI_HAL_MCUHOST_WiFi_ON_Request(int On)
{
    char s_u8buffer[UF_MAX_LEN];
    memset(s_u8buffer, 0, UF_MAX_LEN);
    s_u8buffer[UF_LEN] = 0x5;
    s_u8buffer[UF_CMD] = 0x84;
    s_u8buffer[UF_DATA] = On;
    USART_Send_Data(mcu_fd,s_u8buffer);
    //printf("%s, %x\n",__func__,s_u8buffer[UF_CMD]);

}

/* 0: normal start, 1: AP resume, 2: STA resume  */
 void wake_write_flag(int flag)
{
    int flag_fd;
    int ret;

    printf("wake_write_flag, %d!\n",flag);
    
    flag_fd = open("/jffs0/wake_flag.txt",O_WRONLY|O_CREAT);
    if (flag_fd < 0)
    {
        printf("open wake_flag.txt failed!\n");
        return;
    }
    if (flag == 1)
    {
        ret = write(flag_fd,"1",2);
    }
    else if (flag == 2)
    {
        ret = write(flag_fd,"2",2);
    }
    else if (flag == 0)
    {
        ret = write(flag_fd,"0",2);
    }
    else
    {
        printf("flag only could be 0 or 1 or 2\n");
    }
     if (ret < 0)
    {
        printf("write flag_fd error\n");
    }
    close(flag_fd);
    return;

}

int wake_read_flag(void)
{
    int flag_fd;
    int ret;
    char buf[10];

    flag_fd = open("/jffs0/wake_flag.txt",O_RDONLY);
    if (flag_fd < 0)
    {
        printf("open wake_flag.txt failed!\n");
        return -1;
    }
    ret = read(flag_fd,buf,2);
    if (ret < 0)
    {
        printf("read flag_fd error\n");
        return -1;
    }
    printf("wake_flag: %s\n",buf);
    ret = memcmp(buf,"1",1);
    if (ret == 0)
        return 1;

    ret = memcmp(buf,"2",1);

    if (ret == 0)
        return 2;
        
    return 0;
}