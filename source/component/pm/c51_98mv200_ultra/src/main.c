#include "base.h"
#include "gpio.h"
#include "keyled.h"
#include "ir.h"
#include "timer.h"

static DATA_U32_S g_u32GpioPort;
static HI_U8 kltype = 0;

HI_U8 g_u8GpioIEV = 0; //0:Falling edge or low level; 1: Rising edge or high level
HI_U8 g_u8GpioIBE = 0; //0:single edge; 1:double edge
HI_U8 g_u8GpioIS  = 0; //0:edge; 1: level

HI_U32 g_u32DateBaseAddr = DATA_BASE_ADDR;

#define RESUME_FLAG 0x66031013
#define MCU_LOAD_CODE 0x12345678
#define ENTER_PMOC_FLAG 0x12345678

#define KEYLED_TYPE_GPIOKEY 5
#define PARAM_COUNT 26

/*************************************************************************
                        main  module
*************************************************************************/
HI_U8 intStatus;
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

    intStatus  = INT_STATUS_IP0;

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

    if (pmocflag == HI_FALSE)
    {
        INT_MASK_0 = 0x1a;
    }

    EA = 1;

    return;
}

HI_VOID MCUInit(HI_VOID)
{
    EA = 0;
    ARM_INTR_MASK = 0xff;  // intr mask
    INT_MASK_0 = 0x1a;     //  key ir timer intr
    INT_MASK_1 = 0x0;
    INT_MASK_2 = 0x0;
    INT_MASK_3 = 0x0;

    RI = 0;
    TI = 0;
    ES = 1;

    pmocflag = HI_FALSE;

    return;
}

HI_VOID GetBaseParams(HI_VOID)
{
    HI_U8 i;

    for (i = 0; i < PARAM_COUNT; i++)
    {
        regAddr.val32 = SC_GEN32_ADDR + i * 4;
        read_regVal();
        regAddr.val32 = g_u32DateBaseAddr + i * 4;
        write_regValEx();
    }
    return;
}

HI_VOID PrintInitParams(HI_VOID)
{
#ifndef HI_ADVCA_RELEASE
    HI_U8 i;

    printf_str("======== [MCU PARAM] ======== \r\n");
    printf_str("Debug Mask:");
    printf_hex(dbgmask);
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

    printf_str("WakeUpGpioNo:");
    printf_hex(g_u32GpioPort.val32);

    printf_str("======== [MCU Init Ready] ======== \r\n");
#endif

    return;
}

HI_VOID GetInitParams(HI_VOID)
{
    HI_U8 i;

    /* Get the debug param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_DBGMASK;
    read_regValEx();
    dbgmask = regData.val8[3] & 0x7;

    /*record gpio index, between 40 and 47 */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIO0;
    read_regValEx();
    GpioValArray[0] = regData.val8[3];

    /*record gpio output, 1 or 0 */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIO1;
    read_regValEx();
    GpioValArray[1] = regData.val8[3];
    g_u8GpioIEV = regData.val8[2];
    g_u8GpioIBE = regData.val8[1];
    g_u8GpioIS  = regData.val8[0];

    regAddr.val32 = g_u32DateBaseAddr + DATA_KEYTYPE;
    read_regValEx();
    kltype = regData.val8[3];

    /* Get timer param */
    if (kltype != KEYLED_TYPE_GPIOKEY)
    {
        regAddr.val32 = g_u32DateBaseAddr + DATA_DISPMODE;
        read_regValEx();
        time_type = regData.val8[3];

        regAddr.val32 = g_u32DateBaseAddr + DATA_DISPVAL;
        read_regValEx();
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
    read_regValEx();
    waittime.val32 = regData.val32;

    regAddr.val32 = g_u32DateBaseAddr + DATA_KEYVAL;
    read_regValEx();
    klPmocVal = regData.val8[3];

    /* Get gpio port param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_GPIOPORT;
    read_regValEx();
    g_u32GpioPort.val32 = regData.val32;

    /* Get the IR param */
    regAddr.val32 = g_u32DateBaseAddr + DATA_IRTYPE;
    read_regValEx();
    ir_type = regData.val8[3];

    regAddr.val32 = g_u32DateBaseAddr + DATA_IRNUM;
    read_regValEx();
    ir_pmocnum = regData.val8[3];
    if (ir_pmocnum > IR_PMOC_NUM)
    {
        ir_pmocnum = IR_PMOC_NUM;
    }

    regAddr.val32 = g_u32DateBaseAddr + DATA_IRVAL;
    for (i = 0; i < ir_pmocnum; i++)
    {
        read_regValEx();
        irPmocLval[i].val32 = regData.val32;
        regAddr.val8[3] += 0x4;
        read_regValEx();
        irPmocHval[i].val32 = regData.val32;
        regAddr.val8[3] += 0x4;
    }

    PrintInitParams();

    return;
}

void GetTimePeriod(void)
{
    HI_U32 u32TimePeriod = 0;

    regAddr.val32 = g_u32DateBaseAddr + DATA_TIMEVAL;
    read_regValEx();
    u32TimePeriod = regData.val32 - waittime.val32;

    /* save standby period in gen */
    regAddr.val32 = DATA_PERIOD;
    regData.val32 = u32TimePeriod;
    write_regVal();

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

void SystemSuspend(void)
{
    /* CPU Reset*/
    regAddr.val32 = PMC_BASE_ADDR + PERI_PMC47;
    read_regVal();
    regData.val8[2] |= 0x02; //bit9
    write_regVal();

    /* change MCU bus clock to 24M */
    regAddr.val32 = CFG_BASE_ADDR + MCU_CTRL;
    read_regVal();
    regData.val8[3] &= 0xfc; //bit [1:0] = 0x0
    write_regVal();

#ifndef HI_ADVCA_RELEASE
    if (!(dbgmask & 0x4))
#endif
    {
        SystemPowerDown();
    }

    return;
}

HI_VOID SystemResume(HI_VOID)
{
#ifndef HI_ADVCA_RELEASE
    if (!(dbgmask & 0x4))
#endif
    {
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

        regAddr.val32 = (CFG_BASE_ADDR + SC_GEN15);
        read_regVal();
        if(PMOC_CHECK_TO_SUSPEND == regData.val32) 
        {
            regData.val32 = 0;
            write_regVal();
            break;
        }
    }
}

HI_VOID SaveStandbyFlag(HI_VOID)
{
    // record wakeup type in sc_gen
    regAddr.val32 = DATA_WAKEUPTYPE;
    regData.val32 = 0x0;
    regData.val8[3] = pmocType;
    write_regVal();

    return;
}

void main()
{
    HI_U8 i;

    while (1)
    {
        MCUInit();

        WaitforEnterFlag();

        GetBaseParams();

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

#ifndef HI_ADVCA_RELEASE
        printf_str("Enter while circle \r\n");
#endif

        while (1)
        {
            wait_minute_2(10, 10);
            EA = 0;
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

    }

    return;
}
