/*******************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: drv_aiao_intf.c
 * Description: aiao interface of module.
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main\1
 ********************************************************************************/

/***************************** included files ******************************/
#include "hi_type.h"
#include "hi_drv_struct.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_module.h"
#include "hi_drv_module.h"

#include "hi_drv_ai.h"
#include "hi_drv_ao.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifdef HI_AUDIO_AI_SUPPORT
extern HI_S32 AI_DRV_ModInit(HI_VOID);
extern HI_S32 AI_DRV_ModExit(HI_VOID);
#endif

#ifdef HI_ALSA_AO_SUPPORT
extern int AO_ALSA_ModInit(void);
extern void  AO_ALSA_ModExit(void);
#endif

extern HI_S32 AO_DRV_ModInit(HI_VOID);
extern HI_S32 AO_DRV_ModExit(HI_VOID);

#ifdef HI_AIAO_TIMER_SUPPORT
extern HI_S32  Timer_DRV_Init(HI_VOID);
extern HI_VOID Timer_DRV_DeInit(HI_VOID);
#endif

/*****************************************************************************
 Prototype    : AIAO_DRV_ModInit
 Description  : initialize function in AIAO module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
HI_S32 AIAO_DRV_ModInit(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_AIAO, "HI_AIAO", HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_AO("HI_DRV_MODULE_Register HI_ID_AIAO Fail\n");
        return s32Ret;
    }

#ifdef HI_AUDIO_AI_SUPPORT
    s32Ret = AI_DRV_ModInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MODULE_UnRegister(HI_ID_AIAO);
        HI_FATAL_AO("AI_DRV_ModInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
#endif

    s32Ret = AO_DRV_ModInit();
    if (HI_SUCCESS != s32Ret)
    {
#ifdef HI_AUDIO_AI_SUPPORT
        AI_DRV_ModExit();
#endif
        HI_DRV_MODULE_UnRegister(HI_ID_AIAO);
        HI_FATAL_AO("AO_DRV_ModInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

#ifdef HI_AIAO_TIMER_SUPPORT
    s32Ret = Timer_DRV_Init();
    if (HI_SUCCESS != s32Ret)
    {
        AO_DRV_ModExit();
#ifdef HI_AUDIO_AI_SUPPORT
        AI_DRV_ModExit();
#endif
        HI_DRV_MODULE_UnRegister(HI_ID_AIAO);
        HI_FATAL_AO("Timer_DRV_Init failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
#endif

#ifdef HI_ALSA_AO_SUPPORT
    s32Ret = AO_ALSA_ModInit();
    if (HI_SUCCESS != s32Ret)
    {
#ifdef HI_AIAO_TIMER_SUPPORT
        Timer_DRV_DeInit();
#endif
        AO_DRV_ModExit();
#ifdef HI_AUDIO_AI_SUPPORT
        AI_DRV_ModExit();
#endif
        HI_DRV_MODULE_UnRegister(HI_ID_AIAO);
        HI_FATAL_AO("AO_ALSA_ModInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
#endif

#ifdef MODULE
    HI_PRINT("Load hi_aiao.ko success.  \t(%s)\n", VERSION_STRING);
#endif

    return s32Ret;
}

/*****************************************************************************
 Prototype    : AIAO_DRV_ModExit
 Description  : exit function in AIAO module
 Input        : None
 Output       : None
 Return Value :
*****************************************************************************/
HI_VOID AIAO_DRV_ModExit(HI_VOID)
{

#ifdef HI_ALSA_AO_SUPPORT
    AO_ALSA_ModExit();
#endif

#ifdef HI_AIAO_TIMER_SUPPORT
    Timer_DRV_DeInit();
#endif

#ifdef HI_AUDIO_AI_SUPPORT
    AI_DRV_ModExit();
#endif

    AO_DRV_ModExit();

    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_AIAO);

    HI_INFO_AO(" **** AIAO_DRV_ModExit OK  **** \n");
}

#ifdef MODULE
module_init(AIAO_DRV_ModInit);
module_exit(AIAO_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
