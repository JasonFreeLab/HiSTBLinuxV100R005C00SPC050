#include "hi_type.h"
#include "R850.h"

extern R850_TUNER_NUM_TYPE TUNER_NO;

typedef struct _I2C_LEN_TYPE
{
	UINT8 RegAddr;
	UINT8 Data[50];
	UINT8 Len;
}I2C_LEN_TYPE;

typedef struct _I2C_TYPE
{
	UINT8 RegAddr;
	UINT8 Data;
}I2C_TYPE;

UINT8 R850_I2C_Write_Len(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_LEN_TYPE *I2C_Info);
UINT8 R850_I2C_Read_Len(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_LEN_TYPE *I2C_Info);
UINT8 R850_I2C_Write(R850_TUNER_NUM_TYPE R850_Tuner_Num, I2C_TYPE *I2C_Info);
int R850_Convert(int InvertNum);
