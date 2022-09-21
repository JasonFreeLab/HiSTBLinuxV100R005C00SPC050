#ifndef __DRV_ADSP_PRIVATE_H__
#define __DRV_ADSP_PRIVATE_H__

#include "hi_type.h"
#include "hi_module.h"
#include "hi_drv_sys.h"
#include "hi_drv_dev.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"
#include "hi_drv_proc.h"
#include "hi_drv_stat.h"
#include "hi_drv_module.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HI_FATAL_ADSP(fmt...) \
    HI_FATAL_PRINT(HI_ID_ADSP, fmt)

#define HI_ERR_ADSP(fmt...) \
    HI_ERR_PRINT(HI_ID_ADSP, fmt)

#define HI_WARN_ADSP(fmt...) \
    HI_WARN_PRINT(HI_ID_ADSP, fmt)

#define HI_INFO_ADSP(fmt...) \
    HI_INFO_PRINT(HI_ID_ADSP, fmt)

#if (1 == HI_PROC_SUPPORT)
typedef struct tagADSP_REGISTER_PARAM_S
{
    DRV_PROC_READ_FN  pfnReadProc;
    DRV_PROC_WRITE_FN pfnWriteProc;
} ADSP_REGISTER_PARAM_S;
#endif

HI_S32  ADSP_DRV_Init(HI_VOID);
HI_VOID ADSP_DRV_Exit(HI_VOID);
HI_S32  ADSP_DRV_Suspend(PM_BASEDEV_S* pdev, pm_message_t state);
HI_S32  ADSP_DRV_Resume(PM_BASEDEV_S* pdev);

#if (1 == HI_PROC_SUPPORT)
HI_S32  ADSP_DRV_ReadProc(struct seq_file* p, HI_VOID* v);
HI_S32  ADSP_DRV_WriteProc(struct file* file, const char __user* buf, size_t count, loff_t* ppos);

HI_S32  ADSP_DRV_RegisterProc(ADSP_REGISTER_PARAM_S* pstParam);
HI_VOID ADSP_DRV_UnregisterProc(HI_VOID);

HI_VOID ADSP_ProcDeInit(HI_VOID);
HI_S32  ADSP_ProcInit(HI_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_ADSP_PRIVATE_H__ */
