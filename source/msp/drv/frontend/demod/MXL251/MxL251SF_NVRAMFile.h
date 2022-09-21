/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_NVRAMFile.h
 * 
 * AUTHOR             : Jun Huang
 *                      Richard Liu
 *                      Jun Huang
 *
 * DATE CREATED       : 09/16/2010
 *                      12/29/2010
 *                      06/18/2011
 *
 * DESCRIPTION        : This file is header file for MxLNVRAMFile
 *
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

#ifndef __MXL251SF_NVRAM_FILE_H__
#define __MXL251SF_NVRAM_FILE_H__

/*****************************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
*****************************************************************************************/
#include "MaxLinearDataTypes.h"
#include "MxL251SF_Power.h"

/*****************************************************************************************
    Macros
*****************************************************************************************/

#define MXL_NVRAM_FILE_SIGNATURE          'M'
#define MXL_NVRAM_FILE_FMTVERSION         0x85 // MSB indicates 251

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/
typedef struct
{
  UINT8                       Signature;   // Identification 'M'
  UINT8                       FmtVersion;  // Version of format
  UINT16                      Length;      // Total length in little endian
} MXL_NVRAM_FILE_HEADER_T;

typedef struct
{
  MXL_NVRAM_FILE_HEADER_T     Header;
  MXL_PWR_TEMP_COMP_COEF_T    PwrTempComp;
  MXL_PWR_FREQ_COMP_COEF_T    PwrFreqComp[MXL_PWR_CAL_NUM_OF_TUNERS];
  MXL_PWR_TILT_COMP_COEF_T    PwrTiltComp[MXL_PWR_CAL_NUM_OF_TUNERS];
#ifndef _MXL251_BUILD_
  MXL_PWR_NBFREQ_COMP_COEF_T  PwrNBFreqComp[MXL_PWR_CAL_NUM_OF_TUNERS];
#endif // _MXL251_BUILD_
  // Add more todo
} MXL_NVRAM_FILE_T;

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/

#endif // __MXL251SF_NVRAM_FILE_H__

