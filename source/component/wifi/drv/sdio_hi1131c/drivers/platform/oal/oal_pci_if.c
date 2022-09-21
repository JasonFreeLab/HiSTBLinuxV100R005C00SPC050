/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_pci.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年2月18日
  最近修改   :
  功能描述   : PCIe驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_hardware.h"
#include "oal_bus_if.h"
#include "oal_pci_if.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_PCI_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* PCI驱动支持的设备列表 */

#define OAL_PCI_WITP_DEVICE_ID    0x1151

OAL_CONST oal_pci_device_id_stru g_st_pci_id_table[] =
{
    {0x168c, 0x0007, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x0012, PCI_ANY_ID, PCI_ANY_ID },
    {0xa727, 0x0013, PCI_ANY_ID, PCI_ANY_ID }, /* 3com */
    {0x10b7, 0x0013, PCI_ANY_ID, PCI_ANY_ID }, /* 3com 3CRDAG675 */
    {0x168c, 0x1014, PCI_ANY_ID, PCI_ANY_ID }, /* IBM minipci 5212 */
    {0x168c, 0x101a, PCI_ANY_ID, PCI_ANY_ID }, /* some Griffin-Lite */
    {0x168c, 0x0015, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x0016, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x0017, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x0018, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x0019, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x001a, PCI_ANY_ID, PCI_ANY_ID },
    {0x168c, 0x001b, PCI_ANY_ID, PCI_ANY_ID }, /* Eagle */
    {0x168c, 0x001d, PCI_ANY_ID, PCI_ANY_ID }, /* Nala */
    {0x168c, 0xff1d, PCI_ANY_ID, PCI_ANY_ID }, /* owl emulation */
    {0x168c, 0xff1c, PCI_ANY_ID, PCI_ANY_ID }, /* owl emulation */
    {0x168c, 0x0023, PCI_ANY_ID, PCI_ANY_ID }, /* PCI (MB/CB)   */
    {0x168c, 0x0024, PCI_ANY_ID, PCI_ANY_ID }, /* PCI-E (XB)    */
    {0x168c, 0x0027, PCI_ANY_ID, PCI_ANY_ID }, /* Sowl PCI      */
    {0x168c, 0x0029, PCI_ANY_ID, PCI_ANY_ID }, /* Merlin PCI    */
    {0x168c, 0x002a, PCI_ANY_ID, PCI_ANY_ID }, /* Merlin PCIE   */
    {0x168c, 0x002b, PCI_ANY_ID, PCI_ANY_ID }, /* Kite PCIE     */
    {0x168c, 0x002d, PCI_ANY_ID, PCI_ANY_ID }, /* Kiwi PCI      */
    {0x168c, 0x002e, PCI_ANY_ID, PCI_ANY_ID }, /* Kiwi PCIE     */
    {0x168c, 0xabcd, PCI_ANY_ID, PCI_ANY_ID }, /* Osprey PCIE Emulation   */
    {0x168c, 0x0030, PCI_ANY_ID, PCI_ANY_ID }, /* Osprey PCIE   */
    {0x168c, 0x0033, PCI_ANY_ID, PCI_ANY_ID }, /* Peacock PCIE  */
    {0x19e5, 0x1151, PCI_ANY_ID, PCI_ANY_ID }, /* 1151 PCIE  */
    {0, }
};

oal_pci_bar_idx_enum_uint8 g_en_bar_table[1] =
{
    OAL_PCI_BAR_0,   /* 256KB地址空间，用于SoC MAC PHY地址映射 */
};

/* 静态函数声明 */
OAL_STATIC oal_int32  oal_pci_probe(oal_pci_dev_stru *pst_pci_dev, OAL_CONST oal_pci_device_id_stru *pst_id);
OAL_STATIC oal_void  oal_pci_remove(oal_pci_dev_stru *pst_pci_dev);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
OAL_STATIC oal_int32 oal_pci_suspend(oal_pci_dev_stru *pst_pci_dev,oal_pm_message_t state);
OAL_STATIC oal_int32 oal_pci_resume(oal_pci_dev_stru *pst_pci_dev);

#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT) || (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT))
extern int  pcie_sys_reinit(unsigned int mode_sel);
#elif(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT)
    /* WS835低功耗需要的pcie复位函数看是否后续需要，再添加 */
#else
extern int  hi_pcie_reinit(unsigned int ui_ch);
#endif
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
OAL_STATIC oal_pci_driver_stru g_st_pci_drv =
{
    .name       = "witp_pci",
    .id_table   = g_st_pci_id_table,
    .probe      = oal_pci_probe,
    .remove     = oal_pci_remove,
    .suspend    = oal_pci_suspend,
    .resume     = oal_pci_resume,
};
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
OAL_STATIC oal_pci_driver_stru g_st_pci_drv =
{
    "witp_pci",
    g_st_pci_id_table,
    oal_pci_probe,
    oal_pci_remove
};
#endif


oal_void *g_pst_5115_sys_ctl = OAL_PTR_NULL;
oal_void *g_pst_5610_mode    = OAL_PTR_NULL;
oal_void *g_pst_5610_gpio    = OAL_PTR_NULL;
#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
oal_void *g_pst_5610_gpio1   = OAL_PTR_NULL;   /* 0x10106000地址 */
oal_void *g_pst_5610_gpio2   = OAL_PTR_NULL;   /* 0x10108000地址 */
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
OAL_STATIC oal_int32 oal_pci_suspend(oal_pci_dev_stru *pst_pci_dev,oal_pm_message_t state)
{
     OAL_IO_PRINT("enter oal_pcie_suspend\n");

     return OAL_SUCC;
}

OAL_STATIC oal_int32 oal_pci_resume(oal_pci_dev_stru *pst_pci_dev)
{
     OAL_IO_PRINT("enter oal_pcie_resume\n");

     return OAL_SUCC;
}
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_pcie_set_inbound_iatu
 功能描述  : 设置EP端iATU表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_pcie_set_inbound_iatu(oal_pci_dev_stru *pst_pci_dev)
{
    /* iATU0:BAR0:SoC MAC PHY: 256KB */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x200, 0x80000000);                                           /* view index */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x204, 0x0);                                                  /* ctrl 1 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x208, 0x80000000);                                           /* ctrl 2 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x20c, oal_pci_resource_start(pst_pci_dev, OAL_PCI_BAR_0));   /* base lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x210, 0);                                                    /* base upper */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x214, oal_pci_resource_end(pst_pci_dev, OAL_PCI_BAR_0));     /* limit */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x218, 0x20000000);                                           /* target lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x21c, 0);

    /* 配置命令寄存器                                                                         */
    /* BIT0 = 1(I/O Space Enable), BIT1 = 1(Memory Space Enable), BIT2 = 1(Bus Master Enable) */
    oal_pci_write_config_word(pst_pci_dev, 0x04, 0x7);
}

/*****************************************************************************
 函 数 名  : oal_pcie_set_inbound_iatu_slip_window
 功能描述  : 设置滑窗后的EP端iATU表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_void oal_pcie_set_inbound_iatu_slip_window(oal_pci_dev_stru *pst_pci_dev)
{

    /* iATU0:BAR0:SoC MAC PHY: 256KB */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x200, 0x80000000);                                           /* view index */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x204, 0x0);                                                  /* ctrl 1 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x208, 0x80000000);                                           /* ctrl 2 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x20c, oal_pci_resource_start(pst_pci_dev, OAL_PCI_BAR_0));   /* base lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x210, 0);                                                    /* base upper */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x214, oal_pci_resource_end(pst_pci_dev, OAL_PCI_BAR_0));     /* limit */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x218, 0x20040000);                                           /* target lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x21c, 0);

    /* 配置命令寄存器                                                                         */
    /* BIT0 = 1(I/O Space Enable), BIT1 = 1(Memory Space Enable), BIT2 = 1(Bus Master Enable) */
    oal_pci_write_config_word(pst_pci_dev, 0x04, 0x7);
}


/*****************************************************************************
 函 数 名  : oal_pcie_set_outbound_iatu
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_pcie_set_outbound_iatu(oal_pci_dev_stru *pst_pci_dev)
{
    /* iATU1:512M */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x200, 0x1);            /* view index */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x204, 0x0);            /* ctrl 1 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x208, 0x80000000);     /* ctrl 2 */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x20c, 0x0);            /* base lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x210, 0);              /* base upper */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x214, 0x1FFFFFFF);     /* limit */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x218, 0x80000000);     /* target lower */
    oal_pci_write_config_dword(pst_pci_dev, 0x700 + 0x21c, 0);              /* target upper */

    /* 配置命令寄存器                                                                         */
    /* BIT0 = 1(I/O Space Enable), BIT1 = 1(Memory Space Enable), BIT2 = 1(Bus Master Enable) */
    oal_pci_write_config_word(pst_pci_dev, 0x04, 0x7);
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : oal_pci_debug_info
 功能描述  : 打印PCIe调试信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  oal_pci_debug_info(oal_pci_dev_stru *pst_pci_dev)
{
    oal_pci_bar_idx_enum_uint8   en_index;
    oal_uint32                   aul_bar[OAL_PCI_BAR_BUTT];
    oal_uint32                   aul_len[OAL_PCI_BAR_BUTT];

    for (en_index = 0; en_index < OAL_PCI_BAR_BUTT; en_index++)
    {
        aul_bar[en_index] = oal_pci_resource_start(pst_pci_dev, en_index);
        aul_len[en_index] = oal_pci_resource_len(pst_pci_dev, en_index);

        OAL_IO_PRINT("bar%d: 0x%x, len = 0x%x\n", en_index, aul_bar[en_index], aul_len[en_index]);
    }
}
#endif

/*****************************************************************************
 函 数 名  : oal_pci_witp_init
 功能描述  : WITP 1151 PCI探测初始化函数
 输入参数  : pst_pci_dev: 指向PCI设备
             ul_dev_id     : PCI设备号
 输出参数  : 无
 返 回 值  : Linux错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32 oal_pci_witp_init(oal_pci_dev_stru *pst_pci_dev, oal_uint32 ul_dev_id)
{
    oal_uint8                    uc_index;
    oal_uint8                    uc_subidx;
    oal_pci_bar_idx_enum_uint8   en_bar_idx;
    oal_uint32                   aul_bar[OAL_WITP_MAX_BARS];
    oal_uint32                   aul_len[OAL_WITP_MAX_BARS];
    oal_uint32                   aul_mem[OAL_WITP_MAX_BARS];
    oal_uint8                    uc_chip_idx;              /* 当前已探测到的芯片编号 */
    oal_bus_chip_stru           *pst_bus_chip = OAL_PTR_NULL;
    oal_bus_dev_stru            *pst_bus_dev;
    oal_uint32                   ul_ret;

    /* 获取当前总线上chip的索引 */
    uc_chip_idx = oal_bus_get_chip_num();

    oal_bus_get_chip_instance(&pst_bus_chip, uc_chip_idx);
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_bus_chip))
    {
         OAL_IO_PRINT("oal_pci_witp_init: OAL_PTR_NULL == pst_bus_chip!\n");
         return -OAL_EIO;
    }

    if(0 == uc_chip_idx)
    {
    pst_bus_chip->p_pci_dbi_base = oal_ioremap_nocache(OAL_DBI_BASE_ADDR_0, 0x1000);
    }
    else if(1 == uc_chip_idx)
    {
        pst_bus_chip->p_pci_dbi_base = oal_ioremap_nocache(OAL_DBI_BASE_ADDR_1, 0x1000);
    }
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_bus_chip->p_pci_dbi_base))
    {
        OAL_IO_PRINT("oal_pci_witp_init::Cannot map dbi base for pcie%d!\n", uc_chip_idx);

        return -OAL_EIO;
    }

    pst_bus_chip->uc_chip_id     = uc_chip_idx;
    pst_bus_chip->pst_pci_device = pst_pci_dev;

     /* 1151芯片是DBSC，所以device数量一定为1 */
    pst_bus_chip->uc_device_num = 1;

    /* 获取BUS DEV结构体 */
    pst_bus_dev = &pst_bus_chip->st_bus_dev[0];

    for (uc_index = 0; uc_index < OAL_WITP_MAX_BARS; uc_index++)
    {
        en_bar_idx = g_en_bar_table[uc_index];
        aul_bar[uc_index] = oal_pci_resource_start(pst_pci_dev, en_bar_idx);
        aul_len[uc_index] = oal_pci_resource_len(pst_pci_dev, en_bar_idx);

        OAL_IO_PRINT("BAR %d: set to [mem 0x%x, len = 0x%x]\n",
                     en_bar_idx, aul_bar[uc_index], aul_len[uc_index]);

        /* 申请IO内存资源，此处witp字符串是IO内存资源的名字 */
        if (!oal_request_mem_region(aul_bar[uc_index], aul_len[uc_index], "witp"))
        {
            OAL_IO_PRINT("BAR %d, pci: cannot reserve PCI memory region\n", en_bar_idx);

            for (uc_subidx = 0; uc_subidx < uc_index; uc_subidx++)
            {
                oal_release_mem_region(aul_bar[uc_subidx], aul_len[uc_subidx]);
            }

            oal_pci_disable_device(pst_pci_dev);

            return -OAL_ENODEV;
        }

        aul_mem[uc_index] = (oal_uint)oal_ioremap(aul_bar[uc_index], aul_len[uc_index]);

        OAL_IO_PRINT("BAR %d: ioremap addr = 0x%x\n", en_bar_idx, aul_mem[uc_index]);

        /*lint -e774*/ /* WIN32封装下ul_mem是常量，if判断总是false */
        if (!aul_mem[uc_index])
        {
            OAL_IO_PRINT("BAR %d, pci: cannot remap PCI memory region\n", en_bar_idx);

            for (uc_subidx = 0; uc_subidx < uc_index; uc_subidx++)
            {
                oal_iounmap((OAL_VOLATILE oal_void *)(aul_mem[uc_subidx]));
            }

            for (uc_subidx = 0; uc_subidx <= uc_index; uc_subidx++)
            {
                oal_release_mem_region(aul_bar[uc_subidx], aul_len[uc_subidx]);
            }

            oal_pci_disable_device(pst_pci_dev);

            return -OAL_ENODEV;
        }
        /* lint +e774 */
    }

    /* 保存基地址，1151芯片的基地址等于device的基地址 */
    oal_memcopy(pst_bus_dev->aul_mem_start, aul_mem, OAL_WITP_MAX_BARS * OAL_SIZEOF(oal_uint32));
    oal_memcopy(pst_bus_chip->aul_mem_start, aul_mem, OAL_WITP_MAX_BARS * OAL_SIZEOF(oal_uint32));

    /* 总线上的chip数量增加1 */
    ul_ret = oal_bus_inc_chip_num();
    if(OAL_SUCC != ul_ret)
    {
         OAL_IO_PRINT("oal_pci_probe: oal_bus_inc_chip_num failed!\n");
         return -OAL_EIO;
    }

    /* 更新其他信息 */
    pst_bus_dev->uc_chip_id   = pst_bus_chip->uc_chip_id;
    pst_bus_dev->p_dev        = pst_pci_dev;
    pst_bus_dev->ul_irq_num   = pst_pci_dev->irq;
    pst_bus_dev->ul_device_id = ul_dev_id;
    pst_bus_dev->uc_bar_num   = OAL_WITP_MAX_BARS;

    /* 设置inbound iATU表 */
    oal_pcie_set_inbound_iatu(pst_pci_dev);

    /* 设置outbound iATU表 */
    oal_pcie_set_outbound_iatu(pst_pci_dev);

    OAL_IO_PRINT("WITP: pci_dev->irq      : %d.\n",   pst_bus_dev->ul_irq_num);


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_pci_probe
 功能描述  : PCI探测函数
 输入参数  : pst_pci_dev: 指向PCI设备
             pst_id     : PCI设备表
 输出参数  : 无
 返 回 值  : Linux错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32  oal_pci_probe(oal_pci_dev_stru *pst_pci_dev, OAL_CONST oal_pci_device_id_stru *pst_id)
{
    oal_uint32                   ul_dev_id;
    oal_int32                    l_ret;

    OAL_IO_PRINT("pci probe begin!\n");

    if((OAL_PTR_NULL == pst_pci_dev) || (OAL_PTR_NULL == pst_id))
    {
        OAL_IO_PRINT("pci: pci_enable_device I/O error!\n");
        return -OAL_EIO;
    }

    if (oal_pci_enable_device(pst_pci_dev))
    {
        OAL_IO_PRINT("pci: pci_enable_device I/O error!\n");

        return -OAL_EIO;
    }

#ifdef _PRE_DEBUG_MODE
    oal_pci_debug_info(pst_pci_dev);
#endif

    /* 获取chip中的device id */
    ul_dev_id = OAL_PCI_GET_DEV_ID(pst_id);

    /* 1151 chip的初始化 */
    if(OAL_PCI_WITP_DEVICE_ID == ul_dev_id)
    {
        l_ret = oal_pci_witp_init(pst_pci_dev, ul_dev_id);
        if(OAL_SUCC != l_ret)
        {
            OAL_IO_PRINT("oal_pci_probe: OAL_SUCC != l_ret!\n");
            return -OAL_EIO;
        }
    }
    else
    {
        /* 暂不支持其他芯片 */
        OAL_IO_PRINT("oal_pci_probe: unknown device id (%d)!\n", ul_dev_id);
        return -OAL_EIO;
    }

    OAL_IO_PRINT("PCI driver: probe succ!\n");

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oal_pci_witp_remove
 功能描述  : WITP PCI探测函数
 输入参数  : pst_pci_dev: 指向PCI设备
             pst_id     : PCI设备表
 输出参数  : 无
 返 回 值  : Linux错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void oal_pci_witp_remove(oal_pci_dev_stru *pst_pci_dev)
{
    oal_uint8            uc_index;
    oal_bus_chip_stru   *pst_bus_chip;
    oal_bus_dev_stru    *pst_bus_dev;

    oal_bus_find_dev_instance(&pst_bus_dev, (oal_void *)pst_pci_dev);
    if(OAL_PTR_NULL == pst_bus_dev)
    {
        OAL_IO_PRINT("oal_pci_witp_remove: remove driver failed: OAL_PTR_NULL == pst_bus_dev\n");
        return;
    }

    oal_bus_get_chip_instance(&pst_bus_chip, pst_bus_dev->uc_chip_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_bus_chip))
    {
        OAL_IO_PRINT("oal_pci_witp_remove: remove driver failed: OAL_PTR_NULL == pst_bus_chip\n");
        return;
    }

    oal_iounmap((OAL_VOLATILE oal_void *)(pst_bus_chip->p_pci_dbi_base));

    for (uc_index = 0; uc_index < OAL_WITP_MAX_BARS; uc_index++)
    {
        oal_iounmap((OAL_VOLATILE oal_void *)(pst_bus_dev->aul_mem_start[uc_index]));

        oal_release_mem_region(oal_pci_resource_start(pst_pci_dev, g_en_bar_table[uc_index]),
                               oal_pci_resource_len(pst_pci_dev, g_en_bar_table[uc_index]));
    }

    return;
}

/*****************************************************************************
 函 数 名  : oal_pci_remove
 功能描述  : pci设备移除函数
 输入参数  : pst_pci_dev: pci设备
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  oal_pci_remove(oal_pci_dev_stru *pst_pci_dev)
{
    oal_uint32                    ul_dev_id;

    ul_dev_id = OAL_PCI_GET_DEV_ID(pst_pci_dev);

    if(OAL_PCI_WITP_DEVICE_ID == ul_dev_id)
    {
        oal_pci_witp_remove(pst_pci_dev);
    }
    else
    {
        OAL_IO_PRINT("oal_pci_remove: unknown device id (%d)!\n", ul_dev_id);
    }

    oal_pci_disable_device(pst_pci_dev);

    OAL_IO_PRINT("PCI driver: remove driver.\n");
}

/*****************************************************************************
 函 数 名  : oal_pci_init
 功能描述  : pci初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_pci_init(oal_void)
{
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    oal_uint8 uc_chip_id;
#endif

    OAL_IO_PRINT("PCI driver: driver init start.\n");

    if (oal_pci_register_driver(&g_st_pci_drv) < 0)
    {
        OAL_IO_PRINT("PCI driver: No devices found, driver not installed.\n");

        return OAL_FAIL;
    }

    /* WINDOWS下UT代码 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    for (uc_chip_id = 0; uc_chip_id < WLAN_CHIP_MAX_NUM_PER_BOARD; uc_chip_id++)
    {
        oal_bus_inc_chip_num();
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_pci_exit
 功能描述  : pci驱动退出
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_pci_exit(oal_void)
{
    oal_pci_unregister_driver(&g_st_pci_drv);

    OAL_IO_PRINT("PCI driver: driver unloaded.\n");
}

/*****************************************************************************
 函 数 名  : oal_5115_pci_init
 功能描述  : 5115 system control & PCIE0 基地址映射
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_5115_pci_init(oal_void)
{
    g_pst_5115_sys_ctl = oal_ioremap_nocache(OAL_PCIE_SYS_BASE_PHYS, 0x1000);
    if (OAL_PTR_NULL == g_pst_5115_sys_ctl)
    {
        OAL_IO_PRINT("oal_5115_pci_init, Cannot map system controller register base!\n");

        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_IO_PRINT("oal_5115_pci_init,OAL_PCIE_SYS_BASE_PHYS=0x%x,map g_pst_5115_sys_ctl = 0x%x\n",OAL_PCIE_SYS_BASE_PHYS,(oal_uint32)g_pst_5115_sys_ctl);

    g_pst_5610_mode = oal_ioremap_nocache(0x14900000, 0x200);
    if (OAL_PTR_NULL == g_pst_5610_mode)
    {
        OAL_IO_PRINT("oal_5115_pci_init, Cannot map 5610_mode register base!\n");

        return OAL_ERR_CODE_PTR_NULL;
    }

    g_pst_5610_gpio = oal_ioremap_nocache(0x10107000, 0x100);
    if (OAL_PTR_NULL == g_pst_5610_gpio)
    {
        OAL_IO_PRINT("oal_5115_pci_init, Cannot map 5610_mode register base!\n");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
    g_pst_5610_gpio1 = oal_ioremap_nocache(0x10106000, 0x100);
    if (OAL_PTR_NULL == g_pst_5610_gpio1)
    {
        OAL_IO_PRINT("oal_5115_pci_init, Cannot map g_pst_5610_gpio1 register base!\n");

        return OAL_ERR_CODE_PTR_NULL;
    }

    g_pst_5610_gpio2 = oal_ioremap_nocache(0x10108000, 0x100);
    if (OAL_PTR_NULL == g_pst_5610_gpio2)
    {
        OAL_IO_PRINT("oal_5115_pci_init, Cannot map g_pst_5610_gpio2 register base!\n");

        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oal_5115_pci_exit
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_5115_pci_exit(oal_void)
{
    if (g_pst_5115_sys_ctl)
    {
        oal_iounmap(g_pst_5115_sys_ctl);
    }

    if (g_pst_5610_mode)
    {
        oal_iounmap(g_pst_5610_mode);
    }

    if (g_pst_5610_gpio)
    {
        oal_iounmap(g_pst_5610_gpio);
    }

#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
    if (g_pst_5610_gpio1)
    {
        oal_iounmap(g_pst_5610_gpio1);
    }

    if (g_pst_5610_gpio2)
    {
        oal_iounmap(g_pst_5610_gpio2);
    }
#endif
}


/*****************************************************************************
 函 数 名  : oal_pci_ep_reconfig
 功能描述  : pci设备重新建联后EP端(1151)恢复配置寄存器和IATU表
 输入参数  : pst_pci_dev: pci设备
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_pci_ep_reconfig(oal_pci_dev_stru *pst_pci_dev)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    oal_uint32                    ul_value;
    oal_uint32                    ul_loop_count = 0;

    OAL_IO_PRINT("reconfig IATU tbl!...\n");
    while(ul_loop_count<1000)
    {
        ul_loop_count++;

        ul_value = oal_readl(g_pst_5115_sys_ctl + 0x18);
        if ( (ul_value & 0x20) && (ul_value & 0x8000 ))
        {
            OAL_IO_PRINT("PCIE0 Device Link Up val = 0x%08x.\n",ul_value);

            oal_pci_restore_state(pst_pci_dev);

            OAL_IO_PRINT("oal_pci_restore_state done\n");

            oal_pcie_set_inbound_iatu(pst_pci_dev);

            oal_pcie_set_outbound_iatu(pst_pci_dev);

            OAL_IO_PRINT("oal_pcie_set_outbound_iatu done\n");
            //oal_pci_enable_device(pst_pci_dev);

            return OAL_SUCC;
        }
        else
        {
            OAL_IO_PRINT("PCIE0 Device Link Down val = 0x%08x.\n",ul_value);
            oal_udelay(100);
        }
    }
#endif
    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : oal_pci_rc_reconfig
 功能描述  : pci设备重新建联后恢复RC端(5115)配置寄存器和IATU表
 输入参数  : pst_pci_dev: pci设备
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_pci_rc_reconfig(oal_uint8 uc_chip_id)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT) || (_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT))
    oal_uint8 uc_pcie_slot = uc_chip_id + 1;   /* pcie槽位号从1开始,chip id从0开始*/
    pcie_sys_reinit(uc_pcie_slot);
#elif(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT)
    /* WS835低功耗需要的pcie复位函数看是否后续需要，再添加 */
#else
    hi_pcie_reinit(uc_chip_id);     /* 5610sdk最新代码的pcie是按照chip开始，分为0,1,2；2表示无效 */
#endif

    //OAL_IO_PRINT("Should update kernel!\n");
#endif
    return OAL_TRUE;
}


/* 将pci_id_table导出到用户空间，使热插拔和模块装载系统知道什么模块针对什么硬件设备 */
/*lint -e19*/
/*lint -e578*//*lint -e19*/
OAL_MODULE_DEVICE_TABLE(pci, g_st_pci_id_table);
oal_module_symbol(g_pst_5115_sys_ctl);
oal_module_symbol(g_pst_5610_mode);
oal_module_symbol(g_pst_5610_gpio);
#if(_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)
oal_module_symbol(g_pst_5610_gpio1);
oal_module_symbol(g_pst_5610_gpio2);
#endif
oal_module_symbol(oal_pcie_set_inbound_iatu_slip_window);
oal_module_symbol(oal_pcie_set_inbound_iatu);
oal_module_symbol(oal_pcie_set_outbound_iatu);
oal_module_symbol(oal_pci_ep_reconfig);
oal_module_symbol(oal_pci_rc_reconfig);
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

