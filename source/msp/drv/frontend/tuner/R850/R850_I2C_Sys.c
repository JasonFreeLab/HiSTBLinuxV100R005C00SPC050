#include "R850_i2c_sys.h"
#include "R850.h"

#include "hi_drv_i2c.h"
#include "hi_debug.h"

#include "drv_tuner_ext.h"
#include "drv_demod.h"

R850_TUNER_NUM_TYPE TUNER_NO = R850_TUNER_1;

#if 0
BOOL flag;
LONG *IoRead;
LONG ulIoPortConfig;
HANDLE hDevice[127];
I2C_TRANS TransI2C;
HINSTANCE hDLL;
GETDLLVERSION GetDllVersion;
OPENDEVICEINSTANCE OpenDeviceInstance;
CLOSEDEVICEINSTANCE CloseDeviceInstance;
DETECTDEVICE DetectDevice;
GETDEVICECOUNT GetDeviceCount;
GETDEVICEINFO GetDeviceInfo;
OPENDEVICEBYSERIALID OpenDeviceBySerialId;
GETSERIALID GetSerialId;
CONFIGIOPORTS ConfigIoPorts;
GETIOCONFIG GetIoConfig;
READIOPORTS ReadIoPorts;
WRITEIOPORTS WriteIoPorts;
READI2C ReadI2c;
WRITEI2C WriteI2c;

bool I2C_Init(R850_TUNER_NUM_TYPE R850_Tuner_Num)
{
	hDLL = LoadLibrary("UsbI2cIo.dll");          // attempt load dll
	if( hDLL != NULL) {
		// got handle to dll, now initialize API function pointers
		GetDllVersion=(GETDLLVERSION)GetProcAddress(hDLL,"DAPI_GetDllVersion");
		OpenDeviceInstance=(OPENDEVICEINSTANCE)GetProcAddress(hDLL,"DAPI_OpenDeviceInstance");
		CloseDeviceInstance=(CLOSEDEVICEINSTANCE)GetProcAddress(hDLL,"DAPI_CloseDeviceInstance");
		DetectDevice=(DETECTDEVICE)GetProcAddress(hDLL,"DAPI_DetectDevice");
		GetDeviceCount=(GETDEVICECOUNT)GetProcAddress(hDLL,"DAPI_GetDeviceCount");
		GetDeviceInfo=(GETDEVICEINFO)GetProcAddress(hDLL,"DAPI_GetDeviceInfo");
		OpenDeviceBySerialId=(OPENDEVICEBYSERIALID)GetProcAddress(hDLL,"DAPI_OpenDeviceBySerialId");
		GetSerialId=(GETSERIALID)GetProcAddress(hDLL,"DAPI_GetSerialId");
		ConfigIoPorts=(CONFIGIOPORTS)GetProcAddress(hDLL,"DAPI_ConfigIoPorts"); 
		GetIoConfig=(GETIOCONFIG)GetProcAddress(hDLL,"DAPI_GetIoConfig"); 
		ReadIoPorts=(READIOPORTS)GetProcAddress(hDLL,"DAPI_ReadIoPorts");
		WriteIoPorts=(WRITEIOPORTS)GetProcAddress(hDLL,"DAPI_WriteIoPorts");
		ReadI2c=(READI2C)GetProcAddress(hDLL,"DAPI_ReadI2c");
		WriteI2c=(WRITEI2C)GetProcAddress(hDLL,"DAPI_WriteI2c");
	}
	else
		return false;
	
	hDevice[R850_Tuner_Num]=OpenDeviceInstance("UsbI2cIo", (BYTE)R850_Tuner_Num);

	if(hDevice == INVALID_HANDLE_VALUE) 
	return false;

  TransI2C.byTransType = I2C_TRANS_8ADR;

	return true;
}

bool Close_I2C(R850_TUNER_NUM_TYPE R850_Tuner_Num)
{
	CloseDeviceInstance(hDevice[R850_Tuner_Num]);
	return true;
}
#endif

HI_U8 R850_data[51];

UINT8 R850_I2C_Write_Len(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_LEN_TYPE *I2C_Info)
{
     HI_S32 status = HI_SUCCESS;
    TUNER_I2C_DATA_S I2cDataStr;
    HI_U32 i=0;

    R850_data[0] = I2C_Info->RegAddr;
    for( i=1;i<=I2C_Info->Len;i++ )
    R850_data[i] = I2C_Info->Data[i-1];
    I2cDataStr.pu8ReceiveBuf = 0;
    I2cDataStr.u32ReceiveLength = 0;
    I2cDataStr.pu8SendBuf = R850_data;
    
    I2cDataStr.u32SendLength = I2C_Info->Len+1;
    
    qam_config_i2c_out(R850_Tuner_Num,1);
    
    status = tuner_i2c_send_data( g_stTunerOps[R850_Tuner_Num].enI2cChannel, g_stTunerOps[R850_Tuner_Num].u32TunerAddress, &I2cDataStr );

    if (HI_SUCCESS == status)
    {
        return RT_Success;
    }
    else
    {
        return RT_Fail;
    }
}



UINT8 R850_I2C_Read_Len(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_LEN_TYPE *I2C_Info)
{
    TUNER_I2C_DATA_S stDataStruct = {0};
    HI_S32 s32status = HI_SUCCESS;
    HI_U8 subaddress = 0;
    HI_S32 DataCunt = 0;
    
    qam_config_i2c_out(R850_Tuner_Num, 1); 

    stDataStruct.pu8ReceiveBuf = I2C_Info->Data;
    stDataStruct.u32ReceiveLength = I2C_Info->Len;
    stDataStruct.pu8SendBuf = &subaddress;
    stDataStruct.u32SendLength = 1;

    s32status = tuner_i2c_receive_data(g_stTunerOps[R850_Tuner_Num].enI2cChannel, g_stTunerOps[R850_Tuner_Num].u32TunerAddress, &stDataStruct);

    if(HI_SUCCESS != s32status)
    {
        HI_ERR_TUNER( "tuner_i2c_receive_data error s32status = 0x%x\n", s32status );
        return RT_Fail;
    }
    else
    {
        for(DataCunt = 0;DataCunt < I2C_Info->Len;DataCunt ++)
        {
            I2C_Info->Data[DataCunt] = R850_Convert(I2C_Info->Data[DataCunt]);
        }

        return RT_Success;
    }
}



UINT8 R850_I2C_Write(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_TYPE *I2C_Info)
{
    HI_S32 status = RT_Success;
    TUNER_I2C_DATA_S I2cDataStr;

    R850_data[0] = I2C_Info->RegAddr;
    R850_data[1] = I2C_Info->Data;
    I2cDataStr.pu8ReceiveBuf = 0;
    I2cDataStr.u32ReceiveLength = 0;
    I2cDataStr.pu8SendBuf = R850_data;
    I2cDataStr.u32SendLength = 2;
    qam_config_i2c_out(R850_Tuner_Num,1);

    status = tuner_i2c_send_data( g_stTunerOps[R850_Tuner_Num].enI2cChannel, g_stTunerOps[R850_Tuner_Num].u32TunerAddress, &I2cDataStr );
    if (HI_SUCCESS == status)
    {
        return RT_Success;
    }
    else
    {
        HI_ERR_TUNER("<0>write_I2C error, 0x%x\n", status);
        return RT_Fail;
    }
}


int R850_Convert(int InvertNum)
{
	int ReturnNum = 0;
	int AddNum    = 0x80;
	int BitNum    = 0x01;
	int CuntNum   = 0;

	for(CuntNum = 0;CuntNum < 8;CuntNum ++)
	{
		if(BitNum & InvertNum)
			ReturnNum += AddNum;

		AddNum /= 2;
		BitNum *= 2;
	}

	return ReturnNum;
}
