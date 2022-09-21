/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : otp.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_reg_common.h"
#include "hi_common.h"
#include "command.h"
#include "otp_debug.h"
#ifndef HI_MINIBOOT_SUPPORT
#include "common.h"
#include <linux/string.h>
#else
#include "delay.h"
#endif

#define OTP_V200_BASE_OFFSET        (0xF8AB0000)
#define OTP_V200_CHANNEL_SEL        (OTP_V200_BASE_OFFSET + 0x00)
#define OTP_V200_CPU_RW_CTRL        (OTP_V200_BASE_OFFSET + 0x04)
#define OTP_V200_WR_START           (OTP_V200_BASE_OFFSET + 0x08)
#define OTP_V200_CTRL_STATUS        (OTP_V200_BASE_OFFSET + 0x0c)
#define OTP_V200_RDATA              (OTP_V200_BASE_OFFSET + 0x10)
#define OTP_V200_WDATA              (OTP_V200_BASE_OFFSET + 0x14)
#define OTP_V200_RADDR              (OTP_V200_BASE_OFFSET + 0x18)
#define OTP_V200_WADDR              (OTP_V200_BASE_OFFSET + 0x1C)
#define OTP_V200_MODE               (OTP_V200_BASE_OFFSET + 0x20)

#define OTP_V200_CHIPID             (OTP_V200_BASE_OFFSET + 0xe8)
#define OTP_V200_STBSN              (OTP_V200_BASE_OFFSET + 0x110)
#define OTP_V200_MARKETID           (OTP_V200_BASE_OFFSET + 0x120)
#define OTP_V200_SecureBootEn       (OTP_V200_BASE_OFFSET + 0x98)
#define OTP_V200_CA_VENDOR_ID       (OTP_V200_BASE_OFFSET + 0x12C)
#define OTP_V200_PVREGISTER0        (OTP_V200_BASE_OFFSET + 0x80)

#ifndef HI_REG_READ32
#define HI_REG_READ32(addr,result)  ((result) = *(volatile unsigned int *)(addr))
#endif

#ifndef HI_REG_WRITE32
#define HI_REG_WRITE32(addr,result)  (*(volatile unsigned int *)(addr) = (result))
#endif


typedef union
{
    struct
    {
        HI_U32 channel_sel         : 2; // [0-1]
        HI_U32 reserved            : 30; // [2-31]
    } bits;
    HI_U32 u32;
} OTP_V200_CHANNEL_SEL_U; //Offset:0x00

typedef union
{
    struct
    {
        HI_U32 wr_sel              : 1; // [0]
        HI_U32 rd_enable           : 1; // [1]
        HI_U32 wr_enable           : 1; // [2]
        HI_U32 rsv                 : 1; // [3]
        HI_U32 cpu_size            : 2; // [4-5]
        HI_U32 reserved            : 26; // [6-31]
    } bits;
    HI_U32 u32;
} OTP_V200_CPU_RW_CTRL_U; //Offset:0x04

typedef union
{
    struct
    {
        HI_U32 start              : 1; // [0]
        HI_U32 reserved           : 31; // [1-31]
    } bits;
    HI_U32 u32;
} OTP_V200_WR_START_U; //Offset:0x08

typedef union
{
    struct
    {
        HI_U32 ctrl_ready          : 1; // [0]
        HI_U32 fail_flag           : 1; // [1]
        HI_U32 soak_flag           : 1; // [2]
        HI_U32 rsv                 : 1; // [3]
        HI_U32 r_lock              : 1; // [4]
        HI_U32 w_lock              : 1; // [5]
        HI_U32 reserved            : 26; // [6-31]
    } bits;
    HI_U32 u32;
} OTP_V200_CTRL_STATUS_U;//Offset:0x0c

typedef union
{
    struct
    {
        HI_U32 rdata0              : 8; // [0-7]
        HI_U32 rdata1              : 8; // [8-15]
        HI_U32 rdata2              : 8; // [16-23]
        HI_U32 rdata3              : 8; // [24-31]
    } bits;
    HI_U32 u32;
} OTP_V200_RDATA_U;//Offset:0x10

typedef union
{
    struct
    {
        HI_U32 wdata              : 32; // [0-31]
    } bits;
    HI_U32 u32;
} OTP_V200_WDATA_U;//Offset:0x14

typedef union
{
    struct
    {
        HI_U32 raddr              : 32; // [0-31]
    } bits;
    HI_U32 u32;
} OTP_V200_RADDR_U;//Offset:0x18

typedef union
{
    struct
    {
        HI_U32 waddr              : 32; // [0-31]
    } bits;
    HI_U32 u32;
} OTP_V200_WADDR_U;//Offset:0x1C

typedef union
{
    struct
    {
        HI_U32 max_soak_times      : 4; // [0-3]
        HI_U32 otp_time            : 4; // [4-7]
        HI_U32 soak_en             : 1; // [8]
        HI_U32 time_en             : 1; // [9]
        HI_U32 reserved            : 22; // [10-31]
    } bits;
    HI_U32 u32;
} OTP_V200_MODE_U;//Offset:0x20

static HI_U32 DRV_OTP_GetOTPTimeValue(HI_VOID)
{
    HI_U32 u32Value = 0;

    u32Value = 0x34f;   //OTP_FREQ_28_8M

    return u32Value;
}

static HI_VOID otp_wait(int usec)
{
    udelay(usec);
}

#define OTP_V200_INTERNAL_WRITE_STATUS_ADDR    (0X17)
#define OTP_V200_INTERNAL_WRITE_ERROR_VALUE    (0X80)


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

static HI_U32 HAL_OTP_V200_Read(HI_U32 addr)
{
    OTP_V200_CTRL_STATUS_U CtrlStaut;
    OTP_V200_CHANNEL_SEL_U ChannelSel;
    OTP_V200_CPU_RW_CTRL_U CPURWCtrl;
    OTP_V200_MODE_U        Mode;
    OTP_V200_RADDR_U       RAddr;
    OTP_V200_RDATA_U       Redata;
    HI_U32 u32OTPTimeValue = 0;

    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    //Check CTRL_STATUS ctrl_ready to 0x01
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }
    //Set OTP_V200_CHANNEL_SEL bit channel_sel to 2'b10
    ChannelSel.u32 = otp_read_reg(OTP_V200_CHANNEL_SEL);
    ChannelSel.bits.channel_sel = 0x02;
    otp_write_reg(OTP_V200_CHANNEL_SEL, ChannelSel.u32);
    //Set wr_sel to 0, set rd_enable to 1, read can only do by word
    CPURWCtrl.u32 = otp_read_reg(OTP_V200_CPU_RW_CTRL);
    CPURWCtrl.bits.wr_sel = 0x00;
    CPURWCtrl.bits.rd_enable = 0x01;
    CPURWCtrl.bits.cpu_size = 0x02;
    otp_write_reg(OTP_V200_CPU_RW_CTRL, CPURWCtrl.u32);

    //Set OTP_V200_MODE
    Mode.u32 = otp_read_reg(OTP_V200_MODE);
    u32OTPTimeValue = DRV_OTP_GetOTPTimeValue();
    Mode.u32 |= u32OTPTimeValue;
    otp_write_reg(OTP_V200_MODE, Mode.u32);
    //Set OTP_V200_RADDR
    RAddr.u32 = 0;
    RAddr.bits.raddr = addr;
    otp_write_reg(OTP_V200_RADDR, RAddr.u32);
    //Check CTRL_STATUS bit ctrl_ready to 0x01
    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }
    Redata.u32 = otp_read_reg(OTP_V200_RDATA);

    return Redata.u32;
}

HI_U8 HAL_OTP_V200_ReadByte(HI_U32 addr)
{
    HI_U32 Value = 0;
    HI_U32 readableAddr = 0;

    readableAddr = addr & (~0x3);
    Value = HAL_OTP_V200_Read(readableAddr);
    return (Value >> ((addr & 0x3)*8)) & 0xff ;
}

//Only used internally, No lock! Write to a special address 0x17[7]
static HI_S32 write_fail_flag(HI_VOID)
{
    OTP_V200_CTRL_STATUS_U CtrlStaut;
    OTP_V200_CHANNEL_SEL_U ChannelSel;
    OTP_V200_CPU_RW_CTRL_U CPURWCtrl;
    OTP_V200_MODE_U        Mode;
    OTP_V200_WADDR_U       WAddr;
    OTP_V200_WDATA_U       WDATA;
    OTP_V200_WR_START_U    WRStart;
    HI_U32 u32OTPTimeValue = 0;

    HI_U32 addr  = OTP_V200_INTERNAL_WRITE_STATUS_ADDR;
    HI_U32 tdata = OTP_V200_INTERNAL_WRITE_ERROR_VALUE;

    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    //Check CTRL_STATUS ctrl_ready to 0x01
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }
    //Set OTP_V200_CHANNEL_SEL bit channel_sel to 2'b10
    ChannelSel.u32 = otp_read_reg(OTP_V200_CHANNEL_SEL);
    ChannelSel.bits.channel_sel = 0x02;
    otp_write_reg(OTP_V200_CHANNEL_SEL, ChannelSel.u32);
    //Set wr_sel to 1, set wr_enable to 1, set cpu_size 2'b01(Byte operation)
    CPURWCtrl.u32 = otp_read_reg(OTP_V200_CPU_RW_CTRL);
    CPURWCtrl.bits.wr_sel = 0x01;
    CPURWCtrl.bits.wr_enable = 0x01;
    CPURWCtrl.bits.cpu_size = 0x01;
    otp_write_reg(OTP_V200_CPU_RW_CTRL, CPURWCtrl.u32);
    //Set OTP_V200_MODE
    Mode.u32 = otp_read_reg(OTP_V200_MODE);
    u32OTPTimeValue = DRV_OTP_GetOTPTimeValue();
    Mode.u32 |= u32OTPTimeValue;
    otp_write_reg(OTP_V200_MODE, Mode.u32);
    //Set OTP_V200_WADDR
    WAddr.u32 = 0;
    WAddr.bits.waddr = addr;
    otp_write_reg(OTP_V200_WADDR, WAddr.u32);
    //Set OTP_V200_WDATA
    WDATA.bits.wdata = (HI_U32)tdata;
    otp_write_reg(OTP_V200_WDATA, WDATA.u32);
    //Set WR_START bit start to 1
    WRStart.u32 = otp_read_reg(OTP_V200_WR_START);
    WRStart.bits.start = 1;
    otp_write_reg(OTP_V200_WR_START, WRStart.u32);

    //Check CTRL_STATUS bit ctrl_ready to 0x01
    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }

    return HI_SUCCESS;
}

static HI_S32 HAL_OTP_V200_WriteByte(HI_U32 addr, HI_U8 tdata)
{
    OTP_V200_CTRL_STATUS_U CtrlStaut;
    OTP_V200_CHANNEL_SEL_U ChannelSel;
    OTP_V200_CPU_RW_CTRL_U CPURWCtrl;
    OTP_V200_MODE_U        Mode;
    OTP_V200_WADDR_U       WAddr;
    OTP_V200_WDATA_U       WDATA;
    OTP_V200_WR_START_U    WRStart;
    HI_U32 u32OTPTimeValue = 0;

    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    //Check CTRL_STATUS ctrl_ready to 0x01
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }
    //Set OTP_V200_CHANNEL_SEL bit channel_sel to 2'b10
    ChannelSel.u32 = otp_read_reg(OTP_V200_CHANNEL_SEL);
    ChannelSel.bits.channel_sel = 0x02;
    otp_write_reg(OTP_V200_CHANNEL_SEL, ChannelSel.u32);
    //Set wr_sel to 1, set wr_enable to 1, set cpu_size 2'b01(Byte operation)
    CPURWCtrl.u32 = otp_read_reg(OTP_V200_CPU_RW_CTRL);
    CPURWCtrl.bits.wr_sel = 0x01;
    CPURWCtrl.bits.wr_enable = 0x01;
    CPURWCtrl.bits.cpu_size = 0x01;
    otp_write_reg(OTP_V200_CPU_RW_CTRL, CPURWCtrl.u32);
    //Set OTP_V200_MODE
    Mode.u32 = otp_read_reg(OTP_V200_MODE);

    u32OTPTimeValue = DRV_OTP_GetOTPTimeValue();
    Mode.u32 |= u32OTPTimeValue;

    otp_write_reg(OTP_V200_MODE, Mode.u32);
    //Set OTP_V200_WADDR
    WAddr.u32 = 0;
    WAddr.bits.waddr = addr;
    otp_write_reg(OTP_V200_WADDR, WAddr.u32);
    //Set OTP_V200_WDATA
    WDATA.bits.wdata = (HI_U32)tdata;
    otp_write_reg(OTP_V200_WDATA, WDATA.u32);
    //Set WR_START bit start to 1
    WRStart.u32 = otp_read_reg(OTP_V200_WR_START);
    WRStart.bits.start = 1;
    otp_write_reg(OTP_V200_WR_START, WRStart.u32);

    //Check CTRL_STATUS bit ctrl_ready to 0x01
    CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    while(CtrlStaut.bits.ctrl_ready != 1)
    {
        otp_wait(1);
        CtrlStaut.u32 = otp_read_reg(OTP_V200_CTRL_STATUS);
    }

    if (0 != CtrlStaut.bits.fail_flag)
    {
        HI_ERR_OTP("Write OTP failed!\n");
        write_fail_flag();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_V200_Write(HI_U32 addr, HI_U32 tdata)
{
    int i = 0;
    HI_U8 data = 0;
    HI_S32 ret = HI_FAILURE;

    for(i = 0; i < 4; i++)
    {
        data = (tdata >> (i * 8)) & 0xff;
        ret = HAL_OTP_V200_WriteByte(addr + i, data);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_OTP("Fail to write OTP!addr:0x%x;data:0x%x\n", addr + i, data);
            return HI_FAILURE;
        }
    }

    return ret;
}

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *tdata)
{
    *tdata = HAL_OTP_V200_Read(addr);
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *tdata)
{
    *tdata = HAL_OTP_V200_ReadByte(addr);
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_Reset(HI_VOID)
{
    return HI_FAILURE;
}

HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value)
{
    return HI_FAILURE;
}

HI_S32 HAL_OTP_Write(HI_U32 addr,HI_U32 tdata)
{
    return HAL_OTP_V200_Write(addr, tdata);
}

HI_S32 HAL_OTP_WriteByte(HI_U32 addr,HI_U8 tdata)
{
    return HAL_OTP_V200_WriteByte(addr, tdata);
}

HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32  bit_value)
{
    return HI_FAILURE;
}

HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value)
{
    return HI_FAILURE;
}

