#ifndef _TEE_DRV_MAILBOX_IOCTL_H__
#define _TEE_DRV_MAILBOX_IOCTL_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */

typedef enum
{
    TEE_DRV_MAILBOX_OPEN = 0X0,
    TEE_DRV_MAILBOX_CLOSE,
    TEE_DRV_MAILBOX_SEND,
}MAILBOX_DRV_IOCTL_FUNC_ID_E;


typedef struct
{
    HI_HANDLE handle;
    HI_HANDLE* pHandle;
    HI_U32 id;
    HI_VOID* pMsgBuf;
    HI_U32 MsgLen;
    HI_VOID* pBufOut;
    HI_U32 *pBufOutLen;
    HI_U32 flags;
    HI_U32 param;
}HI_TEE_MAILBOX_DRV_IOCTRL_BUF_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */


#endif
