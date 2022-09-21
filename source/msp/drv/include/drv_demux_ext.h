/******************************************************************************
 Copyright (C), 2009-2014, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : drv_demux_ext.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       : 2012/08/24
 Description   :
******************************************************************************/

#ifndef __DRV_DEMUX_EXT_H__
#define __DRV_DEMUX_EXT_H__

#include "hi_type.h"
#include "hi_drv_dev.h"
#include "hi_drv_demux.h"
#include "hi_drv_descrambler.h"

/*
 * export to other module.
 */
typedef HI_S32  (*FN_DEMUX_GetCapability)(HI_UNF_DMX_CAPABILITY_S *Cap);
typedef HI_S32  (*FN_DEMUX_GetTunerPortPktCnt)(const HI_U32 DvbPortId, HI_U32 *TsPktCnt, HI_U32 *ErrPktCnt);

typedef HI_S32  (*FN_DEMUX_AcquireEs)(HI_HANDLE, DMX_Stream_S*);
typedef HI_S32  (*FN_DEMUX_ReleaseEs)(HI_HANDLE, DMX_Stream_S*);
typedef HI_S32  (*FN_DEMUX_Suspend)(PM_BASEDEV_S *himd, pm_message_t state);
typedef HI_S32  (*FN_DEMUX_Resume)(PM_BASEDEV_S *himd);

typedef HI_S32  (*FN_DEMUX_SetDescramblerKey)(HI_HANDLE KeyHandle, DMX_KEY_TYPE_E enKeyType, HI_U8 *pu8Key, HI_U32 u32KeyLen);
typedef HI_S32  (*FN_DEMUX_SetDescramblerIV)(HI_HANDLE KeyHandle, DMX_KEY_TYPE_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen);


typedef struct
{
    FN_DEMUX_GetCapability      pfnDmxGetCapability;
    FN_DEMUX_GetTunerPortPktCnt pfnDmxGetTunerPortPktCnt;

    FN_DEMUX_AcquireEs          pfnDmxAcquireEs;
    FN_DEMUX_ReleaseEs          pfnDmxReleaseEs;
    FN_DEMUX_Suspend            pfnDmxSuspend;
    FN_DEMUX_Resume             pfnDmxResume;
    FN_DEMUX_SetDescramblerKey  pfnDmxSetDescramblerKey;
    FN_DEMUX_SetDescramblerIV   pfnDmxSetDescramblerIV;
} DEMUX_EXPORT_FUNC_S;

HI_S32  DMX_DRV_ModInit(HI_VOID);
HI_VOID DMX_DRV_ModExit(HI_VOID);

#endif

