/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_bus_if.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月31日
  最近修改   :
  功能描述   : oal_bus_if.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月31日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_BUS_IF_H__
#define __OAL_BUS_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_mem.h"
#include "oal_schedule.h"
#include "oal_util.h"
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include "oal_pci_if.h"
#endif
/*****************************************************************************
  2 枚举定义
*****************************************************************************/

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/


/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define OAL_MAX_BAR_NUM          6          /* 每个设备最大BAR数量 */

/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/




/* 总线设备，DEVICE级 */
typedef struct
{
    oal_uint32       ul_device_id;                       /* 设备号,如0x1151 */
    oal_void        *p_dev;                              /* 指向设备的指针 */
    oal_uint32       ul_irq_num;                         /* 设备中断号 */
    oal_uint8        uc_chip_id;                         /* PCIe号，如PCIe0 */
    oal_uint8        uc_bar_num;                         /* BAR数量 */
    oal_uint8        auc_resv[2];
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];   /* PCI设备I/O区域起始地址 */
#else
    oal_uint32       aul_mem_start[1];
#endif
    oal_irq_dev_stru st_irq_info;
}oal_bus_dev_stru;

/* 总线设备，CHIP级 */
typedef struct
{
    oal_uint8           uc_chip_id;                                /* PCIe号，如PCIe0 */
    oal_uint8        uc_device_num;			/* 该芯片中device个数，应该小于WLAN_DEVICE_MAX_NUM_PER_CHIP */
    oal_uint8        auc_resv[2];
	oal_pci_dev_stru   *pst_pci_device;                            /* 指向所属PCI设备的指针 */
    oal_void           *p_pci_dbi_base;                            /* 指向PCI设备DBI接口的指针，用于配置PCIE内部寄存器 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* 芯片基地址 */
    oal_uint32       aul_mem_start[OAL_WITP_MAX_BARS];
#else
    oal_uint32       aul_mem_start[1];
#endif
    /* device信息 */
    oal_bus_dev_stru st_bus_dev[WLAN_DEVICE_MAX_NUM_PER_CHIP];
}oal_bus_chip_stru;


/*****************************************************************************
  6 消息头定义
*****************************************************************************/


/*****************************************************************************
  7 消息定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  oal_bus_exit(oal_bus_dev_stru *pst_bus_dev);
extern oal_void  oal_bus_find_dev_instance(oal_bus_dev_stru **ppst_bus_dev, oal_void *p_dev);
extern oal_uint32  oal_bus_send(oal_bus_dev_stru *pst_bus, oal_mem_stru *pst_msg_input);
extern oal_uint32  oal_bus_register_irq(oal_void *pst, oal_irq_intr_func p_func, oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void oal_bus_unregister_irq(oal_uint8 uc_chip_id, oal_uint8 uc_device_id);
extern oal_void  oal_bus_get_chip_instance(oal_bus_chip_stru **ppst_bus_chip, oal_uint8 uc_index);
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
extern oal_void oal_bus_irq_affinity_init(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_core_id);
#endif
#endif

extern oal_uint8  oal_bus_get_chip_num(oal_void);
extern oal_uint32  oal_bus_inc_chip_num(oal_void);
extern oal_void oal_bus_init_chip_num(oal_void);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_bus_if.h */
