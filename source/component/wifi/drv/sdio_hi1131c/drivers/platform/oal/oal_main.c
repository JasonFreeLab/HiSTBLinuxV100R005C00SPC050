/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_main.c
  版 本 号   : 初稿
  作    者   : 康国昌
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : OAL模块初始化
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_main.h"
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#include "oal_pci_if.h"
#endif
#include "oal_mem.h"
#include "oal_schedule.h"
#include "oal_net.h"

#include "oal_hcc_host_if.h"
#include "oal_kernel_file.h"

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
#ifndef WIN32
#include "plat_firmware.h"
#endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
void __iomem *g_l2cache_base;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oal_main_init
 功能描述  : OAL模块初始化总入口，包含OAL模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  ATTR_OAL_NO_FUNC_TRACE oal_main_init(oal_void)
{
    oal_uint32  ul_rslt;
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    if(NULL == oal_conn_sysfs_root_obj_init())
    {
        OAL_IO_PRINT("hisi root sysfs init failed\n");
    }
#endif

    /* 为了解各模块的启动时间，增加时间戳打印 */

    /* 内存池初始化 */
    ul_rslt = oal_mem_init_pool();
    if (ul_rslt != OAL_SUCC)
    {
        OAL_IO_PRINT("oal_main_init: oal_mem_init_pool return error code: %d", ul_rslt);
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

#if (_PRE_PRODUCT_ID_HI1151 == _PRE_PRODUCT_ID)
    /* pci驱动注册 */
    ul_rslt = oal_pci_init();
    if (OAL_SUCC != ul_rslt)
    {
        /* 内存池卸载 */
        oal_mem_exit();
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

    ul_rslt = oal_5115_pci_init();
    if (OAL_SUCC != ul_rslt)
    {
        OAL_IO_PRINT("oal_main_init: oal_5115_pci_init return error code: %d", ul_rslt);
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }
#elif ((_PRE_PRODUCT_ID_HI1131C_HOST == _PRE_PRODUCT_ID)||(_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID))
    /* Hi1102 SDIO总线初始化接口 TBD */

    /* 初始化: 总线上的chip数量增加1 */
    oal_bus_init_chip_num();
    ul_rslt = oal_bus_inc_chip_num();
    if(OAL_SUCC != ul_rslt)
    {
         OAL_IO_PRINT("oal_pci_probe: oal_bus_inc_chip_num failed!\n");
         OAL_BUG_ON(1);
         return -OAL_EIO;
    }
#endif

    /* 启动成功 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    OAL_MEMZERO(g_past_net_device, WLAN_VAP_SUPPORT_MAX_NUM_LIMIT * OAL_SIZEOF(oal_net_device_stru *));
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    /* HCC初始化 */
    if (OAL_UNLIKELY(NULL ==hcc_module_init()))
    {
        OAL_IO_PRINT("[ERROR]hcc_module_init return err null\n");
        return -OAL_EFAIL;
    }
#endif

#ifdef _PRE_CONFIG_HISI_CONN_SOFTWDFT
    if(OAL_UNLIKELY(OAL_SUCC != oal_softwdt_init()))
    {
        OAL_IO_PRINT("oal_softwdt_init init failed!\n");
        return -OAL_EFAIL;
    }
#endif

#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
    if(OAL_UNLIKELY(OAL_SUCC != oal_dft_init()))
    {
        OAL_IO_PRINT("oal_dft_init init failed!\n");
        return -OAL_EFAIL;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_main_exit
 功能描述  : OAL模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块卸载返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  ATTR_OAL_NO_FUNC_TRACE oal_main_exit(oal_void)
{
#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
    oal_dft_exit();
#endif

#ifdef _PRE_CONFIG_HISI_CONN_SOFTWDFT
    oal_softwdt_exit();
#endif

    hcc_module_exit(hcc_get_default_handler());

#if (_PRE_PRODUCT_ID_HI1151 == _PRE_PRODUCT_ID)

    /* pci驱动卸载 */
    oal_pci_exit();

    oal_5115_pci_exit();

#elif ((_PRE_PRODUCT_ID_HI1131C_HOST == _PRE_PRODUCT_ID)||(_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID))
    /* Hi1102 SDIO总线exit接口(不下电) TBD */

    /* chip num初始化:0 */
    oal_bus_init_chip_num();
#endif

    /* 内存池卸载 */
    oal_mem_exit();
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    oal_conn_sysfs_root_boot_obj_exit();
    oal_conn_sysfs_root_obj_exit();
#endif

    return ;
}

#if 0
/*****************************************************************************
 函 数 名  : __cyg_profile_func_enter
 功能描述  : 进入替换函数原型
 输入参数  : 固定为函数地址和call site
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void ATTR_OAL_NO_FUNC_TRACE __cyg_profile_func_enter(void *this_func, void *call_site)
{

}

/*****************************************************************************
 函 数 名  : __cyg_profile_func_exit
 功能描述  : 退出替换函数原型
 输入参数  : 固定为函数地址和call site
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void ATTR_OAL_NO_FUNC_TRACE __cyg_profile_func_exit(void *this_func, void *call_site)
{

}
#endif
/*****************************************************************************
 函 数 名  : oal_chip_get_version
 功能描述  : 获取chip version,由平台提供总的version入口,device和host再分别调用
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_chip_get_version(oal_void)
{
    oal_uint32 ul_chip_ver = 0;

#if (_PRE_WLAN_REAL_CHIP == _PRE_WLAN_CHIP_SIM)

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    ul_chip_ver   = WLAN_CHIP_VERSION_HI1151V100H;
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    /* 1102 02需要SOC提供寄存器后实现 */
    ul_chip_ver   = WLAN_CHIP_VERSION_HI1151V100H;
#endif

#else /* else _PRE_WLAN_REAL_CHIP != _PRE_WLAN_CHIP_SIM*/

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    ul_chip_ver   = WLAN_CHIP_VERSION_HI1151V100H;
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
    /* 1102 02需要SOC提供寄存器后实现 */
    ul_chip_ver   = WLAN_CHIP_VERSION_HI1151V100H;
#endif

#endif
    return ul_chip_ver;

}
/*****************************************************************************
 函 数 名  : oal_chip_get_version
 功能描述  : 根据chip version获取device num
 输入参数  : chip version
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 oal_chip_get_device_num(oal_uint32   ul_chip_ver)
{
    oal_uint8   uc_device_nums = 0;

    switch  (ul_chip_ver)
    {
        case WLAN_CHIP_VERSION_HI1151V100H:
        case WLAN_CHIP_VERSION_HI1151V100L:
            uc_device_nums = WLAN_CHIP_DBSC_DEVICE_NUM;
        break;

        default:
            uc_device_nums = 0;
        break;
    }

    return uc_device_nums;
}

/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151 ==_PRE_PRODUCT_ID)
oal_module_init(oal_main_init);
oal_module_exit(oal_main_exit);

#endif
oal_module_symbol(oal_chip_get_version);
oal_module_symbol(oal_chip_get_device_num);
oal_module_symbol(oal_main_init);
oal_module_symbol(oal_main_exit);
oal_module_symbol(g_l2cache_base);
//oal_module_symbol(__cyg_profile_func_enter);
//oal_module_symbol(__cyg_profile_func_exit);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

