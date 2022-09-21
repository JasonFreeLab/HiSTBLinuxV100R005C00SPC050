/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_com.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/12/10
  Description   :
  History       :
  Date          : 2014/12/10
  Author        : sdk
  Modification  :
*******************************************************************************/
#include "reg51.h"
#include "hdmi_mcu_com.h"

/************************* define *********************************************/
#define MCU_REG_CMD_CLEAR       0x00
#define MCU_REG_CMD_READ        0x01
#define MCU_REG_CMD_WRITE       0x03
#define MCU_IRAM_CMD_WRITE      0x07
#define MCU_INTR_CMD_MCE        0x1d

/* UART0 */
#define MCU_REG_UART0_BASE      0xf8b00000
#define MCU_REG_UART0_DR        (MCU_REG_UART0_BASE + 0x0000)
#define MCU_REG_UART0_FR        (MCU_REG_UART0_BASE + 0x0018)

/*************************  enum   ********************************************/

/*************************  struct ********************************************/
typedef union
{
    /* Define the struct bits */
    struct
    {
        HI_U16    bit16_reserved    : 16 ; /* [31:15] */

        HI_U16    bit8_data     : 8  ; /* [7:0] */
        HI_U16    bit1_fe       : 1  ; /* [8] */
        HI_U16    bit1_pe       : 1  ; /* [9] */
        HI_U16    bit1_be       : 1  ; /* [10] */
        HI_U16    bit1_oe       : 1  ; /* [11] */
        HI_U16    bit8_reserved : 4  ; /* [15:12] */
    } bits;

    /* Define an unsigned member */
    HI_U32    u32;
} REG_UART_DR_U; /* OFFSET 0x0000 */

typedef union
{
    /* Define the struct bits */
    struct
    {
        HI_U16    bit16_reserved    : 16 ; /* [31:15] */

        HI_U16    bit3_reserved     : 3  ; /* [2:0] */
        HI_U16    bit1_busy         : 1  ; /* [3] */
        HI_U16    bit1_rxfe         : 1  ; /* [4] */
        HI_U16    bit1_txff         : 1  ; /* [5] */
        HI_U16    bit1_rxff         : 1  ; /* [6] */
        HI_U16    bit1_txfe         : 1  ; /* [7] */
        HI_U16    bit8_reserved     : 8  ; /* [16:8] */
    } bits;

    /* Define an unsigned member */
    HI_U32    u32;
} REG_UART_FR_U; /* OFFSET 0x0018 */

/************************* private data ***************************************/
/* read/write reg */
volatile MCU_COM_U32_U *s_pun32Addr;
volatile MCU_COM_U32_U *s_pun32Data;
static HI_U16           s_u16TimeOut;
static MCU_COM_U32_U    s_un32Data;

/* read/write comm port */
//static HI_U16           u16CharSize = 0;
static MCU_COM_U32_U    s_un32RegUart ;
static REG_UART_FR_U   *s_punRegUartFr;
static REG_UART_DR_U   *s_punRegUartDr;

/************************* public  data ***************************************/

/************************* private interface **********************************/

/************************* public  interface **********************************/

HI_U32 HDMI_MCU_ComRegRead(volatile HI_U32 u32Addr)
{
    s_u16TimeOut = 0xff;

    s_pun32Addr  = (volatile MCU_COM_U32_U *)&u32Addr;
    //pun32Data  =(volatile MCU_COM_U32_U *)pu32Value ;

    ADDR_REG_0 = s_pun32Addr->u8[3];
    ADDR_REG_1 = s_pun32Addr->u8[2];
    ADDR_REG_2 = s_pun32Addr->u8[1];
    ADDR_REG_3 = s_pun32Addr->u8[0];

    CMD_REG = MCU_REG_CMD_READ;
    while( (!(CMD_STATUS_REG & MASK_BIT_1)) && (s_u16TimeOut--));
    CMD_REG = MCU_REG_CMD_CLEAR;

    if (!s_u16TimeOut)
    {
        //error;
    }

    s_un32Data.u8[0] = RD_DATA_REG_3;
    s_un32Data.u8[1] = RD_DATA_REG_2;
    s_un32Data.u8[2] = RD_DATA_REG_1;
    s_un32Data.u8[3] = RD_DATA_REG_0;

    return s_un32Data.u32;
}

HI_VOID HDMI_MCU_ComRegWrite(volatile HI_U32 u32Addr, volatile HI_U32 u32Value)
{
    s_u16TimeOut = 0xff;
    s_pun32Addr  = (volatile MCU_COM_U32_U *)&u32Addr;
    s_pun32Data  = (volatile MCU_COM_U32_U *)&u32Value;

    ADDR_REG_0    = s_pun32Addr->u8[3];
    ADDR_REG_1    = s_pun32Addr->u8[2];
    ADDR_REG_2    = s_pun32Addr->u8[1];
    ADDR_REG_3    = s_pun32Addr->u8[0];

    WR_DATA_REG_0 = s_pun32Data->u8[3];
    WR_DATA_REG_1 = s_pun32Data->u8[2];
    WR_DATA_REG_2 = s_pun32Data->u8[1];
    WR_DATA_REG_3 = s_pun32Data->u8[0];

    CMD_REG = MCU_REG_CMD_WRITE;
    while ((CMD_STATUS_REG & MASK_BIT_0) && (s_u16TimeOut--));
    CMD_REG = MCU_REG_CMD_CLEAR;

    if (!s_u16TimeOut)
    {
        //error;
    }

    return ;
}

#if 0
HI_VOID HDMI_MCU_ComPutc(HI_U8 u8Char)
{
#if HDMI_MCU_DEBUG
    s_punRegUartFr = (REG_UART_FR_U *)&s_un32RegUart.u32;
    s_punRegUartDr = (REG_UART_DR_U *)&s_un32RegUart.u32;

    for (s_u16TimeOut = 0xffff,s_un32RegUart.u32=0; s_u16TimeOut && (s_punRegUartFr->bits.bit1_rxfe); s_u16TimeOut--)
    {
        s_un32RegUart.u32 = HDMI_MCU_ComRegRead(MCU_REG_UART0_FR);
    }

    s_un32RegUart.u32              = 0;
    s_punRegUartDr->bits.bit8_data = u8Char;
    HDMI_MCU_ComRegWrite(MCU_REG_UART0_DR, s_un32RegUart.u32);
#if 0
    u16TimeOut  = 0xff;
    un32RegUart.u32  =0;
    do
    {
        un32RegUart.u32 = HDMI_MCU_ComRegRead(MCU_REG_UART0_FR);
    }while( (u16TimeOut--) &&  punRegUartFr->bz16.bit1_busy);
#endif
#endif

    return ;
}

HI_VOID HDMI_MCU_ComPutU8Hex(HI_U8 u8Char)
{
#if HDMI_MCU_DEBUG
    HI_U8 u8Tmp = u8Char;

    u8Tmp >>= 4;
    u8Tmp += ((u8Tmp>=0) && (u8Tmp<=9)) ? '0' : 'W';
    HDMI_MCU_ComPutc(u8Tmp);
    u8Tmp = u8Char & 0x0f;
    u8Tmp += ((u8Tmp>=0) && (u8Tmp<=9)) ? '0' : 'W';
    HDMI_MCU_ComPutc(u8Tmp);
#endif

    return ;
}

HI_VOID HDMI_MCU_ComPutU32Hex(HI_U32 u32Value)
{
#if HDMI_MCU_DEBUG
    HI_U8 u8Tmp = 0;
    s_pun32Data  = (volatile MCU_COM_U32_U *)&u32Value;

    HDMI_MCU_ComPutc('0');
    HDMI_MCU_ComPutc('x');
    u8Tmp = s_pun32Data->u8[0];
    HDMI_MCU_ComPutU8Hex(u8Tmp);
    u8Tmp = s_pun32Data->u8[1];
    HDMI_MCU_ComPutU8Hex(u8Tmp);
    u8Tmp = s_pun32Data->u8[2];
    HDMI_MCU_ComPutU8Hex(u8Tmp);
    u8Tmp = s_pun32Data->u8[3];
    HDMI_MCU_ComPutU8Hex(u8Tmp);
#endif

    return ;
}


HI_VOID HDMI_MCU_ComPuts(HI_U8 *pu8Str)
{
#if HDMI_MCU_DEBUG
    while( pu8Str && (*pu8Str != '\0') )
    {
        HDMI_MCU_ComPutc(*pu8Str);
        pu8Str++;
    }
#endif

    return ;
}
#endif

HI_VOID HDMI_MCU_ComDelayMs(HI_U16 n)
{
    HI_U16 i = 0,j = 0,k=0;

    for (i=0;i<n;i++)
#if defined (HDMI_MCU_24M)
        for(j=0;j<100;j++);     // 100*10us = 1ms
            for(k=0;k<240;k++); // (1/24M) * 240 = 10us
#elif defined (HDMI_MCU_200M)
        for(j=0;j<1000;j++);    // 1000*1us = 1ms
            for(k=0;k<200;k++); // (1/200M) * 200 = 1us
#elif defined (HDMI_MCU_6M)
        for(j=0;j<100;j++);     // 100*10us = 1ms
            for(k=0;k<60;k++);  // (1/6M) * 60 = 10us
#endif

    return ;
}

HI_VOID HDMI_MCU_ComDelayUs(HI_U16 n)
{
    HI_U16 i = 0,j = 0;

#if defined (HDMI_MCU_24M)
    for(i=0;i<n;i++)
        for(j=0;j<24;j++);      // (1/24M) * 24 = 1us
#elif defined (HDMI_MCU_200M)
    for(j=0;j<n;j++);
        for(j=0;j<200;j++);     // (1/200M) * 200 = 1us
#elif defined (HDMI_MCU_6M)
    for(j=0;j<n;j++);
        for(j=0;j<6;j++);       // (1/6M) * 6 = 1us
#endif

    return ;
}

/************************* end of file ****************************************/

