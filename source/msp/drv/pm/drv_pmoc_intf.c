#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <asm/memory.h>
#include <linux/linkage.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/reboot.h>
#include "hi_common.h"
#include "hi_drv_pmoc.h"
#include "drv_pmoc_ioctl.h"
#include "hi_osal.h"

#include "hi_reg_common.h"
#include "hi_kernel_adapt.h"

#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_drv_reg.h"
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "clock.h"

#include "drv_pmoc_priv.h"
#include "drv_gpio_ext.h"
#include <linux/kthread.h>
#include "hi_dvfs.h"
#include "drv_pmoc_ext.h"
#include "hipm.h"

/* for tee */
#ifdef HI_TEE_MCU_SUPPORT
#include "tee_client_api.h"
static TEEC_Context      g_TeeContext;
static TEEC_Session      g_TeeSession;
#endif

extern unsigned int mpu_get_volt(void);
extern void         mpu_init_volt(void);

extern void         hi_cpufreq_exit(void);
extern void         mpu_exit_clocks(void);
extern unsigned int core_get_volt(void);
extern void         core_init_volt(void);
extern void         core_init_hpm(void);
extern void         mpu_deinit_volt(void);

extern int          cpufreq_gov_debug_init(void);
extern int          cpufreq_gov_dbs_init(void);
extern int          hi_cpufreq_init(void);
extern int          regulator_pwm_voltage_init(void);
extern int          cpu_volt_scale(unsigned int volt);
extern int          core_volt_scale(unsigned int volt);

extern struct clk mpu_ck;
extern unsigned int cur_cpu_volt;
extern unsigned int cur_core_volt;
extern unsigned int init_core_volt;

#ifdef HI_DVFS_CPU_SUPPORT
extern unsigned int cpu_dvfs_enable;
extern struct mutex hi_dvfs_lock;
extern int          pm_cpufreq_boost(void);
HI_U32 * g_pPMCStart = HI_NULL_PTR;
static HI_U32 g_u32TempTrim = 0;
#ifdef HI_TEMP_CTRL_CONFIG
#define TEMP_DOWN HI_TEMP_CTRL_DOWN_THRESHOLD
#define TEMP_UP HI_TEMP_CTRL_UP_THRESHOLD
#define TEMP_REBOOT HI_TEMP_CTRL_REBOOT_THRESHOLD
#define TEMP_STATUS_NORMAL  0x0
#define TEMP_STATUS_CONTROL 0x22222222
#define TEMP_STATUS_STANDBY 0x11111111
static HI_S16 g_s16TempUp;
static HI_S16 g_s16TempDown;
static HI_S16 g_s16TempReboot;
static HI_U8 g_u8TempCtrlEnable;
static struct task_struct *pstTempCtrlThread = HI_NULL;
#endif
#endif

#ifdef HI_AVS_SUPPORT
extern HI_U8 g_u8CpuHpmOffset;
extern void         CPU_AVS_Enable(unsigned int enable);
extern unsigned int CPU_AVS_GetStatus(void);
#endif

extern HI_S32       PMEnterSmartStandby(HI_U32 u32HoldModules);
extern HI_S32       PMQuitSmartStandby(HI_VOID);
void                mpu_get_temperature(HI_S16 * ps16Temp);

#define MCU_START_REG 0xf840f000
#define HI_CHIP_NON_ADVCA 0x2a13c812
#define HI_CHIP_ADVCA 0x6edbe953
#define WAKE_FROM_DDR 0x66031013

#ifdef NOCS3_0_SUPPORT
#define KL_LPC_DISABLE 0xf8ab4108
#define REG_CA_ID_WORD 0xf8ab0060
#define REG_CA_VENDOR_ID 0xf8ab00f0
#else
#define KL_LPC_DISABLE 0xf8a90144
#define REG_CA_ID_WORD 0xf8ab0128
#define REG_CA_VENDOR_ID 0xf8ab012c
#endif

#ifdef CHIP_TYPE_hi3796mv200
#define DDR_WAKEUP_FLAG 0x66031013
#define MAIL_CMD_ACPU_TO_SMCU 0x65211f01
#define MAILBOX_BASE_ADDR 0xf9a39000
#define REG_MAILBOX_CMD 0x20
#define REG_MAILBOX_ARG_0 0x40
#define REG_MAILBOX_TOTEECPU_ADDRESS 0x310
#define REG_MAILBOX_ACPU_TO_SMCU 0x400
#define MAILBOX_STATUS_LOAD_OK 0x80510002
#define SMCU_RESET_ADDR 0xf8a80060
#define HKL_RESET_ADDR 0xf8ab4200
#endif

#ifdef HI_GPIO_LIGHT_SUPPORT
static GPIO_EXT_FUNC_S *s_pGpioFunc = HI_NULL;
#define GPIO_LIGHT HI_GPIO_LIGHT_SET
#endif

static HI_U32 wdgon = 0x0;
static HI_U32 dbgmask   = 0x1;
static HI_U32 keyVal    = 0;
static HI_U32 kltype    = 0;
static HI_U32 timeVal   = 0xffffffff;
static HI_U32 dispMode  = 2;
static HI_U32 irtype    = 0;
static HI_U32 irpmocnum = 1;
static HI_U32 dispvalue = 0x00093a00;
static HI_U8 g_u8UsbWakeUpMask = 0;
static HI_U8 g_u8EthWakeUpEnable = 0;
static HI_U8 g_u8FwEnable = 0;
static HI_U32 irValhigh[PMOC_WKUP_IRKEY_MAXNUM] = {
    0, 0, 0, 0, 0, 0
};
static HI_U32 irVallow[PMOC_WKUP_IRKEY_MAXNUM] = {
    0x639cff00, 0, 0, 0, 0, 0
};

static UMAP_DEVICE_S g_stPmDev;

static HI_U32 GpioValArray[2] = {
    0, 0
};

static HI_U32 g_u32GpioPortVal = 0;
static HI_U8 g_u8GpioIEV = 0; //0:Falling edge or low level; 1: Rising edge or high level
static HI_U8 g_u8GpioIBE = 0; //0:single edge; 1:double edge
static HI_U8 g_u8GpioIS = 0; //0:edge; 1: level
static HI_U32 g_u32LpcDisable;
static HI_BOOL g_bMouseKeyboardEnable = 0;
static HI_BOOL g_bGpioWakeUpEnable = 0;
static HI_BOOL g_bCECWakeUpEnable = 0;
static C51_PmocNet_S g_stNetwork;

#ifndef HI_ADVCA_FUNCTION_RELEASE
static HI_U32 lu32vC51Code[] = {
#include "output.txt"
};
#else
static HI_U32 lu32vC51Code[] = {
#include "output_ca_release.txt"
};
#endif

HI_CHIP_TYPE_E g_enChipType;
HI_CHIP_VERSION_E g_enChipID;
static struct semaphore c51Sem;
static HI_U8 *ltvVirAddr = NULL;
#define C51_GetVIRAddr(addr) (ltvVirAddr + ((addr) - C51_BASE))

static HI_BOOL get_Advca_Support(void)
{
#ifdef CHIP_TYPE_hi3796mv200
    return HI_FALSE;
#else
    HI_U32 AdvcaFlag;
    HI_U32 * pCaIdWord = HI_NULL_PTR;

    pCaIdWord = ioremap_nocache(REG_CA_ID_WORD, 0x4);
    if (HI_NULL == pCaIdWord)
    {
        HI_ERR_PM("ioremap_nocache CA ID WORD err! \n");
        return HI_FALSE;
    }

    HI_REG_READ(pCaIdWord, AdvcaFlag);

    iounmap(pCaIdWord);

    if (HI_CHIP_ADVCA == AdvcaFlag)
    {
        return HI_TRUE;
    }
    else if (HI_CHIP_NON_ADVCA == AdvcaFlag)
    {
        return HI_FALSE;
    }
    else
    {
        HI_ERR_PM("invalid advca flag\n");
        return HI_FALSE;
    }
#endif
}

static HI_S32 get_mcu_status(HI_BOOL * bStart)
{
    HI_U32 * pMcuStart = HI_NULL_PTR;

    pMcuStart = ioremap_nocache(MCU_START_REG, 0x4);
    if (HI_NULL == pMcuStart)
    {
        HI_ERR_PM("ioremap_nocache MCU START code err! \n");
        return HI_FAILURE;
    }

    HI_REG_READ32(pMcuStart, *bStart);

    iounmap(pMcuStart);

    return HI_SUCCESS;
}

static HI_S32 set_mcu_status(HI_BOOL bStart)
{
    HI_U32 * pMcuStart = HI_NULL_PTR;

    pMcuStart = ioremap_nocache(MCU_START_REG, 0x4);
    if (HI_NULL == pMcuStart)
    {
        HI_ERR_PM("ioremap_nocache MCU START code err! \n");
        return HI_FAILURE;
    }

    HI_REG_WRITE32(pMcuStart, bStart);

    iounmap(pMcuStart);

    return HI_SUCCESS;
}

#ifdef HI_TEE_MCU_SUPPORT

/* for 98mv200 only */
#define TEE_MCU_TA_NAME    "hisi_drv_mcu"
#define TEE_MCU_TA_UID     0
#define TEEK_CMD_MCU_LOAD 0
static HI_U32 mcu_load_code_tee(HI_VOID)
{
    TEEC_Result result;
    TEEC_Operation operation;
    TEEC_Operation session_operation;
    TEEC_UUID mcu_id = {0x5766695a, 0x9b44, 0x4f9b,
                        {0x80, 0xd6, 0x74, 0x1f, 0x88, 0x62, 0x4c, 0x41}
                       };

    HI_U32 u32MCUSecID = 0;

    result = TEEK_InitializeContext(NULL, &g_TeeContext);
    if (result != TEEC_SUCCESS)
    {
        HI_ERR_PM("mcu TEEK_InitializeContext Failed!\n");
        return HI_FAILURE;
    }

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    session_operation.params[2].tmpref.buffer = (HI_VOID *)(&u32MCUSecID);
    session_operation.params[2].tmpref.size   = sizeof(u32MCUSecID);
    session_operation.params[3].tmpref.buffer = (HI_VOID *)(TEE_MCU_TA_NAME);
    session_operation.params[3].tmpref.size   = strlen(TEE_MCU_TA_NAME) + 1;

    result = TEEK_OpenSession(&g_TeeContext, &g_TeeSession, &mcu_id, TEEC_LOGIN_IDENTIFY, NULL, &session_operation, NULL);
    if (result != TEEC_SUCCESS)
    {
        HI_ERR_PM("mcu TEEK_OpenSession Failed!\n");
        return HI_FAILURE;
    }

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].tmpref.buffer = lu32vC51Code;
    operation.params[0].tmpref.size = sizeof(lu32vC51Code);

    result = TEEK_InvokeCommand(&g_TeeSession, TEEK_CMD_MCU_LOAD, &operation, NULL);
    if (result != TEEC_SUCCESS)
    {
        HI_ERR_PM("mcu TEEK_InvokeCommand Failed!\n");
        return HI_FAILURE;
    }

    TEEK_CloseSession(&g_TeeSession);
    TEEK_FinalizeContext(&g_TeeContext);

    return HI_SUCCESS;
}
#endif

#ifdef CHIP_TYPE_hi3796mv200
#ifndef HI_TEE_SUPPORT
static HI_BOOL bSMCULoadOK = HI_FALSE;
static HI_VOID smcu_start(HI_VOID)
{
    HI_U8 * pSmcuReset = HI_NULL_PTR;
    HI_U8 * pHKLReset = HI_NULL_PTR;
    HI_U32 u32Val = 0;

    pHKLReset = ioremap_nocache(HKL_RESET_ADDR, 0x4);
    if (HI_NULL == pHKLReset)
    {
        HI_ERR_PM("ioremap_nocache HKL start err! \n");
        return;
    }

    HI_REG_READ32(pHKLReset, u32Val);
    u32Val &= 0xfffffff7; //bit3 to 0: release hkl reset;
    HI_REG_WRITE32(pHKLReset, u32Val);

    iounmap(pHKLReset);

    pSmcuReset = ioremap_nocache(SMCU_RESET_ADDR, 0x4);
    if (HI_NULL == pSmcuReset)
    {
        HI_ERR_PM("ioremap_nocache SMCU START err! \n");
        return;
    }

    HI_REG_READ32(pSmcuReset, u32Val);
    u32Val &= 0xffff76ff; //bit8 to 0: release smcu reset; bit15 to 0: release hrsa reset; bit 11 to 0: release sha3 reset
    u32Val |= 0x14000; //bit 16 to 1: hrsa clock on;bit 14 t0 1: sha3 clock on
    HI_REG_WRITE32(pSmcuReset, u32Val);

    iounmap(pSmcuReset);

    bSMCULoadOK = HI_FALSE;

    return;
}

#ifdef HI_TEMP_CTRL_CONFIG
static HI_VOID smcu_close_clk(HI_VOID)
{
    HI_U8 * pMailbox = HI_NULL_PTR;
    HI_U8 * pSmcuReset = HI_NULL_PTR;
    HI_U8 * pHKLReset = HI_NULL_PTR;
    HI_U32 u32Val = 0;

    pMailbox = ioremap_nocache(MAILBOX_BASE_ADDR, 0x1000);
    if (HI_NULL == pMailbox)
    {
        HI_ERR_PM("ioremap_nocache mailbox err! \n");
        return;
    }

    HI_REG_READ32(pMailbox + REG_MAILBOX_TOTEECPU_ADDRESS, u32Val);
    if (u32Val == MAILBOX_STATUS_LOAD_OK)
    {
        pSmcuReset = ioremap_nocache(SMCU_RESET_ADDR, 0x4);
        if (HI_NULL == pSmcuReset)
        {
            iounmap(pMailbox);
            HI_ERR_PM("ioremap_nocache SMCU START err! \n");
            return;
        }

        HI_REG_READ32(pSmcuReset, u32Val);
        u32Val &= 0xfffeffff; //bit16 to 0: hrsa clk off
        u32Val |= 0x8000; //bit15 to 1: hrsa reset
        HI_REG_WRITE32(pSmcuReset, u32Val);

        iounmap(pSmcuReset);

        pHKLReset = ioremap_nocache(HKL_RESET_ADDR, 0x4);
        if (HI_NULL == pHKLReset)
        {
            HI_ERR_PM("ioremap_nocache HKL start err! \n");
            return;
        }

        HI_REG_READ32(pHKLReset, u32Val);
        u32Val |= 0x08; //bit3 to 1: hkl reset;
        HI_REG_WRITE32(pHKLReset, u32Val);

        iounmap(pHKLReset);

        bSMCULoadOK = HI_TRUE;
    }

    iounmap(pMailbox);

    return;
}
#endif
#endif
#endif

#ifdef NOCS3_0_SUPPORT
#define DDRPHY_BASE_ADDR (0xF8A38000)
#define DATA_BASE_ADDR (0xF8407000)
#define DATA_PHY_BASE_ADDR (DATA_BASE_ADDR + 0x100)
#define DDRPHY_ARRAY_COUNT 4

static HI_VOID DDRPHYRegSave_MV410(HI_VOID)
{
    HI_U32 u32DDRPHY0BaseAddr = 0;
    HI_U32 u32RegCount;
    HI_U8 i, j;
    HI_U32 u32RegVal;

    HI_U32 * pMcuData = HI_NULL_PTR;
    HI_U32 * pTmpAddr = HI_NULL_PTR;
    HI_U32 * pDDRPhyBaseAddr = HI_NULL_PTR;

    pMcuData = ioremap_nocache(DATA_PHY_BASE_ADDR, 0x400);
    if (HI_NULL == pMcuData)
    {
        HI_ERR_PM("ioremap_nocache c51 data  err! \n");
        return;
    }

    pDDRPhyBaseAddr = ioremap_nocache(DDRPHY_BASE_ADDR, 0x500);
    if (HI_NULL == pDDRPhyBaseAddr)
    {
        HI_ERR_PM("ioremap_nocache pDDRPhyBaseAddr  err! \n");
        return;
    }

    u32RegCount = 20;
    u32DDRPHY0BaseAddr = DDRPHY_BASE_ADDR;


    for (i = 0; i < DDRPHY_ARRAY_COUNT; i++)
    {
        HI_REG_WRITE32(pMcuData + i * (u32RegCount + 2), u32RegCount);

        HI_REG_WRITE32(pMcuData + i * (u32RegCount + 2) + 1, u32DDRPHY0BaseAddr + 0x210 + i * 0x80);

        for (j = 0; j < u32RegCount; j++)
        {
            HI_REG_READ32(pDDRPhyBaseAddr + 0x84 + i * 0x20 + j, u32RegVal);
            HI_REG_WRITE32(pMcuData + i * (u32RegCount + 2) + 0x2 + j, u32RegVal);
        }
    }

    pTmpAddr = pMcuData + DDRPHY_ARRAY_COUNT * (u32RegCount + 2);

    /* set (u32DDRBaseAddr + 0x70) bit 20(19 in 98cv200) to 1 */
    HI_REG_WRITE32(pTmpAddr, 1);
    HI_REG_WRITE32(pTmpAddr + 1, DDRPHY_BASE_ADDR + 0x70);

    HI_REG_READ32(pDDRPhyBaseAddr + 0x1c, u32RegVal);
    u32RegVal |= 0x00100000;
    HI_REG_WRITE32(pTmpAddr + 2, u32RegVal);

    /* set (u32DDRBaseAddr + 0x70) bit 20(19 in 98cv200) to 0 */
    HI_REG_WRITE32(pTmpAddr + 3, 1);
    HI_REG_WRITE32(pTmpAddr + 4, DDRPHY_BASE_ADDR + 0x70);

    HI_REG_READ32(pDDRPhyBaseAddr + 0x1c, u32RegVal);
    u32RegVal &= 0xffefffff;
    HI_REG_WRITE32(pTmpAddr + 5, u32RegVal);

    /* set (u32DDRBaseAddr + 0x04) bit 15 to 1 */
    HI_REG_WRITE32(pTmpAddr + 6, 1);
    HI_REG_WRITE32(pTmpAddr + 7, DDRPHY_BASE_ADDR + 0x04);
    HI_REG_WRITE32(pTmpAddr + 8, 0x8000);

    /* set (u32DDRBaseAddr + 0x04) bit 15 to 0 */
    HI_REG_WRITE32(pTmpAddr + 9, 1);
    HI_REG_WRITE32(pTmpAddr + 10, DDRPHY_BASE_ADDR + 0x04);
    HI_REG_WRITE32(pTmpAddr + 11, 0x0);

    /*  set the last value to 0, so bootrom will recognize the end */
    HI_REG_WRITE32(pTmpAddr + 12, 0);

    iounmap(pDDRPhyBaseAddr);
    iounmap(pMcuData);

    /* save the address of c51 ram to SC_GEN16 for bootrom restoring ddr phy reg */
    g_pstRegSysCtrl->SC_GEN16 = DATA_PHY_BASE_ADDR;

    return;
}

HI_U32 ddr_wakeup_check_code[] =
{
    #include "ddr_wakeup_check.txt"
};

extern HI_S32 (* ca_pm_suspend)(HI_VOID *sramAddr, HI_S32 length);

HI_S32 locate_ca_pm_suspend(HI_VOID *sramAddr, HI_S32 length)
{
    if (NULL == sramAddr)
    {
        HI_ERR_PM("Invalid Input param of ca suspend\n");
        return -1;
    }

    if (length <= sizeof (ddr_wakeup_check_code))
    {
        return -1;
    }

    memcpy(sramAddr, ddr_wakeup_check_code, sizeof (ddr_wakeup_check_code));

    return 0;
}
#endif

static HI_S32 set_mcu_lock(HI_U32 u32Status)
{
    HI_U32 * pCaLpcDisable = HI_NULL_PTR;

    pCaLpcDisable = ioremap_nocache(KL_LPC_DISABLE, 0x4);
    if (HI_NULL == pCaLpcDisable)
    {
        HI_ERR_PM("ioremap_nocache CA Lpc Disable ID  err! \n");
        return HI_FAILURE;
    }

    HI_REG_WRITE32(pCaLpcDisable, u32Status); //Lock C51 RAM & Reset

    iounmap(pCaLpcDisable);

    return HI_SUCCESS;
}

static HI_S32  c51_loadCode(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 size = 0;
    HI_U32 *dwPtr = NULL;
    HI_BOOL bAdvca = HI_FALSE;
    HI_BOOL bStatus = HI_FALSE;

    /* Use GEN12 to store the chip type in CA and NOCA */

    bAdvca = get_Advca_Support();

#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3796mv200)
    g_pstRegSysCtrl->SC_GENm[12] = (g_enChipType | (g_enChipID << 16) | (bAdvca << 8));
#else
    g_pstRegSysCtrl->SC_GEN12 = (g_enChipType | (g_enChipID << 16) | (bAdvca << 8));
#endif

    ltvVirAddr = (HI_U8 *)ioremap_nocache(C51_BASE, C51_SIZE);
    if (ltvVirAddr == NULL)
    {
        HI_ERR_PM("ioremap_nocache c51 code err! \n");
        return HI_FAILURE;
    }

    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE);
    HI_INFO_PM("\n dwPtr BASE = %p\n", dwPtr);

    size = sizeof(lu32vC51Code);
    HI_INFO_PM("\n c51_loadCodetoRam  size = %d \n", size);

    get_mcu_status(&bStatus);

    if (HI_FALSE == bStatus)
    {
        for (i = 0; i < (size >> 2); i++)
        {
            HI_REG_WRITE32((dwPtr + i), lu32vC51Code[i]);
        }
    }

    iounmap(ltvVirAddr);

    return HI_SUCCESS;
}

static HI_S32  c51_loadPara(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 *dwPtr = NULL;
    HI_U32 u32CaVendor = 0;
    HI_U32 * pCaVendorId = HI_NULL_PTR;
    HI_BOOL bAdvca = HI_FALSE;

    HI_INFO_PM("\n HI_DRV_SYS_GetChipVersion   enChipType = %d, enChipID = 0x%x \n", g_enChipType, g_enChipID);

    bAdvca = get_Advca_Support();
    if (g_u8UsbWakeUpMask != 0)
    {
#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)
        U_PERI_USB_SUSPEND_INT_MASK unTmpValueUSBMask;
        unTmpValueUSBMask.u32 = g_pstRegPeri->PERI_USB_SUSPEND_INT_MASK.u32;
#else
        U_PERI_USB_RESUME_INT_MASK unTmpValueUSBMask;
        unTmpValueUSBMask.u32 = g_pstRegPeri->PERI_USB_RESUME_INT_MASK.u32;
#endif

#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3798mv200_a)
        if (g_u8UsbWakeUpMask & 0x01)
        {
            unTmpValueUSBMask.bits.usb_suspend0_int_mask = 1;
        }

        if (g_u8UsbWakeUpMask & 0x02)
        {
            unTmpValueUSBMask.bits.usb_suspend1_int_mask = 1;
        }

        if (g_u8UsbWakeUpMask & 0x04)
        {
            unTmpValueUSBMask.bits.usb_suspend2_int_mask = 1;
        }
#else
        if (g_u8UsbWakeUpMask & 0x01)
        {
            unTmpValueUSBMask.bits.usb_phy0_suspend_int_mask = 1;
        }

 #if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
        if (g_u8UsbWakeUpMask & 0x02)
        {
            unTmpValueUSBMask.bits.usb3_utmi_suspend_n = 1;
        }
 #endif

 #if !(defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420))
        if (g_u8UsbWakeUpMask & 0x04)
        {
            unTmpValueUSBMask.bits.usb_phy2_suspend_int_mask = 1;
        }
 #endif

        if (g_u8UsbWakeUpMask & 0x08)
        {
            unTmpValueUSBMask.bits.usb_phy1_suspend_int_mask = 1;
        }
#endif

        g_pstRegPeri->PERI_USB_RESUME_INT_MASK.u32 = unTmpValueUSBMask.u32;

        HI_INFO_PM("\n set  g_u8UsbWakeUpMask to PERI_USB_RESUME_INT_MASK = %d 0x%x \n",
                   g_u8UsbWakeUpMask, unTmpValueUSBMask.u32);
    }

    ltvVirAddr = (HI_U8 *)ioremap_nocache(C51_BASE, C51_SIZE);
    if (ltvVirAddr == NULL)
    {
        HI_ERR_PM("ioremap_nocache c51 para err! \n");
        return HI_FAILURE;
    }

    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE + C51_DATA);

    if (g_u8FwEnable || g_u8EthWakeUpEnable)
    {
        HI_REG_WRITE32((dwPtr + 0), (g_enChipType | (2 << 8)) | (g_enChipID << 16));
    }
    else if (g_u8UsbWakeUpMask)
    {
        HI_REG_WRITE32((dwPtr + 0), (g_enChipType | (1 << 8)) | (g_enChipID << 16));
    }
    else
    {
        HI_REG_WRITE32((dwPtr + 0), (g_enChipType | (g_enChipID << 16)));
    }

    /* Use GEN12 to store the chip type in CA and NOCA */
#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3796mv200)
    g_pstRegSysCtrl->SC_GENm[12] = (g_enChipType | (g_enChipID << 16) | (bAdvca << 8));
#else
    g_pstRegSysCtrl->SC_GEN12 = (g_enChipType | (g_enChipID << 16) | (bAdvca << 8));
#endif

    HI_REG_WRITE32((dwPtr + 1), wdgon);
    HI_REG_WRITE32((dwPtr + 2), (dbgmask | (g_bCECWakeUpEnable << 8)));
    HI_REG_WRITE32((dwPtr + 3), GpioValArray[0]);  /*record gpio index, between 40 and 47 */
    HI_REG_WRITE32((dwPtr + 4), (GpioValArray[1] | (g_u8GpioIEV << 8) | (g_u8GpioIBE << 16) | (g_u8GpioIS << 24)));  /*record gpio output, 1 or 0 */

    HI_REG_WRITE32((dwPtr + 5), dispMode);
    HI_REG_WRITE32((dwPtr + 6), dispvalue);
    HI_REG_WRITE32((dwPtr + 7), timeVal);

    HI_REG_WRITE32((dwPtr + 8), kltype);
    HI_REG_WRITE32((dwPtr + 9), keyVal);

    /* save ca vendor */
    if (get_Advca_Support())
    {
        pCaVendorId = ioremap_nocache(REG_CA_VENDOR_ID, 0x4);
        if (HI_NULL == pCaVendorId)
        {
            HI_ERR_PM("ioremap_nocache CA VENDOR ID  err! \n");
            return HI_FAILURE;

        }

        HI_REG_READ32(pCaVendorId, u32CaVendor);
        u32CaVendor &= 0xff;
        HI_REG_WRITE32((dwPtr + 10), u32CaVendor);
    }

    HI_REG_WRITE32((dwPtr + 11), g_u32GpioPortVal);

    HI_REG_WRITE32((dwPtr + 12), irtype);
    HI_REG_WRITE32((dwPtr + 13), irpmocnum);

    for (i = 0; i < irpmocnum; i++)
    {
        HI_REG_WRITE32((dwPtr + 14 + 2 * i), irVallow[i]);
        HI_REG_WRITE32((dwPtr + 15 + 2 * i), irValhigh[i]);
    }

    iounmap(ltvVirAddr);

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if (g_u8FwEnable || g_u8EthWakeUpEnable)
    {
        g_pstRegSysCtrl->SC_GEN32 = ((g_enChipType | (2 << 8)) | (g_enChipID << 16));
    }
    else if (g_u8UsbWakeUpMask)
    {
        g_pstRegSysCtrl->SC_GEN32 = ((g_enChipType | (1 << 8)) | (g_enChipID << 16));
    }
    else
    {
        g_pstRegSysCtrl->SC_GEN32 = (g_enChipType | (g_enChipID << 16));
    }

    g_pstRegSysCtrl->SC_GEN33 = wdgon;
    g_pstRegSysCtrl->SC_GEN34 = dbgmask;
    g_pstRegSysCtrl->SC_GEN35 = GpioValArray[0];
    g_pstRegSysCtrl->SC_GEN36 = GpioValArray[1] | (g_u8GpioIEV << 8) | (g_u8GpioIBE << 16) | (g_u8GpioIS << 24);
    g_pstRegSysCtrl->SC_GEN37 = dispMode;
    g_pstRegSysCtrl->SC_GEN38 = dispvalue;
    g_pstRegSysCtrl->SC_GEN39 = timeVal;
    g_pstRegSysCtrl->SC_GEN40 = kltype;
    g_pstRegSysCtrl->SC_GEN41 = keyVal;

    /* save ca vendor */
    if (get_Advca_Support())
    {
        HI_REG_READ32(pCaVendorId, u32CaVendor);
        u32CaVendor &= 0xff;
        g_pstRegSysCtrl->SC_GEN42 = u32CaVendor;
    }

    g_pstRegSysCtrl->SC_GEN43 = g_u32GpioPortVal;

    g_pstRegSysCtrl->SC_GEN44 = irtype;
    g_pstRegSysCtrl->SC_GEN45 = irpmocnum;

    g_pstRegSysCtrl->SC_GEN46 = irVallow[0];
    g_pstRegSysCtrl->SC_GEN47 = irValhigh[0];
    g_pstRegSysCtrl->SC_GEN48 = irVallow[1];
    g_pstRegSysCtrl->SC_GEN49 = irValhigh[1];
    g_pstRegSysCtrl->SC_GEN50 = irVallow[2];
    g_pstRegSysCtrl->SC_GEN51 = irValhigh[2];
    g_pstRegSysCtrl->SC_GEN52 = irVallow[3];
    g_pstRegSysCtrl->SC_GEN53 = irValhigh[3];
    g_pstRegSysCtrl->SC_GEN54 = irVallow[4];
    g_pstRegSysCtrl->SC_GEN55 = irValhigh[4];
    g_pstRegSysCtrl->SC_GEN56 = irVallow[5];
    g_pstRegSysCtrl->SC_GEN57 = irValhigh[5];
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
  #ifdef HI_TEE_SUPPORT
    if (g_u8FwEnable || g_u8EthWakeUpEnable)
    {
        g_pstRegSysCtrl->SC_GENy[0] = ((g_enChipType | (2 << 8)) | (g_enChipID << 16));
    }
    else if (g_u8UsbWakeUpMask)
    {
        g_pstRegSysCtrl->SC_GENy[0] = ((g_enChipType | (1 << 8)) | (g_enChipID << 16));
    }
    else
    {
        g_pstRegSysCtrl->SC_GENy[0] = (g_enChipType | (g_enChipID << 16));
    }

    g_pstRegSysCtrl->SC_GENy[1] = wdgon;
    g_pstRegSysCtrl->SC_GENy[2] = dbgmask;
    g_pstRegSysCtrl->SC_GENy[3] = GpioValArray[0];
    g_pstRegSysCtrl->SC_GENy[4] = GpioValArray[1] | (g_u8GpioIEV << 8) | (g_u8GpioIBE << 16) | (g_u8GpioIS << 24);
    g_pstRegSysCtrl->SC_GENy[5] = dispMode;
    g_pstRegSysCtrl->SC_GENy[6] = dispvalue;
    g_pstRegSysCtrl->SC_GENy[7] = timeVal;
    g_pstRegSysCtrl->SC_GENy[8] = kltype;
    g_pstRegSysCtrl->SC_GENy[9] = keyVal;

    /* save ca vendor */
    if (get_Advca_Support())
    {
        HI_REG_READ32(pCaVendorId, u32CaVendor);
        u32CaVendor &= 0xff;
        g_pstRegSysCtrl->SC_GENy[10] = u32CaVendor;
    }

    g_pstRegSysCtrl->SC_GENy[11] = g_u32GpioPortVal;

    g_pstRegSysCtrl->SC_GENy[12] = irtype;
    g_pstRegSysCtrl->SC_GENy[13] = irpmocnum;

    g_pstRegSysCtrl->SC_GENy[14] = irVallow[0];
    g_pstRegSysCtrl->SC_GENy[15] = irValhigh[0];
    g_pstRegSysCtrl->SC_GENy[16] = irVallow[1];
    g_pstRegSysCtrl->SC_GENy[17] = irValhigh[1];
    g_pstRegSysCtrl->SC_GENy[18] = irVallow[2];
    g_pstRegSysCtrl->SC_GENy[19] = irValhigh[2];
    g_pstRegSysCtrl->SC_GENy[20] = irVallow[3];
    g_pstRegSysCtrl->SC_GENy[21] = irValhigh[3];
    g_pstRegSysCtrl->SC_GENy[22] = irVallow[4];
    g_pstRegSysCtrl->SC_GENy[23] = irValhigh[4];
    g_pstRegSysCtrl->SC_GENy[24] = irVallow[5];
    g_pstRegSysCtrl->SC_GENy[25] = irValhigh[5];
  #endif
#endif

    iounmap(pCaVendorId);

    return HI_SUCCESS;
}

#ifdef HI_GPIO_LIGHT_SUPPORT
static HI_VOID SetGpioLightSuspend(HI_BOOL bSuspend)
{
    HI_CHIP_PACKAGE_TYPE_E enPackageType = HI_CHIP_PACKAGE_TYPE_BUTT;

    HI_DRV_SYS_GetChipPackageType(&enPackageType);

    if ((HI_CHIP_TYPE_HI3798M == g_enChipType) && (HI_CHIP_PACKAGE_TYPE_QFP_216 == enPackageType))
    {
        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, !bSuspend);
        }
    }
    else
    {
        if (0xff != HI_NEGATIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, bSuspend);
        }

        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, !bSuspend);
        }
    }

    return;
}
#endif

#define MAX_CHECK_COUNT 1000
static HI_U32 g_corner_type = 0;
static HI_S32 c51_suspend (PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_S32 ret = 0;
    HI_U32 * pCaLpcDisable = HI_NULL_PTR;

#ifdef CHIP_TYPE_hi3796mv200
    HI_U8 * pMailbox = HI_NULL_PTR;
    HI_U32 u32Val = 0;
#ifndef HI_TEE_SUPPORT
    HI_U32 u32Count = 0;
#endif
#endif

#ifdef HI_GPIO_LIGHT_SUPPORT
    SetGpioLightSuspend(HI_TRUE);
#endif

#ifdef NOCS3_0_SUPPORT
    ca_pm_suspend = locate_ca_pm_suspend;
#endif

#ifdef CHIP_TYPE_hi3796mv200
    pMailbox = ioremap_nocache(MAILBOX_BASE_ADDR, 0x1000);
    if (HI_NULL == pMailbox)
    {
        HI_ERR_PM("ioremap_nocache mailbox err! \n");
        return HI_FAILURE;
    }

#ifndef HI_TEE_SUPPORT
    while (u32Count++ < MAX_CHECK_COUNT)
    {
        HI_REG_READ32(pMailbox + REG_MAILBOX_TOTEECPU_ADDRESS, u32Val);
        if (u32Val == MAILBOX_STATUS_LOAD_OK)
        {
            break;
        }
        msleep(1);
    }

    if (u32Count >= MAX_CHECK_COUNT)
    {
        HI_ERR_PM("smcu status err! \n");
        iounmap(pMailbox);
        return HI_FAILURE;
    }
#endif

    /* send flags to smcu through mailbox */
    if (!wdgon)
    {
        u32Val = DDR_WAKEUP_FLAG;
    }

    HI_REG_WRITE32(pMailbox + REG_MAILBOX_ARG_0, u32Val);
    HI_REG_WRITE32(pMailbox + REG_MAILBOX_CMD, MAIL_CMD_ACPU_TO_SMCU);
    HI_REG_WRITE32(pMailbox + REG_MAILBOX_ACPU_TO_SMCU, 0x1);

    iounmap(pMailbox);

#endif

    ret = c51_loadPara();
    if (ret)
    {
        HI_ERR_PM("c51_loadPara err! \n");
        return HI_FAILURE;
    }

    HI_INFO_PM("c51_loadPara ok! \n");

    if (get_Advca_Support())
    {
        pCaLpcDisable = ioremap_nocache(KL_LPC_DISABLE, 0x4);
        if (HI_NULL == pCaLpcDisable)
        {
            HI_ERR_PM("ioremap_nocache CA Lpc Disable ID  err! \n");
            return HI_FAILURE;
        }

        HI_REG_READ(pCaLpcDisable, g_u32LpcDisable);

        iounmap(pCaLpcDisable);
    }

#ifdef HI_DVFS_CPU_SUPPORT
 #ifdef HI_TEMP_CTRL_CONFIG
    g_u8TempCtrlEnable = HI_FALSE;
 #endif
    if (HI_TRUE == cpu_dvfs_enable)
    {
        cpu_dvfs_enable = HI_FALSE;

 #ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
 #endif
    }
#endif

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
#ifdef HI_TEE_MCU_SUPPORT
    if (!wdgon)
    {
        g_pstRegSysCtrl->SC_GENm[13] = WAKE_FROM_DDR;
    }
    else
    {
        g_pstRegSysCtrl->SC_GENm[13] = 0;
    }
#endif
#endif

    /* save the chip corner type */
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    g_corner_type = (g_pstRegSysCtrl->SC_GENm[17] >> 24) & 0xff;
#else
    g_corner_type = (g_pstRegSysCtrl->SC_GEN17 >> 24) & 0xff;
#endif

    HI_PRINT("PM suspend OK\n");
    return HI_SUCCESS;
}

static HI_S32 c51_resume_early(PM_BASEDEV_S *pdev)
{
    /* restore the chip corner type */
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    g_pstRegSysCtrl->SC_GENm[17] = ((g_pstRegSysCtrl->SC_GENm[17] & 0xffffff) | (g_corner_type << 24));
#else
    g_pstRegSysCtrl->SC_GEN17 = ((g_pstRegSysCtrl->SC_GEN17 & 0xffffff) | (g_corner_type << 24));
#endif

    return 0;
}

extern void mpu_resume_clocks(void);
static HI_S32 c51_resume(PM_BASEDEV_S *pdev)
{
#ifdef HI_DVFS_CPU_SUPPORT
    HI_U32 v;
 #if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    U_PERI_CRG18 unTmpValue;
 #endif
#endif

#ifdef CHIP_TYPE_hi3796mv200
#ifndef HI_TEE_SUPPORT
    smcu_start();
#endif
#endif

#ifdef HI_GPIO_LIGHT_SUPPORT
    SetGpioLightSuspend(HI_FALSE);
#endif

#ifdef HI_DVFS_CPU_SUPPORT
 #if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    unTmpValue.u32 = g_pstRegCrg->PERI_CRG18.u32;

    /* config the clock source is APLL */
    if (unTmpValue.bits.cpu_freq_sel_cfg_crg != 0)
    {
        unTmpValue.bits.cpu_sw_begin_cfg = 0;
        g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

        unTmpValue.bits.cpu_freq_sel_cfg_crg = 0;
        g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

        unTmpValue.bits.cpu_sw_begin_cfg = 1;
        g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;
    }
 #endif

    v = mpu_get_volt();
    if (v > cur_cpu_volt)
    {
        mpu_resume_clocks();
        mdelay(15);
        cpu_volt_scale(cur_cpu_volt);
    }
    else
    {
        cpu_volt_scale(cur_cpu_volt);
        mdelay(15);
        mpu_resume_clocks();
    }

    cpu_dvfs_enable = HI_TRUE;

#ifdef HI_TEMP_CTRL_CONFIG
    g_u8TempCtrlEnable = HI_TRUE;
#endif

 #ifdef HI_AVS_SUPPORT
    core_volt_scale(cur_core_volt);
 #endif
#endif

    if (get_Advca_Support())
    {
        set_mcu_status(0x1); ////start MCU
        if (g_u32LpcDisable & 0x3)
        {
            set_mcu_lock(g_u32LpcDisable);
        }
    }
    else
    {
#ifdef HI_PM_START_MCU_RUNNING
        set_mcu_status(0x1);
#endif
    }

#if defined(CHIP_TYPE_hi3798cv200)
    g_pstRegSysCtrl->SC_GENm[0] = 0;
#endif

    HI_PRINT("PM resume OK\n");

    return HI_SUCCESS;
}

static PM_BASEOPS_S c51_baseOps = {
    .probe  = NULL,
    .remove = NULL,
    .shutdown = NULL,
    .prepare  = NULL,
    .complete = NULL,
    .suspend  = c51_suspend,
    .suspend_late = NULL,
    .resume_early = c51_resume_early,
    .resume       = c51_resume
};

static HI_VOID C51_SetScene(HI_UNF_PMOC_SCENE_E sence)
{
    if (sence == HI_UNF_PMOC_SCENE_ETH)
    {
        g_u8FwEnable = 1;
    }
    else
    {
        g_u8FwEnable = 0;
    }

    return;
}

static HI_S32 c51_SetWakeUpParam(C51_PMOC_VAL_S pmocVal)
{
    HI_U32 i;

    if (pmocVal.irnum > PMOC_WKUP_IRKEY_MAXNUM)
    {
        HI_WARN_PM("Out of the max ir number !\n");
        return HI_ERR_PM_INVALID_PARAM;
    }

    if ((irtype != 4) && (pmocVal.irnum > 1))
    {
        HI_WARN_PM("only ir raw type support several power keys, others support only one power key !\n");
        return HI_ERR_PM_INVALID_PARAM;
    }

    irpmocnum = pmocVal.irnum;

    for (i = 0; i < irpmocnum; i++)
    {
        irVallow[i]  = pmocVal.irlVal[i];
        irValhigh[i] = pmocVal.irhVal[i];
    }

#ifdef HI_KEYLED_SUPPORT
    keyVal = pmocVal.keyVal;
#else
    keyVal = 0xffffffff;
#endif
    timeVal = pmocVal.timeVal;

    g_u8UsbWakeUpMask = pmocVal.usbWakeupMask;
    g_u8EthWakeUpEnable = pmocVal.ethWakeupFlag;

    /* use this param 'wdgon' to control resume reset in C51*/
    wdgon = pmocVal.resumeResetFlag;

    g_bMouseKeyboardEnable = pmocVal.mouseKeyboardEnable;
    g_bGpioWakeUpEnable = pmocVal.gpioWakeUpEnable;

    g_u32GpioPortVal = pmocVal.gpioPort;

    g_bCECWakeUpEnable = pmocVal.cecWakeUpEnable;

    memcpy(&g_stNetwork, &pmocVal.stNetwork, sizeof(C51_PmocNet_S));

    /* add for quick standby */
    c51_loadPara();

    return HI_SUCCESS;
}

static HI_VOID c51_GetWakeUpParam(C51_PMOC_VAL_S *pmocVal)
{
    HI_U32 i;

    if (irpmocnum > PMOC_WKUP_IRKEY_MAXNUM)
    {
        irpmocnum = PMOC_WKUP_IRKEY_MAXNUM;
    }

    pmocVal->irnum = irpmocnum;

    for (i = 0; i < irpmocnum; i++)
    {
        pmocVal->irlVal[i] = irVallow[i];
        pmocVal->irhVal[i] = irValhigh[i];
    }

#ifdef HI_KEYLED_SUPPORT
    pmocVal->keyVal = keyVal;
#else
    pmocVal->keyVal = 0xffffffff;
#endif
    pmocVal->timeVal = timeVal;
    pmocVal->usbWakeupMask = g_u8UsbWakeUpMask;
    pmocVal->ethWakeupFlag = g_u8EthWakeUpEnable;

    /* use this param 'wdgon' to control resume reset in C51*/
    pmocVal->resumeResetFlag = wdgon;

    pmocVal->mouseKeyboardEnable = g_bMouseKeyboardEnable;
    pmocVal->gpioWakeUpEnable = g_bGpioWakeUpEnable;

    pmocVal->gpioPort = g_u32GpioPortVal;

    pmocVal->cecWakeUpEnable = g_bCECWakeUpEnable;

    memcpy(&pmocVal->stNetwork, &g_stNetwork, sizeof(C51_PmocNet_S));

    return;
}

static HI_S32 c51_GetStandbyPeriod(HI_U32 *pu32StandbyPeriod)
{
#if (defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)) && defined(HI_TEE_SUPPORT)
    if (g_pstRegSysCtrl->SC_GENy[29] < C51_PMOC_WAKEUP_BUTT)
    {
        *pu32StandbyPeriod = g_pstRegSysCtrl->SC_GENy[30];
    }
#else
    HI_U32 * pWakeup = HI_NULL_PTR;
    HI_U32 u32RegVal;

    pWakeup = ioremap_nocache(C51_BASE + C51_DATA + 0xff8, 0x8);
    if (HI_NULL == pWakeup)
    {
        HI_ERR_PM("ioremap_nocache c51 wake up period err! \n");
        return HI_FAILURE;
    }

    HI_REG_READ32(pWakeup, u32RegVal);
    if (u32RegVal < C51_PMOC_WAKEUP_BUTT)
    {
        HI_REG_READ32(pWakeup + 1, u32RegVal);
        *pu32StandbyPeriod = u32RegVal;
    }

    iounmap(pWakeup);
#endif

    return HI_SUCCESS;
}

static HI_S32 c51_GetWakeUpMode(C51_WAKEUP_MODE_S * psWakeUpMode)
{
#if (defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300 || defined(CHIP_TYPE_hi3798mv310))) && defined(HI_TEE_SUPPORT)
    psWakeUpMode->enWakeUpMode = g_pstRegSysCtrl->SC_GENy[29];
    if (C51_PMOC_WAKEUP_IR == psWakeUpMode->enWakeUpMode)
    {
        /* get power key */
        psWakeUpMode->u64IRPowerKey = g_pstRegSysCtrl->SC_GENy[28];
        psWakeUpMode->u64IRPowerKey = (g_pstRegSysCtrl->SC_GENy[27] | (psWakeUpMode->u64IRPowerKey << 32));
    }
    else if (psWakeUpMode->enWakeUpMode < C51_PMOC_WAKEUP_BUTT)
    {
        psWakeUpMode->u64IRPowerKey = 0;
    }
    else
    {
        HI_ERR_PM(" wakeup mode err! \n");
        return HI_FAILURE;
    }
#else
    HI_U32 * pWakeup = HI_NULL_PTR;
    HI_U32 u32IRPowerKeyHigh, u32IRPowerKeyLow;
    HI_U32 u32RegVal;

    pWakeup = ioremap_nocache(C51_BASE + C51_DATA + 0xff0, 0x10);
    if (HI_NULL == pWakeup)
    {
        HI_ERR_PM("ioremap_nocache c51 wake up key err! \n");
        return HI_FAILURE;
    }

    HI_REG_READ32(pWakeup + 2, u32RegVal);
    psWakeUpMode->enWakeUpMode = u32RegVal;

    if (C51_PMOC_WAKEUP_IR == psWakeUpMode->enWakeUpMode)
    {
        HI_REG_READ32(pWakeup, u32IRPowerKeyLow);
        HI_REG_READ32(pWakeup + 1, u32IRPowerKeyHigh);

        /* get power key */
        psWakeUpMode->u64IRPowerKey = u32IRPowerKeyHigh;
        psWakeUpMode->u64IRPowerKey = (u32IRPowerKeyLow | (psWakeUpMode->u64IRPowerKey << 32));
    }
    else if (psWakeUpMode->enWakeUpMode < C51_PMOC_WAKEUP_BUTT)
    {
        psWakeUpMode->u64IRPowerKey = 0;
    }
    else
    {
        HI_ERR_PM(" wakeup mode err! \n");
        return HI_FAILURE;
    }

    iounmap(pWakeup);
#endif

    return HI_SUCCESS;
}

static HI_S32 c51_CleanWakeUpMode(HI_VOID)
{
#if (defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)) && defined(HI_TEE_SUPPORT)
    g_pstRegSysCtrl->SC_GENy[27] = 0xffffffff;
    g_pstRegSysCtrl->SC_GENy[28] = 0xffffffff;
    g_pstRegSysCtrl->SC_GENy[29] = 0xffffffff;
#else
    HI_U32 * pWakeup = HI_NULL_PTR;

    pWakeup = ioremap_nocache(C51_BASE + C51_DATA + 0xff0, 0x10);
    if (HI_NULL == pWakeup)
    {
        HI_ERR_PM("ioremap_nocache c51 wake up key err! \n");
        return HI_FAILURE;
    }

    /* clean the wake up data*/
    HI_REG_WRITE32(pWakeup, 0xffffffff);
    HI_REG_WRITE32(pWakeup + 1, 0xffffffff);
    HI_REG_WRITE32(pWakeup + 2, 0xffffffff);

    iounmap(pWakeup);
#endif

    return HI_SUCCESS;
}

static long c51_Ioctl(struct file *file, HI_U32 cmd, HI_SIZE_T arg)
{
    HI_VOID __user *argp = (HI_VOID __user*)arg;

    if (down_interruptible(&c51Sem))
    {
        HI_ERR_PM(" down_interruptible err ! \n");
        return HI_FAILURE;
    }

    switch (cmd)
    {
    case HI_PMOC_STANDBY_CMD:
    {
        C51_PMOC_DISP_S dispInfo;

        if (copy_from_user(&dispInfo, argp, sizeof(C51_PMOC_DISP_S)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        dispMode  = dispInfo.mode;
        dispvalue = dispInfo.value;

        HI_INFO_PM("dispMode = %d \n", dispMode);
        HI_INFO_PM("dispvalue = 0x%08x \n", dispvalue);

        break;
    }
    case HI_PMOC_SET_WAKEUP_CMD:
    {
        C51_PMOC_VAL_S pmocVal;

        if (copy_from_user(&pmocVal, argp, sizeof(C51_PMOC_VAL_S)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        up(&c51Sem);
        return  c51_SetWakeUpParam(pmocVal);
    }
    case HI_PMOC_GET_WAKEUP_CMD:
    {
        C51_PMOC_VAL_S pmocVal;

        memset(&pmocVal, 0, sizeof(pmocVal));

        c51_GetWakeUpParam(&pmocVal);

        if (copy_to_user(argp, &pmocVal, sizeof(C51_PMOC_VAL_S)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        break;
    }
    case HI_PMOC_WAKEUP_READY_CMD:
    {
#ifdef HI_TEMP_CTRL_CONFIG
    g_u8TempCtrlEnable = HI_FALSE;
#endif

#ifdef HI_DVFS_CPU_SUPPORT
        cpu_dvfs_enable = HI_FALSE;
#endif

#ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
#endif
        break;
    }
    case HI_PMOC_GET_PERIOD_CMD:
    {
        HI_U32 u32StandbyPeriod = 0;
        HI_S32 ret;

        ret = c51_GetStandbyPeriod(&u32StandbyPeriod);
        if (ret != HI_SUCCESS)
        {
            up(&c51Sem);
            return ret;
        }

        if (copy_to_user(argp, &u32StandbyPeriod, sizeof(HI_U32)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        break;
    }
    case HI_PMOC_WAKEUP_SETDEV_CMD:
    {
        C51_PMOC_DEV_S dev;

        if (copy_from_user(&dev, argp, sizeof(C51_PMOC_DEV_S)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

#ifdef HI_KEYLED_SUPPORT
        kltype = dev.kltype;
#endif
        irtype = dev.irtype;
        break;
    }

    case HI_PMOC_LOAD_MCUCODE_CMD:
    {
        if (copy_from_user(lu32vC51Code, argp, sizeof(lu32vC51Code)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }
        break;
    }

    case HI_PMOC_SET_SCENE_CMD:
    {
        HI_UNF_PMOC_SCENE_E enPmocSence;

        if (copy_from_user(&enPmocSence, argp, sizeof(HI_UNF_PMOC_SCENE_E)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        C51_SetScene(enPmocSence);
        break;
    }

    case HI_PMOC_SET_PWROFFGPIO_CMD:
    {
        if (copy_from_user(GpioValArray, argp, sizeof(GpioValArray)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }
        break;
    }

    case HI_PMOC_ENTER_SMARTSTANDBY_CMD:
    {
        HI_U32 u32HoldModules;
        if (copy_from_user(&u32HoldModules, argp, sizeof(u32HoldModules)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        up(&c51Sem);
        return PMEnterSmartStandby(u32HoldModules);
    }

    case HI_PMOC_QUIT_SMARTSTANDBY_CMD:
    {
        up(&c51Sem);
        return PMQuitSmartStandby();
    }

    case HI_PMOC_BOOST_CPU:
    {
#ifdef HI_DVFS_CPU_SUPPORT
        up(&c51Sem);
        return pm_cpufreq_boost();
#endif
        break;
    }
    case HI_PMOC_GET_WAKEUPMODE_CMD:
    {
        C51_WAKEUP_MODE_S sWakeUpMode;
        HI_S32 ret;

        memset(&sWakeUpMode, 0, sizeof(sWakeUpMode));

        ret = c51_GetWakeUpMode(&sWakeUpMode);
        if (ret != HI_SUCCESS)
        {
            up(&c51Sem);
            return ret;
        }

        if (copy_to_user(argp, &sWakeUpMode, sizeof(C51_WAKEUP_MODE_S)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        break;
    }
    case HI_PMOC_CLEAN_WAKEUP_PARAM_CMD:
    {
        up(&c51Sem);
        return c51_CleanWakeUpMode();
    }
    case HI_PMOC_GET_TEMPERATURE_CMD:
    {
        HI_S32 s32Temperature;
        HI_S16 s16TempReal = 0;

#ifdef HI_DVFS_CPU_SUPPORT
        mpu_get_temperature(&s16TempReal);
#endif
        s32Temperature = s16TempReal * 1000;
        if (copy_to_user(argp, &s32Temperature, sizeof(HI_S32)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            up(&c51Sem);
            return HI_ERR_PM_COPY_DATA_ERR;
        }

        break;
    }
    default:
    {
        up(&c51Sem);
        return -ENOIOCTLCMD;
    }
    }

    up(&c51Sem);

    return HI_SUCCESS;
}

static HI_S32 c51_Open(struct inode *inode, struct file *filp)
{
    return HI_SUCCESS;
}

static HI_S32 c51_Release(struct inode *inode, struct file *filp)
{
    return HI_SUCCESS;
}

static struct file_operations stC51fopts = {
    .owner = THIS_MODULE,
    .open  = c51_Open,
    .release        = c51_Release,
    .unlocked_ioctl = c51_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = c51_Ioctl,  //user space 32bit and kernel space 64 bit run this function
#endif
};

#if (1 == HI_PROC_SUPPORT)

static PM_CMD_DATA_S g_astProcCmd[PM_CMD_MAX_NUM];
HI_S32 PMParseCmd(HI_U8* pu8Cmd, HI_U32 u32Len, PM_CMD_DATA_S** pstCmd, HI_U32* pu32Num)
{
    HI_U32 u32Pos = 0;
    HI_U32 u32SavePos = 0;
    HI_U32 u32CmdNum  = 0;
    HI_BOOL bIsCmd = HI_TRUE;
    HI_U8 u8LastChar = ' ';

    if ((HI_NULL == pu8Cmd) || (0 == u32Len) || (HI_NULL == pstCmd) || (HI_NULL == pu32Num))
    {
        HI_ERR_PM("Invalid.\n");
        return HI_FAILURE;
    }

    u32CmdNum = 0;
    memset(g_astProcCmd, 0, sizeof(g_astProcCmd));

    while ((u32Pos < u32Len) && (pu8Cmd[u32Pos]))
    {
        switch (pu8Cmd[u32Pos])
        {
        case '\0':
        case '\n':
        case '\t':
            break;

        case '=':
            if (bIsCmd)
            {
                bIsCmd = HI_FALSE;
                u32SavePos = 0;
            }

            break;
        case ' ':
            if (!((' ' == u8LastChar) || ('=' == u8LastChar)))
            {
                bIsCmd = !bIsCmd;
                u32SavePos = 0;
                if (bIsCmd)
                {
                    if (u32CmdNum < PM_CMD_MAX_NUM - 1)
                    {
                        u32CmdNum++;
                    }
                    else
                    {
                        goto out;
                    }
                }
            }

            break;
        default:
            if (bIsCmd)
            {
                if (u32SavePos < PM_CMD_MAX_CMD_LEN)
                {
                    g_astProcCmd[u32CmdNum].aszCmd[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }
            else
            {
                if (u32SavePos < PM_CMD_MAX_VLAUE_LEN)
                {
                    g_astProcCmd[u32CmdNum].aszValue[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }

            break;
        }

        u8LastChar = pu8Cmd[u32Pos];
        u32Pos++;
    }

out:
    if (strlen(g_astProcCmd[u32CmdNum].aszCmd) > 0)
    {
        u32CmdNum += 1;
    }

    *pstCmd  = g_astProcCmd;
    *pu32Num = u32CmdNum;
    return HI_SUCCESS;
}

HI_U32 PMParseValue(HI_U8* pu8Value)
{
    if (HI_NULL == pu8Value)
    {
        HI_ERR_PM("Invalid u8Value.\n");
        return HI_FAILURE;
    }

    if (strlen(pu8Value) < 2)
    {
        return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 10);
    }
    else
    {
        if ((pu8Value[0] == '0') && ((pu8Value[1] == 'x') || (pu8Value[1] == 'X')))
        {
            return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 16);
        }
        else
        {
            return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 10);
        }
    }
}

/***********************************************************************/
/*entrance of function controled by the proc file system*/
/*CNcomment:ͨ��proc�ļ�ϵͳ���п��Ƶĺ������*/
static HI_S8 g_s8KeyLedType[5][16] = {
    "74HC164", "PT6961", "CT1642", "PT6964", "FD650"
};
static HI_S8 g_s8IRType[5][16] = {
    "NEC Simple", "TC9012", "NEC Full", "SONY", "RAW"
};
static HI_S8 g_s8DebugType[5][32] = {
    "No debug info",          "Save debug info to ram",
    "Show debug info to LED", "Save to ram & Show to LED",
    "Show debug info in serial port"
};

static HI_S32 PMProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U8 i;

    PROC_PRINT(p, "---------Hisilicon PM Info---------\n");
    PROC_PRINT(p,
               "Scene                   \t :%s\n"
               "Ethernet WakeUp         \t :%s\n"
               "USB WakeUp              \t :%s\n"
               "Display Mode            \t :%s\n"
               "Display Value           \t :0x%08x\n"
               "WakeUp TimeOut          \t :%u(s)\n"
               "KeyLed Type             \t :%s\n"
               "KeyLed WakeUp Key       \t :%d\n"
               "IR Type                 \t :%s\n"
               "IR WakeUp Key Number    \t :%d\n",

               (g_u8FwEnable == 1) ? "Eth Forward" : "Standard",
               (g_u8EthWakeUpEnable == 1) ? "Enable" : "Disable",
               (g_u8UsbWakeUpMask == 1) ? "Enable" : "Disable",
               (dispMode == 0) ? "No Display" : ((dispMode == 1) ? "Display Number" : "Display Time"),
               dispvalue,
               timeVal,
               g_s8KeyLedType[kltype],
               keyVal,
               g_s8IRType[irtype],
               irpmocnum);

    for (i = 0; i < irpmocnum; i++)
    {
        PROC_PRINT(p, "IR WakeUp Key:          \t :High 32-bit(0x%x), Low 32-bit(0x%x)\n",
                   irValhigh[i], irVallow[i]);
    }

    PROC_PRINT(p,
               "Wake Up Reset             \t :%s \n"
               "Debug Mode                \t :%s \n"
               "HDMI CEC wake up          \t :%s \n"
               "Gpio wake up port         \t :0x%08x \n"
               "Power off GPIO Number     \t :%d \n"
               "Power off GPIO Direction  \t :%d \n",

               (wdgon == 1) ? "Enable" : "Disable",
               g_s8DebugType[dbgmask],
               (g_bCECWakeUpEnable == 1) ? "Enable" : "Disable",
               g_u32GpioPortVal,
               GpioValArray[0],
               GpioValArray[1]);

    return HI_SUCCESS;
}

static HI_S32 MCUDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    if ((u32Para1 == 0) || (u32Para1 == 1))
    {
        wdgon = u32Para1;
    }
    else
    {
        HI_ERR_PM("plese set the value of Watchdog Status : 0x0(CLOSE) or 0x1(ON)\n");
    }

    if (u32Para2 <= 7)
    {
        dbgmask = u32Para2;
    }
    else
    {
        HI_ERR_PM("plese set the value of Debug Mode : between 0x0 and 0x7\n");
    }

    return HI_SUCCESS;
}

static HI_VOID MCUProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo reset=0/1 > /proc/hisi/msp/pm, wake up reset or not.\n"
        "echo debug=0/1/2/4> /proc/hisi/msp/pm, set debug level:\n"
        "\t0: %s;\n"
        "\t1: %s;\n"
        "\t2: %s;\n"
        "\t4: %s.\n",
        g_s8DebugType[0], g_s8DebugType[1], g_s8DebugType[2], g_s8DebugType[3]
        );

    return;
}

static HI_S32 PMProcWrite(struct file * file,
                          const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if ((count > 63) || (copy_from_user(ProcPara, buf, count)))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        goto err;
    }

    if (1 == u32CmdNum)
    {
        /* Only set reset mode */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_WAKEUPRESET, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUDebugCtrl(PMParseValue(pstCmd[0].aszValue), dbgmask);
        }
        /* Only set debug level */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_DEBUG, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUDebugCtrl(wdgon, PMParseValue(pstCmd[0].aszValue));
        }
        /* Help */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HELP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUProcHelper();
        }
        /* Enter smart stanby */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_ENTERSMARTSTANDBY, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            PMEnterSmartStandby(PMParseValue(pstCmd[0].aszValue));
        }
        /* Quit smart stanby */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_QUITSMARTSTANDBY, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            PMQuitSmartStandby();
        }
        /* Support 0xXXX 0xXXX command */
        else
        {
            MCUDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else
    {
        goto err;
    }

    return count;

err:
    HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
    MCUProcHelper();
    return count;
}

#endif

#ifdef HI_DVFS_CPU_SUPPORT
#ifdef CHIP_TYPE_hi3796mv200
#define OTP_TMP_TRIM (0x318)
#else
#define OTP_TMP_TRIM (0x258)
#endif

#ifdef CA_FRAMEWORK_V200_SUPPORT
extern HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *value);
#else
extern HI_U32 HAL_OTP_V200_Read(HI_U32 addr);
#endif
void mpu_init_temperature(void)
{
    /* Init tsensor */
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    HI_REG_WRITE32(PERI_PMC10, 0x72);
#else
    HI_REG_WRITE32(PERI_PMC10, 0x07200000);
#endif

#if !defined(CHIP_TYPE_hi3716mv410) && !defined(CHIP_TYPE_hi3716mv420)
    #ifdef CA_FRAMEWORK_V200_SUPPORT
        HAL_OTP_Read(OTP_TMP_TRIM, &g_u32TempTrim);
    #else
        g_u32TempTrim = HAL_OTP_V200_Read(OTP_TMP_TRIM);
    #endif
#endif

    return;
}

void mpu_get_temperature(HI_S16 * ps16Temp)
{
    HI_U32 u32RegVal;
    HI_U8 i, j;
    HI_U32 u32TsensorAverage = 0;

    if (HI_NULL == ps16Temp)
    {
        HI_ERR_PM("Invalid param \n");
        return;
    }

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    HI_REG_WRITE32(PERI_PMC10, 0x72);
    for (j = 0; j < 4; j++)
    {
        HI_REG_READ32(PERI_PMC12 + j, u32RegVal);
        for (i = 0; i < 2; i++)
        {
            u32TsensorAverage += ((u32RegVal >> (16 * i)) & 0x3ff);
        }
    }
#else
    HI_REG_WRITE32(PERI_PMC10, 0x07200000);

    for (j = 0; j < 2; j++)
    {
        HI_REG_READ32(PERI_PMC12 + j, u32RegVal);
        for (i = 0; i < 4; i++)
        {
            u32TsensorAverage += ((u32RegVal >> (8 * i)) & 0xff);
        }
    }
#endif

    u32TsensorAverage = (u32TsensorAverage / 8);

#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798mv310)   \
    || defined(CHIP_TYPE_hi3796mv200)
    if ((HI_CHIP_TYPE_HI3798M == g_enChipType) && (HI_CHIP_VERSION_V300 == g_enChipID))
    {
        *ps16Temp = ((u32TsensorAverage - 171) * 165 / 774) - 40;
    }
    else
    {
        *ps16Temp = ((u32TsensorAverage - 125) * 165 / 806) - 40;
    }
#elif defined(CHIP_TYPE_hi3798mv200_a)
    *ps16Temp = ((u32TsensorAverage - 171) * 165 / 774) - 40;
#else
    *ps16Temp = (u32TsensorAverage * 180) / 255 - 40;
#endif

    u32RegVal = g_u32TempTrim & 0x400000; //bit[22]
    if (u32RegVal == 0)
    {
     *ps16Temp += ((g_u32TempTrim >> 18) & 0xf);//bit[21:18]
    }
    else
    {
     *ps16Temp -= ((g_u32TempTrim >> 18) & 0xf);
    }

    return;
}

#if (1 == HI_PROC_SUPPORT)

HI_S32 CPUDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    HI_U32 u32CpuCurFreq = 0;

    HI_INFO_PM("\n xx u32Para1 = 0x%x, u32Para2 = 0x%x \n", u32Para1, u32Para2);

    if ((0 == u32Para1) && (0 == u32Para2))
    {
        HI_ERR_PM("plese set the valid value \n");
        return HI_SUCCESS;
    }

#ifdef HI_AVS_SUPPORT
    CPU_AVS_Enable(HI_FALSE);
#endif

    if (0 == u32Para2)
    {
        hi_clk_set_rate(&mpu_ck, u32Para1);

        HI_INFO_PM("\n set rate2 = 0x%x finish \n", u32Para1);

        return HI_SUCCESS;
    }
    else if (0 == u32Para1)
    {
        cpu_volt_scale(u32Para2);

        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);

        return HI_SUCCESS;
    }

    u32CpuCurFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);

    if (u32Para1 > u32CpuCurFreq)
    {
        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);

        cpu_volt_scale(u32Para2);

        msleep(10);

        hi_clk_set_rate(&mpu_ck, u32Para1);

        HI_INFO_PM("\n set rate = 0x%x finish \n", u32Para1);
    }
    else
    {
        HI_INFO_PM("\n set rate = 0x%x before \n", u32Para1);
        hi_clk_set_rate(&mpu_ck, u32Para1);

        msleep(10);

        cpu_volt_scale(u32Para2);

        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);
    }

    return HI_SUCCESS;
}

static HI_VOID CPUProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo volt=1180 > /proc/hisi/msp/pm_cpu, set cpu volt in mv.\n"
        "echo freq=1000000 > /proc/hisi/msp/pm_cpu, set cpu freq in kHz.\n"
        "echo avs on/off > /proc/hisi/msp/pm_cpu, open/close cpu avs.\n"
        "echo freq=1000000 volt=1180 > /proc/hisi/msp/pm_cpu, set cpu volt and freq simultaneity.\n"
        );

    return;
}

static HI_S32 CPUProcWrite(struct file * file,
                           const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if ((count > 63) || (copy_from_user(ProcPara, buf, count)))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        goto err;
    }

    if (1 == u32CmdNum)
    {
        /* Only set CPU volt */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUDebugCtrl(0, PMParseValue(pstCmd[0].aszValue));
        }
        /* Only set CPU freq */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszValue), 0);
        }

#ifdef HI_AVS_SUPPORT
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HPMOFFSET, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_u8CpuHpmOffset = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_AVS, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            /* CPU AVS ON */
            if (0 == HI_OSAL_Strncasecmp(PM_CMD_ON, pstCmd[0].aszValue, strlen(pstCmd[0].aszCmd)))
            {
                CPU_AVS_Enable(HI_TRUE);
            }
            /* CPU AVS OFF */
            else if (0 == HI_OSAL_Strncasecmp(PM_CMD_OFF, pstCmd[0].aszValue, strlen(pstCmd[0].aszCmd)))
            {
                CPU_AVS_Enable(HI_FALSE);
            }
        }
#endif

        /* Help */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HELP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUProcHelper();
        }
        /* Support 0xXXX 0xXXX command */
        else /*if (('0' == pstCmd[0].aszCmd[0]) && ('0' == pstCmd[0].aszValue[0]))*/
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else if (2 == u32CmdNum)
    {
        if ((0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
            && (0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[1].aszValue), PMParseValue(pstCmd[0].aszValue));
        }
        else if ((0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
                 && (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszValue), PMParseValue(pstCmd[1].aszValue));
        }
        else
        {
            goto err;
        }
    }
    else
    {
        goto err;
    }

    return count;

err:
    HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
    CPUProcHelper();
    return count;
}

extern unsigned int cur_cpu_hpm;
static HI_S32 CPUProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 u32CpuVolt, u32CpuFreq;

    HI_U32 u32CpuAVSStatus = 0xff;
    HI_S16 s16Temperature;
    HI_U8 u8CpuHpmOffset = 0x0;

#ifdef HI_AVS_SUPPORT
    u32CpuAVSStatus = CPU_AVS_GetStatus();
    u8CpuHpmOffset  = g_u8CpuHpmOffset;
#endif
    mutex_lock(&hi_dvfs_lock);
#ifndef HI_AVS_HARDWARE
    u32CpuVolt = cur_cpu_volt;
#else
    u32CpuVolt = mpu_get_volt();
#endif
    u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
    mutex_unlock(&hi_dvfs_lock);

    mpu_get_temperature(&s16Temperature);

#if defined(CHIP_TYPE_hi3716mv410)
    PROC_PRINT(p, "CPU: freq = %d(kHz)\n", u32CpuFreq);
#else
    PROC_PRINT(p, "CPU: freq = %d(kHz), current volt = %d(mv) \n", u32CpuFreq, u32CpuVolt);
#endif
#ifdef HI_AVS_SUPPORT
    PROC_PRINT(p, "CPU: AVS = %s, hpm offset = %d hpm target = 0x%x \n",
               (u32CpuAVSStatus != 0xff) ? ((u32CpuAVSStatus == 1) ? "On" : "Off") : "None", u8CpuHpmOffset,
               cur_cpu_hpm);
#else
    PROC_PRINT(p, "CPU: AVS = %s, hpm offset = %d \n",
               (u32CpuAVSStatus != 0xff) ? ((u32CpuAVSStatus == 1) ? "On" : "Off") : "None", u8CpuHpmOffset);
#endif
    PROC_PRINT(p, "Tsensor: temperature = %d degree \n", s16Temperature);
#ifdef HI_TEMP_CTRL_CONFIG
    PROC_PRINT(p, "CPU: Temp Control is %s \n", (cpu_dvfs_enable == HI_TRUE) ? "Quit" : "Enter");
#endif
    return HI_SUCCESS;
}

#endif //end of (1 == HI_PROC_SUPPORT)

#ifdef HI_TEMP_CTRL_CONFIG
#if (1 == HI_PROC_SUPPORT)
static HI_VOID TempProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo tempctrl=1 > /proc/hisi/msp/pm_temp, enable temperature control\n"
        "echo tempdown=110 > /proc/hisi/msp/pm_temp, set down threshold temperature.\n"
        "echo tempup=100 > /proc/hisi/msp/pm_temp, set up threshold temperature.\n"
        "echo tempreboot=125 > /proc/hisi/msp/pm_temp, set reboot threshold temperature.\n"
        );

    return;
}

static HI_S32 TempProcRead(struct seq_file *p, HI_VOID *v)
{
    PROC_PRINT(p, "Temperature control is %s \n", (g_u8TempCtrlEnable == HI_TRUE) ? "On" : "Off");
    PROC_PRINT(p, "Temperature down threshold:  %d degree\n", g_s16TempDown);
    PROC_PRINT(p, "Temperature up threshold:  %d degree\n", g_s16TempUp);
    PROC_PRINT(p, "Temperature reboot threshold:  %d degree\n", g_s16TempReboot);

    return HI_SUCCESS;
}

static HI_S32 TempProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if ((count > 63) || (copy_from_user(ProcPara, buf, count)))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        return count;
    }

    if (1 == u32CmdNum)
    {
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPCTRL, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_u8TempCtrlEnable = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPDOWN, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempDown = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPUP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempUp = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPREBOOT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempReboot = PMParseValue(pstCmd[0].aszValue);
        }
        else
        {
            HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
            TempProcHelper();
            return count;
        }
    }

    return count;
}

#endif //end of (1 == HI_PROC_SUPPORT)

#if defined(CHIP_TYPE_hi3798cv200)
HI_VOID adjust_volt_in_low_temp(HI_BOOL bAddVolt)
{
    HI_U32 u32CpuVolt, u32CpuFreq;
    HI_U8 i;

    mutex_lock(&hi_dvfs_lock);
    u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
    if (u32CpuFreq < 800000)
    {
        u32CpuVolt = mpu_get_volt();

        for (i = 0; i < MAX_FREQ_NUM; i++)
        {
            if (u32CpuFreq == cpu_freq_hpm_table[i].freq)
            {
                break;
            }
        }

        if (i >= MAX_FREQ_NUM)
        {
            HI_ERR_PM("Can't find the freq(%d) in table \n", u32CpuFreq);
            mutex_unlock(&hi_dvfs_lock);
            return;
        }

        if (u32CpuVolt == cpu_freq_hpm_table[i].vsetting)
        {
            cpu_volt_scale(cpu_freq_hpm_table[i].vsetting + 50);
        }
        else
        {
            if (HI_FALSE == bAddVolt)
            {
                cpu_volt_scale(cpu_freq_hpm_table[i].vsetting);
            }
        }
    }
    else if (u32CpuFreq == 800000)
    {
 #ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
        hi_clk_set_rate(&mpu_ck, u32CpuFreq);
        CPU_AVS_Enable(HI_TRUE);
 #endif
    }

    mutex_unlock(&hi_dvfs_lock);

    return;
}
#endif


HI_S32 temperature_control_thread(void *Arg)
{
    HI_S16 s16Temperature;
    HI_U32 u32CpuFreq;
    HI_U32 u32OriCpuFreq = DEFAULT_INIT_FREQ;
    HI_U8 u8TimeInterval = 100;
    HI_U8 i;
    HI_BOOL bNeedReboot = HI_TRUE;
    HI_BOOL bStatus = HI_FALSE;

#if defined(CHIP_TYPE_hi3798cv200)
    HI_BOOL bEneterLowTemp = HI_FALSE;
#endif

    HI_INFO_PM("enter temperature_control_thread\n");

    g_s16TempUp = TEMP_UP;
    g_s16TempDown = TEMP_DOWN;
    g_s16TempReboot = TEMP_REBOOT;
    g_u8TempCtrlEnable = HI_TRUE;

/* This register 0 means normal mode */
#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)\
|| defined(CHIP_TYPE_hi3796mv200)
    g_pstRegSysCtrl->SC_GENm[13] = TEMP_STATUS_NORMAL;
#else
    g_pstRegSysCtrl->SC_GEN13 = TEMP_STATUS_NORMAL;
#endif

    while (!kthread_should_stop())
    {
        msleep(u8TimeInterval);

#ifdef CHIP_TYPE_hi3796mv200
#ifndef HI_TEE_SUPPORT
        if (bSMCULoadOK == HI_FALSE)
        {
            smcu_close_clk();
        }
#endif
#endif

        if (HI_FALSE == g_u8TempCtrlEnable)
        {
            continue;
        }

        mpu_get_temperature(&s16Temperature);

#if defined(CHIP_TYPE_hi3798cv200)
        if (s16Temperature <= LOW_TEMPERATURE)
        {
            if (HI_FALSE == bEneterLowTemp)
            {
                adjust_volt_in_low_temp(HI_TRUE);
                bEneterLowTemp = HI_TRUE;
            }
        }
        else
        {
            if (HI_TRUE == bEneterLowTemp)
            {
                adjust_volt_in_low_temp(HI_FALSE);
                bEneterLowTemp = HI_FALSE;
            }
        }
#endif

        if (s16Temperature < g_s16TempUp)
        {
#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)\
|| defined(CHIP_TYPE_hi3796mv200)
            if (TEMP_STATUS_NORMAL != g_pstRegSysCtrl->SC_GENm[13])
#else
            if (TEMP_STATUS_NORMAL != g_pstRegSysCtrl->SC_GEN13)
#endif
            {
                for (i = 0; i < MAX_FREQ_NUM; i++)
                {
                    if (u32OriCpuFreq == cpu_freq_hpm_table[i].freq)
                    {
                        break;
                    }
                }

                if (i >= MAX_FREQ_NUM)
                {
                    continue;
                }

                u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
                hi_device_scale(&mpu_dev, u32CpuFreq, u32OriCpuFreq);

                cpu_dvfs_enable = HI_TRUE;
#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)\
|| defined(CHIP_TYPE_hi3796mv200)
                g_pstRegSysCtrl->SC_GENm[13] = TEMP_STATUS_NORMAL;
#else
                g_pstRegSysCtrl->SC_GEN13 = TEMP_STATUS_NORMAL;
#endif
            }

            bNeedReboot = HI_TRUE;
            u8TimeInterval = 100;
            continue;
        }
        else if ((g_s16TempDown <= s16Temperature) && (s16Temperature < g_s16TempReboot))
        {
            /* stop dvfs */
            if (HI_TRUE == cpu_dvfs_enable)
            {
                cpu_dvfs_enable = HI_FALSE;

 /* This register TEMP_STATUS_CONTROL means entering temp. control mode */
#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)\
|| defined(CHIP_TYPE_hi3796mv200)
                g_pstRegSysCtrl->SC_GENm[13] = TEMP_STATUS_CONTROL;
#else
                g_pstRegSysCtrl->SC_GEN13 = TEMP_STATUS_CONTROL;
#endif
                u32OriCpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
                HI_INFO_PM("u32OriCpuFreq = %d \n", u32OriCpuFreq);
            }

            u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
            if (u32CpuFreq == cpu_freq_hpm_table[0].freq)
            {
                continue;
            }
            else
            {
                /* close avs */
            #ifdef HI_AVS_SUPPORT
                CPU_AVS_Enable(HI_FALSE);
            #endif

                /* set freq to low */
                hi_device_scale(&mpu_dev, u32CpuFreq, cpu_freq_hpm_table[0].freq);
            }

            bNeedReboot = HI_TRUE;
            u8TimeInterval = 20;
        }
        else if (s16Temperature >= g_s16TempReboot)
        {
            if (HI_TRUE == cpu_dvfs_enable)
            {
                /* stop dvfs */
                cpu_dvfs_enable = HI_FALSE;
#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)\
|| defined(CHIP_TYPE_hi3796mv200)
                g_pstRegSysCtrl->SC_GENm[13] = TEMP_STATUS_CONTROL;
#else
                g_pstRegSysCtrl->SC_GEN13 = TEMP_STATUS_CONTROL;
#endif
                u32OriCpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);

                /* set freq to low */
                hi_device_scale(&mpu_dev, u32OriCpuFreq, cpu_freq_hpm_table[0].freq);

                /* in the process of start system, do not reboot system  */
                bNeedReboot = HI_FALSE;
            }
            else
            {
                if (HI_TRUE == bNeedReboot)
                {
                    HI_ERR_PM("Tsensor is extremly high, suspend system!!\n");

                    get_mcu_status(&bStatus);
                    if (HI_FALSE == bStatus)
                    {
                        c51_loadPara();
                        set_mcu_status(0x1); //start MCU
                    }

#if defined(CHIP_TYPE_hi3798cv200) \
|| defined(CHIP_TYPE_hi3798mv200)  \
|| defined(CHIP_TYPE_hi3798mv300)  \
|| defined(CHIP_TYPE_hi3798mv310)   \
|| defined(CHIP_TYPE_hi3798mv200_a)
                    g_pstRegSysCtrl->SC_GENm[13] = TEMP_STATUS_STANDBY;
#elif defined(CHIP_TYPE_hi3796mv200)
                    g_pstRegSysCtrl->LP_START.u32 = TEMP_STATUS_STANDBY;
#else
                    g_pstRegSysCtrl->SC_GEN13 = TEMP_STATUS_STANDBY;
#endif
                }
            }
        }
    }

    return HI_SUCCESS;
}

#endif

#if (1 == HI_PROC_SUPPORT)
HI_S32 COREDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    if ((0 == u32Para1) && (0 == u32Para2))
    {
#if defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3798mv100)
        core_volt_scale(init_core_volt);
#else
        HI_ERR_PM("plese set the valid value \n");
#endif
        return HI_SUCCESS;
    }

    if (u32Para2 != 0)
    {
        core_volt_scale(u32Para2);
    }
    else
    {
        core_volt_scale(u32Para1);
    }

    return HI_SUCCESS;
}

static HI_VOID COREProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo volt=1180 > /proc/hisi/msp/pm_core, set core volt in mv.\n"
        );

    return;
}

static HI_S32 COREProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if ((count > 63) || (copy_from_user(ProcPara, buf, count)))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if ((HI_SUCCESS == s32Ret) && (1 == u32CmdNum))
    {
        /* Set core volt */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            COREDebugCtrl(0, PMParseValue(pstCmd[0].aszValue));
        }
        else
        {
            COREDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else
    {
        HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
        COREProcHelper();
    }

    return count;
}

static HI_S32 COREProcRead(struct seq_file *p, HI_VOID *v)
{
#if defined(CHIP_TYPE_hi3716mv410)
    PROC_PRINT(p, "No Support!\n");
#else
    HI_U32 u32CoreVolt, u32VoltMin, u32VoltMid, u32VoltMax;

    u32CoreVolt = core_get_volt();

    PROC_PRINT(p, "CORE: volt = %d(mv)\n", u32CoreVolt);

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32VoltMin = (g_pstRegSysCtrl->SC_GENm[17] >> 16) & 0xff;
#else
    u32VoltMin = (g_pstRegSysCtrl->SC_GEN17 >> 16) & 0xff;
#endif
    u32VoltMin = CORE_VMAX - ((u32VoltMin - 1) * PWM_STEP) / PWM_CLASS;

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32VoltMax = g_pstRegSysCtrl->SC_GENm[17] & 0xff;
#else
    u32VoltMax = g_pstRegSysCtrl->SC_GEN17 & 0xff;
#endif
    u32VoltMax = CORE_VMAX - ((u32VoltMax - 1) * PWM_STEP) / PWM_CLASS;

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32VoltMid = (g_pstRegSysCtrl->SC_GENm[17] >> 8) & 0xff;
#else
    u32VoltMid = (g_pstRegSysCtrl->SC_GEN17 >> 8) & 0xff;
#endif
    u32VoltMid = CORE_VMAX - ((u32VoltMid - 1) * PWM_STEP) / PWM_CLASS;

    PROC_PRINT(p, "CORE: Level1 volt = %d(mv), Level2 volt = %d(mv), Level3 volt = %d(mv)\n", u32VoltMin, u32VoltMid, u32VoltMax);
#endif

    return HI_SUCCESS;
}

 #endif //end of (1 == HI_PROC_SUPPORT)
#endif

#ifdef HI_DVFS_CPU_SUPPORT
extern int pm_cpufreq_set_boost(int flag, int freq);
#endif
static PMOC_EXT_FUNC_S g_stPmocExportFuncs =
{
#ifdef HI_DVFS_CPU_SUPPORT
    .pfnPmocSetCPUFreq = pm_cpufreq_set_boost,
#endif
};

/***********************************************************************/
HI_S32 PMOC_DRV_ModInit(HI_VOID)
{
    HI_S32 ret;

#if (1 == HI_PROC_SUPPORT)
    DRV_PROC_ITEM_S *item;
#endif

    HI_INIT_MUTEX(&c51Sem);

#ifdef CHIP_TYPE_hi3796mv200
#ifndef HI_TEE_SUPPORT
    smcu_start();
#endif
#endif

#ifdef HI_TEE_MCU_SUPPORT
    mcu_load_code_tee();
#endif

    ret = HI_DRV_MODULE_Register(HI_ID_PM, "HI_PM", (HI_VOID*)&g_stPmocExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PM("c51 init fail ret = 0x%x!\n", ret);
        return ret;
    }

#ifdef HI_GPIO_LIGHT_SUPPORT
    ret = HI_DRV_MODULE_GetFunction(HI_ID_GPIO, (HI_VOID**)&s_pGpioFunc);
    if ((HI_SUCCESS != ret) || (s_pGpioFunc == HI_NULL))
    {
        HI_ERR_PM("Get GPIO function failed! \n");
        return HI_FAILURE;
    }
#endif

#if (1 == HI_PROC_SUPPORT)
    item = HI_DRV_PROC_AddModule("pm", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = PMProcRead;
    item->write = PMProcWrite;
#endif

    /* get chip type for the whole pmoc module use */
    HI_DRV_SYS_GetChipVersion(&g_enChipType, &g_enChipID);

    ret = c51_loadCode();
    if (ret)
    {
        HI_ERR_PM("c51_loadCode err! \n");
        return HI_FAILURE;
    }

#ifdef HI_DVFS_CPU_SUPPORT
 #if (1 == HI_PROC_SUPPORT)
    item = HI_DRV_PROC_AddModule("pm_cpu", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = CPUProcRead;
    item->write = CPUProcWrite;

    item = HI_DRV_PROC_AddModule("pm_core", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = COREProcRead;
    item->write = COREProcWrite;
 #endif

    g_pPMCStart = ioremap_nocache(PMC_BASE, 0x1000);
    if (HI_NULL == g_pPMCStart)
    {
        HI_ERR_PM("ioremap_nocache pmc base err! \n");
        return HI_FAILURE;
    }

    core_init_volt();

    mpu_init_volt();
    mpu_init_clocks();
    hi_cpufreq_init();
    mpu_init_temperature();

 #ifdef HI_TEMP_CTRL_CONFIG
  #if (1 == HI_PROC_SUPPORT)
    item = HI_DRV_PROC_AddModule("pm_temp", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = TempProcRead;
    item->write = TempProcWrite;
  #endif

    pstTempCtrlThread = kthread_create(temperature_control_thread, NULL, "temperature_control");
    if (IS_ERR(pstTempCtrlThread))
    {
        HI_ERR_PM("create mcu watchdog thread failed.\n");
        return HI_FAILURE;
    }
    wake_up_process(pstTempCtrlThread);
 #endif
#endif

    HI_OSAL_Snprintf(g_stPmDev.devfs_name, sizeof(g_stPmDev.devfs_name), UMAP_DEVNAME_PM);
    g_stPmDev.fops   = &stC51fopts;
    g_stPmDev.minor  = UMAP_MIN_MINOR_PM;
    g_stPmDev.owner  = THIS_MODULE;
    g_stPmDev.drvops = &c51_baseOps;
    if (HI_DRV_DEV_Register(&g_stPmDev) < 0)
    {
        HI_FATAL_PM("Unable to register pm dev\n");
        return HI_FAILURE;
    }

    if (get_Advca_Support())
    {
#ifdef NOCS3_0_SUPPORT
        /* save ddr phy param for standby */
        DDRPHYRegSave_MV410();

        /* lock mcu ram */
        set_mcu_lock(0x3);

        /* set gpio wakeup interrupt to level */
        g_u8GpioIS = 1;
#endif

       /* before start mcu, clear the runtime check ok flag */
#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3796mv200)
        g_pstRegSysCtrl->SC_GENx[3] = 0;
#else
        g_pstRegSysCtrl->SC_GEN27 = 0;
#endif
        set_mcu_status(0x1);
    }
    else
    {
#ifdef HI_PM_START_MCU_RUNNING
        set_mcu_status(0x1);
#endif
    }

#ifdef MODULE
    HI_PRINT("Load hi_pmoc.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID PMOC_DRV_ModExit(HI_VOID)
{
#if (1 == HI_PROC_SUPPORT)
    HI_DRV_PROC_RemoveModule("pm");
#endif

#ifdef HI_DVFS_CPU_SUPPORT
 #if (1 == HI_PROC_SUPPORT)
    HI_DRV_PROC_RemoveModule("pm_cpu");
    HI_DRV_PROC_RemoveModule("pm_core");
 #endif
    hi_cpufreq_exit();
    mpu_exit_clocks();
    mpu_deinit_volt();

 #ifdef HI_TEMP_CTRL_CONFIG
  #if (1 == HI_PROC_SUPPORT)
    HI_DRV_PROC_RemoveModule("pm_temp");
  #endif
    if (pstTempCtrlThread)
    {
        kthread_stop(pstTempCtrlThread);
        pstTempCtrlThread = HI_NULL;
    }
 #endif

    iounmap(g_pPMCStart);
#endif

    HI_DRV_DEV_UnRegister(&g_stPmDev);

    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_PM);

    HI_INFO_PM(" PMOC_DRV_ModExit ok! \n");

    return;
}

#ifdef MODULE
module_init(PMOC_DRV_ModInit);
module_exit(PMOC_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
