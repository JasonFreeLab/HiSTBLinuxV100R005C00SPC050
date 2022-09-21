/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCal.h
 * 
 * AUTHOR             : Jun Huang
 *                      Richard Liu
 *                      Jun Huang
 *
 * DATE CREATED       : 10/15/2010
 *                      12/29/2010
 *                      06/18/2011
 *
 * DESCRIPTION        : This file contains header file for calibration
 *
 ****************************************************************************************
 *                Copyright (c) 2006, MaxLinear, Inc.
 ****************************************************************************************/

#ifndef __MXL251SF_PHY_CAL_H__
#define __MXL251SF_PHY_CAL_H__

/*****************************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
*****************************************************************************************/
#include "MaxLinearDataTypes.h"
#include "MxL251SF_PhyCtrlApi.h"
#include "MxL251SF_PhyCfg.h"
#include "MxL251SF_OEM_Drv.h"
#include "MxL_Debug.h"

/*****************************************************************************************
    Macros
*****************************************************************************************/
#define MXL251_DIFF_GAIN_96_16_MHZ_MODES 8 

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/
void MxL251_PwrCalInit(void);
void MxL251_PwrCoefInit(PMXL251SF_DEV_CONTEXT_T devContextPtr);
MXL_STATUS MxL251_PwrLoadCoef(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT8* BufPtr, UINT32 BufLen);
MXL_STATUS MxL251_ConfigTunerCreatePwrCalCoef(PMXL_RX_PWR_CAL_T pwrCreateCalPtr);
MXL_STATUS Mxl251_ConfigTunerCalDone(PMXL_RX_PWR_CAL_COEF_INFO_T tunerCalDonePtr);
#ifdef _MXL251_FIXEDPOINT_
MXL_STATUS MxL251_PwrMeasureRxPower(UINT8 i2cAddr, UINT8 chanId, SINT32* rxPwrIndBmVPtr, POWER_CAL_COMP_E bComp, MXL_BOOL powerMonEnabled);
MXL_STATUS MxL251_CalOobRxPower(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, SINT32 rxPwrIndBmV, SINT32* pwrIndBmVPtr);
#else
MXL_STATUS MxL251_PwrMeasureRxPower(UINT8 i2cAddr, UINT8 chanId, REAL32* rxPwrIndBmVPtr, POWER_CAL_COMP_E bComp, MXL_BOOL powerMonEnabled);
MXL_STATUS MxL251_CalOobRxPower(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, REAL32 rxPwrIndBmV, REAL32* pwrIndBmVPtr);
#endif
MXL_STATUS MxL251_GetDeviceVersionInfo(PMXL_DEV_VERSION_INFO_T devInfoPtr);
MXL_STATUS MxL251_GetDSCALInfo(PMXL_GET_DSCAL_INFO_T cmdPtr);
MXL_STATUS MxL251_Ctrl_ConfigTunerCalCutOffFreq(PMXL_TUNER_CAL_SET_CUTOFF_FREQ_CFG_T cmdPtr);

#endif /* __MXL251SF_PHY_CAL_H__*/

