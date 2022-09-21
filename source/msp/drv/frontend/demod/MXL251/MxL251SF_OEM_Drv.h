/*******************************************************************************
 * Example MxL251SF_OEM_Drv.h
 ******************************************************************************/

#ifndef __MXL251SF_OEM_DRV_H__
#define __MXL251SF_OEM_DRV_H__

#include "MaxLinearDataTypes.h"
#include "MxL_Debug.h"

// !!! FIXME !!! 
// The following macro defines maximum number of bytes that can be sent
// in one block write.
//
// Note that this parameter varies from platform to platform.  If unsure of the
// hardware limitation, please start with a smaller number, for example, 8
#define MAX_BLOCK_WRITE_LENGTH   256 // FIXME 

MXL_STATUS MxL251_Ctrl_ResetMxL251SF(UINT8 I2cSlaveAddr);
MXL_STATUS MxL251_Ctrl_WriteRegister(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 RegData);
MXL_STATUS MxL251_Ctrl_ReadRegister(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 *DataPtr);

MXL_STATUS MxL251_Ctrl_ReadBlock(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 ReadSize, UINT8* BufPtr);
MXL_STATUS MxL251_Ctrl_WriteBlock(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 BufSize, UINT8* BufPtr);

MXL_STATUS MxL251_Ctrl_LoadMxLNVRAMFile(UINT8 I2cSlaveAddr, UINT8 *BufPtr, UINT32 BufLen);
MXL_STATUS MxL251_Ctrl_SaveMxLNVRAMFile(UINT8 I2cSlaveAddr, UINT8 *BufPtr, UINT32 BufLen);

MXL_STATUS MxL251_Ctrl_DelayUsec(UINT32 usec);
MXL_STATUS MxL251_Ctrl_GetCurrTimeInUsec(UINT64* usecPtr);

void MxL251_I2C_SetPort(UINT32 TunerPort);

#endif /* __MXL251SF_OEM_DRV_H__*/

