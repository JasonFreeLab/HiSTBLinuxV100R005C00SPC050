/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sm2.c
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_adapt.h"
#include "hal_sm2.h"
#include "drv_rng.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

cipher_mutex g_Sm2Mutex;
cipher_queue_head s_stSm2WaitQueue;

#define SM2_IRQ_NUMBER                 (157 + 32)
#define SM2_TIME_OUT                   1000
#define CRC16_POLYNOMIAL               0x1021

#if 0
/****************Only for debug***********************/
#define SM2_DBG_MSG(a,b,c)          HI_PRINT_HEX(a,b,c)
const HI_U8 *g_pu8k = "\x59\x27\x6e\x27\xd5\x06\x86\x1a\x16\x68\x0f\x3a\xd9\xc0\x2d\xcc\xef\x3c\xc1\xfa\x3c\xdb\xe4\xce\x6d\x54\xb8\x0d\xea\xc1\xbc\x21";
/**********************END****************************/
#else
#define SM2_DBG_MSG(a,b,c)
const HI_U8 *g_pu8k = HI_NULL;
#endif

static HI_U32 g_bSm2Done = HI_FALSE;
HI_VOID *g_u32Sm2Base = HI_NULL;
HI_VOID *g_u32Sm2Crg = HI_NULL;

static const HI_S8 * s_ErrString[] =
{
    "SM2 is still running",
    "The operation of mod inverse is failed",
    "Get randnum failed",
    "Attacked by DFA",
    "The result of mod add/multiply is infinity"
};
static HI_U16 s_u16CRC16Table[256];

#define random()  DRV_CIPHER_Rand() //prandom_u32()
#define SM2_CHECK(f) if( ( ret = f ) != 0 ) { DRV_SM2_DeInit(); DRV_SM2_Init(); goto cleanup;}

static HI_VOID  DRV_SM2_CRC16Init(void)
{
    HI_U16 nRemainder;
    HI_U16 i, j;

    for(i = 0; i < 256; i ++)
    {
        nRemainder = i << 8;
        for(j = 8; j > 0; j --)
        {
            if(nRemainder & 0x8000)
            {
                nRemainder = (nRemainder << 1) ^ CRC16_POLYNOMIAL;
            }
            else
            {
                nRemainder = (nRemainder << 1);
            }
        }
        s_u16CRC16Table[i] = nRemainder;
    }
}

/**
KEY Encrypt with random :
    K_temp = K ^ {random_2,random_1,random_2,random_1,random_2,random_1,andom_2,random_1}
    crc_data_in = { random_2,random_1, K_temp };
**/
HI_U16 DRV_SM2_CRC16Key(HI_U16 u32Initial , HI_U32 u32Key[SM2_LEN_IN_WROD])
{
    HI_U32 i, j;
    HI_U16 u16CRC = 0x0000;
    HI_U8 *pu8Val;

    u16CRC = u32Initial;

    for( i = 0; i < SM2_LEN_IN_WROD; i+=2)
    {
        pu8Val = (HI_U8*)&u32Key[SM2_LEN_IN_WROD - i - 2];
        for (j=0; j<4; j++)
        {
            u16CRC = (u16CRC << 8) ^ s_u16CRC16Table[((u16CRC >> 8) ^ pu8Val[j]) & 0x00FF];
        }
        pu8Val = (HI_U8*)&u32Key[SM2_LEN_IN_WROD - i - 1];
        for (j=0; j<4; j++)
        {
            u16CRC = (u16CRC << 8) ^ s_u16CRC16Table[((u16CRC >> 8) ^ pu8Val[j]) & 0x00FF];
        }
    }

    return u16CRC;
}

/*crc = CRC16(crc, randnum)*/
static HI_U16 DRV_SM2_CRC16Rndom(HI_U16 u32Initial , HI_U32 u32Rndom[2])
{
    HI_U32 i;
    HI_U16 u16CRC = 0x0000;
    HI_U8 *pu8Val;

    u16CRC = u32Initial;
    pu8Val = (HI_U8*)&u32Rndom[1];
    for (i=0; i<4; i++)
    {
        u16CRC = (u16CRC << 8) ^ s_u16CRC16Table[((u16CRC >> 8) ^ pu8Val[i]) & 0x00FF];
    }

    pu8Val = (HI_U8*)&u32Rndom[0];
    for (i=0; i<4; i++)
    {
        u16CRC = (u16CRC << 8) ^ s_u16CRC16Table[((u16CRC >> 8) ^ pu8Val[i]) & 0x00FF];
    }

    return u16CRC;
}

/*crc = CRC16(crc, 0)*/
static HI_U16 DRV_SM2_CRC16Zero(HI_U16 u32Initial, HI_U32 u32Len)
{
    HI_U32 i;
    HI_U16 u16CRC = 0x0000;

    u16CRC = u32Initial;

    for( i = 0; i < u32Len; i++)
    {
        u16CRC = (u16CRC << 8) ^ s_u16CRC16Table[((u16CRC >> 8) ^ 0x00) & 0x00FF];
    }

    return u16CRC;
}

#if 0
/*** Ring Shift Left ***/
static HI_U32 DRV_SM2_RSL(HI_U32 u32Val, HI_U32 u32Offset)
{
    HI_U32 u32Result;

    if ( u32Offset > 0)
    {
        u32Result = u32Val << u32Offset;
        u32Result |= u32Val >> (sizeof(u32Val)*8 - u32Offset);
    }
    else
    {
        u32Result = u32Val;
    }
    return u32Result;
}
#endif

#ifdef INT_ENABLE
static irqreturn_t DRV_SM2_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 u32Int;

    u32Int = HAL_SM2_GetInt();

    HI_INFO_CIPHER("INT: 0x%x\n", u32Int);

    if ((u32Int & 0x0C) == 0x0C)
    {
        g_bSm2Done = HI_TRUE;
        HI_INFO_CIPHER("Sm2 Done\n");
        cipher_queue_wait_up(&s_stSm2WaitQueue);
    }
    if ((u32Int & 0xF0) != 0xa0)
    {
        HI_ERR_CIPHER("ALARM: IP may be attacked by DFA !!!\n");
        HAL_SM2_DisableInt();
    }

    HAL_SM2_ClrInt();

    return IRQ_HANDLED;
}
#endif

HI_S32 DRV_SM2_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    cipher_mutex_init(&g_Sm2Mutex);

    g_u32Sm2Base = cipher_ioremap_nocache(CIPHER_SM2_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32Sm2Base == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache sm2 Reg failed\n");
        return HI_FAILURE;
    }

    g_u32Sm2Crg = cipher_ioremap_nocache(CIPHER_SM2_CRG_ADDR_PHY, 0x10);
    if (g_u32Sm2Crg == HI_NULL)
    {
        cipher_iounmap(g_u32Sm2Base);
        HI_ERR_CIPHER("ioremap_nocache sm2 Crg Reg failed\n");
        return HI_FAILURE;
    }

    DRV_SM2_CRC16Init();

#ifdef INT_ENABLE
    cipher_queue_init(&s_stSm2WaitQueue);

    /* request irq */
    ret = cipher_request_irq(SM2_IRQ_NUMBER, DRV_SM2_ISR, "sm2");
    if(HI_SUCCESS != ret)
    {
        HAL_SM2_DisableInt();
        HI_ERR_CIPHER("Irq request failure, ret=%#x.", ret);
        return HI_FAILURE;
    }
#endif

    HAL_SM2_Disable();

    return ret;
}

HI_VOID DRV_SM2_DeInit(HI_VOID)
{
#ifdef INT_ENABLE
    cipher_free_irq(SM2_IRQ_NUMBER, "sm2");
#endif

    HAL_SM2_Disable();

    cipher_iounmap(g_u32Sm2Base);
    cipher_iounmap(g_u32Sm2Crg);
}

static HI_S32 DRV_SM2_WaitDone(HI_BOOL bIsFast)
{
    HI_U32 u32ResFlag;
    HI_U32 u32ErrCode;

#ifdef INT_ENABLE
    if (0 == cipher_queue_wait_timeout(s_stSm2WaitQueue, g_bSm2Done != HI_FALSE, SM2_TIME_OUT))
    {
        HI_ERR_CIPHER("HAL_SM2_WaitDone() - time out! \n");
        HI_ERR_CIPHER("INT INFO: EN = 0x%x, STATUS = 0x%x, RAW = 0x%x, BUSY: 0x%x\n",
            HAL_SM2_GetIntEn(), HAL_SM2_GetInt(), HAL_SM2_GetRawInt(), HAL_SM2_GetBusy());
        return HI_FAILURE;
    }
#else
    HI_S32 ret = HI_SUCCESS;

    ret = HAL_SM2_WaitReady(bIsFast);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }
#endif

    u32ResFlag = HAL_SM2_GetResultFlag();
    if (u32ResFlag != 0x05)
    {
        u32ErrCode = HAL_SM2_GetFailureFlag() % 4;
        HI_ERR_CIPHER("SM2 operation failed: %s\n", s_ErrString[u32ErrCode]);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*c = a + b mod p*/
HI_S32 DRV_SM2_AddMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_ADD_MOD);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, u32p, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32b, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod add failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("AddMod-a", u32a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddMod-b", u32b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddMod-p", u32p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddMod-c", u32c, SM2_LEN_IN_WROD*4);
*/
    return ret;
}

/*c = a - b mod p*/
HI_S32 DRV_SM2_SubMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_SUB_MOD);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32b, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, u32p, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod sub failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("SubMod-a", u32a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("SubMod-b", u32b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("SubMod-p", u32p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("SubMod-c", u32c, SM2_LEN_IN_WROD*4);
*/
    return HI_SUCCESS;
}

/*c = a * b mod p*/
HI_S32 DRV_SM2_MulModp(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD],
                      HI_BOOL bIsPrivateKey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Random[2];
    HI_U32 u32Key[SM2_LEN_IN_WROD];
    HI_U16 u16CRC = 0, u16HardCRC = 0;
    HI_U32 i;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    memset(u32Key, 0, SM2_LEN_IN_BYTE);
    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_MOD);

    if(bIsPrivateKey)
    {
        u32Random[0] = random();
        u32Random[1] = random();

        for(i=0; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32b[i] ^ u32Random[1];
        }
        for(i=1; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32b[i] ^ u32Random[0];
        }
        u16CRC = DRV_SM2_CRC16Key(0x0000, u32Key);
        u16CRC = DRV_SM2_CRC16Rndom(u16CRC, u32Random);

        HAL_SM2_SetKeyRandom(u32Random);
        HAL_SM2_SetKeyCrc(u16CRC);
        HAL_SM2_OTPKeyEnable(HI_FALSE);

        HAL_SM2_PrivateKeyEnable(HI_TRUE);
    }
    else
    {
        HAL_SM2_PrivateKeyEnable(HI_FALSE);
        memcpy(u32Key, u32b, SM2_LEN_IN_BYTE);
    }

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32Key, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, s_u32p, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod mul failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_OTPKeyEnable(HI_FALSE);
    HAL_SM2_PrivateKeyEnable(HI_FALSE);

    u16HardCRC = HAL_SM2_GetCrc16();
    HI_INFO_CIPHER("Private KEY CRC: 0x%x\n", HAL_SM2_GetCrc16());
    if (bIsPrivateKey)
    {
        if (u16HardCRC != u16CRC)
        {
            HI_ERR_CIPHER("SM2 mod mul CRC error, soft crc: 0x%x, hard crc: 0x%x\n", u16CRC, u16HardCRC);
            return HI_FAILURE;
        }
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("MulModp-a", u32a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-b", u32b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-p", s_u32p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-c", u32c, SM2_LEN_IN_WROD*4);
*/
    return HI_SUCCESS;
}

/*c = a * b mod n*/
HI_S32 DRV_SM2_MulModn(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD],
                      HI_BOOL bIsPrivateKey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Random[2];
    HI_U32 u32Key[SM2_LEN_IN_WROD];
    HI_U16 u16CRC = 0, u16HardCRC = 0;
    HI_U32 i;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    memset(u32Key, 0, SM2_LEN_IN_BYTE);
    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_MOD);

    if(bIsPrivateKey)
    {

        u32Random[0] = random();
        u32Random[1] = random();

        for(i=0; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32b[i] ^ u32Random[1];
        }
        for(i=1; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32b[i] ^ u32Random[0];
        }
        u16CRC = DRV_SM2_CRC16Key(0x00, u32Key);
        u16CRC = DRV_SM2_CRC16Rndom(u16CRC, u32Random);

        HAL_SM2_SetKeyRandom(u32Random);
        HAL_SM2_SetKeyCrc(u16CRC);
        HAL_SM2_OTPKeyEnable(HI_FALSE);

        HAL_SM2_PrivateKeyEnable(HI_TRUE);
    }
    else
    {
        HAL_SM2_PrivateKeyEnable(HI_FALSE);
        memcpy(u32Key, u32b, SM2_LEN_IN_BYTE);
    }

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32Key, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, s_u32n, HI_FALSE);
//  HAL_SM2_SetWP(s_u32wn[SM2_LEN_IN_WROD - 2], s_u32wn[SM2_LEN_IN_WROD - 1]);

    HAL_SM2_OTPKeyEnable(HI_FALSE);
    HAL_SM2_PrivateKeyEnable(HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod mul failed\n");
        return HI_FAILURE;
    }

    u16HardCRC = HAL_SM2_GetCrc16();
    HI_INFO_CIPHER("Private KEY CRC: 0x%x\n", HAL_SM2_GetCrc16());
    if (bIsPrivateKey)
    {
        if (u16HardCRC != u16CRC)
        {
            HI_ERR_CIPHER("SM2 mod mul CRC error, soft crc: 0x%x, hard crc: 0x%x\n", u16CRC, u16HardCRC);
            return HI_FAILURE;
        }
    }
/*  else
    {
        u16CRC = DRV_SM2_CRC16Key(0x0000, u32Key);
        if (u16HardCRC != u16CRC)
        {
            HI_ERR_CIPHER("SM2 mod mul CRC error, soft crc: 0x%x, hard crc: 0x%x\n", u16CRC, u16HardCRC);
            return HI_FAILURE;
        }
    }*/

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("MulModp-a", u32a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-b", u32b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-p", s_u32n, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulModp-c", u32c, SM2_LEN_IN_WROD*4);
*/
    return HI_SUCCESS;
}

/*c = a^-1 mod p*/
HI_S32 DRV_SM2_InvMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_INV_MOD);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, u32p, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod inv failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("InvMod-a", u32a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("InvMod-p", u32p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("InvMod-c", u32c, SM2_LEN_IN_WROD*4);
*/
    return HI_SUCCESS;
}

/*c = a mod p*/
HI_S32 DRV_SM2_Mod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_MOD);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_NRAM, 0, u32p, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mod failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32c);
/*
    HI_PRINT_HEX ("mod-a", u32a, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mod-p", u32p, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mod-c", u32c, SM2_LEN_IN_BYTE);
*/
    return HI_SUCCESS;
}

/*c = a * b*/
HI_S32 DRV_SM2_Mul( const HI_U32 u32a[SM2_LEN_IN_WROD],
                    const HI_U32 u32b[SM2_LEN_IN_WROD],
                    HI_U32 u32c[SM2_LEN_IN_WROD*2])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_MUL);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_RRAM, 0, u32b, HI_FALSE);
    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mul failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_MRAM, 0, u32c);
/*
    HI_PRINT_HEX ("mul-a", u32a, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mul-b", u32b, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mul-c", u32c, SM2_LEN_IN_BYTE*2);
*/
    return HI_SUCCESS;
}

/*R = k ·P(x,y)*/
HI_S32 DRV_SM2_MulDot( const HI_U32 u32k[SM2_LEN_IN_WROD],
                    const HI_U32 u32Px[SM2_LEN_IN_WROD],
                    const HI_U32 u32Py[SM2_LEN_IN_WROD],
                    HI_U32 u32Rx[SM2_LEN_IN_WROD],
                    HI_U32 u32Ry[SM2_LEN_IN_WROD],
                    HI_BOOL bIsPrivateKey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Random[2];
    HI_U32 u32Key[SM2_LEN_IN_WROD];
    HI_U16 u16CRC = 0, u16HardCRC = 0;
    HI_U32 i;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    memset(u32Key, 0, SM2_LEN_IN_BYTE);
    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_DOT);

    if(bIsPrivateKey)
    {
        u32Random[0] = random();
        u32Random[1] = random();

        for(i=0; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32k[i] ^ u32Random[1];
        }
        for(i=1; i<SM2_LEN_IN_WROD; i+=2)
        {
           u32Key[i] =  u32k[i] ^ u32Random[0];
        }

        u16CRC = DRV_SM2_CRC16Key(u16CRC, u32Key);
        u16CRC = DRV_SM2_CRC16Rndom(u16CRC, u32Random);
        u16CRC = DRV_SM2_CRC16Zero(u16CRC, 56);

        HAL_SM2_SetKeyRandom(u32Random);
        HAL_SM2_SetKeyCrc(u16CRC);
        HAL_SM2_OTPKeyEnable(HI_FALSE);
        HAL_SM2_PrivateKeyEnable(HI_TRUE);
    }
    else
    {
        HAL_SM2_PrivateKeyEnable(HI_FALSE);
        memcpy(u32Key, u32k, SM2_LEN_IN_BYTE);
    }

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32Px, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 1, u32Py, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 2, s_u32n, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 3, s_u32b, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 0, u32Key, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 1, s_u32p, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 2, s_u32a, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 3, s_u32Gx, HI_TRUE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 4, s_u32Gy, HI_TRUE);

    HAL_SM2_OTPKeyEnable(HI_FALSE);
    HAL_SM2_PrivateKeyEnable(HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 mul dot failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_OTPKeyEnable(HI_FALSE);
    HAL_SM2_PrivateKeyEnable(HI_FALSE);

    u16HardCRC = HAL_SM2_GetCrc16();
    HI_INFO_CIPHER("Private KEY CRC: 0x%x\n", HAL_SM2_GetCrc16());
    if (bIsPrivateKey)
    {
        if (u16HardCRC != u16CRC)
        {
            HI_ERR_CIPHER("SM2 mod mul CRC error, soft crc: 0x%x, hard crc: 0x%x\n", u16CRC, u16HardCRC);
            return HI_FAILURE;
        }
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32Rx);
    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 1, u32Ry);
/*
    HI_PRINT_HEX ("MulDot-k", u32k, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Px", u32Px, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Py", u32Py, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Rx", u32Rx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Ry", u32Ry, SM2_LEN_IN_WROD*4);
    HI_PRINT("CRC: 0x%02X\n", HAL_SM2_GetCrc16());
*/
    return HI_SUCCESS;
}

/*C = S(x,y) + R(x,y)*/
HI_S32 DRV_SM2_AddDot( const HI_U32 u32Sx[SM2_LEN_IN_WROD],
                    const HI_U32 u32Sy[SM2_LEN_IN_WROD],
                    const HI_U32 u32Rx[SM2_LEN_IN_WROD],
                    const HI_U32 u32Ry[SM2_LEN_IN_WROD],
                    HI_U32 u32Cx[SM2_LEN_IN_WROD],
                    HI_U32 u32Cy[SM2_LEN_IN_WROD])
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(SM2_MODEA_SIZE, SM2_OPCODE_ADD_DOT);

    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 0, u32Sx, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_MRAM, 1, u32Sy, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 1, s_u32p, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 2, s_u32a, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 3, u32Rx, HI_FALSE);
    HAL_SM2_SetRAM(SM2_RAM_TYPE_KRAM, 4, u32Ry, HI_FALSE);

    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 dot add failed\n");
        return HI_FAILURE;
    }

    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 0, u32Cx);
    HAL_SM2_GetRAM(SM2_RAM_TYPE_RRAM, 1, u32Cy);
/*
    HI_PRINT_HEX ("AddDot-Sx", u32Sx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Sy", u32Sy, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Rx", u32Rx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Ry", u32Ry, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Cx", u32Cx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Cy", u32Ry, SM2_LEN_IN_WROD*4);
*/
    return HI_SUCCESS;
}

HI_S32 DRV_SM2_CleanRam(SM2_MODEA_S enModea)
{
    HI_S32 ret = HI_SUCCESS;

    g_bSm2Done = HI_FALSE;

    ret = HAL_SM2_WaitReady(HI_TRUE);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SM2 wait ready failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_SetMode(enModea, SM2_OPCODE_CLR_RAM);
    HAL_SM2_Start();

    ret = DRV_SM2_WaitDone(HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SM2 clean ram failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_U16 DRV_SM2_GetCRC16(HI_VOID)
{
    return HAL_SM2_GetCrc16();
}

static HI_S32 DRV_SM2_GetRandnum(HI_U32 u32Randnum[SM2_LEN_IN_WROD], const HI_U32 u32Max[SM2_LEN_IN_WROD])
{
    HI_U32 i = 0;

    if(g_pu8k == HI_NULL)
    {
        while(i < SM2_LEN_IN_WROD)
        {
            u32Randnum[i] = random();
            if (u32Randnum[i] <= u32Max[i])
            {
                i++;
            }
        }
    }
    else
    {
        memcpy(u32Randnum, g_pu8k, SM2_LEN_IN_BYTE);
    }

    return HI_SUCCESS;
}

/*check val whether zero or not*/
static HI_BOOL DRV_SM2_IsZero(const HI_U32 u32Val[SM2_LEN_IN_WROD])
{
    HI_U32 i = 0;

    for(i=0; i < SM2_LEN_IN_WROD; i++)
    {
        if (u32Val[i] != 0x00)
        {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

/*compare 2 val*/
static HI_S32 DRV_SM2_Cmp(const HI_U32 u32Val1[SM2_LEN_IN_WROD], const HI_U32 u32Val2[SM2_LEN_IN_WROD])
{
    HI_U32 i = 0;
    HI_U8 *p1;
    HI_U8 *p2;

    p1 = (HI_U8 *)u32Val1;
    p2 = (HI_U8 *)u32Val2;

    for(i=0; i < SM2_LEN_IN_WROD*4; i++)
    {
        if (p1[i] > p2[i])
        {
            return 1;
        }
        else if (p1[i] < p2[i])
        {
            return -1;
        }
    }

    return 0;
}

/*check val whether less than s_u32n1 or not*/
static HI_S32 DRV_SM2_RangCheck(const HI_U32 u32Val[SM2_LEN_IN_WROD])
{
    HI_U32 i = 0;
    const HI_U8 *pu8Val ;
    const HI_U8 *pu8n1;

    if (DRV_SM2_IsZero(u32Val))
    {
        return HI_FAILURE;
    }

    pu8Val = (HI_U8 *)u32Val;
    pu8n1 = (HI_U8 *)s_u32n1;

    for(i=0; i < SM2_LEN_IN_BYTE; i++)
    {
        if (pu8Val[i] < pu8n1[i])
        {
            return HI_SUCCESS;
        }
        else if (pu8Val[i] > pu8n1[i])
        {
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

/***************************************
  1. generate a randnum k, k∈[1,n-1],
  2. (x1,y1)=[k]G,
  3. r=(e+x1)mod n, if r=0 or r+k=n, return step 1
  4. s=((1+dA)^-1 ·(k-r·dA))mod n
****************************************/
HI_S32 DRV_SM2_Sign(SM2_SIGN_DATA_S *pSm2SignData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 *pu32Buf;
    HI_U32 *pu32m;
    HI_U32 *pu32k;
    HI_U32 *pu32Rx;
    HI_U32 *pu32Ry;
    HI_U32 *pu32ee;
    HI_U32 *pu32rk;
    HI_U32 *pu32my;
    HI_U32 *pu32mr;
    HI_U32 *pu32mk;
    HI_U32 *pu32mrk;
    HI_U32 *pu32mrky;
    HI_U32 *pu32TA;
    HI_U32 *pu32mTA;
    HI_U32 *pu32mTy;
    HI_U32 *pu32minv;
    HI_U32 *pu32mrk1;
    HI_U32 *pu32mrky1;
    HI_U32 *pu32rky1;
    HI_U32 *pu32mTz;
    HI_U32 *pu32ms;

    HI_U32 u32ReTry = 0;
    HI_U32 id  = 0;
    HI_U32 i,j;

    if( NULL == pSm2SignData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    pu32Buf = (HI_U32 *)cipher_malloc(SM2_LEN_IN_BYTE * 20);
    if( NULL == pu32Buf )
    {
        HI_ERR_CIPHER("Error! Malloc memory failed!\n");
        return HI_FAILURE;
    }

    pu32m    = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32k    = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32Rx   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32Ry   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32ee   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32rk   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32my   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mr   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mk   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mrk  = pu32Buf + SM2_LEN_IN_WROD * id++ ;//10
    pu32mrky = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32TA   = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mTA  = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mTy  = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32minv = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mrk1 = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mrky1= pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32rky1 = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32mTz  = pu32Buf + SM2_LEN_IN_WROD * id++ ;
    pu32ms   = pu32Buf + SM2_LEN_IN_WROD * id++ ;//20

    while(1)
    {
        if (u32ReTry++ > 10)
        {
            HI_ERR_CIPHER("Error! K is Invalid!\n");
            ret = HI_FAILURE;
            goto cleanup;
        }

        /************Step 1  ******************/
        HI_INFO_CIPHER("1. generate randnum k\n");
        for(i=0; i<8; i++)
        {
            SM2_CHECK(DRV_SM2_GetRandnum(pu32Buf + SM2_LEN_IN_WROD* i, s_u32n1));
        }
        j = random() & 0x07;
        memcpy(pu32k, pu32Buf + SM2_LEN_IN_WROD * j, SM2_LEN_IN_BYTE);
        SM2_DBG_MSG ("k", pu32k, SM2_LEN_IN_BYTE);

        /************Step 2 - 7 **************/
        HI_INFO_CIPHER("2. R=k*G\n");
        SM2_DBG_MSG("Gx", s_u32Gx, SM2_LEN_IN_BYTE);
        SM2_DBG_MSG("Gy", s_u32Gy, SM2_LEN_IN_BYTE);
        SM2_CHECK(DRV_SM2_MulDot(pu32k, s_u32Gx, s_u32Gy, pu32Rx, pu32Ry, HI_TRUE));
        SM2_DBG_MSG("Rx", pu32Rx, SM2_LEN_IN_BYTE);
        SM2_DBG_MSG("Ry", pu32Ry, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("3. e`=e+0 mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pSm2SignData->u32e, s_u320, s_u32n, pu32ee));
        SM2_DBG_MSG("e`", pu32ee, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("4. r=e`+Rx mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pu32ee, pu32Rx, s_u32n, pSm2SignData->u32r));
        SM2_DBG_MSG("r", pSm2SignData->u32r, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("5. r ?=0\n");
        if(DRV_SM2_IsZero(pSm2SignData->u32r))
        {
            continue;
        }
        HI_INFO_CIPHER("6. rk= r+k mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pSm2SignData->u32r, pu32k, s_u32n, pu32rk));
        SM2_DBG_MSG("rk", pu32rk, SM2_LEN_IN_BYTE);
        HI_INFO_CIPHER("7. rk ?=0\n");
        if(DRV_SM2_IsZero(pu32rk))
        {
            continue;
        }

        /************Step 8 - 13 **************/
        HI_INFO_CIPHER("8. generate randnum my\n");
        SM2_CHECK(DRV_SM2_GetRandnum(pu32my, s_u32n1));
        SM2_DBG_MSG("my", pu32my, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("9. mr=r*N mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pSm2SignData->u32r, s_u32N, pu32mr, HI_FALSE));
        SM2_DBG_MSG("mr", pu32mr, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("10. mk=k*N mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32k, s_u32N, pu32mk, HI_FALSE));
        SM2_DBG_MSG("mk", pu32mk, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("11. mrk = (mr + mk) mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pu32mr, pu32mk, s_u32n, pu32mrk));
        SM2_DBG_MSG("mrk", pu32mrk, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("12. mrky = (mrk * my) mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32mrk, pu32my, pu32mrky, HI_FALSE));
        SM2_DBG_MSG("mrky", pu32mrky, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("13. TA= dA*my mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32my, pSm2SignData->u32d, pu32TA, HI_TRUE));//????
        SM2_DBG_MSG("TA", pu32TA, SM2_LEN_IN_BYTE);

        /************Step 14 - 19 **************/
        HI_INFO_CIPHER("14. mTA = TA*N mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32TA, s_u32N, pu32mTA, HI_FALSE));
        SM2_DBG_MSG("mTA", pu32mTA, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("15. mTy = (mTA + my) mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pu32mTA, pu32my, s_u32n, pu32mTy));
        SM2_DBG_MSG("mTy", pu32mTy, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("16. minv = mTy^-1 mod n\n");
        SM2_CHECK(DRV_SM2_InvMod(pu32mTy, s_u32n, pu32minv));
        SM2_DBG_MSG("minv", pu32minv, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("17. mrk1 = (mr + mk) mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pu32mr, pu32mk, s_u32n, pu32mrk1));
        SM2_DBG_MSG("mrk1", pu32mrk1, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("18. mrky1 = (mrk1 * my) mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32mrk1, pu32my, pu32mrky1, HI_FALSE));
        SM2_DBG_MSG("mrky1", pu32mrky1, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("19. mrky1 ?= mrky\n");
        if (DRV_SM2_Cmp(pu32mrky1, pu32mrky) != 0)
        {
            HI_ERR_CIPHER("Error! mrky1 != mrky!\n");
            ret = HI_FAILURE;
            goto cleanup;
        }

        /************Step 20 - 25 **************/
        HI_INFO_CIPHER("20. mTz = (mrky * minv) mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32mrky, pu32minv, pu32mTz, HI_FALSE));
        SM2_DBG_MSG("mTz", pu32mTz, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("21. ms = (mTz - mr) mod n\n");
        SM2_CHECK(DRV_SM2_SubMod(pu32mTz, pu32mr, s_u32n, pu32ms));
        SM2_DBG_MSG("ms", pu32ms, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("22. ms ?=0\n");
        if(DRV_SM2_IsZero(pu32ms))
        {
            continue;
        }
        HI_INFO_CIPHER("23. s=ms*1 mod n\n");
        SM2_CHECK(DRV_SM2_MulModn(pu32ms, s_u321, pSm2SignData->u32s, HI_FALSE));
        SM2_DBG_MSG("s", pSm2SignData->u32s, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("24. rk= r+k mod n\n");
        SM2_CHECK(DRV_SM2_AddMod(pSm2SignData->u32r, pu32k, s_u32n, pu32rk));
        SM2_DBG_MSG("rk", pu32rk, SM2_LEN_IN_BYTE);

        HI_INFO_CIPHER("25. rk ?=0\n");
        if(DRV_SM2_IsZero(pu32rk))
        {
            continue;
        }

        break;
    }

cleanup:

    (HI_VOID)DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);
    memset(pu32Buf, 0, SM2_LEN_IN_BYTE * 20);
    cipher_free(pu32Buf);

    HI_INFO_CIPHER("DRV_SM2_Sign end\n");

    return ret;
}

/***************************************
  1. t=(r+s)mod n, if t==0, return fail
  2. (x1,y1)=[s]G+tP,
  3. r=(e+x1)mod n, if r==R, return pass
****************************************/
HI_S32 DRV_SM2_Verify(SM2_VERIFY_DATA_S *pSm2VerifyData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32t[SM2_LEN_IN_WROD];
    HI_U32 u32sGx[SM2_LEN_IN_WROD];
    HI_U32 u32sGy[SM2_LEN_IN_WROD];
    HI_U32 u32tPAx[SM2_LEN_IN_WROD];
    HI_U32 u32tPAy[SM2_LEN_IN_WROD];
    HI_U32 u32Rx[SM2_LEN_IN_WROD];
    HI_U32 u32Ry[SM2_LEN_IN_WROD];
    HI_U32 u32ee[SM2_LEN_IN_WROD];
    HI_U32 u32v[SM2_LEN_IN_WROD];

    if( NULL == pSm2VerifyData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    memset(u32t, 0, sizeof(u32t));
    memset(u32sGx, 0, sizeof(u32sGx));
    memset(u32sGy, 0, sizeof(u32sGy));
    memset(u32tPAx, 0, sizeof(u32tPAx));
    memset(u32tPAy, 0, sizeof(u32tPAy));
    memset(u32Rx, 0, sizeof(u32Rx));
    memset(u32Ry, 0, sizeof(u32Ry));
    memset(u32ee, 0, sizeof(u32ee));
    memset(u32v, 0, sizeof(u32v));

    SM2_CHECK(DRV_SM2_RangCheck(pSm2VerifyData->u32r));                         /*1<=r<=n-1*/
    SM2_CHECK(DRV_SM2_RangCheck(pSm2VerifyData->u32s));                         /*1<=s<=n-1*/
    SM2_CHECK(DRV_SM2_AddMod(pSm2VerifyData->u32r, pSm2VerifyData->u32s, s_u32n, u32t)); /*t=r+s mod n*/
    if(DRV_SM2_IsZero(u32t))                                                    /*t = 0 ?*/
    {
        HI_ERR_CIPHER("Error! t is zero!\n");
        return HI_FAILURE;
    }

    SM2_CHECK(DRV_SM2_MulDot(pSm2VerifyData->u32s, s_u32Gx, s_u32Gy, u32sGx, u32sGy, HI_FALSE));   /*sG=s*G*/
    SM2_CHECK(DRV_SM2_MulDot(u32t, pSm2VerifyData->u32Px, pSm2VerifyData->u32Py, u32tPAx, u32tPAy, HI_FALSE)); /*tPA=t*PA*/
    SM2_CHECK(DRV_SM2_AddDot(u32sGx, u32sGy, u32tPAx, u32tPAy, u32Rx, u32Ry));           /*R=sG+tPA*/
    SM2_CHECK(DRV_SM2_AddMod(pSm2VerifyData->u32e, s_u320, s_u32n, u32ee));              /*e`=e+0 mod n*/
    SM2_CHECK(DRV_SM2_AddMod(u32ee, u32Rx, s_u32n, u32v));                               /*v=e`+Rx mod n*/
    if (DRV_SM2_Cmp(pSm2VerifyData->u32r, u32v) == 0)                                    /*v = r ?*/
    {
        ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_CIPHER("Error! r != v!\n");
        ret = HI_FAILURE;
    }

cleanup:

    ret = DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);

    return ret;
}

/* Compute C1(x, y) = k * G(x, y), XY = k * P(x, y)*/
HI_S32 DRV_SM2_Encrypt(SM2_ENC_DATA_S *pSm2EncData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32k[SM2_LEN_IN_WROD];
    HI_U32 u32ReTry = 0;

    if( NULL == pSm2EncData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    if(DRV_SM2_IsZero(pSm2EncData->u32Px) && DRV_SM2_IsZero(pSm2EncData->u32Py))                                                    /*t = 0 ?*/
    {
        HI_ERR_CIPHER("Error! PB is zero!\n");
        return HI_FAILURE;
    }

    while(1)
    {
        if (u32ReTry++ > 10)
        {
            HI_ERR_CIPHER("Error! K is Invalid!\n");
            ret =  HI_FAILURE;
            goto cleanup;
        }
        SM2_CHECK(DRV_SM2_GetRandnum(u32k, s_u32n1));                               /*generate randnum k, 1<=k<=n-1*/
        SM2_CHECK(DRV_SM2_MulDot(u32k, s_u32Gx, s_u32Gy, pSm2EncData->u32C1x, pSm2EncData->u32C1y, HI_FALSE));                                                  /*C1=k*G*/
        if(DRV_SM2_IsZero(pSm2EncData->u32C1x) && DRV_SM2_IsZero(pSm2EncData->u32C1y))                                                    /*t = 0 ?*/
        {
            continue;
        }

        SM2_CHECK(DRV_SM2_MulDot(u32k, pSm2EncData->u32Px, pSm2EncData->u32Py,
            pSm2EncData->u32X2, pSm2EncData->u32Y2, HI_FALSE));                               /*kPB=k*PB*/
        if(DRV_SM2_IsZero(pSm2EncData->u32X2) && DRV_SM2_IsZero(pSm2EncData->u32Y2))                                                    /*t = 0 ?*/
        {
            continue;
        }
        break;
    }

cleanup:

    (HI_VOID)DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);

    return ret;
}

/*check y^2=x^3+ax+b ? */
static HI_S32 DRV_SM2_DotCheck(HI_U32 u32X[SM2_LEN_IN_WROD], HI_U32 u32Y[SM2_LEN_IN_WROD], HI_BOOL bIsMulDotCheck)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32mx[SM2_LEN_IN_WROD];
    HI_U32 u32my[SM2_LEN_IN_WROD];
    HI_U32 u32mx2[SM2_LEN_IN_WROD];
    HI_U32 u32mx3[SM2_LEN_IN_WROD];
    HI_U32 u32max[SM2_LEN_IN_WROD];
    HI_U32 u32mt[SM2_LEN_IN_WROD];
    HI_U32 u32ms[SM2_LEN_IN_WROD];
    HI_U32 u32my2[SM2_LEN_IN_WROD];

    if(DRV_SM2_IsZero(u32X) && DRV_SM2_IsZero(u32Y))                                                    /*t = 0 ?*/
    {
        HI_ERR_CIPHER("Error! X or Y is zero!\n");
        return HI_FAILURE;
    }

    memset(u32mx, 0, sizeof(u32mx));
    memset(u32my, 0, sizeof(u32my));
    memset(u32mx2, 0, sizeof(u32mx2));
    memset(u32mx3, 0, sizeof(u32mx3));
    memset(u32max, 0, sizeof(u32max));
    memset(u32mt, 0, sizeof(u32mt));
    memset(u32ms, 0, sizeof(u32ms));
    memset(u32my2, 0, sizeof(u32my2));

    HI_INFO_CIPHER("1. ma = a*P mod p\n");
    HI_INFO_CIPHER("2. mb = b*P mod p\n");
    HI_INFO_CIPHER("3. mx=C1x*P mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(u32X, s_u32P, u32mx, HI_FALSE));
    HI_INFO_CIPHER("4. my=C1y*P mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(u32Y, s_u32P, u32my, HI_FALSE));
    HI_INFO_CIPHER("5. mx2=mx* mx mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(u32mx, u32mx, u32mx2, HI_FALSE));
    HI_INFO_CIPHER("6. mx3=mx2* mx mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(u32mx2, u32mx, u32mx3, HI_FALSE));
    HI_INFO_CIPHER("7. max=ma*mx mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(s_u32ma, u32mx, u32max, HI_FALSE));
    HI_INFO_CIPHER("8. mt= mx3+max mod p\n");
    SM2_CHECK(DRV_SM2_AddMod(u32mx3, u32max, s_u32p, u32mt));
    HI_INFO_CIPHER("9. ms= mt+mb mod p\n");
    SM2_CHECK(DRV_SM2_AddMod(u32mt, s_u32mb, s_u32p, u32ms));
    HI_INFO_CIPHER("10. my2=my*my mod p\n");
    SM2_CHECK(DRV_SM2_MulModp(u32my, u32my, u32my2, HI_FALSE));
    HI_INFO_CIPHER("11. my2 ?= ms\n");
    if (DRV_SM2_Cmp(u32ms, u32my2) != 0)
    {
        HI_ERR_CIPHER("Error! my2 != s!\n");
        ret =  HI_FAILURE;
        goto cleanup;
    }

    if (bIsMulDotCheck)
    {
        HI_INFO_CIPHER("12. S= h * C1\n");
        SM2_CHECK(DRV_SM2_MulDot(s_u321, u32X, u32Y, u32mx, u32my, HI_FALSE));
    }
cleanup:

    (HI_VOID)DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);

    return ret;
}

/*Compute M(x, y) = C1(x, y) * d*/
HI_S32 DRV_SM2_Decrypt(SM2_DEC_DATA_S *pSm2DecData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Mx[SM2_LEN_IN_WROD];
    HI_U32 u32My[SM2_LEN_IN_WROD];

    if( NULL == pSm2DecData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    if(DRV_SM2_IsZero(pSm2DecData->u32C1x) && DRV_SM2_IsZero(pSm2DecData->u32C1x))                                                    /*t = 0 ?*/
    {
        HI_ERR_CIPHER("Error! C1 is zero!\n");
        return HI_FAILURE;
    }

    /*check C1y^2=C1x^3+aC1x+b ? */
    SM2_CHECK(DRV_SM2_DotCheck(pSm2DecData->u32C1x, pSm2DecData->u32C1y, HI_TRUE));

    /*Compute M(x,y)*/
    SM2_CHECK(DRV_SM2_MulDot(pSm2DecData->u32d, pSm2DecData->u32C1x, pSm2DecData->u32C1y,
                u32Mx, u32My, HI_TRUE));

//    HI_PRINT_HEX ("Mx", u32Mx, 32);
//    HI_PRINT_HEX ("My", u32My, 32);

    /*check C1y^2=C1x^3+aC1x+b ? */
    SM2_CHECK(DRV_SM2_DotCheck(pSm2DecData->u32C1x, pSm2DecData->u32C1y, HI_TRUE));

    /*check My^2=Mx^3+aMx+b ? */
    SM2_CHECK(DRV_SM2_DotCheck(u32Mx, u32My, HI_FALSE));

    memcpy(pSm2DecData->u32X2, u32Mx, SM2_LEN_IN_BYTE);
    memcpy(pSm2DecData->u32Y2, u32My, SM2_LEN_IN_BYTE);

cleanup:

    memset(u32Mx, 0, SM2_LEN_IN_BYTE);
    memset(u32My, 0, SM2_LEN_IN_BYTE);
    (HI_VOID)DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);

    return ret;
}

/*Compute P(x,y) = d * G(x,y)*/
HI_S32 DRV_SM2_Key(SM2_KEY_DATA_S *pSm2KeyData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i,j;
    HI_U32 au32Random[8][SM2_LEN_IN_WROD];

    if( NULL == pSm2KeyData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_FAILURE;
    }

    HI_INFO_CIPHER ("Step 1. generate randnum d, 1<=k<=n-2");
    for(i=0; i<8; i++)
    {
        SM2_CHECK(DRV_SM2_GetRandnum(au32Random[i], s_u32n1));
    }
    j = random() & 0x07;
    memcpy(pSm2KeyData->u32d, au32Random[j], SM2_LEN_IN_BYTE);

    HI_INFO_CIPHER ("Step 2. PA=dA*G");
    SM2_CHECK(DRV_SM2_MulDot(pSm2KeyData->u32d, s_u32Gx, s_u32Gy, pSm2KeyData->u32Px,
        pSm2KeyData->u32Py, HI_TRUE)); /*P = d * G*/

cleanup:

    (HI_VOID)DRV_SM2_CleanRam(SM2_MODEA_CLR_ALLRAM);

    return ret;
}

HI_S32 HI_DRV_SM2_Sign(SM2_SIGN_DATA_S *pSm2SignData)
{
    HI_S32 ret = HI_SUCCESS;

    if(cipher_mutex_lock(&g_Sm2Mutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_Enable();

    ret = DRV_SM2_Sign(pSm2SignData);

    HAL_SM2_Disable();

    cipher_mutex_unlock(&g_Sm2Mutex);
    return ret;
}

HI_S32 HI_DRV_SM2_Verify(SM2_VERIFY_DATA_S *pSm2VerifyData)
{
    HI_S32 ret = HI_SUCCESS;

    if(cipher_mutex_lock(&g_Sm2Mutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_Enable();

    ret = DRV_SM2_Verify(pSm2VerifyData);

    HAL_SM2_Disable();

    cipher_mutex_unlock(&g_Sm2Mutex);

    return ret;
}

HI_S32 HI_DRV_SM2_Encrypt(SM2_ENC_DATA_S *pSm2EncData)
{
    HI_S32 ret = HI_SUCCESS;

    if(cipher_mutex_lock(&g_Sm2Mutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_Enable();

    ret = DRV_SM2_Encrypt(pSm2EncData);

    HAL_SM2_Disable();

    cipher_mutex_unlock(&g_Sm2Mutex);
    return ret;
}

HI_S32 HI_DRV_SM2_Decrypt(SM2_DEC_DATA_S *pSm2DecData)
{
    HI_S32 ret = HI_SUCCESS;

    if(cipher_mutex_lock(&g_Sm2Mutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_Enable();

    ret = DRV_SM2_Decrypt(pSm2DecData);

    HAL_SM2_Disable();

    cipher_mutex_unlock(&g_Sm2Mutex);
    return ret;
}

HI_S32 HI_DRV_SM2_Key(SM2_KEY_DATA_S *pSm2KeyData)
{
    HI_S32 ret = HI_SUCCESS;

    if(cipher_mutex_lock(&g_Sm2Mutex))
    {
        HI_ERR_CIPHER("cipher_mutex_lock failed!\n");
        return HI_FAILURE;
    }

    HAL_SM2_Enable();

    ret = DRV_SM2_Key(pSm2KeyData);

    HAL_SM2_Disable();

    cipher_mutex_unlock(&g_Sm2Mutex);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

