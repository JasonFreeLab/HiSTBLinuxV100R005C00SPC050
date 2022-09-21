/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

******************************************************************************
文 件 名   : main
版 本 号   : 初稿
作    者   : 
生成日期   : 2014年10月10日
最近修改   :
功能描述   : main.c 文件
函数列表   :
修改历史   :
1.日    期   : 2014年10月10日
 作    者   : 
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
#define HISI_LOG_TAG    "[WIFI_MAIN]"
#include "main.h"
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "sdt_drv.h"
#elif ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
#include "mac_resource.h"
#endif

#if (_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID)
#include "hmac_ext_if.h"
#include "wal_ext_if.h"
#include "dmac_ext_if.h"
#include "oal_kernel_file.h"

#ifdef _PRE_WLAN_FEATURE_WOW
#include "hmac_wow.h"
#endif

#elif (_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID)
/*TBD 以上头文件待回收*/
#include "oam_log.h"
#include "sdio_slave.h"
#include "channel_slave.h"
#include "oal_main.h"
#include "uart.h"
//#include "oam_msgsendrecv.h"
//#include "oam_data_send.h"
#include "uart.h"

#include "oal_hcc_slave_if.h"
#include "pm_extern.h"

#include "hal_ext_if.h"

#include "dmac_ext_if.h"
#include "dmac_alg.h"

#include "dmac_pm_sta.h"

#ifdef _PRE_WLAN_FEATURE_WOW
#include "dmac_wow.h"
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif


#elif(_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "dmac_alg.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "hmac_ext_if.h"
#include "wal_ext_if.h"
#endif

#if (_PRE_PRODUCT_ID_HI1131C_HOST == _PRE_PRODUCT_ID)
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_FEATURE_USB
#include "oal_usb_if.h"
#endif

#ifdef CONFIG_MMC
#include "oal_sdio_host_if.h"
#endif
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAIN_C

//#include "hmac_vap.h"
//#include "oal_hcc_host_if.h"


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
oal_void platform_module_exit(oal_uint16 us_bitmap);
OAL_STATIC oal_void builder_module_exit(oal_uint16 us_bitmap);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : host_mode_exit
 功能描述  : 选择性卸载不同模块
 输入参数  : oal_uint8 uc_bitmap:
            BIT0:oal
            BIT1:oam
            BIT2:sdt
            BIT3:frw
            BIT4:hal
            BIT5:dmac
            BIT6:alg
            BIT7:hmac
            BIT8:wal

 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
extern    oal_void oam_hisi_kill(void);

#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
OAL_STATIC oal_void builder_module_exit(oal_uint16 us_bitmap)
{
#if ((_PRE_PRODUCT_ID_HI1131C_DEV != _PRE_PRODUCT_ID) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
    #if (_PRE_PRODUCT_ID_HI1131C_DEV != _PRE_PRODUCT_ID)
        if (BIT8 & us_bitmap)
        {
            wal_main_exit();
        }
        if (BIT7 & us_bitmap)
        {
            hmac_main_exit();
        }

        oam_hisi_kill();
    #elif (_PRE_PRODUCT_ID_HI1131C_HOST != _PRE_PRODUCT_ID)

        #ifdef _PRE_WLAN_ALG_ENABLE
            if (BIT6 & us_bitmap)
            {
                alg_main_exit();
            }
        #endif

        if (BIT5 & us_bitmap)
        {
            dmac_main_exit();
        }
        if (BIT4 & us_bitmap)
        {
            hal_main_exit();
        }

        platform_module_exit(us_bitmap);
    #endif

#endif

    return;
}
#endif

#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)&&(_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID))
/*****************************************************************************
 函 数 名  : host_test_get_chip_msg
 功能描述  : 用于1102 host侧ut测试，hmac获得板级信息
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 host_test_get_chip_msg(oal_void)
{
    oal_uint32             ul_return;
    mac_chip_stru         *pst_chip;
    frw_event_mem_stru    *pst_event_mem;
    frw_event_stru        *pst_event;             /* 事件结构体 */
    oal_uint32             ul_dev_id;
    oal_netbuf_stru       *pst_netbuf;
    dmac_tx_event_stru    *pst_ctx_event;
    oal_uint8             *pst_mac_rates_11g;
    /** 待补充 ***/


    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAL_IO_PRINT("host_test_get_chip_msg: hmac_init_event_process FRW_EVENT_ALLOC result = OAL_PTR_NULL.\n");
        return OAL_FAIL;
    }

    /* 申请netbuf内存 */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        OAL_IO_PRINT("host_test_get_chip_msg: hmac_init_event_process OAL_MEM_NETBUF_ALLOC result = OAL_PTR_NULL.\n");
        return OAL_FAIL;
    }

    pst_event                 = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event             = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_ctx_event->pst_netbuf = pst_netbuf;
    pst_mac_rates_11g = (oal_uint8*)oal_netbuf_data(pst_ctx_event->pst_netbuf);
    pst_chip = (mac_chip_stru *)(pst_mac_rates_11g + sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM);

    ul_dev_id = (oal_uint32) oal_queue_dequeue(&(g_st_mac_res.st_dev_res.st_queue));
    /* 0为无效值 */
    if (0 == ul_dev_id)
    {
        OAL_IO_PRINT("host_test_get_chip_msg:oal_queue_dequeue return 0!");
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }
    pst_chip->auc_device_id[0] = (oal_uint8)(ul_dev_id - 1);

    /* 根据ul_chip_ver，通过hal_chip_init_by_version函数获得 */
    pst_chip->uc_device_nums = 1;
    pst_chip->uc_chip_id = 0;
    pst_chip->en_chip_state = OAL_TRUE;

    /* 由hal_chip_get_version函数得到,1102 02需要SOC提供寄存器后实现 */
    pst_chip->ul_chip_ver = WLAN_CHIP_VERSION_HI1151V100H;

    pst_chip->pst_chip_stru = OAL_PTR_NULL;


    ul_return = hmac_init_event_process(pst_event_mem);
    if(OAL_UNLIKELY(ul_return != OAL_SUCC))
    {
        OAL_IO_PRINT("host_test_get_chip_msg: hmac_init_event_process  ul_return != OAL_SUCC\n");
        FRW_EVENT_FREE(pst_event_mem);
        oal_netbuf_free(pst_netbuf);
        return OAL_FAIL;
    }

    return OAL_SUCC;

}
#endif
//#elif (((_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)&&(_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID)))
#if  (defined(HI1102_EDA))
/*****************************************************************************
 函 数 名  : device_test_create_cfg_vap
 功能描述  : device侧eda用例打桩使用
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 device_test_create_cfg_vap(oal_void)
{
    oal_uint32          ul_return;
    frw_event_mem_stru *pst_event_mem;
    frw_event_stru     *pst_event;

    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAL_IO_PRINT("device_test_create_cfg_vap: hmac_init_event_process FRW_EVENT_ALLOC result = OAL_PTR_NULL.\n");
        return OAL_FAIL;
    }

    ul_return = dmac_init_event_process(pst_event_mem);
    if (OAL_SUCC != ul_return)
    {
        OAL_IO_PRINT("device_test_create_cfg_vap: dmac_init_event_process result = fale.\n");
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event->st_event_hdr.uc_device_id = 0;

    ul_return = dmac_cfg_vap_init_event(pst_event_mem);
    if (OAL_SUCC != ul_return)
    {
        FRW_EVENT_FREE(pst_event_mem);
        return ul_return;
    }

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
#endif

#if ((_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID)||(_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID))

#ifdef _PRE_1131C_DEV_FUNCTION_NOT_USED
/*****************************************************************************
 函 数 名  : platform_module_exit
 功能描述  : 平台模块卸载总入口(仅供51和02 Device侧用)
 输入参数  : oal_uint8 uc_bitmap:
            默认:
            BIT0:oal
            BIT1:oam
            BIT2:sdt
            BIT3:frw
            BIT4:hal
            BIT5:dmac
            BIT6:alg
            BIT7:hmac
            BIT8:wal
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void platform_module_exit(oal_uint16 us_bitmap)
{
    if (BIT3 & us_bitmap)
    {
        frw_main_exit();
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        /* 02目前不需要SDT初始化 TBD */
        if (BIT2 & us_bitmap)
        {
            sdt_drv_main_exit();
        }
    #endif
#endif
    if (BIT1 & us_bitmap)
    {
        oam_main_exit();
    }
    if (BIT0 & us_bitmap)
    {
        oal_main_exit();
    }
    return;
}
#endif //#ifdef _PRE_1131C_DEV_FUNCTION_NOT_USED


/*****************************************************************************
 函 数 名  : platform_module_init
 功能描述  :(仅供51和02 Device侧用)
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :
 备注:    依赖builder_module_exit()

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 platform_module_init(oal_void)
{
    oal_int32  l_return   = OAL_FAIL;
    oal_uint16  us_bitmap  = 0;

    //WLAN_EDA_TRACE_TAG(0x4110UL);
    l_return = oal_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("platform_module_init: oal_main_init return error code: %d\r\n", l_return);
        return l_return;
    }
#if (!defined(_PRE_EDA))
    l_return = oam_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("platform_module_init: oam_main_init return error code: %d\r\n", l_return);
        us_bitmap = BIT0;
        builder_module_exit(us_bitmap);
        return l_return;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)||(_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* 02目前不需要SDT初始化 TBD */
        l_return = sdt_drv_main_init();
        if (OAL_SUCC != l_return)
        {
            OAL_IO_PRINT("platform_module_init: sdt_drv_main_init return error code: %d\r\n", l_return);
            us_bitmap = BIT0|BIT1;
            builder_module_exit(us_bitmap);
            return l_return;
        }
    #endif
#endif
#endif
    //WLAN_EDA_TRACE_TAG(0x4120UL);
    l_return = frw_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("platform_module_init: frw_main_init return error code: %d\r\n", l_return);
        us_bitmap = BIT0 | BIT1 | BIT2;
        builder_module_exit(us_bitmap);
        return l_return;
    }

    /*启动完成后，输出打印*/
    OAL_IO_PRINT("platform_module_init:: platform_main_init finish!\r\n");

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : device_main_init
 功能描述  : 固件侧裸系统下模块初始化总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32  device_module_init(oal_void)
{
    oal_int32  l_return  = OAL_FAIL;
    oal_uint16 us_bitmap = 0;

    //WLAN_EDA_TRACE_TAG(0x4210UL);
    l_return = hal_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("device_module_init: hal_main_init return error code: %d", l_return);
        return l_return;
    }

    //WLAN_EDA_TRACE_TAG(0x4220UL);
    l_return = dmac_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("device_module_init: dmac_main_init return error code: %d", l_return);
        us_bitmap = BIT4;
        builder_module_exit(us_bitmap);
        return l_return;
    }
#if (!defined(_PRE_EDA))
#if defined(_PRE_WLAN_ALG_ENABLE) || defined(_PRE_WLAN_CHIP_TEST_ALG)
    l_return = alg_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("device_module_init: alg_main_init return error code : %d", l_return);
        us_bitmap = BIT4 | BIT5;
        builder_module_exit(us_bitmap);
        return l_return;
    }
#endif
#endif

#if 0
#if (((_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)&&(_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID)) || (defined(_PRE_EDA)))
    /* ut工程打桩用:从host下发创建cfg_vap命令 */
    l_return = (oal_int32) device_test_create_cfg_vap();
    if (OAL_SUCC != l_return)
    {
        return l_return;
    }
#endif
#endif
    //WLAN_EDA_TRACE_TAG(0x4240UL);
    /*启动完成后，输出打印*/
    OAL_IO_PRINT("device_module_init:: device_module_init finish!\r\n");

    return OAL_SUCC;
}
#endif
#if ((_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID)||(_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID))
#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
 函 数 名  : hwifi_config_host_global_dts_param
 功能描述  :
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
extern oal_uint32 band_5g_enabled;
oal_uint32 hwifi_config_host_global_dts_param(oal_void)
{
    /**************************** 获取5g开关 ******************************/
    band_5g_enabled = !!hwifi_get_init_value(CUS_TAG_DTS, WLAN_CFG_DTS_BAND_5G_ENABLE);

#ifndef _PRE_WLAN_FEATURE_5G
    band_5g_enabled = OAL_FALSE;
#endif /* _PRE_WLAN_FEATURE_5G */

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
#endif /* #if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION) */

extern      oal_int32 wlan_pm_open(oal_void);
extern oal_uint32 wlan_pm_close(oal_void);
extern int isAsic(void);

/*****************************************************************************
 函 数 名  : host_main_init
 功能描述  :
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  host_module_init(oal_void)
{
    oal_int32  l_return = OAL_FAIL;
    oal_uint16 us_bitmap = 0;

#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    hwifi_config_init(CUS_TAG_DTS);
    hwifi_config_host_global_dts_param();
    hwifi_config_init(CUS_TAG_NV);
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
#endif

    l_return = hmac_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("host_module_init: hmac_main_init return error code: %d", l_return);
        return l_return;
    }
#if 0
#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)&&(_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID))
    /* ut工程打桩用:从device获取板级信息 */
    l_return = (oal_int32) host_test_get_chip_msg();
    if (OAL_SUCC != l_return)
    {
        us_bitmap = BIT7;
        builder_module_exit(us_bitmap);
        return l_return;
    }
#endif
#endif
    l_return = wal_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("host_module_init: wal_main_init return error code: %d", l_return);
        us_bitmap = BIT7;
#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
        builder_module_exit(us_bitmap);
#endif
        return l_return;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
    g_uc_custom_cali_done = OAL_FALSE;

    /* 为解决:asic不需要此上下电，fpga mpw0上电与此有关，去掉后默认wifi关的情况下会扫描不到*/
       if (!isAsic())
       {
           wlan_pm_open();
           mdelay(7);
           wlan_pm_close();
       }
    /* end */
#endif

#ifdef _PRE_WLAN_FEATURE_WOW
    hmac_wow_init();
#endif

    /*启动完成后，输出打印*/
    OAL_IO_PRINT("host_module_init:: host_main_init finish!");

    return OAL_SUCC;
}
#endif

#if (_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID)
/*****************************************************************************
 函 数 名  : 1102_device_main_init
 功能描述  : Hi1102项目device侧初始化总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  hi1102_device_main_init(oal_void)
{
    oal_int32  l_return  = OAL_FAIL;
    oal_uint16  us_bitmap;
    frw_event_mem_stru *pst_event_mem;

    //WLAN_EDA_TRACE_TAG(0x4100UL);
    l_return = platform_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("host_bottom_main_init: platform_module_init return error code: %d\r\n", l_return);
        return l_return;
    }

    //WLAN_EDA_TRACE_TAG(0x4200UL);
    l_return = device_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("host_bottom_main_init: device_module_init return error code: %d\r\n", l_return);
        us_bitmap = BIT0 | BIT1 | BIT2 | BIT3;
        builder_module_exit(us_bitmap);
        return l_return;
    }
#ifndef WIN32
    /* 1102 需要在device初始化成功后同步速率级 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAL_IO_PRINT("hi1102_device_main_init: dmac_init_event_process FRW_EVENT_ALLOC result = OAL_PTR_NULL.\n");
        return OAL_FAIL;
    }

    l_return = dmac_init_event_process(pst_event_mem);
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("hi1102_device_main_init: dmac_init_event_process result = fale.\n");
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    FRW_EVENT_FREE(pst_event_mem);
#endif
    #if (!defined(_PRE_EDA))
    /*device_ready:调用HCC接口通知Hmac,Dmac已经完成初始化 TBD*/
    //hcc_send_msg2host(D2H_MSG_WLAN_READY);
    chanslv_sendmsg_sync(D2H_MSG_WLAN_READY);   //wwx327330,2016.02.18修改
    #endif
    /*启动完成后，输出打印*/
    OAL_IO_PRINT("Hi1102_device_main_init:: Hi1102_device_main_init finish!\r\n");

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : device_main_init
 功能描述  : 固件侧 系统总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
typedef oal_uint8 (*dmac_psm_save_ps_state_type)(oal_void);
dmac_psm_save_ps_state_type g_fn_dmac_psm_save_ps_state_type_ram = dmac_psm_save_ps_state;
typedef oal_uint8 (*dmac_psm_recover_no_powerdown_type)(oal_void);
dmac_psm_recover_no_powerdown_type g_fn_dmac_psm_recover_no_powerdown_type_ram = dmac_psm_recover_no_powerdown;
typedef oal_void (*dmac_psm_recover_start_dma_type)(oal_uint8*, oal_uint8*, oal_uint8*);
dmac_psm_recover_start_dma_type g_fn_dmac_psm_recover_start_dma_type_ram = dmac_psm_recover_start_dma;
typedef oal_uint8 (*dmac_psm_recover_powerdown_type)(oal_uint8, oal_uint8, oal_uint8);
dmac_psm_recover_powerdown_type g_fn_dmac_psm_recover_powerdown_type_ram = dmac_psm_recover_powerdown;
typedef oal_uint8 (*dmac_psm_cbb_stopwork_type)(oal_void);
dmac_psm_cbb_stopwork_type g_fn_dmac_psm_cbb_stopwork_type_ram = dmac_psm_cbb_stopwork;
typedef oal_void (*dmac_psm_save_register_type)(oal_void);
dmac_psm_save_register_type g_fn_dmac_psm_save_register_type_ram = dmac_psm_save_register;
typedef oal_void (*dmac_psm_restore_register_type)(oal_void);
dmac_psm_restore_register_type g_fn_dmac_psm_restore_register_type_ram = dmac_psm_restore_register;
typedef oal_void (*pm_wlan_deepsleep_save_state_type)(oal_void);
pm_wlan_deepsleep_save_state_type g_fn_pm_wlan_deepsleep_save_state_type_ram = pm_wlan_deepsleep_save_state;
typedef oal_void (*pm_wlan_deepsleep_load_state_type)(oal_void);
pm_wlan_deepsleep_load_state_type g_fn_pm_wlan_deepsleep_load_state_type_ram = pm_wlan_deepsleep_load_state;

oal_void device_main_init(oal_void)
{
    /* init */
    extern volatile oal_uint32     g_ulGpioIntCount;

    oal_int32 l_return = OAL_FAIL;
    l_return = hi1102_device_main_init();
    PRINT("device_main_init exit..."NEWLINE);
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("device_main_function: Hi1102_device_main_init return error code: %d", l_return);
        /* 初始化失败不退出主程序，等待重启 */
        for (;;)
        ;
    }
    OAL_IO_PRINT("device_main_function: hi1102_device_main_init succ!!\r\n");
#if 1
#if (SUB_SYSTEM == SUB_SYS_WIFI)
    if(g_pf_PM_WLAN_IsrRegister != NULL)
    {
        g_pf_PM_WLAN_IsrRegister();
    }
    else
    {
        OAM_ERROR_LOG0(0, 0, "g_pf_PM_WLAN_IsrRegister Empty");
        return;
    }
    if(g_pf_PM_WLAN_FuncRegister != NULL)
    {
        g_pf_PM_WLAN_FuncRegister(
                                    device_psm_main_function,     /* 1 */
                                    dmac_psm_check_hw_txq_state,  /* 2 */
                                    dmac_psm_check_txrx_state,    /* 3 */
                                    dmac_psm_clean_state,         /* 4 */
                                    dmac_psm_save_start_dma,      /* 5 */
                                    g_fn_dmac_psm_save_ps_state_type_ram,       /* 6 */
                                    g_fn_dmac_psm_recover_no_powerdown_type_ram,/* 7 */
                                    g_fn_dmac_psm_recover_start_dma_type_ram,   /* 8 */
                                    g_fn_dmac_psm_recover_powerdown_type_ram,   /* 9 */
                                    g_fn_dmac_psm_cbb_stopwork_type_ram,        /* 10 */
                                    dmac_psm_rf_awake,            /* 11 */
                                    dmac_psm_rf_sleep,            /* 12 */
                                    dmac_psm_is_fake_queues_empty,/* 13 */
                                    g_fn_dmac_psm_save_register_type_ram,       /* 14 */
                                    g_fn_dmac_psm_restore_register_type_ram,    /* 15 */
                                    dmac_wow_host_sleep_callback,    /*16*/
                                    g_fn_pm_wlan_deepsleep_save_state_type_ram, /* 17 */
                                    g_fn_pm_wlan_deepsleep_load_state_type_ram  /* 18 */
                                 );
    }
    else
    {
        OAM_ERROR_LOG0(0, 0, "g_pf_PM_WLAN_FuncRegister Empty");
        return;
    }

#endif
#endif
    g_ulGpioIntCount = 0;
}





/*****************************************************************************
 函 数 名  : device_psm_main_function
 功能描述  : 睡眠唤醒接口,(遗留给平台的接口)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
typedef oal_void (*device_main_function_type)(oal_void);
device_main_function_type g_fn_device_main_function_type_ram = device_main_function;

oal_uint8 device_psm_main_function(oal_void)
{
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    mac_device_stru         *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
#endif
    g_fn_device_main_function_type_ram();

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_mac_device = mac_res_get_dev(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{device_psm_main_function::pst_device[id:0] is NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    hal_btcoex_process_bt_status(pst_hal_device);
#endif

    return OAL_SUCC;
}

#elif (_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID)
#include "hmac_vap.h"
#include "oal_hcc_host_if.h"

/*****************************************************************************
 函 数 名  : 1102_host_main_init
 功能描述  : Hi1102项目host侧初始化总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  hi1102_host_main_init(oal_void)
{
    //oal_uint32 ul_return = OAL_FAIL;
    oal_int32  l_return = OAL_FAIL;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    hcc_flowctl_get_device_mode_register(hmac_flowctl_check_device_is_sta_mode);
    hcc_flowctl_operate_subq_register(hmac_vap_net_start_subqueue, hmac_vap_net_stop_subqueue);
#else
    hcc_tx_flow_ctrl_cb_register(hmac_vap_net_stopall, hmac_vap_net_startall);
#endif

    l_return = host_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("Hi1102_host_main_init: host_module_init return error code: %d", l_return);
        return l_return;
    }

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    wal_hipriv_register_inetaddr_notifier();
    wal_hipriv_register_inet6addr_notifier();
#endif

    /*启动完成后，输出打印*/
    OAL_IO_PRINT("Hi1102_host_main_init:: Hi1102_host_main_init finish!\n");

    return OAL_SUCC;

}
/*****************************************************************************
 函 数 名  : Hi1102_host_main_exit
 功能描述  : Hi1102项目host侧卸载总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hi1102_host_main_exit(oal_void)
{
    oal_uint16 us_bitmap = 0;

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    wal_hipriv_unregister_inetaddr_notifier();
    wal_hipriv_unregister_inet6addr_notifier();
#endif

    us_bitmap =  BIT6 | BIT7 | BIT8;
#if (_PRE_OS_VERSION_LITEOS != _PRE_OS_VERSION)
    builder_module_exit(us_bitmap);
#endif

    return ;
}
#elif (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)

/*****************************************************************************
 函 数 名  : Hi1105_main_init
 功能描述  : Hi1151项目初始化总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 hi1151_main_init(oal_void)
{
    oal_int32  l_return   = OAL_FAIL;
    oal_uint16  us_bitmap  = 0;

    l_return = platform_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("Hi1151_main_init: platform_module_init return error code: %d/r/n", l_return);
        return l_return;
    }

    l_return = device_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("Hi1151_main_init: device_module_init return error code: %d/r/n", l_return);
        us_bitmap = BIT0 | BIT1 | BIT2 | BIT3;
        builder_module_exit(us_bitmap);
        return l_return;
    }

    l_return = host_module_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("Hi1151_main_init: host_module_init return error code: %d/r/n", l_return);
        us_bitmap = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6;
        builder_module_exit(us_bitmap);
        return l_return;
    }
    /*启动完成后，输出打印*/
    OAL_IO_PRINT("Hi1151_main_init:: Hi1151_main_init finish!/r/n");

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : Hi1151_main_exit
 功能描述  : Hi1151项目卸载总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hi1151_main_exit(oal_void)
{
    oal_uint16 us_bitmap = 0;

    us_bitmap = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 | BIT8;
    builder_module_exit(us_bitmap);

    return ;
}
#endif




/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1131C_HOST == _PRE_PRODUCT_ID)
#ifndef CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
oal_int32 g_wifi_init_flag = 0;
oal_int32 g_wifi_init_ret;
/*built-in*/
OAL_STATIC ssize_t  wifi_sysfs_set_init(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    char            mode[128] = {0};
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    if ((sscanf(buf, "%20s", mode) != 1))
    {
        OAL_IO_PRINT("set value one param!\n");
        return -OAL_EINVAL;
    }

    if(sysfs_streq("init", mode))
    {
        /*init*/
        if(0 == g_wifi_init_flag)
        {
            g_wifi_init_ret = hi1102_host_main_init();
            g_wifi_init_flag = 1;
        }
        else
        {
            OAL_IO_PRINT("double init!\n");
        }
    }
    else
    {
        OAL_IO_PRINT("invalid input:%s\n",mode);
    }

    return count;
}

OAL_STATIC ssize_t  wifi_sysfs_get_init(struct device *dev, struct device_attribute *attr, char*buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    if(1 == g_wifi_init_flag)
    {
        if(OAL_SUCC == g_wifi_init_ret)
        {
            ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "running\n");
        }
        else
        {
            ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "boot failed ret=%d\n", g_wifi_init_ret);
        }
    }
    else
    {
        ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "uninit\n");
    }

    return ret;
}
OAL_STATIC DEVICE_ATTR(wifi, S_IRUGO | S_IWUSR, wifi_sysfs_get_init, wifi_sysfs_set_init);
OAL_STATIC struct attribute *wifi_init_sysfs_entries[] = {
        &dev_attr_wifi.attr,
        NULL
};

OAL_STATIC struct attribute_group wifi_init_attribute_group = {
        .attrs = wifi_init_sysfs_entries,
};

oal_int32  wifi_sysfs_init(oal_void)
{
    oal_int32 ret = 0;
    oal_kobject*     pst_root_boot_object = NULL;
    pst_root_boot_object = oal_get_sysfs_root_boot_object();
    if(NULL == pst_root_boot_object)
    {
        OAL_IO_PRINT("[E]get root boot sysfs object failed!\n");
        return -OAL_EBUSY;
    }

    ret = sysfs_create_group(pst_root_boot_object,&wifi_init_attribute_group);
    if (ret)
    {
        OAL_IO_PRINT("sysfs create plat boot group fail.ret=%d\n",ret);
        ret = -OAL_ENOMEM;
        return ret;
    }

    return ret;
}

oal_void  wifi_sysfs_exit(oal_void)
{
    /*need't exit,built-in*/
    return;
}
oal_module_init(wifi_sysfs_init);
oal_module_exit(wifi_sysfs_exit);
#endif
#else
oal_module_init(hi1102_host_main_init);
oal_module_exit(hi1102_host_main_exit);
#endif
#elif  (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(hi1151_main_init);
oal_module_exit(hi1151_main_exit);
#endif
oal_module_license("GPL");
/*lint +e578*//*lint +e19*/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

