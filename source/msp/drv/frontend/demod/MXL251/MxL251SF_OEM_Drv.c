/*******************************************************************************
 * Example MxL251SF_OEM_Drv.c
 ******************************************************************************/

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#define MXL_NVRAM_FILE_NAME "nvram.bin"
#else
#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include "linux/i2c.h"
#else
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#endif

#include "hi_type.h"

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

#include "MaxLinearDataTypes.h"
#include "MxL251SF_OEM_Drv.h"

#ifdef MXL_USB_I2C
    #include "mxl_usb_i2c.h"
#endif

static HI_U32 g_Mxl251TunerPort;

#define MXL251_DEVICE_ID 0


/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ResetMxL251SF
--| 
--| DESCRIPTION   : This function resets MxL251 through Reset Pin
--| PARAMETERS    : I2cSlaveAddr - Slave Address of MxL251
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ResetMxL251SF(UINT8 I2cSlaveAddr)
{
  //MXL_STATUS status = MXL_TRUE;

  // !!! FIXME !!!
  // OEM should toggle reset pin of MxL251 specified by I2C Slave Addr
  
  HI_S32 u32Ret = HI_SUCCESS; 

  u32Ret  = s_tuner_pGpioFunc->pfnGpioDirSetBit(g_u32ResetCruGpioNo, HI_FALSE);

  u32Ret |= s_tuner_pGpioFunc->pfnGpioWriteBit(g_u32ResetCruGpioNo, 0);
  
  MxL251_Ctrl_DelayUsec(2000);
  u32Ret |= s_tuner_pGpioFunc->pfnGpioWriteBit(g_u32ResetCruGpioNo, 1);
  
  if (HI_SUCCESS != u32Ret)
  {
	  HI_ERR_TUNER("Demod reset failed !\n");
	  return MXL_FAILED;
  }
  MxL251_Ctrl_DelayUsec(2000);
  
  return MXL_SUCCESS;
  
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WriteRegister
--|
--| DESCRIPTION   : This function does I2C write operation.
--| PARAMETERS    : I2cSlaveAddr - Slave Address of MxL251
--|                 RegAddr - Register address of MxL251 to write.
--|                 RegData - Data to write to the specified address.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WriteRegister(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 RegData)
{
  //MXL_STATUS status = MXL_TRUE;

  // !!! FIXME !!!
  // OEM should implement I2C write protocol that complies with MxL251 I2C
  // format.

  // 16bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr(H)| |RegAddr(L)| |RegData(H)| |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), P(Stop condition)

  UINT8 sout[2];
  HI_S32 s32Ret = HI_SUCCESS;
  
  //oem_data_t * user_data = (oem_data_t *) MxL251_HRCLS_OEM_DataPtr[MXL251_DEVICE_ID];

  //if (1)
  {
      UINT8 i2cIndex = g_stTunerOps[g_Mxl251TunerPort].enI2cChannel; // get device i2c address
	  UINT8 i2cAddress = g_stTunerOps[g_Mxl251TunerPort].u32TunerAddress;

  	  sout[0] = (UINT8)((RegData >> 8) & 0x00ff);
	  sout[1] = (UINT8)(RegData & 0x00ff);	  
	  
	  MxL_DLL_DEBUG0("<MxL_Register_Write: I2cSlaveAddr - 0x%02x, RegAddr - 0x%04x, RegData  - 0x%04x\n", 
			  I2cSlaveAddr, RegAddr, RegData);

		if(HI_STD_I2C_NUM >i2cIndex)
	  {
		  //s32Ret = HI_DRV_I2C_Write(i2cIndex, i2cAddress, regAddr,2, sout, 2);
		  s32Ret = s_tuner_pI2cFunc->pfnI2cWrite(i2cIndex, i2cAddress, RegAddr,2, sout, 2);
		 
		  if(HI_SUCCESS != s32Ret)
		  {
			  return MXL_FAILED;
		  }
	  }
	  else
	  {
	  
		  //s32Ret = HI_DRV_GPIOI2C_WriteExt(i2cIndex,i2cAddress, regAddr, 2, sout, 2);
		  s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cWriteExt(i2cIndex,i2cAddress, RegAddr, 2, sout, 2);
		  if(HI_SUCCESS != s32Ret)
		  {
			  return MXL_FAILED;
		  }
	  }
	  
	  //printk("\n===222222222222===Write==RegAddr:%x=sout[0]:%x===sout[1]:%x========\n",RegAddr,sout[0],sout[1]);
  	}


  return MXL_SUCCESS;
  
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ReadRegister
--|
--| DESCRIPTION   : This function does I2C read operation.
--| PARAMETERS    : I2cSlaveAddr - Slave Address of MxL251
--|                 RegAddr - Register address of MxL251 to read.
--|                 DataPtr - Data container to return 16 data.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ReadRegister(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 *DataPtr)
{
  MXL_STATUS status = MXL_TRUE;

  // !!! FIXME !!!
  // OEM should implement I2C read protocol that complies with MxL251 I2C
  // format.

  // 16 Register Read Protocol:
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFF| |0xFB| |RegAddr(H)| |RegAddr(L)| |P|
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // |SLAVE |         |A|    |A|    |A|          |A|          |A| |
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // +------+-+-----+-+-+-------+--+-------+--+-+
  // |MASTER|S|SADDR|R| |       |MA|       |MN|P|
  // +------+-+-----+-+-+-------+--+-------+--+-+
  // |SLAVE |         |A|Data(H)|  |Data(L)|  | |
  // +------+---------+-+-------+--+----------+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), P(Stop condition)
  
  HI_U32  readAddr;
  UINT8 sout[2];
  HI_S32 s32Ret = HI_SUCCESS;
  
  //oem_data_t * user_data = (oem_data_t *) MxL251_HRCLS_OEM_DataPtr[MXL251_DEVICE_ID];
    
  //if (1)
  {
	  UINT8 i2cIndex = g_stTunerOps[g_Mxl251TunerPort].enI2cChannel; 
	  UINT8 i2cAddress = g_stTunerOps[g_Mxl251TunerPort].u32TunerAddress;

	  readAddr = (0xff << 24) | (0xfb << 16) | RegAddr;
	  
	  //printk("\n===11111111111111111111111111===Read==RegAddr:%x=sout[0]:%x===sout[1]:%x========\n",RegAddr,sout[0],sout[1]);

	 if(HI_STD_I2C_NUM > i2cIndex)
	 {
	 
		 // s32Ret = HI_DRV_I2C_Read(i2cIndex, i2cAddress, readAddr, 4, sout, 2);
		  s32Ret = s_tuner_pI2cFunc->pfnI2cRead(i2cIndex, i2cAddress, readAddr, 4, sout, 2);
		  if(HI_SUCCESS != s32Ret)
		  {
			  *DataPtr = 0;
			  return MXL_FAILED;
		  }
	  }
	  else
	  {
		  //s32Ret = HI_DRV_GPIOI2C_ReadExt(i2cIndex, i2cAddress,readAddr, 4, sout, 2);
		  s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(i2cIndex, i2cAddress,readAddr, 4, sout, 2);
		  if(HI_SUCCESS != s32Ret)
		  {
			  *DataPtr = 0;
			  return MXL_FAILED;
		  }
	  }
	  
	  *DataPtr = (sout[0] << 8) | sout[1] ;

	  MxL_DLL_DEBUG0("MxL_Register_Read: I2cSlaveAddr - 0x%02x, RegAddr - 0x%04x, RegData - 0x%04x\n", 
		  I2cSlaveAddr, RegAddr, *DataPtr);    

	  //printk("\n===222222222222222222222===Read==RegAddr:%x=sout[0]:%x===sout[1]:%x========\n",RegAddr,sout[0],sout[1]);
  	}
	return status;

}
  
/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WriteBlock
--|
--| DESCRIPTION   : This function does I2C block write operation.
--| PARAMETERS    : I2cSlaveAddr - Slave Address of MxL251
--|                 RegAddr - Register address of MxL251 to start a block write.
--|                 BufSize - The number of bytes to write
--|                 BufPtr - Data bytes to write to the specified address.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WriteBlock(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 BufSize, UINT8 *BufPtr)
{
  MXL_STATUS status = MXL_TRUE;

  // !!! FIXME !!!
  // OEM should implement I2C block write protocol that complies with MxL251 I2C
  // format.

  // Block Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+---------+-+---+-----------------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr(H)| |RegAddr(L)| |BufPtr[0]| |   |BufPtr[Bufsize-1]| |P|
  // +------+-+-----+-+-+----------+-+----------+-+---------+-+...+-----------------+-+-+
  // |SLAVE |         |A|          |A|          |A|         |A|   |                 |A| |
  // +------+---------+-+----------+-+---- -----+-+---------+-+---+-----------------+-+-+
  // Legends: SADDR(I2c slave address), S(Start condition), A(Ack), P(Stop condition)
  
	HI_S32 s32Ret = HI_SUCCESS;
	//oem_data_t * user_data = (oem_data_t *) MxL251_HRCLS_OEM_DataPtr[MXL251_DEVICE_ID];
	//if (user_data)
	{
		UINT8 i2cIndex = g_stTunerOps[g_Mxl251TunerPort].enI2cChannel; 
		UINT8 i2cAddress = g_stTunerOps[g_Mxl251TunerPort].u32TunerAddress;
		//printk("\n===11111111111111111111111111===WriteBlock===================================\n");

        MxL_DLL_DEBUG0(">>MxL_Block_Write: I2cSlaveAddr - 0x%02x, RegAddr - 0x%04x block size - 0x%04x\n",
                    I2cSlaveAddr, RegAddr, BufSize);    

		if(HI_STD_I2C_NUM >i2cIndex)
     	{
     	   // s32Ret = HI_DRV_I2C_Write(i2cIndex, i2cAddress, regAddr,2, bufPtr, bufSize);
     	   s32Ret = s_tuner_pI2cFunc->pfnI2cWrite(i2cIndex, i2cAddress, RegAddr,2, BufPtr, BufSize);
     	   
     	    if(HI_SUCCESS != s32Ret)
     	    {
     	        return MXL_FAILED;
     	    }
     	}
     	else
     	{
     	    //s32Ret = HI_DRV_GPIOI2C_WriteExt(i2cIndex,i2cAddress, regAddr, 2, bufPtr, bufSize);
	        s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cWriteExt(i2cIndex,i2cAddress, RegAddr, 2, BufPtr, BufSize);
     	    if(HI_SUCCESS != s32Ret)
     	    {
     	        return MXL_FAILED;
         	}
         }
		
		//printk("\n===222222222222222222222===WriteBlock===================================\n");
	}

	return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ReadBlock
--|
--| DESCRIPTION   : This function does I2C block read operation.
--| PARAMETERS    : I2cSlaveAddr - Slave Address of MxL251
--|                 RegAddr - Register Address to start a block read
--|                 ReadSize - The number of bytes to read
--|                 BufPtr - Container to hold readback data
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ReadBlock(UINT8 I2cSlaveAddr, UINT16 RegAddr, UINT16 ReadSize, UINT8 *BufPtr)
{
  MXL_STATUS status = MXL_TRUE;

  // !!! FIXME !!!
  // OEM should implement I2C block read protocol that complies with MxL251 I2C
  // format.
  
  // Block Read Protocol (n bytes of data):
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFF| |0xFD| |RegAddr(H)| |RegAddr(L)| |P|
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // |SLAVE |         |A|    |A|    |A|          |A|          |A| |
  // +------+-+-----+-+-+----+-+----+-+----------+-+----------+-+-+
  // +------+-+-----+-+-------+-+-----+-+-----+-+-----+-+-+
  // |MASTER|S|SADDR|R|       |A|     |A|       |     |N|P|
  // +------+-+-----+-+-+-----+-+-----+-+  ...  +-----+-+-+
  // |SLAVE |         |A|DATA0| |DATA1| |       |DATAn|   |
  // +------+---------+-+-----+-+-----+-+-----+-+-----+---+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Acknowledgement), N(NACK), P(Stop condition)
  
  HI_U32  readAddr;
  //UINT8 sout[4];
  HI_S32 s32Ret = HI_SUCCESS;
  
  //oem_data_t * user_data = (oem_data_t *) MxL251_HRCLS_OEM_DataPtr[MXL251_DEVICE_ID];
	
  //if (1)
  {
	  UINT8 i2cIndex = g_stTunerOps[g_Mxl251TunerPort].enI2cChannel; 
	  UINT8 i2cAddress = g_stTunerOps[g_Mxl251TunerPort].u32TunerAddress;

	  readAddr = (0xff << 24) | (0xfd << 16) | RegAddr;
	  
	  //printk("\n======MxL251_Ctrl_ReadBlock============MxL251_Ctrl_ReadBlock===============MxL251_Ctrl_ReadBlock============\n");
	  MxL_DLL_DEBUG0("<<MxL_Block_Read: I2cSlaveAddr - 0x%02x, RegAddr - 0x%04x block size - 0x%04x\n", 
				  I2cSlaveAddr, RegAddr, ReadSize);    

	 if(HI_STD_I2C_NUM > i2cIndex)
	 {
		  s32Ret = s_tuner_pI2cFunc->pfnI2cRead(i2cIndex, i2cAddress, readAddr, 4, BufPtr, ReadSize);
		  if(HI_SUCCESS != s32Ret)
		  {
			  return MXL_FAILED;
		  }
	  }
	  else
	  {
		  s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(i2cIndex, i2cAddress,readAddr, 4, BufPtr, ReadSize);
		  if(HI_SUCCESS != s32Ret)
		  {
			  return MXL_FAILED;
		  }
	  }
	  

	}
	return status;

}


#ifdef WIN32
/*------------------------------------------------------------------------------
--|
--| FUNCTION NAME : MxL251_Ctrl_OpenMxLNVRAMFile(void)
--|
--| DESCRIPTION   : Win32 version example of opening a MxLNVRAMFile
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL251_Ctrl_OpenMxLNVRAMFile(UINT8 I2cSlaveAddr, FILE** filePtrPtr, const SINT8* modePtr)
{
  SINT8 fnameBuf[MAX_PATH];

  UINT32 n = (UINT32)GetModuleFileName(NULL, fnameBuf, MAX_PATH);  
  SINT32 nWriten;

  if (n <= 0 || n >= MAX_PATH/* truncate */)
  {
    MxL_DLL_DEBUG0("%s - GetModuleFileName failed\n", __FUNCTION__);
    return MXL_FALSE;
  }

  while (n > 0)  
  {
    n--;
    if(fnameBuf[n] == '\\' || fnameBuf[n] == '/')  
    {
      break;
    }  
  }

  if (n == 0)
  {
    MxL_DLL_DEBUG0("%s - no path seperator found\n", __FUNCTION__);
    return MXL_FALSE;
  }

  n++; // to include path char

  nWriten = _snprintf(fnameBuf + n, (MAX_PATH-1-n), "%s%02x.bin", MXL_NVRAM_FILE_NAME, I2cSlaveAddr);

  if (nWriten <= 0 || (UINT32)nWriten >= (MAX_PATH-1-n))
  {
    MxL_DLL_DEBUG0("%s - insufficient buffer length\n", __FUNCTION__);
    return MXL_FALSE;
  }

  // To assure zero-termination
  fnameBuf[n+nWriten]=0;

  *filePtrPtr = fopen(fnameBuf, modePtr);

  if (0 == *filePtrPtr)
  {
    MxL_DLL_DEBUG0("%s - Failed to open %s\n", __FUNCTION__, fnameBuf);
    return MXL_FALSE;
  }

  MxL_DLL_DEBUG0("%s - NVRAM file %s is opened\n", __FUNCTION__, fnameBuf);

  return MXL_TRUE;
}
#endif // WIN32

/*------------------------------------------------------------------------------
--|
--| FUNCTION NAME : MxL251_Ctrl_LoadMxLNVRAMFile
--|
--| DESCRIPTION   : Load MxLNVRAMFile
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_LoadMxLNVRAMFile(UINT8 I2cSlaveAddr, UINT8 *BufPtr, UINT32 BufLen)
{
  MXL_STATUS status = MXL_FALSE;

  // !!! FIXME !!! 
  // To be implemented for customer OEM platform
#ifdef WIN32
  FILE* in;

  if (MXL_TRUE != MxL251_Ctrl_OpenMxLNVRAMFile(I2cSlaveAddr, &in, "rb"))
  {
    return MXL_FALSE;
  }

  if (BufLen == fread(BufPtr, sizeof(UINT8), BufLen, in))
  {
    status = MXL_TRUE;
  }
  else
  {
    MxL_DLL_DEBUG0("Failed to read file " MXL_NVRAM_FILE_NAME "\n");
  }

  fclose(in);
#endif // WIN32
  return status;
}

/*------------------------------------------------------------------------------
--|
--| FUNCTION NAME : MxL251_Ctrl_SaveMxLNVRAMFile
--|
--| DESCRIPTION   : Save MxLNVRAMFile
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SaveMxLNVRAMFile(UINT8 I2cSlaveAddr, UINT8 *BufPtr, UINT32 BufLen)
{
  MXL_STATUS status = MXL_FALSE;
  // !!! FIXME !!! 
  // To be implemented for customer OEM platform

#ifdef WIN32
  FILE* out;

  if (MXL_TRUE != MxL251_Ctrl_OpenMxLNVRAMFile(I2cSlaveAddr, &out, "wb"))
  {
    return MXL_FALSE;
  }

  if (BufLen == fwrite(BufPtr, sizeof(UINT8), BufLen, out))
  {
    status = MXL_TRUE;
  }
  else
  {
    MxL_DLL_DEBUG0("Failed to write file " MXL_NVRAM_FILE_NAME "\n");
  }

  fclose(out);
#endif // WIN32
  return status;  
}

/*------------------------------------------------------------------------------
--|
--| FUNCTION NAME : MxL251_Ctrl_DelayUsec
--|
--| DESCRIPTION   : Delay in micro-seconds
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_DelayUsec(UINT32 usec)
{
  // !!! FIXME !!! 
  // To be implemented for customer OEM platform

//  msleep(usec);
  udelay(usec);

  return MXL_TRUE;
}

/*------------------------------------------------------------------------------
--|
--| FUNCTION NAME : MxL251_Ctrl_GetCurrTimeInUsec
--|
--| DESCRIPTION   : Get current time in micro-seconds
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetCurrTimeInUsec(UINT64* usecPtr)
{
  // !!! FIXME !!! 
  // To be implemented for customer OEM platform
#ifdef WIN32
  // The following example is based on Windows Platform
  static LARGE_INTEGER freq = {{0}};

  LARGE_INTEGER curTime;

  if (0 == freq.QuadPart)
  {
    if (!QueryPerformanceFrequency(&freq))
    {
      MxL_DLL_ERROR0("failed");
      return MXL_FALSE;
    }
  }

  if (!QueryPerformanceCounter(&curTime))
  {
    MxL_DLL_ERROR0("failed");
    return MXL_FALSE;
  }

  *usecPtr = (1000000ULL*curTime.QuadPart)/freq.QuadPart;
#else // WIN32
  struct timeval currTime;
  unsigned long long timeInUsec;

  //MxL_DLL_DEBUG0(" MxL251_Ctrl_GetTimeTickInUsec ");
  do_gettimeofday(&currTime);

  timeInUsec = (unsigned long long)((unsigned long long) currTime.tv_sec*1000*1000) + (unsigned long long)currTime.tv_usec;
  *usecPtr= timeInUsec;

  //MxL_DLL_DEBUG0("MxL251_Ctrl_GetTimeTickInUsec return %llu\n", timeInUsec);
#endif // WIN32

  return MXL_TRUE;
}

void MxL251_I2C_SetPort(UINT32 TunerPort)
{
    g_Mxl251TunerPort = TunerPort;
}

