/******************************************************************************

Copyright (C), 2016-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_cert.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2016-11-4
Last Modified :
Description   : Hisilicon CERT API declaration
Function List :
History       :
******************************************************************************/

#ifndef __HI_TEE_CERT__
#define __HI_TEE_CERT__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      CERT */
/** @{ */  /** <!-- [CERT] */

/** Input and Output data Num */
/**CNcomment:Input data 和Output data数据大小*/
#define CERT_AKL_REG_DATA_NUM             8

/** Initialization vector max length */
/**CNcomment:IV最大数据长度*/
#define HI_TEE_CERT_IV_MAX_LEN            16

/**< Engine type*/
/**< CNcomment: 引擎类型*/
typedef enum
{
    HI_TEE_CERT_KEY_PORT_DEMUX        = 0X0,   /**< DEMUX*/
    HI_TEE_CERT_KEY_PORT_CIPHER       = 0x1,   /**< MCipher*/
    HI_TEE_CERT_KEY_PORT_PLCIPHER     = 0x2,   /**< PayLoad Cipher*/
    HI_TEE_CERT_KEY_PORT_UNKNOWN      = 0x3,
} HI_TEE_CERT_KEY_PORT_SEL_E;

/**< Target engine type*/
/**< CNcomment: 目标引擎类型*/
typedef enum
{
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_CSA2          = 1,   /**<Demux PAYLOAD CSA2 */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_CSA3             ,   /**<Demux PAYLOAD CSA3 */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_AES_CBC_IDSA     ,   /**<Demux/PLCipher PAYLOAD AES  IPTV Mode */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_AES_ECB          ,   /**<Demux/PLCipher PAYLOAD AES  ECB Mode */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_AES_CBC_CI       ,   /**<Demux/PLCipher PAYLOAD AES  CIPLUS */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_ECB ,   /**<Demux PAYLOAD AES  CLRSTART ECB */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_CBC ,   /**<Demux PAYLOAD AES  CLRSTART CBC */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_ASA              ,   /**<Demux PAYLOAD ASA */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_TDES_IPTV        ,   /**<Demux PAYLOAD TDES IPTV */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_TDES_ECB         ,   /**<Demux PAYLOAD TDES ECB */
    HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_TDES_CBC         ,   /**<Demux PAYLOAD TDES CBC */
    HI_TEE_CERT_TARGET_ENGINE_RAW_AES                  ,   /**<MultiCipher AES CBC */
    HI_TEE_CERT_TARGET_ENGINE_RAW_TDES                 ,   /**<MultiCipher AES CBC */
    HI_TEE_CERT_TARGET_ENGINE_BUTT
} HI_TEE_CERT_TARGET_ENGINE_E;

/**< Timeout type*/
/**< CNcomment: 超时类型*/
typedef enum
{
    HI_TEE_CERT_TIMEOUT_DEFAULT, /**<  Default timeout. Indicates that the associated command does not write in OTP.*/
                                 /**<  CNcomment: 默认超时，表明相关的命令是不会向otp中写入数据的命令*/
    HI_TEE_CERT_TIMEOUT_OTP,     /**<  The associated command is writing in OTP memory.*/
                                 /**<  CNcomment: 表明相关的命令会将数据写入到otp中的命令*/
    HI_TEE_CERT_LAST_TIMEOUT     /**<  Other use.*/  /**< CNcomment: 其他用途*/
} HI_TEE_CERT_TIMTOUT_E;

/** Structure of the CERT exchange information */
/** CNcomment:CERT exchange信息结构 */
typedef struct
{
    HI_U8 u8InputData[4 * CERT_AKL_REG_DATA_NUM];  /**< Input data to be written in the 8 32-bit CERT common interface DATA_IN_X
                                                        registers. First 4 MSB inputData[0:3] shall be written in DATA_IN_0
                                                        register, next 4 MSB inputData[4:7] in DATA_IN_1 register and so on.*/
                                                   /**< CNcomment: 输入数据，用于写入到CERT DATA_IN_X寄存器的8个32比特数据，
                                                        前4字节(MSB)写在DATA_IN_0寄存器,接下来4字节(MSB)写入DATA_IN_1，以此类推。*/
    HI_U8 u8OutputData[4 * CERT_AKL_REG_DATA_NUM]; /**< Buffer where to write values of the 8 32-bit CERT common interface
                                                        DATA_OUT_X registers following the processing of a command. */
                                                   /**< CNcomment: 命令执行之后，此缓存用于写入从CERT DATA_OUT_X寄存器读取的8个32比特数据*/
    HI_U8 u8Status[4];                             /**< Buffer where to write the value of the CERT common interface STATUS_AKL
                                                        register following the processing of a command.*/
                                                   /**< CNcomment: 命令执行之后，此缓存用于写入从STATUS_AKL寄存器读取的数据*/
    HI_U8 u8Opcodes[4];                            /**< Command operation codes to be written in the CERT common interface
                                                        COMMAND register. The least significant bit that acts as the command
                                                        start bit is already set to 1.*/
                                                   /**< CNcomment: 写入CERT COMMAND寄存器的命令操作码，最后一个bit设置为1有效*/
    HI_TEE_CERT_TIMTOUT_E enTimeout;               /**< This field characterizes the processing duration of the command. It is
                                                        not expressed as a duration. Associated timeout values is to be defined
                                                        by the entity in charge of developing the CERT driver. This field is
                                                        mainly used to know whether the command is going to write in OTP or not.*/
                                                   /**< CNcomment: 描述命令的处理时间, 并不是描述具体时间的长度，具体超时时间由驱动负责
                                                        这个字段主要用于感知操作命令是否是写otp的命令*/
} HI_TEE_CERT_COMMAND;


/** Structure of the CERT CTRL information */
/** CNcomment:CERT CTRL信息结构 */
typedef struct
{
    HI_HANDLE hHandle;                               /**< Target module handle, address information included*/ 
    HI_BOOL bIsEven;                                 /**< Type of key odd or even*/ 
    HI_TEE_CERT_TARGET_ENGINE_E enEngine;            /**< Target crypto engine*/
    HI_TEE_CERT_KEY_PORT_SEL_E enPortSel;            /**< Port select*/
    HI_BOOL bSecEn;                                  /**< Secure enable*/
} HI_TEE_CERT_KEY_DATA_S;

/** Structure of the IV information */
/** CNcomment:IV信息结构 */
typedef struct
{
    HI_HANDLE hHandle;                               /**< Target module handle, address information included*/
    HI_BOOL bIsEven;                                 /**< Type of IV odd or even*/
    HI_U8   u8IV[HI_TEE_CERT_IV_MAX_LEN];               /**< Initialization vector (IV) */
    HI_U32  u32Len;                                  /**< Initialization vector (IV) length*/
} HI_TEE_CERT_IV_S;

/**< Structure of CERT resource */
/**< CNcomment: CERT资源结构*/
typedef struct
{
    HI_HANDLE hResHandle;  /**< Cert resource handle */  /**< CNcomment: Cert 句柄*/
} HI_TEE_CERT_RES_HANDLE;

typedef struct
{
    HI_U32 addr;
    HI_U32 val;
} CERT_REG_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      CERT */
/** @{ */  /** <!--[CERT]*/

/**
\brief Initializes the CERT module.CNcomment:初始化CERT模块。CNend
\attention \n
Before using CERT, you must call this application programming interface (API).\n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:在进行PLCIPHER相关操作前应该首先调用本接口\n
重复调用本接口返回成功。CNend
\param  N/A.CNcomment:无。CNend
\retval ::HI_SUCCESS Success. CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\see \n
N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_Init(HI_VOID);

/**
\brief Deinitializes the CERT module. CNcomment:去初始化CERT模块。CNend
\attention \n
After this API is called, the CERT module is stopped, and the CERT resources used by the process are released.\n
This API is valid when it is called for the first time. If this API is called repeatedly, the error code HI_SUCCESS is returned.
CNcomment:调用本接口停止使用CERT模块，并释放本进程所占用的CERT资源\n
本接口第一次调用起作用，重复调用返回成功。CNend
\param  N/A.CNcomment:无。CNend
\retval ::HI_SUCCESS Success CNcomment:成功。CNend
\retval ::HI_FAILURE Calling this API fails. CNcomment:API系统调用失败。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_DeInit(HI_VOID);

/**
\brief Send the key on the bus to the subsequent encryption or descryption engine.
CNcomment:将总线上的key送给后级加解密引擎。CNend
\param[in] pstCtlData     Pointer to the structure of the CERT CTRL information.
CNcomment:指针类型，指向CERT CTRL信息控制结构体。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_CERT_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_UseKey( HI_TEE_CERT_KEY_DATA_S *pstCtlData);

/**
\brief Set initialization vector to the subsequent encryption or descryption engine.
CNcomment:将IV送给后级加解密引擎。CNend
\param[in] pstCtlData     Pointer to the structure of the IV information.
CNcomment:指针类型，指向IV信息控制结构体。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_CERT_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_SetIV(HI_TEE_CERT_IV_S *pstIv);

/**
\brief Reset cert. CNcomment:复位CERT模块。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_Reset(HI_VOID);

/**
\brief This function reserves the CERT resource for exclusive use to the caller.
CNcomment:获取cert的资源。CNend
\param[out] ppstResourceHandle     Handle assigned to the CERT resource.
CNcomment:指针类型，指向CERT 资源的句柄。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_CERT_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_Lock(HI_TEE_CERT_RES_HANDLE **ppstResourceHandle);

/**
\brief This function releases the CERT resource previously locked by HI_TEE_CERT_Lock()
CNcomment:释放被函数HI_TEE_CERT_Lock锁住的资源。CNend
\param[in] pstResourceHandle     Pointer to the structure of the CERT resource handle.
CNcomment:指针类型，指向CERT 资源的句柄。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_CERT_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_Unlock(HI_TEE_CERT_RES_HANDLE *pstResourceHandle);

/**
\brief
This function is used to send a series of commands to the CERT block, for chipset information or operating OTP.
CNcomment:此函数用于想CERT IP发送一系列的命令，获取芯片信息或者操作OTP。 CNend
\param[in] pstResourceHandle Handle to the CERT resource.
CNcomment:指针类型，指向CERT 资源的句柄。CNend
\param[in] ulNumOfCommands   Number of commands to be processed by the CERT block.
CNcomment: 操作CERT的命令的条目数。CNend
\param[in,out] pstCommands   This structure is used to accommodate input parameters of each command \n
as well as resulting output. The memory is allocated by the caller.
CNcomment: 该结构用于存储每个命令的输入参数以及生成的输出。内存由调用者分配。CNend
\param[out] pulNumOfProcessedCommands   Number of commands actually processed by the CERT block.
CNcomment:实际执行的命令条数。CNend
\retval ::HI_SUCCESS Success.CNcomment:成功。CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
\retval ::HI_ERR_CERT_NOT_INIT  The CERT module is not initialized.CNcomment:模块没有初始化。CNend
\retval ::HI_ERR_CERT_INVALID_PTR  The pointer is null. CNcomment:指针参数为空。CNend
\retval ::HI_ERR_CERT_TIME_OUT  The timeout has expired and the CERT block is still processing a command.
CNcomment:CERT一直在执行某个命令导致超时。CNend
\see \n
 N/A.CNcomment:无。CNend
*/
HI_S32 HI_TEE_CERT_Exchange(HI_TEE_CERT_RES_HANDLE *pstResourceHandle, HI_SIZE_T ulNumOfCommands,
                            const HI_TEE_CERT_COMMAND *pstCommands, HI_SIZE_T *pulNumOfProcessedCommands);


HI_S32 HI_TEE_CERT_READL( CERT_REG_S *reg);

HI_S32 HI_TEE_CERT_WRITEL( CERT_REG_S *reg);
/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif   /* __HI_TEE_CERT__ */

/* END OF FILE */
