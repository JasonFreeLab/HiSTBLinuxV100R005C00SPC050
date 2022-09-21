//-----------------------------------------------------//
//                                                                  //
// Filename: R850.c                                        //
//                                                                  //
// This file is R850 tuner driver                        //
// Copyright 2015 by Rafaelmicro., Inc.            //
// Author: Ryan Chang                                     //
//-----------------------------------------------------//


#include "R850.h"
#include "R850_i2c_sys.h"
#include <linux/delay.h>

#include "hi_drv_i2c.h"
#include "hi_debug.h"

#include "drv_tuner_ext.h"
#include "drv_demod.h"

#define  FILTER_GAIN_DELAY  5
#define  FILTER_CODE_DELAY 5
#define  XTAL_CHK_DELAY    20
#define  PLL_LOCK_DELAY    10

UINT32 R850_RF_KHz = 435;

//==========Device Address============//
 UINT8 R850_ADDRESS = 0xF8;	                 //R850 I2C addr is 0xF8

//===========Xtal Frequency===========//
 UINT16 R850_Xtal = 16000;					 //Xtal clock rate.

//===========Xtal Cap set (Range is 0~41pF) ===============
//Suggest R850_Xtal_cap use 39pF when xtal CL value is 20pF, Default.
//Suggest R850_Xtal_cap use 30pF when xtal CL value is 16pF 
//Suggest R850_Xtal_cap use 22pF when xtal CL value is 12pF 
 UINT8 R850_Xtal_cap = 39;
 UINT8 R850_Xtal_cap_slave = 0;

//===========External LNA Option===========//
UINT8 R850_External_LNA = 0;			     //External LNA : 0:Disable , 1:Enable


UINT8 R850_iniArray[3][R850_REG_NUM] = {
	{      
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //24M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
	  //      0,    1,    2,    3,    4,    5,    6,    7
           0xCA, 0xC0, 0x72, 0x50, 0x00, 0xE0, 0x00, 0x30,
	  //   0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F  
	  //	  8,    9,   10,   11,   12,   13,   14,   15
		   0x86, 0xBB, 0xF8, 0xB0, 0xD2, 0x81, 0xCD, 0x46,
	  //   0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17 
	  //	 16,   17,   18,   19,   20,   21,   22,   23
           0x37, 0x40, 0x89, 0x8C, 0x55, 0x95, 0x07, 0x23,
	  //   0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F
	  //	 24,   25,   26,   27,   28,   29,   30,   31,
		   0x21, 0xF1, 0x4C, 0x5F, 0xE4, 0x20, 0xA9, 0x6C,
	  //   0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
	  //     32,   33,   34,   35,   36,   37,   38,   39
		   0x53, 0xAB, 0x5B, 0x46, 0xB3, 0x93, 0x6E, 0x41 },
	  //   0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
	  //	 40,   41,   42,   43,   44,   45,   46,   47
	{
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //16M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
	  //      0,    1,    2,    3,    4,    5,    6,    7
           0xCA, 0xC0, 0x72, 0x50, 0x00, 0xE0, 0x01, 0x30,
	  //   0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F
	  //	  8,    9,   10,   11,   12,   13,   14,   15
		   0x06, 0xBB, 0xF8, 0xB0, 0xF0, 0x61, 0xCD, 0x14,
	  //   0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17 
	  //	 16,   17,   18,   19,   20,   21,   22,   23
           0x37, 0x42, 0x81, 0x92, 0x00, 0xE0, 0x07, 0x23,
	  //   0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F 
	  //	 24,   25,   26,   27,   28,   29,   30,   31,
		   0x21, 0xF1, 0x8C, 0x5F, 0xE4, 0x00, 0xA9, 0x6C,
	  //   0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 
	  //     32,   33,   34,   35,   36,   37,   38,   39
		   0x31, 0xAB, 0x5A, 0x47, 0xB3, 0x93, 0xE9, 0x41 },
	  //   0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F 
	  //	 40,   41,   42,   43,   44,   45,   46,   47	
	{      
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //27M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
	  //      0,    1,    2,    3,    4,    5,    6,    7
           0xCA, 0xC0, 0x72, 0x50, 0x00, 0xE0, 0x00, 0x30,
	  //   0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F  
	  //	  8,    9,   10,   11,   12,   13,   14,   15
		   0x86, 0xBB, 0xF8, 0xB0, 0xD2, 0x81, 0xCD, 0x46,
	  //   0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17 
	  //	 16,   17,   18,   19,   20,   21,   22,   23
           0x37, 0x40, 0x89, 0x8B, 0x4B, 0x68, 0x04, 0x23,
	  //   0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F
	  //	 24,   25,   26,   27,   28,   29,   30,   31,
		   0x21, 0xF1, 0x4C, 0x5F, 0xE4, 0x20, 0xA9, 0x6C,
	  //   0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
	  //     32,   33,   34,   35,   36,   37,   38,   39
		   0x53, 0xAB, 0x5B, 0x46, 0xB3, 0x93, 0x6E, 0x41 }
	  //   0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
	  //	 40,   41,   42,   43,   44,   45,   46,   47
};

UINT32 R850_ADC_READ_DELAY = 2;
UINT8  R850_ADC_READ_COUNT = 1;

UINT8 R850_Chip = R850_MT1;			         
UINT8 R850_Address_List[8] = {0x38, 0x78, 0xb8, 0xf8, 0x34, 0x74, 0xb4, 0xf4};

UINT8 Divider_Manual = 0;					
UINT8 R850_XtalDiv = XTAL_DIV1;
UINT8 R850_Fil_Cal_Gap = 8;
UINT32 R850_IF_HIGH = 8500;
UINT32 R850_IF_GOLOBAL = 6000;
UINT8 R850_Xtal_Pwr[MAX_TUNER_NUM] = {XTAL_HIGHEST,XTAL_HIGHEST,XTAL_HIGHEST,XTAL_HIGHEST};			 //*
UINT8 R850_Xtal_Pwr_tmp[MAX_TUNER_NUM] = {XTAL_HIGHEST,XTAL_HIGHEST,XTAL_HIGHEST,XTAL_HIGHEST};		 //*
UINT8 R850_Mixer_Mode = R850_IMR_REV;
UINT8 R850_Mixer_Mode_Manual = 0;
UINT8 R850_Mixer_Amp_LPF_IMR_CAL = 7;
UINT8 R850_Nrb_Det_Mode = R850_NRB_DET_ON;

//LPF Cal Array 72MHz
UINT8 R850_LPF_CAL_Array[3][R850_REG_NUM] = {   //24M  //16M  //27MHz
	 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only
	   0xC0, 0x49, 0x3F, 0x90, 0x13, 0xE1, 0x89, 0x7A,
	   0x07, 0xF1, 0x9A, 0x50, 0x30, 0x20, 0xE1, 0x00,
	   0x00, 0x04, 0x81, 0x11, 0xEF, 0xEE, 0x17, 0x07,
	   0x31, 0x71, 0x54, 0xB2, 0xEE, 0xA9, 0xBB, 0x0B,
	   0xA3, 0x00, 0x0B, 0x44, 0x92, 0x1F, 0xE6, 0x80 },
	 {
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0xC0, 0x49, 0x3F, 0x90, 0x13, 0xE1, 0x89, 0x7A,						  						 
	   0x07, 0xF1, 0x9A, 0x50, 0x30, 0x20, 0xE1, 0x00,
	   0x00, 0x04, 0x81, 0x1C, 0x66, 0x66, 0x16, 0x07,
	   0x31, 0x71, 0x94, 0xBB, 0xEE, 0x89, 0xBB, 0x0B,
	   0xA3, 0x00, 0x0B, 0x44, 0x92, 0x1F, 0xE6, 0x80 },
	 { 
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only
	   0xC0, 0x49, 0x3F, 0x90, 0x13, 0xE1, 0x89, 0x7A,
	   0x07, 0xF1, 0x9A, 0x50, 0x30, 0x20, 0xE1, 0x00,
	   0x00, 0x04, 0x81, 0x11, 0xEF, 0xEE, 0x17, 0x07,
	   0x31, 0x71, 0x54, 0xB0, 0xEE, 0xA9, 0xBB, 0x0B,
	   0xA3, 0x00, 0x0B, 0x44, 0x92, 0x1F, 0xE6, 0x80 }
};
//IMR Cal array 544MHz(24MHz)
UINT8 R850_IMR_CAL_Array[3][R850_REG_NUM] = {   //24M  //16M  //27MHz
	{  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0xC0, 0x49, 0x3A, 0x90, 0x03, 0xC1, 0x61, 0x71,       	   													  						 
	   0x17, 0xF1, 0x18, 0x55, 0x30, 0x20, 0xF3, 0xED,
	   0x1F, 0x1C, 0x81, 0x13, 0x00, 0x80, 0x0A, 0x07,
	   0x21, 0x71, 0x54, 0xF1, 0xF2, 0xA9, 0xBB, 0x0B,					
	   0xA3, 0xF6, 0x0B, 0x44, 0x92, 0x17, 0xE6, 0x80 },
	{
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0xC0, 0x49, 0x3A, 0x90, 0x03, 0xC1, 0x61, 0x71,
	   0x17, 0xF1, 0x18, 0x55, 0x30, 0x20, 0xF3, 0xED,
	   0x1F, 0x1C, 0x81, 0x13, 0x00, 0x80, 0x0A, 0x07,
	   0x21, 0x71, 0x94, 0xF1, 0xF2, 0x89, 0xBB, 0x0B,
	   0xA3, 0xF6, 0x0B, 0x44, 0x92, 0x17, 0xE6, 0x80
													  },
	{  
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0xC0, 0x49, 0x3A, 0x90, 0x03, 0xC1, 0x61, 0x71,       	   													  						 
	   0x17, 0xF1, 0x18, 0x55, 0x30, 0x20, 0xF3, 0xED,
	   0x1F, 0x1C, 0x81, 0x13, 0x00, 0x80, 0x0A, 0x07,
	   0x21, 0x71, 0x54, 0xF1, 0xF2, 0xA9, 0xBB, 0x0B,					
	   0xA3, 0xF6, 0x0B, 0x44, 0x92, 0x17, 0xE6, 0x80 }
	
};
//----------------------------------------------------------//
//                   Internal Parameters                    //
//----------------------------------------------------------//

UINT8 R850_Array[MAX_TUNER_NUM][R850_REG_NUM];
R850_SectType R850_IMR_Data[MAX_TUNER_NUM][R850_IMR_POINT_NUM];
I2C_TYPE  R850_I2C;
I2C_LEN_TYPE R850_I2C_Len;
UINT8  R850_IMR_point_num;
UINT8  R850_Initial_flag = FALSE;
UINT8  R850_Initial_done_flag[MAX_TUNER_NUM] = {FALSE, FALSE, FALSE, FALSE};
UINT8  R850_IMR_done_flag[MAX_TUNER_NUM] = {FALSE, FALSE, FALSE, FALSE};
UINT8  R850_Bandwidth = 0;   //8M
UINT8  R850_Lpf_Lsb = 0;
UINT8  R850_Fil_Cal_flag[MAX_TUNER_NUM][R850_STD_SIZE];
static UINT8 R850_Fil_Cal_BW[MAX_TUNER_NUM][R850_STD_SIZE];
static UINT8 R850_Fil_Cal_code[MAX_TUNER_NUM][R850_STD_SIZE];
static UINT8 R850_Fil_Cal_LpfLsb[MAX_TUNER_NUM][R850_STD_SIZE];    
static R850_Standard_Type R850_pre_standard[MAX_TUNER_NUM] = {R850_STD_SIZE, R850_STD_SIZE, R850_STD_SIZE, R850_STD_SIZE};
static UINT8 R850_SBY[MAX_TUNER_NUM][R850_REG_NUM];
static UINT8 R850_Standby_flag[MAX_TUNER_NUM] = {FALSE};
static UINT8 R850_IMR_Cal_Result[MAX_TUNER_NUM] = {0}; //1: fail, 0: ok
static UINT8 R850_Fil_Cal_BW_def[R850_STD_SIZE]={
	   3, 2, 2, 3, 2, 2, 2, 0,           //{DVB_T_6M, DVB_T_7M, DVB_T_8M, DVB_T2_6M, DVB_T2_7M, DVB_T2_8M, DVB_T2_1_7M, DVB_T2_10M}
	   0, 2, 2, 3, 2, 2, 3, 2,           //{DVB_C_8M, DVB_C_6M, J83B, ISDB_T_4063, ISDB_T_4570, DTMB_8M_4570, DTMB_6M_4500, ATSC}
	   2, 2, 0, 2, 2, 0, 3,              //{DVB_T_6M, DVB_T_7M, DVB_T_8M, DVB_T2_6M, DVB_T2_7M, DVB_T2_8M, DVB_T2_1_7M, DVB_T2_10M} (IF 5M)
	   0, 2, 2, 2, 0, 2, 2, 2            //{DVB_C_8M, DVB_C_6M, J83B, ISDB_T_4063, ISDB_T_4570, DTMB_8M_4570, DTMB_6M_4500, ATSC} (IF 5M), FM
       };
static UINT8 R850_Fil_Cal_code_def[R850_STD_SIZE]={
        3,  8,  2,  3,  8,  2,  8,  0,             //DVB-T, DVB-T2
	    8,  4,  7,  5, 16,  1,  5,  6,             //DVB-C, J83B, ISDBT, DTMB, ATSC
	   13,  1, 13, 13,  1, 13, 23,                 //DVB-T, DVB-T2 (IF 5M)
	   11,  3, 11, 10, 11,  9,  8, 17              //DVB-C, J83B, ISDBT, DTMB, ATSC (IF 5M), FM
       };


//----------------------------------------------------------//
//                   Internal static struct                         //
//----------------------------------------------------------//
static R850_SysFreq_Info_Type  SysFreq_Info1;
static R850_Sys_Info_Type         Sys_Info1;
static R850_Freq_Info_Type       Freq_Info1;
//----------------------------------------------------------//
//                   Internal Functions                            //
//----------------------------------------------------------//
R850_ErrCode R850_Xtal_Check(R850_TUNER_NUM_TYPE R850_Tuner_Num);
R850_ErrCode R850_InitReg(R850_TUNER_NUM_TYPE R850_Tuner_Num);
R850_ErrCode R850_Cal_Prepare(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 u1CalFlag);
R850_ErrCode R850_IMR(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 IMR_MEM, UINT8 IM_Flag, UINT8 Rev_Mode);
R850_ErrCode R850_PLL(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 LO_Freq, R850_Standard_Type R850_Standard);
R850_ErrCode R850_MUX(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 LO_KHz, UINT32 RF_KHz, R850_Standard_Type R850_Standard);
R850_ErrCode R850_IQ(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont);
R850_ErrCode R850_IQ_Tree(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R850_SectType* CompareTree);
R850_ErrCode R850_CompreCor(R850_SectType* CorArry);
R850_ErrCode R850_CompreStep(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* StepArry, UINT8 Pace);
R850_ErrCode R850_Muti_Read(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8* IMR_Result_Data);
R850_ErrCode R850_Section(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* SectionArry);
R850_ErrCode R850_F_IMR(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont);
R850_ErrCode R850_IMR_Cross(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont, UINT8* X_Direct);
R850_ErrCode R850_IMR_Iqcap(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Point);   
R850_ErrCode R850_SetStandard(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Standard_Type RT_Standard);
R850_ErrCode R850_SetFrequency(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Set_Info R850_INFO);

R850_Sys_Info_Type R850_Sys_Sel(R850_Standard_Type R850_Standard);
R850_Freq_Info_Type R850_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R850_Standard_Type R850_Standard);
R850_SysFreq_Info_Type R850_SysFreq_NrbDetOn_Sel(R850_Standard_Type R850_Standard,UINT32 RF_freq);	//Nrb Det ON
R850_SysFreq_Info_Type R850_SysFreq_NrbDetOff_Sel(R850_Standard_Type R850_Standard,UINT32 RF_freq); //Nrb Det OFF

UINT8 R850_Filt_Cal_ADC(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 IF_Freq, UINT8 R850_BW, UINT8 FilCal_Gap);


#if(R850_RSSI_NORMAL_TYPE == TRUE)

	static UINT16 R850_Lna_Acc_Gain[4][32] = 
	{
		{0, 13, 24, 36, 49, 62, 76, 90, 105, 120, 135, 151, 163, 177, 191, 207, 222, 235, 249, 258, 267, 267, 267, 267, 267, 275, 286, 300, 316, 332, 329, 343},
		{0, 12, 23, 35, 48, 62, 77, 91, 107, 125, 142, 161, 171, 182, 194, 208, 220, 230, 242, 248, 255, 255, 255, 255, 255, 270, 285, 303, 320, 335, 321, 338},
		{0, 12, 24, 36, 50, 66, 81, 98, 117, 137, 158, 182, 192, 202, 213, 223, 232, 238, 244, 248, 251, 251, 251, 251, 251, 265, 280, 297, 312, 325, 318, 341},
		{0, 11, 23, 35, 49, 64, 80, 96, 114, 134, 153, 173, 184, 193, 202, 209, 215, 220, 222, 225, 227, 227, 227, 227, 227, 240, 254, 268, 281, 292, 307, 323},
	};

	static INT8 Lna_Acc_Gain_offset[86]={6,  4, 4, 3, 3, 4, 3, 2, 2, 1,	//45~145
										0, -2, -3, -5, -6, -7, -10, -9, -9, -10,	//145~245
										  -9, -9, -8, -8, -6, -4, -3, -1, -1, 0,	//245~345
										 8, 10, 10, 11, 11, 9, 10, 8, 4, 4,	//345~445
										 1, 0, 0, -2, -2, -2, -2, -2, -1, -2,	//445~545
										 0, 3, 2, 4, -2, 6, 6, 4, 3, 4,	//545~645
										 2, 0, -2, -4, -5, -7, 10, 7, 6, 4,	//645~745
										3, 2, 1, 0, -1, -1, -2, -2, -1, -2, //745~845
										-1, -2, -2, -2, -2, -3};						//845~905
#else

	static UINT16 R850_Lna_Acc_Gain[4][32] = 
	{
		{0, 13, 25, 38, 51, 65, 80, 94, 111, 128, 146, 164, 177, 190, 205, 220, 235, 248, 262, 271, 280, 280, 280, 280, 280, 288, 298, 313, 329, 345, 341, 358},
		{0, 13, 24, 37, 50, 65, 80, 95, 112, 130, 149, 168, 178, 188, 200, 212, 227, 237, 249, 256, 263, 263, 263, 263, 263, 276, 292, 310, 326, 342, 329, 348},
		{0, 12, 23, 34, 46, 60, 73, 86, 100, 115, 129, 143, 154, 165, 175, 186, 196, 204, 211, 216, 220, 220, 220, 220, 220, 234, 249, 266, 281, 294, 288, 301},
		{0, 12, 24, 38, 52, 68, 85, 103, 123, 147, 172, 202, 213, 223, 232, 240, 247, 251, 255, 257, 260, 260, 260, 260, 260, 273, 286, 301, 313, 324, 334, 363},
	};

	static INT8 Lna_Acc_Gain_offset[86]={-7, -9, -9, -10, -9, -9, -10, -11, -11, -12,	//45~145
										-13, 44, 27, 15, 11, 8, 5, 13, 15, 16,	//145~245
										  17, 16, 16, 14, 13, 8, 6, 3, -1, -7,	//245~345
										 3, -4, -8, -10, -12, -16, -20, 1, 5, 3,	//345~445
										 2, -1, -5, -7, -9, -11, -11, -11, -11, -12,	//445~545
										 -12, -12, -10, -10, -5, -3, -1, 0, 2, 4,	//545~645
										 8, 13, 15, 17, 18, 21, -21, -17, -13, -10,	//645~745
										-6, -5, -2, -1, -1, 3, 5, 7, 6, 6, //745~845
										5, 5, 6, 6, 5, 2};						//845~905
#endif
static UINT16 R850_Rf_Acc_Gain[16] = 
{
 0, 15, 31, 46, 58, 58, 58, 58, 58, 72,			//0~9
86, 99, 113, 113, 124, 134						//10~15
};

static UINT16 R850_Mixer_Acc_Gain[16] = 
{
 0, 0, 0, 0, 10, 22, 34, 46, 58, 70,			//0~9
 82, 93, 102, 122, 142, 142						//10~12
};

void R850_Delay_MS(UINT16 DelayTimeInMs)
{
	if(R850_Initial_flag == FALSE)
  		mdelay(DelayTimeInMs);
	else
		msleep(DelayTimeInMs);
}

R850_Sys_Info_Type R850_Sys_Sel(R850_Standard_Type R850_Standard)
{
	R850_Sys_Info_Type R850_Sys_Info;

	switch (R850_Standard)
	{
	case R850_DVB_T_6M: 
	case R850_DVB_T2_6M: 
		R850_Sys_Info.IF_KHz=4570;               //IF
		R850_Sys_Info.BW=1;                      //BW(v7M/v6M)=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7550;          //CAL IF
		R850_Sys_Info.HPF_COR=8;	             //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T_7M:
	case R850_DVB_T2_7M:
		R850_Sys_Info.IF_KHz=4570;               //IF
		R850_Sys_Info.BW=1;                      //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7920;          //CAL IF
		R850_Sys_Info.HPF_COR=11;	             //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		    //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T_8M:
	case R850_DVB_T2_8M:
		R850_Sys_Info.IF_KHz=4570;                //IF
		R850_Sys_Info.BW=0;                       //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8450;           //CAL IF
		R850_Sys_Info.HPF_COR=12;                //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T2_1_7M: 
		R850_Sys_Info.IF_KHz=1900;
		R850_Sys_Info.BW=1;                       //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7920;           //CAL IF
		R850_Sys_Info.HPF_COR=11;	             //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T2_10M: 
		R850_Sys_Info.IF_KHz=5600;
		R850_Sys_Info.BW=0;                      //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=10500;         //CAL IF
		R850_Sys_Info.HPF_COR=12;                //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_C_8M:
		R850_Sys_Info.IF_KHz=5070;
		R850_Sys_Info.BW=0;                       //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8850;           //CAL IF
		R850_Sys_Info.HPF_COR=11;                //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_C_6M:  
		R850_Sys_Info.IF_KHz=5070;
		R850_Sys_Info.BW=1;                      //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8100;          //CAL IF   
		R850_Sys_Info.HPF_COR=5;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;			//R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_J83B:  
		R850_Sys_Info.IF_KHz=5070;
		R850_Sys_Info.BW=1;                       //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8100;          //CAL IF  
		R850_Sys_Info.HPF_COR=5;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;			 //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_ISDB_T_4063: 
		R850_Sys_Info.IF_KHz=4063;
		R850_Sys_Info.BW=1;                      //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7070;          //CAL IF  
		if(R850_Chip == R850_MP)
			R850_Sys_Info.HPF_COR=8;             //R24[7:4] [0~15 ; input: "0~15"]
		else
			R850_Sys_Info.HPF_COR=10;             //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_ISDB_T_4570:
		R850_Sys_Info.IF_KHz=4570;                    //IF
		R850_Sys_Info.BW=1;                       //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7400;          //CAL IF
		if(R850_Chip == R850_MP)
			R850_Sys_Info.HPF_COR=5;             //R24[7:4] [0~15 ; input: "0~15"]
		else
			R850_Sys_Info.HPF_COR=8;             //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DTMB_8M_4570: 
		R850_Sys_Info.IF_KHz=4570;
		R850_Sys_Info.BW=0;                                //BW=8M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8450;           //CAL IF  
		R850_Sys_Info.HPF_COR=12;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;			 //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DTMB_6M_4500:
		R850_Sys_Info.IF_KHz=4500;
		R850_Sys_Info.BW=1;                      //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7200;           //CAL IF    
		R850_Sys_Info.HPF_COR=8;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		    //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_ATSC:  
		R850_Sys_Info.IF_KHz=5070;
		R850_Sys_Info.BW=1;                      //BW=7M    R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8050;          //CAL IF   
		R850_Sys_Info.HPF_COR=5;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

    case R850_DVB_T_6M_IF_5M: 
	case R850_DVB_T2_6M_IF_5M: 
		R850_Sys_Info.IF_KHz=5000;                    //IF
		R850_Sys_Info.BW=1;                      //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7920;          //CAL IF
		R850_Sys_Info.HPF_COR=6;                  //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		    //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T_7M_IF_5M:  
	case R850_DVB_T2_7M_IF_5M:  
		R850_Sys_Info.IF_KHz=5000;                     //IF
		R850_Sys_Info.BW=0;                       //BW=8M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8450;           //CAL IF
		R850_Sys_Info.HPF_COR=9;                   //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T_8M_IF_5M: 
	case R850_DVB_T2_8M_IF_5M:
		R850_Sys_Info.IF_KHz=5000;                     //IF
		R850_Sys_Info.BW=0;                       //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8700;           //CAL IF
		R850_Sys_Info.HPF_COR=10;                  //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_T2_1_7M_IF_5M: 
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=2;                       //BW=6M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=6000;           //CAL IF
		R850_Sys_Info.HPF_COR=1;                  //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_C_8M_IF_5M:  
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=0;                       //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=9250;           //CAL IF 
		R850_Sys_Info.HPF_COR=11;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DVB_C_6M_IF_5M:  
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=1;                      //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8200;          //CAL IF   
		R850_Sys_Info.HPF_COR=6;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;			 //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_J83B_IF_5M:  
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=1;                       //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7550;          //CAL IF  
		R850_Sys_Info.HPF_COR=5;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;			 //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_ISDB_T_IF_5M: 
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=1;                      //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7780;          //CAL IF  
		R850_Sys_Info.HPF_COR=3;                 //R24[7:4] [0~15 ; input: "0~15"]
		if(R850_Chip == R850_MP)
			R850_Sys_Info.FILT_EXT_ENA=1;		     //R18[6] filter ext enable [off(0), on(1)]
		else
			R850_Sys_Info.FILT_EXT_ENA=0;			 //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DTMB_8M_IF_5M: 
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=0;                      //BW=8M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8800;          //CAL IF  
		R850_Sys_Info.HPF_COR=11;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=2;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_DTMB_6M_IF_5M:
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=1;                       //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8100;           //CAL IF  
		R850_Sys_Info.HPF_COR=6;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		    //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;
	
	case R850_ATSC_IF_5M:  
		R850_Sys_Info.IF_KHz=5000;
		R850_Sys_Info.BW=1;                      //BW=7M   R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7920;          //CAL IF   
		R850_Sys_Info.HPF_COR=5;                 //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	case R850_FM:  
		R850_Sys_Info.IF_KHz=2400;
		R850_Sys_Info.BW=1;                       //BW=7M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=7300;           //CAL IF
		R850_Sys_Info.HPF_COR=2;                  //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;

	default:  //R850_DVB_T_8M
		R850_Sys_Info.IF_KHz=4570;                //IF
		R850_Sys_Info.BW=0;                       //BW=8M  R23[6:5] [8M(0), 7M(1), 6M(2)]
		R850_Sys_Info.FILT_CAL_IF=8450;           //CAL IF
		R850_Sys_Info.HPF_COR=12;                //R24[7:4] [0~15 ; input: "0~15"]
		R850_Sys_Info.FILT_EXT_ENA=0;		     //R18[6] filter ext disable [off(0), on(1)]
		R850_Sys_Info.FILT_COMP=1;				 //R24[3:2] [0~3 ; input: "0~3"]
		break;
	}

	// DTV
	R850_Sys_Info.HPF_NOTCH = 0;          //R23[7] notch high  [notch high(0), notch low(1)]

	if(R850_Chip == R850_MP)
	{
		R850_Sys_Info.AGC_CLK = 0;          //R47[3:2] 1k   [1kHz(0), 512Hz(1), 4kHz(2), 64Hz(3)]
		R850_Sys_Info.IMG_GAIN = 0;          ////R46[4] High   [High(0), Low(1)]
	}
	else
	{
		R850_Sys_Info.AGC_CLK = 1;          //R47[3:2] 1k   [1kHz(0), 512Hz(1), 4kHz(2), 64Hz(3)]
		R850_Sys_Info.IMG_GAIN = 3;          ////MSB:R44[0] , LSB:R46[4]  highest   [lowest(0), high(1), low(2), highest(3)]
	}
		
	
	
	//Mixer PLL mode
	if(R850_Mixer_Mode_Manual == 1)
	{

	}
	else
	{
		if((R850_Standard==R850_ATSC) || (R850_Standard==R850_ATSC_IF_5M)) //ATSC
		{
			R850_Mixer_Mode = R850_IMR_NOR;  //mixer up-side tune
			R850_Mixer_Amp_LPF_IMR_CAL = 7;
		}
		else if((R850_Standard==R850_J83B) || (R850_Standard==R850_J83B_IF_5M))  //J83B
		{
			R850_Mixer_Mode = R850_IMR_NOR;  //mixer up-side tune
			R850_Mixer_Amp_LPF_IMR_CAL = 7;
		}
		else if((R850_Standard==R850_DTMB_8M_4570) || (R850_Standard==R850_DTMB_6M_4500)  ||  (R850_Standard==R850_DTMB_8M_IF_5M) || (R850_Standard==R850_DTMB_6M_IF_5M))
		{
			R850_Mixer_Mode = R850_IMR_NOR;  //mixer up-side tune
			R850_Mixer_Amp_LPF_IMR_CAL = 7;
		}
		else if((R850_Standard==R850_ISDB_T_4063) || (R850_Standard==R850_ISDB_T_4570) || (R850_Standard==R850_ISDB_T_IF_5M))
		{
			R850_Mixer_Mode = R850_IMR_REV;  //mixer low-side tune
			R850_Mixer_Amp_LPF_IMR_CAL = 7;  //only isdb-t use 7 for reverse, and use 4 for other standard
		}
		else  //other DTV
		{
			R850_Mixer_Mode = R850_IMR_NOR;   //mixer low-side tune
			R850_Mixer_Amp_LPF_IMR_CAL = 4;
		}
	}

	return R850_Sys_Info;
}



R850_Freq_Info_Type R850_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R850_Standard_Type R850_Standard)
{
	R850_Freq_Info_Type R850_Freq_Info;


	//----- LO dependent parameter --------

	//IMR point 
	if((LO_freq>0) && (LO_freq<170000))  
	{
         R850_Freq_Info.IMR_MEM_NOR = 0;   
		 R850_Freq_Info.IMR_MEM_REV = 5;
	}
	else if((LO_freq>=170000) && (LO_freq<240000))  
	{
         R850_Freq_Info.IMR_MEM_NOR = 4;   
		 R850_Freq_Info.IMR_MEM_REV = 9;   
	}
	else if((LO_freq>=240000) && (LO_freq<400000))  
	{
         R850_Freq_Info.IMR_MEM_NOR = 1;   
		 R850_Freq_Info.IMR_MEM_REV = 6;   
	}
	else if((LO_freq>=400000) && (LO_freq<760000))  
	{
		 R850_Freq_Info.IMR_MEM_NOR = 2; 
		 R850_Freq_Info.IMR_MEM_REV = 7;   
	}
	else 
	{
		 R850_Freq_Info.IMR_MEM_NOR = 3;
		 R850_Freq_Info.IMR_MEM_REV = 8;   
	}

	//TF_HPF_BPF R16[2:0]
	/*	7-lowest:111 ; 6:011 ; 5:101 ; 4:001 ; 3:110 ; 2:010 ; 1:100 ; 0-noBPF:000	*/
	if(LO_freq<580000)
		R850_Freq_Info.TF_HPF_BPF = 0x07;		//7 => 111:lowset BPF  R16[2:0]
	else if(LO_freq>=580000 && LO_freq<660000)
		R850_Freq_Info.TF_HPF_BPF = 0x01;	//	//4 => 001
	else if(LO_freq>=660000 && LO_freq<780000)
		R850_Freq_Info.TF_HPF_BPF = 0x06;	//	//3 => 110
	else if(LO_freq>=780000 && LO_freq<900000)
		R850_Freq_Info.TF_HPF_BPF = 0x04;	//	//1 => 100
	else
		R850_Freq_Info.TF_HPF_BPF = 0x00;		//0 => 000

	/*
	00: highest band
	01: med band
	10: low band
	11: Ultrawide band
	*/
	//RF polyfilter band
	if((LO_freq>0) && (LO_freq<133000))  
         R850_Freq_Info.RF_POLY = 2;   //R17[6:5]=2; low	=> R18[1:0]
	else if((LO_freq>=133000) && (LO_freq<221000))  
         R850_Freq_Info.RF_POLY = 1;   //R17[6:5]=1; mid	=> R18[1:0]
	else if((LO_freq>=221000) && (LO_freq<760000))  
		 R850_Freq_Info.RF_POLY = 0;   //R17[6:5]=0; highest    => R18[1:0]
	else
		 R850_Freq_Info.RF_POLY = 3;   //R17[6:5]=3; ultra high	=> R18[1:0]

	
	/*
	00: highest
	01: high
	10: low
	11: lowest
	*/
	//TF_HPF_Corner
	if((LO_freq>0) && (LO_freq<480000))  
         R850_Freq_Info.TF_HPF_CNR = 3;   //lowest	=> R16[4:3]
	else if((LO_freq>=480000) && (LO_freq<550000))  
         R850_Freq_Info.TF_HPF_CNR = 2;   // low	=> R16[4:3]
	else if((LO_freq>=550000) && (LO_freq<700000))  
		 R850_Freq_Info.TF_HPF_CNR = 1;   // high    => R16[4:3]
	else
		 R850_Freq_Info.TF_HPF_CNR = 0;   //highest	=> R16[4:3]


	//LPF Cap, Notch
	switch(R850_Standard)
	{
		case R850_DVB_C_8M:                            //Cable
		case R850_DVB_C_6M:
		case R850_J83B:
        case R850_DVB_C_8M_IF_5M:
		case R850_DVB_C_6M_IF_5M:
		case R850_J83B_IF_5M:
			if(LO_freq<77000)  
			{
				R850_Freq_Info.LPF_CAP = 15;
				R850_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=77000) && (LO_freq<85000))
			{
				R850_Freq_Info.LPF_CAP = 15;
				R850_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=85000) && (LO_freq<115000))
			{
				R850_Freq_Info.LPF_CAP = 13;
				R850_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=115000) && (LO_freq<125000))
			{
				R850_Freq_Info.LPF_CAP = 11;
				R850_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=125000) && (LO_freq<141000))
			{
				R850_Freq_Info.LPF_CAP = 9;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=141000) && (LO_freq<157000))
			{
				R850_Freq_Info.LPF_CAP = 8;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=157000) && (LO_freq<181000))
			{
				R850_Freq_Info.LPF_CAP = 6;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=181000) && (LO_freq<205000))
			{
				R850_Freq_Info.LPF_CAP = 3;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R850_Freq_Info.LPF_CAP = 0;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			//Diplexer Select R14[3:2]
			if(LO_freq<330000)
				R850_Freq_Info.TF_DIPLEXER = 2; //LPF   R14[3:2]
			else
				R850_Freq_Info.TF_DIPLEXER = 0; //HPF


			break;

		default:  //Air, DTMB (for 180nH)
			if((LO_freq>0) && (LO_freq<73000))  
			{
				R850_Freq_Info.LPF_CAP = 8;
				R850_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=73000) && (LO_freq<81000))
			{
				R850_Freq_Info.LPF_CAP = 8;
				R850_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=81000) && (LO_freq<89000))
			{
				R850_Freq_Info.LPF_CAP = 8;
				R850_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=89000) && (LO_freq<121000))
			{
				R850_Freq_Info.LPF_CAP = 6;
				R850_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=121000) && (LO_freq<145000))
			{
				R850_Freq_Info.LPF_CAP = 4;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=145000) && (LO_freq<153000))
			{
				R850_Freq_Info.LPF_CAP = 3;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=153000) && (LO_freq<177000))
			{
				R850_Freq_Info.LPF_CAP = 2;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=177000) && (LO_freq<201000))
			{
				R850_Freq_Info.LPF_CAP = 1;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R850_Freq_Info.LPF_CAP = 0;
				R850_Freq_Info.LPF_NOTCH = 0;
			}
			//Diplexer Select R14[3:2]
			if(LO_freq<340000)
				R850_Freq_Info.TF_DIPLEXER = 2; //LPF   R14[3:2]
			else
				R850_Freq_Info.TF_DIPLEXER = 0; //HPF
			break;

	}//end switch(standard)


	return R850_Freq_Info;

}



R850_SysFreq_Info_Type R850_SysFreq_NrbDetOn_Sel(R850_Standard_Type R850_Standard,UINT32 RF_freq)
{
	R850_SysFreq_Info_Type R850_SysFreq_Info;

	switch(R850_Standard)
	{
	case R850_DVB_T_6M:
	case R850_DVB_T_7M:
	case R850_DVB_T_8M:
	case R850_DVB_T_6M_IF_5M:
	case R850_DVB_T_7M_IF_5M:
	case R850_DVB_T_8M_IF_5M:
	case R850_DVB_T2_6M:
	case R850_DVB_T2_7M: 
	case R850_DVB_T2_8M:
	case R850_DVB_T2_1_7M:
	case R850_DVB_T2_10M:
    case R850_DVB_T2_6M_IF_5M:
	case R850_DVB_T2_7M_IF_5M:
	case R850_DVB_T2_8M_IF_5M:
	case R850_DVB_T2_1_7M_IF_5M:
		if(RF_freq<=340000)
		{	
			//LNA
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else if ((RF_freq>662000) && (RF_freq<=670000))
		{
			//LNA
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=4;			//lna RF(slow)	(R45[1:0];R32[5];R31[0];) : 1110 lna RF(slow)			case 4
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else if ((RF_freq>782000) && (RF_freq<=790000))
		{
			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;			//Both (slow) (R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else
		{
			//LNA
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x5A;				//R42[7:0] RF VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
	
		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]	   ["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

    case R850_DVB_C_8M:
	case R850_DVB_C_6M:	
	case R850_DVB_C_8M_IF_5M:
	case R850_DVB_C_6M_IF_5M:	
		if(RF_freq<=335000)
		{			
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}
		else if ((RF_freq>335000) && (RF_freq<=660000) )
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else  // RF_freq>660MHz
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=3;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA	
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H=0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=0;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (A)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]


		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]
		

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]


		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

	case R850_J83B:
	case R850_J83B_IF_5M:
		if(RF_freq<=335000)
		{
			//LNA	
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}
		else if ((RF_freq>340000) && (RF_freq<=660000) )
		{
			//LNA	
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]

			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else  // RF_freq>660MHz
		{
			//LNA	
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]

			//RFBuf
			R850_SysFreq_Info.RF_TOP=3;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA	
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H=0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=0;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (A)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=0;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

	case R850_ISDB_T_4063:	

		if(RF_freq<=340000)
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0]  LNA VTL/H=0.94(6) / 1.44(B)

			//RFBuf
			R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=15;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=12;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else if(RF_freq>=470000 && RF_freq<488000)	//470~488
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=6;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x8C;				//R39[7:0]  LNA VTL/H=1.14(8) / 1.54(C)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5  

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else if(RF_freq>=680000 && RF_freq<692000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H=0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]
			
			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else if(RF_freq>=692000 && RF_freq<698000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5B;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.44(B)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=3;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else	//other frequency
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5  

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}

		//PW
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

	
		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//VGA
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		R850_SysFreq_Info.HPF_COMP=2;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]

		break;

	case R850_ISDB_T_4570:	
	case R850_ISDB_T_IF_5M:	
		if(RF_freq<=340000)
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0]  LNA VTL/H=0.94(6) / 1.44(B)

			//RFBuf
			R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=15;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x0B;				//R41[3:0] 1.44 (B)
			R850_SysFreq_Info.MIXER_VTL=0x06;				//R43[3:0] 0.94 (6)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=12;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else if(RF_freq>=470000 && RF_freq<488000)	//470~488
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=6;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x8C;				//R39[7:0]  LNA VTL/H=1.14(8) / 1.54(C)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5  

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else if(RF_freq>=680000 && RF_freq<692000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H=0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]
			
			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else if(RF_freq>=692000 && RF_freq<698000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5B;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.44(B)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=3;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}
		else	//other frequency
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(4) / 1.44(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
			R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5  

			//NRB  
			R850_SysFreq_Info.IMG_NRB_ADDER=3;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
		}

		//PW
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

	
		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//VGA
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		R850_SysFreq_Info.HPF_COMP=2;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		
		break;

	case R850_DTMB_8M_4570:
	case R850_DTMB_6M_4500:
	case R850_DTMB_8M_IF_5M:
	case R850_DTMB_6M_IF_5M:
		if(RF_freq<=100000)
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0] LNA VTL/H = 0.94(6) / 1.44(B)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=3;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
			
			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else if(RF_freq<=340000)
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0] LNA VTL/H = 0.94(6) / 1.44(B)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=6;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=2;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=0;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=1;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=0;			//R10[4] [high (0), low (1)]
		

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5      
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)] 

		//VGA
		R850_SysFreq_Info.HPF_COMP=0;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=0;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	case R850_ATSC:
	case R850_ATSC_IF_5M:
		if(RF_freq<=340000)
		{
			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else
		{
			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=6;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x0B;				//R41[3:0] 1.44 (B)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =1;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=6;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5    
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=12;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=2;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=2;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	case R850_FM:
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H = 0x5A;				//R42[7:0] RF VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 0;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x0B;				//R41[3:0] 1.44 (B)
		R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=5;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]


		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=0;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=0;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	default: //DVB-T
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
	

		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]	   ["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;
	
	} //end switch

	return R850_SysFreq_Info;

}

R850_SysFreq_Info_Type R850_SysFreq_NrbDetOff_Sel(R850_Standard_Type R850_Standard,UINT32 RF_freq)
{
	R850_SysFreq_Info_Type R850_SysFreq_Info;

	switch(R850_Standard)
	{
	case R850_DVB_T_6M:
	case R850_DVB_T_7M:
	case R850_DVB_T_8M:
	case R850_DVB_T_6M_IF_5M:
	case R850_DVB_T_7M_IF_5M:
	case R850_DVB_T_8M_IF_5M:
	case R850_DVB_T2_6M:
	case R850_DVB_T2_7M: 
	case R850_DVB_T2_8M:
	case R850_DVB_T2_1_7M:
	case R850_DVB_T2_10M:
    case R850_DVB_T2_6M_IF_5M:
	case R850_DVB_T2_7M_IF_5M:
	case R850_DVB_T2_8M_IF_5M:
	case R850_DVB_T2_1_7M_IF_5M:
		if(RF_freq<=340000)
		{	
			//PW
			R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else if ((RF_freq>662000) && (RF_freq<=670000))
		{
			//PW
			R850_SysFreq_Info.LNA_NRB_DET=0;				//R11[7]    ["on" (0), "off" (1)]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=4;			//lna RF(slow)	(R45[1:0];R32[5];R31[0];) : 1110 lna RF(slow)			case 4
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else if ((RF_freq>782000) && (RF_freq<=790000))
		{
			//PW
			R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;			//Both (slow) (R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		else
		{
			//PW
			R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

			//NRB  
			R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		}
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=3;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
	

		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]	   ["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

    case R850_DVB_C_8M:
	case R850_DVB_C_6M:	
	case R850_DVB_C_8M_IF_5M:
	case R850_DVB_C_6M_IF_5M:	

		if(RF_freq<=335000)
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}
		else if ((RF_freq>335000) && (RF_freq<=660000) )
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else  // RF_freq>660MHz
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=3;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA	
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H=0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=0;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (A)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]


		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]
		

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]


		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

	case R850_J83B:
	case R850_J83B_IF_5M:
		if(RF_freq<=335000)
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}
		else if ((RF_freq>340000) && (RF_freq<=660000) )
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		}
		else  // RF_freq>660MHz
		{
			//RFBuf
			R850_SysFreq_Info.RF_TOP=3;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]

			//NRB
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA	
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H=0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=0;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (A)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=0;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.NRB_TOP=5;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;

	case R850_ISDB_T_4063:	
	case R850_ISDB_T_4570:	
	case R850_ISDB_T_IF_5M:	
		if(RF_freq<=340000)
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0]  LNA VTL/H=0.94(6) / 1.44(B)

			//RFBuf
			R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=15;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=0;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=12;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		
			//VGA
			R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		}
		else if(RF_freq>=680000 && RF_freq<692000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=3;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x4A;				//R39[7:0]  LNA VTL/H=0.74(4) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=0;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]
			
			//NRB
			R850_SysFreq_Info.NRB_TOP=6;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7
			
			//VGA
			R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		}
		else if(RF_freq>=692000 && RF_freq<698000)	//LTE
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 0;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5B;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.44(B)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x6B;				//R42[7:0] RF VTL/H = 0.94(6) / 1.44(B)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=1;				// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=3;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=2;  			//(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=4;			//R45[7:4]		0.15u (0) / 0.9u (4) 	=> 0 + 4 = 4
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=7;			//R44[7:4]		0.6u (3) / 0.9u (4)		=> 3 + 4 = 7
			
			
			//VGA
			R850_SysFreq_Info.HPF_COMP=2;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		}
		else	//other frequency
		{
			//PW
			R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]

			//LNA
			R850_SysFreq_Info.LNA_TOP=3;					//R38[2:0]  ["7~0" (0~7)]
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)


			//RFBuf
			R850_SysFreq_Info.RF_TOP=6;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
			R850_SysFreq_Info.RF_VTL_H = 0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R850_SysFreq_Info.MIXER_TOP=14;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.MIXER_GAIN_LIMIT=1;			//R22[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

			//Polyphase
			R850_SysFreq_Info.ENB_POLY_GAIN=0;			// R25[1]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R850_SysFreq_Info.NRB_TOP=6;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

			//Discharge
			R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
			R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
			R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		
			//VGA
			R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		}

		//PW
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

	
		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0] 1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]


		//Filter
		if(R850_Chip == R850_MP)
			R850_SysFreq_Info.FILTER_TOP=12;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		else
			R850_SysFreq_Info.FILTER_TOP=6;						//R44[3:0]  ["7-highest ~ 0-lowest" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//NRB  
		R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		
		break;

	case R850_DTMB_8M_4570:
	case R850_DTMB_6M_4500:
	case R850_DTMB_8M_IF_5M:
	case R850_DTMB_6M_IF_5M:
		if(RF_freq<=100000)
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0] LNA VTL/H = 0.94(6) / 1.44(B)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=3;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else if(RF_freq<=340000)
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x6B;				//R39[7:0] LNA VTL/H = 0.94(6) / 1.44(B)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=10;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=3;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else
		{
			//LNA
			R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)

			//NRB  
			R850_SysFreq_Info.NRB_TOP=6;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
			R850_SysFreq_Info.NRB_BW_HPF=2;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
			R850_SysFreq_Info.IMG_NRB_ADDER=0;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}

		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=3;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=1;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=0;			//R10[4] [high (0), low (1)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5      
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)] 

		//VGA
		R850_SysFreq_Info.HPF_COMP=0;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=0;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	case R850_ATSC:
	case R850_ATSC_IF_5M:
		if(RF_freq<=340000)
		{
			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		else
		{
			//Filter
			R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]
		}
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=5;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_TOP=5;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H = 0x6A;				//R42[7:0] RF VTL/H = 0.94(6) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 7;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=12;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x0B;				//R41[3:0] 1.44 (B)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0] 0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =1;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=6;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]


		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5    
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=12;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=2;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=2;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	case R850_FM:
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=4;					//R38[2:0]  ["7~0" (0~7)]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H = 0x5A;				//R42[7:0] RF VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 0;			//R19[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x0B;				//R41[3:0] 1.44 (B)
		R850_SysFreq_Info.MIXER_VTL=0x05;				//R43[3:0] 0.84 (5)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]

		//Filter
		R850_SysFreq_Info.FILTER_TOP=5;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=1;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=0;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]


		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				// R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=1;				//R46[3:2]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=0;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=0;					//R21[4]	   ["2K" (0) , "8K" (1)]

		break;

	default: //DVB-T
		//PW
		R850_SysFreq_Info.NA_PWR_DET = 1;				//R10[6]   ["off" (0), "on" (1)]
		R850_SysFreq_Info.LNA_NRB_DET=1;				//R11[7]    ["on" (0), "off" (1)]

		//LNA
		R850_SysFreq_Info.LNA_TOP=3;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.LNA_VTL_H=0x5A;				//R39[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R850_SysFreq_Info.RF_LTE_PSG=1;					//R17[4]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R850_SysFreq_Info.RF_TOP=4;						//R38[6:4]  ["7~0" (0~7) ; input: "7~0"]
		R850_SysFreq_Info.RF_VTL_H=0x4A;				//R42[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R850_SysFreq_Info.RF_GAIN_LIMIT=0;				//MSB R18[2], LSB R16[6]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R850_SysFreq_Info.MIXER_AMP_LPF = 4;			//R19[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R850_SysFreq_Info.MIXER_TOP=9;					//R40[3:0]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.MIXER_VTH=0x09;				//R41[3:0]	1.24 (9)
		R850_SysFreq_Info.MIXER_VTL=0x04;				//R43[3:0]	0.74 (4)
		R850_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R22[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]
		R850_SysFreq_Info.MIXER_DETBW_LPF =0;			//R46[7]	["normal" (0), "enhance amp det LPF" (1)]
	

		//Filter
		R850_SysFreq_Info.FILTER_TOP=4;					//R44[3:0]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.FILTER_VTH=0x90;				//R41[7:4]  1.24 (9)
		R850_SysFreq_Info.FILTER_VTL=0x40;				//R43[7:4]  0.74 (4)
		R850_SysFreq_Info.FILT_3TH_LPF_CUR=1;			//R10[4] [high (0), low (1)]
		R850_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R24[1:0]		[normal (0), +1.5dB (1), +3dB (2), +4.5dB (3)]

		//Discharge
		R850_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		R850_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		R850_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R850_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		R850_SysFreq_Info.LNA_DIS_SLOW_FAST=5;			//R44[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5   
		R850_SysFreq_Info.BB_DIS_CURR=0;                //R25[6]		["x1" (0) , "x1/2" (1)]
		R850_SysFreq_Info.MIXER_FILTER_DIS=2;			//R37[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R850_SysFreq_Info.BB_DET_MODE=0;				//R37[2]		["peak" (0), "average" (1)]

		//Polyphase
		R850_SysFreq_Info.ENB_POLY_GAIN=0;				//R25[1]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R850_SysFreq_Info.NRB_TOP=4;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R850_SysFreq_Info.NRB_BW_HPF=0;					//R26[3:2]     [lowest (0), low (1), high (2), highest (3)]
		R850_SysFreq_Info.NRB_BW_LPF=2;					//R26[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R850_SysFreq_Info.IMG_NRB_ADDER=2;				//R46[3:2]	   ["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		//VGA
		R850_SysFreq_Info.HPF_COMP=1;					//R13[2:1]	   ["normal" (0) , "+1.5dB" (1), "+3dB" (2), "+4dB" (3)]
		R850_SysFreq_Info.FB_RES_1ST=1;					//R21[4]	   ["2K" (0) , "8K" (1)]
		break;
	
	} //end switch

	return R850_SysFreq_Info;
}




R850_ErrCode R850_Init(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Standard_Type R850_Standard)
{
    UINT8 i;
//	UINT8 check_i2c_count = 0;
	R850_Sys_Info_Type R850_Sys_Init;

	R850_Sys_Init = R850_Sys_Sel (R850_Standard);	//Get R850_Mixer_Mode by different standard


	//Check Device Address
	R850_I2C_Len.RegAddr = 0x00;
	R850_I2C_Len.Len = 1;
	R850_I2C_Len.Data[0] = 0;
	/*while(check_i2c_count < 8)
	{
		R850_ADDRESS = R850_Address_List[check_i2c_count];
		if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) == RT_Success)
		{
			if((R850_I2C_Len.Data[0] == CHIP_ID) && (check_i2c_count >= 4))
			{
				R850_Chip = R850_MP;
				break;
			}
			else if ((R850_I2C_Len.Data[0] == CHIP_ID) && (check_i2c_count < 4))
			{
				R850_Chip = R850_MT1;
				break;
			}
			else
			{
				check_i2c_count++;
			}
		}
		else
		{
			check_i2c_count++;
		}
	}*/

	if(R850_Initial_done_flag[R850_Tuner_Num]==FALSE)
	{
		  //reset filter cal. data
		  for (i=0; i<R850_STD_SIZE; i++)
		  {
			  R850_Fil_Cal_flag[R850_Tuner_Num][i] = FALSE;
			  R850_Fil_Cal_code[R850_Tuner_Num][i] = 0; 
			  R850_Fil_Cal_BW[R850_Tuner_Num][i] = 0x00;
			  R850_Fil_Cal_LpfLsb[R850_Tuner_Num][i] = 0;
		  }

		  R850_IMR_Cal_Result[R850_Tuner_Num] = 0; 

          if(R850_IMR_done_flag[R850_Tuner_Num]==FALSE)
		  {
			 if(R850_Cal_Prepare(R850_Tuner_Num, R850_IMR_CAL) != RT_Success)     
				  return RT_Fail;

			 if(R850_Mixer_Mode == R850_IMR_NOR)
			 {
				 if(R850_IMR(R850_Tuner_Num, 2, TRUE, R850_IMR_NOR) != RT_Success)       //Full K node 2
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 1, FALSE, R850_IMR_NOR) != RT_Success)
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 0, FALSE, R850_IMR_NOR) != RT_Success)
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 3, FALSE, R850_IMR_NOR) != RT_Success)   
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 4, FALSE, R850_IMR_NOR) != RT_Success)   
					return RT_Fail;
			 }
			 else
			 {
				 //Reverse
				 if(R850_IMR(R850_Tuner_Num, 7, TRUE, R850_IMR_REV) != RT_Success)   //Full K node 7, Rev
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 6, FALSE, R850_IMR_REV) != RT_Success) 
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 5, FALSE, R850_IMR_REV) != RT_Success)   
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 8, TRUE, R850_IMR_REV) != RT_Success)	//Full K node 8, Rev
					return RT_Fail;

				 if(R850_IMR(R850_Tuner_Num, 9, FALSE, R850_IMR_REV) != RT_Success)   
					return RT_Fail;
			 }

			R850_IMR_done_flag[R850_Tuner_Num] = TRUE;

		  }

//RF < 100MHz => Xtal PW = Low
//other		  => Xtal PW = Highest


		  //do Xtal check
#if(R850_SHARE_XTAL==TRUE)
		  R850_Xtal_Pwr[R850_Tuner_Num] = XTAL_HIGHEST;
#else
		  if(R850_InitReg(R850_Tuner_Num) != RT_Success)        
			 return RT_Fail;

		  if(R850_Xtal_Check(R850_Tuner_Num) != RT_Success)        
		     return RT_Fail;

		  if(R850_Xtal_Pwr_tmp[R850_Tuner_Num]==XTAL_HIGHEST)
			  R850_Xtal_Pwr[R850_Tuner_Num] = XTAL_HIGHEST;
		  else
			  R850_Xtal_Pwr[R850_Tuner_Num] = R850_Xtal_Pwr_tmp[R850_Tuner_Num]+1;	
		  
#endif

		  R850_Initial_done_flag[R850_Tuner_Num] = TRUE;
	} //end if(check init flag)

	//write initial reg
	if(R850_InitReg(R850_Tuner_Num) != RT_Success)        
		return RT_Fail;

	R850_pre_standard[R850_Tuner_Num] = R850_STD_SIZE;

	return RT_Success;
}



R850_ErrCode R850_InitReg(R850_TUNER_NUM_TYPE R850_Tuner_Num)//ok
{
	UINT8 InitArrayCunt = 0;
	
	//Write Full Table, Set Xtal Power = highest at initial
	R850_I2C_Len.RegAddr = 0;
	R850_I2C_Len.Len = R850_REG_NUM;


	if(R850_Xtal == 24000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
		{
			R850_I2C_Len.Data[InitArrayCunt] = R850_iniArray[0][InitArrayCunt];
			R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_iniArray[0][InitArrayCunt];
		}
	}
	else if(R850_Xtal == 16000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
		{
			R850_I2C_Len.Data[InitArrayCunt] = R850_iniArray[1][InitArrayCunt];
			R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_iniArray[1][InitArrayCunt];
		}
	}
	else if(R850_Xtal == 27000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
		{
			R850_I2C_Len.Data[InitArrayCunt] = R850_iniArray[2][InitArrayCunt];
			R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_iniArray[2][InitArrayCunt];
		}
	}
	else
	{
		//no support now
		return RT_Fail;
	}
#if(R850_CLOCK_OUT_ENABLE_AFTER_INIT==TRUE)
	//Clock Out Enable
	R850_I2C_Len.Data[34] = (R850_Array[R850_Tuner_Num][34] & 0xFB) ;  
	R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFB);  
#endif

	if(R850_I2C_Write_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		return RT_Fail;

	return RT_Success;
}
R850_ErrCode R850_Xtal_Check(R850_TUNER_NUM_TYPE R850_Tuner_Num)
{
	UINT8 i = 0;
	UINT8 lock_bank = 55;

	//set pll autotune = 64kHz  
	R850_I2C.RegAddr = 47;
	if(R850_Chip == R850_MP)  // R47[1:0] = 0
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC;
	else // R47[1] = 0
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][47];
	if(R850_I2C_Write(R850_Tuner_Num,&R850_I2C) != RT_Success)
		return RT_Fail;
/*
	//Xtal_pow=lowest & Xtal_div=1
	R850_I2C.RegAddr = 32;
	R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0x39) | 0x06 | 0x00;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][32];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
	    return RT_Fail;
*/
	//Set Ni, Si, DivNum    
	if (R850_Xtal == 24000)  //LO=510MHz, VCO=4080MHz
	{
		R850_Array[R850_Tuner_Num][27] = (R850_Array[R850_Tuner_Num][27] & 0x80) | 18;              //Ni=18	=> R27
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xFC) | 0;				//Si=0	=> R30[1:0]
		R850_Array[R850_Tuner_Num][29] = (R850_Array[R850_Tuner_Num][29] & 0x0F) | 0<<4;				//SDM=0000 0000 0000 00000	=> R29[7:4]
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xE3) | 0x08;           //div 8 => R30[4:2]
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x27) | 0x00 | 0x00;  //gm*2(24); Xtal div1 => R34[7:6] , R34[0]
		//R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x20;           //AGC ref clk (24) => same as VCO manual code
	}
	else if (R850_Xtal == 16000) //LO=510MHz, VCO=4080MHz
	{
		R850_Array[R850_Tuner_Num][27] = (R850_Array[R850_Tuner_Num][27] & 0x80) | 28;             //Ni=28 => R27
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xFC) | 2;				//Si=2  => R30[1:0]
		R850_Array[R850_Tuner_Num][29] = (R850_Array[R850_Tuner_Num][29] & 0x0F) | 8<<4;				//SDM=0000 0000 0000 00000	=> R29[7:4]
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xE3) | 0x08;			//div 8 => R30[4:2]
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x3E) | 0x80 | 0x00; //gm(16); Xtal div1 => R34[7:6] , R34[0]
		//R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x00;           //AGC ref clk (16) => same as VCO manual code
	}
	else if (R850_Xtal == 27000) //LO=509.9941MHz, VCO=4079.953MHz
	{
		R850_Array[R850_Tuner_Num][27] = (R850_Array[R850_Tuner_Num][27] & 0x80) | 28;             //Ni=28 => R27
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xFC) | 2;				//Si=2  => R30[1:0]
		R850_Array[R850_Tuner_Num][29] = 0xBE;				//SDM=1000 1110
		R850_Array[R850_Tuner_Num][30] = (R850_Array[R850_Tuner_Num][30] & 0xE3) | 0x08;			//div 8 => R30[4:2]
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x27) | 0x00 | 0x00;  //gm*2(24); Xtal div1 => R34[7:6] , R34[0]
		//R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x00;           //AGC ref clk (16) => same as VCO manual code
	}
	else  //no support 
	{
		return RT_Fail;
	}
	R850_I2C.RegAddr = 27;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = 30;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = 34;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = 29;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//set cap = 40p
	R850_I2C.RegAddr = 33;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x07) | 0xF8;  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	R850_I2C.RegAddr = 34;   //LSB
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF7) | 0x80;  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//set manual initial reg = 1 000000; 
	R850_I2C.RegAddr = 31;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x80) | 0x40;  //manual 
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//set auto
	R850_I2C.RegAddr = 31;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;


	for(i=0; i<XTAL_CHECK_SIZE; i++) //0~3
	{
	    // from weak to strong
		R850_I2C.RegAddr = 34;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | ((UINT8)(XTAL_HIGHEST-i)<<4);  //3~0
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		R850_Delay_MS(XTAL_CHK_DELAY);  //10 or 20ms??

		R850_I2C_Len.RegAddr = 0x00;
		R850_I2C_Len.Len = 3;
		R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);


        if(((R850_I2C_Len.Data[2] & 0x40) == 0x40) && ((R850_I2C_Len.Data[2] & 0x3F) <= (lock_bank+6)) && ((R850_I2C_Len.Data[2] & 0x3F) >= (lock_bank-6))) 
		{
		    R850_Xtal_Pwr_tmp[R850_Tuner_Num] = i;
			break;
		}

	    if(i==(XTAL_CHECK_SIZE-1))
		{
	        R850_Xtal_Pwr_tmp[R850_Tuner_Num] = i;
		}
	}


    return RT_Success;
}
R850_ErrCode R850_Cal_Prepare(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 u1CalFlag)
{
	 //R850_Cal_Info_Type  Cal_Info;
	 UINT8   InitArrayCunt = 0;
	 //Write Full Table, include PLL & RingPLL all settings
	 R850_I2C_Len.RegAddr = 0;
	 R850_I2C_Len.Len = R850_REG_NUM;

	 switch(u1CalFlag)
	 {
	    case R850_IMR_CAL:
				if(R850_Xtal == 24000)
				{
					//542MHz
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_IMR_CAL_Array[0][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_IMR_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R850_Xtal == 16000)
				{
					//542MHz
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_IMR_CAL_Array[1][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_IMR_CAL_Array[1][InitArrayCunt];
					}
				}
				else if(R850_Xtal == 27000)
				{
					//542MHz
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_IMR_CAL_Array[2][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_IMR_CAL_Array[2][InitArrayCunt];
					}
				}
				else
				{
					//no support now
					return RT_Fail;
				}
			break;

		case R850_IMR_LNA_CAL:						    

			break;

		case R850_LPF_CAL: 
				
				if(R850_Xtal == 24000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_LPF_CAL_Array[0][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_LPF_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R850_Xtal == 16000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_LPF_CAL_Array[1][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_LPF_CAL_Array[1][InitArrayCunt];
					}	
				}
				else if(R850_Xtal == 27000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R850_REG_NUM; InitArrayCunt ++)
					{
						R850_I2C_Len.Data[InitArrayCunt] = R850_LPF_CAL_Array[2][InitArrayCunt];
						R850_Array[R850_Tuner_Num][InitArrayCunt] = R850_LPF_CAL_Array[2][InitArrayCunt];
					}	
				}
				else
				{
				   //no support 27MHz now
					return RT_Fail;
				}
			break;		

		default:
			break;	

	 }

	 if(R850_I2C_Write_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		 return RT_Fail;
	  

      return RT_Success;
}




R850_ErrCode R850_IMR(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 IMR_MEM, UINT8 IM_Flag, UINT8 Rev_Mode)
{

	//-------------------------------------------------------------------
	//to do
	UINT32 RingVCO = 0;
	UINT32 RingFreq = 0;
	UINT32 RingRef = R850_Xtal;
	UINT8  divnum_ring = 0;
	//UINT8  u1MixerGain = 6;  //fix at initial test

	UINT8  IMR_Gain = 0;
	UINT8  IMR_Phase = 0;
	R850_SectType IMR_POINT;

	//R850_Array[R850_Tuner_Num][24] &= 0x3F;    //clear ring_div1, R24[7:6] 
	//R850_Array[R850_Tuner_Num][25] &= 0xFC;   //clear ring_div2, R25[1:0] 

	if(R850_Xtal==24000)  //24M	
	{
			divnum_ring = 17;
	}
	else if(R850_Xtal==16000) //16M
	{
		divnum_ring = 25;                    //3200/8/16.  32>divnum>7
	}
	else if(R850_Xtal==27000) //27M
	{
		divnum_ring = 15;                    //3200/8/16.  32>divnum>7
	}
	else //not support
	{
		 return RT_Fail;
	}
	
	 RingVCO = (divnum_ring)* 8 * RingRef;
	 RingFreq = RingVCO/48;

	switch(IMR_MEM)
	{
	case 0: // RingFreq = 136.0M  (16M, 24M) ;  RingFreq = 135.0M (27M) ; 
		RingFreq = RingVCO/24;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x02;  // ring_div1 /6 (2)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x08;  // ring_div2 /4 (2)	R35[1:0] => R36[3:2]
		break;
	case 1: // RingFreq = 326M  (16M, 24M) ;  RingFreq = 324.0M (27M) ; 
		RingFreq = RingVCO/10;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x01;  // ring_div1 /5 (1)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x04;  // ring_div2 /2 (1)	R35[1:0] => R36[3:2]
		break;
	case 2: // RingFreq = 544M  (16M, 24M) ;  RingFreq = 540.0M (27M) ; 
		RingFreq = RingVCO/6;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x02;  // ring_div1 /6 (2)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x00;  // ring_div2 /1 (0)	R35[1:0] => R36[3:2]
		break;
	case 3: // RingFreq = 816M  (16M, 24M) ;  RingFreq = 810.0M (27M) ; 
		RingFreq = RingVCO/4;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x00;  // ring_div1 /4 (0)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x00;  // ring_div2 /1 (0)	R35[1:0] => R36[3:2]		
		break;
	case 4: // RingFreq = 200M  (16M, 24M) ;  RingFreq = 202M (27M) ; 
		RingFreq = RingVCO/16;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x00;  // ring_div1 /4 (0)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x08;  // ring_div2 /4 (2)	R35[1:0] => R36[3:2]		
		break;
	case 5: // RingFreq = 136M  (16M, 24M) ;  RingFreq = 135.0M (27M) ; 
		RingFreq = RingVCO/24;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x02;  // ring_div1 /6 (2)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x08;  // ring_div2 /4 (2)	R35[1:0] => R36[3:2]
		break;
	case 6: // RingFreq = 326M  (16M, 24M) ;  RingFreq = 324.0M (27M) ; 
		RingFreq = RingVCO/10;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x01;  // ring_div1 /5 (1)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x04;  // ring_div2 /2 (1)	R35[1:0] => R36[3:2]
		break;
	case 7: // RingFreq = 544M  (16M, 24M) ;  RingFreq = 540.0M (27M) ; 
		RingFreq = RingVCO/6;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x02;  // ring_div1 /6 (2)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x00;  // ring_div2 /1 (0)	R35[1:0] => R36[3:2]
		break;
	case 8: // RingFreq = 816M  (16M, 24M) ;  RingFreq = 810.0M (27M) ; 
		RingFreq = RingVCO/4;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x00;  // ring_div1 /4 (0)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x00;  // ring_div2 /1 (0)	R35[1:0] => R36[3:2]		
		break;
	case 9: // RingFreq = 200M  (16M, 24M) ;  RingFreq = 202M (27M) ; 
		RingFreq = RingVCO/16;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x00;  // ring_div1 /4 (0)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x08;  // ring_div2 /4 (2)	R35[1:0] => R36[3:2]		
		break;
	default: // RingFreq = 544M  (16M, 24M) ;  RingFreq = 540.0M (27M) ; 
		RingFreq = RingVCO/6;
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xFC) | 0x02;  // ring_div1 /6 (2)	R34[6:5] => R36[1:0]
		R850_Array[R850_Tuner_Num][36] = (R850_Array[R850_Tuner_Num][36] & 0xF3) | 0x00;  // ring_div2 /1 (0)	R35[1:0] => R36[3:2]
		break;
	}

	//write RingPLL setting, R34[4:0] => R35[4:0]
	R850_Array[R850_Tuner_Num][35] = (R850_Array[R850_Tuner_Num][35] & 0xE0) | divnum_ring;   //ring_div_num, R34[4:0]

	if(RingVCO>=3200000)
	    R850_Array[R850_Tuner_Num][35] = (R850_Array[R850_Tuner_Num][35] & 0xBF);   //vco_band=high, R34[7]=0 => R35[6]
	 else
        R850_Array[R850_Tuner_Num][35] = (R850_Array[R850_Tuner_Num][35] | 0x40);      //vco_band=low, R34[7]=1 => R35[6]

	//write RingPLL setting, R35
	R850_I2C.RegAddr = 35;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	
    //write RingPLL setting, R36
	R850_I2C.RegAddr = 36;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//Ring PLL power initial at "min_lp"
/*
	//Ring PLL power, R25[2:1]
	if((RingFreq>0) && (RingFreq<R850_RING_POWER_FREQ))  
         R850_Array[R850_Tuner_Num][25] = (R850_Array[R850_Tuner_Num][25] & 0xF9) | 0x04;   //R25[2:1]=2'b10; min_lp
	else
        R850_Array[R850_Tuner_Num][25] = (R850_Array[R850_Tuner_Num][25] & 0xF9) | 0x00;   //R25[2:1]=2'b00; min

	R850_I2C.RegAddr = 0x19;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][25];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
*/
	if(Rev_Mode==R850_IMR_NOR)
	{
		//Must do MUX before PLL() 
		if(R850_MUX(R850_Tuner_Num, RingFreq - R850_IMR_IF, RingFreq, R850_STD_SIZE) != RT_Success)      //IMR MUX (LO, RF)
			return RT_Fail;

		R850_IF_GOLOBAL = R850_IMR_IF;
		if(R850_PLL(R850_Tuner_Num, (RingFreq - R850_IMR_IF), R850_STD_SIZE) != RT_Success)  //IMR PLL
			return RT_Fail;

		 //Img_R = normal
		 R850_I2C.RegAddr = 19;
		 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF);  //R20[7]=0 => R19[4]=0
	    // Mixer Amp LPF=7 (0 is widest)
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF8) | (R850_Mixer_Amp_LPF_IMR_CAL); 
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		if(IMR_MEM==4)
		{
			//output atten
			 R850_I2C.RegAddr = 36;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (0x10);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;
		}
		else
		{
			 //output atten
			 R850_I2C.RegAddr = 36;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (0x30);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;
		}

		//Mixer Gain = 8
		 R850_I2C.RegAddr = 41;
		 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (8);  //R41[3:0]=0
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			 return RT_Fail;

		//clear IQ_cap
		//IMR_POINT.Iqcap = R850_Array[R850_Tuner_Num][19] & 0x3F;
		IMR_POINT.Iqcap = 0;

		if(IM_Flag == TRUE)
		{
			 if(R850_IQ(R850_Tuner_Num, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
		else  //IMR_MEM 1, 0, 3, 4
		{
			if((IMR_MEM==1) || (IMR_MEM==3))
			{
				IMR_POINT.Gain_X = R850_IMR_Data[R850_Tuner_Num][2].Gain_X;   //node 3
				IMR_POINT.Phase_Y = R850_IMR_Data[R850_Tuner_Num][2].Phase_Y;
				IMR_POINT.Value = R850_IMR_Data[R850_Tuner_Num][2].Value;
			}
			else if((IMR_MEM==0) || (IMR_MEM==4))
			{
				IMR_POINT.Gain_X = R850_IMR_Data[R850_Tuner_Num][1].Gain_X;  
				IMR_POINT.Phase_Y = R850_IMR_Data[R850_Tuner_Num][1].Phase_Y;
				IMR_POINT.Value = R850_IMR_Data[R850_Tuner_Num][1].Value;
			}
	
			if(R850_F_IMR(R850_Tuner_Num, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
	}
	else
	{
		//Must do MUX before PLL() 
		if(R850_MUX(R850_Tuner_Num, RingFreq + R850_IMR_IF, RingFreq, R850_STD_SIZE) != RT_Success)      //IMR MUX (LO, RF)
			return RT_Fail;

		R850_IF_GOLOBAL = R850_IMR_IF;
		if(R850_PLL(R850_Tuner_Num, (RingFreq + R850_IMR_IF), R850_STD_SIZE) != RT_Success)  //IMR PLL
			return RT_Fail;

		//Img_R = inverse
		R850_I2C.RegAddr = 19;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x10);  //R20[7]=0 => R19[4]=1
	    // Mixer Amp LPF=7 or 4 depend on standard(0 is widest)
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF8) | (R850_Mixer_Amp_LPF_IMR_CAL); 
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		if(IMR_MEM==9)
		{
			//Mixer Gain = 7
			 R850_I2C.RegAddr = 41;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (7);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;

			//output atten
			 R850_I2C.RegAddr = 36;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (0x10);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;
		}
		else
		{
			//Mixer Gain = 6
			 R850_I2C.RegAddr = 41;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (6);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;

			 //output atten
			 R850_I2C.RegAddr = 36;
			 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (0x30);  // R41[3:0]=0
			 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
			 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
				 return RT_Fail;
		}



		//clear IQ_cap
		//IMR_POINT.Iqcap = R850_Array[R850_Tuner_Num][19] & 0x3F;
		IMR_POINT.Iqcap = 0;

		if(IM_Flag == TRUE)  // 7, 8
		{
			 if(R850_IQ(R850_Tuner_Num, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
		else  //IMR_MEM 6, 5, 9
		{
			if(IMR_MEM==6)
			{
				IMR_POINT.Gain_X = R850_IMR_Data[R850_Tuner_Num][7].Gain_X;    //node 6
				IMR_POINT.Phase_Y = R850_IMR_Data[R850_Tuner_Num][7].Phase_Y;
				IMR_POINT.Value = R850_IMR_Data[R850_Tuner_Num][7].Value;
			}
			else if((IMR_MEM==5) || (IMR_MEM==9))
			{
				IMR_POINT.Gain_X = R850_IMR_Data[R850_Tuner_Num][6].Gain_X;    
				IMR_POINT.Phase_Y = R850_IMR_Data[R850_Tuner_Num][6].Phase_Y;
				IMR_POINT.Value = R850_IMR_Data[R850_Tuner_Num][6].Value;
			}
			if(R850_F_IMR(R850_Tuner_Num, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
	}

	//Save IMR Value
	R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Gain_X  = IMR_POINT.Gain_X;
	R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Phase_Y = IMR_POINT.Phase_Y;
	R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Value = IMR_POINT.Value;
	R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Iqcap = IMR_POINT.Iqcap;	

	IMR_Gain = R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Gain_X & 0x2F;   //R20[3:0]
	IMR_Phase = R850_IMR_Data[R850_Tuner_Num][IMR_MEM].Phase_Y & 0x2F; //R21[3:0]


	if(((IMR_Gain & 0x0F)>6) || ((IMR_Phase & 0x0F)>6))
	{		
		R850_IMR_Cal_Result[R850_Tuner_Num] = 1; //fail
	}
	return RT_Success;
}


R850_ErrCode R850_PLL(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 LO_Freq, R850_Standard_Type R850_Standard)//ok
{
	UINT8  MixDiv = 2;
	UINT8  DivBuf = 0;
	UINT8  Ni = 0;
	UINT8  Si = 0;
	UINT8  DivNum = 0;
	UINT16  Nint = 0;
	UINT32 VCO_Min = 2200000;
	UINT32 VCO_Max = 4400000;
	UINT32 VCO_Freq = 0;
	UINT32 PLL_Ref	= R850_Xtal;		
	UINT32 VCO_Fra	= 0;		
	UINT16 Nsdm = 2;
	UINT16 SDM = 0;
	UINT16 SDM16to9 = 0;
	UINT16 SDM8to1 = 0;
	UINT8   XTAL_POW = 0;
	UINT16  u2XalDivJudge;
	UINT8   u1XtalDivRemain;
	UINT8   CP_CUR = 0x00;
	UINT8   CP_OFFSET = 0x00;
	UINT8   SDM_RES = 0x00;
	UINT8   NS_RES = 0x00;
	UINT8   IQGen_Cur = 0;    //DminDmin
	UINT8   IQBias = 1;           //BiasI
	UINT8   IQLoad = 0;          //3.2k/2
	UINT8   OutBuf_Bias = 0;   //max
	UINT8   BiasHf = 0;            //135u
	UINT8	PllArrayCunt = 0;

	if(R850_Chip == R850_MP)
		VCO_Min=2270000;
	else
		VCO_Min=2200000;	

	VCO_Max = VCO_Min*2;

	// VCO current = 0 (max)
	R850_I2C.RegAddr = 32;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | 0x00; // R31[1:0] = 0   => R32[3:2] = 0

	// VCO power = auto
	R850_I2C.RegAddr = 46;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF) | 0x40; // R26[7] = 1 => R46[6] = 1

	// HfDiv Buf = 6dB buffer
	R850_I2C.RegAddr = 37;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | 0x00; // R17[7]=0	=> R37[4]=0

	// Divider HfDiv current = 135u
	R850_I2C.RegAddr = 12;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | 0x00; // R10[1:0]=00	=> R12[3:2]=00

	// PLL LDOA=2.2V
	R850_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | 0x00; // R11[3:2]=00 => R11[3:2]=00

	// PFD DLDO=4mA
	R850_I2C.RegAddr = 12;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x3F) | 0x00; // R8[5:4]=00 => R12[7:6]=00

	// DLDO2=3mA
	R850_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | 0x10; // R11[5:4]=01 => R11[5:4]=01

	// HF Fiv LDO=7mA (new bonding set this off)
	R850_I2C.RegAddr = 9;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF9) | 0x00; // R12[2:1]=00	=> R9[2:1]=00

    //------ Xtal freq depend setting: Xtal Gm & AGC ref clk --------//
	if(R850_Xtal==24000)
	{
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x3F) | 0x00;  //gm*2(24)  R32[4:3]:00 => R34[7:6]:00
		R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x20;  //clk /3 (24) => R37[5]=1
	}
	else if(R850_Xtal==16000)
	{
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x3F) | 0x80;  //gm(16)	R32[4:3]:10 => R34[7:6]:10
		R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x00;  //clk /2 (16)	=> R37[5]=0
	}
	else if(R850_Xtal==27000)
	{
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0x3F) | 0x00;  //gm*2(24)  R32[4:3]:00 => R34[7:6]:00
		R850_Array[R850_Tuner_Num][37] = (R850_Array[R850_Tuner_Num][37] & 0xDF) | 0x20;  //clk /3 (24) => R37[5]=1
	}
	else  //not support Xtal freq
		return RT_Fail;

	//----- Set XTAL Power ------//
#if(R850_SHARE_XTAL==TRUE)
		XTAL_POW = 0;        //highest,       R32[2:1]=0
		//Set X'tal Cap
		if(R850_Tuner_Num == 0)
			R850_SetXtalCap(R850_Tuner_Num, R850_Xtal_cap);
		else
			R850_SetXtalCap(R850_Tuner_Num, R850_Xtal_cap_slave);
#else
		if(LO_Freq<100000) //Xtal PW : Low
		{
			if(R850_Xtal_Pwr[R850_Tuner_Num] <= XTAL_LOW )
			{
				XTAL_POW = 2;
			}
			else
			{
				XTAL_POW = 3 - R850_Xtal_Pwr[R850_Tuner_Num];
			}
		}
		else if((110000<=LO_Freq) && (LO_Freq<130000)) //Xtal PW: High
		{
			if(R850_Xtal_Pwr[R850_Tuner_Num] <= XTAL_HIGH )
			{
				XTAL_POW = 1;
			}
			else
			{
				XTAL_POW = 3 - R850_Xtal_Pwr[R850_Tuner_Num];
			}
		}
		else //Xtal PW : Highest
		{
			XTAL_POW = 0;
		}
		//Set X'tal Cap
		if(R850_Tuner_Num == 0)
			R850_SetXtalCap(R850_Tuner_Num, R850_Xtal_cap);
		else
			R850_SetXtalCap(R850_Tuner_Num, R850_Xtal_cap_slave);
#endif

	R850_I2C.RegAddr = 34;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (XTAL_POW<<4);	//R32[2:1] => R34[5:4]


	CP_CUR = 0x00;     //0.7m, R30[7:5]=000
	CP_OFFSET = 0x00;  //0u,     R37[1]=0
	if(R850_Xtal == 24000)
	{
		u2XalDivJudge = (UINT16) ((LO_Freq+R850_IF_GOLOBAL)/1000/12);
	//  48, 120 ,264 ,288, 336
		if((u2XalDivJudge==4)||(u2XalDivJudge==10)||(u2XalDivJudge==22)||(u2XalDivJudge==24)||(u2XalDivJudge==28))
		{
			CP_OFFSET = 0x02;  //30u,     R37[1]=1
		}
		else
		{
			CP_OFFSET = 0x00;  //0u,     R37[1]=0
		}
	}
	else if(R850_Xtal == 16000)
	{
		u2XalDivJudge = (UINT16) ((LO_Freq+R850_IF_GOLOBAL)/1000/8);
		//
		if((u2XalDivJudge==6)||(u2XalDivJudge==10)||(u2XalDivJudge==12)||(u2XalDivJudge==48))
		{
			CP_OFFSET = 0x02;  //30u,     R37[1]=1
		}
		else
		{
			CP_OFFSET = 0x00;  //0u,     R37[1]=0
		}
	}
	else if(R850_Xtal == 27000)
	{
		u2XalDivJudge = (UINT16) ((LO_Freq+R850_IF_GOLOBAL)/100/135);
		//  48, 120 ,264 ,288, 336
		if((u2XalDivJudge==4)||(u2XalDivJudge==10)||(u2XalDivJudge==22)||(u2XalDivJudge==24)||(u2XalDivJudge==28))
		{
			CP_OFFSET = 0x02;  //30u,     R37[1]=1
		}
		else
		{
			CP_OFFSET = 0x00;  //0u,     R37[1]=0
		}
	}

	R850_I2C.RegAddr = 30;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x1F) | (CP_CUR);	//    => R30[7:5]

	R850_I2C.RegAddr = 37;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD) | (CP_OFFSET);	//    => R37[1]

	//set pll autotune = 64kHz (fast)  R47[1:0](MP) ,  R47[0](MT1)
	R850_I2C.RegAddr = 47;
	if(R850_Chip == R850_MP)
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC;
	else
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD;

	//Divider
	while(MixDiv <= 64)
	{
		if(((LO_Freq * MixDiv) >= VCO_Min) && ((LO_Freq * MixDiv) < VCO_Max))
		{
			DivBuf = MixDiv;
			while(DivBuf > 2)
			{
				DivBuf = DivBuf >> 1;
				DivNum ++;
			}			
			break;
		}
		MixDiv = MixDiv << 1;
	}

	//IQ Gen block & BiasHF & NS_RES & SDM_Res
	if(MixDiv <= 4)  //Div=2,4
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 1;           //BiasI   
		IQLoad = 0;          //3.2k/2 
		OutBuf_Bias = 0;   //0 (max)     
		BiasHf = 0;           //135u
		SDM_RES = 0;     //short  
		NS_RES = 0;        //0R 
	}
	else if(MixDiv == 8) 
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 1;   //1 
		BiasHf = 1;           //110u
		SDM_RES = 0;     //short
		NS_RES = 1;        //800R 
	}
	else if(MixDiv == 16) 
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 2;   //2 
		BiasHf = 1;           //110u
		SDM_RES = 0;     //short  
		NS_RES = 0;        //0R
	}
	else if(MixDiv >= 32) //32, 64
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 3;   //3 (min)
		BiasHf = 1;           //110u
		SDM_RES = 0;     //short
		NS_RES = 0;        //0R
	}
	else
	{
		return RT_Fail;
	}


	if(Divider_Manual==1)
	{
		
	}
	else
	{
		//Xtal Div setting
		if(R850_Standard == R850_STD_SIZE) //for cal, RingPLL not support xtal div2
		{
				R850_XtalDiv = XTAL_DIV1; //div1 for calibration
		}
		else  //DTV
		{
			if(R850_Xtal==24000)
			   u2XalDivJudge = (UINT16) ((LO_Freq + R850_IF_GOLOBAL)/1000/12);
			else if(R850_Xtal==16000)
			   u2XalDivJudge = (UINT16) ((LO_Freq + R850_IF_GOLOBAL)/1000/8);
			else if(R850_Xtal==27000)
			   u2XalDivJudge = (UINT16) ((LO_Freq + R850_IF_GOLOBAL)/100/135);
			else
			   return RT_Fail;

			u1XtalDivRemain = (UINT8) (u2XalDivJudge % 2);

			if(LO_Freq < (372000+R850_IF_HIGH))	  
			{
		   		if(u1XtalDivRemain==1) //odd
				{
					R850_XtalDiv = XTAL_DIV1;
				}
				else  //even, spur area
				{
					R850_XtalDiv = XTAL_DIV1_2;
				}
			}
			else if(((LO_Freq + R850_IF_GOLOBAL) >= 478000) && ((LO_Freq + R850_IF_GOLOBAL) < 482000) && (R850_Standard == R850_ISDB_T_4063))
			{
				R850_XtalDiv = XTAL_DIV4;
			}
			else
			{
				R850_XtalDiv = XTAL_DIV1;
			}
		}
	}


	//Xtal divider setting
	//R850_XtalDiv = XTAL_DIV2; //div 1, 2, 4
	if(R850_XtalDiv==XTAL_DIV1)
	{
		PLL_Ref = R850_Xtal;	         
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFC) | 0x00; //b7:2nd_div2=0, b6:1st_div2=0	 R32[7:6] => R34[1:0]
	}
	else if(R850_XtalDiv==XTAL_DIV1_2)
	{
		PLL_Ref = R850_Xtal/2;   
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFC) | 0x02; //1st_div2=0(R34[0]), 2nd_div2=1(R34[1])
	}
	else if(R850_XtalDiv==XTAL_DIV2_1)
	{
		PLL_Ref = R850_Xtal/2;   
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFC) | 0x01; //1st_div2=1(R34[0]), 2nd_div2=0(R34[1])
	}
	else if(R850_XtalDiv==XTAL_DIV4)  //24MHz
	{
		PLL_Ref = R850_Xtal/4;	         
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFC) | 0x03; //b7:2nd_div2=1, b6:1st_div2=1  R32[7:6] => R34[1:0]
	}
	

	//IQ gen current R10[7] => R11[0]
	R850_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE) | (IQGen_Cur); 

	//Out Buf Bias R10[6:5] => R45[3:2]
	R850_I2C.RegAddr = 45;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | (OutBuf_Bias<<2); 

	//BiasI R29[2] => R46[0]
	R850_I2C.RegAddr = 46;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE) | (IQBias); 

	//IQLoad R36[5] => R46[1]
	R850_I2C.RegAddr = 46;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD) | (IQLoad<<1); 

	//BiasHF R29[7:6] => R32[1:0]
	R850_I2C.RegAddr = 32;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | (BiasHf); 

	//SDM_RES R30[7] => R32[4]
	R850_I2C.RegAddr = 32;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | (SDM_RES<<4); 

	//NS_RES  R36[0]  => R17[7]
	R850_I2C.RegAddr = 17;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F) | (NS_RES<<7); 

	//Divider num R35[5:3] => R30[4:2]
	R850_I2C.RegAddr = 30;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE3) | (DivNum << 2);  

	VCO_Freq = LO_Freq * MixDiv;
	Nint = (UINT16) (VCO_Freq / 2 / PLL_Ref);
	VCO_Fra = (UINT16) (VCO_Freq - 2 * PLL_Ref * Nint);

	//Boundary spur prevention
	if (VCO_Fra < PLL_Ref/64)           //2*PLL_Ref/128
		VCO_Fra = 0;
	else if (VCO_Fra > PLL_Ref*127/64)  //2*PLL_Ref*127/128
	{
		VCO_Fra = 0;
		Nint ++;
	}
	else if((VCO_Fra > PLL_Ref*127/128) && (VCO_Fra < PLL_Ref)) //> 2*PLL_Ref*127/256,  < 2*PLL_Ref*128/256
		VCO_Fra = PLL_Ref*127/128;      // VCO_Fra = 2*PLL_Ref*127/256
	else if((VCO_Fra > PLL_Ref) && (VCO_Fra < PLL_Ref*129/128)) //> 2*PLL_Ref*128/256,  < 2*PLL_Ref*129/256
		VCO_Fra = PLL_Ref*129/128;      // VCO_Fra = 2*PLL_Ref*129/256
	else
		VCO_Fra = VCO_Fra;

	//Ni & Si	
	Ni = (UINT8) ((Nint - 13) / 4);
	Si = (UINT8) (Nint - 4 *Ni - 13);

	R850_I2C.RegAddr = 27;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x80) | Ni;     //R26[6:0] => R27[6:0]

	R850_I2C.RegAddr = 30;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | Si;  //R35[7:6] => R30[1:0]
         	
	//pw_sdm & pw_dither
	R850_I2C.RegAddr = 32;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] &= 0x3F;        //R29[1:0] => R32[7:6]
	if(VCO_Fra == 0)
	{
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] |= 0xC0;
	}

	//SDM calculator
	while(VCO_Fra > 1)
	{			
		if (VCO_Fra > (2*PLL_Ref / Nsdm))
		{		
			SDM = SDM + 32768 / (Nsdm/2);
			VCO_Fra = VCO_Fra - 2*PLL_Ref / Nsdm;
			if (Nsdm >= 0x8000)
				break;
		}
		Nsdm = Nsdm << 1;
	}

	SDM16to9 = SDM >> 8;
	SDM8to1 =  SDM - (SDM16to9 << 8);

	R850_I2C.RegAddr = 29;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (UINT8) SDM16to9;  //R28 => R29

	R850_I2C.RegAddr = 28;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (UINT8) SDM8to1;    //R27 => R28


	R850_I2C_Len.RegAddr = 8;
	R850_I2C_Len.Len = 40;

	for(PllArrayCunt = 0 ; PllArrayCunt < 40 ; PllArrayCunt ++)
	{
		R850_I2C_Len.Data[PllArrayCunt] = R850_Array[R850_Tuner_Num][PllArrayCunt + 8];
	}
	if(R850_I2C_Write_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		return RT_Fail;

	
	if(R850_XtalDiv == XTAL_DIV1)
		R850_Delay_MS(PLL_LOCK_DELAY);
	else if((R850_XtalDiv == XTAL_DIV1_2) || (R850_XtalDiv == XTAL_DIV2_1))
	    R850_Delay_MS(PLL_LOCK_DELAY*2);
	else
	    R850_Delay_MS(PLL_LOCK_DELAY*4);  

	//set pll autotune = 1khz (2'b10)
	R850_I2C.RegAddr = 47;
	if(R850_Chip == R850_MP)
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | 0x02;
	else
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD) | 0x02;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;

}


R850_ErrCode R850_MUX(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 LO_KHz, UINT32 RF_KHz, R850_Standard_Type R850_Standard)
{	
	UINT8 Reg_IMR_Gain   = 0;
	UINT8 Reg_IMR_Phase  = 0;
	UINT8 Reg_IMR_Iqcap  = 0;

	//Freq_Info_Type Freq_Info1;
	Freq_Info1 = R850_Freq_Sel(LO_KHz, RF_KHz, R850_Standard);


	// TF_DIPLEXER
	R850_I2C.RegAddr = 14;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | (Freq_Info1.TF_DIPLEXER<<2);  //LPF    => R14[3:2]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//TF_HPF_BPF => R16[2:0]   	TF_HPF_CNR => R16[4:3]
	R850_I2C.RegAddr = 16;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE0) | (Freq_Info1.TF_HPF_BPF) | (Freq_Info1.TF_HPF_CNR << 3);  // R16[2:0], R16[4:3]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	// RF Polyfilter
	R850_I2C.RegAddr = 18;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | (Freq_Info1.RF_POLY);  //R17[6:5] => R18[1:0]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	// LNA Cap
	R850_I2C.RegAddr = 14;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | (Freq_Info1.LPF_CAP<<4);	  //R16[3:0]	=>	R14[7:4]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	// LNA Notch
	R850_I2C.RegAddr = 15;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (Freq_Info1.LPF_NOTCH);  //R16[7:4]  =>  R15[3:0]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;



	//Set_IMR
	if( (R850_IMR_done_flag[R850_Tuner_Num] == TRUE) && (R850_IMR_Cal_Result[R850_Tuner_Num]==0))
	{
		if(R850_Mixer_Mode==R850_IMR_NOR)
		{
			Reg_IMR_Gain = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_NOR].Gain_X & 0x2F;   //R20[4:0] => R20[3:0]
			Reg_IMR_Phase = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_NOR].Phase_Y & 0x2F; //R21[4:0] => R21[3:0]
			Reg_IMR_Iqcap = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_NOR].Iqcap;                  //0,1,2
		}
		else
		{
			Reg_IMR_Gain = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_REV].Gain_X & 0x2F;   //R20[4:0] => R20[3:0]
			Reg_IMR_Phase = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_REV].Phase_Y & 0x2F; //R21[4:0] => R21[3:0]
			Reg_IMR_Iqcap = R850_IMR_Data[R850_Tuner_Num][Freq_Info1.IMR_MEM_REV].Iqcap;                  //0,1,2		
		}
	}
	else
	{
		Reg_IMR_Gain = 0;
	    Reg_IMR_Phase = 0;
		Reg_IMR_Iqcap = 0;
	}

	//Gain, R20[4:0]
	R850_I2C.RegAddr = R850_IMR_GAIN_REG;                  
	R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] = (R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] & 0xD0) | (Reg_IMR_Gain & 0x2F);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

    //Phase, R21[4:0]
	R850_I2C.RegAddr = R850_IMR_PHASE_REG;                  
	R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] = (R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] & 0xD0) | (Reg_IMR_Phase & 0x2F);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//Iqcap, R21[7:6]
	R850_I2C.RegAddr = R850_IMR_IQCAP_REG;
	R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] = (R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] & 0x3F) | (Reg_IMR_Iqcap<<6);
	R850_I2C.Data =R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG]  ;
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}

R850_ErrCode R850_IQ(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont)
{
	R850_SectType Compare_IQ[3];
	UINT8   X_Direction;  // 1:X, 0:Y

	//------- increase Filter gain max to let ADC read value significant ---------//
	R850_I2C.RegAddr = 41;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0xF0);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];  
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	

	//give a initial value, no useful
	Compare_IQ[0].Gain_X  = R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] & 0xD0; 
	Compare_IQ[0].Phase_Y = R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] & 0xD0;


	    // Determine X or Y
	    if(R850_IMR_Cross(R850_Tuner_Num, &Compare_IQ[0], &X_Direction) != RT_Success)
			return RT_Fail;

		if(X_Direction==1)
		{
			//compare and find min of 3 points. determine I/Q direction
		    if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
			  return RT_Fail;

		    //increase step to find min value of this direction
		    if(R850_CompreStep(R850_Tuner_Num, &Compare_IQ[0], R850_IMR_GAIN_REG) != RT_Success)  //X
			  return RT_Fail;
		}
		else
		{
		   //compare and find min of 3 points. determine I/Q direction
		   if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		   	 return RT_Fail;

		   //increase step to find min value of this direction
		   if(R850_CompreStep(R850_Tuner_Num, &Compare_IQ[0], R850_IMR_PHASE_REG) != RT_Success)  //Y
			 return RT_Fail;
		}

		//Another direction
		if(X_Direction==1) //Y-direct
		{	    
           if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success) //Y
		     return RT_Fail;

		   //compare and find min of 3 points. determine I/Q direction
		   if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		   	 return RT_Fail;

		   //increase step to find min value of this direction
		   if(R850_CompreStep(R850_Tuner_Num, &Compare_IQ[0], R850_IMR_PHASE_REG) != RT_Success)  //Y
			 return RT_Fail;
		}
		else //X-direct
		{
		   if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, R850_IMR_PHASE_REG, &Compare_IQ[0]) != RT_Success) //X
		     return RT_Fail;
        
		   //compare and find min of 3 points. determine I/Q direction
		   if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		     return RT_Fail;

	       //increase step to find min value of this direction
		   if(R850_CompreStep(R850_Tuner_Num, &Compare_IQ[0], R850_IMR_GAIN_REG) != RT_Success) //X
		     return RT_Fail;
		}
		

		//--- Check 3 points again---//
		if(X_Direction==1)  //X-direct
		{
		    if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, R850_IMR_PHASE_REG, &Compare_IQ[0]) != RT_Success) //X
			  return RT_Fail;
		}
		else  //Y-direct
		{
		   if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success) //Y
			return RT_Fail;
		}

		if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
			return RT_Fail;

    //Section-9 check
	if(R850_Section(R850_Tuner_Num, &Compare_IQ[0]) != RT_Success)
			return RT_Fail;

	//clear IQ_Cap = 0
	//Compare_IQ[0].Iqcap = R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] & 0x3F;
	Compare_IQ[0].Iqcap = 0;

	if(R850_IMR_Iqcap(R850_Tuner_Num, &Compare_IQ[0]) != RT_Success)
			return RT_Fail;

	*IQ_Pont = Compare_IQ[0];

	//reset gain/phase/iqcap control setting
	R850_I2C.RegAddr = R850_IMR_GAIN_REG;
	R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] = R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] & 0xD0;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = R850_IMR_PHASE_REG;
	R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] = R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] & 0xD0;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = R850_IMR_IQCAP_REG;
	R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] = R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] & 0x3F;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}



//--------------------------------------------------------------------------------------------
// Purpose: record IMR results by input gain/phase location
//          then adjust gain or phase positive 1 step and negtive 1 step, both record results
// input: FixPot: phase or gain
//        FlucPot phase or gain
//        PotReg: Reg20 or Reg21
//        CompareTree: 3 IMR trace and results
// output: TREU or FALSE
//--------------------------------------------------------------------------------------------
R850_ErrCode R850_IQ_Tree(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R850_SectType* CompareTree)
{
	UINT8 TreeCunt  = 0;
	UINT8 PntReg = 0;
		
	//PntReg is reg to change; FlucPot is change value
	if(PotReg == R850_IMR_GAIN_REG)
		PntReg = R850_IMR_PHASE_REG; //phase control
	else
		PntReg = R850_IMR_GAIN_REG; //gain control

	for(TreeCunt = 0; TreeCunt<3; TreeCunt ++)
	{
		R850_I2C.RegAddr = PotReg;
		R850_I2C.Data = FixPot;
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		R850_I2C.RegAddr = PntReg;
		R850_I2C.Data = FlucPot;
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		if(R850_Muti_Read(R850_Tuner_Num, &CompareTree[TreeCunt].Value) != RT_Success)
			return RT_Fail;
	
		if(PotReg == R850_IMR_GAIN_REG)
		{
			CompareTree[TreeCunt].Gain_X  = FixPot;
			CompareTree[TreeCunt].Phase_Y = FlucPot;
		}
		else
		{
			CompareTree[TreeCunt].Phase_Y  = FixPot;
			CompareTree[TreeCunt].Gain_X = FlucPot;
		}
		
		if(TreeCunt == 0)   //try right-side point
			FlucPot ++; 
		else if(TreeCunt == 1) //try left-side point
		{
			if((FlucPot & 0x0F) == 1) //if absolute location is 1, change I/Q direction
			{
				if(FlucPot & 0x20) //b[5]:I/Q selection. 0:Q-path, 1:I-path
				{
					//FlucPot = (FlucPot & 0xE0) | 0x01;
					FlucPot = (FlucPot & 0xD0) | 0x01;
				}
				else
				{
					//FlucPot = (FlucPot & 0xE0) | 0x11;
					FlucPot = (FlucPot & 0xD0) | 0x21;
				}
			}
			else
				FlucPot = FlucPot - 2;  
		}
	}

	return RT_Success;
}




//-----------------------------------------------------------------------------------/ 
// Purpose: compare IMR result aray [0][1][2], find min value and store to CorArry[0]
// input: CorArry: three IMR data array
// output: TRUE or FALSE
//-----------------------------------------------------------------------------------/
R850_ErrCode R850_CompreCor(R850_SectType* CorArry)
{
	UINT8 CompCunt = 0;
	R850_SectType CorTemp;

	for(CompCunt=3; CompCunt > 0; CompCunt --)
	{
		if(CorArry[0].Value > CorArry[CompCunt - 1].Value) //compare IMR result [0][1][2], find min value
		{
			CorTemp = CorArry[0];
			CorArry[0] = CorArry[CompCunt - 1];
			CorArry[CompCunt - 1] = CorTemp;
		}
	}

	return RT_Success;
}


//-------------------------------------------------------------------------------------//
// Purpose: if (Gain<9 or Phase<9), Gain+1 or Phase+1 and compare with min value
//          new < min => update to min and continue
//          new > min => Exit
// input: StepArry: three IMR data array
//        Pace: gain or phase register
// output: TRUE or FALSE 
//-------------------------------------------------------------------------------------//
R850_ErrCode R850_CompreStep(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* StepArry, UINT8 Pace)
{
	R850_SectType StepTemp;
	
	//min value already saved in StepArry[0]
	StepTemp.Phase_Y = StepArry[0].Phase_Y;  //whole byte data
	StepTemp.Gain_X = StepArry[0].Gain_X;
	//StepTemp.Iqcap  = StepArry[0].Iqcap;

	while(((StepTemp.Gain_X & 0x0F) < R850_IMR_TRIAL) && ((StepTemp.Phase_Y & 0x0F) < R850_IMR_TRIAL))  
	{
		if(Pace == R850_IMR_GAIN_REG)
			StepTemp.Gain_X ++;
		else
			StepTemp.Phase_Y ++;
	
		R850_I2C.RegAddr = R850_IMR_GAIN_REG;
		R850_I2C.Data = StepTemp.Gain_X ;
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		R850_I2C.RegAddr = R850_IMR_PHASE_REG;
		R850_I2C.Data = StepTemp.Phase_Y;
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		if(R850_Muti_Read(R850_Tuner_Num, &StepTemp.Value) != RT_Success)
			return RT_Fail;

		if(StepTemp.Value <= StepArry[0].Value)
		{
			StepArry[0].Gain_X  = StepTemp.Gain_X;
			StepArry[0].Phase_Y = StepTemp.Phase_Y;
			//StepArry[0].Iqcap = StepTemp.Iqcap;
			StepArry[0].Value   = StepTemp.Value;
		}
		else if((StepTemp.Value - 2*R850_ADC_READ_COUNT) > StepArry[0].Value)
		{
			break;
		}
		
	} //end of while()
	
	return RT_Success;
}


//-----------------------------------------------------------------------------------/ 
// Purpose: read multiple IMR results for stability
// input: IMR_Reg: IMR result address
//        IMR_Result_Data: result 
// output: TRUE or FALSE
//-----------------------------------------------------------------------------------/
R850_ErrCode R850_Muti_Read(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8* IMR_Result_Data) //ok
{
	
	R850_Delay_MS(R850_ADC_READ_DELAY);
	R850_I2C_Len.RegAddr = 0;
	R850_I2C_Len.Len = 2;              // read 0x01
	if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
	{
		R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);
	}
	*IMR_Result_Data = R850_I2C_Len.Data[1] & 0x3F;

	return RT_Success;
}

 //ok
R850_ErrCode R850_Section(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont)
{
	R850_SectType Compare_IQ[3];
	R850_SectType Compare_Bet[3];

	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xDF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)  // y-direction
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x20) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R850_CompreCor(&Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return RT_Success;
}


R850_ErrCode R850_IMR_Cross(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont, UINT8* X_Direct)
{

	R850_SectType Compare_Cross[9]; //(0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0)+(0,Q-2)(0,I-2)(Q-2,0)(I-2,0)
	R850_SectType Compare_Temp;
	UINT8 CrossCount = 0;
	UINT8 RegGain = R850_Array[R850_Tuner_Num][R850_IMR_GAIN_REG] & 0xD0;
	UINT8 RegPhase = R850_Array[R850_Tuner_Num][R850_IMR_PHASE_REG] & 0xD0;

	//memset(&Compare_Temp,0, sizeof(R850_SectType));
	Compare_Temp.Gain_X = 0;
	Compare_Temp.Phase_Y = 0;
	Compare_Temp.Iqcap = 0;
	Compare_Temp.Value = 255;

	for(CrossCount=0; CrossCount<9; CrossCount++)
	{

		if(CrossCount==0)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==1)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;       //0
		  Compare_Cross[CrossCount].Phase_Y = RegPhase + 1;  //Q-1
		}
		else if(CrossCount==2)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;               //0
		  Compare_Cross[CrossCount].Phase_Y = (RegPhase | 0x20) + 1; //I-1
		}
		else if(CrossCount==3)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain + 1; //Q-1
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==4)
		{
		  //Compare_Cross[CrossCount].Gain_X = (RegGain | 0x10) + 1; //I-1
		  Compare_Cross[CrossCount].Gain_X = (RegGain | 0x20) + 1; //I-1
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==5)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;       //0
		  Compare_Cross[CrossCount].Phase_Y = RegPhase + 2;  //Q-2
		}
		else if(CrossCount==6)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;               //0
		  Compare_Cross[CrossCount].Phase_Y = (RegPhase | 0x20) + 2; //I-2
		}
		else if(CrossCount==7)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain + 2; //Q-2
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==8)
		{
		  Compare_Cross[CrossCount].Gain_X = (RegGain | 0x20) + 2; //I-2
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}

    	R850_I2C.RegAddr = R850_IMR_GAIN_REG;
	    R850_I2C.Data = Compare_Cross[CrossCount].Gain_X;
	    if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		   return RT_Fail;

	    R850_I2C.RegAddr = R850_IMR_PHASE_REG;
	    R850_I2C.Data = Compare_Cross[CrossCount].Phase_Y;
	    if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		  return RT_Fail;
	
        if(R850_Muti_Read(R850_Tuner_Num, &Compare_Cross[CrossCount].Value) != RT_Success)
		  return RT_Fail;

		if( Compare_Cross[CrossCount].Value < Compare_Temp.Value)
		{
		  Compare_Temp.Value = Compare_Cross[CrossCount].Value;
		  Compare_Temp.Gain_X = Compare_Cross[CrossCount].Gain_X;
		  Compare_Temp.Phase_Y = Compare_Cross[CrossCount].Phase_Y;		
		}
	} //end for loop


	if(((Compare_Temp.Phase_Y & 0x2F)==0x01) || (Compare_Temp.Phase_Y & 0x2F)==0x02)  //phase Q1 or Q2
	{
      *X_Direct = (UINT8) 0;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[1].Gain_X;    //0
	  IQ_Pont[1].Phase_Y = Compare_Cross[1].Phase_Y; //Q1
	  IQ_Pont[1].Value = Compare_Cross[1].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[5].Gain_X;   //0
	  IQ_Pont[2].Phase_Y = Compare_Cross[5].Phase_Y;//Q2
	  IQ_Pont[2].Value = Compare_Cross[5].Value;
	}
	else if(((Compare_Temp.Phase_Y & 0x2F)==0x21) || (Compare_Temp.Phase_Y & 0x2F)==0x22)  //phase I1 or I2
	{
      *X_Direct = (UINT8) 0;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[2].Gain_X;    //0
	  IQ_Pont[1].Phase_Y = Compare_Cross[2].Phase_Y; //Q1
	  IQ_Pont[1].Value = Compare_Cross[2].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[6].Gain_X;   //0
	  IQ_Pont[2].Phase_Y = Compare_Cross[6].Phase_Y;//Q2
	  IQ_Pont[2].Value = Compare_Cross[6].Value;
	}
	else if(((Compare_Temp.Gain_X & 0x2F)==0x01) || (Compare_Temp.Gain_X & 0x2F)==0x02)  //gain Q1 or Q2
	{
      *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[3].Gain_X;    //Q1
	  IQ_Pont[1].Phase_Y = Compare_Cross[3].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[3].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[7].Gain_X;   //Q2
	  IQ_Pont[2].Phase_Y = Compare_Cross[7].Phase_Y;//0
	  IQ_Pont[2].Value = Compare_Cross[7].Value;
	}
	else if(((Compare_Temp.Gain_X & 0x2F)==0x21) || (Compare_Temp.Gain_X & 0x2F)==0x22)  //gain I1 or I2
	{
      *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[4].Gain_X;    //I1
	  IQ_Pont[1].Phase_Y = Compare_Cross[4].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[4].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[8].Gain_X;   //I2
	  IQ_Pont[2].Phase_Y = Compare_Cross[8].Phase_Y;//0
	  IQ_Pont[2].Value = Compare_Cross[8].Value;
	}
	else //(0,0) 
	{	
	  *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y;
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[3].Gain_X;    //Q1
	  IQ_Pont[1].Phase_Y = Compare_Cross[3].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[3].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[4].Gain_X;   //I1
	  IQ_Pont[2].Phase_Y = Compare_Cross[4].Phase_Y; //0
	  IQ_Pont[2].Value = Compare_Cross[4].Value;
	}
	return RT_Success;
}


//----------------------------------------------------------------------------------------//
// purpose: search surrounding points from previous point 
//          try (x-1), (x), (x+1) columns, and find min IMR result point
// input: IQ_Pont: previous point data(IMR Gain, Phase, ADC Result, RefRreq)
//                 will be updated to final best point                 
// output: TRUE or FALSE
//----------------------------------------------------------------------------------------//
R850_ErrCode R850_F_IMR(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Pont)
{
	R850_SectType Compare_IQ[3];
	R850_SectType Compare_Bet[3];

	 //------- increase Filter gain max to let ADC read value significant ---------//
	R850_I2C.RegAddr = 41;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0xF0);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];  
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xDF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)  // y-direction
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x20) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R850_IQ_Tree(R850_Tuner_Num, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R850_IMR_GAIN_REG, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	if(R850_CompreCor(&Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R850_CompreCor(&Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	//clear IQ_Cap = 0
	//Compare_Bet[0].Iqcap = R850_Array[R850_Tuner_Num][3] & 0xFC;
	Compare_Bet[0].Iqcap = 0;

	if(R850_IMR_Iqcap(R850_Tuner_Num, &Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return RT_Success;
}


R850_ErrCode R850_IMR_Iqcap(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_SectType* IQ_Point)   
{
    R850_SectType Compare_Temp;
	int i = 0;

	//Set Gain/Phase to right setting
	R850_I2C.RegAddr = R850_IMR_GAIN_REG;
	R850_I2C.Data = IQ_Point->Gain_X; 
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_I2C.RegAddr = R850_IMR_PHASE_REG;
	R850_I2C.Data = IQ_Point->Phase_Y;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_I2C.Data;
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//try iqcap
	for(i=0; i<3; i++)
	{
		Compare_Temp.Iqcap = (UINT8) i;  
		R850_I2C.RegAddr = R850_IMR_IQCAP_REG;
		R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] = (R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG] & 0x3F) | (Compare_Temp.Iqcap<<6);  
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_IMR_IQCAP_REG];  
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			   return RT_Fail;

		

		if(R850_Muti_Read(R850_Tuner_Num, &(Compare_Temp.Value)) != RT_Success)
			   return RT_Fail;

		if(Compare_Temp.Value < IQ_Point->Value)
		{
			IQ_Point->Value = Compare_Temp.Value; 
			IQ_Point->Iqcap = Compare_Temp.Iqcap;  //0, 1, 2
		}
		else if(Compare_Temp.Value == IQ_Point->Value)
		{
			IQ_Point->Value = Compare_Temp.Value; 
			IQ_Point->Iqcap = Compare_Temp.Iqcap;  //0, 1, 2
		}
	}

    return RT_Success;
}




R850_ErrCode R850_SetStandard(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Standard_Type RT_Standard)
{
	UINT8 u1FilCalGap = 16;

	if(RT_Standard != R850_pre_standard[R850_Tuner_Num])
	{
		 if(R850_InitReg(R850_Tuner_Num) != RT_Success)      
		     return RT_Fail;
	}
    R850_pre_standard[R850_Tuner_Num] = RT_Standard;


    Sys_Info1 = R850_Sys_Sel(RT_Standard);

	// Filter Calibration	
	 u1FilCalGap = 16;

	//HPF ext protection
    if(R850_Fil_Cal_flag[R850_Tuner_Num][RT_Standard] == FALSE)
	{
		R850_Fil_Cal_code[R850_Tuner_Num][RT_Standard] = R850_Filt_Cal_ADC(R850_Tuner_Num, Sys_Info1.FILT_CAL_IF, Sys_Info1.BW, u1FilCalGap);
		R850_Fil_Cal_BW[R850_Tuner_Num][RT_Standard] = R850_Bandwidth;
        R850_Fil_Cal_flag[R850_Tuner_Num][RT_Standard] = TRUE;
        R850_Fil_Cal_LpfLsb[R850_Tuner_Num][RT_Standard] = R850_Lpf_Lsb;

		//protection
		if(R850_IMR_Cal_Result[R850_Tuner_Num]==1) //fail
		{
			if((R850_Fil_Cal_BW[R850_Tuner_Num][RT_Standard]==3) && (R850_Fil_Cal_code[R850_Tuner_Num][RT_Standard]==15))  //6M/15
			{
				R850_Fil_Cal_BW[R850_Tuner_Num][RT_Standard] = R850_Fil_Cal_BW_def[RT_Standard];
				R850_Fil_Cal_code[R850_Tuner_Num][RT_Standard] = (R850_Fil_Cal_code_def[RT_Standard]>>1);
				R850_Fil_Cal_LpfLsb[R850_Tuner_Num][RT_Standard] = (R850_Fil_Cal_code_def[RT_Standard] & 0x01);
			}
		}
	    //Reset register and Array
	    if(R850_InitReg(R850_Tuner_Num) != RT_Success)
		   return RT_Fail;
	}
	// Set LPF Lsb bit
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE) | (R850_Fil_Cal_LpfLsb[R850_Tuner_Num][RT_Standard]);  //R23[0]
	// Set LPF fine code
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE1) | (R850_Fil_Cal_code[R850_Tuner_Num][RT_Standard]<<1);  //R23[4:1]
	// Set LPF coarse BW
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x9F) | (R850_Fil_Cal_BW[R850_Tuner_Num][RT_Standard]<<5);  //R23[6:5]
	//Set HPF notch  R23[7]
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F) | (Sys_Info1.HPF_NOTCH<<7);  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;


	// Set HPF corner 
	R850_I2C.RegAddr = 24;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | (Sys_Info1.HPF_COR<<4);	//R24[3:0] => R24[7:4]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;


	// Set Filter Auto Ext  
	R850_I2C.RegAddr = 18;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF) | (Sys_Info1.FILT_EXT_ENA<<6);  // =>R18[6]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//set Filter Comp				 //R24[3:2]
	R850_I2C.RegAddr = 24;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | (Sys_Info1.FILT_COMP<<2);  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	

	// Set AGC clk R47[3:2]
	R850_I2C.RegAddr = 47;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | (Sys_Info1.AGC_CLK<<2);  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
     

	// Set IMG Gain R47[3:2]
	if(R850_Chip == R850_MP)   //R46[4] High   [High(0), Low(1)]
	{
		R850_I2C.RegAddr = 46;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | (Sys_Info1.IMG_GAIN<<4);
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;
	}
	else  //MSB:R44[0] , LSB:R46[4]  highest   [lowest(0), high(1), low(2), highest(3)]
	{
		R850_I2C.RegAddr = 44;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE) | ((Sys_Info1.IMG_GAIN & 0x02)>>1);  
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;
		R850_I2C.RegAddr = 46;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | ((Sys_Info1.IMG_GAIN & 0x01)<<4);  
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;
	}


/*

	// Record SW Version 
	R850_I2C.RegAddr = 0x0C;
	R850_Array[R850_Tuner_Num][12] = (R850_Array[R850_Tuner_Num][12] & 0xF0) | VER_NUM;  
    R850_I2C.Data = R850_Array[R850_Tuner_Num][12];
    if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
       return RT_Fail;

	// Record init flag
	R850_I2C.RegAddr = 0x1A;
	R850_Array[R850_Tuner_Num][26] = ((R850_Array[R850_Tuner_Num][26] & 0xF0) | (R850_Initial_done_flag<<1) | (R850_Fil_Cal_flag[RT_Standard]<<2) 
		| R850_IMR_done_flag | (R850_DetectTfType<<3));  
    R850_I2C.Data = R850_Array[R850_Tuner_Num][26];
    if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
       return RT_Fail;
    

	//Rspin
	//disable IF_AGC read, R8[7]=0
	R850_I2C.RegAddr = 0x08;
	R850_Array[R850_Tuner_Num][8] = R850_Array[R850_Tuner_Num][8] & 0x7F;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][8];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//ADC power off, R12[7]=1
	R850_I2C.RegAddr = 0x0C;
	R850_Array[R850_Tuner_Num][12] = R850_Array[R850_Tuner_Num][12] | 0x80;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][12];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	
*/
	return RT_Success;
}


UINT8  R850_Filt_Cal_ADC(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 IF_Freq, UINT8 R850_BW, UINT8 FilCal_Gap)
{
	 UINT8     u1FilterCodeResult = 0;
	 UINT8     u1FilterCode = 0;
	 UINT8     u1FilterCalValue = 0;
	 UINT8     u1FilterCalValuePre = 0;
	 UINT8     initial_cnt = 0;
	 UINT8     i = 0;
	 //UINT32   RingVCO = 0;
	 UINT32   RingFreq = 72000;
	 UINT8   ADC_Read_Value = 0;
	 UINT8	 ADC_Read_Value_8M5Hz = 0;
	 UINT8   LPF_Count = 0;
	 //UINT32   RingRef = R850_Xtal;
	 //UINT8     divnum_ring = 0;
	 //UINT8    VGA_Count = 0;


	 if(R850_Cal_Prepare(R850_Tuner_Num, R850_LPF_CAL) != RT_Success)      
	      return RT_Fail;

	 R850_IF_GOLOBAL = IF_Freq;
	 //Set PLL (TBD, normal)
	 if(R850_PLL(R850_Tuner_Num, (RingFreq - IF_Freq), R850_STD_SIZE) != RT_Success)   //FilCal PLL
	       return RT_Fail;

	 //------- increase Filter gain to let ADC read value significant ---------//
	 for(LPF_Count=5; LPF_Count < 16; LPF_Count ++)  
	 {
		R850_I2C.RegAddr = 41;
		R850_Array[R850_Tuner_Num][41] = (R850_Array[R850_Tuner_Num][41] & 0x0F) | (LPF_Count<<4);
		R850_I2C.Data = R850_Array[R850_Tuner_Num][41];  
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

		R850_Delay_MS(FILTER_GAIN_DELAY); //
		
		if(R850_Muti_Read(R850_Tuner_Num, &ADC_Read_Value) != RT_Success)
			return RT_Fail;

		if(ADC_Read_Value > 40*R850_ADC_READ_COUNT)
		{
			break;
		}
	 }


	 //If IF_Freq>10MHz, need to compare 8.5MHz ADC Value, 
	 //If the ADC values greater than 8 in the same gain,the filter corner select 8M / 0
	 if(IF_Freq>=10000)
	 {
		 R850_IF_GOLOBAL = 8500;
		 //Set PLL (TBD, normal)
		 if(R850_PLL(R850_Tuner_Num, (RingFreq - 8500), R850_STD_SIZE) != RT_Success)   //FilCal PLL
			 return RT_Fail;

		 R850_Delay_MS(FILTER_GAIN_DELAY); //
		
		 if(R850_Muti_Read(R850_Tuner_Num, &ADC_Read_Value_8M5Hz) != RT_Success)
			 return RT_Fail;

		 if(ADC_Read_Value_8M5Hz > (ADC_Read_Value + 8) )
		 {
			R850_Bandwidth = 0; //8M
			R850_Lpf_Lsb = 0;	//0
			u1FilterCodeResult = 0;
			return u1FilterCodeResult;
		 }
		 else
		 {
			R850_IF_GOLOBAL = IF_Freq;
			//Set PLL (TBD, normal)
			if(R850_PLL(R850_Tuner_Num, (RingFreq - IF_Freq), R850_STD_SIZE) != RT_Success)   //FilCal PLL
				return RT_Fail;
		 }
	 }



	 //------- Try suitable BW --------//
	 if(R850_BW==2) //6M
         initial_cnt = 1;  //try 7M first
	 else
		 initial_cnt = 0;  //try 8M first

	 for(i=initial_cnt; i<3; i++)
	 {
         if(i==0)
             R850_Bandwidth = 0; //8M
		 else if(i==1)
			 R850_Bandwidth = 2; //7M
		 else
			 R850_Bandwidth = 3; //6M, (not 2!!!!!)

		 //Set BW R22[5:4] => R23[6:5]
		 R850_I2C.RegAddr = 23;	
		 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xCF) | (R850_Bandwidth<<5);   
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];		
		 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;	

		 // read code 0 R22[4:1] => R23[4:1]
		 R850_I2C.RegAddr = 23;
		 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE1);  //code 0
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			  return RT_Fail;

		 R850_Delay_MS(FILTER_CODE_DELAY); //delay ms
	     
		 if(R850_Muti_Read(R850_Tuner_Num, &u1FilterCalValuePre) != RT_Success)
			  return RT_Fail;

		 //read code 26 R22[4:1] => R23[4:1]
		 R850_I2C.RegAddr = 23;
		 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE1) | (13<<1);  //code 26
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			  return RT_Fail;

		 R850_Delay_MS(FILTER_CODE_DELAY); //delay ms
	     
		 if(R850_Muti_Read(R850_Tuner_Num, &u1FilterCalValue) != RT_Success)
			  return RT_Fail;

		 if(u1FilterCalValuePre > (u1FilterCalValue+16))  //suitable BW found
			 break;
	 }

     //-------- Try LPF filter code ---------//
	 u1FilterCalValuePre = 0;
	 for(u1FilterCode=0; u1FilterCode<16; u1FilterCode++)
	 {
         R850_I2C.RegAddr = 23;
         R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][ R850_I2C.RegAddr] & 0xE1) | (u1FilterCode<<1);
         R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
         if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
              return RT_Fail;

		 R850_Delay_MS(FILTER_CODE_DELAY); //delay ms

		 if(R850_Muti_Read(R850_Tuner_Num, &u1FilterCalValue) != RT_Success)
		      return RT_Fail;

		 if((IF_Freq>=10000)&&(u1FilterCode==0))
		 {
			u1FilterCalValuePre = ADC_Read_Value_8M5Hz;
		 }
		 else if(u1FilterCode==0)
		 {
              u1FilterCalValuePre = u1FilterCalValue;
		 }

		 if((u1FilterCalValue+FilCal_Gap*R850_ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCode;
			  break;
		 }
	 }

     //Try LSB bit
	 if(u1FilterCodeResult>0)   //try code-1 & lsb=1
	 {		 
		 R850_I2C.RegAddr = 23;
         R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE0) | ((u1FilterCodeResult-1)<<1) | 0x01;
         R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
         if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
              return RT_Fail;

		 R850_Delay_MS(FILTER_GAIN_DELAY); //delay ms

		 if(R850_Muti_Read(R850_Tuner_Num, &u1FilterCalValue) != RT_Success)
			  return RT_Fail;

		 if((u1FilterCalValue+FilCal_Gap*R850_ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCodeResult - 1;
			 R850_Lpf_Lsb = 1;
		 }
		 else
		 {
		 	 //u1FilterCodeResult = u1FilterCodeResult;
			 R850_Lpf_Lsb = 0;
		 }
	 }
     
	 if(u1FilterCode==16)
          u1FilterCodeResult = 15;

	  return u1FilterCodeResult;

}

R850_ErrCode R850_SetFrequency(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Set_Info R850_INFO) //Write Multi byte 
{

	 UINT32	LO_KHz;
	 UINT8    Img_R;
	 UINT8 SetFreqArrayCunt;

	  //Get Sys-Freq parameter
	 if(R850_Nrb_Det_Mode==R850_NRB_DET_ON)
	 {
		SysFreq_Info1 = R850_SysFreq_NrbDetOn_Sel(R850_INFO.R850_Standard, R850_INFO.RF_KHz);
	 }
	 else
	 {
		SysFreq_Info1 = R850_SysFreq_NrbDetOff_Sel(R850_INFO.R850_Standard, R850_INFO.RF_KHz);
	 }

	 R850_IMR_point_num = Freq_Info1.IMR_MEM_NOR;

     // Check Input Frequency Range
	 if((R850_INFO.RF_KHz<40000) || (R850_INFO.RF_KHz>1002000))
	 {
	          return RT_Fail;
	 }

	 if(R850_Mixer_Mode==R850_IMR_REV)
	 {
		 LO_KHz = R850_INFO.RF_KHz - Sys_Info1.IF_KHz;
		 Img_R = 1;
	 }
	 else
	 {
		 LO_KHz = R850_INFO.RF_KHz + Sys_Info1.IF_KHz;
		 Img_R = 0;
	 }

	 R850_I2C.RegAddr = 19;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | (Img_R<<4);  //R20[7] => R19[4]
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;


	//Set MUX dependent var. Must do before PLL()
    if(R850_MUX(R850_Tuner_Num, LO_KHz, R850_INFO.RF_KHz, R850_INFO.R850_Standard) != RT_Success)   //normal MUX
       return RT_Fail;

	R850_IF_GOLOBAL = Sys_Info1.IF_KHz;
    //Set PLL
    if(R850_PLL(R850_Tuner_Num, LO_KHz, R850_INFO.R850_Standard) != RT_Success) //noraml PLL
       return RT_Fail;

	// PW
	// Set NA det power R10[6]
	R850_I2C.RegAddr = 10;
	if(R850_External_LNA == 0)	//External LNA Disable => depend on setting
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF) | (SysFreq_Info1.NA_PWR_DET<<6);
	else	//External LNA Enable => fixed
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF);

	//Set Man Buf Cur R16[5]
	R850_I2C.RegAddr = 16;
	if(R850_External_LNA == 0)	//External LNA Disable => depend on initial value
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xDF) | (R850_iniArray[0][R850_I2C.RegAddr] & 0x20);
	else	//External LNA Enable => fixed
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x20);


	//LNA_NRB_DET R11[7]
	R850_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F) | (SysFreq_Info1.LNA_NRB_DET<<7);  

	//LNA
	// LNA_TOP R38[2:0]
	R850_I2C.RegAddr = 38;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF8) | (7 - SysFreq_Info1.LNA_TOP);

	// LNA VTL/H R39[7:0]
	R850_I2C.RegAddr = 39;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr ] & 0x00) | SysFreq_Info1.LNA_VTL_H;

	// RF_LTE_PSG R17[4]
	R850_I2C.RegAddr = 17;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr ] & 0xEF) | (SysFreq_Info1.RF_LTE_PSG<<4);

	//RF
	// RF TOP R38[6:4]
	R850_I2C.RegAddr = 38;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x8F) | ((7 - SysFreq_Info1.RF_TOP)<<4);

	// RF VTL/H R42[7:0]
	R850_I2C.RegAddr = 42;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x00) | SysFreq_Info1.RF_VTL_H;

	// RF Gain Limt  (MSB:R18[2] & LSB:R16[6])
	switch(SysFreq_Info1.RF_GAIN_LIMIT)
	{
	case 0://'b00
		R850_Array[R850_Tuner_Num][18] = (R850_Array[R850_Tuner_Num][18] & 0xFB);
		R850_Array[R850_Tuner_Num][16] = (R850_Array[R850_Tuner_Num][16] & 0xBF);
		break;
	case 1://'b01
		R850_Array[R850_Tuner_Num][18] = (R850_Array[R850_Tuner_Num][18] & 0xFB);
		R850_Array[R850_Tuner_Num][16] = (R850_Array[R850_Tuner_Num][16] | 0x40);
		break;
	case 2://'b10
		R850_Array[R850_Tuner_Num][18] = (R850_Array[R850_Tuner_Num][18] | 0x02);
		R850_Array[R850_Tuner_Num][16] = (R850_Array[R850_Tuner_Num][16] & 0xBF);
		break;
	case 3://'b11
		R850_Array[R850_Tuner_Num][18] = (R850_Array[R850_Tuner_Num][18] | 0x02);
		R850_Array[R850_Tuner_Num][16] = (R850_Array[R850_Tuner_Num][16] | 0x40);
		break;
	}

	//MIXER & FILTER
	//MIXER_AMP_LPF  R19[2:0]
	R850_I2C.RegAddr = 19;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF8) | SysFreq_Info1.MIXER_AMP_LPF;  
	
    // MIXER TOP R40[3:0]
	R850_I2C.RegAddr = 40;
    R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (15 - SysFreq_Info1.MIXER_TOP); 

	// Filter TOP R44[3:0] for MP, R44[3:1] for MT1
	R850_I2C.RegAddr = 44;
	if(R850_Chip == R850_MP)
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | (15-SysFreq_Info1.FILTER_TOP);
	else
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF1) | ((7-SysFreq_Info1.FILTER_TOP)<<1);

	//FILT_3TH_LPF_CUR=0;	//R10[4] [high (0), low (1)]
	R850_I2C.RegAddr = 10;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | (SysFreq_Info1.FILT_3TH_LPF_CUR<<4);  

	// 3th_LPF_Gain R24[1:0]
	R850_I2C.RegAddr = 24;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFC) | SysFreq_Info1.FILT_3TH_LPF_GAIN;  

    // MIXER VTH & Filter VTH  R41[7:0]
	R850_I2C.RegAddr = 41;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x00) | SysFreq_Info1.MIXER_VTH | SysFreq_Info1.FILTER_VTH);

    // MIXER VTL & Filter VTL R43[7:0]
	R850_I2C.RegAddr = 43;
    R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x00) | SysFreq_Info1.MIXER_VTL | SysFreq_Info1.FILTER_VTL);

	// Mixer Gain Limt R22[7:6]
	R850_I2C.RegAddr = 22;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x3F) | (SysFreq_Info1.MIXER_GAIN_LIMIT << 6);

	// MIXER_DETBW_LPF R46[7]
	R850_I2C.RegAddr = 46;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F) | (SysFreq_Info1.MIXER_DETBW_LPF << 7);
	
	//Discharge
	//LNA_RF Discharge Mode  (R45[1:0]=2'b01; R9[6]=1)	=> (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	
	if(SysFreq_Info1.LNA_RF_DIS_MODE==0)  //auto (normal)
	{
	    R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x00;	//00
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x01; //  //1
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x20;//	//1
	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==1)  //both(fast+slow)
	{
		R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x03;	//11
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x01; //  //1
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x20;//	//1
	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==2)  //both(slow)
	{
		R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x03;	//11
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x00;   //0
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x00;	//0
	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==3)  //LNA(slow)
	{
		R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x03;	//11
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x01;  // //1
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x00;	//0
	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==4)  //RF(slow)
	{
		R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x03;	//11
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x00;   //0
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x20;//	//1
	}
	else
	{
	 	R850_Array[R850_Tuner_Num][45] = (R850_Array[R850_Tuner_Num][45] & 0xFC) | 0x00;	//00
		R850_Array[R850_Tuner_Num][31] = (R850_Array[R850_Tuner_Num][31] & 0xFE) | 0x01; //  //1
		R850_Array[R850_Tuner_Num][32] = (R850_Array[R850_Tuner_Num][32] & 0xDF) | 0x20;//	//1
	}

	//LNA_RF_CHARGE_CUR R31[1]  
	R850_I2C.RegAddr = 31;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD) | (SysFreq_Info1.LNA_RF_CHARGE_CUR<<1);  

	//LNA_RF_dis current  R13[5]
	R850_I2C.RegAddr = 13;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xDF) | (SysFreq_Info1.LNA_RF_DIS_CURR<<5);  

	//RF_slow disch(5:4) / fast disch(7:6)  //(R45[7:4])
	R850_I2C.RegAddr = 45;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | (SysFreq_Info1.RF_DIS_SLOW_FAST<<4);  

	//LNA slow disch(5:4) / fast disch(7:6) =>	R44[7:4]
	R850_I2C.RegAddr = 44;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | (SysFreq_Info1.LNA_DIS_SLOW_FAST<<4);  

	//BB disch current R25[6]
	R850_I2C.RegAddr = 25;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF) | (SysFreq_Info1.BB_DIS_CURR<<6);  

	//Mixer/Filter disch  R37[7:6]
	R850_I2C.RegAddr = 37;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x3F) | (SysFreq_Info1.MIXER_FILTER_DIS<<6);  

	//BB Det Mode  R37[2]
	R850_I2C.RegAddr = 37;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFB) | (SysFreq_Info1.BB_DET_MODE<<2);  

	//Polyphase
	//ENB_POLY_GAIN  R25[1]
	R850_I2C.RegAddr = 25;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFD) | (SysFreq_Info1.ENB_POLY_GAIN<<1);

	//NRB  
	// NRB TOP R40[7:4]
	R850_I2C.RegAddr = 40;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | ((15 - SysFreq_Info1.NRB_TOP)<<4);

	//NRB LPF & HPF BW  R26[7:6 & 3:2]
	R850_I2C.RegAddr = 26;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x33) | (SysFreq_Info1.NRB_BW_HPF<<2) | (SysFreq_Info1.NRB_BW_LPF<<6);

	//NBR Image TOP adder R46[3:2]
	R850_I2C.RegAddr = 46;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | (SysFreq_Info1.IMG_NRB_ADDER<<2);  

	//VGA
	//HPF_COMP R13[2:1]	
	R850_I2C.RegAddr = 13;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF9) | (SysFreq_Info1.HPF_COMP<<1);  

	//FB_RES_1ST  //R21[4]
	R850_I2C.RegAddr = 21;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xEF) | (SysFreq_Info1.FB_RES_1ST<<4);  

	//other setting

	// Set AGC clk R47[3:2]    only for isdbt 4.063 (set 1Khz because Div/4, original agc clk is 512Hz)
	if( (R850_INFO.RF_KHz >= 478000) && (R850_INFO.RF_KHz < 482000) && (R850_INFO.R850_Standard == R850_ISDB_T_4063) )
	{
		R850_I2C.RegAddr = 47;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3);  
	}

	switch(R850_INFO.R850_Standard)
	{
	case R850_DVB_C_6M:
	case R850_DVB_C_8M:
	case R850_DVB_C_6M_IF_5M:
	case R850_DVB_C_8M_IF_5M:
	case R850_J83B:
	case R850_J83B_IF_5M:
		//For DVB-C-8M AGC Clk = 1KHz  R47[3:2]=0,
		R850_I2C.RegAddr = 47;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3);  
		break;
	default:
		break;
	}

    //IF AGC1
	R850_I2C.RegAddr = 25;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xDF;


	//Set LT 
    if(R850_INFO.R850_LT==LT_ON)
	{
		//LT Sel: active LT(after LNA) R8[6]=1 ; acLT PW: ON R8[7]=1
		R850_Array[R850_Tuner_Num][8] = (R850_Array[R850_Tuner_Num][8] | 0xC0 );    
		//Pulse LT on R10[1]=1
		R850_Array[R850_Tuner_Num][10] = (R850_Array[R850_Tuner_Num][10] | 0x02);    
	}
	else
	{
		//LT Sel: active LT(after LNA) R8[6]=1 ; acLT PW: OFF R8[7]=0
		R850_Array[R850_Tuner_Num][8] = ((R850_Array[R850_Tuner_Num][8] | 0x40) & 0x7F);
		//Pulse LT on R10[1]=0
		R850_Array[R850_Tuner_Num][10] = (R850_Array[R850_Tuner_Num][10] & 0xFD);
	}


    //Set Clk Out
	if(R850_INFO.R850_ClkOutMode==CLK_OUT_OFF)
	{
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] | 0x04);   //no clk out  R34[2] = 1
	}
	else
	{
		R850_Array[R850_Tuner_Num][34] = (R850_Array[R850_Tuner_Num][34] & 0xFB);   //clk out  R34[2] = 0
	}

	R850_I2C_Len.RegAddr = 8;
	R850_I2C_Len.Len = 40;

	for(SetFreqArrayCunt = 0 ; SetFreqArrayCunt < 40 ; SetFreqArrayCunt ++)
	{
		R850_I2C_Len.Data[SetFreqArrayCunt] = R850_Array[R850_Tuner_Num][SetFreqArrayCunt + 8];
	}
	if(R850_I2C_Write_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		return RT_Fail;

//R8[2]
//LDO bypass		550MHz~670MHz	R8[2]=1
//LDO 2.95v			other			R8[2]=0
/*
	R850_I2C.RegAddr = 8;
	if((R850_INFO.RF_KHz>=550000) && (R850_INFO.RF_KHz<670000))
	{
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x04;
	}
	else
	{
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFB;
	}
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
*/
	 return RT_Success;
}


R850_ErrCode R850_SetPllData(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_Set_Info R850_INFO)
{	  
	  if(R850_Initial_done_flag[R850_Tuner_Num]==FALSE)
	  {
	      R850_Init(R850_Tuner_Num, R850_INFO.R850_Standard);
	  }

      if(R850_SetStandard(R850_Tuner_Num, R850_INFO.R850_Standard) != RT_Success)
		  return RT_Fail;

      if(R850_SetFrequency(R850_Tuner_Num, R850_INFO) != RT_Success)
          return RT_Fail;

      return RT_Success;
}


R850_ErrCode R850_Standby(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_LoopThrough_Type R850_STANDBY_LT)
{
	UINT8 i;

	for(i=0; i<R850_REG_NUM; i++)
	{
		R850_SBY[R850_Tuner_Num][i]=R850_Array[R850_Tuner_Num][i];
	}

	 //All, LDO , LNA
	 R850_I2C.RegAddr = 8;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][ R850_I2C.RegAddr] & 0xC3) | 0x03);  
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //Mixer Cur=low, Mixer PW, RF Buf PW, Hfdiv_ldo_Cur, TF Buf PW=high
	 R850_I2C.RegAddr = 9;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = 0xEE;  
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //IQ Gen, NAT PW, Channel fil cur= low, RF nrb det, MixAmp Cur
	 R850_I2C.RegAddr = 10;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBB) | 0xB9);  
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //LNA nrb det, Ring PW, pll_LDO, ADC, IQGen Cur
	 R850_I2C.RegAddr = 11;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = 0xFE;    
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //AGC PW, LNA_RF Det, Xtal LDO PW, PFD_dldo
	 R850_I2C.RegAddr = 12;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF0) | 0x0F;    
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //Set LT 
     if(R850_STANDBY_LT==LT_ON)
	 {
		//LT Sel: off LT(before LNA) R8[6]=0 ; acLT PW: off R8[7]=0
		R850_Array[R850_Tuner_Num][8] = (R850_Array[R850_Tuner_Num][8] & 0x3F);
		//Pulse LT off R10[1]=0
		R850_Array[R850_Tuner_Num][10] = (R850_Array[R850_Tuner_Num][10] & 0xFD);
	 }
	 else
	 {
		//LT Sel: active LT(after LNA) R8[6]=1 ; acLT PW: OFF R8[7]=0
		R850_Array[R850_Tuner_Num][8] = ((R850_Array[R850_Tuner_Num][8] | 0x40) & 0x7F);
		//Pulse LT off R10[1]=0
		R850_Array[R850_Tuner_Num][10] = (R850_Array[R850_Tuner_Num][10] & 0xFD);
	 }

	 R850_I2C.RegAddr = 8;
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 R850_I2C.RegAddr = 10;
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	//LNA manual mode and gain =31; R13[0]=1 , R13[5]=1(Gain MSB)
	 R850_I2C.RegAddr = 13;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x21);
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	//LNA manual Gain = 31  R39[7:4]
	 R850_I2C.RegAddr = 39;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0xF0);
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;


	 //Diplexer sel bypass R14[3:2] = 01
	 R850_I2C.RegAddr = 14;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xF3) | 0x04); 
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;


	 //VGA code mode  R25[2]
	 R850_I2C.RegAddr = 25;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x04; 
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //Rf Buf manual 0  R17[6] = 1    R42[7:4] = 0
	 R850_I2C.RegAddr = 17;
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x40; 
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 R850_I2C.RegAddr = 42; 
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F); 
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 //LNA Cur = Lowest R8[5:4] = 11
	 R850_I2C.RegAddr = 8; 
	 R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x30); 
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	 if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
			return RT_Fail;

	 R850_Standby_flag[R850_Tuner_Num] = TRUE;
	
	return RT_Success;
}

//-----------------------------------------------------------------------//
//  This function is used to wake up tuner from Standby mode   //
//-----------------------------------------------------------------------//
R850_ErrCode R850_WakeUp(R850_TUNER_NUM_TYPE R850_Tuner_Num)
{
	UINT8 i;
	UINT8 PLL_LDO_A; //R11[3:2]  = 11 (OFF)
	UINT8 PLL_LDO_D; //R11[5:4]  = 11 (OFF)
	UINT8 PDF_dldo;  //R12[7:6]  = 11 (OFF)
	//UINT8 Mixer_pw;	 //R9[5] = 1 (OFF)
	//UINT8 IQ_Gen_pw; //R10[7] = 1 (OFF)
	if(R850_Standby_flag[R850_Tuner_Num] == FALSE)
	{
		return RT_Success;
	}

	PLL_LDO_A = R850_SBY[R850_Tuner_Num][11] & 0x0C;
	PLL_LDO_D = R850_SBY[R850_Tuner_Num][11] & 0x30;
	PDF_dldo = R850_SBY[R850_Tuner_Num][12] & 0xC0;
  
	R850_SBY[R850_Tuner_Num][9] =  R850_SBY[R850_Tuner_Num][9]  | 0x20;	 //R9[5] = 1 (OFF)   Mixer_pw
	R850_SBY[R850_Tuner_Num][10] = R850_SBY[R850_Tuner_Num][10] | 0x80;  //R10[7] = 1 (OFF)   IQ_Gen_pw
	R850_SBY[R850_Tuner_Num][11] = R850_SBY[R850_Tuner_Num][11] | 0x3C;  //R11[5:4]  = 11 (OFF) PLL_LDO_D   &   R11[3:2]  = 11 (OFF) PLL_LDO_A
	R850_SBY[R850_Tuner_Num][12] = R850_SBY[R850_Tuner_Num][12] | 0xC0;  //R12[7:6]  = 12 (OFF)  PDF_dldo
	
	R850_I2C_Len.RegAddr = 0;
	R850_I2C_Len.Len = R850_REG_NUM;
	for(i = 0; i<R850_REG_NUM; i ++)
	{
		R850_I2C_Len.Data[i] = R850_SBY[R850_Tuner_Num][i];
		R850_Array[R850_Tuner_Num][i] = R850_SBY[R850_Tuner_Num][i];
	}
	if(R850_I2C_Write_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		return RT_Fail;

	//Mixer ON  R9[5] = 0 (ON)
	R850_I2C.RegAddr = 9;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xDF; 
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//IQ Gen ON  R10[7] = 0 (ON)
	R850_I2C.RegAddr = 10;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//R12[7:6]  = 12 (ON)  PDF_dldo
	R850_I2C.RegAddr = 12;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = ((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x3F) | PDF_dldo); 
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	//R11[5:4]  = 11 (OFF) PLL_LDO_D   &   R11[3:2]  = 11 (OFF) PLL_LDO_A
	R850_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (((R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xC3) | PLL_LDO_A) | PLL_LDO_D);  //R9[5]=0
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	R850_Standby_flag[R850_Tuner_Num] = FALSE;

	return RT_Success;
}

R850_ErrCode R850_GetRfGain(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_RF_Gain_Info *pR850_rf_gain)
{
	UINT16 acc_lna_gain[32] = {  0, 15, 26, 34, 50, 61, 75, 87, 101, 117,			//0~9
	                            130, 144, 154, 164, 176, 188, 199, 209, 220, 226,	//10~19
								233, 232, 232, 232, 232, 247, 262, 280, 296, 311,	//20~29
								296, 308											//30~31
                               }; 
	UINT16 acc_rf_gain[16] = {  0, 15, 26, 34, 50, 61, 75, 87, 101, 117,			//0~9
								130, 144, 154, 164, 176, 188 };						//10~15

	UINT16 acc_mixer_gain[16] = {  0, 0, 0, 0, 9, 22, 32, 44, 56, 68,				//0~9
								 80, 90, 100, 100, 100, 100 };						//10~15

	R850_I2C_Len.RegAddr = 0x00;
	R850_I2C_Len.Len = 6;
	if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
	{
		R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);
	}

	pR850_rf_gain->RF_gain1 = (R850_I2C_Len.Data[3] & 0x1F);            //lna
	pR850_rf_gain->RF_gain2 = (R850_I2C_Len.Data[4] & 0x0F);            //rf
	pR850_rf_gain->RF_gain3 = (R850_I2C_Len.Data[4] & 0xF0)>>4;       //mixer
	pR850_rf_gain->RF_gain4 = (R850_I2C_Len.Data[5] & 0x0F);             //filter
/*
	if(pR850_rf_gain->RF_gain1 > 24) 
        pR850_rf_gain->RF_gain1 = 24;  

	//Mixer Amp Gain
	if(pR850_rf_gain->RF_gain3 > 10)
        pR850_rf_gain->RF_gain3 = 10;  //MixerAmp gain max is 10	
	
	pR850_rf_gain->RF_gain_comb = (acc_lna_gain[pR850_rf_gain->RF_gain1] + acc_rfbuf_gain + pR850_rf_gain->RF_gain3*12);
*/
	pR850_rf_gain->RF_gain_comb = acc_lna_gain[pR850_rf_gain->RF_gain1]
		                        + acc_rf_gain[pR850_rf_gain->RF_gain2]
		                        + acc_mixer_gain[pR850_rf_gain->RF_gain3]
								+ pR850_rf_gain->RF_gain4*14;
    return RT_Success;
}





R850_ErrCode R850_RfGainMode(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_RF_Gain_TYPE R850_RfGainType)
{
    UINT8 MixerGain = 0;
	UINT8 RfGain = 0;
	UINT8 LnaGain = 0;
	//UINT8 FilterGain = 0;

	if(R850_RfGainType==RF_MANUAL)
	{
		//LNA auto off R13[0]
	     R850_I2C.RegAddr = 13;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x01;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][13];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer buffer off R12[7]
	     R850_I2C.RegAddr = 12;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x80;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer auto off R12[6]
	     R850_I2C.RegAddr = 12;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xBF;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;

		R850_I2C_Len.RegAddr = 0x00;
		R850_I2C_Len.Len = 4; 
		if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
		{
		    R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);
		}

		RfGain = (R850_I2C_Len.Data[4] & 0x0F);
		MixerGain = ((R850_I2C_Len.Data[4] & 0xF0) >> 4);  
		LnaGain = R850_I2C_Len.Data[3] & 0x1F;

		//set LNA gain  R13[5] & R39[7:4]
	    R850_I2C.RegAddr = 13;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xDF) | ((LnaGain & 0x10));
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		   return RT_Fail;
		R850_I2C.RegAddr = 39;
		R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | ((LnaGain & 0x0F)<<4);
		R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		   return RT_Fail;

		//set Mixer Buffer gain R42[7:4]
		R850_I2C.RegAddr = 0x1A;
		R850_Array[R850_Tuner_Num][26] = (R850_Array[R850_Tuner_Num][26] & 0x0F) | (RfGain<<4);
		R850_I2C.Data = R850_Array[R850_Tuner_Num][26];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		   return RT_Fail;

		//set Mixer gain  R41[3:0]
		R850_I2C.RegAddr = 0x07;
		R850_Array[R850_Tuner_Num][7] = (R850_Array[R850_Tuner_Num][7] & 0xF0) | MixerGain;
		R850_I2C.Data = R850_Array[R850_Tuner_Num][7];
		if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		   return RT_Fail;
	}
	else
	{
	    //LNA auto on R13[0]
	     R850_I2C.RegAddr = 13;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer buffer on R12[7]
	     R850_I2C.RegAddr = 12;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x7F;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer auto on  R12[6]
	     R850_I2C.RegAddr = 12;
	     R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] | 0x40;
		 R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		       return RT_Fail;
	}

    return RT_Success;
}

//------------------------------------------------------------------//
//  R850_PLL_Lock( ): Read PLL lock status (R3[6])        //
//  Return: 1: PLL lock                                                    //
//          0: PLL unlock                                                //
//------------------------------------------------------------------//
UINT8 R850_PLL_Lock(R850_TUNER_NUM_TYPE R850_Tuner_Num)
{
	UINT8 fg_lock = 0;

	R850_I2C_Len.RegAddr = 0x00;
	R850_I2C_Len.Len = 3;
	if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
	{
	    R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);
	}

	if( (R850_I2C_Len.Data[2] & 0x40) == 0x00 ) 		
		fg_lock = 0;		
	else
        fg_lock = 1;

	return fg_lock;
}

//------------------------------------------------------------------//
//  R850_SetIfFreq( ): Update tuner IF parameter               //
//  Input para1: desired IF output freq                               //
//  Input para2: RF freq                                                   //
//  Input para3: TV system number                                   //
//------------------------------------------------------------------//
R850_ErrCode R850_SetIfFreq(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT16 IF_KHz, UINT32 RF_KHz, R850_Standard_Type u1SystemStd)
{
	R850_Sys_Info_Type     Sys_Info_temp;
	R850_Set_Info     R850_Info;

	//Sys_Info1.IF_KHz = IF_KHz;

	R850_Info.R850_ClkOutMode = CLK_OUT_OFF;
	R850_Info.R850_LT = LT_OFF;
	R850_Info.R850_Standard = u1SystemStd;

	Sys_Info_temp = R850_Sys_Sel(u1SystemStd);
	R850_Info.RF_KHz = RF_KHz + IF_KHz - Sys_Info_temp.IF_KHz;

	R850_SetFrequency(R850_Tuner_Num, R850_Info);

	return RT_Success;
}

//------------------------------------------------------------------------------- //
//  R850_SetLpfBw( ): Set LPF coarse tune parameter: LPF_BW         //
//  cover range if LPF_BW is:                                                          //
//		0: 7.60M~11.30MHz                                                              //
//		1: 6.45M~ 9.00MHz                                                               //
//		2: 5.60M~ 7.45MHz                                                                // 
//--------------------------------------------------------------------------------//
R850_ErrCode R850_SetLpfBw(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 LPF_BW)  
{
	UINT8 u1LpfBw;

	if(LPF_BW==0)
         u1LpfBw = 0x00;     //8M
    else if(LPF_BW==1)
         u1LpfBw = 0x40;     //7M
	else
         u1LpfBw = 0x60;     //6M

	// Set LPF coarse BW, R22[6:5] => 23[6:5]
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x9F) | u1LpfBw;
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}

//------------------------------------------------------------------------------- //
//  R850_SetLpfOffset( ): Set LPF fine tune parameter: LPF_Offset     //
//  range: 0x00~0x1F    (R23[4:0])                                                    //
//  31 is narrowest; 0 is widest                                                           //
//--------------------------------------------------------------------------------//
R850_ErrCode R850_SetLpfOffset(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 LPF_Offset)  
{
	// Set LPF fine code
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE0) | (LPF_Offset);  //R23[4:0]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}

//---------------------------------------------------------------------//
//  R850_SetHpfOffset( ): Set HPF parameter: HPF_Offset     //
//  range is: 0x00~0x0F    (R24[7:4])                                    //
//  0 is narrowest; 15 is widest                                              //
//	0: 4.80M		4: 2.25M		8: 1.45M		12: 0.67M			//
//	1: 2.97M		5: 2.00M		9: 1.15M		13: 0.54M			//
//	2: 2.65M		6: 1.78M		10: 0.90M		14: 0.41M			//
//	3: 2.50M		7: 1.67M		11: 0.79M		15: 0.33M			//
//---------------------------------------------------------------------//
R850_ErrCode R850_SetHpfOffset(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 HPF_Offset)  
{

	// Set HPF corner 
	R850_I2C.RegAddr = 24;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x0F) | (HPF_Offset<<4);
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}

//------------------------------------------------------------------//
//  R850_SetIfLpf( ): Set LPF                                          //
//  Input parameter: LPF_Cor_Freq    (unit: KHz)              //
//------------------------------------------------------------------//
R850_ErrCode R850_SetIfLpf(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 LPF_Cor_Freq)
{
	UINT8     u1FilterCode;

	u1FilterCode = R850_Filt_Cal_ADC(R850_Tuner_Num, LPF_Cor_Freq, 0, 16);

	// Set LPF fine code
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xE1) | (u1FilterCode<<1);  //R23[4:1]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	// Set LPF Lsb bit
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0xFE) | (R850_Lpf_Lsb);  //R23[0]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
	    return RT_Fail;

	// Set LPF coarse BW
	R850_I2C.RegAddr = 23;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] & 0x9F) | (R850_Bandwidth<<5);  //R23[6:5]
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}



//----------------------------------------------------------------------//
//  R850_GetRfRssi( ): Get RF RSSI                                      //
//  1st parameter: input RF Freq    (KHz)                                //
//  2nd parameter: input Standard                                           //
//  3rd parameter: output signal level (dBm*1000)                    //
//  4th parameter: output RF max gain indicator (1:max gain)    //
//-----------------------------------------------------------------------//
R850_ErrCode R850_GetRfRssi(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 RF_Freq_Khz, R850_Standard_Type RT_Standard, INT32 *RfLevelDbm, UINT8 *fgRfMaxGain)
{ 	
	//UINT8 bPulseFlag;
	R850_RF_Gain_Info rf_gain_info;
	UINT16  acc_lna_gain;
	UINT16  acc_rfbuf_gain;
	UINT16  acc_mixer_gain;
	UINT16  rf_total_gain;
	UINT8   u1FreqIndex;
	INT16  u2FreqFactor=0;
	UINT8  u1LnaGainqFactorIdx;
	INT32     rf_rssi;
	INT32    fine_tune = 0;    //for find tune 
	UINT8 	rf_limit;
	UINT8	mixer_limit;
	UINT8	mixer_1315_gain = 0;
	UINT8	filter_limit;
    
#if(R850_RSSI_NORMAL_TYPE == TRUE)				
	//{50~135, 135~215, 215~265, 265~315, 315~325, 325~345, 345~950}
	INT8 R850_Start_Gain_Cal_By_Freq[7] = {10, -10, -30, -10, 20, 20, 20};
#else									
	//{50~215, 215~275, 275~295, 295~710, 710~950}
	INT8 R850_Start_Gain_Cal_By_Freq[5] = {0, -20, 0, +20, +30};
	//MS_S8 R850_Start_Gain_Cal_By_Freq[7] = {0, 0, 0, 0, 0};
#endif

	R850_I2C_Len.RegAddr = 0x00;
	R850_I2C_Len.Len = 6;

	if(R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len) != RT_Success)
	{
		R850_I2C_Read_Len(R850_Tuner_Num, &R850_I2C_Len);
	}
	//bPulseFlag = ((R850_I2C_Len.Data[1] & 0x40) >> 6);

	rf_gain_info.RF_gain1 = (R850_I2C_Len.Data[3] & 0x1F);          //lna
	rf_gain_info.RF_gain2 = (R850_I2C_Len.Data[4] & 0x0F);          //rf
	rf_gain_info.RF_gain3 = (R850_I2C_Len.Data[4] & 0xF0)>>4;       //mixer
	rf_gain_info.RF_gain4 = (R850_I2C_Len.Data[5] & 0x0F);          //filter

	
   //max gain indicator
	if((rf_gain_info.RF_gain1==31) && (rf_gain_info.RF_gain2==15) && (rf_gain_info.RF_gain3==15) && (rf_gain_info.RF_gain4==15))  
		*fgRfMaxGain = 1;
	else
		*fgRfMaxGain = 0;
	rf_limit = (((R850_Array[R850_Tuner_Num][18]&0x04)>>1) + ((R850_Array[R850_Tuner_Num][16]&0x40)>>6));
	
	if(rf_limit==0)
		rf_limit = 15;
	else if(rf_limit==1)
		rf_limit = 11;
	else if(rf_limit==2)
		rf_limit = 13;
	else
		rf_limit = 9;

	mixer_limit = (((R850_Array[R850_Tuner_Num][22]&0xC0)>>6)*2)+6;			//0=6, 1=8, 2=10, 3=12
	mixer_1315_gain = ((R850_Array[R850_Tuner_Num][25]&0x02)>>1);			//0:original, 1:ctrl by mixamp (>10)

	if( rf_gain_info.RF_gain2 > rf_limit)
		rf_gain_info.RF_gain2 = rf_limit;

	if((rf_gain_info.RF_gain3 > 12)&&(mixer_1315_gain==1))
		mixer_1315_gain = rf_gain_info.RF_gain3;		//save 0 or 13 or 14 or 15

	if( rf_gain_info.RF_gain3 > mixer_limit)
		rf_gain_info.RF_gain3 = mixer_limit;
	

	filter_limit = (R850_Array[R850_Tuner_Num][22]&0x01);
	if(filter_limit==1)
		filter_limit = 15;
	else
		filter_limit = 13;

	if( rf_gain_info.RF_gain4 > filter_limit)
		rf_gain_info.RF_gain4 = filter_limit;




#if(R850_RSSI_NORMAL_TYPE == TRUE)
		//coarse adjustment
		if(RF_Freq_Khz<135000)   //<135M
		{
			u1FreqIndex = 0;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[0];
		}
		else if((RF_Freq_Khz>=135000)&&(RF_Freq_Khz<215000))   //135~215M
		{
			u1FreqIndex = 0;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[1];
		}
		else if((RF_Freq_Khz>=215000)&&(RF_Freq_Khz<265000))   //215~265M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[2];
		}
		else if((RF_Freq_Khz>=265000)&&(RF_Freq_Khz<315000))   //265~315M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[3];
		}
		else if((RF_Freq_Khz>=315000)&&(RF_Freq_Khz<325000))   //315~325M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[4];
		}
		else if((RF_Freq_Khz>=325000)&&(RF_Freq_Khz<345000))   //325~345M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[5];
		}
		else if((RF_Freq_Khz>=345000)&&(RF_Freq_Khz<420000))   //345~420M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[6];
		}
		else if((RF_Freq_Khz>=420000)&&(RF_Freq_Khz<710000))   //420~710M
		{
			u1FreqIndex = 2;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[6];

		}
		else    // >=710
		{
			u1FreqIndex = 3;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[6];
		}
#else	//{50~215, 215~425, 425~710, 710~1000}				// u1FreqIndex
		////{50~215, 215~275, 275~295, 295~710, 695~950}	// u2FreqFactor
		//coarse adjustment
		if(RF_Freq_Khz<215000)   //<215M
		{
			u1FreqIndex = 0;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[0];
		}
		else if((RF_Freq_Khz>=215000)&&(RF_Freq_Khz<275000))   //215~275M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[1];
		}
		else if((RF_Freq_Khz>=275000)&&(RF_Freq_Khz<295000))   //275~295M
		{
			u1FreqIndex = 1;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[2];
		}
		else if((RF_Freq_Khz>=295000)&&(RF_Freq_Khz<420000))   //295M~425M
		{
			u1FreqIndex = 1;
			u2FreqFactor = 30;
		}
		else if((RF_Freq_Khz>=420000)&&(RF_Freq_Khz<710000))   //425M~710M
		{
			u1FreqIndex = 2;
			if((RF_Freq_Khz>=470000)&&(RF_Freq_Khz<525000) || (RF_Freq_Khz>=575000)&&(RF_Freq_Khz<625000))
				u2FreqFactor = 0;
			else if(RF_Freq_Khz>=680000)
				u2FreqFactor = 10;
			else
				u2FreqFactor = R850_Start_Gain_Cal_By_Freq[3];
		}
		else    // >=710
		{
			u1FreqIndex = 3;
			u2FreqFactor = R850_Start_Gain_Cal_By_Freq[4];
		}


#endif

	//LNA Gain
	acc_lna_gain = R850_Lna_Acc_Gain[u1FreqIndex][rf_gain_info.RF_gain1];



//fine adjustment
	//Cal LNA Gain	by Freq 

//Method 2 : All frequencies are finely adjusted..

						
	if(rf_gain_info.RF_gain1 >= 10)
	{
		u1LnaGainqFactorIdx = (UINT8) ((RF_Freq_Khz-50000) / 10000);

		if( ((RF_Freq_Khz-50000)  - (u1LnaGainqFactorIdx * 10000))>=5000)
			u1LnaGainqFactorIdx +=1;
		acc_lna_gain += (UINT16)(Lna_Acc_Gain_offset[u1LnaGainqFactorIdx]);

	}

	//RF buf
	acc_rfbuf_gain = R850_Rf_Acc_Gain[rf_gain_info.RF_gain2];
	if(RF_Freq_Khz<=300000)
		acc_rfbuf_gain += (rf_gain_info.RF_gain2 * 1);
	else if (RF_Freq_Khz>=600000)
		acc_rfbuf_gain -= (rf_gain_info.RF_gain2 * 1);

	//Mixer 
	acc_mixer_gain = R850_Mixer_Acc_Gain [rf_gain_info.RF_gain3]  ;
	
	if((mixer_1315_gain!=0) && (mixer_1315_gain!=1))	//Gain 13 or 14 or 15
		acc_mixer_gain = acc_mixer_gain + (R850_Mixer_Acc_Gain[mixer_1315_gain] - R850_Mixer_Acc_Gain[12]);



	//Add Rf Buf and Mixer Gain
	rf_total_gain = acc_lna_gain + acc_rfbuf_gain + acc_mixer_gain + rf_gain_info.RF_gain4*15;

	rf_rssi = fine_tune - (INT32) (rf_total_gain - u2FreqFactor);

	*RfLevelDbm = rf_rssi*100;
    return RT_Success;
}

//-----------------------------------------------------------------------//
//  R850_GetIfRssi( ): Get IF VGA GAIN                                   //
//  1st parameter: return IF VGA Gain     (dB*100)                       //
//-----------------------------------------------------------------------//
R850_ErrCode R850_GetIfRssi(R850_TUNER_NUM_TYPE R850_Tuner_Num, INT32 *VgaGain)
{
	UINT8   adc_read;
    I2C_TYPE          Dlg_I2C;
	I2C_LEN_TYPE Dlg_I2C_Len;
//Optimize value
	UINT16   vga_table[64] = {                        //*100
		0, 0, 20, 20, 30, 50, 60, 80, 110, 130, 130, 160,   //0~11
		200, 240, 280, 330, 380, 410, 430, 480, 530, 590,   //12~21
		640, 690, 730, 760, 780, 810, 840, 890, 930, 950,   //22~31
		980, 1010, 1010, 1030, 1060, 1100, 1120, 1140, 1170, 1180,   //32~41
		1190, 1210, 1220, 1260, 1270, 1300, 1320, 1320, 1340, 1340,   //42~51
		1360, 1390, 1400, 1420, 1440, 1450, 1460, 1480, 1490, 1510,   //52~61
		1550, 1600            //62~63
	};

	//ADC sel : vagc, R22[3:2]=2
	Dlg_I2C.RegAddr = 22;
	R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] & 0xF3) | 0x08;
	Dlg_I2C.Data = R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//IF_AGC read, R18[5]=1
	Dlg_I2C.RegAddr = 18;
	R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] = R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] | 0x20;
	Dlg_I2C.Data = R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//ADC power on, R11[1]=0
	Dlg_I2C.RegAddr = 11;
	R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] = R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr] & 0xFD;
	Dlg_I2C.Data = R850_Array[R850_Tuner_Num][Dlg_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//read adc value
	Dlg_I2C_Len.RegAddr = 0x00;
	Dlg_I2C_Len.Len = 2;
	if(R850_I2C_Read_Len(R850_Tuner_Num, &Dlg_I2C_Len) != RT_Success) // read data length
	{
		R850_I2C_Read_Len(R850_Tuner_Num, &Dlg_I2C_Len);
	}
	adc_read = (Dlg_I2C_Len.Data[1] & 0x3F);

	*VgaGain = vga_table[adc_read];
	return RT_Success;
}

//----------------------------------------------------------------------//
//  R850_GetRfRssi( ): Get RF RSSI                                      //
//  1st parameter: input RF Freq    (KHz)                                //
//  2nd parameter: input Standard                                           //
//  3rd parameter: return signal level indicator (dBm)               //
//-----------------------------------------------------------------------//
R850_ErrCode R850_GetTotalRssi(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT32 RF_Freq_Khz, R850_Standard_Type RT_Standard, INT32 *RssiDbm)
{
	INT32   rf_rssi;
	INT32   if_rssi;
	INT32   rem, total_rssi;
	INT32   ssi_offset = 0;   //need to fine tune by platform
	INT32   total_rssi_dbm;
	UINT8  rf_max_gain_flag;

	R850_GetRfRssi(R850_Tuner_Num, RF_Freq_Khz, RT_Standard, &rf_rssi, &rf_max_gain_flag);

	R850_GetIfRssi(R850_Tuner_Num, &if_rssi);  //vga gain        

    total_rssi = rf_rssi - (if_rssi*10);
	rem = total_rssi - (total_rssi/1000)*1000; //for rounding
	if((rem>-500) && (rem<500))
		total_rssi_dbm = (total_rssi/1000);
	else if(rem<=-500)
		total_rssi_dbm = (total_rssi/1000)-1;
	else
		total_rssi_dbm = (total_rssi/1000)+1;

	//for different platform, need to fine tune offset value
	*RssiDbm = total_rssi_dbm + ssi_offset;   

	return RT_Success;
}






R850_ErrCode R850_SetXtalCap(R850_TUNER_NUM_TYPE R850_Tuner_Num, UINT8 u8XtalCap)
{
	UINT8 XtalCap;
	UINT8 Capx;
	UINT8 Capx_3_0, Capxx;

	if(u8XtalCap>31)
	{
		XtalCap = 1;  //10
		Capx = u8XtalCap-10;
	}
	else
	{
		XtalCap = 0; //0
        Capx = u8XtalCap;
	}

	Capxx = Capx & 0x01;
    Capx_3_0 = Capx >> 1;
		
	// Set Xtal Cap  R33[6:3], R34[3]     XtalCap => R33[7]
	R850_I2C.RegAddr = 33;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr ] & 0x07) | (Capx_3_0 << 3) | ( XtalCap << 7);  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;
	R850_I2C.RegAddr = 34;
	R850_Array[R850_Tuner_Num][R850_I2C.RegAddr] = (R850_Array[R850_Tuner_Num][R850_I2C.RegAddr ] & 0xF7) | (Capxx << 3);  
	R850_I2C.Data = R850_Array[R850_Tuner_Num][R850_I2C.RegAddr];
	if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}

R850_ErrCode R850_SetHpfNotch(R850_TUNER_NUM_TYPE R850_Tuner_Num, R850_HpfNotch_Type R850_HpfNotch)
{

	if(R850_HpfNotch==HPF_NOTCH_HIGH)
	{
		R850_Array[R850_Tuner_Num][23] = R850_Array[R850_Tuner_Num][23] & 0x7F;  //R23[7]=0
	}
	else //gain attenuation
	{		
		R850_Array[R850_Tuner_Num][23] = R850_Array[R850_Tuner_Num][23] | 0x80;
	}

     R850_I2C.RegAddr = 23;
	 R850_I2C.Data = R850_Array[R850_Tuner_Num][23];
     if(R850_I2C_Write(R850_Tuner_Num, &R850_I2C) != RT_Success)
	       return RT_Fail;

    return RT_Success;
}

HI_S32 r850_init_tuner(HI_U32 u32TunerPort)
{
    R850_Set_Info R850_Info_Msg;

    if (HI_UNF_DEMOD_DEV_TYPE_J83B == g_stTunerOps[u32TunerPort].enDemodDevType)
    {   
        R850_Info_Msg.R850_Standard=R850_J83B;
    }
    else
    {    
         R850_Info_Msg.R850_Standard= R850_DVB_C_8M;
        
    } 

    R850_Initial_flag = FALSE;
    R850_Initial_done_flag[u32TunerPort]=FALSE;
    R850_IMR_done_flag[u32TunerPort]=FALSE;

    if(R850_Init(u32TunerPort,R850_Info_Msg.R850_Standard) != RT_Success)
    {
        return HI_FAILURE;
    }
	
    R850_Initial_flag = TRUE;
		
    return HI_SUCCESS;
}

HI_S32 r850_set_tuner(HI_U32 u32TunerPort, HI_U8  enI2cChannel, HI_U32 puRF)
{
    R850_Set_Info R850_Info_Msg;
    R850_RF_KHz = puRF;
   
    if (HI_UNF_DEMOD_DEV_TYPE_J83B == g_stTunerOps[u32TunerPort].enDemodDevType)
    {   
        R850_Info_Msg.R850_Standard=R850_J83B;
    }
    else
    {    
         R850_Info_Msg.R850_Standard= R850_DVB_C_8M;
    } 
    R850_Info_Msg.R850_LT= LT_ON;
    R850_Info_Msg.R850_ClkOutMode = CLK_OUT_ON;
    R850_Info_Msg.RF_KHz = puRF; // unit: kHz	
    
    if(R850_SetPllData(u32TunerPort,R850_Info_Msg) != RT_Success)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID r850_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength)
{
    R850_ErrCode err = RT_Success;
    INT32 RssiDbm  ;
    R850_Set_Info R850_Info_Msg;
    //UINT32 RfLevel  ;
    //UINT8 fgRfMaxGain ;

    if (HI_UNF_DEMOD_DEV_TYPE_J83B == g_stTunerOps[u32TunerPort].enDemodDevType)
    {   
        R850_Info_Msg.R850_Standard=R850_J83B;
    }
    else
    {    
         R850_Info_Msg.R850_Standard= R850_DVB_C_8M;
    } 

    R850_Info_Msg.RF_KHz = R850_RF_KHz;
    
    err = R850_GetTotalRssi(u32TunerPort,R850_Info_Msg.RF_KHz, R850_Info_Msg.R850_Standard, &RssiDbm);
    
    if(RT_Success != err)
    {
	    HI_ERR_TUNER("R850_GetTotalRssi\n");
	    return;
    }
    
	if( ((R850_RF_KHz >= 100000 ) && (R850_RF_KHz < 171000 ))|| ( R850_RF_KHz == 203000 ))
	{
        RssiDbm = (HI_U32)(RssiDbm + 117);	 
	}
	else if( (R850_RF_KHz >= 187000 ) && (R850_RF_KHz < 203000 ) )
	{
        RssiDbm = (HI_U32)(RssiDbm + 115);	 
	}
	else if( (R850_RF_KHz >= 211000 ) && (R850_RF_KHz < 283000 ) )
	{
        RssiDbm = (HI_U32)(RssiDbm + 113);	 
	}
	else if( (R850_RF_KHz == 283000) || ((R850_RF_KHz >= 786000 ) && (R850_RF_KHz <= 858000 )) )
	{
        RssiDbm = (HI_U32)(RssiDbm + 116);	 
	}
	else if( (R850_RF_KHz >= 339000 ) && (R850_RF_KHz < 714000 ) )
	{
        RssiDbm = (HI_U32)(RssiDbm + 120);	 
	}
	else
	{
        RssiDbm = (HI_U32)(RssiDbm + 118);	 
	}

    pu32SignalStrength[1] = RssiDbm;	 

    return;
}

HI_VOID r850_tuner_resume (HI_U32 u32TunerPort)
{
    r850_init_tuner(u32TunerPort);
    return;
}

HI_S32 r850_tuner_standby(HI_U32 u32TunerPort, HI_U32 u32Status)
{
    R850_ErrCode err = RT_Success;
    R850_LoopThrough_Type R850_LoopSwitch = LT_OFF;
		
   err = R850_Standby(u32TunerPort,R850_LoopSwitch);
    if(RT_Success != err)
    {
        HI_ERR_TUNER("R850_Standby\n");
		return HI_FAILURE;
    }
    return HI_SUCCESS;
}

