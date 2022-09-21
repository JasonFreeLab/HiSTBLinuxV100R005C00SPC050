/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_otp.h
  Version       : Initial Draft
  Author        : Hisilicon otp software group
  Created       : 2016/10/9
  Description   :
*******************************************************************************/
/**
 * \file
 * \brief Describes the information about the otp module.
          CNcomment:提供 OTP 模块的相关信息 CNend
 */
#ifndef __HI_UNF_OTP_H__
#define __HI_UNF_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/** CA VendorID */
typedef enum
{
    HI_UNF_OTP_VENDORID_COMMON     = 0x00,        /**<No-Advcance CA chipset, Marked with 0*/
    HI_UNF_OTP_VENDORID_NAGRA      = 0x01,        /**<NAGRA  Chipse, Marked with R*/
    HI_UNF_OTP_VENDORID_IRDETO     = 0x02,        /**<IRDETO Chipset, Marked with I*/
    HI_UNF_OTP_VENDORID_CONAX      = 0x03,        /**<CONAX Chipset, Marked with C*/
    HI_UNF_OTP_VENDORID_NDS        = 0x04,        /**<NDS Chipset*/
    HI_UNF_OTP_VENDORID_SUMA       = 0x05,        /**<SUMA Chipset, Marked with S*/
    HI_UNF_OTP_VENDORID_NOVEL      = 0x06,        /**<NOVEL Chipset, Marked with Y*/
    HI_UNF_OTP_VENDORID_VERIMATRIX = 0x07,        /**<VERIMATRIX Chipset, Marked with M*/
    HI_UNF_OTP_VENDORID_CTI        = 0x08,        /**<CTI Chipset, Marked with T*/
    HI_UNF_OTP_VENDORID_SAFEVIEW   = 0x09,        /**<SAFEVIEW CA Chipset*/
    HI_UNF_OTP_VENDORID_LATENSE    = 0x0a,        /**<LATENSE CA Chipset*/
    HI_UNF_OTP_VENDORID_SH_TELECOM = 0x0b,        /**<SH_TELECOM CA Chipset*/
    HI_UNF_OTP_VENDORID_DCAS       = 0x0c,        /**<DCAS CA Chipset*/
    HI_UNF_OTP_VENDORID_VIACCESS   = 0x0d,        /**<VIACCESS CA Chipset*/
    HI_UNF_OTP_VENDORID_BUTT
} HI_UNF_OTP_VENDORID_E;

/** FLASH device types*/
typedef enum
{
    HI_UNF_OTP_FLASH_TYPE_SPI     = 0,    /**<SPI flash*/
    HI_UNF_OTP_FLASH_TYPE_NAND,           /**<nand flash*/
    HI_UNF_OTP_FLASH_TYPE_NOR,            /**<nor flash*/
    HI_UNF_OTP_FLASH_TYPE_EMMC,           /**<eMMC*/
    HI_UNF_OTP_FLASH_TYPE_SPI_NAND,       /**<spi_nand flash*/
    HI_UNF_OTP_FLASH_TYPE_SD,             /**<FSD/TSD flash*/
    HI_UNF_OTP_FLASH_TYPE_BUTT
} HI_UNF_OTP_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum
{
    HI_UNF_OTP_JTAG_MODE_OPEN     = 0,
    HI_UNF_OTP_JTAG_MODE_PROTECT,
    HI_UNF_OTP_JTAG_MODE_CLOSED,
    HI_UNF_OTP_JTAG_MODE_BUTT
} HI_UNF_OTP_JTAG_MODE_E;

/** Rootkey type*/
typedef enum
{
    HI_UNF_OTP_OEM_ROOTKEY        = 0,
    HI_UNF_OTP_HDCP_ROOTKEY,
    HI_UNF_OTP_STB_ROOTKEY,
    HI_UNF_OTP_SW_ROOTKEY,
    HI_UNF_OTP_STBTA_ROOTKEY,

} HI_UNF_OTP_ROOTKEY_E;

#define OTP_FIELD_VALUE_MAX_LEN 1024
#define OTP_FIELD_NAME_MAX_LEN 32
typedef struct
{
    HI_BOOL bBurn;
    HI_CHAR aszFieldName[OTP_FIELD_NAME_MAX_LEN]; //32
    HI_U32 u32ValueLen;
    HI_U8 au8Value[OTP_FIELD_VALUE_MAX_LEN]; //4
    HI_BOOL bLock;
}HI_UNF_OTP_BURN_PV_ITEM_S;


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

#define HI_UNF_OTP_Open(HI_VOID) HI_UNF_OTP_Init(HI_VOID)
#define HI_UNF_OTP_Close(HI_VOID) HI_UNF_OTP_DeInit(HI_VOID)

/**
\brief Initializes the otp module. CNcomment:初始化OTP模块 CNend
\attention \n
Before calling other functions in this file, you must call this application programming interface (API).
CNcomment 在调用OTP模块其他接口前，要求首先调用本接口 CNend
\param N/A
\retval ::HI_SUCCESS  Success.   CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.       CNcomment:API系统调用失败 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_Init(HI_VOID);

/**
\brief Deinitializes the otp module. CNcomment:去初始化OTP设备 CNend
\attention \n
N/A
\param N/A                                        CNcomment:无。 CNend
\retval ::HI_SUCCESS  Success.   CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.       CNcomment:API系统调用失败 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_DeInit(HI_VOID);


/**
\brief Set customer key, the customer key is used by the customer to encrypt some private data.
\brief CNcomment:设置customer key，customer key由客户自己定义，且自定义用途。 CNend
\attention \n
N/A
\param[in] pKey:  Customer key to be written to otp.                    CNcomment:Customer key的值，待写入OTP。 CNend
\param[in] u32KeyLen:  The length of customer key, must be 16bytes.     CNcomment:Customer key的长度，必须为16字节。           CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);

/**
\brief Get customer key, the customer key is used by the customer to encrypt some private data.
\brief CNcomment:获取customer key。 CNend
\attention \n
N/A
\param[in] pKey:Buffer to store the customer key read from otp.     CNcomment:存储customer key的buffer。 CNend
\param[in] u32KeyLen:The length of buffer, must be 16bytes.             CNcomment:customer key 的长度，必须为16字节。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);


/**
\brief Set stb private data, the stb private data is used by the customer to set some private data.
\brief CNcomment:设置客户私有数据。 CNend
\attention \n
N/A
\param[in] u32Offset:  The offset to set the private data, should be between 0 and 15.  CNcomment:设置stbprivData的偏移，必须为0~15之间。 CNend
\param[in] u8Data:  The private data to be set.                         CNcomment:需要设置的值。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);

/**
\brief Get stb private data, the stb private data is used by the customer to set some private data.
\brief CNcomment:获取客户私有数据。 CNend
\attention \n
N/A
\param[in] u32Offset:  The offset to get the private data, should be between 0 and 15.  CNcomment:获取stbprivData的偏移，必须为0~15之间。 CNend
\param[out] pu8Data:  The data read from otp.                           CNcomment:获取的值。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);

/**
\brief burn chipset to normal chipset CNcomment:将芯片烧写成普通芯片 CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID);

/**
\brief Burn nomal chipset to secure chipset
\brief CNcomment:将普通芯片烧写成安全芯片。 CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID);

/**
\brief Get idword lock status CNcomment:获取芯片内部IDWord锁定标志位状态 CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to IDWord lock status. CNcomment:指针类型，锁状态信息 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);
/**
\brief  Set hdcp root key to otp, 16bytes length.
\brief CNcomment:向芯片内部写入hdcp root key，必须为16字节长。 CNend
\attention \n
N/A
\param[in] pu8RootKey:  Set hdcp root key to otp.                   CNcomment设置hdcp root key到OTP。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_WriteHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen);

/**
\brief  Get hdcp root key from otp, 16bytes length.
\brief CNcomment:读取芯片内部设置的hdcp root key，必须为16字节长。 CNend
\attention \n
N/A
\param[out] pu8RootKey:  Point to hdcp root key from otp.               CNcomment:从OTP中获取hdcp root key。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_ReadHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen);

/**
\brief  Lock hdcp root key in otp.
\brief CNcomment:锁定芯片内部设置的hdcp root key。锁定后，hdcp root key将不可被读取。 CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_LockHdcpRootKey(HI_VOID);

/**
\brief  Get hdcp root Key lock flag.
\brief CNcomment:读取芯片内部设置的hdcp root key的锁定标志位。 CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to hdcp root key lock flag from otp.     CNcomment:指向获取到的标志位。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetHdcpRootKeyLockFlag(HI_BOOL *pbLock);

/**
\brief Set stb root key to otp.
\brief CNcomment:向芯片内部设置stb root key。 CNend
\attention \n
N/A
\param[in] u8StbRootKey:  Point to stb root key value.                  CNcomment:Stb root key的值。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_WriteStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen);

/**
\brief Get stb root key from otp.
\brief CNcomment:读取芯片内部设置的stb root key。 CNend
\attention \n
N/A
\param[out] pu8RootKey:  Point to stb root key from otp.                CNcomment:只想获取到的Stb root key。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_ReadStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen);

/**
\brief Lock stb root key in otp.
\brief CNcomment:锁住芯片内部设置的stb root key。锁定后，stb root key将不可被读取。 CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_LockStbRootKey(HI_VOID);

/**
\brief Get stb root Key lock flag
\brief CNcomment:获取芯片内部stb root key的锁定标志位。 CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to stb root key lock flag from otp.      CNcomment:指向获取到的标志位。 CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:API系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:API系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetStbRootKeyLockFlag(HI_BOOL *pbLockFlag);


/**
\brief Get CA Vendor ID. CNcomment:获取高安厂商标识 CNend
\attention \n
N/A
\param[out] penVendorID:  CA VendorID. CNcomment:高安厂商标识 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetVendorID(HI_UNF_OTP_VENDORID_E *penVendorID);

/**
\brief Get the serial number of the STB. CNcomment:获取机顶盒序列号 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pu8StbSn serial number of the STB. CNcomment:指针类型，机顶盒序列号 CNend
\param[in/out] pu32Len point to the length of serial number of the STB, current is 4. CNcomment:指针类型，机顶盒序列号长度，当前是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_OTP_GetStbSN(HI_U8 *pu8StbSN, HI_U32 *pu32Len);

/**
\brief Set the serial number of the STB. CNcomment:设置机顶盒序列号 CNend
\attention \n
The serial number of the STB is set before delivery. The serial number can be set once only and takes effects after the STB restarts.
CNcomment:在机顶盒出厂时设置，仅支持设置一次，设置后重启生效 CNend
\param[in] pu8StbSn point to serial number of the STB. CNcomment:指针类型，机顶盒序列号 CNend
\param[in] u32Len The length of serial number of the STB, current is 4. CNcomment:指针类型，机顶盒序列号长度，当前是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:重复设置 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetStbSN(HI_U8 *pu8StbSN, HI_U32 u32Len);

/**
\brief set the type of flash memory for security startup. CNcomment:指定安全启动的Flash类型 CNend
\attention N/A
\param[in]  enFlashType Type of the flash memory for security startup. CNcomment: 启动的Flash类型 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:重复设置 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType);


/**
\brief Disables the self-boot. CNcomment:关闭自举功能, boot下不能使用串口/网口升级 CNend
\attention \n
The setting is performed before delivery and can be performed once only.
The self-boot function is enabled by default.
CNcomment:在机顶盒出厂时选择是否设置，仅支持设置一次，默认使能SelfBoot功能 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_DisableSelfBoot(HI_VOID);

/**
\brief Get the self-boot status. CNcomment:获取自举状态 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbDisable Pointer to the self-boot status, true means DISABLE. CNcomment:指针类型，自举状态，true表示禁用自举功能 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetSelfBootStat(HI_BOOL *pbDisable);


/**
\brief Force decrypt the BootLoader. CNcomment:设置必须对BootLoader进行解密 CNend
\attention \n
The setting is performed before delivery and can be performed once only.
CNcomment:在机顶盒出厂时选择是否设置，仅支持设置一次
默认根据Flash中的数据标识，决定BootLoader是否需要解密 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_EnableBootDecrypt(HI_VOID);


/**
\brief Get the BootLoader Decryption status. CNcomment:获取BootLoader解密状态 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Point to bootLoader Decryption status. CNcomment:指针类型，Bootloader解密标志位 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetBootDecryptStat(HI_BOOL *pbEnable);


/**
\brief Enable the security startup. This API should be used after the API HI_UNF_OTP_SetBootMode.
CNcomment:设置安全启动使能，该接口必须和HI_UNF_OTP_COMMON_SetBootMode配套使用 CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_EnableSCS(HI_VOID);


/**
\brief Get the security startup status function. CNcomment:获取安全启动使能标记 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Point to bootLoader SCS status. CNcomment:指针类型，安全启动使能标志位 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetSCSStat(HI_BOOL *pbEnable);


/**
\brief Enable the Trust Zone. CNcomment:设置Trust Zone使能CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_EnableTrustZone(HI_VOID);


/**
\brief Get the Trust Zone status.
CNcomment:获取TrustZone使能标记 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Point to trust zone status. CNcomment:指针类型，安全区域使能标志位 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable);


/**
\brief Get the market segment identifier. CNcomment:获取市场区域码  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pu8MSID Point to MSID. CNcomment:指针类型，市场区域码 CNend
\param[in/out] pu32Len Point to MSID length, current is 4. CNcomment:指针类型，市场区域码长度，当前长度是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetMSID(HI_U8 *pu8MSID, HI_U32 *pu32Len);


/**
\brief Set the market segment identifier CNcomment:设置市场区域码  CNend
\attention \n
None CNcomment:无 CNend
\param[in] pu8MSID Point to MSID. CNcomment:指针类型，市场区域码 CNend
\param[in/out] u32MSIdLen MSID length, current is 4. CNcomment:市场区域码长度，当前长度是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetMSID(HI_U8 *pu8MSID, HI_U32 u32Len);


/**
\brief Get the secure os market segment identifier CNcomment:获取安全OS市场区域码  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pu8SOSMSID Point to SOS MSID. CNcomment:指针类型，安全OS市场区域码 CNend
\param[in/out] pu32Len Point to SOS MSID length, current is 4. CNcomment:指针类型，安全OS市场区域码长度，当前长度是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 *pu32Len);


/**
\brief Sets the sos market segment identifier CNcomment:设置安全OS市场区域码  CNend
\attention \n
None CNcomment:无 CNend
\param[in] pu8SOSMSID Point to SOSMSID. CNcomment:指针类型，安全OS市场区域码 CNend
\param[in] u32Len MSID length, current is 4. CNcomment:指针类型，安全OS市场区域码长度，当前长度是4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 u32Len);

/**
\brief Sets the LongData segment identifier CNcomment:设置LongData  CNend
\attention \n
None CNcomment:无 CNend
\param[in] u32Offset CNcomment: 地址偏移16字节对齐 CNend
\param[in] pu8Value CNcomment: otp数据数组  CNend
\param[in] u32Length CNcomment: otp数据数组长度,不用16字节对齐  CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:设置LongData  CNend
\attention \n
None CNcomment:无 CNend
\param[in] u32Offset CNcomment: 地址偏移16字节对齐 CNend
\param[out] pu8Value CNcomment: 接受otp数据数组  CNend
\param[in] u32Length CNcomment: otp数据数组长度,不用16字节对齐  CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:设置LongData的锁  CNend
\attention \n
None CNcomment:无 CNend
\param[in] u32Offset CNcomment: 地址偏移,16字节对齐 CNend
\param[in] u32Length CNcomment: otp数据数组长度,16字节对齐  CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:获得LongData的锁 CNend
\attention \n
None CNcomment:无 CNend
\param[in] u32Offset CNcomment: 地址偏移,16字节对齐 CNend
\param[in] u32Length CNcomment: otp数据数组长度,16字节对齐  CNend
\param[out] pu32Lock CNcomment: 返回0全没锁,返回1全锁,返回2部分被锁  CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length,  HI_U32 * pu32Lock);

/**
\brief disable wake up from ddr. CNcomment:关闭原地唤醒模式 CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_DisableDDRWakeup(HI_VOID);


/**
\brief Get wake up from ddr status. CNcomment:获取原地唤醒状态 CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbDisable Point to DDR WakeUp status. CNcomment:指针类型，原地唤醒使能状态 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetDDRWakeupStat(HI_BOOL *pbDisable);

/**
\brief Lock the whole OTP area. CNcomment:锁定整个OTP区域 CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_LockGlobalOTP(HI_VOID);



/**
\brief Get global otp lock status function. CNcomment:获取OTP锁状态 CNend
\attention \n
None CNcomment:无 CNend
\param[out]  pbEnable Point to global OTP lock status. CNcomment:指针类型，OTP锁定状态 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetGlobalOTPLockStat(HI_BOOL *pbEnable);


/**
\brief Enable runtime-check. CNcomment:设置运行时校验功能使能 CNend
\attention \n
None CNcomment:无 CNend
\param[in]  None
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_EnableRuntimeCheck(HI_VOID);


/**
\brief Get runtime-check status CNcomment:获取运行时校验状态使能标记  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Point to runtime Check status. CNcomment:指针类型，运行时校验使能状态 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetRuntimeCheckStat(HI_BOOL *pbEnable);

/**
\brief Disable DDR wakeup check. CNcomment:关闭待机唤醒校验。CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_DisableDDRWakeupCheck(HI_VOID);


/**
\brief Get ddr wakeup check status. CNcomment:获取待机唤醒校验使能标记  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Point to DDR Wakeup Check status. CNcomment:指针类型，待机唤醒校验使能状态 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetDDRWakeupCheckStat(HI_BOOL *pbEnable);


/**
\brief Enable ddr scramble. CNcomment:设置内存加扰功能 CNend
\attention \n
None CNcomment:无 CNend
\retval ::HI_SUCCESS Success.  CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE Failure.  CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTP未初始化 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_EnableDDRScramble(HI_VOID);


/**
\brief Get ddr scramble status CNcomment:获取内存加扰使能标记  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pbEnable Pointer to DDR Scramble Stat. CNcomment:指向内存加扰使能标记值的指针 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_GetDDRScrambleStat(HI_BOOL *pbEnable);


/**
\brief Get the mode of the JTAG. CNcomment:获取JTAG调试接口模式 CNend
\attention \n
None CNcomment:无 CNend
\param[out] penJtagMode Point to the mode of the JTAG. CNcomment:指针类型，JTAG调试接口模式 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_GetJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode);


/**
\brief Set the mode of the JTAG. CNcomment:设置JTAG调试接口模式 CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:不支持设置为打开状态。\n
打开的时候可以关闭或设置为密钥保护状态。\n
处于密钥保护状态时可以关闭。\n
关闭之后不能打开和设置为密钥保护状态 CNend
\param[in] enJtagMode Mode of the JTAG. CNcomment:JTAG调试接口模式 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_SetJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode);


/**
\brief Get the mode of the TEE JTAG. CNcomment:获取 TEE JTAG调试接口模式 CNend
\attention \n
None CNcomment:无 CNend
\param[out] penJtagMode Point to the mode of the JTAG. CNcomment:指针类型，JTAG调试接口模式 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_GetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode);


/**
\brief Set the mode of the TEE JTAG. CNcomment:设置 TEE JTAG调试接口模式 CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:不支持设置为打开状态。\n
打开的时候可以关闭或设置为密钥保护状态。\n
处于密钥保护状态时可以关闭。\n
关闭之后不能打开和设置为密钥保护状态 CNend
\param[in] enJtagMode Mode of the JTAG. CNcomment:JTAG调试接口模式 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_SetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode);


/**
\brief Get the boot version identifier CNcomment:获取boot版本号  CNend
\attention \n
None CNcomment:无 CNend
\param[out] pu8VersionID Point to version ID. CNcomment:指针类型，boot版本号 CNend
\param[in/out] pu32VersionIdLen Point to the length of version ID, current is 4. CNcomment:指针类型，boot版本号长度，当前为4 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetBootVersionID(HI_U8 *pu8VersionID, HI_U32 *pu32Len);


/**
\brief Sets the boot version identifier CNcomment:设置boot版本号  CNend
\attention \n
None CNcomment:无 CNend
\param[in] pu8VersionID Point to version ID. CNcomment:指针类型，boot版本号 CNend
\param[in] u32Len The length of version ID, current is 4. CNcomment:指针类型，boot版本号长度，当前为4 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
None CNcomment:无 CNend
*/
HI_S32 HI_UNF_OTP_SetBootVersionID(HI_U8 *pu8VersionID, HI_U32 u32Len);


/**
\brief Set root key to otp. CNcomment:向芯片内部设置根密钥 CNend
\attention \n
N/A
\param[in] enRootkeyType:   Type of rootkey.        CNcomment:根密钥类型 CNend
\param[in] pu8Rootkey: Point to root key value.     CNcomment:指针类型，根密钥 CNend
\param[in] u32Len: The length of root key.          CNcomment:根密钥长度 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_U8 *pu8Rootkey, HI_U32 u32Len);


/**
\brief Get root key lock status.                    CNcomment:获取OTP锁状态信息 CNend
\attention \n
N/A
\param[in] enRootkeyType: Type of rootkey.          CNcomment:根密钥类型 CNend
\param[out] pbLock: Point to root key lock status.  CNcomment:指针类型，跟密钥是否被锁 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_BOOL *pbLock);

/**
\brief Set RSA key to otp. CNcomment:向芯片内部设置RSA密钥 CNend
\attention \n
N/A
\param[in] pu8Key: Point to RSA key value.         CNcomment:指针类型，RSA密钥 CNend
\param[in] u32KeyLen: The length of RSA key.       CNcomment:RSA密钥长度 CNend
\retval ::HI_SUCCESS Success                                            CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called                        CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized  CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid   CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
\brief Get rsa lock status. CNcomment:获取RSA lock状态 CNend
\attention \n
N/A
\param[out] pbLock: Rsa lock status.   CNcomment:指针类型，RSA lock状态 CNend
\retval ::HI_SUCCESS  Success.         CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.         CNcomment:API系统调用失败 CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTP未初始化 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetRSALockStat(HI_BOOL *pbLock);


/**
\brief Burn product PV to otp. CNcomment:向芯片内部OTP固定配置 CNend
\attention \n
N/A
\param[in] pstPV: Point to the name of the config table.   CNcomment:指针类型，配置数据表地址 CNend
\param[in] u32Num:  the nember of config table.         CNcomment:配置数据条目数 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num);

/**
\brief Verify product PV. CNcomment:调试校验PV数据的正确性 CNend
\attention \n
N/A
\param[in] pstPV: Point to the name of the config table.   CNcomment:指针类型，配置数据表地址 CNend
\param[in] u32Num:  the nember of config table.         CNcomment:配置数据条目数 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS 成功 CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  API系统调用失败 CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CA未初始化 CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  输入参数非法 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_VerifyProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_OTP_H__ */
