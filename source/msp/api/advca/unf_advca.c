/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_advca.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : Hisilicon CA API definition
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <limits.h>

#include "hi_common.h"
#include "hi_unf_advca.h"
#include "hi_drv_struct.h"
#include "hi_error_mpi.h"
#include "hi_drv_advca.h"
#include "drv_advca_ioctl.h"
#include "drv_otp_ioctl.h"
#include "drv_otp_ext.h"
#include "hi_unf_cipher.h"
#include "hi_mpi_cipher.h"


static HI_S32 g_s32CaFd = -1;
static HI_S32 g_AdvcaInitCounter = -1;

static HI_UNF_ADVCA_KEYLADDER_LEV_E g_dvbLadder;
static HI_UNF_ADVCA_KEYLADDER_LEV_E g_r2rLadder;
static HI_UNF_ADVCA_VENDORID_E g_vendorType;

static HI_HANDLE  g_hCipher ;
static HI_BOOL g_bCryptologyConfig = HI_FALSE;


#define CA_CheckPointer(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            HI_ERR_CA("pointer parameter is NULL.\n"); \
            return -1; \
        } \
    } while (0)

#define CA_ASSERT(api, ret) \
    do{ \
        ret = api; \
        if (ret != HI_SUCCESS) \
        { \
            HI_ERR_CA("run %s failed, ERRNO:%#x.\n", #api, ret); \
            return ret;\
        } \
        else\
        {\
        /*HI_INFO_CA("sample %s: run %s ok.\n", __FUNCTION__, #api);}*/   \
        }\
    }while(0)

extern HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen);

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_Init
*  Description:    open ca
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_Init(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 s32DevFd = 0;
    HI_U32 u32VendorType = 0;
    if (g_AdvcaInitCounter > 0)
    {
        g_AdvcaInitCounter++;
        return HI_SUCCESS;
    }

    s32DevFd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR, 0);
    if (s32DevFd < 0)
    {
        HI_ERR_CA("ca open err. \n");
        return HI_ERR_CA_OPEN_ERR;
    }
    g_AdvcaInitCounter = 1;

    g_s32CaFd   = s32DevFd;
    ret = HI_UNF_ADVCA_GetDVBKeyLadderStage(&g_dvbLadder);
    ret |= HI_UNF_ADVCA_GetR2RKeyLadderStage(&g_r2rLadder);
    ret |= HI_UNF_ADVCA_GetVendorID(&u32VendorType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type err. \n");
        (HI_VOID)HI_UNF_ADVCA_DeInit();
        return HI_FAILURE;
    }

    g_vendorType = (HI_UNF_ADVCA_VENDORID_E)u32VendorType;


    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_DeInit
*  Description:    close ca
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:      ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID)
{
    if(g_AdvcaInitCounter > 0)
    {
        g_AdvcaInitCounter--;
    }

    if(g_AdvcaInitCounter != 0)
    {
        return HI_SUCCESS;
    }

    close(g_s32CaFd);
    g_s32CaFd   = -1;
    g_AdvcaInitCounter = -1;

    g_dvbLadder = HI_UNF_ADVCA_KEYLADDER_BUTT;
    g_r2rLadder = HI_UNF_ADVCA_KEYLADDER_BUTT;
    g_vendorType = HI_UNF_ADVCA_NULL;

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetChipId
*  Description:    get chip id
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pu32ChipId)
    {
        HI_ERR_CA("pu32ChipId == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_CHIPID, pu32ChipId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_CHIPID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetMarketId
*  Description:    get market id
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetMarketId(HI_U8 u8MarketId[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8MarketId)
    {
        HI_ERR_CA("pu32MarketId == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_MARKETID, u8MarketId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_MARKETID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetMarketId
*  Description:    set market id
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetMarketId(HI_U8 u8MarketId[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }
    if (HI_NULL == u8MarketId)
    {
        HI_ERR_CA("pu32MarketId == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_MARKETID, u8MarketId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_MARKETID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetStbSn
*  Description:    get stb serial number
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U8 u8StbSn[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8StbSn)
    {
        HI_ERR_CA("u8StbSn == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_STBSN, u8StbSn);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_STBSN err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetSerialNumber
*  Description:    set stb serial number
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetStbSn(HI_U8 u8StbSn[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8StbSn)
    {
        HI_ERR_CA("u8StbSn == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    ret = ioctl(g_s32CaFd, CMD_CA_SET_STBSN, u8StbSn);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_STBSN err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetVersionId
*  Description:    get version id
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetVersionId(HI_U8 u8VersionId[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8VersionId)
    {
        HI_ERR_CA("u8VersionId == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_VERSIONID, u8VersionId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_VERSIONID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetVersionId
*  Description:    set version id
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetVersionId(HI_U8 u8VersionId[4])
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8VersionId)
    {
        HI_ERR_CA("u8VersionId == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_VERSIONID, u8VersionId);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_VERSIONID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_LockHardCwSel
*  Description:    Set hardware CW word only. Default, it depend on the configure of Demux.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_LockHardCwSel(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_LOCKHARDCWSEL,0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_LOCKHARDCWSEL err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_LockBootDecEn
*  Description:    Enable bootloader decryption
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_LockBootDecEn(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_LOCKBOOTDECEN, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_LOCKBOOTDECEN err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetBootDecEnStat
*  Description:    Get the decrypt flag of bootloader.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetBootDecEnStat(HI_U32 *pu32Stat)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pu32Stat)
    {
        HI_ERR_CA("pu32Stat == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_BLOAD_DEC_EN, pu32Stat);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_BLOAD_DEC_EN err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_LockR2RHardKey
*  Description:    Set to use the hardware key as R2R key.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_LockR2RHardKey(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_LOCKR2RHARDKEY,0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_LOCKR2RHARDKEY err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetHardCwSelStat
*  Description:    Check whether we use a static hardware CW word or not.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetHardCwSelStat(HI_BOOL *pbLock)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("pbLock == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_STATHARDCWSEL,pbLock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_STATHARDCWSEL err. \n");
        return ret;
    }

    return HI_SUCCESS;
}


/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetR2RHardKeyStat
*  Description:    To check the R2R Key is Hardware Key or not.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetR2RHardKeyStat(HI_BOOL *pbLock)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("pbLock == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_STATR2RHARDKEY,pbLock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_STATR2RHARDKEY err. \n");
        return ret;
    }

    return HI_SUCCESS;

}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_DisableLinkProtection
*  Description:    Disable link protection
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_DisableLinkProtection(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DISABLELPT,0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DISABLELP err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_DisableSelfBoot
*  Description:    Disable self boot.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_DisableSelfBoot(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DISABLESELFBOOT,0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DISABLESELFBOOT err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetSelfBootStat
*  Description:    Get the status of self boot, if it is close or not.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetSelfBootStat(HI_BOOL *pbDisable)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pbDisable)
    {
        HI_ERR_CA("pbDisable == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_SELFBOOT, pbDisable);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_SELFBOOT err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetSecBootStat
*  Description:    Get the status of secure boot, if it is enabled or not.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType)
{
    HI_S32 ret;
    HI_U32 val;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pbEnable)
    {
        HI_ERR_CA("pbEnable == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if (HI_NULL == penFlashType)
    {
        HI_ERR_CA("penFlashType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    /**Get the status of secure boot, if it is enabled or not. CNcomment:获取安全启动使能状态 CNend */
    ret = ioctl(g_s32CaFd, CMD_CA_GET_SCSACTIVE, &val);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_SCSACTIVE err. \n");
        return ret;
    }

    if (val)
    {
        *pbEnable = HI_TRUE;
    }
    else
    {
        *pbEnable = HI_FALSE;
    }

    /**Get boot flash selection control flag. CNcomment:获取flash启动类型控制标志 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_GET_BOOTSEL_CTRL, &val);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_BOOTSEL_CTRL err. \n");
        return ret;
    }

    if(0 == val)
    {
        *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
        HI_INFO_CA("Boot mode is controlled by chipset pin. \n");
        return HI_SUCCESS;
    }

    /**Get the startup flash type. CNcomment:获取安全启动的Flash类型 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_GET_BOOTMODE, penFlashType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_BOOTMODE err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_EnableSecBoot
*  Description:    Enable secure boot and set the startup flash type.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType)
{
    HI_S32 ret;
    HI_U32 u32BootselCtrl = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enFlashType >= HI_UNF_ADVCA_FLASH_TYPE_BUTT)
    {
        HI_ERR_CA("enFlashType >= HI_UNF_ADVCA_FLASH_TYPE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if(enFlashType == HI_UNF_ADVCA_FLASH_TYPE_NOR)
    {
        HI_ERR_CA("enFlashType set to HI_UNF_ADVCA_FLASH_TYPE_NOR, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    /**Enable secure boot. CNcomment:使能安全启动 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_SET_SCSACTIVE,0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_SCSACTIVE err. \n");
        return ret;
    }

    /**Set the startup flash type.  CNcomment:设置安全启动的Flash类型 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_SET_BOOTMODE, &enFlashType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_BOOTMODE err. \n");
        return ret;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_BOOTSEL_CTRL, &u32BootselCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_BOOTSEL_CTRL err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_EnableSecBootEx(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

     /**Enable secure boot. CNcomment:使能安全启动 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_SET_SCSACTIVE, 0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_SCSACTIVE err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetFlashTypeEx(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType)
{
    HI_S32 ret;
    HI_U32 u32BootselCtrl = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enFlashType >= HI_UNF_ADVCA_FLASH_TYPE_BUTT)
    {
        HI_ERR_CA("enFlashType >=HI_UNF_ADVCA_FLASH_TYPE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if(enFlashType == HI_UNF_ADVCA_FLASH_TYPE_NOR)
    {
        HI_ERR_CA("enFlashType set to HI_UNF_ADVCA_FLASH_TYPE_NOR, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

     /**Set the startup flash type.  CNcomment:设置安全启动的Flash类型 CNend*/
    ret = ioctl(g_s32CaFd, CMD_CA_SET_BOOTMODE, &enFlashType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_BOOTMODE err. \n");
        return ret;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_BOOTSEL_CTRL, &u32BootselCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_BOOTSEL_CTRL err.\n");
        return ret;
    }

    return HI_SUCCESS;
}


/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetJtagMode
*  Description:    get jtag mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (penJtagMode == NULL)
    {
        HI_ERR_CA("penJtagMode == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_JTAGPRTMODE, penJtagMode);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_JTAGPRTMODE err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetJtagMode
*  Description:    set jtag mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E enJtagMode)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enJtagMode >= HI_UNF_ADVCA_JTAG_MODE_BUTT)
    {
        HI_ERR_CA("enJtagMode >=HI_UNF_ADVCA_JTAG_MODE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_JTAGPRTMODE, &enJtagMode);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_JTAGPRTMODE err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetR2RKeyLadderStage
*  Description:    get r2r ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (penStage == NULL)
    {
        HI_ERR_CA("penStage == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_R2R_GETLADDER, penStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_GETLADDER err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetR2RKeyLadderStage
*  Description:    set r2r ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((enStage >= HI_UNF_ADVCA_KEYLADDER_BUTT) || (enStage < HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("enStage = %d, invalid.\n", enStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_R2R_SETLADDER, &enStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_SETLADDER err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetDVBKeyLadderStage
*  Description:    get dvb ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (penStage == NULL)
    {
        HI_ERR_CA("penStage == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_GETLADDER, penStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CW_GETLADDER err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetDVBKeyLadderStage
*  Description:    set dvb ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((enStage < HI_UNF_ADVCA_KEYLADDER_LEV2) || (enStage >= HI_UNF_ADVCA_KEYLADDER_BUTT))
    {
        HI_ERR_CA("enStage = %d, invalid.\n", enStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_SETLADDER, &enStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DVB_SETLADDER err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetR2RAlg
*  Description:    set r2r alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_ALG_TYPE_BUTT)
    {
        HI_ERR_CA("enType >=  HI_UNF_ADVCA_ALG_TYPE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_R2R_SETALG, &enType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_SETALG err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetDVBAlg
*  Description:    set cw alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_ALG_TYPE_BUTT)
    {
        HI_ERR_CA("enType >=  HI_UNF_ADVCA_ALG_TYPE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_SETALG, &enType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CW_SETALG err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetR2RAlg
*  Description:    set cw alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pEnType == NULL)
    {
        HI_ERR_CA("pEnType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_R2R_GETALG, pEnType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_GETALG err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetDVBAlg
*  Description:    set cw alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pEnType == NULL)
    {
        HI_ERR_CA("pEnType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_GETALG, pEnType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DVB_GETALG err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetR2RSessionKey
*  Description:    set r2r session key
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
/*lint -save -e818 ignored by sdk, because these function prototypes could not be changed*/
HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret;
    CA_CRYPTPM_S cryptPm;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enTotalStage;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pu8Key == NULL)
    {
        HI_ERR_CA("pu8Key == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_R2R_GETLADDER, &enTotalStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_GETLADDER err. \n");
        return ret;
    }

    if (enStage > enTotalStage)
    {
        HI_ERR_CA("enStage(%d) > g_dvbLadder(%d), invalid.\n", enStage, enTotalStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    cryptPm.ladder = enStage;
    memcpy(cryptPm.pDin, pu8Key, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_R2R_CRYPT, &cryptPm);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_R2R_CRYPT err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetDVBSessionKey
*  Description:    set dvb session key
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret;
    CA_CRYPTPM_S cryptPm;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pu8Key == NULL)
    {
        HI_ERR_CA("pu8Key == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (enStage >= g_dvbLadder)
    {
        HI_ERR_CA("enStage(%d) >= g_dvbLadder(%d), invalid.\n", enStage, g_dvbLadder);
        return HI_ERR_CA_INVALID_PARA;
    }

    cryptPm.ladder = enStage;
    memcpy(cryptPm.pDin, pu8Key, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_DVB_CRYPT, &cryptPm);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CW_CRYPT err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetGDRMSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                                    HI_HANDLE hCipherHandle,
                                    HI_U8 *pu8Input,
                                    HI_U32 u32InputLen,
                                    HI_U32 *pu32GdrmFlag)
{
    HI_S32 ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stTrans;
    CA_GDRM_CRYPTPM_S stGDRMCryptParam;

    if (g_AdvcaInitCounter <= 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((NULL == pu8Input) || (0 == u32InputLen) || (u32InputLen > 32))
    {
        HI_ERR_CA("Invalid params.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if ((HI_UNF_ADVCA_KEYLADDER_LEV3 == enLevel) && (NULL == pu32GdrmFlag))
    {
        HI_ERR_CA("Invalid level and enLevel, pu8GdrmFlag pointer.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stTrans, 0 , sizeof(stTrans));
    memset(&stGDRMCryptParam, 0, sizeof(stGDRMCryptParam));

    stGDRMCryptParam.stCACryptParams.ladder = enLevel;
    stGDRMCryptParam.stCACryptParams.enKlTarget = HI_UNF_ADVCA_CA_TARGET_MULTICIPHER;
    if (HI_UNF_ADVCA_KEYLADDER_LEV3 == enLevel)
    {
        stGDRMCryptParam.u32KeyAddr = hCipherHandle & 0xFF;
    }
    stGDRMCryptParam.bIsDecrypt = HI_TRUE;
    memcpy(stGDRMCryptParam.stCACryptParams.pDin, pu8Input, u32InputLen);

    stTrans.enCmdChildID = CMD_CHILD_ID_CA_GDRM_CRYPT;
    memcpy(stTrans.pu8ParamBuf, &stGDRMCryptParam, sizeof(CA_GDRM_CRYPTPM_S));
    stTrans.u32ParamLen = sizeof(CA_GDRM_CRYPTPM_S);
    ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stTrans);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CHILD_ID_CA_GDRM_CRYPT err\n");
        return ret;
    }

    if (HI_UNF_ADVCA_KEYLADDER_LEV3 == enLevel)
    {
        memcpy(&stGDRMCryptParam, stTrans.pu8ParamBuf, sizeof(stGDRMCryptParam));
        *pu32GdrmFlag = stGDRMCryptParam.u32GDRMFlag;
    }

    return HI_SUCCESS;
}


/***********************************************************************************
*  Function:       HI_UNF_ADVCA_EncryptSWPK
*  Description:    Encrypt the key of software protetion.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_EncryptSWPK(HI_U8 *pPlainSwpk,HI_U8 *pEncryptedSwpk)
{
    HI_S32 ret;
    CA_ENCRYPTSWPK_S stEncryptSWPK;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pPlainSwpk)
    {
        HI_ERR_CA("HI_NULL == pClearSwpk, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (HI_NULL == pEncryptedSwpk)
    {
        HI_ERR_CA("HI_NULL == pEncryptSwpk, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memcpy(stEncryptSWPK.ClearSwpk, pPlainSwpk, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_SWPK_CRYPT, &stEncryptSWPK);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SWPK_CRYPT err. \n");
        return ret;
    }

    memcpy(pEncryptedSwpk,stEncryptSWPK.EncryptSwpk,16);

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetChipId
*  Description:    Set the chip id if it's not set.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         Be careful with the following functions!
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetChipId(HI_U32 Id)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_CHIPID, &Id);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_CHIPID err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetDVBRootKey(HI_U8 *pkey)
{
    HI_S32 ret;
    CA_KEY_S stCaKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memcpy(stCaKey.KeyBuf, pkey, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_SET_DVB_ROOT_KEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_DVB_ROOT_KEY err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetR2RRootKey(HI_U8 *pkey)
{
    HI_S32 ret;
    CA_KEY_S stCaKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memcpy(stCaKey.KeyBuf, pkey, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_SET_R2R_ROOT_KEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_R2R_ROOT_KEY err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetJtagKey(HI_U8 *pkey)
{
    HI_S32 ret;
    CA_KEY_S stCaKey;
    HI_U32 u32ChipID = 0;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_CHIPID, &u32ChipID);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_CHIPID err, ret = 0x%x. \n", ret);
        return ret;
    }

    if(0 == u32ChipID)
    {
        HI_ERR_CA("Error! Please set chipid before setting jtag key! \n");
        return HI_FAILURE;
    }

    memcpy(stCaKey.KeyBuf, pkey, 8);
    ret = ioctl(g_s32CaFd, CMD_CA_SET_JTAG_KEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_JTAG_KEY err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetJtagKey(HI_U8 *pkey)
{
    HI_S32 ret;
    CA_KEY_S stCaKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_JTAG_KEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_JTAG_KEY err. \n");
        return ret;
    }

    memcpy(pkey, stCaKey.KeyBuf, 8);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetSPRootKey(HI_U8 *pu8Key, HI_U32 u32Len)
{
    HI_S32 ret = HI_SUCCESS;
    CA_KEY_S stCaKey;
    if((NULL == pu8Key) || (16 != u32Len))
    {
        HI_ERR_CA("Invalid parameters!\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }
    memcpy(stCaKey.KeyBuf, pu8Key, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_SET_SP_ROOT_KEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_SP_ROOT_KEY err. \n");
        return ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetRSAKey(HI_U8 *pkey)
{
    HI_S32 ret = HI_SUCCESS;
    CA_KEY_S stCaKey, stRdKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memcpy(stCaKey.KeyBuf, pkey, 512);
    ret = ioctl(g_s32CaFd, CMD_CA_EXT1_SETRSAKEY, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_EXT1_SETRSAKEY err. \n");
        return ret;
    }

    memset(stRdKey.KeyBuf, 0, 512);
    ret = ioctl(g_s32CaFd, CMD_CA_EXT1_GETRSAKEY, &stRdKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_EXT1_GETRSAKEY err. \n");
        return ret;
    }

    if (memcmp(stCaKey.KeyBuf, stRdKey.KeyBuf, 512))
    {
        HI_ERR_CA("RSA Key Set err. \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetRSAKey(HI_U8 *pkey)
{
    HI_S32 ret = HI_SUCCESS;
    CA_KEY_S stRdKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pkey == NULL)
    {
        HI_ERR_CA("pkey == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(stRdKey.KeyBuf, 0, 512);
    ret = ioctl(g_s32CaFd, CMD_CA_EXT1_GETRSAKEY, &stRdKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_EXT1_GETRSAKEY err. \n");
        return ret;
    }

    memcpy(pkey, stRdKey.KeyBuf, 512);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_OtpReadByte(HI_U32 Addr, HI_U8 *pu8Value)
{
    HI_S32 ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if((Addr >= 0x800) || (NULL == pu8Value))
    {
        HI_ERR_CA("Invalid parameters!\n");
        return HI_FAILURE;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));

    stCmdParam.enCmdChildID = CMD_CHILD_ID_OTP_READ_BYTE;
    memcpy(stCmdParam.pu8ParamBuf, &Addr, sizeof(HI_U32));
    stCmdParam.u32ParamLen = 5;

    ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err. \n");
        return ret;
    }

    *pu8Value = stCmdParam.pu8ParamBuf[4];

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_OtpWriteByte(HI_U32 Addr,HI_U8 Value)
{
    HI_S32 ret;
    OTP_ENTRY_S stOtpEntry;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    stOtpEntry.addr  = Addr;
    stOtpEntry.value = Value;
    ret = ioctl(g_s32CaFd, CMD_CA_EXT1_OTPWRITEBYTE, &stOtpEntry);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_EXT1_OPTWRITE err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_OtpRead(HI_U32 Addr, HI_U32 *pValue)
{
    HI_S32 ret = HI_SUCCESS;
    OTP_ENTRY_S stOtpEntry;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pValue)
    {
        HI_ERR_CA("invalid param pValue\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (0 != (Addr % 4))
    {
        HI_ERR_CA("Addr is not aliged by 4\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    stOtpEntry.addr = Addr;
    ret = ioctl(g_s32CaFd, CMD_CA_EXT1_OTPREAD, &stOtpEntry);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_EXT1_OTPREAD err. \n");
        return ret;
    }

    *pValue = stOtpEntry.value;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_NovelCryptologyConfig(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32VendorType = 0;
    HI_U8  SessionKey1[16];
    HI_U8  SessionKey2[16];
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage = HI_UNF_ADVCA_KEYLADDER_BUTT;
    HI_U8 u8CipherInput[16] = {0x10, 0x6b, 0xe2, 0x28, 0xc6, 0x7b, 0x82, 0x09, 0x6a, 0x17, 0xc7, 0x25, 0xe5, 0xd5, 0x55, 0x4e};
    HI_U8 u8KeyladderInput1[16] = {0xb4, 0x8a, 0x34, 0xee, 0x36, 0x74, 0x8b, 0xf8, 0x98, 0x11, 0x10, 0x2c, 0x27, 0x8c, 0xe6, 0xdf};
    HI_U8 u8KeyladderInput2[16] = {0xd2, 0x7b, 0xfc, 0x9b, 0x68, 0x91, 0x99, 0x62, 0x77, 0x0f, 0x27, 0x3c, 0xc8, 0x45, 0xfa, 0xfb};
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if(HI_TRUE == g_bCryptologyConfig)
    {
        HI_INFO_CA("HI_UNF_ADVCA_NovelCryptologyConfig has already be called\n");
        return 0;
    }

    ret = HI_UNF_ADVCA_GetVendorID(&u32VendorType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("get vendor type err. \n");
        return HI_FAILURE;
    }
    g_vendorType = (HI_UNF_ADVCA_VENDORID_E)u32VendorType;

    if (HI_UNF_ADVCA_NOVEL != g_vendorType)
    {
        HI_ERR_CA("CA vendor NOT match! Permission denied:%d != %d!\n", HI_UNF_ADVCA_NOVEL, g_vendorType);
        return HI_ERR_CA_NOT_SUPPORT;
    }

    memset(SessionKey1,0,sizeof(SessionKey1));
    memset(SessionKey2,0,sizeof(SessionKey2));
    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    /*open and config keyladder*/
    ret = HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_AES);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("HI_UNF_ADVCA_SetR2RAlg failed:%#x\n", ret);
        return ret;
    }

    ret = HI_UNF_ADVCA_GetR2RKeyLadderStage(&enStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("HI_UNF_ADVCA_SetR2RSessionKey failed:%#x\n", ret);
        return ret;
    }
    memcpy(SessionKey1, u8KeyladderInput1, sizeof(SessionKey1));
    ret |= HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1,SessionKey1);
    if(enStage == HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        memcpy(SessionKey2, u8KeyladderInput2, sizeof(SessionKey2));
        ret |= HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2,SessionKey2);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("HI_UNF_ADVCA_SetR2RSessionKey failed:%#x\n", ret);
            return ret;
        }
    }
    /*open and config Cipher*/
    CipherCtrl.bKeyByCA = HI_TRUE;
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
    memset(CipherCtrl.u32IV, 0, sizeof(CipherCtrl.u32IV));
    memcpy(CipherCtrl.u32Key, u8CipherInput, 16);
    ret = HI_UNF_CIPHER_Open();
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("HI_UNF_CIPHER_Open failed:%#x\n", ret);
        return ret;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;

    ret = HI_UNF_CIPHER_CreateHandle(&g_hCipher, &stCipherAttr);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("HI_UNF_CIPHER_CreateHandle failed:%#x\n", ret);
        return ret;
    }

    ret = HI_UNF_CIPHER_ConfigHandle(g_hCipher, &CipherCtrl);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("HI_UNF_CIPHER_ConfigHandle failed:%#x\n", ret);
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(g_hCipher);
        return ret;
    }
    g_bCryptologyConfig = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_NovelDataEncrypt(HI_U8 *pPlainText, HI_U32 TextLen, HI_U8 *pCipherText)
{
    HI_S32 ret = HI_FAILURE;

    if (HI_FALSE == g_bCryptologyConfig)
    {
        HI_ERR_CA("call HI_UNF_ADVCA_NovelCryptologyConfig first\n");
        return ret;
    }
    if ((HI_NULL == pPlainText) || (HI_NULL == pCipherText))
    {
        HI_ERR_CA("null pointer error\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if ((TextLen < 16) || (TextLen%16 != 0))
    {
        HI_ERR_CA("Data length must be times of 16BYTE\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (HI_UNF_ADVCA_NOVEL != g_vendorType)
    {
        HI_ERR_CA("CA vendor NOT match! Permission denied!\n");
        return HI_ERR_CA_NOT_SUPPORT;
    }

    return HI_UNF_CIPHER_Encrypt(g_hCipher, (HI_U32)(HI_ULONG)pPlainText, (HI_U32)(HI_ULONG)pCipherText, TextLen);
}


HI_S32 HI_UNF_ADVCA_NovelDataDecrypt(HI_U8 *pCipherText, HI_U32 TextLen, HI_U8 *pPlainText)
{
    HI_S32 ret = HI_FAILURE;

    if(HI_FALSE == g_bCryptologyConfig)
    {
        HI_ERR_CA("call HI_UNF_ADVCA_NovelCryptologyConfig first\n");
        return ret;
    }
    if ((HI_NULL == pPlainText) || (HI_NULL == pCipherText))
    {
        HI_ERR_CA("null pointer error\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    if ((TextLen < 16) || (TextLen%16 != 0))
    {
        HI_ERR_CA("Data length must be times of 16BYTE\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (HI_UNF_ADVCA_NOVEL != g_vendorType)
    {
        HI_ERR_CA("CA vendor NOT match! Permission denied!\n");
        return HI_ERR_CA_NOT_SUPPORT;
    }

    return HI_UNF_CIPHER_Decrypt(g_hCipher, (HI_U32)(HI_ULONG)pCipherText, (HI_U32)(HI_ULONG)pPlainText, TextLen);
}

HI_S32 HI_UNF_ADVCA_IsMarketIdSet(HI_BOOL *pbIsMarketIdSet)
{
    HI_S32 ret = HI_SUCCESS;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (NULL == pbIsMarketIdSet)
    {
        HI_ERR_CA("NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_CHECK_MARKET_ID_SET, pbIsMarketIdSet);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CHECK_MARKET_ID_SET err.\n");
        return ret;
    }

    return HI_SUCCESS;
}



HI_S32 HI_UNF_ADVCA_GetVendorID(HI_U32 *pu32VendorID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pu32VendorID == NULL)
    {
        HI_ERR_CA("pu32VendorID == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_VENDOR_ID, pu32VendorID);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_VENDOR_ID err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetSPKeyLadderStage
*  Description:    get SP ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (penStage == NULL)
    {
        HI_ERR_CA("penStage == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_GETLADDER, penStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_GETLADDER err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetSPKeyLadderStage
*  Description:    set SP ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((enStage >= HI_UNF_ADVCA_KEYLADDER_BUTT) || (enStage < HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("enStage = %d, invalid.\n", enStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_SETLADDER, &enStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_SETLADDER err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetSPAlg
*  Description:    set SP alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_ALG_TYPE_BUTT)
    {
        HI_ERR_CA("enType(0x%x) >=  HI_UNF_ADVCA_ALG_TYPE_BUTT(0x%x), invalid.\n", enType, HI_UNF_ADVCA_ALG_TYPE_BUTT);
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_SETALG, &enType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_SETALG err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetSPAlg
*  Description:    get SP alg
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pEnType == NULL)
    {
        HI_ERR_CA("pEnType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_GETALG, pEnType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_GETALG err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetSPDscMode
*  Description:    set SP dsc mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E enType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_SP_DSC_MODE_BUTT)
    {
        HI_ERR_CA("enType(0x%x) >=  HI_UNF_ADVCA_SP_DSC_MODE_BUTT(0x%x), invalid.\n", enType, HI_UNF_ADVCA_SP_DSC_MODE_BUTT);
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_SET_DSC_MODE, &enType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_SET_DSC_MODE err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetSPDscMode
*  Description:    get SP dsc mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *pEnType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pEnType == NULL)
    {
        HI_ERR_CA("pEnType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_GET_DSC_MODE, pEnType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_GET_DSC_MODE err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetSPSessionKey
*  Description:    set SP session key
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetSPSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret;
    CA_CRYPTPM_S cryptPm;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enTotalStage;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pu8Key == NULL)
    {
        HI_ERR_CA("pu8Key == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SP_GETLADDER, &enTotalStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_GETLADDER err.\n");
        return ret;
    }

    if (enStage > enTotalStage)
    {
        HI_ERR_CA("enStage(%d) > enTotalStage(%d), invalid.\n", enStage, enTotalStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    cryptPm.ladder = enStage;
    memcpy(cryptPm.pDin, pu8Key, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_SP_CRYPT, &cryptPm);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_CRYPT err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetCSA3Alg
*  Description:    get the algorithm of CSA3 key ladder
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetCSA3Alg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pEnType == NULL)
    {
        HI_ERR_CA("pEnType == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_CSA3_GETALG, pEnType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DVB_CSA3_GETALG err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetCSA3Alg
*  Description:    set the algorithm of CSA3 key ladder
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetCSA3Alg(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_ALG_TYPE_BUTT)
    {
        HI_ERR_CA("enType >=  HI_UNF_ADVCA_ALG_TYPE_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DVB_CSA3_SETALG, &enType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DVB_CSA3_SETALG err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetCSA3KeyLadderStage
*  Description:    get CSA3 ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetCSA3KeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (penStage == NULL)
    {
        HI_ERR_CA("penStage == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_CSA3_GETLADDER, penStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CSA3_GETLADDER err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetCSA3KeyLadderStage
*  Description:    set CSA3 ladder stage
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetCSA3KeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (HI_UNF_ADVCA_KEYLADDER_LEV2 != enStage) && (HI_UNF_ADVCA_KEYLADDER_LEV3 != enStage))
    {
        HI_ERR_CA("Invalid keyladder level select! Only supported 2 or 3 level\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_CSA3_SETLADDER, &enStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CSA3_SETLADDER err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetCSA3SessionKey
*  Description:    set CSA3 session key
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetCSA3SessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret;
    CA_CRYPTPM_S cryptPm;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enTotalStage;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (pu8Key == NULL)
    {
        HI_ERR_CA("pu8Key == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_CSA3_GETLADDER, &enTotalStage);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SP_GETLADDER err.\n");
        return ret;
    }

    if (enStage > enTotalStage)
    {
        HI_ERR_CA("enStage(%d) > enTotalStage(%d), invalid.\n", enStage, enTotalStage);
        return HI_ERR_CA_INVALID_PARA;
    }

    cryptPm.ladder = enStage;
    memcpy(cryptPm.pDin, pu8Key, 16);
    ret = ioctl(g_s32CaFd, CMD_CA_CSA3_CRYPT, &cryptPm);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_CSA3_CRYPT err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_DisableDDRWakeup(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_LOWPOWER_DISABLE, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_LOWPOWER_DISABLE err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_SetDDRScramble(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Set = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_DDR_SCRAMBLE_EN, &u32Set);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_DDR_SCRAMBLE_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_GetDDRScrambleStat(HI_U32 *pu32Stat)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pu32Stat)
    {
        HI_ERR_CA("pu32Stat == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_DDR_SCRAMBLE_EN, pu32Stat);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_DDR_SCRAMBLE_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_LockCSA3HardCW(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_CSA3_HARDONLY_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_CSA3_HARDONLY_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_GetCSA3HardCWStat(HI_BOOL *pbLock)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pbLock)
    {
        HI_ERR_CA("pbLock == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_CSA3_HARDONLY_EN, pbLock);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_CSA3_HARDONLY_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_LockSPHardCW(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_SP_HARDONLY_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_SP_HARDONLY_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_DisableTsklDES(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_TSKL_DES_DISABLE, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_TSKL_DES_DISABLE err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_LockGlobalOTP(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_OTP_GLOBAL_LOCK_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_OTP_GLOBAL_LOCK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_DisableDCasKl(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_DCAS_KL_DISABLE, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_DCAS_KL_DISABLE err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_EnableRuntimeCheck(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_RUNTIME_CHECK_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_RUNTIME_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_EnableDDRWakeupCheck(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_WAKEUP_DDR_CHECK_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_WAKEUP_DDR_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_EnableVersionCheck(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_VERSION_CHECK_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_VERSION_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_GetVersionCheckStat(HI_U32 *pu32Stat)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pu32Stat)
    {
        HI_ERR_CA("pu32Stat == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_VERSION_CHECK_EN, pu32Stat);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_VERSION_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_EnableBootMSIDCheck(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_BL_MSID_CHECK_EN, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_BL_MSID_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_GetBootMSIDCheckStat(HI_U32 *pu32Stat)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == pu32Stat)
    {
        HI_ERR_CA("pu32Stat == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_BL_MSID_CHECK_EN, pu32Stat);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_BL_MSID_CHECK_EN err.\n");
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 HI_UNF_ADVCA_DisableJtagRead(HI_VOID)
{
    HI_S32 ret;
    HI_U32 u32Value = 1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_JTAG_READ_DISABLE, &u32Value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_JTAG_READ_DISABLE err.\n");
        return ret;
    }

    return HI_SUCCESS;
}


/***********************************************************************************
*  Function:       HI_UNF_ADVCA_DCASOpen
*  Description:    Open DCAS Mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_DCASOpen(HI_UNF_CIPHER_ALG_E enAlg)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((enAlg != HI_UNF_CIPHER_ALG_3DES) && (enAlg != HI_UNF_CIPHER_ALG_AES))
    {
        HI_ERR_CA("enAlg must be HI_UNF_CIPHER_ALG_3DES or HI_UNF_CIPHER_ALG_AES\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DCAS_OPEN, &enAlg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DCAS_OPEN err. \n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetDCASChipId
*  Description:    Get DCAS CHIPID
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetDCASChipId(HI_U32 *pu32MSBID, HI_U32 *pu32LSBID)
{
    HI_S32 Ret = 0;
    HI_U32 u32DCASID_MSBAddr, u32DCASID_LSBAddr;
    HI_U32 u32StbSN0, u32StbSN1;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if((pu32MSBID == NULL) || (pu32LSBID == NULL))
    {
        HI_ERR_CA("Invalid parameter!\r\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    u32DCASID_MSBAddr = 0xF8AB00E8;
    u32DCASID_LSBAddr = 0xF8AB00EC;

    Ret = HI_SYS_ReadRegister(u32DCASID_MSBAddr, &u32StbSN0);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Get Dcas chipid MSB failed\n");
        *pu32MSBID = 0X00;
        *pu32LSBID = 0X00;
        return HI_FAILURE;
    }

    Ret = HI_SYS_ReadRegister(u32DCASID_LSBAddr, &u32StbSN1);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Get Dcas chipid LSB failed\n");
        *pu32MSBID = 0X00;
        *pu32LSBID = 0X00;
        return HI_FAILURE;
    }

    *pu32MSBID = u32StbSN0;
    *pu32LSBID = u32StbSN1;

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_DCASClose
*  Description:    Close DCAS Mode
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_DCASClose(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_DCAS_CLOSE, 0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DCAS_CLOSE err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetDCASSessionKey
*  Description:    set DCAS Session Key
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:         ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_LEV_E enDCASLevel, HI_U8 au8Key[16], HI_U8 au8Output[16])
{
    HI_S32 ret;
    CA_DCAS_PARAM_S DCASParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if ((au8Key == NULL)||(au8Output == NULL))
    {
        HI_ERR_CA("au8Key == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (enDCASLevel >= HI_UNF_ADVCA_DCAS_KEYLADDER_BUTT)
    {
        HI_ERR_CA("enDCASLevel >= HI_UNF_ADVCA_DCAS_KEYLADDER_BUTT, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&DCASParam, 0, sizeof(CA_DCAS_PARAM_S));
    DCASParam.level = enDCASLevel;
    memcpy(DCASParam.pDin, au8Key, 16);

    ret = ioctl(g_s32CaFd, CMD_CA_DCAS_PARAM_ID_SET, &DCASParam);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_DCAS_CRYPT err.\n");
        return ret;
    }

    memcpy(au8Output, DCASParam.pDout, 16);

    return HI_SUCCESS;
}
/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SWPKKeyLadderOpen
*  Description:    Open SWPK keyladder
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderOpen(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SWPK_KEY_LADDER_OPEN, 0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SWPK_KEY_LADDER_OPEN err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SWPKKeyLadderClose
*  Description:   Close SWPK keyladder
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderClose(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SWPK_KEY_LADDER_CLOSE, 0);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SWPK_KEY_LADDER_CLOSE err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_OtpReset
*  Description:   Reset OTP
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_OtpReset(HI_VOID)
{
    HI_S32 ret;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_OTP_RESET, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_OTP_RESET err.\n");
        return ret;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_GetRevision
*  Description:   Get the software revision
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_GetRevision(HI_U8 u8Revision[25])
{
    HI_S32 ret;
    CA_KEY_S stCaKey;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (HI_NULL == u8Revision)
    {
        HI_ERR_CA("u8Revision == NULL, invalid.\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = ioctl(g_s32CaFd, CMD_CA_GET_REVISION, &stCaKey);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_REVISION err.\n");
        return ret;
    }

    memcpy(u8Revision, stCaKey.KeyBuf, 25);

    return HI_SUCCESS;
}



HI_S32 HI_UNF_ADVCA_CalculteAES_CMAC(HI_U8 *buffer, HI_U32 Length, HI_U8 Key[16], HI_U8 MAC[16])
{
    HI_S32 ret = 0;
    HI_HANDLE hCipher = 0xffffffff;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U8 au8SessionInput1[16] = {0x23,0x34,0x34,0x52,0x34,0x55,0x45,0x84,0x54,0x54,0x84,0x53,0x34,0x47,0x34,0x47};
    HI_U8 au8SessionInput2[16] = {0x56,0x34,0x88,0x52,0x34,0x89,0x45,0xa0,0x54,0x54,0x77,0x53,0x34,0x47,0x34,0x91};
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;

    CA_CheckPointer(buffer);
    CA_CheckPointer(Key);
    CA_CheckPointer(MAC);

    /*open and config cipher*/
    CA_ASSERT(HI_UNF_ADVCA_Init(),ret);
    CA_ASSERT(HI_UNF_CIPHER_Init(),ret);
    CA_ASSERT(HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_AES), ret);
    CA_ASSERT(HI_UNF_ADVCA_GetR2RKeyLadderStage(&enStage), ret);

    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    CA_ASSERT(HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr),ret);


    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        ret = HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1, au8SessionInput1);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CA("Fail to set R2R session key, level %d\n", HI_UNF_ADVCA_KEYLADDER_LEV1);
            goto ERROR_EXIT;
        }
    }

    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        ret = HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2, au8SessionInput2);
        if (ret != HI_SUCCESS)
        {
           HI_ERR_CA("Fail to set R2R session key, level %d\n", HI_UNF_ADVCA_KEYLADDER_LEV2);
           goto ERROR_EXIT;
        }
    }

    memset(&CipherCtrl,0x00,sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.bKeyByCA = HI_TRUE;
    CipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_R2R;
    CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    CipherCtrl.stChangeFlags.bit1IV = 1;
    memcpy(CipherCtrl.u32Key, Key, 16);
    memset(CipherCtrl.u32IV, 0x0, 16);

    ret = HI_UNF_CIPHER_ConfigHandle(hCipher,&CipherCtrl);
    if (ret != HI_SUCCESS)
    {
       HI_ERR_CA("Fail to config cipher\n");
       goto ERROR_EXIT;
    }

    ret = HI_UNF_CIPHER_CalcMAC(hCipher, buffer, Length, MAC, HI_TRUE);
    if (ret != HI_SUCCESS)
    {
       HI_ERR_CA("HI_UNF_CIPHER_CalcMAC failed, ret: 0x%x\n", ret);
       goto ERROR_EXIT;
    }

    ret = HI_SUCCESS;

ERROR_EXIT:

    if (HI_SUCCESS != HI_UNF_CIPHER_DestroyHandle(hCipher))
    {
       HI_ERR_CA("Fail to destory cipher handle\n");
       return HI_FAILURE;
    }

    if (HI_SUCCESS != HI_UNF_ADVCA_DeInit())
    {
       HI_ERR_CA("Fail to DeInit ADVCA\n");
       return HI_FAILURE;
    }

    return ret;
}

HI_S32 HI_UNF_ADVCA_SetKlDPAClkSelEn(HI_BOOL bValue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bTmp = bValue;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_KL_DPA_CLK_SEL_EN;
    memcpy(stCmdParam.pu8ParamBuf, &bTmp, sizeof(HI_BOOL));
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetMiscRootKey(HI_U8 *pu8Key, HI_U32 u32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (NULL == pu8Key) || (16 != u32Len) )
    {
        HI_ERR_CA("Invalid param!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_MISC_ROOT_KEY;
    memcpy(stCmdParam.pu8ParamBuf, pu8Key, u32Len);
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetESCK(HI_U8 *pu8Key, HI_U32 u32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (NULL == pu8Key) || (16 != u32Len) )
    {
        HI_ERR_CA("Invalid param!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_ESCK;
    memcpy(stCmdParam.pu8ParamBuf, pu8Key, u32Len);
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (HI_UNF_ADVCA_KEYLADDER_LEV2 != enLevel) && (HI_UNF_ADVCA_KEYLADDER_LEV3 != enLevel))
    {
        HI_ERR_CA("Invalid keyladder level select! Only supported 2 or 3 level\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_MISC_LV_SEL;
    memcpy(stCmdParam.pu8ParamBuf, &enLevel, sizeof(HI_UNF_ADVCA_KEYLADDER_LEV_E));
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}


HI_S32 HI_UNF_ADVCA_GetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( NULL == penLevel)
    {
        HI_ERR_CA("Invalid param, NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_GET_MISC_LV_SEL;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    memcpy(penLevel, stCmdParam.pu8ParamBuf, sizeof(HI_BOOL));

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetMiscAlg(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enType >= HI_UNF_ADVCA_ALG_TYPE_BUTT)
    {
        HI_ERR_CA("Invalid alg type: %d\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_MISC_SETALG;
    memcpy(stCmdParam.pu8ParamBuf, &enType, sizeof(HI_UNF_ADVCA_ALG_TYPE_E));
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetMiscAlg(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_ADVCA_ALG_TYPE_E enType = HI_UNF_ADVCA_ALG_TYPE_BUTT;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if(NULL == penType)
    {
        HI_ERR_CA("Invalid param input ,NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_MISC_GETALG;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    memcpy(&enType, stCmdParam.pu8ParamBuf, sizeof(HI_UNF_ADVCA_ALG_TYPE_E));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    *penType = enType;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetOEMRootKey(HI_U8 *pu8OEMRootKey, HI_U32 u32KeyLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (NULL == pu8OEMRootKey) || (16 != u32KeyLen))
    {
        HI_ERR_CA("Error! Invalid parameter input!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_OEM_ROOT_KEY;
    memcpy(stCmdParam.pu8ParamBuf, pu8OEMRootKey, u32KeyLen);
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetOEMRootKey(HI_U8 *pu8OEMRootKey, HI_U32 u32KeyLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( (NULL == pu8OEMRootKey) || (16 != u32KeyLen))
    {
        HI_ERR_CA("Error! Invalid parameter input!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_GET_OEM_ROOT_KEY;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err.\n");
        return s32Ret;
    }

    memcpy(pu8OEMRootKey, stCmdParam.pu8ParamBuf, u32KeyLen);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetOEMRootKeyLockFlag(HI_BOOL *pbLockFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( NULL == pbLockFlag)
    {
        HI_ERR_CA("Error! Invalid parameter input!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_GET_OEM_ROOT_KEY_LOCK;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err. \n");
        return s32Ret;
    }

    memcpy(pbLockFlag, stCmdParam.pu8ParamBuf, sizeof(HI_BOOL));

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_SetTZEnable(HI_BOOL bValue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;
    HI_BOOL bTZEnable = bValue;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_SOC_OTP_TZ_EN;
    memcpy(stCmdParam.pu8ParamBuf, &bTZEnable, sizeof(HI_BOOL));

    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err. \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetTZEnStatus(HI_BOOL *pbEn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( NULL == pbEn )
    {
        HI_ERR_CA("Invalid param ,NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_GET_SOC_OTP_TZ_EN;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err. \n");
        return s32Ret;
    }

    memcpy(pbEn, stCmdParam.pu8ParamBuf, sizeof(HI_BOOL));

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_ADVCA_SetTZOtp
*  Description:    Set the otp in Trustzone.
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         The input address should be 16byte aligned!
***********************************************************************************/
HI_S32 HI_UNF_ADVCA_SetTZOtp(HI_U32 u32Addr, HI_U8 *pu8InData, HI_U32 u32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;
    CA_OTP_TZ_DATA_S stOtpTzInput;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( NULL == pu8InData )
    {
        HI_ERR_CA("Invalid param, null pointer!");
        return HI_FAILURE;
    }
    if((u32Addr % 16) != 0)
    {
        HI_ERR_CA("u32Addr(0x%x) is not aligned by 16!", u32Addr);
        return HI_FAILURE;
    }
    if(u32Len > 128)
    {
        HI_ERR_CA("Invalid param, u32Len(%d) > 128!", u32Len);
        return HI_FAILURE;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    memset(&stOtpTzInput, 0, sizeof(stOtpTzInput));
    stOtpTzInput.u32Addr = u32Addr;
    stOtpTzInput.u32Len = u32Len;
    memcpy(stOtpTzInput.u8Buf, pu8InData, u32Len);

    memcpy(stCmdParam.pu8ParamBuf, &stOtpTzInput, sizeof(CA_OTP_TZ_DATA_S));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_SET_OTP_TZ;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err:0x%x \n", s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_GetTZOtp(HI_U32 u32Addr, HI_U32 u32Len, HI_U8 *pu8OutData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stCmdParam;
    CA_OTP_TZ_DATA_S stOtpTzTrans;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if( NULL == pu8OutData )
    {
        HI_ERR_CA("Invalid param, null pointer!");
        return HI_FAILURE;
    }

    if((u32Addr % 16) != 0)
    {
        HI_ERR_CA("u32Addr(0x%x) is not aligned by 16!", u32Addr);
        return HI_FAILURE;
    }
    if(u32Len > 128)
    {
        HI_ERR_CA("Invalid param, u32Len(%d) > 128!", u32Len);
        return HI_FAILURE;
    }

    memset(&stCmdParam, 0, sizeof(stCmdParam));
    memset(&stOtpTzTrans, 0, sizeof(stOtpTzTrans));

    stOtpTzTrans.u32Addr = u32Addr;
    stOtpTzTrans.u32Len = u32Len;

    memcpy(stCmdParam.pu8ParamBuf, &stOtpTzTrans, sizeof(CA_OTP_TZ_DATA_S));
    stCmdParam.enCmdChildID = CMD_CHILD_ID_GET_OTP_TZ;
    s32Ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stCmdParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SUPPER_ID err. \n");
        return s32Ret;
    }

    memcpy(&stOtpTzTrans, stCmdParam.pu8ParamBuf, sizeof(CA_OTP_TZ_DATA_S));
    memcpy(pu8OutData, stOtpTzTrans.u8Buf, u32Len);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_TYPE_E enType, HI_U8 *pu8ParamIn, HI_U32 u32ParamLen)
{
    HI_S32 ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stParams;
    HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S *pstParams = NULL;

    if (g_s32CaFd <= 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    memset(&stParams, 0, sizeof(stParams));
    switch ( enType )
    {
        case HI_UNF_ADVCA_LOCK_RSA_KEY:
        {
            stParams.enCmdChildID = CMD_CHILD_ID_LOCK_RSA_KEY;
            ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stParams);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CA("ca ioctl  set rsa key lock flag err. \n");
                return ret;
            }
            break;
        }
        case HI_UNF_ADVCA_LOCK_TZ_OTP:
        {
            if ( (NULL == pu8ParamIn) || (0 == u32ParamLen) || (u32ParamLen != sizeof(HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S)) )
            {
                HI_ERR_CA("Invalid params input.\n");
                return HI_ERR_CA_INVALID_PARA;
            }

            pstParams = (HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S *)pu8ParamIn;

            /* tz otp : 0x100 ~ 0x17f , total length : 128 bytes*/
            if((0 != (pstParams->u32Addr%16)) || (pstParams->u32Addr < 0x100) || (pstParams->u32Addr > 0x170))
            {
                HI_ERR_CA("Invalid params, addr.\n");
                return HI_ERR_CA_INVALID_PARA;
            }

            if ( (0!=(pstParams->u32Len%16)) || (pstParams->u32Len > 128) )
            {
                HI_ERR_CA("Invalid params, u32Len.\n");
                return HI_ERR_CA_INVALID_PARA;
            }
            if ( ((pstParams->u32Addr + pstParams->u32Len) > 0x180) )
            {
                HI_ERR_CA("Invalid params, u32Len.\n");
                return HI_ERR_CA_INVALID_PARA;
            }

            stParams.enCmdChildID = CMD_CHILD_ID_LOCK_OTP_TZ;
            memcpy(stParams.pu8ParamBuf, (HI_VOID *)pstParams, sizeof(HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S));
            stParams.u32ParamLen = u32ParamLen;

            ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stParams);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CA("ca ioctl set tz otp lock flag err. \n");
                return ret;
            }
            break;
        }
        case HI_UNF_ADVCA_LOCK_MISC_KL_DISABLE:
        {
            stParams.enCmdChildID = CMD_CHILD_ID_LOCK_MISC_KL_DISABLE;
            ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stParams);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CA("ca ioctl lock misc kl disable err. \n");
                return ret;
            }
            break;
        }
        case HI_UNF_ADVCA_LOCK_GG_KL_DISABLE:
        {
            stParams.enCmdChildID = CMD_CHILD_ID_LOCK_GG_KL_DISABLE;
            ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stParams);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CA("ca ioctl lock gg kl disable err. \n");
                return ret;
            }
            break;
        }
        case HI_UNF_ADVCA_LOCK_TSKL_CSA3_DISABLE:
        {
            stParams.enCmdChildID = CMD_CHILD_ID_LOCK_TSKL_CSA3_DISABLE;
            ret = ioctl(g_s32CaFd, CMD_CA_SUPPER_ID, &stParams);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_CA("ca ioctl lock tskl csa3 disable err. \n");
                return ret;
            }
            break;
        }
        default:
        {
            HI_ERR_CA("Not supported.\n");
            return HI_ERR_CA_NOT_SUPPORT;
        }
    }

    return ret;
}

HI_S32 HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr)
{
    HI_S32 ret = HI_SUCCESS;
    CA_OTP_ATTR_S stOtpAttr;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if(enOtpFuse >= HI_UNF_ADVCA_OTP_FUSE_BUTT || enOtpFuse <= HI_UNF_ADVCA_OTP_NULL)
    {
        HI_ERR_CA("Invalid parameter, enOtpFuse = %d\n", enOtpFuse);
        return HI_ERR_CA_INVALID_PARA;
    }

    if(pstOtpFuseAttr == NULL)
    {
        HI_ERR_CA("Invalid parameter, pstOtpFuseAttr = NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stOtpAttr, 0, sizeof(stOtpAttr));
    stOtpAttr.enOtpFuseId = enOtpFuse;
    memcpy(&stOtpAttr.stOtpAttr, pstOtpFuseAttr, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    ret = ioctl(g_s32CaFd, CMD_CA_SET_OTP_FUSE, &stOtpAttr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_OTP_FUSE err. \n");
        return ret;
    }

    return ret;
}

HI_S32 HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr)
{
    HI_S32 ret = HI_SUCCESS;
    CA_OTP_ATTR_S stOtpAttr;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if(enOtpFuse >= HI_UNF_ADVCA_OTP_FUSE_BUTT || enOtpFuse <= HI_UNF_ADVCA_OTP_NULL)
    {
        HI_ERR_CA("Invalid parameter, enOtpFuse = %d\n", enOtpFuse);
        return HI_ERR_CA_INVALID_PARA;
    }

    if(pstOtpFuseAttr == NULL)
    {
        HI_ERR_CA("Invalid parameter, pstOtpFuseAttr == NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(&stOtpAttr, 0, sizeof(stOtpAttr));
    stOtpAttr.enOtpFuseId = enOtpFuse;
    ret = ioctl(g_s32CaFd, CMD_CA_GET_OTP_FUSE, &stOtpAttr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_OTP_FUSE err. \n");
        return ret;
    }
    memcpy(pstOtpFuseAttr, &stOtpAttr.stOtpAttr, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));

    return ret;
}

static HI_VOID UNF_ADVCA_PrepareTAdata(HI_UNF_ADVCA_KEYLADDER_TA_ATTR_S *pstTAAttr, CA_KEYLADDER_ATTR_S *pstKladAttr)
{

    pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enTAKlAttr = pstTAAttr->enTAKlAttr;

    if (pstTAAttr->enTAKlAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ENABLE)
    {
        pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.bEnable = pstTAAttr->bEnable;
    }
    else if (pstTAAttr->enTAKlAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ALG)
    {
        pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enAlgType = pstTAAttr->enAlgType;
    }
    else if (pstTAAttr->enTAKlAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_SESSION_KEY)
    {
        pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage = pstTAAttr->enStage;
        memcpy(pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.au8SessionKey, pstTAAttr->au8SessionKey, 16);
    }
    else if (pstTAAttr->enTAKlAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_LOAD_TRANDATA)
    {
        pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage = pstTAAttr->enStage;
        pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.u32TranDataLen = pstTAAttr->u32TranDataLen;
        memcpy(pstKladAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.u8TranData, pstTAAttr->pu8TranData, pstTAAttr->u32TranDataLen);
    }
}

HI_S32 HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_TYPE_E enKeyLadderType, HI_UNF_ADVCA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 ret = HI_SUCCESS;
    CA_KEYLADDER_ATTR_S stKeyladderAttr;

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if(enKeyLadderType >= HI_UNF_ADVCA_KEYLADDER_TYPE_BUTT)
    {
        HI_ERR_CA("Invalid parameter, enKeyLadderType = %d\n", enKeyLadderType);
        return HI_ERR_CA_INVALID_PARA;
    }

    if(pstKeyladderAttr == NULL)
    {
        HI_ERR_CA("Invalid parameter, pstKeyladderAttr = NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }


    memset(&stKeyladderAttr, 0, sizeof(stKeyladderAttr));
    stKeyladderAttr.enKeyLadderType = enKeyLadderType;

    if (enKeyLadderType == HI_UNF_ADVCA_KEYLADDER_TA)
    {
        UNF_ADVCA_PrepareTAdata(&pstKeyladderAttr->unKlAttr.stTAKlAttr, &stKeyladderAttr);
    }
    else
    {
        memcpy(&stKeyladderAttr.stKeyladderAttr, pstKeyladderAttr, sizeof(HI_UNF_ADVCA_KEYLADDER_ATTR_S));
    }

    ret = ioctl(g_s32CaFd, CMD_CA_SET_KEYLADDER_ATTR, &stKeyladderAttr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_SET_KEYLADDER_ATTR err:0x%x\n", ret);
        return ret;
    }
#if !defined(CHIP_TYPE_hi3798mv100) \
 && !defined(CHIP_TYPE_hi3796mv100) \
 && !defined(CHIP_TYPE_hi3716dv100) \
 && defined(HI_ADVCA_TYPE_VERIMATRIX)
    if (HI_UNF_ADVCA_KEYLADDER_GDRM == enKeyLadderType)
    {
        if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT == pstKeyladderAttr->unKlAttr.stGDRMAttr.enGDRMKlAttr)
        {
            memcpy(pstKeyladderAttr->unKlAttr.stGDRMAttr.au8Output, stKeyladderAttr.stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, 16);
        }
        else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG == pstKeyladderAttr->unKlAttr.stGDRMAttr.enGDRMKlAttr)
        {
            memcpy(pstKeyladderAttr->unKlAttr.stGDRMAttr.au8Output, stKeyladderAttr.stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, 4);
        }
    }
#endif
    return ret;
}


HI_S32 HI_UNF_ADVCA_CaVendorOperation(HI_UNF_ADVCA_VENDORID_E enCaVendor, HI_UNF_ADVCA_CA_VENDOR_OPT_S *pstCaVendorOpt)
{
    HI_S32 ret = HI_SUCCESS;
    CA_VENDOR_OPT_S CaVendorOpt;
    HI_UNF_ADVCA_CA_VENDOR_OPT_E enCaVendorOpt;
    HI_U8 *pu8RefCbcMac = NULL;
    HI_U32 u32AppLen;
    HI_UNF_CIPHER_HASH_ATTS_S stCipherHashAttr;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_U8 u8CbcMac[16] = {0};

    if (g_AdvcaInitCounter < 0)
    {
        HI_ERR_CA("ca not init\n");
        return HI_ERR_CA_NOT_INIT;
    }

    if (enCaVendor >= HI_UNF_ADVCA_VENDORIDE_BUTT)
    {
        HI_ERR_CA("Invalid parameter, enCaVendor = %d\n", enCaVendor);
        return HI_ERR_CA_INVALID_PARA;
    }

    if (pstCaVendorOpt == NULL)
    {
        HI_ERR_CA("Invalid parameter, pstCaVendorOpt = NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    enCaVendorOpt = pstCaVendorOpt->enCaVendorOpt;
    if (enCaVendor == HI_UNF_ADVCA_IRDETO && enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CBCMAC_CALC)
    {
        stCipherHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC;
        ret = HI_UNF_CIPHER_HashInit(&stCipherHashAttr, &hHandle);
        ret |= HI_UNF_CIPHER_HashUpdate(hHandle, pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.pu8InputData,
                                                                                    pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.u32InputDataLen);
        ret |= HI_UNF_CIPHER_HashFinal(hHandle, u8CbcMac);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CBC-MAC calculation error!\n");
            return ret;
        }
        memcpy(pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.au8OutputCBCMAC, u8CbcMac,  16);
    }
    else if (enCaVendor == HI_UNF_ADVCA_IRDETO && enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CBCMAC_AUTH)
    {
        pu8RefCbcMac = pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.au8RefCBCMAC;
        u32AppLen = pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.u32AppLen;
        ret = HI_MPI_CIPHER_CbcMac_Auth(pu8RefCbcMac, u32AppLen);

        stCipherHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC;
        ret |= HI_UNF_CIPHER_HashInit(&stCipherHashAttr, &hHandle);
        ret |= HI_UNF_CIPHER_HashUpdate(hHandle, pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.pu8InputData,
                                                 pstCaVendorOpt->unCaVendorOpt.stIrdetoCbcMac.u32InputDataLen);
        ret |= HI_UNF_CIPHER_HashFinal(hHandle, u8CbcMac);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CBC-MAC authentication error! ret = 0x%x\n", ret);
            return ret;
        }
    }
    else if(enCaVendor == HI_UNF_ADVCA_VERIMATRIX && enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_VMX_GET_RNG)
    {
        HI_U32 u32RandomNumber = 0;

        ret = HI_UNF_CIPHER_Init();
        ret |= HI_MPI_CIPHER_GetRandomNumber(&u32RandomNumber, 0);
        if (HI_SUCCESS != ret && HI_ERR_CIPHER_NO_AVAILABLE_RNG != ret)
        {
            HI_ERR_CA("HI_MPI_CIPHER_GetRandomNumber error! ret = 0x%x\n", ret);
            return ret;
        }
        else if(HI_ERR_CIPHER_NO_AVAILABLE_RNG == ret)
        {
            return ret;
        }

        pstCaVendorOpt->unCaVendorOpt.stVMXRng.u32RNG = u32RandomNumber;
    }
    else
    {
        memset(&CaVendorOpt, 0, sizeof(CaVendorOpt));
        CaVendorOpt.enCaVendor = enCaVendor;
        memcpy(&CaVendorOpt.stCaVendorOpt, pstCaVendorOpt, sizeof(HI_UNF_ADVCA_CA_VENDOR_OPT_S));
        ret = ioctl(g_s32CaFd, CMD_CA_SET_CAVENDOR_OPT, &CaVendorOpt);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("ca ioctl CMD_CA_SET_CAVENDOR_OPT err. \n");
            return ret;
        }
        memcpy(pstCaVendorOpt, &CaVendorOpt.stCaVendorOpt, sizeof(HI_UNF_ADVCA_CA_VENDOR_OPT_S));
    }

    return ret;
}

/*--------------------------------END--------------------------------------*/

