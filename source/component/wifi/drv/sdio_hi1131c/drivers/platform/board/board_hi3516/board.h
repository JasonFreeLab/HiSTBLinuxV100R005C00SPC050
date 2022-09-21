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
#include "asm/platform.h"
#include "oal_types.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/

#define             BOARD_SUCC                           (0)
#define             BOARD_FAIL                           (-1)

#define             DATA_INT_GPIO_GROUP                  (6)
#define             DATA_INT_GPIO_GROUP_PIN              (5)
#define             WLAN_PM_H2D_GPIO_GROUP               (6)
#define             WLAN_PM_H2D_GPIO_GROUP_PIN           (7)
#define             WLAN_EN_GPIO_GROUP                   (7)
#define             WLAN_EN_GPIO_PIN                     (0)
#define             POWER_EN_GPIO_GROUP                  (7)
#define             POWER_EN_GPIO_PIN                    (1)


#define             GPIO6_5_MUXCTRL_REG53_OFFSET         (0x0D4)
#define             GPIO6_7_MUXCTRL_REG55_OFFSET         (0x0DC)
#define             GPIO7_0_MUXCTRL_REG56_OFFSET         (0x0E0)
#define             GPIO7_1_MUXCTRL_REG57_OFFSET         (0x0E4)


#define             GPIO6_5_MUXCTRL_REG53_VALUE          (0)
#define             GPIO6_7_MUXCTRL_REG55_VALUE          (0)
#define             GPIO7_0_MUXCTRL_REG56_VALUE          (0)
#define             GPIO7_1_MUXCTRL_REG57_VALUE          (0)

#define             GPIO_DIR_IN                          (0)
#define             GPIO_DIR_OUT                         (1)

#define             GPIO_LOW_LEVEl                       (0)
#define             GPIO_HIGH_LEVEL                      (1)

#define             GPIO_IS_EDGE                         (0)
#define             GPIO_IS_LEVEL                        (1)

#define             GPIO_IBE_SINGLE                      (0)
#define             GPIO_IBE_DOUBLE                      (1)


#define             GPIO_IEV_NEGEDGE                     (0)
#define             GPIO_IEV_POSEDGE                     (1)

#define             GPIO_IEV_LOW_LEVEL                   (0)
#define             GPIO_IEV_HIGH_LEVEL                  (1)

#define             GPIO_IE_DISABLE                      (0)
#define             GPIO_IE_ENABLE                       (1)

#define             WALN_IRQ                             NUM_HAL_INTERRUPT_GPIO
#define             INVALID_IRQ                          (-1)

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*private data for pm driver*/
typedef struct {

    /* hi1131c  irq info */
    uint32 wlan_irq;    

    /* evb or fpga verison */
    int32 is_asic;

    /* prepare before board power on */
    int32 need_power_prepare;
}BOARD_INFO;

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern BOARD_INFO * get_board_info(oal_void);
extern int32 hi110x_board_init(oal_void);
extern oal_void hi110x_board_exit(oal_void);
extern oal_void board_power_on(oal_void);
extern oal_void board_power_off(oal_void);
extern oal_int32 board_get_wlan_h2d_pm_state(oal_void);
extern oal_void board_set_wlan_h2d_pm_state(oal_uint32 ul_value);
extern oal_uint32 board_get_and_clear_wlan_gpio_intr_state(oal_void);
extern oal_void wlan_rst(oal_void);

#endif

