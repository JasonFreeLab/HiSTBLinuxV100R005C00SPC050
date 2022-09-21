/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_test_main.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年2月19日
  最近修改   :
  功能描述   : 芯片验证的dmac层测试代码、桩函数等
  函数列表   :
  修改历史   :
  1.日    期   : 2014年2月19日
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
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "hmac_ext_if.h"
#include "oam_ext_if.h"
#include "hmac_vap.h"
#include "hmac_main.h"
#include "hmac_test_main.h"
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
#include "dmac_ext_if.h"
#include "hmac_vap.h"
#include "dmac_vap.h"
#include "mac_vap.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_TEST_MAIN_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
hmac_test_mng_stru  g_st_hmac_test_mng;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_test_init
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  hmac_test_init(oal_void)
{
    OAL_MEMZERO(&g_st_hmac_test_mng, OAL_SIZEOF(hmac_test_mng_stru));
}

/*****************************************************************************
 函 数 名  : hmac_test_set_chip_test
 功能描述  : 打开芯片验证的总开关
 输入参数  : puc_chip_test_open: 开关
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void hmac_test_set_chip_test(oal_uint8 uc_chip_test_open)
{
    g_st_hmac_test_mng.uc_hmac_chip_test = uc_chip_test_open;
    return;
}

/*****************************************************************************
 函 数 名  : hmac_test_get_chip_test
 功能描述  : 获得芯片验证的总开关
 输入参数  :
 输出参数  : 无
 返 回 值  : 芯片验证的总开关
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_test_get_chip_test(oal_void)
{
    return g_st_hmac_test_mng.uc_hmac_chip_test;
}

/*lint -e19*/
oal_module_symbol(hmac_test_set_chip_test);
/*lint +e19*/


#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

