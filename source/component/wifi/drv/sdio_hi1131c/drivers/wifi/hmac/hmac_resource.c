/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_resource.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年1月31日
  最近修改   :
  功能描述   : HMAC资源池主文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年1月31日
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
#include "hmac_resource.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RESOURCE_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
hmac_res_stru    g_st_hmac_res;
oal_uint8   g_auc_hmac_macaddr[WLAN_MAC_ADDR_LEN] = {0};


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : hmac_res_alloc_mac_dev
 功能描述  : 获取一个HMAC DEV资源
 输入参数  : 无
 输出参数  : HMAC DEV内存索引值
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_res_alloc_mac_dev(oal_uint32    ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_res_alloc_hmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[ul_dev_idx])++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_res_free_mac_dev
 功能描述  : 释放对应HMAC DEV的内存
 输入参数  : 对应HMAC DEV内存索引
 输出参数  : 无
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_res_free_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_free_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[ul_dev_idx])--;

    if (0 != g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[ul_dev_idx])
    {
        return OAL_SUCC;
    }

    /* 入队索引值需要加1操作 */
    oal_queue_enqueue(&(g_st_hmac_res.st_hmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_dev_idx + 1));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : hmac_res_get_mac_dev
 功能描述  : 获取对应HMAC DEV索引的内存
 输入参数  : 对应HMAC DEV内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
hmac_device_stru  *hmac_res_get_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_res_get_hmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_PTR_NULL;
    }

    return &(g_st_hmac_res.st_hmac_dev_res.ast_hmac_dev_info[ul_dev_idx]);
}

/*****************************************************************************
 函 数 名  : hmac_res_init
 功能描述  : 初始化HMAC资源池内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_res_init(oal_void)
{
    oal_uint32      ul_loop;

    OAL_MEMZERO(&g_st_hmac_res, OAL_SIZEOF(g_st_hmac_res));

    /***************************************************************************
            初始化HMAC DEV的资源管理内容
    ***************************************************************************/
    oal_queue_set(&(g_st_hmac_res.st_hmac_dev_res.st_queue),
                  g_st_hmac_res.st_hmac_dev_res.aul_idx,
                  MAC_RES_MAX_DEV_NUM);

    for (ul_loop = 0; ul_loop < MAC_RES_MAX_DEV_NUM; ul_loop++)
    {
        /* 初始值保存的是对应数组下标值加1 */
        oal_queue_enqueue(&(g_st_hmac_res.st_hmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_loop + 1));

        /* 初始化对应的引用计数值为0 */
        g_st_hmac_res.st_hmac_dev_res.auc_user_cnt[ul_loop] = 0;
    }

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : hmac_res_exit
 功能描述  : 资源池退出，释放动态申请的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_res_exit(mac_board_stru *pst_hmac_board)
{
    oal_uint8           uc_chip;
    oal_uint8           uc_device_max;
    oal_uint8           uc_device;
    oal_uint16          ul_chip_max_num;
    mac_chip_stru       *pst_chip;

    /* chip支持的最大数由PCIe总线处理提供; */
    ul_chip_max_num = oal_bus_get_chip_num();

    for (uc_chip = 0; uc_chip < ul_chip_max_num; uc_chip++)
    {
        pst_chip = &pst_hmac_board->ast_chip[uc_chip];

        /* OAL接口获取支持device个数 */
        uc_device_max = oal_chip_get_device_num(pst_chip->ul_chip_ver);

        for (uc_device = 0; uc_device < uc_device_max; uc_device++)
        {
            /* 释放hmac res资源 */
            hmac_res_free_mac_dev(pst_chip->auc_device_id[uc_device]);
        }
    }
    return OAL_SUCC;
}
#endif
/*lint -e19*/
oal_module_symbol(hmac_res_get_mac_dev);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

