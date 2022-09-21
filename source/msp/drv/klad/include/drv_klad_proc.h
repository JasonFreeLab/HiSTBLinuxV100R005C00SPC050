/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_proc.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_KLAD_PROC_H__
#define __DRV_KLAD_PROC_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


HI_S32 DRV_KLAD_ProcWrite(struct file* file, const char __user* buf, size_t count, loff_t* ppos);
HI_S32 DRV_KLAD_ProcRead(struct seq_file* p, HI_VOID* v);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_KLAD_PROC_H__ */

