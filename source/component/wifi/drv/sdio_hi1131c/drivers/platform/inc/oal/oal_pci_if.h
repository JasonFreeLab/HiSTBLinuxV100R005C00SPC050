/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_pci_if.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年2月28日
  最近修改   :
  功能描述   : oal_pci_if.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月28日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_PCI_IF_H__
#define __OAL_PCI_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

#include "oal_types.h"
#include "oal_util.h"
#include "oal_hardware.h"
#include "arch/oal_pci_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_PCI_IF_H

/*****************************************************************************
  2 枚举定义
*****************************************************************************/
/*****************************************************************************
  枚举名  : oal_pci_bar_idx_enum_uint8
  协议表格:
  枚举说明:
*****************************************************************************/
typedef enum
{
    OAL_PCI_BAR_0 = 0,
    OAL_PCI_BAR_1,
    OAL_PCI_BAR_2,
    OAL_PCI_BAR_3,
    OAL_PCI_BAR_4,
    OAL_PCI_BAR_5,

    OAL_PCI_BAR_BUTT
}oal_pci_bar_idx_enum;
typedef oal_uint8 oal_pci_bar_idx_enum_uint8;


/*****************************************************************************
  3 全局变量声明
*****************************************************************************/
extern oal_pci_bar_idx_enum_uint8 g_en_bar_table[1];


/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define OAL_WITP_MAX_BARS   OAL_ARRAY_SIZE(g_en_bar_table)

#define OAL_PCIE_SYS_BASE_PHYS   (0x10100000)        /* SYSCTRL */
#define OAL_DBI_BASE_ADDR_0      (0x10A00000)        /* IO空间 64k */
#define OAL_DBI_BASE_ADDR_1      (0x10A02000)        /* IO空间 64k */
#define OAL_PERI_W_PCIE0	     (0xBC)
#define OAL_PERI_R_PCIE0         (0xC0)
#define OAL_PERI_W_PCIE1         (0xEC)
#define OAL_PERI_R_PCIE1         (0xF0)

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
  结构名  : oal_pcie_iatu_stru
  结构说明: Internal Address Translation Unit(iATU)结构体
*****************************************************************************/
typedef struct
{
    oal_uint32    ul_viewport;          /* iATU Viewport Register                    */
	oal_uint32    ul_region_ctrl_1;     /* iATU Region Control 1 Register            */
	oal_uint32    ul_region_ctrl_2;     /* iATU Region Control 2 Register            */
	oal_uint32    ul_lbar;              /* iATU Region Lower Base Address Register   */
	oal_uint32    ul_ubar;              /* iATU Region Upper Base Address Register   */
	oal_uint32    ul_lar;               /* iATU Region Limit Address Register        */
	oal_uint32    ul_ltar;		        /* iATU Region Lower Target Address Register */
	oal_uint32    ul_utar;              /* iATU Region Upper Target Address Register */
} oal_pcie_iatu_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void oal_pcie_set_inbound_iatu_slip_window(oal_pci_dev_stru *pst_pci_dev);
extern oal_void oal_pcie_set_inbound_iatu(oal_pci_dev_stru *pst_pci_dev);
extern oal_void  oal_pcie_set_outbound_iatu(oal_pci_dev_stru *pst_pci_dev);
extern oal_uint32  oal_pci_ep_reconfig(oal_pci_dev_stru *pst_pci_dev);
extern oal_uint32  oal_pci_rc_reconfig(oal_uint8 uc_chip_id);
extern oal_void  oal_pci_exit(oal_void);
extern oal_uint32  oal_pci_init(oal_void);
extern oal_uint32  oal_5115_pci_init(oal_void);
extern oal_void oal_5115_pci_exit(oal_void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_pci_if.h */
