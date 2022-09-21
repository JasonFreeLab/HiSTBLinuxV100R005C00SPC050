/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdcp.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"

#ifdef HDCP_ENABLE

//#define DISPLAY_KSV_CRC

extern HI_VOID *g_u32CipherRegBase;
#define CALC_ST0                         (g_u32CipherRegBase + 0x0318)

#define HDCP_KEY_RAM_LONG_SIZE    (512)
#define P32 0xEDB88320L
static HI_S32 crc_tab32_init = 0;
static HI_U32 crc_tab32[256];

extern HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S g_stFlashHdcpKey;
extern HI_BOOL g_bHDCPKeyLoadFlag;

static HI_VOID init_crc32_tab( HI_VOID )
{
    HI_U32 i,j;
    HI_U32 u32Crc;

    for (i=0; i<256; i++) {
        u32Crc = (HI_U32) i;
        for (j=0; j<8; j++) {
            if (u32Crc & 0x00000001L) {
                u32Crc = (u32Crc >> 1) ^ P32;
            } else {
                u32Crc = u32Crc >> 1;
            }
        }
        crc_tab32[i] = u32Crc;
    }
    crc_tab32_init = 1;
}

static HI_U32 update_crc_32(HI_U32 u32Crc, HI_CHAR s8C)
{
    HI_U32 u32Tmp, u32Long_c;

    u32Long_c = 0x000000ffL & (HI_U32) s8C;
    u32Tmp = u32Crc ^ u32Long_c;
    u32Crc = (u32Crc >> 8) ^ crc_tab32[u32Tmp & 0xff];
    return u32Crc;
}

static HI_S32 Cipher_CRC32( HI_U8* pu8Buff,HI_U32 length, HI_U32 *pu32Crc32Result)
{
    HI_U32 u32Crc32;
    HI_U32 i;
    u32Crc32 = 0xffffffffL;

    if ( (NULL == pu32Crc32Result) || (NULL == pu8Buff) )
    {
        return HI_FAILURE;
    }

    if (!crc_tab32_init) {
        init_crc32_tab();
    }
    for(i=0 ; i < length ; i++) {
        u32Crc32 = update_crc_32(u32Crc32,(char)pu8Buff[i]);
    }
    u32Crc32 ^= 0xffffffffL;

    *pu32Crc32Result = u32Crc32;

    return HI_SUCCESS;
}

/*
        head              HDMIIP_HDCPKey                 CRC32_0 CRC32_1
      |-------|-----------------------------------------|------|------|
      |4bytes-|-----------------Encrypt(320bytes)-------|-4byte|-4byte|
*/
#if defined (CHIP_TYPE_hi3798cv200_a) || defined (CHIP_TYPE_hi3798cv200_b)
static HI_S32 DRV_CIPHER_HdcpKeyExpand512(HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                                          HI_U8 *pu8In, HI_U8 *pu8Out)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_Config_CTRL CipherCtrl;
    HI_U8 *pu8HdcpKey;

    if ((pu8In == HI_NULL) || (pu8Out == HI_NULL) )
    {
        HI_ERR_CIPHER("NULL Pointer, Invalid param input!\n");
        return HI_FAILURE;
    }

    memset(pu8Out, 0, HDCP_KEY_RAM_LONG_SIZE);
    memcpy(pu8Out, pu8In, HDCP_KEY_RAM_SIZE);
    pu8Out[HDCP_KEY_RAM_LONG_SIZE - 2] = 0x00; //AV Content Protection
    pu8Out[HDCP_KEY_RAM_LONG_SIZE - 1] = 0xFF; //OTP Locked
    pu8HdcpKey = pu8Out + HDCP_KEY_RAM_SIZE;
    memcpy((HI_VOID*)CipherCtrl.u32IV, pu8In + (HDCP_KEY_RAM_SIZE - CI_IV_SIZE), CI_IV_SIZE);

    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.stChangeFlags.bit1IV = 1;

    return HI_DRV_CIPHER_CPU_Encrypt(pu8HdcpKey, HDCP_KEY_RAM_LONG_SIZE - HDCP_KEY_RAM_SIZE,
               pu8HdcpKey, CIPHER_HDCP_MODE_HDCP_KEY, enRootKeyType,
               HI_DRV_HDCPKEY_TX0, &CipherCtrl, HI_FALSE);
}
#endif

HI_S32 DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Crc32Result = 0;
    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType;
    HI_U32 u32Tmp = 0;
    HI_U8  *pu8HdcpKey = HI_NULL;
    HI_U32 HdcpKeylen= 0;
    CIPHER_Config_CTRL CipherCtrl;

    if( HI_NULL == pstFlashHdcpKey)
    {
        HI_ERR_CIPHER("NULL Pointer, Invalid param input!\n");
        return HI_FAILURE;
    }

    if(pstFlashHdcpKey->u32KeyLen != HDCP_KEY_CHIP_FILE_SIZE)
    {
        HI_ERR_CIPHER("Invalid key len: 0x%x!\n", pstFlashHdcpKey->u32KeyLen);
        return HI_FAILURE;
    }

    // HDCP1.x Tx/Rx
    if (HI_DRV_HDCP_VERIOSN_1x == pstFlashHdcpKey->enHDCPVersion)
    {
        u32Tmp = pstFlashHdcpKey->u8Key[0] & 0xc0;
        if ( 0x00 == u32Tmp)
        {
            enRootKeyType = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
        }
        else if( 0x80 == u32Tmp)
        {
            enRootKeyType = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;
        }
        else
        {
            HI_ERR_CIPHER("Invalid keySelect mode input!\n");
            return  HI_FAILURE;
        }

        /* verify crc32_1 */
        s32Ret = Cipher_CRC32(pstFlashHdcpKey->u8Key, (HDCP_KEY_CHIP_FILE_SIZE - 4), &u32Crc32Result);
        if ( HI_FAILURE == s32Ret)
        {
            HI_ERR_CIPHER("HDCP KEY CRC32_1 calc failed!\n");
            return HI_FAILURE;
        }
        if ( memcmp(&u32Crc32Result, &pstFlashHdcpKey->u8Key[HDCP_KEY_CHIP_FILE_SIZE - 4], 4) != 0 )
        {
            HI_ERR_CIPHER("HDCP KEY CRC32_1 compare failed!");
            return HI_FAILURE;
        }
#if defined (CHIP_TYPE_hi3798cv200_a) || defined (CHIP_TYPE_hi3798cv200_b)
        pu8HdcpKey = (HI_U8*)HI_KMALLOC(HDCP_KEY_RAM_LONG_SIZE, GFP_KERNEL);
        if (pu8HdcpKey == HI_NULL)
        {
            HI_ERR_CIPHER("HDCP malloc buff failed!\n");
            return HI_FAILURE;
        }
        s32Ret = DRV_CIPHER_HdcpKeyExpand512(enRootKeyType, pstFlashHdcpKey->u8Key + 4, pu8HdcpKey);
        if (pu8HdcpKey == HI_NULL)
        {
            HI_KFREE(pu8HdcpKey);
            HI_ERR_CIPHER("Hdcp Key expand to 512 failed!\n");
            return HI_FAILURE;
        }
        HdcpKeylen = HDCP_KEY_RAM_LONG_SIZE;
#else
        pu8HdcpKey = pstFlashHdcpKey->u8Key + 4;
        HdcpKeylen = HDCP_KEY_RAM_SIZE;
#endif

        memset(&CipherCtrl, 0, sizeof(CipherCtrl));
        CipherCtrl.CIpstCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.CIpstCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        CipherCtrl.CIpstCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.CIpstCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
        CipherCtrl.CIpstCtrl.stChangeFlags.bit1IV = 1;
        s32Ret = HI_DRV_CIPHER_CPU_Encrypt(pu8HdcpKey, HdcpKeylen,
               HI_NULL, CIPHER_HDCP_MODE_HDCP_KEY, enRootKeyType,
               pstFlashHdcpKey->enHDCPKeyType, &CipherCtrl, HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CIPHER("HDCP key decrypt final failed!\n");
            return HI_FAILURE;
        }
#ifdef DISPLAY_KSV_CRC
        HAL_CIPHER_ReadReg(CALC_ST0, &u32Tmp);
        HI_PRINT("Load HDCP Key, KSV CRC: 0x%02x\n", (u32Tmp >> 12) & 0x0F);
#endif
        memcpy(&g_stFlashHdcpKey, pstFlashHdcpKey, sizeof(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S));
        g_bHDCPKeyLoadFlag = HI_TRUE;
#if defined (CHIP_TYPE_hi3798cv200_a) || defined (CHIP_TYPE_hi3798cv200_b)
        HI_KFREE(pu8HdcpKey);
#endif

    }
    else   // HDCP2.x Rx/Tx or other
    {
        HI_ERR_CIPHER("Please set correct HDCP verison!");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID s_DRV_CIPHER_FormatHDCPKey(HI_UNF_HDCP_DECRYPT_S *pSrcKey, HI_U8 u8DstKey[HDCP_KEY_RAM_SIZE])
{
    HI_S32 i;
    HI_U8 TailBytes[31] = {0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3,
                           0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,
                           0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,
                           0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    HI_U32 CheckSum = 0xa3c5;
    HI_U32 XorValue, Temp;

    memset(u8DstKey, 0, HDCP_KEY_RAM_SIZE);

    /* Byte 0*/
    u8DstKey[0] = 0x00;
    /* Byte 1 ~ 5 KSV */
    for (i = 0; i < 5; i ++)
    {
        u8DstKey[1 + i] = pSrcKey->u8KSV[i];
    }
    /* Byte 8 */
    u8DstKey[8] = 0xa8;
    /* Byte 9 ~ 288 Device Private Key */
    for (i = 0; i < 280; i ++)
    {
        u8DstKey[9 + i] = pSrcKey->u8PrivateKey[i];
    }
    /* Byte 289 ~ 319 */
    for (i = 0; i < 31; i ++)
    {
        u8DstKey[289 + i] = TailBytes[i];
    }

    /* Count CRC value */
    for(i=0; i<320; i++)
    {
        if((i>=6) && (i<=8))
        {
            continue;
        }
        XorValue = CheckSum ^ u8DstKey[i];
        Temp = ~((XorValue >> 7) ^ (XorValue >> 16));
        XorValue = XorValue << 1;
        XorValue = (XorValue & 0x1fffe) | (Temp & 1);
        CheckSum = XorValue;
    }

    for(i=0; i<8; i++)
    {
        XorValue = CheckSum;
        Temp = ~((XorValue >> 7) ^ (XorValue >> 16));
        XorValue = XorValue << 1;
        XorValue = (XorValue & 0x1fffe) | (Temp & 1);
        CheckSum = XorValue;
    }

    /* Byte 6 && 7  CRC Value */
    u8DstKey[6] = CheckSum & 0xff;
    u8DstKey[7] = (CheckSum >> 8) & 0xff;


    return;
}

/**********************************************************************
    DCP申请的独立的HDCP key原始格式，共308Bytes：
    0~4    KSV  固定为 "02000000"    Key Selection Vector use to communicate between HDMI Transmitter and Receiver.
    5~7         固定为 "000000"
    8~287     Device Private Key    Secret data
    288~307    Reserved    No use

    HISI HDCP Key工具将申请到的Key重新封装，生成新的key文件大小为384个字节，各字段意义如下：
    第0~7(8)字节      ：海思标记位：HISI_xxx
    第8~15(8)字节     ：工具版本号：V0000001
    第16~47(32)字节   ：客户的ID号：xxxxxxxx
    第48~367(320)字节 ：加密后的320bytes HDCP key(16字节对齐)。
    第368~384(16)字节 ：后续使用，暂定为随机数。

    芯片上加密存放到文件中的HDCP Key格式
    head              HDMIIP_HDCPKey                 CRC32_0 CRC32_1
    |-------|-----------------------------------------|------|------|
    |4bytes-|-----------------Encrypt(320bytes)-------|-4byte|-4byte|

    total: 332

    Head格式：4 byte
    B0[7..6] key type, 00: otp root key, 01: hisi defined 10: host root key
    B1:      固定为0x00;
    B2~B3:   固定为"HI"

    HDCPKey 格式：320 byte
    B0:      固定为0x00;
    B1~B5:   KSV (DCP组织申请的HDCP Key中提取）
    B6~B7:   HDCPKey的CRC16，不包括B6~B8.
    B8：     固定为0xa8;
    B9~B288: Device Private Key (DCP组织申请的HDCP Key中提取）
    B289~B319: 填充为 0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3, 0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    CRC32_0：  加密前HDCPKey的CRC32
    CRC32_1：  Head+HDCPKey+CRC32_0的CRC32
*/
static HI_S32 s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat(HI_UNF_HDCP_HDCPKEY_S *pSrcKey,  HI_UNF_HDCP_DECRYPT_S *pDstkey)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *pu8EncryptKey = HI_NULL;
    HI_U8 *pu8ClearKey = HI_NULL;
    CIPHER_Config_CTRL CipherCtrl;

    if(!pSrcKey->EncryptionFlag)
    {
        HI_ERR_CIPHER("EncryptionFlag Error!\n");
        return HI_FAILURE;
    }

    memset(&CipherCtrl, 0, sizeof(CipherCtrl));
    pu8EncryptKey = pSrcKey->key.EncryptData.u8EncryptKey;
    pu8ClearKey = pDstkey->u8PrivateKey;

    pu8EncryptKey+=8; //跳过海思标记位：HISI_xxx
    if( memcmp("V0000001", pu8EncryptKey, 8) != 0 )
    {
        HI_ERR_CIPHER("EncryptKey check version failed\n");
        return HI_FAILURE;
    }
    pu8EncryptKey+=8; //跳过海思标记位：HISI_xxx
    pu8EncryptKey+=32; //跳过客户的ID号：xxxxxxxx

    memcpy((HI_U8 *)CipherCtrl.CIpstCtrl.u32Key, "zhong", 5);

    CipherCtrl.CIpstCtrl.bKeyByCA = HI_FALSE;
    CipherCtrl.CIpstCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.CIpstCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    CipherCtrl.CIpstCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.CIpstCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.CIpstCtrl.stChangeFlags.bit1IV = 1;

    ret = HI_DRV_CIPHER_CPU_Encrypt(pu8EncryptKey, 16,
               pu8ClearKey, CIPHER_HDCP_MODE_NO_HDCP_KEY, 0, 0, &CipherCtrl, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("(HI_DRV_CIPHER_CPU_Encrypt call failed\n");
        return HI_FAILURE;
    }
    memcpy(pDstkey->u8KSV, pu8ClearKey, 5);
    memcpy(pDstkey->u8PrivateKey, pu8ClearKey+8, 8);
    pu8ClearKey = pDstkey->u8PrivateKey+8;
    pu8EncryptKey += 16;

    CipherCtrl.CIpstCtrl.stChangeFlags.bit1IV = 0;
    ret = HI_DRV_CIPHER_CPU_Encrypt(pu8EncryptKey, 272,
               pu8ClearKey, CIPHER_HDCP_MODE_NO_HDCP_KEY, 0, 0, &CipherCtrl, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("(HI_DRV_CIPHER_CPU_Encrypt call failed\n");
        return HI_FAILURE;
    }

    return ret;
}

static HI_S32 s_DRV_CIPHER_CryptoFormattedHDCPKey(HI_U8 *pu8Input,
                                    HI_U32 u32InputLen,
                                    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                                    HI_U8 *pu8Output)
{
    CIPHER_Config_CTRL CipherCtrl;

    if ( NULL == pu8Input )
    {
        HI_ERR_CIPHER("Invalid param , null pointer input!\n");
        return HI_FAILURE;
    }

    if (NULL == pu8Output )
    {
        HI_ERR_CIPHER("Invalid param , null pointer!\n");
        return HI_FAILURE;
    }

    if ( HDCP_KEY_RAM_SIZE != u32InputLen)
    {
        HI_ERR_CIPHER("Invalid keylength input!\n");
        return HI_FAILURE;
    }

    memset(&CipherCtrl, 0, sizeof(CipherCtrl));
    CipherCtrl.CIpstCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.CIpstCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    CipherCtrl.CIpstCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.CIpstCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    memset(CipherCtrl.CIpstCtrl.u32IV, 0, sizeof(CipherCtrl.CIpstCtrl.u32IV));
    CipherCtrl.CIpstCtrl.stChangeFlags.bit1IV = 1;

    return HI_DRV_CIPHER_CPU_Encrypt(pu8Input, u32InputLen,
           pu8Output, CIPHER_HDCP_MODE_HDCP_KEY, enRootKeyType, HI_DRV_HDCPKEY_TX0,
           &CipherCtrl, HI_FALSE);
}

static HI_U8 DRV_CIPHER_CRC4(HI_U32 u32Value)
{
    HI_U8 u8Temp;
    HI_U8 u8CRC4 = 0;
    HI_S32 i;

    for (i=31; i>=0; i--)
    {
        u8Temp = ((u32Value >> ((unsigned int)i)) ^ (u8CRC4 >> 3)) & 0x01;
        u8CRC4 ^= u8Temp;
        u8CRC4 <<= 0x01;
        u8CRC4 |= u8Temp;
    }
    u8CRC4 &= 0x0F;

    return u8CRC4 ^ 0x05;
}

HI_S32 DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8  *pu8OutKey = HI_NULL;
    HI_U32 u32KeyLen = 0;
    HI_U32 u32CRC_0 = 0;
    HI_U32 u32CRC_1 = 0;
    HI_U8  u8Crc4 = 0;
    HI_U32 u32Ksv = 0;
    HI_UNF_HDCP_DECRYPT_S stDstKey;
    HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enHDCPRootKeyType = CIPHER_HDCP_KEY_TYPE_HISI_DEFINED;

    if ( NULL == pstHdcpKeyTransfer)
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }

    memset(&stDstKey, 0, sizeof(stDstKey));
    pu8OutKey = pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey;

    /* header config */
    pu8OutKey[u32KeyLen++] = (pstHdcpKeyTransfer->bIsUseOTPRootKey ? 0x00 : 0x80);
    pu8OutKey[u32KeyLen++] = 0x00;
    /* 'H' 'I' display that the Encrypted Hdpcp Key Exists */
    pu8OutKey[u32KeyLen++] = 'H';
    pu8OutKey[u32KeyLen++] = 'I';

    /* format clear text*/
    if ( HI_TRUE == pstHdcpKeyTransfer->stHdcpKey.EncryptionFlag)
    {
        ret = s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat(&pstHdcpKeyTransfer->stHdcpKey, &stDstKey);
        if(ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("s_DRV_CIPHER_DecryptHDCPKeyBeforeFormat failed!\n");
            return HI_FAILURE;
        }
        (HI_VOID)s_DRV_CIPHER_FormatHDCPKey(&stDstKey, &pu8OutKey[u32KeyLen]);
    }
    else
    {
        (HI_VOID)s_DRV_CIPHER_FormatHDCPKey(&pstHdcpKeyTransfer->stHdcpKey.key.DecryptData, &pu8OutKey[u32KeyLen]);
    }
    /* crc32_0 calculate */
    ret = Cipher_CRC32(&pu8OutKey[u32KeyLen], HDCP_KEY_RAM_SIZE, &u32CRC_0);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_0 calc failed!\n");
        return HI_FAILURE;
    }

    /* encrypt formated text*/
    if (pstHdcpKeyTransfer->bIsUseOTPRootKey)
    {
        enHDCPRootKeyType = CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY;
    }
//    HI_PRINT_HEX("CLEN-320", &pu8OutKey[u32KeyLen], HDCP_KEY_RAM_SIZE);
    u32Ksv  = pu8OutKey[u32KeyLen + 2];
    u32Ksv |= pu8OutKey[u32KeyLen + 3] << 8;
    u32Ksv |= pu8OutKey[u32KeyLen + 4] << 16;
    u32Ksv |= pu8OutKey[u32KeyLen + 5] << 24;
    u8Crc4 = DRV_CIPHER_CRC4(u32Ksv);
#ifdef DISPLAY_KSV_CRC
    HI_PRINT_HEX("KSV", &pu8OutKey[u32KeyLen + 1], 5);
    HI_PRINT("Encrypt HDCP key, KSV: 0x%x, CRC4 0x%02x\n", u32Ksv, u8Crc4);// shouble be 0x0C
#endif
    ret = s_DRV_CIPHER_CryptoFormattedHDCPKey(&pu8OutKey[u32KeyLen],
                                            HDCP_KEY_RAM_SIZE,
                                            enHDCPRootKeyType,
                                            &pu8OutKey[u32KeyLen]);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Encrypt HDCP Key using rootkey in otp failed!\n");
        return HI_FAILURE;
    }
    u32KeyLen+=HDCP_KEY_RAM_SIZE;
    memcpy(&pu8OutKey[u32KeyLen], &u32CRC_0, 4);
    u32KeyLen+=4;

    /* crc32_1  calculate */
    ret = Cipher_CRC32(pu8OutKey, u32KeyLen, &u32CRC_1);
    if ( HI_FAILURE == ret)
    {
        HI_ERR_CIPHER("CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
    memcpy(&pu8OutKey[u32KeyLen], &u32CRC_1, 4);
    u32KeyLen+=4;

    return HI_SUCCESS;
}
#endif //HDCP_ENABLE
