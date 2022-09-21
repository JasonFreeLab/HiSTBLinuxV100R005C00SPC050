/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_mailbox_ext.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_MAILBOX_EXT_H__
#define __TEE_DRV_MAILBOX_EXT_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/** Mailbox ID */
#define MID_SMCU_SCS             (0x20)      /**<SCS of SMCU Firmware*/
#define MID_SMCU_SEC_STANDBY     (0x21)      /**<Secure standby SMCU driver*/
#define MID_SMCU_KEY_PROVISION   (0x22)      /**<Key provision SMCU driver*/
#define MID_SMCU_RUNTIME_CHECK   (0x23)      /**<Runtime check SMCU driver*/

#define MID_TCPU_SEC_STANDBY     (0x41)      /**<Secure standby TEE driver*/
#define MID_TCPU_KEY_PROVISION   (0x42)      /**<Key provision TEE driver*/
#define MID_TCPU_RUNTIME_CHECK   (0x43)      /**<Runtime check TEE driver*/


typedef struct
{
    const void *pMsgBuf;
    HI_U32 MsgLen;
    void *pBufOut;
    HI_U32 *pBufOutLen;
} TEE_DRV_MAILBOX_BUFFER_S;

/******************************* API declaration *****************************/

/**
\brief Open mailbox device.                                                     CNcomment:打开 mailbox 设备，返回 maibox 句柄。 CNend
\attention \n
N/A
\param[out] pHandle: Create handle/A                                            CNcomment:无。 CNend
\param[in]  id:  mailbox ID/A                                                   CNcomment:无。 CNend

\retval ::HI_SUCCESS  Call this API successful.                                 CNcomment:系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API failure.                                    CNcomment:分配句柄失败。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 id);

/**
\brief Destory mailbox instance.                                                CNcomment:关闭 mailbox 设备实例。 CNend
\attention \n
N/A
\param [in] handle: mailbox instance handle/A                                   CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                 CNcomment:系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API failure.                                    CNcomment:释放句柄失败。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 id);

/**
\brief  send data by mailbox.                                                   CNcomment:通过 mailbox 发送数据。 CNend
\attention \n
N/A
\param [in] handle: mailbox instance handle/A                                   CNcomment:无。 CNend
\param [in] ReceiverId: mailbox ID of data receiver/A                           CNcomment:无。 CNend
\param [in] pBuffer: mailbox input and output buffer/A                          CNcomment:无。 CNend
\param [in] Flags: mail box mode/A                                              CNcomment:超时模式和阻塞模式。 CNend
\param [in] Param: mailbox max wait time/A                                      CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.                                 CNcomment:系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API failure.                                    CNcomment:系统调用失败。 CNend
\see \n
N/A
*/
HI_S32 TEE_DRV_MAILBOX_Send
(
    HI_HANDLE handle,
    HI_U32 ReceiverId,
    TEE_DRV_MAILBOX_BUFFER_S *pBuffer,
    HI_U32 Flags,
    HI_U32 Param
);


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
