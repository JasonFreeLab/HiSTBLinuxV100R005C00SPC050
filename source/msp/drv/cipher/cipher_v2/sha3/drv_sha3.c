/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sha3.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"

#ifdef SHA3_ENABLE

HI_VOID *g_u32Sha3RegBase ;

#define SHA3_REG_BASE                    g_u32Sha3RegBase
#define INT_STATUS                      (SHA3_REG_BASE + 0x000)
#define INT_EN                          (SHA3_REG_BASE + 0x004)
#define INT_RAW                         (SHA3_REG_BASE + 0x008)
#define SHA_SMMU_EN                     (SHA3_REG_BASE + 0x020)
#define SHA_SMMU_START_ADDR             (SHA3_REG_BASE + 0x024)
#define SHA3_DMA_START_ADDR             (SHA3_REG_BASE + 0x300)
#define SHA3_DMA_LEN                     (SHA3_REG_BASE + 0x304)
#define SHA3_CTRL                       (SHA3_REG_BASE + 0x308)
#define SHA3_DATA_IN                    (SHA3_REG_BASE + 0x30c)
#define SHA3_CPU_LEN                    (SHA3_REG_BASE + 0x310)
#define SHA3_STATE_VAL                  (SHA3_REG_BASE + 0x314)
#define SHA3_STATE_VAL_ADDR             (SHA3_REG_BASE + 0x318)
#define SHA3_STATUS                     (SHA3_REG_BASE + 0x31c)
#define SHA3_INT_MASK                   (0x01 << 2)
#define SHA3_START                      (0x01 << 0)

#define SHA3_MAX_BLOCK_SIZE                (144)             //sha3-224

#define SHA3_IRQ_NUMBER                 (156 + 32)
#define SHA3_TIME_OUT                   50000
#define CPU_DAT_IN_READY                (0x01 << 16)

static cipher_mutex s_SHA3Mutex;
static cipher_queue_head s_Sha3WaitQueue;
static HI_BOOL  s_bSha3Done = HI_FALSE;

#ifdef INT_ENABLE
irqreturn_t DRV_SHA3_ISR(HI_S32 irq, HI_VOID *devId)
{
    HI_U32 INTValue = 0;

    HAL_CIPHER_ReadReg (INT_STATUS, &INTValue);

    HI_INFO_CIPHER(" in the isr INTValue=%#x!\n", INTValue);

    if (INTValue & SHA3_INT_MASK) /* single pkg */
    {
        s_bSha3Done = HI_TRUE;
        cipher_queue_wait_up(&s_Sha3WaitQueue);
        HAL_CIPHER_WriteReg(INT_RAW, SHA3_INT_MASK);
    }

    return IRQ_HANDLED;
}
#endif

HI_S32 DRV_SHA3_Init(HI_VOID)
{
    HI_S32 ret;
    HI_U32 Value;
    HI_U32 *pvirt;

    pvirt = cipher_ioremap_nocache(CIPHER_SHA3_CRG_ADDR_PHY, 16);
    if (pvirt == 0)
    {
        HI_ERR_CIPHER("ioremap_nocache phy addr err:%x.\n", CIPHER_SHA3_CRG_ADDR_PHY);
        return HI_FAILURE;
    }

    HAL_CIPHER_ReadReg(pvirt, &Value);
    HAL_SET_BIT(Value, 14);   /* clock opened */
    HAL_CIPHER_WriteReg(pvirt,Value);

    HAL_CIPHER_ReadReg(pvirt, &Value);
    HAL_SET_BIT(Value, 11); /* reset */
    HAL_CIPHER_WriteReg(pvirt,Value);
    cipher_msleep(50);

    HAL_CLEAR_BIT(Value, 11); /* cancel reset */
    HAL_CIPHER_WriteReg(pvirt,Value);

    cipher_iounmap(pvirt);

    g_u32Sha3RegBase = cipher_ioremap_nocache(CIPHER_SHA3_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32Sha3RegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache sha3 Reg failed\n");
        return HI_FAILURE;
    }

    cipher_queue_init(&s_Sha3WaitQueue);

    HAL_CIPHER_WriteReg(INT_RAW, SHA3_INT_MASK);

#ifdef INT_ENABLE
    HAL_CIPHER_WriteReg(INT_EN,  0x80000000 | SHA3_INT_MASK); //int enable
    ret = cipher_request_irq(SHA3_IRQ_NUMBER, DRV_SHA3_ISR, IRQF_DISABLED, "sha3");
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("sha3 Irq request failure, ret=%#x, irq=%d", ret, SHA3_IRQ_NUMBER);
        return HI_FAILURE;
    }
#endif

#ifdef SMMU_ENABLE
    HAL_CIPHER_WriteReg(SHA_SMMU_EN, 0x01);
    HAL_CIPHER_WriteReg(SHA_SMMU_START_ADDR, cipher_mmu_table_addr());
#else
    HAL_CIPHER_WriteReg(SHA_SMMU_EN, 0x00);
#endif

    return HI_SUCCESS;
}

static HI_S32 DRV_SHA3_WaitRaedy(HI_VOID)
{
    HI_U32 u32Ctrl;
    HI_U32 u32Time = 0;

    while(u32Time++ < SHA3_TIME_OUT)
    {
        HAL_CIPHER_ReadReg(SHA3_CTRL, &u32Ctrl);
        if (! (u32Ctrl & SHA3_START))
        {
            return HI_SUCCESS;
        }
        cipher_msleep(1);
    }

    HI_ERR_CIPHER("sha3 busy !!!");

    return HI_FAILURE;
}

HI_VOID DRV_SHA3_DeInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    //reset
 #ifdef INT_ENABLE
    cipher_free_irq(SHA3_IRQ_NUMBER, "sha3");
 #endif
    cipher_iounmap(g_u32Sha3RegBase);
}

static HI_U32 SHA3_MsgPadding(HI_U8 *pu8Msg, HI_U32 u32TotalLen, HI_U32 u32BlockSize)
{
    HI_U32 u32Tmp = 0;
    HI_U32 u32PLen;
    HI_U32 u32ByteLen;

    if( NULL == pu8Msg )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return 0;
    }

    u32ByteLen = u32TotalLen % u32BlockSize;
    u32PLen = u32BlockSize - u32ByteLen;
    memset(&pu8Msg[u32ByteLen], 0, u32PLen);
    pu8Msg[u32ByteLen] |= 0x06;
    u32ByteLen+=u32PLen - 1;
    u32Tmp = 0x80;
    pu8Msg[u32ByteLen] |= u32Tmp;
    u32ByteLen++;

    return u32ByteLen;
}

static HI_S32 SHA3_CPUInput(HI_U32 *pu32Msg, HI_U32 u32Len)
{
    HI_U32 i;
    HI_U32 u32Status = 0, u32Timeout = 0;

    for(i=0; i<u32Len/4; i++)
    {
        HAL_CIPHER_WriteReg(SHA3_DATA_IN, pu32Msg[i]);
 //       printk("KEY: 0x%x\n", pu32Msg[i]);
    }

    while(u32Timeout < SHA3_TIME_OUT)
    {
        HAL_CIPHER_ReadReg(SHA3_STATUS, &u32Status);
        if(u32Status & CPU_DAT_IN_READY)
        {
             break;
        }
    }

    if( u32Timeout >= SHA3_TIME_OUT )
    {
        HI_ERR_CIPHER("Error, hmac set key timeout!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 SHA3_WaitDone(HI_VOID)
{
#ifdef INT_ENABLE
    HI_S32 ret;

    ret = cipher_queue_wait_timeout(s_Sha3WaitQueue, s_bSha3Done!= HI_FALSE, 1000);
    if (ret == 0)
    {
        HI_ERR_CIPHER("hmac set key(%d) time out! SHA3_IRQ_NUMBER: %d \n", bIsOKey, SHA3_IRQ_NUMBER);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
#else
    return DRV_SHA3_WaitRaedy();
#endif
}

static HI_S32 SHA3_SetKey(CIPHER_HASH_DATA_S *pCipherHashData, HI_BOOL bIsOKey)
{
    HI_U32 u32KeyLen = 0, u32Size;
    HI_U32 i, u32Ctrl = 0;
    HI_U32 u32Cnt;
    HI_U32 u32Key[200];
    HI_S32 ret;

    switch(pCipherHashData->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_224:
        u32Ctrl |= 0x00 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_256:
        u32Ctrl |= 0x01 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_384:
        u32Ctrl |= 0x02 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_512:
        u32Ctrl |= 0x03 << 12;
        break;
    default:
        HI_ERR_CIPHER("Hash type invalid: 0x%x!\n", pCipherHashData->enShaType);
        return HI_FAILURE;
    }

    u32Ctrl |= 0x01 << 8; //data_in_sel, cpu
    u32Ctrl |= 0x00 << 7; //bit_end_en
    u32Ctrl |= 0x01 << 5; //init_val_sel
    u32Ctrl |= 0x00 << 4; //sha3_small_end_en
    u32Ctrl |= pCipherHashData->bKeyByCA << 3; //key_sel
    u32Ctrl |= bIsOKey << 1; //cal_mode
    HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);

    s_bSha3Done = HI_FALSE;

//    printk("KeyLen %d, BlockSize %d\n", pCipherHashData->u32HMACKeyLen, pCipherHashData->u8BlockSize);
    if (pCipherHashData->u32HMACKeyLen <= pCipherHashData->u8BlockSize)
    {
        HAL_CIPHER_WriteReg(SHA3_CPU_LEN, pCipherHashData->u8BlockSize);
        u32Ctrl |= SHA3_START; //sha3_start
        HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);

        if (pCipherHashData->bKeyByCA)
        {
            ret = SHA3_CPUInput(u32Key, 0);
        }
        else
        {
             memset(u32Key, 0, SHA3_MAX_BLOCK_SIZE);
            if (cipher_copy_from_user(u32Key, pCipherHashData->pu8HMACKey, pCipherHashData->u32HMACKeyLen))
            {
                HI_ERR_CIPHER("Error, copy hmac key from user failed!\n");
                return HI_FAILURE;
            }
            ret = SHA3_CPUInput(u32Key, pCipherHashData->u8BlockSize);
        }
        if( ret != HI_SUCCESS )
        {
            return HI_FAILURE;
        }
    }
    else
    {
        u32Size = pCipherHashData->u32HMACKeyLen % pCipherHashData->u8BlockSize;
        if (u32Size == 0)
        {
            u32Size = pCipherHashData->u32HMACKeyLen + pCipherHashData->u8BlockSize;
        }
        else
        {
            u32Size = pCipherHashData->u32HMACKeyLen + pCipherHashData->u8BlockSize - u32Size;
        }

        HAL_CIPHER_WriteReg(SHA3_CPU_LEN, u32Size);
        u32Ctrl |= SHA3_START; //sha3_start
        HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);

        u32Cnt = pCipherHashData->u32HMACKeyLen / pCipherHashData->u8BlockSize;
        for(i=0; i < u32Cnt; i++)
        {
            u32Size = pCipherHashData->u8BlockSize;
            if (cipher_copy_from_user(u32Key, pCipherHashData->pu8HMACKey + u32KeyLen, u32Size))
            {
                HI_ERR_CIPHER("Error, copy hmac key from user failed!\n");
                return HI_FAILURE;
            }
            ret = SHA3_CPUInput(u32Key, u32Size);
            if( ret != HI_SUCCESS )
            {
                return HI_FAILURE;
            }
            u32KeyLen += u32Size;
        }
        if (cipher_copy_from_user(u32Key, pCipherHashData->pu8HMACKey + u32KeyLen,
            pCipherHashData->u32HMACKeyLen - u32KeyLen))
        {
            HI_ERR_CIPHER("Error, copy hmac key from user failed!\n");
            return HI_FAILURE;
        }
        u32Size = SHA3_MsgPadding((HI_U8*)u32Key, pCipherHashData->u32HMACKeyLen, pCipherHashData->u8BlockSize);
 //       HI_PRINT_HEX("PAD", (HI_U8*)u32Key, pCipherHashData->u8BlockSize);
        ret = SHA3_CPUInput(u32Key, u32Size);
        if( ret != HI_SUCCESS )
        {
            return HI_FAILURE;
        }
    }

    ret = SHA3_WaitDone();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SHA3 wait ready failed!\n");
        return HI_FAILURE;
    }

    for(i=0; i<HASH_OUTPUT_SIZE_WORD; i++)
    {
        HAL_CIPHER_WriteReg(SHA3_STATE_VAL_ADDR, i);
        HAL_CIPHER_ReadReg(SHA3_STATE_VAL, &u32Key[i]);
    }
//    HI_PRINT_HEX("HASH", (HI_U8*)u32Key, 200);

    return HI_SUCCESS;
}

static HI_S32 SHA3_Update(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Ctrl = 0;
    HI_U32 i;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }
//    printk("u8Mode %d, enShaType %d, u32DataLen %d, u32DataPhy 0x%x, u8BlockSize %d, Step %d\n",
//    pCipherHashData->u8Mode, pCipherHashData->enShaType,
//    pCipherHashData->u32DataLen, pCipherHashData->u32DataPhy,
//    pCipherHashData->u8BlockSize, pCipherHashData->enStep);

    ret = DRV_SHA3_WaitRaedy();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SHA3 Wait Raedy failed!\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->enStep & HI_DRV_HASH_STEP_INIT)
    {
        if(pCipherHashData->u8Mode == HASH_MODE_MAC)
        {
            ret = SHA3_SetKey(pCipherHashData, HI_FALSE);
            if(HI_SUCCESS != ret)
            {
                HI_ERR_CIPHER("SHA3_SetKey failed! ret = 0x%08x\n", ret);
                return HI_FAILURE;
            }
            u32Ctrl |= 0x02 << 5; //init_val_sel, use last val
        }
        else
        {
            u32Ctrl |= 0x01 << 5; //init_val_sel, use 0
        }
    }
    else
    {
        u32Ctrl |= 0x00 << 5; //init_val_sel, use config val
        for(i=0; i<HASH_OUTPUT_SIZE_WORD; i++)
        {
            HAL_CIPHER_WriteReg(SHA3_STATE_VAL_ADDR, i);
            HAL_CIPHER_WriteReg(SHA3_STATE_VAL, pCipherHashData->u32ShaVal[i]);
        }
  //      HI_PRINT_HEX("INIT", (HI_U8*)pCipherHashData->u32ShaVal, 200);
    }

    switch(pCipherHashData->enShaType)
    {
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_224:
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_224:
        u32Ctrl |= 0x00 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_256:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_256:
        u32Ctrl |= 0x01 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_384:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_384:
        u32Ctrl |= 0x02 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_512:
    case HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA3_512:
        u32Ctrl |= 0x03 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_SHAKE128:
        u32Ctrl |= 0x04 << 12;
        break;
    case HI_UNF_CIPHER_HASH_TYPE_SHA3_SHAKE256:
        u32Ctrl |= 0x05 << 12;
        break;
    default:
        HI_ERR_CIPHER("Hash type invalid: 0x%x!\n", pCipherHashData->enShaType);
        return HI_FAILURE;
    }

    u32Ctrl |= (pCipherHashData->u32DataLen == 0 ? 2 : 0) << 8; //data_in_sel
    u32Ctrl |= 0x00 << 7; //bit_end_en
    u32Ctrl |= 0x00 << 4; //sha3_small_end_en
    u32Ctrl |= 0x00 << 3; //key_sel
    u32Ctrl |= 0x02 << 1; //cal_mode. raw hash

    HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);
    HAL_CIPHER_WriteReg(SHA3_DMA_START_ADDR, pCipherHashData->u32DataPhy);
    HAL_CIPHER_WriteReg(SHA3_DMA_LEN, pCipherHashData->u32DataLen);

    flush_cache();

    s_bSha3Done = HI_FALSE;

    /*start*/
    u32Ctrl |= SHA3_START;
    HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);

    ret = SHA3_WaitDone();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("SHA3 wait ready failed!\n");
        return HI_FAILURE;
    }

    for(i=0; i<HASH_OUTPUT_SIZE_WORD; i++)
    {
        HAL_CIPHER_WriteReg(SHA3_STATE_VAL_ADDR, i);
        HAL_CIPHER_ReadReg(SHA3_STATE_VAL, &pCipherHashData->u32ShaVal[i]);
    }
//    HI_PRINT_HEX("_HASH", (HI_U8*)pCipherHashData->u32ShaVal, 200);

    return HI_SUCCESS;

}

static HI_S32 SHA3_Final(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Ctrl = 0;
    HI_U32 u32Size, i;

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    ret = SHA3_Update(pCipherHashData);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("SHA3_Update failed\n");
        return HI_FAILURE;
    }

    if(pCipherHashData->u8Mode == HASH_MODE_MAC)
    {
        ret = SHA3_SetKey(pCipherHashData, HI_TRUE);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("SHA3_SetKey failed! ret = 0x%08x\n", ret);
            return HI_FAILURE;
        }

        s_bSha3Done = HI_FALSE;

        HAL_CIPHER_ReadReg(SHA3_CTRL, &u32Ctrl);
        u32Ctrl &= ~0x26;
        u32Ctrl |= 0x04;      //cpu mode, cal msg
        u32Ctrl |= 0x02 << 5; //init_val_sel, use last val
        HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);
        u32Size = SHA3_MsgPadding((HI_U8*)pCipherHashData->u32ShaVal, pCipherHashData->u8OutputSize, pCipherHashData->u8BlockSize);
        HAL_CIPHER_WriteReg(SHA3_CPU_LEN, u32Size);

        u32Ctrl |= 0x01;  //start
        HAL_CIPHER_WriteReg(SHA3_CTRL, u32Ctrl);

        ret = SHA3_CPUInput(pCipherHashData->u32ShaVal, u32Size);
        if( ret != HI_SUCCESS )
        {
            return HI_FAILURE;
        }

        ret = SHA3_WaitDone();
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("SHA3 wait ready failed!\n");
            return HI_FAILURE;
        }

        for(i=0; i<HASH_OUTPUT_SIZE_WORD; i++)
        {
            HAL_CIPHER_WriteReg(SHA3_STATE_VAL_ADDR, i);
            HAL_CIPHER_ReadReg(SHA3_STATE_VAL, &pCipherHashData->u32ShaVal[i]);
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_SHA3_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData)
{
    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error, Null pointer input!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_SHA3_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if(cipher_mutex_lock(&s_SHA3Mutex))
    {
        HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }
    s32Ret = SHA3_Update(pCipherHashData);

    cipher_mutex_unlock(&s_SHA3Mutex);

    return s32Ret;
}

HI_S32 HI_DRV_SHA3_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if(cipher_mutex_lock(&s_SHA3Mutex))
    {
        HI_ERR_CIPHER("down_interruptible failed!\n");
        return HI_FAILURE;
    }

    s32Ret = SHA3_Final(pCipherHashData);

    cipher_mutex_unlock(&s_SHA3Mutex);

    return s32Ret;
}
#endif


