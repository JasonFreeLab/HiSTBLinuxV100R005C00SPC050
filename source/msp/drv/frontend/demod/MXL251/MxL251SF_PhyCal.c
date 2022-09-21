/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCal.c
 *
 * AUTHOR             : Jun Huang
 *                      Richard Liu
 *                      Jun Huang
 *						Randhir Jha
 *						
 * DATE CREATED       : 10/15/2010
 *                      12/29/2010
 *                      06/18/2011
 *                      03/18/2013
 *
 * DESCRIPTION        : This file contains calibration routines like
 *                      Power Calibration for RX power report
 *
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

//#include <math.h>
#include "drv_i2c_ext.h"
#include "drv_gpioi2c_ext.h"
#include "drv_gpio_ext.h"
#include "hi_drv_gpioi2c.h"
#include "hi_debug.h"


#include "hi_drv_stat.h"
#include "hi_drv_dev.h"
#include "hi_drv_reg.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_proc.h"

#include "drv_tuner_ext.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_diseqc.h"
#include "drv_demod.h"

#include "MxL251SF_PhyCal.h"
#include "MxL251SF_Power.h"
#include "MxL251SF_NVRAMFile.h"

#ifndef _MXL251_BUILD_
static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_100_5Band[] =
{
 // F_REF_Mn    F_WB_Mn    F_WB_Md    F_WB_Mx    F_REF_Mx
  { 44000000,   44000000,  84500000,  125000000, 170000000},
  { 80000000,  125000000, 187500000,  250000000, 295000000},
  {205000000,  250000000, 400000000,  550000000, 595000000},
  {505000000,  550000000, 690000000,  830000000, 830000000},
  {830000001,  830000001, 915000000, 1000000001,1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_200_5Band[] =
{
 // F_REF_Mn    F_WB_Mn    F_WB_Md    F_WB_Mx    F_REF_Mx
  { 44000000,   44000000,  84500000,  125000000, 170000000},
  { 80000000,  125000000, 187500000,  250000000, 295000000},
//{                       400000000,  550000000, 595000000},
  {205000000,  250000000, 415000000,  580000000, 625000000},
//{505000000,  550000000, 690000000,                      },
  {535000000,  580000000, 705000000,  830000000, 830000000},
  {830000001,  830000001, 915000000, 1000000001,1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_100_4Band[] =
{
 // F_REF_Mn    F_WB_Mn    F_WB_Md    F_WB_Mx    F_REF_Mx
 //{44000000,   44000000,  84500000,  125000000, 170000000},
  {112000000,  125000000, 187500000,  250000000, 295000000},
  {205000000,  250000000, 400000000,  550000000, 595000000},
  {505000000,  550000000, 690000000,  830000000, 830000000},
  {830000001,  830000001, 915000000, 1000000001,1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_200_4Band[] =
{
 // F_REF_Mn    F_WB_Mn    F_WB_Md    F_WB_Mx    F_REF_Mx
 //{44000000,   44000000,  84500000,  125000000, 170000000},
  {112000000,  125000000, 187500000,  250000000, 295000000},
//{                       400000000,  550000000, 595000000},
  {205000000,  250000000, 415000000,  580000000, 625000000},
//{505000000,  550000000, 690000000,                      },
  {535000000,  580000000, 705000000,  830000000, 830000000},
  {830000001,  830000001, 915000000, 1000000001,1000000001},
};
#else // _MXL251_BUILD_

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_100_5Band[] =
{
 // F_WB_Mn    F_WB_Mx
  { 44000000,  125000000},
  {125000000,  250000000},
  {250000000,  550000000},
  {550000000,  830000000},
  {830000001, 1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_200_5Band[] =
{
 // F_WB_Mn    F_WB_Mx
  { 44000000,  125000000},
  {125000000,  250000000},
  {250000000,  580000000},
  {580000000,  830000000},
  {830000001, 1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_100_4Band[] =
{
 // F_WB_Mn    F_WB_Mx
  {125000000,  250000000},
  {250000000,  550000000},
  {550000000,  830000000},
  {830000001, 1000000001},
};

static const MXL_PWR_CAL_FREQ_RANGE_T PwrCalFreqRangeTable_ES1_200_4Band[] =
{
 // F_WB_Mn    F_WB_Mx
  {125000000,  250000000},
  {250000000,  580000000},
  {580000000,  830000000},
  {830000001, 1000000001},
};

#endif // _MXL251_BUILD_

#ifndef _MXL251_BUILD_
static const MXL_PWR_CAL_FREQ_RANGE_T* PwrCalFreqRangeTable = PwrCalFreqRangeTable_ES1_100_5Band;
#endif // _MXL251_BUILD_

static const SINT32 PwrCalDefaultCalFreq[] =
{
  92000000,
  116000000,
  140000000,
  164000000,
  212000000,
  260000000,
  280000000,
  356000000,
  452000000,
  540000000,
  560000000,
  580000000,
  600000000,
  630000000,
  660000000,
  690000000,
  720000000,
  750000000,
  780000000,
  810000000,
  840000000,
  870000000,
  900000000,
  930000000,
  960000000,
  990000000
};

#ifndef _MXL251_BUILD_
// Calibration frequency points for NB offset characterization
static const SINT32 PwrCalDefaultNbCalFreqList[] =
{
  356000000,
  452000000,
  690000000,
  750000000,
//  810000000,
};
#endif // _MXL251_BUILD_

static const SINT32 PwrCalNBFreqList[3][MXL_PWR_CAL_MAX_NBCAL_PT + 1] =
{
  // Each row has to be 0-terminated
  {-45000000, -33000000, -21000000, -9000000, 9000000, 21000000, 33000000, 45000000, 0},
  {-21000000, -16000000, -10000000, -4000000, 4000000, 10000000, 16000000, 21000000, 0},
  // {4000000, 6000000, 8000000, 10000000, 12000000, 14000000, 16000000, 18000000, 20000000, 22000000, 0},
  // {4000000, 6000000, 8000000, 10000000, 12000000, 14000000, 16000000, 18000000, 20000000, 22000000, 0},
  {3000000, 0}
};

#ifdef _MXL251_FIXEDPOINT_
//fixed point format with MXL251_PRECISION fractional bits
static const UINT32 PwrCalCRLUT[] =
{
  0xD  ,
  0x10 ,
  0x14 ,
  0x19 ,
  0x1F ,
  0x27 ,
  0x30 ,
  0x3C ,
  0x4C ,
  0x5F ,
  0x77 ,
  0x94 ,
  0xBA ,
  0xE8 ,
  0x122,
  0x16A,
  0x1C2,
};
#else
static const REAL32 PwrCalCRLUT[] =
{
  0.01193f,     // DU = 0dB
  0.01493f,     // DU = 1dB
  0.01869f,     // DU = 2dB
  0.02342f,     // DU = 3dB
  0.02938f,     // DU = 4dB
  0.03686f,     // DU = 5dB
  0.04626f,     // DU = 6dB
  0.05807f,     // DU = 7dB
  0.07289f,     // DU = 8dB
  0.09147f,     // DU = 9dB
  0.11476f,     // DU = 10dB
  0.14389f,     // DU = 11dB
  0.18029f,     // DU = 12dB
  0.22569f,     // DU = 13dB
  0.28218f,     // DU = 14dB
  0.35226f,     // DU = 15dB
  0.43891f,     // DU = 16dB ]
};
#endif

#ifndef _MXL251_BUILD_
static MXL_NVRAM_FILE_T MxLNVRAMFile;
// Enable or disable compensation during debug scan
static POWER_CAL_COMP_E PwrCalCompAtScan = POWER_CAL_DISABLE_COMP;
#endif // _MXL251_BUILD_

// Warning: only one copy of PwrCalLog for all 4 devices
static MXL_PWR_CAL_LOG_T PwrCalLog[MXL_PWR_CAL_NUM_OF_TUNERS];

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_MemCpy
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : memory copy
--|
--| RETURN VALUE  : Destination pointer
--|
--|-------------------------------------------------------------------------------------*/

static void * MxL251_MemCpy(void* dstPtr, const void* srcPtr, UINT32 n)
{
  UINT8* dstPtr8 = (UINT8*)dstPtr;

  const UINT8* srcPtr8 = (const UINT8*)srcPtr;

  if (n && dstPtr8 && srcPtr8)
  {
    do
    {
      *dstPtr8++ = *srcPtr8++;
    } while (--n);
  }
  return dstPtr;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrInitQuadratic
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Init a quadratic
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

static void MxL251_PwrInitQuadratic(MXL_PWR_QUADRATIC_COEF_T* coefPtr)
{
  coefPtr->C2  = 0;
  coefPtr->C1  = 0;
  coefPtr->C0  = 0;
  coefPtr->F_C = 0;
  coefPtr->F_D = 1;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalInit
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Add an entry to PwrCal Log
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxL251_PwrCalInit(void)
{
  UINT32 tunerId;
  UINT32 i;
  // Initialize PwrCalLog
  for (tunerId = 0; tunerId < MXL_PWR_CAL_NUM_OF_TUNERS; ++tunerId)
  {
    PwrCalLog[tunerId].numEntries = 0;
    for (i = 0; i < MXL_PWR_CAL_MAX_NUM_LOG_ENTRIES; ++i)
    {
      PwrCalLog[tunerId].table[i].RX_PWR = MXL_PWR_UNDEFINED_POWER;
    }
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrUpdateCalFreqRangeTable
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 05/17/2011
--|
--| DESCRIPTION   : Update PwrCalFreqRangeTable based on MxLNVRAMFile.PwrTempComp.NumOfFreqBands
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxL251_PwrUpdateCalFreqRangeTable(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT32 numOfBands)
{
  devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands = numOfBands;

  if (devContextPtr->ChipId == ES1_MM0_VERSION)
  {
    devContextPtr->PwrCalFreqRangeTable = (5==numOfBands)?
      PwrCalFreqRangeTable_ES1_100_5Band:
      PwrCalFreqRangeTable_ES1_100_4Band;
  }
  else
  {
    devContextPtr->PwrCalFreqRangeTable = (5==numOfBands)?
      PwrCalFreqRangeTable_ES1_200_5Band:
      PwrCalFreqRangeTable_ES1_200_4Band;
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCoefInit
--|
--| AUTHOR        : Jun Huang
--|                 Richard Liu
--|
--| DATE CREATED  : 09/15/2010
--|                 12/29/2010
--|
--| DESCRIPTION   : Add an entry to PwrCal Log
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxL251_PwrCoefInit(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
  UINT32 tunerId;
  UINT32 i;
#ifndef _MXL251_BUILD_
  UINT32 F_BAND;
  UINT32 j;
#endif // _MXL251_BUILD_

  // Initialize MxLNVRAMFile
  devContextPtr->MxLNVRAMFile.Header.Signature  = MXL_NVRAM_FILE_SIGNATURE;
  devContextPtr->MxLNVRAMFile.Header.FmtVersion = MXL_NVRAM_FILE_FMTVERSION;
  devContextPtr->MxLNVRAMFile.Header.Length     = sizeof(devContextPtr->MxLNVRAMFile);

  // Initialize MxLNVRAMFile.PwrTempComp
  devContextPtr->MxLNVRAMFile.PwrTempComp.Header.Signature = 0; // MXL_PWR_COEF_SIGNATURE_INVALID;
  devContextPtr->MxLNVRAMFile.PwrTempComp.Header.Length    = sizeof(devContextPtr->MxLNVRAMFile.PwrTempComp);
  devContextPtr->MxLNVRAMFile.PwrTempComp.REF_TEMP_CODE    = MXL_PWR_UNDEFINED_TEMP_CODE;
#ifndef _MXL251_BUILD_
  for (i = 0; i < MXL_PWR_CAL_NUM_OF_FREQ_BANDS; ++i)
  {
    for (j = 0; j < MXL_PWR_MAX_NUM_LNA_BO; ++j)
    {
      devContextPtr->MxLNVRAMFile.PwrTempComp.Slope_T[i][j] = 0;
    }
  }
#endif // _MXL251_BUILD_

  // Initialize MxLNVRAMFile.PwrFreqComp
  for (i = 0; i < MXL_PWR_CAL_NUM_OF_FREQ_BANDS; ++i)
  {
    for (tunerId = 0; tunerId < MXL_PWR_CAL_NUM_OF_TUNERS; ++tunerId)
    {
      devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Header.Signature = 0; // MXL_PWR_COEF_SIGNATURE_INVALID;
      devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Header.Length = sizeof(devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId]);
      MxL251_PwrInitQuadratic(&(devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Coef[i]));
    }
  }

  // Initialize MxLNVRAMFile.PwrTiltComp
  for (tunerId = 0; tunerId < MXL_PWR_CAL_NUM_OF_TUNERS; ++tunerId)
  {
    devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Header.Signature = 0; // MXL_PWR_COEF_SIGNATURE_INVALID;
    devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Header.Length = sizeof(devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId]);
    MxL251_PwrInitQuadratic(&(devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Coef));
  }

#ifndef _MXL251_BUILD_
  // Initialize PwrNBFreqComp
  for (tunerId = 0; tunerId < MXL_PWR_CAL_NUM_OF_TUNERS; ++tunerId)
  {
    MXL_PWR_NBFREQ_COMP_COEF_T* p = &(devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId]);
    p->Header.Signature = 0; // MXL_PWR_COEF_SIGNATURE_INVALID;
    p->Header.Length = sizeof(devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId]);
    for (F_BAND = 0; F_BAND < MXL_PWR_CAL_NUM_OF_FREQ_BANDS; ++F_BAND)
    {
      for (i = 0; i < MXL_PWR_CAL_NUM_BW_MODES/*2*/; ++i)
      {
        for (j = 0; j < MXL_PWR_CAL_MAX_NBCAL_PT; ++j)
        {
          p->FREQ_NB[i][j] = 0;
          p->OFFSET_NB[i][F_BAND][j] = 0;
        }
      }
      p->OFFSET_SCH_NB[F_BAND] = 0;
    }
  }
#endif // _MXL251_BUILD_

  // Set default num of freq bands (5)
  // Will be overwriten in MxL251_PwrLoadCoef right after firmware download
  MxL251_PwrUpdateCalFreqRangeTable(devContextPtr, MXL_PWR_CAL_NUM_OF_FREQ_BANDS);

}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetFreqBandIndex
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : This function returns RF input power in dBm.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static UINT32 MxL251_PwrGetFreqBandIndex(PMXL251SF_DEV_CONTEXT_T devContextPtr, SINT32 F_WB)
{
  // PwrCalFreqRangeTable
  if      (F_WB <= devContextPtr->PwrCalFreqRangeTable[0].F_WB_Mx) return MXL_PWR_CAL_FREQ_BAND_IDX_VHF1; // 0
  else if (F_WB <= devContextPtr->PwrCalFreqRangeTable[1].F_WB_Mx) return MXL_PWR_CAL_FREQ_BAND_IDX_VHF2; // 1
  else if (F_WB <= devContextPtr->PwrCalFreqRangeTable[2].F_WB_Mx) return MXL_PWR_CAL_FREQ_BAND_IDX_UHF1; // 2
  else if (F_WB <= devContextPtr->PwrCalFreqRangeTable[3].F_WB_Mx) return MXL_PWR_CAL_FREQ_BAND_IDX_UHF21; // 3
  else                                              return (devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands - 1); // (3 or 4) 
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrSaveMeasurementsToLog
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : This function saves power and gain measurements to log
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrSaveMeasurementsToLog(
  UINT8 i2cAddr,
  MXL_TUNER_ID_E tunerId,
  UINT8 chanId,
  MXL_PWR_CAL_LOG_ENTRY_T* p)
{
  UINT16 regData;
#ifdef _MXL251_FIXEDPOINT_
  SINT32 regData_temp;
#endif

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_RF1_GAIN+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  p->G_RF1 = MXL_SCALEUP((SINT32)((SINT16)regData), MXL251_PRECISION);
#else
  p->G_RF1 = (REAL32)(SINT16)regData;
#endif

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_LNA_GAIN+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  p->G_LNA = MXL_SCALEUP((SINT32)((SINT16)regData), MXL251_PRECISION);
#else
  p->G_LNA = (REAL32)(SINT16)regData;
#endif

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_RF2_GAIN+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  p->G_RF2 = MXL_SCALEUP((SINT32)((SINT16)regData), MXL251_PRECISION);
#else
  p->G_RF2 = (REAL32)(SINT16)regData;
#endif

  // Get WBVGA gains
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_WBVGA_GAIN+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_WB_DVGA  = MXL_DIV_SCALE(regData_temp, 32, MXL251_PRECISION );  
#else
  p->G_WB_DVGA = ((REAL32)(SINT16)regData)/32;
#endif

  // MxL_DLL_DEBUG0("%s (G_WB_DVGA=%f G_RF1=%f G_LNA=%f G_RF2=%f)\n",
  //     __FUNCTION__,
  //     p->G_WB_DVGA,
  //     p->G_RF1,
  //     p->G_LNA,
  //     p->G_RF2
  //     );

  // Get G_CIC1
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_G_CIC1+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_CIC1     = MXL_DIV_SCALE(regData_temp, PWR_REPORT_NB_GAIN_SCALE, MXL251_PRECISION);  
#else
  p->G_CIC1 = ((REAL32)(SINT16)regData)/PWR_REPORT_NB_GAIN_SCALE;
#endif

  // Get G_CIC2;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_G_CIC2+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_CIC2     = MXL_DIV_SCALE(regData_temp, PWR_REPORT_NB_GAIN_SCALE, MXL251_PRECISION );  
#else
  p->G_CIC2 = ((REAL32)(SINT16)regData)/PWR_REPORT_NB_GAIN_SCALE;
#endif

  // Get G_TCF;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_G_TCF+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_TCF      = MXL_DIV_SCALE(regData_temp, PWR_REPORT_NB_GAIN_SCALE, MXL251_PRECISION );  
#else
  p->G_TCF = ((REAL32)(SINT16)regData)/PWR_REPORT_NB_GAIN_SCALE;
#endif

  // Get G_FIR5;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_G_FIR5+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_FIR5     = MXL_DIV_SCALE(regData_temp, PWR_REPORT_NB_GAIN_SCALE, MXL251_PRECISION );  
#else
  p->G_FIR5 = ((REAL32)(SINT16)regData)/PWR_REPORT_NB_GAIN_SCALE;
#endif
  // Get G_NB_DAGC;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_G_NBDAGC+chanId*PWR_REPORT_MAILBOX_REG_BLOCK_SIZE,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT16)regData;
  p->G_NB_DAGC  = MXL_DIV_SCALE(regData_temp, 64, MXL251_PRECISION );  
#else
  p->G_NB_DAGC = ((REAL32)(SINT16)regData)/64;
#endif

  // Read P_OUT
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        MAILBOX_REG_PWR_REPORT_CHN0_DVGA_RSSI + chanId*2,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  regData_temp  = (SINT32)regData;  
  p->P_OUT  = MXL_DIV_SCALE(regData_temp, 32, MXL251_PRECISION );  
#else
  p->P_OUT = ((REAL32)regData)/32;
#endif
  MxL251_Ctrl_ReadRegister (i2cAddr, ADCx_RSSI_RB_REG(tunerId), &(p->AdcRssi));

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalAddLog
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Add an entry to PwrCal Log
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalAddLog(
  UINT8 i2cAddr,
  MXL_TUNER_ID_E tunerId,
  SINT32 F_NB,
  SINT32 F_WB,
#ifdef _MXL251_FIXEDPOINT_
  SINT32 P_REF,
#else
  REAL32 P_REF,
#endif
  MXL_PWR_CAL_TCF_MODE_E TCFmode
#ifndef  _MXL251_BUILD_
  , MXL_PWR_CAL_NB_MODE_E NB
#endif //  _MXL251_BUILD_
  )
{
  MXL_PWR_CAL_LOG_ENTRY_T* p = &PwrCalLog[tunerId].table[PwrCalLog[tunerId].numEntries];
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  if (PwrCalLog[tunerId].numEntries >= (MXL_PWR_CAL_MAX_NUM_LOG_ENTRIES-1))
  {
    MxL_DLL_DEBUG0("%s - too many log entries\n", __FUNCTION__);
    return MXL_FALSE;
  }

  p->F_NB       = F_NB;
  p->F_WB       = F_WB;
  p->F_BAND     = MxL251_PwrGetFreqBandIndex(devContextPtr, F_WB);//F_BAND;
#ifdef _MXL251_FIXEDPOINT_
  p->P_REF      = (SINT32)P_REF;
#else
  p->P_REF      = P_REF;
#endif
  p->TCFmode    = TCFmode;

#ifndef  _MXL251_BUILD_
  p->NB         = NB;
#endif //  _MXL251_BUILD_
  PwrCalLog[tunerId].numEntries++;

  // MxL_DLL_DEBUG0("%s - tuner %d: numEntries=%d\n", __FUNCTION__, tunerId, PwrCalLog[tunerId].numEntries);

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetTemperature
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get temperature in degree
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_PwrGetTemperature(UINT8 i2cAddr, SINT16* tempPtr)
{
  UINT16 regData;
  SINT32 tempCode;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, DFE_TSENS_RB_REG, &regData))
  {
    return MXL_FALSE;
  }
  // Tcode = 0.471*TdegC + 145.6
  // TdegC = (Tcode - 145.6)/0.471
  tempCode = (SINT32)MXL_SIGN_EXT16(regData, DFE_TSENS_RB_NBITS);
  *tempPtr = (tempCode*1000 - 145600)/471;
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_T
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get temperature compensation (C_T)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetC_T(UINT8 i2cAddr, UINT8 tunerId, /*SINT32 freqBandIdx,*/ SINT32* C_TPtr)
#else
static MXL_STATUS MxL251_PwrGetC_T(UINT8 i2cAddr, UINT8 tunerId, /*SINT32 freqBandIdx, */ REAL32* C_TPtr)
#endif
{
#ifdef _POWER_REPORTING_TEMP_COMP_ENABLED_
  SINT16 tempDegree = 25;
  UINT16 LNA_BO;
  UINT16 regData;
  // SINT32 boIdx;
#endif
#ifdef _MXL251_FIXEDPOINT_
  SINT64 ct_temp;  
#endif
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  *C_TPtr = 0;

  if (MXL_PWR_COEF_TABLE_SIGNATURE != devContextPtr->MxLNVRAMFile.PwrTempComp.Header.Signature)
  {
    return MXL_TRUE;
  }
  // Check if the platform is FPGA or Silicon
  if (IS_ASIC_TARGET(devContextPtr))
  {
#ifdef _POWER_REPORTING_TEMP_COMP_ENABLED_
    // Silicon

#ifdef _POWER_REPORTING_TEMP_COMP_DEBUG_
    if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, ECO8_REG, &regData))
    {
      return MXL_FALSE;
    }

    if (0 != (regData & 0x8000))
    {
      // Temp compensation disabled
      return MXL_TRUE;
    }

#endif // _POWER_REPORTING_TEMP_COMP_DEBUG_

    if (MXL_PWR_UNDEFINED_TEMP_CODE == devContextPtr->MxLNVRAMFile.PwrTempComp.REF_TEMP_CODE)
    {
      // No temperature was stored (old calibration)
      return MXL_TRUE;
    }

    if (MXL_TRUE != MxL251_PwrGetTemperature(i2cAddr, &tempDegree))
    {
      return MXL_FALSE;
    }

    if (MXL_TRUE != MxL251_Ctrl_ReadRegisterMask(i2cAddr,
          DFE_AGC_LNA_x_BO_REG(tunerId),
          DFE_AGC_LNA_x_BO_MASK(tunerId),
          &regData))
    {
      return MXL_FALSE;
    }
    LNA_BO = regData >> DFE_AGC_LNA_x_BO_LSB(tunerId);
    MxL_DLL_DEBUG0("LNA_BO=%u\n", LNA_BO);

    // Tsensor=temp in C of the internal temp sensor
    // Tcal=temp in C of the internal temp sensor at the time of the production cal
    // F=RF center frequency in MHz
    // LNABO= the LNA BO in dB (0 to 8). Assume the RF1 and RF2 and LNA BO contributions are linearly separable
    //
    //
    // Gain change (dB) = [ -0.8*(F-45)/(999-45)+-0.7+LNABO*(0.05) ]*(Tsensor-Tcal)/70
    //
    // Power readback correction (dB) = - Gain change (dB)
    //
#ifdef _MXL251_FIXEDPOINT_
	//(-0.8f*((REAL32)(devContextPtr->Tuners[tunerId].WbCapFreqInHz)/1000000.0f-45.0f)/(999.0f-45.0f)-0.7f+(REAL32)LNA_BO*0.05f );
	// Gain = [ -0.8*(F-45)/(999-45)+-0.7+LNABO*(0.05) ]*(Tsensor-Tcal)/70
	//ct_temp * 1000000*100 = [ 100*-0.8*(F-45*1000000)/(999-45) + -0.7*100 * 1000000 + LNABO *(0.05*1000000)*100 ] * (Tsensor-Tcal)/70

	ct_temp  = ((SINT64)(devContextPtr->Tuners[tunerId].WbCapFreqInHz) - 45*1000000);//scaled up by 10^6
	ct_temp *= -1* 80; //scaled up by 10^8
    //ct_temp /= 954;
	ct_temp = MXL_DIV64_S(ct_temp, 954);
	ct_temp -= 70 *1000000;
    //ct_temp /= 10000; //scale down to avoid overflow; final scale factor = 10^4
	ct_temp = MXL_DIV64_S(ct_temp, 10000); //scale down to avoid overflow; final scale factor = 10^4
	ct_temp += (LNA_BO * 5* 100);
    //ct_temp /= 70;
	ct_temp = MXL_DIV64_S(ct_temp, 70);
	ct_temp *= (tempDegree - devContextPtr->MxLNVRAMFile.PwrTempComp.REF_TEMP_CODE);
    *C_TPtr  = (SINT32)(MXL_DIV_SCALE64_S(ct_temp,10000, MXL251_PRECISION));//scale up by MXL251_PRECISION
    //MxL_DLL_DEBUG0("C_T= {%f}\n", MXL_VAL64(*C_TPtr));
#else
    *C_TPtr =  ( -0.8f*((REAL32)(devContextPtr->Tuners[tunerId].WbCapFreqInHz)/1000000.0f-45.0f)/(999.0f-45.0f)-0.7f+(REAL32)LNA_BO*0.05f );
    *C_TPtr *= ((REAL32)tempDegree-(REAL32)(devContextPtr->MxLNVRAMFile.PwrTempComp.REF_TEMP_CODE))/70.0f;
    *C_TPtr = -(*C_TPtr);
    MxL_DLL_DEBUG0("C_T=%f\n", *C_TPtr);
#endif
#endif
  }

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_F
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get C_F
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetC_F(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT32 tunerId, SINT32 freq, SINT32 freqBandIdx, SINT32* C_FPtr)
#else
static MXL_STATUS MxL251_PwrGetC_F(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT32 tunerId, SINT32 freq, SINT32 freqBandIdx, REAL32* C_FPtr)
#endif
{
  MXL_PWR_QUADRATIC_COEF_T * p;  

  *C_FPtr = 0;
  if (MXL_PWR_COEF_TABLE_SIGNATURE != devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Header.Signature)
  {
    return MXL_TRUE;
  }

  // Only do frequency compensation if table is valid
  p = &(devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Coef[freqBandIdx]);

  if (p->F_D)
  {
#ifdef _MXL251_FIXEDPOINT_
	SINT64 X;
	SINT64 Cfptr = *C_FPtr;
	X = MXL_DIV_SCALE64_S((freq/100000 - p->F_C/100000),(p->F_D/100000), MXL251_PRECISION);
	Cfptr = MXL_MUL64_S(X , X ,MXL251_PRECISION);
	Cfptr = MXL_MUL64_S(p->C2 , Cfptr , MXL251_PRECISION);
	Cfptr += MXL_MUL64_S(p->C1 , X, MXL251_PRECISION);
	Cfptr += p->C0 ;
	*C_FPtr = (SINT32)Cfptr;
	
#else
    REAL32 X = (REAL32)(freq - p->F_C) / (REAL32)(p->F_D);
    *C_FPtr = p->C0 + p->C1*X + p->C2 * X * X; // (11)
#endif

    return MXL_TRUE;
  }
  else
  {
    MxL_DLL_DEBUG0("%s: F_D is 0\r\n", __FUNCTION__);
    return MXL_FALSE;
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_TC
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get C_TC
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetC_TC(UINT8 i2cAddr, UINT32 tunerId, SINT32 freq, SINT32 freqBandIdx, SINT32* C_TCPtr)
#else
static MXL_STATUS MxL251_PwrGetC_TC(UINT8 i2cAddr, UINT32 tunerId, SINT32 freq, SINT32 freqBandIdx, REAL32* C_TCPtr)
#endif
{

#ifdef _MXL251_FIXEDPOINT_
		SINT64 X;
		SINT64 Cfptr;
#endif
  UINT16 regData;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);
  UINT32 tiltOn = 0;

  *C_TCPtr = 0;

  // Only do tilt compensation if table is valid
  if (MXL_PWR_COEF_TABLE_SIGNATURE != devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Header.Signature)
  {
    return MXL_TRUE;
  }

  if (freqBandIdx == MXL_PWR_CAL_FREQ_BAND_IDX_UHF21 ||freqBandIdx == MXL_PWR_CAL_FREQ_BAND_IDX_UHF22)
  {
    if (IS_ES2_OR_NEWER(devContextPtr))
    {
      if (MXL_TRUE != MxL251_Ctrl_ReadRegister(
            i2cAddr,
            MAILBOX_REG_TILT_FLAG,
            &regData))
      {
        return MXL_FALSE;
      }
      tiltOn = (regData & DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK);
    }
    else
    {
      if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ANA_DNXx_LNA_TILT_REG(tunerId), &regData))
      {
        return MXL_FALSE;
      }
      tiltOn = (regData & 0x4000);
    }
    if (tiltOn)
    {
      /* Tilt comp enabled*/
      MXL_PWR_QUADRATIC_COEF_T* p = &devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Coef;
      if (p->F_D)
      {
#ifdef _MXL251_FIXEDPOINT_
		Cfptr = *C_TCPtr;
		X = MXL_DIV_SCALE64_S((freq/100000 - p->F_C/100000),(p->F_D/100000), MXL251_PRECISION);
		Cfptr = MXL_MUL64_S(X , X ,MXL251_PRECISION);
		Cfptr = MXL_MUL64_S(p->C2 , Cfptr , MXL251_PRECISION);
		Cfptr += MXL_MUL64_S(p->C1 , X, MXL251_PRECISION);
		Cfptr += p->C0 ;
		*C_TCPtr = (SINT32)Cfptr;
#else
        REAL32 X = (REAL32)(freq - p->F_C) / (REAL32)(p->F_D);
        *C_TCPtr = p->C0 + p->C1 * X + p->C2 * X * X;
#endif
      }
      else
      {
        MxL_DLL_DEBUG0("%s - ERROR: F_D is 0\r\n", __FUNCTION__);
        return MXL_FALSE;
      }
    }
  }

  return MXL_TRUE;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_R
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get C_R
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetC_R(UINT8 i2cAddr, SINT32* C_RPtr)
#else
static MXL_STATUS MxL251_PwrGetC_R(UINT8 i2cAddr, REAL32* C_RPtr)
#endif
{
  UINT16 regData;
  UINT32 du0, du1;
  *C_RPtr = 0;

  // Always get the channel RSSI DU of last tuned channel
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_CUR_CHAN_RSSI_DU, &regData))
  {
    return MXL_FALSE;
  }

  du0 = regData & 0xFF;
  du1 = regData >> 8;

  // Note both du0 and du1 were defined as SINT8
  // So negative du becomes larger than 0x80 and effectively 0 contribution to C_R
  if (du0 < sizeof(PwrCalCRLUT)/sizeof(PwrCalCRLUT[0])) *C_RPtr += PwrCalCRLUT[du0];
  if (du1 < sizeof(PwrCalCRLUT)/sizeof(PwrCalCRLUT[0])) *C_RPtr += PwrCalCRLUT[du1];

  return MXL_TRUE;
}

#ifndef _MXL251_BUILD_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_NB
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : Get C_NB
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrGetC_NB(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT32 tunerId, SINT32 freqBandIdx, SINT32 /*F_NB*/, UINT32 wbBW, REAL32* C_NBPtr)
{
  *C_NBPtr = 0;
  if (MXL_PWR_COEF_TABLE_SIGNATURE != devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].Header.Signature)
  {
    MxL_DLL_DEBUG0("%s - invalid signature\n", __FUNCTION__);
    *C_NBPtr = 0;
    return MXL_TRUE;
  }

  if (wbBW == WB_16_MHz)
  {
    // Single channel mode
    *C_NBPtr = devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_SCH_NB[freqBandIdx];
    return MXL_TRUE;
  }
  else
  {
    // Full or half bandwidth
    MXL_PWR_NBFREQ_COMP_COEF_T* p = &(devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId]);
    UINT32 bwMode = (wbBW == WB_96_MHz)?0:1;

    if (F_NB <= p->FREQ_NB[bwMode][0])
    {
      // If F_NB is below smallest calib point, use the lowest one
      *C_NBPtr = p->OFFSET_NB[bwMode][freqBandIdx][0];
      MxL_DLL_DEBUG0("%s - use lowest point\n", __FUNCTION__);
    }
    else if (F_NB >= p->FREQ_NB[bwMode][MXL_PWR_CAL_MAX_NBCAL_PT-1])
    {
      // If F_NB is beyond highest calib point, use the highest one
      *C_NBPtr = p->OFFSET_NB[bwMode][freqBandIdx][MXL_PWR_CAL_MAX_NBCAL_PT-1];
      MxL_DLL_DEBUG0("%s - use highest point\n", __FUNCTION__);
    }
    else
    {
      // Otherwise use interpolation
      UINT32 i;
      for (i = 0; i < MXL_PWR_CAL_MAX_NBCAL_PT - 1; ++i)
      {
        REAL32 F1 = (REAL32)(p->FREQ_NB[bwMode][i])   ;
        REAL32 F2 = (REAL32)(p->FREQ_NB[bwMode][i+1]) ;
        if (F1 <= (REAL32)F_NB && (REAL32)F_NB <= F2 && F2 > F1)
        {
          REAL32 O1 = (REAL32)(p->OFFSET_NB[bwMode][freqBandIdx][i])  ;
          REAL32 O2 = (REAL32)(p->OFFSET_NB[bwMode][freqBandIdx][i+1]);
          *C_NBPtr = O1 + ((O2 - O1)*((REAL32)F_NB - F1)) / (F2 - F1); // (17)
          break;
        }
      }
      if (i >= (MXL_PWR_CAL_MAX_NBCAL_PT - 1))
      {
        MxL_DLL_ERROR0("failed to get C_NB");
        return MXL_FALSE;
      }
    }
    return MXL_TRUE;
  }
}
#endif // _MXL251_BUILD_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_UpdateFirmwareStatus
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/22/2010
--|
--| DESCRIPTION   : This function updates FirmwareStatus
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_UpdateFirmwareStatus(UINT8 i2cAddr)
{
  MXL_DEV_VERSION_INFO_T devInfo;

  devInfo.I2cSlaveAddr = i2cAddr;

  if (MXL_TRUE != MxL251_GetDeviceVersionInfo(&devInfo))
  {
    return MXL_FALSE;
  }

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetC_ST
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 11/22/2010
--|
--| DESCRIPTION   : This function returns compensation with single tuner case
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetC_ST(UINT8 i2cAddr, SINT32 F_RF, SINT32* C_STPtr)
#else
static MXL_STATUS MxL251_PwrGetC_ST(UINT8 i2cAddr, SINT32 F_RF, REAL32* C_STPtr)
#endif
{
#ifdef _MXL251_FIXEDPOINT_
  SINT64 cs_temp;
#endif
  UINT16 tuner0Enable;
  UINT16 tuner1Enable;
  
  *C_STPtr = 0;

  if (MXL_TRUE != MxL251_Ctrl_ReadRegisterMask(i2cAddr, DIG_ANA_TUNER0_ENA_REG, DIG_ANA_TUNER0_ENA_MASK, &tuner0Enable))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_ReadRegisterMask(i2cAddr, DIG_ANA_TUNER1_ENA_REG, DIG_ANA_TUNER1_ENA_MASK, &tuner1Enable))
  {
    return MXL_FALSE;
  }

  if (tuner0Enable == 0 || tuner1Enable == 0)
  {
    // If one tuner is off
    if (F_RF < 650000000)
    {
#ifdef _MXL251_FIXEDPOINT_	 
	  *C_STPtr = 0x199a; //Scaled to MXL251_PRECISION
#else
      *C_STPtr = 0.2f;
#endif
    }
    else
    {
#ifdef _MXL251_FIXEDPOINT_	  
		/*At this point (F_RF - 650000000) is always positive.
		  Using 29 fraction bits for 0.2 & 0.6 and scaling the frequency by 100000 */
		cs_temp =   (UINT64)  0x13333333 * (F_RF/100000 - 6500);
        //cs_temp /= 3500;
		cs_temp = MXL_DIV64_S( cs_temp,0x6666666);
		/* bringing back to MXL251_PRECISION */
        //cs_temp /= (1 << (29 - MXL251_PRECISION )); 
		cs_temp = MXL_DIV64_S(cs_temp, (1 << (29 - MXL251_PRECISION ))); 
		*C_STPtr = (SINT32)cs_temp;
#else
        *C_STPtr = 0.2f + 0.6f * (REAL32)(F_RF - 650000000)/(REAL32)350000000;
#endif
    }
  }
#ifdef _MXL251_FIXEDPOINT_
  MxL_DLL_DEBUG0("tuner0Enable=%d, tuner1Enable=%d, C_ST=%x\n", tuner0Enable, tuner1Enable, *C_STPtr);
#else
  MxL_DLL_DEBUG0("tuner0Enable=%d, tuner1Enable=%d, C_ST=%f\n", tuner0Enable, tuner1Enable, *C_STPtr);
#endif
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrMeasureRxPower
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/15/2010
--|
--| DESCRIPTION   : This function returns RF input power in dBm.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
MXL_STATUS MxL251_PwrMeasureRxPower(UINT8 i2cAddr, UINT8 chanId, SINT32* rxPwrIndBmVPtr, POWER_CAL_COMP_E bComp, MXL_BOOL powerMonEnabled)
#else
MXL_STATUS MxL251_PwrMeasureRxPower(UINT8 i2cAddr, UINT8 chanId, REAL32* rxPwrIndBmVPtr, POWER_CAL_COMP_E bComp, MXL_BOOL powerMonEnabled)
#endif
{
  SINT32  F_WB;
  SINT32  F_NB;
  SINT32  freqBandIdx;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);
#ifdef _MXL251_FIXEDPOINT_
  SINT32  C_T = 0;
  SINT32  C_F = 0;
  SINT32  C_TC = 0;
  SINT32  C_R = 0;
#else
  REAL32  C_T = 0;
  REAL32  C_F = 0;
  REAL32  C_TC = 0;
  REAL32  C_R = 0;
#endif

#ifndef _MXL251_BUILD_
#ifdef _MXL251_FIXEDPOINT_
  UINT32 C_NB = 0;
#else
  REAL32 C_NB = 0;
#endif
#endif // _MXL251_BUILD_

#ifdef _MXL251_FIXEDPOINT_
  SINT32  C_ST = 0;
#else
  REAL32  C_ST = 0; // Compensation due to single tuner
#endif
  UINT16  regData;
  UINT8   tunerId;
  HOST_COMMAND_T  hostCmd;
  MXL_PWR_CAL_LOG_ENTRY_T* logPtr;
  MXL_BOOL fastScan;

  MxL_DLL_DEBUG0("%s - i2cAddr=0x%x, ChanId=%d\n", __FUNCTION__, i2cAddr, chanId);

  tunerId = MxL251_Ctrl_GetTunerId(chanId);

  fastScan = (MXL_ENABLE == powerMonEnabled)?MXL_ENABLE:(devContextPtr->Tuners[tunerId].FastScanEnable);

  if (MXL_DISABLE == fastScan)
  {
    // Make sure channel is enabled
    if (MXL_TRUE != MxL251_Ctrl_GetChanXbarEnaRegister(i2cAddr, &regData))
    {
      return MXL_FALSE;
    }
    if (0 == (regData & DFE_CHN_ENA_BIT(chanId)))
    {
      MxL_DLL_DEBUG0("%s - channel %d not enabled\n", __FUNCTION__, chanId);
      return MXL_FALSE;
    }
  }

  // Wait until last tune command is done
  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }

  // Get last F_NB
  F_NB = devContextPtr->Tuners[tunerId].FreqOffsetInHz;

  // if (devContextPtr->FirmwareVersion > 0x0101010106ULL)
  if (MXL_DISABLE == fastScan)
  {
    // Send host command to enable power report
    FORM_CMD_HEADER(hostCmd, HOST_CMD_TUNER_POWER_REPORT_CFG, 0, 0);
    hostCmd.payloadCheckSum = (UINT8)(1<<chanId); // channelMap
    if (MXL_TRUE != MxL251_Ctrl_SendHostCommand(i2cAddr, &hostCmd))
    {
      return MXL_FALSE;
    }

    // Wait until host command is done
    if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
    {
      return MXL_FALSE;
    }
  }

  // Initialize MxLNVRAMFile if not done so
  if (MXL_NVRAM_FILE_SIGNATURE != devContextPtr->MxLNVRAMFile.Header.Signature)
  {
    MxL251_PwrCoefInit(devContextPtr);
  }

  // Get C_T
  F_WB = devContextPtr->Tuners[tunerId].WbCapFreqInHz;
  freqBandIdx = MxL251_PwrGetFreqBandIndex(devContextPtr, F_WB);

  if (MXL_DISABLE == fastScan)
  {
#ifdef _MXL251_FIXEDPOINT_
    if (MXL_TRUE != MxL251_PwrGetC_T(i2cAddr, tunerId,/* freqBandIdx,*/ &C_T))
#else
    if (MXL_TRUE != MxL251_PwrGetC_T(i2cAddr, tunerId,/* freqBandIdx, */&C_T))
#endif
    {
      return MXL_FALSE;
    }

    if (0 == MxL251_Ctrl_SpinOnRegField(i2cAddr,
          MAILBOX_REG_PWR_REPORT_CHN0_RXPWR + chanId*2,
          0xFFFF,
          0x8000,
          SPIN_UNTIL_NEQ,
          5000000))
    {
      MxL_DLL_ERROR0("Reading RxPwr timeout");
      return MXL_FALSE;
    }
  }

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        ((MXL_ENABLE == powerMonEnabled)?MAILBOX_REG_CHN0_RXPWR_MONITOR:MAILBOX_REG_PWR_REPORT_CHN0_RXPWR) + chanId*2,
        &regData))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  *rxPwrIndBmVPtr = (SINT32)(MXL_DIV_SCALE_S((SINT32)((SINT16)regData), 64, MXL251_PRECISION));
  //MxL_DLL_PRINT0("%s - raw RxPwr={%f}\n",__FUNCTION__, MXL_VAL64(*rxPwrIndBmVPtr));
#else
  *rxPwrIndBmVPtr = ((REAL32)(SINT16)regData)/64;
  MxL_DLL_PRINT0("%s - raw RxPwr=%f\n", __FUNCTION__, *rxPwrIndBmVPtr);
#endif
  

  logPtr = &PwrCalLog[tunerId].table[PwrCalLog[tunerId].numEntries];

  if (POWER_CAL_ENABLE_COMP == bComp)
  {
    // If compensation is enabled
    // Get C_F
    if (MXL_TRUE != MxL251_PwrGetC_F(devContextPtr, tunerId, F_WB + F_NB, freqBandIdx, &C_F))
    {
      return MXL_FALSE;
    }

    if (MXL_DISABLE == fastScan)
    {
      // Get C_TC
      if (MXL_TRUE != MxL251_PwrGetC_TC(i2cAddr, tunerId, F_WB + F_NB, freqBandIdx, &C_TC))
      {
        return MXL_FALSE;
      }

      // Get C_R
      if (MXL_TRUE != MxL251_PwrGetC_R(i2cAddr, &C_R))
      {
        return MXL_FALSE;
      }
    }

#ifndef _MXL251_BUILD_
    // Get C_NB
    if (MXL_TRUE != MxL251_PwrGetC_NB(devContextPtr, tunerId, freqBandIdx, F_NB, devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz, &C_NB))
    {
      return MXL_FALSE;
    }
    *rxPwrIndBmVPtr += C_NB;
#endif //  _MXL251_BUILD_

    *rxPwrIndBmVPtr += C_T + C_F + C_TC + C_R;

    if (MXL_DISABLE == fastScan)
    {
      if (MXL_TRUE != MxL251_PwrGetC_ST(i2cAddr, F_WB + F_NB, &C_ST))
      {
        return MXL_FALSE;
      }
      *rxPwrIndBmVPtr -= C_ST;
    }
    if (WB_96_MHz == devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz)
    {
      *rxPwrIndBmVPtr += MXL251_DIFF_GAIN_96_16_MHZ_MODES;
    }

    logPtr->C_F  = C_F;
    logPtr->C_TC = C_TC;
    logPtr->C_R  = C_R;
#ifndef _MXL251_BUILD_
    logPtr->C_NB = C_NB;
#endif // _MXL251_BUILD_
  }
  else
  {
    logPtr->C_F  = 0;
    logPtr->C_TC = 0;
    logPtr->C_R  = 0;
#ifndef _MXL251_BUILD_
    logPtr->C_NB = 0;
#endif // _MXL251_BUILD_
  } 


  if (MXL_DISABLE == fastScan)
  {
    // Update log
    logPtr->RX_PWR = *rxPwrIndBmVPtr;

    if (MXL_TRUE != MxL251_PwrSaveMeasurementsToLog(i2cAddr, (MXL_TUNER_ID_E)tunerId, chanId, logPtr))
    {
      return MXL_FALSE;
    }

    if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_DEBUG_FLAG, &regData))
    {
      return MXL_FALSE;
    }

    if (1) // 0 != (regData&PWR_CAL_DEBUG_BIT_VERBOSE))
    {
      // Only print logs in verbose mode
#ifdef _MXL251_FIXEDPOINT_
        //MxL_DLL_PRINT0("%s - P_IN={%f} P_OUT={%f}\n", __FUNCTION__, MXL_VAL64(logPtr->RX_PWR), MXL_VAL64(logPtr->P_OUT));
#else
	  MxL_DLL_PRINT0("%s - P_IN=%f P_OUT=%f\n", __FUNCTION__, logPtr->RX_PWR, logPtr->P_OUT);
#endif

//#ifndef _MXL251_BUILD_
#if 1
#if 0
      MxL_DLL_PRINT0("%s - G_WB_DVGA=%-.2f G_RF1=%-.0f G_LNA=%-.0f G_RF2=%-.0f G_CIC1=%-.2f G_CIC2=%-.2f G_TCF=%-.2f G_FIR5=%-.2f G_NB_DAGC%-.2f AdcRssi=%-5u C_F=%-.3f C_TC=%-.3f C_R=%-.3f C_NB=%-.3f C_ST=%-.3f C_T=%-.3f\n", 
          __FUNCTION__,
          logPtr->G_WB_DVGA,
          logPtr->G_RF1,
          logPtr->G_LNA,
          logPtr->G_RF2,
          logPtr->G_CIC1,
          logPtr->G_CIC2,
          logPtr->G_TCF,
          logPtr->G_FIR5,
          logPtr->G_NB_DAGC,
          logPtr->AdcRssi,
          logPtr->C_F,
          logPtr->C_TC,
          logPtr->C_R,
          logPtr->C_NB,
          C_ST,
          C_T
          );
#endif
#else // _MXL251_BUILD_
#ifdef _MXL251_FIXEDPOINT_	  
	  MxL_DLL_PRINT0("%s - G_WB_DVGA=%-.3f G_RF1=%-.0f G_LNA=%-.0f G_RF2=%-.0f G_CIC1=%-.2f G_CIC2=%-.2f G_TCF=%-.2f G_FIR5=%-.2f G_NB_DAGC%-.2f AdcRssi=%-5u C_F=%-.3f ",
          __FUNCTION__,
          MXL_VAL(logPtr->G_WB_DVGA),MXL_VAL(logPtr->G_RF1),  MXL_VAL(logPtr->G_LNA),MXL_VAL(logPtr->G_RF2),MXL_VAL(logPtr->G_CIC1),MXL_VAL(logPtr->G_CIC2),MXL_VAL(logPtr->G_TCF),MXL_VAL(logPtr->G_FIR5),\
		  MXL_VAL(logPtr->G_NB_DAGC),logPtr->AdcRssi,MXL_VAL(logPtr->C_F));
	  MxL_DLL_PRINT0("C_TC=%-.3f C_R=%-.3f",MXL_VAL(logPtr->C_TC) ,MXL_VAL(logPtr->C_R));
	  MxL_DLL_PRINT0("C_ST=%-.3f C_T=%-.3f\n",MXL_VAL64(C_ST),MXL_VAL64(C_T));
#else
	  MxL_DLL_PRINT0("%s - G_WB_DVGA=%-.3f G_RF1=%-.0f G_LNA=%-.0f G_RF2=%-.0f G_CIC1=%-.2f G_CIC2=%-.2f G_TCF=%-.2f G_FIR5=%-.2f G_NB_DAGC%-.2f AdcRssi=%-5u C_F=%-.3f C_TC=%-.3f C_R=%-.3f C_ST=%-.3f C_T=%-.3f\n",
          __FUNCTION__,
          logPtr->G_WB_DVGA,
          logPtr->G_RF1,
          logPtr->G_LNA,
          logPtr->G_RF2,
          logPtr->G_CIC1,
          logPtr->G_CIC2,
          logPtr->G_TCF,
          logPtr->G_FIR5,
          logPtr->G_NB_DAGC,
          logPtr->AdcRssi,
          logPtr->C_F,
          logPtr->C_TC,
          logPtr->C_R,
          C_ST,
          C_T
          );
#endif
#endif // _MXL251_BUILD_
    }
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_CalOobRxPower
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/08/2015
--|
--| DESCRIPTION   : This function is used to calculate RX RF power in dBmV unit.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
MXL_STATUS MxL251_CalOobRxPower(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, SINT32 rxPwrIndBmV, SINT32* pwrIndBmVPtr)
{
  UINT8 status = MXL_SUCCESS;
  UINT16 agcGain, regAddr; 
  SINT32 val; 
  UINT32 val1,val2;

  regAddr = MxL251_Ctrl_ConvertDemodIdToAddr(demodId,DEMOD_MAGC_GAIN__REG);

  status |= MxL251_Ctrl_ReadRegister(i2cAddr, regAddr, &agcGain);
  
  if (agcGain <= 0)
  {
    MxL_DLL_PRINT0("Demod%d register %x read = %d, abnormal! \n",demodId,regAddr,agcGain);
    *pwrIndBmVPtr = rxPwrIndBmV;
  }
  else 
  {
   // calculate 20*log(value/1024);
   status |= MxL251_Ctrl_10Log((UINT32)agcGain, &val1);
   status |= MxL251_Ctrl_10Log(1024, &val2);
   val2 = 3010;  // log10(1024)*1000 = 3010 
   val = (SINT32)(val1 - val2)*20;
   *pwrIndBmVPtr = rxPwrIndBmV - val/1000 + OOB_RX_POWER_CAL_FACTOR;
  }

  return (MXL_STATUS)status;
}
#else
MXL_STATUS MxL251_CalOobRxPower(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, REAL32 rxPwrIndBmV, REAL32* pwrIndBmVPtr)
{
  UINT8 status = MXL_SUCCESS;
  UINT16 agcGain, regAddr; 
  REAL32 val1,val2;

  regAddr = MxL251_Ctrl_ConvertDemodIdToAddr(demodId,DEMOD_MAGC_GAIN__REG);

  status |= MxL251_Ctrl_ReadRegister(i2cAddr, regAddr, &agcGain);

  if (agcGain <= 0)
  {
    MxL_DLL_PRINT0("Demod%d register %x read = %d, abnormal! \n",demodId,regAddr,agcGain);
    *pwrIndBmVPtr = rxPwrIndBmV;
  }
  else 
  {
   // calculate 20*log(value/1024);
   status |= MxL251_Ctrl_10Log((REAL32)agcGain, &val1);
   status |= MxL251_Ctrl_10Log(1024, &val2);
   val1 = (val1 - val2)*20;
   *pwrIndBmVPtr = rxPwrIndBmV - val1 + OOB_RX_POWER_CAL_FACTOR;
  }

  return (MXL_STATUS)status;
}
#endif 
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalTuneMeasureOnce
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : This function is used to make 251 rx power meter to be
--|                 calibrated to improve accuracy of its measurement
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalTuneMeasureOnce(UINT8 i2cAddr,
                                           UINT8 tunerId,
                                           SINT32 F_WB,
                                           SINT32 F_NB,
                                           MXL_PWR_CAL_TCF_MODE_E TCFmode,
#ifndef _MXL251_BUILD_
                                           MXL_PWR_CAL_NB_MODE_E bwMode,
#endif //_MXL251_BUILD_
#ifdef _MXL251_FIXEDPOINT_
                                           SINT32 P_REF										   
#else
                                           REAL32 P_REF
#endif //_MXL251_FIXEDPOINT_
										   )
{
  UINT8 wbCapBandWidthInMHz;
  UINT8  chanId = MxL251_Ctrl_GetDemodChanId((MXL_TUNER_ID_E)tunerId);
#ifdef _MXL251_FIXEDPOINT_
  SINT32                    rxPwr;
#else
  REAL32                    rxPwr;
#endif
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  // MxL251_Ctrl_DelayUsec(200000);
  // NB disable
  if (MXL_TRUE != MxL251_Ctrl_NbChanDisable(i2cAddr, chanId, MXL_ENABLE/*ifRamp*/))
  {
    return MXL_FALSE;
  }

  if (!IS_ASIC_TARGET(devContextPtr))
  {
    // Force at 48 MHz for FPGA platform
    wbCapBandWidthInMHz = WB_48_MHz;
  }
  else
  {
#ifndef _MXL251_BUILD_
    if (bwMode <= PWR_CAL_NB_MODE_FULL_BAND_NBCAL)      wbCapBandWidthInMHz = (UINT8)WB_96_MHz;
    else if (bwMode == PWR_CAL_NB_MODE_HALF_BAND_NBCAL) wbCapBandWidthInMHz = (UINT8)WB_48_MHz;
    else
#endif // _MXL251_BUILD_
      wbCapBandWidthInMHz = (UINT8)WB_16_MHz;
  }

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
          MAILBOX_REG_TILT_FLAG,
          DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK,
          (TCFmode==MXL_PWR_CAL_TCF_MODE_ON)?DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK:0x0000))
    {
      return MXL_FALSE;
    }
  }
  else
  {
    // Set TCF on/off depending on TCFmode
    if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
          DIG_ANA_DNXx_LNA_TILT_REG(tunerId),
          0xC000,
          (TCFmode==MXL_PWR_CAL_TCF_MODE_ON)?0x4000:0x0000))
    {
      return MXL_FALSE;
    }
  }

  if (MXL_TRUE != MxL251_Ctrl_WbTunerEnable(
        i2cAddr,
        (MXL_TUNER_ID_E)tunerId,
        MXL_TUNER_ENABLED_NORMAL,
        (UINT32)F_WB,
        wbCapBandWidthInMHz,
        MXL_DISABLE/*fastScan*/))
  {
    return MXL_FALSE;
  }
  // MxL251_Ctrl_DelayUsec(200000);

  // Check if the previous NB or WB tune is done
  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }

//  // Freeze LNA_BO to 4
//  if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
//        DFE_AGC_LNA_x_BO_REG(tunerId),
//        DFE_AGC_LNA_x_BO_MASK(tunerId),
//        4<<DFE_AGC_LNA_x_BO_LSB(tunerId)/*4dB*/))
//  {
//    return MXL_FALSE;
//  }

//  MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, AGC_APPLY_GAIN_MASK, 0);
//  MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, AGC_APPLY_GAIN_MASK, AGC_APPLY_GAIN_MASK);
//  MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, AGC_APPLY_GAIN_MASK, 0);

  // NB Tune
  if (MXL_TRUE != MxL251_Ctrl_NbChannelEnable(
        i2cAddr,
        tunerId,
        chanId,
        NB_6_MHz,
        F_WB + F_NB, // centerFrequencyInHz,
        MXL_INVERTED_IF_SPECTRUM, // MXL_BOOL IF_Polarity,
        0, // UINT16 IF_AgcSetPoint,
        0 // UINT32 IF_FreqInHz
        ))
  {
    return MXL_FALSE;
  }

//  MxL251_Ctrl_DelayUsec(200000);

  if (MXL_TRUE != MxL251_PwrMeasureRxPower(
        i2cAddr,
        chanId,
        &rxPwr,
        devContextPtr->PwrCalCompAtScan,
        MXL_DISABLE/*powerMonEnabled*/))
  {
    return MXL_FALSE;
  }

  MxL251_PwrCalAddLog(
      i2cAddr,
      (MXL_TUNER_ID_E)tunerId,
      F_NB,
      F_WB,
      P_REF,
      TCFmode
#ifndef _MXL251_BUILD_
      , bwMode
#endif // _MXL251_BUILD_
  );

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalTuneMeasure
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : This function is used to make 251 rx power meter to be
--|                 calibrated to improve accuracy of its measurement
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalTuneMeasure(UINT8 i2cAddr,
                                           UINT8 tunerId,
                                           SINT32 F_WB,
                                           SINT32 F_NB,
                                           MXL_PWR_CAL_TCF_MODE_E TCFmode,
#ifndef _MXL251_BUILD_
                                           MXL_PWR_CAL_NB_MODE_E bwMode,
#endif // _MXL251_BUILD_
#ifdef _MXL251_FIXEDPOINT_
                                           SINT32 P_REF
#else
                                           REAL32 P_REF
#endif
										   )
{
  UINT32 nRetries = 3;
  while (nRetries--)
  {
#ifdef _MXL251_FIXEDPOINT_
    MxL_DLL_PRINT0("Power calibration on %d (F_WB=%d F_NB=%d) with P_REF= ", F_WB+F_NB, F_WB, F_NB);
    //MxL_DLL_PRINT0(" {%f}\n", MXL_VAL64(P_REF));
#else
	MxL_DLL_PRINT0("Power calibration on %d (F_WB=%d F_NB=%d) with P_REF=%f\n", F_WB+F_NB, F_WB, F_NB, P_REF);
#endif //#ifdef _MXL251_FIXEDPOINT_

#ifndef _MXL251_BUILD_
    if (MXL_TRUE  == MxL251_PwrCalTuneMeasureOnce(i2cAddr, tunerId, F_WB, F_NB, TCFmode, bwMode, P_REF))
#else // _MXL251_BUILD_
    if (MXL_TRUE  == MxL251_PwrCalTuneMeasureOnce(i2cAddr, tunerId, F_WB, F_NB, TCFmode, /*bwMode, */ P_REF))
#endif // _MXL251_BUILD_
    {
      return MXL_TRUE;
    }
  }
  MxL_DLL_ERROR0("%s - failed 3 retries\r\n", __FUNCTION__);
  return MXL_FALSE;
}

#ifndef _MXL251_BUILD_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalNbCalNeeded
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 11/12/2010
--|
--| DESCRIPTION   : Test if NB calibration is needed for a given F_REF
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_PwrCalNbCalNeeded(SINT32 F_REF)
{
  UINT32 i;
  for (i = 0; i < sizeof(PwrCalDefaultNbCalFreqList)/sizeof(PwrCalDefaultNbCalFreqList[0]); ++i)
  {
    if (PwrCalDefaultNbCalFreqList[i] == F_REF)
    {
      return MXL_TRUE;
    }
  }
  return MXL_FALSE;
}
#endif // _MXL251_BUILD_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalOneFreq
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : This function is used to make 251 rx power meter to be
--|                 calibrated to improve accuracy of its measurement
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrCalOneFreq(UINT8 i2cAddr, UINT8 tunerId, SINT32 F_REF, SINT32 P_REF)
#else
static MXL_STATUS MxL251_PwrCalOneFreq(UINT8 i2cAddr, UINT8 tunerId, SINT32 F_REF, REAL32 P_REF)
#endif
{
  SINT32 i;

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  for (i = 0; i < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++i)
  {
    const MXL_PWR_CAL_FREQ_RANGE_T* pT = &(devContextPtr->PwrCalFreqRangeTable[i]);
    SINT32 F_NB, F_WB;
    SINT32 F_BAND;

#ifndef _MXL251_BUILD_

    // F_REF_Mn    F_WB_Mn   F_WB_Md    F_WB_Mx   F_REF_Mx
    if (F_REF < pT->F_REF_Mn)
    {
      continue;
    }
    else if (F_REF < pT->F_WB_Mn)
    {
      // Largest integer multiple of 4 (or 3) within ( max(F_WB_Mn(i) - F_REF, 12), 48 - 4 (or 3)]
      F_NB = ((MXL_MAX((pT->F_WB_Mn - F_REF)/1000000 + 1, 12) + 2)/3)*3;
      F_NB = MXL_MIN(F_NB, 48-4);
      F_NB = -F_NB;
      // F_NB = -42;
    }
    else if (F_REF < pT->F_WB_Md)
    {
      F_NB = -12;
    }
    else if (F_REF < pT->F_WB_Mx)
    {
      F_NB = 12;
    }
    else if (F_REF < pT->F_REF_Mx)
    {
      // Smallest integer multiple of 4 (or 3) within ( max(F_REF - F_WB_ Mx(i), 12), 48 - 4 (or 3)]
      F_NB = ((MXL_MAX((F_REF - pT->F_WB_Mx)/1000000 + 1, 12) + 2)/3)*3;
      F_NB = MXL_MIN(F_NB, 48-4);
      // F_NB = 42; // ((MXL_MAX((pT->F_REF_Mx - F_REF)/1000000, 12) + 2)/3)*3;
    }
    else
    {
      continue;
    }

    F_NB *= 1000000;
    F_WB = F_REF - F_NB;
#else // _MXL251_BUILD_
    F_NB = 3000000; // by default always place LO to the left of channel center
    F_WB = F_REF - F_NB;

    // F_WB_Mn   F_WB_Mx
    if (F_WB < pT->F_WB_Mn || F_WB > pT->F_WB_Mx)
    {
      continue;
    }
#endif // _MXL251_BUILD_

    F_BAND = MxL251_PwrGetFreqBandIndex(devContextPtr, F_WB);

    // 251: do not calibration over full band mode
    // For all bands: calibrate with TCF off under full bandwidth
    if (MXL_TRUE != MxL251_PwrCalTuneMeasure(i2cAddr,
                                             tunerId,
                                             F_WB,
                                             F_NB,
                                             MXL_PWR_CAL_TCF_MODE_OFF,
#ifndef _MXL251_BUILD_
                                             PWR_CAL_NB_MODE_FULL_BAND_DEFAULT,
#endif // _MXL251_BUILD_
                                             P_REF))
    {
      return MXL_FALSE;
    }

    // If F_WB is in UHF2: calibrate with TCF on under full bandwidth
    if (MXL_PWR_CAL_FREQ_BAND_IDX_UHF21/*3*/ == F_BAND
       || MXL_PWR_CAL_FREQ_BAND_IDX_UHF22/*4*/ == F_BAND
        )
    {
      if (MXL_TRUE != MxL251_PwrCalTuneMeasure(i2cAddr,
                                               tunerId,
                                               F_WB,
                                               F_NB,
                                               MXL_PWR_CAL_TCF_MODE_ON,
#ifndef _MXL251_BUILD_
                                               PWR_CAL_NB_MODE_FULL_BAND_DEFAULT,
#endif // _MXL251_BUILD_
                                               P_REF))
      {
        return MXL_FALSE;
      }
    }

#ifndef _MXL251_BUILD_
    // Calibrate NB offset on all bandwidth modes if needed
    if (MXL_TRUE == MxL251_PwrCalNbCalNeeded(F_REF))
    {
      // If F_BAND if for UHF1/UHF21/UHF22 only
      MXL_PWR_CAL_NB_MODE_E bwMode;

      for (bwMode = PWR_CAL_NB_MODE_FULL_BAND_NBCAL; bwMode <= PWR_CAL_NB_MODE_SINGLECHAN_NBCAL; bwMode = (MXL_PWR_CAL_NB_MODE_E)(bwMode+1))
      {
        UINT32 iNB;
        for (iNB = 0; ; ++iNB)
        {
          // Go through all predefined NB offset defined for bandwidth mode iNB
          F_NB = PwrCalNBFreqList[bwMode-PWR_CAL_NB_MODE_FULL_BAND_NBCAL][iNB];
          if (F_NB == 0)
          {
            break;
          }

          F_WB = F_REF - F_NB;

          if (MXL_TRUE != MxL251_PwrCalTuneMeasure(i2cAddr,
                                                   tunerId,
                                                   F_WB,
                                                   F_NB,
                                                   MXL_PWR_CAL_TCF_MODE_OFF,
                                                   bwMode,
                                                   P_REF))
          {
            return MXL_FALSE;
          }
        }
      }
    }
#endif // _MXL251_BUILD_
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalGetRefPower
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Get reference power by linear interpolation from power profile
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrCalGetRefPower(PMXL_RX_PWR_CAL_T pwrCreateCalPtr, SINT32 f, SINT32* refPwrPtr)
#else
static MXL_STATUS MxL251_PwrCalGetRefPower(PMXL_RX_PWR_CAL_T pwrCreateCalPtr, SINT32 f, REAL32* refPwrPtr)
#endif
{
  UINT8 i;

#ifdef _MXL251_FIXEDPOINT_
  // FIXME: assuming power profile is sorted
  if ((UINT32)f < pwrCreateCalPtr->CalFreq[0].CalibFreqInHz)
  {
	//The vlaues are scaled up by 256; Bringing it to MXL251_PRECISION
    *refPwrPtr = pwrCreateCalPtr->CalFreq[0].ReferencePwrIndBmV;
	*refPwrPtr = MXL_DIV_SCALE64_S(*refPwrPtr, 256, MXL251_PRECISION);
    return MXL_TRUE;
  }

  if ((UINT32)f >= pwrCreateCalPtr->CalFreq[pwrCreateCalPtr->NumCalFreq-1].CalibFreqInHz)
  {
	//The vlaues are scaled up by 256; Bringing it to MXL251_PRECISION
    *refPwrPtr = pwrCreateCalPtr->CalFreq[pwrCreateCalPtr->NumCalFreq-1].ReferencePwrIndBmV;
	*refPwrPtr = MXL_DIV_SCALE64_S(*refPwrPtr, 256, MXL251_PRECISION);
    return MXL_TRUE;
  }

  for (i=0; i<pwrCreateCalPtr->NumCalFreq - 1; i++)
  {
    SINT32 f0 = (SINT32)pwrCreateCalPtr->CalFreq[i].CalibFreqInHz;
    SINT32 f1 = (SINT32)pwrCreateCalPtr->CalFreq[i+1].CalibFreqInHz;
	SINT64 temp;
	SINT64 ref;
    if (f >= f0 && f < f1)
    {
      SINT64 p0 = pwrCreateCalPtr->CalFreq[i].ReferencePwrIndBmV;  //8
      SINT64 p1 = pwrCreateCalPtr->CalFreq[i+1].ReferencePwrIndBmV;//8	  

	  temp = (p1-p0)* (f-f0);
	  temp = MXL_SCALEUP64_S(temp,MXL251_PRECISION);
	  ref  = MXL_SCALEUP64_S(p0, MXL251_PRECISION);
	  ref  += MXL_DIV64_S(temp, (f1-f0)); //(MXL251_PRECISION + 8)
	  ref  = MXL_DIV64_S(ref, 256); //MXL251_PRECISION
	  *refPwrPtr  = (SINT32)ref;

      //MxL_DLL_DEBUG0("refPwr={%f}", MXL_VAL64(*refPwrPtr));
	  MxL_DLL_DEBUG0("f=%d f0=%d f1=%d ", f, f0, f1);
      //MxL_DLL_DEBUG0("p0={%f} p1={%f}\r\n",(REAL32)p0, (REAL32)p1);
      return MXL_TRUE;
    }
  }
#else //_MXL251_FIXEDPOINT_
  // FIXME: assuming power profile is sorted
  if ((UINT32)f < pwrCreateCalPtr->CalFreq[0].CalibFreqInHz)
  {
    *refPwrPtr = (REAL32)(pwrCreateCalPtr->CalFreq[0].ReferencePwrIndBmV)/256.0f;
    return MXL_TRUE;
  }

  if ((UINT32)f >= pwrCreateCalPtr->CalFreq[pwrCreateCalPtr->NumCalFreq-1].CalibFreqInHz)
  {
    *refPwrPtr = (REAL32)(pwrCreateCalPtr->CalFreq[pwrCreateCalPtr->NumCalFreq-1].ReferencePwrIndBmV)/256.0f;
    return MXL_TRUE;
  }

  for (i=0; i<pwrCreateCalPtr->NumCalFreq - 1; i++)
  {
    SINT32 f0 = (SINT32)pwrCreateCalPtr->CalFreq[i].CalibFreqInHz;
    SINT32 f1 = (SINT32)pwrCreateCalPtr->CalFreq[i+1].CalibFreqInHz;
    if (f >= f0 && f < f1)
    {
      REAL32 p0 = (REAL32)(pwrCreateCalPtr->CalFreq[i].ReferencePwrIndBmV);
      REAL32 p1 = (REAL32)(pwrCreateCalPtr->CalFreq[i+1].ReferencePwrIndBmV);      
      *refPwrPtr = (REAL32)(p0 + ((p1-p0)*(REAL32)(f-f0))/(REAL32)(f1-f0))/256.0f;
	  MxL_DLL_DEBUG0("refPwr=%f f=%d f0=%d f1=%d p0=%f p1=%f\r\n",*refPwrPtr, f, f0, f1, p0, p1);
      return MXL_TRUE;
    }
  }
#endif //_MXL251_FIXEDPOINT_
  return MXL_FALSE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrGetQuadratic
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Get quadratic coefficients C2, C1, C0
--|
--| RETURN VALUE  : MXL_STATUS
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static MXL_STATUS MxL251_PwrGetQuadratic(SINT32 Xi[], SINT32 Oi[], UINT32 n, MXL_PWR_QUADRATIC_COEF_T* coefPtr)
#else
static MXL_STATUS MxL251_PwrGetQuadratic(REAL32 Xi[], REAL32 Oi[], UINT32 n, MXL_PWR_QUADRATIC_COEF_T* coefPtr)
#endif
{

  MxL_DLL_DEBUG0("%s - n=%d\r\n", __FUNCTION__, n);
  if (n == 1)
  {
    coefPtr->C2 = 0;
    coefPtr->C1 = 0;
    coefPtr->C0 = Oi[0];
  }
  else if (n == 2)
  {
    coefPtr->C2 = 0;
#ifdef _MXL251_FIXEDPOINT_
    coefPtr->C1 = MXL_DIV_SCALE64_S((Oi[1]-Oi[0]),(Xi[1]-Xi[0]), MXL251_PRECISION);
	if(MXL_IS_ZERO((Xi[1]-Xi[0]), MXL251_PRECISION))
#else
    coefPtr->C1 = (Oi[1]-Oi[0])/(Xi[1]-Xi[0]);
    if (MXL_IS_REAL32_ZERO(Xi[1]-Xi[0]))
#endif
    {
      MxL_DLL_DEBUG0("%s - divide by 0 (Xi[1]-Xi[0])\r\n", __FUNCTION__);
      return MXL_FALSE;
    }
#ifdef _MXL251_FIXEDPOINT_
    coefPtr->C0 = MXL_DIV_SCALE64_S((Oi[0]*Xi[1]-Oi[1]*Xi[0]),(Xi[1]-Xi[0]), MXL251_PRECISION);
#else
	coefPtr->C0 = (Oi[0]*Xi[1]-Oi[1]*Xi[0])/(Xi[1]-Xi[0]);
#endif
  }
  else if (n >= 3)
  {
    UINT32 i;
#ifdef _MXL251_FIXEDPOINT_
    SINT64 S21 = 0;
    SINT64 S11 = 0;
    SINT64 S01 = 0;
    SINT64 S40 = 0;
    SINT64 S30 = 0;
    SINT64 S20 = 0;
    SINT64 S10 = 0;
    SINT64 S00; 
    SINT64 D;
	SINT64 temp;
	SINT64 temp_S40;
	SINT64 oi,xi;
	SINT64 oixi,oixixi, xixi, xi3;
	SINT64 t;
    static UINT8 debugCount = 0;
	debugCount++;
#else
    REAL32 S21 = 0.0;
    REAL32 S11 = 0.0;
    REAL32 S01 = 0.0;
    REAL32 S40 = 0.0;
    REAL32 S30 = 0.0;
    REAL32 S20 = 0.0;
    REAL32 S10 = 0.0;
    REAL32 S00 = (REAL32)n;
    REAL32 D;
#endif

#ifdef  _MXL251_FIXEDPOINT_
#define MXL251_PRECISION1    25
#define MXL1_VAL(x)		     MXL_HEX_TO_REAL32(x, MXL251_PRECISION1)
#define MXL1_VAL64(x) ((x>0) ? ((REAL32)((UINT64)(x) / (REAL32)(1 << (MXL251_PRECISION1)))): ((REAL32)((SINT64)(x) / (REAL32)(1 << (MXL251_PRECISION1)))))
	
	S00 = MXL_SCALEUP(n, MXL251_PRECISION1);
    for (i = 0; i < n; ++i)
    {
      //MxL_DLL_DEBUG0("Xi[%d]=%x Oi[%d]=%x\r\n", i, Xi[i], i, Oi[i]); 
	  //MxL_DLL_DEBUG0("Xi[%d]=%f Oi[%d]=%f\r\n", i, MXL_VAL(Xi[i]), i, MXL_VAL(Oi[i]));
	  /*   S01 += Oi[i];
      S11 += Oi[i]*Xi[i];
      S21 += Oi[i]*Xi[i]*Xi[i];
      S10 += Xi[i];
      S20 += Xi[i]*Xi[i];
      S30 += Xi[i]*Xi[i]*Xi[i];
      S40 += Xi[i]*Xi[i]*Xi[i]*Xi[i];
	  */	
	  oi = MXL_SCALEUP64_S(Oi[i],(MXL251_PRECISION1-MXL251_PRECISION));
	  xi = MXL_SCALEUP64_S(Xi[i],(MXL251_PRECISION1-MXL251_PRECISION));
      //MxL_DLL_DEBUG0("Xi[%d]={%f} Oi[%d]={%f}\r\n", i, MXL1_VAL64(xi), i, MXL1_VAL64(oi));
      
	  oixi   = MXL_MUL64_S(oi,   xi, MXL251_PRECISION1);
      oixixi = MXL_MUL64_S(oixi, xi, MXL251_PRECISION1);	  
	  xixi   = MXL_MUL64_S(xi,   xi, MXL251_PRECISION1);
	  xi3    = MXL_MUL64_S(xixi, xi, MXL251_PRECISION1);
	  S01 += oi;
	  S11 += oixi;
	  S21 += oixixi;
      S10 += xi;	  
	  S20 += xixi;      
	  S30 += xi3;
      //S40 += (SINT64)((xixi * xixi / (1 << MXL251_PRECISION1) ) + 0.5);//RJ: to check overflow!	  
      temp_S40 = MXL_DIV64_S(xixi * xixi, (1 << MXL251_PRECISION1));
      S40 += temp_S40;
#if 0
      MxL_DLL_DEBUG0("S01={%f} S11={%f} S21={%f} S10={%f}  S20={%f} S30=%f S40=%f \r\n", \
      MXL1_VAL64(S01),MXL1_VAL64(S11),MXL1_VAL64(S21),MXL1_VAL64(S10),MXL1_VAL64(S20),MXL1_VAL64(S30),MXL1_VAL64(S40));
#endif
    }

	//D = (S00*S20*S40 - S10*S10*S40 - S00*S30*S30 + 2*S10*S20*S30 - S20*S20*S20);
	D  = MXL_MUL64_S(MXL_MUL64_S(S00,S20,MXL251_PRECISION1),   S40, MXL251_PRECISION1);
	D -= MXL_MUL64_S(MXL_MUL64_S(S10,S10,MXL251_PRECISION1),   S40, MXL251_PRECISION1);
	D -= MXL_MUL64_S(MXL_MUL64_S(S00,S30,MXL251_PRECISION1),   S30, MXL251_PRECISION1);
	D += 2* MXL_MUL64_S(MXL_MUL64_S(S10,S20,MXL251_PRECISION1),S30, MXL251_PRECISION1);
	D -= MXL_MUL64_S(MXL_MUL64_S(S20,S20,MXL251_PRECISION1),   S20, MXL251_PRECISION1);
    //MxL_DLL_DEBUG0("D={%f}\n", MXL1_VAL64(D));

    if (MXL_IS_ZERO(D, MXL251_PRECISION1))
    {
      MxL_DLL_DEBUG0("%s - divide by 0\r\n", __FUNCTION__);
      return MXL_FALSE;
    }
    //coefPtr->C0 = (S01*S20*S40 - S11*S10*S40 - S01*S30*S30 + S11*S20*S30 + S21*S10*S30 - S21*S20*S20)/D;
	/*
	temp  = MXL_MUL64_S(MXL_MUL64_S(S01, S20, MXL251_PRECISION1 ), S40, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S11, S10, MXL251_PRECISION1 ), S40, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S01, S30, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);	
	temp += MXL_MUL64_S(MXL_MUL64_S(S11, S20, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S21, S10, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S21, S20, MXL251_PRECISION1 ), S20, MXL251_PRECISION1);*/

	t  = MXL_MUL64_S(MXL_MUL64_S(S01, S20, MXL251_PRECISION1 ), S40, MXL251_PRECISION1);
	temp = t;
	t = MXL_MUL64_S(MXL_MUL64_S(S11, S10, MXL251_PRECISION1 ), S40, MXL251_PRECISION1);
	temp -= t; 
	t = MXL_MUL64_S(MXL_MUL64_S(S01, S30, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);
	temp -= t;
	t =  MXL_MUL64_S(MXL_MUL64_S(S11, S20, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);
	temp += t;
	t = MXL_MUL64_S(MXL_MUL64_S(S21, S10, MXL251_PRECISION1 ), S30, MXL251_PRECISION1);
	temp += t;
	t = MXL_MUL64_S(MXL_MUL64_S(S21, S20, MXL251_PRECISION1 ), S20, MXL251_PRECISION1);
	temp -= t;
	
	coefPtr->C0 = (SINT32)(MXL_DIV_SCALE64_S(temp , D, MXL251_PRECISION1));
	
    //coefPtr->C1 = (S11*S00*S40 - S01*S10*S40 + S01*S20*S30 - S21*S00*S30 - S11*S20*S20 + S21*S10*S20)/D;
	temp  = MXL_MUL64_S(MXL_MUL64_S(S11, S00, MXL251_PRECISION1), S40, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S01, S10, MXL251_PRECISION1), S40, MXL251_PRECISION1);
	temp += MXL_MUL64_S(MXL_MUL64_S(S01, S20, MXL251_PRECISION1), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S21, S00, MXL251_PRECISION1), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S11, S20, MXL251_PRECISION1), S20, MXL251_PRECISION1);
	temp += MXL_MUL64_S(MXL_MUL64_S(S21, S10, MXL251_PRECISION1), S20, MXL251_PRECISION1);
	coefPtr->C1 = (SINT32)(MXL_DIV_SCALE64_S(temp, D, MXL251_PRECISION1));

    //coefPtr->C2 = (S01*S10*S30 - S11*S00*S30 - S01*S20*S20 + S11*S10*S20 + S21*S00*S20 - S21*S10*S10)/D;
	temp  = MXL_MUL64_S(MXL_MUL64_S(S01, S10, MXL251_PRECISION1), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S11, S00, MXL251_PRECISION1), S30, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S01, S20, MXL251_PRECISION1), S20, MXL251_PRECISION1);
	temp += MXL_MUL64_S(MXL_MUL64_S(S11, S10, MXL251_PRECISION1), S20, MXL251_PRECISION1);
	temp += MXL_MUL64_S(MXL_MUL64_S(S21, S00, MXL251_PRECISION1), S20, MXL251_PRECISION1);
	temp -= MXL_MUL64_S(MXL_MUL64_S(S21, S10, MXL251_PRECISION1), S10, MXL251_PRECISION1);
	coefPtr->C2 = (SINT32)(MXL_DIV_SCALE64_S(temp, D, MXL251_PRECISION1));
	coefPtr->C0 = MXL_SCALEDOWN(coefPtr->C0,(MXL251_PRECISION1-MXL251_PRECISION)); 
	coefPtr->C1 = MXL_SCALEDOWN(coefPtr->C1,(MXL251_PRECISION1-MXL251_PRECISION));  
	coefPtr->C2 = MXL_SCALEDOWN(coefPtr->C2,(MXL251_PRECISION1-MXL251_PRECISION)); 
    //MxL_DLL_DEBUG0("C0={%f} C1={%f} C2={%f}\r\n", MXL_VAL(coefPtr->C0), MXL_VAL(coefPtr->C1), MXL_VAL(coefPtr->C2));
	
#else //_MXL251_FIXEDPOINT_
    for (i = 0; i < n; ++i)
    {
	  MxL_DLL_DEBUG0("Xi[%d]=%f Oi[%d]=%f\r\n", i, Xi[i], i, Oi[i]);
      S01 += Oi[i];
      S11 += Oi[i]*Xi[i];
      S21 += Oi[i]*Xi[i]*Xi[i];
      S10 += Xi[i];
      S20 += Xi[i]*Xi[i];
      S30 += Xi[i]*Xi[i]*Xi[i];
      S40 += Xi[i]*Xi[i]*Xi[i]*Xi[i];
	  MxL_DLL_DEBUG0("S01={%f} S11=%f S21={%f} S10=%f  S20={%f} S30=%f S40=%f \r\n", S01,S11,S21,S10,S20,S30,S40);
    }	
    D = (S00*S20*S40 - S10*S10*S40 - S00*S30*S30 + 2*S10*S20*S30 - S20*S20*S20);
	MxL_DLL_DEBUG0("D={%f}\n", D);
    if (MXL_IS_REAL32_ZERO((D)))
    {
      MxL_DLL_DEBUG0("%s - divide by 0\r\n", __FUNCTION__);
      return MXL_FALSE;
    }
    coefPtr->C0 = (S01*S20*S40 - S11*S10*S40 - S01*S30*S30 + S11*S20*S30 + S21*S10*S30 - S21*S20*S20)/D;
    coefPtr->C1 = (S11*S00*S40 - S01*S10*S40 + S01*S20*S30 - S21*S00*S30 - S11*S20*S20 + S21*S10*S20)/D;
    coefPtr->C2 = (S01*S10*S30 - S11*S00*S30 - S01*S20*S20 + S11*S10*S20 + S21*S00*S20 - S21*S10*S10)/D;

	MxL_DLL_DEBUG0("C0=%f C1=%f C2=%f\r\n", coefPtr->C0, coefPtr->C1, coefPtr->C2);
#endif //_MXL251_FIXEDPOINT_
  }


  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalCalcTempComp
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Calculate temperature compensation coefficients
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalCalcTempComp(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
#ifdef _POWER_REPORTING_TEMP_COMP_ENABLED_
  devContextPtr->MxLNVRAMFile.PwrTempComp.Header.Signature = MXL_PWR_COEF_TABLE_SIGNATURE;
#endif // _POWER_REPORTING_TEMP_COMP_ENABLED_
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalCalcTiltComp
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Calculate tilt compensation coefficients
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalCalcTiltComp(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
  UINT32 i;
  MXL_PWR_CAL_LOG_ENTRY_T* p;
  UINT32 list[MXL_PWR_CAL_MAX_CAL_POINTS];
#ifdef _MXL251_FIXEDPOINT_
  SINT32 Oi[MXL_PWR_CAL_MAX_CAL_POINTS];
  SINT32 Xi[MXL_PWR_CAL_MAX_CAL_POINTS];
#else
  REAL32 Oi[MXL_PWR_CAL_MAX_CAL_POINTS];
  REAL32 Xi[MXL_PWR_CAL_MAX_CAL_POINTS];
#endif
  MXL_PWR_QUADRATIC_COEF_T* coefPtr;
  UINT32  n;
  UINT8   tunerId;

  for (tunerId = TUNER0; tunerId <= TUNER1; ++tunerId)
  {
    MxL_DLL_DEBUG0("%s - tuner=%d PwrCalLog[].numEntries=%d\r\n",
        __FUNCTION__, tunerId, PwrCalLog[tunerId].numEntries);

    coefPtr = &(devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Coef);
    n = 0;
    // FIXME: assuming all frequencies are sorted
    for (i = 0; i < PwrCalLog[tunerId].numEntries; ++i)
    {
      if (i < (PwrCalLog[tunerId].numEntries - 1))
      {
        p = &PwrCalLog[tunerId].table[i];
        if (   p[0].TCFmode == MXL_PWR_CAL_TCF_MODE_OFF
            && p[1].TCFmode == MXL_PWR_CAL_TCF_MODE_ON
            && MXL_PWR_UNDEFINED_POWER < p[0].RX_PWR
            && MXL_PWR_UNDEFINED_POWER < p[1].RX_PWR
            )
        {
          list[n] = i;
          n++;
        }
      }
    }

    MxL251_PwrInitQuadratic(coefPtr);

    if (n == 0)
    {
      MxL_DLL_ERROR0("%s - empty log\n", __FUNCTION__);
      return MXL_FALSE;
    }

    p = &PwrCalLog[tunerId].table[list[n/2]];
    coefPtr->F_C = p->F_WB + p->F_NB;
    coefPtr->F_D = 96000000;

    for (i = 0; i < n; ++i)
    {
      p = &PwrCalLog[tunerId].table[list[i]];
#ifdef _MXL251_FIXEDPOINT_
      Oi[i] = (SINT32)(p[1].RX_PWR - p[0].RX_PWR);
      Xi[i] = (SINT32)(MXL_DIV_SCALE64_S(((p->F_WB + p->F_NB) - coefPtr->F_C),coefPtr->F_D, MXL251_PRECISION));
#else
      Oi[i] = p[1].RX_PWR - p[0].RX_PWR;
      Xi[i] = ((REAL32)(p->F_WB + p->F_NB) - coefPtr->F_C)/coefPtr->F_D;
#endif
    }

    if (MXL_TRUE != MxL251_PwrGetQuadratic(Xi, Oi, n, coefPtr))
    {
      return MXL_FALSE;
    }
    devContextPtr->MxLNVRAMFile.PwrTiltComp[tunerId].Header.Signature = MXL_PWR_COEF_TABLE_SIGNATURE;
  }
  MxL_DLL_DEBUG0("%s - end\r\n", __FUNCTION__);

  return MXL_TRUE;
}

#ifndef _MXL251_BUILD_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalGetNbCalFreqIndex
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Get NB Calibration Frequency Index according to F_NB
--|
--| RETURN VALUE  : <0 if failed, [0,3]: actual index
--|
--|-------------------------------------------------------------------------------------*/

static SINT32 MxL251_PwrCalGetNbCalFreqIndex(MXL_PWR_CAL_NB_MODE_E nbMode, SINT32 F_NB)
{
  const SINT32* pc = &PwrCalNBFreqList[nbMode-PWR_CAL_NB_MODE_FULL_BAND_NBCAL][0];
  SINT32 iFreq = 0;
  while (*pc)
  {
    if ((*pc) == F_NB)
    {
      return iFreq;
    }
    iFreq++;
    pc++;
  }
  return -1;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalPopulateNbFreqComp
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Populate NB Calibration Compensation data to other bands
--|                 If srcBand is the first calibrated band, populate to [0, MXL_PWR_CAL_NUM_OF_FREQ_BANDS)
--|                 If srcBand is not first calibrated band, populate to [srcBand+1, MXL_PWR_CAL_NUM_OF_FREQ_BANDS)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalPopulateNbFreqComp(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT32 tunerId, SINT32 srcBand, SINT32 prevCalBand)
{
  SINT32 i;
  SINT32 j;
  SINT32 dstBand;
  if (prevCalBand >= 0)
  {
    // If it's not first calibrated band, populate to [srcBand+1, end)
    dstBand = srcBand + 1;
  }
  else
  {
    // If it's first calibrated band populate to [0, end)
    dstBand = 0;
  }

 for (; dstBand < MXL_PWR_CAL_NUM_OF_FREQ_BANDS; ++dstBand)
 {
   MxL_DLL_DEBUG0("%s - copying from %d to %d\r\n", __FUNCTION__, srcBand, dstBand);
   if (dstBand != srcBand)
   {
     for (i = 0; i < MXL_PWR_CAL_NUM_BW_MODES/*2*/; ++i)
     {
       for (j = 0; j < MXL_PWR_CAL_MAX_NBCAL_PT; ++j)
       {
         devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[i][dstBand][j] = devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[i][srcBand][j];
       }
     }
     devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_SCH_NB[dstBand] = devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_SCH_NB[srcBand];
   }
 }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalCalcNBFreqComp
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Calculate NB frequency compensation coefficients
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalCalcNBFreqComp(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
  UINT32 i;
  MXL_PWR_CAL_LOG_ENTRY_T* p;
  MXL_PWR_CAL_NB_MODE_E nbMode;
  REAL32 sum[MXL_PWR_CAL_MAX_NBCAL_PT];
  UINT32 n[MXL_PWR_CAL_MAX_NBCAL_PT];
  SINT32 iFreq;
  SINT32 iMode;
  REAL32 offset00;
  UINT8  tunerId;
  SINT32 F_BAND;
  SINT32 prevCalBand; // Last calibrated band

  for (tunerId = TUNER0; tunerId <= TUNER1; ++tunerId)
  {
    prevCalBand = -1; // Reset last calibrated band (to detect if current band is first calibrated one)

    for (F_BAND = 0; F_BAND < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++F_BAND)
    {
      MxL_DLL_DEBUG0("%s - F_BAND=%d\n", __FUNCTION__, F_BAND);
      // devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[bwMode][freqBandIdx][]
      for (nbMode = PWR_CAL_NB_MODE_FULL_BAND_NBCAL; nbMode <= PWR_CAL_NB_MODE_SINGLECHAN_NBCAL; nbMode = (MXL_PWR_CAL_NB_MODE_E)(nbMode+1))
      {
        // Clear accumulators for averaging
        for (i = 0; i < MXL_PWR_CAL_MAX_NBCAL_PT; ++i)
        {
          n[i] = 0;
          sum[i] = 0;
        }

        // Group data by NB offset for F_BAND only
        for (i = 0; i < PwrCalLog[tunerId].numEntries; ++i)
        {
          p = &PwrCalLog[tunerId].table[i];
          if (MXL_PWR_UNDEFINED_POWER < p->RX_PWR
              && nbMode == p->NB
              && F_BAND == (SINT32)(p->F_BAND)
              )
          {
            iFreq = MxL251_PwrCalGetNbCalFreqIndex(nbMode, p->F_NB);
            if (iFreq >= 0)
            {
              sum[iFreq] += p->P_REF - p->RX_PWR;
              n[iFreq]++;
            }
          }
        }

        if (0 == n[0])
        {
          // No data for this mode
          break;
        }

        // Populate results
        for (iFreq = 0; iFreq < MXL_PWR_CAL_MAX_NBCAL_PT; ++iFreq)
        {
          iMode = ((SINT32)nbMode - (SINT32)PWR_CAL_NB_MODE_FULL_BAND_NBCAL);

          if (0 == PwrCalNBFreqList[iMode][iFreq])
          {
            break;
          }

          if (0 == n[iFreq])
          {
            // No point
            MxL_DLL_ERROR0("%s - no calibration points found on NB offset %d\n",
                __FUNCTION__,
                PwrCalNBFreqList[iMode][iFreq]);
            return MXL_FALSE;
          }

          // At least one point
          if (iMode < 2)
          {
            // Full or Half bandwidth
            devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[iMode][F_BAND][iFreq] = sum[iFreq]/n[iFreq];
            devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].FREQ_NB  [iMode][iFreq] = PwrCalNBFreqList[iMode][iFreq];
            MxL_DLL_DEBUG0("%s - F_BAND=%d iMode=%d iFreq=%d FREQ_NB=%d n=%d\r\n",
                __FUNCTION__,
                F_BAND,
                iMode,
                iFreq,
                PwrCalNBFreqList[iMode][iFreq],
                n[iFreq]
                );
          }
          else // PWR_CAL_NB_MODE_SINGLECHAN_NBCAL
          {
            // Single channel
            devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_SCH_NB[F_BAND] = sum[iFreq]/n[iFreq];
          }
        }
      } // end of nbMode


      if (0 != n[0])
      {
        // Calculate offset00 base on the average of middle points
        offset00 = (devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[0][F_BAND][MXL_PWR_CAL_MAX_NBCAL_PT/2 - 1]
            + devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[0][F_BAND][MXL_PWR_CAL_MAX_NBCAL_PT/2 - 0])/2;

        // Subtract offset00 from all coefficients
        for (iMode = 0; iMode < 2; ++iMode)
        {
          for (iFreq = 0; iFreq < MXL_PWR_CAL_MAX_NBCAL_PT; ++iFreq)
          {
            devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_NB[iMode][F_BAND][iFreq] -= offset00;
          }
        }

        devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].OFFSET_SCH_NB[F_BAND] -= offset00;

        MxL251_PwrCalPopulateNbFreqComp(devContextPtr, tunerId, F_BAND, prevCalBand);

        prevCalBand = F_BAND;
      }

    } // end of F_BAND

    devContextPtr->MxLNVRAMFile.PwrNBFreqComp[tunerId].Header.Signature = MXL_PWR_COEF_TABLE_SIGNATURE;

  } // end of tunerId
  return MXL_TRUE;
}
#endif // _MXL251_BUILD_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalCalcFreqComp
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : Calculate frequency compensation coefficients
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_PwrCalCalcFreqComp(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
  UINT32 i;
  MXL_PWR_CAL_LOG_ENTRY_T* p;
  UINT32 list[MXL_PWR_CAL_MAX_CAL_POINTS];
#ifdef _MXL251_FIXEDPOINT_
  SINT32 Oi[MXL_PWR_CAL_MAX_CAL_POINTS];
  SINT32 Xi[MXL_PWR_CAL_MAX_CAL_POINTS];
#else
  REAL32 Oi[MXL_PWR_CAL_MAX_CAL_POINTS];
  REAL32 Xi[MXL_PWR_CAL_MAX_CAL_POINTS];
#endif
  MXL_PWR_QUADRATIC_COEF_T* coefPtr;
  UINT32 n;
  UINT8 tunerId;
  SINT32 F_BAND;

  for (tunerId = TUNER0; tunerId <= TUNER1; ++tunerId)
  {
    for (F_BAND = 0; F_BAND < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++F_BAND)
    {
      coefPtr = &(devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Coef[F_BAND]);
      n = 0;
      // FIXME: assuming all frequencies are sorted
      for (i = 0; i < PwrCalLog[tunerId].numEntries; ++i)
      {
        p = &PwrCalLog[tunerId].table[i];
        if (   MXL_PWR_UNDEFINED_POWER < p->RX_PWR
            && F_BAND == p->F_BAND
            && MXL_PWR_CAL_TCF_MODE_OFF == p->TCFmode
#ifndef _MXL251_BUILD_
            && PWR_CAL_NB_MODE_FULL_BAND_DEFAULT == p->NB
#endif // _MXL251_BUILD_
            )
        {
          list[n] = i;
          n++;
        }
      }
      MxL_DLL_DEBUG0("%s - # data points = %d\r\n", __FUNCTION__, n);

      MxL251_PwrInitQuadratic(coefPtr);

      if (n == 0)
      {
        continue; // Move to next band
      }

      p = &PwrCalLog[tunerId].table[list[n/2]];
      coefPtr->F_C = p->F_WB + p->F_NB;
      MxL_DLL_DEBUG0("%s - F_C=list[%d]=%d\r\n", __FUNCTION__, list[n/2], coefPtr->F_C);
      coefPtr->F_D = 96000000;

      for (i = 0; i < n; ++i)
      {

        p = &PwrCalLog[tunerId].table[list[i]];
#ifndef _MXL251_BUILD_
        {
         REAL32 C_NB;
         if (MXL_TRUE != MxL251_PwrGetC_NB(devContextPtr, tunerId, F_BAND, p->F_NB, WB_96_MHz, &C_NB))
         {
           return MXL_FALSE;
         }
         //MxL_DLL_DEBUG0("PwrFreqComp: O[%d]=%f - %f - %f\r\n", i, p->P_REF, p->RX_PWR, C_NB);
         Oi[i] = p->P_REF - p->RX_PWR - C_NB;
		}
#else // _MXL251_BUILD_
#ifdef _MXL251_FIXEDPOINT_
	    Oi[i] = (SINT32)(p->P_REF - p->RX_PWR);
        //MxL_DLL_DEBUG0("PwrFreqComp: O[%d]={%f} - {%f}\r\n", i, MXL_VAL64(p->P_REF), MXL_VAL64(p->RX_PWR));
#else	//#ifdef _MXL251_FIXEDPOINT_
		Oi[i] = (p->P_REF - p->RX_PWR);
		MxL_DLL_DEBUG0("PwrFreqComp: O[%d]=%f - %f\r\n", i, p->P_REF, p->RX_PWR);
#endif	//#ifdef _MXL251_FIXEDPOINT_


#endif // _MXL251_BUILD_

#ifdef _MXL251_FIXEDPOINT_
		Xi[i] = (SINT32)(MXL_DIV_SCALE64_S(((p->F_WB + p->F_NB) - coefPtr->F_C),coefPtr->F_D, MXL251_PRECISION));
#else
        Xi[i] = ((REAL32)(p->F_WB + p->F_NB) - coefPtr->F_C)/coefPtr->F_D;
#endif //_MXL251_FIXEDPOINT_
      }

      if (MXL_TRUE != MxL251_PwrGetQuadratic(Xi, Oi, n, coefPtr))
      {
        return MXL_FALSE;
      }
    }
    devContextPtr->MxLNVRAMFile.PwrFreqComp[tunerId].Header.Signature = MXL_PWR_COEF_TABLE_SIGNATURE;
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrLoadCoef
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/30/2010
--|
--| DESCRIPTION   : Load Pwr coef
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_PwrLoadCoef(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT8* BufPtr, UINT32 BufLen)
{
  MXL_NVRAM_FILE_T* filePtr;

  MXL_NVRAM_FILE_T tmpFile;

  // Initialize MxLNVRAMFile if not done so
  if (MXL_NVRAM_FILE_SIGNATURE != devContextPtr->MxLNVRAMFile.Header.Signature)
  {
    MxL251_PwrCoefInit(devContextPtr);
  }

  // If buffer is not provided, use NVRAM file
  if (0 == BufPtr || 0 == BufLen)
  {
    if (MXL_TRUE != MxL251_Ctrl_LoadMxLNVRAMFile(devContextPtr->i2cSlaveAddr, (UINT8*)&tmpFile, sizeof(tmpFile)))
    {
      return MXL_FALSE;
    }
    BufPtr = (UINT8*)&tmpFile;
    BufLen = sizeof(tmpFile);
  }

  filePtr = (MXL_NVRAM_FILE_T*)BufPtr;

  MxL_DLL_DEBUG0("%s - MxLNVRAMFile passed from buffer: Signature=%d FmtVersion=%d fileLen=%d\n",
    __FUNCTION__,
    filePtr->Header.Signature,
    filePtr->Header.FmtVersion,
    filePtr->Header.Length);

  if (BufLen < sizeof(devContextPtr->MxLNVRAMFile) || sizeof(devContextPtr->MxLNVRAMFile) != filePtr->Header.Length)
  {
    MxL_DLL_ERROR0("%s - invalid file format\n", __FUNCTION__);
    return MXL_FALSE;
  }

  if (MXL_NVRAM_FILE_SIGNATURE  != filePtr->Header.Signature)
  {
    MxL_DLL_ERROR0("%s - invalid file signature\n", __FUNCTION__);
    return MXL_FALSE;
  }

  if (MXL_NVRAM_FILE_FMTVERSION != filePtr->Header.FmtVersion)
  {
    MxL_DLL_ERROR0("%s - invalid file format version %d (%d is required)\n",
        __FUNCTION__,
        filePtr->Header.FmtVersion,
        MXL_NVRAM_FILE_FMTVERSION);
    return MXL_FALSE;
  }

  MxL251_MemCpy(&(devContextPtr->MxLNVRAMFile), filePtr, sizeof(devContextPtr->MxLNVRAMFile));
  // TODO: sectional copy

  if (4 != devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands)
  {
    // For backward compatibility
    // Existing customers should have 0;
    // It's 4 only if new API is being used
    devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands = 5;
  }

  MxL251_PwrUpdateCalFreqRangeTable(devContextPtr, devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands);

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrUpdateCoefTablesFromLog
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 09/30/2010
--|
--| DESCRIPTION   : Update Pwr coefficient tables
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

static void MxL251_PwrUpdateCalibCoefFromLog(PMXL251SF_DEV_CONTEXT_T devContextPtr)
{
  if (MXL_NVRAM_FILE_SIGNATURE != devContextPtr->MxLNVRAMFile.Header.Signature)
  {
    // Make sure returns valid table
    MxL251_PwrCoefInit(devContextPtr);
  }

  if (PwrCalLog[TUNER0].numEntries || PwrCalLog[TUNER1].numEntries)
  {
    // Calculate coeficients
    MxL251_PwrCalCalcTempComp(devContextPtr);
    MxL251_PwrCalCalcTiltComp(devContextPtr);
#ifndef _MXL251_BUILD_
    MxL251_PwrCalCalcNBFreqComp(devContextPtr);
#endif // _MXL251_BUILD_
    MxL251_PwrCalCalcFreqComp(devContextPtr);
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalOneRefFrequency
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 11/02/2010
--|
--| DESCRIPTION   : Performes power calibration on one reference frequency
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_PwrCalOneRefFrequency(PMXL_RX_PWR_CAL_T pwrCreateCalPtr, UINT32 F_REF)
{
#ifdef _MXL251_FIXEDPOINT_
  SINT32  P_REF;
#else
  REAL32  P_REF;
#endif
  UINT8  tunerId; // TODO:

  if (MXL_TRUE != MxL251_PwrCalGetRefPower(pwrCreateCalPtr, F_REF, &P_REF))
  {
    return MXL_FALSE;
  }

  for (tunerId = TUNER0; tunerId <= TUNER1; ++tunerId)
  {
    if (MXL_TRUE != MxL251_PwrCalOneFreq(pwrCreateCalPtr->I2cSlaveAddr, tunerId, F_REF, P_REF))
    {
      return MXL_FALSE;
    }
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_PwrCalDebug
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 11/04/2010
--|
--| DESCRIPTION   : Power calibration debug
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_PwrCalDebug(PMXL_RX_PWR_CAL_T pwrCreateCalPtr, UINT16 calFreqStepMHz)
{
  UINT8  i2cAddr = pwrCreateCalPtr->I2cSlaveAddr;
  UINT8  tunerId;
#ifdef _MXL251_FIXEDPOINT_
  SINT32 P_REF;
#else
  REAL32 P_REF;
#endif
  SINT32 F_REF;

  SINT32 F_WB;
  SINT32 freqWbStartHz;
  SINT32 freqWbEndHz;
  SINT32 freqWbStepHz;

  SINT32 F_NB;
  SINT32 freqNbStartHz;
  SINT32 freqNbEndHz;
  SINT32 freqNbStepHz;

  // Fetched from MB registers
  UINT16 bwMode;
  UINT16 tunerMap;
  UINT16 WbCenterFreqMHz;
  SINT16 NbOffsetFreqMHz;
  UINT16 regData;
  UINT16 wbStepMHz = calFreqStepMHz&0xFF;       // Low  byte: wbStep
  UINT16 nbStepMHz = (calFreqStepMHz>>8)&0xFF;  // High byte: nbStep

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_TUNER_MAP, &tunerMap))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_BW_MODE, &bwMode))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_F_WB_MHZ, &WbCenterFreqMHz))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_NB_OFFSET, &regData))
  {
    return MXL_FALSE;
  }
  NbOffsetFreqMHz = (SINT16)((SINT8)regData);

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_PWR_CAL_DEBUG_FLAG, &regData))
  {
    return MXL_FALSE;
  }

  devContextPtr->PwrCalCompAtScan = (regData&PWR_CAL_DEBUG_BIT_ENABLE_COMPENSATION)?POWER_CAL_ENABLE_COMP:POWER_CAL_DISABLE_COMP;

  // Setup NB offset range

  freqNbStepHz = (SINT32)nbStepMHz*1000000;
  if (0 == freqNbStepHz)
  {
    // Use fixed NB offset (specified by NbOffsetFreqMHz)
    freqNbStartHz = NbOffsetFreqMHz*1000000;
    freqNbEndHz   = NbOffsetFreqMHz*1000000;
    freqNbStepHz  = 6000000; // Set to any non-0 step
  }
  else
  {
    // NB scan range differs by bandwith modes
    if (bwMode == 0)
    {
      // full bandwith
      freqNbStartHz = -45000000;
      freqNbEndHz   =  45000000;
    }
    else
    {
      // half bandwith
      freqNbStartHz = -21000000;
      freqNbEndHz   =  21000000;
    }
  }

  if (WbCenterFreqMHz)
  {
    // Fixed WB center, and scan NB only
    freqWbStartHz = ((SINT32)WbCenterFreqMHz)*1000000;
    freqWbEndHz   = ((SINT32)WbCenterFreqMHz)*1000000;
    freqWbStepHz  = 1000000; // Any non-0
  }
  else
  {
    // Scan WB with full range from 50 to 1002 MHz
    freqWbStartHz = 50*1000000;
    freqWbEndHz   = 1002*1000000;
    freqWbStepHz  = (SINT32)wbStepMHz*1000000;
  }

  // Default to tuner0 only, unless specified with non-zero map
  if (0 == tunerMap) tunerMap = 1;

  for (tunerId = TUNER0; tunerId <= TUNER1; ++tunerId)
  {
    if (tunerMap & 1)
    {
      for (F_WB = freqWbStartHz; F_WB <= freqWbEndHz; F_WB += freqWbStepHz)
      {
        for (F_NB = freqNbStartHz; F_NB <= freqNbEndHz; F_NB += freqNbStepHz)
        {
          F_REF = F_WB + F_NB;

          if (F_NB == 0 || F_REF < 40000000 || F_REF > 1001000000)
          {
            // do not scan on 0 offset
            continue;
          }

          if (MXL_TRUE != MxL251_PwrCalGetRefPower(pwrCreateCalPtr, F_REF, &P_REF))
          {
            return MXL_FALSE;
          }

          if (MXL_TRUE != MxL251_PwrCalTuneMeasure(i2cAddr,
                tunerId,
                F_WB,
                F_NB,
                MXL_PWR_CAL_TCF_MODE_OFF,
#ifndef _MXL251_BUILD_
                bwMode==0?PWR_CAL_NB_MODE_FULL_BAND_NBCAL:PWR_CAL_NB_MODE_HALF_BAND_NBCAL,
#endif // _MXL251_BUILD_
                P_REF))
          {
            return MXL_FALSE;
          }
        }
      }
    }
    tunerMap >>= 1;
  }

  return MXL_TRUE;
}


/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigTunerCreatePwrCalCoef - MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : This function is used to make 251 rx power meter to be
--|                 calibrated to improve accuracy of its measurement
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_ConfigTunerCreatePwrCalCoef(PMXL_RX_PWR_CAL_T pwrCreateCalPtr)
{
  UINT32 i;
  UINT16 calFreqStepMHz = 0;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(pwrCreateCalPtr->I2cSlaveAddr);
  MXL_STATUS status = MXL_TRUE;
  UINT16 savedTiltFlag;

  MxL_DLL_DEBUG0("MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG - i2cAddr=0x%x, NumCalFreq=%d\n", pwrCreateCalPtr->I2cSlaveAddr, pwrCreateCalPtr->NumCalFreq);

  if (1 == pwrCreateCalPtr->NumCalFreq)
  {
    // QAM not supported
    MxL_DLL_ERROR0("Power calibration on QAM source is not supported");
    return MXL_FALSE;
  }
  else
  {
    // Broadband noise
    if (MXL_TRUE != MxL251_UpdateFirmwareStatus(pwrCreateCalPtr->I2cSlaveAddr))
    {
      return MXL_FALSE;
    }

    // Initialize Power Calibration
    MxL251_PwrCalInit();

    if (MXL_TRUE != MxL251_Ctrl_ReadRegister(pwrCreateCalPtr->I2cSlaveAddr, MAILBOX_REG_PWR_CAL_FREQ_STEP_MHZ, &calFreqStepMHz))
    {
      return MXL_FALSE;
    }

    if (calFreqStepMHz == 0)
    {
      // Save savedTiltFlag
      if (MXL_TRUE != MxL251_Ctrl_ReadRegister(pwrCreateCalPtr->I2cSlaveAddr, MAILBOX_REG_TILT_FLAG, &savedTiltFlag))
      {
        return MXL_FALSE;
      }

      // Use default calibration frequency list
      for (i = 0; i < sizeof(PwrCalDefaultCalFreq)/sizeof(PwrCalDefaultCalFreq[0]); ++i)
      {
        if (MXL_TRUE != MxL251_PwrCalOneRefFrequency(pwrCreateCalPtr, PwrCalDefaultCalFreq[i]))
        {
          status = MXL_FALSE;
          break;
        }
      }

      // Restore savedTiltFlag
      if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(
            pwrCreateCalPtr->I2cSlaveAddr,
            MAILBOX_REG_TILT_FLAG,
            DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK,
            savedTiltFlag&DEBUG0_AFEAGC_V2_TILT_ON_PLANT_MASK))
      {
        return MXL_FALSE;
      }

      if (MXL_TRUE != status)
      {
        return MXL_FALSE;
      }

      if (MXL_TRUE != MxL251_PwrGetTemperature(pwrCreateCalPtr->I2cSlaveAddr,
            &(devContextPtr->MxLNVRAMFile.PwrTempComp.REF_TEMP_CODE)))
      {
        return MXL_FALSE;
      }

      MxL251_Ctrl_WbTunerDisable(pwrCreateCalPtr->I2cSlaveAddr, TUNER0, MXL_BOOL_TRUE/*disableAna*/);
      MxL251_Ctrl_WbTunerDisable(pwrCreateCalPtr->I2cSlaveAddr, TUNER1, MXL_BOOL_TRUE/*disableAna*/);

      // if (MXL_TRUE != MxL251_Ctrl_NbChanDisable(
      //       pwrCreateCalPtr->I2cSlaveAddr,
      //       MxL251_Ctrl_GetDemodChanId(tunerId),
      //       MXL_ENABLE/*ifRamp*/))
      // {
      //   return MXL_FALSE;
      // }

      MxL251_PwrUpdateCalibCoefFromLog(devContextPtr);
    }
    else
    {
      // Use automatic scan frequency list
      if (MXL_TRUE != MxL251_PwrCalDebug(pwrCreateCalPtr, calFreqStepMHz))
      {
        devContextPtr->PwrCalCompAtScan = POWER_CAL_DISABLE_COMP;
        return MXL_FALSE;
      }
      devContextPtr->PwrCalCompAtScan = POWER_CAL_DISABLE_COMP;
    }
    return MXL_TRUE;
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : Mxl251_ConfigTunerCalDone - MXL_TUNER_CAL_DONE_CFG
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 08/25/2010
--|
--| DESCRIPTION   : This function is used to return the calibrated parameters
--|                 back to host applicaton, when the calibration is done
--|                 with the various frequencies.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS Mxl251_ConfigTunerCalDone(PMXL_RX_PWR_CAL_COEF_INFO_T tunerCalDonePtr)
{
  UINT16 debugCalFreqStepMHz = 0;

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(tunerCalDonePtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_CAL_DONE_CFG - i2cAddr=0x%x, calType=%d, tablesize=%d CoefTblPtr=%x\n",
      tunerCalDonePtr->I2cSlaveAddr,
      tunerCalDonePtr->CalType,
      tunerCalDonePtr->CoefTableSize,
      (UINT32)(tunerCalDonePtr->CoefTblPtr));

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(tunerCalDonePtr->I2cSlaveAddr,
                                           MAILBOX_REG_PWR_CAL_FREQ_STEP_MHZ,
                                           &debugCalFreqStepMHz))
  {
    return MXL_FALSE;
  }

  switch (tunerCalDonePtr->CalType)
  {
    case RX_PWR_CAL:

      if (0 == debugCalFreqStepMHz)
      {
        MxL251_PwrUpdateCalibCoefFromLog(devContextPtr);
      }

      // Return calibration data
      if (tunerCalDonePtr->CoefTableSize && tunerCalDonePtr->CoefTblPtr)
      {
        if (tunerCalDonePtr->CoefTableSize >= sizeof(devContextPtr->MxLNVRAMFile))
        {
          // Return coef table
          MxL251_MemCpy(tunerCalDonePtr->CoefTblPtr, &(devContextPtr->MxLNVRAMFile), sizeof(devContextPtr->MxLNVRAMFile));

          MxL_DLL_DEBUG0("%s - returning Coef table\n", __FUNCTION__);

          tunerCalDonePtr->CoefTableSize = sizeof(devContextPtr->MxLNVRAMFile);
        }
        else
        {
          MxL_DLL_DEBUG0("%s - insufficient buffer size %d (expecting %d)\n",
              __FUNCTION__,
              tunerCalDonePtr->CoefTableSize,
              sizeof(devContextPtr->MxLNVRAMFile));
          return MXL_FALSE;
        }
      }

      if (0 == debugCalFreqStepMHz)
      {
        // TODO: ignore all NVRAM file errors
        MxL251_Ctrl_SaveMxLNVRAMFile(
            tunerCalDonePtr->I2cSlaveAddr,
            (UINT8*)&(devContextPtr->MxLNVRAMFile),
            sizeof(devContextPtr->MxLNVRAMFile));
      }
      return MXL_TRUE;

    default:
      return MXL_FALSE;
  }
}


typedef struct
{
  UINT8* outBufPtr;
  UINT32 outBufLen;
  UINT32 outPos;
} MXL_LOG_T;

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_DSCALInfoPrint
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 10/02/2010
--|
--| DESCRIPTION   : This function prints log to specified output
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_DSCALInfoPrint(MXL_LOG_T* logPtr, SINT8 *pFormat, ...)
{
#if 0
  va_list argP;
  SINT32 maxWrite;
  SINT32 nWriten;
  va_start(argP, pFormat);

  if (logPtr->outBufPtr)
  {
    maxWrite = logPtr->outBufLen - logPtr->outPos - 1;
    if (maxWrite < 10)
    {
      return MXL_FALSE;
    }
    nWriten  = vsnprintf((SINT8*)logPtr->outBufPtr + logPtr->outPos,
                                maxWrite,
                                pFormat,
                                argP);

    if (nWriten >= maxWrite || nWriten < 0)
    {
      MxL_DLL_ERROR0("MxL251_DSCALInfoPrint truncated");
      return MXL_FALSE;
    }
    logPtr->outPos += nWriten;
  }
  else
  {
    vprintf(pFormat, argP);
  }

  // Clean up variable argument pointer
  va_end(argP);
#endif
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDSCALInfo - MXL_TUNER_DSCAL_INFO_REQ
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 9/30/2010
--|
--| DESCRIPTION   : This function returns calibration log
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_GetDSCALInfo(PMXL_GET_DSCAL_INFO_T cmdPtr)
{
  UINT32 i;

#ifndef _MXL251_BUILD_
  UINT32 F_BAND;
  UINT32 j;
#endif // _MXL251_BUILD_
  UINT32 tunerId;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(cmdPtr->I2cSlaveAddr);

  MXL_NVRAM_FILE_T* filePtr = (MXL_NVRAM_FILE_T*)&(devContextPtr->MxLNVRAMFile);

  MXL_LOG_T log;
  log.outBufPtr = cmdPtr->outBufPtr;
  log.outBufLen = cmdPtr->outBufLen;
  log.outPos    = 0;

  MxL_DLL_DEBUG0("MXL_TUNER_DSCAL_INFO_REQ\n");

  for (tunerId = 0; tunerId < 2; ++tunerId)
  {
    MXL_PWR_CAL_LOG_T* logPtr = (MXL_PWR_CAL_LOG_T*)&PwrCalLog[tunerId];
    if (0 == logPtr->numEntries)
    {
      MxL251_DSCALInfoPrint(&log, "%% Tuner [%d] has empty log\n", tunerId);
      continue;
    }

    MxL251_DSCALInfoPrint(&log, "%%Tuner %d\n", tunerId);
#ifndef _MXL251_BUILD_
    MxL251_DSCALInfoPrint(&log, "%%F_NB F_WB F_BAND P_REF RX_PWR NB TCF P_OUT G_WBDVGA G_RF1 G_LNA G_RF2 G_CIC1 G_CIC2 G_TCF G_FIR5 G_NBDAGC ADCRssi C_F C_TC C_R C_NB\n");
#else // _MXL251_BUILD_
    MxL251_DSCALInfoPrint(&log, "%%F_NB F_WB F_BAND P_REF RX_PWR TCF P_OUT G_WBDVGA G_RF1 G_LNA G_RF2 G_CIC1 G_CIC2 G_TCF G_FIR5 G_NBDAGC ADCRssi C_F C_TC C_R\n");
#endif // _MXL251_BUILD_

    for (i = 0; i < logPtr->numEntries; ++i)
    {
      MXL_PWR_CAL_LOG_ENTRY_T* p = &(logPtr->table[i]);
#ifndef _MXL251_BUILD_
      MxL251_DSCALInfoPrint(&log, "%-d %-d %-d %-.2f %-.2f %-d %-d %-.2f %-.2f %-.0f %-.0f %-.0f %-.2f %-.2f %-.2f %-.2f %-.2f %-5u %-.3f %-.3f %-.3f %-.3f\n",
            p->F_NB,
            p->F_WB,
            p->F_BAND,
            p->P_REF,
            p->RX_PWR,
            p->NB,
            p->TCFmode,
            p->P_OUT,
            p->G_WB_DVGA,
            p->G_RF1,
            p->G_LNA,
            p->G_RF2,
            p->G_CIC1,
            p->G_CIC2,
            p->G_TCF,
            p->G_FIR5,
            p->G_NB_DAGC,
            p->AdcRssi,
            p->C_F,
            p->C_TC,
            p->C_R,
            p->C_NB
              );
#else // _MXL251_BUILD_

#ifdef _MXL251_FIXEDPOINT_
      MxL251_DSCALInfoPrint(&log, "%-d %-d %-d %-.2f %-.2f %-d %-.2f %-.3f %-.0f %-.0f %-.0f %-.2f %-.2f %-.2f %-.2f %-.2f %-5u %-.3f %-.3f %-.3f\n",
          p->F_NB,p->F_WB,p->F_BAND,MXL_VAL(p->P_REF),MXL_VAL(p->RX_PWR),p->TCFmode,MXL_VAL(p->P_OUT),MXL_VAL(p->G_WB_DVGA),MXL_VAL(p->G_RF1),\
		  MXL_VAL(p->G_LNA),MXL_VAL(p->G_RF2),MXL_VAL(p->G_CIC1),MXL_VAL(p->G_CIC2),MXL_VAL(p->G_TCF),
          MXL_VAL(p->G_FIR5), MXL_VAL(p->G_NB_DAGC),p->AdcRssi,MXL_VAL(p->C_F),MXL_VAL(p->C_TC),MXL_VAL(p->C_R));
#else
      MxL251_DSCALInfoPrint(&log, "%-d %-d %-d %-.2f %-.2f %-d %-.2f %-.3f %-.0f %-.0f %-.0f %-.2f %-.2f %-.2f %-.2f %-.2f %-5u %-.3f %-.3f %-.3f\n",
          p->F_NB,p->F_WB,p->F_BAND,p->P_REF,p->RX_PWR,p->TCFmode,p->P_OUT,p->G_WB_DVGA,p->G_RF1,p->G_LNA,p->G_RF2,p->G_CIC1,p->G_CIC2,p->G_TCF,
          p->G_FIR5,p->G_NB_DAGC,p->AdcRssi,p->C_F,p->C_TC,p->C_R);
#endif
#endif // _MXL251_BUILD_
    }
  }
  // Dump MxLNVRAMFile
  MxL251_DSCALInfoPrint(&log, "\n%% Power Coefficient Header: Signature=%c FmtVersion=%d Length=%d NumOfFreqBands=%d\n",
      filePtr->Header.Signature,
      filePtr->Header.FmtVersion,
      filePtr->Header.Length,
      devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands);

  MxL251_DSCALInfoPrint(&log, "\n%% TempComp Header: Signature=%c Length=%d REF_TEMP_CODE=%d\n",
      filePtr->PwrTempComp.Header.Signature?filePtr->PwrTempComp.Header.Signature:'U',
      filePtr->PwrTempComp.Header.Length,
      filePtr->PwrTempComp.REF_TEMP_CODE);

#ifndef _MXL251_BUILD_
  for (i = 0; i < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++i)
  {
    MxL251_DSCALInfoPrint(&log, "%% SLOPE_T[%d][]=", i);
    for (j = 0; j < MXL_PWR_MAX_NUM_LNA_BO; ++j)
    {
      MxL251_DSCALInfoPrint(&log, "%-8.3f ", filePtr->PwrTempComp.Slope_T[i][j]);
    }
    MxL251_DSCALInfoPrint(&log, "\n");
  }
#endif // _MXL251_BUILD_

  for (tunerId = 0; tunerId < 2; ++tunerId)
  {
    MxL251_DSCALInfoPrint(&log, "\n%% FreqComp[%d] Header: Signature=%c Length=%d\n",
        tunerId,
        filePtr->PwrFreqComp[tunerId].Header.Signature,
        filePtr->PwrFreqComp[tunerId].Header.Length);
    MxL251_DSCALInfoPrint(&log, "%% %-11s %-11s %-11s %-11s %-11s\n", "C0", "C1", "C2", "F_C", "F_D");

    for (i = 0; i < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++i)
    {
#ifdef _MXL251_FIXEDPOINT_
      MxL251_DSCALInfoPrint(&log, "%% %-11.3f %-11.3f %-11.3f %-11d %-11d\n",
          MXL_VAL(filePtr->PwrFreqComp[tunerId].Coef[i].C0 ),
          MXL_VAL(filePtr->PwrFreqComp[tunerId].Coef[i].C1 ),
          MXL_VAL(filePtr->PwrFreqComp[tunerId].Coef[i].C2 ),
          (filePtr->PwrFreqComp[tunerId].Coef[i].F_C),
          (filePtr->PwrFreqComp[tunerId].Coef[i].F_D)
          );
#else
      MxL251_DSCALInfoPrint(&log, "%% %-11.3f %-11.3f %-11.3f %-11d %-11d\n",
          filePtr->PwrFreqComp[tunerId].Coef[i].C0,
          filePtr->PwrFreqComp[tunerId].Coef[i].C1,
          filePtr->PwrFreqComp[tunerId].Coef[i].C2,
          filePtr->PwrFreqComp[tunerId].Coef[i].F_C,
          filePtr->PwrFreqComp[tunerId].Coef[i].F_D
          );
#endif //_MXL251_FIXEDPOINT_
    }
  }

  for (tunerId = 0; tunerId < 2; ++tunerId)
  {
    MxL251_DSCALInfoPrint(&log, "\n%% TiltComp[%d] Header: Signature=%c Length=%d\n",
        tunerId,
        filePtr->PwrTiltComp[tunerId].Header.Signature,
        filePtr->PwrTiltComp[tunerId].Header.Length);

    MxL251_DSCALInfoPrint(&log, "%% %-11s %-11s %-11s %-11s %-11s\n", "C0", "C1", "C2", "F_C", "F_D");

#ifdef _MXL251_FIXEDPOINT_
    MxL251_DSCALInfoPrint(&log, "%% %-11.3f %-11.3f %-11.3f %-11d %-11d\n",
        MXL_VAL(filePtr->PwrTiltComp[tunerId].Coef.C0  ),
        MXL_VAL(filePtr->PwrTiltComp[tunerId].Coef.C1  ),
        MXL_VAL(filePtr->PwrTiltComp[tunerId].Coef.C2  ),
        filePtr->PwrTiltComp[tunerId].Coef.F_C  ,
        filePtr->PwrTiltComp[tunerId].Coef.F_D 
        );
#else
    MxL251_DSCALInfoPrint(&log, "%% %-11.3f %-11.3f %-11.3f %-11d %-11d\n",
        filePtr->PwrTiltComp[tunerId].Coef.C0,
        filePtr->PwrTiltComp[tunerId].Coef.C1,
        filePtr->PwrTiltComp[tunerId].Coef.C2,
        filePtr->PwrTiltComp[tunerId].Coef.F_C,
        filePtr->PwrTiltComp[tunerId].Coef.F_D
        );
#endif //_MXL251_FIXEDPOINT_
  }

#ifndef _MXL251_BUILD_
   for (tunerId = 0; tunerId < 2; ++tunerId)
   {
     MxL251_DSCALInfoPrint(&log, "\n%% NBFreqComp[%d] Header: Signature=%c Length=%d\n",
         tunerId,
         filePtr->PwrNBFreqComp[tunerId].Header.Signature,
         filePtr->PwrNBFreqComp[tunerId].Header.Length);
 #ifndef _MXL251_BUILD_
     for (i = 0; i < MXL_PWR_CAL_NUM_BW_MODES; ++i)
     {
       MxL251_DSCALInfoPrint(&log, "%% FREQ_NB[%d][]=", i);
       for (j = 0; j < MXL_PWR_CAL_MAX_NBCAL_PT; ++j)
       {
         MxL251_DSCALInfoPrint(&log, "%-11d ", filePtr->PwrNBFreqComp[tunerId].FREQ_NB[i][j]);
       }
       MxL251_DSCALInfoPrint(&log, "\n");
     }
 #endif // _MXL251_BUILD_

    for (F_BAND = 0; F_BAND < devContextPtr->MxLNVRAMFile.PwrTempComp.NumOfFreqBands; ++F_BAND)
    {
#ifndef _MXL251_BUILD_
      for (i = 0; i < MXL_PWR_CAL_NUM_BW_MODES; ++i)
      {
        MxL251_DSCALInfoPrint(&log, "%% OFFSET_NB[%d][%d][]=", i, F_BAND);
        for (j = 0; j < MXL_PWR_CAL_MAX_NBCAL_PT; ++j)
        {
          MxL251_DSCALInfoPrint(&log, "%-11.3f ", filePtr->PwrNBFreqComp[tunerId].OFFSET_NB[i][F_BAND][j]);
        }
        MxL251_DSCALInfoPrint(&log, "\n");
      }
#endif // _MXL251_BUILD_
      MxL251_DSCALInfoPrint(&log, "%% OFFSET_SCH_NB[%d]=%-11.3f\n", F_BAND, filePtr->PwrNBFreqComp[tunerId].OFFSET_SCH_NB[F_BAND]);
    }
  }
#endif // _MXL251_BUILD_
  cmdPtr->outBufLen = log.outPos;
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConfigTunerCalCutOffFreq - MXL_TUNER_CAL_CUTOFF_FREQ_CFG
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 05/17/2011
--|
--| DESCRIPTION   : This function configures DS Cal cutoff frequency
--|
--| RETURN VALUE  : MXL_TRUE of MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ConfigTunerCalCutOffFreq(PMXL_TUNER_CAL_SET_CUTOFF_FREQ_CFG_T cmdPtr)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(cmdPtr->I2cSlaveAddr);
  MxL_DLL_DEBUG0("MXL_TUNER_CAL_CUTOFF_FREQ_CFG - i2cAddr=0x%x, cutoff=%d Hz\n",
      cmdPtr->I2cSlaveAddr, cmdPtr->CutOffFreqInHz);

  // Update PwrCalFreqRangeTable based on CutOffFreqInHz
  MxL251_PwrUpdateCalFreqRangeTable(devContextPtr, (cmdPtr->CutOffFreqInHz < MXL_PWR_CAL_CUTOFF_FREQ_THRESHOLD)?5:4);

  return MXL_TRUE;
}
