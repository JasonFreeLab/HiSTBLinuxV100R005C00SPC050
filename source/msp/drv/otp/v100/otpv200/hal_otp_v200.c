/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp_v200.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <asm/delay.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <asm/memory.h>
#include <linux/poll.h>
#include "hi_kernel_adapt.h"
#include "hi_type.h"
#include "drv_otp.h"
#include "drv_otp_common.h"
#include "drv_otp_reg_v200.h"
#include "drv_otp_v200.h"
#ifdef SDK_OTP_ARCH_VERSION_V3
#include "drv_otp_ext.h"
#else
#include "otp_drv.h"
#endif

#define OTP_SIZE  (0x800)

static HI_U32 s_otp_buffer[OTP_SIZE] = {0};

HI_DECLARE_MUTEX(g_OtpV200Mutex);

#define OTP_V200_INTERNAL_WRITE_STATUS_ADDR    (0X17)
#define OTP_V200_INTERNAL_WRITE_ERROR_VALUE    (0X80)

#define DRV_OTPV200_LOCK() do{          \
        HI_S32 s32Ret = 0;          \
        s32Ret = down_interruptible(&g_OtpV200Mutex);       \
            if (0 != s32Ret)                                                    \
            {                                                                       \
                HI_FATAL_OTP("Down_interruptible error!\n");    \
                return -1;                                                      \
            }                                                                       \
    }while(0)

#define DRV_OTPV200_UNLOCK() do{    \
            up(&g_OtpV200Mutex);    \
        }while(0)


static HI_U32 DRV_OTP_GetOTPTimeValue(HI_VOID)
{
    HI_U32 u32Value = 0;

#ifdef CHIP_TYPE_hi3712
        u32Value = 0x33f;   //OTP_FREQ_24M
#else
        u32Value = 0x34f;   //OTP_FREQ_28_8M
#endif

    return u32Value;
}

//Only used internally, No lock! Write to a special address 0x17[7]
static HI_S32 write_fail_flag(HI_VOID)
{
    volatile OTP_V200_CTRL_STATUS_U CtrlStaut;
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
    //Set wr_sel to 1, set wr_enable to 1, set cpu_sizeΪ2'b01(Byte operation)
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



HI_S32 HAL_OTP_V200_WriteToOTP(HI_U32 addr, HI_U32 value, HI_BOOL bWord)
{
    volatile OTP_V200_CTRL_STATUS_U CtrlStaut;
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
    //Set wr_sel to 1, set wr_enable to 1, set cpu_size to 2'b10(Word Operation)
    CPURWCtrl.u32 = otp_read_reg(OTP_V200_CPU_RW_CTRL);
    CPURWCtrl.bits.wr_sel = 0x01;
    CPURWCtrl.bits.wr_enable = 0x01;
    CPURWCtrl.bits.cpu_size = ((bWord == HI_TRUE) ? 0x02 : 0x01);
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
    WDATA.bits.wdata = value;
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
        HI_FATAL_OTP("Write OTP failed!\n");
        write_fail_flag();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_U32 HAL_OTP_V200_ReadFromOTP(HI_U32 addr)
{
    volatile OTP_V200_CTRL_STATUS_U CtrlStaut;
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

HI_VOID DRV_OTP_BUFFER_INIT(HI_VOID)
{
    HI_S32 i;
    HI_U32 value;

    for (i = 0; i < OTP_SIZE; i += 4)
    {
        value = HAL_OTP_V200_ReadFromOTP(i);
        memcpy(&s_otp_buffer[i], &value, sizeof (HI_U32));
    }

}

HI_U32 HAL_OTP_V200_ReadFromBuffer(HI_U32 addr)
{
    return s_otp_buffer[addr];
}

HI_S32 HAL_OTP_V200_WriteToBuffer(HI_U32 addr, HI_U32 value)
{
    HI_U32 value_from_otp = 0;
    /* check if addr is 4bytes aligned or not */

    if (addr + 4 >= OTP_SIZE)
    {
        HI_FATAL_OTP("large than otp size\n");
        return HI_FAILURE;
    }

    if( 0 != (addr & 0x3))
    {
        HI_FATAL_OTP("Addr must be aligned with 4 Bytes!\n");
        return HI_FAILURE;
    }

    value_from_otp = HAL_OTP_V200_Read(addr);

    value_from_otp = value_from_otp | value;

    memcpy(&s_otp_buffer[addr], &value_from_otp, sizeof (HI_U32));

    return HI_SUCCESS;
}

HI_S32 HAL_OTP_V200_WriteByteToBuffer(HI_U32 addr, HI_U8 value)
{

    HI_U32 value_to_write = 0;
    HI_U32 write_addr = 0;

    write_addr = addr & (~0x3);

    value_to_write = HAL_OTP_V200_Read(write_addr);

    value_to_write = value_to_write | (value << ((addr & 0x3) * 8));

    DRV_OTPV200_LOCK();

    memcpy(&s_otp_buffer[addr], &value_to_write, sizeof (HI_U32));

    DRV_OTPV200_UNLOCK();

    return HI_SUCCESS;
}

HI_U32 HAL_OTP_V200_Read(HI_U32 addr)
{
    HI_U32 value = 0;

    value = HAL_OTP_V200_ReadFromBuffer(addr);

    return value;
}

HI_U8 HAL_OTP_V200_ReadByte(HI_U32 addr)
{
    HI_U32 Value = 0;
    HI_U32 readableAddr = 0;

    readableAddr = addr & (~0x3);
    Value = HAL_OTP_V200_Read(readableAddr);
    return (Value >> ((addr & 0x3)*8)) & 0xff ;
//    return (HI_U8)(Value & 0xff);
}

HI_S32 HAL_OTP_V200_Write(HI_U32 addr, HI_U32 tdata)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 otp_data = 0;
    HI_U32 i = 0;
    HI_U8 data = 0;

    for(i = 0;i < 4; i++)
    {
        data = (tdata >> (8*i)) & 0xff;
        ret = HAL_OTP_V200_WriteToOTP(addr + i, data, HI_FALSE);
        if(ret != HI_SUCCESS)
        {
            HI_FATAL_OTP("Fail to write OTP!addr:0x%x;data:0x%x\n", addr + i, data);
            return HI_FAILURE;
        }
    }

    if(ret != HI_FAILURE)
    {
        otp_data = HAL_OTP_V200_ReadFromOTP(addr);

        ret  = HAL_OTP_V200_WriteToBuffer(addr, otp_data);
    }

    return ret;
}

HI_S32 HAL_OTP_V200_WriteByte(HI_U32 addr, HI_U8 tdata)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 otp_data = 0;
    HI_U32 addr_align = 0;


    ret = HAL_OTP_V200_WriteToOTP(addr, (HI_U32) tdata, HI_FALSE);

    if(ret != HI_FAILURE)
    {
        addr_align = addr & (~0x3);
        otp_data = HAL_OTP_V200_ReadFromOTP(addr_align);

        ret  = HAL_OTP_V200_WriteToBuffer(addr_align, otp_data);
    }

    return ret;
}

HI_S32  HAL_OTP_V200_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32 bit_value)
{
    HI_U8 u8Data = 0;

    if(bit_value == 1)
    {
        u8Data = HAL_OTP_V200_ReadByte(addr);
        u8Data |= (1 << bit_pos);

        return HAL_OTP_V200_WriteByte(addr, u8Data);
    }
    else
    {
        //Do nothing when bit_value is 0.
    }
    return HI_SUCCESS;
}

EXPORT_SYMBOL(HAL_OTP_V200_Read);
EXPORT_SYMBOL(HAL_OTP_V200_ReadByte);
EXPORT_SYMBOL(HAL_OTP_V200_Write);
EXPORT_SYMBOL(HAL_OTP_V200_WriteByte);
EXPORT_SYMBOL(HAL_OTP_V200_WriteBit);

/*-------------------------------------END--------------------------------------*/

