/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"
#include "drv_rng.h"
#include "drv_rsa.h"

static HI_VOID *g_u32RsaRegCrg = HI_NULL;
#ifdef IFEP_RSA_ENABLE
/**************************** IFEP RSA ***************************/

#define RSA_INTERRUPT_ENABLE
#define RSA_IRQ_NUMBER                 (79 + 32)

HI_VOID *g_u32RsaRegBase = HI_NULL;

#define CIPHER_RSA_REG_BASE_RSA                  g_u32RsaRegBase
#define SEC_RSA_BUSY_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x50)
#define SEC_RSA_MOD_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x54)
#define SEC_RSA_WSEC_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x58)
#define SEC_RSA_WDAT_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x5c)
#define SEC_RSA_RPKT_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x60)
#define SEC_RSA_RRSLT_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x64)
#define SEC_RSA_START_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x68)
#define SEC_RSA_ADDR_REG                          (CIPHER_RSA_REG_BASE_RSA + 0x6C)
#define SEC_RSA_ERROR_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x70)
#define SEC_RSA_CRC16_REG                         (CIPHER_RSA_REG_BASE_RSA + 0x74)
#define SEC_RSA_KEY_RANDOM_1                      (CIPHER_RSA_REG_BASE_RSA + 0x7c)
#define SEC_RSA_INT_EN                            (CIPHER_RSA_REG_BASE_RSA + 0x80)
#define SEC_RSA_INT_STATUS                        (CIPHER_RSA_REG_BASE_RSA + 0x84)
#define SEC_RSA_INT_RAW                           (CIPHER_RSA_REG_BASE_RSA + 0x88)
#define SEC_RSA_INT_ERR_CLR                       (CIPHER_RSA_REG_BASE_RSA + 0x8c)
#define SEC_RSA_KEY_RANDOM_2                      (CIPHER_RSA_REG_BASE_RSA + 0x94)

#define RSA_DATA_CLR               (7<<4)
#define RSA_DATA_CLR_KEY           (1<<4)
#define RSA_DATA_CLR_INPUT         (2<<4)
#define RSA_DATA_CLR_OUTPUT        (4<<4)
#define RSA_MOD_SEL                (3 << 0)
#define RSA_MOD_SEL_OPT            (0 << 0)
#define RSA_MOD_SEL_KEY_UPDATA     (1 << 0)
#define RSA_MOD_SEL_RAM_CLAER      (2 << 0)
#define RSA_MOD_SEL_CRC16          (3 << 0)
#define RSA_BUSY                   (1 << 0)
#define RSA_START                  (1 << 0)

#define RSA_RTY_CNT             50000
#define RSA_TIME_OUT            1000


#define CRC16_POLYNOMIAL               0x1021
#define CPU_TO_BE32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))

typedef enum hiCIPHER_INT_TYPE_E
{
    CIPHER_INT_TYPE_IN_BUF  =                     0x1,
    CIPHER_INT_TYPE_OUT_BUF =                     0x2,
} CIPHER_INT_TYPE_E;

typedef enum hiCIPHER_BUF_TYPE_E
{
    CIPHER_BUF_TYPE_IN  =                         0x1,
    CIPHER_BUF_TYPE_OUT =                         0x2,
} CIPHER_BUF_TYPE_E;

typedef enum hiCIPHER_RSA_DATA_TYPE_E
{
    CIPHER_RSA_DATA_TYPE_CONTEXT,
    CIPHER_RSA_DATA_TYPE_MODULE,
    CIPHER_RSA_DATA_TYPE_KEY,
} CIPHER_RSA_DATA_TYPE_E;

typedef enum hiCIPHER_RSA_KEY_WIDTH_E
{
    CIPHER_RSA_KEY_WIDTH_1K = 0x00,
    CIPHER_RSA_KEY_WIDTH_2K = 0x01,
    CIPHER_RSA_KEY_WIDTH_4K = 0x02,
    CIPHER_RSA_KEY_WIDTH_3K = 0x03,
}CIPHER_RSA_KEY_WIDTH_E;

HI_VOID *g_RsaMutex;
static HI_U32 g_bRsaDone = HI_FALSE;
static HI_U16 s_CrcTable[256];

HI_VOID HAL_RSA_Start(HI_VOID)
{
    HAL_CIPHER_WriteReg(SEC_RSA_START_REG, 0x05);
}

HI_S32 HAL_RSA_WaitFree(HI_VOID)
{
    HI_U32 u32Value;
    HI_U32 u32TryCount = 0;

    do
    {
        HAL_CIPHER_ReadReg(SEC_RSA_BUSY_REG, &u32Value);
        if ((u32Value & RSA_BUSY) == 0)
        {
            return HI_SUCCESS;
        }
        u32TryCount++;
        cipher_msleep(1);
    } while (u32TryCount < RSA_RTY_CNT);

    return HI_FAILURE;
}

HI_VOID HAL_RSA_ClearRam(HI_VOID)
{
    HI_U32 u32Value;

    HAL_CIPHER_ReadReg(SEC_RSA_MOD_REG, &u32Value);
    u32Value &= 0x0c;
    u32Value |= RSA_DATA_CLR_INPUT | RSA_DATA_CLR_OUTPUT | RSA_DATA_CLR_KEY | RSA_MOD_SEL_RAM_CLAER;
    HAL_CIPHER_WriteReg(SEC_RSA_MOD_REG, u32Value);
}

HI_VOID HAL_RSA_Crc(HI_VOID)
{
    HI_U32 u32Value;

    HAL_CIPHER_ReadReg(SEC_RSA_MOD_REG, &u32Value);
    u32Value &= 0x0C; //don't chang sec_rsa_key_width
    u32Value |= 0x03;
    HAL_CIPHER_WriteReg(SEC_RSA_MOD_REG, u32Value);
}

HI_VOID HAL_RSA_GetCrc(HI_U32 *pu32Crc)
{
    HAL_CIPHER_ReadReg(SEC_RSA_CRC16_REG, pu32Crc);
}

HI_VOID HAL_RSA_ConfigMode(CIPHER_RSA_KEY_WIDTH_E enKenWidth)
{
    HI_U32 u32Value;

    u32Value = (enKenWidth << 2) | RSA_MOD_SEL_OPT;
    HAL_CIPHER_WriteReg(SEC_RSA_MOD_REG, u32Value);
}

HI_VOID HAL_RSA_SetCRC(HI_U16 u16Crc)
{
    HAL_CIPHER_WriteReg(SEC_RSA_CRC16_REG, u16Crc);
}

HI_VOID HAL_RSA_SetRandom(HI_U32 u32Rnadom[2])
{
    HAL_CIPHER_WriteReg(SEC_RSA_KEY_RANDOM_1, (u32Rnadom[0]));
    HAL_CIPHER_WriteReg(SEC_RSA_KEY_RANDOM_2, (u32Rnadom[1]));
}

HI_VOID HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_E enDataType, HI_U8 *pu8Data,
                          HI_U32 u32DataLen, HI_U32 u32Len, HI_U32 u32Rnadom[2])
{
    HI_U32 u32Value;
    HI_U32 *u32Reg;
    HI_U8 *pPos;
    HI_U32 i= 0;
    HI_BOOL id = 0;

    if (enDataType == CIPHER_RSA_DATA_TYPE_CONTEXT)
    {
        u32Reg = SEC_RSA_WDAT_REG;
    }
    else
    {
        u32Reg = SEC_RSA_WSEC_REG;
    }

    pPos = pu8Data;
    for(i=0; i<u32Len; i+=4)
    {
        u32Value  = (HI_U32)pPos[0];
        u32Value |= ((HI_U32)pPos[1]) << 8;
        u32Value |= ((HI_U32)pPos[2]) << 16;
        u32Value |= ((HI_U32)pPos[3]) << 24;
        if (enDataType != CIPHER_RSA_DATA_TYPE_CONTEXT)
        {
            u32Value ^= u32Rnadom[id];
        }
        HAL_CIPHER_WriteReg(u32Reg, u32Value);
        pPos+=4;
        id ^= 0x01;
    }
}

HI_VOID HAL_RSA_ReadData(HI_U8 *pu8Data, HI_U32 u32DataLen, HI_U32 u32Klen)
{
    HI_U32 u32Value;
    HI_U8 *pPos;
    HI_U32 i = 0;

    pPos = pu8Data;
   /*
    for(i=0; i<(u32Klen - u32DataLen); i+=4)
    {
        HAL_CIPHER_ReadReg(SEC_RSA_RRSLT_REG, &u32Value);
    }*/
    for(i=0; i<u32Klen; i+=4)
    {
        HAL_CIPHER_ReadReg(SEC_RSA_RRSLT_REG, &u32Value);
        pPos[0] = (HI_U8)(u32Value & 0xFF);
        pPos[1] = (HI_U8)((u32Value >> 8) & 0xFF);
        pPos[2] = (HI_U8)((u32Value >> 16) & 0xFF);
        pPos[3] = (HI_U8)((u32Value >> 24) & 0xFF);
        pPos+=4;
    }
}

HI_U32 HAL_RSA_GetErrorCode(HI_VOID)
{
    HI_U32 u32Value;

    HAL_CIPHER_ReadReg(SEC_RSA_ERROR_REG, &u32Value);

    return u32Value;
}

HI_VOID HAL_RSA_ClrInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SEC_RSA_INT_RAW, 0x01);
    (HI_VOID)HAL_CIPHER_WriteReg(SEC_RSA_INT_ERR_CLR, 0x01);
}

HI_U32 HAL_RSA_GetInt(HI_VOID)
{
    HI_U32 u32Int;

    (HI_VOID)HAL_CIPHER_ReadReg(SEC_RSA_INT_STATUS, &u32Int);

    return u32Int;
}

HI_U32 HAL_RSA_GetRawInt(HI_VOID)
{
    HI_U32 u32Int;

    (HI_VOID)HAL_CIPHER_ReadReg(SEC_RSA_INT_RAW, &u32Int);

    return u32Int;
}

HI_VOID HAL_RSA_EnableInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SEC_RSA_INT_EN, 0x80000001);
}

HI_VOID HAL_RSA_DisableInt(HI_VOID)
{
    (HI_VOID)HAL_CIPHER_WriteReg(SEC_RSA_INT_EN, 0x00);
}

HI_VOID HAL_RSA_Enable(HI_VOID)
{
    HI_U32 Value;

    HAL_CIPHER_ReadReg(g_u32RsaRegCrg, &Value);
    HAL_SET_BIT(Value, 16); /* clock opened */
    HAL_CIPHER_WriteReg(g_u32RsaRegCrg,Value);
    cipher_msleep(1);

    HAL_CLEAR_BIT(Value, 15); /* cancel reset */
    HAL_CIPHER_WriteReg(g_u32RsaRegCrg,Value);

#ifdef INT_ENABLE
    HAL_RSA_EnableInt();
#endif
}

HI_VOID HAL_RSA_Disable(HI_VOID)
{
    HI_U32 Value;

    HAL_CIPHER_ReadReg(g_u32RsaRegCrg, &Value);

    HAL_SET_BIT(Value, 15); /* reset */
    HAL_CIPHER_WriteReg(g_u32RsaRegCrg,Value);
    cipher_msleep(1);

    HAL_CLEAR_BIT(Value, 16); /* clock closed */
    HAL_CIPHER_WriteReg(g_u32RsaRegCrg,Value);
}

static HI_VOID  DRV_RSA_Crc16Init(HI_VOID)
{
    HI_U16 nRemainder;
    HI_U16 n, m;
    HI_U16  *pulTable = s_CrcTable;

    for(n = 0; n < 256; n ++)
    {
        nRemainder = (HI_U16)n << 8;
        for(m = 8; m > 0; m --)
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
        *(pulTable + n) = nRemainder;
    }
}

static HI_U16 DRV_RSA_CRC16_BLOCK(HI_U16 crc, HI_U8 block[8], HI_U8 u32Rnadom[8])
{
    HI_U8 i, j;
    HI_U8 val;

    for(i=0; i<2; i++)
    {
        for(j=0; j<4; j++)
        {
            val = block[i*4+3-j] ^ u32Rnadom[i*4+3-j];
            crc = (crc<<8) ^ s_CrcTable[((crc>>8) ^ val) & 0xFF];
        }
    }

    return crc;
}

static HI_U16 DRV_RSA_KeyCRC(HI_U8 *pu8N, HI_U8 *pu8K, HI_U32 u32Klen, HI_U32 u32Rnadom[2])
{
    HI_U32 i;
    HI_U16 crc = 0;

    for(i=0; i<u32Klen; i+=8)
    {
        crc = DRV_RSA_CRC16_BLOCK(crc, pu8N+i, (HI_U8*)u32Rnadom);
    }
    for(i=0; i<u32Klen; i+=8)
    {
        crc = DRV_RSA_CRC16_BLOCK(crc, pu8K+i, (HI_U8*)u32Rnadom);
    }

    return crc;
}

#ifdef INT_ENABLE
cipher_queue_head s_stRsaWaitQueue;

static irqreturn_t DRV_RSA_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 u32Int;

    u32Int = HAL_RSA_GetInt();

    HI_INFO_CIPHER("RSA INT: 0x%x\n", u32Int);

    if (u32Int & 01)
    {
        g_bRsaDone = HI_TRUE;
        HI_INFO_CIPHER("RSA Done\n");
        cipher_queue_wait_up(&s_stRsaWaitQueue);
    }

    HAL_RSA_ClrInt();

    return IRQ_HANDLED;
}
#endif

HI_S32 DRV_IFEP_RSA_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    cipher_mutex_init(&g_RsaMutexKernel);

    g_u32RsaRegBase = cipher_ioremap_nocache(CIPHER_RSA_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32RsaRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache rsa Reg failed\n");
        return HI_FAILURE;
    }

#ifdef INT_ENABLE
    /* request irq */
    ret = cipher_request_irq(RSA_IRQ_NUMBER, DRV_RSA_ISR, "rsa");
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Irq request failure, ret=%#x.", ret);
        return HI_FAILURE;
    }
    cipher_queue_init(&s_stRsaWaitQueue);
#endif

    HAL_RSA_Disable();

    DRV_RSA_Crc16Init();

    return ret;
}

HI_VOID DRV_IFEP_RSA_DeInit(HI_VOID)
{

#ifdef INT_ENABLE
    cipher_free_irq(RSA_IRQ_NUMBER, "rsa");
    cipher_queue_init(&s_stRsaWaitQueue);
#endif

    HAL_RSA_Disable();

    cipher_iounmap(g_u32RsaRegBase);
}

HI_S32 DRV_RSA_WaitDone(HI_VOID)
{
#ifdef INT_ENABLE
    if (0 == wait_event_interruptible_timeout(s_stRsaWaitQueue, g_bRsaDone != HI_FALSE, RSA_TIME_OUT))
    {
        HI_ERR_CIPHER("RSA time out! \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
#else
    return HAL_RSA_WaitFree();
#endif
}

HI_S32 DRV_CIPHER_CheckRsaData(HI_U8 *N, HI_U8 *E, HI_U8 *MC, HI_U32 u32Len)
{
    HI_U32 i;

    /*MC > 0*/
    for(i=0; i<u32Len; i++)
    {
        if(MC[i] > 0)
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA M/C is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*MC < N*/
    for(i=0; i<u32Len; i++)
    {
        if(MC[i] < N[i])
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA M/C is larger than N, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*E >= 1*/
    for(i=0; i<u32Len; i++)
    {
        if(E[i] > 0)
        {
            break;
        }
    }
    if(i>=u32Len)
    {
        HI_ERR_CIPHER("RSA D/E is zero, error!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

//    HI_PRINT_HEX("N", N, u32Len);
//    HI_PRINT_HEX("K", E, u32Len);

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_ClearRsaRam(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    g_bRsaDone = HI_FALSE;

    HAL_RSA_ClearRam();
    HAL_RSA_Start();
    ret = DRV_RSA_WaitDone();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_CalcRsaCrc(HI_U16 *pu16Crc)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Val;

    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    g_bRsaDone = HI_FALSE;

    HAL_RSA_Crc();
    HAL_RSA_Start();
    ret = DRV_RSA_WaitDone();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        return HI_FAILURE;
    }

    HAL_RSA_GetCrc(&u32Val);

    *pu16Crc = (HI_U16)u32Val;

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_IFEP_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ErrorCode;
    HI_U32 u32KeyLen;
    CIPHER_RSA_KEY_WIDTH_E enKeyWidth;
    HI_U32 u32Rnadom[2];
    HI_U16 u16CrC;

    if ((pCipherRsaData->pu8Input == HI_NULL) ||(pCipherRsaData->pu8Output== HI_NULL)
        || (pCipherRsaData->pu8N == HI_NULL) || (pCipherRsaData->pu8K == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if ((pCipherRsaData->u16NLen == 0) || (pCipherRsaData->u16KLen == 0))
    {
        HI_ERR_CIPHER("RSA K size is zero.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pCipherRsaData->u32DataLen != pCipherRsaData->u16NLen)
    {
        HI_ERR_CIPHER("Error, DataLen != u16NLen!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (pCipherRsaData->u16NLen <= 128)
    {
        u32KeyLen = 128;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_1K;
    }
    else if (pCipherRsaData->u16NLen <= 256)
    {
        u32KeyLen = 256;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_2K;
    }
    else if (pCipherRsaData->u16NLen <= 384)
    {
        u32KeyLen = 384;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_3K;
    }
    else if (pCipherRsaData->u16NLen <= 512)
    {
        u32KeyLen = 512;
        enKeyWidth = CIPHER_RSA_KEY_WIDTH_4K;
    }
    else
    {
        HI_ERR_CIPHER("u16NLen(0x%x) is invalid\n", pCipherRsaData->u16NLen);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    ret = DRV_CIPHER_CheckRsaData(pCipherRsaData->pu8N, pCipherRsaData->pu8K, pCipherRsaData->pu8Input, u32KeyLen);
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA data invalid!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

//    msleep(1000);
//    HI_PRINT_HEX("N", pCipherRsaData->pu8N, pCipherRsaData->u16NLen);
//    HI_PRINT_HEX("K", pCipherRsaData->pu8K, pCipherRsaData->u16NLen);

    g_bRsaDone = HI_FALSE;
    HAL_RSA_Enable();

    ret = HAL_RSA_WaitFree();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy!\n");
        HAL_RSA_Disable();
        return HI_FAILURE;
    }

    /*Config Mode*/
    HAL_RSA_ConfigMode(enKeyWidth);

    u32Rnadom[0] = DRV_CIPHER_Rand();
    u32Rnadom[1] = DRV_CIPHER_Rand();
    u16CrC = DRV_RSA_KeyCRC(pCipherRsaData->pu8N, pCipherRsaData->pu8K, u32KeyLen, u32Rnadom);
    HI_INFO_CIPHER("CRC16: 0x%x\n", u16CrC);
    HAL_RSA_SetRandom(u32Rnadom);
    HAL_RSA_SetCRC(u16CrC);

    /*Write N,E,M*/
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_MODULE, pCipherRsaData->pu8N,
        pCipherRsaData->u16NLen, u32KeyLen, u32Rnadom);
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_KEY, pCipherRsaData->pu8K,
        pCipherRsaData->u16NLen, u32KeyLen, u32Rnadom);
    HAL_RSA_WriteData(CIPHER_RSA_DATA_TYPE_CONTEXT, pCipherRsaData->pu8Input,
        pCipherRsaData->u16NLen, u32KeyLen, u32Rnadom);

//    HI_PRINT_HEX("M_IN", pCipherRsaData->pu8Input, u32KeyLen);

    /*Sart*/
    HAL_RSA_Start();
    ret = DRV_RSA_WaitDone();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA is busy and timeout,error!\n");
        HAL_RSA_Disable();
        return HI_FAILURE;
    }

    u32ErrorCode = HAL_RSA_GetErrorCode();
    if( 0 != u32ErrorCode )
    {
        HI_ERR_CIPHER("RSA is err: chipset error code: 0x%x!\n", u32ErrorCode);
        HAL_RSA_Disable();
        return HI_FAILURE;
    }

    /*Get result*/
    HAL_RSA_ReadData(pCipherRsaData->pu8Output, pCipherRsaData->u16NLen, u32KeyLen);

//    HI_PRINT_HEX("M_OUT", pCipherRsaData->pu8Output, u32KeyLen);

    ret = DRV_CIPHER_ClearRsaRam();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("RSA clear ram error!\n");
        HAL_RSA_Disable();
        return HI_FAILURE;
    }

    HAL_RSA_Disable();

    return HI_SUCCESS;

}
#endif //IFEP_RSA_ENABLE
/**************************** RSA ***************************/
HI_S32 DRV_RSA_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    g_u32RsaRegCrg = cipher_ioremap_nocache(CIPHER_RSA_CRG_ADDR_PHY, 0x10);
    if (g_u32RsaRegCrg == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache rsa Reg failed\n");
        return HI_FAILURE;
    }

#ifdef IFEP_RSA_ENABLE
    ret = DRV_IFEP_RSA_Init();
    if (ret != HI_SUCCESS)
    {
        cipher_iounmap(g_u32RsaRegCrg);
        return ret;
    }
#endif

    return ret;
}

HI_VOID DRV_RSA_DeInit(HI_VOID)
{
#ifdef IFEP_RSA_ENABLE
    DRV_IFEP_RSA_DeInit();
#endif

    cipher_iounmap(g_u32RsaRegCrg);
}

HI_S32 DRV_CIPHER_CalcRsa_ex(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    HI_U32 ret;
    HI_BOOL bSecure;

    /* The IPEP RSA only can be accessed by secure CPU */
    ret = HI_DRV_SYS_GetCPUSecureMode(&bSecure);
    if(ret != HI_SUCCESS)
    {
        return ret;
    }
#ifdef IFEP_RSA_ENABLE
    if(bSecure)
    {
        /*Use the IPEP RSA if support*/
        return DRV_CIPHER_IFEP_CalcRsa(pCipherRsaData);
    }
    else
#endif
    {
        /*Otherwise use the software RSA */
        return DRV_CIPHER_CalcRsa_SW(pCipherRsaData);
    }
}

HI_S32 DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    static HI_U8  N[CIPHER_MAX_RSA_KEY_LEN];
    static HI_U8  K[CIPHER_MAX_RSA_KEY_LEN];
    static HI_U8  M[CIPHER_MAX_RSA_KEY_LEN];
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32KeyLen;
    CIPHER_RSA_DATA_S stCipherRsaData;
    HI_U8 *p;

    if(pCipherRsaData == HI_NULL)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((pCipherRsaData->pu8Input == HI_NULL) ||(pCipherRsaData->pu8Output== HI_NULL)
        || (pCipherRsaData->pu8N == HI_NULL) || (pCipherRsaData->pu8K == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        HI_ERR_CIPHER("pu8Input:0x%p, pu8Output:0x%p, pu8N:0x%p, pu8K:0x%p\n", pCipherRsaData->pu8Input, pCipherRsaData->pu8Output, pCipherRsaData->pu8N,pCipherRsaData->pu8K);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    if(pCipherRsaData->u32DataLen != pCipherRsaData->u16NLen)
    {
        HI_ERR_CIPHER("Error, DataLen != u16NLen!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pCipherRsaData->u16KLen > pCipherRsaData->u16NLen)
    {
        HI_ERR_CIPHER("Error, KLen > u16NLen!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    cipher_memset_s(N, sizeof(N), 0, sizeof(N));
    cipher_memset_s(K, sizeof(K), 0, sizeof(K));
    cipher_memset_s(M, sizeof(M), 0, sizeof(M));

    /*Only support the key width of 1024,2048 and 4096*/
    if (pCipherRsaData->u16NLen <= 128)
    {
        u32KeyLen = 128;
    }
    else if (pCipherRsaData->u16NLen <= 256)
    {
        u32KeyLen = 256;
    }
    else if (pCipherRsaData->u16NLen <= 384)
    {
        u32KeyLen = 384;
    }
    else if (pCipherRsaData->u16NLen <= 512)
    {
        u32KeyLen = 512;
    }
    else
    {
        HI_ERR_CIPHER("u16NLen(0x%x) is invalid\n", pCipherRsaData->u16NLen);
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    /*if dataLen < u32KeyLen, padding 0 before data*/
    p = N + (u32KeyLen - pCipherRsaData->u16NLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8N, pCipherRsaData->u16NLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }
    p = K + (u32KeyLen - pCipherRsaData->u16KLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8K, pCipherRsaData->u16KLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }
    p = M + (u32KeyLen - pCipherRsaData->u32DataLen);
    if (cipher_copy_from_user(p, pCipherRsaData->pu8Input, pCipherRsaData->u32DataLen))
    {
        HI_ERR_CIPHER("copy data from user fail!\n");
        return HI_FAILURE;
    }

    cipher_memset_s(&stCipherRsaData, sizeof(stCipherRsaData), 0, sizeof(CIPHER_RSA_DATA_S));
    stCipherRsaData.pu8N = N;
    stCipherRsaData.pu8K = K;
    stCipherRsaData.pu8Input = M;
    stCipherRsaData.u16NLen = u32KeyLen;
    stCipherRsaData.u16KLen = u32KeyLen;
    stCipherRsaData.u32DataLen = u32KeyLen;
    stCipherRsaData.pu8Output = M;

    ret = DRV_CIPHER_CalcRsa_ex(&stCipherRsaData);
    if( HI_SUCCESS != ret )
    {
        return HI_FAILURE;
    }

    if (cipher_copy_to_user(pCipherRsaData->pu8Output, M+(u32KeyLen - pCipherRsaData->u16NLen),
            pCipherRsaData->u16NLen))
    {
        HI_ERR_CIPHER("copy data to user fail!\n");
        return HI_FAILURE;
    }

    return ret;
}

HI_S32 HI_DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    HI_S32 ret = HI_SUCCESS;

    if(pCipherRsaData == HI_NULL)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(cipher_mutex_lock(&g_RsaMutexKernel))
    {
        HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    ret = DRV_CIPHER_CalcRsa(pCipherRsaData);

    cipher_mutex_unlock(&g_RsaMutexKernel);

    return ret;
}

EXPORT_SYMBOL(HI_DRV_CIPHER_CalcRsa);


