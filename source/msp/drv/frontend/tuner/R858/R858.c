//-----------------------------------------------------//
//
// Filename: R858.c
//
// This file is R858 tuner driver
// Copyright 2015 by Rafaelmicro., Inc.
// Author: Vincent Chien
//-----------------------------------------------------//

/*
 C H A N G E   R E C O R D
  Date        Author           Version      Description
--------   --------------    --------   ----------------------
06/06/2016     Vincent 	        v1.0
08/03/2016     Vincent          v1.1        modify agc speed
08/05/2016     Vincent          v1.2        share_xtal
08/10/2016     Vincent          v1.3        add LT choose
06/01/2017     Vincent          v1.4        add DVBT/T2 and J.83B
10/01/2017     Vincent          v1.5        add ATSC
25/01/2017     Vincent          v1.6        add xtal choose

*/

#include "R858.h"
#include "R858_I2C_Sys.h"    // "I2C_Sys" is only for SW porting reference.


#include <linux/delay.h>

#include "hi_drv_i2c.h"
#include "hi_debug.h"

#include "drv_tuner_ext.h"
#include "drv_demod.h"


//Standby mode
//1. R858_SBY_IND: individual down, LNA on
//2. R858_SBY_ALL: all down
UINT8   R858_Standby_Mode = R858_SBY_IND;
UINT8   R858_Mixer_Mode = R858_IMR_REV;

//User mode
//1. R858_SINGLE: one R858
//2. R858_DUAL: two R858
UINT8   R858_User_Mode = R858_DUAL;

R858_ExtTunerNum_Type R858_ExtTunerNum = R858_NUM1;
R858_IntTunerNum_Type  R858_IntTunerNum = R858_TUNER1;



R858_IMR_CAL_TYPE	R858_imr_type = IMR_AUTO;  //IMR_AUTO, IMR_MANUAL

//UINT8  Chip_type_flag = 0;  //0:RT858_A ; 1;RT858_B

//-----------------------------
/*
	R858_NO_SHARE_XTAL = 0,           //single R858
	R858_MASTER_TO_SLAVE_XTAL,        //Dual   R858 
    R858_SLAVE_XTAL_IN,               //Only R858_1 is slave
	R858_SLAVE_XTAL_OFF,			  //Both R858_1 and R8s8_2 are slave
*/
//------------------------------


//UINT8   R858_SHARE_XTAL = R858_MASTER_TO_SLAVE_XTAL;
#define   R858_SHARE_XTAL  (1)
//#define R858_SHARE_XTAL 1
UINT8   R858_XTAL_CAP = 25;  //(range 0~31)


//#define  R858_SHARE_XTAL   FALSE
#define  LNA_VTH_PARAMETER 4
#define  LNA_VTL_PARAMETER 2

#define  RF_VTH_PARAMETER 4
#define  RF_VTL_PARAMETER 2
#define  MIX_FILT_VTH_PARAMETER 4
#define  MIX_FILT_VTL_PARAMETER 2
#define  ADC_MULTI_READ   1
#define  FILTER_GAIN_DELAY  5
#define  FILTER_CODE_DELAY  5
#define  XTAL_CHK_DELAY    20
#define  PLL_LOCK_DELAY    10
static UINT32 ADC_READ_DELAY = 2;
static UINT8  ADC_READ_COUNT = 1;
UINT16  STBY_DELAY_MS = 300;
UINT16  WAKEUP_DELAY_MS = 300;
UINT16  VTHVTL_DELAY_MS = 300;

#if 0
void usleep(DWORD waitTime){
	LARGE_INTEGER perfCnt, start, now;

	QueryPerformanceFrequency(&perfCnt);
	QueryPerformanceCounter(&start);
	do {
		QueryPerformanceCounter((LARGE_INTEGER*) &now);
	} while ((now.QuadPart - start.QuadPart) / float(perfCnt.QuadPart) * 1000 < waitTime);
}
#endif
//#define R858_Delay_MS(R858_ExtTunerNum_Type, x_ms)	usleep(x_ms)


UINT8 R858_iniArray[2][R858_REG_NUM] = {     //Tuner1/2
		{	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     //Reg0~7, read only
		//  0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  
			0x10, 0x70, 0xA7, 0x01, 0x06, 0x12, 0x30, 0x89, 0x20, 0x20,     //Reg R8~47(both) & R47~R55(tuner1)
		//  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F  0x10  0x11
			0x7B, 0x82, 0x30, 0x0A, 0x55, 0x15, 0x83, 0x46, 0xA1, 0x08,    
		//  0x12  0x13  0x14  0x15  0x16  0x17  0x18  0x19  0x1A  0x1B 
			0x00, 0xE1, 0x5A, 0x38, 0xDB, 0x87, 0x35, 0x49, 0x39, 0x49,
		//  0x1C  0x1D  0x1E  0x1F  0x20  0x21  0x22  0x23  0x24  0x25
			0x45, 0x00, 0xCD, 0x2A, 0x0B, 0xE8, 0xD8, 0x00, 0xD2, 0x80,
		//  0x26  0x27  0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
			0x22, 0x02, 0x00, 0x57, 0xAD, 0xF6, 0x77, 0x1A},
		//  0x30  0x31 	0x32  0x33  0x34  0x35  0x36  0x37 


		{	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     //Reg0~7, read only
		//  0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  
			0x10, 0x70, 0xA7, 0x01, 0x06, 0x12, 0x30, 0x89, 0x20, 0x20,     //Reg R8~47(both) & R47~R55(tuner1)
		//  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F  0x10  0x11
			0x7B, 0x82, 0x30, 0x11, 0xAA, 0xEA, 0x83, 0x46, 0xA1, 0x08,    
		//  0x12  0x13  0x14  0x15  0x16  0x17  0x18  0x19  0x1A  0x1B  
			0x00, 0xE1, 0x5A, 0x38, 0xD8, 0x87, 0x35, 0x49, 0x39, 0x49,
		//  0x1C  0x1D  0x1E  0x1F  0x20  0x21  0x22  0x23  0x24  0x25
			0x45, 0x00, 0xCD, 0x2A, 0x0B, 0xE8, 0xD8, 0x00, 0xD2, 0x80,
		//  0x26  0x27  0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
			0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08}
		//  0x30  0x31 	0x32  0x33  0x34  0x35  0x36  0x37 
};
	
//UINT8  R858_iniArray2[6]={0x17, 0x13, 0x01, 0x07, 0x01, 0x3F};  //Reg R42~R47(tuner2)

UINT8   R858_ADDRESS[R858_MAX_NUM][2] = {{0x14, 0x34},{0x14, 0x34}};//{{0xD4, 0xF4},{0x14, 0x34}};   
UINT32  R858_Xtal = 24000;             //
UINT8   R858_XtalDiv = XTAL_DIV1_2;
UINT8   R858_Fil_Cal_Gap = 8;
static UINT8   Divider_Manual = 0;					//*not release
UINT32  R858_IF_HIGH = 8500; 
UINT32  R858_IF_GOLOBAL = 6000;
UINT8   R858_Xtal_Pwr = R858_XTAL_HIGHEST;
UINT8   R858_Xtal_Pwr_tmp = R858_XTAL_HIGHEST;

//LPF Cal Array 72MHz
UINT8 R858_LPF_CAL_Array[2][R858_REG_NUM] = {   //tuner1/2
	 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only
	   0x12, 0x70, 0xB0, 0x01, 0x06, 0x03, 0x02, 0x88,
	   0x20, 0x00, 0x78, 0x80, 0x00, 0x10, 0x55, 0x55,
	   0x80, 0x55, 0xC7, 0x08, 0x00, 0xB9, 0x5A, 0xF8,
	   0xDA, 0x87, 0x3C, 0x19, 0x39, 0x39, 0x01, 0x06,
	   0xAD, 0xF0, 0x0F, 0xE0, 0xD8, 0x07, 0xD2, 0x00, 
	   0xE0, 0xE1, 0x11, 0x17, 0xA1, 0xD6, 0x73, 0x18},
	 {
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only
	   0x12, 0x70, 0xB4, 0x01, 0x06, 0x03, 0x02, 0x88,
	   0x20, 0x00, 0x78, 0x80, 0x00, 0x10, 0x55, 0x55,
	   0x80, 0x55, 0xC7, 0x08, 0x00, 0xB9, 0x5A, 0xF8,
	   0xDA, 0x87, 0x3C, 0x19, 0x39, 0x39, 0x01, 0x06,
	   0xAD, 0xF0, 0x0F, 0xE0, 0xD8, 0x07, 0xD2, 0x00, 
	   0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

//IMR Cal array 
UINT8 R858_IMR_CAL_Array[2][R858_REG_NUM] = {   //tuner1/2
	{  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x12, 0x00, 0xB0, 0x01, 0x06, 0x11, 0x36, 0x88,   //R14[1]:RingtoBuf on
	   0xF0, 0x00, 0x0F, 0x00, 0x4A, 0x0D, 0x55, 0xD5,
	   0x00, 0x53, 0xA2, 0x08, 0x00, 0xB9, 0x38, 0xF8,
	   0x9C, 0x88, 0x4C, 0x68, 0x38, 0xF8, 0x01, 0x06,					
	   0xF6, 0x50, 0x00, 0x40, 0xFE, 0x5D, 0xD0, 0x18,
	   0x20, 0x40, 0xD1, 0x00, 0x90, 0x25, 0x00, 0x08},
	{
	   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x12, 0xF0, 0xB4, 0x01, 0x06, 0x15, 0x3A, 0x88,   //R14[1]:RingtoBuf on
	   0xF3, 0xD0, 0x8B, 0x81, 0x48, 0x0D, 0x55, 0xD5,
	   0x00, 0x53, 0xA2, 0x08, 0x00, 0x00, 0x38, 0xF8,
	   0x9C, 0x88, 0x4C, 0x68, 0x38, 0xF8, 0x01, 0x06,	
	   0xF6, 0x50, 0x00, 0x40, 0xC0, 0x45, 0xD6, 0x18, 
	   0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};  

//----------------------------------------------------------//
//                   Internal Parameters                          //
//----------------------------------------------------------//
UINT8 R858_Array[R858_MAX_NUM][2][56];
R858_SectType R858_IMR_Data[R858_MAX_NUM][2][R842_IMR_POINT_NUM] = {{{{0}}}};//{{0,0,0,0}};
                                               
I2C_TYPE  R858_I2C;
I2C_LEN_TYPE R858_I2C_Len;

UINT8  R858_IMR_point_num;
UINT8  R858_Initial_done_flag[R858_MAX_NUM][2] = {{FALSE, FALSE},{FALSE, FALSE}};
UINT8  R858_IMR_done_flag[R858_MAX_NUM][2] = {{FALSE, FALSE},{FALSE, FALSE}};
UINT8  R858_Bandwidth[R858_MAX_NUM][2] = {{0,0},{0,0}};   //8M
UINT8  R858_Lpf_Lsb[R858_MAX_NUM][2] = {{0,0},{0,0}}; 


UINT8  R858_Fil_Cal_flag[R858_MAX_NUM][2][R858_STD_SIZE]={{{0}}};//{0};
static UINT8 R858_Fil_Cal_BW[R858_MAX_NUM][2][R858_STD_SIZE];
static UINT8 R858_Fil_Cal_code[R858_MAX_NUM][2][R858_STD_SIZE];
static UINT8 R858_Fil_Cal_LpfLsb[R858_MAX_NUM][2][R858_STD_SIZE]; 

static R858_Standard_Type R858_pre_standard[R858_MAX_NUM][2] = {{R858_STD_SIZE, R858_STD_SIZE},{R858_STD_SIZE, R858_STD_SIZE}};
static UINT8 R858_SBY[R858_MAX_NUM][2][R858_REG_NUM];
static UINT8 R858_SBY2[R858_MAX_NUM][6];           //tuner 1, R42~R47
static UINT8 R858_SBY_flag[R858_MAX_NUM][2]={{0,0},{0,0}}; 

static UINT8 R858_OTH_VTH_Width_flag[R858_MAX_NUM][2]={{0,0},{0,0}}; 
static UINT8 R858_OTH_VTL_Width_flag[R858_MAX_NUM][2]={{0,0},{0,0}}; 

static UINT8 R858_LNA_VTH_Width_flag[R858_MAX_NUM]={0,0}; 
static UINT8 R858_LNA_VTL_Width_flag[R858_MAX_NUM]={0,0}; 
static UINT8 R858_LNA_VTHVTL_Change_flag[R858_MAX_NUM]={0,0}; 

static UINT8 R858_OTH_VTHVTL_Change_flag[R858_MAX_NUM][2]={{0,0},{0,0}}; 
static UINT8 LNA_VTH_ORIGINAL[R858_MAX_NUM];
static UINT8 LNA_VTL_ORIGINAL[R858_MAX_NUM];
static UINT8 LNA_VTH[R858_MAX_NUM];
static UINT8 LNA_VTL[R858_MAX_NUM];
static UINT8 Filter_VTHL_ORIGINAL[R858_MAX_NUM][2];
static UINT8 Mixer_VTHL_ORIGINAL[R858_MAX_NUM][2];
static UINT8 RfBuffer_VTHL_ORIGINAL[R858_MAX_NUM][2];

//----------------------------------------------------------//
//                   Internal static struct                         //
//----------------------------------------------------------//
static R858_SysFreq_Info_Type  SysFreq_Info1;
static R858_Sys_Info_Type    Sys_Info1;
static R858_Freq_Info_Type   Freq_Info1;
//----------------------------------------------------------//
//                   Internal Functions                            //
//----------------------------------------------------------//
R858_ErrCode R858_InitReg(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);
R858_ErrCode R858_InitUserMode(R858_Set_Info R858_INFO);
R858_ErrCode R858_Cal_Prepare(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 u1CalFlag);
R858_ErrCode R858_Xtal_Check(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);  //TUNER1

R858_ErrCode R858_IMR(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 IMR_MEM, UINT8 IM_Flag,UINT8 Rev_Mode);
R858_ErrCode R858_IMR_Process(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);

R858_ErrCode R858_PLL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 LO_Freq, R858_Standard_Type R858_Standard);
R858_ErrCode R858_MUX(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 LO_KHz, UINT32 RF_KHz, R858_Standard_Type R858_Standard);
R858_ErrCode R858_IQ(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont);
R858_ErrCode R858_IQ_Tree(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R858_SectType* CompareTree);
R858_ErrCode R858_IQ_Tree5(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R858_SectType* CompareTree);
R858_ErrCode R858_CompreCor(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* CorArry);
R858_ErrCode R858_CompreStep(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* StepArry, UINT8 Pace);
R858_ErrCode R858_Muti_Read(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8* IMR_Result_Data);
R858_ErrCode R858_Section(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* SectionArry);
R858_ErrCode R858_F_IMR(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont);
R858_ErrCode R858_IMR_Cross(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont, UINT8* X_Direct);
R858_ErrCode R858_IMR_Iqcap(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Point);   
R858_ErrCode R858_SetStandard(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Standard_Type RT_Standard);
R858_ErrCode R858_SetFrequency(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Set_Info R858_INFO);
R858_ErrCode R858_SetRF_MIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 Shift_Type, UINT8 Shift_Num, UINT8 Shift_Num1);
R858_ErrCode R858_SetMIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 Shift_Type, UINT8 Shift_Num, UINT8 Shift_Num1);
R858_ErrCode R858_Orignial_RF_MIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum1);

R858_Sys_Info_Type R858_Sys_Sel(R858_Standard_Type R858_Standard);
R858_Freq_Info_Type R858_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R858_Standard_Type R858_Standard);
R858_SysFreq_Info_Type R858_SysFreq_Sel(R858_Standard_Type R858_Standard,UINT32 RF_freq);

UINT8 R858_Filt_Cal_ADC(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 IF_Freq, UINT8 R858_BW, UINT8 FilCal_Gap);

static UINT16 R858_Lna_Acc_Gain[4][32] = 
{
	{0, 10,  19, 29, 40, 53, 66, 78, 94,  110, 129, 148, 160, 173, 186, 200, 214, 226, 241, 249, 258, 258, 258, 258, 258, 266, 276, 291, 307, 324, 319, 337},
	{0, 9,  17, 26, 36, 47, 59, 71, 84,  99,  115, 131, 141, 152, 163, 175, 187, 196, 208, 213, 219, 219, 219, 219, 219, 234, 249, 267, 284, 301, 287, 303},
	{0, 8,  16, 25, 34, 45, 57, 68, 81,  95, 111, 126, 136, 146, 155, 164, 171, 176, 183, 189, 193, 193, 193, 193, 193, 207, 220, 234, 244, 252, 272, 286},
	{0, 9,  17, 26, 36, 47, 59, 72, 86,  102, 119, 138, 148, 157, 165, 172, 178, 183, 193, 199, 204, 204, 204, 204, 204, 218, 231, 245, 255, 261, 288, 304},
};

static INT8 Lna_Acc_Gain_offset[86]={19,  16,  10,   8,  8, 11,  6,   8,  0, -4,	//45~145
									 -4,  -6,  -5,  -5, -6, -9,-12,  12, 10, 10,	//145~245
									  9,   8,   9,   5,  5,  0,  1,  -1, -3, -4,	//245~345
									 -7,  -9, -10, -10,-10,-11,-13, -13,  4,  3,	//345~445
									  3,   5,   6,   5,  3,  0, -2,  -2, -3, -1,	//445~545
									  0,   1,   1,  -2, -3, -4, -3,  -2,  0,  0,	//545~645
									  1,   3,   3,   3,  5,  3, -9,  -9, -4, -5,	//645~745
									  2,   1,   0,   0, -3, -4, -4,  -1,  5,  5,	//745~845
									  5,   4,   4,   1,  1,  1};						//845~905

static UINT16 R858_Rf_Acc_Gain[16] = 
{
   0, 15, 30, 44, 55, 55, 55, 55, 55, 69,			//0~9
  82, 95, 108, 121, 131, 140						//10~15
};           

static UINT16 R858_Mixer_Acc_Gain[13] = 
{
   0, 0, 0, 0, 11, 23, 35, 47, 59, 72,			//0~9
   82, 83, 83,					//10~12
};        

R858_Sys_Info_Type R858_Sys_Sel(R858_Standard_Type R858_Standard)
{
//below not release
/*
***********************************  Filter  **********************************************
1.HPF_COR 	R18[6:3]	
[0~15 ; input: "0~15"]

2.FILT_EXT_ENA R19[6]
[off(0), on(1)]

3.BW(v7M/v6M) R17[5:4]
[8M(0), not use(1), 7M(2), 6M(3)]

4..HPF_NOTCH R18[7]
[notch high(0), notch low(1)]


***********************************  Clock  **********************************************
1.AGC_CLK	R38[5:4]
[1kHz(0), 512Hz(1), 4kHz(2), 64Hz(3)]

*/
	R858_Sys_Info_Type R858_Sys_Info;

	switch (R858_Standard)
	{
	case R858_DVB_T_6M: 
	case R858_DVB_T2_6M:
		R858_Sys_Info.IF_KHz=4570;               //IF
		R858_Sys_Info.BW=1;                      //BW(v7M/v6M)=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7450;          //CAL IF
		R858_Sys_Info.HPF_COR=5;	             //R18[6:3] [0~15 ; input: "0~15"]v
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]v
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T_7M:  
	case R858_DVB_T2_7M:  
		R858_Sys_Info.IF_KHz=4570;               //IF
		R858_Sys_Info.BW=1;                      //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7750;          //CAL IF
		R858_Sys_Info.HPF_COR=8;	             //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		    //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T_8M: 
	case R858_DVB_T2_8M: 
		R858_Sys_Info.IF_KHz=4570;                //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8500;           //CAL IF
		R858_Sys_Info.HPF_COR=12;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T2_1_7M: 
		R858_Sys_Info.IF_KHz=1900;
		R858_Sys_Info.BW=1;                       //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7800;           //CAL IF
		R858_Sys_Info.HPF_COR=8;	             //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_T2_10M: 
		R858_Sys_Info.IF_KHz=5600;
		R858_Sys_Info.BW=0;                      //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=10800;         //CAL IF
		R858_Sys_Info.HPF_COR=12;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_8M:   
		R858_Sys_Info.IF_KHz=5070;
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=9000;           //CAL IF
		R858_Sys_Info.HPF_COR=10;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_6M:  
		R858_Sys_Info.IF_KHz=5070;
		R858_Sys_Info.BW=1;                      //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8025;          //CAL IF   
		R858_Sys_Info.HPF_COR=3;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			//R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
		case R858_J83B_IF_5370:  
		R858_Sys_Info.IF_KHz=5370;
		R858_Sys_Info.BW=0;                       //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8320;          //CAL IF  
		R858_Sys_Info.HPF_COR=4;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
		case R858_J83B_IF_5070:  
		R858_Sys_Info.IF_KHz=5070;
		R858_Sys_Info.BW=0;                       //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8020;          //CAL IF  
		R858_Sys_Info.HPF_COR=5;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_J83B_IF_5M:  
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=0;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7800;          //CAL IF  
		R858_Sys_Info.HPF_COR=3;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_J83B_IF_5500:  
		R858_Sys_Info.IF_KHz=5500;
		R858_Sys_Info.BW=0;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8300;          //CAL IF  
		R858_Sys_Info.HPF_COR=2;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
	
	case R858_J83B_IF_4300:  
		R858_Sys_Info.IF_KHz=4300;
		R858_Sys_Info.BW=0;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7050;          //CAL IF  

		R858_Sys_Info.HPF_COR=9;                //R18[6:3] [0~15 ; input: "0~15"]

		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_J83B_IF_4000:  
		R858_Sys_Info.IF_KHz=4000;
		R858_Sys_Info.BW=0;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=6850;          //CAL IF  
		R858_Sys_Info.HPF_COR=11;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
	case R858_ISDB_T_4063: 
		R858_Sys_Info.IF_KHz=4063;
		R858_Sys_Info.BW=1;                      //BW=7M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7000;          //CAL IF  //7200
		//if(R858_Chip == R858_MP)
			R858_Sys_Info.HPF_COR=8;             //R18[6:3] [0~15 ; input: "0~15"]
		//else
		//	R858_Sys_Info.HPF_COR=11;            //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_ISDB_T_4570:
		R858_Sys_Info.IF_KHz=4570;                    //IF
		R858_Sys_Info.BW=1;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7250;          //CAL IF
		//if(R858_Chip == R858_MP)
			R858_Sys_Info.HPF_COR=5;            //R18[6:3] [0~15 ; input: "0~15"]
		//else
		//	R858_Sys_Info.HPF_COR=8;            //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DTMB_8M_4570: 
		R858_Sys_Info.IF_KHz=4570;
		R858_Sys_Info.BW=0;                                //BW=8M
		R858_Sys_Info.FILT_CAL_IF=8500;           //CAL IF  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.HPF_COR=12;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DTMB_6M_4500:
		R858_Sys_Info.IF_KHz=4500;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7000;           //CAL IF    
		R858_Sys_Info.HPF_COR=5;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		    //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_ATSC:  
		R858_Sys_Info.IF_KHz=5070;
		R858_Sys_Info.BW=1;                      //BW=7M  R17[5:4]  [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7900;          //CAL IF   
		R858_Sys_Info.HPF_COR=4;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

    case R858_DVB_T_6M_IF_5M: 
	case R858_DVB_T2_6M_IF_5M: 
		R858_Sys_Info.IF_KHz=5000;                    //IF
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7800;          //CAL IF
		R858_Sys_Info.HPF_COR=4;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		    //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T_7M_IF_5M:  
	case R858_DVB_T2_7M_IF_5M:  
		R858_Sys_Info.IF_KHz=5000;                     //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8450;           //CAL IF
		R858_Sys_Info.HPF_COR=9;                  //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;
	case R858_DVB_T_7M_IF_5500:  
	case R858_DVB_T2_7M_IF_5500:  
		R858_Sys_Info.IF_KHz=5500;                     //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8950;           //CAL IF
		R858_Sys_Info.HPF_COR=6;                  //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T_8M_IF_5M: 
	case R858_DVB_T2_8M_IF_5M:
		R858_Sys_Info.IF_KHz=5000;                     //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8700;           //CAL IF
		R858_Sys_Info.HPF_COR=10;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T_8M_IF_5500: 
	case R858_DVB_T2_8M_IF_5500:
		R858_Sys_Info.IF_KHz=5500;                     //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=9200;           //CAL IF
		R858_Sys_Info.HPF_COR=8;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DVB_T2_1_7M_IF_5M: 
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=2;                       //BW=6M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=5900;           //CAL IF
		R858_Sys_Info.HPF_COR=1;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_8M_IF_5500:  
		R858_Sys_Info.IF_KHz=5500;
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=9750;           //CAL IF 
		R858_Sys_Info.HPF_COR=7;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_8M_IF_5M:  
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=9250;           //CAL IF 
		R858_Sys_Info.HPF_COR=10;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_6M_IF_5500:  
		R858_Sys_Info.IF_KHz=5500;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8600;          //CAL IF   
		R858_Sys_Info.HPF_COR=1;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DVB_C_6M_IF_5M:  
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8100;          //CAL IF   
		R858_Sys_Info.HPF_COR=4;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;


	case R858_ISDB_T_IF_5M: 
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7940;          //CAL IF  
		R858_Sys_Info.HPF_COR=3;                //R18[6:3] [0~15 ; input: "0~15"]
		//if(R858_Chip == R858_MP)
			R858_Sys_Info.FILT_EXT_ENA=1;		     //R19[6] filter ext enable [off(0), on(1)]
		//else
		//	R858_Sys_Info.FILT_EXT_ENA=0;			 //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=3;			//buf 8
		break;

	case R858_DTMB_8M_IF_5M: 
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=0;                      //BW=8M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8650;          //CAL IF  
		R858_Sys_Info.HPF_COR=9;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_DTMB_6M_IF_5M:
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=1;                       //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=7700;           //CAL IF  
		R858_Sys_Info.HPF_COR=4;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		    //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
	
	case R858_ATSC_IF_5M:  
		R858_Sys_Info.IF_KHz=5000;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8000;          //CAL IF   
		R858_Sys_Info.HPF_COR=5;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	case R858_ATSC_IF_5500:  
		R858_Sys_Info.IF_KHz=5500;
		R858_Sys_Info.BW=1;                      //BW=7M   R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=8500;          //CAL IF   
		R858_Sys_Info.HPF_COR=3;                //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;

	default:  //R858_DVB_C_8M_IF_5M
		R858_Sys_Info.IF_KHz=5000;                     //IF
		R858_Sys_Info.BW=0;                       //BW=8M  R17[5:4] [8M(0), 7M(1), 6M(2)]
		R858_Sys_Info.FILT_CAL_IF=9250;           //CAL IF
		R858_Sys_Info.HPF_COR=10;                 //R18[6:3] [0~15 ; input: "0~15"]
		R858_Sys_Info.FILT_EXT_ENA=0;		     //R19[6] filter ext disable [off(0), on(1)]
		R858_Sys_Info.FILT_EXT_WIDEST=0x00;		//R30[2]=0, ext normal
		R858_Sys_Info.FILT_EXT_POINT=2;			//lna=max-1 & Buf 4
		break;
	}

	// DTV
	//R858_Sys_Info.SWCAP_CLK = 0x02;      //8k       (R18[1:0]=2) //AGC 500Hz map to 8k
	R858_Sys_Info.HPF_NOTCH = 0;          //R23[7] notch high  [notch high(0), notch low(1)]

	//if(R858_Chip == R858_MP)
	//{
		R858_Sys_Info.AGC_CLK = 0;          //R38[5:4] 1k   [1kHz(0), 512Hz(1), 4kHz(2), 64Hz(3)]
	//	R858_Sys_Info.IMG_GAIN = 0;          ////R46[4] High   [High(0), Low(1)]
	//}
	//else
	//{
	//	R858_Sys_Info.AGC_CLK = 1;          //R38[5:4] 1k   [1kHz(0), 512Hz(1), 4kHz(2), 64Hz(3)]
	//	R858_Sys_Info.IMG_GAIN = 3;          ////MSB:R44[0] , LSB:R46[4]  highest   [lowest(0), high(1), low(2), highest(3)]
	//}
		
	switch(R858_Standard)
	{
	case R858_J83B_IF_5370:
	case R858_J83B_IF_5070:
	case R858_J83B_IF_5M:	
	case R858_J83B_IF_5500:
	case R858_J83B_IF_4300:
	case R858_J83B_IF_4000:
	case R858_ATSC:
	case R858_ATSC_IF_5M:
	case R858_ATSC_IF_5500:
		R858_Mixer_Mode = R858_IMR_NOR;  //mixer up-side tune
		break;
	default:
		R858_Mixer_Mode = R858_IMR_REV;
		break;

	}

	//R858_Sys_Info.SWBUF_CUR = 0x04;          //low  (R4[2]=1)
	//R858_Sys_Info.FILT_CUR = 0x00;         //highest  (R10[6:5]=2'b00)
	//R858_Sys_Info.RF_BUF_CUR = 0x00;    //high  (R4[7]=0)
	//R858_Sys_Info.TF_CUR = 0x40;                  //low       (R3[6]=1)
	//R858_Sys_Info.LNA_DET_MODE=0x01;    //discharge (R31[0]=1) 
//	R858_Sys_Info.NA_DISCHARGE = 0x04;   //1          (R31[4:2]=3'b001)

	//R858_Sys_Info.FILT_COMP = 0x20;      //1          (R30[6:5]=2'b01)


	//Filter 3dB
/*
	switch(R858_Standard)
	{
		case R858_DVB_C_8M_IF_5M:
			R858_Sys_Info.FILT_3DB = 0x08;         // ON       (R30[3]=1)
		break;
	
		default: 
		    R858_Sys_Info.FILT_3DB = 0x00;         // OFF      (R30[3]=0)
		break;
	}

	//BW 1.7M
	if((R858_Standard==R858_DVB_T2_1_7M) || (R858_Standard==R858_FM))
		R858_Sys_Info.V17M = 0x80;       //enable, R11[7]=1
	else
	    R858_Sys_Info.V17M = 0x00;       //disable, R11[7]=0, (include DVBT2 1.7M IF=5MHz)
*/

	return R858_Sys_Info;
}


R858_Freq_Info_Type R858_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R858_Standard_Type R858_Standard)
{
	R858_Freq_Info_Type R858_Freq_Info;


	//----- LO dependent parameter --------
	//IMR point 
	if((LO_freq>0) && (LO_freq<205000))
         R858_Freq_Info.IMR_MEM = 0;
	else if((LO_freq>=205000) && (LO_freq<400000))
         R858_Freq_Info.IMR_MEM = 1;
	else if((LO_freq>=400000) && (LO_freq<760000))
		 R858_Freq_Info.IMR_MEM = 2;
	else 
		 R858_Freq_Info.IMR_MEM = 3;

	/*if((LO_freq>0) && (LO_freq<130000))
         R858_Freq_Info.IMR_MEM = 0;
	else if((LO_freq>=130000) && (LO_freq<210000))
         R858_Freq_Info.IMR_MEM = 1;
	else if((LO_freq>=210000) && (LO_freq<430000))
		 R858_Freq_Info.IMR_MEM = 2;
	else if((LO_freq>=430000) && (LO_freq<560000))
		 R858_Freq_Info.IMR_MEM = 3;
	else if((LO_freq>=560000) && (LO_freq<800000))
		 R858_Freq_Info.IMR_MEM = 4;
	else 
		 R858_Freq_Info.IMR_MEM = 5;*/



	//Diplexer Select R11[1:0]
	if(LO_freq<340000)
		R858_Freq_Info.TF_DIPLEXER = 2; //LPF   R11[1:0]
	else
		R858_Freq_Info.TF_DIPLEXER = 0; //HPF

	//TF_HPF_BPF  R12[2:0]
	/*	7-lowest:111 ; 6:011 ; 5:101 ; 4:001 ; 3:110 ; 2:010 ; 1:100 ; 0-noBPF:000	*/
	if(LO_freq<580000)
		R858_Freq_Info.TF_HPF_BPF = 0;		//7 => 111:lowset BPF  R12[2:0]
	else if(LO_freq>=580000 && LO_freq<660000)
		R858_Freq_Info.TF_HPF_BPF = 6;		//4 => 001
	else if(LO_freq>=660000 && LO_freq<780000)
		R858_Freq_Info.TF_HPF_BPF = 3;		//3 => 110
	else if(LO_freq>=780000 && LO_freq<900000)
		R858_Freq_Info.TF_HPF_BPF = 3;		//1 => 100
	else
		R858_Freq_Info.TF_HPF_BPF = 7;		//0 => 000

	/*
	00: highest band
	01: med band
	10: low band
	11: do not use
	*/
	//RF polyfilter band
	if((LO_freq>0) && (LO_freq<133000))  
         R858_Freq_Info.RF_POLY = 2;   // low	=> R14[3:2]
	else if((LO_freq>=133000) && (LO_freq<221000))  
         R858_Freq_Info.RF_POLY = 1;   //mid	=> R14[3:2]
	else if((LO_freq>=221000) && (LO_freq<789000))  
		 R858_Freq_Info.RF_POLY = 0;   //highest    => R14[3:2]
	else
		 R858_Freq_Info.RF_POLY = 3;   //do not use	=> R14[3:2]

	
	/*
	00: highest
	01: high
	10: low
	11: lowest
	*/
	//TF_HPF_Corner
	if((LO_freq>0) && (LO_freq<480000))  
         R858_Freq_Info.TF_HPF_CNR = 0;   //lowest	=> R11[7:6]
	else if((LO_freq>=480000) && (LO_freq<550000))  
         R858_Freq_Info.TF_HPF_CNR = 1;   // low	=> R11[7:6]]
	else if((LO_freq>=550000) && (LO_freq<700000))  
		 R858_Freq_Info.TF_HPF_CNR = 2;   // high    => R11[7:6]
	else
		 R858_Freq_Info.TF_HPF_CNR = 3;   //highest	=> R11[7:6]


	//LPF Cap, Notch
	switch(R858_Standard)
	{
		case R858_DVB_C_8M:                            //Cable
		case R858_DVB_C_6M:
        case R858_DVB_C_8M_IF_5M:
		case R858_DVB_C_8M_IF_5500:
		case R858_DVB_C_6M_IF_5M:
		case R858_DVB_C_6M_IF_5500:
		case R858_J83B_IF_5370:
		case R858_J83B_IF_5070:
		case R858_J83B_IF_5M:
		case R858_J83B_IF_5500:
		case R858_J83B_IF_4300:
		case R858_J83B_IF_4000:

			if(LO_freq<77000)  
			{
				R858_Freq_Info.LPF_CAP = 15;
				R858_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=77000) && (LO_freq<85000))
			{
				R858_Freq_Info.LPF_CAP = 15;
				R858_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=85000) && (LO_freq<115000))
			{
				R858_Freq_Info.LPF_CAP = 13;
				R858_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=115000) && (LO_freq<125000))
			{
				R858_Freq_Info.LPF_CAP = 11;
				R858_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=125000) && (LO_freq<141000))
			{
				R858_Freq_Info.LPF_CAP = 9;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=141000) && (LO_freq<157000))
			{
				R858_Freq_Info.LPF_CAP = 8;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=157000) && (LO_freq<181000))
			{
				R858_Freq_Info.LPF_CAP = 6;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=181000) && (LO_freq<205000))
			{
				R858_Freq_Info.LPF_CAP = 3;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R858_Freq_Info.LPF_CAP = 0;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			break;

		default:  //Air, DTMB (for 180nH)
			if((LO_freq>0) && (LO_freq<73000))  
			{
				R858_Freq_Info.LPF_CAP = 8;
				R858_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=73000) && (LO_freq<81000))
			{
				R858_Freq_Info.LPF_CAP = 8;
				R858_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=81000) && (LO_freq<89000))
			{
				R858_Freq_Info.LPF_CAP = 8;
				R858_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=89000) && (LO_freq<121000))
			{
				R858_Freq_Info.LPF_CAP = 6;
				R858_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=121000) && (LO_freq<145000))
			{
				R858_Freq_Info.LPF_CAP = 4;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=145000) && (LO_freq<153000))
			{
				R858_Freq_Info.LPF_CAP = 3;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=153000) && (LO_freq<177000))
			{
				R858_Freq_Info.LPF_CAP = 2;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=177000) && (LO_freq<201000))
			{
				R858_Freq_Info.LPF_CAP = 1;
				R858_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R858_Freq_Info.LPF_CAP = 0;
				R858_Freq_Info.LPF_NOTCH = 0;
			}

			break;

	}//end switch(standard)


	switch(R858_Standard)
	{
		case R858_DVB_C_8M:
		case R858_DVB_C_6M:	
        case R858_DVB_C_8M_IF_5M:
		case R858_DVB_C_8M_IF_5500:
		case R858_DVB_C_6M_IF_5M:
		case R858_DVB_C_6M_IF_5500:

			if((LO_freq>0) && (LO_freq<=200000))
				R858_Freq_Info.TF_BUF_PW = 0;
			else
				R858_Freq_Info.TF_BUF_PW = 1;
			break;

		default:

			R858_Freq_Info.TF_BUF_PW = 1;
			break;

	}
	return R858_Freq_Info;
}



R858_SysFreq_Info_Type R858_SysFreq_Sel(R858_Standard_Type R858_Standard,UINT32 RF_freq)
{
//below not release
/*
***********************************  PW  **********************************************
1.NA_PWR_DET : R44[1]
["off" (0), "on" (1)]


***********************************  LNA  **********************************************
1.LNA_TOP : R45[2:0]	co-use ; tuner 1 control
["7~0" (0~7)]

2.LNA_VTL_H : VTL=>R30[7:4]   VTH=>R30[3:0]
["0.34"(0), "0.44"(1), "0.54"(2), "0.64"(3), "0.74"(4), "0.84"(5), "0.94"(6), "1.04"(7), "1.14"(8), "1.24"(9), "1.34"(A), "1.44"(B), "1.54"(C), "1.64"(D), "1.74"(E), "1.94"(F)]

3.LNA_NRB_DET : R8[4]
["on" (0), "off" (1)]

4.RF_LTE_PSG : R32[3]
["no psg" (0), "7.5dB(5~8)" (1)]


***********************************  RF  ***********************************************
1.RF_TOP :  R32[2:0]                
["7~0" (0~7)]

2.RF_VTL_H :  R31[7:0]
["0.34"(0), "0.44"(1), "0.54"(2), "0.64"(3), "0.74"(4), "0.84"(5), "0.94"(6), "1.04"(7), "1.14"(8), "1.24"(9), "1.34"(A), "1.44"(B), "1.54"(C), "1.64"(D), "1.74"(E), "1.94"(F)]

3.RF_GAIN_LIMIT : MSB R18[2] , LSB R16[6]
["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

********************************  Mixer & Mixeramp *************************************
1.MIXER_AMP_CURRENT : R10[1]
["high" (0), "low" (1)]

2.MIXER_AMP_LPF R47[2:0]
["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]

3.MIXER_TOP R34[7:4]
["15-highest ~ 0-lowest" (0~15)]

4.MIXER_VTL_H R35[7:0]
["0.34"(0), "0.44"(1), "0.54"(2), "0.64"(3), "0.74"(4), "0.84"(5), "0.94"(6), "1.04"(7), "1.14"(8), "1.24"(9), "1.34"(A), "1.44"(B), "1.54"(C), "1.64"(D), "1.74"(E), "1.94"(F)]

5.MIXER_GAIN_LIMIT R46[7:6]
["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

********************************  Filter *************************************
1.FILTER_TOP : R36[7:4]
["15-highest ~ 0-lowest" (0~15)]

2.FILTER_VTL_H : R37[7:0]
["0.34"(0), "0.44"(1), "0.54"(2), "0.64"(3), "0.74"(4), "0.84"(5), "0.94"(6), "1.04"(7), "1.14"(8), "1.24"(9), "1.34"(A), "1.44"(B), "1.54"(C), "1.64"(D), "1.74"(E), "1.94"(F)]

3.FILT_3TH_LPF_GAIN : R17[7:6]		
[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)] ? Description different

*********************************** NRB ********************************************
1.NRB_TOP : R33[3:0]
["15-highest ~ 0-lowest" (0~15)]

2.NRB_BW_HPF : R33[5:4]
["lowest" (0), "low" (1), "high" (2), "highest" (3)]

3.NRB_BW_LPF : R33[7:6]
["widest" (0), "wide" (1), "low" (2), "lowest" (3)]

4.IMG_NRB_ADDER : R34[2:1]
["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

********************************  Polyphase *************************************
1.ENB_POLY_GAIN : R17[3]
["original" (0), "ctrl by mixamp (>10)" (1)]




***********************************  Discharge  **************************************
1. LNA_RF_DIS_MODE : [normal, Both(fast+slow), Both(slow), lna(slow), RF(slow)]   ?
(R45[1:0];R32[5];R31[0];) : 0011 normal					case 0
(R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
(R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
(R45[1:0];R32[5];R31[0];) : 1101 lna (slow)				case 3
(R45[1:0];R32[5];R31[0];) : 1110 lna RF(slow)			case 4

2. LNA_RF_DIS_CURR : R13[5]
["1/3 dis current" (0), "normal" (1)] 

3. RF_DIS_SLOW_FAST : R45 [7:4]		
SLOW : R45[5:4] ["0.15u" (0), "0.3u" (1), "0.45u" (2) , "0.6u" (3)]
FAST : R45[7:6] ["0.6u" (0), "0.9u" (4), "1.5u" (8), "2.4u" (12)]
example : SLOW / FAST = 0.3u / 1.5u = (1) + (8) = 9

4. 	BB_DIS_CURR : R40[0]
["x1" (0) , "x1/2" (1)]

5. MIXER_FILTER_DIS : R39[7:6]
["highest" (0), "high" (1), "low" (2), "lowest" (3)]

6.LNA_DIS_SLOW_FAST : R44[7:4]
SLOW : R44[5:4] ["0.15u" (0), "0.3u" (1), "0.45u" (2) , "0.6u" (3)]
FAST : R44[7:6] ["0.6u" (0), "0.9u" (4), "1.5u" (8), "2.4u" (12)]

7.BB_DET_MODE : R39[4] ?
["average" (0), "peak" (1)] 

*/

	R858_SysFreq_Info_Type R858_SysFreq_Info;

	switch(R858_Standard)
	{
	case R858_DVB_T_6M:
	case R858_DVB_T_7M:
	case R858_DVB_T_8M:
	case R858_DVB_T_6M_IF_5M:
	case R858_DVB_T_7M_IF_5M:
	case R858_DVB_T_7M_IF_5500:
	case R858_DVB_T_8M_IF_5M:
	case R858_DVB_T_8M_IF_5500:
	case R858_DVB_T2_6M:
	case R858_DVB_T2_7M: 
	case R858_DVB_T2_8M:
	case R858_DVB_T2_1_7M:
	case R858_DVB_T2_10M:
    case R858_DVB_T2_6M_IF_5M:
	case R858_DVB_T2_7M_IF_5M:
	case R858_DVB_T2_7M_IF_5500:
	case R858_DVB_T2_8M_IF_5M:
	case R858_DVB_T2_8M_IF_5500:
	case R858_DVB_T2_1_7M_IF_5M:
		if(RF_freq<=340000)
		{	
			//LNA
			R858_SysFreq_Info.LNA_TOP=2;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
			R858_SysFreq_Info.LNA_VTL_H=0x5A;				//R30[7:0] LNA VTL/H = 0.84(5) / 1.34(A)  vv

			//NRB  
			R858_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Mixer
			R858_SysFreq_Info.MIXER_VTL_H=0x49;				//R35[7:0]	Mixer VTL/H = 0.74(4) / 1.24(9) v

			//Discharge
			//R858_SysFreq_Info.LNA_RF_DIS_MODE=0;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			//R858_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
			//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=16;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9  ? 
			R858_SysFreq_Info.RF_DIS_SLOW_FAST=11;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
			R858_SysFreq_Info.LNA_RF_DIS_MODE=7;			//Both (fast+slow) b'07(R55[4]=1,R55[1]=1,R53[5]=1) 
														//slow			   b'06(R55[4]=1,R55[1]=1,R53[5]=0) 
														//normal		   b'01(R55[4]=0,R55[1]=0,R53[5]=1) 
			R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)] v 
		}
		else if ((RF_freq>782000) && (RF_freq<=790000))
		{
			//LNA
			R858_SysFreq_Info.LNA_TOP=5;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
			R858_SysFreq_Info.LNA_VTL_H=0x49;				//R30[7:0] LNA VTL/H = 0.74(4) / 1.24(9)  v

			//NRB  
			R858_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Mixer
			R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.84(5) / 1.34(A) v

			//Discharge
			//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (slow) (R45[1:0];R32[5];R31[0];) : 1100 Both (slow)			case 2
			//R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=12;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9  ? 
			R858_SysFreq_Info.RF_DIS_SLOW_FAST=9;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
			R858_SysFreq_Info.LNA_RF_DIS_MODE=7;			//Both (fast+slow) b'07(R55[4]=1,R55[1]=1,R53[5]=1) 
															//slow			   b'06(R55[4]=1,R55[1]=1,R53[5]=0) 
															//normal		   b'01(R55[4]=0,R55[1]=0,R53[5]=1) 
			R858_SysFreq_Info.LNA_NRB_DET=0;				//R8[4]    ["on" (0), "off" (1)] v 
		}
		else
		{
			//LNA
			R858_SysFreq_Info.LNA_TOP=1;					//R38[2:0] ["7~0" (0~7) ; input: "7~0"]
			R858_SysFreq_Info.LNA_VTL_H=0x49;				//R30[7:0] LNA VTL/H = 0.74(4) / 1.24(9)  v

			//NRB  
			R858_SysFreq_Info.NRB_TOP=3;					//R40[7:4]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Mixer
			R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.84(5) / 1.34(A) v

			//Discharge
			//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0];R32[5];R31[0];) : 1111 Both (fast+slow)		case 1
			//R858_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R31[1]  ["6x chargeI" (0), "4x chargeI" (1)]
			//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=16;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9  ? 
			R858_SysFreq_Info.RF_DIS_SLOW_FAST=11;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
			R858_SysFreq_Info.LNA_RF_DIS_MODE=7;			//Both (fast+slow) b'07(R55[4]=1,R55[1]=1,R53[5]=1) 
														//slow			   b'06(R55[4]=1,R55[1]=1,R53[5]=0) 
														//normal		   b'01(R55[4]=0,R55[1]=0,R53[5]=1) 
			R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)] v 
		}
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)] v  co-use ; tuner 1 control v
		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 1;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]
		//AGC
		R858_SysFreq_Info.AGC_CLK_CRTL = 0;            //R48[5]   ["normal"(0), after clksel(s) 64Hz(1)]

		//LNA
		//R858_SysFreq_Info.LNA_TOP=4;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control v
		//R858_SysFreq_Info.LNA_VTL_H=0x5A;				//R30[7:0] LNA VTL/H = 0.84(5) / 1.34(A)  v
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)] v


		//RFBuf
		R858_SysFreq_Info.RF_TOP=4;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"] v
		R858_SysFreq_Info.RF_VTL_H=0x5A;				//R31[7:0]  RF VTL/H = 0.74(4) / 1.34(A) v
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)] v

		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]	["high" (0), "low" (1)] v
		R858_SysFreq_Info.MIXER_AMP_LPF = 4;			//R47[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)] v
		R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"] v

		R858_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)] v

		//Filter
		R858_SysFreq_Info.FILTER_TOP=12;					//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"] v
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.24(9) v
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)] ? Description different

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1 ?
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)]  ?
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5  ?
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=9;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9  ? 
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)] v
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)] v
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]  ? Description different
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R32[5]		["4x chargeI" (0), "2x chargeI" (1)]
		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]

		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=1;				//R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)] v

		//NRB  
		R858_SysFreq_Info.NRB_TOP=3;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"] v
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)] v
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)] v
		R858_SysFreq_Info.IMG_NRB_ADDER=0;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]v
		
		break;

    case R858_DVB_C_8M:
	case R858_DVB_C_6M:	
	case R858_DVB_C_8M_IF_5500:
	case R858_DVB_C_8M_IF_5M:
	case R858_DVB_C_6M_IF_5500:
	case R858_DVB_C_6M_IF_5M:	
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)]

		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 0;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//AGC
		R858_SysFreq_Info.AGC_CLK_CRTL = 1;            //R48[5]   ["normal"(0), after clksel(s) 64Hz(1)]
		//LNA
		R858_SysFreq_Info.LNA_TOP=1;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x38;				//R30[7:0] LNA VTL/H=0.64(3) / 1.14(8)
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R858_SysFreq_Info.RF_TOP=3;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H=0x38;				//R31[7:0] RF VTL/H = 0.64(3) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 4;			//R47[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=12;				//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.24(9) v
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]
		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R32[5]  ["4x chargeI" (0), "2x chargeI" (1)]
		R858_SysFreq_Info.RF_DIS_SLOW_FAST=11;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
		R858_SysFreq_Info.LNA_RF_DIS_MODE=7;			//Both (fast+slow) b'07(R55[4]=1,R55[1]=1,R53[5]=1) 
														//slow			   b'06(R55[4]=1,R55[1]=1,R53[5]=0) 
														//normal		   b'01(R55[4]=0,R55[1]=0,R53[5]=1) 
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=16;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9  ? 
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["peak" (0), "average" (1)]
		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=1;				// R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]
		//NRB  
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=2;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		R858_SysFreq_Info.NRB_TOP=5;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
	
		
		break;
	case R858_J83B_IF_5370:
	case R858_J83B_IF_5070:
	case R858_J83B_IF_5M:	
	case R858_J83B_IF_5500:
	case R858_J83B_IF_4300:
	case R858_J83B_IF_4000:

		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)]

		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 0;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//LNA
		R858_SysFreq_Info.LNA_TOP=1;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x38;				//R30[7:0] LNA VTL/H=0.64(3) / 1.14(8)
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R858_SysFreq_Info.RF_TOP=3;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H=0x38;				//R31[7:0] RF VTL/H = 0.64(3) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 4;			//R47[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=12;				//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.24(9) v
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]

		R858_SysFreq_Info.FILT_5TH_NCH = 1;				//R19[0]	[high(0), low(1)]

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=0;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=8;		//R44[7:4]		0.15u (1) / 1.5u (4)   => 0 + 8 = 8
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["peak" (0), "average" (1)]

		//Discharge
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R32[5]  ["4x chargeI" (0), "2x chargeI" (1)]
		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=1;				// R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]
		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 0;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//AGC
		R858_SysFreq_Info.AGC_CLK_CRTL = 1;            //R48[5]   ["normal"(0), after clksel(s) 64Hz(1)]
		

		//NRB  
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=0;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		R858_SysFreq_Info.NRB_TOP=5;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
	
		break;

	case R858_ISDB_T_4063:	
	case R858_ISDB_T_4570:	
	case R858_ISDB_T_IF_5M:	
		if(RF_freq<=340000)
		{
			//PW
			R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]

			//RFBuf
			R858_SysFreq_Info.RF_VTL_H = 0x49;				//R31[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
			R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Polyphase
			R858_SysFreq_Info.ENB_POLY_GAIN=1;			// R17[3]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
			R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			//R858_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		}
		else if(RF_freq>=680000 && RF_freq<692000)	//LTE
		{
			//PW
			R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]

			//RFBuf
			R858_SysFreq_Info.RF_VTL_H=0x49;				//R31[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
			R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Polyphase
			R858_SysFreq_Info.ENB_POLY_GAIN=1;			// R17[3]		original ["original" (0), "ctrl by mixamp (>10)" (1)]
			
			//NRB
			R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
			R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			//R858_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		}
		else if(RF_freq>=692000 && RF_freq<698000)	//LTE
		{
			//PW
			R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]

			//RFBuf
			R858_SysFreq_Info.RF_VTL_H = 0x49;				//R31[7:0] RF VTL/H = 0.84(5) / 1.44(B)

			//Mixer and mixamp
			//R858_SysFreq_Info.MIXER_TOP=12;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
			R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
			R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Polyphase
			R858_SysFreq_Info.ENB_POLY_GAIN=1;				// R17[3]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
			R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			//R858_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		}
		else	//other frequency
		{
			//PW
			R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]

			//RFBuf
			R858_SysFreq_Info.RF_VTL_H = 0x49;				//R31[7:0] RF VTL/H = 0.74(4) / 1.34(A)

			//Mixer and mixamp
			R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
			R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]

			//Polyphase
			R858_SysFreq_Info.ENB_POLY_GAIN=1;			// R17[3]		original ["original" (0), "ctrl by mixamp (>10)" (1)]

			//NRB
			R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
			R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]

			//Filter
			//R858_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		}

		//Filter
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +1.7dB (1), +3.4dB (2), +4.6dB (3)]
		//PW
		R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)]

	
		//LNA
		R858_SysFreq_Info.LNA_TOP=1;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x49;				//R30[7:0]  LNA VTL/H=0.84(5) / 1.44(B)
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R858_SysFreq_Info.RF_TOP=3;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

	
		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_LPF = 4;			//R47[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.84(5) / 1.24(9)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=2;			//R46[7:6] ["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=12;				//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.34(A) 
		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=0;			//R45[7:4]		0.15u (0) / 0.6u (0)  
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=8;			//R44[7:4]		0.15u (0) / 1.5u (8)   => 0 + 8 = 8    
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R32[5]		 ["4x chargeI" (0), "2x chargeI" (1)]
		//NRB  
		//R858_SysFreq_Info.NRB_TOP=10;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.IMG_NRB_ADDER=2;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
		R858_SysFreq_Info.NRB_TOP=5;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
	
		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 1;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//AGC
		R858_SysFreq_Info.AGC_CLK_CRTL = 0;            //R48[5]   ["normal"(0), after clksel(s) 64Hz(1)]


		
		break;

	case R858_DTMB_8M_4570:
	case R858_DTMB_6M_4500:
	case R858_DTMB_8M_IF_5M:
	case R858_DTMB_6M_IF_5M:
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=0;				//R8[4]    ["on" (0), "off" (1)]
		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 0;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//LNA
		R858_SysFreq_Info.LNA_TOP=4;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x5A;				//R30[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]


		//RFBuf
		R858_SysFreq_Info.RF_TOP=4;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H=0x4A;				//R31[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]	["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 7;			//R47[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=9;					//R34[7:4]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x49;				//R35[7:0]	Mixer VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=4;					//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=9;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9     
		R858_SysFreq_Info.BB_DIS_CURR=0;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=2;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]			
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=0;			//R32[5]		["4x chargeI" (0), "2x chargeI" (1)]

		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=0;				//R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R858_SysFreq_Info.NRB_TOP=4;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=2;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
	
		break;

	case R858_ATSC:
	case R858_ATSC_IF_5M:
	case R858_ATSC_IF_5500:
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=0;				//R8[4]    ["on" (0), "off" (1)]

		//LNA
		R858_SysFreq_Info.LNA_TOP=5;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x7C;				//R30[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R858_SysFreq_Info.RF_TOP=5;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H = 0x6B;				//R31[7:0] RF VTL/H = 0.84(5) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

	
		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]   ["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 4;			//R47[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=10;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x5A;				//R35[7:0]	Mixer VTL/H = 0.84(5) / 1.44(B)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]


		//Filter
		R858_SysFreq_Info.FILTER_TOP=12;					//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.34(A)
		if(RF_freq<=340000)
			R858_SysFreq_Info.FILT_3TH_LPF_GAIN=0;			//R17[7:6]	[normal (0), +1.7dB (1), +3.4dB (2), +4.7dB (3)]
		else
			R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +1.7dB (1), +3.4dB (2), +4.7dB (3)]

		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]
		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=8;			//R44[7:4]		0.3u (0) / 1.5u (8)   => 0 + 8 = 8   
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]
		R858_SysFreq_Info.RF_DIS_SLOW_FAST=15;			//R45[7:4]		0.15u (1) / 0.6u (4)  => 0 + 0 = 0
		R858_SysFreq_Info.LNA_RF_DIS_MODE=7;			//Both (fast+slow) b'07(R55[4]=1,R55[1]=1,R53[5]=1) 
														//slow			   b'06(R55[4]=1,R55[1]=1,R53[5]=0) 
														//normal		   b'01(R55[4]=0,R55[1]=0,R53[5]=1) 
		R858_SysFreq_Info.LNA_RF_CHARGE_CUR=1;			//R32[5]  ["4x chargeI" (0), "2x chargeI" (1)]


		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 1;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]
		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=0;				// R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]


		//NRB  
		R858_SysFreq_Info.NRB_TOP=6;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_HPF=3;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=2;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
	

		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 1;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]

		//AGC
		R858_SysFreq_Info.AGC_CLK_CRTL = 0;            //R48[5]   ["normal"(0), after clksel(s) 64Hz(1)]
		break;
/*
	case R858_FM:
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=0;				//R8[4]    ["on" (0), "off" (1)]

		//LNA
		R858_SysFreq_Info.LNA_TOP=4;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x5A;				//R30[7:0]  LNA VTL/H=0.84(5) / 1.34(A)	
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]

		//RFBuf
		R858_SysFreq_Info.RF_TOP=4;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H = 0x5A;				//R31[7:0] RF VTL/H = 0.84(5) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]


		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=1;			//R10[1]   ["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 0;			//R47[2:0] ["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=9;					//R34[7:4] ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x5B;				//R35[7:0]	Mixer VTL/H = 0.84(5) / 1.44(B)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=5;					//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x4A;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.34(A)
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=3;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)  
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=8;			//R44[7:4]		0.3u (0) / 1.5u (8)   => 0 + 8 = 8   
		R858_SysFreq_Info.BB_DIS_CURR=1;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=0;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]


		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=0;				// R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]


		//NRB  
		R858_SysFreq_Info.NRB_TOP=4;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=1;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]

		break;
*/
	default: //DVB-T
		//PW
		R858_SysFreq_Info.NA_PWR_DET = 1;				//R44[1]   ["off" (0), "on" (1)]
		R858_SysFreq_Info.LNA_NRB_DET=1;				//R8[4]    ["on" (0), "off" (1)]

		//LNA
		R858_SysFreq_Info.LNA_TOP=4;					//R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control
		R858_SysFreq_Info.LNA_VTL_H=0x5A;				//R30[7:0] LNA VTL/H = 0.84(5) / 1.34(A)
		R858_SysFreq_Info.RF_LTE_PSG=1;					//R32[3]  ["no psg" (0), "7.5dB(5~8)" (1)]
		//Clock
		R858_SysFreq_Info.AUTO_SPEED = 0;               //R39[1]   [" manual rfagc clk"(0), "auto ctrl by slow flag to 64Hz"(1)]


		//RFBuf
		R858_SysFreq_Info.RF_TOP=4;						//R32[2:0]  ["7~0" (0~7) ; input: "7~0"]
		R858_SysFreq_Info.RF_VTL_H=0x4A;				//R31[7:0] RF VTL/H = 0.74(4) / 1.34(A)
		R858_SysFreq_Info.RF_GAIN_LIMIT=0;				//R13[6:5]v   ["max =15" (0), "max =11" (1), "max =13" (2), "max =9" (3)]

		//Mixer and Mixamp
		R858_SysFreq_Info.MIXER_AMP_CURRENT=0;			//R10[1]	["high" (0), "low" (1)]
		R858_SysFreq_Info.MIXER_AMP_LPF = 7;			//R47[2:0]	["normal (widest)" (0), "1" (1), "2" (2), "3" (3), "4" (4), "5" (5), "6" (6), "narrowest" (7)]
		R858_SysFreq_Info.MIXER_TOP=9;					//R34[7:4]	["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.MIXER_VTL_H=0x49;				//R35[7:0]	Mixer VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.MIXER_GAIN_LIMIT=3;			//R46[7:6]	["max=6" (0), "max=8" (1), "max=10" (2), "max=12" (3)]

		//Filter
		R858_SysFreq_Info.FILTER_TOP=4;					//R36[7:4]  ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.FILTER_VTL_H=0x49;			//R37[7:0]  Flter VTL/H = 0.74(4) / 1.24(9)
		R858_SysFreq_Info.FILT_3TH_LPF_GAIN=2;			//R17[7:6]	[normal (0), +0.5dB (1), +1dB (2), +1.5dB (3)]
		R858_SysFreq_Info.FILT_5TH_NCH = 0;				//R19[0]	[high(0), low(1)]

		//Discharge
		//R858_SysFreq_Info.LNA_RF_DIS_MODE=1;			//Both (fast+slow) (R45[1:0]=0'b00; R31[0]=1 ;R32[5]=1)	: 1111 Both (fast+slow)	case 1
		//R858_SysFreq_Info.LNA_RF_DIS_CURR=1;		    //R13[5]		["1/3 dis current" (0), "normal" (1)] 
		//R858_SysFreq_Info.RF_DIS_SLOW_FAST=5;			//R45[7:4]		0.3u (1) / 0.9u (4)   => 1 + 4 = 5
		//R858_SysFreq_Info.LNA_DIS_SLOW_FAST=9;			//R44[7:4]		0.3u (1) / 1.5u (8)   => 1 + 8 = 9     
		R858_SysFreq_Info.BB_DIS_CURR=0;                //R40[0]		["x1" (0) , "x1/2" (1)]
		R858_SysFreq_Info.MIXER_FILTER_DIS=2;			//R39[7:6]		["highest" (0), "high" (1), "low" (2), "lowest" (3)]
		R858_SysFreq_Info.BB_DET_MODE=0;				//R39[4]		["average" (0), "peak" (1)]

		//Polyphase
		R858_SysFreq_Info.ENB_POLY_GAIN=0;				//R17[3]=0		original ["original" (0), "ctrl by mixamp (>10)" (1)]

		//NRB  
		R858_SysFreq_Info.NRB_TOP=4;					//R33[3:0]     ["15-highest ~ 0-lowest" (0~15) ; input: "15~0"]
		R858_SysFreq_Info.NRB_BW_HPF=0;					//R33[5:4]     [lowest (0), low (1), high (2), highest (3)]
		R858_SysFreq_Info.NRB_BW_LPF=2;					//R33[7:6]     [widest (0), wide (1), low (2), lowest (3)]
		R858_SysFreq_Info.IMG_NRB_ADDER=2;				//R34[2:1]		["original" (0), "top+6" (1), "top+9" (2), "top+11" (3)]
	

		break;
	
	} //end switch

	return R858_SysFreq_Info;

}





//R858_ErrCode R858_Init_ALL(R858_ExtTunerNum_Type R858_Num,R858_Standard_Type RT_Standard1,R858_Standard_Type RT_Standard2 )
R858_ErrCode R858_Init_ALL(R858_ExtTunerNum_Type R858_Num,R858_Set_Info R858_INFO)
{													      
	R858_Sys_Info_Type R858_Sys_Init;

	R858_Sys_Init = R858_Sys_Sel (R858_INFO.R858_Standard);	//Get R850_Mixer_Mode by different standard	

	if(R858_Init(R858_Num, R858_TUNER1) != RT_Success)
		return RT_Fail;

	//if(R858_SetStandard(R858_Num, R858_TUNER1, RT_Standard1) != RT_Success)
	if(R858_SetStandard(R858_Num, R858_TUNER1, R858_INFO.R858_Standard) != RT_Success)
	{
		return RT_Fail;
	}

	if(R858_Init(R858_Num, R858_TUNER2) != RT_Success)			
		return RT_Fail;

	if(R858_SetStandard(R858_Num, R858_TUNER2, R858_INFO.R858_Standard_2) != RT_Success)
	{
		return RT_Fail;
	}


	return RT_Success;
}

R858_ErrCode R858_Init(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{
	
	UINT8 i;
		
	if(R858_Initial_done_flag[R858_Num][IntTunerNum]==FALSE)
	{

		//Reset Standby falg
		R858_SBY_flag[R858_Num][IntTunerNum] = 0;

		R858_OTH_VTH_Width_flag[R858_Num][IntTunerNum] = 0;
		R858_OTH_VTL_Width_flag[R858_Num][IntTunerNum] = 0;
		R858_LNA_VTH_Width_flag[R858_Num]=0;
		R858_LNA_VTL_Width_flag[R858_Num]=0;
		R858_LNA_VTHVTL_Change_flag[R858_Num]=0;
		R858_OTH_VTHVTL_Change_flag[R858_Num][IntTunerNum]=0;

		//reset filter cal.
		for (i=0; i<R858_STD_SIZE; i++)
		{	  
		  R858_Fil_Cal_flag[R858_Num][IntTunerNum][i] = FALSE;
		  R858_Fil_Cal_code[R858_Num][IntTunerNum][i] = 0;
		  R858_Fil_Cal_BW[R858_Num][IntTunerNum][i] = 0x00;
		  R858_Fil_Cal_LpfLsb[R858_Num][IntTunerNum][i] = 0;
		}


		if(R858_IMR_done_flag[R858_Num][IntTunerNum]==FALSE)
		{
			//start IMR calibration
			if(R858_Cal_Prepare(R858_Num, IntTunerNum, R858_IMR_CAL) != RT_Success)     
				return RT_Fail;

			if(R858_IMR_Process(R858_Num, IntTunerNum) != RT_Success)       //Tuner{N,M}
				return RT_Fail;

			R858_IMR_done_flag[R858_Num][IntTunerNum] = TRUE;
		}


		//do Xtal check (only tuner1,1)
		if(IntTunerNum==R858_TUNER1 && R858_Num==R858_NUM1)
		{
			if(R858_InitReg(R858_Num, R858_TUNER1) != RT_Success)        
				return RT_Fail;

			if(R858_Xtal_Check(R858_Num, R858_TUNER1) != RT_Success)        //only do tuner1
				return RT_Fail;

			if(R858_Xtal_Pwr_tmp==R858_XTAL_HIGHEST)
				R858_Xtal_Pwr = R858_XTAL_HIGHEST;
			else
				R858_Xtal_Pwr = R858_Xtal_Pwr_tmp + 1;
		}

			R858_Initial_done_flag[R858_Num][IntTunerNum] = TRUE;
	} 

	if(R858_InitReg(R858_Num, IntTunerNum) != RT_Success)        
			return RT_Fail;

	R858_pre_standard[R858_Num][IntTunerNum] = R858_STD_SIZE;

	return RT_Success;
}



R858_ErrCode R858_InitReg(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{
	UINT8 InitArrayCunt = 0;
	UINT8   XTAL_CAP_RESOL_1;
	
	if(R858_SHARE_XTAL == R858_NO_SHARE_XTAL)//single
	{
		XTAL_CAP_RESOL_1 = R858_XTAL_CAP;
	}
	else if (R858_SHARE_XTAL == R858_MASTER_TO_SLAVE_XTAL)//Dual
	{
		XTAL_CAP_RESOL_1 = R858_XTAL_CAP;	
	}
	else if(R858_SHARE_XTAL == R858_SLAVE_XTAL_IN) //Only R858_1 is slave
	{
		XTAL_CAP_RESOL_1 = 0;
	}
	else //Both R858_1 and R8s8_2 are slave
	{
		XTAL_CAP_RESOL_1 = 0;	
	}

	//Tuner1 R48~R55 setting
	for(InitArrayCunt = 48; InitArrayCunt<(R858_REG_NUM); InitArrayCunt ++)
	{
		R858_I2C_Len.Data[InitArrayCunt-48] = R858_iniArray[R858_TUNER1][InitArrayCunt];
		R858_Array[R858_Num][R858_TUNER1][InitArrayCunt] = R858_iniArray[R858_TUNER1][InitArrayCunt];
	}

	R858_I2C_Len.RegAddr = 48;
	R858_I2C_Len.Len = 8;
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
		return RT_Fail;

	R858_iniArray[IntTunerNum][29] = (R858_iniArray[IntTunerNum][29] & 0x86) | ((XTAL_CAP_RESOL_1 & 0x1E)<<2) | (XTAL_CAP_RESOL_1 & 0x01);//R29[6:3] R29[0]
	
	//write I2C len to R8~R55 of tuner1 or tuner2

	for(InitArrayCunt = 8; InitArrayCunt<R858_REG_NUM; InitArrayCunt ++)
	{
		
			R858_I2C_Len.Data[InitArrayCunt-8] = R858_iniArray[IntTunerNum][InitArrayCunt];
			R858_Array[R858_Num][IntTunerNum][InitArrayCunt] = R858_iniArray[IntTunerNum][InitArrayCunt];
		
	}
	//re-set xtal pw
	R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xF9) | (UINT8)((R858_XTAL_HIGHEST - R858_Xtal_Pwr)<<1);	//R29[2:1]
	R858_I2C_Len.Data[21] = R858_Array[R858_Num][IntTunerNum][29];
	
	R858_I2C_Len.RegAddr = 8;
	R858_I2C_Len.Len = R858_REG_NUM-8;
	R858_I2C_Len.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];
	if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
		return RT_Fail;

	return RT_Success;
}




R858_ErrCode R858_Xtal_Check(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{
	UINT8 i = 0;
	UINT8 vco_check_bank = 49;
	UINT8 vco_bank = 0;

	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];

	//Set PLL auto tune fatest (64k), R38[3:2]=00
	R858_I2C.RegAddr  = 38;								
	R858_Array[R858_Num][IntTunerNum][38] = (R858_Array[R858_Num][IntTunerNum][38] & 0xF3) | 0x00;
    R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][38];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;

	//Set PLL related parameter
	R858_Array[R858_Num][IntTunerNum][21] = (R858_Array[R858_Num][IntTunerNum][21] & 0x80) | 16;     //Ni=16
	R858_Array[R858_Num][IntTunerNum][25] = (R858_Array[R858_Num][IntTunerNum][25] & 0xFC) | 2;      //Si=2
	R858_Array[R858_Num][IntTunerNum][26] = (R858_Array[R858_Num][IntTunerNum][26] & 0xF8) | 2;      //div 8 (div2???)
	//R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xCF) | 0x00;  //Xtal div1
	//R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xFD) | 0x00;  //gm on
	//R858_Array[R858_Num][IntTunerNum][47] = (R858_Array[R858_Num][IntTunerNum][47] & 0x7F) | 0x00;  //tuner1 gm2 on (???)

	R858_I2C.RegAddr = 21;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][21];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;

	R858_I2C.RegAddr = 25;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][25];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;

	R858_I2C.RegAddr = 26;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][26];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;

	//R858_I2C.RegAddr = 29;
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][29];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//    return RT_Fail;

	//Set larget cap (41p)
	//R858_I2C.RegAddr = 28;
	//R858_Array[R858_Num][IntTunerNum][28] = R858_Array[R858_Num][IntTunerNum][28] | 0xF8;
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][28];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//    return RT_Fail;


	R858_I2C.RegAddr = 29;
	R858_Array[R858_Num][IntTunerNum][29] = R858_Array[R858_Num][IntTunerNum][29] | 0x78;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][29];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	//Set manual VCO bank: 1 000000;	
	R858_I2C.RegAddr = 24;
	R858_Array[R858_Num][IntTunerNum][24] = (R858_Array[R858_Num][IntTunerNum][24] & 0x80) | 0x40;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][24];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	//set auto
	R858_I2C.RegAddr = 24;
	R858_Array[R858_Num][IntTunerNum][24] = (R858_Array[R858_Num][IntTunerNum][24] & 0xBF);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][24];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	for(i=0; i<R858_XTAL_CHECK_SIZE; i++)  //(i=0~3)
	{
	    
		

		//set power,  from weak to strong 
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xF9) | ((UINT8)(R858_XTAL_HIGHEST-i)<<1);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][29];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;


		R858_Delay_MS(R858_Num, XTAL_CHK_DELAY);

		R858_I2C_Len.RegAddr = 0x00;
		R858_I2C_Len.Len = 4;  //R3[6:1]
		R858_I2C_Len.I2cAddr = R858_ADDRESS[R858_Num][R858_IntTunerNum];
		if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
		{
			if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
				return RT_Fail;
		}

		//lock to VCO band ??? if VCO=3792 (LO=474MHz)
		vco_bank = (R858_I2C_Len.Data[3] & 0x7E)>>1;
		if(((R858_I2C_Len.Data[3] & 0x01) == 0x01) && (vco_bank <= (vco_check_bank + 6)) && (vco_bank >= (vco_check_bank-6))) 
		{
		    R858_Xtal_Pwr_tmp = i;
			break;
		}

	    if(i==(R858_XTAL_CHECK_SIZE-1))
		{
	        R858_Xtal_Pwr_tmp = i;
		}
	}

    return RT_Success;
}	
R858_ErrCode R858_Cal_Prepare(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 u1CalFlag)
{
	 UINT8   InitArrayCunt = 0;
	 UINT8   XTAL_CAP_RESOL_1;
	
	 //?????????
	 //do not write both tuner at the same time, or filter cal will affect another tuner 

	 //Write Full Table, include PLL & RingPLL all settings
	 R858_I2C_Len.RegAddr = 0;
	 R858_I2C_Len.Len = R858_REG_NUM;
	 if(R858_SHARE_XTAL == R858_NO_SHARE_XTAL)//single
	 {
		XTAL_CAP_RESOL_1 = R858_XTAL_CAP;
	 }
	 else if (R858_SHARE_XTAL == R858_MASTER_TO_SLAVE_XTAL)//Dual
	 {
		XTAL_CAP_RESOL_1 = R858_XTAL_CAP;	
	 }
	 else if(R858_SHARE_XTAL == R858_SLAVE_XTAL_IN) //Only R858_1 is slave
	 {
		XTAL_CAP_RESOL_1 = 0;
	 }
	 else //Both R858_1 and R8s8_2 are slave
	 {
		XTAL_CAP_RESOL_1 = 0;	
	 }

	 switch(u1CalFlag)
	 {
		 case R858_IMR_CAL:

			
			//Tuner1 R48~R55 setting
			for(InitArrayCunt = 48; InitArrayCunt<(R858_REG_NUM); InitArrayCunt ++)
			{
	
					R858_I2C_Len.Data[InitArrayCunt-48] = R858_IMR_CAL_Array[R858_TUNER1][InitArrayCunt];
					R858_Array[R858_Num][R858_TUNER1][InitArrayCunt] = R858_IMR_CAL_Array[R858_TUNER1][InitArrayCunt];

			}

			R858_I2C_Len.RegAddr = 48;
			R858_I2C_Len.Len = 8;
			R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
				return RT_Fail;


			//write I2C len to R8~R55 of tuner1 or tuner2
			R858_IMR_CAL_Array[IntTunerNum][29] = (R858_IMR_CAL_Array[IntTunerNum][29] & 0x86) | ((XTAL_CAP_RESOL_1 & 0x1E)<<2) | (XTAL_CAP_RESOL_1 & 0x01);//R29[6:3] R29[
			for(InitArrayCunt = 8; InitArrayCunt<(R858_REG_NUM); InitArrayCunt ++)
			{			

				R858_I2C_Len.Data[InitArrayCunt-8] = R858_IMR_CAL_Array[IntTunerNum][InitArrayCunt];
				R858_Array[R858_Num][IntTunerNum][InitArrayCunt] = R858_IMR_CAL_Array[IntTunerNum][InitArrayCunt];

			}
			R858_I2C_Len.RegAddr = 8;
			R858_I2C_Len.Len = 20;//(R858_REG_NUM-8);
			R858_I2C_Len.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];
			if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
				return RT_Fail;


			//Ring PLL pw on
			R858_I2C.RegAddr=49;
			R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFD) ;
			R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;


			break;

		 case R858_LPF_CAL:



			//Tuner1 R48~R55 setting
			for(InitArrayCunt = 48; InitArrayCunt<R858_REG_NUM; InitArrayCunt ++)
			{
	
					R858_I2C_Len.Data[InitArrayCunt-48] = R858_LPF_CAL_Array[R858_TUNER1][InitArrayCunt];
					R858_Array[R858_Num][R858_TUNER1][InitArrayCunt] = R858_LPF_CAL_Array[R858_TUNER1][InitArrayCunt];

			}

			R858_I2C_Len.RegAddr = 48;
			R858_I2C_Len.Len = 8;
			R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
				return RT_Fail;


			R858_LPF_CAL_Array[IntTunerNum][29] = (R858_LPF_CAL_Array[IntTunerNum][29] & 0x86) | ((XTAL_CAP_RESOL_1 & 0x1E)<<2) | (XTAL_CAP_RESOL_1 & 0x01);//R29[6:3] R29[


			//write I2C len to R8~R55 of tuner1 or tuner2
			for(InitArrayCunt = 8; InitArrayCunt < (R858_REG_NUM); InitArrayCunt ++)
			{


					R858_I2C_Len.Data[InitArrayCunt-8] = R858_LPF_CAL_Array[IntTunerNum][InitArrayCunt];
				    R858_Array[R858_Num][IntTunerNum][InitArrayCunt] = R858_LPF_CAL_Array[IntTunerNum][InitArrayCunt];


			}
			R858_I2C_Len.RegAddr = 8;
			R858_I2C_Len.Len = (R858_REG_NUM-8);
			R858_I2C_Len.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];
			if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
				return RT_Fail;


		
			break;

		 default:
			 break;
	 }
	



//--------------------------------------------------------------------------------------------------------------------------------


	 //clk_out_enb must enable R28[7]=0 
	 R858_I2C.RegAddr=28;
	 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	 R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x7F) ;
	 R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	 	    return RT_Fail;

	 //Ring PLL pw on

	  R858_I2C.RegAddr=49;
	  R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	  R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFD) ;
	  R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	  if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;





      return RT_Success;
}




R858_ErrCode R858_IMR_Process(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{

	if(IntTunerNum==R858_TUNER1)
	{

		//Set Ring to RFBuf in R14[1], Tuner1 ON
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER1][14] = (R858_Array[R858_Num][R858_TUNER1][14] & 0xFD) | 0x02; //on
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner2 OFF
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER2];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER2][14] = (R858_Array[R858_Num][R858_TUNER2][14] & 0xFD) | 0x00; //off
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER2][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}
	else
	{


		//Set Ring to RFBuf in R14[1], Tuner1 Off
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER1][14] = (R858_Array[R858_Num][R858_TUNER1][14] & 0xFD) | 0x00; //off
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner2 On
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER2];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER2][14] = (R858_Array[R858_Num][R858_TUNER2][14] & 0xFD) | 0x02; //on
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER2][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}
	
	
	if(R858_Mixer_Mode == R858_IMR_REV)
	{
	
		if(R858_IMR(R858_Num, IntTunerNum, 2, TRUE, R858_IMR_REV) != RT_Success)       //Full K node 3
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 1, FALSE , R858_IMR_REV ) != RT_Success)
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 0, FALSE , R858_IMR_REV) != RT_Success)
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 3, FALSE , R858_IMR_REV ) != RT_Success)
			return RT_Fail;
	}
	else
	{

			
		if(R858_IMR(R858_Num, IntTunerNum, 2, TRUE, R858_IMR_NOR) != RT_Success)       //Full K node 3
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 1, FALSE , R858_IMR_NOR) != RT_Success)
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 0, FALSE , R858_IMR_NOR) != RT_Success)
			return RT_Fail;

		if(R858_IMR(R858_Num, IntTunerNum, 3, FALSE , R858_IMR_NOR) != RT_Success)
			return RT_Fail;


	}

	return RT_Success;
}
R858_ErrCode R858_IMR(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 IMR_MEM, UINT8 IM_Flag ,UINT8 Rev_Mode)
{




	UINT32 RingVCO = 0;
	UINT32 RingFreq = 0;
	UINT8 counter =0;

	R858_SectType Compare_Bet[3];


	UINT8 imr_auto_result1 = 0;
    //UINT8 imr_auto_result2 = 0;
	UINT8 imr_done_1 = 0;

	UINT32 RingRef = R858_Xtal;
	UINT8   divnum_ring = 0;
	UINT8     ADC_Read_Value = 0;
	UINT8     LPF_Count = 0;

	R858_SectType IMR_POINT;

	if(R858_Xtal==16000)  //16M
	{
         divnum_ring = 25;    
	}
	else if(R858_Xtal==24000) //24M
	{
		if(IMR_MEM==2)
			divnum_ring = 18;
		//else if(IMR_MEM == 0 && IntTunerNum ==1)
			//divnum_ring = 19;
		else
			divnum_ring = 17;
	}
	else //not support
	{
		 return RT_Fail;
	}

	 RingVCO = (divnum_ring)* 8 * RingRef;
	 //RingFreq = RingVCO/48;

	 switch(IMR_MEM)
	{
		
	case 0: // RingFreq = 102M
		RingFreq = RingVCO/32;
		R858_Array[R858_Num][R858_TUNER1][49] = (R858_Array[R858_Num][R858_TUNER1][49] & 0xCF) | (0<<4);  // ring_div1 /4 (0),      R49[5:4]
		R858_Array[R858_Num][R858_TUNER1][48] = (R858_Array[R858_Num][R858_TUNER1][48] & 0x3F) | (3<<6);  // ring_div2 /8 (3),      R49[7:6]

		break;
	case 1: // RingFreq = 326M
		RingFreq = RingVCO/10;
		R858_Array[R858_Num][R858_TUNER1][49] = (R858_Array[R858_Num][R858_TUNER1][49] & 0xCF) | (1<<4);   // ring_div1 /5 (1)	
		R858_Array[R858_Num][R858_TUNER1][48] = (R858_Array[R858_Num][R858_TUNER1][48] & 0x3F) | (1<<6);   // ring_div2 /2 (1)	

		break;
	case 2: // RingFreq = 544M
		RingFreq = RingVCO/6;
		R858_Array[R858_Num][R858_TUNER1][49] = (R858_Array[R858_Num][R858_TUNER1][49] & 0xCF) | (2<<4);  // ring_div1 /6 (2)	
		R858_Array[R858_Num][R858_TUNER1][48] = (R858_Array[R858_Num][R858_TUNER1][48] & 0x3F) | (0<<6);  // ring_div2 /1 (0)	

		break;
	case 3: // RingFreq = 816M
		RingFreq = RingVCO/4;
		R858_Array[R858_Num][R858_TUNER1][49] = (R858_Array[R858_Num][R858_TUNER1][49] & 0xCF) | (0<<4);   // ring_div1 /4 (0)	
		R858_Array[R858_Num][R858_TUNER1][48] = (R858_Array[R858_Num][R858_TUNER1][48] & 0x3F) | (0<<6);   // ring_div2 /1 (0)	

		break;
	}	 

	 //if(RingVCO>=3200000)	
		//R858_Array[R858_Num][R858_TUNER1][49] &= 0xF7;   //high vco_band
	 //else	
		//R858_Array[R858_Num][R858_TUNER1][49] |= 0x08;      //low vco_band

	 if(RingVCO>=3200000)	
		R858_Array[R858_Num][R858_TUNER1][48] &= 0xF7;   //high vco_band
	 else	
		R858_Array[R858_Num][R858_TUNER1][48] |= 0x08;      //low vco_band

		 
	 R858_Array[R858_Num][R858_TUNER1][50] = (R858_Array[R858_Num][R858_TUNER1][50] & 0xE0) | divnum_ring; 

	 //------- Set RingPLL I2C in Tuner1 reg ----------//
	 R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];	

	 R858_I2C.RegAddr = 48;
	 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][48];
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	 R858_I2C.RegAddr = 49;
	 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][49];
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	 R858_I2C.RegAddr = 50;
	 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][50];
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	//-----------------------------------------------------//

	if(R858_Num == 1)
	{

		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][R858_TUNER1][29] = (R858_Array[R858_Num][R858_TUNER1][29] & 0x06);  //R[7]=0  R[6:3] R[0] = 0
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][29];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	}

	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	 

	if(Rev_Mode==R858_IMR_REV)
	{

		//Must do MUX before PLL() 
		if(R858_MUX(R858_Num, IntTunerNum, RingFreq + R858_IMR_IF, RingFreq, R858_STD_SIZE) != RT_Success)      //IMR MUX (LO, RF)
			return RT_Fail;

		if(R858_PLL(R858_Num, IntTunerNum, (RingFreq + R858_IMR_IF), R858_STD_SIZE) != RT_Success)  //IMR PLL
			return RT_Fail;


		//Img_R = reverse
		R858_I2C.RegAddr = 16;
		R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] | 0x20);  //R16[5]=1
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}
	else
	{

		//Must do MUX before PLL() 
		if(R858_MUX(R858_Num, IntTunerNum, RingFreq - R858_IMR_IF, RingFreq, R858_STD_SIZE) != RT_Success)      //IMR MUX (LO, RF)
			return RT_Fail;

		if(R858_PLL(R858_Num, IntTunerNum, (RingFreq - R858_IMR_IF), R858_STD_SIZE) != RT_Success)  //IMR PLL
			return RT_Fail;

		//Img_R = normal
		R858_I2C.RegAddr = 16;
		R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xDF);  //R16[5]=0
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	}

	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];	  

	//LNA gain R53[5:1] = 0

	R858_I2C.RegAddr = 53;
	R858_Array[R858_Num][R858_TUNER1][53] = (R858_Array[R858_Num][R858_TUNER1][53] & 0xC1); 
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][53];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	 return RT_Fail;

	 R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	 
	 for(LPF_Count=15; LPF_Count>=1; LPF_Count--)  //start from 5 (??)
	 {
		R858_I2C.RegAddr = 37;
		R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0x0F) | (LPF_Count<<4);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];  
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;


		R858_Delay_MS(R858_Num, FILTER_GAIN_DELAY); //
		
		if(R858_Muti_Read(R858_Num, IntTunerNum, &ADC_Read_Value) != RT_Success)
			return RT_Fail;


		if(ADC_Read_Value < 50*ADC_READ_COUNT)
			break;
	 }
	//Mixer Amp LPF???



	if(R858_imr_type == IMR_AUTO)
	{	
			
		    R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];			
			//-----------------------turn on auto_imr		
			
			// tpp R35[3:1]
			R858_I2C.RegAddr = 35;
			R858_Array[R858_Num][IntTunerNum][35] = (R858_Array[R858_Num][IntTunerNum][35] & 0xF1) | (0x03<<1); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][35];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			 return RT_Fail;

			// ts R37[2:1]
			R858_I2C.RegAddr = 37;
			R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0xF9) | (0x03<<1); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			 return RT_Fail;

			


			//DSP unable R44[0]=0   off    

			R858_I2C.RegAddr = 44;
			R858_Array[R858_Num][IntTunerNum][44] = (R858_Array[R858_Num][IntTunerNum][44] & 0xFE); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][44];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			 return RT_Fail;
			


	        
			//sel code R15[7]=0   DSP       
			R858_I2C.RegAddr = 15;
			R858_Array[R858_Num][IntTunerNum][15] = (R858_Array[R858_Num][IntTunerNum][15] & 0x7F); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][15];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			 return RT_Fail;



		

			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xF0) ; 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
					return RT_Fail;

			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xF0) ; 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;

			//Dsp clk
			R858_I2C.RegAddr = 35;
			R858_Array[R858_Num][IntTunerNum][35] = (R858_Array[R858_Num][IntTunerNum][35] & 0xFE) | 0x01 ; 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][35];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;

		
			//DSP enable R44[0]=1   on       
			R858_I2C.RegAddr = 44;
			R858_Array[R858_Num][IntTunerNum][44] = (R858_Array[R858_Num][IntTunerNum][44] & 0xFE) | 0x01; 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][44];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			 return RT_Fail;


			R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];		
			R858_Delay_MS(R858_Num, 55);

			R858_I2C_Len.RegAddr = 0;
			R858_I2C_Len.Len = 3;              // read R2 ymin and xmin	
			if(I2C_Read_Len(R858_Num, &R858_I2C_Len) != RT_Success)
			{
				I2C_Read_Len(R858_Num, &R858_I2C_Len);
			}


			if(IntTunerNum == 0)	
				imr_done_1 = R858_I2C_Len.Data[1] & 0x01 ;
			else
				imr_done_1 = (R858_I2C_Len.Data[1] & 0x02)>>1 ;


			for(counter =0;counter<30;counter++)
			{
				if(imr_done_1 == 0x01)
				{	
					

					break;
				}
				else
				{
					R858_I2C_Len.RegAddr = 0;
					R858_I2C_Len.Len = 3;              // read R2 ymin and xmin	

					R858_Delay_MS(R858_Num, 1);
					if(I2C_Read_Len(R858_Num, &R858_I2C_Len) != RT_Success)
					{
						I2C_Read_Len(R858_Num, &R858_I2C_Len);
					}
					
					if(IntTunerNum == 0)	
						imr_done_1 = R858_I2C_Len.Data[1] & 0x01 ;
					else
						imr_done_1 = (R858_I2C_Len.Data[1] & 0x02)>>1 ;

				}

			}

			R858_I2C_Len.RegAddr = 0;
			R858_I2C_Len.Len = 3;              // read R2 ymin and xmin	
			if(I2C_Read_Len(R858_Num, &R858_I2C_Len) != RT_Success)
			{
				I2C_Read_Len(R858_Num, &R858_I2C_Len);
			}
			imr_auto_result1 = R858_I2C_Len.Data[2] ;

			//if(File_done==1)
			//{	

			//	//fprintf(imr_auto_result1,1,sizeof(imr_auto_result1),pFile);
			//	if(IMR_MEM == 0)
			//		fprintf(pFile0,"%d DSP_NUMBER= %d %X done1 = %d\n" ,number,(R858_I2C_Len.Data[1] & 0xFC)>>2,imr_auto_result1,imr_done_1); 
			//	else if(IMR_MEM == 1)
			//		fprintf(pFile1,"%d DSP_NUMBER= %d %X done1 = %d\n" ,number,(R858_I2C_Len.Data[1] & 0xFC)>>2,imr_auto_result1,imr_done_1); 
			//	else if(IMR_MEM == 2)
			//		fprintf(pFile2,"%d DSP_NUMBER= %d %X done1 = %d\n" ,number,(R858_I2C_Len.Data[1] & 0xFC)>>2,imr_auto_result1,imr_done_1); 
			//	else 
			//		fprintf(pFile3,"%d DSP_NUMBER= %d %X done1 = %d\n" ,number,(R858_I2C_Len.Data[1] & 0xFC)>>2,imr_auto_result1,imr_done_1); 
			//}


					

			//sel code R15[7]=1   I2C   
			//R858_I2C.RegAddr = 15;
			//R858_Array[R858_Num][IntTunerNum][15] = (R858_Array[R858_Num][IntTunerNum][15] & 0x7F) | 0x80; 
			//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][15];
			//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			// return RT_Fail;
			


			
		



		
		IMR_POINT.Gain_X  = ((IMR_POINT.Gain_X) & 0x00) | (imr_auto_result1 & 0x07) | ((imr_auto_result1 & 0x08) <<1) ;
		IMR_POINT.Phase_Y = ((IMR_POINT.Phase_Y) & 0x00) |((imr_auto_result1 & 0x70) >> 4) | ((imr_auto_result1 & 0x80) >>3) ;
		IMR_POINT.Iqcap = 0;




		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

        //sel code R15[7]=1   I2C       
		R858_I2C.RegAddr = 15;
		R858_Array[R858_Num][IntTunerNum][15] = (R858_Array[R858_Num][IntTunerNum][15] & 0x7F) | 0x80; 
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][15];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

		//R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][1-IntTunerNum];	  

		////sel code R15[7]=1   I2C       
		//R858_I2C.RegAddr = 15;
		//R858_Array[R858_Num][1-IntTunerNum][15] = (R858_Array[R858_Num][1-IntTunerNum][15] & 0x7F) | 0x80; 
		//R858_I2C.Data = R858_Array[R858_Num][1-IntTunerNum][15];
		//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		// return RT_Fail;


		Compare_Bet[0].Gain_X = IMR_POINT.Gain_X;
		Compare_Bet[0].Phase_Y =IMR_POINT.Phase_Y;

		Compare_Bet[0].Iqcap = 0;	

		if(R858_IMR_Iqcap(R858_Num, IntTunerNum, &Compare_Bet[0]) != RT_Success)
			return RT_Fail;

		IMR_POINT = Compare_Bet[0];


	}
	else
	{

		IMR_POINT.Iqcap = 0;

		if(IM_Flag == TRUE)
		{
			 if(R858_IQ(R858_Num, IntTunerNum, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
		else
		{

			if((IMR_MEM==1) || (IMR_MEM==3))
			{
				IMR_POINT.Gain_X = R858_IMR_Data[R858_Num][IntTunerNum][2].Gain_X;   //node 3
				IMR_POINT.Phase_Y = R858_IMR_Data[R858_Num][IntTunerNum][2].Phase_Y;
				IMR_POINT.Value = R858_IMR_Data[R858_Num][IntTunerNum][2].Value;
			}
			else if(IMR_MEM==0)
			{
				IMR_POINT.Gain_X = R858_IMR_Data[R858_Num][IntTunerNum][1].Gain_X;  
				IMR_POINT.Phase_Y = R858_IMR_Data[R858_Num][IntTunerNum][1].Phase_Y;
				IMR_POINT.Value = R858_IMR_Data[R858_Num][IntTunerNum][1].Value;
			}
			

			if(R858_F_IMR(R858_Num, IntTunerNum, &IMR_POINT) != RT_Success)
				return RT_Fail;
		}
	}

	//Save IMR Value
	switch(IMR_MEM)
	{
	case 0:
		R858_IMR_Data[R858_Num][IntTunerNum][0].Gain_X  = IMR_POINT.Gain_X;
		R858_IMR_Data[R858_Num][IntTunerNum][0].Phase_Y = IMR_POINT.Phase_Y;
		R858_IMR_Data[R858_Num][IntTunerNum][0].Value = IMR_POINT.Value;
		R858_IMR_Data[R858_Num][IntTunerNum][0].Iqcap = IMR_POINT.Iqcap;		
		break;
	case 1:
		R858_IMR_Data[R858_Num][IntTunerNum][1].Gain_X  = IMR_POINT.Gain_X;
		R858_IMR_Data[R858_Num][IntTunerNum][1].Phase_Y = IMR_POINT.Phase_Y;
		R858_IMR_Data[R858_Num][IntTunerNum][1].Value = IMR_POINT.Value;
		R858_IMR_Data[R858_Num][IntTunerNum][1].Iqcap = IMR_POINT.Iqcap;
		break;
	case 2:
		R858_IMR_Data[R858_Num][IntTunerNum][2].Gain_X  = IMR_POINT.Gain_X;
		R858_IMR_Data[R858_Num][IntTunerNum][2].Phase_Y = IMR_POINT.Phase_Y;
		R858_IMR_Data[R858_Num][IntTunerNum][2].Value = IMR_POINT.Value;
		R858_IMR_Data[R858_Num][IntTunerNum][2].Iqcap = IMR_POINT.Iqcap;
		break;
	case 3:
		R858_IMR_Data[R858_Num][IntTunerNum][3].Gain_X  = IMR_POINT.Gain_X;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Phase_Y = IMR_POINT.Phase_Y;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Value = IMR_POINT.Value;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Iqcap = IMR_POINT.Iqcap;
		break;
    default:
		R858_IMR_Data[R858_Num][IntTunerNum][3].Gain_X  = IMR_POINT.Gain_X;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Phase_Y = IMR_POINT.Phase_Y;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Value = IMR_POINT.Value;
		R858_IMR_Data[R858_Num][IntTunerNum][3].Iqcap = IMR_POINT.Iqcap;
		break;
	}


	return RT_Success;
}


R858_ErrCode R858_PLL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 LO_Freq, R858_Standard_Type R858_Standard)
{
	UINT8  MixDiv = 2;
	UINT8  DivBuf = 0;
	UINT8  Ni = 0;
	UINT8  Si = 0;
	UINT8  DivNum = 0;
	UINT16  Nint = 0;
	UINT32 VCO_Min = 2270000;
	UINT32 VCO_Max = 4540000;
	UINT32 VCO_Freq = 0;
	UINT32 PLL_Ref	= R858_Xtal;		
	UINT32 VCO_Fra	= 0;		
	UINT16 Nsdm = 2;
	UINT16 SDM = 0;
	UINT16 SDM16to9 = 0;
	UINT16 SDM8to1 = 0;
	UINT8   XTAL_POW = 0;
	UINT32  u2XalDivJudge = 0;
	UINT8   CP_CUR = 0x00;
	UINT8	CP_CPI = 0x00;
	UINT8   CP_OFFSET = 0x00;
	UINT8   SDM_RES = 0x00;
	UINT8   NS_RES = 0x00;
	UINT8   CLK_OUT_PWR = 0x00;
	UINT8   IQGen_Cur = 0;    //DminDmin
	UINT8   IQBias = 1;           //BiasI
	UINT8   IQLoad = 0;          //3.2k/2
	UINT8   IQdeg = 0;          //off
	UINT8   OutBuf_Bias = 0;   //max
	UINT8   BiasHf = 0;            //135u
	UINT8	PllArrayCunt = 0;

	//UINT8	XTAL_CAP_RESOL_1 = 25;
	UINT8	XTAL_CAP_1 = 0;
	UINT8	CLK_OUT_POW_1_1 = 3;//off
	UINT8	CLK_OUT_POW_1_2 = 3;//off
	UINT8	XTAL_CAP_RESOL_2 = 0;
	UINT8	XTAL_CAP_2 = 0;
	UINT8	CLK_OUT_POW_2_1 = 3;//off
	UINT8	CLK_OUT_POW_2_2 = 3;//off
	UINT32  RF_TEMP = 0;
    UINT8  Hfdiv_cur = 0;
	UINT8  Divider_out = 0;
	UINT8  Vco_cur = 0;

	//Assign device address
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	// VCO current = 0 (max)
	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | 0x00; // R25[7:6] = 0
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// VCO power = auto
	R858_I2C.RegAddr = 24;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | 0x80; // R24[7] = 1
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// HfDiv Buf = 6dB buffer
	R858_I2C.RegAddr = 26;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | 0x00; // R26[7]=0
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// Divider HfDiv current = 135u
	R858_I2C.RegAddr = 27;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | 0x00; // R27[4:3]=0
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// PLL LDOA=2.3V
	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF3) | 0x04; // R25[3:2]=01
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// PFD DLDO=4mA
	R858_I2C.RegAddr = 47;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | 0x00; // R47[6:5]=00
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/


	//-----------------------------------------------------------------------

	// DLDO2=4mA
	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | 0x00; // R25[5:4]=01
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	// HF Fiv LDO=7mA (new bonding set this off)
	R858_I2C.RegAddr = 26;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | 0x00; // R26[4:3]=00
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

		R858_I2C_Len.RegAddr = 8;
		R858_I2C_Len.Len = 48;	
	

	/*gm Tuner #1
	R29[1],R47[7] 
	00: 24 MHz
	01: 16 MHz
	10: 16 MHz
	11: OFF
	*/
	/*gm Tuner #2 
	R29[1] ( set off forever )
	0: on
	1: off
	*/

    //------ Xtal freq depend setting: Xtal Gm & AGC ref clk --------//
	//if(R858_Xtal==24000)
	//{
	//	if(IntTunerNum==R858_TUNER1)
	//	{
	//		//gm R28[4:3]

	//		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0xE7) | 0x00;  //gm*2(24)  

	//		
	//		//R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xFD) | 0x00;  //gm*2(24)  R29[1]=0
	//		//R858_Array[R858_Num][IntTunerNum][47] = (R858_Array[R858_Num][IntTunerNum][47] & 0x7F) | 0x00;  //gm*2(24)  R47[7]=0
	//	}
	//	else
	//	{
	//		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0xF7) | 0x08;  //gm*2(24)  R29[1]=1 (???)
	//	}
	//	R858_Array[R858_Num][IntTunerNum][46] = (R858_Array[R858_Num][IntTunerNum][46] & 0xDF) | 0x20;  //clk /3 (24) => R46[5]=1 
	//}
	//else if(R858_Xtal==16000)
	//{
	//	if(IntTunerNum==R858_TUNER1)
	//	{
	//		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0xE7) | 0x00;  //gm*2(24)  

	//		//R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xFD) | 0x02;  //gm*2(24)  R29[1] =1
	//		//R858_Array[R858_Num][IntTunerNum][47] = (R858_Array[R858_Num][IntTunerNum][47] & 0x7F) | 0x00;  //gm*2(24)  R47[7] =0
	//	}
	//	else
	//	{
	//		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0xF7) | 0x08;  //gm*2(24)  R29[1] =1
	//	}
	//	R858_Array[R858_Num][IntTunerNum][46] = (R858_Array[R858_Num][IntTunerNum][46] & 0xDF) | 0x00;  //clk /2 (16)	=> R45[5]=0
	//}
	//else  //not support Xtal freq
	//	return RT_Fail;

	//Xtal Gm
	//R858_I2C.RegAddr = 34;
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	//AGC ref clk 
	//R858_I2C.RegAddr = 37;
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	//----- Set XTAL Power ------//
#if(R858_SHARE_XTAL==TRUE)
		XTAL_POW = 0;        //highest,       R32[2:1]=0
		//R858_SetXtalIntCap();
#else
	XTAL_POW = (UINT8) (R858_XTAL_HIGHEST - R858_Xtal_Pwr);
	u2XalDivJudge = (UINT32) ((LO_Freq+R858_IF_GOLOBAL));
#endif

	R858_I2C.RegAddr = 29;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF9) | (XTAL_POW<<1);	//R29[2:1]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	if(R858_SHARE_XTAL == R858_NO_SHARE_XTAL)//single
	{

		XTAL_CAP_1 = 1; //10pF
		CLK_OUT_POW_1_1 = 2;//low
		CLK_OUT_POW_1_2 = 3;//off
		XTAL_CAP_RESOL_2 = 0;
		XTAL_CAP_2 = 0;
		CLK_OUT_POW_2_1 = 3;//off
		CLK_OUT_POW_2_2 = 3;//off

	}
	else if (R858_SHARE_XTAL == R858_MASTER_TO_SLAVE_XTAL)//Dual
	{

		XTAL_CAP_1 = 1;  //10pF
		CLK_OUT_POW_1_1 = 2;//low
		CLK_OUT_POW_1_2 = 2;//low
		XTAL_CAP_RESOL_2 = 0;
		XTAL_CAP_2 = 0;
		CLK_OUT_POW_2_1 = 2;//low
		CLK_OUT_POW_2_2 = 3;//off
	}
		else if(R858_SHARE_XTAL == R858_SLAVE_XTAL_IN) //Only R858_1 is slave
	{

		XTAL_CAP_1 = 0;  //0pF
		CLK_OUT_POW_1_1 = 2;//low
		CLK_OUT_POW_1_2 = 2;//low
		XTAL_CAP_RESOL_2 = 0;
		XTAL_CAP_2 = 0;
		CLK_OUT_POW_2_1 = 2;//low
		CLK_OUT_POW_2_2 = 3;//off
	}
	else //Both R858_1 and R8s8_2 are slave
	{

		XTAL_CAP_1 = 0;  //0pF
		CLK_OUT_POW_1_1 = 2;//low
		CLK_OUT_POW_1_2 = 3;//off
		XTAL_CAP_RESOL_2 = 0;
		XTAL_CAP_2 = 0;
		CLK_OUT_POW_2_1 = 2;//low
		CLK_OUT_POW_2_2 = 3;//off
	}



	if(R858_Num ==0)
	{

		
		//Xtal_cap
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | XTAL_CAP_1<<7;	//R29[7]
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;


		if(IntTunerNum==0)
		{	
			//clk_out_pow
			R858_I2C.RegAddr = 48;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | CLK_OUT_POW_1_1;	//R29[7]
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}

		else
		{
			//clk_out_pow
			R858_I2C.RegAddr = 48;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | CLK_OUT_POW_1_2;	//R29[7]
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}
	}
	else
	{

		
		//Xtal_cap resol
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x86) | ((XTAL_CAP_RESOL_2 & 0x1E)<<2) | (XTAL_CAP_RESOL_2 & 0x01);//R29[6:3] R29[0]
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
		
		//Xtal_cap
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | XTAL_CAP_2<<7;	//R29[7]
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
		
		if(IntTunerNum==0)
		{
			//clk_out_pow
			R858_I2C.RegAddr = 48;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | CLK_OUT_POW_2_1;	//R29[7]
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}

		else
		{
			//clk_out_pow
			R858_I2C.RegAddr = 48;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | CLK_OUT_POW_2_2;	//R29[7]
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}


	}


	CP_CUR = 0x05;     //0.7m, R27[2:0]=000
	CP_CPI = 0x00;
	CP_OFFSET = 0x00;  //0u,     R38[1]=0
/*
	if(R858_Xtal == 24000)
	{
		u2XalDivJudge = (UINT16) ((LO_Freq+R858_IF_GOLOBAL)/1000/12);
	//  48, 120 ,264 ,288, 336
		if((u2XalDivJudge==4)||(u2XalDivJudge==10)||(u2XalDivJudge==22)||(u2XalDivJudge==24)||(u2XalDivJudge==28))
		{
			CP_OFFSET = 0x02;  //30u,     R38[1]=1
		}
		else
		{
			CP_OFFSET = 0x00;  //0u,     R38[1]=0
		}
	}
	else if(R858_Xtal == 16000)
	{
		u2XalDivJudge = (UINT16) ((LO_Freq+R858_IF_GOLOBAL)/1000/8);
		//
		if((u2XalDivJudge==6)||(u2XalDivJudge==10)||(u2XalDivJudge==12)||(u2XalDivJudge==48))
		{
			CP_OFFSET = 0x02;  //30u,     R38[1]=1
		}
		else
		{
			CP_OFFSET = 0x00;  //0u,     R38[1]=0
		}
	}
*/

	

	//CP_OFFSET
	if(R858_Xtal == 24000)
	{	if(IntTunerNum == 0) //Tuner1
		{
			if(((u2XalDivJudge>=69000) && (u2XalDivJudge<92000)) || ((u2XalDivJudge>=164000) && (u2XalDivJudge<237000)) || (u2XalDivJudge==528000) || (u2XalDivJudge==552000) || (u2XalDivJudge==576000))
			{
				CP_OFFSET = 0x02;  //on,     R38[1]=1
			}
			else
			{
				CP_OFFSET = 0x00;  //off,    R38[1]=0
			}
		}
		else
		{
			if(((u2XalDivJudge>=48000) && (u2XalDivJudge<114000)) || ((u2XalDivJudge>=165000) && (u2XalDivJudge<171000)) || ((u2XalDivJudge>=357000) && (u2XalDivJudge<376000)) || ((u2XalDivJudge>=405000) && (u2XalDivJudge<412000)) || (u2XalDivJudge==412000)|| ((u2XalDivJudge>=429000) && (u2XalDivJudge<436000)) || ((u2XalDivJudge>=452000) && (u2XalDivJudge<460000)) || (u2XalDivJudge==360000)  || (u2XalDivJudge==408000) || (u2XalDivJudge==432000) || (u2XalDivJudge==444000) || (u2XalDivJudge==468000) || (u2XalDivJudge==504000) || (u2XalDivJudge==552000))
			{
				CP_OFFSET = 0x02;  //on,     R38[1]=1
			}
			else
			{
				CP_OFFSET = 0x00;  //off,    R38[1]=0
			}
		}
	}
	//CP_CPI
	if(R858_Xtal == 24000)
	{
		if(IntTunerNum == 0) //Tuner1
		{
			if(((u2XalDivJudge>=69000) && (u2XalDivJudge<92000)) || ((u2XalDivJudge>=164000) && (u2XalDivJudge<238000)))
			{
				CP_CPI = 0x01;  //on,		R27[5]=1
			}
			else
			{
				CP_CPI = 0x00;  //off,     R27[5]=0
			}
		}
		else				//Tuner2
		{
			if(((u2XalDivJudge>=48000) && (u2XalDivJudge<114000) && (u2XalDivJudge!=72000) ) || ((u2XalDivJudge>=165000) && (u2XalDivJudge<172000)) || ((u2XalDivJudge>=357000) && (u2XalDivJudge<376000)) || (u2XalDivJudge==384000) || ((u2XalDivJudge>=405000) && (u2XalDivJudge<412000)) || ((u2XalDivJudge>=429000) && (u2XalDivJudge<436000))  || (u2XalDivJudge==444000) || (u2XalDivJudge==468000) || (u2XalDivJudge==504000))
			{
				CP_CPI = 0x01;  //on,		R27[5]=1
			}
			else
			{
				CP_CPI = 0x00;  //off,     R27[5]=0
			}

		}
	}
	//CP_CUR
	if(R858_Xtal == 24000)
	{

		if(IntTunerNum == 0) //Tuner1
		{
			//if(((u2XalDivJudge>=48000) && (u2XalDivJudge<114000) && (u2XalDivJudge!=72000) )  || (u2XalDivJudge==962000)) //48 to 198MHz
			if(((u2XalDivJudge>=48000) && (u2XalDivJudge<69000)) || ((u2XalDivJudge>=76000) && (u2XalDivJudge<117000)) || ((u2XalDivJudge>=164000) && (u2XalDivJudge<238000)) || ((u2XalDivJudge>=488000) && (u2XalDivJudge<497000)) || ((u2XalDivJudge>=512000) && (u2XalDivJudge<524000)) || ((u2XalDivJudge>=533000) && (u2XalDivJudge<547000)) || ((u2XalDivJudge>=557000) && (u2XalDivJudge<573000)) || ((u2XalDivJudge>=581000) && (u2XalDivJudge<596000)) || ((u2XalDivJudge>=605000) && (u2XalDivJudge<620000)) || ((u2XalDivJudge>=629000) && (u2XalDivJudge<644000))  || ((u2XalDivJudge>=846000) && (u2XalDivJudge<857000)) || ((u2XalDivJudge>=900000) && (u2XalDivJudge<1000000)) ) //48 to 198MHz
			{
				CP_CUR = 0x00;  //0.7mA,		R27[2:0]=0
			}
			else if(((u2XalDivJudge>=69000) && (u2XalDivJudge<76000))  || (u2XalDivJudge==648000) || (u2XalDivJudge==672000) || (u2XalDivJudge==696000) || (u2XalDivJudge==720000)  || (u2XalDivJudge==744000) || (u2XalDivJudge==768000))
			{
				CP_CUR = 0x05;  //0.2mA,		R27[2:0]=5
			}
			//else if(u2XalDivJudge==600000 || u2XalDivJudge==624000)
			else if(u2XalDivJudge==600000 )
			{
				CP_CUR = 0x03;  //0.4mA,		R27[2:0]=3
			}
			//else if((u2XalDivJudge>=114000) && (u2XalDivJudge<198000))  // 114MHz to 198MHz
			else if((u2XalDivJudge>=117000) && (u2XalDivJudge<198000))  // 114MHz to 198MHz
			{
				CP_CUR = 0x04;  //0.3mA,		R27[2:0]=4
			}
			//else if((u2XalDivJudge>=864000) && (u2XalDivJudge<=1000000))
			else if((u2XalDivJudge>=864000) && (u2XalDivJudge<=900000))
			{
				CP_CUR = 0x05;  //0.2mA,		R27[2:0]=5
			}
			//else if((u2XalDivJudge==528000) || (u2XalDivJudge==552000) || (u2XalDivJudge==576000)) 
			else if((u2XalDivJudge==528000) ) 
			{
				CP_CUR = 0x01;  //0.6mA,		R27[2:0]=1
			}
			else	// >198MHz
			{
				CP_CUR = 0x00;  //0.7mA,		R27[2:0]=0
			}
		}
		else //tuner2
		{
			if((u2XalDivJudge>=48000) && (u2XalDivJudge<198000)) //48 to 198MHz
			{
				CP_CUR = 0x04;  //0.3mA,		R27[2:0]=4
			}
			else if(((u2XalDivJudge>=376000) && (u2XalDivJudge<405000)) || ((u2XalDivJudge>=436000) && (u2XalDivJudge<452000)) || ((u2XalDivJudge>=513000) && (u2XalDivJudge<516000)) || ((u2XalDivJudge>=878000) && (u2XalDivJudge<1000000)))
			{
				CP_CUR = 0x00;  //0.7mA,		R27[2:0]=0
			}
			else if(u2XalDivJudge==216000 || u2XalDivJudge==360000 || ((u2XalDivJudge>=357000) && (u2XalDivJudge<376000)) || ((u2XalDivJudge>=405000) && (u2XalDivJudge<411000))  )
			{
				CP_CUR = 0x03;  //0.4mA,		R27[2:0]=3
			}
			else if((u2XalDivJudge==384000) || (u2XalDivJudge==408000) || ((u2XalDivJudge>=429000) && (u2XalDivJudge<436000)) || (u2XalDivJudge==444000) || ((u2XalDivJudge>=452000) && (u2XalDivJudge<459000)) || (u2XalDivJudge==556000))
			{
				CP_CUR = 0x02;  //0.5mA,		R27[2:0]=2
			}
			else if(((u2XalDivJudge>=864000) && (u2XalDivJudge<87800)) ||(u2XalDivJudge==72000))
			{
				CP_CUR = 0x05;  //0.2mA,		R27[2:0]=5
			}
			else if((u2XalDivJudge==468000) || (u2XalDivJudge==504000) || (u2XalDivJudge==552000)) 
			{
				CP_CUR = 0x01;  //0.6mA,		R27[2:0]=1
			}
			else // >=198MHz
			{
				CP_CUR = 0x00;  //0.7mA,		R27[2:0]=0
			}
		}
	}
	//CLK_OUT_PWR  Tuner1 and Tuner2 Set Low
	if(R858_Xtal == 24000)
	{
		CLK_OUT_PWR = 0x02;  //low,       R48[1:0]=2
	}

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.RegAddr = 27;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | (CP_CUR);	//    => R27[2:0]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	R858_I2C.RegAddr = 27;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (CP_CPI<<5);	//    => R27[2:0]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	R858_I2C.RegAddr = 38;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | (CP_OFFSET);	//    => R38[1]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	R858_I2C.RegAddr = 48;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | (CLK_OUT_PWR);	//    => R38[1]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/


	//set pll autotune = 64kHz (fast)  R38[3:2] = 00
	R858_I2C.RegAddr = 38;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7;
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

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

	RF_TEMP = LO_Freq + 5000;

	//IQ Gen block & BiasHF & NS_RES & SDM_Res




	BiasHf = 0;           //90u
	Hfdiv_cur = 0;	      //90

	if(MixDiv <= 4)  //Div=2,4
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 1;           //BiasI   
		IQLoad = 0;          //3.2k/2 
		OutBuf_Bias = 3;   //3 (max)     
		//BiasHf = 2;           //90u
		SDM_RES = 0;     //short  
		NS_RES = 0;        //0R 

		//Hfdiv_cur = 2;	//90


	}
	else if(MixDiv == 8) 
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 2;   //2 
		//BiasHf = 2;           //90u
		SDM_RES = 0;     //short
		NS_RES = 1;        //800R 
		//Hfdiv_cur = 2;	//90

		DivNum = 2;
	}
	else if(MixDiv == 16) 
	{
		IQGen_Cur = 1;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 3;   //1 
		//BiasHf = 2;           //90u
		SDM_RES = 0;     //short  
		NS_RES = 0;        //0R
		//Hfdiv_cur = 2;	//90
		Divider_out = 0;
		DivNum = 4;

		if(IntTunerNum == 0)
		{
			IQdeg = 1; //800R
		}
		else
		{
			IQdeg = 0; //off
		}

	}
	else if(MixDiv >= 32) //32, 64
	{
		IQGen_Cur = 1;    //DminDmin
		IQBias = 0;           //BiasI/2   
		IQLoad = 1;          //3.2k
		OutBuf_Bias = 3;   //0 (min)
		//BiasHf = 2;           //90u
		SDM_RES = 0;     //short
		NS_RES = 0;        //0R
		//Hfdiv_cur = 2;	//90
		Divider_out = 0;


		if(MixDiv == 32)
		{
			//BiasHf = 2;     //90u
			//Hfdiv_cur = 2;	//90

			if(IntTunerNum == 0)
			{
				IQdeg = 1; //800R
			}
			else
			{
				IQdeg = 0; //off
			}

			
		}
		else
		{
			//BiasHf = 2;     //90u
			//Hfdiv_cur = 1;	//110u
			IQdeg = 0; //off
		}


		if( MixDiv == 32)
			DivNum = 6;
		else
			DivNum = 7;
	}

	else
	{
		return RT_Fail;
	}
	if(Divider_Manual==1)
	{
		R858_XtalDiv = XTAL_DIV2_1;
	}
	else
	{
		//Xtal Div setting
		if(R858_Standard == R858_STD_SIZE) //for cal, RingPLL not support xtal div2
		{
				R858_XtalDiv = XTAL_DIV1; //div1 for calibration
		}
		else  //DTV
		{		
			u2XalDivJudge = (UINT32) ((LO_Freq+R858_IF_GOLOBAL));

			if(IntTunerNum == 0) //Tuner1
			{
				if(((u2XalDivJudge>=48000) && (u2XalDivJudge<57000)) || (u2XalDivJudge==528000) || (u2XalDivJudge==552000) || (u2XalDivJudge==576000) || (u2XalDivJudge==600000) || (u2XalDivJudge==624000) || (u2XalDivJudge==648000) || (u2XalDivJudge==672000) || (u2XalDivJudge==696000) || (u2XalDivJudge==720000) || (u2XalDivJudge==744000) || (u2XalDivJudge==768000)) //48 to 114MHz
				{
					R858_XtalDiv = XTAL_DIV1_2;
				}
				//else if(((u2XalDivJudge>=114000) && (u2XalDivJudge<198000) ) || (u2XalDivJudge==72000) || (u2XalDivJudge==216000) || (u2XalDivJudge==360000) || (u2XalDivJudge==360000) || (u2XalDivJudge==828000) )   // 114MHz to 198MHz
				else if(((u2XalDivJudge>=57000) && (u2XalDivJudge<238000)) || ((u2XalDivJudge>=488000) && (u2XalDivJudge<497000))  || ((u2XalDivJudge>=848000) && (u2XalDivJudge<857000)) || ((u2XalDivJudge>=900000) && (u2XalDivJudge<1003000))   || (u2XalDivJudge==828000) )   // 114MHz to 198MHz
				{
					R858_XtalDiv = XTAL_DIV1;
				}
				else if((u2XalDivJudge>=512000) && (u2XalDivJudge<=780000))  // 516MHz to 780MHz
				{
					R858_XtalDiv = XTAL_DIV1;
				}
				else	// >198MHz
				{
					R858_XtalDiv = XTAL_DIV1_2;
				}
			}
			else
			{

				if((u2XalDivJudge>=48000) && (u2XalDivJudge<114000) && (u2XalDivJudge!=72000)) //48 to 114MHz
				{
					R858_XtalDiv = XTAL_DIV1_2;
				}
				else if(((u2XalDivJudge>=114000) && (u2XalDivJudge<198000)) || ((u2XalDivJudge>=357000) && (u2XalDivJudge<412000))  || ((u2XalDivJudge>=429000) && (u2XalDivJudge<460000)) || ((u2XalDivJudge>=513000) && (u2XalDivJudge<516000)) || ((u2XalDivJudge>=878000) && (u2XalDivJudge<1003000)) || (u2XalDivJudge==72000) || (u2XalDivJudge==216000) || (u2XalDivJudge==360000))   // 114MHz to 198MHz
				{
					R858_XtalDiv = XTAL_DIV1;
				}
				else if((u2XalDivJudge>=516000) && (u2XalDivJudge<=780000))  // 516MHz to 780MHz
				{
					R858_XtalDiv = XTAL_DIV1;
				}
				else	// >198MHz
				{
					R858_XtalDiv = XTAL_DIV1_2;
				}

			}
		}
	}
	//Assign device address
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
    
	//V3???????

	//R858_XtalDiv = XTAL_DIV2; //div 1, 2, 4
	if(R858_XtalDiv==XTAL_DIV1)
	{
		PLL_Ref = R858_Xtal;	         
		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0x9F) | 0x00; //
	}
	else if(R858_XtalDiv==XTAL_DIV1_2)
	{
		PLL_Ref = R858_Xtal/2;   
		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0x9F) | 0x20; //
	}
	else if(R858_XtalDiv==XTAL_DIV2_1)
	{
		PLL_Ref = R858_Xtal/2;   
		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0x9F) | 0x20; //
	}
	else if(R858_XtalDiv==XTAL_DIV4)  //24MHz
	{
		PLL_Ref = R858_Xtal/4;
		R858_Array[R858_Num][IntTunerNum][28] = (R858_Array[R858_Num][IntTunerNum][28] & 0x9F) | 0x40; //
	}



	//if(R858_XtalDiv==XTAL_DIV1)
	//{
	//	PLL_Ref = R858_Xtal;	         
	//	R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xCF) | 0x00; //1st_div2=0, 2nd_div2=0	 R29[5:4]
	//}
	//else if(R858_XtalDiv==XTAL_DIV1_2)
	//{
	//	PLL_Ref = R858_Xtal/2;   
	//	R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xCF) | 0x20; //1st_div2=0(R29[4]), 2nd_div2=1(R29[5])
	//}
	//else if(R858_XtalDiv==XTAL_DIV2_1)
	//{
	//	PLL_Ref = R858_Xtal/2;   
	//	R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xCF) | 0x10; //1st_div2=1(R29[4]), 2nd_div2=0(R29[5])
	//}
	//else if(R858_XtalDiv==XTAL_DIV4)  //24MHz
	//{
	//	PLL_Ref = R858_Xtal/4;
	//	R858_Array[R858_Num][IntTunerNum][29] = (R858_Array[R858_Num][IntTunerNum][29] & 0xCF) | 0x30; //2nd_div2=1, 1st_div2=1  R29[5:4]
	//}

	//Xtal divider setting
	//R858_I2C.RegAddr = 34;
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	   return RT_Fail;*/

	//IQ gen current R10[6]
	R858_I2C.RegAddr = 10;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xBF) | (IQGen_Cur<<6); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//Out Buf Bias R41[7:6]
	R858_I2C.RegAddr = 41;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (OutBuf_Bias<<6); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//BiasI R41[5]
	R858_I2C.RegAddr = 41;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (IQBias<<5); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//IQLoad R41[4]
	R858_I2C.RegAddr = 41;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) | (IQLoad<<4); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//BiasHF R26[6:5]
	R858_I2C.RegAddr = 26;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | (BiasHf<<5); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//SDM_RES R28[2]
	R858_I2C.RegAddr = 28;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFB) | (SDM_RES<<2); 
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//NS_RES  R21[7] 
	//if(Chip_type_flag == 1)
	//{
	//R858_I2C.RegAddr = 21;
	//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | (NS_RES<<7); 
	//}
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;*/

	//Divider num R26[2:0]
	R858_I2C.RegAddr = 26;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | (DivNum);  
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

    //Vco curr R25[7:6]
	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (Vco_cur<<6);  

	//Divider out R26[7]
	R858_I2C.RegAddr = 26;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | (Divider_out<<7);  

	//Divider out R27[4:3]
	R858_I2C.RegAddr = 27;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | (Hfdiv_cur<<3);  

	//IQ_deg R44[3]
	R858_I2C.RegAddr = 44;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7) | (IQdeg<<3);  

	////Divider out R19[5]  v3_a no
	//R858_I2C.RegAddr = 19;
	//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (	Div2_ouput_buf<<5);  



	//R858_I2C.RegAddr = 26;
	//if(DivNum== 3||DivNum== 4||DivNum== 5)
	//	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | 0x80 ; //1
	//else
	//	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) ; //0


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

	R858_I2C.RegAddr = 21;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x80) | Ni;     //R21[6:0]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	  return RT_Fail;*/

	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | Si;  //R25[1:0]
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	  return RT_Fail;*/
         	
	//pw_sdm & pw_dither
	R858_I2C.RegAddr = 28;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] &= 0xFC;        //R28[1:0]
	if(VCO_Fra == 0)
	{
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] |= 0x03;
	}
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

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

	R858_I2C.RegAddr = 23;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (UINT8) SDM16to9;  //R23
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	R858_I2C.RegAddr = 22;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (UINT8) SDM8to1;    //R22
	//R858_I2C_Len.Data[R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	//if(IntTunerNum == 0)
	//{
	R858_I2C_Len.RegAddr = 8;
	R858_I2C_Len.Len = 40;	

	for(PllArrayCunt = 0 ; PllArrayCunt < 40 ; PllArrayCunt ++)
	{
		R858_I2C_Len.Data[PllArrayCunt] = R858_Array[R858_Num][IntTunerNum][PllArrayCunt + 8];
	}
	if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
		return RT_Fail;




	/*}
	else
	{

		R858_I2C_Len.RegAddr = 8;
		R858_I2C_Len.Len = 40;	
	
		for(PllArrayCunt = 0 ; PllArrayCunt < 40 ; PllArrayCunt ++)
		{
			R858_I2C_Len.Data[PllArrayCunt] = R858_Array[R858_Num][IntTunerNum][PllArrayCunt + 8];
		}
		if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
			return RT_Fail;

	}*/
	
	
	
	
	if(R858_XtalDiv == XTAL_DIV1)
		R858_Delay_MS(R858_Num, PLL_LOCK_DELAY);
	else if((R858_XtalDiv == XTAL_DIV1_2) || (R858_XtalDiv == XTAL_DIV2_1))
	    R858_Delay_MS(R858_Num, PLL_LOCK_DELAY*2);
	else
		R858_Delay_MS(R858_Num, PLL_LOCK_DELAY*4);
	   
		//R858_Delay_MS(R858_Num, PLL_LOCK_DELAY*4);  

	//R858_Delay_MS(R858_Num, PLL_LOCK_DELAY*2);

	//set pll autotune = 1khz R38[3:2]
	R858_I2C.RegAddr = 38;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7) | 0x08;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;

}


R858_ErrCode R858_MUX(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 LO_KHz, UINT32 RF_KHz, R858_Standard_Type R858_Standard)
{	
	UINT8 Reg_IMR_Gain   = 0;
	UINT8 Reg_IMR_Phase  = 0;
	UINT8 Reg_IMR_Iqcap  = 0;

	//Assign device address
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	//Freq_Info_Type Freq_Info1;
	Freq_Info1 = R858_Freq_Sel(LO_KHz, RF_KHz, R858_Standard);


	// TF_DIPLEXER
	R858_I2C.RegAddr = 11;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | (Freq_Info1.TF_DIPLEXER);  // R11[1:0]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	////TF_HPF_BPF =>  R11[7:6], R12[0]
	//R858_I2C.RegAddr = 11;
	//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | ((Freq_Info1.TF_HPF_BPF & 0x06)<<5) ;  // R11[7:6]
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;


	//R858_I2C.RegAddr = 12;
	//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE) | (Freq_Info1.TF_HPF_BPF & 0x01) ;  // R12[0]
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;

	//TF_HPF_BPF =>  R12[2:0]

	R858_I2C.RegAddr = 12;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | (Freq_Info1.TF_HPF_BPF & 0x07) ;  // R12[2:0]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	//TF_HPF_CNR => R11[7:6]
	R858_I2C.RegAddr = 11;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (Freq_Info1.TF_HPF_CNR << 6);  // R11[7:6]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	// RF Polyfilter
	R858_I2C.RegAddr = 14;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF3) | (Freq_Info1.RF_POLY << 2);  //R14[3:2]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	// LNA Cap
	R858_I2C.RegAddr = 11;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xC3) | (Freq_Info1.LPF_CAP << 2);	  //R11[5:2]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	// LNA Notch
	R858_I2C.RegAddr = 12;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x07) | (Freq_Info1.LPF_NOTCH << 3);  // R12[7:3]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	//TF BUF PW
	R858_I2C.RegAddr = 9;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) | (Freq_Info1.TF_BUF_PW << 4);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	//Set_IMR
	if(R858_IMR_done_flag[R858_Num][IntTunerNum] == TRUE)
	{
		Reg_IMR_Gain = R858_IMR_Data[R858_Num][IntTunerNum][Freq_Info1.IMR_MEM].Gain_X;       //b4 + b3:0
		Reg_IMR_Phase = R858_IMR_Data[R858_Num][IntTunerNum][Freq_Info1.IMR_MEM].Phase_Y;     //b4 + b3:0
		Reg_IMR_Iqcap = R858_IMR_Data[R858_Num][IntTunerNum][Freq_Info1.IMR_MEM].Iqcap;          //0,1,2
	}
	else
	{
		Reg_IMR_Gain = 0;
	    Reg_IMR_Phase = 0;
		Reg_IMR_Iqcap = 0;
	}

	//Gain/Phase, R16[3:0]R17[3:0]
	R858_I2C.RegAddr = 16;                  
	R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (Reg_IMR_Gain & 0x1F);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	R858_I2C.RegAddr = 17;                  
	R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xE0) | (Reg_IMR_Phase & 0x1F);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;



 //   //Gain/Phase dir, R17[4]phase  R16[4]gan
	//R858_I2C.RegAddr = 16;                  
	//R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xEF) | ((Reg_IMR_Gain & 0x10));
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;

	//R858_I2C.RegAddr = 17;                  
	//R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xEF) | ((Reg_IMR_Phase & 0x10));
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;



	//Iqcap, R15[2:1]
	R858_I2C.RegAddr = 15;
	R858_Array[R858_Num][IntTunerNum][15] = (R858_Array[R858_Num][IntTunerNum][15] & 0xF9) | (Reg_IMR_Iqcap<<1);
	R858_I2C.Data =R858_Array[R858_Num][IntTunerNum][15];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	return RT_Success;
}



R858_ErrCode R858_IQ(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont)
{
	
	
	R858_SectType Compare_IQ[3];
	UINT8   X_Direction;  // 1:X, 0:Y

	UINT8   ADC_Read_Value;
	UINT8   LPF_Count;

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	 //manual LPF gain
	 R858_I2C.RegAddr = 19;
	 R858_Array[R858_Num][IntTunerNum][19] = (R858_Array[R858_Num][IntTunerNum][19] & 0xFD);
	 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][19];  
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	 // increase LPF power to let image significant
	 for(LPF_Count=0; LPF_Count<16; LPF_Count++)  //start from 5 (??)
	 {
		R858_I2C.RegAddr = 37;
		R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0x0F) | (LPF_Count<<4);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];  
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, FILTER_GAIN_DELAY); //
		
		if(R858_Muti_Read(R858_Num, IntTunerNum, &ADC_Read_Value) != RT_Success)
			return RT_Fail;

		if(ADC_Read_Value > 40*ADC_READ_COUNT)
			break;
	 }

	/*R858_I2C.RegAddr = 37;
	R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0x0F) | (15<<4);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];  
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/

	Compare_IQ[0].Gain_X  = (R858_Array[R858_Num][IntTunerNum][16] & 0x1F); 
	Compare_IQ[0].Phase_Y = (R858_Array[R858_Num][IntTunerNum][17] & 0x1F);

	    // Determine X or Y
	    if(R858_IMR_Cross(R858_Num, IntTunerNum, &Compare_IQ[0], &X_Direction) != RT_Success)
			return RT_Fail;


		if(X_Direction==1)
		{
			//compare and find min of 3 points. determine I/Q direction
		    if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
			  return RT_Fail;

		    //increase step to find min value of this direction
		    if(R858_CompreStep(R858_Num, IntTunerNum, &Compare_IQ[0], 0x10) != RT_Success)  //X
			  return RT_Fail;	
		}
		else
		{
		   //compare and find min of 3 points. determine I/Q direction
		   if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		   	 return RT_Fail;

		   //increase step to find min value of this direction
		   if(R858_CompreStep(R858_Num, IntTunerNum, &Compare_IQ[0], 0x11) != RT_Success)  //Y
			 return RT_Fail;	
		}

		//Another direction
		if(X_Direction==1)
		{	    
           if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success) //Y	
		     return RT_Fail;	

		   //compare and find min of 3 points. determine I/Q direction
		   if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		   	 return RT_Fail;

		   //increase step to find min value of this direction
		   if(R858_CompreStep(R858_Num, IntTunerNum, &Compare_IQ[0], 0x11) != RT_Success)  //Y
			 return RT_Fail;	
		}
		else
		{
		   if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, 0x11, &Compare_IQ[0]) != RT_Success) //X
		     return RT_Fail;	
        
		   //compare and find min of 3 points. determine I/Q direction
		   if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		     return RT_Fail;

	       //increase step to find min value of this direction
		   if(R858_CompreStep(R858_Num, IntTunerNum, &Compare_IQ[0], 0x10) != RT_Success) //X
		     return RT_Fail;	
		}
		

		//--- Check 3 points again---//
		if(X_Direction==1)
		{
		    if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, 0x11, &Compare_IQ[0]) != RT_Success) //X
			  return RT_Fail;	
		}
		else
		{
		   if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success) //Y
			return RT_Fail;		
		}

		if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
			return RT_Fail;

    //Section-9 check
    //if(R858_F_IMR(&Compare_IQ[0]) != RT_Success)
	if(R858_Section(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
			return RT_Fail;

	//clear IQ_Cap = 0   
	Compare_IQ[0].Iqcap = 0;

	if(R858_IMR_Iqcap(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
			return RT_Fail;

	*IQ_Pont = Compare_IQ[0];

	//reset gain/phase/iqcap control setting
	R858_I2C.RegAddr = 16;	// R16[4:0]  
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE0;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	R858_I2C.RegAddr = 17;	// R17[4:0]  
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE0;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	R858_I2C.RegAddr = 15;	//  R15[2:1] 
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF9;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}



//--------------------------------------------------------------------------------------------
// Purpose: record IMC results by input gain/phase location
//          then adjust gain or phase positive 1 step and negtive 1 step, both record results
// input: FixPot: phase or gain
//        FlucPot phase or gain
//        PotReg: 0x10 or 0x11 for R858
//        CompareTree: 3 IMR trace and results
// output: TREU or FALSE
//--------------------------------------------------------------------------------------------

//20131217-Ryan


R858_ErrCode R858_IQ_Tree(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R858_SectType* CompareTree)
{
	UINT8 TreeCunt  = 0;
	UINT8 TreeTimes = 3;
//	UINT8 PntReg = 0;

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	//PntReg is reg to change; FlucPot is change value
/*
	if(PotReg == 0x10)
		PntReg = 0x11; //phase control
	else
		PntReg = 0x10; //gain control
*/
	for(TreeCunt = 0; TreeCunt<TreeTimes; TreeCunt++)
	{
		if(PotReg==0x10)  //change phase (FlucPot is phase)
		{
/*			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0x00) | ((FlucPot & 0x0F)<<4) | (FixPot & 0x0F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;

			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xFD) | ((FlucPot & 0x10)>>3) | ((FixPot & 0x10)>>4);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;	*/	


			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (FixPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;


			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xE0) | (FlucPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;	
		}

		else //change gain (FlucPot is gain)
		{
/*			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0x00) | ((FlucPot & 0x0F)<<0) | ((FixPot & 0x0F)<<4);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;

			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xFE) | ((FlucPot & 0x10)>>4) | ((FixPot & 0x10)>>3);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;		*/		

			
			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (FlucPot & 0x1F); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;


			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xE0)  | (FixPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;	
		}
/*
		R858_I2C.RegAddr = PotReg;
		R858_I2C.Data    = FixPot;
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_I2C.RegAddr = PntReg;
		R858_I2C.Data    = FlucPot;
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
*/
		if(R858_Muti_Read(R858_Num, IntTunerNum, &CompareTree[TreeCunt].Value) != RT_Success)
			return RT_Fail;
	

		if(PotReg == 0x10) //change phase
		{
			CompareTree[TreeCunt].Gain_X  = FixPot;
			CompareTree[TreeCunt].Phase_Y = FlucPot;
		}
		else  //change gain
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
				if(FlucPot & 0x10) //b[4]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;			
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;
				}
			}
			else
				FlucPot = FlucPot - 2;  
				
		}
	}

	return RT_Success;
}
R858_ErrCode R858_IQ_Tree5(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R858_SectType* CompareTree)
{
	/*UINT8 TreeCunt  = 0;
	UINT8 TreeTimes = 3;*/


	UINT8 TreeCunt  = 0;
	UINT8 TreeTimes = 5;
	UINT8 TempPot   = 0;
	UINT8 CompCunt = 0;
	R858_SectType CorTemp[5];
    R858_SectType Compare_Temp;
	UINT8 CuntTemp = 0;
//	UINT8 PntReg = 0;


	memset(&Compare_Temp,0, sizeof(R858_SectType));
	Compare_Temp.Value = 255;

	for(CompCunt=0; CompCunt<3; CompCunt++)
	{
		CorTemp[CompCunt].Gain_X = CompareTree[CompCunt].Gain_X;
		CorTemp[CompCunt].Phase_Y = CompareTree[CompCunt].Phase_Y;
		CorTemp[CompCunt].Value = CompareTree[CompCunt].Value;
	}


	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	//PntReg is reg to change; FlucPot is change value

	for(TreeCunt = 0; TreeCunt<TreeTimes; TreeCunt++)
	{
		if(PotReg==0x10)  //change phase (FlucPot is phase)
		{

			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (FixPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;


			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xE0) | (FlucPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;	
		}

		else //change gain (FlucPot is gain)
		{
			
			R858_I2C.RegAddr = 16;
			R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (FlucPot & 0x1F); 
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;


			R858_I2C.RegAddr = 17;
			R858_Array[R858_Num][IntTunerNum][17] = (R858_Array[R858_Num][IntTunerNum][17] & 0xE0)  | (FixPot & 0x1F);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;	
		}

		if(R858_Muti_Read(R858_Num, IntTunerNum, &CorTemp[TreeCunt].Value) != RT_Success)
			return RT_Fail;
	

		if(PotReg == 0x10) //change phase
		{
			CorTemp[TreeCunt].Gain_X  = FixPot;
			CorTemp[TreeCunt].Phase_Y = FlucPot;
		}
		else  //change gain
		{
			CorTemp[TreeCunt].Phase_Y  = FixPot;
			CorTemp[TreeCunt].Gain_X = FlucPot;
		}
		
	




		if(TreeCunt == 0)   //next try right-side 1 point
			FlucPot ++;     //+1
		else if(TreeCunt == 1)   //next try right-side 2 point
			FlucPot ++;     //1+1=2
		else if(TreeCunt == 2)   //next try left-side 1 point
		{
			if((FlucPot & 0x0F) == 1) //if absolute location is 2, change I/Q direction and set to 1
			{
				TempPot = 1;
				if((FlucPot & 0x10)==0x10) //b[5]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;  //Q1
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;  //I1
				}
			}
			else
				FlucPot -= 3;  //+2-3=-1
		}
		else if(TreeCunt == 3) //next try left-side 2 point
		{
			if(TempPot==1)  //been chnaged I/Q
			{
				FlucPot += 1;
			}
			else if((FlucPot & 0x0F) == 0x00) //if absolute location is 0, change I/Q direction
			{
				TempPot = 1;
				if((FlucPot & 0x10)==0x10) //b[5]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;  //Q1
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;  //I1
				}
			}
			else
				FlucPot -= 1;  //-1-1=-2
		}

		if(CorTemp[TreeCunt].Value < Compare_Temp.Value)
		{
		  Compare_Temp.Value = CorTemp[TreeCunt].Value;
		  Compare_Temp.Gain_X = CorTemp[TreeCunt].Gain_X;
		  Compare_Temp.Phase_Y = CorTemp[TreeCunt].Phase_Y;		
		  CuntTemp = TreeCunt; 
		}

	}


	











	for(CompCunt=0; CompCunt<3; CompCunt++)
	{
		if(CuntTemp==3 || CuntTemp==4)
		{
			CompareTree[CompCunt].Gain_X = CorTemp[2+CompCunt].Gain_X;  //2,3,4
			CompareTree[CompCunt].Phase_Y = CorTemp[2+CompCunt].Phase_Y;
			CompareTree[CompCunt].Value = CorTemp[2+CompCunt].Value;
		}
		else
		{
			CompareTree[CompCunt].Gain_X = CorTemp[CompCunt].Gain_X;    //0,1,2
			CompareTree[CompCunt].Phase_Y = CorTemp[CompCunt].Phase_Y;
			CompareTree[CompCunt].Value = CorTemp[CompCunt].Value;
		}
		
	}

	return RT_Success;
}



//-----------------------------------------------------------------------------------/ 
// Purpose: compare IMC result aray [0][1][2], find min value and store to CorArry[0]
// input: CorArry: three IMR data array
// output: TRUE or FALSE
//-----------------------------------------------------------------------------------/
R858_ErrCode R858_CompreCor(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* CorArry)
{
	UINT8 CompCunt = 0;
	R858_SectType CorTemp;

	for(CompCunt = 3;CompCunt > 0;CompCunt --)
	{
		if(CorArry[0].Value > CorArry[CompCunt - 1].Value) //compare IMC result [0][1][2], find min value
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
R858_ErrCode R858_CompreStep(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* StepArry, UINT8 Pace)
{
	
	UINT8 Reg16 = R858_Array[R858_Num][IntTunerNum][16] & 0xE0;	
	UINT8 Reg17 = R858_Array[R858_Num][IntTunerNum][17] & 0xE0;	
	
	
	R858_SectType StepTemp;
	
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  



	//min value already saved in StepArry[0]
	StepTemp.Phase_Y = StepArry[0].Phase_Y;
	StepTemp.Gain_X  = StepArry[0].Gain_X;
	//StepTemp.Iqcap  = StepArry[0].Iqcap;

	while(((StepTemp.Gain_X & 0x0F) < R858_IMR_TRIAL) && ((StepTemp.Phase_Y & 0x0F) < R858_IMR_TRIAL))  
	{
		if(Pace == 0x10)	
		{
			StepTemp.Gain_X++;    //gain direction
		}
		else
			StepTemp.Phase_Y++;   //phase direction
	
		R858_I2C.RegAddr = 16;	
		R858_I2C.Data = Reg16 | (StepTemp.Gain_X & 0x0F);
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_I2C.RegAddr = 17;	
		R858_I2C.Data = Reg17 | (StepTemp.Phase_Y & 0x0F);
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
/*
		R858_I2C.RegAddr = 16;	
		R858_I2C.Data = StepTemp.Phase_Y;
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
*/
		if(R858_Muti_Read(R858_Num, IntTunerNum, &StepTemp.Value) != RT_Success)
			return RT_Fail;

		if(StepTemp.Value <= StepArry[0].Value)
		{
			StepArry[0].Gain_X  = StepTemp.Gain_X;
			StepArry[0].Phase_Y = StepTemp.Phase_Y;
			//StepArry[0].Iqcap = StepTemp.Iqcap;
			StepArry[0].Value   = StepTemp.Value;
		}
		else if((StepTemp.Value - 2*ADC_READ_COUNT) > StepArry[0].Value)
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
R858_ErrCode R858_Muti_Read(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8* IMR_Result_Data)
{
#if (ADC_MULTI_READ==3)
	UINT8 ReadCunt     = 0;
	UINT16 ReadAmount  = 0;
	UINT8 ReadMax = 0;
	UINT8 ReadMin = 255;
	UINT8 ReadData = 0;
	
    R858_Delay_MS(R858_Num, ADC_READ_DELAY);//2

	for(ReadCunt = 0; ReadCunt < (ADC_READ_COUNT+2); ReadCunt ++)
	{
		R858_I2C_Len.RegAddr = 0x00;
		R858_I2C_Len.Len = 5;              // read R4
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
		{
			I2C_Read_Len(R858_Num , &R858_I2C_Len);
		}

		ReadData = (R858_I2C_Len.Data[4] & 0x3F);
		
		ReadAmount = ReadAmount + (UINT16)ReadData;
		
		if(ReadData < ReadMin)
			ReadMin = ReadData;
		
        if(ReadData > ReadMax)
			ReadMax = ReadData;
	}
	*IMR_Result_Data = (UINT8) (ReadAmount - (UINT16)ReadMax - (UINT16)ReadMin);
#else
	R858_Delay_MS(R858_Num, ADC_READ_DELAY);//2

	R858_I2C_Len.RegAddr = 0;
	R858_I2C_Len.Len = 3;              // read R1
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	if(I2C_Read_Len(R858_Num, &R858_I2C_Len) != RT_Success)
	{
		I2C_Read_Len(R858_Num, &R858_I2C_Len);
	}
	*IMR_Result_Data = (R858_I2C_Len.Data[1] & 0xFC)>>2;
#endif

	return RT_Success;
}


R858_ErrCode R858_Section(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont)
{
	R858_SectType Compare_IQ[3];
	R858_SectType Compare_Bet[3];

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x1F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xDF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)  // y-direction
		return RT_Fail;		

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;	

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x1F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x20) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;		

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return RT_Success;
}


R858_ErrCode R858_IMR_Cross(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont, UINT8* X_Direct)
{

	R858_SectType Compare_Cross[9]; //(0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0)+(0,Q-2)(0,I-2)(Q-2,0)(I-2,0)
	R858_SectType Compare_Temp;
	UINT8 CrossCount = 0;
	UINT8 Reg16 = R858_Array[R858_Num][IntTunerNum][16] & 0xE0;	
	UINT8 Reg17 = R858_Array[R858_Num][IntTunerNum][17] & 0xE0;	

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	Compare_Temp.Gain_X = 0;
	Compare_Temp.Phase_Y = 0;
	Compare_Temp.Iqcap = 0;
	Compare_Temp.Value = 255;

	for(CrossCount=0; CrossCount<9; CrossCount++)
	{
/*
		if(CrossCount==0)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16;   //(0, 0)
		  Compare_Cross[CrossCount].Phase_Y = Reg17;
		}
		else if(CrossCount==1)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+(1<<4);   //(0, Q-1)
		  Compare_Cross[CrossCount].Phase_Y = Reg17;      
		}
		else if(CrossCount==2)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+(1<<4);   // (0, I-1)
		  Compare_Cross[CrossCount].Phase_Y = Reg17+(1<<1); 
		}
		else if(CrossCount==3)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+1;          //(Q-1, 0)
		  Compare_Cross[CrossCount].Phase_Y = Reg17;
		}
		else if(CrossCount==4)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+1;          //(I-1,0)
		  Compare_Cross[CrossCount].Phase_Y = Reg17+(1<<0);
		}
		else if(CrossCount==5)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+(2<<4);  //(0, Q-2)
		  Compare_Cross[CrossCount].Phase_Y = Reg17;  
		}
		else if(CrossCount==6)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+(2<<4);   //(0, I-2)
		  Compare_Cross[CrossCount].Phase_Y = Reg17+(1<<1); 
		}
		else if(CrossCount==7)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+2;        //(Q-2,0)
		  Compare_Cross[CrossCount].Phase_Y = Reg17;
		}
		else if(CrossCount==8)
		{
		  Compare_Cross[CrossCount].Gain_X = Reg16+2;        //(I-2,0)
		  Compare_Cross[CrossCount].Phase_Y = Reg17+(1<<0);
		}
*/
		if(CrossCount==0)
		{
		  Compare_Cross[CrossCount].Gain_X = 0;   //(0, 0)
		  Compare_Cross[CrossCount].Phase_Y = 0;
		}
		else if(CrossCount==1)
		{
		  Compare_Cross[CrossCount].Gain_X = 0;   //(0, Q-1)
		  Compare_Cross[CrossCount].Phase_Y = 1;      
		}
		else if(CrossCount==2)
		{
		  Compare_Cross[CrossCount].Gain_X = 0;   // (0, I-1)
		  Compare_Cross[CrossCount].Phase_Y = 1+(1<<4); 
		}
		else if(CrossCount==3)
		{
		  Compare_Cross[CrossCount].Gain_X = 1;          //(Q-1, 0)
		  Compare_Cross[CrossCount].Phase_Y = 0;
		}
		else if(CrossCount==4)
		{
		  Compare_Cross[CrossCount].Gain_X = 1+(1<<4);          //(I-1,0)
		  Compare_Cross[CrossCount].Phase_Y = 0;
		}
		else if(CrossCount==5)
		{
		  Compare_Cross[CrossCount].Gain_X = 0;  //(0, Q-2)
		  Compare_Cross[CrossCount].Phase_Y = 2;  
		}
		else if(CrossCount==6)
		{
		  Compare_Cross[CrossCount].Gain_X = 0;   //(0, I-2)
		  Compare_Cross[CrossCount].Phase_Y = 2+(1<<4); 
		}
		else if(CrossCount==7)
		{
		  Compare_Cross[CrossCount].Gain_X = 2;        //(Q-2,0)
		  Compare_Cross[CrossCount].Phase_Y = 0;
		}
		else if(CrossCount==8)
		{
		  Compare_Cross[CrossCount].Gain_X = 2+(1<<4);        //(I-2,0)
		  Compare_Cross[CrossCount].Phase_Y = 0;
		}


	   R858_I2C.RegAddr = 16;	
	   R858_I2C.Data = Reg16 | (Compare_Cross[CrossCount].Gain_X & 0x1F);
	   if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		   return RT_Fail;

	   R858_I2C.RegAddr = 17;	
	   R858_I2C.Data = Reg17 | (Compare_Cross[CrossCount].Phase_Y & 0x1F);
	   if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		   return RT_Fail;

       //R858_I2C.RegAddr = 16;	
	   //R858_I2C.Data = (Compare_Cross[CrossCount].Gain_X & 0x0F) | ((Compare_Cross[CrossCount].Phase_Y & 0x0F)<<4);
	   //if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		  // return RT_Fail;


	   // R858_I2C.RegAddr = 17;	
	   // R858_I2C.Data = Reg17 | ((Compare_Cross[CrossCount].Gain_X & 0x10)>>4) | ((Compare_Cross[CrossCount].Phase_Y & 0x10)>>3);
	   // if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		  //return RT_Fail;

		/*if(CrossCount == 0)
		{
			R858_Delay_MS(R858_Num, 5);//2
		}*/
	
        if(R858_Muti_Read(R858_Num, IntTunerNum, &Compare_Cross[CrossCount].Value) != RT_Success)
		  return RT_Fail;

		if( Compare_Cross[CrossCount].Value < Compare_Temp.Value)
		{
		  Compare_Temp.Value = Compare_Cross[CrossCount].Value;
		  Compare_Temp.Gain_X = Compare_Cross[CrossCount].Gain_X;
		  Compare_Temp.Phase_Y = Compare_Cross[CrossCount].Phase_Y;		
		}
	} //end for loop


    if(((Compare_Temp.Phase_Y & 0x1F)==0x01) || (Compare_Temp.Phase_Y & 0x1F)==0x02)  //phase Q1 or Q2
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
	else if(((Compare_Temp.Phase_Y & 0x1F)==0x11) || (Compare_Temp.Phase_Y & 0x1F)==0x12)  //phase I1 or I2
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
	else if(((Compare_Temp.Gain_X & 0x1F)==0x01) || (Compare_Temp.Gain_X & 0x1F)==0x02)  //gain Q1 or Q2
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
	else if(((Compare_Temp.Gain_X & 0x1F)==0x11) || (Compare_Temp.Gain_X & 0x1F)==0x12)  //gain I1 or I2
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
R858_ErrCode R858_F_IMR(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Pont)
{
	R858_SectType Compare_IQ[3];
	R858_SectType Compare_Bet[3];

	UINT8   ADC_Read_Value;
	UINT8   LPF_Count;

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	 //manual LPF gain
	 R858_I2C.RegAddr = 19;
	 R858_Array[R858_Num][IntTunerNum][19] = (R858_Array[R858_Num][IntTunerNum][19] & 0xFD);
	 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][19];  
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	 // increase LPF power to let image significant
	 for(LPF_Count=0; LPF_Count<16; LPF_Count++)  //start from 5 (??)
	 {
		R858_I2C.RegAddr = 37;
		R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0x0F) | (LPF_Count<<4);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];  
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, FILTER_GAIN_DELAY); //
		
		if(R858_Muti_Read(R858_Num, IntTunerNum, &ADC_Read_Value) != RT_Success)
			return RT_Fail;

		if(ADC_Read_Value > 40*ADC_READ_COUNT)
			break;
	 }

	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xEF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)  // y-direction
		return RT_Fail;	

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;	

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x10) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R858_IQ_Tree5(R858_Num, IntTunerNum, Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, 0x10, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;		

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_IQ[0]) != RT_Success)
		return RT_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R858_CompreCor(R858_Num, IntTunerNum, &Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	//clear IQ_Cap = 0
	Compare_Bet[0].Iqcap = 0;	

	if(R858_IMR_Iqcap(R858_Num, IntTunerNum, &Compare_Bet[0]) != RT_Success)
		return RT_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return RT_Success;
}


R858_ErrCode R858_IMR_Iqcap(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_SectType* IQ_Point)   
{
    R858_SectType Compare_Temp;
	int i = 0;

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];	  

	////Set Gain/Phase to right setting
	//R858_I2C.RegAddr = 16;	
	//R858_Array[R858_Num][IntTunerNum][16]=(IQ_Point->Gain_X & 0x0F) + ((IQ_Point->Phase_Y & 0x0F)<<4); 
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;

	//R858_I2C.RegAddr = 17;	// R17[5:0]  
	//R858_Array[R858_Num][IntTunerNum][17]=(R858_Array[R858_Num][IntTunerNum][17] & 0xFC) | ((IQ_Point->Gain_X & 0x10)>>4) | ((IQ_Point->Phase_Y & 0x10)>>3);
	//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;


	//Set Gain/Phase to right setting
	R858_I2C.RegAddr = 16;	
	R858_Array[R858_Num][IntTunerNum][16]=(R858_Array[R858_Num][IntTunerNum][16] & 0xE0) | (IQ_Point->Gain_X & 0x1F); 
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	R858_I2C.RegAddr = 17;	// R17[5:0]  
	R858_Array[R858_Num][IntTunerNum][17]=(R858_Array[R858_Num][IntTunerNum][17] & 0xE0) | (IQ_Point->Phase_Y & 0x1F);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][17];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	//try iqcap
	for(i=0; i<3; i++)	
	{
		Compare_Temp.Iqcap = (UINT8) i;  
		R858_I2C.RegAddr = 15;		// R15[2:1] 
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr ] & 0xF9) | (Compare_Temp.Iqcap<<1);  
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];  
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			   return RT_Fail;

		if(R858_Muti_Read(R858_Num, IntTunerNum, &(Compare_Temp.Value)) != RT_Success)
			   return RT_Fail;

		if(Compare_Temp.Value < IQ_Point->Value)
		{
			IQ_Point->Value = Compare_Temp.Value; 
			IQ_Point->Iqcap = Compare_Temp.Iqcap;
		}
	}

    return RT_Success;
}

R858_ErrCode R858_SetStandard(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Standard_Type RT_Standard)
{	 
	
	UINT8 u1FilCalGap = 16;
	UINT8 Enb_Pulse = 0x00;

	//Assign device address
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	if(RT_Standard != R858_pre_standard[R858_Num][IntTunerNum])
	{
		 if(R858_InitReg(R858_Num, IntTunerNum) != RT_Success)      
		     return RT_Fail;
	}
    R858_pre_standard[R858_Num][IntTunerNum] = RT_Standard;


    Sys_Info1 = R858_Sys_Sel(RT_Standard);


	// Filter Calibration	
	 u1FilCalGap = 16;

	//HPF ext protection

    if(R858_Fil_Cal_flag[R858_Num][IntTunerNum][RT_Standard] == FALSE)
	{
		R858_Fil_Cal_code[R858_Num][IntTunerNum][RT_Standard] = R858_Filt_Cal_ADC(R858_Num, IntTunerNum, Sys_Info1.FILT_CAL_IF, Sys_Info1.BW, u1FilCalGap);
		R858_Fil_Cal_BW[R858_Num][IntTunerNum][RT_Standard] = R858_Bandwidth[R858_Num][IntTunerNum];        
        R858_Fil_Cal_LpfLsb[R858_Num][IntTunerNum][RT_Standard] = R858_Lpf_Lsb[R858_Num][IntTunerNum];

		R858_Fil_Cal_flag[R858_Num][IntTunerNum][RT_Standard] = TRUE;

	    //Reset register and Array
	    if(R858_InitReg(R858_Num, IntTunerNum) != RT_Success)
		   return RT_Fail;
	}


	//if(RT_Standard == R858_DVB_C_8M_IF_5500 || RT_Standard== R858_DVB_C_8M_IF_5500)


	switch(RT_Standard)
	{
		case R858_DVB_C_8M:                            //Cable
		case R858_DVB_C_6M:
        case R858_DVB_C_8M_IF_5M:
		case R858_DVB_C_8M_IF_5500:
		case R858_DVB_C_6M_IF_5M:
		case R858_DVB_C_6M_IF_5500:

			Enb_Pulse = 0x02;
			break;
		default:

			Enb_Pulse = 0x00;
			break;

	}

	// Set Enb Pulse bit
	R858_I2C.RegAddr = 24;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | Enb_Pulse  ;  //R20[2]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;


	// Set LPF Lsb bit
	R858_I2C.RegAddr = 20;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFB) | (R858_Fil_Cal_LpfLsb[R858_Num][IntTunerNum][RT_Standard]<<2);  //R20[2]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	    return RT_Fail;

	// Set LPF fine code
	R858_I2C.RegAddr = 20;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x87) | (R858_Fil_Cal_code[R858_Num][IntTunerNum][RT_Standard]<<3);  //R20[6:3]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;  


	// Set LPF coarse BW
	R858_I2C.RegAddr = 16;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (R858_Fil_Cal_BW[R858_Num][IntTunerNum][RT_Standard]<<6);  //R16[7:6]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	//Set HPF notch  R18[7]
	R858_I2C.RegAddr = 18;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x7F) | (Sys_Info1.HPF_NOTCH<<7);  
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	if((RT_Standard == R858_J83B_IF_4300) && (IntTunerNum == R858_TUNER2))
	{
		Sys_Info1.HPF_COR = 8;
	}

	// Set HPF corner 
	R858_I2C.RegAddr = 18;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x87) | (Sys_Info1.HPF_COR<<3);	//R18[6:3]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	// Set Filter Auto Ext  
	R858_I2C.RegAddr = 19;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xBF) | (Sys_Info1.FILT_EXT_ENA<<6);  //R19[6]
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	

	// Set AGC clk R38[5:4]
	R858_I2C.RegAddr = 38;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | (Sys_Info1.AGC_CLK<<4);  
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	if(R858_Num == 1)
	{
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][R858_TUNER1][29] = (R858_Array[R858_Num][R858_TUNER1][29] & 0x06);  //R[7]=0  R[6:3] R[0] = 0
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][29];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	}
     

	return RT_Success;
}


UINT8  R858_Filt_Cal_ADC(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 IF_Freq, UINT8 R858_BW, UINT8 FilCal_Gap)
{
	 UINT8     u1FilterCodeResult = 0;
	 UINT8     u1FilterCode = 0;
	 UINT8     u1FilterCalValue = 0;
	 UINT8     u1FilterCalValuePre = 0;
	 UINT32    u4RingFreq = 68000;
	 UINT8     initial_cnt = 0;
	 UINT8     i = 0;
	 UINT8     ADC_Read_Value = 0;
	 UINT8     LPF_Count = 0;
	 //UINT32   RingVCO = 0;
	 //UINT32   RingRef = R858_Xtal;
	 //UINT8     divnum_ring = 0;

	 //R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];


	// if(IntTunerNum == 0)
	//{

 //      u4RingFreq = 68000;
	//}
	//else
	//{
 //      u4RingFreq = 72000;
	//}


	 if(R858_Cal_Prepare(R858_Num, IntTunerNum, R858_LPF_CAL) != RT_Success)      
		 return RT_Fail;


	 /*if(R858_Xtal == 16000)
	 {
		u4RingFreq = 66666;
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 50;
		R858_Array[R858_Num][R858_TUNER1][50] = (R858_Array[R858_Num][R858_TUNER1][50] & 0xD0) | 0x19; //on
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][50];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	 }*/



	if(IntTunerNum==R858_TUNER1)
	{
		////Select det2=tuner1 in Tuner1 R46[1]
		//R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		//R858_I2C.RegAddr = 46;
		//R858_Array[R858_Num][R858_TUNER1][46] = (R858_Array[R858_Num][R858_TUNER1][46] & 0xFD) | 0x00; //tuner1
		//R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][46];
		//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		//	return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner1 ON
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER1][14] = (R858_Array[R858_Num][R858_TUNER1][14] & 0xFD) | 0x02; //on
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner2 OFF
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER2];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER2][14] = (R858_Array[R858_Num][R858_TUNER2][14] & 0xFD) | 0x00; //off
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER2][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}
	else   //Tuner2
	{
		////Select det2=tuner2 in Tuner1 R46
		//R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		//R858_I2C.RegAddr = 46;
		//R858_Array[R858_Num][R858_TUNER1][46] = (R858_Array[R858_Num][R858_TUNER1][46] & 0xFD) | 0x02;  //tuner2
		//R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][46];
		//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		//	return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner1 Off
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER1][14] = (R858_Array[R858_Num][R858_TUNER1][14] & 0xFD) | 0x00; //off
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		//Set Ring to RFBuf in R14[1], Tuner2 On
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER2];
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][R858_TUNER2][14] = (R858_Array[R858_Num][R858_TUNER2][14] & 0xFD) | 0x02; //on
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER2][14];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}


	if(R858_Num == 1)
	{
		R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.RegAddr = 29;
		R858_Array[R858_Num][R858_TUNER1][29] = (R858_Array[R858_Num][R858_TUNER1][29] & 0x06);  //R[7]=0  R[6:3] R[0] = 0
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][29];
				if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	}


	R858_I2C.I2cAddr = R858_ADDRESS[R858_Num][IntTunerNum];
	


		
	 if(R858_PLL(R858_Num, IntTunerNum, (u4RingFreq - IF_Freq), R858_STD_SIZE) != RT_Success)   //FilCal PLL
	     return RT_Fail;

	 //manual LPF gain
	 R858_I2C.RegAddr = 19;
	 R858_Array[R858_Num][IntTunerNum][19] = (R858_Array[R858_Num][IntTunerNum][19] & 0xFD);
	 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][19];  
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	 ////Ring PLL pw on

	 // R858_I2C.RegAddr=49;
	 // R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	 // R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFD) ;
	 // R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	 // if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		// return RT_Fail;

  //  //Ring PLL pw off

	 //R858_I2C.RegAddr=49;
	 //R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	 //R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
	 //R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	 //if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		//return RT_Fail;

	 //for(int InitArrayCunt = 48; InitArrayCunt<R858_REG_NUM; InitArrayCunt ++)
	 //{
		//R858_I2C_Len.Data[InitArrayCunt-48] = R858_LPF_CAL_Array[R858_TUNER1][InitArrayCunt];
	 //}
	 //R858_I2C_Len.Data[49-48] = R858_I2C_Len.Data[49-48] & 0xFD;
	 //R858_I2C_Len.RegAddr = 48;
	 //R858_I2C_Len.Len = 8;
	 //R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	 //if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
		//return RT_Fail;




	 //print   R858_Array[R858_Num][R858_TUNER1][0] ~ R858_Array[R858_Num][R858_TUNER1][55]
	 //print   R858_Array[R858_Num][R858_TUNER2][0] ~ R858_Array[R858_Num][R858_TUNER2][55]

	 for(LPF_Count=0; LPF_Count<16; LPF_Count++)  //start from 5 (??)
	 {
		R858_I2C.RegAddr = 37;
		R858_Array[R858_Num][IntTunerNum][37] = (R858_Array[R858_Num][IntTunerNum][37] & 0x0F) | (LPF_Count<<4);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][37];  
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, FILTER_GAIN_DELAY); //
		
		if(R858_Muti_Read(R858_Num, IntTunerNum, &ADC_Read_Value) != RT_Success)
			return RT_Fail;

		if(ADC_Read_Value > 40*ADC_READ_COUNT)
			break;
	 }

     //Must do before PLL() 
	 //if(R858_MUX(IntTunerNum, u4RingFreq + IF_Freq, u4RingFreq, R858_STD_SIZE) != RT_Success)     //FilCal MUX (LO_Freq, RF_Freq)
	   //  return RT_Fail;

	 //Set PLL




	 //------- Try suitable BW --------//
	 if(R858_BW==2) //6M
         initial_cnt = 1;  //try 7M first
	 else
		 initial_cnt = 0;  //try 8M first

	 for(i=initial_cnt; i<3; i++)
	 {
         if(i==0)
             R858_Bandwidth[R858_Num][IntTunerNum] = 0; //8M
		 else if(i==1)
			 R858_Bandwidth[R858_Num][IntTunerNum] = 2; //7M
		 else
			 R858_Bandwidth[R858_Num][IntTunerNum] = 3; //6M

		 //Set BW R16[7:6]
		 R858_I2C.RegAddr = 16;	
	     R858_Array[R858_Num][IntTunerNum][16] = (R858_Array[R858_Num][IntTunerNum][16] & 0x3F) | (R858_Bandwidth[R858_Num][IntTunerNum]<<6);
         R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][16];		
         if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		      return RT_Fail;	

		 // read code 0 (4 MSB bits) R20[2]
		 R858_I2C.RegAddr = 20;
		 R858_Array[R858_Num][IntTunerNum][20] = (R858_Array[R858_Num][IntTunerNum][20] & 0x87) | (0<<3);  //code 0<<1
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][20];
		 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			  return RT_Fail;

		 R858_Delay_MS(R858_Num, FILTER_CODE_DELAY); //delay ms
	     
		 if(R858_Muti_Read(R858_Num, IntTunerNum, &u1FilterCalValuePre) != RT_Success)
			  return RT_Fail;

		 //read code 13*2 (4 MSB bits)
		 R858_I2C.RegAddr = 20;
		 R858_Array[R858_Num][IntTunerNum][20] = (R858_Array[R858_Num][IntTunerNum][20] & 0x87) | (13<<3);  //code 13<<1
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][20];
		 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			  return RT_Fail;

		 R858_Delay_MS(R858_Num, FILTER_CODE_DELAY); //delay ms
	     
		 if(R858_Muti_Read(R858_Num, IntTunerNum, &u1FilterCalValue) != RT_Success)
			  return RT_Fail;

		 if(u1FilterCalValuePre > (u1FilterCalValue+16))  //suitable BW found
			 break;
	 }

     //-------- Try LPF filter code ---------//
	 u1FilterCalValuePre = 0;
	 for(u1FilterCode=0; u1FilterCode<16; u1FilterCode++)
	 {
		 R858_I2C.RegAddr = 20;
		 R858_Array[R858_Num][IntTunerNum][20] = (R858_Array[R858_Num][IntTunerNum][20] & 0x87) | (u1FilterCode<<3);  //code<<1
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][20];
		 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			  return RT_Fail;

		 R858_Delay_MS(R858_Num, FILTER_CODE_DELAY); //delay ms

		 if(R858_Muti_Read(R858_Num, IntTunerNum, &u1FilterCalValue) != RT_Success)
		      return RT_Fail;

		 if(u1FilterCode==0)
              u1FilterCalValuePre = u1FilterCalValue;

		 if((u1FilterCalValue+FilCal_Gap*ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCode;
			  break;
		 }

	 }

     //Try LSB bit
	 if(u1FilterCodeResult>0)   //try code-1 & lsb=1
	 {		
		 R858_I2C.RegAddr = 20;
		 R858_Array[R858_Num][IntTunerNum][20] = (R858_Array[R858_Num][IntTunerNum][20] & 0x83) | ((u1FilterCodeResult-1)<<3) | (1<<2);  
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][20];
		 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			  return RT_Fail;

		 R858_Delay_MS(R858_Num, FILTER_CODE_DELAY); //delay ms

		 if(R858_Muti_Read(R858_Num, IntTunerNum, &u1FilterCalValue) != RT_Success)
			  return RT_Fail;

		 if((u1FilterCalValue+FilCal_Gap*ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCodeResult - 1;
			 R858_Lpf_Lsb[R858_Num][IntTunerNum] = 1;
		 }
		 else
		 {		 	 
			 R858_Lpf_Lsb[R858_Num][IntTunerNum] = 0;
		 }
	 }



     
	 if(u1FilterCode==16)
          u1FilterCodeResult = 15;

	  return u1FilterCodeResult;

}
R858_ErrCode R858_SetFrequency(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Set_Info R858_INFO)
{
	 UINT32	LO_KHz;
	 UINT8    Img_R;
	 UINT8 SetFreqArrayCunt;

	//Assign device address
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];


     // Check Input Frequency Range
	 if((R858_INFO.RF_KHz<40000) || (R858_INFO.RF_KHz>1002000))
	 {
	          return RT_Fail;
	 }

	 if(R858_Mixer_Mode==R858_IMR_REV)
	 {
		 LO_KHz = R858_INFO.RF_KHz - Sys_Info1.IF_KHz;
		 Img_R = 1;
	 }
	 else
	 {
		 LO_KHz = R858_INFO.RF_KHz + Sys_Info1.IF_KHz;
		 Img_R = 0;
	 }


	// lna current
	if((R858_INFO.RF_KHz>=330000) && (R858_INFO.RF_KHz<620000))
	{
        R858_I2C.RegAddr = 51;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | 0x00 );//highest
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
	}
	else
	{
		R858_I2C.RegAddr = 51;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | 0x40 );// low
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	}

	switch(R858_INFO.R858_Standard)
	{
	case R858_DVB_T_6M:
	case R858_DVB_T_7M:
	case R858_DVB_T_8M:
	case R858_DVB_T_6M_IF_5M:
	case R858_DVB_T_7M_IF_5M:
	case R858_DVB_T_7M_IF_5500:
	case R858_DVB_T_8M_IF_5M:
	case R858_DVB_T_8M_IF_5500:
	case R858_DVB_T2_6M:
	case R858_DVB_T2_7M: 
	case R858_DVB_T2_8M:
	case R858_DVB_T2_1_7M:
	case R858_DVB_T2_10M:
    case R858_DVB_T2_6M_IF_5M:
	case R858_DVB_T2_7M_IF_5M:
	case R858_DVB_T2_7M_IF_5500:
	case R858_DVB_T2_8M_IF_5M:
	case R858_DVB_T2_8M_IF_5500:
	case R858_DVB_T2_1_7M_IF_5M:
	case R858_ISDB_T_4063:	
	case R858_ISDB_T_4570:	
	case R858_ISDB_T_IF_5M:
	case R858_ATSC:
	case R858_ATSC_IF_5M:
	case R858_ATSC_IF_5500:

		//AGC  R48[5]  
		R858_I2C.RegAddr = 48;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | 0x20 );
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		break;

	default:

		 //AGC  R48[5]  
		R858_I2C.RegAddr = 48;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (SysFreq_Info1.AGC_CLK_CRTL<<5);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

		break;

	}
	  R858_I2C.RegAddr = 16;  //R16[5]
	  R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (Img_R<<5);  //R16[5]
	  R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	  if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		 return RT_Fail;

	  if(R858_Num == 1)
	  {
			R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			R858_I2C.RegAddr = 29;
			R858_Array[R858_Num][R858_TUNER1][29] = (R858_Array[R858_Num][R858_TUNER1][29] & 0x06);  //R[7]=0  R[6:3] R[0] = 0
			R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][29];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;

	  }

	  R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	 //Set MUX dependent var. Must do before PLL( ) 
     if(R858_MUX(R858_Num, IntTunerNum, LO_KHz, R858_INFO.RF_KHz, R858_INFO.R858_Standard) != RT_Success)   //normal MUX
        return RT_Fail;




	 R858_IF_GOLOBAL = Sys_Info1.IF_KHz;

     //Set PLL
     if(R858_PLL(R858_Num, IntTunerNum, LO_KHz, R858_INFO.R858_Standard) != RT_Success) //noraml PLL
        return RT_Fail;



     R858_IMR_point_num = Freq_Info1.IMR_MEM;

     //Get Sys-Freq parameter
     SysFreq_Info1 = R858_SysFreq_Sel(R858_INFO.R858_Standard, R858_INFO.RF_KHz);


	 LNA_VTH_ORIGINAL[R858_Num] = SysFreq_Info1.LNA_VTL_H & 0x0F;
	 LNA_VTL_ORIGINAL[R858_Num] = (SysFreq_Info1.LNA_VTL_H & 0xF0)>>4;
	 Filter_VTHL_ORIGINAL[R858_Num][IntTunerNum] = SysFreq_Info1.FILTER_VTL_H;
	 Mixer_VTHL_ORIGINAL[R858_Num][IntTunerNum] = SysFreq_Info1.MIXER_VTL_H;
	 RfBuffer_VTHL_ORIGINAL[R858_Num][IntTunerNum] =  SysFreq_Info1.RF_VTL_H;
	//LNA_NRB_DET R8[4]
	R858_I2C.RegAddr = 8;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) | (SysFreq_Info1.LNA_NRB_DET<<4);  
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/


	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	if(R858_SBY_flag[R858_Num][1-IntTunerNum]==1)//stnady recover
	{
		LNA_VTH[R858_Num] = LNA_VTH_ORIGINAL[R858_Num];
		LNA_VTL[R858_Num] = LNA_VTL_ORIGINAL[R858_Num];
		R858_LNA_VTHVTL_Change_flag[R858_Num]= 0 ;

	}
	else if(R858_LNA_VTHVTL_Change_flag[R858_Num]==0) //不需放寬
	{
		LNA_VTH[R858_Num] = SysFreq_Info1.LNA_VTL_H & 0x0F;
		LNA_VTL[R858_Num] = (SysFreq_Info1.LNA_VTL_H & 0xF0)>>4;
	}
	else 
	{

	}
	//LNA
	// LNA VTL/H R30[7:0]
	R858_I2C.RegAddr = 30;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | (LNA_VTL[R858_Num]<<4) | LNA_VTH[R858_Num];
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	
	//init myself
	if(R858_SBY_flag[R858_Num][1-IntTunerNum]==1)//stnady recover
	{
		R858_Orignial_RF_MIX_FILT_VHTL(R858_Num, IntTunerNum);
		R858_OTH_VTHVTL_Change_flag[R858_Num][IntTunerNum]=0;
	}
	else if(R858_OTH_VTHVTL_Change_flag[R858_Num][IntTunerNum]==0 && R858_OTH_VTHVTL_Change_flag[R858_Num][1-IntTunerNum]==0)	//原本
	{	
		// MIXER VTL / VTH R35[7:0]
		R858_I2C.RegAddr = 35;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | SysFreq_Info1.MIXER_VTL_H );

		// Filter VTL / VTH R37[7:0]
		R858_I2C.RegAddr = 37;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | SysFreq_Info1.FILTER_VTL_H);

		// RF VTL/H R31[7:0]
		R858_I2C.RegAddr = 31;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | SysFreq_Info1.RF_VTL_H;

	}
	else //no standby do nothing
	{

	}


	// RF_LTE_PSG R32[3] 
	R858_I2C.RegAddr = 32;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7) | (SysFreq_Info1.RF_LTE_PSG<<3);
	/*R858_I2C.Data = R858_Array[R858_Num][R858_I2C.RegAddr ];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/


	//RF
	// RF TOP R32[2:0]
	R858_I2C.RegAddr = 32;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | ((7 - SysFreq_Info1.RF_TOP));
	/*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;*/





	// RF Gain Limt  R13[6:5]
	R858_I2C.RegAddr = 13;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | (SysFreq_Info1.RF_GAIN_LIMIT<<5);
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//MIXER & FILTER
	//MIXER_AMP_CURRENT =>R10[1]
	R858_I2C.RegAddr = 10;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | (SysFreq_Info1.MIXER_AMP_CURRENT<<1);  
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//MIXER_AMP_LPF  R47[2:0]
	R858_I2C.RegAddr = 47;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | SysFreq_Info1.MIXER_AMP_LPF;  
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/
	
    // MIXER TOP R34[7:4]
	R858_I2C.RegAddr = 34;
    R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | ((15 - SysFreq_Info1.MIXER_TOP)<<4); 
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	// Filter TOP R36[7:4]
	R858_I2C.RegAddr = 36;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | ((15-SysFreq_Info1.FILTER_TOP)<<4);
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	// 3th_LPF_Gain R17[7:6]
	R858_I2C.RegAddr = 17;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (SysFreq_Info1.FILT_3TH_LPF_GAIN<<6);  
	R858_I2C.RegAddr = 19;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE) | (SysFreq_Info1.FILT_5TH_NCH);  

    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/





	// Mixer Gain Limt R46[7:6]
	R858_I2C.RegAddr = 46;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (SysFreq_Info1.MIXER_GAIN_LIMIT << 6);
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/
	if(SysFreq_Info1.LNA_RF_DIS_MODE==1)  //normal 
	{
	    R858_Array[R858_Num][IntTunerNum][53] = (R858_Array[R858_Num][IntTunerNum][53] & 0xDF) | 0x20;	//1
		R858_Array[R858_Num][IntTunerNum][55] = (R858_Array[R858_Num][IntTunerNum][55] & 0xED) ;        //00

	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==6)  //slow
	{
		R858_Array[R858_Num][IntTunerNum][53] = (R858_Array[R858_Num][IntTunerNum][53] & 0xDF) ;		//0
		R858_Array[R858_Num][IntTunerNum][55] = (R858_Array[R858_Num][IntTunerNum][55] & 0xED) | 0x12;  //11
		
	}
	else if(SysFreq_Info1.LNA_RF_DIS_MODE==7)  //Both (fast+slow)
	{
		R858_Array[R858_Num][IntTunerNum][53] = (R858_Array[R858_Num][IntTunerNum][53] & 0xDF) | 0x20;	//1
		R858_Array[R858_Num][IntTunerNum][55] = (R858_Array[R858_Num][IntTunerNum][55] & 0xED) | 0x12;  //11
		
	}
	else
	{
	 	R858_Array[R858_Num][IntTunerNum][53] = (R858_Array[R858_Num][IntTunerNum][53] & 0xDF) | 0x20;	//1
		R858_Array[R858_Num][IntTunerNum][55] = (R858_Array[R858_Num][IntTunerNum][55] & 0xED) | 0x12;  //11
		
	}
	R858_I2C.RegAddr = 55;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFB) | (SysFreq_Info1.LNA_RF_CHARGE_CUR<<2);  
	R858_I2C.RegAddr = 53;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
    return RT_Fail;

	R858_I2C.RegAddr = 55;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
    return RT_Fail;

	//BB disch current R40[0]
	R858_I2C.RegAddr = 40;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE) | (SysFreq_Info1.BB_DIS_CURR);  
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//Mixer/Filter disch  R39[7:6]
	R858_I2C.RegAddr = 39;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x3F) | (SysFreq_Info1.MIXER_FILTER_DIS<<6);  
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//BB Det Mode  R39[4]
	R858_I2C.RegAddr = 39;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) | (SysFreq_Info1.BB_DET_MODE<<4);  
		//Auto_speed  R39[1]   
	R858_I2C.RegAddr = 39;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | (SysFreq_Info1.AUTO_SPEED << 1);  
   /* R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//Polyphase
	//ENB_POLY_GAIN  R17[5]
	R858_I2C.RegAddr = 17;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (SysFreq_Info1.ENB_POLY_GAIN<<5));
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//NRB  
	// NRB TOP R33[3:0]
	R858_I2C.RegAddr = 33;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0) | ((15 - SysFreq_Info1.NRB_TOP));
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//NRB LPF & HPF BW  R33[7:6 & 5:4]
	R858_I2C.RegAddr = 33;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | (SysFreq_Info1.NRB_BW_HPF<<4) | (SysFreq_Info1.NRB_BW_LPF<<6);
   /* R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/

	//NBR Image TOP adder R34[2:1]
	R858_I2C.RegAddr = 34;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF9) | (SysFreq_Info1.IMG_NRB_ADDER<<1);  
    /*R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;*/


	//other setting

    //IF AGC1
	R858_I2C.RegAddr = 25;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF;
	

	//================================Tuner 1 only=============================

	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];

	//PW
	// Set NA det power R44[1]  
	R858_I2C.RegAddr = 51;
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x7F) | (SysFreq_Info1.NA_PWR_DET<<7);
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];


	R858_I2C.RegAddr = 51;
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xF8) | 0x07;
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];

	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	//RF slow disch(2:1) / fast disch(4:3) =>	R53[4:1]
	R858_I2C.RegAddr = 53;
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xE1) ;  
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xE1) | (SysFreq_Info1.RF_DIS_SLOW_FAST<<1); 
    R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];

    if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
       return RT_Fail;



	//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	//	return RT_Fail;

	//LNA 
	// LNA_TOP R45[2:0] ["7~0" (0~7) ; input: "7~0"] ; co-use ; tuner 1 control	
	R858_I2C.RegAddr = 54;
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x1F) | (((7 - SysFreq_Info1.LNA_TOP))<<5);
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	//Ring PLL pw off

	 R858_I2C.RegAddr=49;
	 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	 R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
	 R858_I2C.Data=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	 if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;



	 if(R858_INFO.R858_LT==LT_ON)  //active LT=O
	{
		R858_I2C.RegAddr = 51;
		R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFB) | 0x04;
	}
	else
	{
		R858_I2C.RegAddr = 51;
		R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xFB) | 0x00;

	}
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	/*
	//Tuner 1 Clock out must set "on" R29[6] =0
	R858_I2C.RegAddr = 29;
	R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = ((R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xBF));
	R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
*/
	//================================Tuner 2 only=============================
	/*
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER2];

    //user set Clk Out, Control by Tuner2 => always ON no matter use one R858 or two R858
	R858_I2C.RegAddr = 29;  // last tuner clk out can be set on/off by user, others set ON
	if(R858_INFO.R858_ClkOutMode==CLK_OUT_OFF)
	{
		R858_Array[R858_Num][R858_TUNER2][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER2][R858_I2C.RegAddr] | 0x40);   //no clk out  R29[6] = 1
	}
	else
	{
		R858_Array[R858_Num][R858_TUNER2][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER2][R858_I2C.RegAddr] & 0xBF);   //clk out  R29[6] = 0
	}
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
*/
//=============================Genernal Register====================================
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	//AGC  R48[5]  
	R858_I2C.RegAddr = 48;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xDF) | (SysFreq_Info1.AGC_CLK_CRTL<<5);
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
	return RT_Fail;

	
	R858_I2C_Len.RegAddr = 8;
	R858_I2C_Len.Len = 40;

	for(SetFreqArrayCunt = 0 ; SetFreqArrayCunt < 40 ; SetFreqArrayCunt ++)
	{
		R858_I2C_Len.Data[SetFreqArrayCunt] = R858_Array[R858_Num][IntTunerNum][SetFreqArrayCunt + 8];
	}
	if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
		return RT_Fail;





//R8[2]
//LDO bypass		550MHz~670MHz	R8[2]=1
//LDO 2.95v			other			R8[2]=0
/*
	R858_I2C.RegAddr = 8;
	if((R858_INFO.RF_KHz>=550000) && (R858_INFO.RF_KHz<670000))
	{
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x04;
	}
	else
	{
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFB;
	}
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
*/

	 return RT_Success;
}




R858_ErrCode R858_SetPllData(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Set_Info R858_INFO)
{

	
	if(R858_Initial_done_flag[R858_Num][IntTunerNum]==FALSE)
	{
		if(R858_Init(R858_Num, IntTunerNum) != RT_Success)
		return RT_Fail;
	}


	if(IntTunerNum==0)
	{
		if(R858_SetStandard(R858_Num, IntTunerNum, R858_INFO.R858_Standard) != RT_Success)
		{
		  return RT_Fail;
		}
	}
	else
	{
		if(R858_SetStandard(R858_Num, IntTunerNum, R858_INFO.R858_Standard_2) != RT_Success)
		{
		  return RT_Fail;
		}

	}


	if(R858_SetFrequency(R858_Num, IntTunerNum, R858_INFO) != RT_Success)
	{
	  return RT_Fail;
	}


      return RT_Success;
}


R858_ErrCode R858_Standby(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_LT_Type R858_LT)
{
	UINT8 i;

	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	if(R858_SBY_flag[R858_Num][IntTunerNum]==0)
	{
		for(i=8; i<R858_REG_NUM; i++)  //store R8~R55
		{
			R858_SBY[R858_Num][IntTunerNum][i]=R858_Array[R858_Num][IntTunerNum][i];
		}

		for(i=48; i<R858_REG_NUM; i++)  //store tuner1 R48~R55
		{
			R858_SBY2[R858_Num][i-48]=R858_Array[R858_Num][R858_TUNER1][i];
		}


		//LNA VTH/VTL
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];		
		if(R858_SBY_flag[R858_Num][1-IntTunerNum]==0) //W-S(S-W) to S-S
		{
			if(R858_LNA_VTHVTL_Change_flag[R858_Num]== 1) //do nothing
			{

			}
			else
			{
				//LNA VTH-2 / VTL+2  
				LNA_VTH[R858_Num] = LNA_VTH[R858_Num] + LNA_VTH_PARAMETER;
				R858_LNA_VTHVTL_Change_flag[R858_Num]= 1;
			}

		}
		else //W-W to S-W(W-S)
		{

				//VTH+2 / VTL-2
			LNA_VTH[R858_Num] = LNA_VTH_ORIGINAL[R858_Num];
			LNA_VTL[R858_Num] = LNA_VTL_ORIGINAL[R858_Num];
			R858_LNA_VTHVTL_Change_flag[R858_Num]= 0 ;
		}

		R858_I2C.RegAddr = 30;
		R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x00) | (LNA_VTL[R858_Num]<<4) | LNA_VTH[R858_Num];
		R858_SBY[R858_Num][R858_TUNER1][R858_I2C.RegAddr]=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Orignial_RF_MIX_FILT_VHTL(R858_Num, IntTunerNum);

		if(R858_SBY_flag[R858_Num][1-IntTunerNum]==0)
		{
			if(R858_OTH_VTHVTL_Change_flag[R858_Num][1-IntTunerNum]==0)
			{
				//需放寬
				R858_SetRF_MIX_FILT_VHTL(R858_Num, (R858_IntTunerNum_Type)(1-IntTunerNum), 1, RF_VTH_PARAMETER, 0);
				R858_SetMIX_FILT_VHTL(R858_Num, (R858_IntTunerNum_Type)(1-IntTunerNum), 1, MIX_FILT_VTH_PARAMETER, 0);
				R858_OTH_VTHVTL_Change_flag[R858_Num][1-IntTunerNum]=1;
			}
			else // do nothing
			{

			}

		}
		else // do nothing
		{

		}

		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		//R10
		R858_I2C.RegAddr = 10;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFF) | 0xFF;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		if(IntTunerNum ==1)
		{
			//R9[1]
			R858_I2C.RegAddr = 9;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//R9 off expect R9[3] R9[1]
		R858_I2C.RegAddr = 9;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0xF5) ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));


		//R8[5]rf Nrb Det  R8[4]lna Nrb Det  R8[2] RF Det off
		R858_I2C.RegAddr = 8;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x34) ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));


		//TF PW R13[4]
		R858_I2C.RegAddr = 13;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//VGA
		R858_I2C.RegAddr = 46;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE) | 0x01;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//PLL LDO div1
		R858_I2C.RegAddr = 26;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | 0x18;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));


		//PLL LDO div2
		R858_I2C.RegAddr = 14;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | 0x30;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
		
		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//PLL LDO D2
		R858_I2C.RegAddr = 25;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | 0x30;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		
		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//PLL LDO D1
		R858_I2C.RegAddr = 47;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | 0x60;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		
		R858_Delay_MS(R858_Num, (STBY_DELAY_MS/2));

		//R8[1] RF PW
		R858_I2C.RegAddr = 8;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, STBY_DELAY_MS);




		//PLL LDO A

				
		//R8[3] Mix PW
		R858_I2C.RegAddr = 8;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7) | 0x08 ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, STBY_DELAY_MS);

		




		////IQ gen, AGC, ADC
		//R858_I2C.RegAddr = 9;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF8) | 0x07;
		//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		//	return RT_Fail;

		//R858_Delay_MS(R858_Num, STBY_DELAY_MS);//2


	

		////ADC=VAGC
		//R858_I2C.RegAddr = 41;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFC) | 0x02;
		//R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		//if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		//	return RT_Fail;

		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];



		if(R858_Standby_Mode == R858_SBY_ALL)
		{
			//Set Internal Tuner 1
			R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];

			//LNA off, off LT, actLT off, LNA det off NAT off
			R858_I2C.RegAddr = 51;
			R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x70) | 0x08;
			R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		
		}

		R858_SBY_flag[R858_Num][IntTunerNum]=1;
	}

	return RT_Success;
}



R858_ErrCode R858_Wakeup(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{
	UINT8 i;


	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];	

	if(R858_SBY_flag[R858_Num][IntTunerNum]==1)
	{
		//LNA VTH/VTL
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];		
		if(R858_SBY_flag[R858_Num][1-IntTunerNum]==0)
		{
			if(R858_LNA_VTHVTL_Change_flag[R858_Num]== 1)// do nothing
			{
			}
			else
			{
				LNA_VTL[R858_Num] = LNA_VTL[R858_Num]-LNA_VTL_PARAMETER;
				R858_LNA_VTHVTL_Change_flag[R858_Num]= 1;
			}

		}
		else //另一路standby recover
		{
			LNA_VTH[R858_Num] = LNA_VTH_ORIGINAL[R858_Num];
			LNA_VTL[R858_Num] = LNA_VTL_ORIGINAL[R858_Num];
			R858_LNA_VTHVTL_Change_flag[R858_Num]= 0 ;
		}
		R858_I2C.RegAddr = 30;
		R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0x00) | (LNA_VTL[R858_Num]<<4) | LNA_VTH[R858_Num];
		R858_SBY[R858_Num][R858_TUNER1][R858_I2C.RegAddr]=R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
		R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;


		if(R858_SBY_flag[R858_Num][1-IntTunerNum]==0)
		{
			if(R858_OTH_VTHVTL_Change_flag[R858_Num][1-IntTunerNum]==0)// 須還原
			{
				R858_SetRF_MIX_FILT_VHTL(R858_Num, (R858_IntTunerNum_Type)(1-IntTunerNum), 0, 0, RF_VTL_PARAMETER);
				R858_SetMIX_FILT_VHTL(R858_Num, (R858_IntTunerNum_Type)(1-IntTunerNum), 0, 0, MIX_FILT_VTL_PARAMETER);
				R858_OTH_VTHVTL_Change_flag[R858_Num][1-IntTunerNum]=1;
			}
			else //do nothing
			{

			}
	
		}
		else // do nothing
		{

		}
		
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];




		//R8[3] Mix PW ON
		R858_I2C.RegAddr = 8;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7) | 0x08 ;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF7);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, WAKEUP_DELAY_MS);




		//R8[1] RF PW
		R858_I2C.RegAddr = 8;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | (R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x02) ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, WAKEUP_DELAY_MS);


		//PLL LDO D1
		R858_I2C.RegAddr = 47;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x9F) | (R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x60);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		
		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));



		//PLL LDO D2
		R858_I2C.RegAddr = 25;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | 0x30;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | (R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x30);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		
		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));


		//PLL LDO div2
		R858_I2C.RegAddr = 14;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | 0x30;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCF) | (R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x30);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;
		
		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));



		//PLL LDO div1
		R858_I2C.RegAddr = 26;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | 0x18;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xE7) | (R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x18);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));


		//VGA PW ON
		R858_I2C.RegAddr = 46;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE) | 0x01;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));


		//TF PW R13[4] = 1
		R858_I2C.RegAddr = 13;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xEF) ;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x10) ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));

		//R8[5]rf Nrb Det  R8[4]lna Nrb Det  R8[2] RF Det on
		R858_I2C.RegAddr = 8;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x34) ;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xCB) |0x30 ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;


		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));

		//R9 off expect R9[3] R9[1]
		R858_I2C.RegAddr = 9;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0xF5) ;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0A) | 0x04 ;
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

		R858_Delay_MS(R858_Num, (WAKEUP_DELAY_MS/2));

		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		if(IntTunerNum ==1)
		{
			//R9[1] = 0
			R858_I2C.RegAddr = 9;
			//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD) | 0x02 ;
			R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD);
			R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
			if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
				return RT_Fail;
		}

		//R10
		R858_I2C.RegAddr = 10;
		//R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFF) | 0xFF;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00);
		R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
		if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
			return RT_Fail;

	
		
		R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
		R858_I2C_Len.RegAddr = 8;
		R858_I2C_Len.Len = R858_REG_NUM-8;
		for(i = 8; i<R858_REG_NUM; i ++)  //write R8~R47
		{
			R858_I2C_Len.Data[i-8] = R858_SBY[R858_Num][IntTunerNum][i];
			R858_Array[R858_Num][IntTunerNum][i] = R858_SBY[R858_Num][IntTunerNum][i];
		}
		if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
			return RT_Fail;

		

		if(R858_Standby_Mode == R858_SBY_ALL)
		{
			//tuner1
			R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
			R858_I2C_Len.RegAddr = 48;
			R858_I2C_Len.Len = 8;
			for(i = 48; i<R858_REG_NUM; i ++)  //write R48~R55
			{
				R858_I2C_Len.Data[i-48] = R858_SBY2[R858_Num][i-48];
				R858_Array[R858_Num][R858_TUNER1][i] = R858_SBY2[R858_Num][i-48];
			}
			if(I2C_Write_Len(R858_Num, &R858_I2C_Len) != RT_Success)
				return RT_Fail;
		}

		R858_SBY_flag[R858_Num][IntTunerNum]=0;
	}
	return RT_Success;
}


//Shift_Type=0:Narrow , Shift_Type=1:Wide
R858_ErrCode R858_SetRF_MIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 Shift_Type, UINT8 Shift_Num, UINT8 Shift_Num1)
{
	UINT8 VTH_Temp;
	UINT8 VTL_Temp;

	//RF buf VTH R31[3:0] / VTL R31[7:4]
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.RegAddr = 31;
	if(Shift_Type==0)   //Narrow VTH - Shift_Num / VTL + Shift_Num
	{
		//VTH - Shift_Num / VTL + Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) - Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) - Shift_Num1;
	}
	else //Wide VTH + Shift_Num / VTL - Shift_Num
	{
		//VTH - Shift_Num    //VTL + Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) + Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) + Shift_Num1;
	}
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | (VTL_Temp<<4) | VTH_Temp;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
		return RT_Success;
}
R858_ErrCode R858_Orignial_RF_MIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum)
{
	
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	//RF buf VTH R31[3:0] / VTL R31[7:4]
	R858_I2C.RegAddr = 31;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | RfBuffer_VTHL_ORIGINAL[R858_Num][IntTunerNum];
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	//Mixer VTH R35[3:0] / VTL R35[7:4]
	R858_I2C.RegAddr = 35;
		R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | Mixer_VTHL_ORIGINAL[R858_Num][IntTunerNum];
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;


	//Filter VTH R37[3:0] / VTL R37[7:4]
	R858_I2C.RegAddr = 37;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) |  Filter_VTHL_ORIGINAL[R858_Num][IntTunerNum];
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	R858_OTH_VTHVTL_Change_flag[R858_Num][IntTunerNum]=0;

	return RT_Success;
}
R858_ErrCode R858_SetMIX_FILT_VHTL(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 Shift_Type, UINT8 Shift_Num, UINT8 Shift_Num1)
{
	UINT8 VTH_Temp;
	UINT8 VTL_Temp;

	//RF buf VTH R31[3:0] / VTL R31[7:4]
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C.RegAddr = 35;
	if(Shift_Type==0)   //Narrow VTH - Shift_Num / VTL + Shift_Num
	{
		//VTH - Shift_Num / VTL + Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) - Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) - Shift_Num1;
	}
	else //Wide VTH + Shift_Num / VTL - Shift_Num
	{
		//VTH + Shift_Num    //VTL - Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) + Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) + Shift_Num1;
	}
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | (VTL_Temp<<4) | VTH_Temp;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;



	//Filter VTH R37[3:0] / VTL R37[7:4]
	R858_I2C.RegAddr = 37;
	if(Shift_Type==0)   //Narrow VTH - Shift_Num / VTL + Shift_Num
	{
		//VTH - Shift_Num / VTL + Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) - Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) - Shift_Num1;
	}
	else //Wide VTH + Shift_Num / VTL - Shift_Num
	{
		//VTH + Shift_Num    //VTL - Shift_Num
		VTH_Temp = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) + Shift_Num;
		VTL_Temp = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xF0)>>4) + Shift_Num1;
	}
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x00) | (VTL_Temp<<4) | VTH_Temp;
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	R858_SBY[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}



R858_ErrCode R858_GetRfGain(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_RF_Gain_Info *pR858_rf_gain)
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

	//Assign device address
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];

	R858_I2C_Len.RegAddr = 0x00;
	R858_I2C_Len.Len = 5;  //xx

	if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
	{
		I2C_Read_Len(R858_Num , &R858_I2C_Len);
	}
	pR858_rf_gain->RF_gain1 = ((R858_I2C_Len.Data[4] & 0xF8)>>3);       //lna
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	R858_I2C_Len.RegAddr = 0x00;
	R858_I2C_Len.Len = 7;  //xx

	if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
	{
		I2C_Read_Len(R858_Num , &R858_I2C_Len);
	}

	pR858_rf_gain->RF_gain2 = (R858_I2C_Len.Data[5] & 0x0F);            //rf
	pR858_rf_gain->RF_gain3 = (R858_I2C_Len.Data[5] & 0xF0)>>4;       //mixer
	pR858_rf_gain->RF_gain4 = (R858_I2C_Len.Data[6] & 0x0F);             //filter
/*
	if(pR858_rf_gain->RF_gain1 > 24) 
        pR858_rf_gain->RF_gain1 = 24;  

	//Mixer Amp Gain
	if(pR858_rf_gain->RF_gain3 > 10)
        pR858_rf_gain->RF_gain3 = 10;  //MixerAmp gain max is 10	
	
	pR858_rf_gain->RF_gain_comb = (acc_lna_gain[pR858_rf_gain->RF_gain1] + acc_rfbuf_gain + pR858_rf_gain->RF_gain3*12);
*/
	pR858_rf_gain->RF_gain_comb = acc_lna_gain[pR858_rf_gain->RF_gain1]
		                        + acc_rf_gain[pR858_rf_gain->RF_gain2]
		                        + acc_mixer_gain[pR858_rf_gain->RF_gain3]
								+ pR858_rf_gain->RF_gain4*14;

    return RT_Success;
}


R858_ErrCode R858_RfGainMode(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_RF_Gain_TYPE R858_RfGainType)
{
    UINT8 MixerGain = 0;
	UINT8 RfGain = 0;
	UINT8 LnaGain = 0;
	UINT8 FilterGain = 0;

	//Assign device address
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	if(R858_RfGainType==RF_MANUAL)
	{
		//LNA auto off
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	     R858_I2C.RegAddr = 46;
	     R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] | 0x40;   // R46[6] = 1   co-use control by tuner 1
		 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][5];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		 //Mixer buffer off
	     R858_I2C.RegAddr = 13;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x01;  // R13[0]  = 1 
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][26];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer gain auto off
	     R858_I2C.RegAddr = 15;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE;  //R15[0] = 0
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		//Filter gain auto off
	     R858_I2C.RegAddr = 19;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFD;  //R19[1] = 0
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		R858_I2C_Len.RegAddr = 0x00;
		R858_I2C_Len.Len = 4; 
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
		{
			I2C_Read_Len(R858_Num , &R858_I2C_Len);
		}

		LnaGain = ((R858_I2C_Len.Data[1] & 0xF8) >>3);  //lna    // R1[7:3]  
		MixerGain = ((R858_I2C_Len.Data[2] & 0xF0) >> 4); //mixer // R2[7:4]
		RfGain = (R858_I2C_Len.Data[2] & 0x0F);   //rf		 // R2[3:0] 
		FilterGain = (R858_I2C_Len.Data[3] & 0x0F);   //filter		 // R3[3:0] 


		//set LNA gain
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	     R858_I2C.RegAddr = 43;
	     R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = (R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xE0) | LnaGain;  // R43[4:0]  
		 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		 //set Mixer Buffer gain
	     R858_I2C.RegAddr = 31;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | (RfGain << 4));  //R31[7:4] 
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		 //set Mixer gain
	     R858_I2C.RegAddr = 35;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | (MixerGain << 4)); // R35[7:4]  
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		//set Filter gain
	     R858_I2C.RegAddr = 37;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = ((R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0x0F) | (FilterGain << 4)); // R37[7:4]  
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;
	}
	else
	{
	    //LNA auto on
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];
	     R858_I2C.RegAddr = 46;
	     R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] = R858_Array[R858_Num][R858_TUNER1][R858_I2C.RegAddr] & 0xBF;   // R46[6] = 0   co-use control by tuner 1
		 R858_I2C.Data = R858_Array[R858_Num][R858_TUNER1][5];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;
		 R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

		 //Mixer buffer on
	     R858_I2C.RegAddr = 13;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] & 0xFE;  // R13[0]  = 0
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][26];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		 //Mixer gain auto on
	     R858_I2C.RegAddr = 15;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x01;  //R15[0] = 1
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;

		 //Filter gain auto on
		 R858_I2C.RegAddr = 19;
	     R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] | 0x02;  //R19[1] = 1
		 R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	     if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		       return RT_Fail;
	}

    return RT_Success;
}


//----------------------------------------------------------------------//
//  R858_SetXtalCap( ): Set R858 Internal Xtal Cap                //
//  1st parameter: Xtal Cap value; range 0~41(pF)                    //
//-----------------------------------------------------------------------//
R858_ErrCode R858_SetXtalCap(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 u8XtalCap)
{
	UINT8 XtalCap;
	UINT8 Capx;
	UINT8 Capx_3_0, Capxx;

	//Assign device address
	R858_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

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
		
	// Set Xtal Cap  R28[6:3], R29[0]     XtalCap => R28[7]
	R858_I2C.RegAddr = 28;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr ] & 0x07) | (Capx_3_0 << 3) | ( XtalCap << 7);  
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;
	R858_I2C.RegAddr = 29;
	R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr ] & 0xFE) | Capxx;  
	R858_I2C.Data = R858_Array[R858_Num][IntTunerNum][R858_I2C.RegAddr];
	if(I2C_Write(R858_Num, &R858_I2C) != RT_Success)
		return RT_Fail;

	return RT_Success;
}
//----------------------------------------------------------------------//
//  R858_GetRfRssi( ): Get RF RSSI                                      //
//  1st parameter: input RF Freq    (KHz)                                //
//  2nd parameter: input Standard                                           //
//  3rd parameter: output signal level (dBm*1000)                    //
//  4th parameter: output RF max gain indicator (1:max gain)    //
//-----------------------------------------------------------------------//
//R858_ErrCode R858_GetRfRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 RF_Freq_Khz, R858_Standard_Type RT_Standard, INT32 *RfLevelDbm, UINT8 *fgRfMaxGain)
R858_ErrCode R858_GetRfRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 RF_Freq_Khz, INT32 *RfLevelDbm, UINT8 *fgRfMaxGain)
{ 	
	//UINT8 bPulseFlag;
	R858_RF_Gain_Info rf_gain_info;
	UINT16  acc_lna_gain;
	UINT16  acc_rfbuf_gain;
	UINT16  acc_mixer_gain;
	UINT16  rf_total_gain;
	UINT8   u1FreqIndex;
	INT16  u2FreqFactor=0;
	UINT8  u1LnaGainqFactorIdx;
	INT32     rf_rssi;
	INT32    fine_tune = 0;    //for find tune 
	INT8 R858_Start_Gain_Cal_By_Freq[10] = {15, 20, -33, 42, 35, 48, 35, 43, 25, 25};
//	UINT8 	rf_limit;

		//{50~135, 135~215, 215~265, 265~315, 315~325, 325~345, 345~950}

	//Assign device address
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][R858_TUNER1];

	R858_I2C_Len.RegAddr = 0x00;
	R858_I2C_Len.Len = 5;
	if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
	{
		I2C_Read_Len(R858_Num , &R858_I2C_Len);
	}
	rf_gain_info.RF_gain1 = ((R858_I2C_Len.Data[4] & 0xF8)>>3);       //lna
	R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

	R858_I2C_Len.RegAddr = 0x00;
	R858_I2C_Len.Len = 7;
	if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success)
	{
		I2C_Read_Len(R858_Num , &R858_I2C_Len);
	}
	
	//bPulseFlag = ((R858_I2C_Len.Data[1] & 0x40) >> 6);


	rf_gain_info.RF_gain2 = (R858_I2C_Len.Data[5] & 0x0F);            //rf
	rf_gain_info.RF_gain3 = (R858_I2C_Len.Data[5] & 0xF0)>>4;       //mixer
	rf_gain_info.RF_gain4 = (R858_I2C_Len.Data[6] & 0x0F);             //filter

/*
	//max RF buffer
	rf_limit = (((R858_Array[R858_Num][18]&0x04)>>1) + ((R858_Array[R858_Num][16]&0x40)>>6));
	if(rf_limit==0)
		rf_gain_info.RF_gain2 = 15;
	else if(rf_limit==1)
		rf_gain_info.RF_gain2 = 11;
	else if(rf_limit==2)
		rf_gain_info.RF_gain2 = 13;
	else
		rf_gain_info.RF_gain2 = 9;


	//max Mixer		
	if((R858_Array[R858_Num][22]&0xC0)==0x00)
		rf_gain_info.RF_gain3 = 6;
	else if((R858_Array[R858_Num][22]&0xC0)==0x40)
		rf_gain_info.RF_gain3 = 8;
	else if((R858_Array[R858_Num][22]&0xC0)==0x80)
		rf_gain_info.RF_gain3 = 10;
	else
		rf_gain_info.RF_gain3 = 12;
*/

	//Limit LNA, MixerAmp max gain
	if(rf_gain_info.RF_gain3 > 12)
        rf_gain_info.RF_gain3 = 12; 


   //max gain indicator
	if((rf_gain_info.RF_gain1==31) && (rf_gain_info.RF_gain2==15) && (rf_gain_info.RF_gain3==12) && (rf_gain_info.RF_gain4==15))  
		*fgRfMaxGain = 1;
	else
		*fgRfMaxGain = 0;

/*
//TF_HPF_Corner
if((LO_freq>0) && (LO_freq<480000))  
     R858_Freq_Info.TF_HPF_CNR = 3;   //lowest	=> R16[4:3]
else if((LO_freq>=480000) && (LO_freq<550000))  
     R858_Freq_Info.TF_HPF_CNR = 2;   // low	=> R16[4:3]
else if((LO_freq>=550000) && (LO_freq<700000))  
	 R858_Freq_Info.TF_HPF_CNR = 1;   // high    => R16[4:3]
else
	 R858_Freq_Info.TF_HPF_CNR = 0;   //highest	=> R16[4:3]
*/
/*
<230 => u1FreqIndex = 0
230~420 => u1FreqIndex = 1
420~710 => u1FreqIndex = 2
>710 => u1FreqIndex = 3
*/

/*
		//RF polyfilter band
	if((LO_freq>0) && (LO_freq<133000))  
         R858_Freq_Info.RF_POLY = 2;   //R17[6:5]=2; low	=> R18[1:0]
	else if((LO_freq>=133000) && (LO_freq<221000))  
         R858_Freq_Info.RF_POLY = 1;   //R17[6:5]=1; mid	=> R18[1:0]
	else if((LO_freq>=221000) && (LO_freq<789000))  
		 R858_Freq_Info.RF_POLY = 0;   //R17[6:5]=0; highest    => R18[1:0]
	else
		 R858_Freq_Info.RF_POLY = 3;   //R17[6:5]=3; ultra high	=> R18[1:0]
*/

/*
Freq	SFC-U Start		RFGain Start									RF RSSI show value	(dBm)		SFC-U Start - RF RSSI show value (dBm)
50			 0dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							+1
100			-1dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							0
130			-1dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							0

140			-2dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-1
150			-3dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-2
200			-3dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-2
210			-4dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-3
	
220			-5dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-4
230			-7dB		lna=0    rf=0	 mixer = 2->5  filter = 0		0 -> -2							-5
240			-7dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-6
250			-6dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-5
260			-5dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-4

270			-4dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-3
280			-4dB		lna=0    rf=0	 mixer = 2->5  filter = 0		0 -> -2							-2
290			-3dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-2
300			-3dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-2
310			-3dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							-2

320			-1dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							0
330			+1dB		lna=0    rf=0	 mixer = 2->4  filter = 0		0 -> -1							+2
340			-1dB		lna=0    rf=0	 mixer = 5->6  filter = 0		-2 -> -3						+2

350			+1dB		lna=0    rf=0	 mixer = 7->8  filter = 0		-4 -> -5						+6
400			+0dB		lna=0    rf=0	 mixer = 6->7  filter = 0		-3 -> -4						+4
450			+1dB		lna=0    rf=0	 mixer = 4->5  filter = 0		-1 -> -2						+3
500			+0dB		lna=0    rf=0	 mixer = 7->8  filter = 0		-4 -> -5						+5
550			+0dB		lna=0    rf=0	 mixer = 6->7  filter = 0		-3 -> -4						+4
600			+1dB		lna=0    rf=0	 mixer = 6->7  filter = 0		-3 -> -4						+5
650			+1dB		lna=0    rf=0	 mixer = 5->6  filter = 0		-2 -> -3						+4

700			+0dB		lna=0    rf=0	 mixer = 4->5  filter = 0		-1 -> -2						+2
750			+1dB		lna=0    rf=0	 mixer = 6->7  filter = 0	    -3 -> -4						+5	
800			+1dB		lna=0    rf=0	 mixer = 5->6  filter = 0		-2 -> -3						+4
850			+0dB		lna=0    rf=0	 mixer = 4->5  filter = 0		-1 -> -2						+2
900			+1dB		lna=0    rf=0	 mixer = 5->6  filter = 0		-2 -> -3						+4
950			+1dB		lna=0    rf=0	 mixer = 5->6  filter = 0		-2 -> -3						+4

Result
INT8 R858_Start_Gain_By_Freq[7] = {0,      -20,     -50,     -20,     0,       20,      40};
								  {50~135, 135~215, 215~265, 265~315, 315~325, 325~345, 345~950}
*/

//coarse adjustment
if(RF_Freq_Khz<100000)   //0~100M
	{
		u1FreqIndex = 0;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[0];
	}
	else if((RF_Freq_Khz>=100000)&&(RF_Freq_Khz<200000))   //100~200M
	{
		u1FreqIndex = 0;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[1];
	}
	else if((RF_Freq_Khz>=200000)&&(RF_Freq_Khz<300000))   //200~300M
	{
		u1FreqIndex = 1;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[2];
	}
	else if((RF_Freq_Khz>=300000)&&(RF_Freq_Khz<400000))   //300~400M
	{
		u1FreqIndex = 1;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[3];
	}
	else if((RF_Freq_Khz>=400000)&&(RF_Freq_Khz<500000))   //400~500M
	{
		u1FreqIndex = 2;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[4];
	}
	else if((RF_Freq_Khz>=500000)&&(RF_Freq_Khz<600000))   //500~600M
	{
		u1FreqIndex = 2;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[5];
	}
	else if((RF_Freq_Khz>=600000)&&(RF_Freq_Khz<700000))   //600~700M
	{
		u1FreqIndex = 2;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[6];
	}
	else if((RF_Freq_Khz>=700000)&&(RF_Freq_Khz<800000))   //700~800M
	{
		u1FreqIndex = 3;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[7];

	}
	else if((RF_Freq_Khz>=800000)&&(RF_Freq_Khz<900000))   //800~900M
	{
		u1FreqIndex = 3;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[8];
	}
	else    // >=710
	{
		u1FreqIndex = 3;
		u2FreqFactor = R858_Start_Gain_Cal_By_Freq[9];
	}


	//LNA Gain
	acc_lna_gain = R858_Lna_Acc_Gain[u1FreqIndex][rf_gain_info.RF_gain1];



//fine adjustment
	//Cal LNA Gain	by Freq 
//Method 2 : All frequencies are finely adjusted..				
	if(rf_gain_info.RF_gain1 >= 10)
	{
		u1LnaGainqFactorIdx = (UINT8) ((RF_Freq_Khz-50000) / 10000);

		if( ((RF_Freq_Khz-50000)  - (u1LnaGainqFactorIdx * 10000))>=5000)
			u1LnaGainqFactorIdx +=1;

		acc_lna_gain = acc_lna_gain + (UINT16)(Lna_Acc_Gain_offset[u1LnaGainqFactorIdx]);

	}

	//RF buf
	acc_rfbuf_gain = R858_Rf_Acc_Gain[rf_gain_info.RF_gain2];
	if(RF_Freq_Khz<=300000)
		acc_rfbuf_gain += (rf_gain_info.RF_gain2 * 1);
	else if (RF_Freq_Khz>=600000)
		acc_rfbuf_gain -= (rf_gain_info.RF_gain2 * 1);

	//Mixer 
	acc_mixer_gain = R858_Mixer_Acc_Gain [rf_gain_info.RF_gain3]  ;

	//Add Rf Buf and Mixer Gain
	rf_total_gain = acc_lna_gain + acc_rfbuf_gain + acc_mixer_gain + rf_gain_info.RF_gain4*15;

	rf_rssi = fine_tune - (INT32) (rf_total_gain - u2FreqFactor);

	*RfLevelDbm = rf_rssi*100;

    return RT_Success;
}

//-----------------------------------------------------------------------//
//  R858_GetIfRssi( ): Get IF VGA GAIN                                   //
//  1st parameter: return IF VGA Gain     (dB*100)                       //
//-----------------------------------------------------------------------//
R858_ErrCode R858_GetIfRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, INT32 *VgaGain)
{
	UINT8   adc_read;
    I2C_TYPE          Dlg_I2C;
	UINT16   vga_table[64] = {                        //*100
		0, 10, 20, 40, 50, 80, 110, 120, 170, 210, 230, 290,   //0~11
		320, 370, 410, 460, 530, 560, 600, 640, 660, 720,   //12~21
		760, 790, 830, 860, 870, 900, 920, 950, 970, 1000,   //22~31
		1030, 1050, 1060, 1090, 1100, 1130, 1150, 1170, 1180, 1200,   //32~41
		1220, 1230, 1240, 1270, 1280, 1300, 1310, 1320, 1330, 1360,   //42~51
		1370, 1390, 1400, 1420, 1450, 1460, 1490, 1550, 1560, 1560,   //52~61
		1560, 1560   
	};


	//Assign device address
	Dlg_I2C.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];

//original value
/*	UINT16   vga_table[64] = {                        //100
		0, 0, 20, 20, 30, 50, 60, 70, 110, 130, 130, 160,   //0~11
		190, 250, 280, 330, 380, 410, 430, 480, 510, 620,   //12~21
		640, 710, 730, 770, 770, 810, 830, 900, 930, 940,   //22~31
		990, 1010, 1010, 1030, 1060, 1100, 1120, 1140, 1170, 1180,   //32~41
		1190, 1210, 1220, 1260, 1270, 1300, 1320, 1320, 1340, 1340,   //42~51
		1360, 1390, 1400, 1420, 1440, 1450, 1460, 1480, 1490, 1510,   //52~61
		1520, 1600            //62~63
	};
*/
//Optimize value

	//ADC sel : vagc, 41[1:0]=2
	Dlg_I2C.RegAddr = 41;
	R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] = (R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] & 0xFC) | 0x02;
	Dlg_I2C.Data = R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr];
	if(I2C_Write(R858_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//IF_AGC read, R41[3]=1
	Dlg_I2C.RegAddr = 41;
	R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] | 0x08;
	Dlg_I2C.Data = R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr];
	if(I2C_Write(R858_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//ADC power on, R9[2]=0
	Dlg_I2C.RegAddr = 9;
	R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] = R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr] & 0xFD;
	Dlg_I2C.Data = R858_Array[R858_Num][IntTunerNum][Dlg_I2C.RegAddr];
	if(I2C_Write(R858_Num, &Dlg_I2C) != RT_Success)
		return RT_Fail;

	//read adc value
		R858_I2C_Len.I2cAddr=R858_ADDRESS[R858_Num][IntTunerNum];
	R858_I2C_Len.RegAddr = 0x00;
	R858_I2C_Len.Len = 4;
	if(I2C_Read_Len(R858_Num , &R858_I2C_Len) != RT_Success) // read data length
	{
		I2C_Read_Len(R858_Num , &R858_I2C_Len);
	}
	adc_read = (R858_I2C_Len.Data[1] & 0xFC)>>2;

	*VgaGain = vga_table[adc_read];

	return RT_Success;
}

//----------------------------------------------------------------------//
//  R858_GetRfRssi( ): Get RF RSSI                                      //
//  1st parameter: input RF Freq    (KHz)                                //
//  2nd parameter: input Standard                                           //
//  3rd parameter: return signal level indicator (dBm)               //
//-----------------------------------------------------------------------//
R858_ErrCode R858_GetTotalRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 RF_Freq_Khz, INT32 *RssiDbm)
{
	INT32   rf_rssi;
	INT32   if_rssi;
	INT32   rem, total_rssi;
	INT32   ssi_offset = 0;   //need to fine tune by platform
	INT32   total_rssi_dbm;
	UINT8  rf_max_gain_flag;

	R858_GetRfRssi(R858_Num, IntTunerNum, RF_Freq_Khz, &rf_rssi, &rf_max_gain_flag);

	R858_GetIfRssi(R858_Num, IntTunerNum, &if_rssi);  //vga gain        

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

R858_Standard_Type aStandard[R858_MAX_NUM][R858_MAX_TUNER] = {{0}};

HI_S32 r858_init_tuner(HI_U32 u32TunerPort)
{
    R858_Set_Info R858_Info_Msg;
    R858_Standard_Type R858_Standard;


    R858_ExtTunerNum = u32TunerPort / R858_MAX_TUNER;
    R858_IntTunerNum = u32TunerPort % R858_MAX_TUNER;

    R858_Initial_done_flag[R858_ExtTunerNum][R858_IntTunerNum]= FALSE;
    R858_IMR_done_flag[R858_ExtTunerNum][R858_IntTunerNum]= FALSE;

    R858_I2C_SetPort(u32TunerPort);

    switch (g_stTunerOps[u32TunerPort].enSigType)
    {
        case HI_UNF_TUNER_SIG_TYPE_J83B:
            if (R858_IntTunerNum == R858_TUNER1)
                R858_Standard = R858_J83B_IF_5M;
            else
                R858_Standard = R858_J83B_IF_5500;
            break;
        case HI_UNF_TUNER_SIG_TYPE_CAB:
            if (R858_IntTunerNum == R858_TUNER1)
                R858_Standard = R858_DVB_C_8M_IF_5M;
            else
                R858_Standard = R858_DVB_C_8M_IF_5500;
            break;
        case HI_UNF_TUNER_SIG_TYPE_DVB_T:
            R858_Standard = R858_DVB_T_8M_IF_5M;
            break;
        case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
            R858_Standard = R858_DVB_T2_8M_IF_5M;
            break;
        default:
            HI_ERR_TUNER("Unsupported Signal_type %d.\n", g_stTunerOps[u32TunerPort].enSigType);
            return HI_FAILURE;
    }
    aStandard[R858_ExtTunerNum][R858_IntTunerNum] = R858_Standard;

    if (R858_IntTunerNum == R858_TUNER2)
    {
        R858_Info_Msg.R858_Standard = aStandard[R858_ExtTunerNum][R858_IntTunerNum - 1];
        R858_Info_Msg.R858_Standard_2 = aStandard[R858_ExtTunerNum][R858_IntTunerNum];

        if(R858_Init_ALL(R858_ExtTunerNum, R858_Info_Msg) != RT_Success)
        {
            HI_ERR_TUNER("Init r858 failed: port %d.\n", u32TunerPort);
            return HI_FAILURE;
        }
    }
		
    return HI_SUCCESS;
}

static HI_S32 r858_set_standard(HI_U32 u32TunerPort, R858_Set_Info *pR858_Info_Msg)
{
    R858_Standard_Type R858_Standard;
    
    R858_ExtTunerNum = u32TunerPort / R858_MAX_TUNER;
    R858_IntTunerNum = u32TunerPort % R858_MAX_TUNER;

    if (g_stTunerOps[u32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_J83B)
    {
        if (R858_IntTunerNum == R858_TUNER1)
            R858_Standard = R858_J83B_IF_5M;
        else
            R858_Standard = R858_J83B_IF_5500;
    }
    else if (g_stTunerOps[u32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_CAB)
    {
        if (R858_IntTunerNum == R858_TUNER1)
            R858_Standard = R858_DVB_C_8M_IF_5M;
        else
            R858_Standard = R858_DVB_C_8M_IF_5500;
    }
    else if (g_stTunerOps[u32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_DVB_T)
    {
        if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 8000)
        {
            R858_Standard = R858_DVB_T_8M_IF_5M;
        }
        else if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 7000)
        {
            R858_Standard = R858_DVB_T_7M_IF_5M;
        }
        else if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 6000)
        {
            R858_Standard = R858_DVB_T_6M_IF_5M;
        }
        else
        {
            HI_ERR_TUNER("Unsupported T bandwidth %d, port %d.\n", g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth, u32TunerPort);
            return HI_FAILURE;
        }
    }
    else if (g_stTunerOps[u32TunerPort].enSigType == HI_UNF_TUNER_SIG_TYPE_DVB_T2)
    {
        if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 8000)
        {
            R858_Standard = R858_DVB_T2_8M_IF_5M;
        }
        else if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 7000)
        {
            R858_Standard = R858_DVB_T2_7M_IF_5M;
        }
        else if (g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth == 6000)
        {
            R858_Standard = R858_DVB_T2_6M_IF_5M;
        }
        else
        {
            HI_ERR_TUNER("Unsupported T2 bandwidth %d, port %d.\n", g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth, u32TunerPort);
            return HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_TUNER("Unsupported Signal_type %d.\n", g_stTunerOps[u32TunerPort].enSigType);
        return HI_FAILURE;
    }
    
    aStandard[R858_ExtTunerNum][R858_IntTunerNum] = R858_Standard;

    if (R858_IntTunerNum == R858_TUNER1)
    {
        pR858_Info_Msg->R858_Standard = R858_Standard;
    }
    else
    {
        pR858_Info_Msg->R858_Standard_2 = R858_Standard;
    }

    return HI_SUCCESS;
}

UINT32 R858_RF_KHz = 435;
HI_S32 r858_set_tuner(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_U32 puRF)
{
    R858_Set_Info R858_Info_Msg;
    HI_S32 s32Ret = HI_FAILURE;
    

    R858_ExtTunerNum = u32TunerPort / R858_MAX_TUNER;
    R858_IntTunerNum = u32TunerPort % R858_MAX_TUNER;

    R858_I2C_SetPort(u32TunerPort);
    
    s32Ret = r858_set_standard(u32TunerPort, &R858_Info_Msg);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_TUNER("Set standard failed, port %d.\n", u32TunerPort);
        return HI_FAILURE;
    }

    R858_Info_Msg.R858_LT = LT_ON;
    R858_Info_Msg.R858_ClkOutMode = CLK_OUT_ON;
    R858_Info_Msg.RF_KHz = puRF; // unit: kHz	
    //R858_Info_Msg.R858_User_Mode = R858_DUAL;
    
    if(R858_SetPllData(R858_ExtTunerNum, R858_IntTunerNum, R858_Info_Msg) != RT_Success)
    {
        HI_ERR_TUNER("Set freq failed: port %d.\n", u32TunerPort);
        return HI_FAILURE;
    }
    
    R858_RF_KHz = puRF;

    return HI_SUCCESS;
}

HI_S32 r858_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength)
{
    R858_ErrCode err = RT_Success;
    INT32 RssiDbm  ;
    R858_Set_Info R858_Info_Msg;
    //UINT32 RfLevel  ;
    //UINT8 fgRfMaxGain ;


    R858_ExtTunerNum = u32TunerPort / R858_MAX_TUNER;
    R858_IntTunerNum = u32TunerPort % R858_MAX_TUNER;

    R858_Info_Msg.R858_Standard = R858_DVB_T_8M_IF_5M;

    R858_Info_Msg.RF_KHz = R858_RF_KHz;

    R858_I2C_SetPort(u32TunerPort);

    err = R858_GetTotalRssi(R858_ExtTunerNum, R858_IntTunerNum, R858_Info_Msg.RF_KHz, &RssiDbm);
    
    if(RT_Success != err)
    {
	    HI_ERR_TUNER("Get signal strength failed: port %d.\n", u32TunerPort);
	    return HI_FAILURE;
    }
	
    //HI_ERR_TUNER("========RssiDbm : %d ==========\n",(RssiDbm + 107));

    pu32SignalStrength[1] = (HI_U32)(RssiDbm + 106);	 
    
    return HI_SUCCESS;
}

HI_VOID r858_tuner_resume (HI_U32 u32TunerPort)
{
    r858_init_tuner(u32TunerPort);
    return;
}

