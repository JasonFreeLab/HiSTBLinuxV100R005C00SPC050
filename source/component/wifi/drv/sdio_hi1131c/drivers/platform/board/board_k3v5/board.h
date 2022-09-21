/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : board.h
  Version    : first draft
  Author     : 
  Create date: 2015/04/08
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015/04/08
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include "plat_type.h"

/*****************************************************************************
  2 Define macro
*****************************************************************************/

#define BOARD_SUCC                           (0)
#define BOARD_FAIL                           (-1)

#define GPIO_LOWLEVEL                        (0)
#define GPIO_HIGHLEVEL                       (1)

#define NO_NEED_POWER_PREPARE                (0)
#define NEED_POWER_PREPARE                   (1)

#define GPIO_HOST_TO_DEVICE                  (222)
#define GPIO_PMU_PWRON                       (24)
#define GPIO_WL_RST_N                        (29)


#define DTS_NODE_HI110X                     "hisilicon,hi1102"
#define DTS_NODE_HI110X_BFGX                "hisilicon,hisi_bfgx"
#define DTS_NODE_HI110X_WIFI                "hisilicon,hisi_wifi"

#define DTS_COMP_HI110X_BOARD_NAME          DTS_NODE_HI110X

#define DTS_PROP_GPIO_POWEN_ON              "hi1102,gpio_power_on"
#define DTS_PROP_GPIO_WLAN_WAKEUP_HOST      "hi1102,gpio_wlan_wakeup_host"
#define DTS_PROP_GPIO_BFGN_WAKEUP_HOST      "hi1102,gpio_bfgn_wakeup_host"
#define DTS_PROP_GPIO_BFGN_IR_CTRL          "hi1102,gpio_bfgn_ir_ctrl"
#define DTS_PROP_UART_POART                 "hi1102,uart_port"
#define DTS_PROP_CLK_32K                    "huawei,pmu_clk32b"
#define DTS_PROP_VERSION                    "hi1102,asic_version"
#define DTS_PROP_POWER_PREPARE              "hi1102,power_prepare"

#define PROC_NAME_GPIO_POWEN_ON             "power_on_enable"
#define PROC_NAME_GPIO_WLAN_EN              "wlan_en_enable"
#define PROC_NAME_GPIO_WLAN_WAKEUP_HOST     "wlan_wake_host"
#define PROC_NAME_GPIO_HOST_TO_DEVICE       "host_to_device"


#define VERSION_FPGA                (0)
#define VERSION_ASIC                (1)

#define GET_CLOCK_GPIO_VAL()                board_get_wlan_host_to_dev_gpio_val()
#define SET_CLOCK_40M()                     board_set_host_to_dev_gpio_val_low()
#define SET_CLOCK_24M()                     board_set_host_to_dev_gpio_val_high()
#define RESTORE_CLOCK_GPIO_VAL(val)         set_host_to_dev_gpio_val(val)

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*private data for pm driver*/
typedef struct {
	/* hi110x gpio info */
    int32 power_on_enable;
    int32 wlan_en;
    int32 wlan_wakeup_host;
    int32 wlan_host_to_device;

	/* hi110x irq info */
	uint32 wlan_irq;	

	/* hi110x clk info */
	const char * clk_32k_name;
	struct clk* clk_32k;

    /* evb or fpga verison */
    int32 is_asic;

    /* prepare before board power on */
    int32 need_power_prepare;
	struct pinctrl *pctrl;
	struct pinctrl_state *pins_normal;
	struct pinctrl_state *pins_idle;
}BOARD_INFO;

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern BOARD_INFO * get_board_info(void);
extern int32 hi110x_board_init(void);
extern void hi110x_board_exit(void);
extern void board_power_on(void);
extern void board_power_off(void);
extern int board_get_bwkup_gpio_val(void);
extern int board_get_wlan_wkup_gpio_val(void);
extern int board_get_wlan_host_to_dev_gpio_val(void);
extern void board_set_host_to_dev_gpio_val_low(void);
extern void board_set_host_to_dev_gpio_val_high(void);
extern void board_set_wlan_h2d_pm_state(unsigned int ul_value);
extern void set_host_to_dev_gpio_val(int val);
extern void wlan_rst(void);


#endif

