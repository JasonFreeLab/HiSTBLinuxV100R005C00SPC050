#include "base.h"
#include "gpio.h"
#include "keyled.h"
#include "ir.h"
#include "timer.h"
#include "hdmi/hdmi_mcu_task.h"

HI_U8 g_u8ChipType = 0;
HI_U16 g_u16ChipId = 0;
static HI_U8 g_u8HighWakeUp;

static DATA_U32_S g_u32GpioPort;
static HI_U8 kltype = 0;

HI_U8 g_u8KeyEnterPmoc = 0x0;

HI_U8 g_u8GpioIEV = 0; //0:Falling edge or low level; 1: Rising edge or high level
HI_U8 g_u8GpioIBE = 0; //0:single edge; 1:double edge
HI_U8 g_u8GpioIS  = 0; //0:edge; 1: level

static HI_U8 g_u8CECWakeUpEnable = 0;

HI_U32 g_u32DateBaseAddr = DATA_BASE_ADDR;
HI_BOOL g_bAdvCaSupport = HI_FALSE;

HI_BOOL g_bBootSuspend = HI_FALSE;

#define DDRPHY_ARRAY_COUNT 4
#define DDRPHY_REG_COUNT 20
#define RESUME_FLAG 0x66031013

#define MCU_LOAD_CODE 0x12345678
#define ENTER_PMOC_FLAG 0x12345678
#define MCU_BOOT_SUSPEND_FLAG 0x12345678

#define KEYLED_TYPE_GPIOKEY 5

static HI_U8 g_u8CaVendorId;

#define CHECK_ADDR   0x0
#define CHECK_LENGTH 0xA00000
/*************************************************************************
                        main  module
*************************************************************************/
HI_U8 intStatus, intStatus1, intStatus2, intStatus3;
HI_VOID intr_process() interrupt 4
{
    HI_U8 i;

    if (HI_FALSE != pmocflag)
    {
        return;
    }

    EA = 0;
    INT_MASK_0 = 0x0;
    INT_MASK_1 = 0x0;
    INT_MASK_2 = 0x0;
    INT_MASK_3 = 0x0;

    intStatus  = INT_STATUS_IP0;
    intStatus1 = INT_STATUS_IP1;
    intStatus2 = INT_STATUS_IP2;
    intStatus3 = INT_STATUS_IP3;

    if (intStatus & 0x10) //bit4
    {
        for (i = 0; i < 4; i++)
        {
            if (g_u32GpioPort.val8[i] != 0)
            {
                gpio_isr(g_u32GpioPort.val8[i]);
                if (pmocflag == HI_TRUE)
                {
                    intStatus &= 0xef;
                }
            }
        }
    }

    /* The keyled who use GPIO to get key has no interrupt, so it needs other */
    /* interrupts to help itself to check key.                                */
#if (defined KEYLED_CT1642_INNER) || (defined KEYLED_74HC164)
    if ((intStatus & 0x10)) //bit4
#endif
    {
        if (kltype != KEYLED_TYPE_GPIOKEY)
        {
            KEYLED_Isr();
        }
    }

    if (intStatus & 0x02) //bit1
    {
        TIMER_Isr();
    }
    else if (intStatus & 0x08) //bit3
    {
        IR_Isr();
    }

    if (intStatus2 & 0x10) //bit20
    {
        /* clear the interrupt */
        regAddr.val32 = 0xf9840a00;
        read_regVal();
        regData.val8[3] = 0x60;
        write_regVal();

        pmocflag = HI_TRUE;
        pmocType = HI_UNF_PMOC_WKUP_ETH;
    }
    else if (intStatus2 & 0x01) //bit 16
    {
        //printf_char('u');
        pmocflag = HI_TRUE;
        pmocType = HI_UNF_PMOC_WKUP_USB;
    }

    if ((intStatus3 & 0x20) && (g_u8CECWakeUpEnable))//bit29
    {
        MCU_HDMI_TaskIrqHandle();
    }

    if (pmocflag == HI_FALSE)
    {
        INT_MASK_0 = 0x1a;
        INT_MASK_1 = 0x20;
        INT_MASK_2 = 0x11;
        
        if (g_u8CECWakeUpEnable)
        {
            INT_MASK_3 = 0x20;
        }
    }

    EA = 1;

    return;
}

HI_VOID MCUInit(HI_VOID)
{
    EA = 0;
    ARM_INTR_MASK = 0xff;  // intr mask
    INT_MASK_0 = 0x1a;     //  key ir timer intr
    INT_MASK_1 = 0x20;     // GPIO_STB1
    INT_MASK_2 = 0x11;     //GSF usb
    INT_MASK_3 = 0x00;

    RI = 0;
    TI = 0;
    ES = 1;

    pmocflag = HI_FALSE;

    return;
}

HI_VOID GetBaseParams(HI_VOID)
{
    /* Get the chip type */
    regAddr.val32 = CFG_BASE_ADDR + SC_GEN12;
    read_regVal();
    g_u8ChipType = regData.val8[3];
    g_u16ChipId  = regData.val16[0];
    g_bAdvCaSupport = regData.val8[2];

    /* Get the boot suspend flag */
    regAddr.val32 = DATA_BOOT_SUSPEND_FLAG;
    read_regVal();
    if (regData.val32 == MCU_BOOT_SUSPEND_FLAG)
    {
        g_bBootSuspend = HI_TRUE;
    }

    return;
}

HI_VOID PrintInitParams(HI_VOID)
{
#ifndef HI_ADVCA_RELEASE
    HI_U8 i;

    printf_str("======== [MCU PARAM] ======== \r\n");
    printf_str("Chip Type:");
    printf_hex(g_u8ChipType);
    printf_str("Chip Version:");
    printf_hex(g_u16ChipId);
    printf_str("Suspend Type:");
    printf_hex(g_u8HighWakeUp);
    printf_str("Reboot Enable:");
    printf_hex(wdgon);
    printf_str("Debug Mask:");
    printf_hex(dbgmask);
    printf_str("HDMI CEC Wakeup Enable:");
    printf_hex(g_u8CECWakeUpEnable);
    printf_str("Power Gpio No:");
    printf_hex(GpioValArray[0]);
    printf_str("Power Gpio Value:");
    printf_hex(GpioValArray[1]);
    printf_str("Display Mode:");
    printf_hex(time_type);
    printf_str("Display Time Hour:");
    printf_hex(time_hour);
    printf_str("Display Time Minute:");
    printf_hex(time_minute);
    printf_str("Display Time Second:");
    printf_hex(time_second);
    printf_str("WakeUp Time:");
    printf_hex(waittime.val32);
    printf_str("WakeUp key type:");
    printf_hex(kltype);
    printf_str("WakeUp Key:");
    printf_hex(klPmocVal);
    printf_str("IR Type:");
    printf_hex(ir_type);
    printf_str("IR No:");
    printf_hex(ir_pmocnum);

    for (i = 0; i < ir_pmocnum; i++)
    {
        printf_str("IR KeyLow:");
        printf_hex(irPmocLval[i].val32);
        printf_str("IR KeyHigh:");
        printf_hex(irPmocHval[i].val32);
    }

    if (g_bAdvCaSupport)
    {
        printf_str("Ca Vender ID:");
        printf_hex(g_u8CaVendorId);
    }

    printf_str("WakeUpGpioNo:");
    printf_hex(g_u32GpioPort.val32);

    printf_str("======== [MCU Init Ready] ======== \r\n");
#endif

    return;
}

HI_VOID GetInitParams(HI_VOID)
{
    HI_U8 i;

    /* Get the standby scene */
    regAddr.val32 = g_u32DateBaseAddr + DATA_CHIP;
    read_regVal();
    g_u8ChipType = regData.val8[3];
    g_u8HighWakeUp = regData.val8[2];
    g_u16ChipId = regData.val16[0];

    regAddr.val32 = g_u32DateBaseAddr + DATA_WDGON;
    read_regVal();
    wdgon = regData.val8[3] & 0x1;

    /* Get the debug param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_DBGMASK;
    read_regVal();
    dbgmask = regData.val8[3] & 0x7;
    g_u8CECWakeUpEnable = regData.val8[2];

    /*record gpio index, between 40 and 47 */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIO0;
    read_regVal();
    GpioValArray[0] = regData.val8[3];

    /*record gpio output, 1 or 0 */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIO1;
    read_regVal();
    GpioValArray[1] = regData.val8[3];
    g_u8GpioIEV = regData.val8[2];
    g_u8GpioIBE = regData.val8[1];
    g_u8GpioIS  = regData.val8[0];

    regAddr.val32 = g_u32DateBaseAddr + DATA_KEYTYPE;
    read_regVal();
    kltype = regData.val8[3];

    /* Get timer param */
    if (kltype != KEYLED_TYPE_GPIOKEY)
    {
        regAddr.val32 = g_u32DateBaseAddr + DATA_DISPMODE;
        read_regVal();
        time_type = regData.val8[3];

        regAddr.val32 = g_u32DateBaseAddr + DATA_DISPVAL;
        read_regVal();
        if (time_type == TIME_DISPLAY)
        {
            // timer display
            if ((regData.val8[1] >= 24)
                || (regData.val8[2] >= 60)
                || (regData.val8[3] >= 60))
            {
                // default value
                time_hour = 9;
                time_minute = 58;
                time_second = 0;
            }
            else
            {
                time_hour = regData.val8[1];
                time_minute = regData.val8[2];
                time_second = regData.val8[3];
            }
        }
    }

    /* Get the time out of wake up */
    regAddr.val32 = g_u32DateBaseAddr + DATA_TIMEVAL;
    read_regVal();
    waittime.val32 = regData.val32;

    regAddr.val32 = g_u32DateBaseAddr + DATA_KEYVAL;
    read_regVal();
    klPmocVal = regData.val8[3];

    if (g_bAdvCaSupport)
    {
        regAddr.val32 = g_u32DateBaseAddr + DATA_CAVENDOR;
        read_regVal();
        g_u8CaVendorId = regData.val8[3];
    }

    /* Get gpio port param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIOPORT;
    read_regVal();
    g_u32GpioPort.val32 = regData.val32;

    /* Get the IR param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_IRTYPE;
    read_regVal();
    ir_type = regData.val8[3];

    regAddr.val32 = g_u32DateBaseAddr + DATA_IRNUM;
    read_regVal();
    ir_pmocnum = regData.val8[3];
    if (ir_pmocnum > IR_PMOC_NUM)
    {
        ir_pmocnum = IR_PMOC_NUM;
    }

    regAddr.val32 = g_u32DateBaseAddr + DATA_IRVAL;
    for (i = 0; i < ir_pmocnum; i++)
    {
        read_regVal();
        irPmocLval[i].val32 = regData.val32;
        regAddr.val8[3] += 0x4;
        read_regVal();
        irPmocHval[i].val32 = regData.val32;
        regAddr.val8[3] += 0x4;
    }

    PrintInitParams();

    return;
}

void SaveRegToRam(HI_U32 u32DDRBaseAddr, HI_U32 u32DataBaseAddr, HI_U32 u32RegCount)
{
    HI_U8 i, j;
    HI_U32 u32TmpAddr;

    for (i = 0; i < DDRPHY_ARRAY_COUNT; i++)
    {
        regAddr.val32 = u32DataBaseAddr + i * (u32RegCount + 2) * 0x4;
        regData.val32 = u32RegCount;
        write_regValEx();

        regAddr.val32 = u32DataBaseAddr + i * (u32RegCount + 2) * 0x4 + 0x4;
        regData.val32 = u32DDRBaseAddr + 0x210 + i * 0x80;
        write_regValEx();

        for (j = 0; j < u32RegCount; j++)
        {
            regAddr.val32 = u32DDRBaseAddr + 0x210 + i * 0x80 + j * 0x4;
            read_regVal();
            regAddr.val32 = u32DataBaseAddr + i * (u32RegCount + 2) * 0x4 + 0x8 + j * 0x4;
            write_regValEx();
        }
    }

    u32TmpAddr = u32DataBaseAddr + DDRPHY_ARRAY_COUNT * (u32RegCount + 2) * 0x4;

    /* save (0x21c + 0x400), (0x220 + 0x400), (0x224 + 0x400) */
    for (i = 0; i < DDRPHY_ARRAY_COUNT; i++)
    {
        regAddr.val32 = u32TmpAddr;
        regData.val32 = 3;
        write_regValEx();

        regAddr.val32 = u32TmpAddr + 0x4;
        regData.val32 = u32DDRBaseAddr + 0x21c + i * 0x80 + 0x400;
        write_regValEx();

        for (j = 0; j < 3; j++)
        {
            regAddr.val32 = u32DDRBaseAddr + 0x21c + i * 0x80 + 0x400 + j * 0x4;
            read_regVal();
            regAddr.val32 = u32TmpAddr + 0x8 + j * 0x4;
            write_regValEx();
        }

        u32TmpAddr += 5 * 0x4;

        /* save (0x240 + 0x400) */
        regAddr.val32 = u32TmpAddr;
        regData.val32 = 1;
        write_regValEx();

        regAddr.val32 = u32TmpAddr + 0x4;
        regData.val32 = u32DDRBaseAddr + 0x240 + i * 0x80 + 0x400;
        write_regValEx();

        regAddr.val32 = u32DDRBaseAddr + 0x240 + i * 0x80 + 0x400;
        read_regVal();
        regAddr.val32 = u32TmpAddr + 0x8;
        write_regValEx();

        u32TmpAddr += 3 * 0x4;

        /* save 0x270 0x274 for ddr4*/
        regAddr.val32 = u32TmpAddr;
        regData.val32 = 2;
        write_regValEx();

        regAddr.val32 = u32TmpAddr + 0x4;
        regData.val32 = u32DDRBaseAddr + 0x270 + i * 0x80;
        write_regValEx();

        for (j = 0; j < 2; j++)
        {
            regAddr.val32 = u32DDRBaseAddr + 0x270 + i * 0x80 + j * 0x4;
            read_regVal();
            regAddr.val32 = u32TmpAddr + 0x8 + j * 0x4;
            write_regValEx();
        }
        u32TmpAddr += 4 * 0x4;

    }

    /* set (u32DDRBaseAddr + 0x70) bit 20(19 in 98cv200) to 1 */
    regAddr.val32 = u32TmpAddr;
    regData.val32 = 1;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x4;
    regData.val32 = u32DDRBaseAddr + 0x70;
    write_regValEx();

    regAddr.val32 = u32DDRBaseAddr + 0x70;
    read_regVal();
    regData.val8[1] |= 0x08;
    regAddr.val32 = u32TmpAddr + 0x8;
    write_regValEx();

    /* set (u32DDRBaseAddr + 0x70) bit 20(19 in 98cv200) to 0 */
    regAddr.val32 = u32TmpAddr + 0xc;
    regData.val32 = 1;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x10;
    regData.val32 = u32DDRBaseAddr + 0x70;
    write_regValEx();

    regAddr.val32 = u32DDRBaseAddr + 0x70;
    read_regVal();
    regData.val8[1] &= 0xf7;
    regAddr.val32 = u32TmpAddr + 0x14;
    write_regValEx();

    /* set (u32DDRBaseAddr + 0x70) bit 15 to 1 */
    regAddr.val32 = u32TmpAddr + 0x18;
    regData.val32 = 1;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x1c;
    regData.val32 = u32DDRBaseAddr + 0x04;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x20;
    regData.val32 = 0x8000;
    write_regValEx();

    /* set (u32DDRBaseAddr + 0x70) bit 15 to 0 */
    regAddr.val32 = u32TmpAddr + 0x24;
    regData.val32 = 1;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x28;
    regData.val32 = u32DDRBaseAddr + 0x04;
    write_regValEx();

    regAddr.val32 = u32TmpAddr + 0x2c;
    regData.val32 = 0x0;
    write_regValEx();

    return;
}

void DDRPHYRegSave(void)
{
    HI_U32 u32DDRPHY0BaseAddr = 0;
    HI_U32 u32DataBaseAddr, u32DDRPHYCount;

    u32DDRPHYCount = 13;
    u32DDRPHY0BaseAddr = DDRPHY0_BASE_ADDR_98CV200_A;

    u32DataBaseAddr = DATA_PHY_BASE_ADDR;
    SaveRegToRam(u32DDRPHY0BaseAddr, u32DataBaseAddr, u32DDRPHYCount);

    u32DataBaseAddr += (DDRPHY_ARRAY_COUNT * (u32DDRPHYCount + 2) + 12) * 0x4;

    u32DataBaseAddr +=  DDRPHY_ARRAY_COUNT * 12 * 0x4;

    /*  set the last value to 0, so bootrom will recognize the end */
    regAddr.val32 = u32DataBaseAddr;
    regData.val32 = 0;
    write_regValEx();

    /* save the address of c51 ram to SC_GEN16 for bootrom restoring ddr phy reg */
    regAddr.val32 = CFG_BASE_ADDR + SC_GEN16;
    regData.val32 = DATA_PHY_BASE_ADDR;
    write_regVal();

    return;
}

void DDREnterSelf(void)
{  
        HI_U32 u32DDRC0BaseAddr, u32DDRPHY0BaseAddr;

        u32DDRC0BaseAddr = DDRC0_BASE_ADDR_98CV200_A;
        u32DDRPHY0BaseAddr = DDRPHY0_BASE_ADDR_98CV200_A;
    
        /* Config DDR to self-refresh state */
        regAddr.val32 = u32DDRC0BaseAddr + DDR_SREF;
        read_regVal();
        regData.val8[3] = 0x01;
        write_regVal();

        /* Whether DDR change to self-refresh state */
        while (1)
        {
            regAddr.val32 = u32DDRC0BaseAddr + DDR_STATUS;
            read_regVal();
            if ((regData.val8[3] & 0x1) == 0x1) //bit0
            {
                break;
            }
        }

        wait_minute_2(10, 10);

        /* cs/ck/oe disable to reduce power */
        regAddr.val32 = DDRPHY0_BASE_ADDR_98CV200_A + 0x78;
        read_regVal();
        regData.val8[3] &= 0x7f;
        write_regVal();

        regAddr.val32 = DDR_PHYCTRL0_28NM_ADDR;
        regData.val32 = 0x2800;
        write_regVal();

        /* enable DDRPHY retention */
        regAddr.val32 = CFG_BASE_ADDR + DDR_PHY_ISO;
        read_regVal();
        regData.val8[3] &= 0xfc;
        regData.val8[3] |= 0x02;
        write_regVal();
}

void GetTimePeriod(void)
{
    HI_U32 u32TimePeriod = 0;

    regAddr.val32 = g_u32DateBaseAddr + DATA_TIMEVAL;
    read_regVal();
    u32TimePeriod = regData.val32 - waittime.val32;

    /* save standby period in 51 ram */
    regAddr.val32 = DATA_PERIOD;
    regData.val32 = u32TimePeriod;
    write_regValEx();

#ifndef HI_ADVCA_RELEASE
    printf_str("Suspend Period:");
    printf_hex(u32TimePeriod);
#endif

    return;
}

void SystemPowerDown(void)
{
    /*set the delay 100ms between power up and  revocation of reset*/
    /* (1000 / 12) * 0x124f80 ns  */
    regAddr.val32 = 0xf8000038;
    regData.val32 = 0x124f80;
    write_regVal();

    regAddr.val32 = 0xf8000008;
    regData.val32 = 0x0;
    write_regVal();
    while (1)
    {
        regAddr.val32 = 0xf8000040;
        read_regVal();
        if ((regData.val8[3] & 0xf0) == 0x60) //bit[7:4]
        {
            break;
        }
    }
    
    return;
}

void LowPowerSet()
{
#if 0
    /* test code */
    regAddr.val32 = 0xf8ce4800;
    read_regVal();
    printf_hex(regData.val32);

    regAddr.val32 = 0xf8ce4828;
    regData.val32 = 0x12;
    write_regVal();
    regData.val32 = 0;
    read_regVal();
    printf_hex(regData.val32);
#endif

    printf_str("Low power set \r\n");
    
    /* switch cpu clock to xtal */
    regAddr.val32 = 0xf8a22048;
    regData.val32 = 0x204;
    write_regVal();
    regData.val32 = 0x604;
    write_regVal();

    /* close cpu clk  don't reset cluster_cold_srst_req */
    /* for it will cause mcu could not access power down area*/
    regAddr.val32 = 0xf8a22050;
    regData.val32 = 0x1e0ff80;
    write_regVal();

    /* switch bus clock to  xtal */
    regAddr.val32 = 0xf8a22058;
    regData.val32 = 0x0;
    write_regVal();

    /* APLL power down */
    regAddr.val32 = 0xf8a22004;
    regData.val32 = 0x081020C8;
    write_regVal();

    /* BPLL power down */
    regAddr.val32 = 0xf8a2200c;
    regData.val32 = 0x0210307D;
    //write_regVal();

    /* DPLL power down */
    regAddr.val32 = 0xf8a22014;
    regData.val32 = 0x0A103075;
    write_regVal();

    /* VPLL power down */
    regAddr.val32 = 0xf8a22024;
    regData.val32 = 0x0A1020E1;
    write_regVal();

    /* HPLL power down */
    regAddr.val32 = 0xf8a2202c;
    regData.val32 = 0x0A102063;
    write_regVal();

    /* EPLL power down */
    regAddr.val32 = 0xf8a22034;
    regData.val32 = 0x0810208F;
    write_regVal();

    /* QPLL power down */
    regAddr.val32 = 0xf8a2203c;
    regData.val32 = 0x0A1020C8;
    write_regVal();

    /* DDR power down */
    regAddr.val32 = 0xf8a22064;
    regData.val32 = 0xd00;
    write_regVal();

#if 0
    /* UART power down */
    regAddr.val32 = 0xf8a22068;
    regData.val32 = 0xa0;
    write_regVal();
#endif
    /* I2C power down */
    regAddr.val32 = 0xf8a2206c;
    regData.val32 = 0x2220;
    write_regVal();

    /* SSP power down */
    regAddr.val32 = 0xf8a22070;
    regData.val32 = 0x2;
    write_regVal();

    /* SCI power down */
    regAddr.val32 = 0xf8a22074;
    regData.val32 = 0xa;
    write_regVal();

    /* VDH power down */
    regAddr.val32 = 0xf8a22078;
    regData.val32 = 0x70;
    write_regVal();
    
    /* JPGD power down */
    regAddr.val32 = 0xf8a2207c;
    regData.val32 = 0x10;
    write_regVal();

    /* PGD power down */
    regAddr.val32 = 0xf8a22084;
    regData.val32 = 0x10;
    write_regVal();

    /* BPD power down */
    regAddr.val32 = 0xf8a22088;
    regData.val32 = 0x10;
    write_regVal();

    /* VENC power down */
    regAddr.val32 = 0xf8a2208c;
    regData.val32 = 0x10;
    write_regVal();
    
    /* JPGE power down */
    regAddr.val32 = 0xf8a22090;
    regData.val32 = 0x10;
    write_regVal();
   
    /* TDE power down */
    regAddr.val32 = 0xf8a22094;
    regData.val32 = 0x10;
    write_regVal();

    /* SDIO power down */
    regAddr.val32 = 0xf8a2209c;
    regData.val32 = 0x310;
    write_regVal();

    /* EMMC power down */
    regAddr.val32 = 0xf8a220a0;
    regData.val32 = 0x310;
    write_regVal();

    /* SATA power down */
    regAddr.val32 = 0xf8a220a8;
    regData.val32 = 0xf00;
    write_regVal();

    /* USB3 power down */
    regAddr.val32 = 0xf8a220b0;
    regData.val32 = 0x1000;
    write_regVal();

    /* USB2 power down */
    regAddr.val32 = 0xf8a220b8;
    regData.val32 = 0x37000;
    write_regVal();

    /* USB2 PHY power down */
    regAddr.val32 = 0xf8a220bc;
    regData.val32 = 0x18750;
    write_regVal();

    /* CA power down */
    regAddr.val32 = 0xf8a220c0;
    regData.val32 = 0x600;
    write_regVal();
    
    /* SHA power down */
    regAddr.val32 = 0xf8a220c4;
    regData.val32 = 0x50;
    write_regVal();

#if 0
    /* PMC power down */
    regAddr.val32 = 0xf8a220c8;
    regData.val32 = 0x10;
    write_regVal();
#endif

    /* GSF power down */
    regAddr.val32 = 0xf8a220cc;
    regData.val32 = 0x25;
    write_regVal();

    /* ETH power down */
    regAddr.val32 = 0xf8a220d0;
    regData.val32 = 0x0;
    write_regVal();

    /* GPU power down */
    regAddr.val32 = 0xf8a220d4;
    regData.val32 = 0x10;
    write_regVal();

    /* VDP1 power down */
    regAddr.val32 = 0xf8a220d8;
    regData.val32 = 0x40000000;
    write_regVal();

    /* VPSS power down */
    regAddr.val32 = 0xf8a220f0;
    regData.val32 = 0x10;
    write_regVal();

    /* PVR power down */
    regAddr.val32 = 0xf8a220fc;
    regData.val32 = 0x1000000;
    write_regVal();

    /* HDMI power down */
    regAddr.val32 = 0xf8a2210c;
    regData.val32 = 0x3c0;
    //write_regVal();

    /* HDMI PHY power down */
    regAddr.val32 = 0xf8a22110;
    regData.val32 = 0x30;
    write_regVal();

    /* ADAC power down */
    regAddr.val32 = 0xf8a22114;
    regData.val32 = 0x10;
    write_regVal();

    /* AIAO power down */
    regAddr.val32 = 0xf8a22118;
    regData.val32 = 0x10;
    write_regVal();

    /* VDAC power down */
    regAddr.val32 = 0xf8a2211c;
    regData.val32 = 0x0;
    write_regVal();

    /* COMBO PHY down */
    regAddr.val32 = 0xf8a22188;
    regData.val32 = 0x10;
    write_regVal();

    /* PCIE power down */
    regAddr.val32 = 0xf8a2218c;
    regData.val32 = 0x70;
    write_regVal();

    /* SDIO1 power down */
    regAddr.val32 = 0xf8a2228c;
    regData.val32 = 0x310;
    write_regVal();

    /* VDP2 down */
    regAddr.val32 = 0xf8a2234c;
    regData.val32 = 0x20000000;
    write_regVal();

    /* FMC down */
    regAddr.val32 = 0xf8a22380;
    regData.val32 = 0x90;
    write_regVal();

    /* FEPHY down */
    regAddr.val32 = 0xf8a22388;
    regData.val32 = 0x10;
    write_regVal();

    /* DMAC down */
    regAddr.val32 = 0xf8a2238c;
    regData.val32 = 0x10;
    write_regVal();

    /* GZIP down */
    regAddr.val32 = 0xf8a22390;
    regData.val32 = 0x10;
    write_regVal();

    /* PCIE IO down */
    regAddr.val32 = 0xf8a20850;
    regData.val32 = 0x0;
    write_regVal();

    /*set cpu volt to 800mv */
    regAddr.val32 = 0xf8a23018;
    regData.val32 = 0x00b500dd;
    write_regVal();

    /*set core volt to 800mv */
    regAddr.val32 = 0xf8a23020;
    regData.val32 = 0x00b500dd;
    write_regVal();

#if 1
    /* set stb_power_off to gpio5_6 */
    regAddr.val32 = 0xf8000044;
    read_regVal();
    regData.val8[2] |= 0x1;
    write_regVal();

    regAddr.val32 = 0xf8004400;
    read_regVal();
    regData.val32 |= 0x40;
    write_regVal();

    regAddr.val32 = 0xf8004100;
    regData.val32 = 0x0;
    write_regVal();
#endif

    return;
}

HI_VOID ClockPowerDown(HI_VOID)
{
    //choose ddr timer to 24M
    regAddr.val32 = CRG_BASE_ADDR + 0x128;
    read_regVal();
    regData.val32 = 0x304;
    write_regVal();
    regData.val32 = 0x704;
    write_regVal();

    /* GPU Power Down */
    regAddr.val32 = PMC_BASE_ADDR + 0xb0;
    read_regVal();
    regData.val8[3] = 0x0c;
    write_regVal();

    //switch bus to 24M
    regAddr.val32 = CRG_BASE_ADDR + 0x58;
    regData.val32 = 0;
    write_regVal();

    //APLL  power down
    regAddr.val32 = CRG_BASE_ADDR + 0x04;
    read_regVal();
    regData.val8[1] |= 0x10;
    write_regVal();

    //HPLL  power down
    regAddr.val32 = CRG_BASE_ADDR + 0x2c;
    read_regVal();
    regData.val8[1] |= 0x10;
    write_regVal();

    //QPLL  power down.
    regAddr.val32 = CRG_BASE_ADDR + 0x44;
    read_regVal();
    regData.val8[1] |= 0x10;
    write_regVal();

    return;
}

void SystemSuspend(void)
{

    /* CPU Reset*/
    regAddr.val32 = PMC_BASE_ADDR + PERI_PMC47;
    read_regVal();
    regData.val8[2] |= 0x02; //bit9
    write_regVal();

    if ((g_u8CaVendorId != CA_VENDOR_ID_NAGRA) || (!g_bAdvCaSupport))
    {
        if ((0x0 == wdgon) && (0x0 == g_u8KeyEnterPmoc))
        {
            DDREnterSelf();
        }
    }

    /* change MCU bus clock to 24M / 8 */
    regAddr.val32 = CFG_BASE_ADDR + MCU_CTRL;
    read_regVal();
    regData.val8[3] &= 0xfc; //bit [1:0] = 0x0
    write_regVal();

    if ((NORMAL_WAKEUP != g_u8HighWakeUp))
    {
       ClockPowerDown();
    }

    if (!(dbgmask & 0x4))
    {
        if (NORMAL_WAKEUP == g_u8HighWakeUp)
        {
            SystemPowerDown();
        }    
    }

    return;
}

HI_VOID SystemResume(HI_VOID)
{
    if (!(dbgmask & 0x4))
    {
        if (g_u8HighWakeUp != NORMAL_WAKEUP)
        {
            SystemPowerDown();
        }

        /* power up */
        regAddr.val32 = 0xf8000008;
        regData.val32 = 0x1;
        write_regVal();

        while (1)
        {
            wait_minute_2(10, 10);
        }
    }

    return;
}

void WaitforEnterFlag(void)
{
    while (1)
    {
        wait_minute_2(200, 200);

        /* read kernel flag to break; */
        regAddr.val32 = DATA_ENTER_FLAG;
        read_regVal();
        if (ENTER_PMOC_FLAG == regData.val32)
        {
            regData.val32 = 0x0;
            write_regVal();
            break;
        }
        else if (TEMP_CHECK_TO_SUSPEND == regData.val32)
        {
            regData.val32 = 0x0;
            write_regVal();
            g_u8KeyEnterPmoc = 0x1;
            break;
        }
    }
}

void WaitforEnterStandbyFlag(void)
{
    HI_U8 u8Data = 0xff;
    HI_U32 u32Count = 0;

    regAddr.val32 = DATA_SUSPEND_FLAG;
    read_regVal();

    /* first power, jump wait */
    if (regData.val32 == MCU_LOAD_CODE)
    {
        return;
    }

    /* Get gpio port param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIOPORT;
    read_regVal();
    g_u32GpioPort.val8[3] = regData.val8[3];

    while (1)
    {
        wait_minute_2(10, 10);

        //check advca pmoc flag
        if (g_bAdvCaSupport)
        {
            regAddr.val32 = (CFG_BASE_ADDR + SC_GEN15);
            read_regVal();
            if(PMOC_CHECK_TO_SUSPEND == regData.val32)
            {
                regData.val32 = 0;
                write_regVal();
                break;
            }
        }

        /* read kernel flag to break; */
        regAddr.val32 = DATA_ENTER_FLAG;
        read_regVal();
        if (ENTER_PMOC_FLAG == regData.val32)
        {
            regData.val32 = 0x0;
            write_regVal();
            break;
        }
        else if (TEMP_CHECK_TO_SUSPEND == regData.val32)
        {
            regData.val32 = 0x0;
            write_regVal();
            g_u8KeyEnterPmoc = 0x1;
            break;
        }

        if (g_u32GpioPort.val8[3] == 0)
        {
            continue;
        }

        gpio5_read_bit(g_u32GpioPort.val8[3] % 8, &u8Data);
        if (0 == u8Data)
        {
            u32Count++;
            if (u32Count > 1000)
            {
                g_u8KeyEnterPmoc = 0x1;
                u32Count = 0;
            }
        }
        else
        {
            if (0x1 == g_u8KeyEnterPmoc)
            {
                u32Count++;
                if (u32Count > 1000)
                {
                    break;
                }
            }
            else
            {
                u32Count = 0;
            }
        }
    }
}

HI_VOID SaveStandbyFlag(HI_VOID)
{
    regAddr.val32 = DATA_SUSPEND_FLAG;
    read_regVal();
    if ((regData.val32 != MCU_LOAD_CODE)
        && (0x0 == wdgon)
        && (0x0 == g_u8KeyEnterPmoc))
    {
        // Set resume flag for boot.
        regAddr.val32 = CFG_BASE_ADDR + SC_GEN0;
        regData.val32 = RESUME_FLAG;
        write_regVal();
    }

    // record wakeup type in C51 Ram
    regAddr.val32 = DATA_WAKEUPTYPE;
    regData.val32 = 0x0;
    regData.val8[3] = pmocType;
    write_regValEx();

    return;
}

HI_VOID SetDDRWakeUpParams(HI_VOID)
{
    regAddr.val32 = DATA_BASE_ADDR + 0x800 + 6 * 0x4;;
    regData.val32 = CHECK_ADDR;
    write_regValEx();

    regAddr.val32 = DATA_BASE_ADDR + 0x800 + 7 * 0x4;
    regData.val32 = CHECK_LENGTH;
    write_regValEx();

    return;
}

HI_VOID GetDDRWakeUpParams(HI_VOID)
{
    HI_U32 u32TempVal = 0;
    HI_U8 i;

    //check whether otp bit:ddr_wakeup_disable is enabled,
    regAddr.val32 = 0xF8AB0080; //  0xF8AB0080[4],  0x0[4]:0:enable;1:disabled
    read_regVal();
    u32TempVal = regData.val32;
    if (0x0 != (u32TempVal & 0x10))
    {
    #ifndef HI_ADVCA_RELEASE
        printf_str("------------------DDR wakeup is disabled------------------\r\n");
    #endif
        return;
    }

#ifndef HI_ADVCA_RELEASE
    printf_str("------------------DDR wakeup is enabled, start DDR wakeup progress------------------\r\n");
#endif

    regAddr.val32 = CFG_BASE_ADDR + SC_GEN19;
    regData.val32 = DATA_BASE_ADDR + 0x800;
    write_regVal();

    /* Read the ddr wakeup checking data from SC_GEN59,  then write it to 51 RAM */
    for (i = 0; i < 5; i++)
    {
        regAddr.val32 = CFG_BASE_ADDR + SC_GEN59 + i * 0x4;//HASH[i]
        read_regVal();
        regAddr.val32 = DATA_BASE_ADDR + 0x800 + i * 0x4;
        write_regValEx();
    }

    regAddr.val32 = DATA_BASE_ADDR + 0x800 + 5 * 0x4;
    regData.val32 = 0x01;
    write_regValEx();
   
    regAddr.val32 = DATA_BASE_ADDR + 0x800 + 6 * 0x4;
    regData.val32 = CHECK_ADDR;
    write_regValEx();
    
    regAddr.val32 = DATA_BASE_ADDR + 0x800 + 7 * 0x4;
    regData.val32 = CHECK_LENGTH;
    write_regValEx();
    
    return;
}

HI_VOID ADVCA_CHECK(HI_VOID)
{
    SetDDRWakeUpParams(); //for A9 calculate HASH
    while(1)
    {
        regAddr.val32 = (CFG_BASE_ADDR + SC_GEN15);
        read_regVal();
        if(PMOC_CHECK_TO_SUSPEND == regData.val32) //check pmoc flag
        {
            regAddr.val32 = (CFG_BASE_ADDR + SC_GEN15);
            regData.val32 = 0;
            write_regVal();
            break;
        }

        regAddr.val32 = DATA_ENTER_FLAG;
        read_regVal();
        if(TEMP_CHECK_TO_SUSPEND == regData.val32) //check temp control to pm
        {
            regAddr.val32 = DATA_ENTER_FLAG;
            regData.val32 = 0;
            write_regVal();
            g_u8KeyEnterPmoc = 0x1;
            return;
        }

        wait_minute_2(100,100);
    }

    GetDDRWakeUpParams();
}


void main()
{
    HI_U8 i;

    while (1)
    {
        MCUInit();

        GetBaseParams();

        if (g_bBootSuspend == HI_TRUE)
        {
            WaitforEnterStandbyFlag();
        }
        else
        {
            if (g_bAdvCaSupport)
            {
                ADVCA_CHECK();
            }
            else
            {
                WaitforEnterFlag();
            }
        }

#ifndef HI_ADVCA_RELEASE
        dbgmask = 4;
        printf_str("Enter MCU \r\n");
#endif

        GetInitParams();

        if (kltype != KEYLED_TYPE_GPIOKEY)
        {
            KEYLED_Init();
        }

        TIMER_Init();

        for (i = 0; i < 4; i++)
        {
            if (g_u32GpioPort.val8[i] != 0)
            {
                gpio_SetIntType(g_u32GpioPort.val8[i]);
            }
        }

        if ((g_u8CaVendorId != CA_VENDOR_ID_NAGRA) || (!g_bAdvCaSupport))
        {
            if ((0x0 == wdgon) && (0x0 == g_u8KeyEnterPmoc))
            {
                DDRPHYRegSave();
            }
        }

        SystemSuspend();

        if (kltype != KEYLED_TYPE_GPIOKEY)
        {
            KEYLED_Early_Display();
        }

        TIMER_Enable();

        for (i = 0; i < 4; i++)
        {
            if (g_u32GpioPort.val8[i] != 0)
            {
                gpio_IntEnable(g_u32GpioPort.val8[i], HI_TRUE);
            }
        }

        IR_Init();
        IR_Start();

        if (g_u8CECWakeUpEnable)
        {
            MCU_HDMI_TaskInit();
        }

#ifndef HI_ADVCA_RELEASE
        printf_str("Enter while circle \r\n");
#endif

        while (1)
        {
            wait_minute_2(10, 10);
            EA = 0;

            if (g_u8CECWakeUpEnable)
            {
                MCU_HDMI_TaskHandle();
            }
        
            if (pmocflag)
            {
                break;
            }

            EA = 1;
        }

#ifndef HI_ADVCA_RELEASE
        printf_str("Quit while circle \r\n");
#endif

        if (kltype != KEYLED_TYPE_GPIOKEY)
        {
            KEYLED_Disable();
        }

        if (g_u8CECWakeUpEnable)
        {
            MCU_HDMI_TaskDeInit();
        }
    
        IR_Disable();

        TIMER_Disable();

        SaveStandbyFlag();

        GetTimePeriod();

        // resume system
        SystemResume();

#ifndef HI_ADVCA_RELEASE
        printf_str("Resume from MCU \r\n");
        printf_str("Resume Type:");
        printf_hex(pmocType);
#endif

        // wait for cpu power up to shut down mcu.
        while (!g_bAdvCaSupport)
        {
            wait_minute_2(10, 10);
        }
    }

    return;
}
