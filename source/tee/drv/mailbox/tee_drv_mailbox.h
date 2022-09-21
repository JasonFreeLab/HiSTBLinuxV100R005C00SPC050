/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_mailbox.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_MAILBOX_H__
#define __TEE_DRV_MAILBOX_H__

#include "hi_type.h"
#include "hi_tee_log.h"
//#include "tee_os_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     TEE_DRV_MAILBOX */
/** @{ */  /** <!-- [TEE_DRV_MAILBOX] */

#define MBOX_MAX_NUM                             (4)

#define MBOX_HEAD_HANDLE                         (0x1f)
#define MBOX_INVALID_HANDLE                      (0xffff)
#define MBOX_INVALID_ID                          (0xffff)

#define MBOX_MSG_END                             (0x1)
#define MBOX_MSG_CONTINUE                        (0x0)

#define MBOX_SMCU_BASE_ADDR                      (0xf9a39000)
#define MBOX_TEECPU_TO_SMCU_ARGV_NUM             (8)
#define MBOX_SCPU_BASE_ADDR                      (0x48ABD000)
#define MBOX_TEECPU_TO_SCPU_ARGV_NUM             (16)
#define RECVCPU_INTR_FROM_TEECPU_STATUS(base)    ((base) + 0x040c)
#define CMD_HEAD_TEECPU_TO_RECVCPU(base)         ((base) + 0x0200)
#define CMD_ARGV_TEECPU_TO_RECVCPU(base, x)      ((base) + 0x0240 + (x) *4)
#define CMD_SEND_TEECPU_TO_RECVCPU(base)         ((base) + 0x0404)

#define TEECPU_INTR_STATUS(base)                 ((base) + 0x041c)
#define CMD_HEAD_SENDCPU_TO_TEECPU(base)         ((base) + 0x0300)
#define CMD_ARG_SENDCPU_TO_TEECPU(base, x)       ((base) + 0x0310 + (x) * 4)
#define MBOX_SMCU_TO_TEECPU_ARGV_NUM             (4)
#define MBOX_SCPU_TO_TEECPU_ARGV_NUM             (16)

#define ReadReg(addr)                            *(volatile unsigned int *)(tee_hal_phys_to_virt(addr))
#define WriteReg(addr,result)                    (*(volatile unsigned int *)(tee_hal_phys_to_virt(addr))) = (result)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     TEE_DRV_MAILBOX */
/** @{ */  /** <!-- [TEE_DRV_MAILBOX] */

/****** Enumeration definition ************/

typedef enum
{
    MBOX_MODE_BLOCK = 0x0,
    MBOX_MODE_BLOCK_TIMEOUT,
    MBOX_MODE_BUTT,
}MBOX_MSG_MODE_E;

typedef enum
{
    MBOX_IDLE,
    MBOX_BUSY,
    MBOX_BUTT,
}MBOX_STATE_E;

/****** Structure definition **************/

typedef struct
{
    unsigned int    handle[MBOX_MAX_NUM];
}MBOX_STATE_S;

typedef struct
{
    HI_U32 BaseAddr;
    HI_U32 SendArgvNum;
    HI_U32 RcvArgvNum;
    HI_U32 Flags;
    HI_U32 TimeOut;
    HI_BOOL CrcFlag;

}MBOX_PARAM_S;

/****** Union definition ******************/
typedef union
{
    struct
    {
        unsigned int reserved            : 8;  /** [7:0]   */
        unsigned int length              : 6;  /** [13:8]  */
        unsigned int length_reserved     : 2;  /** [15:14] */
        unsigned int receiver            : 7;  /** [22:16] */
        unsigned int end                 : 1;  /** [23]    */
        unsigned int sender              : 7;  /** [30:24] */
        unsigned int start               : 1;  /** [31]    */
    } bits;

    unsigned int u32;
} MBOX_MSG_HEAD_U;

typedef union
{
    struct
    {
        unsigned int bit0                 : 8;  /** [7:0]    */
        unsigned int bit1                 : 8;  /** [15:8]   */
        unsigned int bit2                 : 8;  /** [23:16]  */
        unsigned int bit3                 : 8;  /** [31:24]  */
    } bits;

    unsigned int u32;
} MBOX_MSG_BODY_U;

typedef union
{
    struct
    {
        unsigned int cmd_send             : 1;  /** [0]     */
        unsigned int reserved             : 31; /** [31:1] */
    } bits;

    unsigned int u32;
} MBOX_CDM_SEND_U;

typedef union
{
    struct {
        unsigned int intr                 : 1;  /** [0] */
        unsigned int reserved             : 31; /** [31:1] */
    } bits;

    unsigned int u32;
} MBOX_INTR_STATUS_U;


/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/
HI_S32 Test(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */

#endif /* __TEE_DRV_MAILBOX_H__ */


