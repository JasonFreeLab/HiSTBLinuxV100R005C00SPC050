/*
 * hisilicon DVFS Management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
 */

#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/plist.h>
#include <linux/slab.h>
#include "opp.h"
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include "clock.h"
#include <linux/kthread.h>

#include "hi_reg_common.h"
#include "hi_drv_reg.h"
#include "hi_drv_sys.h"
#include "hi_dvfs.h"
#include "hi_drv_pmoc.h"
#include "drv_i2c_ext.h"
#include "hi_drv_module.h"
#include "hi_kernel_adapt.h"

extern struct clk mpu_ck;

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
#define PWM_CPU PERI_PMC7
#else
#define PWM_CPU PERI_PMC6
#endif

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a)
#define PWM_CORE PERI_PMC8
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
#define PWM_CORE PERI_PMC6
#else
#define PWM_CORE PERI_PMC7
#endif

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 10 /*ms*/

extern HI_CHIP_TYPE_E g_enChipType;
extern HI_CHIP_VERSION_E g_enChipID;
unsigned int cur_cpu_volt  = 1300;
unsigned int cur_core_volt = 1150;
unsigned int init_core_volt = 1150;

#if defined(CHIP_TYPE_hi3796mv200)
static unsigned int cpu_volt_1500[4] = {1200, 1040, 1130, 1200};
#endif

#ifdef HI_AVS_SUPPORT
 #ifndef HI_AVS_HARDWARE
 static struct task_struct *pstAVSThread = HI_NULL;
 #endif
HI_DECLARE_MUTEX(g_CPUAVSMutex);
static unsigned int cpu_avs_enable = HI_TRUE;
#endif

int core_volt_scale(unsigned int volt);

DEFINE_MUTEX(hi_dvfs_lock);

/**
 * struct hi_dvfs_info - The per vdd dvfs info
 * @user_lock:  spinlock for plist operations
 *
 * This is a fundamental structure used to store all the required
 * DVFS related information for a vdd.
 */
struct hi_dvfs_info
{
    unsigned int volt;
    unsigned int new_freq;
    unsigned int old_freq;
};

static void device_volt_scale(unsigned char device, unsigned int volt)
{
    unsigned int * pwm_reg;
    unsigned int period, duty, v, tmp;
    unsigned int vmax, vmin, pwc, pws;

    if (CPU_DEVICE == device)
    {
        pwm_reg = PWM_CPU;
        vmax = CPU_VMAX;
        vmin = CPU_VMIN;
    }
    else if (CORE_DEVICE == device)
    {
        pwm_reg = PWM_CORE;
        vmax = CORE_VMAX;
        vmin = CORE_VMIN;
    }
    else
    {
        HI_ERR_PM("Not supprot this device .\n");
        return;
    }

    pwc = PWM_CLASS;
    pws = PWM_STEP;

    period = (((vmax - vmin) * pwc) / pws) + 1;
    duty = (((vmax - volt) * pwc) / pws) + 1;

    HI_REG_READ32(pwm_reg, v);
    tmp = PWM_PERIOD_MASK;
    v &= ~tmp;
    v |= period;

    tmp = PWM_DUTY_MASK;
    v &= ~tmp;
    v |= duty << 16;
    HI_REG_WRITE32(pwm_reg, v);

    return;
}

int cpu_volt_scale(unsigned int volt)
{
#if defined(CHIP_TYPE_hi3716mv410)
    return 0;
#endif

    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);

    if (volt > CPU_VMAX)
    {
        HI_ERR_PM("volt %d is out of range! Force it to vmax\n", volt);
        volt = CPU_VMAX;
    }
    else if (volt < CPU_VMIN)
    {
        HI_ERR_PM("volt %d is out of range! Do not change volt \n", volt);
        return 0;
    }

    device_volt_scale(CPU_DEVICE, volt);

    cur_cpu_volt = volt;

    return 0;
}

#ifdef HI_AVS_SUPPORT
unsigned int CPU_AVS_GetStatus(void)
{
    return cpu_avs_enable;
}

void CPU_AVS_Enable(unsigned int enable)
{   
#ifdef HI_AVS_HARDWARE
    HI_U32 u32RegVal;
    HI_REG_READ32(PERI_PMC218, u32RegVal);
    if (HI_TRUE == enable)
    {
        u32RegVal |= 0x1;
    }
    else
    {
        u32RegVal &= 0xfffffffe;
    }
    HI_REG_WRITE32(PERI_PMC218, u32RegVal);

    if ((HI_CHIP_TYPE_HI3798M == g_enChipType) && (HI_CHIP_VERSION_V300 == g_enChipID))
    {
        /* set pwm0 duty limit enable */
        HI_REG_READ32(PERI_PMC223, u32RegVal);
        if (HI_TRUE == enable)
        {
            u32RegVal |= 0x1;
        }
        else
        {
            u32RegVal &= 0xfffffffe;
        }
        HI_REG_WRITE32(PERI_PMC223, u32RegVal);
    }
#endif

    cpu_avs_enable = enable;

    HI_INFO_PM("\n CPU_AVS_Enable = %d \n", enable);
}

extern unsigned int cur_cpu_hpm;
extern unsigned int cur_cpu_vmin;
extern unsigned int cur_cpu_vmax;
HI_S32 cpu_avs_thread(void *Arg)
{
    HI_U16 u16HpmCode, u16HpmCodeAverage = 0;
    HI_U32 u32RegVal;
    HI_S16 s16HpmDelta;
    HI_U8 i;
    HI_S32 ret;

    while (!kthread_should_stop())
    {
        msleep(AVS_INTERVAL);

        if (!CPU_AVS_GetStatus())
        {
            continue;
        }

        /* read current code */
        u16HpmCodeAverage = 0;
        for (i = 0; i < 2; i++)
        {
            HI_REG_READ32(PERI_PMC31, u32RegVal);
            u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;
            u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;

            HI_REG_READ32(PERI_PMC32, u32RegVal);
            u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;
            u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;

            msleep(4);
        }

        u16HpmCodeAverage = u16HpmCodeAverage / (i * 4);

        s16HpmDelta = u16HpmCodeAverage - cur_cpu_hpm;

        HI_INFO_PM("\n show u16HpmCodeMin = 0x%x cur_cpu_hpm = 0x%x \n", u16HpmCodeAverage, cur_cpu_hpm);

        /* compare code value */
        if (s16HpmDelta <= 0x1)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /* up 10mv */
            if (cur_cpu_volt < cur_cpu_vmax)
            {
                cpu_volt_scale(cur_cpu_volt + AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else if (s16HpmDelta >= 0xa)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /*down 10mv */
            if (cur_cpu_volt > cur_cpu_vmin)
            {
                cpu_volt_scale(cur_cpu_volt - AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else
        {
            msleep(10 * AVS_INTERVAL);
        }
    }

    return HI_SUCCESS;
}

#endif //end of HI_AVS_SUPPORT

unsigned int mpu_get_volt(void)
{
    unsigned int v;

    HI_REG_READ32(PWM_CPU, v);
    v = (v | 0xffff) >> 16;
    if (v == 0)
    {
        return CPU_VMAX;
    }
    v = CPU_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;

    return v;
}

void mpu_init_volt(void)
{
    /* get cpu volt set in boot */
    cur_cpu_volt = mpu_get_volt();

#ifdef HI_AVS_SUPPORT
 #ifndef HI_AVS_HARDWARE
    pstAVSThread = kthread_create(cpu_avs_thread, NULL, "cpu_avs");
    if (IS_ERR(pstAVSThread))
    {
        HI_ERR_PM("create avs thread failed.\n");
        return;
    }
    wake_up_process(pstAVSThread);
 #endif
#endif

    return;
}

void mpu_deinit_volt(void)
{
#ifdef HI_AVS_SUPPORT
 #ifndef HI_AVS_HARDWARE
    if (pstAVSThread)
    {
        kthread_stop(pstAVSThread);
        pstAVSThread = HI_NULL;
    }
 #endif
#endif
}

int core_volt_scale(unsigned int volt)
{
    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);
    if (volt > CORE_VMAX)
    {
        HI_ERR_PM("volt %d is out of range! Force it to vmax\n", volt);
        volt = CORE_VMAX;
    }
    else if (volt < CORE_VMIN)
    {
        HI_ERR_PM("volt %d is out of range! Do not change volt \n", volt);
        return 0;
    }
    device_volt_scale(CORE_DEVICE, volt);
    
    cur_core_volt = volt;

    return 0;
}

unsigned int core_get_volt(void)
{
    unsigned int v;

    /* get core volt set in boot */
    HI_REG_READ32(PWM_CORE, v);
    v = (v | 0xffff) >> 16;
    if (v == 0)
    {
        return CORE_VMAX;
    }
    v = CORE_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;

    return v;
}

void core_init_volt(void)
{
    cur_core_volt = core_get_volt();
    init_core_volt = cur_core_volt;

    return;
}

/**
 * _dvfs_scale() : Scale the devices associated with a voltage domain
 *
 * Returns 0 on success else the error value.
 */
static int _dvfs_scale(struct device *target_dev, struct hi_dvfs_info *tdvfs_info)
{
    struct clk * clk;
    int ret;

    HI_INFO_PM("%s rate=%ld\n", __FUNCTION__, tdvfs_info->new_freq);

    clk = &mpu_ck;
    if (tdvfs_info->new_freq == tdvfs_info->old_freq)
    {
        return 0;
    }
    else if (tdvfs_info->new_freq > tdvfs_info->old_freq)
    {
#ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }
#endif
        cpu_volt_scale(tdvfs_info->volt);

#ifdef HI_AVS_SUPPORT
        up(&g_CPUAVSMutex);
#endif

        msleep(10);
        ret = hi_clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("%s: scale freq to %ld falt\n",
                      __func__, tdvfs_info->new_freq);
            return ret;
        }
    }
    else
    {
#ifdef HI_AVS_SUPPORT
	    CPU_AVS_Enable(HI_FALSE);
#endif
        ret = hi_clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("%s: scale freq to %ld falt\n",
                      __func__, tdvfs_info->new_freq);
            return ret;
        }

        msleep(10);

#ifdef HI_AVS_SUPPORT
        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }
#endif
        cpu_volt_scale(tdvfs_info->volt);

#ifdef HI_AVS_SUPPORT
        up(&g_CPUAVSMutex);
#endif
    }

#ifdef HI_AVS_SUPPORT
 #if   defined(CHIP_TYPE_hi3798cv200) \
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3798mv200) \
    || defined(CHIP_TYPE_hi3798mv300) \
    || defined(CHIP_TYPE_hi3798mv310)
    if ((tdvfs_info->new_freq > 600000))
 #elif defined(CHIP_TYPE_hi3796mv200)
    if ((tdvfs_info->new_freq > 600000) && (tdvfs_info->new_freq < 1500000))
 #else
    if ((tdvfs_info->new_freq > 400000) && (tdvfs_info->new_freq < 1500000))
 #endif
    {
        /* wait for hpm test */
        msleep(8);
        CPU_AVS_Enable(HI_TRUE);
    }
#endif

    return ret;
}

/**
 * hi_device_scale() - Set a new rate at which the devices is to operate
 * @rate:   the rnew rate for the device.
 *
 * This API gets the device opp table associated with this device and
 * tries putting the device to the requested rate and the voltage domain
 * associated with the device to the voltage corresponding to the
 * requested rate. Since multiple devices can be assocciated with a
 * voltage domain this API finds out the possible voltage the
 * voltage domain can enter and then decides on the final device
 * rate.
 *
 * Return 0 on success else the error value
 */
int hi_device_scale(struct device *target_dev, unsigned int old_freq, unsigned int new_freq)
{
    struct opp *opp;
    unsigned long volt, freq = new_freq;
    struct hi_dvfs_info dvfs_info;
    
#if defined(CHIP_TYPE_hi3798cv200)
    HI_S16 s16Temperature;
#endif

#if defined(CHIP_TYPE_hi3796mv200)
    unsigned int corner_type;
#endif

    int ret = 0;

    HI_INFO_PM("hi_device_scale,oldfreq = %ld,newfreq = %ld\n", old_freq, new_freq);

    /* Lock me to ensure cross domain scaling is secure */
    mutex_lock(&hi_dvfs_lock);
    rcu_read_lock();

    opp = opp_find_freq_ceil(target_dev, &freq);

    /* If we dont find a max, try a floor at least */
    if (IS_ERR(opp))
    {
        opp = opp_find_freq_floor(target_dev, &freq);
    }

    if (IS_ERR(opp))
    {
        rcu_read_unlock();
        HI_ERR_PM("%s: Unable to find OPP for freq%ld\n",
                  __func__, freq);
        ret = -ENODEV;
        goto out;
    }

    volt = opp_get_voltage(opp);

    rcu_read_unlock();

    dvfs_info.old_freq = (unsigned int)old_freq;

    dvfs_info.new_freq = (unsigned int)freq;

    dvfs_info.volt = (unsigned int)volt;

    /* in low temp. add volt 50 mv */
#if defined(CHIP_TYPE_hi3798cv200)
    mpu_get_temperature(&s16Temperature);
    if (s16Temperature <= LOW_TEMPERATURE)
    {
        if (freq <= 600000)
        {
            dvfs_info.volt += 50;
        }
    }
#endif


#if defined(CHIP_TYPE_hi3796mv200)
    /* in 1.5G, set svb voltage */
    if ((cpu_volt_1500[0] == dvfs_info.volt) && (freq == 1500000))
    {
        corner_type = (g_pstRegSysCtrl->SC_GENm[17] >> 24) & 0xff;
        dvfs_info.volt = cpu_volt_1500[corner_type];
    }
#endif

    /* Do the actual scaling */
    ret = _dvfs_scale( target_dev, &dvfs_info);

    if (ret)
    {
        HI_ERR_PM("%s: scale failed %d[f=%ld, v=%ld]\n",
                  __func__, ret, freq, volt);

        /* Fall through */
    }

    /* Fall through */
out:
    mutex_unlock(&hi_dvfs_lock);
    return ret;
}
