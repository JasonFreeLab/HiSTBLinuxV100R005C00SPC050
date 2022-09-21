/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "hi_type.h"
#include "hal_otp.h"
#include "otp_debug.h"

#define BITS_PER_LONG 32
#define GENMASK_U(h, l) \
    (((~0U) << (l)) & (~0U >> (BITS_PER_LONG - 1 - (h))))
#define GENMASKREV_U(h, l) \
    ~(((~0U) << (l)) & (~0U >> (BITS_PER_LONG - 1 - (h))))

#ifndef HI_REG_READ32
#define HI_REG_READ32(addr,result)  ((result) = *(volatile unsigned int *)(addr))
#endif

#ifndef HI_REG_WRITE32
#define HI_REG_WRITE32(addr,result)  (*(volatile unsigned int *)(addr) = (result))
#endif


//PERM_CTRL register address
#define PERM_REG_BASE           (0xf8ab0000)
#define OTP_RW_CTRL             (PERM_REG_BASE + 0x4000)       //OTP MEM read and write control
#define OTP_RDATA               (PERM_REG_BASE + 0x4020)
#define OTP_WDATA               (PERM_REG_BASE + 0x4024)
#define OTP_RADDR               (PERM_REG_BASE + 0x4028)
#define OTP_WADDR               (PERM_REG_BASE + 0x402C)
#define OTP_CTR_ST0             (PERM_REG_BASE + 0x4034)         //OTP controller status
#define OTP_SH_UPDATE           (PERM_REG_BASE + 0x4040)        //Shadow register update request

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

static HI_VOID otp_write_reg(HI_U32 addr, HI_U32 val)
{
    HI_REG_WRITE32(addr, val);
    return;
}

static HI_U32 otp_read_reg(HI_U32 addr)
{
    HI_U32 val = 0;
    HI_REG_READ32(addr, val);
    return val;
}

static HI_S32 s_check_error_status(HI_VOID)
{
    OTP_CTR_ST0_U st0;

    st0.u32 = 0;
    st0.u32 = otp_read_reg(OTP_CTR_ST0);

    if (0 == st0.bits.otp_init_rdy)
    {
        HI_ERR_OTP("OTP initialization not finished\n");
        return HI_FAILURE;
    }
    else if (1 == st0.bits.err)
    {
        HI_WARN_OTP("hostCPU read or the program permission check fail\n");
        return HI_SUCCESS;
    }
    else if (1 == st0.bits.prm_rd_fail)
    {
        HI_ERR_OTP("data read back check fail\n");
        return HI_FAILURE;
    }
    else if (1 == st0.bits.rd_fail)
    {
        HI_ERR_OTP("read operation abnormal\n");
        return HI_FAILURE;
    }
    else if (1 == st0.bits.prog_disable)
    {
        HI_ERR_OTP("OTP fuse otp_global_lock_en is 1\n");
        return HI_FAILURE;
    }
    else
    {
        return HI_SUCCESS;
    }
}

static void s_wait_ctrl_idle(HI_VOID)
{
    HI_U32 reg_data[1] = {0};

    reg_data[0] = otp_read_reg(OTP_RW_CTRL);
    while ((*reg_data & 0x1) == 0x1)
    {
        reg_data[0] = otp_read_reg(OTP_RW_CTRL);
    }

    return;
}

HI_VOID HAL_OTP_Reset(HI_VOID)
{
    HI_U32 reg_data[1] = {0};

    otp_write_reg(OTP_SH_UPDATE, 0x1);
    reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    while ((*reg_data & 0x2) == 0x0)        //2b'10
    {
        reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    }

    return;
}

HI_VOID HAL_OTP_Init(HI_VOID)
{
    HI_U32 reg_data[1] = {0};

    reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    while ((*reg_data & 0x1) == 0x0)
    {
        reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    }

    return ;
}

HI_VOID HAL_OTP_DeInit(HI_VOID)
{
    return ;
}

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *value)
{
    HI_U32 read1, read2, ramdom;

    OTP_CHECK_PARAM(HI_NULL == value);

    otp_write_reg(OTP_RADDR, addr);
    otp_write_reg(OTP_RW_CTRL, 0x3);
    s_wait_ctrl_idle();

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    //msleep(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    read1 = otp_read_reg(OTP_RDATA);

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    //msleep(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    ramdom = ramdom;
    read2 = otp_read_reg(OTP_RDATA);

    if (read1 != read2)
    {
        *value = 0;
        HI_ERR_OTP("Read otp error\n");
        return HI_FAILURE;
    }

    *value = read1;

    return s_check_error_status();
}

HI_S32 HAL_OTP_Write(HI_U32 addr, HI_U32 value)
{
    if ((addr & 0x03) != 0)
    {
        HI_ERR_OTP("OTP address:%x is not 4 bytes aligned\n");
        return HI_FAILURE;
    }

    (HI_VOID)HAL_OTP_WriteByte(addr + 0x00, value & 0xFF);
    (HI_VOID)HAL_OTP_WriteByte(addr + 0x01, (value >> 8) & 0xFF);
    (HI_VOID)HAL_OTP_WriteByte(addr + 0x02, (value >> 16) & 0xFF);
    (HI_VOID)HAL_OTP_WriteByte(addr + 0x03, (value >> 24) & 0xFF);

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *value)
{
    HI_S32 ret = 0;
    HI_U32 v = 0;
    HI_U32 addr_e = 0;

    OTP_CHECK_PARAM(HI_NULL == value);

    addr_e = addr & (~0x3);
    ret = HAL_OTP_Read(addr_e, &v);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }
    *value = (v >> ((addr & 0x3) * 8)) & 0xff;

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_WriteByte(HI_U32 addr, HI_U8 value)
{
    otp_write_reg(OTP_WDATA, value);
    otp_write_reg(OTP_WADDR, addr);
    otp_write_reg(OTP_RW_CTRL, 0x5);
    s_wait_ctrl_idle();

    return s_check_error_status();
}


HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32 bit_value)
{
    HI_U8 data = 0;
    HI_S32 ret = 0;

    if (bit_value == 1)
    {
        ret = HAL_OTP_ReadByte(addr, &data);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
        data |= (1 << bit_pos);

        return HAL_OTP_WriteByte(addr, data);
    }
    else
    {
        //Do nothing when bit_value is 0.
    }
    return HI_SUCCESS;
}


HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value)
{
    HI_S32 ret = 0;
    HI_U8 data = 0;

    if (start_bit + bit_width > 8)
    {
        return HI_FAILURE;
    }

    ret = HAL_OTP_ReadByte(addr, &data);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
    data &= GENMASK_U(start_bit + bit_width - 1, start_bit);
    *value = data >> start_bit;

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value)
{
    HI_S32 ret = 0;
    HI_U8 data = 0;

    if (start_bit + bit_width > 8)
    {
        return HI_FAILURE;
    }
    ret = HAL_OTP_ReadByte(addr, &data);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
    data = (data & GENMASKREV_U(start_bit + bit_width - 1, start_bit)) |
           ((value << start_bit) & GENMASK_U(start_bit + bit_width - 1, start_bit));

    return HAL_OTP_WriteByte(addr, data);
}

