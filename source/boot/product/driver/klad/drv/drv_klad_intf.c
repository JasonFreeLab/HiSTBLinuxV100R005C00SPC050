/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_intf.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_klad.h"
#include "drv_klad.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "drv_klad_basic.h"
#ifdef HI_ADVCA_NAGRA_SUPPORT
#include "drv_klad_nagra.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


HI_S32 BOOT_KLAD_Ioctl(HI_U32 cmd, HI_VOID *argp)
{
    return DRV_KLAD_Ioctl(cmd, argp);
}


/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode init.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_S32 KLAD_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("klad module init error\n");
        KLAD_FUNC_EXIT();
        goto err0;
    }

#ifdef HI_ADVCA_NAGRA_SUPPORT
    ret = DRV_KLAD_NAGRA_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_NAGRA_Init failed\n");
        KLAD_FUNC_EXIT();
        goto err0;
    }
#endif

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;

err0:
#ifdef HI_ADVCA_NAGRA_SUPPORT
    DRV_KLAD_NAGRA_Exit();
#endif
    DRV_KLAD_Exit();
    KLAD_FUNC_EXIT();
    return HI_FAILURE;
}

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode exit.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_VOID KLAD_ModExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_Exit failed\n");
    }

#ifdef HI_ADVCA_NAGRA_SUPPORT
    ret = DRV_KLAD_NAGRA_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_NAGRA_Exit failed\n");
    }
#endif

    DRV_KLAD_Exit();
    KLAD_FUNC_EXIT();
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
