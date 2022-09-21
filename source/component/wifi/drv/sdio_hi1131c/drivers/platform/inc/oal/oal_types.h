/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_types.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月7日
  最近修改   :
  功能描述   : oal_types.h 的头文件,基本数据类型定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月7日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_TYPES_H__
#define __OAL_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "arch/oal_types.h"
/*****************************************************************************
  2 基本数据类型定义
*****************************************************************************/
typedef float                   oal_float32;        /* 数据前缀:f */
typedef double                  oal_float64;        /* 数据前缀:d */

/*******************************************************************************
    不确定长度，在32位机长度为32bits，在64位机长度为64bits
*******************************************************************************/
typedef unsigned long           oal_uint;           /* 数据前缀:ui */
typedef signed long             oal_int;            /* 数据前缀:i */
typedef unsigned long           oal_ulong;           /*和指针类型等长*/
typedef signed long             oal_long;            /*数据前缀:i */

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define OAL_PTR_NULL        (0L)                        /* 空指针定义，指针判断是否为空时与OAL_PTR_NULL进行比较 */

#ifndef NULL
#define NULL    OAL_PTR_NULL
#endif

#define OAL_REFERENCE(data)	((void)(data))

/* linux错误码 */
#define OAL_EFAIL               1   /* 内核通用错误返回值 -1 */
#define OAL_EIO                 5   /* I/O error */
#define OAL_ENOMEM              12  /* Out of memory */
#define OAL_EFAUL               14  /* Bad address */
#define OAL_EBUSY               16  /* Device or resource busy */
#define OAL_ENODEV              19  /* No such device */
#define OAL_EINVAL              22  /* Invalid argument */

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
typedef enum
{
    OAL_FALSE   = 0,
    OAL_TRUE    = 1,

    OAL_BUTT
}oal_bool_enum;
typedef oal_uint8 oal_bool_enum_uint8;

/* 三种业务类型 */
typedef enum
{
    OAL_TRAFFIC_NORMAL= 0,					/*一般业务*/
    OAL_TRAFFIC_MULTI_USER_MULTI_AC   = 1,	/*多用户多优先级业务*/
    OAL_TRAFFIC_MULTI_USER_ONLY_BE   = 2,		/*32用户单优先级业务*/
    OAL_TRAFFIC_BUTT
}oal_traffic_type_enum;
typedef oal_uint8 oal_traffic_type_enum_uint8;

/* 定义功能开关 */
typedef enum
{
    OAL_SWITCH_OFF  = 0,
    OAL_SWITCH_ON   = 1,

    OAL_SWITCH_BUTT
}oal_switch_enum;
typedef oal_uint8 oal_switch_enum_uint8;

typedef enum
{
    /**************************************************************************
        platform err code
    ***************************************************************************/
    ERR_CODE_PLATFORM_BASE  = 0x00000001,
    /**************************************************************************
        wifi err code
    ***************************************************************************/
    ERR_CODE_WIFI_BASE      = 0x10000000,
    /**************************************************************************
        bt device code
    ***************************************************************************/
    ERR_CODE_BT_BASE        = 0x20000000,
    /**************************************************************************
        fm err code
    ***************************************************************************/
    ERR_CODE_FM_BASE        = 0x30000000,
    /**************************************************************************
        gnss err code
    ***************************************************************************/
    ERR_CODE_GNSS_BASE      = 0x40000000,
    /**************************************************************************
        nfc err code
    ***************************************************************************/
    ERR_CODE_NFC_BASE       = 0x50000000,
    /**************************************************************************
        ir device code
    ***************************************************************************/
    ERR_CODE_IR_BASE        = 0x60000000,
}err_code_enum;
typedef oal_uint32 err_code_enum_uint32;

/* 软件整体错误码定义 */
typedef enum
{
    OAL_SUCC                                  = 0,                              /* 成功，没有异常 */   

    /**************************************************************************
        plat pm exception
    **************************************************************************/
    OAL_ERR_CODE_PM_BASE                     = 10,
    OAL_ERR_CODE_ALREADY_OPEN                = (OAL_ERR_CODE_PM_BASE + 0),    /* 已经打开 */
    OAL_ERR_CODE_ALREADY_CLOSE               = (OAL_ERR_CODE_PM_BASE + 1),    /* 已经关闭 */

    /**************************************************************************
        system exception
    **************************************************************************/
    OAL_ERR_CODE_SYS_BASE                     = 100,
    OAL_ERR_CODE_PTR_NULL                     = (OAL_ERR_CODE_SYS_BASE + 0),    /* 指针检查为空 */
    OAL_ERR_CODE_ARRAY_OVERFLOW               = (OAL_ERR_CODE_SYS_BASE + 1),    /* 数组下标越界 */
    OAL_ERR_CODE_DIV_ZERO                     = (OAL_ERR_CODE_SYS_BASE + 2),    /* 除0操作 */
    OAL_ERR_CODE_ALLOC_MEM_FAIL               = (OAL_ERR_CODE_SYS_BASE + 3),    /* 申请内存失败 */
    OAL_ERR_CODE_FREE_MEM_FAIL                = (OAL_ERR_CODE_SYS_BASE + 4),
    OAL_ERR_CODE_START_TIMRE_FAIL             = (OAL_ERR_CODE_SYS_BASE + 5),    /* 启动定时器失败 */
    OAL_ERR_CODE_RESET_INPROGRESS             = (OAL_ERR_CODE_SYS_BASE + 6),    /* 复位处理中 */
    OAL_ERR_CODE_MAC_DEVICE_NULL              = (OAL_ERR_CODE_SYS_BASE + 7),    /* mac_device_struz找不到 */
	OAL_ERR_CODE_MAGIC_NUM_FAIL               = (OAL_ERR_CODE_SYS_BASE + 8),    /* 魔法数字检测失败 */
	OAL_ERR_CODE_NETBUF_INDEX_CHANGE          = (OAL_ERR_CODE_SYS_BASE + 9),    /*netbuf 被篡改 */
    OAL_ERR_CODE_CFG_REG_TIMEOUT              = (OAL_ERR_CODE_SYS_BASE + 10),   /* 配置寄存器超时 */
    OAL_ERR_CODE_CFG_REG_ERROR                = (OAL_ERR_CODE_SYS_BASE + 11),   /* 配置寄存器错误 */
    OAL_ERR_CODE_LIST_NOT_EMPTY_ERROR         = (OAL_ERR_CODE_SYS_BASE + 12),   /* 链表不为空，一般出现于链表清除动作后 */

    OAL_ERR_SYS_BUTT                          = (OAL_ERR_CODE_SYS_BASE + 999),        /* system error最大值*/

    /**************************************************************************
        config exception
    ***************************************************************************/
    OAL_ERR_CODE_CONFIG_BASE                  = 1000,
    OAL_ERR_CODE_INVALID_CONFIG               = (OAL_ERR_CODE_CONFIG_BASE + 0), /* 无效配置 */
    OAL_ERR_CODE_CONFIG_UNSUPPORT             = (OAL_ERR_CODE_CONFIG_BASE + 1), /* 配置不支持 */
    OAL_ERR_CODE_CONFIG_EXCEED_SPEC           = (OAL_ERR_CODE_CONFIG_BASE + 2), /* 配置超过规格 */
    OAL_ERR_CODE_CONFIG_TIMEOUT               = (OAL_ERR_CODE_CONFIG_BASE + 3), /* 配置超时 */
    OAL_ERR_CODE_CONFIG_BUSY                  = (OAL_ERR_CODE_CONFIG_BASE + 4),
    OAL_ERR_CODE_ADD_VAP_INDX_UNSYNC          = (OAL_ERR_CODE_CONFIG_BASE + 5), /* HMAC和DMAC创建vap时的index不一致 */
    OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC   = (OAL_ERR_CODE_CONFIG_BASE + 6), /* HMAC和DMAC创建multi user时的index不一致 */
    OAL_ERR_CODE_USER_RES_CNT_ZERO            = (OAL_ERR_CODE_CONFIG_BASE + 7), /* 用户资源已经释放，重复释放 */

    OAL_ERR_CODE_CONFIG_BUTT                  = (OAL_ERR_CODE_CONFIG_BASE + 99),/* 配置错误最大值*/

    /**************************************************************************
        MSG exception
    **************************************************************************/
    OAL_ERR_CODE_MSG_BASE                      = 1100,
    OAL_ERR_CODE_MSG_TYPE_ERR                  = (OAL_ERR_CODE_MSG_BASE + 0),   /* 消息类型解析错误 */
    OAL_ERR_CODE_MSG_NOT_CMPTBL_WITH_STATE     = (OAL_ERR_CODE_MSG_BASE + 1),   /* 消息与所处的状态不一致 */
    OAL_ERR_CODE_MSG_IE_MISS                   = (OAL_ERR_CODE_MSG_BASE + 2),   /* 消息IE缺失 */
    OAL_ERR_CODE_MSG_IE_VALUE_ERR              = (OAL_ERR_CODE_MSG_BASE + 3),   /* 消息IE的值错误 */
    OAL_ERR_CODE_IPC_QUEUE_FULL                = (OAL_ERR_CODE_MSG_BASE + 4),   /* ipc内部消息发送队列列已满 */
    OAL_ERR_CODE_MSG_NOT_FIND_STA_TAB          = (OAL_ERR_CODE_MSG_BASE + 5),   /* 消息找不到状态表 */
    OAL_ERR_CODE_MSG_NOT_FIND_ACT_TAB          = (OAL_ERR_CODE_MSG_BASE + 6),   /* 消息找不到动作表 */
    OAL_ERR_CODE_MSG_ACT_FUN_NULL              = (OAL_ERR_CODE_MSG_BASE + 7),   /* 消息对应的处理函数为NULL */
    OAL_ERR_CODE_MSG_LENGTH_ERR                = (OAL_ERR_CODE_MSG_BASE + 8),   /* 消息长度错误 */

    OAL_ERR_CODE_MSG_BUTT                      = (OAL_ERR_CODE_MSG_BASE + 99),  /* 消息错误最大值*/

    /**************************************************************************
        文件操作错误码
    **************************************************************************/
    OAL_ERR_CODE_FILE_BASE                     = 1200,
    OAL_ERR_CODE_OPEN_FILE_FAIL                = (OAL_ERR_CODE_FILE_BASE + 0),
    OAL_ERR_CODE_WRITE_FILE_FAIL               = (OAL_ERR_CODE_FILE_BASE + 1),
    OAL_ERR_CODE_READ_FILE_FAIL                = (OAL_ERR_CODE_FILE_BASE + 2),
    OAL_ERR_CODE_CLOSE_FILE_FAIL               = (OAL_ERR_CODE_FILE_BASE + 3),

    OAL_ERR_CODE_FILE_BUTT                     = (OAL_ERR_CODE_FILE_BASE + 99), /*文件操作错误最大值*/

    /**************************************************************************
        各模块自定义错误
    **************************************************************************/
    /**************************** 描述符操作错误 *****************************/
    OAL_ERR_CODE_DSCR_BASE                     = 10000,
    OAL_ERR_CODE_RX_DSCR_AMSDU_DISORDER        = (OAL_ERR_CODE_DSCR_BASE + 0),  /* AMSDU对应的描述符乱序 */
    OAL_ERR_CODE_RX_DSCR_LOSE                  = (OAL_ERR_CODE_DSCR_BASE + 1),  /* 描述符域buf数目不对应 */

    OAL_ERR_CODE_DSCR_BUTT                     = (OAL_ERR_CODE_DSCR_BASE + 999),

    /**************************************************************************
        各特性自定义错误,从20000开始，每个特性分配100个
    **************************************************************************/
    /**************************** AMSDU特性 ***********************************/
    OAL_ERR_CODE_HMAC_AMSDU_BASE               = 20000,
    OAL_ERR_CODE_HMAC_AMSDU_DISABLE            = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 0),  /* amsdu功能关闭 */
    OAL_ERR_CODE_HMAC_MSDU_LEN_OVER            = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 1),

    OAL_ERR_CODE_HMAC_AMSDU_BUTT               = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 999),

    /********************************* 其它 **********************************/
    /**************************** 11i 特性 ***********************************/
    OAL_ERR_CODE_SECURITY_BASE               = 21000,
    OAL_ERR_CODE_SECURITY_KEY_TYPE           = (OAL_ERR_CODE_SECURITY_BASE + 0),
    OAL_ERR_CODE_SECURITY_KEY_LEN            = (OAL_ERR_CODE_SECURITY_BASE + 1),
    OAL_ERR_CODE_SECURITY_KEY_ID             = (OAL_ERR_CODE_SECURITY_BASE + 2),
    OAL_ERR_CODE_SECURITY_CHIPER_TYPE        = (OAL_ERR_CODE_SECURITY_BASE + 3),
    OAL_ERR_CODE_SECURITY_BUFF_NUM           = (OAL_ERR_CODE_SECURITY_BASE + 4),
    OAL_ERR_CODE_SECURITY_BUFF_LEN           = (OAL_ERR_CODE_SECURITY_BASE + 5),
    OAL_ERR_CODE_SECURITY_WRONG_KEY          = (OAL_ERR_CODE_SECURITY_BASE + 6),
    OAL_ERR_CODE_SECURITY_USER_INVAILD       = (OAL_ERR_CODE_SECURITY_BASE + 7),
    OAL_ERR_CODE_SECURITY_PARAMETERS         = (OAL_ERR_CODE_SECURITY_BASE + 8),
    OAL_ERR_CODE_SECURITY_AUTH_TYPE          = (OAL_ERR_CODE_SECURITY_BASE + 9),
    OAL_ERR_CODE_SECURITY_CAP                = (OAL_ERR_CODE_SECURITY_BASE + 10),
    OAL_ERR_CODE_SECURITY_CAP_MFP            = (OAL_ERR_CODE_SECURITY_BASE + 11),
    OAL_ERR_CODE_SECURITY_CAP_BSS            = (OAL_ERR_CODE_SECURITY_BASE + 12),
    OAL_ERR_CODE_SECURITY_CAP_PHY            = (OAL_ERR_CODE_SECURITY_BASE + 13),
    OAL_ERR_CODE_SECURITY_PORT_INVALID       = (OAL_ERR_CODE_SECURITY_BASE + 14),
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    OAL_ERR_CODE_SECURITY_MAC_INVALID        = (OAL_ERR_CODE_SECURITY_BASE + 15),
    OAL_ERR_CODE_SECURITY_MODE_INVALID       = (OAL_ERR_CODE_SECURITY_BASE + 16),
    OAL_ERR_CODE_SECURITY_LIST_FULL          = (OAL_ERR_CODE_SECURITY_BASE + 17),
    OAL_ERR_CODE_SECURITY_AGING_INVALID      = (OAL_ERR_CODE_SECURITY_BASE + 18),
    OAL_ERR_CODE_SECURITY_THRESHOLD_INVALID  = (OAL_ERR_CODE_SECURITY_BASE + 19),
    OAL_ERR_CODE_SECURITY_RESETIME_INVALID   = (OAL_ERR_CODE_SECURITY_BASE + 20),
#endif
    OAL_ERR_CODE_SECURITY_BUTT               = (OAL_ERR_CODE_SECURITY_BASE + 99),
    /* 错误码整理，先不删除原先的错误码，待全部上完库以后再删除 */
    OAL_ERR_CODE_HMAC_SECURITY_BASE               = 21100,
    OAL_ERR_CODE_HMAC_SECURITY_KEY_TYPE           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 0),
    OAL_ERR_CODE_HMAC_SECURITY_KEY_LEN            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 1),
    OAL_ERR_CODE_HMAC_SECURITY_KEY_ID             = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 2),
    OAL_ERR_CODE_HMAC_SECURITY_CHIPER_TYPE        = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 3),
    OAL_ERR_CODE_HMAC_SECURITY_BUFF_NUM           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 4),
    OAL_ERR_CODE_HMAC_SECURITY_BUFF_LEN           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 5),
    OAL_ERR_CODE_HMAC_SECURITY_WRONG_KEY          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 6),
    OAL_ERR_CODE_HMAC_SECURITY_USER_INVAILD       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 7),
    OAL_ERR_CODE_HMAC_SECURITY_PARAMETERS         = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 8),
    OAL_ERR_CODE_HMAC_SECURITY_AUTH_TYPE          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 9),
    OAL_ERR_CODE_HMAC_SECURITY_CAP                = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 10),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_MFP            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 11),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_BSS            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 12),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_PHY            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 13),
    OAL_ERR_CODE_HMAC_SECURITY_PORT_INVALID       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 14),
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    OAL_ERR_CODE_HMAC_SECURITY_MAC_INVALID        = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 15),
    OAL_ERR_CODE_HMAC_SECURITY_MODE_INVALID       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 16),
    OAL_ERR_CODE_HMAC_SECURITY_LIST_FULL          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 17),
    OAL_ERR_CODE_HMAC_SECURITY_AGING_INVALID      = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 18),
    OAL_ERR_CODE_HMAC_SECURITY_THRESHOLD_INVALID  = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 19),
    OAL_ERR_CODE_HMAC_SECURITY_RESETIME_INVALID   = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 20),
#endif
    OAL_ERR_CODE_HMAC_SECURITY_BUTT               = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 499),

/**************************** wapi 特性 ***********************************/
    OAL_ERR_CODE_WAPI_BASE                          = 21600,
    OAL_ERR_CODE_WAPI_NETBUFF_LEN_ERR               = (OAL_ERR_CODE_WAPI_BASE + 0),
    OAL_ERR_CODE_WAPI_DECRYPT_FAIL                  = (OAL_ERR_CODE_WAPI_BASE + 1),
    OAL_ERR_CODE_WAPI_MIC_CALC_FAIL                 = (OAL_ERR_CODE_WAPI_BASE + 2),
    OAL_ERR_CODE_WAPI_ENRYPT_FAIL                   = (OAL_ERR_CODE_WAPI_BASE + 3),
    OAL_ERR_CODE_WAPI_MIC_CMP_FAIL                  = (OAL_ERR_CODE_WAPI_BASE + 4),

    OAL_ERR_CODE_WAPI_BUTT                          = (OAL_ERR_CODE_WAPI_BASE + 99),
    /********************************* 其它 **********************************/
    /**************************** 11w 特性 ***********************************/
    OAL_ERR_CODE_PMF_BASE                         = 22000,
    OAL_ERR_CODE_PMF_ACTIVE_DOWN                  = (OAL_ERR_CODE_PMF_BASE + 0), /* user的bit_pmf_active开关没有使能开启 */
    OAL_ERR_CODE_PMF_SA_QUERY_REQ_SEND_FAIL       = (OAL_ERR_CODE_PMF_BASE + 1), /* hmac_send_sa_query_req函数发送sa query req操作失败 */
    OAL_ERR_CODE_PMF_DISABLED                     = (OAL_ERR_CODE_PMF_BASE + 2), /* dot11RSNAProtectedManagementFramesActivated 值为0 */
    OAL_ERR_CODE_PMF_SA_QUERY_START_FAIL          = (OAL_ERR_CODE_PMF_BASE + 3), /* hmac_start_sa_query函数返回结果失败 */
    OAL_ERR_CODE_PMF_SA_QUERY_DEL_USER_FAIL       = (OAL_ERR_CODE_PMF_BASE + 4), /* hmac_sa_query_del_user函数,SA query流程删除用户失败 */
    OAL_ERR_CODE_PMF_BIP_AES_CMAC_ENCRYPT_FAIL    = (OAL_ERR_CODE_PMF_BASE + 5), /* oal_crypto_aes_cmac_encrypt函数，AES_CMAC加密失败 */
    OAL_ERR_CODE_PMF_BIP_CRIPTO_FAIL              = (OAL_ERR_CODE_PMF_BASE + 6), /* dmac_bip_crypto函数，bip加密失败 */
    OAL_ERR_CODE_PMF_BIP_DECRIPTO_FAIL            = (OAL_ERR_CODE_PMF_BASE + 7), /* oal_crypto_bip_demic函数，bip解密失败 */
    OAL_ERR_CODE_PMF_IGTK_INDX_FAIL               = (OAL_ERR_CODE_PMF_BASE + 8), /* 给的igtk_index 错误 */
    OAL_ERR_CODE_PMF_VAP_CAP_FAIL                 = (OAL_ERR_CODE_PMF_BASE + 9), /* VAP的mfpc&mfpr设置错误 */
    OAL_ERR_CODE_PMF_VAP_ACTIVE_DOWN              = (OAL_ERR_CODE_PMF_BASE + 10), /* VAP的mib dot11RSNAActived设置为OAL_FALES */
    OAL_ERR_CODE_PMF_IGTK_NOT_EXIST               = (OAL_ERR_CODE_PMF_BASE + 11), /* igtk不存在或者igtk_id值错误 */
    OAL_ERR_CODE_PMF_ALIGN_ERR                    = (OAL_ERR_CODE_PMF_BASE + 12), /* bip加解密过程错误 */
    OAL_ERR_CODE_PMF_REPLAY_ATTAC                 = (OAL_ERR_CODE_PMF_BASE + 13), /* bip重放攻击 */
    OAL_ERR_CODE_PMF_MMIE_ERR                     = (OAL_ERR_CODE_PMF_BASE + 14), /* bip完整性校验检查失败 */
    OAL_ERR_CODE_PMF_NO_PROTECTED_ERROR           = (OAL_ERR_CODE_PMF_BASE + 15), /* PMF使能收到未加密的单播强健管理帧 */

    OAL_ERR_CODE_PMF_BUTT                         = (OAL_ERR_CODE_PMF_BASE + 999),
    /********************************* 其它 **********************************/
    /***************hostapd/wpa_supplicant事件上报和下发特性 *****************/
    OAL_ERR_CODE_CFG80211_BASE               = 23000,
    OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL       = (OAL_ERR_CODE_CFG80211_BASE + 0),  /* skb不足无法存消息头和内容 */
    OAL_ERR_CODE_CFG80211_EMSGSIZE           = (OAL_ERR_CODE_CFG80211_BASE + 1),  /* 消息太长,属性无法填充 */
    OAL_ERR_CODE_CFG80211_MCS_EXCEED         = (OAL_ERR_CODE_CFG80211_BASE + 2),  /* MCS大于32 */
    OAL_ERR_CODE_CFG80211_ENOBUFS            = (OAL_ERR_CODE_CFG80211_BASE + 3),

    OAL_ERR_CODE_CFG80211_BUTT               = (OAL_ERR_CODE_CFG80211_BASE + 999),

    /********************************* OAL **********************************/
    OAL_ERR_CODE_OAL_BASE                    = 24000,

    /**************************** OAL --- 内存池 ****************************/
    OAL_ERR_CODE_OAL_MEM_BASE                = (OAL_ERR_CODE_OAL_BASE + 0),
    OAL_ERR_CODE_OAL_MEM_GET_POOL_FAIL       = (OAL_ERR_CODE_OAL_MEM_BASE + 0),   /* 获取内存池全局指针失败 */
    OAL_ERR_CODE_OAL_MEM_ALLOC_CTRL_BLK_FAIL = (OAL_ERR_CODE_OAL_MEM_BASE + 1),   /* 申请块内存失败 */
    OAL_ERR_CODE_OAL_MEM_SKB_SUBPOOL_ID_ERR  = (OAL_ERR_CODE_OAL_MEM_BASE + 2),   /* 获取netbuf subpool id失败 */
    OAL_ERR_CODE_OAL_MEM_GET_CFG_TBL_FAIL    = (OAL_ERR_CODE_OAL_MEM_BASE + 3),   /* 获取内存池配置信息失败 */
    OAL_ERR_CODE_OAL_MEM_EXCEED_MAX_LEN      = (OAL_ERR_CODE_OAL_MEM_BASE + 4),   /* 内存块最大长度超过限制 */
    OAL_ERR_CODE_OAL_MEM_EXCEED_SUBPOOL_CNT  = (OAL_ERR_CODE_OAL_MEM_BASE + 5),   /* 子内存池个数超过限制 */
    OAL_ERR_CODE_OAL_MEM_DOG_TAG             = (OAL_ERR_CODE_OAL_MEM_BASE + 6),   /* 内存被踩 */
    OAL_ERR_CODE_OAL_MEM_ALREADY_FREE        = (OAL_ERR_CODE_OAL_MEM_BASE + 7),   /* 释放了一块已经被释放的内存 */
    OAL_ERR_CODE_OAL_MEM_USER_CNT_ERR        = (OAL_ERR_CODE_OAL_MEM_BASE + 8),   /* 释放一块引用计数为0的内存 */
    OAL_ERR_CODE_OAL_MEM_EXCEED_TOTAL_CNT    = (OAL_ERR_CODE_OAL_MEM_BASE + 9),   /* 可用内存块数目超过整个子内存池总内存块数 */
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    /**************************** OAL --- 事件 ****************************/
    OAL_ERR_CODE_OAL_EVENT_BASE              = (OAL_ERR_CODE_OAL_BASE + 100),
    OAL_ERR_CODE_OAL_EVENT_Q_EMPTY           = (OAL_ERR_CODE_OAL_EVENT_BASE + 0),
#endif
    OAL_ERR_CODE_OAL_BUTT                    = (OAL_ERR_CODE_OAL_BASE + 999),

    /********************************* OAM **********************************/
    OAL_ERR_CODE_OAM_BASE                    = 25000,

    /**************************** OAM --- event *****************************/
    OAL_ERR_CODE_OAM_EVT_BASE               = (OAL_ERR_CODE_OAM_BASE + 0),
    OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED    = (OAL_ERR_CODE_OAM_EVT_BASE + 0),    /* 用户索引超过最大值 */
    OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID  = (OAL_ERR_CODE_OAM_EVT_BASE + 1),    /* 既不是发送流程，也不是接收流程 */
    OAL_ERR_CODE_OAM_EVT_FR_HDR_LEN_INVALID = (OAL_ERR_CODE_OAM_EVT_BASE + 2),    /* 帧头长度异常 */
    OAL_ERR_CODE_OAM_EVT_FR_LEN_INVALID     = (OAL_ERR_CODE_OAM_EVT_BASE + 3),    /* 帧体(包括帧头)长度异常 */
    OAL_ERR_CODE_OAM_EVT_DSCR_LEN_INVALID   = (OAL_ERR_CODE_OAM_EVT_BASE + 4),    /* 描述符长度异常 */

    OAL_ERR_CODE_OAM_BUTT                    = (OAL_ERR_CODE_OAM_BASE + 999),

    /********************************* KeepAlive **********************************/
    OAL_ERR_CODE_KEEPALIVE_BASE             = 26000,
    /**************************** KeepAlive --- event *****************************/
    OAL_ERR_CODE_KEEPALIVE_CONFIG_VAP       = (OAL_ERR_CODE_KEEPALIVE_BASE + 1),
    OAL_ERR_CODE_KEEPALIVE_BIG_INTERVAL     = (OAL_ERR_CODE_KEEPALIVE_BASE + 2),
    OAL_ERR_CODE_KEEPALIVE_SMALL_LIMIT      = (OAL_ERR_CODE_KEEPALIVE_BASE + 3),
    OAL_ERR_CODE_KEEPALIVE_INVALID_VAP      = (OAL_ERR_CODE_KEEPALIVE_BASE + 4),
    OAL_ERR_CODE_KEEPALIVE_PTR_NULL         = (OAL_ERR_CODE_KEEPALIVE_BASE + 5),

    OAL_ERR_CODE_KEEPALIVE_BUTT             = (OAL_ERR_CODE_KEEPALIVE_BASE + 999),


    /******* PROXY ARP特性 COMP--skb处理完成; INCOMP--skb没有处理完成，留待后续处理******/
    OAL_ERR_CODE_PROXY_ARP_BASE                     = 27000,
    OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 0), /* 接收到的SKB异常 */
    OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP  = (OAL_ERR_CODE_PROXY_ARP_BASE + 1), /* GARP源地址非本BSS */
    OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 2), /* GARP源地址学习成功 */
    OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 3), /* 回 arp reply到本BSS */
    OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 4), /* 回 arp reply到ETH */
    OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 5), /* 创建SKB失败 */
    OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 6), /* 接收到的SKB异常 */
    OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 7), /* 接收到的SKB异常 */
    OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 8), /* 接收到组播的arp reply */
    OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP             = (OAL_ERR_CODE_PROXY_ARP_BASE + 9), /* 接收到arp reply，转发 */
    OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 10),/* 不是arp req或者reply */

    OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 11),/* 通过NS学习地址，ap发现该ns的源mac不存在 */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 12),/* 通过NS学习地址，ap发现该ipv6地址已经记录在hash中 */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 13),/* 通过NS学习地址正常 */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 14),/* 通过NS学习地址失败 */
    OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 15),/* 从NS的icmpv6 opt中获取ll失败 */
    OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 16),/* NS icmpv6中的target ipv6地址不在hash表中*/
    OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP    = (OAL_ERR_CODE_PROXY_ARP_BASE + 17),/* 构造NA失败 */
    OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP      = (OAL_ERR_CODE_PROXY_ARP_BASE + 18),/* 收到NS后，AP正常回复NA到BSS */
    OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP             = (OAL_ERR_CODE_PROXY_ARP_BASE + 19),/* 非法的NA*/
    OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 20),/* 从组播响应的NA中 icmpv6 opt获取ll失败*/
    OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 21),/* 从单播响应的NA中 icmpv6 opt获取ll失败*/
    OAL_ERR_CODE_PROXY_ND_NA_DUP_ADDR_INCOMP        = (OAL_ERR_CODE_PROXY_ARP_BASE + 22),/* NA中携带的ipv6地址冲突 */
    OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 23),/* NA中S标志为0 */
    OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 24),/* NA中S标志为1 */
    OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 25),/* 没有携带icmpv6 */
    OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP    = (OAL_ERR_CODE_PROXY_ARP_BASE + 26),/* 不是NS或者NA */
    OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 27),/* arp中的target ipv4地址不在hash表中*/
    OAL_ERR_CODE_PROXY_OTHER_INCOMP                 = (OAL_ERR_CODE_PROXY_ARP_BASE + 28),/* 不属于proxy 处理的帧 */
    OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP      = (OAL_ERR_CODE_PROXY_ARP_BASE + 29),/* 收到NS后，AP正常回复NA到ETH */
    OAL_ERR_CODE_PROXY_ARP_BUTT                     = (OAL_ERR_CODE_PROXY_ARP_BASE + 499),

    /******* PSM特性******/
    OAL_ERR_CODE_PSM_BASE                           = 27500,
    OAL_ERR_CODE_PS_QUEUE_OVERRUN                   = (OAL_ERR_CODE_PSM_BASE + 0), /* ps队列满 */

    /********************************* 队列模块 **********************************/
    OAL_ERR_CODE_QUEUE_BASE                             = 28000,
    OAL_ERR_CODE_QUEUE_CNT_ZERO                         = (OAL_ERR_CODE_QUEUE_BASE + 0),    /* 队列为空 */

    /********************************* SWP CBB模块 *******************************/
    OAL_ERR_CODE_SWP_CBB_BASE                           = 28100,
    OAL_ERR_CODE_SWP_CBB_ALREADY_ACTIVE                 = (OAL_ERR_CODE_SWP_CBB_BASE + 0),  /* 当前CBB接口已经激活 */
    OAL_ERR_CODE_SWP_CBB_INT_REGISTER_FAIL              = (OAL_ERR_CODE_SWP_CBB_BASE + 1),  /* 中断处理函数注册失败 */
    OAL_ERR_CODE_SWP_CBB_LENGTH_INVALID                 = (OAL_ERR_CODE_SWP_CBB_BASE + 2),  /* 数据长度无效 */
    OAL_ERR_CODE_SWP_CBB_BUFFUR_FULL                    = (OAL_ERR_CODE_SWP_CBB_BASE + 3),  /* SWP CBB RX或TX缓存已满 */

    /********************************* Type A模块 ********************************/
    OAL_ERR_CODE_TYPE_A_BASE                            = 28200,
    OAL_ERR_CODE_UID_ERR                                = (OAL_ERR_CODE_TYPE_A_BASE  + 0),  /* UID 出错  */
    OAL_ERR_TIME_OUT_TIMES_BEYOND                       = (OAL_ERR_CODE_TYPE_A_BASE  + 1),  /* 超时次数超出 */
    OAL_ERR_LEVEL_BEYOND                                = (OAL_ERR_CODE_TYPE_A_BASE  + 2),  /* 级联次数超出 */

    /********************************* Type A LISTEN NFC-DEP模块 ********************************/
    OAL_ERR_CODE_NFC_DEP_LISTEN_BASE                    = 28300,

    /********************************* Type A POLL NFC-DEP模块 ********************************/
    OAL_ERR_CODE_NFC_DEP_POLL_BASE                      = 28400,

    /********************************* NFC-DEP协议模块 ********************************/
    OAL_ERR_CODE_NFC_DEP_BASE                           = 28500,
    OAL_ERR_CODE_NFC_DEP_FRAME_TYPE_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 0),  /* 帧类型错误 */
    OAL_ERR_CODE_NFC_DEP_FRAME_OPCODE_ERR               = (OAL_ERR_CODE_NFC_DEP_BASE + 1),  /* 帧操作码错误 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DID_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 2),  /* DID 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_GEN_INFO_FLAG_ERR       = (OAL_ERR_CODE_NFC_DEP_BASE + 3),  /* GEN INFO flag 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DSI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 4),  /* DSI 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DRI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 5),  /* DRI 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_FSL_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 6),  /* FSL 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_MI_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 7),  /* MI 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_NAD_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 8),  /* NAD 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_PNI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 9),  /* PNI 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_PAYLOAD_ERR             = (OAL_ERR_CODE_NFC_DEP_BASE + 10), /* PAYLOAD 出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_SENS_RES_ERR            = (OAL_ERR_CODE_NFC_DEP_BASE + 11), /* sens_res  出错 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_TAG1_PLT_SUCC           = (OAL_ERR_CODE_NFC_DEP_BASE + 12), /* sens_res 解析，走tag1防冲突处理流程 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CL_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 13), /* SDD_REQ 级联值错误 */
    OAL_ERR_CODE_NFC_DEP_NFCID_ERR                      = (OAL_ERR_CODE_NFC_DEP_BASE + 14), /* NFCID错误 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CASCADE_ERR             = (OAL_ERR_CODE_NFC_DEP_BASE + 15), /* Cascade标识错误 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_BCC_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 16), /* BCC校验错误 */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CT_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 17), /* CT位错误 */

    /********************************* NFC CBB 模块**********************************/
    OAL_ERR_CODE_NFC_CBB_BASE                           = 28600,
    OAL_ERR_CODE_NFC_RX_CRC_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 0),  /* CRC 错误 */
    OAL_ERR_CODE_NFC_RX_PTY_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 1),  /* PTY 错误 */
    OAL_ERR_CODE_NFC_RX_BCC_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 2),  /* BCC 错误 */
    OAL_ERR_CODE_NFC_CRPLL_UNLOCK_FLAG_ERR              = (OAL_ERR_CODE_NFC_CBB_BASE + 3),  /* CRPLL 失锁 错误 */
    OAL_ERR_CODE_NFC_LSTNA_FALLING_FALL_ERR             = (OAL_ERR_CODE_NFC_CBB_BASE + 4),  /* FAILING EDGE 错误*/
    OAL_ERR_CODE_NFC_RX_BUFF_ERR                        = (OAL_ERR_CODE_NFC_CBB_BASE + 5),  /* BUFF 错误 */
    OAL_ERR_CODE_NFC_RX_BUFF_FRAME_TYPE_ERR             = (OAL_ERR_CODE_NFC_CBB_BASE + 6),  /* FRAME TYPE 错误 */
    OAL_ERR_CODE_CBB_INT_REGISTER_FAIL                  = (OAL_ERR_CODE_NFC_CBB_BASE + 7),  /* INT_REGISTER_FAIL 错误 */
    OAL_ERR_CODE_CBB_LSTN_RX2TX_TO                      = (OAL_ERR_CODE_NFC_CBB_BASE + 8),  /* Listen模式，数据发送超时 */
    OAL_ERR_CODE_NFC_RX_LSTN_RATE_ERR                   = (OAL_ERR_CODE_NFC_CBB_BASE + 9),  /* type f Listen模式，接收数据对应的数据速率错误 */

    /********************************* 调度模块 **********************************/
    OAL_ERR_CODE_SCHED_BASE                             = 28700,
    OAL_ERR_CODE_SCHED_FSM_EXCEPT_FUN_NULL              = (OAL_ERR_CODE_SCHED_BASE + 0),    /* 状态机异常处理函数为NULL */
    OAL_ERR_CODE_SCHED_FSM_STA_TAB_NULL                 = (OAL_ERR_CODE_SCHED_BASE + 1),    /* 状态机状态表为NULL或无内容 */
    OAL_ERR_CODE_SCHED_PUSH_QUEUE_ID_INVALID            = (OAL_ERR_CODE_SCHED_BASE + 2),    /* 插入队列ID无效 */

    /********************************* Tag4B模块 **********************************/
    OAL_ERR_CODE_TAG4B_BASE                             = 28800,
    OAL_ERR_CODE_TAG4B_NOT_COMPLIANT_14443              = (OAL_ERR_CODE_TAG4B_BASE + 0),    /* 不兼容14443协议错误 */
    OAL_ERR_CODE_TAG4B_OPCODE_ERR                       = (OAL_ERR_CODE_TAG4B_BASE + 1),    /* ATTRIB操作码错误 */
    OAL_ERR_CODE_TAG4B_TYPE_B_DID_ERR                   = (OAL_ERR_CODE_TAG4B_BASE + 2),    /* DID错误 */
    OAL_ERR_CODE_TAG4B_NFCID_ERR                        = (OAL_ERR_CODE_TAG4B_BASE + 3),    /* NFCID错误 */
    OAL_ERR_CODE_TAG4B_BR_ERR                           = (OAL_ERR_CODE_TAG4B_BASE + 4),    /* 速率错误 */
    OAL_ERR_CODE_TAG4B_PARAM3_MSB_ERR                   = (OAL_ERR_CODE_TAG4B_BASE + 5),    /* PARAM3 b8-b4不为0 */

    /********************************* ISO-DEP协议模块 **********************************/
    OAL_ERR_CODE_ISO_DEP_BASE                           = 28900,
    OAL_ERR_CODE_ISO_DEP_IBLOCK_RETRY_ERR               = (OAL_ERR_CODE_ISO_DEP_BASE + 0),  /* IBLOCK重传超过最大值错误 */
    OAL_ERR_CODE_ISO_DEP_OVER_FSC_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 1),  /* 发送接收block长度大于FSC错误 */
    OAL_ERR_CODE_ISO_DEP_OVER_FSD_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 2),  /* 发送接收block长度大于FSD错误 */
    OAL_ERR_CODE_ISO_DEP_BLOCK_TYPE_ERR                 = (OAL_ERR_CODE_ISO_DEP_BASE + 3),  /* BLOCK类型错误 */
    OAL_ERR_CODE_ISO_DEP_DID_ERR                        = (OAL_ERR_CODE_ISO_DEP_BASE + 4),  /* DID错误 */
    OAL_ERR_CODE_ISO_DEP_NAD_ERR                        = (OAL_ERR_CODE_ISO_DEP_BASE + 5),  /* NAD错误 */
    OAL_ERR_CODE_ISO_DEP_BN_ERR                         = (OAL_ERR_CODE_ISO_DEP_BASE + 6),  /* BLOCK NUM错误 */
    OAL_ERR_CODE_ISO_DEP_ACK_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 7),  /* R_ACK重传超过最大值错误*/
    OAL_ERR_CODE_ISO_DEP_NAK_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 8),  /* R_NAK重传超过最大值错误*/
    OAL_ERR_CODE_ISO_DEP_WTX_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 9),  /* S_WTX重传超过最大值错误*/
    OAL_ERR_CODE_ISO_DEP_DSL_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 10), /* S_DSL重传超过最大值错误*/
    OAL_ERR_CODE_ISO_DEP_PCB_FIX_NUM_ERR                = (OAL_ERR_CODE_ISO_DEP_BASE + 11), /* PBC中fix num错误 */
    OAL_ERR_CODE_ISO_DEP_WTXM_ERR                       = (OAL_ERR_CODE_ISO_DEP_BASE + 12), /* WTXM错误 */
    OAL_ERR_CODE_ISO_DEP_PROTOCOL_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 13), /* 协议错误 */
    OAL_ERR_CODE_ISO_DEP_UNRECOVERABLE_EXCEPTIOM        = (OAL_ERR_CODE_ISO_DEP_BASE + 14), /* 不可恢复异常 */

    /********************************* TYPE B协议模块 **********************************/
    OAL_ERR_CODE_TYPE_B_BASE                            = 29000,
    OAL_ERR_CODE_CUR_SLOT_NUM_ERR                       = (OAL_ERR_CODE_TYPE_B_BASE + 1),   /* 时间槽数错误 */
    OAL_ERR_CODE_SLOT_NUM_ERR                           = (OAL_ERR_CODE_TYPE_B_BASE + 2),   /* 时间槽数量错误 */
    OAL_ERR_CODE_TYPE_B_SENSB_RES_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_B_BASE + 3),   /* SENSB_RES操作码错误 */
    OAL_ERR_CODE_TYPE_B_CR_AFI_ERR                      = (OAL_ERR_CODE_TYPE_B_BASE + 4),   /* AFI不一致的错误 */
    OAL_ERR_CODE_DID_OVER_ERR                           = (OAL_ERR_CODE_TYPE_B_BASE + 5),   /* did值超出范围 */
    OAL_ERR_CODE_FSD_FSC_TR0_TR1_TR2_VALUE_ERR          = (OAL_ERR_CODE_TYPE_B_BASE + 6),   /* FSD或者FSC取值错误 */
    OAL_ERR_CODE_MBL_ERR                                = (OAL_ERR_CODE_TYPE_B_BASE + 7),   /* MBL取值不正确 */
    /********************************* TAG4A模块 **********************************/
    OAL_ERR_CODE_TAG4A_BASE                             = 29100,
    OAL_ERR_CODE_TAG4A_ATS_TL_ERR                       = (OAL_ERR_CODE_SCHED_BASE + 0),    /* ATS TL错误 */
    OAL_ERR_CODE_TAG4A_PPS_RES_ERR                      = (OAL_ERR_CODE_SCHED_BASE + 1),    /* PPS_RES错误 */
    OAL_ERR_CODE_TAG4A_PPS_DID_ERR                      = (OAL_ERR_CODE_SCHED_BASE + 2),    /* PPS_RES DID错误 */
    OAL_ERR_CODE_TAG4A_RATS_OPCODE_ERR                  = (OAL_ERR_CODE_SCHED_BASE + 3),    /* RATS 帧头错误 */
    OAL_ERR_CODE_TAG4A_RATS_DID_ERR                     = (OAL_ERR_CODE_SCHED_BASE + 4),    /* RATS DID错误 */
    /********************************* TYPE F协议模块 **********************************/
    OAL_ERR_CODE_TYPE_F_BASE                            = 29200,
    OAL_ERR_CODE_TYPE_F_SENSF_RES_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_F_BASE + 1),   /* SENSF_RES操作码错误 */
    OAL_ERR_CODE_TYPE_F_SENSF_REQ_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_F_BASE + 2),   /* SENSF_REQ操作码错误 */
    OAL_ERR_CODE_TYPE_F_SENSF_RES_WITH_RD_ERR           = (OAL_ERR_CODE_TYPE_F_BASE + 3),   /* SENSF_RES带有RD错误 */
    /********************************* TAG3协议模块 **********************************/
    OAL_ERR_CODE_TAG3_BASE                              = 29300,
    OAL_ERR_CODE_TAG3_CUP_CMD_OPCODE_ERR                = (OAL_ERR_CODE_TAG3_BASE + 1),     /* CUP_CMD帧头错误 */
    OAL_ERR_CODE_TAG3_CUP_RES_OPCODE_ERR                = (OAL_ERR_CODE_TAG3_BASE + 2),     /* CUP_RES帧头错误 */
    OAL_ERR_CODE_TAG3_PAYLOAD_ERR                       = (OAL_ERR_CODE_TAG3_BASE + 3),     /* PAYLOAD错误 */

    /********************************* NCI协议RF DISCOVERY模块 **********************************/
    OAL_ERR_CODE_RF_DISCOVERY_BASE                      = 29400,
    OAL_ERR_CODE_RF_DISCOVERY_TECH_TYPE_ERR             = (OAL_ERR_CODE_RF_DISCOVERY_BASE + 1), /* 技术类型错误 */
    OAL_ERR_CODE_RF_DISCOVERY_MODE_ERR                  = (OAL_ERR_CODE_RF_DISCOVERY_BASE + 2), /* 配置的模式错误 */

    /********************************* TECH DETECT ACT模块 **********************************/
    OAL_ERR_CODE_TECH_DETECT_ACT_BASE                   = 29500,
    OAL_ERR_CODE_TECH_DETECT_ACT_TECH_TYPE_ERR          = (OAL_ERR_CODE_TECH_DETECT_ACT_BASE + 1), /* 技术类型都不尽兴侦测的错误 */

    /********************************* NCI协议模块**********************************/
    OAL_ERR_CODE_NCI_BASE                               = 29600,
    OAL_ERR_CODE_NCI_CONFIG_PARAM_INVALID               = (OAL_ERR_CODE_NCI_BASE + 1),      /* 无效的参数 */
    OAL_ERR_CODE_NCI_UNKNOWN_MSG                        = (OAL_ERR_CODE_NCI_BASE + 2),      /* 不能识别的命令 */
    OAL_ERR_CORE_NCI_PAYLOAD_ERR                        = (OAL_ERR_CODE_NCI_BASE + 3),      /* PAYLOAD错误 */
    OAL_ERR_CODE_NCI_DISPATCH_FUN_NULL                  = (OAL_ERR_CODE_NCI_BASE + 4),      /* Dispatch中的函数为NULL */
    OAL_ERR_CODE_NCI_VAL_LEN_TOO_SHORT                  = (OAL_ERR_CODE_NCI_BASE + 5),      /* 存储参数的空间不足 */
    OAL_ERR_CODE_NCI_RECV_MSG_TOO_BIG                   = (OAL_ERR_CODE_NCI_BASE + 6),      /* 接收的消息组装后存不下 */
    OAL_ERR_CODE_NCI_PARAM_ID_TOO_BIG                   = (OAL_ERR_CODE_NCI_BASE + 7),      /* 参数的ID超出范围 */
    OAL_ERR_CODE_NCI_GID_OID_INVALID                    = (OAL_ERR_CODE_NCI_BASE + 8),      /* NCI消息的GID或OID无效 */
    OAL_ERR_CODE_NCI_PACKET_INVALID                     = (OAL_ERR_CODE_NCI_BASE + 9),      /* 接收到的NCI Packet是无效的 */

    /********************************* SHDLC协议模块**********************************/
    OAL_ERR_CODE_SHDLC_BASE                             = 29700,
    OAL_ERR_RECV_FRAME_TYPE_DIF_FSM                     = (OAL_ERR_CODE_SHDLC_BASE + 1),    /* 接收到的帧类型与当前状态不符 */
    OAL_ERR_RECV_RSET_LENGTH                            = (OAL_ERR_CODE_SHDLC_BASE + 2),    /* 接收到的RSET帧的payload长度超出限定范围 */
    OAL_ERR_RECV_FRAME_TYPE_UNKNOWN                     = (OAL_ERR_CODE_SHDLC_BASE + 3),    /* 接收到帧的类型未知 */
    OAL_ERR_RECV_I_FRAME_LENGTH                         = (OAL_ERR_CODE_SHDLC_BASE + 4),    /* 接收到帧的I帧的payload长度超出限定范围 */

/* #ifdef _PRE_WLAN_FEATURE_ROAM */
    /********************************* 漫游模块**********************************/
    OAL_ERR_CODE_ROAM_BASE                              = 29800,
    OAL_ERR_CODE_ROAM_DISABLED                          = (OAL_ERR_CODE_ROAM_BASE + 0),      /* 功能未使能   */
    OAL_ERR_CODE_ROAM_INVALID_VAP                       = (OAL_ERR_CODE_ROAM_BASE + 1),      /* 无效的VAP    */
    OAL_ERR_CODE_ROAM_INVALID_USER                      = (OAL_ERR_CODE_ROAM_BASE + 2),      /* 无效的USER   */
    OAL_ERR_CODE_ROAM_NO_VALID_BSS                      = (OAL_ERR_CODE_ROAM_BASE + 3),      /* 无可用的BSS  */
    OAL_ERR_CODE_ROAM_STATE_UNEXPECT                    = (OAL_ERR_CODE_ROAM_BASE + 4),      /* 状态错误     */
    OAL_ERR_CODE_ROAM_EVENT_UXEXPECT                    = (OAL_ERR_CODE_ROAM_BASE + 5),      /* 事件错误     */
    OAL_ERR_CODE_ROAM_FRAMER_SUB_TYPE                   = (OAL_ERR_CODE_ROAM_BASE + 6),      /* 帧类型错误   */
    OAL_ERR_CODE_ROAM_FRAMER_LEN                        = (OAL_ERR_CODE_ROAM_BASE + 7),      /* 帧长度错误   */
    OAL_ERR_CODE_ROAM_INVALID_VAP_STATUS                = (OAL_ERR_CODE_ROAM_BASE + 8),      /* 无效的VAP状态*/
    OAL_ERR_CODE_ROAM_HANDSHAKE_FAIL                    = (OAL_ERR_CODE_ROAM_BASE + 9),      /* 秘钥交互失败*/
/* #endif //_PRE_WLAN_FEATURE_ROAM */

    /********************************* HW RESET 模块*************************************/
    OAL_ERR_CODE_HW_RESET_BASE                          = 30600,
    OAL_ERR_CODE_HW_RESET_PHY_SAVE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 0),
    OAL_ERR_CODE_HW_RESET_MAC_SAVE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 1),
    OAL_ERR_CODE_HW_RESET_MAC_SAVE_SIZELIMIT            = (OAL_ERR_CODE_HW_RESET_BASE + 2),
    OAL_ERR_CODE_HW_RESET_PHY_SAVE_SIZELIMIT            = (OAL_ERR_CODE_HW_RESET_BASE + 3),
    OAL_ERR_CODE_HW_RESET_TX_QUEUE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 4),    /* reset流程中申请tx fake queue失败 */

    OAL_FAIL,                                                                   /* 通用异常，仅在以上异常无法匹配填写此值 */

    OAL_ERR_CODE_BUTT
}oal_err_code_enum;
typedef oal_uint32 oal_err_code_enum_uint32;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 消息头定义
*****************************************************************************/


/*****************************************************************************
  7 消息定义
*****************************************************************************/


/*****************************************************************************
  8 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  9 UNION定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_types.h */

