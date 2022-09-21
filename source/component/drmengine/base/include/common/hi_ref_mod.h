/**
 \file
 \brief 模块公共定义
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author Hisilicon STB Step-2 software group
 \date 2009/03/19
 */

#ifndef __HI_REF_MOD_H__
#define __HI_REF_MOD_H__

#include "hi_type.h"
#include "utils/Logger.h"
#include "hi_unf_version.h"
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
#include "hi_module.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
#define HI_MOD_ID_NULL       (HI_ID_USR_START + (0))     /** 起始mod id */
#else
#define HI_MOD_ID_NULL       (0xB0)                      /** 起始mod id */
#endif
#define HI_MOD_MAX_NUM       (HI_MOD_ID_NULL + (100))    /** 最大mod个数 */

#define HI_MOD_INVALID_ID    (-1)    /** 非法mod id */
#define HI_MOD_NAME_LEN      (32)    /** mod名称字节数 */
#define HI_MSG_APPID         (0x0)
#define HI_DEF_MSGTYPE(mid, MSYTYPE) \
    ( ((HI_MSG_APPID)<<24) | (((HI_S32)mid) << 16 ) | (HI_S32)(MSYTYPE) )

/******************************* API declaration *****************************/

/**
\brief 根据模块ID取模块名
\attention \n
无
\param[in] u32ModID 模块ID

\retval ::模块名
\retval ::如果u32ModID非法,返回空字符串""

\see \n
无
*/
const HI_CHAR * HI_MOD_GetNameById(HI_U32 u32ModID);

/**
\brief 根据模块ID取模块名
\attention \n
无
\param[in] pszModName 模块名称
\param[out] pu32ModId 获取到的mod id

\retval ::成功，HI_SUCCESS
\retval ::失败，HI_FAILURE

\see \n
无
*/
HI_S32 HI_MOD_GetIdByName(HI_CHAR *pszModName, HI_U32 *pu32ModId);

/**
\brief 注册模块id
\attention \n
无
\param[in] u32ModId 模块ID，上层定义的modid,范围0-(HI_MOD_MAX_NUM-1)
\param[in] pszModName 模块名称

\retval ::成功，HI_SUCCESS
\retval ::失败，HI_FAILURE

\see \n
无
*/
HI_S32 HI_MOD_Register(HI_U32 u32ModId, HI_CHAR* pszModName);

/** 注册mod */
#define REG_MOD(MODID, MODNAME) \
do { \
    HI_S32 ret = HI_MOD_Register(MODID, #MODNAME); \
    if (HI_SUCCESS != ret) \
    { \
        HI_LOGE("ret = %d", ret); \
    } \
} while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_REF_MOD_H__*/
