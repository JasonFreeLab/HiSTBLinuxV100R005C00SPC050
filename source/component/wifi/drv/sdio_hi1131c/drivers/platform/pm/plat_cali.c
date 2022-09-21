/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : plat_cali.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : 更新和加载独立校准数据
  函数列表   :

  修改历史   :
  1.日    期   : 2015年7月16日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "plat_firmware.h"
#include "plat_cali.h"
#include "plat_debug.h"
#include "plat_type.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RF_CALI_DATA_BUF_LEN  (sizeof(oal_cali_param_stru))

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/

/*保存校准数据的buf*/
oal_uint8 *g_pucCaliDataBuf = NULL;
oal_uint8 g_uc_netdev_is_open = OAL_FALSE;
/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : get_cali_count
 功能描述  : 返回校准的次数，首次开机校准时为0，以后递增
 输入参数  : uint32 *count:调用函数保存校准次数的地址
 输出参数  : count:自开机以来，已经校准的次数
 返 回 值  : 0表示成功，-1表示失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 get_cali_count(oal_uint32 *count)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint16 cali_count;
    oal_uint32 cali_parm;

    if (NULL == count)
    {
        PS_PRINT_ERR("count is NULL\n");
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    cali_count    = pst_cali_data->st_cali_update_info.ul_cali_time;
    cali_parm     = *(oal_uint32 *)&(pst_cali_data->st_cali_update_info);

    PS_PRINT_WARNING("cali count is [%d], cali update info is [%d]\n", cali_count, cali_parm);

    *count = cali_parm;

    return SUCC;
}

#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : get_bfgx_cali_data
 功能描述  : 返回保存bfgx校准数据的内存首地址以及长度
 输入参数  : uint8  *buf:调用函数保存bfgx校准数据的首地址
             uint32 *len:调用函数保存bfgx校准数据内存长度的地址
             uint32 buf_len:buf的长度
 输出参数  : 无
 返 回 值  : 0表示成功，-1表示失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
int32 get_bfgx_cali_data(oal_uint8 *buf, oal_uint32 *len, oal_uint32 buf_len)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint32 bfgx_cali_data_len;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -EFAIL;
    }

    if (NULL == len)
    {
        PS_PRINT_ERR("len is NULL\n");
        return -EFAIL;
    }

    bfgx_cali_data_len = sizeof(oal_bfgn_cali_param_stru);
    if (buf_len < bfgx_cali_data_len)
    {
        PS_PRINT_ERR("buf_len[%d] is smaller than struct size[%d]\n", buf_len, bfgx_cali_data_len);
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    OS_MEM_CPY(buf, (oal_uint8 *)&(pst_cali_data->st_bfgn_cali_data), bfgx_cali_data_len);
    *len = bfgx_cali_data_len;

    return SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : get_cali_data_buf_addr
 功能描述  : 返回保存校准数据的内存地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_pucCaliDataBuf的地址，也可能是NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void *get_cali_data_buf_addr(void)
{
    PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
    return g_pucCaliDataBuf;
}

EXPORT_SYMBOL(get_cali_data_buf_addr);
EXPORT_SYMBOL(g_uc_netdev_is_open);

/*****************************************************************************
 函 数 名  : cali_data_buf_malloc
 功能描述  : 分配保存校准数据的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0表示分配成功，-1表示分配失败
 调用函数  :
 被调函数  : firmware_cfg_init

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 cali_data_buf_malloc(void)
{
    oal_uint8 *buffer = NULL;

    buffer = oal_kzalloc(RF_CALI_DATA_BUF_LEN, OAL_GFP_KERNEL);
    if (NULL == buffer)
    {
        return -EFAIL;
    }
    g_pucCaliDataBuf = buffer;

    //plat_bfgx_cali_data_test();

    return SUCC;
}

/*****************************************************************************
 函 数 名  : cali_data_buf_free
 功能描述  : 释放保存校准数据的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : firmware_cfg_clear

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void cali_data_buf_free(void)
{
    if (NULL != g_pucCaliDataBuf)
    {
        oal_free(g_pucCaliDataBuf);
    }
    g_pucCaliDataBuf = NULL;
}


