/*****************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
 File Name     : hi_msg_queue.h
Version       : Initial draft
Author        : HiSilicon multimedia software group
Created Date   : 2012-09-19
Last Modified by:
Description   : Application programming interfaces (APIs) of the Message Queue (MsgQueue)
Function List :
Change History:
 ******************************************************************************/

/** @defgroup Common (MsgQueue)
 * \file
 * \brief Application programming interfaces (APIs) of the Message Queue (MsgQueue).
*/

#ifndef __HI_MSG_QUEUE_H
#define __HI_MSG_QUEUE_H

#include <pthread.h>
#include <semaphore.h>

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      MsgQueue */
/** @{ */  /** <!-- [MsgQueue] */

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup     MsgQueue  */
/** @{ */  /** <!-- [MsgQueue] */

/* message */
typedef struct message_hdr_s
{
    struct message_hdr_s    *message_hdr_next;
} message_hdr_t;

typedef struct message_half_s
{
    message_hdr_t       *message_half_head;
    message_hdr_t       *message_half_tail;
    sem_t               message_half_sem;    /* used for sync purpose */
    pthread_mutex_t     message_half_mutex;    /* guard queue ops */
} message_half_t;

typedef struct message_queue_s
{
    message_half_t      message_queue_free;
    message_half_t      message_queue_queue;
    HI_VOID             *message_queue_memory;
} message_queue_t;

typedef message_queue_t HI_MsgQueue_t;  /* for init function */
typedef message_queue_t *HI_MsgQueue_p;  /* message queue handle */

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      MsgQueue */
/** @{ */  /** <!-- [MsgQueue] */

/**
\brief Message Queue Create
CNcomment:\brief 消息队列创建.
\attention \n
N/A
\param[in] MessageSize  message size                                        CNcomment:单个消息内容的大小
\param[in] Messages     counut of message                                   CNcomment:多少个消息
\retval ::HI_MsgQueue_p:create ok return the message queue,otherwise null   CNcomment:创建成功，返回消息队列的句柄，失败返回NULL
\see \n
N/A
*/
HI_MsgQueue_p HI_MsgQueueCreate(size_t MessageSize, unsigned int Messages);

/**
\brief Message Queue Destroy
CNcomment:\brief 消息队列销毁.
\attention \n
N/A
\param[in] Queue     message queue handle                                   CNcomment:消息队列的句柄
\retval :: HI_VOID
\see \n
N/A
*/
HI_VOID HI_MsgQueueDestroy(HI_MsgQueue_p Queue);

/**
\brief Message Queue Claim
CNcomment:\brief 消息队列申请.
\attention \n
N/A
\param[in] Queue        message queue handle                                CNcomment:消息队列的句柄
\param[in] Timeout_MS   timeout 0:forever                                   CNcomment:申请超时，0:永远等待
\retval ::Message:      claim ok return the message, otherwise null         CNcomment:申请成功，返回消息的句柄，失败返回NULL
\see \n
N/A
*/
HI_VOID* HI_MsgClaim(HI_MsgQueue_p Queue, unsigned int Timeout_MS);

/**
\brief Message send
CNcomment:\brief 消息发送.
\attention \n
N/A
\param[in] Queue     message queue handle                                   CNcomment:消息队列的句柄
\param[in] Message   message content                                        CNcomment:消息内容
\retval :: HI_VOID
\see \n
N/A
*/
HI_VOID HI_MsgSend(HI_MsgQueue_p Queue, HI_VOID *Message);

/**
\brief Message receive
CNcomment:\brief 消息接收.
\attention \n
N/A
\param[in] Queue        message queue handle                                CNcomment:消息队列的句柄
\param[in] Timeout_MS   timeout 0:forever                                   CNcomment:接收超时，0:永远等待
\retval :: HI_VOID
\see \n
N/A
*/
HI_VOID *HI_MsgReceive(HI_MsgQueue_p Queue, unsigned int Timeout_MS);

/**
\brief Message release
CNcomment:\brief 消息释放.
\attention \n
N/A
\param[in] Queue     message queue handle                                   CNcomment:消息队列的句柄
\param[in] Message   message content                                        CNcomment:消息内容
\retval :: HI_VOID
\see \n
N/A
*/
HI_VOID HI_MsgRelease(HI_MsgQueue_p Queue, HI_VOID *Message);

/**
\brief Get the amount of message in the queue.
CNcomment:\brief 消息释放.
\attention \n
N/A
\param[in] Queue     message queue handle                                   CNcomment:消息队列的句柄
\retval :: the amount of message in the queue.
\see \n
N/A
*/
int HI_MsgGetAmount(HI_MsgQueue_p Queue);
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*__MSG_Q_H*/
