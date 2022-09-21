/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/
#ifndef __HAL_OTP_H__
#define __HAL_OTP_H__

#include "hi_common.h"
#include "hi_type.h"
#include "hi_error_mpi.h"

#define CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        HI_FATAL_OTP("Null point.\n"); \
        return HI_ERR_OTP_PTR_NULL;\
    }\
}while(0)

#define OTP_BITS_PER_LONG 32
#define GENMASK_U(h, l) \
    (((~0U) << (l)) & (~0U >> (OTP_BITS_PER_LONG - 1 - (h))))
#define GENMASKREV_U(h, l) \
    ~(((~0U) << (l)) & (~0U >> (OTP_BITS_PER_LONG - 1 - (h))))


//PERM_CTRL register address
#define PERM_REG_BASE           (0xf8ab0000)
#define OTP_RW_CTRL             (PERM_REG_BASE + 0x4000)		//OTP MEM read and write control
#define OTP_RDATA               (PERM_REG_BASE + 0x4020)
#define OTP_WDATA               (PERM_REG_BASE + 0x4024)
#define OTP_RADDR               (PERM_REG_BASE + 0x4028)
#define OTP_WADDR               (PERM_REG_BASE + 0x402C)
#define OTP_CTR_ST0             (PERM_REG_BASE + 0x4034)		//OTP controller status
#define OTP_SH_UPDATE           (PERM_REG_BASE + 0x4040)		//Shadow register update request

#define RNG_BASE                      0xf8abc000
#define RNG_FIFO_DATA                 0x0204

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

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *tdata);
HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *tdata);
HI_S32 HAL_OTP_Init(HI_VOID);
HI_S32 HAL_OTP_Reset(HI_VOID);
HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value);
HI_S32 HAL_OTP_Write(HI_U32 addr,HI_U32 tdata);
HI_S32 HAL_OTP_WriteByte(HI_U32 addr,HI_U8 tdata);
HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32  bit_value);
HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value);

#endif /* __HAL_OTP_H__ */
