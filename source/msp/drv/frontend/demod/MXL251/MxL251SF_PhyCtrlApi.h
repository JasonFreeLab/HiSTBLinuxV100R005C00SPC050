/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCtrlApi.h
 * 
 * AUTHOR             : Brenndon Lee
 *                      Sunghoon Park
 *                      Richard Liu
 *                      Chien-Chen Chen
 *                      Jun Huang
 *
 * DATE CREATED       : 6/6/2010
 *                      7/6/2010
 *                      12/21/2010
 *                      06/16/2011
 *                      06/18/2011
 *
 * DESCRIPTION        : This file is header file for MxL251SF_PhyCtrlApi.cpp
 *
 ****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

#ifndef __MXL251SF_PHY_CTRL_API_H__
#define __MXL251SF_PHY_CTRL_API_H__

/*****************************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
*****************************************************************************************/
#include "MaxLinearDataTypes.h"

/*****************************************************************************************
    Macros
*****************************************************************************************/

/** @brief Max number of MxL HRCLS devices that can be managed by a MxLWare driver */
#define MXL251_HRCLS_MAX_NUM_DEVICES             2

#define MAX_251SF_DEVICES          4
#define MAX_251SF_DEMODS           2
#define MXL_VERSION_SIZE           4
#define MAX_COMMAND_DATA_SIZE      252 
#define MAX_NUM_CAL_FREQ           128
#define MAX_NUM_CHANNELS           8

/* The following macro enables integer calculation */
/* If you are using floating point calculation, please comment it out */
/* MxL251SF MMS float and int calculation controled by user */
/* However, MxL251SF driver supports only the conditional compile */
#define __MXL_INTEGER_CALC_STATISTICS__

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/* Command ID's  */
typedef enum
{
  /* MxLWare_API_ConfigDevice */
  MXL_DEV_DEVICE_RESET_CFG = 0,
  MXL_DEV_FIRMWARE_DOWNLOAD_CFG,
  MXL_DEV_XTAL_SETTINGS_CFG,
  MXL_DEV_POWER_MODE_CFG, 
  MXL_DEV_OVERWRITE_DEFAULT_CFG,
  MXL_DEV_PSM_CFG,

  /* MxLWare251SF_API_GetDeviceStatus */
  MXL_DEV_VERSION_INFO_REQ = 0x100,
  MXL_DEV_PSM_REQ,
  MXL_DEV_POWER_MODE_REQ,

  /* MxLWare251SF_API_ConfigDemod */
  MXL_DEMOD_SYMBOL_RATE_CFG = 0x200,
  MXL_DEMOD_MPEG_OUT_CFG,
  MXL_DEMOD_CLK_POLARITY_CFG,
  MXL_DEMOD_ANNEX_QAM_TYPE_CFG,
  MXL_DEMOD_INTR_MASK_CFG,
  MXL_DEMOD_INTR_CLEAR_CFG,
  MXL_DEMOD_RESET_STAT_COUNTER_CFG, 
  MXL_DEMOD_ADC_IQ_FLIP_CFG,
  MXL_DEMOD_EQUALIZER_FILTER_CFG,
  MXL_DEMOD_PSM_CFG,
  MXL_DEMOD_RESTART_CFG,
  MXL_DEMOD_INVERT_SPECTRUM_CFG,

  /* MxLWare251SF_API_GetDemodStatus */
  MXL_DEMOD_ANNEX_QAM_TYPE_REQ = 0x300,
  MXL_DEMOD_INTR_STATUS_REQ,
  MXL_DEMOD_QAM_LOCK_REQ,
  MXL_DEMOD_FEC_LOCK_REQ,
  MXL_DEMOD_MPEG_LOCK_REQ,
  MXL_DEMOD_SNR_REQ,
  MXL_DEMOD_BER_UNCODED_BER_CER_REQ,
  MXL_DEMOD_STAT_COUNTERS_REQ,
  MXL_DEMOD_CARRIER_OFFSET_REQ,
  MXL_DEMOD_EQUALIZER_FILTER_REQ,
  MXL_DEMOD_INTERLEAVER_DEPTH_REQ,
  MXL_DEMOD_TIMING_OFFSET_REQ,
  MXL_DEMOD_CLK_POLARITY_REQ,           
  MXL_DEMOD_MPEG_OUT_REQ,               
  MXL_DEMOD_PSM_REQ,
  MXL_DEMOD_ALL_LOCK_STATUS_REQ,
  MXL_DEMOD_CONSTELLATION_VALUES_REQ,

  /* MxLWare251SF_API_ConfigTuner */
  MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG = 0x400, 
  MXL_TUNER_CAL_DONE_CFG,               
  MXL_TUNER_DOWNLOAD_CAL_COEF_CFG,      
  MXL_TUNER_CHAN_TUNE_CFG,
  MXL_TUNER_AGC_LOCK_SPEED_CFG,
  MXL_TUNER_CAL_CUTOFF_FREQ_CFG,
  MXL_TUNER_ENHANCED_CHAN_TUNE_CFG,
#ifdef _TUNER_TEST_API_ENABLED_
  MXL_TUNER_TEST_CFG,
#endif // _TUNER_TEST_API_ENABLED_

  /* MxLWare251SF_API_GetTunerStatus */
  MXL_TUNER_LOCK_STATUS_REQ = 0x500, 
  MXL_TUNER_RF_RX_PWR_REQ,
  MXL_TUNER_CURR_SETTING_REQ,
  MXL_TUNER_DSCAL_INFO_REQ,
  MXL_TUNER_MONITOR_RX_PWR_REQ,

} MXL_CMD_TYPE_E;

/* MxL251SF Device Tuner ID options */
typedef enum
{
  TUNER0 = 0,
  TUNER1 = 1,
  MAX_NUM_TUNER = 2
} MXL_TUNER_ID_E;

/* MxL251SF Device Demodulator ID options */
typedef enum
{
  DEMOD0 = 0,
  DEMOD1 = 1,
  MAX_NUM_DEMOD = 2
} MXL_DEMOD_ID_E;

/* MxL251SF Device IF ID options */
typedef enum
{
  IF0 = 0,
  IF1 = 1,
  MXL_NUM_IF = 2
} MXL_IF_ID_E;

/* MXL_DEV_FIRMWARE_DOWNLOAD_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
  UINT16 MbinBufferSize;               /* IN, Firmware buffer size in byte unit */
  UINT8 *MbinBufferPtr;                /* IN, Pointer of the buffer that stores MBIN format firmware */
} MXL_FW_INFO_T, *PMXL_FW_INFO_T;

/* MXL_DEV_DEVICE_RESET_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
} MXL_DEV_RESET_T, *PMXL_DEV_RESET_T;

/* MXL_DEV_XTAL_SETTINGS_CFG */
typedef enum
{
  XTAL_16MHz = 0,
  XTAL_24MHz,
  XTAL_25MHz,
  XTAL_27MHz
} MXL_XTAL_FREQ_E;

typedef enum
{
  XTAL_CLK_SHARING_DISABLED = 0, // Both clockin and clockout disabled
  XTAL_CLK_SHARING_MASTER   = 1, // clockout=1, clockin=0 
  XTAL_CLK_SHARING_SLAVE    = 2, // clockout=0, clockin=1
} MXL_XTAL_CLK_SHARING_E;



typedef struct
{
  UINT8 I2cSlaveAddr;                     /* IN, I2C Address of MxL Device */
  MXL_XTAL_FREQ_E DigXtalFreq;            /* IN, XTAL Frequency, refers above */
  UINT8 XtalCap;                          /* IN, Internal Capacitor value in parallel with XTAL */
  MXL_XTAL_CLK_SHARING_E XtalClkSharing;  /* IN, XTAL clock sharing:  */
  MXL_BOOL LoopThruEnable;                /* IN, Enable or Disabling LoopThrough,1=Enable, 0=Disable */
  MXL_BOOL SplitterEnable;                /* IN, Enable or Disabling Splitter, 1=Enable, 0=Disable */ 
} MXL_XTAL_CFG_T, *PMXL_XTAL_CFG_T;

/* MXL_DEV_POWER_MODE_CFG and MXL_DEV_POWER_MODE_REQ*/
typedef enum
{
  POWER_MODE_SLEEP = 0,
  POWER_MODE_STANDBY,
  POWER_MODE_NORMAL,
} MXL_PWR_MODE_E; 

typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_PWR_MODE_E PowerMode;   /* IN, Power mode */
} MXL_PWR_MODE_CFG_T, *PMXL_PWR_MODE_CFG_T;

/* MXL_DEV_OVERWRITE_DEFAULT_CFG  */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;      /* IN, Demodulator ID */
} MXL_OVERWRITE_DEFAULT_CFG_T, *PMXL_OVERWRITE_DEFAULT_CFG_T;

/* MXL_DEV_VERSION_INFO_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                     /* IN, I2C Address of MxL Device */
  UINT8 DevId;                            /* OUT, Device Id of MxL Device */
  UINT8 DevVer;                           /* OUT, Device Version of MxL Device */
  UINT8 MxLWareVer[MXL_VERSION_SIZE];     /* OUT, MxLWare version information */      
  UINT8 FirmwareVer[MXL_VERSION_SIZE];    /* OUT, firmware version information */        
  UINT8 BootLoaderVer[MXL_VERSION_SIZE];  /* OUT, boot loader version information */  
  UINT8 MxLWareRCVer;                     /* OUT, MxLWare RC version information */  
  UINT8 FirmwareRCVer;                    /* OUT, firmware RC version information */  
} MXL_DEV_VERSION_INFO_T, *PMXL_DEV_VERSION_INFO_T;

/* MXL_DEMOD_SYMBOL_RATE_CFG */
typedef enum
{
  SYM_TYPE_J83A = 0,
  SYM_TYPE_J83B,
  SYM_TYPE_USER_DEFINED_J83A,
  SYM_TYPE_USER_DEFINED_J83B,
  SYM_TYPE_OOB
} MXL_SYM_TYPE_E;

typedef enum
{
  SYM_RATE_0_772MHz = 0, 
  SYM_RATE_1_024MHz,
  SYM_RATE_1_544MHz
} MXL_OOB_SYM_RATE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;               /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;           /* IN, Demodulator ID */
  MXL_SYM_TYPE_E SymbolType;        /* IN, symbol type */
#ifdef _MXL251_FIXEDPOINT_
  UINT32 SymbolRate;                /* IN, For user defined A/B symbol rate */
  UINT32 SymbolRate256;             /* IN, For user defined B symbol rate */
#else
  REAL32 SymbolRate;                /* IN, For user defined A/B symbol rate */
  REAL32 SymbolRate256;             /* IN, For user defined B symbol rate */
#endif
  MXL_OOB_SYM_RATE_E OobSymbolRate; /* IN, For OOB Symbol rate */
} MXL_SYMBOL_RATE_T, *PMXL_SYMBOL_RATE_T;

/* MXL_DEMOD_MPEG_OUT_CFG */
typedef enum
{
  MPEG_SERIAL_LSB_1ST = 0,
  MPEG_SERIAL_MSB_1ST,

  MPEG_SYNC_WIDTH_BIT = 0,
  MPEG_SYNC_WIDTH_BYTE
} MPEG_DATA_FMT_E;

typedef enum
{
  MPEG_ACTIVE_LOW = 0,
  MPEG_ACTIVE_HIGH,

  MPEG_CLK_POSITIVE  = 0,
  MPEG_CLK_NEGATIVE,

  MPEG_CLK_IN_PHASE = 0,
  MPEG_CLK_INVERTED,
} MPEG_CLK_FMT_E;

typedef enum
{
  MPEG_CLK_5_33MHz  = 0,
  MPEG_CLK_8_00MHz,
  MPEG_CLK_10_66MHz,
  MPEG_CLK_21_33MHz,
  MPEG_CLK_32_00MHz,
  MPEG_CLK_42_66MHz,
  MPEG_CLK_64_00MHz,
  MPEG_CLK_85_33MHz,
} MPEG_CLK_RATE_E;

typedef enum
{
  MPEG_DRV_MODE_1X = 0,
  MPEG_DRV_MODE_2X, 
  MPEG_DRV_MODE_3X,
  MPEG_DRV_MODE_4X,
  MPEG_DRV_MODE_5X,
  MPEG_DRV_MODE_6X,
  MPEG_DRV_MODE_7X,
  MPEG_DRV_MODE_8X,
} MPEG_DRV_STRENGTH_MODE_E;

typedef struct
{
  MPEG_DRV_STRENGTH_MODE_E PAD_MPSYN_DRV;
  MPEG_DRV_STRENGTH_MODE_E PAD_MPDAT_DRV;
  MPEG_DRV_STRENGTH_MODE_E PAD_MPVAL_DRV;
} MPEG_PAD_DRV_T, *PMPEG_PAD_DRV_T;

typedef struct
{
  UINT8           I2cSlaveAddr;        /* IN, I2C Address of MxL Device   */   
  MXL_DEMOD_ID_E  DemodId;             /* IN, Demodulator ID number */  
  MPEG_DATA_FMT_E LsbOrMsbFirst;       /* IN, In Serial mode, transmit MSB first or LSB */
  MPEG_DATA_FMT_E MpegSyncPulseWidth;  /* IN, In serial mode, it can be configured with either 1 bit or 1 byte. */
  MPEG_CLK_FMT_E  MpegValidPol;        /* IN, VALID polarity, active high or low */ 
  MPEG_CLK_FMT_E  MpegSyncPol;         /* IN, SYNC byte(0x47) indicator, Active high or low */
  MPEG_CLK_RATE_E MpegClkFreq;         /* IN, MPEG clock frequency for internal clock source */
  MXL_BOOL        MpegErrorIndication; /* IN, If enabled, TEI bit shall be set when TS packet is broken */
  MXL_BOOL        Mpeg3WireModeEnable; /* IN, 0: disable 3 wire mode 1: enable 3 wire mode*/
  MPEG_PAD_DRV_T  MpegPadDrv;          /* IN, Configure MPEG output pad drive strength */
} MXL_MPEG_OUT_CFG_T, *PMXL_MPEG_OUT_CFG_T;

/* MXL_DEMOD_CLK_POLARITY_CFG */
typedef struct
{
  UINT8                    I2cSlaveAddr;        /* IN, I2C Address of MxL Device   */   
  MPEG_CLK_FMT_E           MpegClkPol;          /* IN, MPEG data validity with clock, Rising or Falling edge */
  MPEG_DRV_STRENGTH_MODE_E MpegClkPadDrv;       /* IN, MPEG clock pad drive mode */
} MXL_CLK_POLARITY_CFG_T, *PMXL_CLK_POLARITY_CFG_T;

/* MXL_DEMOD_ANNEX_QAM_TYPE_CFG */
typedef enum
{
  ANNEX_B = 0,
  ANNEX_A
} MXL_ANNEX_TYPE_E;

typedef enum
{
  QAM16 = 0,
  QAM64,
  QAM256,
  QAM1024,
  QAM32,
  QAM128,
 MXL_QPSK
} MXL_QAM_TYPE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;       /* IN, Demodulator ID number */
  MXL_ANNEX_TYPE_E AnnexType;   /* IN, Annex-B or A */
  MXL_BOOL AutoDetectQamType;   /* IN, Enable or disable of Auto QAM detect */
  MXL_BOOL AutoDetectMode;      /* IN, Enable or disable of Auto Annex mode detet */
  MXL_QAM_TYPE_E QamType;       /* IN, manual mode, set QAM type directly */
} MXL_ANNEX_CFG_T, *PMXL_ANNEX_CFG_T;

/* MXL_TUNER_CHAN_TUNE_CFG */
typedef enum
{
  MXL_TUNER_DISABLED =0,
  MXL_TUNER_ENABLED_NORMAL = 1,
  MXL_TUNER_ENABLED_LOWPOWER = 2,
} MXL_TUNER_POWER_MODE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL251SF */
  MXL_TUNER_ID_E TunerId;     /* IN, Tuner identification number */
  MXL_TUNER_POWER_MODE_E TunerPowerMode;  /* IN, Tuner Power Mode */
  UINT8 BandWidthInMhz;       /* IN, NB channel bandwidth in MHz, 8 for 8Mhz, 6 for 6Mhz */
  UINT32 CenterFrequencyInHz; /* IN, NB center frequency in Hz */
} MXL_TUNER_CHAN_TUNE_CFG_T, *PMXL_TUNER_CHAN_TUNE_CFG_T;

/* MXL_TUNER_ENHANCED_CHAN_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL251SF */
  MXL_TUNER_ID_E TunerId;     /* IN, Tuner identification number */
  MXL_TUNER_POWER_MODE_E TunerPowerMode;  /* IN, Tuner Power Mode */
  UINT8 BandWidthInMhz;       /* IN, NB channel bandwidth in MHz, 8 for 8Mhz, 6 for 6Mhz */
  UINT32 CenterFrequencyInHz; /* IN, NB center frequency in Hz */
  MXL_BOOL ASIEnable;         /* IN, Auto Spectrum Inversion enable */
  MXL_BOOL ECOSEnable;        /* IN, Extended Carrier Offset Search enable */
} MXL_TUNER_ENHANCED_CHAN_TUNE_CFG_T, *PMXL_TUNER_ENHANCED_CHAN_TUNE_CFG_T;

#ifdef _TUNER_TEST_API_ENABLED_
/* MXL_TUNER_TEST_CFG */
typedef struct
{
  UINT8    I2cSlaveAddr;    /* IN, I2C Address of MxL Device */
  SINT8*   CmdString;       /* IN, Command String */ 
} MXL_TUNER_TEST_CFG_T, *PMXL_TUNER_TEST_CFG_T;
#endif // _TUNER_TEST_API_ENABLED_

/* MXL_DEMOD_INTR_MASK_CFG */
#define INTR_FEC_LOST_EN          0x0001
#define INTR_FEC_LOCK_EN          0x0002
#define INTR_MPEG_LOST_EN         0x0004
#define INTR_MPEG_LOCK_EN         0x0008
#define INTR_QAM_LOCK_GAINED_EN   0x0010
#define INTR_QAM_LOCK_LOST_EN     0x0020

typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  UINT16 IntrMask;            /* IN, interrupt MASK word */
} MXL_INTR_CFG_T, *PMXL_INTR_CFG_T;

/* MXL_DEMOD_INTR_STATUS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  UINT16 IntrStatus;          /* OUT, Interrupt status */
  UINT16 IntrMask;            /* OUT, Interrupt mask */
} MXL_INTR_STATUS_T, *PMXL_INTR_STATUS_T;

/* MXL_DEMOD_INTR_CLEAR_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  UINT16 IntrClear;           /* IN, Interrupt clear word */
} MXL_INTR_CLEAR_T, *PMXL_INTR_CLEAR_T;

/* MXL_DEMOD_FEC_LOCK_REQ, MXL_DEMOD_MPEG_LOCK_REQ, MXL_DEMOD_QAM_LOCK_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  MXL_BOOL Status;            /* OUT, Demod lock status, MXL_LOCKED=lock, MXL_UNLOCKED=unlock */
} MXL_DEMOD_LOCK_STATUS_T, *PMXL_DEMOD_LOCK_STATUS_T;

/* MXL_DEMOD_ALL_LOCK_STATUS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  MXL_BOOL QamLockStatus;     /* OUT, Demod Qam lock status, MXL_LOCKED=lock, MXL_UNLOCKED=unlock  */
  MXL_BOOL FecLockStatus;     /* OUT, Demod Fec lock status, MXL_LOCKED=lock, MXL_UNLOCKED=unlock  */
  MXL_BOOL MpegLockStatus;    /* OUT, Demod Mpeg lock status,MXL_LOCKED=lock, MXL_UNLOCKED=unlock  */
  MXL_BOOL RetuneRequired;    /* OUT, Demod Retune Required, MXL_BOOL_TRUE=required, MXL_BOOL_FALSE=not required */
} MXL_DEMOD_ALL_LOCK_STATUS_T, *PMXL_DEMOD_ALL_LOCK_STATUS_T;

/* MXL_DEMOD_SNR_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
#ifdef _MXL251_FIXEDPOINT_
  UINT32 SNR;
#else
  REAL32 SNR;                 /* OUT, SNR, float point format */
#endif
  UINT32 MseSize;             /* OUT, MSE size */
} MXL_DEMOD_SNR_INFO_T, *PMXL_DEMOD_SNR_INFO_T;

/* MXL_DEMOD_BER_UNCODED_BER_CER_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
#ifdef _MXL251_FIXEDPOINT_
  UINT64 BER;                 /* OUT, BER, float point format */
  UINT64 UncodedBER;          /* OUT, Uncoded BER, float point format */
  UINT64 CER;                 /* OUT, CW error rate, float point format */
#else
  REAL64 BER;                 /* OUT, BER, float point format */
  REAL64 UncodedBER;          /* OUT, Uncoded BER, float point format */
  REAL64 CER;                 /* OUT, CW error rate, float point format */
#endif
} MXL_DEMOD_BER_INFO_T, *PMXL_DEMOD_BER_INFO_T;

/* MXL_DEMOD_STAT_COUNTERS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  UINT64 AccCwCorrCount;      /* OUT, Accumulated corrected code words */
  UINT64 AccCwErrCount;       /* OUT, Accumulated uncorrected code words */
  UINT64 AccCwReceived;       /* OUT, Accumulated total received code words */
  UINT64 AccCwUnerrCount;     /* OUT, Accumulated counter for code words received */
  UINT64 AccCorrBits;         /* OUT, Accumulated counter for corrected bits */
  UINT64 AccErrMpeg;          /* OUT, Accumulated counter for erred mpeg frames */
  UINT64 AccReceivedMpeg;     /* OUT, Accumulated counter for received mpeg frames */
} MXL_DEMOD_STAT_COUNT_T, *PMXL_DEMOD_STAT_COUNT_T;

/* MXL_DEMOD_RESET_STAT_COUNTER_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
} MXL_RESET_COUNTER_T, *PMXL_RESET_COUNTER_T;

/* MXL_DEMOD_ANNEX_QAM_TYPE_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;      /* IN, Demodulator ID number */
  MXL_ANNEX_TYPE_E AnnexType;  /* OUT, Provide a current Annex Type */
  MXL_QAM_TYPE_E QamType;      /* OUT,  Provide a current QAM type */
} MXL_DEMOD_ANNEXQAM_INFO_T, *PMXL_DEMOD_ANNEXQAM_INFO_T;

/* MXL_DEMOD_CARRIER_OFFSET_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;      /* IN, Demodulator ID number */
#ifdef _MXL251_FIXEDPOINT_
  UINT64 CarrierOffset ;       /* OUT, Carrier offset frequency, MHz unit*/
#else
  REAL64 CarrierOffset ;       /* OUT, Carrier offset frequency, MHz unit*/
#endif
} MXL_DEMOD_CARRIEROFFSET_INFO_T, *PMXL_DEMOD_CARRIEROFFSET_INFO_T;

/* MXL_DEMOD_INTERLEAVER_DEPTH_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
  UINT8 InterDepthI;          /* OUT, Interleaver I */ 
  UINT8 InterDepthJ;          /* OUT, Interleaver J */
} MXL_INTERDEPTH_INFO_T, *PMXL_INTERDEPTH_INFO_T;

/* MXL_DEMOD_EQUALIZER_FILTER_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;        /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;    /* IN, Demodulator ID number */
#ifdef _MXL251_FIXEDPOINT_
  UINT32 FfeInfo[16];        /* OUT, FFE filter */
  UINT32 SpurInfo[32];       /* OUT, Spur filter */
  UINT32 DfeInfo[56];        /* OUT, DFE filter */
#else
  REAL32 FfeInfo[16];        /* OUT, FFE filter */
  REAL32 SpurInfo[32];       /* OUT, Spur filter */
  REAL32 DfeInfo[56];        /* OUT, DFE filter */
#endif
  UINT8 DsEqMainLocation;    /* OUT, Location of leading tap (in FFE) */
  UINT8 DsEqDfeTapNum;       /* OUT, Number of taps in DFE */
} MXL_DEMOD_EQUALFILTER_INFO_T, *PMXL_DEMOD_EQUALFILTER_INFO_T;

/* MXL_DEMOD_TIMING_OFFSET_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;
  MXL_DEMOD_ID_E DemodId;     /* IN, Demodulator ID number */
#ifdef _MXL251_FIXEDPOINT_
  SINT64 TimingOffset;        /* Timing offset (ppm unit) */
#else
  REAL64 TimingOffset;        /* Timing offset (ppm unit) */
#endif

} MXL_DEMOD_TIMINGOFFSET_INFO_T, *PMXL_DEMOD_TIMINGOFFSET_INFO_T;

/* MXL_DEMOD_CLK_POLARITY_REQ */
typedef struct
{
  UINT8                     I2cSlaveAddr;        /* IN, I2C Address of MxL Device   */   
  MPEG_CLK_FMT_E            MpegClkPol;          /* OUT, MPEG data validity with clock, Rising or Falling edge */
  MPEG_DRV_STRENGTH_MODE_E  MpegClkPadDrv;       /* OUT, MPEG clock pad drive mode */
} MXL_DEMOD_CLKPOLARITY_INFO_T, *PMXL_DEMOD_CLKPOLARITY_INFO_T;

/* MXL_DEMOD_MPEG_OUT_REQ */
typedef struct
{
  UINT8           I2cSlaveAddr;        /* IN, I2C Address of MxL Device   */   
  MXL_DEMOD_ID_E  DemodId;             /* IN, Demodulator ID number */  
  MPEG_DATA_FMT_E LsbOrMsbFirst;       /* OUT, In Serial mode, transmit MSB first or LSB */
  MPEG_DATA_FMT_E MpegSyncPulseWidth;  /* OUT, In serial mode, it can be configured with either 1 bit or 1 byte. */
  MPEG_CLK_FMT_E  MpegValidPol;        /* OUT, VALID polarity, active high or low */ 
  MPEG_CLK_FMT_E  MpegSyncPol;         /* OUT, SYNC byte(0x47) indicator, Active high or low */
  MPEG_CLK_RATE_E MpegClkFreq;         /* OUT, MPEG clock frequency for internal clock source */
  MXL_BOOL        MpegErrorIndication; /* OUT, If enabled, TEI bit shall be set when TS packet is broken */
  MXL_BOOL        Mpeg3WireModeEnable; /* OUT, 0 - 3 wire mode disabled  1 - 3 wire mode enabled*/
  MPEG_PAD_DRV_T  MpegPadDrv;          /* OUT, MPEG output pad drive strength configuration */
} MXL_MPEG_OUT_INFO_T, *PMXL_MPEG_OUT_INFO_T;

/* MXL_DEMOD_ADC_IQ_FLIP_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;        /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;    /* IN, Demodulator ID number */
  MXL_BOOL AdcIqFlip;        /* IN, Enable or disable Flip the I/Q path after ADC */
} MXL_ADCIQFLIP_CFG_T, *PMXL_ADCIQFLIP_CFG_T;

/* MXL_DEMOD_EQUALIZER_FILTER_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;      /* IN, Demodulator ID number */
  MXL_BOOL EqualizerSetting;   /* IN, Enable or disable Equalizer Bypass */
} MXL_EQUALIZER_CFG_T, *PMXL_EQUALIZER_CFG_T;

/* MXL_DEMOD_CONSTELLATION_VALUES_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;    /* IN, Demodulator ID number */
  SINT16 iVal;        /* OUT, value of DMDx_SOFTDEC_VALUE register */
  SINT16 qVal;        /* OUT, value of DMDx_SOFTDEC_VALUE register */
} MXL_DEMOD_CONSTELLATION_VAL_REQ_T, *PMXL_DEMOD_CONSTELLATION_VAL_REQ_T;

/* MXL_TUNER_CURR_SETTING_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;        /* IN, I2C Address of MxL Device */
  MXL_TUNER_ID_E TunerId;    /* IN, Tuner identification number */
  UINT8  BandwidthInMHz;     /* OUT, current setting of narrow band channel bandwidth, in MHz. 6 for 6MHz, 8 for 8MHz. */
  UINT32 CenterFrequencyInHz; /* OUT, current  RF center Frequency setting in Hz */
  MXL_TUNER_POWER_MODE_E TunerPowerMode; /* OUT, Tuner Power mode (DISABLED, ENABLED_NORAML, ENABLED_LOWPOWER) */
} MXL_TUNER_SETTINGS_T, *PMXL_TUNER_SETTINGS_T;

/* MXL_TUNER_LOCK_STATUS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;         /* IN, I2C Address of MxL Device */
  MXL_TUNER_ID_E TunerId;     /* IN, Tuner identification number */
  MXL_BOOL TunerLockStatus;   /* OUT, Status of Tuner Lock */
  MXL_BOOL AgcLockStatus;     /* OUT, Status of AGC Lock */
  MXL_BOOL TunerDoneStatus;   /* OUT, Status of Tuner Done */
} MXL_TUNER_LOCK_STATUS_T, *PMXL_TUNER_LOCK_STATUS_T;

/* MXL_TUNER_RF_RX_PWR_REQ */
typedef struct
{
  UINT8  I2cSlaveAddr;        /* IN, I2C Address of MxL Device */
  MXL_TUNER_ID_E TunerId;     /* IN, Tuner identification number */
  MXL_SYM_TYPE_E SymbolType;  /* IN, symbol type */
#ifdef _MXL251_FIXEDPOINT_
  SINT32 RxPwrIndBmV;         /* OUT, RF Input Power in dBmV */
#else
  REAL32 RxPwrIndBmV;         /* OUT, RF Input Power in dBmV */
#endif
} MXL_TUNER_RX_PWR_T, *PMXL_TUNER_RX_PWR_T;

/* MXL_TUNER_AGC_LOCK_SPEED_CFG */
typedef enum
{
  FAST_AGC_LOCK,
  NORMAL_AGC_LOCK
} MXL_AGC_LOCK_SPEED_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                /* IN, I2C Address of MxL Device */
  MXL_TUNER_ID_E TunerId;            /* IN, Tuner ID number */
  MXL_AGC_LOCK_SPEED_E AgcSpeedMode; /* IN, AGC lock speed */
} MXL_AGC_CTRL_SPEED_T, *PMXL_AGC_CTRL_SPEED_T;

/* MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG */
typedef struct
{
  UINT32 CalibFreqInHz;             /* IN, Frequency used to calibrate 251 internal rx power meter */
  SINT32 ReferencePwrIndBmV;        /* IN, Power level in dBmV of the reference signal at the frequency (8 fractional bits) */
} MXL_CAL_FREQ_T, *PMXL_CAL_FREQ_T;

typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  UINT8 NumCalFreq;            /* IN, The number of valid entries in CalFreq array */
  MXL_CAL_FREQ_T CalFreq[MAX_NUM_CAL_FREQ]; /* IN, CalFreq array */
} MXL_RX_PWR_CAL_T, *PMXL_RX_PWR_CAL_T;

/* MXL_TUNER_CAL_DONE_CFG */ 
typedef enum
{
  RX_PWR_CAL = 0,
  GAIN_STEP_ERRORS,
  IQ_TILT,
  IQ_AVG,
  CHAN_SCAN_TBL
} MXL_CAL_TYPE_E;

/* MXL_TUNER_CAL_DONE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_CAL_TYPE_E CalType;      /* IN, Calibration Type to be done */
  UINT32 CoefTableSize;        /* IN/OUT, Table size in byte that contains RX power calibration coeffcients */
  UINT8* CoefTblPtr;           /* IN, Pointer to the buffer that mxlware will fill up with calibration coeffcients */
} MXL_RX_PWR_CAL_COEF_INFO_T, *PMXL_RX_PWR_CAL_COEF_INFO_T;

/* MXL_TUNER_DOWNLOAD_CAL_COEF_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;          /* IN, I2C Address of MxL Device */
  MXL_CAL_TYPE_E CalType;      /* In, Rx_PWR_CAL type */
  UINT16 CoefTableSize;        /* IN, Table size in byte that contains RX power alibraton coeffcients */ 
  UINT8* CoefTblPtr;           /* IN, Ponter to the buffer that has calibration coeffcients */
} MXL_CAL_COEF_INFO_T, *PMXL_CAL_COEF_INFO_T;

/* MXL_TUNER_DSCAL_INFO_REQ */
typedef struct
{
  UINT8  I2cSlaveAddr;     /* IN, I2C Address of MxL Device */
  UINT32 outBufLen;        /* IN/OUT, Log file size in byte */ 
  UINT8* outBufPtr;        /* IN, Ponter to the buffer that has calibration coeffcients */
} MXL_GET_DSCAL_INFO_T, *PMXL_GET_DSCAL_INFO_T;

/* MXL_TUNER_CAL_CUTOFF_FREQ_CFG */
typedef struct
{
  UINT8    I2cSlaveAddr;    /* IN, I2C Address of MxL Device */
  UINT32   CutOffFreqInHz;  /* IN, Cut off frequency in Hz */ 
} MXL_TUNER_CAL_CUTOFF_FREQ_CFG_T, *PMXL_TUNER_CAL_SET_CUTOFF_FREQ_CFG_T;

/*  MXL_DEV_PSM_CFG and MXL_DEV_PSM_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
  MXL_BOOL LoopThruEnable;             /* IN/OUT, Enable or Disable LoopThrough (MXL_ENABLE = Enable)*/
  MXL_BOOL SplitterEnable;             /* IN/OUT, Enable or Disable Splitter (MXL_ENABLE = Enable)*/
} MXL_DEV_PSM_INFO_T, *PMXL_DEV_PSM_INFO_T;

/*  MXL_DEMOD_PSM_CFG and MXL_DEMOD_PSM_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E  DemodId;           /* IN, Demod Id */
  MXL_BOOL DemodEnable;              /* IN/OUT, MXL_ENABLE or MXL_DISABLE */
} MXL_DEMOD_PSM_INFO_T, *PMXL_DEMOD_PSM_INFO_T;

/* MXL_DEMOD_RESTART_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E DemodId;              /* IN, Demodulator ID */
} MXL_DEMOD_RESTART_CFG_T, *PMXL_DEMOD_RESTART_CFG_T;

/*  MXL_DEMOD_INVERT_SPECTRUM_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                /* IN, I2C Address of MxL Device */
  MXL_DEMOD_ID_E  DemodId;           /* IN, Demod Id */
} MXL_DEMOD_INVERT_SPECTRUM_CFG_T, *PMXL_DEMOD_INVERT_SPECTRUM_CFG_T;

/* MXL_TUNER_MONITOR_RX_PWR_REQ */
typedef struct
{
  UINT8  I2cSlaveAddr;        /* IN, I2C Address of MxL Device */
  MXL_TUNER_ID_E  TunerId;    /* IN, NB Channel ID number */
#ifdef _MXL251_FIXEDPOINT_
  SINT32 RxPwrIndBmV;         /* OUT, RF Input Power in dBmV */
#else
  REAL32 RxPwrIndBmV;         /* OUT, RF Input Power in dBmV */
#endif
} MXL_TUNER_MONITOR_RX_PWR_REQ_T, *PMXL_TUNER_MONITOR_RX_PWR_REQ_T;

#ifndef _LEGACY_API_INTERFACE_
/*****************************************************************************************
    API COMMAND interface structure 
*****************************************************************************************/

typedef struct
{
  MXL_CMD_TYPE_E commandId;  // Command Identifier

  union
  {
    // Ctrl_Wrap_ConfigDevice
    MXL_DEV_RESET_T                 cmdDevDeviceResetCfg;       // MXL_DEV_DEVICE_RESET_CFG
    MXL_XTAL_CFG_T                  cmdDevXtalSettingsCfg;      // MXL_DEV_XTAL_SETTINGS_CFG
    MXL_PWR_MODE_CFG_T              cmdDevPowerModeCfg;         // MXL_DEV_POWER_MODE_CFG
    MXL_FW_INFO_T                   cmdDevFirmwareDownloadCfg;  // MXL_DEV_FIRMWARE_DOWNLOAD_CFG
    MXL_OVERWRITE_DEFAULT_CFG_T     cmdDevOverwriteDefaultCfg;  // MXL_DEV_OVERWRITE_DEFAULT_CFG
    MXL_DEV_PSM_INFO_T              cmdDevPsmCfg;               // MXL_DEV_PSM_CFG

    // Ctrl_Wrap_GetDeviceStatus
    MXL_DEV_VERSION_INFO_T          cmdDevVersionInfoReq;       // MXL_DEV_VERSION_INFO_REQ
    MXL_DEV_PSM_INFO_T              cmdDevPsmReq;               // MXL_DEV_PSM_REQ
    MXL_PWR_MODE_CFG_T              cmdDevPowerModeReq;         // MXL_DEV_POWER_MODE_REQ

    // Ctrl_Wrap_ConfigDemod
    MXL_SYMBOL_RATE_T               cmdDemodSymbolRateCfg;      // MXL_DEMOD_SYMBOL_RATE_CFG
    MXL_MPEG_OUT_CFG_T              cmdDemodMpegOutCfg;         // MXL_DEMOD_MPEG_OUT_CFG
    MXL_CLK_POLARITY_CFG_T          cmdDemodClkPolarityCfg;     // MXL_DEMOD_CLK_POLARITY_CFG
    MXL_ANNEX_CFG_T                 cmdDemodAnnexQamTypeCfg;    // MXL_DEMOD_ANNEX_QAM_TYPE_CFG
    MXL_INTR_CFG_T                  cmdDemodIntrMaskCfg;        // MXL_DEMOD_INTR_MASK_CFG
    MXL_INTR_CLEAR_T                cmdDemodIntrClearCfg;       // MXL_DEMOD_INTR_CLEAR_CFG
    MXL_RESET_COUNTER_T             cmdDemodResetStatCounterCfg;// MXL_DEMOD_RESET_STAT_COUNTER_CFG
    MXL_ADCIQFLIP_CFG_T             cmdDemodAdcIqFlipCfg;       // MXL_DEMOD_ADC_IQ_FLIP_CFG
    MXL_EQUALIZER_CFG_T             cmdDemodEqualizerFilterCfg; // MXL_DEMOD_EQUALIZER_FILTER_CFG
    MXL_DEMOD_PSM_INFO_T            cmdDemodPsmCfg;             // MXL_DEMOD_PSM_CFG
    MXL_DEMOD_RESTART_CFG_T         cmdDemodRestartCfg;         // MXL_DEMOD_RESTART_CFG
    MXL_DEMOD_INVERT_SPECTRUM_CFG_T cmdDemodInvertSpectrumCfg;  // MXL_DEMOD_INVERT_SPECTRUM_CFG

    // Ctrl_Wrap_GetDemodStatus
    MXL_DEMOD_ANNEXQAM_INFO_T       cmdDemodAnnexQamTypeReq;    // MXL_DEMOD_ANNEX_QAM_TYPE_REQ
    MXL_INTR_STATUS_T               cmdDemodIntrStatusReq;      // MXL_DEMOD_INTR_STATUS_REQ
    MXL_DEMOD_LOCK_STATUS_T         cmdDemodQamLockReq;         // MXL_DEMOD_QAM_LOCK_REQ
    MXL_DEMOD_LOCK_STATUS_T         cmdDemodFecLockReq;         // MXL_DEMOD_FEC_LOCK_REQ
    MXL_DEMOD_LOCK_STATUS_T         cmdDemodMpegLockReq;        // MXL_DEMOD_MPEG_LOCK_REQ
    MXL_DEMOD_ALL_LOCK_STATUS_T     cmdDemodAllLockStatusReq;   // MXL_DEMOD_ALL_LOCK_STATUS_REQ
    MXL_DEMOD_SNR_INFO_T            cmdDemodSnrReq;             // MXL_DEMOD_SNR_REQ
    MXL_DEMOD_BER_INFO_T            cmdDemodBerUncodedBerCerReq;// MXL_DEMOD_BER_UNCODED_BER_CER_REQ
    MXL_DEMOD_STAT_COUNT_T          cmdDemodStatCountersReq;    // MXL_DEMOD_STAT_COUNTERS_REQ
    MXL_DEMOD_CARRIEROFFSET_INFO_T  cmdDemodCarrierOffsetReq;   // MXL_DEMOD_CARRIER_OFFSET_REQ
    MXL_DEMOD_EQUALFILTER_INFO_T    cmdDemodEqualizerFilterReq; // MXL_DEMOD_EQUALIZER_FILTER_REQ
    MXL_INTERDEPTH_INFO_T           cmdDemodInterleaverDepthReq;// MXL_DEMOD_INTERLEAVER_DEPTH_REQ
    MXL_DEMOD_TIMINGOFFSET_INFO_T   cmdDemodTimingOffsetReq;    // MXL_DEMOD_TIMING_OFFSET_REQ
    MXL_DEMOD_CLKPOLARITY_INFO_T    cmdDemodClkPolarityReq;     // MXL_DEMOD_CLK_POLARITY_REQ
    MXL_MPEG_OUT_INFO_T             cmdDemodMpegOutReq;         // MXL_DEMOD_MPEG_OUT_REQ
    MXL_DEMOD_PSM_INFO_T            cmdDemodPsmReq;             // MXL_DEMOD_PSM_REQ
    MXL_DEMOD_CONSTELLATION_VAL_REQ_T cmdDemodConstellValReq;   // MXL_DEMOD_CONSTELLATION_VALUES_REQ 

    // Ctrl_Wrap_ConfigTuner
    MXL_RX_PWR_CAL_T                    cmdTunerCreateRxPwrCalCoefCfg; // MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG
    MXL_RX_PWR_CAL_COEF_INFO_T          cmdTunerCalDoneCfg;            // MXL_TUNER_CAL_DONE_CFG
    MXL_CAL_COEF_INFO_T                 cmdTunerDownloadCalCoefCfg;    // MXL_TUNER_DOWNLOAD_CAL_COEF_CFG
    MXL_TUNER_CHAN_TUNE_CFG_T           cmdTunerChanTuneCfg;           // MXL_TUNER_CHAN_TUNE_CFG
    MXL_AGC_CTRL_SPEED_T                cmdTunerAgcLockSpeedCfg;       // MXL_TUNER_AGC_LOCK_SPEED_CFG
    MXL_TUNER_CAL_CUTOFF_FREQ_CFG_T     cmdTunerCalCutoffFreqCfg;      // MXL_TUNER_CAL_CUTOFF_FREQ_CFG
#ifdef _TUNER_TEST_API_ENABLED_
    MXL_TUNER_TEST_CFG_T                cmdTunerTestCfg;               // MXL_TUNER_TEST_CFG
#endif // _TUNER_TEST_API_ENABLED_
    MXL_TUNER_ENHANCED_CHAN_TUNE_CFG_T  cmdTunerEnhancedChanTuneCfg;   // MXL_TUNER_ENHANCED_CHAN_TUNE_CFG

    // Ctrl_Wrap_GetTunerStatus
    MXL_TUNER_LOCK_STATUS_T         cmdTunerLockStatusReq;      // MXL_TUNER_LOCK_STATUS_REQ
    MXL_TUNER_RX_PWR_T              cmdTunerRfRxPwrReq;         // MXL_TUNER_RF_RX_PWR_REQ
    MXL_TUNER_SETTINGS_T            cmdTunerCurrSettingReq;     // MXL_TUNER_CURR_SETTING_REQ
    MXL_GET_DSCAL_INFO_T            cmdTunerDscalInfoReq;       // MXL_TUNER_DSCAL_INFO_REQ
    MXL_TUNER_MONITOR_RX_PWR_REQ_T  cmdTunerMonitorRxPwrReq;    // MXL_TUNER_MONITOR_RX_PWR_REQ
  };
} MXL_COMMAND_T;
#endif // _LEGACY_API_INTERFACE_

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/
#ifndef __MXL_GUI__
#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigDevice(MXL_CMD_TYPE_E cmdType, void *paramPtr);
MXL_STATUS MxLWare251SF_API_GetDeviceStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr);
MXL_STATUS MxLWare251SF_API_ConfigDemod(MXL_CMD_TYPE_E cmdType, void *paramPtr);
MXL_STATUS MxLWare251SF_API_GetDemodStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr);
MXL_STATUS MxLWare251SF_API_ConfigTuner(MXL_CMD_TYPE_E cmdType, void *paramPtr);
MXL_STATUS MxLWare251SF_API_GetTunerStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr);
#else // _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigDevice(MXL_COMMAND_T *commandPtr);
MXL_STATUS MxLWare251SF_API_GetDeviceStatus(MXL_COMMAND_T *commandPtr);
MXL_STATUS MxLWare251SF_API_ConfigDemod(MXL_COMMAND_T *commandPtr);
MXL_STATUS MxLWare251SF_API_GetDemodStatus(MXL_COMMAND_T *commandPtr);
MXL_STATUS MxLWare251SF_API_ConfigTuner(MXL_COMMAND_T *commandPtr);
MXL_STATUS MxLWare251SF_API_GetTunerStatus(MXL_COMMAND_T *commandPtr);
#endif // _LEGACY_API_INTERFACE_
#endif // __MXL_GUI__

#endif /* __MXL251SF_PHY_CTRL_API_H__*/

