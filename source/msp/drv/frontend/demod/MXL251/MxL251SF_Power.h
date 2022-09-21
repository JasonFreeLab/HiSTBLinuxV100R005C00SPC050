/*******************************************************************************
 *
 * FILE NAME          : MxL251SF_Power.h
 * 
 * AUTHOR             : Jun Huang
 *                      Jun Huang
 *
 * DATE CREATED       : 09/16/2010
 *                      06/18/2011
 *
 * DESCRIPTION        : This file is header file for power reporting and 
 *                      calibration.
 *
 *******************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL251SF_POWER_H__
#define __MXL251SF_POWER_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/
#include "MaxLinearDataTypes.h"

/******************************************************************************
    Macros
******************************************************************************/

// Power reporting and DS calibration
#ifdef _MXL251_FIXEDPOINT_
#define MXL_PWR_UNDEFINED_POWER           -0x80000//-0xFFFFFF //FIXME:
#else
#define MXL_PWR_UNDEFINED_POWER           -512.0
#endif
#define MXL_PWR_UNDEFINED_TEMP_CODE       0x7FFF
#define MXL_PWR_MAX_LNA_BO_DB             8
#define MXL_PWR_MAX_NUM_LNA_BO            (MXL_PWR_MAX_LNA_BO_DB/2+1)

#define MXL_PWR_CAL_NUM_OF_FREQ_BANDS     5
#define MXL_PWR_CAL_NUM_OF_TUNERS         2

#define MXL_PWR_CAL_MAX_NBCAL_PT          8
#ifndef _MXL251_BUILD_
#define MXL_PWR_CAL_NUM_BW_MODES          2
#endif // _MXL251_BUILD_

#define MXL_PWR_CAL_MAX_FREQ_COMP_PT      15

#define MXL_PWR_CAL_FREQ_BAND_IDX_VHF1    0
#define MXL_PWR_CAL_FREQ_BAND_IDX_VHF2    1
#define MXL_PWR_CAL_FREQ_BAND_IDX_UHF1    2
#define MXL_PWR_CAL_FREQ_BAND_IDX_UHF21   3
#define MXL_PWR_CAL_FREQ_BAND_IDX_UHF22   4

#define MXL_PWR_CAL_MAX_CAL_POINTS        10
#define MXL_PWR_CAL_MAX_NUM_LOG_ENTRIES   20

#define MXL_PWR_COEF_TABLE_SIGNATURE      'T'

#define MXL_PWR_CAL_CUTOFF_FREQ_THRESHOLD 100000000U

/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

#ifndef _MXL251_BUILD_
// WARNING: please do not change order:
// THe following lookup requires the enums are defined in following order
// (F_NB = (SINT32)PwrCalNBFreqList[bwMode-PWR_CAL_NB_MODE_FULL_BAND_NBCAL][iNB] * 1000000)
typedef enum
{
  PWR_CAL_NB_MODE_FULL_BAND_DEFAULT = 0,
  PWR_CAL_NB_MODE_FULL_BAND_NBCAL   = 1,
  PWR_CAL_NB_MODE_HALF_BAND_NBCAL   = 2,
  PWR_CAL_NB_MODE_SINGLECHAN_NBCAL  = 3,
} MXL_PWR_CAL_NB_MODE_E;
#endif // _MXL251_BUILD_

typedef enum
{
  MXL_PWR_CAL_TCF_MODE_OFF = 0,
  MXL_PWR_CAL_TCF_MODE_ON  = 1,
} MXL_PWR_CAL_TCF_MODE_E;

typedef struct
{
#ifndef _MXL251_BUILD_
  SINT32 F_REF_Mn;
  SINT32 F_WB_Mn;
  SINT32 F_WB_Md;
  SINT32 F_WB_Mx;
  SINT32 F_REF_Mx;
#else // _MXL251_BUILD_
  SINT32 F_WB_Mn;
  SINT32 F_WB_Mx;
#endif // _MXL251_BUILD_
} MXL_PWR_CAL_FREQ_RANGE_T;

typedef struct
{
  UINT8  Signature;   // Signature to identify type of table (0 if invalid)
  UINT8  Reserved;    // Byte Padding
  UINT16 Length;      // Length of table including header in little endian
} MXL_PWR_TABLE_HEADER_T;

typedef struct
{
#ifdef _MXL251_FIXEDPOINT_
  SINT32 C0;
  SINT32 C1;
  SINT32 C2;
#else
  REAL32 C0;
  REAL32 C1;
  REAL32 C2;
#endif
  SINT32 F_C;
  SINT32 F_D;
} MXL_PWR_QUADRATIC_COEF_T;

typedef struct
{
  MXL_PWR_TABLE_HEADER_T Header;
  SINT16 REF_TEMP_CODE;
  UINT8  Reserved; // padding
  UINT8  NumOfFreqBands;
#ifndef _MXL251_BUILD_
  REAL32 Slope_T[MXL_PWR_CAL_NUM_OF_FREQ_BANDS][MXL_PWR_MAX_NUM_LNA_BO];  
#endif // _MXL251_BUILD_
} MXL_PWR_TEMP_COMP_COEF_T;

typedef struct
{
  MXL_PWR_TABLE_HEADER_T Header;
  MXL_PWR_QUADRATIC_COEF_T Coef[MXL_PWR_CAL_NUM_OF_FREQ_BANDS];
  // MXL_PWR_CAL_MAX_FREQ_COMP_PT
} MXL_PWR_FREQ_COMP_COEF_T;

typedef struct
{
  MXL_PWR_TABLE_HEADER_T Header;
  MXL_PWR_QUADRATIC_COEF_T Coef;
} MXL_PWR_TILT_COMP_COEF_T;

#ifndef _MXL251_BUILD_
typedef struct
{
  MXL_PWR_TABLE_HEADER_T Header;
  SINT32 FREQ_NB[MXL_PWR_CAL_NUM_BW_MODES][MXL_PWR_CAL_MAX_NBCAL_PT];
  REAL32 OFFSET_NB[MXL_PWR_CAL_NUM_BW_MODES][MXL_PWR_CAL_NUM_OF_FREQ_BANDS][MXL_PWR_CAL_MAX_NBCAL_PT];
  REAL32 OFFSET_SCH_NB[MXL_PWR_CAL_NUM_OF_FREQ_BANDS];
} MXL_PWR_NBFREQ_COMP_COEF_T;
#endif // _MXL251_BUILD_

#ifdef _MXL251_FIXEDPOINT_
typedef struct
{
  SINT32 F_NB;
  SINT32 F_WB;
  SINT32 F_BAND;
  SINT32 P_REF;
  SINT32 RX_PWR;
#ifndef _MXL251_BUILD_
  UINT8  NB;
#endif // _MXL251_BUILD_
  UINT8  TCFmode;
  UINT8  reserved1;
  UINT8  reserved2;
  SINT32 P_OUT;
  SINT32 G_WB_DVGA;
  SINT32 G_RF1; // G_RF1_MAX_DB /*0*/  - agc_rf1_bo; // TODO
  SINT32 G_LNA; // G_LNA_MAX_DB /*20*/ - agc_lna_X_bo; // TODO
  SINT32 G_RF2; // G_RF2_MAX_DB /*20*/ - agc_rf2_X_bo; // TODO
  SINT32 G_CIC1;
  SINT32 G_CIC2;
  SINT32 G_TCF;
  SINT32 G_FIR5;
  SINT32 G_NB_DAGC; // saturate to [-20, 20]
  UINT16 AdcRssi;   // padding  
  SINT32 C_F;
  SINT32 C_TC;
  SINT32 C_R;
#ifndef _MXL251_BUILD_
  REAL32 C_NB;
#endif // _MXL251_BUILD_
} MXL_PWR_CAL_LOG_ENTRY_T;

#else //_MXL251_FIXEDPOINT_

typedef struct
{
  SINT32 F_NB;
  SINT32 F_WB;
  SINT32 F_BAND;
  REAL32 P_REF;
  REAL32 RX_PWR;
#ifndef _MXL251_BUILD_
  UINT8  NB;
#endif // _MXL251_BUILD_
  UINT8  TCFmode;
  UINT8  reserved1;
  UINT8  reserved2;
  REAL32 P_OUT;
  REAL32 G_WB_DVGA;
  REAL32 G_RF1; // G_RF1_MAX_DB /*0*/  - agc_rf1_bo; // TODO
  REAL32 G_LNA; // G_LNA_MAX_DB /*20*/ - agc_lna_X_bo; // TODO
  REAL32 G_RF2; // G_RF2_MAX_DB /*20*/ - agc_rf2_X_bo; // TODO
  REAL32 G_CIC1;
  REAL32 G_CIC2;
  REAL32 G_TCF;
  REAL32 G_FIR5;
  REAL32 G_NB_DAGC; // saturate to [-20, 20]
  UINT16 AdcRssi;   // padding  
  REAL32 C_F;
  REAL32 C_TC;
  REAL32 C_R;
#ifndef _MXL251_BUILD_
  REAL32 C_NB;
#endif // _MXL251_BUILD_
} MXL_PWR_CAL_LOG_ENTRY_T;
#endif //_MXL251_FIXEDPOINT_

typedef struct
{
  UINT32 numEntries;
  MXL_PWR_CAL_LOG_ENTRY_T table[MXL_PWR_CAL_MAX_NUM_LOG_ENTRIES];
} MXL_PWR_CAL_LOG_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

/******************************************************************************
    Prototypes
******************************************************************************/

#endif // __MXL251SF_POWER_H__
