/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : hmac_dfx.c
  版 本 号   : 初稿
  作    者   : z
  生成日期   : 2014年4月7日
  最近修改   :
  功能描述   : DFX文件接扩
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月7日
    作    者   : z
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
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hmac_dfx.h"
#include "oal_file.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DFX_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

OAL_STATIC oam_cfg_data_stru  g_ast_cfg_data[OAM_CFG_TYPE_BUTT] =
{
    {OAM_CFG_TYPE_MAX_ASOC_USER,     "USER_SPEC",     "max_asoc_user",     31},
};

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST)
/*针对1102  Host存在该变量，避免重定义*/

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
oal_int32    g_l_proxysta_feature = 0;
#endif
oal_uint16   g_us_wlan_assoc_user_max_num     = WLAN_ASSOC_USER_MAX_NUM_LIMIT;     /* 关联用户的最大个数 Root AP模式下为32个,Repeater模式下是15个 */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* 由于WL_L2_DRAM大小限制，目前暂时开放3个业务vap，整体规格开放待后续优化 TBD */
oal_uint32   g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;  /* 3个AP + 1个配置vap */
#else
oal_uint32   g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;  /* 4个AP + 1个配置vap */
#endif

#else
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_int32    g_l_proxysta_feature ;
#endif
extern oal_uint16   g_us_wlan_assoc_user_max_num;
extern oal_uint32   g_ul_wlan_vap_max_num_per_device;
#endif

/*****************************************************************************
  3 函数实现  TBD 置换函数名称
*****************************************************************************/
/*****************************************************************************
 函 数 名  : oam_cfg_get_item_by_id
 功能描述  : 提供给其他模块获取配置项值的接口
 输入参数  : en_cfg_type:其它模块传入的配置项类型
 输出参数  :
 返 回 值  : 配置项的值或者错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oam_cfg_get_item_by_id(oam_cfg_type_enum_uint16  en_cfg_type)
{
    oal_uint32      ul_loop;

    for (ul_loop = 0; ul_loop < OAM_CFG_TYPE_BUTT; ul_loop++)
    {
        if (en_cfg_type == g_ast_cfg_data[ul_loop].en_cfg_type)
        {
            break;
        }
    }

    if (OAM_CFG_TYPE_BUTT == ul_loop)
    {
        OAL_IO_PRINT("oam_cfg_get_item_by_id::get cfg item failed!\n");
        return -OAL_FAIL;
    }

    return g_ast_cfg_data[ul_loop].l_val;
}

#if ((_PRE_PRODUCT_ID_HI1131C_DEV ==_PRE_PRODUCT_ID) || (_PRE_PRODUCT_ID_HI1131C_HOST ==_PRE_PRODUCT_ID))
/*****************************************************************************
 函 数 名  : oam_spec_init
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_custom_init(oal_void)
{
    /* 硬件限制:3个STA; 2个AP */
    /* 软件规格:
        1)AP 模式:  2个ap + 1个配置vap
        2)STA 模式: 3个sta + 1个配置vap
        3)STA+P2P共存模式:  1个sta + 1个P2P_dev + 1个P2P_GO/Client + 1个配置vap
        4)STA+Proxy STA共存模式:  1个sta + ?个proxy STA + 1个配置vap
    */
    g_us_wlan_assoc_user_max_num     = WLAN_ASSOC_USER_MAX_NUM_LIMIT;
    // TBD 设定为WLAN_ASSOC_USER_MAX_NUM_LIMIT;
    g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;

    return OAL_SUCC;
}

#else

/*****************************************************************************
 函 数 名  : oam_spec_init
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  hmac_custom_init(oal_void)
{

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (g_l_proxysta_feature)
    {
        g_us_wlan_assoc_user_max_num  = 15;
        g_ul_wlan_vap_max_num_per_device = WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;/* 1个AP, 1个sta，15个Proxy STA，1个配置vap */
    }
    else
#endif
    {
        g_us_wlan_assoc_user_max_num  = WLAN_ASSOC_USER_MAX_NUM_LIMIT;
        g_ul_wlan_vap_max_num_per_device = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE;
    }

    return OAL_SUCC;
}
#endif



/*****************************************************************************
 函 数 名  : oam_cfg_restore_all_item
 功能描述  : 从配置文件中获取配置项的值中间失败的话，需要将之前获取的值恢复
             为默认值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  oam_cfg_restore_all_item(oal_int32 al_default_cfg_data[])
{
    oal_uint32          ul_loop;

    for (ul_loop = 0; ul_loop < OAM_CFG_TYPE_BUTT; ul_loop++)
    {
        g_ast_cfg_data[ul_loop].l_val = al_default_cfg_data[ul_loop];
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_cfg_get_all_item
 功能描述  : OAM模块加载的时候将配置文件中的所有配置信息保存到一个内部结构中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  oam_cfg_get_all_item(oal_void)
{
    oal_int32     al_default_cfg_data[OAM_CFG_TYPE_BUTT] = {0};
    oal_uint8    *puc_plaintext;
    oal_uint8    *puc_ciphertext;
    oal_uint32    ul_file_size = 0;
    oal_uint32    ul_loop;
    oal_int32     l_ret =0;
    oal_int       i_key[OAL_AES_KEYSIZE_256] = {0x1,0x2,0x3,0x4d,0x56,0x10,0x11,0x12,
                                       		    0x1,0x2,0x3,0x4d,0x56,0x10,0x11,0x12,
                                       		    0x1,0x2,0x3,0x4d,0x56,0x10,0x11,0x12,
                                       		    0x1,0x2,0x3,0x4d,0x56,0x10,0x11,0x12};

	oal_aes_key_stru    st_aes_key;

    /* 保存默认配置，如果获取配置文件中信息的时候中间有失败的情况，则需要恢复
       前面全局配置信息，其它模块加载的时候可以按照默认配置加载
    */
    for (ul_loop = 0; ul_loop < OAM_CFG_TYPE_BUTT; ul_loop++)
    {
        al_default_cfg_data[ul_loop] = g_ast_cfg_data[ul_loop].l_val;
    }

    /* 获取文件大小并获取文件指针 */

    l_ret = oal_file_size(OAL_CFG_FILE_PATH,&ul_file_size);

    if (OAL_SUCC != l_ret)
    {
        OAL_IO_PRINT("oam_cfg_get_all_item::get file size failed!\n");
        return l_ret;
    }

    /* 将配置文件中的所有数据读到一个缓冲区里，此时数据是加密的 */
    puc_ciphertext = oal_memalloc(ul_file_size + OAM_CFG_STR_END_SIGN_LEN);
    if (OAL_PTR_NULL == puc_ciphertext)
    {
        OAL_IO_PRINT("oam_cfg_get_all_item::alloc ciphertext buf failed! load ko with default cfg!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_MEMZERO(puc_ciphertext, ul_file_size + OAM_CFG_STR_END_SIGN_LEN);

    l_ret = oam_cfg_read_file_to_buf((oal_int8 *)puc_ciphertext, ul_file_size);
    if (OAL_SUCC != l_ret)
    {
        OAL_IO_PRINT("oam_cfg_get_all_item::get cfg data from file failed! fail id-->%d\n", l_ret);
        oal_free(puc_ciphertext);
        return l_ret;
    }

    /* 申请明文空间，并将密文解密 */
    puc_plaintext = oal_memalloc(ul_file_size + OAM_CFG_STR_END_SIGN_LEN);
    if (OAL_PTR_NULL == puc_plaintext)
    {
        OAL_IO_PRINT("oam_cfg_get_all_item::alloc pc_plaintext buf failed! load ko with default cfg!\n");
        oal_free(puc_ciphertext);

        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_MEMZERO(puc_plaintext, ul_file_size + OAM_CFG_STR_END_SIGN_LEN);

    /* 解密 */
    l_ret = (oal_int32)oal_aes_expand_key(&st_aes_key,(oal_uint8 *)i_key,OAL_AES_KEYSIZE_256);
    if (OAL_SUCC != l_ret)
    {
        oal_free(puc_plaintext);
        oal_free(puc_ciphertext);

        return l_ret;
    }

    oam_cfg_decrypt_all_item(&st_aes_key, (oal_int8 *)puc_ciphertext,
                            (oal_int8 *)puc_plaintext, ul_file_size);

    /* 获取配置文件中每一项的信息，保存到OAM内部结构中 */
    for (ul_loop = 0; ul_loop < OAM_CFG_TYPE_BUTT; ul_loop++)
    {
        l_ret = oam_cfg_get_one_item((oal_int8 *)puc_plaintext,
                                     g_ast_cfg_data[ul_loop].pc_section,
                                     g_ast_cfg_data[ul_loop].pc_key,
                                     &g_ast_cfg_data[ul_loop].l_val);

        /* 如果获取某一配置值不成功，则恢复配置项的默认值 */
        if (OAL_SUCC != l_ret)
        {
            OAL_IO_PRINT("oam_cfg_get_all_item::get cfg item fail! ul_loop=%d\n", ul_loop);

            oam_cfg_restore_all_item(al_default_cfg_data);
            oal_free(puc_plaintext);
            oal_free(puc_ciphertext);

            return l_ret;
        }
    }

    /* 释放缓冲区 */
    oal_free(puc_plaintext);
    oal_free(puc_ciphertext);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : oam_config_init
 功能描述  : 模块初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月10日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  oam_cfg_init(oal_void)
{
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
    oal_int32      l_ret = OAL_SUCC;

    l_ret = oam_cfg_get_all_item();

    return (oal_uint32)l_ret;
#else
    return 0;
#endif
}

oal_uint32 hmac_dfx_init(void)
{
    oam_register_init_hook(OM_WIFI, oam_cfg_init);
    return hmac_custom_init();
}

oal_uint32 hmac_dfx_exit(void)
{
    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
