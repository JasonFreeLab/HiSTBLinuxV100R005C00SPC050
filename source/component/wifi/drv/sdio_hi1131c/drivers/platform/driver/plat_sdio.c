/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : plat_sdio.c
 * Version       : Hi1102
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

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include "oal_sdio.h"
#include "oal_sdio_host_if.h"

#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_pm.h"
#include "plat_firmware.h"
#include "oal_time.h"
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
extern struct sdio_func *p_gst_sdio_func;
#endif

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/

/*****************************************************************************
  3 Function Definition
*****************************************************************************/

/*
 * Prototype    : sdio_patch_writesb
 * Description  : provide interface for pm driver
 * Input        : uint8* buf, uint32 len
 * Output       : None
 * Return Value : int32
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         :
 *     Author       :
 *     Modification : Created function
 *
 */
int32 sdio_patch_writesb(uint8* buf, uint32 len)
{
    int ret;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    struct sdio_func *func = pm_data->pst_wlan_pm_info->pst_sdio->func;

    if (NULL == func)
    {
        PS_PRINT_ERR("Sdio device is NOT initialized\n");
        return -FAILURE;
    }

    if (NULL == buf || len == 0)
    {
        PS_PRINT_ERR("Write buf is NULL\n");
        return -FAILURE;
    }

    PS_PRINT_DBG("======sdio write:%u\n",len);
    //print_hex_dump_bytes("writesb :", DUMP_PREFIX_ADDRESS, buf, len);

    len  = HISDIO_ALIGN_4_OR_BLK(len);

    //if(len < HISDIO_BLOCK_SIZE){
    sdio_claim_host(func);
    ret = oal_sdio_writesb(func, HISDIO_REG_FUNC1_FIFO, buf, len);
    if (ret < 0)
    {
        PS_PRINT_ERR("oal_sdio_writesb error:%d\n", ret);
    }
    sdio_release_host(func);
    //}else{
    //    ret = hi110x_sdio_rw_sg(func, SDIO_WRITE, buf, len);
    //}

    return ret;
}

/*
 * Prototype    : sdio_patch_readsb
 * Description  : provide interface for pm driver
 * Input        : uint8* buf, uint32 len uint32 timeout (ms)
 * Output       : None
 * Return Value : int32
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         :
 *     Author       :
 *     Modification : Created function
 *
 */

int32 sdio_patch_readsb(uint8* buf, uint32 len, uint32 timeout)
{
    uint8   int_mask;
    uint8  *ver_info;
    int     ret = 0;
    unsigned long timeout_jiffies;
    uint32  xfer_count;
    int     i;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    struct sdio_func *func = pm_data->pst_wlan_pm_info->pst_sdio->func;


    if (NULL == func)
    {
        PS_PRINT_ERR("sdio device is NOT initialized\n");

        return -FAILURE;
    }

    if (NULL == buf || 0 == len)
    {
        PS_PRINT_ERR("Invalid NULL read buf\n");

        return -FAILURE;
    }


    sdio_claim_host(func);
    timeout_jiffies = OAL_TIME_JIFFY + OAL_MSECS_TO_JIFFIES(timeout);
    for(;;)
    {
        int_mask = oal_sdio_readb(func, HISDIO_REG_FUNC1_INT_STATUS, &ret);
        if(ret)
        {
            PS_PRINT_ERR("read int mask fail, ret=%d\n", ret);
            sdio_release_host(func);
            return -FAILURE;
        }

        if(int_mask & HISDIO_FUNC1_INT_MASK)
        {
            /*sdio int came*/
            break;
        }

        if(oal_time_after(OAL_TIME_JIFFY, timeout_jiffies))
        {
            PS_PRINT_ERR("read int mask timeout, int_mask=%x\n", int_mask);
            sdio_release_host(func);
            return -FAILURE;
        }
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)        
        cpu_relax();
#endif        
    }

    oal_sdio_writeb(func, int_mask, HISDIO_REG_FUNC1_INT_STATUS, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("clear int mask error:%d\n", ret);
        sdio_release_host(func);
        return -FAILURE;
    }
    
    timeout_jiffies = OAL_TIME_JIFFY + OAL_MSECS_TO_JIFFIES(timeout);
    for(;;)
    {
        int_mask = oal_sdio_readb(func, HISDIO_REG_FUNC1_INT_STATUS, &ret);
        if(ret)
        {
            PS_PRINT_ERR("read int mask fail, ret=%d\n", ret);
            sdio_release_host(func);
            return -FAILURE;
        }

        if(0 == (int_mask & HISDIO_FUNC1_INT_MASK))
        {
            /*sdio int came*/
            break;
        }

        if(oal_time_after(OAL_TIME_JIFFY, timeout_jiffies))
        {
            PS_PRINT_ERR("clear int timeout, int_mask=%x\n", int_mask);
            sdio_release_host(func);
            return -FAILURE;
        }
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)        
        cpu_relax();
#endif
    }

    xfer_count = oal_sdio_readl(func, HISDIO_REG_FUNC1_XFER_COUNT, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("read xfer_count err:%d\n", ret);
        sdio_release_host(func);
        return -FAILURE;
    }

    PS_PRINT_DBG("xfer_cout=%d, len=%d\n", xfer_count, len);

    if (xfer_count < len)
    {
        len = xfer_count;
        PS_PRINT_DBG("xfer_count(%d) not equal to len(%d)\n", xfer_count, len);
    }

    ver_info = oal_kzalloc((xfer_count + 1),OAL_GFP_KERNEL);
    if (NULL == ver_info)
    {
        sdio_release_host(func);
        return -ENOMEM;
    }

    memset(ver_info, 0, xfer_count);
    ret = oal_sdio_readsb(func, ver_info, HISDIO_REG_FUNC1_FIFO, xfer_count);
    if (ret < 0)
    {
        PS_PRINT_ERR("hsdio_readsb error:%d\n", ret);
    }
    else
    {
        for (i = 0; i < len; i++)
        {
            buf[i] = ver_info[i];
        }
    }

    PS_PRINT_DBG("=====sdio read:[ret=%d]\n", ret);

    oal_free(ver_info);

    sdio_release_host(func);

    return xfer_count;
}

#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
int32 wlan_power_on_sdio()
{
    uint32_t ret;
    board_power_on();

    ret = oal_sdio_dev_reinit();
    if(SUCC != ret)
    {
        printf("oal_sdio_dev_reinit failed!\r\n");
        goto failed_sdio_enum;
    }

    /*上电时开启GPIO中断*/
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
    ret = firmware_download(WIFI_CFG);
    if(SUCC!=ret)
    {
        PS_PRINT_ERR("firmware power on fail\n");
        board_power_off();
    }
failed_sdio_enum:
    return ret;
}
int32 wlan_power_off_sdio(void)
{
    printf("wlan_power_off_sdio enter.\n");
    //board_power_off_sdio();
    return SUCC;
}

int32_t send_msg(uint8_t * buf, uint32_t len)
{
    int ret;

    struct sdio_func *func = p_gst_sdio_func;

    if (NULL == func)
    {
        PS_PRINT_ERR("Sdio device is NOT initialized\n");
        return -EFAIL;
    }

    if (NULL == buf || len == 0)
    {
        PS_PRINT_ERR("Write buf is NULL\n");
        return -EFAIL;
    }

    PS_PRINT_DBG("======sdio write:%u\n",len);
    //print_hex_dump_bytes("writesb :", DUMP_PREFIX_ADDRESS, buf, len);

    len  = HISDIO_ALIGN_4_OR_BLK(len);

    //if(len < HISDIO_BLOCK_SIZE){
   // sdio_claim_host(func);
    //mmc_acquire_card(func->card);//
    //ret = sdio_writesb(func, HISDIO_REG_FUNC1_FIFO, buf, len);
    ret = sdio_write_fifo_block(func, HISDIO_REG_FUNC1_FIFO, buf, len);
    if (ret < 0)
    {
        PS_PRINT_ERR("oal_sdio_writesb error:%d\n", ret);
    }
    //mmc_release_card(func->card);//
  //  sdio_release_host(func);
    //}else{
    //    ret = hi110x_sdio_rw_sg(func, SDIO_WRITE, buf, len);
    //}

    return ret;
}

read_msg(uint8_t * buf, uint32_t len, uint32_t ms_timeout)
{
    uint8_t   int_mask;
    uint8_t  *ver_info;
    int     ret = 0;
    uint32_t  xfer_count;
    int     i;
    uint64_t tick_last;
    uint64_t timeout_jiffies;

    struct sdio_func *func = p_gst_sdio_func;


    if (NULL == func)
    {
        PS_PRINT_ERR("sdio device is NOT initialized\n");
        return -EFAIL;
    }

    if (NULL == buf || 0 == len)
    {
        PS_PRINT_ERR("Invalid NULL read buf\n");

        return -EFAIL;
    }
    //mmc_acquire_card(func->card);//
    uint64_t beforetick=LOS_TickCountGet();
    timeout_jiffies = beforetick + LOS_MilliSec2Tick(ms_timeout);
    printf("before tick=%lld, lask tick=%lld\r\n", beforetick, timeout_jiffies);
    for(;;)
    {
        int_mask = sdio_read_byte(func, HISDIO_REG_FUNC1_INT_STATUS, &ret);
        if(ret)
        {
            PS_PRINT_ERR("read int mask fail, ret=%d\n", ret);
      //      sdio_release_host(func);
            //mmc_release_card(func->card);//
            return -EFAIL;
        }

        if(int_mask & HISDIO_FUNC1_INT_MASK)
        {
            /*sdio int came*/
            break;
        }
        beforetick=LOS_TickCountGet();
        if((int64_t)timeout_jiffies-(int64_t)beforetick<0)
        {
            PS_PRINT_ERR("read int mask timeout, int_mask=%x\n", int_mask);
    //        sdio_release_host(func);
            //mmc_release_card(func->card);//
            return -EFAIL;
        }
    }

    sdio_write_byte(func, int_mask, HISDIO_REG_FUNC1_INT_STATUS, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("clear int mask error:%d\n", ret);
   //     sdio_release_host(func);
        //mmc_release_card(func->card);//
        return -EFAIL;
    }

    xfer_count = sdio_readl(func, HISDIO_REG_FUNC1_XFER_COUNT, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("read xfer_count err:%d\n", ret);
   //     sdio_release_host(func);
       // mmc_release_card(func->card);//
        return -EFAIL;
    }

    PS_PRINT_DBG("xfer_cout=%d, len=%d\n", xfer_count, len);

    if (xfer_count < len)
    {
        PS_PRINT_DBG("xfer_count(%d) not equal to len(%d)\n", xfer_count, len);
        len = xfer_count;
    }
    if(xfer_count > len)
    {
        ver_info = malloc(xfer_count + 1);
        if (NULL == ver_info)
        {
      //      sdio_release_host(func);
            //mmc_release_card(func->card);//
            return -EFAIL;
        }

        memset(ver_info, 0, xfer_count+1);
        ret = sdio_read_fifo_block(func, ver_info, HISDIO_REG_FUNC1_FIFO, xfer_count);
    }
    else
    {
        ret = sdio_read_fifo_block(func, buf, HISDIO_REG_FUNC1_FIFO, xfer_count);
    }

    if (ret < 0)
    {
        PS_PRINT_ERR("hsdio_readsb error:%d\n", ret);
    }
    else
    {
        if(xfer_count > len)
        {
            for (i = 0; i < len; i++)
            {
                buf[i] = ver_info[i];
            }
        }

    }
    if(xfer_count > len)
    {
       PS_PRINT_DBG("=====sdio read:[ret=%d]\n", ret);
 //   sdio_release_host(func);
   // mmc_release_card(func->card);//
    return xfer_count;
     free(ver_info);
    }
}
#endif


