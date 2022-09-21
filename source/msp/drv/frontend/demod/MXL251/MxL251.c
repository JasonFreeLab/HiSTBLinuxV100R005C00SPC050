/*******************************************************************************
 *
 * FILE NAME          : example254.c
 *
 * AUTHOR             : Mariusz Murawski
 *
 * DATE CREATED       : 07/15/2012
 *
 * DESCRIPTION        : Example code of MxL_HRCLS MxLWare API
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <semaphore.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/semaphore.h>

#include "hi_type.h"

#include "drv_i2c_ext.h"
#include "drv_gpioi2c_ext.h"
#include "drv_gpio_ext.h"
#include "hi_drv_gpioi2c.h"
#include "hi_debug.h"
#include "hi_drv_file.h"

#include "hi_drv_stat.h"
#include "hi_drv_dev.h"
#include "hi_drv_reg.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_proc.h"

#include "drv_tuner_ext.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_diseqc.h"
#include "drv_demod.h"


#include "MxL251SF_PhyCtrlApi.h"
#include "MxL251SF_PhyCfg.h"
#include "MxL_Debug.h"
#include "MxL251SF_OEM_Drv.h"

#include "hi_type.h"
#include "drv_i2c_ext.h"
#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_drv_proc.h"
#include "hi_drv_sys.h"

#include "hi_type.h"
#include "hi_unf_i2c.h"
#include "drv_tuner_ext.h"
#include "drv_demod.h"


//#include "tuner.h"
/************************************************************************************
  Device ID used in this sample code.
  If more Hercules devices are used at the same time, they should have
  consecutive.
  This is customer's application responsibility to enumerate devices.
 ************************************************************************************/
#define HRCLS_DEVICE_ID 0

#define HRCLS_EXAMPLE_CODE_DEVICE "MxL214"
#define HRCLS_EXAMPLE_CODE_VERSION "1.10"

/************************************************************************************
  Default carystal capacitors value. This value is platform dependent.
 ************************************************************************************/
#define HRCLS_XTAL_CAP_VALUE 0 
#define HRCLS_I2C_ADDRESS 80
//#define HRCLS_PORT_MAX 4
#define MAX_TUNER (2)
/************************************************************************************
  Firmware filename.
 ************************************************************************************/
#define MXL251_CONNCECT_TIMEOUT	1000		/* ms */ 
static HI_U32 s_u32mxl251ConnectTimeout = MXL251_CONNCECT_TIMEOUT;

HI_BOOL  g_Mxl251IninFlag = 0;
HI_U32  u32ResetGpioNo = 0;

MXL_COMMAND_T mxlCmd;


MXL_STATUS DevDeviceResetCfg(UINT8 i2cAddr)
{
    //MXL_STATUS status = MXL_TRUE;
    //MXL_COMMAND_T mxlCmd;

    /* Reset Chip, Customer should fill function "MxL251_Ctrl_ResetMxL251SF" to toggle reset pin */
    MXL_STATUS mxlStatus;
    //MxL_DLL_PRINT0("Reseting ...");
    mxlCmd.commandId = MXL_DEV_DEVICE_RESET_CFG;
    mxlCmd.cmdDevDeviceResetCfg.I2cSlaveAddr = i2cAddr;  	
    mxlStatus = MxLWare251SF_API_ConfigDevice(&mxlCmd);
    //MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}

MXL_STATUS DevXtalSettingsCfg(UINT8 i2cAddr, UINT32 xtalFreq, UINT32 xtalCap, UINT32 xtalClkSharing, UINT32 ltEnable, UINT32 spltEnable)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    MxL_DLL_PRINT0("Configure Xtal Settings...");
    mxlCmd.commandId = MXL_DEV_XTAL_SETTINGS_CFG;
    mxlCmd.cmdDevXtalSettingsCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDevXtalSettingsCfg.DigXtalFreq = (MXL_XTAL_FREQ_E)xtalFreq;
    mxlCmd.cmdDevXtalSettingsCfg.XtalCap = xtalCap;
    mxlCmd.cmdDevXtalSettingsCfg.XtalClkSharing = (MXL_XTAL_CLK_SHARING_E)xtalClkSharing;
    mxlCmd.cmdDevXtalSettingsCfg.LoopThruEnable = (MXL_BOOL)ltEnable;
    mxlCmd.cmdDevXtalSettingsCfg.SplitterEnable = (MXL_BOOL)spltEnable;
    mxlStatus = MxLWare251SF_API_ConfigDevice(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}

MXL_STATUS DevVersionInfoReq(UINT8 i2cAddr, UINT8* devIdPtr, UINT8* fwLoadedPtr)
{
    MXL_STATUS mxlStatus = MXL_TRUE;
    //MXL_COMMAND_T mxlCmd;

    *devIdPtr    = 0; // Default to 'unknown' device id (0)
    *fwLoadedPtr = 0; // Default to no firmware

    mxlCmd.commandId = MXL_DEV_VERSION_INFO_REQ;
    mxlCmd.cmdDevVersionInfoReq.I2cSlaveAddr = i2cAddr;

    if (MXL_TRUE != MxLWare251SF_API_GetDeviceStatus(&mxlCmd))
    {
    MxL_DLL_ERROR0("MXL_DEV_VERSION_INFO_REQ failed\n");
    return MXL_FALSE;
    }

    MxL_DLL_PRINT0("DevId=%d DevVer=%d\nMxLWare: %d.%d.%d.%d-RC%d Firmware:%d.%d.%d.%d-RC%d Bootloader:%d.%d.%d.%d\n",
         mxlCmd.cmdDevVersionInfoReq.DevId,
         mxlCmd.cmdDevVersionInfoReq.DevVer,
         mxlCmd.cmdDevVersionInfoReq.MxLWareVer[0], 
         mxlCmd.cmdDevVersionInfoReq.MxLWareVer[1], 
         mxlCmd.cmdDevVersionInfoReq.MxLWareVer[2], 
         mxlCmd.cmdDevVersionInfoReq.MxLWareVer[3],
         mxlCmd.cmdDevVersionInfoReq.MxLWareRCVer,
         mxlCmd.cmdDevVersionInfoReq.FirmwareVer[0], 
         mxlCmd.cmdDevVersionInfoReq.FirmwareVer[1], 
         mxlCmd.cmdDevVersionInfoReq.FirmwareVer[2], 
         mxlCmd.cmdDevVersionInfoReq.FirmwareVer[3],
         mxlCmd.cmdDevVersionInfoReq.FirmwareRCVer,
         mxlCmd.cmdDevVersionInfoReq.BootLoaderVer[0], 
         mxlCmd.cmdDevVersionInfoReq.BootLoaderVer[1], 
         mxlCmd.cmdDevVersionInfoReq.BootLoaderVer[2], 
         mxlCmd.cmdDevVersionInfoReq.BootLoaderVer[3]
        );

    *devIdPtr    = mxlCmd.cmdDevVersionInfoReq.DevId;
    *fwLoadedPtr = !(mxlCmd.cmdDevVersionInfoReq.FirmwareVer[0] == 0 
                && mxlCmd.cmdDevVersionInfoReq.FirmwareVer[1] == 0 
                && mxlCmd.cmdDevVersionInfoReq.FirmwareVer[2] == 0 
                && mxlCmd.cmdDevVersionInfoReq.FirmwareVer[3] == 0);
    return mxlStatus;
}

struct semaphore mxl251_sem;

static HI_U8  g_Mxl251Fireware[]= 
{
    #include "./MxL251SF_FW.h"
};

/* Example code of MXL_DEV_FIRMWARE_DOWNLOAD_CFG API */
MXL_STATUS DevFirmwareDownloadCfg(UINT8 i2cAddr, SINT8* fname)
{
    #define MAX_FW_BUFFER_SIZE 60000

    MXL_STATUS mxlStatus = MXL_TRUE;
    //MXL_COMMAND_T mxlCmd;

    /************************************************************************************
    Open firmware file in binary mode
    ************************************************************************************/
    UINT16 firmwareSize = 0;

    firmwareSize =sizeof(g_Mxl251Fireware)/sizeof(HI_U8); 

    mxlCmd.commandId = MXL_DEV_VERSION_INFO_REQ;
    mxlCmd.cmdDevVersionInfoReq.I2cSlaveAddr = i2cAddr;
    if (MXL_TRUE != MxLWare251SF_API_GetDeviceStatus(&mxlCmd))
    {
    MxL_DLL_ERROR0("MXL_DEV_VERSION_INFO_REQ failed\n");
    return MXL_FALSE;
    }

    // Only download firmware if firmware has not been not loaded
    mxlCmd.commandId = MXL_DEV_FIRMWARE_DOWNLOAD_CFG;
    mxlCmd.cmdDevFirmwareDownloadCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDevFirmwareDownloadCfg.MbinBufferSize = firmwareSize;
    mxlCmd.cmdDevFirmwareDownloadCfg.MbinBufferPtr = g_Mxl251Fireware;

    MxL_DLL_PRINT0("MXL_DEV_FIRMWARE_DOWNLOAD_CFG ...");
    mxlStatus = MxLWare251SF_API_ConfigDevice(&mxlCmd);
    if (MXL_TRUE == mxlStatus) 
    	MxL_DLL_PRINT0("\nFirmware was successfully downloaded (status=%d)\n", mxlStatus);
    else                       
    	MxL_DLL_ERROR0("\nFirmware download failed (status=%d)\n", mxlStatus);

    return mxlStatus;
}

/* Example code for MXL_DEV_OVERWRITE_DEFAULT_CFG API */
MXL_STATUS DevOverwriteDefaultCfg(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    MxL_DLL_PRINT0("OverWrite Demod Defualt Settings...");
    mxlCmd.commandId = MXL_DEV_OVERWRITE_DEFAULT_CFG;
    mxlCmd.cmdDevOverwriteDefaultCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDevOverwriteDefaultCfg.DemodId = demodId;
    mxlStatus = MxLWare251SF_API_ConfigDevice(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus); 
    return mxlStatus;
}

/* Example code for MXL_DEMOD_SYMBOL_RATE_CFG API */
MXL_STATUS DemodSymbolRateCfg(
    UINT8 i2cAddr, 
    MXL_DEMOD_ID_E demodId, 
    MXL_SYM_TYPE_E symbolType, /* SYM_TYPE_J83A=0, SYM_TYPE_J83B=1, SYM_TYPE_USER_DEFINED_J83A=2, SYM_TYPE_USER_DEFINED_J83B=3, SYM_TYPE_OOB=4 */
    UINT32 symbolRate, 
    UINT32 symbolRate256, 
    MXL_OOB_SYM_RATE_E oobSymbolRate /* SYM_RATE_0_772MHz=0, SYM_RATE_1_024MHz=1, SYM_RATE_1_544MHz=2 */)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    MxL_DLL_PRINT0("Configure SymbolRate...");

    mxlCmd.commandId = MXL_DEMOD_SYMBOL_RATE_CFG;
    mxlCmd.cmdDemodSymbolRateCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodSymbolRateCfg.DemodId = demodId;
    /* For Symbol Type SYM_TYPE_J83A, MxlWare use defualt settings, 
    * ignore SymbolRate &  SymbolRate256. Refer to MxLWare API Doc */
    mxlCmd.cmdDemodSymbolRateCfg.SymbolType = symbolType; // SYM_TYPE_J83A; 
    mxlCmd.cmdDemodSymbolRateCfg.SymbolRate = symbolRate; // 0.0f;
    mxlCmd.cmdDemodSymbolRateCfg.SymbolRate256 = symbolRate256; // 0.0f;
    mxlCmd.cmdDemodSymbolRateCfg.OobSymbolRate = oobSymbolRate; // 0.0f;
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);

//  printf("DbgMsg: %s %d %d %d %d %d\n ",
//                      __FUNCTION__, 
//                      mxlCmd.cmdDemodSymbolRateCfg.I2cSlaveAddr,
//                      mxlCmd.cmdDemodSymbolRateCfg.DemodId,
//                      mxlCmd.cmdDemodSymbolRateCfg.SymbolType,
//                      mxlCmd.cmdDemodSymbolRateCfg.SymbolRate,
//                      mxlCmd.cmdDemodSymbolRateCfg.SymbolRate256,
//                      mxlCmd.cmdDemodSymbolRateCfg.OobSymbolRate);
    return mxlStatus;
}

/* Example code for MXL_DEMOD_ANNEX_QAM_TYPE_CFG API */
MXL_STATUS DemodAnnexQamTypeCfg(
    UINT8 i2cAddr, 
    MXL_DEMOD_ID_E demodId, 
    MXL_ANNEX_TYPE_E annexType, /* ANNEX_B = 0, ANNEX_A=1 */
    MXL_BOOL autoDetectQamType, 
    MXL_BOOL autoDetectMode, 
    MXL_QAM_TYPE_E qamType /* QAM16=0, QAM64=1, QAM256=2, QAM1024=3, QAM32=4, QAM128=5, QPSK=6 */)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    MxL_DLL_PRINT0("Configure QAM Type...");

    mxlCmd.commandId = MXL_DEMOD_ANNEX_QAM_TYPE_CFG;
    mxlCmd.cmdDemodAnnexQamTypeCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodAnnexQamTypeCfg.DemodId = demodId;
    mxlCmd.cmdDemodAnnexQamTypeCfg.AnnexType = annexType; // ANNEX_A;
    mxlCmd.cmdDemodAnnexQamTypeCfg.AutoDetectQamType = autoDetectQamType; // MXL_DISABLE;
    mxlCmd.cmdDemodAnnexQamTypeCfg.AutoDetectMode = autoDetectMode; // MXL_DISABLE;
    mxlCmd.cmdDemodAnnexQamTypeCfg.QamType = qamType; // QAM64;
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);

//  printf("bgMsg: %s %d %d %d %d %d %d\n", 
//                        __FUNCTION__,
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.I2cSlaveAddr = i2cAddr,
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.DemodId = demodId,
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.AnnexType = annexType, 
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.AutoDetectQamType = autoDetectQamType,
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.AutoDetectMode = autoDetectMode,
//                        mxlCmd.cmdDemodAnnexQamTypeCfg.QamType = qamType);
    return mxlStatus;
}

/* Example code for MXL_DEMOD_ADC_IQ_FLIP_CFG API */
MXL_STATUS DemodAdcIqFlipCfg(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL adcIqFlip)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    /* Configure Demod's ADC IQ flip Settings (Optional Step) */
    MxL_DLL_PRINT0("Configure ADC IQ Flip...");

    mxlCmd.commandId = MXL_DEMOD_ADC_IQ_FLIP_CFG;
    mxlCmd.cmdDemodAdcIqFlipCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodAdcIqFlipCfg.DemodId = demodId;
    mxlCmd.cmdDemodAdcIqFlipCfg.AdcIqFlip = adcIqFlip; // MXL_ENABLE;
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);

//  printf("DbgMsg: %s %d %d %d %d\n ",
//                      __FUNCTION__, 
//                      mxlCmd.cmdDemodAdcIqFlipCfg.I2cSlaveAddr = i2cAddr,
//                      mxlCmd.cmdDemodAdcIqFlipCfg.DemodId = demodId,
//                      mxlCmd.cmdDemodAdcIqFlipCfg.AdcIqFlip = adcIqFlip);

    return mxlStatus;
}

/* Example code for MXL_DEMOD_CLK_POLARITY_CFG API */
MXL_STATUS DemodClkPolarityCfg(
    UINT8 i2cAddr, 
    MPEG_CLK_FMT_E mpegClkPol, /* MPEG_CLK_POSITIVE=0, MPEG_CLK_NEGATIVE=1 */
    MPEG_DRV_STRENGTH_MODE_E mpegClkPadDrv /* 1X=0, 2X=1, 3X=1, 4X=1, 5X=1, 6X=1, 7X=1, 8X=1 */ )
{
    /* Configure Global MPEG OUT Clock Polarity & Driver Strength Settings */
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    mxlCmd.commandId = MXL_DEMOD_CLK_POLARITY_CFG;
    mxlCmd.cmdDemodClkPolarityCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodClkPolarityCfg.MpegClkPol = mpegClkPol; // MPEG_CLK_POSITIVE;
    mxlCmd.cmdDemodClkPolarityCfg.MpegClkPadDrv = mpegClkPadDrv; // MPEG_DRV_MODE_4X;
    MxL_DLL_PRINT0("Configure Global MPEG Out Clock Settings...");
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}

/* Example code for MXL_DEMOD_MPEG_OUT_CFG API */
MXL_STATUS DemodMpegOutCfg(
    UINT8 i2cAddr, 
    MXL_DEMOD_ID_E demodId, 
    MPEG_DATA_FMT_E lsbOrMsbFirst,      /* MPEG_SERIAL_LSB_1ST=0, MPEG_SERIAL_MSB_1ST=1*/
    MPEG_DATA_FMT_E mpegSyncPulseWidth, /* MPEG_SYNC_WIDTH_BIT=0, MPEG_SYNC_WIDTH_BYTE=1*/
    MPEG_CLK_FMT_E mpegValidPol,        /* MPEG_CLK_POSITIVE=0, MPEG_CLK_NEGATIVE=1 */
    MPEG_CLK_FMT_E mpegSyncPol,         /* MPEG_CLK_POSITIVE=0, MPEG_CLK_NEGATIVE=1 */
    MPEG_CLK_RATE_E mpegClkFreq,        /* MPEG_CLK_5_33MHz=0, MPEG_CLK_8_00MHz, 
                                           MPEG_CLK_10_66MHz, MPEG_CLK_21_33MHz, 
                                           MPEG_CLK_32_00MHz, MPEG_CLK_42_66MHz, 
                                           MPEG_CLK_64_00MHz, MPEG_CLK_85_33MHz*/
    MXL_BOOL mpegErrorIndication, 
    MXL_BOOL mpeg3WireModeEnable, 
    MPEG_DRV_STRENGTH_MODE_E PAD_MPSYN_DRV, /* MPEG_DRV_MODE_1X = 0, MPEG_DRV_MODE_2X, 
                                               MPEG_DRV_MODE_3X, MPEG_DRV_MODE_4X, 
                                               MPEG_DRV_MODE_5X, MPEG_DRV_MODE_6X, 
                                               MPEG_DRV_MODE_7X, MPEG_DRV_MODE_8X*/
    MPEG_DRV_STRENGTH_MODE_E PAD_MPDAT_DRV, 
    MPEG_DRV_STRENGTH_MODE_E PAD_MPVAL_DRV)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    /* Configure MPEG Interface Settings */
    mxlCmd.commandId = MXL_DEMOD_MPEG_OUT_CFG;
    mxlCmd.cmdDemodMpegOutCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodMpegOutCfg.DemodId = demodId;
    mxlCmd.cmdDemodMpegOutCfg.LsbOrMsbFirst = lsbOrMsbFirst; // MPEG_SERIAL_LSB_1ST;
    mxlCmd.cmdDemodMpegOutCfg.MpegSyncPulseWidth = mpegSyncPulseWidth; // MPEG_SYNC_WIDTH_BIT;
    mxlCmd.cmdDemodMpegOutCfg.MpegValidPol = mpegValidPol; // MPEG_CLK_POSITIVE;
    mxlCmd.cmdDemodMpegOutCfg.MpegSyncPol  = mpegSyncPol; // MPEG_CLK_POSITIVE;
    mxlCmd.cmdDemodMpegOutCfg.MpegClkFreq  = mpegClkFreq; // MPEG_CLK_21_33MHz;
    mxlCmd.cmdDemodMpegOutCfg.MpegErrorIndication = mpegErrorIndication; // MXL_DISABLE;
    mxlCmd.cmdDemodMpegOutCfg.Mpeg3WireModeEnable = mpeg3WireModeEnable; // MXL_DISABLE;
    mxlCmd.cmdDemodMpegOutCfg.MpegPadDrv.PAD_MPSYN_DRV = PAD_MPSYN_DRV; // MPEG_DRV_MODE_4X;
    mxlCmd.cmdDemodMpegOutCfg.MpegPadDrv.PAD_MPDAT_DRV = PAD_MPDAT_DRV; // MPEG_DRV_MODE_4X;
    mxlCmd.cmdDemodMpegOutCfg.MpegPadDrv.PAD_MPVAL_DRV = PAD_MPVAL_DRV; // MPEG_DRV_MODE_4X;
    MxL_DLL_PRINT0("Configure MPEG Out OF Settings...");
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}


/* Example code for MXL_TUNER_CHAN_TUNE_CFG API */
MXL_STATUS TunerChanTuneCfg(UINT8 i2cAddr, 
                                MXL_TUNER_ID_E tunerId, 
                                MXL_TUNER_POWER_MODE_E powerMode, 
                                UINT8 bandWidthInMhz, 
                                UINT32 centerFreqInHz)
{
    //MXL_COMMAND_T mxlCmd;
    MXL_STATUS mxlStatus;

    mxlCmd.commandId = MXL_TUNER_CHAN_TUNE_CFG;
    mxlCmd.cmdTunerChanTuneCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdTunerChanTuneCfg.TunerId = tunerId;
    mxlCmd.cmdTunerChanTuneCfg.TunerPowerMode = powerMode;
    mxlCmd.cmdTunerChanTuneCfg.BandWidthInMhz = bandWidthInMhz;
    mxlCmd.cmdTunerChanTuneCfg.CenterFrequencyInHz = centerFreqInHz;
    MxL_DLL_PRINT0("MXL_TUNER_CHAN_TUNE_CFG - Tune Tuner[%d] to CenterFrequency=%dHz,BandWidth=%dMhz...",
                  tunerId,
                  mxlCmd.cmdTunerChanTuneCfg.CenterFrequencyInHz,    
                  mxlCmd.cmdTunerChanTuneCfg.BandWidthInMhz);
    mxlStatus = MxLWare251SF_API_ConfigTuner(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}

MXL_STATUS EnhancedChanTuneCfg(UINT8 i2cAddr, 
                                   MXL_TUNER_ID_E tunerId, 
                                   MXL_TUNER_POWER_MODE_E powerMode, /* Not used */ 
                                   UINT8 bandWidthInMhz, 
                                   UINT32 centerFreqInHz,
                                   MXL_BOOL asiEnabled,
                                   MXL_BOOL ecosEnabled)
{
    UINT8 mxlStatus = MXL_TRUE;
    //MXL_COMMAND_T mxlCmd;

    /* Call API */
    mxlCmd.commandId = MXL_TUNER_ENHANCED_CHAN_TUNE_CFG;   
    mxlCmd.cmdTunerEnhancedChanTuneCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.TunerId = tunerId;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.TunerPowerMode = powerMode;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.BandWidthInMhz = bandWidthInMhz;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.CenterFrequencyInHz = centerFreqInHz;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.ASIEnable = asiEnabled;
    mxlCmd.cmdTunerEnhancedChanTuneCfg.ECOSEnable = ecosEnabled;
    MxL_DLL_PRINT0("MXL_TUNER_ENHANCED_CHAN_TUNE_CFG - Tune Tuner[%d] to CenterFrequency=%dHz,BandWidth=%dMhz...\n",
                  tunerId,
                  mxlCmd.cmdTunerEnhancedChanTuneCfg.CenterFrequencyInHz,    
                  mxlCmd.cmdTunerEnhancedChanTuneCfg.BandWidthInMhz);
    mxlStatus = MxLWare251SF_API_ConfigTuner(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);

    return (MXL_STATUS)mxlStatus;
}

/* Example code for MXL_DEMOD_ALL_LOCK_STATUS_REQ API */
MXL_STATUS DemodRestartCfg(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    mxlCmd.commandId = MXL_DEMOD_RESTART_CFG;
    mxlCmd.cmdDemodRestartCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodRestartCfg.DemodId = demodId;
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    return mxlStatus;  
}

/* Example code for MXL_TUNER_RF_RX_PWR_REQ API */
MXL_STATUS TunerRfRxPwrReq(UINT8 i2cAddr, UINT8 tunerId, SINT32* pwrPtr)
{
    //MXL_COMMAND_T mxlCmd;
    MXL_STATUS mxlStatus;
    MxL_DLL_PRINT0("Get rx power ...\n");

    mxlCmd.commandId = MXL_TUNER_RF_RX_PWR_REQ;
    mxlCmd.cmdTunerRfRxPwrReq.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdTunerRfRxPwrReq.TunerId = (MXL_TUNER_ID_E)tunerId;
    mxlStatus = MxLWare251SF_API_GetTunerStatus(&mxlCmd);

    MxL_DLL_PRINT0("Status =%d\n", mxlStatus);
    MxL_DLL_PRINT0("RxPower=%d\n", mxlCmd.cmdTunerRfRxPwrReq.RxPwrIndBmV);

    *pwrPtr = mxlCmd.cmdTunerRfRxPwrReq.RxPwrIndBmV;
    return mxlStatus;
}

/* Example code for MXL_DEMOD_RESET_STAT_COUNTER_CFG API */
MXL_STATUS DemodResetStatCounter(
    UINT8 i2cAddr, 
    MXL_DEMOD_ID_E demodId)
{
    /* Configure Reset Stat Counter */
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    mxlCmd.commandId = MXL_DEMOD_RESET_STAT_COUNTER_CFG ;
    mxlCmd.cmdDemodResetStatCounterCfg.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodResetStatCounterCfg.DemodId = demodId; 
    MxL_DLL_PRINT0("Configure Reset Stat Counter...");
    mxlStatus = MxLWare251SF_API_ConfigDemod(&mxlCmd);
    MxL_DLL_PRINT0("Status:%d\n", mxlStatus);
    return mxlStatus;
}

MXL_STATUS GetDemodBER(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId)
{
    MXL_STATUS mxlStatus;
    //MXL_COMMAND_T mxlCmd;

    MxL_DLL_PRINT0("Get Demod BER, UncodeBER, CER...\n");

    mxlCmd.commandId = MXL_DEMOD_SNR_REQ;
    mxlCmd.cmdDemodSnrReq.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodSnrReq.DemodId = demodId;
    mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);
    MxL_DLL_PRINT0("SNR=%d\n", mxlCmd.cmdDemodSnrReq.SNR);

    mxlCmd.commandId = MXL_DEMOD_BER_UNCODED_BER_CER_REQ;
    mxlCmd.cmdDemodBerUncodedBerCerReq.I2cSlaveAddr = i2cAddr;
    mxlCmd.cmdDemodBerUncodedBerCerReq.DemodId = demodId;
    mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);

    MxL_DLL_PRINT0("***** BER=%I64d, UncodedBER=%I64d, CER=%I64d ****", 
      mxlCmd.cmdDemodBerUncodedBerCerReq.BER, 
      mxlCmd.cmdDemodBerUncodedBerCerReq.UncodedBER, 
      mxlCmd.cmdDemodBerUncodedBerCerReq.CER);

    MxL_DLL_PRINT0("\n");
    return mxlStatus;
}

UINT32 u32CurrFreq;
UINT32 u32CurrSymbol;
	
HI_S32 mxl251_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S *pstChannel)
{

	MXL_STATUS status = 0;
#if 1
	UINT32 freqkHz;
	UINT8 bwMHz=8;
	MXL_QAM_TYPE_E qamType;
	UINT16 symbolRatekSps;
	MXL_ANNEX_TYPE_E annexType = ANNEX_A ;
	UINT32   u32SymbolRate;  
	UINT8           i2cAddr;
	MXL_DEMOD_ID_E  demodId;
	MXL_SYM_TYPE_E  symtype;
	//UINT8           devId;
	//UINT8           fwLoaded;
    //SINT32          rxPwr;
	
	if (u32TunerPort >= MAX_TUNER)
	{
		HI_ERR_TUNER("Bad u32TunerPort\n");
		return HI_FAILURE;
	}

	i2cAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
	
	switch(u32TunerPort)
	{
	    case 0:
		demodId = DEMOD0;
		break;
	    case 1:
		demodId = DEMOD1;
		break;
	    default:
		HI_ERR_TUNER( "u32TunerPort(%d) goes over the top(%d) \n",u32TunerPort,MAX_TUNER);
		return HI_FAILURE;
		break;
				
	}
    switch(pstChannel->enQamType)
	{
	    case QAM_TYPE_16:
		qamType =QAM16 ;
		break;
	    case QAM_TYPE_32:
		qamType =QAM32 ;
		break;
	    case QAM_TYPE_64:
		qamType =QAM64 ;
		break;
	    case QAM_TYPE_128:
		qamType =QAM128 ;
		break;
	    case QAM_TYPE_256:
		qamType = QAM256 ;
		break;
	    default:
		HI_ERR_TUNER( "QamType(%d) is unsupported \n",pstChannel->enQamType);
		return HI_FAILURE;
		break;				
	}

	g_stTunerOps[u32TunerPort].u32CurrQamMode = pstChannel->enQamType;
      
    switch(g_stTunerOps[u32TunerPort].enSigType)
	{ 
	    case HI_UNF_TUNER_SIG_TYPE_CAB:
		     annexType = ANNEX_A; 
			 symtype = SYM_TYPE_J83A;
		     bwMHz = 8;
		     break;
	    case HI_UNF_TUNER_SIG_TYPE_J83B:
		     annexType = ANNEX_B; 
			 symtype = SYM_TYPE_J83B;
		     bwMHz = 6;
		     break;
	    default:
		     break;
    }
    status = down_interruptible(&mxl251_sem);	
    symbolRatekSps = (pstChannel->unSRBW.u32SymbolRate / 1000) ; /*KHZ */

	// symbolRatekSps = pstChannel->unSRBW.u32SymbolRate / 1000; /* KHz */
	freqkHz = pstChannel->u32Frequency;
	u32CurrFreq = pstChannel->u32Frequency;
	u32CurrSymbol = pstChannel->unSRBW.u32SymbolRate;
	u32SymbolRate = (( pstChannel->unSRBW.u32SymbolRate /1000 ) * 1024) / 1000;			 /* kHZ*/

    // Overwrite default for each demod
	status = DevOverwriteDefaultCfg(i2cAddr, demodId);
	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("DevOverwriteDefaultCfg error\n");
		return status;
	}    

    // Config symbol rate
	//status = DemodSymbolRateCfg(i2cAddr,demodId,SYM_TYPE_USER_DEFINED_J83A,7040,7040,(MXL_OOB_SYM_RATE_E) SYM_RATE_0_772MHz);
	status = DemodSymbolRateCfg(i2cAddr,demodId,SYM_TYPE_USER_DEFINED_J83A,u32SymbolRate,u32SymbolRate,(MXL_OOB_SYM_RATE_E) SYM_RATE_0_772MHz);
	
	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("DemodSymbolRateCfg error\n");
		return status;
	}

    // Config Annex and Qam type
 
    status = DemodAnnexQamTypeCfg(i2cAddr, demodId, ANNEX_A,MXL_DISABLE,MXL_DISABLE, qamType);

	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("DemodAnnexQamTypeCfg error\n");
		return status;
	}

#if 0	
    // Config IQ flip
//        status = DemodAdcIqFlipCfg(i2cAddr,demodId, MXL_ENABLE);
    status = DemodAdcIqFlipCfg(i2cAddr,demodId, MXL_ENABLE);
	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("DemodAdcIqFlipCfg error\n");
		return status;
	}
#endif

    // Config global demod clock polarity
    status = DemodMpegOutCfg(
        i2cAddr, 
        demodId,
        MPEG_SERIAL_MSB_1ST, // MPEG_DATA_FMT_E LsbOrMsbFirst;
        MPEG_SYNC_WIDTH_BYTE, // MPEG_DATA_FMT_E MpegSyncPulseWidth;
        MPEG_CLK_NEGATIVE,   // MPEG_CLK_FMT_E  MpegValidPol;
        MPEG_CLK_NEGATIVE,   // MPEG_CLK_FMT_E  MpegSyncPol;
        MPEG_CLK_85_33MHz,   // MPEG_CLK_RATE_E MpegClkFreq;
        MXL_DISABLE,         // MXL_BOOL        MpegErrorIndication;
        MXL_DISABLE,         // MXL_BOOL        Mpeg3WireModeEnable;
        MPEG_DRV_MODE_1X,    // MPEG_DRV_STRENGTH_MODE_E PAD_MPSYN_DRV;
        MPEG_DRV_MODE_1X,    // MPEG_DRV_STRENGTH_MODE_E PAD_MPDAT_DRV;
        MPEG_DRV_MODE_1X     // MPEG_DRV_STRENGTH_MODE_E PAD_MPVAL_DRV
        );
	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("DemodMpegOutCfg error\n");
		return status;
	}  
	
#if 0
	//freqkHz = 666000;
	status = TunerChanTuneCfg(i2cAddr, demodId, MXL_TUNER_ENABLED_NORMAL, bwMHz, freqkHz*1000);
	
	if (status != MXL_SUCCESS)
	{
		HI_ERR_TUNER("TunerChanTuneCfg error\n");
		return status;
	}
	
#else

	status = EnhancedChanTuneCfg(i2cAddr, demodId, MXL_TUNER_ENABLED_NORMAL, bwMHz, freqkHz*1000,(MXL_BOOL)1/*ASIEnable*/,(MXL_BOOL)1/*ECOSEnable*/);

	if (status != MXL_SUCCESS)
	{
		HI_INFO_TUNER("EnhancedChanTuneCfg error\n");
		//return status;
	}
#endif	
	//L251_Ctrl_DelayUsec(10*1000);
	
	//status = DemodRestartCfg(i2cAddr, demodId);
	//if (status != MXL_SUCCESS)
	//{
	//	HI_ERR_TUNER("DemodRestartCfg error\n");
	//	return status;
	//}	
	#endif
	
	up(&mxl251_sem);
    return HI_SUCCESS;
}

  
/**************************************************************************************
   Example code for device initialization, and FB and NB tuner handover
 *************************************************************************************/

HI_S32 mxl251_init(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_UNF_TUNER_DEV_TYPE_E enTunerDevType)
{
      
  /************************************************************************************
    Driver initialization. Call this API function before any other function.
    Pass NULL as oemDataPtr as no extra data needs to be provided to OEM function.
    Device (devId) must be enumerated by customer software. devId enumaration must 
    always start from 0.    
   ************************************************************************************/

	MXL_STATUS status;
	UINT8           i2cAddr;
	//MXL_DEMOD_ID_E  demodId;
	UINT8           devId;
	UINT8           fwLoaded;
	//HI_S8 bRet = -1;

	if (u32TunerPort >= MAX_TUNER)
	{
		HI_ERR_TUNER("Bad u32TunerPort\n");
		return HI_FAILURE;
	}
	
	HI_INIT_MUTEX(&mxl251_sem);
	status = down_interruptible(&mxl251_sem);

	MxL251_I2C_SetPort(u32TunerPort);
	
	i2cAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
			
    status = DevDeviceResetCfg(i2cAddr);
    if(status != MXL_SUCCESS)
    {
    	HI_ERR_TUNER("DevDeviceResetCfg error\n");
    	up(&mxl251_sem);
    	return HI_FAILURE;
    }
    g_Mxl251IninFlag = HI_TRUE;

    /************************************************************************************
    Capacitor value is don't care.
    ************************************************************************************/
    status = DevXtalSettingsCfg(i2cAddr, XTAL_25MHz,30/*xtalCap*/,XTAL_CLK_SHARING_DISABLED/*XtalClkSharing*/, MXL_DISABLE /*ltEnable*/,  MXL_DISABLE /*spltEnable*/);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("DevXtalSettingsCfg error\n");
        up(&mxl251_sem);
        return HI_FAILURE;
    }

    /*
    * Check device HW and SW version; and if FW was already downloaded
    */
    status =  DevVersionInfoReq(i2cAddr, &devId, &fwLoaded);
    if (status != MXL_SUCCESS)
    {
    	HI_ERR_TUNER("DevVersionInfoReq error\n");
    	up(&mxl251_sem);
    	return HI_FAILURE;
    }
    			  
    if (!fwLoaded)
    {
        /* 
        * Download firmware; the example code testDevFirmwareDownloadCfg() also shows 
        *	- How to check if FW has already been downloaded
        *	- How to pick right firmware binary based on DevId (chip version)
        */
        status =   DevFirmwareDownloadCfg(i2cAddr, 0);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("DevFirmwareDownloadCfg error\n");
            up(&mxl251_sem);
            return HI_FAILURE;
        }

        /*
        * Check device HW and SW version again after FW download
        */
        status =  DevVersionInfoReq(i2cAddr, &devId, &fwLoaded);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("DevVersionInfoReq error\n");
            up(&mxl251_sem);
            return HI_FAILURE;
        }
      
        /* 
        * Config global demod clock polarity (applied to all demods)
        */
        status = DemodClkPolarityCfg(i2cAddr, MPEG_CLK_POSITIVE, MPEG_DRV_MODE_4X);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("DemodClkPolarityCfg error\n");
            return status;
        }
    }
    else
    {
        MxL_DLL_PRINT0("Firmware was already downloaded.\n");
    }
    up(&mxl251_sem);
  
    return HI_SUCCESS;
}

HI_S32 mxl251_get_snr(HI_U32 u32TunerPort, HI_U32* pu32SNR)
{
     //MXL_COMMAND_T mxlCmd;
     MXL_STATUS mxlStatus;
    
     mxlCmd.commandId = MXL_DEMOD_SNR_REQ;
     mxlCmd.cmdDemodAllLockStatusReq.I2cSlaveAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
     mxlCmd.cmdDemodAllLockStatusReq.DemodId = u32TunerPort;
     	 
     mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);
     
     if (mxlStatus != MXL_SUCCESS)
     {
    	 HI_ERR_TUNER("MxLWare251SF_API_GetDemodStatus error\n");
    	 return HI_FAILURE;
     }
     
        pu32SNR[0] = (HI_U32)((mxlCmd.cmdDemodSnrReq.SNR)/100);
		
	return HI_SUCCESS;
}
HI_VOID mxl251_connect_timeout(HI_U32 u32ConnectTimeout)
{
    s_u32mxl251ConnectTimeout = u32ConnectTimeout;
    return;
}
HI_S32 mxl251_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType)
{
	 return 0; 
}
HI_S32 mxl251_get_status (HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E  *penTunerStatus)
{
    //MXL_COMMAND_T mxlCmd;
    MXL_STATUS mxlStatus;
    TUNER_ACC_QAM_PARAMS_S CurChannel;

    HI_TUNER_CHECKPOINTER( penTunerStatus);
    /* Check tuner port and init. */
    if (u32TunerPort >= MAX_TUNER)
    {
     HI_ERR_TUNER("Bad u32TunerPort\n");
     return HI_FAILURE;
    }

    CurChannel.enQamType = g_stTunerOps[u32TunerPort].u32CurrQamMode;
    CurChannel.u32Frequency = u32CurrFreq;
    CurChannel.unSRBW.u32SymbolRate = u32CurrSymbol;

    mxlCmd.commandId = MXL_DEMOD_ALL_LOCK_STATUS_REQ;
    mxlCmd.cmdDemodAllLockStatusReq.I2cSlaveAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
    mxlCmd.cmdDemodAllLockStatusReq.DemodId = u32TunerPort;
    	 
    mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);

    if (mxlStatus != MXL_SUCCESS)
    {
        HI_ERR_TUNER("MxLWare251SF_API_GetDemodStatus error\n");
        return HI_FAILURE;
    }
    // HI_ERR_TUNER("===mxl251_get_status ===, QamLockStatus:%d, FecLockStatus:%d, MpegLockStatus:%d, RetuneRequired:%d\n",
  					//CurChannel.enQamType,CurChannel.u32Frequency,CurChannel.unSRBW.u32SymbolRate,mxlCmd.cmdDemodAllLockStatusReq.QamLockStatus, mxlCmd.cmdDemodAllLockStatusReq.FecLockStatus, mxlCmd.cmdDemodAllLockStatusReq.MpegLockStatus, mxlCmd.cmdDemodAllLockStatusReq.RetuneRequired);

	 if( ( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.QamLockStatus )&&( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.FecLockStatus )&&
	  	( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.MpegLockStatus )&&( MXL_BOOL_FALSE ==  mxlCmd.cmdDemodAllLockStatusReq.RetuneRequired ))
	 {
		 *penTunerStatus = HI_UNF_TUNER_SIGNAL_LOCKED;
	 }
	 else if( ( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.QamLockStatus )&&( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.FecLockStatus )&&
	  	      ( MXL_LOCKED ==  mxlCmd.cmdDemodAllLockStatusReq.MpegLockStatus )&&( MXL_BOOL_TRUE ==  mxlCmd.cmdDemodAllLockStatusReq.RetuneRequired ))
	 	 {
		 	*penTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
			mxl251_connect(u32TunerPort, &CurChannel);
	 	 }
		 else
		 {
			 *penTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
		 }

	return HI_SUCCESS;
}

HI_S32 mxl251_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength)
{
    //MXL_COMMAND_T mxlCmd;
    MXL_STATUS status;
	
    SINT32 SignalStrength = 0;	

    status = TunerRfRxPwrReq( g_stTunerOps[u32TunerPort].u32TunerAddress,u32TunerPort, &SignalStrength);

    if (MXL_SUCCESS != status)
    {
	   HI_ERR_TUNER("mxl251_get_signal_strength error!\n");
          return HI_FAILURE;
    }

    SignalStrength = (HI_U32)(SignalStrength/1020 + 69);

    pu32SignalStrength[1] =SignalStrength;
	
    return HI_SUCCESS;
}

HI_S32 mxl251_get_ber(HI_U32 u32TunerPort, HI_U32 *pu32ber)
{
    //MXL_COMMAND_T mxlCmd;
    MXL_STATUS mxlStatus;
    HI_U32 i=0;
    HI_U32 j=0;
    HI_U32 au32Tmp = 0;
    HI_U32 au32Ber= 0;
    //UINT16 annexType = ANNEX_A_TYPE;

    // reset stat counter
    /*mxlStatus =  DemodResetStatCounter(g_stTunerOps[u32TunerPort].u32TunerAddress, u32TunerPort);

    if (mxlStatus != MXL_SUCCESS)
    {
     HI_ERR_TUNER("DemodResetStatCounter error\n");
     return HI_FAILURE;
    }

    msleep(1000);*/
    MxL_DLL_PRINT0("Get Demod BER, UncodeBER, CER...\n");
  
    mxlCmd.commandId = MXL_DEMOD_BER_UNCODED_BER_CER_REQ;
    mxlCmd.cmdDemodBerUncodedBerCerReq.I2cSlaveAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
    mxlCmd.cmdDemodBerUncodedBerCerReq.DemodId = u32TunerPort;
    mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);
  

    MxL_DLL_PRINT0("Get Demod Stat Counter ...\n");
    
    mxlCmd.commandId = MXL_DEMOD_STAT_COUNTERS_REQ;
    mxlCmd.cmdDemodStatCountersReq.I2cSlaveAddr = g_stTunerOps[u32TunerPort].u32TunerAddress;
    mxlCmd.cmdDemodStatCountersReq.DemodId = u32TunerPort;
    mxlStatus = MxLWare251SF_API_GetDemodStatus(&mxlCmd);
    
    MxL_DLL_PRINT0("***** CwCorrCount=%I64d, CwErrCount=%I64d, CwReceived=%I64d, CwUnerrCount=%I64d , CorrBits=%I64d, errMpeg=%I64d, receivedMpeg=%I64d ****\n", 
    mxlCmd.cmdDemodStatCountersReq.AccCwCorrCount, 
    mxlCmd.cmdDemodStatCountersReq.AccCwErrCount, 
    mxlCmd.cmdDemodStatCountersReq.AccCwReceived,
    mxlCmd.cmdDemodStatCountersReq.AccCwUnerrCount, 
    mxlCmd.cmdDemodStatCountersReq.AccCorrBits, 
    mxlCmd.cmdDemodStatCountersReq.AccErrMpeg, 
    mxlCmd.cmdDemodStatCountersReq.AccReceivedMpeg);
  

	if (mxlCmd.cmdDemodStatCountersReq.AccCwReceived > 0)
	{
		//cer
   		 au32Tmp = (HI_U32)mxl251_u64mod((HI_U64)(mxlCmd.cmdDemodStatCountersReq.AccCwErrCount *10000000) ,(mxlCmd.cmdDemodStatCountersReq.AccCwReceived *1));
		//ber FEC before 
		au32Ber = (HI_U32)mxl251_u64mod((HI_U64)(mxlCmd.cmdDemodStatCountersReq.AccCorrBits *6127),(mxlCmd.cmdDemodStatCountersReq.AccCwReceived));

		au32Ber  = au32Ber	+ 26*(au32Tmp);
 
		if (au32Ber != 0)
		{
			while (au32Ber >= 10)
			{
			    au32Ber = au32Ber /10;
			    i++;
				if(au32Ber >= 1000)
				{ 
				   j = i;
				   au32Tmp = au32Ber;
				   
				}
			}
		}

	    pu32ber[0] = (HI_U32)au32Ber;
	    pu32ber[1] = (HI_U32)(au32Tmp % 1000 );
	    pu32ber[2] = (HI_U32)(8 - i);
		
	}
	else
	{
	    pu32ber[0] = (HI_U32)1;
	    pu32ber[1] = (HI_U32)0;
	    pu32ber[2] = (HI_U32)0;

	}
	
    mxlStatus =  DemodResetStatCounter(g_stTunerOps[u32TunerPort].u32TunerAddress, u32TunerPort);

    if (mxlStatus != MXL_SUCCESS)
    {
     HI_ERR_TUNER("DemodResetStatCounter error\n");
     return HI_FAILURE;
    }

  return HI_SUCCESS;
}

