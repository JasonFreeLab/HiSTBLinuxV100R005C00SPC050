
/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_com.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : t00273561
  Modification  :
*******************************************************************************/
#ifndef __MCU_HDMI_COM_H__
#define __MCU_HDMI_COM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"
#include "base.h"

#define  HDMI_MCU_DEBUG  1
//#define HDMI_MCU_6M
#define HDMI_MCU_24M
//#define HDMI_MCU_200M

#define MASK_BIT_0  0x01
#define MASK_BIT_1  0x02
#define MASK_BIT_2  0x04
#define MASK_BIT_3  0x08
#define MASK_BIT_4  0x10
#define MASK_BIT_5  0x20
#define MASK_BIT_6  0x40
#define MASK_BIT_7  0x80

#define MCU_COM_CLEAR(x)     ((x) = 0)
#define MCU_BIT_CHK(p, mask) ((p) & (mask))

#define MCU_NULL_CHK_RET(p)  do{ \
	if ((void *)HI_NULL == p) \
	{HDMI_MCU_ComPuts("null *p!\n"); \
	return HI_FAILURE;} \
}while(0)

typedef union
{
    HI_U8   u8[4];
    HI_U16  u16[2];
    HI_U32  u32;
}MCU_COM_U32_U;

HI_U32  HDMI_MCU_ComRegRead(volatile HI_U32 u32Addr);
HI_VOID HDMI_MCU_ComRegWrite(volatile HI_U32 u32Addr, volatile HI_U32 u32Value);

//HI_VOID HDMI_MCU_ComPutU8Hex(HI_U8 u8Char);
#define HDMI_MCU_ComPutU8Hex(u8Char) printf_hex(u8Char)
//HI_VOID HDMI_MCU_ComPutU32Hex(HI_U32 u32Value);

#define HDMI_MCU_ComPutc(u8Char) printf_char(u8Char)
#define HDMI_MCU_ComPuts(pu8Str) printf_str(pu8Str)
//HI_VOID HDMI_MCU_ComPutc(HI_U8 u8Char);
//HI_VOID HDMI_MCU_ComPuts(HI_U8 *pu8Str);

HI_VOID HDMI_MCU_ComDelayMs(HI_U16 n);
HI_VOID HDMI_MCU_ComDelayUs(HI_U16 n);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __HDMI_MCU_COM_H__ */


