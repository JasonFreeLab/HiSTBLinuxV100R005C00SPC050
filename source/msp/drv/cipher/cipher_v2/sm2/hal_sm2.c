/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_sm2.c
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_adapt.h"
#include "hal_sm2.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

extern HI_VOID *g_u32Sm2Base;
extern HI_VOID *g_u32Sm2Crg;

/* Set the defualt timeout value for hash calculating (5000 ms)*/
#define SM2_MAX_DURATION (30000)

#define  SM2_REG_BASE_ADDR              g_u32Sm2Base  //IO_ADDRESS(SM2_REG_BASE_ADDR_PHY)
#define  SM2_REG_BUSY                   (SM2_REG_BASE_ADDR + 0x00)
#define  SM2_REG_WORK_MODE              (SM2_REG_BASE_ADDR + 0x04)
#define  SM2_REG_STRAT                  (SM2_REG_BASE_ADDR + 0x08)
#define  SM2_REG_DEBUG_EN               (SM2_REG_BASE_ADDR + 0x10)
#define  SM2_REG_RNG_OPTION             (SM2_REG_BASE_ADDR + 0x14)
#define  SM2_REG_INT_ENABLE             (SM2_REG_BASE_ADDR + 0x20)
#define  SM2_REG_INT_STATUS             (SM2_REG_BASE_ADDR + 0x24)
#define  SM2_REG_NOMASK_STATUS          (SM2_REG_BASE_ADDR + 0x28)
#define  SM2_REG_RESULT_FLAG            (SM2_REG_BASE_ADDR + 0x40)
#define  SM2_REG_FAILURE_FLAGS          (SM2_REG_BASE_ADDR + 0x44)
#define  SM2_REG_RRAM_CTRL_CFG          (SM2_REG_BASE_ADDR + 0x6c)
#define  SM2_REG_WP_L                   (SM2_REG_BASE_ADDR + 0x80)
#define  SM2_REG_WP_H                   (SM2_REG_BASE_ADDR + 0x84)
#define  SM2_REG_OTP_KEY_SEL_EN         (SM2_REG_BASE_ADDR + 0x88)
#define  SM2_REG_KEY_RANDOM             (SM2_REG_BASE_ADDR + 0x8c)
#define  SM2_REG_KEY_CRC                (SM2_REG_BASE_ADDR + 0x90)
#define  SM2_REG_KEY_CFG                (SM2_REG_BASE_ADDR + 0x9c)
#define  SM2_REG_KEY_RANDOM_A           (SM2_REG_BASE_ADDR + 0x100)
#define  SM2_REG_MRAM                   (SM2_REG_BASE_ADDR + 0x200)
#define  SM2_REG_NRAM                   (SM2_REG_BASE_ADDR + 0x600)
#define  SM2_REG_KRAM                   (SM2_REG_BASE_ADDR + 0xa00)
#define  SM2_REG_RRAM                   (SM2_REG_BASE_ADDR + 0xe00)
#define  SM2_RAM_SECTION_SIZE_IN_WORD   (0x18)

HI_S32 HAL_SM2_WaitReady(HI_BOOL bIsFast)
{
    HI_SIZE_T ulTimeOut = 0;
    HI_U32 u32Ctrl;

    /* wait for hash_rdy */
    while(1)
    {
        (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_BUSY, &u32Ctrl);
        if((u32Ctrl & 0x01) == 0x00)
        {
             break;
        }
        if (ulTimeOut++ >= SM2_MAX_DURATION )
        {
            HI_ERR_CIPHER("Error! SM2 wait ready time out!\n");
            return HI_FAILURE;
        }
        if (!bIsFast)
        {
            cipher_msleep(1);
        }
    }

    return HI_SUCCESS;
}

HI_VOID HAL_SM2_SetMode(SM2_MODEA_S enModea, SM2_OPCODE_S enOpcode)
{
    HI_U32 u32Mode;
//    HI_U32 u32Val;

    if (enOpcode != SM2_OPCODE_CLR_RAM)
    {
        u32Mode = 0x04 << 8;
        u32Mode|= enOpcode;
    }
    else
    {
        u32Mode = enModea << 8;
        u32Mode|= enOpcode;
    }

    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_WORK_MODE, u32Mode);
}

HI_VOID HAL_SM2_Start(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_STRAT, 0x05);
}

HI_U32 HAL_SM2_GetResultFlag(HI_VOID)
{
    HI_U32 u32Flag;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_RESULT_FLAG, &u32Flag);

    return u32Flag;
}

HI_U32 HAL_SM2_GetFailureFlag(HI_VOID)
{
    HI_U32 u32Flag;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_FAILURE_FLAGS, &u32Flag);

    return u32Flag;
}

HI_U16 HAL_SM2_GetCrc16(HI_VOID)
{
    HI_U32 u32Crc;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_RRAM_CTRL_CFG, &u32Crc);

    return (u32Crc >> 16) & 0xFFFF;
}


HI_VOID HAL_SM2_ClrInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_NOMASK_STATUS, 0x11);
}

HI_U32 HAL_SM2_GetInt(HI_VOID)
{
    HI_U32 u32Int;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_INT_STATUS, &u32Int);

    return u32Int;
}

HI_U32 HAL_SM2_GetRawInt(HI_VOID)
{
    HI_U32 u32Int;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_NOMASK_STATUS, &u32Int);

    return u32Int;
}

HI_U32 HAL_SM2_GetBusy(HI_VOID)
{
    HI_U32 u32Busy;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_BUSY, &u32Busy);

    return u32Busy;
}

HI_U32 HAL_SM2_GetIntEn(HI_VOID)
{
    HI_U32 u32Int;

    (HI_VOID)HAL_CIPHER_ReadReg(SM2_REG_INT_ENABLE, &u32Int);

    return u32Int;
}

HI_VOID HAL_SM2_EnableInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_INT_ENABLE, 0x80000003);
}

HI_VOID HAL_SM2_DisableInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_INT_ENABLE, 0x00);
}

HI_VOID HAL_SM2_SetRAM(SM2_RAM_TYPE_S enRamType, HI_U32 u32Section, const HI_U32 u32Ram[SM2_LEN_IN_WROD], HI_BOOL bIsExpandZero)
{
    HI_VOID *pAddrStart = 0;
    HI_VOID *pAddrEnd = 0;
    HI_U32 u32Val;
    HI_U32 i;

    pAddrStart = SM2_REG_MRAM + 0x400 * enRamType + u32Section * SM2_RAM_SECTION_SIZE_IN_WORD *4;
    pAddrEnd = pAddrStart + SM2_RAM_SECTION_SIZE_IN_WORD * 4;

    for(i=0; i<SM2_LEN_IN_WROD; i++)
    {
        u32Val = CPU_TO_BE32(u32Ram[SM2_LEN_IN_WROD - i - 1]);
        (HI_VOID)HAL_CIPHER_WriteReg(pAddrStart, u32Val);
        pAddrStart+=4;
    }
    if (bIsExpandZero)
    {
        while(pAddrStart < pAddrEnd)//¸ßÎ»²¹0
        {
            (HI_VOID)HAL_CIPHER_WriteReg(pAddrStart, 0x00);
            pAddrStart+=4;
        }
    }
}

HI_VOID HAL_SM2_GetRAM(SM2_RAM_TYPE_S enRamType, HI_U32 u32Section, HI_U32 *u32Ram)
{
    HI_VOID *pAddr;
    HI_U32 u32Val;
    HI_U32 u32Len = SM2_LEN_IN_WROD;
    HI_U32 i;

    if (enRamType == SM2_RAM_TYPE_MRAM) //when compute mul, the result is store in 0x00~0x40
    {
        u32Len = SM2_LEN_IN_WROD *2;
    }

    pAddr = SM2_REG_MRAM + 0x400 * enRamType + u32Section * SM2_RAM_SECTION_SIZE_IN_WORD * 4;

    for(i=0; i<u32Len; i++)
    {
        (HI_VOID)HAL_CIPHER_ReadReg(pAddr + i*4, &u32Val);
        u32Ram[u32Len - i - 1]  = CPU_TO_BE32(u32Val);
    }
}

HI_VOID HAL_SM2_SetWP(HI_U32 u32WPH, HI_U32 u32WPL)
{
    HI_U32 u32Val;

    u32Val = CPU_TO_BE32(u32WPL);
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_WP_L, u32Val);

    u32Val = CPU_TO_BE32(u32WPH);
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_WP_H, u32Val);
}

HI_VOID HAL_SM2_SetRngOption(HI_U32 u32Option)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_RNG_OPTION, u32Option);
}

HI_VOID HAL_SM2_OTPKeyEnable(HI_BOOL bIsEnable)
{
    if (bIsEnable)
    {
        (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_OTP_KEY_SEL_EN, 0x06);
    }
    else
    {
        (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_OTP_KEY_SEL_EN, 0x09);
    }
}

HI_VOID HAL_SM2_SetKeyRandom(HI_U32 u32Random[2])
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_KEY_RANDOM, CPU_TO_BE32(u32Random[0]));
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_KEY_RANDOM_A, CPU_TO_BE32(u32Random[1]));
}

HI_VOID HAL_SM2_SetKeyCrc(HI_U16 u16Crc)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_KEY_CRC, u16Crc);
}

HI_VOID HAL_SM2_PrivateKeyEnable(HI_BOOL bIsEnable)
{
    if (bIsEnable)
    {
        (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_KEY_CFG, 0x05);
    }
    else
    {
        (HI_VOID)HAL_CIPHER_WriteReg(SM2_REG_KEY_CFG, 0x0a);
    }
}

HI_VOID HAL_SM2_Enable(HI_VOID)
{
    HI_U32 Value;
    HI_U32 *pu32Crg = g_u32Sm2Crg;

    HAL_CIPHER_ReadReg(pu32Crg, &Value);
    HAL_SET_BIT(Value, 12);   /* clock opened */
    HAL_CIPHER_WriteReg(pu32Crg, Value);

    cipher_msleep(1);

    HAL_CLEAR_BIT(Value, 9); /* cancel reset */
    HAL_CIPHER_WriteReg(pu32Crg, Value);

#ifdef INT_ENABLE
    HAL_SM2_EnableInt();
#endif
}

HI_VOID HAL_SM2_Disable(HI_VOID)
{
    HI_U32 Value;
    HI_U32 *pu32Crg = g_u32Sm2Crg;

    HAL_CIPHER_ReadReg(pu32Crg, &Value);
    HAL_SET_BIT(Value, 9); /* reset */
    HAL_CIPHER_WriteReg(pu32Crg,Value);
    cipher_msleep(1);

    HAL_CIPHER_ReadReg(pu32Crg, &Value);
    HAL_CLEAR_BIT(Value, 12);   /* clock close */
    HAL_CIPHER_WriteReg(pu32Crg,Value);
}

HI_S32 HAL_SM2_SoftReset(HI_VOID)
{
    HAL_SM2_Disable();
    HAL_SM2_Enable();
    
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
