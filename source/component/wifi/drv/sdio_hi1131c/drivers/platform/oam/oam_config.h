/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oam_config.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2014年4月7日
  最近修改   :
  功能描述   : oam_config.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月7日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAM_CONFIG_H__
#define __OAM_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION))
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 配置项的值在配置文件中占的最大字节数 */
#define   OAM_CFG_VAL_MAX_LEN       20

/* 等于号(=)长度 */
#define   OAM_CFG_EQUAL_SIGN_LEN    1

/* '\0'长度 */
#define   OAM_CFG_STR_END_SIGN_LEN  1


typedef oal_uint32 (* p_oam_customize_init_func)(oal_void);
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*TBD 待枚举值和BFGIN归一*/
/* primID pattern */
enum OM_MSG_MODULEID
{
    OM_WIFI_HOST    = 0x00,
    OM_WIFI         = 0x01,
    OM_BT           = 0x02,
    OM_GNSS         = 0x03,
    OM_FM           = 0x04,
    OM_PF           = 0x05,
    OM_MODULEID_BUTT
};
typedef oal_uint8 oam_msg_moduleid_enum_uint8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    p_oam_customize_init_func customize_init[OM_MODULEID_BUTT];       /* 所有定制化的初始函数 */
}oam_customize_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern oam_customize_stru g_oam_customize;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  oam_register_init_hook(oam_msg_moduleid_enum_uint8 en_moduleid,  p_oam_customize_init_func p_func);
extern oal_int32  oam_cfg_get_one_item(
                                           oal_int8   *pc_cfg_data_buf,
                                           oal_int8   *pc_section,
                                           oal_int8   *pc_key,
                                          oal_int32   *pl_val);

extern oal_int32  oam_cfg_read_file_to_buf(
                                                    oal_int8   *pc_cfg_data_buf,
                                                    oal_uint32  ul_file_size);

extern oal_uint32  oam_cfg_decrypt_all_item(
                                              oal_aes_key_stru *pst_aes_key,
                                              oal_int8         *pc_ciphertext,
                                              oal_int8         *pc_plaintext,
                                              oal_uint32        ul_cipher_len);


#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)

/* '\0'长度 */
#define   OAM_CFG_STR_END_SIGN_LEN  1

enum OM_MSG_MODULEID
{
    OM_WIFI         = 0x00,
    OM_MODULEID_BUTT
};

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_config.h */
