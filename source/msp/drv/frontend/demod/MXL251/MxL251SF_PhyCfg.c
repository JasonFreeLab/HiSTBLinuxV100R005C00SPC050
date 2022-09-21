/*****************************************************************************************
 *
 * FILE NAME          : MxL251SF_PhyCfg.c
 * 
 * AUTHOR             : Brenndon Lee
 *                      Dong Liu
 *                      Sunghoon Park
 *                      Richard Liu
 *                      Jun Huang
 *                      Randhir Jha
 *
 * DATE CREATED       : 5/18/2009
 *                      5/14/2010
 *                      7/06/2010
 *                      12/24/2010
 *                      06/18/2011
 *                      03/18/2011
 *
 * DESCRIPTION        : This file contains demod and RF control parameters.
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

#include "MxL251SF_PhyCfg.h"

// Assure MxL251Dev[] is zero initialized
MXL251SF_DEV_CONTEXT_T MxL251Dev[MAX_251SF_DEVICES] = {{0}};

#ifndef _MXL251_BUILD_
UINT16 DAGCBottomSetPt = 10*16;
#endif // _MXL251_BUILD_

REG_CTRL_INFO_T MxL_OobAciMfCoef[] =
{
  {0x8110, 0x001F, 0x0000},  /* ACI_COEF_ADDR */
  {0x8118, 0x003F, 0x0000},  /* MF_COEF_ADDR */
  {0x8110, 0x8000, 0x8000},  /* ACI_AUTO_INC */
  {0x8118, 0x8000, 0x8000},  /* MF_AUTO_INC */
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL_OobAciMfCoef_0_772MHz[] =     
{
  {0x8114, 0xFFFF, 0x0004}, /* ACI_COEF_DATA */
  {0x8114, 0xFFFF, 0x0009}, 
  {0x8114, 0xFFFF, 0x000d}, 
  {0x8114, 0xFFFF, 0x000f}, 
  {0x8114, 0xFFFF, 0x000d}, 
  {0x8114, 0xFFFF, 0x0005}, 
  {0x8114, 0xFFFF, 0x1ff5}, 
  {0x8114, 0xFFFF, 0x1fe0}, 
  {0x8114, 0xFFFF, 0x1fca}, 
  {0x8114, 0xFFFF, 0x1fb8}, 
  {0x8114, 0xFFFF, 0x1fb3}, 
  {0x8114, 0xFFFF, 0x1fc1}, 
  {0x8114, 0xFFFF, 0x1fe8}, 
  {0x8114, 0xFFFF, 0x002b}, 
  {0x8114, 0xFFFF, 0x0085}, 
  {0x8114, 0xFFFF, 0x00f0}, 
  {0x8114, 0xFFFF, 0x0160}, 
  {0x8114, 0xFFFF, 0x01c5}, 
  {0x8114, 0xFFFF, 0x0212}, 
  {0x8114, 0xFFFF, 0x023c}, 

  {0x811C, 0xFFFF, 0x0000}, /* MF_COEF_DATA */
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},  
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x01ff},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x0008},
  {0x811C, 0xFFFF, 0x03f3},
  {0x811C, 0xFFFF, 0x03f1},
  {0x811C, 0xFFFF, 0x001e},
  {0x811C, 0xFFFF, 0x0015},
  {0x811C, 0xFFFF, 0x03ca},
  {0x811C, 0xFFFF, 0x03ea},
  {0x811C, 0xFFFF, 0x004f},
  {0x811C, 0xFFFF, 0x0013},
  {0x811C, 0xFFFF, 0x039d},
  {0x811C, 0xFFFF, 0x03f7},
  {0x811C, 0xFFFF, 0x006b},
  {0x811C, 0xFFFF, 0x03f9},
  {0x811C, 0xFFFF, 0x03a0},
  {0x811C, 0xFFFF, 0x001e},
  {0x811C, 0xFFFF, 0x003e},
  {0x811C, 0xFFFF, 0x1fca},
  {0x811C, 0xFFFF, 0x1ffc},
  {0x811C, 0xFFFF, 0x0045},
  {0x811C, 0xFFFF, 0x1fbb},
  {0x811C, 0xFFFF, 0x1fc3},
  {0x811C, 0xFFFF, 0x0086},
  {0x811C, 0xFFFF, 0x0016},
  {0x811C, 0xFFFF, 0x1f5a},
  {0x811C, 0xFFFF, 0x0030},
  {0x811C, 0xFFFF, 0x006c},
  {0x811C, 0xFFFF, 0x1f6e},
  {0x811C, 0xFFFF, 0x004e},
  {0x811C, 0xFFFF, 0x00f4},
  {0x811C, 0xFFFF, 0x1df8},
  {0x811C, 0xFFFF, 0x1ec3},
  {0x811C, 0xFFFF, 0x08f2},
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL_OobAciMfCoef_1_024MHz[] =     
{
  {0x8114, 0xFFFF, 0x1ff3}, /* ACI_COEF_DATA */ 
  {0x8114, 0xFFFF, 0x1ff5}, 
  {0x8114, 0xFFFF, 0x1ffd}, 
  {0x8114, 0xFFFF, 0x000b}, 
  {0x8114, 0xFFFF, 0x001a}, 
  {0x8114, 0xFFFF, 0x0025}, 
  {0x8114, 0xFFFF, 0x0026}, 
  {0x8114, 0xFFFF, 0x0017}, 
  {0x8114, 0xFFFF, 0x1ff8}, 
  {0x8114, 0xFFFF, 0x1fcf}, 
  {0x8114, 0xFFFF, 0x1fa6}, 
  {0x8114, 0xFFFF, 0x1f8e}, 
  {0x8114, 0xFFFF, 0x1f95}, 
  {0x8114, 0xFFFF, 0x1fc9}, 
  {0x8114, 0xFFFF, 0x002b}, 
  {0x8114, 0xFFFF, 0x00b5}, 
  {0x8114, 0xFFFF, 0x0154}, 
  {0x8114, 0xFFFF, 0x01ef}, 
  {0x8114, 0xFFFF, 0x026a}, 
  {0x8114, 0xFFFF, 0x02ae}, 
  
  {0x811C, 0xFFFF, 0x0000}, /* MF_COEF_DATA */
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0001},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x03ff},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x03fe},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x03ff},
  {0x811C, 0xFFFF, 0x03fe},
  {0x811C, 0xFFFF, 0x03ff},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x0001},
  {0x811C, 0xFFFF, 0x03fd},
  {0x811C, 0xFFFF, 0x03ff},
  {0x811C, 0xFFFF, 0x0007},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x1ff4},
  {0x811C, 0xFFFF, 0x1ffb},
  {0x811C, 0xFFFF, 0x0015},
  {0x811C, 0xFFFF, 0x000b},
  {0x811C, 0xFFFF, 0x1fd1},
  {0x811C, 0xFFFF, 0x1fe9},
  {0x811C, 0xFFFF, 0x0068},
  {0x811C, 0xFFFF, 0x0032},
  {0x811C, 0xFFFF, 0x1f2e},
  {0x811C, 0xFFFF, 0x1f97},
  {0x811C, 0xFFFF, 0x018a},
  {0x811C, 0xFFFF, 0x00b8},
  {0x811C, 0xFFFF, 0x1d07},
  {0x811C, 0xFFFF, 0x1efb},
  {0x811C, 0xFFFF, 0x0968},
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL_OobAciMfCoef_1_544MHz[] =     
{
  {0x8114, 0xFFFF, 0x0002}, /* ACI_COEF_DATA */
  {0x8114, 0xFFFF, 0x0003},
  {0x8114, 0xFFFF, 0x0003},
  {0x8114, 0xFFFF, 0x1ffe},
  {0x8114, 0xFFFF, 0x1ff5},
  {0x8114, 0xFFFF, 0x1fef},
  {0x8114, 0xFFFF, 0x1ff3},
  {0x8114, 0xFFFF, 0x0005},
  {0x8114, 0xFFFF, 0x0022},
  {0x8114, 0xFFFF, 0x0038},
  {0x8114, 0xFFFF, 0x0031},
  {0x8114, 0xFFFF, 0x0000},
  {0x8114, 0xFFFF, 0x1fb1},
  {0x8114, 0xFFFF, 0x1f6b},
  {0x8114, 0xFFFF, 0x1f67},
  {0x8114, 0xFFFF, 0x1fd3},
  {0x8114, 0xFFFF, 0x00b5},
  {0x8114, 0xFFFF, 0x01e1},
  {0x8114, 0xFFFF, 0x02fe},
  {0x8114, 0xFFFF, 0x03ab},
                         
  {0x811C, 0xFFFF, 0x0000}, /* MF_COEF_DATA */
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x0000},
  {0x811C, 0xFFFF, 0x01ff},
  {0x811C, 0xFFFF, 0x0002},
  {0x811C, 0xFFFF, 0x0008},
  {0x811C, 0xFFFF, 0x03f3},
  {0x811C, 0xFFFF, 0x03f1},
  {0x811C, 0xFFFF, 0x001e},
  {0x811C, 0xFFFF, 0x0015},
  {0x811C, 0xFFFF, 0x03ca},
  {0x811C, 0xFFFF, 0x03ea},
  {0x811C, 0xFFFF, 0x004f},
  {0x811C, 0xFFFF, 0x0013},
  {0x811C, 0xFFFF, 0x039d},
  {0x811C, 0xFFFF, 0x03f7},
  {0x811C, 0xFFFF, 0x006b},
  {0x811C, 0xFFFF, 0x03f9},
  {0x811C, 0xFFFF, 0x03a0},
  {0x811C, 0xFFFF, 0x001e},
  {0x811C, 0xFFFF, 0x003e},
  {0x811C, 0xFFFF, 0x1fca},
  {0x811C, 0xFFFF, 0x1ffc},
  {0x811C, 0xFFFF, 0x0045},
  {0x811C, 0xFFFF, 0x1fbb},
  {0x811C, 0xFFFF, 0x1fc3},
  {0x811C, 0xFFFF, 0x0086},
  {0x811C, 0xFFFF, 0x0016},
  {0x811C, 0xFFFF, 0x1f5a},
  {0x811C, 0xFFFF, 0x0030},
  {0x811C, 0xFFFF, 0x006c},
  {0x811C, 0xFFFF, 0x1f6e},
  {0x811C, 0xFFFF, 0x004e},
  {0x811C, 0xFFFF, 0x00f4},
  {0x811C, 0xFFFF, 0x1df8},
  {0x811C, 0xFFFF, 0x1ec3},
  {0x811C, 0xFFFF, 0x08f2},
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL251_DemodEqualizerSpeedUp[] = 
{
  {0x8084, 0xFFFF, 0xD566},
  {0x8140, 0xFFFF, 0x083A},
  {0x80A0, 0xFFFF, 0x8508},
  {0x80D4, 0xFFFF, 0x4179},
  {0,    0,    0}
};

#ifdef _OOB_SUPPORT_ENABLED_
REG_CTRL_INFO_T MxL251_DemodEqualizerSpeedUpOob_0_772MHz[] = 
{
  {0x8084, 0xFFFF, 0xD5F9},
  {0x8140, 0xFFFF, 0x083A},
  {0x80A0, 0xFFFF, 0x8508},
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL251_DemodEqualizerSpeedUpOob_1_024MHz[] = 
{
  {0x8084, 0xFFFF, 0xD5FA},
  {0x8140, 0xFFFF, 0x083A},
  {0x80A0, 0xFFFF, 0x8508},
  {0,    0,    0}
};

REG_CTRL_INFO_T MxL251_DemodEqualizerSpeedUpOob_1_544MHz[] = 
{
  {0x8084, 0xFFFF, 0xD5F9},
  {0x8140, 0xFFFF, 0x083A},
  {0x80A0, 0xFFFF, 0x8508},
  {0,    0,    0}
};
#endif // _OOB_SUPPORT_ENABLED_

/* For Demodule Coefficients Setting */
UINT16 MxL251_MatchedFilterCoef_AnnexB256[48] =
{
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x01FB,  0x0005,  0x0002,  0x03FF,
  0x03F4,  0x000B,  0x0008,  0x03FB,  0x03E6,  0x0018,  0x0011,  0x03F2,  0x03D3,
  0x002E,  0x0021,  0x03DC,  0x03BA,  0x0053,  0x0035,  0x1FB5,  0x1F9C,  0x008C,
  0x004F,  0x1F72,  0x1F79,  0x00D6,  0x0038,  0x1ECA,  0x1F78,  0x01FA,  0x0064,
  0x1CD3,  0x1F5F,  0x09F9
};

UINT16 MxL251_MatchedFilterCoef_AnnexB64[48] =
{
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0001,  0x03FE,
  0x03FE,  0x0004,  0x0004,  0x03F8,  0x03F8,  0x000E,  0x000D,  0x03E8,  0x03ED,
  0x0024,  0x001D,  0x03CA,  0x03D9,  0x004C,  0x0033,  0x1F9A,  0x1FC0,  0x0086,
  0x004E,  0x1F50,  0x1FA7,  0x00DB,  0x003D,  0x1E99,  0x1F93,  0x01F1,  0x0075,
  0x1CB6,  0x1F7D,  0x09DA
};

UINT16 MxL251_MatchedFilterCoef_AnnexA[48] =
{
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,
  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x01FD,  0x0006,  0x03FD,  0x0002,
  0x03F5,  0x000F,  0x03FF,  0x03FB,  0x03EF,  0x0019,  0x000A,  0x03EB,  0x03E4,
  0x0029,  0x001E,  0x03CF,  0x03D6,  0x0044,  0x0034,  0x1FA9,  0x1FBE,  0x0074,
  0x0044,  0x1F70,  0x1FDA,  0x0101,  0x005E,  0x1EAD,  0x1F9E,  0x01EA,  0x0073,
  0x1CAA,  0x1F74,  0x09C9
};

INTERLEAVER_LOOKUP_INFO_T MxL251_InterDepthLookUpTable[] =
{
  {128, 1}, {128, 1}, {128, 2}, {64,  2}, {128, 3}, {32,  4}, {128, 4}, {16,  8},
  {128, 5}, {8,  16}, {128, 6}, {0,   0}, {128, 7}, {0,   0}, {128, 8}, {0,   0}
};

LUTY_LOOKUP_INFO_T MxL251_LutYLookUpTable[] = 
{
  {0},     {0},     {3010},  {4771},  {6021},  {6990},  {7782},  {8451},  
  {9031},  {9542},  {10000}, {10414}, {10792}, {11139}, {11461}, {11761},
  {12041}, {12304}, {12553}, {12788}, {13010}, {13222}, {13424}, {13617},
  {13802}, {13979}, {14150}, {14314}, {14472}, {14624}, {14771}, {14914}
};

static const REG_MASK_INFO_T RegMapDemodClockEnable[] = 
{
  {DEMOD1_CLK_EN_REG, DMD1_MCLK_EN_MASK|DMD1_CLK_X4_EN|DMD1_CLK_X2_EN|DMD1_CLK_X1_EN},
  {DEMOD2_CLK_EN_REG, DMD2_MCLK_EN_MASK|DMD2_CLK_X4_EN|DMD2_CLK_X2_EN|DMD2_CLK_X1_EN},
};

/* Define maximum permitted length for block write operation */
UINT32 MxL251_I2cMaxWriteLen = MAX_BLOCK_WRITE_LENGTH;  


/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetDeveiceContext
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 12/29/2010
--|
--| DESCRIPTION   : Retrieve MxL251SF device context
--|
--| INPUTS        : i2cSlaveAddress
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

PMXL251SF_DEV_CONTEXT_T MxL251_Ctrl_GetDeviceContext(UINT8 i2cAddr)
{
  return &MxL251Dev[i2cAddr&3];
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_WaitForHostCommandToComplete
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : This function returns firmware release candiate version
--|
--| RETURN VALUE  : MXL_TRUE and MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_WaitForHostCommandToComplete(UINT8 i2cAddr)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);
  UINT32 timeRemain;

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    // Do not wait if firmware is not loaded
    return MXL_TRUE;
  }

  timeRemain = MxL251_Ctrl_SpinOnRegField(i2cAddr, 
                                                 MAILBOX_REG_NUM_PENDING_HOST_CMDS, 
                                                 0xFFFF,
                                                 (UINT16)0,
                                                 SPIN_UNTIL_EQ, 
                                                 1000000/*1 seconds*/);
  return (0 == timeRemain)?MXL_FALSE:MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WriteRegisterMask
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|                  
--| DESCRIPTION   : Write register with mask
--|                 
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WriteRegisterMask(UINT8 i2cAddr, UINT16 regAddr, UINT16 mask, UINT16 val)
{
  UINT16 regData;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, regAddr, &regData))
  {
    return MXL_FALSE;
  }

  regData = (regData & ~mask) | (val & mask);

  return MxL251_Ctrl_WriteRegister(i2cAddr, regAddr, regData);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WriteRegisterField
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 03/07/2011
--|                  
--| DESCRIPTION   : Write register field
--|                 
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WriteRegisterField(UINT8 i2cAddr, UINT16 regAddr, UINT8 bitLocation, UINT8 bitWidth, UINT16 value)
{
  UINT16 mask = (0xFFFF>>(16-bitWidth)) << bitLocation;
  return MxL251_Ctrl_WriteRegisterMask(i2cAddr, regAddr, mask, (value << bitLocation));
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ReadRegisterMask
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|                  
--| DESCRIPTION   : Read register with mask
--|                 
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE if error
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ReadRegisterMask(UINT8 i2cAddr, UINT16 regAddr, UINT16 mask, UINT16* valPtr)
{
  UINT16 regData;
  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr, regAddr, &regData))
  {
    return MXL_FALSE;
  }

  *valPtr = (regData & mask);

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ProgramRegisters
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2/18/2011
--|
--| DESCRIPTION   : This function writes multiple registers with provided data array and 
--|                 demod id
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ProgramRegisters(UINT8 i2cSlaveAddr, MXL_DEMOD_ID_E demodId , PREG_CTRL_INFO_T ctrlRegInfoPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT16 i, tmp;
  
  i = 0;

  for (;;)
  {
    if ((ctrlRegInfoPtr[i].regAddr == 0) && (ctrlRegInfoPtr[i].mask == 0) && (ctrlRegInfoPtr[i].data == 0)) break;

    // Check if partial bits of register were updated
    if (ctrlRegInfoPtr[i].mask != 0xFFFF)  
    {
      status = MxL251_Ctrl_ReadRegister(i2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, ctrlRegInfoPtr[i].regAddr), &tmp);
      if (status != MXL_TRUE) break;;
    }
    
    tmp &= ~ctrlRegInfoPtr[i].mask;
    tmp |= ctrlRegInfoPtr[i].data;

    status = MxL251_Ctrl_WriteRegister(i2cSlaveAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, ctrlRegInfoPtr[i].regAddr), tmp);
    if (status != MXL_TRUE) break;

    i++;
  }

  return status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetBigEndian24
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Convert INT8 buf[0..2] into 24-bit big endian
--|
--| RETURN VALUE  : 24-bit unsigned value
--|-------------------------------------------------------------------------------------*/

UINT32 MxL251_Ctrl_GetBigEndian24(const UINT8 buf[])
{
  return (((UINT32)buf[0])<<16) | (((UINT32)buf[1])<<8) | buf[2];
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetBigEndian24
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Convert 24-bits val into buf[0..2] in big endian
--|
--| RETURN VALUE  : none
--|-------------------------------------------------------------------------------------*/

void MxL251_Ctrl_SetBigEndian24(UINT8 buf[], UINT32 val)
{
  buf[2] = val&0xFF;  val >>= 8;
  buf[1] = val&0xFF;  val >>= 8;
  buf[0] = val&0xFF;

  return;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetBigEndian32
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Convert INT8 buf[0..2] into 32-bit big endian
--|
--| RETURN VALUE  : 32-bit unsigned value
--|-------------------------------------------------------------------------------------*/

UINT32 MxL251_Ctrl_GetBigEndian32(const UINT8 buf[])
{
  return (((UINT32)buf[0])<<24) | (((UINT32)buf[1])<<16) | (((UINT32)buf[2])<<8) | buf[3];
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetBigEndian32
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Convert 32-bits val into buf[0..2] in big endian
--|
--| RETURN VALUE  : none
--|-------------------------------------------------------------------------------------*/

void MxL251_Ctrl_SetBigEndian32(UINT8 buf[], UINT32 val)
{
  buf[3] = val&0xFF;  val >>= 8;
  buf[2] = val&0xFF;  val >>= 8;
  buf[1] = val&0xFF;  val >>= 8;
  buf[0] = val&0xFF;

  return;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_CalCheckSum
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : This function calculate CheckSum of input data array.
--|
--| RETURN VALUE  : CheckSum, check sum of input data array
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_CalCheckSum(UINT8 inDataLen, UINT8 *inDataPtr, UINT8 *checkSum)
{
  UINT16 sum = 0;

  if (inDataLen == 0)
  {
    *checkSum = 0;
    return(MXL_TRUE);
  }
  else 
  {
    while (inDataLen--)
      sum += *inDataPtr++;

    *checkSum = (UINT8)(sum & 0xFF);
  }

  return(MXL_TRUE);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_CheckIntegration
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : This function check if received data is integrate or not by 
--|                 compare CheckSum.
--|
--| RETURN VALUE  : MXL_TRUE: data is complete, MXL_FALSE: not complete
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_CheckIntegration(UINT8 readCheckSum, UINT8 readDataLen, UINT8 *readDataPtr)
{
  UINT16 sum = 0;
  UINT8 len;

  if (readDataLen == 0)
    return(MXL_TRUE);  // Do not need to check integrate 
    
  for (len = 0; len < readDataLen; len ++)
    sum += *readDataPtr++;
 
  if ((sum & 0xff) == readCheckSum) 
    return(MXL_TRUE);  // Data is complete 
  else 
    return(MXL_FALSE); // Data is not complete
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_DownloadFirmwareInMbin
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : Download MBIN format firmware file into device 
--|                 MBIN file format is like below:
--|                 MBIN Header (16 bytes)
--|                 Seg#0 Header (8 bytes)
--|                 Seg#0 Data (Variable length in bytes)
--|                 ...
--|                 Seg#N Header (8 bytes)
--|                 Seg#N Data (Variable length in bytes)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_DownloadFirmwareInMbin(UINT8 i2cSlaveAddr, MBIN_FILE_T* mbinPtr, UINT8 enableRun)
{
  MBIN_SEGMENT_T *segmentPtr ;
  UINT32 index;
  UINT32 segLength;
  UINT32 segAddress;

  MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareInMbin: Header ID = %d, Segments number = %d \n",mbinPtr->header.id, mbinPtr->header.numSegments);

  segmentPtr = (MBIN_SEGMENT_T*)(&mbinPtr->data[0]);

  /* Check for proper file format */
  if (mbinPtr->header.id != MBIN_FILE_HEADER_ID )
  {
    MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareInMbin: Invalid file header ID (%c)\n", mbinPtr->header.id);
    return MXL_FALSE; // If the file is not MBIN format, then exit with MXL_FALSE 
  }

  /* Process each segment */
  for (index = 0; index < mbinPtr->header.numSegments; index++)
  {
    /* Validate segment header ID */
    if ( segmentPtr->header.id != MBIN_SEGMENT_HEADER_ID)
    {
      MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareInMbin: Invalid segment header ID (%c)\n",segmentPtr->header.id);
      return MXL_FALSE; // If the segment format is wrong, then exit with MXL_FALSE 
    }

    /* Get segment data length and start address */
    segLength  = MxL251_Ctrl_GetBigEndian24(&(segmentPtr->header.len24[0]));
    segAddress = MxL251_Ctrl_GetBigEndian32(&(segmentPtr->header.address[0]));
    
    /* Send segment */
    if (MXL_TRUE != MxL251_Ctrl_DownloadFirmwareSegment(i2cSlaveAddr, segAddress, segmentPtr->data, segLength))
    {
      return MXL_FALSE;
    }

    /* Next segment */
    segmentPtr = (MBIN_SEGMENT_T*)&(segmentPtr->data[((segLength + 3)/4)*4]);

  }   

  if ((MXL_BOOL)enableRun == MXL_ENABLE)  
  { 
    // Run firmware after download
    return MxL251_Ctrl_SendDownloadCommand(i2cSlaveAddr, HOST_CMD_DOWNLOAD_DONE_CFG, &(mbinPtr->header.entryAddress[0]), 4, 0);
  }
  else 
  {
    // Do not run firmware after download 
    return MXL_TRUE;
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_DownloadFirmwareSegment
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : Download segment of MBIN format firmware into MxL251SF device  
--|
--| RETURN VALUE  : none
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_DownloadFirmwareSegment(UINT8 i2cSlaveAddr, UINT32 address, const UINT8* dataPtr, UINT32 dataLen)
{
  UINT32 nSend;       // Bytes that send to device
  UINT16 seqNum = 0;  // Record the firmware block sequence number that have been downloaded 
  UINT8  payload[4];

  MxL251_Ctrl_SetBigEndian32(payload, address);

  // Send  command firstly 
  if (MXL_TRUE != MxL251_Ctrl_SendDownloadCommand(i2cSlaveAddr, HOST_CMD_SET_ADDR_CFG, payload, 4, 0))
  {
    MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareSegment: HOST_CMD_SET_ADDR_CFG failed! \n");
    return MXL_FALSE;
  }
  else 
    MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareSegment: HOST_CMD_SET_ADDR_CFG success. Segment data length = %d\n", dataLen);

  while (dataLen)
  {
    // Send segment data, the block length is nSend
    if (dataLen > (MxL251_I2cMaxWriteLen - COMMAND_HEADER_LENGTH))
    {
      nSend = MxL251_I2cMaxWriteLen - COMMAND_HEADER_LENGTH;
    }
    else
    {
      nSend = dataLen;
    }

    MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareSegment: HOST_CMD_DOWNLOAD_SEGMENT_CFG, Max Limitation = %d, send length = %d bytes\n",MxL251_I2cMaxWriteLen, nSend);

    if (MXL_TRUE != MxL251_Ctrl_SendDownloadCommand(i2cSlaveAddr, HOST_CMD_DOWNLOAD_SEGMENT_CFG, (void*)dataPtr, nSend, seqNum))
    {
      MxL_DLL_DEBUG0("Ctrl_DownloadFirmwareSegment: send HOST_CMD_DOWNLOAD_SEGMENT_CFG fail. \n");
      return MXL_FALSE;
    }

    // Sending data pointer is moved to next segment 
    seqNum ++;
    dataPtr += nSend;
    dataLen -= nSend;
    address += nSend;
  }

  return MXL_TRUE;
}

#ifdef _DOWNLOAD_DEBUG_ENABLED_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_CheckCommandResponse
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 04/07/2011
--|
--| DESCRIPTION   : Check respose of download commands
--|
--| RETURN VALUE  : none
--|-------------------------------------------------------------------------------------*/

void MxL251_Ctrl_CheckCommandResponse(UINT8 i2cSlaveAddr, UINT16 cmd)
{
  UINT8 readBuffer[COMMAND_HEADER_LENGTH];
  if (0 == MxL251_Ctrl_ReadBlock(i2cSlaveAddr, cmd, COMMAND_HEADER_LENGTH, readBuffer))
  {
    MxL_DLL_DEBUG0("CMDRESPONSE: SYNC=0x%02X, errorCode=0x%02X, checkSum=0x%02X, dataLen=0x%02X. \n",
     readBuffer[0],readBuffer[1],readBuffer[2],readBuffer[3]);
  }
  else
  {
    MxL_DLL_DEBUG0("Block read failed\n");
  }
}
#endif // _DOWNLOAD_DEBUG_ENABLED_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SendDownloadCommand
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : Send download command into MxL251SF device  
--|
--| RETURN VALUE  : none
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SendDownloadCommand(UINT8 i2cSlaveAddr, MXL_CMD_ID_E commandId, void* dataPtr, UINT32 dataLen, UINT16 downloadBlockCnt)
{
  HOST_COMMAND_T downloadFwSeg;
  FW_RESPONSE_T  response;
  UINT32 i;
  static UINT32 curAddress = 0; // curAddress is used for debugging purpose only

  // Check if the sending data length exceeds the limitation 
  if (dataLen > (MxL251_I2cMaxWriteLen - COMMAND_HEADER_LENGTH))
  {
    MxL_DLL_ERROR0("Invalid command length (%d)\n", dataLen);
    return MXL_FALSE;
  }

  switch (commandId)
  {
    case HOST_CMD_SET_ADDR_CFG:
      curAddress = MxL251_Ctrl_GetBigEndian32((UINT8*)dataPtr);
      MxL_DLL_DEBUG0("I2CTRC_FW_DOWNLOAD // COMMAND_SET_ADDR_CFG(0x%08x)\n", curAddress);
      break;

    case HOST_CMD_DOWNLOAD_SEGMENT_CFG:
      MxL_DLL_DEBUG0("I2CTRC_FW_DOWNLOAD // COMMAND_DOWNLOAD_SEGMENT_CFG(0x%08x-0x%08x)\n", curAddress, curAddress+dataLen-1);
      curAddress += dataLen;
      break;

    case HOST_CMD_DOWNLOAD_DONE_CFG:
      MxL_DLL_DEBUG0("I2CTRC_FW_DOWNLOAD // COMMAND_DOWNLOAD_DONE_CFG(0x%08x)\n", MxL251_Ctrl_GetBigEndian32((UINT8*)dataPtr));
      break;

    default: 
      MxL_DLL_ERROR0("Invalid command (%d)\n", commandId);
      break;
  }

  // Populate command header
  FORM_CMD_HEADER(downloadFwSeg, commandId, downloadBlockCnt, dataLen);
  
  // Copy data from dataPtr to downloadFwSeg.data
  for (i = 0; i < dataLen; i++)  // Copy data from dataPtr to downloadFwSeg.data
    downloadFwSeg.data[i] = (UINT8)*((UINT8*)dataPtr+i);

  // Calculate the CheckSum
  MxL251_Ctrl_CalCheckSum(downloadFwSeg.payloadLen, (UINT8 *)dataPtr, &downloadFwSeg.payloadCheckSum); // Calculate CheckSum

  if (MXL_TRUE != MxL251_Ctrl_SendHostCommand(i2cSlaveAddr, &downloadFwSeg))
  { 
    // There is error either in Command transfering or response receiving
     MxL_DLL_ERROR0("Calling Ctrl_SendHostCommand error ! \n");
     return MXL_FALSE;
  }

  if (commandId == HOST_CMD_DOWNLOAD_DONE_CFG)
  {
    if (MXL_TRUE != MxL251_Ctrl_GetDeviceResp(i2cSlaveAddr, HOST_CMD_DOWNLOAD_DONE_CFG, &response))
    {
      MxL_DLL_ERROR0("HOST_CMD_DOWNLOAD_DONE_CFG failed MxL251_Ctrl_GetDeviceResp\n");
      return MXL_FALSE;
    }

    if (0xFF != response.syncChar || 0x00 != response.errorCode)
    {
      MxL_DLL_ERROR0("HOST_CMD_DOWNLOAD_DONE_CFG failed: syncChar=0x%02x errorCode=0x%02x\n", 
         response.syncChar, response.errorCode);
      return MXL_FALSE;
    }
  }
  else if (commandId == HOST_CMD_DOWNLOAD_SEGMENT_CFG)
  {
#ifdef _DOWNLOAD_DEBUG_ENABLED_
    MxL251_Ctrl_CheckCommandResponse(i2cSlaveAddr, HOST_CMD_DOWNLOAD_SEGMENT_CFG);
#endif // _DOWNLOAD_DEBUG_ENABLED_
    // MxL_DLL_DEBUG0("Block %d is downloaded successfully. \n", downloadBlockCnt);
  }
  else
  {
#ifdef _DOWNLOAD_DEBUG_ENABLED_
    MxL251_Ctrl_CheckCommandResponse(i2cSlaveAddr, HOST_CMD_SET_ADDR_CFG);
#endif // _DOWNLOAD_DEBUG_ENABLED_
  }

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SendHostCommand
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : This function send host command to device, not read response.
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SendHostCommand(UINT8 i2cSlaveAddr, PHOST_COMMAND_T commandPtr)
{
  UINT16 bufferSize,i;
  UINT8 status = MXL_TRUE;
  UINT16 RegAddr; 
  UINT8 writeBuffer[sizeof(HOST_COMMAND_T)]; 

  // If there is command data, copy it into writeBuffer
  if (commandPtr->payloadLen > 0)
  {
    for (i = 0; i < commandPtr->payloadLen; i++)  // Copy data from commandPtr->data to writeBuffer
      writeBuffer[2 + i] = commandPtr->data[i];

    bufferSize = commandPtr->payloadLen + 2; 
  }
  else 
    bufferSize = 2; 

  RegAddr = commandPtr->syncChar; 
  RegAddr = (RegAddr << 8) + (UINT16)(commandPtr->commandId);
  writeBuffer[0] = commandPtr->payloadCheckSum; 
  writeBuffer[1] = commandPtr->payloadLen;  

  // Send host command to MxL251SF 
  status = (UINT8)MxL251_Ctrl_WriteBlock(i2cSlaveAddr, RegAddr, bufferSize, writeBuffer);

  return((MXL_STATUS)status);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetDeviceResp
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : This function gets device response from certain Sub address.
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetDeviceResp(UINT8 i2cSlaveAddr, UINT16 subAddr, PFW_RESPONSE_T responsePtr)
{
  UINT16 bufferSize,i;
  UINT8 status = MXL_TRUE;
  UINT8 readBuffer[sizeof(HOST_COMMAND_T)];

  // Read response header firstly 
  status |= (UINT8)MxL251_Ctrl_ReadBlock(i2cSlaveAddr, subAddr, COMMAND_HEADER_LENGTH, readBuffer);

  MxL_DLL_DEBUG0("Block read back : SYNC=0x%02X, errorCode=0x%02X, checkSum=0x%02X, dataLen=0x%02X. \n",
                  readBuffer[0],readBuffer[1],readBuffer[2],readBuffer[3]);

  if (status == MXL_TRUE)  // Read block success 
  {
    responsePtr->syncChar = readBuffer[0];
    responsePtr->errorCode = (MXL_RSP_ID_E)readBuffer[1];
    responsePtr->payloadCheckSum = readBuffer[2];
    responsePtr->payloadLen = readBuffer[3];

    // Check if previous command execution success or not
    if (responsePtr->errorCode == RESPONSE_ID_SUCCESS)
    {
      // Check if need to read response data
      if (responsePtr->payloadLen > 0)
      {
        bufferSize = responsePtr->payloadLen;
     
        // Read Response data 
        status |= (UINT8)MxL251_Ctrl_ReadBlock(i2cSlaveAddr, subAddr, bufferSize, readBuffer);  

        // Check if received response data is complete or not 
        status |= MxL251_Ctrl_CheckIntegration(responsePtr->payloadCheckSum, (UINT8)bufferSize, readBuffer);

        if (status == MXL_TRUE) // Read response data success 
        {
          for (i = 0; i < bufferSize; i++)  // Copy data from readBuffer to responsePtr->data
            responsePtr->data[i] = readBuffer[i]; 
        }
      }
    }
    else return(MXL_FALSE);
  }

  return((MXL_STATUS)status);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_HostComm
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : This function send host command and get response between host
--|                 and firmware.
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_HostComm(UINT8 i2cSlaveAddr, PHOST_COMMAND_T commandPtr, PFW_RESPONSE_T responsePtr)
{
  UINT16 bufferSize,i;
  UINT16 RegAddr; 
  UINT8 status = MXL_TRUE;
  UINT8 writeBuffer[sizeof(HOST_COMMAND_T)]; 
  UINT8 readBuffer[sizeof(HOST_COMMAND_T)];

  // If there is command data, copy it into writeBuffer
  if (commandPtr->payloadLen > 0)
  {
    for (i = 0; i < commandPtr->payloadLen; i++)  // Copy data from commandPtr->data to writeBuffer
      writeBuffer[2 + i] = commandPtr->data[i];

    /* Write Buffer include both payloadCheckSum and payloadLen two bytes */
    bufferSize = commandPtr->payloadLen + 2; 
  }
  else 
    bufferSize = 2; // Write Buffer only contais payloadCheckSum and payloadLen two bytes 

  // Form RegAddr using syncChar and Command ID bytes 
  RegAddr = commandPtr->syncChar; 
  RegAddr = (RegAddr << 8) + (UINT16)(commandPtr->commandId);
  // Write buffer begining two bytes are payload check sum and payload data length 
  writeBuffer[0] = commandPtr->payloadCheckSum; 
  writeBuffer[1] = commandPtr->payloadLen;  

  // Send host command to MxL251SF 
  status = (UINT8)MxL251_Ctrl_WriteBlock(i2cSlaveAddr, RegAddr, bufferSize, writeBuffer);

  // Read response header firstly 
  status |= (UINT8)MxL251_Ctrl_ReadBlock(i2cSlaveAddr, (UINT16)commandPtr->commandId, COMMAND_HEADER_LENGTH, readBuffer);

  MxL_DLL_DEBUG0("Block read back : SYNC=0x%02X, errorCode=0x%02X, checkSum=0x%02X, dataLen=0x%02X. \n",
     readBuffer[0],readBuffer[1],readBuffer[2],readBuffer[3]);

  if (status == MXL_TRUE)  // Block read operation is successful 
  {
    responsePtr->syncChar = readBuffer[0];
    responsePtr->errorCode = (MXL_RSP_ID_E)readBuffer[1];
    responsePtr->payloadCheckSum = readBuffer[2];
    responsePtr->payloadLen = readBuffer[3];

    // Check if previous command execution success or not
    if (responsePtr->errorCode == RESPONSE_ID_SUCCESS)
    {
      // Check if need to read response data (check if Payload length is large than 0 ) 
      if (responsePtr->payloadLen > 0)
      {
        bufferSize = responsePtr->payloadLen;
     
        // Read Response data 
        status |= (UINT8)MxL251_Ctrl_ReadBlock(i2cSlaveAddr, (UINT16)commandPtr->commandId, bufferSize, readBuffer);  

        // Check if received response data is complete or not 
        status |= MxL251_Ctrl_CheckIntegration(responsePtr->payloadCheckSum, (UINT8)bufferSize, readBuffer);

        if (status == MXL_TRUE) // Read response data success 
        {
          for (i = 0; i < bufferSize; i++)  // Copy data from readBuffer to responsePtr->data
            responsePtr->data[i] = readBuffer[i]; 
        }
      }
    }
    else
    {
      return(MXL_FALSE); // There is erro because response errorCode is not RESPONSE_ID_SUCCESS 
    }
  }

  return((MXL_STATUS)status);
}


/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_NbTuneCfgDfeXbar
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24 
--|
--| DESCRIPTION   : This function configures DFE and XBAR 
--|
--|                 Digital Mixer Frequency control register configuraiton by
--|                 the different PLL 
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_NbTuneCfgDfeXbar(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT32 chanId)
{
  UINT8 status = MXL_TRUE;

#ifdef _MXL251_FIXEDPOINT_
  SINT64 nbFreqOffsetInMHz;
  UINT32 scaleFactor;
  SINT64  temp2; 
#else
  REAL32 nbFreqOffsetInMHz;
#endif
  SINT32 freqOffsetInHz;
  UINT16 control, tmp16; 
  UINT16 enableMap;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  status |= MxL251_Ctrl_GetChanXbarEnaRegister(i2cAddr, &control);

  // Set primary channel
  enableMap = control&0xFF;

  if (chanId >= DFE_IF_BASE
      && FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus
      && (devContextPtr->Tuners[tunerId].FastScanEnable) == MXL_DISABLE)
  {
    MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_IF_RAMP_BOTTOM, &(devContextPtr->DAGCBottomSetPt));

    if (0 != (enableMap & DFE_CHN_ENA_BIT(chanId)))
    {
      // If this channel was current enabled, ramp it down to lowest
      if (MXL_TRUE != MxL251_Ctrl_SetNewIFLevel(i2cAddr, 
            chanId - DFE_IF_BASE, 
            devContextPtr->DAGCBottomSetPt))
      {
        MxL_DLL_ERROR0("%s - MxL251_Ctrl_SetNewIFLevel failed\n", __FUNCTION__);
        return MXL_FALSE;
      }
      if (MXL_TRUE != MxL251_Ctrl_WaitUntilIFLevelRampDone(
            i2cAddr,
            chanId - DFE_IF_BASE))
      {
        MxL_DLL_ERROR0("%s - MxL251_Ctrl_WaitUntilIFLevelRampDone failed\n", __FUNCTION__);
        return MXL_FALSE;
      }
    }
    else
    {
      // If this channel was current disabled, program SETPT register directly
      MxL251_Ctrl_WriteRegister(i2cAddr,
          DFE_DAGCx_SETPT_REG(chanId), 
          devContextPtr->DAGCBottomSetPt);
    }
  }

  // Set primary channel
  if (chanId < DFE_IF_BASE && 0 == (enableMap & 0x000F))
  {
    // Enabling one TS channel, and no TS channel are enabled before
    //
    // DFE_PCH_ISEL_TS has only 2-bit wide, to indicate which of 4 TS channels
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                  DFE_PCH_ISEL_TS_REG, 
                                  DFE_PCH_ISEL_TS_MASK, 
                                  chanId<<DFE_PCH_ISEL_TS_SHIFT_BITS);
  }
  else if (chanId >= DFE_IF_BASE && 0 == (enableMap & 0x00F0))
  {
    // Enable one IF channel, and no IF channel are enabled before

    // DFE_PCH_ISEL_IF has only 2-bit wide, to indicate which of 4 IF channels
    // (chanId-DFE_IF_BASE) has range from 0 to 3, although DFE_PCH_ISEL_IF_MASK will mask.
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                  DFE_PCH_ISEL_IF_REG, 
                                  DFE_PCH_ISEL_IF_MASK, 
                                  (chanId-DFE_IF_BASE)<<DFE_PCH_ISEL_IF_SHIFT_BITS);
  }
  
  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    UINT16 currDfeChan;
 
    currDfeChan   = 1 << chanId;

    control |= (currDfeChan & 0x00FF);  // Set enable bit field 

    currDfeChan <<= 8;  
  
    if (tunerId == TUNER0 )  control &= ~(currDfeChan & 0xFF00);  // Set Tuner 0 or Tuner 1 selection 
    else  control |= (currDfeChan & 0xFF00);

    /* Default is all path enabled */
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_XBAR_CHAN_CFG_REG, control);

    // Configure NB channel bandwidth (DFE_CHN0_CTRL_BW_SEL)
    status = (UINT8)MxL251_Ctrl_ReadRegister(i2cAddr, DFE_BANDWIDTH_CFG_REG, &control);

    if (devContextPtr->Tuners[tunerId].BandWidthInMHz == NB_8_MHz) 
    {
      control |= currDfeChan;
    }
    else
    {
      control &= ~currDfeChan;  // 6 MHz
    }
  
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_BANDWIDTH_CFG_REG, control);
  }
  // Program Frequency offset (Freq offset from Wide Band)
  // offset = NB - WB
  freqOffsetInHz = (SINT32)devContextPtr->Tuners[tunerId].NbChanFreqInHz - (SINT32)devContextPtr->Tuners[tunerId].WbCapFreqInHz;

  // Save frequency offset
  devContextPtr->Tuners[tunerId].FreqOffsetInHz = freqOffsetInHz;

  if (IS_ASIC_TARGET(devContextPtr))  // Silicon
  {
    freqOffsetInHz = -freqOffsetInHz;
  }
  MxL_DLL_DEBUG0("Freq offset:%d Hz\tWb_BW=%d\n", freqOffsetInHz,devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz);

  // Convert it to MHz
#ifdef _MXL251_FIXEDPOINT_
  nbFreqOffsetInMHz = freqOffsetInHz;
  scaleFactor = 1000000;
#else
  nbFreqOffsetInMHz = (REAL32)freqOffsetInHz/1000000;
#endif

  // ADC Sampling modes and Sampling Frequency
  // Based on Reference PLL Frequency, 3 different cases are provided
  switch (devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz)
  {
    case WB_96_MHz:
      tmp16 = 6;
      // Check a boundary condition
#ifdef _MXL251_FIXEDPOINT_
      if ((nbFreqOffsetInMHz > 64 * scaleFactor) || (nbFreqOffsetInMHz < -64 * scaleFactor))
      {
          MxL_DLL_DEBUG0("Wrong NB Freq offset:%llx MHz\n", MXL_DIV64_S(nbFreqOffsetInMHz, scaleFactor));
      }
#else
	  if ((nbFreqOffsetInMHz > 64) || (nbFreqOffsetInMHz < -64))
      {
        MxL_DLL_DEBUG0("Wrong NB Freq offset:%f MHz\n", nbFreqOffsetInMHz);
      }
#endif
      break;
    
    case WB_48_MHz:
    default:
      tmp16 = 3;
      // Check a boundary condition
#ifdef _MXL251_FIXEDPOINT_
	  if ((nbFreqOffsetInMHz > 32 * scaleFactor) || (nbFreqOffsetInMHz < -32 * scaleFactor))
	  {
          MxL_DLL_DEBUG0("Wrong NB Freq offset:%llx MHz\n", MXL_DIV64_S(nbFreqOffsetInMHz,scaleFactor));
      }
#else
      if ((nbFreqOffsetInMHz > 32) || (nbFreqOffsetInMHz < -32))
      {
        MxL_DLL_DEBUG0("Wrong NB Freq offset:%f MHz\n", nbFreqOffsetInMHz);
      }
#endif
      break;

    case WB_16_MHz:
      tmp16 = 1;
#ifdef _MXL251_FIXEDPOINT_
	  if ((nbFreqOffsetInMHz > 106 * 100000) || (nbFreqOffsetInMHz < -106 * 100000))
	  {
         MxL_DLL_DEBUG0("Wrong NB Freq offset:%llx MHz\n", MXL_DIV64_S(nbFreqOffsetInMHz,scaleFactor));
      }
#else
      if ((nbFreqOffsetInMHz > 10.6) || (nbFreqOffsetInMHz < -10.6))
      {
        MxL_DLL_DEBUG0("Wrong NB Freq offset:%f MHz\n", nbFreqOffsetInMHz);
      }
#endif
      break;
  }

#if 1
  switch (devContextPtr->XtalFreq)
  {
    case XTAL_16MHz:
    case XTAL_24MHz: // PLL 256MHz
      nbFreqOffsetInMHz = (6/tmp16) * (nbFreqOffsetInMHz * 512);
      break;

    case XTAL_25MHz: // PLL 255.56MHz
      //nbFreqOffsetInMHz = (6/tmp16) * ((nbFreqOffsetInMHz * 9 * 65536)/1150);
      nbFreqOffsetInMHz = (6/tmp16) * (MXL_DIV64_S((nbFreqOffsetInMHz * 9 * 65536),1150));
      MxL_DLL_DEBUG0("XTAL_25MHZ -- nbFreqOffsetInMHz:%lld MHz\n", nbFreqOffsetInMHz);
      break;

    case XTAL_27MHz: // PLL 255
      //nbFreqOffsetInMHz = (6/tmp16) * ((nbFreqOffsetInMHz * 2 * 65536)/255);
      nbFreqOffsetInMHz = (6/tmp16) * (MXL_DIV64_S((nbFreqOffsetInMHz * 2 * 65536),255));
      break;
  }
#endif


#ifdef _MXL251_FIXEDPOINT_ 
  //temp2 = (SINT64)(nbFreqOffsetInMHz /scaleFactor + 0.5);
  temp2 = MXL_DIV64_S(nbFreqOffsetInMHz, scaleFactor);
  nbFreqOffsetInMHz = temp2;
  MxL_DLL_DEBUG0("After scaleFactor -- temp2:%lldMHz, nbFreqOffsetInMHz:%lldMHz\n", temp2, nbFreqOffsetInMHz);
#endif


  // DFE_CHN_DMX_FCW
#ifdef _MXL251_FIXEDPOINT_
 // nbFreqOffsetInMHz = -12308;
  MxL_DLL_DEBUG0("Freq offset to write to DMX:{%d} \n", (SINT32)nbFreqOffsetInMHz);
  status |= MxL251_Ctrl_WriteRegister(
      i2cAddr, 
      (FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus)?MAILBOX_REG_DFE_HOSTCMD_PARAM1:(DFE_FREQ_OFFSET_CFG_REG + chanId * 4), 
      (UINT16)nbFreqOffsetInMHz);
#else
  MxL_DLL_DEBUG0("Freq offset to write to DMX:%d \n", (SINT16)(nbFreqOffsetInMHz+0.5));
  status |= MxL251_Ctrl_WriteRegister(
      i2cAddr, 
      (FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus)?MAILBOX_REG_DFE_HOSTCMD_PARAM1:(DFE_FREQ_OFFSET_CFG_REG + chanId * 4), 
      (UINT16)(SINT16)(nbFreqOffsetInMHz+0.5));
#endif
  

  return(MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetFir3Cic2Cic1
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Set NB FIR3, CIC2, and CIC1 mode
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetFir3Cic2Cic1(UINT8 i2cAddr, UINT8 chanId, UINT32 wbBW)
{
  /*
     96   48   16
     dfe_chn0_fir3_byp 0    1     1
     dfe_chn0_cic2_byp 0    1     1
     dfe_chn0_cic1_byp 0    0     1
     */
  UINT16 fir3cic2cic1Byp = 0;

  switch (wbBW)
  {
    case WB_96_MHz: fir3cic2cic1Byp = 0x00; break;
    case WB_48_MHz: fir3cic2cic1Byp = 0x06; break;
    case WB_16_MHz: fir3cic2cic1Byp = 0x07; break;
  }

  if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
                                                DFE_CIC1_BYP_CIC2_SCALE_CIC2_BYP_REG(chanId), 
                                                (0x7<<DFE_CIC1_BYP_LSB(chanId)), 
                                                (fir3cic2cic1Byp<<DFE_CIC1_BYP_LSB(chanId))))
  {
    return MXL_FALSE;
  }

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConvertDemodIdToAddr
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : This function converts to demod address based on demod ID
--|
--| RETURN VALUE  : UINT16 
--|
--|-------------------------------------------------------------------------------------*/

UINT16 MxL251_Ctrl_ConvertDemodIdToAddr(MXL_DEMOD_ID_E DemodId, UINT16 Addr)
{
  /* Reset demod id <15 : 12> */
  UINT16 retVal = (Addr & 0x0FFF);

  switch(DemodId)
  {
    /* Demod 0 */
    case DEMOD0:
      retVal |= 0x7000;
      break;

    /* Demod 1 */
    case DEMOD1:
      retVal |= 0x8000;
      break;
    default:
      break;
  }

  return retVal;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetField
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Get nbits field starting from lsbloc
--|
--| RETURN VALUE  : UINT32
--|
--|-------------------------------------------------------------------------------------*/

UINT32 MxL251_Ctrl_GetField(UINT32 input, UINT32 lsbloc, UINT32 nbits)
{
  return (input & MXL_MASK(lsbloc, nbits) ) >> lsbloc;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetField
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Set nbits field starting from lsbloc to val
--|
--| RETURN VALUE  : UINT32
--|
--|-------------------------------------------------------------------------------------*/

UINT32 MxL251_Ctrl_SetField(UINT32 input, UINT32 lsbloc, UINT32 nbits, UINT32 value)
{
  return (input & (~(MXL_MASK(lsbloc, nbits)))) | ((value<<lsbloc) & MXL_MASK(lsbloc, nbits));
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetMpegOutEnable
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 10/14/2010
--|
--| DESCRIPTION   : Set MPEG Output Enable
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetMpegOutEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL mpegOutEnable)
{
  UINT8 status = MXL_TRUE;
  UINT8 chanId = MxL251_Ctrl_ConvertDemodIdToChanId(demodId);
  MXL_BOOL oobOutEnable;
  UINT16 qamType;

  if (mpegOutEnable == MXL_DISABLE)
  {
    // Diable both mpegOut and oobOut
    oobOutEnable = MXL_DISABLE;
  }
  else
  {
    // Enable either mpegOut or oobOut, depending on QAM_TYPE
    status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, QAM_ANNEX_TYPE_REG), &qamType);
    qamType &= 0x0007;
    if (qamType == MXL_QPSK)
    {
      mpegOutEnable = MXL_DISABLE;
      oobOutEnable  = MXL_ENABLE;
    }
    else
    {
      mpegOutEnable = MXL_ENABLE;
      oobOutEnable  = MXL_DISABLE;
    }
  }

  // Enable/disable MPEG out
  status |= MxL251_Ctrl_WriteRegisterMask(
      i2cAddr, 
      MPEGx_OPEN_REG, 
      MPEGx_OPEN_MASK(chanId), 
      (mpegOutEnable == MXL_DISABLE)?MPEGx_OPEN_MASK(chanId):0
      );

  // Enable/disable OOB out
  status |= MxL251_Ctrl_WriteRegisterMask(
      i2cAddr, 
      OOBx_OEN_REG, 
      OOBx_OEN_MASK(chanId), 
      (oobOutEnable == MXL_DISABLE)?OOBx_OEN_MASK(chanId):0
      );

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetMpegPadDrv
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Set MPEG Output Interface pad drive strength
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetMpegPadDrv(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, PMPEG_PAD_DRV_T padDrvPtr)
{
  UINT16 control =0;
  UINT16  drv = 0;
  UINT8 status = MXL_TRUE;

  switch (demodId)
  {
    case DEMOD0:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPSYN_1_DRV_REG, &control);
      control &= (~PAD_MPSYN_1_DRV_MASK);
      drv = padDrvPtr->PAD_MPSYN_DRV;
      control |= (drv <<8);
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MPSYN_1_DRV_REG, control);

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MDAT_1_DRV_REG, &control);
      control &= (~PAD_MDAT_1_DRV_MASK);
      drv = padDrvPtr->PAD_MPDAT_DRV;
      control |= drv;
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MDAT_1_DRV_REG, control);

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPVAL_1_DRV_REG, &control);
      control &= (~PAD_MPVAL_1_DRV_MASK);
      drv = padDrvPtr->PAD_MPVAL_DRV;
      control |= (drv<<12);
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MPVAL_1_DRV_REG, control);
      
      break;

    case DEMOD1:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPSYN_2_DRV_REG, &control);
      control &= (~PAD_MPSYN_2_DRV_MASK);
      drv = padDrvPtr->PAD_MPSYN_DRV;
      control |= (drv <<4);
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MPSYN_2_DRV_REG, control);

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MDAT_2_DRV_REG, &control);
      control &= (~PAD_MDAT_2_DRV_MASK);
      drv = padDrvPtr->PAD_MPDAT_DRV;
      control |= (drv<<12);
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MDAT_2_DRV_REG, control);

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPVAL_2_DRV_REG, &control);
      control &= (~PAD_MPVAL_2_DRV_MASK);
      drv = padDrvPtr->PAD_MPVAL_DRV;
      control |= (drv<<8);
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, PAD_MPVAL_2_DRV_REG, control);

      break;

    default:
      status = MXL_FALSE;
      MxL_DLL_ERROR0("%s - invalid demodId %d\n", __FUNCTION__, demodId);
      break;
  }

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetMpegPadDrv
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Get MPEG Output Interface pad drive strength
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetMpegPadDrv(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, PMPEG_PAD_DRV_T padDrvPtr)
{
  UINT16 control =0;
  UINT16  drv = 0;
  UINT8 status = MXL_TRUE;

  switch (demodId)
  {
    case DEMOD0:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPSYN_1_DRV_REG, &control);
      control &= PAD_MPSYN_1_DRV_MASK;
      drv = control >>8;
      padDrvPtr->PAD_MPSYN_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;
     
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MDAT_1_DRV_REG, &control);
      control &= PAD_MDAT_1_DRV_MASK;
      drv = control;
      padDrvPtr->PAD_MPDAT_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPVAL_1_DRV_REG, &control);
      control &= PAD_MPVAL_1_DRV_MASK;
      drv = control >> 12;
      padDrvPtr->PAD_MPVAL_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;
     
      break;

    case DEMOD1:
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPSYN_2_DRV_REG, &control);
      control &= PAD_MPSYN_2_DRV_MASK;
      drv = control >> 4;
      padDrvPtr->PAD_MPSYN_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;

      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MDAT_2_DRV_REG, &control);
      control &= PAD_MDAT_2_DRV_MASK;
      drv = control >> 12;
      padDrvPtr->PAD_MPDAT_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;
      
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, PAD_MPVAL_2_DRV_REG, &control);
      control &= PAD_MPVAL_2_DRV_MASK;
      drv = control >> 8;
      padDrvPtr->PAD_MPVAL_DRV = (MPEG_DRV_STRENGTH_MODE_E)drv;
   
      break;

    default:
      status = MXL_FALSE;
      MxL_DLL_ERROR0("%s - invalid demodId %d\n", __FUNCTION__, demodId);
      break;

  }
  
  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetRefVCOFreqInMHz
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Get MxL251_Device.RefVCOFreqInMHz
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

UINT16 MxL251_Ctrl_GetRefVCOFreqInMHz(UINT8 i2cAddr)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  return devContextPtr->RefVCOFreqInMHz;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SpinOnRegField
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Poll a field until masked value is not 'value', or timeout
--|
--| INPUTS        : addr  - a 16-bit register address
--|                 mask  - 16-bit mask
--|                 value - reference to be tested against (*(UINT16*)(addr)|mask)
--|                 timeoutUs - timeout in us
--|
--| RETURN VALUE  : 0 if timeout; non-zero: remaining time
--|
--|-------------------------------------------------------------------------------------*/
UINT32 MxL251_Ctrl_SpinOnRegField(UINT8 i2cAddr, UINT16 addr, UINT16 mask, UINT16 value, SPIN_CONDITION_E cond, UINT32 timeoutUs)
{
#ifndef _MXL_PATE_BUILD_
  UINT64 startTime, curTime;
  UINT32 elapsedTime;
  UINT16 regData = 0;
  UINT32 sleepTime;

  // if (timeoutUs < 5000) sleepTime        = 1000;
  sleepTime = 1000; // fixed interval to 1ms
  //if (timeoutUs < 50000) sleepTime  = 1000;
  //else sleepTime = 10000;

  MxL251_Ctrl_GetCurrTimeInUsec(&startTime);

  for(;;)
  {
    MxL251_Ctrl_ReadRegisterMask(i2cAddr, addr, mask, &regData);

    MxL251_Ctrl_GetCurrTimeInUsec(&curTime);
    elapsedTime = (UINT32)(curTime - startTime);
    if (  (cond == SPIN_UNTIL_NEQ && (regData & mask) != value)
        ||(cond == SPIN_UNTIL_EQ && (regData & mask) == value))
    {
      return (timeoutUs - elapsedTime);
    }

    if (elapsedTime >= timeoutUs)
    {
      return 0;
    }
    
    MxL251_Ctrl_DelayUsec(sleepTime);
  }
#else // _MXL_PATE_BUILD_
  return (timeoutUs - 1);
#endif // _MXL_PATE_BUILD_
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetNewIFLevel
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Set IF level mailbox register
--|
--| INPUTS        : desiredIfLevel
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetNewIFLevel(UINT8 i2cAddr, UINT8 ifIndex, UINT16 desiredIfLevel)
{
  UINT16 agcSetPt;

  if (MXL_TRUE != MxL251_Ctrl_WaitUntilIFLevelRampDone(i2cAddr, ifIndex))
  {
    // To assure current ramping is done
    MxL_DLL_ERROR0("%s - MxL251_Ctrl_WaitUntilIFLevelRampDone failed\n", __FUNCTION__);
    return MXL_FALSE;
  }

  MxL251_Ctrl_ReadRegister(i2cAddr, DFE_DAGCx_SETPT_REG(ifIndex + DFE_IF_BASE), &agcSetPt);  
  MxL_DLL_DEBUG0("%s - configured to %d (current agcSetPt=%d)\n", __FUNCTION__, desiredIfLevel, agcSetPt);
  return MxL251_Ctrl_WriteRegister(i2cAddr, 
                                   MAILBOX_REG_IF0_AGC_SETPT + ifIndex*2, 
                                   desiredIfLevel&0x03FF);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WaitUntilIFLevelRampDone
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Wait until IF level ramping is settled
--|
--| INPUTS        : i2cAddr: i2c slave address of the selected interface
--|                 ifIndex: 0-based IF channel index (0 to 3)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WaitUntilIFLevelRampDone(UINT8 i2cAddr, UINT8 ifIndex)
{
  UINT16 agcSetPt;

  MxL_DLL_DEBUG0("%s - started\n", __FUNCTION__);
  if (0 == MxL251_Ctrl_SpinOnRegField(i2cAddr, 
        MAILBOX_REG_IF0_AGC_SETPT + ifIndex*2, 
        0xFFFF,
        (UINT16)0,
        SPIN_UNTIL_EQ, 
        2000000/*2 seconds*/))
  {
    MxL_DLL_ERROR0("%s - timeout\n", __FUNCTION__);
    return MXL_FALSE;
  }

  MxL251_Ctrl_ReadRegister(i2cAddr, DFE_DAGCx_SETPT_REG(ifIndex + DFE_IF_BASE), &agcSetPt);  

  MxL_DLL_DEBUG0("%s - done (current agcSetPt=%d)\n", __FUNCTION__, agcSetPt);

  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetVcoFreq
--| 
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : Get VCO frequency for corresponding LO frequency
--|
--| RETURN VALUE  : VCO Frequency in Hz
--|
--|-------------------------------------------------------------------------------------*/

UINT64 MxL251_Ctrl_GetVcoFreq(UINT32 fLO)
{
  UINT64 vcoFreq = 0;
#if 1
  UINT8  divShift = 6;
  while ((divShift > 2) && ((fLO>>(6-divShift)) > (SEQ_VHF11HI)))
  {
    divShift--;
  }
  vcoFreq = (((UINT64) fLO)<<divShift);
#endif
  return vcoFreq;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetTunerId
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 6/8/2010
--|                 
--| DESCRIPTION   : Returns WB tunerId configured on chanId
--|
--| RETURN VALUE  : TunerId
--|
--|-------------------------------------------------------------------------------------*/

UINT8 MxL251_Ctrl_GetTunerId(UINT8 chanId)
{
  return ((chanId&3)-1)&1;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_NbChanDisable
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 6/8/2010
--|                 
--| DESCRIPTION   : This API disables one NB chain that comprises of RF circuitry,
--|                 a DEMOD or IF out and put the circutry into low power mode.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/
MXL_STATUS MxL251_Ctrl_NbChanDisable(UINT8 i2cAddr, UINT8 chanId, MXL_BOOL ifRampNeeded)
{
  UINT16          control = 0;
  UINT16          enableMap;
  UINT16          iSelChan = 0;
#ifndef _MXL251_BUILD_
  UINT8           tunerId = MxL251_Ctrl_GetTunerId(chanId);
#endif // _MXL251_BUILD_

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  MxL_DLL_DEBUG0("MXL_TUNER_NB_CHAN_DISABLE_CFG-i2cAddr=0x%x, ChanId=%d\n", i2cAddr, chanId);

  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }

#ifndef _MXL251_BUILD_
  if (devContextPtr->Tuners[tunerId].NbChanFreqInHz == 0)
  {
    MxL_DLL_DEBUG0("ChanId:%d was not enabled before\n", chanId);
  }
  else
  {
    devContextPtr->Tuners[tunerId].NbChanFreqInHz = 0;
    MxL_DLL_DEBUG0("ChanId:%d is disabled\n", chanId);
  }
#endif // _MXL251_BUILD_

  if (MXL_TRUE != MxL251_Ctrl_GetChanXbarEnaRegister(i2cAddr,
        &enableMap))
  {
    return MXL_FALSE;
  }

  if (chanId >= DFE_IF_BASE) 
  {
    MxL251_Ctrl_ReadRegister(i2cAddr, MAILBOX_REG_IF_RAMP_BOTTOM, &(devContextPtr->DAGCBottomSetPt));

    if (0 != (enableMap & DFE_CHN_ENA_BIT(chanId)) && ifRampNeeded == MXL_ENABLE)
    {
      // If this channel was current enabled, ramp it down to lowest
      if (MXL_TRUE != MxL251_Ctrl_SetNewIFLevel(i2cAddr, 
                                                chanId - DFE_IF_BASE, 
                                                devContextPtr->DAGCBottomSetPt))
      {
        MxL_DLL_ERROR0("%s - MxL251_Ctrl_SetNewIFLevel failed\n", __FUNCTION__);
        return MXL_FALSE;
      }
      if (MXL_TRUE != MxL251_Ctrl_WaitUntilIFLevelRampDone(
            i2cAddr, 
            chanId - DFE_IF_BASE))
      {
        MxL_DLL_ERROR0("%s - MxL251_Ctrl_WaitUntilIFLevelRampDone failed\n", __FUNCTION__);
        return MXL_FALSE;
      }
    }
    else
    {
      // If this channel was current disabled, program SETPT register directly
      MxL251_Ctrl_WriteRegister(i2cAddr,
                                DFE_DAGCx_SETPT_REG(chanId), 
                                devContextPtr->DAGCBottomSetPt);
    }
  }

  enableMap &= (0xFF & ~DFE_CHN_ENA_BIT(chanId));

  if (chanId < DFE_IF_BASE && 0 != (enableMap & 0x000F))
  {
    // Disabling one TS channel, and at one TS channel remains enabled
    MxL251_Ctrl_ReadRegisterMask(i2cAddr, DFE_PCH_ISEL_TS_REG, DFE_PCH_ISEL_TS_MASK, &iSelChan);
    iSelChan >>= DFE_PCH_ISEL_TS_SHIFT_BITS;

    if (0 == (enableMap & DFE_CHN_ENA_BIT(iSelChan))) // Current selected channel is diabled
    {
      for (iSelChan = 0; iSelChan < 4; ++iSelChan)
      {
        if (enableMap & (1<<iSelChan))
        {
          MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                        DFE_PCH_ISEL_TS_REG, 
                                        DFE_PCH_ISEL_TS_MASK, 
                                        iSelChan<<DFE_PCH_ISEL_TS_SHIFT_BITS);
          break;
        }
      }
    }
  }
  else if (chanId >= DFE_IF_BASE && 0 != (enableMap & 0x00F0))
  {
    // Disabling one IF channel, and at one IF channel remains enabled
    MxL251_Ctrl_ReadRegisterMask(i2cAddr, DFE_PCH_ISEL_IF_REG, DFE_PCH_ISEL_IF_MASK, &iSelChan);
    iSelChan >>= DFE_PCH_ISEL_IF_SHIFT_BITS;

    if (0 == (enableMap & DFE_CHN_ENA_BIT(iSelChan + DFE_IF_BASE))) // Current selected channel is diabled
    {
      for (iSelChan = 0; iSelChan < 4; ++iSelChan)
      {
        if (enableMap & (1<<(iSelChan + DFE_IF_BASE)))
        {
          MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                        DFE_PCH_ISEL_IF_REG, 
                                        DFE_PCH_ISEL_IF_MASK, 
                                        iSelChan<<DFE_PCH_ISEL_IF_SHIFT_BITS);
          break;
        }
      }
    }
  }

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    // Disable chain
    if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
                                                  DFE_XBAR_CHAN_CFG_REG, 
                                                  DFE_CHN_ENA_BIT(chanId),
                                                  (UINT16)MXL_DISABLE))
    {
      return MXL_FALSE;
    }  
  }

  if (chanId >= DFE_IF_BASE)
  {
    if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
    {  
      // IF channels
      if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
            DFE_UPX_CH_ENAx_REG, 
            DFE_UPX_CH_ENAx_BIT(chanId),
            (UINT16)MXL_DISABLE))   
      {
        return MXL_FALSE;
      }
    }

    if (devContextPtr->ActiveIFMap > 0)
    {
      devContextPtr->ActiveIFMap &= ~(1<<chanId);

      MxL_DLL_DEBUG0("devContextPtr->ActiveIFMap=%d\n", devContextPtr->ActiveIFMap);

      if (0==devContextPtr->ActiveIFMap) // If last IF channel, turn off DAC
      {
        //Ctrl_SetRegFieldControl(i2cAddr, "dig_ana_dac_resetb", (REAL64) 0, (MXL_BOOL) 0);
        //Ctrl_GetRegFieldControl(i2cAddr, "dig_ana_if_spare", &dacSpare);
        //dacSpare = (REAL64) (((UINT16) dacSpare)&0x7F);
        //Ctrl_SetRegFieldControl(i2cAddr, "dig_ana_if_spare", dacSpare, (MXL_BOOL) 0);
        MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DAC_RESETB_REG, DIG_ANA_DAC_RESETB_MASK, (0<<DIG_ANA_DAC_RESETB_SHIFT_BITS));
        MxL251_Ctrl_ReadRegisterMask(i2cAddr, DIG_ANA_IF_SPARE_REG, DIG_ANA_IF_SPARE_MASK, &control);
        control &= (0x7F << DIG_ANA_IF_SPARE_SHIFT_BITS);
        MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_IF_SPARE_REG, DIG_ANA_IF_SPARE_MASK, control);

        //Ctrl_SetRegFieldControl(i2cAddr, "dig_ana_dac_ena", (REAL64) 0, (MXL_BOOL) 0);
        //Ctrl_SetRegFieldControl(i2cAddr, "dig_ana_if_wb_ena", (REAL64) 0, (MXL_BOOL) 0);
        MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DAC_ENA_REG, DIG_ANA_DAC_ENA_MASK, (0<<DIG_ANA_DAC_ENA_SHIFT_BITS));
        MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_IF_WB_ENA_REG, DIG_ANA_IF_WB_ENA_MASK, (0<<DIG_ANA_IF_WB_ENA_SHIFT_BITS));
      }
    }
  }

  if (FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus)
  {
    HOST_COMMAND_T  tunerNbChanDisableCmd;
    // Add Host Command Calling, using mixed command mode  
    FORM_CMD_HEADER(tunerNbChanDisableCmd, HOST_CMD_TUNER_NB_CHAN_DISABLE_CFG, 0, 0);
    // Only pass ChanId parameter to firmware, fill parameter into checkSum field  
    tunerNbChanDisableCmd.payloadCheckSum = (UINT8)chanId;
    // Do not need to read command response from Firmware 
    return MxL251_Ctrl_SendHostCommand(i2cAddr, &tunerNbChanDisableCmd);
  }
  else
  {
    return MXL_TRUE;
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WbTunerDisable
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : WB disable API
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WbTunerDisable(UINT8 i2cAddr, UINT8 tunerId, MXL_BOOL disableAna)
{
  UINT16          regData;
  UINT16          activeIfMap0;
  UINT16          activeIfMap1;
  UINT16          activeChanMap;
  MXL_BOOL        ifRampNeeded;
  UINT8           chanId;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_GetChanXbarEnaRegister(i2cAddr, &regData))
  {
    return MXL_FALSE;
  }

  activeIfMap0 = (~(regData >> 8)) & (regData&0xF0); // active IF channel map on tuner0
  activeIfMap1 =   (regData >> 8)  & (regData&0xF0); // active IF channel map on tuner1

  MxL_DLL_DEBUG0("activeIfMap0=%x activeIfMap1=%x\n", activeIfMap0, activeIfMap1);

  // Check if there are IF channels on both tuners
  ifRampNeeded = ((0 != activeIfMap0) && (0 != activeIfMap1))?MXL_ENABLE:MXL_DISABLE;

  if (0 == tunerId)
  {
    activeChanMap = (~(regData >> 8)) & (regData & 0xFF);
  }
  else
  {
    activeChanMap = ( (regData >> 8)) & (regData & 0xFF);
  }  

  for (chanId = 0; chanId < MAX_NUM_CHANNELS; ++chanId)
  {
    if (activeChanMap & 1)
    {
      MxL251_Ctrl_NbChanDisable(i2cAddr, chanId, ifRampNeeded);
    }
    activeChanMap >>= 1;
  }

  // Ticket #303: VCO avoidance is used even if original tuner has been disabled
  // This change affects backdoor mode only
  // disableAna is almost always true
  if (MXL_BOOL_TRUE != disableAna)
  {
    return MXL_TRUE;
  }

  // Only clear memory variables if the analog is actually disabled
  devContextPtr->Tuners[tunerId].WbCapFreqInHz = 0;
  devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz = 0;

  if (FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus)
  {
    HOST_COMMAND_T  cmd;

    FORM_CMD_HEADER(cmd, HOST_CMD_TUNER_WB_DISABLE_CFG, 0, 0);

    // Pass Tuner ID to firmware
    cmd.payloadCheckSum = (UINT8)(tunerId & 0x0001);
    return MxL251_Ctrl_SendHostCommand(i2cAddr, &cmd);  
  }
  else
  {
#ifdef _DBG_I2C_BACK_DOOR_MODE_  
    // Refer to MaxLinearDataTyps.h for conditional compliation definition
    MxL_DLL_DEBUG0("%s - progamming WB tune disable sequence started.\n", __FUNCTION__);
    SEQ_DisableTuner(i2cAddr, tunerId);
    MxL_DLL_DEBUG0("%s - progamming WB tune disable sequence done.\n", __FUNCTION__);
    return MXL_TRUE;
#else // _DBG_I2C_BACK_DOOR_MODE_
    MxL_DLL_ERROR0("%s - WB tune disable sequence not programmed because firmware is not loaded\n", __FUNCTION__);
    return MXL_FALSE;
#endif // _DBG_I2C_BACK_DOOR_MODE_
  }
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetWbCaptureBw
--|
--| AUTHOR        : Richard Liu
--|
--| DATE CREATED  : 2010/12/24
--|
--| DESCRIPTION   : This function set wide band capture band width according to 
--|                 tuner ID.
--|
--| RETURN VALUE  : None 
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetWbCaptureBw(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT8 wbBwVal)
{
  UINT16 control;
  UINT8 status = MXL_TRUE;
// Remove this function, since FW is doing it
  switch (tunerId)
  {
    case TUNER0:   
      // Set Digital Analog Tuner BW fields , bit <5:4> of DIG_ANA_TUNER0_BW_REG
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ANA_TUNER0_BW_REG, &control);          
      control = (control & (~DIG_ANA_TUNER_BW_MASK)) | (wbBwVal << 4); 
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DIG_ANA_TUNER0_BW_REG, control);
        
      // Set Digital Analog ADC BW fields, bit <15:14> of DIG_ANA_ADC0_BW_REG 
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ANA_ADC0_BW_REG, &control);          
      control = (control & (~DIG_ANA_ADC_BW_MASK)) | (wbBwVal << 14); 
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DIG_ANA_ADC0_BW_REG, control);

      // Set Demod tuner done in DFE, TENTATIVE, remove it later; Set DFE_ADC0_BW fields
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DFE_ADC_BW_REG, &control); 
      // Set DFE_TO_DMDn_TUNER_DONE field as previous process, remove it later
      control = (control & ~DFE_ADC0_BW_MASK) | wbBwVal | 0x01F0;  // Bit <1:0>
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_ADC_BW_REG, control);
      break;

    case TUNER1:   
      // Set Digital Analog Tuner BW fields , bit <5:4> of DIG_ANA_TUNER1_BW_REG
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ANA_TUNER1_BW_REG, &control);          
      control = (control & (~DIG_ANA_TUNER_BW_MASK)) | (wbBwVal << 4); 
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DIG_ANA_TUNER1_BW_REG, control);
        
      // Set Digital Analog ADC BW fields, bit <15:14> of DIG_ANA_ADC1_BW_REG 
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ANA_ADC1_BW_REG, &control);          
      control = (control & (~DIG_ANA_ADC_BW_MASK)) | (wbBwVal << 14); 
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DIG_ANA_ADC1_BW_REG, control);

      // Set Demod tuner done in DFE, TENTATIVE, remove it later; Set DFE_ADC1_BW fields
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DFE_ADC_BW_REG, &control); 
      // Set DFE_TO_DMDn_TUNER_DONE field as previous process, remove it later
      control = (control & ~DFE_ADC1_BW_MASK) | (wbBwVal<<2) | 0x01F0;  // Bit <3:2>
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_ADC_BW_REG, control);
      break;

    default: 
      status = MXL_FALSE;
      break;
  }

  return(MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_WbTunerEnable
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : WB disable API
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_WbTunerEnable(UINT8 i2cAddr, UINT8 tunerId, MXL_TUNER_POWER_MODE_E powerMode, UINT32 wbCapFreqInHz, UINT8 WbCapBwInMHz, MXL_BOOL fastScan)
{
  HOST_COMMAND_T tunerWbCaptureCmd;
  UINT16 control;
  UINT8 status = MXL_TRUE;
  UINT8 wbBwVal;
  UINT16 tzBwBias;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  MxL_DLL_DEBUG0("%s - tunerId=%d powerMode=%u Lo=%uHz, CBW=%uMHz.\n", 
      __FUNCTION__, tunerId, powerMode, wbCapFreqInHz, WbCapBwInMHz);

  // Check if the previous NB or WB tune is done
  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }
  
  devContextPtr->Tuners[tunerId].FastScanEnable = fastScan;
  devContextPtr->Tuners[tunerId].WbCapFreqInHz = wbCapFreqInHz;
  devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz  = WbCapBwInMHz;

  switch (WbCapBwInMHz)
  {
    case WB_96_MHz:  
      wbBwVal = WB_96MHZ_BYTE; 
      break; 

    case WB_48_MHz:  
      wbBwVal = WB_48MHZ_BYTE; 
      break; 

    case WB_16_MHz:  
      wbBwVal = WB_16MHZ_BYTE; 
      break; 
   
    default:
      MxL_DLL_ERROR0("invalid bandwidth mode");
      return MXL_FALSE;
  }

  control = (powerMode == MXL_TUNER_ENABLED_LOWPOWER)?DIG_ANA_DNXx_LNA_BIAS_LOWPOWER_MASK:0;

  tzBwBias = (WbCapBwInMHz == WB_16_MHz)?0:2;

  tzBwBias <<= DIG_ANA_DNXx_TZ_BW_BIAS_LSB;

  switch (tunerId)
  {
    case TUNER0:
      status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
          DIG_ANA_DNX0_LNA_BIAS_REG,
          DIG_ANA_DNXx_LNA_BIAS_LOWPOWER_MASK, 
          control);

      if (IS_ES2_OR_NEWER(devContextPtr))
      {
        status |= MxL251_Ctrl_WriteRegisterMask(
            i2cAddr, 
            DIG_ANA_DNX0_LNA_SPARE_REG, 
            DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/, 
            DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/);

        status |= MxL251_Ctrl_WriteRegisterMask(
            i2cAddr, 
            DIG_ANA_DNX0_LNA_SPARE_REG, 
            DIG_ANA_DNX0_LNA_SPARE_STROBE_MASK/*bit9*/, 
            0/*bit9*/);
      }
      status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
          DIG_ANA_DNX0_TZ_BW_BIAS_REG,
          DIG_ANA_DNXx_TZ_BW_BIAS_MASK, 
          tzBwBias);

      // Write DFE_WB_DIG_GAIN register  
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DFE_WB_DIG_GAIN_REG, &control); 
      control |= WB_TUNER0_DIG_GAIN_WORD;
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_WB_DIG_GAIN_REG, control);

      break;

    case TUNER1: 
      status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
          DIG_ANA_DNX1_LNA_BIAS_REG,
          DIG_ANA_DNXx_LNA_BIAS_LOWPOWER_MASK, 
          control);

      if (IS_ES2_OR_NEWER(devContextPtr))
      {
        status |= MxL251_Ctrl_WriteRegisterMask(
            i2cAddr, 
            DIG_ANA_DNX1_LNA_SPARE_REG, 
            DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/,
            DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/);

        status |= MxL251_Ctrl_WriteRegisterMask(
            i2cAddr, 
            DIG_ANA_DNX1_LNA_SPARE_REG, 
            DIG_ANA_DNX1_LNA_SPARE_STROBE_MASK/*bit9*/, 
            0/*bit9*/);
      }

      status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
          DIG_ANA_DNX1_TZ_BW_BIAS_REG,
          DIG_ANA_DNXx_TZ_BW_BIAS_MASK, 
          tzBwBias); 

      // Write DFE_WB_DIG_GAIN register
      status |= MxL251_Ctrl_ReadRegister(i2cAddr, DFE_WB_DIG_GAIN_REG, &control); 
      control |= WB_TUNER1_DIG_GAIN_WORD;
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_WB_DIG_GAIN_REG, control);
      break;    
    
    default:
      MxL_DLL_ERROR0("invalid tuner id.");
      return MXL_FALSE;
  }

  // Bit 2-0 of WbCapFreqInHz are ignored;
  //
  // WbCapFreqInHz[15-0]  is programmed to ECO5
  // WbCapFreqInHz[31-16] is programmed to ECO6
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, ECO5_REG, (UINT16)((devContextPtr->Tuners[tunerId].WbCapFreqInHz) & 0xFFFF));
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, ECO6_REG, (UINT16)(((devContextPtr->Tuners[tunerId].WbCapFreqInHz) >>16)&0xFFFF));

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
#ifdef _DBG_I2C_BACK_DOOR_MODE_  
    // Refer to MaxLinearDataTyps.h for conditional compliation definition
    MxL_DLL_DEBUG0("%s - progamming WB tune sequence started.\n", __FUNCTION__);
    SEQ_CfgTuner(i2cAddr, 
        tunerId, 
        wbCapFreqInHz,
        wbBwVal);
    MxL_DLL_DEBUG0("%s - progamming WB tune sequence done.\n", __FUNCTION__);
#else // _DBG_I2C_BACK_DOOR_MODE_
    MxL_DLL_ERROR0("%s - WB tune sequence not programmed because firmware is not loaded\n", __FUNCTION__);
#endif // _DBG_I2C_BACK_DOOR_MODE_
  }
  else
  {
    if (!IS_ASIC_TARGET(devContextPtr))
    {
      // For FPGA
      MxL251_Ctrl_SetWbCaptureBw(i2cAddr, (MXL_TUNER_ID_E)tunerId, wbBwVal);
    }
    // Add Host Command Calling, using mixed command mode  
    FORM_CMD_HEADER(tunerWbCaptureCmd, HOST_CMD_TUNER_WB_CAPTURE_TUNE_CFG, 0, 0);
    control =   (((UINT16)tunerId&0x0001) << 0) 
              + (((UINT16)wbBwVal & 0x0003) << 1)
              + (((devContextPtr->Tuners[tunerId].FastScanEnable) == MXL_ENABLE?1:0) << 3);

    // Pass Tuner ID, WbCapBandWidthInMHz, WbCapFreqInMHz to firmware
    tunerWbCaptureCmd.payloadCheckSum = (UINT8)(control&0x00FF);

    // Do not need to read command response from Firmware 
    status |= MxL251_Ctrl_SendHostCommand(i2cAddr, &tunerWbCaptureCmd);
  }

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_NbChannelEnable
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Enable a NB channel
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_NbChannelEnable(UINT8 i2cAddr, UINT8 tunerId, UINT8 chanId, UINT8 bandWidthInMHz, UINT32 centerFrequencyInHz, MXL_BOOL IFOut_Polarity, UINT16 IFOut_SignalLevel, UINT32 IFOut_FreqInHz)
{
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);
  devContextPtr->Tuners[tunerId].BandWidthInMHz = bandWidthInMHz;
  devContextPtr->Tuners[tunerId].NbChanFreqInHz = centerFrequencyInHz;

  MxL_DLL_DEBUG0("%s: channel %d on tuner %d tuned to %d Hz with bw=%d MHz\n", 
      __FUNCTION__, chanId, tunerId, centerFrequencyInHz, bandWidthInMHz);

  /* Strategy, program wb first, then do nb program */
  if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
  {
    return MXL_FALSE;
  }

#if 0
  if (FastScanEnable[tunerId] == MXL_ENABLE)
  {
    // Wait until first AGC
    if (0 == MxL251_Ctrl_SpinOnRegField(i2cAddr, 
          MAILBOX_REG_FAST_WB0_AGC_FIRST+tunerId*2, 
          1,
          0,
          SPIN_UNTIL_EQ,
          500000))
    {
      MxL_DLL_ERROR0("MAILBOX_REG_FAST_WBx_AGC_FIRST timeout");
      return MXL_FALSE;
    }
  }
#endif

  // Set DFE decimation and clock
  if (MXL_TRUE != MxL251_Ctrl_SetFir3Cic2Cic1(i2cAddr,
                                              chanId,
                                              devContextPtr->Tuners[tunerId].WbCapBandWidthInMhz))
  {
    return MXL_FALSE;
  }

  if (chanId >= DFE_IF_BASE)
  {
    if (MXL_TRUE != MxL251_Ctrl_ConfigIF(i2cAddr, chanId, IFOut_Polarity, IFOut_SignalLevel, IFOut_FreqInHz))
    {
      return MXL_FALSE;
    }
  }

  // Configure DFE and XBAR (DFE_CHN_XBAR_SEL)
  if (MXL_TRUE != MxL251_Ctrl_NbTuneCfgDfeXbar(i2cAddr, (MXL_TUNER_ID_E)tunerId, chanId))
  {
    return MXL_FALSE;
  }

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    // No addtional logic is required
  }
  else
  {
    HOST_COMMAND_T tunerNbChanTuneCmd;
    // Add Host Command Calling, using mixed command mode  
    FORM_CMD_HEADER(tunerNbChanTuneCmd, HOST_CMD_TUNER_NB_CHAN_TUNE_CFG, 0, 0);
    // Only pass chanId parameter to firmware, fill parameter into checkSum field  
    tunerNbChanTuneCmd.payloadCheckSum = chanId
                                        + (tunerId<<3) 
                                        + ((bandWidthInMHz==8?1:0)<<4); // To fix item 8
    // Do not need to read command response from Firmware 
    if (MXL_TRUE != MxL251_Ctrl_SendHostCommand(i2cAddr,&tunerNbChanTuneCmd))
    {
      return MXL_FALSE;
    }

    if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
    {
      return MXL_FALSE;
    }
    if (chanId >= DFE_IF_BASE)
    {
      if (MXL_TRUE != MxL251_Ctrl_SetNewIFLevel(i2cAddr, 
                                                chanId - DFE_IF_BASE, 
                                                (UINT16)(IFOut_SignalLevel) & 0x03FF))
      {
        return MXL_FALSE;
      }

      if (MXL_TRUE != MxL251_Ctrl_WaitUntilIFLevelRampDone(i2cAddr, 
                                                           chanId - DFE_IF_BASE))
      {
        return MXL_FALSE;
      }
      
    }
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_MoveWbCenterIfNeeded
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Move WB center if needed
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_MoveWbCenterIfNeeded(PMXL251SF_DEV_CONTEXT_T devContextPtr, UINT8 tunerId, UINT32* wbCapFreqInHzPtr, UINT8* wbCapBwInMHzPtr)
{
  UINT32 wbCapFreqInHz = *wbCapFreqInHzPtr;
  UINT8  wbCapBwInMHz  = *wbCapBwInMHzPtr;
  UINT32 otherLoFreq = devContextPtr->Tuners[1-tunerId].WbCapFreqInHz;
  UINT32 nbBwInHz = (UINT32)(devContextPtr->Tuners[tunerId].BandWidthInMHz) * 1000000;

  // Added tmp variables for fracN avoidance
  UINT32 vcoFreqInMHz;
  UINT32 loDivRatio = MAX_LO_DIV_RATIO;

  if (nbBwInHz == 0)
  {
    // If NB BW is not known on current tuner, use BW from the other tuner 
    nbBwInHz = (UINT32)(devContextPtr->Tuners[1-tunerId].BandWidthInMHz) * 1000000;

    if (nbBwInHz == 0)
    {
      // If NB BW is not know on either tuner, use 6MHz
      nbBwInHz = 6000000;
    }
    devContextPtr->Tuners[tunerId].BandWidthInMHz = nbBwInHz/1000000;
  }

  if (wbCapFreqInHz < 70000000U)
  {
    // For LO lower than 70MHz;
    if (wbCapBwInMHz == WB_16_MHz)
    {
      // For 16MHz and default f_NB at LO+nbBwInHz/2, LO can not move more than 48MHz.
      // So low boundary is (70MHz - 48MHz + 8MHz margin for vco avoidance) = 30MHz
      if (wbCapFreqInHz <= 30000000U)
      {
        MxL_DLL_ERROR0("%s: Cannot tune to %u\n", __FUNCTION__, wbCapFreqInHz);
        return MXL_FALSE;
      }
      // Expand CBW to 96MHz
      wbCapBwInMHz  = WB_96_MHz;
      *wbCapBwInMHzPtr = wbCapBwInMHz;
      MxL_DLL_DEBUG0("LO[%d] has expanded CBW to 96MHz\n", tunerId);

      // move  LO frequency up to the smallest grid that's above 70MHz
      wbCapFreqInHz = wbCapFreqInHz + ((70000000U - wbCapFreqInHz + nbBwInHz - 1)/nbBwInHz)*nbBwInHz;
    }
    else
    {
      MxL_DLL_ERROR0("%s: Cannot tune to CBW=%u\n", __FUNCTION__, wbCapBwInMHz);
      return MXL_FALSE;
    }
  }

  if (otherLoFreq)
  {
    // If the other tuner is tuned, calc difference in VCO frequency
    SINT64 diffVcoFreq = (SINT64)MxL251_Ctrl_GetVcoFreq(wbCapFreqInHz) 
                       - (SINT64)MxL251_Ctrl_GetVcoFreq(otherLoFreq);

    if (diffVcoFreq > -6000000 && diffVcoFreq < 6000000)
    {
      // If VCO frequency difference is within 6MHz, shift it to right by last known NB BW
      // Put LO to the right of channel
      wbCapFreqInHz = wbCapFreqInHz + nbBwInHz;
      // Do not perform bandwidth expansion
    }
  }


  // Include fracN avoidance here
  vcoFreqInMHz = wbCapFreqInHz/(MHZ_1/MAX_LO_DIV_RATIO);
  while ((vcoFreqInMHz > MAX_VCO_FREQ_IN_MHZ) && (loDivRatio))
  {
	  vcoFreqInMHz = (vcoFreqInMHz>>1);
	  loDivRatio = (loDivRatio>>1);
  }
  if ((vcoFreqInMHz > (MAX_VCO_FREQ_AVOID1_IN_MHZ - FRACN_AVOIDANCE_FREQ_LIMIT_MHZ)) 
      && (vcoFreqInMHz < (MAX_VCO_FREQ_AVOID1_IN_MHZ + FRACN_AVOIDANCE_FREQ_LIMIT_MHZ)))
  {
	  wbCapFreqInHz = ((MAX_VCO_FREQ_AVOID1_IN_MHZ*(MHZ_1/SCALE_OVERFLOW_PROTECT))/loDivRatio)*SCALE_OVERFLOW_PROTECT;
  }
  else if ((vcoFreqInMHz > (MAX_VCO_FREQ_AVOID2_IN_MHZ - FRACN_AVOIDANCE_FREQ_LIMIT_MHZ)) 
      && (vcoFreqInMHz < (MAX_VCO_FREQ_AVOID2_IN_MHZ + FRACN_AVOIDANCE_FREQ_LIMIT_MHZ)))
  {
	  wbCapFreqInHz = ((MAX_VCO_FREQ_AVOID2_IN_MHZ*(MHZ_1/SCALE_OVERFLOW_PROTECT))/loDivRatio)*SCALE_OVERFLOW_PROTECT;
  }
  // end fracN avoidance

  if ((*wbCapFreqInHzPtr) != wbCapFreqInHz)
  {
    MxL_DLL_DEBUG0("LO[%d] is moved from %d to %d\n", tunerId, *wbCapFreqInHzPtr, wbCapFreqInHz);
    *wbCapFreqInHzPtr = wbCapFreqInHz;
  }

  return MXL_TRUE;
}


/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConfigTunerOverwriteDefault  
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|
--| DATE CREATED  : 10/17/2010
--|                 12/29/2010
--|
--| DESCRIPTION   : Overwrite default for Tuner. There is separate API for Demod
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ConfigTunerOverwriteDefault(UINT8 i2cAddr)
{
  UINT8 status = MXL_TRUE;
  UINT8 chanId;
  MXL_DEMOD_ID_E demodId;
  MPEG_PAD_DRV_T mpegPadDrv;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  // DFE_RSTN 1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_RESET_REG, DFE_RESETN_MASK, 0x0001);

  // LTSpare to be set to 1
  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // spare[0]: bypass sequencer (leave it as 0)
    // spare[1]: register strobe 0->1 to write
  }
  else
  {
    // spare[0]: release reset for power sequence 
    // spare <1> is used as bypass for RFRSSI buffer sequencer (leave it alone)
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_LT_SPARE_REG, DIG_ANA_LT_SPARE_MASK, 0x0001);
  }

  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_RFRSSI_AVG_SAMP_REG, DFE_RFRSSI_AVG_SAMP_MASK, 0x0600);

  //dig_ana_dnx0_lna_ena      0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX0_LNA_ENA_REG, DIG_ANA_DNX0_LNA_ENA_MASK, (0<<DIG_ANA_DNX0_LNA_ENA_SHIFT_BITS));

  //dig_ana_dnx1_lna_ena      0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX1_LNA_ENA_REG, DIG_ANA_DNX1_LNA_ENA_MASK, (0<<DIG_ANA_DNX1_LNA_ENA_SHIFT_BITS));

  //dig_ana_adc0_resetb     0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC0_RESETB_REG, DIG_ANA_ADC0_RESETB_MASK, (0<<DIG_ANA_ADC0_RESETB_SHIFT_BITS));

  //dig_ana_adc1_resetb     0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC1_RESETB_REG, DIG_ANA_ADC1_RESETB_MASK, (0<<DIG_ANA_ADC1_RESETB_SHIFT_BITS));

  //dig_ana_dac_resetb      0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DAC_RESETB_REG, DIG_ANA_DAC_RESETB_MASK, (0<<DIG_ANA_DAC_RESETB_SHIFT_BITS));

  //dig_ana_adc0_bias     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC0_BIAS_REG, DIG_ANA_ADC0_BIAS_MASK, (1<<DIG_ANA_ADC0_BIAS_SHIFT_BITS));

  //dig_ana_adc0_vcmi     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC0_VCMI_REG, DIG_ANA_ADC0_VCMI_MASK, (1<<DIG_ANA_ADC0_VCMI_SHIFT_BITS));

  //dig_ana_adc0_vref     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC0_VREF_REG, DIG_ANA_ADC0_VREF_MASK, (1<<DIG_ANA_ADC0_VREF_SHIFT_BITS));

  //dig_ana_adc0_spare      4
  // Changed from 4 to 0 (for both ES1 and ES2) 0 to use white sequence for cal
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC0_SPARE_REG, DIG_ANA_ADC0_SPARE_MASK, (0<<DIG_ANA_ADC0_SPARE_SHIFT_BITS));

  //dig_ana_adc1_bias     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC1_BIAS_REG, DIG_ANA_ADC1_BIAS_MASK, (1<<DIG_ANA_ADC1_BIAS_SHIFT_BITS));

  // dig_ana_adc1_vcmi     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC1_VCMI_REG, DIG_ANA_ADC1_VCMI_MASK, (1<<DIG_ANA_ADC1_VCMI_SHIFT_BITS));

  // dig_ana_adc1_vref     1
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC1_VREF_REG, DIG_ANA_ADC1_VREF_MASK, (1<<DIG_ANA_ADC1_VREF_SHIFT_BITS));

  //dig_ana_adc1_spare      4
  // Changed from 4 to 0 (for both ES1 and ES2) 0 to use white sequence for cal
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_ADC1_SPARE_REG, DIG_ANA_ADC1_SPARE_MASK, (0<<DIG_ANA_ADC1_SPARE_SHIFT_BITS));

  //dfe_cdc0_offset_tz_flip     255
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_CDC0_OFFSET_TZ_FLIP_REG, DFE_CDC0_OFFSET_TZ_FLIP_MASK, (0xFF<<DFE_CDC0_OFFSET_TZ_FLIP_SHIFT_BITS));

  //dfe_cdc1_offset_tz_flip     255
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_CDC1_OFFSET_TZ_FLIP_REG, DFE_CDC1_OFFSET_TZ_FLIP_MASK, (0xFF<<DFE_CDC1_OFFSET_TZ_FLIP_SHIFT_BITS));

  //dig_ana_dnx0_rctune     6
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX0_RCTUNE_REG, DIG_ANA_DNX0_RCTUNE_MASK, (6<<DIG_ANA_DNX0_RCTUNE_SHIFT_BITS));

  //dig_ana_dnx1_rctune     6
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX1_RCTUNE_REG, DIG_ANA_DNX1_RCTUNE_MASK, (6<<DIG_ANA_DNX1_RCTUNE_SHIFT_BITS));

  //dig_ana_rfsx0_fdcp_timingmode   160
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_FDCP_TIMINGMODE_REG, DIG_ANA_RFSX0_FDCP_TIMINGMODE_MASK, (0xA0<<DIG_ANA_RFSX0_FDCP_TIMINGMODE_SHIFT_BITS));

  //dig_ana_rfsx1_fdcp_timingmode   160
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_FDCP_TIMINGMODE_REG, DIG_ANA_RFSX1_FDCP_TIMINGMODE_MASK, (0xA0<<DIG_ANA_RFSX1_FDCP_TIMINGMODE_SHIFT_BITS));

  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_FDCP_EXT_BIN_REG, DIG_ANA_RFSX0_FDCP_EXT_BIN_MASK, (0xF<<DIG_ANA_RFSX0_FDCP_EXT_BIN_SHIFT_BITS));

  //dig_ana_rfsx1_fdcp_timingmode   160
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_FDCP_EXT_BIN_REG, DIG_ANA_RFSX1_FDCP_EXT_BIN_MASK, (0xF<<DIG_ANA_RFSX1_FDCP_EXT_BIN_SHIFT_BITS));


  //dig_ana_rfsx0_spare_reg0    66
  // To gate off test mux, and disables oc (offset-correction) in charge pump
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_SPARE_REG0_REG, DIG_ANA_RFSX0_SPARE_REG0_MASK, (0x42<<DIG_ANA_RFSX0_SPARE_REG0_SHIFT_BITS));

  //dig_ana_rfsx1_spare_reg0    66
  // To gate off test mux, and disables oc (offset-correction) in charge pump
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_SPARE_REG0_REG, DIG_ANA_RFSX1_SPARE_REG0_MASK, (0x42<<DIG_ANA_RFSX1_SPARE_REG0_SHIFT_BITS));

  //dig_ana_rfsx0_en_oc_only    0 (works together with spare_reg0)
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_EN_OC_ONLY_REG , DIG_ANA_RFSX0_EN_OC_ONLY_MASK, (0<<DIG_ANA_RFSX0_EN_OC_ONLY_SHIFT_BITS));

  //dig_ana_rfsx1_en_oc_only    0
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_EN_OC_ONLY_REG, DIG_ANA_RFSX1_EN_OC_ONLY_MASK, (0<<DIG_ANA_RFSX1_EN_OC_ONLY_SHIFT_BITS));

  /**
  if ( dig_ana_rfsx0_en_oc_only == 0) dig_ana_rfsx0_sel_6vco does not matter
  **/

  if (IS_ES2_OR_NEWER(devContextPtr))
  {
    // "<7> regulator enable, <2> dac clk flip, <1> reg leak current, <0> unused
    // <6:4> bias ramping DAC value; 111 = max current (needs default overwrite)"

    // - [7]: Regulator disabled (enabled when turning on first IF channel)
    // - [6:4]: Set bias current to max
    // - [0]: unused (leave as 1)
    MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_IF_SPARE        , 113); //    8252, 0, 8
    // The following bits are already cleared in firmware at WB tune time
    // - MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ADC0_CHOP_ENA   , 0);   //    8200, 0, 1 
    // - MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ADC1_CHOP_ENA   , 0);   //    12296, 0, 1 

    // Do not enable the following code until _ADC_TI_CAL_ENABLED_ is enabled
    // NOTE: let firmware control these bits
    //  - MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ADC0_TI_CAL     , 2);   //    8208, 0, 2 
    //  - MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ADC1_TI_CAL     , 2);   //    12304, 0, 2

    // spare<0>=abb_bias_enb, spare<1>=bq1_hbw_ena, spare<2>=bq2_hbw_ena
    MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ABB0_SPARE      , 6);   //    8196, 0, 4 
    MxL251_Ctrl_WriteRegisterField(i2cAddr, DIG_ANA_ABB1_SPARE      , 6);   //    12292, 0, 4 
    // MxL251_Ctrl_WriteRegisterField(i2cAddr, DFE_CDC0_OFFSET_TZ_FLIP , 255); //    16436, 0, 8
    // MxL251_Ctrl_WriteRegisterField(i2cAddr, DFE_CDC1_OFFSET_TZ_FLIP , 255); //    16484, 0, 8 
  }
  else
  {
    // dig_ana_rfsx0_fdcp_ext_sel_bin 15
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_REG, DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_MASK, (15<<DIG_ANA_RFSX0_FDCP_EXT_SEL_BIN_SHIFT_BITS));
    // dig_ana_rfsx1_fdcp_ext_sel_bin 15
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_REG, DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_MASK, (15<<DIG_ANA_RFSX1_FDCP_EXT_SEL_BIN_SHIFT_BITS));

    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX0_CAL_CLKMODE_REG, DIG_ANA_RFSX0_CAL_CLKMODE_MASK, (2<<DIG_ANA_RFSX0_CAL_CLKMODE_SHIFT_BITS));
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_RFSX1_CAL_CLKMODE_REG, DIG_ANA_RFSX1_CAL_CLKMODE_MASK, (2<<DIG_ANA_RFSX1_CAL_CLKMODE_SHIFT_BITS));
  }

  // Disable all DFE NB channels
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_XBAR_CHAN_CFG_REG, DFE_CHN_ENA_ALL_MASK, MXL_DISABLE);

  // Initialize all IF AGC set points to lowest
  for (chanId = DFE_IF_BASE; chanId < (DFE_IF_BASE + MAX_NUM_IF_OUT); ++chanId)
  {
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, DFE_DAGCx_SETPT_REG(chanId), devContextPtr->DAGCBottomSetPt);
  }

  mpegPadDrv.PAD_MPSYN_DRV = MPEG_DRV_MODE_1X;
  mpegPadDrv.PAD_MPDAT_DRV = MPEG_DRV_MODE_1X;
  mpegPadDrv.PAD_MPVAL_DRV = MPEG_DRV_MODE_1X;

  // Set MPEG pad strength to 2X
  for (demodId = DEMOD0; demodId <= DEMOD1; demodId = (MXL_DEMOD_ID_E)(demodId+1))
  {
    status |= MxL251_Ctrl_SetMpegPadDrv(i2cAddr, demodId, &mpegPadDrv);
    status |= MxL251_Ctrl_SetMpegOutEnable(i2cAddr, demodId, MXL_DISABLE);
  }

  // Set MPEG clock drive strength to 2X
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, PAD_MCLK_DRV_REG, PAD_MCLK_DRV_MASK, (MPEG_DRV_MODE_1X<<PAD_MCLK_DRV_SHIFT_BITS));

  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_UploadCustomCoefs
--| 
--| AUTHOR        : Richard Liu, Richard Liu
--|
--| DATE CREATED  : 08/18/2010, 12/30/2010
--|
--| DESCRIPTION   : This function upload custom coefs into demod
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_UploadCustomCoefs(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_ANNEX_TYPE_E annexType, MXL_QAM_TYPE_E qamType)
{
  UINT16* coefPtr = NULL;
  UINT16 temp16;
  UINT8 i;
  UINT8 status = MXL_TRUE;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  MxL_DLL_DEBUG0("MxL251_Ctrl_UploadCustomCoefs - i2cAddr:0x%x demodId:0x%x annexType:0x%x qamType:0x%x\n", i2cAddr, demodId, annexType, qamType);

  devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  /* Disable custom coef enable for safety. After upload, enable it again */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ENA_CFG_REG), &temp16);
  temp16 &= ~(0x4000);
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ENA_CFG_REG), temp16);
    
  /* A. Set the MF_COEF_ADDR register field to 0x0 */
  /* B. Set  MF_AUTO_INC register field to 1 */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ADDR_CFG_REG), &temp16);
  temp16 &= 0x7FC0;
  temp16 |= 0x8000;

  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ADDR_CFG_REG), temp16);
    
  /* C. Upload 48 words coef value */    
  if (annexType == ANNEX_A)
  {
    coefPtr = MxL251_MatchedFilterCoef_AnnexA;
  }
  else
  {
    if (qamType== QAM64)
    {
      coefPtr = MxL251_MatchedFilterCoef_AnnexB64;
    }
    if (qamType == QAM256)
    {
      coefPtr = MxL251_MatchedFilterCoef_AnnexB256;
    }
  }

  if (coefPtr != NULL)
  {    
    for (i=0; i<48; i++)
    {
      status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_DATA_CFG_REG), coefPtr[i]);
    }
  }

  /* D. Set  MF_CUSTOM_COEF_EN register field to 1 */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ENA_CFG_REG), &temp16);
  temp16 |= 0x4000;
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD0_CUSTOM_COEF_ENA_CFG_REG), temp16);

  devContextPtr->Tuners[demodId].Demod.CurQamType   = (UINT8)qamType;
  devContextPtr->Tuners[demodId].Demod.CurAnnexType = (UINT8)annexType;
 
  return (MXL_STATUS)status;
}

/*---------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetMCNSSD
--| 
--| AUTHOR        : Brenndon Lee
--|                 Richard Liu
--|
--| DATE CREATED  : 1/24/2008
--|                 12/21/2010
--|
--| DESCRIPTION   : Read back Counter registers for BER, CER calculation.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetMCNSSD(UINT8 I2cSlaveAddr, MXL_DEMOD_ID_E demodId, UINT8 regCode, UINT32 *dataPtr)
{
  UINT8 status = MXL_TRUE;
  UINT32 tmp;
  UINT16 lsb;
  UINT16 msb;

  switch (regCode)
  {
    case CW_CORR_COUNT:
      /* CW_CORR_COUNT = MSB * 2^16 +  LSB */
      /*  Get LSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG), 
                                          0x0002);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG), 
                                         &lsb);
      /* Get MSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG),
                                          0x0003);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG),
                                         &msb);
      tmp = msb << 16;
      tmp |= lsb;
      break;

    case CW_ERR_COUNT:
      /* CW_ERR_COUNT = MSB * 2^16 +  LSB */
      /* Get LSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG),       
                                          0x0004);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG),       
                                         &lsb);

      /* Get MSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG),       
                                          0x0005);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG),
                                         &msb);

      tmp = msb << 16;
      tmp |= lsb;
      break;

    case CW_COUNT:
      /* CW_COUNT = MSB * 2^16 +  LSB */
      /* Get LSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG),
                                          0x0000);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG),      
                                         &lsb);
      /* Get MSB */
      status |= MxL251_Ctrl_WriteRegister(I2cSlaveAddr, 
                                          MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_SEL_REG),       
                                          0x0001);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr,
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, MCNSSD_REG),
                                         &msb);

      tmp = msb << 16;
      tmp |= lsb;
      break;

    case CORR_BITS:
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, NCBL_REG),       
                                         &lsb);
      status |= MxL251_Ctrl_ReadRegister(I2cSlaveAddr, 
                                         MxL251_Ctrl_ConvertDemodIdToAddr(demodId, NCBH_REG),
                                         &msb);
      msb &= 0x00FF; /* Only 8bit is valid */

      tmp = msb << 16;
      tmp |= lsb;
      break;
    
    default:
      tmp = 0;
      break;
  }

  *dataPtr = tmp;

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetChanXbarEnaRegister
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Get chan xbar and enable register
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetChanXbarEnaRegister(UINT8 i2cAddr, UINT16* regDataPtr)
{
  UINT16 regData;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
        DFE_XBAR_CHAN_CFG_REG,
        regDataPtr))
  {
    return MXL_FALSE;
  }

  if (FIRMWARE_STATUS_LOADED == devContextPtr->FirmwareStatus)
  {
    if (MXL_TRUE != MxL251_Ctrl_ReadRegister(i2cAddr,
          MAILBOX_REG_DFE_ACTIVE_CHAN_MAP,
          &regData))
    {
      return MXL_FALSE;
    }
    *regDataPtr &= 0xFF00;
    *regDataPtr |= (regData&0xFF);
  }
  return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConfigDemodClockEnable
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Config demod clocks
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ConfigDemodClockEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL enable)
{
  UINT8 status = MXL_TRUE;

  if (demodId >= MAX_251SF_DEMODS)
  {
    return MXL_FALSE;
  }

  if (enable == MXL_ENABLE)
  {
    // Enable demod clocks
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                            RegMapDemodClockEnable[demodId].addr,
                                            RegMapDemodClockEnable[demodId].mask, 
                                            RegMapDemodClockEnable[demodId].mask);

    // Restart demod
    status |= MxL251_Ctrl_WriteRegister(i2cAddr,
                                        MxL251_Ctrl_ConvertDemodIdToAddr(demodId, 0x63FC),
                                        0xFFFF);
  }
  else
  {
    // Disable demod clocks
    status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
                                            RegMapDemodClockEnable[demodId].addr,
                                            RegMapDemodClockEnable[demodId].mask, 
                                            0);
  }

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetDemodClockEnable
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Get demod clock enable configuration
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetDemodClockEnable(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId, MXL_BOOL* enablePtr)
{
  UINT8 status = MXL_TRUE;
  UINT16 enable = 0;

  if (demodId >= MAX_251SF_DEMODS)
  {
    return MXL_FALSE;
  }

  status |= MxL251_Ctrl_ReadRegisterMask(i2cAddr, 
                                         RegMapDemodClockEnable[demodId].addr,
                                         RegMapDemodClockEnable[demodId].mask, 
                                         &enable);

  *enablePtr = (RegMapDemodClockEnable[demodId].mask == enable)?MXL_ENABLE:MXL_DISABLE;
  return (MXL_STATUS)status;
}

#ifdef _ENABLE_UART_DEBUG_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_EnableUart
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 12/08/2010
--|
--| DESCRIPTION   : Enable debug UART port
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_EnableUart(UINT8 i2cAddr)
{
  UINT32 i;
  static const UINT16 UartEnableCmds[][2] = {
    {0x0020, 0x0002},
    {0x0028, 0x561f},
    {0x0028, 0x560f},
    {0x1018, 0x0025},
    {0x1034, 0x000e},
    {0x1030, 'U'},
    {0x1030, 'A'},
    {0x1030, 'R'},
    {0x1030, 'T'},
    {0x1030, ' '},
    {0x1030, 'E'},
    {0x1030, 'N'},
    {0x1030, 'A'},
    {0x1030, 'B'},
    {0x1030, 'L'},
    {0x1030, 'E'},
    {0x1030, 'D'},
    {0x1030, '\r'},
    {0x1030, '\n'},
    {0x1000, 0x0115},
  };  

  for (i = 0; i < sizeof(UartEnableCmds)/sizeof(UartEnableCmds[0]); ++i)
  {
    MxL251_Ctrl_WriteRegister(i2cAddr, UartEnableCmds[i][0], UartEnableCmds[i][1]);
  }
  return MXL_TRUE;
}

#endif // _ENABLE_UART_DEBUG_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConfigIF
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 01/26/2010
--|
--| DESCRIPTION   : Config IF
--|
--| RETURN VALUE  : MXL_TRUE for success or MXL_FALSE for failed
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ConfigIF(UINT8 i2cAddr, UINT8 chanId, MXL_BOOL IF_Polarity, UINT16 IF_AgcSetPoint, UINT32 IF_FreqInHz)
{
  UINT32 ifFreqWord;
  UINT16 control = 0;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  // Check if the platform is FPGA or Silicon
  if (IS_ASIC_TARGET(devContextPtr))
  {
    // ES1 or ES2
    ifFreqWord = (IF_FreqInHz + 250000) / 500000;
  }
  else
  {
    // FPGA
    ifFreqWord = (IF_FreqInHz + 125000) / 250000;
  }

  if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
        DFE_UPXx_DDFSWORD_REG(chanId),
        (0xFF<<DFE_UPXx_DDFSWORD_LSB(chanId)), 
        (UINT16)(ifFreqWord<<DFE_UPXx_DDFSWORD_LSB(chanId))))
  {
    return MXL_FALSE;
  }

  if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr,
        DFE_UPXx_NEGATEQ_REG, 
        DFE_UPXx_NEGATEQ_BIT(chanId), 
        IF_Polarity?DFE_UPXx_NEGATEQ_BIT(chanId):0))
  {
    return MXL_FALSE;
  } 

  if (0 == devContextPtr->ActiveIFMap) // If first IF channel, Config IF and DAC
  {
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_IF_WB_ENA_REG, DIG_ANA_IF_WB_ENA_MASK, (1<<DIG_ANA_IF_WB_ENA_SHIFT_BITS));
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_UPX_WBCLK_ENA_REG, DFE_UPX_WBCLK_ENA_MASK, (1<<DFE_UPX_WBCLK_ENA_SHIFT_BITS));
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DAC_ENA_REG, DIG_ANA_DAC_ENA_MASK, (1<<DIG_ANA_DAC_ENA_SHIFT_BITS));

    MxL251_Ctrl_ReadRegisterMask(i2cAddr, DIG_ANA_IF_SPARE_REG, DIG_ANA_IF_SPARE_MASK, &control);

    control |= (0x80<<DIG_ANA_IF_SPARE_SHIFT_BITS);
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_IF_SPARE_REG, DIG_ANA_IF_SPARE_MASK, control);
    MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DAC_RESETB_REG, DIG_ANA_DAC_RESETB_MASK, (1<<DIG_ANA_DAC_RESETB_SHIFT_BITS));
  }

  devContextPtr->ActiveIFMap |= (1<<chanId);

  if (FIRMWARE_STATUS_LOADED != devContextPtr->FirmwareStatus)
  {
    // If firmware is not loaded, program dfe_upx_ch_ena field to enable IF Channel
    if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
          DFE_UPX_CH_ENAx_REG,
          DFE_UPX_CH_ENAx_BIT(chanId),
          DFE_UPX_CH_ENAx_BIT(chanId)))
    {
      return MXL_FALSE;
    } 

    if (MXL_TRUE != MxL251_Ctrl_WriteRegister(i2cAddr, 
          DFE_DAGCx_SETPT_REG(chanId),
          (UINT16)(IF_AgcSetPoint) & 0x03FF))
    {
      return MXL_FALSE;
    }
  }

  if (MXL_TRUE != MxL251_Ctrl_WriteRegisterMask(i2cAddr, 
        DFE_UPX_CLK_ENAx_REG,
        DFE_UPX_CLK_ENAx_BIT(chanId),
        DFE_UPX_CLK_ENAx_BIT(chanId)))
  {
    return MXL_FALSE;
  }

  return MXL_TRUE;

}

#ifdef _BOOT_SCAN_ENABLED_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_CalcXCovar
--| 
--| AUTHOR        : Sridhar Ramesh
--|
--| DATE CREATED  : 11/05/2010
--|
--| DESCRIPTION   : Cross-covariance. Used for linear curve fit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
SINT32 MxL251_Ctrl_CalcXCovar(UINT16 *dataSet1, UINT16 *dataSet2, UINT16 dataSize)
#else
REAL32 MxL251_Ctrl_CalcXCovar(UINT16 *dataSet1, UINT16 *dataSet2, UINT16 dataSize)
#endif
{
  UINT16 ii;
#ifdef _MXL251_FIXEDPOINT_
  UINT64 meanSet1 = 0.0;
  UINT64 meanSet2 = 0.0;
  UINT64 xProduct12 = 0.0;
#else
  REAL32 meanSet1 = 0.0;
  REAL32 meanSet2 = 0.0;
  REAL32 xProduct12 = 0.0;
#endif

#ifdef _MXL251_FIXEDPOINT_
  for (ii = 0; ii < dataSize; ii++)
  {
    meanSet1   += dataSet1[ii];
    meanSet2   += dataSet2[ii];
    xProduct12 += dataSet2[ii]*dataSet1[ii];
  }
  meanSet1   = MXL_DIV_SCALE64(meanSet1, dataSize, MXL251_PRECISION);
  meanSet2   = MXL_DIV_SCALE64(meanSet2, dataSize, MXL251_PRECISION);
  xProduct12 = MXL_DIV_SCALE64(xProduct12, dataSize, MXL251_PRECISION);

#else
  for (ii = 0; ii < dataSize; ii++)
  {
    meanSet1   += ((REAL32) dataSet1[ii]);
    meanSet2   += ((REAL32) dataSet2[ii]);
    xProduct12 += ((REAL32) (dataSet2[ii]*dataSet1[ii]));
  }
  meanSet1   /= (REAL32)dataSize;
  meanSet2   /= (REAL32)dataSize;
  xProduct12 /= (REAL32)dataSize;
#endif

#ifdef _MXL251_FIXEDPOINT_
  return((SINT64)(xProduct12 - MXL_MUL64(meanSet1, meanSet2, MXL251_PRECISION)));
#else
  return(xProduct12 - meanSet1*meanSet2);
#endif
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_GetDigRSSI
--| 
--| AUTHOR        : Sridhar Ramesh
--|
--| DATE CREATED  : 11/05/2010
--|
--| DESCRIPTION   : Gets DIG RSSI value
--|
--| RETURN VALUE  : Status
--|
--|-------------------------------------------------------------------------------------*/

UINT16 MxL251_Ctrl_MxLGetDigRSSI(UINT8 I2cSlaveAddr, MXL_TUNER_ID_E tId)
{
  UINT16 dig_rssi;
  UINT16 bkOff;

  MxL251_Ctrl_ReadRegister(I2cSlaveAddr, ADCx_RSSI_RB_REG(tId), &(dig_rssi)); 
  //MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - RAW ADC_RSSI = %f \n", dig_rssi*0.0625);

  MxL251_Ctrl_ReadRegisterMask(I2cSlaveAddr, DFE_AGC_RF1_BO_REG, ((1<<DFE_AGC_RF1_BO_NBITS)-1), &bkOff);
  MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - RF1 BO = %d \n", (bkOff>>DFE_AGC_RF1_BO_LSB));
  dig_rssi += 16*(bkOff>>DFE_AGC_RF1_BO_LSB);

  MxL251_Ctrl_ReadRegisterMask(I2cSlaveAddr, DFE_AGC_LNA_x_BO_REG(tId), DFE_AGC_LNA_x_BO_MASK(tId), &bkOff);
  MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - LNA BO = %d \n", (bkOff>>DFE_AGC_LNA_x_BO_LSB(tId)));
  dig_rssi += 16*(bkOff>>DFE_AGC_LNA_x_BO_LSB(tId));

  MxL251_Ctrl_ReadRegisterMask(I2cSlaveAddr, DFE_AGC_RF2_x_BO_REG, (DFE_AGC_RF2_x_BO_LSB(tId)<<DFE_AGC_RF2_x_BO_NBITS)-DFE_AGC_RF2_x_BO_LSB(tId), &bkOff);
  MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - RF2 BO = %d \n", (bkOff>>(DFE_AGC_RF2_x_BO_LSB(tId))));
  dig_rssi += 16*(bkOff>>(DFE_AGC_RF2_x_BO_LSB(tId)));

  //MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - CAPTURE BW RSSI = %f \n", dig_rssi*0.0625);

  return dig_rssi;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_BootScan - MXL_DEV_BOOTSCAN
--| 
--| AUTHOR        : Sridhar Ramesh
--|
--| DATE CREATED  : 11/04/2010
--|
--| DESCRIPTION   : Perform start-up plant scan
--|                 Can give tunerID and captureBW as arguments. 
--|                 Set tunerID to 0xFF for autoselect
--|                 Set captureBW to 0xFF for autoselect
--|
--| RETURN VALUE  : Status
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_BootScan(UINT8 i2cAddr, MXL_TUNER_ID_E tunerId, UINT8 captureBW)
{
  UINT8 capBWInMhz;
  // Determine starting Center Frequency
  UINT32 tuneCenterFreq = BOOT_SCAN_FREQ_START + captureBW/2;
  UINT16 tuneCount;
#ifdef _MXL251_FIXEDPOINT_
  SINT64 varFreq;
#else
  REAL32 varFreq;
#endif

  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  if (0xFF==tunerId)
  {
    tunerId = TUNER0;
  }

  if (0xFF==captureBW)
  {
    capBWInMhz = WB_48_MHz;
  }
  else
  {
    capBWInMhz = captureBW;
  }

  tuneCount = 0;

  while (tuneCenterFreq < BOOT_SCAN_FREQ_STOP)
  {

    MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - i2cAddr=0x%x : Freq = %d MHz\n", i2cAddr, tuneCenterFreq);

    devContextPtr->BootScan.wbFreq[tuneCount] = tuneCenterFreq;

    tuneCenterFreq += (UINT32)capBWInMhz;

    MxL251_Ctrl_WbTunerEnable(i2cAddr, tunerId, MXL_TUNER_ENABLED_NORMAL, tuneCenterFreq*1000000, capBWInMhz, MXL_DISABLE/*fastScan*/);

    if (MXL_TRUE != MxL251_WaitForHostCommandToComplete(i2cAddr))
    {
      return MXL_FALSE;
    }
    //MxL251_Ctrl_WriteRegisterMask(i2cAddr, DFE_AGC_LNA_x_BO_REG(tunerId), DFE_AGC_LNA_x_BO_MASK, (8<<DFE_AGC_LNA_x_BO_LSB));
    //MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, 1, 0);
    //MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, 1, 1);
    //MxL251_Ctrl_WriteRegisterMask(i2cAddr, AGC_APPLY_GAIN_REG, 1, 0);

    devContextPtr->BootScan.adcRssi[tuneCount] = MxL251_Ctrl_MxLGetDigRSSI(i2cAddr, tunerId);
    if (devContextPtr->BootScan.adcRssi[tuneCount] > BOOT_SCAN_MIN_VALID_RSSI)
    {
      tuneCount++;
    }
  }

  devContextPtr->BootScan.estimatedTilt = 0.0;

  varFreq = MxL251_Ctrl_CalcXCovar(devContextPtr->BootScan.wbFreq, devContextPtr->BootScan.wbFreq, tuneCount);
#ifdef _MXL251_FIXEDPOINT_
  if(varFreq != 0)
#else
  if (!MXL_IS_REAL32_ZERO(varFreq))
#endif
  {
    // covar(devContextPtr->BootScan.wbFreq, devContextPtr->BootScan.wbFreq) should never be 0, but check it to make sure
#ifdef _MXL251_FIXEDPOINT_
    SINT64 temp = MxL251_Ctrl_CalcXCovar(devContextPtr->BootScan.adcRssi, devContextPtr->BootScan.wbFreq, tuneCount);
	temp = -1 * MXL_DIV_SCALE64_S(temp, varFreq, MXL251_PRECISION);
	devContextPtr->BootScan.estimatedTilt = temp;
#else
    devContextPtr->BootScan.estimatedTilt = -(MxL251_Ctrl_CalcXCovar(devContextPtr->BootScan.adcRssi, devContextPtr->BootScan.wbFreq, tuneCount))/varFreq;
#endif
  }

  //MxL_DLL_DEBUG0("MXL_DEV_BOOTSCAN_CFG - ESTIMATED TILT = %f dB/GHz \n", devContextPtr->BootScan.estimatedTilt*62.50);

  MxL251_Ctrl_WbTunerDisable(i2cAddr, tunerId, MXL_BOOL_TRUE/*disableAna*/);

  return MXL_TRUE;
}

#endif // _BOOT_SCAN_ENABLED_

#ifdef _DYNAMIC_VCO_THRESHOLD_ENABLED_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetRfSx0SynthCal
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 02/27/2011
--|
--| DESCRIPTION   : Get ANA_DIG_RFSX0_RDBK_SYNTHCAL
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_GetRfSx0SynthCal(UINT8 i2cAddr, UINT16* synthCalPtr)
{
  UINT16 adjust = 0;
  UINT8  status = MXL_TRUE;

#ifdef _DEBUG_VCO_THRESHOLD_ENABLED_
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, 0x0004, &adjust);
#endif // _DEBUG_VCO_THRESHOLD_ENABLED_

  status |= MxL251_Ctrl_ReadRegisterMask(
        i2cAddr, 
        ANA_DIG_RFSX0_RDBK_SYNTHCAL_REG, 
        ANA_DIG_RFSX0_RDBK_SYNTHCAL_MASK, // 0x03FF, aligned to LSB
        synthCalPtr);

  *synthCalPtr += adjust;

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_SetVcoThreshold
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 02/27/2011
--|
--| DESCRIPTION   : Set VCO Threshold
--|
--| RETURN VALUE  : Always MXL_TRUE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_SetVcoThreshold(UINT8 i2cAddr)
{
  UINT16 regData;
  UINT8  status = MXL_TRUE;
  PMXL251SF_DEV_CONTEXT_T devContextPtr = MxL251_Ctrl_GetDeviceContext(i2cAddr);

  // This function will be called on ES2 only
  devContextPtr->vcoThresholdInMHz = 3600; // Initilize default BN = 3.6GHz.

  // Tune LO = 3.59GHz/4 = 897.5MHz
  status |= MxL251_Ctrl_WbTunerEnable(i2cAddr, TUNER0, MXL_TUNER_ENABLED_NORMAL, 897500000, WB_96_MHz, MXL_DISABLE/*fastScan*/);

  // Wait until host command done
  status |= MxL251_WaitForHostCommandToComplete(i2cAddr);

  if (MXL_TRUE == status)
  {
    status |= MxL251_Ctrl_GetRfSx0SynthCal(i2cAddr, &regData);

	// Wait until WBVGA locked
    MxL251_Ctrl_SpinOnRegField(i2cAddr, 
                               MAILBOX_REG_AFEAGC_WBVGA0_LOCK, 
                               0xFFFF,
                               (UINT16)0,
                               SPIN_UNTIL_NEQ, 
                               1000000/*1 seconds*/);

    // Do second tune any way
    status |= MxL251_Ctrl_WbTunerEnable(i2cAddr, TUNER0, MXL_TUNER_ENABLED_NORMAL, 902500000, WB_96_MHz, MXL_DISABLE/*fastScan*/);

    if (regData > 1000)
    {
      devContextPtr->vcoThresholdInMHz = 3450;
    }
    else
    {
      // Tune LO = 3.61GHz/4 = 902.5MHz

      // Wait until host command done
      status |= MxL251_WaitForHostCommandToComplete(i2cAddr);

      status |= MxL251_Ctrl_GetRfSx0SynthCal(i2cAddr, &regData);

      if (MXL_TRUE == status && regData < 100)
      {
        devContextPtr->vcoThresholdInMHz = 3750;
      }
    }
  }

  status |= MxL251_Ctrl_WbTunerDisable(i2cAddr, TUNER0, MXL_BOOL_TRUE/*disableAna*/);

  if (MXL_TRUE == status)
  {
    status |= MxL251_Ctrl_WriteRegister(i2cAddr, MAILBOX_REG_VCO_TRHSH_IN_MHZ, devContextPtr->vcoThresholdInMHz);
  }

  // Alway return true
  return MXL_TRUE; // (MXL_STATUS)status;
}
#endif // _DYNAMIC_VCO_THRESHOLD_ENABLED_

#ifdef _MXL_API_DEBUG_ENABLED_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_PrintWithTime 
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 01/10/2011
--|
--| DESCRIPTION   : Print message with time stamp
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_PrintWithTime(SINT8 *pFormat, ...)
{
  va_list argP;
  UINT64 us;
  MxL251_Ctrl_GetCurrTimeInUsec(&us);
  va_start(argP, pFormat);

  printtk("%u ms: ", (UINT32)us/1000);

  vprintf(pFormat, argP);
  va_end(argP);
  return MXL_TRUE;
}

#endif // _MXL_API_DEBUG_ENABLED_

#ifdef _MXL251_BUILD_
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetDemodChanId
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/10/2011
--|
--| DESCRIPTION   : Get index of DEMOD channel based on tunerId
--|
--| RETURN VALUE  : channel id for the specified demod channel
--|
--|-------------------------------------------------------------------------------------*/

UINT8 MxL251_Ctrl_GetDemodChanId(MXL_TUNER_ID_E tunerId)
{
  return (tunerId+1);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetIFChanId
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/10/2011
--|
--| DESCRIPTION   : Get index of IF channel based on tunerId
--|
--| RETURN VALUE  : channel id for the specified IF channel
--|
--|-------------------------------------------------------------------------------------*/

UINT8 MxL251_Ctrl_GetIFChanId(MXL_TUNER_ID_E tunerId)
{
  return (tunerId+5);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConvertDemodIdToChanId
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/10/2011
--|
--| DESCRIPTION   : Convert demod id into channel id
--|
--| RETURN VALUE  : channel id for the specified demod channel
--|
--|-------------------------------------------------------------------------------------*/
UINT8 MxL251_Ctrl_ConvertDemodIdToChanId(MXL_DEMOD_ID_E demodId)
{
  return (demodId+1);
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_GetDemodId
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/10/2011
--|
--| DESCRIPTION   : Get DEMOD ID based on tunerId
--|
--| RETURN VALUE  : Demod ID (DEMOD0 or DEMOD1) for the specified demod channel
--|
--|-------------------------------------------------------------------------------------*/

MXL_DEMOD_ID_E MxL251_Ctrl_GetDemodId(MXL_TUNER_ID_E tunerId)
{
  return (MXL_DEMOD_ID_E)(tunerId);
}
#endif // _MXL251_BUILD_

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_ConfigDemodEqualizer
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/20/2011
--|
--| DESCRIPTION   : Config Demod equalizer
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_ConfigDemodEqualizer(PMXL_SYMBOL_RATE_T symbolRatePtr)
{
  UINT8 status = MXL_TRUE;

  PREG_CTRL_INFO_T programDataPtr = NULL;

#ifdef _OOB_SUPPORT_ENABLED_
  if (SYM_TYPE_OOB == symbolRatePtr->SymbolType)
  {
    switch (symbolRatePtr->OobSymbolRate)
    {
      case SYM_RATE_0_772MHz:
        programDataPtr = MxL251_DemodEqualizerSpeedUpOob_0_772MHz;
        break;

      case SYM_RATE_1_024MHz:
        programDataPtr = MxL251_DemodEqualizerSpeedUpOob_1_024MHz;
        break;

      case SYM_RATE_1_544MHz:
        programDataPtr = MxL251_DemodEqualizerSpeedUpOob_1_544MHz;
        break;

      default:
        return MXL_FALSE;
    }
  }
  else
#endif // _OOB_SUPPORT_ENABLED_
  {
    programDataPtr = MxL251_DemodEqualizerSpeedUp;
  }

  status |= MxL251_Ctrl_ProgramRegisters(symbolRatePtr->I2cSlaveAddr, symbolRatePtr->DemodId, programDataPtr);

  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_TunerStandby
--| 
--| AUTHOR        : Jun Huang
--|
--| DATE CREATED  : 06/22/2011
--|
--| DESCRIPTION   : Turn off both tuners
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_TunerStandby(UINT8 i2cAddr)
{
  UINT8 status = MXL_TRUE;
  status |= MxL251_WaitForHostCommandToComplete(i2cAddr);
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_TUNER0_ENA_REG, DIG_ANA_TUNER0_ENA_MASK, 0);
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_TUNER1_ENA_REG, DIG_ANA_TUNER1_ENA_MASK, 0);
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX0_LNA_ENA_REG, DIG_ANA_DNX0_LNA_ENA_MASK, 0);
  status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_DNX1_LNA_ENA_REG, DIG_ANA_DNX1_LNA_ENA_MASK, 0);
  return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_RestartDemod - MXL_DEMOD_RESTART_CFG
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

MXL_STATUS MxL251_Ctrl_DemodRestart(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId)
{
  UINT8  status = MXL_TRUE;

  // Restart demod, Do this after annex type config
  status |= MxL251_Ctrl_WriteRegister(i2cAddr,
                               MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD_RESTART_REG),
                               0xFFFF);
  return (MXL_STATUS)status;
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

MXL_STATUS MxL251_Ctrl_DemodInvertSpecrum(UINT8 i2cAddr, MXL_DEMOD_ID_E demodId)
{
  UINT8   status = MXL_TRUE;
  UINT16  regData;
  UINT16  regDataCo;
  
  MxL_DLL_DEBUG0("MXL_DEMOD_INVERT_SPECTRUM_CFG- i2cAddr=0x%x, DemodId=%d\n", 
                  i2cAddr, demodId);

  /* Set Carrier Offset Address */ 
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, 
                               MxL251_Ctrl_ConvertDemodIdToAddr(demodId, CARRIER_OFFSET_REG), 
                               0x0087);
  
  /* Read Carrier Offset */ 
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(demodId, CARRIER_OFFSET_RB_REG), 
                              &regDataCo);

  /* Toggle flipping ADC I/Q channels */
  status |= MxL251_Ctrl_ReadRegister(i2cAddr, DIG_ADCIQ_FLIP_REG, &regData);
  regData ^= (DEMOD0_IQ_FLIP << MxL251_Ctrl_ConvertDemodIdToChanId(demodId));
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, DIG_ADCIQ_FLIP_REG, regData);
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(demodId, DEMOD_RESTART_REG), 
                              0xFFFF);
  /* Flip and write Carrier Offset */ 
  status |= MxL251_Ctrl_WriteRegister(i2cAddr, 
                              MxL251_Ctrl_ConvertDemodIdToAddr(demodId, CARRIER_OFFSET_RB_REG), 
                              (UINT16)(-(SINT16)regDataCo));

  return (MXL_STATUS)status;
}
  
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_DeviceStandby
--| 
--| AUTHOR        : SidS
--|
--| DATE CREATED  : 06/22/2011
--|
--| DESCRIPTION   : Config device to standby
--|                 Turn off all nb channels, demod, mpegout, tuners, splitter
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxL251_Ctrl_DeviceStandby(UINT8 i2cAddr)
{
  UINT8 status = MXL_TRUE;
  MXL_TUNER_ID_E tunerId;

  for (tunerId = TUNER0; tunerId <= TUNER1; tunerId = (MXL_TUNER_ID_E)(tunerId+1))
  {
    // Disable all NB channels
    status |= MxL251_Ctrl_NbChanDisable(i2cAddr, MxL251_Ctrl_GetIFChanId(tunerId), MXL_ENABLE/*ramp*/);
    status |= MxL251_Ctrl_NbChanDisable(i2cAddr, MxL251_Ctrl_GetDemodChanId(tunerId), MXL_ENABLE/*ramp*/);
    /* Disable MPEG and OOB OUT */
    status |= MxL251_Ctrl_SetMpegOutEnable(i2cAddr, MxL251_Ctrl_GetDemodId(tunerId), MXL_DISABLE);
    /* Disable DEMOD */
    status |= MxL251_Ctrl_ConfigDemodClockEnable(i2cAddr, MxL251_Ctrl_GetDemodId(tunerId), MXL_DISABLE);
    /* Disable tuner */
    status |= MxL251_Ctrl_WbTunerDisable(i2cAddr, tunerId, MXL_BOOL_TRUE/*disableAna*/); 
  }

  // Turn off both tuners
  status |= MxL251_Ctrl_TunerStandby(i2cAddr);

    /* Disable splitter */
      status |= MxL251_Ctrl_WriteRegisterMask(i2cAddr, DIG_ANA_SPLT_ENA_REG, DIG_ANA_SPLT_ENA_MASK, (0<<DIG_ANA_SPLT_ENA_SHIFT_BITS));
        return (MXL_STATUS)status;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxL251_Ctrl_10Log
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/04/2015
--|
--| DESCRIPTION   : Calculate y=log(x)
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-------------------------------------------------------------------------------------*/
#ifdef _MXL251_FIXEDPOINT_
MXL_STATUS MxL251_Ctrl_10Log(UINT32 in, UINT32* out)
{
  MXL_STATUS status = MXL_TRUE;
  UINT32 coef[5] = {24,190,627,1213,752};
  UINT32 B, tmp, temp[4]; 
  SINT16 m = 0, n = 0;
  // Calculation principle is 
  // log(x) = log(B*1024)  // B blongs to [1,2)
  //        = a1*B^4 + a2*B^3 + a3*B^2 + a4*B + a5
  // while a1 = -0.0238 
  //       a2 = 0.1893
  //       a3 = -0.6266
  //       a4 = 1.2128
  //       a5 = -0.7516
  
  if(in <= 0) return MXL_FALSE;
  
  if(in <=1000)
  {
    tmp = in; 
    while(tmp < 1000)
    {
      tmp = tmp<<1; 
      n--;
    }
    m = 3; 
    in = tmp;
  }
  else 
  {
    m = 3; 
    tmp = in /1000; 
    while(tmp>=2)
    {
      tmp = tmp>>1; 
      n++;
    }
    if (n>0) tmp = in >> n;
    else tmp = in;
  }

  // make input as x.xxx format 
  Ctrl_MulDiv32Bit(tmp, tmp, 1000, &B);  // B*B/1000
  Ctrl_MulDiv32Bit(coef[3], tmp, 1000, &temp[3]);  // coef has been multipled 1000 times 
  Ctrl_MulDiv32Bit(coef[2], B, 1000, &temp[2]);
  Ctrl_MulDiv32Bit(B, tmp, 1000, &B);  // B*B*B/(1000*1000) 
  Ctrl_MulDiv32Bit(coef[1], B, 1000, &temp[1]);
  Ctrl_MulDiv32Bit(B, tmp, 1000, &B);  // B*B*B*B/(1000*1000*1000) 
  Ctrl_MulDiv32Bit(coef[0], B, 1000, &temp[0]);

  *out = m*1000+n*301-coef[4]+temp[1]+temp[3]-temp[0]-temp[2]; 

  return status;
}
#else  
MXL_STATUS MxL251_Ctrl_10Log(REAL32 in, REAL32* out) 
{
  MXL_STATUS status = MXL_TRUE;
  UINT16 m = 0, n = 0;
  REAL64 coef[6] = {0.30102,-0.0238,0.1893,-0.6266,1.2128,-0.7516};
  REAL64 tmp, B; 
  // Calculation principle is 
  // log(x) = log(10^m*2^n*B)  // B blongs to [1,2)
  //        = m + nlog(2) + log(B)
  //        = m + 0.30102n + a1*B^4 + a2*B^3 + a3*B^2 + a4*B + a5
  // while a1 = -0.0238 
  //       a2 = 0.1893
  //       a3 = -0.6266
  //       a4 = 1.2128
  //       a5 = -0.7516
  
  if(in <= 0) return MXL_FALSE;

  // calculate m,n
  tmp = in; 
  while(tmp>=10)
  {
    tmp = tmp /10.0; 
    m++;
  }
  while(tmp>=2)
  {
    tmp = tmp /2.0; 
    n++;
  }
  B = tmp; 
  *out = (REAL32)(m + coef[0]*n + coef[1]*(B*B*B*B) + coef[2]*(B*B*B) 
             + coef[3]*(B*B) + coef[4]*B + coef[5]);

  return status;
}
#endif 

/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_MulDiv32Bit
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 12/09/2009
--|
--| DESCRIPTION   : Complete a*b/c calculation (all are 32bit integers) 
--|                 The principle is:
--|                  MulData1 = (b1*2^p1) + r1  
--|                  MulData2 = (b2*2^p2) + r2  
--|                  Result = MulData1 * MulData2 / DivData
--|                  RetVal1 = (b1*2^p1) * (b2*2^p2) / (b3*2^p3) 
--|                  RetVal2 = (b1*2^p1) * r2 / (b3*2^p3) 
--|                  RetVal3 = r1 * (b2*2^p2) / (b3*2^p3) 
--|                  Result = RetVal1 + RetVal2 + RetVal3
--|---------------------------------------------------------------------------*/

MXL_STATUS Ctrl_MulDiv32Bit(UINT32 MulData1, UINT32 MulData2, UINT32 DivData, UINT32* RtnVal)
{
  UINT32 RetVal1,RetVal2,RetVal3; 
  UINT16 b1,b2,b3;
  SINT16 p1,p2,p3;
  UINT16 r1=0,r2=0;

  Ctrl_Decomp32Bit(MulData1,&b1,&p1);
  if (p1 > 0) r1 = (UINT16)MulData1 - (b1 << p1);

  Ctrl_Decomp32Bit(MulData2,&b2,&p2);
  if (p2 > 0) r2 = (UINT16)MulData2 - (b2 << p2);

  Ctrl_Decomp32Bit(DivData,&b3,&p3);
      
  Ctrl_SubMulDiv(b1,b2,b3,p1,p2,p3,&RetVal1);
  Ctrl_SubMulDiv(b1,r2,b3,p1,0,p3,&RetVal2);
  Ctrl_SubMulDiv(r1,b2,b3,0,p2,p3,&RetVal3);

  *RtnVal = RetVal1 + RetVal2 + RetVal3;

  return (MXL_TRUE);
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_SubMulDiv
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 12/09/2009
--|
--| DESCRIPTION   : Complete the calculation  
--|                 RetVal = (b1*2^p1) * (b2*2^p2) / (b3*2^p3) 
--|                        = ( b1*b2/b3)*2^(p1+p2-p3) 
--|  
--|---------------------------------------------------------------------------*/

MXL_STATUS Ctrl_SubMulDiv(UINT16 b1,UINT16 b2,UINT16 b3,SINT16 p1,SINT16 p2,SINT16 p3,UINT32 *RetVal)
{
  SINT16 p4;
  UINT32 b4,b5; 

  p4 = p1 + p2 - p3;

  if ((p4 >= 32) && (p3 < 0))
  {
    p4 = p1 + p2; // Because of p3 <0, hence force p3 = 0 
    b5 = b3 >> (-p3);
  }
  else if ((p4 <= -32) && (p3 > 0))
  {
    p4 = p1 + p2; // Because of p3 >0, force p3 = 0 
    b5 = (UINT32)b3 << p3;
  }
  else b5 = b3;
 
  if (p4 > 0) 
  { 
    if (Ctrl_HighBit(b5) > p4)
    {
      b5 = (UINT32)(b5 >> p4);
      *RetVal = (UINT32)b1 * b2 / b5;       
    }
    else 
    {
      b4 = (UINT32)b1 * b2 / b5;
      *RetVal = (UINT32)(b4 << p4);
    }
  }
  else 
  {    
    b4 = (UINT32)b1 * b2 / b5;
    p4 = - p4;
    // Round operation
    if ( Ctrl_HighBit(b4)+1 == p4 && p4 >1 )
      b4 = b4 + (b4 >> 1);

    *RetVal = (UINT32)(b4 >> p4);
   }
   return(MXL_TRUE);
}
/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_Decomp32Bit
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/27/2015
--|
--| DESCRIPTION   : Decompose 32 bit unsigned integer into a power(16 bit Signed) 
--|                 and basis (16 bit unsigned integer). In = b*Power(2,p);
--|  
--|---------------------------------------------------------------------------*/

MXL_STATUS Ctrl_Decomp32Bit(UINT32 In, UINT16* b, SINT16* p)
{
  UINT16 Bas;
  SINT16 Pwr;
  UINT8 NonZeroP=31; 
  
  NonZeroP = Ctrl_HighBit(In);

  if (NonZeroP > 15) 
  { 
    Pwr = NonZeroP - 15;
    Bas = (UINT16)((In >> Pwr) & 0x0000FFFF); 
  }
  else if (NonZeroP <15)
  {
    Pwr =  NonZeroP -15;
    Bas = (UINT16)((In << (15-NonZeroP)) & 0x0000FFFF);
  }
  else 
  { 
    Pwr = 0;
    Bas = (UINT16)In; 
  }

  * b = Bas;
  * p = Pwr;

  return(MXL_TRUE);
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_HighBit
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 12/30/2009
--|
--| DESCRIPTION   : Get the first non-zero bit position of input parameter
--|  
--|---------------------------------------------------------------------------*/

UINT8 Ctrl_HighBit(UINT32 In)
{
   UINT8 k,NonZeroP = 31; 
   UINT32 Mask = 0x80000000;
  
   for (k = 0; k < 32; k++)
   {
     if ((In & Mask) == 0x00) 
     {
       Mask = Mask >> 1;
       NonZeroP = NonZeroP - 1;
     }
     else  break;
   }
   return(NonZeroP);
}
