/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : vdp_energy_saving.c
  Version       : Initial Draft
  Author        : w00284030
  Created       : 2017/6/5
  Last Modified :
  Description   : Energy saving moudle
  Function List :
  History       :
******************************************************************************/

#include "vdp_define.h"
#include "vdp_ip_define.h"
#include "drv_disp_osal.h"
#include "drv_disp_priv.h"
#include "drv_win_hal.h"
#include "drv_win_wbc.h"
#include "drv_display.h"
#include "drv_window.h"
#include "drv_disp_hal.h"
#include "drv_async.h"
#include "drv_low_power.h"


static HI_BOOL bLowPowerInit = HI_FALSE;
static HI_U32  g_u32LastLayerEnStatus = 0;


#define LowPower_CheckInit()\
{                           \
    if (!bLowPowerInit)     \
    {                       \
        return HI_FAILURE;  \
    }                       \
}

/*****************************************************************************
 Prototype    : LowPower_AddMsg
 Description  : Add a regtister operation msg to async queue
 Input        : eRegister   - Regtister
                bEnable     - Whether enable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_AddMsg(REG_NAME_E eRegister, HI_BOOL bEnable)
{
    ASYNC_MSG_S *msg    = HI_NULL;
    HI_U32 u32CycleTime = 0;
    HI_U32 u32LeftTime  = 0;

    if (!(msg = VDP_ASYNC_GetMsgPointer(0)))
    {
        return HI_FAILURE;
    }

    /* Use DISP1 cycle time */
    if (DISP_GetVbiTimeInfo(HI_DRV_DISPLAY_1, &u32CycleTime, &u32LeftTime))
    {
        return HI_FAILURE;
    }

    msg->ulExpectedTime = VDP_ASYNC_GenExpectTime(u32CycleTime);
    msg->enAsyncType = ASYNC_MSG_TYPE_LOWPOWER;
    msg->unMsgItem.AsyncMsgEnergysaving.enRegName = eRegister;
    msg->unMsgItem.AsyncMsgEnergysaving.bRegStatus = bEnable;
    if (HI_SUCCESS != VDP_ASYNC_PushMsg(msg, ENERGY_SAVING_QUEUE_IDX))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_DelMsg
 Description  : Delete all regtister operation msg which matched in the queue
 Input        : reg_name    - Regtister name
                bEnable     - Whether enable
 Output       : None
 Return Value : None
*****************************************************************************/
static HI_VOID LowPower_DelMsg(REG_NAME_E reg_name, HI_BOOL bEnable)
{
    ASYNC_MSG_S msg;

    msg.enAsyncType = ASYNC_MSG_TYPE_LOWPOWER;
    msg.unMsgItem.AsyncMsgEnergysaving.enRegName = reg_name;
    msg.unMsgItem.AsyncMsgEnergysaving.bRegStatus = bEnable;
    VDP_ASYNC_DelMsg(&msg, ENERGY_SAVING_QUEUE_IDX);

    return;
}

/*****************************************************************************
 Prototype    : LowPower_SetLayerClockEn
 Description  : Enable V1 or V3 layer clock gate, other layer not supported
 Input        : enLayer     - Layer index
                bEnable     - Enable or disable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_SetLayerClockEn(VDP_LAYER_VID_E enLayer, HI_BOOL bEnable)
{
    HI_S32 u32Ret                = 0;
    DISP_INTF_OPERATION_S* pfOpt = HI_NULL;

    pfOpt = DISP_HAL_GetOperationPtr();
    DispCheckNullPointer(pfOpt);
    u32Ret = pfOpt->PF_SetLayerClockEnable(enLayer, bEnable);

    return u32Ret;
}

/*****************************************************************************
 Prototype    : LowPower_OpenLayerClock
 Description  : Open layer clock and delete clock-close msg form queue
 Input        : enLayer     - Layer index
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_OpenLayerClock(VDP_LAYER_VID_E enLayer)
{
    HI_S32 s32Ret = 0;

    switch (enLayer)
    {
        case VDP_LAYER_VID0 :
            LowPower_DelMsg(REG_V0_LAYER_CLOCK_GATE, HI_FALSE);
            s32Ret = LowPower_SetLayerClockEn(VDP_LAYER_VID0, HI_TRUE);
            break;
        case VDP_LAYER_VID1 :
            LowPower_DelMsg(REG_V1_LAYER_CLOCK_GATE, HI_FALSE);
            s32Ret = LowPower_SetLayerClockEn(VDP_LAYER_VID1, HI_TRUE);
            break;
        case VDP_LAYER_VID3 :
            LowPower_DelMsg(REG_V3_LAYER_CLOCK_GATE, HI_FALSE);
            s32Ret = LowPower_SetLayerClockEn(VDP_LAYER_VID3, HI_TRUE);
            break;
        default:
            s32Ret = HI_SUCCESS;
    }

    return s32Ret;
}


/*****************************************************************************
 Prototype    : LowPower_AddLayerClockCloseMsg
 Description  : Add layer clock close message to low power async queue
 Input        : enLayer     - Layer index
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_AddLayerClockCloseMsg(VDP_LAYER_VID_E enLayer)
{
    HI_S32 s32Ret = 0;

    switch (enLayer)
    {
        case VDP_LAYER_VID0 :
            s32Ret = LowPower_AddMsg(REG_V0_LAYER_CLOCK_GATE, HI_FALSE);
            break;
        case VDP_LAYER_VID1 :
            s32Ret = LowPower_AddMsg(REG_V1_LAYER_CLOCK_GATE, HI_FALSE);
            break;
        case VDP_LAYER_VID3 :
            s32Ret = LowPower_AddMsg(REG_V3_LAYER_CLOCK_GATE, HI_FALSE);
            break;
        default:
            s32Ret = HI_SUCCESS;
    }

    return s32Ret;
}

/*****************************************************************************
 Prototype    : LowPower_SetVpWbcClockEn
 Description  : Enable VP WBC clock gate
 Input        : bEnable     - Enable or disable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_SetVpWbcClockEn(HI_BOOL bEnable)
{
    DISP_INTF_OPERATION_S* pfOpt = DISP_HAL_GetOperationPtr();

    DispCheckNullPointer(pfOpt);
    pfOpt->PF_SetVpWbcClockEnable(bEnable);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_SetDhdWbcClockEn
 Description  : Enable DHD WBC clock gate
 Input        : bEnable     - Enable or disable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_SetDhdWbcClockEn(HI_BOOL bEnable)
{
    DISP_INTF_OPERATION_S* pfOpt = DISP_HAL_GetOperationPtr();

    DispCheckNullPointer(pfOpt);
    pfOpt->PF_SetDhdWbcClockEnable(bEnable);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_SetVdacVbgEn
 Description  : Enable VDAC Vbg
 Input        : bEnable     - Enable or disable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_SetVdacVbgEn(HI_BOOL bEnable)
{
    DISP_INTF_OPERATION_S* pfOpt = DISP_HAL_GetOperationPtr();

    DispCheckNullPointer(pfOpt);
    pfOpt->PF_SetVdacVbgEnable(bEnable);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_Callback
 Description  : Definition of energy-saving module callback
 Input        : ASYNC_MSG_S *async_msg
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_Callback(const ASYNC_MSG_S *pAsyncMsg)
{
    ASYNC_MSG_ENERGYSAVING_S msg;

    if (ASYNC_MSG_TYPE_LOWPOWER != pAsyncMsg->enAsyncType)
    {
        return HI_FAILURE;
    }

    msg = pAsyncMsg->unMsgItem.AsyncMsgEnergysaving;

    /* Operate register recorded in msg */
    switch (msg.enRegName)
    {
        case REG_V0_LAYER_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID0, msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        case REG_V1_LAYER_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID1, msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        case REG_V3_LAYER_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID3, msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        case REG_VP_WBC_VIDEO_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetVpWbcClockEn(msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        case REG_DHD_WBC_VIDEO_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetDhdWbcClockEn(msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        case REG_VBG_VIDEO_CLOCK_GATE :
            if (HI_SUCCESS != LowPower_SetVdacVbgEn(msg.bRegStatus))
            {
                return HI_FAILURE;
            }
            break;

        default:;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_NoticeGraphIsogenyEn
 Description  : Notice graph isogeny status
 Input        : bEnable - enable or disable
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
static HI_S32 LowPower_NoticeGraphIsogenyEn(HI_BOOL bEnable)
{
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_CloseLayerWhenQuit
 Description  : Close all clock when exe closed
 Input        : None
 Output       : None
 Return Value : 0-success; others-error codes
*****************************************************************************/
static HI_S32 LowPower_CloseLayerWhenQuit(HI_VOID)
{
    /* Disable all layer clock */
    if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID0, HI_FALSE))
    {
        return HI_FAILURE;
    }
    if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID1, HI_FALSE))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 LowPower_Init(HI_VOID)
{
    if (bLowPowerInit)
    {
        return HI_SUCCESS;
    }

    /* Init async moudle */
    VDP_ASYNC_Init();

    if (HI_SUCCESS != VDP_ASYNC_RegCallback(ASYNC_MSG_TYPE_LOWPOWER, &LowPower_Callback))
    {
        return HI_FAILURE;
    }

    if (HI_SUCCESS != VDP_ASYNC_ResetMsgQueue(ENERGY_SAVING_QUEUE_IDX))
    {
        return HI_FAILURE;
    }

    bLowPowerInit = HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 LowPower_DeInit(HI_VOID)
{
    /* Close all clock related to low power */
    if (HI_SUCCESS != LowPower_CloseLayerWhenQuit())
    {
        return HI_FAILURE;
    }

    /* Destroy low power message queue */
    if (HI_SUCCESS != VDP_ASYNC_DestroyMsgQueue(ENERGY_SAVING_QUEUE_IDX))
    {
        return HI_FAILURE;
    }

    g_u32LastLayerEnStatus = 0;
    bLowPowerInit = HI_FALSE;

    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype    : LowPower_OpenIsogeny
 Description  : Standard defination channel open
 Input        : None
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
HI_S32 LowPower_OpenIsogeny(HI_VOID)
{
    LowPower_CheckInit();

    /* Open video WBC clock gate */
    LowPower_DelMsg(REG_VP_WBC_VIDEO_CLOCK_GATE, HI_FALSE);
    if (HI_SUCCESS != LowPower_SetVpWbcClockEn(HI_TRUE))
    {
        return HI_FAILURE;
    }

    /* Open VBG */
    LowPower_DelMsg(REG_VBG_VIDEO_CLOCK_GATE, HI_FALSE);
    if (HI_SUCCESS != LowPower_SetVdacVbgEn(HI_TRUE))
    {
        return HI_FAILURE;
    }

    /* Open V3 clock gate */
    LowPower_DelMsg(REG_V3_LAYER_CLOCK_GATE, HI_FALSE);
    if (HI_SUCCESS != LowPower_SetLayerClockEn(VDP_LAYER_VID3, HI_TRUE))
    {
        return HI_FAILURE;
    }


    /* Enable G4 */
    if (HI_SUCCESS != LowPower_NoticeGraphIsogenyEn(HI_TRUE))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype    : LowPower_CloseIsogeny
 Description  : Standard defination channel close.
                Disable channel by order :* DAV -> DHD1 -> G4 -> V3 -> WBC_DHD&WBC_VP.
                Clock gate disable is as the same order.
 Input        : None
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
HI_S32 LowPower_CloseIsogeny(HI_VOID)
{
    LowPower_CheckInit();

    /* Disable G4 */
    if (HI_SUCCESS != LowPower_NoticeGraphIsogenyEn(HI_FALSE))
    {
        return HI_FAILURE;
    }

    /* V3 clock gate close msg */
    if (HI_SUCCESS != LowPower_AddMsg(REG_V3_LAYER_CLOCK_GATE, HI_FALSE))
    {
        return HI_FAILURE;
    }

    /* Video VPWBC clock gate close msg */
    if (HI_SUCCESS != LowPower_AddMsg(REG_VP_WBC_VIDEO_CLOCK_GATE, HI_FALSE))
    {
        return HI_FAILURE;
    }

    /* VBG close msg */
    if (HI_SUCCESS != LowPower_AddMsg(REG_VBG_VIDEO_CLOCK_GATE, HI_FALSE))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : LowPower_OperatePipLayer
 Description  : Change PIP layer open/close status
 Input        : None
 Output       : None
 Return Value : 0-success; others-error code
*****************************************************************************/
HI_S32 LowPower_OperatePipLayer(HI_U32 u32LayerEnRecorder)
{
    HI_S32          i = 0;
    HI_S32          s32Ret = 0;

    LowPower_CheckInit();

    /* No change Or no window , return without operation  */
    if (u32LayerEnRecorder == g_u32LastLayerEnStatus)
    {
        return HI_SUCCESS;
    }
    g_u32LastLayerEnStatus = u32LayerEnRecorder;

    /* Operate layer according PIP status, only V0/V1 at present */
    for (i=0; i<=VDP_LAYER_VID1; i++)
    {
        if (u32LayerEnRecorder & (1 << i))
        {
            s32Ret = LowPower_OpenLayerClock(i);
        }
        else
        {
            s32Ret = LowPower_AddLayerClockCloseMsg(i);
        }

        if (s32Ret)
        {
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}