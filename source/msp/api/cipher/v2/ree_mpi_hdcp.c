/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_cipher.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

HI_S32 HI_MPI_CIPHER_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pstHdcpKey, HI_BOOL bIsUseOTPRootKey, HI_U8 u8OutEncryptKey[HDCP_KEY_CHIP_FILE_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HDCP_KEY_TRANSFER_S stDecryptHdcpKeyTransfer;

    INLET_PARAM_CHECK_POINT_NULL(pstHdcpKey);
    INLET_PARAM_CHECK_POINT_NULL(u8OutEncryptKey);

    cipher_memset_s(&stDecryptHdcpKeyTransfer, sizeof(stDecryptHdcpKeyTransfer), 0x0, sizeof(CIPHER_HDCP_KEY_TRANSFER_S));
    stDecryptHdcpKeyTransfer.bIsUseOTPRootKey = bIsUseOTPRootKey;
    cipher_memcpy_s(&stDecryptHdcpKeyTransfer.stHdcpKey, sizeof(stDecryptHdcpKeyTransfer.stHdcpKey), pstHdcpKey, sizeof(HI_UNF_HDCP_HDCPKEY_S));

    ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPTHDCPKEY, &stDecryptHdcpKeyTransfer);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("cmd encrypt hdcpkey failed!\n");
        return HI_FAILURE;
    }

    cipher_memcpy_s(u8OutEncryptKey, HDCP_KEY_CHIP_FILE_SIZE, stDecryptHdcpKeyTransfer.u8FlashEncryptedHdcpKey, HDCP_KEY_CHIP_FILE_SIZE);

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_LoadHDCPKey(HI_U8 *pu8EncryptedHDCPKey, HI_U32 u32Len)
{
    HI_S32 ret = HI_SUCCESS;
    HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S stHdcpKey;

    INLET_PARAM_CHECK_POINT_NULL(pu8EncryptedHDCPKey);

    if (HDCP_KEY_CHIP_FILE_SIZE != u32Len)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    cipher_memset_s(&stHdcpKey, sizeof(stHdcpKey), 0, sizeof(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S));
    cipher_memcpy_s(&stHdcpKey.u8Key, sizeof(stHdcpKey.u8Key), pu8EncryptedHDCPKey, u32Len);
    stHdcpKey.u32KeyLen = u32Len;
    stHdcpKey.enHDCPVersion = HI_DRV_HDCP_VERIOSN_1x;
    stHdcpKey.enHDCPKeyType = HI_DRV_HDCPKEY_TX0;

    ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_LOADHDCPKEY, &stHdcpKey);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Load hdcpkey failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

