/*****************************************************************************************
 *
 * FILE NAME          : MaxLinearDataTypes.h
 * 
 * AUTHOR             : Brenndon Lee
 * DATE CREATED       : Jul/31, 2006
 *
 * DESCRIPTION        : This file contains MaxLinear-defined data types.
 *                      Instead of using ANSI C data type directly in source code
 *                      All module should include this header file.
 *                      And conditional compilation switch is also declared
 *                      here.
 *
 *****************************************************************************************
 *                Copyright (c) 2006, MaxLinear, Inc.
 ****************************************************************************************/

#ifndef __MAXLINEAR_DATA_TYPES_H__
#define __MAXLINEAR_DATA_TYPES_H__

/*****************************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
*****************************************************************************************/

/*****************************************************************************************
    Macros
*****************************************************************************************/

/* Changes for Fixed Point Arithmetic */
#define  _MXL251_FIXEDPOINT_
#define   MXL251_PRECISION   10 

#define _MXL251_BUILD_
#define _DYNAMIC_VCO_THRESHOLD_ENABLED_
#define _SOC_ID_DEBUG_ENABLED_
#define _DEBUG_VCO_THRESHOLD_ENABLED_
#define _POWER_REPORTING_TEMP_COMP_ENABLED_
#define _POWER_REPORTING_TEMP_COMP_DEBUG_
//#define _OOB_SUPPORT_ENABLED_
// #define _BOOT_SCAN_ENABLED_
// #define _LEGACY_API_INTERFACE_

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/
typedef unsigned char        UINT8;
typedef unsigned short       UINT16;
typedef unsigned int         UINT32;
typedef unsigned long long   UINT64;

typedef long long SINT64;
typedef char                 SINT8;
typedef short                SINT16;
typedef int                  SINT32;
typedef float                REAL32;
typedef double               REAL64;

#define MXL_MIN(x, y)                   (((x) < (y)) ? (x) : (y))
#define MXL_MAX(x, y)                   (((x) >= (y)) ? (x) : (y))
#define MXL_ABS(x)                      (((x) >= 0) ? (x) : -(x))

 #define mxl251_u64mod(x, y)             (  \
                                         {  \
                                           UINT64 out = 0; \
                                           UINT64 x_1 = (UINT64) x; \
                                           UINT32 y_1 = (UINT32) y; \
                                           if (y) \
                                           { \
                                             out = do_div(x_1,y_1); \
                                           } \
                                           x_1; \
                                        } \
                                         )
typedef enum 
{
  IFX_SUCCESS = 0,
  IFX_FAILED,
  IFX_BUSY,
  IFX_NULL_PTR,
  IFX_INVALID_PARAMETER,
  IFX_BUFFER_TOO_SMALL,
  IFX_TIMEOUT  
} IFX_STATUS;

typedef enum 
{
  MXL_TRUE = 0,
  MXL_SUCCESS = 0,
  MXL_FALSE = 1,  
  MXL_FAILED = 1,
} MXL_STATUS;

typedef enum 
{
  MXL_DISABLE = 0,
  MXL_ENABLE  = 1,  
        
  MXL_NO_FREEZE = 0,
  MXL_FREEZE    = 1,

  MXL_UNLOCKED = 0,
  MXL_LOCKED   = 1,

  MXL_MPEG_OUT = 0,
  MXL_IF_OUT   = 1,
  
  MXL_WB_TUNER = 0,
  MXL_NB_TUNER = 1,

  MXL_INVERTED_IF_SPECTRUM = 0,
  MXL_NORMAL_IF_SPECTRUM   = 1,

  MXL_TUNER = 0,
  MXL_DEMOD =1,

  MXL_BOOL_FALSE = 0,
  MXL_BOOL_TRUE  = 1,  

} MXL_BOOL;


/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/

#endif /* __MAXLINEAR_DATA_TYPES_H__ */

