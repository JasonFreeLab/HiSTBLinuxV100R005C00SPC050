/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_vap.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
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
#include "oal_mem.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "hmac_ext_if.h"
#endif
#include "dmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_VAP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_UAPSD
#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
oal_uint8 g_uc_uapsd_cap = WLAN_FEATURE_UAPSD_IS_OPEN;
#else
oal_uint8 g_uc_uapsd_cap = OAL_FALSE;
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_HISTREAM
oal_uint8 g_uc_histream_switch = HISTREAM_SWITCH_OFF;
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
/* 1131debug: mac_vap_init_mib_11n   预留接口 */
oal_bool_enum_uint8 mac_vap_init_mib_11n_adjust(mac_vap_stru *);
typedef oal_bool_enum_uint8 (*mac_vap_init_mib_11n_adjust_type)(mac_vap_stru  *pst_mac_vap);
mac_vap_init_mib_11n_adjust_type g_fn_mac_vap_init_mib_11n_adjust_patch_ram = mac_vap_init_mib_11n_adjust;

/* 1131debug: mac_vap_init   预留接口 */
oal_bool_enum_uint8 mac_vap_init_adjust(mac_vap_stru *, oal_uint8, oal_uint8, oal_uint8, mac_cfg_add_vap_param_stru *);
typedef oal_bool_enum_uint8 (*mac_vap_init_adjust_type)(
                mac_vap_stru               *pst_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param);
mac_vap_init_adjust_type g_fn_mac_vap_init_adjust_patch_ram = mac_vap_init_adjust;
#endif
/* WME初始参数定义，按照OFDM初始化 AP模式 值来自于TGn 9 Appendix D: Default WMM AC Parameters */
/* :修改BE/BK的cwmin的大小，由4修改为3，
    之前修改影响认证4.2.23&4.2.7&4.2.8，同频干扰由抗干扰动态edca调整算法实现,现在由3修改为4*/
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_ap[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          4,     6,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,    0,
    },

    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        1,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        1,          2,     3,     1504,
    },
};

/* WMM初始参数定义，按照OFDM初始化 STA模式 */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_sta[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          3,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          2,     3,     1504,
    },
};

/* WMM初始参数定义，aput建立的bss中STA的使用的EDCA参数 */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_bss[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          4,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          2,     3,     1504,
    },
};

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/* 多用户多优先级使用的EDCA参数 */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_multi_user_multi_ac_params_ap[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },
};
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_get_wmm_cfg
 功能描述  : 获取ap或者sta 的配置指针
 输入参数  : en_vap_mode: en_vap_mode当前模式

 输出参数  :
 返 回 值  : wmm配置指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
mac_wme_param_stru  *mac_get_wmm_cfg(wlan_vap_mode_enum_uint8 en_vap_mode)
{
    /* 参考认证项配置，没有按照协议配置，WLAN_VAP_MODE_BUTT表示是ap广播给sta的edca参数 */
    if (WLAN_VAP_MODE_BUTT == en_vap_mode)
    {
        return (mac_wme_param_stru  *)g_ast_wmm_initial_params_bss;
    }
    else if(WLAN_VAP_MODE_BSS_AP == en_vap_mode)
    {
       return (mac_wme_param_stru  *)g_ast_wmm_initial_params_ap;
    }
    return (mac_wme_param_stru  *)g_ast_wmm_initial_params_sta;

}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 函 数 名  : mac_get_wmm_cfg_multi_user_multi_ac
 功能描述  : 获取多用户多优先级时ap的配置指针
 输入参数  : uc_traffic_type: 业务类型

 输出参数  :
 返 回 值  : wmm配置指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
mac_wme_param_stru  *mac_get_wmm_cfg_multi_user_multi_ac(oal_traffic_type_enum_uint8 uc_traffic_type)
{
    /* 多用户下业务类型采用新参数，否则采用ap模式下的默认值 */
    if (OAL_TRAFFIC_MULTI_USER_MULTI_AC == uc_traffic_type)
    {
        return (mac_wme_param_stru  *)g_ast_wmm_multi_user_multi_ac_params_ap;
    }

    return (mac_wme_param_stru  *)g_ast_wmm_initial_params_ap;

}
#endif

/*****************************************************************************
 函 数 名  : mac_mib_set_station_id
 功能描述  : 设置StationID值，即mac地址
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru   *pst_param;

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

    oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,pst_param->auc_station_id);

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 函 数 名  : mac_mib_get_station_id
 功能描述  : 设置StationID值，即mac地址
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len : 返回参数的长度
             pc_param: 返回参数
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru   *pst_param;

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

    oal_memcopy(pst_param->auc_station_id,
                pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    *puc_len = OAL_SIZEOF(mac_cfg_staion_id_param_stru);

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : mac_mib_set_bss_type
 功能描述  : 设置bss type mib值
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = *((oal_int32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType = (oal_uint8)l_value;

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_mib_get_bss_type
 功能描述  : 读取bss type mib值
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len : 返回参数的长度
             pc_param: 返回参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_int32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType;
    *puc_len = OAL_SIZEOF(oal_int32);

    return OAL_SUCC;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_mib_set_ssid
 功能描述  : 设置ssid mib值
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ssid_param_stru    *pst_param;
    oal_uint8                   uc_ssid_len;
    oal_uint8                  *puc_mib_ssid;

    pst_param   = (mac_cfg_ssid_param_stru *)puc_param;
    uc_ssid_len = pst_param->uc_ssid_len;       /* 长度不包括字符串结尾'\0' */

    if (uc_ssid_len > WLAN_SSID_MAX_LEN - 1)
    {
        uc_ssid_len = WLAN_SSID_MAX_LEN - 1;
    }

    puc_mib_ssid = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;

    oal_memcopy(puc_mib_ssid, pst_param->ac_ssid, uc_ssid_len);
    puc_mib_ssid[uc_ssid_len] = '\0';

    return OAL_SUCC;
}

//#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_mib_get_ssid
 功能描述  : 读取ssid mib值
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len : 返回参数的长度
             pc_param: 返回参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    mac_cfg_ssid_param_stru *pst_param;
    oal_uint8                uc_ssid_len;
    oal_uint8               *puc_mib_ssid;

    puc_mib_ssid = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;
    uc_ssid_len  = (oal_uint8)OAL_STRLEN((oal_int8 *)puc_mib_ssid);

    pst_param = (mac_cfg_ssid_param_stru *)puc_param;

    pst_param->uc_ssid_len = uc_ssid_len;
    oal_memcopy(pst_param->ac_ssid, puc_mib_ssid, uc_ssid_len);

    *puc_len = OAL_SIZEOF(mac_cfg_ssid_param_stru);

    return OAL_SUCC;
}
//#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_mib_set_beacon_period
 功能描述  : 设置beacon interval的值
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32       ul_value;

    ul_value     = *((oal_uint32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)ul_value;

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_mib_get_beacon_period
 功能描述  : 读取beacon interval的值
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len    : 返回参数的长度
             pc_param   : 返回参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_uint32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_mib_set_dtim_period
 功能描述  : 设置dtim period的值
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value     = *((oal_int32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = (oal_uint32)l_value;

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_mib_get_dtim_period
 功能描述  : 读取dtim period的值
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len    : 返回参数的长度
             pc_param   : 返回参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_uint32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_mib_set_shpreamble
 功能描述  : 设置short preamble MIB值
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value     = *((oal_int32 *)puc_param);

    if (0 != l_value)
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, OAL_TRUE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_mib_get_shpreamble
 功能描述  : 获取short preamble MIB值
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = mac_mib_get_ShortPreambleOptionImplemented(pst_mac_vap);

    *((oal_int32 *)puc_param) = l_value;

    *puc_len = OAL_SIZEOF(l_value);

    return OAL_SUCC;

}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

#if 0
/*****************************************************************************
 函 数 名  : mac_mib_get_GroupReceivedFrameCount
 功能描述  : 读取VAP已接收到的组播帧的数目
 输入参数  : (1)需要设置的VAP的指针
             (2)需要设置的字符串的长度
 输出参数  : 接收到的amsdu的个数
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_get_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_group_count)
{
    *((oal_uint32*)puc_group_count) = pst_mac_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11GroupReceivedFrameCount;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_mib_set_GroupReceivedFrameCount
 功能描述  : 设置接收到的的组播帧的数目
 输入参数  : (1)需要设置的VAP的指针
             (2)需要设置的字符串的长度
             (3)设置的值
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_mib_set_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_group_count)
{
    oal_uint32      ul_value;

    ul_value = *((oal_uint32 *)puc_group_count);

    pst_mac_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11GroupReceivedFrameCount = ul_value;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : mac_mib_get_wpa_pairwise_cipher_suite
 功能描述  : 获取实现的pairwise cipher suites个数
 输入参数  : pst_mac_vap: 指向vap
 输出参数  : puc_num    : 实现的pairwise cipher suites个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_get_wpa_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            uc_num++;
        }
    }
    *puc_num = uc_num;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_wpa2_pairwise_cipher_suite
 功能描述  : 获取实现的pairwise cipher suites个数
 输入参数  : pst_mac_vap: 指向vap
 输出参数  : puc_num    : 实现的pairwise cipher suites个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            uc_num++;
        }
    }

    *puc_num = uc_num;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_authentication_suite
 功能描述  : 获取实现的authentication suites个数
 输入参数  : pst_mac_vap: 指向vap
 输出参数  : puc_num    : 实现的authentication suites个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月16日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_get_authentication_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_AUTHENTICATION_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].en_dot11RSNAConfigAuthenticationSuiteActivated)
        {
            uc_num++;
        }
    }

    *puc_num = uc_num;
}

/*****************************************************************************
 函 数 名  : mac_mib_get_wpa2_pairwise_cipher_suite_value
 功能描述  : 获取实现的pairwise cipher suites 加密套件值
 输入参数  : pst_mac_vap        : 指向vap
 输出参数  : puc_pairwise_value : 实现的pairwise cipher suites 加密套件值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value)
{
    oal_uint8   uc_loop;
    oal_uint8   uc_pairwise_index = 0;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_pairwise_value))
    {
        MAC_ERR_VAR(0, "Error:NULL pointer.%x, %x", pst_mac_vap, puc_pairwise_value);
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_mib_get_wpa2_pairwise_cipher_suite_value::param null, %d %d.}",  pst_mac_vap, puc_pairwise_value);

        return;
    }

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            puc_pairwise_value[uc_pairwise_index++] = pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].uc_dot11RSNAConfigPairwiseCipherImplemented;
        }
    }
}

/*****************************************************************************
 函 数 名  : mac_mib_get_wpa_pairwise_cipher_suite_value
 功能描述  : 获取实现的pairwise cipher suites 加密套件值
 输入参数  : pst_mac_vap        : 指向vap
 输出参数  : puc_pairwise_value : 实现的pairwise cipher suites 加密套件值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_get_wpa_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value)
{
    oal_uint8   uc_loop;
    oal_uint8   uc_pairwise_index = 0;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_pairwise_value))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_mib_get_wpa_pairwise_cipher_suite_value::param null.}");

        return;
    }

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            puc_pairwise_value[uc_pairwise_index++] = pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].uc_dot11RSNAConfigPairwiseCipherImplemented;
        }
    }
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : mac_mib_get_smps
 功能描述  : 获取MIB项 en_dot11MIMOPowerSave 的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : en_dot11MIMOPowerSave
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数
*****************************************************************************/
wlan_mib_mimo_power_save_enum_uint8 mac_mib_get_smps(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_smps_mode
 功能描述  : 获取en_dot11MIMOPowerSave的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    if (OAL_TRUE != pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
    {
        /* 非HT用户，不支持SMPS 返回非法信息WLAN_MIB_MIMO_POWER_SAVE_BUTT */
        *puc_param = WLAN_MIB_MIMO_POWER_SAVE_BUTT;
        *pus_len   = OAL_SIZEOF(oal_uint8);
        return OAL_SUCC;
    }

    *puc_param = pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave;

    *pus_len   = OAL_SIZEOF(oal_uint8);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_smps_en
 功能描述  : 获取bit_smps的值
 输入参数  : pst_mac_vap: MAC VAP结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    mac_device_stru   *pst_mac_device;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{mac_vap_get_smps_en::pst_mac_device[%d] null.}", pst_mac_vap->uc_device_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_param = pst_mac_device->en_smps;

    *pus_len   = OAL_SIZEOF(oal_uint8);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_smps
 功能描述  : 设置vap的smps
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_smps(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_smps = uc_value;
}
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
/*****************************************************************************
 函 数 名  : mac_vap_set_uapsd_en
 功能描述  : 设置U-APSD使能
 输入参数  : pst_mac_vap: 指向mac vap结构体
             uc_len     : 参数长度
             pc_param   : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32  mac_vap_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_value)
{
    pst_mac_vap->st_cap_flag.bit_uapsd = (OAL_TRUE == uc_value)?1:0;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_uapsd_en
 功能描述  : 读取beacon interval的值
 输入参数  : pst_mac_vap: 指向mac vap结构体
 输出参数  : puc_len    : 返回参数的长度
             pc_param   : 返回参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  mac_vap_get_uapsd_en(mac_vap_stru *pst_mac_vap)
{
    //*puc_param  = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11APSDOptionImplemented;

    return pst_mac_vap->st_cap_flag.bit_uapsd;
}

#endif


/*****************************************************************************
 函 数 名  : mac_vap_user_exist
 功能描述  : 检查dmac list的检查
 输入参数  :
 输出参数  : 无
 返 回 值  : 成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月02日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年05月02日
    作    者   : 
    修改内容   : 修改函数名及返回值

*****************************************************************************/
oal_uint32 mac_vap_user_exist(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru      *pst_user_list_head;
    oal_dlist_head_stru      *pst_member_entry;


    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_member_entry,pst_user_list_head,pst_head)
    {
        if(pst_new == pst_member_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{oal_dlist_check_head:dmac user doule add.}");
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : mac_vap_add_assoc_user
 功能描述  : 增加关联用户，获取hash值并加入hash表中
 输入参数  : vap对象内存指针，以及user对象指针(user对象需要在调用此函数前申请并赋值)
 输出参数  : 无
 返 回 值  : 成功或失败
 调用函数  : mac_vap_get_user_hash_value、oal_dlist_insert_elem_head
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_add_assoc_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx)
{
    mac_user_stru              *pst_user;
    mac_res_user_hash_stru     *pst_hash;
    oal_uint32                  ul_rslt;
    oal_uint16                  us_hash_idx;
    oal_dlist_head_stru        *pst_dlist_head;
    oal_uint                    ul_irq_save;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_user[%d] null.}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user->us_user_hash_idx = MAC_CALCULATE_HASH_VALUE(pst_user->auc_user_mac_addr);

    /* 分配hash结构体: DMAC_offload 模式下 hmac和dmac侧的us_hash_idx可能不一致，但是对业务无影响，
    此indx仅用来标志每一个使用中的hash单元，不用来做hash查找用户 */
    ul_rslt = mac_res_alloc_hash(&us_hash_idx);

    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_add_assoc_user::mac_res_alloc_hash failed[%d].}", ul_rslt);

        return ul_rslt;
    }

    pst_hash = mac_res_get_hash(us_hash_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hash))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_hash[%d] null.}", us_hash_idx);
        mac_res_free_hash(us_hash_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_SUCC == mac_vap_user_exist(&(pst_user->st_user_dlist), &(pst_vap->st_mac_user_list_head)))
    {
        mac_res_free_hash(us_hash_idx);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::user[%d] already exist.}", us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 记录HASH对应的资源池索引值 */
    pst_hash->us_hash_res_idx = us_hash_idx;

    /* 记录对应的用户索引值 */
    pst_hash->us_user_idx = us_user_idx;

    pst_dlist_head = &(pst_vap->ast_user_hash[pst_user->us_user_hash_idx]);
#ifdef _PRE_WLAN_DFT_STAT
    (pst_vap->ul_hash_cnt)++;
#endif
    oal_dlist_add_head(&(pst_hash->st_entry), pst_dlist_head);

    /* 加入双向链表表头 */
    pst_dlist_head = &(pst_vap->st_mac_user_list_head);
    oal_dlist_add_head(&(pst_user->st_user_dlist), pst_dlist_head);
#ifdef _PRE_WLAN_DFT_STAT
    (pst_vap->ul_dlist_cnt)++;
#endif
    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* 更新cache user */
    oal_set_mac_addr(pst_vap->auc_cache_user_mac_addr, pst_user->auc_user_mac_addr);
    pst_vap->us_cache_user_id = us_user_idx;

    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* 记录STA模式下的与之关联的VAP的id */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_vap, (oal_uint8)us_user_idx);
    }

    /* vap已关联 user个数++ */
    pst_vap->us_user_nums++;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_vap_del_user
 功能描述  : 删除用户，将用户从双向链表中删除，并从hash表中删除
 输入参数  : vap对象指针，以及user对象指针(user对象需要在调用此函数前找到,
             并且此函数不负责释放user内存,由删除者调用USER_DESTORY函数释放内存)
 输出参数  : 无
 返 回 值  : 成功或失败
 调用函数  : oal_dlist_rmv_elem
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_del_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx)
{
    mac_user_stru          *pst_user;
    mac_user_stru          *pst_user_temp;
    oal_dlist_head_stru    *pst_hash_head;
    oal_dlist_head_stru    *pst_entry;
    mac_res_user_hash_stru *pst_user_hash;
    oal_dlist_head_stru    *pst_dlist_tmp       = OAL_PTR_NULL;
    oal_uint32              ul_ret              = OAL_FAIL;
    oal_uint8               uc_txop_ps_user_cnt = 0;
    oal_uint                ul_irq_save;


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ASSOC, "{mac_vap_del_user::pst_vap null,us_user_idx is %d}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }


    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* 与cache user id对比 , 相等则清空cache user*/
    if (us_user_idx == pst_vap->us_cache_user_id)
    {
        oal_set_mac_addr_zero(pst_vap->auc_cache_user_mac_addr);
        /*  解决用户已删除，cache id和mac addr均为0，导致发送完成中断下半部依旧可以找到已删除的用户 */
        pst_vap->us_cache_user_id = MAC_INVALID_USER_ID;
    }

    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);

    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::pst_user null,us_user_idx is %d}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_asoc_state(pst_user, MAC_USER_STATE_BUTT);

    if(pst_user->us_user_hash_idx >= MAC_VAP_USER_HASH_MAX_VALUE)
    {
        /*ADD USER命令丢失，或者重复删除User都可能进入此分支。*/
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::hash idx invaild %u}", pst_user->us_user_hash_idx);
        return OAL_FAIL;
    }

    pst_hash_head = &(pst_vap->ast_user_hash[pst_user->us_user_hash_idx]);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, pst_hash_head)
    {
        pst_user_hash = (mac_res_user_hash_stru *)pst_entry;

        pst_user_temp = (mac_user_stru *)mac_res_get_mac_user((oal_uint8)(pst_user_hash->us_user_idx));

        if (OAL_PTR_NULL == pst_user_temp)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::pst_user_temp null,us_user_idx is %d}", us_user_idx);

            continue;
        }
        if (pst_user_temp->st_vht_hdl.bit_vht_txop_ps)
        {
            uc_txop_ps_user_cnt++;
        }

        if (!oal_compare_mac_addr(pst_user->auc_user_mac_addr, pst_user_temp->auc_user_mac_addr))
        {
            oal_dlist_delete_entry(pst_entry);

            /* 从双向链表中拆掉 */
            oal_dlist_delete_entry(&(pst_user->st_user_dlist));

            mac_res_free_hash(pst_user_hash->us_hash_res_idx);
            ul_ret = OAL_SUCC;

#ifdef _PRE_WLAN_DFT_STAT
            (pst_vap->ul_hash_cnt)--;
            (pst_vap->ul_dlist_cnt)--;
#endif
            /* 初始化相应成员 */
            pst_user->us_user_hash_idx = 0xffff;
            pst_user->us_assoc_id      = us_user_idx;
            pst_user->en_is_multi_user = OAL_FALSE;
            OAL_MEMZERO(pst_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
            pst_user->uc_vap_id        = 0xff;
            pst_user->uc_device_id     = 0xff;
            pst_user->uc_chip_id       = 0xff;
            pst_user->en_user_asoc_state = MAC_USER_STATE_BUTT;
            pst_user->uc_drop_ncw  = OAL_FALSE;
        }
    }

    if (0 == uc_txop_ps_user_cnt)
    {
        pst_vap->st_cap_flag.bit_txop_ps = OAL_FALSE;
    }

    if (OAL_SUCC == ul_ret)
    {
        /* vap已关联 user个数-- */
        if (pst_vap->us_user_nums)
        {
            pst_vap->us_user_nums--;
        }
        /* STA模式下将关联的VAP的id置为非法值 */
        if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
        {
            mac_vap_set_assoc_id(pst_vap, 0xff);
        }
        return OAL_SUCC;
    }

    OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::delete user failed,user idx is %d.}", us_user_idx);

    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : mac_vap_find_user_by_macaddr
 功能描述  : 根据user MAC地址查找user对象
 输入参数  : vap对象指针，以及user MAC地址
 输出参数  : user对象指针
 返 回 值  : 成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_find_user_by_macaddr( mac_vap_stru *pst_vap, oal_uint8 *puc_sta_mac_addr, oal_uint16 *pus_user_idx)
{
    mac_user_stru              *pst_mac_user;
    oal_uint32                  ul_user_hash_value;
    mac_res_user_hash_stru     *pst_hash;
    oal_dlist_head_stru        *pst_entry;
    oal_uint                    ul_irq_save;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
                  || (OAL_PTR_NULL == puc_sta_mac_addr)
                  || ((OAL_PTR_NULL == pus_user_idx))))
    {
        /* 1131维测，修改打印每个地址值 */
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{mac_vap_find_user_by_macaddr::pst_vap:[%p],puc_sta_mac_addr:[%p],pus_user:[%p].}", pst_vap, puc_sta_mac_addr, pus_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_vap->uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            return OAL_FAIL;
        }

        if (!oal_compare_mac_addr(pst_mac_user->auc_user_mac_addr, puc_sta_mac_addr))
        {
            *pus_user_idx = pst_vap->uc_assoc_vap_id;
            return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;
        }
        return OAL_FAIL;
    }

    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);
    /* 与cache user对比 , 相等则直接返回cache user id*/
    if (!oal_compare_mac_addr(pst_vap->auc_cache_user_mac_addr, puc_sta_mac_addr))
    {
        /* 用户删除后，user macaddr和cache user macaddr地址均为0，但实际上用户已经删除，此时user id无效 */
        *pus_user_idx = pst_vap->us_cache_user_id;
        oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
        return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;
    }

    ul_user_hash_value = MAC_CALCULATE_HASH_VALUE(puc_sta_mac_addr);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_vap->ast_user_hash[ul_user_hash_value]))
    {
        pst_hash = (mac_res_user_hash_stru *)pst_entry;

        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_hash->us_user_idx);

        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_find_user_by_macaddr::pst_mac_user null.user idx %d}",pst_hash->us_user_idx);
            continue;
        }

        /* 相同的MAC地址 */
        if (!oal_compare_mac_addr(pst_mac_user->auc_user_mac_addr, puc_sta_mac_addr))
        {
            *pus_user_idx = pst_hash->us_user_idx;
            /*更新cache user*/
            oal_set_mac_addr(pst_vap->auc_cache_user_mac_addr, pst_mac_user->auc_user_mac_addr);
            pst_vap->us_cache_user_id = pst_hash->us_user_idx;
            oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
            return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;
        }
    }
    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
    return OAL_FAIL;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_device_find_user_by_macaddr
 功能描述  : 根据user MAC地址查找user对象
 输入参数  : vap对象指针，以及user MAC地址
 输出参数  : user对象指针
 返 回 值  : 成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_device_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx)
{
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    oal_uint8                   uc_vap_id;
    oal_uint8                   uc_vap_idx;
    oal_uint32                  ul_ret;

    /* 获取device */
    pst_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "mac_res_get_dev[%d] return null ", pst_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 对device下的所有vap进行遍历 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        uc_vap_id = pst_device->auc_vap_id[uc_vap_idx];

        /* 配置vap不需要处理 */
        if (uc_vap_id == pst_device->uc_cfg_vap_id)
        {
            continue;
        }

        /* 本vap不需要处理 */
        if (uc_vap_id == pst_vap->uc_vap_id)
        {
            continue;
        }

        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            continue;
        }

        /* 只处理AP模式 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_sta_mac_addr, pus_user_idx);
        if (OAL_SUCC == ul_ret)
        {
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

#if 0
/*****************************************************************************
 函 数 名  : mac_vap_update_user
 功能描述  : 更新user信息
 输入参数  : VAP对象和user数据结构指针，入参user数据结构中的所有信息在调用此函数前均已赋值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_update_user(mac_vap_stru *pst_vap, oal_uint32   ul_user_dix)
{
    /* 非OFFLOAD方案下不需要实现 */

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : mac_vap_init_wme_param
 功能描述  : 初始化wme参数, 除sta之外的模式
 输入参数  :
 输出参数  : pst_wme_param: wme参数
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_init_wme_param(mac_vap_stru *pst_mac_vap)
{
    OAL_CONST mac_wme_param_stru   *pst_wmm_param;
    OAL_CONST mac_wme_param_stru   *pst_wmm_param_sta;
    oal_uint8                       uc_ac_type;

    pst_wmm_param = mac_get_wmm_cfg(pst_mac_vap->en_vap_mode);
    if(OAL_PTR_NULL == pst_wmm_param)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_ac_type = 0; uc_ac_type < WLAN_WME_AC_BUTT; uc_ac_type++)
    {
        /* VAP自身的EDCA参数 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableIndex   = uc_ac_type + 1;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableAIFSN   = pst_wmm_param[uc_ac_type].ul_aifsn;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableCWmin   = pst_wmm_param[uc_ac_type].ul_logcwmin;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableCWmax   = pst_wmm_param[uc_ac_type].ul_logcwmax;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableTXOPLimit = pst_wmm_param[uc_ac_type].ul_txop_limit;
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* AP模式时广播给STA的EDCA参数，只在AP模式需要初始化此值，使用WLAN_VAP_MODE_BUTT， */
        pst_wmm_param_sta = mac_get_wmm_cfg(WLAN_VAP_MODE_BUTT);

        for (uc_ac_type = 0; uc_ac_type < WLAN_WME_AC_BUTT; uc_ac_type++)
        {
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableIndex     = uc_ac_type + 1;  /* 注: 协议规定取值1 2 3 4 */
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableAIFSN     = pst_wmm_param_sta[uc_ac_type].ul_aifsn;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableCWmin     = pst_wmm_param_sta[uc_ac_type].ul_logcwmin;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableCWmax     = pst_wmm_param_sta[uc_ac_type].ul_logcwmax;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableTXOPLimit = pst_wmm_param_sta[uc_ac_type].ul_txop_limit;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_mib_clear_rsna_auth_suite
 功能描述  : 清除 RSN认证套件
 输入参数  :
 输出参数  : pst_mac_vap
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_clear_rsna_auth_suite(mac_vap_stru *pst_mac_vap)
{
    oal_uint8   uc_index = 0;

    for (uc_index = 0; uc_index < WLAN_AUTHENTICATION_SUITES; uc_index++)
    {
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].uc_dot11RSNAConfigAuthenticationSuiteImplemented = 0xff;
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].ul_dot11RSNAConfigAuthenticationSuiteIndex       = uc_index;
    }
}

/*****************************************************************************
 函 数 名  : mac_mib_set_rsna_auth_suite
 功能描述  : 设置 RSN认证套件信息
 输入参数  :
 输出参数  : pst_mac_vap，uc_auth_value
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_mib_set_rsna_auth_suite(mac_vap_stru *pst_mac_vap, oal_uint8 uc_auth_value)
{
    oal_uint8 uc_index;

    if ((WLAN_AUTH_SUITE_1X == uc_auth_value)
        || (WLAN_AUTH_SUITE_PSK == uc_auth_value))
    {
        uc_index = 0;
    }
    else if ((WLAN_AUTH_SUITE_1X_SHA256 == uc_auth_value)
        || (WLAN_AUTH_SUITE_PSK_SHA256 == uc_auth_value))
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_mac_vap->uc_vap_id, "ERROR! auth_value = %d", uc_auth_value);
        return;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].uc_dot11RSNAConfigAuthenticationSuiteImplemented = uc_auth_value;
    pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_TRUE;

}
#if 0
/*****************************************************************************
 函 数 名  : mac_vap_get_user_wme_info
 功能描述  : 读取关联用户的WME参数
 输入参数  : pst_vap      : 指向VAP用户的指针
             en_wme_type  : WME枚举类型
 输出参数  : ppst_wme_info: 指向WME参数的指针
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_get_user_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if (OAL_PTR_NULL == pst_vap || OAL_PTR_NULL == pst_wme_info)
    {
        MAC_ERR_LOG(0, "mac_get_user_wme_info: input pointers are null!");
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{mac_vap_get_user_wme_info::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_wme_info->ul_aifsn = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableAIFSN;
    pst_wme_info->ul_logcwmax = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmax;
    pst_wme_info->ul_logcwmin = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmin;
    pst_wme_info->ul_txop_limit = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableTXOPLimit;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_user_wme_info
 功能描述  : 设置关联用户的WME参数
 输入参数  : pst_vap      : 指向VAP用户的指针
             en_wme_type  : WME枚举类型
             pst_wme_info : 指向WME参数的指针
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_set_user_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if (OAL_PTR_NULL == pst_vap || OAL_PTR_NULL == pst_wme_info)
    {
        MAC_ERR_LOG(0, "mac_get_user_wme_info: input pointers are null!");
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{mac_vap_set_user_wme_info::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableAIFSN = pst_wme_info->ul_aifsn;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmax = pst_wme_info->ul_logcwmax;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmin = pst_wme_info->ul_logcwmin;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableTXOPLimit = pst_wme_info->ul_txop_limit;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : mac_vap_init_rsna_status
 功能描述  : 初始化11i mib信息，STA相关统计信息
 输入参数  : pst_vap: 指向VAP用户的指针
           : ul_idx :sta idx
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_init_rsna_status(mac_vap_stru *pst_vap, oal_uint32 ul_idx)
{
    OAL_MEMZERO((oal_void *)(&pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx]), OAL_SIZEOF(wlan_mib_Dot11RSNAStatsEntry_stru));
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx].ul_dot11RSNAStatsIndex = ul_idx;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx].ul_dot11RSNAStatsVersion = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigVersion;
}

/*****************************************************************************
 函 数 名  : mibset_RSNAStatsSTAAddress
 功能描述  :
 输入参数  : pst_vap: 指向VAP用户的指针
           : ul_idx :
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void mibset_RSNAStatsSTAAddress(oal_uint8 *puc_addr, mac_vap_stru *pst_vap, oal_uint16 us_idx)
{
    oal_memcopy((oal_void *)pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[us_idx].auc_dot11RSNAStatsSTAAddress,puc_addr, WLAN_MAC_ADDR_LEN);
}
void mibset_RSNAStatsSelectedPairwiseCipher(oal_uint8 inp, mac_vap_stru *pst_vap, oal_uint16 us_idx)
{
     pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[us_idx].uc_dot11RSNAStatsSelectedPairwiseCipher = inp;;
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
void mac_mib_set_RSNAAuthenticationSuiteSelected(mac_vap_stru *pst_vap, oal_uint8 uc_inp)
{
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected = uc_inp;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
void mac_mib_set_RSNAPairwiseCipherSelected(mac_vap_stru *pst_vap, oal_uint8 uc_inp)
{
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherSelected = uc_inp;
}

void mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_inp, oal_uint8 uc_idx)
{
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_idx].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_TRUE;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_idx].uc_dot11RSNAConfigAuthenticationSuiteImplemented = uc_inp;
}

void mibset_RSNAClearWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap)
{
    oal_uint8 uc_index;

    for (uc_index = 0; uc_index < WLAN_PAIRWISE_CIPHER_SUITES; uc_index++)
    {
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = 0xFF;
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_FALSE;

    }
}


void mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value)
{
    oal_uint8 uc_index;

    if (WLAN_80211_CIPHER_SUITE_CCMP == uc_pairwise_value)
    {
        uc_index = 0;
    }
    else if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pairwise_value)
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_vap->uc_vap_id, "mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented pairwise_value[%d]: ERROR!", uc_pairwise_value);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented::invalid uc_pairwise_value[%d].}", uc_pairwise_value);

        return;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = uc_pairwise_value;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated = OAL_TRUE;
}


void mibset_RSNAClearWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap)
{
    oal_uint8 uc_index;

    for (uc_index = 0; uc_index < WLAN_PAIRWISE_CIPHER_SUITES; uc_index++)
    {
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = 0xFF;
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_FALSE;
    }
}


void mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value)
{
    oal_uint8 uc_index;

    if (WLAN_80211_CIPHER_SUITE_CCMP == uc_pairwise_value)
    {
        uc_index = 0;
    }
    else if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pairwise_value)
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_vap->uc_vap_id, "mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented pairwise_value[%d]: ERROR!", uc_pairwise_value);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented::invalid pairwise_value[%d].}", uc_pairwise_value);

        return;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = uc_pairwise_value;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_TRUE;
}
/*****************************************************************************
 函 数 名  : mac_vap_init_mib_11n
 功能描述  : 初始化11n的mib
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11n(mac_vap_stru  *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;
    mac_device_stru               *pst_dev;

    pst_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_dev)
    {
        MAC_WARNING_LOG(pst_mac_vap->uc_vap_id, "mac_vap_init_mib_11n: pst_dev is null ptr");
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_mib_11n::pst_dev null.}");

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;

    pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_FALSE;

    pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented         = OAL_FALSE;  //1131_debug  1131C不支持
    pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated           = OAL_FALSE;  /* 默认ldpc && stbc功能打开，用于STA的协议协商 */
    pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated               = HT_TX_STBC_DEFAULT_VALUE;
    /* pst_mib_info->st_phy_ht.en_dot11FortyMHzOperationImplemented        = OAL_FALSE; */
    pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented      = !pst_mac_vap->st_cap_flag.bit_disable_2ght40;
    pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented      = OAL_TRUE;

    /* SMPS特性宏不开启时默认均为POWER_SAVE_MIMO */
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave          = WLAN_MIB_MIMO_POWER_SAVE_MIMO;

    pst_mib_info->st_phy_ht.en_dot11HTGreenfieldOptionImplemented       = HT_GREEN_FILED_DEFAULT_VALUE;
    pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented    = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented   = !pst_mac_vap->st_cap_flag.bit_disable_2ght40;
    pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented   = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented             = pst_dev->bit_tx_stbc;
    pst_mib_info->st_phy_ht.en_dot11RxSTBCOptionImplemented             = (pst_dev->bit_rx_stbc == 0) ? OAL_FALSE : OAL_TRUE;
    pst_mib_info->st_phy_ht.ul_dot11NumberOfSpatialStreamsImplemented   = 2;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MaxAMSDULength         = 0;
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11LsigTxopProtectionOptionImplemented = OAL_FALSE;
#else
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11LsigTxopProtectionOptionImplemented = OAL_TRUE;
#endif

    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11MaxRxAMPDUFactor       = 3;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11MinimumMPDUStartSpacing= 5;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11PCOOptionImplemented   = OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11TransitionTime         = 3;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MCSFeedbackOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11HTControlFieldSupported= OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11RDResponderOptionImplemented = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_TXBF
    /* txbf能力信息 注:11n bfee能力目前全填0，日后增量实现针对华为设备开启,C01交付 */
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitStaggerSoundingOptionImplemented = pst_dev->bit_su_bfmer;
#else
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitStaggerSoundingOptionImplemented = 0;
#endif
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ReceiveStaggerSoundingOptionImplemented  = 0;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ReceiveNDPOptionImplemented      = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitNDPOptionImplemented       = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ImplicitTransmitBeamformingOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11CalibrationOptionImplemented      = 0;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ExplicitCSITransmitBeamformingOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ExplicitNonCompressedBeamformingMatrixOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitTransmitBeamformingCSIFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitNonCompressedBeamformingFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitCompressedBeamformingFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberBeamFormingCSISupportAntenna              = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberNonCompressedBeamformingMatrixSupportAntenna     = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberCompressedBeamformingMatrixSupportAntenna        = 0;

    /* 天线选择能力信息 */
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11AntennaSelectionOptionImplemented              = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitExplicitCSIFeedbackASOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitIndicesFeedbackASOptionImplemented     = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11ExplicitCSIFeedbackASOptionImplemented         = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitExplicitCSIFeedbackASOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11ReceiveAntennaSelectionOptionImplemented       = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitSoundingPPDUOptionImplemented          = 0;

    /* obss信息 */
    pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell                = 20;
    pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell                 = 10;
    pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval         = 300;
    pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel      = 200;
    pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel       = 20;
    pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor= 5;
    pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold           = 25;

    /*默认使用2040共存*/
     mac_mib_init_2040(pst_mac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
     /*1131debug: mac_vap_init_mib_11n  预留接口 */
     if (NULL != g_fn_mac_vap_init_mib_11n_adjust_patch_ram)
     {
        if (OAL_TRUE == g_fn_mac_vap_init_mib_11n_adjust_patch_ram(pst_mac_vap))
        {
            return;
        }
     }
#endif
}

/*****************************************************************************
 函 数 名  : mac_vap_init_11ac_mcs_singlenss
 功能描述  : 初始化11ac mib中mcs信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_11ac_mcs_singlenss(
                wlan_mib_ieee802dot11_stru          *pst_mib_info,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_tx_max_mcs_map_stru         *pst_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru         *pst_rx_max_mcs_map;

    /* 获取mib值指针 */
    pst_rx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap));
    pst_tx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap));

    /* 20MHz带宽的情况下，支持MCS0-MCS8 */
    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_20M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_20M_11AC;
    }

    /* 40MHz带宽的情况下，支持MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_40MINUS == en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_40M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_40M_11AC;
    }

    /* 80MHz带宽的情况下，支持MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_80MINUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80MINUSPLUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSPLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_80M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_80M_11AC;
    }
}

/*****************************************************************************
 函 数 名  : mac_vap_init_11ac_mcs_doublenss
 功能描述  : 初始化11ac mib中mcs信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_11ac_mcs_doublenss(
                wlan_mib_ieee802dot11_stru          *pst_mib_info,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_tx_max_mcs_map_stru         *pst_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru         *pst_rx_max_mcs_map;

    /* 获取mib值指针 */
    pst_rx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap));
    pst_tx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap));

    /* 20MHz带宽的情况下，支持MCS0-MCS8 */
    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_20M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_20M_11AC;
    }

    /* 40MHz带宽的情况下，支持MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_40MINUS == en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_40M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_40M_11AC;
    }

    /* 80MHz带宽的情况下，支持MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_80MINUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80MINUSPLUS== en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSMINUS== en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSPLUS== en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_80M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_80M_11AC;
    }

}

/*****************************************************************************
 函 数 名  : mac_vap_init_mib_11ac
 功能描述  : 初始化11ac mib信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11ac(mac_vap_stru  *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru      *pst_mib_info;
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_mib_11ac::pst_mac_dev[%d] null.}", pst_mac_vap->uc_device_id);

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_TRUE;

    pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11MaxMPDULength                      = WLAN_MIB_VHT_MPDU_11454;
    pst_mib_info->st_wlan_mib_phy_vht.uc_dot11VHTChannelWidthOptionImplemented          = WLAN_MIB_VHT_SUPP_WIDTH_80;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTLDPCCodingOptionImplemented            = pst_mac_dev->bit_ldpc_coding;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented           = OAL_TRUE;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn160and80p80Implemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTTxSTBCOptionImplemented                = pst_mac_dev->bit_tx_stbc;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTRxSTBCOptionImplemented                = (pst_mac_dev->bit_rx_stbc == 0) ? OAL_FALSE : OAL_TRUE;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTSUBeamformerOptionImplemented  = pst_mac_dev->bit_su_bfmer;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTSUBeamformeeOptionImplemented  = pst_mac_dev->bit_su_bfmee;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTNumberSoundingDimensions       = pst_mac_dev->uc_tx_chain - 1;
#else
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTNumberSoundingDimensions       = 0;
#endif
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTMUBeamformerOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTMUBeamformeeOptionImplemented  = pst_mac_dev->bit_mu_bfmee;
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTBeamformeeNTxSupport           = 1;
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_TRUE;
#endif
    pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTControlFieldSupported           = OAL_FALSE;
    pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTMaxRxAMPDUFactor                = 7;            /* 2^(13+1)-1字节 */
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented   = OAL_TRUE;
#endif
}
/*****************************************************************************
 函 数 名  : mac_vap_init_mib_11i
 功能描述  : 初始化11i mib信息
 输入参数  : pst_vap 指向VAP用户的指针
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11i(mac_vap_stru  *pst_vap)
{
    oal_uint8 uc_idx;

    /* 预备认证功能默认为FALSE，在RSN CAP检查时需要判断 */
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAPreauthenticationImplemented = OAL_FALSE;

    /* WEP、WAPI加密方式时、IBSS下需要去使能 */
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated                   = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR                        = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC                        = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated  = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked                  = OAL_FALSE;

    /* Version信息为1 */
    /* see <80211-2012> chapter 8.4.2.27 RSN elemet  */
    /* RSN Version 1 is defined in this standard */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigVersion = MAC_RSN_IE_VERSION;

    if (OAL_TRUE == pst_vap->st_cap_flag.bit_wpa2)
    {
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = WLAN_80211_CIPHER_SUITE_CCMP;
    }

    if(OAL_TRUE == pst_vap->st_cap_flag.bit_wpa)
    {
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = WLAN_80211_CIPHER_SUITE_TKIP;
    }

    if (WLAN_80211_CIPHER_SUITE_TKIP == pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher)
    {//WPA
        /* TKIP加密方式下GTK的bit位为256 */
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
    }
    else if(WLAN_80211_CIPHER_SUITE_CCMP == pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher)
    {//WPA2
        /* CCMP加密方式下GTK的bit位为256 */
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
    }

    /* 最终选择的AKM Suite类型, 初始化为PSK */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected   = WLAN_AUTH_SUITE_PSK;

    /* 最终选择的Pairwise Cipher类型, CCMP */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherSelected        = WLAN_80211_CIPHER_SUITE_CCMP;

    /* 最终选择的Group Cipher类型, 初始化为PSK */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherSelected = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteRequested  = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested       = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested          = 0;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNA4WayHandshakeFailures         = 0;

    /* wpa PairwiseCipher CCMP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherIndex            = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_CCMP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_CCMP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;


    /* wpa PairwiseCipher TKIP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherIndex            = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_TKIP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_TKIP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;

    /* wpa2 PairwiseCipher CCMP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherIndex            = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_CCMP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_CCMP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;


    /* wpa2 PairwiseCipher TKIP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherIndex            = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_TKIP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_TKIP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;

    /* AuthenticationSuite */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].ul_dot11RSNAConfigAuthenticationSuiteIndex       = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].uc_dot11RSNAConfigAuthenticationSuiteImplemented = WLAN_AUTH_SUITE_PSK;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].ul_dot11RSNAConfigAuthenticationSuiteIndex       = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].uc_dot11RSNAConfigAuthenticationSuiteImplemented = WLAN_AUTH_SUITE_PSK_SHA256;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;



    /* 初始化组播用户信息 */
    mac_vap_init_rsna_status(pst_vap, 0);
    oal_memset(pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[0].auc_dot11RSNAStatsSTAAddress, 0xFF, 6);
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[0].uc_dot11RSNAStatsSelectedPairwiseCipher = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = 0;

    /* 初始化单播用户信息 */
    for(uc_idx = 1; uc_idx < (WLAN_ASSOC_USER_MAX_NUM_LIMIT + 1); uc_idx++)
    {
        mac_vap_init_rsna_status(pst_vap, uc_idx);
    }

}

/*****************************************************************************
函 数 名  : mac_vap_init_legacy_rates
功能描述  : 初始化11a 11g速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_legacy_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    oal_uint8                      uc_curr_rate_index = 0;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* 初始化速率集 */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* 初始化速率个数，基本速率个数，非基本速率个数 */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11A;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11A;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11A;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 6;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 24;

    /* 将速率拷贝到VAP结构体下的速率集中 */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_curr_rate_index]);

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps == 6)
            || (puc_orig_rate->uc_mbps == 12)
            || (puc_orig_rate->uc_mbps == 24))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            puc_curr_rate->uc_mac_rate |= 0x80;
            uc_curr_rate_index++;
        }

        /* Non-basic rates */
        else if ((puc_orig_rate->uc_mbps== 9)
                || (puc_orig_rate->uc_mbps == 18)
                || (puc_orig_rate->uc_mbps == 36)
                || (puc_orig_rate->uc_mbps == 48)
                || (puc_orig_rate->uc_mbps == 54))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            uc_curr_rate_index++;
        }

        if (uc_curr_rate_index == pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates)
        {
            break;
        }
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_11b_rates
功能描述  : 初始化11b速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11b_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    oal_uint8                      uc_curr_rate_index = 0;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* 初始化速率集 */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* 初始化速率个数，基本速率个数，非基本速率个数 */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11B;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = 0;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11B;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 2;

    /* 将速率拷贝到VAP结构体下的速率集中 */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_curr_rate_index]);

        /*  Basic Rates  */
        if ((puc_orig_rate->uc_mbps == 1) || (puc_orig_rate->uc_mbps == 2)
           || ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && ((puc_orig_rate->uc_mbps == 5) || (puc_orig_rate->uc_mbps == 11))))
        {
            pst_vap->st_curr_sup_rates.uc_br_rate_num++;
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            puc_curr_rate->uc_mac_rate |= 0x80;
            uc_curr_rate_index++;
        }

        /* Non-basic rates */
        else if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode)
                && ((puc_orig_rate->uc_mbps == 5) || (puc_orig_rate->uc_mbps == 11)))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            uc_curr_rate_index++;
        }
        else
        {
            continue;
        }

        if (uc_curr_rate_index == pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates)
        {
            break;
        }
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_11g_mixed_one_rates
功能描述  : 初始化11b速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11g_mixed_one_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* 初始化速率集 */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* 初始化速率个数，基本速率个数，非基本速率个数 */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11G_MIXED;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11G_MIXED_ONE;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11G_MIXED_ONE;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 11;

    /* 将速率拷贝到VAP结构体下的速率集中 */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_rate_index]);

        oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps== 1)
            || (puc_orig_rate->uc_mbps == 2)
            || (puc_orig_rate->uc_mbps == 5)
            || (puc_orig_rate->uc_mbps == 11))
        {
            puc_curr_rate->uc_mac_rate |= 0x80;
        }
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_11g_mixed_two_rates
功能描述  : 初始化11g mixed two速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11g_mixed_two_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* 初始化速率集 */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* 初始化速率个数，基本速率个数，非基本速率个数 */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11G_MIXED;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11G_MIXED_TWO;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11G_MIXED_TWO;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 24;

    /* 将速率拷贝到VAP结构体下的速率集中 */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_rate_index]);

        oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps== 1)
            || (puc_orig_rate->uc_mbps == 2)
            || (puc_orig_rate->uc_mbps == 5)
            || (puc_orig_rate->uc_mbps == 11)
            || (puc_orig_rate->uc_mbps == 6)
            || (puc_orig_rate->uc_mbps == 12)
            || (puc_orig_rate->uc_mbps == 24))
        {
            puc_curr_rate->uc_mac_rate |= 0x80;
        }
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_11n_rates
功能描述  : 初始化11n速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11n_rates(mac_vap_stru *pst_mac_vap,mac_device_stru *pst_mac_dev)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;
    /* 初始化速率集 */

    /* MCS相关MIB值初始化 */
    pst_mib_info->st_phy_ht.en_dot11TxMCSSetDefined              = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot11TxRxMCSSetNotEqual           = OAL_FALSE;
    pst_mib_info->st_phy_ht.en_dot11TxUnequalModulationSupported = OAL_FALSE;

    /* 将MIB值的MCS MAP清零 */
    OAL_MEMZERO(pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue, WLAN_HT_MCS_BITMASK_LEN);

    /* 1个空间流 */
    if (WLAN_SINGLE_NSS == pst_mac_dev->en_nss_num)
    {
        pst_mib_info->st_phy_ht.ul_dot11TxMaximumNumberSpatialStreamsSupported = 1;
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[0] = 0xFF; /* 支持 RX MCS 0-7，8位全置为1*/
        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[0] = 0xFF; /* 支持 TX MCS 0-7，8位全置为1*/

        pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_SINGLE_NSS_20M_11N;

        if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
        {
            /* 40M 支持MCS32 */
            pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[4] = (oal_uint8)0x01;  /* 支持 RX MCS 32,最后一位为1 */
            pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[4] = (oal_uint8)0x01;  /* 支持 RX MCS 32,最后一位为1 */
            pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_SINGLE_NSS_40M_11N;
        }
    }

    /* 2个空间流 */
    else if (WLAN_DOUBLE_NSS == pst_mac_dev->en_nss_num)
    {
        pst_mib_info->st_phy_ht.ul_dot11TxMaximumNumberSpatialStreamsSupported = 2;
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[0] = 0xFF;  /* 支持 RX MCS 0-7，8位全置为1*/
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[1] = 0xFF;  /* 支持 RX MCS 8-15，8位全置为1*/

        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[0] = 0xFF;  /* 支持 TX MCS 0-7，8位全置为1*/
        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[1] = 0xFF;  /* 支持 TX MCS 8-15，8位全置为1*/

        pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_DOUBLE_NSS_20M_11N;

        if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
        {
            /* 40M 支持的最大速率为300M */
            pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[4] = (oal_uint8)0x01;  /* 支持 RX MCS 32,最后一位为1 */
            pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[4] = (oal_uint8)0x01;  /* 支持 RX MCS 32,最后一位为1 */
            pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_DOUBLE_NSS_40M_11N;
        }
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_11ac_rates
功能描述  : 初始化11n速率
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11ac_rates(mac_vap_stru *pst_mac_vap,mac_device_stru *pst_mac_dev)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;

    /* 先将TX RX MCSMAP初始化为所有空间流都不支持 0xFFFF*/
    pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap = 0xFFFF;
    pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap = 0xFFFF;

    if (WLAN_SINGLE_NSS == pst_mac_dev->en_nss_num)
    {
        /* 1个空间流的情况 */
        mac_vap_init_11ac_mcs_singlenss(pst_mib_info, pst_mac_vap->st_channel.en_bandwidth);
    }
    else if (WLAN_DOUBLE_NSS == pst_mac_dev->en_nss_num)
    {
        /* 2个空间流的情况 */
        mac_vap_init_11ac_mcs_doublenss(pst_mib_info, pst_mac_vap->st_channel.en_bandwidth);
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_11ac_rates::invalid en_nss_num[%d].}", pst_mac_dev->en_nss_num);
    }
}

/*****************************************************************************
 函 数 名  : mac_vap_init_p2p_rates
 功能描述  : 初始化p2p vap的速率集
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_init_p2p_rates(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru  *pst_rates)
{
    mac_device_stru               *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_p2p_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }

    mac_vap_init_legacy_rates(pst_vap, pst_rates);

    /* begin: 1102 在listen channel的probe respons 携带速率集有重复IE.  */
#ifdef _PRE_WLAN_FEATURE_5G
    oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_5G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));
#endif /* _PRE_WLAN_FEATURE_5G */
    oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_2G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));
    /* end: 1102 在listen channel的probe respons 携带速率集有重复IE.  */

    if (WLAN_VHT_MODE == en_vap_protocol)
    {
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else
    {
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
    }
}

oal_void mac_vap_init_rates_by_protocol(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru *pst_rates)
{
    mac_device_stru *pst_mac_dev;

    pst_mac_dev = (mac_device_stru *)mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates_by_protocol::mac_res_get_dev fail.device_id:[%d].}", pst_vap->uc_device_id);
        return;
    }

    /* STA模式默认协议模式是11ac，初始化速率集为所有速率集 */
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(pst_vap))
    {
        mac_vap_init_p2p_rates(pst_vap, en_vap_protocol, pst_rates);
        return;
    }
#endif
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode && WLAN_VHT_MODE == en_vap_protocol)
    {
        /* 用于STA全信道扫描 5G时 填写支持速率集ie */
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
    #ifdef _PRE_WLAN_FEATURE_5G
        oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_5G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));
    #endif /* _PRE_WLAN_FEATURE_5G */

        /* 用于STA全信道扫描 2G时 填写支持速率集ie */
        mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_2G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));

        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_VHT_ONLY_MODE == en_vap_protocol) || (WLAN_VHT_MODE == en_vap_protocol))
    {
#ifdef _PRE_WLAN_FEATURE_11AC2G
        if (WLAN_BAND_2G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        }
        else
        {
            mac_vap_init_legacy_rates(pst_vap, pst_rates);
        }
#else
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
#endif
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_HT_ONLY_MODE == en_vap_protocol) || (WLAN_HT_MODE == en_vap_protocol))
    {
        if (WLAN_BAND_2G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        }
    #ifdef _PRE_WLAN_FEATURE_5G
        else if (WLAN_BAND_5G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_legacy_rates(pst_vap, pst_rates);
        }
    #endif /* _PRE_WLAN_FEATURE_5G */

        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_LEGACY_11A_MODE == en_vap_protocol) || (WLAN_LEGACY_11G_MODE == en_vap_protocol))
    {
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
    }
    else if (WLAN_LEGACY_11B_MODE == en_vap_protocol)
    {
        mac_vap_init_11b_rates(pst_vap, pst_rates);
    }
    else if (WLAN_MIXED_ONE_11G_MODE == en_vap_protocol)
    {
        mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
    }
    else if (WLAN_MIXED_TWO_11G_MODE == en_vap_protocol)
    {
        mac_vap_init_11g_mixed_two_rates(pst_vap, pst_rates);
    }
    else
    {
        /* 暂时不处理 */
    }
}

/*****************************************************************************
函 数 名  : mac_vap_init_rates
功能描述  : 初始化速率集
输入参数  :
输出参数  :
返 回 值  : 错误码
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年7月30日
   作    者   : 
   修改内容   : 新生成函数
 2.日    期   : 2013年11月6日
   作    者   :  
   修改内容   : 修改不同协议模式速率初始化

*****************************************************************************/
oal_void mac_vap_init_rates(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_mac_dev;
    wlan_protocol_enum_uint8       en_vap_protocol;
    mac_data_rate_stru            *pst_rates;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }

    /* 初始化速率集 */
    pst_rates   = mac_device_get_all_rates(pst_mac_dev);

    en_vap_protocol = pst_vap->en_protocol;

    mac_vap_init_rates_by_protocol(pst_vap, en_vap_protocol, pst_rates);

}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
函 数 名  : mac_sta_init_bss_rates
功能描述  : STA初始化速率集
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2015年5月30日
   作    者   : 
   修改内容   : 新生成函数
*****************************************************************************/
oal_void mac_sta_init_bss_rates(mac_vap_stru *pst_vap, oal_void *pst_bss_dscr)
{
    mac_device_stru               *pst_mac_dev;
    wlan_protocol_enum_uint8       en_vap_protocol;
    mac_data_rate_stru            *pst_rates;
    oal_uint32                     i,j;
    mac_bss_dscr_stru             *pst_bss = (mac_bss_dscr_stru *)pst_bss_dscr;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }


    /* 初始化速率集 */
    pst_rates   = mac_device_get_all_rates(pst_mac_dev);
    if(OAL_PTR_NULL != pst_bss)
    {
        for(i = 0; i < pst_bss->uc_num_supp_rates; i++)
        {
            for(j = 0; j < MAC_DATARATES_PHY_80211G_NUM; j++)
            {
                if((pst_rates[j].uc_mac_rate & 0x7f) == (pst_bss->auc_supp_rates[i] & 0x7f))
                {
                    pst_rates[j].uc_mac_rate = pst_bss->auc_supp_rates[i];
                    break;
                }
            }
        }
    }

    en_vap_protocol = pst_vap->en_protocol;

    mac_vap_init_rates_by_protocol(pst_vap, en_vap_protocol, pst_rates);
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

#if 0
#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 函 数 名  : mac_vap_dft_stat_init
 功能描述  : 初始化vap吞吐统计的资源
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  mac_vap_dft_stat_init(mac_vap_stru *pst_vap)
{
    OAL_MEMZERO(&pst_vap->st_vap_dft, OAL_SIZEOF(mac_vap_dft_stru));

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : mac_vap_dft_stat_clear
 功能描述  : 清楚vap吞吐统计资源
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_dft_stat_clear(mac_vap_stru *pst_vap)
{
    pst_vap->st_vap_dft.ul_flg = 0;

    if (OAL_TRUE == pst_vap->st_vap_dft.st_vap_dft_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_vap->st_vap_dft.st_vap_dft_timer);
    }

    if (OAL_PTR_NULL != pst_vap->st_vap_dft.pst_vap_dft_stats)
    {
        OAL_MEM_FREE(pst_vap->st_vap_dft.pst_vap_dft_stats, OAL_TRUE);
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : mac_vap_set_tx_power
 功能描述  : 设置vap的发送功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_tx_power(mac_vap_stru *pst_vap, oal_uint8 uc_tx_power)
{
    pst_vap->uc_tx_power = uc_tx_power;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_aid
 功能描述  : 设置vap的aid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_aid(mac_vap_stru *pst_vap, oal_uint16 us_aid)
{
    pst_vap->us_sta_aid = us_aid;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_assoc_id
 功能描述  : 设置vap的assoc_vap_id 该参数只在STA有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_assoc_id(mac_vap_stru *pst_vap, oal_uint8 uc_assoc_vap_id)
{
    pst_vap->uc_assoc_vap_id = uc_assoc_vap_id;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_uapsd_cap
 功能描述  : 设置vap的assoc_vap_id 该参数只在STA有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_uapsd_cap(mac_vap_stru *pst_vap, oal_uint8 uc_uapsd_cap)
{
    pst_vap->uc_uapsd_cap = uc_uapsd_cap;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_p2p_mode
 功能描述  : 设置vap的p2p模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_p2p_mode(mac_vap_stru *pst_vap, wlan_p2p_mode_enum_uint8 en_p2p_mode)
{
    pst_vap->en_p2p_mode = en_p2p_mode;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_multi_user_idx
 功能描述  : 设置vap的组播用户id
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_multi_user_idx(mac_vap_stru *pst_vap, oal_uint16 us_multi_user_idx)
{
    pst_vap->us_multi_user_idx = us_multi_user_idx;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_rx_nss
 功能描述  : 设置vap的接收nss
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_rx_nss(mac_vap_stru *pst_vap, oal_uint8 uc_rx_nss)
{
    pst_vap->en_vap_rx_nss = uc_rx_nss;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_al_tx_payload_flag
 功能描述  : 设置vap的常发payload长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_al_tx_payload_flag(mac_vap_stru *pst_vap, oal_uint8 uc_paylod)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_payload_flag = uc_paylod;
#endif
}

/*****************************************************************************
 函 数 名  : mac_vap_set_al_tx_flag
 功能描述  : 设置vap的常发模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_al_tx_flag(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_al_tx_flag = en_flag;
#endif
}

/*****************************************************************************
 函 数 名  : mac_set_al_tx_first_run
 功能描述  : 设置vap的常发模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_al_tx_first_run(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_first_run = en_flag;
#endif
}

#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 函 数 名  : mac_vap_set_uapsd_para
 功能描述  : 设置vap的uapsd参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_uapsd_para(mac_vap_stru *pst_mac_vap, mac_cfg_uapsd_sta_stru *pst_uapsd_info)
{
    oal_uint8                 uc_ac;

    pst_mac_vap->st_sta_uapsd_cfg.uc_max_sp_len = pst_uapsd_info->uc_max_sp_len;

    for (uc_ac = 0; uc_ac < WLAN_WME_AC_BUTT; uc_ac++)
    {
        pst_mac_vap->st_sta_uapsd_cfg.uc_delivery_enabled[uc_ac] = pst_uapsd_info->uc_delivery_enabled[uc_ac];
        pst_mac_vap->st_sta_uapsd_cfg.uc_trigger_enabled[uc_ac]  = pst_uapsd_info->uc_trigger_enabled[uc_ac];
    }

}
#endif

/*****************************************************************************
 函 数 名  : mac_vap_set_wmm_params_update_count
 功能描述  : 设置vap的wmm update count
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_wmm_params_update_count(mac_vap_stru *pst_vap, oal_uint8 uc_update_count)
{
    pst_vap->uc_wmm_params_update_count = uc_update_count;
}
#if 0
/*****************************************************************************
 函 数 名  : mac_vap_set_rifs_tx_on
 功能描述  : 设置vap的wmm update count
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_rifs_tx_on(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_rifs_tx_on = uc_value;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_tdls_prohibited
 功能描述  : 设置vap的tdls_prohibited
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_tdls_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_tdls_prohibited = uc_value;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_tdls_channel_switch_prohibited
 功能描述  : 设置vap的tdls_channel_switch_prohibited
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_tdls_channel_switch_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_tdls_channel_switch_prohibited = uc_value;
}
#endif

/*****************************************************************************
 函 数 名  : mac_vap_set_11ac2g
 功能描述  : 设置vap的11ac2g
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_11ac2g(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_11ac2g = uc_value;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_hide_ssid
 功能描述  : 设置vap的hide ssid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_vap_set_hide_ssid(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_hide_ssid = uc_value;
}

/*****************************************************************************
 函 数 名  : mac_get_p2p_mode
 功能描述  : 获取Vap的P2P模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : mac_vap_stru *pst_vap
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
wlan_p2p_mode_enum_uint8  mac_get_p2p_mode(mac_vap_stru *pst_vap)
{
    return (pst_vap->en_p2p_mode);
}


/*****************************************************************************
 函 数 名  : mac_p2p_dec_num
 功能描述  : 删除P2P vap num的功能函数
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月22日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_dec_p2p_num(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_device;

    pst_device     = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_p2p_dec_num::pst_device[%d] null.}", pst_vap->uc_device_id);
        return;
    }

    if (IS_P2P_DEV(pst_vap))
    {
        pst_device->st_p2p_info.uc_p2p_device_num--;
    }
    else if (IS_P2P_GO(pst_vap) || IS_P2P_CL(pst_vap))
    {
        pst_device->st_p2p_info.uc_p2p_goclient_num--;
    }
}
/*****************************************************************************
 函 数 名  : mac_inc_p2p_num
 功能描述  : add p2p vap时同步增加p2p设备的计数器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_inc_p2p_num(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_dev;

    pst_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_inc_p2p_num::pst_dev[%d] null.}", pst_vap->uc_device_id);
        return;
    }

    if (IS_P2P_DEV(pst_vap))
    {
        /* device下sta个数加1 */
        pst_dev->st_p2p_info.uc_p2p_device_num++;
    }
    else if (IS_P2P_GO(pst_vap))
    {
        pst_dev->st_p2p_info.uc_p2p_goclient_num++;
    }
    else if (IS_P2P_CL(pst_vap))
    {
        pst_dev->st_p2p_info.uc_p2p_goclient_num++;
    }
}

/*****************************************************************************
函 数 名  : mac_vap_save_app_ie
功能描述  : 将用户态 IE 信息拷贝到内核态中
输入参数  : mac_vap_stru *pst_mac_vap
          oal_net_dev_ioctl_data_stru *pst_ioctl_data
          enum WPS_IE_TYPE en_type
输出参数  : 无
返 回 值  : OAL_STATIC oal_uint8*
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2015年4月28日
  作    者   : 
  修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_save_app_ie(mac_vap_stru *pst_mac_vap, oal_app_ie_stru *pst_app_ie, en_app_ie_type_uint8 en_type)
{
    oal_uint8           *puc_ie = OAL_PTR_NULL;
    oal_uint32           ul_ie_len;
    oal_app_ie_stru      st_tmp_app_ie;

    OAL_MEMZERO(&st_tmp_app_ie, OAL_SIZEOF(oal_app_ie_stru));

    if (en_type >= OAL_APP_IE_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_save_app_ie::invalid en_type[%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    ul_ie_len = pst_app_ie->ul_ie_len;

    /* 如果输入WPS 长度为0， 则直接释放VAP 中资源 */
    if (0 == ul_ie_len)
    {
        if (OAL_PTR_NULL != pst_mac_vap->ast_app_ie[en_type].puc_ie)
        {
            OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);
        }

        pst_mac_vap->ast_app_ie[en_type].puc_ie         = OAL_PTR_NULL;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_len      = 0;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len  = 0;

        return OAL_SUCC;
    }

    /* 检查该类型的IE是否需要申请内存 */
    if ((pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len < ul_ie_len) || (NULL == pst_mac_vap->ast_app_ie[en_type].puc_ie))
    {
        /* 这种情况不应该出现，维测需要 */
        if (NULL == pst_mac_vap->ast_app_ie[en_type].puc_ie && pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len != 0  )
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_app_ie::invalid len[%d].}",
                          pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len);
        }

        /* 如果以前的内存空间小于新信息元素需要的长度，则需要重新申请内存 */
        puc_ie = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(ul_ie_len), OAL_TRUE);
        if (OAL_PTR_NULL == puc_ie)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_app_ie::LOCAL_MEM_POOL is empty!,len[%d], en_type[%d].}",
                              pst_app_ie->ul_ie_len, en_type);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);

        pst_mac_vap->ast_app_ie[en_type].puc_ie = puc_ie;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len = ul_ie_len;
    }

    oal_memcopy((oal_void*)pst_mac_vap->ast_app_ie[en_type].puc_ie, (oal_void*)pst_app_ie->auc_ie, ul_ie_len);
    pst_mac_vap->ast_app_ie[en_type].ul_ie_len = ul_ie_len;

    return OAL_SUCC;
}
 /*****************************************************************************
 函 数 名  : mac_vap_clear_app_ie
 功能描述  : 清除保存的ie
 输入参数  : mac_vap_stru *pst_mac_vap
           enum WPS_IE_TYPE en_type
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint8*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年4月28日
  作    者   : 
  修改内容   : 新生成函数

 *****************************************************************************/
 oal_uint32 mac_vap_clear_app_ie(mac_vap_stru *pst_mac_vap, en_app_ie_type_uint8 en_type)
 {
     if (en_type < OAL_APP_IE_NUM)
     {
         if (OAL_PTR_NULL != pst_mac_vap->ast_app_ie[en_type].puc_ie)
         {
             OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);
             pst_mac_vap->ast_app_ie[en_type].puc_ie    = OAL_PTR_NULL;
         }
         pst_mac_vap->ast_app_ie[en_type].ul_ie_len     = 0;
         pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len = 0;
     }

     return OAL_SUCC;
 }

 oal_void mac_vap_free_mib(mac_vap_stru   *pst_vap)
{
    if(NULL == pst_vap)
        return;

    if (OAL_PTR_NULL != pst_vap->pst_mib_info)
    {
        wlan_mib_ieee802dot11_stru  *pst_mib_info = pst_vap->pst_mib_info;
        /*先置空再释放*/
        pst_vap->pst_mib_info = OAL_PTR_NULL;
        OAL_MEM_FREE(pst_mib_info, OAL_TRUE);
    }
}

 /*****************************************************************************
 函 数 名  : mac_vap_exit
 功能描述  : mac vap exit
 输入参数  :
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_exit(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_device;
    oal_uint8                      uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_exit::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->uc_init_flag = MAC_VAP_INVAILD;

    /* 释放与hmac有关的内存 */
    mac_vap_free_mib(pst_vap);

    /* 释放WPS信息元素内存 */
    for (uc_index = 0; uc_index < OAL_APP_IE_NUM; uc_index++)
    {
        mac_vap_clear_app_ie(pst_vap, uc_index);
    }

    /* 业务vap已删除，从device上去掉 */
    pst_device     = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_exit::pst_device[%d] null.}", pst_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 业务vap已经删除，从device中去掉 */
    for (uc_index = 0; uc_index < pst_device->uc_vap_num; uc_index++)
    {
        /* 从device中找到vap id */
        if (pst_device->auc_vap_id[uc_index] == pst_vap->uc_vap_id)
        {
            /* 如果不是最后一个vap，则把最后一个vap id移动到这个位置，使得该数组是紧凑的 */
            if(uc_index < (pst_device->uc_vap_num - 1))
            {
                pst_device->auc_vap_id[uc_index] = pst_device->auc_vap_id[pst_device->uc_vap_num - 1];
                break;
            }
        }
    }

    /* device下的vap总数减1 */
    pst_device->uc_vap_num--;
    /* 清除数组中已删除的vap id，保证非零数组元素均为未删除vap */
    pst_device->auc_vap_id[pst_device->uc_vap_num] = 0;

    /* device下sta个数减1 */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        pst_device->uc_sta_num--;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
        {
            if ((OAL_TRUE == pst_vap->st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_vap->st_vap_proxysta.en_is_main_proxysta))
            {
                pst_device->uc_proxysta_num--;
            }
        }
#endif

    }
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_dec_p2p_num(pst_vap);
#endif

    pst_vap->en_protocol  = WLAN_PROTOCOL_BUTT;

    /* 最后1个vap删除时，清除device级带宽信息 */
    if (0 == pst_device->uc_vap_num)
    {
        pst_device->uc_max_channel   = 0;
        pst_device->en_max_band      = WLAN_BAND_BUTT;
        pst_device->en_max_bandwidth = WLAN_BAND_WIDTH_BUTT;
    }

    /* 删除之后将vap的状态置位非法 */
    mac_vap_state_change(pst_vap, MAC_VAP_STATE_BUTT);

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : mac_init_mib
 功能描述  : mib初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月29日
    作    者   : 
    修改内容   : 新生成函数

  2.日    期   : 2013年11月6日
    作    者   :  
    修改内容   : 增加HT only和VHT only协议模式的初始化

*****************************************************************************/
OAL_STATIC oal_void  mac_init_mib(mac_vap_stru *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru *pst_mib_info;
    oal_uint8 uc_idx;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_init_mib::pst_mac_vap null.}");

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;

    /* 公共特性mib值初始化 */
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod             = WLAN_DTIM_DEFAULT;
    pst_mib_info->st_wlan_mib_operation.ul_dot11RTSThreshold            = WLAN_RTS_MAX;
    pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold  = WLAN_FRAG_THRESHOLD_MAX;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType         = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod           = WLAN_BEACON_INTVAL_DEFAULT;


    mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
    pst_mib_info->st_phy_hrdsss.en_dot11PBCCOptionImplemented           = OAL_FALSE;
    pst_mib_info->st_phy_hrdsss.en_dot11ChannelAgilityPresent           = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11MultiDomainCapabilityActivated = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementRequired = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11ExtendedChannelSwitchActivated = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented   = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11APSDOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11QBSSLoadImplemented    = OAL_TRUE;
    pst_mib_info->st_phy_erp.en_dot11ShortSlotTimeOptionImplemented     = OAL_TRUE;
    pst_mib_info->st_phy_erp.en_dot11ShortSlotTimeOptionActivated       = OAL_TRUE; //11g 性能问题 
    pst_mib_info->st_wlan_mib_sta_config.en_dot11RadioMeasurementActivated = OAL_FALSE;


    pst_mib_info->st_phy_erp.en_dot11DSSSOFDMOptionActivated            = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11ImmediateBlockAckOptionImplemented = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11DelayedBlockAckOptionImplemented   = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut = WLAN_AUTH_TIMEOUT;

    mac_mib_set_HtProtection(pst_mac_vap, WLAN_MIB_HT_NO_PROTECTION);
    mac_mib_set_RifsMode(pst_mac_vap, OAL_TRUE);
    mac_mib_set_NonGFEntitiesPresent(pst_mac_vap, OAL_FALSE);
    mac_mib_set_LsigTxopFullProtectionActivated(pst_mac_vap, OAL_TRUE);

    pst_mib_info->st_wlan_mib_operation.en_dot11DualCTSProtection       = OAL_FALSE;
    pst_mib_info->st_wlan_mib_operation.en_dot11PCOActivated            = OAL_FALSE;

    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationResponseTimeOut = WLAN_ASSOC_TIMEOUT;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout = WLAN_SA_QUERY_RETRY_TIME;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout   = WLAN_SA_QUERY_MAXIMUM_TIME;

    /* 认证算法表初始化 */
    pst_mib_info->st_wlan_mib_auth_alg.uc_dot11AuthenticationAlgorithm = WLAN_WITP_AUTH_OPEN_SYSTEM;
    pst_mib_info->st_wlan_mib_auth_alg.en_dot11AuthenticationAlgorithmsActivated = OAL_FALSE;

    /* WEP 缺省Key表初始化 */
    for(uc_idx = 0; uc_idx < WLAN_NUM_DOT11WEPDEFAULTKEYVALUE; uc_idx++)
    {
        oal_memset(pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue, 0, WLAN_MAX_WEP_STR_SIZE);
        /* 大小初始化为 WEP-40  */
        pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = 40;
    }

    /*   WEP Kep 映射表初始化    */
    oal_memset(pst_mib_info->st_wlan_mib_wep_key_map.auc_dot11WEPKeyMappingValue,
           0, WLAN_MAX_WEP_STR_SIZE);
    oal_memset(pst_mib_info->st_wlan_mib_wep_key_map.auc_dot11WEPKeyMappingAddress, 0,
           WLAN_MAC_ADDR_LEN);
    pst_mib_info->st_wlan_mib_wep_key_map.en_dot11WEPKeyMappingWEPOn = OAL_FALSE;

    /*    相关私有表初始化  */
    pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked                 = OAL_FALSE;
    pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID                = 0;
    pst_mib_info->st_wlan_mib_privacy.en_dot11ExcludeUnencrypted             = OAL_TRUE;
    pst_mib_info->st_wlan_mib_privacy.ul_dot11WEPICVErrorCount               = 0;
    pst_mib_info->st_wlan_mib_privacy.ul_dot11WEPExcludedCount               = 0;

    /* 更新wmm参数初始值 */
    mac_vap_init_wme_param(pst_mac_vap);

    /* 11i */
    mac_vap_init_mib_11i(pst_mac_vap);

    /* 默认11n 11ac使能关闭，配置协议模式时打开 */
    mac_vap_init_mib_11n(pst_mac_vap);
    mac_vap_init_mib_11ac(pst_mac_vap);

    /* staut低功耗mib项初始化 */
    pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode = WLAN_MIB_PWR_MGMT_MODE_ACTIVE;

}

/*****************************************************************************
 函 数 名  : mac_vap_cap_init_legacy
 功能描述  : legacy协议初始化vap能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_cap_init_legacy(mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->st_cap_flag.bit_rifs_tx_on = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_smps       = WLAN_MIB_MIMO_POWER_SAVE_MIMO;
    return;
}

/*****************************************************************************
 函 数 名  : mac_vap_cap_init_htvht
 功能描述  : ht vht协议初始化vap能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  mac_vap_cap_init_htvht(mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->st_cap_flag.bit_rifs_tx_on = OAL_FALSE;

#ifdef _PRE_WLAN_FEATURE_TXOPPS
    if(OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {   /* 规避死机*/
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_cap_init_htvht::pst_mib_info null,vap mode[%d] state[%d] user num[%d].}",
                                     pst_mac_vap->en_vap_mode ,pst_mac_vap->en_vap_state, pst_mac_vap->us_user_nums);
        return OAL_FAIL;
    }
    if (pst_mac_vap->en_protocol == WLAN_VHT_MODE ||
         pst_mac_vap->en_protocol == WLAN_VHT_ONLY_MODE)
    {
        pst_mac_vap->st_cap_flag.bit_txop_ps   = OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_FALSE;
        pst_mac_vap->st_cap_flag.bit_txop_ps    = OAL_FALSE;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    pst_mac_vap->st_cap_flag.bit_smps = mac_mib_get_smps(pst_mac_vap);
#else
    pst_mac_vap->st_cap_flag.bit_smps = WLAN_MIB_MIMO_POWER_SAVE_MIMO;
#endif

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_vap_config_vht_ht_mib_by_protocol
 功能描述  : 依据VAP 协议模式，初始化vap HT/VHT 相应 MIB 能力
 输入参数  : pst_mac_vap: 指向vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
//TODO
oal_uint32 mac_vap_config_vht_ht_mib_by_protocol(mac_vap_stru *pst_mac_vap)
{

    if(OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {   /* 规避死机*/
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_config_vht_ht_mib_by_protocol::pst_mib_info null,vap mode[%d] state[%d] user num[%d].}",
                                     pst_mac_vap->en_vap_mode ,pst_mac_vap->en_vap_state, pst_mac_vap->us_user_nums);
        return OAL_FAIL;
    }
    /* 根据协议模式更新 HT/VHT mib值 */
    if (WLAN_HT_MODE == pst_mac_vap->en_protocol || WLAN_HT_ONLY_MODE == pst_mac_vap->en_protocol)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_TRUE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_FALSE;
    }
    else if (WLAN_VHT_MODE == pst_mac_vap->en_protocol || WLAN_VHT_ONLY_MODE == pst_mac_vap->en_protocol)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_TRUE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_FALSE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_init_rx_nss_by_protocol
 功能描述  : 初始化rx nss
 输入参数  : pst_mac_vap: 指向vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月27日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_init_rx_nss_by_protocol(mac_vap_stru *pst_mac_vap)
{
    wlan_protocol_enum_uint8 en_protocol;
    mac_device_stru         *pst_mac_device;

    en_protocol   = pst_mac_vap->en_protocol;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init_rx_nss_by_protocol::pst_mac_device[%d] null.}", pst_mac_vap->uc_device_id);
        return;
    }

    switch(en_protocol)
    {
        case WLAN_HT_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
        case WLAN_HT_11G_MODE:
             pst_mac_vap->en_vap_rx_nss  = WLAN_DOUBLE_NSS;
             break;
        case WLAN_PROTOCOL_BUTT:
             pst_mac_vap->en_vap_rx_nss  = WLAN_NSS_BUTT;
             return;

        default:
             pst_mac_vap->en_vap_rx_nss  = WLAN_SINGLE_NSS;
             break;
    }

    pst_mac_vap->en_vap_rx_nss = OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_mac_device->en_nss_num);
}

/*****************************************************************************
 函 数 名  : mac_vap_init_by_protocol
 功能描述  : 依据协议初始化vap相应能力
 输入参数  : pst_mac_vap: 指向vap
             en_protocol: 协议枚举
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_init_by_protocol(mac_vap_stru *pst_mac_vap, wlan_protocol_enum_uint8 en_protocol)
{
    pst_mac_vap->en_protocol          = en_protocol;

    if (en_protocol < WLAN_HT_MODE)
    {
        mac_vap_cap_init_legacy(pst_mac_vap);
    }
    else
    {
        if(OAL_SUCC != mac_vap_cap_init_htvht(pst_mac_vap))
        {
            return OAL_FAIL;
        }
    }

    /* 根据协议模式更新mib值 */
    if(OAL_SUCC != mac_vap_config_vht_ht_mib_by_protocol(pst_mac_vap))
    {
        return OAL_FAIL;
    }

    /* 根据协议更新初始化空间流个数 */
    mac_vap_init_rx_nss_by_protocol(pst_mac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_change_mib_by_bandwidth
 功能描述  : 根据带宽更改vap的mib值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_change_mib_by_bandwidth(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    wlan_mib_ieee802dot11_stru *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;

    if (OAL_PTR_NULL == pst_mib_info)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_change_mib_by_bandwidth::pst_mib_info null.}");

        return;
    }

    /* 更新40M使能mib, 默认使能 */
    mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_TRUE);

    /* 更新short gi使能mib, 默认全使能，根据带宽信息更新 */
    pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented           = OAL_TRUE;
    mac_mib_set_ShortGIOptionInFortyImplemented(pst_mac_vap, OAL_TRUE);
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_TRUE;

    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_FALSE);
        mac_mib_set_ShortGIOptionInFortyImplemented(pst_mac_vap, OAL_FALSE);
        pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_FALSE;
    }
    else if (WLAN_BAND_WIDTH_20M < en_bandwidth && en_bandwidth < WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_FALSE;
    }


}


#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
/*****************************************************************************
 函 数 名  : hmac_proxy_init_vap
 功能描述  : 初始化proxy特性所需要的结构
 输入参数  : pst_mac_vap: mac_vap指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_err_code_enum_uint32 mac_proxy_init_vap(mac_vap_stru  *pst_mac_vap)
{
    pst_mac_vap->pst_vap_proxyarp = OAL_PTR_NULL;
    return OAL_SUCC;
}
#endif


/*****************************************************************************
 函 数 名  : mac_vap_init
 功能描述  : mac vap init
 输入参数  :
 输出参数  :
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_init(
                mac_vap_stru               *pst_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param)
{
    oal_uint32                     ul_loop;
    wlan_mib_ieee802dot11_stru    *pst_mib_info;
    mac_device_stru               *pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_vap_init::pst_mac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->uc_chip_id     = uc_chip_id;
    pst_vap->uc_device_id   = uc_device_id;
    pst_vap->uc_vap_id      = uc_vap_id;
    pst_vap->en_vap_mode    = pst_param->en_vap_mode;
	pst_vap->ul_core_id     = pst_mac_device->ul_core_id;

    pst_vap->bit_has_user_bw_limit  = OAL_FALSE;
	pst_vap->bit_vap_bw_limit   = 0;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_vap->bit_voice_aggr     = OAL_TRUE;
#else
	pst_vap->bit_voice_aggr     = OAL_FALSE;
#endif

    oal_set_mac_addr_zero(pst_vap->auc_bssid);

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_vap->ast_user_hash[ul_loop]));
    }

    /* cache user 锁初始化 */
    oal_spin_lock_init(&pst_vap->st_cache_user_lock);

    oal_dlist_init_head(&pst_vap->st_mac_user_list_head);

    /* 初始化支持2.4G 11ac私有增强 */
#ifdef _PRE_WLAN_FEATURE_11AC2G
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    pst_vap->st_cap_flag.bit_11ac2g = pst_param->bit_11ac2g_enable;
#else
    pst_vap->st_cap_flag.bit_11ac2g = OAL_TRUE;
#endif
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    /* 根据定制化刷新2g ht40能力 */
    pst_vap->st_cap_flag.bit_disable_2ght40 = pst_param->bit_disable_capab_2ght40;
#else
    pst_vap->st_cap_flag.bit_disable_2ght40 = OAL_FALSE;
#endif


    switch(pst_vap->en_vap_mode)
    {
        case WLAN_VAP_MODE_CONFIG :
            return OAL_SUCC;
        case WLAN_VAP_MODE_BSS_STA:
        case WLAN_VAP_MODE_BSS_AP:
            /* 设置vap参数默认值 */
            pst_vap->uc_assoc_vap_id = 0xff;
            pst_vap->uc_tx_power     = WLAN_MAX_TXPOWER;
            pst_vap->st_protection.en_protection_mode    = WLAN_PROT_NO;

            pst_vap->st_cap_flag.bit_dsss_cck_mode_40mhz = OAL_TRUE;

            /* 初始化特性标识 */
            pst_vap->st_cap_flag.bit_uapsd      = WLAN_FEATURE_UAPSD_IS_OPEN;
       #ifdef _PRE_WLAN_FEATURE_UAPSD
       #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
            if (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode)
            {
                pst_vap->st_cap_flag.bit_uapsd      = g_uc_uapsd_cap;
            }
       #endif
       #endif
            /* 初始化dpd能力 */
            pst_vap->st_cap_flag.bit_dpd_enbale = OAL_TRUE;

            pst_vap->st_cap_flag.bit_dpd_done   = OAL_FALSE;
            /* 初始化TDLS prohibited关闭 */
            pst_vap->st_cap_flag.bit_tdls_prohibited                = OAL_FALSE;
            /* 初始化TDLS channel switch prohibited关闭 */
            pst_vap->st_cap_flag.bit_tdls_channel_switch_prohibited = OAL_FALSE;

            /* 初始化KeepALive开关 */
            pst_vap->st_cap_flag.bit_keepalive   = OAL_TRUE;
            /* 初始化安全特性值 */
            //pst_vap->uc_80211i_mode              = OAL_FALSE;
            pst_vap->st_cap_flag.bit_wpa         = OAL_FALSE;
            pst_vap->st_cap_flag.bit_wpa2        = OAL_FALSE;

            //OAL_MEMZERO(&(pst_vap->st_key_mgmt), sizeof(mac_key_mgmt_stru));

            /* 初始化协议模式与带宽为非法值，需通过配置命令配置 */
            pst_vap->st_channel.en_band         = WLAN_BAND_BUTT;
            pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_BUTT;
            pst_vap->st_channel.uc_chan_number  = 0;
            pst_vap->en_protocol  = WLAN_PROTOCOL_BUTT;

            /*设置自动保护开启*/
            pst_vap->st_protection.bit_auto_protection = OAL_SWITCH_ON;

            OAL_MEMZERO(pst_vap->ast_app_ie, OAL_SIZEOF(mac_app_ie_stru) * OAL_APP_IE_NUM);

            /*设置初始化rx nss值,之后按协议初始化 */
            pst_vap->en_vap_rx_nss = WLAN_NSS_BUTT;

            /* 设置VAP状态为初始状态INIT */
            mac_vap_state_change(pst_vap, MAC_VAP_STATE_INIT);

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
            mac_proxy_init_vap(pst_vap);
#endif /* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

/* 清mac vap下的uapsd的状态,否则状态会有残留，导致host device uapsd信息不同步 */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        OAL_MEMZERO(&(pst_vap->st_sta_uapsd_cfg),OAL_SIZEOF(mac_cfg_uapsd_sta_stru));
#endif/* #ifdef _PRE_WLAN_FEATURE_STA_PM */

#ifdef _PRE_WLAN_FEATURE_P2P
            //pst_vap->uc_p2p0_hal_vap_id     = 0xff;
            //pst_vap->uc_p2p_gocl_hal_vap_id = 0xff;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            break;
        case WLAN_VAP_MODE_WDS:
            /* TBD 初始化wds特性标识 */
            break;
        case WLAN_VAP_MODE_MONITOER :
            /* TBD */
            break;
        case WLAN_VAP_HW_TEST:
            /* TBD */
            break;
        default :
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANY, "{mac_vap_init::invalid vap mode[%d].}", pst_vap->en_vap_mode);

            return OAL_ERR_CODE_INVALID_CONFIG;
    }
    /* 申请MIB内存空间，配置VAP没有MIB */
    if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) ||
        (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) ||
        (WLAN_VAP_MODE_WDS == pst_vap->en_vap_mode))
    {
        pst_vap->pst_mib_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_MIB, OAL_SIZEOF(wlan_mib_ieee802dot11_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_vap->pst_mib_info)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init::pst_mib_info alloc null, size[%d].}", OAL_SIZEOF(wlan_mib_ieee802dot11_stru));
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        pst_mib_info = pst_vap->pst_mib_info;
        OAL_MEMZERO(pst_mib_info, OAL_SIZEOF(wlan_mib_ieee802dot11_stru));

        /* 设置mac地址 */
        oal_set_mac_addr(pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, pst_mac_device->auc_hw_addr);
        pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID[WLAN_MAC_ADDR_LEN - 1] += uc_vap_id;

        /* 初始化mib值 */
        mac_init_mib(pst_vap);

#ifdef _PRE_WLAN_FEATURE_TXBF
        pst_vap->st_txbf_add_cap.bit_imbf_receive_cap  = 0;
        pst_vap->st_txbf_add_cap.bit_exp_comp_txbf_cap = OAL_TRUE;
        pst_vap->st_txbf_add_cap.bit_min_grouping      = 3;
        pst_vap->st_txbf_add_cap.bit_csi_bfee_max_rows = 1;
        pst_vap->st_txbf_add_cap.bit_channel_est_cap   = 1;
        pst_vap->bit_ap_11ntxbf                        = 0;
        pst_vap->st_cap_flag.bit_11ntxbf               = 1;
#endif
        /*1131debug: mac_vap_init    预留接口 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
        if (NULL != g_fn_mac_vap_init_adjust_patch_ram)
        {
            if (OAL_TRUE == g_fn_mac_vap_init_adjust_patch_ram(pst_vap, uc_chip_id, uc_device_id, uc_vap_id, pst_param))
            {
                return OAL_SUCC;
            }
        }
#endif
        /* sta以最大能力启用 */
        if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
        {
            /* 初始化sta协议模式为11ac */
            switch(pst_mac_device->en_protocol_cap)
            {
                case WLAN_PROTOCOL_CAP_LEGACY:
                case WLAN_PROTOCOL_CAP_HT:
                     pst_vap->en_protocol                = WLAN_HT_MODE;
                     break;

                case WLAN_PROTOCOL_CAP_VHT:
                     pst_vap->en_protocol                = WLAN_VHT_MODE;
                     break;

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_protocol_cap[%d] is not supportted.}", pst_mac_device->en_protocol_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;
            }

            switch(pst_mac_device->en_bandwidth_cap)
            {
                case WLAN_BW_CAP_20M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_20M;
                     break;

                case WLAN_BW_CAP_40M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_40MINUS;
                     break;

                case WLAN_BW_CAP_80M:
                case WLAN_BW_CAP_160M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_80PLUSMINUS;
                     break;

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_bandwidth_cap[%d] is not supportted.}", pst_mac_device->en_bandwidth_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;

            }

            switch(pst_mac_device->en_band_cap)
            {
                case WLAN_BAND_CAP_2G:
                     pst_vap->st_channel.en_band         = WLAN_BAND_2G;
                     break;

            #ifdef _PRE_WLAN_FEATURE_5G
                case WLAN_BAND_CAP_5G:
                case WLAN_BAND_CAP_2G_5G:
                     pst_vap->st_channel.en_band         = WLAN_BAND_5G;
                     break;
            #endif /* _PRE_WLAN_FEATURE_5G */

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_band_cap[%d] is not supportted.}", pst_mac_device->en_band_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;

            }

            if(OAL_SUCC != mac_vap_init_by_protocol(pst_vap, WLAN_VHT_MODE))
            {
                mac_vap_free_mib(pst_vap);
                return OAL_ERR_CODE_INVALID_CONFIG;
            }
            mac_vap_init_rates(pst_vap);
        }
    }

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    if (HISTREAM_SWITCH_ON == g_uc_histream_switch)
    {
        pst_vap->st_histream_info.en_hidevice_type = MAC_HIDEVICE_WMT;
    }
#endif //_PRE_WLAN_FEATURE_HISTREAM

    pst_vap->uc_init_flag = MAC_VAP_VAILD;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_bssid
 功能描述  : 设置BSSID
 输入参数  : mac_vap_stru *pst_mac_vap,
             oal_uint8 *puc_bssid
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_set_bssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid)
{
    oal_memcopy (pst_mac_vap->auc_bssid, puc_bssid, WLAN_MAC_ADDR_LEN);
    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_vap_set_current_channel
 功能描述  : 设置mib信息中当前信道
 输入参数  : 频段:wlan_channel_band_enum_uint8 en_band,
             信道:oal_uint8 uc_channel
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_set_current_channel(mac_vap_stru *pst_vap, wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel)
{
    oal_uint8  uc_channel_idx = 0;
    oal_uint32 ul_ret;

    /* 检查信道号 */
    ul_ret = mac_is_channel_num_valid(en_band, uc_channel);
    if(OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* 根据信道号找到索引号 */
    ul_ret = mac_get_channel_idx_from_num(en_band, uc_channel, &uc_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    pst_vap->st_channel.uc_chan_number = uc_channel;
    pst_vap->st_channel.en_band        = en_band;
    pst_vap->st_channel.uc_idx         = uc_channel_idx;

    pst_vap->pst_mib_info->st_wlan_mib_phy_dsss.ul_dot11CurrentChannel = uc_channel_idx;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_curr_baserate
 功能描述  : 获取某个基本速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  mac_vap_get_curr_baserate(mac_vap_stru *pst_mac_ap,oal_uint8 uc_br_idx)
{
    oal_uint8          uc_loop;
    oal_uint8          uc_found_br_num = 0;
    oal_uint8          uc_rate_num;
    mac_rateset_stru  *pst_rate;

    if (OAL_PTR_NULL == pst_mac_ap)
    {
        return (oal_uint8)OAL_ERR_CODE_PTR_NULL;
    }
    pst_rate = &(pst_mac_ap->st_curr_sup_rates.st_rate);

    uc_rate_num = pst_rate->uc_rs_nrates;

    /* 查找base rate 并记录查找到的个数，与所以比较并返回 */
    for (uc_loop = 0; uc_loop < uc_rate_num; uc_loop++)
    {
        if (0 != ((pst_rate->ast_rs_rates[uc_loop].uc_mac_rate) & 0x80))
        {
            if (uc_br_idx == uc_found_br_num)
            {
                return pst_rate->ast_rs_rates[uc_loop].uc_mac_rate;
            }

            uc_found_br_num++;
        }
    }

    /* 未找到，返回错误 */
    return OAL_FALSE;

}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_vap_state_change_to_sdt
 功能描述  : VAP状态迁移事件以消息形式上报SDT
 输入参数  : en_vap_state:将要变为的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月3日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_state_change(mac_vap_stru *pst_mac_vap, mac_vap_state_enum_uint8 en_vap_state)
{
#if IS_HOST
    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_state_change:from[%d]to[%d]}",pst_mac_vap->en_vap_state,en_vap_state);
#endif
    pst_mac_vap->en_vap_state = en_vap_state;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_vap_check_bss_cap_info_phy_ap
 功能描述  : 检查能力信息中与PHY相关的信息
 输入参数  : 无
 输出参数  : 无check_bss_capability_phy
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : 
    修改内容   : 新生成函数
 修改历史      :
  1.日    期   : 2013年12月6日
    作    者   :  
    修改内容   : 修改函数名，转换为AP和STA公共函数
*****************************************************************************/
oal_bool_enum_uint8  mac_vap_check_bss_cap_info_phy_ap(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap)
{
    mac_cap_info_stru  *pst_cap_info = (mac_cap_info_stru *)(&us_cap_info);

    if (WLAN_BAND_2G != pst_mac_vap->st_channel.en_band)
    {
        return OAL_TRUE;
    }

    /* PBCC */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11PBCCOptionImplemented) &&
       (1 == pst_cap_info->bit_pbcc))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::PBCC is different.}");
    }

    /* Channel Agility */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ChannelAgilityPresent) &&
       (1 == pst_cap_info->bit_channel_agility))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::Channel Agility is different.}");
    }

    /* DSSS-OFDM Capabilities */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_erp.en_dot11DSSSOFDMOptionActivated) &&
       (1 == pst_cap_info->bit_dsss_ofdm))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::DSSS-OFDM Capabilities is different.}");
    }

    return OAL_TRUE;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

/*****************************************************************************
 函 数 名  : mac_vap_get_bandwidth_cap
 功能描述  : 获取vap的带宽运行信息获取vap带宽能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_get_bandwidth_cap(mac_vap_stru *pst_mac_vap, wlan_bw_cap_enum_uint8 *pen_cap)
{
    mac_channel_stru            *pst_channel;
    wlan_bw_cap_enum_uint8       en_band_cap = WLAN_BW_CAP_20M;

    pst_channel = &(pst_mac_vap->st_channel);

    if (WLAN_BAND_WIDTH_40PLUS == pst_channel->en_bandwidth || WLAN_BAND_WIDTH_40MINUS == pst_channel->en_bandwidth)
    {
        en_band_cap = WLAN_BW_CAP_40M;
    }
    else if (pst_channel->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        en_band_cap = WLAN_BW_CAP_80M;
    }

    *pen_cap = en_band_cap;
}

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/*****************************************************************************
 函 数 名  : mac_vap_add_proxysta_dev
 功能描述  : 抛事件到WAL层 添加Proxy STA到hash表，如果为第一个Proxy STA，则挂网桥钩子函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_vap_add_proxysta_dev(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_msg)
{
    frw_event_mem_stru          *pst_event_mem;
    frw_event_stru              *pst_event;
    mac_cfg_set_oma_param_stru  *pst_mac_cfg_set_oma = (mac_cfg_set_oma_param_stru *)puc_msg;

    if (OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{mac_vap_add_proxysta_dev::add Proxy STA vap.}");

        /* 抛加入完成事件到WAL */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_cfg_set_oma_param_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{mac_vap_add_proxysta_dev::Event alloc fail,size[%d]!}", OAL_SIZEOF(mac_cfg_set_oma_param_stru));

            return;
        }

        /* 填写事件 */
        pst_event = (frw_event_stru *)pst_event_mem->puc_data;

        FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                           FRW_EVENT_TYPE_HOST_CTX,
                           HMAC_HOST_CTX_EVENT_SUB_TYPE_ADD_PROXY_STA_VAP,
                           OAL_SIZEOF(mac_cfg_set_oma_param_stru),
                           FRW_EVENT_PIPELINE_STAGE_0,
                           pst_mac_vap->uc_chip_id,
                           pst_mac_vap->uc_device_id,
                           pst_mac_vap->uc_vap_id);

        oal_memcopy(pst_event->auc_event_data, pst_mac_cfg_set_oma, OAL_SIZEOF(mac_cfg_set_oma_param_stru));

        /* 分发事件 */
        frw_event_dispatch_event(pst_event_mem);
        FRW_EVENT_FREE(pst_event_mem);
    }
    else
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{mac_vap_add_proxysta_dev::this vap is not a proxysta.}");
    }

}

#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
oal_uint32 mac_dump_protection(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param)
{
#ifdef _PRE_INFO_LOG
    mac_h2d_protection_stru     *pst_h2d_prot;
    mac_protection_stru         *pst_protection;

    if (OAL_PTR_NULL == puc_param)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_h2d_prot = (mac_h2d_protection_stru *)puc_param;
    pst_protection = &pst_h2d_prot->st_protection;

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "\r\nul_sync_mask=0x%x us_user_idx=%d bit_barker_preamble_mode=%d en_dot11HTProtection=%d\r\n",
            pst_h2d_prot->ul_sync_mask, pst_h2d_prot->us_user_idx, pst_h2d_prot->st_user_cap_info.bit_barker_preamble_mode,
            pst_h2d_prot->en_dot11HTProtection);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "en_dot11RIFSMode=%d en_dot11LSIGTXOPFullProtectionActivated=%d en_dot11NonGFEntitiesPresent=%d en_protection_mode=%d\r\n",
            pst_h2d_prot->en_dot11RIFSMode, pst_h2d_prot->en_dot11LSIGTXOPFullProtectionActivated,
            pst_h2d_prot->en_dot11NonGFEntitiesPresent, pst_protection->en_protection_mode);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_obss_non_erp_aging_cnt=%d uc_obss_non_ht_aging_cnt=%d bit_auto_protection=%d bit_obss_non_erp_present=%d\r\n",
            pst_protection->uc_obss_non_erp_aging_cnt, pst_protection->uc_obss_non_ht_aging_cnt,
            pst_protection->bit_auto_protection, pst_protection->bit_obss_non_erp_present);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "bit_obss_non_ht_present=%d bit_rts_cts_protect_mode=%d bit_lsig_txop_protect_mode=%d uc_sta_no_short_slot_num=%d\r\n",
            pst_protection->bit_obss_non_ht_present, pst_protection->bit_rts_cts_protect_mode,
            pst_protection->bit_lsig_txop_protect_mode, pst_protection->uc_sta_no_short_slot_num);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_sta_no_short_preamble_num=%d uc_sta_non_erp_num=%d uc_sta_non_ht_num=%d uc_sta_non_gf_num=%d\r\n",
            pst_protection->uc_sta_no_short_preamble_num, pst_protection->uc_sta_non_erp_num,
            pst_protection->uc_sta_non_ht_num, pst_protection->uc_sta_non_gf_num);
    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_sta_20M_only_num=%d uc_sta_no_40dsss_cck_num=%d uc_sta_no_lsig_txop_num=%d\r\n",
            pst_protection->uc_sta_20M_only_num, pst_protection->uc_sta_no_40dsss_cck_num,
            pst_protection->uc_sta_no_lsig_txop_num);
#endif /* _PRE_INFO_LOG */

    return OAL_SUCC;
}
#endif //#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)

#if 0
oal_void  mac_vap_set_p2p_channel(mac_vap_stru *pst_mac_vap, mac_channel_stru * pst_p2p_home_channel)
{
    /*
    TBD
    */
}
#endif
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 函 数 名  : mac_vap_init_pmf
 功能描述  : 获取pmf的配置能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 mac_vap_init_pmf(mac_vap_stru  *pst_mac_vap,
                                       mac_cfg80211_connect_security_stru *pst_mac_security_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_security_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF,"mac_11w_init_privacy::Null input,pst_mac_vap[%d],security_param[%d]!!",
                        pst_mac_vap,pst_mac_security_param );
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_TRUE != mac_mib_get_rsnaactivated(pst_mac_vap))
    {
        return OAL_TRUE;
    }
    switch(pst_mac_security_param->en_pmf_cap)
    {
        case MAC_PMF_DISABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
        }
        break;
        case MAC_PMF_ENABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
        }
        break;
        case MAC_PME_REQUIRED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_TRUE);
        }
        break;
        default:
        {
            return OAL_FALSE;
        }
    }

    if (MAC_NL80211_MFP_REQUIRED == pst_mac_security_param->en_mgmt_proteced)
    {
        pst_mac_vap->en_user_pmf_cap = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->en_user_pmf_cap = OAL_FALSE;
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : mac_vap_add_wep_key
 功能描述  : add wep key逻辑，抛事件到DMAC
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数
  2.日    期   : 2015年5月12日
    作    者   : 
    修改内容   : wep密钥保存在组播用户中

*****************************************************************************/
OAL_STATIC oal_uint32 mac_vap_add_wep_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_wep_key_param_stru          *pst_wep_addkey_params = OAL_PTR_NULL;
    mac_user_stru                   *pst_multi_user        = OAL_PTR_NULL;
    wlan_priv_key_param_stru        *pst_wep_key           = OAL_PTR_NULL;
    oal_uint32                       ul_cipher_type        = WLAN_CIPHER_SUITE_WEP40;
    oal_uint8                        uc_wep_cipher_type    = WLAN_80211_CIPHER_SUITE_WEP_40;

    pst_wep_addkey_params = (mac_wep_key_param_stru*)puc_param;

    /*wep 密钥最大为4个*/
    if(pst_wep_addkey_params->uc_key_index >= WLAN_MAX_WEP_KEY_COUNT)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    switch (pst_wep_addkey_params->uc_key_len)
    {
        case WLAN_WEP40_KEY_LEN:
            uc_wep_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
            ul_cipher_type     = WLAN_CIPHER_SUITE_WEP40;
            break;
        case WLAN_WEP104_KEY_LEN:
            uc_wep_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_104;
            ul_cipher_type     = WLAN_CIPHER_SUITE_WEP104;
            break;
        default:
            return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    /* WEP密钥信息记录到组播用户中*/
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    /* 初始化WEP组播加密套件 */
    mac_mib_set_RSNAGroupCipherSelected(pst_mac_vap, uc_wep_cipher_type);

    /*初始化组播用户的安全信息*/
    if (pst_wep_addkey_params->en_default_key == OAL_TRUE)
    {
        pst_multi_user->st_key_info.en_cipher_type     = uc_wep_cipher_type;
        pst_multi_user->st_key_info.uc_default_index   = pst_wep_addkey_params->uc_key_index;
        pst_multi_user->st_key_info.uc_igtk_key_index  = 0xff;/* wep时设置为无效 */
        pst_multi_user->st_key_info.bit_gtk            = 0;
    }

    pst_wep_key   = &pst_multi_user->st_key_info.ast_key[pst_wep_addkey_params->uc_key_index];

    pst_wep_key->ul_cipher        = ul_cipher_type;
    pst_wep_key->ul_key_len       = (oal_uint32)pst_wep_addkey_params->uc_key_len;

    OAL_MEMZERO(pst_wep_key->auc_key, WLAN_WPA_KEY_LEN);
    oal_memcopy(pst_wep_key->auc_key, pst_wep_addkey_params->auc_wep_key, pst_wep_addkey_params->uc_key_len);

    /* TBD 挪出去 初始化组播用户的发送信息 */
    pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type      = pst_wep_addkey_params->uc_key_index + HAL_KEY_TYPE_PTK;
    pst_multi_user->st_user_tx_info.st_security.en_cipher_protocol_type = uc_wep_cipher_type;
    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
    //              "{mac_config_11i_add_wep_key::set multiuser ciphertype[%d] ok}", uc_wep_cipher_type);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_init_privacy
 功能描述  : 根据内核下发的关联能力，赋值加密相关的mib 值
 输入参数  : mac_vap_stru                        *pst_mac_vap
             mac_cfg80211_connect_param_stru     *pst_mac_connect_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月26日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_init_privacy(mac_vap_stru *pst_mac_vap, mac_cfg80211_connect_security_stru *pst_mac_security_param)
{
    mac_wep_key_param_stru              st_wep_key = {0};
    mac_cfg80211_crypto_settings_stru  *pst_crypto;
    oal_uint8                           uc_loop = 0;
    oal_uint32                          ul_ret  = OAL_SUCC;

    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
#if defined (_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    /* 初始化 RSNActive 为FALSE */
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
#endif
    /* 清除加密套件信息 */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);

    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;

    /* 不加密 */
    if (OAL_FALSE == pst_mac_security_param->en_privacy)
    {
        return OAL_SUCC;
    }

    /* WEP加密 */
    if (0 != pst_mac_security_param->uc_wep_key_len)
    {
        st_wep_key.uc_key_len   = pst_mac_security_param->uc_wep_key_len;
        st_wep_key.uc_key_index = pst_mac_security_param->uc_wep_key_index;
        st_wep_key.en_default_key = OAL_TRUE;
        oal_memcopy(st_wep_key.auc_wep_key, pst_mac_security_param->auc_wep_key, WLAN_WEP104_KEY_LEN);
        ul_ret = mac_vap_add_wep_key(pst_mac_vap, OAL_SIZEOF(mac_wep_key_param_stru), (oal_uint8 *)&st_wep_key);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{mac_11i_init_privacy::mac_config_11i_add_wep_key failed[%d].}", ul_ret);
        }
        return ul_ret;
    }

    /* WPA/WPA2加密 */
    pst_crypto = &(pst_mac_security_param->st_crypto);

    if ((pst_crypto->n_ciphers_pairwise > WLAN_PAIRWISE_CIPHER_SUITES) ||
        (pst_crypto->n_akm_suites > WLAN_AUTHENTICATION_SUITES))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_11i_init_privacy::cipher_num[%d] akm_num[%d] unexpected.}",
                       pst_crypto->n_ciphers_pairwise, pst_crypto->n_akm_suites);
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /* 初始化RSNA mib 为 TRUR */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);

    /* 初始化组播密钥套件 */
    mac_mib_set_rsnacfggroupcipher(pst_mac_vap, (oal_uint8)(pst_crypto->cipher_group));
    mac_mib_set_RSNAGroupCipherSelected(pst_mac_vap, (oal_uint8)(pst_crypto->cipher_group));

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    ul_ret = mac_vap_init_pmf(pst_mac_vap, pst_mac_security_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_11i_init_privacy::mac_11w_init_privacy failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif
    /* 初始化单播密钥套件 */
    if (pst_crypto->wpa_versions == WITP_WPA_VERSION_1)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;
        for (uc_loop = 0; uc_loop < pst_crypto->n_ciphers_pairwise; uc_loop++)
        {
            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_crypto->ciphers_pairwise[uc_loop]);
        }
    }
    else if (pst_crypto->wpa_versions == WITP_WPA_VERSION_2)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;
        for (uc_loop = 0; uc_loop < pst_crypto->n_ciphers_pairwise; uc_loop++)
        {
            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_crypto->ciphers_pairwise[uc_loop]);
        }
    }

    /* 初始化认证套件 */
    for (uc_loop = 0; uc_loop < pst_crypto->n_akm_suites; uc_loop++)
    {
        mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(pst_mac_vap, pst_crypto->akm_suites[uc_loop], uc_loop);
    }

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                  "{mac_11i_init_privacy::wpa_version[%d], group %d, n_pairwise %d, n_akm %d.}",
                  pst_crypto->wpa_versions,
                  pst_crypto->cipher_group,
                  pst_crypto->n_ciphers_pairwise,
                  pst_crypto->n_akm_suites);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_mib_set_wep
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_mib_set_wep(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id)
{
    /*初始化wep相关MIB信息*/
    oal_memset(pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_key_id].auc_dot11WEPDefaultKeyValue, 0, WLAN_MAX_WEP_STR_SIZE);
    pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_key_id].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = 40;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_check_auth_policy
 功能描述  : 检测认证方式是否匹配
 输入参数  : wlan_mib_ieee802dot11_stru *pst_mib_info
             oal_uint8 uc_policy
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8    OAL_TRUE:匹配成功
                                    OAL_FALSE:匹配失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月31日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 mac_check_auth_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                                   oal_uint8 uc_policy)
{
    oal_uint8 uc_loop = 0;
    for (uc_loop = 0; uc_loop < MAC_AUTHENTICATION_SUITE_NUM; uc_loop++)
    {
        /* 检测认证套件是否使能和匹配 */
        if ((pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].en_dot11RSNAConfigAuthenticationSuiteActivated == OAL_TRUE)
            && (pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].uc_dot11RSNAConfigAuthenticationSuiteImplemented == uc_policy))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : mac_get_user_by_addr
 功能描述  : 根据mac地址获取mac_user指针
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
mac_user_stru  *mac_vap_get_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr)
{
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx   = 0xffff;
    mac_user_stru          *pst_mac_user = OAL_PTR_NULL;

    /*根据mac addr找到sta索引*/
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if(OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::find_user_by_macaddr failed[%d].}", ul_ret);
        if(OAL_PTR_NULL != puc_mac_addr)
        {
            OAM_WARNING_LOG3(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::mac[%x:XX:XX:XX:%x:%x] cant be found!}",
                                    puc_mac_addr[0], puc_mac_addr[4], puc_mac_addr[5]);
        }
        return OAL_PTR_NULL;
    }

    /*根据sta索引找到user内存区域*/
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::user ptr null.}");
    }

    return pst_mac_user;
}

/*****************************************************************************
 函 数 名  : mac_vap_add_beacon
 功能描述  : 复位11X端口
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_add_beacon(mac_vap_stru *pst_mac_vap, mac_beacon_param_stru *pst_beacon_param)
{
    mac_user_stru                        *pst_multi_user;
    wlan_mib_dot11RSNAConfigEntry_stru   *pst_mib_rsna_cfg;
    oal_uint32                            ul_loop;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_beacon_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_vap_add_beacon::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 清除之前的加密配置信息 */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;
    mac_mib_clear_rsna_auth_suite(pst_mac_vap);

    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = OAL_FALSE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = OAL_FALSE;

    /* 清除组播密钥信息 */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_add_beacon::pst_multi_user null [idx:%d] .}", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_beacon_param->en_privacy)
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_11i_add_beacon::privacy disabled");
        return OAL_SUCC;
    }

    /* 使能加密 */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    pst_mib_rsna_cfg = &pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg;

    if (0 == (pst_beacon_param->uc_crypto_mode & (WLAN_WPA_BIT | WLAN_WPA2_BIT)))
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_11i_add_beacon::wep enabled");
        return OAL_SUCC;
    }
    /* WEP加密时，在addbeacon流程之前，已经通过add key配置了密钥。 */
    mac_user_init_key(pst_multi_user);
    pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;

    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);
    /* 配置组播套件 */
    switch (pst_beacon_param->uc_group_crypto)
    {
        case WLAN_80211_CIPHER_SUITE_TKIP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
            break;
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                           "{mac_vap_add_beacon::UNEXPECTED group_crypto[%d].}", pst_beacon_param->uc_group_crypto);
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_mib_rsna_cfg->uc_dot11RSNAConfigGroupCipher     = pst_beacon_param->uc_group_crypto;

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
    //              "{mac_11i_add_beacon::WPA group [%d]}", pst_beacon_param->uc_group_crypto);

    /* 配置认证套件 */
    for(ul_loop = 0; ul_loop < MAC_AUTHENTICATION_SUITE_NUM; ul_loop++)
    {
        if (0xff == pst_beacon_param->auc_auth_type[ul_loop])
        {
            continue;
        }
        mac_mib_set_rsna_auth_suite(pst_mac_vap, pst_beacon_param->auc_auth_type[ul_loop]);
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;

        /* 配置WPA单播密钥套件 */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_11i_add_beacon::WPA pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA2_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;

        /* 配置WPA2单播密钥套件 */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            /*  WIFI_SW: B130版本：CI 验证库上SVN节点3399的软件版本，2.4G混合加密四次握手失败  */
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_11i_add_beacon::WPA2 pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }

        /* RSN 能力 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR  = (pst_beacon_param->us_rsn_capability & BIT6) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC  = (pst_beacon_param->us_rsn_capability & BIT7) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated = pst_beacon_param->us_rsn_capability & BIT0;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x0C) >> 2;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x30) >> 4;

    }


    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_user_add_key
 功能描述  : 根据en_key_type，调用相应的函数，更新vap信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_add_key(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_key_id, mac_key_params_stru *pst_key)
{
    oal_uint32                            ul_ret;

    switch ((oal_uint8)pst_key->cipher)
    {
        case WLAN_80211_CIPHER_SUITE_WEP_40:
        case WLAN_80211_CIPHER_SUITE_WEP_104:
            /* 设置mib */
            mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
            mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
            //TBD 设置组播密钥套件应该放在set default key
            mac_mib_set_rsnacfggroupcipher(pst_mac_vap, (oal_uint8)pst_key->cipher);
            ul_ret = mac_user_add_wep_key(pst_mac_user, uc_key_id, pst_key);
            break;
        case WLAN_80211_CIPHER_SUITE_TKIP:
        case WLAN_80211_CIPHER_SUITE_CCMP:
            ul_ret = mac_user_add_rsn_key(pst_mac_user, uc_key_id, pst_key);
            break;
        case WLAN_80211_CIPHER_SUITE_BIP:
            ul_ret = mac_user_add_bip_key(pst_mac_user, uc_key_id, pst_key);
            break;
        default:
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_default_key_id
 功能描述  : 获取mac加密属性default_key_id
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 mac_vap_get_default_key_id(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru                *pst_multi_user;
    oal_uint8                     uc_default_key_id;

    /* 根据索引，从组播用户密钥信息中查找密钥 */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        /* TBD 调用本函数的地方都没有错误返回处理 */
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{mac_vap_get_default_key_id::multi_user[%d] NULL}", pst_mac_vap->us_multi_user_idx);
        return 0;
    }

    if ((pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_40) &&
        (pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_104))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_vap_get_default_key_id::unexpectd cipher_type[%d]}", pst_multi_user->st_key_info.en_cipher_type);
        return 0;
    }
    uc_default_key_id = pst_multi_user->st_key_info.uc_default_index;
    if (uc_default_key_id >= WLAN_NUM_TK)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{mac_vap_get_default_key_id::unexpectd keyid[%d]}", uc_default_key_id);
        return 0;
    }
    return uc_default_key_id;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_default_key
 功能描述  : 更新hmac加密属性default_key
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8  uc_key_index)
{
    wlan_priv_key_param_stru     *pst_wep_key = OAL_PTR_NULL;
    mac_user_stru                *pst_multi_user;

    /* 1.1 如果非wep 加密，则直接返回 */
    if (OAL_TRUE != mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    /* 2.1 根据索引，从组播用户密钥信息中查找密钥 */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_wep_key   = &pst_multi_user->st_key_info.ast_key[uc_key_index];

    if (pst_wep_key->ul_cipher != WLAN_CIPHER_SUITE_WEP40 &&
        pst_wep_key->ul_cipher != WLAN_CIPHER_SUITE_WEP104)
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /* 3.1 更新密钥类型及default id */
    pst_multi_user->st_key_info.en_cipher_type     = (oal_uint8)(pst_wep_key->ul_cipher);
    pst_multi_user->st_key_info.uc_default_index   = uc_key_index;

    /* 4.1 设置mib属性 */
    mac_set_wep_default_keyid(pst_mac_vap, uc_key_index);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_set_default_mgmt_key
 功能描述  : 设置管理帧密钥
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_set_default_mgmt_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    mac_user_stru                *pst_multi_user;

    /* 管理帧加密信息保存在组播用户中 */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /* keyid校验 */
    if (uc_key_index < WLAN_NUM_TK || uc_key_index > WLAN_MAX_IGTK_KEY_INDEX)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    if (WLAN_80211_CIPHER_SUITE_BIP != (oal_uint8)pst_multi_user->st_key_info.ast_key[uc_key_index].ul_cipher)
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }


    /* 更新IGTK的keyid */
    pst_multi_user->st_key_info.uc_igtk_key_index   = uc_key_index;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_user_init_security_port
 功能描述  : 初始化STA 加密情况下，数据过滤的参数。
 输入参数  : pst_hmac_sta
             pst_hmac_user_ap
 输出参数  : 无
 返 回 值  : mac_status_code_enum_uint16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月11日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
void mac_vap_init_user_security_port(mac_vap_stru  *pst_mac_vap,
                                        mac_user_stru *pst_mac_user)
{
    mac_user_set_port(pst_mac_user, OAL_TRUE);

    if (OAL_TRUE != pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated)
    {
        return;
    }

    /* 是否采用WPA 或WPA2 加密方式 */
    if ((OAL_TRUE != pst_mac_vap->st_cap_flag.bit_wpa)
        && (OAL_TRUE != pst_mac_vap->st_cap_flag.bit_wpa2))
    {
        return;
    }

    /* STA需要检测是否采用802.1X 认证方式 */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode
        && OAL_TRUE == mac_check_auth_policy(pst_mac_vap->pst_mib_info, WLAN_AUTH_SUITE_1X))
        || (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode))
    {
        mac_user_set_port(pst_mac_user, OAL_FALSE);
    }

    /* :如果用户已经关联，仍需要初始化用户加密能力为不加密 */
    mac_user_init_key(pst_mac_user);
}

/*****************************************************************************
 函 数 名  : mac_vap_set_beacon
 功能描述  : 复位11X端口
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_vap_set_beacon(mac_vap_stru *pst_mac_vap, mac_beacon_param_stru *pst_beacon_param)
{
    //mac_user_stru                        *pst_multi_user;
    wlan_mib_dot11RSNAConfigEntry_stru   *pst_mib_rsna_cfg;
    oal_uint32                            ul_loop;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_beacon_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_vap_set_beacon::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 清除之前的加密配置信息 */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;
    mac_mib_clear_rsna_auth_suite(pst_mac_vap);

    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = OAL_FALSE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = OAL_FALSE;

#if 0
    /* 清除组播密钥信息 */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_beacon::pst_multi_user null .}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    if (OAL_FALSE == pst_beacon_param->en_privacy)
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_beacon::privacy disabled");
        return OAL_SUCC;
    }

    /* 使能加密 */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    pst_mib_rsna_cfg = &pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg;

    if (0 == (pst_beacon_param->uc_crypto_mode & (WLAN_WPA_BIT | WLAN_WPA2_BIT)))
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_beacon::wep enabled");
        return OAL_SUCC;
    }
    /* WEP加密时，在addbeacon流程之前，已经通过add key配置了密钥。 */
    //mac_user_init_key(pst_multi_user);
    //pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;

    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);
    /* 配置组播套件 */
    switch (pst_beacon_param->uc_group_crypto)
    {
        case WLAN_80211_CIPHER_SUITE_TKIP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
            break;
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                           "{mac_vap_set_beacon::UNEXPECTED group_crypto[%d].}", pst_beacon_param->uc_group_crypto);
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_mib_rsna_cfg->uc_dot11RSNAConfigGroupCipher     = pst_beacon_param->uc_group_crypto;

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
    //              "{mac_vap_set_beacon::WPA group [%d]}", pst_beacon_param->uc_group_crypto);

    /* 配置认证套件 */
    for(ul_loop = 0; ul_loop < MAC_AUTHENTICATION_SUITE_NUM; ul_loop++)
    {
        if (0xff == pst_beacon_param->auc_auth_type[ul_loop])
        {
            continue;
        }
        mac_mib_set_rsna_auth_suite(pst_mac_vap, pst_beacon_param->auc_auth_type[ul_loop]);
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;

        /* 配置WPA单播密钥套件 */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
             //             "{mac_vap_set_beacon::WPA pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA2_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;

        /* 配置WPA2单播密钥套件 */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            /*  WIFI_SW: B130版本：CI 验证库上SVN节点3399的软件版本，2.4G混合加密四次握手失败  */
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_vap_set_beacon::WPA2 pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }

        /* RSN 能力 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR  = (pst_beacon_param->us_rsn_capability & BIT6) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC  = (pst_beacon_param->us_rsn_capability & BIT7) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated = pst_beacon_param->us_rsn_capability & BIT0;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x0C) >> 2;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x30) >> 4;

    }


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_get_mac_addr
 功能描述  : 获取vap的 mac地址
 输入参数  : dmac_vap_stru *pst_dmac_vap
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8* mac_vap_get_mac_addr(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_P2P
    if (IS_P2P_DEV(pst_mac_vap))
    {
        /* 获取P2P DEV MAC 地址，赋值到probe req 帧中 */
        return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID;
    }
    else
#endif /* _PRE_WLAN_FEATURE_P2P */
    {
        /* 设置地址2为自己的MAC地址 */
        return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;
    }
}
#ifdef _PRE_WLAN_FEATURE_11R
/*****************************************************************************
 函 数 名  : mac_mib_init_ft_cfg
 功能描述  : 初始化Fast BSS Trisition信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_mib_init_ft_cfg(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mde)
{

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::pst_mib_info null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_PTR_NULL == puc_mde) || (puc_mde[0] != MAC_EID_MOBILITY_DOMAIN) || (puc_mde[1] != 3))
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_FALSE;
        return OAL_SUCC;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_TRUE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID[0] = puc_mde[2];
    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID[1] = puc_mde[3];
    if (puc_mde[4] & 1)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTOverDSActivated = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTOverDSActivated = OAL_FALSE;
    }
    if (puc_mde[4] & 2)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTResourceRequestSupported = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTResourceRequestSupported = OAL_FALSE;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_mib_get_md_id
 功能描述  : 获取当前的md id
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_mib_get_md_id(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_mdid)
{

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::pst_mib_info null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
    {
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_TRUE;

    *pus_mdid = *(oal_uint16*)(pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID);

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_11R


/*lint -e19*/
//oal_module_symbol(mac_vap_set_p2p_channel);
#ifdef _PRE_WLAN_FEATURE_UAPSD
oal_module_symbol(g_uc_uapsd_cap);
#endif
oal_module_symbol(mac_vap_set_bssid);
oal_module_symbol(mac_vap_set_current_channel);
oal_module_symbol(mac_vap_init_wme_param);
oal_module_symbol(mac_mib_set_station_id);
oal_module_symbol(mac_vap_state_change);
#if 0
oal_module_symbol(mac_mib_get_station_id);
#endif
oal_module_symbol(mac_mib_set_bss_type);
oal_module_symbol(mac_get_bss_type);
oal_module_symbol(mac_mib_set_ssid);
oal_module_symbol(mac_get_ssid);
oal_module_symbol(mac_mib_set_beacon_period);
oal_module_symbol(mac_get_beacon_period);
oal_module_symbol(mac_mib_set_dtim_period);
#ifdef _PRE_WLAN_FEATURE_UAPSD
oal_module_symbol(mac_vap_set_uapsd_en);
oal_module_symbol(mac_vap_get_uapsd_en);
#endif
#if 0
oal_module_symbol(mac_mib_get_GroupReceivedFrameCount);
oal_module_symbol(mac_mib_set_GroupReceivedFrameCount);
oal_module_symbol(mac_vap_get_user_wme_info);
oal_module_symbol(mac_vap_set_user_wme_info);
#endif
oal_module_symbol(mac_mib_set_shpreamble);
oal_module_symbol(mac_mib_get_shpreamble);
oal_module_symbol(mac_vap_add_assoc_user);
oal_module_symbol(mac_vap_del_user);
oal_module_symbol(mac_vap_init);
oal_module_symbol(mac_vap_exit);
oal_module_symbol(mac_init_mib);
oal_module_symbol(mac_mib_get_ssid);
oal_module_symbol(mac_mib_get_bss_type);
oal_module_symbol(mac_mib_get_beacon_period);
oal_module_symbol(mac_mib_get_dtim_period);
oal_module_symbol(mac_vap_init_rates);
oal_module_symbol(mac_vap_init_by_protocol);
oal_module_symbol(mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented);
oal_module_symbol(mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented);
oal_module_symbol(mibset_RSNAClearWpaPairwiseCipherImplemented);
oal_module_symbol(mibset_RSNAClearWpa2PairwiseCipherImplemented);
oal_module_symbol(mac_vap_config_vht_ht_mib_by_protocol);
oal_module_symbol(mac_mib_set_RSNAAuthenticationSuiteSelected);
oal_module_symbol(mac_vap_check_bss_cap_info_phy_ap);
oal_module_symbol(mac_mib_set_RSNAConfigAuthenticationSuiteImplemented);
oal_module_symbol(mac_get_wmm_cfg);
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
oal_module_symbol(mac_get_wmm_cfg_multi_user_multi_ac);
#endif
oal_module_symbol(mac_vap_get_bandwidth_cap);
oal_module_symbol(mac_vap_change_mib_by_bandwidth);
oal_module_symbol(mac_vap_init_rx_nss_by_protocol);
oal_module_symbol(mac_mib_clear_rsna_auth_suite);
oal_module_symbol(mac_mib_set_rsna_auth_suite);
oal_module_symbol(mac_dump_protection);
oal_module_symbol(mac_vap_set_aid);
oal_module_symbol(mac_vap_set_al_tx_payload_flag);
oal_module_symbol(mac_vap_set_assoc_id);
oal_module_symbol(mac_vap_set_al_tx_flag);
oal_module_symbol(mac_vap_set_tx_power);
oal_module_symbol(mac_vap_set_uapsd_cap);
oal_module_symbol(mac_vap_set_al_tx_first_run);
oal_module_symbol(mac_vap_set_multi_user_idx);
oal_module_symbol(mac_vap_set_wmm_params_update_count);
#if 0
oal_module_symbol(mac_vap_set_rifs_tx_on);
oal_module_symbol(mac_vap_set_tdls_prohibited);
oal_module_symbol(mac_vap_set_tdls_channel_switch_prohibited);
#endif
oal_module_symbol(mac_vap_set_11ac2g);
oal_module_symbol(mac_vap_set_hide_ssid);
oal_module_symbol(mac_get_p2p_mode);
oal_module_symbol(mac_vap_clear_app_ie);
oal_module_symbol(mac_vap_save_app_ie);
oal_module_symbol(mac_vap_set_rx_nss);
oal_module_symbol(mac_vap_find_user_by_macaddr);
oal_module_symbol(mac_vap_get_curr_baserate);

oal_module_symbol(mac_sta_init_bss_rates);

#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(mac_mib_get_smps);
oal_module_symbol(mac_vap_get_smps_mode);
oal_module_symbol(mac_vap_get_smps_en);
oal_module_symbol(mac_vap_set_smps);
#endif

oal_module_symbol(mac_device_find_user_by_macaddr);

oal_module_symbol(mac_vap_init_privacy);

oal_module_symbol(mac_mib_set_wep);
oal_module_symbol(mac_check_auth_policy);
oal_module_symbol(mac_vap_get_user_by_addr);

oal_module_symbol(mac_vap_add_beacon);
oal_module_symbol(mac_vap_add_key);
oal_module_symbol(mac_vap_get_default_key_id);
oal_module_symbol(mac_vap_set_default_key);
oal_module_symbol(mac_vap_set_default_mgmt_key);
oal_module_symbol(mac_vap_init_user_security_port);
oal_module_symbol(mac_vap_set_beacon);
/*lint +e19*/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)
#pragma arm section rwdata = "patch", code = "patch", zidata = "patch", rodata = "patch"
oal_bool_enum_uint8 mac_vap_init_mib_11n_adjust(mac_vap_stru  *pst_mac_vap)
{
    return OAL_FALSE;
}
oal_bool_enum_uint8 mac_vap_init_adjust(
                    mac_vap_stru               *pst_vap,
                    oal_uint8                   uc_chip_id,
                    oal_uint8                   uc_device_id,
                    oal_uint8                   uc_vap_id,
                    mac_cfg_add_vap_param_stru *pst_param)
{
    return OAL_FALSE;
}
#pragma arm section rodata, code, rwdata, zidata
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


