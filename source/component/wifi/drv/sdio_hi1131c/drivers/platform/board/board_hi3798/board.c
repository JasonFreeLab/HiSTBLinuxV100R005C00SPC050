/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : board.c
 * Version       : Hi1102
 * Author        : 
 * Created       : 2015/04/08
 * Last Modified :
 * Description   : board resource get
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
#include <linux/of.h>
#include <linux/of_gpio.h>
/*lint -e322*//*lint -e7*/
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/pinctrl/consumer.h>
#include <linux/fs.h>
/*lint +e322*//*lint +e7*/

#include "board.h"
#include "plat_debug.h"
#include "hisi_ini.h"


#define SDIO_REG_WRITEL(Addr, Value)  ((*(volatile unsigned int *)(Addr)) = (Value))
#define SDIO_REG_READL(Addr)          (*(volatile unsigned int *)(Addr))
#if defined(CFG_PRODUCT_TYPE_LINUX)
#define BOARD_INI_FILE_PATH           "/etc/Wireless/firmware/cfg_hisi_1131_hi3798.ini"
#else
#define BOARD_INI_FILE_PATH           "/system/vendor/firmware/cfg_hisi_1131_hi3798.ini"
#endif
#define MAX_BOARD_INI_VAR_LEN         (40)

typedef struct{
    int8        addr_var[MAX_BOARD_INI_VAR_LEN];
    int8        value_var[MAX_BOARD_INI_VAR_LEN];
}stru_board_pinctrl_para;


typedef enum
{
    SDIO_CLK     = 0,
    SDIO_CMD        ,
    SDIO_DATA0      ,
    SDIO_DATA1      ,
    SDIO_DATA2      ,
    SDIO_DATA3      ,
    WLAN_RST        ,
    PMU_PWRON       ,
    DATA_INTR       ,
    HOST2DEV        ,
    BOARD_PINCTRL_INDEX_BUTT,
}BOARD_PINCTRL_INDEX;

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/

stru_board_pinctrl_para      g_ast_board_cfg_para[BOARD_PINCTRL_INDEX_BUTT] = 
{
    {"sdio_clk_addr",           "sdio_clk_val"},
    {"sdio_cmd_addr",           "sdio_cmd_val"},
    {"sdio_data0_addr",         "sdio_data0_val"},
    {"sdio_data1_addr",         "sdio_data1_val"},
    {"sdio_data2_addr",         "sdio_data2_val"},
    {"sdio_data3_addr",         "sdio_data3_val"},     
    {"gpio_wlan_rst_addr",      "gpio_wlan_rst_val"},
    {"gpio_pmu_pwron_addr",     "gpio_pmu_pwron_val"},
    {"gpio_data_intr_addr",     "gpio_data_intr_val"},
    {"gpio_host2dev_addr",      "gpio_host2dev_val"},
};

BOARD_INFO g_board_info = {0};


inline BOARD_INFO * get_board_info(void)
{
    return &g_board_info;
}

int32 board_clk_init(void)
{
    uint32 ul_addr = 0;
    uint32 ul_value = 0;
    long   l_modu_head_ops = 0;
    
    int32 l_ret = BOARD_FAIL;
    struct file *fp = NULL;

    fp = filp_open(BOARD_INI_FILE_PATH, O_RDONLY, 0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("open %s failed!!!", BOARD_INI_FILE_PATH);
        return BOARD_FAIL;
    }
    PS_PRINT_INFO("open %s succ!", BOARD_INI_FILE_PATH);

    l_ret = board_ini_find_modu(fp);
    if (BOARD_FAIL == l_ret)
    {
        PS_PRINT_ERR("can't find board ini modu!!!");
        goto err;
    }

    l_modu_head_ops = fp->f_pos;

    PS_PRINT_INFO("file ops is 0x%lx\n",l_modu_head_ops);
    
    l_ret = board_ini_find_var(fp, "wifi_clk_mux_addr", &ul_addr);
    if ((BOARD_FAIL == l_ret) || (ul_addr == 0x0))
    {
        goto err;
    }

    ul_value = SDIO_REG_READL(IO_ADDRESS(ul_addr));
    ul_value |= (0x2 << 3);//配置wifi_clk管脚复用
    
    PS_PRINT_INFO("wifi_clk_mux_addr=0x%x\n", ul_addr);    
    PS_PRINT_INFO("value=0x%x\n", ul_value);
    
    SDIO_REG_WRITEL(IO_ADDRESS(ul_addr), ul_value);
    PS_PRINT_INFO("addr value=0x%x\n", SDIO_REG_READL(IO_ADDRESS(ul_addr)));

    ul_addr = 0;
    ul_value = 0;
    fp->f_pos = l_modu_head_ops;
    
    l_ret = board_ini_find_var(fp, "wifi_clk_en_addr", &ul_addr);
    if ((BOARD_FAIL == l_ret) || (ul_addr == 0x0))
    {
        goto err;
    }
    PS_PRINT_INFO("wifi_clk_en_addr=0x%x\n", ul_addr);
    
    ul_value = SDIO_REG_READL(IO_ADDRESS(ul_addr));
    ul_value |= (0x1 << 16);//配置wifi_clk使能
    
    PS_PRINT_INFO("value=0x%x\n", ul_value);
        
    SDIO_REG_WRITEL(IO_ADDRESS(ul_addr), ul_value);
    PS_PRINT_INFO("value=0x%x\n", SDIO_REG_READL(IO_ADDRESS(ul_addr)));
    filp_close(fp, NULL);
    
    return BOARD_SUCC;
err:
   filp_close(fp, NULL);
   return BOARD_FAIL; 
}

int32 board_cfg_init(void)
{
    uint32 ul_addr = 0;
    uint32 ul_value = 0;
    long   l_modu_head_ops = 0;
    
    int32 l_ret = BOARD_FAIL;
    uint32 i = 0;
    INI_FILE *fp = NULL;
    
    fp = filp_open(BOARD_INI_FILE_PATH, O_RDONLY, 0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("open %s failed!!!", BOARD_INI_FILE_PATH);
        return BOARD_FAIL;
    }
    PS_PRINT_INFO("open %s succ!", BOARD_INI_FILE_PATH);

    l_ret = board_ini_find_modu(fp);
    if (BOARD_FAIL == l_ret)
    {
        PS_PRINT_ERR("can't find board ini modu!!!");
        goto err;
    }

    l_modu_head_ops = fp->f_pos;

    printk("file ops is 0x%lx\n",l_modu_head_ops);
    
    for (i=0; i<BOARD_PINCTRL_INDEX_BUTT; i++)
    {

        fp->f_pos = l_modu_head_ops;
        
        l_ret = board_ini_find_var(fp, g_ast_board_cfg_para[i].addr_var, &ul_addr);
        if ((BOARD_FAIL == l_ret) || (ul_addr == 0x0))
        {
            goto err;
        }
        PS_PRINT_INFO("addr=0x%x\n", ul_addr);
        
        fp->f_pos = l_modu_head_ops;
        l_ret = board_ini_find_var(fp, g_ast_board_cfg_para[i].value_var, &ul_value);
        if (BOARD_FAIL == l_ret)
        {
            goto err;
        }
        PS_PRINT_INFO("value=0x%x\n", ul_value);
        
        SDIO_REG_WRITEL(IO_ADDRESS(ul_addr), ul_value);
        PS_PRINT_INFO("addr value=0x%x\n", SDIO_REG_READL(IO_ADDRESS(ul_addr)));

    }
    filp_close(fp, NULL);    
    return BOARD_SUCC;
    
err:
   filp_close(fp, NULL);
   return BOARD_FAIL;    
}


int32 board_power_gpio_init(void)
{
    int32 ret= BOARD_FAIL;

    PS_PRINT_INFO("in func\n");

    g_board_info.power_on_enable = GPIO_PMU_PWRON;
    ret = gpio_request_one(g_board_info.power_on_enable, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_POWEN_ON);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_POWEN_ON);
        goto err_get_power_on_gpio;
    }

    g_board_info.wlan_en = GPIO_WL_RST_N;
    ret = gpio_request_one(g_board_info.wlan_en, GPIOF_OUT_INIT_HIGH, PROC_NAME_GPIO_WLAN_EN);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_WLAN_EN);
        goto err_get_wlan_en_gpio;
    }

    /*host to device gpio request*/
    g_board_info.wlan_host_to_device = GPIO_HOST_TO_DEVICE;
    ret = gpio_request_one(g_board_info.wlan_host_to_device, GPIOF_OUT_INIT_HIGH, PROC_NAME_GPIO_HOST_TO_DEVICE);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_HOST_TO_DEVICE);
        goto err_get_host_to_device;
    }

    return BOARD_SUCC;

    err_get_host_to_device:
        gpio_free(g_board_info.wlan_en);
    err_get_wlan_en_gpio:
        gpio_free(g_board_info.power_on_enable);
    err_get_power_on_gpio:

    return BOARD_FAIL;
}

void board_power_gpio_exit(void)
{
    PS_PRINT_FUNCTION_NAME;

    gpio_free(g_board_info.power_on_enable);
    gpio_free(g_board_info.wlan_en);
    gpio_free(g_board_info.wlan_host_to_device);

    /* 卸载成功后，输出打印 */
    printk("board exit ok!\n");
    return;
}

int32 board_gpio_init(void)
{
    int32 ret= BOARD_FAIL;

    PS_PRINT_INFO("in func\n");

    g_board_info.power_on_enable = GPIO_PMU_PWRON;
    ret = gpio_request_one(g_board_info.power_on_enable, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_POWEN_ON);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_POWEN_ON);
        goto err_get_power_on_gpio;
    }

    g_board_info.wlan_en = GPIO_WL_RST_N;
    ret = gpio_request_one(g_board_info.wlan_en, GPIOF_OUT_INIT_HIGH, PROC_NAME_GPIO_WLAN_EN);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_WLAN_EN);
        goto err_get_wlan_en_gpio;
    }

    /*wifi wake host gpio request*/
    g_board_info.wlan_wakeup_host = GPIO_DEVICE_TO_HOST;
    ret = gpio_request_one(g_board_info.wlan_wakeup_host, GPIOF_IN, PROC_NAME_GPIO_WLAN_WAKEUP_HOST);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_WLAN_WAKEUP_HOST);
        goto err_get_wlan_wkup_host_gpio;
    }

    /*host to device gpio request*/
    g_board_info.wlan_host_to_device = GPIO_HOST_TO_DEVICE;
    ret = gpio_request_one(g_board_info.wlan_host_to_device, GPIOF_OUT_INIT_HIGH, PROC_NAME_GPIO_HOST_TO_DEVICE);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_HOST_TO_DEVICE);
        goto err_get_host_to_device;
    }

    /*data interrupt gpio request*/
    g_board_info.wlan_data_intr = GPIO_DATA_INTR;
    ret = gpio_request_one(g_board_info.wlan_data_intr, GPIOF_IN, PROC_NAME_GPIO_DATA_INTR);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_DATA_INTR);
        goto err_get_wlan_data_intr;
    }

    return BOARD_SUCC;

    err_get_wlan_data_intr:
        gpio_free(g_board_info.wlan_host_to_device);
    err_get_host_to_device:
        gpio_free(g_board_info.wlan_wakeup_host);
    err_get_wlan_wkup_host_gpio:
        gpio_free(g_board_info.wlan_en);
    err_get_wlan_en_gpio:
        gpio_free(g_board_info.power_on_enable);
    err_get_power_on_gpio:

    return BOARD_FAIL;
}

int board_get_wlan_wkup_gpio_val(void)
{
    return gpio_get_value(g_board_info.wlan_wakeup_host);
}

int board_get_wlan_host_to_dev_gpio_val(void)
{
    return gpio_get_value(g_board_info.wlan_host_to_device);
}


void board_set_host_to_dev_gpio_val_low(void)
{
    gpio_direction_output(g_board_info.wlan_host_to_device, GPIO_LOWLEVEL);
}

void board_set_host_to_dev_gpio_val_high(void)
{
    gpio_direction_output(g_board_info.wlan_host_to_device, GPIO_HIGHLEVEL);
}

void set_host_to_dev_gpio_val(int val)
{
    if(GPIO_HIGHLEVEL == val)
    {
        board_set_host_to_dev_gpio_val_high();
    }
    else
    {
        board_set_host_to_dev_gpio_val_low();
    }
}

void board_set_wlan_h2d_pm_state(unsigned int ul_value)
{
    if (ul_value)
    {
        gpio_direction_output(g_board_info.wlan_host_to_device, GPIO_HIGHLEVEL);
    }
    else
    {
        gpio_direction_output(g_board_info.wlan_host_to_device, GPIO_LOWLEVEL);
    }
}

int32 board_irq_init(void)
{
    uint32 irq = 0;
    int32 gpio = 0;

    PS_PRINT_INFO("in func\n");

    gpio = g_board_info.wlan_data_intr;
    irq = gpio_to_irq(gpio);
    g_board_info.wlan_irq = irq;

    PS_PRINT_INFO("wlan_irq is %d\n", g_board_info.wlan_irq);

    return BOARD_SUCC;
}




void board_power_on(void)
{
#ifdef CONFIG_DEV_CLK_40M
    SET_CLOCK_40M();
#else
    SET_CLOCK_24M();
#endif
    gpio_direction_output(g_board_info.power_on_enable, GPIO_LOWLEVEL);
    mdelay(10);
    gpio_direction_output(g_board_info.power_on_enable, GPIO_HIGHLEVEL);
    mdelay(30);
}

void board_power_off(void)
{
    gpio_direction_output(g_board_info.power_on_enable, GPIO_LOWLEVEL);
}

void wlan_rst(void)
{
    gpio_direction_output(g_board_info.wlan_en, GPIO_LOWLEVEL);
    mdelay(5);
    gpio_direction_output(g_board_info.wlan_en, GPIO_HIGHLEVEL);
    mdelay(30);
}


void himciv200_sdio_card_detect_change(void)
{
    unsigned int regval;
    regval = SDIO_REG_READL(SDIO_CARD_CTRL);

    regval ^=  0x1;
       
    SDIO_REG_WRITEL(SDIO_CARD_CTRL, regval );
}

int32 hi110x_board_init(void)
{
    int32 ret = BOARD_FAIL;

    PS_PRINT_FUNCTION_NAME;

    ret = board_gpio_init();
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = board_irq_init();
    if (BOARD_SUCC != ret)
    {
        goto err_gpio_source;
    }
    return ret;
err_gpio_source:
        gpio_free(g_board_info.wlan_wakeup_host);
        gpio_free(g_board_info.power_on_enable);
        return BOARD_FAIL;
}

void hi110x_board_exit(void)
{
    PS_PRINT_FUNCTION_NAME;

    gpio_free(g_board_info.power_on_enable);
    gpio_free(g_board_info.wlan_en);
    gpio_free(g_board_info.wlan_wakeup_host);
    gpio_free(g_board_info.wlan_host_to_device);
    gpio_free(g_board_info.wlan_data_intr);

    /* 卸载成功后，输出打印 */
    printk("board exit ok!\n");
    return;
}


