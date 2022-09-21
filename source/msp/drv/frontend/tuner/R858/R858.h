#ifndef  _R858_H_ 
#define _R858_H_

#define VERSION   "R858_GUI_v4_1.6"
#define VER_NUM   0
#define CHIP_ID       0x41

//----------------------------------------------------------//
//                   Type Define                                    //
//----------------------------------------------------------//
#define UINT8  unsigned char	//0 ~ 255
#define UINT16 unsigned short	//0 ~ 65535
#define UINT32 unsigned long	//0 ~ 4,294,967,295
#define INT32 signed int	       //¡V2147483648 ~ 2147483647
#define INT16 signed short		
#define INT8   signed char

#define TRUE   1
#define FALSE 0
//----------------------------------------------------------//
//                   Define                                            //
//----------------------------------------------------------//
//#define R858_SHARE_XTAL_OUT    FALSE     //self-oscillation

//#define R858_REG_NUM         48
#define R858_REG_NUM         56

#define R858_IMR_IF              5300
#define R858_IMR_TRIAL       9
#define R858_RING_POWER_FREQ_LOW   115000
#define R858_RING_POWER_FREQ_HIGH  450000

//temp, only for IQ_Tree use
#define R858_IMR_GAIN_REG     16
#define R858_IMR_PHASE_REG   17
#define R858_IMR_IQCAP_REG   15
#define R842_IMR_POINT_NUM   4  //per spectrum

//----------------------------------------------------------//
//                   Internal Structure                     //
//----------------------------------------------------------//
typedef struct _R858_Sys_Info_Type
{
	UINT8          BW;
	UINT8		   V17M; //
	UINT8		   HPF_COR;
	UINT8          FILT_EXT_ENA;
	UINT8          FILT_EXT_WIDEST;  //no use 
	UINT8          FILT_EXT_POINT; //
	UINT8          LNA_DET_MODE; //
	UINT8          HPF_NOTCH;  
	UINT8          NA_DISCHARGE;  //
	UINT8          AGC_CLK; 
	UINT8		   FILT_COMP;  //
	UINT8		   FILT_CUR;   //
	UINT8		   FILT_3DB;   //
	UINT8		   SWBUF_CUR;  //
	UINT8          TF_CUR;     //
	UINT8		   RF_BUF_CUR; //
	UINT8		   LNA_CUR;       //
	UINT8		   INDUC_BIAS;  //no use
	UINT8          SWCAP_CLK;  //
	UINT8          IMG_GAIN;  //no use
	UINT16		   IF_KHz; 
	UINT16		   FILT_CAL_IF;
}R858_Sys_Info_Type;

typedef struct _R858_Freq_Info_Type
{
	UINT8		RF_POLY;
	UINT8		LNA_BAND;
	UINT8		LPF_CAP;
	UINT8		LPF_NOTCH;
	UINT8		TF_DIPLEXER;
	UINT8		TF_HPF_BPF;
	UINT8		TF_HPF_CNR;
	UINT8		TF_BUF_PW;
	UINT8		IMR_MEM;
	UINT8       BYP_LPF; 
	UINT8       TEMP;    
}R858_Freq_Info_Type;

typedef struct _R858_SysFreq_Info_Type
{
	UINT8	   LNA_TOP;
	UINT8	   LNA_VTL_H;
	UINT8      RF_TOP;
	UINT8      RF_VTL_H;
	UINT8      RF_GAIN_LIMIT;
	UINT8      NRB_TOP;
	UINT8      NRB_BW_HPF;
	UINT8      NRB_BW_LPF;
	UINT8      DET_BW_LPF;
	UINT8      DET_BW_SEL;

	UINT8	   AUTO_SPEED;
	UINT8      AGC_CLK_CRTL;
	UINT8      LNA_RF_CHARGE_CUR;
	UINT8	   MIXER_TOP;
	UINT8	   MIXER_VTL_H;
	UINT8      MIXER_GAIN_LIMIT;
	UINT8      FILTER_TOP;
	UINT8      FILTER_VTL_H;
	UINT8      LNA_RF_DIS_MODE;
	UINT8      LNA_RF_DIS_CURR;
	UINT8      LNA_DIS_SLOW_FAST;
	UINT8      RF_DIS_SLOW_FAST;
	UINT8      BB_DET_MODE;
	UINT8      BB_DIS_CURR;
	UINT8      MIXER_FILTER_DIS;
	UINT8      IMG_NRB_ADDER;
	UINT8      LNA_NRB_DET;
	UINT8      ENB_POLY_GAIN;
	UINT8	   MIXER_AMP_CURRENT;
	UINT8	   MIXER_AMP_LPF;
	UINT8	   NA_PWR_DET;		//no use
	UINT8	   FILT_3TH_LPF_GAIN;
	UINT8	   FILT_5TH_NCH; //
	UINT8	   RF_LTE_PSG;
}R858_SysFreq_Info_Type;

typedef struct _R858_Cal_Info_Type
{
	UINT8		FILTER_6DB;
	UINT8		MIXER_AMP_GAIN;
	UINT8		MIXER_BUFFER_GAIN;
	UINT8		LNA_GAIN;
	UINT8		LNA_POWER;
	UINT8		RFBUF_OUT;
	UINT8		RFBUF_POWER;
	UINT8		TF_CAL;
}R858_Cal_Info_Type;

typedef struct _R858_SectType
{
	UINT8   Phase_Y;
	UINT8   Gain_X;
	UINT8   Iqcap;
	UINT8   Value;
}R858_SectType;

typedef enum _R858_IMR_Type  
{
	R858_IMR_NOR=0,
	R858_IMR_REV,
}R858_IMR_Type;

typedef enum _R858_Cal_Type
{
	R858_IMR_CAL = 0,
	R858_LPF_CAL
}R858_Cal_Type;


enum XTAL_PWR_VALUE
{
	R858_XTAL_LOWEST = 0,
    R858_XTAL_LOW,
    R858_XTAL_HIGH,
    R858_XTAL_HIGHEST,
	R858_XTAL_CHECK_SIZE
};


typedef enum _R858_Xtal_Div_TYPE
{
	XTAL_DIV1 = 0,
	XTAL_DIV1_2,	//1st_div2=0(R34[0]), 2nd_div2=1(R34[1])  ; same AGC clock
	XTAL_DIV2_1,	//1st_div2=1(R34[0]), 2nd_div2=0(R34[1])  ; diff AGC clock
	XTAL_DIV4
}R858_Xtal_Div_TYPE;

enum STANDBY_MODE
{
	R858_SBY_IND = 0,
    R858_SBY_ALL,
};

enum USER_MODE
{
	R858_SINGLE = 0,  //single R858
    R858_DUAL,          //dual R858
};

typedef enum _R858_Share_Xtal_Type
{
	R858_NO_SHARE_XTAL = 0,           //single R858
	R858_MASTER_TO_SLAVE_XTAL,        //Dual   R858 
    R858_SLAVE_XTAL_IN,               //Only R858_1 is slave
	R858_SLAVE_XTAL_OFF,			  //Both R858_1 and R8s8_2 are slave

}R858_Share_Xtal_Type;
//----------------------------------------------------------//
//                   R858 Public Parameter                     //
//----------------------------------------------------------//
typedef enum _R858_ErrCode
{
	RT_Success = TRUE,
	RT_Fail = FALSE
}R858_ErrCode;

//typedef enum _R858_Standard_Type  //Don't remove standand list!!
//{
//	R858_MN_5100 = 0,          //for NTSC_MN, PAL_M (IF=5.1M)
//	R858_MN_5800,              //for NTSC_MN, PLA_M (IF=5.8M)
//	R858_PAL_I,                //for PAL-I
//	R858_PAL_DK,               //for PAL DK in non-"DTMB+PAL DK" case
//	R858_PAL_B_7M,             //no use
//	R858_PAL_BGH_8M,           //for PAL B/G, PAL G/H
//	R858_SECAM_L,              //for SECAM L
//	R858_SECAM_L1,             //for SECAM L'
//	R858_SECAM_L1_INV,       
//	R858_MN_CIF_5M,             //for NTSC_MN, PLA_M (CIF=5.0M)
//	R858_PAL_I_CIF_5M,          //for PAL-I (CIF=5.0M)
//	R858_PAL_DK_CIF_5M,         //for PAL DK (CIF=5M)
//	R858_PAL_B_7M_CIF_5M,       //for PAL-B 7M (CIF=5M)
//	R858_PAL_BGH_8M_CIF_5M,     //for PAL G/H 8M (CIF=5M)
//	R858_SECAM_L_CIF_5M,        //for SECAM L (CIF=5M)
//	R858_SECAM_L1_CIF_5M,       //for SECAM L' (CIF=5M)
//	R858_SECAM_L1_INV_CIF_5M,   //(CIF=5M)
//	R858_ATV_SIZE,
//	R858_DVB_T_6M = R858_ATV_SIZE,
//	R858_DVB_T_7M,
//	R858_DVB_T_8M, 
//    R858_DVB_T2_6M,       //IF=4.57M
//	R858_DVB_T2_7M,       //IF=4.57M
//	R858_DVB_T2_8M,       //IF=4.57M
//	R858_DVB_T2_1_7M,
//	R858_DVB_T2_10M,
//	R858_DVB_C_8M,
//	R858_DVB_C_6M, 
//	R858_J83B,
//	R858_ISDB_T_4063,      //IF=4.063M
//	R858_ISDB_T_4570,		 //IF=4.57M
//	R858_DTMB_8M_4570,  //IF=4.57M, BW=8M
//	R858_DTMB_6M_4500,  //IF=4.50M, BW=6M
//	R858_ATSC,
//	R858_SATELLITE,  //no use, 
//	R858_DVB_T_6M_IF_5M,   //below are DTV IF=5M 
//	R858_DVB_T_7M_IF_5M,
//	R858_DVB_T_8M_IF_5M,
//	R858_DVB_T2_6M_IF_5M,
//	R858_DVB_T2_7M_IF_5M,
//	R858_DVB_T2_8M_IF_5M,
//	R858_DVB_T2_1_7M_IF_5M,
//	R858_DVB_C_8M_IF_5M,
//	R858_DVB_C_6M_IF_5M, 
//	R858_J83B_IF_5M,
//	R858_ISDB_T_IF_5M,
//	R858_DTMB_8M_IF_5M,   //IF=5.0M, BW=8M
//	R858_DTMB_6M_IF_5M,   //IF=5.0M, BW=6M
//	R858_ATSC_IF_5M,  
//	R858_FM,
//	R858_STD_SIZE,
//}R858_Standard_Type;



typedef enum _R858_Standard_Type  //Don't remove standand list!!
{
	//DTV
	R858_DVB_T_6M = 0,  
	R858_DVB_T_7M,
	R858_DVB_T_8M, 
    R858_DVB_T2_6M,       //IF=4.57M
	R858_DVB_T2_7M,       //IF=4.57M
	R858_DVB_T2_8M,       //IF=4.57M
	R858_DVB_T2_1_7M,
	R858_DVB_T2_10M,
	R858_DVB_C_8M,
	R858_DVB_C_6M, 
	R858_J83B,
	R858_ISDB_T_4063,           //IF=4.063M
	R858_ISDB_T_4570,           //IF=4.57M
	R858_DTMB_8M_4570,      //IF=4.57M
	R858_DTMB_6M_4500,      //IF=4.5M, BW=6M
	R858_ATSC,  
	//DTV IF=5M
	R858_DVB_T_6M_IF_5M,
	R858_DVB_T_7M_IF_5M,
	R858_DVB_T_7M_IF_5500,
	R858_DVB_T_8M_IF_5M,
	R858_DVB_T_8M_IF_5500,
	R858_DVB_T2_6M_IF_5M,
	R858_DVB_T2_7M_IF_5M,
	R858_DVB_T2_7M_IF_5500,
	R858_DVB_T2_8M_IF_5M,
	R858_DVB_T2_8M_IF_5500,
	R858_DVB_T2_1_7M_IF_5M,
	R858_DVB_C_8M_IF_5500,
	R858_DVB_C_8M_IF_5M,
	R858_DVB_C_6M_IF_5500,
	R858_DVB_C_6M_IF_5M,
	R858_J83B_IF_5370,
	R858_J83B_IF_5070,
	R858_J83B_IF_5M,
	R858_J83B_IF_5500,
	R858_J83B_IF_4300,
	R858_J83B_IF_4000,
	R858_ISDB_T_IF_5M,            
	R858_DTMB_8M_IF_5M,     
	R858_DTMB_6M_IF_5M,     
	R858_ATSC_IF_5M,  
	R858_ATSC_IF_5500,
	//R858_FM,
	R858_STD_SIZE,
}R858_Standard_Type;

typedef enum _R858_GPO_Type
{
	HI_SIG = TRUE,
	LO_SIG = FALSE
}R858_GPO_Type;

typedef enum _R858_RF_Gain_TYPE
{
	RF_AUTO = 0,
	RF_MANUAL
}R858_RF_Gain_TYPE;




typedef enum _R858_ClkOutMode_Type
{
	CLK_OUT_OFF = 0,
	CLK_OUT_ON
}R858_ClkOutMode_Type;

typedef enum _R858_LT_Type
{
	LT_OFF = 0,   //off or passive LT
	LT_ON           //active LT
}R858_LT_Type;

typedef struct _R858_Set_Info
{
	UINT32							RF_KHz;
	R858_Standard_Type				R858_Standard;
	R858_Standard_Type				R858_Standard_2;
	R858_ClkOutMode_Type			R858_ClkOutMode;
	R858_LT_Type					R858_LT;
	UINT8                           R858_User_Mode;

}R858_Set_Info;

typedef struct _R858_RF_Gain_Info
{
	UINT16  RF_gain_comb;
	UINT8   RF_gain1;
	UINT8   RF_gain2;
	UINT8   RF_gain3;
	UINT8	RF_gain4;
}R858_RF_Gain_Info;


typedef enum _R858_IntTunerNum_Type  //R858 Internal tuner num
{
	R858_TUNER1 = 0,
	R858_TUNER2,
	R858_MAX_TUNER
}R858_IntTunerNum_Type;

typedef enum _R858_ExtTunerNum_Type   //R858 External tuner num
{
	R858_NUM1 = 0,
	R858_NUM2,
	R858_MAX_NUM
}R858_ExtTunerNum_Type;


typedef enum _R858_IMR_CAL_TYPE
{
	IMR_AUTO = 0,
	IMR_MANUAL
}R858_IMR_CAL_TYPE;
//----------------------------------------------------------//
//                   R858 Public Function                       //
//----------------------------------------------------------//


//#define R858_Delay_MS(R858_ExtTunerNum_Type, x_ms)	usleep(x_ms)
#define R858_Delay_MS(R858_ExtTunerNum_Type, x_ms)	msleep(x_ms)  //	Sleep(x_ms)



R858_ErrCode R858_Init_ALL(R858_ExtTunerNum_Type R858_Num,R858_Set_Info R858_INFO);
R858_ErrCode R858_Init(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);
R858_ErrCode R858_Cal_Prepare(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 u1CalFlag);
R858_ErrCode R858_IMR_Process(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);
R858_ErrCode R858_IMR(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 IMR_MEM, UINT8 IM_Flag,UINT8 Rev_Mode);

R858_ErrCode R858_InitUserMode(R858_Set_Info R858_INFO);
R858_ErrCode R858_SetPllData(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_Set_Info R858_INFO);
R858_ErrCode R858_Standby(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_LT_Type R858_LT);
R858_ErrCode R858_Wakeup(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum);
R858_ErrCode R858_GetRfGain(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_RF_Gain_Info *pR858_rf_gain);
R858_ErrCode R858_RfGainMode(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, R858_RF_Gain_TYPE R858_RfGainType);
R858_ErrCode R858_SetXtalCap(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT8 u8XtalCap); 
R858_ErrCode R858_GetRfRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 RF_Freq_Khz, INT32 *RfLevelDbm, UINT8 *fgRfMaxGain);
R858_ErrCode R858_GetIfRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, INT32 *VgaGain);
R858_ErrCode R858_GetTotalRssi(R858_ExtTunerNum_Type R858_Num, R858_IntTunerNum_Type IntTunerNum, UINT32 RF_Freq_Khz, INT32 *RssiDbm);
    

#endif