/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCtrlApi.c
 * 
 * AUTHOR             : Brenndon Lee
 *                      Dong Liu 
 *                      Sunghoon Park
 *                      Richard Liu
 *                      Jun Huang
 *					    Randhir Jha
 *
 * DATE CREATED       : 6/22/2009
 *                      08/26/2010
 *                      07/06/2010
 *                      12/21/2010
 *                      06/18/2011
 *                      03/18/2013
 *
 * DESCRIPTION        : This file contains MxL251SF driver APIs
 *                             
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

//#include <math.h>
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

#include "MxL251SF_PhyCtrlApi.h"
#include "MxL251SF_PhyCfg.h"

#include "MxL_Debug.h"
#include "MxL251SF_OEM_Drv.h"
#include "MxL251SF_PhyCal.h"

#ifdef _FAST_SCAN_TEST_ENABLED_
#include "MxL251SF_FastScanTest.c"
#endif //  _FAST_SCAN_TEST_ENABLED_

#ifdef _MXL251_FIXEDPOINT_
typedef struct
{
  UINT16 x2;
  SINT32 a;
  SINT32 b;
}MXL_SNR_RANGE_T;

static MXL_SNR_RANGE_T snrRangeQam64[] = {
  {8, -75257, 4633548},
  {19, -32451, 4272396},
  {42, -14646, 3926475},
  {90, -6824, 3594585},
  {191, -3219, 3268550},
  {404, -1523, 2943878},
  {854, -721, 2619375},
  {1803, -341, 2294854},
  {3804, -162, 1970594},
  {8024, -76, 1646463},
  {16925, -36, 1322355},
  {34243, -17, 1005132},  
  {0,0,0}
  };

static MXL_SNR_RANGE_T snrRangeQam16[] = {
  {8, -75257, 4612359},
  {19, -32451, 4251207},
  {42, -14646, 3905286},
  {90, -6824, 3573395},
  {191, -3219, 3247361},
  {404, -1523, 2922689},
  {854, -721, 2598186},
  {1803, -341, 2273666},
  {3804, -162, 1949404},
  {8024, -76, 1625274},
  {16925, -36, 1301166},
  {32612, -18, 992174},
  {0,0,0}
  };

static MXL_SNR_RANGE_T snrRangeQam256[] = {
  {8, -75257, 4638688},
  {19, -32451, 4277536},
  {42, -14646, 3931615},
  {90, -6824, 3599724},
  {191, -3219, 3273690},
  {404, -1523, 2949018},
  {854, -721, 2624516},
  {1803, -341, 2299994},
  {3804, -162, 1975733},
  {8024, -76, 1651603},
  {16925, -36, 1327495},
  {34651, -17, 1008299},
  {0,0,0}
  };

static MXL_SNR_RANGE_T snrRangeQam32[] = {
  {4, -150514, 4612359},
  {10, -60205, 4214419},
  {23, -26694, 3864607},
  {50, -12259, 3526387},
  {107, -5746, 3197869},
  {227, -2710, 2871717},
  {480, -1282, 2546940},
  {1014, -607, 2222508},
  {2140, -287, 1898166},
  {4515, -136, 1573980},
  {9524, -64, 1249834},
  {16306, -34, 961458},
  {0,0,0}
  };

static MXL_SNR_RANGE_T snrRangeQam128[] = {
  {4, -150515, 4623084},
  {10, -60205, 4225143},
  {23, -26694, 3875331},
  {50, -12259, 3537111},
  {107, -5746, 3208594},
  {227, -2710, 2882442},
  {480, -1282, 2557664},
  {1014, -607, 2233232},
  {2140, -287, 1908890},
  {4515, -136, 1584704},
  {9524, -64, 1260558},
  {16714, -33, 967789},
  {0,0,0},
  };

static MXL_SNR_RANGE_T snrRangeQpsk[] = {
  {14, -43004, 4624594},
  {31, -19704, 4288137},
  {67, -9169, 3956929},
  {143, -4304, 3628849},
  {303, -2031, 3302900},
  {641, -961, 2978047},
  {1354, -455, 2653349},
  {2857, -215, 2328987},
  {6027, -102, 2004838},
  {12713, -48, 1680714},
  {26814, -22, 1356603},
  {56554, -10, 1032505},
  {58703, -7, 842441},
  {0,0,0}
  };  

static UINT32 MxLWare251_ReqDemodSnrLinear(MXL_SNR_RANGE_T * snrArray, UINT16 rawValue);

#endif
/* MxLWare Driver version for MxL251SF */
const UINT8 MxLWare251SFVersion[] = {2, 1, 9, 5};

/* In addtion to DrvVersion, this candidate information is also internally used to
 * indicate if this drvier is verified by QA department. 
 * If this variable has 0, it's been verified
 */
const UINT8 MxLWare251SFCandidateVersion = 1;

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDeviceReset - MXL_DEV_DEVICE_RESET_CFG
--| 
--| AUTHOR        : Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 05/10/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Reset MxL251SF device
--|                 
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDeviceReset(PMXL_DEV_RESET_T devResetPtr)
{
  UINT8  status = MXL_TRUE;
  UINT16 SOC_MM;
  UINT8  j;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(devResetPtr->I2cSlaveAddr);
  
  //UINT8 readBuffer[4];
  
  MxL_DLL_DEBUG0("MXL_DEV_DEVICE_RESET_CFG -i2cAddr=0x%x\n", devResetPtr->I2cSlaveAddr);

  // Reset MxL251SF by toggling Reset pin
  MxL251_Ctrl_ResetMxL251SF(devResetPtr->I2cSlaveAddr);

  devContextPtr->ActiveIFMap = 0;
  devContextPtr->i2cSlaveAddr = devResetPtr->I2cSlaveAddr;

  /* Register this I2C address */
  MxL_DLL_DEBUG0("MXL_DEV_DEVICE_RESET_CFG - i2cAddr =0x%x is reset. \n", devContextPtr->i2cSlaveAddr);

	
	//status |= (UINT8)MxL251_Ctrl_ReadBlock(devContextPtr->i2cSlaveAddr, 0x0e, COMMAND_HEADER_LENGTH, readBuffer);

#if 1
  for( j=0; j< MAX_251SF_DEMODS; j++)
  {
    devContextPtr->AccStatCounter.AccCwCorrCount[j] = 0;
    devContextPtr->AccStatCounter.AccCwErrCount[j] = 0;
    devContextPtr->AccStatCounter.AccCwUnerrCount[j] = 0;
    devContextPtr->AccStatCounter.AccCwReceived[j] = 0;
    devContextPtr->AccStatCounter.AccCorrBits[j] = 0;
    devContextPtr->AccStatCounter.AccErrMpeg[j] = 0;
    devContextPtr->AccStatCounter.AccReceivedMpeg[j] = 0;
  }

  status |= MxL251_Ctrl_ReadRegister(devResetPtr->I2cSlaveAddr, ANA_DIG_SOC_ID_REG, &(devContextPtr->AsicId));

#ifdef _SOC_ID_DEBUG_ENABLED_
  status |= MxL251_Ctrl_ReadRegister(devResetPtr->I2cSlaveAddr, ECO_4_SOC_ID_REG, &(devContextPtr->ChipId));
  if (0 == devContextPtr->ChipId)
#endif // _SOC_ID_DEBUG_ENABLED_
  {
    // Make sure ChipId is obtained before MxL251_PwrCoefInit()
    status |= MxL251_Ctrl_ReadRegister(devResetPtr->I2cSlaveAddr, ANA_DIG_SOC_MM_REG, &SOC_MM);
    devContextPtr->ChipId = devContextPtr->AsicId*256 + SOC_MM;

    if (0 == devContextPtr->ChipId)
    {
      // FPGA
      UINT16 linkRtlVersion;
      status |= MxL251_Ctrl_ReadRegister(devResetPtr->I2cSlaveAddr, LINK_RTL_VERSION_REG, &linkRtlVersion);
      devContextPtr->ChipId = (linkRtlVersion >= 0x2000)?ES2_MM0_VERSION:ES1_MM0_VERSION;
      MxL_DLL_DEBUG0("%s FPGA detected, linkRtlVersion=0x%04x\n", __FUNCTION__, linkRtlVersion);
    }
  }
  MxL_DLL_DEBUG0("%s ChipId=0x%04x AsicId=0x%04x\n", __FUNCTION__, devContextPtr->ChipId, devContextPtr->AsicId);

  // For ES1: MxL251_Device.vcoThresholdInMHz is used by backdoor mode only
  // For ES2: MxL251_Device.vcoThresholdInMHz will be updated by MxL251_Ctrl_SetVcoThreshold
  devContextPtr->vcoThresholdInMHz = IS_ES2_OR_NEWER(devContextPtr)?3600:3500;

  devContextPtr->DAGCBottomSetPt = 10*16;
  devContextPtr->Tuners[0].Demod.LockRangeInHz = 100000;
  devContextPtr->Tuners[1].Demod.LockRangeInHz = 100000;

  // Initialize Power coefficients
  MxL251_PwrCoefInit(devContextPtr);

  // Initialize Power Calibration
  MxL251_PwrCalInit();
#endif

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDevXtalSettings - MXL_DEV_XTAL_SETTINGS_CFG
--| 
--| AUTHOR        : Brenndon Lee, Dong Liu
--|
--| DATE CREATED  : 7/19/2010 
--|
--| DESCRIPTION   : This function configures XTAL frequency, Clok-out settings, and
--|                 Loop through control for MxL251SF.
--|                 
--|                 Narrow-band channel tune and Symbol rate config will need the exact
--|                 the xtal frequency.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDevXtalSettings(PMXL_XTAL_CFG_T xtalSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 refSxIntMod[4] = {144, 96, 92, 85};
  UINT16 rcTuneResult = 0;
  UINT16 capValue;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(xtalSetPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEV_XTAL_SETTINGS_CFG - i2cAddr=0x%x, XtalFreq=%d, XtalCap=%d, XtalClkSharing=%d, LoopThrough=%d, SplitterEnable=%d\n",
                                              xtalSetPtr->I2cSlaveAddr,
                                              xtalSetPtr->DigXtalFreq,
                                              xtalSetPtr->XtalCap,
                                              xtalSetPtr->XtalClkSharing,
                                              xtalSetPtr->LoopThruEnable,
                                              xtalSetPtr->SplitterEnable);

  // This will be used in NB Chan Tune and Symbol Rate config
  // Before FW is downloaded, Xtal Frequency has to be configued by MxLWare. 
  // PLL out clock freq will vary with Xtal Freq
  // Xtal Freq      PLL Out Freq
  //  16/24MHz  ->     256MHz
  //  25MHz     ->     255.555MHz
  //  27MHz     ->     255MHz
  devContextPtr->XtalFreq = xtalSetPtr->DigXtalFreq;

  switch (xtalSetPtr->DigXtalFreq)
  {
    case XTAL_16MHz:
    case XTAL_24MHz:
#ifdef _MXL251_FIXEDPOINT_
      devContextPtr->RefPllFreqInMHz = 0x40001;
#else
      devContextPtr->RefPllFreqInMHz = 256.0;
#endif
      devContextPtr->RefVCOFreqInMHz = 2304;
	  break;

    case XTAL_25MHz:
#ifdef _MXL251_FIXEDPOINT_ 
      devContextPtr->RefPllFreqInMHz = 0x3fe3e; 
#else
	  devContextPtr->RefPllFreqInMHz = (REAL32)255.56;
#endif
	  devContextPtr->RefVCOFreqInMHz = 2300;
      break;

    case XTAL_27MHz:
#ifdef _MXL251_FIXEDPOINT_
      devContextPtr->RefPllFreqInMHz = 0x3fe3e;
#else
	  devContextPtr->RefPllFreqInMHz = 255.0;
#endif
      devContextPtr->RefVCOFreqInMHz = 2295;
      break;
  }

  // Configure XTAL 
  MxL_DLL_DEBUG0("MXL_XTAL_CFG xtal_cap = %d \n", xtalSetPtr->XtalCap);

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_xtal_26mhz", (REAL64) ((xtalSetPtr->DigXtalFreq)>0), (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_26MHZ_REG, DIG_ANA_XTAL_26MHZ_MASK, (xtalSetPtr->DigXtalFreq)<<DIG_ANA_XTAL_26MHZ_SHIFT_BITS);

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_xtal_cap", (REAL64) (xtalSetPtr->XtalCap), (MXL_BOOL) 0);
  capValue = xtalSetPtr->XtalCap;

  if (xtalSetPtr->XtalClkSharing == XTAL_CLK_SHARING_SLAVE)
  {
    // Force capValue to 0 for slave mode
    capValue = 0;
  }

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // Ticket #273: update xtal load cap mapping
    // max=41pF
    if (capValue == 0)
    {
      // stays at 0
      // capValue = 0;
    }
    else if (capValue >= 10)
    {
      capValue -= 9;
    }
    else
    {
      MxL_DLL_ERROR0("%s - incorrect cap value is specified (%d)\n", __FUNCTION__, capValue);
      return MXL_FALSE;
    }
    // At this point max(capValue) = 31
    // dig_ana_xtal_spare: <3>force done<2>reduce buf size<1>MSB of CAP val<0>MSB of ext bias
    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr, 
        DIG_ANA_XTAL_CAP_REG, 
        DIG_ANA_XTAL_CAP_MASK, 
        (capValue&0x000F)<<DIG_ANA_XTAL_CAP_SHIFT_BITS);

    // dig_ana_xtal_spare = 12 + (msb<<1); 
    status |= MxL251_Ctrl_WriteRegisterMask( xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_SPARE_REG, DIG_ANA_XTAL_SPARE_MASK, // (12<< DIG_ANA_XTAL_SPARE_SHIFT_BITS));
        ((12 + ((capValue & 0x10)?2:0)) << DIG_ANA_XTAL_SPARE_SHIFT_BITS));
  }
  else
  {
    status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_CAP_REG, DIG_ANA_XTAL_CAP_MASK, capValue<<DIG_ANA_XTAL_CAP_SHIFT_BITS);
    // dig_ana_xtal_spare = 12; 
    status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_SPARE_REG, DIG_ANA_XTAL_SPARE_MASK, (12 << DIG_ANA_XTAL_SPARE_SHIFT_BITS));

  }
   
  // dig_ana_xtal_cal_rstb = 0; 
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_CAL_RSTB_REG, DIG_ANA_XTAL_CAL_RSTB_MASK, (0<< DIG_ANA_XTAL_CAL_RSTB_SHIFT_BITS));
   
  if (xtalSetPtr->XtalClkSharing == XTAL_CLK_SHARING_SLAVE)
  {
    // dig_ana_xtal_th<1:0>=3
    MxL251_Ctrl_WriteRegisterField(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_TH, 3);
    // dig_ana_xtal_cal_rstb = 0;
    status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_CAL_RSTB_REG, DIG_ANA_XTAL_CAL_RSTB_MASK, (0<< DIG_ANA_XTAL_CAL_RSTB_SHIFT_BITS));
  }

  // dig_ana_xtal_cal_rstb = 1;
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_XTAL_CAL_RSTB_REG, DIG_ANA_XTAL_CAL_RSTB_MASK, (1<< DIG_ANA_XTAL_CAL_RSTB_SHIFT_BITS));

  //dig_ana_misc_spare      66
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_MISC_SPARE_REG, DIG_ANA_MISC_SPARE_MASK, (0x42<<DIG_ANA_MISC_SPARE_SHIFT_BITS));

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // poll ana_dig_refsx_sethi_rb<13> (for DNX 1.5-V regulator output ready)

    // To assure supply is ready
    if (0 == MxL251_Ctrl_SpinOnRegField(
          xtalSetPtr->I2cSlaveAddr, 
          ANA_DIG_REFSX_SETHI_RB_REG, 
          ANA_DIG_REFSX_SETHI_RB_MASK,
          0,
          SPIN_UNTIL_NEQ, 
          200000/*200 ms*/))
    {
      MxL_DLL_ERROR0("%s - ANA_DIG_REFSX_SETHI_RB_REG timeout\n", __FUNCTION__);
      // Ignore the error
      // status |= MXL_FALSE;
      // return MXL_FALSE;
    }

    MxL251_Ctrl_WriteRegisterField(xtalSetPtr->I2cSlaveAddr, DIG_ANA_LT_GAIN,   3);
    MxL251_Ctrl_WriteRegisterField(xtalSetPtr->I2cSlaveAddr, DIG_ANA_SPLT_GAIN, 3);

    // For each of the following
    // (Strobe LNA/LT/SPLT/RFRSSI defaults)

    /** Rising edges */
    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr, 
        DIG_ANA_DNX0_LNA_SPARE_REG, 
        DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/, 
        DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr, 
        DIG_ANA_DNX1_LNA_SPARE_REG, 
        DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/, 
        DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_LT_SPARE_REG,
        DIG_ANA_LT_SPARE_STROBE_MASK/*2*/,
        DIG_ANA_LT_SPARE_STROBE_MASK/*2*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_SPLT_SPARE_REG,
        DIG_ANA_SPLT_SPARE_STROBE_MASK /*1<<11*/,
        DIG_ANA_SPLT_SPARE_STROBE_MASK/*1<<11*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_DNX0_SPARE_REG,
        DIG_ANA_DNX0_SPARE_RFRSSI_STROBE_MASK/*1<<7*/,
        DIG_ANA_DNX0_SPARE_RFRSSI_STROBE_MASK/*1<<7*/);


    /** Falling edges */
    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr, 
        DIG_ANA_DNX0_LNA_SPARE_REG, 
        DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/, 
        0/*bit9*/);
    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr, 
        DIG_ANA_DNX1_LNA_SPARE_REG, 
        DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/, 
        0/*bit9*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_LT_SPARE_REG,
        DIG_ANA_LT_SPARE_STROBE_MASK/*2*/,
        0/*2*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_SPLT_SPARE_REG,
        DIG_ANA_SPLT_SPARE_STROBE_MASK /*1<<11*/,
        0/*1<<11*/);

    status |= MxL251_Ctrl_WriteRegisterMask(
        xtalSetPtr->I2cSlaveAddr,
        DIG_ANA_DNX0_SPARE_REG,
        DIG_ANA_DNX0_SPARE_RFRSSI_STROBE_MASK/*1<<7*/,
        0/*1<<7*/);
  }

  // Configure RefSX
  MxL_DLL_DEBUG0("MXL_REFPLL_CFG int = %d \n",(refSxIntMod[xtalSetPtr->DigXtalFreq]));

  //dig_ana_refsx_amp_regdig      3 
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_AMP_REGDIG_REG, DIG_ANA_REFSX_AMP_REGDIG_MASK, (3<<DIG_ANA_REFSX_AMP_REGDIG_SHIFT_BITS));

  //dig_ana_refsx_spare     0
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_SPARE_REG, DIG_ANA_REFSX_SPARE_MASK, (0<<DIG_ANA_REFSX_SPARE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_refsx_dsm_intmod", (REAL64) (refSxIntMod[xtalSetPtr->DigXtalFreq]), (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_DSM_INTMOD_REG, DIG_ANA_REFSX_DSM_INTMOD_MASK, (refSxIntMod[xtalSetPtr->DigXtalFreq])<<DIG_ANA_REFSX_DSM_INTMOD_SHIFT_BITS);

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_refsx_dsm_fracmod", (REAL64) 0, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_DSM_FRACMOD_REG, 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_DSM_FRACMOD_REG-4, 0x01FF, 0);

  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_TUNE_REG, DIG_ANA_REFSX_TUNE_MASK, (0<<DIG_ANA_REFSX_TUNE_SHIFT_BITS));
  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_refsx_ena", (REAL64) 1, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_ENA_REG, DIG_ANA_REFSX_ENA_MASK, (1<<DIG_ANA_REFSX_ENA_SHIFT_BIT));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_refsx_tune", (REAL64) 1, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_REFSX_TUNE_REG, DIG_ANA_REFSX_TUNE_MASK, (1<<DIG_ANA_REFSX_TUNE_SHIFT_BITS));

  // In FPGA, skip this
  if (IS_ASIC_TARGET(devContextPtr))
  {
    if (0 == MxL251_Ctrl_SpinOnRegField(xtalSetPtr->I2cSlaveAddr, 
                                        ANA_REFSX_TUNE_DONE_REG, 
                                        ANA_REFSX_TUNE_DONE_MASK, 
                                        0, 
                                        SPIN_UNTIL_NEQ,
                                        500000))
    {
      MxL_DLL_ERROR0("ANA_REFSX_TUNE_DONE timeout");
      // return MXL_FALSE;
    }
  }
  
  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "amba_clk_ctrl", (REAL64) 5, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, AMBA_CLK_CTRL_REG, AMBA_CLK_CTRL_MASK, (5<<AMBA_CLK_CTRL_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "amba_clk_src", (REAL64) 0, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, AMBA_CLK_SRC_REG, AMBA_CLK_SRC_MASK, (0<<AMBA_CLK_SRC_SHIFT_BITS));
  
  MxL_DLL_DEBUG0("%s MxL251_Ctrl_ConfigTunerOverwriteDefault starting.\n", __FUNCTION__);

  // Initialize Tuner
  MxL251_Ctrl_ConfigTunerOverwriteDefault(xtalSetPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("%s MxL251_Ctrl_ConfigTunerOverwriteDefault is done.\n", __FUNCTION__);

  // Start RF RSSI CAL
  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_rfrssi_cal_ena", (REAL64) 1, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_RFRSSI_CAL_ENA_REG, DIG_ANA_RFRSSI_CAL_ENA_MASK, (1<<DIG_ANA_RFRSSI_CAL_ENA_SHIFT_BITS));
 
  
  MxL251_Ctrl_DelayUsec(80); // 80us delay
  // RF RFSSI DFE reg config
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_RFRSSI_EN_REG, DFE_RFRSSI_EN_MASK, 0x0020);

 // NOTE: Need 1.5 ms between rssi cal ena start and stop - how to do this?
  MxL251_Ctrl_DelayUsec(2000); // 2ms delay

  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_RFRSSI_CAL_REG, DFE_RFRSSI_CAL_MASK,  (1<<DFE_RFRSSI_CAL_SHIFT_BITS));

  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_RFRSSI_CAL_REG, DFE_RFRSSI_CAL_MASK,  (0<<DFE_RFRSSI_CAL_SHIFT_BITS));
   

  MxL_DLL_DEBUG0("%s RFRSSI cal is done.\n", __FUNCTION__);
  // Stop RFRSSI Cal
  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_rfrssi_cal_ena", (REAL64) 0, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_RFRSSI_CAL_ENA_REG, DIG_ANA_RFRSSI_CAL_ENA_MASK,  (0<<DIG_ANA_RFRSSI_CAL_ENA_SHIFT_BITS));

// Start Temp Sens CAL
   
  // TSENS DFE reg config
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_TSENS_EN_REG, DFE_TSENS_EN_MASK, 0x2000);

//  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_TSENS_CAL_REG, DFE_TSENS_CAL_MASK,  (1<<DFE_TSENS_CAL_SHIFT_BITS));
//  
//  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DFE_TSENS_CAL_REG, DFE_TSENS_CAL_MASK,  (0<<DFE_TSENS_CAL_SHIFT_BITS));

  // NOTE: Need 1.5 ms between rf rssi cal ena start and stop - how to do this?
  //MxL251_Ctrl_DelayUsec(2000); // 2ms delay

  // Configure RCTune
  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_rctune_ena", (REAL64) 1, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_RCTUNE_ENA_REG, DIG_ANA_RCTUNE_ENA_MASK, (1<<DIG_ANA_RCTUNE_ENA_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_rctune_ena", (REAL64) 0, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_RCTUNE_ENA_REG, DIG_ANA_RCTUNE_ENA_MASK, (0<<DIG_ANA_RCTUNE_ENA_SHIFT_BITS));

  //status |= Ctrl_GetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "ana_dig_rctune", &rcTuneResult);
  status |= MxL251_Ctrl_ReadRegisterMask(xtalSetPtr->I2cSlaveAddr, ANA_DIG_RCTUNE_REG, ANA_DIG_RCTUNE_MASK, &rcTuneResult);
  rcTuneResult >>= ANA_DIG_RCTUNE_SHIFT_BITS;

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_abb0_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_ABB0_RCTUNE_REG, DIG_ANA_ABB0_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_ABB0_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_abb1_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_ABB1_RCTUNE_REG, DIG_ANA_ABB1_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_ABB1_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_adc0_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr,DIG_ANA_ADC0_RCTUNE_REG, DIG_ANA_ADC0_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_ADC0_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_adc1_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_ADC1_RCTUNE_REG, DIG_ANA_ADC1_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_ADC1_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_dnx0_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_DNX0_RCTUNE_REG, DIG_ANA_DNX0_RCTUNE_MASK,  (rcTuneResult<<DIG_ANA_DNX0_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_dnx1_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_DNX1_RCTUNE_REG, DIG_ANA_DNX1_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_DNX1_RCTUNE_SHIFT_BITS));

  //status |= Ctrl_SetRegFieldControl(xtalSetPtr->I2cSlaveAddr, "dig_ana_if_rctune", rcTuneResult, (MXL_BOOL) 0);
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_IF_RCTUNE_REG, DIG_ANA_IF_RCTUNE_MASK, (rcTuneResult<<DIG_ANA_IF_RCTUNE_SHIFT_BITS));

  MxL_DLL_DEBUG0("%s RC tune is done.\n", __FUNCTION__);

  /* configure SplitterEnable */
  rcTuneResult = xtalSetPtr->SplitterEnable ? 1 : 0;
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_SPLT_ENA_REG, DIG_ANA_SPLT_ENA_MASK, (rcTuneResult<<DIG_ANA_SPLT_ENA_SHIFT_BITS));

  /* loop through  */
  rcTuneResult = xtalSetPtr->LoopThruEnable ? 1: 0;
  status |= MxL251_Ctrl_WriteRegisterMask(xtalSetPtr->I2cSlaveAddr, DIG_ANA_LT_ENA_REG, DIG_ANA_LT_ENA_MASK, (rcTuneResult<<DIG_ANA_LT_ENA_SHIFT_BITS));

#ifdef _ENABLE_UART_DEBUG_
  MxL251_Ctrl_EnableUart(xtalSetPtr->I2cSlaveAddr);
#endif // _ENABLE_UART_DEBUG_

  /* CLKOUT enable */
  status |= MxL251_Ctrl_WriteRegisterMask(
      xtalSetPtr->I2cSlaveAddr, 
      DIG_ANA_CLKOUT_ENA_REG, 
      DIG_ANA_CLKOUT_ENA_MASK, 
      (xtalSetPtr->XtalClkSharing == XTAL_CLK_SHARING_MASTER)?DIG_ANA_CLKOUT_ENA_MASK:0
      );

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDevPSM - MXL_DEV_PSM_CFG
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 01/05/2011 
--|
--| DESCRIPTION   : This function performs Power Save Mode configuration
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDevPSM(PMXL_DEV_PSM_INFO_T psmCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 flag;

  MxL_DLL_DEBUG0("MXL_DEV_PSM_CFG - i2cAddr=0x%x, LoopThrough=%d, SplitterEnable=%d\n",
                        psmCfgPtr->I2cSlaveAddr, psmCfgPtr->LoopThruEnable, psmCfgPtr->SplitterEnable);

  /* configure SplitterEnable */
  flag = psmCfgPtr->SplitterEnable ? 1 : 0;
  status |= MxL251_Ctrl_WriteRegisterMask(psmCfgPtr->I2cSlaveAddr, DIG_ANA_SPLT_ENA_REG, DIG_ANA_SPLT_ENA_MASK, (flag<<DIG_ANA_SPLT_ENA_SHIFT_BITS));

  /* loop through  */
  flag = psmCfgPtr->LoopThruEnable ? 1: 0;
  status |= MxL251_Ctrl_WriteRegisterMask(psmCfgPtr->I2cSlaveAddr, DIG_ANA_LT_ENA_REG, DIG_ANA_LT_ENA_MASK, (flag<<DIG_ANA_LT_ENA_SHIFT_BITS));

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigFwDownload - MXL_DEV_FIRMWARE_DOWNLOAD_CFG
--| 
--| AUTHOR        : Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 05/06/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Download MxL251SF firmware a.k.a DOCSIS FW in MBIN format into 
--|                 MxL251SF device via I2C interface. 
--|                 After power-on, this should be done first before using any other 
--|                 APIs defined here.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigFwDownload(PMXL_FW_INFO_T fwInfoPtr)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(fwInfoPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEV_FIRMWARE_DOWNLOAD_CFG - i2cAddr=0x%x Firmware size: %u BufPtr=0x%x\n", fwInfoPtr->I2cSlaveAddr, fwInfoPtr->MbinBufferSize, (UINT32)fwInfoPtr->MbinBufferPtr);

  if (MXL_TRUE != MxL251_Ctrl_DownloadFirmwareInMbin(fwInfoPtr->I2cSlaveAddr, (MBIN_FILE_T*)(fwInfoPtr->MbinBufferPtr), MXL_ENABLE))
  {
    return MXL_FALSE;
  }

  devContextPtr->FirmwareStatus = FIRMWARE_STATUS_LOADED;
  // MxL251_Ctrl_EnableUart(fwInfoPtr->I2cSlaveAddr);

  // TODO: ignore all errors from NVRAM
  MxL251_PwrLoadCoef(devContextPtr, 0/*BufPtr*/, 0 /*BufLen*/);

#ifdef _DYNAMIC_VCO_THRESHOLD_ENABLED_
  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    MxL251_Ctrl_SetVcoThreshold(fwInfoPtr->I2cSlaveAddr);
  }
#endif // _DYNAMIC_VCO_THRESHOLD_ENABLED_

#ifdef _BOOT_SCAN_ENABLED_
  MxL251_Ctrl_BootScan(fwInfoPtr->I2cSlaveAddr, TUNER0, WB_16_MHz);
#endif // _BOOT_SCAN_ENABLED_
 
  // Turn off both tuners
  MxL251_Ctrl_TunerStandby(fwInfoPtr->I2cSlaveAddr);

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDeviceVersionInfo - MXL_DEV_VERSION_INFO_REQ
--| 
--| AUTHOR        : Brenndon Lee
--|                 Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 6/19/2009
--|                 07/19/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns MxL251SF hardware version information and 
--|                 software module version informaton. 
--|                 Hardware version information include chip Id and chip version.
--|                 Software module version information include MxLWare, firmware 
--|                 and boot loader version information
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_GetDeviceVersionInfo(PMXL_DEV_VERSION_INFO_T devInfoPtr)
{
  FW_RESPONSE_T getDevVerRsp;
  UINT16 readBack;
  UINT8 k;
  MXL_STATUS status;
  UINT32 fwVer;
  UINT8  fwRcVer = 0;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(devInfoPtr->I2cSlaveAddr);;
  
  devContextPtr->FirmwareStatus = FIRMWARE_STATUS_UNKNOWN;

  // Read VERSION_REG register to get Chip ID and version information 
  // Fixed: FIXME Set correct address of Version Reg for ES1
  status = MxL251_Ctrl_ReadRegister(devInfoPtr->I2cSlaveAddr, ANA_DIG_SOC_ID_REG, &readBack);
  if (status == MXL_TRUE) // Read operation success 
  {
    devInfoPtr->DevId = (UINT8)(readBack);
  }
  status = MxL251_Ctrl_ReadRegister(devInfoPtr->I2cSlaveAddr, ANA_DIG_SOC_MM_REG, &readBack);
  if (status == MXL_TRUE) // Read operation success 
  {
    devInfoPtr->DevVer = (UINT8)(readBack);
  }

  MxL_DLL_DEBUG0("MXL_DEV_VERSION_INFO_REQ - \n");
  MxL_DLL_DEBUG0("i2cAddr=0x%x,Device Id = 0x%d, Device Version = 0x%x\n", devInfoPtr->I2cSlaveAddr, devInfoPtr->DevId, devInfoPtr->DevVer);    

  // Get MxLWare version information
  for (k = 0; k < MXL_VERSION_SIZE; k++)
    devInfoPtr->MxLWareVer[k] = MxLWare251SFVersion[k];

  devInfoPtr->MxLWareRCVer  = MxLWare251SFCandidateVersion;

  MxL_DLL_DEBUG0("MxLWare version: 0x%x.0x%x.0x%x.0x%x-RC%d\n", 
                 devInfoPtr->MxLWareVer[0],
                 devInfoPtr->MxLWareVer[1], 
                 devInfoPtr->MxLWareVer[2],
                 devInfoPtr->MxLWareVer[3],
                 devInfoPtr->MxLWareRCVer);

  // Get firmware and bootloader version information 
  status = MxL251_Ctrl_GetDeviceResp(devInfoPtr->I2cSlaveAddr, HOST_CMD_DEV_VERSION_INFO_REQ, &getDevVerRsp);
  
  if ((getDevVerRsp.errorCode == RESPONSE_ID_SUCCESS) && (status == MXL_TRUE)  
      && (getDevVerRsp.payloadLen == MXL_VERSION_SIZE*2))
  {
    MxL_DLL_DEBUG0("Received FW version info from Firmware successfully\n");
  
    for (k = 0; k < MXL_VERSION_SIZE; k++) // Response Data[0:3] : Firmware version     
      devInfoPtr->FirmwareVer[k] = getDevVerRsp.data[k];  
  
    for (k = 0; k < MXL_VERSION_SIZE; k++) // Response Data[4:7] : Boot loader version     
      devInfoPtr->BootLoaderVer[k] = getDevVerRsp.data[k + MXL_VERSION_SIZE];  
  
    if (MXL_TRUE != MxL251_Ctrl_ReadRegister(devInfoPtr->I2cSlaveAddr, 
                                             MAILBOX_REG_FIRMWARE_RC_VER, &readBack))
    {
      readBack = 0xFF;
    }

    fwRcVer = (UINT8)readBack;

    devInfoPtr->FirmwareRCVer = fwRcVer;

    MxL_DLL_DEBUG0("FW version : %u.%u.%u.%u-RC%u\n", devInfoPtr->FirmwareVer[0], 
                                                      devInfoPtr->FirmwareVer[1], 
                                                      devInfoPtr->FirmwareVer[2],
                                                      devInfoPtr->FirmwareVer[3],
                                                      fwRcVer);
  }
  else
  {
    // Check sum is wrong
    // Firmware is not loaded.
    // When firmware is not loaded, I2C protocol is carried out by bootloader
    for (k = 0; k < MXL_VERSION_SIZE; k++) // Response Data[0:3] : Firmware version     
      devInfoPtr->FirmwareVer[k] = 0;  
  
    for (k = 0; k < MXL_VERSION_SIZE; k++) // Response Data[4:7] : Boot loader version     
      devInfoPtr->BootLoaderVer[k] = 0;  
  
    // MxL_DLL_ERROR0("Check sum is wrong");
  }
  
  MxL_DLL_DEBUG0("BootLoader version: 0x%x.0x%x.0x%x.0x%x\n",
                  devInfoPtr->BootLoaderVer[0], devInfoPtr->BootLoaderVer[1],
                  devInfoPtr->BootLoaderVer[2], devInfoPtr->BootLoaderVer[3]);
  
  fwVer = (((UINT32)(devInfoPtr->FirmwareVer[0])) << 0)
          + (((UINT32)(devInfoPtr->FirmwareVer[1])) << 8)
          + (((UINT32)(devInfoPtr->FirmwareVer[2])) << 16)
          + (((UINT32)(devInfoPtr->FirmwareVer[3])) << 24);
  
  devContextPtr->FirmwareStatus = fwVer?FIRMWARE_STATUS_LOADED:FIRMWARE_STATUS_BOOTLOADER;  
  devContextPtr->FirmwareVersion = (UINT64)fwVer*256 + (UINT64)fwRcVer;
  
  MxL_DLL_DEBUG0("Firmware status=%d\r\n", devContextPtr->FirmwareStatus);
  
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDevicePSMInfo - MXL_DEV_PSM_REQ
--| 
--| AUTHOR        : Jun Huang
--|                 Richard Liu
--|
--| DATE CREATED  : 01/05/2011 
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns Power Save Mode configuration
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDevicePSMInfo(PMXL_DEV_PSM_INFO_T psmCfgPtr)
{
  UINT8  status = MXL_TRUE;
  UINT16 regData;

  /* Get SplitterEnable */
  status |= MxL251_Ctrl_ReadRegisterMask(psmCfgPtr->I2cSlaveAddr, DIG_ANA_SPLT_ENA_REG, DIG_ANA_SPLT_ENA_MASK, &regData);
  psmCfgPtr->SplitterEnable = regData?MXL_ENABLE:MXL_DISABLE;

  /* Get loop through configuration */
  status |= MxL251_Ctrl_ReadRegisterMask(psmCfgPtr->I2cSlaveAddr, DIG_ANA_LT_ENA_REG, DIG_ANA_LT_ENA_MASK, &regData);
  psmCfgPtr->LoopThruEnable = regData?MXL_ENABLE:MXL_DISABLE;

  MxL_DLL_DEBUG0("MXL_DEV_PSM_REQ - i2cAddr=0x%x, LoopThrough=%d, SplitterEnable=%d\n",
                  psmCfgPtr->I2cSlaveAddr, psmCfgPtr->LoopThruEnable, psmCfgPtr->SplitterEnable);

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDevicePowerModeInfo - MXL_DEV_POWER_MODE_REQ
--| 
--| AUTHOR        : SidS 
--|
--| DATE CREATED  : 06/16/2011 
--|
--| DESCRIPTION   : This function returns Power Mode information 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDevicePowerModeInfo(PMXL_PWR_MODE_CFG_T paramPtr)
{
  UINT8  status = MXL_TRUE;

  UINT16 regData;
  UINT16 tunerEna0;
  UINT16 tunerEna1;

  /* Sleep or not - cpu clock src*/
  status |= MxL251_Ctrl_ReadRegisterMask(paramPtr->I2cSlaveAddr, AMBA_CLK_SRC_REG, AMBA_CLK_SRC_MASK, &regData);
  if (AMBA_CLK_SRC_MASK == regData)
  { 
    /* Sleep */
    paramPtr->PowerMode = (MXL_PWR_MODE_E)POWER_MODE_SLEEP;
  }
  else
  {
    /* Standby or normal - tuner_en */
    status |= MxL251_WaitForHostCommandToComplete(paramPtr->I2cSlaveAddr);
    status |= MxL251_Ctrl_ReadRegisterMask(paramPtr->I2cSlaveAddr, DIG_ANA_TUNER0_ENA_REG, DIG_ANA_TUNER0_ENA_MASK, &tunerEna0);
    status |= MxL251_Ctrl_ReadRegisterMask(paramPtr->I2cSlaveAddr, DIG_ANA_TUNER1_ENA_REG, DIG_ANA_TUNER1_ENA_MASK, &tunerEna1);
    if (tunerEna0 == 0 && tunerEna1 == 0)
    {
      /* Standby */
      paramPtr->PowerMode = (MXL_PWR_MODE_E)POWER_MODE_STANDBY;
    }
    else
    { 
      /* Normal - not checking for Nb/Demod/Upx/Mpeg-out */
      paramPtr->PowerMode = (MXL_PWR_MODE_E)POWER_MODE_NORMAL;
    }
  }
  MxL_DLL_DEBUG0("MXL_DEV_POWER_MODE_REQ- i2cAddr=0x%x, PowerMode=%d\n", paramPtr->I2cSlaveAddr, paramPtr->PowerMode);

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDevPowerSavingMode - MXL_DEV_POWER_MODE_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 6/19/2009
--|                 2/14/2009
--|                 7/19/2010   
--|
--| DESCRIPTION   : This function configures Standby mode and Sleep mode to
--|                 control power consumption.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDevPowerMode(PMXL_PWR_MODE_CFG_T pwrModePtr)
{
  UINT8 status = MXL_TRUE;
  MXL_PWR_MODE_CFG_T currentPwrModeReq;
  UINT8 i2cAddr = pwrModePtr->I2cSlaveAddr;

  MxL_DLL_DEBUG0("MXL_DEV_POWER_MODE_CFG - i2cAddr=0x%x, powerMode=%d\n", pwrModePtr->I2cSlaveAddr, pwrModePtr->PowerMode);

  /* Get current power state */
  currentPwrModeReq.I2cSlaveAddr = i2cAddr;
  status |= MxL251_GetDevicePowerModeInfo((PMXL_PWR_MODE_CFG_T)&currentPwrModeReq);

  switch (pwrModePtr->PowerMode)
  {
    case POWER_MODE_SLEEP:
      switch (currentPwrModeReq.PowerMode)
      {
        case POWER_MODE_SLEEP:
          MxL_DLL_PRINT0("Device is already in SLEEP mode\n");
          break;

        case POWER_MODE_NORMAL:
          status |= MxL251_Ctrl_DeviceStandby(i2cAddr);
          // let it fall through: do not put break
          // break;

        case POWER_MODE_STANDBY:
          /* Switch processor clock to Xtal */
          /* Turn-off Ref Pll */
          status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, AMBA_CLK_SRC_REG, AMBA_CLK_SRC_MASK, (1<<AMBA_CLK_SRC_SHIFT_BITS));
          status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_REFSX_ENA_REG, DIG_ANA_REFSX_ENA_MASK, (0<<DIG_ANA_REFSX_ENA_SHIFT_BIT));
          break;

        default:
          MxL_DLL_ERROR0("Invalid current PowerMode mode (%d)\n", currentPwrModeReq.PowerMode);
          status = MXL_FALSE;
          break;
      }
      break;

    case POWER_MODE_STANDBY:

      switch (currentPwrModeReq.PowerMode)
      {
        case POWER_MODE_SLEEP:
          MxL_DLL_ERROR0("Use MXL_DEV_XTAL_SETTINGS_CFG to enter STANDBY mode\n");
          status = MXL_FALSE;
          break;

        case POWER_MODE_NORMAL:
          status |= MxL251_Ctrl_DeviceStandby(i2cAddr);
          break;

        case POWER_MODE_STANDBY:
          MxL_DLL_PRINT0("Device is already in STANDBY mode\n");
          break;

        default:
          MxL_DLL_ERROR0("Invalid current PowerMode mode (%d)\n", currentPwrModeReq.PowerMode);
          status = MXL_FALSE;
          break;
      }
      break;

    case POWER_MODE_NORMAL:
      status = MXL_FALSE;
      MxL_DLL_ERROR0("Use any WB tune API enter NORMAL mode\n");
      break;

    default:
      status = MXL_FALSE;
      MxL_DLL_ERROR0("Invalid power mode %d\n", pwrModePtr->PowerMode);
      break;
  }

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDevOverwriteDefault - MXL_DEV_OVERWRITE_DEFAULT_CFG
--| 
--| AUTHOR        : Sunghoon Park, Brenndon Lee, Dong Liu, Richard Liu
--|
--| DATE CREATED  : 08/27/2009, 6/1/2010, 07/19/2010, 12/21/2010
--|
--| DESCRIPTION   : Configure MxL251SF default settings
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDevOverwriteDefault(PMXL_OVERWRITE_DEFAULT_CFG_T overwritePtr)
{
  UINT16 control;
  UINT8 status;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(overwritePtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEV_OVERWRITE_DEFAULT_CFG - i2cAddr=0x%x,DemodId = %d\n", overwritePtr->I2cSlaveAddr, overwritePtr->DemodId);

  status = (UINT8)MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr, DFE_RESET_REG, 0xFF01);

  // repeat
  status |= MxL251_Ctrl_ConfigDemodClockEnable(overwritePtr->I2cSlaveAddr, overwritePtr->DemodId, MXL_ENABLE);  

  switch (overwritePtr->DemodId)
  {
    case DEMOD0: 

      // Set reset register  
      status |= MxL251_Ctrl_ReadRegister(overwritePtr->I2cSlaveAddr, DEMOD1_RESET_REG, &control);

      control &= ~DMD1_RESET_MASK; // Clear out reset bit
      status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr, DEMOD1_RESET_REG, control);
      break;

    case DEMOD1: 
      
      // Set reset register  
      status |= MxL251_Ctrl_ReadRegister(overwritePtr->I2cSlaveAddr, DEMOD2_RESET_REG, &control);

      control &= ~DMD2_RESET_MASK; // Clear out reset bit
      status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr, DEMOD2_RESET_REG, control);  
      break;

    default:
      break;
  }

  // Reset INT reset register according to demod ID
  status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_INT_RESET_REG),
                                      DMD0_INT_RESET);

  // To improve burst noise performance depend on  demod ID.
  control = DMD0_BURST_FREEZE_MODE|DMD0_BURST_FREEZE_MODE_ENABLE;

  status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr, 
                                      MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_BURST_FREEZE_CTRL_REG),
                                      control);

  /* From system team suggestion, change defualt value to below */
  control = 0x8508;
  
  status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_EQU_CARR_DD_CTRL_REG),
                                      control);
  
  control = 0x4179;
  status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_EQU_LLP_CTRL_REG),
                                      control);

  control = 0xD566;
  status |= MxL251_Ctrl_WriteRegister(overwritePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_EQU_FREQ_FAGC_CTR_REG),
                                      control);

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    MxL251_Ctrl_WriteRegisterMask(overwritePtr->I2cSlaveAddr,
                                  MxL251_Ctrl_ConvertDemodIdToAddr(overwritePtr->DemodId, DEMOD0_MASK_TUNER_DONE_REG), 
                                  0x1<<3, 0x1<<3);
  }

  MxL_DLL_DEBUG0("MxL_ConfigDevOverwriteDefault demod %d\n", overwritePtr->DemodId);

  // Invalidate QAM and Annex type
  devContextPtr->Tuners[overwritePtr->DemodId].Demod.CurQamType   = INVALID_ANNEX_QAM;
  devContextPtr->Tuners[overwritePtr->DemodId].Demod.CurAnnexType = INVALID_ANNEX_QAM;  

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodInterrupt - MXL_DEMOD_INTR_MASK_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Michael Sleva
--|
--| DATE CREATED  : 6/19/2009
--|                 6/10/2010
--|
--| DESCRIPTION   : This function configures Interrupt Mask register 
--|                 to enable or disable it.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodInterrupt(PMXL_INTR_CFG_T intrMaskInfoPtr)
{
  MXL_STATUS status;
  UINT16 intrMask = intrMaskInfoPtr->IntrMask;

  MxL_DLL_DEBUG0("MXL_DEMOD_INTR_MASK_CFG - i2cAddr=0x%x, Configuring demod ID = %d,  mask=%04x!\n", intrMaskInfoPtr->I2cSlaveAddr, intrMaskInfoPtr->DemodId, intrMask); 

  status = MxL251_Ctrl_WriteRegister(intrMaskInfoPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(intrMaskInfoPtr->DemodId, DEMOD0_INTR_MASK_REG), intrMask); 
 
  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodSymbolRate - MXL_DEMOD_SYMBOL_RATE_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|               : Sunghoon Park
--|               : Dong Liu
--|               : Richard Liu
--|
--| DATE CREATED  : 6/19/2009
--|               : 05/10/2010
--|               : 12/21/2010
--|
--| DESCRIPTION   : This function configures Symbol Rate for Annex A/B. 
--|                 Resample register bank - 0 : Annex-A bank
--|                                          1 : Annex B 64 QAM
--|                                          2 : Annex B 256 QAM
--|                 Interpolator bypass - 0 : bypass off
--|                                       1 : bypass on
--|                 Symbol rate - 0 : 6.89 MHz (A)
--|                               1 : 5.05 MHz (B64)
--|                               2 : 5.36 Mhz (B256)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodSymbolRate(PMXL_SYMBOL_RATE_T symbolRatePtr) 
{
  UINT8 status = MXL_TRUE;
#ifdef _MXL251_FIXEDPOINT_
  UINT64 sPSin;
  UINT64 symbolRate[SYM_NUM_B_BANK];
  UINT64 resampleRateRatio;
  UINT64 temp;
  UINT64 temp1;
  UINT32 point75;
#else
  REAL32 sPSin,symbolRate[SYM_NUM_B_BANK];
  UINT32 resampleRateRatio;
#endif  
  
  UINT16 resampleRegCtrl;
  UINT8 i, numBank, bank[SYM_NUM_B_BANK];
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(symbolRatePtr->I2cSlaveAddr);
  SINT32 demodLockRangeInHz = 100000;

#ifdef _OOB_SUPPORT_ENABLED_
  UINT16 control;
  PREG_CTRL_INFO_T OobFilterCoefDataPtr = NULL;
#endif // _OOB_SUPPORT_ENABLED_


#ifdef _MXL251_FIXEDPOINT_
#if 0
  MxL_DLL_DEBUG0("MXL_DEMOD_SYMBOL_RATE_CFG - i2cAddr=0x%x, DemodId=%d, SymbolType=%d,  SymbolRate=%x {%f}, SymbolRate256=%x {%f}, OobSymbolRate=%d \n",
      symbolRatePtr->I2cSlaveAddr, 
      symbolRatePtr->DemodId,
      symbolRatePtr->SymbolType,       	  
	  symbolRatePtr->SymbolRate, MXL_VAL(symbolRatePtr->SymbolRate),
      symbolRatePtr->SymbolRate256, MXL_VAL(symbolRatePtr->SymbolRate256),
	  symbolRatePtr->OobSymbolRate);
#endif
	  //MxL_DLL_DEBUG0("\t SymbolRate={%f}, SymbolRate256={%f} ",MXL_VAL64(symbolRatePtr->SymbolRate), MXL_VAL64(symbolRatePtr->SymbolRate256));
#else
	MxL_DLL_DEBUG0("MXL_DEMOD_SYMBOL_RATE_CFG - i2cAddr=0x%x, DemodId=%d, SymbolType=%d, SymbolRate=%f, SymbolRate256=%f OobSymbolRate=%d\n",
      symbolRatePtr->I2cSlaveAddr, 
      symbolRatePtr->DemodId, 
      symbolRatePtr->SymbolType, 
      symbolRatePtr->SymbolRate, 
      symbolRatePtr->SymbolRate256,
      symbolRatePtr->OobSymbolRate);
#endif
  switch (symbolRatePtr->SymbolType)
  {
    case SYM_TYPE_J83A:
#ifdef _MXL251_FIXEDPOINT_
	  symbolRate[0] = 0x1b90;
#else
      symbolRate[0] = (REAL32)6.89;
#endif
      bank[0] = 0; /* Annex-A bank */
      numBank = 1;
      break;

    case SYM_TYPE_J83B:
	  numBank = 2;
      bank[0] = 1; /* Annex-B 64QAM bank */
      bank[1] = 2; /* Annex-B 256QAM bank */
#ifdef _MXL251_FIXEDPOINT_
	  symbolRate[0] = 0x143b;
      symbolRate[1] = 0x1572;
#else
      symbolRate[0] = (REAL32)5.056941;
      symbolRate[1] = (REAL32)5.360537;
#endif
      break;

    case SYM_TYPE_USER_DEFINED_J83A:
	  symbolRate[0] = symbolRatePtr->SymbolRate;
      numBank = 1;
      bank[0] = 0; /* Annex-A bank */
      break;

    case SYM_TYPE_USER_DEFINED_J83B:
      numBank = 2;
      symbolRate[0] = symbolRatePtr->SymbolRate;
      bank[0] = 1; /* Annex-B 64QAM bank */
      symbolRate[1] = symbolRatePtr->SymbolRate256;
      bank[1] = 2; /* Annex-B 256QAM bank */
      break;

#ifdef _OOB_SUPPORT_ENABLED_
    case SYM_TYPE_OOB:
      numBank = 1;
      bank[0] = 0; /* Annex-A bank */
      switch (symbolRatePtr->OobSymbolRate)
      {
        case SYM_RATE_0_772MHz:
#ifdef  _MXL251_FIXEDPOINT_
		  symbolRate[0] = 0x318;
#else
          symbolRate[0] = (REAL32)0.772/* 0x03139094 */;
#endif
          OobFilterCoefDataPtr = MxL_OobAciMfCoef_0_772MHz;
          demodLockRangeInHz = 30000;
          break;

        case SYM_RATE_1_024MHz:
#ifdef  _MXL251_FIXEDPOINT_
		  symbolRate[0] = 0x41a;
#else
          symbolRate[0] = (REAL32)1.024 /* 0x0251C000 */ ;
#endif
          OobFilterCoefDataPtr = MxL_OobAciMfCoef_1_024MHz;
          demodLockRangeInHz = 40000;
          break;

        case SYM_RATE_1_544MHz:
#ifdef  _MXL251_FIXEDPOINT_
		  symbolRate[0] = 0x62e;
#else
          symbolRate[0] = (REAL32)1.544/* 0x0189C84A */ ;
#endif
          OobFilterCoefDataPtr = MxL_OobAciMfCoef_1_544MHz;
          demodLockRangeInHz = 50000;
          break;

        default:
          return MXL_FALSE;
      }
      break;
#endif // _OOB_SUPPORT_ENABLED_

    default:
      return MXL_FALSE;
      break;
  }
#ifdef _MXL251_FIXEDPOINT_
  MxL_DLL_DEBUG0("SymbolRate[0] = %llx ",symbolRate[0]);
#else
  MxL_DLL_DEBUG0("SymbolRate[0] = %f ",symbolRate[0]);
#endif

  devContextPtr->Tuners[symbolRatePtr->DemodId].Demod.LockRangeInHz = demodLockRangeInHz;

  /* Configure Resample rate ratio  */
  for (i = 0; i < numBank; i++)
  {
    /* Read the current settings. */
    status |= MxL251_Ctrl_ReadRegister(symbolRatePtr->I2cSlaveAddr,
        MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId, SYMBOL_RATE_RESAMP_BANK_REG),
        &resampleRegCtrl);
    resampleRegCtrl &= 0xFFF8;

    /* Select Bank */
    resampleRegCtrl |= bank[i]; 
    if (symbolRate[i] <= 0)//FIXME its unsigned int!
    {
      MxL_DLL_DEBUG0("%s - ERROR: symbolRate[i] is 0\n", __FUNCTION__);
      return MXL_FALSE;
    }

#ifdef _MXL251_FIXEDPOINT_	
/* sPSin needs extreme precision due to a multiplier 2^24. In absense of that symbolRate will be way off */
#define MXL251_PRECISION1 40 
#define DELTA_SHIFT (MXL251_PRECISION1 - MXL251_PRECISION)
#define SCALE_PRE1   ((UINT64)1 << MXL251_PRECISION1)
#define SCALE_DELTA  ((UINT64)1 << DELTA_SHIFT)

	temp  =  ((UINT64)devContextPtr->RefPllFreqInMHz << DELTA_SHIFT);
	temp1 =   MXL_DIV64(temp , 24);
	temp1   = MXL_DIV64(temp1, symbolRate[i]);
	sPSin   = temp1;
    resampleRateRatio = 1 << 24;
	symbolRate[i] = resampleRateRatio * temp1;
	symbolRate[i]  = (symbolRate[i] >> (DELTA_SHIFT)); //bring back to MxL precision
#else
    sPSin = (devContextPtr->RefPllFreqInMHz/24)/symbolRate[i];
    resampleRateRatio = 1 << 24;
    symbolRate[i] = (REAL32)resampleRateRatio * sPSin;
#endif

#ifdef _MXL251_FIXEDPOINT_	
	MxL_DLL_DEBUG0("\nSPSin = %llx,ResampleRateRatio = 0x%llx, symbolRate[%d] = {%llx}\n", sPSin, resampleRateRatio, i, symbolRate[i]);
#else
	MxL_DLL_DEBUG0("\nSPSin = %f, ResampleRateRatio = 0x%x, symbolRate[%d]=%f\n", sPSin, resampleRateRatio,i,symbolRate[i]);
#endif

#ifdef _MXL251_FIXEDPOINT_	
	if(sPSin <= 4 * SCALE_DELTA)
#else
    if (sPSin <= 4)
#endif
    {
      /* Interpolator X3 should not be bypassed  */
      resampleRegCtrl &= ~BYPASS_INTERPOLATOR;
#ifdef _MXL251_FIXEDPOINT_
	  point75 = 0x300;
	  symbolRate[i] = MXL_MUL64(symbolRate[i], point75, MXL251_PRECISION);  //*= 0.75;
#else
      symbolRate[i] *= 0.75;
#endif
    }
    else
    {
      /* Interpolator X3 should be bypassed  */
      resampleRegCtrl |= BYPASS_INTERPOLATOR;
#ifdef _MXL251_FIXEDPOINT_
	  symbolRate[i] = MXL_DIV(symbolRate[i],4);
#else
	  symbolRate[i] /= 4;
#endif
    }
    /* Configure Resample_register bank and Interpolator bypass control  */
    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr,
        MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId, SYMBOL_RATE_RESAMP_BANK_REG),
        resampleRegCtrl);

#ifdef _MXL251_FIXEDPOINT_	
	resampleRateRatio = symbolRate[i];	
	MxL_DLL_DEBUG0("\nSPSin = {%llx}, ResampleRateRatio = 0x%llx, symbolRate[%d] = 0x%llx\n", sPSin,\
		resampleRateRatio, i, symbolRate[i]);
#else
	resampleRateRatio = (UINT32)symbolRate[i];
	MxL_DLL_DEBUG0("\nSPSin = %f, ResampleRateRatio = 0x%x, symbolRate[%d]=%f\n", sPSin, resampleRateRatio,i,symbolRate[i]);
#endif

    /* Configure Resample Rate Ratio register */

    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr, 
        MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId, SYMBOL_RATE_RESAMP_RATE_LO_REG), 
        resampleRateRatio & 0xFFFF);
    resampleRateRatio >>= 16;
    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr, 
        MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId, SYMBOL_RATE_RESAMP_RATE_HI_REG), 
        resampleRateRatio & 0xFFFF);

  }

#ifdef _OOB_SUPPORT_ENABLED_
  if (SYM_TYPE_OOB == symbolRatePtr->SymbolType)
  {
    /* Set Annex-A and QPSK  */
    control = MXL_QPSK;
    control |= ANNEX_A_TYPE;
    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId,QAM_ANNEX_TYPE_REG), control);

    /* Watch dog disable <12> */
    status |= MxL251_Ctrl_ReadRegister(symbolRatePtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId,QAM_TYPE_AUTO_DETECT_REG), &control);
    control &= 0xEFFF;
    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId,QAM_TYPE_AUTO_DETECT_REG), control);

    /* Enable Custom ACI COEF <5> */
    /* Enable Matched Filter custom coefficients <6> */
    status |= MxL251_Ctrl_ReadRegister(symbolRatePtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId,DEMOD0_CUSTOM_COEF_ENA_CFG_REG), &control);
    control |= 0x6000;
    status |= MxL251_Ctrl_WriteRegister(symbolRatePtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(symbolRatePtr->DemodId,DEMOD0_CUSTOM_COEF_ENA_CFG_REG), control);

    /* Configure control before writing filter data */
    status |= MxL251_Ctrl_ProgramRegisters(symbolRatePtr->I2cSlaveAddr, symbolRatePtr->DemodId, MxL_OobAciMfCoef);

    /* Program multiple registers for the specified function */
    status |= MxL251_Ctrl_ProgramRegisters(symbolRatePtr->I2cSlaveAddr, symbolRatePtr->DemodId, OobFilterCoefDataPtr);
  }
#endif // _OOB_SUPPORT_ENABLED_

  status |= MxL251_Ctrl_ConfigDemodEqualizer(symbolRatePtr);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodAnnexQamType - MXL_DEMOD_ANNEX_QAM_TYPE_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 6/19/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : This function configure QAM_ANNEX_TYPE and QAM type
--|                 Annex-A type corresponds to J.83 A/C QAM, and OOB signal
--|                 Annex-B for J.83 B QAM signal
--|                 QAM Type : 0 - 16 QAM, 1 - 64 QAM, 2 - 256 QAM,
--|                            3 - 1024 QAM, 4 - 32 QAM, 5 - 128 QAM,
--|                            6 - QPSK
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodAnnexQamType(PMXL_ANNEX_CFG_T annexQamTypePtr) 
{
  UINT16 annnexType, autoDetectCtrl;
  UINT8 status = MXL_TRUE;
  
  MxL_DLL_DEBUG0("MXL_DEMOD_ANNEX_QAM_TYPE_CFG - i2cAddr=0x%x, DemodId=%d, AnnexType=%d, AutoDetectQamType=%d, AutoDetectMode=%d, QamType=%d\n",
                    annexQamTypePtr->I2cSlaveAddr, annexQamTypePtr->DemodId, annexQamTypePtr->AnnexType, annexQamTypePtr->AutoDetectQamType, annexQamTypePtr->AutoDetectMode, annexQamTypePtr->QamType);    
  
  /* Read the current settings. */
  status |= MxL251_Ctrl_ReadRegister(annexQamTypePtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, QAM_ANNEX_TYPE_REG),
                              &annnexType);

  if (annexQamTypePtr->AnnexType == ANNEX_A) annnexType |= ANNEX_A_TYPE;
  else annnexType &= ~ANNEX_A_TYPE; /* Annex-B  */

  status = (UINT8)MxL251_Ctrl_ReadRegister(annexQamTypePtr->I2cSlaveAddr, 
                                           MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, QAM_TYPE_AUTO_DETECT_REG),
                                           &autoDetectCtrl);
  /* autoDetectCtrl = 0x0014; */
  if (annexQamTypePtr->AutoDetectQamType == MXL_ENABLE)
  {
    autoDetectCtrl |= ENABLE_AUTO_DETECT_QAM_TYPE; /* Enable Auto detect QAM Type */
  
    if (annexQamTypePtr->AutoDetectMode == MXL_ENABLE) autoDetectCtrl |= ENABLE_AUTO_DETECT_MODE; /* Enable Auto-detect mode  */
    else autoDetectCtrl &= ~ENABLE_AUTO_DETECT_MODE; /* Disbale Auto-detect mode  */
  }
  else
  { 
    autoDetectCtrl &= ~ENABLE_AUTO_DETECT_QAM_TYPE; /* Disable Auto detect QAM Type */
  
      /* Set QAM type manually */
      /* Reset QAM type <2:0>  */
    annnexType &= 0xFFF8;
    annnexType |= annexQamTypePtr->QamType;
  }
  
  /* Configure Annex Type */
  status |= MxL251_Ctrl_WriteRegister(annexQamTypePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, QAM_ANNEX_TYPE_REG),
                                      annnexType);
  if (annexQamTypePtr->AnnexType == ANNEX_A) 
  {
    status |= MxL251_Ctrl_WriteRegister(annexQamTypePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, MPEG_SYNC_CONTROL_REG),
                                      MPEG_SYNC_CONTROL_ANNEXA);
   
  }
  else
  {
    status |= MxL251_Ctrl_WriteRegister(annexQamTypePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, MPEG_SYNC_CONTROL_REG),
                                      MPEG_SYNC_CONTROL_ANNEXB);

  }
  /* Configure Auto detect mode */
  status |= MxL251_Ctrl_WriteRegister(annexQamTypePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, QAM_TYPE_AUTO_DETECT_REG),
                                      autoDetectCtrl);

  /* Upload Demodule coefficients based on  Annex Type and QAM type. 
   * In Auto detect mode, defer coefficients upload to MxL_GetDemodAnnexQamType be called */
  if (annexQamTypePtr->AutoDetectQamType != MXL_ENABLE)
  {
    status |= MxL251_Ctrl_UploadCustomCoefs(annexQamTypePtr->I2cSlaveAddr, annexQamTypePtr->DemodId, annexQamTypePtr->AnnexType, annexQamTypePtr->QamType);
  }

  // Tentative, FPGA
  // Restart demod, Do this after annex type config
  status |= MxL251_Ctrl_WriteRegister(annexQamTypePtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, 0x63FC),
                                      0xFFFF);
  
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodMpegOutIface - MXL_DEMOD_MPEG_OUT_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 6/19/2009
--|                 8/19/2010
--|                 8/30/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : For Transport stream output through MPEG TS interface
--|                 the following parameters are needed to configure after or before
--|                 demod lock.
--|                  TS output mode : Seral or Parallel
--|                  MSB or LSB first      : In serial output mode
--|                  MPEG Valid Polarity   : Active Low or High
--|                  MPEG Sync Polarity    : Active Low or High
--|                  MPEG Sync Pulse width : 1 bit or 8 bit, only for serial mode
--|                  MPEG CLK Frequency  : 0 - 5.33MHz(default)
--|               (Internally generated) : 1 - 8.00MHz 
--|                                      : 2 - 10.66MHz 
--|                                      : 3 - 21.33MHz 
--|                                      : 4 - 32.00MHz
--|                                      : 5 - 42.66MHz 
--|                                      : 6 - 64.00MHz  
--|                                      : 7 - 85.33MHz 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodMpegOutIface(PMXL_MPEG_OUT_CFG_T mpegOutParamPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 control;
  UINT8 i2cAddr = mpegOutParamPtr->I2cSlaveAddr;

  MxL_DLL_DEBUG0("MXL_DEMOD_MPEG_OUT_CFG - i2cAddr=0x%x, LsbOrMsbFirst=%d, MpegValidPol=%d, MpegSyncPol=%d MpegSyncPulseWidth=%d, MpegClkFreq=%d, MpegErrorIndication=%d Mpeg3WireModeEnable=%d PAD_MPSYN_DRV=%d PAD_MPDAT_DRV=%d PAD_MPVAL_DRV=%d DemodId=%d\n",
                 mpegOutParamPtr->I2cSlaveAddr,
                 mpegOutParamPtr->LsbOrMsbFirst,
                 mpegOutParamPtr->MpegValidPol,
                 mpegOutParamPtr->MpegSyncPol,
                 mpegOutParamPtr->MpegSyncPulseWidth,
                 mpegOutParamPtr->MpegClkFreq,
                 mpegOutParamPtr->MpegErrorIndication,
                 mpegOutParamPtr->Mpeg3WireModeEnable,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPSYN_DRV,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPDAT_DRV,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPVAL_DRV,
                 mpegOutParamPtr->DemodId);

  /* MPEG Clock Frequency */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MPEGOUT_CLK_CTRL_REG, &control);

  control &= 0xF8FF; // Clear out MPEG clock field
  control |= (mpegOutParamPtr->MpegClkFreq << 8);

  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MPEGOUT_CLK_CTRL_REG, control);

  /* Set MPEG paramters according to Demod ID */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_SER_CTRL_REG), &control);
  control &= 0xFFF0;

  /* LSB or MSB first */
  if (mpegOutParamPtr->LsbOrMsbFirst == MPEG_SERIAL_MSB_1ST) control |= (MPEG_SERIAL_MSB_1ST << 2);

  /* SYNC Pulse width */
  if (mpegOutParamPtr->MpegSyncPulseWidth == MPEG_SYNC_WIDTH_BYTE) control |= (MPEG_SYNC_WIDTH_BYTE << 3);

  /* If MPEG Data out format is serial, configure for phase and polarity */
  /* MPEG Data Valid polarity */
  if (mpegOutParamPtr->MpegValidPol == MPEG_ACTIVE_LOW) control |= MPEG_ACTIVE_HIGH;

  /* MPEG Sync polarity */
  if (mpegOutParamPtr->MpegSyncPol == MPEG_ACTIVE_LOW) control |= (MPEG_ACTIVE_HIGH << 1);
  if (mpegOutParamPtr->MpegErrorIndication == MXL_ENABLE)
  {
    control |= (1 << 8);  // dmdX_mpeg_frame_error_indication
  }
  else
  {
    control &= ~(1 << 8);
  }
  control &= ~(1 << 7);// disable_fifo_read_limit

  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_SER_CTRL_REG), control);


  /* MPEG Out error indication */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_ERROR_IND_REG), &control);
  control &= (~ENABLE_MPEG_ERROR_IND); // dmdX_fecb/a_mpeg_erri
  control |= (1 << 11); // dmdX_feca_srs_en
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_ERROR_IND_REG), control);

  /* MPEG 3 wire or 4 wire mode */
  switch (mpegOutParamPtr->DemodId)
  {
    case 0:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEMOD1_MDVAL_GATE_EN_REG,&control);
      control &= (~DEMOD1_MDVAL_GATE_EN_MASK);
      if (mpegOutParamPtr->Mpeg3WireModeEnable)
      {
        control |= DEMOD1_MDVAL_GATE_EN_MASK;
      }
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DEMOD1_MDVAL_GATE_EN_REG, control); 
      break;

    case 1:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEMOD2_MDVAL_GATE_EN_REG,&control);
      control &= (~DEMOD2_MDVAL_GATE_EN_MASK);
      if (mpegOutParamPtr->Mpeg3WireModeEnable)
      {
        control |= DEMOD2_MDVAL_GATE_EN_MASK;
      }
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DEMOD2_MDVAL_GATE_EN_REG, control);
      break;

    default:
      MxL_DLL_ERROR0("Invalid demod id %d", mpegOutParamPtr->DemodId);
      status |= MXL_FALSE;
      break;
  }
 
  /* MPEG Pad output driver configure */
  status |= MxL251_Ctrl_SetMpegPadDrv(i2cAddr, mpegOutParamPtr->DemodId, &mpegOutParamPtr->MpegPadDrv);
  status |= MxL251_Ctrl_SetMpegOutEnable(i2cAddr, mpegOutParamPtr->DemodId, MXL_ENABLE);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MXL251_ConfigDemodeGlobalClkPolarity - MXL_DEMOD_CLK_POLARITY_CFG
--| 
--| AUTHOR        : Richard Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 08/30/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Set global clock polarity
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MXL251_ConfigDemodeGlobalClkPolarity(PMXL_CLK_POLARITY_CFG_T clkPolarPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 control;
  UINT8 i2cAddr = clkPolarPtr->I2cSlaveAddr;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(clkPolarPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEMOD_CLK_POLARITY_CFG - i2cAddr=0x%x, mpegClkPol=%d mpegClkDrv=%d\n", clkPolarPtr->I2cSlaveAddr, clkPolarPtr->MpegClkPol, clkPolarPtr->MpegClkPadDrv);

  // For global clock polarity, read  0x005c bit<6> and write it back 
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEM_MP_CLK_INV_REG, &control);

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // MP_CLK_INV always 1 for ES2
    control |= (MPEG_CLK_NEGATIVE << 6);
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, DEM_MP_CLK_INV_REG, control);

    status |= MxL251_Ctrl_WriteRegisterMask(
        i2cAddr, 
        TP_CLK_INV_REG, 
        TP_CLK_INV_MASK,
        (clkPolarPtr->MpegClkPol == MPEG_CLK_NEGATIVE)?TP_CLK_INV_MASK:0
        );

    // DEM0_MDVAL_GATE_EN_INV ... DEM3_MDVAL_GATE_EN_INV
    status |= MxL251_Ctrl_WriteRegisterMask(
        i2cAddr, 
        DMDx_MDVAL_GATE_EN_INV_REG, 
        DMDx_MDVAL_GATE_EN_INV_MASK,
        (clkPolarPtr->MpegClkPol == MPEG_CLK_NEGATIVE)?0:DMDx_MDVAL_GATE_EN_INV_MASK
        );
  }
  else
  {
    control &= 0xFFBF; // Clear Bit<6>
    if (clkPolarPtr->MpegClkPol == MPEG_CLK_NEGATIVE) control |= (MPEG_CLK_NEGATIVE << 6);
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, DEM_MP_CLK_INV_REG, control);
  }

  control = (UINT16)clkPolarPtr->MpegClkPadDrv;
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, PAD_MCLK_DRV_REG, PAD_MCLK_DRV_MASK, (control<<PAD_MCLK_DRV_SHIFT_BITS));

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodAdcIqFlip - MXL_DEMOD_ADC_IQ_FLIP_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 06/18/2010
--|                 07/06/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Set ADC IQ Flip enable/disable
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodAdcIqFlip(PMXL_ADCIQFLIP_CFG_T adcIqFlipPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 control;
  UINT8 chanId = MxL251_Ctrl_ConvertDemodIdToChanId(adcIqFlipPtr->DemodId);

  /* Enable = 1, disable = 0
   * Flip the I/Q path after ADC
   * DIG_ADCIQ_FLIP <4>
   */
  MxL_DLL_DEBUG0("MXL_DEMOD_ADC_IQ_FLIP_CFG- i2cAddr=0x%x, DemodId=%d, AdcIqFlip=%d\n", adcIqFlipPtr->I2cSlaveAddr, adcIqFlipPtr->DemodId, adcIqFlipPtr->AdcIqFlip);
 
  status |= MxL251_Ctrl_ReadRegister(adcIqFlipPtr->I2cSlaveAddr, DIG_ADCIQ_FLIP_REG, &control);

  /* Demod 0 <11>, Demod 1 <12>, Demod 2 <13>, Demod 3 <14>, */

  if (adcIqFlipPtr->AdcIqFlip == MXL_ENABLE) control |= (DEMOD0_IQ_FLIP << chanId);
  else                                       control &= ~(DEMOD0_IQ_FLIP << chanId);

  status |= MxL251_Ctrl_WriteRegister(adcIqFlipPtr->I2cSlaveAddr, DIG_ADCIQ_FLIP_REG, control);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodEqualizerSetting - MXL_DEMOD_EQUALIZER_FILTER_CFG
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 12/21/2010
--|
--| DESCRIPTION   : Set Demodulator Equalizer
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodEqualizerSetting(PMXL_EQUALIZER_CFG_T equalSettingPtr)
{  
  UINT8 status = MXL_TRUE;
  UINT16 control;

  MxL_DLL_DEBUG0("MXL_DEMOD_EQUALIZER_FILTER_CFG - i2cAddr=0x%x, DemodId=%d, EqualizerSetting = %d", equalSettingPtr->I2cSlaveAddr, equalSettingPtr->DemodId, equalSettingPtr->EqualizerSetting);

  status |= MxL251_Ctrl_ReadRegister(equalSettingPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(equalSettingPtr->DemodId, EQ_SPUR_BYPASS_REG), 
                                     &control);
  
  /* EQ_SPUR_BYPASS <9> */
  /* Enable = 1, Disable = 0 */
  if (equalSettingPtr->EqualizerSetting == MXL_ENABLE) control |= 0x0200;
  else control &= 0xFDFF;

  status |= MxL251_Ctrl_WriteRegister(equalSettingPtr->I2cSlaveAddr, 
                                      MxL251_Ctrl_ConvertDemodIdToAddr(equalSettingPtr->DemodId, EQ_SPUR_BYPASS_REG), 
                                      control);

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodRestart - MXL_DEMOD_RESTART_CFG
--| 
--| AUTHOR        : SidS
--|
--| DATE CREATED  : 05/06/2011
--|
--| DESCRIPTION   : Restart Demod (config data not lost)
--|                 
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodRestart(PMXL_DEMOD_RESTART_CFG_T cmdPtr)
{
  MxL_DLL_DEBUG0("MXL_DEMOD_RESTART_CFG - i2cAddr=0x%x, DemodId=%d\n", 
                  cmdPtr->I2cSlaveAddr, cmdPtr->DemodId);

  // Restart demod, Do this after annex type config
  return MxL251_Ctrl_DemodRestart(cmdPtr->I2cSlaveAddr, cmdPtr->DemodId);
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodInvertSpecrum- MXL_DEMOD_INVERT_SPECTRUM_CFG
--|
--| AUTHOR        : SidS 
--|
--| DATE CREATED  : 05/10/2011
--|
--| DESCRIPTION   : This function inverts the current carrier offset 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodInvertSpecrum(PMXL_DEMOD_INVERT_SPECTRUM_CFG_T paramPtr)
{
  MxL_DLL_DEBUG0("MXL_DEMOD_INVERT_SPECTRUM_CFG- i2cAddr=0x%x, DemodId=%d\n", 
                  paramPtr->I2cSlaveAddr, paramPtr->DemodId);

  return MxL251_Ctrl_DemodInvertSpecrum(paramPtr->I2cSlaveAddr, paramPtr->DemodId);
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MXL251_ConfigTunerDownLoadCalCoef - MXL_TUNER_DOWNLOAD_CAL_COEF_CFG
--| 
--| AUTHOR        : Richard Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 08/25/2010
--|                 12/21/2010
--|                  
--| DESCRIPTION   : This function is used to download rx power calibration 
--|                 coefficients which stored in host side into MxL251
--|                 
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MXL251_ConfigTunerDownLoadCalCoef(PMXL_CAL_COEF_INFO_T calCoefInfoPtr)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(calCoefInfoPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_DOWNLOAD_CAL_COEF_CFG - i2cAddr=0x%x, calType=%d, coefTblSize=%d, CoefTblPtr=%x\n",
      calCoefInfoPtr->I2cSlaveAddr, 
      calCoefInfoPtr->CalType, 
      calCoefInfoPtr->CoefTableSize, 
      (UINT32)(calCoefInfoPtr->CoefTblPtr));

  switch (calCoefInfoPtr->CalType)
  {
    case RX_PWR_CAL:
      return MxL251_PwrLoadCoef(devContextPtr ,calCoefInfoPtr->CoefTblPtr, calCoefInfoPtr->CoefTableSize);

    default:
      return MXL_FALSE;
  }
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigTunerChanTune - MXL_TUNER_CHAN_TUNE_CFG
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 12/21/2010
--|
--| DESCRIPTION   : Tune MxL251 to provided radio frequency with given bandwidth
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigTunerChanTune(PMXL_TUNER_CHAN_TUNE_CFG_T  chanTunePtr)
{
  MXL_TUNER_ID_E tunerId = chanTunePtr->TunerId;
  UINT8 demodChanId = MxL251_Ctrl_GetDemodChanId(tunerId);
  UINT8 i2cAddr = chanTunePtr->I2cSlaveAddr;
  UINT8 status = MXL_TRUE;
  UINT32 wbCapFreqInHz;
  UINT8 wbCapBwInMHz = WB_16_MHz;

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_CHAN_TUNE_CFG - i2cAddr=0x%x, tunerid=0x%x, tunerpowermode=0x%x, bandwidth=%dMhz centerFreq=%dHz\n",
      i2cAddr,
	  tunerId,
	  chanTunePtr->TunerPowerMode,
	  chanTunePtr->BandWidthInMhz,
	  chanTunePtr->CenterFrequencyInHz);

  if (tunerId >= MAX_NUM_TUNER)
  {
    MxL_DLL_ERROR0("invalid tuner id %d", tunerId);
    return MXL_FALSE;
  }

  devContextPtr->Tuners[tunerId].TunerPowerMode = chanTunePtr->TunerPowerMode;

  if (chanTunePtr->TunerPowerMode == MXL_TUNER_DISABLED)
  {
    // DISABLING
    UINT8 ifChanId = MxL251_Ctrl_GetIFChanId(tunerId);
    // Disable NB channels
    status |= MxL251_Ctrl_NbChanDisable(i2cAddr, ifChanId, MXL_ENABLE/*ramp*/);
    status |= MxL251_Ctrl_NbChanDisable(i2cAddr, demodChanId, MXL_ENABLE/*ramp*/);
    // Disable tuner
    status |= MxL251_Ctrl_WbTunerDisable(i2cAddr, tunerId, MXL_BOOL_TRUE/*disableAna*/);
    return (MXL_STATUS)status;
  }
  else
  {
    // ENABLING 

    // Set BandWidthInMHz, so that channel BW is know at the time of WB tune
    devContextPtr->Tuners[tunerId].BandWidthInMHz = chanTunePtr->BandWidthInMhz;

    // By default, place LO to the left of channel 
    wbCapFreqInHz = chanTunePtr->CenterFrequencyInHz - (chanTunePtr->BandWidthInMhz/2)*1000000;

    // Move LO to the right if needed (for VCO avoidance)
    if (MXL_TRUE != MxL251_Ctrl_MoveWbCenterIfNeeded(devContextPtr, tunerId, &wbCapFreqInHz, &wbCapBwInMHz))
    {
      return MXL_FALSE;
    }

#ifdef _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
    // Enable tuner
    devContextPtr->Tuners[tunerId].Demod.NbTunerOffsetInHz = 0;
#endif // _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_

    if (MXL_TRUE != MxL251_Ctrl_WbTunerEnable(
          i2cAddr, 
          tunerId, 
          chanTunePtr->TunerPowerMode, 
          wbCapFreqInHz, 
          wbCapBwInMHz,
          MXL_DISABLE/*fastScan*/))
    {
      return MXL_FALSE;
    }

    if (MXL_TRUE != MxL251_Ctrl_NbChannelEnable(
          i2cAddr,
          tunerId,
          demodChanId,
          chanTunePtr->BandWidthInMhz,
          chanTunePtr->CenterFrequencyInHz,
          MXL_INVERTED_IF_SPECTRUM, // MXL_BOOL IF_Polarity,
          0, // UINT16 IF_AgcSetPoint,
          0 // UINT32 IF_FreqInHz
          ))
    {
      return MXL_FALSE;
    }

    return MXL_TRUE;
  }
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigTunerAgcLockSpeed - MXL_TUNER_AGC_LOCK_SPEED_CFG
--| 
--| AUTHOR        : Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 01/06/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : This function configures AGC lock speed with either 
--|                 fast mode or normal mode
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigTunerAgcLockSpeed(PMXL_AGC_CTRL_SPEED_T agcCtrlSpeedMode)
{
  UINT8 status = MXL_TRUE;

  MxL_DLL_DEBUG0("MXL_TUNER_AGC_LOCK_SPEED_CFG - i2cAddr=0x%x, TunerId=%d, AgcSpeed=%d\n", agcCtrlSpeedMode->I2cSlaveAddr,
                 agcCtrlSpeedMode->TunerId, agcCtrlSpeedMode->AgcSpeedMode);

  switch (agcCtrlSpeedMode->AgcSpeedMode)
  {
    case FAST_AGC_LOCK:
      status = (UINT8)MxL251_Ctrl_WriteRegister(agcCtrlSpeedMode->I2cSlaveAddr, AGC_CTRL_SPEED_REG, FAST_AGC_CTRL_LOCK);
      break;

    case NORMAL_AGC_LOCK:
      status = (UINT8)MxL251_Ctrl_WriteRegister(agcCtrlSpeedMode->I2cSlaveAddr, AGC_CTRL_SPEED_REG, NORMAL_AGC_CTRL_LOCK);
      break;

    default:
      status = (UINT8)MXL_FALSE;
      break;
  }

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigTunerEnhancedChanTune - MXL_TUNER_ENHANCED_CHAN_TUNE_CFG
--| 
--| AUTHOR        : SidS 
--|
--| DATE CREATED  : 06/27/2010
--|
--| DESCRIPTION   : Tune MxL251 to provided radio frequency. 
--|                 If ASIEnable is enabled, searches for extended carrier frequency
--|                 If ECOSEnable is enabled, automatically inverts spectrum to check for lock
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigTunerEnhancedChanTune(PMXL_TUNER_ENHANCED_CHAN_TUNE_CFG_T enhancedChanTunePtr)
{
  UINT8          i2cAddr           = enhancedChanTunePtr->I2cSlaveAddr;
  MXL_TUNER_ID_E tunerId           = enhancedChanTunePtr->TunerId;
  UINT32         ecosIteration     = 0;
  UINT32         newCenterFreqInHz;
  MXL_BOOL       asiFirstIter      = MXL_BOOL_TRUE;
  UINT64         qamTimeOut        = ENHANCED_CHAN_TUNE_TIMEOUT_QAM_LOCK; /* second time: actual_lock_time+20ms */
  UINT64         currentTime;      /* Current time                                         */
  UINT64         globalStartTime;  /* Start time for global timeout checking               */
  ENHANCED_CHAN_TUNE_STATE_E      state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK;
  MXL_DEMOD_ALL_LOCK_STATUS_T     cmdDemodAllLockStatus;
  UINT64         nbEndTime      = 0ULL;
  UINT64         qamLockEndTime = 0ULL;
  UINT64         fecLockEndTime = 0ULL;
  UINT32         wbCapFreqInHz;
  UINT8          wbCapBwInMHz = WB_16_MHz;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_ENHANCED_CHAN_TUNE_CFG - i2cAddr=0x%x, tunerid=0x%x, tunerpowermode=0x%x, "
      "bandwidth=%dMhz centerFreq=%dHz, ASIEnable=%d, ECOSEnable=%d\n",
      i2cAddr, tunerId, enhancedChanTunePtr->TunerPowerMode, enhancedChanTunePtr->BandWidthInMhz, 
      enhancedChanTunePtr->CenterFrequencyInHz, enhancedChanTunePtr->ASIEnable, enhancedChanTunePtr->ECOSEnable);

  /* Initialize */
  cmdDemodAllLockStatus.I2cSlaveAddr = i2cAddr;
  cmdDemodAllLockStatus.DemodId = MxL251_Ctrl_GetDemodId(tunerId);

  /* Measure global start time */
  MxL251_Ctrl_GetCurrTimeInUsec(&globalStartTime); 

  /* Regular WB tune */
  devContextPtr->Tuners[tunerId].TunerPowerMode = enhancedChanTunePtr->TunerPowerMode;

  // Set BandWidthInMHz, so that channel BW is know at the time of WB tune
  devContextPtr->Tuners[tunerId].BandWidthInMHz = enhancedChanTunePtr->BandWidthInMhz;

  // By default, place LO to the left of channel 
  wbCapFreqInHz = enhancedChanTunePtr->CenterFrequencyInHz - (enhancedChanTunePtr->BandWidthInMhz/2)*1000000;

  // Move LO to the right if needed (for VCO avoidance)
  if (MXL_TRUE != MxL251_Ctrl_MoveWbCenterIfNeeded(devContextPtr, tunerId, &wbCapFreqInHz, &wbCapBwInMHz))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_WbTunerEnable(
        i2cAddr, 
        tunerId, 
        enhancedChanTunePtr->TunerPowerMode, 
        wbCapFreqInHz, 
        wbCapBwInMHz,
        MXL_DISABLE/*fastScan*/))
  {
    MxL_DLL_ERROR0("%s - MxL251_Ctrl_WbTunerEnable() failed\n", __FUNCTION__);   
    return MXL_FALSE;
  }

  /* ********************************************************** */
  /* Initial NB Tune to center frequency                        */
  /* ********************************************************** */
  newCenterFreqInHz = enhancedChanTunePtr->CenterFrequencyInHz;

#ifdef _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
  if (MXL_ENABLE == enhancedChanTunePtr->ECOSEnable)
  {
    newCenterFreqInHz = (UINT32)((SINT32)newCenterFreqInHz + devContextPtr->Tuners[tunerId].Demod.LastLockedCarrierOffset);
  }

  devContextPtr->Tuners[tunerId].Demod.NbTunerOffsetInHz = newCenterFreqInHz - enhancedChanTunePtr->CenterFrequencyInHz;
#endif // _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_

  MxL_DLL_DEBUG0("%s - Initial Tune channel [%d] to CenterFrequency=%dHz\n", 
      __FUNCTION__, tunerId, newCenterFreqInHz);

  if (MXL_TRUE != MxL251_Ctrl_NbChannelEnable(
          i2cAddr,
          tunerId,
          MxL251_Ctrl_GetDemodChanId(tunerId),
          enhancedChanTunePtr->BandWidthInMhz,
          newCenterFreqInHz,
          /* Dont care*/ MXL_INVERTED_IF_SPECTRUM, 
          /* Dont care*/ 31*16,
          /* Dont care*/ 5000000))
  {
    MxL_DLL_ERROR0("%s - MxL251_ConfigTunerNbChanTune() failed\n", __FUNCTION__);
    return MXL_FALSE;
  }
  MxL251_Ctrl_DelayUsec(30000);
  if (MXL_TRUE != MxL251_Ctrl_WriteRegister(i2cAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(cmdDemodAllLockStatus.DemodId, 0x63FC),
                                      0xFFFF))
  {
    return MXL_FALSE;
  }

  MxL251_Ctrl_GetCurrTimeInUsec(&nbEndTime); 

  /*******************************************************************************/
  /* Main lock checking loop:                                                    */
  /*   (1) Check QAM lock                                                        */
  /*         - If timed out, search extended carrier frequency offsets and retry */
  /*   (2) Check FEC lock                                                        */
  /*         - If timed out on first time, invert spectrum and retry             */
  /*   (3) Check MPEG lock                                                       */
  /*******************************************************************************/
  for (; ; MxL251_Ctrl_DelayUsec(1000) /* Delay here to give OS some time */)
  {
    /* Get status of all locks */ 
    if (MXL_TRUE != MxL251_GetDemodAllLockStatus(&cmdDemodAllLockStatus))
    {
      MxL_DLL_ERROR0("%s - MxL251_GetDemodAllLockStatus failed\n", __FUNCTION__);
      return MXL_FALSE;
    }

    /* Measure current time */
    MxL251_Ctrl_GetCurrTimeInUsec(&currentTime); 

    /* Check global timeout */
    if ((UINT64)ENHANCED_CHAN_TUNE_TIMEOUT_ALL_LOCK < (currentTime - globalStartTime))
    {
      MxL_DLL_ERROR0("%s - global timeout\n", __FUNCTION__);
      return MXL_FALSE;
    }

    /* Check retune needed */
    if (MXL_BOOL_TRUE == cmdDemodAllLockStatus.RetuneRequired)
    {
      MxL_DLL_ERROR0("%s - false lock detected ... \n", __FUNCTION__);
      return MXL_FALSE;
    }
    
    /* ********************************************************** */
    /* Start of QAM lock detection                                */
    /* If needed, search for extended carrier frequency offsets   */
    /* ********************************************************** */
    if (MXL_UNLOCKED == cmdDemodAllLockStatus.QamLockStatus)
    {
      /* Needed if QAM unlocked after FEC unlocked */ 
      if (ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK != state)
      {
        if (MXL_BOOL_TRUE == asiFirstIter)
        {
          // Restore QamLock timeout
          qamTimeOut = ENHANCED_CHAN_TUNE_TIMEOUT_QAM_LOCK;
        }
        state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK;
      }

      /* No QAM lock, check QAM timeout */
      if ((currentTime-nbEndTime) < qamTimeOut)
      {
        /* No timeout, keep checking QAM lock */
        continue;
      }

      /* ***********************************************************/
      /* QAM lock timed out                                        */
      /* Start of extended carrier frequency offset search         */
      /* ***********************************************************/
      if (MXL_ENABLE != enhancedChanTunePtr->ECOSEnable)
      {
        MxL_DLL_ERROR0("%s - Failed to get QAM lock currentTime=%llu nbEndTime=%llu qamTimeOut=%llu\n", 
            __FUNCTION__, currentTime, nbEndTime, qamTimeOut);
        return MXL_FALSE;
      }

      if (ecosIteration >= NUM_ECOS_OFFSET_SEARCH)
      {
        MxL_DLL_ERROR0("%s - End of carrier offset search\n", __FUNCTION__);
        return MXL_FALSE;
      }

      newCenterFreqInHz = enhancedChanTunePtr->CenterFrequencyInHz;
      if (ecosIteration == 0)
      {
        // Search left
        newCenterFreqInHz -= 2*devContextPtr->Tuners[tunerId].Demod.LockRangeInHz;
      }
      else
      {
        // Search right
        newCenterFreqInHz += 2*devContextPtr->Tuners[tunerId].Demod.LockRangeInHz;
      }

      ecosIteration++;

      /* For new carrier frequency offset: */
      /*   (1) Retune channel              */
      MxL_DLL_DEBUG0("%s - Retune Tuner[%d] to CenterFrequency=%dHz\n", 
          __FUNCTION__, tunerId, newCenterFreqInHz);

#ifdef _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
      devContextPtr->Tuners[tunerId].Demod.NbTunerOffsetInHz = newCenterFreqInHz - enhancedChanTunePtr->CenterFrequencyInHz;
#endif // _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_

#ifdef _DBG_LOCK_TIME_TEST_ENABLED_
      MxL251_Ctrl_GetCurrTimeInUsec(&nbStartTime); 
      LockTimeTest.NumLockTries++;
#endif // _DBG_LOCK_TIME_TEST_ENABLED_

      if (MXL_TRUE != MxL251_Ctrl_NbChannelEnable(
            i2cAddr,
            tunerId,
            MxL251_Ctrl_GetDemodChanId(tunerId),
            enhancedChanTunePtr->BandWidthInMhz,
            newCenterFreqInHz,
            MXL_INVERTED_IF_SPECTRUM, // MXL_BOOL IF_Polarity,
            0, // UINT16 IF_AgcSetPoint,
            0 // UINT32 IF_FreqInHz
            ))
      {
        MxL_DLL_ERROR0("%s - MxL251_Ctrl_NbChannelEnable failed\n", __FUNCTION__);
        return MXL_FALSE;
      }
      MxL251_Ctrl_DelayUsec(30000);
      if (MXL_TRUE != MxL251_Ctrl_WriteRegister(i2cAddr,
                                          MxL251_Ctrl_ConvertDemodIdToAddr(cmdDemodAllLockStatus.DemodId, 0x63FC),
                                          0xFFFF))
      {
        return MXL_FALSE;
      }
      
      MxL251_Ctrl_GetCurrTimeInUsec(&nbEndTime); 
#ifdef _DBG_LOCK_TIME_TEST_ENABLED_
      LockTimeTest.NbTuneTime = (UINT32)(nbEndTime-nbStartTime)/1000U;
#endif // _DBG_LOCK_TIME_TEST_ENABLED_

      /* Try QAM lock again */ 
      continue;
    }

    /* QAM lock detected                                                  */ 

    if (ecosIteration > 1)
    {
      /* At least one search was performed and the last one was (ecosIteration-1) */
      ecosIteration = 0; // Reset ecosIteration
    }

    /* Second iteration, qamTimeOut = (First actual QAM lock time) + 20ms */
    if (MXL_BOOL_TRUE == asiFirstIter && qamTimeOut == ENHANCED_CHAN_TUNE_TIMEOUT_QAM_LOCK)
    {
      qamTimeOut = (currentTime - nbEndTime) + (UINT64)150000; 
    }

    /* ************************************************ */
    /* Start of FEC lock detection                      */
    /* If needed, invert spectrum                       */
    /* ************************************************ */

    if (ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK == state)
    {
      /* Update the state */
      state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_FEC_LOCK;
      MxL_DLL_DEBUG0("%s - QAM locked in %ums\n", __FUNCTION__, (UINT32)(currentTime-nbEndTime)/1000U);
#ifdef _DBG_LOCK_TIME_TEST_ENABLED_
      LockTimeTest.QamLockTime = (UINT32)(currentTime-nbEndTime)/1000U;
#endif // _DBG_LOCK_TIME_TEST_ENABLED_
      /* Restart timer for FEC lock */
      qamLockEndTime = currentTime;
    }

    if (MXL_UNLOCKED == cmdDemodAllLockStatus.FecLockStatus)
    {
      /* Needed if FEC unlocked while waiting for MPEG lock */ 
      if (ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_FEC_LOCK != state)
      {
        state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_FEC_LOCK;
      }

      /* No lock, Check FEC Timeout */
      if ((currentTime-qamLockEndTime) < ENHANCED_CHAN_TUNE_TIMEOUT_FEC_LOCK)
      {
        /* No timeout, try FEC lock again */
        continue;
      }

      /* FEC timed out */ 

      /* Check if auto spectrum inversion is enabled */
      if (MXL_ENABLE != enhancedChanTunePtr->ASIEnable)
      {
        /* If auto spectrum inversion is not enabled, return fail */
        MxL_DLL_ERROR0("%s - FEC lock timed out\n", __FUNCTION__);
        return MXL_FALSE;
      }

      /* Check if spectrum is already inverted */
      if (MXL_BOOL_FALSE == asiFirstIter)
      {
        MxL_DLL_ERROR0("%s - Failed to get FEC lock after inverting spectrum\n", __FUNCTION__);
        return MXL_FALSE;
      }

      /* Spectrum is not inverted yet, invert sprectrum */
      if (MXL_TRUE != MxL251_Ctrl_DemodInvertSpecrum(
            i2cAddr,
            MxL251_Ctrl_GetDemodId(tunerId)))
      {
        MxL_DLL_ERROR0("%s - MxL251_ConfigDemodInvertSpecrum() failed\n", __FUNCTION__);
        return MXL_FALSE;
      }

      MxL_DLL_DEBUG0("%s - Spectrum Inverted\n", __FUNCTION__);

      /* Reset state machine */
      state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_QAM_LOCK;

      /* Update flag         */
      asiFirstIter = MXL_BOOL_FALSE;

      continue;
    }

    /* ************************************************ */
    /* Start of MPEG lock detection                     */
    /* ************************************************ */

    /* Change the state */
    if (ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_FEC_LOCK == state)
    {
      state = ENHANCED_CHAN_TUNE_STATE_WAIT_FOR_MPEG_LOCK;
      MxL_DLL_DEBUG0("%s - FEC locked in %ums\n", __FUNCTION__, (UINT32)(currentTime-qamLockEndTime)/1000U);
#ifdef _DBG_LOCK_TIME_TEST_ENABLED_
      LockTimeTest.FecLockTime = (UINT32)(currentTime-qamLockEndTime)/1000U;
#endif // _DBG_LOCK_TIME_TEST_ENABLED_
      fecLockEndTime = currentTime;
    }

    if (MXL_UNLOCKED == cmdDemodAllLockStatus.MpegLockStatus)
    {
      if ((currentTime-fecLockEndTime) > ENHANCED_CHAN_TUNE_TIMEOUT_MPEG_LOCK)
      { 
        MxL_DLL_ERROR0("%s - MPEG lock timed out\n", __FUNCTION__);
        return MXL_FALSE;
      }
      /* No timeout, try MPEG lock again */
      continue;
    } 
    MxL_DLL_DEBUG0("%s - MPEG locked in %ums\n", __FUNCTION__, (UINT32)(currentTime-fecLockEndTime)/1000U);

    /* ************************************************ */
    /* All locks detected                               */
    /* ************************************************ */
    MxL_DLL_DEBUG0("%s - All locks detected in %ums\n", __FUNCTION__, (UINT32)(currentTime-globalStartTime)/1000U);

#ifdef _DBG_LOCK_TIME_TEST_ENABLED_
    LockTimeTest.MpegLockTime = (UINT32)(currentTime-fecLockEndTime)/1000U;
    LockTimeTest.DmdLockTime = (UINT32)(currentTime-nbEndTime)/1000U;
#endif // _DBG_LOCK_TIME_TEST_ENABLED_

    return MXL_TRUE;
  }

  // This code is not reachable; kept to avoid compiler warning
  return MXL_FALSE;
}

#ifdef _TUNER_TEST_API_ENABLED_
/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigTunerTest - MXL_TUNER_TEST_CFG
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 07/22/2011
--|                 
--| DESCRIPTION   : This API executes a CLI command string specified in cmdPtr->CmdString
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_ConfigTunerTest(PMXL_TUNER_TEST_CFG_T cmdPtr)
{
  char* cmdStr = (char*)(cmdPtr->CmdString);
  // printf("[mxltest]@%08x \"%s\"\n", (UINT32)cmdStr, cmdStr);
  MxL251_Ctrl_ProcessCLICommand(cmdStr);

  return MXL_TRUE;
}
#endif // _TUNER_TEST_API_ENABLED_

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodInterruptStatus - MXL_DEMOD_INTR_STATUS_REQ
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 6/19/2009
--|
--| DESCRIPTION   : This function retrieves the interrupt status when Interrupt 
--|                 is triggered by demod
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodInterruptStatus(PMXL_INTR_STATUS_T intrStatusInfoPtr)
{
  HOST_COMMAND_T demodIntrStatCmd;
  FW_RESPONSE_T demodIntrStatRsp;
  UINT16 intrMask;
  UINT8 status = MXL_TRUE;

  MxL_DLL_DEBUG0("MXL_DEMOD_INTR_STATUS_REQ - i2cAddr=0x%x, DemodId=%d\n", intrStatusInfoPtr->I2cSlaveAddr, intrStatusInfoPtr->DemodId);

  // Get interrupt status using host command
  FORM_CMD_HEADER(demodIntrStatCmd, HOST_CMD_DEMOD_INTR_STATUS_REQ, 0, 0);
  MxL251_Ctrl_CalCheckSum(demodIntrStatCmd.payloadLen, (UINT8 *)demodIntrStatCmd.data, &demodIntrStatCmd.payloadCheckSum); // Calculate CheckSum

  status = (UINT8)MxL251_Ctrl_HostComm(intrStatusInfoPtr->I2cSlaveAddr, &demodIntrStatCmd, &demodIntrStatRsp);
  
  // Copy out demod interrupt status into user buffer 
  if (demodIntrStatRsp.errorCode == RESPONSE_ID_SUCCESS && status == MXL_TRUE)
  {
    intrStatusInfoPtr->IntrStatus = (UINT16)demodIntrStatRsp.data[(UINT8)MxL251_Ctrl_ConvertDemodIdToChanId(intrStatusInfoPtr->DemodId)];
  }

  // Get interrupt mask using register read
  status |= MxL251_Ctrl_ReadRegister(intrStatusInfoPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(intrStatusInfoPtr->DemodId, DEMOD0_INTR_MASK_REG), &intrMask); 
  if (status == MXL_TRUE)
  {
    intrStatusInfoPtr->IntrMask = intrMask; 
  }

  MxL_DLL_DEBUG0("intrStatus=0x%x, intrMask=0x%x\n", intrStatusInfoPtr->IntrStatus, intrStatusInfoPtr->IntrMask);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ClearDemodInterrupt - MXL_DEMOD_INTR_CLEAR_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Michael Sleva
--|
--| DATE CREATED  : 6/19/2009
--|                 6/19/2010
--|
--| DESCRIPTION   : This function clears the triggered interrupt
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ClearDemodInterrupt(PMXL_INTR_CLEAR_T intrClearInfoPtr)
{
  HOST_COMMAND_T intrClrCmd;
  MXL_STATUS status;
  
  MxL_DLL_DEBUG0("MXL_DEMOD_INTR_CLEAR_CFG - i2cAddr=0x%x, DemodId=%d, intClear=0x%x\n", intrClearInfoPtr->I2cSlaveAddr, 
                 intrClearInfoPtr->DemodId, intrClearInfoPtr->IntrClear);
  
  status = MxL251_Ctrl_WriteRegister(intrClearInfoPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(intrClearInfoPtr->DemodId, DEMOD0_INTR_MASK_REG), intrClearInfoPtr->IntrClear); 

  /* Build host command header */
  // serial number  - 0 (not used)
  // payload length - 0 (not sending payload data)
  FORM_CMD_HEADER(intrClrCmd, HOST_CMD_DEMOD_INTR_CLEAR_CFG, 0, 0);

  /* Send clear demod host command to device */
  status = MxL251_Ctrl_SendHostCommand(intrClearInfoPtr->I2cSlaveAddr, &intrClrCmd);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodLockStatus - MXL_DEMOD_QAM_LOCK_REQ
--|                                             MXL_DEMOD_FEC_LOCK_REQ, 
--|                                             MXL_DEMOD_MPEG_LOCK_REQ, 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 6/24/2009
--|                 7/06/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns QAM, FEC, or MPEG Lock status of Demod.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodLockStatus(MXL_CMD_TYPE_E cmdType, PMXL_DEMOD_LOCK_STATUS_T demodLockStatusPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 lock;
  UINT16 readBack, annexType;
 
  switch (cmdType)
  {
    case MXL_DEMOD_QAM_LOCK_REQ:
      MxL_DLL_DEBUG0("MXL_DEMOD_QAM_LOCK_REQ - i2cAddr=0x%x, DemodId=%d\n", demodLockStatusPtr->I2cSlaveAddr, demodLockStatusPtr->DemodId);
      status = (UINT8)MxL251_Ctrl_ReadRegister(demodLockStatusPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodLockStatusPtr->DemodId, QAM_LOCK_STATUS_REG) , &readBack);
      lock = (UINT8)(readBack & 0x0001);
      MxL_DLL_DEBUG0("lock=%d\n", lock);
      break;

    case MXL_DEMOD_MPEG_LOCK_REQ:
      MxL_DLL_DEBUG0("MXL_DEMOD_MPEG_LOCK_REQ - i2cAddr=0x%x, DemodId=%d\n", demodLockStatusPtr->I2cSlaveAddr, demodLockStatusPtr->DemodId);
      status = (UINT8)MxL251_Ctrl_ReadRegister(demodLockStatusPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodLockStatusPtr->DemodId, FEC_MPEG_LOCK_REG), &readBack);
      lock = (UINT8)(readBack & 0x0001);
      MxL_DLL_DEBUG0("lock=%d\n", lock);
      break;

    case MXL_DEMOD_FEC_LOCK_REQ:
      /* Check Annex Type and QAM TYPE  */
      MxL_DLL_DEBUG0("MXL_DEMOD_FEC_LOCK_REQ - i2cAddr=0x%x, DemodId=%d\n", demodLockStatusPtr->I2cSlaveAddr, demodLockStatusPtr->DemodId);
      status |= MxL251_Ctrl_ReadRegister(demodLockStatusPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodLockStatusPtr->DemodId, QAM_ANNEX_TYPE_REG), &readBack); 
      annexType = readBack & ANNEX_A_TYPE;    /* Bit 10 of Reg 0x8001 gives ANNEX Type */

      status |= MxL251_Ctrl_ReadRegister(demodLockStatusPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodLockStatusPtr->DemodId, FEC_MPEG_LOCK_REG), &readBack);

      lock = (UINT8)((readBack >> 1) & 0x0001);

      if (annexType == ANNEX_A_TYPE)
      {
        if (lock == 0) lock = 1; /* Locked to FEC */
        else lock = 0;           /* Unlock */
      }
      MxL_DLL_DEBUG0("lock=%d\n", lock);
      break;

    default:
      return MXL_FALSE;
      break;
  }

  demodLockStatusPtr->Status = (MXL_BOOL)lock;

  return (MXL_STATUS)status; 
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodSnr - MXL_DEMOD_SNR_REQ
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 6/19/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns SNR(Signal to Noise Ratio) and
--|                 supports only float point calculation
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodSnr(PMXL_DEMOD_SNR_INFO_T snrPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 annexType, qamType;
  UINT16 regData, control;
#ifdef _MXL251_FIXEDPOINT_
  MXL_SNR_RANGE_T * snrArray = NULL;
#else
  UINT16 es, m;
  REAL32 mse, constant, k;
#endif
  UINT32 CalcRes;

  MxL_DLL_DEBUG0("MXL_DEMOD_SNR_REQ - i2cAddr=0x%x, DemodId=%d\n", snrPtr->I2cSlaveAddr, snrPtr->DemodId);

  /* Read QAM and Annex type */
  status |= MxL251_Ctrl_ReadRegister(snrPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, QAM_ANNEX_TYPE_REG),
                                     &regData);

  annexType = (regData & 0x0400) >> 10;
  qamType = (regData & 0x0007);

  /* Before reading SNR value, write MSE_AVG_COEF */
  status |= MxL251_Ctrl_ReadRegister(snrPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, SNR_MSE_AVG_COEF_REG),
                                     &control);
  control &= 0x07FF;
  control |= MSE_AVG_COEF;
  status |= MxL251_Ctrl_WriteRegister(snrPtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, SNR_MSE_AVG_COEF_REG),
                                      control);

  status |= MxL251_Ctrl_ReadRegister(snrPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, SNR_EXT_SPACE_ADDR_REG),
                                     &regData);
  regData &= 0x0100;

  /* Set command to read MSE data from Extended space data register  */
  regData |= 0x0089;
  status |= MxL251_Ctrl_WriteRegister(snrPtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, SNR_EXT_SPACE_ADDR_REG),
                                      regData);

  status |= MxL251_Ctrl_ReadRegister(snrPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, SNR_EXT_SPACE_DATA_REG),
                                     &regData);
  
  MxL_DLL_DEBUG0("SNR : QAM Type = %d, Annex type = %d, Reg(0x60FC) = 0x%x\n", qamType, annexType, regData);    

  switch (qamType)
  {
    case 0: /* 16 QAM */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQam16; 
#else
      m = 8;  
      es = 10;
#endif
      break;

    case 1: /* 64 QAM */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQam64; 
#else
      m = 16;  
      es = 42;
#endif
      break;

    case 2: /* 256 QAM */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQam256; 
#else
      m = 32;  
      es = 170;
#endif
      break;

    case 4: /* 32 QAM */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQam32; 
#else
      m = 16;  
      es = 20;
#endif
      break;

    case 5: /* 128 QAM */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQam128; 
#else
      m = 32;  
      es = 82;
#endif
      break;

    case 6: /* QPSK */
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQpsk; 
#else
      m = 8;  
      es = 18;
#endif
      break;

    default:
#ifdef _MXL251_FIXEDPOINT_
		snrArray = snrRangeQpsk; 
#else
      m = 1;  
      es = 1;
#endif
      break;
  }

  /*
   * MSE = 10log10(regData * 2^ -(N + Log2(1/16)) * 8/K)
   * SNR = -1 * MSE
   * n = 16 (No. of Bits)
   * K = es/(M/2)2
   * E & M change with QAM types
   */
#ifndef _MXL251_FIXEDPOINT_
  constant = 1.0/1048576; /* 2 ^(-N + Log2(1/16); */
  k = (REAL32)pow(((REAL64)m/2), 2.0);
  k = (REAL32)(es)/k;
#endif
  
#ifdef _MXL251_FIXEDPOINT_
  if (regData != 0)
  {    
	  snrPtr->SNR = MxLWare251_ReqDemodSnrLinear(snrArray, regData);
  }
  else
  {
    snrPtr->SNR = 0;
  }
#else
  if (regData != 0)
  { 
	mse = 10 * (REAL32)log10((REAL32)regData * constant * (8/k));
	snrPtr->SNR = -1 * mse;
  }
  else
  {
    snrPtr->SNR = 0;
  }
  MxL_DLL_DEBUG0("mse = %f, SNR=%f \n", mse,snrPtr->SNR);
#endif

  /* SNR/MSE size (num of symbols) */
  status |= MxL251_Ctrl_ReadRegister(snrPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(snrPtr->DemodId, PHY_EQUALIZER_LLP_CONTROL_1_DEBUG_MSE_REGISTER),
                                     &regData);
  regData = (regData & 0xF800) >> 11;
  CalcRes = (regData + 1)/2 + 5;
  /* pow(2, CalcRes) */
  snrPtr->MseSize = 1 << CalcRes;

#ifdef _MXL251_FIXEDPOINT_
  //MxL_DLL_DEBUG0("SNR = {%f}dB mseSize=%d\n", MXL_VAL(snrPtr->SNR), snrPtr->MseSize);    
#else
  MxL_DLL_DEBUG0("SNR = %fdB mseSize=%d\n", snrPtr->SNR, snrPtr->MseSize);    
#endif 

  return (MXL_STATUS)status;           
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodBer - MXL_DEMOD_BER_UNCODED_BER_CER_REQ
--| 
--| AUTHOR        : Brenndon Lee, Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 6/19/2009, 07/07/2010 
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns BER(Bit Error Ratio), CER, and Uncoded BER
--|                 It supports only for float point calculation
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodBer(PMXL_DEMOD_BER_INFO_T berInfoPtr) 
{
  UINT8  status = MXL_TRUE;

  UINT32 cw_corr_count;
  UINT32 cw_err_count;
  UINT32 cw_count;
  UINT32 cw_unerr_count;
  UINT32 corr_bits;        
  UINT32 err_mpeg;
  UINT16 received_mpeg;
  UINT64 x, y;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(berInfoPtr->I2cSlaveAddr);

  UINT16 regData, annexType;
  UINT8  DemodId;

  MxL_DLL_DEBUG0("MXL_DEMOD_BER_UNCODED_BER_CER_REQ - i2cAddr=0x%x, DemodId=%d\n", berInfoPtr->I2cSlaveAddr, berInfoPtr->DemodId);

 
  MxL_DLL_DEBUG0("MXL_DEMOD_BER_UNCODED_BER_CER_REQ, i2cAddr =0x%x BER is updated. \n", devContextPtr->i2cSlaveAddr);
  /* Check Annex Type and QAM TYPE */
  status |= MxL251_Ctrl_ReadRegister(berInfoPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(berInfoPtr->DemodId, QAM_ANNEX_TYPE_REG), 
                                     &regData); 
  annexType = regData & ANNEX_A_TYPE;    /* Bit 10 of Reg 0x8001 gives ANNEX Type */

  /* Clear the internal HW counters to avoid overflow */
  status |= MxL251_Ctrl_WriteRegister(berInfoPtr->I2cSlaveAddr, 
                                      MxL251_Ctrl_ConvertDemodIdToAddr(berInfoPtr->DemodId, STAMP_REG), 
                                      0x0055);

  MxL251_Ctrl_GetMCNSSD(berInfoPtr->I2cSlaveAddr, berInfoPtr->DemodId, CW_CORR_COUNT, &cw_corr_count);
  MxL251_Ctrl_GetMCNSSD(berInfoPtr->I2cSlaveAddr, berInfoPtr->DemodId, CW_ERR_COUNT, &cw_err_count);
  MxL251_Ctrl_GetMCNSSD(berInfoPtr->I2cSlaveAddr, berInfoPtr->DemodId, CW_COUNT, &cw_count);
  MxL251_Ctrl_GetMCNSSD(berInfoPtr->I2cSlaveAddr, berInfoPtr->DemodId, CORR_BITS, &corr_bits);

  cw_unerr_count = cw_count - cw_corr_count - cw_err_count;

  status |= MxL251_Ctrl_ReadRegister(berInfoPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(berInfoPtr->DemodId,FRCNT_REG), &regData); 

  /* ERR_MPEG */
  if (annexType == ANNEX_A_TYPE) 
  {
    received_mpeg = 0xFFFF - regData;
    err_mpeg = cw_err_count;
  }
  else
  {
    received_mpeg = regData;

    status |= MxL251_Ctrl_ReadRegister(berInfoPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(berInfoPtr->DemodId,MEF_REG), &regData); 
    err_mpeg = regData;
  }

  DemodId = berInfoPtr->DemodId;
  /* Update Statistic counter */
#ifdef _MXL_PATE_BUILD_
  if (PATE_I2C_MODE_SIM2 == PATE_I2cMode)
#endif // _MXL_PATE_BUILD_
  {
  devContextPtr->AccStatCounter.AccCwCorrCount[DemodId] += cw_corr_count;
  devContextPtr->AccStatCounter.AccCwErrCount[DemodId] += cw_err_count;
  devContextPtr->AccStatCounter.AccCwUnerrCount[DemodId] += cw_unerr_count;
  devContextPtr->AccStatCounter.AccCorrBits[DemodId] += corr_bits;
  devContextPtr->AccStatCounter.AccErrMpeg[DemodId] += err_mpeg;
  devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId] += received_mpeg;
  devContextPtr->AccStatCounter.AccCwReceived[DemodId] = devContextPtr->AccStatCounter.AccCwCorrCount[DemodId] + \
                                                                devContextPtr->AccStatCounter.AccCwErrCount[DemodId]  + \
                                                                devContextPtr->AccStatCounter.AccCwUnerrCount[DemodId];
  }

  /* Check boundary case */
  if (devContextPtr->AccStatCounter.AccCwReceived[DemodId] == 0)
  {
	  berInfoPtr->CER = 0;
  }
  else
  {
    /* Calculate CER */
#ifdef _MXL251_FIXEDPOINT_ 
      //berInfoPtr->CER  = (devContextPtr->AccStatCounter.AccCwErrCount[DemodId] * (1 << MXL251_PRECISION)/ devContextPtr->AccStatCounter.AccCwReceived[DemodId]);
    x = devContextPtr->AccStatCounter.AccCwErrCount[DemodId] * (1 << MXL251_PRECISION);
    y = devContextPtr->AccStatCounter.AccCwReceived[DemodId];
    berInfoPtr->CER = MXL_DIV64(x, y);
#else
    berInfoPtr->CER = (REAL64)devContextPtr->AccStatCounter.AccCwErrCount[DemodId] / devContextPtr->AccStatCounter.AccCwReceived[DemodId];
#endif
  }

  /* Calculate BER and Uncoded BER */
  if (annexType == ANNEX_A_TYPE) 
  {
    if (devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId] == 0) 
	{
		berInfoPtr->BER = 0;
	}
    else
	{
#ifdef _MXL251_FIXEDPOINT_ 
        //berInfoPtr->BER  =  ((1 << MXL251_PRECISION) * 9 * devContextPtr->AccStatCounter.AccErrMpeg[DemodId]) / (188 * 8 * devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId]);
	x = (1 << MXL251_PRECISION) * 9 * devContextPtr->AccStatCounter.AccErrMpeg[DemodId];
    y = 88 * 8 * devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId];
    berInfoPtr->BER = MXL_DIV64(x, y);
#else
		berInfoPtr->BER = (9.0 * (REAL64)devContextPtr->AccStatCounter.AccErrMpeg[DemodId]) / (188.0 * 8.0 * (REAL64)devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId]);
#endif
	}
    if (devContextPtr->AccStatCounter.AccCwReceived[DemodId] == 0) 
	{
		berInfoPtr->UncodedBER = 0;
	}
    else
	{
#ifdef _MXL251_FIXEDPOINT_ 
        //berInfoPtr->UncodedBER  = ((1 << MXL251_PRECISION) * devContextPtr->AccStatCounter.AccCorrBits[DemodId]) / (devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 204 * 8);
		x = ((1 << MXL251_PRECISION) * devContextPtr->AccStatCounter.AccCorrBits[DemodId]);
        y = (devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 204 * 8);
		berInfoPtr->UncodedBER = MXL_DIV64(x, y);
#else
		berInfoPtr->UncodedBER = (REAL64)devContextPtr->AccStatCounter.AccCorrBits[DemodId] / ((REAL64)devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 204.0 * 8.0);
#endif
	}
  }
  else
  {
    if (devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId] == 0) 
	{
		berInfoPtr->BER = 0;
	}
    else
	{
#ifdef _MXL251_FIXEDPOINT_ 
        //berInfoPtr->BER  = ((1 << MXL251_PRECISION) * 10 * devContextPtr->AccStatCounter.AccErrMpeg[DemodId]) / (188 * 8 * devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId]);
        x = ((1 << MXL251_PRECISION) * 10 * devContextPtr->AccStatCounter.AccErrMpeg[DemodId]);
        y = (188 * 8 * devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId]);
		berInfoPtr->BER = MXL_DIV64(x, y);
#else
		berInfoPtr->BER = (10.0 * (REAL64)devContextPtr->AccStatCounter.AccErrMpeg[DemodId]) / (188.0 * 8.0 * (REAL64)devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId]);
#endif
	}
    if (devContextPtr->AccStatCounter.AccCwReceived[DemodId] == 0)
	{
		berInfoPtr->UncodedBER = 0;
	}
    else
	{
#ifdef _MXL251_FIXEDPOINT_ 
        //berInfoPtr->UncodedBER = ((1 << MXL251_PRECISION) * devContextPtr->AccStatCounter.AccCorrBits[DemodId])/ (devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 128 * 7);
		x = ((1 << MXL251_PRECISION) * devContextPtr->AccStatCounter.AccCorrBits[DemodId]); 
        y = (devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 128 * 7);
		berInfoPtr->UncodedBER = MXL_DIV64(x, y);
#else
		berInfoPtr->UncodedBER = (REAL64)devContextPtr->AccStatCounter.AccCorrBits[DemodId] / ((REAL64)devContextPtr->AccStatCounter.AccCwReceived[DemodId] * 128.0 * 7.0);
#endif
	}
  }
#ifdef _MXL251_FIXEDPOINT_
  //MxL_DLL_DEBUG0("\nCER = {%f}", MXL_VAL64(berInfoPtr->CER));
  //MxL_DLL_DEBUG0("\nBER = {%f}", MXL_VAL64(berInfoPtr->BER));
  //MxL_DLL_DEBUG0("\nUncoded BER ={%f}\n", MXL_VAL64(berInfoPtr->UncodedBER));
#else
  MxL_DLL_DEBUG0("CER = %f\n", berInfoPtr->CER);
  MxL_DLL_DEBUG0("BER = %f\n", berInfoPtr->BER);
  MxL_DLL_DEBUG0("Uncoded BER = %f\n", berInfoPtr->UncodedBER);
#endif
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodStatisticCounters - MXL_DEMOD_STAT_COUNTERS_REQ
--| 
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 6/24/2009
--|                 12/21/2010
--|                 
--| DESCRIPTION   : It reads back statistic counters
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodStatisticCounters(PMXL_DEMOD_STAT_COUNT_T statCountPtr)
{
  MXL_STATUS status = MXL_FALSE;
  UINT8 DemodId;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(statCountPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEMOD_STAT_COUNTERS_REQ - i2cAddr=0x%x, DemodId=%d\n", statCountPtr->I2cSlaveAddr, statCountPtr->DemodId);

  MxL_DLL_DEBUG0("MXL_DEMOD_STAT_COUNTERS_REQ, Read i2cAddr = 0x%x Statistic Counter. \n", devContextPtr->i2cSlaveAddr);

  DemodId = statCountPtr->DemodId;

  /* Accumulated counter for corrected code word */
  statCountPtr->AccCwCorrCount = devContextPtr->AccStatCounter.AccCwCorrCount[DemodId];

  /* Accumulated counter for uncorrected code word */
  statCountPtr->AccCwErrCount = devContextPtr->AccStatCounter.AccCwErrCount[DemodId];

  /* Accumulated total received code words */
  statCountPtr->AccCwReceived = devContextPtr->AccStatCounter.AccCwReceived[DemodId];
    
  /* Accumulated counter for code words received */
  statCountPtr->AccCwUnerrCount = devContextPtr->AccStatCounter.AccCwUnerrCount[DemodId];

  /* Accumulated counter for corrected bits */
  statCountPtr->AccCorrBits = devContextPtr->AccStatCounter.AccCorrBits[DemodId];

  /* Accumulated counter for erred mpeg frames */
  statCountPtr->AccErrMpeg = devContextPtr->AccStatCounter.AccErrMpeg[DemodId];

  /* Accumulated counter for received mpeg frames */
  statCountPtr->AccReceivedMpeg = devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId];     

  status = MXL_TRUE;
  
  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ResetDemodStatCounters - MXL_DEMOD_RESET_STAT_COUNTER_CFG
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|
--| DATE CREATED  : 6/25/2009
--|                 12/21/2010
--|                 
--| DESCRIPTION   : It resets the statistic variales that shall be used to calculate 
--|                 BER, CER, Uncoded BER.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ResetDemodStatCounters(PMXL_RESET_COUNTER_T resetCountPtr)
{
  MXL_STATUS status = MXL_FALSE;
  UINT8 DemodId;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(resetCountPtr->I2cSlaveAddr);
    
  MxL_DLL_DEBUG0("MXL_DEMOD_RESET_STAT_COUNTER_CFG - i2cAddr=0x%x, DemodId=%d\n", resetCountPtr->I2cSlaveAddr, resetCountPtr->DemodId);

  DemodId = resetCountPtr->DemodId;
  MxL_DLL_DEBUG0("MXL_DEMOD_RESET_STAT_COUNTER_CFG, i2caddr %d BER accumulatedvalue is reset. \n", resetCountPtr->I2cSlaveAddr);
  devContextPtr->AccStatCounter.AccCwCorrCount[DemodId] = 0;
  devContextPtr->AccStatCounter.AccCwErrCount[DemodId] = 0;
  devContextPtr->AccStatCounter.AccCwUnerrCount[DemodId] = 0;
  devContextPtr->AccStatCounter.AccCwReceived[DemodId] = 0;
  devContextPtr->AccStatCounter.AccCorrBits[DemodId] = 0;
  devContextPtr->AccStatCounter.AccErrMpeg[DemodId] = 0;
  devContextPtr->AccStatCounter.AccReceivedMpeg[DemodId] = 0;

  status = MXL_TRUE;
  return status;
}
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251_ReqDemodSnrLinear
--| 
--| AUTHOR        : Randhir Jha
--|
--| DATE CREATED  : 22/3/2013
--|                  
--| DESCRIPTION   : Finds a,b coeffs for given snr_rawValue and calculates SNR:
--|                 snr = a*(rawValue) + b 
--|        
--|                 NOTE: Reused this function from Herculeus!
--|                 
--| RETURN VALUE  : snr : This has MXL251_PRECISION fractional bits.
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
static UINT32 MxLWare251_ReqDemodSnrLinear(MXL_SNR_RANGE_T * snrArray, UINT16 rawValue)
{
  UINT32 snr = 0;
  UINT8  index = 0;
  UINT64 snr_temp;

  if (rawValue)
  {
    while ((snrArray[index].x2) && (rawValue > snrArray[index].x2)) index++;

    if (snrArray[index].x2 == 0) index--;
    MxL_DLL_DEBUG0("index=%d, a=%d, b=%d\n", index, snrArray[index].a, snrArray[index].b);
    snr = (UINT32)(snrArray[index].a * rawValue + snrArray[index].b);
	snr_temp = MXL_SCALEUP64(snr, MXL251_PRECISION) ;
    snr = (UINT32)MXL_DIV64(snr_temp, 100000);
  }
  return snr;
}
#endif
/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodAnnexQamType - MXL_DEMOD_ANNEX_QAM_TYPE_REQ
--| 
--| AUTHOR        : Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 07/06/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Get Annex (B or A) and Qam type
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodAnnexQamType(PMXL_DEMOD_ANNEXQAM_INFO_T annexQamTypePtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 regData;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(annexQamTypePtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEMOD_ANNEX_QAM_TYPE_REQ - i2cAddr=0x%x, DemodId=%d\n", 
                 annexQamTypePtr->I2cSlaveAddr, annexQamTypePtr->DemodId);

  status |= MxL251_Ctrl_ReadRegister(annexQamTypePtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(annexQamTypePtr->DemodId, QAM_ANNEX_TYPE_REG),
                                     &regData); 

  /* Annex type */
  annexQamTypePtr->AnnexType = (MXL_ANNEX_TYPE_E)((regData & 0x0400) >> 10);

  /* QAM type */
  annexQamTypePtr->QamType = (MXL_QAM_TYPE_E)(regData & 0x0007);

  /* Check if QAM or Annex type has been changed since last update */
  if (devContextPtr->Tuners[annexQamTypePtr->DemodId].Demod.CurQamType   != annexQamTypePtr->QamType ||
      devContextPtr->Tuners[annexQamTypePtr->DemodId].Demod.CurAnnexType != annexQamTypePtr->AnnexType)
  {
    status |= MxL251_Ctrl_UploadCustomCoefs(annexQamTypePtr->I2cSlaveAddr, annexQamTypePtr->DemodId, annexQamTypePtr->AnnexType, annexQamTypePtr->QamType);
  }

  MxL_DLL_DEBUG0("AnnexType=%d, QamType=%d\n", annexQamTypePtr->AnnexType, annexQamTypePtr->QamType);
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodCarrierOffset - MXL_DEMOD_CARRIER_OFFSET_REQ
--| 
--| AUTHOR        : Sunghoon Park, Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 06/17/2009, 07/07/2010 
--|                 12/21/2010
--|
--| DESCRIPTION   : Get carrier offset
--|                 before reading Carrier Offset, 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodCarrierOffset(PMXL_DEMOD_CARRIEROFFSET_INFO_T carrierOffsetPtr)
{
  UINT8 status = MXL_TRUE;

  MXL_DEMOD_ANNEXQAM_INFO_T annexQamType;

  UINT8 byPass;
  UINT16 regData;
#ifdef _MXL251_FIXEDPOINT_
  UINT64 SymbolRate = 0, SymbolRate_temp;
  UINT64 nominalSymRate = 0;
  UINT64 temp;
  SINT16 reg ;
  SINT64 co_val;//MXL251_PRECISION * 3
  //REAL64 co_flt;
#else
  REAL32 SymbolRate = 0;
  UINT32 nominalSymRate = 0;
#endif

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(carrierOffsetPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEMOD_CARRIER_OFFSET_REQ - i2cAddr=0x%x, DemodId=%d\n", carrierOffsetPtr->I2cSlaveAddr, carrierOffsetPtr->DemodId);

  /* Before readback, carrier offset register needs to be written by data 0x0087  */
  status |= MxL251_Ctrl_WriteRegister(carrierOffsetPtr->I2cSlaveAddr, 
                                      MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, CARRIER_OFFSET_REG), 
                                      0x0087);
  
  /* Check Annex and Qam type */
  annexQamType.I2cSlaveAddr = carrierOffsetPtr->I2cSlaveAddr;
  annexQamType.DemodId = carrierOffsetPtr->DemodId;
  status |= MxL251_GetDemodAnnexQamType(&annexQamType);

  /* Read the current settings. */
  status |= MxL251_Ctrl_ReadRegister(carrierOffsetPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, SYMBOL_RATE_RESAMP_BANK_REG), 
                                     &regData);

  /* Save bypass mode */
  byPass = (UINT8)regData & 0x0010;

  regData &= 0xFFF8;
  /* Config Bank <2:0> */
  if (annexQamType.AnnexType == ANNEX_A)
  {
    /* Annex A bank = 0 */
    regData |= 0x0000;
  }
  else
  {
    if (annexQamType.QamType == QAM64)
    {
      /* Annex B and 64QAM = 1 */
      regData |= 0x0001;
    }
    else
    {
      /* Annex B and 256QAM = 2 */
      regData |= 0x0002;
    }
  }
  status |= MxL251_Ctrl_WriteRegister(carrierOffsetPtr->I2cSlaveAddr, 
                               MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, SYMBOL_RATE_RESAMP_BANK_REG), 
                               regData);

  /* SYMBOL_RATE_RESAMP_RATE_HI_REG */
  status |= MxL251_Ctrl_ReadRegister(carrierOffsetPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, SYMBOL_RATE_RESAMP_RATE_HI_REG), 
                              &regData);
  nominalSymRate = ((UINT32)regData) << 16;

  /* SYMBOL_RATE_RESAMP_RATE_LO_REG */
  status |= MxL251_Ctrl_ReadRegister(carrierOffsetPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, SYMBOL_RATE_RESAMP_RATE_LO_REG), 
                              &regData);
  nominalSymRate |= (UINT32)regData;

#ifdef _MXL251_FIXEDPOINT_
#define PRECISON_EXT  26  
  nominalSymRate <<= PRECISON_EXT; //scale up 
  if (0 != byPass)
  {
    SymbolRate = (nominalSymRate * 4) >> 24; 
  }
  else
  {
      //SymbolRate = ((nominalSymRate) / 0x300) >> 24; //0.75 in required precision //(PRECISON_EXT-MXL251_PRECISION)
    temp = MXL_DIV64(nominalSymRate, 0x300);
    SymbolRate = temp >> 24; 
  }

#else
  if (0 != byPass)
  {
    SymbolRate = (REAL32)(nominalSymRate * 4 / (1 << 24));
  }
  else
  {
    SymbolRate = (REAL32)(nominalSymRate / (REAL32)((1 << 24) * 0.75));
  }
#endif

  //NominalSymRate is a UINT32 assigned value, so checking against zero shold be okay.
  if (SymbolRate <= 0)
  {
    MxL_DLL_DEBUG0("%s - Error: SymbolRate has not been programmed\n", __FUNCTION__);
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  SymbolRate_temp = ((UINT64)devContextPtr->RefPllFreqInMHz << PRECISON_EXT); //(PRECISON_EXT + MXL251_PRECISION)
  //SymbolRate_temp /= 24; 
  SymbolRate_temp = MXL_DIV64(SymbolRate_temp, 24); 

  //SymbolRate_temp /= SymbolRate;//(2*MXL251_PRECISION)
  SymbolRate_temp = MXL_DIV64(SymbolRate_temp, SymbolRate);//(2*MXL251_PRECISION)
  SymbolRate = (UINT32)(SymbolRate_temp >> MXL251_PRECISION); //(MXL251_PRECISION)

#else
  SymbolRate = (devContextPtr->RefPllFreqInMHz/24.0f)/SymbolRate;
#endif

  /* Read the current settings. */
  status |= MxL251_Ctrl_ReadRegister(carrierOffsetPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(carrierOffsetPtr->DemodId, CARRIER_OFFSET_RB_REG), 
                                     &regData);
#ifdef _MXL251_FIXEDPOINT_
  devContextPtr->Tuners[carrierOffsetPtr->DemodId].Demod.CurSymbolRate = (UINT32)SymbolRate;
#else
  devContextPtr->Tuners[carrierOffsetPtr->DemodId].Demod.CurSymbolRate = SymbolRate;
#endif
  
  /* CarrierOffset = SymbolRate * Singed(regData) * 2^(-N+1+log2(1/16)) */
  /* N = number of bits, therefore, N = 16  */
#ifdef _MXL251_FIXEDPOINT_
  reg =   (SINT16)regData;
  co_val = (SINT64)((SymbolRate_temp << MXL251_PRECISION) * reg);//MXL251_PRECISION * 3
  
  co_val >>= 19; //(3 * MXL251_PRECISION)
  carrierOffsetPtr->CarrierOffset  = co_val; //3 * MXL251_PRECISION  
  //co_flt = (REAL64)(co_val)/(1 << (3*MXL251_PRECISION));
  //MxL_DLL_DEBUG0("CarrierOffset=%fMhz\n", co_flt); //3 * MXL251_PRECISION  
#else
  carrierOffsetPtr->CarrierOffset = SymbolRate * (SINT16)regData;
  /* pow (2, -19) */
  carrierOffsetPtr->CarrierOffset *= (REAL64)1 / (REAL64)(1 << 19); 
  MxL_DLL_DEBUG0("CarrierOffset=%fMhz\n", carrierOffsetPtr->CarrierOffset);
#endif


  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodInterleaverDepth - MXL_DEMOD_INTERLEAVER_DEPTH_REQ
--| 
--| AUTHOR        : Sunghoon Park
--|
--| DATE CREATED  : 06/18/2009
--|
--| DESCRIPTION   : Get Interleaver Depth I and J
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodInterleaverDepth(PMXL_INTERDEPTH_INFO_T interDepthPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 regData, annexType;
  PINTERLEAVER_LOOKUP_INFO_T interDepthLoopUpTable = MxL251_InterDepthLookUpTable;

  MxL_DLL_DEBUG0("MXL_DEMOD_INTERLEAVER_DEPTH_REQ - i2cAddr=0x%x, DemodId=%d\n", interDepthPtr->I2cSlaveAddr, interDepthPtr->DemodId);

  /* Read the current Annex Type <10> */
  status |= MxL251_Ctrl_ReadRegister(interDepthPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(interDepthPtr->DemodId, QAM_ANNEX_TYPE_REG), 
                              &annexType);
  annexType &= 0x0400;

  /* Before readback index for interleaver depth, clear out bit6-3 */
  status |= MxL251_Ctrl_ReadRegister(interDepthPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(interDepthPtr->DemodId, INTERLEAVER_DEPTH_REG), 
                              &regData);

  regData &= 0xFF87;
  status |= MxL251_Ctrl_WriteRegister(interDepthPtr->I2cSlaveAddr, 
                               MxL251_Ctrl_ConvertDemodIdToAddr(interDepthPtr->DemodId, INTERLEAVER_DEPTH_REG), 
                               regData);
  
  /* Read the current settings. */
  status |= MxL251_Ctrl_ReadRegister(interDepthPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(interDepthPtr->DemodId, INTERLEAVER_DEPTH_REG), 
                              &regData);

  /* Interleaver Depth I, J <6:3>
   * regData = Control word(4bits) becomes 
   * the address of InterleaverDepth LookUp Table
   */
  regData = (regData >> 3) & 0x000F;

  MxL_DLL_DEBUG0("Interleaver depth Index : %d\n", regData);

  if (annexType == ANNEX_B) /* Annex_B */
  {
    interDepthPtr->InterDepthI = interDepthLoopUpTable[regData].interDepthI;
    interDepthPtr->InterDepthJ = interDepthLoopUpTable[regData].interDepthJ;
  }
  else           /* Annex_A */
  {
    interDepthPtr->InterDepthI = 12;
    interDepthPtr->InterDepthJ = 17;
  }

  MxL_DLL_DEBUG0("InterDepthI=%d, InterDepthJ=%d\n", interDepthPtr->InterDepthI, interDepthPtr->InterDepthJ);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodEqualizerFilter - MXL_DEMOD_EQUALIZER_FILTER_REQ
--| 
--| AUTHOR        : Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 06/18/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : Get Equalizer filter
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodEqualizerFilter(PMXL_DEMOD_EQUALFILTER_INFO_T equalizerFilterPtr)
{
  UINT16 regData;
  UINT8 status = MXL_TRUE;
  UINT8 i;

  MxL_DLL_DEBUG0("MXL_DEMOD_EQUALIZER_FILTER_REQ - i2cAddr=0x%x, DemodId=%d\n", equalizerFilterPtr->I2cSlaveAddr, equalizerFilterPtr->DemodId);

  status |= MxL251_Ctrl_ReadRegister(equalizerFilterPtr->I2cSlaveAddr,
                                     MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_FILTER_REG),
                                     &regData);
  /* Read FFE */
  regData = 0x0100;
  status |= MxL251_Ctrl_WriteRegister(equalizerFilterPtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_FILTER_REG),
                                      regData);
  for (i=0; i<16; i++)
  {
    status |= MxL251_Ctrl_ReadRegister(equalizerFilterPtr->I2cSlaveAddr,
                                       MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_EXT_SPACE_DATA_REG),
                                       &regData);
#ifdef _MXL251_FIXEDPOINT_
    equalizerFilterPtr->FfeInfo[i] = regData;
#else
	equalizerFilterPtr->FfeInfo[i] = (REAL32)regData;
#endif
  }

  /* Read spur */
  regData = 0x0120;
  
  status |= MxL251_Ctrl_WriteRegister(equalizerFilterPtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_FILTER_REG),
                                      regData);
  for (i=0; i<32; i++)
  {
    status |= MxL251_Ctrl_ReadRegister(equalizerFilterPtr->I2cSlaveAddr,
                                       MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_EXT_SPACE_DATA_REG),
                                       &regData);
#ifdef _MXL251_FIXEDPOINT_
	equalizerFilterPtr->SpurInfo[i] = regData;
#else
    equalizerFilterPtr->SpurInfo[i] = (REAL32)regData;
#endif
  }

  /* Read Dfe */
  regData = 0x0140;
  
  status |= MxL251_Ctrl_WriteRegister(equalizerFilterPtr->I2cSlaveAddr,
                                      MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_FILTER_REG),
                                      regData);
  for (i=0; i<56; i++)
  {
    status |= MxL251_Ctrl_ReadRegister(equalizerFilterPtr->I2cSlaveAddr,
                                       MxL251_Ctrl_ConvertDemodIdToAddr(equalizerFilterPtr->DemodId, EQUALIZER_EXT_SPACE_DATA_REG),
                                       &regData);
#ifdef _MXL251_FIXEDPOINT_
	equalizerFilterPtr->DfeInfo[i] = regData;
#else
    equalizerFilterPtr->DfeInfo[i] = (REAL32)regData;
#endif
  }

  equalizerFilterPtr->DsEqDfeTapNum = 16;

  /* DsEqMainLocation, do later */

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodTimingOffset - MXL_DEMOD_TIMING_OFFSET_REQ
--| 
--| AUTHOR        : Sunghoon Park, Dong Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 07/21/2009, 07/07/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : It retrieves demodulator timing offset information.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodTimingOffset(PMXL_DEMOD_TIMINGOFFSET_INFO_T timingOffsetPtr)
{
  UINT8 status = MXL_TRUE;

  UINT8 bankCfgData = 0;
  UINT16 regData;
  SINT16 godardAcc;
  UINT32 tmpRate = 0;
  MXL_DEMOD_ANNEXQAM_INFO_T annexQamType;
#ifdef _MXL251_FIXEDPOINT_
  SINT64 temp;
#endif

  MxL_DLL_DEBUG0("MXL_DEMOD_TIMING_OFFSET_REQ - i2cAddr=0x%x, DemodId=%d\n", timingOffsetPtr->I2cSlaveAddr, timingOffsetPtr->DemodId);

  /* Readback current Annex and QAM type first */
  annexQamType.I2cSlaveAddr = timingOffsetPtr->I2cSlaveAddr;
  annexQamType.DemodId = timingOffsetPtr->DemodId;
  status = (UINT8)MxL251_GetDemodAnnexQamType(&annexQamType);

  switch(annexQamType.AnnexType)
  {
    case ANNEX_B:
      switch(annexQamType.QamType)
      {
        case QAM64:
          bankCfgData = 1;
          break;

        case QAM256:
          bankCfgData = 2;
          break;

        default:
          return MXL_FALSE;
      }
      break;

    case ANNEX_A:
      bankCfgData = 0;
      break;
  }

  /* Config bank <2:0> */
  status |= MxL251_Ctrl_ReadRegister(timingOffsetPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(timingOffsetPtr->DemodId, RESAMP_BANK_REG), &regData);
  regData = ((regData & 0xFFF8) | bankCfgData);
  status |= MxL251_Ctrl_WriteRegister(timingOffsetPtr->I2cSlaveAddr, 
   RESAMP_BANK_REG, regData);

  /* Resample readback: High<10:0>, Low<15:0> */
  status |= MxL251_Ctrl_ReadRegister(timingOffsetPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(timingOffsetPtr->DemodId, RATE_RESAMP_RATE_MID_HI_REG), 
                                     &regData);
  tmpRate = (regData & 0x07FF) << 16;
  status |= MxL251_Ctrl_ReadRegister(timingOffsetPtr->I2cSlaveAddr, 
                                     MxL251_Ctrl_ConvertDemodIdToAddr(timingOffsetPtr->DemodId, RATE_RESAMP_RATE_MID_LO_REG), 
                                     &regData);
  tmpRate = ((tmpRate & 0xFFFF0000) | regData);

  if (0 == tmpRate)
  {
    MxL_DLL_DEBUG0("%s - ERROR: RATE_RESAMP_RATE has not been programmed\n", __FUNCTION__);
    return MXL_FALSE;
  }

  /* Calculate timing offset (ppm unit) */
  status |= MxL251_Ctrl_ReadRegister(timingOffsetPtr->I2cSlaveAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(timingOffsetPtr->DemodId, GODARD_ACC_REG), 
                              (UINT16*)&godardAcc);
#ifdef _MXL251_FIXEDPOINT_
  temp = (SINT64)godardAcc * 1000000;
  temp *= (1<< MXL251_PRECISION);
  temp = MXL_DIV64_S(temp, tmpRate);
  temp = MXL_DIV64_S(temp, 2);
  //timingOffsetPtr->TimingOffset = (temp * (1<< MXL251_PRECISION)) / tmpRate / 2;
  //MxL_DLL_DEBUG0("timingOffset = %fppm\n", MXL_VAL64(timingOffsetPtr->TimingOffset));
#else
  timingOffsetPtr->TimingOffset = ((REAL64)godardAcc * 1000000.0) / (REAL64)tmpRate / 2.0;
  MxL_DLL_DEBUG0("timingOffset = %fppm\n", timingOffsetPtr->TimingOffset);
#endif

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodGloablClkPolarity - MXL_DEMOD_CLK_POLARITY_REQ
--| 
--| AUTHOR        : Richard Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 08/30/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Get current global clock polarity
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodGloablClkPolarity(PMXL_DEMOD_CLKPOLARITY_INFO_T clkPolarPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 control;
  UINT8 i2cAddr = clkPolarPtr->I2cSlaveAddr;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(clkPolarPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_DEMOD_CLK_POLARITY_REQ - i2cAddr=0x%x\n", clkPolarPtr->I2cSlaveAddr);

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // For global clock polarity, read  0x005c bit<6> and write it back 
    status |= MxL251_Ctrl_ReadRegisterMask(
        i2cAddr, 
        TP_CLK_INV_REG, 
        TP_CLK_INV_MASK, 
        &control);

    if (control) // <bit 6>
    {
      clkPolarPtr->MpegClkPol = MPEG_CLK_NEGATIVE;
    }
    else
    {
      clkPolarPtr->MpegClkPol = MPEG_CLK_POSITIVE;
    }
  }
  else
  {
    // For global clock polarity, read  0x005c bit<6> and write it back 
    status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEM_MP_CLK_INV_REG, &control);

    if (control & 0x0040) // <bit 6>
    {
      clkPolarPtr->MpegClkPol = MPEG_CLK_NEGATIVE;
    }
    else
    {
      clkPolarPtr->MpegClkPol = MPEG_CLK_POSITIVE;
    }
  }

  status |= MxL251_Ctrl_ReadRegisterMask(i2cAddr, PAD_MCLK_DRV_REG, PAD_MCLK_DRV_MASK, &control);
  clkPolarPtr->MpegClkPadDrv = (MPEG_DRV_STRENGTH_MODE_E)(control >> 8);

  MxL_DLL_DEBUG0("mpegClkPol=%d mpegClkDrv=%d\n", clkPolarPtr->MpegClkPol, clkPolarPtr->MpegClkPadDrv);

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodMpegOutIface - MXL_DEMOD_MPEG_OUT_REQ
--| 
--| AUTHOR        : Richard Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 08/30/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : Get current global clock polarity
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodMpegOutIface(PMXL_MPEG_OUT_INFO_T mpegOutParamPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 control;
  UINT8 i2cAddr = mpegOutParamPtr->I2cSlaveAddr;

  MxL_DLL_DEBUG0("MXL_DEMOD_MPEG_OUT_REQ - i2cAddr=0x%x, DemodId=%d\n", mpegOutParamPtr->I2cSlaveAddr, mpegOutParamPtr->DemodId);
  
  /* MPEG Clock Frequency */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MPEGOUT_CLK_CTRL_REG, &control);

  control &= 0x0700; // only get MPEG clock field
  mpegOutParamPtr->MpegClkFreq  = (MPEG_CLK_RATE_E)(control>>8);

  /* Set MPEG paramters according to Demod ID */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_SER_CTRL_REG), &control);
  control &= 0x000F;  // only get MPEG SERIAL control field

  /* LSB or MSB first */
  if (control & (MPEG_SERIAL_MSB_1ST << 2))
  {
    mpegOutParamPtr->LsbOrMsbFirst = MPEG_SERIAL_MSB_1ST;
  }
  else
  {
    mpegOutParamPtr->LsbOrMsbFirst = MPEG_SERIAL_LSB_1ST;
  }

  /* SYNC Pulse width */
  if (control & (MPEG_SYNC_WIDTH_BYTE << 3))
  {
    mpegOutParamPtr->MpegSyncPulseWidth = MPEG_SYNC_WIDTH_BYTE;
  }
  else
  {
    mpegOutParamPtr->MpegSyncPulseWidth = MPEG_SYNC_WIDTH_BIT;
  }

  /* If MPEG Data out format is serial, configure for phase and polarity */
  /* MPEG Data Valid polarity */
  if (control & MPEG_ACTIVE_HIGH)
  {
    mpegOutParamPtr->MpegValidPol = MPEG_ACTIVE_LOW;
  }
  else
  {
    mpegOutParamPtr->MpegValidPol = MPEG_ACTIVE_HIGH; 
  }

  /* MPEG Sync polarity */
  if (control & (MPEG_ACTIVE_HIGH << 1))
  {
    mpegOutParamPtr->MpegSyncPol = MPEG_ACTIVE_LOW;
  }
  else
  {
    mpegOutParamPtr->MpegSyncPol = MPEG_ACTIVE_HIGH;
  }
  
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(mpegOutParamPtr->DemodId, MPEGOUT_ERROR_IND_REG), &control);

  if (control & ENABLE_MPEG_ERROR_IND)
  {
    mpegOutParamPtr->MpegErrorIndication = MXL_ENABLE;
  }
  else
  {
    mpegOutParamPtr->MpegErrorIndication = MXL_DISABLE;
  }

  switch (mpegOutParamPtr->DemodId)
  {
    case DEMOD0 :
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEMOD1_MDVAL_GATE_EN_REG, &control);
      if (control & DEMOD1_MDVAL_GATE_EN_MASK)
      {
        mpegOutParamPtr->Mpeg3WireModeEnable = MXL_ENABLE;
      }
      else
      {
        mpegOutParamPtr->Mpeg3WireModeEnable = MXL_DISABLE;
      }
      break;

    case DEMOD1 :

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DEMOD2_MDVAL_GATE_EN_REG, &control);
      if (control & DEMOD2_MDVAL_GATE_EN_MASK)
      {
        mpegOutParamPtr->Mpeg3WireModeEnable = MXL_ENABLE;
      }
      else
      {
        mpegOutParamPtr->Mpeg3WireModeEnable = MXL_DISABLE;
      }
      break;

    default:
      status |= MXL_FALSE;
      MxL_DLL_ERROR0("Invalid demod id %d", mpegOutParamPtr->DemodId);
      break;
  }

  status |= MxL251_Ctrl_GetMpegPadDrv(i2cAddr, mpegOutParamPtr->DemodId , &mpegOutParamPtr->MpegPadDrv);

  MxL_DLL_DEBUG0("MXL_DEMOD_MPEG_OUT_REQ - LsbOrMsbFirst=%d, MpegValidPol=%d, MpegSyncPol=%d\n MpegSyncPulseWidth=%d, MpegClkFreq=%d, MpegErrorIndication=%d, Mpeg3WireModeEnable =%d"
                 "PAD_MPSYN_DRV = %d, PAD_MPDAT_DRV=%d PAD_MPVAL_DRV=%d\n",
                 mpegOutParamPtr->LsbOrMsbFirst,
                 mpegOutParamPtr->MpegValidPol,
                 mpegOutParamPtr->MpegSyncPol,
                 mpegOutParamPtr->MpegSyncPulseWidth,
                 mpegOutParamPtr->MpegClkFreq,
                 mpegOutParamPtr->MpegErrorIndication,
                 mpegOutParamPtr->Mpeg3WireModeEnable,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPSYN_DRV,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPDAT_DRV,
                 mpegOutParamPtr->MpegPadDrv.PAD_MPVAL_DRV);

  return (MXL_STATUS)status;
}



/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_ConfigDemodPsmInfo - MXL_DEMOD_PSM_CFG
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 01/05/2011
--|
--| DESCRIPTION   : This function configures demod PSM
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_ConfigDemodPsmInfo(PMXL_DEMOD_PSM_INFO_T paramPtr)
{
  UINT8  status = MXL_TRUE;
  MxL_DLL_DEBUG0("MXL_DEMOD_PSM_INFO_CFG - i2cAddr=0x%x, DemodId=%d, DemodEnable=%d\n", 
                  paramPtr->I2cSlaveAddr, paramPtr->DemodId, paramPtr->DemodEnable);
  
  status |= MxL251_Ctrl_SetMpegOutEnable(paramPtr->I2cSlaveAddr, paramPtr->DemodId, paramPtr->DemodEnable);
  status |= MxL251_Ctrl_ConfigDemodClockEnable(paramPtr->I2cSlaveAddr, paramPtr->DemodId, paramPtr->DemodEnable);
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodPsmInfo - MXL_DEMOD_PSM_INFO_REQ
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 01/05/2011
--|
--| DESCRIPTION   : This function returns demod PSM configuration
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetDemodPsmInfo(PMXL_DEMOD_PSM_INFO_T paramPtr)
{
  MXL_STATUS status;
  status = MxL251_Ctrl_GetDemodClockEnable(paramPtr->I2cSlaveAddr, paramPtr->DemodId, &(paramPtr->DemodEnable));

  MxL_DLL_DEBUG0("MXL_DEMOD_PSM_INFO_REQ - i2cAddr=0x%x, DemodId=%d, DemodEnable=%d\n", 
                  paramPtr->I2cSlaveAddr, paramPtr->DemodId, paramPtr->DemodEnable);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodAllLockStatus - MXL_DEMOD_ALL_LOCK_STATUS_REQ
--|
--| AUTHOR        : SidS 
--|
--| DATE CREATED  : 5/04/2011
--|
--| DESCRIPTION   : This function detects QAM, FEC, and MPEG Lock statuses of Demod.
--|                 It also checks for a false lock condition and reports retune required
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_GetDemodAllLockStatus(PMXL_DEMOD_ALL_LOCK_STATUS_T cmdPtr)
{
  UINT8  status = MXL_TRUE;
  UINT16 annexType;
  UINT16 readBack;

  cmdPtr->RetuneRequired = MXL_BOOL_FALSE; 

  // QAM
  status |= (UINT8)MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, QAM_LOCK_STATUS_REG) , &readBack);
  cmdPtr->QamLockStatus = (MXL_BOOL)(readBack & 0x0001);

  // FEC
  /* Check Annex Type and QAM TYPE  */
  status |= MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, QAM_ANNEX_TYPE_REG), &readBack); 
  annexType = readBack & ANNEX_A_TYPE;    /* Bit 10 of Reg 0x8001 gives ANNEX Type */

  status |= MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, FEC_MPEG_LOCK_REG), &readBack);

  cmdPtr->FecLockStatus = (MXL_BOOL)((readBack >> 1) & 0x0001);

  if (annexType == ANNEX_A_TYPE)
  {
    // Flip lock bit for ANNEX_A type
    cmdPtr->FecLockStatus = (MXL_LOCKED == cmdPtr->FecLockStatus)?MXL_UNLOCKED:MXL_LOCKED;
  }

  cmdPtr->MpegLockStatus = (MXL_BOOL)(readBack & 0x0001);

  /* Check Retune Required */
  if (MXL_LOCKED == cmdPtr->FecLockStatus && MXL_LOCKED == cmdPtr->MpegLockStatus)
  {
    /* Read EQU_FAGC_GAIN */
    status |= MxL251_Ctrl_WriteRegister(cmdPtr->I2cSlaveAddr,
        MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, SNR_EXT_SPACE_ADDR_REG),
        (UINT16)0x86);
    status |= MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr,
        MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, SNR_EXT_SPACE_DATA_REG),
        &readBack);
    readBack &= 0x0FFF; /* EQU_FAGC_GAIN[11:0] */

    if (readBack < 9)
    {
      cmdPtr->RetuneRequired = MXL_BOOL_TRUE;
      //cmdPtr->QamLockStatus  = MXL_UNLOCKED;
      //cmdPtr->FecLockStatus  = MXL_UNLOCKED;
      //cmdPtr->MpegLockStatus = MXL_UNLOCKED;
    }
  }

  MxL_DLL_DEBUG0("MXL_DEMOD_ALL_LOCK_STATUS_REQ - i2cAddr=0x%x, DemodId=%d, QamLockStatus:%d, FecLockStatus:%d, MpegLockStatus:%d, RetuneRequired:%d\n",
      cmdPtr->I2cSlaveAddr, cmdPtr->DemodId, cmdPtr->QamLockStatus, cmdPtr->FecLockStatus, cmdPtr->MpegLockStatus, cmdPtr->RetuneRequired);

#ifdef _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
  if ((cmdPtr->QamLockStatus) && (cmdPtr->FecLockStatus) && (cmdPtr->MpegLockStatus))
  {
    MXL_DEMOD_CARRIEROFFSET_INFO_T demodCarrierOffsetInfo;
    MXL_DEMOD_ANNEXQAM_INFO_T demodAnnexQamInfo;
    SINT32 totalOffset;
    PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(cmdPtr->I2cSlaveAddr);
    SINT32 lockRange = devContextPtr->Tuners[cmdPtr->DemodId].Demod.LockRangeInHz*3;

    /* Get the current carrier offset */
    demodCarrierOffsetInfo.I2cSlaveAddr = cmdPtr->I2cSlaveAddr;
    demodCarrierOffsetInfo.DemodId      = cmdPtr->DemodId;
    status |= MxL251_GetDemodCarrierOffset(&demodCarrierOffsetInfo);

    /* Get the annex Type */
    demodAnnexQamInfo.I2cSlaveAddr  = cmdPtr->I2cSlaveAddr;
    demodAnnexQamInfo.DemodId       = cmdPtr->DemodId;
    status |= MxL251_GetDemodAnnexQamType((PMXL_DEMOD_ANNEXQAM_INFO_T)&demodAnnexQamInfo);

    /* For AnnexB invert carrier offset */
    if (ANNEX_B == demodAnnexQamInfo.AnnexType)
    {
      demodCarrierOffsetInfo.CarrierOffset = - demodCarrierOffsetInfo.CarrierOffset;
    }

    totalOffset = demodCarrierOffsetInfo.CarrierOffset * 1000000
                + devContextPtr->Tuners[cmdPtr->DemodId].Demod.NbTunerOffsetInHz;

    if (totalOffset >= -lockRange && totalOffset < lockRange)
    {
      /* Update the value of LastLockedCarrierOffset*/
      devContextPtr->Tuners[cmdPtr->DemodId].Demod.LastLockedCarrierOffset = totalOffset;
    }

    MxL_DLL_DEBUG0("%s - DemodId=%d, CarrierOffset=%d NbTunerOffsetInHz=%d\n", 
        __FUNCTION__, 
        cmdPtr->DemodId, 
        demodCarrierOffsetInfo.CarrierOffset * 1000000,
        devContextPtr->Tuners[cmdPtr->DemodId].Demod.NbTunerOffsetInHz
        ); 
  }
#endif // _DBG_USE_LAST_LOCKED_CARRIER_OFFSET_
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDemodConstellationValue - MXL_DEMOD_CONSTELLATION_VALUES_REQ
--|
--| AUTHOR        : ChauD
--|
--| DATE CREATED  : 10/31/2014
--|
--| DESCRIPTION   : This function reads DMDx_SOFTDEC_VALUE register and returns I/Q values thru
--|                           the pass-in parameter PMXL_DEMOD_CONSTELLATION_VAL_REQ_T.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/
static MXL_STATUS MxL251_GetDemodConstellationValue(PMXL_DEMOD_CONSTELLATION_VAL_REQ_T cmdPtr)
{
  UINT8  status = MXL_TRUE;
  
  MxL_DLL_DEBUG0("%s[%d]: - I2cSlaveAddr=%d, DemodId=%d.\n", 
  	  __FUNCTION__, __LINE__, (cmdPtr ? cmdPtr->I2cSlaveAddr : 0), (cmdPtr ? cmdPtr->DemodId : 0));
  if (cmdPtr)
  {
    UINT16 softDecValueReg, regVal;
	
    softDecValueReg = MxL251_Ctrl_ConvertDemodIdToAddr(cmdPtr->DemodId, DMD0_SOFTDEC_VALUE);
    do
    {
      status = MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr, softDecValueReg, &regVal);
    } while ((status == MXL_SUCCESS) && (((regVal & 0x0400) >> 10) == 1));

    if (status == MXL_SUCCESS)
    {
      cmdPtr->iVal= (SINT16)(regVal & 0x03FF);
      status = MxL251_Ctrl_ReadRegister(cmdPtr->I2cSlaveAddr, softDecValueReg, &regVal);
      cmdPtr->qVal = (SINT16)(regVal & 0x03FF);
    }
  }
  else status = MXL_FAILED;
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetTunerLockStatus - MXL_TUNER_LOCK_STATUS_REQ
--|
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Richard Liu
--|
--| DATE CREATED  : 6/25/2009
--|                 11/10/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns Tuner, AGC Lock, and
--|                 Tuner Done status after tuning.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetTunerLockStatus(PMXL_TUNER_LOCK_STATUS_T tunerLockStatusPtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 regAddr, lock, agcLockMask;

  MxL_DLL_DEBUG0("MXL_TUNER_LOCK_STATUS_REQ - i2cAddr=0x%x, TunerId=%d\n", 
                  tunerLockStatusPtr->I2cSlaveAddr, 
                  tunerLockStatusPtr->TunerId);

  // Clear them out
  tunerLockStatusPtr->TunerDoneStatus = MXL_UNLOCKED;
  tunerLockStatusPtr->AgcLockStatus = MXL_UNLOCKED;
  tunerLockStatusPtr->TunerLockStatus = MXL_UNLOCKED;


  //if (tunerLockStatusPtr->WbOrNbTuner == MXL_WB_TUNER)
  {
    // Get register address for the specified tuner
    if (tunerLockStatusPtr->TunerId == TUNER0) 
    {
      regAddr = RF_WB_TUNER0_STATUS_REG;
      agcLockMask = RF_WB_TUNER0_AGC_LOCK;
    }
    else 
    {
      regAddr = RF_WB_TUNER1_STATUS_REG;
      agcLockMask = RF_WB_TUNER1_AGC_LOCK;
    }

    // Check WB Tuner lock status
    status = (UINT8)MxL251_Ctrl_ReadRegister(tunerLockStatusPtr->I2cSlaveAddr, regAddr, &lock);

    if (lock & RF_WB_SYN_LOCK) tunerLockStatusPtr->TunerLockStatus = MXL_LOCKED;
  
    // Check AGC Lock status of WB tuner
    status |= MxL251_Ctrl_ReadRegister(tunerLockStatusPtr->I2cSlaveAddr, RF_WB_TUNER_AGC_LOCK_STATUS_REG, &lock);
    
    if (lock & agcLockMask) tunerLockStatusPtr->AgcLockStatus = MXL_LOCKED;

    if ((tunerLockStatusPtr->TunerLockStatus == MXL_LOCKED) &&
        (tunerLockStatusPtr->AgcLockStatus == MXL_LOCKED))
    {
      tunerLockStatusPtr->TunerDoneStatus = MXL_LOCKED;
    }
  }
#if 0
  else
  {

    // NB channel status
    regAddr = DFE_CHAN0_DFEAGC_STATE_REG + ((tunerLockStatusPtr->TunerId+1) << 1);
    status = (UINT8)MxL251_Ctrl_ReadRegister(tunerLockStatusPtr->I2cSlaveAddr, regAddr, &lock);
    
    if ((status == MXL_TRUE) && ((lock & DFE_AGC_LOCK) == DFE_AGC_LOCK))
    {
      tunerLockStatusPtr->TunerDoneStatus = MXL_LOCKED;
      tunerLockStatusPtr->AgcLockStatus = MXL_LOCKED;
      tunerLockStatusPtr->TunerLockStatus = MXL_LOCKED;
    }
  }
#endif
  MxL_DLL_DEBUG0("TunerLock=%d, AgcLock=%d, TunerDone=%d\n", tunerLockStatusPtr->TunerLockStatus, tunerLockStatusPtr->AgcLockStatus, tunerLockStatusPtr->TunerDoneStatus);
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetTunerCurrSettings - MXL_TUNER_CURR_SETTING_REQ
--|
--| AUTHOR        : Dong Liu
--|                 Richard Liu
--|                 Richard Liu
--|
--| DATE CREATED  : 05/10/2010
--|                 09/01/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : This function returns the current wide and narrow band channel
--|                 setting for a certain tuner 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetTunerCurrSettings(PMXL_TUNER_SETTINGS_T tunerCurrSetPtr)
{
  UINT8 status = MXL_TRUE;
  MXL_TUNER_ID_E tunerId;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(tunerCurrSetPtr->I2cSlaveAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_CURR_SETTING_REQ - i2cAddr=0x%x, TunerId=%d\n", tunerCurrSetPtr->I2cSlaveAddr, tunerCurrSetPtr->TunerId);
  tunerId = tunerCurrSetPtr->TunerId;

  if (tunerId > MAX_NUM_TUNER)
  {
    MxL_DLL_DEBUG0("Exceed MAX_NUM_TUNER(tunerId=%d Max=%d)\n", tunerId, MAX_NUM_TUNER);
    return MXL_FALSE;
  }

  tunerCurrSetPtr->CenterFrequencyInHz = devContextPtr->Tuners[tunerId].NbChanFreqInHz;
  tunerCurrSetPtr->BandwidthInMHz      = devContextPtr->Tuners[tunerId].BandWidthInMHz;
  tunerCurrSetPtr->TunerPowerMode      = devContextPtr->Tuners[tunerId].TunerPowerMode;

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetTunerRxPower - MXL_TUNER_RF_RX_PWR_REQ
--|
--| AUTHOR        : Brenndon Lee
--|                 Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 2/4/2015
--|
--| DESCRIPTION   : This function returns RF input power in dBm.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetTunerRxPower(PMXL_TUNER_RX_PWR_T tunerRxPwrPtr)
{
 UINT8  status = MXL_TRUE;  
#ifdef _MXL251_FIXEDPOINT_
  SINT32 oriPwrIndBmV, PwrIndBmV = 0;
#else 
  REAL32 oriPwrIndBmV,PwrIndBmV; 
#endif 
  status = MxL251_PwrMeasureRxPower(
        tunerRxPwrPtr->I2cSlaveAddr, 
        MxL251_Ctrl_GetDemodChanId(tunerRxPwrPtr->TunerId), 
        &oriPwrIndBmV, 
        POWER_CAL_ENABLE_COMP,
        MXL_DISABLE/*powerMonEnabled*/);

  MxL_DLL_DEBUG0("MxL251_GetTunerRxPower: Symbol_Type = %d \n",tunerRxPwrPtr->SymbolType);

  if (tunerRxPwrPtr->SymbolType == SYM_TYPE_OOB)
  {
      //status |= MxL251_CalOobRxPower(tunerRxPwrPtr->I2cSlaveAddr,MXL_DEMOD_ID_E(tunerRxPwrPtr->TunerId),oriPwrIndBmV, &PwrIndBmV);
#ifdef _MXL251_FIXEDPOINT_
     MxL_DLL_DEBUG0(" Original RX power = %d dBmV, compensated RX power =  %d dBmV\n", oriPwrIndBmV, PwrIndBmV);
#else 
    MxL_DLL_DEBUG0(" Original RX power = %f dBmV, compensated RX power =  %f dBmV \n", oriPwrIndBmV, PwrIndBmV);
#endif 
  }
  else 
	PwrIndBmV = oriPwrIndBmV; // No extra process 
  
  tunerRxPwrPtr->RxPwrIndBmV = PwrIndBmV;
#ifdef _MXL251_FIXEDPOINT_
  //MxL_DLL_DEBUG0("Status (%d), Symbol_Type = %d, RxPwrIndBmV={%d}\n",status, tunerRxPwrPtr->SymbolType, MXL_VAL64(tunerRxPwrPtr->RxPwrIndBmV));
#else
  MxL_DLL_DEBUG0("Status (%d), Symbol_Type = %d, RxPwrIndBmV={%f}\n",status, tunerRxPwrPtr->SymbolType, tunerRxPwrPtr->RxPwrIndBmV);
#endif

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetTunerMonitorRxPower - MXL_TUNER_MONITOR_RX_PWR_REQ
--|
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 04/11/2011
--|
--| DESCRIPTION   : This function returns up-to-date RF input power in dBm without retune
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

static MXL_STATUS MxL251_GetTunerMonitorRxPower(PMXL_TUNER_MONITOR_RX_PWR_REQ_T cmdPtr)
{
  MxL_DLL_DEBUG0("MXL_TUNER_MONITOR_RX_PWR_REQ - i2cAddr=0x%x, TunerId=%d\n", cmdPtr->I2cSlaveAddr, cmdPtr->TunerId);

  if (MXL_TRUE != MxL251_PwrMeasureRxPower(
        cmdPtr->I2cSlaveAddr, 
        MxL251_Ctrl_GetDemodChanId(cmdPtr->TunerId), 
        &(cmdPtr->RxPwrIndBmV), 
        POWER_CAL_ENABLE_COMP,
        MXL_ENABLE/*powerMonEnabled*/))
  {
    return MXL_FALSE;
  }
#ifdef _MXL251_FIXEDPOINT_
  //MxL_DLL_DEBUG0("RxPwrIndBmV={%f}\n", MXL_VAL64(cmdPtr->RxPwrIndBmV));
#else
  MxL_DLL_DEBUG0("RxPwrIndBmV=%f\n", cmdPtr->RxPwrIndBmV);
#endif
  return MXL_TRUE;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_ConfigDevice 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Dong Liu
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|                 05/10/2010 
--|                 12/21/2010
--|
--| DESCRIPTION   : The general device configuration shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigDevice(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else // _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigDevice(MXL_COMMAND_T *commandPtr)
#endif // _LEGACY_API_INTERFACE_
{
  MXL_STATUS status = MXL_TRUE;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_ConfigDevice - %d\n", cmdType);

  switch (cmdType)
  {
    case MXL_DEV_DEVICE_RESET_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDeviceReset((PMXL_DEV_RESET_T)paramPtr);
#else
      status = MxL251_ConfigDeviceReset(&(commandPtr->cmdDevDeviceResetCfg));
#endif
      break;

    case MXL_DEV_XTAL_SETTINGS_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDevXtalSettings((PMXL_XTAL_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDevXtalSettings(&(commandPtr->cmdDevXtalSettingsCfg));
#endif
      break;

    case MXL_DEV_FIRMWARE_DOWNLOAD_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigFwDownload((PMXL_FW_INFO_T)paramPtr);
#else
      status = MxL251_ConfigFwDownload(&(commandPtr->cmdDevFirmwareDownloadCfg));
#endif
      break;

    case MXL_DEV_POWER_MODE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDevPowerMode((PMXL_PWR_MODE_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDevPowerMode(&(commandPtr->cmdDevPowerModeCfg));
#endif
      break;

    case MXL_DEV_OVERWRITE_DEFAULT_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDevOverwriteDefault((PMXL_OVERWRITE_DEFAULT_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDevOverwriteDefault(&(commandPtr->cmdDevOverwriteDefaultCfg));
#endif
      break;

    case MXL_DEV_PSM_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDevPSM((PMXL_DEV_PSM_INFO_T)paramPtr);
#else
      status = MxL251_ConfigDevPSM(&(commandPtr->cmdDevPsmCfg));
#endif
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);

  return status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_GetDeviceStatus 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Dong Liu
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|                 05/10/2010 
--|                 12/21/2010
--|
--| DESCRIPTION   : The general device inquiries shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_GetDeviceStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else
MXL_STATUS MxLWare251SF_API_GetDeviceStatus(MXL_COMMAND_T *commandPtr)
#endif
{
  MXL_STATUS status = MXL_TRUE;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_GetDeviceStatus - %d\n", cmdType);

  switch (cmdType)
  {
    case MXL_DEV_VERSION_INFO_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDeviceVersionInfo((PMXL_DEV_VERSION_INFO_T)paramPtr);
#else
      status = MxL251_GetDeviceVersionInfo(&(commandPtr->cmdDevVersionInfoReq));
#endif
      break;

    case MXL_DEV_PSM_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDevicePSMInfo((PMXL_DEV_PSM_INFO_T)paramPtr);
#else
      status = MxL251_GetDevicePSMInfo(&(commandPtr->cmdDevPsmReq));
#endif
      break;

    case MXL_DEV_POWER_MODE_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDevicePowerModeInfo((PMXL_PWR_MODE_CFG_T)paramPtr);
#else
      status = MxL251_GetDevicePowerModeInfo(&(commandPtr->cmdDevPowerModeReq));
#endif
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_ConfigDemod 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : The demod block specific configuration shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigDemod(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else
MXL_STATUS MxLWare251SF_API_ConfigDemod(MXL_COMMAND_T *commandPtr)
#endif
{
  MXL_STATUS status = MXL_TRUE;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_ConfigDemod - %d\n", cmdType);

  switch (cmdType)
  {
    case MXL_DEMOD_SYMBOL_RATE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodSymbolRate((PMXL_SYMBOL_RATE_T)paramPtr);
#else
      status = MxL251_ConfigDemodSymbolRate(&(commandPtr->cmdDemodSymbolRateCfg));
#endif
      break;
      
    case MXL_DEMOD_MPEG_OUT_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodMpegOutIface((PMXL_MPEG_OUT_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodMpegOutIface(&(commandPtr->cmdDemodMpegOutCfg));
#endif
      break;

    case MXL_DEMOD_CLK_POLARITY_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MXL251_ConfigDemodeGlobalClkPolarity((PMXL_CLK_POLARITY_CFG_T)paramPtr);
#else
      status = MXL251_ConfigDemodeGlobalClkPolarity(&(commandPtr->cmdDemodClkPolarityCfg));
#endif
      break;

    case MXL_DEMOD_ANNEX_QAM_TYPE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodAnnexQamType((PMXL_ANNEX_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodAnnexQamType(&(commandPtr->cmdDemodAnnexQamTypeCfg));
#endif
      break;

    case MXL_DEMOD_INTR_MASK_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodInterrupt((PMXL_INTR_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodInterrupt(&(commandPtr->cmdDemodIntrMaskCfg));
#endif
      break;

    case MXL_DEMOD_INTR_CLEAR_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ClearDemodInterrupt((PMXL_INTR_CLEAR_T)paramPtr);
#else
      status = MxL251_ClearDemodInterrupt(&(commandPtr->cmdDemodIntrClearCfg));
#endif
      break;

    case MXL_DEMOD_RESET_STAT_COUNTER_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ResetDemodStatCounters((PMXL_RESET_COUNTER_T)paramPtr);
#else
      status = MxL251_ResetDemodStatCounters(&(commandPtr->cmdDemodResetStatCounterCfg));
#endif
      break;

    case MXL_DEMOD_ADC_IQ_FLIP_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodAdcIqFlip((PMXL_ADCIQFLIP_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodAdcIqFlip(&(commandPtr->cmdDemodAdcIqFlipCfg));
#endif
      break;

    case MXL_DEMOD_EQUALIZER_FILTER_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodEqualizerSetting((PMXL_EQUALIZER_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodEqualizerSetting(&(commandPtr->cmdDemodEqualizerFilterCfg));
#endif
      break;

    case MXL_DEMOD_PSM_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodPsmInfo((PMXL_DEMOD_PSM_INFO_T)paramPtr);
#else
      status = MxL251_ConfigDemodPsmInfo(&(commandPtr->cmdDemodPsmCfg));
#endif
      break;

    case MXL_DEMOD_RESTART_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodRestart((PMXL_DEMOD_RESTART_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodRestart(&(commandPtr->cmdDemodRestartCfg));
#endif
      break;
 
    case MXL_DEMOD_INVERT_SPECTRUM_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigDemodInvertSpecrum((PMXL_DEMOD_INVERT_SPECTRUM_CFG_T)paramPtr);
#else
      status = MxL251_ConfigDemodInvertSpecrum(&(commandPtr->cmdDemodInvertSpectrumCfg));
#endif
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_GetDemodStatus 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : The demod specific inquiries shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_GetDemodStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else
MXL_STATUS MxLWare251SF_API_GetDemodStatus(MXL_COMMAND_T *commandPtr)
#endif
{
  MXL_STATUS status = MXL_TRUE;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_GetDemodStatus - %d\n", cmdType);

  switch (cmdType)
  {
    case MXL_DEMOD_ANNEX_QAM_TYPE_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodAnnexQamType((PMXL_DEMOD_ANNEXQAM_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodAnnexQamType(&(commandPtr->cmdDemodAnnexQamTypeReq));
#endif
      break;

    case MXL_DEMOD_INTR_STATUS_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodInterruptStatus((PMXL_INTR_STATUS_T)paramPtr);
#else
      status = MxL251_GetDemodInterruptStatus(&(commandPtr->cmdDemodIntrStatusReq));
#endif
      break;

    case MXL_DEMOD_FEC_LOCK_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodLockStatus(cmdType,  (PMXL_DEMOD_LOCK_STATUS_T)paramPtr);
#else
      status = MxL251_GetDemodLockStatus(cmdType, &(commandPtr->cmdDemodFecLockReq));
#endif
      break;

    case MXL_DEMOD_MPEG_LOCK_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodLockStatus(cmdType,  (PMXL_DEMOD_LOCK_STATUS_T)paramPtr);
#else
      status = MxL251_GetDemodLockStatus(cmdType, &(commandPtr->cmdDemodMpegLockReq));
#endif
      break;

    case MXL_DEMOD_QAM_LOCK_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodLockStatus(cmdType,  (PMXL_DEMOD_LOCK_STATUS_T)paramPtr);
#else
      status = MxL251_GetDemodLockStatus(cmdType, &(commandPtr->cmdDemodQamLockReq));
#endif
      break;

    case MXL_DEMOD_ALL_LOCK_STATUS_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodAllLockStatus((PMXL_DEMOD_ALL_LOCK_STATUS_T)paramPtr);
#else
      status = MxL251_GetDemodAllLockStatus(&(commandPtr->cmdDemodAllLockStatusReq));
#endif
      break;

    case MXL_DEMOD_SNR_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodSnr((PMXL_DEMOD_SNR_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodSnr(&(commandPtr->cmdDemodSnrReq));
#endif
      break;

    case MXL_DEMOD_BER_UNCODED_BER_CER_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodBer((PMXL_DEMOD_BER_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodBer(&(commandPtr->cmdDemodBerUncodedBerCerReq));
#endif
      break;

    case MXL_DEMOD_STAT_COUNTERS_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodStatisticCounters((PMXL_DEMOD_STAT_COUNT_T)paramPtr);
#else
      status = MxL251_GetDemodStatisticCounters(&(commandPtr->cmdDemodStatCountersReq));
#endif
      break;

    case MXL_DEMOD_CARRIER_OFFSET_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodCarrierOffset((PMXL_DEMOD_CARRIEROFFSET_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodCarrierOffset(&(commandPtr->cmdDemodCarrierOffsetReq));
#endif
      break;

    case MXL_DEMOD_EQUALIZER_FILTER_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodEqualizerFilter((PMXL_DEMOD_EQUALFILTER_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodEqualizerFilter(&(commandPtr->cmdDemodEqualizerFilterReq));
#endif
      break;

    case MXL_DEMOD_INTERLEAVER_DEPTH_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodInterleaverDepth((PMXL_INTERDEPTH_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodInterleaverDepth(&(commandPtr->cmdDemodInterleaverDepthReq));
#endif
      break;

    case MXL_DEMOD_TIMING_OFFSET_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodTimingOffset((PMXL_DEMOD_TIMINGOFFSET_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodTimingOffset(&(commandPtr->cmdDemodTimingOffsetReq));
#endif
      break;

    case MXL_DEMOD_CLK_POLARITY_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodGloablClkPolarity((PMXL_DEMOD_CLKPOLARITY_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodGloablClkPolarity(&(commandPtr->cmdDemodClkPolarityReq));
#endif
      break;

    case MXL_DEMOD_MPEG_OUT_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodMpegOutIface((PMXL_MPEG_OUT_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodMpegOutIface(&(commandPtr->cmdDemodMpegOutReq));
#endif
      break;

    case MXL_DEMOD_PSM_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodPsmInfo((PMXL_DEMOD_PSM_INFO_T)paramPtr);
#else
      status = MxL251_GetDemodPsmInfo(&(commandPtr->cmdDemodPsmReq));
#endif
      break;


    case MXL_DEMOD_CONSTELLATION_VALUES_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDemodConstellationValue((PMXL_DEMOD_CONSTELLATION_VAL_REQ_T)paramPtr);
#else
      status = MxL251_GetDemodConstellationValue(&(commandPtr->cmdDemodConstellValReq));
#endif
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_ConfigTuner 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Dong Liu 
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|               : 05/10/2010
--|                 12/21/2010
--|
--| DESCRIPTION   : The tuner block specific configuration shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_ConfigTuner(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else
MXL_STATUS MxLWare251SF_API_ConfigTuner(MXL_COMMAND_T *commandPtr)
#endif
{
  MXL_STATUS status = MXL_TRUE;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_ConfigTuner : CmdType =%d\n", cmdType);
  
  switch (cmdType)
  {
    case MXL_TUNER_CREATE_RX_PWR_CAL_COEF_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigTunerCreatePwrCalCoef((PMXL_RX_PWR_CAL_T)paramPtr);
#else
      status = MxL251_ConfigTunerCreatePwrCalCoef(&(commandPtr->cmdTunerCreateRxPwrCalCoefCfg));
#endif
      break;

    case MXL_TUNER_CAL_DONE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = Mxl251_ConfigTunerCalDone((PMXL_RX_PWR_CAL_COEF_INFO_T)paramPtr);
#else
      status = Mxl251_ConfigTunerCalDone(&(commandPtr->cmdTunerCalDoneCfg));
#endif
      break;

    case MXL_TUNER_DOWNLOAD_CAL_COEF_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MXL251_ConfigTunerDownLoadCalCoef((PMXL_CAL_COEF_INFO_T)paramPtr);
#else
      status = MXL251_ConfigTunerDownLoadCalCoef(&(commandPtr->cmdTunerDownloadCalCoefCfg));
#endif
      break;

    case MXL_TUNER_CHAN_TUNE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigTunerChanTune((PMXL_TUNER_CHAN_TUNE_CFG_T)paramPtr);
#else
      status = MxL251_ConfigTunerChanTune(&(commandPtr->cmdTunerChanTuneCfg));
#endif
      break;

    case MXL_TUNER_AGC_LOCK_SPEED_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigTunerAgcLockSpeed((PMXL_AGC_CTRL_SPEED_T)paramPtr);
#else
      status = MxL251_ConfigTunerAgcLockSpeed(&(commandPtr->cmdTunerAgcLockSpeedCfg));
#endif
      break;

    case MXL_TUNER_CAL_CUTOFF_FREQ_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_Ctrl_ConfigTunerCalCutOffFreq((PMXL_TUNER_CAL_SET_CUTOFF_FREQ_CFG_T)paramPtr);
#else
      status = MxL251_Ctrl_ConfigTunerCalCutOffFreq(&(commandPtr->cmdTunerCalCutoffFreqCfg));
#endif
      break;      

#ifdef _TUNER_TEST_API_ENABLED_
    case MXL_TUNER_TEST_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigTunerTest((PMXL_TUNER_TEST_CFG_T)paramPtr);
#else
      status = MxL251_ConfigTunerTest(&(commandPtr->cmdTunerTestCfg));
#endif
      break;
#endif // _TUNER_TEST_API_ENABLED_

    case MXL_TUNER_ENHANCED_CHAN_TUNE_CFG:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_ConfigTunerEnhancedChanTune((PMXL_TUNER_ENHANCED_CHAN_TUNE_CFG_T)paramPtr);
#else
      status = MxL251_ConfigTunerEnhancedChanTune(&(commandPtr->cmdTunerEnhancedChanTuneCfg));
#endif
      break;      

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);

  return status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare251SF_API_GetTunerStatus 
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|                 Chien-Chen
--|
--| DATE CREATED  : 6/19/2009
--|                 12/21/2010
--|
--| DESCRIPTION   : The tuner specific inquiries shall be handled 
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

#ifdef _LEGACY_API_INTERFACE_
MXL_STATUS MxLWare251SF_API_GetTunerStatus(MXL_CMD_TYPE_E cmdType, void *paramPtr)
#else
MXL_STATUS MxLWare251SF_API_GetTunerStatus(MXL_COMMAND_T *commandPtr)
#endif
{
  MXL_STATUS status;

#ifndef _LEGACY_API_INTERFACE_
  MXL_CMD_TYPE_E cmdType = commandPtr->commandId;
#endif // _LEGACY_API_INTERFACE_

  MxL_DLL_DEBUG0("MxLWare251SF_API_GetTunerStatus : CmdType =%d\n", cmdType);
  
  switch (cmdType)
  {
    case MXL_TUNER_LOCK_STATUS_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetTunerLockStatus((PMXL_TUNER_LOCK_STATUS_T)paramPtr);
#else
      status = MxL251_GetTunerLockStatus(&(commandPtr->cmdTunerLockStatusReq));
#endif
      break;

    case MXL_TUNER_RF_RX_PWR_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetTunerRxPower((PMXL_TUNER_RX_PWR_T)paramPtr);
#else
      status = MxL251_GetTunerRxPower(&(commandPtr->cmdTunerRfRxPwrReq));
#endif
	  // debug aim !   
	  MxL_DLL_DEBUG0("MxL251_GetTunerRxPower: RX power = %d \n",commandPtr->cmdTunerRfRxPwrReq.RxPwrIndBmV);
      break;

    case MXL_TUNER_CURR_SETTING_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetTunerCurrSettings((PMXL_TUNER_SETTINGS_T)paramPtr);
#else
      status = MxL251_GetTunerCurrSettings(&(commandPtr->cmdTunerCurrSettingReq));
#endif
      break;

    case MXL_TUNER_DSCAL_INFO_REQ:
#ifdef _FAST_SCAN_TEST_ENABLED_
      status = test_scan(((PMXL_GET_DSCAL_INFO_T)paramPtr)->I2cSlaveAddr);
#else // _FAST_SCAN_TEST_ENABLED_
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetDSCALInfo((PMXL_GET_DSCAL_INFO_T)paramPtr);
#else
      status = MxL251_GetDSCALInfo(&(commandPtr->cmdTunerDscalInfoReq));
#endif
#endif // _FAST_SCAN_TEST_ENABLED_
      break;

    case MXL_TUNER_MONITOR_RX_PWR_REQ:
#ifdef _LEGACY_API_INTERFACE_
      status = MxL251_GetTunerMonitorRxPower((PMXL_TUNER_MONITOR_RX_PWR_REQ_T)paramPtr);
#else
      status = MxL251_GetTunerMonitorRxPower(&(commandPtr->cmdTunerMonitorRxPwrReq));
#endif
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  MxL_DLL_DEBUG0("DONE(%d)\n", status);
  return status;
}

