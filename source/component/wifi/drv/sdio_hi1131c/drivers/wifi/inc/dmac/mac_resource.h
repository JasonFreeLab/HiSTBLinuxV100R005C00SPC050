/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : mac_resource.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : mac_resource.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAC_RESOURCE_H__
#define __MAC_RESOURCE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_queue.h"
#include "mac_device.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_RESOURCE_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/



#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV)

    /* mac_vap_stru, hmac_vap_stru私有部分, dmac_vap_stru私有部分总规格 */
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define MAC_RES_VAP_SIZE        3600
#else
#define MAC_RES_VAP_SIZE        1404
#endif

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* mac_user_stru, hmac_user_stru私有部分, dmac_user_stru私有部分总规格，必须四字节对齐 */
#ifdef _PRE_WLAN_FEATURE_REKEY_OFFLOAD
#define MAC_RES_USER_SIZE       1564
#else
#define MAC_RES_USER_SIZE       1520
#endif
#else
#define MAC_RES_USER_SIZE       1404
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

#elif (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_HOST)

    /* mac_vap_stru, hmac_vap_stru私有部分, dmac_vap_stru私有部分总规格 */
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define MAC_RES_VAP_SIZE        5872
#else
#define MAC_RES_VAP_SIZE        5872 /*适配ARM64 都对齐到8B*/
#endif

#ifdef CONFIG_ARM64
/*when arm64, c pointer change to 8 bytes*/
#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 1700 /* 增加业务识别功能后，hmac_user_stru结构体中增加用户业务信息，扩充规格为1700 */
#else
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 0
#endif  /* end of _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

#define MAC_RES_USER_SIZE       (4072 + FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE)
#else

    /* mac_user_stru, hmac_user_stru私有部分, dmac_user_stru私有部分总规格，考虑到ARM64都对齐到8B */
#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 1700 /* 增加业务识别功能后，hmac_user_stru结构体中增加用户业务信息，扩充规格为1700 */
#else
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 0
#endif  /* end of _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

#define MAC_RES_USER_SIZE       (2992 + FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE)
#endif  /* end of CONFIG_ARM64 */

#else

    /* mac_vap_stru, hmac_vap_stru私有部分, dmac_vap_stru私有部分总规格 */
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define MAC_RES_VAP_SIZE        4200//(2600 + 1232)     /* lm: hmac vap结构体中增加变量定时器，结果大小超出规格，因此扩充规格大小 */
#else
#define MAC_RES_VAP_SIZE        2500
#endif

    /* mac_user_stru, hmac_user_stru私有部分, dmac_user_stru私有部分总规格，必须四字节对齐 */
#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 1700 /* 增加业务识别功能后，hmac_user_stru结构体中增加用户业务信息，扩充规格为1700 */
#else
#define FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE 0
#endif  /* end of _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

#define MAC_RES_USER_SIZE       (3700 + FEATURE_TX_CLASSIFY_LAN_TO_WLAN_RES_SIZE) /* 原来为3560,后增大结构体成员后为3640,预留60（原因：51双核加载dmac出现改结构体过大）*/

#endif



/* 最大dev数量 */
#define MAC_RES_MAX_DEV_NUM     (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern oal_uint16 g_us_max_asoc_user;


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
   oal_uint8       uc_vap[MAC_RES_VAP_SIZE];
}mac_res_mem_vap_stru;

typedef struct
{
   oal_uint8       uc_user[MAC_RES_USER_SIZE];
}mac_res_mem_user_stru;

typedef struct
{
    oal_dlist_head_stru     st_entry;
    oal_uint16              us_user_idx;                /* 记录对应的USER的索引值 */
    oal_uint16              us_hash_res_idx;            /* 记录对应的HASH资源池的索引值 */
}mac_res_user_hash_stru;

/*
typedef struct
{
    mac_res_user_hash_stru      ast_user_hash_info[WLAN_ASSOC_USER_MAX_NUM];
    oal_queue_stru              st_queue;
    oal_uint32                  aul_idx[WLAN_ASSOC_USER_MAX_NUM];
    oal_uint8                   auc_user_cnt[WLAN_ASSOC_USER_MAX_NUM];

}mac_res_hash_stru;
*/

typedef struct
{
    mac_res_user_hash_stru     *pst_user_hash_info;
    oal_queue_stru              st_queue;
    oal_uint                   *pul_idx;
    oal_uint8                  *puc_user_cnt;
}mac_res_hash_stru;

typedef struct
{
    mac_device_stru     ast_dev_info[MAC_RES_MAX_DEV_NUM];
    oal_queue_stru      st_queue;
    oal_uint            aul_idx[MAC_RES_MAX_DEV_NUM];
    oal_uint8           auc_user_cnt[MAC_RES_MAX_DEV_NUM];
    oal_uint8           auc_resv[2];
}mac_res_device_stru;

typedef struct
{
    mac_res_mem_vap_stru    ast_vap_info[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oal_queue_stru          st_queue;
    oal_uint                aul_idx[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oal_uint16              us_hmac_priv_size;
    oal_uint8               auc_user_cnt[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
    oal_uint8               auc_resv[2];
}mac_res_vap_stru;

typedef struct
{
    mac_res_mem_user_stru  *pst_user_info;
    oal_queue_stru          st_queue;
    oal_uint                *pul_idx;
    oal_uint16              us_hmac_priv_size;
    oal_uint8               auc_resv[2];
    oal_uint8              *puc_user_cnt;

}mac_res_user_stru;


typedef struct
{
    mac_res_device_stru st_dev_res;
    mac_res_vap_stru    st_vap_res;
    mac_res_user_stru   st_user_res;
    mac_res_hash_stru   st_hash_res;
}mac_res_stru;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern mac_res_stru    g_st_mac_res;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32  mac_res_alloc_dmac_dev(oal_uint8    *puc_dev_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  mac_res_alloc_hmac_dev(oal_uint8    *puc_dev_idx);
#else
extern oal_uint32  mac_res_alloc_hmac_dev(oal_uint32    ul_dev_idx);
#endif
extern oal_uint32  mac_res_free_dev(oal_uint32 ul_dev_idx);
extern oal_uint32  mac_res_free_mac_user(oal_uint16 us_idx);
extern oal_uint32  mac_res_free_mac_vap(oal_uint32 ul_idx);
extern oal_uint32  mac_res_free_hash(oal_uint32 ul_hash_idx);



/*****************************************************************************
 函 数 名  : mac_res_alloc_hash
 功能描述  : 获取一个HASH资源
 输入参数  : 无
 输出参数  : HASH内存索引值
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_res_alloc_hash(oal_uint16    *pus_hash_idx)
{
    oal_uint  ul_hash_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pus_hash_idx))
    {
        return OAL_FAIL;
    }

    ul_hash_idx_temp = (oal_uint)oal_queue_dequeue(&(g_st_mac_res.st_hash_res.st_queue));

    /* 0为无效值 */
    if (0 == ul_hash_idx_temp)
    {
        return OAL_FAIL;
    }

    *pus_hash_idx = (oal_uint16)(ul_hash_idx_temp - 1);

    (g_st_mac_res.st_hash_res.puc_user_cnt[ul_hash_idx_temp - 1])++;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_res_get_hash
 功能描述  : 获取对应hash索引的内存
 输入参数  : 对应hash内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_res_user_hash_stru*  mac_res_get_hash(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= (oal_uint32)(g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM)))
    {
        return OAL_PTR_NULL;
    }

    return &(g_st_mac_res.st_hash_res.pst_user_hash_info[ul_dev_idx]);
}

/*****************************************************************************
 函 数 名  : mac_res_alloc_hmac_vap
 功能描述  : 分配HMAC层的VAP资源
 输入参数  : 无
 输出参数  : HMAC VAP内存索引值
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_res_alloc_hmac_vap(oal_uint8 *puc_idx, oal_uint16 us_hmac_priv_size)
{
    oal_uint  ul_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_idx))
    {
        return OAL_FAIL;
    }

    ul_idx_temp = (oal_uint)oal_queue_dequeue(&(g_st_mac_res.st_vap_res.st_queue));

    /* 0为无效值 */
    if (0 == ul_idx_temp)
    {
        return OAL_FAIL;
    }

    *puc_idx = (oal_uint8)(ul_idx_temp - 1);

    g_st_mac_res.st_vap_res.us_hmac_priv_size = us_hmac_priv_size;

    (g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx_temp - 1])++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_res_alloc_dmac_vap
 功能描述  : 分配DMAC层的VAP资源
 输入参数  :
 输出参数  : 下一个可以创建的vap的index
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_res_alloc_dmac_vap(oal_uint8 uc_idx)
{
    if (OAL_UNLIKELY(uc_idx >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FAIL;
    }

    (g_st_mac_res.st_vap_res.auc_user_cnt[uc_idx])++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_res_alloc_dmac_user
 功能描述  : 分配DMAC层的USER资源
 输入参数  : DMAC USER内存索引值，此索引值由HMAC决定
 输出参数  : 无
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_res_alloc_dmac_user(oal_uint16 us_idx)
{
    if (OAL_UNLIKELY((us_idx) >= (g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM)))
    {
        return OAL_FAIL;
    }

    /* DMAC仅需要设置为有效即可 */
    (g_st_mac_res.st_user_res.puc_user_cnt[us_idx])++;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_res_get_dev
 功能描述  : 获取对应DEV索引的内存
 输入参数  : 对应DEV内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_device_stru*  mac_res_get_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        return OAL_PTR_NULL;
    }

    return &(g_st_mac_res.st_dev_res.ast_dev_info[ul_dev_idx]);
}

/*****************************************************************************
 函 数 名  : mac_res_get_hmac_vap
 功能描述  : 获取对应HMAC VAP索引的内存,由HMAC层强转为自己的内存解析
 输入参数  : 对应HMAC VAP内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void*  mac_res_get_hmac_vap(oal_uint32 ul_idx)
{
    if (OAL_UNLIKELY(ul_idx >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_PTR_NULL;
    }

    return (oal_void *)(&(g_st_mac_res.st_vap_res.ast_vap_info[ul_idx]));
}

/*****************************************************************************
 函 数 名  : mac_res_get_mac_vap
 功能描述  : 获取对应MAC VAP索引的内存,由MAC层强转为自己的内存解析
 输入参数  : 对应MAC VAP内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void*  mac_res_get_mac_vap(oal_uint8 uc_idx)
{
    if (OAL_UNLIKELY(uc_idx >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_PTR_NULL;
    }

    /* 这里返回偏移内存空间 */
    return (oal_void *)((oal_uint8 *)(&(g_st_mac_res.st_vap_res.ast_vap_info[uc_idx]))
                        + g_st_mac_res.st_vap_res.us_hmac_priv_size);

}

/*****************************************************************************
 函 数 名  : mac_res_get_dmac_vap
 功能描述  : 获取对应DMAC VAP索引的内存,由HMAC层强转为自己的内存解析
 输入参数  : 对应DMAC VAP内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void*  mac_res_get_dmac_vap(oal_uint8 uc_idx)
{
    return mac_res_get_mac_vap(uc_idx);
}

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_res_alloc_hmac_user
 功能描述  : 分配HMAC层的USER资源
 输入参数  : 无
 输出参数  : HMAC USER内存索引值
 返 回 值  : OAL_SUCC/OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_res_alloc_hmac_user(oal_uint16 *pus_idx, oal_uint16 us_hmac_priv_size)
{
    oal_uint  ul_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pus_idx))
    {
        return OAL_FAIL;
    }

    ul_idx_temp = (oal_uint)oal_queue_dequeue(&(g_st_mac_res.st_user_res.st_queue));

    /* 0为无效值 */
    if (0 == ul_idx_temp)
    {
        return OAL_FAIL;
    }

    *pus_idx = (oal_uint16)(ul_idx_temp - 1);

    g_st_mac_res.st_user_res.us_hmac_priv_size = us_hmac_priv_size;

    (g_st_mac_res.st_user_res.puc_user_cnt[ul_idx_temp - 1])++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_res_get_hmac_user
 功能描述  : 获取对应HMAC USER索引的内存,由HMAC层强转为自己的内存解析
 输入参数  : 对应HMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void*  _mac_res_get_hmac_user(oal_uint16 us_idx)
{
    if (OAL_UNLIKELY(us_idx >= g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM))
    {
        return OAL_PTR_NULL;
    }

    return (oal_void *)(&(g_st_mac_res.st_user_res.pst_user_info[us_idx]));
}
#endif //#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1131C_HOST)
/*****************************************************************************
 函 数 名  : mac_res_get_mac_user
 功能描述  : 获取对应MAC USER索引的内存
 输入参数  : 对应MAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void*  _mac_res_get_mac_user(oal_uint16 us_idx)
{
    if (OAL_UNLIKELY(us_idx >= (g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM)))
    {
        return OAL_PTR_NULL;
    }

    /* 这里偏移内存空间 */
    return (oal_void *)((oal_uint8 *)(&(g_st_mac_res.st_user_res.pst_user_info[us_idx]))
                        + g_st_mac_res.st_user_res.us_hmac_priv_size);
}

/*****************************************************************************
 函 数 名  : mac_res_get_max_user_id
 功能描述  : 获取最大user_id
 输入参数  : 对应DMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint16  mac_res_get_max_user_id(void)
{
    return (oal_uint16)(g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM);
}

extern oal_uint32  mac_res_init(oal_void);
extern oal_uint32  mac_res_exit(void);
extern oal_uint16  mac_res_get_max_asoc_user(oal_void);
extern oal_uint32  mac_res_set_max_asoc_user(oal_uint16 us_num);
extern oal_uint32  mac_res_alloc_hmac_user_ex(oal_uint16 *pus_idx, oal_uint16 us_hmac_priv_size);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_resource.h */
