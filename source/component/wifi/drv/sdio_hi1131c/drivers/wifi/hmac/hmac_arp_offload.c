/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_arp_offload.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2015年5月14日
  最近修改   :
  功能描述   : ARP Offloading相关函数实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月14日
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
#include "frw_ext_if.h"
#include "hmac_arp_offload.h"
#include "hmac_vap.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ARP_OFFLOAD_C


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : hmac_arp_offload_set_ip_addr
 功能描述  : 网络接口UP/DOWN时，增加/删除IP地址
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_void *pst_ip_addr
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_arp_offload_set_ip_addr(mac_vap_stru *pst_mac_vap,
                                        dmac_ip_type_enum_uint8 en_type,
                                        dmac_ip_oper_enum_uint8 en_oper,
                                        oal_void *pst_ip_addr)
{
    dmac_ip_addr_config_stru  st_ip_addr_config;
    oal_uint32                ul_ret;

    if (OAL_UNLIKELY(NULL == pst_ip_addr))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{hmac_arp_offload_set_ip_addr::The pst_mac_vap point is NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memset(&st_ip_addr_config, 0, OAL_SIZEOF(st_ip_addr_config));

    if (DMAC_CONFIG_IPV4 == en_type)
    {
        oal_memcopy(st_ip_addr_config.auc_ip_addr, pst_ip_addr, OAL_IPV4_ADDR_SIZE);
    }
    else if (DMAC_CONFIG_IPV6 == en_type)
    {
        oal_memcopy(st_ip_addr_config.auc_ip_addr, pst_ip_addr, OAL_IPV6_ADDR_SIZE);
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{hmac_arp_offload_set_ip_addr::The type[%d] is error.}", en_type);
        return OAL_ERR_CODE_MAGIC_NUM_FAIL;
    }
    st_ip_addr_config.en_type = en_type;

    if (OAL_UNLIKELY(DMAC_IP_OPER_BUTT <= en_oper))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{hmac_arp_offload_set_ip_addr::The operation[%d] is error.}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    st_ip_addr_config.en_oper = en_oper;

    ul_ret = hmac_config_set_ip_addr(pst_mac_vap, OAL_SIZEOF(dmac_ip_addr_config_stru), (oal_uint8 *)&st_ip_addr_config);
    return ul_ret;
}

/*****************************************************************************
 函 数 名  : hmac_arp_offload_enable
 功能描述  : host侧打开/关闭ARP offload功能的接口
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_bool_enum_uint8 en_switch
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 hmac_arp_offload_enable(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_switch)
{
    oal_uint32                    ul_ret;

    if (OAL_UNLIKELY(NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{hmac_arp_offload_enable::The pst_mac_vap point is NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_SWITCH_BUTT <= en_switch))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{hmac_arp_offload_enable::The en_switch[%d] is error.}", en_switch);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    ul_ret = hmac_config_enable_arp_offload(pst_mac_vap, OAL_SIZEOF(oal_switch_enum_uint8), (oal_switch_enum_uint8 *)&en_switch);
    return ul_ret;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

