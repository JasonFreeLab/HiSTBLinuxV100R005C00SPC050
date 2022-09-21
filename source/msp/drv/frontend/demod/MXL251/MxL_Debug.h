/*******************************************************************************
 * Example MxL_Debug.h
 ******************************************************************************/

#ifndef __MXL_DEBUG_H__
#define __MXL_DEBUG_H__

#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/module.h>
#else
#include <stdio.h>
#include <string.h>
#endif

#include "MaxLinearDataTypes.h"

// !!! FIXME !!!
// The following 3 macros should be replace by customer debug print functions
#if 0 
#define MxL_DLL_DEBUG0(...) // FIXME
#define MxL_DLL_ERROR0(...) // FIXME
#define MxL_DLL_PRINT0(...) // FIXME
#else
//#define MxL_DLL_DEBUG0(...) // FIXME
//#define MxL_DLL_ERROR0(...) // FIXME
//#define MxL_DLL_PRINT0(...) // FIXME
#define MxL_DLL_DEBUG0 HI_INFO_TUNER //printk // FIXME
#define MxL_DLL_ERROR0 HI_INFO_TUNER //printk // FIXME
#define MxL_DLL_PRINT0 HI_INFO_TUNER //printk // FIXME
#endif
// Or, define them to empty to disable all debug messages:
//      #define MxL_DLL_DEBUG0(...)
//      #define MxL_DLL_ERROR0(...)
//      #define MxL_DLL_PRINT0(...)

#endif // __MXL_DEBUG_H__

