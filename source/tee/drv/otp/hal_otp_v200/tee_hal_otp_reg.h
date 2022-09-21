/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_hal_otp_reg.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_HAL_OTP_REG_H__
#define __TEE_HAL_OTP_REG_H__

#include "hi_type.h"

//PERM_CTRL register address
#define PERM_REG_BASE           (0xf8ab0000)
#define OTP_RW_CTRL             (PERM_REG_BASE + 0x4000)		//OTP MEM read and write control
#define OTP_RDATA               (PERM_REG_BASE + 0x4020)
#define OTP_WDATA               (PERM_REG_BASE + 0x4024)
#define OTP_RADDR               (PERM_REG_BASE + 0x4028)
#define OTP_WADDR               (PERM_REG_BASE + 0x402C)
#define OTP_CTR_ST0             (PERM_REG_BASE + 0x4034)		//OTP controller status
#define OTP_SH_UPDATE           (PERM_REG_BASE + 0x4040)		//Shadow register update request

#define OTP_ANTIROLLBACK_NUMBER           (0x180)
#define OTP_ANTIROLLBACK_MAX_LEN           (0x10)
#define OTP_ADDR_DIEID                    (0x300)
typedef union
{
    struct
    {
        HI_U32 otp_init_rdy       : 1; //[0]
        HI_U32 soft_req_otp_rdy   : 1; //[1]
        HI_U32 prg_flag           : 1; //[2]
        HI_U32 rd_flag            : 1; //[3]
        HI_U32 err                : 1; //[4]
        HI_U32 prm_rd_fail        : 1; //[5]
        HI_U32 rd_fail            : 1; //[6]
        HI_U32 prog_disable       : 1; //[7]
        HI_U32 otp_init_err       : 1; //[8]
        HI_U32 reserved           : 23; //[23]
    } bits;
    HI_U32 u32;
} OTP_CTR_ST0_U;

#endif  /* __TEE_HAL_OTP_REG_H__ */

