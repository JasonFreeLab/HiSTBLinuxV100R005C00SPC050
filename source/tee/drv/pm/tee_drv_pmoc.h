/******************************************************************************
 *
 * Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_pmoc.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-3-27
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_PMOC_H__
#define __TEE_DRV_PMOC_H__

#include "hi_tee_debug.h"

#define SMCU_WAIT_TIME_OUT (5000)

#define SMCU_RESET_ADDR (0xf8a80060)

#define MAILBOX_BASE_ADDR (0xf9a39000)
#define MAILBOX_TOTEECPU_ADDRESS (0xf9a39310)

#define MAILBOX_FROM_TEECPU_CMD_ADDRESS (0xf9a39200)
#define MAILBOX_FROM_TEECPU_PARAM_ADDRESS (0xf9a39240)
#define MAILBOX_CMD_SEND_TEECPU_TO_SMCU_ADDRESS (0xf9a39404)

#define MAILBOX_TCPU_SEC_STANDBY (0x41)
#define MAILBOX_SMCU_SEC_STANDBY (0x21)

#define MAILBOX_STATUS_LOAD_OK (0x80510002)
#define MAILBOX_STATUS_FAIL    (0x8051F000)
#define MAILBOX_REG_COUNT (8)
#define MAILBOX_BUF_LENGTH (8)
#define SHA3 (0x66031013)
#define AARCH32 (0)
#define AARCH64 (1)
#define SHA3_BLOCK_SIZE (136)
#define OTP_RUNTIME_CHECK_ADDR (0x4) //bit1

#define LP_START (0xf8000a08)

#define PM_WRITE_REG(Addr, Value) ((*(volatile HI_U32 *)(tee_hal_phys_to_virt(Addr))) = (Value))
#define PM_READ_REG(Addr) (*(volatile HI_U32 *)(tee_hal_phys_to_virt(Addr)))

#endif


