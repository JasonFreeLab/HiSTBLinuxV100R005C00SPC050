#include <stdio.h>
#include "sys/types.h"
#include "sys/time.h"
#include "hi_type.h"
#include "sys/prctl.h"
#include "eth_drv.h"

#include "fcntl.h"
#include "asm/io.h"
#include "hi_ext_hal_mcu.h"


#define himm(address, value) writel(value, address)
int mcu_fd = -1;

HI_S32 HI_Product_McuHost_Event_proc(HAL_MCUHOST_EVENT_E eMCUHOSTEVENT)
{
    HI_S32 s32Ret = HI_SUCCESS;
    switch(eMCUHOSTEVENT)
    {
        case MCUHOST_SYSTEMCLOSE:
        {
            #ifdef CFG_SUPPORT_WIFI_STA

            //Wl scansuppress 1
            wwd_get_scansuppress();
            wwd_wifi_set_scansuppress(1); // set scansuppress to 1
            wwd_get_scansuppress();

            //Wl PM 1
            wwd_sta_set_powersave(1, 0);

            //Wl bcn_li_dtim 10
            wwd_sta_get_bcn_li_dtim();
            wwd_sta_set_bcn_li_dtim(10); // if ap router dtim is 2 seconds
            wwd_sta_get_bcn_li_dtim();

            //wl host_sleep 1
            wwd_set_host_sleep(1);
            #endif

            #ifdef CFG_SUPPORT_WIFI_AP
            extern void wwd_wowl_ap_enable(void);
            wwd_wowl_ap_enable();
            #else
            //extern void wwd_wowl_sta_enable( char *pattern_string, int offset );
            //wwd_wowl_sta_enable("0x983B16F8F39C", 66);
            #endif

            //host_oob_interrupt_disable();


            break;
        }
        default:
            printf("err when switch eMCUHOSTEVENT\n");
            return HI_FAILURE;
    }
    return HI_SUCCESS;
}

void hi_uart2_open(void)
{
    writew(0x3, IO_MUX_REG_BASE + 0x0CC);   //myh
    writew(0x3, IO_MUX_REG_BASE + 0x0D0);   //myh

    mcu_fd = open("/dev/uartdev-2", O_RDWR);
    if (mcu_fd < 0)
    {
        mcu_fd = -1;
        printf("open %s with %d ret = %d\n","/dev/uartdev-2", O_RDWR, mcu_fd);
    }
    else
    {
        printf("\nhi_uart2_open success\n");
    }
}
void hi_uart2_close(void)
{
    close(mcu_fd);
    mcu_fd = -1;
}

void mcu_uart_proc()
{
    hi_uart2_open();
    HI_HAL_MCUHOST_WiFi_ON_Request(1);
    extern HI_S32 HI_Product_McuHost_Event_proc(HAL_MCUHOST_EVENT_E eMCUHOSTEVENT);
    HI_HAL_MCUHOST_Init();
    HI_HAL_MCUHOST_RegisterNotifyProc(HI_Product_McuHost_Event_proc);
}

