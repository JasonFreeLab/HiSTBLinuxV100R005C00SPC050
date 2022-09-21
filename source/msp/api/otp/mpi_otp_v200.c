/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
    File Name   : mpi_otp_v200.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "hi_unf_otp.h"
#include "otp_enum.h"
#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "drv_otp_ioctl.h"
#include "hi_mpi_otp_v200.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 g_otp_dev_fd    =   -1;
HI_S32 g_otp_open_cnt  =   0;
pthread_mutex_t   g_otp_mutex = PTHREAD_MUTEX_INITIALIZER;

extern HI_S32 OTP_DRV_Init(HI_VOID);
extern HI_S32 OTP_DRV_DeInit(HI_VOID);
extern HI_S32 OTP_DRV_Reset(HI_VOID);
extern HI_S32 OTP_DRV_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv_list, HI_U32 num);
extern HI_S32 OTP_DRV_DebugProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv_list, HI_U32 num);
extern HI_S32 OTP_DRV_PVItemByName(HI_CHAR *otp_name, HI_U32 name_len, HI_BOOL is_write,
                                   HI_U8 *value, HI_U32 *value_len, HI_BOOL is_lock);
extern HI_S32 OTP_DRV_PVItem(HI_OTP_DATA_E field_id, HI_BOOL is_write,
                             HI_U8 *value, HI_U32 *value_len, HI_BOOL is_lock);

extern HI_S32 OTP_DRV_PVItemLock(HI_OTP_DATA_E field_id, HI_BOOL is_write, HI_BOOL *lock);

extern HI_S32 OTP_DRV_PVItemIdxByName(HI_CHAR * otp_name, HI_U32 name_len, HI_BOOL is_write,
    HI_U8 *     value, HI_U32 * value_len, HI_BOOL is_lock, HI_U32 idx);

extern HI_S32 OTP_DRV_PVItemIdxLockByName(HI_CHAR * otp_name, HI_U32 name_len, HI_BOOL is_write, HI_BOOL * lock,
     HI_U32     idx, HI_U32 u32Length);

HI_U32 otp_data_output[] =
{
#ifdef HI_OTP_DEBUG_SUPPORT
#include OTP_DATA_FILE_DEBUG
#endif
#ifdef HI_OTP_CONAX_SUPPORT
#include OTP_DATA_FILE_CONAX
#endif
#ifdef HI_OTP_NAGRA_SUPPORT
#include OTP_DATA_FILE_NAGRA
#endif
#ifdef HI_OTP_VERIMATRIX_SUPPORT
#include OTP_DATA_FILE_VERIMATRIX
#endif
};



HI_U32 OTP_DataSize(HI_VOID)
{
    return sizeof(otp_data_output);
}

HI_S32 OTP_PVItemWrite(HI_OTP_DATA_E field_id, HI_U8 *value, HI_U32 *value_len)
{
    return OTP_DRV_PVItem(field_id, HI_TRUE, value, value_len, HI_TRUE);
}

HI_S32 OTP_PVItemRead(HI_OTP_DATA_E field_id, HI_U8 *value, HI_U32 *value_len)
{
    return OTP_DRV_PVItem(field_id, HI_FALSE, value, value_len, HI_TRUE);
}

HI_S32 HI_MPI_OTP_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    HI_OTP_LOCK();

    if (-1 != g_otp_dev_fd)
    {
        g_otp_open_cnt++;
        HI_OTP_UNLOCK();
        return HI_SUCCESS;
    }

    g_otp_dev_fd = open("/dev/" UMAP_DEVNAME_OTP, O_RDWR, 0);
    if ( g_otp_dev_fd < 0)
    {
        HI_ERR_OTP("Open OTP ERROR. [%d:%s]\n", errno, strerror(errno));
        HI_OTP_UNLOCK();
        return HI_FAILURE;
    }

    ret = OTP_DRV_Init();
    if (ret)
    {
        HI_ERR_OTP("Init otp data failed ret=%d.\n", ret);
        HI_OTP_UNLOCK();
        return HI_FAILURE;
    }
    g_otp_open_cnt++;
    HI_OTP_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_DeInit(HI_VOID)
{
    HI_OTP_LOCK();

    if ( g_otp_dev_fd < 0)
    {
        HI_OTP_UNLOCK();
        return HI_SUCCESS;
    }

    /*OTP_DRV_DeInit ²»ÒªÖ´ÐÐ*/

    g_otp_open_cnt--;
    if ( 0 == g_otp_open_cnt)
    {
        close(g_otp_dev_fd);
        g_otp_dev_fd = -1;
    }

    HI_OTP_UNLOCK();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_SetCustomerKey(HI_U8 *key, HI_U32 key_len)
{
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(key);
    CHECK_OTP_PARAM(key_len != 16);

    ret = OTP_PVItemWrite(HI_OTP_CUSTOMER_KEY, key, &key_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set customer key failed, return:%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetCustomerKey(HI_U8 *key, HI_U32 key_len)
{
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(key);
    CHECK_OTP_PARAM(key_len != 16);

    ret = OTP_PVItemRead(HI_OTP_CUSTOMER_KEY, key, &key_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get customer key failed, return:%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_SetStbPrivData(HI_U32 offset, HI_U8 data)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8  private_data[16] = {0};
    HI_U32 len = 16;

    CHECK_OTP_PARAM(offset >= 16);

    private_data[offset] = data;

    ret= OTP_DRV_PVItem(HI_OTP_STB_PRIVATE_DATA, HI_TRUE, private_data, &len, HI_FALSE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Set stb private data failed, return:%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetStbPrivData(HI_U32 offset, HI_U8 *data)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 private_data[16] = {0};
    HI_U32 len = 16;

    CHECK_NULL_PTR(data);
    CHECK_OTP_PARAM(offset >= 16);

    ret = OTP_DRV_PVItem(HI_OTP_STB_PRIVATE_DATA, HI_FALSE, private_data, &len, HI_FALSE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get stb private data failed, return:%x\n", ret);
        return ret;
    }

    *data = private_data[offset];

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_BurnToNormalChipset(HI_VOID)
{
    HI_U32 data = 0x2A13C812;
    HI_U32 len = 4;

    return OTP_PVItemWrite(HI_OTP_SEC_WORD, (HI_U8 *)&data, &len);
}

HI_S32 HI_MPI_OTP_BurnToSecureChipset(HI_VOID)
{
    HI_U32 data = 0x6EDBE953;
    HI_U32 len = 4;

    return OTP_PVItemWrite(HI_OTP_SEC_WORD, (HI_U8 *)&data, &len);
}

HI_S32 HI_MPI_OTP_GetIDWordLockFlag(HI_BOOL *pbLock)
{
    HI_S32 ret   = HI_FAILURE;
    HI_BOOL lock = HI_FALSE;

    CHECK_NULL_PTR(pbLock);

    ret = OTP_DRV_PVItemLock(HI_OTP_SEC_WORD, HI_FALSE, &lock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get ID word lock status\n");
        return ret;
    }

    *pbLock = lock;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetVendorID(HI_UNF_OTP_VENDORID_E *vendor_id)
{
    HI_U8 data = 0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(vendor_id);

    ret = OTP_PVItemRead(HI_OTP_CA_VENDOR_ID, (HI_U8 *)&data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get ca vendor id failed, return:%x\n", ret);
        return ret;
    }

    *vendor_id = data;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetStbSN(HI_U8 *stb_sn, HI_U32 *plen)
{
    CHECK_NULL_PTR(stb_sn);
    CHECK_NULL_PTR(plen);
    CHECK_OTP_PARAM(*plen != 4);

    return OTP_PVItemRead(HI_OTP_STB_SN, stb_sn, plen);
}

HI_S32 HI_MPI_OTP_SetStbSN(HI_U8 *stb_sn, HI_U32 len)
{
    CHECK_NULL_PTR(stb_sn);
    CHECK_OTP_PARAM(len != 4);

    return OTP_PVItemWrite(HI_OTP_STB_SN, stb_sn, &len);
}

HI_S32 HI_MPI_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E flash_type)
{
    HI_U8 data = flash_type;
    HI_U32 len = 1;

    CHECK_OTP_PARAM(flash_type >= HI_UNF_OTP_FLASH_TYPE_BUTT);

    return OTP_PVItemWrite(HI_OTP_BOOT_MODE_SEL, &data, &len);
}

HI_S32 HI_MPI_OTP_DisableSelfBoot(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 data = 0xF;
    HI_U32 len = 1;

    ret = OTP_PVItemWrite(HI_OTP_USB_SELF_BOOT_DISABLE, &data, &len);
    ret |= OTP_PVItemWrite(HI_OTP_UART_SELF_BOOT_DISABLE, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to disable self boot, return:%x\n",ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetSelfBootStat(HI_BOOL *disable)
{
    HI_U8 usb_disable = 0x0;
    HI_U8 uart_disable = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(disable);

    ret = OTP_PVItemRead(HI_OTP_USB_SELF_BOOT_DISABLE, &usb_disable, &len);
    ret |= OTP_PVItemRead(HI_OTP_UART_SELF_BOOT_DISABLE, &uart_disable, &len);
    if ((usb_disable == 0x5) && (uart_disable == 0x5))
    {
        *disable = HI_FALSE;
    }
    else if ((usb_disable == 0xf) && (uart_disable == 0xf))
    {
        *disable = HI_TRUE;
    }
    else
    {
        HI_ERR_OTP("self boot status is not expected value, usb:%x, uart:%x\n", usb_disable, uart_disable);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_EnableBootDecrypt(HI_VOID)
{
    HI_U8 data = 0x1;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_BLOAD_DEC_EN, &data, &len);
}

HI_S32 HI_MPI_OTP_GetBootDecryptStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(enable);

    ret = OTP_PVItemRead(HI_OTP_BLOAD_DEC_EN, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get boot decrypt status, return:%X\n", ret);
        return ret;
    }

    *enable = data;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_EnableSCS(HI_VOID)
{
    HI_U8 data = 0xff;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_SCS_ACTIVATION, &data, &len);
}

HI_S32 HI_MPI_OTP_GetSCSStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(enable);
    ret = OTP_PVItemRead(HI_OTP_SCS_ACTIVATION, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get scs status, return:%x\n", ret);
        return ret;
    }

    *enable = (data == 0x81) ? 0: 1;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_EnableTrustZone(HI_VOID)
{
    HI_U8 data = 0xff;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_SOC_TEE_ENABLE, &data, &len);
}

HI_S32 HI_MPI_OTP_GetTrustZoneStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(enable);

    ret = OTP_PVItemRead(HI_OTP_SOC_TEE_ENABLE, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get scs status, return:%x\n", ret);
        return ret;
    }

    *enable = (data == 0x42) ? HI_FALSE : HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetMSID(HI_U8 *msid, HI_U32 *plen)
{
    CHECK_NULL_PTR(msid);
    CHECK_NULL_PTR(plen);
    CHECK_OTP_PARAM(*plen != 4);

    return OTP_PVItemRead(HI_OTP_MSID, msid, plen);
}

HI_S32 HI_MPI_OTP_SetMSID(HI_U8 *msid, HI_U32 len)
{
    CHECK_NULL_PTR(msid);
    CHECK_OTP_PARAM(len != 4);

    return OTP_PVItemWrite(HI_OTP_MSID, msid, &len);
}

HI_S32 HI_MPI_OTP_GetSOSMSID(HI_U8 *sos_msid, HI_U32 *plen)
{
    CHECK_NULL_PTR(sos_msid);
    CHECK_NULL_PTR(plen);
    CHECK_OTP_PARAM(*plen != 4);

    return OTP_PVItemRead(HI_OTP_SOS_MSID, sos_msid, plen);
 }

HI_S32 HI_MPI_OTP_SetSOSMSID(HI_U8 *sos_msid, HI_U32 len)
{
    CHECK_NULL_PTR(sos_msid);
    CHECK_OTP_PARAM(len != 4);

    return OTP_PVItemWrite(HI_OTP_SOS_MSID, sos_msid, &len);
}

HI_S32 HI_MPI_OTP_SetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length)
{
    CHECK_NULL_PTR(pFuseName);
    CHECK_NULL_PTR(pu8Value);

    if( u32Length == 0 )
    {
        HI_ERR_OTP("Failed u32Length[0]\n");
        return HI_FAILURE;
    }
    if( u32Offset + u32Length > OTP_FIELD_VALUE_MAX_LEN )
    {
        HI_ERR_OTP("Failed u32Offset u32Length too long [ %u > %u ]\n", u32Offset + u32Length , OTP_FIELD_VALUE_MAX_LEN);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemIdxByName(pFuseName, strlen(pFuseName), HI_TRUE,
        pu8Value, &u32Length, HI_TRUE, u32Offset);
}

HI_S32 HI_MPI_OTP_GetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length)
{
    CHECK_NULL_PTR(pFuseName);
    CHECK_NULL_PTR(pu8Value);

    if( u32Length == 0 )
    {
        HI_ERR_OTP("Failed u32Length[0]\n");
        return HI_FAILURE;
    }
    if( u32Offset + u32Length > OTP_FIELD_VALUE_MAX_LEN )
    {
        HI_ERR_OTP("Failed u32Offset u32Length too long [ %u > %u ]\n", u32Offset + u32Length , OTP_FIELD_VALUE_MAX_LEN);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemIdxByName(pFuseName, strlen(pFuseName), HI_FALSE,
        pu8Value, &u32Length, HI_TRUE, u32Offset);
}

HI_S32 HI_MPI_OTP_SetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length)
{
	HI_BOOL lock;
    CHECK_NULL_PTR(pFuseName);

    if( u32Length == 0 )
    {
        HI_ERR_OTP("Failed u32Length[0]\n");
        return HI_FAILURE;
    }
    if( u32Offset + u32Length > OTP_FIELD_VALUE_MAX_LEN )
    {
        HI_ERR_OTP("Failed u32Offset u32Length too long [ %u > %u ]\n", u32Offset + u32Length , OTP_FIELD_VALUE_MAX_LEN);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemIdxLockByName(pFuseName, strlen(pFuseName), HI_TRUE,
        &lock , u32Offset, u32Length);
}

HI_S32 HI_MPI_OTP_GetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length, HI_U32 * pu32Lock)
{
    CHECK_NULL_PTR(pFuseName);
    CHECK_NULL_PTR(pu32Lock);

    if( u32Length == 0 )
    {
        HI_ERR_OTP("Failed u32Length[0]\n");
        return HI_FAILURE;
    }
    if( u32Offset + u32Length > OTP_FIELD_VALUE_MAX_LEN )
    {
        HI_ERR_OTP("Failed u32Offset u32Length too long [ %u > %u ]\n", u32Offset + u32Length , OTP_FIELD_VALUE_MAX_LEN);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemIdxLockByName(pFuseName, strlen(pFuseName), HI_FALSE,
            pu32Lock, u32Offset, u32Length);
}

HI_S32 HI_MPI_OTP_DisableDDRWakeup(HI_VOID)
{
    HI_U8 data = 0x1;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_DDR_WAKEUP_DISABLE, &data, &len);
}

HI_S32 HI_MPI_OTP_GetDDRWakeupStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(enable);

    ret = OTP_PVItemRead(HI_OTP_DDR_WAKEUP_DISABLE, &data, &len);
    if(ret != HI_SUCCESS)
    {
        HI_FATAL_OTP("Get DDRWakeup status failed.ret =%d.\n", ret);
        return ret;
    }
    *enable = data & 0x01;
    return ret;
}

HI_S32 HI_MPI_OTP_LockGlobalOTP(HI_VOID)
{
    HI_U8 data = 0x1;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_OTP_GLOBAL_LOCK_EN, &data, &len);
}

HI_S32 HI_MPI_OTP_GetGlobalOTPLockStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(enable);

    ret = OTP_PVItemRead(HI_OTP_OTP_GLOBAL_LOCK_EN, &data, &len);
    *enable = data;
    return ret;
}

HI_S32 HI_MPI_OTP_EnableRuntimeCheck(HI_VOID)
{
    HI_U8 data = 0x1;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_RUNTIME_CHECK_EN, &data, &len);
}

HI_S32 HI_MPI_OTP_GetRuntimeCheckStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(enable);
    ret = OTP_PVItemRead(HI_OTP_RUNTIME_CHECK_EN, &data, &len);
    *enable = data;
    return ret;
}

HI_S32 HI_MPI_OTP_DisableDDRWakeupCheck(HI_VOID)
{
    HI_U8 data = 0xa;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_WAKEUP_DDR_CHECK_EN, &data, &len);
}

HI_S32 HI_MPI_OTP_GetDDRWakeupCheckStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(enable);
    ret = OTP_PVItemRead(HI_OTP_WAKEUP_DDR_CHECK_EN, &data, &len);
    *enable = (data == 0xa) ? HI_FALSE : HI_TRUE;
    return ret;
}

HI_S32 HI_MPI_OTP_EnableDDRScramble(HI_VOID)
{
    HI_U8 data = 0xFF;
    HI_U32 len = 1;

    return OTP_PVItemWrite(HI_OTP_DDR_SCRAMBLE_EN, &data, &len);
}

HI_S32 HI_MPI_OTP_GetDDRScrambleStat(HI_BOOL *enable)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(enable);
    ret = OTP_PVItemRead(HI_OTP_DDR_SCRAMBLE_EN, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get ddr scrambleStat failed, return:%x\n", ret);
        return ret;
    }

    *enable = (data == 0x81) ? HI_FALSE : HI_TRUE;
    return ret;
}

HI_S32 HI_MPI_OTP_GetJtagMode(HI_UNF_OTP_JTAG_MODE_E *jtag_mode)
{
    HI_U8 data = 0x0;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;

    CHECK_NULL_PTR(jtag_mode);
    ret = OTP_PVItemRead(HI_OTP_CHIP_JTAG_PRT_MODE, &data, &len);
    if (ret)
    {
        HI_FATAL_OTP("Fail to get jtag mode, return 0x%x.\n", ret);
        return ret;
    }

    if (0x42 == data)
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_OPEN;
    }
    else if (0x63 == data)
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_PROTECT;
    }
    else
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_CLOSED;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_SetJtagMode(HI_UNF_OTP_JTAG_MODE_E jtag_mode)
{
    HI_U8 data = 0xff;
    HI_U32 len = 1;
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_OTP_JTAG_MODE_E otp_jtag_mode = HI_UNF_OTP_JTAG_MODE_BUTT;

    if(jtag_mode >= HI_UNF_OTP_JTAG_MODE_BUTT)
    {
        HI_FATAL_OTP("Set jtag mode, parameters check failed, mode=%d.\n", jtag_mode);
        return HI_ERR_OTP_INVALID_PARA;
    }

    ret = HI_MPI_OTP_GetJtagMode(&otp_jtag_mode);
    if (ret)
    {
        HI_ERR_OTP("Fail to get jtag mode, return 0x%x.\n", ret);
        return ret;
    }

    if(jtag_mode == otp_jtag_mode)
    {
        HI_INFO_OTP("Need not to set jtag mode again.\n");
        return HI_SUCCESS;
    }

    if(jtag_mode == HI_UNF_OTP_JTAG_MODE_OPEN)
    {
        data = 0x42;
        if(otp_jtag_mode != HI_UNF_OTP_JTAG_MODE_OPEN)
        {
            HI_FATAL_OTP("Not support set mode OPEN, jtag mode that get frome otp is %d.\n", otp_jtag_mode);
            return HI_ERR_OTP_NOT_SUPPORT;
        }
    }

    if(jtag_mode == HI_UNF_OTP_JTAG_MODE_PROTECT)
    {
        data = 0x63;
        if(otp_jtag_mode == HI_UNF_OTP_JTAG_MODE_CLOSED)
        {
            HI_FATAL_OTP("Not support set mode PROTECT.\n");
            return HI_ERR_OTP_NOT_SUPPORT;
        }
    }

    ret = OTP_PVItemWrite(HI_OTP_CHIP_JTAG_PRT_MODE, &data, &len);
    if (ret)
    {
        HI_FATAL_OTP("Fail to set jtag mode, return 0x%x.\n", ret);
    }

    return ret;
}

HI_S32 HI_MPI_OTP_GetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E *jtag_mode)
{
    HI_U8 jtag_data = 0x0;
    HI_U8 tz_data   = 0x0;
    HI_U32 jtag_len = 1;
    HI_U32 tz_len   = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULL_PTR(jtag_mode);

    ret = OTP_PVItemRead(HI_OTP_TEE_JTAG_MODE, &jtag_data, &jtag_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to get tee jtag mode, return:0x%x.\n", ret);
        return ret;
    }

    if (jtag_data >= 2)
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_CLOSED;
        return HI_SUCCESS;
    }
    else if (jtag_data == 1)
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_PROTECT;
        return HI_SUCCESS;
    }

    ret = OTP_PVItemRead(HI_OTP_SOC_TEE_ENABLE, &tz_data, &tz_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to get trust zone enable, return:0x%x.\n", ret);
        return ret;
    }

    if (tz_data == 1)
    {
        *jtag_mode = HI_UNF_OTP_JTAG_MODE_PROTECT;
        return HI_SUCCESS;
    }

    *jtag_mode = HI_UNF_OTP_JTAG_MODE_OPEN;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_SetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E jtag_mode)
{
    HI_U8 data = 0;
    HI_U32 len = 1;
    HI_S32 ret = HI_FAILURE;

    if(jtag_mode >= HI_UNF_OTP_JTAG_MODE_BUTT)
    {
        HI_ERR_OTP("Set jtag mode, parameters check failed, mode=%d.\n", jtag_mode);
        return HI_ERR_OTP_INVALID_PARA;
    }

    ret = OTP_PVItemRead(HI_OTP_TEE_JTAG_MODE, &data, &len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to get tee jtag mode, return:0x%x.\n", ret);
        return ret;
    }

    if (jtag_mode < data)
    {
        HI_ERR_OTP("Fail to set tee jtag mode, set:%x, but otp is already:%x\n");
        return HI_ERR_OTP_INVALID_PARA;
    }

    return OTP_PVItemWrite(HI_OTP_TEE_JTAG_MODE, &data, &len);
}

HI_S32 HI_MPI_OTP_GetBootVersionID(HI_U8 *version_id, HI_U32 *plen)
{
    CHECK_NULL_PTR(version_id);
    CHECK_NULL_PTR(plen);
    CHECK_OTP_PARAM(*plen != 4);

    return OTP_PVItemRead(HI_OTP_STB_VERSION_REF, version_id, plen);
}

HI_S32 HI_MPI_OTP_SetBootVersionID(HI_U8 *version_id, HI_U32 len)
{
    CHECK_NULL_PTR(version_id);
    CHECK_OTP_PARAM(len != 4);

    return OTP_PVItemWrite(HI_OTP_STB_VERSION_REF, version_id, &len);
}

HI_S32 HI_MPI_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E type, HI_U8 *key, HI_U32 len)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 key_len = 16;
    HI_OTP_DATA_E id = HI_OTP_DATA_BUTT;

    CHECK_NULL_PTR(key);
    switch(type)
    {
        case HI_UNF_OTP_OEM_ROOTKEY:
            id = HI_OTP_OEM_ROOTKEY;
            break;
        case HI_UNF_OTP_HDCP_ROOTKEY:
            id = HI_OTP_HDCP_ROOTKEY;
            break;
        case HI_UNF_OTP_STB_ROOTKEY:
            id = HI_OTP_STB_ROOTKEY;
            break;
        case HI_UNF_OTP_SW_ROOTKEY:
            id = HI_OTP_SW_ROOTKEY;
            break;
        case HI_UNF_OTP_STBTA_ROOTKEY:
            id = HI_OTP_STB_TA_ROOTKEY;
            break;
        default:
            HI_ERR_OTP("unkonwn ROOTKEY type=%d.\n", type);
            return HI_ERR_OTP_INVALID_PARA;
    }

    if(key_len != len)
    {
        HI_ERR_OTP("error length. provide length %d, need length %d.\n", len, key_len);
        return HI_ERR_OTP_INVALID_PARA;
    }

    ret = OTP_PVItemWrite(id, key, &key_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to write rootkey(%d), return:0x%x.\n", id, ret);
        return ret;
    }
#if 0
    if(reset)
    {
        ret = OTP_DRV_Reset();
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E type, HI_BOOL *pbLock)
{
    HI_OTP_DATA_E id = HI_OTP_DATA_BUTT;
    HI_S32 ret       = HI_FAILURE;
    HI_BOOL lock     = HI_FALSE;

    switch(type)
    {
        case HI_UNF_OTP_OEM_ROOTKEY:
            id = HI_OTP_OEM_ROOTKEY;
            break;
        case HI_UNF_OTP_HDCP_ROOTKEY:
            id = HI_OTP_HDCP_ROOTKEY;
            break;
        case HI_UNF_OTP_STB_ROOTKEY:
            id = HI_OTP_STB_ROOTKEY;
            break;
        case HI_UNF_OTP_SW_ROOTKEY:
            id = HI_OTP_SW_ROOTKEY;
            break;
        case HI_UNF_OTP_STBTA_ROOTKEY:
            id = HI_OTP_STB_TA_ROOTKEY;
            break;
        default:
            HI_ERR_OTP("unkonwn ROOTKEY type=%d.\n", type);
            return HI_ERR_OTP_INVALID_PARA;
    }

    ret =  OTP_DRV_PVItemLock(id, HI_FALSE, &lock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get rootkey(%d) lock status, return:0x%x\n", id, ret);
        return ret;
    }

    *pbLock = lock;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv, HI_U32 u32Num)
{
    HI_U32 i = 0;
    HI_UNF_OTP_BURN_PV_ITEM_S *pv_item = NULL;

    CHECK_OTP_INIT();
    CHECK_NULL_PTR(pv);

    for (i = 0; i < u32Num; i++)
    {
        pv_item = pv + i;
        if (pv_item->bBurn != HI_TRUE && pv_item->bBurn != HI_FALSE)
        {
            HI_FATAL_OTP("bBurn check failed. [%d]\n", pv_item->bBurn);
            return HI_ERR_OTP_INVALID_PARA;
        }

        if (pv_item->bLock != HI_TRUE && pv_item->bLock != HI_FALSE)
        {
            HI_FATAL_OTP("bLock check failed. [%d]\n", pv_item->bLock);
            return HI_ERR_OTP_INVALID_PARA;
        }

        if (pv_item->u32ValueLen > OTP_FIELD_VALUE_MAX_LEN)
        {
            HI_FATAL_OTP("u32ValueLen check failed. [%d]\n", pv_item->u32ValueLen);
            return HI_ERR_OTP_INVALID_PARA;
        }

        if (strlen(pv_item->aszFieldName) >= OTP_FIELD_NAME_MAX_LEN)
        {
            HI_FATAL_OTP("u32ValueLen check failed. [%d]\n", pv_item->u32ValueLen);
            return HI_ERR_OTP_INVALID_PARA;
        }
    }

    return OTP_DRV_BurnProductPV(pv, u32Num);
}

HI_S32 HI_MPI_OTP_VerifyProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pv, HI_U32 u32Num)
{
    HI_U32 i = 0;
    HI_UNF_OTP_BURN_PV_ITEM_S *pv_item = NULL;

    CHECK_OTP_INIT();
    CHECK_NULL_PTR(pv);

    for (i = 0; i < u32Num; i++)
    {
        pv_item = pv + i;
        if (pv_item->bBurn != HI_TRUE && pv_item->bBurn != HI_FALSE)
        {
            HI_FATAL_OTP("bBurn check failed. [%d]\n", pv_item->bBurn);
            return HI_ERR_OTP_INVALID_PARA;
        }
        if (pv_item->bLock != HI_TRUE && pv_item->bLock != HI_FALSE)
        {
            HI_FATAL_OTP("bLock check failed. [%d]\n", pv_item->bLock);
            return HI_ERR_OTP_INVALID_PARA;
        }
        if (pv_item->u32ValueLen > OTP_FIELD_VALUE_MAX_LEN)
        {
            HI_FATAL_OTP("u32ValueLen check failed. [%d]\n", pv_item->u32ValueLen);
            return HI_ERR_OTP_INVALID_PARA;
        }
        if (strlen(pv_item->aszFieldName) >= OTP_FIELD_NAME_MAX_LEN)
        {
            HI_FATAL_OTP("u32ValueLen check failed. [%d]\n", pv_item->u32ValueLen);
            return HI_ERR_OTP_INVALID_PARA;
        }
    }
    return OTP_DRV_DebugProductPV(pv, u32Num);
}

HI_S32 HI_MPI_OTP_SetOtpFuse(HI_CHAR *field_name, HI_U32 name_len, HI_U8 *value, HI_U32 value_len)
{
    CHECK_NULL_PTR(field_name);
    CHECK_NULL_PTR(value);
    if (name_len >= OTP_FIELD_NAME_MAX_LEN || value_len > OTP_FIELD_VALUE_MAX_LEN)
    {
        HI_FATAL_OTP("[get]parameters check failed, otp name len=%d, value len=%d.\n", name_len, value_len);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemByName(field_name, name_len, HI_TRUE, value, &value_len, HI_TRUE);
}

HI_S32 HI_MPI_OTP_GetOtpFuse(HI_CHAR *field_name, HI_U32 name_len, HI_U8 *value, HI_U32 value_len)
{
    CHECK_NULL_PTR(field_name);
    CHECK_NULL_PTR(value);
    if (name_len >= OTP_FIELD_NAME_MAX_LEN || value_len > OTP_FIELD_VALUE_MAX_LEN)
    {
        HI_FATAL_OTP("[get]parameters check failed, otp name len=%d, value len=%d.\n", name_len, value_len);
        return HI_FAILURE;
    }
    return OTP_DRV_PVItemByName(field_name, name_len, HI_FALSE, value, &value_len, HI_TRUE);
}

HI_S32 HI_MPI_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 rsakey[512] = {0};
    HI_U32 rsa_key_len = 256;
    HI_U32 rsa_exponent_len = 16;

    CHECK_NULL_PTR(pu8Key);
    CHECK_OTP_PARAM(u32KeyLen != 512);

    memcpy(rsakey, pu8Key, 512);

    ret = OTP_PVItemWrite(HI_OTP_RSAROOTPUBLICKEYMODULUS, rsakey, &rsa_key_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to set rsa key, return:%x\n", ret);
        return ret;
    }

    ret = OTP_PVItemWrite(HI_OTP_RSAROOTPUBLICKEYEXPONENT, &rsakey[496], &rsa_exponent_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to set rsa exponent, return:%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_OTP_GetRSALockStat(HI_BOOL *pbLock)
{
    HI_S32 ret = HI_FAILURE;
    HI_BOOL lock = HI_FALSE;

    CHECK_NULL_PTR(pbLock);

    ret = OTP_DRV_PVItemLock(HI_OTP_RSAROOTPUBLICKEYMODULUS, HI_FALSE, &lock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed te get rsa lock, return:%x\n", ret);
        return ret;
    }

    *pbLock = lock;
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
