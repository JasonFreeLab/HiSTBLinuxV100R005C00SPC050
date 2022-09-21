/*******************************************************************************
 *
 * FILE NAME          : MxL_Debug.h
 * 
 * AUTHOR             : David Zhou
 *                      Ron Green - Added MxL_VFC_DEBUG for the MxL Color 
 *                                  Formater filter.
 *
 * DATE CREATED       : 2/7/2008
 *                      9/15/2008
 *
 * DESCRIPTION        : Debug header files 
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL_DEBUG_H__
#define __MXL_DEBUG_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/
#include "drv_demod.h"
#include "MaxLinearDataTypes.h"

/******************************************************************************
    Macros
******************************************************************************/

// User Mode define
//#define __USER_MODE_DEBUG__  
#define MxL_DLL_DEBUG0(...)  MxL_VFC_DEBUG(DEBUG_LEVEL_INFO, __VA_ARGS__)
#define MxL_DLL_ERROR0(fmt, ...)  MxL_VFC_DEBUG(DEBUG_LEVEL_INFO, "DLLERROR - %s:" fmt "\r\n", __FUNCTION__, __VA_ARGS__)
#define MxL_DLL_PRINT0(fmt, ...)  MxL_VFC_DEBUG(DEBUG_LEVEL_INFO, "DLLPRINT - %s:" fmt "\r\n", __FUNCTION__, __VA_ARGS__)

// Enable debug log to file
#define DEBUG_LOG_TO_FILE

// Enable debug header info
#define DEBUG_WITH_HEADER

// Debug buffer size
#define DEBUG_MAX_STRING_LENGTH        256
#define DEBUG_MAX_HEADER_LENGTH        48

// Debug module index
#define DEBUG_MAX_MODULE_NUMBER        8

// Debug mask:  debug control dword upper 24-bit

#ifdef __USER_MODE_DEBUG__
// User Mode masks
#define DEBUG_MASK_INIT         0x00000100
#define DEBUG_MASK_CONTROL      0x00000200
#define DEBUG_MASK_MONITOR      0x00000400
#define DEBUG_MASK_FAIL         0x00000800
#define DEBUG_MASK_DSHOW        0x00001000
#define DEBUG_MASK_UDP          0x00002000
#define DEBUG_MASK_UI           0x00004000
#else
// Kernel Mode masks
#define DEBUG_MASK_INIT         0x00000100
#define DEBUG_MASK_CONTROL      0x00000200
#define DEBUG_MASK_MONITOR      0x00000400
#define DEBUG_MASK_FAIL         0x00000800
#define DEBUG_MASK_TIMING       0x00001000
#define DEBUG_MASK_DPC          0x00002000
#define DEBUG_MASK_REGISTERS    0x00004000
#define DEBUG_MASK_USBSTRUCTS   0x00010000
#define DEBUG_MASK_IRP          0x00020000
#define DEBUG_MASK_USB          0x00040000
#define DEBUG_MASK_USBISO       0x00080000
#define DEBUG_MASK_IOCTL        0x00100000
#define DEBUG_MASK_POWER        0x00200000
#define DEBUG_MASK_PNP          0x00400000
#define DEBUG_MASK_ARBITER      0x00800000
#define DEBUG_MASK_REGISTRY     0x01000000     
#define DEBUG_MASK_656          0x02000000
#define DEBUG_MASK_I2S          0x04000000
#define DEBUG_MASK_FILTER       0x08000000
#define DEBUG_MASK_PIN	        0x10000000
#define DEBUG_MASK_STREAM       0x20000000
#define DEBUG_MASK_BDA          0x40000000   

#endif

// Debug module:  debug control dword bit 4-7

#ifdef __USER_MODE_DEBUG__
// User Mode modules
#define DEBUG_MODULE_GNL       0x00000000
#define DEBUG_MODULE_IR        0x00000010
#define DEBUG_MODULE_UI        0x00000020
#define DEBUG_MODULE_DLL       0x00000040
#define DEBUG_MODULE_VFC       0x00000080
#else
// Kernel Mode modules
#define DEBUG_MODULE_GNL       0x00000000
#define DEBUG_MODULE_USB       0x00000010
#define DEBUG_MODULE_BDA       0x00000020
#define DEBUG_MODULE_CAP       0x00000040
#endif

// Debug function: macro definition

#ifdef __USER_MODE_DEBUG__
// User Mode debug functions
// DZ: __VA_ARG__ is supported in VC8 but not in VC7
#define MxL_IR_DEBUG(control, format, ...)    MxL_DebugTrace(control|DEBUG_MODULE_IR, format, __VA_ARGS__)
#define MxL_UI_DEBUG(control, format, ...)    MxL_DebugTrace(control|DEBUG_MODULE_UI, format, __VA_ARGS__)
#define MxL_DLL_DEBUG(control, format, ...)   MxL_DebugTrace(control|DEBUG_MODULE_DLL, format, __VA_ARGS__)
#define MxL_VFC_DEBUG(control, format, ...)   MxL_DebugTrace(control|DEBUG_MODULE_VFC, format, __VA_ARGS__) // MxL Color Formater
#else
// Kernel Mode debug functions
#define MxL_USB_KDEBUG(control, format, ...)  MxL_DebugTrace(control|DEBUG_MODULE_USB, format, __VA_ARGS__)
#define MxL_BDA_KDEBUG(control, format, ...)  MxL_DebugTrace(control|DEBUG_MODULE_BDA, format, __VA_ARGS__)
#define MxL_CAP_KDEBUG(control, format, ...)  MxL_DebugTrace(control|DEBUG_MODULE_CAP, format, __VA_ARGS__)
#define MxL_VFC_DEBUG(control, format, ...)   
#endif

/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

// Debug level enumeration: debug control dword bit 0-3
typedef enum
{
  DEBUG_LEVEL_OFF   =	0,
  DEBUG_LEVEL_ERROR,		
  DEBUG_LEVEL_WARNING,	
  DEBUG_LEVEL_INFO		
} DEBUG_LEVEL_E;

// Debug code string mapping
typedef struct
{
  UINT32 Code;
  SINT8  *Description;
} DEBUG_CODE_MAPPING_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/
extern UINT8 DebugLevelControl;
extern UINT32 DebugMaskControl;

/******************************************************************************
    Prototypes
******************************************************************************/
void MxL_DebugLogToFile(SINT8 *pFileName, UINT8 *pBuff, UINT32 BuffSize);
void MxL_DebugTrace(UINT32 control, SINT8 *pFormat, ...);

#endif /* __MXL_DEBUG_H__*/
