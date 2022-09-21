/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
    File Name   : drv_otp.c
    Version       : Initial Draft
    Author        : Hisilicon multimedia software group
    Created      : 2017/04/06
    Description :
    History        :
    1.Date        : 2017/04/06
        Modification: Created file
******************************************************************************/
#include "hal_otp.h"
#include "drv_otp.h"
#include "otp_debug.h"
#include "string.h"
#include "otp.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define OTP_CUSTOMER_KEY_LEN            (16)
#define OTP_INTERNAL_PV_1               (0x04)
#define OTP_INTERNAL_PVLOCK_1           (0x0C)
#define OTP_INTERNAL_DATALOCK_0         (0x10)
#define OTP_RIGHT_CTRL_EN_ADDR          (0x19)
#define OTP_ADVCA_ID_WORD_ADDR          (0xa8)      //0xa8 ~ 0xab
#define OTP_SCS_EN_BAK_ADDR             (0xad)
#define OTP_JTAG_MODE_BAK_ADDR          (0xae)
#define OTP_RIGHT_CTRL_EN_BAK_ADDR      (0xaf)
#define OTP_SELF_BOOT_DIABLE_BAK_ADDR   (0x1c)
#define ADVCA_ID_WORD                   (0x6EDBE953)
#define OTP_STB_PRIV_DATA_ADDR          (0x2b0)
#define OTP_CUSTOMER_KEY_ADDR           (0x2c0)

#define otp_read_reg(addr)          (*(volatile HI_U32 *)(addr))
#define otp_write_reg(addr, val)    ((*(volatile HI_U32 *)(addr)) = (val))


HI_S32 DRV_OTP_Init(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_DeInit(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data)
{
    OTP_CHECK_PARAM(u32Offset >= 16);

    return HAL_OTP_WriteByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, u8Data);
}

HI_S32 DRV_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    OTP_CHECK_PARAM(u32Offset >= 16);
    OTP_CHECK_PARAM(HI_NULL == pu8Data);

    ret = HAL_OTP_ReadByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get stb priv data, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pu8Data = value;

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    HI_U8 customerkey[OTP_CUSTOMER_KEY_LEN] = {0};
    HI_S32 ret            = HI_FAILURE;
    HI_S32 i              = 0;

    OTP_CHECK_PARAM(HI_NULL == pKey);
    OTP_CHECK_PARAM(u32KeyLen != 16);

    for (i = 0; i < 16; i++)
    {
        ret = HAL_OTP_ReadByte(OTP_CUSTOMER_KEY_ADDR + i, &customerkey[i]);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_OTP("failed to get customer key, return:%x\n", ret);
            return HI_FAILURE;
        }
    }

    memcpy(pKey, customerkey, OTP_CUSTOMER_KEY_LEN);

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag)
{
    HI_U32 value = 0;
    HI_S32 ret   = HI_FAILURE;

    OTP_CHECK_PARAM(HI_NULL == pbLockFlag);

    ret = HAL_OTP_Read(OTP_INTERNAL_DATALOCK_0, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get id word lock flag, return:%x\n", ret);
        return HI_FAILURE;
    }

    if(1 == ((value >> 10) & 0x1))           //0X11[2]
    {
        *pbLockFlag = HI_TRUE;
    }
    else
    {
        *pbLockFlag = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_LockIDWord(HI_VOID)
{
    HI_S32 ret      = 0;
    HI_U32 u32Value = 0;
    HI_U8 u8Value   = 0;

    /* ID_WORD_lock */
    ret = HAL_OTP_Read(OTP_INTERNAL_DATALOCK_0, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read id word lock\n");
        return HI_FAILURE;
    }

    /* Check ID_WORD locked or not */
    u8Value = (u32Value >> 8) & 0x04;              //0X11[2]
    if(0 == u8Value)
    {
        /* Lock ID_WORD */
        u8Value = ((u32Value >> 8) | 0x04) & 0xff;     //0X11[2]
        ret = HAL_OTP_WriteByte(OTP_INTERNAL_DATALOCK_0 + 1, u8Value);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_OTP("Write id word failed!\n");
            return HI_FAILURE;
        }
    }

    /* secure_chip_flag_lock */
    ret = HAL_OTP_Read(OTP_INTERNAL_PVLOCK_1, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read secure chip flag lock\n");
        return HI_FAILURE;
    }

    /* Check secure_chip_flag locked or not */
    u8Value = (u32Value & 0x1);                     //0xc[0]
    if(0 == u8Value)
    {
        /* Lock secure_chip_flag */
        u8Value = (u32Value | 0x1) & 0xff;          //0xc[0]
        ret = HAL_OTP_WriteByte(OTP_INTERNAL_PVLOCK_1, u8Value);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_OTP("Write secure_chip_flag_lock failed!\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_BurnToNormalChipset(HI_VOID)
{
    HI_S32 ret              = HI_SUCCESS;
    HI_U32 value            = 0;
    HI_BOOL bIsIDWordLocked = HI_FALSE;

    ret = HAL_OTP_Read(OTP_ADVCA_ID_WORD_ADDR, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get id word\n");
        return HI_FAILURE;
    }

    if (ADVCA_ID_WORD == value)
    {
        HI_ERR_OTP("It's secure chipset already, can not burn to normal!\n");
        return HI_FAILURE;
    }

    ret = DRV_OTP_GetIDWordLockFlag(&bIsIDWordLocked);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get IDWord Lock Flag error!\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == bIsIDWordLocked)
    {
        return HI_SUCCESS;
    }

    return DRV_OTP_LockIDWord();
}

HI_S32 DRV_OTP_BurnToSecureChipset(HI_VOID)
{
    HI_S32 ret              = HI_FAILURE;
    HI_U32 value            = 0;
    HI_BOOL bIsIDWordLocked = HI_FALSE;

    ret = DRV_OTP_GetIDWordLockFlag(&bIsIDWordLocked);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get IDWord Lock Flag error!\n");
        return HI_FAILURE;
    }

    ret = HAL_OTP_Read(OTP_ADVCA_ID_WORD_ADDR, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get IDWord error!\n");
        return HI_FAILURE;
    }

    if ((HI_TRUE == bIsIDWordLocked) && (ADVCA_ID_WORD == value))
    {
        return HI_SUCCESS;
    }

    if ((HI_TRUE != bIsIDWordLocked) && (ADVCA_ID_WORD == value))
    {
        return DRV_OTP_LockIDWord();
    }

    if ((HI_TRUE == bIsIDWordLocked) && (ADVCA_ID_WORD != value))
    {
        HI_ERR_OTP("ID_WORD has already been loacked to noaml chipset\n");
        return HI_FAILURE;
    }

    /* echo write 0x04 0x01 > /proc/msp/otp //secure_chip_flag */
    ret = HAL_OTP_WriteByte(OTP_INTERNAL_PV_1, 0x01);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set secure_chip_flag failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /* echo write 0x19 0x08 > /proc/msp/otp  //right_ctrl_en */
    ret = HAL_OTP_WriteByte(OTP_RIGHT_CTRL_EN_ADDR, 0x08);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set right_ctrl_en failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /*
        echo write 0xa8 0x53 > /proc/msp/otp  //Advca ID_WORD
        echo write 0xa9 0xe9 > /proc/msp/otp  //Advca ID_WORD
        echo write 0xaa 0xdb > /proc/msp/otp  //Advca ID_WORD
        echo write 0xab 0x6e > /proc/msp/otp  //Advca ID_WORD
    */
    ret = HAL_OTP_WriteByte(OTP_ADVCA_ID_WORD_ADDR, 0x53);
    ret |= HAL_OTP_WriteByte(OTP_ADVCA_ID_WORD_ADDR + 1, 0xe9);
    ret |= HAL_OTP_WriteByte(OTP_ADVCA_ID_WORD_ADDR + 2, 0xdb);
    ret |= HAL_OTP_WriteByte(OTP_ADVCA_ID_WORD_ADDR + 3, 0x6e);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set advca ID_WORD failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /* echo write 0xad 0x81 > /proc/msp/otp  //scs_en_bak */
    ret = HAL_OTP_WriteByte(OTP_SCS_EN_BAK_ADDR, 0x81);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set scs_en_bak failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /* echo write 0xae 0x42 > /proc/msp/otp  //jtag_mode_bak */
    ret = HAL_OTP_WriteByte(OTP_JTAG_MODE_BAK_ADDR, 0x42);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set jtag_mode_bak failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /* echo write 0xaf 0xff > /proc/msp/otp  //right_ctrl_en_bak */
    ret = HAL_OTP_WriteByte(OTP_RIGHT_CTRL_EN_BAK_ADDR, 0xff);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set right_ctrl_en_bak failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    /* echo write 0x1c 0x11 > /proc/msp/otp  //self_boot_disable_bak */
    ret = HAL_OTP_WriteByte(OTP_SELF_BOOT_DIABLE_BAK_ADDR, 0x11);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set self_boot_disable_bak failed, ret: 0x%x!\n", ret);
        return HI_FAILURE;
    }

    return DRV_OTP_LockIDWord();
}

HI_U32 DRV_OTP_Read(HI_U32 addr)
{
    HI_U32 value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_Read(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_U8  DRV_OTP_ReadByte(HI_U32 addr)
{
    HI_U8  value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_ReadByte(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_S32 DRV_OTP_WriteByte(HI_U32 addr, HI_U8 u8data)
{
    HI_S32 ret = HI_FAILURE;

    ret = HAL_OTP_WriteByte(addr, u8data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to write otp, return:%x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_Write(HI_U32 addr, HI_U32 u32data)
{
    HI_S32 ret = HI_FAILURE;

    ret = HAL_OTP_Write(addr, u32data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to write otp, return:%x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_VOID OTP_Init(void)
{
    (HI_VOID)DRV_OTP_Init();
}

HI_VOID OTP_DeInit(void)
{
    (HI_VOID)DRV_OTP_DeInit();
}
HI_U32 OTP_Read(HI_U32 addr)
{
    return DRV_OTP_Read(addr);
}

HI_S32 OTP_Write(HI_U32 addr, HI_U32 u32Data)
{
    return DRV_OTP_Write(addr, u32Data);
}

HI_U8  OTP_ReadByte(HI_U32 addr)
{
    return DRV_OTP_ReadByte(addr);
}

HI_S32 OTP_SetByte(HI_U32 addr, HI_U8 tdata)
{
    return DRV_OTP_WriteByte(addr, tdata);
}


HI_S32 OTP_GetMarketID(HI_U8 u8Id[4])
{
    unsigned int id;

    id = otp_read_reg(OTP_V200_MARKETID);

    u8Id[0] = (id >> 24) & 0xff;
    u8Id[1] = (id >> 16) & 0xff;
    u8Id[2] = (id >> 8) & 0xff;
    u8Id[3] = id & 0xff;

    return HI_SUCCESS;
}

HI_S32 OTP_GetR2RLadderLevel(OTP_KEY_LEVEL_E *pLevel)
{
    OTP_CHECK_PARAM(HI_NULL == pLevel);

    *pLevel = otp_read_reg(OTP_V200_PVREGISTER0);
    *pLevel = (*pLevel >> 6) & 0x1;

    if(0 ==*pLevel)
    {
        *pLevel = OTP_KEY_LEV2;
    }
    else
    {
        *pLevel = OTP_KEY_LEV3;
    }

    return HI_SUCCESS;
}

HI_S32 OTP_V200_getChipID(HI_U32 *pID)
{
    if (pID == NULL)
    {
        return HI_FAILURE;
    }

    *pID = otp_read_reg(OTP_V200_CHIPID);

    return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

