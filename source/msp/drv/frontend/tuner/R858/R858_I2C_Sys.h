#ifndef _I2C_SYS_H_
#define _I2C_SYS_H_

#include "R858.h"

typedef struct _I2C_LEN_TYPE
{
	UINT8 Data[50];
	UINT8 RegAddr;
	UINT8 Len;
	UINT8 I2cAddr;
	UINT8 Temp;
}I2C_LEN_TYPE;

typedef struct _I2C_TYPE
{
	UINT8 RegAddr;
	UINT8 Data;
	UINT8 I2cAddr;
	UINT8 Temp;
}I2C_TYPE;

int I2C_Init(void);
int Close_I2C(void);
int I2C_Write_Len(R858_ExtTunerNum_Type R858_Num, I2C_LEN_TYPE *I2C_Info);
int I2C_Read_Len(R858_ExtTunerNum_Type R858_Num, I2C_LEN_TYPE *I2C_Info);
int I2C_Write(R858_ExtTunerNum_Type R858_Num, I2C_TYPE *I2C_Info);
int Rafael_Convert(int InvertNum);
void R858_I2C_SetPort(unsigned int u32TunerPort);


#endif
