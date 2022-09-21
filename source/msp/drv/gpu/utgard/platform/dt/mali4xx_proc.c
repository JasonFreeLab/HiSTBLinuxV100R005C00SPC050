#ifdef GPU_PROC_SUPPORT

#include <linux/clkdev.h>
#include <asm/clkdev.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#ifdef CONFIG_PROC_FS
 #include <linux/proc_fs.h>
#endif
#include <linux/seq_file.h>

#include <linux/regulator/driver.h>
#include <linux/clk.h>

#include "mali_kernel_common.h"
#include "mali_osk_mali.h"
#include "mali_pm_metrics.h"

#include "hi_drv_proc.h"
#include "hi_osal.h"

#include "mali4xx_scaling.h"
#include "mali4xx_dt.h"

#define GPU_CMD_MAX_NUM (2)
#define GPU_CMD_MAX_CMD_LEN (32)
#define GPU_CMD_MAX_VLAUE_LEN (32)
#define GPU_CMD_ON "on"
#define GPU_CMD_OFF "off"
#define GPU_CMD_VOLT "volt"
#define GPU_CMD_FREQ "freq"
#define GPU_CMD_HELP "help"
#define GPU_CMD_WAKEUPRESET "reset"
#define GPU_CMD_DEBUG "debug"
#define GPU_CMD_ENTERSMARTSTANDBY "entersmart"
#define GPU_CMD_QUITSMARTSTANDBY "quitsmart"

typedef struct tagGPU_CMD_DATA_S
{
    HI_U8 aszCmd[GPU_CMD_MAX_CMD_LEN];
    HI_U8 aszValue[GPU_CMD_MAX_VLAUE_LEN];
} GPU_CMD_DATA_S;

static GPU_CMD_DATA_S g_astGPUProcCmd[GPU_CMD_MAX_NUM];

unsigned int mali_proc_get_gp_utilization(void)
{
    struct mali_device *mdev = dev_get_drvdata(mali_adp_get_device());
    struct mali_config *mali_valuable;
    unsigned int busy = 0, total = 0;

    mali_valuable = (struct mali_config*)mdev->devfreq->last_status.private_data;

    if(mali_valuable == NULL)
    {
        return 0;
    }

    busy = (unsigned int)(mali_valuable->time_busy_gp) >> 10;

    total = (unsigned int)(mali_valuable->time_busy_gp + mali_valuable->time_idle_gp) >> 10;

    return 100 * busy / (total + 1);
}

unsigned int mali_proc_get_pp_utilization(void)
{
    struct mali_device *mdev = dev_get_drvdata(mali_adp_get_device());
    struct mali_config *mali_valuable;
    unsigned int busy = 0, total = 0;

    mali_valuable = (struct mali_config*)mdev->devfreq->last_status.private_data;

    if(mali_valuable == NULL)
    {
        return 0;
    }

    busy = (unsigned int)(mali_valuable->time_busy_pp) >> 10;

    total = (unsigned int)(mali_valuable->time_busy_pp + mali_valuable->time_idle_pp) >> 10;

    return 100 * busy / (total + 1);
}

HI_U32 GPUParseValue(HI_U8* pu8Value)
{
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

HI_S32 GPUParseCmd(HI_U8* pu8Cmd, HI_U32 u32Len, GPU_CMD_DATA_S** pstCmd, HI_U32* pu32Num)
{
    HI_U32 u32Pos = 0;
    HI_U32 u32SavePos = 0;
    HI_U32 u32CmdNum = 0;
    HI_BOOL bIsCmd   = HI_TRUE;
    HI_U8 u8LastChar = ' ';

    if ((HI_NULL == pu8Cmd) || (0 == u32Len) || (HI_NULL == pstCmd) || (HI_NULL == pu32Num))
    {
        MALI_PRINT_ERROR(("Invalid.\n"));
        return HI_FAILURE;
    }

    u32CmdNum = 0;
    memset(g_astGPUProcCmd, 0, sizeof(g_astGPUProcCmd));

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
                    if (u32CmdNum < GPU_CMD_MAX_NUM - 1)
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
                if (u32SavePos < GPU_CMD_MAX_CMD_LEN)
                {
                    g_astGPUProcCmd[u32CmdNum].aszCmd[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }
            else
            {
                if (u32SavePos < GPU_CMD_MAX_VLAUE_LEN)
                {
                    g_astGPUProcCmd[u32CmdNum].aszValue[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }

            break;
        }

        u8LastChar = pu8Cmd[u32Pos];
        u32Pos++;
    }

out:
    if (strlen(g_astGPUProcCmd[u32CmdNum].aszCmd) > 0)
    {
        u32CmdNum += 1;
    }

    *pstCmd  = g_astGPUProcCmd;
    *pu32Num = u32CmdNum;
    return HI_SUCCESS;
}

HI_S32 GPUDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    HI_U32 u32CpuCurFreq = 0;
    struct mali_device *mdev = dev_get_drvdata(mali_adp_get_device());

    MALI_DEBUG_PRINT(2, ("\n gpu freq = 0x%x, voltage = 0x%x \n", u32Para1, u32Para2));

    if ((0 == u32Para1) && (0 == u32Para2))
    {
        MALI_PRINT_ERROR(("plese set the valid value \n"));
        return HI_SUCCESS;
    }

    if (0 == u32Para2)
    {
        clk_set_rate(mdev->clock, u32Para1*1000);
        mdev->current_freq = u32Para1*1000;

        return HI_SUCCESS;
    }

    if (0 == u32Para1)
    {
        regulator_set_voltage(mdev->regulator, u32Para2*1000, u32Para2*1000);
        mdev->current_voltage = u32Para2*1000;

        return HI_SUCCESS;
    }

    u32CpuCurFreq = (HI_U32)clk_get_rate(mdev->clock);
    if (u32Para1 > u32CpuCurFreq)
    {
        regulator_set_voltage(mdev->regulator, u32Para2*1000, u32Para2*1000);
        clk_set_rate(mdev->clock, u32Para1*1000);
    }
    else
    {
        clk_set_rate(mdev->clock, u32Para1*1000);
        regulator_set_voltage(mdev->regulator, u32Para2*1000, u32Para2*1000);
    }

    mdev->current_voltage = u32Para2*1000;
    mdev->current_freq = u32Para1*1000;

    return HI_SUCCESS;
}

static HI_S32 GPUProcRead(struct seq_file *p, HI_VOID *v)
{
    struct mali_device *mdev = dev_get_drvdata(mali_adp_get_device());

    PROC_PRINT(p,     "---------Hisilicon GPU Info---------\n");
    PROC_PRINT(p,     "Frequency                :%d(kHz)\n",(HI_U32)clk_get_rate(mdev->clock)/1000);
    PROC_PRINT(p,     "Voltage                  :%d(mv)\n",(HI_U32)regulator_get_voltage(mdev->regulator)/1000);
    PROC_PRINT(p,     "GP_utilization           :%d(percent)\n",mali_proc_get_gp_utilization());
    PROC_PRINT(p,     "PP_utilization           :%d(percent)\n",mali_proc_get_pp_utilization());

    if (1 == mali_adp_get_powerstatus())
    {
        PROC_PRINT(p, "Power_status             :power down\n");
    }
    else
    {
        PROC_PRINT(p, "Power_status             :power up\n");
    }

    PROC_PRINT(p,     "Shared_mem_size          :%d(MB)\n",CONFIG_GPU_MAX_SHARE_MEM_SIZE/1024/1024);

    if (1 == mali_adp_get_dvfsstatus())
    {
        PROC_PRINT(p, "DVFS_enable              :enable\n");
    }
    else
    {
        PROC_PRINT(p, "DVFS_enable              :disable\n");
    }

    return 0;
}

static HI_VOID GPUProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo volt=1080 > /proc/hisi/msp/pm_gpu, set gpu volt in mv.\n"
        "echo freq=432000 > /proc/hisi/msp/pm_gpu, set gpu freq in kHz.\n"
        "echo avs on/off > /proc/hisi/msp/pm_gpu, open/close gpu avs.\n"
        "echo freq=432000 volt=1080 > /proc/hisi/msp/pm_gpu, set gpu volt and freq simultaneity.\n"
    );

    return;
}

static HI_S32 GPUProcWrite(struct file * file,
                           const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {0};
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    GPU_CMD_DATA_S* pstCmd = HI_NULL;

    if(count > sizeof(ProcPara))
    {
        return -EFAULT;
    }

    if (copy_from_user(ProcPara, buf, count))
    {
        return -EFAULT;
    }

    s32Ret = GPUParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        goto err;
    }

    if (1 == u32CmdNum)
    {
        /* Only set GPU volt */
        if (0 == HI_OSAL_Strncasecmp(GPU_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            GPUDebugCtrl(0, GPUParseValue(pstCmd[0].aszValue));
        }
        /* Only set GPU freq */
        else if (0 == HI_OSAL_Strncasecmp(GPU_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            GPUDebugCtrl(GPUParseValue(pstCmd[0].aszValue), 0);
        }
        /* Help */
        else if (0 == HI_OSAL_Strncasecmp(GPU_CMD_HELP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            GPUProcHelper();
        }
        /* Support 0xXXX 0xXXX command */
        else /*if (('0' == pstCmd[0].aszCmd[0]) && ('0' == pstCmd[0].aszValue[0]))*/
        {
            GPUDebugCtrl(GPUParseValue(pstCmd[0].aszCmd), GPUParseValue(pstCmd[0].aszValue));
        }
    }
    else if (2 == u32CmdNum)
    {
        if ((0 == HI_OSAL_Strncasecmp(GPU_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
            && (0 == HI_OSAL_Strncasecmp(GPU_CMD_FREQ, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            GPUDebugCtrl(GPUParseValue(pstCmd[1].aszValue), GPUParseValue(pstCmd[0].aszValue));
        }
        else if ((0 == HI_OSAL_Strncasecmp(GPU_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
                 && (0 == HI_OSAL_Strncasecmp(GPU_CMD_VOLT, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            GPUDebugCtrl(GPUParseValue(pstCmd[0].aszValue), GPUParseValue(pstCmd[1].aszValue));
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
    GPUProcHelper();
    return count;
}

int gpu_proc_create(void)
{
    DRV_PROC_ITEM_S *item;

    item = HI_DRV_PROC_AddModule("pm_gpu", NULL, NULL);
    if (!item)
    {
        MALI_PRINT_ERROR(("add GPU proc module failed\n"));
        return -1;
    }

    item->read  = GPUProcRead;
    item->write = GPUProcWrite;
    return 0;
}

int gpu_proc_destroy(void)
{
    HI_DRV_PROC_RemoveModule("pm_gpu");
    return 0;
}

#endif
