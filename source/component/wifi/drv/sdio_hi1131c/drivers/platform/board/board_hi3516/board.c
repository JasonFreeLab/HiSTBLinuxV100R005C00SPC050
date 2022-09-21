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

/*lint -e322*//*lint -e7*/
#include <linux/interrupt.h>
#include <asm/hal_platform_ints.h>
#include <linux/delay.h>
/*lint +e322*//*lint +e7*/

#include "board.h"
#include "plat_debug.h"
#include "arch/oal_util.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
BOARD_INFO g_board_info = {0};

/*****************************************************************************
  3 Function Definition
*****************************************************************************/

inline BOARD_INFO * get_board_info(oal_void)
{
    return &g_board_info;
}

oal_void wlan_enable(oal_void)
{
    gpio_write(WLAN_EN_GPIO_GROUP, WLAN_EN_GPIO_PIN, GPIO_HIGH_LEVEL);
}
oal_void wlan_disable(oal_void)
{
    gpio_write(WLAN_EN_GPIO_GROUP, WLAN_EN_GPIO_PIN, GPIO_LOW_LEVEl);
}
oal_void power_enable(oal_void)
{
    gpio_write(POWER_EN_GPIO_GROUP, POWER_EN_GPIO_PIN, GPIO_HIGH_LEVEL);
}
oal_void power_disable(oal_void)
{
    gpio_write(POWER_EN_GPIO_GROUP, POWER_EN_GPIO_PIN, GPIO_LOW_LEVEl);
}

oal_void board_power_on(oal_void)
{
    int clock;
    PS_PRINT_FUNCTION_NAME;
    clock = board_get_wlan_h2d_pm_state();
    board_set_wlan_h2d_pm_state(GPIO_LOW_LEVEl);  // set low, tcxo 40M
    power_disable();
    msleep(10);
    power_enable();
    wlan_enable();
    msleep(30);
    board_set_wlan_h2d_pm_state(clock);
}

int board_get_wlan_wkup_gpio_val(void)
{
    return gpio_mis_read(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN);
}

oal_void wlan_rst(oal_void)
{
    wlan_disable();
    mdelay(5);
    wlan_enable();
    mdelay(50);
}

oal_void board_power_off(oal_void)
{
    PS_PRINT_FUNCTION_NAME;
    power_disable();
    msleep(10);
}

oal_int32 board_get_wlan_h2d_pm_state(oal_void)
{  
    return gpio_read(WLAN_PM_H2D_GPIO_GROUP, WLAN_PM_H2D_GPIO_GROUP_PIN);
}


oal_void board_set_wlan_h2d_pm_state(oal_uint32 ul_value)
{
    if (ul_value)
    {
        gpio_write(WLAN_PM_H2D_GPIO_GROUP, WLAN_PM_H2D_GPIO_GROUP_PIN, GPIO_HIGH_LEVEL);
    }
    else
    {
        gpio_write(WLAN_PM_H2D_GPIO_GROUP, WLAN_PM_H2D_GPIO_GROUP_PIN, GPIO_LOW_LEVEl);
    }
}

oal_uint32 board_get_and_clear_wlan_gpio_intr_state(oal_void)
{
    oal_uint32                ul_gpio_state = 0;
    ul_gpio_state = gpio_mis_read(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN);
    gpio_ic_clear(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN);
    return ul_gpio_state;
}

oal_int32 board_mutex_init(oal_void)
{
    oal_int32 ret= BOARD_FAIL;
    UINTPTR uwIntSave;
    uwIntSave = LOS_IntLock();
    
    writel(GPIO6_5_MUXCTRL_REG53_VALUE, IO_MUX_REG_BASE + GPIO6_5_MUXCTRL_REG53_OFFSET);
    writel(GPIO6_7_MUXCTRL_REG55_VALUE, IO_MUX_REG_BASE + GPIO6_7_MUXCTRL_REG55_OFFSET);
    writel(GPIO7_0_MUXCTRL_REG56_VALUE, IO_MUX_REG_BASE + GPIO7_0_MUXCTRL_REG56_OFFSET);
    writel(GPIO7_1_MUXCTRL_REG57_VALUE, IO_MUX_REG_BASE + GPIO7_1_MUXCTRL_REG57_OFFSET);
    
    (VOID)LOS_IntRestore(uwIntSave); 
    return BOARD_SUCC;    
}

oal_int32 board_gpio_init(oal_void)
{
    oal_int32 ret= BOARD_FAIL;
    UINTPTR uwIntSave;
    uwIntSave = LOS_IntLock();

    gpio_dir_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_DIR_IN);
    gpio_dir_config(WLAN_PM_H2D_GPIO_GROUP,WLAN_PM_H2D_GPIO_GROUP_PIN,GPIO_DIR_OUT);
    gpio_dir_config(WLAN_EN_GPIO_GROUP,WLAN_EN_GPIO_PIN,GPIO_DIR_OUT);
    gpio_dir_config(POWER_EN_GPIO_GROUP,POWER_EN_GPIO_PIN,GPIO_DIR_OUT); 

    (VOID)LOS_IntRestore(uwIntSave); 
    return BOARD_SUCC;    
}

oal_int32 board_irq_init(oal_void)
{
    oal_int32 ret= BOARD_FAIL;
    UINTPTR uwIntSave;
    uwIntSave = LOS_IntLock();

    gpio_dir_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_DIR_IN);
    gpio_is_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_IS_EDGE);
    gpio_ibe_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_IBE_SINGLE);
    gpio_iev_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_IEV_POSEDGE);
    gpio_ic_clear(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN);
    gpio_ie_config(DATA_INT_GPIO_GROUP,DATA_INT_GPIO_GROUP_PIN,GPIO_IE_ENABLE);

    (VOID)LOS_IntRestore(uwIntSave); 

    g_board_info.wlan_irq = WALN_IRQ;
    
    return BOARD_SUCC;    
}

oal_int32 hi110x_board_init(oal_void)
{
    oal_int32 ret = BOARD_FAIL;

    PS_PRINT_FUNCTION_NAME;
    board_mutex_init();
    board_gpio_init();
    board_irq_init();

    ret = BOARD_SUCC;
    return ret;
}

oal_void hi110x_board_exit(oal_void)
{
    g_board_info.wlan_irq = INVALID_IRQ;
}


