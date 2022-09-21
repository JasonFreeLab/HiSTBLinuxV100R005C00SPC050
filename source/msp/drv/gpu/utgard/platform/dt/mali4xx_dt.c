
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/pm.h>

/* After 3.19.0 kenrel droped CONFIG_PM_RUNTIME define,define by ourself */
#if defined(CONFIG_PM) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 19, 0)
#define CONFIG_PM_RUNTIME 1
#endif

#ifdef CONFIG_PM_RUNTIME
 #include <linux/pm_runtime.h>
#endif
#include <asm/io.h>
#include <linux/mali/mali_utgard.h>
#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_osk_mali.h"

#include <linux/dma-mapping.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/clk.h>
#include <linux/delay.h>

#include "mali4xx_dt.h"
#include "mali4xx_scaling.h"
#include "mali4xx_opp.h"
#include "mali4xx_proc.h"
#include "mali4xx_cfg.h"

#include "drv_gpu_ext.h"

typedef enum
{
    SEC_REG_ADDR_BASE = 0xF9230200,
    SEC_REG_ADDR_SIZE = 0x0100,

    SEC_REG_OFFSET_SWITCH  = 0x0,
    SEC_REG_OFFSET_IDLES_COUNT = 0x4,
    SEC_REG_OFFSET_STATUS = 0x8,
} sec_reg_addr;

typedef enum
{
    TEMP_REG_ADDR_BASE = 0xF80000b4,
    TEMP_REG_ADDR_SIZE = 0x0100,

    TEMP_REG_VALUE_CONCTRL = 0x22222222,
} temp_reg_addr;

typedef enum
{
    MALI_POWER_MODE_ON,
    MALI_POWER_MODE_LIGHT_SLEEP,
    MALI_POWER_MODE_DEEP_SLEEP,
} mali_power_mode;

#if CONFIG_GPU_DVFS_ENABLE
static int mali_dvfs_enable = 1;
#else
int mali_dvfs_enable = 0;
#endif
module_param(mali_dvfs_enable, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_dvfs_enable, "enable dvfs");

#ifdef GPU_MAXFREQ_CONFIG_SUPPORT
static unsigned int mali_dvfs_max_frequency = 0;
module_param(mali_dvfs_max_frequency, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_dvfs_max_frequency, "max frequency");

static unsigned int mali_dvfs_min_frequency = 0;
module_param(mali_dvfs_min_frequency, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_dvfs_min_frequency, "min frequency");
#endif

static int mali_dvfs_max_utilization = 0;
module_param(mali_dvfs_max_utilization, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_dvfs_max_utilization, "max utilization");

static int mali_dvfs_min_utilization = 0;
module_param(mali_dvfs_min_utilization, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_dvfs_min_utilization, "min utilization");

static u32 s_PowerOff = 1;

static struct device *s_MaliDevice = NULL;

static struct mali_config s_MaliConfiguration;

static struct mali_hw_core *s_SecCore = NULL;
static struct mali_hw_core *s_TempCore = NULL;

static int	mali_adp_suspend(struct device *device);
static int	mali_adp_resume(struct device *device);
static int	mali_adp_freeze(struct device *device);
static int	mali_adp_thaw(struct device *device);
#ifdef CONFIG_PM_RUNTIME
static int	mali_adp_runtime_suspend(struct device *device);
static int	mali_adp_runtime_resume(struct device *device);
static int	mali_adp_runtime_idle(struct device *device);
#endif

int mali_adp_secure_init(void);
void mali_adp_secure_deinit(void);
int mali_adp_secure_enable(void);
int mali_adp_secure_disable(void);

_mali_osk_errcode_t mali_adp_platform_init(struct device *device);
_mali_osk_errcode_t mali_adp_platform_deinit(struct device *device);

static struct dev_pm_ops mali_device_dev_pm_ops =
{
    .suspend         = mali_adp_suspend,
    .resume          = mali_adp_resume,
    .freeze          = mali_adp_freeze,
    .thaw            = mali_adp_thaw,
    .restore         = mali_adp_thaw,
#ifdef CONFIG_PM_RUNTIME
    .runtime_suspend = mali_adp_runtime_suspend,
    .runtime_resume  = mali_adp_runtime_resume,
    .runtime_idle    = mali_adp_runtime_idle,
#endif
};

static struct device_type mali_device_device_type =
{
    .pm = &mali_device_dev_pm_ops,
};

static GPU_EXT_FUNC_S mali_export_function =
{
    .pfnGPUSetFreqAndVolt = mali_ext_set_freq_and_volt,
    .pfnGPUSetMaxFreq = mali_ext_set_max_freq,
};

static struct mali_gpu_device_data mali_device_data =
{
    .shared_mem_size      = CONFIG_GPU_MAX_SHARE_MEM_SIZE,
    .fb_start             = 0x00000000,
    .fb_size              = 0x80000000,
    .dedicated_mem_start  = 0x0,
    .dedicated_mem_size   = 0x0,
    .control_interval     = 50,          /*50ms*/
    .utilization_callback = NULL,
    .max_job_runtime      = 5000,        /* 5 seconds */
    .get_clock_info       = NULL,
    .get_freq             = NULL,
    .set_freq             = NULL,
    .secure_mode_init                   = mali_adp_secure_init,
    .secure_mode_deinit                 = mali_adp_secure_deinit,
    .gpu_reset_and_secure_mode_enable   = mali_adp_secure_enable,
    .gpu_reset_and_secure_mode_disable  = mali_adp_secure_disable,
};

int mali_platform_device_init(struct platform_device *device)
{
    int err = -1;

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3796mv200)
    int num_pp_cores = 2;
#else
    int num_pp_cores = 0;
#endif

    mali_adp_platform_init(&(device->dev));

#ifdef CONFIG_PM_RUNTIME
    atomic_set(&device->dev.power.usage_count, 0);
#endif

    if (!device->dev.dma_mask)
    {
        device->dev.dma_mask = &device->dev.coherent_dma_mask;
    }

    device->dev.type = &mali_device_device_type;

    err = platform_device_add_data(device, &mali_device_data, sizeof(mali_device_data));

    if (0 == err)
    {
#ifdef CONFIG_PM_RUNTIME
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 37))
        pm_runtime_set_autosuspend_delay(&(device->dev), 1000);
        pm_runtime_use_autosuspend(&(device->dev));
#endif
        pm_runtime_enable(&(device->dev));
#endif
        MALI_DEBUG_ASSERT(0 < num_pp_cores);
        mali_core_scaling_init(num_pp_cores);
    }

    return err;
}

int mali_platform_device_deinit(struct platform_device *device)
{
    MALI_IGNORE(device);

    mali_core_scaling_term();

#ifdef CONFIG_PM_RUNTIME
    pm_runtime_disable(&(device->dev));
#endif

    mali_adp_platform_deinit(&(device->dev));

    return 0;
}

static struct mali_hw_core * mali_adp_core_create(u32 phys_addr, u32 size, char* description)
{
    struct mali_hw_core *hwcore = (struct mali_hw_core *)_mali_osk_malloc(sizeof(struct mali_hw_core));

    if (NULL == hwcore)
    {
        HISI_ERROR_INFO();
        return NULL;
    }

    hwcore->phys_addr = phys_addr;
    hwcore->size = size;
    hwcore->description = NULL;
    hwcore->mapped_registers = _mali_osk_mem_mapioregion(hwcore->phys_addr, hwcore->size, hwcore->description);

    if (NULL == hwcore->mapped_registers)
    {
        HISI_ERROR_INFO();
        _mali_osk_free(hwcore);
        hwcore = NULL;
        return NULL;
    }

    return hwcore;
}

static void mali_adp_core_destroy(struct mali_hw_core *hwcore)
{
    if (NULL == hwcore)
    {
        HISI_ERROR_INFO();
        return;
    }

    _mali_osk_mem_unmapioregion(hwcore->phys_addr, hwcore->size, hwcore->mapped_registers);

    _mali_osk_free(hwcore);
}

void mali_adp_platform_hw_core_create(void)
{
    s_SecCore = mali_adp_core_create(SEC_REG_ADDR_BASE, SEC_REG_ADDR_SIZE, "hisi_sec");

    if (NULL == s_SecCore)
    {
        HISI_ERROR_INFO();
    }

    s_TempCore = mali_adp_core_create(TEMP_REG_ADDR_BASE, TEMP_REG_ADDR_SIZE, "hisi_temp");

    if (NULL == s_TempCore)
    {
        HISI_ERROR_INFO();
    }
}

void mali_adp_platform_hw_core_destroy(void)
{
    mali_adp_core_destroy(s_SecCore);

    s_SecCore = NULL;

    mali_adp_core_destroy(s_TempCore);

    s_TempCore = NULL;
}

_mali_osk_errcode_t mali_adp_platform_init(struct device *device)
{
    mali_adp_platform_hw_core_create();

    s_MaliDevice = device;

#ifdef GPU_PROC_SUPPORT
    gpu_proc_create();
#endif

    HI_DRV_MODULE_Register(HI_ID_GPU, "MALI", (HI_VOID*)&mali_export_function);

    MALI_SUCCESS;
}

_mali_osk_errcode_t mali_adp_platform_deinit(struct device *device)
{
#ifdef GPU_PROC_SUPPORT
    gpu_proc_destroy();
#endif

    mali_adp_platform_hw_core_destroy();

    s_MaliDevice = NULL;

    HI_DRV_MODULE_UnRegister(HI_ID_GPU);

    MALI_SUCCESS;
}

_mali_osk_errcode_t mali_adp_power_mode_change(struct device *device, mali_power_mode power_mode, mali_bool isruntime)
{
    struct mali_device *mdev = dev_get_drvdata(device);
    unsigned long d_freq, d_volt;

    d_volt = opps_get_default_volt();
    d_freq = opps_get_default_freq();

    switch (power_mode)
    {
        case MALI_POWER_MODE_ON:
            if (s_PowerOff == 1)
            {
                clk_enable(mdev->clock);

                s_PowerOff = 0;
            }
            break;
        case MALI_POWER_MODE_LIGHT_SLEEP:
        case MALI_POWER_MODE_DEEP_SLEEP:
            if (s_PowerOff == 0)
            {
                if(mali_dvfs_enable == 1)
                {
                    regulator_set_voltage(mdev->regulator, d_volt, d_volt);
                    clk_set_rate(mdev->clock, d_freq);
                    mdev->current_voltage = d_volt;
                    mdev->current_freq = d_freq;
                }

                clk_disable(mdev->clock);

                s_PowerOff = 1;
            }
            break;
    }

    if(HISI_DEBUG)
        printk("mali_adp_power_mode_change@ power_mode = %d\n", power_mode);

    MALI_SUCCESS;
}

static int mali_adp_suspend(struct device *device)
{
    int ret = 0;

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->suspend))
    {
        ret = device->driver->pm->suspend(device);
    }

    if(0 == ret)
    {
        mali_adp_power_mode_change(device, MALI_POWER_MODE_DEEP_SLEEP, MALI_FALSE);
    }

    return ret;
}

static int mali_adp_resume(struct device *device)
{
    int ret = 0;

    mali_adp_power_mode_change(device, MALI_POWER_MODE_ON, MALI_FALSE);

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->resume))
    {
        ret = device->driver->pm->resume(device);
    }

    return ret;
}

static int mali_adp_freeze(struct device *device)
{
    int ret = 0;

    mali_adp_power_mode_change(device, MALI_POWER_MODE_ON, MALI_FALSE);

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->freeze))
    {
        ret = device->driver->pm->freeze(device);
    }

    if(0 == ret)
    {
        mali_adp_power_mode_change(device, MALI_POWER_MODE_DEEP_SLEEP, MALI_FALSE);
    }

    return ret;
}

static int mali_adp_thaw(struct device *device)
{
    int ret = 0;

    mali_adp_power_mode_change(device, MALI_POWER_MODE_ON, MALI_FALSE);

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->thaw))
    {
        ret = device->driver->pm->thaw(device);
    }

    return ret;
}

#ifdef CONFIG_PM_RUNTIME
static int mali_adp_runtime_suspend(struct device *device)
{
    int ret = 0;

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->runtime_suspend))
    {
        ret = device->driver->pm->runtime_suspend(device);
    }

    if(0 == ret)
    {
        mali_adp_power_mode_change(device, MALI_POWER_MODE_LIGHT_SLEEP, MALI_TRUE);
    }

    return ret;
}

static int mali_adp_runtime_resume(struct device *device)
{
    int ret = 0;

    mali_adp_power_mode_change(device, MALI_POWER_MODE_ON, MALI_TRUE);

    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->runtime_resume))
    {
        ret = device->driver->pm->runtime_resume(device);
    }

    return ret;
}

static int mali_adp_runtime_idle(struct device *device)
{
    if ((NULL != device->driver)
        && (NULL != device->driver->pm)
        && (NULL != device->driver->pm->runtime_idle))
    {
        int ret = device->driver->pm->runtime_idle(device);
        if (0 != ret)
        {
            return ret;
        }
    }

    pm_runtime_suspend(device);

    return 0;
}

#endif

void mali_adp_secure_reset_request(void)
{
#ifdef GPU_SECURE_SUPPORT
	int value ;

    mali_hw_core_register_write(s_SecCore, SEC_REG_OFFSET_IDLES_COUNT, 0x1ff);

    value = mali_hw_core_register_read(s_SecCore, SEC_REG_OFFSET_SWITCH);
    value = value | 0x1;

    mali_hw_core_register_write(s_SecCore, SEC_REG_OFFSET_SWITCH, value);

    value = 0 ;
    while(!value)
    {
        value = mali_hw_core_register_read(s_SecCore, SEC_REG_OFFSET_STATUS);
    }
#endif
}

void mali_adp_secure_reset_cancel(void)
{
#ifdef GPU_SECURE_SUPPORT
	int value ;

    mali_hw_core_register_write(s_SecCore, SEC_REG_OFFSET_IDLES_COUNT, 0x1ff);

    value = mali_hw_core_register_read(s_SecCore, SEC_REG_OFFSET_SWITCH);
    value = value & 0xfffffffe;

    mali_hw_core_register_write(s_SecCore, SEC_REG_OFFSET_SWITCH, value);

    value = 0 ;
    while(!value)
    {
        value = mali_hw_core_register_read(s_SecCore, SEC_REG_OFFSET_STATUS);
    }
#endif
}

int mali_adp_secure_init(void)
{
    mali_adp_secure_reset_cancel() ;

    return 0 ;
}

void mali_adp_secure_deinit(void)
{
    mali_adp_secure_reset_cancel() ;

    return;
}

int mali_adp_secure_enable(void)
{
	mali_adp_secure_reset_request() ;

	return 0 ;
}

int mali_adp_secure_disable(void)
{
	mali_adp_secure_reset_cancel() ;

	return 0 ;
}

struct device * mali_adp_get_device(void)
{
    return s_MaliDevice;
}

int mali_adp_get_powerstatus(void)
{
    return s_PowerOff;
}

int mali_adp_get_dvfsstatus(void)
{
    return mali_dvfs_enable;
}

unsigned int mali_adp_get_temp_ctrl(void)
{
    /* 1: disable dvfs, configure min frequency
       0: enable dvfs */

#ifdef CFG_TEMP_CTRL_CONFIG
    unsigned int value = mali_hw_core_register_read(s_TempCore, 0);

    if(value == TEMP_REG_VALUE_CONCTRL)
    {
        if(HISI_DEBUG)
            printk("mali_adp_get_temp_ctrl@ disable dvfs\n");

        return 1;
    }
#endif

    return 0;
}

void* mali_adp_get_configuration(struct mali_device *mdev)
{
    if(mali_dvfs_max_frequency == 0)
    {
        mali_dvfs_max_frequency = (unsigned int)opps_get_max_freq()/1000;
    }

    if(mali_dvfs_min_frequency == 0)
    {
        mali_dvfs_min_frequency = (unsigned int)opps_get_min_freq()/1000;
    }

    if(mali_dvfs_max_utilization == 0)
    {
        mali_dvfs_max_utilization = opps_get_max_utilization();
    }

    if(mali_dvfs_min_utilization == 0)
    {
        mali_dvfs_min_utilization = opps_get_min_utilization();
    }

    s_MaliConfiguration.dvfs_enable = mali_dvfs_enable;
    s_MaliConfiguration.max_frequency = mali_dvfs_max_frequency * 1000;
    s_MaliConfiguration.min_frequency = mali_dvfs_min_frequency * 1000;
    s_MaliConfiguration.max_utilization = mali_dvfs_max_utilization;
    s_MaliConfiguration.min_utilization = mali_dvfs_min_utilization;

    s_MaliConfiguration.time_busy_gp = mdev->mali_metrics.time_busy_gp;
    s_MaliConfiguration.time_idle_gp = mdev->mali_metrics.time_idle_gp;
    s_MaliConfiguration.time_busy_pp = mdev->mali_metrics.time_busy_pp[0];
    s_MaliConfiguration.time_idle_pp = mdev->mali_metrics.time_idle_pp[0];

    s_MaliConfiguration.temp_ctrl = mali_adp_get_temp_ctrl();

    return (void*)(&s_MaliConfiguration);
}

int mali_ext_set_freq_and_volt(int freq, int volt, int dvfs_enable)
{
    struct mali_device *mdev = dev_get_drvdata(mali_adp_get_device());

    mali_dvfs_enable = dvfs_enable;

    mdelay(1000);

    if((freq == 0) && (volt == 0))
    {
        HISI_ERROR_INFO();
    }
    else if(freq == 0)
    {
        regulator_set_voltage(mdev->regulator, volt*1000, volt*1000);
    }
    else if(volt == 0)
    {
        clk_set_rate(mdev->clock, freq*1000);
    }
    else
    {
        regulator_set_voltage(mdev->regulator, volt*1000, volt*1000);
        clk_set_rate(mdev->clock, freq*1000);
    }

    return 0;
}

int mali_ext_set_max_freq(int freq)
{
    mali_dvfs_max_frequency = freq;

    return 0;
}


