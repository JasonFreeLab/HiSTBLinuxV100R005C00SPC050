/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name             :   hal_tianlai_adac.c
  Version               :   Initial Draft
  Author                :   Hisilicon multimedia software group
  Created               :   2010/02/28
  Last Modified         :
  Description           :   audio dac driver
  Function List         :
  History               :
  1.Date                :   2010/02/28
    Author              :
    Modification        :   Created file

******************************************************************************/

#include "hal_tianlai_adac.h"
#include "hal_tianlai_adac_v500.h"
#include "hal_tianlai_adac_v600.h"
#include "hal_tianlai_adac_v700.h"

#include "audio_util.h"

#if defined (CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)

#ifdef HI_SND_MUTECTL_SUPPORT
HI_VOID ADAC_TIANLAI_FastPowerEnable(HI_BOOL bEnable)
{
    if (HI_TRUE == AUTIL_IsChipMV300())
    {
        ADAC_TIANLAI_V700_FastPowerEnable(bEnable);
    }
    else
    {
        ADAC_TIANLAI_V600_FastPowerEnable(bEnable);
    }
}
#endif

HI_VOID ADAC_TIANLAI_Init(HI_U32 u32SampelRate, HI_BOOL bResume)
{
    if (HI_TRUE == AUTIL_IsChipMV300())
    {
        ADAC_TIANLAI_V700_Init(u32SampelRate, bResume);
    }
    else
    {
        ADAC_TIANLAI_V600_Init(u32SampelRate, bResume);
    }
}

HI_VOID ADAC_TIANLAI_DeInit(HI_BOOL bSuspend)
{
    if (HI_TRUE == AUTIL_IsChipMV300())
    {
        ADAC_TIANLAI_V700_DeInit(bSuspend);
    }
    else
    {
        ADAC_TIANLAI_V600_DeInit(bSuspend);
    }
}

#else

#ifdef HI_SND_MUTECTL_SUPPORT
HI_VOID ADAC_TIANLAI_FastPowerEnable(HI_BOOL bEnable)
{
#if defined (HI_TIANLAI_V500)
    ADAC_TIANLAI_V500_FastPowerEnable(bEnable);
#elif defined (HI_TIANLAI_V600)
    ADAC_TIANLAI_V600_FastPowerEnable(bEnable);
#elif defined (HI_TIANLAI_V700)
    ADAC_TIANLAI_V700_FastPowerEnable(bEnable);
#endif
}
#endif

HI_VOID ADAC_TIANLAI_Init(HI_U32 u32SampelRate, HI_BOOL bResume)
{
#if defined (HI_TIANLAI_V500)
    ADAC_TIANLAI_V500_Init(u32SampelRate, bResume);
#elif defined (HI_TIANLAI_V600)
    ADAC_TIANLAI_V600_Init(u32SampelRate, bResume);
#elif defined (HI_TIANLAI_V700)
    ADAC_TIANLAI_V700_Init(u32SampelRate, bResume);
#endif
}

HI_VOID ADAC_TIANLAI_DeInit(HI_BOOL bSuspend)
{
#if defined (HI_TIANLAI_V500)
    ADAC_TIANLAI_V500_DeInit(bSuspend);
#elif defined (HI_TIANLAI_V600)
    ADAC_TIANLAI_V600_DeInit(bSuspend);
#elif defined (HI_TIANLAI_V700)
    ADAC_TIANLAI_V700_DeInit(bSuspend);
#endif
}
#endif
