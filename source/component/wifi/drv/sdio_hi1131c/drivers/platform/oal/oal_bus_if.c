/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_bus_if.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月31日
  最近修改   :
  功能描述   : 总线接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月31日
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
#include "oal_bus_if.h"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 实际chip数量 */
OAL_STATIC oal_uint8         g_uc_bus_chip_num = 0;
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT))||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151))
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
OAL_STATIC oal_bus_chip_stru g_st_bus_chip[WLAN_CHIP_MAX_NUM_PER_BOARD] = {{0},{0}};
#else
OAL_STATIC oal_bus_chip_stru g_st_bus_chip[WLAN_CHIP_MAX_NUM_PER_BOARD] = {{0}};
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
OAL_STATIC oal_int8         *g_pac_irq_pc_name[4] = {"wlan1", "wlan2", "wlan3", "wlan4"};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : oal_bus_find_dev_instance
 功能描述  : 获取总线设备接口
 输入参数  : oal_bus_dev_stru **ppst_bus_dev, oal_uint8 uc_index
 输出参数  : ppst_bus_dev: 总线设备
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_bus_find_dev_instance(oal_bus_dev_stru **ppst_bus_dev, oal_void *p_dev)
{
    oal_uint8  uc_chip_index;
    oal_uint8  uc_device_index;

    for(uc_chip_index = 0; uc_chip_index < g_uc_bus_chip_num; uc_chip_index++)
    {
        for(uc_device_index = 0; uc_device_index < g_st_bus_chip[uc_chip_index].uc_device_num; uc_device_index++)
        {
            /* 两个地址相等 */
            if(g_st_bus_chip[uc_chip_index].st_bus_dev[uc_device_index].p_dev == p_dev)
            {
                *ppst_bus_dev = &g_st_bus_chip[uc_chip_index].st_bus_dev[uc_device_index];
                return;
            }
        }
    }

    *ppst_bus_dev = OAL_PTR_NULL;
}
/*****************************************************************************
 函 数 名  : oal_bus_get_dev_instance
 功能描述  : 获取bus dev
 输入参数  : uc_chip_id     : CHIP ID
             uc_device_id   : DEVICE ID
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bus_dev_stru * oal_bus_get_dev_instance(oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_chip_stru          *pst_bus_chip;

    if(uc_chip_id >= WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        OAL_IO_PRINT("oal_bus_register_irq: uc_chip_id = %d\n", uc_chip_id);
        return OAL_PTR_NULL;
    }

    pst_bus_chip = &g_st_bus_chip[uc_chip_id];

    if(uc_device_id >= pst_bus_chip->uc_device_num)
    {
        OAL_IO_PRINT("oal_bus_register_irq: uc_device_id = %d\n", uc_device_id);
        return OAL_PTR_NULL;
    }

    return &pst_bus_chip->st_bus_dev[uc_device_id];
}
/*****************************************************************************
 函 数 名  : oal_bus_unregister_irq
 功能描述  : 注销中断
 输入参数  :
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_bus_unregister_irq(oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_dev_stru           *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);
    if(OAL_PTR_NULL == pst_bus_dev)
    {
        return;
    }

    oal_irq_free(&pst_bus_dev->st_irq_info);
}
/*****************************************************************************
 函 数 名  : oal_bus_register_irq
 功能描述  : 注册中断
 输入参数  : pst      : 设备结构体
             p_func   : 回调函数指针
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_bus_register_irq(oal_void *pst, oal_irq_intr_func p_func, oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_dev_stru           *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);
    if(OAL_PTR_NULL == pst_bus_dev)
    {
        return OAL_FAIL;
    }

    OAL_IRQ_INIT_MAC_DEV(pst_bus_dev->st_irq_info,
                         pst_bus_dev->ul_irq_num,
                         OAL_SA_SHIRQ,
                         g_pac_irq_pc_name[uc_chip_id * WLAN_DEVICE_MAX_NUM_PER_CHIP + uc_device_id],
                         pst,
                         p_func);

    if (oal_irq_setup(&pst_bus_dev->st_irq_info))
    {
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : oal_bus_get_instance
 功能描述  : 获取总线设备接口
 输入参数  : oal_bus_dev_stru **ppst_bus_dev, oal_uint8 uc_index
 输出参数  : ppst_bus_dev: 总线设备
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  oal_bus_get_chip_instance(oal_bus_chip_stru **ppst_bus_chip, oal_uint8 uc_index)
{
    if(uc_index < WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        *ppst_bus_chip = &g_st_bus_chip[uc_index];
    }
    else
    {
        *ppst_bus_chip = OAL_PTR_NULL;
        OAL_IO_PRINT("oal_bus_get_chip_instance: uc_index = %d\n", uc_index);
    }
}


#endif

/*****************************************************************************
 函 数 名  : oal_bus_get_chip_num
 功能描述  : 获取硬件总线接口个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : chip 个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  oal_bus_get_chip_num(oal_void)
{
    return g_uc_bus_chip_num;
}

/*****************************************************************************
 函 数 名  : oal_bus_inc_chip_num
 功能描述  : 获取硬件总线接口个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : chip 个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oal_bus_inc_chip_num(oal_void)
{
    if(g_uc_bus_chip_num < WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        g_uc_bus_chip_num++;
    }
    else
    {
        OAL_IO_PRINT("oal_bus_inc_chip_num FAIL: g_uc_bus_chip_num = %d\n", g_uc_bus_chip_num);
        return OAL_FAIL;
    }

    /* WINDOWS下UT代码 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    g_st_bus_chip[0].uc_device_num = g_uc_bus_chip_num;
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : oal_bus_init_chip_num
 功能描述  : 初始化chip num
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_bus_init_chip_num(oal_void)
{
    g_uc_bus_chip_num = 0;

    /* WINDOWS下UT代码 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    g_st_bus_chip[0].uc_device_num = g_uc_bus_chip_num;
#endif
    return;
}


#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
/*****************************************************************************
 函 数 名  : oal_irq_affinity_init
 功能描述  : 中断和核绑定初始化
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void oal_bus_irq_affinity_init(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_core_id)
{
	oal_bus_dev_stru *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);

    oal_irq_set_affinity(pst_bus_dev->st_irq_info.ul_irq, ul_core_id);
}
#endif

/*lint -e19*/
oal_module_symbol(oal_bus_get_chip_num);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
oal_module_symbol(oal_bus_get_chip_instance);
oal_module_symbol(oal_bus_register_irq);
oal_module_symbol(oal_bus_unregister_irq);
#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(oal_bus_irq_affinity_init);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

